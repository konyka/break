# Plugins / DNACalibLib

- module root: `Plugins/Animation/DNACalib/Source/DNACalibLib`
- headers: 61; symbols: 1892
- symbol kinds: class=43, delegate=1, enum=6, enumerator=23, function=627, macro=21, member=284, namespace=59, prototype=733, struct=63, typedef=32
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RigLogicLib, UnrealEd

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/CommandImplBase.h` (Private)


#### class `dnac::CommandImplBase`  
`template<class TCommand> class CommandImplBase`  
_L11-34_
- L13 _protected function_ `explicit CommandImplBase(MemoryResource* memRes_) : memRes`
- L18 _public function_ `static TCommand* create(MemoryResource* memRes)`
- L23 _public function_ `static void destroy(TCommand* instance)`
- L28 _public function_ `MemoryResource* getMemoryResource()`
- L33 _private member_ `MemoryResource* memRes;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/TypeDefs.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace dnac`
- L23 _typedef_ `template<typename T> using AlignedAllocator = PolyAllocator<T, 64ul, AlignedMemoryResource>;` (scope `dnac`)
- L26 _typedef_ `template<typename T> using Blob = terse::Blob<T, PolyAllocator<T>>;` (scope `dnac`)
- L29 _typedef_ `template<typename T> using DynArray = terse::DynArray<T, PolyAllocator<T>>;` (scope `dnac`)
- L32 _typedef_ `template<typename T> using AlignedDynArray = terse::DynArray<T, AlignedAllocator<T>>;` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/commands/CalculateMeshLowerLODsCommandImpl.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dnac`
- L9 _prototype_ `bool isUVMapOverlapping(ConstArrayView<float> us, ConstArrayView<float> vs, std::size_t overlapCountThreshold = 10ul, float uvCompareThreshold = 0.0002f);` (scope `dnac`)
- L13 _prototype_ `void offsetOverlappingUVMapRegion(ArrayView<float> us, ArrayView<float> vs, float uOffset = 1.0f, float vOffset = 0.0f, float uvCompareThreshold = 0.0002f);` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/commands/RenameResourceCommand.h` (Private)


#### class `dnac::RenameResourceCommand`  
`template<class TDerived> class RenameResourceCommand : public CommandImplBase<TDerived>`  
_L15-86_
- inherits: `CommandImplBase<TDerived>`
- L17 _private typedef_ `using Super = CommandImplBase<TDerived>;`
- L26 _public function_ `explicit RenameResourceCommand(MemoryResource* memRes_) : Super`
- L34 _public prototype_ `virtual ~RenameResourceCommand() = default;`
- L36 _public prototype_ `RenameResourceCommand(const RenameResourceCommand&) = default;`
- L37 _public prototype_ `RenameResourceCommand& operator=(const RenameResourceCommand&) = default;`
- L39 _public prototype_ `RenameResourceCommand(RenameResourceCommand&&) = default;`
- L40 _public prototype_ `RenameResourceCommand& operator=(RenameResourceCommand&&) = default;`
- L42 _public function_ `void setName(std::uint16_t index_, const char* newName_)`
- L48 _public function_ `void setName(const char* oldName_, const char* newName_)`
- L54 _public function_ `void run(DNACalibDNAReaderImpl* output)`
- L63 _private function_ `void searchAndRename(DNACalibDNAReaderImpl* output)`
- L73 _private function_ `void rename(DNACalibDNAReaderImpl* output)`
- L77 _private prototype_ `virtual std::uint16_t getNameCount(const dna::Reader* input) const = 0;`
- L78 _private prototype_ `virtual StringView getNameByIndex(const dna::Reader* input, std::uint16_t index_) const = 0;`
- L79 _private prototype_ `virtual void setNameByIndex(dna::Writer* output, std::uint16_t index_, const char* name) = 0;`
- L82 _private member_ `String<char> oldName;`
- L83 _private member_ `String<char> newName;`
- L84 _private member_ `std::uint16_t index;`
- L85 _private member_ `Configuration config;`

#### enum `dnac::RenameResourceCommand::Configuration`  
`enum class Configuration`  
_L19-23_
- L20 _public enumerator_ `Unconfigured`
- L21 _public enumerator_ `SearchAndRename`
- L22 _public enumerator_ `RenameByIndex`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/commands/SupportFactories.h` (Private)


#### struct `dnac::WeightGetterFactory`  
`struct WeightGetterFactory`  
_L22-31_
- L23 _public typedef_ `using GetterFunc = std::function<float(float*, std::size_t)>;`
- L25 _public function_ `static GetterFunc create(const Vector<float>& masks)`

#### struct `dnac::OperationFactory`  
`struct OperationFactory`  
_L33-57_
- L34 _public typedef_ `using OpFunc = std::function<float(float, float, float)>;`
- L36 _public function_ `static OpFunc create(VectorOperation operation)`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace dnac`
- L27 _function_ `return [](float* , std::size_t )` (scope `dnac::WeightGetterFactory::create`)
- L29 _function_ `return [](float* pMasks, std::size_t index)` (scope `dnac::WeightGetterFactory::create`)
- L39 _function_ `return [](float a, float b, float weight)` (scope `dnac::OperationFactory::create`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/Aliases.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/BaseImpl.h` (Private)


#### class `dnac::BaseImpl`  
`class BaseImpl`  
_L10-38_
- L12 _protected function_ `explicit BaseImpl(MemoryResource* memRes_) : memRes`
- L17 _protected function_ `BaseImpl(UnknownLayerPolicy unknownPolicy, UpgradeFormatPolicy upgradePolicy, MemoryResource* memRes_) : memRes`
- L22 _protected prototype_ `~BaseImpl() = default;`
- L24 _protected prototype_ `BaseImpl(const BaseImpl&) = delete;`
- L25 _protected prototype_ `BaseImpl& operator=(const BaseImpl&) = delete;`
- L27 _protected prototype_ `BaseImpl(BaseImpl&& rhs) = delete;`
- L28 _protected prototype_ `BaseImpl& operator=(BaseImpl&&) = delete;`
- L31 _public function_ `MemoryResource* getMemoryResource()`
- L36 _protected member_ `MemoryResource* memRes;`
- L37 _protected member_ `mutable DNA dna;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/DNA.h` (Private)


#### struct `dnac::Dispatcher`  
`template<typename TVersion, TVersion Fallback> struct Dispatcher<TVersion, Fallback>`  
_L117-132_
- L120 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion , bool transparent)`
- L136 _public typedef_ `using Super = Dispatcher<TVersion, Rest...>;`
- L139 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion version, bool transparent)`

#### struct `dnac::Dispatcher`  
`template<typename TVersion, TVersion Expected, TVersion... Rest> struct Dispatcher<TVersion, Expected, Rest...> : Dispatcher<TVersion, Rest...>`  
_L135-151_
- inherits: `Dispatcher<TVersion,Rest...>`
- L120 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion , bool transparent)`
- L136 _public typedef_ `using Super = Dispatcher<TVersion, Rest...>;`
- L139 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion version, bool transparent)`

#### enum `dnac::FileVersion`  
`enum FileVersion : std::uint64_t`  
_L170-181_
- L171 _public enumerator_ `unknown = 0u`
- L172 _public enumerator_ `v21 = rev(2, 1)`
- L173 _public enumerator_ `v22 = rev(2, 2)`
- L174 _public enumerator_ `v23 = rev(2, 3)`
- L175 _public enumerator_ `v24 = rev(2, 4)`
- L176 _public enumerator_ `v25 = rev(2, 5)`
- L177 _public enumerator_ `v26 = rev(2, 6)`
- L178 _public enumerator_ `v27 = rev(2, 7)`
- L179 _public enumerator_ `v28 = rev(2, 8)`
- L180 _public enumerator_ `latest = v28`

#### enum `dnac::UpgradeFormatPolicy`  
`enum class UpgradeFormatPolicy`  
_L199-202_
- L200 _public enumerator_ `Disallowed`
- L201 _public enumerator_ `Allowed`

#### struct `dnac::SerializationContext`  
`struct SerializationContext`  
_L204-207_
- L205 _public member_ `FileVersion version;`
- L206 _public member_ `void* data;`

#### struct `dnac::Version`  
`struct Version`  
_L209-238_
- L210 _public member_ `std::uint16_t generation;`
- L211 _public member_ `std::uint16_t version;`
- L213 _public function_ `Version(FileVersion fileVersion) : generation`
- L218 _public function_ `operator FileVersion() const`
- L223 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L230 _public function_ `bool matches(FileVersion fileVersion) const`
- L235 _public function_ `bool supported() const`

#### struct `dnac::ExpectedValue`  
`template<typename T> struct ExpectedValue`  
_L241-266_
- L242 _public member_ `T expected;`
- L243 _public member_ `T got;`
- L245 _public function_ `explicit ExpectedValue(const T& value) : expected`
- L251 _public function_ `template<class Archive> void load(Archive& archive)`
- L257 _public function_ `template<class Archive> void save(Archive& archive)`
- L263 _public function_ `bool matches() const`

#### struct `dnac::Signature`  
`template<std::size_t Size> struct Signature`  
_L269-287_
- L270 _public typedef_ `using SignatureValueType = std::array<char, Size>;`
- L272 _public member_ `ExpectedValue<SignatureValueType> value;`
- L274 _public function_ `explicit Signature(SignatureValueType bytes) : value`
- L279 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L284 _public function_ `bool matches() const`

#### struct `dnac::SectionLookupTable`  
`struct SectionLookupTable`  
_L289-318_
- L290 _public member_ `terse::ArchiveOffset<std::uint32_t> descriptor;`
- L291 _public member_ `terse::ArchiveOffset<std::uint32_t> definition;`
- L292 _public member_ `terse::ArchiveOffset<std::uint32_t> behavior;`
- L293 _public member_ `terse::ArchiveOffset<std::uint32_t> controls;`
- L294 _public member_ `terse::ArchiveOffset<std::uint32_t> joints;`
- L295 _public member_ `terse::ArchiveOffset<std::uint32_t> blendShapeChannels;`
- L296 _public member_ `terse::ArchiveOffset<std::uint32_t> animatedMaps;`
- L297 _public member_ `terse::ArchiveOffset<std::uint32_t> geometry;`
- L300 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::Index`  
`struct Index`  
_L320-348_
- L321 _public member_ `std::uint32_t id;`
- L322 _public member_ `std::uint32_t version;`
- L323 _public member_ `terse::ArchiveOffset<std::uint32_t> offset;`
- L324 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L327 _public function_ `template<std::size_t Length = 16ul> std::array<char, Length> label()`
- L338 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::IndexTable`  
`struct IndexTable`  
_L350-389_
- L351 _public member_ `Vector<Index> entries;`
- L353 _public function_ `explicit IndexTable(MemoryResource* memRes) : entries`
- L357 _public function_ `Index* get(std::uint32_t id, std::uint32_t version)`
- L366 _public function_ `const Index* get(std::uint32_t id, std::uint32_t version) const`
- L370 _public function_ `Index* create(std::uint32_t id, std::uint32_t version)`
- L376 _public function_ `void destroy(std::uint32_t id, std::uint32_t version)`
- L385 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::UnknownLayer`  
`struct UnknownLayer`  
_L391-433_
- L392 _public member_ `std::uint32_t id;`
- L393 _public member_ `std::uint32_t version;`
- L394 _public member_ `Blob<char> data;`
- L396 _public function_ `UnknownLayer(std::uint32_t id_, std::uint32_t version_, MemoryResource* memRes) : id`
- L402 _public function_ `std::uint32_t layerId()`
- L406 _public function_ `std::uint32_t layerVersion()`
- L410 _public function_ `bool layerSupported(FileVersion )`
- L415 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::Layer`  
`template<std::uint32_t Id, std::uint32_t Version, typename TData, FileVersion AvailableFromFileVersion> struct Layer : TData`  
_L436-471_
- inherits: `TData`
- L439 _public function_ `template<typename... Args> explicit Layer(Args&&... args) : TData`
- L443 _public function_ `std::uint32_t layerId()`
- L447 _public function_ `std::uint32_t layerVersion()`
- L451 _public function_ `bool layerSupported(FileVersion inVersion)`
- L456 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::LayerContainer`  
`template<> struct LayerContainer<>`  
_L477-516_
- L478 _public member_ `UnknownLayerPolicy unknownPolicy;`
- L479 _public member_ `UpgradeFormatPolicy upgradePolicy;`
- L480 _public member_ `Vector<UnknownLayer> unknownLayers;`
- L482 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes) : unknownPolicy`
- L489 _public function_ `template<typename TArchive> void serialize(TArchive& archive)`
- L513 _public function_ `void updateIndexTable(IndexTable& , FileVersion )`
- L520 _public typedef_ `using Super = LayerContainer<TRest...>;`
- L522 _public member_ `TLayer* layer;`
- L524 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes, TLayer* layer_, TRest*... rest) : Super`
- L544 _public function_ `void updateIndexTable(IndexTable& indexTable, FileVersion fileVersion)`

#### struct `dnac::LayerContainer`  
`template<typename TLayer, typename... TRest> struct LayerContainer<TLayer, TRest...> : LayerContainer<TRest...>`  
_L519-559_
- inherits: `LayerContainer<TRest...>`
- L478 _public member_ `UnknownLayerPolicy unknownPolicy;`
- L479 _public member_ `UpgradeFormatPolicy upgradePolicy;`
- L480 _public member_ `Vector<UnknownLayer> unknownLayers;`
- L482 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes) : unknownPolicy`
- L489 _public function_ `template<typename TArchive> void serialize(TArchive& archive)`
- L513 _public function_ `void updateIndexTable(IndexTable& , FileVersion )`
- L520 _public typedef_ `using Super = LayerContainer<TRest...>;`
- L522 _public member_ `TLayer* layer;`
- L524 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes, TLayer* layer_, TRest*... rest) : Super`
- L544 _public function_ `void updateIndexTable(IndexTable& indexTable, FileVersion fileVersion)`

#### struct `dnac::RawSurjectiveMapping`  
`template<typename TFrom, typename TTo = TFrom> struct RawSurjectiveMapping : public SurjectiveMapping<TFrom, TTo>`  
_L562-572_
- inherits: `SurjectiveMapping<TFrom,TTo>`
- L566 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawCoordinateSystem`  
`struct RawCoordinateSystem`  
_L574-598_
- L575 _public member_ `std::uint16_t xAxis;`
- L576 _public member_ `std::uint16_t yAxis;`
- L577 _public member_ `std::uint16_t zAxis;`
- L579 _public function_ `bool operator==(const CoordinateSystem& coordinateSystem) const`
- L585 _public function_ `bool operator!=(const CoordinateSystem& coordinateSystem) const`
- L590 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawLODMapping`  
`struct RawLODMapping : public LODMapping`  
_L600-610_
- inherits: `LODMapping`
- L604 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawDescriptor`  
`struct RawDescriptor`  
_L612-670_
- L613 _public typedef_ `using StringPair = std::tuple<String<char>, String<char>>;`
- L615 _public member_ `String<char> name;`
- L616 _public member_ `std::uint16_t archetype;`
- L617 _public member_ `std::uint16_t gender;`
- L618 _public member_ `std::uint16_t age;`
- L619 _public member_ `Vector<StringPair> metadata;`
- L620 _public member_ `std::uint16_t translationUnit;`
- L621 _public member_ `std::uint16_t rotationUnit;`
- L622 _public member_ `RawCoordinateSystem coordinateSystem;`
- L623 _public member_ `std::uint16_t lodCount;`
- L624 _public member_ `std::uint16_t maxLOD;`
- L625 _public member_ `String<char> complexity;`
- L626 _public member_ `String<char> dbName;`
- L628 _public function_ `explicit RawDescriptor(MemoryResource* memRes) : name`
- L644 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawDescriptorExt`  
`struct RawDescriptorExt`  
_L672-731_
- L673 _public member_ `RotationSequence rotationSequence;`
- L674 _public member_ `RotationSign rotationSign;`
- L675 _public member_ `FaceWindingOrder faceWindingOrder;`
- L677 _public function_ `explicit RawDescriptorExt(MemoryResource* memRes) : rotationSequence`
- L685 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L693 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v22> )`
- L698 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v23> )`
- L703 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v24> )`
- L708 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v25> )`
- L713 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v26> )`
- L718 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v27> )`
- L723 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion )`

#### struct `dnac::RawVector3Vector`  
`struct RawVector3Vector`  
_L733-805_
- L734 _public member_ `AlignedDynArray<float> xs;`
- L735 _public member_ `AlignedDynArray<float> ys;`
- L736 _public member_ `AlignedDynArray<float> zs;`
- L738 _public function_ `explicit RawVector3Vector(MemoryResource* memRes) : xs`
- L744 _public function_ `RawVector3Vector(std::size_t size_, float initial, MemoryResource* memRes) : xs`
- L750 _public function_ `RawVector3Vector(ConstArrayView<float> xs_, ConstArrayView<float> ys_, ConstArrayView<float> zs_, MemoryResource* memRes) : xs`
- L757 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L766 _public function_ `std::size_t size() const`
- L771 _public function_ `void reserve(std::size_t count)`
- L777 _public function_ `void resize(std::size_t count)`
- L783 _public function_ `void resize(std::size_t count, float value)`
- L789 _public function_ `void clear()`
- L796 _public function_ `template<typename Iterator> void assign(Iterator start, Iterator end)`

#### struct `dnac::RawDefinition`  
`struct RawDefinition`  
_L807-871_
- L808 _public member_ `RawLODMapping lodJointMapping;`
- L809 _public member_ `RawLODMapping lodBlendShapeMapping;`
- L810 _public member_ `RawLODMapping lodAnimatedMapMapping;`
- L811 _public member_ `RawLODMapping lodMeshMapping;`
- L812 _public member_ `Vector<String<char>> guiControlNames;`
- L813 _public member_ `Vector<String<char>> rawControlNames;`
- L814 _public member_ `Vector<String<char>> jointNames;`
- L815 _public member_ `Vector<String<char>> blendShapeChannelNames;`
- L816 _public member_ `Vector<String<char>> animatedMapNames;`
- L817 _public member_ `Vector<String<char>> meshNames;`
- L818 _public member_ `RawSurjectiveMapping<std::uint16_t> meshBlendShapeChannelMapping;`
- L819 _public member_ `DynArray<std::uint16_t> jointHierarchy;`
- L820 _public member_ `RawVector3Vector neutralJointTranslations;`
- L821 _public member_ `RawVector3Vector neutralJointRotations;`
- L823 _public function_ `explicit RawDefinition(MemoryResource* memRes) : lodJointMapping`
- L841 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawConditionalTable`  
`struct RawConditionalTable`  
_L873-905_
- L874 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L875 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L876 _public member_ `DynArray<float> fromValues;`
- L877 _public member_ `DynArray<float> toValues;`
- L878 _public member_ `DynArray<float> slopeValues;`
- L879 _public member_ `DynArray<float> cutValues;`
- L881 _public function_ `explicit RawConditionalTable(MemoryResource* memRes) : inputIndices`
- L891 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawPSDMatrix`  
`struct RawPSDMatrix`  
_L907-927_
- L908 _public member_ `DynArray<std::uint16_t> rows;`
- L909 _public member_ `DynArray<std::uint16_t> columns;`
- L910 _public member_ `DynArray<float> values;`
- L912 _public function_ `explicit RawPSDMatrix(MemoryResource* memRes) : rows`
- L919 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawControls`  
`struct RawControls`  
_L929-949_
- L930 _public member_ `std::uint16_t psdCount;`
- L931 _public member_ `RawConditionalTable conditionals;`
- L932 _public member_ `RawPSDMatrix psds;`
- L934 _public function_ `explicit RawControls(MemoryResource* memRes) : psdCount`
- L941 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawJointGroup`  
`struct RawJointGroup`  
_L951-988_
- L957 _public member_ `DynArray<std::uint16_t> lods;` — Row count of each LOD 12, 9, 3, |  |  + LOD-2 contains first 3 rows |  + LOD-1 contains first 9 rows + LOD-0 contains first 12 rows
- L959 _public member_ `DynArray<std::uint16_t> inputIndices;` — Sub-matrix col -> input vector
- L961 _public member_ `DynArray<std::uint16_t> outputIndices;` — Sub-matrix row -> output vector
- L963 _public member_ `AlignedDynArray<float> values;` — Non-zero values of all sub-matrices
- L965 _public member_ `DynArray<std::uint16_t> jointIndices;`
- L967 _public function_ `explicit RawJointGroup(MemoryResource* memRes) : lods`
- L976 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawJoints`  
`struct RawJoints`  
_L990-1010_
- L991 _public member_ `std::uint16_t rowCount;`
- L992 _public member_ `std::uint16_t colCount;`
- L993 _public member_ `Vector<RawJointGroup> jointGroups;`
- L995 _public function_ `explicit RawJoints(MemoryResource* memRes) : rowCount`
- L1002 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawBlendShapeChannels`  
`struct RawBlendShapeChannels`  
_L1012-1032_
- L1013 _public member_ `DynArray<std::uint16_t> lods;`
- L1014 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1015 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1017 _public function_ `explicit RawBlendShapeChannels(MemoryResource* memRes) : lods`
- L1024 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawAnimatedMaps`  
`struct RawAnimatedMaps`  
_L1034-1050_
- L1035 _public member_ `DynArray<std::uint16_t> lods;`
- L1036 _public member_ `RawConditionalTable conditionals;`
- L1038 _public function_ `explicit RawAnimatedMaps(MemoryResource* memRes) : lods`
- L1044 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawBehavior`  
`struct RawBehavior`  
_L1052-1098_
- L1053 _public member_ `RawControls controls;`
- L1054 _public member_ `RawJoints joints;`
- L1055 _public member_ `RawBlendShapeChannels blendShapeChannels;`
- L1056 _public member_ `RawAnimatedMaps animatedMaps;`
- L1058 _public function_ `explicit RawBehavior(MemoryResource* memRes) : controls`
- L1066 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L1088 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion)`

#### struct `dnac::RawTextureCoordinateVector`  
`struct RawTextureCoordinateVector`  
_L1100-1126_
- L1101 _public member_ `DynArray<float> us;`
- L1102 _public member_ `DynArray<float> vs;`
- L1104 _public function_ `explicit RawTextureCoordinateVector(MemoryResource* memRes) : us`
- L1110 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1117 _public function_ `std::size_t size() const`
- L1122 _public function_ `void clear()`

#### struct `dnac::RawVertexLayoutVector`  
`struct RawVertexLayoutVector`  
_L1128-1159_
- L1129 _public member_ `DynArray<std::uint32_t> positions;`
- L1130 _public member_ `DynArray<std::uint32_t> textureCoordinates;`
- L1131 _public member_ `DynArray<std::uint32_t> normals;`
- L1133 _public function_ `explicit RawVertexLayoutVector(MemoryResource* memRes) : positions`
- L1140 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1149 _public function_ `std::size_t size() const`
- L1154 _public function_ `void clear()`

#### struct `dnac::RawFace`  
`struct RawFace`  
_L1161-1173_
- L1162 _public member_ `DynArray<std::uint32_t> layoutIndices;`
- L1164 _public function_ `explicit RawFace(MemoryResource* memRes) : layoutIndices`
- L1169 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawVertexSkinWeights`  
`struct RawVertexSkinWeights`  
_L1175-1191_
- L1176 _public member_ `AlignedDynArray<float> weights;`
- L1177 _public member_ `DynArray<std::uint16_t> jointIndices;`
- L1179 _public function_ `explicit RawVertexSkinWeights(MemoryResource* memRes) : weights`
- L1185 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawBlendShapeTarget`  
`struct RawBlendShapeTarget`  
_L1193-1213_
- L1194 _public member_ `RawVector3Vector deltas;`
- L1195 _public member_ `DynArray<std::uint32_t> vertexIndices;`
- L1196 _public member_ `std::uint16_t blendShapeChannelIndex;`
- L1198 _public function_ `explicit RawBlendShapeTarget(MemoryResource* memRes) : deltas`
- L1205 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMesh`  
`struct RawMesh`  
_L1215-1306_
- L1216 _public member_ `terse::ArchiveOffset<std::uint32_t> offset;`
- L1217 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1218 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1219 _public member_ `RawVector3Vector positions;`
- L1220 _public member_ `RawTextureCoordinateVector textureCoordinates;`
- L1221 _public member_ `RawVector3Vector normals;`
- L1222 _public member_ `RawVertexLayoutVector layouts;`
- L1223 _public member_ `Vector<RawFace> faces;`
- L1224 _public member_ `std::uint16_t maximumInfluencePerVertex;`
- L1225 _public member_ `Vector<RawVertexSkinWeights> skinWeights;`
- L1226 _public member_ `Vector<RawBlendShapeTarget> blendShapeTargets;`
- L1227 _public member_ `terse::ArchiveOffset<std::uint32_t>::Proxy offsetMarker;`
- L1228 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1230 _public function_ `explicit RawMesh(MemoryResource* memRes) : offset`
- L1247 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1253 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L1279 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion)`

#### struct `dnac::RawGeometry`  
`struct RawGeometry`  
_L1308-1320_
- L1309 _public member_ `Vector<RawMesh> meshes;`
- L1311 _public function_ `explicit RawGeometry(MemoryResource* memRes) : meshes`
- L1316 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawActivationFunction`  
`struct RawActivationFunction`  
_L1322-1338_
- L1323 _public member_ `std::uint16_t functionId;`
- L1324 _public member_ `DynArray<float> parameters;`
- L1326 _public function_ `explicit RawActivationFunction(MemoryResource* memRes) : functionId`
- L1332 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawNeuralNetworkLayer`  
`struct RawNeuralNetworkLayer`  
_L1340-1360_
- L1341 _public member_ `DynArray<float> biases;`
- L1342 _public member_ `DynArray<float> weights;` — 2D Matrix
- L1343 _public member_ `RawActivationFunction activationFunction;`
- L1345 _public function_ `explicit RawNeuralNetworkLayer(MemoryResource* memRes) : biases`
- L1352 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawNeuralNetwork`  
`struct RawNeuralNetwork`  
_L1362-1392_
- L1363 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1364 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1365 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1366 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1367 _public member_ `Vector<RawNeuralNetworkLayer> layers;`
- L1368 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1370 _public function_ `explicit RawNeuralNetwork(MemoryResource* memRes) : size`
- L1380 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMeshRegionMembership`  
`struct RawMeshRegionMembership`  
_L1394-1410_
- L1395 _public member_ `Matrix<String<char>> regionNames;` — [meshIndex][regionIndex]
- L1396 _public member_ `Vector<Matrix<std::uint16_t>> indices;` — [meshIndex][regionIndex][neuralNetworkIndices...]
- L1398 _public function_ `explicit RawMeshRegionMembership(MemoryResource* memRes) : regionNames`
- L1404 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMachineLearnedBehavior`  
`struct RawMachineLearnedBehavior`  
_L1412-1436_
- L1413 _public member_ `Vector<String<char>> mlControlNames;`
- L1414 _public member_ `RawLODMapping lodNeuralNetworkMapping;`
- L1415 _public member_ `RawMeshRegionMembership neuralNetworkToMeshRegion;`
- L1416 _public member_ `Vector<RawNeuralNetwork> neuralNetworks;`
- L1418 _public function_ `explicit RawMachineLearnedBehavior(MemoryResource* memRes) : mlControlNames`
- L1426 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawRBFPose`  
`struct RawRBFPose`  
_L1438-1454_
- L1439 _public member_ `String<char> name;`
- L1440 _public member_ `float scale;`
- L1442 _public function_ `explicit RawRBFPose(MemoryResource* memRes) : name`
- L1448 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawRBFPoseExt`  
`struct RawRBFPoseExt`  
_L1456-1476_
- L1457 _public member_ `DynArray<std::uint16_t> inputControlIndices;`
- L1458 _public member_ `DynArray<std::uint16_t> outputControlIndices;`
- L1459 _public member_ `DynArray<float> outputControlWeights;`
- L1461 _public function_ `explicit RawRBFPoseExt(MemoryResource* memRes) : inputControlIndices`
- L1468 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawRBFSolver`  
`struct RawRBFSolver`  
_L1478-1544_
- L1479 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1480 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1481 _public member_ `String<char> name;`
- L1482 _public member_ `DynArray<std::uint16_t> rawControlIndices;`
- L1483 _public member_ `DynArray<std::uint16_t> poseIndices;`
- L1484 _public member_ `DynArray<float> rawControlValues;`
- L1485 _public member_ `float radius;`
- L1486 _public member_ `float weightThreshold;`
- L1487 _public member_ `std::uint16_t solverType;`
- L1488 _public member_ `std::uint16_t automaticRadius;`
- L1489 _public member_ `std::uint16_t distanceMethod;`
- L1490 _public member_ `std::uint16_t normalizeMethod;`
- L1491 _public member_ `std::uint16_t functionType;`
- L1492 _public member_ `std::uint16_t twistAxis;`
- L1493 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1495 _public function_ `explicit RawRBFSolver(MemoryResource* memRes) : size`
- L1514 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawRBFBehavior`  
`struct RawRBFBehavior`  
_L1546-1566_
- L1547 _public member_ `RawLODMapping lodSolverMapping;`
- L1548 _public member_ `Vector<RawRBFSolver> solvers;`
- L1549 _public member_ `Vector<RawRBFPose> poses;`
- L1551 _public function_ `explicit RawRBFBehavior(MemoryResource* memRes) : lodSolverMapping`
- L1558 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawRBFBehaviorExt`  
`struct RawRBFBehaviorExt`  
_L1568-1584_
- L1569 _public member_ `Vector<String<char>> poseControlNames;`
- L1570 _public member_ `Vector<RawRBFPoseExt> poses;`
- L1572 _public function_ `explicit RawRBFBehaviorExt(MemoryResource* memRes) : poseControlNames`
- L1578 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawJointRepresentation`  
`struct RawJointRepresentation`  
_L1586-1600_
- L1587 _public member_ `std::uint16_t translation;`
- L1588 _public member_ `std::uint16_t rotation;`
- L1589 _public member_ `std::uint16_t scale;`
- L1592 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawJointBehaviorMetadata`  
`struct RawJointBehaviorMetadata`  
_L1602-1614_
- L1603 _public member_ `Vector<RawJointRepresentation> jointRepresentations;`
- L1605 _public function_ `explicit RawJointBehaviorMetadata(MemoryResource* memRes) : jointRepresentations`
- L1610 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawTwist`  
`struct RawTwist`  
_L1616-1640_
- L1617 _public member_ `DynArray<float> twistBlendWeights;`
- L1618 _public member_ `DynArray<std::uint16_t> twistOutputJointIndices;`
- L1619 _public member_ `DynArray<std::uint16_t> twistInputControlIndices;`
- L1620 _public member_ `std::uint16_t twistAxis;`
- L1622 _public function_ `explicit RawTwist(MemoryResource* memRes) : twistBlendWeights`
- L1630 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawSwing`  
`struct RawSwing`  
_L1642-1666_
- L1643 _public member_ `DynArray<float> swingBlendWeights;`
- L1644 _public member_ `DynArray<std::uint16_t> swingOutputJointIndices;`
- L1645 _public member_ `DynArray<std::uint16_t> swingInputControlIndices;`
- L1646 _public member_ `std::uint16_t twistAxis;`
- L1648 _public function_ `explicit RawSwing(MemoryResource* memRes) : swingBlendWeights`
- L1656 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawTwistSwingBehavior`  
`struct RawTwistSwingBehavior`  
_L1668-1684_
- L1669 _public member_ `Vector<RawTwist> twists;`
- L1670 _public member_ `Vector<RawSwing> swings;`
- L1672 _public function_ `explicit RawTwistSwingBehavior(MemoryResource* memRes) : twists`
- L1678 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMLOperation`  
`struct RawMLOperation`  
_L1686-1710_
- L1687 _public member_ `DynArray<std::uint32_t> parameters;`
- L1688 _public member_ `DynArray<std::uint16_t> mlOperationSetDependencyIndices;`
- L1689 _public member_ `DynArray<std::uint16_t> mlOperationDependencyIndices;`
- L1690 _public member_ `std::uint16_t operationType;`
- L1692 _public function_ `explicit RawMLOperation(MemoryResource* memRes) : parameters`
- L1700 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMachineLearnedBehaviorTypeData`  
`struct RawMachineLearnedBehaviorTypeData`  
_L1712-1728_
- L1713 _public member_ `Vector<RawLODMapping> lodMLOperationMappings;`
- L1714 _public member_ `Matrix<RawMLOperation> operations;`
- L1716 _public function_ `explicit RawMachineLearnedBehaviorTypeData(MemoryResource* memRes) : lodMLOperationMappings`
- L1722 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMachineLearnedBehaviorJoints`  
`struct RawMachineLearnedBehaviorJoints`  
_L1730-1754_
- L1731 _public member_ `DynArray<std::uint16_t> parameterKeys;`
- L1732 _public member_ `DynArray<std::uint16_t> parameterValues;`
- L1733 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1734 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1736 _public function_ `explicit RawMachineLearnedBehaviorJoints(MemoryResource* memRes) : parameterKeys`
- L1744 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::RawMachineLearnedBehaviorExt`  
`struct RawMachineLearnedBehaviorExt`  
_L1756-1772_
- L1757 _public member_ `Vector<RawMachineLearnedBehaviorTypeData> mlbTypeData;`
- L1758 _public member_ `RawMachineLearnedBehaviorJoints mlbJoints;`
- L1760 _public function_ `explicit RawMachineLearnedBehaviorExt(MemoryResource* memRes) : mlbTypeData`
- L1766 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `dnac::DNA`  
`struct DNA`  
_L1774-1972_
- L1775 _public member_ `MemoryResource* memRes;`
- L1776 _public member_ `Signature<3> signature{{'D', 'N', 'A'}};`
- L1777 _public member_ `Version version{FileVersion::latest};`
- L1778 _public member_ `IndexTable indexTable;`
- L1779 _public member_ `Layer<sid4("desc"), rev(1, 1), RawDescriptor, FileVersion::v22> descrip`
- L1780 _public member_ `Layer<sid4("defn"), rev(1, 1), RawDefinition, FileVersion::v22> definit`
- L1781 _public member_ `Layer<sid4("bhvr"), rev(1, 1), RawBehavior, FileVersion::v22> behav`
- L1782 _public member_ `Layer<sid4("geom"), rev(1, 1), RawGeometry, FileVersion::v22> geome`
- L1783 _public member_ `Layer<sid4("mlbh"), rev(1, 0), RawMachineLearnedBehavior, FileVersion::v23> machineLearnedBehav`
- L1784 _public member_ `Layer<sid4("rbfb"), rev(1, 0), RawRBFBehavior, FileVersion::v24> rbfBehav`
- L1785 _public member_ `Layer<sid4("rbfe"), rev(1, 0), RawRBFBehaviorExt, FileVersion::v25> rbfBehavior`
- L1786 _public member_ `Layer<sid4("jbmd"), rev(1, 0), RawJointBehaviorMetadata, FileVersion::v24> jointBehaviorMetad`
- L1787 _public member_ `Layer<sid4("twsw"), rev(1, 0), RawTwistSwingBehavior, FileVersion::v24> twistSwingBehav`
- L1788 _public member_ `Layer<sid4("mlbe"), rev(1, 0), RawMachineLearnedBehaviorExt, FileVersion::v26> machineLearnedBehavior`
- L1789 _public member_ `Layer<sid4("dsce"), rev(1, 0), RawDescriptorExt, FileVersion::v27> descriptor`
- L1791 _public typedef_ `using Layers = LayerContainer<decltype(descriptor), decltype(definition), decltype(behavior), decltype(geometry), decltype(machineLearnedBehavior), decltype(rbfBehavior), decltype(rbfBehaviorExt), decltype(jointBehaviorMetadata), decltype(twistSwingBehavior), decltype(machineLearnedBehaviorExt), decltype(descriptorExt)>;`
- L1802 _public member_ `Layers layers;`
- L1804 _public function_ `DNA(UnknownLayerPolicy unknownPolicy, UpgradeFormatPolicy upgradePolicy, MemoryResource* memRes_) : memRes`
- L1834 _public function_ `explicit DNA(MemoryResource* memRes_) : DNA`
- L1839 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1857 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> v21)`
- L1886 _public function_ `template<class Archive, typename AnyVersion> IfHigher<AnyVersion, FileVersion::v21> load(Archive& archive, AnyVersion)`
- L1912 _public function_ `template<class Archive, typename AnyVersion> IfHigher<AnyVersion, FileVersion::v21> save(Archive& archive, AnyVersion)`
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
- L91 _namespace_ `namespace dnac`
- L100 _function_ `template<typename Archive> void load(Archive& archive, FaceWindingOrder& value)` (scope `dnac`)
- L108 _function_ `template<typename Archive> void save(Archive& archive, FaceWindingOrder& value)` (scope `dnac`)
- L153 _function_ `static constexpr std::uint32_t sid4(const char* name)` (scope `dnac`)
- L158 _function_ `static constexpr std::uint32_t rev(std::uint16_t generation, std::uint16_t version)` (scope `dnac`)
- L162 _function_ `static constexpr std::uint16_t high16(std::uint32_t packed)` (scope `dnac`)
- L166 _function_ `static constexpr std::uint16_t low16(std::uint32_t packed)` (scope `dnac`)
- L183 _typedef_ `using Dispatch = Dispatcher<FileVersion, FileVersion::v21, FileVersion::v22, FileVersion::v23, FileVersion::v24, FileVersion::v25, FileVersion::v26, FileVersion::v27, FileVersion::v28>;` (scope `dnac`)
- L194 _typedef_ `template<typename A, FileVersion B> using IfHigher = typename std::enable_if<(A::value() > B), void>::type;` (scope `dnac`)
- L197 _typedef_ `template<typename A, FileVersion B> using IfLower = typename std::enable_if<(A::value() < B), void>::type;` (scope `dnac`)
- L380 _function_ `std::remove_if(entries.begin(), entries.end(), [id, version](const Index& index) { return (index.id == id) && (index.version == version); }), entries.end());` (scope `dnac::IndexTable::destroy`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/DNACalibDNAReaderImpl.h` (Private)


#### class `dnac::DNACalibDNAReaderImpl`  
`class DNACalibDNAReaderImpl : public ReaderImpl<DNACalibDNAReader>, public WriterImpl<dna::Writer>`  
_L17-74_
- inherits: `ReaderImpl<DNACalibDNAReader>,WriterImpl<dna::Writer>`
- L19 _public prototype_ `explicit DNACalibDNAReaderImpl(MemoryResource* memRes_);`
- L21 _public prototype_ `virtual ~DNACalibDNAReaderImpl();`
- L23 _public prototype_ `void unload(DataLayer layer) override;`
- L25 _public prototype_ `DNACalibDNAReaderImpl(const DNACalibDNAReaderImpl&) = delete;`
- L26 _public prototype_ `DNACalibDNAReaderImpl& operator=(const DNACalibDNAReaderImpl&) = delete;`
- L28 _public prototype_ `DNACalibDNAReaderImpl(DNACalibDNAReaderImpl&&) = delete;`
- L29 _public prototype_ `DNACalibDNAReaderImpl& operator=(DNACalibDNAReaderImpl&&) = delete;`
- L32 _public prototype_ `void setNeutralJointTranslations(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);`
- L33 _public prototype_ `void setNeutralJointTranslations(RawVector3Vector&& translations);`
- L34 _public prototype_ `void setNeutralJointTranslation(std::uint16_t index, const Vector3& translation);`
- L37 _public prototype_ `void setNeutralJointRotations(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);`
- L38 _public prototype_ `void setNeutralJointRotations(RawVector3Vector&& rotations);`
- L39 _public prototype_ `void setNeutralJointRotation(std::uint16_t index, const Vector3& rotation);`
- L42 _public prototype_ `void setJointGroupValues(std::uint16_t jointGroupIndex, AlignedDynArray<float>&& values);`
- L45 _public prototype_ `void setVertexPositions(std::uint16_t meshIndex, ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);`
- L49 _public prototype_ `void setVertexPositions(std::uint16_t meshIndex, RawVector3Vector&& positions);`
- L52 _public prototype_ `void setBlendShapeTargetDeltas(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);`
- L57 _public prototype_ `void setBlendShapeTargetDeltas(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, RawVector3Vector&& deltas);`
- L60 _public prototype_ `void setBlendShapeTargetVertexIndices(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, ConstArrayView<std::uint32_t> vertexIndices);`
- L64 _public prototype_ `void pruneBlendShapeTargets(float threshold);`
- L66 _public prototype_ `void removeMeshes(ConstArrayView<std::uint16_t> meshIndices);`
- L67 _public prototype_ `void removeJoints(ConstArrayView<std::uint16_t> jointIndices);`
- L68 _public prototype_ `void removeJointAnimations(ConstArrayView<std::uint16_t> jointIndex);`
- L69 _public prototype_ `void removeBlendShapes(ConstArrayView<std::uint16_t> blendShapeIndices);`
- L70 _public prototype_ `void removeAnimatedMaps(ConstArrayView<std::uint16_t> animatedMapIndices);`
- L72 _public prototype_ `void convertToTranslationUnit(TranslationUnit translationUnit);`
- L73 _public prototype_ `void convertToRotationUnit(RotationUnit rotationUnit);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/DenormalizedData.h` (Private)


#### struct `dnac::DenormalizedData`  
`template<class Reader> struct DenormalizedData`  
_L25-357_
- L26 _public member_ `LODMapping jointVariableAttributeIndices;`
- L27 _public member_ `LODMapping meshBlendShapeMappingIndices;`
- L28 _public member_ `Matrix<std::uint16_t> rbfPoseJointOutputIndices;`
- L29 _public member_ `Matrix<float> rbfPoseJointOutputValues;`
- L30 _public member_ `Matrix<std::uint16_t> rbfBlendShapeChannelOutputIndices;`
- L31 _public member_ `Matrix<std::uint16_t> rbfAnimatedMapOutputIndices;`
- L32 _public member_ `Vector<Matrix<std::uint32_t>> mlOperationParameters;`
- L33 _public member_ `Vector<Matrix<std::uint16_t>> mlDependencyOperationSetIndices;`
- L34 _public member_ `Vector<Matrix<std::uint16_t>> mlDependencyOperationIndices;`
- L36 _public function_ `explicit DenormalizedData(MemoryResource* memRes) : jointVariableAttributeIndices`
- L49 _public function_ `void populate(const Reader* source)`
- L61 _public function_ `void populateJointVariableAttributeIndices(const Reader* source)`
- L174 _public function_ `void populateMeshBlendShapeMappingIndices(const Reader* source)`
- L203 _public function_ `void populateRBFPoseJointOutputIndices(const Reader* source)`
- L229 _public function_ `void populateRBFPoseJointOutputValues(const Reader* source)`
- L280 _public function_ `void populateRBFBlendShapeOutputIndices(const Reader* source)`
- L300 _public function_ `void populateRBFAnimatedMapOutputIndices(const Reader* source)`
- L319 _public function_ `void populateMLOperationParameters(const Reader* source)`
- L334 _public function_ `void populateMLDependencyOperationSetIndices(const Reader* source)`
- L346 _public function_ `void populateMLDependencyOperationIndices(const Reader* source)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace dnac`
- L88 _function_ `auto isJointInLOD = [source](std::uint16_t jointIndex, std::uint16_t lod)` (scope `dnac::DenormalizedData::populateJointVariableAttributeIndices`)
- L93 _function_ `auto getNumMLAttributesPerJoint = [source]()` (scope `dnac::DenormalizedData::populateJointVariableAttributeIndices`)
- L184 _function_ `auto isMappingNeeded = [&meshIndices, &blendShapeIndices](const MeshBlendShapeChannelMapping& mapping)` (scope `dnac::DenormalizedData::populateMeshBlendShapeMappingIndices`)
- L234 _function_ `auto jointIndexToJointGroupMap = [&]()` (scope `dnac::DenormalizedData::populateRBFPoseJointOutputValues`)
- L246 _function_ `const auto indexOf = [](ConstArrayView<std::uint16_t> container, std::uint16_t val)` (scope `dnac::DenormalizedData::populateRBFPoseJointOutputValues`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/LODConstraint.h` (Private)


#### class `dnac::LODConstraint`  
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

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/LODMapping.h` (Private)


#### class `dnac::LODMapping`  
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

- L18 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/ReaderImpl.h` (Private)


#### class `dnac::ReaderImpl`  
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

- L21 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/SurjectiveMapping.h` (Private)


#### struct `dnac::SurjectiveMapping`  
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

#### struct `dnac::SurjectiveMapping::Pair`  
`struct Pair`  
_L22-25_
- L23 _public member_ `TFrom from;`
- L24 _public member_ `TTo to;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace dnac`
- L90 _function_ `std::transform(target.begin(), target.end(), target.begin(), [&mapping](U oldValue) { return mapping.at(oldValue); });` (scope `dnac::SurjectiveMapping::update`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/WriterImpl.h` (Private)


#### class `dnac::WriterImpl`  
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

- L24 _namespace_ `namespace dnac`
- L28 _function_ `ensureHasSize(TContainer& target, std::size_t size)` (scope `dnac`)
- L44 _function_ `template<class TContainer, typename U> typename std::enable_if<std::is_integral<U>::value, typename TContainer::value_type&>::type getAt(TContainer& target, U index)` (scope `dnac`)
- L50 _function_ `template<class TContainer, typename TSize, typename TValue> typename std::enable_if<std::is_integral<TSize>::value>::type setAt(TContainer& target, TSize index, const TValue& value)` (scope `dnac`)
- L388 _typedef_ `using CharStringPair = std::tuple<String<char>, String<char>>;` (scope `dnac::WriterImpl::setMetaData`)
- L389 _function_ `auto it = std::find_if(dna.descriptor.metadata.begin(), dna.descriptor.metadata.end(), [&key](const CharStringPair& kv) { auto& k = std::get<0>(kv); return (std::strlen(key) == k.size() && std::strncmp(k.data(), key, k.size()) == 0); });` (scope `dnac::WriterImpl::setMetaData`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/filters/AnimatedMapFilter.h` (Private)


#### class `dnac::AnimatedMapFilter`  
`class AnimatedMapFilter`  
_L14-29_
- L16 _public prototype_ `explicit AnimatedMapFilter(MemoryResource* memRes_);`
- L17 _public prototype_ `void configure(std::uint16_t animatedMapCount, UnorderedSet<std::uint16_t> allowedAnimatedMapIndices, Matrix<std::uint16_t> lodIndices);`
- L20 _public prototype_ `void apply(RawDefinition& dest);`
- L21 _public prototype_ `void apply(RawBehavior& dest);`
- L22 _public prototype_ `bool passes(std::uint16_t index) const;`
- L25 _private member_ `MemoryResource* memRes;`
- L26 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L27 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`
- L28 _private member_ `Matrix<std::uint16_t> animatedMapLODIndices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/filters/BlendShapeFilter.h` (Private)


#### class `dnac::BlendShapeFilter`  
`class BlendShapeFilter`  
_L15-32_
- L17 _public prototype_ `explicit BlendShapeFilter(MemoryResource* memRes_);`
- L18 _public prototype_ `void configure(std::uint16_t blendShapeCount, UnorderedSet<std::uint16_t> allowedBlendShapeIndices, Vector<std::uint16_t> blendShapeLODs);`
- L21 _public prototype_ `void apply(RawDefinition& dest);`
- L22 _public prototype_ `void apply(RawBehavior& dest);`
- L23 _public prototype_ `void apply(RawMesh& dest);`
- L24 _public prototype_ `bool passes(std::uint16_t index) const;`
- L25 _public prototype_ `std::uint16_t remapped(std::uint16_t index) const;`
- L28 _private member_ `MemoryResource* memRes;`
- L29 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L30 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`
- L31 _private member_ `Vector<std::uint16_t> newBlendShapeLODs;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/filters/JointFilter.h` (Private)


#### class `dnac::JointFilter`  
`class JointFilter`  
_L18-43_
- L26 _public prototype_ `explicit JointFilter(MemoryResource* memRes_);`
- L27 _public prototype_ `void configure(std::uint16_t jointCount, UnorderedSet<std::uint16_t> allowedJointIndices, Option option_ = Option::All);`
- L28 _public prototype_ `void apply(RawDefinition& dest);`
- L29 _public prototype_ `void apply(RawBehavior& dest);`
- L30 _public prototype_ `void apply(RawVertexSkinWeights& dest);`
- L31 _public prototype_ `void apply(RawJointBehaviorMetadata& dest);`
- L32 _public prototype_ `void apply(RawTwistSwingBehavior& dest);`
- L33 _public prototype_ `bool passes(std::uint16_t index) const;`
- L34 _public prototype_ `std::uint16_t remapped(std::uint16_t oldIndex) const;`
- L35 _public prototype_ `std::uint16_t filteredJointCount() const;`
- L38 _private member_ `MemoryResource* memRes;`
- L39 _private member_ `UnorderedSet<std::uint16_t> passingIndices;`
- L40 _private member_ `UnorderedMap<std::uint16_t, std::uint16_t> remappedIndices;`
- L41 _private member_ `Option option;`
- L42 _private member_ `std::uint16_t rootJointIndex;`

#### enum `dnac::JointFilter::Option`  
`enum class Option`  
_L20-23_
- L21 _public enumerator_ `All`
- L22 _public enumerator_ `AnimationOnly`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/filters/MeshFilter.h` (Private)


#### class `dnac::MeshFilter`  
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

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/dna/filters/Remap.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dnac`
- L11 _function_ `template<typename T> inline void remap(T originalCount, const UnorderedSet<T>& keptIndices, UnorderedMap<T, T>& mapping)` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/types/BoundingBox.h` (Private)


#### class `dnac::BoundingBox`  
`class BoundingBox`  
_L13-69_
- L15 _public member_ `static constexpr float defaultAlpha = 0.0003f;`
- L19 _private typedef_ `template<typename TIter> using unqualified_iter_value_type = typename std::remove_cv<typename std::iterator_traits<TIter>::value_type>::type;`
- L24 _public function_ `BoundingBox(TIter begin, TIter end, float alpha) : min`
- L40 _public function_ `template<typename TContainer> explicit BoundingBox(TContainer container, float alpha = defaultAlpha) : BoundingBox(std::begin(container), std::end(container), alpha)`
- L44 _public function_ `bool contains(fvec2 point) const`
- L48 _public function_ `float distance(fvec2 point) const`
- L54 _public function_ `bool overlaps(const BoundingBox& other) const`
- L58 _public function_ `fvec2 getMin() const`
- L62 _public function_ `fvec2 getMax() const`
- L67 _private member_ `fvec2 min;`
- L68 _private member_ `fvec2 max;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/types/Triangle.h` (Private)


#### class `dnac::Triangle`  
`class Triangle`  
_L11-31_
- L14 _public prototype_ `Triangle(const fvec2& a, const fvec2& b, const fvec2& c);`
- L15 _public prototype_ `explicit Triangle(const std::array<fvec2, 3>& vertices);`
- L17 _public prototype_ `fvec3 getBarycentricCoords(const fvec2& point) const;`
- L19 _public prototype_ `fvec2 A() const;`
- L20 _public prototype_ `fvec2 B() const;`
- L21 _public prototype_ `fvec2 C() const;`
- L24 _private member_ `fvec2 a;`
- L25 _private member_ `fvec2 v0;` — b-a
- L26 _private member_ `fvec2 v1;` — c-a;
- L27 _private member_ `float d00;` — v0 dot v0
- L28 _private member_ `float d01;` — v0 dot v1
- L29 _private member_ `float d11;` — v1 dot v1
- L30 _private member_ `float denom;` — d00 * d11 - d01 * d01;

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/types/UVBarycentricMapping.h` (Private)


#### class `dnac::UVBarycentricMapping`  
`class UVBarycentricMapping`  
_L11-34_
- L13 _public typedef_ `using TrianglePositionIndicesPair = std::tuple<Triangle, std::array<std::uint32_t, 3u>>;`
- L14 _public typedef_ `using BarycentricPositionIndicesPair = std::tuple<fvec3, ConstArrayView<std::uint32_t>>;`
- L17 _public prototype_ `UVBarycentricMapping(const std::function<ConstArrayView<std::uint32_t>(std::uint32_t)>& faceGetter, ConstArrayView<std::uint32_t> vertexPositionIndices, ConstArrayView<std::uint32_t> textureCoordinateUVIndices, ConstArrayView<float> Us, ConstArrayView<float> Vs, std::uint32_t faceCount, MemoryResource* memRes);`
- L25 _public prototype_ `BarycentricPositionIndicesPair getBarycentric(fvec2 uv) const;`
- L26 _public prototype_ `const Triangle& getTriangle(std::uint32_t index) const;`
- L27 _public prototype_ `ConstArrayView<std::uint32_t> getTrianglePositionIndices(std::uint32_t index) const;`
- L28 _public prototype_ `ConstArrayView<BoundingBox> getBoundingBoxes() const;`
- L31 _private member_ `Vector<Triangle> triangles;`
- L32 _private member_ `Vector<BoundingBox> boundingBoxes;`
- L33 _private member_ `Vector<std::array<std::uint32_t, 3u>> trianglePositionIndices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/utils/Algorithm.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dnac`
- L9 _function_ `inline fmat4 extractTranslationMatrix(const fmat4& transformationMatrix)` (scope `dnac`)
- L17 _function_ `inline fvec3 extractScaleVector(const fmat4& transformationMatrix)` (scope `dnac`)
- L25 _function_ `inline fmat4 extractRotationMatrix(const fmat4& transformationMatrix)` (scope `dnac`)
- L35 _function_ `inline fvec3 extractTranslationVector(const fmat4& transformationMatrix)` (scope `dnac`)
- L39 _function_ `inline frad3 extractRotationVector(const fmat4& transformationMatrix)` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/utils/Extd.h` (Private)


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

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/utils/FormatString.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dnac`
- L10 _function_ `template<typename... Args> String<char> formatString(MemoryResource* memRes, const char* format, Args&&... args)` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/utils/Macros.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define FORCE_INLINE __forceinline`
- L9 _macro_ `#define FORCE_INLINE inline __attribute__((always_inline))`
- L15 _macro_ `#define ASSUME_TRUE(condition) __assume(condition)`
- L17 _macro_ `#define ASSUME_TRUE(condition) \`
- L26 _macro_ `#define UNUSED(x) static_cast<void>(x)`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Private/dnacalib/utils/ScopedEnumEx.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dnac`
- L10 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator&(TEnum lhs, TEnum rhs)` (scope `dnac`)
- L11 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dnac::operator &`)
- L16 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator|(TEnum lhs, TEnum rhs)` (scope `dnac`)
- L17 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dnac::operator |`)
- L22 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator^(TEnum lhs, TEnum rhs)` (scope `dnac`)
- L23 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dnac::operator ^`)
- L28 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator~(TEnum value)` (scope `dnac`)
- L29 _typedef_ `using Underlying = typename std::underlying_type<TEnum>::type;` (scope `dnac::operator ~`)
- L34 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator&=(TEnum& lhs, TEnum rhs)` (scope `dnac`)
- L39 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator|=(TEnum& lhs, TEnum rhs)` (scope `dnac`)
- L44 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type operator^=(TEnum& lhs, TEnum rhs)` (scope `dnac`)
- L49 _function_ `template<typename TEnum> typename std::enable_if<std::is_enum<TEnum>::value, bool>::type contains(TEnum lhs, TEnum rhs)` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/DNACalibLib.h` (Public)


#### class `FDNACalibLib`  
`class FDNACalibLib : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNACalibLib, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNACalibLib, Log, All);`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/Command.h` (Public)


#### class `dnac::Command`  
`class DNACAPI Command`  
_L16-20_
- desc: @brief Command is an abstract class whose implementations are expected to modify the DNA provided in the run() method in some way.
- L18 _public prototype_ `virtual ~Command();`
- L19 _public prototype_ `virtual void run(DNACalibDNAReader* output) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/DNACalib.h` (Public)
_(no declarations extracted)_

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define DNACAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define DNACAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define DNACAPI` — Build or use static library

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/CalculateMeshLowerLODsCommand.h` (Public)


#### class `dnac::CalculateMeshLowerLODsCommand`  
`class CalculateMeshLowerLODsCommand : public Command`  
_L19-45_
- inherits: `Command`
- desc: @brief CalculateMeshLowerLODsCommand is used to recalculate vertex positions for lower LOD meshes of the specified mesh. @note The calculation is done based on vertex positions of the specified mesh and vertex texture coordinates of its lower LOD meshes.
- L21 _public prototype_ `DNACAPI explicit CalculateMeshLowerLODsCommand(MemoryResource* memRes = nullptr);`
- L23 _public prototype_ `DNACAPI explicit CalculateMeshLowerLODsCommand(std::uint16_t meshIndex, MemoryResource* memRes = nullptr);`
- L25 _public prototype_ `DNACAPI ~CalculateMeshLowerLODsCommand();`
- L27 _public prototype_ `CalculateMeshLowerLODsCommand(const CalculateMeshLowerLODsCommand&) = delete;`
- L28 _public prototype_ `CalculateMeshLowerLODsCommand& operator=(const CalculateMeshLowerLODsCommand&) = delete;`
- L30 _public prototype_ `DNACAPI CalculateMeshLowerLODsCommand(CalculateMeshLowerLODsCommand&&);`
- L31 _public prototype_ `DNACAPI CalculateMeshLowerLODsCommand& operator=(CalculateMeshLowerLODsCommand&&);`
- L38 _public prototype_ `DNACAPI void setMeshIndex(std::uint16_t meshIndex);` — @brief Method for setting the index of the mesh to calculate lower LOD meshes from. @param meshIndex The index of the mesh.
- L40 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L44 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/ClearBlendShapesCommand.h` (Public)


#### class `dnac::ClearBlendShapesCommand`  
`class ClearBlendShapesCommand : public Command`  
_L20-37_
- inherits: `Command`
- desc: @brief ClearBlendShapesCommand is used to clear all blend shapes data from a DNA. @note This command clears blend shape target deltas and blend shape animation data. By doing so, it transforms the DNA to be "joints only".
- L22 _public prototype_ `DNACAPI explicit ClearBlendShapesCommand(MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~ClearBlendShapesCommand();`
- L26 _public prototype_ `ClearBlendShapesCommand(const ClearBlendShapesCommand&) = delete;`
- L27 _public prototype_ `ClearBlendShapesCommand& operator=(const ClearBlendShapesCommand&) = delete;`
- L29 _public prototype_ `DNACAPI ClearBlendShapesCommand(ClearBlendShapesCommand&&);`
- L30 _public prototype_ `DNACAPI ClearBlendShapesCommand& operator=(ClearBlendShapesCommand&&);`
- L32 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L36 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/CommandSequence.h` (Public)


#### class `dnac::CommandSequence`  
`class CommandSequence : public Command`  
_L20-95_
- inherits: `Command`
- desc: @brief CommandSequence is used to run a sequence of commands on the same DNA. @note Commands will be run in the order in which they were added to the sequence. @note CommandSequence holds pointers to commands, but does not own them.
- L22 _public prototype_ `DNACAPI explicit CommandSequence(MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~CommandSequence();`
- L26 _public prototype_ `CommandSequence(const CommandSequence&) = delete;`
- L27 _public prototype_ `CommandSequence& operator=(const CommandSequence&) = delete;`
- L29 _public prototype_ `DNACAPI CommandSequence(CommandSequence&&);`
- L30 _public prototype_ `DNACAPI CommandSequence& operator=(CommandSequence&&);`
- L32 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L39 _public prototype_ `DNACAPI void add(Command* command);` — @brief Method for adding a command to a sequence of commands to run. @param command The command to add.
- L46 _public prototype_ `DNACAPI void add(ArrayView<Command> commands);` — @brief Method for adding multiple commands to a sequence of commands to run. @param commands The commands to add.
- L49 _public function_ `template<class... Commands> void add(Commands... commands)`
- L62 _public prototype_ `DNACAPI void remove(Command* command);` — @brief Method for removing a command from the sequence of commands to run. @param command The command to remove.
- L69 _public prototype_ `DNACAPI void remove(ArrayView<Command> commands);` — @brief Method for removing an array of commands from the sequence of commands to run. @param commands The commands to remove.
- L72 _public function_ `template<class... Commands> void remove(Commands... commands)`
- L85 _public prototype_ `DNACAPI bool contains(Command* command) const;` — @brief Method for checking if the provided command is part of the command sequence. @param command The command to check.
- L90 _public prototype_ `DNACAPI std::size_t size() const;` — @brief Number of commands in command sequence.
- L94 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/ConditionalCommand.h` (Public)


#### class `dnac::ConditionalCommand`  
`template<class TCommand, class TCondition> class ConditionalCommand : public Command`  
_L15-66_
- inherits: `Command`
- desc: @brief ConditionalCommand is used to run a command if the specified condition is met.
- L17 _private typedef_ `using CommandType = TCommand;`
- L18 _private typedef_ `using ConditionType = TCondition;`
- L21 _public function_ `ConditionalCommand() : command`
- L26 _public function_ `ConditionalCommand(CommandType* command_, ConditionType condition_) : command`
- L31 _public prototype_ `~ConditionalCommand() = default;`
- L33 _public prototype_ `ConditionalCommand(const ConditionalCommand&) = delete;`
- L34 _public prototype_ `ConditionalCommand& operator=(const ConditionalCommand&) = delete;`
- L36 _public prototype_ `ConditionalCommand(ConditionalCommand&&) = default;`
- L37 _public prototype_ `ConditionalCommand& operator=(ConditionalCommand&&) = default;`
- L44 _public function_ `void setCommand(Command* command_)` — @brief Method for setting the command to run. @param command_ The command to run.
- L53 _public function_ `void setCondition(ConditionType condition_)` — @brief Method for setting the condition under which the command should run. @param condition_ The condition that should be met.
- L57 _public function_ `void run(DNACalibDNAReader* output) override`
- L64 _private member_ `CommandType* command;`
- L65 _private member_ `ConditionType condition;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace dnac`
- L69 _function_ `template<class TCommand, class TCondition> ConditionalCommand<TCommand, TCondition> makeConditional(TCommand* command, TCondition condition)` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/ConvertUnitsCommand.h` (Public)


#### class `dnac::ConvertUnitsCommand`  
`class ConvertUnitsCommand : public Command`  
_L16-38_
- inherits: `Command`
- desc: @brief ConvertUnitsCommand is used to perform unit conversions over all relevant data in a DNA.
- L18 _public prototype_ `DNACAPI explicit ConvertUnitsCommand(MemoryResource* memRes = nullptr);`
- L19 _public prototype_ `DNACAPI explicit ConvertUnitsCommand(TranslationUnit translationUnit, RotationUnit rotationUnit, MemoryResource* memRes = nullptr);`
- L23 _public prototype_ `DNACAPI ~ConvertUnitsCommand();`
- L25 _public prototype_ `ConvertUnitsCommand(const ConvertUnitsCommand&) = delete;`
- L26 _public prototype_ `ConvertUnitsCommand& operator=(const ConvertUnitsCommand&) = delete;`
- L28 _public prototype_ `DNACAPI ConvertUnitsCommand(ConvertUnitsCommand&&);`
- L29 _public prototype_ `DNACAPI ConvertUnitsCommand& operator=(ConvertUnitsCommand&&);`
- L31 _public prototype_ `DNACAPI void setTranslationUnit(TranslationUnit translationUnit);`
- L32 _public prototype_ `DNACAPI void setRotationUnit(RotationUnit rotationUnit);`
- L33 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L37 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/PruneBlendShapeTargetsCommand.h` (Public)


#### class `dnac::PruneBlendShapeTargetsCommand`  
`class PruneBlendShapeTargetsCommand : public Command`  
_L19-43_
- inherits: `Command`
- desc: @brief PruneBlendShapeTargetsCommand is used to prune blend shape target deltas whose absolute magnitude is less than or equal to the specified threshold.
- L21 _public prototype_ `DNACAPI explicit PruneBlendShapeTargetsCommand(MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI explicit PruneBlendShapeTargetsCommand(float threshold, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~PruneBlendShapeTargetsCommand();`
- L26 _public prototype_ `PruneBlendShapeTargetsCommand(const PruneBlendShapeTargetsCommand&) = delete;`
- L27 _public prototype_ `PruneBlendShapeTargetsCommand& operator=(const PruneBlendShapeTargetsCommand&) = delete;`
- L29 _public prototype_ `DNACAPI PruneBlendShapeTargetsCommand(PruneBlendShapeTargetsCommand&&);`
- L30 _public prototype_ `DNACAPI PruneBlendShapeTargetsCommand& operator=(PruneBlendShapeTargetsCommand&&);`
- L37 _public prototype_ `DNACAPI void setThreshold(float threshold);` — @brief Method for setting the threshold for pruning blend shape target deltas. @param threshold The threshold to use.
- L38 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L42 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RemoveAnimatedMapCommand.h` (Public)


#### class `dnac::RemoveAnimatedMapCommand`  
`class RemoveAnimatedMapCommand : public Command`  
_L18-53_
- inherits: `Command`
- desc: @brief RemoveAnimatedMapCommand is used to remove animated maps.
- L20 _public prototype_ `DNACAPI explicit RemoveAnimatedMapCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RemoveAnimatedMapCommand(std::uint16_t animatedMapIndex, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RemoveAnimatedMapCommand(ConstArrayView<std::uint16_t> animatedMapIndices, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RemoveAnimatedMapCommand();`
- L26 _public prototype_ `RemoveAnimatedMapCommand(const RemoveAnimatedMapCommand&) = delete;`
- L27 _public prototype_ `RemoveAnimatedMapCommand& operator=(const RemoveAnimatedMapCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RemoveAnimatedMapCommand(RemoveAnimatedMapCommand&&);`
- L30 _public prototype_ `DNACAPI RemoveAnimatedMapCommand& operator=(RemoveAnimatedMapCommand&&);`
- L39 _public prototype_ `DNACAPI void setAnimatedMapIndex(std::uint16_t animatedMapIndex);` — @brief Method for setting the index of the animated map to remove. @param animatedMapIndex The index of the animated map. @note Call to either setter overwrites previous setter calls. When running the command, the last set animated map(s) will be removed.
- L47 _public prototype_ `DNACAPI void setAnimatedMapIndices(ConstArrayView<std::uint16_t> animatedMapIndices);` — @brief Method for setting the indices of animated maps to remove. @param animatedMapIndices The animated map indices. @note Call to either setter overwrites previous setter calls. When running the command, the last set animated map(s) will be removed.
- L48 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L52 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RemoveBlendShapeCommand.h` (Public)


#### class `dnac::RemoveBlendShapeCommand`  
`class RemoveBlendShapeCommand : public Command`  
_L18-53_
- inherits: `Command`
- desc: @brief RemoveBlendShapeCommand is used to remove blend shapes.
- L20 _public prototype_ `DNACAPI explicit RemoveBlendShapeCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RemoveBlendShapeCommand(std::uint16_t blendShapeIndex, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RemoveBlendShapeCommand(ConstArrayView<std::uint16_t> blendShapeIndices, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RemoveBlendShapeCommand();`
- L26 _public prototype_ `RemoveBlendShapeCommand(const RemoveBlendShapeCommand&) = delete;`
- L27 _public prototype_ `RemoveBlendShapeCommand& operator=(const RemoveBlendShapeCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RemoveBlendShapeCommand(RemoveBlendShapeCommand&&);`
- L30 _public prototype_ `DNACAPI RemoveBlendShapeCommand& operator=(RemoveBlendShapeCommand&&);`
- L39 _public prototype_ `DNACAPI void setBlendShapeIndex(std::uint16_t blendShapeIndex);` — @brief Method for setting the index of the blend shape to remove. @param blendShapeIndex The index of the blend shape. @note Call to either setter overwrites previous setter calls. When running the command, the last set blend shape(s) will be removed.
- L47 _public prototype_ `DNACAPI void setBlendShapeIndices(ConstArrayView<std::uint16_t> blendShapeIndices);` — @brief Method for setting the indices of blend shapes to remove. @param blendShapeIndices The blend shape indices. @note Call to either setter overwrites previous setter calls. When running the command, the last set blend shape(s) will be removed.
- L48 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L52 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RemoveJointAnimationCommand.h` (Public)


#### class `dnac::RemoveJointAnimationCommand`  
`class RemoveJointAnimationCommand : public Command`  
_L18-53_
- inherits: `Command`
- desc: @brief RemoveJointAnimationCommand is used to remove joint animation data.
- L20 _public prototype_ `DNACAPI explicit RemoveJointAnimationCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RemoveJointAnimationCommand(std::uint16_t jointIndex, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RemoveJointAnimationCommand(ConstArrayView<std::uint16_t> jointIndices, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RemoveJointAnimationCommand();`
- L26 _public prototype_ `RemoveJointAnimationCommand(const RemoveJointAnimationCommand&) = delete;`
- L27 _public prototype_ `RemoveJointAnimationCommand& operator=(const RemoveJointAnimationCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RemoveJointAnimationCommand(RemoveJointAnimationCommand&&);`
- L30 _public prototype_ `DNACAPI RemoveJointAnimationCommand& operator=(RemoveJointAnimationCommand&&);`
- L39 _public prototype_ `DNACAPI void setJointIndex(std::uint16_t jointIndex);` — @brief Method for setting the index of a joint whose animation data to remove. @param jointIndex The index of the joint. @note Call to either setter overwrites previous setter calls. When running the command, the last set joint animation(s) will be removed.
- L47 _public prototype_ `DNACAPI void setJointIndices(ConstArrayView<std::uint16_t> jointIndices);` — @brief Method for setting the indices of joints whose animation data to remove. @param jointIndices The joint indices. @note Call to either setter overwrites previous setter calls. When running the command, the last set joint animation(s) will be removed.
- L48 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L52 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RemoveJointCommand.h` (Public)


#### class `dnac::RemoveJointCommand`  
`class RemoveJointCommand : public Command`  
_L18-53_
- inherits: `Command`
- desc: @brief RemoveJointCommand is used to remove joints.
- L20 _public prototype_ `DNACAPI explicit RemoveJointCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RemoveJointCommand(std::uint16_t jointIndex, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RemoveJointCommand(ConstArrayView<std::uint16_t> jointIndices, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RemoveJointCommand();`
- L26 _public prototype_ `RemoveJointCommand(const RemoveJointCommand&) = delete;`
- L27 _public prototype_ `RemoveJointCommand& operator=(const RemoveJointCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RemoveJointCommand(RemoveJointCommand&&);`
- L30 _public prototype_ `DNACAPI RemoveJointCommand& operator=(RemoveJointCommand&&);`
- L39 _public prototype_ `DNACAPI void setJointIndex(std::uint16_t jointIndex);` — @brief Method for setting the index of the joint to remove. @param jointIndex The index of the joint. @note Call to either setter overwrites previous setter calls. When running the command, the last set joint(s) will be removed.
- L47 _public prototype_ `DNACAPI void setJointIndices(ConstArrayView<std::uint16_t> jointIndices);` — @brief Method for setting the indices of joints to remove. @param jointIndices The joint indices. @note Call to either setter overwrites previous setter calls. When running the command, the last set joint(s) will be removed.
- L48 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L52 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RemoveMeshCommand.h` (Public)


#### class `dnac::RemoveMeshCommand`  
`class RemoveMeshCommand : public Command`  
_L18-52_
- inherits: `Command`
- desc: @brief RemoveMeshCommand is used to remove meshes.
- L20 _public prototype_ `DNACAPI explicit RemoveMeshCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RemoveMeshCommand(std::uint16_t meshIndex, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RemoveMeshCommand(ConstArrayView<std::uint16_t> meshIndices, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RemoveMeshCommand();`
- L26 _public prototype_ `RemoveMeshCommand(const RemoveMeshCommand&) = delete;`
- L27 _public prototype_ `RemoveMeshCommand& operator=(const RemoveMeshCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RemoveMeshCommand(RemoveMeshCommand&&);`
- L30 _public prototype_ `DNACAPI RemoveMeshCommand& operator=(RemoveMeshCommand&&);`
- L37 _public prototype_ `DNACAPI void setMeshIndex(std::uint16_t meshIndex);` — @brief Method for setting the index of the mesh to remove. @param meshIndex The index of the mesh.
- L45 _public prototype_ `DNACAPI void setMeshIndices(ConstArrayView<std::uint16_t> meshIndices);` — @brief Method for setting the indices of meshes to remove. @param meshIndices The mesh indices. @note Call to either setter overwrites previous setter calls. When running the command, the last set mesh(es) will be removed.
- L47 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L51 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RenameAnimatedMapCommand.h` (Public)


#### class `dnac::RenameAnimatedMapCommand`  
`class RenameAnimatedMapCommand : public Command`  
_L18-56_
- inherits: `Command`
- desc: @brief RenameAnimatedMapCommand is used to rename an animated map.
- L20 _public prototype_ `DNACAPI explicit RenameAnimatedMapCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RenameAnimatedMapCommand(std::uint16_t animatedMapIndex, const char* newName, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RenameAnimatedMapCommand(const char* oldName, const char* newName, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RenameAnimatedMapCommand();`
- L26 _public prototype_ `RenameAnimatedMapCommand(const RenameAnimatedMapCommand&) = delete;`
- L27 _public prototype_ `RenameAnimatedMapCommand& operator=(const RenameAnimatedMapCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RenameAnimatedMapCommand(RenameAnimatedMapCommand&&);`
- L30 _public prototype_ `DNACAPI RenameAnimatedMapCommand& operator=(RenameAnimatedMapCommand&&);`
- L39 _public prototype_ `DNACAPI void setName(std::uint16_t animatedMapIndex, const char* newName);` — @brief Method for setting a new name for animated map with given index. @param animatedMapIndex The index of the animated map whose name to change. @param newName The new name for the animated map.
- L50 _public prototype_ `DNACAPI void setName(const char* oldName, const char* newName);` — @brief Method for setting a new name for animated map with given name. @note The renaming will not happen if there is no animated map with given current name. @param oldName The current name of the animated map whose name to change. @param newName The new name for the animated map.
- L51 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L55 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RenameBlendShapeCommand.h` (Public)


#### class `dnac::RenameBlendShapeCommand`  
`class RenameBlendShapeCommand : public Command`  
_L18-56_
- inherits: `Command`
- desc: @brief RenameBlendShapeCommand is used to rename a blend shape channel.
- L20 _public prototype_ `DNACAPI explicit RenameBlendShapeCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RenameBlendShapeCommand(std::uint16_t blendShapeIndex, const char* newName, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RenameBlendShapeCommand(const char* oldName, const char* newName, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RenameBlendShapeCommand();`
- L26 _public prototype_ `RenameBlendShapeCommand(const RenameBlendShapeCommand&) = delete;`
- L27 _public prototype_ `RenameBlendShapeCommand& operator=(const RenameBlendShapeCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RenameBlendShapeCommand(RenameBlendShapeCommand&&);`
- L30 _public prototype_ `DNACAPI RenameBlendShapeCommand& operator=(RenameBlendShapeCommand&&);`
- L39 _public prototype_ `DNACAPI void setName(std::uint16_t blendShapeIndex, const char* newName);` — @brief Method for setting a new name for blend shape channel with given index. @param blendShapeIndex The index of the blend shape channel whose name to change. @param newName The new name for the blend shape channel.
- L50 _public prototype_ `DNACAPI void setName(const char* oldName, const char* newName);` — @brief Method for setting a new name for blend shape channel with given name. @note The renaming will not happen if there is no blend shape channel with given current name. @param oldName The current name of the blend shape channel whose name to change. @param newName The new name for the blend shape channel.
- L51 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L55 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RenameJointCommand.h` (Public)


#### class `dnac::RenameJointCommand`  
`class RenameJointCommand : public Command`  
_L18-56_
- inherits: `Command`
- desc: @brief RenameJointCommand is used to rename a joint.
- L20 _public prototype_ `DNACAPI explicit RenameJointCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RenameJointCommand(std::uint16_t jointIndex, const char* newName, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RenameJointCommand(const char* oldName, const char* newName, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RenameJointCommand();`
- L26 _public prototype_ `RenameJointCommand(const RenameJointCommand&) = delete;`
- L27 _public prototype_ `RenameJointCommand& operator=(const RenameJointCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RenameJointCommand(RenameJointCommand&&);`
- L30 _public prototype_ `DNACAPI RenameJointCommand& operator=(RenameJointCommand&&);`
- L39 _public prototype_ `DNACAPI void setName(std::uint16_t jointIndex, const char* newName);` — @brief Method for setting a new name for joint with given index. @param jointIndex The index of the joint whose name to change. @param newName The new name for the joint.
- L50 _public prototype_ `DNACAPI void setName(const char* oldName, const char* newName);` — @brief Method for setting a new name for joint with given name. @note The renaming will not happen if there is no joint with given current name. @param oldName The current name of the joint whose name to change. @param newName The new name for the joint.
- L51 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L55 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RenameMeshCommand.h` (Public)


#### class `dnac::RenameMeshCommand`  
`class RenameMeshCommand : public Command`  
_L18-56_
- inherits: `Command`
- desc: @brief RenameMeshCommand is used to rename a mesh.
- L20 _public prototype_ `DNACAPI explicit RenameMeshCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI RenameMeshCommand(std::uint16_t meshIndex, const char* newName, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI RenameMeshCommand(const char* oldName, const char* newName, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~RenameMeshCommand();`
- L26 _public prototype_ `RenameMeshCommand(const RenameMeshCommand&) = delete;`
- L27 _public prototype_ `RenameMeshCommand& operator=(const RenameMeshCommand&) = delete;`
- L29 _public prototype_ `DNACAPI RenameMeshCommand(RenameMeshCommand&&);`
- L30 _public prototype_ `DNACAPI RenameMeshCommand& operator=(RenameMeshCommand&&);`
- L39 _public prototype_ `DNACAPI void setName(std::uint16_t meshIndex, const char* newName);` — @brief Method for setting a new name for mesh with given index. @param meshIndex The index of the mesh whose name to change. @param newName The new name for the mesh.
- L50 _public prototype_ `DNACAPI void setName(const char* oldName, const char* newName);` — @brief Method for setting a new name for mesh with given name. @note The renaming will not happen if there is no mesh with given current name. @param oldName The current name of the mesh whose name to change. @param newName The new name for the mesh.
- L51 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L55 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/RotateCommand.h` (Public)


#### class `dnac::RotateCommand`  
`class RotateCommand : public Command`  
_L21-52_
- inherits: `Command`
- desc: @brief RotateCommand is used to rotate neutral joints and vertex positions around given origin. @note Joint rotations are represented in parent space, so it is enough to rotate only root joints, as that rotation will be propagated to the rest of the joints. @note If the origin is not set, the assumed origin is (0, 0, 0).
- L23 _public prototype_ `DNACAPI explicit RotateCommand(MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI RotateCommand(Vector3 degrees, Vector3 origin, MemoryResource* memRes = nullptr);`
- L26 _public prototype_ `DNACAPI ~RotateCommand();`
- L28 _public prototype_ `RotateCommand(const RotateCommand&) = delete;`
- L29 _public prototype_ `RotateCommand& operator=(const RotateCommand&) = delete;`
- L31 _public prototype_ `DNACAPI RotateCommand(RotateCommand&&);`
- L32 _public prototype_ `DNACAPI RotateCommand& operator=(RotateCommand&&);`
- L39 _public prototype_ `DNACAPI void setRotation(Vector3 degrees);` — @brief Method for setting the rotation angles. @param degrees Rotation angles in degrees.
- L46 _public prototype_ `DNACAPI void setOrigin(Vector3 origin);` — @brief Method for setting the rotation origin. @param origin Origin coordinates.
- L47 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L51 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/ScaleCommand.h` (Public)


#### class `dnac::ScaleCommand`  
`class ScaleCommand : public Command`  
_L18-50_
- inherits: `Command`
- desc: @brief ScaleCommand is used to scale neutral joints, vertex positions and joint and blendshape deltas by a factor. @note Only translation attributes of neutral joints and joint deltas are scaled.
- L20 _public prototype_ `DNACAPI explicit ScaleCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI ScaleCommand(float scale, Vector3 origin, MemoryResource* memRes = nullptr);`
- L23 _public prototype_ `DNACAPI ~ScaleCommand();`
- L25 _public prototype_ `ScaleCommand(const ScaleCommand&) = delete;`
- L26 _public prototype_ `ScaleCommand& operator=(const ScaleCommand&) = delete;`
- L28 _public prototype_ `DNACAPI ScaleCommand(ScaleCommand&&);`
- L29 _public prototype_ `DNACAPI ScaleCommand& operator=(ScaleCommand&&);`
- L36 _public prototype_ `DNACAPI void setScale(float scale);` — @brief Method for setting the scale factor to multiply with. @param scale Scale factor.
- L44 _public prototype_ `DNACAPI void setOrigin(Vector3 origin);` — @brief Method for setting the origin. @note The origin is used to properly scale position values (vertex positions and neutral joint translations). @param origin Origin coordinates.
- L45 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L49 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/SetBlendShapeTargetDeltasCommand.h` (Public)


#### class `dnac::SetBlendShapeTargetDeltasCommand`  
`class SetBlendShapeTargetDeltasCommand : public Command`  
_L19-135_
- inherits: `Command`
- desc: @brief SetBlendShapeTargetDeltasCommand is used to change blend shape target deltas.
- L21 _public member_ `DNACAPI static const sc::StatusCode VertexIndicesOutOfBoundsError;`
- L22 _public member_ `DNACAPI static const sc::StatusCode NoVertexIndicesSetError;`
- L23 _public member_ `DNACAPI static const sc::StatusCode DeltasVertexIndicesCountMismatch;`
- L24 _public member_ `DNACAPI static const sc::StatusCode DeltasMasksCountMismatch;`
- L27 _public prototype_ `DNACAPI explicit SetBlendShapeTargetDeltasCommand(MemoryResource* memRes = nullptr);`
- L28 _public prototype_ `DNACAPI SetBlendShapeTargetDeltasCommand(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, ConstArrayView<Vector3> deltas, ConstArrayView<std::uint32_t> vertexIndices, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L34 _public prototype_ `DNACAPI SetBlendShapeTargetDeltasCommand(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs, ConstArrayView<std::uint32_t> vertexIndices, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L42 _public prototype_ `DNACAPI SetBlendShapeTargetDeltasCommand(std::uint16_t meshIndex, std::uint16_t blendShapeTargetIndex, ConstArrayView<Vector3> deltas, ConstArrayView<std::uint32_t> vertexIndices, ConstArrayView<float> masks, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L59 _public prototype_ `DNACAPI ~SetBlendShapeTargetDeltasCommand();`
- L61 _public prototype_ `SetBlendShapeTargetDeltasCommand(const SetBlendShapeTargetDeltasCommand&) = delete;`
- L62 _public prototype_ `SetBlendShapeTargetDeltasCommand& operator=(const SetBlendShapeTargetDeltasCommand&) = delete;`
- L64 _public prototype_ `DNACAPI SetBlendShapeTargetDeltasCommand(SetBlendShapeTargetDeltasCommand&&);`
- L65 _public prototype_ `DNACAPI SetBlendShapeTargetDeltasCommand& operator=(SetBlendShapeTargetDeltasCommand&&);`
- L72 _public prototype_ `DNACAPI void setMeshIndex(std::uint16_t meshIndex);` — @brief Method for setting the index of the mesh whose blend shape target to change. @param meshIndex The mesh index.
- L78 _public prototype_ `DNACAPI void setBlendShapeTargetIndex(std::uint16_t blendShapeTargetIndex);` — @brief Method for setting the index of the blend shape target to change. @param blendShapeTargetIndex The blend shape target index.
- L85 _public prototype_ `DNACAPI void setDeltas(ConstArrayView<Vector3> deltas);` — @brief Method for setting the values used to calculate new deltas for blend shape target. @param deltas The values used in calculation.
- L96 _public prototype_ `DNACAPI void setDeltas(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);` — @brief Method for setting the values used to calculate new deltas for blend shape target. @param xs The X values for each delta. @param ys The Y values for each delta. @param zs The Z values for each delta.
- L103 _public prototype_ `DNACAPI void setVertexIndices(ConstArrayView<std::uint32_t> vertexIndices);` — @brief Method for setting the vertex indices that correspond to new deltas. @param vertexIndices The vertexIndices.
- L112 _public prototype_ `DNACAPI void setMasks(ConstArrayView<float> masks);` — @brief Method for setting masks used to calculate new deltas for blend shape target. @note If no masks are set, default weight value of 1 is used for each delta. @param masks The weights for each delta.
- L129 _public prototype_ `DNACAPI void setOperation(VectorOperation operation);` — @brief Method for setting the type of operation used to calculate new deltas for blend shape target. @note Available operations are: Interpolate, Add, Subtract and Multiply. Each delta is calculated based on the provided operation type in the following way: Interpolate: \f$newValue = previousValue * (1 - weight) + setValue * weight\f$\n Add: \f$newValue = previousValue + (setValue * weight)\f$\n Subtract: \f$newValue = previousValue - (setValue * weight)\f$\n Multiply: \f$newValue = previousValue * (setValue * weight)\f$\n setValue is the value from new deltas that were set, and weight is the value from masks array. @param operation The operation to use.
- L130 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L134 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/SetLODsCommand.h` (Public)


#### class `dnac::SetLODsCommand`  
`class SetLODsCommand : public Command`  
_L19-43_
- inherits: `Command`
- desc: @brief SetLODsCommand is used to specify LODs to use. Joints, blend shapes, animated maps and meshes that are not in specified LODs are removed from the DNA.
- L21 _public prototype_ `DNACAPI explicit SetLODsCommand(MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI SetLODsCommand(ConstArrayView<std::uint16_t> lods, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~SetLODsCommand();`
- L26 _public prototype_ `SetLODsCommand(const SetLODsCommand&) = delete;`
- L27 _public prototype_ `SetLODsCommand& operator=(const SetLODsCommand&) = delete;`
- L29 _public prototype_ `DNACAPI SetLODsCommand(SetLODsCommand&&);`
- L30 _public prototype_ `DNACAPI SetLODsCommand& operator=(SetLODsCommand&&);`
- L37 _public prototype_ `DNACAPI void setLODs(ConstArrayView<std::uint16_t> lods);` — @brief Method for setting the LODs to keep. @param lods New LODs to be used.
- L38 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L42 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/SetNeutralJointRotationsCommand.h` (Public)


#### class `dnac::SetNeutralJointRotationsCommand`  
`class SetNeutralJointRotationsCommand : public Command`  
_L18-57_
- inherits: `Command`
- desc: @brief SetNeutralJointRotationsCommand is used to set new rotation values to neutral joints.
- L20 _public prototype_ `DNACAPI explicit SetNeutralJointRotationsCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI SetNeutralJointRotationsCommand(ConstArrayView<Vector3> rotations, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI SetNeutralJointRotationsCommand(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs, MemoryResource* memRes = nullptr);`
- L27 _public prototype_ `DNACAPI ~SetNeutralJointRotationsCommand();`
- L29 _public prototype_ `SetNeutralJointRotationsCommand(const SetNeutralJointRotationsCommand&) = delete;`
- L30 _public prototype_ `SetNeutralJointRotationsCommand& operator=(const SetNeutralJointRotationsCommand&) = delete;`
- L32 _public prototype_ `DNACAPI SetNeutralJointRotationsCommand(SetNeutralJointRotationsCommand&&);`
- L33 _public prototype_ `DNACAPI SetNeutralJointRotationsCommand& operator=(SetNeutralJointRotationsCommand&&);`
- L40 _public prototype_ `DNACAPI void setRotations(ConstArrayView<Vector3> rotations);` — @brief Method for setting the neutral joint rotations. @param rotations Rotation values for each joint.
- L51 _public prototype_ `DNACAPI void setRotations(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);` — @brief Method for setting the neutral joint rotations. @param xs The X rotation value for each joint. @param ys The Y rotation value for each joint. @param zs The Z rotation value for each joint.
- L52 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L56 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/SetNeutralJointTranslationsCommand.h` (Public)


#### class `dnac::SetNeutralJointTranslationsCommand`  
`class SetNeutralJointTranslationsCommand : public Command`  
_L18-57_
- inherits: `Command`
- desc: @brief SetNeutralJointTranslationsCommand is used to set new translation values to neutral joints.
- L20 _public prototype_ `DNACAPI explicit SetNeutralJointTranslationsCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI SetNeutralJointTranslationsCommand(ConstArrayView<Vector3> translations, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI SetNeutralJointTranslationsCommand(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs, MemoryResource* memRes = nullptr);`
- L27 _public prototype_ `DNACAPI ~SetNeutralJointTranslationsCommand();`
- L29 _public prototype_ `SetNeutralJointTranslationsCommand(const SetNeutralJointTranslationsCommand&) = delete;`
- L30 _public prototype_ `SetNeutralJointTranslationsCommand& operator=(const SetNeutralJointTranslationsCommand&) = delete;`
- L32 _public prototype_ `DNACAPI SetNeutralJointTranslationsCommand(SetNeutralJointTranslationsCommand&&);`
- L33 _public prototype_ `DNACAPI SetNeutralJointTranslationsCommand& operator=(SetNeutralJointTranslationsCommand&&);`
- L40 _public prototype_ `DNACAPI void setTranslations(ConstArrayView<Vector3> translations);` — @brief Method for setting the neutral joint translations. @param translations Translation values for each joint.
- L51 _public prototype_ `DNACAPI void setTranslations(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);` — @brief Method for setting the neutral joint translations. @param xs The X translation value for each joint. @param ys The Y translation value for each joint. @param zs The Z translation value for each joint.
- L52 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L56 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/SetSkinWeightsCommand.h` (Public)


#### class `dnac::SetSkinWeightsCommand`  
`class SetSkinWeightsCommand : public Command`  
_L18-67_
- inherits: `Command`
- desc: @brief SetSkinWeightsCommand is used to set new skin weights for a vertex in a mesh.
- L20 _public prototype_ `DNACAPI explicit SetSkinWeightsCommand(MemoryResource* memRes = nullptr);`
- L21 _public prototype_ `DNACAPI SetSkinWeightsCommand(std::uint16_t meshIndex, std::uint32_t vertexIndex, ConstArrayView<float> weights, ConstArrayView<std::uint16_t> jointIndices, MemoryResource* memRes = nullptr);`
- L27 _public prototype_ `DNACAPI ~SetSkinWeightsCommand();`
- L29 _public prototype_ `SetSkinWeightsCommand(const SetSkinWeightsCommand&) = delete;`
- L30 _public prototype_ `SetSkinWeightsCommand& operator=(const SetSkinWeightsCommand&) = delete;`
- L32 _public prototype_ `DNACAPI SetSkinWeightsCommand(SetSkinWeightsCommand&&);`
- L33 _public prototype_ `DNACAPI SetSkinWeightsCommand& operator=(SetSkinWeightsCommand&&);`
- L40 _public prototype_ `DNACAPI void setMeshIndex(std::uint16_t meshIndex);` — @brief Method for setting the index of the targeted mesh. @param meshIndex The mesh index.
- L47 _public prototype_ `DNACAPI void setVertexIndex(std::uint32_t vertexIndex);` — @brief Method for setting the index of the vertex to change. @param vertexIndex The vertex index.
- L54 _public prototype_ `DNACAPI void setWeights(ConstArrayView<float> weights);` — @brief Method for setting the weights with which joints influence the vertex in question. @param weights Weights for each joint that has an influence on the vertex.
- L61 _public prototype_ `DNACAPI void setJointIndices(ConstArrayView<std::uint16_t> jointIndices);` — @brief Method for setting the joint indices of joints that influence the vertex in question. @param jointIndices Joint indices of joints that have an influence on the vertex.
- L62 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L66 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/SetVertexPositionsCommand.h` (Public)


#### class `dnac::SetVertexPositionsCommand`  
`class SetVertexPositionsCommand : public Command`  
_L19-112_
- inherits: `Command`
- desc: @brief SetVertexPositionsCommand is used to change vertex positions values.
- L21 _public member_ `DNACAPI static const sc::StatusCode PositionsMasksCountMismatch;`
- L24 _public prototype_ `DNACAPI explicit SetVertexPositionsCommand(MemoryResource* memRes = nullptr);`
- L26 _public prototype_ `DNACAPI SetVertexPositionsCommand(std::uint16_t meshIndex, ConstArrayView<Vector3> positions, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L30 _public prototype_ `DNACAPI SetVertexPositionsCommand(std::uint16_t meshIndex, ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L36 _public prototype_ `DNACAPI SetVertexPositionsCommand(std::uint16_t meshIndex, ConstArrayView<Vector3> positions, ConstArrayView<float> masks, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L41 _public prototype_ `DNACAPI SetVertexPositionsCommand(std::uint16_t meshIndex, ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs, ConstArrayView<float> masks, VectorOperation operation, MemoryResource* memRes = nullptr);`
- L49 _public prototype_ `DNACAPI ~SetVertexPositionsCommand();`
- L51 _public prototype_ `SetVertexPositionsCommand(const SetVertexPositionsCommand&) = delete;`
- L52 _public prototype_ `SetVertexPositionsCommand& operator=(const SetVertexPositionsCommand&) = delete;`
- L54 _public prototype_ `DNACAPI SetVertexPositionsCommand(SetVertexPositionsCommand&&);`
- L55 _public prototype_ `DNACAPI SetVertexPositionsCommand& operator=(SetVertexPositionsCommand&&);`
- L62 _public prototype_ `DNACAPI void setMeshIndex(std::uint16_t meshIndex);` — @brief Method for setting the index of the mesh to change. @param meshIndex The mesh index.
- L69 _public prototype_ `DNACAPI void setPositions(ConstArrayView<Vector3> positions);` — @brief Method for setting the vertex positions used to calculate new values. @param positions The vertex positions.
- L80 _public prototype_ `DNACAPI void setPositions(ConstArrayView<float> xs, ConstArrayView<float> ys, ConstArrayView<float> zs);` — @brief Method for setting the vertex positions used to calculate new values. @param xs The X coordinates for each vertex. @param ys The Y coordinates for each vertex. @param zs The Z coordinates for each vertex.
- L89 _public prototype_ `DNACAPI void setMasks(ConstArrayView<float> masks);` — @brief Method for setting vertex masks used to calculate new vertex position values. @note If no masks are set, default weight value of 1 is used for each vertex. @param masks The weights for each vertex.
- L106 _public prototype_ `DNACAPI void setOperation(VectorOperation operation);` — @brief Method for setting the type of operation used to calculate new vertex position values. @note Available operations are: Interpolate, Add, Subtract and Multiply. Each position is calculated based on the provided operation type in the following way: Interpolate: \f$newValue = previousValue * (1 - weight) + setValue * weight\f$\n Add: \f$newValue = previousValue + (setValue * weight)\f$\n Subtract: \f$newValue = previousValue - (setValue * weight)\f$\n Multiply: \f$newValue = previousValue * (setValue * weight)\f$\n setValue is the value from new positions that were set, and weight is the value from masks array. @param operation The operation to use.
- L107 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L111 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/TranslateCommand.h` (Public)


#### class `dnac::TranslateCommand`  
`class TranslateCommand : public Command`  
_L19-43_
- inherits: `Command`
- desc: @brief TranslateCommand is used to translate neutral joints and vertex positions. @note Joint translations are represented in parent space, so it is enough to translate only root joints, as that translation will be propagated to the rest of the joints.
- L21 _public prototype_ `DNACAPI explicit TranslateCommand(MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `DNACAPI TranslateCommand(Vector3 translation, MemoryResource* memRes = nullptr);`
- L24 _public prototype_ `DNACAPI ~TranslateCommand();`
- L26 _public prototype_ `TranslateCommand(const TranslateCommand&) = delete;`
- L27 _public prototype_ `TranslateCommand& operator=(const TranslateCommand&) = delete;`
- L29 _public prototype_ `DNACAPI TranslateCommand(TranslateCommand&&);`
- L30 _public prototype_ `DNACAPI TranslateCommand& operator=(TranslateCommand&&);`
- L37 _public prototype_ `DNACAPI void setTranslation(Vector3 translation);` — @brief Method for setting the translation vector. @param translation The translation vector.
- L38 _public prototype_ `DNACAPI void run(DNACalibDNAReader* output) override;`
- L42 _private member_ `ScopedPtr<Impl> pImpl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/commands/VectorOperations.h` (Public)


#### enum `dnac::VectorOperation`  
`enum class VectorOperation`  
_L7-12_
- L8 _public enumerator_ `Interpolate`
- L9 _public enumerator_ `Add`
- L10 _public enumerator_ `Subtract`
- L11 _public enumerator_ `Multiply`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace dnac`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/dna/DNACalibDNAReader.h` (Public)


#### class `dnac::DNACalibDNAReader`  
`class DNACAPI DNACalibDNAReader : public dna::Reader`  
_L12-20_
- inherits: `dna::Reader`
- L14 _public prototype_ `static DNACalibDNAReader* create(MemoryResource* memRes = nullptr);`
- L15 _public prototype_ `static DNACalibDNAReader* create(const dna::Reader* reader, MemoryResource* memRes = nullptr);`
- L16 _public prototype_ `static void destroy(DNACalibDNAReader* instance);`
- L19 _protected prototype_ `virtual ~DNACalibDNAReader();`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<dnac::DNACalibDNAReader>`  
_L27-29_
- L28 _public typedef_ `using type = FactoryCreate<dnac::DNACalibDNAReader>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<dnac::DNACalibDNAReader>`  
_L32-34_
- L33 _public typedef_ `using type = FactoryDestroy<dnac::DNACalibDNAReader>;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace dnac`
- L24 _namespace_ `namespace pma`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/types/Aliases.h` (Public)


#### Free symbols / members of external scopes

- L24 _namespace_ `namespace dnac`
- L43 _typedef_ `template<typename T> using ArrayView = dna::ArrayView<T>;` (scope `dnac`)
- L46 _typedef_ `template<typename T> using ConstArrayView = dna::ConstArrayView<T>;` (scope `dnac`)

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define DNAC_MAJOR_VERSION 6`
- L6 _macro_ `#define DNAC_MINOR_VERSION 16`
- L7 _macro_ `#define DNAC_PATCH_VERSION 3`
- L8 _macro_ `#define DNAC_VERSION_STRING "6.16.3"`

### `Plugins/Animation/DNACalib/Source/DNACalibLib/Public/dnacalib/version/VersionInfo.h` (Public)


#### struct `dnac::VersionInfo`  
`struct DNACAPI VersionInfo`  
_L10-15_
- L11 _public prototype_ `static int getMajorVersion();`
- L12 _public prototype_ `static int getMinorVersion();`
- L13 _public prototype_ `static int getPatchVersion();`
- L14 _public prototype_ `static StringView getVersionString();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace dnac`
