# Plugins / GeneSplicerLib

- module root: `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib`
- headers: 100; symbols: 2492
- symbol kinds: class=63, delegate=1, enum=7, enumerator=27, function=831, macro=40, member=398, namespace=104, prototype=799, struct=105, typedef=115, variable=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RigLogicLib, UnrealEd

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/GeneSplicerDNAReaderImpl.h` (Private)


#### class `gs4::GeneSplicerDNAReaderImpl`  
`class GeneSplicerDNAReaderImpl : public ReaderImpl<GeneSplicerDNAReader>, public WriterImpl<dna::Writer>`  
_L22-46_
- inherits: `ReaderImpl<GeneSplicerDNAReader>,WriterImpl<dna::Writer>`
- L24 _public prototype_ `explicit GeneSplicerDNAReaderImpl(MemoryResource* memRes_);`
- L27 _public prototype_ `void unload(DataLayer layer) override;` — Reader methods
- L30 _public prototype_ `void setJointGroups(Vector<RawJointGroup>&& jointGroups);` — GSWriter methods
- L33 _public prototype_ `void setVertexPositions(std::uint16_t meshIndex, RawVector3Vector&& positions);`
- L36 _public prototype_ `void setVertexNormals(std::uint16_t meshIndex, RawVector3Vector&& normals);`
- L39 _public prototype_ `void setNeutralJointTranslations(RawVector3Vector&& translations);`
- L42 _public prototype_ `void setNeutralJointRotations(RawVector3Vector&& rotations);`
- L44 _public prototype_ `void setSkinWeights(std::uint16_t meshIndex, Vector<RawVertexSkinWeights>&& rawSkinWeights);`
- L45 _public prototype_ `void setBlendShapeTargets(std::uint16_t meshIndex, Vector<RawBlendShapeTarget>&& blendShapeTargets);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/GeneSplicerImpl.h` (Private)


#### class `gs4::GeneSplicer::Impl`  
`class GeneSplicer::Impl`  
_L19-62_
- L21 _private typedef_ `using SplicerPtr = pma::UniqueInstance<Splicer>::PointerType;`
- L24 _public prototype_ `Impl(SplicerPtr neutralJointSplicer_, SplicerPtr jointBehaviorSplicer_, SplicerPtr blendShapeSplicer_, SplicerPtr neutralMeshSplicer_, SplicerPtr skinWeightSplicer_, MemoryResource* memRes);`
- L32 _public function_ `template<CalculationType CT> static Impl* create(MemoryResource* memRes)`
- L47 _public prototype_ `static void destroy(Impl* instance);`
- L48 _public prototype_ `void splice(const SpliceData& spliceData, GeneSplicerDNAReader* output);`
- L49 _public prototype_ `void spliceNeutralJoints(const SpliceData& spliceData, GeneSplicerDNAReader* output);`
- L50 _public prototype_ `void spliceNeutralMeshes(const SpliceData& spliceData, GeneSplicerDNAReader* output);`
- L51 _public prototype_ `void spliceBlendShapes(const SpliceData& spliceData, GeneSplicerDNAReader* output);`
- L52 _public prototype_ `void spliceJointBehavior(const SpliceData& spliceData, GeneSplicerDNAReader* output);`
- L53 _public prototype_ `void spliceSkinWeights(const SpliceData& spliceData, GeneSplicerDNAReader* output);`
- L56 _private member_ `MemoryResource* memRes;`
- L57 _private member_ `SplicerPtr neutralJointSplicer;`
- L58 _private member_ `SplicerPtr jointBehaviorSplicer;`
- L59 _private member_ `SplicerPtr blendShapeSplicer;`
- L60 _private member_ `SplicerPtr neutralMeshSplicer;`
- L61 _private member_ `SplicerPtr skinWeightSplicer;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/Macros.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define FORCE_INLINE __forceinline`
- L9 _macro_ `#define FORCE_INLINE inline __attribute__((always_inline))`
- L15 _macro_ `#define ASSUME_TRUE(condition) __assume(condition)`
- L18 _macro_ `#define ASSUME_TRUE(condition) \` — *INDENT-OFF*
- L28 _macro_ `#define UNUSED(x) static_cast<void>(x)`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/Splicer.h` (Private)


#### class `gs4::Splicer`  
`class Splicer`  
_L17-25_
- L19 _public prototype_ `explicit Splicer(MemoryResource* memRes);`
- L20 _public prototype_ `virtual void splice(const SpliceDataInterface* spliceData, GeneSplicerDNAReader* output) = 0;`
- L21 _public prototype_ `virtual ~Splicer();`
- L24 _protected member_ `MemoryResource* memRes;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/TypeDefs.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace gs4`
- L26 _typedef_ `template<typename T> using AlignedAllocator = PolyAllocator<T, trimd::F256::alignment(), AlignedMemoryResource>;` (scope `gs4`)
- L29 _typedef_ `template<typename T> using AlignedVector = Vector<T, AlignedAllocator<T>>;` (scope `gs4`)
- L32 _typedef_ `template<typename T> using Blob = terse::Blob<T, PolyAllocator<T>>;` (scope `gs4`)
- L35 _typedef_ `template<typename T> using DynArray = terse::DynArray<T, PolyAllocator<T>>;` (scope `gs4`)
- L38 _typedef_ `template<typename T> using AlignedDynArray = terse::DynArray<T, AlignedAllocator<T>>;` (scope `gs4`)
- L41 _typedef_ `template<typename T> using AlignedMatrix = Vector<AlignedVector<T>>;` (scope `gs4`)
- L43 _variable_ `static constexpr auto cFalse = static_cast<char>(0);` (scope `gs4`)
- L44 _variable_ `static constexpr auto cTrue = static_cast<char>(1);` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/blendshapesplicer/BlendShapeSplicer.h` (Private)


#### class `gs4::BlendShapeSplicer`  
`template<CalculationType CT> class BlendShapeSplicer : public Splicer`  
_L16-21_
- inherits: `Splicer`
- L20 _public prototype_ `void splice(const SpliceDataInterface* spliceData, GeneSplicerDNAReader* output) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/Aliases.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/BaseImpl.h` (Private)


#### class `gs4::BaseImpl`  
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

- L8 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/DNA.h` (Private)


#### struct `gs4::Dispatcher`  
`template<typename TVersion, TVersion Fallback> struct Dispatcher<TVersion, Fallback>`  
_L119-134_
- L122 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion , bool transparent)`
- L138 _public typedef_ `using Super = Dispatcher<TVersion, Rest...>;`
- L141 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion version, bool transparent)`

#### struct `gs4::Dispatcher`  
`template<typename TVersion, TVersion Expected, TVersion... Rest> struct Dispatcher<TVersion, Expected, Rest...> : Dispatcher<TVersion, Rest...>`  
_L137-153_
- inherits: `Dispatcher<TVersion,Rest...>`
- L122 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion , bool transparent)`
- L138 _public typedef_ `using Super = Dispatcher<TVersion, Rest...>;`
- L141 _public function_ `template<class Archive, typename TSerializable> void operator()(Archive& archive, TSerializable& object, TVersion version, bool transparent)`

#### enum `gs4::FileVersion`  
`enum FileVersion : std::uint64_t`  
_L172-183_
- L173 _public enumerator_ `unknown = 0u`
- L174 _public enumerator_ `v21 = rev(2, 1)`
- L175 _public enumerator_ `v22 = rev(2, 2)`
- L176 _public enumerator_ `v23 = rev(2, 3)`
- L177 _public enumerator_ `v24 = rev(2, 4)`
- L178 _public enumerator_ `v25 = rev(2, 5)`
- L179 _public enumerator_ `v26 = rev(2, 6)`
- L180 _public enumerator_ `v27 = rev(2, 7)`
- L181 _public enumerator_ `v28 = rev(2, 8)`
- L182 _public enumerator_ `latest = v28`

#### enum `gs4::UpgradeFormatPolicy`  
`enum class UpgradeFormatPolicy`  
_L201-204_
- L202 _public enumerator_ `Disallowed`
- L203 _public enumerator_ `Allowed`

#### struct `gs4::SerializationContext`  
`struct SerializationContext`  
_L206-209_
- L207 _public member_ `FileVersion version;`
- L208 _public member_ `void* data;`

#### struct `gs4::Version`  
`struct Version`  
_L211-240_
- L212 _public member_ `std::uint16_t generation;`
- L213 _public member_ `std::uint16_t version;`
- L215 _public function_ `Version(FileVersion fileVersion) : generation`
- L220 _public function_ `operator FileVersion() const`
- L225 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L232 _public function_ `bool matches(FileVersion fileVersion) const`
- L237 _public function_ `bool supported() const`

#### struct `gs4::SectionLookupTable`  
`struct SectionLookupTable`  
_L242-271_
- L243 _public member_ `terse::ArchiveOffset<std::uint32_t> descriptor;`
- L244 _public member_ `terse::ArchiveOffset<std::uint32_t> definition;`
- L245 _public member_ `terse::ArchiveOffset<std::uint32_t> behavior;`
- L246 _public member_ `terse::ArchiveOffset<std::uint32_t> controls;`
- L247 _public member_ `terse::ArchiveOffset<std::uint32_t> joints;`
- L248 _public member_ `terse::ArchiveOffset<std::uint32_t> blendShapeChannels;`
- L249 _public member_ `terse::ArchiveOffset<std::uint32_t> animatedMaps;`
- L250 _public member_ `terse::ArchiveOffset<std::uint32_t> geometry;`
- L253 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::Index`  
`struct Index`  
_L273-301_
- L274 _public member_ `std::uint32_t id;`
- L275 _public member_ `std::uint32_t version;`
- L276 _public member_ `terse::ArchiveOffset<std::uint32_t> offset;`
- L277 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L280 _public function_ `template<std::size_t Length = 16ul> std::array<char, Length> label()`
- L291 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::IndexTable`  
`struct IndexTable`  
_L303-342_
- L304 _public member_ `Vector<Index> entries;`
- L306 _public function_ `explicit IndexTable(MemoryResource* memRes) : entries`
- L310 _public function_ `Index* get(std::uint32_t id, std::uint32_t version)`
- L319 _public function_ `const Index* get(std::uint32_t id, std::uint32_t version) const`
- L323 _public function_ `Index* create(std::uint32_t id, std::uint32_t version)`
- L329 _public function_ `void destroy(std::uint32_t id, std::uint32_t version)`
- L338 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::UnknownLayer`  
`struct UnknownLayer`  
_L344-386_
- L345 _public member_ `std::uint32_t id;`
- L346 _public member_ `std::uint32_t version;`
- L347 _public member_ `Blob<char> data;`
- L349 _public function_ `UnknownLayer(std::uint32_t id_, std::uint32_t version_, MemoryResource* memRes) : id`
- L355 _public function_ `std::uint32_t layerId()`
- L359 _public function_ `std::uint32_t layerVersion()`
- L363 _public function_ `bool layerSupported(FileVersion )`
- L368 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::Layer`  
`template<std::uint32_t Id, std::uint32_t Version, typename TData, FileVersion AvailableFromFileVersion> struct Layer : TData`  
_L389-424_
- inherits: `TData`
- L392 _public function_ `template<typename... Args> explicit Layer(Args&&... args) : TData`
- L396 _public function_ `std::uint32_t layerId()`
- L400 _public function_ `std::uint32_t layerVersion()`
- L404 _public function_ `bool layerSupported(FileVersion inVersion)`
- L409 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::LayerContainer`  
`template<> struct LayerContainer<>`  
_L430-469_
- L431 _public member_ `UnknownLayerPolicy unknownPolicy;`
- L432 _public member_ `UpgradeFormatPolicy upgradePolicy;`
- L433 _public member_ `Vector<UnknownLayer> unknownLayers;`
- L435 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes) : unknownPolicy`
- L442 _public function_ `template<typename TArchive> void serialize(TArchive& archive)`
- L466 _public function_ `void updateIndexTable(IndexTable& , FileVersion )`
- L473 _public typedef_ `using Super = LayerContainer<TRest...>;`
- L475 _public member_ `TLayer* layer;`
- L477 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes, TLayer* layer_, TRest*... rest) : Super`
- L497 _public function_ `void updateIndexTable(IndexTable& indexTable, FileVersion fileVersion)`

#### struct `gs4::LayerContainer`  
`template<typename TLayer, typename... TRest> struct LayerContainer<TLayer, TRest...> : LayerContainer<TRest...>`  
_L472-512_
- inherits: `LayerContainer<TRest...>`
- L431 _public member_ `UnknownLayerPolicy unknownPolicy;`
- L432 _public member_ `UpgradeFormatPolicy upgradePolicy;`
- L433 _public member_ `Vector<UnknownLayer> unknownLayers;`
- L435 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes) : unknownPolicy`
- L442 _public function_ `template<typename TArchive> void serialize(TArchive& archive)`
- L466 _public function_ `void updateIndexTable(IndexTable& , FileVersion )`
- L473 _public typedef_ `using Super = LayerContainer<TRest...>;`
- L475 _public member_ `TLayer* layer;`
- L477 _public function_ `LayerContainer(UnknownLayerPolicy unknownPolicy_, UpgradeFormatPolicy upgradePolicy_, MemoryResource* memRes, TLayer* layer_, TRest*... rest) : Super`
- L497 _public function_ `void updateIndexTable(IndexTable& indexTable, FileVersion fileVersion)`

#### struct `gs4::RawSurjectiveMapping`  
`template<typename TFrom, typename TTo = TFrom> struct RawSurjectiveMapping : public SurjectiveMapping<TFrom, TTo>`  
_L515-525_
- inherits: `SurjectiveMapping<TFrom,TTo>`
- L519 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawCoordinateSystem`  
`struct RawCoordinateSystem`  
_L527-551_
- L528 _public member_ `std::uint16_t xAxis;`
- L529 _public member_ `std::uint16_t yAxis;`
- L530 _public member_ `std::uint16_t zAxis;`
- L532 _public function_ `bool operator==(const CoordinateSystem& coordinateSystem) const`
- L538 _public function_ `bool operator!=(const CoordinateSystem& coordinateSystem) const`
- L543 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawLODMapping`  
`struct RawLODMapping : public LODMapping`  
_L553-563_
- inherits: `LODMapping`
- L557 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawDescriptor`  
`struct RawDescriptor`  
_L565-623_
- L566 _public typedef_ `using StringPair = std::tuple<String<char>, String<char>>;`
- L568 _public member_ `String<char> name;`
- L569 _public member_ `std::uint16_t archetype;`
- L570 _public member_ `std::uint16_t gender;`
- L571 _public member_ `std::uint16_t age;`
- L572 _public member_ `Vector<StringPair> metadata;`
- L573 _public member_ `std::uint16_t translationUnit;`
- L574 _public member_ `std::uint16_t rotationUnit;`
- L575 _public member_ `RawCoordinateSystem coordinateSystem;`
- L576 _public member_ `std::uint16_t lodCount;`
- L577 _public member_ `std::uint16_t maxLOD;`
- L578 _public member_ `String<char> complexity;`
- L579 _public member_ `String<char> dbName;`
- L581 _public function_ `explicit RawDescriptor(MemoryResource* memRes) : name`
- L597 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawDescriptorExt`  
`struct RawDescriptorExt`  
_L625-684_
- L626 _public member_ `RotationSequence rotationSequence;`
- L627 _public member_ `RotationSign rotationSign;`
- L628 _public member_ `FaceWindingOrder faceWindingOrder;`
- L630 _public function_ `explicit RawDescriptorExt(MemoryResource* memRes) : rotationSequence`
- L638 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L646 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v22> )`
- L651 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v23> )`
- L656 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v24> )`
- L661 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v25> )`
- L666 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v26> )`
- L671 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v27> )`
- L676 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion )`

#### struct `gs4::RawVector3Vector`  
`struct RawVector3Vector`  
_L686-758_
- L687 _public member_ `AlignedDynArray<float> xs;`
- L688 _public member_ `AlignedDynArray<float> ys;`
- L689 _public member_ `AlignedDynArray<float> zs;`
- L691 _public function_ `explicit RawVector3Vector(MemoryResource* memRes) : xs`
- L697 _public function_ `RawVector3Vector(std::size_t size_, float initial, MemoryResource* memRes) : xs`
- L703 _public function_ `RawVector3Vector(ConstArrayView<float> xs_, ConstArrayView<float> ys_, ConstArrayView<float> zs_, MemoryResource* memRes) : xs`
- L710 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L719 _public function_ `std::size_t size() const`
- L724 _public function_ `void reserve(std::size_t count)`
- L730 _public function_ `void resize(std::size_t count)`
- L736 _public function_ `void resize(std::size_t count, float value)`
- L742 _public function_ `void clear()`
- L749 _public function_ `template<typename Iterator> void assign(Iterator start, Iterator end)`

#### struct `gs4::RawDefinition`  
`struct RawDefinition`  
_L760-824_
- L761 _public member_ `RawLODMapping lodJointMapping;`
- L762 _public member_ `RawLODMapping lodBlendShapeMapping;`
- L763 _public member_ `RawLODMapping lodAnimatedMapMapping;`
- L764 _public member_ `RawLODMapping lodMeshMapping;`
- L765 _public member_ `Vector<String<char>> guiControlNames;`
- L766 _public member_ `Vector<String<char>> rawControlNames;`
- L767 _public member_ `Vector<String<char>> jointNames;`
- L768 _public member_ `Vector<String<char>> blendShapeChannelNames;`
- L769 _public member_ `Vector<String<char>> animatedMapNames;`
- L770 _public member_ `Vector<String<char>> meshNames;`
- L771 _public member_ `RawSurjectiveMapping<std::uint16_t> meshBlendShapeChannelMapping;`
- L772 _public member_ `DynArray<std::uint16_t> jointHierarchy;`
- L773 _public member_ `RawVector3Vector neutralJointTranslations;`
- L774 _public member_ `RawVector3Vector neutralJointRotations;`
- L776 _public function_ `explicit RawDefinition(MemoryResource* memRes) : lodJointMapping`
- L794 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawConditionalTable`  
`struct RawConditionalTable`  
_L826-858_
- L827 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L828 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L829 _public member_ `DynArray<float> fromValues;`
- L830 _public member_ `DynArray<float> toValues;`
- L831 _public member_ `DynArray<float> slopeValues;`
- L832 _public member_ `DynArray<float> cutValues;`
- L834 _public function_ `explicit RawConditionalTable(MemoryResource* memRes) : inputIndices`
- L844 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawPSDMatrix`  
`struct RawPSDMatrix`  
_L860-880_
- L861 _public member_ `DynArray<std::uint16_t> rows;`
- L862 _public member_ `DynArray<std::uint16_t> columns;`
- L863 _public member_ `DynArray<float> values;`
- L865 _public function_ `explicit RawPSDMatrix(MemoryResource* memRes) : rows`
- L872 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawControls`  
`struct RawControls`  
_L882-902_
- L883 _public member_ `std::uint16_t psdCount;`
- L884 _public member_ `RawConditionalTable conditionals;`
- L885 _public member_ `RawPSDMatrix psds;`
- L887 _public function_ `explicit RawControls(MemoryResource* memRes) : psdCount`
- L894 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawJointGroup`  
`struct RawJointGroup`  
_L904-941_
- L910 _public member_ `DynArray<std::uint16_t> lods;` — Row count of each LOD 12, 9, 3, |  |  + LOD-2 contains first 3 rows |  + LOD-1 contains first 9 rows + LOD-0 contains first 12 rows
- L912 _public member_ `DynArray<std::uint16_t> inputIndices;` — Sub-matrix col -> input vector
- L914 _public member_ `DynArray<std::uint16_t> outputIndices;` — Sub-matrix row -> output vector
- L916 _public member_ `AlignedDynArray<float> values;` — Non-zero values of all sub-matrices
- L918 _public member_ `DynArray<std::uint16_t> jointIndices;`
- L920 _public function_ `explicit RawJointGroup(MemoryResource* memRes) : lods`
- L929 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawJoints`  
`struct RawJoints`  
_L943-963_
- L944 _public member_ `std::uint16_t rowCount;`
- L945 _public member_ `std::uint16_t colCount;`
- L946 _public member_ `Vector<RawJointGroup> jointGroups;`
- L948 _public function_ `explicit RawJoints(MemoryResource* memRes) : rowCount`
- L955 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawBlendShapeChannels`  
`struct RawBlendShapeChannels`  
_L965-985_
- L966 _public member_ `DynArray<std::uint16_t> lods;`
- L967 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L968 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L970 _public function_ `explicit RawBlendShapeChannels(MemoryResource* memRes) : lods`
- L977 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawAnimatedMaps`  
`struct RawAnimatedMaps`  
_L987-1003_
- L988 _public member_ `DynArray<std::uint16_t> lods;`
- L989 _public member_ `RawConditionalTable conditionals;`
- L991 _public function_ `explicit RawAnimatedMaps(MemoryResource* memRes) : lods`
- L997 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawBehavior`  
`struct RawBehavior`  
_L1005-1051_
- L1006 _public member_ `RawControls controls;`
- L1007 _public member_ `RawJoints joints;`
- L1008 _public member_ `RawBlendShapeChannels blendShapeChannels;`
- L1009 _public member_ `RawAnimatedMaps animatedMaps;`
- L1011 _public function_ `explicit RawBehavior(MemoryResource* memRes) : controls`
- L1019 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L1041 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion)`

#### struct `gs4::RawTextureCoordinateVector`  
`struct RawTextureCoordinateVector`  
_L1053-1079_
- L1054 _public member_ `DynArray<float> us;`
- L1055 _public member_ `DynArray<float> vs;`
- L1057 _public function_ `explicit RawTextureCoordinateVector(MemoryResource* memRes) : us`
- L1063 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1070 _public function_ `std::size_t size() const`
- L1075 _public function_ `void clear()`

#### struct `gs4::RawVertexLayoutVector`  
`struct RawVertexLayoutVector`  
_L1081-1112_
- L1082 _public member_ `DynArray<std::uint32_t> positions;`
- L1083 _public member_ `DynArray<std::uint32_t> textureCoordinates;`
- L1084 _public member_ `DynArray<std::uint32_t> normals;`
- L1086 _public function_ `explicit RawVertexLayoutVector(MemoryResource* memRes) : positions`
- L1093 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1102 _public function_ `std::size_t size() const`
- L1107 _public function_ `void clear()`

#### struct `gs4::RawFace`  
`struct RawFace`  
_L1114-1126_
- L1115 _public member_ `DynArray<std::uint32_t> layoutIndices;`
- L1117 _public function_ `explicit RawFace(MemoryResource* memRes) : layoutIndices`
- L1122 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawVertexSkinWeights`  
`struct RawVertexSkinWeights`  
_L1128-1144_
- L1129 _public member_ `AlignedDynArray<float> weights;`
- L1130 _public member_ `DynArray<std::uint16_t> jointIndices;`
- L1132 _public function_ `explicit RawVertexSkinWeights(MemoryResource* memRes) : weights`
- L1138 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawBlendShapeTarget`  
`struct RawBlendShapeTarget`  
_L1146-1166_
- L1147 _public member_ `RawVector3Vector deltas;`
- L1148 _public member_ `DynArray<std::uint32_t> vertexIndices;`
- L1149 _public member_ `std::uint16_t blendShapeChannelIndex;`
- L1151 _public function_ `explicit RawBlendShapeTarget(MemoryResource* memRes) : deltas`
- L1158 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMesh`  
`struct RawMesh`  
_L1168-1259_
- L1169 _public member_ `terse::ArchiveOffset<std::uint32_t> offset;`
- L1170 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1171 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1172 _public member_ `RawVector3Vector positions;`
- L1173 _public member_ `RawTextureCoordinateVector textureCoordinates;`
- L1174 _public member_ `RawVector3Vector normals;`
- L1175 _public member_ `RawVertexLayoutVector layouts;`
- L1176 _public member_ `Vector<RawFace> faces;`
- L1177 _public member_ `std::uint16_t maximumInfluencePerVertex;`
- L1178 _public member_ `Vector<RawVertexSkinWeights> skinWeights;`
- L1179 _public member_ `Vector<RawBlendShapeTarget> blendShapeTargets;`
- L1180 _public member_ `terse::ArchiveOffset<std::uint32_t>::Proxy offsetMarker;`
- L1181 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1183 _public function_ `explicit RawMesh(MemoryResource* memRes) : offset`
- L1200 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1206 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> )`
- L1232 _public function_ `template<class Archive, typename AnyVersion> void serialize(Archive& archive, AnyVersion)`

#### struct `gs4::RawGeometry`  
`struct RawGeometry`  
_L1261-1273_
- L1262 _public member_ `Vector<RawMesh> meshes;`
- L1264 _public function_ `explicit RawGeometry(MemoryResource* memRes) : meshes`
- L1269 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawActivationFunction`  
`struct RawActivationFunction`  
_L1275-1291_
- L1276 _public member_ `std::uint16_t functionId;`
- L1277 _public member_ `DynArray<float> parameters;`
- L1279 _public function_ `explicit RawActivationFunction(MemoryResource* memRes) : functionId`
- L1285 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawNeuralNetworkLayer`  
`struct RawNeuralNetworkLayer`  
_L1293-1313_
- L1294 _public member_ `DynArray<float> biases;`
- L1295 _public member_ `DynArray<float> weights;` — 2D Matrix
- L1296 _public member_ `RawActivationFunction activationFunction;`
- L1298 _public function_ `explicit RawNeuralNetworkLayer(MemoryResource* memRes) : biases`
- L1305 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawNeuralNetwork`  
`struct RawNeuralNetwork`  
_L1315-1345_
- L1316 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1317 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1318 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1319 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1320 _public member_ `Vector<RawNeuralNetworkLayer> layers;`
- L1321 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1323 _public function_ `explicit RawNeuralNetwork(MemoryResource* memRes) : size`
- L1333 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMeshRegionMembership`  
`struct RawMeshRegionMembership`  
_L1347-1363_
- L1348 _public member_ `Matrix<String<char>> regionNames;` — [meshIndex][regionIndex]
- L1349 _public member_ `Vector<Matrix<std::uint16_t>> indices;` — [meshIndex][regionIndex][neuralNetworkIndices...]
- L1351 _public function_ `explicit RawMeshRegionMembership(MemoryResource* memRes) : regionNames`
- L1357 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMachineLearnedBehavior`  
`struct RawMachineLearnedBehavior`  
_L1365-1389_
- L1366 _public member_ `Vector<String<char>> mlControlNames;`
- L1367 _public member_ `RawLODMapping lodNeuralNetworkMapping;`
- L1368 _public member_ `RawMeshRegionMembership neuralNetworkToMeshRegion;`
- L1369 _public member_ `Vector<RawNeuralNetwork> neuralNetworks;`
- L1371 _public function_ `explicit RawMachineLearnedBehavior(MemoryResource* memRes) : mlControlNames`
- L1379 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawRBFPose`  
`struct RawRBFPose`  
_L1391-1407_
- L1392 _public member_ `String<char> name;`
- L1393 _public member_ `float scale;`
- L1395 _public function_ `explicit RawRBFPose(MemoryResource* memRes) : name`
- L1401 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawRBFPoseExt`  
`struct RawRBFPoseExt`  
_L1409-1429_
- L1410 _public member_ `DynArray<std::uint16_t> inputControlIndices;`
- L1411 _public member_ `DynArray<std::uint16_t> outputControlIndices;`
- L1412 _public member_ `DynArray<float> outputControlWeights;`
- L1414 _public function_ `explicit RawRBFPoseExt(MemoryResource* memRes) : inputControlIndices`
- L1421 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawRBFSolver`  
`struct RawRBFSolver`  
_L1431-1497_
- L1432 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t> size;`
- L1433 _public member_ `terse::Anchor<std::uint32_t> baseMarker;`
- L1434 _public member_ `String<char> name;`
- L1435 _public member_ `DynArray<std::uint16_t> rawControlIndices;`
- L1436 _public member_ `DynArray<std::uint16_t> poseIndices;`
- L1437 _public member_ `DynArray<float> rawControlValues;`
- L1438 _public member_ `float radius;`
- L1439 _public member_ `float weightThreshold;`
- L1440 _public member_ `std::uint16_t solverType;`
- L1441 _public member_ `std::uint16_t automaticRadius;`
- L1442 _public member_ `std::uint16_t distanceMethod;`
- L1443 _public member_ `std::uint16_t normalizeMethod;`
- L1444 _public member_ `std::uint16_t functionType;`
- L1445 _public member_ `std::uint16_t twistAxis;`
- L1446 _public member_ `terse::ArchiveSize<std::uint32_t, std::uint32_t>::Proxy sizeMarker;`
- L1448 _public function_ `explicit RawRBFSolver(MemoryResource* memRes) : size`
- L1467 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawRBFBehavior`  
`struct RawRBFBehavior`  
_L1499-1519_
- L1500 _public member_ `RawLODMapping lodSolverMapping;`
- L1501 _public member_ `Vector<RawRBFSolver> solvers;`
- L1502 _public member_ `Vector<RawRBFPose> poses;`
- L1504 _public function_ `explicit RawRBFBehavior(MemoryResource* memRes) : lodSolverMapping`
- L1511 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawRBFBehaviorExt`  
`struct RawRBFBehaviorExt`  
_L1521-1537_
- L1522 _public member_ `Vector<String<char>> poseControlNames;`
- L1523 _public member_ `Vector<RawRBFPoseExt> poses;`
- L1525 _public function_ `explicit RawRBFBehaviorExt(MemoryResource* memRes) : poseControlNames`
- L1531 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawJointRepresentation`  
`struct RawJointRepresentation`  
_L1539-1553_
- L1540 _public member_ `std::uint16_t translation;`
- L1541 _public member_ `std::uint16_t rotation;`
- L1542 _public member_ `std::uint16_t scale;`
- L1545 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawJointBehaviorMetadata`  
`struct RawJointBehaviorMetadata`  
_L1555-1567_
- L1556 _public member_ `Vector<RawJointRepresentation> jointRepresentations;`
- L1558 _public function_ `explicit RawJointBehaviorMetadata(MemoryResource* memRes) : jointRepresentations`
- L1563 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawTwist`  
`struct RawTwist`  
_L1569-1593_
- L1570 _public member_ `DynArray<float> twistBlendWeights;`
- L1571 _public member_ `DynArray<std::uint16_t> twistOutputJointIndices;`
- L1572 _public member_ `DynArray<std::uint16_t> twistInputControlIndices;`
- L1573 _public member_ `std::uint16_t twistAxis;`
- L1575 _public function_ `explicit RawTwist(MemoryResource* memRes) : twistBlendWeights`
- L1583 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawSwing`  
`struct RawSwing`  
_L1595-1619_
- L1596 _public member_ `DynArray<float> swingBlendWeights;`
- L1597 _public member_ `DynArray<std::uint16_t> swingOutputJointIndices;`
- L1598 _public member_ `DynArray<std::uint16_t> swingInputControlIndices;`
- L1599 _public member_ `std::uint16_t twistAxis;`
- L1601 _public function_ `explicit RawSwing(MemoryResource* memRes) : swingBlendWeights`
- L1609 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawTwistSwingBehavior`  
`struct RawTwistSwingBehavior`  
_L1621-1637_
- L1622 _public member_ `Vector<RawTwist> twists;`
- L1623 _public member_ `Vector<RawSwing> swings;`
- L1625 _public function_ `explicit RawTwistSwingBehavior(MemoryResource* memRes) : twists`
- L1631 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMLOperation`  
`struct RawMLOperation`  
_L1639-1663_
- L1640 _public member_ `DynArray<std::uint32_t> parameters;`
- L1641 _public member_ `DynArray<std::uint16_t> mlOperationSetDependencyIndices;`
- L1642 _public member_ `DynArray<std::uint16_t> mlOperationDependencyIndices;`
- L1643 _public member_ `std::uint16_t operationType;`
- L1645 _public function_ `explicit RawMLOperation(MemoryResource* memRes) : parameters`
- L1653 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMachineLearnedBehaviorTypeData`  
`struct RawMachineLearnedBehaviorTypeData`  
_L1665-1681_
- L1666 _public member_ `Vector<RawLODMapping> lodMLOperationMappings;`
- L1667 _public member_ `Matrix<RawMLOperation> operations;`
- L1669 _public function_ `explicit RawMachineLearnedBehaviorTypeData(MemoryResource* memRes) : lodMLOperationMappings`
- L1675 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMachineLearnedBehaviorJoints`  
`struct RawMachineLearnedBehaviorJoints`  
_L1683-1707_
- L1684 _public member_ `DynArray<std::uint16_t> parameterKeys;`
- L1685 _public member_ `DynArray<std::uint16_t> parameterValues;`
- L1686 _public member_ `DynArray<std::uint16_t> inputIndices;`
- L1687 _public member_ `DynArray<std::uint16_t> outputIndices;`
- L1689 _public function_ `explicit RawMachineLearnedBehaviorJoints(MemoryResource* memRes) : parameterKeys`
- L1697 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::RawMachineLearnedBehaviorExt`  
`struct RawMachineLearnedBehaviorExt`  
_L1709-1725_
- L1710 _public member_ `Vector<RawMachineLearnedBehaviorTypeData> mlbTypeData;`
- L1711 _public member_ `RawMachineLearnedBehaviorJoints mlbJoints;`
- L1713 _public function_ `explicit RawMachineLearnedBehaviorExt(MemoryResource* memRes) : mlbTypeData`
- L1719 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::DNA`  
`struct DNA`  
_L1727-1925_
- L1728 _public member_ `MemoryResource* memRes;`
- L1729 _public member_ `Signature<3> signature{{'D', 'N', 'A'}};`
- L1730 _public member_ `Version version{FileVersion::latest};`
- L1731 _public member_ `IndexTable indexTable;`
- L1732 _public member_ `Layer<sid4("desc"), rev(1, 1), RawDescriptor, FileVersion::v22> descrip`
- L1733 _public member_ `Layer<sid4("defn"), rev(1, 1), RawDefinition, FileVersion::v22> definit`
- L1734 _public member_ `Layer<sid4("bhvr"), rev(1, 1), RawBehavior, FileVersion::v22> behav`
- L1735 _public member_ `Layer<sid4("geom"), rev(1, 1), RawGeometry, FileVersion::v22> geome`
- L1736 _public member_ `Layer<sid4("mlbh"), rev(1, 0), RawMachineLearnedBehavior, FileVersion::v23> machineLearnedBehav`
- L1737 _public member_ `Layer<sid4("rbfb"), rev(1, 0), RawRBFBehavior, FileVersion::v24> rbfBehav`
- L1738 _public member_ `Layer<sid4("rbfe"), rev(1, 0), RawRBFBehaviorExt, FileVersion::v25> rbfBehavior`
- L1739 _public member_ `Layer<sid4("jbmd"), rev(1, 0), RawJointBehaviorMetadata, FileVersion::v24> jointBehaviorMetad`
- L1740 _public member_ `Layer<sid4("twsw"), rev(1, 0), RawTwistSwingBehavior, FileVersion::v24> twistSwingBehav`
- L1741 _public member_ `Layer<sid4("mlbe"), rev(1, 0), RawMachineLearnedBehaviorExt, FileVersion::v26> machineLearnedBehavior`
- L1742 _public member_ `Layer<sid4("dsce"), rev(1, 0), RawDescriptorExt, FileVersion::v27> descriptor`
- L1744 _public typedef_ `using Layers = LayerContainer<decltype(descriptor), decltype(definition), decltype(behavior), decltype(geometry), decltype(machineLearnedBehavior), decltype(rbfBehavior), decltype(rbfBehaviorExt), decltype(jointBehaviorMetadata), decltype(twistSwingBehavior), decltype(machineLearnedBehaviorExt), decltype(descriptorExt)>;`
- L1755 _public member_ `Layers layers;`
- L1757 _public function_ `DNA(UnknownLayerPolicy unknownPolicy, UpgradeFormatPolicy upgradePolicy, MemoryResource* memRes_) : memRes`
- L1787 _public function_ `explicit DNA(MemoryResource* memRes_) : DNA`
- L1792 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L1810 _public function_ `template<class Archive> void serialize(Archive& archive, terse::Version<FileVersion::v21> v21)`
- L1839 _public function_ `template<class Archive, typename AnyVersion> IfHigher<AnyVersion, FileVersion::v21> load(Archive& archive, AnyVersion)`
- L1865 _public function_ `template<class Archive, typename AnyVersion> IfHigher<AnyVersion, FileVersion::v21> save(Archive& archive, AnyVersion)`
- L1880 _public function_ `void postLoadActions()`
- L1896 _public function_ `void unloadDefinition()`
- L1900 _public function_ `void unloadBehavior()`
- L1904 _public function_ `void unloadGeometry()`
- L1908 _public function_ `void unloadMachineLearnedBehavior()`
- L1913 _public function_ `void unloadRBFBehavior()`
- L1918 _public function_ `void unloadJointBehaviorMetadata()`
- L1922 _public function_ `void unloadTwistSwingBehavior()`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace tdm`
- L39 _macro_ `#define TDM_ROT_SEQ_SERIALIZER_DEFINED`
- L42 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L50 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L58 _macro_ `#define TDM_ROT_SIGN_SERIALIZER_DEFINED`
- L61 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L78 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L93 _namespace_ `namespace gs4`
- L102 _function_ `template<typename Archive> void load(Archive& archive, FaceWindingOrder& value)` (scope `gs4`)
- L110 _function_ `template<typename Archive> void save(Archive& archive, FaceWindingOrder& value)` (scope `gs4`)
- L155 _function_ `static constexpr std::uint32_t sid4(const char* name)` (scope `gs4`)
- L160 _function_ `static constexpr std::uint32_t rev(std::uint16_t generation, std::uint16_t version)` (scope `gs4`)
- L164 _function_ `static constexpr std::uint16_t high16(std::uint32_t packed)` (scope `gs4`)
- L168 _function_ `static constexpr std::uint16_t low16(std::uint32_t packed)` (scope `gs4`)
- L185 _typedef_ `using Dispatch = Dispatcher<FileVersion, FileVersion::v21, FileVersion::v22, FileVersion::v23, FileVersion::v24, FileVersion::v25, FileVersion::v26, FileVersion::v27, FileVersion::v28>;` (scope `gs4`)
- L196 _typedef_ `template<typename A, FileVersion B> using IfHigher = typename std::enable_if<(A::value() > B), void>::type;` (scope `gs4`)
- L199 _typedef_ `template<typename A, FileVersion B> using IfLower = typename std::enable_if<(A::value() < B), void>::type;` (scope `gs4`)
- L333 _function_ `std::remove_if(entries.begin(), entries.end(), [id, version](const Index& index) { return (index.id == id) && (index.version == version); }), entries.end());` (scope `gs4::IndexTable::destroy`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/DenormalizedData.h` (Private)


#### struct `gs4::DenormalizedData`  
`template<class Reader> struct DenormalizedData`  
_L24-356_
- L25 _public member_ `LODMapping jointVariableAttributeIndices;`
- L26 _public member_ `LODMapping meshBlendShapeMappingIndices;`
- L27 _public member_ `Matrix<std::uint16_t> rbfPoseJointOutputIndices;`
- L28 _public member_ `Matrix<float> rbfPoseJointOutputValues;`
- L29 _public member_ `Matrix<std::uint16_t> rbfBlendShapeChannelOutputIndices;`
- L30 _public member_ `Matrix<std::uint16_t> rbfAnimatedMapOutputIndices;`
- L31 _public member_ `Vector<Matrix<std::uint32_t>> mlOperationParameters;`
- L32 _public member_ `Vector<Matrix<std::uint16_t>> mlDependencyOperationSetIndices;`
- L33 _public member_ `Vector<Matrix<std::uint16_t>> mlDependencyOperationIndices;`
- L35 _public function_ `explicit DenormalizedData(MemoryResource* memRes) : jointVariableAttributeIndices`
- L48 _public function_ `void populate(const Reader* source)`
- L60 _public function_ `void populateJointVariableAttributeIndices(const Reader* source)`
- L173 _public function_ `void populateMeshBlendShapeMappingIndices(const Reader* source)`
- L202 _public function_ `void populateRBFPoseJointOutputIndices(const Reader* source)`
- L228 _public function_ `void populateRBFPoseJointOutputValues(const Reader* source)`
- L279 _public function_ `void populateRBFBlendShapeOutputIndices(const Reader* source)`
- L299 _public function_ `void populateRBFAnimatedMapOutputIndices(const Reader* source)`
- L318 _public function_ `void populateMLOperationParameters(const Reader* source)`
- L333 _public function_ `void populateMLDependencyOperationSetIndices(const Reader* source)`
- L345 _public function_ `void populateMLDependencyOperationIndices(const Reader* source)`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace gs4`
- L87 _function_ `auto isJointInLOD = [source](std::uint16_t jointIndex, std::uint16_t lod)` (scope `gs4::DenormalizedData::populateJointVariableAttributeIndices`)
- L92 _function_ `auto getNumMLAttributesPerJoint = [source]()` (scope `gs4::DenormalizedData::populateJointVariableAttributeIndices`)
- L183 _function_ `auto isMappingNeeded = [&meshIndices, &blendShapeIndices](const MeshBlendShapeChannelMapping& mapping)` (scope `gs4::DenormalizedData::populateMeshBlendShapeMappingIndices`)
- L233 _function_ `auto jointIndexToJointGroupMap = [&]()` (scope `gs4::DenormalizedData::populateRBFPoseJointOutputValues`)
- L245 _function_ `const auto indexOf = [](ConstArrayView<std::uint16_t> container, std::uint16_t val)` (scope `gs4::DenormalizedData::populateRBFPoseJointOutputValues`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/Extd.h` (Private)


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

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/LODConstraint.h` (Private)


#### class `gs4::LODConstraint`  
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

- L9 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/LODMapping.h` (Private)


#### class `gs4::LODMapping`  
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

- L18 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/ReaderImpl.h` (Private)


#### class `gs4::ReaderImpl`  
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

- L21 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/SurjectiveMapping.h` (Private)


#### struct `gs4::SurjectiveMapping`  
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

#### struct `gs4::SurjectiveMapping::Pair`  
`struct Pair`  
_L22-25_
- L23 _public member_ `TFrom from;`
- L24 _public member_ `TTo to;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace gs4`
- L90 _function_ `std::transform(target.begin(), target.end(), target.begin(), [&mapping](U oldValue) { return mapping.at(oldValue); });` (scope `gs4::SurjectiveMapping::update`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/dna/WriterImpl.h` (Private)


#### class `gs4::WriterImpl`  
`template<class TWriterBase> class WriterImpl : public virtual TWriterBase, public virtual BaseImpl`  
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

- L24 _namespace_ `namespace gs4`
- L28 _function_ `ensureHasSize(TContainer& target, std::size_t size)` (scope `gs4`)
- L44 _function_ `template<class TContainer, typename U> typename std::enable_if<std::is_integral<U>::value, typename TContainer::value_type&>::type getAt(TContainer& target, U index)` (scope `gs4`)
- L50 _function_ `template<class TContainer, typename TSize, typename TValue> typename std::enable_if<std::is_integral<TSize>::value>::type setAt(TContainer& target, TSize index, const TValue& value)` (scope `gs4`)
- L388 _typedef_ `using CharStringPair = std::tuple<String<char>, String<char>>;` (scope `gs4::WriterImpl::setMetaData`)
- L389 _function_ `auto it = std::find_if(dna.descriptor.metadata.begin(), dna.descriptor.metadata.end(), [&key](const CharStringPair& kv) { auto& k = std::get<0>(kv); return (std::strlen(key) == k.size() && std::strncmp(k.data(), key, k.size()) == 0); });` (scope `gs4::WriterImpl::setMetaData`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/geometrysplicer/NeutralMeshSplicer.h` (Private)


#### class `gs4::NeutralMeshSplicer`  
`template<CalculationType CT> class NeutralMeshSplicer : public Splicer`  
_L17-22_
- inherits: `Splicer`
- L21 _public prototype_ `void splice(const SpliceDataInterface* spliceData, GeneSplicerDNAReader* output) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/jointbehaviorsplicer/JointBehaviorSplicer.h` (Private)


#### class `gs4::JointBehaviorSplicer`  
`template<CalculationType CT> class JointBehaviorSplicer : public Splicer`  
_L13-18_
- inherits: `Splicer`
- L17 _public prototype_ `void splice(const SpliceDataInterface* spliceData, GeneSplicerDNAReader* output) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/neutraljointsplicer/JointAttribute.h` (Private)


#### enum `gs4::JointAttribute`  
`enum class JointAttribute`  
_L7-10_
- L8 _public enumerator_ `Translation`
- L9 _public enumerator_ `Rotation`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/neutraljointsplicer/JointAttributeSpecialization.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace gs4`
- L13 _prototype_ `template<JointAttribute T> FORCE_INLINE ConstVec3VectorView getJointAttributeValues(const Reader* const reader);` (scope `gs4`)
- L16 _function_ `template<> FORCE_INLINE ConstVec3VectorView getJointAttributeValues<JointAttribute::Translation>(const Reader* const reader)` (scope `gs4`)
- L23 _function_ `template<> FORCE_INLINE ConstVec3VectorView getJointAttributeValues<JointAttribute::Rotation>(const Reader* const reader)` (scope `gs4`)
- L30 _prototype_ `template<JointAttribute T> FORCE_INLINE Vec3 getJointAttributeValue(const Reader* const reader, std::uint16_t jointIndex);` (scope `gs4`)
- L33 _function_ `template<> FORCE_INLINE Vec3 getJointAttributeValue<JointAttribute::Translation>(const Reader* const reader, std::uint16_t jointIndex)` (scope `gs4`)
- L38 _function_ `template<> FORCE_INLINE Vec3 getJointAttributeValue<JointAttribute::Rotation>(const Reader* const reader, std::uint16_t jointIndex)` (scope `gs4`)
- L43 _prototype_ `template<JointAttribute T> FORCE_INLINE void setJointAttributeValues(GeneSplicerDNAReaderImpl* output, RawVector3Vector& result);` (scope `gs4`)
- L46 _function_ `template<> FORCE_INLINE void setJointAttributeValues<JointAttribute::Translation>(GeneSplicerDNAReaderImpl* output, RawVector3Vector& result)` (scope `gs4`)
- L52 _function_ `template<> FORCE_INLINE void setJointAttributeValues<JointAttribute::Rotation>(GeneSplicerDNAReaderImpl* output, RawVector3Vector& result)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/neutraljointsplicer/NeutralJointSplicer.h` (Private)


#### class `gs4::NeutralJointSplicer`  
`template<CalculationType CT> class NeutralJointSplicer : public Splicer`  
_L14-19_
- inherits: `Splicer`
- L18 _public prototype_ `void splice(const SpliceDataInterface* spliceData, GeneSplicerDNAReader* output) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/skinweightsplicer/SkinWeightMeshSplicer.h` (Private)


#### class `gs4::SkinWeightMeshSplicer`  
`template<CalculationType CT> class SkinWeightMeshSplicer`  
_L19-51_
- L21 _public typedef_ `using AlignedVBlock16Vector = Vector<VBlock<16>, PolyAllocator<VBlock<16>, 64>>;`
- L33 _public prototype_ `SkinWeightMeshSplicer(ConstArrayView<const PoolSpliceParamsImpl*> pools, std::uint16_t meshIndex, MemoryResource* memRes);`
- L34 _public prototype_ `Vector<RawVertexSkinWeights> spliceMesh(const Vector<RawVertexSkinWeights>& baseArchetypeMeshSkinWeights, MemoryResource* outputMemRes) const;`
- L38 _private prototype_ `ConstArrayView<std::uint16_t> getJointIndices(std::uint32_t vertexIndex) const;`
- L39 _private prototype_ `MemoryResource* getMemoryResource() const;`
- L41 _private prototype_ `void prune(RawVertexSkinWeights& vtxRes) const;`
- L42 _private prototype_ `VBlock<16> spliceAndNormalize(std::uint32_t blockIndex, AlignedVBlock16Vector& blockResult) const;`
- L44 _private prototype_ `void spliceBlock(std::uint32_t blockIndex, ArrayView<RawVertexSkinWeights> outputBlock) const;`
- L47 _private member_ `Vector<GenePoolDetails> genePools;`
- L48 _private member_ `const VariableWidthMatrix<uint16_t>* jointIndices;`
- L49 _private member_ `std::uint32_t skinWeightCount;`
- L50 _private member_ `std::uint16_t maximumInfluences;`

#### struct `gs4::SkinWeightMeshSplicer::GenePoolDetails`  
`struct GenePoolDetails`  
_L24-30_
- L26 _public prototype_ `GenePoolDetails(const PoolSpliceParamsImpl* pool, std::uint16_t meshIndex);`
- L27 _public member_ `ConstArrayView<TiledMatrix2D<16u>> meshDNABlocks;`
- L28 _public member_ `Matrix2DView<const VBlock<16>> meshWeights;`
- L29 _public member_ `ConstArrayView<std::uint16_t> dnaIndices;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/skinweightsplicer/SkinWeightSplicer.h` (Private)


#### class `gs4::SkinWeightSplicer`  
`template<CalculationType CT> class SkinWeightSplicer : public Splicer`  
_L13-18_
- inherits: `Splicer`
- L17 _public prototype_ `void splice(const SpliceDataInterface* spliceData, GeneSplicerDNAReader* output) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/JointWeights.h` (Private)


#### class `gs4::JointWeights`  
`class JointWeights`  
_L16-29_
- L18 _public prototype_ `explicit JointWeights(const JointRegionAffiliationReader* jointRegionAffiliation, MemoryResource* memRes);`
- L20 _public prototype_ `void compute(const SpliceWeights& spliceWeights, ConstArrayView<std::uint16_t> dnaIndices);`
- L22 _public prototype_ `bool empty() const;`
- L23 _public prototype_ `void clear();`
- L24 _public prototype_ `const TiledMatrix2D<16u>& getData() const;`
- L27 _private member_ `TiledMatrix2D<16u> weights;`
- L28 _private member_ `Vector<RegionAffiliation<>> regionAffiliations;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/PoolSpliceParamsFilter.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace gs4`
- L13 _function_ `template<typename TFilter> VariableWidthMatrix<const PoolSpliceParamsImpl*> filterPoolSpliceParamsPerMesh(const SpliceDataInterface* spliceData, TFilter predicate, MemoryResource* memRes)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/PoolSpliceParamsImpl.h` (Private)


#### class `gs4::PoolSpliceParamsImpl`  
`class PoolSpliceParamsImpl : public PoolSpliceParams`  
_L22-77_
- inherits: `PoolSpliceParams`
- L25 _public prototype_ `static PoolSpliceParamsImpl* create(const RegionAffiliationReader* regionAffiliationReader, const GenePool* genePool, MemoryResource* memRes_);`
- L28 _public prototype_ `static void destroy(PoolSpliceParamsImpl* instance);`
- L31 _private prototype_ `static bool compatible(const RegionAffiliationReader* regionAffiliationReader, const GenePool* genePool, MemoryResource* memRes_);`
- L36 _public prototype_ `PoolSpliceParamsImpl(const RegionAffiliationReader* regionAffiliationReader, const GenePoolInterface* genePool, MemoryResource* memRes_);`
- L40 _public prototype_ `void setSpliceWeights(std::uint16_t dnaStartIndex, const float* weights, std::uint32_t count) override;`
- L41 _public prototype_ `void setMeshFilter(const std::uint16_t* meshIndices, std::uint16_t count) override;`
- L42 _public prototype_ `void setDNAFilter(const std::uint16_t* dnaIndices, std::uint16_t count) override;`
- L43 _public prototype_ `void clearFilters() override;`
- L44 _public prototype_ `void setScale(float scale) override;`
- L46 _public prototype_ `void generateJointBehaviorOutputIndexTargetOffsets(const RawGenes& baseArchetype);`
- L47 _public prototype_ `const Matrix2D<std::uint8_t>& getJointBehaviorOutputIndexTargetOffsets() const;`
- L49 _public prototype_ `ConstArrayView<float> getSpliceWeights(std::uint16_t dnaIndex) const;`
- L50 _public prototype_ `ConstArrayView<std::uint16_t> getMeshIndices() const;`
- L51 _public prototype_ `ConstArrayView<std::uint16_t> getDNAIndices() const;`
- L53 _public prototype_ `bool isMeshEnabled(std::uint16_t meshIndex) const;`
- L55 _public prototype_ `const Matrix2D<float>& getSpliceWeightsData() const;`
- L56 _public prototype_ `const Vector<TiledMatrix2D<16u>>& getVertexWeightsData() const;`
- L57 _public prototype_ `const TiledMatrix2D<16u>& getJointWeightsData() const;`
- L58 _public prototype_ `const GenePoolInterface* getGenePool() const;`
- L59 _public prototype_ `float getScale() const;`
- L60 _public prototype_ `std::uint16_t getDNACount() const override;`
- L61 _public prototype_ `std::uint16_t getRegionCount() const override;`
- L63 _public prototype_ `void cacheAll();`
- L64 _public prototype_ `void clearAll();`
- L67 _private member_ `static sc::StatusProvider status;`
- L68 _private member_ `MemoryResource* memRes;`
- L69 _private member_ `const GenePoolInterface* genePool;`
- L70 _private member_ `SpliceWeights spliceWeights;`
- L71 _private member_ `mutable VertexWeights vertexWeights;`
- L72 _private member_ `mutable JointWeights jointWeights;`
- L73 _private member_ `Vector<std::uint16_t> dnaIndices;`
- L74 _private member_ `Vector<std::uint16_t> meshIndices;`
- L75 _private member_ `OutputIndexTargetOffsets jointBehaviorOutputIndexTargets;`
- L76 _private member_ `float scale;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<gs4::PoolSpliceParamsImpl>`  
_L84-86_
- L85 _public typedef_ `using type = FactoryCreate<gs4::PoolSpliceParamsImpl>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<gs4::PoolSpliceParamsImpl>`  
_L89-91_
- L90 _public typedef_ `using type = FactoryDestroy<gs4::PoolSpliceParamsImpl>;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace gs4`
- L81 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/RegionAffiliation.h` (Private)


#### struct `gs4::RegionAffiliation`  
`template<std::uint16_t N = 1u> struct RegionAffiliation`  
_L20-84_
- L28 _public function_ `static constexpr std::size_t firstNSize()`
- L32 _public function_ `explicit RegionAffiliation(MemoryResource* memRes) : rest`
- L37 _public function_ `RegionAffiliation(ConstArrayView<std::uint16_t> regionIndices, ConstArrayView<float> values, MemoryResource* memRes) : rest`
- L62 _public function_ `float totalWeightAcrossRegions(ConstArrayView<float> weightsPerRegion) const`
- L82 _public member_ `Vector<IndexValue> rest;`
- L83 _public member_ `std::array<IndexValue, N> firstN;`

#### struct `gs4::RegionAffiliation::IndexValue`  
`struct IndexValue`  
_L22-25_
- L23 _public member_ `float value;`
- L24 _public member_ `std::uint16_t index;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/SpliceDataImpl.h` (Private)


#### class `gs4::SpliceData::Impl`  
`class SpliceData::Impl`  
_L29-58_
- L31 _public typedef_ `using pool_name_type = String<char>;`
- L34 _public prototype_ `static Impl* create(MemoryResource* memRes_);`
- L35 _public prototype_ `static void destroy(Impl* instance);`
- L38 _public prototype_ `Impl(MemoryResource* memRes_);`
- L40 _public prototype_ `void registerGenePool(StringView name, const RegionAffiliationReader* reader, const GenePool* genePool);`
- L41 _public prototype_ `void unregisterGenePool(StringView name);`
- L43 _public prototype_ `PoolSpliceParams* getPoolParams(StringView name);`
- L44 _public prototype_ `Vector<const PoolSpliceParamsImpl*> getAllPoolParams() const;`
- L46 _public prototype_ `void setBaseArchetype(const dna::Reader* baseArchetype);`
- L47 _public prototype_ `const RawGenes& getBaseArchetype() const;`
- L49 _public prototype_ `void cacheAll();`
- L52 _private prototype_ `void accustimizePoolsAndBaseArch();`
- L55 _private member_ `MemoryResource* memRes;`
- L56 _private member_ `UnorderedMap<std::string, ScopedPtr<PoolSpliceParamsImpl>> pools;`
- L57 _private member_ `RawGenes baseArchetype;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace gs4`
- L28 _typedef_ `using SpliceDataInterface = PImplExtractor<SpliceData>::impl_type;` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/SpliceWeights.h` (Private)


#### class `gs4::SpliceWeights`  
`class SpliceWeights`  
_L14-26_
- L16 _public prototype_ `explicit SpliceWeights(std::uint16_t dnaCount, std::uint16_t regionCount, MemoryResource* memRes);`
- L17 _public prototype_ `void set(std::uint16_t dnaStartIndex, ConstArrayView<float> weights);`
- L19 _public prototype_ `ConstArrayView<float> get(std::uint16_t dnaIdx) const;`
- L20 _public prototype_ `const Matrix2D<float>& getData() const;`
- L21 _public prototype_ `std::uint16_t getDNACount() const;`
- L22 _public prototype_ `std::uint16_t getRegionCount() const;`
- L25 _private member_ `Matrix2D<float> weights;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/VertexWeights.h` (Private)


#### class `gs4::VertexWeights`  
`class VertexWeights`  
_L17-31_
- L20 _public prototype_ `explicit VertexWeights(const VertexRegionAffiliationReader* regionAffiliationReader, MemoryResource* memRes);`
- L21 _public prototype_ `void compute(const SpliceWeights& spliceWeights, ConstArrayView<std::uint16_t> meshIndices, ConstArrayView<std::uint16_t> dnaIndices);`
- L24 _public prototype_ `void clear();`
- L25 _public prototype_ `bool empty() const;`
- L26 _public prototype_ `const Vector<TiledMatrix2D<16u>>& getData() const;`
- L29 _private member_ `Vector<TiledMatrix2D<16u>> weights;`
- L30 _private member_ `VariableWidthMatrix<RegionAffiliation<>> regionAffiliations;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/BlendShapeDeltas.h` (Private)


#### struct `gs4::BlendShapeDeltas`  
`template<std::uint16_t BlockSize> struct BlendShapeDeltas`  
_L26-66_
- desc: In order to reduce the size of BlendShapePool and increase cache efficiency we keep each of the above in corresponding vector. But we'll need two more vectors: 1. bucketOffsets will tell us the offset of the first bucket in each Blend Shape. 2. bucketDNABlockOffset indicates offset within the dnaBlocks vector for the initial dnaBlock in each bucket. This aligns with the offset of the first dnaIndex within a bucket in the dnaIndices vector.
- L28 _public function_ `BlendShapeDeltas(MemoryResource* memRes) : bucketOffsets`
- L37 _public function_ `std::uint16_t getBlockSize() const`
- L42 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L46 _public function_ `void shrinkToFit()`
- L56 _public member_ `VariableWidthMatrix<std::size_t> bucketOffsets;` — [meshIndex][bsIndex]
- L59 _public member_ `Vector<std::uint32_t> bucketVertexIndices;` — [bucketOffset]
- L60 _public member_ `Vector<std::size_t> bucketDNABlockOffsets;`
- L61 _public member_ `AlignedVector<XYZBlock<BlockSize>> archBlocks;`
- L64 _public member_ `Vector<std::uint16_t> dnaIndices;` — [blockOffset]
- L65 _public member_ `AlignedVector<XYZBlock<BlockSize>> dnaBlocks;`

#### struct `gs4::BlendShapeDeltasFactory`  
`template<std::uint16_t BlockSize> struct BlendShapeDeltasFactory`  
_L69-73_
- L70 _public prototype_ `BlendShapeDeltas<BlockSize> operator()(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnas, MemoryResource* memRes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/BlendShapePool.h` (Private)


#### class `gs4::BlendShapePool`  
`class BlendShapePool`  
_L17-39_
- L19 _public prototype_ `BlendShapePool(MemoryResource* memRes);`
- L20 _public prototype_ `BlendShapePool(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnas, MemoryResource* memRes = nullptr);`
- L22 _public prototype_ `ConstArrayView<VariableWidthMatrix<std::uint32_t>> getVertexIndices() const;`
- L23 _public prototype_ `const BlendShapeDeltas<4u>& getBlendShapeTargetDeltas() const;`
- L24 _public prototype_ `std::uint16_t getBlendShapeCount(std::uint16_t meshIndex) const;`
- L27 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L33 _private prototype_ `void fillVertexIndices(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnas, MemoryResource* memRes);`
- L37 _private member_ `Vector<VariableWidthMatrix<std::uint32_t>> vertexIndices;` — [meshIdx][bsIdx][deltaIdx]
- L38 _private member_ `BlendShapeDeltas<4u> deltas;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/GenePoolImpl.h` (Private)


#### class `gs4::GenePoolImpl`  
`class GenePoolImpl : public GenePoolInterface`  
_L28-212_
- inherits: `GenePoolInterface`
- L95 _private function_ `const Signature<3> getSignature()`
- L99 _private function_ `const Signature<3> getEoF()`
- L104 _public prototype_ `GenePoolImpl(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnas, GenePoolMask genePoolMask, MemoryResource* memRes_);`
- L109 _public prototype_ `explicit GenePoolImpl(MemoryResource* memRes_);`
- L111 _public prototype_ `std::uint16_t getDNACount() const override;`
- L112 _public prototype_ `StringView getDNAName(std::uint16_t dnaIndex) const override;`
- L113 _public prototype_ `dna::Gender getDNAGender(std::uint16_t dnaIndex) const override;`
- L114 _public prototype_ `std::uint16_t getDNAAge(std::uint16_t dnaIndex) const override;`
- L116 _public prototype_ `std::uint16_t getMeshCount() const override;`
- L117 _public prototype_ `std::uint32_t getVertexCount(std::uint16_t meshIndex) const override;`
- L118 _public prototype_ `std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const override;`
- L119 _public prototype_ `Vector3 getDNAVertexPosition(std::uint16_t dnaIndex, std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L120 _public prototype_ `Vector3 getArchetypeVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L122 _public prototype_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const override;`
- L124 _public prototype_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const override;`
- L125 _public prototype_ `std::uint16_t getMaximumInfluencesPerVertex(std::uint16_t meshIdx) const override;`
- L127 _public prototype_ `std::uint16_t getNeutralJointCount() const override;`
- L129 _public prototype_ `std::uint16_t getJointCount() const override;`
- L130 _public prototype_ `StringView getJointName(std::uint16_t jointIndex) const override;`
- L131 _public prototype_ `std::uint16_t getJointGroupCount() const override;`
- L133 _public prototype_ `Vector3 getDNANeutralJointWorldTranslation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const override;`
- L134 _public prototype_ `Vector3 getArchetypeNeutralJointWorldTranslation(std::uint16_t jointIndex) const override;`
- L135 _public prototype_ `Vector3 getDNANeutralJointWorldRotation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const override;`
- L136 _public prototype_ `Vector3 getArchetypeNeutralJointWorldRotation(std::uint16_t jointIndex) const override;`
- L138 _public prototype_ `ConstArrayView<XYZTiledMatrix<16u>> getNeutralMeshes() const override;`
- L140 _public prototype_ `const BlendShapeDeltas<4u>& getBlendShapeTargetDeltas() const override;`
- L141 _public prototype_ `ConstArrayView<VariableWidthMatrix<std::uint32_t>> getBlendShapeTargetVertexIndices() const override;`
- L143 _public prototype_ `const VariableWidthMatrix<TiledMatrix2D<16u>>& getSkinWeightValues() const override;`
- L144 _public prototype_ `ConstArrayView<VariableWidthMatrix<std::uint16_t>> getSkinWeightJointIndices() const override;`
- L146 _public prototype_ `const XYZTiledMatrix<16u>& getNeutralJoints(JointAttribute jointAttribute) const override;`
- L148 _public prototype_ `const VariableWidthMatrix<std::uint16_t>& getJointBehaviorInputIndices() const override;`
- L149 _public prototype_ `const VariableWidthMatrix<std::uint16_t>& getJointBehaviorOutputIndices() const override;`
- L150 _public prototype_ `const VariableWidthMatrix<std::uint16_t>& getJointBehaviorLODs() const override;`
- L151 _public prototype_ `ConstArrayView<SingleJointBehavior> getJointBehaviorValues() const override;`
- L153 _public prototype_ `MemoryResource* getMemoryResource() const override;`
- L156 _public function_ `template<class Archive> void save(Archive& archive)`
- L176 _public function_ `template<class Archive> void load(Archive& archive)`
- L201 _public prototype_ `~GenePoolImpl() = default;`
- L204 _private member_ `MemoryResource* memRes;`
- L205 _private member_ `ExpectedVersion version{0, 1};`
- L206 _private member_ `MetaData metadata;`
- L207 _private member_ `NeutralMeshPool neutralMeshes;`
- L208 _private member_ `BlendShapePool blendShapes;`
- L209 _private member_ `NeutralJointPool neutralJoints;`
- L210 _private member_ `SkinWeightPool skinWeights;`
- L211 _private member_ `JointBehaviorPool jointBehavior;`

#### struct `gs4::GenePoolImpl::SectionLookupTable`  
`struct SectionLookupTable`  
_L30-42_
- L31 _public member_ `terse::ArchiveOffset<std::uint64_t> neutralMeshes;`
- L32 _public member_ `terse::ArchiveOffset<std::uint64_t> blendShapes;`
- L33 _public member_ `terse::ArchiveOffset<std::uint64_t> neutralJoints;`
- L34 _public member_ `terse::ArchiveOffset<std::uint64_t> skinWeights;`
- L35 _public member_ `terse::ArchiveOffset<std::uint64_t> jointBehavior;`
- L36 _public member_ `terse::ArchiveOffset<std::uint64_t> metadata;`
- L39 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::GenePoolImpl::MetaData`  
`struct MetaData`  
_L44-92_
- L45 _public member_ `Vector<String<char>> names;`
- L46 _public member_ `Vector<std::uint16_t> genders;`
- L47 _public member_ `Vector<std::uint16_t> ages;`
- L48 _public member_ `Vector<String<char>> jointNames;`
- L49 _public member_ `std::uint16_t dbMaxLOD;`
- L50 _public member_ `String<char> dbName;`
- L51 _public member_ `String<char> dbComplexity;`
- L52 _public member_ `Vector<std::uint32_t> vertexCountPerMesh;`
- L53 _public member_ `GenePoolMask genePoolMask;`
- L55 _public function_ `explicit MetaData(MemoryResource* memRes) : names`
- L67 _public function_ `explicit MetaData(const Vector<String<char>>& names_, const Vector<std::uint16_t>& genders_, const Vector<std::uint16_t>& ages_, const Vector<String<char>>& jointNames_, std::uint16_t dbMaxLOD_, String<char> dbName_, String<char> dbComplexity_, const Vector<std::uint32_t>& vertexCountPerMesh_, GenePoolMask genePoolMask_, MemoryResource* memRes) : names`
- L89 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/GenePoolInterface.h` (Private)


#### class `gs4::GenePool::Impl`  
`class GenePool::Impl`  
_L22-88_
- L25 _public prototype_ `static GenePoolInterface* create(const Reader* deltaArchetype, const Reader** dnas, std::uint16_t dnaCount, GenePoolMask genePoolMask, MemoryResource* memRes);`
- L31 _public prototype_ `static GenePoolInterface* create(MemoryResource* memRes);`
- L33 _public prototype_ `static void destroy(GenePoolInterface* instance);`
- L36 _public prototype_ `virtual ~Impl();`
- L38 _public prototype_ `virtual std::uint16_t getDNACount() const = 0;`
- L39 _public prototype_ `virtual StringView getDNAName(std::uint16_t dnaIndex) const = 0;`
- L40 _public prototype_ `virtual dna::Gender getDNAGender(std::uint16_t dnaIndex) const = 0;`
- L41 _public prototype_ `virtual std::uint16_t getDNAAge(std::uint16_t dnaIndex) const = 0;`
- L43 _public prototype_ `virtual std::uint16_t getMeshCount() const = 0;`
- L44 _public prototype_ `virtual std::uint32_t getVertexCount(std::uint16_t meshIndex) const = 0;`
- L45 _public prototype_ `virtual std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const = 0;`
- L46 _public prototype_ `virtual Vector3 getDNAVertexPosition(std::uint16_t dnaIndex, std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;`
- L47 _public prototype_ `virtual Vector3 getArchetypeVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;`
- L49 _public prototype_ `virtual std::uint16_t getBlendShapeTargetCount(std::uint16_t meshIndex) const = 0;`
- L51 _public prototype_ `virtual std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const = 0;`
- L52 _public prototype_ `virtual std::uint16_t getMaximumInfluencesPerVertex(std::uint16_t meshIdx) const = 0;`
- L54 _public prototype_ `virtual std::uint16_t getNeutralJointCount() const = 0;`
- L56 _public prototype_ `virtual std::uint16_t getJointCount() const = 0;`
- L57 _public prototype_ `virtual StringView getJointName(std::uint16_t jointIndex) const = 0;`
- L58 _public prototype_ `virtual std::uint16_t getJointGroupCount() const = 0;`
- L60 _public prototype_ `virtual Vector3 getDNANeutralJointWorldTranslation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const = 0;`
- L61 _public prototype_ `virtual Vector3 getArchetypeNeutralJointWorldTranslation(std::uint16_t jointIndex) const = 0;`
- L62 _public prototype_ `virtual Vector3 getDNANeutralJointWorldRotation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const = 0;`
- L63 _public prototype_ `virtual Vector3 getArchetypeNeutralJointWorldRotation(std::uint16_t jointIndex) const = 0;`
- L65 _public prototype_ `virtual ConstArrayView<XYZTiledMatrix<16u>> getNeutralMeshes() const = 0;`
- L67 _public prototype_ `virtual const BlendShapeDeltas<4u>& getBlendShapeTargetDeltas() const = 0;`
- L68 _public prototype_ `virtual ConstArrayView<VariableWidthMatrix<std::uint32_t>> getBlendShapeTargetVertexIndices() const = 0;`
- L70 _public prototype_ `virtual const VariableWidthMatrix<TiledMatrix2D<16u>>& getSkinWeightValues() const = 0;`
- L71 _public prototype_ `virtual ConstArrayView<VariableWidthMatrix<std::uint16_t>> getSkinWeightJointIndices() const = 0;`
- L73 _public prototype_ `virtual const XYZTiledMatrix<16u>& getNeutralJoints(JointAttribute jointAttribute) const = 0;`
- L75 _public prototype_ `virtual const VariableWidthMatrix<std::uint16_t>& getJointBehaviorInputIndices() const = 0;`
- L76 _public prototype_ `virtual const VariableWidthMatrix<std::uint16_t>& getJointBehaviorOutputIndices() const = 0;`
- L77 _public prototype_ `virtual const VariableWidthMatrix<std::uint16_t>& getJointBehaviorLODs() const = 0;`
- L78 _public prototype_ `virtual ConstArrayView<SingleJointBehavior> getJointBehaviorValues() const = 0;`
- L80 _public function_ `virtual bool getIsNullGenePool() const`
- L84 _public prototype_ `virtual MemoryResource* getMemoryResource() const = 0;`
- L87 _private member_ `static sc::StatusProvider status;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<gs4::GenePoolInterface>`  
_L93-95_
- L94 _public typedef_ `using type = FactoryCreate<gs4::GenePoolInterface>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<gs4::GenePoolInterface>`  
_L98-100_
- L99 _public typedef_ `using type = FactoryDestroy<gs4::GenePoolInterface>;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace gs4`
- L21 _typedef_ `using GenePoolInterface = PImplExtractor<GenePool>::impl_type;` (scope `gs4`)
- L91 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/JointBehaviorPool.h` (Private)


#### class `gs4::JointBehaviorPool`  
`class JointBehaviorPool`  
_L25-47_
- L27 _public prototype_ `JointBehaviorPool(MemoryResource* memRes);`
- L28 _public prototype_ `JointBehaviorPool(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnas, MemoryResource* memRes);`
- L30 _public prototype_ `const VariableWidthMatrix<std::uint16_t>& getInputIndices() const;`
- L31 _public prototype_ `const VariableWidthMatrix<std::uint16_t>& getOutputIndices() const;`
- L32 _public prototype_ `const VariableWidthMatrix<std::uint16_t>& getLODs() const;`
- L33 _public prototype_ `ConstArrayView<SingleJointBehavior> getJointValues() const;`
- L34 _public prototype_ `std::uint16_t getJointGroupCount() const;`
- L37 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L42 _private member_ `MemoryResource* memRes;`
- L43 _private member_ `Vector<SingleJointBehavior> jointValues;`
- L44 _private member_ `VariableWidthMatrix<std::uint16_t> inIndices;`
- L45 _private member_ `VariableWidthMatrix<std::uint16_t> outIndices;`
- L46 _private member_ `VariableWidthMatrix<std::uint16_t> LODs;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/NeutralJointPool.h` (Private)


#### class `gs4::NeutralJointPool`  
`class NeutralJointPool`  
_L101-124_
- L103 _public prototype_ `NeutralJointPool(MemoryResource* memRes);`
- L104 _public prototype_ `NeutralJointPool(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnas, MemoryResource* memRes);`
- L106 _public prototype_ `template<JointAttribute JT> const XYZTiledMatrix<16u>& getDNAData() const;`
- L108 _public prototype_ `std::uint16_t getJointCount() const;`
- L110 _public prototype_ `Vector3 getDNANeutralJointWorldTranslation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const;`
- L111 _public prototype_ `Vector3 getArchetypeNeutralJointWorldTranslation(std::uint16_t jointIndex) const;`
- L112 _public prototype_ `Vector3 getDNANeutralJointWorldRotation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const;`
- L113 _public prototype_ `Vector3 getArchetypeNeutralJointWorldRotation(std::uint16_t jointIndex) const;`
- L116 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L121 _private member_ `XYZTiledMatrix<16u> dnaTranslations;`
- L122 _private member_ `XYZTiledMatrix<16u> dnaRotations;`
- L123 _private member_ `RawNeutralJoints archJoints;`
- L127 _prototype_ `template<> const XYZTiledMatrix<16u>& NeutralJointPool::getDNAData<JointAttribute::Translation>() const;`
- L130 _prototype_ `template<> const XYZTiledMatrix<16u>& NeutralJointPool::getDNAData<JointAttribute::Rotation>() const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace tdm`
- L12 _macro_ `#define TDM_COORD_SYS_SERIALIZER_DEFINED`
- L15 _function_ `template<typename Archive> void load(Archive& archive, tdm::coord_sys& value)` (scope `tdm`)
- L32 _function_ `template<typename Archive> void save(Archive& archive, tdm::coord_sys& value)` (scope `tdm`)
- L46 _macro_ `#define TDM_ROT_SEQ_SERIALIZER_DEFINED`
- L49 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L57 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_seq& value)` (scope `tdm`)
- L65 _macro_ `#define TDM_ROT_SIGN_SERIALIZER_DEFINED`
- L68 _function_ `template<typename Archive> void load(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L85 _function_ `template<typename Archive> void save(Archive& archive, tdm::rot_sign& value)` (scope `tdm`)
- L99 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/NeutralMeshPool.h` (Private)


#### class `gs4::NeutralMeshPool`  
`class NeutralMeshPool`  
_L14-31_
- L16 _public prototype_ `NeutralMeshPool(MemoryResource* memRes);`
- L17 _public prototype_ `NeutralMeshPool(const Reader* deltaArchetype, ConstArrayView<const Reader*> dnaReaders, MemoryResource* memRes);`
- L18 _public prototype_ `ConstArrayView<XYZTiledMatrix<16u>> getData() const;`
- L19 _public prototype_ `Vec3 getDNAVertexPosition(std::uint16_t dnaIndex, std::uint16_t meshIndex, std::uint32_t vertexIndex) const;`
- L20 _public prototype_ `Vec3 getArchetypeVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const;`
- L21 _public prototype_ `std::uint32_t getVertexCount(std::uint16_t meshIndex) const;`
- L24 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L29 _private member_ `Vector<XYZTiledMatrix<16u>> dnas;`
- L30 _private member_ `Vector<RawVector3Vector> arch;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/NullGenePoolImpl.h` (Private)


#### class `gs4::NullGenePoolImpl`  
`class NullGenePoolImpl : public GenePoolInterface`  
_L12-159_
- inherits: `GenePoolInterface`
- L15 _public function_ `NullGenePoolImpl(MemoryResource* memRes_) : memRes`
- L23 _public prototype_ `~NullGenePoolImpl();`
- L25 _public function_ `std::uint16_t getDNACount() const override`
- L29 _public function_ `StringView getDNAName(std::uint16_t) const override`
- L33 _public function_ `dna::Gender getDNAGender(std::uint16_t) const override`
- L37 _public function_ `std::uint16_t getDNAAge(std::uint16_t) const override`
- L41 _public function_ `std::uint16_t getMeshCount() const override`
- L45 _public function_ `std::uint32_t getVertexCount(std::uint16_t) const override`
- L49 _public function_ `std::uint32_t getVertexPositionCount(std::uint16_t) const override`
- L53 _public function_ `Vector3 getDNAVertexPosition(std::uint16_t, std::uint16_t, std::uint32_t) const override`
- L57 _public function_ `Vector3 getArchetypeVertexPosition(std::uint16_t, std::uint32_t) const override`
- L61 _public function_ `std::uint16_t getBlendShapeTargetCount(std::uint16_t) const override`
- L65 _public function_ `std::uint32_t getSkinWeightsCount(std::uint16_t) const override`
- L69 _public function_ `std::uint16_t getMaximumInfluencesPerVertex(std::uint16_t) const override`
- L73 _public function_ `std::uint16_t getNeutralJointCount() const override`
- L77 _public function_ `std::uint16_t getJointCount() const override`
- L81 _public function_ `StringView getJointName(std::uint16_t) const override`
- L85 _public function_ `std::uint16_t getJointGroupCount() const override`
- L89 _public function_ `Vector3 getDNANeutralJointWorldTranslation(std::uint16_t, std::uint16_t) const override`
- L93 _public function_ `Vector3 getArchetypeNeutralJointWorldTranslation(std::uint16_t) const override`
- L97 _public function_ `Vector3 getDNANeutralJointWorldRotation(std::uint16_t, std::uint16_t) const override`
- L101 _public function_ `Vector3 getArchetypeNeutralJointWorldRotation(std::uint16_t) const override`
- L105 _public function_ `ConstArrayView<XYZTiledMatrix<16u>> getNeutralMeshes() const override`
- L109 _public function_ `const BlendShapeDeltas<4u>& getBlendShapeTargetDeltas() const override`
- L113 _public function_ `ConstArrayView<VariableWidthMatrix<std::uint32_t>> getBlendShapeTargetVertexIndices() const override`
- L117 _public function_ `const VariableWidthMatrix<TiledMatrix2D<16u>>& getSkinWeightValues() const override`
- L121 _public function_ `ConstArrayView<VariableWidthMatrix<std::uint16_t>> getSkinWeightJointIndices() const override`
- L125 _public function_ `const XYZTiledMatrix<16u>& getNeutralJoints(JointAttribute) const override`
- L129 _public function_ `const VariableWidthMatrix<std::uint16_t>& getJointBehaviorInputIndices() const override`
- L133 _public function_ `const VariableWidthMatrix<std::uint16_t>& getJointBehaviorOutputIndices() const override`
- L137 _public function_ `const VariableWidthMatrix<std::uint16_t>& getJointBehaviorLODs() const override`
- L141 _public function_ `ConstArrayView<SingleJointBehavior> getJointBehaviorValues() const override`
- L145 _public function_ `bool getIsNullGenePool() const override`
- L149 _public function_ `MemoryResource* getMemoryResource() const override`
- L154 _private member_ `MemoryResource* memRes;`
- L155 _private member_ `XYZTiledMatrix<16u> emptyXYZTiledMatrix;`
- L156 _private member_ `VariableWidthMatrix<std::uint16_t> emptyVariableWidth16iMatrix;`
- L157 _private member_ `VariableWidthMatrix<TiledMatrix2D<16u>> emptyVariableTiledMatrix2DMatrix;`
- L158 _private member_ `BlendShapeDeltas<4u> blendShapeDeltas;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/OutputIndexTargetOffsets.h` (Private)


#### class `gs4::OutputIndexTargetOffsets`  
`class OutputIndexTargetOffsets`  
_L24-34_
- L27 _public prototype_ `explicit OutputIndexTargetOffsets(std::uint16_t jointCount, MemoryResource* memRes);`
- L28 _public prototype_ `void mapJointGroup(ConstArrayView<std::uint16_t> poolOutputIndices, ConstArrayView<std::uint16_t> archOutputIndices);`
- L29 _public prototype_ `const Matrix2D<std::uint8_t>& get() const;`
- L33 _private member_ `Matrix2D<std::uint8_t> offsets;` — [jnt][outPos]=offset

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/RawNeutralJoints.h` (Private)


#### struct `gs4::RawNeutralJoints`  
`struct RawNeutralJoints`  
_L12-44_
- L13 _public function_ `RawNeutralJoints(MemoryResource* memRes) : translations`
- L18 _public function_ `RawNeutralJoints(const Reader* dna, MemoryResource* memRes) : translations`
- L35 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L39 _public member_ `RawVector3Vector translations;`
- L40 _public member_ `RawVector3Vector rotations;`
- L41 _public member_ `dna::CoordinateSystem coordinateSystem;`
- L42 _public member_ `dna::RotationSequence rotationSequence;`
- L43 _public member_ `dna::RotationSign rotationSigns;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace gs4`
- L28 _function_ `auto toRadians = [](float& r)` (scope `gs4::RawNeutralJoints::RawNeutralJoints`)
- L46 _prototype_ `void toWorldSpace(std::function<std::uint16_t(std::uint16_t)> getJointParentIndex, RawNeutralJoints& neutralJoints);` (scope `gs4`)
- L47 _prototype_ `void toLocalSpace(std::function<std::uint16_t(std::uint16_t)> getJointParentIndex, RawNeutralJoints& neutralJoints);` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/SingleJointBehavior.h` (Private)


#### struct `gs4::SingleJointBehavior`  
`struct SingleJointBehavior`  
_L13-51_
- L15 _public typedef_ `using allocator_type = Vector<TiledMatrix2D<16>>::allocator_type;`
- L18 _public prototype_ `explicit SingleJointBehavior(const allocator_type& allocator);`
- L20 _public prototype_ `SingleJointBehavior(const SingleJointBehavior& rhs, const allocator_type& allocator);`
- L21 _public prototype_ `SingleJointBehavior(SingleJointBehavior&& rhs, const allocator_type& allocator);`
- L23 _public prototype_ `SingleJointBehavior(const SingleJointBehavior&) = default;`
- L24 _public prototype_ `SingleJointBehavior& operator=(const SingleJointBehavior&) = default;`
- L26 _public prototype_ `SingleJointBehavior(SingleJointBehavior&&) = default;`
- L27 _public prototype_ `SingleJointBehavior& operator=(SingleJointBehavior&&) = default;`
- L29 _public prototype_ `void setValues(std::uint16_t inputCount, std::uint8_t outPos, ConstArrayView<float> deltaArchValues, ConstArrayView<ConstArrayView<float>> dnaValues);`
- L34 _public prototype_ `ConstArrayView<TiledMatrix2D<16>> getValues() const;`
- L35 _public prototype_ `ConstArrayView<std::uint8_t> getOutputOffsets() const;`
- L36 _public prototype_ `std::uint8_t getTranslationCount() const;`
- L39 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L44 _private prototype_ `void setOutputPositionValues(std::uint8_t outPos, std::uint16_t dnaIdx, ConstArrayView<float> valuesToOperate);`
- L48 _private member_ `Vector<TiledMatrix2D<16>> outputIndexBlocks;` — [outPos{[0-9)}][vBlockIndex][dnaIdx][input]=value
- L49 _private member_ `Vector<std::uint8_t> outputOffsets;`
- L50 _private member_ `std::uint8_t translationCount;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/SkinWeightPool.h` (Private)


#### class `gs4::SkinWeightPool`  
`class SkinWeightPool`  
_L13-42_
- L15 _public prototype_ `SkinWeightPool(MemoryResource* memRes);`
- L16 _public prototype_ `SkinWeightPool(ConstArrayView<const Reader*> dnas, MemoryResource* memRes);`
- L17 _public prototype_ `const VariableWidthMatrix<TiledMatrix2D<16u>>& getWeights() const;`
- L18 _public prototype_ `ConstArrayView<VariableWidthMatrix<std::uint16_t>> getJointIndices() const;`
- L19 _public prototype_ `std::uint16_t getMaximumInfluencesPerVertex(std::uint16_t meshIdx) const;`
- L20 _public prototype_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIdx) const;`
- L23 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L28 _private prototype_ `void resizeAndReserve(const Reader* dna);`
- L29 _private prototype_ `void initializeJointIndices(ConstArrayView<const Reader*> dnas, std::uint16_t meshIndex);`
- L30 _private prototype_ `void generateBlocks(ConstArrayView<const Reader*> dnas, std::uint16_t meshIndex);`
- L31 _private prototype_ `void generateBlock(ConstArrayView<const Reader*> dnas, std::uint16_t meshIndex, std::uint32_t blockIdx, std::uint16_t blockSize);`
- L38 _private member_ `Vector<VariableWidthMatrix<std::uint16_t>> jointIndices;` — [mesh][vtxIdx][jntPos]
- L40 _private member_ `VariableWidthMatrix<TiledMatrix2D<16u>> weights;` — [mesh][blockIdx][dnaIdx][jntPos]{0-16}
- L41 _private member_ `Vector<std::uint16_t> maximumInfluencesPerVertexPerMesh;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/stream/FilteredInputArchive.h` (Private)


#### class `gs4::FilteredInputArchive`  
`class FilteredInputArchive final : public terse::ExtendableBinaryInputArchive<FilteredInputArchive, BoundedIOStream, std::uint64_t, std::uint64_t, terse::Endianness::Network>`  
_L16-50_
- inherits: `terse::ExtendableBinaryInputArchive<FilteredInputArchive,BoundedIOStream,std::uint64_t,std::uint64_t,terse::Endianness::Network>`
- L22 _private typedef_ `using BaseArchive = terse::ExtendableBinaryInputArchive<FilteredInputArchive, BoundedIOStream, std::uint64_t, std::uint64_t, terse::Endianness::Network>;`
- L30 _public prototype_ `FilteredInputArchive(BoundedIOStream* stream_, GenePoolMask mask_, MemoryResource* memRes_);`
- L33 _private prototype_ `bool isMasked(GenePoolMask poolType);`
- L34 _private prototype_ `void process(GenePoolImpl::MetaData& dest);`
- L35 _private prototype_ `void process(NeutralMeshPool& dest);`
- L36 _private prototype_ `void process(BlendShapePool& dest);`
- L37 _private prototype_ `void process(NeutralJointPool& dest);`
- L38 _private prototype_ `void process(SkinWeightPool& dest);`
- L39 _private prototype_ `void process(JointBehaviorPool& dest);`
- L42 _private function_ `template<typename... Args> void process(Args&&... args)`
- L47 _private member_ `BoundedIOStream* stream;`
- L48 _private member_ `MemoryResource* memRes;`
- L49 _private member_ `GenePoolMask mask;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/genepool/stream/FilteredOutputArchive.h` (Private)


#### class `gs4::FilteredOutputArchive`  
`class FilteredOutputArchive final : public terse::ExtendableBinaryOutputArchive<FilteredOutputArchive, BoundedIOStream, std::uint64_t, std::uint64_t, terse::Endianness::Network>`  
_L16-51_
- inherits: `terse::ExtendableBinaryOutputArchive<FilteredOutputArchive,BoundedIOStream,std::uint64_t,std::uint64_t,terse::Endianness::Network>`
- L22 _private typedef_ `using BaseArchive = terse::ExtendableBinaryOutputArchive<FilteredOutputArchive, BoundedIOStream, std::uint64_t, std::uint64_t, terse::Endianness::Network>;`
- L30 _public prototype_ `FilteredOutputArchive(BoundedIOStream* stream_, GenePoolMask mask_, MemoryResource* memRes_);`
- L33 _private prototype_ `void process(GenePoolImpl::MetaData& source);`
- L34 _private prototype_ `void process(NeutralMeshPool& source);`
- L35 _private prototype_ `void process(BlendShapePool& source);`
- L36 _private prototype_ `void process(NeutralJointPool& source);`
- L37 _private prototype_ `void process(SkinWeightPool& source);`
- L38 _private prototype_ `void process(JointBehaviorPool& source);`
- L40 _private prototype_ `bool isMasked(GenePoolMask poolType);`
- L43 _private function_ `template<typename... Args> void process(Args&&... args)`
- L48 _private member_ `BoundedIOStream* stream;`
- L49 _private member_ `MemoryResource* memRes;`
- L50 _private member_ `GenePoolMask mask;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/rawgenes/BlendShapeRawGenes.h` (Private)


#### class `gs4::BlendShapeRawGenes`  
`class BlendShapeRawGenes`  
_L13-25_
- L15 _public prototype_ `explicit BlendShapeRawGenes(MemoryResource* memRes);`
- L17 _public prototype_ `void set(const Reader* dna);`
- L18 _public prototype_ `void accustomize(ConstArrayView<VariableWidthMatrix<std::uint32_t>> blendShapeTargetVertexIndices);`
- L20 _public prototype_ `const VariableWidthMatrix<RawBlendShapeTarget>& getBlendShapeTargets() const;`
- L23 _private member_ `MemoryResource* memRes;`
- L24 _private member_ `VariableWidthMatrix<RawBlendShapeTarget> blendShapeTargets;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/rawgenes/JointBehaviorRawGenes.h` (Private)


#### class `gs4::JointBehaviorRawGenes`  
`class JointBehaviorRawGenes`  
_L17-34_
- L19 _public prototype_ `explicit JointBehaviorRawGenes(MemoryResource* memRes);`
- L21 _public prototype_ `void set(const Reader* dna);`
- L22 _public prototype_ `void accustomize(const VariableWidthMatrix<std::uint16_t>& outputIndicesOther, const VariableWidthMatrix<std::uint16_t>& lodsOther);`
- L24 _public prototype_ `void accustomizeJointGroup(ConstArrayView<std::uint16_t> outputIndicesOther, ConstArrayView<std::uint16_t> lodsOther, std::uint16_t jointGroupIndex);`
- L28 _public prototype_ `ConstArrayView<RawJointGroup> getJointGroups() const;`
- L31 _private member_ `MemoryResource* memRes;`
- L32 _private member_ `Vector<RawJointGroup> jointGroups;`
- L33 _private member_ `std::uint16_t jointCount;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/rawgenes/JointGroupOutputIndicesMerger.h` (Private)


#### struct `gs4::JointGroupOutputIndicesMerger`  
`struct JointGroupOutputIndicesMerger`  
_L13-61_
- L15 _public function_ `JointGroupOutputIndicesMerger(ConstArrayView<std::uint16_t> jointIndices_, MemoryResource* memRes_) : memRes`
- L22 _public function_ `void add(const RawJointGroup& jointGroup)`
- L26 _public function_ `void add(ConstArrayView<std::uint16_t> outputIndices_, ConstArrayView<std::uint16_t> lods_)`
- L31 _public function_ `void reserve(std::uint16_t size)`
- L37 _public function_ `template<typename TOutputIndicesOuputIter, typename ULODReverseOutputIter> TOutputIndicesOuputIter merge(TOutputIndicesOuputIter outputIndicesIter, ULODReverseOutputIter lodsOnePastLast)`
- L57 _private member_ `MemoryResource* memRes;`
- L58 _private member_ `ConstArrayView<std::uint16_t> jointIndices;`
- L59 _private member_ `Vector<ConstArrayView<std::uint16_t>> outputIndices;`
- L60 _private member_ `Vector<ConstArrayView<std::uint16_t>> lods;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/rawgenes/RawGenes.h` (Private)


#### class `gs4::RawGenes`  
`class RawGenes`  
_L20-47_
- L22 _public prototype_ `explicit RawGenes(MemoryResource* memRes);`
- L24 _public prototype_ `void set(const Reader* dna);`
- L26 _public prototype_ `std::uint16_t getMeshCount() const;`
- L27 _public prototype_ `std::uint16_t getJointCount() const;`
- L28 _public prototype_ `std::uint32_t getVertexCount(std::uint16_t meshIndex) const;`
- L29 _public prototype_ `std::uint32_t getSkinWeightsCount(std::uint16_t meshIndex) const;`
- L31 _public prototype_ `ConstArrayView<RawVector3Vector> getNeutralMeshes() const;`
- L32 _public prototype_ `const VariableWidthMatrix<RawBlendShapeTarget>& getBlendShapeTargets() const;`
- L33 _public prototype_ `ConstArrayView<RawJointGroup> getJointGroups() const;`
- L34 _public prototype_ `const RawVector3Vector& getNeutralJoints(JointAttribute jointAttribute) const;`
- L35 _public prototype_ `ConstArrayView<Vector<RawVertexSkinWeights>> getSkinWeights() const;`
- L37 _public prototype_ `void accustomize(const GenePoolInterface* genePool);`
- L40 _private member_ `MemoryResource* memRes;`
- L41 _private member_ `Vector<RawVector3Vector> neutralMeshes;`
- L42 _private member_ `Vector<std::uint32_t> vertexCountPerMesh;`
- L43 _private member_ `BlendShapeRawGenes blendShapes;`
- L44 _private member_ `JointBehaviorRawGenes jointBehavior;`
- L45 _private member_ `RawNeutralJoints neutralJoints;`
- L46 _private member_ `Matrix<RawVertexSkinWeights> skinWeights;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/splicedata/rawgenes/RawGenesUtils.h` (Private)


#### Free symbols / members of external scopes

- L25 _namespace_ `namespace gs4`
- L27 _function_ `inline ConstArrayView<float> getJointValuesForOutputIndex(ConstArrayView<std::uint16_t> outputIndices, ConstArrayView<float> values, std::size_t inputCount, std::uint16_t outputIndex)` (scope `gs4`)
- L41 _function_ `inline ConstArrayView<float> getJointValuesForOutputIndex(const RawJointGroup& jointGroup, std::uint16_t outputIndex)` (scope `gs4`)
- L48 _function_ `inline ConstArrayView<float> getJointValuesForOutputIndex(const Reader* dna, std::uint16_t jointGroupIndex, std::uint16_t outputIndex)` (scope `gs4`)
- L57 _function_ `inline ConstArrayView<std::uint16_t> getOutputIndicesIntroducedByLOD(ConstArrayView<std::uint16_t> outputIndices, ConstArrayView<std::uint16_t> lods, std::uint16_t lodIndex)` (scope `gs4`)
- L67 _function_ `inline void copyJointGroupValues(const RawJointGroup& srcJointGroup, RawJointGroup& destJointGroup)` (scope `gs4`)
- L77 _function_ `inline Vector<RawVector3Vector> getNeutralMeshesFromDNA(const Reader* dna, MemoryResource* memRes)` (scope `gs4`)
- L91 _function_ `template<JointAttribute JT> inline RawVector3Vector getNeutralJointsFromDNA(const Reader* dna, MemoryResource* memRes)` (scope `gs4`)
- L96 _function_ `inline Matrix<RawVertexSkinWeights> getSkinWeightFromDNA(const Reader* dna, MemoryResource* memRes)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/system/Detect.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define GS_BUILD_WITH_SSE 1`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/system/SIMD.h` (Private)


#### struct `gs4::GetTF128`  
`template<CalculationType CT> struct GetTF128`  
_L21-21_
- L25 _public typedef_ `using type = trimd::scalar::F128;`
- L30 _public typedef_ `using type = trimd::F128;`

#### struct `gs4::GetTF128`  
`template<> struct GetTF128<CalculationType::Scalar>`  
_L24-26_
- L25 _public typedef_ `using type = trimd::scalar::F128;`
- L30 _public typedef_ `using type = trimd::F128;`

#### struct `gs4::GetTF128`  
`template<> struct GetTF128<CalculationType::SSE>`  
_L29-31_
- L25 _public typedef_ `using type = trimd::scalar::F128;`
- L30 _public typedef_ `using type = trimd::F128;`

#### struct `gs4::GetTF128`  
`template<> struct GetTF128<CalculationType::AVX>`  
_L34-36_
- L25 _public typedef_ `using type = trimd::scalar::F128;`
- L30 _public typedef_ `using type = trimd::F128;`

#### struct `gs4::GetTF256`  
`template<CalculationType CT> struct GetTF256`  
_L39-39_
- L43 _public typedef_ `using type = trimd::scalar::F256;`
- L48 _public typedef_ `using type = trimd::F256;`

#### struct `gs4::GetTF256`  
`template<> struct GetTF256<CalculationType::Scalar>`  
_L42-44_
- L43 _public typedef_ `using type = trimd::scalar::F256;`
- L48 _public typedef_ `using type = trimd::F256;`

#### struct `gs4::GetTF256`  
`template<> struct GetTF256<CalculationType::AVX>`  
_L47-49_
- L43 _public typedef_ `using type = trimd::scalar::F256;`
- L48 _public typedef_ `using type = trimd::F256;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define TRIMD_ENABLE_AVX`
- L13 _macro_ `#define TRIMD_ENABLE_SSE`
- L18 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/Alignment.h` (Private)


#### enum `gs4::Alignment`  
`enum class Alignment`  
_L7-10_
- L8 _public enumerator_ `Aligned`
- L9 _public enumerator_ `Unaligned`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/Block.h` (Private)


#### struct `gs4::__anon78c351dc0111::CompareFloat`  
`struct CompareFloat`  
_L22-27_
- L24 _public function_ `bool operator()(float a, float b) const noexcept`

#### struct `gs4::XYZBlock`  
`template<std::uint16_t BlockSize> struct XYZBlock`  
_L32-63_
- L33 _public member_ `float Xs[BlockSize];`
- L34 _public member_ `float Ys[BlockSize];`
- L35 _public member_ `float Zs[BlockSize];`
- L37 _public function_ `static constexpr std::uint16_t size()`
- L41 _public function_ `static constexpr std::uint16_t totalSize()`
- L45 _public function_ `bool operator==(const XYZBlock<BlockSize> other) const`
- L52 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `gs4::VBlock`  
`template<std::uint16_t BlockSize> struct VBlock`  
_L66-93_
- L67 _public member_ `float v[BlockSize];`
- L69 _public function_ `float& operator[](std::size_t index)`
- L74 _public function_ `const float& operator[](std::size_t index) const`
- L79 _public function_ `static constexpr std::uint16_t size()`
- L83 _public function_ `bool operator==(const VBlock<BlockSize>& other) const`
- L88 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace gs4`
- L20 _namespace_ `namespace (anonymous)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/BlockStorage.h` (Private)


#### struct `gs4::BlockSplicer`  
`template<CalculationType CT> struct BlockSplicer`  
_L45-102_
- L47 _public function_ `static inline void splice(Matrix2DView<const XYZBlock<16u>> dnas, Matrix2DView<const VBlock<16u>> weights, ConstArrayView<std::uint16_t> dnaIndices, Vec3VectorView result, float scale)`

#### struct `gs4::BlockSplicer`  
`template<> struct BlockSplicer<CalculationType::SSE>`  
_L105-182_
- L47 _public function_ `static inline void splice(Matrix2DView<const XYZBlock<16u>> dnas, Matrix2DView<const VBlock<16u>> weights, ConstArrayView<std::uint16_t> dnaIndices, Vec3VectorView result, float scale)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace gs4`
- L18 _typedef_ `template<std::uint16_t BlockSize> using XYZTiledMatrix = AlignedMatrix2D<XYZBlock<BlockSize>>;` (scope `gs4`)
- L21 _typedef_ `template<std::uint16_t BlockSize> using TiledMatrix2D = Matrix2D<VBlock<BlockSize>, PolyAllocator<VBlock<BlockSize>, static_cast<std::uint16_t>(BlockSize * 4)>>;` (scope `gs4`)
- L23 _function_ `inline std::size_t getPaddedCount(std::size_t count, std::uint16_t blockSize)` (scope `gs4`)
- L28 _function_ `inline std::size_t getBlockCount(std::size_t count)` (scope `gs4`)
- L33 _function_ `inline RawVector3Vector constructWithPadding(const RawVector3Vector& elements, MemoryResource* memRes, std::uint16_t blockSize = XYZTiledMatrix<16u>::value_type::size())` (scope `gs4`)
- L52 _typedef_ `using TF256 = typename GetTF256<CT>::type;` (scope `gs4::BlockSplicer::splice`)
- L112 _typedef_ `using TF128 = typename GetTF128<CalculationType::SSE>::type;` (scope `gs4::BlockSplicer::splice`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/ExpectedValue.h` (Private)


#### struct `gs4::ExpectedValue`  
`template<typename T> struct ExpectedValue`  
_L8-33_
- L9 _public member_ `T expected;`
- L10 _public member_ `T got;`
- L12 _public function_ `explicit ExpectedValue(const T& value) : expected`
- L18 _public function_ `template<class Archive> void load(Archive& archive)`
- L24 _public function_ `template<class Archive> void save(Archive& archive)`
- L30 _public function_ `bool matches() const`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/Matrix.h` (Private)


#### class `gs4::Matrix2D`  
`template<class T, typename Allocator = PolyAllocator<T>> class Matrix2D`  
_L32-133_
- L35 _public typedef_ `using value_type = T;` — *INDENT-OFF*
- L36 _public typedef_ `using const_value_type = const T;`
- L37 _public typedef_ `using index_type = std::size_t;`
- L38 _public typedef_ `using pointer = value_type*;`
- L39 _public typedef_ `using const_pointer = const value_type*;`
- L40 _public typedef_ `using reference = value_type&;`
- L41 _public typedef_ `using const_reference = const value_type&;`
- L42 _public typedef_ `using slice_type = ArrayView<value_type>;`
- L43 _public typedef_ `using const_slice_type = ConstArrayView<value_type>;`
- L44 _public typedef_ `using allocator_type = Allocator;`
- L48 _public function_ `explicit Matrix2D(const allocator_type& alloc) : rows`
- L54 _public function_ `Matrix2D(index_type rows_, index_type columns_, const allocator_type& alloc) : rows`
- L61 _public function_ `Matrix2D(index_type rows_, index_type columns_, const_reference initial, const allocator_type& alloc) : rows`
- L67 _public function_ `Matrix2D(const Matrix2D& rhs, const allocator_type& alloc) : rows`
- L73 _public prototype_ `~Matrix2D() = default;`
- L75 _public prototype_ `Matrix2D(const Matrix2D&) = default;`
- L76 _public prototype_ `Matrix2D& operator=(const Matrix2D&) = default;`
- L78 _public prototype_ `Matrix2D(Matrix2D&&) = default;`
- L79 _public prototype_ `Matrix2D& operator=(Matrix2D&&) = default;`
- L81 _public function_ `slice_type operator[](index_type row)`
- L86 _public function_ `const_slice_type operator[](index_type row) const`
- L91 _public function_ `index_type rowCount() const noexcept`
- L95 _public function_ `index_type columnCount() const noexcept`
- L99 _public function_ `std::size_t size() const noexcept`
- L103 _public function_ `pointer data() noexcept`
- L107 _public function_ `const_pointer data() const noexcept`
- L111 _public function_ `allocator_type getAllocator() const noexcept`
- L116 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L121 _private function_ `pointer rowAt(index_type index)`
- L125 _private function_ `const_pointer rowAt(index_type index) const`
- L130 _private member_ `index_type rows;`
- L131 _private member_ `index_type columns;`
- L132 _private member_ `terse::DynArray<value_type, Allocator> values;`

#### class `gs4::Matrix2DView`  
`template<class T> class Matrix2DView`  
_L139-230_
- L142 _public typedef_ `using value_type = T;`
- L143 _public typedef_ `using const_value_type = const T;`
- L144 _public typedef_ `using index_type = std::size_t;`
- L145 _public typedef_ `using pointer = value_type*;`
- L146 _public typedef_ `using const_pointer = const value_type*;`
- L147 _public typedef_ `using reference = value_type&;`
- L148 _public typedef_ `using const_reference = const value_type&;`
- L149 _public typedef_ `using slice_type = ArrayView<value_type>;`
- L150 _public typedef_ `using const_slice_type = ConstArrayView<value_type>;`
- L151 _public typedef_ `using size_type = std::size_t;`
- L154 _public function_ `Matrix2DView(pointer ptr_, index_type rows_, index_type columns_) : ptr`
- L161 _public function_ `template<typename U, typename Allocator> Matrix2DView(const Matrix2D<U, Allocator>& matrix) : ptr`
- L168 _public function_ `template<typename U, typename Allocator> Matrix2DView(Matrix2D<U, Allocator>& matrix) : ptr`
- L174 _public prototype_ `~Matrix2DView() = default;`
- L176 _public function_ `Matrix2DView(const Matrix2DView& other) : ptr`
- L182 _public prototype_ `Matrix2DView& operator=(const Matrix2DView&) = default;`
- L184 _public prototype_ `Matrix2DView(Matrix2DView&&) = default;`
- L185 _public prototype_ `Matrix2DView& operator=(Matrix2DView&&) = default;`
- L187 _public function_ `index_type rowCount() const noexcept`
- L191 _public function_ `index_type columnCount() const noexcept`
- L195 _public function_ `std::size_t size() const noexcept`
- L199 _public function_ `slice_type operator[](index_type row)`
- L204 _public function_ `const_slice_type operator[](index_type row) const`
- L209 _public function_ `pointer data() noexcept`
- L213 _public function_ `const_pointer data() const noexcept`
- L218 _private function_ `pointer rowAt(index_type index)`
- L222 _private function_ `const_pointer rowAt(index_type index) const`
- L227 _private member_ `pointer ptr;`
- L228 _private member_ `index_type rows;`
- L229 _private member_ `index_type columns;`

#### class `gs4::Matrix3D`  
`template<class T, typename Allocator = PolyAllocator<T>> class Matrix3D`  
_L233-341_
- L236 _public typedef_ `using value_type = T;`
- L237 _public typedef_ `using const_value_type = const T;`
- L238 _public typedef_ `using index_type = std::size_t;`
- L239 _public typedef_ `using pointer = value_type*;`
- L240 _public typedef_ `using const_pointer = const value_type*;`
- L241 _public typedef_ `using reference = value_type&;`
- L242 _public typedef_ `using const_reference = const value_type&;`
- L243 _public typedef_ `using slice_type = Matrix2DView<value_type>;`
- L244 _public typedef_ `using const_slice_type = Matrix2DView<const value_type>;`
- L245 _public typedef_ `using size_type = std::size_t;`
- L246 _public typedef_ `using memory_resource_pointer = MemoryResource*;`
- L247 _public typedef_ `using allocator_type = Allocator;`
- L250 _public function_ `explicit Matrix3D(const allocator_type& allocator_) : Matrix3D`
- L254 _public function_ `Matrix3D(index_type zCount, index_type yCount, index_type xCount, allocator_type allocator_) : values`
- L261 _public function_ `Matrix3D(const Matrix3D& rhs, const allocator_type& allocator_) : values`
- L268 _public function_ `Matrix3D(const Matrix3D& rhs) : values`
- L275 _public function_ `Matrix3D& operator=(const Matrix3D& rhs)`
- L281 _public prototype_ `Matrix3D(Matrix3D&& rhs) = default;`
- L282 _public prototype_ `Matrix3D& operator=(Matrix3D&& rhs) = default;`
- L284 _public function_ `index_type zCount() const noexcept`
- L288 _public function_ `index_type yCount() const noexcept`
- L292 _public function_ `index_type xCount() const noexcept`
- L296 _public function_ `std::size_t size() const noexcept`
- L300 _public function_ `slice_type operator[](index_type zi)`
- L305 _public function_ `const_slice_type operator[](index_type zi) const`
- L310 _public function_ `pointer data() noexcept`
- L314 _public function_ `const_pointer data() const noexcept`
- L318 _public function_ `allocator_type getAllocator() const noexcept`
- L323 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L328 _private function_ `pointer xAt(index_type zi)`
- L332 _private function_ `const_pointer xAt(index_type zi) const`
- L337 _private member_ `terse::DynArray<value_type, allocator_type> values;`
- L338 _private member_ `index_type z;`
- L339 _private member_ `index_type y;`
- L340 _private member_ `index_type x;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace gs4`
- L136 _typedef_ `template<typename T> using AlignedMatrix2D = Matrix2D<T, AlignedAllocator<T>>;` (scope `gs4`)
- L344 _typedef_ `template<typename T> using AlignedMatrix3D = Matrix3D<T, AlignedAllocator<T>>;` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/PImplExtractor.h` (Private)


#### struct `gs4::PImplExtractor`  
`template<class T> struct PImplExtractor`  
_L17-60_
- L19 _public typedef_ `using wrapper_type = T;`
- L20 _public typedef_ `using const_wrapper_type = const T;`
- L21 _public typedef_ `using wrapper_reference = wrapper_type&;`
- L22 _public typedef_ `using const_wrapper_reference = const wrapper_type&;`
- L23 _public typedef_ `using wrapper_ptr = wrapper_type*;`
- L24 _public typedef_ `using const_wrapper_ptr = const wrapper_type*;`
- L27 _public typedef_ `template<class TDestroyer> using wrapper_smart_ptr = ScopedPtr<wrapper_type, TDestroyer>;`
- L29 _public typedef_ `template<class TDestroyer> using const_wrapper_smart_ptr = const ScopedPtr<wrapper_type, TDestroyer>;`
- L31 _public typedef_ `using impl_type = typename T::Impl;`
- L32 _public typedef_ `using impl_ptr = impl_type*;`
- L33 _public typedef_ `using const_impl_ptr = const impl_type*;`
- L35 _public function_ `static const_impl_ptr get(const_wrapper_reference holder)`
- L39 _public function_ `static impl_ptr get(wrapper_reference holder)`
- L43 _public function_ `static const_impl_ptr get(const_wrapper_ptr holder)`
- L47 _public function_ `static impl_ptr get(wrapper_ptr holder)`
- L52 _public function_ `template<class TDestroyer> static const_impl_ptr get(const_wrapper_smart_ptr<TDestroyer>& holder)`
- L57 _public function_ `template<class TDestroyer> static impl_ptr get(wrapper_smart_ptr<TDestroyer>& holder)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace gs4`
- L12 _function_ `template<class T, typename... Args> ScopedPtr<T, FactoryDestroy<T>> makePImpl(Args&&... args)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/Signature.h` (Private)


#### struct `gs4::Signature`  
`template<std::size_t Size> struct Signature`  
_L12-30_
- L13 _public typedef_ `using SignatureValueType = std::array<char, Size>;`
- L15 _public member_ `ExpectedValue<SignatureValueType> value;`
- L17 _public function_ `explicit Signature(SignatureValueType bytes) : value`
- L22 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L27 _public function_ `bool matches() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/VariableWidthMatrix.h` (Private)


#### class `gs4::VariableWidthMatrix`  
`template<class T, typename Allocator = PolyAllocator<T>> class VariableWidthMatrix`  
_L26-229_
- L29 _public typedef_ `using value_type = T;` — *INDENT-OFF*
- L30 _public typedef_ `using const_value_type = const T;`
- L31 _public typedef_ `using index_type = std::size_t;`
- L32 _public typedef_ `using pointer = value_type*;`
- L33 _public typedef_ `using const_pointer = const value_type*;`
- L34 _public typedef_ `using reference = value_type&;`
- L35 _public typedef_ `using const_reference = const value_type&;`
- L36 _public typedef_ `using slice_type = ArrayView<value_type>;`
- L37 _public typedef_ `using const_slice_type = ConstArrayView<value_type>;`
- L38 _public typedef_ `using allocator_type = Allocator;`
- L81 _public function_ `friend bool operator==(const Iterator& a, const Iterator& b)`
- L85 _public function_ `friend bool operator!=(const Iterator& a, const Iterator& b)`
- L95 _public function_ `explicit VariableWidthMatrix(const allocator_type& allocator) : rowIndices`
- L100 _public function_ `VariableWidthMatrix(const VariableWidthMatrix& rhs, const allocator_type& alloc) : rowIndices`
- L105 _public function_ `VariableWidthMatrix(VariableWidthMatrix&& rhs, const allocator_type& alloc) : rowIndices`
- L110 _public prototype_ `VariableWidthMatrix(const VariableWidthMatrix&) = default;`
- L111 _public prototype_ `VariableWidthMatrix& operator=(const VariableWidthMatrix&) = default;`
- L113 _public prototype_ `VariableWidthMatrix(VariableWidthMatrix&&) = default;`
- L114 _public prototype_ `VariableWidthMatrix& operator=(VariableWidthMatrix&&) = default;`
- L116 _public prototype_ `~VariableWidthMatrix() = default;`
- L118 _public function_ `slice_type operator[](index_type row)`
- L123 _public function_ `const_slice_type operator[](index_type row) const`
- L128 _public function_ `index_type rowCount() const noexcept`
- L132 _public function_ `index_type columnCount(index_type row) const`
- L137 _public function_ `std::size_t size() const noexcept`
- L141 _public function_ `pointer data() noexcept`
- L145 _public function_ `const_pointer data() const noexcept`
- L149 _public function_ `allocator_type getAllocator() const noexcept`
- L153 _public function_ `void appendRow(const_slice_type row)`
- L158 _public function_ `void appendRow(index_type columnCount)`
- L163 _public function_ `void appendRow(index_type columnCount, const_reference value)`
- L168 _public function_ `void append(index_type row, const_reference element)`
- L172 _public function_ `void insert(index_type row, index_type column, const_reference element)`
- L181 _public function_ `void reserve(index_type rowCount, index_type valueCount)`
- L186 _public function_ `void shrinkToFit()`
- L191 _public function_ `void clear()`
- L196 _public function_ `Iterator begin()`
- L200 _public function_ `const Iterator begin() const`
- L204 _public function_ `Iterator end()`
- L208 _public function_ `const Iterator end() const`
- L213 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L218 _private function_ `pointer rowAt(index_type index)`
- L222 _private function_ `const_pointer rowAt(index_type index) const`
- L227 _private member_ `Vector<index_type> rowIndices;`
- L228 _private member_ `Vector<value_type, Allocator> values;`

#### struct `gs4::VariableWidthMatrix::Iterator`  
`struct Iterator`  
_L41-92_
- L42 _public typedef_ `using iterator_category = std::bidirectional_iterator_tag;`
- L43 _public typedef_ `using difference_type = std::ptrdiff_t;`
- L44 _public typedef_ `using value_type = T;`
- L45 _public typedef_ `using pointer = value_type*;`
- L46 _public typedef_ `using reference = value_type&;`
- L48 _public function_ `Iterator(const_pointer valuesPtr_, Vector<index_type>::const_iterator indicesIter_) : indicesIter`
- L53 _public function_ `ConstArrayView<T> operator*() const`
- L59 _public function_ `Iterator& operator++()`
- L64 _public function_ `Iterator operator++(int)`
- L70 _public function_ `Iterator& operator--()`
- L75 _public function_ `Iterator operator--(int)`
- L90 _private member_ `Vector<index_type>::const_iterator indicesIter;`
- L91 _private member_ `const_pointer valuesPtr;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace gs4`
- L232 _typedef_ `template<typename T> using AlignedVariableWidthMatrix = VariableWidthMatrix<T, AlignedAllocator<T>>;` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/Vec3.h` (Private)


#### struct `gs4::ConstVec3VectorView`  
`struct ConstVec3VectorView`  
_L12-16_
- L13 _public member_ `ConstArrayView<float> Xs;`
- L14 _public member_ `ConstArrayView<float> Ys;`
- L15 _public member_ `ConstArrayView<float> Zs;`

#### struct `gs4::Vec3VectorView`  
`struct Vec3VectorView`  
_L18-28_
- L19 _public member_ `ArrayView<float> Xs;`
- L20 _public member_ `ArrayView<float> Ys;`
- L21 _public member_ `ArrayView<float> Zs;`
- L23 _public function_ `Vec3VectorView(RawVector3Vector& vec) : Xs`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace gs4`
- L10 _typedef_ `using Vec3 = Vector3;` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/types/Version.h` (Private)


#### struct `gs4::ExpectedVersion`  
`struct ExpectedVersion`  
_L11-28_
- L12 _public member_ `ExpectedValue<std::uint16_t> generation;`
- L13 _public member_ `ExpectedValue<std::uint16_t> version;`
- L15 _public function_ `ExpectedVersion(std::uint16_t generation_, std::uint16_t version_) : generation`
- L21 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L25 _public function_ `bool matches() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/utils/Algorithm.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace gs4`
- L22 _function_ `template<typename T, typename OutIter, typename std::enable_if<std::is_unsigned<T>::value, bool>::type = true> OutIter mergeIndices(ConstArrayView<ConstArrayView<T>> multipleIndices, T maximumIndex, OutIter outputIter, MemoryResource* memRes)` (scope `gs4`)
- L28 _function_ `const auto mark = [&contains](T index)` (scope `gs4::mergeIndices`)
- L43 _function_ `template<typename T, typename OutIter, typename std::enable_if<std::is_unsigned<T>::value, bool>::type = true> OutIter mergeIndices(ConstArrayView<T> indices, ConstArrayView<T> otherIndices, T maximumIndex, OutIter outputIter, MemoryResource* memRes)` (scope `gs4`)
- L53 _function_ `template<typename T> static void inverseMapping(ConstArrayView<T> indices, ArrayView<T> inverseIndices)` (scope `gs4`)
- L60 _function_ `inline fmat4 extractTranslationMatrix(const fmat4& transformationMatrix)` (scope `gs4`)
- L68 _function_ `inline fmat4 extractRotationMatrix(const fmat4& transformationMatrix)` (scope `gs4`)
- L76 _function_ `inline fvec3 extractTranslationVector(const fmat4& transformationMatrix)` (scope `gs4`)
- L80 _function_ `inline frad3 extractRotationVector(const fmat4& transformationMatrix)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/genesplicer/utils/IterTools.h` (Private)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace gs4`
- L23 _function_ `template<class TIterator, typename TDistance> TIterator advanced(TIterator source, TDistance distance)` (scope `gs4`)
- L29 _function_ `template<class TIterator, class Predicate> typename TIterator::difference_type advanceWhile(TIterator& it, const TIterator& end, Predicate pred)` (scope `gs4`)
- L38 _function_ `template<class TInputIterator, class TOutputIterator> inline void safeCopy(const TInputIterator& start, const TInputIterator& end, TOutputIterator destination, std::size_t size)` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/BaseImpl.h` (Private)


#### class `raf::BaseImpl`  
`class BaseImpl`  
_L10-33_
- L12 _protected function_ `explicit BaseImpl(MemoryResource* memRes_) : memRes`
- L17 _protected prototype_ `~BaseImpl() = default;`
- L19 _protected prototype_ `BaseImpl(const BaseImpl&) = delete;`
- L20 _protected prototype_ `BaseImpl& operator=(const BaseImpl&) = delete;`
- L22 _protected prototype_ `BaseImpl(BaseImpl&& rhs) = delete;`
- L23 _protected prototype_ `BaseImpl& operator=(BaseImpl&&) = delete;`
- L26 _public function_ `MemoryResource* getMemoryResource()`
- L31 _protected member_ `MemoryResource* memRes;`
- L32 _protected member_ `RegionAffiliation regionAffiliation;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/ReaderImpl.h` (Private)


#### class `raf::ReaderImpl`  
`template<class TReaderBase> class ReaderImpl : public TReaderBase, public virtual BaseImpl`  
_L22-43_
- inherits: `TReaderBase,BaseImpl`
- L24 _public typedef_ `using ReaderInterface = TReaderBase;`
- L27 _public prototype_ `explicit ReaderImpl(MemoryResource* memRes_);`
- L30 _public prototype_ `std::uint16_t getJointCount() const override;` — JointRegionAffiliationReader methods
- L31 _public prototype_ `ConstArrayView<std::uint16_t> getJointRegionIndices(std::uint16_t jointIndex) const override;`
- L32 _public prototype_ `ConstArrayView<float> getJointRegionAffiliation(std::uint16_t jointIndex) const override;`
- L35 _public prototype_ `std::uint16_t getMeshCount() const override;` — VertexRegionAffiliationReader methods
- L36 _public prototype_ `std::uint32_t getVertexCount(std::uint16_t meshIndex) const override;`
- L37 _public prototype_ `ConstArrayView<std::uint16_t> getVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L38 _public prototype_ `ConstArrayView<float> getVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex) const override;`
- L41 _public prototype_ `std::uint16_t getRegionCount() const override;` — RegionAffiliationReader methods
- L42 _public prototype_ `StringView getRegionName(std::uint16_t regionIndex) const override;`
- L50 _function_ `template<class TReaderBase> inline ReaderImpl<TReaderBase>::ReaderImpl(MemoryResource* memRes_) : BaseImpl`
- L63 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getJointCount() const`
- L68 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getJointRegionIndices(std::uint16_t jointIndex) const`
- L76 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getJointRegionAffiliation(std::uint16_t jointIndex) const`
- L84 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getMeshCount() const`
- L89 _function_ `template<class TReaderBase> inline std::uint32_t ReaderImpl<TReaderBase>::getVertexCount(std::uint16_t meshIndex) const`
- L97 _function_ `template<class TReaderBase> inline ConstArrayView<std::uint16_t> ReaderImpl<TReaderBase>::getVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const`
- L106 _function_ `template<class TReaderBase> inline ConstArrayView<float> ReaderImpl<TReaderBase>::getVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex) const`
- L115 _function_ `template<class TReaderBase> inline std::uint16_t ReaderImpl<TReaderBase>::getRegionCount() const`
- L120 _function_ `template<class TReaderBase> inline StringView ReaderImpl<TReaderBase>::getRegionName(std::uint16_t regionIndex) const`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/RegionAffiliation.h` (Private)


#### struct `raf::RawRegionAffiliation`  
`struct RawRegionAffiliation`  
_L20-48_
- L21 _public member_ `Vector<std::uint16_t> regionIndices;`
- L22 _public member_ `Vector<float> values;`
- L24 _public function_ `explicit RawRegionAffiliation(MemoryResource* memRes) : regionIndices`
- L30 _public function_ `template<typename TUInt16Container, typename TFloatContainer> RawRegionAffiliation(const TUInt16Container& regionIndices_, const TFloatContainer& values_, MemoryResource* memRes) : regionIndices`
- L39 _public function_ `template<class Archive> void serialize(Archive& archive)`

#### struct `raf::RegionAffiliation`  
`struct RegionAffiliation`  
_L50-101_
- L51 _public member_ `Signature<3> signature{{'R', 'A', 'F'}};`
- L52 _public member_ `Version version{1, 1};`
- L53 _public member_ `Matrix<RawRegionAffiliation> vertexRegions;`
- L54 _public member_ `Vector<RawRegionAffiliation> jointRegions;`
- L55 _public member_ `Vector<String<char>> regionNames;`
- L56 _public member_ `Signature<3> eof{{'F', 'A', 'R'}};`
- L58 _public function_ `explicit RegionAffiliation(MemoryResource* memRes) : vertexRegions`
- L65 _public function_ `template<class Archive> void load(Archive& archive)`
- L86 _public function_ `template<class Archive> void save(Archive& archive)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/RegionAffiliationBinaryStreamReaderImpl.h` (Private)


#### class `raf::RegionAffiliationBinaryStreamReaderImpl`  
`class RegionAffiliationBinaryStreamReaderImpl : public ReaderImpl<RegionAffiliationBinaryStreamReader>`  
_L11-20_
- inherits: `ReaderImpl<RegionAffiliationBinaryStreamReader>`
- L13 _public prototype_ `RegionAffiliationBinaryStreamReaderImpl(BoundedIOStream* stream_, MemoryResource* memRes_);`
- L15 _public prototype_ `void read() override;`
- L18 _private member_ `static sc::StatusProvider status;`
- L19 _private member_ `BoundedIOStream* stream;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/RegionAffiliationBinaryStreamWriterImpl.h` (Private)


#### class `raf::RegionAffiliationBinaryStreamWriterImpl`  
`class RegionAffiliationBinaryStreamWriterImpl : public WriterImpl<RegionAffiliationBinaryStreamWriter>`  
_L11-21_
- inherits: `WriterImpl<RegionAffiliationBinaryStreamWriter>`
- L13 _public prototype_ `RegionAffiliationBinaryStreamWriterImpl(BoundedIOStream* stream_, MemoryResource* memRes_);`
- L15 _public prototype_ `void write() override;`
- L18 _private member_ `static sc::StatusProvider status;`
- L20 _private member_ `BoundedIOStream* stream;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/RegionAffiliationJSONStreamReaderImpl.h` (Private)


#### class `raf::RegionAffiliationJSONStreamReaderImpl`  
`class RegionAffiliationJSONStreamReaderImpl : public ReaderImpl<RegionAffiliationJSONStreamReader>`  
_L11-20_
- inherits: `ReaderImpl<RegionAffiliationJSONStreamReader>`
- L13 _public prototype_ `RegionAffiliationJSONStreamReaderImpl(BoundedIOStream* stream_, MemoryResource* memRes_);`
- L15 _public prototype_ `void read() override;`
- L18 _private member_ `static sc::StatusProvider status;`
- L19 _private member_ `BoundedIOStream* stream;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/RegionAffiliationJSONStreamWriterImpl.h` (Private)


#### class `raf::RegionAffiliationJSONStreamWriterImpl`  
`class RegionAffiliationJSONStreamWriterImpl : public WriterImpl<RegionAffiliationJSONStreamWriter>`  
_L11-22_
- inherits: `WriterImpl<RegionAffiliationJSONStreamWriter>`
- L13 _public prototype_ `RegionAffiliationJSONStreamWriterImpl(BoundedIOStream* stream_, std::uint32_t indentWidth_, MemoryResource* memRes_);`
- L15 _public prototype_ `void write() override;`
- L18 _private member_ `static sc::StatusProvider status;`
- L20 _private member_ `BoundedIOStream* stream;`
- L21 _private member_ `std::uint32_t indentWidth;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/TypeDefs.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/WriterImpl.h` (Private)


#### class `raf::WriterImpl`  
`template<class TWriterBase> class WriterImpl : public TWriterBase, public virtual BaseImpl`  
_L53-83_
- inherits: `TWriterBase,BaseImpl`
- L55 _public typedef_ `using WriterInterface = TWriterBase;`
- L58 _public prototype_ `explicit WriterImpl(MemoryResource* memRes_);`
- L61 _public prototype_ `void setJointRegionIndices(std::uint16_t jointIndex, const std::uint16_t* regionIndices, std::uint16_t count) override;` — JointRegionAffiliationWriter methods
- L62 _public prototype_ `void setJointRegionAffiliation(std::uint16_t jointIndex, const float* regionAffiliationValues, std::uint16_t count) override;`
- L63 _public prototype_ `void clearJointAffiliations() override;`
- L64 _public prototype_ `void deleteJointAffiliation(std::uint16_t jointIndex) override;`
- L67 _public prototype_ `void setVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex, const std::uint16_t* regionIndices, std::uint16_t count) override;` — VertexRegionAffiliationWriter methods
- L71 _public prototype_ `void setVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex, const float* regionAffiliationValues, std::uint16_t count) override;`
- L75 _public prototype_ `void clearVertexAffiliations() override;`
- L76 _public prototype_ `void clearVertexAffiliations(std::uint16_t meshIndex) override;`
- L77 _public prototype_ `void deleteVertexAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex) override;`
- L80 _public prototype_ `void clearRegionNames() override;` — RegionAffiliationWriter methods
- L81 _public prototype_ `void setRegionName(std::uint16_t regionIndex, const char* regionName) override;`
- L82 _public prototype_ `void setFrom(const RegionAffiliationReader* source) override;`
- L90 _function_ `template<class TWriterBase> WriterImpl<TWriterBase>::WriterImpl(MemoryResource* memRes_) : BaseImpl`
- L103 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointRegionIndices(std::uint16_t jointIndex, const std::uint16_t* regionIndices, std::uint16_t count)`
- L111 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setJointRegionAffiliation(std::uint16_t jointIndex, const float* regionAffiliationValues, std::uint16_t count)`
- L119 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearJointAffiliations()`
- L124 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteJointAffiliation(std::uint16_t jointIndex)`
- L132 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex, const std::uint16_t* regionIndices, std::uint16_t count)`
- L142 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex, const float* regionAffiliationValues, std::uint16_t count)`
- L152 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearVertexAffiliations()`
- L157 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearVertexAffiliations(std::uint16_t meshIndex)`
- L164 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::deleteVertexAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex)`
- L174 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::clearRegionNames()`
- L179 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setRegionName(std::uint16_t regionIndex, const char* regionName)`
- L184 _function_ `template<class TWriterBase> inline void WriterImpl<TWriterBase>::setFrom(const RegionAffiliationReader* source)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace raf`
- L26 _function_ `ensureHasSize(TContainer& target, std::size_t size)` (scope `raf`)
- L42 _function_ `template<class TContainer, typename U> typename std::enable_if<std::is_integral<U>::value, typename TContainer::value_type&>::type getAt(TContainer& target, U index)` (scope `raf`)
- L48 _function_ `template<class TContainer, typename TSize, typename TValue> typename std::enable_if<std::is_integral<TSize>::value>::type setAt(TContainer& target, TSize index, const TValue& value)` (scope `raf`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Private/raf/types/SerializationTypes.h` (Private)


#### struct `raf::ExpectedValue`  
`template<typename T> struct ExpectedValue`  
_L18-40_
- L19 _public member_ `T expected;`
- L20 _public member_ `T got;`
- L22 _public function_ `explicit ExpectedValue(const T& value) : expected`
- L28 _public function_ `template<class Archive> void load(Archive& archive)`
- L33 _public function_ `template<class Archive> void save(Archive& archive)`
- L37 _public function_ `bool matches() const`

#### struct `raf::Signature`  
`template<std::size_t Size> struct Signature`  
_L43-60_
- L44 _public typedef_ `using SignatureValueType = std::array<char, Size>;`
- L46 _public member_ `ExpectedValue<SignatureValueType> value;`
- L48 _public function_ `explicit Signature(SignatureValueType bytes) : value`
- L53 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L57 _public function_ `bool matches() const`

#### struct `raf::Version`  
`struct Version`  
_L62-87_
- L63 _public member_ `std::uint16_t generation;`
- L64 _public member_ `std::uint16_t version;`
- L66 _public function_ `Version(std::uint16_t generation_, std::uint16_t version_) : generation`
- L72 _public function_ `template<class Archive> void serialize(Archive& archive)`
- L79 _public function_ `bool supported() const`
- L84 _public function_ `bool matches(std::uint16_t generation_, std::uint16_t version_) const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/GeneSplicerLib.h` (Public)


#### class `FGeneSplicerLib`  
`class FGeneSplicerLib : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicerLib, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeneSplicerLib, Log, All);`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/CalculationType.h` (Public)


#### enum `gs4::CalculationType`  
`enum class CalculationType`  
_L7-11_
- L8 _public enumerator_ `Scalar` — scalar implementation
- L9 _public enumerator_ `SSE` — vectorized implementation
- L10 _public enumerator_ `AVX` — vectorized implementation

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define GSAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define GSAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define GSAPI` — Build or use static library

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/GeneSplicer.h` (Public)


#### class `gs4::GeneSplicer`  
`class GeneSplicer final`  
_L16-84_
- desc: @brief A stateless facility that wraps the splicing algorithms.
- L23 _public prototype_ `GSAPI explicit GeneSplicer(CalculationType calculationType = CalculationType::SSE, MemoryResource* memRes = nullptr);` — @brief Constructor @param calculationType Determines which algorithm implementation is used for splicing
- L25 _public prototype_ `GSAPI ~GeneSplicer();`
- L27 _public prototype_ `GeneSplicer(const GeneSplicer&) = delete;`
- L28 _public prototype_ `GeneSplicer& operator=(const GeneSplicer&) = delete;`
- L30 _public prototype_ `GSAPI GeneSplicer(GeneSplicer&& rhs);`
- L31 _public prototype_ `GSAPI GeneSplicer& operator=(GeneSplicer&& rhs);`
- L39 _public prototype_ `GSAPI void splice(const SpliceData* spliceData, GeneSplicerDNAReader* output);` — @brief Run all the individual splicers. @param spliceData Contains all the necessary input data that is used during splicing. @param output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L47 _public prototype_ `GSAPI void spliceNeutralMeshes(const SpliceData* spliceData, GeneSplicerDNAReader* output);` — @brief Run only the neutral mesh splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L55 _public prototype_ `GSAPI void spliceBlendShapes(const SpliceData* spliceData, GeneSplicerDNAReader* output);` — @brief Run only the blend shape splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L63 _public prototype_ `GSAPI void spliceNeutralJoints(const SpliceData* spliceData, GeneSplicerDNAReader* output);` — @brief Run only the neutral joint splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L71 _public prototype_ `GSAPI void spliceJointBehavior(const SpliceData* spliceData, GeneSplicerDNAReader* output);` — @brief Run only the joint behavior splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L79 _public prototype_ `GSAPI void spliceSkinWeights(const SpliceData* spliceData, GeneSplicerDNAReader* output);` — @brief Run only the skin weight splicer. @param spliceData Contains all the necessary input data that is used during splicing. @param output Output parameter - the DNA Reader that will contain the spliced DNA data.
- L83 _private member_ `ScopedPtr<Impl, FactoryDestroy<Impl>> pImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/GeneSplicerDNAReader.h` (Public)


#### class `gs4::GeneSplicerDNAReader`  
`class GSAPI GeneSplicerDNAReader : public Reader, public virtual Writer`  
_L13-41_
- inherits: `Reader,Writer`
- desc: @brief A special purpose DNA Reader type which serves as the output parameter of GeneSplicer.
- L30 _public prototype_ `static GeneSplicerDNAReader* create(const dna::Reader* reader, MemoryResource* memRes = nullptr);` — @brief Factory method for the creation of GeneSplicerDNAReader @param reader The original DNA reader from which GeneSplicerDNAReader is initialized. @note During initialization, all the static data (data that is not generated during splicing) is copied from the given source reader. @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L37 _public prototype_ `static void destroy(GeneSplicerDNAReader* instance);` — @brief Method for freeing a GeneSplicerDNAReader instance. @param instance Instance of GeneSplicerDNAReader to be freed. @see create
- L40 _protected prototype_ `virtual ~GeneSplicerDNAReader();`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<gs4::GeneSplicerDNAReader>`  
_L48-50_
- L49 _public typedef_ `using type = FactoryCreate<gs4::GeneSplicerDNAReader>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<gs4::GeneSplicerDNAReader>`  
_L53-55_
- L54 _public typedef_ `using type = FactoryDestroy<gs4::GeneSplicerDNAReader>;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace gs4`
- L45 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/splicedata/GenePool.h` (Public)


#### class `gs4::GenePool`  
`class GenePool final`  
_L17-214_
- desc: @brief Encapsulates the input data that GeneSplicer uses during splicing.
- L19 _public member_ `GSAPI static const StatusCode DNAMismatch;`
- L20 _public member_ `GSAPI static const StatusCode DNAsEmpty;`
- L42 _public prototype_ `GSAPI GenePool(const dna::Reader* deltaArchetype, const dna::Reader** dnas, std::uint16_t dnaCount, GenePoolMask mask = GenePoolMask::All, MemoryResource* memRes = nullptr);` — @brief Creates optimized structure for splicing that contains copy of all required data from DNAs that will be used in splicing. @param dnas The DNA Readers that will participate in splicing. @param deltaArchetype The deltaArchetype DNA reader. @note All required data from pointers is copied to internal data structures, does not take over ownership. @param dnaCount The number of DNA Readers, i.e. the length of the DNAs array. @param mask Used for loading only certain sections of GenePool. @note The number of DNAs set through this API, excluding deltaArchetype, directly impacts the number of splice weights that must be set through PoolSpliceParams::setSpliceWeights @see PoolSpliceParams::setSpliceWeights
- L62 _public prototype_ `GSAPI GenePool(BoundedIOStream* stream, GenePoolMask mask = GenePoolMask::All, MemoryResource* memRes = nullptr);` — @brief Creates optimized structure for splicing that contains copy of all required data from DNAs that will be used in splicing. @note All required data from stream is copied to internal data structures, does not take over ownership. @param stream Source stream from which data is going to be read. @param mask Used for loading only certain sections of GenePool. @note The number of DNAs in stream, excluding deltaArchetype, directly impacts the number of splice weights that must be set through PoolSpliceParams::setSpliceWeights @see PoolSpliceParams::setSpliceWeights
- L71 _public prototype_ `GSAPI void dump(BoundedIOStream* stream, GenePoolMask mask = GenePoolMask::All);` — @brief Writes out GenePool to a stream. @param stream Destination stream to which data is going to be written. @param mask Used for dumping only certain sections of GenePool.
- L73 _public prototype_ `GSAPI ~GenePool();`
- L75 _public prototype_ `GenePool(const GenePool&) = delete;`
- L76 _public prototype_ `GenePool& operator=(const GenePool&) = delete;`
- L78 _public prototype_ `GSAPI GenePool(GenePool&& rhs);`
- L79 _public prototype_ `GSAPI GenePool& operator=(GenePool&& rhs);`
- L81 _public prototype_ `GSAPI std::uint16_t getDNACount() const;`
- L90 _public prototype_ `GSAPI StringView getDNAName(std::uint16_t dnaIndex) const;` — @param dnaIndex A position in the zero-indexed array of DNA names. @warning The index must be less than the value returned by getDNACount. @return View over the  name string. @see getDNACount
- L98 _public prototype_ `GSAPI dna::Gender getDNAGender(std::uint16_t dnaIndex) const;` — @param dnaIndex A position in the zero-indexed array of DNA genders. @warning The index must be less than the value returned by getDNACount. @see getDNACount
- L106 _public prototype_ `GSAPI std::uint16_t getDNAAge(std::uint16_t dnaIndex) const;` — @param dnaIndex A position in the zero-indexed array of DNA ages. @warning The index must be less than the value returned by getDNACount. @see getDNACount
- L108 _public prototype_ `GSAPI std::uint16_t getMeshCount() const;`
- L117 _public prototype_ `GSAPI std::uint32_t getVertexPositionCount(std::uint16_t meshIndex) const;` — @brief Number of vertex positions in the entire mesh. @param meshIndex A position in the zero-indexed array of meshes. @warning The index must be less than the value returned by getMeshCount. @see getMeshCount
- L136 _public prototype_ `GSAPI Vector3 getDNAVertexPosition(std::uint16_t dnaIndex, std::uint16_t meshIndex, std::uint32_t vertexIndex) const;` — @brief The vertex position of DNA. @param dnaIndex A position in the zero-indexed array of DNAs. @warning The index must be less than the value returned by getDNACount. @see getDNACount @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @see getMeshCount @param vertexIndex The index of the vertex position in the zero-indexed array of vertex positions. @warning vertexIndex must be less than the value returned by getVertexPositionCount. @see getVertexPositionCount
- L150 _public prototype_ `GSAPI Vector3 getArchetypeVertexPosition(std::uint16_t meshIndex, std::uint32_t vertexIndex) const;` — @brief The vertex position of archetype. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @see getMeshCount @param vertexIndex The index of the vertex position in the zero-indexed array of vertex positions. @warning vertexIndex must be less than the value returned by getVertexPositionCount. @see getVertexPositionCount
- L152 _public prototype_ `GSAPI std::uint16_t getJointCount() const;`
- L161 _public prototype_ `GSAPI StringView getJointName(std::uint16_t jointIndex) const;` — @brief Name of the requested joint. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @see getJointCount
- L175 _public prototype_ `GSAPI Vector3 getDNANeutralJointWorldTranslation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const;` — @brief Translation of DNA's joint in world space. @param dnaIndex A position in the zero-indexed array of DNAs. @warning The index must be less than the value returned by getDNACount. @see getDNACount @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @see getJointCount
- L183 _public prototype_ `GSAPI Vector3 getArchetypeNeutralJointWorldTranslation(std::uint16_t jointIndex) const;` — @brief Translation of archetype's joint in world space. @param jointIndex A name's position in the zero-indexed array of joint names. @warning The index must be less than the value returned by getJointCount.
- L197 _public prototype_ `GSAPI Vector3 getDNANeutralJointWorldRotation(std::uint16_t dnaIndex, std::uint16_t jointIndex) const;` — @brief Rotation of DNA's joint in world space. @param dnaIndex A position in the zero-indexed array of DNAs. @warning The index must be less than the value returned by getDNACount. @see getDNACount @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @see getJointCount
- L206 _public prototype_ `GSAPI Vector3 getArchetypeNeutralJointWorldRotation(std::uint16_t jointIndex) const;` — @brief Rotation of archetype's joint in world space. @param jointIndex A joint's position in the zero-indexed array of joints. @warning The index must be less than the value returned by getJointCount. @see getJointCount
- L213 _private member_ `ScopedPtr<Impl, FactoryDestroy<Impl>> pImpl;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/splicedata/GenePoolMask.h` (Public)


#### enum `gs4::GenePoolMask`  
`enum class GenePoolMask : std::uint32_t`  
_L11-18_
- L12 _public enumerator_ `NeutralMeshes = 1`
- L13 _public enumerator_ `BlendShapes = 2`
- L14 _public enumerator_ `SkinWeights = 4`
- L15 _public enumerator_ `NeutralJoints = 8`
- L16 _public enumerator_ `JointBehavior = 16`
- L17 _public enumerator_ `All = 31`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace gs4`
- L20 _prototype_ `GSAPI GenePoolMask operator~(GenePoolMask a);` (scope `gs4`)
- L21 _prototype_ `GSAPI GenePoolMask operator|(GenePoolMask a, GenePoolMask b);` (scope `gs4`)
- L22 _prototype_ `GSAPI GenePoolMask operator&(GenePoolMask a, GenePoolMask b);` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/splicedata/PoolSpliceParams.h` (Public)


#### class `gs4::PoolSpliceParams`  
`class GSAPI PoolSpliceParams`  
_L15-93_
- desc: @brief Encapsulates the input data that GeneSplicer uses during splicing.
- L17 _public member_ `static const StatusCode GenePoolIncompatible;`
- L18 _public member_ `static const StatusCode WeightsInvalid;`
- L21 _public prototype_ `virtual ~PoolSpliceParams();`
- L34 _public prototype_ `virtual void setDNAFilter(const std::uint16_t* dnaIndices, std::uint16_t count) = 0;` — @brief Specify which subset of DNAs will participate in splicing. @note This may significantly reduce the amount of computation that needs to be performed. @param dnaIndices The indices of DNAs that will participate in splicing, while DNAs not present in this list will be skipped. @param count The number of DNA indices, i.e. the length of the dnaIndices array. @note The dna indices will be copied into PoolSpliceParams.
- L47 _public prototype_ `virtual void setMeshFilter(const std::uint16_t* meshIndices, std::uint16_t count) = 0;` — @brief Specify which subset of meshes will participate in splicing. @note This may significantly reduce the amount of computation that needs to be performed. @param meshIndices The indices of meshes that will participate in splicing, while Meshes not present in this list will be skipped. @param count The number of Mesh indices, i.e. the length of the meshIndices array. @note The mesh indices will be copied into PoolSpliceParams.
- L51 _public prototype_ `virtual void clearFilters() = 0;` — @brief Clears dna and mesh filters previously set by setDNAFilter and SetMeshFilter
- L83 _public prototype_ `virtual void setSpliceWeights(std::uint16_t dnaStartIndex, const float* weights, std::uint32_t count) = 0;` — @brief Set weights for each region of DNAs starting from DNA at dnaStartIndex index spanning across successive DNAs until reaching the end of specified weights array, i.e. weights + count. @note All values will be copied. @param dnaStartIndex Index of the first dna in succession for which the weights apply. @param weights C style array of floats, containing weights of DNAs per all regions. @param count The number of weights, i.e. the length of the weights array. @warning The weight count must be equal to the region count multiplied by the number of DNAs whose weights are being set by the call. @details Initially when PoolSpliceParams is created weights are filled with zeros. For the sake of example lets say we have 2 Regions and 4 DNAs. Which translates to: Region-0  Region-1 DNA-0    0.0       0.0 DNA-1    0.0       0.0 DNA-2    0.0       0.0 DNA-3    0.0       0.0 after calling setSpiceWeights with dnaStartIndex = 1, weights=[0.1f, 0.9f, 0.4f, 05f], count = 4 Weights will chagne for DNAs with indices 1 and 2: Region-0  Region-1 DNA-0    0.0       0.0 DNA-1    0.1       0.9 DNA-2    0.4       0.5 DNA-3    0.0       0.0
- L89 _public prototype_ `virtual void setScale(float scale) = 0;` — @brief Sets scaling factor for splicing. @param scale Scale to be applied while splicing.
- L91 _public prototype_ `virtual std::uint16_t getDNACount() const = 0;`
- L92 _public prototype_ `virtual std::uint16_t getRegionCount() const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/splicedata/SpliceData.h` (Public)


#### class `gs4::SpliceData`  
`class SpliceData final`  
_L17-74_
- desc: @brief Encapsulates the input data that GeneSplicer uses during splicing.
- L19 _public prototype_ `GSAPI explicit SpliceData(MemoryResource* memRes = nullptr);`
- L20 _public prototype_ `GSAPI ~SpliceData();`
- L22 _public prototype_ `SpliceData(const SpliceData&) = delete;`
- L23 _public prototype_ `SpliceData& operator=(const SpliceData&) = delete;`
- L25 _public prototype_ `GSAPI SpliceData(SpliceData&& rhs);`
- L26 _public prototype_ `GSAPI SpliceData& operator=(SpliceData&& rhs);`
- L40 _public prototype_ `GSAPI void registerGenePool(const char* name, const RegionAffiliationReader* raf, const GenePool* genePool);` — @brief Registers gene pool for splicing. @param name Null terminated string used as key to later access gene pool parameters @param raf Region affiliations associated with given pool. @note Region affiliations will be copied into SpliceData and will be held as long as gene pool is not destroyed. @param genePool Gene pool that holds dnas to be spliced. @note Gene pool will not be copied, and the user is responsible to maintain it's lifecycle.
- L46 _public prototype_ `GSAPI void unregisterGenePool(const char* name);` — @brief Unregisters gene pool previously registered @param name Null terminated string, desired name of gene pool to unregister.
- L54 _public prototype_ `GSAPI PoolSpliceParams* getPoolParams(const char* name);` — @brief Access previously registered gene pools to set splicing parameters. @param name Null terminated string, desired name of gene pool to access. @note If name is not registered return value will be nullptr
- L66 _public prototype_ `GSAPI void setBaseArchetype(const dna::Reader* baseArchetype);` — @brief Set the base Archetype DNA Reader. @note The baseArchetype DNA reader provides the neutral values that are used as base onto which deltas will be added. @param baseArchetype The baseArchetype DNA reader. @note All data reqired from pointer is copied to internal data structures, does not take over ownership.
- L73 _private member_ `ScopedPtr<Impl, FactoryDestroy<Impl>> pImpl;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/types/Aliases.h` (Public)


#### Free symbols / members of external scopes

- L23 _namespace_ `namespace gs4`
- L53 _typedef_ `template<typename T> using ArrayView = dna::ArrayView<T>;` (scope `gs4`)
- L56 _typedef_ `template<typename T> using ConstArrayView = dna::ConstArrayView<T>;` (scope `gs4`)

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define GS_MAJOR_VERSION 10`
- L6 _macro_ `#define GS_MINOR_VERSION 1`
- L7 _macro_ `#define GS_PATCH_VERSION 3`
- L8 _macro_ `#define GS_VERSION_STRING "10.1.3"`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/genesplicer/version/VersionInfo.h` (Public)


#### struct `gs4::VersionInfo`  
`struct GSAPI VersionInfo`  
_L10-15_
- L11 _public prototype_ `static int getMajorVersion();`
- L12 _public prototype_ `static int getMinorVersion();`
- L13 _public prototype_ `static int getPatchVersion();`
- L14 _public prototype_ `static StringView getVersionString();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace gs4`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/Defs.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L7 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L9 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L10 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L12 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L13 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L31 _macro_ `#define RAFAPI DLL_EXPORT` — Build shared library
- L34 _macro_ `#define RAFAPI DLL_IMPORT` — Use shared library
- L37 _macro_ `#define RAFAPI` — Build or use static library

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/JointRegionAffiliationReader.h` (Public)


#### class `raf::JointRegionAffiliationReader`  
`class RAFAPI JointRegionAffiliationReader`  
_L15-38_
- desc: @brief Read-only accessors for joint region affiliation.
- L18 _protected prototype_ `virtual ~JointRegionAffiliationReader();`
- L21 _public prototype_ `virtual std::uint16_t getJointCount() const = 0;`
- L29 _public prototype_ `virtual ConstArrayView<std::uint16_t> getJointRegionIndices(std::uint16_t jointIndex) const = 0;` — @brief List of region indices for specified joint. @param jointIndex A joint's position in the zero-indexed array of joints. @warning jointIndex must be less than the value returned by getJointCount.
- L37 _public prototype_ `virtual ConstArrayView<float> getJointRegionAffiliation(std::uint16_t jointIndex) const = 0;` — @brief List of joint-region affiliations (0.0f-1.0f) for specified joint. @param vertexIndex A joint's position in the zero-indexed array of joints. @warning jointIndex must be less than the value returned by getJointCount.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/JointRegionAffiliationWriter.h` (Public)


#### class `raf::JointRegionAffiliationWriter`  
`class RAFAPI JointRegionAffiliationWriter`  
_L14-51_
- desc: @brief Write-only accessors for joint region affiliation.
- L16 _protected prototype_ `virtual ~JointRegionAffiliationWriter();`
- L28 _public prototype_ `virtual void setJointRegionIndices(std::uint16_t jointIndex, const std::uint16_t* regionIndices, std::uint16_t count) = 0;` — @brief List of region indices. @param jointIndex A joint's position in the zero-indexed array of meshes. @param regionIndices The source address from which the region indices are to be copied. @param count The number of regions that affiliate with joint specified joint.
- L38 _public prototype_ `virtual void setJointRegionAffiliation(std::uint16_t jointIndex, const float* regionAffiliationValues, std::uint16_t count) = 0;` — @brief List of joint-region affiliations (0.0f-1.0f) for specified joint. @param jointIndex A joint's position in the zero-indexed array of joints. @param regionAffiliationValues The source address from which the region affiliations are to be copied. @param count The number of regions that affiliate with joint specified joint.
- L44 _public prototype_ `virtual void clearJointAffiliations() = 0;` — @brief Clears all joint region affiliations and indices .
- L50 _public prototype_ `virtual void deleteJointAffiliation(std::uint16_t jointIndex) = 0;` — @brief Deletes joint region affiliations and indices. @param jointIndex A joint's position in the zero-indexed array of joints.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationBinaryStreamReader.h` (Public)


#### class `raf::RegionAffiliationBinaryStreamReader`  
`class RAFAPI RegionAffiliationBinaryStreamReader : public RegionAffiliationStreamReader`  
_L11-36_
- inherits: `RegionAffiliationStreamReader`
- L13 _protected prototype_ `virtual ~RegionAffiliationBinaryStreamReader();`
- L28 _public prototype_ `static RegionAffiliationBinaryStreamReader* create(BoundedIOStream* stream, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of RegionAffiliationBinaryStreamReader @param stream Stream from which data is going to be read. @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L35 _public prototype_ `static void destroy(RegionAffiliationBinaryStreamReader* instance);` — @brief Method for freeing a RegionAffiliationBinaryStreamReader instance. @param instance Instance of RegionAffiliationBinaryStreamReader to be freed. @see create

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<raf::RegionAffiliationBinaryStreamReader>`  
_L43-45_
- L44 _public typedef_ `using type = FactoryCreate<raf::RegionAffiliationBinaryStreamReader>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<raf::RegionAffiliationBinaryStreamReader>`  
_L48-50_
- L49 _public typedef_ `using type = FactoryDestroy<raf::RegionAffiliationBinaryStreamReader>;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`
- L40 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationBinaryStreamWriter.h` (Public)


#### class `raf::RegionAffiliationBinaryStreamWriter`  
`class RAFAPI RegionAffiliationBinaryStreamWriter : public RegionAffiliationStreamWriter`  
_L11-36_
- inherits: `RegionAffiliationStreamWriter`
- L13 _protected prototype_ `virtual ~RegionAffiliationBinaryStreamWriter();`
- L28 _public prototype_ `static RegionAffiliationBinaryStreamWriter* create(BoundedIOStream* stream, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of RegionAffiliationBinaryStreamWriter @param stream Stream to which data is going to be written. @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L35 _public prototype_ `static void destroy(RegionAffiliationBinaryStreamWriter* instance);` — @brief Method for freeing a RigDefinitionBinaryStreamWriter instance. @param instance Instance of RigDefinitionBinaryStreamWriter to be freed. @see create

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<raf::RegionAffiliationBinaryStreamWriter>`  
_L43-45_
- L44 _public typedef_ `using type = FactoryCreate<raf::RegionAffiliationBinaryStreamWriter>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<raf::RegionAffiliationBinaryStreamWriter>`  
_L48-50_
- L49 _public typedef_ `using type = FactoryDestroy<raf::RegionAffiliationBinaryStreamWriter>;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`
- L40 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationJSONStreamReader.h` (Public)


#### class `raf::RegionAffiliationJSONStreamReader`  
`class RAFAPI RegionAffiliationJSONStreamReader : public RegionAffiliationStreamReader`  
_L11-36_
- inherits: `RegionAffiliationStreamReader`
- L13 _protected prototype_ `virtual ~RegionAffiliationJSONStreamReader();`
- L28 _public prototype_ `static RegionAffiliationJSONStreamReader* create(BoundedIOStream* stream, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of RegionAffiliationJSONStreamReader @param stream Stream from which data is going to be read. @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L35 _public prototype_ `static void destroy(RegionAffiliationJSONStreamReader* instance);` — @brief Method for freeing a RegionAffiliationJSONStreamReader instance. @param instance Instance of RegionAffiliationJSONStreamReader to be freed. @see create

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<raf::RegionAffiliationJSONStreamReader>`  
_L43-45_
- L44 _public typedef_ `using type = FactoryCreate<raf::RegionAffiliationJSONStreamReader>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<raf::RegionAffiliationJSONStreamReader>`  
_L48-50_
- L49 _public typedef_ `using type = FactoryDestroy<raf::RegionAffiliationJSONStreamReader>;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`
- L40 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationJSONStreamWriter.h` (Public)


#### class `raf::RegionAffiliationJSONStreamWriter`  
`class RAFAPI RegionAffiliationJSONStreamWriter : public RegionAffiliationStreamWriter`  
_L11-40_
- inherits: `RegionAffiliationStreamWriter`
- L13 _protected prototype_ `virtual ~RegionAffiliationJSONStreamWriter();`
- L30 _public prototype_ `static RegionAffiliationJSONStreamWriter* create(BoundedIOStream* stream, std::uint32_t indentWidth = 4u, MemoryResource* memRes = nullptr);` — @brief Factory method for creation of RegionAffiliationJSONStreamWriter @param stream Stream to which data is going to be written. @param indentWidth Number of spaces to use for indentation. @param memRes A custom memory resource to be used for allocations. @note If a custom memory resource is not given, a default allocation mechanism will be used. @warning User is responsible for releasing the returned pointer by calling destroy. @see destroy
- L39 _public prototype_ `static void destroy(RegionAffiliationJSONStreamWriter* instance);` — @brief Method for freeing a RegionAffiliationJSONStreamWriter instance. @param instance Instance of RegionAffiliationJSONStreamWriter to be freed. @see create

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<raf::RegionAffiliationJSONStreamWriter>`  
_L47-49_
- L48 _public typedef_ `using type = FactoryCreate<raf::RegionAffiliationJSONStreamWriter>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<raf::RegionAffiliationJSONStreamWriter>`  
_L52-54_
- L53 _public typedef_ `using type = FactoryDestroy<raf::RegionAffiliationJSONStreamWriter>;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`
- L44 _namespace_ `namespace pma`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationReader.h` (Public)


#### class `raf::RegionAffiliationReader`  
`class RAFAPI RegionAffiliationReader : public JointRegionAffiliationReader, public VertexRegionAffiliationReader`  
_L16-23_
- inherits: `JointRegionAffiliationReader,VertexRegionAffiliationReader`
- desc: @brief Read-only accessors for vertex and joint region affiliation.
- L18 _protected prototype_ `virtual ~RegionAffiliationReader();`
- L21 _public prototype_ `virtual std::uint16_t getRegionCount() const = 0;`
- L22 _public prototype_ `virtual StringView getRegionName(std::uint16_t regionIndex) const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationStreamReader.h` (Public)


#### class `raf::RegionAffiliationStreamReader`  
`class RAFAPI RegionAffiliationStreamReader : public RegionAffiliationReader`  
_L11-22_
- inherits: `RegionAffiliationReader`
- L13 _public member_ `static const StatusCode IOError;`
- L14 _public member_ `static const StatusCode SignatureMismatchError;`
- L15 _public member_ `static const StatusCode VersionMismatchError;`
- L18 _protected prototype_ `virtual ~RegionAffiliationStreamReader();`
- L21 _public prototype_ `virtual void read() = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationStreamWriter.h` (Public)


#### class `raf::RegionAffiliationStreamWriter`  
`class RAFAPI RegionAffiliationStreamWriter : public RegionAffiliationWriter`  
_L11-20_
- inherits: `RegionAffiliationWriter`
- L13 _public member_ `static const StatusCode IOError;`
- L16 _protected prototype_ `virtual ~RegionAffiliationStreamWriter();`
- L19 _public prototype_ `virtual void write() = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/RegionAffiliationWriter.h` (Public)


#### class `raf::RegionAffiliationWriter`  
`class RAFAPI RegionAffiliationWriter : public JointRegionAffiliationWriter, public VertexRegionAffiliationWriter`  
_L18-26_
- inherits: `JointRegionAffiliationWriter,VertexRegionAffiliationWriter`
- desc: @brief Write-only accessors for vertex and joint region affiliation.
- L20 _protected prototype_ `virtual ~RegionAffiliationWriter();`
- L23 _public prototype_ `virtual void clearRegionNames() = 0;`
- L24 _public prototype_ `virtual void setRegionName(std::uint16_t regionIndex, const char* regionName) = 0;`
- L25 _public prototype_ `virtual void setFrom(const RegionAffiliationReader* source) = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/VertexRegionAffiliationReader.h` (Public)


#### class `raf::VertexRegionAffiliationReader`  
`class RAFAPI VertexRegionAffiliationReader`  
_L15-54_
- desc: @brief Read-only accessors for vertex and joint region affiliation.
- L17 _protected prototype_ `virtual ~VertexRegionAffiliationReader();`
- L20 _public prototype_ `virtual std::uint16_t getMeshCount() const = 0;`
- L28 _public prototype_ `virtual std::uint32_t getVertexCount(std::uint16_t meshIndex) const = 0;` — @brief Number of vertices in the entire mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount.
- L40 _public prototype_ `virtual raf::ConstArrayView<std::uint16_t> getVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;` — @brief List of region indices for specified vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param vertexIndex A vertex's position in the zero-indexed array of vertices. @warning vertexIndex must be less than the value returned by getVertexCount.
- L53 _public prototype_ `virtual raf::ConstArrayView<float> getVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex) const = 0;` — @brief List of vertex-region affiliations (0.0f-1.0f) for specified vertex. @param meshIndex A mesh's position in the zero-indexed array of meshes. @warning meshIndex must be less than the value returned by getMeshCount. @param vertexIndex A vertex's position in the zero-indexed array of vertices. @warning vertexIndex must be less than the value returned by getVertexCount.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/VertexRegionAffiliationWriter.h` (Public)


#### class `raf::VertexRegionAffiliationWriter`  
`class RAFAPI VertexRegionAffiliationWriter`  
_L14-73_
- desc: @brief Write-only accessors for vertex and joint region affiliation.
- L16 _protected prototype_ `virtual ~VertexRegionAffiliationWriter();`
- L33 _public prototype_ `virtual void setVertexRegionIndices(std::uint16_t meshIndex, std::uint32_t vertexIndex, const std::uint16_t* regionIndices, std::uint16_t count) = 0;` — @brief List of region indices. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param vertexIndex A vertex's position in the zero-indexed array of meshes. @param regionIndices The source address from which the region indices are to be copied. @param count The number of regions that affiliate with vertexIndex. @note The mesh storage will be implicitly resized (if needed) to provide storage for the number of meshes that is inferred from the specified index.
- L51 _public prototype_ `virtual void setVertexRegionAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex, const float* regionAffiliationValues, std::uint16_t count) = 0;` — @brief List of vertex region affiliations. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param vertexIndex A vertex's position in the zero-indexed array of meshes. @param regionAffiliationValues The source address from which the region affiliations are to be copied. @param count The number of regions that affiliate with vertexIndex. @note The mesh storage will be implicitly resized (if needed) to provide storage for the number of meshes that is inferred from the specified index.
- L58 _public prototype_ `virtual void clearVertexAffiliations() = 0;` — @brief Clears all vertex region affiliations and indices.
- L64 _public prototype_ `virtual void clearVertexAffiliations(std::uint16_t meshIndex) = 0;` — @brief Clears all region affiliations and indices of vertices in specified mesh. @param meshIndex A mesh's position in the zero-indexed array of meshes.
- L72 _public prototype_ `virtual void deleteVertexAffiliation(std::uint16_t meshIndex, std::uint32_t vertexIndex) = 0;` — @brief Deletes vertex region affiliations and indices. @param meshIndex A mesh's position in the zero-indexed array of meshes. @param vertexIndex A vertex's position in the zero-indexed array of meshes.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/types/Aliases.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace raf`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerLib/Public/raf/version/Version.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define RAF_MAJOR_VERSION 5`
- L6 _macro_ `#define RAF_MINOR_VERSION 2`
- L7 _macro_ `#define RAF_PATCH_VERSION 5`
- L8 _macro_ `#define RAF_VERSION_STRING "5.2.5"`
