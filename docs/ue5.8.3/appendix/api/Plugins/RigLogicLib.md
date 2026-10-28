# Plugins / RigLogicLib

- module root: `Plugins/Animation/RigLogic/Source/RigLogicLib`
- headers: 270; symbols: 5707
- symbol kinds: class=159, delegate=1, enum=42, enumerator=150, function=1776, macro=260, member=764, namespace=322, prototype=1673, struct=261, typedef=296, variable=3
- PublicDependencyModuleNames: ControlRig, Core, CoreUObject, EditorFramework, Engine, UnrealEd

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/WindowsPlatformUE.h` (Private)
_(no declarations extracted)_

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/BaseImpl.h` (Private)


#### class `dna::BaseImpl`  
`class BaseImpl`  
_L11-43_
- L13 _protected function_ `explicit BaseImpl(MemoryResource* memRes_) : memRes`
- L18 _protected function_ `BaseImpl(UnknownLayerPolicy unknownPolicy, UpgradeFormatPolicy upgradePolicy, MemoryResource* memRes_) : memRes`
- L23 _protected prototype_ `~BaseImpl() = default;`
- L25 _protected prototype_ `BaseImpl(const BaseImpl&) = delete;`
- L26 _protected prototype_ `BaseImpl& operator=(const BaseImpl&) = delete;`
- L28 _protected prototype_ `BaseImpl(BaseImpl&& rhs) = delete;`
- L29 _protected prototype_ `BaseImpl& operator=(BaseImpl&&) = delete;`
- L32 _public function_ `MemoryResource* getMemoryResource()`
- L36 _public function_ `void rawCopyInto(DNA& destination, DataLayer layer, UnknownLayerPolicy policy, MemoryResource* memRes_)`
- L41 _protected member_ `MemoryResource* memRes;`
- L42 _protected member_ `mutable DNA dna;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/DNA.h` (Private)


#### struct `dna::Dispatcher`  
`template<typename TVersion, TVersion Fallback> struct Dispatcher<TVersion, Fallback>`  
_L111-126_
- L114 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion , bool transparent)`
- L130 _public typedef_ `using Super = Dispatcher<TVersion, Rest...>;`
- L133 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion version, bool transparent)`

#### struct `dna::Dispatcher`  
`template<typename TVersion, TVersion Expected, TVersion... Rest> struct Dispatcher<TVersion, Expected, Rest...> : Dispatcher<TVersion, Rest...>`  
_L129-145_
- inherits: `Dispatcher<TVersion,Rest...>`
- L114 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion , bool transparent)`
- L130 _public typedef_ `using Super = Dispatcher<TVersion, Rest...>;`
- L133 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion version, bool transparent)`

#### enum `dna::FileVersion`  
`enum FileVersion : std::uint64_t`  
_L164-175_
- L165 _public enumerator_ `unknown = 0u`
- L166 _public enumerator_ `v21 = rev(2, 1)`
- L167 _public enumerator_ `v22 = rev(2, 2)`
- L168 _public enumerator_ `v23 = rev(2, 3)`
- L169 _public enumerator_ `v24 = rev(2, 4)`
- L170 _public enumerator_ `v25 = rev(2, 5)`
- L171 _public enumerator_ `v26 = rev(2, 6)`
- L172 _public enumerator_ `v27 = rev(2, 7)`
- L173 _public enumerator_ `v28 = rev(2, 8)`
- L174 _public enumerator_ `latest = v28`

#### enum `dna::UpgradeFormatPolicy`  
`enum class UpgradeFormatPolicy`  
_L193-196_
- L194 _public enumerator_ `Disallowed`
- L195 _public enumerator_ `Allowed`

#### struct `dna::SerializationContext`  
`struct SerializationContext`  
_L198-201_
- L199 _public member_ `FileVersion version;`
- L200 _public member_ `void* data;`

#### struct `dna::Version`  
`struct Version`  
_L203-232_
- L204 _public member_ `std::uint16_t generation;`
- L205 _public member_ `std::uint16_t version;`
- L207 _public function_ `Version(FileVersion fileVersion) : generation`
- L212 _public function_ `operator FileVersion() const`
- L217 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L224 _public function_ `bool matches(FileVersion fileVersion) const`
- L229 _public function_ `bool supported() const`

#### struct `dna::ExpectedValue`  
`template<typename T> struct ExpectedValue`  
_L235-260_
- L236 _public member_ `T expected;`
- L237 _public member_ `T got;`
- L239 _public function_ `explicit ExpectedValue(const T& value) : expected`
- L245 _public function_ `template<class Archive> void load(Archive& archive)`
- L251 _public function_ `template<class Archive> void save(Archive& archive)`
- L257 _public function_ `bool matches() const`

#### struct `dna::Signature`  
`template<std::size_t Size> struct Signature`  
_L263-281_
- L264 _public typedef_ `using SignatureValueType = std::array<char, Size>;`
- L266 _public member_ `ExpectedValue<SignatureValueType> value;`
- L268 _public function_ `explicit Signature(SignatureValueType bytes) : value`
- L273 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L278 _public function_ `bool matches() const`

#### struct `dna::SectionLookupTable`  
`struct SectionLookupTable`  
_L283-312_
- L284 _public member_ `terse::ArchiveOffset<std::uint32_t> descriptor;`
- L285 _public member_ `terse::ArchiveOffset<std::uint32_t> definition;`
- L286 _public member_ `terse::ArchiveOffset<std::uint32_t> behavior;`
- L287 _public member_ `terse::ArchiveOffset<std::uint32_t> controls;`
- L288 _public member_ `terse::ArchiveOffset<std::uint32_t> joints;`
- L289 _public member_ `terse::ArchiveOffset<std::uint32_t> blendShapeChannels;`
- L290 _public member_ `terse::ArchiveOffset<std::uint32_t> animatedMaps;`
- L291 _public member_ `terse::ArchiveOffset<std::uint32_t> geometry;`
- L294 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::Index`  
`struct Index`  
_L314-342_
- L315 _public member_ `std::uint32_t id;`
- L316 _public member_ `std::uint32_t version;`
- L317 _public member_ `terse::ArchiveOffset<std::uint32_t> offset;`
- L318 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L321 _public function_ `template<std::size_t Length = 16ul> std::array<char, Length> label()`
- L332 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::IndexTable`  
`struct IndexTable`  
_L344-383_
- L345 _public member_ `Vector<Index> entries;`
- L347 _public function_ `explicit IndexTable(MemoryResource* memRes) : entries`
- L351 _public function_ `Index* get(std::uint32_t id, std::uint32_t version)`
- L360 _public function_ `const Index* get(std::uint32_t id, std::uint32_t version) const`
- L364 _public function_ `Index* create(std::uint32_t id, std::uint32_t version)`
- L370 _public function_ `void destroy(std::uint32_t id, std::uint32_t version)`
- L379 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::UnknownLayer`  
`struct UnknownLayer`  
_L385-427_
- L386 _public member_ `std::uint32_t id;`
- L387 _public member_ `std::uint32_t version;`
- L388 _public member_ `Blob<char> data;`
- L390 _public function_ `UnknownLayer(std::uint32_t id_, std::uint32_t version_, MemoryResource* memRes) : id`
- L396 _public function_ `std::uint32_t layerId()`
- L400 _public function_ `std::uint32_t layerVersion()`
- L404 _public function_ `bool layerSupported(FileVersion )`
- L409 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::Layer`  
`template<std::uint32_t Id, std::uint32_t Version, typename TData, FileVersion AvailableFromFileVersion> struct Layer : TData`  
_L430-465_
- inherits: `TData`
- L433 _public function_ `template<typename... Args> explicit Layer(Args&&... args) : TData`
- L437 _public function_ `std::uint32_t layerId()`
- L441 _public function_ `std::uint32_t layerVersion()`
- L445 _public function_ `bool layerSupported(FileVersion inVersion)`
- L450 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::LayerContainer`  
`template<> struct LayerContainer<>`  
_L471-510_
- L472 _public member_ `UnknownLayerPolicy unknownPolicy;`
- L473 _public member_ `UpgradeFormatPolicy upgradePolicy;`
- L474 _public member_ `Vector<UnknownLayer> unknownLayers;`
- L476 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes) : unknownPolicy`
- L483 _public function_ `template<typename TArchive> void serialize(TArchive& archive)`
- L507 _public function_ `void updateIndexTable(IndexTable& , FileVersion )`
- L514 _public typedef_ `using Super = LayerContainer<TRest...>;`
- L516 _public member_ `TLayer* layer;`
- L518 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes, TLayer* layer_, TRest*... rest) : Super`
- L538 _public function_ `void updateIndexTable(IndexTable& indexTable, FileVersion fileVersion)`

#### struct `dna::LayerContainer`  
`template<typename TLayer, typename... TRest> struct LayerContainer<TLayer, TRest...> : LayerContainer<TRest...>`  
_L513-553_
- inherits: `LayerContainer<TRest...>`
- L472 _public member_ `UnknownLayerPolicy unknownPolicy;`
- L473 _public member_ `UpgradeFormatPolicy upgradePolicy;`
- L474 _public member_ `Vector<UnknownLayer> unknownLayers;`
- L476 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes) : unknownPolicy`
- L483 _public function_ `template<typename TArchive> void serialize(TArchive& archive)`
- L507 _public function_ `void updateIndexTable(IndexTable& , FileVersion )`
- L514 _public typedef_ `using Super = LayerContainer<TRest...>;`
- L516 _public member_ `TLayer* layer;`
- L518 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes, TLayer* layer_, TRest*... rest) : Super`
- L538 _public function_ `void updateIndexTable(IndexTable& indexTable, FileVersion fileVersion)`

#### struct `dna::RawSurjectiveMapping`  
`template<typename TFrom, typename TTo = TFrom> struct RawSurjectiveMapping : public SurjectiveMapping<TFrom, TTo>`  
_L556-566_
- inherits: `SurjectiveMapping<TFrom,TTo>`
- L560 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawCoordinateSystem`  
`struct RawCoordinateSystem`  
_L568-592_
- L569 _public member_ `std::uint16_t xAxis;`
- L570 _public member_ `std::uint16_t yAxis;`
- L571 _public member_ `std::uint16_t zAxis;`
- L573 _public function_ `bool operator==(const CoordinateSystem& coordinateSystem) const`
- L579 _public function_ `bool operator!=(const CoordinateSystem& coordinateSystem) const`
- L584 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawLODMapping`  
`struct RawLODMapping : public LODMapping`  
_L594-604_
- inherits: `LODMapping`
- L598 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawDescriptor`  
`struct RawDescriptor`  
_L606-664_
- L607 _public typedef_ `using StringPair = std::tuple<String<char>, String<char>>;`
- L609 _public member_ `String<char> name;`
- L610 _public member_ `std::uint16_t archetype;`
- L611 _public member_ `std::uint16_t gender;`
- L612 _public member_ `std::uint16_t age;`
- L613 _public member_ `Vector<StringPair> metadata;`
- L614 _public member_ `std::uint16_t translationUnit;`
- L615 _public member_ `std::uint16_t rotationUnit;`
- L616 _public member_ `RawCoordinateSystem coordinateSystem;`
- L617 _public member_ `std::uint16_t lodCount;`
- L618 _public member_ `std::uint16_t maxLOD;`
- L619 _public member_ `String<char> complexity;`
- L620 _public member_ `String<char> dbName;`
- L622 _public function_ `explicit RawDescriptor(MemoryResource* memRes) : name`
- L638 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawDescriptorExt`  
`struct RawDescriptorExt`  
_L666-725_
- L667 _public member_ `RotationSequence rotationSequence;`
- L668 _public member_ `RotationSign rotationSign;`
- L669 _public member_ `FaceWindingOrder faceWindingOrder;`
- L671 _public function_ `explicit RawDescriptorExt(MemoryResource* memRes) : rotationSequence`
- L679 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L687 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v22> )`
- L692 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v23> )`
- L697 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v24> )`
- L702 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v25> )`
- L707 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v26> )`
- L712 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v27> )`
- L717 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion )`

#### struct `dna::RawVector3Vector`  
`struct RawVector3Vector`  
_L727-799_
- L728 _public member_ `AlignedDynArray<float> xs;`
- L729 _public member_ `AlignedDynArray<float> ys;`
- L730 _public member_ `AlignedDynArray<float> zs;`
- L732 _public function_ `explicit RawVector3Vector(MemoryResource* memRes) : xs`
- L738 _public function_ `RawVector3Vector(std::size_t size_, float initial, MemoryResource* memRes) : xs`
- L744 _public function_ `RawVector3Vector(ConstArrayView<float> xs_, ConstArrayView<float> ys_, ConstArrayView<float> zs_, MemoryResource* memRes) : xs`
- L751 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L760 _public function_ `std::size_t size() const`
- L765 _public function_ `void reserve(std::size_t count)`
- L771 _public function_ `void resize(std::size_t count)`
- L777 _public function_ `void resize(std::size_t count, float value)`
- L783 _public function_ `void clear()`
- L790 _public function_ `template<typename Iterator> void assign(Iterator start, Iterator end)`

#### struct `dna::RawDefinition`  
`struct RawDefinition`  
_L801-865_
- L802 _public member_ `RawLODMapping lodJointMapping;`
- L803 _public member_ `RawLODMapping lodBlendShapeMapping;`
- L804 _public member_ `RawLODMapping lodAnimatedMapMapping;`
- L805 _public member_ `RawLODMapping lodMeshMapping;`
- L806 _public member_ `Vector<String<char>> guiControlNames;`
- L807 _public member_ `Vector<String<char>> rawControlNames;`
- L808 _public member_ `Vector<String<char>> jointNames;`
- L809 _public member_ `Vector<String<char>> blendShapeChannelNames;`
- L810 _public member_ `Vector<String<char>> animatedMapNames;`
- L811 _public member_ `Vector<String<char>> meshNames;`
- L812 _public member_ `RawSurjectiveMapping<std::uint16_t> meshBlendShapeChannelMapping;`
- L813 _public member_ `DynArray<std::uint16_t> jointHierarchy;`
- L814 _public member_ `RawVector3Vector neutralJointTranslations;`
- L815 _public member_ `RawVector3Vector neutralJointRotations;`
- L817 _public function_ `explicit RawDefinition(MemoryResource* memRes) : lodJointMapping`
- L835 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawConditionalTable`  
`struct RawConditionalTable`  
_L867-899_
- L868 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L869 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L870 _public member_ `DynArray<float> fromValues;`
- L871 _public member_ `DynArray<float> toValues;`
- L872 _public member_ `DynArray<float> slopeValues;`
- L873 _public member_ `DynArray<float> cutValues;`
- L875 _public function_ `explicit RawConditionalTable(MemoryResource* memRes) : inputIndices`
- L885 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawPSDMatrix`  
`struct RawPSDMatrix`  
_L901-921_
- L902 _public member_ `DynArray<std::uint16_t> rows;`
- L903 _public member_ `DynArray<std::uint16_t> columns;`
- L904 _public member_ `DynArray<float> values;`
- L906 _public function_ `explicit RawPSDMatrix(MemoryResource* memRes) : rows`
- L913 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawControls`  
`struct RawControls`  
_L923-943_
- L924 _public member_ `std::uint16_t psdCount;`
- L925 _public member_ `RawConditionalTable conditionals;`
- L926 _public member_ `RawPSDMatrix psds;`
- L928 _public function_ `explicit RawControls(MemoryResource* memRes) : psdCount`
- L935 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawJointGroup`  
`struct RawJointGroup`  
_L945-982_
- L951 _public member_ `DynArray<std::uint16_t> lods;` — Row count of each LOD 12, 9, 3, |  |  + LOD-2 contains first 3 rows |  + LOD-1 contains first 9 rows + LOD-0 contains first 12 rows
- L953 _public member_ `DynArray<std::uint16_t> inputIndices;` — Sub-matrix col -> input vector
- L955 _public member_ `DynArray<std::uint16_t> outputIndices;` — Sub-matrix row -> output vector
- L957 _public member_ `AlignedDynArray<float> values;` — Non-zero values of all sub-matrices
- L959 _public member_ `DynArray<std::uint16_t> jointIndices;`
- L961 _public function_ `explicit RawJointGroup(MemoryResource* memRes) : lods`
- L970 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawJoints`  
`struct RawJoints`  
_L984-1004_
- L985 _public member_ `std::uint16_t rowCount;`
- L986 _public member_ `std::uint16_t colCount;`
- L987 _public member_ `Vector<RawJointGroup> jointGroups;`
- L989 _public function_ `explicit RawJoints(MemoryResource* memRes) : rowCount`
- L996 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawBlendShapeChannels`  
`struct RawBlendShapeChannels`  
_L1006-1026_
- L1007 _public member_ `DynArray<std::uint16_t> lods;`
- L1008 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1009 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1011 _public function_ `explicit RawBlendShapeChannels(MemoryResource* memRes) : lods`
- L1018 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawAnimatedMaps`  
`struct RawAnimatedMaps`  
_L1028-1044_
- L1029 _public member_ `DynArray<std::uint16_t> lods;`
- L1030 _public member_ `RawConditionalTable conditionals;`
- L1032 _public function_ `explicit RawAnimatedMaps(MemoryResource* memRes) : lods`
- L1038 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawBehavior`  
`struct RawBehavior`  
_L1046-1092_
- L1047 _public member_ `RawControls controls;`
- L1048 _public member_ `RawJoints joints;`
- L1049 _public member_ `RawBlendShapeChannels blendShapeChannels;`
- L1050 _public member_ `RawAnimatedMaps animatedMaps;`
- L1052 _public function_ `explicit RawBehavior(MemoryResource* memRes) : controls`
- L1060 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L1082 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion)`

#### struct `dna::RawTextureCoordinateVector`  
`struct RawTextureCoordinateVector`  
_L1094-1120_
- L1095 _public member_ `DynArray<float> us;`
- L1096 _public member_ `DynArray<float> vs;`
- L1098 _public function_ `explicit RawTextureCoordinateVector(MemoryResource* memRes) : us`
- L1104 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1111 _public function_ `std::size_t size() const`
- L1116 _public function_ `void clear()`

#### struct `dna::RawVertexLayoutVector`  
`struct RawVertexLayoutVector`  
_L1122-1153_
- L1123 _public member_ `DynArray<std::uint32_t> positions;`
- L1124 _public member_ `DynArray<std::uint32_t> textureCoordinates;`
- L1125 _public member_ `DynArray<std::uint32_t> normals;`
- L1127 _public function_ `explicit RawVertexLayoutVector(MemoryResource* memRes) : positions`
- L1134 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1143 _public function_ `std::size_t size() const`
- L1148 _public function_ `void clear()`

#### struct `dna::RawFace`  
`struct RawFace`  
_L1155-1167_
- L1156 _public member_ `DynArray<std::uint32_t> layoutIndices;`
- L1158 _public function_ `explicit RawFace(MemoryResource* memRes) : layoutIndices`
- L1163 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawVertexSkinWeights`  
`struct RawVertexSkinWeights`  
_L1169-1185_
- L1170 _public member_ `AlignedDynArray<float> weights;`
- L1171 _public member_ `DynArray<std::uint16_t> jointIndices;`
- L1173 _public function_ `explicit RawVertexSkinWeights(MemoryResource* memRes) : weights`
- L1179 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawBlendShapeTarget`  
`struct RawBlendShapeTarget`  
_L1187-1207_
- L1188 _public member_ `RawVector3Vector deltas;`
- L1189 _public member_ `DynArray<std::uint32_t> vertexIndices;`
- L1190 _public member_ `std::uint16_t blendShapeChannelIndex;`
- L1192 _public function_ `explicit RawBlendShapeTarget(MemoryResource* memRes) : deltas`
- L1199 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMesh`  
`struct RawMesh`  
_L1209-1300_
- L1210 _public member_ `terse::ArchiveOffset<std::uint32_t> offset;`
- L1211 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1212 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1213 _public member_ `RawVector3Vector positions;`
- L1214 _public member_ `RawTextureCoordinateVector textureCoordinates;`
- L1215 _public member_ `RawVector3Vector normals;`
- L1216 _public member_ `RawVertexLayoutVector layouts;`
- L1217 _public member_ `Vector<RawFace> faces;`
- L1218 _public member_ `std::uint16_t maximumInfluencePerVertex;`
- L1219 _public member_ `Vector<RawVertexSkinWeights> skinWeights;`
- L1220 _public member_ `Vector<RawBlendShapeTarget> blendShapeTargets;`
- L1221 _public member_ `terse::ArchiveOffset<std::uint32_t>::Proxy offsetMarker;`
- L1222 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1224 _public function_ `explicit RawMesh(MemoryResource* memRes) : offset`
- L1241 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1247 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L1273 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion)`

#### struct `dna::RawGeometry`  
`struct RawGeometry`  
_L1302-1314_
- L1303 _public member_ `Vector<RawMesh> meshes;`
- L1305 _public function_ `explicit RawGeometry(MemoryResource* memRes) : meshes`
- L1310 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawActivationFunction`  
`struct RawActivationFunction`  
_L1316-1332_
- L1317 _public member_ `std::uint16_t functionId;`
- L1318 _public member_ `DynArray<float> parameters;`
- L1320 _public function_ `explicit RawActivationFunction(MemoryResource* memRes) : functionId`
- L1326 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawNeuralNetworkLayer`  
`struct RawNeuralNetworkLayer`  
_L1334-1354_
- L1335 _public member_ `DynArray<float> biases;`
- L1336 _public member_ `DynArray<float> weights;` — 2D Matrix
- L1337 _public member_ `RawActivationFunction activationFunction;`
- L1339 _public function_ `explicit RawNeuralNetworkLayer(MemoryResource* memRes) : biases`
- L1346 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawNeuralNetwork`  
`struct RawNeuralNetwork`  
_L1356-1386_
- L1357 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1358 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1359 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1360 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1361 _public member_ `Vector<RawNeuralNetworkLayer> layers;`
- L1362 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1364 _public function_ `explicit RawNeuralNetwork(MemoryResource* memRes) : size`
- L1374 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMeshRegionMembership`  
`struct RawMeshRegionMembership`  
_L1388-1404_
- L1389 _public member_ `Matrix<String<char>> regionNames;` — [meshIndex][regionIndex]
- L1390 _public member_ `Vector<Matrix<std::uint16_t>> indices;` — [meshIndex][regionIndex][neuralNetworkIndices...]
- L1392 _public function_ `explicit RawMeshRegionMembership(MemoryResource* memRes) : regionNames`
- L1398 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMachineLearnedBehavior`  
`struct RawMachineLearnedBehavior`  
_L1406-1430_
- L1407 _public member_ `Vector<String<char>> mlControlNames;`
- L1408 _public member_ `RawLODMapping lodNeuralNetworkMapping;`
- L1409 _public member_ `RawMeshRegionMembership neuralNetworkToMeshRegion;`
- L1410 _public member_ `Vector<RawNeuralNetwork> neuralNetworks;`
- L1412 _public function_ `explicit RawMachineLearnedBehavior(MemoryResource* memRes) : mlControlNames`
- L1420 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawRBFPose`  
`struct RawRBFPose`  
_L1432-1448_
- L1433 _public member_ `String<char> name;`
- L1434 _public member_ `float scale;`
- L1436 _public function_ `explicit RawRBFPose(MemoryResource* memRes) : name`
- L1442 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawRBFPoseExt`  
`struct RawRBFPoseExt`  
_L1450-1470_
- L1451 _public member_ `DynArray<std::uint16_t> inputControlIndices;`
- L1452 _public member_ `DynArray<std::uint16_t> outputControlIndices;`
- L1453 _public member_ `DynArray<float> outputControlWeights;`
- L1455 _public function_ `explicit RawRBFPoseExt(MemoryResource* memRes) : inputControlIndices`
- L1462 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawRBFSolver`  
`struct RawRBFSolver`  
_L1472-1538_
- L1473 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1474 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1475 _public member_ `String<char> name;`
- L1476 _public member_ `DynArray<std::uint16_t> rawControlIndices;`
- L1477 _public member_ `DynArray<std::uint16_t> poseIndices;`
- L1478 _public member_ `DynArray<float> rawControlValues;`
- L1479 _public member_ `float radius;`
- L1480 _public member_ `float weightThreshold;`
- L1481 _public member_ `std::uint16_t solverType;`
- L1482 _public member_ `std::uint16_t automaticRadius;`
- L1483 _public member_ `std::uint16_t distanceMethod;`
- L1484 _public member_ `std::uint16_t normalizeMethod;`
- L1485 _public member_ `std::uint16_t functionType;`
- L1486 _public member_ `std::uint16_t twistAxis;`
- L1487 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1489 _public function_ `explicit RawRBFSolver(MemoryResource* memRes) : size`
- L1508 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawRBFBehavior`  
`struct RawRBFBehavior`  
_L1540-1560_
- L1541 _public member_ `RawLODMapping lodSolverMapping;`
- L1542 _public member_ `Vector<RawRBFSolver> solvers;`
- L1543 _public member_ `Vector<RawRBFPose> poses;`
- L1545 _public function_ `explicit RawRBFBehavior(MemoryResource* memRes) : lodSolverMapping`
- L1552 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawRBFBehaviorExt`  
`struct RawRBFBehaviorExt`  
_L1562-1578_
- L1563 _public member_ `Vector<String<char>> poseControlNames;`
- L1564 _public member_ `Vector<RawRBFPoseExt> poses;`
- L1566 _public function_ `explicit RawRBFBehaviorExt(MemoryResource* memRes) : poseControlNames`
- L1572 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawJointRepresentation`  
`struct RawJointRepresentation`  
_L1580-1594_
- L1581 _public member_ `std::uint16_t translation;`
- L1582 _public member_ `std::uint16_t rotation;`
- L1583 _public member_ `std::uint16_t scale;`
- L1586 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawJointBehaviorMetadata`  
`struct RawJointBehaviorMetadata`  
_L1596-1608_
- L1597 _public member_ `Vector<RawJointRepresentation> jointRepresentations;`
- L1599 _public function_ `explicit RawJointBehaviorMetadata(MemoryResource* memRes) : jointRepresentations`
- L1604 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawTwist`  
`struct RawTwist`  
_L1610-1634_
- L1611 _public member_ `DynArray<float> twistBlendWeights;`
- L1612 _public member_ `DynArray<std::uint16_t> twistOutputJointIndices;`
- L1613 _public member_ `DynArray<std::uint16_t> twistInputControlIndices;`
- L1614 _public member_ `std::uint16_t twistAxis;`
- L1616 _public function_ `explicit RawTwist(MemoryResource* memRes) : twistBlendWeights`
- L1624 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawSwing`  
`struct RawSwing`  
_L1636-1660_
- L1637 _public member_ `DynArray<float> swingBlendWeights;`
- L1638 _public member_ `DynArray<std::uint16_t> swingOutputJointIndices;`
- L1639 _public member_ `DynArray<std::uint16_t> swingInputControlIndices;`
- L1640 _public member_ `std::uint16_t twistAxis;`
- L1642 _public function_ `explicit RawSwing(MemoryResource* memRes) : swingBlendWeights`
- L1650 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawTwistSwingBehavior`  
`struct RawTwistSwingBehavior`  
_L1662-1678_
- L1663 _public member_ `Vector<RawTwist> twists;`
- L1664 _public member_ `Vector<RawSwing> swings;`
- L1666 _public function_ `explicit RawTwistSwingBehavior(MemoryResource* memRes) : twists`
- L1672 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMLOperation`  
`struct RawMLOperation`  
_L1680-1704_
- L1681 _public member_ `DynArray<std::uint32_t> parameters;`
- L1682 _public member_ `DynArray<std::uint16_t> mlOperationSetDependencyIndices;`
- L1683 _public member_ `DynArray<std::uint16_t> mlOperationDependencyIndices;`
- L1684 _public member_ `std::uint16_t operationType;`
- L1686 _public function_ `explicit RawMLOperation(MemoryResource* memRes) : parameters`
- L1694 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMachineLearnedBehaviorTypeData`  
`struct RawMachineLearnedBehaviorTypeData`  
_L1706-1722_
- L1707 _public member_ `Vector<RawLODMapping> lodMLOperationMappings;`
- L1708 _public member_ `Matrix<RawMLOperation> operations;`
- L1710 _public function_ `explicit RawMachineLearnedBehaviorTypeData(MemoryResource* memRes) : lodMLOperationMappings`
- L1716 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMachineLearnedBehaviorJoints`  
`struct RawMachineLearnedBehaviorJoints`  
_L1724-1748_
- L1725 _public member_ `DynArray<std::uint16_t> parameterKeys;`
- L1726 _public member_ `DynArray<std::uint16_t> parameterValues;`
- L1727 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1728 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1730 _public function_ `explicit RawMachineLearnedBehaviorJoints(MemoryResource* memRes) : parameterKeys`
- L1738 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::RawMachineLearnedBehaviorExt`  
`struct RawMachineLearnedBehaviorExt`  
_L1750-1766_
- L1751 _public member_ `Vector<RawMachineLearnedBehaviorTypeData> mlbTypeData;`
- L1752 _public member_ `RawMachineLearnedBehaviorJoints mlbJoints;`
- L1754 _public function_ `explicit RawMachineLearnedBehaviorExt(MemoryResource* memRes) : mlbTypeData`
- L1760 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dna::DNA`  
`struct DNA`  
_L1768-1972_
- L1769 _public member_ `MemoryResource* memRes;`
- L1770 _public member_ `Signature<3> signature{{'D', 'N', 'A'}};`
- L1771 _public member_ `Version version{FileVersion::latest};`
- L1772 _public member_ `IndexTable indexTable;`
- L1773 _public member_ `Layer<sid4("desc"), rev(1, 1), RawDescriptor, FileVersion::v22> descrip`
- L1774 _public member_ `Layer<sid4("defn"), rev(1, 1), RawDefinition, FileVersion::v22> definit`
- L1775 _public member_ `Layer<sid4("bhvr"), rev(1, 1), RawBehavior, FileVersion::v22> behav`
- L1776 _public member_ `Layer<sid4("geom"), rev(1, 1), RawGeometry, FileVersion::v22> geome`
- L1777 _public member_ `Layer<sid4("mlbh"), rev(1, 0), RawMachineLearnedBehavior, FileVersion::v23> machineLearnedBehav`
- L1778 _public member_ `Layer<sid4("rbfb"), rev(1, 0), RawRBFBehavior, FileVersion::v24> rbfBehav`
- L1779 _public member_ `Layer<sid4("rbfe"), rev(1, 0), RawRBFBehaviorExt, FileVersion::v25> rbfBehavior`
- L1780 _public member_ `Layer<sid4("jbmd"), rev(1, 0), RawJointBehaviorMetadata, FileVersion::v24> jointBehaviorMetad`
- L1781 _public member_ `Layer<sid4("twsw"), rev(1, 0), RawTwistSwingBehavior, FileVersion::v24> twistSwingBehav`
- L1782 _public member_ `Layer<sid4("mlbe"), rev(1, 0), RawMachineLearnedBehaviorExt, FileVersion::v26> machineLearnedBehavior`
- L1783 _public member_ `Layer<sid4("dsce"), rev(1, 0), RawDescriptorExt, FileVersion::v27> descriptor`
- L1785 _public typedef_ `using Layers = LayerContainer<decltype(descriptor), decltype(definition), decltype(behavior), decltype(geometry), decltype(machineLearnedBehavior), decltype(rbfBehavior), decltype(rbfBehaviorExt), decltype(jointBehaviorMetadata), decltype(twistSwingBehavior), decltype(machineLearnedBehaviorExt), decltype(descriptorExt)>;`
- L1796 _public member_ `Layers layers;`
- L1798 _public function_ `DNA(UnknownLayerPolicy unknownPolicy, UpgradeFormatPolicy upgradePolicy, MemoryResource* memRes_) : memRes`
- L1828 _public function_ `explicit DNA(MemoryResource* memRes_) : DNA`
- L1833 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1851 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> v21)`
- L1880 _public function_ `template<class Archive, typename AnyVersion> IfHigher<AnyVersion, FileVersion::v21> load(Archive& archive, AnyVersion)`
- L1906 _public function_ `template<class Archive, typename AnyVersion> IfHigher<AnyVersion, FileVersion::v21> save(Archive& archive, AnyVersion)`
- L1921 _public function_ `void ensureLayerIndexed(std::uint32_t layerId, std::uint32_t layerVersion)`
- L1927 _public function_ `void postLoadActions()`
- L1943 _public function_ `void unloadDefinition()`
- L1947 _public function_ `void unloadBehavior()`
- L1951 _public function_ `void unloadGeometry()`
- L1955 _public function_ `void unloadMachineLearnedBehavior()`
- L1960 _public function_ `void unloadRBFBehavior()`
- L1965 _public function_ `void unloadJointBehaviorMetadata()`
- L1969 _public function_ `void unloadTwistSwingBehavior()`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace tdm`
- L37 _macro_ `#define TDM_ROT_SEQ_SERIALIZER_DEFINED`
- L40 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L48 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L56 _macro_ `#define TDM_ROT_SIGN_SERIALIZER_DEFINED`
- L59 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L76 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L91 _namespace_ `namespace dna`
- L94 _function_ `template<typename Archive> void load(Archive& archive, FaceWindingOrder& value)` (scope `dna`)
- L102 _function_ `template<typename Archive> void save(Archive& archive, FaceWindingOrder& value)` (scope `dna`)
- L147 _function_ `static constexpr std::uint32_t sid4(const char* name)` (scope `dna`)
- L152 _function_ `static constexpr std::uint32_t rev(std::uint16_t generation, std::uint16_t version)` (scope `dna`)
- L156 _function_ `static constexpr std::uint16_t high16(std::uint32_t packed)` (scope `dna`)
- L160 _function_ `static constexpr std::uint16_t low16(std::uint32_t packed)` (scope `dna`)
- L177 _typedef_ `using Dispatch = Dispatcher<FileVersion, FileVersion::v21, FileVersion::v22, FileVersion::v23, FileVersion::v24, FileVersion::v25, FileVersion::v26, FileVersion::v27, FileVersion::v28>;` (scope `dna`)
- L188 _typedef_ `template<typename A, FileVersion B> using IfHigher = typename std::enable_if<(A::value() > B), void>::type;` (scope `dna`)
- L191 _typedef_ `template<typename A, FileVersion B> using IfLower = typename std::enable_if<(A::value() < B), void>::type;` (scope `dna`)
- L374 _function_ `std::remove_if(entries.begin(), entries.end(), [id, version](const Index& index) { return (index.id == id) && (index.version == version); }), entries.end());` (scope `dna::IndexTable::destroy`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/DataLayerBitmask.h` (Private)


#### enum `dna::DataLayerBitmask`  
`enum class DataLayerBitmask`  
_L10-20_
- L11 _public enumerator_ `Descriptor = 1`
- L12 _public enumerator_ `Definition = 2`
- L13 _public enumerator_ `Behavior = 4`
- L14 _public enumerator_ `GeometryBlendShapesOnly = 8`
- L15 _public enumerator_ `GeometryRest = 16`
- L16 _public enumerator_ `MachineLearnedBehavior = 32`
- L17 _public enumerator_ `RBFBehavior = 64`
- L18 _public enumerator_ `JointBehaviorMetadata = 128`
- L19 _public enumerator_ `TwistSwingBehavior = 256`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dna`
- L22 _function_ `inline DataLayerBitmask computeDataLayerBitmask(DataLayer layer)` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/DenormalizedData.h` (Private)


#### struct `dna::DenormalizedData`  
`template<class Reader> struct DenormalizedData`  
_L26-358_
- L27 _public member_ `LODMapping jointVariableAttributeIndices;`
- L28 _public member_ `LODMapping meshBlendShapeMappingIndices;`
- L29 _public member_ `Matrix<std::uint16_t> rbfPoseJointOutputIndices;`
- L30 _public member_ `Matrix<float> rbfPoseJointOutputValues;`
- L31 _public member_ `Matrix<std::uint16_t> rbfBlendShapeChannelOutputIndices;`
- L32 _public member_ `Matrix<std::uint16_t> rbfAnimatedMapOutputIndices;`
- L33 _public member_ `Vector<Matrix<std::uint32_t>> mlOperationParameters;`
- L34 _public member_ `Vector<Matrix<std::uint16_t>> mlDependencyOperationSetIndices;`
- L35 _public member_ `Vector<Matrix<std::uint16_t>> mlDependencyOperationIndices;`
- L37 _public function_ `explicit DenormalizedData(MemoryResource* memRes) : jointVariableAttributeIndices`
- L50 _public function_ `void populate(const Reader* source)`
- L62 _public function_ `void populateJointVariableAttributeIndices(const Reader* source)`
- L175 _public function_ `void populateMeshBlendShapeMappingIndices(const Reader* source)`
- L204 _public function_ `void populateRBFPoseJointOutputIndices(const Reader* source)`
- L230 _public function_ `void populateRBFPoseJointOutputValues(const Reader* source)`
- L281 _public function_ `void populateRBFBlendShapeOutputIndices(const Reader* source)`
- L301 _public function_ `void populateRBFAnimatedMapOutputIndices(const Reader* source)`
- L320 _public function_ `void populateMLOperationParameters(const Reader* source)`
- L335 _public function_ `void populateMLDependencyOperationSetIndices(const Reader* source)`
- L347 _public function_ `void populateMLDependencyOperationIndices(const Reader* source)`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace dna`
- L89 _function_ `auto isJointInLOD = [source](std::uint16_t jointIndex, std::uint16_t lod)` (scope `dna::DenormalizedData::populateJointVariableAttributeIndices`)
- L94 _function_ `auto getNumMLAttributesPerJoint = [source]()` (scope `dna::DenormalizedData::populateJointVariableAttributeIndices`)
- L185 _function_ `auto isMappingNeeded = [&meshIndices, &blendShapeIndices](const MeshBlendShapeChannelMapping& mapping)` (scope `dna::DenormalizedData::populateMeshBlendShapeMappingIndices`)
- L235 _function_ `auto jointIndexToJointGroupMap = [&]()` (scope `dna::DenormalizedData::populateRBFPoseJointOutputValues`)
- L247 _function_ `const auto indexOf = [](ConstArrayView<std::uint16_t> container, std::uint16_t val)` (scope `dna::DenormalizedData::populateRBFPoseJointOutputValues`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/Helpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`
- L13 _function_ `inline void copy(DNA& source, DNA& destination, DataLayer layer, UnknownLayerPolicy policy, MemoryResource* memRes)` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/LODConstraint.h` (Private)


#### class `dna::LODConstraint`  
`class LODConstraint`  
_L11-26_
- L13 _public prototype_ `LODConstraint(std::uint16_t maxLOD, std::uint16_t minLOD, MemoryResource* memRes);`
- L14 _public prototype_ `LODConstraint(ConstArrayView<std::uint16_t> lods, MemoryResource* memRes);`
- L16 _public prototype_ `bool hasImpactOn(std::uint16_t lodCount) const;`
- L17 _public prototype_ `std::uint16_t getMaxLOD() const;`
- L18 _public prototype_ `std::uint16_t getMinLOD() const;`
- L19 _public prototype_ `std::uint16_t getLODCount() const;`
- L20 _public prototype_ `void clampTo(std::uint16_t lodCount);`
- L21 _public prototype_ `void applyTo(Vector<std::uint16_t>& unconstrainedLODs) const;`
- L22 _public prototype_ `void applyTo(DynArray<std::uint16_t>& unconstrainedLODs) const;`
- L25 _private member_ `Vector<std::uint16_t> lods;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/LODMapping.h` (Private)


#### class `dna::LODMapping`  
`class LODMapping`  
_L22-66_
- L24 _public prototype_ `explicit LODMapping(MemoryResource* memRes_);`
- L26 _public prototype_ `std::uint16_t getLODCount() const;`
- L27 _public prototype_ `void resetIndices();`
- L28 _public prototype_ `void resetLODs();`
- L29 _public prototype_ `void reset();`
- L30 _public prototype_ `void setLODCount(std::uint16_t lodCount);`
- L31 _public prototype_ `void discardLODs(const LODConstraint& lodConstraint);`
- L32 _public prototype_ `ConstArrayView<std::uint16_t> getIndices(std::uint16_t lod) const;`
- L33 _public prototype_ `std::uint16_t getIndexListCount() const;`
- L34 _public prototype_ `void clearIndices(std::uint16_t index);`
- L35 _public prototype_ `void addIndices(std::uint16_t index, const std::uint16_t* source, std::uint16_t count);`
- L38 _public function_ `template<class TIterator> void addIndices(std::uint16_t index, TIterator begin, TIterator end)`
- L46 _public prototype_ `void associateLODWithIndices(std::uint16_t lod, std::uint16_t index);`
- L47 _public prototype_ `void mapIndices(std::function<std::uint16_t(std::uint16_t)> mapper);`
- L48 _public prototype_ `void filterIndices(std::function<bool(std::uint16_t)> filterer);`
- L49 _public prototype_ `void sortIndices();`
- L50 _public prototype_ `UnorderedSet<std::uint16_t> getCombinedDistinctIndices(MemoryResource* memRes) const;`
- L53 _private prototype_ `void cleanupIndices();`
- L64 _protected member_ `Vector<std::uint16_t> lods;` — Map indices to rows of the below defined matrix, e.g.: lods: [0, 0, 1, 1] indices: {[10, 15, 12], [9, 7, 43, 67]} expands into: 0: [10, 15, 12] 1: [10, 15, 12] 2: [9, 7, 43, 67] 3: [9, 7, 43, 67]
- L65 _protected member_ `Matrix<std::uint16_t> indices;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/ReaderImpl.h` (Private)


#### class `dna::ReaderImpl`  
`template<class TReaderBase> class ReaderImpl : public TReaderBase, public virtual BaseImpl`  
_L24-248_
- inherits: `TReaderBase,BaseImpl`
- L26 _public prototype_ `explicit ReaderImpl(MemoryResource* memRes_);`
- L29 _public prototype_ `std::uint16_t getFileFormatGeneration() const override;` — HeaderReader methods
- L30 _public prototype_ `std::uint16_t getFileFormatVersion() const override;`
- L33 _public prototype_ `StringView getName() const override;` — DescriptorReader methods
- L34 _public prototype_ `Archetype getArchetype() const override;`
- L35 _public prototype_ `Gender getGender() const override;`
- L36 _public prototype_ `std::uint16_t getAge() const override;`
- L37 _public prototype_ `std::uint32_t getMetaDataCount() const override;`
- L38 _public prototype_ `StringView getMetaDataKey(std::uint32_t index) const override;`
- L39 _public prototype_ `StringView getMetaDataValue(const char* key) const override;`
- L40 _public prototype_ `TranslationUnit getTranslationUnit() const override;`
- L41 _public prototype_ `RotationUnit getRotationUnit() const override;`
- L42 _public prototype_ `CoordinateSystem getCoordinateSystem() const override;`
- L43 _public prototype_ `RotationSequence getRotationSequence() const override;`
- L44 _public prototype_ `RotationSign getRotationSign() const override;`
- L45 _public prototype_ `FaceWindingOrder getFaceWindingOrder() const override;`
- L46 _public prototype_ `std::uint16_t getLODCount() const override;`
- L47 _public prototype_ `std::uint16_t getDBMaxLOD() const override;`
- L48 _public prototype_ `StringView getDBComplexity() const override;`
- L49 _public prototype_ `StringView getDBName() const override;`
- L52 _public prototype_ `std::uint16_t getGUIControlCount() const override;` — DefinitionReader methods
- L53 _public prototype_ `StringView getGUIControlName(std::uint16_t index) const override;`
- L54 _public prototype_ `std::uint16_t getRawControlCount() const override;`
- L55 _public prototype_ `StringView getRawControlName(std::uint16_t index) const override;`
- L56 _public prototype_ `std::uint16_t getJointCount() const override;`
- L57 _public prototype_ `StringView getJointName(std::uint16_t index) const override;`
- L58 _public prototype_ `std::uint16_t getJointIndexListCount() const override;`
- L59 _public prototype_ `ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override;`
- L60 _public prototype_ `std::uint16_t getJointParentIndex(std::uint16_t index) const override;`
- L61 _public prototype_ `std::uint16_t getBlendShapeChannelCount() const override;`
- L62 _public prototype_ `StringView getBlendShapeChannelName(std::uint16_t index) const override;`
- L63 _public prototype_ `std::uint16_t getBlendShapeChannelIndexListCount() const override;`
- L64 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override;`
- L65 _public prototype_ `std::uint16_t getAnimatedMapCount() const override;`
- L66 _public prototype_ `StringView getAnimatedMapName(std::uint16_t index) const override;`
- L67 _public prototype_ `std::uint16_t getAnimatedMapIndexListCount() const override;`
- L68 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override;`
- L69 _public prototype_ `std::uint16_t getMeshCount() const override;`
- L70 _public prototype_ `StringView getMeshName(std::uint16_t index) const override;`
- L71 _public prototype_ `std::uint16_t getMeshIndexListCount() const override;`
- L72 _public prototype_ `ConstArrayView<std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const override;`
- L73 _public prototype_ `std::uint16_t getMeshBlendShapeChannelMappingCount() const override;`
- L74 _public prototype_ `MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const override;`
- L75 _public prototype_ `ConstArrayView<std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const override;`
- L76 _public prototype_ `Vector3 getNeutralJointTranslation(std::uint16_t index) const override;`
- L77 _public prototype_ `ConstArrayView<float> getNeutralJointTranslationXs() const override;`
- L78 _public prototype_ `ConstArrayView<float> getNeutralJointTranslationYs() const override;`
- L79 _public prototype_ `ConstArrayView<float> getNeutralJointTranslationZs() const override;`
- L80 _public prototype_ `Vector3 getNeutralJointRotation(std::uint16_t index) const override;`
- L81 _public prototype_ `ConstArrayView<float> getNeutralJointRotationXs() const override;`
- L82 _public prototype_ `ConstArrayView<float> getNeutralJointRotationYs() const override;`
- L83 _public prototype_ `ConstArrayView<float> getNeutralJointRotationZs() const override;`
- L86 _public prototype_ `ConstArrayView<std::uint16_t> getGUIToRawInputIndices() const override;` — BehaviorReader methods
- L87 _public prototype_ `ConstArrayView<std::uint16_t> getGUIToRawOutputIndices() const override;`
- L88 _public prototype_ `ConstArrayView<float> getGUIToRawFromValues() const override;`
- L89 _public prototype_ `ConstArrayView<float> getGUIToRawToValues() const override;`
- L90 _public prototype_ `ConstArrayView<float> getGUIToRawSlopeValues() const override;`
- L91 _public prototype_ `ConstArrayView<float> getGUIToRawCutValues() const override;`
- L92 _public prototype_ `std::uint16_t getPSDCount() const override;`
- L93 _public prototype_ `ConstArrayView<std::uint16_t> getPSDRowIndices() const override;`
- L94 _public prototype_ `ConstArrayView<std::uint16_t> getPSDColumnIndices() const override;`
- L95 _public prototype_ `ConstArrayView<float> getPSDValues() const override;`
- L96 _public prototype_ `std::uint16_t getJointRowCount() const override;`
- L97 _public prototype_ `std::uint16_t getJointColumnCount() const override;`
- L98 _public prototype_ `ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const override;`
- L99 _public prototype_ `std::uint16_t getJointGroupCount() const override;`
- L100 _public prototype_ `ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const override;`
- L101 _public prototype_ `ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const override;`
- L102 _public prototype_ `ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const override;`
- L103 _public prototype_ `ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const override;`
- L104 _public prototype_ `ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const override;`
- L105 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelLODs() const override;`
- L106 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelOutputIndices() const override;`
- L107 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelInputIndices() const override;`
- L108 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapLODs() const override;`
- L109 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapInputIndices() const override;`
- L110 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapOutputIndices() const override;`
- L111 _public prototype_ `ConstArrayView<float> getAnimatedMapFromValues() const override;`
- L112 _public prototype_ `ConstArrayView<float> getAnimatedMapToValues() const override;`
- L113 _public prototype_ `ConstArrayView<float> getAnimatedMapSlopeValues() const override;`
- L114 _public prototype_ `ConstArrayView<float> getAnimatedMapCutValues() const override;`
- L117 _public prototype_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override;` — GeometryReader methods
- L118 _public prototype_ `Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L119 _public prototype_ `ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const override;`
- L120 _public prototype_ `ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const override;`
- L121 _public prototype_ `ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const override;`
- L122 _public prototype_ `std::uint32_t getVertexTextureCoordinateCount(std::uint16_t meshIndex) const override;`
- L123 _public prototype_ `TextureCoordinate getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const override;`
- L124 _public prototype_ `ConstArrayView<float> getVertexTextureCoordinateUs(std::uint16_t meshIndex) const override;`
- L125 _public prototype_ `ConstArrayView<float> getVertexTextureCoordinateVs(std::uint16_t meshIndex) const override;`
- L126 _public prototype_ `std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const override;`
- L127 _public prototype_ `Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const override;`
- L128 _public prototype_ `ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const override;`
- L129 _public prototype_ `ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const override;`
- L130 _public prototype_ `ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const override;`
- L131 _public prototype_ `std::uint32_t getFaceCount(std::uint16_t meshIndex) const override;`
- L132 _public prototype_ `ConstArrayView<std::uint32_t> getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const override;`
- L133 _public prototype_ `std::uint32_t getVertexLayoutCount(std::uint16_t meshIndex) const override;`
- L134 _public prototype_ `VertexLayout getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const override;`
- L135 _public prototype_ `ConstArrayView<std::uint32_t> getVertexLayoutPositionIndices(std::uint16_t meshIndex) const override;`
- L136 _public prototype_ `ConstArrayView<std::uint32_t> getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const override;`
- L137 _public prototype_ `ConstArrayView<std::uint32_t> getVertexLayoutNormalIndices(std::uint16_t meshIndex) const override;`
- L138 _public prototype_ `std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const override;`
- L139 _public prototype_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override;`
- L140 _public prototype_ `ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L141 _public prototype_ `ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L142 _public prototype_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override;`
- L143 _public prototype_ `std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override;`
- L144 _public prototype_ `std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override;`
- L145 _public prototype_ `Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const override;`
- L148 _public prototype_ `ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override;`
- L149 _public prototype_ `ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override;`
- L150 _public prototype_ `ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override;`
- L151 _public prototype_ `ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const override;`
- L154 _public prototype_ `std::uint16_t getMLControlCount() const override;` — MachineLearnedBehaviorReader methods
- L155 _public prototype_ `StringView getMLControlName(std::uint16_t index) const override;`
- L156 _public prototype_ `std::uint16_t getNeuralNetworkCount() const override;`
- L157 _public prototype_ `std::uint16_t getNeuralNetworkIndexListCount() const override;`
- L158 _public prototype_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForLOD(std::uint16_t lod) const override;`
- L159 _public prototype_ `std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const override;`
- L160 _public prototype_ `StringView getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const override;`
- L161 _public prototype_ `ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const override;`
- L163 _public prototype_ `ConstArrayView<std::uint16_t> getNeuralNetworkInputIndices(std::uint16_t netIndex) const override;`
- L164 _public prototype_ `ConstArrayView<std::uint16_t> getNeuralNetworkOutputIndices(std::uint16_t netIndex) const override;`
- L165 _public prototype_ `std::uint16_t getNeuralNetworkLayerCount(std::uint16_t netIndex) const override;`
- L166 _public prototype_ `ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex) const override;`
- L167 _public prototype_ `ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex) const override;`
- L169 _public prototype_ `ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex) const override;`
- L170 _public prototype_ `ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex) const override;`
- L173 _public prototype_ `std::uint16_t getRBFPoseCount() const override;` — RBFBehaviorReader methods
- L174 _public prototype_ `StringView getRBFPoseName(std::uint16_t index) const override;`
- L175 _public prototype_ `ConstArrayView<std::uint16_t> getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const override;`
- L176 _public prototype_ `ConstArrayView<std::uint16_t> getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const override;`
- L177 _public prototype_ `ConstArrayView<std::uint16_t> getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const override;`
- L178 _public prototype_ `ConstArrayView<float> getRBFPoseJointOutputValues(std::uint16_t poseIndex) const override;`
- L179 _public prototype_ `float getRBFPoseScale(std::uint16_t poseIndex) const override;`
- L180 _public prototype_ `std::uint16_t getRBFPoseControlCount() const override;`
- L181 _public prototype_ `StringView getRBFPoseControlName(std::uint16_t poseControlIndex) const override;`
- L182 _public prototype_ `ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const override;`
- L183 _public prototype_ `ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const override;`
- L184 _public prototype_ `ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const override;`
- L185 _public prototype_ `std::uint16_t getRBFSolverCount() const override;`
- L186 _public prototype_ `std::uint16_t getRBFSolverIndexListCount() const override;`
- L187 _public prototype_ `ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override;`
- L188 _public prototype_ `StringView getRBFSolverName(std::uint16_t index) const override;`
- L189 _public prototype_ `ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const override;`
- L190 _public prototype_ `ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const override;`
- L191 _public prototype_ `ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const override;`
- L192 _public prototype_ `RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const override;`
- L193 _public prototype_ `float getRBFSolverRadius(std::uint16_t solverIndex) const override;`
- L194 _public prototype_ `AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const override;`
- L195 _public prototype_ `float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const override;`
- L196 _public prototype_ `RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const override;`
- L197 _public prototype_ `RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const override;`
- L198 _public prototype_ `RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const override;`
- L199 _public prototype_ `TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const override;`
- L202 _public prototype_ `TranslationRepresentation getJointTranslationRepresentation(std::uint16_t jointIndex) const override;` — JointBehaviorMetadataReader methods
- L203 _public prototype_ `RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const override;`
- L204 _public prototype_ `ScaleRepresentation getJointScaleRepresentation(std::uint16_t jointIndex) const override;`
- L207 _public prototype_ `std::uint16_t getTwistCount() const override;` — TwistSwingBehaviorReader methods
- L208 _public prototype_ `TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const override;`
- L209 _public prototype_ `ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const override;`
- L210 _public prototype_ `ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const override;`
- L211 _public prototype_ `ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const override;`
- L212 _public prototype_ `std::uint16_t getSwingCount() const override;`
- L213 _public prototype_ `TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const override;`
- L214 _public prototype_ `ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const override;`
- L215 _public prototype_ `ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const override;`
- L216 _public prototype_ `ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const override;`
- L219 _public prototype_ `std::uint16_t getMLTypeCount() const override;` — MachineLearnedBehaviorExtReader methods
- L220 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override;`
- L221 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L222 _public prototype_ `MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override;`
- L225 _public prototype_ `ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override;`
- L228 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override;`
- L231 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override;`
- L234 _public prototype_ `std::uint16_t getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L235 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const override;`
- L238 _public prototype_ `ConstArrayView<std::uint16_t> getMLJointsInputIndices() const override;`
- L239 _public prototype_ `ConstArrayView<std::uint16_t> getMLJointsOutputIndices() const override;`
- L240 _public prototype_ `ConstArrayView<std::uint16_t> getMLJointsParameterKeys() const override;`
- L241 _public prototype_ `ConstArrayView<std::uint16_t> getMLJointsParameterValues() const override;`
- L244 _protected member_ `mutable DenormalizedData<TReaderBase> cache;`
- L247 _private prototype_ `bool isMLExtLoaded() const;`
- L255 _function_ `template<class TReaderBase> inline ReaderImpl<TReaderBase>::ReaderImpl(MemoryResource* memRes_) : BaseImpl`
- L269 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getFileFormatGeneration() const`
- L274 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getFileFormatVersion() const`
- L279 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getName() const`
- L284 _function_ `template<class TReaderBase> inline Archetype ReaderImpl<TReaderBase>::getArchetype() const`
- L289 _function_ `template<class TReaderBase> inline Gender ReaderImpl<TReaderBase>::getGender() const`
- L294 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getAge() const`
- L299 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getMetaDataCount() const`
- L304 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getMetaDataKey(std::uint32_t index) const`
- L313 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getMetaDataValue(const char* key) const`
- L324 _function_ `template<class TReaderBase> inline TranslationUnit ReaderImpl<TReaderBase>::getTranslationUnit() const`
- L329 _function_ `template<class TReaderBase> inline RotationUnit ReaderImpl<TReaderBase>::getRotationUnit() const`
- L334 _function_ `template<class TReaderBase> inline CoordinateSystem ReaderImpl<TReaderBase>::getCoordinateSystem() const`
- L341 _function_ `template<class TReaderBase> inline RotationSequence ReaderImpl<TReaderBase>::getRotationSequence() const`
- L346 _function_ `template<class TReaderBase> inline RotationSign ReaderImpl<TReaderBase>::getRotationSign() const`
- L351 _function_ `template<class TReaderBase> inline FaceWindingOrder ReaderImpl<TReaderBase>::getFaceWindingOrder() const`
- L356 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getLODCount() const`
- L361 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getDBMaxLOD() const`
- L366 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getDBComplexity() const`
- L371 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getDBName() const`
- L376 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getGUIControlCount() const`
- L381 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getGUIControlName(std::uint16_t index) const`
- L390 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getRawControlCount() const`
- L395 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getRawControlName(std::uint16_t index) const`
- L404 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointCount() const`
- L409 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getJointName(std::uint16_t index) const`
- L418 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointIndexListCount() const`
- L423 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointIndicesForLOD(std::uint16_t lod) const`
- L428 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointParentIndex(std::uint16_t index) const`
- L436 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getBlendShapeChannelCount() const`
- L441 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getBlendShapeChannelName(std::uint16_t index) const`
- L450 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getBlendShapeChannelIndexListCount() const`
- L455 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const`
- L460 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getAnimatedMapCount() const`
- L465 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getAnimatedMapName(std::uint16_t index) const`
- L474 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getAnimatedMapIndexListCount() const`
- L479 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getAnimatedMapIndicesForLOD(std::uint16_t lod) const`
- L484 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMeshCount() const`
- L489 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getMeshName(std::uint16_t index) const`
- L498 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMeshIndexListCount() const`
- L503 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getMeshIndicesForLOD(std::uint16_t lod) const`
- L508 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMeshBlendShapeChannelMappingCount() const`
- L513 _function_ `template<class TReaderBase> inline MeshBlendShapeChannelMapping ReaderImpl<TReaderBase>::getMeshBlendShapeChannelMapping(std::uint16_t index) const`
- L520 _function_ `ReaderImpl<TReaderBase>::getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const`
- L528 _function_ `template<class TReaderBase> inline Vector3 ReaderImpl<TReaderBase>::getNeutralJointTranslation(std::uint16_t index) const`
- L537 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeutralJointTranslationXs() const`
- L543 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeutralJointTranslationYs() const`
- L549 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeutralJointTranslationZs() const`
- L555 _function_ `template<class TReaderBase> inline Vector3 ReaderImpl<TReaderBase>::getNeutralJointRotation(std::uint16_t index) const`
- L564 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeutralJointRotationXs() const`
- L570 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeutralJointRotationYs() const`
- L576 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeutralJointRotationZs() const`
- L582 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getGUIToRawInputIndices() const`
- L588 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getGUIToRawOutputIndices() const`
- L594 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getGUIToRawFromValues() const`
- L600 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getGUIToRawToValues() const`
- L606 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getGUIToRawSlopeValues() const`
- L612 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getGUIToRawCutValues() const`
- L618 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getPSDCount() const`
- L623 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getPSDRowIndices() const`
- L629 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getPSDColumnIndices() const`
- L635 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getPSDValues() const`
- L641 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointRowCount() const`
- L646 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointColumnCount() const`
- L651 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointVariableAttributeIndices(std::uint16_t lod) const`
- L659 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointGroupCount() const`
- L664 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointGroupLODs(std::uint16_t jointGroupIndex) const`
- L673 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointGroupInputIndices(std::uint16_t jointGroupIndex) const`
- L682 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const`
- L691 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getJointGroupValues(std::uint16_t jointGroupIndex) const`
- L700 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointGroupJointIndices(std::uint16_t jointGroupIndex) const`
- L709 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getBlendShapeChannelLODs() const`
- L715 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getBlendShapeChannelInputIndices() const`
- L721 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getBlendShapeChannelOutputIndices() const`
- L727 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getAnimatedMapLODs() const`
- L733 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getAnimatedMapInputIndices() const`
- L739 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getAnimatedMapOutputIndices() const`
- L745 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getAnimatedMapFromValues() const`
- L751 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getAnimatedMapToValues() const`
- L757 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getAnimatedMapSlopeValues() const`
- L763 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getAnimatedMapCutValues() const`
- L769 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getVertexPositionCount(std::uint16_t meshIndex) const`
- L777 _function_ `template<class TReaderBase> inline Position ReaderImpl<TReaderBase>::getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const`
- L788 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexPositionXs(std::uint16_t meshIndex) const`
- L797 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexPositionYs(std::uint16_t meshIndex) const`
- L806 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexPositionZs(std::uint16_t meshIndex) const`
- L815 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getVertexTextureCoordinateCount(std::uint16_t meshIndex) const`
- L823 _function_ `template<class TReaderBase> inline TextureCoordinate ReaderImpl<TReaderBase>::getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const`
- L835 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexTextureCoordinateUs(std::uint16_t meshIndex) const`
- L843 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexTextureCoordinateVs(std::uint16_t meshIndex) const`
- L851 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getVertexNormalCount(std::uint16_t meshIndex) const`
- L859 _function_ `template<class TReaderBase> inline Normal ReaderImpl<TReaderBase>::getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const`
- L870 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexNormalXs(std::uint16_t meshIndex) const`
- L879 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexNormalYs(std::uint16_t meshIndex) const`
- L888 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexNormalZs(std::uint16_t meshIndex) const`
- L897 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getFaceCount(std::uint16_t meshIndex) const`
- L905 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint32_t> ReaderImpl<TReaderBase>::getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const`
- L916 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getVertexLayoutCount(std::uint16_t meshIndex) const`
- L924 _function_ `template<class TReaderBase> inline VertexLayout ReaderImpl<TReaderBase>::getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const`
- L935 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint32_t> ReaderImpl<TReaderBase>::getVertexLayoutPositionIndices(std::uint16_t meshIndex) const`
- L945 _function_ `ReaderImpl<TReaderBase>::getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const`
- L954 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint32_t> ReaderImpl<TReaderBase>::getVertexLayoutNormalIndices(std::uint16_t meshIndex) const`
- L963 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMaximumInfluencePerVertex(std::uint16_t meshIndex) const`
- L971 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getSkinWeightsCount(std::uint16_t meshIndex) const`
- L980 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const`
- L991 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const`
- L1002 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getBlendShapeTargetCount(std::uint16_t meshIndex) const`
- L1010 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const`
- L1020 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const`
- L1030 _function_ `template<class TReaderBase> inline Delta ReaderImpl<TReaderBase>::getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const`
- L1043 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const`
- L1054 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const`
- L1065 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const`
- L1077 _function_ `ReaderImpl<TReaderBase>::getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const`
- L1087 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMLControlCount() const`
- L1092 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getMLControlName(std::uint16_t index) const`
- L1101 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getNeuralNetworkCount() const`
- L1106 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getNeuralNetworkIndexListCount() const`
- L1111 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getNeuralNetworkIndicesForLOD(std::uint16_t lod) const`
- L1116 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMeshRegionCount(std::uint16_t meshIndex) const`
- L1124 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const`
- L1134 _function_ `ReaderImpl<TReaderBase>::getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const`
- L1146 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getNeuralNetworkInputIndices(std::uint16_t netIndex) const`
- L1155 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getNeuralNetworkOutputIndices(std::uint16_t netIndex) const`
- L1164 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getNeuralNetworkLayerCount(std::uint16_t netIndex) const`
- L1173 _function_ `template<class TReaderBase> inline ActivationFunction ReaderImpl<TReaderBase>::getNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex) const`
- L1184 _function_ `ReaderImpl<TReaderBase>::getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex) const`
- L1194 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex) const`
- L1204 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex) const`
- L1214 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getRBFPoseCount() const`
- L1219 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getRBFPoseName(std::uint16_t poseIndex) const`
- L1228 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const`
- L1241 _function_ `ReaderImpl<TReaderBase>::getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const`
- L1253 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const`
- L1265 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getRBFPoseJointOutputValues(std::uint16_t poseIndex) const`
- L1277 _function_ `template<class TReaderBase> inline float ReaderImpl<TReaderBase>::getRBFPoseScale(std::uint16_t poseIndex) const`
- L1286 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getRBFPoseControlCount() const`
- L1291 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getRBFPoseControlName(std::uint16_t poseControlIndex) const`
- L1300 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFPoseInputControlIndices(std::uint16_t poseIndex) const`
- L1309 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const`
- L1318 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const`
- L1327 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getRBFSolverCount() const`
- L1332 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getRBFSolverIndexListCount() const`
- L1337 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFSolverIndicesForLOD(std::uint16_t lod) const`
- L1342 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getRBFSolverName(std::uint16_t solverIndex) const`
- L1350 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFSolverRawControlIndices(std::uint16_t solverIndex) const`
- L1358 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getRBFSolverPoseIndices(std::uint16_t solverIndex) const`
- L1366 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getRBFSolverRawControlValues(std::uint16_t solverIndex) const`
- L1374 _function_ `template<class TReaderBase> inline RBFSolverType ReaderImpl<TReaderBase>::getRBFSolverType(std::uint16_t solverIndex) const`
- L1382 _function_ `template<class TReaderBase> inline float ReaderImpl<TReaderBase>::getRBFSolverRadius(std::uint16_t solverIndex) const`
- L1390 _function_ `template<class TReaderBase> inline AutomaticRadius ReaderImpl<TReaderBase>::getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const`
- L1398 _function_ `template<class TReaderBase> inline float ReaderImpl<TReaderBase>::getRBFSolverWeightThreshold(std::uint16_t solverIndex) const`
- L1406 _function_ `template<class TReaderBase> inline RBFDistanceMethod ReaderImpl<TReaderBase>::getRBFSolverDistanceMethod(std::uint16_t solverIndex) const`
- L1414 _function_ `template<class TReaderBase> inline RBFNormalizeMethod ReaderImpl<TReaderBase>::getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const`
- L1422 _function_ `template<class TReaderBase> inline RBFFunctionType ReaderImpl<TReaderBase>::getRBFSolverFunctionType(std::uint16_t solverIndex) const`
- L1430 _function_ `template<class TReaderBase> inline TwistAxis ReaderImpl<TReaderBase>::getRBFSolverTwistAxis(std::uint16_t solverIndex) const`
- L1438 _function_ `template<class TReaderBase> inline TranslationRepresentation ReaderImpl<TReaderBase>::getJointTranslationRepresentation(std::uint16_t jointIndex) const`
- L1446 _function_ `template<class TReaderBase> inline RotationRepresentation ReaderImpl<TReaderBase>::getJointRotationRepresentation(std::uint16_t jointIndex) const`
- L1454 _function_ `template<class TReaderBase> inline ScaleRepresentation ReaderImpl<TReaderBase>::getJointScaleRepresentation(std::uint16_t jointIndex) const`
- L1462 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getTwistCount() const`
- L1467 _function_ `template<class TReaderBase> inline TwistAxis ReaderImpl<TReaderBase>::getTwistSetupTwistAxis(std::uint16_t twistIndex) const`
- L1475 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getTwistInputControlIndices(std::uint16_t twistIndex) const`
- L1483 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getTwistOutputJointIndices(std::uint16_t twistIndex) const`
- L1491 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getTwistBlendWeights(std::uint16_t twistIndex) const`
- L1499 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getSwingCount() const`
- L1504 _function_ `template<class TReaderBase> inline TwistAxis ReaderImpl<TReaderBase>::getSwingSetupTwistAxis(std::uint16_t swingIndex) const`
- L1512 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getSwingInputControlIndices(std::uint16_t swingIndex) const`
- L1520 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getSwingOutputJointIndices(std::uint16_t swingIndex) const`
- L1528 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getSwingBlendWeights(std::uint16_t swingIndex) const`
- L1536 _function_ `template<class TReaderBase> inline bool ReaderImpl<TReaderBase>::isMLExtLoaded() const`
- L1541 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMLTypeCount() const`
- L1549 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMLOperationSetCount(std::uint16_t mlTypeIndex) const`
- L1560 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const`
- L1575 _function_ `template<class TReaderBase> inline MachineLearnedBehaviorOperationType ReaderImpl<TReaderBase>::getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const`
- L1600 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint32_t> ReaderImpl<TReaderBase>::getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const`
- L1628 _function_ `ReaderImpl<TReaderBase>::getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const`
- L1656 _function_ `ReaderImpl<TReaderBase>::getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const`
- L1683 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const`
- L1700 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const`
- L1718 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getMLJointsInputIndices() const`
- L1726 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getMLJointsOutputIndices() const`
- L1734 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getMLJointsParameterKeys() const`
- L1742 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getMLJointsParameterValues() const`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/SurjectiveMapping.h` (Private)


#### struct `dna::SurjectiveMapping`  
`template<typename TFrom, typename TTo = TFrom> struct SurjectiveMapping`  
_L20-96_
- L28 _public function_ `explicit SurjectiveMapping(MemoryResource* memRes) : from`
- L33 _public function_ `Pair get(std::size_t index) const`
- L38 _public function_ `void add(TFrom from_, TTo to_)`
- L43 _public function_ `void set(std::size_t index, TFrom from_, TTo to_)`
- L52 _public function_ `void removeIf(std::function<bool(const TFrom&, const TTo&)> predicate)`
- L69 _public function_ `void updateFrom(const UnorderedMap<TFrom, TFrom>& mapping)`
- L73 _public function_ `void updateTo(const UnorderedMap<TTo, TTo>& mapping)`
- L77 _public function_ `std::size_t size() const`
- L82 _public function_ `void clear()`
- L89 _private function_ `template<typename U> void update(Vector<U>& target, const UnorderedMap<U, U>& mapping)`
- L94 _protected member_ `Vector<TFrom> from;`
- L95 _protected member_ `Vector<TTo> to;`

#### struct `dna::SurjectiveMapping::Pair`  
`struct Pair`  
_L22-25_
- L23 _public member_ `TFrom from;`
- L24 _public member_ `TTo to;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace dna`
- L90 _function_ `std::transform(target.begin(), target.end(), target.begin(), [&mapping](U oldValue) { return mapping.at(oldValue); });` (scope `dna::SurjectiveMapping::update`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/TypeDefs.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace dna`
- L19 _typedef_ `template<typename T> using AlignedAllocator = PolyAllocator<T, 64ul, AlignedMemoryResource>;` (scope `dna`)
- L22 _typedef_ `template<typename T> using Blob = terse::Blob<T, PolyAllocator<T>>;` (scope `dna`)
- L25 _typedef_ `template<typename T> using DynArray = terse::DynArray<T, PolyAllocator<T>>;` (scope `dna`)
- L28 _typedef_ `template<typename T> using AlignedDynArray = terse::DynArray<T, AlignedAllocator<T>>;` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/WriterImpl.h` (Private)


#### class `dna::WriterImpl`  
`template<class TWriterBase> class WriterImpl : public TWriterBase, public virtual BaseImpl`  
_L55-332_
- inherits: `TWriterBase,BaseImpl`
- L57 _public prototype_ `explicit WriterImpl(MemoryResource* memRes_);`
- L60 _public prototype_ `void setFileFormatGeneration(std::uint16_t generation) override;` — HeaderWriter methods
- L61 _public prototype_ `void setFileFormatVersion(std::uint16_t version) override;`
- L64 _public prototype_ `void setName(const char* name) override;` — DescriptorWriter methods
- L65 _public prototype_ `void setArchetype(Archetype archetype) override;`
- L66 _public prototype_ `void setGender(Gender gender) override;`
- L67 _public prototype_ `void setAge(std::uint16_t age) override;`
- L68 _public prototype_ `void clearMetaData() override;`
- L69 _public prototype_ `void setMetaData(const char* key, const char* value) override;`
- L70 _public prototype_ `void setTranslationUnit(TranslationUnit unit) override;`
- L71 _public prototype_ `void setRotationUnit(RotationUnit unit) override;`
- L72 _public prototype_ `void setCoordinateSystem(CoordinateSystem system) override;`
- L73 _public prototype_ `void setRotationSequence(RotationSequence rotationSequence) override;`
- L74 _public prototype_ `void setRotationSign(const RotationSign& rotationSign) override;`
- L75 _public prototype_ `void setFaceWindingOrder(FaceWindingOrder faceWindingOrder) override;`
- L76 _public prototype_ `void setLODCount(std::uint16_t lodCount) override;`
- L77 _public prototype_ `void setDBMaxLOD(std::uint16_t lod) override;`
- L78 _public prototype_ `void setDBComplexity(const char* name) override;`
- L79 _public prototype_ `void setDBName(const char* name) override;`
- L82 _public prototype_ `void clearGUIControlNames() override;` — DefinitionWriter methods
- L83 _public prototype_ `void setGUIControlName(std::uint16_t index, const char* name) override;`
- L84 _public prototype_ `void clearRawControlNames() override;`
- L85 _public prototype_ `void setRawControlName(std::uint16_t index, const char* name) override;`
- L86 _public prototype_ `void clearJointNames() override;`
- L87 _public prototype_ `void setJointName(std::uint16_t index, const char* name) override;`
- L88 _public prototype_ `void clearJointIndices() override;`
- L89 _public prototype_ `void setJointIndices(std::uint16_t index, const std::uint16_t* jointIndices, std::uint16_t count) override;`
- L90 _public prototype_ `void clearLODJointMappings() override;`
- L91 _public prototype_ `void setLODJointMapping(std::uint16_t lod, std::uint16_t index) override;`
- L92 _public prototype_ `void clearBlendShapeChannelNames() override;`
- L93 _public prototype_ `void setJointHierarchy(const std::uint16_t* jointIndices, std::uint16_t count) override;`
- L94 _public prototype_ `void setBlendShapeChannelName(std::uint16_t index, const char* name) override;`
- L95 _public prototype_ `void clearBlendShapeChannelIndices() override;`
- L96 _public prototype_ `void setBlendShapeChannelIndices(std::uint16_t index, const std::uint16_t* blendShapeChannelIndices, std::uint16_t count) override;`
- L99 _public prototype_ `void clearLODBlendShapeChannelMappings() override;`
- L100 _public prototype_ `void setLODBlendShapeChannelMapping(std::uint16_t lod, std::uint16_t index) override;`
- L101 _public prototype_ `void clearAnimatedMapNames() override;`
- L102 _public prototype_ `void setAnimatedMapName(std::uint16_t index, const char* name) override;`
- L103 _public prototype_ `void clearAnimatedMapIndices() override;`
- L104 _public prototype_ `void setAnimatedMapIndices(std::uint16_t index, const std::uint16_t* animatedMapIndices, std::uint16_t count) override;`
- L105 _public prototype_ `void clearLODAnimatedMapMappings() override;`
- L106 _public prototype_ `void setLODAnimatedMapMapping(std::uint16_t lod, std::uint16_t index) override;`
- L107 _public prototype_ `void clearMeshNames() override;`
- L108 _public prototype_ `void setMeshName(std::uint16_t index, const char* name) override;`
- L109 _public prototype_ `void clearMeshIndices() override;`
- L110 _public prototype_ `void setMeshIndices(std::uint16_t index, const std::uint16_t* meshIndices, std::uint16_t count) override;`
- L111 _public prototype_ `void clearLODMeshMappings() override;`
- L112 _public prototype_ `void setLODMeshMapping(std::uint16_t lod, std::uint16_t index) override;`
- L113 _public prototype_ `void clearMeshBlendShapeChannelMappings() override;`
- L114 _public prototype_ `void setMeshBlendShapeChannelMapping(std::uint32_t index, std::uint16_t meshIndex, std::uint16_t blendShapeChannelIndex) override;`
- L117 _public prototype_ `void setNeutralJointTranslations(const Vector3* translations, std::uint16_t count) override;`
- L118 _public prototype_ `void setNeutralJointRotations(const Vector3* rotations, std::uint16_t count) override;`
- L121 _public prototype_ `void setGUIToRawInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) override;` — BehaviorWriter methods
- L122 _public prototype_ `void setGUIToRawOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) override;`
- L123 _public prototype_ `void setGUIToRawFromValues(const float* fromValues, std::uint16_t count) override;`
- L124 _public prototype_ `void setGUIToRawToValues(const float* toValues, std::uint16_t count) override;`
- L125 _public prototype_ `void setGUIToRawSlopeValues(const float* slopeValues, std::uint16_t count) override;`
- L126 _public prototype_ `void setGUIToRawCutValues(const float* cutValues, std::uint16_t count) override;`
- L127 _public prototype_ `void setPSDCount(std::uint16_t count) override;`
- L128 _public prototype_ `void setPSDRowIndices(const std::uint16_t* rowIndices, std::uint16_t count) override;`
- L129 _public prototype_ `void setPSDColumnIndices(const std::uint16_t* columnIndices, std::uint16_t count) override;`
- L130 _public prototype_ `void setPSDValues(const float* weights, std::uint16_t count) override;`
- L131 _public prototype_ `void setJointRowCount(std::uint16_t rowCount) override;`
- L132 _public prototype_ `void setJointColumnCount(std::uint16_t columnCount) override;`
- L133 _public prototype_ `void clearJointGroups() override;`
- L134 _public prototype_ `void deleteJointGroup(std::uint16_t jointGroupIndex) override;`
- L135 _public prototype_ `void setJointGroupLODs(std::uint16_t jointGroupIndex, const std::uint16_t* lods, std::uint16_t count) override;`
- L136 _public prototype_ `void setJointGroupInputIndices(std::uint16_t jointGroupIndex, const std::uint16_t* inputIndices, std::uint16_t count) override;`
- L139 _public prototype_ `void setJointGroupOutputIndices(std::uint16_t jointGroupIndex, const std::uint16_t* outputIndices, std::uint16_t count) override;`
- L142 _public prototype_ `void setJointGroupValues(std::uint16_t jointGroupIndex, const float* values, std::uint32_t count) override;`
- L143 _public prototype_ `void setJointGroupJointIndices(std::uint16_t jointGroupIndex, const std::uint16_t* jointIndices, std::uint16_t count) override;`
- L146 _public prototype_ `void setBlendShapeChannelLODs(const std::uint16_t* lods, std::uint16_t count) override;`
- L147 _public prototype_ `void setBlendShapeChannelInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) override;`
- L148 _public prototype_ `void setBlendShapeChannelOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) override;`
- L149 _public prototype_ `void setAnimatedMapLODs(const std::uint16_t* lods, std::uint16_t count) override;`
- L150 _public prototype_ `void setAnimatedMapInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) override;`
- L151 _public prototype_ `void setAnimatedMapOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) override;`
- L152 _public prototype_ `void setAnimatedMapFromValues(const float* fromValues, std::uint16_t count) override;`
- L153 _public prototype_ `void setAnimatedMapToValues(const float* toValues, std::uint16_t count) override;`
- L154 _public prototype_ `void setAnimatedMapSlopeValues(const float* slopeValues, std::uint16_t count) override;`
- L155 _public prototype_ `void setAnimatedMapCutValues(const float* cutValues, std::uint16_t count) override;`
- L158 _public prototype_ `void clearMeshes() override;` — GeometryWriter methods
- L159 _public prototype_ `void deleteMesh(std::uint16_t meshIndex) override;`
- L160 _public prototype_ `void setVertexPositions(std::uint16_t meshIndex, const Position* positions, std::uint32_t count) override;`
- L161 _public prototype_ `void setVertexTextureCoordinates(std::uint16_t meshIndex, const TextureCoordinate* textureCoordinates, std::uint32_t count) override;`
- L164 _public prototype_ `void setVertexNormals(std::uint16_t meshIndex, const Normal* normals, std::uint32_t count) override;`
- L165 _public prototype_ `void setVertexLayouts(std::uint16_t meshIndex, const VertexLayout* layouts, std::uint32_t count) override;`
- L166 _public prototype_ `void clearFaceVertexLayoutIndices(std::uint16_t meshIndex) override;`
- L167 _public prototype_ `void setFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex, const std::uint32_t* layoutIndices, std::uint32_t count) override;`
- L171 _public prototype_ `void setMaximumInfluencePerVertex(std::uint16_t meshIndex, std::uint16_t maxInfluenceCount) override;`
- L172 _public prototype_ `void clearSkinWeights(std::uint16_t meshIndex) override;`
- L173 _public prototype_ `void setSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex, const float* weights, std::uint16_t count) override;`
- L177 _public prototype_ `void setSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex, const std::uint16_t* jointIndices, std::uint16_t count) override;`
- L181 _public prototype_ `void clearBlendShapeTargets(std::uint16_t meshIndex) override;`
- L182 _public prototype_ `void setBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint16_t blendShapeChannelIndex) override;`
- L185 _public prototype_ `void setBlendShapeTargetDeltas(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, const Delta* deltas, std::uint32_t count) override;`
- L189 _public prototype_ `void setBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, const std::uint32_t* vertexIndices, std::uint32_t count) override;`
- L195 _public prototype_ `void clearMLControlNames() override;` — MachineLearnedBehaviorWriter methods
- L196 _public prototype_ `void setMLControlName(std::uint16_t index, const char* name) override;`
- L197 _public prototype_ `void clearNeuralNetworks() override;`
- L198 _public prototype_ `void clearNeuralNetworkIndices() override;`
- L199 _public prototype_ `void setNeuralNetworkIndices(std::uint16_t index, const std::uint16_t* netIndices, std::uint16_t count) override;`
- L200 _public prototype_ `void clearMeshRegionNames() override;`
- L201 _public prototype_ `void clearMeshRegionNames(std::uint16_t meshIndex) override;`
- L202 _public prototype_ `void setMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex, const char* name) override;`
- L203 _public prototype_ `void clearLODNeuralNetworkMappings() override;`
- L204 _public prototype_ `void setLODNeuralNetworkMapping(std::uint16_t lod, std::uint16_t index) override;`
- L205 _public prototype_ `void clearNeuralNetworkIndicesPerMeshRegion() override;`
- L206 _public prototype_ `void setNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex, const std::uint16_t* netIndices, std::uint16_t count) override;`
- L210 _public prototype_ `void deleteNeuralNetwork(std::uint16_t netIndex) override;`
- L211 _public prototype_ `void setNeuralNetworkInputIndices(std::uint16_t netIndex, const std::uint16_t* inputIndices, std::uint16_t count) override;`
- L212 _public prototype_ `void setNeuralNetworkOutputIndices(std::uint16_t netIndex, const std::uint16_t* outputIndices, std::uint16_t count) override;`
- L213 _public prototype_ `void clearNeuralNetworkLayers(std::uint16_t netIndex) override;`
- L214 _public prototype_ `void setNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex, ActivationFunction function) override;`
- L217 _public prototype_ `void setNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex, const float* activationFunctionParameters, std::uint16_t count) override;`
- L221 _public prototype_ `void setNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex, const float* biases, std::uint32_t count) override;`
- L225 _public prototype_ `void setNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex, const float* weights, std::uint32_t count) override;`
- L231 _public prototype_ `void clearRBFPoses() override;` — RBFBehaviorWriter methods
- L232 _public prototype_ `void setRBFPoseName(std::uint16_t poseIndex, const char* name) override;`
- L233 _public prototype_ `void setRBFPoseScale(std::uint16_t poseIndex, float scale) override;`
- L234 _public prototype_ `void clearRBFPoseControlNames() override;`
- L235 _public prototype_ `void setRBFPoseControlName(std::uint16_t poseControlIndex, const char* name) override;`
- L236 _public prototype_ `void setRBFPoseInputControlIndices(std::uint16_t poseIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) override;`
- L239 _public prototype_ `void setRBFPoseOutputControlIndices(std::uint16_t poseIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) override;`
- L242 _public prototype_ `void setRBFPoseOutputControlWeights(std::uint16_t poseIndex, const float* controlWeights, std::uint16_t controlWeightCount) override;`
- L245 _public prototype_ `void clearRBFSolvers() override;`
- L246 _public prototype_ `void clearRBFSolverIndices() override;`
- L247 _public prototype_ `void setRBFSolverIndices(std::uint16_t index, const std::uint16_t* solverIndices, std::uint16_t count) override;`
- L248 _public prototype_ `void clearLODRBFSolverMappings() override;`
- L249 _public prototype_ `void setLODRBFSolverMapping(std::uint16_t lod, std::uint16_t index) override;`
- L250 _public prototype_ `void setRBFSolverName(std::uint16_t solverIndex, const char* name) override;`
- L251 _public prototype_ `void setRBFSolverRawControlIndices(std::uint16_t solverIndex, const std::uint16_t* inputIndices, std::uint16_t count) override;`
- L254 _public prototype_ `void setRBFSolverPoseIndices(std::uint16_t solverIndex, const std::uint16_t* poseIndices, std::uint16_t count) override;`
- L255 _public prototype_ `void setRBFSolverRawControlValues(std::uint16_t solverIndex, const float* values, std::uint16_t count) override;`
- L256 _public prototype_ `void setRBFSolverType(std::uint16_t solverIndex, RBFSolverType type) override;`
- L257 _public prototype_ `void setRBFSolverRadius(std::uint16_t solverIndex, float radius) override;`
- L258 _public prototype_ `void setRBFSolverAutomaticRadius(std::uint16_t solverIndex, AutomaticRadius automaticRadius) override;`
- L259 _public prototype_ `void setRBFSolverWeightThreshold(std::uint16_t solverIndex, float weightThreshold) override;`
- L260 _public prototype_ `void setRBFSolverDistanceMethod(std::uint16_t solverIndex, RBFDistanceMethod distanceMethod) override;`
- L261 _public prototype_ `void setRBFSolverNormalizeMethod(std::uint16_t solverIndex, RBFNormalizeMethod normalizeMethod) override;`
- L262 _public prototype_ `void setRBFSolverFunctionType(std::uint16_t solverIndex, RBFFunctionType functionType) override;`
- L263 _public prototype_ `void setRBFSolverTwistAxis(std::uint16_t solverIndex, TwistAxis twistAxis) override;`
- L266 _public prototype_ `void clearJointRepresentations() override;` — JointBehaviorMetadataWriter
- L267 _public prototype_ `void setJointTranslationRepresentation(std::uint16_t jointIndex, TranslationRepresentation representation) override;`
- L268 _public prototype_ `void setJointRotationRepresentation(std::uint16_t jointIndex, RotationRepresentation representation) override;`
- L269 _public prototype_ `void setJointScaleRepresentation(std::uint16_t jointIndex, ScaleRepresentation representation) override;`
- L272 _public prototype_ `void clearTwists() override;` — TwistSwingBehaviorWriter
- L273 _public prototype_ `void deleteTwist(std::uint16_t twistIndex) override;`
- L274 _public prototype_ `void setTwistSetupTwistAxis(std::uint16_t twistIndex, TwistAxis twistAxis) override;`
- L275 _public prototype_ `void setTwistInputControlIndices(std::uint16_t twistIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) override;`
- L278 _public prototype_ `void setTwistOutputJointIndices(std::uint16_t twistIndex, const std::uint16_t* jointIndices, std::uint16_t jointIndexCount) override;`
- L281 _public prototype_ `void setTwistBlendWeights(std::uint16_t twistIndex, const float* blendWeights, std::uint16_t blendWeightCount) override;`
- L282 _public prototype_ `void clearSwings() override;`
- L283 _public prototype_ `void deleteSwing(std::uint16_t swingIndex) override;`
- L284 _public prototype_ `void setSwingSetupTwistAxis(std::uint16_t swingIndex, TwistAxis twistAxis) override;`
- L285 _public prototype_ `void setSwingInputControlIndices(std::uint16_t swingIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) override;`
- L288 _public prototype_ `void setSwingOutputJointIndices(std::uint16_t swingIndex, const std::uint16_t* jointIndices, std::uint16_t jointIndexCount) override;`
- L291 _public prototype_ `void setSwingBlendWeights(std::uint16_t swingIndex, const float* blendWeights, std::uint16_t blendWeightCount) override;`
- L294 _public prototype_ `void clearMLExtData() override;` — MachineLearnedBehaviorExtWriter methods
- L295 _public prototype_ `void clearMLOperationSets(std::uint16_t mlTypeIndex) override;`
- L296 _public prototype_ `void clearMLOperations(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) override;`
- L297 _public prototype_ `void setMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, MachineLearnedBehaviorOperationType operationType) override;`
- L301 _public prototype_ `void setMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint32_t* parameters, std::uint16_t count) override;`
- L306 _public prototype_ `void setMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint16_t* indices, std::uint16_t count) override;`
- L311 _public prototype_ `void setMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint16_t* indices, std::uint16_t count) override;`
- L316 _public prototype_ `void clearMLOperationIndicesAndLODMappings() override;`
- L317 _public prototype_ `void clearMLOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) override;`
- L318 _public prototype_ `void clearLODMLOperationMappings(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) override;`
- L319 _public prototype_ `void setMLOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t index, const std::uint16_t* mlOperationIndices, std::uint16_t count) override;`
- L324 _public prototype_ `void setLODMLOperationMapping(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod, std::uint16_t index) override;`
- L328 _public prototype_ `void setMLJointsParameterKeys(const std::uint16_t* parameterKeys, std::uint16_t count) override;`
- L329 _public prototype_ `void setMLJointsParameterValues(const std::uint16_t* parameterValues, std::uint16_t count) override;`
- L330 _public prototype_ `void setMLJointsInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) override;`
- L331 _public prototype_ `void setMLJointsOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) override;`
- L339 _function_ `template<class TWriterBase> WriterImpl<TWriterBase>::WriterImpl(MemoryResource* memRes_) : BaseImpl`
- L352 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setFileFormatGeneration(std::uint16_t generation)`
- L357 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setFileFormatVersion(std::uint16_t version)`
- L362 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setName(const char* name)`
- L367 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setArchetype(Archetype archetype)`
- L372 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGender(Gender gender)`
- L377 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAge(std::uint16_t age)`
- L382 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMetaData()`
- L387 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMetaData(const char* key, const char* value)`
- L407 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setTranslationUnit(TranslationUnit unit)`
- L412 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRotationUnit(RotationUnit unit)`
- L417 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setCoordinateSystem(CoordinateSystem system)`
- L424 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRotationSequence(RotationSequence rotationSequence)`
- L429 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRotationSign(const RotationSign& rotationSign)`
- L434 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setFaceWindingOrder(FaceWindingOrder faceWindingOrder)`
- L439 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODCount(std::uint16_t lodCount)`
- L444 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setDBMaxLOD(std::uint16_t lod)`
- L449 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setDBComplexity(const char* name)`
- L454 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setDBName(const char* name)`
- L459 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearGUIControlNames()`
- L464 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIControlName(std::uint16_t index, const char* name)`
- L469 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearRawControlNames()`
- L474 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRawControlName(std::uint16_t index, const char* name)`
- L479 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearJointNames()`
- L484 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointName(std::uint16_t index, const char* name)`
- L489 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearJointIndices()`
- L494 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointIndices(std::uint16_t index, const std::uint16_t* jointIndices, std::uint16_t count)`
- L502 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODJointMappings()`
- L507 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODJointMapping(std::uint16_t lod, std::uint16_t index)`
- L512 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointHierarchy(const std::uint16_t* jointIndices, std::uint16_t count)`
- L517 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearBlendShapeChannelNames()`
- L522 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeChannelName(std::uint16_t index, const char* name)`
- L527 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearBlendShapeChannelIndices()`
- L532 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeChannelIndices(std::uint16_t index, const std::uint16_t* blendShapeChannelIndices, std::uint16_t count)`
- L540 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODBlendShapeChannelMappings()`
- L545 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODBlendShapeChannelMapping(std::uint16_t lod, std::uint16_t index)`
- L550 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearAnimatedMapNames()`
- L555 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapName(std::uint16_t index, const char* name)`
- L560 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearAnimatedMapIndices()`
- L565 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapIndices(std::uint16_t index, const std::uint16_t* animatedMapIndices, std::uint16_t count)`
- L573 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODAnimatedMapMappings()`
- L578 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODAnimatedMapMapping(std::uint16_t lod, std::uint16_t index)`
- L583 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMeshNames()`
- L588 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMeshName(std::uint16_t index, const char* name)`
- L593 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMeshIndices()`
- L598 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMeshIndices(std::uint16_t index, const std::uint16_t* meshIndices, std::uint16_t count)`
- L604 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODMeshMappings()`
- L609 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODMeshMapping(std::uint16_t lod, std::uint16_t index)`
- L614 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMeshBlendShapeChannelMappings()`
- L619 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMeshBlendShapeChannelMapping(std::uint32_t index, std::uint16_t meshIndex, std::uint16_t blendShapeChannelIndex)`
- L626 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeutralJointTranslations(const Vector3* translations, std::uint16_t count)`
- L631 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeutralJointRotations(const Vector3* rotations, std::uint16_t count)`
- L636 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIToRawInputIndices(const std::uint16_t* inputIndices, std::uint16_t count)`
- L641 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIToRawOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count)`
- L646 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIToRawFromValues(const float* fromValues, std::uint16_t count)`
- L651 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIToRawToValues(const float* toValues, std::uint16_t count)`
- L656 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIToRawSlopeValues(const float* slopeValues, std::uint16_t count)`
- L661 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setGUIToRawCutValues(const float* cutValues, std::uint16_t count)`
- L666 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setPSDCount(std::uint16_t count)`
- L671 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setPSDRowIndices(const std::uint16_t* rowIndices, std::uint16_t count)`
- L676 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setPSDColumnIndices(const std::uint16_t* columnIndices, std::uint16_t count)`
- L681 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setPSDValues(const float* weights, std::uint16_t count)`
- L686 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointRowCount(std::uint16_t rowCount)`
- L691 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointColumnCount(std::uint16_t columnCount)`
- L696 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearJointGroups()`
- L701 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteJointGroup(std::uint16_t jointGroupIndex)`
- L709 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointGroupLODs(std::uint16_t jointGroupIndex, const std::uint16_t* lods, std::uint16_t count)`
- L717 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointGroupInputIndices(std::uint16_t jointGroupIndex, const std::uint16_t* inputIndices, std::uint16_t count)`
- L725 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointGroupOutputIndices(std::uint16_t jointGroupIndex, const std::uint16_t* outputIndices, std::uint16_t count)`
- L733 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointGroupValues(std::uint16_t jointGroupIndex, const float* values, std::uint32_t count)`
- L741 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointGroupJointIndices(std::uint16_t jointGroupIndex, const std::uint16_t* jointIndices, std::uint16_t count)`
- L749 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeChannelLODs(const std::uint16_t* lods, std::uint16_t count)`
- L754 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeChannelInputIndices(const std::uint16_t* inputIndices, std::uint16_t count)`
- L759 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeChannelOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count)`
- L764 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapLODs(const std::uint16_t* lods, std::uint16_t count)`
- L769 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapInputIndices(const std::uint16_t* inputIndices, std::uint16_t count)`
- L774 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count)`
- L779 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapFromValues(const float* fromValues, std::uint16_t count)`
- L784 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapToValues(const float* toValues, std::uint16_t count)`
- L789 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapSlopeValues(const float* slopeValues, std::uint16_t count)`
- L794 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setAnimatedMapCutValues(const float* cutValues, std::uint16_t count)`
- L799 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMeshes()`
- L804 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteMesh(std::uint16_t meshIndex)`
- L812 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setVertexPositions(std::uint16_t meshIndex, const Position* positions, std::uint32_t count)`
- L818 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setVertexTextureCoordinates(std::uint16_t meshIndex, const TextureCoordinate* textureCoordinates, std::uint32_t count)`
- L833 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setVertexNormals(std::uint16_t meshIndex, const Normal* normals, std::uint32_t count)`
- L839 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setVertexLayouts(std::uint16_t meshIndex, const VertexLayout* layouts, std::uint32_t count)`
- L854 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearFaceVertexLayoutIndices(std::uint16_t meshIndex)`
- L861 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex, const std::uint32_t* layoutIndices, std::uint32_t count)`
- L871 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMaximumInfluencePerVertex(std::uint16_t meshIndex, std::uint16_t maxInfluenceCount)`
- L877 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearSkinWeights(std::uint16_t meshIndex)`
- L884 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex, const float* weights, std::uint16_t count)`
- L894 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex, const std::uint16_t* jointIndices, std::uint16_t count)`
- L904 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearBlendShapeTargets(std::uint16_t meshIndex)`
- L911 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint16_t blendShapeChannelIndex)`
- L920 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeTargetDeltas(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, const Delta* deltas, std::uint32_t count)`
- L930 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, const std::uint32_t* vertexIndices, std::uint32_t count)`
- L940 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMLControlNames()`
- L945 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLControlName(std::uint16_t index, const char* name)`
- L950 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearNeuralNetworks()`
- L955 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearNeuralNetworkIndices()`
- L960 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkIndices(std::uint16_t index, const std::uint16_t* netIndices, std::uint16_t count)`
- L968 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODNeuralNetworkMappings()`
- L973 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODNeuralNetworkMapping(std::uint16_t lod, std::uint16_t index)`
- L978 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMeshRegionNames()`
- L983 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMeshRegionNames(std::uint16_t meshIndex)`
- L990 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex, const char* name)`
- L996 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearNeuralNetworkIndicesPerMeshRegion()`
- L1001 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex, const std::uint16_t* netIndices, std::uint16_t count)`
- L1011 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteNeuralNetwork(std::uint16_t netIndex)`
- L1019 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkInputIndices(std::uint16_t netIndex, const std::uint16_t* inputIndices, std::uint16_t count)`
- L1027 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkOutputIndices(std::uint16_t netIndex, const std::uint16_t* outputIndices, std::uint16_t count)`
- L1035 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearNeuralNetworkLayers(std::uint16_t netIndex)`
- L1041 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex, ActivationFunction function)`
- L1050 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex, const float* activationFunctionParameters, std::uint16_t count)`
- L1060 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex, const float* biases, std::uint32_t count)`
- L1070 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex, const float* weights, std::uint32_t count)`
- L1080 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearRBFPoses()`
- L1086 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFPoseName(std::uint16_t poseIndex, const char* name)`
- L1092 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFPoseScale(std::uint16_t poseIndex, float scale)`
- L1098 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearRBFPoseControlNames()`
- L1103 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFPoseControlName(std::uint16_t poseControlIndex, const char* name)`
- L1108 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFPoseInputControlIndices(std::uint16_t poseIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount)`
- L1116 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFPoseOutputControlIndices(std::uint16_t poseIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount)`
- L1124 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFPoseOutputControlWeights(std::uint16_t poseIndex, const float* controlWeights, std::uint16_t controlWeightCount)`
- L1132 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearRBFSolvers()`
- L1137 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearRBFSolverIndices()`
- L1142 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverIndices(std::uint16_t index, const std::uint16_t* solverIndices, std::uint16_t count)`
- L1150 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODRBFSolverMappings()`
- L1155 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODRBFSolverMapping(std::uint16_t lod, std::uint16_t index)`
- L1160 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverName(std::uint16_t solverIndex, const char* name)`
- L1166 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverRawControlIndices(std::uint16_t solverIndex, const std::uint16_t* rawControlIndices, std::uint16_t count)`
- L1174 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverPoseIndices(std::uint16_t solverIndex, const std::uint16_t* poseIndices, std::uint16_t count)`
- L1182 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverRawControlValues(std::uint16_t solverIndex, const float* values, std::uint16_t count)`
- L1190 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverType(std::uint16_t solverIndex, RBFSolverType type)`
- L1196 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverRadius(std::uint16_t solverIndex, float radius)`
- L1202 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverAutomaticRadius(std::uint16_t solverIndex, AutomaticRadius automaticRadius)`
- L1208 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverWeightThreshold(std::uint16_t solverIndex, float weightThreshold)`
- L1214 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverDistanceMethod(std::uint16_t solverIndex, RBFDistanceMethod distanceMethod)`
- L1220 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverNormalizeMethod(std::uint16_t solverIndex, RBFNormalizeMethod normalizeMethod)`
- L1226 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverFunctionType(std::uint16_t solverIndex, RBFFunctionType functionType)`
- L1232 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRBFSolverTwistAxis(std::uint16_t solverIndex, TwistAxis twistAxis)`
- L1238 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearJointRepresentations()`
- L1243 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointTranslationRepresentation(std::uint16_t jointIndex, TranslationRepresentation representation)`
- L1250 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointRotationRepresentation(std::uint16_t jointIndex, RotationRepresentation representation)`
- L1257 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointScaleRepresentation(std::uint16_t jointIndex, ScaleRepresentation representation)`
- L1263 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearTwists()`
- L1268 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteTwist(std::uint16_t twistIndex)`
- L1276 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setTwistSetupTwistAxis(std::uint16_t twistIndex, TwistAxis twistAxis)`
- L1282 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setTwistInputControlIndices(std::uint16_t twistIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount)`
- L1290 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setTwistOutputJointIndices(std::uint16_t twistIndex, const std::uint16_t* jointIndices, std::uint16_t jointIndexCount)`
- L1298 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setTwistBlendWeights(std::uint16_t twistIndex, const float* blendWeights, std::uint16_t blendWeightCount)`
- L1306 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearSwings()`
- L1311 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteSwing(std::uint16_t swingIndex)`
- L1319 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setSwingSetupTwistAxis(std::uint16_t swingIndex, TwistAxis twistAxis)`
- L1325 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setSwingInputControlIndices(std::uint16_t swingIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount)`
- L1333 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setSwingOutputJointIndices(std::uint16_t swingIndex, const std::uint16_t* jointIndices, std::uint16_t jointIndexCount)`
- L1341 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setSwingBlendWeights(std::uint16_t swingIndex, const float* blendWeights, std::uint16_t blendWeightCount)`
- L1349 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMLExtData()`
- L1358 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMLOperationSets(std::uint16_t mlTypeIndex)`
- L1365 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMLOperations(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex)`
- L1375 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, MachineLearnedBehaviorOperationType operationType)`
- L1386 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint32_t* parameters, std::uint16_t count)`
- L1398 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint16_t* indices, std::uint16_t count)`
- L1410 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint16_t* indices, std::uint16_t count)`
- L1422 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMLOperationIndicesAndLODMappings()`
- L1429 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearMLOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex)`
- L1438 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearLODMLOperationMappings(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex)`
- L1447 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t index, const std::uint16_t* mlOperationIndices, std::uint16_t count)`
- L1459 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setLODMLOperationMapping(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod, std::uint16_t index)`
- L1469 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLJointsParameterKeys(const std::uint16_t* parameterKeys, std::uint16_t count)`
- L1474 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLJointsParameterValues(const std::uint16_t* parameterValues, std::uint16_t count)`
- L1479 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLJointsInputIndices(const std::uint16_t* inputIndices, std::uint16_t count)`
- L1484 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setMLJointsOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count)`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace dna`
- L28 _function_ `ensureHasSize(TContainer& target, std::size_t size)` (scope `dna`)
- L44 _function_ `template<class TContainer, typename U> typename std::enable_if<std::is_integral<U>::value, typename TContainer::value_type&>::type getAt(TContainer& target, U index)` (scope `dna`)
- L50 _function_ `template<class TContainer, typename TSize, typename TValue> typename std::enable_if<std::is_integral<TSize>::value>::type setAt(TContainer& target, TSize index, const TValue& value)` (scope `dna`)
- L388 _typedef_ `using CharStringPair = std::tuple<String<char>, String<char>>;` (scope `dna::WriterImpl::setMetaData`)
- L389 _function_ `auto it = std::find_if(dna.descriptor.metadata.begin(), dna.descriptor.metadata.end(), [&key](const CharStringPair& kv) { auto& k = std::get<0>(kv); return (std::strlen(key) == k.size() && std::strncmp(k.data(), key, k.size()) == 0); });` (scope `dna::WriterImpl::setMetaData`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/filters/AnimatedMapFilter.h` (Private)


#### class `dna::AnimatedMapFilter`  
`class AnimatedMapFilter`  
_L13-24_
- L15 _public prototype_ `explicit AnimatedMapFilter(MemoryResource* memRes_);`
- L16 _public prototype_ `void configure(std::uint16_t animatedMapCount, UnorderedSet<std::uint16_t> allowedAnimatedMapIndices);`
- L17 _public prototype_ `void apply(RawDefinition& dest);`
- L18 _public prototype_ `bool passes(std::uint16_t index) const;`
- L21 _private member_ `MemoryResource* memRes;`
- L22 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L23 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/filters/BlendShapeFilter.h` (Private)


#### class `dna::BlendShapeFilter`  
`class BlendShapeFilter`  
_L14-27_
- L16 _public prototype_ `explicit BlendShapeFilter(MemoryResource* memRes_);`
- L17 _public prototype_ `void configure(std::uint16_t blendShapeCount, UnorderedSet<std::uint16_t> allowedBlendShapeIndices);`
- L18 _public prototype_ `void apply(RawDefinition& dest);`
- L19 _public prototype_ `void apply(RawMesh& dest);`
- L20 _public prototype_ `bool passes(std::uint16_t index) const;`
- L21 _public prototype_ `std::uint16_t remapped(std::uint16_t index) const;`
- L24 _private member_ `MemoryResource* memRes;`
- L25 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L26 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/filters/JointFilter.h` (Private)


#### class `dna::JointFilter`  
`class JointFilter`  
_L19-45_
- L27 _public prototype_ `explicit JointFilter(MemoryResource* memRes_);`
- L28 _public prototype_ `void configure(std::uint16_t jointCount, UnorderedSet<std::uint16_t> allowedJointIndices, Option option_ = Option::All);`
- L29 _public prototype_ `void apply(RawDefinition& dest);`
- L30 _public prototype_ `void apply(RawBehavior& dest);`
- L31 _public prototype_ `void apply(RawVertexSkinWeights& dest);`
- L32 _public prototype_ `void apply(RawJointBehaviorMetadata& dest);`
- L33 _public prototype_ `void apply(RawTwistSwingBehavior& dest);`
- L34 _public prototype_ `void apply(RawMachineLearnedBehaviorJoints& dest);`
- L35 _public prototype_ `bool passes(std::uint16_t index) const;`
- L36 _public prototype_ `std::uint16_t remapped(std::uint16_t oldIndex) const;`
- L37 _public prototype_ `std::uint16_t filteredJointCount() const;`
- L40 _private member_ `MemoryResource* memRes;`
- L41 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L42 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`
- L43 _private member_ `Option option;`
- L44 _private member_ `std::uint16_t rootJointIndex;`

#### enum `dna::JointFilter::Option`  
`enum class Option`  
_L21-24_
- L22 _public enumerator_ `All`
- L23 _public enumerator_ `AnimationOnly`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/filters/MeshFilter.h` (Private)


#### class `dna::MeshFilter`  
`class MeshFilter`  
_L14-26_
- L16 _public prototype_ `explicit MeshFilter(MemoryResource* memRes_);`
- L17 _public prototype_ `void configure(std::uint16_t meshCount, UnorderedSet<std::uint16_t> allowedMeshIndices);`
- L18 _public prototype_ `void apply(RawDefinition& dest);`
- L19 _public prototype_ `void apply(RawMachineLearnedBehavior& dest);`
- L20 _public prototype_ `bool passes(std::uint16_t index) const;`
- L23 _private member_ `MemoryResource* memRes;`
- L24 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L25 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/filters/Remap.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dna`
- L11 _function_ `template<typename T> inline void remap(T originalCount, const UnorderedSet<T>& keptIndices, UnorderedMap<T, T>& mapping)` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/stream/BinaryStreamReaderImpl.h` (Private)


#### class `dna::BinaryStreamReaderImpl`  
`class BinaryStreamReaderImpl : public ReaderImpl<BinaryStreamReader>, private StreamReaderStatus`  
_L15-28_
- inherits: `ReaderImpl<BinaryStreamReader>,StreamReaderStatus`
- L17 _public prototype_ `BinaryStreamReaderImpl(BoundedIOStream* stream_, const Configuration& config_, MemoryResource* memRes_);`
- L19 _public prototype_ `void unload(DataLayer layer) override;`
- L20 _public prototype_ `void read() override;`
- L21 _public prototype_ `bool isLODConstrained() const;`
- L24 _private member_ `BoundedIOStream* stream;`
- L25 _private member_ `FilteredBinaryInputArchive archive;`
- L26 _private member_ `Configuration config;`
- L27 _private member_ `bool lodConstrained;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/stream/BinaryStreamWriterImpl.h` (Private)


#### class `dna::BinaryStreamWriterImpl`  
`class BinaryStreamWriterImpl : public WriterImpl<BinaryStreamWriter>`  
_L16-31_
- inherits: `WriterImpl<BinaryStreamWriter>`
- L18 _public prototype_ `BinaryStreamWriterImpl(BoundedIOStream* stream_, MemoryResource* memRes_);`
- L20 _public prototype_ `void write() override;`
- L23 _public prototype_ `void setFrom(const BinaryStreamReader* source, DataLayer layer, UnknownLayerPolicy policy, MemoryResource* memRes_) override;`
- L25 _public prototype_ `void setFrom(const JSONStreamReader* source, DataLayer layer, UnknownLayerPolicy policy, MemoryResource* memRes_) override;`
- L29 _private member_ `BoundedIOStream* stream;`
- L30 _private member_ `terse::BinaryOutputArchive<BoundedIOStream> archive;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/stream/FilteredBinaryInputArchive.h` (Private)


#### class `dna::FilteredBinaryInputArchive`  
`class FilteredBinaryInputArchive final : public AnimatedMapFilter, public BlendShapeFilter, public JointFilter, public MeshFilter, public terse::ExtendableBinaryInputArchive<FilteredBinaryInputArchive, BoundedIOStream, std::uint32_t, std::uint32_t, terse::Endianness::Network>`  
_L20-115_
- inherits: `AnimatedMapFilter,BlendShapeFilter,JointFilter,MeshFilter,terse::ExtendableBinaryInputArchive<FilteredBinaryInputArchive,BoundedIOStream,std::uint32_t,std::uint32_t,terse::Endianness::Network>`
- L30 _private typedef_ `using BaseArchive = terse::ExtendableBinaryInputArchive<FilteredBinaryInputArchive, BoundedIOStream, std::uint32_t, std::uint32_t, terse::Endianness::Network>;`
- L39 _public prototype_ `FilteredBinaryInputArchive(BoundedIOStream* stream_, DataLayer layer_, LODConstraint&& lodConstraint, MemoryResource* memRes_);`
- L44 _public prototype_ `bool isOk();`
- L46 _public prototype_ `std::size_t boundSize(std::size_t size);`
- L49 _private prototype_ `void process(RawDescriptor& dest);`
- L50 _private prototype_ `void process(RawDefinition& dest);`
- L53 _private function_ `template<typename AnyVersion> void process(terse::Versioned<RawBehavior, AnyVersion>& dest)`
- L64 _private function_ `template<typename AnyVersion> void process(terse::Versioned<RawBehavior, AnyVersion>&& dest)`
- L68 _private prototype_ `void process(RawControls& dest);`
- L69 _private prototype_ `void process(RawJoints& dest);`
- L70 _private prototype_ `void process(RawBlendShapeChannels& dest);`
- L71 _private prototype_ `void process(RawAnimatedMaps& dest);`
- L72 _private prototype_ `void process(terse::Versioned<RawGeometry, terse::Version<FileVersion::v21>>& dest);`
- L73 _private prototype_ `void process(terse::Versioned<RawGeometry, terse::Version<FileVersion::v21>>&& dest);`
- L74 _private prototype_ `void process(terse::Versioned<RawGeometry, terse::Version<FileVersion::v22>>& dest);`
- L75 _private prototype_ `void process(terse::Versioned<RawGeometry, terse::Version<FileVersion::v22>>&& dest);`
- L78 _private function_ `template<typename AnyVersion> void process(terse::Versioned<RawGeometry, AnyVersion>& dest)`
- L83 _private function_ `template<typename AnyVersion> void process(terse::Versioned<RawGeometry, AnyVersion>&& dest)`
- L87 _private prototype_ `void process(Vector<RawBlendShapeTarget>& dest);`
- L88 _private prototype_ `void process(RawVertexSkinWeights& dest);`
- L89 _private prototype_ `void process(RawMachineLearnedBehavior& dest);`
- L90 _private prototype_ `void process(RawRBFBehavior& dest);`
- L91 _private prototype_ `void process(RawRBFBehaviorExt& dest);`
- L92 _private prototype_ `void process(RawJointBehaviorMetadata& dest);`
- L93 _private prototype_ `void process(RawTwistSwingBehavior& dest);`
- L94 _private prototype_ `void process(RawMachineLearnedBehaviorExt& dest);`
- L96 _private prototype_ `void process(DNA& dest);`
- L97 _private prototype_ `void removeUnreferencedBlendShapes(DNA& dest);`
- L100 _private function_ `template<typename... Args> void process(Args&&... args)`
- L105 _private prototype_ `template<typename TContainer> void processSubset(TContainer& dest, std::size_t offset, std::size_t size);`
- L108 _private member_ `BoundedIOStream* stream;`
- L109 _private member_ `MemoryResource* memRes;`
- L110 _private member_ `DataLayerBitmask layerBitmask;`
- L111 _private member_ `LODConstraint lodConstraint;`
- L112 _private member_ `Vector<bool> loadedControls;`
- L113 _private member_ `std::uint16_t unconstrainedLODCount;`
- L114 _private member_ `bool malformed;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/stream/JSONStreamReaderImpl.h` (Private)


#### class `dna::JSONStreamReaderImpl`  
`class JSONStreamReaderImpl : public ReaderImpl<JSONStreamReader>, private StreamReaderStatus`  
_L18-28_
- inherits: `ReaderImpl<JSONStreamReader>,StreamReaderStatus`
- L20 _public prototype_ `JSONStreamReaderImpl(BoundedIOStream* stream_, MemoryResource* memRes_);`
- L22 _public prototype_ `void unload(DataLayer layer) override;`
- L23 _public prototype_ `void read() override;`
- L26 _private member_ `BoundedIOStream* stream;`
- L27 _private member_ `terse::JSONInputArchive<BoundedIOStream> archive;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/stream/JSONStreamWriterImpl.h` (Private)


#### class `dna::JSONStreamWriterImpl`  
`class JSONStreamWriterImpl : public WriterImpl<JSONStreamWriter>`  
_L19-32_
- inherits: `WriterImpl<JSONStreamWriter>`
- L21 _public prototype_ `JSONStreamWriterImpl(BoundedIOStream* stream_, std::uint32_t indentWidth, MemoryResource* memRes_);`
- L23 _public prototype_ `void write() override;`
- L26 _public prototype_ `void setFrom(const BinaryStreamReader* source, DataLayer layer, UnknownLayerPolicy policy, MemoryResource* memRes_) override;`
- L27 _public prototype_ `void setFrom(const JSONStreamReader* source, DataLayer layer, UnknownLayerPolicy policy, MemoryResource* memRes_) override;`
- L30 _private member_ `BoundedIOStream* stream;`
- L31 _private member_ `terse::JSONOutputArchive<BoundedIOStream> archive;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/stream/StreamReaderStatus.h` (Private)


#### struct `dna::StreamReaderStatus`  
`struct StreamReaderStatus`  
_L9-11_
- L10 _public member_ `static sc::StatusProvider status;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/types/CoordinateSystemConverter.h` (Private)


#### class `dna::CoordinateSystemConverter`  
`class CoordinateSystemConverter`  
_L11-73_
- L13 _public prototype_ `CoordinateSystemConverter(const CoordinateSystem& dstCoordinateSystem_, RotationSequence dstRotationSequence_, const RotationSign& dstRotationSigns_, FaceWindingOrder dstFaceWindingOrder_, MemoryResource* memRes_);`
- L18 _public prototype_ `void convert(DNA& dna);`
- L21 _private prototype_ `void convertNeutralJointTranslations(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L26 _private prototype_ `void convertNeutralJointRotations(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L31 _private prototype_ `void convertJointDeltas(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L36 _private prototype_ `void convertVertexPositions(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L41 _private prototype_ `void convertVertexNormals(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L46 _private prototype_ `void convertBlendShapeDeltas(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L51 _private prototype_ `void convertRBFSolverRawControlValues(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L56 _private prototype_ `void convertTwistAxes(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L61 _private prototype_ `void convertFaceWinding(DNA& dna, const CoordinateSystem& srcCoordinateSystem, RotationSequence srcRotationSequence, const RotationSign& srcRotationSigns, FaceWindingOrder srcFaceWindingOrder);`
- L68 _private member_ `CoordinateSystem dstCoordinateSystem;`
- L69 _private member_ `RotationSequence dstRotationSequence;`
- L70 _private member_ `RotationSign dstRotationSigns;`
- L71 _private member_ `FaceWindingOrder dstFaceWindingOrder;`
- L72 _private member_ `MemoryResource* memRes;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/types/Limits.h` (Private)


#### struct `dna::LODLimits`  
`struct LODLimits`  
_L9-22_
- L10 _public function_ `static constexpr std::uint16_t max()`
- L14 _public function_ `static constexpr std::uint16_t min()`
- L18 _public function_ `static constexpr std::uint16_t count()`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/utils/Extd.h` (Private)


#### enum `extd::impl::LUTStrategy`  
`enum class LUTStrategy`  
_L84-87_
- L85 _public enumerator_ `ByValue`
- L86 _public enumerator_ `ByPosition`

#### class `extd::impl::LUTFilter`  
`template<typename TLUT, LUTStrategy Strategy> class LUTFilter`  
_L90-110_
- L92 _public function_ `explicit LUTFilter(const TLUT& lut_) : lut`
- L97 _public function_ `template<typename T, LUTStrategy ChosenStrategy = Strategy> typename std::enable_if<ChosenStrategy == LUTStrategy::ByValue, bool>::type operator()(const T& value, std::size_t )`
- L103 _public function_ `template<typename T, LUTStrategy ChosenStrategy = Strategy> typename std::enable_if<ChosenStrategy == LUTStrategy::ByPosition, bool>::type operator()(const T& , std::size_t index)`
- L109 _private member_ `const TLUT& lut;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define EXTD_GUARD`
- L28 _namespace_ `namespace extd`
- L31 _function_ `template<typename T> inline T clamp(T value, T low, T high)` (scope `extd`)
- L36 _function_ `template<typename T> inline T roundUp(T number, T multiple)` (scope `extd`)
- L41 _function_ `template<typename T> inline T interpolate(T a, T b, T weight)` (scope `extd`)
- L46 _function_ `template<class TInputIterator, class T> inline bool contains(TInputIterator first, TInputIterator last, const T& value)` (scope `extd`)
- L51 _function_ `template<class TContainer, class T> inline bool contains(const TContainer& container, const T& value)` (scope `extd`)
- L56 _function_ `template<class T> inline bool contains(const std::set<T>& container, const T& value)` (scope `extd`)
- L61 _function_ `template<class T, class Predicate, typename... Args> inline void filter(std::vector<T, Args...>& source, Predicate pred)` (scope `extd`)
- L64 _function_ `source.erase(std::remove_if(std::begin(source), std::end(source), [&source, &pred](const T& value) { const auto index = static_cast<std::size_t>(&value - &(source.front())); return !pred(value, index); }), source.end());` (scope `extd::filter`)
- L72 _function_ `template<class TContainer, class Predicate, typename... Args> inline void filter(TContainer& source, Predicate pred)` (scope `extd`)
- L73 _typedef_ `using value_type = typename TContainer::value_type;` (scope `extd::filter`)
- L74 _function_ `auto newEnd = std::remove_if(std::begin(source), std::end(source), [&source, &pred](const value_type& value) { const auto index = static_cast<std::size_t>(&value - source.data()); return !pred(value, index); });` (scope `extd::filter`)
- L82 _namespace_ `namespace impl` (scope `extd`)
- L115 _function_ `template<typename TLookUpTable> inline impl::LUTFilter<TLookUpTable, impl::LUTStrategy::ByValue> byValue(const TLookUpTable& lookUpTable)` (scope `extd`)
- L120 _function_ `template<typename TLookUpTable> inline impl::LUTFilter<TLookUpTable, impl::LUTStrategy::ByPosition> byPosition(const TLookUpTable& lookUpTable)` (scope `extd`)
- L125 _function_ `template<class TContainer, class TComparator> inline typename TContainer::value_type minOf(const TContainer& container, TComparator&& comparator)` (scope `extd`)
- L126 _typedef_ `using ValueType = typename TContainer::value_type;` (scope `extd::minOf`)
- L132 _function_ `template<class TContainer> inline typename TContainer::value_type minOf(const TContainer& container)` (scope `extd`)
- L134 _function_ `const auto compare = [](const ValueType& lhs, const ValueType& rhs)` (scope `extd::minOf`)
- L139 _function_ `template<class TContainer, class TComparator> inline typename TContainer::value_type maxOf(const TContainer& container, TComparator&& comparator)` (scope `extd`)
- L140 _typedef_ `using ValueType = typename TContainer::value_type;` (scope `extd::maxOf`)
- L146 _function_ `template<class TContainer> inline typename TContainer::value_type maxOf(const TContainer& container)` (scope `extd`)
- L148 _function_ `const auto compare = [](const ValueType& lhs, const ValueType& rhs)` (scope `extd::maxOf`)
- L153 _function_ `template<class TSource, class TDestination> inline void copy(const TSource& source, TDestination& destination)` (scope `extd`)
- L158 _function_ `template<class T, class U> inline void copy(av::ArrayView<T> source, av::ArrayView<U> destination)` (scope `extd`)
- L173 _function_ `template<class TIterator, typename TDistance> TIterator advanced(TIterator source, TDistance distance)` (scope `extd`)
- L179 _function_ `template<class TIterator, class Predicate> typename std::iterator_traits<TIterator>::difference_type advanceWhile(TIterator& it, const TIterator& end, Predicate pred)` (scope `extd`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/utils/Macros.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define FORCE_INLINE __forceinline`
- L9 _macro_ `#define FORCE_INLINE inline __attribute__((always_inline))`
- L15 _macro_ `#define ASSUME_TRUE(condition) __assume(condition)`
- L17 _macro_ `#define ASSUME_TRUE(condition) \`
- L26 _macro_ `#define UNUSED(x) static_cast<void>(x)`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/dna/utils/ScopedEnumEx.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`
- L10 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator&(TEnum lhs, TEnum rhs)` (scope `dna`)
- L11 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dna::operator &`)
- L16 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator|(TEnum lhs, TEnum rhs)` (scope `dna`)
- L17 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dna::operator |`)
- L22 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator^(TEnum lhs, TEnum rhs)` (scope `dna`)
- L23 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dna::operator ^`)
- L28 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator~(TEnum value)` (scope `dna`)
- L29 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dna::operator ~`)
- L34 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator&=(TEnum& lhs, TEnum rhs)` (scope `dna`)
- L39 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator|=(TEnum& lhs, TEnum rhs)` (scope `dna`)
- L44 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator^=(TEnum& lhs, TEnum rhs)` (scope `dna`)
- L49 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, bool>::type contains(TEnum lhs, TEnum rhs)` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/TypeDefs.h` (Private)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace tdm`
- L23 _macro_ `#define TDM_FMAT3_SERIALIZER_DEFINED`
- L30 _function_ `template<typename Archive> void load(Archive& archive, tdm::fmat3& value)` (scope `tdm`)
- L32 _function_ `value.apply([archive](tdm::fmat3::row_type& row, tdm::dim_t ri) mutable { row.apply([archive, ri](tdm::fmat3::value_type& v, tdm::dim_t ci) mutable { RL_UNUSED(ri); RL_UNUSED(ci); archive(v); }); });` (scope `tdm::load`)
- L33 _function_ `row.apply([archive, ri](tdm::fmat3::value_type& v, tdm::dim_t ci) mutable { RL_UNUSED(ri); RL_UNUSED(ci); archive(v); });` (scope `tdm::load::__anon28ef67ae0102`)
- L42 _function_ `template<typename Archive> void save(Archive& archive, tdm::fmat3& value)` (scope `tdm`)
- L44 _function_ `value.apply([archive](tdm::fmat3::row_type& row, tdm::dim_t ri) mutable { row.apply([archive, ri](tdm::fmat3::value_type& v, tdm::dim_t ci) mutable { RL_UNUSED(ri); RL_UNUSED(ci); archive(v); }); });` (scope `tdm::save`)
- L45 _function_ `row.apply([archive, ri](tdm::fmat3::value_type& v, tdm::dim_t ci) mutable { RL_UNUSED(ri); RL_UNUSED(ci); archive(v); });` (scope `tdm::save::__anon28ef67ae0302`)
- L60 _macro_ `#define TDM_COORD_SYS_SERIALIZER_DEFINED`
- L63 _function_ `template<typename Archive> void load(Archive& archive, tdm::coord_sys& value)` (scope `tdm`)
- L80 _function_ `template<typename Archive> void save(Archive& archive, tdm::coord_sys& value)` (scope `tdm`)
- L94 _macro_ `#define TDM_ROT_SEQ_SERIALIZER_DEFINED`
- L97 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L105 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L113 _macro_ `#define TDM_ROT_SIGN_SERIALIZER_DEFINED`
- L116 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L133 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L147 _namespace_ `namespace rl4`
- L151 _variable_ `static constexpr std::size_t cacheLineAlignment = 64ul;` (scope `rl4`)
- L154 _typedef_ `template<typename T> using AlignedAllocator = PolyAllocator<T, cacheLineAlignment, AlignedMemoryResource>;` (scope `rl4`)
- L157 _typedef_ `template<typename T> using AlignedVector = Vector<T, AlignedAllocator<T>>;` (scope `rl4`)
- L160 _typedef_ `template<typename T> using AlignedMatrix = Vector<AlignedVector<T>>;` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMaps.h` (Private)


#### class `rl4::AnimatedMaps`  
`class AnimatedMaps`  
_L14-27_
- L16 _public typedef_ `using Pointer = UniqueInstance<AnimatedMaps>::PointerType;`
- L19 _protected prototype_ `virtual ~AnimatedMaps();`
- L22 _public prototype_ `virtual AnimatedMapsOutputInstance::Pointer createInstance(MemoryResource* memRes) const = 0;`
- L23 _public prototype_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t ) const = 0;`
- L24 _public prototype_ `virtual void calculate(const ControlsInputInstance* inputs, AnimatedMapsOutputInstance* outputs, std::uint16_t lod) const = 0;`
- L25 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L26 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMapsFactory.h` (Private)


#### struct `rl4::AnimatedMapsFactory`  
`struct AnimatedMapsFactory`  
_L14-18_
- L16 _public prototype_ `create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, Controls* controls, MemoryResource* memRes);`
- L17 _public prototype_ `static AnimatedMaps::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMapsImpl.h` (Private)


#### class `rl4::AnimatedMapsImpl`  
`class AnimatedMapsImpl : public AnimatedMaps`  
_L16-31_
- inherits: `AnimatedMaps`
- L18 _public prototype_ `AnimatedMapsImpl(Vector<std::uint16_t>&& lods_, ConditionalTable&& conditionals_, AnimatedMapsOutputInstance::Factory instanceFactory_);`
- L21 _public prototype_ `AnimatedMapsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L22 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override;`
- L23 _public prototype_ `void calculate(const ControlsInputInstance* inputs, AnimatedMapsOutputInstance* outputs, std::uint16_t lod) const override;`
- L24 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L25 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L28 _private member_ `Vector<std::uint16_t> lods;`
- L29 _private member_ `ConditionalTable conditionals;`
- L30 _private member_ `AnimatedMapsOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMapsImplOutputInstance.h` (Private)


#### class `rl4::AnimatedMapsImplOutputInstance`  
`class AnimatedMapsImplOutputInstance : public AnimatedMapsOutputInstance`  
_L12-20_
- inherits: `AnimatedMapsOutputInstance`
- L14 _public prototype_ `AnimatedMapsImplOutputInstance(std::uint16_t animatedMapCount, MemoryResource* memRes);`
- L15 _public prototype_ `ArrayView<float> getOutputBuffer() override;`
- L16 _public prototype_ `void resetOutputBuffer() override;`
- L19 _private member_ `Vector<float> outputBuffer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMapsNull.h` (Private)


#### class `rl4::AnimatedMapsNull`  
`class AnimatedMapsNull : public AnimatedMaps`  
_L16-25_
- inherits: `AnimatedMaps`
- L18 _public prototype_ `AnimatedMapsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L19 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t ) const override;`
- L20 _public prototype_ `void calculate(const ControlsInputInstance* , AnimatedMapsOutputInstance* , std::uint16_t ) const override;`
- L23 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& ) override;`
- L24 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& ) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMapsNullOutputInstance.h` (Private)


#### class `rl4::AnimatedMapsNullOutputInstance`  
`class AnimatedMapsNullOutputInstance : public AnimatedMapsOutputInstance`  
_L10-14_
- inherits: `AnimatedMapsOutputInstance`
- L12 _public prototype_ `ArrayView<float> getOutputBuffer() override;`
- L13 _public prototype_ `void resetOutputBuffer() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/animatedmaps/AnimatedMapsOutputInstance.h` (Private)


#### class `rl4::AnimatedMapsOutputInstance`  
`class AnimatedMapsOutputInstance`  
_L18-27_
- L20 _public typedef_ `using Pointer = UniqueInstance<AnimatedMapsOutputInstance>::PointerType;`
- L21 _public typedef_ `using Factory = std::function<Pointer(MemoryResource*)>;`
- L24 _public prototype_ `virtual ~AnimatedMapsOutputInstance();`
- L25 _public prototype_ `virtual ArrayView<float> getOutputBuffer() = 0;`
- L26 _public prototype_ `virtual void resetOutputBuffer() = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapes.h` (Private)


#### class `rl4::BlendShapes`  
`class BlendShapes`  
_L14-27_
- L16 _public typedef_ `using Pointer = UniqueInstance<BlendShapes>::PointerType;`
- L19 _protected prototype_ `virtual ~BlendShapes();`
- L22 _public prototype_ `virtual BlendShapesOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const = 0;`
- L23 _public prototype_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const = 0;`
- L24 _public prototype_ `virtual void calculate(const ControlsInputInstance* inputs, BlendShapesOutputInstance* outputs, std::uint16_t lod) const = 0;`
- L25 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L26 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapesFactory.h` (Private)


#### struct `rl4::BlendShapesFactory`  
`struct BlendShapesFactory`  
_L14-18_
- L16 _public prototype_ `create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, Controls* controls, MemoryResource* memRes);`
- L17 _public prototype_ `static BlendShapes::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapesImpl.h` (Private)


#### class `rl4::BlendShapesImpl`  
`class BlendShapesImpl : public BlendShapes`  
_L15-32_
- inherits: `BlendShapes`
- L17 _public prototype_ `BlendShapesImpl(Vector<std::uint16_t>&& lods_, Vector<std::uint16_t>&& inputIndices_, Vector<std::uint16_t>&& outputIndices_, BlendShapesOutputInstance::Factory instanceFactory_);`
- L21 _public prototype_ `BlendShapesOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L22 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override;`
- L23 _public prototype_ `void calculate(const ControlsInputInstance* inputs, BlendShapesOutputInstance* outputs, std::uint16_t lod) const override;`
- L24 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L25 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L28 _private member_ `Vector<std::uint16_t> lods;`
- L29 _private member_ `Vector<std::uint16_t> inputIndices;`
- L30 _private member_ `Vector<std::uint16_t> outputIndices;`
- L31 _private member_ `BlendShapesOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapesImplOutputInstance.h` (Private)


#### class `rl4::BlendShapesImplOutputInstance`  
`class BlendShapesImplOutputInstance : public BlendShapesOutputInstance`  
_L12-20_
- inherits: `BlendShapesOutputInstance`
- L14 _public prototype_ `BlendShapesImplOutputInstance(std::uint16_t blendShapeCount, MemoryResource* memRes);`
- L15 _public prototype_ `ArrayView<float> getOutputBuffer() override;`
- L16 _public prototype_ `void resetOutputBuffer() override;`
- L19 _private member_ `Vector<float> outputBuffer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapesNull.h` (Private)


#### class `rl4::BlendShapesNull`  
`class BlendShapesNull : public BlendShapes`  
_L15-24_
- inherits: `BlendShapes`
- L17 _public prototype_ `BlendShapesOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L18 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t ) const override;`
- L19 _public prototype_ `void calculate(const ControlsInputInstance* , BlendShapesOutputInstance* , std::uint16_t ) const override;`
- L22 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& ) override;`
- L23 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& ) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapesNullOutputInstance.h` (Private)


#### class `rl4::BlendShapesNullOutputInstance`  
`class BlendShapesNullOutputInstance : public BlendShapesOutputInstance`  
_L10-14_
- inherits: `BlendShapesOutputInstance`
- L12 _public prototype_ `ArrayView<float> getOutputBuffer() override;`
- L13 _public prototype_ `void resetOutputBuffer() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/blendshapes/BlendShapesOutputInstance.h` (Private)


#### class `rl4::BlendShapesOutputInstance`  
`class BlendShapesOutputInstance`  
_L19-28_
- L21 _public typedef_ `using Pointer = UniqueInstance<BlendShapesOutputInstance>::PointerType;`
- L22 _public typedef_ `using Factory = std::function<Pointer(MemoryResource*)>;`
- L25 _public prototype_ `virtual ~BlendShapesOutputInstance();`
- L26 _public prototype_ `virtual ArrayView<float> getOutputBuffer() = 0;`
- L27 _public prototype_ `virtual void resetOutputBuffer() = 0;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/conditionaltable/ConditionalTable.h` (Private)


#### struct `rl4::Range`  
`struct Range`  
_L11-36_
- L12 _public member_ `float from;`
- L13 _public member_ `float to;`
- L14 _public member_ `Vector<std::uint16_t> rows;`
- L16 _public function_ `explicit Range(MemoryResource* memRes) : from`
- L22 _public function_ `Range(float from_, float to_, MemoryResource* memRes) : from`
- L28 _public function_ `std::size_t size() const`
- L33 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `rl4::RangeMap`  
`struct RangeMap`  
_L38-65_
- L39 _public member_ `Vector<Range> ranges;`
- L41 _public function_ `explicit RangeMap(MemoryResource* memRes) : ranges`
- L45 _public function_ `Range* findRange(float from, float to)`
- L52 _public function_ `Range* addRange(float from, float to)`
- L62 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### class `rl4::ConditionalTable`  
`class ConditionalTable`  
_L67-115_
- L69 _public prototype_ `explicit ConditionalTable(MemoryResource* memRes);`
- L70 _public prototype_ `ConditionalTable(Vector<std::uint16_t>&& inputIndices_, Vector<std::uint16_t>&& outputIndices_, Vector<float>&& fromValues_, Vector<float>&& toValues_, Vector<float>&& slopeValues_, Vector<float>&& cutValues_, std::uint16_t inputCount_, std::uint16_t outputCount_, MemoryResource* memRes);`
- L80 _public prototype_ `std::uint16_t getRowCount() const;`
- L81 _public prototype_ `std::uint16_t getInputCount() const;`
- L82 _public prototype_ `std::uint16_t getOutputCount() const;`
- L83 _public prototype_ `ConstArrayView<std::uint16_t> getInputIndices() const;`
- L84 _public prototype_ `ConstArrayView<std::uint16_t> getOutputIndices() const;`
- L85 _public prototype_ `void calculateForward(const float* inputs, float* outputs) const;`
- L86 _public prototype_ `void calculateForward(const float* inputs, float* outputs, std::uint16_t rowCount) const;`
- L87 _public prototype_ `void calculateReverse(float* inputs, const float* outputs) const;`
- L88 _public prototype_ `void calculateReverse(float* inputs, const float* outputs, std::uint16_t rowCount) const;`
- L91 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L105 _private member_ `Vector<RangeMap> rangeMaps;`
- L106 _private member_ `Vector<std::uint16_t> intervalsRemaining;`
- L107 _private member_ `Vector<std::uint16_t> inputIndices;`
- L108 _private member_ `Vector<std::uint16_t> outputIndices;`
- L109 _private member_ `Vector<float> fromValues;`
- L110 _private member_ `Vector<float> toValues;`
- L111 _private member_ `Vector<float> slopeValues;`
- L112 _private member_ `Vector<float> cutValues;`
- L113 _private member_ `std::uint16_t inputCount;`
- L114 _private member_ `std::uint16_t outputCount;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`
- L46 _function_ `auto it = std::find_if(ranges.begin(), ranges.end(), [from, to](const Range& range) { return ((range.from == from) && (range.to == to)); });` (scope `rl4::RangeMap::findRange`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/controls/Controls.h` (Private)


#### class `rl4::Controls`  
`class Controls`  
_L13-40_
- L15 _public typedef_ `using Pointer = UniqueInstance<Controls>::PointerType;`
- L18 _public prototype_ `Controls(ConditionalTable&& guiToRawMapping_, Vector<ControlInitializer>&& initialValues_, ControlsInputInstance::Factory instanceFactory_, std::uint16_t lodCount, MemoryResource* memRes);`
- L24 _public prototype_ `ControlsInputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const;`
- L25 _public prototype_ `void registerControls(std::uint16_t lod, ConstArrayView<std::uint16_t> controlIndices);`
- L26 _public prototype_ `ConstArrayView<std::uint16_t> getRegisteredControls(std::uint16_t lod) const;`
- L27 _public prototype_ `void mapGUIToRaw(ControlsInputInstance* instance) const;`
- L28 _public prototype_ `void mapRawToGUI(ControlsInputInstance* instance) const;`
- L31 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L36 _private member_ `Matrix<std::uint16_t> registeredControls;`
- L37 _private member_ `ConditionalTable guiToRawMapping;`
- L38 _private member_ `Vector<ControlInitializer> initialValues;`
- L39 _private member_ `ControlsInputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/controls/ControlsFactory.h` (Private)


#### struct `rl4::ControlsFactory`  
`struct ControlsFactory`  
_L13-19_
- L14 _public prototype_ `static Controls::Pointer create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, MemoryResource* memRes);`
- L18 _public prototype_ `static Controls::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/controls/ControlsInputInstance.h` (Private)


#### struct `rl4::ControlInitializer`  
`struct ControlInitializer`  
_L18-26_
- L19 _public member_ `std::uint32_t index;`
- L20 _public member_ `float value;`
- L23 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### class `rl4::ControlsInputInstance`  
`class ControlsInputInstance`  
_L28-45_
- L30 _public typedef_ `using Pointer = UniqueInstance<ControlsInputInstance>::PointerType;`
- L31 _public typedef_ `using Factory = std::function<Pointer(ConstArrayView<ControlInitializer>, MemoryResource*)>;`
- L34 _public prototype_ `virtual ~ControlsInputInstance();`
- L35 _public prototype_ `virtual void resetInputBuffer() = 0;`
- L36 _public prototype_ `virtual ArrayView<float> getGUIControlBuffer() = 0;`
- L37 _public prototype_ `virtual ArrayView<float> getInputBuffer() = 0;`
- L38 _public prototype_ `virtual ConstArrayView<float> getGUIControlBuffer() const = 0;`
- L39 _public prototype_ `virtual ConstArrayView<float> getInputBuffer() const = 0;`
- L40 _public prototype_ `virtual std::uint16_t getGUIControlCount() const = 0;`
- L41 _public prototype_ `virtual std::uint16_t getRawControlCount() const = 0;`
- L42 _public prototype_ `virtual std::uint16_t getPSDControlCount() const = 0;`
- L43 _public prototype_ `virtual std::uint16_t getMLControlCount() const = 0;`
- L44 _public prototype_ `virtual std::uint16_t getRBFControlCount() const = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/controls/instances/StandardControlsInputInstance.h` (Private)


#### class `rl4::StandardControlsInputInstance`  
`class StandardControlsInputInstance : public ControlsInputInstance`  
_L12-42_
- inherits: `ControlsInputInstance`
- L14 _public prototype_ `StandardControlsInputInstance(std::uint16_t guiControlCount_, std::uint16_t rawControlCount_, std::uint16_t psdControlCount_, std::uint16_t mlControlCount_, std::uint16_t rbfControlCount_, ConstArrayView<ControlInitializer> initialValues_, MemoryResource* memRes);`
- L22 _public prototype_ `void resetInputBuffer() override;`
- L23 _public prototype_ `ArrayView<float> getGUIControlBuffer() override;`
- L24 _public prototype_ `ArrayView<float> getInputBuffer() override;`
- L25 _public prototype_ `ConstArrayView<float> getGUIControlBuffer() const override;`
- L26 _public prototype_ `ConstArrayView<float> getInputBuffer() const override;`
- L27 _public prototype_ `std::uint16_t getGUIControlCount() const override;`
- L28 _public prototype_ `std::uint16_t getRawControlCount() const override;`
- L29 _public prototype_ `std::uint16_t getPSDControlCount() const override;`
- L30 _public prototype_ `std::uint16_t getMLControlCount() const override;`
- L31 _public prototype_ `std::uint16_t getRBFControlCount() const override;`
- L34 _private member_ `Vector<float> guiControlBuffer;`
- L35 _private member_ `Vector<float> inputBuffer;`
- L36 _private member_ `Vector<ControlInitializer> initialValues;`
- L37 _private member_ `std::uint16_t guiControlCount;`
- L38 _private member_ `std::uint16_t rawControlCount;`
- L39 _private member_ `std::uint16_t psdControlCount;`
- L40 _private member_ `std::uint16_t mlControlCount;`
- L41 _private member_ `std::uint16_t rbfControlCount;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointBehaviorFilter.h` (Private)


#### class `rl4::JointBehaviorFilter`  
`class JointBehaviorFilter`  
_L9-75_
- L21 _public prototype_ `JointBehaviorFilter(const dna::Reader* reader_, MemoryResource* memRes);`
- L23 _public prototype_ `JointBehaviorFilter& include(dna::TranslationRepresentation translationType);`
- L24 _public prototype_ `JointBehaviorFilter& include(dna::RotationRepresentation rotationType);`
- L25 _public prototype_ `JointBehaviorFilter& include(dna::ScaleRepresentation scaleType);`
- L26 _public prototype_ `JointBehaviorFilter& exclude(dna::TranslationRepresentation translationType);`
- L27 _public prototype_ `JointBehaviorFilter& exclude(dna::RotationRepresentation rotationType);`
- L28 _public prototype_ `JointBehaviorFilter& exclude(dna::ScaleRepresentation scaleType);`
- L31 _public function_ `template<typename... TAttr> JointBehaviorFilter included(TAttr... attrTypes) const`
- L39 _public function_ `template<typename... TAttr> JointBehaviorFilter excluded(TAttr... attrTypes) const`
- L47 _public function_ `template<typename... TAttr> JointBehaviorFilter only(TAttr... attrTypes) const`
- L52 _public prototype_ `dna::TranslationUnit getTranslationUnit() const;`
- L53 _public prototype_ `dna::RotationUnit getRotationUnit() const;`
- L54 _public prototype_ `std::uint16_t getLODCount() const;`
- L55 _public prototype_ `std::uint16_t getControlCount() const;`
- L56 _public prototype_ `std::uint16_t getJointCount() const;`
- L57 _public prototype_ `std::uint16_t getRowCount() const;`
- L58 _public prototype_ `std::uint16_t getColumnCount() const;`
- L59 _public prototype_ `std::uint16_t getJointGroupCount() const;`
- L60 _public prototype_ `std::uint16_t getRowCountForLOD(std::uint16_t jointGroupIndex, std::uint16_t lod) const;`
- L61 _public prototype_ `std::uint16_t getRowCount(std::uint16_t jointGroupIndex) const;`
- L62 _public prototype_ `std::uint16_t getColumnCount(std::uint16_t jointGroupIndex) const;`
- L63 _public prototype_ `void copyInputIndices(std::uint16_t jointGroupIndex, ArrayView<std::uint16_t> dest) const;`
- L64 _public prototype_ `void copyOutputIndices(std::uint16_t jointGroupIndex, ArrayView<std::uint16_t> dest) const;`
- L65 _public prototype_ `void copyValues(std::uint16_t jointGroupIndex, ArrayView<float> dest) const;`
- L67 _public prototype_ `const dna::Reader* getReader() const;`
- L70 _private prototype_ `bool isAttributeEnabled(std::uint16_t absAttrIndex) const;`
- L73 _private member_ `const dna::Reader* reader;`
- L74 _private member_ `Vector<FilterType> filters;`

#### struct `rl4::JointBehaviorFilter::FilterType`  
`struct FilterType`  
_L11-18_
- L12 _public member_ `std::uint8_t attr;`
- L13 _public member_ `std::uint8_t repr;`
- L15 _public function_ `bool operator==(const JointBehaviorFilter::FilterType& rhs)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`
- L33 _typedef_ `using expander = int[];` (scope `rl4::JointBehaviorFilter::included`)
- L41 _typedef_ `using expander = int[];` (scope `rl4::JointBehaviorFilter::excluded`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/Joints.h` (Private)


#### class `rl4::Joints`  
`class Joints`  
_L17-60_
- L19 _public typedef_ `using Pointer = UniqueInstance<Joints>::PointerType;`
- L22 _public prototype_ `Joints(JointsEvaluator::Pointer evaluator_, RigMetadata* meta, MemoryResource* memRes);`
- L23 _public prototype_ `Joints(JointsEvaluator::Pointer evaluator_, Vector<float>&& neutralValues_, Matrix<std::uint16_t>&& variableAttributeIndices_, Matrix<std::uint16_t>&& jointIndices_, std::uint16_t jointGroupCount_);`
- L29 _public prototype_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const;`
- L30 _public prototype_ `ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const;`
- L31 _public prototype_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const;`
- L32 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const;`
- L33 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const;`
- L39 _public function_ `template<class Archive> void load(Archive& archive)`
- L45 _public function_ `template<class Archive> void save(Archive& archive)`
- L50 _public prototype_ `std::uint16_t getJointGroupCount() const;`
- L51 _public prototype_ `ConstArrayView<float> getNeutralValues() const;`
- L52 _public prototype_ `ConstArrayView<std::uint16_t> getVariableAttributeIndices(std::uint16_t lod) const;`
- L55 _private member_ `JointsEvaluator::Pointer evaluator;`
- L56 _private member_ `Vector<float> neutralValues;`
- L57 _private member_ `Matrix<std::uint16_t> variableAttributeIndices;`
- L58 _private member_ `Matrix<std::uint16_t> jointIndices;`
- L59 _private member_ `std::uint16_t jointGroupCount;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointsBuilder.h` (Private)


#### class `rl4::JointsBuilder`  
`class JointsBuilder`  
_L15-30_
- L17 _public typedef_ `using Pointer = UniqueInstance<JointsBuilder>::PointerType;`
- L20 _public prototype_ `virtual ~JointsBuilder();`
- L22 _public prototype_ `static Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`
- L24 _public prototype_ `virtual void computeStorageRequirements() = 0;`
- L25 _public prototype_ `virtual void computeStorageRequirements(const JointBehaviorFilter& source) = 0;`
- L26 _public prototype_ `virtual void allocateStorage(const JointBehaviorFilter& source) = 0;`
- L27 _public prototype_ `virtual void fillStorage(const JointBehaviorFilter& source) = 0;`
- L28 _public prototype_ `virtual void registerControls(Controls* controls) = 0;`
- L29 _public prototype_ `virtual JointsEvaluator::Pointer build() = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointsEvaluator.h` (Private)


#### class `rl4::JointsEvaluator`  
`class JointsEvaluator`  
_L14-31_
- L16 _public typedef_ `using Pointer = UniqueInstance<JointsEvaluator>::PointerType;`
- L19 _protected prototype_ `virtual ~JointsEvaluator();`
- L22 _public prototype_ `virtual JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const = 0;`
- L23 _public prototype_ `virtual std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const = 0;`
- L24 _public prototype_ `virtual void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const = 0;`
- L25 _public prototype_ `virtual void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const = 0;`
- L29 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L30 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointsFactory.h` (Private)


#### struct `rl4::JointsFactory`  
`struct JointsFactory`  
_L14-18_
- L16 _public prototype_ `create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, Controls* controls, MemoryResource* memRes);`
- L17 _public prototype_ `static Joints::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointsNullEvaluator.h` (Private)


#### class `rl4::JointsNullEvaluator`  
`class JointsNullEvaluator : public JointsEvaluator`  
_L14-25_
- inherits: `JointsEvaluator`
- L16 _public prototype_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L17 _public prototype_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t ) const override;`
- L18 _public prototype_ `void calculate(ControlsInputInstance* , JointsOutputInstance* , std::uint16_t ) const override;`
- L19 _public prototype_ `void calculate(ControlsInputInstance* , JointsOutputInstance* , std::uint16_t , std::uint16_t ) const override;`
- L23 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& ) override;`
- L24 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& ) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointsNullOutputInstance.h` (Private)


#### class `rl4::JointsNullOutputInstance`  
`class JointsNullOutputInstance : public JointsOutputInstance`  
_L9-13_
- inherits: `JointsOutputInstance`
- L11 _public prototype_ `ArrayView<float> getOutputBuffer() override;`
- L12 _public prototype_ `void resetOutputBuffer() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/JointsOutputInstance.h` (Private)


#### class `rl4::JointsOutputInstance`  
`class JointsOutputInstance`  
_L18-29_
- L20 _public typedef_ `using Pointer = UniqueInstance<JointsOutputInstance>::PointerType;`
- L21 _public typedef_ `using Factory = std::function<Pointer(MemoryResource*)>;`
- L24 _protected prototype_ `virtual ~JointsOutputInstance();`
- L27 _public prototype_ `virtual ArrayView<float> getOutputBuffer() = 0;`
- L28 _public prototype_ `virtual void resetOutputBuffer() = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/CPUJointsBuilder.h` (Private)


#### class `rl4::CPUJointsBuilder`  
`class CPUJointsBuilder : public JointsBuilder`  
_L17-36_
- inherits: `JointsBuilder`
- L19 _public prototype_ `CPUJointsBuilder(const Configuration& config_, RigMetadata* meta_, MemoryResource* memRes_);`
- L20 _public prototype_ `void computeStorageRequirements() override;`
- L21 _public prototype_ `void computeStorageRequirements(const JointBehaviorFilter& source) override;`
- L22 _public prototype_ `void allocateStorage(const JointBehaviorFilter& source) override;`
- L23 _public prototype_ `void fillStorage(const JointBehaviorFilter& source) override;`
- L24 _public prototype_ `void registerControls(Controls* controls) override;`
- L25 _public prototype_ `JointsEvaluator::Pointer build() override;`
- L28 _private member_ `MemoryResource* memRes;`
- L29 _private member_ `Configuration config;`
- L30 _private member_ `RigMetadata* meta;`
- L31 _private member_ `UniqueInstance<JointsBuilder>::PointerType bpcmBuilder;`
- L32 _private member_ `UniqueInstance<JointsBuilder>::PointerType quaternionBuilder;`
- L33 _private member_ `UniqueInstance<JointsBuilder>::PointerType twistSwingBuilder;`
- L34 _private member_ `UniqueInstance<JointsBuilder>::PointerType mlBuilder;`
- L35 _private member_ `std::uint16_t numAttrsPerJoint;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/CPUJointsEvaluator.h` (Private)


#### class `rl4::CPUJointsEvaluator`  
`class CPUJointsEvaluator : public JointsEvaluator`  
_L14-41_
- inherits: `JointsEvaluator`
- L20 _public prototype_ `CPUJointsEvaluator(JointsEvaluator::Pointer bpcmEvaluator_, JointsEvaluator::Pointer quaternionEvaluator_, JointsEvaluator::Pointer twistSwingEvaluator_, JointsEvaluator::Pointer mlEvaluator_, JointsOutputInstance::Factory instanceFactory_);`
- L25 _public prototype_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L26 _public prototype_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const override;`
- L27 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const override;`
- L28 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const override;`
- L32 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L33 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L36 _private member_ `JointsEvaluator::Pointer bpcmEvaluator;`
- L37 _private member_ `JointsEvaluator::Pointer quaternionEvaluator;`
- L38 _private member_ `JointsEvaluator::Pointer twistSwingEvaluator;`
- L39 _private member_ `JointsEvaluator::Pointer mlEvaluator;`
- L40 _private member_ `JointsOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/CPUJointsOutputInstance.h` (Private)


#### class `rl4::CPUJointsOutputInstance`  
`class CPUJointsOutputInstance : public JointsOutputInstance`  
_L21-34_
- inherits: `JointsOutputInstance`
- L23 _public prototype_ `CPUJointsOutputInstance(std::uint16_t jointAttributeCount, TranslationType translationType, RotationType rotationType, ScaleType scaleType, MemoryResource* memRes);`
- L28 _public prototype_ `ArrayView<float> getOutputBuffer() override;`
- L29 _public prototype_ `void resetOutputBuffer() override;`
- L32 _private member_ `AlignedVector<float> outputBuffer;`
- L33 _private member_ `std::function<void(ArrayView<float>)> resetBuffer;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/BPCMCalculationStrategy.h` (Private)


#### struct `rl4::bpcm::JointGroupLinearCalculationStrategy`  
`struct JointGroupLinearCalculationStrategy`  
_L333-340_
- L334 _public prototype_ `virtual ~JointGroupLinearCalculationStrategy();`
- L336 _public prototype_ `virtual void calculate(const JointGroupView& jointGroup, ConstArrayView<float> inputs, ArrayView<float> outputs, std::uint16_t lod) const = 0;`

#### struct `rl4::bpcm::VectorizedJointGroupLinearCalculationStrategy`  
`template<typename T, typename TFVec, class TRotationAdapter> struct VectorizedJointGroupLinearCalculationStrategy : public JointGroupLinearCalculationStrategy`  
_L343-357_
- inherits: `JointGroupLinearCalculationStrategy`
- L344 _public member_ `TRotationAdapter rotationAdapter;`
- L346 _public function_ `explicit VectorizedJointGroupLinearCalculationStrategy(TRotationAdapter&& rotationAdapter_) : rotationAdapter`
- L350 _public function_ `void calculate(const JointGroupView& jointGroup, ConstArrayView<float> inputs, ArrayView<float> outputs, std::uint16_t lod) const override`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rl4`
- L17 _namespace_ `namespace bpcm` (scope `rl4`)
- L46 _function_ `template<typename TFVec, typename T> static FORCE_INLINE void processBlocks8x1(const std::uint16_t* inputIndicesEndAlignedTo4, const std::uint16_t* inputIndicesEnd, ConstArrayView<float> inputs, const T* values, TFVec& sum1, TFVec& sum2)` (scope `rl4::bpcm`) — Process the remainder portion after 8x4 blocks Consumes 4 x 2 values per input index, but input indexes are processed one by one. The maximum number of iterations performed is 3, as anything larger would be already consumed by the 8x4 block processor. It's executed only after the 8x4 block processor in cases when the matrix column count is not divisible by 8. [ x x x x x x x x X Y Z ] Input Vector 0 1 2 3 4 5 6 7 8 9 0 0 x x x x x x x x A C E  |  X * A + Y * C + Z * E 1 x x x x x x x x A C E  |  X * A + Y * C + Z * E 2 x x x x x x x x A C E  |  X * A + Y * C + Z * E 3 x x x x x x x x A C E  |  X * A + Y * C + Z * E 4 x x x x x x x x B D F  |  X * B + Y * D + Z * F 5 x x x x x x x x B D F  |  X * B + Y * D + Z * F 6 x x x x x x x x B D F  |  X * B + Y * D + Z * F 7 x x x x x x x x B D F  |  X * B + Y * D + Z * F 8 x x x x x x x x x x x  | 9 x x x x x x x x x x x  | 10 x x x x x x x x x x x  | 11 x x x x x x x x x x x  |
- L88 _function_ `template<typename TFVec, typename T> static FORCE_INLINE void processBlocks8x4(const std::uint16_t* inputIndicesStart, const std::uint16_t* inputIndicesEndAlignedTo4, const std::uint16_t* inputIndicesEnd, ConstArrayView<float> inputs, const T* values, float* outbuf)` (scope `rl4::bpcm`) — Process the main portion of the matrix that's partitionable into 8x4 blocks Consumes 4 x 2 values per input index, and loads 4 input indexes per iteration, thus a single iteration processes 32 values. This is the most performant of all the block processors as for every 4 x 2 values only a single input vector needs to be filled (which is expensive as it involves a lot of shuffle instructions). [ S T U V W X Y Z x x x ] Input Vector 0 1 2 3 4 5 6 7 8 9 0 0 A C E G I K M O x x x  |  S * A + T * C + U * E + V * G + W * I + X * K + Y * M + Z * O 1 A C E G I K M O x x x  |  S * A + T * C + U * E + V * G + W * I + X * K + Y * M + Z * O 2 A C E G I K M O x x x  |  S * A + T * C + U * E + V * G + W * I + X * K + Y * M + Z * O 3 A C E G I K M O x x x  |  S * A + T * C + U * E + V * G + W * I + X * K + Y * M + Z * O 4 B D F H J L N P x x x  |  S * B + T * D + U * F + V * H + W * J + X * L + Y * N + Z * P 5 B D F H J L N P x x x  |  S * B + T * D + U * F + V * H + W * J + X * L + Y * N + Z * P 6 B D F H J L N P x x x  |  S * B + T * D + U * F + V * H + W * J + X * L + Y * N + Z * P 7 B D F H J L N P x x x  |  S * B + T * D + U * F + V * H + W * J + X * L + Y * N + Z * P 8 x x x x x x x x x x x  | 9 x x x x x x x x x x x  | 10 x x x x x x x x x x x  | 11 x x x x x x x x x x x  |
- L166 _function_ `template<typename TFVec, typename T> static FORCE_INLINE void processBlocks4x1(const std::uint16_t* inputIndicesEndAlignedTo8, const std::uint16_t* inputIndicesEnd, ConstArrayView<float> inputs, const T* values, TFVec& sum1)` (scope `rl4::bpcm`) — Process the remainder portion after 4x8 blocks Consumes 4 x 1 values per input index, but input indexes are processed one by one. The maximum number of iterations performed is 7, as anything larger would be already consumed by the 4x8 block processor. It's executed only after the 4x8 block processor, in cases when the matrix column count is not divisible by 8. [ x x x x x x x x T U V W X Y Z ] Input Vector 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 0 x x x x x x x x x x x x x x x  | 1 x x x x x x x x x x x x x x x  | 2 x x x x x x x x x x x x x x x  | 3 x x x x x x x x x x x x x x x  | 4 x x x x x x x x x x x x x x x  | 5 x x x x x x x x x x x x x x x  | 6 x x x x x x x x x x x x x x x  | 7 x x x x x x x x x x x x x x x  | 8 x x x x x x x x A B C D E F G  |  T * A + U * B + V * C + W * D + X * E + Y * F + Z * G 9 x x x x x x x x A B C D E F G  |  T * A + U * B + V * C + W * D + X * E + Y * F + Z * G 10 x x x x x x x x A B C D E F G  |  T * A + U * B + V * C + W * D + X * E + Y * F + Z * G 11 x x x x x x x x A B C D E F G  |  T * A + U * B + V * C + W * D + X * E + Y * F + Z * G
- L208 _function_ `template<typename TFVec, typename T> static FORCE_INLINE void processBlocks4x8(const std::uint16_t* inputIndicesStart, const std::uint16_t* inputIndicesEndAlignedTo8, const std::uint16_t* inputIndicesEnd, ConstArrayView<float> inputs, const T* values, float* outbuf)` (scope `rl4::bpcm`) — Process the vertical remainder portion of the matrix that's partitionable into 4x8 blocks Consumes 4 x 1 values per input index, and loads 8 input indexes per iteration, thus a single iteration processes 32 values. Although it processes the same number of values per iteration as the 8x4 block processor, it does so by having to fill 8 input vectors (one for each 4 x 1 value-block), thus requiring twice the number of shuffle instructions which makes it somewhat less performant than the 8x4 variant. It gets executed only in cases when the matrix row count is not divisible by 8. [ S T U V W X Y Z x x x ] Input Vector 0 1 2 3 4 5 6 7 8 9 0 0 x x x x x x x x x x x  | 1 x x x x x x x x x x x  | 2 x x x x x x x x x x x  | 3 x x x x x x x x x x x  | 4 x x x x x x x x x x x  | 5 x x x x x x x x x x x  | 6 x x x x x x x x x x x  | 7 x x x x x x x x x x x  | 8 A B C D E F G H x x x  |  S * A + T * B + U * C + V * D + W * E + X * F + Y * G + Z * H 9 A B C D E F G H x x x  |  S * A + T * B + U * C + V * D + W * E + X * F + Y * G + Z * H 10 A B C D E F G H x x x  |  S * A + T * B + U * C + V * D + W * E + X * F + Y * G + Z * H 11 A B C D E F G H x x x  |  S * A + T * B + U * C + V * D + W * E + X * F + Y * G + Z * H
- L267 _function_ `template<typename TFVec, typename T> static FORCE_INLINE void processJointGroupBlock4(const JointGroupView& jointGroup, ConstArrayView<float> inputs, ArrayView<float> outputs, std::uint16_t lod)` (scope `rl4::bpcm`) — Orchestrate the execution of the needed block processors for a given joint group

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/BPCMJointsBuilder.h` (Private)


#### class `rl4::bpcm::BPCMJointsBuilder`  
`class BPCMJointsBuilder : public JointsBuilder`  
_L18-43_
- inherits: `JointsBuilder`
- L20 _public prototype_ `BPCMJointsBuilder(const Configuration& config_, RigMetadata* meta_, MemoryResource* memRes_);`
- L22 _public prototype_ `void computeStorageRequirements() override;`
- L23 _public prototype_ `void computeStorageRequirements(const JointBehaviorFilter& ) override;`
- L24 _public prototype_ `void allocateStorage(const JointBehaviorFilter& source) override;`
- L25 _public prototype_ `void fillStorage(const JointBehaviorFilter& source) override;`
- L26 _public prototype_ `void registerControls(Controls* controls) override;`
- L27 _public prototype_ `JointsEvaluator::Pointer build() override;`
- L30 _private prototype_ `void setOutputRotationIndices(const JointBehaviorFilter& source);`
- L31 _private prototype_ `void setOutputRotationLODs(ConstArrayView<LODRegion> lods, ConstArrayView<std::uint16_t> outputRotationIndices, std::uint32_t outputOffset, std::uint16_t jointGroupIndex);`
- L37 _private member_ `Configuration config;`
- L38 _private member_ `RigMetadata* meta;`
- L39 _private member_ `MemoryResource* memRes;`
- L40 _private member_ `JointStorage storage;`
- L41 _private member_ `dna::RotationUnit rotationUnit;`
- L42 _private member_ `std::uint16_t lodCount;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace rl4`
- L16 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/BPCMJointsBuilderFactory.h` (Private)


#### struct `rl4::BPCMJointsBuilderFactory`  
`struct BPCMJointsBuilderFactory`  
_L11-15_
- L12 _public prototype_ `static UniqueInstance<JointsBuilder>::PointerType create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/BPCMJointsEvaluator.h` (Private)


#### class `rl4::bpcm::Evaluator`  
`class Evaluator : public JointsEvaluator`  
_L19-49_
- inherits: `JointsEvaluator`
- L21 _public typedef_ `using CalculationStrategyPointer = typename UniqueInstance<JointGroupLinearCalculationStrategy>::PointerType;`
- L27 _public prototype_ `Evaluator(JointStorage&& storage_, Vector<JointGroupView>&& jointGroups_, CalculationStrategyPointer strategy_, JointsOutputInstance::Factory instanceFactory_, MemoryResource* memRes_);`
- L33 _public prototype_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L34 _public prototype_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const override;`
- L35 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const override;`
- L36 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const override;`
- L40 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L41 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L44 _private member_ `MemoryResource* memRes;`
- L45 _private member_ `JointStorage storage;`
- L46 _private member_ `Vector<JointGroupView> jointGroups;`
- L47 _private member_ `CalculationStrategyPointer strategy;`
- L48 _private member_ `JointsOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rl4`
- L17 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/JointGroup.h` (Private)


#### struct `rl4::bpcm::JointGroup`  
`struct JointGroup`  
_L14-44_
- L16 _public member_ `std::uint32_t valuesOffset;` — Start of non-zero values in storage
- L18 _public member_ `std::uint32_t inputIndicesOffset;` — Start of sub-matrix col -> input vector mapping in storage
- L20 _public member_ `std::uint32_t outputIndicesOffset;` — Start of sub-matrix row -> output vector mapping in storage
- L22 _public member_ `std::uint32_t lodsOffset;` — Start of LODs in storage
- L24 _public member_ `std::uint32_t outputRotationIndicesOffset;` — Start of output rotation indices in storage
- L26 _public member_ `std::uint32_t outputRotationLODsOffset;` — Start of output rotation index LODs in storage
- L28 _public member_ `std::uint32_t valuesSize;` — Sizes associated with start offsets
- L29 _public member_ `std::uint32_t colCount;`
- L30 _public member_ `std::uint32_t rowCount;`
- L33 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L12 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/RotationAdapters.h` (Private)


#### struct `rl4::bpcm::NoopAdapter`  
`struct NoopAdapter`  
_L16-24_
- L17 _public member_ `tdm::rot_sign rotSigns;`
- L19 _public function_ `FORCE_INLINE void forward(const JointGroupView& , ArrayView<float> , std::uint16_t ) const`
- L22 _public function_ `FORCE_INLINE void reverse(const JointGroupView& , ArrayView<float> , std::uint16_t ) const`

#### struct `rl4::bpcm::EulerAnglesToQuaternions`  
`template<typename TAngle, tdm::rot_seq Order> struct EulerAnglesToQuaternions`  
_L27-60_
- L28 _public member_ `tdm::rot_sign rotSigns;`
- L33 _public function_ `FORCE_INLINE void forward(const JointGroupView& jointGroup, ArrayView<float> outputs, std::uint16_t lod) const`
- L47 _public function_ `FORCE_INLINE void reverse(const JointGroupView& jointGroup, ArrayView<float> outputs, std::uint16_t lod) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`
- L14 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/bpcm/Storage.h` (Private)


#### struct `rl4::bpcm::JointStorage`  
`struct JointStorage`  
_L15-45_
- L17 _public member_ `FloatArray values;` — All non-zero values
- L19 _public member_ `AlignedVector<std::uint16_t> inputIndices;` — Sub-matrix col -> input vector
- L21 _public member_ `AlignedVector<std::uint16_t> outputIndices;` — Sub-matrix row -> output vector
- L23 _public member_ `Vector<LODRegion> lodRegions;` — Output index boundaries for each LOD
- L25 _public member_ `Vector<std::uint16_t> outputRotationIndices;` — Rotation indices (the start index for each rotation, used for conversion to quaternions)
- L27 _public member_ `Vector<std::uint16_t> outputRotationLODs;` — Rotation index boundaries for each LOD
- L29 _public member_ `Vector<JointGroup> jointGroups;` — Delineate storage into joint-groups
- L31 _public function_ `explicit JointStorage(MemoryResource* memRes) : values`
- L42 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `rl4::bpcm::JointGroupView`  
`struct JointGroupView`  
_L47-56_
- L48 _public member_ `void* values;`
- L49 _public member_ `std::uint32_t colCount;`
- L50 _public member_ `std::uint32_t rowCount;`
- L51 _public member_ `std::uint16_t* inputIndices;`
- L52 _public member_ `std::uint16_t* outputIndices;`
- L53 _public member_ `std::uint16_t* outputRotationIndices;`
- L54 _public member_ `std::uint16_t* outputRotationLODs;`
- L55 _public member_ `LODRegion* lods;`

#### struct `rl4::bpcm::StorageSnapshot`  
`template<typename T, typename TF256, typename TF128> struct StorageSnapshot`  
_L59-76_
- L61 _public function_ `Vector<JointGroupView> operator()(JointStorage& storage, MemoryResource* memRes)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`
- L13 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/ml/CoordinateSystemTransformer.h` (Private)


#### struct `rl4::ml::NoopTransformer`  
`struct NoopTransformer`  
_L12-29_
- L14 _public function_ `static FORCE_INLINE void transform(ArrayView<float> values, ConstArrayView<std::uint16_t> baseIndices, const tdm::fmat3& changeOfBasis, tdm::rot_seq srcSeq, const tdm::rot_sign& srcSigns, tdm::rot_seq dstSeq, const tdm::rot_sign& dstSigns)`

#### struct `rl4::ml::TranslationTransformer`  
`struct TranslationTransformer`  
_L31-53_
- L33 _public function_ `static FORCE_INLINE void transform(ArrayView<float> values, ConstArrayView<std::uint16_t> baseIndices, const tdm::fmat3& changeOfBasis, tdm::rot_seq srcSeq, const tdm::rot_sign& srcSigns, tdm::rot_seq dstSeq, const tdm::rot_sign& dstSigns)`

#### struct `rl4::ml::QuaternionTransformer`  
`struct QuaternionTransformer`  
_L55-80_
- L57 _public function_ `static FORCE_INLINE void transform(ArrayView<float> values, ConstArrayView<std::uint16_t> baseIndices, const tdm::fmat3& changeOfBasis, tdm::rot_seq srcSeq, const tdm::rot_sign& srcSigns, tdm::rot_seq dstSeq, const tdm::rot_sign& dstSigns)`

#### struct `rl4::ml::EulerAnglesTransformer`  
`template<typename TAngle> struct EulerAnglesTransformer`  
_L83-106_
- L88 _public function_ `static FORCE_INLINE void transform(ArrayView<float> values, ConstArrayView<std::uint16_t> baseIndices, const tdm::fmat3& changeOfBasis, tdm::rot_seq srcSeq, const tdm::rot_sign& srcSigns, tdm::rot_seq dstSeq, const tdm::rot_sign& dstSigns)`

#### struct `rl4::ml::ScaleTransformer`  
`struct ScaleTransformer`  
_L108-132_
- L110 _public function_ `static FORCE_INLINE void transform(ArrayView<float> values, ConstArrayView<std::uint16_t> baseIndices, const tdm::fmat3& changeOfBasis, tdm::rot_seq srcSeq, const tdm::rot_sign& srcSigns, tdm::rot_seq dstSeq, const tdm::rot_sign& dstSigns)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`
- L10 _namespace_ `namespace ml` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/ml/MLJointsBuilder.h` (Private)


#### class `rl4::ml::MLJointsBuilder`  
`class MLJointsBuilder : public JointsBuilder`  
_L19-54_
- inherits: `JointsBuilder`
- L21 _public prototype_ `MLJointsBuilder(const Configuration& config_, RigMetadata* meta_, MemoryResource* memRes_);`
- L22 _public prototype_ `void computeStorageRequirements() override;`
- L23 _public prototype_ `void computeStorageRequirements(const JointBehaviorFilter& source) override;`
- L24 _public prototype_ `void allocateStorage(const JointBehaviorFilter& source) override;`
- L25 _public prototype_ `void fillStorage(const JointBehaviorFilter& source) override;`
- L26 _public prototype_ `void registerControls(Controls* controls) override;`
- L27 _public prototype_ `JointsEvaluator::Pointer build() override;`
- L30 _private prototype_ `void remapIndices(std::uint16_t lod);`
- L33 _private member_ `MemoryResource* memRes;`
- L34 _private member_ `Configuration config;`
- L35 _private member_ `RigMetadata* meta;`
- L36 _private member_ `Matrix<std::uint16_t> inputIndices;`
- L37 _private member_ `Matrix<std::uint16_t> outputIndices;`
- L38 _private member_ `Matrix<std::uint16_t> inputRotationBaseIndices;`
- L39 _private member_ `Matrix<std::uint16_t> outputRotationBaseIndices;`
- L40 _private member_ `Matrix<std::uint16_t> uniqueTranslationBaseIndices;`
- L41 _private member_ `Matrix<std::uint16_t> uniqueRotationBaseIndices;`
- L42 _private member_ `Matrix<std::uint16_t> uniqueScaleBaseIndices;`
- L43 _private member_ `tdm::fmat3 changeOfBasis;`
- L44 _private member_ `tdm::rot_seq srcSeq;`
- L45 _private member_ `tdm::rot_sign srcSigns;`
- L46 _private member_ `tdm::rot_seq dstSeq;`
- L47 _private member_ `tdm::rot_sign dstSigns;`
- L48 _private member_ `std::uint16_t inputJointAttrCount;`
- L49 _private member_ `std::uint16_t outputJointAttrCount;`
- L50 _private member_ `dna::RotationUnit rotationUnit;`
- L51 _private member_ `TranslationType mlTranslationType;`
- L52 _private member_ `RotationType mlRotationType;`
- L53 _private member_ `ScaleType mlScaleType;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rl4`
- L17 _namespace_ `namespace ml` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/ml/MLJointsBuilderFactory.h` (Private)


#### struct `rl4::MLJointsBuilderFactory`  
`struct MLJointsBuilderFactory`  
_L11-15_
- L12 _public prototype_ `static UniqueInstance<JointsBuilder>::PointerType create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/ml/MLJointsEvaluator.h` (Private)


#### class `rl4::ml::MLJointsEvaluator`  
`template<class TTranslationTransformer, class TRotationTransformer, class TScaleTransformer, class TRotationAdapter> class MLJointsEvaluator : public JointsEvaluator`  
_L17-163_
- inherits: `JointsEvaluator`
- L23 _public function_ `MLJointsEvaluator(Matrix<std::uint16_t>&& inputIndices_, Matrix<std::uint16_t>&& outputIndices_, Matrix<std::uint16_t>&& inputRotationBaseIndices_, Matrix<std::uint16_t>&& outputRotationBaseIndices_, Matrix<std::uint16_t>&& uniqueTranslationBaseIndices_, Matrix<std::uint16_t>&& uniqueRotationBaseIndices_, Matrix<std::uint16_t>&& uniqueScaleBaseIndices_, const tdm::fmat3& changeOfBasis_, tdm::rot_seq srcSeq_, tdm::rot_sign srcSigns_, tdm::rot_seq dstSeq_, tdm::rot_sign dstSigns_, TRotationAdapter&& rotationAdapter_, JointsOutputInstance::Factory instanceFactory_) : inputIndices`
- L53 _public function_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override`
- L57 _public function_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const override`
- L62 _public function_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const override`
- L109 _public function_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const override`
- L118 _public function_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override`
- L133 _public function_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override`
- L149 _private member_ `Matrix<std::uint16_t> inputIndices;`
- L150 _private member_ `Matrix<std::uint16_t> outputIndices;`
- L151 _private member_ `Matrix<std::uint16_t> inputRotationBaseIndices;`
- L152 _private member_ `Matrix<std::uint16_t> outputRotationBaseIndices;`
- L153 _private member_ `Matrix<std::uint16_t> uniqueTranslationBaseIndices;`
- L154 _private member_ `Matrix<std::uint16_t> uniqueRotationBaseIndices;`
- L155 _private member_ `Matrix<std::uint16_t> uniqueScaleBaseIndices;`
- L156 _private member_ `tdm::fmat3 changeOfBasis;`
- L157 _private member_ `tdm::rot_seq srcSeq;`
- L158 _private member_ `tdm::rot_sign srcSigns;`
- L159 _private member_ `tdm::rot_seq dstSeq;`
- L160 _private member_ `tdm::rot_sign dstSigns;`
- L161 _private member_ `TRotationAdapter rotationAdapter;`
- L162 _private member_ `JointsOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`
- L14 _namespace_ `namespace ml` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/ml/RotationAdapters.h` (Private)


#### struct `rl4::ml::NoopAdapter`  
`struct NoopAdapter`  
_L14-40_
- L15 _public member_ `tdm::rot_sign rotationSigns;`
- L17 _public function_ `FORCE_INLINE void adapt(ConstArrayView<float> inputs, ArrayView<float> outputs, ConstArrayView<std::uint16_t> inputRotationBaseIndices, ConstArrayView<std::uint16_t> outputRotationBaseIndices) const`

#### struct `rl4::ml::QuaternionsToEulerAngles`  
`template<typename TAngle, tdm::rot_seq Order> struct QuaternionsToEulerAngles`  
_L43-67_
- L44 _public member_ `tdm::rot_sign rotationSigns;`
- L49 _public function_ `FORCE_INLINE void adapt(ConstArrayView<float> inputs, ArrayView<float> outputs, ConstArrayView<std::uint16_t> inputRotationBaseIndices, ConstArrayView<std::uint16_t> outputRotationBaseIndices) const`

#### struct `rl4::ml::EulerAnglesToQuaternions`  
`template<typename TAngle, tdm::rot_seq Order> struct EulerAnglesToQuaternions`  
_L70-98_
- L71 _public member_ `tdm::rot_sign rotationSigns;`
- L76 _public function_ `FORCE_INLINE void adapt(ConstArrayView<float> inputs, ArrayView<float> outputs, ConstArrayView<std::uint16_t> inputRotationBaseIndices, ConstArrayView<std::uint16_t> outputRotationBaseIndices) const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L12 _namespace_ `namespace ml` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/quaternions/JointGroup.h` (Private)


#### struct `rl4::JointGroup`  
`struct JointGroup`  
_L13-39_
- L15 _public member_ `FloatArray values;` — All non-zero values
- L17 _public member_ `Vector<std::uint16_t> inputIndices;` — Sub-matrix col -> input vector
- L19 _public member_ `Vector<std::uint16_t> outputIndices;` — Sub-matrix row -> output vector
- L21 _public member_ `Vector<LODRegion> lods;` — Output index boundaries for each LOD
- L23 _public member_ `std::uint32_t colCount;` — Matrix size
- L24 _public member_ `std::uint32_t rowCount;`
- L26 _public function_ `explicit JointGroup(MemoryResource* memRes) : values`
- L36 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/quaternions/QuaternionCalculationStrategy.h` (Private)


#### struct `rl4::JointGroupQuaternionCalculationStrategy`  
`struct JointGroupQuaternionCalculationStrategy`  
_L290-296_
- L291 _public prototype_ `virtual ~JointGroupQuaternionCalculationStrategy();`
- L292 _public prototype_ `virtual void calculate(const JointGroup& jointGroup, ConstArrayView<float> inputs, ArrayView<float> outputs, std::uint16_t lod) const = 0;`

#### struct `rl4::VectorizedJointGroupQuaternionCalculationStrategy`  
`template<typename T, typename TFVec256, typename TFVec128, class TRotationAdapter> struct VectorizedJointGroupQuaternionCalculationStrategy : public JointGroupQuaternionCalculationStrategy`  
_L299-346_
- inherits: `JointGroupQuaternionCalculationStrategy`
- L300 _public member_ `TRotationAdapter rotationAdapter;`
- L302 _public function_ `explicit VectorizedJointGroupQuaternionCalculationStrategy(TRotationAdapter&& rotationAdapter_) : rotationAdapter`
- L306 _public function_ `void calculate(const JointGroup& jointGroup, ConstArrayView<float> inputs, ArrayView<float> outputs, std::uint16_t lod) const override`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace rl4`
- L107 _function_ `template<typename TFVec> static FORCE_INLINE void fastlerpWithIdentity(TFVec& qxACEG, TFVec& qyACEG, TFVec& qzACEG, TFVec& qwACEG, const TFVec& weight)` (scope `rl4`) — FastLerp between 4 arbitrary and 4 identity quaternions fastlerp_with_identity(Q, WEIGHT): IQ = [0, 0, 0, 1] // Dot product between IQ and Q D1 = IQ.x * Q.x + IQ.y * Q.y + IQ.z * Q.z + IQ.w * Q.w; D1 = 0 * Q.x + 0 * Q.y + 0 * Q.z + 1 * Q.w D1 = Q.w // Select bias based on dot product BIAS1 = D1 >= 0 ? 1.0 : -1.0 AW = BIAS1 * (1.0 - WEIGHT) // Because: // LERPED = (Q * WEIGHT) + (IQ * AW) // And: // IQ.x * AW = 0 * AW // IQ.y * AW = 0 * AW // IQ.z * AW = 0 * AW // IQ.w * AW = 1 * AW // It follows that: LERPED = [ Q.x * WEIGHT Q.y * WEIGHT Q.z * WEIGHT Q.w * WEIGHT + AW ] fastlerp_with_identity_simplified(Q, WEIGHT): BIAS1 = Q.w >= 0 ? 1.0 : -1.0 AW = BIAS1 * (1.0 - WEIGHT) LERPED = [ Q.x * WEIGHT Q.y * WEIGHT Q.z * WEIGHT Q.w * WEIGHT + AW ] A, C, E, G are quaternions representing delta rotations as an array of 4 floats [x, y, z, w]. fastlerp_with_identity_simd(A, C, E, G, WEIGHT): NEG_ONES = [-1, -1, -1, -1] ONES = [1, 1, 1, 1] MASK = [ A.w >= 0 C.w >= 0 E.w >= 0 G.w >= 0 ] BIAS = ANDNOT(MASK, NEG_ONES) | (ONES & MASK) ONE_MINUS_WEIGHT = [ (1.0 - WEIGHT) (1.0 - WEIGHT) (1.0 - WEIGHT) (1.0 - WEIGHT) ] AWS = BIAS * ONE_MINUS_WEIGHT WEIGHTS = [WEIGHT, WEIGHT, WEIGHT, WEIGHT] LERPED_X = [ A.x * WEIGHTS C.x * WEIGHTS E.x * WEIGHTS G.x * WEIGHTS ] LERPED_Y = [ A.y * WEIGHTS C.y * WEIGHTS E.y * WEIGHTS G.y * WEIGHTS ] LERPED_Z = [ A.z * WEIGHTS C.z * WEIGHTS E.z * WEIGHTS G.z * WEIGHTS ] LERPED_W = [ A.w * WEIGHTS + AWS C.w * WEIGHTS + AWS E.w * WEIGHTS + AWS G.w * WEIGHTS + AWS ] L
- L186 _function_ `template<typename TFVec> static FORCE_INLINE void normalize(TFVec& qxACEG, TFVec& qyACEG, TFVec& qzACEG, TFVec& qwACEG)` (scope `rl4`) — Normalize quaternion normalize(Q): SS = Q.x * Q.x + Q.y * Q.y + Q.z * Q.z + Q.w * Q.w INVSS = 1.0 / SQRT(SS) NORMALIZED = [ Q.x *= INVSS Q.y *= INVSS Q.z *= INVSS Q.w *= INVSS ] normalize_simd(A, C, E, G): XS_SQUARED = [ A.x * A.x C.x * C.x E.x * E.x G.x * G.x ] YS_SQUARED = [ A.y * A.y C.y * C.y E.y * E.y G.y * G.y ] ZS_SQUARED = [ A.z * A.z C.z * C.z E.z * E.z G.z * G.z ] WS_SQUARED = [ A.w * A.w C.w * C.w E.w * E.w G.w * G.w ] S_SUM = XS_SQUARED + YS_SQUARED + ZS_SQUARED + WS_SQUARED INVSS = 1.0 / SQRT(S_SUM)  // _mm_rsqrt_ps(S_SUM) NORMALIZED_A = [ A.x * INVSS A.y * INVSS A.z * INVSS A.w * INVSS ] NORMALIZED_B = [ B.x * INVSS B.y * INVSS B.z * INVSS B.w * INVSS ] NORMALIZED_C = [ C.x * INVSS C.y * INVSS C.z * INVSS C.w * INVSS ] NORMALIZED_D = [ D.x * INVSS D.y * INVSS D.z * INVSS D.w * INVSS ]
- L256 _function_ `template<typename TFVec, typename T> static FORCE_INLINE void blendQuaternions(const T* quaternions, ConstArrayView<std::uint16_t> inputIndices, ConstArrayView<float> inputs, float* outbuf)` (scope `rl4`) — Multiply each quaternion of a joint group by the expression weight, and combine them together into a single rotation Rotation = FastLerp(IdentityQuaternion, PoseQuaternion, ExpressionWeight); Rotation = Normalize(Rotation); OutputRotation = Rotation * OutputRotation;  // OutputRotation is the accumulator A, C, E, G are quaternions representing delta rotations as an array of 4 floats [x, y, z, w]. B, D, F, H are the accumulator quaternions that will contain the combined, blended rotations. The below operation is how a freshly blended set of 4 quaternions are combined with the accumulator quaternions. This first set of multiplications is how each pair is multiplied individually: A[3]*B[0] + A[0]*B[3] + A[1]*B[2] - A[2]*B[1]; A[3]*B[1] - A[0]*B[2] + A[1]*B[3] + A[2]*B[0]; A[3]*B[2] + A[0]*B[1] - A[1]*B[0] + A[2]*B[3]; A[3]*B[3] - A[0]*B[0] - A[1]*B[1] - A[2]*B[2]; C[3]*D[0] + C[0]*D[3] + C[1]*D[2] - C[2]*D[1]; C[3]*D[1] - C[0]*D[2] + C[1]*D[3] + C[2]*D[0]; C[3]*D[2] + C[0]*D[1] - C[1]*D[0] + C[2]*D[3]; C[3]*D[3] - C[0]*D[0] - C[1]*D[1] - C[2]*D[2]; E[3]*F[0] + E[0]*F[3] + E[1]*F[2] - E[2]*F[1]; E[3]*F[1] - E[0]*F[2] + E[1]*F[3] + E[2]*F[0]; E[3]*F[2] + E[0]*F[1] - E[1]*F[0] + E[2]*F[3]; E[3]*F[3] - E[0]*F[0] - E[1]*F[1] - E[2]*F[2]; G[3]*H[0] + G[0]*H[3] + G[1]*H[2] - G[2]*H[1]; G[3]*H[1] - G[0]*H[2] + G[1]*H[3] + G[2]*H[0]; G[3]*H[2] + G[0]*H[1] - G[1]*H[0] + G[2]*H[3]; G[3]*H[3] - G[0]*H[0] - G[1]*H[1] - G[2]*H[2]; And the below transformation is the same as the above shown bl

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/quaternions/QuaternionJointsBuilder.h` (Private)


#### class `rl4::QuaternionJointsBuilder`  
`class QuaternionJointsBuilder : public JointsBuilder`  
_L16-43_
- inherits: `JointsBuilder`
- L18 _public prototype_ `QuaternionJointsBuilder(const Configuration& config_, RigMetadata* meta_, MemoryResource* memRes_);`
- L20 _public prototype_ `void computeStorageRequirements() override;`
- L21 _public prototype_ `void computeStorageRequirements(const JointBehaviorFilter& source) override;`
- L22 _public prototype_ `void allocateStorage(const JointBehaviorFilter& source) override;`
- L23 _public prototype_ `void fillStorage(const JointBehaviorFilter& source) override;`
- L24 _public prototype_ `void registerControls(Controls* controls) override;`
- L25 _public prototype_ `JointsEvaluator::Pointer build() override;`
- L28 _private prototype_ `void setInputIndices(JointGroup& group, ConstArrayView<std::uint16_t> inputIndices);`
- L29 _private prototype_ `void setOutputIndices(JointGroup& group, ConstArrayView<std::uint16_t> outputIndices);`
- L30 _private prototype_ `void setValues(JointGroup& group, ConstArrayView<float> eulers, ConstArrayView<std::uint16_t> inputIndices, ConstArrayView<std::uint16_t> outputIndices);`
- L34 _private prototype_ `void setLODs(JointGroup& group, ConstArrayView<std::uint16_t> outputIndices);`
- L35 _private prototype_ `void remapOutputIndices(JointGroup& group);`
- L38 _private member_ `Configuration config;`
- L39 _private member_ `RigMetadata* meta;`
- L40 _private member_ `MemoryResource* memRes;`
- L41 _private member_ `Vector<JointGroup> jointGroups;`
- L42 _private member_ `dna::RotationUnit rotationUnit;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/quaternions/QuaternionJointsBuilderFactory.h` (Private)


#### struct `rl4::QuaternionJointsBuilderFactory`  
`struct QuaternionJointsBuilderFactory`  
_L11-15_
- L12 _public prototype_ `static UniqueInstance<JointsBuilder>::PointerType create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/quaternions/QuaternionJointsEvaluator.h` (Private)


#### class `rl4::QuaternionJointsEvaluator`  
`class QuaternionJointsEvaluator : public JointsEvaluator`  
_L16-44_
- inherits: `JointsEvaluator`
- L22 _private typedef_ `using CalculationStrategyPointer = typename UniqueInstance<JointGroupQuaternionCalculationStrategy>::PointerType;`
- L25 _public prototype_ `QuaternionJointsEvaluator(CalculationStrategyPointer strategy_, Vector<JointGroup>&& jointGroups_, JointsOutputInstance::Factory instanceFactory_, MemoryResource* memRes);`
- L30 _public prototype_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L31 _public prototype_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const override;`
- L32 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const override;`
- L33 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const override;`
- L37 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L38 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L41 _private member_ `CalculationStrategyPointer strategy;`
- L42 _private member_ `Vector<JointGroup> jointGroups;`
- L43 _private member_ `JointsOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/quaternions/RotationAdapters.h` (Private)


#### struct `rl4::PassthroughAdapter`  
`struct PassthroughAdapter`  
_L13-45_
- L14 _public member_ `tdm::rot_sign rotationSigns;`
- L16 _public function_ `static FORCE_INLINE void forward(const float* quaternions, std::size_t count, std::size_t stride, const std::uint16_t* outputIndices, ArrayView<float> outputs)`
- L31 _public function_ `static FORCE_INLINE void reverse(float* quaternions, std::size_t count, std::size_t stride, const std::uint16_t* outputIndices, ConstArrayView<float> outputs)`

#### struct `rl4::QuaternionsToEulerAngles`  
`template<typename TAngle, tdm::rot_seq Order> struct QuaternionsToEulerAngles`  
_L48-90_
- L49 _public member_ `tdm::rot_sign rotationSigns;`
- L51 _public function_ `FORCE_INLINE void forward(const float* quaternions, std::size_t count, std::size_t stride, const std::uint16_t* outputIndices, ArrayView<float> outputs) const`
- L71 _public function_ `FORCE_INLINE void reverse(float* quaternions, std::size_t count, std::size_t stride, const std::uint16_t* outputIndices, ConstArrayView<float> outputs) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/twistswing/TwistSwingJointsBuilder.h` (Private)


#### class `rl4::TwistSwingJointsBuilder`  
`template<typename TValue, typename TFVec256, typename TFVec128> class TwistSwingJointsBuilder : public JointsBuilder`  
_L31-48_
- inherits: `JointsBuilder`
- L33 _public prototype_ `TwistSwingJointsBuilder(const Configuration& config_, RigMetadata* meta_, MemoryResource* memRes_);`
- L35 _public prototype_ `void computeStorageRequirements() override;`
- L36 _public prototype_ `void computeStorageRequirements(const JointBehaviorFilter& source) override;`
- L37 _public prototype_ `void allocateStorage(const JointBehaviorFilter& source) override;`
- L38 _public prototype_ `void fillStorage(const JointBehaviorFilter& source) override;`
- L39 _public prototype_ `void registerControls(Controls* controls) override;`
- L40 _public prototype_ `JointsEvaluator::Pointer build() override;`
- L43 _private member_ `Configuration config;`
- L44 _private member_ `RigMetadata* meta;`
- L45 _private member_ `MemoryResource* memRes;`
- L46 _private member_ `Vector<TwistSwingSetup> setups;`
- L47 _private member_ `dna::RotationUnit rotationUnit;`
- L51 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::TwistSwingJointsBuilder(const Configuration& config_, RigMetadata* meta_, MemoryResource* memRes_) : config`
- L62 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> void TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::computeStorageRequirements()`
- L66 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> void TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::computeStorageRequirements(const JointBehaviorFilter& )`
- L70 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> void TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::allocateStorage(const JointBehaviorFilter& )`
- L74 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> void TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::fillStorage(const JointBehaviorFilter& source)`
- L170 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> void TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::registerControls(Controls* )`
- L315 _function_ `template<typename TValue, typename TFVec256, typename TFVec128> JointsEvaluator::Pointer TwistSwingJointsBuilder<TValue, TFVec256, TFVec128>::build()`

#### struct `rl4::TwistSwingJointsEvaluatorFactory`  
`template<typename TValue, typename TFVec256, typename TFVec128> struct TwistSwingJointsEvaluatorFactory`  
_L174-312_
- L176 _public function_ `JointsEvaluator::Pointer operator()(RotationType rotationType, tdm::rot_seq rotationSequence, tdm::rot_sign rotationSigns, dna::RotationUnit rotationUnit, Vector<TwistSwingSetup> setups, MemoryResource* memRes)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rl4`
- L18 _function_ `template<class TContainer, class UContainer> static bool containersEqual(const TContainer& lhs, const UContainer& rhs)` (scope `rl4`)
- L132 _function_ `[this, twistInputIndices, twistOutputIndices, twistBlendWeights, twistTwistAxis](TwistSwingSetup& setup)` (scope `rl4::TwistSwingJointsBuilder::fillStorage`)
- L156 _function_ `auto it = std::find_if(setups.begin(), setups.end(), [twistInputIndices](const TwistSwingSetup& setup) { return containersEqual(setup.swingInputIndices, twistInputIndices); });` (scope `rl4::TwistSwingJointsBuilder::fillStorage`)
- L183 _typedef_ `using TSJEvaluator = TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, PassthroughAdapter>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L193 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::fdeg, tdm::rot_seq::xyz>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L194 _typedef_ `using TSJEvaluator = TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, Q2E>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L200 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::frad, tdm::rot_seq::xyz>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L213 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::fdeg, tdm::rot_seq::xzy>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L220 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::frad, tdm::rot_seq::xzy>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L233 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::fdeg, tdm::rot_seq::yxz>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L240 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::frad, tdm::rot_seq::yxz>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L253 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::fdeg, tdm::rot_seq::yzx>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L260 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::frad, tdm::rot_seq::yzx>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L273 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::fdeg, tdm::rot_seq::zxy>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L280 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::frad, tdm::rot_seq::zxy>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L293 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::fdeg, tdm::rot_seq::zyx>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)
- L300 _typedef_ `using Q2E = QuaternionsToEulerAngles<tdm::frad, tdm::rot_seq::zyx>;` (scope `rl4::TwistSwingJointsEvaluatorFactory::operator ()`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/twistswing/TwistSwingJointsBuilderFactory.h` (Private)


#### struct `rl4::TwistSwingJointsBuilderFactory`  
`struct TwistSwingJointsBuilderFactory`  
_L11-15_
- L12 _public prototype_ `static UniqueInstance<JointsBuilder>::PointerType create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/twistswing/TwistSwingJointsEvaluator.h` (Private)


#### class `rl4::TwistSwingJointsEvaluator`  
`template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> class TwistSwingJointsEvaluator : public JointsEvaluator`  
_L35-60_
- inherits: `JointsEvaluator`
- L41 _public prototype_ `explicit TwistSwingJointsEvaluator(Vector<TwistSwingSetup>&& setups_, TRotationAdapter&& rotationAdapter_, JointsOutputInstance::Factory instanceFactory_, MemoryResource* memRes);`
- L46 _public prototype_ `JointsOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L47 _public prototype_ `std::uint32_t getJointDeltaValueCountForLOD(std::uint16_t lod) const override;`
- L48 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod) const override;`
- L49 _public prototype_ `void calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t lod, std::uint16_t jointGroupIndex) const override;`
- L53 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L54 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L57 _private member_ `Vector<TwistSwingSetup> setups;`
- L58 _private member_ `TRotationAdapter rotationAdapter;`
- L59 _private member_ `JointsOutputInstance::Factory instanceFactory;`
- L63 _function_ `template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::TwistSwingJointsEvaluator( Vector<TwistSwingSetup>&& setups_, TRotationAdapter&& rotationAdapter_, JointsOutputInstance::Factory instanceFactory_, MemoryResource* ) : setups`
- L75 _function_ `TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::createInstance(MemoryResource* instanceMemRes) const`
- L81 _function_ `template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> std::uint32_t TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::getJointDeltaValueCountForLOD( std::uint16_t ) const`
- L87 _function_ `template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> void TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::calculate(ControlsInputInstance* inputs, JointsOutputInstance* outputs, std::uint16_t ) const`
- L151 _function_ `template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> void TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::calculate(ControlsInputInstance* , JointsOutputInstance* , std::uint16_t , std::uint16_t ) const`
- L158 _function_ `template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> void TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::load( terse::BinaryInputArchive<BoundedIOStream>& archive)`
- L164 _function_ `template<typename TValue, typename TFVec256, typename TFVec128, class TRotationAdapter> void TwistSwingJointsEvaluator<TValue, TFVec256, TFVec128, TRotationAdapter>::save( terse::BinaryOutputArchive<BoundedIOStream>& archive)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace rl4`
- L19 _function_ `static inline tdm::fquat separateTwistComponentByAxisX(const tdm::fquat& input)` (scope `rl4`)
- L24 _function_ `static inline tdm::fquat separateTwistComponentByAxisY(const tdm::fquat& input)` (scope `rl4`)
- L29 _function_ `static inline tdm::fquat separateTwistComponentByAxisZ(const tdm::fquat& input)` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/twistswing/TwistSwingSetup.h` (Private)


#### struct `rl4::TwistSwingSetup`  
`struct TwistSwingSetup`  
_L9-41_
- L10 _public member_ `dna::TwistAxis twistTwistAxis;`
- L11 _public member_ `Vector<float> twistBlendWeights;`
- L12 _public member_ `Vector<std::uint16_t> twistOutputIndices;`
- L13 _public member_ `Vector<std::uint16_t> twistInputIndices;`
- L14 _public member_ `dna::TwistAxis swingTwistAxis;`
- L15 _public member_ `Vector<float> swingBlendWeights;`
- L16 _public member_ `Vector<std::uint16_t> swingOutputIndices;`
- L17 _public member_ `Vector<std::uint16_t> swingInputIndices;`
- L19 _public function_ `explicit TwistSwingSetup(MemoryResource* memRes) : twistTwistAxis`
- L31 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/utils/JointGroupOptimizer.h` (Private)


#### struct `rl4::JointGroupOptimizer`  
`struct JointGroupOptimizer`  
_L12-22_
- L13 _public prototype_ `static void defragment(const JointBehaviorFilter& source, std::uint16_t jointGroupIndex, Vector<float>& values, Vector<std::uint16_t>& inputIndices, Vector<std::uint16_t>& outputIndices, ArrayView<LODRegion> lodRegions, float translationPruningThreshold, float rotationPruningThreshold, float scalePruningThreshold);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/joints/cpu/utils/LODRegion.h` (Private)


#### struct `rl4::ColumnLOD`  
`struct ColumnLOD`  
_L11-33_
- L12 _public member_ `std::uint32_t size;`
- L13 _public member_ `std::uint32_t sizeAlignedTo4;`
- L14 _public member_ `std::uint32_t sizeAlignedTo8;`
- L16 _public prototype_ `ColumnLOD() = default;`
- L17 _public function_ `explicit ColumnLOD(std::uint32_t size_) : size`
- L23 _public function_ `ColumnLOD(std::uint32_t size_, std::uint32_t sizeAlignedTo4_, std::uint32_t sizeAlignedTo8_) : size`
- L30 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `rl4::LODRegion`  
`struct LODRegion`  
_L37-45_
- L38 _public member_ `ColumnLOD inputLODs;`
- L39 _public member_ `RowLOD outputLODs;`
- L42 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`
- L35 _typedef_ `using RowLOD = PaddedBlockView;` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/MachineLearnedBehavior.h` (Private)


#### class `rl4::MachineLearnedBehavior`  
`class MachineLearnedBehavior`  
_L17-59_
- L19 _public typedef_ `using Pointer = UniqueInstance<MachineLearnedBehavior>::PointerType;`
- L22 _public prototype_ `MachineLearnedBehavior(MachineLearnedBehaviorEvaluator::Pointer evaluator_, MemoryResource* memRes);`
- L23 _public prototype_ `MachineLearnedBehavior(MachineLearnedBehaviorEvaluator::Pointer evaluator_, Vector<std::uint16_t>&& meshRegionCounts_);`
- L25 _public prototype_ `MachineLearnedBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const;`
- L26 _public prototype_ `void calculate(ControlsInputInstance* inputs, MachineLearnedBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod) const;`
- L29 _public prototype_ `void calculate(ControlsInputInstance* inputs, MachineLearnedBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const;`
- L37 _public function_ `template<class Archive> void load(Archive& archive)`
- L43 _public function_ `template<class Archive> void save(Archive& archive)`
- L48 _public prototype_ `std::uint16_t getMeshCount() const;`
- L49 _public prototype_ `std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const;`
- L50 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const;`
- L51 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const;`
- L52 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const;`
- L57 _private member_ `MachineLearnedBehaviorEvaluator::Pointer evaluator;`
- L58 _private member_ `Vector<std::uint16_t> meshRegionCounts;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/MachineLearnedBehaviorEvaluator.h` (Private)


#### class `rl4::MachineLearnedBehaviorEvaluator`  
`class MachineLearnedBehaviorEvaluator`  
_L12-37_
- L14 _public typedef_ `using Pointer = UniqueInstance<MachineLearnedBehaviorEvaluator>::PointerType;`
- L17 _protected prototype_ `virtual ~MachineLearnedBehaviorEvaluator();`
- L20 _public prototype_ `virtual MachineLearnedBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const = 0;`
- L21 _public prototype_ `virtual std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const = 0;`
- L22 _public prototype_ `virtual std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;`
- L23 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;`
- L26 _public prototype_ `virtual void calculate(ControlsInputInstance* inputs, MachineLearnedBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod) const = 0;`
- L29 _public prototype_ `virtual void calculate(ControlsInputInstance* inputs, MachineLearnedBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const = 0;`
- L35 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L36 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/MachineLearnedBehaviorFactory.h` (Private)


#### struct `rl4::MachineLearnedBehaviorFactory`  
`struct MachineLearnedBehaviorFactory`  
_L13-19_
- L14 _public prototype_ `static MachineLearnedBehavior::Pointer create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, MemoryResource* memRes);`
- L18 _public prototype_ `static MachineLearnedBehavior::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/MachineLearnedBehaviorNullEvaluator.h` (Private)


#### class `rl4::MachineLearnedBehaviorNullEvaluator`  
`class MachineLearnedBehaviorNullEvaluator : public MachineLearnedBehaviorEvaluator`  
_L13-32_
- inherits: `MachineLearnedBehaviorEvaluator`
- L15 _public prototype_ `MachineLearnedBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L16 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t ) const override;`
- L17 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t , std::uint16_t ) const override;`
- L18 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t , std::uint16_t , std::uint16_t ) const override;`
- L21 _public prototype_ `void calculate(ControlsInputInstance* , MachineLearnedBehaviorOutputInstance* , std::uint16_t ) const override;`
- L24 _public prototype_ `void calculate(ControlsInputInstance* , MachineLearnedBehaviorOutputInstance* , std::uint16_t , std::uint16_t , std::uint16_t , std::uint16_t ) const override;`
- L30 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& ) override;`
- L31 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& ) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/MachineLearnedBehaviorNullOutputInstance.h` (Private)


#### class `rl4::MachineLearnedBehaviorNullOutputInstance`  
`class MachineLearnedBehaviorNullOutputInstance : public MachineLearnedBehaviorOutputInstance`  
_L9-15_
- inherits: `MachineLearnedBehaviorOutputInstance`
- L11 _public prototype_ `ArrayView<float> getMaskBuffer() override;`
- L12 _public prototype_ `ConstArrayView<float> getMaskBuffer() const override;`
- L13 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t ) const override;`
- L14 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t , std::uint16_t ) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/MachineLearnedBehaviorOutputInstance.h` (Private)


#### class `rl4::MachineLearnedBehaviorOutputInstance`  
`class MachineLearnedBehaviorOutputInstance`  
_L9-19_
- L11 _public typedef_ `using Pointer = UniqueInstance<MachineLearnedBehaviorOutputInstance>::PointerType;`
- L14 _public prototype_ `virtual ~MachineLearnedBehaviorOutputInstance();`
- L15 _public prototype_ `virtual ArrayView<float> getMaskBuffer() = 0;`
- L16 _public prototype_ `virtual ConstArrayView<float> getMaskBuffer() const = 0;`
- L17 _public prototype_ `virtual std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const = 0;`
- L18 _public prototype_ `virtual std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/CPUMachineLearnedBehaviorEvaluator.h` (Private)


#### class `rl4::ml::cpu::Evaluator`  
`class Evaluator : public MachineLearnedBehaviorEvaluator`  
_L21-58_
- inherits: `MachineLearnedBehaviorEvaluator`
- L27 _public prototype_ `Evaluator(const Configuration& config_, Matrix<LODSpec<std::uint16_t>>&& lods_, Matrix<OperationSet::Pointer>&& mlOperations_, Vector<Matrix<std::uint16_t>>&& bufferSizes_, std::uint32_t meshRegionCount_, OutputInstance::Factory instanceFactory_);`
- L33 _public prototype_ `MachineLearnedBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L34 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override;`
- L35 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L36 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L39 _public prototype_ `void calculate(ControlsInputInstance* inputs, MachineLearnedBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override;`
- L45 _public prototype_ `void calculate(ControlsInputInstance* inputs, MachineLearnedBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod) const override;`
- L48 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L49 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L52 _private member_ `const Configuration* config;`
- L53 _private member_ `Matrix<LODSpec<std::uint16_t>> lods;`
- L54 _private member_ `Matrix<OperationSet::Pointer> mlOperations;`
- L55 _private member_ `Vector<Matrix<std::uint16_t>> bufferSizes;`
- L56 _private member_ `std::uint32_t meshRegionCount;`
- L57 _private member_ `OutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rl4`
- L17 _namespace_ `namespace ml` (scope `rl4`)
- L19 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/CPUMachineLearnedBehaviorFactory.h` (Private)


#### class `rl4::ml::cpu::Factory`  
`class Factory`  
_L17-23_
- L19 _public prototype_ `static MachineLearnedBehaviorEvaluator::Pointer create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`
- L13 _namespace_ `namespace ml` (scope `rl4`)
- L15 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/CPUMachineLearnedBehaviorOutputInstance.h` (Private)


#### class `rl4::ml::cpu::OutputInstance`  
`class OutputInstance : public MachineLearnedBehaviorOutputInstance`  
_L23-55_
- inherits: `MachineLearnedBehaviorOutputInstance`
- L25 _public typedef_ `using Factory = std::function<Pointer(const Vector<Matrix<std::uint16_t>>&, std::uint32_t, MemoryResource*)>;`
- L28 _public prototype_ `OutputInstance(const Vector<Matrix<std::uint16_t>>& bufferSizes, std::uint32_t meshRegionCount, MemoryResource* memRes);`
- L29 _public prototype_ `ArrayView<float> getMaskBuffer() override;`
- L30 _public prototype_ `ConstArrayView<float> getMaskBuffer() const override;`
- L31 _public prototype_ `ArrayView<float> getOutputBuffer(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex);`
- L35 _public function_ `ConstArrayView<float*> getWorkBufferPtrs(std::uint16_t mlTypeIndex) const`
- L38 _public function_ `ConstArrayView<std::uint16_t> getWorkBufferHalfSizes(std::uint16_t mlTypeIndex) const`
- L42 _public function_ `ConstArrayView<std::uint16_t> getWorkBufferOffsetsPerOperationSet(std::uint16_t mlTypeIndex) const`
- L46 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override;`
- L47 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L50 _private member_ `AlignedVector<float> workBuffer;`
- L51 _private member_ `Matrix<float*> workBufferPtrs;`
- L52 _private member_ `Matrix<std::uint16_t> workBufferHalfSizes;`
- L53 _private member_ `Matrix<std::uint16_t> workBufferOffsetsPerOperationSet;`
- L54 _private member_ `Vector<float> maskBuffer;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace rl4`
- L19 _namespace_ `namespace ml` (scope `rl4`)
- L21 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/NeuralNet.h` (Private)


#### struct `rl4::ml::cpu::MatrixLayout`  
`struct MatrixLayout`  
_L18-35_
- desc: Describes the memory layout of a weight matrix: original dimensions, SIMD-padded dimensions, per-LOD output block views, and the input block view. Does not own any data.
- L19 _public member_ `Extent original;`
- L20 _public member_ `Extent padded;`
- L21 _public member_ `Vector<PaddedBlockView> rows;` — per-LOD output block views
- L22 _public member_ `PaddedBlockView cols;` — input block view
- L24 _public function_ `explicit MatrixLayout(MemoryResource* memRes) : original`
- L32 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `rl4::ml::cpu::NeuralNetLayer`  
`struct NeuralNetLayer`  
_L37-56_
- L38 _public member_ `MatrixLayout weights;`
- L39 _public member_ `Vector<float> activationFunctionParameters;`
- L40 _public member_ `dna::ActivationFunction activationFunction;`
- L41 _public member_ `std::size_t weightOffset;` — offset into NeuralNet::flatData
- L42 _public member_ `std::size_t biasOffset;` — offset into NeuralNet::flatData
- L44 _public function_ `explicit NeuralNetLayer(MemoryResource* memRes) : weights`
- L53 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `rl4::ml::cpu::NeuralNet`  
`struct NeuralNet`  
_L58-79_
- L59 _public member_ `Vector<NeuralNetLayer> layers;`
- L60 _public member_ `std::uint32_t maskIndex;`
- L61 _public member_ `FloatArray flatData;` — contiguous weights+biases for all layers, indexed via per-layer offsets
- L63 _public function_ `NeuralNet(MemoryResource* memRes) : layers`
- L69 _public function_ `NeuralNet(Vector<NeuralNetLayer>&& layers_, std::uint32_t maskIndex_, FloatArray&& flatData_) : layers`
- L76 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L12 _namespace_ `namespace ml` (scope `rl4`)
- L14 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/Operation.h` (Private)


#### enum `rl4::ml::cpu::OperationSetType`  
`enum class OperationSetType : std::uint16_t`  
_L33-44_
- L34 _public enumerator_ `MLP = 0`
- L35 _public enumerator_ `WeightedSum8 = 1`
- L36 _public enumerator_ `WeightedSum16 = 2`
- L37 _public enumerator_ `WeightedSum24 = 3`
- L38 _public enumerator_ `WeightedSum32 = 4`
- L39 _public enumerator_ `WeightedSum40 = 5`
- L40 _public enumerator_ `WeightedSum48 = 6`
- L41 _public enumerator_ `WeightedSum56 = 7`
- L42 _public enumerator_ `WeightedSum64 = 8`
- L43 _public enumerator_ `WeightedSum = WeightedSum64` — default alias: largest block size

#### struct `rl4::ml::cpu::OperationSet`  
`struct OperationSet`  
_L58-76_
- L59 _public typedef_ `using Pointer = UniqueInstance<OperationSet>::PointerType;`
- L61 _public prototype_ `virtual ~OperationSet();`
- L63 _public prototype_ `virtual void execute(ConstArrayView<std::uint16_t> activeOpIndices, std::uint16_t lod, ConstArrayView<float> masks, ArrayView<float> inputBuffer, std::size_t opSetWorkBufferOffset, ConstArrayView<float*> workBufferPtrs, ConstArrayView<std::uint16_t> workBufferHalfSizes, ConstArrayView<std::uint16_t> workBufferOffsetsPerOperationSet) const = 0;`
- L72 _public prototype_ `virtual OperationSetType getType() const = 0;`
- L74 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L75 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### struct `rl4::ml::cpu::Dependency`  
`struct Dependency`  
_L78-86_
- L79 _public member_ `std::uint16_t opSetIdx;`
- L80 _public member_ `std::uint16_t opIdx;`
- L83 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `rl4::ml::cpu::MLPOperationData`  
`struct MLPOperationData`  
_L88-109_
- L89 _public member_ `NeuralNet neuralNet;`
- L90 _public member_ `Vector<Dependency> inputDeps;` — cross-operation-set (opSetIdx, opIdx) pairs; empty if inputs come from controls
- L91 _public member_ `Vector<std::uint16_t> inputControlIndices;`
- L92 _public member_ `Vector<std::uint16_t> outputControlIndices;`
- L93 _public member_ `Vector<std::uint16_t> outputCounts;` — per-dep output count for the gather phase
- L94 _public member_ `Vector<std::uint16_t> outputCountsPerLOD;` — precomputed from layers.back().weights.rows[lod].size
- L95 _public member_ `Vector<float> defaultValues;`
- L97 _public member_ `std::uint16_t tailZeroCount;` — Padding floats a WeightedSum consumer may over-read past this op's outputs; 0 for well-formed DNA.
- L99 _public function_ `explicit MLPOperationData(MemoryResource* memRes) : neuralNet`

#### struct `rl4::ml::cpu::WeightedSumOperationData`  
`struct WeightedSumOperationData`  
_L111-121_
- L112 _public member_ `Vector<Dependency> inputDeps;` — cross-operation-set (opSetIdx, opIdx) pairs
- L113 _public member_ `Vector<float> weights;`
- L114 _public member_ `std::uint16_t outputCount;`
- L116 _public function_ `explicit WeightedSumOperationData(MemoryResource* memRes) : inputDeps`

#### struct `rl4::ml::cpu::OperationSetData`  
`struct OperationSetData`  
_L123-141_
- L124 _public member_ `OperationSetType type;`
- L125 _public member_ `Vector<WeightedSumOperationData> wsOps;`
- L126 _public member_ `Vector<MLPOperationData> mlpOps;`
- L127 _public member_ `bool hasMasks;`
- L129 _public function_ `explicit OperationSetData(MemoryResource* memRes) : type`
- L136 _public function_ `bool empty() const`

#### struct `rl4::ml::cpu::MLPOperationSet`  
`template<typename T, typename TF256, typename TF128> struct MLPOperationSet : OperationSet`  
_L144-375_
- inherits: `OperationSet`
- L145 _public member_ `Vector<MLPOperationData> ops;`
- L146 _public member_ `Vector<const T*> cachedLayerDataPtrs;`
- L147 _public member_ `bool hasMasks;`
- L149 _public function_ `explicit MLPOperationSet(MemoryResource* memRes) : ops`
- L155 _public function_ `explicit MLPOperationSet(Vector<MLPOperationData>&& ops_, bool hasMasks_, MemoryResource* memRes) : ops`
- L165 _public function_ `void execute(ConstArrayView<std::uint16_t> activeOpIndices, std::uint16_t lod, ConstArrayView<float> masks, ArrayView<float> inputBuffer, std::size_t opSetWorkBufferOffset, ConstArrayView<float*> workBufferPtrs, ConstArrayView<std::uint16_t> workBufferHalfSizes, ConstArrayView<std::uint16_t> workBufferOffsetsPerOperationSet) const override`
- L320 _public function_ `OperationSetType getType() const override`
- L324 _public function_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override`
- L363 _public function_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override`

#### struct `rl4::ml::cpu::InvokeN`  
`template<std::size_t Count, std::size_t Index = 0> struct InvokeN`  
_L378-384_
- L380 _public function_ `template<typename Fn> void operator()(Fn func)`

#### struct `rl4::ml::cpu::InvokeN`  
`template<std::size_t Count> struct InvokeN<Count, Count>`  
_L387-392_
- L380 _public function_ `template<typename Fn> void operator()(Fn func)`

#### struct `rl4::ml::cpu::WeightedSumOperationSet`  
`template<std::size_t BlockSize, typename TF256, typename TF128> struct WeightedSumOperationSet : OperationSet`  
_L395-505_
- inherits: `OperationSet`
- L396 _public member_ `Vector<WeightedSumOperationData> ops;`
- L398 _public function_ `explicit WeightedSumOperationSet(MemoryResource* memRes) : ops`
- L402 _public function_ `explicit WeightedSumOperationSet(Vector<WeightedSumOperationData>&& ops_, MemoryResource* ) : ops`
- L406 _public function_ `void execute(ConstArrayView<std::uint16_t> activeOpIndices, std::uint16_t lod, ConstArrayView<float> masks, ArrayView<float> inputBuffer, std::size_t opSetWorkBufferOffset, ConstArrayView<float*> workBufferPtrs, ConstArrayView<std::uint16_t> workBufferHalfSizes, ConstArrayView<std::uint16_t> workBufferOffsetsPerOperationSet) const override`
- L466 _public function_ `OperationSetType getType() const override`
- L487 _public function_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override`
- L499 _public function_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override`

#### struct `rl4::ml::cpu::OperationSetFactory`  
`template<typename T, typename TF256, typename TF128> struct OperationSetFactory`  
_L508-553_
- L509 _public typedef_ `using BasePointer = UniqueInstance<OperationSet>::PointerType;`
- L511 _public function_ `BasePointer operator()(OperationSetData&& data, MemoryResource* memRes)`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace rl4`
- L29 _namespace_ `namespace ml` (scope `rl4`)
- L31 _namespace_ `namespace cpu` (scope `rl4::ml`)
- L47 _function_ `template<typename Archive> void load(Archive& archive, OperationSetType& value)` (scope `rl4::ml::cpu`)
- L54 _function_ `template<typename Archive> void save(Archive& archive, OperationSetType& value)` (scope `rl4::ml::cpu`)
- L139 _function_ `std::all_of(mlpOps.begin(), mlpOps.end(), [](const MLPOperationData& op) { return op.neuralNet.layers.empty(); });` (scope `rl4::ml::cpu::OperationSetData::empty`)
- L444 _function_ `[&](std::size_t bi)` (scope `rl4::ml::cpu::WeightedSumOperationSet::execute`)
- L446 _function_ `InvokeN<blockCount>()([&](std::size_t bi) { sums[bi] += blocks[bi] * weight; });` (scope `rl4::ml::cpu::WeightedSumOperationSet::execute`)
- L448 _function_ `InvokeN<blockCount>()([&](std::size_t bi) { sums[bi].unalignedStore(pBuf + elem + TF256::size() * bi); });` (scope `rl4::ml::cpu::WeightedSumOperationSet::execute`)
- L515 _typedef_ `using OpSet = MLPOperationSet<T, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L519 _typedef_ `using OpSet = WeightedSumOperationSet<8, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L523 _typedef_ `using OpSet = WeightedSumOperationSet<16, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L527 _typedef_ `using OpSet = WeightedSumOperationSet<24, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L531 _typedef_ `using OpSet = WeightedSumOperationSet<32, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L535 _typedef_ `using OpSet = WeightedSumOperationSet<40, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L539 _typedef_ `using OpSet = WeightedSumOperationSet<48, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L543 _typedef_ `using OpSet = WeightedSumOperationSet<56, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)
- L548 _typedef_ `using OpSet = WeightedSumOperationSet<64, TF256, TF128>;` (scope `rl4::ml::cpu::OperationSetFactory::operator ()`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/LayerEvaluator.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`
- L11 _namespace_ `namespace ml` (scope `rl4`)
- L13 _namespace_ `namespace cpu` (scope `rl4::ml`)
- L17 _function_ `processBlocks8x1(const float* inputVectorEndAlignedTo4, const float* inputVectorEnd, const T* weights, TF128& sum1, TF128& sum2)` (scope `rl4::ml::cpu`)
- L33 _function_ `template<typename TF128, typename TActivationFunction, typename T> static FORCE_INLINE void processBlocks8x4(const float* inputVectorStart, const float* inputVectorEndAlignedTo4, const float* inputVectorEnd, const T* weights, const T* biases, const float* activationParams, float* outbuf)` (scope `rl4::ml::cpu`)
- L94 _function_ `template<typename TF128, typename T> static FORCE_INLINE void processBlocks4x1(const float* inputVectorEndAlignedTo8, const float* inputVectorEnd, const T* weights, TF128& sum1)` (scope `rl4::ml::cpu`)
- L109 _function_ `template<typename TF128, typename TActivationFunction, typename T> static FORCE_INLINE void processBlocks4x8(const float* inputVectorStart, const float* inputVectorEndAlignedTo8, const float* inputVectorEnd, const T* weights, const T* biases, const float* activationParams, float* outbuf)` (scope `rl4::ml::cpu`)
- L173 _function_ `template<typename T, typename TF256, typename TF128, template<class...> class TActivationFunction> static FORCE_INLINE void calculateBlock4(const T* weights, const T* biases, const float* activationParams, const PaddedBlockView& cols, const PaddedBlockView& rows, ConstArrayView<float> inputs, ArrayView<float> outputs)` (scope `rl4::ml::cpu`) — Raw-pointer overload: used by the set-based evaluator with pre-resolved pointers.

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/LeakyReLULayerEvaluator.h` (Private)


#### struct `rl4::ml::cpu::LeakyReLUActivationFunction`  
`template<typename TFVec> struct LeakyReLUActivationFunction`  
_L17-37_
- L19 _public function_ `void operator()(TFVec& sum, const float* activationParams)`
- L27 _public function_ `void operator()(TFVec& sum1, TFVec& sum2, const float* activationParams)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L12 _namespace_ `namespace ml` (scope `rl4`)
- L14 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/LinearLayerEvaluator.h` (Private)


#### struct `rl4::ml::cpu::LinearActivationFunction`  
`template<typename TFVec> struct LinearActivationFunction`  
_L16-23_
- L18 _public function_ `void operator()(TFVec& , const float* )`
- L21 _public function_ `void operator()(TFVec& , TFVec& , const float* )`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`
- L11 _namespace_ `namespace ml` (scope `rl4`)
- L13 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/ReLULayerEvaluator.h` (Private)


#### struct `rl4::ml::cpu::ReLUActivationFunction`  
`template<typename TFVec> struct ReLUActivationFunction`  
_L17-32_
- L19 _public function_ `void operator()(TFVec& sum, const float* )`
- L25 _public function_ `void operator()(TFVec& sum1, TFVec& sum2, const float* )`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L12 _namespace_ `namespace ml` (scope `rl4`)
- L14 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/SigmoidLayerEvaluator.h` (Private)


#### struct `rl4::ml::cpu::SigmoidActivationFunction`  
`template<typename TF128> struct SigmoidActivationFunction<TF128, typename std::enable_if<HasSize<TF128, 4ul>::value>::type>`  
_L23-58_
- L25 _public function_ `void operator()(TF128& sum, const float* )`
- L39 _public function_ `void operator()(TF128& sum1, TF128& sum2, const float* )`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace rl4`
- L15 _namespace_ `namespace ml` (scope `rl4`)
- L17 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/TanHLayerEvaluator.h` (Private)


#### struct `rl4::ml::cpu::TanHActivationFunction`  
`template<typename TF128> struct TanHActivationFunction<TF128, typename std::enable_if<HasSize<TF128, 4ul>::value>::type>`  
_L23-58_
- L25 _public function_ `void operator()(TF128& sum, const float* )`
- L39 _public function_ `void operator()(TF128& sum1, TF128& sum2, const float* )`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace rl4`
- L15 _namespace_ `namespace ml` (scope `rl4`)
- L17 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/ml/cpu/layers/Utils.h` (Private)


#### struct `rl4::ml::cpu::HasSize`  
`template<typename TFVec, std::size_t Size> struct HasSize`  
_L14-16_
- L15 _public member_ `static constexpr bool value = (TFVec::size() == Size);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`
- L9 _namespace_ `namespace ml` (scope `rl4`)
- L11 _namespace_ `namespace cpu` (scope `rl4::ml`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNet.h` (Private)


#### class `rl4::PSDNet`  
`class PSDNet`  
_L14-31_
- L16 _public typedef_ `using Pointer = UniqueInstance<PSDNet>::PointerType;`
- L19 _protected prototype_ `virtual ~PSDNet();`
- L22 _public prototype_ `virtual PSDNetOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const = 0;`
- L23 _public prototype_ `virtual std::uint16_t getPSDCount() const = 0;`
- L24 _public prototype_ `virtual ConstArrayView<std::uint16_t> getPSDInputIndicesForLOD(std::uint16_t lod) const = 0;`
- L25 _public prototype_ `virtual ConstArrayView<std::uint16_t> getPSDOutputIndicesForLOD(std::uint16_t lod) const = 0;`
- L26 _public prototype_ `virtual void calculate(ControlsInputInstance* inputInstance, PSDNetOutputInstance* outputInstance, std::uint16_t lod) const = 0;`
- L29 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L30 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNetFactory.h` (Private)


#### struct `rl4::PSDNetFactory`  
`struct PSDNetFactory`  
_L14-18_
- L16 _public prototype_ `create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, Controls* controls, MemoryResource* memRes);`
- L17 _public prototype_ `static PSDNet::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNetImpl.h` (Private)


#### struct `rl4::PSD`  
`struct PSD`  
_L15-24_
- L16 _public member_ `std::size_t offset;`
- L17 _public member_ `std::size_t size;`
- L18 _public member_ `float weight;`
- L21 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### class `rl4::PSDNetImpl`  
`class PSDNetImpl : public PSDNet`  
_L26-53_
- inherits: `PSDNet`
- L28 _public prototype_ `PSDNetImpl(PSDNetOutputInstance::Factory instanceFactory_, MemoryResource* memRes);`
- L29 _public prototype_ `PSDNetImpl(Matrix<std::uint16_t>&& inputLODs_, Matrix<std::uint16_t>&& outputLODs_, Vector<std::uint16_t>&& inputIndicesPerPSD_, Vector<PSD>&& psds_, std::uint16_t psdMinIndex_, std::uint16_t psdMaxIndex_, PSDNetOutputInstance::Factory instanceFactory_);`
- L37 _public prototype_ `PSDNetOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L38 _public prototype_ `std::uint16_t getPSDCount() const override;`
- L39 _public prototype_ `ConstArrayView<std::uint16_t> getPSDInputIndicesForLOD(std::uint16_t lod) const override;`
- L40 _public prototype_ `ConstArrayView<std::uint16_t> getPSDOutputIndicesForLOD(std::uint16_t lod) const override;`
- L41 _public prototype_ `void calculate(ControlsInputInstance* inputInstance, PSDNetOutputInstance* outputInstance, std::uint16_t lod) const override;`
- L42 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L43 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L46 _private member_ `Matrix<std::uint16_t> inputLODs;`
- L47 _private member_ `Matrix<std::uint16_t> outputLODs;`
- L48 _private member_ `Vector<std::uint16_t> inputIndicesPerPSD;`
- L49 _private member_ `Vector<PSD> psds;`
- L50 _private member_ `std::uint16_t psdMinIndex;`
- L51 _private member_ `std::uint16_t psdMaxIndex;`
- L52 _private member_ `PSDNetOutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNetImplOutputInstance.h` (Private)


#### class `rl4::PSDNetImplOutputInstance`  
`class PSDNetImplOutputInstance : public PSDNetOutputInstance`  
_L12-20_
- inherits: `PSDNetOutputInstance`
- L14 _public prototype_ `PSDNetImplOutputInstance(std::uint16_t controlCount, MemoryResource* memRes);`
- L15 _public prototype_ `void resetClampBuffer() override;`
- L16 _public prototype_ `ArrayView<float> getClampBuffer() override;`
- L19 _private member_ `Vector<float> clampBuffer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNetNull.h` (Private)


#### class `rl4::PSDNetNull`  
`class PSDNetNull : public PSDNet`  
_L13-22_
- inherits: `PSDNet`
- L15 _public prototype_ `PSDNetOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L16 _public prototype_ `std::uint16_t getPSDCount() const override;`
- L17 _public prototype_ `ConstArrayView<std::uint16_t> getPSDInputIndicesForLOD(std::uint16_t ) const override;`
- L18 _public prototype_ `ConstArrayView<std::uint16_t> getPSDOutputIndicesForLOD(std::uint16_t ) const override;`
- L19 _public prototype_ `void calculate(ControlsInputInstance* , PSDNetOutputInstance* , std::uint16_t ) const override;`
- L20 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& ) override;`
- L21 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& ) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNetNullOutputInstance.h` (Private)


#### class `rl4::PSDNetNullOutputInstance`  
`class PSDNetNullOutputInstance : public PSDNetOutputInstance`  
_L12-16_
- inherits: `PSDNetOutputInstance`
- L14 _public prototype_ `void resetClampBuffer() override;`
- L15 _public prototype_ `ArrayView<float> getClampBuffer() override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/psdnet/PSDNetOutputInstance.h` (Private)


#### class `rl4::PSDNetOutputInstance`  
`class PSDNetOutputInstance`  
_L9-18_
- L11 _public typedef_ `using Pointer = UniqueInstance<PSDNetOutputInstance>::PointerType;`
- L12 _public typedef_ `using Factory = std::function<Pointer(MemoryResource*)>;`
- L15 _public prototype_ `virtual ~PSDNetOutputInstance();`
- L16 _public prototype_ `virtual void resetClampBuffer() = 0;`
- L17 _public prototype_ `virtual ArrayView<float> getClampBuffer() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/RBFBehavior.h` (Private)


#### class `rl4::RBFBehavior`  
`class RBFBehavior`  
_L17-44_
- L19 _public typedef_ `using Pointer = UniqueInstance<RBFBehavior>::PointerType;`
- L22 _public prototype_ `explicit RBFBehavior(RBFBehaviorEvaluator::Pointer evaluator_);`
- L24 _public prototype_ `RBFBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const;`
- L25 _public prototype_ `ConstArrayView<std::uint16_t> getSolverIndicesForLOD(std::uint16_t lod) const;`
- L26 _public prototype_ `void calculate(ControlsInputInstance* inputs, RBFBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod) const;`
- L27 _public prototype_ `void calculate(ControlsInputInstance* inputs, RBFBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod, std::uint16_t solverIndex) const;`
- L33 _public function_ `template<class Archive> void load(Archive& archive)`
- L38 _public function_ `template<class Archive> void save(Archive& archive)`
- L43 _private member_ `RBFBehaviorEvaluator::Pointer evaluator;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/RBFBehaviorEvaluator.h` (Private)


#### class `rl4::RBFBehaviorEvaluator`  
`class RBFBehaviorEvaluator`  
_L12-31_
- L14 _public typedef_ `using Pointer = UniqueInstance<RBFBehaviorEvaluator>::PointerType;`
- L17 _protected prototype_ `virtual ~RBFBehaviorEvaluator();`
- L20 _public prototype_ `virtual RBFBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const = 0;`
- L21 _public prototype_ `virtual ConstArrayView<std::uint16_t> getSolverIndicesForLOD(std::uint16_t lod) const = 0;`
- L22 _public prototype_ `virtual void calculate(ControlsInputInstance* inputs, RBFBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod) const = 0;`
- L25 _public prototype_ `virtual void calculate(ControlsInputInstance* inputs, RBFBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod, std::uint16_t solverIndex) const = 0;`
- L29 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive) = 0;`
- L30 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/RBFBehaviorFactory.h` (Private)


#### struct `rl4::RBFBehaviorFactory`  
`struct RBFBehaviorFactory`  
_L13-19_
- L14 _public prototype_ `static RBFBehavior::Pointer create(const Configuration& config, RigMetadata* meta, const dna::Reader* reader, MemoryResource* memRes);`
- L18 _public prototype_ `static RBFBehavior::Pointer create(const Configuration& config, RigMetadata* meta, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/RBFBehaviorNullEvaluator.h` (Private)


#### class `rl4::RBFBehaviorNullEvaluator`  
`class RBFBehaviorNullEvaluator : public RBFBehaviorEvaluator`  
_L13-26_
- inherits: `RBFBehaviorEvaluator`
- L15 _public prototype_ `RBFBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override;`
- L16 _public prototype_ `ConstArrayView<std::uint16_t> getSolverIndicesForLOD(std::uint16_t ) const override;`
- L17 _public prototype_ `void calculate(ControlsInputInstance* , RBFBehaviorOutputInstance* , std::uint16_t ) const override;`
- L20 _public prototype_ `void calculate(ControlsInputInstance* , RBFBehaviorOutputInstance* , std::uint16_t , std::uint16_t ) const override;`
- L24 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& ) override;`
- L25 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& ) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/RBFBehaviorNullOutputInstance.h` (Private)


#### class `rl4::RBFBehaviorNullOutputInstance`  
`class RBFBehaviorNullOutputInstance : public RBFBehaviorOutputInstance`  
_L9-14_
- inherits: `RBFBehaviorOutputInstance`
- L11 _public prototype_ `ArrayView<float> getInputBuffer(std::uint16_t ) override;`
- L12 _public prototype_ `ArrayView<float> getIntermediateWeightsBuffer(std::uint16_t ) override;`
- L13 _public prototype_ `ArrayView<float> getOutputWeightsBuffer(std::uint16_t ) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/RBFBehaviorOutputInstance.h` (Private)


#### class `rl4::RBFBehaviorOutputInstance`  
`class RBFBehaviorOutputInstance`  
_L9-18_
- L11 _public typedef_ `using Pointer = UniqueInstance<RBFBehaviorOutputInstance>::PointerType;`
- L14 _public prototype_ `virtual ~RBFBehaviorOutputInstance();`
- L15 _public prototype_ `virtual ArrayView<float> getInputBuffer(std::uint16_t solverIndex) = 0;`
- L16 _public prototype_ `virtual ArrayView<float> getIntermediateWeightsBuffer(std::uint16_t solverIndex) = 0;`
- L17 _public prototype_ `virtual ArrayView<float> getOutputWeightsBuffer(std::uint16_t solverIndex) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/cpu/AdditiveRBFSolver.h` (Private)


#### class `rl4::AdditiveRBFSolver`  
`class AdditiveRBFSolver : public RBFSolver`  
_L9-16_
- inherits: `RBFSolver`
- L11 _public prototype_ `explicit AdditiveRBFSolver(MemoryResource* memRes);`
- L12 _public prototype_ `AdditiveRBFSolver(const RBFSolverRecipe& recipe, MemoryResource* memRes);`
- L14 _public prototype_ `RBFSolverType getSolverType() const override;`
- L15 _public prototype_ `void solve(ArrayView<float> input, ArrayView<float> intermediateWeights, ArrayView<float> outputWeights) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/cpu/CPURBFBehaviorEvaluator.h` (Private)


#### class `rl4::rbf::cpu::Evaluator`  
`template<typename T, typename TF256, typename TF128> class Evaluator : public RBFBehaviorEvaluator`  
_L26-199_
- inherits: `RBFBehaviorEvaluator`
- L28 _public typedef_ `using SolverVectorType = Vector<RBFSolver::Pointer>;`
- L34 _public function_ `Evaluator(LODSpec<std::uint16_t>&& lods_, SolverVectorType&& solvers_, Matrix<std::uint16_t>&& solverRawControlInputIndices_, Matrix<std::uint16_t>&& solverRawControlOutputIndices_, Matrix<std::uint16_t>&& solverPoseIndices_, Matrix<std::uint16_t>&& poseInputControlIndices_, Matrix<std::uint16_t>&& poseOutputControlIndices_, Matrix<float>&& poseOutputControlWeights_, Vector<std::uint16_t>&& inputCountPerSolver_, Vector<std::uint16_t>&& targetCountPerSolver_, OutputInstance::Factory&& instanceFactory_) : lods`
- L58 _public function_ `RBFBehaviorOutputInstance::Pointer createInstance(MemoryResource* instanceMemRes) const override`
- L62 _public function_ `ConstArrayView<std::uint16_t> getSolverIndicesForLOD(std::uint16_t lod) const override`
- L67 _public function_ `void calculate(std::uint16_t solverIndex, ArrayView<float> rawControls, ArrayView<float> inputBuffer, ArrayView<float> intermediateWeightsBuffer, ArrayView<float> outputWeightsBuffer) const`
- L109 _public function_ `void calculate(ControlsInputInstance* inputs, RBFBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod) const override`
- L125 _public function_ `void calculate(ControlsInputInstance* inputs, RBFBehaviorOutputInstance* intermediateOutputs, std::uint16_t lod, std::uint16_t solverIndex) const override`
- L140 _public function_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override`
- L168 _public function_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override`
- L188 _private member_ `LODSpec<std::uint16_t> lods;`
- L189 _private member_ `SolverVectorType solvers;`
- L190 _private member_ `Matrix<std::uint16_t> solverRawControlInputIndices;`
- L191 _private member_ `Matrix<std::uint16_t> solverRawControlOutputIndices;`
- L192 _private member_ `Matrix<std::uint16_t> solverPoseIndices;`
- L193 _private member_ `Matrix<std::uint16_t> poseInputControlIndices;`
- L194 _private member_ `Matrix<std::uint16_t> poseOutputControlIndices;`
- L195 _private member_ `Matrix<float> poseOutputControlWeights;`
- L196 _private member_ `Vector<std::uint16_t> inputCountPerSolver;`
- L197 _private member_ `Vector<std::uint16_t> targetCountPerSolver;`
- L198 _private member_ `OutputInstance::Factory instanceFactory;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace rl4`
- L21 _namespace_ `namespace rbf` (scope `rl4`)
- L23 _namespace_ `namespace cpu` (scope `rl4::rbf`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/cpu/CPURBFBehaviorFactory.h` (Private)


#### class `rl4::rbf::cpu::Factory`  
`template<typename T, typename TF256, typename TF128> class Factory`  
_L25-159_
- L27 _public function_ `static RBFBehaviorEvaluator::Pointer create(RigMetadata* meta, const dna::Reader* reader, MemoryResource* memRes)`
- L148 _private function_ `static LODSpec<std::uint16_t> computeLODs(const dna::RBFBehaviorReader* reader, MemoryResource* memRes)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace rl4`
- L20 _namespace_ `namespace rbf` (scope `rl4`)
- L22 _namespace_ `namespace cpu` (scope `rl4::rbf`)
- L41 _function_ `auto instanceFactory = [](ConstArrayView<std::uint16_t> inputCounts, ConstArrayView<std::uint16_t> targetCounts, MemoryResource* instanceMemRes)` (scope `rl4::rbf::cpu::Factory::create`)
- L42 _typedef_ `using OutputInstancePointer = UniqueInstance<OutputInstance, RBFBehaviorOutputInstance>;` (scope `rl4::rbf::cpu::Factory::create::__anon873544f40102`)
- L74 _function_ `angConv = [](float angle)` (scope `rl4::rbf::cpu::Factory::create`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/cpu/CPURBFBehaviorOutputInstance.h` (Private)


#### class `rl4::rbf::cpu::OutputInstance`  
`class OutputInstance : public RBFBehaviorOutputInstance`  
_L23-39_
- inherits: `RBFBehaviorOutputInstance`
- L25 _public typedef_ `using Factory = std::function<Pointer(ConstArrayView<std::uint16_t>, ConstArrayView<std::uint16_t>, MemoryResource*)>;`
- L28 _public prototype_ `OutputInstance(ConstArrayView<std::uint16_t> inputCountPerSolver, ConstArrayView<std::uint16_t> targetCountPerSolver, MemoryResource* memRes);`
- L31 _public prototype_ `ArrayView<float> getInputBuffer(std::uint16_t solverIndex) override;`
- L32 _public prototype_ `ArrayView<float> getIntermediateWeightsBuffer(std::uint16_t solverIndex) override;`
- L33 _public prototype_ `ArrayView<float> getOutputWeightsBuffer(std::uint16_t solverIndex) override;`
- L36 _private member_ `Vector<AlignedVector<float>> inputBuffers;`
- L37 _private member_ `Vector<AlignedVector<float>> intermediateWeightsBuffers;`
- L38 _private member_ `Vector<AlignedVector<float>> outputWeightsBuffers;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace rl4`
- L19 _namespace_ `namespace rbf` (scope `rl4`)
- L21 _namespace_ `namespace cpu` (scope `rl4::rbf`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/cpu/InterpolativeRBFSolver.h` (Private)


#### class `rl4::InterpolativeRBFSolver`  
`class InterpolativeRBFSolver : public RBFSolver`  
_L9-23_
- inherits: `RBFSolver`
- L11 _public prototype_ `explicit InterpolativeRBFSolver(const RBFSolverRecipe& recipe, MemoryResource* memRes);`
- L12 _public prototype_ `explicit InterpolativeRBFSolver(MemoryResource* memRes);`
- L14 _public prototype_ `RBFSolverType getSolverType() const override;`
- L15 _public prototype_ `void solve(ArrayView<float> input, ArrayView<float> intermediateWeights, ArrayView<float> outputWeights) const override;`
- L16 _public prototype_ `void load(terse::BinaryInputArchive<BoundedIOStream>& archive) override;`
- L17 _public prototype_ `void save(terse::BinaryOutputArchive<BoundedIOStream>& archive) override;`
- L19 _public prototype_ `const Matrix<float>& getCoefficients() const;`
- L22 _private member_ `Matrix<float> coefficients;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/rbf/cpu/RBFSolver.h` (Private)


#### struct `rl4::RBFSolverRecipe`  
`struct RBFSolverRecipe`  
_L25-37_
- L26 _public member_ `RBFSolverType solverType;`
- L27 _public member_ `RBFDistanceMethod distanceMethod;`
- L28 _public member_ `RBFFunctionType weightFunction;`
- L29 _public member_ `RBFNormalizeMethod normalizeMethod;`
- L30 _public member_ `TwistAxis twistAxis;`
- L31 _public member_ `bool isAutomaticRadius;`
- L32 _public member_ `float radius;`
- L33 _public member_ `float weightThreshold;`
- L34 _public member_ `std::uint16_t rawControlCount;`
- L35 _public member_ `ConstArrayView<float> targetValues;`
- L36 _public member_ `ConstArrayView<float> targetScales;`

#### class `rl4::RBFSolver`  
`class RBFSolver`  
_L39-84_
- L41 _public typedef_ `using Pointer = UniqueInstance<RBFSolver>::PointerType;`
- L42 _public typedef_ `using DistanceWeightFun = std::function<void(ConstArrayView<AlignedVector<float>>, ConstArrayView<float>, ArrayView<float>, float)>;`
- L44 _public typedef_ `using InputConvertFun = std::function<void(ArrayView<float>)>;`
- L47 _public prototype_ `static Pointer create(RBFSolverRecipe recipe, MemoryResource* memRes);`
- L50 _public prototype_ `explicit RBFSolver(MemoryResource* memRes);`
- L51 _public prototype_ `RBFSolver(const RBFSolverRecipe& recipe, MemoryResource* memRes);`
- L53 _public prototype_ `virtual ~RBFSolver();`
- L55 _public prototype_ `virtual RBFSolverType getSolverType() const = 0;`
- L56 _public prototype_ `virtual void solve(ArrayView<float> input, ArrayView<float> intermediateWeights, ArrayView<float> outputWeights) const = 0;`
- L58 _public prototype_ `virtual void load(terse::BinaryInputArchive<BoundedIOStream>& archive);`
- L59 _public prototype_ `virtual void save(terse::BinaryOutputArchive<BoundedIOStream>& archive);`
- L61 _public prototype_ `ConstArrayView<AlignedVector<float>> getTargets() const;`
- L62 _public prototype_ `ConstArrayView<float> getTargetScales() const;`
- L63 _public prototype_ `float getRadius() const;`
- L64 _public prototype_ `float getWeightThreshold() const;`
- L65 _public prototype_ `RBFDistanceMethod getDistanceMethod() const;`
- L66 _public prototype_ `RBFFunctionType getWeightFunction() const;`
- L67 _public prototype_ `RBFNormalizeMethod getNormalizeMethod() const;`
- L68 _public prototype_ `TwistAxis getTwistAxis() const;`
- L71 _protected prototype_ `void normalizeAndCutOff(ArrayView<float> outputWeights) const;`
- L74 _protected member_ `Vector<AlignedVector<float>> targets;`
- L75 _protected member_ `Vector<float> targetScale;`
- L76 _protected member_ `DistanceWeightFun getDistanceWeight;`
- L77 _protected member_ `InputConvertFun convertInput;`
- L78 _protected member_ `float radius;`
- L79 _protected member_ `float weightThreshold;`
- L80 _protected member_ `RBFDistanceMethod distanceMethod;`
- L81 _protected member_ `RBFFunctionType weightFunction;`
- L82 _protected member_ `RBFNormalizeMethod normalizeMethod;`
- L83 _protected member_ `TwistAxis twistAxis;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/riglogic/ConfigurationSerializer.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`
- L10 _function_ `template<class Archive> void serialize(Archive& archive, Configuration& config)` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/riglogic/RigInstanceImpl.h` (Private)


#### class `rl4::RigInstanceImpl`  
`class RigInstanceImpl : public RigInstance`  
_L22-92_
- inherits: `RigInstance`
- L24 _public prototype_ `RigInstanceImpl(RigMetadata* meta, RigLogicImpl* rigLogic, MemoryResource* memRes_);`
- L26 _public prototype_ `std::uint16_t getGUIControlCount() const override;`
- L27 _public prototype_ `float getGUIControl(std::uint16_t index) const override;`
- L28 _public prototype_ `void setGUIControl(std::uint16_t index, float value) override;`
- L29 _public prototype_ `ArrayView<float> getGUIControlValues() override;`
- L30 _public prototype_ `ConstArrayView<float> getGUIControlValues() const override;`
- L32 _public prototype_ `std::uint16_t getRawControlCount() const override;`
- L33 _public prototype_ `float getRawControl(std::uint16_t index) const override;`
- L34 _public prototype_ `void setRawControl(std::uint16_t index, float value) override;`
- L35 _public prototype_ `ArrayView<float> getRawControlValues() override;`
- L36 _public prototype_ `ConstArrayView<float> getRawControlValues() const override;`
- L38 _public prototype_ `std::uint16_t getPSDControlCount() const override;`
- L39 _public prototype_ `float getPSDControl(std::uint16_t index) const override;`
- L40 _public prototype_ `ConstArrayView<float> getPSDControlValues() const override;`
- L42 _public prototype_ `std::uint16_t getMLControlCount() const override;`
- L43 _public prototype_ `float getMLControl(std::uint16_t index) const override;`
- L44 _public prototype_ `ConstArrayView<float> getMLControlValues() const override;`
- L46 _public prototype_ `std::uint16_t getMLTypeCount() const override;`
- L47 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override;`
- L48 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L49 _public prototype_ `ConstArrayView<float> getMLMaskValues() const override;`
- L50 _public prototype_ `ArrayView<float> getMLMaskValues() override;`
- L52 _public prototype_ `std::uint16_t getRBFControlCount() const override;`
- L53 _public prototype_ `float getRBFControl(std::uint16_t index) const override;`
- L54 _public prototype_ `ConstArrayView<float> getRBFControlValues() const override;`
- L56 _public prototype_ `std::uint16_t getLOD() const override;`
- L57 _public prototype_ `void setLOD(std::uint16_t level) override;`
- L59 _public prototype_ `ConstArrayView<float> getJointOutputs() const override;`
- L60 _public prototype_ `ConstArrayView<float> getBlendShapeOutputs() const override;`
- L61 _public prototype_ `ConstArrayView<float> getAnimatedMapOutputs() const override;`
- L63 _public prototype_ `ControlsInputInstance* getControlsInputInstance();`
- L64 _public prototype_ `MachineLearnedBehaviorOutputInstance* getMachineLearnedBehaviorOutputInstance();`
- L65 _public prototype_ `RBFBehaviorOutputInstance* getRBFBehaviorOutputInstance();`
- L66 _public prototype_ `PSDNetOutputInstance* getPSDNetOutputInstance();`
- L67 _public prototype_ `JointsOutputInstance* getJointsOutputInstance();`
- L68 _public prototype_ `BlendShapesOutputInstance* getBlendShapesOutputInstance();`
- L69 _public prototype_ `AnimatedMapsOutputInstance* getAnimatedMapOutputInstance();`
- L71 _public prototype_ `MemoryResource* getMemoryResource();`
- L74 _private member_ `MemoryResource* memRes;`
- L76 _private member_ `std::uint16_t lodMaxLevel;`
- L77 _private member_ `std::uint16_t lodLevel;`
- L78 _private member_ `std::uint16_t guiControlCount;`
- L79 _private member_ `std::uint16_t rawControlCount;`
- L80 _private member_ `std::uint16_t psdControlCount;`
- L81 _private member_ `std::uint16_t mlControlCount;`
- L82 _private member_ `std::uint16_t rbfControlCount;`
- L83 _private member_ `std::uint16_t mlTypeCount;`
- L85 _private member_ `ControlsInputInstance::Pointer controlsInstance;`
- L86 _private member_ `MachineLearnedBehaviorOutputInstance::Pointer machineLearnedBehaviorInstance;`
- L87 _private member_ `RBFBehaviorOutputInstance::Pointer rbfBehaviorInstance;`
- L88 _private member_ `PSDNetOutputInstance::Pointer psdNetInstance;`
- L89 _private member_ `JointsOutputInstance::Pointer jointsInstance;`
- L90 _private member_ `BlendShapesOutputInstance::Pointer blendShapesInstance;`
- L91 _private member_ `AnimatedMapsOutputInstance::Pointer animatedMapsInstance;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/riglogic/RigLogicImpl.h` (Private)


#### class `rl4::RigLogicImpl`  
`class RigLogicImpl : public RigLogic`  
_L25-101_
- inherits: `RigLogic`
- L27 _public prototype_ `RigLogicImpl(const Configuration& config_, ActiveFeatures activeFeatures_, RigMetadata::Pointer meta_, Controls::Pointer controls_, MachineLearnedBehavior::Pointer machineLearnedBehavior_, RBFBehavior::Pointer rbfBehavior_, PSDNet::Pointer psds_, Joints::Pointer joints_, BlendShapes::Pointer blendShapes_, AnimatedMaps::Pointer animatedMaps_, MemoryResource* memRes_);`
- L39 _public prototype_ `void dump(BoundedIOStream* destination) const override;`
- L40 _public prototype_ `const Configuration& getConfiguration() const override;`
- L41 _public prototype_ `RigMetadata* getRigMetadata() const;`
- L42 _public prototype_ `std::uint16_t getLODCount() const override;`
- L43 _public prototype_ `ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const override;`
- L44 _public prototype_ `ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L47 _public prototype_ `ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const override;`
- L48 _public prototype_ `ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const override;`
- L49 _public prototype_ `ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const override;`
- L50 _public prototype_ `ConstArrayView<float> getNeutralJointValues() const override;`
- L51 _public prototype_ `ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const override;`
- L52 _public prototype_ `std::uint16_t getJointGroupCount() const override;`
- L53 _public prototype_ `std::uint16_t getRBFSolverCount() const override;`
- L54 _public prototype_ `std::uint16_t getTwistCount() const override;`
- L55 _public prototype_ `std::uint16_t getSwingCount() const override;`
- L56 _public prototype_ `std::uint16_t getMeshCount() const override;`
- L57 _public prototype_ `std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const override;`
- L58 _public prototype_ `std::uint16_t getMLTypeCount() const override;`
- L59 _public prototype_ `std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const override;`
- L60 _public prototype_ `std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const override;`
- L62 _public prototype_ `ControlsInputInstance::Pointer createControlsInstance(MemoryResource* instanceMemRes) const;`
- L63 _public prototype_ `MachineLearnedBehaviorOutputInstance::Pointer createMachineLearnedBehaviorInstance(MemoryResource* instanceMemRes) const;`
- L64 _public prototype_ `RBFBehaviorOutputInstance::Pointer createRBFBehaviorInstance(MemoryResource* instanceMemRes) const;`
- L65 _public prototype_ `PSDNetOutputInstance::Pointer createPSDNetInstance(MemoryResource* instanceMemRes) const;`
- L66 _public prototype_ `JointsOutputInstance::Pointer createJointsInstance(MemoryResource* instanceMemRes) const;`
- L67 _public prototype_ `BlendShapesOutputInstance::Pointer createBlendShapesInstance(MemoryResource* instanceMemRes) const;`
- L68 _public prototype_ `AnimatedMapsOutputInstance::Pointer createAnimatedMapsInstance(MemoryResource* instanceMemRes) const;`
- L70 _public prototype_ `void mapGUIToRawControls(RigInstance* instance) const override;`
- L71 _public prototype_ `void mapRawToGUIControls(RigInstance* instance) const override;`
- L72 _public prototype_ `void calculateMLControls(RigInstance* instance) const override;`
- L73 _public prototype_ `void calculateMLControls(RigInstance* instance, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const override;`
- L77 _public prototype_ `void calculateRBFControls(RigInstance* instance) const override;`
- L78 _public prototype_ `void calculateRBFControls(RigInstance* instance, std::uint16_t solverIndex) const override;`
- L79 _public prototype_ `void calculatePSDControls(RigInstance* instance) const override;`
- L80 _public prototype_ `void calculateJoints(RigInstance* instance) const override;`
- L81 _public prototype_ `void calculateJoints(RigInstance* instance, std::uint16_t jointGroupIndex) const override;`
- L82 _public prototype_ `void calculateBlendShapes(RigInstance* instance) const override;`
- L83 _public prototype_ `void calculateAnimatedMaps(RigInstance* instance) const override;`
- L84 _public prototype_ `void calculate(RigInstance* instance) const override;`
- L85 _public prototype_ `void collectCalculationStats(const RigInstance* instance, Stats* stats) const override;`
- L87 _public prototype_ `MemoryResource* getMemoryResource();`
- L90 _private member_ `MemoryResource* memRes;`
- L91 _private member_ `Configuration config;`
- L92 _private member_ `ActiveFeatures activeFeatures;`
- L93 _private member_ `RigMetadata::Pointer meta;`
- L94 _private member_ `Controls::Pointer controls;`
- L95 _private member_ `MachineLearnedBehavior::Pointer machineLearnedBehavior;`
- L96 _private member_ `RBFBehavior::Pointer rbfBehavior;`
- L97 _private member_ `PSDNet::Pointer psds;`
- L98 _private member_ `Joints::Pointer joints;`
- L99 _private member_ `BlendShapes::Pointer blendShapes;`
- L100 _private member_ `AnimatedMaps::Pointer animatedMaps;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/riglogic/RigMetadata.h` (Private)


#### enum `rl4::InitializationMethod`  
`enum class InitializationMethod : std::uint16_t`  
_L12-15_
- L13 _public enumerator_ `Create`
- L14 _public enumerator_ `Restore`

#### enum `rl4::EvaluatorType`  
`enum class EvaluatorType : std::uint16_t`  
_L17-21_
- L18 _public enumerator_ `Auto`
- L19 _public enumerator_ `Null`
- L20 _public enumerator_ `Concrete`

#### struct `rl4::RigMetadata`  
`struct RigMetadata`  
_L23-128_
- L24 _public typedef_ `using Pointer = UniqueInstance<RigMetadata>::PointerType;`
- L26 _public member_ `tdm::coord_sys coordinateSystem;`
- L27 _public member_ `tdm::rot_seq rotationSequence;`
- L28 _public member_ `tdm::rot_sign rotationSigns;`
- L29 _public member_ `std::uint16_t lodCount;`
- L30 _public member_ `std::uint16_t guiControlCount;`
- L31 _public member_ `std::uint16_t rawControlCount;`
- L32 _public member_ `std::uint16_t psdControlCount;`
- L33 _public member_ `std::uint16_t mlControlCount;`
- L34 _public member_ `std::uint16_t rbfControlCount;`
- L35 _public member_ `std::uint16_t jointGroupCount;`
- L36 _public member_ `std::uint16_t jointAttributeCount;`
- L37 _public member_ `std::uint16_t blendShapeCount;`
- L38 _public member_ `std::uint16_t animatedMapCount;`
- L39 _public member_ `std::uint16_t mlTypeCount;`
- L40 _public member_ `std::uint16_t rbfSolverCount;`
- L41 _public member_ `std::uint16_t twistCount;`
- L42 _public member_ `std::uint16_t swingCount;`
- L43 _public member_ `Vector<std::uint16_t> evaluators;`
- L45 _public member_ `InitializationMethod initializationMethod;` — Non-serialized, runtime parameter
- L47 _public function_ `static Pointer create(const Configuration& config, const dna::Reader* reader, MemoryResource* memRes, InitializationMethod initializationMethod)`
- L75 _public function_ `explicit RigMetadata(MemoryResource* memRes, InitializationMethod initializationMethod_) : coordinateSystem`
- L98 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L119 _public function_ `EvaluatorType popFrontEvaluator()`
- L125 _public function_ `void pushBackEvaluator(EvaluatorType id)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/system/simd/Detect.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define RL_BUILD_WITH_SSE 1`
- L13 _macro_ `#define RL_BUILD_WITH_HALF_FLOATS 1`
- L21 _macro_ `#define RL_BUILD_WITH_AVX 1`
- L32 _macro_ `#define RL_BUILD_WITH_NEON 1`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/system/simd/SIMD.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define TRIMD_ENABLE_RUNTIME_FEATURE_DETECTION`
- L15 _macro_ `#define TRIMD_ENABLE_F16C`
- L18 _macro_ `#define TRIMD_ENABLE_AVX`
- L21 _macro_ `#define TRIMD_ENABLE_SSE`
- L34 _macro_ `#define TRIMD_ENABLE_NEON_FP16`
- L36 _macro_ `#define TRIMD_ENABLE_NEON`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/system/simd/Utils.h` (Private)


#### struct `rl4::ActiveFeatures`  
`struct ActiveFeatures`  
_L12-15_
- L13 _public member_ `CalculationType calculationType;`
- L14 _public member_ `FloatingPointType floatingPointType;`

#### struct `rl4::RuntimeTemplateInstantiator`  
`struct RuntimeTemplateInstantiator`  
_L94-140_
- L95 _public member_ `const Configuration* config;`
- L98 _public function_ `template<template<class...> class TClass, class TReturnType, typename... Args> TReturnType invoke(Args&&... args)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L17 _function_ `inline bool operator==(const ActiveFeatures& lhs, const ActiveFeatures& rhs)` (scope `rl4`)
- L21 _function_ `inline bool operator!=(const ActiveFeatures& lhs, const ActiveFeatures& rhs)` (scope `rl4`)
- L25 _function_ `inline ActiveFeatures getActiveFeatures(const Configuration& config)` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/types/Extent.h` (Private)


#### struct `rl4::Extent`  
`struct Extent`  
_L9-21_
- L10 _public member_ `std::uint32_t rows;`
- L11 _public member_ `std::uint32_t cols;`
- L13 _public function_ `std::uint32_t size() const`
- L18 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`
- L23 _function_ `inline bool operator==(const Extent& lhs, const Extent& rhs)` (scope `rl4`)
- L27 _function_ `inline bool operator!=(const Extent& lhs, const Extent& rhs)` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/types/LODSpec.h` (Private)


#### struct `rl4::LODSpec`  
`template<typename T> struct LODSpec`  
_L10-30_
- L12 _public member_ `Matrix<T> indicesPerLOD;`
- L14 _public member_ `T count;` — Actual object count that we are LODing eg. RBF solver count, neural network count...
- L16 _public function_ `explicit LODSpec(MemoryResource* memRes) : indicesPerLOD`
- L21 _public function_ `LODSpec(Matrix<T>&& indicesPerLOD_, T count_) : indicesPerLOD`
- L27 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/types/PaddedBlockView.h` (Private)


#### struct `rl4::PaddedBlockView`  
`struct PaddedBlockView`  
_L11-63_
- L13 _public member_ `std::uint32_t size;` — Unpadded size
- L16 _public member_ `std::uint32_t sizePaddedToLastFullBlock;` — If the last full block needs to be masked-off because it contains padding, this view will include that last full block as well
- L19 _public member_ `std::uint32_t sizePaddedToSecondLastFullBlock;` — If the last full block needs to be masked-off because it contains padding, that full block won't be included in this boundary as it needs special care
- L21 _public prototype_ `PaddedBlockView() = default;`
- L22 _public function_ `PaddedBlockView(std::uint32_t viewRowCount, std::uint32_t paddedRowCount, std::uint32_t blockHeight, std::uint32_t padTo) : size`
- L51 _public function_ `PaddedBlockView(std::uint32_t viewRowCount, std::uint32_t boundaryRowCountPaddedToLastFullBlock, std::uint32_t boundaryRowCountPaddedToSecondLastFullBlock) : size`
- L60 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/types/bpcm/FloatArray.h` (Private)


#### struct `rl4::FloatArray`  
`struct FloatArray`  
_L16-78_
- L17 _public member_ `AlignedVector<float> fp32;`
- L18 _public member_ `AlignedVector<std::uint16_t> fp16;`
- L20 _public function_ `explicit FloatArray(MemoryResource* memRes) : fp32`
- L26 _public function_ `template<class Archive> void load(Archive& archive)`
- L33 _public function_ `template<class Archive> void save(Archive& archive)`
- L40 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, float>::value, T*>::type data()`
- L45 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, std::uint16_t>::value, T*>::type data()`
- L50 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, float>::value, const T*>::type data() const`
- L55 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, std::uint16_t>::value, const T*>::type data() const`
- L60 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, float>::value, std::size_t>::type size() const`
- L65 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, std::uint16_t>::value, std::size_t>::type size() const`
- L70 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, float>::value, void>::type resize(std::size_t newSize)`
- L75 _public function_ `template<typename T> typename std::enable_if<std::is_same<T, std::uint16_t>::value, void>::type resize(std::size_t newSize)`

#### struct `rl4::FloatArrayDeserializer`  
`template<typename TF256, typename TF128> struct FloatArrayDeserializer<float, TF256, TF128>`  
_L81-87_
- L84 _public function_ `template<class TArchive> void operator()(FloatArray& instance, TArchive& archive)`

#### struct `rl4::FloatArrayDeserializer`  
`template<typename TF256, typename TF128> struct FloatArrayDeserializer<std::uint16_t, TF256, TF128>`  
_L90-107_
- L84 _public function_ `template<class TArchive> void operator()(FloatArray& instance, TArchive& archive)`

#### struct `rl4::FloatArraySerializer`  
`template<typename TF256, typename TF128> struct FloatArraySerializer<float, TF256, TF128>`  
_L110-116_
- L113 _public function_ `template<class TArchive> void operator()(FloatArray& instance, TArchive& archive)`

#### struct `rl4::FloatArraySerializer`  
`template<typename TF256, typename TF128> struct FloatArraySerializer<std::uint16_t, TF256, TF128>`  
_L119-136_
- L113 _public function_ `template<class TArchive> void operator()(FloatArray& instance, TArchive& archive)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/types/bpcm/Optimizer.h` (Private)


#### struct `rl4::bpcm::Optimizer`  
`template<typename TFVec, std::uint32_t BlockHeight, std::uint32_t PadTo, std::uint32_t Stride> struct Optimizer`  
_L16-119_
- L20 _public function_ `static std::uint32_t optimize(float* dest, const float* source, Extent dimensions)`
- L51 _public function_ `static std::uint32_t optimize(std::uint16_t* dest, const float* source, Extent dimensions)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace rl4`
- L13 _namespace_ `namespace bpcm` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/utils/Extd.h` (Private)


#### enum `extd::impl::LUTStrategy`  
`enum class LUTStrategy`  
_L84-87_
- L85 _public enumerator_ `ByValue`
- L86 _public enumerator_ `ByPosition`

#### class `extd::impl::LUTFilter`  
`template<typename TLUT, LUTStrategy Strategy> class LUTFilter`  
_L90-110_
- L92 _public function_ `explicit LUTFilter(const TLUT& lut_) : lut`
- L97 _public function_ `template<typename T, LUTStrategy ChosenStrategy = Strategy> typename std::enable_if<ChosenStrategy == LUTStrategy::ByValue, bool>::type operator()(const T& value, std::size_t )`
- L103 _public function_ `template<typename T, LUTStrategy ChosenStrategy = Strategy> typename std::enable_if<ChosenStrategy == LUTStrategy::ByPosition, bool>::type operator()(const T& , std::size_t index)`
- L109 _private member_ `const TLUT& lut;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define EXTD_GUARD`
- L28 _namespace_ `namespace extd`
- L31 _function_ `template<typename T> inline T clamp(T value, T low, T high)` (scope `extd`)
- L36 _function_ `template<typename T> inline T roundUp(T number, T multiple)` (scope `extd`)
- L41 _function_ `template<typename T> inline T interpolate(T a, T b, T weight)` (scope `extd`)
- L46 _function_ `template<class TInputIterator, class T> inline bool contains(TInputIterator first, TInputIterator last, const T& value)` (scope `extd`)
- L51 _function_ `template<class TContainer, class T> inline bool contains(const TContainer& container, const T& value)` (scope `extd`)
- L56 _function_ `template<class T> inline bool contains(const std::set<T>& container, const T& value)` (scope `extd`)
- L61 _function_ `template<class T, class Predicate, typename... Args> inline void filter(std::vector<T, Args...>& source, Predicate pred)` (scope `extd`)
- L64 _function_ `source.erase(std::remove_if(std::begin(source), std::end(source), [&source, &pred](const T& value) { const auto index = static_cast<std::size_t>(&value - &(source.front())); return !pred(value, index); }), source.end());` (scope `extd::filter`)
- L72 _function_ `template<class TContainer, class Predicate, typename... Args> inline void filter(TContainer& source, Predicate pred)` (scope `extd`)
- L73 _typedef_ `using value_type = typename TContainer::value_type;` (scope `extd::filter`)
- L74 _function_ `auto newEnd = std::remove_if(std::begin(source), std::end(source), [&source, &pred](const value_type& value) { const auto index = static_cast<std::size_t>(&value - source.data()); return !pred(value, index); });` (scope `extd::filter`)
- L82 _namespace_ `namespace impl` (scope `extd`)
- L115 _function_ `template<typename TLookUpTable> inline impl::LUTFilter<TLookUpTable, impl::LUTStrategy::ByValue> byValue(const TLookUpTable& lookUpTable)` (scope `extd`)
- L120 _function_ `template<typename TLookUpTable> inline impl::LUTFilter<TLookUpTable, impl::LUTStrategy::ByPosition> byPosition(const TLookUpTable& lookUpTable)` (scope `extd`)
- L125 _function_ `template<class TContainer, class TComparator> inline typename TContainer::value_type minOf(const TContainer& container, TComparator&& comparator)` (scope `extd`)
- L126 _typedef_ `using ValueType = typename TContainer::value_type;` (scope `extd::minOf`)
- L132 _function_ `template<class TContainer> inline typename TContainer::value_type minOf(const TContainer& container)` (scope `extd`)
- L134 _function_ `const auto compare = [](const ValueType& lhs, const ValueType& rhs)` (scope `extd::minOf`)
- L139 _function_ `template<class TContainer, class TComparator> inline typename TContainer::value_type maxOf(const TContainer& container, TComparator&& comparator)` (scope `extd`)
- L140 _typedef_ `using ValueType = typename TContainer::value_type;` (scope `extd::maxOf`)
- L146 _function_ `template<class TContainer> inline typename TContainer::value_type maxOf(const TContainer& container)` (scope `extd`)
- L148 _function_ `const auto compare = [](const ValueType& lhs, const ValueType& rhs)` (scope `extd::maxOf`)
- L153 _function_ `template<class TSource, class TDestination> inline void copy(const TSource& source, TDestination& destination)` (scope `extd`)
- L158 _function_ `template<class T, class U> inline void copy(av::ArrayView<T> source, av::ArrayView<U> destination)` (scope `extd`)
- L173 _function_ `template<class TIterator, typename TDistance> TIterator advanced(TIterator source, TDistance distance)` (scope `extd`)
- L179 _function_ `template<class TIterator, class Predicate> typename std::iterator_traits<TIterator>::difference_type advanceWhile(TIterator& it, const TIterator& end, Predicate pred)` (scope `extd`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/riglogic/utils/Macros.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define FORCE_INLINE __forceinline`
- L9 _macro_ `#define FORCE_INLINE inline __attribute__((always_inline))`
- L15 _macro_ `#define ASSUME_TRUE(condition) __assume(condition)`
- L17 _macro_ `#define ASSUME_TRUE(condition) \`
- L26 _macro_ `#define RL_UNUSED(x) static_cast<void>(x)`
- L30 _macro_ `#define RL_FALSE static_cast<char>(0)`
- L34 _macro_ `#define RL_TRUE static_cast<char>(1)`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/status/PredefinedCodes.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace sc`
- L9 _variable_ `static const StatusCode OK{0, "Ok"` (scope `sc`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/status/Registry.h` (Private)


#### class `sc::StatusCodeRegistry`  
`class StatusCodeRegistry`  
_L11-15_
- L13 _public prototype_ `static bool insert(std::initializer_list<StatusCode> statuses);`
- L14 _public prototype_ `static bool contains(StatusCode status);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace sc`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/status/Storage.h` (Private)


#### class `sc::StatusStorage`  
`class StatusStorage`  
_L12-21_
- L14 _public prototype_ `static void set(StatusCode status);`
- L15 _public prototype_ `static void reset();`
- L16 _public prototype_ `static StatusCode get();`
- L17 _public prototype_ `static bool isOk();`
- L18 _public prototype_ `static constexpr std::size_t bufferSize();`
- L19 _public prototype_ `static HookFunction getHook();`
- L20 _public prototype_ `static void setHook(HookFunction hook);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace sc`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/streams/FileStreamImpl.h` (Private)


#### class `trio::FileStreamImpl`  
`class FileStreamImpl : public FileStream`  
_L26-51_
- inherits: `FileStream`
- L28 _public prototype_ `FileStreamImpl(const char* path_, AccessMode accessMode_, OpenMode openMode_, MemoryResource* memRes_);`
- L30 _public prototype_ `void open() override;`
- L31 _public prototype_ `void close() override;`
- L32 _public prototype_ `std::uint64_t tell() override;`
- L33 _public prototype_ `void seek(std::uint64_t position) override;`
- L34 _public prototype_ `std::uint64_t size() override;`
- L35 _public prototype_ `std::size_t read(char* destination, std::size_t size) override;`
- L36 _public prototype_ `std::size_t read(Writable* destination, std::size_t size) override;`
- L37 _public prototype_ `std::size_t write(const char* source, std::size_t size) override;`
- L38 _public prototype_ `std::size_t write(Readable* source, std::size_t size) override;`
- L40 _public prototype_ `MemoryResource* getMemoryResource();`
- L43 _private member_ `std::fstream file;`
- L44 _private member_ `NativeString filePath;`
- L45 _private member_ `AccessMode fileAccessMode;`
- L46 _private member_ `OpenMode fileOpenMode;`
- L47 _private member_ `std::uint64_t fileSize;`
- L48 _private member_ `std::uint64_t filePos;`
- L49 _private member_ `MemoryResource* memRes;`
- L50 _private member_ `StreamStatus status;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/streams/MemoryMappedFileStreamFallback.h` (Private)


#### class `trio::MemoryMappedFileStreamFallback`  
`class MemoryMappedFileStreamFallback : public MemoryMappedFileStream`  
_L21-49_
- inherits: `MemoryMappedFileStream`
- L23 _public prototype_ `MemoryMappedFileStreamFallback(const char* path_, AccessMode accessMode_, MemoryResource* memRes_);`
- L24 _public prototype_ `~MemoryMappedFileStreamFallback();`
- L26 _public prototype_ `MemoryMappedFileStreamFallback(const MemoryMappedFileStreamFallback&) = delete;`
- L27 _public prototype_ `MemoryMappedFileStreamFallback& operator=(const MemoryMappedFileStreamFallback&) = delete;`
- L29 _public prototype_ `MemoryMappedFileStreamFallback(MemoryMappedFileStreamFallback&&) = delete;`
- L30 _public prototype_ `MemoryMappedFileStreamFallback& operator=(MemoryMappedFileStreamFallback&&) = delete;`
- L32 _public prototype_ `void open() override;`
- L33 _public prototype_ `void close() override;`
- L34 _public prototype_ `std::uint64_t tell() override;`
- L35 _public prototype_ `void seek(std::uint64_t position) override;`
- L36 _public prototype_ `std::uint64_t size() override;`
- L37 _public prototype_ `std::size_t read(char* destination, std::size_t size) override;`
- L38 _public prototype_ `std::size_t read(Writable* destination, std::size_t size) override;`
- L39 _public prototype_ `std::size_t write(const char* source, std::size_t size) override;`
- L40 _public prototype_ `std::size_t write(Readable* source, std::size_t size) override;`
- L41 _public prototype_ `void flush() override;`
- L42 _public prototype_ `void resize(std::uint64_t size) override;`
- L44 _public prototype_ `MemoryResource* getMemoryResource();`
- L47 _private member_ `pma::ScopedPtr<FileStream> stream;`
- L48 _private member_ `MemoryResource* memRes;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/streams/MemoryMappedFileStreamUnix.h` (Private)


#### class `trio::MemoryMappedFileStreamUnix`  
`class MemoryMappedFileStreamUnix : public MemoryMappedFileStream`  
_L19-64_
- inherits: `MemoryMappedFileStream`
- L21 _public prototype_ `MemoryMappedFileStreamUnix(const char* path_, AccessMode accessMode_, MemoryResource* memRes_);`
- L22 _public prototype_ `~MemoryMappedFileStreamUnix();`
- L24 _public prototype_ `MemoryMappedFileStreamUnix(const MemoryMappedFileStreamUnix&) = delete;`
- L25 _public prototype_ `MemoryMappedFileStreamUnix& operator=(const MemoryMappedFileStreamUnix&) = delete;`
- L27 _public prototype_ `MemoryMappedFileStreamUnix(MemoryMappedFileStreamUnix&&) = delete;`
- L28 _public prototype_ `MemoryMappedFileStreamUnix& operator=(MemoryMappedFileStreamUnix&&) = delete;`
- L30 _public prototype_ `void open() override;`
- L31 _public prototype_ `void close() override;`
- L32 _public prototype_ `std::uint64_t tell() override;`
- L33 _public prototype_ `void seek(std::uint64_t position) override;`
- L34 _public prototype_ `std::uint64_t size() override;`
- L35 _public prototype_ `std::size_t read(char* destination, std::size_t size) override;`
- L36 _public prototype_ `std::size_t read(Writable* destination, std::size_t size) override;`
- L37 _public prototype_ `std::size_t write(const char* source, std::size_t size) override;`
- L38 _public prototype_ `std::size_t write(Readable* source, std::size_t size) override;`
- L39 _public prototype_ `void flush() override;`
- L40 _public prototype_ `void resize(std::uint64_t size) override;`
- L42 _public prototype_ `MemoryResource* getMemoryResource();`
- L45 _private prototype_ `void openFile();`
- L46 _private prototype_ `void closeFile();`
- L47 _private prototype_ `void mapFile(std::uint64_t offset, std::uint64_t size);`
- L48 _private prototype_ `void unmapFile();`
- L49 _private prototype_ `void resizeFile(std::uint64_t size);`
- L52 _private member_ `StreamStatus status;`
- L53 _private member_ `NativeString filePath;`
- L54 _private member_ `AccessMode fileAccessMode;`
- L55 _private member_ `MemoryResource* memRes;`
- L56 _private member_ `int file;`
- L57 _private member_ `void* data;`
- L58 _private member_ `std::uint64_t position;`
- L59 _private member_ `std::uint64_t fileSize;`
- L60 _private member_ `std::uint64_t viewOffset;`
- L61 _private member_ `std::size_t viewSize;`
- L62 _private member_ `bool delayedMapping;`
- L63 _private member_ `bool dirty;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/streams/MemoryMappedFileStreamWindows.h` (Private)


#### class `trio::MemoryMappedFileStreamWindows`  
`class MemoryMappedFileStreamWindows : public MemoryMappedFileStream`  
_L21-67_
- inherits: `MemoryMappedFileStream`
- L23 _public prototype_ `MemoryMappedFileStreamWindows(const char* path_, AccessMode accessMode_, MemoryResource* memRes_);`
- L24 _public prototype_ `~MemoryMappedFileStreamWindows();`
- L26 _public prototype_ `MemoryMappedFileStreamWindows(const MemoryMappedFileStreamWindows&) = delete;`
- L27 _public prototype_ `MemoryMappedFileStreamWindows& operator=(const MemoryMappedFileStreamWindows&) = delete;`
- L29 _public prototype_ `MemoryMappedFileStreamWindows(MemoryMappedFileStreamWindows&&) = delete;`
- L30 _public prototype_ `MemoryMappedFileStreamWindows& operator=(MemoryMappedFileStreamWindows&&) = delete;`
- L32 _public prototype_ `void open() override;`
- L33 _public prototype_ `void close() override;`
- L34 _public prototype_ `std::uint64_t tell() override;`
- L35 _public prototype_ `void seek(std::uint64_t position) override;`
- L36 _public prototype_ `std::uint64_t size() override;`
- L37 _public prototype_ `std::size_t read(char* destination, std::size_t size) override;`
- L38 _public prototype_ `std::size_t read(Writable* destination, std::size_t size) override;`
- L39 _public prototype_ `std::size_t write(const char* source, std::size_t size) override;`
- L40 _public prototype_ `std::size_t write(Readable* source, std::size_t size) override;`
- L41 _public prototype_ `void flush() override;`
- L42 _public prototype_ `void resize(std::uint64_t size) override;`
- L44 _public prototype_ `MemoryResource* getMemoryResource();`
- L47 _private prototype_ `void openFile();`
- L48 _private prototype_ `void closeFile();`
- L49 _private prototype_ `void mapFile(std::uint64_t offset, std::uint64_t size);`
- L50 _private prototype_ `void unmapFile();`
- L51 _private prototype_ `void resizeFile(std::uint64_t size);`
- L54 _private member_ `StreamStatus status;`
- L55 _private member_ `NativeString filePath;`
- L56 _private member_ `AccessMode fileAccessMode;`
- L57 _private member_ `MemoryResource* memRes;`
- L58 _private member_ `HANDLE file;`
- L59 _private member_ `HANDLE mapping;`
- L60 _private member_ `LPVOID data;`
- L61 _private member_ `std::uint64_t position;`
- L62 _private member_ `std::uint64_t fileSize;`
- L63 _private member_ `std::uint64_t viewOffset;`
- L64 _private member_ `std::size_t viewSize;`
- L65 _private member_ `bool delayedMapping;`
- L66 _private member_ `bool dirty;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/streams/MemoryStreamImpl.h` (Private)


#### class `trio::MemoryStreamImpl`  
`class MemoryStreamImpl : public MemoryStream`  
_L24-45_
- inherits: `MemoryStream`
- L26 _public prototype_ `MemoryStreamImpl(std::size_t initialSize, MemoryResource* memRes_);`
- L28 _public prototype_ `void open() override;`
- L29 _public prototype_ `void close() override;`
- L30 _public prototype_ `std::uint64_t tell() override;`
- L31 _public prototype_ `void seek(std::uint64_t position_) override;`
- L32 _public prototype_ `std::uint64_t size() override;`
- L33 _public prototype_ `std::size_t read(char* destination, std::size_t size) override;`
- L34 _public prototype_ `std::size_t read(Writable* destination, std::size_t size) override;`
- L35 _public prototype_ `std::size_t write(const char* source, std::size_t size) override;`
- L36 _public prototype_ `std::size_t write(Readable* source, std::size_t size) override;`
- L38 _public prototype_ `MemoryResource* getMemoryResource();`
- L41 _private member_ `StreamStatus status;`
- L42 _private member_ `Vector<char> data;`
- L43 _private member_ `std::size_t position;`
- L44 _private member_ `MemoryResource* memRes;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/streams/StreamStatus.h` (Private)


#### class `trio::StreamStatus`  
`class StreamStatus`  
_L11-19_
- L13 _public function_ `sc::StatusProvider* operator->()`
- L18 _private member_ `static sc::StatusProvider status;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/utils/NativeString.h` (Private)


#### struct `trio::StringConverter`  
`template<> struct StringConverter<char>`  
_L29-36_
- L30 _public typedef_ `using CharacterType = char;`
- L31 _public typedef_ `using StringType = pma::String<CharacterType>;`
- L33 _public function_ `static StringType from(const char* source, pma::MemoryResource* memRes)`
- L40 _public typedef_ `using CharacterType = wchar_t;`

#### struct `trio::StringConverter`  
`template<> struct StringConverter<wchar_t>`  
_L39-66_
- L30 _public typedef_ `using CharacterType = char;`
- L31 _public typedef_ `using StringType = pma::String<CharacterType>;`
- L33 _public function_ `static StringType from(const char* source, pma::MemoryResource* memRes)`
- L40 _public typedef_ `using CharacterType = wchar_t;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace trio`
- L69 _typedef_ `using NativeCharacter = wchar_t;` (scope `trio`)
- L71 _typedef_ `using NativeCharacter = char;` (scope `trio`)
- L74 _typedef_ `using NativeString = pma::String<NativeCharacter>;` (scope `trio`)
- L75 _typedef_ `using NativeStringConverter = StringConverter<NativeCharacter>;` (scope `trio`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/utils/PlatformWindows.h` (Private)


#### Free symbols / members of external scopes

- L15 _macro_ `#define WIN32_LEAN_AND_MEAN`
- L16 _macro_ `#define NOGDICAPMASKS`
- L17 _macro_ `#define NOVIRTUALKEYCODES`
- L18 _macro_ `#define NOWINMESSAGES`
- L19 _macro_ `#define NOWINSTYLES`
- L20 _macro_ `#define NOSYSMETRICS`
- L21 _macro_ `#define NOMENUS`
- L22 _macro_ `#define NOICONS`
- L23 _macro_ `#define NOKEYSTATES`
- L24 _macro_ `#define NOSYSCOMMANDS`
- L25 _macro_ `#define NORASTEROPS`
- L26 _macro_ `#define NOSHOWWINDOW`
- L27 _macro_ `#define NOATOM`
- L28 _macro_ `#define NOCLIPBOARD`
- L29 _macro_ `#define NOCOLOR`
- L30 _macro_ `#define NOCTLMGR`
- L31 _macro_ `#define NODRAWTEXT`
- L32 _macro_ `#define NOGDI`
- L33 _macro_ `#define NOKERNEL`
- L34 _macro_ `#define NOUSER`
- L35 _macro_ `#define NOMB`
- L36 _macro_ `#define NOMEMMGR`
- L37 _macro_ `#define NOMETAFILE`
- L38 _macro_ `#define NOMINMAX`
- L39 _macro_ `#define NOMSG`
- L40 _macro_ `#define NOOPENFILE`
- L41 _macro_ `#define NOSCROLL`
- L42 _macro_ `#define NOSERVICE`
- L43 _macro_ `#define NOSOUND`
- L44 _macro_ `#define NOTEXTMETRIC`
- L45 _macro_ `#define NOWH`
- L46 _macro_ `#define NOWINOFFSETS`
- L47 _macro_ `#define NOCOMM`
- L48 _macro_ `#define NOKANJI`
- L49 _macro_ `#define NOHELP`
- L50 _macro_ `#define NOPROFILER`
- L51 _macro_ `#define NODEFERWINDOWPOS`
- L52 _macro_ `#define NOMCX`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Private/trio/utils/ScopedEnumEx.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace trio`
- L10 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator&(TEnum lhs, TEnum rhs)` (scope `trio`)
- L11 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `trio::operator &`)
- L16 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator|(TEnum lhs, TEnum rhs)` (scope `trio`)
- L17 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `trio::operator |`)
- L22 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator^(TEnum lhs, TEnum rhs)` (scope `trio`)
- L23 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `trio::operator ^`)
- L28 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator~(TEnum value)` (scope `trio`)
- L29 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `trio::operator ~`)
- L34 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator&=(TEnum& lhs, TEnum rhs)` (scope `trio`)
- L39 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator|=(TEnum& lhs, TEnum rhs)` (scope `trio`)
- L44 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator^=(TEnum& lhs, TEnum rhs)` (scope `trio`)
- L49 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, bool>::type contains(TEnum lhs, TEnum rhs)` (scope `trio`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/ArchiveMemoryStream.h` (Public)


#### class `FArchiveMemoryStream`  
`class FArchiveMemoryStream: public rl4::BoundedIOStream`  
_L16-35_
- inherits: `rl4::BoundedIOStream`
- desc: Adapter that allows using an FArchive instance as a rl4::BoundedIOStream
- L19 _public prototype_ `explicit FArchiveMemoryStream(FArchive* Archive);`
- L21 _public prototype_ `void seek(std::uint64_t Position) override;`
- L22 _public prototype_ `std::uint64_t tell() override;`
- L23 _public prototype_ `void open() override;`
- L24 _public prototype_ `void close() override;`
- L25 _public prototype_ `size_t read(char* ReadToBuffer, size_t Size) override;`
- L26 _public prototype_ `size_t read(Writable* Destination, size_t Size) override;`
- L27 _public prototype_ `size_t write(const char* WriteFromBuffer, size_t Size) override;`
- L28 _public prototype_ `size_t write(Readable* Source, size_t Size) override;`
- L29 _public prototype_ `std::uint64_t size() override;`
- L32 _private member_ `FArchive* Archive;`
- L33 _private member_ `int64 Origin;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define RIGLOGICLIB_API`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/FMemoryResource.h` (Public)


#### class `FMemoryResource`  
`class FMemoryResource : public rl4::MemoryResource`  
_L10-34_
- inherits: `rl4::MemoryResource`
- L13 _public function_ `void* allocate(std::size_t size, std::size_t alignment) override`
- L18 _public function_ `void deallocate(void* ptr, std::size_t size, std::size_t alignment) override`
- L23 _public function_ `static TSharedPtr<FMemoryResource> SharedInstance()`
- L29 _public function_ `static MemoryResource* Instance()`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/RigLogicLib.h` (Public)


#### class `FRigLogicLib`  
`class FRigLogicLib : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `void StartupModule() override;`
- L16 _public prototype_ `void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicLib, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicLib, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/arrayview/ArrayView.h` (Public)


#### struct `av::ArrayViewTraits`  
`template<typename T> struct ArrayViewTraits`  
_L19-27_
- L20 _public typedef_ `using value_type = T;`
- L21 _public typedef_ `using reference = T&;`
- L22 _public typedef_ `using const_reference = const T&;`
- L23 _public typedef_ `using pointer = T*;`
- L24 _public typedef_ `using const_pointer = const T*;`
- L25 _public typedef_ `using size_type = std::size_t;`
- L26 _public typedef_ `using difference_type = std::ptrdiff_t;`
- L31 _public typedef_ `using value_type = const T;`
- L32 _public typedef_ `using reference = const T&;`
- L34 _public typedef_ `using pointer = const T*;`

#### struct `av::ArrayViewTraits`  
`template<typename T> struct ArrayViewTraits<const T>`  
_L30-38_
- L20 _public typedef_ `using value_type = T;`
- L21 _public typedef_ `using reference = T&;`
- L22 _public typedef_ `using const_reference = const T&;`
- L23 _public typedef_ `using pointer = T*;`
- L24 _public typedef_ `using const_pointer = const T*;`
- L25 _public typedef_ `using size_type = std::size_t;`
- L26 _public typedef_ `using difference_type = std::ptrdiff_t;`
- L31 _public typedef_ `using value_type = const T;`
- L32 _public typedef_ `using reference = const T&;`
- L34 _public typedef_ `using pointer = const T*;`

#### struct `av::IsCompatible`  
`template<typename T, typename U> struct IsCompatible`  
_L41-45_
- L42 _public member_ `static constexpr bool value = std::is_same<typename std::remove_cv<T>::type, typename std::remove_cv<U>::type>::value && (std::is_const<typename std::remove_reference<T>::type>::value || !std::is_const<typename std::remove_reference<U>::type>::value);`

#### class `av::ArrayView`  
`template<typename T> class ArrayView`  
_L58-178_
- desc: @brief A view over a continuous sequence of objects. @tparam T element type Provides a view over a continuous sequence of objects owned by some other object. Contains a count of elements and a pointer to a location where they are stored. ArrayView does not own the memory it points to - it does not perform any allocation and deallocation. It can be constructed given a pointer and element count, or a container type argument. The class provides helper methods for creating subviews over the objects, and methods for by-value comparison with containers. ConstArrayView represents an immutable view.
- L60 _public typedef_ `using value_type = typename ArrayViewTraits<T>::value_type;`
- L61 _public typedef_ `using reference = typename ArrayViewTraits<T>::reference;`
- L62 _public typedef_ `using const_reference = typename ArrayViewTraits<T>::const_reference;`
- L63 _public typedef_ `using const_pointer = typename ArrayViewTraits<T>::const_pointer;`
- L64 _public typedef_ `using pointer = typename ArrayViewTraits<T>::pointer;`
- L65 _public typedef_ `using size_type = typename ArrayViewTraits<T>::size_type;`
- L66 _public typedef_ `using difference_type = typename ArrayViewTraits<T>::difference_type;`
- L68 _public prototype_ `ArrayView() = default;`
- L69 _public prototype_ `~ArrayView() noexcept = default;`
- L71 _public prototype_ `ArrayView(const ArrayView&) = default;`
- L72 _public prototype_ `ArrayView& operator=(const ArrayView&) = default;`
- L74 _public prototype_ `ArrayView(ArrayView&&) = default;`
- L75 _public prototype_ `ArrayView& operator=(ArrayView&&) = default;`
- L77 _public function_ `ArrayView(pointer src, size_type size) : ptr`
- L83 _public function_ `template<typename U, typename std::enable_if<IsCompatible<T, U>::value, int>::type = 0> ArrayView(ArrayView<U>& src) : ArrayView`
- L88 _public function_ `template<typename U, typename std::enable_if<IsCompatible<T, U>::value, int>::type = 0> ArrayView(const ArrayView<U>& src) : ArrayView`
- L93 _public function_ `template<typename U, typename std::enable_if<IsCompatible<T, U>::value, int>::type = 0> ArrayView(ArrayView<U>&& src) : ArrayView`
- L101 _public function_ `ArrayView(U&& src) : ArrayView`
- L105 _public function_ `size_type size() const`
- L109 _public function_ `pointer data()`
- L113 _public function_ `const_pointer data() const`
- L117 _public function_ `pointer begin()`
- L121 _public function_ `pointer end()`
- L125 _public function_ `const_pointer cbegin() const`
- L129 _public function_ `const_pointer cend() const`
- L133 _public function_ `const_pointer begin() const`
- L137 _public function_ `const_pointer end() const`
- L141 _public function_ `reference operator[](std::size_t index)`
- L146 _public function_ `const_reference operator[](std::size_t index) const`
- L151 _public function_ `reference at(std::size_t index)`
- L155 _public function_ `const_reference at(std::size_t index) const`
- L159 _public function_ `ArrayView subview(std::size_t offset, std::size_t count) const`
- L165 _public function_ `ArrayView first(std::size_t count) const`
- L170 _public function_ `ArrayView last(std::size_t count) const`
- L176 _private member_ `pointer ptr{nullptr};`
- L177 _private member_ `size_type sz{};`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace av`
- L181 _function_ `template<typename T, typename U> bool operator==(const ArrayView<T>& lhs, const ArrayView<U>& rhs)` (scope `av`)
- L198 _function_ `template<typename T, typename U> bool operator!=(const ArrayView<T>& lhs, const ArrayView<U>& rhs)` (scope `av`)
- L203 _function_ `template<typename T, typename TContainer> typename std::enable_if<!std::is_base_of<ArrayView<T>, TContainer>::value, bool>::type operator==(const ArrayView<T>& lhs, const TContainer& rhs)` (scope `av`)
- L218 _function_ `template<typename T, typename TContainer> typename std::enable_if<!std::is_base_of<ArrayView<T>, TContainer>::value, bool>::type operator!=(const ArrayView<T>& lhs, const TContainer& rhs)` (scope `av`)
- L224 _function_ `template<typename T, typename TContainer> typename std::enable_if<!std::is_base_of<ArrayView<T>, TContainer>::value, bool>::type operator==(const TContainer& lhs, const ArrayView<T>& rhs)` (scope `av`)
- L230 _function_ `template<typename T, typename TContainer> typename std::enable_if<!std::is_base_of<ArrayView<T>, TContainer>::value, bool>::type operator!=(const TContainer& lhs, const ArrayView<T>& rhs)` (scope `av`)
- L236 _typedef_ `template<typename T> using ConstArrayView = ArrayView<const T>;` (scope `av`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/arrayview/StringView.h` (Public)


#### class `av::StringView`  
`class StringView : public ConstArrayView<char>`  
_L9-32_
- inherits: `ConstArrayView<char>`
- L11 _public typedef_ `using Base = ConstArrayView<char>;`
- L16 _public function_ `const char* c_str() const`
- L20 _public function_ `operator const char*() const`
- L24 _public function_ `const char* operator*() const`
- L29 _private function_ `const char* dataOrEmpty() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace av`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/arrayview/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define AV_MAJOR_VERSION 1`
- L6 _macro_ `#define AV_MINOR_VERSION 1`
- L7 _macro_ `#define AV_PATCH_VERSION 8`
- L8 _macro_ `#define AV_VERSION_STRING "1.1.8"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/BinaryStreamReader.h` (Public)


#### class `dna::BinaryStreamReader`  
`class DNAAPI BinaryStreamReader : public StreamReader`  
_L12-146_
- inherits: `StreamReader`
- L28 _public prototype_ `static BinaryStreamReader* create(BoundedIOStream* stream, const Configuration& config = {}, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of BinaryStreamReader @param stream Source stream from which data is going to be read. @param config Specify the filtering and adaptation parameters. @see Configuration @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L59 _public prototype_ `static BinaryStreamReader* create(BoundedIOStream* stream, DataLayer layer, UnknownLayerPolicy policy = UnknownLayerPolicy::Preserve, std::uint16_t maxLOD = 0u, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of BinaryStreamReader @param stream Source stream from which data is going to be read. @param layer Specify the layer up to which the data needs to be loaded. @note The Definition data layer depends on and thus implicitly loads the Descriptor layer. The Behavior data layer depends on and thus implicitly loads the Definition layer. The Geometry data layer depends on and thus also implicitly loads the Definition layer. The MachineLearnedBehavior data layer depends on and thus also implicitly loads the Definition layer. @param policy Specify whether unknown layers are to be preserved or just ignored. @param maxLOD The maximum level of details to be loaded. @note A value of zero indicates to load all LODs. @warning The maxLOD value must be less than the value returned by getLODCount. @see getLODCount @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L94 _public prototype_ `static BinaryStreamReader* create(BoundedIOStream* stream, DataLayer layer, UnknownLayerPolicy policy, std::uint16_t maxLOD, std::uint16_t minLOD, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of BinaryStreamReader @param stream Source stream from which data is going to be read. @param layer Specify the layer up to which the data needs to be loaded. @note The Definition data layer depends on and thus implicitly loads the Descriptor layer. The Behavior data layer depends on and thus implicitly loads the Definition layer. The Geometry data layer depends on and thus also implicitly loads the Definition layer. The MachineLearnedBehavior data layer depends on and thus also implicitly loads the Definition layer. @param policy Specify whether unknown layers are to be preserved or just ignored. @param maxLOD The maximum level of details to be loaded. @param minLOD The minimum level of details to be loaded. @note A range of [0, LOD count - 1] for maxLOD / minLOD respectively indicates to load all LODs. @warning Both maxLOD and minLOD values must be less than the value returned by getLODCount. @see getLODCount @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L131 _public prototype_ `static BinaryStreamReader* create(BoundedIOStream* stream, DataLayer layer, UnknownLayerPolicy policy, std::uint16_t* lods, std::uint16_t lodCount, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of BinaryStreamReader @param stream Source stream from which data is going to be read. @param layer Specify the layer up to which the data needs to be loaded. @note The Definition data layer depends on and thus implicitly loads the Descriptor layer. The Behavior data layer depends on and thus implicitly loads the Definition layer. The Geometry data layer depends on and thus also implicitly loads the Definition layer. The MachineLearnedBehavior data layer depends on and thus also implicitly loads the Definition layer. @param policy Specify whether unknown layers are to be preserved or just ignored. @param lods An array specifying which exact lods to load. @warning All values in the array must be less than the value returned by getLODCount. @see getLODCount @param lodCount The number of elements in the lods array. @warning There cannot be more elements in the array than the value returned by getLODCount. @see getLODCount @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L143 _public prototype_ `static void destroy(BinaryStreamReader* instance);` — @brief Method for freeing a BinaryStreamReader instance. @param instance Instance of BinaryStreamReader to be freed. @see create

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<dna::BinaryStreamReader>`  
_L153-155_
- L154 _public typedef_ `using type = pma::FactoryCreate<dna::BinaryStreamReader>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<dna::BinaryStreamReader>`  
_L158-160_
- L159 _public typedef_ `using type = pma::FactoryDestroy<dna::BinaryStreamReader>;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace dna`
- L150 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/BinaryStreamWriter.h` (Public)


#### class `dna::BinaryStreamWriter`  
`class DNAAPI BinaryStreamWriter : public StreamWriter`  
_L14-50_
- inherits: `StreamWriter`
- L28 _public prototype_ `static BinaryStreamWriter* create(BoundedIOStream* stream, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of BinaryStreamWriter @param stream Stream into which the data is going to be written. @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L35 _public prototype_ `static void destroy(BinaryStreamWriter* instance);` — @brief Method for freeing a BinaryStreamWriter instance. @param instance Instance of BinaryStreamWriter to be freed. @see create
- L40 _public prototype_ `virtual void setFrom(const BinaryStreamReader* source, DataLayer layer = DataLayer::All, UnknownLayerPolicy policy = UnknownLayerPolicy::Preserve, MemoryResource* memRes = nullptr) = 0;`
- L45 _public prototype_ `virtual void setFrom(const JSONStreamReader* source, DataLayer layer = DataLayer::All, UnknownLayerPolicy policy = UnknownLayerPolicy::Preserve, MemoryResource* memRes = nullptr) = 0;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<dna::BinaryStreamWriter>`  
_L57-59_
- L58 _public typedef_ `using type = pma::FactoryCreate<dna::BinaryStreamWriter>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<dna::BinaryStreamWriter>`  
_L62-64_
- L63 _public typedef_ `using type = pma::FactoryDestroy<dna::BinaryStreamWriter>;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`
- L54 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/Configuration.h` (Public)


#### enum `dna::DataLayer`  
`enum class DataLayer : std::uint32_t`  
_L11-22_
- L12 _public enumerator_ `Descriptor = 1`
- L13 _public enumerator_ `Definition = 2 | Descriptor` — Implicitly loads Descriptor
- L14 _public enumerator_ `Behavior = 4 | Definition` — Implicitly loads Definition
- L15 _public enumerator_ `Geometry = 8 | Definition` — Implicitly loads Definition
- L16 _public enumerator_ `GeometryWithoutBlendShapes = 16 | Definition` — Implicitly loads Definition
- L17 _public enumerator_ `MachineLearnedBehavior = 32 | Definition` — Implicitly loads Definition
- L18 _public enumerator_ `RBFBehavior = 64 | Behavior` — Implicitly loads Behavior
- L19 _public enumerator_ `JointBehaviorMetadata = 128 | Definition` — Implicitly loads Definition
- L20 _public enumerator_ `TwistSwingBehavior = 256 | Definition` — Implicitly loads Definition
- L21 _public enumerator_ `All = RBFBehavior | Geometry | MachineLearnedBehavior | JointBehaviorMetadata | TwistSwingBehavior`

#### enum `dna::UnknownLayerPolicy`  
`enum class UnknownLayerPolicy`  
_L28-31_
- L29 _public enumerator_ `Preserve`
- L30 _public enumerator_ `Ignore`

#### enum `dna::CoordinateSystemTransformPolicy`  
`enum class CoordinateSystemTransformPolicy`  
_L33-36_
- L34 _public enumerator_ `Preserve`
- L35 _public enumerator_ `Transform`

#### enum `dna::TranslationUnit`  
`enum class TranslationUnit`  
_L38-41_
- L39 _public enumerator_ `cm`
- L40 _public enumerator_ `m`

#### enum `dna::RotationUnit`  
`enum class RotationUnit`  
_L43-46_
- L44 _public enumerator_ `degrees`
- L45 _public enumerator_ `radians`

#### enum `dna::FaceWindingOrder`  
`enum class FaceWindingOrder : std::uint8_t`  
_L51-54_
- desc: Face vertex winding order, viewed along the outward surface normal. CCW: cross product of consecutive face vertices agrees in direction with stored normals. CW:  cross product of consecutive face vertices opposes stored normals (left-handed / DirectX style).
- L52 _public enumerator_ `ccw = 0`
- L53 _public enumerator_ `cw = 1`

#### struct `dna::Configuration`  
`struct Configuration`  
_L62-94_
- L65 _public member_ `DataLayer layer = DataLayer::All;` — Specify the layer up to which the data needs to be loaded. @see DataLayer
- L67 _public member_ `UnknownLayerPolicy unknownLayerPolicy = UnknownLayerPolicy::Preserve;` — Specify whether unknown layers are to be preserved or just ignored.
- L71 _public member_ `ConstArrayView<std::uint16_t> lods = {};` — An array specifying which exact LODs to load. @note usage of this parameter causes the values set for maxLOD / minLOD to be ignored. @warning All values in the array must be less than the value returned by getLODCount.
- L75 _public member_ `std::uint16_t maxLOD = 0;` — The maximum level of details to be loaded. @note A range of [0, LOD count - 1] for maxLOD / minLOD respectively indicates to load all LODs. @warning The maxLOD value must be less than the value returned by getLODCount.
- L79 _public member_ `std::uint16_t minLOD = static_cast<std::uint16_t>(-1);` — The minimum level of details to be loaded. @note A range of [0, LOD count - 1] for maxLOD / minLOD respectively indicates to load all LODs. @warning The minLOD value must be less than the value returned by getLODCount.
- L83 _public member_ `CoordinateSystemTransformPolicy coordinateSystemTransformPolicy = CoordinateSystemTransformPolicy::Preserve;` — Preserve transform policy will perform no conversion whatsoever Transform policy will perform conversion to the specified destination coordinate system unless the data is already in that system.
- L85 _public member_ `CoordinateSystem coordinateSystem = {};` — The axis directions for all coordinate axes.
- L87 _public member_ `RotationSequence rotationSequence = RotationSequence::xyz;` — The rotation sequence applied globally.
- L89 _public member_ `RotationSign rotationSign = {RotationDirection::positive, RotationDirection::positive, RotationDirection::positive};` — Rotation direction per each coordinate axis.
- L93 _public member_ `FaceWindingOrder faceWindingOrder = FaceWindingOrder::ccw;` — The face winding order of the geometry data. Authored DNAs are CCW (cross product of consecutive face vertices points along the outward surface normal). Converters normalize to this value when the CoordinateSystemTransformPolicy is set to Transform.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`
- L24 _function_ `inline DataLayer operator|(DataLayer lhs, DataLayer rhs)` (scope `dna`)
- L56 _typedef_ `using Direction = tdm::axis_dir;` (scope `dna`)
- L57 _typedef_ `using RotationDirection = tdm::rot_dir;` (scope `dna`)
- L58 _typedef_ `using RotationSequence = tdm::rot_seq;` (scope `dna`)
- L59 _typedef_ `using RotationSign = tdm::rot_sign;` (scope `dna`)
- L60 _typedef_ `using CoordinateSystem = tdm::coord_sys;` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define DNAAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define DNAAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define DNAAPI` — Build or use static library

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/JSONStreamReader.h` (Public)


#### class `dna::JSONStreamReader`  
`class DNAAPI JSONStreamReader : public StreamReader`  
_L14-38_
- inherits: `StreamReader`
- L28 _public prototype_ `static JSONStreamReader* create(BoundedIOStream* stream, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of JSONStreamReader @param stream Source stream from which data is going to be read. @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L35 _public prototype_ `static void destroy(JSONStreamReader* instance);` — @brief Method for freeing a JSONStreamReader instance. @param instance Instance of JSONStreamReader to be freed. @see create

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<dna::JSONStreamReader>`  
_L45-47_
- L46 _public typedef_ `using type = pma::FactoryCreate<dna::JSONStreamReader>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<dna::JSONStreamReader>`  
_L50-52_
- L51 _public typedef_ `using type = pma::FactoryDestroy<dna::JSONStreamReader>;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`
- L42 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/JSONStreamWriter.h` (Public)


#### class `dna::JSONStreamWriter`  
`class DNAAPI JSONStreamWriter : public StreamWriter`  
_L17-53_
- inherits: `StreamWriter`
- L33 _public prototype_ `static JSONStreamWriter* create(BoundedIOStream* stream, std::uint32_t indentWidth = 4u, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of JSONStreamWriter @param stream Stream into which the data is going to be written. @param indentWidth Number of spaces to use for indentation. @param memRes Memory resource to be used for allocations. @note If a memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L40 _public prototype_ `static void destroy(JSONStreamWriter* instance);` — @brief Method for freeing a JSONStreamWriter instance. @param instance Instance of JSONStreamWriter to be freed. @see create
- L45 _public prototype_ `virtual void setFrom(const BinaryStreamReader* source, DataLayer layer = DataLayer::All, UnknownLayerPolicy policy = UnknownLayerPolicy::Preserve, MemoryResource* memRes = nullptr) = 0;`
- L49 _public prototype_ `virtual void setFrom(const JSONStreamReader* source, DataLayer layer = DataLayer::All, UnknownLayerPolicy policy = UnknownLayerPolicy::Preserve, MemoryResource* memRes = nullptr) = 0;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<dna::JSONStreamWriter>`  
_L60-62_
- L61 _public typedef_ `using type = pma::FactoryCreate<dna::JSONStreamWriter>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<dna::JSONStreamWriter>`  
_L65-67_
- L66 _public typedef_ `using type = pma::FactoryDestroy<dna::JSONStreamWriter>;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`
- L57 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/Reader.h` (Public)


#### class `dna::Reader`  
`class DNAAPI Reader : public RBFBehaviorReader, public GeometryReader, public MachineLearnedBehaviorExtReader, public JointBehaviorMetadataReader, public TwistSwingBehaviorReader`  
_L24-37_
- inherits: `RBFBehaviorReader,GeometryReader,MachineLearnedBehaviorExtReader,JointBehaviorMetadataReader,TwistSwingBehaviorReader`
- desc: @brief The abstract Reader which its implementations are expected to inherit. @note This class combines the various different reader interfaces into a single interface. The artificial separation into multiple interfaces mirrors the DNA file structure that is separated into matching layers under the same names. As these layers can be selectively loaded, it might be convenient to slice-off interfaces which layers were not loaded.
- L36 _public prototype_ `virtual void unload(DataLayer layer) = 0;` — @brief Unload all data of the specified layer and all layers dependent on it. @param layer Layer whose data should be unloaded.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/StreamReader.h` (Public)


#### class `dna::StreamReader`  
`class DNAAPI StreamReader : public Reader`  
_L12-24_
- inherits: `Reader`
- L14 _public member_ `static const sc::StatusCode SignatureMismatchError;`
- L15 _public member_ `static const sc::StatusCode VersionMismatchError;`
- L16 _public member_ `static const sc::StatusCode InvalidDataError;`
- L23 _public prototype_ `virtual void read() = 0;` — @brief read data from stream into internal structures.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/StreamWriter.h` (Public)


#### class `dna::StreamWriter`  
`class DNAAPI StreamWriter : public Writer`  
_L11-18_
- inherits: `Writer`
- L17 _public prototype_ `virtual void write() = 0;` — @brief Write data to stream from internal structures.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/Writer.h` (Public)


#### class `dna::Writer`  
`class DNAAPI Writer : public RBFBehaviorWriter, public GeometryWriter, public MachineLearnedBehaviorExtWriter, public JointBehaviorMetadataWriter, public TwistSwingBehaviorWriter`  
_L25-53_
- inherits: `RBFBehaviorWriter,GeometryWriter,MachineLearnedBehaviorExtWriter,JointBehaviorMetadataWriter,TwistSwingBehaviorWriter`
- desc: @brief The abstract Writer which its implementations are expected to inherit. @note This class combines the various different writer interfaces into a single interface. The artificial separation into multiple interfaces in this case just mirrors the structure of the Reader hierarchy, as it's not possible to selectively write only specific layers.
- L49 _public prototype_ `virtual void setFrom(const Reader* source, DataLayer layer = DataLayer::All, UnknownLayerPolicy policy = UnknownLayerPolicy::Preserve, MemoryResource* memRes = nullptr);` — @brief Initialize the Writer from the given Reader. @note This function copies all the data from the given Reader into the Writer instance, by calling each getter function of the Reader, and passing the return values to the matching setter functions in the Writer. It is implemented in the abstract class itself to provide the functionality for all DNA Writers. @param source The source DNA Reader from which the data needs to be copied. @param layer Limit which layers should be taken over from the given source reader. @param policy Specify whether unknown layers are to be preserved or just ignored. @param memRes Optional memory resource to use for temporary allocations during copying.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/BehaviorReader.h` (Public)


#### class `dna::BehaviorReader`  
`class DNAAPI BehaviorReader : public virtual DefinitionReader`  
_L19-215_
- inherits: `DefinitionReader`
- desc: @brief Read-only accessors for DNA attributes that define the rig's evaluation. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L21 _protected prototype_ `virtual ~BehaviorReader();`
- L28 _public prototype_ `virtual ConstArrayView<std::uint16_t> getGUIToRawInputIndices() const = 0;` — @brief Input indices used for mapping gui to raw controls. @return View over the array of input indices.
- L33 _public prototype_ `virtual ConstArrayView<std::uint16_t> getGUIToRawOutputIndices() const = 0;` — @brief Output indices used for mapping gui to raw controls. @return View over the array of output indices.
- L39 _public prototype_ `virtual ConstArrayView<float> getGUIToRawFromValues() const = 0;` — @brief Filter values(lower-bounds) used to decide whether a particular entry should be evaluated or not during gui to raw control mapping. @return View over the array of filter values.
- L45 _public prototype_ `virtual ConstArrayView<float> getGUIToRawToValues() const = 0;` — @brief Filter values(upper-bounds) used to decide whether a particular entry should be evaluated or not during gui to raw control mapping. @return View over the array of filter values.
- L51 _public prototype_ `virtual ConstArrayView<float> getGUIToRawSlopeValues() const = 0;` — @brief Computational values(slope/gradient) used for calculating the output value during gui to raw control mapping. @return View over the array of computational values.
- L57 _public prototype_ `virtual ConstArrayView<float> getGUIToRawCutValues() const = 0;` — @brief Computational values(vertical intercept) used for calculating the output value during gui to raw control mapping. @return View over the array of computational values.
- L61 _public prototype_ `virtual std::uint16_t getPSDCount() const = 0;` — @brief The number of distinct PSD expressions.
- L66 _public prototype_ `virtual ConstArrayView<std::uint16_t> getPSDRowIndices() const = 0;` — @brief PSD(input) indices. @return View over the array of PSD indices.
- L71 _public prototype_ `virtual ConstArrayView<std::uint16_t> getPSDColumnIndices() const = 0;` — @brief Control(input) indices. @return View over the array of control indices.
- L76 _public prototype_ `virtual ConstArrayView<float> getPSDValues() const = 0;` — @brief Weights associated with each PSD row and column pair. @return View over the array of weights.
- L80 _public prototype_ `virtual std::uint16_t getJointRowCount() const = 0;` — @brief Number of rows in the entire, uncompressed joint matrix.
- L84 _public prototype_ `virtual std::uint16_t getJointColumnCount() const = 0;` — @brief Number of columns in the entire, uncompressed joint matrix.
- L89 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const = 0;` — @brief Joint attribute indices (output indices) for the requested LOD. @return View over the array of joint indices.
- L93 _public prototype_ `virtual std::uint16_t getJointGroupCount() const = 0;` — @brief Number of joint groups present in the entire joint matrix.
- L109 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointGroupLODs(std::uint16_t jointGroupIndex) const = 0;` — @brief Number of rows per each level of detail for the requested joint group. @note Each element's position represents the level itself, while the value denotes the number of rows within the joint group belonging to that level. e.g.: [12, 9, 3] |   |  + LOD-2 contains first 3 rows |   + LOD-1 contains first 9 rows + LOD-0 contains first 12 rows @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning jointGroupIndex must be less than the value returned by getJointGroupCount. @return View over the array of LOD bounds.
- L120 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointGroupInputIndices(std::uint16_t jointGroupIndex) const = 0;` — @brief Column indices that the requested joint group contains. @note The column indices point into the entire, uncompressed joint matrix. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning jointGroupIndex must be less than the value returned by getJointGroupCount. @return View over the array of column indices.
- L131 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointGroupOutputIndices(std::uint16_t jointGroupIndex) const = 0;` — @brief Row indices that the requested joint group contains. @note The row indices point into the entire, uncompressed joint matrix. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning jointGroupIndex must be less than the value returned by getJointGroupCount. @return View over the array of row indices.
- L140 _public prototype_ `virtual ConstArrayView<float> getJointGroupValues(std::uint16_t jointGroupIndex) const = 0;` — @brief Values that the requested joint group contains. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning jointGroupIndex must be less than the value returned by getJointGroupCount. @return View over the array of values.
- L152 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointGroupJointIndices(std::uint16_t jointGroupIndex) const = 0;` — @brief Joint indices that the requested joint group contains. @note These joint indices can be used to get the joint names through DefinitionReader::getJointName. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning jointGroupIndex must be less than the value returned by getJointGroupCount. @return View over the array of joint indices. @see DefinitionReader
- L163 _public prototype_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelLODs() const = 0;` — @brief Input index count per each level of detail for blend shape channels. @note Each element's position represents the level itself  (e.g. [0,1,2,3,4,5] Value 0 is LOD with highest of details, value 5 is LOD with lowest details), while the value denotes the number of input indices belonging to that level. @warning These LOD values are not interchangeable with the LOD indices from DefinitionReader::getBlendShapeChannelIndicesForLOD. @return View over the array of LOD bounds.
- L168 _public prototype_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelInputIndices() const = 0;` — @brief Input indices used to index into the input vector. @return View over the array of input indices.
- L173 _public prototype_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelOutputIndices() const = 0;` — @brief Output indices specify the positions of blend shape channel output values. @return View over the array of output indices.
- L182 _public prototype_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapLODs() const = 0;` — @brief Row count per each level of detail for animated maps. @note Each element's position represents the level itself  (e.g. [0,1,2,3,4,5] Value 0 is LOD with highest of details, value 5 is LOD with lowest details), while the value denotes the number of rows (within the conditional table), belonging to that level. @return View over the array of LOD bounds.
- L187 _public prototype_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapInputIndices() const = 0;` — @brief Input indices used to index into the array of input values. @return View over the array of input indices.
- L192 _public prototype_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapOutputIndices() const = 0;` — @brief Output indices that specify the computed output value's position. @return View over the array of output indices.
- L198 _public prototype_ `virtual ConstArrayView<float> getAnimatedMapFromValues() const = 0;` — @brief Filter values(lower-bounds) used to decide whether a particular entry should be evaluated or not. @return View over the array of filter values.
- L204 _public prototype_ `virtual ConstArrayView<float> getAnimatedMapToValues() const = 0;` — @brief Filter values(upper-bounds) used to decide whether a particular entry should be evaluated or not. @return View over the array of filter values.
- L209 _public prototype_ `virtual ConstArrayView<float> getAnimatedMapSlopeValues() const = 0;` — @brief Computational values(slope/gradient) used for calculating the output value. @return View over the array of computational values.
- L214 _public prototype_ `virtual ConstArrayView<float> getAnimatedMapCutValues() const = 0;` — @brief Computational values(vertical intercept) used for calculating the output value. @return View over the array of computational values.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/BehaviorWriter.h` (Public)


#### class `dna::BehaviorWriter`  
`class DNAAPI BehaviorWriter : public virtual DefinitionWriter`  
_L19-298_
- inherits: `DefinitionWriter`
- desc: @brief Write-only accessors for DNA attributes that define the rig's evaluation. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L21 _protected prototype_ `virtual ~BehaviorWriter();`
- L31 _public prototype_ `virtual void setGUIToRawInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) = 0;` — @brief Input indices used for mapping gui to raw controls. @param inputIndices The source address from which the input indices are to be copied. @param count The number of input indices to copy.
- L39 _public prototype_ `virtual void setGUIToRawOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) = 0;` — @brief Output indices used for mapping gui to raw controls. @param outputIndices The source address from which the output indices are to be copied. @param count The number of output indices to copy.
- L48 _public prototype_ `virtual void setGUIToRawFromValues(const float* fromValues, std::uint16_t count) = 0;` — @brief Filter values(lower-bounds) used to decide whether a particular entry should be evaluated or not during gui to raw control mapping. @param fromValues The source address from which the filter values are to be copied. @param count The number of filter values to copy.
- L57 _public prototype_ `virtual void setGUIToRawToValues(const float* toValues, std::uint16_t count) = 0;` — @brief Filter values(upper-bounds) used to decide whether a particular entry should be evaluated or not during gui to raw control mapping. @param toValues The source address from which the filter values are to be copied. @param count The number of filter values to copy.
- L66 _public prototype_ `virtual void setGUIToRawSlopeValues(const float* slopeValues, std::uint16_t count) = 0;` — @brief Computational values(slope/gradient) used for calculating the output value during gui to raw control mapping. @param slopeValues The source address from which the computational values are to be copied. @param count The number of computational values to copy.
- L75 _public prototype_ `virtual void setGUIToRawCutValues(const float* cutValues, std::uint16_t count) = 0;` — @brief Computational values(vertical intercept) used for calculating the output value during gui to raw control mapping. @param cutValues The source address from which the computational values are to be copied. @param count The number of computational values to copy.
- L79 _public prototype_ `virtual void setPSDCount(std::uint16_t count) = 0;` — @brief The number of distinct PSD expressions.
- L87 _public prototype_ `virtual void setPSDRowIndices(const std::uint16_t* rowIndices, std::uint16_t count) = 0;` — @brief PSD(input) indices which will become the rows of the PSD matrix. @param rowIndices The source address from which the PSD indices are to be copied. @param count The number of PSD indices to copy.
- L95 _public prototype_ `virtual void setPSDColumnIndices(const std::uint16_t* columnIndices, std::uint16_t count) = 0;` — @brief Control(input) indices which will become the columns of the PSD matrix. @param columnIndices The source address from which the control indices are to be copied. @param count The number of control indices to copy.
- L103 _public prototype_ `virtual void setPSDValues(const float* weights, std::uint16_t count) = 0;` — @brief Weights associated with each PSD row and column pair. @param weights The source address from which the weight values are to be copied. @param count The number of weight values to copy.
- L107 _public prototype_ `virtual void setJointRowCount(std::uint16_t rowCount) = 0;` — @brief Number of rows in the entire, uncompressed joint matrix.
- L111 _public prototype_ `virtual void setJointColumnCount(std::uint16_t columnCount) = 0;` — @brief Number of columns in the entire, uncompressed joint matrix.
- L115 _public prototype_ `virtual void clearJointGroups() = 0;` — @brief Delete all joint groups.
- L123 _public prototype_ `virtual void deleteJointGroup(std::uint16_t jointGroupIndex) = 0;` — @brief Delete the specified joint group. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning jointGroupIndex must be less than the value returned by getJointGroupCount.
- L143 _public prototype_ `virtual void setJointGroupLODs(std::uint16_t jointGroupIndex, const std::uint16_t* lods, std::uint16_t count) = 0;` — @brief Number of rows per each level of detail for the specified joint group. @note Each element's position represents the level itself, while the value denotes the number of rows within the joint group belonging to that level. e.g.: [12, 9, 3] |   |  + LOD-2 contains first 3 rows |   + LOD-1 contains first 9 rows + LOD-0 contains first 12 rows @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @note The joint group storage will be implicitly resized (if needed) to provide storage for the number of joint groups that is inferred from the specified index. @param lods The source address from which the lod bounds are to be copied. @param count The number of lod bounds to copy.
- L158 _public prototype_ `virtual void setJointGroupInputIndices(std::uint16_t jointGroupIndex, const std::uint16_t* inputIndices, std::uint16_t count) = 0;` — @brief Column indices that the specified joint group contains. @note The column indices point into the entire, uncompressed joint matrix. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @note The joint group storage will be implicitly resized (if needed) to provide storage for the number of joint groups that is inferred from the specified index. @param inputIndices The source address from which the column indices are to be copied. @param count The number of column indices to copy.
- L175 _public prototype_ `virtual void setJointGroupOutputIndices(std::uint16_t jointGroupIndex, const std::uint16_t* outputIndices, std::uint16_t count) = 0;` — @brief Row indices that the specified joint group contains. @note The row indices point into the entire, uncompressed joint matrix. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @note The joint group storage will be implicitly resized (if needed) to provide storage for the number of joint groups that is inferred from the specified index. @param outputIndices The source address from which the row indices are to be copied. @param count The number of row indices to copy.
- L190 _public prototype_ `virtual void setJointGroupValues(std::uint16_t jointGroupIndex, const float* values, std::uint32_t count) = 0;` — @brief Values that the specified joint group contains. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @note The joint group storage will be implicitly resized (if needed) to provide storage for the number of joint groups that is inferred from the specified index. @param values The source address from which the values are to be copied. @param count The number of values to copy.
- L203 _public prototype_ `virtual void setJointGroupJointIndices(std::uint16_t jointGroupIndex, const std::uint16_t* jointIndices, std::uint16_t count) = 0;` — @brief Joint indices that the specified joint group contains. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @note The joint group storage will be implicitly resized (if needed) to provide storage for the number of joint groups that is inferred from the specified index. @param jointIndices The source address from which the joint indices are to be copied. @param count The number of joint indices to copy.
- L219 _public prototype_ `virtual void setBlendShapeChannelLODs(const std::uint16_t* lods, std::uint16_t count) = 0;` — @brief Input index count per each level of detail for blend shapes. @note Each element's position represents the level itself  (e.g. [0,1,2,3,4,5] Value 0 is LOD with highest of details, value 5 is LOD with lowest details), while the value denotes the number of input indices belonging to that level. @param lods The source address from which the lod bounds are to be copied. @param count The number of lod bounds to copy. @warning The LOD values set here are not interchangeable with the LOD indices set in DefinitionWriter::setBlendShapeNameIndices and DefinitionWriter::setLODBlendShapeMapping
- L227 _public prototype_ `virtual void setBlendShapeChannelInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) = 0;` — @brief Input indices used to index into the input vector. @param inputIndices The source address from which the input indices are to be copied. @param count The number of input indices to copy.
- L235 _public prototype_ `virtual void setBlendShapeChannelOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) = 0;` — @brief Output indices specify the positions of blend shape output values. @param outputIndices The source address from which the output indices are to be copied. @param count The number of output indices to copy.
- L247 _public prototype_ `virtual void setAnimatedMapLODs(const std::uint16_t* lods, std::uint16_t count) = 0;` — @brief Row count per each level of detail for animated maps. @note Each element's position represents the level itself  (e.g. [0,1,2,3,4,5] Value 0 is LOD with highest of details, value 5 is LOD with lowest details), while the value denotes the number of rows (within the conditional table), belonging to that level. @param lods The source address from which the lod bounds are to be copied. @param count The number of lod bounds to copy.
- L255 _public prototype_ `virtual void setAnimatedMapInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) = 0;` — @brief Input indices used to index into the array of input values. @param inputIndices The source address from which the input indices are to be copied. @param count The number of input indices to copy.
- L263 _public prototype_ `virtual void setAnimatedMapOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) = 0;` — @brief Output indices that specify the computed output value's position. @param outputIndices The source address from which the output indices are to be copied. @param count The number of output indices to copy.
- L272 _public prototype_ `virtual void setAnimatedMapFromValues(const float* fromValues, std::uint16_t count) = 0;` — @brief Filter values(lower-bounds) used to decide whether a particular entry should be evaluated or not. @param fromValues The source address from which the filter values are to be copied. @param count The number of filter values to copy.
- L281 _public prototype_ `virtual void setAnimatedMapToValues(const float* toValues, std::uint16_t count) = 0;` — @brief Filter values(upper-bounds) used to decide whether a particular entry should be evaluated or not. @param toValues The source address from which the filter values are to be copied. @param count The number of filter values to copy.
- L289 _public prototype_ `virtual void setAnimatedMapSlopeValues(const float* slopeValues, std::uint16_t count) = 0;` — @brief Computational values(slope/gradient) used for calculating the output value. @param slopeValues The source address from which the computational values are to be copied. @param count The number of computational values to copy.
- L297 _public prototype_ `virtual void setAnimatedMapCutValues(const float* cutValues, std::uint16_t count) = 0;` — @brief Computational values(vertical intercept) used for calculating the output value. @param cutValues The source address from which the computational values are to be copied. @param count The number of computational values to copy.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/DefinitionReader.h` (Public)


#### struct `dna::MeshBlendShapeChannelMapping`  
`struct MeshBlendShapeChannelMapping`  
_L17-20_
- desc: @brief Mapping that associates a blend shape channel to it's mesh.
- L18 _public member_ `std::uint16_t meshIndex;`
- L19 _public member_ `std::uint16_t blendShapeChannelIndex;`

#### class `dna::DefinitionReader`  
`class DNAAPI DefinitionReader : public DescriptorReader`  
_L28-295_
- inherits: `DescriptorReader`
- desc: @brief Read-only accessors for DNA attributes that represent the rig's static data. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L30 _protected prototype_ `virtual ~DefinitionReader();`
- L36 _public prototype_ `virtual std::uint16_t getGUIControlCount() const = 0;` — @brief Number of GUI controls.
- L45 _public prototype_ `virtual StringView getGUIControlName(std::uint16_t index) const = 0;` — @brief Name of the requested GUI control. @param index A name's position in the zero-indexed array of GUI control names. @warning The index must be less than the value returned by getGUIControlCount. @return View over the GUI control name string.
- L49 _public prototype_ `virtual std::uint16_t getRawControlCount() const = 0;` — @brief Number of raw controls.
- L58 _public prototype_ `virtual StringView getRawControlName(std::uint16_t index) const = 0;` — @brief Name of the requested raw control. @param index A name's position in the zero-indexed array of raw control names. @warning The index must be less than the value returned by getRawControlCount. @return View over the control name string.
- L62 _public prototype_ `virtual std::uint16_t getJointCount() const = 0;` — @brief Number of raw joints.
- L71 _public prototype_ `virtual StringView getJointName(std::uint16_t index) const = 0;` — @brief Name of the requested joint. @param index A name's position in the zero-indexed array of joint names. @warning The index must be less than the value returned by getJointCount. @return View over the joint name string.
- L77 _public prototype_ `virtual std::uint16_t getJointIndexListCount() const = 0;` — @brief Number of joint index lists. @note This value is useful only in the context of DefinitionWriter.
- L88 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of joint indices for the specified LOD. @param lod The level of detail which joints are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the joint indices. @see getLODCount @see getJointName
- L112 _public prototype_ `virtual std::uint16_t getJointParentIndex(std::uint16_t index) const = 0;` — @brief Index of the requested joint's parent. @note The joint hierarchy may be traversed and reconstructed using this function. Example: Joint names: [A, B, C, D, E, F, G, H, I] Hierarchy:   [0, 0, 0, 1, 1, 4, 2, 6, 2] Describes the following hierarchy: A + B | + D | + E |   + F + C + G | + H + I Requesting the parent index of joint 5 (joint name: F) would return 4 (joint name: E). Requesting the parent index of the root joint: 0 (joint name: A) would return the same index 0. An out of bounds request (an index greater than the number of joints returns UINT16_MAX). @param index The joint index which parent is being requested.
- L116 _public prototype_ `virtual std::uint16_t getBlendShapeChannelCount() const = 0;` — @brief Number of blend shape channels.
- L125 _public prototype_ `virtual StringView getBlendShapeChannelName(std::uint16_t index) const = 0;` — @brief Name of the requested blend shape channel. @param index A name's position in the zero-indexed array of blend shape channel names. @warning The index must be less than the value returned by getBlendShapeChannelCount. @return View over the blend shape channel name string.
- L131 _public prototype_ `virtual std::uint16_t getBlendShapeChannelIndexListCount() const = 0;` — @brief Number of blend shape channel index lists. @note This value is useful only in the context of DefinitionWriter.
- L144 _public prototype_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of blend shape channel indices for the specified LOD. @param lod The level of detail which blend shape channels are being requested. @warning The lod index must be less than the value returned by DescriptorReader::getLODCount. @return View over the blend shape channel indices. @warning These LOD indices are not interchangeable with the LOD values from BehaviorReader::getBlendShapeChannelLODs. @see DescriptorReader::getLODCount @see getBlendShapeChannelName
- L148 _public prototype_ `virtual std::uint16_t getAnimatedMapCount() const = 0;` — @brief Number of animated maps.
- L157 _public prototype_ `virtual StringView getAnimatedMapName(std::uint16_t index) const = 0;` — @brief Name of the requested animated map. @param index A name's position in the zero-indexed array of animated map names. @warning The index must be less than the value returned by getAnimatedMapCount. @return View over the animated map name string.
- L163 _public prototype_ `virtual std::uint16_t getAnimatedMapIndexListCount() const = 0;` — @brief Number of animated map index lists. @note This value is useful only in the context of DefinitionWriter.
- L174 _public prototype_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of animated map indices for the specified LOD. @param lod The level of detail which animated maps are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the animated map indices. @see getLODCount @see getAnimatedMapName
- L178 _public prototype_ `virtual std::uint16_t getMeshCount() const = 0;` — @brief Number of meshes.
- L187 _public prototype_ `virtual StringView getMeshName(std::uint16_t index) const = 0;` — @brief Name of the requested mesh. @param index A name's position in the zero-indexed array of mesh names. @warning The index must be less than the value returned by getMeshCount. @return View over the mesh name string.
- L193 _public prototype_ `virtual std::uint16_t getMeshIndexListCount() const = 0;` — @brief Number of mesh index lists. @note This value is useful only in the context of DefinitionWriter.
- L204 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMeshIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of mesh indices for the specified LOD. @param lod The level of detail which meshes are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the mesh indices. @see getLODCount @see getMeshName
- L208 _public prototype_ `virtual std::uint16_t getMeshBlendShapeChannelMappingCount() const = 0;` — @brief Number of mesh-blend shape channel mapping items.
- L216 _public prototype_ `virtual MeshBlendShapeChannelMapping getMeshBlendShapeChannelMapping(std::uint16_t index) const = 0;` — @param index A mapping's position in the zero-indexed array of mesh-blend shape channel mappings. @warning The index must be less than the value returned by getMeshBlendShapeChannelMappingCount. @return A structure holding the mesh index and the associated blend shape channel index.
- L230 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMeshBlendShapeChannelMappingIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of mesh-blend shape channel mapping indices for the specified LOD. @note The indices from this list can be used with the getMeshBlendShapeChannelMapping API to retrieve individual mapping items. @param lod The level of detail which meshes are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the mesh blend shape channel mapping indices. @see getLODCount @see getMeshBlendShapeChannelMapping
- L238 _public prototype_ `virtual Vector3 getNeutralJointTranslation(std::uint16_t index) const = 0;` — @param index A joint's position in the zero-indexed array of joint translations. @warning The index must be less than the value returned by getJointCount. @return The joint's translation (x, y, z).
- L246 _public prototype_ `virtual ConstArrayView<float> getNeutralJointTranslationXs() const = 0;` — @brief List of all translation X values. @note This is an advanced API for performance critical access, for more convenient usage see getNeutralJointTranslation. @return View over all X values. @see getNeutralJointTranslation
- L254 _public prototype_ `virtual ConstArrayView<float> getNeutralJointTranslationYs() const = 0;` — @brief List of all translation Y values. @note This is an advanced API for performance critical access, for more convenient usage see getNeutralJointTranslation. @return View over all Y values. @see getNeutralJointTranslation
- L262 _public prototype_ `virtual ConstArrayView<float> getNeutralJointTranslationZs() const = 0;` — @brief List of all translation Z values. @note This is an advanced API for performance critical access, for more convenient usage see getNeutralJointTranslation. @return View over all Z values. @see getNeutralJointTranslation
- L270 _public prototype_ `virtual Vector3 getNeutralJointRotation(std::uint16_t index) const = 0;` — @param index A joint's position in the zero-indexed array of joint rotations. @warning The index must be less than the value returned by getJointCount. @return The joint's rotation (x, y, z).
- L278 _public prototype_ `virtual ConstArrayView<float> getNeutralJointRotationXs() const = 0;` — @brief List of all rotation X values. @note This is an advanced API for performance critical access, for more convenient usage see getNeutralJointRotation. @return View over all X values. @see getNeutralJointRotation
- L286 _public prototype_ `virtual ConstArrayView<float> getNeutralJointRotationYs() const = 0;` — @brief List of all rotation Y values. @note This is an advanced API for performance critical access, for more convenient usage see getNeutralJointRotation. @return View over all Y values. @see getNeutralJointRotation
- L294 _public prototype_ `virtual ConstArrayView<float> getNeutralJointRotationZs() const = 0;` — @brief List of all rotation Z values. @note This is an advanced API for performance critical access, for more convenient usage see getNeutralJointRotation. @return View over all Z values. @see getNeutralJointRotation

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/DefinitionWriter.h` (Public)


#### class `dna::DefinitionWriter`  
`class DNAAPI DefinitionWriter : public DescriptorWriter`  
_L20-328_
- inherits: `DescriptorWriter`
- desc: @brief Write-only accessors for DNA attributes that represent the rig's static data. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L22 _protected prototype_ `virtual ~DefinitionWriter();`
- L28 _public prototype_ `virtual void clearGUIControlNames() = 0;` — @brief Delete all stored GUI control names.
- L41 _public prototype_ `virtual void setGUIControlName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified GUI control. @param index A name's position in the zero-indexed array of GUI control names. @note The control name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L45 _public prototype_ `virtual void clearRawControlNames() = 0;` — @brief Delete all stored raw control names.
- L58 _public prototype_ `virtual void setRawControlName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified raw control. @param index A name's position in the zero-indexed array of raw control names. @note The control name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L62 _public prototype_ `virtual void clearJointNames() = 0;` — @brief Delete all stored joint names.
- L75 _public prototype_ `virtual void setJointName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified joint. @param index A name's position in the zero-indexed array of joint names. @note The joint name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L79 _public prototype_ `virtual void clearJointIndices() = 0;` — @brief Delete all stored joint indices.
- L98 _public prototype_ `virtual void setJointIndices(std::uint16_t index, const std::uint16_t* jointIndices, std::uint16_t count) = 0;` — @brief Store a list of joint indices onto a specified index. @param index A position in a zero-indexed array where joint indices are stored. @note The index denotes the position of an entire joint index list, not the position of it's individual elements, i.e. the row index in a 2D matrix of joint indices. @note The joint index storage will be implicitly resized (if needed) to provide storage for the number of joint indices that is inferred from the specified index. @param jointIndices The source address from which the joint indices are to be copied. @note These indices can be used to access joint names through DefinitionReader::getJointName. @param count The number of joint indices to copy.
- L102 _public prototype_ `virtual void clearLODJointMappings() = 0;` — @brief Delete all stored LOD to joint list index mapping entries.
- L111 _public prototype_ `virtual void setLODJointMapping(std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which joints belong to which level of detail. @param lod The actual level of detail to which the joints are being associated. @param index The index onto which joints indices were assigned using setJointIndices. @see setJointIndices
- L115 _public prototype_ `virtual void clearBlendShapeChannelNames() = 0;` — @brief Delete all stored blend shape channel names.
- L128 _public prototype_ `virtual void setBlendShapeChannelName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified blend shape channel. @param index A name's position in the zero-indexed array of blend shape channel names. @note The blend shape channel name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L132 _public prototype_ `virtual void clearBlendShapeChannelIndices() = 0;` — @brief Delete all stored blend shape channel indices.
- L151 _public prototype_ `virtual void setBlendShapeChannelIndices(std::uint16_t index, const std::uint16_t* blendShapeChannelIndices, std::uint16_t count) = 0;` — @brief Store a list of blend shape channel name indices onto a specified index. @param index A position in a zero-indexed array where blend shape channel name indices are stored. @note The index denotes the position of an entire blend shape channel index list, not the position of it's individual elements, i.e. the row index in a 2D matrix of blend shape channel indices. @note The blend shape channel index storage will be implicitly resized (if needed) to provide storage for the number of blend shape channel name indices that is inferred from the specified index. @param blendShapeChannelIndices The source address from which the blend shape channel name indices are to be copied. @note These indices can be used to access blend shape channel names through DefinitionReader::getBlendShapeChannelName. @param count The number of blend shape channel name indices to copy.
- L157 _public prototype_ `virtual void clearLODBlendShapeChannelMappings() = 0;` — @brief Delete all stored LOD to blend shape channel list index mapping entries.
- L168 _public prototype_ `virtual void setLODBlendShapeChannelMapping(std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which blend shape channels belong to which level of detail. @param lod The actual level of detail to which the blend shape channels are being associated. @param index The index onto which blend shape channel name indices were assigned using setBlendShapeChannelIndices. @warning The LOD indices set here are not interchangeable with the LOD values set in BehaviorWriter::setBlendShapeChannelLODs. @see setBlendShapeChannelIndices
- L172 _public prototype_ `virtual void clearAnimatedMapNames() = 0;` — @brief Delete all stored animated map names.
- L185 _public prototype_ `virtual void setAnimatedMapName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified animated map. @param index A name's position in the zero-indexed array of animated map names. @note The animated map name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L189 _public prototype_ `virtual void clearAnimatedMapIndices() = 0;` — @brief Delete all stored animated map indices.
- L208 _public prototype_ `virtual void setAnimatedMapIndices(std::uint16_t index, const std::uint16_t* animatedMapIndices, std::uint16_t count) = 0;` — @brief Store a list of animated map name indices onto a specified index. @param index A position in a zero-indexed array where animated map name indices are stored. @note The index denotes the position of an entire animated map index list, not the position of it's individual elements, i.e. the row index in a 2D matrix of animated map indices. @note The animated map index storage will be implicitly resized (if needed) to provide storage for the number of animated map name indices that is inferred from the specified index. @param animatedMapIndices The source address from which the animated map name indices are to be copied. @note These indices can be used to access animated map names through DefinitionReader::getAnimatedMapName. @param count The number of animated map name indices to copy.
- L212 _public prototype_ `virtual void clearLODAnimatedMapMappings() = 0;` — @brief Delete all stored LOD to animated map list index mapping entries.
- L221 _public prototype_ `virtual void setLODAnimatedMapMapping(std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which animated maps belong to which level of detail. @param lod The actual level of detail to which the animated maps are being associated. @param index The index onto which animated map indices were assigned using setAnimatedMapIndices. @see setAnimatedMapIndices
- L225 _public prototype_ `virtual void clearMeshNames() = 0;` — @brief Delete all stored mesh names.
- L238 _public prototype_ `virtual void setMeshName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified mesh. @param index A name's position in the zero-indexed array of mesh names. @note The mesh name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L242 _public prototype_ `virtual void clearMeshIndices() = 0;` — @brief Delete all stored mesh indices.
- L261 _public prototype_ `virtual void setMeshIndices(std::uint16_t index, const std::uint16_t* meshIndices, std::uint16_t count) = 0;` — @brief Store a list of mesh name indices onto a specified index. @param index A position in a zero-indexed array where mesh name indices are stored. @note The index denotes the position of an entire mesh index list, not the position of it's individual elements, i.e. the row index in a 2D matrix of mesh indices. @note The mesh index storage will be implicitly resized (if needed) to provide storage for the number of mesh name indices that is inferred from the specified index. @param meshIndices The source address from which the mesh name indices are to be copied. @note These indices can be used to access mesh names through DefinitionReader::getMeshName. @param count The number of mesh name indices to copy.
- L265 _public prototype_ `virtual void clearLODMeshMappings() = 0;` — @brief Delete all stored LOD to mesh list index mapping entries.
- L274 _public prototype_ `virtual void setLODMeshMapping(std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which meshes belong to which level of detail. @param lod The actual level of detail to which the meshes are being associated. @param index The index onto which mesh indices were assigned using setMeshIndices. @see setMeshIndices
- L278 _public prototype_ `virtual void clearMeshBlendShapeChannelMappings() = 0;` — @brief Delete all stored mesh to blend shape channel mapping entries.
- L288 _public prototype_ `virtual void setMeshBlendShapeChannelMapping(std::uint32_t index, std::uint16_t meshIndex, std::uint16_t blendShapeChannelIndex) = 0;` — @brief Associate a blend shape channel with it's mesh. @param index A mapping's position in the zero-indexed array of mesh-blend shape channel mappings. @param meshIndex A mesh's position in the zero-indexed array of mesh names. @param blendShapeChannelIndex A blend shape channel's position in the zero-indexed array of blend shape channel names.
- L313 _public prototype_ `virtual void setJointHierarchy(const std::uint16_t* jointIndices, std::uint16_t count) = 0;` — @brief A simple array describing the parent-child relationships between joints. @note Example: Joint names: [A, B, C, D, E, F, G, H] Hierarchy:   [0, 0, 0, 1, 1, 4, 2, 2] Describes the following hierarchy: A + B | + D | + E |   + F + C + G + H @param jointIndices The source address from which the joint indices are to be copied. @note These indices can be used to access joint names through DefinitionReader::getJointName. @param count The number of joint indices to copy.
- L320 _public prototype_ `virtual void setNeutralJointTranslations(const Vector3* translations, std::uint16_t count) = 0;` — @param translations The source address from which the translations are to be copied. @param count The number of translation values to copy.
- L327 _public prototype_ `virtual void setNeutralJointRotations(const Vector3* rotations, std::uint16_t count) = 0;` — @param rotations The source address from which the rotations are to be copied. @param count The number of rotation values to copy.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/Descriptor.h` (Public)


#### enum `dna::Archetype`  
`enum class Archetype`  
_L10-17_
- L11 _public enumerator_ `asian`
- L12 _public enumerator_ `black`
- L13 _public enumerator_ `caucasian`
- L14 _public enumerator_ `hispanic`
- L15 _public enumerator_ `alien`
- L16 _public enumerator_ `other`

#### enum `dna::Gender`  
`enum class Gender`  
_L19-23_
- L20 _public enumerator_ `male`
- L21 _public enumerator_ `female`
- L22 _public enumerator_ `other`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/DescriptorReader.h` (Public)


#### class `dna::DescriptorReader`  
`class DNAAPI DescriptorReader : public HeaderReader`  
_L20-81_
- inherits: `HeaderReader`
- desc: @brief Read-only accessors for various metadata about the character and the rig. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L22 _protected prototype_ `virtual ~DescriptorReader();`
- L25 _public prototype_ `virtual StringView getName() const = 0;`
- L26 _public prototype_ `virtual Archetype getArchetype() const = 0;`
- L27 _public prototype_ `virtual Gender getGender() const = 0;`
- L28 _public prototype_ `virtual std::uint16_t getAge() const = 0;`
- L29 _public prototype_ `virtual std::uint32_t getMetaDataCount() const = 0;`
- L37 _public prototype_ `virtual StringView getMetaDataKey(std::uint32_t index) const = 0;` — @param index A position in the zero-indexed array of key-value pairs. @warning The index must be less than the value returned by getMetaDataCount. @return View over the key name string.
- L49 _public prototype_ `virtual StringView getMetaDataValue(const char* key) const = 0;` — @brief Stored metadata value associated with the given key. @note If no value is associated with the given key, the returned view will contain nullptr and will have a size of 0. @param key A unique-known key that has a value associated to it. @warning The key must be null-terminated. @return View over the metadata value string.
- L50 _public prototype_ `virtual TranslationUnit getTranslationUnit() const = 0;`
- L51 _public prototype_ `virtual RotationUnit getRotationUnit() const = 0;`
- L52 _public prototype_ `virtual CoordinateSystem getCoordinateSystem() const = 0;`
- L53 _public prototype_ `virtual RotationSequence getRotationSequence() const = 0;`
- L54 _public prototype_ `virtual RotationSign getRotationSign() const = 0;`
- L55 _public prototype_ `virtual FaceWindingOrder getFaceWindingOrder() const = 0;`
- L61 _public prototype_ `virtual std::uint16_t getLODCount() const = 0;` — @brief Available levels of detail (e.g. 6 which means the following levels are available: [0,1,2,3,4,5], where 0 is the LOD with the highest details, and 5 is the LOD with lowest details).
- L67 _public prototype_ `virtual std::uint16_t getDBMaxLOD() const = 0;` — @brief The maximum level of detail stored in the DNA data for this character. @note The value is relative to LOD-0 from the database.
- L73 _public prototype_ `virtual StringView getDBComplexity() const = 0;` — @brief Name of the input control interface used to drive this character rig. @note This parameter denotes the character's input control complexity.
- L80 _public prototype_ `virtual StringView getDBName() const = 0;` — @brief Name of the database from which the character originates. @note All characters from the same database must have the same Definition, but may have different complexity or LOD.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/DescriptorWriter.h` (Public)


#### class `dna::DescriptorWriter`  
`class DNAAPI DescriptorWriter : public HeaderWriter`  
_L20-85_
- inherits: `HeaderWriter`
- desc: @brief Write-only accessors to various metadata about the character and the rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L22 _protected prototype_ `virtual ~DescriptorWriter();`
- L31 _public prototype_ `virtual void setName(const char* name) = 0;` — @param name A null-terminated string. @note The passed in name is copied, which will involve an allocation.
- L32 _public prototype_ `virtual void setArchetype(Archetype archetype) = 0;`
- L33 _public prototype_ `virtual void setGender(Gender gender) = 0;`
- L34 _public prototype_ `virtual void setAge(std::uint16_t age) = 0;`
- L38 _public prototype_ `virtual void clearMetaData() = 0;` — @brief Empties the metadata storage, delete all key-value pairs.
- L50 _public prototype_ `virtual void setMetaData(const char* key, const char* value) = 0;` — @brief Associate the metadata value with the given key. @param key A unique, null-terminated key, to which the given value will be assigned. @param value A null-terminated, metadata value, which is to be assigned to the given key. @note Consecutive calls using the same key will overwrite any existing data. @note Passing nullptr as the value argument will cause the associated key to be deleted.
- L51 _public prototype_ `virtual void setTranslationUnit(TranslationUnit unit) = 0;`
- L52 _public prototype_ `virtual void setRotationUnit(RotationUnit unit) = 0;`
- L53 _public prototype_ `virtual void setCoordinateSystem(CoordinateSystem system) = 0;`
- L54 _public prototype_ `virtual void setRotationSequence(RotationSequence rotationSequence) = 0;`
- L55 _public prototype_ `virtual void setRotationSign(const RotationSign& rotationSign) = 0;`
- L56 _public prototype_ `virtual void setFaceWindingOrder(FaceWindingOrder faceWindingOrder) = 0;`
- L64 _public prototype_ `virtual void setLODCount(std::uint16_t lodCount) = 0;` — @brief Available levels of detail (e.g. 6 which means the following levels are available: [0,1,2,3,4,5], where 0 is the LOD with the highest details, and 5 is the LOD with lowest details). @param lodCount The number of levels available.
- L68 _public prototype_ `virtual void setDBMaxLOD(std::uint16_t lod) = 0;` — @brief The maximum level of detail stored in the DNA data for this character.
- L76 _public prototype_ `virtual void setDBComplexity(const char* name) = 0;` — @brief Name of the input control interface used to drive this character rig. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L84 _public prototype_ `virtual void setDBName(const char* name) = 0;` — @brief Name of the database from which the character originates. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/Geometry.h` (Public)


#### struct `dna::TextureCoordinate`  
`struct TextureCoordinate`  
_L11-14_
- L12 _public member_ `float u;`
- L13 _public member_ `float v;`

#### struct `dna::VertexLayout`  
`struct VertexLayout`  
_L20-24_
- L21 _public member_ `std::uint32_t position;`
- L22 _public member_ `std::uint32_t textureCoordinate;`
- L23 _public member_ `std::uint32_t normal;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`
- L16 _typedef_ `using Position = Vector3;` (scope `dna`)
- L17 _typedef_ `using Normal = Vector3;` (scope `dna`)
- L18 _typedef_ `using Delta = Vector3;` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/GeometryReader.h` (Public)


#### class `dna::GeometryReader`  
`class DNAAPI GeometryReader : public virtual DefinitionReader`  
_L19-436_
- inherits: `DefinitionReader`
- desc: @brief Read-only accessors to the geometry data associated with a rig. @warning Implementors should inherit from Reader itself and not this class.
- L21 _protected prototype_ `virtual ~GeometryReader();`
- L31 _public prototype_ `virtual std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const = 0;` — @brief Number of vertex positions in the entire mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L45 _public prototype_ `virtual Position getVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;` — @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param vertexIndex The index of the vertex position in the zero-indexed array of vertex positions. @warning vertexIndex must be less than the value returned by getVertexPositionCount. @note The vertices are sorted by the vertex ID. @return The vertex position.
- L57 _public prototype_ `virtual ConstArrayView<float> getVertexPositionXs(std::uint16_t meshIndex) const = 0;` — @brief List of all vertex position X values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexPosition. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all X values. @see getVertexPosition
- L69 _public prototype_ `virtual ConstArrayView<float> getVertexPositionYs(std::uint16_t meshIndex) const = 0;` — @brief List of all vertex position Y values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexPosition. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all Y values. @see getVertexPosition
- L81 _public prototype_ `virtual ConstArrayView<float> getVertexPositionZs(std::uint16_t meshIndex) const = 0;` — @brief List of all vertex position Z values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexPosition. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all Z values. @see getVertexPosition
- L89 _public prototype_ `virtual std::uint32_t getVertexTextureCoordinateCount(std::uint16_t meshIndex) const = 0;` — @brief Number of texture coordinates in the entire mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L101 _public prototype_ `virtual TextureCoordinate getVertexTextureCoordinate(std::uint16_t meshIndex, std::uint32_t textureCoordinateIndex) const = 0;` — @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param textureCoordinateIndex The index of the texture coordinate in the zero-indexed array of texture coordinates. @warning textureCoordinateIndex must be less than the value returned by getVertexTextureCoordinateCount. @return The texture coordinate.
- L113 _public prototype_ `virtual ConstArrayView<float> getVertexTextureCoordinateUs(std::uint16_t meshIndex) const = 0;` — @brief List of all texture coordinate U values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexTextureCoordinate. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all U values. @see getVertexTextureCoordinate
- L125 _public prototype_ `virtual ConstArrayView<float> getVertexTextureCoordinateVs(std::uint16_t meshIndex) const = 0;` — @brief List of all texture coordinate V values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexTextureCoordinate. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all V values. @see getVertexTextureCoordinate
- L133 _public prototype_ `virtual std::uint32_t getVertexNormalCount(std::uint16_t meshIndex) const = 0;` — @brief Number of vertex normals in the entire mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L145 _public prototype_ `virtual Normal getVertexNormal(std::uint16_t meshIndex, std::uint32_t normalIndex) const = 0;` — @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param normalIndex The index of the vertex normal in the zero-indexed array of vertex normals. @warning normalIndex must be less than the value returned by getVertexNormalCount. @return The vertex normal.
- L157 _public prototype_ `virtual ConstArrayView<float> getVertexNormalXs(std::uint16_t meshIndex) const = 0;` — @brief List of all normal X values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexNormal. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all X values. @see getVertexNormal
- L169 _public prototype_ `virtual ConstArrayView<float> getVertexNormalYs(std::uint16_t meshIndex) const = 0;` — @brief List of all normal Y value for the referenced meshs. @note This is an advanced API for performance critical access, for more convenient usage see getVertexNormal. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all Y values. @see getVertexNormal
- L181 _public prototype_ `virtual ConstArrayView<float> getVertexNormalZs(std::uint16_t meshIndex) const = 0;` — @brief List of all normal Z values for the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexNormal. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all Z values. @see getVertexNormal
- L191 _public prototype_ `virtual std::uint32_t getVertexLayoutCount(std::uint16_t meshIndex) const = 0;` — @brief Number of vertex layouts in the entire mesh. @note A vertex layout is a collection of vertex attributes. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L210 _public prototype_ `virtual VertexLayout getVertexLayout(std::uint16_t meshIndex, std::uint32_t layoutIndex) const = 0;` — @brief Vertex layouts contain only attribute indices which can be used to query the actual attributes, such as positions, texture coordinates and normals, which are associated with the vertex. @note The indices from a layout are usable with the above defined APIs. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param layoutIndex The index of the layout in the zero-indexed array of vertex layouts. @warning layoutIndex must be less than the value returned by getVertexLayoutCount. @see getVertexPosition @see getVertexTextureCoordinate @see getVertexNormal
- L222 _public prototype_ `virtual ConstArrayView<std::uint32_t> getVertexLayoutPositionIndices(std::uint16_t meshIndex) const = 0;` — @brief Position indices for each vertex of the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexLayout. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all vertex position indices values. @see getVertexLayout
- L234 _public prototype_ `virtual ConstArrayView<std::uint32_t> getVertexLayoutTextureCoordinateIndices(std::uint16_t meshIndex) const = 0;` — @brief Texture coordinate indices for each vertex of the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexLayout. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all vertex texture coordinate indices. @see getVertexLayout
- L246 _public prototype_ `virtual ConstArrayView<std::uint32_t> getVertexLayoutNormalIndices(std::uint16_t meshIndex) const = 0;` — @brief Normal indices for each vertex of the referenced mesh. @note This is an advanced API for performance critical access, for more convenient usage see getVertexLayout. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @return View over all vertex normal indices. @see getVertexLayout
- L254 _public prototype_ `virtual std::uint32_t getFaceCount(std::uint16_t meshIndex) const = 0;` — @brief Number of faces that belong to the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L269 _public prototype_ `virtual ConstArrayView<std::uint32_t> getFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex) const = 0;` — @brief List of vertex layout indices the belong to a face on the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param faceIndex A face's position in the zero-indexed array of faces that belong to the above referenced mesh. @warning faceIndex must be less than the value returned by getFaceCount. @return View over the list of vertex layout indices. @see getVertexLayout
- L277 _public prototype_ `virtual std::uint16_t getMaximumInfluencePerVertex(std::uint16_t meshIndex) const = 0;` — @brief The maximum number of joints that may influence any single vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L285 _public prototype_ `virtual std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const = 0;` — @brief Number of skin weights associated with the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L298 _public prototype_ `virtual ConstArrayView<float> getSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;` — @brief List of skin weights influencing the requested vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param vertexIndex A position in the zero-indexed array of vertices. @warning vertexIndex must be less than the value returned by getVertexPositionCount. @return View over the list of skin weights.
- L314 _public prototype_ `virtual ConstArrayView<std::uint16_t> getSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;` — @brief List of joint indices associated with each skin weight for the specified vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param vertexIndex A position in the zero-indexed array of vertices. @warning vertexIndex must be less than the value returned by getVertexPositionCount. @note The joint indices are stored in the same order as the weights they are associated with. @return View over the list of joint indices.
- L323 _public prototype_ `virtual std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const = 0;` — @brief Number of blend shapes that belong to the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L335 _public prototype_ `virtual std::uint16_t getBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const = 0;` — @brief The matching blend shape channel index of the requested blend shape target. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount. @see DefinitionReader::getBlendShapeChannelName
- L347 _public prototype_ `virtual std::uint32_t getBlendShapeTargetDeltaCount(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const = 0;` — @brief Number of deltas that belong to the specified blend shape. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount.
- L363 _public prototype_ `virtual Delta getBlendShapeTargetDelta(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint32_t deltaIndex) const = 0;` — @brief List of deltas for each affected vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount. @param deltaIndex A position in the zero-indexed array of blend shapes deltas. @warning deltaIndex must be less than the value returned by getBlendShapeTargetDeltaCount.
- L381 _public prototype_ `virtual ConstArrayView<float> getBlendShapeTargetDeltaXs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const = 0;` — @brief List of all delta X values for the referenced blend shape target. @note This is an advanced API for performance critical access, for more convenient usage see getBlendShapeTargetDelta. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount. @return View over all X values. @see getBlendShapeTargetDelta
- L398 _public prototype_ `virtual ConstArrayView<float> getBlendShapeTargetDeltaYs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const = 0;` — @brief List of all delta Y values for the referenced blend shape target. @note This is an advanced API for performance critical access, for more convenient usage see getBlendShapeTargetDelta. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount. @return View over all Y values. @see getBlendShapeTargetDelta
- L415 _public prototype_ `virtual ConstArrayView<float> getBlendShapeTargetDeltaZs(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const = 0;` — @brief List of all delta Z values for the referenced blend shape target. @note This is an advanced API for performance critical access, for more convenient usage see getBlendShapeTargetDelta. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount. @return View over all Z values. @see getBlendShapeTargetDelta
- L434 _public prototype_ `virtual ConstArrayView<std::uint32_t> getBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex) const = 0;` — @brief Vertex position indices affected by the referenced blend shape target. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @warning blendShapeTargetIndex must be less than the value returned by getBlendShapeTargetCount. @note The vertex position indices are stored in the same order as the deltas they are associated with. These indices can be used to query the associated vertices themselves through getVertexPosition. @see getVertexPosition @return View over the list of vertex position indices.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/GeometryWriter.h` (Public)


#### class `dna::GeometryWriter`  
`class DNAAPI GeometryWriter : public virtual DefinitionWriter`  
_L19-245_
- inherits: `DefinitionWriter`
- desc: @brief Write-only accessors for the geometry data associated with a rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L21 _protected prototype_ `virtual ~GeometryWriter();`
- L27 _public prototype_ `virtual void clearMeshes() = 0;` — @brief Delete all meshes.
- L35 _public prototype_ `virtual void deleteMesh(std::uint16_t meshIndex) = 0;` — @brief Delete the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L48 _public prototype_ `virtual void setVertexPositions(std::uint16_t meshIndex, const Position* positions, std::uint32_t count) = 0;` — @brief List of vertex positions. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param positions The source address from which the vertex positions are to be copied. @param count The number of vertex positions to copy. @note The mesh storage will be implicitly resized (if needed) to provide storage for the number of meshes that is inferred from the specified index.
- L61 _public prototype_ `virtual void setVertexTextureCoordinates(std::uint16_t meshIndex, const TextureCoordinate* textureCoordinates, std::uint32_t count) = 0;` — @brief List of vertex texture coordinates. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param textureCoordinates The source address from which the texture coordinates are to be copied. @param count The number of texture coordinates to copy. @note The mesh storage will be implicitly resized (if needed) to provide storage for the number of meshes that is inferred from the specified index.
- L76 _public prototype_ `virtual void setVertexNormals(std::uint16_t meshIndex, const Normal* normals, std::uint32_t count) = 0;` — @brief List of vertex normals. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param normals The source address from which the normals are to be copied. @param count The number of normals to copy. @note The mesh storage will be implicitly resized (if needed) to provide storage for the number of meshes that is inferred from the specified index.
- L89 _public prototype_ `virtual void setVertexLayouts(std::uint16_t meshIndex, const VertexLayout* layouts, std::uint32_t count) = 0;` — @brief List of vertex layouts the belong to the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param layouts The source address from which the layouts are to be copied. @param count The number of layouts to copy. @note The mesh storage will be implicitly resized (if needed) to provide storage for the number of meshes that is inferred from the specified index.
- L97 _public prototype_ `virtual void clearFaceVertexLayoutIndices(std::uint16_t meshIndex) = 0;` — @brief Delete all lists of vertex layout indices for the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L116 _public prototype_ `virtual void setFaceVertexLayoutIndices(std::uint16_t meshIndex, std::uint32_t faceIndex, const std::uint32_t* layoutIndices, std::uint32_t count) = 0;` — @brief Vertex layout indices that belong to the specified face. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param faceIndex A face's position in the zero-indexed array of faces that belong to the above referenced mesh. @param layoutIndices The source address from which the layout indices are to be copied. @note The layout indices point into the array that is set through setVertexLayouts @param count The number of vertices to copy. @note Both the mesh storage itself and it's face storage will be implicitly resized (if needed) to provide storage for the number of meshes and/or faces that are inferred from the specified indexes.
- L126 _public prototype_ `virtual void setMaximumInfluencePerVertex(std::uint16_t meshIndex, std::uint16_t maxInfluenceCount) = 0;` — @param meshIndex A mesh's position in the zero-indexed array of meshes. @param maxInfluenceCount The maximum number of joints that may influence any single vertex.
- L134 _public prototype_ `virtual void clearSkinWeights(std::uint16_t meshIndex) = 0;` — @brief Delete all skin weights for the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L152 _public prototype_ `virtual void setSkinWeightsValues(std::uint16_t meshIndex, std::uint32_t vertexIndex, const float* weights, std::uint16_t count) = 0;` — @brief List of skin weights influencing the referenced vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param vertexIndex A position in the zero-indexed array of vertex positions. @param weights The source address from which the weights are to be copied. @param count The number of weights to copy. @note Both the mesh storage itself and it's skin weight storage will be implicitly resized (if needed) to provide storage for the number of meshes and/or skin-weight lists that are inferred from the specified indexes. @warning The sum of weights must add up to 1.
- L174 _public prototype_ `virtual void setSkinWeightsJointIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex, const std::uint16_t* jointIndices, std::uint16_t count) = 0;` — @brief List of joint indices associated with each skin weight for the specified vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param vertexIndex A position in the zero-indexed array of vertex positions. @param jointIndices The source address from which the joint indices are to be copied. @param count The number of joint indices to copy. @note Both the mesh storage itself and it's joint index list storage will be implicitly resized (if needed) to provide storage for the number of meshes and/or joint index lists that are inferred from the specified indexes. @warning The joint indices must be stored in the same order as the weights they are associated with.
- L185 _public prototype_ `virtual void clearBlendShapeTargets(std::uint16_t meshIndex) = 0;` — @brief Delete all blend shape targets for the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L201 _public prototype_ `virtual void setBlendShapeChannelIndex(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, std::uint16_t blendShapeChannelIndex) = 0;` — @brief The matching blend shape channel index of the specified blend shape target. @note Associate the mesh-local blend shape target index with the absolute blend shape channel index as found in the Definition layer. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @param blendShapeChannelIndex The index of the specified blend shape channel in the Definition layer. @note Both the mesh storage itself and it's blend shape target storage will be implicitly resized (if needed) to provide storage for the number of meshes and/or blend shape targets that are inferred from the specified indexes.
- L219 _public prototype_ `virtual void setBlendShapeTargetDeltas(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, const Delta* deltas, std::uint32_t count) = 0;` — @brief List of deltas for each affected vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @param deltas The source address from which the blend shape target deltas are to be copied. @param count The number of blend shape target deltas to copy. @note Both the mesh storage itself and it's blend shape target storage will be implicitly resized (if needed) to provide storage for the number of meshes and/or blend shape targets that are inferred from the specified indexes.
- L241 _public prototype_ `virtual void setBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, const std::uint32_t* vertexIndices, std::uint32_t count) = 0;` — @brief Vertex position indices affected by the specified blend shape target. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param blendShapeTargetIndex A position in the zero-indexed array of blend shape targets within the specified mesh. @param vertexIndices The source address from which the vertex position indices are to be copied. @param count The number of vertex position indices to copy. @note Both the mesh storage itself and it's blend shape target storage will be implicitly resized (if needed) to provide storage for the number of meshes and/or blend shape targets that are inferred from the specified indexes. @warning The vertex position indices must be stored in the same order as the deltas they are associated with.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/HeaderReader.h` (Public)


#### class `dna::HeaderReader`  
`class DNAAPI HeaderReader`  
_L16-23_
- desc: @brief Read-only accessors to the header data associated with a rig. @warning Implementors should inherit from Reader itself and not this class.
- L18 _protected prototype_ `virtual ~HeaderReader();`
- L21 _public prototype_ `virtual std::uint16_t getFileFormatGeneration() const = 0;`
- L22 _public prototype_ `virtual std::uint16_t getFileFormatVersion() const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/HeaderWriter.h` (Public)


#### class `dna::HeaderWriter`  
`class DNAAPI HeaderWriter`  
_L17-24_
- desc: @brief Write-only accessors for the header data associated with a rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L19 _protected prototype_ `virtual ~HeaderWriter();`
- L22 _public prototype_ `virtual void setFileFormatGeneration(std::uint16_t generation) = 0;`
- L23 _public prototype_ `virtual void setFileFormatVersion(std::uint16_t version) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/JointBehaviorMetadata.h` (Public)


#### enum `dna::TranslationRepresentation`  
`enum class TranslationRepresentation`  
_L9-11_
- L10 _public enumerator_ `Vector`

#### enum `dna::RotationRepresentation`  
`enum class RotationRepresentation`  
_L13-16_
- L14 _public enumerator_ `EulerAngles`
- L15 _public enumerator_ `Quaternion`

#### enum `dna::ScaleRepresentation`  
`enum class ScaleRepresentation`  
_L18-20_
- L19 _public enumerator_ `Vector`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/JointBehaviorMetadataReader.h` (Public)


#### class `dna::JointBehaviorMetadataReader`  
`class DNAAPI JointBehaviorMetadataReader : public virtual DefinitionReader`  
_L17-58_
- inherits: `DefinitionReader`
- desc: @brief Read-only accessors to the joint metadata that affects how are they evaluated at runtime. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L19 _protected prototype_ `virtual ~JointBehaviorMetadataReader();`
- L33 _public prototype_ `virtual TranslationRepresentation getJointTranslationRepresentation(std::uint16_t jointIndex) const = 0;` — @brief Get the desired internal representation of a joint's translation component during rig evaluation. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @return The representation of the joint's translation component. @note This metadata affects how joints are calculated, as the given representation will be used internally by the implementation that evaluates them.
- L45 _public prototype_ `virtual RotationRepresentation getJointRotationRepresentation(std::uint16_t jointIndex) const = 0;` — @brief Get the desired internal representation of a joint's rotation component during rig evaluation. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @return The representation of the joint's rotation component. @note This metadata affects how joints are calculated, as the given representation will be used internally by the implementation that evaluates them.
- L57 _public prototype_ `virtual ScaleRepresentation getJointScaleRepresentation(std::uint16_t jointIndex) const = 0;` — @brief Get the desired internal representation of a joint's scale component during rig evaluation. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @return The representation of the joint's scale component. @note This metadata affects how joints are calculated, as the given representation will be used internally by the implementation that evaluates them.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/JointBehaviorMetadataWriter.h` (Public)


#### class `dna::JointBehaviorMetadataWriter`  
`class DNAAPI JointBehaviorMetadataWriter : public virtual DefinitionWriter`  
_L17-65_
- inherits: `DefinitionWriter`
- desc: @brief Write-only accessors to the joint metadata that affects how are they evaluated at runtime. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L19 _protected prototype_ `virtual ~JointBehaviorMetadataWriter();`
- L25 _public prototype_ `virtual void clearJointRepresentations() = 0;` — @brief Delete all representations.
- L38 _public prototype_ `virtual void setJointTranslationRepresentation(std::uint16_t jointIndex, TranslationRepresentation representation) = 0;` — @brief Set the desired internal representation of a joint's translation component during rig evaluation. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @param representation The desired representation of the joint's translation component. @note This metadata affects how joints are calculated, as the given representation will be used internally by the implementation that evaluates them.
- L51 _public prototype_ `virtual void setJointRotationRepresentation(std::uint16_t jointIndex, RotationRepresentation representation) = 0;` — @brief Set the desired internal representation of a joint's rotation component during rig evaluation. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @param representation The desired representation of the joint's rotation component. @note This metadata affects how joints are calculated, as the given representation will be used internally by the implementation that evaluates them.
- L64 _public prototype_ `virtual void setJointScaleRepresentation(std::uint16_t jointIndex, ScaleRepresentation representation) = 0;` — @brief Set the desired internal representation of a joint's scale component during rig evaluation. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @param representation The desired representation of the joint's scale component. @note This metadata affects how joints are calculated, as the given representation will be used internally by the implementation that evaluates them.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/MachineLearnedBehavior.h` (Public)


#### enum `dna::ActivationFunction`  
`enum class ActivationFunction`  
_L7-13_
- L8 _public enumerator_ `linear`
- L9 _public enumerator_ `relu`
- L10 _public enumerator_ `leakyrelu`
- L11 _public enumerator_ `tanh`
- L12 _public enumerator_ `sigmoid`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/MachineLearnedBehaviorExt.h` (Public)


#### enum `dna::MachineLearnedBehaviorOperationType`  
`enum class MachineLearnedBehaviorOperationType : std::uint16_t`  
_L9-15_
- L10 _public enumerator_ `Unspecified`
- L11 _public enumerator_ `Gather`
- L12 _public enumerator_ `Scatter`
- L13 _public enumerator_ `MLP`
- L14 _public enumerator_ `WeightedSum`

#### enum `dna::MachineLearnedBehaviorParameterKey`  
`enum class MachineLearnedBehaviorParameterKey : std::uint16_t`  
_L17-28_
- L18 _public enumerator_ `JointTranslationType`
- L19 _public enumerator_ `JointRotationType`
- L20 _public enumerator_ `JointScaleType`
- L21 _public enumerator_ `JointCoordinateSystemAxisX`
- L22 _public enumerator_ `JointCoordinateSystemAxisY`
- L23 _public enumerator_ `JointCoordinateSystemAxisZ`
- L24 _public enumerator_ `JointRotationSignAxisX`
- L25 _public enumerator_ `JointRotationSignAxisY`
- L26 _public enumerator_ `JointRotationSignAxisZ`
- L27 _public enumerator_ `JointRotationSequence`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/MachineLearnedBehaviorExtReader.h` (Public)


#### class `dna::MachineLearnedBehaviorExtReader`  
`class DNAAPI MachineLearnedBehaviorExtReader : public virtual MachineLearnedBehaviorReader`  
_L20-193_
- inherits: `MachineLearnedBehaviorReader`
- desc: @brief Read-only accessors to the neural network extension data associated with a rig. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L22 _protected prototype_ `virtual ~MachineLearnedBehaviorExtReader();`
- L28 _public prototype_ `virtual std::uint16_t getMLTypeCount() const = 0;` — @brief Number of distinct ML models.
- L38 _public prototype_ `virtual std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const = 0;` — @brief Number of sets of operations within a single model. @note Operations within a single set are safe to execute in parallel, while each operation set itself is expected to be executed sequentially, one after the other. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount.
- L50 _public prototype_ `virtual std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;` — @brief Number of operation within a single operation set. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount.
- L67 _public prototype_ `virtual MachineLearnedBehaviorOperationType getMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const = 0;` — @brief Get the type of the selected operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @warning The index must be less than the value returned by getMLOperationCount. @return The operation type.
- L86 _public prototype_ `virtual ConstArrayView<std::uint32_t> getMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const = 0;` — @brief List of optional static parameters that need to be passed to an operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @warning The index must be less than the value returned by getMLOperationCount. @return View over operation parameters
- L111 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const = 0;` — @brief List of operation set indices that are specified as dependencies of the current operation. @note This list needs to be paired with the list returned by getMLOperationDependencyOperationIndices, where each operation set index and operation index under the same index form a single pair, specifying the (operation-set, operation) index pair that points to a dependency of the current operation. @note As operation sets are evaluated in lock-step, each subsequent operation set will be able to access the results of previous operation sets, and these indices might reference operations whose results are needed as input for the current operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @warning The index must be less than the value returned by getMLOperationCount. @return View over operation set indices
- L136 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const = 0;` — @brief List of operation indices that are specified as dependencies of the current operation. @note This list needs to be paired with the list returned by getMLOperationDependencyOperationSetIndices, where each operation set index and operation index under the same index form a single pair, specifying the (operation-set, operation) index pair that points to a dependency of the current operation. @note As operation sets are evaluated in lock-step, each subsequent operation set will be able to access the results of previous operation sets, and these indices might reference operations whose results are needed as input for the current operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @warning The index must be less than the value returned by getMLOperationCount. @return View over operation indices
- L151 _public prototype_ `virtual std::uint16_t getMLOperationIndexListCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;` — @brief Number of operation index lists. @note This value is useful only in the context of MachineLearnedBehaviorExtWriter. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount.
- L169 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod) const = 0;` — @brief List of operation indices for the specified LOD. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @warning The index must be less than the value returned by getMLTypeCount. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @warning The index must be less than the value returned by getMLOperationSetCount. @param lod The level of detail for which operations are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the operation instance indices. @see DescriptorReader::getLODCount
- L177 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLJointsInputIndices() const = 0;` — @brief Input index list which point into the input buffer used by RigLogic. @note This buffer is partially populated by the ML model itself, providing the joint transformation values which the ML joints evaluator takes and forwards as joint outputs.
- L182 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLJointsOutputIndices() const = 0;` — @brief Output index list which specifies the joint attribute index for each input index. @note Each output index is paired with an input index returned by getMLJointsInputIndices.
- L187 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLJointsParameterKeys() const = 0;` — @brief Optional metadata that can be assigned to ML joints. @note This is used to provide the joint attribute count that the ML model outputs.
- L192 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLJointsParameterValues() const = 0;` — @brief Optional metadata that can be assigned to ML joints. @note This is used to provide the joint attribute count that the ML model outputs.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/MachineLearnedBehaviorExtWriter.h` (Public)


#### class `dna::MachineLearnedBehaviorExtWriter`  
`class DNAAPI MachineLearnedBehaviorExtWriter : public virtual MachineLearnedBehaviorWriter`  
_L19-232_
- inherits: `MachineLearnedBehaviorWriter`
- desc: @brief Write-only accessors for the operation instance data associated with a rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L21 _protected prototype_ `virtual ~MachineLearnedBehaviorExtWriter();`
- L27 _public prototype_ `virtual void clearMLExtData() = 0;` — @brief Delete all stored ML extension data.
- L33 _public prototype_ `virtual void clearMLOperationSets(std::uint16_t mlTypeIndex) = 0;` — @brief Delete all data associated with a single ML type. @param mlTypeIndex The ML model position in the zero-indexed array of ML models.
- L41 _public prototype_ `virtual void clearMLOperations(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) = 0;` — @brief Delete all operations within a single operation set. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets.
- L56 _public prototype_ `virtual void setMLOperationType(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, MachineLearnedBehaviorOperationType operationType) = 0;` — @brief Set the type of the ML operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @param operationType The type of the operation. @note The storage will be implicitly resized (if needed) to provide storage for the new data to be stored.
- L76 _public prototype_ `virtual void setMLOperationParameters(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint32_t* parameters, std::uint16_t count) = 0;` — @brief Set optional static parameters that need to be passed to an operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @note The storage will be implicitly resized (if needed) to provide storage for the new data to be stored. @param parameters The source address from which the parameters are to be copied. @param count The number of parameters to copy.
- L100 _public prototype_ `virtual void setMLOperationDependencyOperationSetIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint16_t* indices, std::uint16_t count) = 0;` — @brief Set the indices of operation sets that are dependencies of this operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @note The storage will be implicitly resized (if needed) to provide storage for the new data to be stored. @param indices The source address from which the dependency operation set indices are to be copied. @param count The number of dependency operation set indices to copy. @note This list needs to be paired with the list set by setMLOperationDependencyOperationIndices, where each operation set index and operation index under the same index form a single pair, specifying the (operation-set, operation) index pair that points to a dependency of the current operation.
- L124 _public prototype_ `virtual void setMLOperationDependencyOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex, const std::uint16_t* indices, std::uint16_t count) = 0;` — @brief Set the indices of operations that are dependencies of this operation. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @param mlOperationIndex The operation position in the zero-indexed array of operations within the selected set. @note The storage will be implicitly resized (if needed) to provide storage for the new data to be stored. @param indices The source address from which the dependency operation indices are to be copied. @param count The number of dependency operation indices to copy. @note This list needs to be paired with the list set by setMLOperationDependencyOperationSetIndices, where each operation set index and operation index under the same index form a single pair, specifying the (operation-set, operation) index pair that points to a dependency of the current operation.
- L132 _public prototype_ `virtual void clearMLOperationIndicesAndLODMappings() = 0;` — @brief Delete all stored operation indices and their corresponding LOD mappings.
- L140 _public prototype_ `virtual void clearMLOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) = 0;` — @brief Delete the operation indices used for operation-LOD mapping for a specific operation set. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets.
- L148 _public prototype_ `virtual void clearLODMLOperationMappings(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) = 0;` — @brief Delete the index-list-LOD mapping entries used for operation-LOD mapping for a specific operation set. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets.
- L174 _public prototype_ `virtual void setMLOperationIndices(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t index, const std::uint16_t* mlOperationIndices, std::uint16_t count) = 0;` — @brief Store a list of operation indices onto a specified index. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @param index A position in a zero-indexed array where operation indices are stored. @note The index denotes the position of an entire operation index list, not the position of its individual elements, i.e. the row index in a 2D matrix of operation indices. @note The operation index storage will be implicitly resized (if needed) to provide storage for the number of operation indices that is inferred from the specified index. @param mlOperationIndices The source address from which the operation indices are to be copied. @note These indices can be used to access operations through the above defined APIs. @param count The number of operation indices to copy. @note The storage will be implicitly resized (if needed) to provide storage for the new data to be stored.
- L191 _public prototype_ `virtual void setLODMLOperationMapping(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which operations belong to which level of detail. @param mlTypeIndex The ML model position in the zero-indexed array of ML models. @param mlOperationSetIndex The operation set position in the zero-indexed array of operation sets. @param lod The actual level of detail to which the operations are being associated. @param index The index onto which operation indices were assigned using setMLOperationIndices. @see setMLOperationIndices
- L204 _public prototype_ `virtual void setMLJointsInputIndices(const std::uint16_t* inputIndices, std::uint16_t count) = 0;` — @brief Input index list which point into the input buffer used by RigLogic. @note This buffer is partially populated by the ML model itself, providing the joint transformation values which the ML joints evaluator takes and forwards as joint outputs. @param inputIndices The source address from which the input indices are to be copied. @param count The number of input indices to copy.
- L213 _public prototype_ `virtual void setMLJointsOutputIndices(const std::uint16_t* outputIndices, std::uint16_t count) = 0;` — @brief Output index list which specifies the joint attribute index for each input index. @note Each output index is paired with an input index returned by getMLJointsInputIndices. @param outputIndices The source address from which the output indices are to be copied. @param count The number of output indices to copy.
- L222 _public prototype_ `virtual void setMLJointsParameterKeys(const std::uint16_t* parameterKeys, std::uint16_t count) = 0;` — @brief Optional metadata that can be assigned to ML joints. @note This is used to provide the joint attribute count that the ML model outputs. @param parameterKeys The source address from which the parameter keys are to be copied. @param count The number of parameter keys to copy.
- L231 _public prototype_ `virtual void setMLJointsParameterValues(const std::uint16_t* parameterValues, std::uint16_t count) = 0;` — @brief Optional metadata that can be assigned to ML joints. @note This is used to provide the joint attribute count that the ML model outputs. @param parameterValues The source address from which the parameter values are to be copied. @param count The number of parameter values to copy.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/MachineLearnedBehaviorReader.h` (Public)


#### class `dna::MachineLearnedBehaviorReader`  
`class DNAAPI MachineLearnedBehaviorReader : public virtual DefinitionReader`  
_L19-184_
- inherits: `DefinitionReader`
- desc: @brief Read-only accessors to the neural network data associated with a rig. @warning Implementors should inherit from Reader itself and not this class.
- L21 _protected prototype_ `virtual ~MachineLearnedBehaviorReader();`
- L27 _public prototype_ `virtual std::uint16_t getMLControlCount() const = 0;` — @brief Number of ML controls.
- L36 _public prototype_ `virtual StringView getMLControlName(std::uint16_t index) const = 0;` — @brief Name of the requested ML control. @param index A name's position in the zero-indexed array of ML control names. @warning The index must be less than the value returned by getMLControlCount. @return View over the control name string.
- L40 _public prototype_ `virtual std::uint16_t getNeuralNetworkCount() const = 0;` — @brief Number of neural networks.
- L46 _public prototype_ `virtual std::uint16_t getNeuralNetworkIndexListCount() const = 0;` — @brief Number of neural network index lists. @note This value is useful only in the context of MachineLearnedBehaviorWriter.
- L56 _public prototype_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of neural network indices for the specified LOD. @param lod The level of detail for which neural networks are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the neural network indices. @see DescriptorReader::getLODCount
- L64 _public prototype_ `virtual std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const = 0;` — @brief Number of mesh regions. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by DefinitionReader::getMeshCount.
- L77 _public prototype_ `virtual StringView getMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex) const = 0;` — @brief Name of the requested region. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by DefinitionReader::getMeshCount. @param regionIndex A name's position in the zero-indexed array of region names. @warning The index must be less than the value returned by getMeshRegionCount. @return View over the region name string.
- L92 _public prototype_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex) const = 0;` — @brief List of neural network indices for the specified mesh and region. @param meshIndex The mesh for which neural networks are being requested. @warning The mesh index must be less than the value returned by getMeshCount. @param regionIndex The region for which neural networks are being requested. @warning The region index must be less than the value returned by getMeshRegionCount. @return View over the neural network indices. @see DefinitionReader::getMeshCount @see DefinitionReader::getMeshRegionCount
- L103 _public prototype_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkInputIndices(std::uint16_t netIndex) const = 0;` — @brief List of input control indices that drive the referenced neural network. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @return View over the input control indices. @see getNeuralNetworkCount
- L113 _public prototype_ `virtual ConstArrayView<std::uint16_t> getNeuralNetworkOutputIndices(std::uint16_t netIndex) const = 0;` — @brief List of control indices whose weights are computed by the neural network. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @return View over the control indices. @see getNeuralNetworkCount
- L122 _public prototype_ `virtual std::uint16_t getNeuralNetworkLayerCount(std::uint16_t netIndex) const = 0;` — @brief The number of neural network layers (excluding the input layer). @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @see getNeuralNetworkCount
- L136 _public prototype_ `virtual ActivationFunction getNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex) const = 0;` — @brief The activation function type. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @param layerIndex A name's position in the zero-indexed array of neural network layers. @warning The index must be less than the value returned by getNeuralNetworkLayerCount. @see getNeuralNetworkCount @see getNeuralNetworkLayerCount
- L152 _public prototype_ `virtual ConstArrayView<float> getNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex) const = 0;` — @brief Additional activation function parameters (if any). @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @param layerIndex A name's position in the zero-indexed array of neural network layers. @warning The index must be less than the value returned by getNeuralNetworkLayerCount. @return View over the activation function parameters (defined in the context of the activation function). @see getNeuralNetworkCount @see getNeuralNetworkLayerCount
- L168 _public prototype_ `virtual ConstArrayView<float> getNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex) const = 0;` — @brief Neural network layer bias values. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @param layerIndex A name's position in the zero-indexed array of neural network layers. @warning The index must be less than the value returned by getNeuralNetworkLayerCount. @return View over the bias values (for each unit in the layer). @see getNeuralNetworkCount @see getNeuralNetworkLayerCount
- L183 _public prototype_ `virtual ConstArrayView<float> getNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex) const = 0;` — @brief Neural network layer weights. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by getNeuralNetworkCount. @param layerIndex A name's position in the zero-indexed array of neural network layers. @warning The index must be less than the value returned by getNeuralNetworkLayerCount. @return View over the weight values (a vector for each unit in the layer). @see getNeuralNetworkCount @see getNeuralNetworkLayerCount

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/MachineLearnedBehaviorWriter.h` (Public)


#### class `dna::MachineLearnedBehaviorWriter`  
`class DNAAPI MachineLearnedBehaviorWriter : public virtual DefinitionWriter`  
_L19-247_
- inherits: `DefinitionWriter`
- desc: @brief Write-only accessors for the neural network data associated with a rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L21 _protected prototype_ `virtual ~MachineLearnedBehaviorWriter();`
- L27 _public prototype_ `virtual void clearMLControlNames() = 0;` — @brief Delete all stored ML control names.
- L40 _public prototype_ `virtual void setMLControlName(std::uint16_t index, const char* name) = 0;` — @brief Name of the specified ML control. @param index A name's position in the zero-indexed array of ML control names. @note The control name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L44 _public prototype_ `virtual void clearNeuralNetworks() = 0;` — @brief Delete all neural networks.
- L48 _public prototype_ `virtual void clearNeuralNetworkIndices() = 0;` — @brief Delete all stored neural network indices.
- L67 _public prototype_ `virtual void setNeuralNetworkIndices(std::uint16_t index, const std::uint16_t* netIndices, std::uint16_t count) = 0;` — @brief Store a list of neural network indices onto a specified index. @param index A position in a zero-indexed array where neural network indices are stored. @note The index denotes the position of an entire neural network index list, not the position of its individual elements, i.e. the row index in a 2D matrix of neural network indices. @note The neural network index storage will be implicitly resized (if needed) to provide storage for the number of neural network indices that is inferred from the specified index. @param netIndices The source address from which the neural network indices are to be copied. @note These indices can be used to access neural networks through the below defined APIs. @param count The number of neural network indices to copy.
- L71 _public prototype_ `virtual void clearLODNeuralNetworkMappings() = 0;` — @brief Delete all stored LOD to neural network list index mapping entries.
- L80 _public prototype_ `virtual void setLODNeuralNetworkMapping(std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which neural networks belong to which level of detail. @param lod The actual level of detail to which the neural networks are being associated. @param index The index onto which neural network indices were assigned using setNeuralNetworkIndices. @see setNeuralNetworkIndices
- L84 _public prototype_ `virtual void clearMeshRegionNames() = 0;` — @brief Clear region information for all meshes.
- L92 _public prototype_ `virtual void clearMeshRegionNames(std::uint16_t meshIndex) = 0;` — @brief Delete all region names for the specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by DefinitionReader::getMeshCount.
- L107 _public prototype_ `virtual void setMeshRegionName(std::uint16_t meshIndex, std::uint16_t regionIndex, const char* name) = 0;` — @brief Name of the specified region. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param regionIndex A name's position in the zero-indexed array of region names. @note The region name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L111 _public prototype_ `virtual void clearNeuralNetworkIndicesPerMeshRegion() = 0;` — @brief Delete all stored neural network indices and accompanying data for each mesh and region.
- L128 _public prototype_ `virtual void setNeuralNetworkIndicesForMeshRegion(std::uint16_t meshIndex, std::uint16_t regionIndex, const std::uint16_t* netIndices, std::uint16_t count) = 0;` — @brief Store a list of neural network indices for the referenced region of a mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param regionIndex A region's position in the zero-indexed array of regions. @note The storage will be implicitly resized (if needed) to provide storage for the new data to be stored. @param netIndices The source address from which the neural network indices are to be copied. @note These indices can be used to access neural networks through the below defined APIs. @param count The number of neural network indices to copy.
- L140 _public prototype_ `virtual void deleteNeuralNetwork(std::uint16_t netIndex) = 0;` — @brief Delete the specified neural network. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by MachineLearnedBehaviorReader::getNeuralNetworkCount. @see MachineLearnedBehaviorReader::getNeuralNetworkCount
- L153 _public prototype_ `virtual void setNeuralNetworkInputIndices(std::uint16_t netIndex, const std::uint16_t* inputIndices, std::uint16_t count) = 0;` — @brief List of input control indices that drive the referenced neural network. @param netIndex A neural network's position in the zero-indexed array of neural networks. @param inputIndices The source address from which the control indices are to be copied. @param count The number of control indices to copy. @note The neural network storage will be implicitly resized (if needed) to provide storage for the new data.
- L166 _public prototype_ `virtual void setNeuralNetworkOutputIndices(std::uint16_t netIndex, const std::uint16_t* outputIndices, std::uint16_t count) = 0;` — @brief List of control indices whose weights are computed by the neural network. @param netIndex A neural network's position in the zero-indexed array of neural networks. @param outputIndices The source address from which the control indices are to be copied. @param count The number of control indices to copy. @note The neural network storage will be implicitly resized (if needed) to provide storage for the new data.
- L177 _public prototype_ `virtual void clearNeuralNetworkLayers(std::uint16_t netIndex) = 0;` — @brief Delete all layers of the referenced neural network. @param netIndex A neural network's position in the zero-indexed array of neural networks. @warning netIndex must be less than the value returned by MachineLearnedBehaviorReader::getNeuralNetworkCount. @see MachineLearnedBehaviorReader::getNeuralNetworkCount
- L190 _public prototype_ `virtual void setNeuralNetworkLayerActivationFunction(std::uint16_t netIndex, std::uint16_t layerIndex, ActivationFunction function) = 0;` — @brief Set the activation function type for the specified neural network layer. @param netIndex A neural network's position in the zero-indexed array of neural networks. @param layerIndex A layer's position in the zero-indexed array of neural network layers. @param function The activation function type. @note The neural network storage will be implicitly resized (if needed) to provide storage for the new data.
- L207 _public prototype_ `virtual void setNeuralNetworkLayerActivationFunctionParameters(std::uint16_t netIndex, std::uint16_t layerIndex, const float* activationFunctionParameters, std::uint16_t count) = 0;` — @brief Set the additional activation function parameters for the specified neural network layer. @param netIndex A neural network's position in the zero-indexed array of neural networks. @param layerIndex A layer's position in the zero-indexed array of neural network layers. @param activationFunctionParameters The source address from which the activation function parameters are to be copied. @param count The number of activation function parameters to copy. @note The neural network storage will be implicitly resized (if needed) to provide storage for the new data.
- L225 _public prototype_ `virtual void setNeuralNetworkLayerBiases(std::uint16_t netIndex, std::uint16_t layerIndex, const float* biases, std::uint32_t count) = 0;` — @brief Set the bias values for each unit of the specified neural network layer. @param netIndex A neural network's position in the zero-indexed array of neural networks. @param layerIndex A layer's position in the zero-indexed array of neural network layers. @param biases The source address from which the bias values are to be copied. @param count The number of bias values to copy. @note The neural network storage will be implicitly resized (if needed) to provide storage for the new data.
- L243 _public prototype_ `virtual void setNeuralNetworkLayerWeights(std::uint16_t netIndex, std::uint16_t layerIndex, const float* weights, std::uint32_t count) = 0;` — @brief Set the weight matrix for the specified neural network layer. @param netIndex A neural network's position in the zero-indexed array of neural networks. @param layerIndex A layer's position in the zero-indexed array of neural network layers. @param weights The source address from which the weight matrix values are to be copied. @param count The number of weight matrix values to copy. @note The neural network storage will be implicitly resized (if needed) to provide storage for the new data.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/RBFBehavior.h` (Public)


#### enum `dna::RBFSolverType`  
`enum class RBFSolverType`  
_L9-23_
- L14 _public enumerator_ `Additive` — The additive solver sums up contributions from each target. It's faster but may require more targets for a good coverage, and requires the normalization step to be performed for smooth results.
- L22 _public enumerator_ `Interpolative` — The interpolative solver interpolates the values from each target based on distance. As long as the input values are within the area bounded by the targets, the interpolation is well-behaved and returns weight values within the 0% - 100% limit with no normalization required. Interpolation also gives smoother results, with fewer targets than additive solver, but at a higher computational cost.

#### enum `dna::RBFFunctionType`  
`enum class RBFFunctionType`  
_L25-31_
- L26 _public enumerator_ `Gaussian`
- L27 _public enumerator_ `Exponential`
- L28 _public enumerator_ `Linear`
- L29 _public enumerator_ `Cubic`
- L30 _public enumerator_ `Quintic`

#### enum `dna::RBFDistanceMethod`  
`enum class RBFDistanceMethod`  
_L33-42_
- L35 _public enumerator_ `Euclidean` — Standard n-dimensional distance measure
- L37 _public enumerator_ `Quaternion` — Treat inputs as quaternion
- L39 _public enumerator_ `SwingAngle` — Treat inputs as quaternion, and find distance between rotated TwistAxis direction
- L41 _public enumerator_ `TwistAngle` — Treat inputs as half quaternion, and find distance between rotations around the TwistAxis direction

#### enum `dna::RBFNormalizeMethod`  
`enum class RBFNormalizeMethod`  
_L44-47_
- L45 _public enumerator_ `OnlyNormalizeAboveOne`
- L46 _public enumerator_ `AlwaysNormalize`

#### enum `dna::AutomaticRadius`  
`enum class AutomaticRadius`  
_L49-52_
- L50 _public enumerator_ `On`
- L51 _public enumerator_ `Off`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/RBFBehaviorReader.h` (Public)


#### class `dna::RBFBehaviorReader`  
`class DNAAPI RBFBehaviorReader : public virtual BehaviorReader`  
_L21-280_
- inherits: `BehaviorReader`
- desc: @brief Read-only accessors to the RBF data associated with a rig. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L23 _protected prototype_ `virtual ~RBFBehaviorReader();`
- L26 _public prototype_ `virtual std::uint16_t getRBFPoseCount() const = 0;`
- L35 _public prototype_ `virtual StringView getRBFPoseName(std::uint16_t poseIndex) const = 0;` — @brief Name of the requested RBF pose. @param poseIndex A name's position in the zero-indexed array of RBF pose names. @warning The index must be less than the value returned by getRBFPoseCount. @return View over the control name string.
- L45 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFPoseJointOutputIndices(std::uint16_t poseIndex) const = 0;` — @brief List of joint output indices of specified pose. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @return View over the array of row indices of raw joint matrix. @see BehaviorReader
- L54 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFPoseBlendShapeChannelOutputIndices(std::uint16_t poseIndex) const = 0;` — @brief List of blend shape channel indices of specifed pose. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @return View over the array of blend shape channel indices.
- L63 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFPoseAnimatedMapOutputIndices(std::uint16_t poseIndex) const = 0;` — @brief List of animated map indices of specifed pose. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @return View over the array of animated map indices.
- L71 _public prototype_ `virtual ConstArrayView<float> getRBFPoseJointOutputValues(std::uint16_t poseIndex) const = 0;` — @brief Values of requested solver pose outputs. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount
- L79 _public prototype_ `virtual float getRBFPoseScale(std::uint16_t poseIndex) const = 0;` — @brief Scale factor of requested solver's pose. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount
- L86 _public prototype_ `virtual std::uint16_t getRBFPoseControlCount() const = 0;` — @brief Number of distinct RBF controls. @note This is the number of unique output control indices for all RBF poses. @see getRBFPoseOutputControlIndices
- L95 _public prototype_ `virtual StringView getRBFPoseControlName(std::uint16_t poseControlIndex) const = 0;` — @brief Name of the requested RBF pose control. @param poseControlIndex A name's position in the zero-indexed array of RBF pose control names. @warning The index must be less than the value returned by getRBFPoseControlCount. @return View over the control name string.
- L108 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFPoseInputControlIndices(std::uint16_t poseIndex) const = 0;` — @brief List of control indices that additionally multiply the pose output (optional). @note When the final output weight of a pose is calculated (this is after it's already multiplied by the weights from @getRBFPoseOutputControlWeights), it can optionally be additionally multiplied by a list of input controls. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @return View over the array of control indices.
- L123 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFPoseOutputControlIndices(std::uint16_t poseIndex) const = 0;` — @brief List of control indices that the specified pose drives. @note This is an additional level of indirection, through which a single RBF pose is able to drive even multiple expressions (by providing multiple control indices for a pose). The solver calculates the output weight for a pose, and that output weight is distributed (and multiplied by the multiplier, @see getRBFPoseOutputControlWeights) to all the controls that are specified in this array. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @return View over the array of control indices.
- L135 _public prototype_ `virtual ConstArrayView<float> getRBFPoseOutputControlWeights(std::uint16_t poseIndex) const = 0;` — @brief List of weights that multiply the RBF outputs. @note When an RBF solver calculates the weights for each of its poses, those output weights are additionally multiplied by this fixed list of multipliers (one weight per control is given). @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @return View over the array of output control multipliers.
- L139 _public prototype_ `virtual std::uint16_t getRBFSolverCount() const = 0;` — @brief Number of RBF solvers.
- L145 _public prototype_ `virtual std::uint16_t getRBFSolverIndexListCount() const = 0;` — @brief Number of RBF solver index lists. @note This value is useful only in the context of RBFBehaviorWriter.
- L155 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of RBF solver indices for the specified LOD. @param lod The level of detail for which RBF solvers are being requested. @warning The lod index must be less than the value returned by getLODCount. @return View over the solver indices. @see DescriptorReader::getLODCount
- L164 _public prototype_ `virtual StringView getRBFSolverName(std::uint16_t solverIndex) const = 0;` — @brief Name of the requested RBF solver. @param solverIndex A name's position in the zero-indexed array of RBF solver names. @warning The index must be less than the value returned by getRBFSolverCount. @return View over the solver name string.
- L191 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFSolverRawControlIndices(std::uint16_t solverIndex) const = 0;` — @brief List of raw body control indices that drive the referenced RBF solver. Depending on the distance method @see setRBFSolverDistanceMethod different number of inputs are expected. Quaternion, SwingAngle and TwistAngle: Inputs treated as quaternion, 4 raw controls per input. One for each attribute of quaternion (x, y, z, w) e.g. two driving joints will require 8 raw controls. Raw control indices: 11, 12, 13, 14, 18, 19, 20, 21 Corresponds to: 0x, 0y, 0z, 0w, 1x, 1y, 1z, 1w Euclidean: Inputs treated as scalar, 1 raw control per input. Since inputs do not represent joints, they are just treated as arbitrary scalar values. Raw control indices: 33, 34, 41, 42, 56 Corresponds to: i0, i1, i2, i3, i4 @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount. @return View over the array of raw control indices
- L200 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFSolverPoseIndices(std::uint16_t solverIndex) const = 0;` — @brief Pose indices of specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount. @return View over the array of pose indices.
- L209 _public prototype_ `virtual ConstArrayView<float> getRBFSolverRawControlValues(std::uint16_t solverIndex) const = 0;` — @brief Raw control values for all poses of requested solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount. @return View over the array of the driver values for all poses.
- L220 _public prototype_ `virtual RBFSolverType getRBFSolverType(std::uint16_t solverIndex) const = 0;` — @brief Type of RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount. @note The Interpolative solver boasts smoother blending, whereas the additive solver, although needing more targets, provides more precise control over each target's influence.
- L228 _public prototype_ `virtual float getRBFSolverRadius(std::uint16_t solverIndex) const = 0;` — @brief Radius of RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount.
- L236 _public prototype_ `virtual AutomaticRadius getRBFSolverAutomaticRadius(std::uint16_t solverIndex) const = 0;` — @brief State of automatic radius switch for specifed RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount.
- L244 _public prototype_ `virtual float getRBFSolverWeightThreshold(std::uint16_t solverIndex) const = 0;` — @brief Weight threshold of RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount.
- L252 _public prototype_ `virtual RBFDistanceMethod getRBFSolverDistanceMethod(std::uint16_t solverIndex) const = 0;` — @brief Distance method of RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount.
- L263 _public prototype_ `virtual RBFNormalizeMethod getRBFSolverNormalizeMethod(std::uint16_t solverIndex) const = 0;` — @brief Normalization method of RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount. @note The additive solver requires normalization, whereas the Interpolative solver is not as reliant on it.
- L271 _public prototype_ `virtual RBFFunctionType getRBFSolverFunctionType(std::uint16_t solverIndex) const = 0;` — @brief Function type of RBF solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount.
- L279 _public prototype_ `virtual TwistAxis getRBFSolverTwistAxis(std::uint16_t solverIndex) const = 0;` — @brief Twist axis of specified RBF solver when DistanceMethod is SwingAngle. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @warning solverIndex must be less than the value returned by getRBFSolverCount.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/RBFBehaviorWriter.h` (Public)


#### class `dna::RBFBehaviorWriter`  
`class DNAAPI RBFBehaviorWriter : public virtual BehaviorWriter`  
_L21-323_
- inherits: `BehaviorWriter`
- desc: @brief Write-only accessors for the RBF data associated with a rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L23 _protected prototype_ `virtual ~RBFBehaviorWriter();`
- L29 _public prototype_ `virtual void clearRBFPoses() = 0;` — @brief Delete all RBF poses.
- L42 _public prototype_ `virtual void setRBFPoseName(std::uint16_t poseIndex, const char* name) = 0;` — @brief Set name of pose. @param poseIndex A RBF pose's position in the zero-indexed array of poses. @note The pose storage will be implicitly resized (if needed) to provide storage for the number of poses that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L53 _public prototype_ `virtual void setRBFPoseScale(std::uint16_t poseIndex, float scale) = 0;` — @brief Set scale factor for the specified pose of solver. @param poseIndex A RBF pose's position in the zero-indexed array of poses. @note The pose storage will be implicitly resized (if needed) to provide storage for the number of poses that is inferred from the specified index. @param scale The solver's pose scale.
- L57 _public prototype_ `virtual void clearRBFPoseControlNames() = 0;` — @brief Delete all RBF pose control names.
- L70 _public prototype_ `virtual void setRBFPoseControlName(std::uint16_t poseControlIndex, const char* name) = 0;` — @brief Name of the specified RBF pose control. @param index A name's position in the zero-indexed array of RBF pose control names. @note The control name storage will be implicitly resized (if needed) to provide storage for the number of names that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L86 _public prototype_ `virtual void setRBFPoseInputControlIndices(std::uint16_t poseIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) = 0;` — @brief Set the list of control indices that additionally multiply the pose output (optional). @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @param controlIndices The source address from which the control indices are to be copied. @note When the final output weight of a pose is calculated (this is after it's already multiplied by the weights from @getRBFPoseOutputControlWeights), it can optionally be additionally multiplied by a list of input controls. @param controlCount The number of control indices to copy.
- L107 _public prototype_ `virtual void setRBFPoseOutputControlIndices(std::uint16_t poseIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) = 0;` — @brief Set the list of control indices that the specified pose drives. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @param controlIndices The source address from which the control indices are to be copied. @note These control indices This is an additional level of indirection, through which a single RBF pose is able to drive even multiple expressions (by providing multiple control indices for a pose). The solver calculates the output weight for a pose, and that output weight is distributed (and multiplied by the multiplier, @see setRBFPoseOutputControlWeights) to all the controls that are specified in this array. @param controlCount The number of control indices to copy.
- L124 _public prototype_ `virtual void setRBFPoseOutputControlWeights(std::uint16_t poseIndex, const float* controlWeights, std::uint16_t controlWeightCount) = 0;` — @brief Set the list of weights that multiply the RBF outputs. @param poseIndex A poses's position in the zero-indexed array of poses. @warning poseIndex must be less than the value returned by getRBFPoseCount @param controlWeights The source address from which the control weights are to be copied. @note When an RBF solver calculates the weights for each of its poses, those output weights are additionally multiplied by this fixed list of multipliers (one weight per control is given). @param controlWeightCount The number of control weights to copy.
- L130 _public prototype_ `virtual void clearRBFSolvers() = 0;` — @brief Delete all RBF solvers.
- L134 _public prototype_ `virtual void clearRBFSolverIndices() = 0;` — @brief Delete all stored RBF solver indices.
- L153 _public prototype_ `virtual void setRBFSolverIndices(std::uint16_t index, const std::uint16_t* solverIndices, std::uint16_t count) = 0;` — @brief Store a list of RBF solver indices onto a specified index. @param index A position in a zero-indexed array where solver indices are stored. @note The index denotes the position of an entire solver index list, not the position of its individual elements, i.e. the row index in a 2D matrix of solver indices. @note The solver index storage will be implicitly resized (if needed) to provide storage for the number of solver indices that is inferred from the specified index. @param solverIndices The source address from which the solver indices are to be copied. @note These indices can be used to access RBF solver through the below defined APIs. @param count The number of solver indices to copy.
- L157 _public prototype_ `virtual void clearLODRBFSolverMappings() = 0;` — @brief Delete all stored LOD to RBF solver list index mapping entries.
- L166 _public prototype_ `virtual void setLODRBFSolverMapping(std::uint16_t lod, std::uint16_t index) = 0;` — @brief Set which solver belongs to which level of detail. @param lod The actual level of detail to which the solvers are being associated. @param index The index onto which solver indices were assigned using setRBFSolverIndices. @see setRBFSolverIndices
- L179 _public prototype_ `virtual void setRBFSolverName(std::uint16_t solverIndex, const char* name) = 0;` — @brief Name of the specified RBF solver. @param solverIndex A name's position in the zero-indexed array of RBF solvers. @note The RBF solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param name A null-terminated string. @note The passed in name is copied, which will involve an additional allocation.
- L210 _public prototype_ `virtual void setRBFSolverRawControlIndices(std::uint16_t solverIndex, const std::uint16_t* rawControlIndices, std::uint16_t count) = 0;` — @brief Store a list of raw control indices of the specified RBF solver. Depending on the distance method @see setRBFSolverDistanceMethod different number of inputs are expected. Quaternion, SwingAngle and TwistAngle: Inputs treated as quaternion, 4 raw controls per input. One for each attribute of quaternion (x, y, z, w) e.g. two driving joints will require 8 raw controls. Raw control indices: 11, 12, 13, 14, 18, 19, 20, 21 Corresponds to: 0x, 0y, 0z, 0w, 1x, 1y, 1z, 1w Euclidean: Inputs treated as scalar. 1 raw control per input. Since inputs do not represent joints, they are just treated as arbitrary scalar values. Raw control indices: 33, 34, 41, 42, 56 Corresponds to: i0, i1, i2, i3, i4 @param solverIndex A position in a zero-indexed array where solvers are stored. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param rawControlIndices The source address from which the raw control indices are to be copied. @param count The number of raw control indices to copy.
- L221 _public prototype_ `virtual void setRBFSolverPoseIndices(std::uint16_t solverIndex, const std::uint16_t* poseIndices, std::uint16_t count) = 0;` — @brief Store a list of pose indices of specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index.
- L234 _public prototype_ `virtual void setRBFSolverRawControlValues(std::uint16_t solverIndex, const float* values, std::uint16_t count) = 0;` — @brief Set raw control values for all poses of requested solver, value for each raw control per pose. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param values The source address from which the values are to be copied. @param count The number of values to copy.
- L245 _public prototype_ `virtual void setRBFSolverType(std::uint16_t solverIndex, RBFSolverType type) = 0;` — @brief Set solver type for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param type The solver type.
- L256 _public prototype_ `virtual void setRBFSolverRadius(std::uint16_t solverIndex, float radius) = 0;` — @brief Set radius for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param radius The solver's radius.
- L267 _public prototype_ `virtual void setRBFSolverAutomaticRadius(std::uint16_t solverIndex, AutomaticRadius automaticRadius) = 0;` — @brief Set automatic radius for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param automaticRadius The solver's automatic radius.
- L278 _public prototype_ `virtual void setRBFSolverWeightThreshold(std::uint16_t solverIndex, float weightThreshold) = 0;` — @brief Set weight threshold for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param weightThreshold The solver's weight threshold.
- L289 _public prototype_ `virtual void setRBFSolverDistanceMethod(std::uint16_t solverIndex, RBFDistanceMethod distanceMethod) = 0;` — @brief Set distance method for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param distanceMethod The solver's distance method.
- L300 _public prototype_ `virtual void setRBFSolverNormalizeMethod(std::uint16_t solverIndex, RBFNormalizeMethod normalizeMethod) = 0;` — @brief Set normalization method for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param normalizeMethod The solver's normalization method.
- L311 _public prototype_ `virtual void setRBFSolverFunctionType(std::uint16_t solverIndex, RBFFunctionType functionType) = 0;` — @brief Set function type for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param functionType The solver's function type.
- L322 _public prototype_ `virtual void setRBFSolverTwistAxis(std::uint16_t solverIndex, TwistAxis twistAxis) = 0;` — @brief Set twist axis for the specified solver. @param solverIndex A RBF solver's position in the zero-indexed array of RBF solvers. @note The solver storage will be implicitly resized (if needed) to provide storage for the number of solvers that is inferred from the specified index. @param TwistAxis The solver's twist axis.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/Twist.h` (Public)


#### enum `dna::TwistAxis`  
`enum class TwistAxis`  
_L7-11_
- L8 _public enumerator_ `X`
- L9 _public enumerator_ `Y`
- L10 _public enumerator_ `Z`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/TwistSwingBehaviorReader.h` (Public)


#### class `dna::TwistSwingBehaviorReader`  
`class DNAAPI TwistSwingBehaviorReader : public virtual DefinitionReader`  
_L20-111_
- inherits: `DefinitionReader`
- desc: @brief Read-only accessors to the Swing and Twist data associated with a rig. @warning Implementors should inherit from Reader itself and not this class. @see Reader
- L22 _protected prototype_ `virtual ~TwistSwingBehaviorReader();`
- L28 _public prototype_ `virtual std::uint16_t getTwistCount() const = 0;` — @brief The number of twist parameter groups.
- L36 _public prototype_ `virtual TwistAxis getTwistSetupTwistAxis(std::uint16_t twistIndex) const = 0;` — @brief Twist axis of the specified twist parameter group. @param twistIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getTwistCount.
- L47 _public prototype_ `virtual ConstArrayView<std::uint16_t> getTwistInputControlIndices(std::uint16_t twistIndex) const = 0;` — @brief Get the raw control indices representing the joint rotation that drives the twist transformation. @note The number of these raw control indices is always 4, representing a single quaternion [x, y, z, w] attributes. @param twistIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getTwistCount. @return View over the raw control indices representing the twist driver joint rotation.
- L56 _public prototype_ `virtual ConstArrayView<std::uint16_t> getTwistOutputJointIndices(std::uint16_t twistIndex) const = 0;` — @brief Get the joint indices whose rotations are driven by the twist transformation. @param twistIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getTwistCount. @return View over the twist driven joint indices.
- L67 _public prototype_ `virtual ConstArrayView<float> getTwistBlendWeights(std::uint16_t twistIndex) const = 0;` — @brief Get the weights that define which portions of the driver joint rotation will be applied to the driven joints. @note There is one weight per output joint in this list. @param twistIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getTwistCount. @return View over the twist blend weights.
- L71 _public prototype_ `virtual std::uint16_t getSwingCount() const = 0;` — @brief The number of swing parameter groups.
- L79 _public prototype_ `virtual TwistAxis getSwingSetupTwistAxis(std::uint16_t swingIndex) const = 0;` — @brief Twist axis of the specified swing parameter group. @param swingIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getSwingCount.
- L90 _public prototype_ `virtual ConstArrayView<std::uint16_t> getSwingInputControlIndices(std::uint16_t swingIndex) const = 0;` — @brief Get the raw control indices representing the joint rotation that drives the swing transformation. @note The number of these raw control indices is always 4, representing a single quaternion [x, y, z, w] attributes. @param swingIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getSwingCount. @return View over the raw control indices representing the swing driver joint rotation.
- L99 _public prototype_ `virtual ConstArrayView<std::uint16_t> getSwingOutputJointIndices(std::uint16_t swingIndex) const = 0;` — @brief Get the joint indices whose rotations are driven by the swing transformation. @param swingIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getSwingCount. @return View over the swing driven joint indices.
- L110 _public prototype_ `virtual ConstArrayView<float> getSwingBlendWeights(std::uint16_t swingIndex) const = 0;` — @brief Get the weights that define which portions of the driver joint rotation will be applied to the driven joints. @note There is one weight per output joint in this list. @param swingIndex The index of the parameter group whose data is being accessed. @warning The index must be less than the value returned by getSwingCount. @return View over the swing blend weights.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/layers/TwistSwingBehaviorWriter.h` (Public)


#### class `dna::TwistSwingBehaviorWriter`  
`class DNAAPI TwistSwingBehaviorWriter : public virtual DefinitionWriter`  
_L20-161_
- inherits: `DefinitionWriter`
- desc: @brief Write-only accessors to the Swing and Twist data associated with a rig. @warning Implementors should inherit from Writer itself and not this class. @see Writer
- L22 _protected prototype_ `virtual ~TwistSwingBehaviorWriter();`
- L28 _public prototype_ `virtual void clearTwists() = 0;` — @brief Delete all twist parameter groups.
- L34 _public prototype_ `virtual void deleteTwist(std::uint16_t twistIndex) = 0;` — @brief Delete the specified twist parameter group. @param twistIndex The index of the parameter group to be deleted.
- L45 _public prototype_ `virtual void setTwistSetupTwistAxis(std::uint16_t twistIndex, TwistAxis twistAxis) = 0;` — @brief Set twist axis for the specified twist parameter group. @param twistIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param TwistAxis The twist axis of the parameter group.
- L60 _public prototype_ `virtual void setTwistInputControlIndices(std::uint16_t twistIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) = 0;` — @brief Set the raw control indices representing the joint rotation that drives the twist transformation. @param twistIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param controlIndices Pointer to raw control indices representing the joint rotation that drives the twist transformation. @note The number of these raw control indices is always 4, representing a single quaternion [x, y, z, w] attributes. @param controlIndexCount The number of raw control indices to copy.
- L75 _public prototype_ `virtual void setTwistOutputJointIndices(std::uint16_t twistIndex, const std::uint16_t* jointIndices, std::uint16_t jointIndexCount) = 0;` — @brief Set the joint indices whose rotations are driven by the twist transformation. @param twistIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param jointIndices Pointer to joint indices of the twist driven joints. @param jointIndexCount The number of joint indices to copy.
- L92 _public prototype_ `virtual void setTwistBlendWeights(std::uint16_t twistIndex, const float* blendWeights, std::uint16_t blendWeightCount) = 0;` — @brief Set the weights that define which portions of the driver joint rotation will be applied to the driven joints. @param twistIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param blendWeights The source address from which the twist blend weights are to be copied. @note There is one weight per output joint in this list. @param blendWeightCount The number of blend weights to copy.
- L96 _public prototype_ `virtual void clearSwings() = 0;` — @brief Delete all swing parameter groups.
- L102 _public prototype_ `virtual void deleteSwing(std::uint16_t swingIndex) = 0;` — @brief Delete the specified swing parameter group. @param swingIndex The index of the parameter group to be deleted.
- L113 _public prototype_ `virtual void setSwingSetupTwistAxis(std::uint16_t swingIndex, TwistAxis twistAxis) = 0;` — @brief Set twist axis for the specified swing parameter group. @param swingIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param TwistAxis The twist axis of the parameter group.
- L128 _public prototype_ `virtual void setSwingInputControlIndices(std::uint16_t swingIndex, const std::uint16_t* controlIndices, std::uint16_t controlIndexCount) = 0;` — @brief Set the raw control indices representing the joint rotation that drives the swing transformation. @param swingIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param controlIndices View over the raw control indices representing the swing driver joint rotation. @note The number of these raw control indices is always 4, representing a single quaternion [x, y, z, w] attributes. @param controlIndexCount The number of raw control indices to copy.
- L143 _public prototype_ `virtual void setSwingOutputJointIndices(std::uint16_t swingIndex, const std::uint16_t* jointIndices, std::uint16_t jointIndexCount) = 0;` — @brief Set the joint indices whose rotations are driven by the swing transformation. @param swingIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param jointIndices Pointer to joint indices of the swing driven joints. @param jointIndexCount The number of joint indices to copy.
- L160 _public prototype_ `virtual void setSwingBlendWeights(std::uint16_t swingIndex, const float* blendWeights, std::uint16_t blendWeightCount) = 0;` — @brief Set the weights that define which portions of the driver joint rotation will be applied to the driven joints. @param swingIndex The index of the parameter group whose data is being accessed. @note The parameter group storage will be implicitly resized (if needed) to provide storage for the number of groups that is inferred from the specified index. @param blendWeights The source address from which the swing blend weights are to be copied. @note There is one weight per output joint in this list. @param blendWeightCount The number of blend weights to copy.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/types/Aliases.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/types/Vector3.h` (Public)


#### struct `dna::Vector3`  
`struct Vector3`  
_L7-67_
- L8 _public member_ `float x;`
- L9 _public member_ `float y;`
- L10 _public member_ `float z;`
- L12 _public function_ `Vector3& operator+=(const Vector3& rhs)`
- L19 _public function_ `Vector3& operator-=(const Vector3& rhs)`
- L26 _public function_ `Vector3& operator*=(const Vector3& rhs)`
- L33 _public function_ `Vector3& operator/=(const Vector3& rhs)`
- L40 _public function_ `Vector3& operator+=(float rhs)`
- L47 _public function_ `Vector3& operator-=(float rhs)`
- L54 _public function_ `Vector3& operator*=(float rhs)`
- L61 _public function_ `Vector3& operator/=(float rhs)`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace dna`
- L69 _function_ `inline Vector3 operator+(Vector3 lhs, const Vector3& rhs)` (scope `dna`)
- L73 _function_ `inline Vector3 operator-(Vector3 lhs, const Vector3& rhs)` (scope `dna`)
- L77 _function_ `inline Vector3 operator*(Vector3 lhs, const Vector3& rhs)` (scope `dna`)
- L81 _function_ `inline Vector3 operator/(Vector3 lhs, const Vector3& rhs)` (scope `dna`)
- L85 _function_ `inline Vector3 operator+(Vector3 lhs, float rhs)` (scope `dna`)
- L89 _function_ `inline Vector3 operator-(Vector3 lhs, float rhs)` (scope `dna`)
- L93 _function_ `inline Vector3 operator*(Vector3 lhs, float rhs)` (scope `dna`)
- L97 _function_ `inline Vector3 operator/(Vector3 lhs, float rhs)` (scope `dna`)
- L101 _function_ `inline bool operator==(const Vector3& lhs, const Vector3& rhs)` (scope `dna`)
- L105 _function_ `inline bool operator!=(const Vector3& lhs, const Vector3& rhs)` (scope `dna`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define DNA_MAJOR_VERSION 10`
- L6 _macro_ `#define DNA_MINOR_VERSION 1`
- L7 _macro_ `#define DNA_PATCH_VERSION 6`
- L8 _macro_ `#define DNA_VERSION_STRING "10.1.6"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/dna/version/VersionInfo.h` (Public)


#### struct `dna::VersionInfo`  
`struct DNAAPI VersionInfo`  
_L10-15_
- L11 _public prototype_ `static int getMajorVersion();`
- L12 _public prototype_ `static int getMinorVersion();`
- L13 _public prototype_ `static int getPatchVersion();`
- L14 _public prototype_ `static StringView getVersionString();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dna`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define PMAAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define PMAAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define PMAAPI` — Build or use static library

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/MemoryResource.h` (Public)


#### class `pma::MemoryResource`  
`class PMAAPI MemoryResource`  
_L17-22_
- desc: @brief MemoryResource is an abstract class that allows the implementation of polymorphic allocators. @note It's purpose is to allow passing arbitrary allocators through API boundaries, without requiring changes in the signatures and types involved.
- L19 _public prototype_ `virtual ~MemoryResource();`
- L20 _public prototype_ `virtual void* allocate(std::size_t size, std::size_t alignment) = 0;`
- L21 _public prototype_ `virtual void deallocate(void* ptr, std::size_t size, std::size_t alignment) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/PolyAllocator.h` (Public)


#### struct `pma::impl::max_align_of`  
`template<typename T, typename U> struct max_align_of`  
_L30-32_
- L31 _public typedef_ `using type = typename std::conditional<(alignof(T) > alignof(U)), T, U>::type;`

#### class `pma::impl::PolyAllocator`  
`template<typename T, std::size_t Alignment, class TDefaultMemoryResource> class PolyAllocator`  
_L35-127_
- L37 _public typedef_ `using value_type = T;`
- L38 _public typedef_ `using traits_type = std::allocator_traits<PolyAllocator>;`
- L44 _public function_ `PolyAllocator()`
- L56 _public function_ `PolyAllocator(MemoryResource* memRes) : PolyAllocator`
- L63 _public function_ `PolyAllocator(std::nullptr_t ) : PolyAllocator`
- L68 _public function_ `template<class U, std::size_t UAlignment, class UDefaultMemoryResource> PolyAllocator(const PolyAllocator<U, UAlignment, UDefaultMemoryResource>& rhs) : pMemRes`
- L72 _public function_ `void* allocateBytes(std::size_t size, std::size_t alignment = Alignment)`
- L76 _public function_ `void deallocateBytes(void* ptr, std::size_t size, std::size_t alignment = Alignment)`
- L81 _public function_ `template<typename U = value_type> typename std::enable_if<!std::is_void<U>::value, U*>::type allocateObject(std::size_t count, std::size_t alignment = Alignment)`
- L87 _public function_ `template<typename U = value_type> typename std::enable_if<!std::is_void<U>::value>::type deallocateObject(U* ptr, std::size_t count, std::size_t alignment = Alignment)`
- L94 _public function_ `template<typename U = value_type, typename... Args> U* newObject(Args&&... args)`
- L102 _public function_ `template<typename U = value_type> void deleteObject(U* ptr)`
- L108 _public function_ `value_type* allocate(std::size_t count)` — Allocation function as requested by standard-library containers
- L113 _public function_ `void deallocate(value_type* ptr, std::size_t count)` — Deallocation function as requested by standard-library containers
- L117 _public function_ `static std::size_t getAlignment()`
- L121 _public function_ `MemoryResource* getMemoryResource() const`
- L126 _private member_ `MemoryResource* pMemRes;`

#### class `pma::PolyAllocator`  
`class PolyAllocator : public std::scoped_allocator_adaptor<impl::PolyAllocator<T, Alignment, TDefaultMemoryResource>>`  
_L134-160_
- inherits: `std::scoped_allocator_adaptor<impl::PolyAllocator<T,Alignment,TDefaultMemoryResource>>`
- L136 _private typedef_ `using Impl = impl::PolyAllocator<T, Alignment, TDefaultMemoryResource>;`
- L137 _private typedef_ `using Base = std::scoped_allocator_adaptor<Impl>;`
- L145 _public prototype_ `PolyAllocator() = default;`
- L147 _public function_ `PolyAllocator(MemoryResource* memRes) : Base`
- L152 _public function_ `template<class U, std::size_t UAlignment, class UDefaultMemoryResource> PolyAllocator(const PolyAllocator<U, UAlignment, UDefaultMemoryResource>& rhs) : Base`
- L157 _public function_ `template<class U, std::size_t UAlignment, class UDefaultMemoryResource> PolyAllocator(const impl::PolyAllocator<U, UAlignment, UDefaultMemoryResource>& rhs) : Base`

#### struct `pma::PolyAllocator::rebind`  
`template<typename U> struct rebind`  
_L141-143_
- L142 _public typedef_ `using other = PolyAllocator<U, Alignment, TDefaultMemoryResource>;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace pma`
- L25 _namespace_ `namespace impl` (scope `pma`)
- L27 _typedef_ `using min_align_t = void*;` (scope `pma::impl`)
- L168 _function_ `bool operator==(const PolyAllocator<T, TAlignment, TDefaultMemoryResource>& lhs, const PolyAllocator<U, UAlignment, UDefaultMemoryResource>& rhs)` (scope `pma`)
- L179 _function_ `bool operator!=(const PolyAllocator<T, TAlignment, TDefaultMemoryResource>& lhs, const PolyAllocator<U, UAlignment, UDefaultMemoryResource>& rhs)` (scope `pma`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/ScopedPtr.h` (Public)


#### struct `pma::New`  
`template<class T, class B = T> struct New`  
_L17-22_
- L19 _public function_ `template<typename... Args> B* operator()(Args&&... args)`
- L44 _public function_ `T* operator()(std::size_t size)`

#### struct `pma::Delete`  
`template<class T, class B = T> struct Delete`  
_L25-40_
- L26 _public function_ `void operator()(B* ptr)`
- L51 _public function_ `void operator()(T* ptr)`

#### struct `pma::New`  
`template<class T> struct New<T[]>`  
_L43-47_
- L19 _public function_ `template<typename... Args> B* operator()(Args&&... args)`
- L44 _public function_ `T* operator()(std::size_t size)`

#### struct `pma::Delete`  
`template<class T> struct Delete<T[]>`  
_L50-65_
- L26 _public function_ `void operator()(B* ptr)`
- L51 _public function_ `void operator()(T* ptr)`

#### struct `pma::FactoryCreate`  
`template<class T, class B = T> struct FactoryCreate`  
_L68-73_
- L70 _public function_ `template<typename... Args> B* operator()(Args&&... args)`

#### struct `pma::FactoryDestroy`  
`template<class T, class B = T> struct FactoryDestroy`  
_L76-80_
- L77 _public function_ `void operator()(B* ptr)`

#### struct `pma::DefaultInstanceCreator`  
`template<class T> struct DefaultInstanceCreator`  
_L83-85_
- L84 _public typedef_ `using type = New<T>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<class T> struct DefaultInstanceDestroyer`  
_L88-90_
- L89 _public typedef_ `using type = Delete<T>;`

#### class `pma::ScopedPtr`  
`template<class T, class TDestroyer = typename DefaultInstanceDestroyer<T>::type> class ScopedPtr : private TDestroyer`  
_L110-234_
- inherits: `TDestroyer`
- desc: @brief Takes ownership over the given pointer and handles it's lifetime. @note As ScopedPtr inherits the specified destroyer type, stateless lifetime managers are zero-cost, but it's also possible to use stateful lifetime managers (such as lambdas with captures and what-not). For stateful lifetime managers, a dedicated constructor exists that receives the destroyer instance and initializes the inherited destroyer type with it. @see makeScoped @see New @see Delete @see FactoryCreate @see FactoryDestroy @see DefaultInstanceCreator @see DefaultInstanceDestroyer
- L127 _public typedef_ `using pointer = typename inspect<T>::pointer_type;`
- L128 _public typedef_ `using element_type = typename inspect<T>::element_type;`
- L129 _public typedef_ `using destroyer_type = TDestroyer;`
- L135 _public function_ `ScopedPtr() : ptr`
- L139 _public function_ `explicit ScopedPtr(pointer ptr_) : ptr`
- L143 _public function_ `ScopedPtr(pointer ptr_, destroyer_type&& destroyer) : destroyer_type`
- L148 _public function_ `~ScopedPtr()`
- L155 _public function_ `ScopedPtr(std::nullptr_t) : ptr`
- L159 _public function_ `ScopedPtr& operator=(std::nullptr_t)`
- L164 _public prototype_ `ScopedPtr(const ScopedPtr&) = delete;`
- L165 _public prototype_ `ScopedPtr& operator=(const ScopedPtr&) = delete;`
- L167 _public function_ `ScopedPtr(ScopedPtr&& rhs) noexcept : ptr`
- L172 _public function_ `ScopedPtr& operator=(ScopedPtr&& rhs) noexcept`
- L178 _public function_ `template<typename U, class UDestroyer> ScopedPtr(ScopedPtr<U, UDestroyer>&& rhs) noexcept : ptr`
- L185 _public function_ `template<typename U, class UDestroyer> ScopedPtr& operator=(ScopedPtr<U, UDestroyer>&& rhs) noexcept`
- L192 _public function_ `template<typename U = T, typename IA = typename inspect<U>::is_array> typename std::enable_if<IA::value, element_type&>::type operator[](std::size_t index) const noexcept`
- L197 _public function_ `template<typename U = T, typename IA = typename inspect<U>::is_array> typename std::enable_if<!IA::value, element_type&>::type operator*() const noexcept`
- L201 _public function_ `pointer operator->() const noexcept`
- L205 _public function_ `operator bool() const noexcept`
- L209 _public function_ `pointer get() const noexcept`
- L213 _public function_ `pointer release() noexcept`
- L219 _public function_ `void reset(pointer rhs = pointer()) noexcept`
- L227 _public function_ `void swap(ScopedPtr& rhs) noexcept`
- L233 _private member_ `pointer ptr;`

#### struct `pma::ScopedPtr::inspect`  
`template<typename U> struct inspect`  
_L113-117_
- L114 _public typedef_ `using element_type = U;`
- L115 _public typedef_ `using pointer_type = element_type*;`
- L116 _public typedef_ `using is_array = std::false_type;`
- L123 _public typedef_ `using is_array = std::true_type;`

#### struct `pma::ScopedPtr::inspect`  
`template<typename U> struct inspect<U[]>`  
_L120-124_
- L114 _public typedef_ `using element_type = U;`
- L115 _public typedef_ `using pointer_type = element_type*;`
- L116 _public typedef_ `using is_array = std::false_type;`
- L123 _public typedef_ `using is_array = std::true_type;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace pma`
- L33 _typedef_ `using complete_type_checker = char[sizeof(T) ? 1 : -1];` (scope `pma::Delete::operator ()`)
- L256 _function_ `ScopedPtr<Base, TDestroyer> makeScoped(Args&&... args)` (scope `pma`)
- L264 _function_ `template<class T, template<class...> class TCreatorTemplate, template<class...> class TDestroyerTemplate, typename... Args> ScopedPtr<T, TDestroyerTemplate<T>> makeScoped(Args&&... args)` (scope `pma`)
- L265 _typedef_ `using TCreator = TCreatorTemplate<T>;` (scope `pma::makeScoped`)
- L266 _typedef_ `using TDestroyer = TDestroyerTemplate<T>;` (scope `pma::makeScoped`)
- L271 _function_ `template<class T, typename... Args> ScopedPtr<T, typename DefaultInstanceDestroyer<T>::type> makeScoped(Args&&... args)` (scope `pma`)
- L272 _typedef_ `using TCreator = typename DefaultInstanceCreator<T>::type;` (scope `pma::makeScoped`)
- L273 _typedef_ `using TDestroyer = typename DefaultInstanceDestroyer<T>::type;` (scope `pma::makeScoped`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/TypeDefs.h` (Public)


#### Free symbols / members of external scopes

- L23 _namespace_ `namespace pma`
- L26 _typedef_ `template<typename T, typename Allocator = PolyAllocator<T>> using String = std::basic_string<T, std::char_traits<T>, Allocator>;` (scope `pma`)
- L29 _typedef_ `template<typename T, typename Allocator = PolyAllocator<T>> using Vector = std::vector<T, Allocator>;` (scope `pma`)
- L32 _typedef_ `template<typename T, typename Allocator = PolyAllocator<Vector<T>>> using Matrix = Vector<Vector<T>, Allocator>;` (scope `pma`)
- L35 _typedef_ `template<typename T, typename Allocator = PolyAllocator<T>> using List = std::list<T, Allocator>;` (scope `pma`)
- L38 _typedef_ `template<typename T, typename Allocator = PolyAllocator<T>> using Set = std::set<T, std::less<T>, Allocator>;` (scope `pma`)
- L41 _typedef_ `template<typename T, typename Allocator = PolyAllocator<T>> using UnorderedSet = std::unordered_set<T, std::hash<T>, std::equal_to<T>, Allocator>;` (scope `pma`)
- L44 _typedef_ `template<typename K, typename V, typename Allocator = PolyAllocator<std::pair<const K, V>>> using Map = std::map<K, V, std::less<K>, Allocator>;` (scope `pma`)
- L47 _typedef_ `template<typename K, typename V, typename Allocator = PolyAllocator<std::pair<const K, V>>> using UnorderedMap = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, Allocator>;` (scope `pma`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/resources/AlignedMemoryResource.h` (Public)


#### class `pma::AlignedMemoryResource`  
`class PMAAPI AlignedMemoryResource : public MemoryResource`  
_L16-20_
- inherits: `MemoryResource`
- desc: @brief A MemoryResource that honors alignment requirements. @see MemoryResource
- L18 _public prototype_ `void* allocate(std::size_t size, std::size_t alignment) override;`
- L19 _public prototype_ `void deallocate(void* ptr, std::size_t size, std::size_t alignment) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/resources/ArenaMemoryResource.h` (Public)


#### class `pma::ArenaMemoryResource`  
`class ArenaMemoryResource : public MemoryResource`  
_L17-92_
- inherits: `MemoryResource`
- desc: @brief Serves allocations from a preallocated memory region. @see MemoryResource
- L37 _public prototype_ `PMAAPI ArenaMemoryResource(std::size_t initialSize, std::size_t regionSize, float growthFactor, MemoryResource* upstream);` — @brief Constructor @param initialSize The size of the first allocated region from which allocation requests are served. @param regionSize When a memory region backing allocation requests has not enough free space to serve an allocation, an additional region is allocated for both the current and all subsequent allocations. This parameter denotes the size of these additionally allocated regions. @param growthFactor It describes by which factor should each subsequently allocated region be scaled, relative to the previous region. A list of possible region allocation would look like: regions = {initialSize, regionSize, regions[1] * growthFactor, regions[2] * growthFactor, ... , regions[n - 1] * growthFactor} @param upstream The backing memory region will be allocated using the given upstream MemoryResource.
- L54 _public prototype_ `PMAAPI ArenaMemoryResource(std::size_t regionSize, float growthFactor, MemoryResource* upstream);` — @brief Constructor @param regionSize When a memory region backing allocation requests has not enough free space to serve an allocation, an additional region is allocated for both the current and all subsequent allocations. This parameter denotes the size of the initial and all subsequently allocated regions. @param growthFactor It describes by which factor should each subsequently allocated region be scaled, relative to the previous region. A list of possible region allocation would look like: regions = {initialSize, regionSize, regions[1] * growthFactor, regions[2] * growthFactor, ... , regions[n - 1] * growthFactor} @param upstream The backing memory region will be allocated using the given upstream MemoryResource.
- L66 _public prototype_ `PMAAPI ArenaMemoryResource(std::size_t regionSize, MemoryResource* upstream);` — @brief Constructor @param regionSize When a memory region backing allocation requests has not enough free space to serve an allocation, an additional region is allocated for both the current and all subsequent allocations. This parameter denotes the size of the initial and all subsequently allocated regions. @note The growth factor in this case will be 1.0, i.e. no growth. @param upstream The backing memory region will be allocated using the given upstream MemoryResource.
- L68 _public prototype_ `PMAAPI ~ArenaMemoryResource();`
- L70 _public prototype_ `ArenaMemoryResource(const ArenaMemoryResource&) = delete;`
- L71 _public prototype_ `ArenaMemoryResource& operator=(const ArenaMemoryResource&) = delete;`
- L73 _public prototype_ `PMAAPI ArenaMemoryResource(ArenaMemoryResource&&);`
- L74 _public prototype_ `PMAAPI ArenaMemoryResource& operator=(ArenaMemoryResource&&);`
- L79 _public prototype_ `PMAAPI void* allocate(std::size_t size, std::size_t alignment) override;` — @brief All allocations will be served from the currently active memory region.
- L83 _public prototype_ `PMAAPI void deallocate(void* ptr, std::size_t size, std::size_t alignment) override;` — @brief This is a no-op, and the regions are only freed when the arena itself is destroyed.
- L87 _public prototype_ `PMAAPI MemoryResource* getUpstreamMemoryResource() const;` — @brief The upstream memory resource was passed through the constructor and is backing all arena allocations.
- L91 _private member_ `ScopedPtr<Impl, FactoryDestroy<Impl>> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/resources/DefaultMemoryResource.h` (Public)


#### class `pma::DefaultMemoryResource`  
`class PMAAPI DefaultMemoryResource : public MemoryResource`  
_L16-20_
- inherits: `MemoryResource`
- desc: @brief A MemoryResource that delegates to malloc / free. @see MemoryResource
- L18 _public prototype_ `void* allocate(std::size_t size, std::size_t alignment) override;`
- L19 _public prototype_ `void deallocate(void* ptr, std::size_t size, std::size_t alignment) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/utils/ManagedInstance.h` (Public)


#### class `pma::impl::ManagedInstance`  
`template<class TPointer, class TTarget, class TBase = TTarget> class ManagedInstance`  
_L25-48_
- L27 _public typedef_ `using PointerType = TPointer;`
- L30 _private function_ `explicit ManagedInstance(MemoryResource* memRes) : pMemRes`
- L35 _public function_ `static ManagedInstance with(MemoryResource* memRes)`
- L40 _public function_ `template<typename... Args> PointerType create(Args&&... args)`
- L47 _private member_ `MemoryResource* pMemRes;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace pma`
- L22 _namespace_ `namespace impl` (scope `pma`)
- L42 _function_ `auto deleter = [alloc](TBase* ptr) mutable` (scope `pma::impl::ManagedInstance::create`)
- L53 _typedef_ `template<class TTarget, class TBase = TTarget> using UniqueInstance = impl::ManagedInstance<std::unique_ptr<TBase, std::function<void(TBase*)>>, TTarget, TBase>;` (scope `pma`)
- L56 _typedef_ `template<class TTarget, class TBase = TTarget> using SharedInstance = impl::ManagedInstance<std::shared_ptr<TBase>, TTarget, TBase>;` (scope `pma`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define PMA_MAJOR_VERSION 1`
- L6 _macro_ `#define PMA_MINOR_VERSION 3`
- L7 _macro_ `#define PMA_PATCH_VERSION 18`
- L8 _macro_ `#define PMA_VERSION_STRING "1.3.18"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define RLAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define RLAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define RLAPI` — Build or use static library

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/RigLogic.h` (Public)
_(no declarations extracted)_

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/riglogic/Configuration.h` (Public)


#### enum `rl4::CalculationType`  
`enum class CalculationType : std::uint8_t`  
_L12-20_
- desc: @brief Implementation type for RigLogic calculations.
- L13 _public enumerator_ `Scalar` — scalar CPU algorithm
- L14 _public enumerator_ `SSE` — vectorized (SSE) CPU algorithm
- L15 _public enumerator_ `AVX` — vectorized (AVX) CPU algorithm (RigLogic must be built with AVX support,
- L17 _public enumerator_ `NEON` — otherwise it falls back to using the Scalar version)
- L19 _public enumerator_ `AnyVector` — otherwise it falls back to using the Scalar version)

#### enum `rl4::FloatingPointType`  
`enum class FloatingPointType : std::uint8_t`  
_L25-28_
- desc: @brief Floating point type used in vectorized calculations.
- L26 _public enumerator_ `Float`
- L27 _public enumerator_ `HalfFloat`

#### enum `rl4::TranslationType`  
`enum class TranslationType : std::uint8_t`  
_L33-35_
- desc: @brief Translation type to be used by RigLogic.
- L34 _public enumerator_ `Vector = 3`

#### enum `rl4::RotationType`  
`enum class RotationType : std::uint8_t`  
_L40-43_
- desc: @brief Rotation type to be used by RigLogic.
- L41 _public enumerator_ `EulerAngles = 3`
- L42 _public enumerator_ `Quaternions = 4`

#### enum `rl4::ScaleType`  
`enum class ScaleType : std::uint8_t`  
_L48-50_
- desc: @brief Scale type to be used by RigLogic.
- L49 _public enumerator_ `Vector = 3`

#### struct `rl4::Configuration`  
`struct Configuration`  
_L52-67_
- L53 _public member_ `CalculationType calculationType = CalculationType::AnyVector;`
- L54 _public member_ `FloatingPointType floatingPointType = FloatingPointType::HalfFloat;`
- L55 _public member_ `bool loadJoints = true;`
- L56 _public member_ `bool loadBlendShapes = true;`
- L57 _public member_ `bool loadAnimatedMaps = true;`
- L58 _public member_ `bool loadMachineLearnedBehavior = true;`
- L59 _public member_ `bool loadRBFBehavior = true;`
- L60 _public member_ `bool loadTwistSwingBehavior = true;`
- L61 _public member_ `TranslationType translationType = TranslationType::Vector;`
- L62 _public member_ `RotationType rotationType = RotationType::EulerAngles;`
- L63 _public member_ `ScaleType scaleType = ScaleType::Vector;`
- L64 _public member_ `float translationPruningThreshold = 0.0f;` — Reasonably safe to try 0.0001f;
- L65 _public member_ `float rotationPruningThreshold = 0.0f;` — Reasonably safe to try 0.1f
- L66 _public member_ `float scalePruningThreshold = 0.0f;` — Reasonably safe to try 0.001f;

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/riglogic/RigInstance.h` (Public)


#### class `rl4::RigInstance`  
`class RLAPI RigInstance`  
_L23-109_
- desc: @brief RigInstance contains the instance specific data of a rig. @note The input / output buffers are all contained within a rig instance. It provides functions for setting the level of detail and input control values of a single instance, as well as accessors to the output values of joints, blend shapes and animated maps. To evaluate / drive the rig instance, it must be passed to the RigLogic::calculate function. @see RigLogic
- L25 _protected prototype_ `virtual ~RigInstance();`
- L45 _public prototype_ `static RigInstance* create(RigLogic* rigLogic, MemoryResource* memRes = nullptr);` — @brief Factory method for the creation of rig instances. @note Rig instances are all tied to their parent RigLogic instance. All rig instances created through a particular RigLogic instance are based on the same DNA. @warning It is not possible to evaluate a rig instance created through one RigLogic instance by another RigLogic instance. @param rigLogic The RigLogic instance upon which this RigInstance should be based. @param memRes A custom memory resource to be used for the allocation of the rig instance resources. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L50 _public prototype_ `static void destroy(RigInstance* instance);` — @brief Method for freeing rig instances. @see create
- L52 _public prototype_ `virtual std::uint16_t getGUIControlCount() const = 0;`
- L53 _public prototype_ `virtual float getGUIControl(std::uint16_t index) const = 0;`
- L54 _public prototype_ `virtual void setGUIControl(std::uint16_t index, float value) = 0;`
- L55 _public prototype_ `virtual ArrayView<float> getGUIControlValues() = 0;`
- L56 _public prototype_ `virtual ConstArrayView<float> getGUIControlValues() const = 0;`
- L58 _public prototype_ `virtual std::uint16_t getRawControlCount() const = 0;`
- L59 _public prototype_ `virtual float getRawControl(std::uint16_t index) const = 0;`
- L60 _public prototype_ `virtual void setRawControl(std::uint16_t index, float value) = 0;`
- L61 _public prototype_ `virtual ArrayView<float> getRawControlValues() = 0;`
- L62 _public prototype_ `virtual ConstArrayView<float> getRawControlValues() const = 0;`
- L64 _public prototype_ `virtual std::uint16_t getPSDControlCount() const = 0;`
- L65 _public prototype_ `virtual float getPSDControl(std::uint16_t index) const = 0;`
- L66 _public prototype_ `virtual ConstArrayView<float> getPSDControlValues() const = 0;`
- L68 _public prototype_ `virtual std::uint16_t getMLControlCount() const = 0;`
- L69 _public prototype_ `virtual float getMLControl(std::uint16_t index) const = 0;`
- L70 _public prototype_ `virtual ConstArrayView<float> getMLControlValues() const = 0;`
- L72 _public prototype_ `virtual std::uint16_t getMLTypeCount() const = 0;`
- L73 _public prototype_ `virtual std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const = 0;`
- L74 _public prototype_ `virtual std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;`
- L75 _public prototype_ `virtual ConstArrayView<float> getMLMaskValues() const = 0;`
- L76 _public prototype_ `virtual ArrayView<float> getMLMaskValues() = 0;`
- L78 _public prototype_ `virtual std::uint16_t getRBFControlCount() const = 0;`
- L79 _public prototype_ `virtual float getRBFControl(std::uint16_t index) const = 0;`
- L80 _public prototype_ `virtual ConstArrayView<float> getRBFControlValues() const = 0;`
- L88 _public prototype_ `virtual ConstArrayView<float> getJointOutputs() const = 0;` — @brief Calculated values for joint transformations. @note This is just a primitive array of floats, providing access to all the values of all transformations. @return View over the array of values.
- L93 _public prototype_ `virtual ConstArrayView<float> getBlendShapeOutputs() const = 0;` — @brief Calculated values for blend shape deformations. @return View over the array of floats.
- L98 _public prototype_ `virtual ConstArrayView<float> getAnimatedMapOutputs() const = 0;` — @brief Calculated values for animated map deformations. @return View over the array of floats.
- L102 _public prototype_ `virtual std::uint16_t getLOD() const = 0;` — @brief The current level of details of this instance.
- L108 _public prototype_ `virtual void setLOD(std::uint16_t level) = 0;` — @brief The current level of details of this instance. @param level Value to set for current level of details.

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<rl4::RigInstance>`  
_L116-118_
- L117 _public typedef_ `using type = FactoryCreate<rl4::RigInstance>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<rl4::RigInstance>`  
_L121-123_
- L122 _public typedef_ `using type = FactoryDestroy<rl4::RigInstance>;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace rl4`
- L113 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/riglogic/RigLogic.h` (Public)


#### class `rl4::RigLogic`  
`class RLAPI RigLogic`  
_L24-303_
- desc: @brief RigLogic calculates rig output values based on input control values. @note A single RigLogic instance can create and drive an arbitrary number of rig instances. Since the rig instance specific data is located on the RigInstance class, RigLogic itself may be considered stateless, and all of it's functions thread-safe. @see RigInstance
- L26 _public typedef_ `using Configuration = rl4::Configuration;`
- L29 _protected prototype_ `virtual ~RigLogic();`
- L47 _public prototype_ `static RigLogic* create(const dna::Reader* reader, const Configuration& config = {}, MemoryResource* memRes = nullptr);` — @brief Factory method for the creation of RigLogic. @param reader Source from which to copy and optimize DNA data, which is used for rig evaluation @param config Determines which algorithm implementation is used for rig evaluation and which submodules to load (affects memory allocations) @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L54 _public prototype_ `static void destroy(RigLogic* instance);` — @brief Method for freeing RigLogic. @param instance Instance of RigLogic to be freed. @see create
- L72 _public prototype_ `static RigLogic* restore(BoundedIOStream* source, MemoryResource* memRes = nullptr);` — @brief Factory method for restoring an instance of RigLogic from a memory dump. @note This form of creation allows faster instantiation of RigLogic, as it doesn't need to go through the storage optimization phase, it just loads an earlier dumped state of a RigLogic instance back into memory. @param source Source stream from which to restore the state, obtained by calling dump. @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see dump @see destroy
- L79 _public prototype_ `virtual void dump(BoundedIOStream* destination) const = 0;` — @brief Create a snapshot of an initialized RigLogic instance. @param destination The output stream into which the current state of RigLogic is going to be written. @see restore
- L83 _public prototype_ `virtual const Configuration& getConfiguration() const = 0;` — @brief Retrieve the configuration that RigLogic was initialized with.
- L89 _public prototype_ `virtual std::uint16_t getLODCount() const = 0;` — @brief Available levels of detail (e.g. 6 which means the following levels are available: [0,1,2,3,4,5], where 0 is the LOD with the highest details, and 5 is the LOD with lowest details).
- L95 _public prototype_ `virtual ConstArrayView<std::uint16_t> getRBFSolverIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of RBF solver indices that need to be computed on the specified LOD. @param lod The LOD for which the indices are requested.
- L101 _public prototype_ `virtual ConstArrayView<std::uint16_t> getMLOperationIndicesForLOD(std::uint16_t lod, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;` — @brief List of ML operation indices that need to be computed on the specified LOD. @param lod The LOD for which the indices are requested.
- L109 _public prototype_ `virtual ConstArrayView<std::uint16_t> getBlendShapeChannelIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of blend shape channel indices that need to be computed on the specified LOD. @param lod The LOD for which the indices are requested.
- L115 _public prototype_ `virtual ConstArrayView<std::uint16_t> getAnimatedMapIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of animated map indices that need to be computed on the specified LOD. @param lod The LOD for which the indices are requested.
- L121 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointIndicesForLOD(std::uint16_t lod) const = 0;` — @brief List of joint indices that need to be computed on the specified LOD. @param lod The LOD for which the indices are requested.
- L128 _public prototype_ `virtual ConstArrayView<float> getNeutralJointValues() const = 0;` — @brief Neutral values of joint transformations. @note These is just a primitive array of floats, providing access to all the values of all transformations. @return View over the array of values.
- L132 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointVariableAttributeIndices(std::uint16_t lod) const = 0;` — @brief All joint output indices concatenated into a single chunk per each LOD.
- L137 _public prototype_ `virtual std::uint16_t getJointGroupCount() const = 0;` — @brief Number of joint groups present in the entire joint matrix. @see calculateJoints
- L142 _public prototype_ `virtual std::uint16_t getRBFSolverCount() const = 0;` — @brief Number of RBF solvers for driving RBF behavior. @see calculateRBFBehavior
- L146 _public prototype_ `virtual std::uint16_t getTwistCount() const = 0;` — @brief Number of twist setups in body behavior.
- L150 _public prototype_ `virtual std::uint16_t getSwingCount() const = 0;` — @brief Number of swing setups in body behavior.
- L154 _public prototype_ `virtual std::uint16_t getMeshCount() const = 0;` — @brief Number of meshes.
- L158 _public prototype_ `virtual std::uint16_t getMeshRegionCount(std::uint16_t meshIndex) const = 0;` — @brief Number of regions within the specified mesh.
- L163 _public prototype_ `virtual std::uint16_t getMLTypeCount() const = 0;` — @brief Number of ML model types. @see calculateMLControls
- L167 _public prototype_ `virtual std::uint16_t getMLOperationSetCount(std::uint16_t mlTypeIndex) const = 0;` — @brief Number of ML operation sets for the specified type.
- L172 _public prototype_ `virtual std::uint16_t getMLOperationCount(std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex) const = 0;` — @brief Number of ML operation for the specified type. @note This can be thought of as parallel instances of a series of operations.
- L178 _public prototype_ `virtual void mapGUIToRawControls(RigInstance* instance) const = 0;` — @brief Maps GUI controls to raw controls. @note This method may be called after either RigInstance::setGUIControlValues or RigInstance::setGUIControl was used.
- L184 _public prototype_ `virtual void mapRawToGUIControls(RigInstance* instance) const = 0;` — @brief Maps raw controls to GUI controls. @note This method may be called after either RigInstance::setRawControlValues or RigInstance::setRawControl was used.
- L193 _public prototype_ `virtual void calculateMLControls(RigInstance* instance) const = 0;` — @brief Calculate controls driving the machine learned behavior of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose controls for driving machine learned behavior are to be calculated. @see calculate
- L202 _public prototype_ `virtual void calculateMLControls(RigInstance* instance, std::uint16_t mlTypeIndex, std::uint16_t mlOperationSetIndex, std::uint16_t mlOperationIndex) const = 0;` — @brief Calculate controls driving the machine learned behavior of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose controls for driving machine learned behavior are to be calculated. @see calculate
- L214 _public prototype_ `virtual void calculateRBFControls(RigInstance* instance) const = 0;` — @brief Calculate controls driving the RBF behavior of the of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose controls for driving machine learned behavior are to be calculated. @see calculate
- L227 _public prototype_ `virtual void calculateRBFControls(RigInstance* instance, std::uint16_t solverIndex) const = 0;` — @brief Calculate controls driving the RBF behavior of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose controls for RBF behavior are to be calculated. @param solverIndex The RBF solver whose outputs need to be calculated. @warning The index must be less than the value returned by getRBFSolverCount. @see calculate
- L239 _public prototype_ `virtual void calculatePSDControls(RigInstance* instance) const = 0;` — @brief Calculate only the PSD control values of the rig. @note Based on the set or computed raw control values, calculate the PSD outputs. The raw control values, followed by the PSD, ML and RBF values represent the input values of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose outputs are to be calculated. @see calculate
- L248 _public prototype_ `virtual void calculateJoints(RigInstance* instance) const = 0;` — @brief Calculate only the joint outputs of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose outputs are to be calculated. @see calculate
- L264 _public prototype_ `virtual void calculateJoints(RigInstance* instance, std::uint16_t jointGroupIndex) const = 0;` — @brief Calculate individual joint groups. @note It's intended to be used in a multi-threaded environment, such that the calculatin of all joint groups is performed by several threads, instead of computing all at once. @note This is considered as an expert usage use case. @param instance The rig instance whose outputs are to be calculated. @param jointGroupIndex A joint group's position in the zero-indexed array of joint groups. @warning The index must be less than the value returned by getJointGroupCount. @see calculate
- L273 _public prototype_ `virtual void calculateBlendShapes(RigInstance* instance) const = 0;` — @brief Calculate only the blend shape channel weights of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose blend shape channel weights are to be calculated. @see calculate
- L282 _public prototype_ `virtual void calculateAnimatedMaps(RigInstance* instance) const = 0;` — @brief Calculate only the animated map outputs of the rig. @note This is considered as an advanced usage use case. @param instance The rig instance whose outputs are to be calculated. @see calculate
- L294 _public prototype_ `virtual void calculate(RigInstance* instance) const = 0;` — @brief Calculate outputs for joints, blend shapes, and animated maps. @note It performs a complete evaluation of the rig, computing all the output values in the following order: - Calculate input values (raw controls + PSDs) - Calculate joint output values - Calculate blend shape output values - Calculate animated map output values @param instance The rig instance whose outputs are to be calculated.
- L302 _public prototype_ `virtual void collectCalculationStats(const RigInstance* instance, Stats* stats) const = 0;` — @brief Collect stats that summarize the overall amount of data that participate in computation for the current LOD. @param instance The rig instance which provides the current LOD to compute the necessary stats. @param stats The object into which the collected data will be written.

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<rl4::RigLogic>`  
_L310-312_
- L311 _public typedef_ `using type = FactoryCreate<rl4::RigLogic>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<rl4::RigLogic>`  
_L315-317_
- L316 _public typedef_ `using type = FactoryDestroy<rl4::RigLogic>;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rl4`
- L307 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/riglogic/Stats.h` (Public)


#### struct `rl4::Stats`  
`struct Stats`  
_L11-21_
- L12 _public member_ `CalculationType calculationType;`
- L13 _public member_ `FloatingPointType floatingPointType;`
- L14 _public member_ `std::uint16_t rbfSolverCount;`
- L15 _public member_ `std::uint16_t mlOperationCount;`
- L16 _public member_ `std::uint16_t psdCount;`
- L17 _public member_ `std::uint16_t blendShapeChannelCount;`
- L18 _public member_ `std::uint16_t animatedMapCount;`
- L19 _public member_ `std::uint16_t jointCount;`
- L20 _public member_ `std::uint32_t jointDeltaValueCount;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/types/Aliases.h` (Public)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace rl4`
- L39 _typedef_ `template<typename T> using ArrayView = dna::ArrayView<T>;` (scope `rl4`)
- L42 _typedef_ `template<typename T> using ConstArrayView = dna::ConstArrayView<T>;` (scope `rl4`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define RL_MAJOR_VERSION 13`
- L6 _macro_ `#define RL_MINOR_VERSION 2`
- L7 _macro_ `#define RL_PATCH_VERSION 9`
- L8 _macro_ `#define RL_VERSION_STRING "13.2.9"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/riglogic/version/VersionInfo.h` (Public)


#### struct `rl4::VersionInfo`  
`struct RLAPI VersionInfo`  
_L10-15_
- L11 _public prototype_ `static int getMajorVersion();`
- L12 _public prototype_ `static int getMinorVersion();`
- L13 _public prototype_ `static int getPatchVersion();`
- L14 _public prototype_ `static StringView getVersionString();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace rl4`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/status/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define SCAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define SCAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define SCAPI` — Build or use static library

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/status/Provider.h` (Public)


#### struct `sc::impl::ISeq`  
`template<std::size_t... Is> struct ISeq`  
_L24-28_
- L25 _public function_ `static constexpr std::size_t size()`

#### struct `sc::impl::Make`  
`template<std::size_t Size, std::size_t Offset, std::size_t... Is> struct Make : Make<(Size - 1), Offset, (Offset + Size) - 1, Is...>`  
_L31-31_
- inherits: `Make<(Size - 1),Offset,(Offset + Size) -1,Is...>`
- L35 _public typedef_ `using Type = ISeq<Is...>;`

#### struct `sc::impl::Make`  
`template<std::size_t Offset, std::size_t... Is> struct Make<0, Offset, Is...>`  
_L34-36_
- L35 _public typedef_ `using Type = ISeq<Is...>;`

#### class `sc::StatusProvider`  
`class SCAPI StatusProvider`  
_L43-92_
- L45 _public prototype_ `explicit StatusProvider(std::initializer_list<StatusCode> statuses);`
- L47 _public prototype_ `static void reset();`
- L48 _public prototype_ `static StatusCode get();`
- L49 _public prototype_ `static bool isOk();`
- L50 _public prototype_ `static void set(StatusCode status);`
- L53 _public function_ `template<std::size_t... Is, typename... Args> static void set(StatusCode status, impl::ISeq<Is...> , Args&&... args)`
- L78 _public function_ `template<typename... Args> static void set(StatusCode status, Args&&... args)`
- L85 _private prototype_ `static void execSet(StatusCode status);`
- L86 _private prototype_ `static const char* execHook(StatusCode status, std::size_t index, const char* data);`
- L89 _private function_ `template<typename T> static T&& execHook(StatusCode , std::size_t , T&& data)`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace sc`
- L21 _namespace_ `namespace impl` (scope `sc`)
- L39 _typedef_ `template<std::size_t Size, std::size_t Offset = std::size_t{}> using MakeISeq = typename Make<Size, Offset>::Type;` (scope `sc::impl`)
- L80 _typedef_ `using ArgIndices = impl::MakeISeq<sizeof...(Args), static_cast<std::size_t>(1)>;` (scope `sc::StatusProvider::set`) — Generate a compile-time integer sequence for each argument [1..nargs]

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/status/Status.h` (Public)


#### class `sc::Status`  
`class SCAPI Status`  
_L29-35_
- L31 _public prototype_ `static bool isOk();`
- L32 _public prototype_ `static StatusCode get();`
- L33 _public prototype_ `static HookFunction getHook();`
- L34 _public prototype_ `static void setHook(HookFunction hook);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace sc`
- L27 _typedef_ `using HookFunction = const char* (*)(StatusCode, std::size_t, const char*);` (scope `sc`) — @brief Hook function that allows overriding the status message itself or any of the string arguments used for interpolation of the final status message. @param StatusCode The StatusCode itself whose message or argument is being hooked at the time of call. @param std::size_t The index denoting which argument is being processed by the hook. @note The value will be 0 when the hook is invoked for the status message itself, and from 1..N for any of the arguments used for interpolating the status message. Although the hook is invoked only for const char* arguments, the indices will still denote their actual position in the argument list. @param const char* The original status message or interpolation argument. @return Another message that will be used as status message or interpolation argument instead of the passed in const char*.

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/status/StatusCode.h` (Public)


#### struct `sc::StatusCode`  
`struct SCAPI StatusCode`  
_L11-14_
- L12 _public member_ `int code;`
- L13 _public member_ `const char* message;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace sc`
- L16 _function_ `inline bool operator==(const StatusCode& lhs, const StatusCode& rhs)` (scope `sc`)
- L20 _function_ `inline bool operator!=(const StatusCode& lhs, const StatusCode& rhs)` (scope `sc`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/status/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SC_MAJOR_VERSION 1`
- L6 _macro_ `#define SC_MINOR_VERSION 2`
- L7 _macro_ `#define SC_PATCH_VERSION 12`
- L8 _macro_ `#define SC_VERSION_STRING "1.2.12"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Ang.h` (Public)


#### struct `tdm::ang`  
`template<typename T, typename TUnit> struct ang`  
_L40-99_
- L41 _public typedef_ `using value_type = T;`
- L43 _public member_ `value_type value;`
- L45 _public function_ `ang() : value`
- L49 _public function_ `explicit constexpr ang(value_type val) : value`
- L53 _public function_ `constexpr ang(const ang<value_type, TUnit>& other) : value`
- L57 _public function_ `ang<value_type, TUnit>& operator=(const ang<value_type, TUnit>& other)`
- L65 _public function_ `explicit ang(const ang<U, impl::radians>& other) : value`
- L72 _public function_ `explicit ang(const ang<U, impl::degrees>& other) : value`
- L76 _public function_ `ang& operator+=(const ang& rhs)`
- L81 _public function_ `ang& operator-=(const ang& rhs)`
- L86 _public function_ `ang& operator*=(value_type val)`
- L91 _public function_ `ang& operator/=(value_type val)`
- L96 _public function_ `ang operator-() const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace tdm`
- L23 _function_ `inline constexpr double pi()` (scope `tdm`)
- L28 _function_ `template<typename T> inline typename std::enable_if<std::is_floating_point<T>::value, T>::type degrees(T radians)` (scope `tdm`)
- L34 _function_ `template<typename T> inline typename std::enable_if<std::is_floating_point<T>::value, T>::type radians(T degrees)` (scope `tdm`)
- L106 _function_ `template<typename T, typename TUnit> inline bool operator==(const ang<T, TUnit>& lhs, const ang<T, TUnit>& rhs)` (scope `tdm`)
- L111 _function_ `template<typename T, typename TUnit> inline bool operator!=(const ang<T, TUnit>& lhs, const ang<T, TUnit>& rhs)` (scope `tdm`)
- L116 _function_ `template<typename T, typename TUnit> inline ang<T, TUnit> operator+(const ang<T, TUnit>& lhs, const ang<T, TUnit>& rhs)` (scope `tdm`)
- L121 _function_ `template<typename T, typename TUnit> inline ang<T, TUnit> operator-(const ang<T, TUnit>& lhs, const ang<T, TUnit>& rhs)` (scope `tdm`)
- L126 _function_ `template<typename T, typename TUnit> inline ang<T, TUnit> operator*(const ang<T, TUnit>& lhs, T rhs)` (scope `tdm`)
- L131 _function_ `template<typename T, typename TUnit> inline ang<T, TUnit> operator*(T lhs, const ang<T, TUnit>& rhs)` (scope `tdm`)
- L136 _function_ `template<typename T, typename TUnit> inline ang<T, TUnit> operator/(const ang<T, TUnit>& lhs, T rhs)` (scope `tdm`)
- L140 _namespace_ `namespace ang_literals` (scope `tdm`)
- L142 _function_ `constexpr fdeg operator""_fdeg(long double angle)` (scope `tdm::ang_literals`)
- L146 _function_ `constexpr frad operator""_frad(long double angle)` (scope `tdm::ang_literals`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Computations.h` (Public)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace tdm`
- L23 _function_ `template<typename T> inline vec3<T> cross(const vec3<T>& lhs, const vec3<T>& rhs)` (scope `tdm`)
- L28 _function_ `template<dim_t L, typename T> inline T dot(const vec<L, T>& lhs, const vec<L, T>& rhs)` (scope `tdm`)
- L33 _function_ `template<typename T> inline T dot(const quat<T>& q1, const quat<T>& q2)` (scope `tdm`)
- L38 _function_ `template<dim_t L, typename T> inline vec<L, T> negate(vec<L, T> v)` (scope `tdm`)
- L43 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> negate(mat<R, C, T> m)` (scope `tdm`)
- L48 _function_ `template<typename T> inline quat<T> negate(quat<T> q)` (scope `tdm`)
- L53 _function_ `template<dim_t L, typename T> inline typename std::enable_if<std::is_floating_point<T>::value, T>::type length(const vec<L, T>& v)` (scope `tdm`)
- L58 _function_ `template<typename T> inline typename std::enable_if<std::is_floating_point<T>::value, T>::type length(const quat<T>& q)` (scope `tdm`)
- L63 _function_ `template<dim_t L, typename T> inline typename std::enable_if<std::is_floating_point<T>::value, vec<L, T>>::type normalize(vec<L, T> v)` (scope `tdm`)
- L68 _function_ `template<typename T> inline typename std::enable_if<std::is_floating_point<T>::value, quat<T>>::type normalize(quat<T> q)` (scope `tdm`)
- L73 _function_ `template<typename T> inline quat<T> conjugate(const quat<T>& q)` (scope `tdm`)
- L78 _function_ `template<typename T> inline quat<T> inverse(const quat<T>& q)` (scope `tdm`)
- L83 _function_ `template<typename T> inline quat<T> lerp(const quat<T>& q1, const quat<T>& q2, T t)` (scope `tdm`)
- L88 _function_ `template<typename T> inline quat<T> slerp(const quat<T>& q1, const quat<T>& q2, T t)` (scope `tdm`)
- L112 _function_ `template<dim_t R, dim_t C, typename T> inline mat<C, R, T> transpose(const mat<R, C, T>& m)` (scope `tdm`)
- L113 _typedef_ `using row_type = typename mat<C, R, T>::row_type;` (scope `tdm::transpose`)
- L115 _function_ `ret.apply([&m](row_type& row, dim_t i) { row = m.column(i); });` (scope `tdm::transpose`)
- L119 _namespace_ `namespace impl` (scope `tdm`)
- L125 _function_ `template<dim_t N, typename T> inline void minor(const mat<N, N, T>& input, dim_t dimensions, dim_t i, dim_t j, mat<N, N, T>& output)` (scope `tdm::impl`)
- L141 _function_ `template<dim_t N, typename T> inline T determinant(const mat<N, N, T>& m, dim_t dimensions)` (scope `tdm::impl`)
- L160 _function_ `template<dim_t N, typename T> inline mat<N, N, T> adjoint(const mat<N, N, T>& m)` (scope `tdm::impl`)
- L182 _function_ `template<dim_t N, typename T> inline T determinant(const mat<N, N, T>& m)` (scope `tdm`)
- L187 _function_ `template<dim_t N, typename T> inline mat<N, N, T> inverse(const mat<N, N, T>& m)` (scope `tdm`)
- L204 _function_ `template<dim_t N, typename T> inline T trace(const mat<N, N, T>& m)` (scope `tdm`)
- L212 _namespace_ `namespace lu` (scope `tdm`)
- L218 _function_ `template<dim_t N, typename T> inline bool decompose(mat<N, N, T>& a, vec<N, dim_t>& permute)` (scope `tdm::lu`)
- L285 _function_ `template<dim_t N, typename T> inline void substitute(const mat<N, N, T>& a, const vec<N, dim_t>& permute, vec<N, T>& b)` (scope `tdm::lu`)
- L312 _function_ `template<dim_t N, typename T> inline mat<N, N, T> inverse(mat<N, N, T> m)` (scope `tdm::lu`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/CoordSys.h` (Public)


#### struct `tdm::coord_sys`  
`struct coord_sys`  
_L32-65_
- L33 _public member_ `axis_dir x;`
- L34 _public member_ `axis_dir y;`
- L35 _public member_ `axis_dir z;`
- L38 _public function_ `template<typename T> mat3<T> basis() const`
- L48 _public function_ `template<typename T> chirality handedness() const`
- L61 _public function_ `template<typename T> bool valid() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace tdm`
- L9 _namespace_ `namespace impl` (scope `tdm`)
- L12 _function_ `template<typename T> inline vec3<T> axis_vector(axis_dir axis)` (scope `tdm::impl`)
- L67 _function_ `inline bool operator==(const coord_sys& lhs, const coord_sys& rhs)` (scope `tdm`)
- L71 _function_ `inline bool operator!=(const coord_sys& lhs, const coord_sys& rhs)` (scope `tdm`)
- L75 _function_ `inline bool operator==(const rot_sign& lhs, const rot_sign& rhs)` (scope `tdm`)
- L79 _function_ `inline bool operator!=(const rot_sign& lhs, const rot_sign& rhs)` (scope `tdm`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Mat.h` (Public)


#### struct `tdm::impl::is_all_scalar`  
`template<typename...> struct is_all_scalar : std::false_type`  
_L13-13_
- inherits: `std::false_type`

#### struct `tdm::impl::is_all_scalar`  
`template<> struct is_all_scalar<> : std::false_type`  
_L16-16_
- inherits: `std::false_type`

#### struct `tdm::impl::is_all_scalar`  
`template<typename T> struct is_all_scalar<T> : std::is_scalar<T>`  
_L19-19_
- inherits: `std::is_scalar<T>`

#### struct `tdm::impl::is_all_scalar`  
`template<typename T> struct is_all_scalar<T, T> : std::is_scalar<T>`  
_L22-22_
- inherits: `std::is_scalar<T>`

#### struct `tdm::impl::is_all_scalar`  
`template<typename T, typename... Us> struct is_all_scalar<T, T, Us...> : is_all_scalar<T, Us...>`  
_L25-25_
- inherits: `is_all_scalar<T,Us...>`

#### struct `tdm::mat`  
`template<dim_t R, dim_t C, typename T> struct mat`  
_L36-268_
- L37 _public typedef_ `using value_type = T;`
- L38 _public typedef_ `using row_type = vec<C, value_type>;`
- L39 _public typedef_ `using column_type = vec<R, value_type>;`
- L41 _public function_ `static constexpr dim_t rows()`
- L45 _public function_ `static constexpr dim_t columns()`
- L50 _private member_ `row_type values[R];`
- L53 _public function_ `mat() : values`
- L57 _public prototype_ `~mat() = default;`
- L59 _public prototype_ `mat(const mat&) = default;`
- L60 _public prototype_ `mat& operator=(const mat&) = default;`
- L62 _public prototype_ `mat(mat&&) = default;`
- L63 _public prototype_ `mat& operator=(mat&&) = default;`
- L66 _public function_ `template<typename U, typename std::enable_if<std::is_scalar<U>::value>::type* = nullptr> explicit mat(U scalar)`
- L72 _public function_ `mat(Us... scalars)`
- L80 _public function_ `template<typename U> mat(const mat<R, C, U>& rhs)`
- L85 _public function_ `template<typename U> mat& operator=(const mat<R, C, U>& rhs)`
- L90 _public function_ `template<typename... Us, typename std::enable_if<sizeof...(Us) == R>::type* = nullptr> mat(const vec<C, Us>&... vs) : values`
- L95 _public function_ `template<typename... Us, typename std::enable_if<sizeof...(Us) == R>::type* = nullptr> static mat from_rows(const vec<C, Us>&... vs)`
- L100 _public function_ `template<typename... Us, typename std::enable_if<sizeof...(Us) == C>::type* = nullptr> static mat from_columns(const vec<R, Us>&... vs)`
- L106 _public function_ `template<typename U, typename..., dim_t H = R, dim_t W = C> static typename std::enable_if<H == W, mat>::type diagonal(U scalar)`
- L113 _public function_ `template<typename U, typename..., dim_t H = R, dim_t W = C> static typename std::enable_if<H == W, mat>::type diagonal(const vec<W, U>& scalars)`
- L120 _public function_ `template<typename... Us, dim_t H = R, dim_t W = C> static typename std::enable_if<(H == W) && (sizeof...(Us) == H), mat>::type diagonal(Us... scalars)`
- L125 _public function_ `template<typename..., dim_t H = R, dim_t W = C> static typename std::enable_if<H == W, mat>::type identity()`
- L129 _public function_ `row_type& operator[](dim_t index)`
- L136 _public function_ `const row_type& operator[](dim_t index) const`
- L143 _public function_ `T& operator()(dim_t rowIndex, dim_t colIndex)`
- L147 _public function_ `const T& operator()(dim_t rowIndex, dim_t colIndex) const`
- L152 _public function_ `template<typename F> mat& apply(F func)`
- L160 _public function_ `template<typename F> const mat& apply(F func) const`
- L167 _public function_ `mat& operator++()`
- L171 _public function_ `mat& operator--()`
- L176 _public function_ `template<typename U> mat& operator+=(U rhs)`
- L181 _public function_ `template<typename U> mat& operator+=(const mat<R, C, U>& rhs)`
- L185 _public function_ `mat& operator+=(const mat& rhs)`
- L190 _public function_ `template<typename U> mat& operator-=(U rhs)`
- L195 _public function_ `template<typename U> mat& operator-=(const mat<R, C, U>& rhs)`
- L199 _public function_ `mat& operator-=(const mat& rhs)`
- L204 _public function_ `template<typename U> mat& operator*=(U rhs)`
- L209 _public function_ `template<typename U> mat& operator*=(const mat<R, C, U>& rhs)`
- L213 _public function_ `mat& operator*=(const mat& rhs)`
- L218 _public function_ `template<typename U> mat& operator/=(U rhs)`
- L223 _public function_ `template<typename U> mat& operator/=(const mat<R, C, U>& rhs)`
- L227 _public function_ `mat& operator/=(const mat& rhs)`
- L232 _public function_ `template<typename..., dim_t H = R, dim_t W = C> typename std::enable_if<H == W, mat&>::type transpose()`
- L236 _public function_ `mat& negate()`
- L241 _public function_ `row_type row(dim_t index) const`
- L245 _public function_ `column_type column(dim_t index) const`
- L252 _public function_ `template<dim_t H, dim_t W> typename std::enable_if<(H > 1 && W > 1 && H <= R && W <= C), mat<H, W, T>>::type submat(dim_t y, dim_t x) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace tdm`
- L10 _namespace_ `namespace impl` (scope `tdm`)
- L30 _prototype_ `template<dim_t R, dim_t C, typename T> inline mat<C, R, T> transpose(const mat<R, C, T>& m);` (scope `tdm`)
- L33 _prototype_ `template<dim_t N, typename T> inline mat<N, N, T> inverse(const mat<N, N, T>& m);` (scope `tdm`)
- L67 _function_ `apply([scalar](row_type& row, dim_t ) { row = row_type{scalar}; });` (scope `tdm::mat::mat`)
- L74 _function_ `apply([&tmp](row_type& row, dim_t ri) { row.apply([&tmp, ri](value_type& value, dim_t ci) { value = tmp[ri * columns() + ci]; }); });` (scope `tdm::mat::mat`)
- L75 _function_ `row.apply([&tmp, ri](value_type& value, dim_t ci) { value = tmp[ri * columns() + ci]; });` (scope `tdm::mat::mat::__anonb64512450202`)
- L81 _function_ `apply([&rhs](row_type& row, dim_t ri) { row = rhs[ri]; });` (scope `tdm::mat::mat`)
- L108 _function_ `ret.apply([scalar](row_type& row, dim_t ri) { row[ri] = scalar; });` (scope `tdm::mat::diagonal`)
- L115 _function_ `ret.apply([&scalars](row_type& row, dim_t ri) { row[ri] = scalars[ri]; });` (scope `tdm::mat::diagonal`)
- L168 _function_ `return apply([](row_type& row, dim_t ) { ++row; });` (scope `tdm::mat::operator ++`)
- L172 _function_ `return apply([](row_type& row, dim_t ) { --row; });` (scope `tdm::mat::operator --`)
- L177 _function_ `return apply([rhs](row_type& row, dim_t ) { row += rhs; });` (scope `tdm::mat::operator +=`)
- L182 _function_ `return apply([&rhs](row_type& row, dim_t ri) { row += rhs[ri]; });` (scope `tdm::mat::operator +=`)
- L191 _function_ `return apply([rhs](row_type& row, dim_t ) { row -= rhs; });` (scope `tdm::mat::operator -=`)
- L196 _function_ `return apply([&rhs](row_type& row, dim_t ri) { row -= rhs[ri]; });` (scope `tdm::mat::operator -=`)
- L205 _function_ `return apply([rhs](row_type& row, dim_t ) { row *= rhs; });` (scope `tdm::mat::operator *=`)
- L219 _function_ `return apply([rhs](row_type& row, dim_t ) { row /= rhs; });` (scope `tdm::mat::operator /=`)
- L237 _function_ `apply([](row_type& row, dim_t ) { row.negate(); });` (scope `tdm::mat::negate`)
- L247 _function_ `apply([&col, index](const row_type& row, dim_t ri) { col[ri] = row[index]; });` (scope `tdm::mat::column`)
- L260 _function_ `ret.apply([this, y, x](typename mat<H, W, T>::row_type& row, dim_t ri) { row.apply([this, y, x, ri](value_type& value, dim_t ci) { value = values[y + ri][x + ci]; }); });` (scope `tdm::mat::submat`)
- L261 _function_ `row.apply([this, y, x, ri](value_type& value, dim_t ci) { value = values[y + ri][x + ci]; });` (scope `tdm::mat::submat::__anonb64512451102`)
- L271 _function_ `template<dim_t R, dim_t C, typename T> inline bool operator==(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L272 _typedef_ `using row_type = typename mat<R, C, T>::row_type;` (scope `tdm::operator ==`)
- L274 _function_ `lhs.apply([&rhs, &retval](const row_type& row, dim_t ri) { retval = retval && (row == rhs[ri]); });` (scope `tdm::operator ==`)
- L279 _function_ `template<dim_t R, dim_t C, typename T> inline bool operator!=(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L284 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator+(const mat<R, C, T>& m)` (scope `tdm`)
- L289 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator-(const mat<R, C, T>& m)` (scope `tdm`)
- L296 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator+(const mat<R, C, T>& lhs, T rhs)` (scope `tdm`)
- L301 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator+(T lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L306 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator+(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L311 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator-(const mat<R, C, T>& lhs, T rhs)` (scope `tdm`)
- L316 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator-(T lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L321 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator-(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L326 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator*(const mat<R, C, T>& lhs, T rhs)` (scope `tdm`)
- L331 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator*(T lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L336 _function_ `template<dim_t R, dim_t C, typename T> inline typename mat<R, C, T>::row_type operator*(const typename mat<R, C, T>::column_type& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L337 _typedef_ `using row_type = typename mat<R, C, T>::row_type;` (scope `tdm::operator *`)
- L339 _function_ `rhs.apply([&ret, &lhs](const row_type& row, dim_t ri) { ret += (row * row_type{lhs[ri]}); });` (scope `tdm::operator *`)
- L344 _function_ `template<dim_t R, dim_t C, typename T> inline typename mat<R, C, T>::column_type operator*(const mat<R, C, T>& lhs, const typename mat<R, C, T>::row_type& rhs)` (scope `tdm`)
- L345 _typedef_ `using column_type = typename mat<R, C, T>::column_type;` (scope `tdm::operator *`)
- L346 _typedef_ `using value_type = typename column_type::value_type;` (scope `tdm::operator *`)
- L348 _function_ `rhs.apply([&ret, &lhs](value_type value, dim_t ci) { ret += (lhs.column(ci) * column_type{value}); });` (scope `tdm::operator *`)
- L353 _function_ `template<dim_t R, dim_t S, dim_t C, typename T> inline mat<R, C, T> operator*(const mat<R, S, T>& lhs, const mat<S, C, T>& rhs)` (scope `tdm`)
- L356 _function_ `ret.apply([&lhs, &rhs](row_type& row, dim_t ri) { row = (lhs[ri] * rhs); });` (scope `tdm::operator *`)
- L361 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator/(const mat<R, C, T>& lhs, T rhs)` (scope `tdm`)
- L366 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator/(T lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L367 _typedef_ `using row_type = typename mat<R, C, T>::row_type;` (scope `tdm::operator /`)
- L369 _function_ `tmp.apply([lhs](row_type& row, dim_t ) { row = lhs / row; });` (scope `tdm::operator /`)
- L374 _function_ `template<dim_t R, dim_t C, typename T> inline typename mat<R, C, T>::row_type operator/(const typename mat<R, C, T>::column_type& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L379 _function_ `template<dim_t R, dim_t C, typename T> inline typename mat<R, C, T>::column_type operator/(const mat<R, C, T>& lhs, const typename mat<R, C, T>::row_type& rhs)` (scope `tdm`)
- L384 _function_ `template<dim_t R, dim_t C, typename T> inline mat<R, C, T> operator/(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)` (scope `tdm`)
- L389 _function_ `template<dim_t R, dim_t C, typename T, typename F> inline mat<R, C, T> applied(const mat<R, C, T>& lhs, F func)` (scope `tdm`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Quat.h` (Public)


#### struct `tdm::impl::euler_to_quat`  
`template<typename T> struct euler_to_quat<T, rot_seq::xyz>`  
_L26-53_
- L28 _public function_ `quat<T> operator()(const rad3<T>& rot, rot_sign signs)`

#### struct `tdm::impl::euler_to_quat`  
`template<typename T> struct euler_to_quat<T, rot_seq::xzy>`  
_L56-82_
- L28 _public function_ `quat<T> operator()(const rad3<T>& rot, rot_sign signs)`

#### struct `tdm::impl::euler_to_quat`  
`template<typename T> struct euler_to_quat<T, rot_seq::yxz>`  
_L85-111_
- L28 _public function_ `quat<T> operator()(const rad3<T>& rot, rot_sign signs)`

#### struct `tdm::impl::euler_to_quat`  
`template<typename T> struct euler_to_quat<T, rot_seq::yzx>`  
_L114-140_
- L28 _public function_ `quat<T> operator()(const rad3<T>& rot, rot_sign signs)`

#### struct `tdm::impl::euler_to_quat`  
`template<typename T> struct euler_to_quat<T, rot_seq::zxy>`  
_L143-169_
- L28 _public function_ `quat<T> operator()(const rad3<T>& rot, rot_sign signs)`

#### struct `tdm::impl::euler_to_quat`  
`template<typename T> struct euler_to_quat<T, rot_seq::zyx>`  
_L172-198_
- L28 _public function_ `quat<T> operator()(const rad3<T>& rot, rot_sign signs)`

#### struct `tdm::impl::quat_to_euler`  
`template<typename T> struct quat_to_euler<T, rot_seq::xyz>`  
_L204-241_
- L206 _public function_ `rad3<T> operator()(const quat<T>& q, rot_sign signs)`

#### struct `tdm::impl::quat_to_euler`  
`template<typename T> struct quat_to_euler<T, rot_seq::xzy>`  
_L244-281_
- L206 _public function_ `rad3<T> operator()(const quat<T>& q, rot_sign signs)`

#### struct `tdm::impl::quat_to_euler`  
`template<typename T> struct quat_to_euler<T, rot_seq::yxz>`  
_L284-321_
- L206 _public function_ `rad3<T> operator()(const quat<T>& q, rot_sign signs)`

#### struct `tdm::impl::quat_to_euler`  
`template<typename T> struct quat_to_euler<T, rot_seq::yzx>`  
_L324-361_
- L206 _public function_ `rad3<T> operator()(const quat<T>& q, rot_sign signs)`

#### struct `tdm::impl::quat_to_euler`  
`template<typename T> struct quat_to_euler<T, rot_seq::zxy>`  
_L364-401_
- L206 _public function_ `rad3<T> operator()(const quat<T>& q, rot_sign signs)`

#### struct `tdm::impl::quat_to_euler`  
`template<typename T> struct quat_to_euler<T, rot_seq::zyx>`  
_L404-441_
- L206 _public function_ `rad3<T> operator()(const quat<T>& q, rot_sign signs)`

#### struct `tdm::quat`  
`template<typename T> struct quat`  
_L484-593_
- L485 _public typedef_ `using value_type = T;`
- L487 _public member_ `value_type x;`
- L488 _public member_ `value_type y;`
- L489 _public member_ `value_type z;`
- L490 _public member_ `value_type w;`
- L492 _public function_ `quat() : x`
- L499 _public function_ `quat(value_type x_, value_type y_, value_type z_, value_type w_) : x`
- L507 _public function_ `template<rot_seq order> static quat<T> from_euler(const rad3<T>& rot, rot_sign signs)`
- L511 _public function_ `explicit quat(const rad3<value_type>& rot, rot_seq order, rot_sign signs) : quat`
- L515 _public function_ `quat& operator+=(const quat& rhs)`
- L523 _public function_ `quat& operator-=(const quat& rhs)`
- L531 _public function_ `quat& operator*=(const quat& rhs)`
- L540 _public function_ `quat& operator*=(value_type val)`
- L548 _public function_ `quat& operator/=(value_type val)`
- L556 _public function_ `quat operator-() const`
- L561 _public function_ `template<rot_seq order> rad3<value_type> euler(rot_sign signs) const`
- L565 _public function_ `rad3<value_type> euler(rot_seq order, rot_sign signs) const`
- L569 _public function_ `quat& negate()`
- L577 _public function_ `value_type length2() const`
- L581 _public function_ `value_type length() const`
- L585 _public function_ `quat& normalize()`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace tdm`
- L20 _namespace_ `namespace impl` (scope `tdm`)
- L34 _function_ `rad3<T> c = applied(h, [](rad<T>& angle, dim_t ) { angle = rad<T>{std::cos(angle.value)}; });` (scope `tdm::impl::euler_to_quat::operator ()`)
- L35 _function_ `rad3<T> s = applied(h, [](rad<T>& angle, dim_t ) { angle = rad<T>{std::sin(angle.value)}; });` (scope `tdm::impl::euler_to_quat::operator ()`)
- L444 _function_ `template<typename T> quat<T> euler2quat(const rad3<T>& rot, rot_seq order, rot_sign signs)` (scope `tdm::impl`)
- L463 _function_ `template<typename T> rad3<T> quat2euler(const quat<T>& q, rot_seq order, rot_sign signs)` (scope `tdm::impl`)
- L596 _function_ `template<typename T> inline bool operator==(const quat<T>& lhs, const quat<T>& rhs)` (scope `tdm`)
- L601 _function_ `template<typename T> inline bool operator!=(const quat<T>& lhs, const quat<T>& rhs)` (scope `tdm`)
- L606 _function_ `template<typename T> inline quat<T> operator+(const quat<T>& lhs, const quat<T>& rhs)` (scope `tdm`)
- L611 _function_ `template<typename T> inline quat<T> operator-(const quat<T>& lhs, const quat<T>& rhs)` (scope `tdm`)
- L616 _function_ `template<typename T> inline quat<T> operator*(const quat<T>& lhs, const quat<T>& rhs)` (scope `tdm`)
- L621 _function_ `template<typename T> inline quat<T> operator*(const quat<T>& lhs, T rhs)` (scope `tdm`)
- L626 _function_ `template<typename T> inline quat<T> operator*(T lhs, const quat<T>& rhs)` (scope `tdm`)
- L631 _function_ `template<typename T> inline quat<T> operator/(const quat<T>& lhs, T rhs)` (scope `tdm`)
- L636 _function_ `template<typename T> inline quat<T> operator/(T lhs, const quat<T>& rhs)` (scope `tdm`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/TDM.h` (Public)
_(no declarations extracted)_

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Transforms.h` (Public)


#### struct `tdm::impl::rot_mat`  
`template<typename T> struct rot_mat<T, rot_seq::xyz>`  
_L106-110_
- L107 _public function_ `mat3<T> operator()(mat3<T> x, mat3<T> y, mat3<T> z)`

#### struct `tdm::impl::rot_mat`  
`template<typename T> struct rot_mat<T, rot_seq::xzy>`  
_L113-117_
- L107 _public function_ `mat3<T> operator()(mat3<T> x, mat3<T> y, mat3<T> z)`

#### struct `tdm::impl::rot_mat`  
`template<typename T> struct rot_mat<T, rot_seq::yxz>`  
_L120-124_
- L107 _public function_ `mat3<T> operator()(mat3<T> x, mat3<T> y, mat3<T> z)`

#### struct `tdm::impl::rot_mat`  
`template<typename T> struct rot_mat<T, rot_seq::yzx>`  
_L127-131_
- L107 _public function_ `mat3<T> operator()(mat3<T> x, mat3<T> y, mat3<T> z)`

#### struct `tdm::impl::rot_mat`  
`template<typename T> struct rot_mat<T, rot_seq::zxy>`  
_L134-138_
- L107 _public function_ `mat3<T> operator()(mat3<T> x, mat3<T> y, mat3<T> z)`

#### struct `tdm::impl::rot_mat`  
`template<typename T> struct rot_mat<T, rot_seq::zyx>`  
_L141-145_
- L107 _public function_ `mat3<T> operator()(mat3<T> x, mat3<T> y, mat3<T> z)`

#### struct `tdm::impl::mat_to_euler`  
`template<typename T> struct mat_to_euler<T, rot_seq::xyz>`  
_L179-213_
- desc: Row-major XYZ intrinsic (R = Rx * Ry * Rz):
- L180 _public function_ `rad3<T> operator()(const mat3<T>& m, rot_sign signs)`

#### struct `tdm::impl::mat_to_euler`  
`template<typename T> struct mat_to_euler<T, rot_seq::xzy>`  
_L217-246_
- desc: Row major XZY intrinsic (R = Rx * Rz * Ry)
- L180 _public function_ `rad3<T> operator()(const mat3<T>& m, rot_sign signs)`

#### struct `tdm::impl::mat_to_euler`  
`template<typename T> struct mat_to_euler<T, rot_seq::yxz>`  
_L250-281_
- desc: Row major YXZ intrinsic (R = Ry * Rx * Rz)
- L180 _public function_ `rad3<T> operator()(const mat3<T>& m, rot_sign signs)`

#### struct `tdm::impl::mat_to_euler`  
`template<typename T> struct mat_to_euler<T, rot_seq::yzx>`  
_L285-314_
- desc: Row major YZX intrinsic (R = Ry * Rz * Rx)
- L180 _public function_ `rad3<T> operator()(const mat3<T>& m, rot_sign signs)`

#### struct `tdm::impl::mat_to_euler`  
`template<typename T> struct mat_to_euler<T, rot_seq::zxy>`  
_L318-347_
- desc: Row major ZXY intrinsic (R = Rz * Rx * Ry)
- L180 _public function_ `rad3<T> operator()(const mat3<T>& m, rot_sign signs)`

#### struct `tdm::impl::mat_to_euler`  
`template<typename T> struct mat_to_euler<T, rot_seq::zyx>`  
_L351-380_
- desc: Row major ZYX intrinsic (R = Rz * Ry * Rx)
- L180 _public function_ `rad3<T> operator()(const mat3<T>& m, rot_sign signs)`

#### enum `tdm::sign_policy`  
`enum class sign_policy`  
_L533-540_
- L536 _public enumerator_ `discard` — Treat scale as a directionless per-axis magnitude: discard any sign, so the result is always non-negative. Correct for absolute scale factors (e.g. a neutral scale of ~1).
- L539 _public enumerator_ `preserve` — Preserve each component's sign: a change of basis only permutes the axes, it must not flip signs. Correct for signed scale deltas (offsets from a neutral scale, which may be negative).

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace tdm`
- L12 _function_ `template<typename T> inline typename std::enable_if<std::is_floating_point<T>::value, T>::type fastasin(T value)` (scope `tdm`)
- L40 _namespace_ `namespace affine` (scope `tdm`)
- L43 _function_ `template<dim_t L, typename T> inline mat<L, L, T> scale(const vec<L, T>& factors)` (scope `tdm::affine`)
- L48 _function_ `template<dim_t L, typename T> inline mat<L, L, T> scale(const mat<L, L, T>& m, const vec<L, T>& factors)` (scope `tdm::affine`)
- L53 _function_ `template<dim_t L, typename T> inline mat<L, L, T> scale(T factor)` (scope `tdm::affine`)
- L58 _function_ `template<dim_t L, typename T> inline mat<L, L, T> scale(const mat<L, L, T>& m, T factor)` (scope `tdm::affine`)
- L64 _namespace_ `namespace impl` (scope `tdm`)
- L67 _function_ `template<typename T> inline mat3<T> rotx(rad<T> x, rot_dir dir)` (scope `tdm::impl`)
- L79 _function_ `template<typename T> inline mat3<T> roty(rad<T> y, rot_dir dir)` (scope `tdm::impl`)
- L91 _function_ `template<typename T> inline mat3<T> rotz(rad<T> z, rot_dir dir)` (scope `tdm::impl`)
- L148 _function_ `template<typename T, rot_seq order> inline mat3<T> euler_to_mat(const rad3<T>& euler, rot_sign signs)` (scope `tdm::impl`)
- L156 _function_ `template<typename T> inline mat3<T> euler2mat(const rad3<T>& euler, rot_seq seq, rot_sign signs)` (scope `tdm::impl`)
- L387 _function_ `template<typename T> inline rad3<T> mat2euler(const mat3<T>& m, rot_seq seq, rot_sign signs)` (scope `tdm::impl`) — Dispatcher function for Euler extraction. The rot_sign parameter indicates the rotation direction convention per axis. Negative rotation direction means the sine terms were negated when building the matrix. The sign is applied in the mat_to_euler structs to match the original convention.
- L407 _namespace_ `namespace projective` (scope `tdm`)
- L410 _function_ `template<typename T> inline mat4<T> rotate(const vec3<T>& axis, rad<T> angle, rot_dir dir)` (scope `tdm::projective`)
- L434 _function_ `template<typename T> inline mat4<T> rotate(const mat4<T>& m, const vec3<T>& axis, rad<T> angle, rot_dir dir)` (scope `tdm::projective`)
- L439 _function_ `template<typename T> inline mat4<T> rotate(rad<T> x, rad<T> y, rad<T> z, rot_seq order, rot_sign signs)` (scope `tdm::projective`)
- L451 _function_ `template<typename T> inline mat4<T> rotate(const mat4<T>& m, rad<T> x, rad<T> y, rad<T> z, rot_seq order, rot_sign signs)` (scope `tdm::projective`)
- L456 _function_ `template<typename T> inline mat4<T> rotate(const rad3<T>& rotation, rot_seq order, rot_sign signs)` (scope `tdm::projective`)
- L461 _function_ `template<typename T> inline mat4<T> rotate(const mat4<T>& m, const rad3<T>& rotation, rot_seq order, rot_sign signs)` (scope `tdm::projective`)
- L466 _function_ `template<dim_t L, typename T> inline mat<L + 1, L + 1, T> scale(const vec<L, T>& factors)` (scope `tdm::projective`)
- L468 _function_ `factors.apply([&diagonal](const T& value, dim_t i) { diagonal[i] = value; });` (scope `tdm::projective::scale`)
- L473 _function_ `template<dim_t L, typename T> inline mat<L + 1, L + 1, T> scale(const mat<L + 1, L + 1, T>& m, const vec<L, T>& factors)` (scope `tdm::projective`)
- L478 _function_ `template<dim_t L, typename T> inline mat<L + 1, L + 1, T> scale(T factor)` (scope `tdm::projective`)
- L483 _function_ `template<dim_t L, typename T> inline mat<L, L, T> scale(const mat<L, L, T>& m, T factor)` (scope `tdm::projective`)
- L488 _function_ `template<dim_t L, typename T> inline mat<L + 1, L + 1, T> translate(const vec<L, T>& position)` (scope `tdm::projective`)
- L490 _function_ `position.apply([&m](const T& value, dim_t i) { m(L, i) = value; });` (scope `tdm::projective::translate`)
- L495 _function_ `template<dim_t L, typename T> inline mat<L + 1, L + 1, T> translate(const mat<L + 1, L + 1, T>& m, const vec<L, T>& position)` (scope `tdm::projective`)
- L502 _function_ `template<typename T> inline mat3<T> change_of_basis(const coord_sys& src, const coord_sys& dst)` (scope `tdm`)
- L511 _function_ `template<typename T> inline vec3<T> convert_position(const vec3<T>& pos, const mat3<T>& c)` (scope `tdm`) — Convert a position or translation vector between coordinate systems. Both positions and translations are transformed by the change-of-basis matrix.
- L516 _function_ `template<typename T> inline vec3<T> convert_position(const vec3<T>& pos, const coord_sys& src_cs, const coord_sys& dst_cs)` (scope `tdm`)
- L523 _function_ `template<typename T> inline vec3<T> convert_direction(const vec3<T>& dir, const mat3<T>& c, bool renormalize = true)` (scope `tdm`) — Convert a direction vector (normal, tangent) between coordinate systems. Optionally renormalizes the result (default: true).
- L529 _function_ `template<typename T> inline vec3<T> convert_direction(const vec3<T>& dir, const coord_sys& src_cs, const coord_sys& dst_cs, bool renormalize = true)` (scope `tdm`)
- L548 _function_ `template<typename T> inline vec3<T> convert_scale(const vec3<T>& scale, const mat3<T>& c, sign_policy policy)` (scope `tdm`) — Convert a scale vector between coordinate systems. A change of basis is a signed permutation. For a signed delta the similarity transform of the diagonal scaling cancels the axis-flip signs (they appear squared), leaving only the axis permutation, so sign_policy::preserve permutes by |c| and keeps each component's own sign. sign_policy::discard instead takes absolute values, treating scale as a directionless magnitude.
- L552 _function_ `[](vec3<T>& row, dim_t )` (scope `tdm::convert_scale`)
- L552 _function_ `[](vec3<T>& row, dim_t )` (scope `tdm::convert_scale::__anon873fdb120302`)
- L560 _function_ `template<typename T> inline vec3<T> convert_scale(const vec3<T>& scale, const coord_sys& src_cs, const coord_sys& dst_cs, sign_policy policy)` (scope `tdm`)
- L565 _function_ `template<typename T> inline rad3<T> convert_rotation(const rad3<T>& rotation, const mat3<T>& c, rot_seq src_seq, const rot_sign& src_signs, rot_seq dst_seq, const rot_sign& dst_signs)` (scope `tdm`)
- L580 _function_ `template<typename T> inline rad3<T> convert_rotation(const rad3<T>& rotation, const coord_sys& src_cs, rot_seq src_seq, const rot_sign& src_signs, const coord_sys& dst_cs, rot_seq dst_seq, const rot_sign& dst_signs)` (scope `tdm`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Types.h` (Public)


#### enum `tdm::chirality`  
`enum class chirality`  
_L119-122_
- L120 _public enumerator_ `left = -1`
- L121 _public enumerator_ `right = 1`

#### enum `tdm::rot_seq`  
`enum class rot_seq`  
_L124-131_
- L125 _public enumerator_ `xyz`
- L126 _public enumerator_ `xzy`
- L127 _public enumerator_ `yxz`
- L128 _public enumerator_ `yzx`
- L129 _public enumerator_ `zxy`
- L130 _public enumerator_ `zyx`

#### enum `tdm::rot_dir`  
`enum class rot_dir`  
_L133-136_
- L134 _public enumerator_ `negative = -1`
- L135 _public enumerator_ `positive = 1`

#### struct `tdm::rot_sign`  
`struct rot_sign`  
_L138-142_
- L139 _public member_ `rot_dir x;`
- L140 _public member_ `rot_dir y;`
- L141 _public member_ `rot_dir z;`

#### enum `tdm::axis_dir`  
`enum class axis_dir`  
_L144-151_
- L145 _public enumerator_ `left`
- L146 _public enumerator_ `right`
- L147 _public enumerator_ `up`
- L148 _public enumerator_ `down`
- L149 _public enumerator_ `front`
- L150 _public enumerator_ `back`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace tdm`
- L22 _typedef_ `using dim_t = std::size_t;` (scope `tdm`)
- L30 _typedef_ `template<typename T> using vec2 = vec<2, T>;` (scope `tdm`)
- L33 _typedef_ `template<typename T> using vec3 = vec<3, T>;` (scope `tdm`)
- L36 _typedef_ `template<typename T> using vec4 = vec<4, T>;` (scope `tdm`)
- L41 _typedef_ `template<dim_t L> using ivec = vec<L, int>;` (scope `tdm`)
- L43 _typedef_ `using ivec2 = ivec<2>;` (scope `tdm`)
- L44 _typedef_ `using ivec3 = ivec<3>;` (scope `tdm`)
- L45 _typedef_ `using ivec4 = ivec<4>;` (scope `tdm`)
- L48 _typedef_ `template<dim_t L> using fvec = vec<L, float>;` (scope `tdm`)
- L50 _typedef_ `using fvec2 = fvec<2>;` (scope `tdm`)
- L51 _typedef_ `using fvec3 = fvec<3>;` (scope `tdm`)
- L52 _typedef_ `using fvec4 = fvec<4>;` (scope `tdm`)
- L60 _typedef_ `template<typename T> using mat2 = mat<2, 2, T>;` (scope `tdm`)
- L63 _typedef_ `template<typename T> using mat3 = mat<3, 3, T>;` (scope `tdm`)
- L66 _typedef_ `template<typename T> using mat4 = mat<4, 4, T>;` (scope `tdm`)
- L71 _typedef_ `template<dim_t R, dim_t C> using imat = mat<R, C, int>;` (scope `tdm`)
- L73 _typedef_ `using imat2 = imat<2, 2>;` (scope `tdm`)
- L74 _typedef_ `using imat3 = imat<3, 3>;` (scope `tdm`)
- L75 _typedef_ `using imat4 = imat<4, 4>;` (scope `tdm`)
- L78 _typedef_ `template<dim_t R, dim_t C> using fmat = mat<R, C, float>;` (scope `tdm`)
- L80 _typedef_ `using fmat2 = fmat<2, 2>;` (scope `tdm`)
- L81 _typedef_ `using fmat3 = fmat<3, 3>;` (scope `tdm`)
- L82 _typedef_ `using fmat4 = fmat<4, 4>;` (scope `tdm`)
- L88 _namespace_ `namespace impl` (scope `tdm`)
- L96 _typedef_ `template<typename T> using deg = ang<T, impl::degrees>;` (scope `tdm`)
- L99 _typedef_ `template<typename T> using rad = ang<T, impl::radians>;` (scope `tdm`)
- L102 _typedef_ `template<typename T> using deg3 = vec3<deg<T>>;` (scope `tdm`)
- L105 _typedef_ `template<typename T> using rad3 = vec3<rad<T>>;` (scope `tdm`)
- L107 _typedef_ `using fdeg = deg<float>;` (scope `tdm`)
- L108 _typedef_ `using fdeg3 = deg3<float>;` (scope `tdm`)
- L109 _typedef_ `using frad = rad<float>;` (scope `tdm`)
- L110 _typedef_ `using frad3 = rad3<float>;` (scope `tdm`)
- L117 _typedef_ `using fquat = quat<float>;` (scope `tdm`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/Vec.h` (Public)


#### struct `tdm::vec`  
`template<dim_t L, typename T> struct vec`  
_L10-167_
- L11 _public typedef_ `using value_type = T;`
- L13 _public function_ `static constexpr dim_t dimensions()`
- L17 _public member_ `value_type values[L];`
- L19 _public function_ `vec() : values`
- L23 _public prototype_ `~vec() = default;`
- L25 _public prototype_ `vec(const vec& rhs) = default;`
- L26 _public prototype_ `vec& operator=(const vec& rhs) = default;`
- L28 _public prototype_ `vec(vec&& rhs) = default;`
- L29 _public prototype_ `vec& operator=(vec&& rhs) = default;`
- L32 _public function_ `template<typename U> vec(const vec<L, U>& rhs)`
- L37 _public function_ `template<typename U> vec& operator=(const vec<L, U>& rhs)`
- L43 _public function_ `template<typename... Vs, typename std::enable_if<(sizeof...(Vs) == L) || (sizeof...(Vs) == 0)>::type* = nullptr> vec(Vs... vs) : values`
- L48 _public function_ `template<typename U, typename..., typename std::enable_if<std::is_convertible<U, T>::value && (L > 1)>::type* = nullptr> explicit vec(U v)`
- L53 _public function_ `template<typename U, typename..., typename std::enable_if<std::is_convertible<U, T>::value>::type* = nullptr> explicit vec(U* pv)`
- L57 _public function_ `T& operator[](dim_t index)`
- L62 _public function_ `const T& operator[](dim_t index) const`
- L68 _public function_ `template<typename F> vec& apply(F func)`
- L76 _public function_ `template<typename F> const vec& apply(F func) const`
- L83 _public function_ `vec& operator++()`
- L87 _public function_ `vec& operator--()`
- L92 _public function_ `template<typename U> vec& operator+=(U rhs)`
- L97 _public function_ `template<typename U> vec& operator+=(const vec<L, U>& rhs)`
- L101 _public function_ `vec& operator+=(const vec& rhs)`
- L106 _public function_ `template<typename U> vec& operator-=(U rhs)`
- L111 _public function_ `template<typename U> vec& operator-=(const vec<L, U>& rhs)`
- L115 _public function_ `vec& operator-=(const vec& rhs)`
- L120 _public function_ `template<typename U> vec& operator*=(U rhs)`
- L125 _public function_ `template<typename U> vec& operator*=(const vec<L, U>& rhs)`
- L129 _public function_ `vec& operator*=(const vec& rhs)`
- L134 _public function_ `template<typename U> vec& operator/=(U rhs)`
- L139 _public function_ `template<typename U> vec& operator/=(const vec<L, U>& rhs)`
- L143 _public function_ `vec& operator/=(const vec& rhs)`
- L148 _public function_ `template<typename..., typename V = T> typename std::enable_if<std::is_floating_point<V>::value, V>::type length() const`
- L154 _public function_ `template<typename..., typename V = T> typename std::enable_if<std::is_floating_point<V>::value, vec&>::type normalize()`
- L158 _public function_ `vec& negate()`
- L162 _public function_ `T sum() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace tdm`
- L84 _function_ `return apply([](T& v, dim_t ) { ++v; });` (scope `tdm::vec::operator ++`)
- L88 _function_ `return apply([](T& v, dim_t ) { --v; });` (scope `tdm::vec::operator --`)
- L93 _function_ `return apply([rhs](T& v, dim_t ) { v += rhs; });` (scope `tdm::vec::operator +=`)
- L98 _function_ `return apply([&rhs](T& v, dim_t i) { v += rhs[i]; });` (scope `tdm::vec::operator +=`)
- L107 _function_ `return apply([rhs](T& v, dim_t ) { v -= rhs; });` (scope `tdm::vec::operator -=`)
- L112 _function_ `return apply([&rhs](T& v, dim_t i) { v -= rhs[i]; });` (scope `tdm::vec::operator -=`)
- L121 _function_ `return apply([rhs](T& v, dim_t ) { v *= rhs; });` (scope `tdm::vec::operator *=`)
- L126 _function_ `return apply([&rhs](T& v, dim_t i) { v *= rhs[i]; });` (scope `tdm::vec::operator *=`)
- L135 _function_ `return apply([rhs](T& v, dim_t ) { v /= rhs; });` (scope `tdm::vec::operator /=`)
- L140 _function_ `return apply([&rhs](T& v, dim_t i) { v /= rhs[i]; });` (scope `tdm::vec::operator /=`)
- L159 _function_ `return apply([](T& v, dim_t ) { v = -v; });` (scope `tdm::vec::negate`)
- L164 _function_ `apply([&retval](const T& v, dim_t ) { retval += v; });` (scope `tdm::vec::sum`)
- L170 _function_ `template<dim_t L, typename T> inline bool operator==(const vec<L, T>& lhs, const vec<L, T>& rhs)` (scope `tdm`)
- L172 _function_ `lhs.apply([&equal, &rhs](const T& v, dim_t i) { equal = equal && (v == rhs[i]); });` (scope `tdm::operator ==`)
- L177 _function_ `template<dim_t L, typename T> inline bool operator!=(const vec<L, T>& lhs, const vec<L, T>& rhs)` (scope `tdm`)
- L182 _function_ `template<dim_t L, typename T> inline vec<L, T> operator+(const vec<L, T>& v)` (scope `tdm`)
- L187 _function_ `template<dim_t L, typename T> inline vec<L, T> operator-(vec<L, T> v)` (scope `tdm`)
- L192 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator+(const vec<L, T>& lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L197 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator+(const vec<L, T>& lhs, U rhs)` (scope `tdm`)
- L202 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator+(T lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L207 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator-(const vec<L, T>& lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L212 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator-(const vec<L, T>& lhs, U rhs)` (scope `tdm`)
- L217 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator-(T lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L222 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator*(const vec<L, T>& lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L227 _function_ `template<dim_t L, typename T, typename U> inline typename std::enable_if<std::is_arithmetic<U>::value, vec<L, T>>::type operator*(const vec<L, T>& lhs, U rhs)` (scope `tdm`)
- L232 _function_ `template<dim_t L, typename T, typename U> inline typename std::enable_if<std::is_arithmetic<T>::value, vec<L, T>>::type operator*(T lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L237 _function_ `template<dim_t L, typename T, typename U> inline vec<L, T> operator/(const vec<L, T>& lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L242 _function_ `template<dim_t L, typename T, typename U> inline typename std::enable_if<std::is_arithmetic<U>::value, vec<L, T>>::type operator/(const vec<L, T>& lhs, U rhs)` (scope `tdm`)
- L247 _function_ `template<dim_t L, typename T, typename U> inline typename std::enable_if<std::is_arithmetic<T>::value, vec<L, T>>::type operator/(T lhs, const vec<L, U>& rhs)` (scope `tdm`)
- L252 _function_ `template<dim_t L, typename T, typename F> vec<L, T> applied(const vec<L, T>& lhs, F func)` (scope `tdm`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/tdm/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define TDM_MAJOR_VERSION 7`
- L6 _macro_ `#define TDM_MINOR_VERSION 0`
- L7 _macro_ `#define TDM_PATCH_VERSION 0`
- L8 _macro_ `#define TDM_VERSION_STRING "7.0.0"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/Archive.h` (Public)


#### class `terse::Archive`  
`template<class ArchiveImpl> class Archive`  
_L17-76_
- L19 _public function_ `explicit Archive(ArchiveImpl* impl_) : impl`
- L24 _public function_ `bool isOk()`
- L28 _public function_ `void sync()`
- L32 _public function_ `void label(const char* value)`
- L37 _public function_ `template<typename... Args> void operator()(Args&&... args)`
- L42 _public function_ `template<class TSerializable> ArchiveImpl& operator<<(TSerializable& source)`
- L48 _public function_ `template<class TSerializable> ArchiveImpl& operator>>(TSerializable& dest)`
- L53 _public function_ `void* getUserData() const`
- L57 _public function_ `void setUserData(void* data)`
- L63 _protected function_ `template<typename Head> void dispatch(Head&& head)`
- L68 _protected function_ `template<typename Head, typename... Tail> void dispatch(Head&& head, Tail&&... tail)`
- L74 _private member_ `ArchiveImpl* impl;`
- L75 _private member_ `void* userData;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/archives/Common.h` (Public)


#### struct `terse::impl::ValueFactory`  
`template<typename T> struct ValueFactory`  
_L29-68_
- L30 _public member_ `static constexpr bool NeedsAllocator = traits::needs_allocator<T>::value;`
- L31 _public member_ `static constexpr bool NeedsMemoryResource = std::is_constructible<T, pma::MemoryResource*>::value;`
- L32 _public member_ `static constexpr bool IsPair = traits::is_pair<T>::value;`
- L33 _public member_ `static constexpr bool IsTuple = traits::is_tuple<T>::value;`
- L34 _public member_ `static constexpr bool IsPrimitive = (!NeedsAllocator && !NeedsMemoryResource & !IsPair & !IsTuple);`
- L37 _public function_ `template<class ParentAllocator, bool IsPrimitive = IsPrimitive> static typename std::enable_if<IsPrimitive, T>::type create(const ParentAllocator& )`
- L42 _public function_ `template<class ParentAllocator, bool IsPrimitive = IsPrimitive> static typename std::enable_if<!IsPrimitive && NeedsMemoryResource, T>::type create(const ParentAllocator& alloc)`
- L48 _public function_ `create(const ParentAllocator& alloc)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace pma`
- L24 _namespace_ `namespace terse`
- L26 _namespace_ `namespace impl` (scope `terse`)
- L49 _typedef_ `using TAllocator = typename std::allocator_traits<ParentAllocator>::template rebind_alloc<typename T::value_type>;` (scope `terse::impl::ValueFactory::create`)
- L56 _typedef_ `using K = typename T::first_type;` (scope `terse::impl::ValueFactory::create`)
- L57 _typedef_ `using V = typename T::second_type;` (scope `terse::impl::ValueFactory::create`)
- L64 _typedef_ `using K = typename std::tuple_element<0, T>::type;` (scope `terse::impl::ValueFactory::create`)
- L65 _typedef_ `using V = typename std::tuple_element<0, T>::type;` (scope `terse::impl::ValueFactory::create`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/archives/Traits.h` (Public)


#### struct `terse::traits::sink`  
`template<typename...> struct sink`  
_L23-25_
- L24 _public typedef_ `using type = void;`

#### struct `terse::traits::needs_allocator`  
`template<typename T, typename = void> struct needs_allocator : std::false_type`  
_L28-28_
- inherits: `std::false_type`

#### struct `terse::traits::needs_allocator`  
`template<typename T> struct needs_allocator<T, typename sink<typename T::allocator_type, decltype(std::declval<T>().get_allocator())>::type> : std::true_type`  
_L31-32_
- inherits: `std::true_type`

#### struct `terse::traits::true_sink`  
`template<class> struct true_sink : std::true_type`  
_L35-35_
- inherits: `std::true_type`

#### struct `terse::traits::has_reserve_member`  
`template<class T> struct has_reserve_member : decltype(test_reserve_member<T>(0))`  
_L44-44_
- inherits: `decltype(test_reserve_member<T>(0)) `

#### struct `terse::traits::has_push_back_member`  
`template<class T> struct has_push_back_member : decltype(test_push_back_member<T>(0))`  
_L54-54_
- inherits: `decltype(test_push_back_member<T>(0)) `

#### struct `terse::traits::has_serialize_member`  
`template<class T> struct has_serialize_member : decltype(test_serialize_member<T>(0))`  
_L65-65_
- inherits: `decltype(test_serialize_member<T>(0)) `

#### struct `terse::traits::has_load_member`  
`template<class T> struct has_load_member : decltype(test_load_member<T>(0))`  
_L74-74_
- inherits: `decltype(test_load_member<T>(0)) `

#### struct `terse::traits::has_save_member`  
`template<class T> struct has_save_member : decltype(test_save_member<T>(0))`  
_L83-83_
- inherits: `decltype(test_save_member<T>(0)) `

#### struct `terse::traits::has_serialize_function`  
`template<class T> struct has_serialize_function : decltype(test_serialize_function<T>(0))`  
_L94-94_
- inherits: `decltype(test_serialize_function<T>(0)) `

#### struct `terse::traits::has_load_function`  
`template<class T> struct has_load_function : decltype(test_load_function<T>(0))`  
_L103-103_
- inherits: `decltype(test_load_function<T>(0)) `

#### struct `terse::traits::has_save_function`  
`template<class T> struct has_save_function : decltype(test_save_function<T>(0))`  
_L112-112_
- inherits: `decltype(test_save_function<T>(0)) `

#### struct `terse::traits::has_versioned_serialize_member`  
`template<class T, class V> struct has_versioned_serialize_member : decltype(test_versioned_serialize_member<T, V>(0))`  
_L124-124_
- inherits: `decltype(test_versioned_serialize_member<T, V>(0)) `

#### struct `terse::traits::has_versioned_load_member`  
`template<class T, class V> struct has_versioned_load_member : decltype(test_versioned_load_member<T, V>(0))`  
_L133-133_
- inherits: `decltype(test_versioned_load_member<T, V>(0)) `

#### struct `terse::traits::has_versioned_save_member`  
`template<class T, class V> struct has_versioned_save_member : decltype(test_versioned_save_member<T, V>(0))`  
_L142-142_
- inherits: `decltype(test_versioned_save_member<T, V>(0)) `

#### struct `terse::traits::has_versioned_serialize_function`  
`template<class T, class V> struct has_versioned_serialize_function : decltype(test_versioned_serialize_function<T, V>(0))`  
_L154-154_
- inherits: `decltype(test_versioned_serialize_function<T, V>(0)) `

#### struct `terse::traits::has_versioned_load_function`  
`template<class T, class V> struct has_versioned_load_function : decltype(test_versioned_load_function<T, V>(0))`  
_L163-163_
- inherits: `decltype(test_versioned_load_function<T, V>(0)) `

#### struct `terse::traits::has_versioned_save_function`  
`template<class T, class V> struct has_versioned_save_function : decltype(test_versioned_save_function<T, V>(0))`  
_L172-172_
- inherits: `decltype(test_versioned_save_function<T, V>(0)) `

#### struct `terse::traits::has_wide_elements`  
`template<typename TContainer> struct has_wide_elements`  
_L180-182_
- L181 _public member_ `static constexpr bool value = (sizeof(typename TContainer::value_type) > 1ul);`

#### struct `terse::traits::is_pair`  
`template<typename T> struct is_pair : public std::false_type`  
_L185-185_
- inherits: `std::false_type`

#### struct `terse::traits::is_pair`  
`template<typename K, typename V> struct is_pair<std::pair<K, V>> : public std::true_type`  
_L188-188_
- inherits: `std::true_type`

#### struct `terse::traits::is_tuple`  
`template<typename T> struct is_tuple : public std::false_type`  
_L191-191_
- inherits: `std::false_type`

#### struct `terse::traits::is_tuple`  
`template<typename K, typename V> struct is_tuple<std::tuple<K, V>> : public std::true_type`  
_L194-194_
- inherits: `std::true_type`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace terse`
- L20 _namespace_ `namespace traits` (scope `terse`)
- L38 _prototype_ `template<class TContainer> static auto test_reserve_member(std::int32_t) -> true_sink<decltype(std::declval<TContainer>().reserve(0u))>;` (scope `terse::traits`)
- L41 _prototype_ `template<class> static auto test_reserve_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L47 _prototype_ `template<class TContainer> static auto test_push_back_member(std::int32_t) -> true_sink<decltype(std::declval<TContainer>().push_back(std::declval<typename TContainer::value_type>()))>;` (scope `terse::traits`)
- L51 _prototype_ `template<class> static auto test_push_back_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L59 _prototype_ `template<class T> static auto test_serialize_member(std::int32_t) -> true_sink<decltype(std::declval<T>().serialize(std::declval<T&>()))>;` (scope `terse::traits`)
- L62 _prototype_ `template<class> static auto test_serialize_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L68 _prototype_ `template<class T> static auto test_load_member(std::int32_t) -> true_sink<decltype(std::declval<T>().load(std::declval<T&>()))>;` (scope `terse::traits`)
- L71 _prototype_ `template<class> static auto test_load_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L77 _prototype_ `template<class T> static auto test_save_member(std::int32_t) -> true_sink<decltype(std::declval<T>().save(std::declval<T&>()))>;` (scope `terse::traits`)
- L80 _prototype_ `template<class> static auto test_save_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L88 _prototype_ `template<class T> static auto test_serialize_function(std::int32_t) -> true_sink<decltype(serialize(std::declval<T&>(), std::declval<T&>()))>;` (scope `terse::traits`)
- L91 _prototype_ `template<class> static auto test_serialize_function(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L97 _prototype_ `template<class T> static auto test_load_function(std::int32_t) -> true_sink<decltype(load(std::declval<T&>(), std::declval<T&>()))>;` (scope `terse::traits`)
- L100 _prototype_ `template<class> static auto test_load_function(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L106 _prototype_ `template<class T> static auto test_save_function(std::int32_t) -> true_sink<decltype(save(std::declval<T&>(), std::declval<T&>()))>;` (scope `terse::traits`)
- L109 _prototype_ `template<class> static auto test_save_function(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L117 _prototype_ `template<class T, class V> static auto test_versioned_serialize_member(std::int32_t) -> true_sink<decltype(std::declval<T>().serialize(std::declval<T&>(), V{}))>;` (scope `terse::traits`)
- L121 _prototype_ `template<class, class> static auto test_versioned_serialize_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L127 _prototype_ `template<class T, class V> static auto test_versioned_load_member(std::int32_t) -> true_sink<decltype(std::declval<T>().load(std::declval<T&>(), V{}))>;` (scope `terse::traits`)
- L130 _prototype_ `template<class, class> static auto test_versioned_load_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L136 _prototype_ `template<class T, class V> static auto test_versioned_save_member(std::int32_t) -> true_sink<decltype(std::declval<T>().save(std::declval<T&>(), V{}))>;` (scope `terse::traits`)
- L139 _prototype_ `template<class, class> static auto test_versioned_save_member(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L147 _prototype_ `template<class T, class V> static auto test_versioned_serialize_function(std::int32_t) -> true_sink<decltype(serialize(std::declval<T&>(), V{}, std::declval<T&>()))>;` (scope `terse::traits`)
- L151 _prototype_ `template<class, class> static auto test_versioned_serialize_function(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L157 _prototype_ `template<class T, class V> static auto test_versioned_load_function(std::int32_t) -> true_sink<decltype(load(std::declval<T&>(), V{}, std::declval<T&>()))>;` (scope `terse::traits`)
- L160 _prototype_ `template<class, class> static auto test_versioned_load_function(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L166 _prototype_ `template<class T, class V> static auto test_versioned_save_function(std::int32_t) -> true_sink<decltype(save(std::declval<T&>(), V{}, std::declval<T&>()))>;` (scope `terse::traits`)
- L169 _prototype_ `template<class, class> static auto test_versioned_save_function(std::uint32_t) -> std::false_type;` (scope `terse::traits`)
- L177 _typedef_ `template<typename TContainer> using is_batchable = std::is_scalar<typename TContainer::value_type>;` (scope `terse::traits`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/archives/binary/InputArchive.h` (Public)


#### class `terse::ExtendableBinaryInputArchive`  
`template<class TExtender, class TStream, typename TSize, typename TOffset, Endianness EByteOrder> class ExtendableBinaryInputArchive : public Archive<TExtender>`  
_L39-327_
- inherits: `Archive<TExtender>`
- L42 _public typedef_ `using SizeType = TSize;` — Given the possibility of both 32 and 64bit platforms, use a fixed width type during serialization
- L43 _public typedef_ `using OffsetType = TOffset;`
- L45 _public function_ `static constexpr Endianness endianness()`
- L50 _private typedef_ `using BaseArchive = Archive<TExtender>;`
- L53 _public function_ `ExtendableBinaryInputArchive(TExtender* extender, TStream* stream_) : BaseArchive`
- L58 _public function_ `bool isOk()`
- L62 _public function_ `void sync()`
- L65 _public function_ `void label(const char* )`
- L68 _public function_ `std::size_t boundSize(std::size_t size)`
- L74 _protected function_ `template<typename T> void process(Transparent<T>&& dest)`
- L79 _protected function_ `template<typename T> void process(Transparent<T>& dest)`
- L83 _protected function_ `void process(Anchor<OffsetType>& dest)`
- L87 _protected function_ `void process(ArchiveOffset<OffsetType>& dest)`
- L93 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy& dest)`
- L98 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy&& dest)`
- L102 _protected function_ `void process(ArchiveSize<SizeType, OffsetType>& dest)`
- L107 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy& dest)`
- L113 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy&& dest)`
- L118 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_member<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L123 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_member<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L128 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L133 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L138 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_function<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L143 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_function<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L148 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L153 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L162 _protected function_ `process(Versioned<T, V>&& dest)`
- L171 _protected function_ `process(Versioned<T, V>& dest)`
- L178 _protected function_ `template<typename T> typename std::enable_if<traits::has_load_member<T>::value, void>::type process(T& dest)`
- L183 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_member<T>::value, void>::type process(T& dest)`
- L188 _protected function_ `template<typename T> typename std::enable_if<traits::has_load_function<T>::value, void>::type process(T& dest)`
- L193 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_function<T>::value, void>::type process(T& dest)`
- L201 _protected function_ `process(T& dest)`
- L208 _protected function_ `template<typename T, typename... Args> void process(Blob<T, Args...>& dest)`
- L218 _protected function_ `template<typename T, std::size_t N> void process(std::array<T, N>& dest)`
- L225 _protected function_ `template<typename T, typename... Args> void process(std::vector<T, Args...>& dest)`
- L231 _protected function_ `template<typename T, typename... Args> void process(DynArray<T, Args...>& dest)`
- L237 _protected function_ `template<typename T, typename... Args> void process(std::basic_string<T, Args...>& dest)`
- L243 _protected function_ `template<typename K, typename V> void process(std::pair<K, V>& dest)`
- L249 _protected function_ `template<typename K, typename V> void process(std::tuple<K, V>& dest)`
- L254 _protected function_ `std::size_t processSize()`
- L263 _protected function_ `processElements(TContainer& dest, std::size_t size)`
- L316 _private function_ `template<class TContainer> void resize(TContainer& dest, std::size_t size)`
- L321 _private function_ `template<typename T, class TAllocator> void resize(DynArray<T, TAllocator>& dest, std::size_t size)`
- L326 _private member_ `TStream* stream;`

#### class `terse::BinaryInputArchive`  
`template<class TStream, typename TSize = std::uint32_t, typename TOffset = TSize, Endianness EByteOrder = Endianness::Network> class BinaryInputArchive : public ExtendableBinaryInputArchive<BinaryInputArchive<TStream, TSize, TOffset, EByteOrder>, TStream, TSize, TOffset, EByteOrder>`  
_L330-349_
- inherits: `ExtendableBinaryInputArchive<BinaryInputArchive<TStream,TSize,TOffset,EByteOrder>,TStream,TSize,TOffset,EByteOrder>`
- L336 _private typedef_ `using BaseArchive = ExtendableBinaryInputArchive<BinaryInputArchive, TStream, TSize, TOffset, EByteOrder>;`
- L340 _public function_ `explicit BinaryInputArchive(TStream* stream_) : BaseArchive`
- L346 _private function_ `template<typename T> void process(T&& dest)`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace terse`
- L209 _typedef_ `using ValueType = typename Blob<T, Args...>::value_type;` (scope `terse::ExtendableBinaryInputArchive::process`)
- L264 _typedef_ `using ValueType = typename TContainer::value_type;` (scope `terse::ExtendableBinaryInputArchive::processElements`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/archives/binary/OutputArchive.h` (Public)


#### class `terse::ExtendableBinaryOutputArchive`  
`template<class TExtender, class TStream, typename TSize, typename TOffset, Endianness EByteOrder> class ExtendableBinaryOutputArchive : public Archive<TExtender>`  
_L39-330_
- inherits: `Archive<TExtender>`
- L41 _private typedef_ `using BaseArchive = Archive<TExtender>;`
- L45 _public typedef_ `using SizeType = TSize;` — Given the possibility of both 32 and 64bit platforms, use a fixed width type during serialization
- L46 _public typedef_ `using OffsetType = TOffset;`
- L48 _public function_ `static constexpr Endianness endianness()`
- L53 _public function_ `ExtendableBinaryOutputArchive(TExtender* extender, TStream* stream_) : BaseArchive`
- L58 _public function_ `bool isOk()`
- L62 _public function_ `void sync()`
- L65 _public function_ `void label(const char* )`
- L68 _public function_ `std::size_t boundSize(std::size_t size)`
- L74 _protected function_ `template<typename T> void process(Transparent<T>&& source)`
- L79 _protected function_ `template<typename T> void process(Transparent<T>& source)`
- L83 _protected function_ `void process(Anchor<OffsetType>& source)`
- L87 _protected function_ `void process(ArchiveOffset<OffsetType>& source)`
- L104 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy& source)`
- L117 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy&& source)`
- L121 _protected function_ `void process(ArchiveSize<SizeType, OffsetType>& source)`
- L138 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy& source)`
- L154 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy&& source)`
- L159 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_member<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L164 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_member<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L169 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L174 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L179 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_function<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L184 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_function<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L189 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L194 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L203 _protected function_ `process(Versioned<T, V>&& source)`
- L212 _protected function_ `process(Versioned<T, V>& dest)`
- L219 _protected function_ `template<typename T> typename std::enable_if<traits::has_save_member<T>::value, void>::type process(const T& source)`
- L224 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_member<T>::value, void>::type process(const T& source)`
- L229 _protected function_ `template<typename T> typename std::enable_if<traits::has_save_function<T>::value, void>::type process(const T& source)`
- L234 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_function<T>::value, void>::type process(const T& source)`
- L242 _protected function_ `process(const T& source)`
- L251 _protected function_ `template<typename T, typename... Args> void process(const Blob<T, Args...>& source)`
- L260 _protected function_ `template<typename T, std::size_t N> void process(const std::array<T, N>& source)`
- L265 _protected function_ `template<typename T, typename... Args> void process(const std::vector<T, Args...>& source)`
- L271 _protected function_ `template<typename T, typename... Args> void process(const DynArray<T, Args...>& source)`
- L277 _protected function_ `template<typename T, typename... Args> void process(const std::basic_string<T, Args...>& source)`
- L283 _protected function_ `template<typename K, typename V> void process(const std::pair<K, V>& source)`
- L289 _protected function_ `template<typename K, typename V> void process(const std::tuple<K, V>& source)`
- L294 _protected function_ `void processSize(std::size_t size)`
- L300 _protected function_ `template<class TContainer> typename std::enable_if<!traits::is_batchable<TContainer>::value>::type processElements(const TContainer& source)`
- L308 _protected function_ `processElements(const TContainer& source)`
- L329 _private member_ `TStream* stream;`

#### class `terse::BinaryOutputArchive`  
`template<class TStream, typename TSize = std::uint32_t, typename TOffset = TSize, Endianness EByteOrder = Endianness::Network> class BinaryOutputArchive : public ExtendableBinaryOutputArchive<BinaryOutputArchive<TStream, TSize, TOffset, EByteOrder>, TStream, TSize, TOffset, EByteOrder>`  
_L333-352_
- inherits: `ExtendableBinaryOutputArchive<BinaryOutputArchive<TStream,TSize,TOffset,EByteOrder>,TStream,TSize,TOffset,EByteOrder>`
- L339 _public typedef_ `using BaseArchive = ExtendableBinaryOutputArchive<BinaryOutputArchive, TStream, TSize, TOffset, EByteOrder>;`
- L343 _public function_ `explicit BinaryOutputArchive(TStream* stream_) : BaseArchive`
- L349 _private function_ `template<typename T> void process(T&& dest)`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace terse`
- L252 _typedef_ `using ValueType = typename Blob<T, Args...>::value_type;` (scope `terse::ExtendableBinaryOutputArchive::process`)
- L317 _typedef_ `using ValueType = typename TContainer::value_type;` (scope `terse::ExtendableBinaryOutputArchive::processElements`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/archives/json/InputArchive.h` (Public)


#### class `terse::ExtendableJSONInputArchive`  
`template<class TExtender, class TStream, typename TSize, typename TOffset> class ExtendableJSONInputArchive : public Archive<TExtender>`  
_L41-653_
- inherits: `Archive<TExtender>`
- L44 _public typedef_ `using SizeType = TSize;` — Given the possibility of both 32 and 64bit platforms, use a fixed width type during serialization
- L45 _public typedef_ `using OffsetType = TOffset;`
- L48 _private typedef_ `using BaseArchive = Archive<TExtender>;`
- L51 _public function_ `ExtendableJSONInputArchive(TExtender* extender, TStream* stream_) : BaseArchive`
- L58 _public function_ `bool isOk() const`
- L62 _public function_ `void sync()`
- L65 _public function_ `std::size_t boundSize(std::size_t size)`
- L69 _public function_ `void label(const char* value)`
- L110 _protected function_ `template<typename T> void process(Transparent<T>&& dest)`
- L115 _protected function_ `template<typename T> void process(Transparent<T>& dest)`
- L120 _protected function_ `void process(Anchor<OffsetType>& )`
- L124 _protected function_ `void process(ArchiveOffset<OffsetType>& dest)`
- L128 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy& )`
- L132 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy&& )`
- L136 _protected function_ `void process(ArchiveSize<SizeType, OffsetType>& dest)`
- L140 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy& )`
- L144 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy&& )`
- L149 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_member<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L154 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_member<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L172 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L177 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L195 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_function<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L200 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_load_function<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L218 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>&& dest)`
- L223 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>& dest)`
- L245 _protected function_ `process(Versioned<T, V>&& dest)`
- L254 _protected function_ `process(Versioned<T, V>& dest)`
- L261 _protected function_ `template<typename T> typename std::enable_if<traits::has_load_member<T>::value, void>::type process(T& dest)`
- L279 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_member<T>::value, void>::type process(T& dest)`
- L297 _protected function_ `template<typename T> typename std::enable_if<traits::has_load_function<T>::value, void>::type process(T& dest)`
- L315 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_function<T>::value, void>::type process(T& dest)`
- L336 _protected function_ `process(T& dest)`
- L343 _protected function_ `void process(char& dest)`
- L357 _protected function_ `void process(std::uint8_t& dest)`
- L363 _protected function_ `void process(std::int8_t& dest)`
- L370 _protected function_ `template<typename T, typename... Args> void process(Blob<T, Args...>& dest)`
- L383 _protected function_ `template<typename T, std::size_t N> void process(std::array<T, N>& dest)`
- L421 _protected function_ `template<typename T, typename... Args> void process(std::vector<T, Args...>& dest)`
- L461 _protected function_ `template<typename T, typename... Args> void process(DynArray<T, Args...>& dest)`
- L508 _protected function_ `template<typename T, typename... Args> void process(std::basic_string<T, Args...>& dest)`
- L532 _protected function_ `template<typename K, typename V> void process(std::pair<K, V>& dest)`
- L561 _protected function_ `template<typename K, typename V> void process(std::tuple<K, V>& dest)`
- L590 _private function_ `bool readChar(char* dest)`
- L598 _private function_ `bool expectChar(char expected)`
- L610 _private function_ `void skipWhiteSpace()`
- L614 _private function_ `void preStructInput()`
- L624 _private function_ `void postStructInput()`
- L632 _private function_ `void pushTransparency()`
- L636 _private function_ `bool popTransparency()`
- L650 _private member_ `CharInputStreamBuf<TStream> streamBuf;`
- L651 _private member_ `std::istream stream;`
- L652 _private member_ `SerializationState state;`

#### struct `terse::ExtendableJSONInputArchive::SerializationState`  
`struct SerializationState`  
_L643-647_
- L644 _public member_ `bool malformed;`
- L645 _public member_ `bool firstMember;`
- L646 _public member_ `bool transparent;`

#### class `terse::JSONInputArchive`  
`template<class TStream, typename TSize = std::uint32_t, typename TOffset = TSize> class JSONInputArchive : public ExtendableJSONInputArchive<JSONInputArchive<TStream, TSize, TOffset>, TStream, TSize, TOffset>`  
_L656-671_
- inherits: `ExtendableJSONInputArchive<JSONInputArchive<TStream,TSize,TOffset>,TStream,TSize,TOffset>`
- L658 _private typedef_ `using BaseArchive = ExtendableJSONInputArchive<JSONInputArchive, TStream, TSize, TOffset>;`
- L662 _public function_ `explicit JSONInputArchive(TStream* stream_) : BaseArchive`
- L668 _private function_ `template<typename T> void process(T&& dest)`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/archives/json/OutputArchive.h` (Public)


#### class `terse::ExtendableJSONOutputArchive`  
`template<class TExtender, class TStream, typename TSize, typename TOffset> class ExtendableJSONOutputArchive : public Archive<TExtender>`  
_L41-386_
- inherits: `Archive<TExtender>`
- L43 _private typedef_ `using BaseArchive = Archive<TExtender>;`
- L47 _public typedef_ `using SizeType = TSize;` — Given the possibility of both 32 and 64bit platforms, use a fixed width type during serialization
- L48 _public typedef_ `using OffsetType = TOffset;`
- L51 _public function_ `ExtendableJSONOutputArchive(TExtender* extender, TStream* stream_, std::uint32_t indentWidth) : BaseArchive`
- L58 _public function_ `bool isOk()`
- L62 _public function_ `void sync()`
- L66 _public function_ `std::size_t boundSize(std::size_t size)`
- L70 _public function_ `void label(const char* value)`
- L82 _protected function_ `template<typename T> void process(Transparent<T>&& source)`
- L87 _protected function_ `template<typename T> void process(Transparent<T>& source)`
- L92 _protected function_ `void process(Anchor<OffsetType>& )`
- L96 _protected function_ `void process(ArchiveOffset<OffsetType>& source)`
- L100 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy& )`
- L104 _protected function_ `void process(typename ArchiveOffset<OffsetType>::Proxy&& )`
- L108 _protected function_ `void process(ArchiveSize<SizeType, OffsetType>& source)`
- L112 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy& )`
- L116 _protected function_ `void process(typename ArchiveSize<SizeType, OffsetType>::Proxy&& )`
- L121 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_member<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L126 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_member<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L138 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L143 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_member<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L155 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_function<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L160 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_save_function<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L172 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>&& source)`
- L177 _protected function_ `template<typename T, typename V> typename std::enable_if<traits::has_versioned_serialize_function<T, V>::value, void>::type process(Versioned<T, V>& source)`
- L193 _protected function_ `process(Versioned<T, V>&& dest)`
- L202 _protected function_ `process(Versioned<T, V>& dest)`
- L209 _protected function_ `template<typename T> typename std::enable_if<traits::has_save_member<T>::value, void>::type process(const T& source)`
- L221 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_member<T>::value, void>::type process(const T& source)`
- L233 _protected function_ `template<typename T> typename std::enable_if<traits::has_save_function<T>::value, void>::type process(const T& source)`
- L245 _protected function_ `template<typename T> typename std::enable_if<traits::has_serialize_function<T>::value, void>::type process(const T& source)`
- L260 _protected function_ `process(const T& source)`
- L264 _protected function_ `void process(char source)`
- L268 _protected function_ `void process(std::uint8_t source)`
- L272 _protected function_ `void process(std::int8_t source)`
- L277 _protected function_ `template<typename T, typename... Args> void process(const Blob<T, Args...>& source)`
- L288 _protected function_ `template<typename T, std::size_t N> void process(const std::array<T, N>& source)`
- L293 _protected function_ `template<typename T, typename... Args> void process(const std::vector<T, Args...>& source)`
- L298 _protected function_ `template<typename T, typename... Args> void process(const DynArray<T, Args...>& source)`
- L303 _protected function_ `template<typename T, typename... Args> void process(const std::basic_string<T, Args...>& source)`
- L308 _protected function_ `template<typename K, typename V> void process(const std::pair<K, V>& source)`
- L317 _protected function_ `template<typename K, typename V> void process(const std::tuple<K, V>& source)`
- L326 _protected function_ `template<class TContainer> void processElements(const TContainer& source)`
- L343 _private function_ `void indent()`
- L347 _private function_ `void preStructOutput()`
- L356 _private function_ `void postStructOutput()`
- L364 _private function_ `void pushTransparency()`
- L368 _private function_ `bool popTransparency()`
- L383 _private member_ `CharOutputStreamBuf<TStream> streamBuf;`
- L384 _private member_ `std::ostream stream;`
- L385 _private member_ `SerializationState state;`

#### struct `terse::ExtendableJSONOutputArchive::SerializationState`  
`struct SerializationState`  
_L375-380_
- L376 _public member_ `std::uint32_t indentWidth;`
- L377 _public member_ `std::uint32_t indentLevel;`
- L378 _public member_ `bool firstMember;`
- L379 _public member_ `bool transparent;`

#### class `terse::JSONOutputArchive`  
`template<class TStream, typename TSize = std::uint32_t, typename TOffset = TSize> class JSONOutputArchive : public ExtendableJSONOutputArchive<JSONOutputArchive<TStream, TSize, TOffset>, TStream, TSize, TOffset>`  
_L389-405_
- inherits: `ExtendableJSONOutputArchive<JSONOutputArchive<TStream,TSize,TOffset>,TStream,TSize,TOffset>`
- L392 _public typedef_ `using BaseArchive = ExtendableJSONOutputArchive<JSONOutputArchive, TStream, TSize, TOffset>;`
- L396 _public function_ `JSONOutputArchive(TStream* stream_, std::uint32_t indentWidth_) : BaseArchive`
- L402 _private function_ `template<typename T> void process(T&& dest)`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/Anchor.h` (Public)


#### struct `terse::Anchor`  
`template<typename TOffset> struct Anchor`  
_L22-68_
- desc: Anchor is a virtual, utility type only (meaning it does not write or read any data from the stream) It only captures the current position in the stream (into an in-memory variable only), at the time when the anchor is encountered in the serialization process. An Anchor can be associated with an ArchiveSize type, and ArchiveSize will use it as the base offset from which to calculate its own size.
- L23 _public typedef_ `using ValueType = TOffset;`
- L24 _public typedef_ `using OnMoveCallback = void (*)(Anchor*, void*);`
- L26 _public member_ `mutable ValueType value;`
- L28 _public member_ `OnMoveCallback onMoveCallback;`
- L29 _public member_ `void* onMoveCallbackData;`
- L31 _public function_ `Anchor() : value`
- L37 _public prototype_ `~Anchor() = default;`
- L39 _public prototype_ `Anchor(const Anchor&) = delete;`
- L40 _public prototype_ `Anchor& operator=(const Anchor&) = delete;`
- L42 _public function_ `Anchor(Anchor&& rhs) : value`
- L54 _public function_ `Anchor& operator=(Anchor&& rhs)`
- L64 _public function_ `void onMove(OnMoveCallback callback, void* data)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/ArchiveOffset.h` (Public)


#### struct `terse::ArchiveOffset`  
`template<typename TOffset> struct ArchiveOffset`  
_L28-128_
- desc: ArchiveOffset is a type that stores an absolute stream offset (both in-memory and writes that value into the stream as well). It has an accompanying Proxy type, which is a virtual, utility type, and they work together to achieve the function of ArchiveOffset. When ArchiveOffset is encountered during the serialization process, at first an empty offset (zero) value will be written into the stream and the position of that offset value will be captured in an in-memory variable. Later, when its associated ArchiveOffset<T>::Proxy is encountered, the current stream position will be captured, and it will update the in-memory value of its ArchiveOffset with it. Then, it will seek the stream to the earlier captured position of the offset value (where zeros were written initially), and it will write the offset value captured by the proxy into the stream. Lastly, it will seek back to the position of the stream before the proxy was encountered, and resume serialization.
- L29 _public typedef_ `using ValueType = TOffset;`
- L87 _public member_ `mutable std::size_t position;` — The position of the marker itself in the stream (this is a runtime-only value which is not written to the file, needed only for the serializer to know where to seek within the stream when the marker's actual value needs to be written)
- L90 _public member_ `mutable ValueType value;` — The position in the stream where the marker wants to point (this is the actual value that is written to the file)
- L92 _public member_ `Proxy* proxy;` — When offset is moved, it's associated proxy must be updated about the new address
- L94 _public function_ `ArchiveOffset() : position`
- L100 _public prototype_ `~ArchiveOffset() = default;`
- L102 _public prototype_ `ArchiveOffset(const ArchiveOffset&) = delete;`
- L103 _public prototype_ `ArchiveOffset& operator=(const ArchiveOffset&) = delete;`
- L105 _public function_ `ArchiveOffset(ArchiveOffset&& rhs) : position`
- L118 _public function_ `ArchiveOffset& operator=(ArchiveOffset&& rhs)`

#### struct `terse::ArchiveOffset::Proxy`  
`struct Proxy`  
_L31-82_
- L32 _public member_ `ArchiveOffset* target;`
- L34 _public function_ `explicit Proxy(ArchiveOffset& ptr) : target`
- L48 _public function_ `~Proxy()`
- L54 _public prototype_ `Proxy(const Proxy&) = delete;`
- L55 _public prototype_ `Proxy& operator=(const Proxy&) = delete;`
- L57 _public function_ `Proxy(Proxy&& rhs) : target`
- L70 _public function_ `Proxy& operator=(Proxy&& rhs)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace terse`
- L131 _function_ `template<typename TOffset> typename ArchiveOffset<TOffset>::Proxy proxy(ArchiveOffset<TOffset>& offset)` (scope `terse`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/ArchiveSize.h` (Public)


#### struct `terse::ArchiveSize`  
`template<typename TSize, typename TOffset> struct ArchiveSize`  
_L34-152_
- desc: ArchiveSize is a type that stores an arbitrary size value (both in-memory and writes that value into the stream as well). It has two accompanying types: Proxy and Anchor, which are both virtual, utility types, and they work together to achieve the function of ArchiveSize. When ArchiveSize is encountered during the serialization process, at first an empty size (zero) value will be written into the stream and the position of that size value will be captured in an in-memory variable. Later, when its associated Anchor is encountered, it will capture the current stream position as the base (start) offset, from which the size is going to be computed (size is relative to some base offset). Lastly, when its ArchiveSize<T>::Proxy is encountered, the current stream position will be captured, and the earlier captured anchor base offset will be subtracted from it (resulting in the size value - the size between Anchor offset and Proxy offset). With the size value computed, it will update the in-memory value stored in ArchiveSize with it. Then, it will seek the stream to the earlier captured position of the size value (where zeros were written initially), and it will write the size value into the stream at that position. With all that done, it will seek back to the position of the stream before the proxy was encountered, and resume serialization.
- L35 _public typedef_ `using ValueType = TSize;`
- L112 _public member_ `mutable std::size_t position;` — The position of the marker itself in the stream (this is a runtime-only value which is not written to the file, needed only for the serializer to know where to seek within the stream when the marker's actual value needs to be written)
- L114 _public member_ `mutable ValueType value;` — The size value itself (what is written to the file)
- L116 _public member_ `Proxy* proxy;` — When size is moved, it's associated proxy must be updated about the new address
- L118 _public function_ `ArchiveSize() : position`
- L124 _public prototype_ `~ArchiveSize() = default;`
- L126 _public prototype_ `ArchiveSize(const ArchiveSize&) = delete;`
- L127 _public prototype_ `ArchiveSize& operator=(const ArchiveSize&) = delete;`
- L129 _public function_ `ArchiveSize(ArchiveSize&& rhs) : position`
- L142 _public function_ `ArchiveSize& operator=(ArchiveSize&& rhs)`

#### struct `terse::ArchiveSize::Proxy`  
`struct Proxy`  
_L37-107_
- L38 _public member_ `ArchiveSize* target;`
- L39 _public member_ `Anchor<TOffset>* base;`
- L41 _public function_ `Proxy(ArchiveSize& size, Anchor<TOffset>& offset) : target`
- L57 _public function_ `~Proxy()`
- L66 _public prototype_ `Proxy(const Proxy&) = delete;`
- L67 _public prototype_ `Proxy& operator=(const Proxy&) = delete;`
- L69 _public function_ `Proxy(Proxy&& rhs) : target`
- L85 _public function_ `Proxy& operator=(Proxy&& rhs)`
- L101 _private function_ `static void onBaseMoved(Anchor<TOffset>* anchor, void* data)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace terse`
- L155 _function_ `template<typename TSize, typename TOffset> typename ArchiveSize<TSize, TOffset>::Proxy proxy(ArchiveSize<TSize, TOffset>& size, Anchor<TOffset>& base)` (scope `terse`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/Blob.h` (Public)


#### class `terse::Blob`  
`template<typename T, typename TAllocator> class Blob`  
_L15-55_
- desc: Blob is a wrapper type around a byte-array essentially, and is used to serialize binary blobs, whose size is predefined by another entity (e.g. an ArchiveSize object). During serialization, the amount of bytes either written to or read from the stream will be controlled by the user (by setting the size on the blob type through the setSize member function). For text-based serializers, binary blobs are Base64 encoded/decoded.
- L19 _public typedef_ `using value_type = T;`
- L20 _public typedef_ `using allocator_type = TAllocator;`
- L23 _public prototype_ `Blob() = default;`
- L25 _public function_ `explicit Blob(const allocator_type& alloc) : bytes`
- L29 _public function_ `Blob(std::size_t size, const allocator_type& alloc) : bytes`
- L33 _public function_ `allocator_type get_allocator() const noexcept`
- L37 _public function_ `value_type* data()`
- L41 _public function_ `const value_type* data() const`
- L45 _public function_ `std::size_t size() const`
- L49 _public function_ `void setSize(std::size_t newSize)`
- L54 _private member_ `DynArray<value_type, allocator_type> bytes;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/CharInputStreamBuf.h` (Public)


#### class `terse::CharInputStreamBuf`  
`template<class TStream, std::size_t BufferSize = 4096ul> class CharInputStreamBuf : public std::streambuf`  
_L18-96_
- inherits: `std::streambuf`
- L20 _public typedef_ `using PosType = std::streambuf::pos_type;`
- L21 _public typedef_ `using OffType = std::streambuf::off_type;`
- L22 _public typedef_ `using CharType = std::streambuf::char_type;`
- L23 _public typedef_ `using IntType = std::streambuf::int_type;`
- L24 _public typedef_ `using TraitsType = std::streambuf::traits_type;`
- L27 _public function_ `explicit CharInputStreamBuf(TStream* stream_) : stream`
- L34 _public function_ `std::streamsize xsgetn(CharType* destination, std::streamsize size) override`
- L63 _public function_ `IntType underflow() override`
- L89 _public function_ `std::streamsize showmanyc() override`
- L94 _private member_ `TStream* stream;`
- L95 _private member_ `std::array<char, BufferSize> buffer;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/CharOutputStreamBuf.h` (Public)


#### class `terse::CharOutputStreamBuf`  
`template<class TStream, std::size_t BufferSize = 4096ul> class CharOutputStreamBuf : public std::streambuf`  
_L18-84_
- inherits: `std::streambuf`
- L20 _public typedef_ `using PosType = std::streambuf::pos_type;`
- L21 _public typedef_ `using OffType = std::streambuf::off_type;`
- L22 _public typedef_ `using CharType = std::streambuf::char_type;`
- L23 _public typedef_ `using IntType = std::streambuf::int_type;`
- L24 _public typedef_ `using TraitsType = std::streambuf::traits_type;`
- L27 _public function_ `explicit CharOutputStreamBuf(TStream* stream_) : stream`
- L33 _public function_ `~CharOutputStreamBuf()`
- L37 _public function_ `std::streamsize xsputn(const CharType* source, std::streamsize size) override`
- L58 _public function_ `IntType overflow(IntType value) override`
- L70 _public function_ `IntType sync() override`
- L82 _private member_ `TStream* stream;`
- L83 _private member_ `std::array<char, BufferSize> buffer;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/DynArray.h` (Public)


#### class `terse::DynArray`  
`template<typename T, class TAllocator> class DynArray`  
_L30-235_
- desc: @brief Resizable array-like abstraction for trivial-types only.
- L34 _public typedef_ `using value_type = T;`
- L35 _public typedef_ `using allocator_type = TAllocator;`
- L38 _private typedef_ `using pointer_type = std::unique_ptr<value_type, std::function<void(value_type*)>>;`
- L41 _public function_ `explicit DynArray(const allocator_type& allocator) : alloc`
- L47 _public function_ `DynArray() : DynArray`
- L51 _public function_ `DynArray(std::size_t size, const allocator_type& allocator = allocator_type{}) : alloc`
- L57 _public function_ `DynArray(std::size_t size, const value_type& value, const allocator_type& allocator = allocator_type{}) : DynArray`
- L63 _public function_ `DynArray(const value_type* source, std::size_t size, const allocator_type& allocator = allocator_type{}) : DynArray`
- L72 _public function_ `template<typename TIterator> DynArray(TIterator start, TIterator end, const allocator_type& allocator = allocator_type{}) : DynArray`
- L88 _public prototype_ `~DynArray() = default;`
- L90 _public function_ `DynArray(const DynArray& rhs) : DynArray`
- L97 _public function_ `DynArray& operator=(const DynArray& rhs)`
- L105 _public function_ `DynArray(DynArray&& rhs) noexcept : alloc`
- L115 _public function_ `DynArray& operator=(DynArray&& rhs) noexcept`
- L122 _public function_ `allocator_type get_allocator() const noexcept`
- L126 _public function_ `void clear()`
- L131 _public function_ `value_type* data()`
- L135 _public function_ `const value_type* data() const`
- L139 _public function_ `std::size_t size() const`
- L143 _public function_ `bool empty() const`
- L147 _public function_ `value_type& operator[](std::size_t index)`
- L152 _public function_ `const value_type& operator[](std::size_t index) const`
- L157 _public function_ `value_type* begin()`
- L161 _public function_ `value_type* end()`
- L165 _public function_ `const value_type* cbegin() const`
- L169 _public function_ `const value_type* cend() const`
- L173 _public function_ `const value_type* begin() const`
- L177 _public function_ `const value_type* end() const`
- L181 _public function_ `void resize(std::size_t size, const value_type& value)`
- L194 _public function_ `void resize(std::size_t size)`
- L198 _public function_ `void resize_uninitialized(std::size_t size)`
- L211 _public function_ `template<typename TIterator> void assign(TIterator start, TIterator end)`
- L227 _private function_ `static pointer_type create(std::size_t size, allocator_type alloc)`
- L232 _private member_ `allocator_type alloc;`
- L233 _private member_ `std::size_t sz;`
- L234 _private member_ `pointer_type ptr;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace terse`
- L183 _function_ `pointer_type old` (scope `terse::DynArray::resize`)
- L200 _function_ `pointer_type old` (scope `terse::DynArray::resize_uninitialized`)
- L228 _function_ `return pointer_type` (scope `terse::DynArray::create`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/Transparent.h` (Public)


#### struct `terse::Transparent`  
`template<typename T> struct Transparent`  
_L14-17_
- desc: Textual serialization (currently JSON only) generates a pair of braces (`{}`) around every type that has a load, save or serialize member or free function, capable of serializing the type in question. In some cases, with lots of nested structures, for a simpler textual representation, some of these layers of abstractions might be preferable to be ignored. The Transparent<T> wrapper type is used for exactly that purpose. By wrapping any member from within a serializer function, that member will be treated as transparent, thus avoiding the generation of a pair of braces for it.
- L15 _public typedef_ `using WrappedType = T;`
- L16 _public member_ `WrappedType& data;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace terse`
- L20 _function_ `template<typename T> Transparent<T> transparent(T& data)` (scope `terse`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/types/Versioned.h` (Public)


#### struct `terse::Version`  
`template<std::uint64_t V> struct Version`  
_L15-19_
- desc: Convenience type for users to define version tags (Version<1>, Version<2>, ...), but it's usage is not mandatory, the user can define custom version tags on it's own, e.g.: struct v1 {}; struct v2 {}; both being also valid version tags, that may be utilized with Terse.
- L16 _public function_ `static constexpr std::uint64_t value()`

#### struct `terse::Versioned`  
`template<typename T, typename V> struct Versioned`  
_L25-29_
- desc: This is a wrapper type that is able to alter the serialization behavior, as in, it bundles a serializable object together with a version tag, and dispatches to different serialization functions, based on the bundled version tag.
- L26 _public typedef_ `using WrappedType = T;`
- L27 _public typedef_ `using TypeVersion = V;`
- L28 _public member_ `WrappedType& data;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace terse`
- L32 _function_ `template<typename T, typename V> Versioned<T, V> versioned(T& dest, V )` (scope `terse`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/utils/Base64.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace terse`
- L17 _variable_ `static const char* alphabet = "AB` (scope `terse`)
- L19 _function_ `constexpr std::size_t base64encode(std::size_t size)` (scope `terse`)
- L24 _function_ `inline std::size_t base64encode(char* destination, const char* source, std::size_t size)` (scope `terse`) — destination should be of length ((4 * size / 3) + 3) & ~3
- L52 _function_ `constexpr std::size_t base64decode(std::size_t size)` (scope `terse`)
- L57 _function_ `inline std::size_t base64decode(char* destination, const char* source, std::size_t size)` (scope `terse`) — destination should be of length (size / 4) * 3

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/utils/ByteSwap.h` (Public)


#### struct `terse::traits::uint_of_size`  
`template<std::size_t size> struct uint_of_size`  
_L28-35_
- L29 _public typedef_ `using type = typename std::conditional< (size == 1ul), std::uint8_t, typename std::conditional<(size == 2ul), std::uint16_t, typename std::conditional<(size <= 4ul), std::uint32_t, std::uint64_t>::type>::type>::type;`

#### struct `terse::impl::block128`  
`struct block128`  
_L41-50_
- L43 _public function_ `static constexpr std::size_t alignment()`

#### enum `terse::Endianness`  
`enum class Endianness`  
_L54-58_
- L55 _public enumerator_ `Little`
- L56 _public enumerator_ `Big`
- L57 _public enumerator_ `Network = Big`

#### struct `terse::ByteSwapper`  
`template<> struct ByteSwapper<Endianness::Little>`  
_L64-99_
- L67 _public function_ `template<typename T> static void swap(T& value)`
- L84 _public function_ `template<typename T> static void swap(T* values)`

#### struct `terse::ByteSwapper`  
`template<> struct ByteSwapper<Endianness::Big>`  
_L102-137_
- L67 _public function_ `template<typename T> static void swap(T& value)`
- L84 _public function_ `template<typename T> static void swap(T* values)`

#### Free symbols / members of external scopes

- L6 _macro_ `#define ENABLE_SSE_BSWAP`
- L23 _namespace_ `namespace terse`
- L25 _namespace_ `namespace traits` (scope `terse`)
- L39 _namespace_ `namespace impl` (scope `terse`)
- L107 _typedef_ `using UIntType = typename traits::uint_of_size<sizeof(T)>::type;` (scope `terse::ByteSwapper::swap`)
- L140 _typedef_ `template<Endianness EByteOrder> using SwapTo = ByteSwapper<EByteOrder>;` (scope `terse`)
- L143 _typedef_ `template<Endianness EByteOrder> using SwapFrom = ByteSwapper<EByteOrder>;` (scope `terse`)
- L146 _function_ `template<typename T> inline void networkToHost(T& value)` (scope `terse`)
- L151 _function_ `template<typename T> inline void networkToHost128(T* values)` (scope `terse`)
- L156 _function_ `template<typename T> inline void hostToNetwork(T& value)` (scope `terse`)
- L161 _function_ `template<typename T> inline void hostToNetwork128(T* values)` (scope `terse`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/utils/Endianness.h` (Public)


#### Free symbols / members of external scopes

- L14 _macro_ `#define OVERRIDDEN_ENDIAN_H`
- L19 _macro_ `#define USE_ENDIAN_H`
- L21 _macro_ `#define USE_MACHINE_ENDIAN_H`
- L23 _macro_ `#define USE_SYS_ENDIAN_H`
- L25 _macro_ `#define USE_SYS_ISA_DEFS_H`
- L27 _macro_ `#define USE_SYS_PARAM_H`
- L53 _macro_ `#define TARGET_LITTLE_ENDIAN` — defined(_M_ARM)  MSVC  || defined(_M_ARM64)  MSVC
- L61 _macro_ `#define TARGET_BIG_ENDIAN` — defined(__MIPSEB__)  GCC,Clang
- L71 _macro_ `#define bswap16(x) __builtin_bswap16((x))`
- L72 _macro_ `#define bswap32(x) __builtin_bswap32((x))`
- L73 _macro_ `#define bswap64(x) __builtin_bswap64((x))`
- L76 _macro_ `#define bswap16(x) bswap_16((x))`
- L77 _macro_ `#define bswap32(x) bswap_32((x))`
- L78 _macro_ `#define bswap64(x) bswap_64((x))`
- L81 _macro_ `#define bswap16(x) _byteswap_ushort((x))`
- L82 _macro_ `#define bswap32(x) _byteswap_ulong((x))`
- L83 _macro_ `#define bswap64(x) _byteswap_uint64((x))`
- L86 _macro_ `#define bswap16(x) OSSwapInt16((x))`
- L87 _macro_ `#define bswap32(x) OSSwapInt32((x))`
- L88 _macro_ `#define bswap64(x) OSSwapInt64((x))`
- L93 _macro_ `#define bswap16(x) swap16((x))`
- L94 _macro_ `#define bswap32(x) swap32((x))`
- L95 _macro_ `#define bswap64(x) swap64((x))`
- L98 _macro_ `#define bswap16(x) BSWAP_16((x))`
- L99 _macro_ `#define bswap32(x) BSWAP_32((x))`
- L100 _macro_ `#define bswap64(x) BSWAP_64((x))`
- L102 _function_ `static inline std::uint16_t bswap16(std::uint16_t x)`
- L106 _function_ `static inline std::uint32_t bswap32(std::uint32_t x)`
- L111 _function_ `static inline std::uint64_t bswap64(std::uint64_t x)`
- L122 _function_ `static inline void bswap16x8(std::uint16_t* source)`
- L128 _function_ `static inline void bswap32x4(std::uint32_t* source)`
- L134 _function_ `static inline void bswap64x2(std::uint64_t* source)`
- L170 _macro_ `#define ntoh8(x) (x)`
- L171 _macro_ `#define hton8(x) (x)`
- L172 _macro_ `#define ntoh16(x) bswap16((x))`
- L173 _macro_ `#define hton16(x) bswap16((x))`
- L174 _macro_ `#define ntoh32(x) bswap32((x))`
- L175 _macro_ `#define hton32(x) bswap32((x))`
- L176 _macro_ `#define ntoh64(x) bswap64((x))`
- L177 _macro_ `#define hton64(x) bswap64((x))`
- L179 _macro_ `#define ntoh8x16(x) (x)` — Vectorized swap
- L180 _macro_ `#define hton8x16(x) (x)`
- L181 _macro_ `#define ntoh16x8(x) bswap16x8((x))`
- L182 _macro_ `#define hton16x8(x) bswap16x8((x))`
- L183 _macro_ `#define ntoh32x4(x) bswap32x4((x))`
- L184 _macro_ `#define hton32x4(x) bswap32x4((x))`
- L185 _macro_ `#define ntoh64x2(x) bswap64x2((x))`
- L186 _macro_ `#define hton64x2(x) bswap64x2((x))`
- L190 _macro_ `#define ntoh16(x) (x)`
- L191 _macro_ `#define hton16(x) (x)`
- L192 _macro_ `#define ntoh32(x) (x)`
- L193 _macro_ `#define hton32(x) (x)`
- L194 _macro_ `#define ntoh64(x) (x)`
- L195 _macro_ `#define hton64(x) (x)`
- L199 _macro_ `#define ntoh16x8(x) (x)`
- L200 _macro_ `#define hton16x8(x) (x)`
- L201 _macro_ `#define ntoh32x4(x) (x)`
- L202 _macro_ `#define hton32x4(x) (x)`
- L203 _macro_ `#define ntoh64x2(x) (x)`
- L204 _macro_ `#define hton64x2(x) (x)`
- L216 _function_ `inline std::uint8_t ntoh(std::uint8_t x)`
- L220 _function_ `inline std::uint16_t ntoh(std::uint16_t x)`
- L224 _function_ `inline std::uint32_t ntoh(std::uint32_t x)`
- L228 _function_ `inline std::uint64_t ntoh(std::uint64_t x)`
- L232 _function_ `inline std::uint8_t hton(std::uint8_t x)`
- L236 _function_ `inline std::uint16_t hton(std::uint16_t x)`
- L240 _function_ `inline std::uint32_t hton(std::uint32_t x)`
- L244 _function_ `inline std::uint64_t hton(std::uint64_t x)`
- L250 _function_ `inline void ntoh(std::uint8_t* x)`
- L254 _function_ `inline void ntoh(std::uint16_t* x)`
- L258 _function_ `inline void ntoh(std::uint32_t* x)`
- L262 _function_ `inline void ntoh(std::uint64_t* x)`
- L266 _function_ `inline void hton(std::uint8_t* x)`
- L270 _function_ `inline void hton(std::uint16_t* x)`
- L274 _function_ `inline void hton(std::uint32_t* x)`
- L278 _function_ `inline void hton(std::uint64_t* x)`
- L284 _function_ `inline std::uint8_t bswap(std::uint8_t x)`
- L289 _function_ `inline std::uint16_t bswap(std::uint16_t x)`
- L293 _function_ `inline std::uint32_t bswap(std::uint32_t x)`
- L297 _function_ `inline std::uint64_t bswap(std::uint64_t x)`
- L301 _function_ `inline void bswap(std::uint8_t* x)`
- L306 _function_ `inline void bswap(std::uint16_t* x)`
- L310 _function_ `inline void bswap(std::uint32_t* x)`
- L314 _function_ `inline void bswap(std::uint64_t* x)`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/utils/VirtualSerializerProxy.h` (Public)


#### class `terse::VirtualSerializerProxy`  
`template<class Serializable> class VirtualSerializerProxy`  
_L8-26_
- L10 _public function_ `explicit VirtualSerializerProxy(Serializable* instance_) : instance`
- L15 _public function_ `template<class TArchive> void load(TArchive& archive)`
- L20 _public function_ `template<class TArchive> void save(TArchive& archive)`
- L25 _private member_ `Serializable* instance;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace terse`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/terse/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define TERSE_MAJOR_VERSION 3`
- L6 _macro_ `#define TERSE_MINOR_VERSION 1`
- L7 _macro_ `#define TERSE_PATCH_VERSION 15`
- L8 _macro_ `#define TERSE_VERSION_STRING "3.1.15"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/AVX.h` (Public)


#### struct `trimd::avx::F256`  
`struct F256`  
_L14-177_
- L15 _public typedef_ `using value_type = float;`
- L17 _public member_ `__m256 data;`
- L19 _public function_ `F256() : data`
- L23 _public function_ `explicit F256(__m256 value) : data`
- L27 _public function_ `explicit F256(float value) : F256`
- L31 _public function_ `F256(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8) : data`
- L35 _public function_ `static F256 fromAlignedSource(const float* source)`
- L39 _public function_ `static F256 fromUnalignedSource(const float* source)`
- L43 _public function_ `static F256 loadSingleValue(const float* source)`
- L49 _public prototype_ `static F256 fromAlignedSource(const std::uint16_t* source);`
- L50 _public prototype_ `static F256 fromUnalignedSource(const std::uint16_t* source);`
- L51 _public prototype_ `static F256 loadSingleValue(const std::uint16_t* source);`
- L55 _public function_ `template<typename T> static void prefetchT0(const T* source)`
- L67 _public function_ `template<typename T> static void prefetchT1(const T* source)`
- L79 _public function_ `template<typename T> static void prefetchT2(const T* source)`
- L91 _public function_ `template<typename T> static void prefetchNTA(const T* source)`
- L102 _public function_ `void alignedLoad(const float* source)`
- L106 _public function_ `void unalignedLoad(const float* source)`
- L110 _public function_ `void alignedStore(float* dest) const`
- L114 _public function_ `void unalignedStore(float* dest) const`
- L119 _public prototype_ `void alignedLoad(const std::uint16_t* source);`
- L120 _public prototype_ `void unalignedLoad(const std::uint16_t* source);`
- L121 _public prototype_ `void alignedStore(std::uint16_t* dest) const;`
- L122 _public prototype_ `void unalignedStore(std::uint16_t* dest) const;`
- L125 _public function_ `float sum() const`
- L135 _public function_ `F256& operator+=(const F256& rhs)`
- L140 _public function_ `F256& operator-=(const F256& rhs)`
- L145 _public function_ `F256& operator*=(const F256& rhs)`
- L150 _public function_ `F256& operator/=(const F256& rhs)`
- L155 _public function_ `F256& operator&=(const F256& rhs)`
- L160 _public function_ `F256& operator|=(const F256& rhs)`
- L165 _public function_ `F256& operator^=(const F256& rhs)`
- L170 _public function_ `static constexpr std::size_t size()`
- L174 _public function_ `static constexpr std::size_t alignment()`
- L181 _function_ `TRIMD_TARGET_F16C inline F256 F256::fromAlignedSource(const std::uint16_t* source)`
- L185 _function_ `TRIMD_TARGET_F16C inline F256 F256::fromUnalignedSource(const std::uint16_t* source)`
- L189 _function_ `TRIMD_TARGET_F16C inline F256 F256::loadSingleValue(const std::uint16_t* source)`
- L193 _function_ `TRIMD_TARGET_F16C inline void F256::alignedLoad(const std::uint16_t* source)`
- L197 _function_ `TRIMD_TARGET_F16C inline void F256::unalignedLoad(const std::uint16_t* source)`
- L201 _function_ `TRIMD_TARGET_F16C inline void F256::alignedStore(std::uint16_t* dest) const`
- L215 _function_ `TRIMD_TARGET_F16C inline void F256::unalignedStore(std::uint16_t* dest) const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace trimd`
- L12 _namespace_ `namespace avx` (scope `trimd`)
- L231 _function_ `inline F256 operator==(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L235 _function_ `inline F256 operator!=(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L239 _function_ `inline F256 operator<(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L243 _function_ `inline F256 operator<=(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L247 _function_ `inline F256 operator>(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L251 _function_ `inline F256 operator>=(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L255 _function_ `inline F256 operator+(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L259 _function_ `inline F256 operator-(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L263 _function_ `inline F256 operator*(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L267 _function_ `inline F256 operator/(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L271 _function_ `inline F256 operator&(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L275 _function_ `inline F256 operator|(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L279 _function_ `inline F256 operator^(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L283 _function_ `inline F256 operator~(const F256& rhs)` (scope `trimd::avx`)
- L289 _function_ `inline void transpose(F256& row0, F256& row1, F256& row2, F256& row3, F256& row4, F256& row5, F256& row6, F256& row7)` (scope `trimd::avx`)
- L316 _function_ `inline F256 abs(const F256& rhs)` (scope `trimd::avx`)
- L321 _function_ `inline F256 andnot(const F256& lhs, const F256& rhs)` (scope `trimd::avx`)
- L325 _function_ `inline F256 rsqrt(const F256& rhs)` (scope `trimd::avx`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/Fallback.h` (Public)


#### struct `trimd::fallback::T256`  
`template<typename T128> struct T256`  
_L19-159_
- L20 _public typedef_ `using value_type = typename T128::value_type;`
- L22 _public member_ `T128 data1;`
- L23 _public member_ `T128 data2;`
- L25 _public function_ `T256(const T128& d1, const T128& d2) : data1`
- L30 _public function_ `T256() : data1`
- L35 _public function_ `T256(value_type v1, value_type v2, value_type v3, value_type v4, value_type v5, value_type v6, value_type v7, value_type v8) : data1`
- L40 _public function_ `explicit T256(value_type value) : T256`
- L45 _public function_ `template<typename U> static T256 fromAlignedSource(const U* source)`
- L50 _public function_ `template<typename U> static T256 fromUnalignedSource(const U* source)`
- L55 _public function_ `template<typename U> static T256 loadSingleValue(const U* source)`
- L60 _public function_ `template<typename U> static void prefetchT0(const U* source)`
- L65 _public function_ `template<typename U> static void prefetchT1(const U* source)`
- L70 _public function_ `template<typename U> static void prefetchT2(const U* source)`
- L75 _public function_ `template<typename U> static void prefetchNTA(const U* source)`
- L80 _public function_ `template<typename U> void alignedLoad(const U* source)`
- L86 _public function_ `template<typename U> void unalignedLoad(const U* source)`
- L92 _public function_ `template<typename U> void alignedStore(U* dest) const`
- L98 _public function_ `template<typename U> void unalignedStore(U* dest) const`
- L103 _public function_ `value_type sum() const`
- L107 _public function_ `T256& operator+=(const T256& rhs)`
- L113 _public function_ `T256& operator-=(const T256& rhs)`
- L119 _public function_ `T256& operator*=(const T256& rhs)`
- L125 _public function_ `T256& operator/=(const T256& rhs)`
- L131 _public function_ `T256& operator&=(const T256& rhs)`
- L137 _public function_ `T256& operator|=(const T256& rhs)`
- L143 _public function_ `T256& operator^=(const T256& rhs)`
- L149 _public function_ `static constexpr std::size_t size()`
- L153 _public function_ `static constexpr std::size_t alignment()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace trimd`
- L16 _namespace_ `namespace fallback` (scope `trimd`)
- L162 _function_ `template<typename T128> inline T256<T128> operator==(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L167 _function_ `template<typename T128> inline T256<T128> operator!=(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L172 _function_ `template<typename T128> inline T256<T128> operator<(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L177 _function_ `template<typename T128> inline T256<T128> operator<=(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L182 _function_ `template<typename T128> inline T256<T128> operator>(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L187 _function_ `template<typename T128> inline T256<T128> operator>=(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L192 _function_ `template<typename T128> inline T256<T128> operator+(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L197 _function_ `template<typename T128> inline T256<T128> operator-(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L202 _function_ `template<typename T128> inline T256<T128> operator*(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L207 _function_ `template<typename T128> inline T256<T128> operator/(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L212 _function_ `template<typename T128> inline T256<T128> operator&(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L217 _function_ `template<typename T128> inline T256<T128> operator|(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L222 _function_ `template<typename T128> inline T256<T128> operator^(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L227 _function_ `template<typename T128> inline T256<T128> operator~(const T256<T128>& rhs)` (scope `trimd::fallback`)
- L232 _function_ `template<typename T128> inline void transpose(T256<T128>& row0, T256<T128>& row1, T256<T128>& row2, T256<T128>& row3, T256<T128>& row4, T256<T128>& row5, T256<T128>& row6, T256<T128>& row7)` (scope `trimd::fallback`)
- L251 _function_ `template<typename T128> inline T256<T128> abs(const T256<T128>& rhs)` (scope `trimd::fallback`)
- L256 _function_ `template<typename T128> inline T256<T128> andnot(const T256<T128>& lhs, const T256<T128>& rhs)` (scope `trimd::fallback`)
- L261 _function_ `template<typename T128> inline T256<T128> rsqrt(const T256<T128>& rhs)` (scope `trimd::fallback`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/Macros.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define FORCE_INLINE __forceinline`
- L9 _macro_ `#define FORCE_INLINE inline __attribute__((always_inline))`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/NEON.h` (Public)


#### struct `trimd::neon::F128`  
`struct F128`  
_L17-155_
- L18 _public typedef_ `using value_type = float;`
- L20 _public member_ `float32x4_t data;`
- L22 _public function_ `F128() : data`
- L26 _public function_ `explicit F128(float32x4_t value) : data`
- L30 _public function_ `explicit F128(float value) : F128`
- L34 _public function_ `F128(float v1, float v2, float v3, float v4)`
- L39 _public function_ `static F128 fromAlignedSource(const float* source)`
- L43 _public function_ `static F128 fromUnalignedSource(const float* source)`
- L47 _public function_ `static F128 loadSingleValue(const float* source)`
- L52 _public prototype_ `static F128 fromAlignedSource(const std::uint16_t* source);`
- L53 _public prototype_ `static F128 fromUnalignedSource(const std::uint16_t* source);`
- L54 _public prototype_ `static F128 loadSingleValue(const std::uint16_t* source);`
- L58 _public function_ `template<typename T> static void prefetchT0(const T* source)`
- L63 _public function_ `template<typename T> static void prefetchT1(const T* source)`
- L68 _public function_ `template<typename T> static void prefetchT2(const T* source)`
- L73 _public function_ `template<typename T> static void prefetchNTA(const T* source)`
- L77 _public function_ `void alignedLoad(const float* source)`
- L81 _public function_ `void unalignedLoad(const float* source)`
- L85 _public function_ `void alignedStore(float* dest) const`
- L89 _public function_ `void unalignedStore(float* dest) const`
- L94 _public prototype_ `void alignedLoad(const std::uint16_t* source);`
- L95 _public prototype_ `void unalignedLoad(const std::uint16_t* source);`
- L96 _public prototype_ `void alignedStore(std::uint16_t* dest) const;`
- L97 _public prototype_ `void unalignedStore(std::uint16_t* dest) const;`
- L100 _public function_ `float sum() const`
- L105 _public function_ `F128& operator+=(const F128& rhs)`
- L110 _public function_ `F128& operator-=(const F128& rhs)`
- L115 _public function_ `F128& operator*=(const F128& rhs)`
- L120 _public function_ `F128& operator/=(const F128& rhs)`
- L133 _public function_ `F128& operator&=(const F128& rhs)`
- L138 _public function_ `F128& operator|=(const F128& rhs)`
- L143 _public function_ `F128& operator^=(const F128& rhs)`
- L148 _public function_ `static constexpr std::size_t size()`
- L152 _public function_ `static constexpr std::size_t alignment()`
- L159 _function_ `TRIMD_TARGET_NEON_FP16 inline F128 F128::fromAlignedSource(const std::uint16_t* source)`
- L163 _function_ `TRIMD_TARGET_NEON_FP16 inline F128 F128::fromUnalignedSource(const std::uint16_t* source)`
- L167 _function_ `TRIMD_TARGET_NEON_FP16 inline F128 F128::loadSingleValue(const std::uint16_t* source)`
- L173 _function_ `TRIMD_TARGET_NEON_FP16 inline void F128::alignedLoad(const std::uint16_t* source)`
- L177 _function_ `TRIMD_TARGET_NEON_FP16 inline void F128::unalignedLoad(const std::uint16_t* source)`
- L181 _function_ `TRIMD_TARGET_NEON_FP16 inline void F128::alignedStore(std::uint16_t* dest) const`
- L185 _function_ `TRIMD_TARGET_NEON_FP16 inline void F128::unalignedStore(std::uint16_t* dest) const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace trimd`
- L15 _namespace_ `namespace neon` (scope `trimd`)
- L191 _function_ `inline F128 operator==(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L195 _function_ `inline F128 operator!=(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L199 _function_ `inline F128 operator<(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L203 _function_ `inline F128 operator<=(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L207 _function_ `inline F128 operator>(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L211 _function_ `inline F128 operator>=(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L215 _function_ `inline F128 operator+(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L219 _function_ `inline F128 operator-(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L223 _function_ `inline F128 operator*(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L227 _function_ `inline F128 operator/(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L231 _function_ `inline F128 operator&(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L235 _function_ `inline F128 operator|(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L239 _function_ `inline F128 operator^(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L243 _function_ `inline F128 operator~(const F128& rhs)` (scope `trimd::neon`)
- L247 _function_ `inline void transpose(F128& row0, F128& row1, F128& row2, F128& row3)` (scope `trimd::neon`)
- L263 _function_ `inline F128 abs(const F128& rhs)` (scope `trimd::neon`)
- L267 _function_ `inline F128 andnot(const F128& lhs, const F128& rhs)` (scope `trimd::neon`)
- L271 _function_ `inline F128 rsqrt(const F128& rhs)` (scope `trimd::neon`)
- L285 _typedef_ `using F256 = fallback::T256<F128>;` (scope `trimd::neon`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/Platform.h` (Public)


#### struct `trimd::CPUFeatures`  
`struct CPUFeatures`  
_L31-44_
- L33 _public member_ `bool NEON;` — ARM
- L34 _public member_ `bool FP16;`
- L36 _public member_ `bool SSE;` — X86
- L37 _public member_ `bool SSE2;`
- L38 _public member_ `bool SSE3;`
- L39 _public member_ `bool SSSE3;`
- L40 _public member_ `bool SSE41;`
- L41 _public member_ `bool SSE42;`
- L42 _public member_ `bool AVX;`
- L43 _public member_ `bool F16C;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define TRIMD_PLATFORM_ARM 1`
- L10 _macro_ `#define TRIMD_PLATFORM_X86 1`
- L15 _macro_ `#define TRIMD_TARGET_F16C __attribute__((target("f16c")))`
- L17 _macro_ `#define TRIMD_TARGET_F16C`
- L23 _macro_ `#define TRIMD_TARGET_NEON_FP16 __attribute__((target("+fp16")))`
- L25 _macro_ `#define TRIMD_TARGET_NEON_FP16`
- L29 _namespace_ `namespace trimd`
- L68 _namespace_ `namespace trimd`
- L72 _function_ `static void cpuidex(int info[4], int functionid, int subfunctionid)` (scope `trimd`)
- L84 _function_ `inline CPUFeatures getCPUFeatures()` (scope `trimd`)
- L102 _function_ `static bool getsysctlflag(const char* name)` (scope `trimd`)
- L117 _macro_ `#define PF_ARM_NEON_INSTRUCTIONS_AVAILABLE 19`
- L132 _macro_ `#define HWCAP_NEON (1 << 12)`
- L136 _macro_ `#define HWCAP_FPHP (1 << 22)`
- L140 _macro_ `#define HWCAP_ASIMDHP (1 << 23)`
- L145 _macro_ `#define HWCAP_ASIMD (1 << 1)`
- L149 _macro_ `#define HWCAP_FPHP (1 << 9)`
- L153 _macro_ `#define HWCAP_ASIMDHP (1 << 10)`
- L178 _namespace_ `namespace trimd`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/PlatformWindows.h` (Public)


#### Free symbols / members of external scopes

- L16 _macro_ `#define WIN32_LEAN_AND_MEAN`
- L17 _macro_ `#define NOGDICAPMASKS`
- L18 _macro_ `#define NOVIRTUALKEYCODES`
- L19 _macro_ `#define NOWINMESSAGES`
- L20 _macro_ `#define NOWINSTYLES`
- L21 _macro_ `#define NOSYSMETRICS`
- L22 _macro_ `#define NOMENUS`
- L23 _macro_ `#define NOICONS`
- L24 _macro_ `#define NOKEYSTATES`
- L25 _macro_ `#define NOSYSCOMMANDS`
- L26 _macro_ `#define NORASTEROPS`
- L27 _macro_ `#define NOSHOWWINDOW`
- L28 _macro_ `#define NOATOM`
- L29 _macro_ `#define NOCLIPBOARD`
- L30 _macro_ `#define NOCOLOR`
- L31 _macro_ `#define NOCTLMGR`
- L32 _macro_ `#define NODRAWTEXT`
- L33 _macro_ `#define NOGDI`
- L34 _macro_ `#define NOKERNEL`
- L35 _macro_ `#define NOUSER`
- L36 _macro_ `#define NOMB`
- L37 _macro_ `#define NOMEMMGR`
- L38 _macro_ `#define NOMETAFILE`
- L39 _macro_ `#define NOMINMAX`
- L40 _macro_ `#define NOMSG`
- L41 _macro_ `#define NOOPENFILE`
- L42 _macro_ `#define NOSCROLL`
- L43 _macro_ `#define NOSERVICE`
- L44 _macro_ `#define NOSOUND`
- L45 _macro_ `#define NOTEXTMETRIC`
- L46 _macro_ `#define NOWH`
- L47 _macro_ `#define NOWINOFFSETS`
- L48 _macro_ `#define NOCOMM`
- L49 _macro_ `#define NOKANJI`
- L50 _macro_ `#define NOHELP`
- L51 _macro_ `#define NOPROFILER`
- L52 _macro_ `#define NODEFERWINDOWPOS`
- L53 _macro_ `#define NOMCX`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/Polyfill.h` (Public)


#### Free symbols / members of external scopes

- L13 _macro_ `#define _mm_loadu_si64 _mm_loadl_epi64`
- L18 _function_ `inline __m128i _mm_loadu_si16(const void* source)`
- L24 _function_ `inline std::int64_t _mm_cvtsi128_si64(__m128i source)`
- L33 _function_ `inline void _mm_storeu_si64(void* dest, __m128i source)`
- L49 _typedef_ `typedef __n16 float16_t;` — MSVC's arm64_neon.h defines vector types (float16x4_t etc.) but omits the scalar float16_t. __n16 is the MSVC intrinsic type for a 16-bit NEON lane.
- L52 _function_ `TRIMD_TARGET_NEON_FP16 inline float16x4_t vdup_n_f16(float16_t value)` — MSVC arm64_neon.h omits vdup_n_f16 and vset_lane_f16. float16x4_t and uint16x4_t both alias __n64 on MSVC, so u16 ops on a float16x4_t register are safe.
- L57 _macro_ `#define vset_lane_f16(value, vec, lane) vset_lane_u16((value).n16_u16[0], (vec), (lane))` — vset_lane_f16 must be a macro since lane index must be a compile-time constant
- L62 _namespace_ `namespace trimd`
- L64 _namespace_ `namespace neon` (scope `trimd`)
- L68 _function_ `template<typename T> inline void prefetch_t0(const T* p)` (scope `trimd::neon`)
- L72 _function_ `template<typename T> inline void prefetch_t1(const T* p)` (scope `trimd::neon`)
- L76 _function_ `template<typename T> inline void prefetch_t2(const T* p)` (scope `trimd::neon`)
- L80 _function_ `template<typename T> inline void prefetch_nta(const T* p)` (scope `trimd::neon`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/SSE.h` (Public)


#### struct `trimd::sse::F128`  
`struct F128`  
_L15-175_
- L16 _public typedef_ `using value_type = float;`
- L18 _public member_ `__m128 data;`
- L20 _public function_ `F128() : data`
- L24 _public function_ `explicit F128(__m128 value) : data`
- L28 _public function_ `explicit F128(float value) : F128`
- L32 _public function_ `F128(float v1, float v2, float v3, float v4) : data`
- L36 _public function_ `static F128 fromAlignedSource(const float* source)`
- L40 _public function_ `static F128 fromUnalignedSource(const float* source)`
- L44 _public function_ `static F128 loadSingleValue(const float* source)`
- L49 _public prototype_ `static F128 fromAlignedSource(const std::uint16_t* source);`
- L50 _public prototype_ `static F128 fromUnalignedSource(const std::uint16_t* source);`
- L51 _public prototype_ `static F128 loadSingleValue(const std::uint16_t* source);`
- L55 _public function_ `template<typename T> static void prefetchT0(const T* source)`
- L67 _public function_ `template<typename T> static void prefetchT1(const T* source)`
- L79 _public function_ `template<typename T> static void prefetchT2(const T* source)`
- L91 _public function_ `template<typename T> static void prefetchNTA(const T* source)`
- L102 _public function_ `void alignedLoad(const float* source)`
- L106 _public function_ `void unalignedLoad(const float* source)`
- L110 _public function_ `void alignedStore(float* dest) const`
- L114 _public function_ `void unalignedStore(float* dest) const`
- L119 _public prototype_ `void alignedLoad(const std::uint16_t* source);`
- L120 _public prototype_ `void unalignedLoad(const std::uint16_t* source);`
- L121 _public prototype_ `void alignedStore(std::uint16_t* dest) const;`
- L122 _public prototype_ `void unalignedStore(std::uint16_t* dest) const;`
- L125 _public function_ `float sum() const`
- L133 _public function_ `F128& operator+=(const F128& rhs)`
- L138 _public function_ `F128& operator-=(const F128& rhs)`
- L143 _public function_ `F128& operator*=(const F128& rhs)`
- L148 _public function_ `F128& operator/=(const F128& rhs)`
- L153 _public function_ `F128& operator&=(const F128& rhs)`
- L158 _public function_ `F128& operator|=(const F128& rhs)`
- L163 _public function_ `F128& operator^=(const F128& rhs)`
- L168 _public function_ `static constexpr std::size_t size()`
- L172 _public function_ `static constexpr std::size_t alignment()`
- L179 _function_ `TRIMD_TARGET_F16C inline F128 F128::fromAlignedSource(const std::uint16_t* source)`
- L183 _function_ `TRIMD_TARGET_F16C inline F128 F128::fromUnalignedSource(const std::uint16_t* source)`
- L187 _function_ `TRIMD_TARGET_F16C inline F128 F128::loadSingleValue(const std::uint16_t* source)`
- L191 _function_ `TRIMD_TARGET_F16C inline void F128::alignedLoad(const std::uint16_t* source)`
- L195 _function_ `TRIMD_TARGET_F16C inline void F128::unalignedLoad(const std::uint16_t* source)`
- L199 _function_ `TRIMD_TARGET_F16C inline void F128::alignedStore(std::uint16_t* dest) const`
- L213 _function_ `TRIMD_TARGET_F16C inline void F128::unalignedStore(std::uint16_t* dest) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trimd`
- L13 _namespace_ `namespace sse` (scope `trimd`)
- L229 _function_ `inline F128 operator==(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L233 _function_ `inline F128 operator!=(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L237 _function_ `inline F128 operator<(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L241 _function_ `inline F128 operator<=(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L245 _function_ `inline F128 operator>(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L249 _function_ `inline F128 operator>=(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L253 _function_ `inline F128 operator+(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L257 _function_ `inline F128 operator-(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L261 _function_ `inline F128 operator*(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L265 _function_ `inline F128 operator/(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L269 _function_ `inline F128 operator&(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L273 _function_ `inline F128 operator|(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L277 _function_ `inline F128 operator^(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L281 _function_ `inline F128 operator~(const F128& rhs)` (scope `trimd::sse`)
- L287 _function_ `inline void transpose(F128& row0, F128& row1, F128& row2, F128& row3)` (scope `trimd::sse`)
- L291 _function_ `inline F128 abs(const F128& rhs)` (scope `trimd::sse`)
- L296 _function_ `inline F128 andnot(const F128& lhs, const F128& rhs)` (scope `trimd::sse`)
- L300 _function_ `inline F128 rsqrt(const F128& rhs)` (scope `trimd::sse`)
- L312 _typedef_ `using F256 = fallback::T256<F128>;` (scope `trimd::sse`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/Scalar.h` (Public)


#### struct `trimd::scalar::T128`  
`template<typename T> struct T128`  
_L25-169_
- L26 _public typedef_ `using value_type = typename std::remove_cv<T>::type;`
- L30 _public member_ `std::array<value_type, 4> data;`
- L32 _public function_ `T128() : data`
- L36 _public function_ `T128(value_type v1, value_type v2, value_type v3, value_type v4) : data({v1, v2, v3, v4})`
- L40 _public function_ `explicit T128(value_type value) : T128(value, value, value, value)`
- L44 _public function_ `static T128 fromAlignedSource(const value_type* source)`
- L48 _public function_ `static T128 fromUnalignedSource(const value_type* source)`
- L52 _public function_ `static T128 loadSingleValue(const value_type* source)`
- L57 _public function_ `template<typename U> static void prefetchT0(const U* )`
- L62 _public function_ `template<typename U> static void prefetchT1(const U* )`
- L67 _public function_ `template<typename U> static void prefetchT2(const U* )`
- L72 _public function_ `template<typename U> static void prefetchNTA(const U* )`
- L76 _public function_ `void alignedLoad(const value_type* source)`
- L83 _public function_ `void unalignedLoad(const value_type* source)`
- L87 _public function_ `void alignedStore(value_type* dest) const`
- L94 _public function_ `void unalignedStore(value_type* dest) const`
- L98 _public function_ `value_type sum() const`
- L102 _public function_ `T128& operator+=(const T128& rhs)`
- L110 _public function_ `T128& operator-=(const T128& rhs)`
- L118 _public function_ `T128& operator*=(const T128& rhs)`
- L126 _public function_ `T128& operator/=(const T128& rhs)`
- L134 _public function_ `T128& operator&=(const T128& rhs)`
- L142 _public function_ `T128& operator|=(const T128& rhs)`
- L150 _public function_ `T128& operator^=(const T128& rhs)`
- L158 _public function_ `static constexpr std::size_t size()`
- L162 _public function_ `static constexpr std::size_t alignment()`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace trimd`
- L22 _namespace_ `namespace scalar` (scope `trimd`)
- L172 _function_ `template<typename T> inline T128<T> operator==(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L180 _function_ `template<typename T> inline T128<T> operator!=(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L188 _function_ `template<typename T> inline T128<T> operator<(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L196 _function_ `template<typename T> inline T128<T> operator<=(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L204 _function_ `template<typename T> inline T128<T> operator>(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L212 _function_ `template<typename T> inline T128<T> operator>=(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L220 _function_ `template<typename T> inline T128<T> operator+(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L225 _function_ `template<typename T> inline T128<T> operator-(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L230 _function_ `template<typename T> inline T128<T> operator*(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L235 _function_ `template<typename T> inline T128<T> operator/(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L240 _function_ `template<typename T> inline T128<T> operator&(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L245 _function_ `template<typename T> inline T128<T> operator|(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L250 _function_ `template<typename T> inline T128<T> operator^(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L255 _function_ `template<typename T> inline T128<T> operator~(const T128<T>& rhs)` (scope `trimd::scalar`)
- L263 _function_ `template<typename T> inline void transpose(T128<T>& row0, T128<T>& row1, T128<T>& row2, T128<T>& row3)` (scope `trimd::scalar`)
- L275 _function_ `template<typename T> inline T128<T> abs(const T128<T>& rhs)` (scope `trimd::scalar`)
- L280 _function_ `template<typename T> inline T128<T> andnot(const T128<T>& lhs, const T128<T>& rhs)` (scope `trimd::scalar`)
- L285 _function_ `template<typename T> inline T128<T> rsqrt(const T128<T>& rhs)` (scope `trimd::scalar`)
- L308 _typedef_ `using F128 = T128<float>;` (scope `trimd::scalar`)
- L309 _typedef_ `using F256 = fallback::T256<F128>;` (scope `trimd::scalar`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/TRiMD.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace trimd`
- L15 _typedef_ `using F256 = avx::F256;` (scope `trimd`)
- L29 _typedef_ `using F128 = sse::F128;` (scope `trimd`)
- L35 _typedef_ `using F128 = neon::F128;` (scope `trimd`)
- L41 _typedef_ `using F128 = scalar::F128;` (scope `trimd`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/Utils.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace trimd`
- L19 _function_ `template<typename TTarget, typename TSource> FORCE_INLINE TTarget bitcast(TSource source)` (scope `trimd`)

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trimd/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define TRIMD_MAJOR_VERSION 2`
- L6 _macro_ `#define TRIMD_MINOR_VERSION 4`
- L7 _macro_ `#define TRIMD_PATCH_VERSION 8`
- L8 _macro_ `#define TRIMD_VERSION_STRING "2.4.8"`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/Concepts.h` (Public)


#### class `trio::Readable`  
`class TRIOAPI Readable`  
_L14-39_
- L25 _public prototype_ `virtual std::size_t read(char* destination, std::size_t size) = 0;` — @brief Read bytes from stream into the given buffer. @param destination Destination buffer into which the data is going to be read from the stream. @param size Number of bytes to read from stream. @return Number of bytes read.
- L35 _public prototype_ `virtual std::size_t read(Writable* destination, std::size_t size) = 0;` — @brief Read bytes from this stream into the given stream. @param destination Destination stream into which the data is going to be read from this stream. @param size Number of bytes to read from stream. @return Number of bytes read.
- L38 _protected prototype_ `virtual ~Readable();`

#### class `trio::Writable`  
`class TRIOAPI Writable`  
_L41-66_
- L52 _public prototype_ `virtual std::size_t write(const char* source, std::size_t size) = 0;` — @brief Writes bytes from the given buffer to the stream. @param source Source buffer from which the data is going to be written to the stream. @param size Number of bytes to write to the stream. @return Number of bytes written.
- L62 _public prototype_ `virtual std::size_t write(Readable* source, std::size_t size) = 0;` — @brief Writes bytes from the given stream to this stream. @param source Source stream from which the data is going to be written into this stream. @param size Number of bytes to write to the stream. @return Number of bytes written.
- L65 _protected prototype_ `virtual ~Writable();`

#### class `trio::Seekable`  
`class TRIOAPI Seekable`  
_L68-85_
- L75 _public prototype_ `virtual std::uint64_t tell() = 0;` — @brief Get the current position in the stream. @return Position in the stream relative to it's start, with 0 denoting the start position.
- L81 _public prototype_ `virtual void seek(std::uint64_t position) = 0;` — @brief Set the current position in the stream. @param position Position in the stream relative to it's start, with 0 denoting the start position.
- L84 _protected prototype_ `virtual ~Seekable();`

#### class `trio::Openable`  
`class TRIOAPI Openable`  
_L87-96_
- L92 _public prototype_ `virtual void open() = 0;` — @brief Open access to the stream.
- L95 _protected prototype_ `virtual ~Openable();`

#### class `trio::Closeable`  
`class TRIOAPI Closeable`  
_L98-107_
- L103 _public prototype_ `virtual void close() = 0;` — @brief Close access to the stream.
- L106 _protected prototype_ `virtual ~Closeable();`

#### class `trio::Controllable`  
`class TRIOAPI Controllable : public Openable, public Closeable`  
_L109-112_
- inherits: `Openable,Closeable`
- L111 _protected prototype_ `virtual ~Controllable();`

#### class `trio::Bounded`  
`class TRIOAPI Bounded`  
_L114-125_
- L121 _public prototype_ `virtual std::uint64_t size() = 0;` — @brief Obtain size of stream in bytes. @return Size in bytes.
- L124 _protected prototype_ `virtual ~Bounded();`

#### class `trio::Buffered`  
`class TRIOAPI Buffered`  
_L127-136_
- L132 _public prototype_ `virtual void flush() = 0;` — @brief Flush the changes to filesystem.
- L135 _protected prototype_ `virtual ~Buffered();`

#### class `trio::Resizable`  
`class TRIOAPI Resizable`  
_L138-147_
- L143 _public prototype_ `virtual void resize(std::uint64_t size) = 0;` — @brief Resize file to the requested size.
- L146 _protected prototype_ `virtual ~Resizable();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define TRIOAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define TRIOAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define TRIOAPI` — Build or use static library

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/Stream.h` (Public)


#### class `trio::BoundedIOStream`  
`class TRIOAPI BoundedIOStream : public Controllable, public Readable, public Writable, public Seekable, public Bounded`  
_L14-27_
- inherits: `Controllable,Readable,Writable,Seekable,Bounded`
- L16 _public typedef_ `using AccessMode = trio::AccessMode;`
- L17 _public typedef_ `using OpenMode = trio::OpenMode;`
- L19 _public member_ `static const sc::StatusCode OpenError;`
- L20 _public member_ `static const sc::StatusCode ReadError;`
- L21 _public member_ `static const sc::StatusCode WriteError;`
- L22 _public member_ `static const sc::StatusCode AlreadyOpenError;`
- L23 _public member_ `static const sc::StatusCode SeekError;`
- L26 _public prototype_ `virtual ~BoundedIOStream();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/streams/FileStream.h` (Public)


#### class `trio::FileStream`  
`class TRIOAPI FileStream : public BoundedIOStream`  
_L13-48_
- inherits: `BoundedIOStream`
- desc: @brief Standard file stream.
- L31 _public prototype_ `static FileStream* create(const char* path, AccessMode accessMode, OpenMode openMode, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of a FileStream instance. @param path UTF-8 encoded path to file to be opened. @param accessMode Control whether the file is opened for reading or writing. @param openMode Control whether the file is opened in binary or textual mode. @param memRes The memory resource to be used for the allocation of the FileStream instance. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L38 _public prototype_ `static void destroy(FileStream* instance);` — @brief Method for freeing a FileStream instance. @param instance Instance of FileStream to be freed. @see create
- L40 _public prototype_ `FileStream() = default;`
- L43 _public prototype_ `FileStream(const FileStream&) = delete;`
- L44 _public prototype_ `FileStream& operator=(const FileStream&) = delete;`
- L46 _public prototype_ `FileStream(FileStream&&) = default;`
- L47 _public prototype_ `FileStream& operator=(FileStream&&) = default;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<trio::FileStream>`  
_L55-57_
- L56 _public typedef_ `using type = FactoryCreate<trio::FileStream>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<trio::FileStream>`  
_L60-62_
- L61 _public typedef_ `using type = FactoryDestroy<trio::FileStream>;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace trio`
- L52 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/streams/MemoryMappedFileStream.h` (Public)


#### class `trio::MemoryMappedFileStream`  
`class TRIOAPI MemoryMappedFileStream : public BoundedIOStream, public Buffered, public Resizable`  
_L15-48_
- inherits: `BoundedIOStream,Buffered,Resizable`
- desc: @brief Memory mapped file stream.
- L31 _public prototype_ `static MemoryMappedFileStream* create(const char* path, AccessMode accessMode, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of a MemoryMappedFileStream instance. @param path UTF-8 encoded path to file to be opened. @param accessMode Control whether the file is opened for reading or writing. @param memRes The memory resource to be used for the allocation of the MemoryMappedFileStream instance. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L38 _public prototype_ `static void destroy(MemoryMappedFileStream* instance);` — @brief Method for freeing a MemoryMappedFileStream instance. @param instance Instance of MemoryMappedFileStream to be freed. @see create
- L40 _public prototype_ `MemoryMappedFileStream() = default;`
- L43 _public prototype_ `MemoryMappedFileStream(const MemoryMappedFileStream&) = delete;`
- L44 _public prototype_ `MemoryMappedFileStream& operator=(const MemoryMappedFileStream&) = delete;`
- L46 _public prototype_ `MemoryMappedFileStream(MemoryMappedFileStream&&) = default;`
- L47 _public prototype_ `MemoryMappedFileStream& operator=(MemoryMappedFileStream&&) = default;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<trio::MemoryMappedFileStream>`  
_L55-57_
- L56 _public typedef_ `using type = FactoryCreate<trio::MemoryMappedFileStream>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<trio::MemoryMappedFileStream>`  
_L60-62_
- L61 _public typedef_ `using type = FactoryDestroy<trio::MemoryMappedFileStream>;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace trio`
- L52 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/streams/MemoryStream.h` (Public)


#### class `trio::MemoryStream`  
`class TRIOAPI MemoryStream : public BoundedIOStream`  
_L15-57_
- inherits: `BoundedIOStream`
- desc: @brief In-memory stream.
- L27 _public prototype_ `static MemoryStream* create(MemoryResource* memRes = nullptr);` — @brief Factory method for creation of a MemoryStream instance. @param memRes The memory resource to be used for the allocation of the MemoryStream instance. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L40 _public prototype_ `static MemoryStream* create(std::size_t initialSize, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of a MemoryStream instance. @param initialSize Initial size of the memory stream. @param memRes The memory resource to be used for the allocation of the MemoryStream instance. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L47 _public prototype_ `static void destroy(MemoryStream* instance);` — @brief Method for freeing a MemoryStream instance. @param instance Instance of MemoryStream to be freed. @see create
- L49 _public prototype_ `MemoryStream() = default;`
- L52 _public prototype_ `MemoryStream(const MemoryStream&) = delete;`
- L53 _public prototype_ `MemoryStream& operator=(const MemoryStream&) = delete;`
- L55 _public prototype_ `MemoryStream(MemoryStream&&) = default;`
- L56 _public prototype_ `MemoryStream& operator=(MemoryStream&&) = default;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<trio::MemoryStream>`  
_L64-66_
- L65 _public typedef_ `using type = FactoryCreate<trio::MemoryStream>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<trio::MemoryStream>`  
_L69-71_
- L70 _public typedef_ `using type = FactoryDestroy<trio::MemoryStream>;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace trio`
- L61 _namespace_ `namespace pma`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/types/Aliases.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/types/Parameters.h` (Public)


#### enum `trio::AccessMode`  
`enum class AccessMode`  
_L7-11_
- L8 _public enumerator_ `Read = 1`
- L9 _public enumerator_ `Write = 2`
- L10 _public enumerator_ `ReadWrite = 3`

#### enum `trio::OpenMode`  
`enum class OpenMode`  
_L13-16_
- L14 _public enumerator_ `Binary = 4`
- L15 _public enumerator_ `Text = 8`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/utils/StreamScope.h` (Public)


#### class `trio::StreamScope`  
`class StreamScope`  
_L11-39_
- L13 _public function_ `explicit StreamScope(Controllable* stream_) : stream`
- L18 _public function_ `~StreamScope()`
- L24 _public prototype_ `StreamScope(const StreamScope&) = delete;`
- L25 _public prototype_ `StreamScope& operator=(const StreamScope&) = delete;`
- L27 _public function_ `StreamScope(StreamScope&& rhs) noexcept : stream`
- L32 _public function_ `StreamScope& operator=(StreamScope&& rhs) noexcept`
- L38 _private member_ `Controllable* stream;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace trio`

### `Plugins/Animation/RigLogic/Source/RigLogicLib/Public/trio/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define TRIO_MAJOR_VERSION 4`
- L6 _macro_ `#define TRIO_MINOR_VERSION 0`
- L7 _macro_ `#define TRIO_PATCH_VERSION 21`
- L8 _macro_ `#define TRIO_VERSION_STRING "4.0.21"`
