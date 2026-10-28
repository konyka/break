# Runtime / MeshDescription

- module root: `Source/Runtime/MeshDescription`
- headers: 12; symbols: 1192
- symbol kinds: class=30, enum=4, enumerator=15, externvar=11, function=640, member=128, namespace=11, prototype=248, struct=32, typedef=73
- PrivateDependencyModuleNames: DerivedDataCache
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/MeshDescription/Public/AttributeArrayContainer.h` (Public)


#### class `TAttributeArrayContainer`  
`template <typename AttributeType> class TAttributeArrayContainer`  
_L11-366_
- L14 _public prototype_ `TAttributeArrayContainer() = default;`
- L16 _public function_ `explicit TAttributeArrayContainer(const AttributeType& InDefaultValue) : DefaultValue(InDefaultValue)`
- L21 _public function_ `int32 Num() const` — Return size of container
- L24 _public function_ `void Initialize(const int32 ElementCount, const AttributeType& Default)` — Initializes the array to the given size with the default value
- L42 _public function_ `void SetNum(const int32 ElementCount, const AttributeType& Default)` — Sets the number of elements, each element itself being a subarray of items of type AttributeType.
- L98 _public function_ `uint32 GetHash(uint32 Crc = 0) const`
- L108 _public function_ `void Insert(const int32 Index, const AttributeType& Default)` — Expands the array if necessary so that the passed element index is valid. Newly created elements will be assigned the default value.
- L120 _public function_ `void SetToDefault(const int32 Index, const AttributeType& Default)` — Fills the index with the default value
- L131 _public prototype_ `void Remap(const TSparseArray<int32>& IndexRemap, const AttributeType& Default);` — Remaps elements according to the passed remapping table
- L142 _public function_ `TArrayView<AttributeType> Get(int32 Index)` — Gets the array attribute at the given index as a TArrayView
- L152 _public function_ `TArrayView<const AttributeType> Get(int32 Index) const` — Gets the array attribute at the given index as a TArrayView
- L162 _public function_ `int32 GetElementCount(int32 Index) const` — Gets the element count of the array attribute at the given index
- L172 _public function_ `int32 GetReservedElementCount(int32 Index) const` — Gets the reserved element count of the array attribute at the given index
- L182 _public function_ `void Set(int32 Index, TArrayView<const AttributeType> Value)` — Sets the attribute array at the given index to the given TArrayView
- L195 _public function_ `TArrayView<AttributeType> SetElementSize(int32 Index, int32 Size, bool bSetCount, bool bSetDefault = true)` — Sets the given attribute array element to have the given number of subarray elements.
- L252 _public function_ `TArrayView<AttributeType> InsertIntoElement(int32 Index, int32 SubArrayIndex, int32 InsertCount = 1)`
- L286 _public function_ `TArrayView<AttributeType> RemoveFromElement(int32 Index, int32 SubArrayIndex, int32 Count = 1)`
- L299 _public function_ `AttributeType GetDefault() const`
- L303 _private function_ `static int32 GetNumRequiredChunks(const int32 ElementCount)`
- L308 _private function_ `static int32 GetElementsInLastChunk(const int32 ElementCount)`
- L313 _private member_ `static const int32 ChunkBits = 8;`
- L314 _private member_ `static const int32 ChunkSize = (1 << ChunkBits);`
- L315 _private member_ `static const int32 ChunkMask = ChunkSize - 1;`
- L324 _private function_ `friend FArchive& operator <<(FArchive& Ar, FChunk& Chunk)`
- L363 _private member_ `TArray<FChunk> Chunks;`
- L364 _private member_ `int32 NumElements = 0;`
- L365 _private member_ `AttributeType DefaultValue = AttributeType();`
- L371 _function_ `template <typename AttributeType> void TAttributeArrayContainer<AttributeType>::Remap(const TSparseArray<int32>& IndexRemap, const AttributeType& Default)`

#### struct `TAttributeArrayContainer::FChunk`  
`struct FChunk`  
_L317-361_
- L319 _public function_ `FChunk()`
- L348 _public member_ `TArray<AttributeType> Data;` — All the data for each element in the chunk, packed contiguously
- L353 _public member_ `TStaticArray<int32, ChunkSize> StartIndex{InPlace, 0};` — Start, count and allocated count in the Data array for each element in the chunk. Arranged as SoA for cache optimization, since the most frequent operation is adding a fixed amount to all the start indices when a value is inserted.
- L354 _public member_ `TStaticArray<int32, ChunkSize> Count {InPlace, 0};`
- L355 _public member_ `TStaticArray<int32, ChunkSize> MaxCount {InPlace, 0};`
- L360 _public member_ `int32 NumElements = ChunkSize;` — Specify number of valid elements in this chunk. Default to maximum number so that we can add chunks in bulk, and all put the final chunk will already be correctly initialized.

#### class `TArrayAttribute`  
`template <typename AttributeType> class TArrayAttribute`  
_L392-719_
- desc: Proxy object which fields access to an unbounded array attribute container.
- L395 _private typedef_ `template <typename T> friend class TArrayAttribute;`
- L398 _public function_ `explicit TArrayAttribute(ArrayType& InArray, int32 InIndex) : Array(&InArray), Index(InIndex)`
- L407 _public function_ `template <typename T = AttributeType, typename TEnableIf<std::is_same_v<T, const T>, int>::Type = 0> TArrayAttribute(TArrayAttribute<std::remove_cv_t<T>> InValue) : Array(InValue.Array), Index(InValue.Index)` — Construct a TArrayAttribute<const T> from a TArrayAttribute<T>.
- L415 _public function_ `AttributeType* GetData() const` — Helper function for returning a typed pointer to the first array attribute entry.
- L427 _public function_ `bool IsValidIndex(int32 ArrayAttributeIndex) const` — Tests if index is valid, i.e. than or equal to zero, and less than the number of elements in the array attribute. @param Index Index to test. @returns True if index is valid. False otherwise.
- L437 _public function_ `bool IsEmpty() const` — Returns true if the array attribute is empty and contains no elements. @returns True if the array attribute is empty.
- L447 _public function_ `int32 Num() const` — Returns number of elements in the array attribute. @returns Number of elements in array attribute.
- L457 _public function_ `AttributeType& operator[](int32 ArrayAttributeIndex) const` — Array bracket operator. Returns reference to array attribute element at given index. @returns Reference to indexed element.
- L470 _public function_ `AttributeType& Last(int32 IndexFromTheEnd = 0) const` — Returns n-th last element from the array attribute. @param IndexFromTheEnd (Optional) Index from the end of array. Default is 0. @returns Reference to n-th last element from the array.
- L478 _public function_ `void SetNum(int32 Num)` — Sets the number of elements in the array attribute.
- L491 _public function_ `void SetNumUninitialized(int32 Num)` — Sets the number of elements in the array attribute without initializing any new elements. It is the responsibility of the caller to do so after this function returns.
- L502 _public function_ `void Reserve(int32 Num)` — Reserves the number of elements in the array attribute.
- L513 _public function_ `int32 Add(const AttributeType& Value)` — Adds the given value to the end of the array attribute, reserving extra space if necessary.
- L525 _public function_ `int32 AddUnique(const AttributeType& Value)` — Adds the given value to the end of the array attribute, reserving extra space if necessary.
- L542 _public function_ `void InsertDefaulted(int32 StartIndex, int32 Count)` — Inserts a number of default-constructed elements in the array attribute
- L551 _public function_ `void Insert(const AttributeType& Value, int32 StartIndex)` — Inserts an element into the given index in the array attribute
- L561 _public function_ `void RemoveAt(int32 StartIndex, int32 Count)` — Removes a number of elements from the array attribute
- L571 _public function_ `template <typename Predicate> int32 RemoveAll(Predicate Pred)` — Removes all elements which match the predicate
- L594 _public function_ `int32 Remove(const AttributeType& Value)`
- L603 _public function_ `int32 Find(const AttributeType& Value) const` — Finds the given value in the array attribute and returns its index
- L618 _public function_ `template <typename Predicate> AttributeType* FindByPredicate(Predicate Pred) const` — Finds an element which matches a predicate functor. @param Pred The functor to apply to each element. @return Pointer to the first element for which the predicate returns true, or nullptr if none is found.
- L633 _public function_ `template <typename Predicate> int32 IndexOfByPredicate(Predicate Pred) const` — Finds an item by predicate. @param Pred The predicate to match. @returns Index to the first matching element, or INDEX_NONE if none is found.
- L642 _public function_ `bool Contains(const AttributeType& Value) const` — Determines whether the array attribute contains a particular value
- L656 _public function_ `template <typename Predicate> bool ContainsByPredicate(Predicate Pred) const` — Checks if this array contains element for which the predicate is true. @param Predicate to use @returns	True if found. False otherwise.
- L665 _public function_ `void Sort()` — Sorts the array assuming < operator is defined for the item type.
- L674 _public function_ `template<typename Predicate> void SortByPredicate(Predicate Pred)` — Sorts the array using the given predicate.
- L683 _public function_ `void StableSort()` — Stable sorts the array assuming < operator is defined for the item type.
- L693 _public function_ `template<typename Predicate> void StableSortByPredicate(Predicate Pred)` — Sorts the array using the given predicate.
- L701 _public function_ `TArrayView<AttributeType> ToArrayView()` — Return a TArrayView representing this array attribute.
- L706 _public function_ `operator TArrayView<AttributeType>()` — Implicitly coerce an array attribute to a TArrayView.
- L713 _public function_ `inline AttributeType* begin() const` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L714 _public function_ `inline AttributeType* end () const`
- L717 _private member_ `ArrayType* Array;`
- L718 _private member_ `int32 Index;`

#### Free symbols / members of external scopes

- L133 _function_ `friend FArchive& operator <<(FArchive& Ar, TAttributeArrayContainer<AttributeType>& Array)`
- L596 _function_ `return RemoveAll([&Value](const AttributeType& ToCompare) { return Value == ToCompare; });` (scope `TArrayAttribute::Remove`)

### `Source/Runtime/MeshDescription/Public/IMeshDescriptionModule.h` (Public)


#### class `IMeshDescriptionModule`  
`class IMeshDescriptionModule : public IModuleInterface`  
_L9-33_
- inherits: `IModuleInterface`
- L19 _public function_ `static inline IMeshDescriptionModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Runtime/MeshDescription/Public/MeshAttributeArray.h` (Public)


#### struct `TVariantFromTuple`  
`template <typename... Ts> struct TVariantFromTuple<TTuple<Ts...>>`  
_L64-64_
- L64 _public typedef_ `template <typename... Ts> struct TVariantFromTuple<TTuple<Ts...>> { using Type = TVariant<FEmptyVariantState, Ts...>; };`

#### struct `TIsBulkSerializable`  
`template <typename T> struct TIsBulkSerializable`  
_L70-70_
- desc: Traits class to specify which attribute types can be bulk serialized.
- L70 _public member_ `template <typename T> struct TIsBulkSerializable { static const bool Value = true; };` — Traits class to specify which attribute types can be bulk serialized.

#### struct `TIsBulkSerializable`  
`template <typename T> struct TIsBulkSerializable`  
_L71-71_
- desc: Traits class to specify which attribute types can be bulk serialized.
- L70 _public member_ `template <typename T> struct TIsBulkSerializable { static const bool Value = true; };` — Traits class to specify which attribute types can be bulk serialized.

#### struct `TIsBulkSerializable`  
`template <typename T> struct TIsBulkSerializable`  
_L72-72_
- desc: Traits class to specify which attribute types can be bulk serialized.
- L70 _public member_ `template <typename T> struct TIsBulkSerializable { static const bool Value = true; };` — Traits class to specify which attribute types can be bulk serialized.

#### class `TMeshAttributeArrayBase`  
`template <typename AttributeType> class TMeshAttributeArrayBase`  
_L83-163_
- desc: This defines the container used to hold mesh element attributes of a particular name and index. It is a simple TArray, so that all attributes are packed contiguously for each element ID. Note that the container may grow arbitrarily as new elements are inserted, but it will never be shrunk as elements are removed. The only operations that will shrink the container are Initialize() and Remap().
- L86 _public function_ `explicit TMeshAttributeArrayBase(uint32 InExtent = 1) : Extent(InExtent)`
- L95 _public function_ `inline int32 Num() const` — Return size of container
- L99 _public function_ `inline const AttributeType* GetData() const` — `UE_DEPRECATED(5.0, "This method will be removed.")` — Return base of data
- L102 _public function_ `inline void Initialize(const int32 ElementCount, const AttributeType& Default)` — Initializes the array to the given size with the default value
- L111 _public function_ `void SetNum(const int32 ElementCount, const AttributeType& Default)`
- L125 _public function_ `uint32 GetHash(uint32 Crc = 0) const`
- L131 _public prototype_ `void Insert(const int32 Index, const AttributeType& Default);` — Expands the array if necessary so that the passed element index is valid. Newly created elements will be assigned the default value.
- L134 _public function_ `void SetToDefault(const int32 Index, const AttributeType& Default)` — Fills the index with the default value
- L143 _public prototype_ `void Remap(const TSparseArray<int32>& IndexRemap, const AttributeType& Default);` — Remaps elements according to the passed remapping table
- L147 _public function_ `inline const AttributeType& operator[](const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use GetElementBase() instead.")` — Element accessors
- L150 _public function_ `inline AttributeType& operator[](const int32 Index)` — `UE_DEPRECATED(5.0, "Please use GetElementBase() instead.")`
- L152 _public function_ `inline const AttributeType* GetElementBase(const int32 Index) const`
- L153 _public function_ `inline AttributeType* GetElementBase(const int32 Index)`
- L155 _public function_ `inline uint32 GetExtent() const`
- L159 _protected member_ `TArray<AttributeType> Container;` — The actual container, represented by a regular array
- L162 _protected member_ `uint32 Extent;` — Number of array elements in this attribute type
- L168 _function_ `template<> inline uint32 TMeshAttributeArrayBase<FName>::GetHash(uint32 Crc) const` — We have to manually implement this or else the default behavior will just hash FName ComparisonIndex and Number, which aren't deterministic
- L179 _function_ `template <typename AttributeType> void TMeshAttributeArrayBase<AttributeType>::Insert(const int32 Index, const AttributeType& Default)`
- L200 _function_ `template <typename AttributeType> void TMeshAttributeArrayBase<AttributeType>::Remap(const TSparseArray<int32>& IndexRemap, const AttributeType& Default)`

#### enum `operator <<::EIndexSize`  
`enum class EIndexSize : uint8`  
_L283-283_
- L283 _public enumerator_ `enum class EIndexSize : uint8 { U8 = 0, U16 = 1, U32 = 2 }; TArray<FName>& Names = Array.Container; if (Ar.IsLoading()) { uint32 NumNames = 0;`
- L283 _public enumerator_ `enum class EIndexSize : uint8 { U8 = 0, U16 = 1, U32 = 2 }; TArray<FName>& Names = Array.Container; if (Ar.IsLoading()) { uint32 NumNames = 0;`
- L283 _public enumerator_ `enum class EIndexSize : uint8 { U8 = 0, U16 = 1, U32 = 2 }; TArray<FName>& Names = Array.Container; if (Ar.IsLoading()) { uint32 NumNames = 0;`

#### enum `EMeshAttributeFlags`  
`enum class EMeshAttributeFlags : uint32`  
_L480-489_
- desc: Flags specifying properties of an attribute
- L482 _public enumerator_ `None = 0`
- L483 _public enumerator_ `Lerpable = (1 << 0)`
- L484 _public enumerator_ `AutoGenerated = (1 << 1)` — Lerpable			= (1 << 0),		  Attribute can be automatically lerped according to the value of 2 or 3 other attributes
- L485 _public enumerator_ `Mergeable = (1 << 2)` — AutoGenerated		= (1 << 1),		  Attribute is auto-generated by importer or editable mesh, rather than representing an imported property
- L486 _public enumerator_ `Transient = (1 << 3)` — Mergeable			= (1 << 2),		  If all vertices' attributes are mergeable, and of near-equal value, they can be welded
- L487 _public enumerator_ `IndexReference = (1 << 4)` — Transient			= (1 << 3),		  Attribute is not serialized
- L488 _public enumerator_ `Mandatory = (1 << 5)` — IndexReference		= (1 << 4),		  Attribute is a reference to another element index

#### class `FMeshAttributeArraySetBase`  
`class FMeshAttributeArraySetBase`  
_L506-576_
- desc: This is the base class for an attribute array set. An attribute array set is a container which holds attribute arrays, one per attribute index. Many attributes have only one index, while others (such as texture coordinates) may want to define many. All attribute array set instances will be of derived types; this type exists for polymorphism purposes, so that they can be managed by a generic TUniquePtr<FMeshAttributeArraySetBase>. In general, we avoid accessing them via virtual dispatch by insisting that their type be passed as a template parameter in the accessor. This can be checked against the Type field to ensure that we are accessing an instance by its correct type.
- L510 _public function_ `inline FMeshAttributeArraySetBase(const uint32 InType, const EMeshAttributeFlags InFlags, const int32 InNumberOfElements, const uint32 InExtent) : Type(InType), Extent(InExtent), NumElements(InNumberOfElements), Flags(InFlags)` — Constructor
- L518 _public prototype_ `virtual ~FMeshAttributeArraySetBase() = default;` — Virtual interface
- L519 _public prototype_ `virtual TUniquePtr<FMeshAttributeArraySetBase> Clone() const = 0;`
- L520 _public prototype_ `virtual void Insert(const int32 Index) = 0;`
- L521 _public prototype_ `virtual void Remove(const int32 Index) = 0;`
- L522 _public prototype_ `virtual void Initialize(const int32 Count) = 0;`
- L523 _public prototype_ `virtual void SetNumElements(const int32 Count) = 0;`
- L524 _public prototype_ `virtual uint32 GetHash() const = 0;`
- L525 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;`
- L526 _public prototype_ `virtual void Remap(const TSparseArray<int32>& IndexRemap) = 0;`
- L529 _public prototype_ `virtual int32 GetNumIndices() const = 0;` — `UE_DEPRECATED(5.0, "Please use GetNumChannels().")`
- L531 _public prototype_ `virtual void SetNumIndices(const int32 NumIndices) = 0;` — `UE_DEPRECATED(5.0, "Please use SetNumChannels().")`
- L533 _public prototype_ `virtual void InsertIndex(const int32 Index) = 0;` — `UE_DEPRECATED(5.0, "Please use InsertChannel().")`
- L535 _public prototype_ `virtual void RemoveIndex(const int32 Index) = 0;` — `UE_DEPRECATED(5.0, "Please use RemoveChannel().")`
- L537 _public prototype_ `virtual int32 GetNumChannels() const = 0;`
- L538 _public prototype_ `virtual void SetNumChannels(const int32 NumChannels) = 0;`
- L539 _public prototype_ `virtual void InsertChannel(const int32 Index) = 0;`
- L540 _public prototype_ `virtual void RemoveChannel(const int32 Index) = 0;`
- L544 _public function_ `template <typename T> inline bool HasType() const` — Determine whether this attribute array set is of the given type
- L550 _public function_ `inline uint32 GetType() const` — Get the type index of this attribute array set
- L553 _public function_ `inline uint32 GetExtent() const` — Get the type extent of this attribute array set
- L556 _public function_ `inline EMeshAttributeFlags GetFlags() const` — Get the flags for this attribute array set
- L559 _public function_ `inline void SetFlags(const EMeshAttributeFlags InFlags)` — Set the flags for this attribute array set
- L562 _public function_ `inline int32 GetNumElements() const` — Return number of elements each attribute index has
- L566 _protected member_ `uint32 Type;` — Type of the attribute array (based on the tuple element index from AttributeTypes)
- L569 _protected member_ `uint32 Extent;` — Extent of the type, i.e. the number of array elements it consists of
- L572 _protected member_ `int32 NumElements;` — Number of elements in each index
- L575 _protected member_ `EMeshAttributeFlags Flags;` — Implementation-defined attribute name flags

#### class `TMeshAttributeArraySet`  
`template <typename AttributeType> class TMeshAttributeArraySet final : public FMeshAttributeArraySetBase`  
_L583-754_
- inherits: `FMeshAttributeArraySetBase`
- desc: This is a type-specific attribute array, which is actually instanced in the attribute set.
- L587 _private typedef_ `using Super = FMeshAttributeArraySetBase;`
- L591 _public function_ `inline explicit TMeshAttributeArraySet(const int32 Extent = 1) : Super(TTupleIndex<AttributeType, AttributeTypes>::Value, EMeshAttributeFlags::None, 0, Extent)` — Constructors
- L595 _public function_ `inline explicit TMeshAttributeArraySet(const int32 NumberOfChannels, const AttributeType& InDefaultValue, const EMeshAttributeFlags InFlags, const int32 InNumberOfElements, const uint32 Extent) : Super(TTupleIndex<AttributeType, AttributeTypes>::Value, InFlags, InNumberOfElements, Extent), DefaultValue(InDefaultValue)`
- L603 _public function_ `virtual TUniquePtr<FMeshAttributeArraySetBase> Clone() const override` — Creates a copy of itself and returns a TUniquePtr to it
- L609 _public function_ `virtual void Insert(const int32 Index) override` — Insert the element at the given index
- L620 _public function_ `virtual void Remove(const int32 Index) override` — Remove the element at the given index, replacing it with a default value
- L629 _public function_ `virtual void Initialize(const int32 Count) override` — Sets the number of elements to the exact number provided, and initializes them to the default value
- L639 _public function_ `virtual void SetNumElements(const int32 Count) override` — Sets the number of elements to the exact number provided, preserving existing elements if the number is bigger
- L648 _public function_ `virtual uint32 GetHash() const override`
- L659 _public function_ `virtual void Serialize(FArchive& Ar) override` — Polymorphic serialization
- L665 _public function_ `virtual void Remap(const TSparseArray<int32>& IndexRemap) override` — Performs an element index remap according to the passed array
- L675 _public function_ `virtual inline int32 GetNumIndices() const override` — `UE_DEPRECATED(5.0, "Please use GetNumChannels().")`
- L678 _public function_ `virtual inline int32 GetNumChannels() const override` — Return number of channels this attribute has
- L681 _public function_ `virtual void SetNumIndices(const int32 NumIndices) override` — `UE_DEPRECATED(5.0, "Please use SetNumChannels().")`
- L684 _public function_ `virtual void SetNumChannels(const int32 NumChannels) override` — Sets number of channels this attribute has
- L700 _public function_ `virtual void InsertIndex(const int32 Index) override` — `UE_DEPRECATED(5.0, "Please use InsertChannel().")`
- L706 _public function_ `virtual void InsertChannel(const int32 Index) override` — Insert a new attribute channel
- L713 _public function_ `virtual void RemoveIndex(const int32 Index) override` — `UE_DEPRECATED(5.0, "Please use RemoveChannel().")`
- L719 _public function_ `virtual void RemoveChannel(const int32 Index) override` — Remove the channel at the given index
- L726 _public function_ `inline const TMeshAttributeArrayBase<AttributeType>& GetArrayForIndex( const int32 Index ) const` — `UE_DEPRECATED(5.0, "Please use GetArrayForChannel().")`
- L728 _public function_ `inline TMeshAttributeArrayBase<AttributeType>& GetArrayForIndex( const int32 Index )` — `UE_DEPRECATED(5.0, "Please use GetArrayForChannel().")`
- L731 _public function_ `inline const TMeshAttributeArrayBase<AttributeType>& GetArrayForChannel( const int32 Index ) const` — Return the TMeshAttributeArrayBase corresponding to the given attribute channel
- L732 _public function_ `inline TMeshAttributeArrayBase<AttributeType>& GetArrayForChannel( const int32 Index )`
- L735 _public function_ `inline AttributeType GetDefaultValue() const` — Return default value for this attribute type
- L750 _protected member_ `TArray<TMeshAttributeArrayBase<AttributeType>, TInlineAllocator<1>> ArrayForChannels;` — An array of MeshAttributeArrays, one per channel
- L753 _protected member_ `AttributeType DefaultValue;` — The default value for an attribute of this name

#### class `TMeshUnboundedAttributeArraySet`  
`template <typename AttributeType> class TMeshUnboundedAttributeArraySet final : public FMeshAttributeArraySetBase`  
_L761-924_
- inherits: `FMeshAttributeArraySetBase`
- desc: This is a type-specific attribute array, which is actually instanced in the attribute set.
- L763 _private typedef_ `using Super = FMeshAttributeArraySetBase;`
- L767 _public function_ `inline TMeshUnboundedAttributeArraySet() : Super(TTupleIndex<AttributeType, AttributeTypes>::Value, EMeshAttributeFlags::None, 0, 0)` — Constructors
- L771 _public function_ `inline explicit TMeshUnboundedAttributeArraySet(const int32 NumberOfChannels, const AttributeType& InDefaultValue, const EMeshAttributeFlags InFlags, const int32 InNumberOfElements) : Super(TTupleIndex<AttributeType, AttributeTypes>::Value, InFlags, InNumberOfElements, 0), DefaultValue(InDefaultValue)`
- L779 _public function_ `virtual TUniquePtr<FMeshAttributeArraySetBase> Clone() const override` — Creates a copy of itself and returns a TUniquePtr to it
- L785 _public function_ `virtual void Insert(const int32 Index) override` — Insert the element at the given index
- L796 _public function_ `virtual void Remove(const int32 Index) override` — Remove the element at the given index, replacing it with a default value
- L805 _public function_ `virtual void Initialize(const int32 Count) override` — Sets the number of elements to the exact number provided, and initializes them to the default value
- L815 _public function_ `virtual void SetNumElements(const int32 Count) override` — Sets the number of elements to the exact number provided, preserving existing elements if the number is bigger
- L824 _public function_ `virtual uint32 GetHash() const override`
- L835 _public function_ `virtual void Serialize(FArchive& Ar) override` — Polymorphic serialization
- L841 _public function_ `virtual void Remap(const TSparseArray<int32>& IndexRemap) override` — Performs an element index remap according to the passed array
- L851 _public function_ `virtual inline int32 GetNumIndices() const override` — `UE_DEPRECATED(5.0, "Please use GetNumChannels().")`
- L854 _public function_ `virtual inline int32 GetNumChannels() const override` — Return number of channels this attribute has
- L857 _public function_ `virtual void SetNumIndices(const int32 NumIndices) override` — `UE_DEPRECATED(5.0, "Please use SetNumChannels().")`
- L860 _public function_ `virtual void SetNumChannels(const int32 NumChannels) override` — Sets number of channels this attribute has
- L876 _public function_ `virtual void InsertIndex(const int32 Index) override` — `UE_DEPRECATED(5.0, "Please use InsertChannel().")`
- L882 _public function_ `virtual void InsertChannel(const int32 Index) override` — Insert a new attribute channel
- L889 _public function_ `virtual void RemoveIndex(const int32 Index) override` — `UE_DEPRECATED(5.0, "Please use RemoveChannel().")`
- L895 _public function_ `virtual void RemoveChannel(const int32 Index) override` — Remove the channel at the given index
- L901 _public function_ `inline const TAttributeArrayContainer<AttributeType>& GetArrayForChannel( const int32 Index ) const` — Return the TMeshAttributeArrayBase corresponding to the given attribute channel
- L902 _public function_ `inline TAttributeArrayContainer<AttributeType>& GetArrayForChannel( const int32 Index )`
- L905 _public function_ `inline AttributeType GetDefaultValue() const` — Return default value for this attribute type
- L920 _protected member_ `TArray<TAttributeArrayContainer<AttributeType>, TInlineAllocator<1>> ArrayForChannels;` — An array of UnboundedArrays, one per channel
- L923 _protected member_ `AttributeType DefaultValue;` — The default value for an attribute of this name

#### struct `TMeshAttributesRefTypeBase`  
`template <typename T> struct TMeshAttributesRefTypeBase`  
_L938-942_
- desc: Define type traits for different kinds of mesh attributes. There are three type of attributes: - simple values (T) - fixed size arrays of values (TArrayView<T>) - variable size arrays of values (TArrayAttribute<T>) Each of these corresponds to a different type of TMeshAttributesRef and TMeshAttributeArraySet.
- L940 _public typedef_ `using AttributeType = T;`
- L941 _public typedef_ `using RealAttributeType = std::conditional_t<TIsDerivedFrom<AttributeType, FElementID>::Value, int32, AttributeType>;`

#### struct `TMeshAttributesRefType`  
`template <typename T> struct TMeshAttributesRefType : TMeshAttributesRefTypeBase<T>`  
_L945-952_
- inherits: `TMeshAttributesRefTypeBase<T>`
- L947 _public member_ `static const uint32 MinExpectedExtent = 1;`
- L948 _public member_ `static const uint32 MaxExpectedExtent = 1;`
- L949 _public typedef_ `using RefType = T;`
- L950 _public typedef_ `using ConstRefType = const T;`
- L951 _public typedef_ `using NonConstRefType = std::remove_cv_t<T>;`
- L957 _public member_ `static const uint32 MinExpectedExtent = 0;`
- L958 _public member_ `static const uint32 MaxExpectedExtent = 0xFFFFFFFF;`
- L959 _public typedef_ `using RefType = TArrayView<T>;`
- L960 _public typedef_ `using ConstRefType = TArrayView<const T>;`
- L961 _public typedef_ `using NonConstRefType = TArrayView<std::remove_cv_t<T>>;`
- L968 _public member_ `static const uint32 MaxExpectedExtent = 0;`
- L969 _public typedef_ `using RefType = TArrayAttribute<T>;`
- L970 _public typedef_ `using ConstRefType = TArrayAttribute<const T>;`
- L971 _public typedef_ `using NonConstRefType = TArrayAttribute<std::remove_cv_t<T>>;`

#### struct `TMeshAttributesRefType`  
`template <typename T> struct TMeshAttributesRefType<TArrayView<T>> : TMeshAttributesRefTypeBase<T>`  
_L955-962_
- inherits: `TMeshAttributesRefTypeBase<T>`
- L947 _public member_ `static const uint32 MinExpectedExtent = 1;`
- L948 _public member_ `static const uint32 MaxExpectedExtent = 1;`
- L949 _public typedef_ `using RefType = T;`
- L950 _public typedef_ `using ConstRefType = const T;`
- L951 _public typedef_ `using NonConstRefType = std::remove_cv_t<T>;`
- L957 _public member_ `static const uint32 MinExpectedExtent = 0;`
- L958 _public member_ `static const uint32 MaxExpectedExtent = 0xFFFFFFFF;`
- L959 _public typedef_ `using RefType = TArrayView<T>;`
- L960 _public typedef_ `using ConstRefType = TArrayView<const T>;`
- L961 _public typedef_ `using NonConstRefType = TArrayView<std::remove_cv_t<T>>;`
- L968 _public member_ `static const uint32 MaxExpectedExtent = 0;`
- L969 _public typedef_ `using RefType = TArrayAttribute<T>;`
- L970 _public typedef_ `using ConstRefType = TArrayAttribute<const T>;`
- L971 _public typedef_ `using NonConstRefType = TArrayAttribute<std::remove_cv_t<T>>;`

#### struct `TMeshAttributesRefType`  
`template <typename T> struct TMeshAttributesRefType<TArrayAttribute<T>> : TMeshAttributesRefTypeBase<T>`  
_L965-972_
- inherits: `TMeshAttributesRefTypeBase<T>`
- L947 _public member_ `static const uint32 MinExpectedExtent = 1;`
- L948 _public member_ `static const uint32 MaxExpectedExtent = 1;`
- L949 _public typedef_ `using RefType = T;`
- L950 _public typedef_ `using ConstRefType = const T;`
- L951 _public typedef_ `using NonConstRefType = std::remove_cv_t<T>;`
- L957 _public member_ `static const uint32 MinExpectedExtent = 0;`
- L958 _public member_ `static const uint32 MaxExpectedExtent = 0xFFFFFFFF;`
- L959 _public typedef_ `using RefType = TArrayView<T>;`
- L960 _public typedef_ `using ConstRefType = TArrayView<const T>;`
- L961 _public typedef_ `using NonConstRefType = TArrayView<std::remove_cv_t<T>>;`
- L968 _public member_ `static const uint32 MaxExpectedExtent = 0;`
- L969 _public typedef_ `using RefType = TArrayAttribute<T>;`
- L970 _public typedef_ `using ConstRefType = TArrayAttribute<const T>;`
- L971 _public typedef_ `using NonConstRefType = TArrayAttribute<std::remove_cv_t<T>>;`

#### struct `TMeshAttributesRegisterType`  
`template <typename T> struct TMeshAttributesRegisterType : TMeshAttributesRefType<T>`  
_L984-987_
- inherits: `TMeshAttributesRefType<T>`
- desc: Additional type traits for registering different attributes. When registering, we need to specify the attribute type with a concrete element count if necessary, i.e. - simple values (T) - fixed size arrays of values (T[N]) - variable size arrays of values (T[])
- L986 _public member_ `static const uint32 Extent = 1;`
- L992 _public member_ `static const uint32 Extent = N;`
- L998 _public member_ `static const uint32 Extent = 0;`

#### struct `TMeshAttributesRegisterType`  
`template <typename T, SIZE_T N> struct TMeshAttributesRegisterType<T[N]> : TMeshAttributesRefType<TArrayView<T>>`  
_L990-993_
- inherits: `TMeshAttributesRefType<TArrayView<T>>`
- L986 _public member_ `static const uint32 Extent = 1;`
- L992 _public member_ `static const uint32 Extent = N;`
- L998 _public member_ `static const uint32 Extent = 0;`

#### struct `TMeshAttributesRegisterType`  
`template <typename T> struct TMeshAttributesRegisterType<T[]> : TMeshAttributesRefType<TArrayAttribute<T>>`  
_L996-999_
- inherits: `TMeshAttributesRefType<TArrayAttribute<T>>`
- L986 _public member_ `static const uint32 Extent = 1;`
- L992 _public member_ `static const uint32 Extent = N;`
- L998 _public member_ `static const uint32 Extent = 0;`

#### class `TMeshAttributesRef`  
``  
_L1024-1211_
- desc: This is the default implementation which handles simple attributes, i.e. those of a simple type T.
- L1029 _public typedef_ `using BaseArrayType = TCopyQualifiersFromTo_T<AttributeType, FMeshAttributeArraySetBase>;`
- L1030 _public typedef_ `using ArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1033 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 1) : ArrayPtr(InArrayPtr)` — Constructor taking a pointer to a FMeshAttributeArraySetBase
- L1042 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, SrcAttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1049 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, AttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1060 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, SrcAttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1066 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> AttributeType& operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1073 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> AttributeType Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1078 _public function_ `AttributeType& operator[](int32 ElementIndex) const`
- L1083 _public function_ `AttributeType Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1088 _public function_ `TArrayView<AttributeType> GetArrayView(int32 ElementIndex, const int32 Channel = 0) const`
- L1093 _public function_ `TArrayView<AttributeType> GetRawArray(const int32 AttributeChannel = 0) const`
- L1105 _public function_ `bool IsValid() const` — Return whether the reference is valid or not
- L1108 _public function_ `AttributeType GetDefaultValue() const` — Return default value for this attribute type
- L1111 _public function_ `int32 GetNumIndices() const` — `UE_DEPRECATED(5.0, "Please use GetNumChannels().")`
- L1117 _public function_ `int32 GetNumChannels() const` — Return number of indices this attribute has
- L1123 _public function_ `int32 GetNumElements() const` — Get the number of elements in this attribute array
- L1129 _public function_ `EMeshAttributeFlags GetFlags() const` — Get the flags for this attribute array set
- L1132 _public function_ `uint32 GetExtent() const` — Get the extent for this attribute type
- L1136 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const AttributeType& Value) const` — Set the element with the given ID and index 0 to the provided value
- L1143 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, const AttributeType& Value) const` — Set the element with the given ID and channel to the provided value
- L1148 _public function_ `void Set(int32 ElementIndex, const AttributeType& Value) const`
- L1153 _public function_ `void Set(int32 ElementIndex, const int32 Channel, const AttributeType& Value) const`
- L1158 _public function_ `void SetArrayView(int32 ElementIndex, TArrayView<const AttributeType> Value) const`
- L1164 _public function_ `void SetArrayView(int32 ElementIndex, const int32 Channel, TArrayView<const AttributeType> Value) const`
- L1171 _public prototype_ `void Copy(TMeshAttributesRef<ElementIDType, const AttributeType> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and channel to this channel
- L1174 _public function_ `void SetNumIndices(const int32 NumChannels) const` — `UE_DEPRECATED(5.0, "Please use SetNumChannels().")`
- L1180 _public function_ `void SetNumChannels(const int32 NumChannels) const` — Sets number of channels this attribute has
- L1186 _public function_ `void InsertIndex(const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use InsertChannel().")`
- L1192 _public function_ `void InsertChannel(const int32 Channel) const` — Inserts an attribute channel
- L1198 _public function_ `void RemoveIndex(const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use RemoveChannel().")`
- L1204 _public function_ `void RemoveChannel(const int32 Channel) const` — Removes an attribute channel
- L1210 _private member_ `BaseArrayType* ArrayPtr;`
- L1214 _function_ `template <typename ElementIDType, typename AttributeType> void TMeshAttributesRef<ElementIDType, AttributeType>::Copy(TMeshAttributesRef<ElementIDType, const AttributeType> Src, const int32 DestChannel, const int32 SrcChannel)`
- L1234 _public typedef_ `using BoundedArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1235 _public typedef_ `using UnboundedArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshUnboundedAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1238 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 1) : ArrayPtr(InArrayPtr), Extent(InExtent)` — Constructor taking a pointer to a TMeshAttributeArraySet
- L1248 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, TArrayView<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1256 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayView<AttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1268 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayView<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1276 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayView<AttributeType> operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1291 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayView<AttributeType> Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1304 _public function_ `TArrayView<AttributeType> operator[](int32 ElementIndex) const`
- L1317 _public function_ `TArrayView<AttributeType> Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1342 _public function_ `TArrayView<AttributeType> GetRawArray(const int32 ChannelIndex = 0) const`
- L1388 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, TArrayView<const AttributeType> Value) const` — Set the element with the given ID and index 0 to the provided value
- L1400 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, TArrayView<const AttributeType> Value) const` — Set the element with the given ID and channel to the provided value
- L1410 _public function_ `void Set(int32 ElementIndex, TArrayView<const AttributeType> Value) const`
- L1420 _public function_ `void Set(int32 ElementIndex, const int32 Channel, TArrayView<const AttributeType> Value) const`
- L1441 _public prototype_ `void Copy(TMeshAttributesConstRef<ElementIDType, TArrayView<AttributeType>> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and index to this index
- L1481 _private member_ `uint32 Extent;`
- L1485 _function_ `template <typename ElementIDType, typename AttributeType> void TMeshAttributesRef<ElementIDType, TArrayView<AttributeType>>::Copy(TMeshAttributesConstRef<ElementIDType, TArrayView<AttributeType>> Src, const int32 DestChannel, const int32 SrcChannel)`
- L1510 _public typedef_ `using ArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshUnboundedAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1513 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 0) : ArrayPtr(InArrayPtr)` — Constructor taking a pointer to a TMeshUnboundedAttributeArraySet
- L1522 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, TArrayAttribute<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1529 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayAttribute<AttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1540 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayAttribute<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1547 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayAttribute<AttributeType> operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1554 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayAttribute<AttributeType> Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1559 _public function_ `TArrayAttribute<AttributeType> operator[](int32 ElementIndex) const`
- L1564 _public function_ `TArrayAttribute<AttributeType> Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1575 _public function_ `const TAttributeArrayContainer<AttributeType>* GetRawArray(const int32 AttributeChannel = 0) const` — In this specialization, GetRawArray returns a pointer to the attribute array container holding the attributes and their index pointers
- L1608 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, TArrayAttribute<const AttributeType> Value) const` — Set the element with the given ID and index 0 to the provided value
- L1615 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, TArrayAttribute<const AttributeType> Value) const` — Set the element with the given ID and channel to the provided value
- L1620 _public function_ `void Set(int32 ElementIndex, TArrayAttribute<const AttributeType> Value) const`
- L1625 _public function_ `void Set(int32 ElementIndex, const int32 Channel, TArrayAttribute<const AttributeType> Value) const`
- L1641 _public prototype_ `void Copy(TMeshAttributesConstRef<ElementIDType, TArrayAttribute<AttributeType>> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and index to this index
- L1650 _public function_ `void InsertChannel(const int32 Index) const` — Inserts an attribute channel
- L1656 _public function_ `void RemoveChannel(const int32 Index) const` — Removes an attribute channel

#### class `TMeshAttributesRef`  
`template <typename ElementIDType, typename AttributeType> class TMeshAttributesRef<ElementIDType, TArrayView<AttributeType>>`  
_L1228-1482_
- L1029 _public typedef_ `using BaseArrayType = TCopyQualifiersFromTo_T<AttributeType, FMeshAttributeArraySetBase>;`
- L1030 _public typedef_ `using ArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1033 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 1) : ArrayPtr(InArrayPtr)` — Constructor taking a pointer to a FMeshAttributeArraySetBase
- L1042 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, SrcAttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1049 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, AttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1060 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, SrcAttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1066 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> AttributeType& operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1073 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> AttributeType Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1078 _public function_ `AttributeType& operator[](int32 ElementIndex) const`
- L1083 _public function_ `AttributeType Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1088 _public function_ `TArrayView<AttributeType> GetArrayView(int32 ElementIndex, const int32 Channel = 0) const`
- L1093 _public function_ `TArrayView<AttributeType> GetRawArray(const int32 AttributeChannel = 0) const`
- L1105 _public function_ `bool IsValid() const` — Return whether the reference is valid or not
- L1108 _public function_ `AttributeType GetDefaultValue() const` — Return default value for this attribute type
- L1111 _public function_ `int32 GetNumIndices() const` — `UE_DEPRECATED(5.0, "Please use GetNumChannels().")`
- L1117 _public function_ `int32 GetNumChannels() const` — Return number of indices this attribute has
- L1123 _public function_ `int32 GetNumElements() const` — Get the number of elements in this attribute array
- L1129 _public function_ `EMeshAttributeFlags GetFlags() const` — Get the flags for this attribute array set
- L1132 _public function_ `uint32 GetExtent() const` — Get the extent for this attribute type
- L1136 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const AttributeType& Value) const` — Set the element with the given ID and index 0 to the provided value
- L1143 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, const AttributeType& Value) const` — Set the element with the given ID and channel to the provided value
- L1148 _public function_ `void Set(int32 ElementIndex, const AttributeType& Value) const`
- L1153 _public function_ `void Set(int32 ElementIndex, const int32 Channel, const AttributeType& Value) const`
- L1158 _public function_ `void SetArrayView(int32 ElementIndex, TArrayView<const AttributeType> Value) const`
- L1164 _public function_ `void SetArrayView(int32 ElementIndex, const int32 Channel, TArrayView<const AttributeType> Value) const`
- L1171 _public prototype_ `void Copy(TMeshAttributesRef<ElementIDType, const AttributeType> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and channel to this channel
- L1174 _public function_ `void SetNumIndices(const int32 NumChannels) const` — `UE_DEPRECATED(5.0, "Please use SetNumChannels().")`
- L1180 _public function_ `void SetNumChannels(const int32 NumChannels) const` — Sets number of channels this attribute has
- L1186 _public function_ `void InsertIndex(const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use InsertChannel().")`
- L1192 _public function_ `void InsertChannel(const int32 Channel) const` — Inserts an attribute channel
- L1198 _public function_ `void RemoveIndex(const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use RemoveChannel().")`
- L1204 _public function_ `void RemoveChannel(const int32 Channel) const` — Removes an attribute channel
- L1210 _private member_ `BaseArrayType* ArrayPtr;`
- L1214 _function_ `template <typename ElementIDType, typename AttributeType> void TMeshAttributesRef<ElementIDType, AttributeType>::Copy(TMeshAttributesRef<ElementIDType, const AttributeType> Src, const int32 DestChannel, const int32 SrcChannel)`
- L1234 _public typedef_ `using BoundedArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1235 _public typedef_ `using UnboundedArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshUnboundedAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1238 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 1) : ArrayPtr(InArrayPtr), Extent(InExtent)` — Constructor taking a pointer to a TMeshAttributeArraySet
- L1248 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, TArrayView<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1256 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayView<AttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1268 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayView<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1276 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayView<AttributeType> operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1291 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayView<AttributeType> Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1304 _public function_ `TArrayView<AttributeType> operator[](int32 ElementIndex) const`
- L1317 _public function_ `TArrayView<AttributeType> Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1342 _public function_ `TArrayView<AttributeType> GetRawArray(const int32 ChannelIndex = 0) const`
- L1388 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, TArrayView<const AttributeType> Value) const` — Set the element with the given ID and index 0 to the provided value
- L1400 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, TArrayView<const AttributeType> Value) const` — Set the element with the given ID and channel to the provided value
- L1410 _public function_ `void Set(int32 ElementIndex, TArrayView<const AttributeType> Value) const`
- L1420 _public function_ `void Set(int32 ElementIndex, const int32 Channel, TArrayView<const AttributeType> Value) const`
- L1441 _public prototype_ `void Copy(TMeshAttributesConstRef<ElementIDType, TArrayView<AttributeType>> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and index to this index
- L1481 _private member_ `uint32 Extent;`
- L1485 _function_ `template <typename ElementIDType, typename AttributeType> void TMeshAttributesRef<ElementIDType, TArrayView<AttributeType>>::Copy(TMeshAttributesConstRef<ElementIDType, TArrayView<AttributeType>> Src, const int32 DestChannel, const int32 SrcChannel)`
- L1510 _public typedef_ `using ArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshUnboundedAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1513 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 0) : ArrayPtr(InArrayPtr)` — Constructor taking a pointer to a TMeshUnboundedAttributeArraySet
- L1522 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, TArrayAttribute<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1529 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayAttribute<AttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1540 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayAttribute<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1547 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayAttribute<AttributeType> operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1554 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayAttribute<AttributeType> Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1559 _public function_ `TArrayAttribute<AttributeType> operator[](int32 ElementIndex) const`
- L1564 _public function_ `TArrayAttribute<AttributeType> Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1575 _public function_ `const TAttributeArrayContainer<AttributeType>* GetRawArray(const int32 AttributeChannel = 0) const` — In this specialization, GetRawArray returns a pointer to the attribute array container holding the attributes and their index pointers
- L1608 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, TArrayAttribute<const AttributeType> Value) const` — Set the element with the given ID and index 0 to the provided value
- L1615 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, TArrayAttribute<const AttributeType> Value) const` — Set the element with the given ID and channel to the provided value
- L1620 _public function_ `void Set(int32 ElementIndex, TArrayAttribute<const AttributeType> Value) const`
- L1625 _public function_ `void Set(int32 ElementIndex, const int32 Channel, TArrayAttribute<const AttributeType> Value) const`
- L1641 _public prototype_ `void Copy(TMeshAttributesConstRef<ElementIDType, TArrayAttribute<AttributeType>> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and index to this index
- L1650 _public function_ `void InsertChannel(const int32 Index) const` — Inserts an attribute channel
- L1656 _public function_ `void RemoveChannel(const int32 Index) const` — Removes an attribute channel

#### class `TMeshAttributesRef`  
`template <typename ElementIDType, typename AttributeType> class TMeshAttributesRef<ElementIDType, TArrayAttribute<AttributeType>>`  
_L1504-1663_
- L1029 _public typedef_ `using BaseArrayType = TCopyQualifiersFromTo_T<AttributeType, FMeshAttributeArraySetBase>;`
- L1030 _public typedef_ `using ArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1033 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 1) : ArrayPtr(InArrayPtr)` — Constructor taking a pointer to a FMeshAttributeArraySetBase
- L1042 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, SrcAttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1049 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, AttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1060 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, SrcAttributeType>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1066 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> AttributeType& operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1073 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> AttributeType Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1078 _public function_ `AttributeType& operator[](int32 ElementIndex) const`
- L1083 _public function_ `AttributeType Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1088 _public function_ `TArrayView<AttributeType> GetArrayView(int32 ElementIndex, const int32 Channel = 0) const`
- L1093 _public function_ `TArrayView<AttributeType> GetRawArray(const int32 AttributeChannel = 0) const`
- L1105 _public function_ `bool IsValid() const` — Return whether the reference is valid or not
- L1108 _public function_ `AttributeType GetDefaultValue() const` — Return default value for this attribute type
- L1111 _public function_ `int32 GetNumIndices() const` — `UE_DEPRECATED(5.0, "Please use GetNumChannels().")`
- L1117 _public function_ `int32 GetNumChannels() const` — Return number of indices this attribute has
- L1123 _public function_ `int32 GetNumElements() const` — Get the number of elements in this attribute array
- L1129 _public function_ `EMeshAttributeFlags GetFlags() const` — Get the flags for this attribute array set
- L1132 _public function_ `uint32 GetExtent() const` — Get the extent for this attribute type
- L1136 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const AttributeType& Value) const` — Set the element with the given ID and index 0 to the provided value
- L1143 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, const AttributeType& Value) const` — Set the element with the given ID and channel to the provided value
- L1148 _public function_ `void Set(int32 ElementIndex, const AttributeType& Value) const`
- L1153 _public function_ `void Set(int32 ElementIndex, const int32 Channel, const AttributeType& Value) const`
- L1158 _public function_ `void SetArrayView(int32 ElementIndex, TArrayView<const AttributeType> Value) const`
- L1164 _public function_ `void SetArrayView(int32 ElementIndex, const int32 Channel, TArrayView<const AttributeType> Value) const`
- L1171 _public prototype_ `void Copy(TMeshAttributesRef<ElementIDType, const AttributeType> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and channel to this channel
- L1174 _public function_ `void SetNumIndices(const int32 NumChannels) const` — `UE_DEPRECATED(5.0, "Please use SetNumChannels().")`
- L1180 _public function_ `void SetNumChannels(const int32 NumChannels) const` — Sets number of channels this attribute has
- L1186 _public function_ `void InsertIndex(const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use InsertChannel().")`
- L1192 _public function_ `void InsertChannel(const int32 Channel) const` — Inserts an attribute channel
- L1198 _public function_ `void RemoveIndex(const int32 Index) const` — `UE_DEPRECATED(5.0, "Please use RemoveChannel().")`
- L1204 _public function_ `void RemoveChannel(const int32 Channel) const` — Removes an attribute channel
- L1210 _private member_ `BaseArrayType* ArrayPtr;`
- L1214 _function_ `template <typename ElementIDType, typename AttributeType> void TMeshAttributesRef<ElementIDType, AttributeType>::Copy(TMeshAttributesRef<ElementIDType, const AttributeType> Src, const int32 DestChannel, const int32 SrcChannel)`
- L1234 _public typedef_ `using BoundedArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1235 _public typedef_ `using UnboundedArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshUnboundedAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1238 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 1) : ArrayPtr(InArrayPtr), Extent(InExtent)` — Constructor taking a pointer to a TMeshAttributeArraySet
- L1248 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, TArrayView<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1256 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayView<AttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1268 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayView<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr), Extent(InRef.Extent)`
- L1276 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayView<AttributeType> operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1291 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayView<AttributeType> Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1304 _public function_ `TArrayView<AttributeType> operator[](int32 ElementIndex) const`
- L1317 _public function_ `TArrayView<AttributeType> Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1342 _public function_ `TArrayView<AttributeType> GetRawArray(const int32 ChannelIndex = 0) const`
- L1388 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, TArrayView<const AttributeType> Value) const` — Set the element with the given ID and index 0 to the provided value
- L1400 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, TArrayView<const AttributeType> Value) const` — Set the element with the given ID and channel to the provided value
- L1410 _public function_ `void Set(int32 ElementIndex, TArrayView<const AttributeType> Value) const`
- L1420 _public function_ `void Set(int32 ElementIndex, const int32 Channel, TArrayView<const AttributeType> Value) const`
- L1441 _public prototype_ `void Copy(TMeshAttributesConstRef<ElementIDType, TArrayView<AttributeType>> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and index to this index
- L1481 _private member_ `uint32 Extent;`
- L1485 _function_ `template <typename ElementIDType, typename AttributeType> void TMeshAttributesRef<ElementIDType, TArrayView<AttributeType>>::Copy(TMeshAttributesConstRef<ElementIDType, TArrayView<AttributeType>> Src, const int32 DestChannel, const int32 SrcChannel)`
- L1510 _public typedef_ `using ArrayType = TCopyQualifiersFromTo_T<AttributeType, TMeshUnboundedAttributeArraySet<std::remove_cv_t<AttributeType>>>;`
- L1513 _public function_ `explicit TMeshAttributesRef(BaseArrayType* InArrayPtr = nullptr, uint32 InExtent = 0) : ArrayPtr(InArrayPtr)` — Constructor taking a pointer to a TMeshUnboundedAttributeArraySet
- L1522 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<ElementIDType, TArrayAttribute<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1529 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayAttribute<AttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1540 _public function_ `TMeshAttributesRef(const TMeshAttributesRef<int32, TArrayAttribute<SrcAttributeType>>& InRef) : ArrayPtr(InRef.ArrayPtr)`
- L1547 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayAttribute<AttributeType> operator[](const ElementIDType ElementID) const` — Access elements from attribute channel 0
- L1554 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> TArrayAttribute<AttributeType> Get(const ElementIDType ElementID, const int32 Channel = 0) const` — Get the element with the given ID and channel
- L1559 _public function_ `TArrayAttribute<AttributeType> operator[](int32 ElementIndex) const`
- L1564 _public function_ `TArrayAttribute<AttributeType> Get(int32 ElementIndex, const int32 Channel = 0) const`
- L1575 _public function_ `const TAttributeArrayContainer<AttributeType>* GetRawArray(const int32 AttributeChannel = 0) const` — In this specialization, GetRawArray returns a pointer to the attribute array container holding the attributes and their index pointers
- L1608 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, TArrayAttribute<const AttributeType> Value) const` — Set the element with the given ID and index 0 to the provided value
- L1615 _public function_ `template <typename T = ElementIDType, typename TEnableIf<TIsDerivedFrom<T, FElementID>::Value, int>::Type = 0> void Set(const ElementIDType ElementID, const int32 Channel, TArrayAttribute<const AttributeType> Value) const` — Set the element with the given ID and channel to the provided value
- L1620 _public function_ `void Set(int32 ElementIndex, TArrayAttribute<const AttributeType> Value) const`
- L1625 _public function_ `void Set(int32 ElementIndex, const int32 Channel, TArrayAttribute<const AttributeType> Value) const`
- L1641 _public prototype_ `void Copy(TMeshAttributesConstRef<ElementIDType, TArrayAttribute<AttributeType>> Src, const int32 DestChannel = 0, const int32 SrcChannel = 0);` — Copies the given attribute array and index to this index
- L1650 _public function_ `void InsertChannel(const int32 Index) const` — Inserts an attribute channel
- L1656 _public function_ `void RemoveChannel(const int32 Index) const` — Removes an attribute channel

#### class `FAttributesSetEntry`  
`class FAttributesSetEntry`  
_L1671-1738_
- desc: This is a wrapper for an allocated attributes array. It holds a TUniquePtr pointing to the actual attributes array, and performs polymorphic copy and assignment, as per the actual array type.
- L1678 _public prototype_ `FAttributesSetEntry() = default;` — Default constructor. This breaks the invariant that Ptr be always valid, but is necessary so that it can be the value type of a TMap.
- L1684 _public function_ `template <typename AttributeType> FAttributesSetEntry(const int32 NumberOfChannels, const AttributeType& Default, const EMeshAttributeFlags Flags, const int32 NumElements, const int32 Extent)` — Construct a valid FAttributesSetEntry of the concrete type specified.
- L1697 _public prototype_ `~FAttributesSetEntry() = default;` — Default destructor
- L1700 _public function_ `FAttributesSetEntry(const FAttributesSetEntry& Other) : Ptr(Other.Ptr ? Other.Ptr->Clone() : nullptr)` — Polymorphic copy: a new copy of Other is created
- L1705 _public prototype_ `FAttributesSetEntry(FAttributesSetEntry&&) = default;` — Default move constructor
- L1708 _public function_ `FAttributesSetEntry& operator=(const FAttributesSetEntry& Other)` — Polymorphic assignment
- L1716 _public prototype_ `FAttributesSetEntry& operator=(FAttributesSetEntry&&) = default;` — Default move assignment
- L1719 _public function_ `inline const FMeshAttributeArraySetBase* Get() const` — Transparent access through the TUniquePtr
- L1720 _public function_ `inline const FMeshAttributeArraySetBase* operator->() const`
- L1721 _public function_ `inline const FMeshAttributeArraySetBase& operator*() const`
- L1722 _public function_ `inline FMeshAttributeArraySetBase* Get()`
- L1723 _public function_ `inline FMeshAttributeArraySetBase* operator->()`
- L1724 _public function_ `inline FMeshAttributeArraySetBase& operator*()`
- L1727 _public function_ `inline explicit operator bool() const` — Object can be coerced to bool to indicate if it is valid
- L1728 _public function_ `inline bool operator!() const`
- L1731 _public prototype_ `void CreateArrayOfType(const uint32 Type, const uint32 Extent);` — Given a type at runtime, allocate an attribute array of that type, owned by Ptr
- L1737 _private member_ `TUniquePtr<FMeshAttributeArraySetBase> Ptr;`
- L2610 _function_ `inline void FAttributesSetEntry::CreateArrayOfType(const uint32 Type, const uint32 Extent)`

#### class `FAttributesSetBase`  
`class FAttributesSetBase`  
_L1745-2053_
- desc: This is the container for all attributes and their arrays. It wraps a TMap, mapping from attribute name to attribute array. An attribute may be of any arbitrary type; we use a mixture of polymorphism and compile-time templates to handle the different types.
- L1749 _public function_ `FAttributesSetBase() : NumElements(0)` — Constructor
- L1766 _public function_ `template <typename T> TMeshAttributesArray<typename TMeshAttributesRegisterType<T>::RefType> RegisterAttributeInternal( const FName AttributeName, const int32 NumberOfChannels = 1, const typename TMeshAttributesRegisterType<T>::RealAttributeType& Default = typename TMeshAttributesRegisterType<T>::RealAttributeType(), const EMeshAttributeFlags Flags = EMeshAttributeFlags::None)`
- L1803 _public function_ `TMeshAttributesArray<typename TMeshAttributesRegisterType<T>::RefType> RegisterAttribute( const FName AttributeName, const int32 NumberOfChannels = 1, const T& Default = T(), const EMeshAttributeFlags Flags = EMeshAttributeFlags::None)`
- L1820 _public function_ `TMeshAttributesArray<typename TMeshAttributesRegisterType<T>::RefType> RegisterAttribute( const FName AttributeName, const int32 NumberOfChannels = 1, const typename TMeshAttributesRegisterType<T>::RealAttributeType& Default = typename TMeshAttributesRegisterType<T>::RealAttributeType(), const EMeshAttributeFlags Flags = EMeshAttributeFlags::None)`
- L1837 _public function_ `TMeshAttributesArray<typename TMeshAttributesRegisterType<T>::RefType> RegisterIndexAttribute( const FName AttributeName, const int32 NumberOfChannels = 1, const EMeshAttributeFlags Flags = EMeshAttributeFlags::None)`
- L1848 _public function_ `void UnregisterAttribute(const FName AttributeName)` — Unregister an attribute with the given name.
- L1854 _public function_ `bool HasAttribute(const FName AttributeName) const` — Determines whether an attribute exists with the given name
- L1863 _public function_ `template <typename T> bool HasAttributeOfType(const FName AttributeName) const` — Determines whether an attribute of the given type exists with the given name
- L1878 _public function_ `void Initialize(const int32 Count)` — Initializes all attributes to have the given number of elements with the default value
- L1888 _public function_ `void SetNumElements(const int32 Count)` — Sets all attributes to have the given number of elements, preserving existing values and filling extra elements with the default value
- L1898 _public function_ `int32 GetNumElements() const` — Gets the number of elements in the attribute set
- L1904 _public prototype_ `void Remap(const TSparseArray<int32>& IndexRemap);` — Applies the given remapping to the attributes set
- L1908 _public function_ `template <typename Allocator> void GetAttributeNames(TArray<FName, Allocator>& OutAttributeNames) const` — Returns an array of all the attribute names registered
- L1914 _public function_ `bool DoesAttributeHaveAnyFlags(const FName AttributeName, EMeshAttributeFlags AttributeFlags) const` — Determine whether an attribute has any of the given flags
- L1925 _public function_ `bool DoesAttributeHaveAllFlags(const FName AttributeName, EMeshAttributeFlags AttributeFlags) const` — Determine whether an attribute has all of the given flags
- L1935 _public function_ `uint32 GetHash(const FName AttributeName) const`
- L1948 _public function_ `void Insert(const int32 Index)` — Insert a new element at the given index. The public API version of this function takes an ID of ElementIDType instead of a typeless index.
- L1981 _public function_ `void Remove(const int32 Index)` — Remove an element at the given index. The public API version of this function takes an ID of ElementIDType instead of a typeless index.
- L1994 _public function_ `template <typename T> TMeshAttributesConstRef<int32, typename TMeshAttributesRefType<T>::ConstRefType> GetAttributesRef(const FName AttributeName) const` — Get an attribute array with the given type and name. The attribute type must correspond to the type passed as the template parameter.
- L2017 _public function_ `template <typename T> TMeshAttributesRef<int32, typename TMeshAttributesRefType<T>::RefType> GetAttributesRef(const FName AttributeName)`
- L2039 _public prototype_ `void AppendAttributesFrom(const FAttributesSetBase& OtherAttributesSet);`
- L2049 _protected member_ `TMap<FName, FAttributesSetEntry> Map;` — The actual container
- L2052 _protected member_ `int32 NumElements;` — The number of elements in each attribute array

#### class `TAttributesSet`  
`template <typename ElementIDType> class TAttributesSet final : public FAttributesSetBase`  
_L2061-2331_
- inherits: `FAttributesSetBase`
- desc: This is a version of the attributes set container which accesses elements by typesafe IDs. This prevents access of (for example) vertex instance attributes by vertex IDs.
- L2084 _public function_ `template <typename T> TMeshAttributesConstRef<ElementIDType, typename TMeshAttributesRefType<T>::ConstRefType> GetAttributesRef(const FName AttributeName) const` — Get an attribute array with the given type and name. The attribute type must correspond to the type passed as the template parameter. Example of use: TVertexAttributesConstRef<FVector> VertexPositions = VertexAttributes().GetAttributesRef<FVector>( "Position" ); // note: assign to value type for( const FVertexID VertexID : GetVertices().GetElementIDs() ) { const FVector Position = VertexPositions.Get( VertexID ); DoSomethingWith( Position ); } Note that the returned object is a value type which should be assigned and passed by value, not reference. It is valid for as long as this TAttributesSet object exists.
- L2108 _public function_ `template <typename T> TMeshAttributesRef<ElementIDType, typename TMeshAttributesRefType<T>::RefType> GetAttributesRef(const FName AttributeName)` — Non-const version
- L2132 _public function_ `int32 GetAttributeIndexCount(const FName AttributeName) const` — `UE_DEPRECATED(5.0, "Please use GetAttributeChannelCount() instead.")`
- L2138 _public function_ `int32 GetAttributeChannelCount(const FName AttributeName) const` — Returns the number of indices for the attribute with the given name
- L2165 _public function_ `void SetAttributeIndexCount(const FName AttributeName, const int32 NumChannels)` — `UE_DEPRECATED(5.0, "Please use SetAttributeChannelCount() instead.")`
- L2171 _public function_ `void SetAttributeChannelCount(const FName AttributeName, const int32 NumChannels)` — Sets the number of indices for the attribute with the given name
- L2181 _public function_ `void SetAttributeIndexCount(const FName AttributeName, const int32 NumIndices)` — `UE_DEPRECATED(5.0, "Please use untemplated SetAttributeChannelCount() instead.")`
- L2194 _public function_ `void InsertAttributeIndex(const FName AttributeName, const int32 Index)` — `UE_DEPRECATED(5.0, "Please use InsertAttributeChannel() instead.")`
- L2200 _public function_ `void InsertAttributeChannel(const FName AttributeName, const int32 Index)` — Insert a new index for the attribute with the given name
- L2223 _public function_ `void RemoveAttributeIndex(const FName AttributeName, const int32 Index)` — `UE_DEPRECATED(5.0, "Please use RemoveAttributeChannel() instead.")`
- L2229 _public function_ `void RemoveAttributeChannel(const FName AttributeName, const int32 Index)` — Remove an existing index from the attribute with the given name
- L2256 _public function_ `template <typename T> T GetAttribute(const ElementIDType ElementID, const FName AttributeName, const int32 AttributeChannel = 0) const` — Get an attribute value for the given element ID. Note: it is generally preferable to get a TMeshAttributesRef and access elements through that, if you wish to access more than one.
- L2277 _public function_ `template <typename T> void SetAttribute(const ElementIDType ElementID, const FName AttributeName, const int32 AttributeChannel, const T& AttributeValue)` — Set an attribute value for the given element ID. Note: it is generally preferable to get a TMeshAttributesRef and set multiple elements through that.
- L2295 _public function_ `inline void Insert(const ElementIDType ElementID)` — Inserts a default-initialized value for all attributes of the given ID
- L2301 _public function_ `inline void Remove(const ElementIDType ElementID)` — Removes all attributes with the given ID
- L2310 _public prototype_ `template <typename ForEachFunc> void ForEach(ForEachFunc Func);` — Call the supplied function on each attribute. The prototype should be Func( const FName AttributeName, auto AttributesRef );
- L2316 _public prototype_ `template <typename ForEachFunc> void ForEach(ForEachFunc Func) const;` — Call the supplied function on each attribute. The prototype should be Func( const FName AttributeName, auto AttributesConstRef );
- L2323 _public prototype_ `template <typename AttributeType, typename ForEachFunc> void ForEachByType(ForEachFunc Func);` — Call the supplied function on each attribute that matches the given type. The type can be given as either a plain type T, TArrayView<T> or TArrayAttribute<T>. The prototype should be Func( const FName AttributeName, auto AttributesRef );
- L2330 _public prototype_ `template <typename AttributeType, typename ForEachFunc> void ForEachByType(ForEachFunc Func) const;` — Call the supplied function on each attribute that matches the given type. The type can be given as either a plain type T, TArrayView<T> or TArrayAttribute<T>. The prototype should be Func( const FName AttributeName, auto AttributesConstRef );
- L2418 _function_ `template <typename ElementIDType> template <typename ForEachFunc> void TAttributesSet<ElementIDType>::ForEach(ForEachFunc Func)`
- L2467 _function_ `template <typename ElementIDType> template <typename ForEachFunc> void TAttributesSet<ElementIDType>::ForEach(ForEachFunc Func) const`
- L2557 _function_ `template <typename ElementIDType> template < typename AttributeType, typename ForEachFunc> void TAttributesSet<ElementIDType>::ForEachByType(ForEachFunc Func)`
- L2567 _function_ `template <typename ElementIDType> template < typename AttributeType, typename ForEachFunc> void TAttributesSet<ElementIDType>::ForEachByType(ForEachFunc Func) const`

#### struct `TJumpTable`  
`template <typename FnType, uint32 Size> struct TJumpTable`  
_L2373-2379_
- desc: Class which implements a function jump table to be automatically generated at compile time. This is used by TAttributesSet to provide O(1) dispatch by attribute type at runtime.
- L2376 _public function_ `template <typename... T> explicit constexpr TJumpTable( T... Ts ) : Fns`
- L2378 _public member_ `FnType* Fns[Size];`

#### struct `ForEachByTypeImpl::DispatchFunctor`  
`template<typename ElementIDType, typename AttributeType, typename ForEachFunc> struct DispatchFunctor`  
_L2484-2493_
- L2486 _public function_ `void operator()(FName Name, ForEachFunc Fn, FMeshAttributeArraySetBase* Attributes)`

#### struct `ForEachByTypeImpl::DispatchFunctor`  
`template<typename ElementIDType, typename AttributeType, typename ForEachFunc> struct DispatchFunctor<ElementIDType, TArrayView<AttributeType>, ForEachFunc>`  
_L2496-2505_
- L2486 _public function_ `void operator()(FName Name, ForEachFunc Fn, FMeshAttributeArraySetBase* Attributes)`

#### struct `ForEachByTypeImpl::DispatchFunctor`  
`template<typename ElementIDType, typename AttributeType, typename ForEachFunc> struct DispatchFunctor<ElementIDType, TArrayAttribute<AttributeType>, ForEachFunc>`  
_L2508-2517_
- L2486 _public function_ `void operator()(FName Name, ForEachFunc Fn, FMeshAttributeArraySetBase* Attributes)`

#### struct `ForEachByTypeImpl::ConstDispatchFunctor`  
`template<typename ElementIDType, typename AttributeType, typename ForEachFunc> struct ConstDispatchFunctor`  
_L2520-2529_
- L2522 _public function_ `void operator()(FName Name, ForEachFunc Fn, const FMeshAttributeArraySetBase* Attributes)`

#### struct `ForEachByTypeImpl::ConstDispatchFunctor`  
`template<typename ElementIDType, typename AttributeType, typename ForEachFunc> struct ConstDispatchFunctor<ElementIDType, TArrayView<AttributeType>, ForEachFunc>`  
_L2532-2541_
- L2522 _public function_ `void operator()(FName Name, ForEachFunc Fn, const FMeshAttributeArraySetBase* Attributes)`

#### struct `ForEachByTypeImpl::ConstDispatchFunctor`  
`template<typename ElementIDType, typename AttributeType, typename ForEachFunc> struct ConstDispatchFunctor<ElementIDType, TArrayAttribute<AttributeType>, ForEachFunc>`  
_L2544-2553_
- L2522 _public function_ `void operator()(FName Name, ForEachFunc Fn, const FMeshAttributeArraySetBase* Attributes)`

#### Free symbols / members of external scopes

- L46 _typedef_ `using AttributeTypes = TTuple < FVector4f, FVector3f, FVector2f, float, int32, bool, FName, FTransform >;` — List of attribute types which are supported. IMPORTANT NOTE: Do not reorder or remove any type from this tuple, or serialization will fail. Types may be added at the end of this list as required.
- L222 _function_ `template <typename T> inline typename TEnableIf<!TIsBulkSerializable<T>::Value, FArchive>::Type& operator<<( FArchive& Ar, TMeshAttributeArrayBase<T>& Array )`
- L260 _function_ `template <> inline TEnableIf<!TIsBulkSerializable<FName>::Value, FArchive>::Type& operator<<( FArchive& Ar, TMeshAttributeArrayBase<FName>& Array )`
- L449 _function_ `template <typename T> inline typename TEnableIf<TIsBulkSerializable<T>::Value, FArchive>::Type& operator<<( FArchive& Ar, TMeshAttributeArrayBase<T>& Array )`
- L491 _prototype_ `ENUM_CLASS_FLAGS(EMeshAttributeFlags);`
- L738 _function_ `friend FArchive& operator<<(FArchive& Ar, TMeshAttributeArraySet& AttributeArraySet)` — Serializer
- L908 _function_ `friend FArchive& operator<<(FArchive& Ar, TMeshUnboundedAttributeArraySet& AttributeArraySet)` — Serializer
- L1012 _typedef_ `template <typename ElementIDType, typename AttributeType> using TMeshAttributesConstRef = TMeshAttributesRef<ElementIDType, typename TMeshAttributesRefType<AttributeType>::ConstRefType>;`
- L1015 _typedef_ `template <typename AttributeType> using TMeshAttributesArray = TMeshAttributesRef<int32, AttributeType>;`
- L1018 _typedef_ `template <typename AttributeType> using TMeshAttributesConstArray = TMeshAttributesRef<int32, typename TMeshAttributesRefType<AttributeType>::ConstRefType>;`
- L1772 _typedef_ `using AttributeType = typename TMeshAttributesRegisterType<T>::AttributeType;` (scope `FAttributesSetBase::RegisterAttributeInternal`)
- L1773 _typedef_ `using RealAttributeType = typename TMeshAttributesRegisterType<T>::RealAttributeType;` (scope `FAttributesSetBase::RegisterAttributeInternal`)
- L1774 _typedef_ `using RefType = typename TMeshAttributesRegisterType<T>::RefType;` (scope `FAttributesSetBase::RegisterAttributeInternal`)
- L1865 _typedef_ `using RealAttributeType = typename TMeshAttributesRefType<T>::RealAttributeType;` (scope `FAttributesSetBase::HasAttributeOfType`)
- L1996 _typedef_ `using RefType = typename TMeshAttributesRefType<T>::ConstRefType;` (scope `FAttributesSetBase::GetAttributesRef`)
- L2000 _typedef_ `using AttributeType = typename TMeshAttributesRefType<T>::AttributeType;` (scope `FAttributesSetBase::GetAttributesRef`)
- L2001 _typedef_ `using RealAttributeType = typename TMeshAttributesRefType<T>::RealAttributeType;` (scope `FAttributesSetBase::GetAttributesRef`)
- L2019 _typedef_ `using RefType = typename TMeshAttributesRefType<T>::RefType;` (scope `FAttributesSetBase::GetAttributesRef`)
- L2086 _typedef_ `using RefType = typename TMeshAttributesRefType<T>::ConstRefType;` (scope `TAttributesSet::GetAttributesRef`)
- L2090 _typedef_ `using AttributeType = typename TMeshAttributesRefType<T>::AttributeType;` (scope `TAttributesSet::GetAttributesRef`)
- L2091 _typedef_ `using RealAttributeType = typename TMeshAttributesRefType<T>::RealAttributeType;` (scope `TAttributesSet::GetAttributesRef`)
- L2110 _typedef_ `using RefType = typename TMeshAttributesRefType<T>::RefType;` (scope `TAttributesSet::GetAttributesRef`)
- L2156 _typedef_ `using ArrayType = TMeshAttributeArraySet<AttributeType>;` (scope `TAttributesSet::GetAttributeIndexCount`)
- L2187 _typedef_ `using ArrayType = TMeshAttributeArraySet<AttributeType>;` (scope `TAttributesSet::SetAttributeIndexCount`)
- L2216 _typedef_ `using ArrayType = TMeshAttributeArraySet<AttributeType>;` (scope `TAttributesSet::InsertAttributeIndex`)
- L2245 _typedef_ `using ArrayType = TMeshAttributeArraySet<AttributeType>;` (scope `TAttributesSet::RemoveAttributeIndex`)
- L2258 _typedef_ `using RefType = typename TMeshAttributesRefType<T>::ConstRefType;` (scope `TAttributesSet::GetAttribute`)
- L2259 _typedef_ `using AttributeType = typename TMeshAttributesRefType<T>::AttributeType;` (scope `TAttributesSet::GetAttribute`)
- L2260 _typedef_ `using RealAttributeType = typename TMeshAttributesRefType<T>::RealAttributeType;` (scope `TAttributesSet::GetAttribute`)
- L2279 _typedef_ `using NonConstRefType = typename TMeshAttributesRefType<T>::NonConstRefType;` (scope `TAttributesSet::SetAttribute`)
- L2280 _typedef_ `using AttributeType = typename TMeshAttributesRefType<T>::AttributeType;` (scope `TAttributesSet::SetAttribute`)
- L2281 _typedef_ `using RealAttributeType = typename TMeshAttributesRefType<T>::RealAttributeType;` (scope `TAttributesSet::SetAttribute`)
- L2383 _namespace_ `namespace ForEachImpl`
- L2387 _typedef_ `template <typename ElementIDType, typename ForEachFunc> using JumpTableType = TJumpTable<void(FName, ForEachFunc, FMeshAttributeArraySetBase*), TTupleArity<AttributeTypes>::Value>;` (scope `ForEachImpl`) — Declare type of jump table used to dispatch functions
- L2391 _function_ `template <typename ElementIDType, typename ForEachFunc, uint32 I> static void Dispatch(FName Name, ForEachFunc Fn, FMeshAttributeArraySetBase* Attributes)` (scope `ForEachImpl`) — Define dispatch function
- L2393 _typedef_ `using AttributeType = typename TTupleElement<I, AttributeTypes>::Type;` (scope `ForEachImpl::Dispatch`)
- L2410 _function_ `template <typename ElementIDType, typename ForEachFunc, uint32... Is> static constexpr JumpTableType<ElementIDType, ForEachFunc> MakeJumpTable(TIntegerSequence< uint32, Is...>)` (scope `ForEachImpl`) — Build ForEach jump table at compile time, a separate instantiation of Dispatch for each attribute type
- L2432 _namespace_ `namespace ForEachConstImpl`
- L2436 _typedef_ `template <typename ElementIDType, typename ForEachFunc> using JumpTableType = TJumpTable<void(FName, ForEachFunc, const FMeshAttributeArraySetBase*), TTupleArity<AttributeTypes>::Value>;` (scope `ForEachConstImpl`) — Declare type of jump table used to dispatch functions
- L2440 _function_ `template <typename ElementIDType, typename ForEachFunc, uint32 I> static void Dispatch(FName Name, ForEachFunc Fn, const FMeshAttributeArraySetBase* Attributes)` (scope `ForEachConstImpl`) — Define dispatch function
- L2442 _typedef_ `using AttributeType = typename TTupleElement<I, AttributeTypes>::Type;` (scope `ForEachConstImpl::Dispatch`)
- L2459 _function_ `template <typename ElementIDType, typename ForEachFunc, uint32... Is> static constexpr JumpTableType<ElementIDType, ForEachFunc> MakeJumpTable(TIntegerSequence< uint32, Is...>)` (scope `ForEachConstImpl`) — Build ForEach jump table at compile time, a separate instantiation of Dispatch for each attribute type
- L2481 _namespace_ `namespace ForEachByTypeImpl`
- L2582 _namespace_ `namespace CreateTypeImpl`
- L2585 _typedef_ `using JumpTableType = TJumpTable<TUniquePtr<FMeshAttributeArraySetBase>(uint32), TTupleArity<AttributeTypes>::Value>;` (scope `CreateTypeImpl`) — Declare type of jump table used to dispatch functions
- L2589 _function_ `template <uint32 I> static TUniquePtr<FMeshAttributeArraySetBase> Dispatch(uint32 Extent)` (scope `CreateTypeImpl`) — Define dispatch function
- L2591 _typedef_ `using AttributeType = typename TTupleElement<I, AttributeTypes>::Type;` (scope `CreateTypeImpl::Dispatch`)
- L2604 _function_ `template <uint32... Is> static constexpr JumpTableType MakeJumpTable(TIntegerSequence< uint32, Is...>)` (scope `CreateTypeImpl`) — Build RegisterAttributeOfType jump table at compile time, a separate instantiation of Dispatch for each attribute type

### `Source/Runtime/MeshDescription/Public/MeshAttributes.h` (Public)


#### class `FMeshAttributes`  
`class FMeshAttributes`  
_L58-197_
- L61 _public function_ `explicit FMeshAttributes(FMeshDescription& InMeshDescription) : MeshDescription(InMeshDescription)`
- L65 _public prototype_ `virtual ~FMeshAttributes() = default;`
- L67 _public prototype_ `virtual void Register(bool bKeepExistingAttribute = false);`
- L69 _public function_ `static bool IsReservedAttributeName(const FName InAttributeName)`
- L85 _public function_ `TVertexAttributesRef<FVector3f> GetVertexPositions()` — Accessors for cached vertex position array
- L90 _public function_ `TVertexAttributesConstRef<FVector3f> GetVertexPositions() const`
- L96 _public function_ `TVertexInstanceAttributesRef<FVertexID> GetVertexInstanceVertexIndices()` — Accessors for array of vertex IDs for vertex instances
- L101 _public function_ `TVertexInstanceAttributesConstRef<FVertexID> GetVertexInstanceVertexIndices() const`
- L107 _public function_ `TEdgeAttributesRef<TArrayView<FVertexID>> GetEdgeVertexIndices()` — Accessors for array of vertex IDs for edges
- L112 _public function_ `TEdgeAttributesConstRef<TArrayView<FVertexID>> GetEdgeVertexIndices() const`
- L118 _public function_ `TTriangleAttributesRef<TArrayView<FVertexInstanceID>> GetTriangleVertexInstanceIndices()` — Accessors for array of vertex instance IDs for triangles
- L123 _public function_ `TTriangleAttributesConstRef<TArrayView<FVertexInstanceID>> GetTriangleVertexInstanceIndices() const`
- L129 _public function_ `TTriangleAttributesRef<TArrayView<FEdgeID>> GetTriangleEdgeIndices()` — Accessors for array of edge IDs for triangles
- L134 _public function_ `TTriangleAttributesConstRef<TArrayView<FEdgeID>> GetTriangleEdgeIndices() const`
- L140 _public function_ `TTriangleAttributesRef<TArrayView<FVertexID>> GetTriangleVertexIndices()` — Accessors for array of vertex IDs for triangles
- L145 _public function_ `TTriangleAttributesConstRef<TArrayView<FVertexID>> GetTriangleVertexIndices() const`
- L151 _public function_ `TTriangleAttributesRef<TArrayView<FUVID>> GetTriangleUVIndices()` — Accessors for array of UV IDs for triangles
- L156 _public function_ `TTriangleAttributesConstRef<TArrayView<FUVID>> GetTriangleUVIndices() const`
- L162 _public function_ `TUVAttributesRef<FVector2f> GetUVCoordinates(int32 UVChannel)` — Accessors for UV coordinates
- L167 _public function_ `TUVAttributesConstRef<FVector2f> GetUVCoordinates(int32 UVChannel) const`
- L173 _public function_ `TTriangleAttributesRef<FPolygonGroupID> GetTrianglePolygonGroupIndices()` — Accessors for array of polygon group IDs for triangles
- L178 _public function_ `TTriangleAttributesConstRef<FPolygonGroupID> GetTrianglePolygonGroupIndices() const`
- L184 _public function_ `TPolygonAttributesRef<FPolygonGroupID> GetPolygonPolygonGroupIndices()` — Accessors for array of polygon group IDs for polygons
- L189 _public function_ `TPolygonAttributesConstRef<FPolygonGroupID> GetPolygonPolygonGroupIndices() const`
- L196 _protected member_ `FMeshDescription& MeshDescription;`

#### class `FMeshConstAttributes`  
`class FMeshConstAttributes`  
_L200-267_
- L203 _public function_ `explicit FMeshConstAttributes(const FMeshDescription& InMeshDescription) : MeshDescription(InMeshDescription)`
- L208 _public function_ `TVertexAttributesConstRef<FVector3f> GetVertexPositions() const` — Accessors for cached vertex position array
- L211 _public function_ `TVertexInstanceAttributesConstRef<FVertexID> GetVertexInstanceVertexIndices() const` — Accessors for array of vertex IDs for vertex instances
- L217 _public function_ `TEdgeAttributesConstRef<TArrayView<FVertexID>> GetEdgeVertexIndices() const` — Accessors for array of vertex IDs for edges
- L223 _public function_ `TTriangleAttributesConstRef<TArrayView<FVertexInstanceID>> GetTriangleVertexInstanceIndices() const` — Accessors for array of vertex instance IDs for triangles
- L229 _public function_ `TTriangleAttributesConstRef<TArrayView<FEdgeID>> GetTriangleEdgeIndices() const` — Accessors for array of edge IDs for triangles
- L235 _public function_ `TTriangleAttributesConstRef<TArrayView<FVertexID>> GetTriangleVertexIndices() const` — Accessors for array of vertex IDs for triangles
- L241 _public function_ `TTriangleAttributesConstRef<TArrayView<FUVID>> GetTriangleUVIndices() const` — Accessors for array of UV IDs for triangles
- L247 _public function_ `TUVAttributesConstRef<FVector2f> GetUVCoordinates(int32 UVChannel) const` — Accessors for UV coordinates
- L253 _public function_ `TTriangleAttributesConstRef<FPolygonGroupID> GetTrianglePolygonGroupIndices() const` — Accessors for array of polygon group IDs for triangles
- L259 _public function_ `TPolygonAttributesConstRef<FPolygonGroupID> GetPolygonPolygonGroupIndices() const` — Accessors for array of polygon group IDs for polygons
- L266 _protected member_ `const FMeshDescription& MeshDescription;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace MeshAttribute`
- L21 _namespace_ `namespace Vertex` (scope `MeshAttribute`)
- L23 _externvar_ `extern const FName Position;` (scope `MeshAttribute::Vertex`)
- L26 _namespace_ `namespace VertexInstance` (scope `MeshAttribute`)
- L28 _externvar_ `extern const FName VertexIndex;` (scope `MeshAttribute::VertexInstance`)
- L31 _namespace_ `namespace Edge` (scope `MeshAttribute`)
- L33 _externvar_ `extern const FName VertexIndex;` (scope `MeshAttribute::Edge`)
- L36 _namespace_ `namespace Triangle` (scope `MeshAttribute`)
- L38 _externvar_ `extern const FName VertexInstanceIndex;` (scope `MeshAttribute::Triangle`)
- L39 _externvar_ `extern const FName PolygonIndex;` (scope `MeshAttribute::Triangle`)
- L40 _externvar_ `extern const FName EdgeIndex;` (scope `MeshAttribute::Triangle`)
- L41 _externvar_ `extern const FName VertexIndex;` (scope `MeshAttribute::Triangle`)
- L42 _externvar_ `extern const FName UVIndex;` (scope `MeshAttribute::Triangle`)
- L43 _externvar_ `extern const FName PolygonGroupIndex;` (scope `MeshAttribute::Triangle`)
- L46 _namespace_ `namespace UV` (scope `MeshAttribute`)
- L48 _externvar_ `extern const FName UVCoordinate;` (scope `MeshAttribute::UV`)
- L51 _namespace_ `namespace Polygon` (scope `MeshAttribute`)
- L53 _externvar_ `extern const FName PolygonGroupIndex;` (scope `MeshAttribute::Polygon`)

### `Source/Runtime/MeshDescription/Public/MeshDescription.h` (Public)


#### enum `(anonymous)`  
``  
_L50-53_

#### enum `EComputeNTBsOptions`  
`enum class EComputeNTBsOptions : uint32`  
_L83-89_
- reflection: `UENUM()`
- L85 _public enumerator_ `None = 0x00000000` — No flags
- L86 _public enumerator_ `Normals = 0x00000001` — Compute the normals
- L87 _public enumerator_ `Tangents = 0x00000002` — Compute the tangents
- L88 _public enumerator_ `WeightedNTBs = 0x00000004` — Use weight angle when computing NTBs to proportionally distribute the vertex instance contribution to the normal/tangent/binormal in a smooth group.    i.e. Weight solve the cylinder problem

#### struct `FMeshDescription`  
`struct FMeshDescription`  
_L93-1321_
- L99 _public prototype_ `FMeshDescription();` — Mesh description should be a moveable type. Hence explicitly declare all the below as defaulted, to ensure they will be generated by the compiler.
- L100 _public prototype_ `~FMeshDescription() = default;`
- L101 _public prototype_ `FMeshDescription(const FMeshDescription&);`
- L102 _public prototype_ `FMeshDescription& operator=(const FMeshDescription&);`
- L103 _public prototype_ `FMeshDescription(FMeshDescription&&) = default;`
- L104 _public prototype_ `FMeshDescription& operator=(FMeshDescription&&) = default;`
- L112 _public prototype_ `static TConstArrayView<TPair<FGuid, int32>> GetSerializationFormatVersions();`
- L115 _public prototype_ `void Serialize(FArchive& Ar);` — Serialize the mesh description
- L118 _public prototype_ `void SerializeLegacy(FArchive& Ar);` — Legacy serialization for old assets
- L121 _public prototype_ `void Empty();` — Empty the meshdescription
- L124 _public prototype_ `void ResetIndexers();` — Operations on all the indexers
- L125 _public prototype_ `void BuildIndexers();`
- L126 _public prototype_ `void RebuildIndexers();`
- L129 _public prototype_ `bool IsEmpty() const;` — Return whether the mesh description is empty
- L131 _public function_ `FVertexArray& Vertices()`
- L132 _public function_ `const FVertexArray& Vertices() const`
- L134 _public function_ `FVertexInstanceArray& VertexInstances()`
- L135 _public function_ `const FVertexInstanceArray& VertexInstances() const`
- L137 _public function_ `FEdgeArray& Edges()`
- L138 _public function_ `const FEdgeArray& Edges() const`
- L140 _public function_ `FUVArray& UVs(int32 Index)`
- L141 _public function_ `const FUVArray& UVs(int32 Index) const`
- L143 _public function_ `FTriangleArray& Triangles()`
- L144 _public function_ `const FTriangleArray& Triangles() const`
- L146 _public function_ `FPolygonArray& Polygons()`
- L147 _public function_ `const FPolygonArray& Polygons() const`
- L149 _public function_ `FPolygonGroupArray& PolygonGroups()`
- L150 _public function_ `const FPolygonGroupArray& PolygonGroups() const`
- L152 _public function_ `TAttributesSet<FVertexID>& VertexAttributes()`
- L153 _public function_ `const TAttributesSet<FVertexID>& VertexAttributes() const`
- L155 _public function_ `TAttributesSet<FVertexInstanceID>& VertexInstanceAttributes()`
- L156 _public function_ `const TAttributesSet<FVertexInstanceID>& VertexInstanceAttributes() const`
- L158 _public function_ `TAttributesSet<FEdgeID>& EdgeAttributes()`
- L159 _public function_ `const TAttributesSet<FEdgeID>& EdgeAttributes() const`
- L161 _public function_ `TAttributesSet<FUVID>& UVAttributes(int32 Index)`
- L162 _public function_ `const TAttributesSet<FUVID>& UVAttributes(int32 Index) const`
- L164 _public function_ `TAttributesSet<FTriangleID>& TriangleAttributes()`
- L165 _public function_ `const TAttributesSet<FTriangleID>& TriangleAttributes() const`
- L167 _public function_ `TAttributesSet<FPolygonID>& PolygonAttributes()`
- L168 _public function_ `const TAttributesSet<FPolygonID>& PolygonAttributes() const`
- L170 _public function_ `TAttributesSet<FPolygonGroupID>& PolygonGroupAttributes()`
- L171 _public function_ `const TAttributesSet<FPolygonGroupID>& PolygonGroupAttributes() const`
- L173 _public function_ `TMap<FName, FMeshElementTypeWrapper>& GetElements()`
- L174 _public function_ `const TMap<FName, FMeshElementTypeWrapper>& GetElements() const`
- L176 _public function_ `void SuspendVertexIndexing()`
- L177 _public function_ `void SuspendVertexInstanceIndexing()`
- L178 _public function_ `void SuspendEdgeIndexing()`
- L179 _public function_ `void SuspendPolygonIndexing()`
- L180 _public function_ `void SuspendPolygonGroupIndexing()`
- L181 _public function_ `void SuspendUVIndexing()`
- L183 _public function_ `void ResumeVertexIndexing()`
- L184 _public function_ `void ResumeVertexInstanceIndexing()`
- L185 _public function_ `void ResumeEdgeIndexing()`
- L186 _public function_ `void ResumePolygonIndexing()`
- L187 _public function_ `void ResumePolygonGroupIndexing()`
- L188 _public function_ `void ResumeUVIndexing()`
- L190 _public function_ `void BuildVertexIndexers()`
- L191 _public function_ `void BuildVertexInstanceIndexers()`
- L192 _public function_ `void BuildEdgeIndexers()`
- L193 _public function_ `void BuildPolygonIndexers()`
- L194 _public function_ `void BuildPolygonGroupIndexers()`
- L200 _public function_ `void ReserveNewVertices(const int32 NumVertices)` — Reserves space for this number of new vertices
- L206 _public function_ `FVertexID CreateVertex()` — Adds a new vertex to the mesh and returns its ID
- L213 _public function_ `void CreateVertexWithID(const FVertexID VertexID)` — Adds a new vertex to the mesh with the given ID
- L219 _public function_ `void DeleteVertex(const FVertexID VertexID)` — Deletes a vertex from the mesh
- L229 _public function_ `bool IsVertexValid(const FVertexID VertexID) const` — Returns whether the passed vertex ID is valid
- L235 _public function_ `void ReserveNewVertexInstances(const int32 NumVertexInstances)` — Reserves space for this number of new vertex instances
- L241 _public function_ `FVertexInstanceID CreateVertexInstance(const FVertexID VertexID)` — Adds a new vertex instance to the mesh and returns its ID
- L249 _public function_ `void CreateVertexInstanceWithID(const FVertexInstanceID VertexInstanceID, const FVertexID VertexID)` — Adds a new vertex instance to the mesh with the given ID
- L256 _public prototype_ `void DeleteVertexInstance(const FVertexInstanceID VertexInstanceID, TArray<FVertexID>* InOutOrphanedVerticesPtr = nullptr);` — Deletes a vertex instance from a mesh
- L259 _public function_ `bool IsVertexInstanceValid(const FVertexInstanceID VertexInstanceID) const` — Returns whether the passed vertex instance ID is valid
- L265 _public function_ `void ReserveNewUVs(const int32 NumUVs, const int32 UVChannel = 0)` — Reserves space for this number of new UVs
- L271 _public function_ `FUVID CreateUV(const int32 UVChannel = 0)` — Adds a new UV to the mesh and returns its ID
- L278 _public function_ `void CreateUVWithID(const FUVID UVID, const int32 UVChannel = 0)` — Adds a new UV to the mesh with the given ID
- L284 _public function_ `void DeleteUV(const FUVID UVID, const int32 UVChannel = 0)` — Deletes a UV from the mesh
- L292 _public function_ `bool IsUVValid(const FUVID UVID, const int32 UVChannel = 0) const` — Returns whether the passed UV ID is valid
- L298 _public function_ `void ReserveNewEdges(const int32 NumEdges)` — Reserves space for this number of new edges
- L304 _public function_ `FEdgeID CreateEdge(const FVertexID VertexID0, const FVertexID VertexID1)` — Adds a new edge to the mesh and returns its ID
- L312 _public function_ `void CreateEdgeWithID(const FEdgeID EdgeID, const FVertexID VertexID0, const FVertexID VertexID1)` — Adds a new edge to the mesh with the given ID
- L319 _public prototype_ `void DeleteEdge(const FEdgeID EdgeID, TArray<FVertexID>* InOutOrphanedVerticesPtr = nullptr);` — Deletes an edge from the mesh
- L322 _public function_ `bool IsEdgeValid(const FEdgeID EdgeID) const` — Returns whether the passed edge ID is valid
- L328 _public function_ `void ReserveNewTriangles(const int32 NumTriangles)` — Reserves space for this number of new triangles
- L334 _public function_ `FTriangleID CreateTriangle(const FPolygonGroupID PolygonGroupID, TArrayView<const FVertexInstanceID> VertexInstanceIDs, TArray<FEdgeID>* OutEdgeIDs = nullptr)` — Adds a new triangle to the mesh and returns its ID. This will also make an encapsulating polygon, and any missing edges.
- L342 _public function_ `void CreateTriangleWithID(const FTriangleID TriangleID, const FPolygonGroupID PolygonGroupID, TArrayView<const FVertexInstanceID> VertexInstanceIDs, TArray<FEdgeID>* OutEdgeIDs = nullptr)` — Adds a new triangle to the mesh with the given ID. This will also make an encapsulating polygon, and any missing edges.
- L349 _public prototype_ `void DeleteTriangle(const FTriangleID TriangleID, TArray<FEdgeID>* InOutOrphanedEdgesPtr = nullptr, TArray<FVertexInstanceID>* InOutOrphanedVertexInstancesPtr = nullptr, TArray<FPolygonGroupID>* InOutOrphanedPolygonGroupsPtr = nullptr);` — Deletes a triangle from the mesh
- L354 _public prototype_ `void DeleteTriangles(const TArray<FTriangleID>& Triangles);` — Deletes triangles from the mesh and remove all orphaned polygon groups, vertex instances, edges and vertices. Will not compact the internal arrays, you must call Compact() manually.
- L357 _public function_ `bool IsTriangleValid(const FTriangleID TriangleID) const` — Returns whether the passed triangle ID is valid
- L363 _public function_ `void ReserveNewPolygons(const int32 NumPolygons)` — Reserves space for this number of new polygons
- L369 _public function_ `FPolygonID CreatePolygon(const FPolygonGroupID PolygonGroupID, TArrayView<const FVertexInstanceID> VertexInstanceIDs, TArray<FEdgeID>* OutEdgeIDs = nullptr)` — Adds a new polygon to the mesh and returns its ID. This will also make any missing edges, and all constituent triangles.
- L377 _public function_ `void CreatePolygonWithID(const FPolygonID PolygonID, const FPolygonGroupID PolygonGroupID, TArrayView<const FVertexInstanceID> VertexInstanceIDs, TArray<FEdgeID>* OutEdgeIDs = nullptr)` — Adds a new polygon to the mesh with the given ID. This will also make any missing edges, and all constituent triangles.
- L384 _public prototype_ `void DeletePolygon(const FPolygonID PolygonID, TArray<FEdgeID>* InOutOrphanedEdgesPtr = nullptr, TArray<FVertexInstanceID>* InOutOrphanedVertexInstancesPtr = nullptr, TArray<FPolygonGroupID>* InOutOrphanedPolygonGroupsPtr = nullptr);` — Deletes a polygon from the mesh
- L389 _public prototype_ `void DeletePolygons(const TArray<FPolygonID>& Polygons);` — Deletes polygons from the mesh and remove all orphaned polygon groups, vertex instances, edges and vertices. Will not compact the internal arrays, you must call Compact() manually.
- L392 _public function_ `bool IsPolygonValid(const FPolygonID PolygonID) const` — Returns whether the passed polygon ID is valid
- L398 _public function_ `void ReserveNewPolygonGroups(const int32 NumPolygonGroups)` — Reserves space for this number of new polygon groups
- L404 _public function_ `FPolygonGroupID CreatePolygonGroup()` — Adds a new polygon group to the mesh and returns its ID
- L411 _public function_ `void CreatePolygonGroupWithID(const FPolygonGroupID PolygonGroupID)` — Adds a new polygon group to the mesh with the given ID
- L417 _public function_ `void DeletePolygonGroup(const FPolygonGroupID PolygonGroupID)` — Deletes a polygon group from the mesh
- L426 _public function_ `bool IsPolygonGroupValid(const FPolygonGroupID PolygonGroupID) const` — Returns whether the passed polygon group ID is valid
- L441 _public prototype_ `bool IsVertexOrphaned(const FVertexID VertexID) const;` — Returns whether a given vertex is orphaned, i.e. it doesn't form part of any polygon
- L444 _public prototype_ `FEdgeID GetVertexPairEdge(const FVertexID VertexID0, const FVertexID VertexID1) const;` — Returns the edge ID defined by the two given vertex IDs, if there is one; otherwise INDEX_NONE
- L447 _public function_ `TArrayView<const FEdgeID> GetVertexConnectedEdgeIDs(const FVertexID VertexID) const` — Returns reference to an array of Edge IDs connected to this vertex
- L453 _public function_ `TArray<FEdgeID> GetVertexConnectedEdges(const FVertexID VertexID) const` — `UE_DEPRECATED(4.26, "Please use GetVertexConnectedEdgeIDs instead.")`
- L459 _public function_ `int32 GetNumVertexConnectedEdges(const FVertexID VertexID) const` — Returns number of edges connected to this vertex
- L465 _public function_ `TArrayView<const FVertexInstanceID> GetVertexVertexInstanceIDs(const FVertexID VertexID) const` — Returns reference to an array of VertexInstance IDs instanced from this vertex
- L471 _public function_ `TArray<FVertexInstanceID> GetVertexVertexInstances(const FVertexID VertexID) const` — `UE_DEPRECATED(4.26, "Please use GetVertexVertexInstanceIDs instead.")`
- L477 _public function_ `int32 GetNumVertexVertexInstances(const FVertexID VertexID) const` — Returns number of vertex instances created from this vertex
- L484 _public function_ `template <typename Alloc> void GetVertexConnectedTriangles(const FVertexID VertexID, TArray<FTriangleID, Alloc>& OutConnectedTriangleIDs) const` — Populates the passed array of TriangleIDs with the triangles connected to this vertex
- L496 _public function_ `template <typename Alloc> TArray<FTriangleID, Alloc> GetVertexConnectedTriangles(const FVertexID VertexID) const` — Returns the triangles connected to this vertex as an array with the specified allocator template type.
- L504 _public function_ `TArray<FTriangleID> GetVertexConnectedTriangles(const FVertexID VertexID) const` — Returns the triangles connected to this vertex
- L512 _public function_ `int32 GetNumVertexConnectedTriangles(const FVertexID VertexID) const` — Returns number of triangles connected to this vertex
- L522 _public function_ `template <typename Alloc> void GetVertexConnectedPolygons(const FVertexID VertexID, TArray<FPolygonID, Alloc>& OutConnectedPolygonIDs) const` — Populates the passed array of PolygonIDs with the polygons connected to this vertex
- L536 _public function_ `template <typename Alloc> TArray<FPolygonID, Alloc> GetVertexConnectedPolygons(const FVertexID VertexID) const` — Returns the polygons connected to this vertex as an array with the specified allocator template type.
- L544 _public function_ `TArray<FPolygonID> GetVertexConnectedPolygons(const FVertexID VertexID) const` — Returns the polygons connected to this vertex
- L552 _public function_ `int32 GetNumVertexConnectedPolygons(const FVertexID VertexID) const` — Returns the number of polygons connected to this vertex
- L559 _public function_ `template <typename Alloc> void GetVertexAdjacentVertices(const FVertexID VertexID, TArray<FVertexID, Alloc>& OutAdjacentVertexIDs) const` — Populates the passed array of VertexIDs with the vertices adjacent to this vertex
- L575 _public function_ `template <typename Alloc> TArray<FVertexID, Alloc> GetVertexAdjacentVertices(const FVertexID VertexID) const` — Returns the vertices adjacent to this vertex as an array with the specified allocator template type.
- L583 _public function_ `TArray<FVertexID> GetVertexAdjacentVertices(const FVertexID VertexID) const` — Returns the vertices adjacent to this vertex
- L591 _public function_ `FVector3f GetVertexPosition(const FVertexID VertexID) const` — Returns the position of this vertex
- L596 _public function_ `TVertexAttributesRef<FVector3f> GetVertexPositions()`
- L601 _public function_ `TVertexAttributesRef<const FVector3f> GetVertexPositions() const`
- L610 _public function_ `FVertexID GetVertexInstanceVertex(const FVertexInstanceID VertexInstanceID) const` — Returns the vertex ID associated with the given vertex instance
- L616 _public prototype_ `FEdgeID GetVertexInstancePairEdge(const FVertexInstanceID VertexInstanceID0, const FVertexInstanceID VertexInstanceID1) const;` — Returns the edge ID defined by the two given vertex instance IDs, if there is one; otherwise INDEX_NONE
- L619 _public function_ `TArrayView<const FTriangleID> GetVertexInstanceConnectedTriangleIDs(const FVertexInstanceID VertexInstanceID) const` — Returns reference to an array of Triangle IDs connected to this vertex instance
- L625 _public function_ `TArray<FTriangleID> GetVertexInstanceConnectedTriangles(const FVertexInstanceID VertexInstanceID) const` — `UE_DEPRECATED(4.26, "Please use GetVertexInstanceTriangleIDs() instead.")`
- L631 _public function_ `int32 GetNumVertexInstanceConnectedTriangles(const FVertexInstanceID VertexInstanceID) const` — Returns the number of triangles connected to this vertex instance
- L638 _public function_ `template <typename Alloc> void GetVertexInstanceConnectedPolygons(const FVertexInstanceID VertexInstanceID, TArray<FPolygonID, Alloc>& OutPolygonIDs) const` — Populates the passed array with the polygons connected to this vertex instance
- L649 _public function_ `template <typename Alloc> TArray<FPolygonID, Alloc> GetVertexInstanceConnectedPolygons(const FVertexInstanceID VertexInstanceID) const` — Returns the polygons connected to this vertex instance as an array with the specified allocator template type.
- L657 _public function_ `TArray<FPolygonID> GetVertexInstanceConnectedPolygons(const FVertexInstanceID VertexInstanceID) const` — Returns the polygons connected to this vertex instance
- L665 _public function_ `int32 GetNumVertexInstanceConnectedPolygons(const FVertexInstanceID VertexInstanceID) const` — Returns the number of polygons connected to this vertex instance.
- L675 _public function_ `bool IsEdgeInternal(const FEdgeID EdgeID) const` — Determine whether a given edge is an internal edge between triangles of a polygon
- L683 _public function_ `bool IsEdgeInternalToPolygon(const FEdgeID EdgeID, const FPolygonID PolygonID) const` — Determine whether a given edge is an internal edge between triangles of a specific polygon
- L692 _public function_ `TArrayView<const FTriangleID> GetEdgeConnectedTriangleIDs(const FEdgeID EdgeID) const` — Returns reference to an array of triangle IDs connected to this edge
- L698 _public function_ `TArray<FTriangleID> GetEdgeConnectedTriangles(const FEdgeID EdgeID) const` — `UE_DEPRECATED(4.26, "Please use GetEdgeConnectedTriangleIDs() instead.")`
- L703 _public function_ `int32 GetNumEdgeConnectedTriangles(const FEdgeID EdgeID) const`
- L710 _public function_ `template <typename Alloc> void GetEdgeConnectedPolygons(const FEdgeID EdgeID, TArray<FPolygonID, Alloc>& OutPolygonIDs) const` — Populates the passed array with polygon IDs connected to this edge
- L721 _public function_ `template <typename Alloc> TArray<FPolygonID, Alloc> GetEdgeConnectedPolygons(const FEdgeID EdgeID) const` — Returns the polygons connected to this edge as an array with the specified allocator template type.
- L729 _public function_ `TArray<FPolygonID> GetEdgeConnectedPolygons(const FEdgeID EdgeID) const` — Returns the polygons connected to this edge
- L737 _public function_ `int32 GetNumEdgeConnectedPolygons(const FEdgeID EdgeID) const` — Returns the number of polygons connected to this edge
- L743 _public function_ `FVertexID GetEdgeVertex(const FEdgeID EdgeID, int32 VertexNumber) const` — Returns the vertex ID corresponding to one of the edge endpoints
- L751 _public function_ `TArrayView<const FVertexID> GetEdgeVertices(const FEdgeID EdgeID) const` — Returns a pair of vertex IDs defining the edge
- L761 _public function_ `FPolygonID GetTrianglePolygon(const FTriangleID TriangleID) const` — Get the polygon which contains this triangle
- L767 _public function_ `FPolygonGroupID GetTrianglePolygonGroup(const FTriangleID TriangleID) const` — Get the polygon group which contains this triangle
- L773 _public function_ `bool IsTrianglePartOfNgon(const FTriangleID TriangleID) const` — Determines if this triangle is part of an n-gon
- L779 _public function_ `TArrayView<const FVertexInstanceID> GetTriangleVertexInstances(const FTriangleID TriangleID) const` — Get the vertex instances which define this triangle
- L785 _public function_ `FVertexInstanceID GetTriangleVertexInstance(const FTriangleID TriangleID, const int32 Index) const` — Get the specified vertex instance by index
- L794 _public function_ `void GetTriangleVertices(const FTriangleID TriangleID, TArrayView<FVertexID> OutVertexIDs) const` — `UE_DEPRECATED(4.26, "Use the other form of GetTriangleVertices")` — Populates the passed array with the vertices which define this triangle
- L805 _public function_ `TArrayView<const FVertexID> GetTriangleVertices(const FTriangleID TriangleID) const` — Return the vertices which define this triangle
- L812 _public function_ `void GetTriangleEdges(const FTriangleID TriangleID, TArrayView<FEdgeID> OutEdgeIDs) const` — `UE_DEPRECATED(4.26, "Use the other form of GetTriangleEdges")` — Populates the passed array with the edges which define this triangle
- L823 _public function_ `TArrayView<FEdgeID> GetTriangleEdges(const FTriangleID TriangleID) const` — Return the edges which form this triangle
- L830 _public function_ `template <typename Alloc> void GetTriangleAdjacentTriangles(const FTriangleID TriangleID, TArray<FTriangleID, Alloc>& OutTriangleIDs) const` — Populates the passed array with adjacent triangles
- L848 _public function_ `template <typename Alloc> TArray<FTriangleID, Alloc> GetTriangleAdjacentTriangles(const FTriangleID TriangleID) const` — Return adjacent triangles into a TArray with the specified allocator
- L856 _public function_ `TArray<FTriangleID> GetTriangleAdjacentTriangles(const FTriangleID TriangleID) const` — Return adjacent triangles to this triangle
- L864 _public function_ `TArrayView<FUVID> GetTriangleUVIndices(const FTriangleID TriangleID, int32 UVChannel = 0) const` — Return UV indices for this triangle for the given channel
- L870 _public function_ `FVertexInstanceID GetVertexInstanceForTriangleVertex(const FTriangleID TriangleID, const FVertexID VertexID) const` — Return the vertex instance which corresponds to the given vertex on the given triangle, or INDEX_NONE
- L880 _public prototype_ `void ReverseTriangleFacing(const FTriangleID TriangleID);` — Reverse the winding order of the vertices of this triangle
- L883 _public prototype_ `void SetTriangleUVIndices(const FTriangleID TriangleID, TArrayView<const FUVID> UVIDs, int32 UVChannel = 0);` — Set the UV indices for this triangle
- L889 _public function_ `TArrayView<const FTriangleID> GetPolygonTriangles(const FPolygonID PolygonID) const` — Return reference to an array of triangle IDs which comprise this polygon
- L895 _public function_ `TArray<FTriangleID> GetPolygonTriangleIDs(const FPolygonID PolygonID) const` — `UE_DEPRECATED(4.26, "Please use GetPolygonTriangles() instead.")`
- L901 _public function_ `int32 GetNumPolygonTriangles(const FPolygonID PolygonID) const` — Return the number of triangles which comprise this polygon
- L908 _public function_ `template <typename Alloc> void GetPolygonVertexInstances(const FPolygonID PolygonID, TArray<FVertexInstanceID, Alloc>& OutVertexInstanceIDs) const` — Returns reference to an array of VertexInstance IDs forming the perimeter of this polygon
- L931 _public function_ `template <typename Alloc> TArray<FVertexInstanceID, Alloc> GetPolygonVertexInstances(const FPolygonID PolygonID) const`
- L938 _public function_ `TArray<FVertexInstanceID> GetPolygonVertexInstances(const FPolygonID PolygonID) const`
- L946 _public function_ `int32 GetNumPolygonVertices(const FPolygonID PolygonID) const` — Returns the number of vertices this polygon has
- L954 _public function_ `template <typename Alloc> void GetPolygonVertices(const FPolygonID PolygonID, TArray<FVertexID, Alloc>& OutVertexIDs) const` — Populates the passed array of VertexIDs with the vertices which form the polygon perimeter
- L978 _public function_ `template <typename Alloc> TArray<FVertexID, Alloc> GetPolygonVertices(const FPolygonID PolygonID) const` — Returns the vertices which form the polygon perimeter as an array templated on the given allocator
- L986 _public function_ `TArray<FVertexID> GetPolygonVertices(const FPolygonID PolygonID) const` — Returns the vertices which form the polygon perimeter
- L995 _public function_ `template <typename Alloc> void GetPolygonPerimeterEdges(const FPolygonID PolygonID, TArray<FEdgeID, Alloc>& OutEdgeIDs) const` — Populates the passed array with the edges which form the polygon perimeter
- L1019 _public function_ `template <typename Alloc> TArray<FEdgeID, Alloc> GetPolygonPerimeterEdges(const FPolygonID PolygonID) const` — Returns the vertices which form the polygon perimeter as an array templated on the given allocator
- L1027 _public function_ `TArray<FEdgeID> GetPolygonPerimeterEdges(const FPolygonID PolygonID) const` — Returns the vertices which form the polygon perimeter
- L1037 _public function_ `template <typename Alloc> void GetPolygonInternalEdges(const FPolygonID PolygonID, TArray<FEdgeID, Alloc>& OutEdgeIDs) const` — Populate the provided array with a list of edges which are internal to the polygon, i.e. those which separate constituent triangles.
- L1058 _public function_ `template <typename Alloc> TArray<FEdgeID, Alloc> GetPolygonInternalEdges(const FPolygonID PolygonID) const` — Return the internal edges of this polygon, i.e. those which separate constituent triangles
- L1066 _public function_ `TArray<FEdgeID> GetPolygonInternalEdges(const FPolygonID PolygonID) const` — Return the internal edges of this polygon, i.e. those which separate constituent triangles
- L1074 _public function_ `int32 GetNumPolygonInternalEdges(const FPolygonID PolygonID) const` — Return the number of internal edges in this polygon
- L1081 _public function_ `template <typename Alloc> void GetPolygonAdjacentPolygons(const FPolygonID PolygonID, TArray<FPolygonID, Alloc>& OutPolygonIDs) const` — Populates the passed array with adjacent polygons
- L1098 _public function_ `template <typename Alloc> TArray<FPolygonID, Alloc> GetPolygonAdjacentPolygons(const FPolygonID PolygonID) const` — Return adjacent polygons into a TArray with the specified allocator
- L1106 _public function_ `TArray<FPolygonID> GetPolygonAdjacentPolygons(const FPolygonID PolygonID) const` — Return adjacent polygons to this polygon
- L1114 _public function_ `FPolygonGroupID GetPolygonPolygonGroup(const FPolygonID PolygonID) const` — Return the polygon group associated with a polygon
- L1120 _public function_ `FVertexInstanceID GetVertexInstanceForPolygonVertex(const FPolygonID PolygonID, const FVertexID VertexID) const` — Return the vertex instance which corresponds to the given vertex on the given polygon, or INDEX_NONE
- L1130 _public prototype_ `void SetPolygonVertexInstance(const FPolygonID PolygonID, const int32 PerimeterIndex, const FVertexInstanceID VertexInstanceID);` — Set the vertex instance at the given index around the polygon to the new value
- L1131 _public prototype_ `void SetPolygonVertexInstances(const FPolygonID PolygonID, TArrayView<const FVertexInstanceID> VertexInstanceIDs);`
- L1134 _public function_ `void SetPolygonPolygonGroup(const FPolygonID PolygonID, const FPolygonGroupID PolygonGroupID)` — Sets the polygon group associated with a polygon
- L1154 _public prototype_ `void ReversePolygonFacing(const FPolygonID PolygonID);` — Reverse the winding order of the vertices of this polygon
- L1157 _public prototype_ `void FindPolygonPerimeter(TArrayView<const FTriangleID> Triangles, TArrayView<TTuple<int32, int32>> Result) const;` — Determines the vertex instances which form the perimeter of a polygon
- L1158 _public prototype_ `void FindPolygonPerimeter(const FPolygonID PolygonID, TArrayView<FEdgeID> Edges) const;`
- L1161 _public prototype_ `void ComputePolygonTriangulation(const FPolygonID PolygonID);` — Generates triangles and internal edges for the given polygon
- L1163 _public prototype_ `void SplitPolygon(FPolygonID PolygonID);`
- L1170 _public function_ `TArrayView<const FPolygonID> GetPolygonGroupPolygonIDs(const FPolygonGroupID PolygonGroupID) const` — Returns the polygons associated with the given polygon group
- L1176 _public function_ `TArray<FPolygonID> GetPolygonGroupPolygons(const FPolygonGroupID PolygonGroupID) const` — `UE_DEPRECATED(4.26, "Please use GetPolygonGroupPolygonIDs() instead.")`
- L1182 _public function_ `TArrayView<const FTriangleID> GetPolygonGroupTriangles(const FPolygonGroupID PolygonGroupID) const` — Returns the triangles associated with the given polygon group
- L1188 _public function_ `int32 GetNumPolygonGroupPolygons(const FPolygonGroupID PolygonGroupID) const` — Returns the number of polygons in this polygon group
- L1194 _public function_ `int32 GetNumPolygonGroupTriangles(const FPolygonGroupID PolygonGroupID) const` — Returns the number of triangles in this polygon group
- L1200 _public prototype_ `void RemapPolygonGroups(const TMap<FPolygonGroupID, FPolygonGroupID>& Remap);` — Remaps polygon groups according to the supplied map
- L1203 _public prototype_ `void TransferPolygonGroup(FPolygonGroupID SourceID, FPolygonGroupID DestinationID);` — Transfer the source polygon group data to the destination polygon group. The source data is append to the destination
- L1209 _public prototype_ `bool NeedsCompact() const;` — Determines if calling Compact() would perform actual compaction or not.
- L1212 _public prototype_ `void Compact( FElementIDRemappings& OutRemappings );` — Compacts the data held in the mesh description, and returns an object describing how the IDs have been remapped.
- L1215 _public prototype_ `void Remap( const FElementIDRemappings& Remappings );` — Remaps the element IDs in the mesh description according to the passed in object
- L1218 _public function_ `int32 GetNumUVElementChannels() const` — Gets the number of UV element channels
- L1221 _public prototype_ `void SetNumUVChannels(const int32 NumUVChannels);` — Sets the specified number of UV channels
- L1224 _public prototype_ `FBoxSphereBounds GetBounds() const;` — Returns bounds of vertices
- L1227 _public prototype_ `void TriangulateMesh();` — Retriangulates the entire mesh
- L1230 _public prototype_ `void ReverseAllPolygonFacing();` — Reverses the winding order of all polygons in the mesh
- L1232 _public prototype_ `float GetTriangleCornerAngleForVertex(const FTriangleID TriangleID, const FVertexID VertexID) const;`
- L1233 _public prototype_ `float GetPolygonCornerAngleForVertex(const FPolygonID PolygonID, const FVertexID VertexID) const;`
- L1235 _public prototype_ `FBox ComputeBoundingBox() const;`
- L1239 _private prototype_ `FPlane ComputePolygonPlane(TArrayView<const FVertexInstanceID> PerimeterVertexInstanceIDs) const;`
- L1240 _private prototype_ `FVector ComputePolygonNormal(TArrayView<const FVertexInstanceID> PerimeterVertexInstanceIDs) const;`
- L1244 _private prototype_ `void Initialize();`
- L1245 _private prototype_ `void InitializeIndexers();`
- L1246 _private prototype_ `void Cache();`
- L1248 _private prototype_ `void CreateVertexInstance_Internal(const FVertexInstanceID VertexInstanceID, const FVertexID VertexID);`
- L1249 _private prototype_ `void CreateEdge_Internal(const FEdgeID EdgeID, const FVertexID VertexID0, const FVertexID VertexID1);`
- L1250 _private prototype_ `void CreateTriangle_Internal(const FTriangleID TriangleID, const FPolygonGroupID PolygonGroupID, TArrayView<const FVertexInstanceID> VertexInstanceIDs, TArray<FEdgeID>* OutEdgeIDs);`
- L1251 _private prototype_ `void CreatePolygon_Internal(const FPolygonID PolygonID, const FPolygonGroupID PolygonGroupID, TArrayView<const FVertexInstanceID> VertexInstanceIDs, TArray<FEdgeID>* OutEdgeIDs);`
- L1252 _private prototype_ `void CreatePolygonTriangles(const FPolygonID PolygonID, TArrayView<const FVertexInstanceID> VertexInstanceIDs);`
- L1253 _private prototype_ `void RemovePolygonTriangles(const FPolygonID PolygonID);`
- L1256 _private prototype_ `template <template <typename...> class TContainer> void DeleteVertexInstance_Internal(const FVertexInstanceID VertexInstanceID, TContainer<FVertexID>* InOutOrphanedVerticesPtr = nullptr);`
- L1258 _private prototype_ `template <template <typename...> class TContainer> void DeleteEdge_Internal(const FEdgeID EdgeID, TContainer<FVertexID>* InOutOrphanedVerticesPtr = nullptr);`
- L1260 _private prototype_ `template <template <typename...> class TContainer> void DeleteTriangle_Internal(const FTriangleID TriangleID, TContainer<FEdgeID>* InOutOrphanedEdgesPtr = nullptr, TContainer<FVertexInstanceID>* InOutOrphanedVertexInstancesPtr = nullptr, TContainer<FPolygonGroupID>* InOutOrphanedPolygonGroupsPtr = nullptr);`
- L1262 _private prototype_ `template <template <typename...> class TContainer> void DeletePolygon_Internal(const FPolygonID PolygonID, TContainer<FEdgeID>* InOutOrphanedEdgesPtr = nullptr, TContainer<FVertexInstanceID>* InOutOrphanedVertexInstancesPtr = nullptr, TContainer<FPolygonGroupID>* InOutOrphanedPolygonGroupsPtr = nullptr);`
- L1265 _private prototype_ `void FixUpElementIDs(const FElementIDRemappings& Remappings);` — Given a set of index remappings, fixes up references to element IDs
- L1268 _private function_ `template <class T> void AddUnique(TArray<T>& Container, const T& Item)`
- L1274 _private function_ `template <class T> void AddUnique(TSet<T>& Container, const T& Item)`
- L1280 _public member_ `static FName VerticesName;`
- L1281 _public member_ `static FName VertexInstancesName;`
- L1282 _public member_ `static FName UVsName;`
- L1283 _public member_ `static FName EdgesName;`
- L1284 _public member_ `static FName TrianglesName;`
- L1285 _public member_ `static FName PolygonsName;`
- L1286 _public member_ `static FName PolygonGroupsName;`
- L1289 _private member_ `TMap<FName, FMeshElementTypeWrapper> Elements;`
- L1291 _private member_ `FMeshElementChannels* VertexElements;`
- L1292 _private member_ `FMeshElementChannels* VertexInstanceElements;`
- L1293 _private member_ `FMeshElementChannels* UVElements;`
- L1294 _private member_ `FMeshElementChannels* EdgeElements;`
- L1295 _private member_ `FMeshElementChannels* TriangleElements;`
- L1296 _private member_ `FMeshElementChannels* PolygonElements;`
- L1297 _private member_ `FMeshElementChannels* PolygonGroupElements;`
- L1299 _private member_ `TMeshAttributesArray<FVertexID> VertexInstanceVertices;`
- L1300 _private member_ `TMeshAttributesArray<TArrayView<FVertexID>> EdgeVertices;`
- L1301 _private member_ `TMeshAttributesArray<TArrayView<FVertexInstanceID>> TriangleVertexInstances;`
- L1302 _private member_ `TMeshAttributesArray<FPolygonID> TrianglePolygons;`
- L1303 _private member_ `TMeshAttributesArray<TArrayView<FEdgeID>> TriangleEdges;`
- L1304 _private member_ `TMeshAttributesArray<TArrayView<FVertexID>> TriangleVertices;`
- L1305 _private member_ `TMeshAttributesArray<TArrayView<FUVID>> TriangleUVs;`
- L1306 _private member_ `TMeshAttributesArray<FPolygonGroupID> TrianglePolygonGroups;`
- L1307 _private member_ `TMeshAttributesArray<FPolygonGroupID> PolygonPolygonGroups;`
- L1308 _private member_ `TMeshAttributesArray<FVector3f> VertexPositions;`
- L1311 _private member_ `mutable FMeshElementIndexer VertexToVertexInstances;` — The indexers are all mutable because they may be rebuilt during what is essentially a get operation
- L1312 _private member_ `mutable FMeshElementIndexer VertexToEdges;`
- L1313 _private member_ `mutable FMeshElementIndexer VertexInstanceToTriangles;`
- L1314 _private member_ `mutable FMeshElementIndexer EdgeToTriangles;`
- L1315 _private member_ `mutable FMeshElementIndexer UVToTriangles;`
- L1316 _private member_ `mutable FMeshElementIndexer PolygonToTriangles;`
- L1317 _private member_ `mutable FMeshElementIndexer PolygonGroupToTriangles;`
- L1318 _private member_ `mutable FMeshElementIndexer PolygonGroupToPolygons;`

#### struct `FMeshDescriptionBulkData`  
`struct FMeshDescriptionBulkData`  
_L1328-1420_
- desc: Bulk data storage for FMeshDescription
- L1331 _public prototype_ `FMeshDescriptionBulkData() = default;`
- L1334 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner);` — Serialization
- L1337 _public prototype_ `void SaveMeshDescription(FMeshDescription& MeshDescription);` — Store a new mesh description in the bulk data
- L1340 _public prototype_ `void LoadMeshDescription(FMeshDescription& MeshDescription);` — Load the mesh description from the bulk data
- L1343 _public prototype_ `void Empty();` — Empties the bulk data
- L1346 _public function_ `bool IsEmpty() const` — Returns true if there is no bulk data available
- L1353 _public function_ `FString GetUnversionedIdString() const` — Return unique ID string for this bulk data that does not include versioning info. Use this for constructing IDs that do not rely on the serialization format of FMeshDescription but is only dependent on its contents, such as storing intermediate representations build from the FMeshDescription data in the DDC.
- L1363 _public function_ `FString GetVersionedIdString() const` — Return unique ID string for this bulk data that also includes current versioning info for FMeshDescription serialization. Use this for constructing IDs that are required for serializing the FMeshDescription bulk data to disk, such as storing FMeshDescription archives in a shared DDC storage.
- L1369 _public function_ `FString GetIdString() const` — `UE_DEPRECATED(5.8, "Use GetVersionedIdString or GetUnversionedIdString instead, depending on requirements")`
- L1378 _public prototype_ `static FString GetSerializationVersionIdString();` — Return an ID string that represents the serialization version for FMeshDescription based on the live custom versions. This differs from GetVersionedIdString() in that it does not include the content hash.
- L1381 _public prototype_ `void UseHashAsGuid();` — Uses a hash as the GUID, useful to prevent recomputing content already in cache.
- L1384 _public function_ `int64 GetBulkDataSize()` — Gets the size of the serialized bulk data
- L1387 _public prototype_ `static TConstArrayView<FGuid> GetMeshDescriptionCustomVersions();` — Returns the CustomVersions GUIDs that are used when serializing an FMeshDescription.
- L1390 _private prototype_ `void UpdateMeshDescriptionFormat();`
- L1392 _private prototype_ `FString GetIdStringFromVersionList(TConstArrayView<TPair<FGuid, int32>> InVersionList) const;`
- L1394 _private prototype_ `static TConstArrayView<TPair<FGuid, int32>> GetFrozenVersions();`
- L1398 _private member_ `FRWLock BulkDataLock;` — Protects simultaneous access to BulkData
- L1401 _private member_ `UE::Serialization::FEditorBulkData BulkData;` — Internally store bulk data as bytes
- L1404 _private member_ `FGuid Guid;` — GUID associated with the data stored herein.
- L1407 _private prototype_ `FGuid GetHash() const;` — Gets this bulk data hash
- L1410 _private member_ `FCustomVersionContainer CustomVersions;` — Take a copy of the bulk data versioning so it can be propagated to the bulk data reader when deserializing MeshDescription
- L1411 _private member_ `FPackageFileVersion UEVersion;`
- L1412 _private member_ `int32 LicenseeUEVersion = INDEX_NONE;`
- L1416 _private member_ `bool bBulkDataUpdated = false;` — Whether the bulk data has been written via SaveMeshDescription
- L1419 _private member_ `bool bGuidIsHash = false;` — Uses hash instead of guid to identify content to improve DDC cache hit.

#### Free symbols / members of external scopes

- L52 _enumerator_ `MAX_MESH_TEXTURE_COORDS_MD = 8` (scope `__anon488810be0103`) — Remove the _MD when FRawMesh will be remove
- L57 _typedef_ `using FVertexArray = TMeshElementContainer<FVertexID>;` — Define container types
- L58 _typedef_ `using FVertexInstanceArray = TMeshElementContainer<FVertexInstanceID>;`
- L59 _typedef_ `using FEdgeArray = TMeshElementContainer<FEdgeID>;`
- L60 _typedef_ `using FUVArray = TMeshElementContainer<FUVID>;`
- L61 _typedef_ `using FTriangleArray = TMeshElementContainer<FTriangleID>;`
- L62 _typedef_ `using FPolygonArray = TMeshElementContainer<FPolygonID>;`
- L63 _typedef_ `using FPolygonGroupArray = TMeshElementContainer<FPolygonGroupID>;`
- L66 _typedef_ `template <typename AttributeType> using TVertexAttributesRef = TMeshAttributesRef<FVertexID, AttributeType>;` — Define aliases for element attributes
- L67 _typedef_ `template <typename AttributeType> using TVertexAttributesRef = TMeshAttributesRef<FVertexID, AttributeType>;` — Define aliases for element attributes
- L68 _typedef_ `template <typename AttributeType> using TVertexAttributesRef = TMeshAttributesRef<FVertexID, AttributeType>;` — Define aliases for element attributes
- L69 _typedef_ `template <typename AttributeType> using TVertexAttributesRef = TMeshAttributesRef<FVertexID, AttributeType>;` — Define aliases for element attributes
- L70 _typedef_ `template <typename AttributeType> using TVertexInstanceAttributesRef = TMeshAttributesRef<FVertexInstanceID, AttributeType>;`
- L71 _typedef_ `template <typename AttributeType> using TEdgeAttributesRef = TMeshAttributesRef<FEdgeID, AttributeType>;`
- L72 _typedef_ `template <typename AttributeType> using TUVAttributesRef = TMeshAttributesRef<FUVID, AttributeType>;`
- L74 _typedef_ `template <typename AttributeType> using TVertexAttributesConstRef = TMeshAttributesConstRef<FVertexID, AttributeType>;`
- L75 _typedef_ `template <typename AttributeType> using TVertexAttributesConstRef = TMeshAttributesConstRef<FVertexID, AttributeType>;`
- L76 _typedef_ `template <typename AttributeType> using TVertexAttributesConstRef = TMeshAttributesConstRef<FVertexID, AttributeType>;`
- L77 _typedef_ `template <typename AttributeType> using TVertexAttributesConstRef = TMeshAttributesConstRef<FVertexID, AttributeType>;`
- L78 _typedef_ `template <typename AttributeType> using TVertexInstanceAttributesConstRef = TMeshAttributesConstRef<FVertexInstanceID, AttributeType>;`
- L79 _typedef_ `template <typename AttributeType> using TEdgeAttributesConstRef = TMeshAttributesConstRef<FEdgeID, AttributeType>;`
- L80 _typedef_ `template <typename AttributeType> using TUVAttributesConstRef = TMeshAttributesConstRef<FUVID, AttributeType>;`
- L90 _prototype_ `ENUM_CLASS_FLAGS(EComputeNTBsOptions);`
- L106 _function_ `friend FArchive& operator<<(FArchive& Ar, FMeshDescription& MeshDescription)`
- L516 _function_ `return Algo::TransformAccumulate(VertexInstances, [this](const FVertexInstanceID ID) { return VertexInstanceToTriangles.Find(ID).Num(); }, 0);` (scope `FMeshDescription::GetNumVertexConnectedTriangles`)
- L874 _function_ `GetTriangleVertexInstances(TriangleID), [this, VertexID](const FVertexInstanceID VertexInstanceID)` (scope `FMeshDescription::GetVertexInstanceForTriangleVertex`)
- L1124 _function_ `[this, VertexID](const FVertexInstanceID VertexInstanceID)` (scope `FMeshDescription::GetVertexInstanceForPolygonVertex`)

### `Source/Runtime/MeshDescription/Public/MeshDescriptionBase.h` (Public)


#### class `UMeshDescriptionBase`  
`class UMeshDescriptionBase : public UObject`  
_L25-500_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L31 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L35 _public function_ `FMeshDescription& GetMeshDescription()` — Get a reference to the actual mesh description
- L40 _public function_ `const FMeshDescription& GetMeshDescription() const`
- L46 _public function_ `void SetMeshDescription(FMeshDescription InMeshDescription)` — Set the mesh description
- L52 _public prototype_ `virtual void RegisterAttributes();` — UMeshDescriptionBase interface
- L53 _public function_ `virtual FMeshAttributes& GetRequiredAttributes()`
- L54 _public function_ `virtual const FMeshAttributes& GetRequiredAttributes() const`
- L58 _public prototype_ `void Reset();` — Reset the contained mesh description
- L61 _public function_ `FVertexArray& Vertices()` — Accessors for mesh element arrays
- L62 _public function_ `const FVertexArray& Vertices() const`
- L64 _public function_ `FVertexInstanceArray& VertexInstances()`
- L65 _public function_ `const FVertexInstanceArray& VertexInstances() const`
- L67 _public function_ `FEdgeArray& Edges()`
- L68 _public function_ `const FEdgeArray& Edges() const`
- L70 _public function_ `FTriangleArray& Triangles()`
- L71 _public function_ `const FTriangleArray& Triangles() const`
- L73 _public function_ `FPolygonArray& Polygons()`
- L74 _public function_ `const FPolygonArray& Polygons() const`
- L76 _public function_ `FPolygonGroupArray& PolygonGroups()`
- L77 _public function_ `const FPolygonGroupArray& PolygonGroups() const`
- L80 _public function_ `TAttributesSet<FVertexID>& VertexAttributes()` — Accessors for mesh element attributes
- L81 _public function_ `const TAttributesSet<FVertexID>& VertexAttributes() const`
- L83 _public function_ `TAttributesSet<FVertexInstanceID>& VertexInstanceAttributes()`
- L84 _public function_ `const TAttributesSet<FVertexInstanceID>& VertexInstanceAttributes() const`
- L86 _public function_ `TAttributesSet<FEdgeID>& EdgeAttributes()`
- L87 _public function_ `const TAttributesSet<FEdgeID>& EdgeAttributes() const`
- L89 _public function_ `TAttributesSet<FTriangleID>& TriangleAttributes()`
- L90 _public function_ `const TAttributesSet<FTriangleID>& TriangleAttributes() const`
- L92 _public function_ `TAttributesSet<FPolygonID>& PolygonAttributes()`
- L93 _public function_ `const TAttributesSet<FPolygonID>& PolygonAttributes() const`
- L95 _public function_ `TAttributesSet<FPolygonGroupID>& PolygonGroupAttributes()`
- L96 _public function_ `const TAttributesSet<FPolygonGroupID>& PolygonGroupAttributes() const`
- L99 _public function_ `TVertexAttributesRef<FVector3f> GetVertexPositions()` — Accessors for cached vertex position array
- L100 _public function_ `TVertexAttributesConstRef<FVector3f> GetVertexPositions() const`
- L106 _public prototype_ `void Empty();` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Empty the mesh description
- L110 _public prototype_ `bool IsEmpty() const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return whether the mesh description is empty
- L118 _public prototype_ `void ReserveNewVertices(int32 NumberOfNewVertices);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reserves space for this number of new vertices
- L122 _public prototype_ `FVertexID CreateVertex();` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new vertex to the mesh and returns its ID
- L126 _public prototype_ `void CreateVertexWithID(FVertexID VertexID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new vertex to the mesh with the given ID
- L130 _public prototype_ `void DeleteVertex(FVertexID VertexID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Deletes a vertex from the mesh
- L134 _public prototype_ `bool IsVertexValid(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether the passed vertex ID is valid
- L138 _public function_ `int32 GetVertexCount() const` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of vertices
- L142 _public prototype_ `void ReserveNewVertexInstances(int32 NumberOfNewVertexInstances);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reserves space for this number of new vertex instances
- L146 _public prototype_ `FVertexInstanceID CreateVertexInstance(FVertexID VertexID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new vertex instance to the mesh and returns its ID
- L150 _public prototype_ `void CreateVertexInstanceWithID(FVertexInstanceID VertexInstanceID, FVertexID VertexID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new vertex instance to the mesh with the given ID
- L154 _public prototype_ `void DeleteVertexInstance(FVertexInstanceID VertexInstanceID, TArray<FVertexID>& OrphanedVertices);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Deletes a vertex instance from a mesh
- L158 _public prototype_ `bool IsVertexInstanceValid(FVertexInstanceID VertexInstanceID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether the passed vertex instance ID is valid
- L162 _public function_ `int32 GetVertexInstanceCount() const` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of vertex instances
- L166 _public prototype_ `void ReserveNewEdges(int32 NumberOfNewEdges);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reserves space for this number of new edges
- L170 _public prototype_ `FEdgeID CreateEdge(FVertexID VertexID0, FVertexID VertexID1);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new edge to the mesh and returns its ID
- L174 _public prototype_ `void CreateEdgeWithID(FEdgeID EdgeID, FVertexID VertexID0, FVertexID VertexID1);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new edge to the mesh with the given ID
- L178 _public prototype_ `void DeleteEdge(FEdgeID EdgeID, TArray<FVertexID>& OrphanedVertices);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Deletes an edge from a mesh
- L182 _public prototype_ `bool IsEdgeValid(FEdgeID EdgeID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether the passed edge ID is valid
- L186 _public function_ `int32 GetEdgeCount() const` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of edges
- L190 _public prototype_ `void ReserveNewTriangles(int32 NumberOfNewTriangles);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reserves space for this number of new triangles
- L194 _public prototype_ `FTriangleID CreateTriangle(FPolygonGroupID PolygonGroupID, const TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new triangle to the mesh and returns its ID. This will also make an encapsulating polygon, and any missing edges.
- L198 _public prototype_ `void CreateTriangleWithID(FTriangleID TriangleID, FPolygonGroupID PolygonGroupID, const TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new triangle to the mesh with the given ID. This will also make an encapsulating polygon, and any missing edges.
- L202 _public prototype_ `void DeleteTriangle(FTriangleID TriangleID, TArray<FEdgeID>& OrphanedEdges, TArray<FVertexInstanceID>& OrphanedVertexInstances, TArray<FPolygonGroupID>& OrphanedPolygonGroupsPtr);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Deletes a triangle from the mesh
- L206 _public prototype_ `bool IsTriangleValid(const FTriangleID TriangleID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether the passed triangle ID is valid
- L210 _public function_ `int32 GetTriangleCount() const` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of triangles
- L214 _public prototype_ `void ReserveNewPolygons(const int32 NumberOfNewPolygons);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reserves space for this number of new polygons
- L218 _public prototype_ `FPolygonID CreatePolygon(FPolygonGroupID PolygonGroupID, TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new polygon to the mesh and returns its ID. This will also make any missing edges, and all constituent triangles.
- L222 _public prototype_ `void CreatePolygonWithID(FPolygonID PolygonID, FPolygonGroupID PolygonGroupID, TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new polygon to the mesh with the given ID. This will also make any missing edges, and all constituent triangles.
- L226 _public prototype_ `void DeletePolygon(FPolygonID PolygonID, TArray<FEdgeID>& OrphanedEdges, TArray<FVertexInstanceID>& OrphanedVertexInstances, TArray<FPolygonGroupID>& OrphanedPolygonGroups);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Deletes a polygon from the mesh
- L230 _public prototype_ `bool IsPolygonValid(FPolygonID PolygonID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether the passed polygon ID is valid
- L234 _public function_ `int32 GetPolygonCount() const` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of polygons
- L238 _public prototype_ `void ReserveNewPolygonGroups(int32 NumberOfNewPolygonGroups);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reserves space for this number of new polygon groups
- L242 _public prototype_ `FPolygonGroupID CreatePolygonGroup();` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new polygon group to the mesh and returns its ID
- L246 _public prototype_ `void CreatePolygonGroupWithID(FPolygonGroupID PolygonGroupID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Adds a new polygon group to the mesh with the given ID
- L250 _public prototype_ `void DeletePolygonGroup(FPolygonGroupID PolygonGroupID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Deletes a polygon group from the mesh
- L254 _public prototype_ `bool IsPolygonGroupValid(FPolygonGroupID PolygonGroupID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether the passed polygon group ID is valid
- L258 _public function_ `int32 GetPolygonGroupCount() const` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of polygon groups
- L266 _public prototype_ `bool IsVertexOrphaned(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns whether a given vertex is orphaned, i.e. it doesn't form part of any polygon
- L270 _public prototype_ `FEdgeID GetVertexPairEdge(FVertexID VertexID0, FVertexID VertexID1) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the edge ID defined by the two given vertex IDs, if there is one; otherwise INDEX_NONE
- L274 _public prototype_ `void GetVertexConnectedEdges(FVertexID VertexID, TArray<FEdgeID>& OutEdgeIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns reference to an array of Edge IDs connected to this vertex
- L278 _public prototype_ `int32 GetNumVertexConnectedEdges(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns number of edges connected to this vertex
- L282 _public prototype_ `void GetVertexVertexInstances(FVertexID VertexID, TArray<FVertexInstanceID>& OutVertexInstanceIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns reference to an array of VertexInstance IDs instanced from this vertex
- L286 _public prototype_ `int32 GetNumVertexVertexInstances(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns number of vertex instances created from this vertex
- L290 _public prototype_ `void GetVertexConnectedTriangles(FVertexID VertexID, TArray<FTriangleID>& OutConnectedTriangleIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the triangles connected to this vertex
- L294 _public prototype_ `int32 GetNumVertexConnectedTriangles(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns number of triangles connected to this vertex
- L298 _public prototype_ `void GetVertexConnectedPolygons(FVertexID VertexID, TArray<FPolygonID>& OutConnectedPolygonIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the polygons connected to this vertex
- L302 _public prototype_ `int32 GetNumVertexConnectedPolygons(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of polygons connected to this vertex
- L306 _public prototype_ `void GetVertexAdjacentVertices(FVertexID VertexID, TArray<FVertexID>& OutAdjacentVertexIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the vertices adjacent to this vertex
- L310 _public prototype_ `FVector GetVertexPosition(FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Gets a vertex position
- L314 _public prototype_ `void SetVertexPosition(FVertexID VertexID, const FVector& Position);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Sets a vertex position
- L322 _public prototype_ `FVertexID GetVertexInstanceVertex(FVertexInstanceID VertexInstanceID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the vertex ID associated with the given vertex instance
- L326 _public prototype_ `FEdgeID GetVertexInstancePairEdge(FVertexInstanceID VertexInstanceID0, FVertexInstanceID VertexInstanceID1) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the edge ID defined by the two given vertex instance IDs, if there is one; otherwise INDEX_NONE
- L330 _public prototype_ `void GetVertexInstanceConnectedTriangles(FVertexInstanceID VertexInstanceID, TArray<FTriangleID>& OutConnectedTriangleIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns reference to an array of Triangle IDs connected to this vertex instance
- L334 _public prototype_ `int32 GetNumVertexInstanceConnectedTriangles(FVertexInstanceID VertexInstanceID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of triangles connected to this vertex instance
- L338 _public prototype_ `void GetVertexInstanceConnectedPolygons(FVertexInstanceID VertexInstanceID, TArray<FPolygonID>& OutConnectedPolygonIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the polygons connected to this vertex instance
- L342 _public prototype_ `int32 GetNumVertexInstanceConnectedPolygons(FVertexInstanceID VertexInstanceID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of polygons connected to this vertex instance.
- L350 _public prototype_ `bool IsEdgeInternal(FEdgeID EdgeID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Determine whether a given edge is an internal edge between triangles of a polygon
- L354 _public prototype_ `bool IsEdgeInternalToPolygon(FEdgeID EdgeID, FPolygonID PolygonID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Determine whether a given edge is an internal edge between triangles of a specific polygon
- L358 _public prototype_ `void GetEdgeConnectedTriangles(FEdgeID EdgeID, TArray<FTriangleID>& OutConnectedTriangleIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns reference to an array of triangle IDs connected to this edge
- L362 _public prototype_ `int32 GetNumEdgeConnectedTriangles(FEdgeID EdgeID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of triangles connected to this edge
- L366 _public prototype_ `void GetEdgeConnectedPolygons(FEdgeID EdgeID, TArray<FPolygonID>& OutConnectedPolygonIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the polygons connected to this edge
- L370 _public prototype_ `int32 GetNumEdgeConnectedPolygons(FEdgeID EdgeID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of polygons connected to this edge
- L374 _public prototype_ `FVertexID GetEdgeVertex(FEdgeID EdgeID, int32 VertexNumber) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the vertex ID corresponding to one of the edge endpoints
- L378 _public prototype_ `void GetEdgeVertices(const FEdgeID EdgeID, TArray<FVertexID>& OutVertexIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns a pair of vertex IDs defining the edge
- L386 _public prototype_ `FPolygonID GetTrianglePolygon(FTriangleID TriangleID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Get the polygon which contains this triangle
- L390 _public prototype_ `FPolygonGroupID GetTrianglePolygonGroup(FTriangleID TriangleID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Get the polygon group which contains this triangle
- L394 _public prototype_ `bool IsTrianglePartOfNgon(FTriangleID TriangleID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Determines if this triangle is part of an n-gon
- L398 _public prototype_ `void GetTriangleVertexInstances(FTriangleID TriangleID, TArray<FVertexInstanceID>& OutVertexInstanceIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Get the vertex instances which define this triangle
- L402 _public prototype_ `FVertexInstanceID GetTriangleVertexInstance(FTriangleID TriangleID, int32 Index) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Get the specified vertex instance by index
- L406 _public prototype_ `void GetTriangleVertices(FTriangleID TriangleID, TArray<FVertexID>& OutVertexIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the vertices which define this triangle
- L410 _public prototype_ `void GetTriangleEdges(FTriangleID TriangleID, TArray<FEdgeID>& OutEdgeIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the edges which define this triangle
- L414 _public prototype_ `void GetTriangleAdjacentTriangles(FTriangleID TriangleID, TArray<FTriangleID>& OutTriangleIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the adjacent triangles to this triangle
- L418 _public prototype_ `FVertexInstanceID GetVertexInstanceForTriangleVertex(FTriangleID TriangleID, FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return the vertex instance which corresponds to the given vertex on the given triangle, or INDEX_NONE
- L426 _public prototype_ `void GetPolygonTriangles(FPolygonID PolygonID, TArray<FTriangleID>& OutTriangleIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return reference to an array of triangle IDs which comprise this polygon
- L430 _public prototype_ `int32 GetNumPolygonTriangles(FPolygonID PolygonID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return the number of triangles which comprise this polygon
- L434 _public prototype_ `void GetPolygonVertexInstances(FPolygonID PolygonID, TArray<FVertexInstanceID>& OutVertexInstanceIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns reference to an array of VertexInstance IDs forming the perimeter of this polygon
- L438 _public prototype_ `int32 GetNumPolygonVertices(FPolygonID PolygonID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of vertices this polygon has
- L442 _public prototype_ `void GetPolygonVertices(FPolygonID PolygonID, TArray<FVertexID>& OutVertexIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the vertices which form the polygon perimeter
- L446 _public prototype_ `void GetPolygonPerimeterEdges(FPolygonID PolygonID, TArray<FEdgeID>& OutEdgeIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the edges which form the polygon perimeter
- L451 _public prototype_ `void GetPolygonInternalEdges(FPolygonID PolygonID, TArray<FEdgeID>& OutEdgeIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Populate the provided array with a list of edges which are internal to the polygon, i.e. those which separate constituent triangles.
- L455 _public prototype_ `int32 GetNumPolygonInternalEdges(FPolygonID PolygonID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return the number of internal edges in this polygon
- L459 _public prototype_ `void GetPolygonAdjacentPolygons(FPolygonID PolygonID, TArray<FPolygonID>& OutPolygonIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Populates the passed array with adjacent polygons
- L463 _public prototype_ `FPolygonGroupID GetPolygonPolygonGroup(FPolygonID PolygonID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return the polygon group associated with a polygon
- L467 _public prototype_ `FVertexInstanceID GetVertexInstanceForPolygonVertex(FPolygonID PolygonID, FVertexID VertexID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Return the vertex instance which corresponds to the given vertex on the given polygon, or INDEX_NONE
- L471 _public prototype_ `void SetPolygonVertexInstances(FPolygonID PolygonID, const TArray<FVertexInstanceID>& VertexInstanceIDs);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Set the vertex instance at the given index around the polygon to the new value
- L475 _public prototype_ `void SetPolygonPolygonGroup(FPolygonID PolygonID, FPolygonGroupID PolygonGroupID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Sets the polygon group associated with a polygon
- L479 _public prototype_ `void ReversePolygonFacing(FPolygonID PolygonID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Reverse the winding order of the vertices of this polygon
- L483 _public prototype_ `void ComputePolygonTriangulation(FPolygonID PolygonID);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")` — Generates triangles and internal edges for the given polygon
- L491 _public prototype_ `void GetPolygonGroupPolygons(FPolygonGroupID PolygonGroupID, TArray<FPolygonID>& OutPolygonIDs) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the polygons associated with the given polygon group
- L495 _public prototype_ `int32 GetNumPolygonGroupPolygons(FPolygonGroupID PolygonGroupID) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")` — Returns the number of polygons in this polygon group
- L498 _protected member_ `FMeshDescription OwnedMeshDescription;`
- L499 _protected member_ `TUniquePtr<FMeshAttributes> RequiredAttributes;`

### `Source/Runtime/MeshDescription/Public/MeshDescriptionBaseBulkData.h` (Public)


#### class `UMeshDescriptionBaseBulkData`  
`class UMeshDescriptionBaseBulkData : public UObject`  
_L24-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: UObject wrapper for FMeshDescriptionBulkData
- L29 _public prototype_ `UMeshDescriptionBaseBulkData();`
- L30 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L31 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L32 _public prototype_ `virtual bool NeedsLoadForClient() const override;`
- L33 _public prototype_ `virtual bool NeedsLoadForServer() const override;`
- L34 _public prototype_ `virtual bool NeedsLoadForEditorGame() const override;`
- L38 _public prototype_ `void Empty();`
- L39 _public prototype_ `UMeshDescriptionBase* CreateMeshDescription();`
- L40 _public prototype_ `UMeshDescriptionBase* GetMeshDescription() const;`
- L41 _public prototype_ `bool HasCachedMeshDescription() const;`
- L42 _public prototype_ `bool CacheMeshDescription();`
- L43 _public prototype_ `void CommitMeshDescription(bool bUseHashAsGuid);`
- L44 _public prototype_ `void RemoveMeshDescription();`
- L45 _public prototype_ `bool IsBulkDataValid() const;`
- L47 _public prototype_ `const FMeshDescriptionBulkData& GetBulkData() const;`
- L48 _public prototype_ `FMeshDescriptionBulkData& GetBulkData();`
- L51 _protected member_ `TPimplPtr<FMeshDescriptionBulkData> BulkData;`
- L54 _protected member_ `TObjectPtr<UMeshDescriptionBase> PreallocatedMeshDescription;` — `UPROPERTY(Transient, Instanced)`
- L57 _protected member_ `TObjectPtr<UMeshDescriptionBase> MeshDescription;` — `UPROPERTY(Transient)`

### `Source/Runtime/MeshDescription/Public/MeshElementArray.h` (Public)


#### class `TMeshElementArrayBase`  
`template <typename ElementType> class TMeshElementArrayBase`  
_L15-85_
- desc: This defines the container used to hold mesh elements. Its important properties are that it acts as an associative container (i.e. an element can be obtained from a given index), and that insert/delete/find are cheap. The current implementation is as a TSparseArray, but we abstract it so that this can be changed later if required, e.g. a TMap might be desirable if we wished to maintain unique indices for the lifetime of the container.
- L75 _public prototype_ `void Compact( TSparseArray<int32>& OutIndexRemap );` — Compacts elements and returns a remapping table
- L78 _public prototype_ `void Remap( const TSparseArray<int32>& IndexRemap );` — Remaps elements according to the passed remapping table
- L84 _protected member_ `TSparseArray<ElementType> Container;` — The actual container, represented by a sparse array
- L268 _function_ `template <typename ElementType> void TMeshElementArrayBase<ElementType>::Compact( TSparseArray<int32>& OutIndexRemap )`
- L293 _function_ `template <typename ElementType> void TMeshElementArrayBase<ElementType>::Remap( const TSparseArray<int32>& IndexRemap )`

#### class `TMeshElementArray`  
`template <typename ElementType, typename ElementIDType> class TMeshElementArray final : public TMeshElementArrayBase<ElementType>`  
_L93-264_
- inherits: `TMeshElementArrayBase<ElementType>`
- desc: We prefer to access elements of the container via strongly-typed IDs. This derived class imposes this type safety.
- L102 _public function_ `inline void Reset( const int32 Elements = 0 )` — Resets the container, optionally reserving space for elements to be added
- L109 _public function_ `inline void Reserve( const int32 Elements )` — Reserves space for the specified total number of elements
- L112 _public function_ `inline ElementIDType Add()` — Add a new element at the next available index, and return the new ID
- L115 _public function_ `inline ElementIDType Add( typename TTypeTraits<ElementType>::ConstInitType Element )` — Add the provided element at the next available index, and return the new ID
- L118 _public function_ `inline ElementIDType Add( ElementType&& Element )` — Add the provided element at the next available index, and return the ID
- L121 _public function_ `inline ElementType& Insert( const ElementIDType ID )` — Inserts a new element with the given ID
- L128 _public function_ `inline ElementType& Insert( const ElementIDType ID, typename TTypeTraits<ElementType>::ConstInitType Element )` — Inserts the provided element with the given ID
- L135 _public function_ `inline ElementType& Insert( const ElementIDType ID, ElementType&& Element )` — Inserts the provided element with the given ID
- L142 _public function_ `inline void Remove( const ElementIDType ID )` — Removes the element with the given ID
- L149 _public function_ `inline ElementType& operator[]( const ElementIDType ID )` — Returns the element with the given ID
- L155 _public function_ `inline const ElementType& operator[]( const ElementIDType ID ) const`
- L162 _public function_ `inline int32 Num() const` — Returns the number of elements in the container
- L165 _public function_ `inline int32 GetArraySize() const` — Returns the index after the last valid element
- L168 _public function_ `inline ElementIDType GetFirstValidID() const` — Returns the first valid ID
- L176 _public function_ `inline bool IsValid( const ElementIDType ID ) const` — Returns whether the given ID is valid or not
- L263 _public function_ `TElementIDs inline GetElementIDs() const` — Return iterable proxy object from container

#### class `TMeshElementArray::TElementIDs`  
`class TElementIDs`  
_L198-260_
- desc: This is a special type of iterator which returns successive IDs of valid elements, rather than the elements themselves. It is designed to be used with a range-for: for( const FVertexID VertexID : GetVertices().GetElementIDs() ) { DoSomethingWith( VertexID ); }
- L202 _public function_ `explicit inline TElementIDs( const TSparseArray<ElementType>& InArray ) : Array( InArray )`
- L225 _public function_ `friend inline bool operator==( const TConstIterator& Lhs, const TConstIterator& Rhs )`
- L230 _public function_ `friend inline bool operator!=( const TConstIterator& Lhs, const TConstIterator& Rhs )`
- L240 _public function_ `inline TConstIterator CreateConstIterator() const`
- L247 _public function_ `inline TConstIterator begin() const`
- L252 _public function_ `inline TConstIterator end() const`
- L259 _private member_ `const TSparseArray<ElementType>& Array;`

#### class `TMeshElementArray::TElementIDs::TConstIterator`  
`class TConstIterator`  
_L206-238_
- L210 _public function_ `explicit inline TConstIterator( typename TSparseArray<ElementType>::TConstIterator&& It ) : Iterator( MoveTemp( It ) )`
- L214 _public function_ `inline TConstIterator& operator++()`
- L220 _public function_ `inline ElementIDType operator*() const`
- L237 _private member_ `typename TSparseArray<ElementType>::TConstIterator Iterator;`

#### Free symbols / members of external scopes

- L24 _function_ `friend FArchive& operator<<( FArchive& Ar, TMeshElementArrayBase& Array )` — Custom serialization for TMeshElementArrayBase. The default TSparseArray serialization also compacts all the elements, removing the gaps and changing the indices. The indices are significant in editable meshes, hence this is a custom serializer which preserves them.
- L182 _function_ `inline friend FArchive& operator<<( FArchive& Ar, TMeshElementArray& Array )` — Serializer

### `Source/Runtime/MeshDescription/Public/MeshElementContainer.h` (Public)


#### class `FMeshElementContainer`  
`class FMeshElementContainer`  
_L24-238_
- desc: Class representing a collection of mesh elements, such as vertices or triangles. It has two purposes: 1) To generate new element IDs on demand, and recycle those which have been discarded. 2) To hold a map of attributes for a given element type and their values.
- L27 _public prototype_ `FMeshElementContainer() = default;`
- L28 _public prototype_ `FMeshElementContainer(const FMeshElementContainer&) = default;`
- L29 _public prototype_ `FMeshElementContainer& operator=(const FMeshElementContainer&) = default;`
- L32 _public function_ `FMeshElementContainer(FMeshElementContainer&& Other)` — Move constructor which ensures that NumHoles is set correctly in the moved object
- L41 _public function_ `FMeshElementContainer& operator=(FMeshElementContainer&& Other)` — Move assignment operator which ensures that NumHoles is set correctly in the moved object
- L54 _public function_ `void Reset(const int32 Elements = 0)` — Resets the container, optionally reserving space for elements to be added
- L62 _public function_ `void Reserve(const int32 Elements)` — Reserves space for the specified total number of elements
- L65 _public function_ `int32 Add()` — Add a new element at the next available index, and return the new ID
- L85 _public function_ `void Insert(const int32 Index)` — Inserts a new element with the given index
- L110 _public function_ `void Remove(const int32 Index)` — Removes the element with the given ID
- L120 _public function_ `int32 Num() const` — Returns the number of elements in the container
- L123 _public function_ `int32 GetArraySize() const` — Returns the index after the last valid element
- L126 _public function_ `int32 GetFirstValidID() const` — Returns the first valid ID
- L132 _public function_ `bool IsValid(const int32 Index) const` — Returns whether the given ID is valid or not
- L138 _public function_ `inline FAttributesSetBase& GetAttributes()` — Accessor for attributes
- L139 _public function_ `inline const FAttributesSetBase& GetAttributes() const`
- L142 _public prototype_ `void Compact(TSparseArray<int32>& OutIndexRemap);` — Compacts elements and returns a remapping table
- L145 _public prototype_ `void Remap(const TSparseArray<int32>& IndexRemap);` — Remaps elements according to the passed remapping table
- L227 _public function_ `FElementIDs inline GetElementIDs() const` — Return iterable proxy object from container
- L231 _protected member_ `TBitArray<> BitArray;` — A bit array of all indices currently in use
- L234 _protected member_ `FAttributesSetBase Attributes;` — Attributes associated with this element container
- L237 _protected member_ `int32 NumHoles = 0;` — A count of the number of unused indices in the bit array. IMPORTANT: This must always correspond to the number of zeroes in the BitArray.

#### class `FMeshElementContainer::FElementIDs`  
`class FElementIDs`  
_L167-224_
- desc: This is a special type of iterator which returns successive IDs of valid elements, rather than the elements themselves. It is designed to be used with a range-for: for (const int32 VertexIndex : GetVertices().GetElementIDs()) { DoSomethingWith(VertexIndex); }
- L170 _public function_ `explicit inline FElementIDs(const TBitArray<>& InArray) : Array(InArray)`
- L192 _public function_ `friend inline bool operator==(const FConstIterator& Lhs, const FConstIterator& Rhs)`
- L197 _public function_ `friend inline bool operator!=(const FConstIterator& Lhs, const FConstIterator& Rhs)`
- L206 _public function_ `inline FConstIterator CreateConstIterator() const`
- L212 _public function_ `inline FConstIterator begin() const`
- L217 _public function_ `inline FConstIterator end() const`
- L223 _private member_ `const TBitArray<>& Array;`

#### class `FMeshElementContainer::FElementIDs::FConstIterator`  
`class FConstIterator`  
_L174-204_
- L177 _public function_ `explicit inline FConstIterator(TConstSetBitIterator<>&& It) : Iterator(MoveTemp(It))`
- L181 _public function_ `inline FConstIterator& operator++()`
- L187 _public function_ `inline int32 operator*() const`
- L203 _private member_ `TConstSetBitIterator<> Iterator;`

#### class `TMeshElementContainer`  
`template <typename ElementIDType> class TMeshElementContainer : public FMeshElementContainer`  
_L245-360_
- inherits: `FMeshElementContainer`
- desc: Templated specialization for type-safety.
- L249 _public function_ `ElementIDType Add()` — Add a new element at the next available index, and return the new ID
- L255 _public function_ `void Insert(const ElementIDType Index)` — Inserts a new element with the given index
- L261 _public function_ `void Remove(const ElementIDType Index)` — Removes the element with the given ID
- L267 _public function_ `ElementIDType GetFirstValidID() const` — Returns the first valid ID
- L273 _public function_ `bool IsValid(const ElementIDType Index) const` — Returns whether the given ID is valid or not
- L279 _public function_ `inline TAttributesSet<ElementIDType>& GetAttributes()` — Accessor for attributes
- L280 _public function_ `inline const TAttributesSet<ElementIDType>& GetAttributes() const`
- L359 _public function_ `TElementIDs inline GetElementIDs() const` — Return iterable proxy object from container

#### class `TMeshElementContainer::TElementIDs`  
`class TElementIDs`  
_L299-356_
- desc: This is a special type of iterator which returns successive IDs of valid elements, rather than the elements themselves. It is designed to be used with a range-for: for (const int32 VertexIndex : GetVertices().GetElementIDs()) { DoSomethingWith(VertexIndex); }
- L302 _public function_ `explicit inline TElementIDs(const TBitArray<>& InArray) : Array(InArray)`
- L324 _public function_ `friend inline bool operator==(const TConstIterator& Lhs, const TConstIterator& Rhs)`
- L329 _public function_ `friend inline bool operator!=(const TConstIterator& Lhs, const TConstIterator& Rhs)`
- L338 _public function_ `inline TConstIterator CreateConstIterator() const`
- L344 _public function_ `inline TConstIterator begin() const`
- L349 _public function_ `inline TConstIterator end() const`
- L355 _private member_ `const TBitArray<>& Array;`

#### class `TMeshElementContainer::TElementIDs::TConstIterator`  
`class TConstIterator`  
_L306-336_
- L309 _public function_ `explicit inline TConstIterator(TConstSetBitIterator<>&& It) : Iterator(MoveTemp(It))`
- L313 _public function_ `inline TConstIterator& operator++()`
- L319 _public function_ `inline ElementIDType operator*() const`
- L335 _private member_ `TConstSetBitIterator<> Iterator;`

#### class `FMeshElementChannels`  
`class FMeshElementChannels`  
_L366-421_
- desc: This is a wrapper for an array of allocated MeshElementContainers.
- L370 _public function_ `explicit FMeshElementChannels(const int32 NumberOfIndices = 1)` — Default constructor creates a single element
- L376 _public function_ `inline const FMeshElementContainer& Get(const int32 Index = 0) const` — Transparent access through the array
- L377 _public function_ `inline const FMeshElementContainer& operator[](const int32 Index) const`
- L378 _public function_ `inline const FMeshElementContainer& operator*() const`
- L379 _public function_ `inline const FMeshElementContainer* operator->() const`
- L380 _public function_ `inline FMeshElementContainer& Get(const int32 Index = 0)`
- L381 _public function_ `inline FMeshElementContainer& operator[](const int32 Index)`
- L382 _public function_ `inline FMeshElementContainer& operator*()`
- L383 _public function_ `inline FMeshElementContainer* operator->()`
- L386 _public function_ `void SetNumChannels(const int32 NumIndices)` — Change the number of indices
- L389 _public function_ `int32 GetNumChannels() const` — Get the number of indices
- L392 _public function_ `void Reset()` — Resets the containers
- L401 _public function_ `bool IsEmpty() const` — Determines whether the mesh element type is empty or not
- L420 _private member_ `TArray<FMeshElementContainer, TInlineAllocator<1>> Channels;` — The usual thing is that a MeshElementType has exactly one channel, so we specially reserve a single element inline to save extra allocations

#### class `FMeshElementTypeWrapper`  
`class FMeshElementTypeWrapper`  
_L428-476_
- desc: This is a wrapper for a FMeshElementChannels. It holds a TUniquePtr pointing to the actual FMeshElementChannels, so that its address is constant and can be cached.
- L432 _public function_ `explicit FMeshElementTypeWrapper(const int32 NumberOfChannels = 1)` — Default constructor - construct a MeshElementType, optionally with more than one channel
- L439 _public function_ `FMeshElementTypeWrapper(const FMeshElementTypeWrapper& Other)` — Copy constructor - make a deep copy of the MeshElementType through the TUniquePtr
- L446 _public function_ `FMeshElementTypeWrapper& operator=(const FMeshElementTypeWrapper& Other)` — Copy assignment
- L454 _public prototype_ `FMeshElementTypeWrapper(FMeshElementTypeWrapper&&) = default;` — Default move constructor
- L457 _public prototype_ `FMeshElementTypeWrapper& operator=(FMeshElementTypeWrapper&&) = default;` — Default move assignment
- L460 _public function_ `const FMeshElementChannels* Get() const` — Transparent access through the TUniquePtr
- L461 _public function_ `const FMeshElementChannels* operator->() const`
- L462 _public function_ `const FMeshElementChannels& operator*() const`
- L463 _public function_ `FMeshElementChannels* Get()`
- L464 _public function_ `FMeshElementChannels* operator->()`
- L465 _public function_ `FMeshElementChannels& operator*()`
- L475 _private member_ `TUniquePtr<FMeshElementChannels> Ptr;`

#### Free symbols / members of external scopes

- L148 _function_ `friend FArchive& operator<<(FArchive& Ar, FMeshElementContainer& Container)` — Serializer
- L283 _function_ `friend FArchive& operator<<(FArchive& Ar, TMeshElementContainer& Container)` — Serializer
- L412 _function_ `friend FArchive& operator<<(FArchive& Ar, FMeshElementChannels& ElementType)` — Serializer
- L468 _function_ `friend FArchive& operator<<(FArchive& Ar, FMeshElementTypeWrapper& Wrapper)` — Serializer

### `Source/Runtime/MeshDescription/Public/MeshElementIndexer.h` (Public)


#### class `FMeshElementIndexer`  
`class FMeshElementIndexer`  
_L47-324_
- desc: This is an efficient container for holding back references to mesh elements from attributes. Typically this will be a one-to-many relationship, where a given key has many different references. Naively this would be implemented as an array of arrays, but we want to minimise allocations and fragmentation as much as possible. This is achieved in two ways: 1) Arrays representing the list of references are consolidated into chunks of a user-specified size. This reduces the number of individual allocations which need to be made. By default, 256 keys are consolidated into a single chunk. 2) The arrays are lazily updated. The most expensive aspect of consolidating adjacent keys' values into a single chunk of data is having to insert new space into the middle of the chunk. If a new value can't be immediately added into a chunk without inserting, the key is marked as stale and the referencer is remembered. If a stale key is queried, the indexer will be updated first, building all stale keys by getting back references from the remembered referencers. There is also a way to fully rebuild an indexer, which will perform optimally few allocations, and collect all back references at once. It may sometimes be desirable to suspend an indexer, build a mesh description with indexing suspended, and then perform an indexer rebuild for additional speed and allocation efficiency. Some element relationships don't lend themselves to chunking, for example polygon groups to triangles. In this case, ther
- L50 _public prototype_ `FMeshElementIndexer() = default;`
- L51 _public prototype_ `FMeshElementIndexer(const FMeshElementChannels* Key, const FMeshElementChannels* Referencer, FName AttributeName, int32 ReferencerChannelIndex = 0);`
- L54 _public prototype_ `FMeshElementIndexer(const FMeshElementIndexer&) = delete;` — Copying not allowed as they reference elements of a MeshDescription of which they are normally a part
- L55 _public prototype_ `FMeshElementIndexer& operator=(const FMeshElementIndexer&) = delete;`
- L58 _public prototype_ `FMeshElementIndexer(FMeshElementIndexer&&) = default;` — Moving OK
- L59 _public prototype_ `FMeshElementIndexer& operator=(FMeshElementIndexer&&) = default;`
- L64 _public prototype_ `void Set(const FMeshElementChannels* Key, const FMeshElementChannels* Referencer, FName AttributeName, int32 ReferencerChannelIndex = 0);` — Set the parameters of this mesh element indexer
- L69 _public function_ `void SetInitialNumReferences(int InInitialSize)` — Sets the initial/expected number of references per key
- L75 _public function_ `void SetChunkSize(int InChunkSize)` — Sets the chunk size for the indexer, for optimization purposes. The default chunk size is 256.
- L85 _public function_ `void SetUnchunked()` — Configures the indexer not to use chunks. This is desirable if there are very few keys with a lot of references, e.g. polygon groups to polygons
- L95 _public prototype_ `void Reset();` — Resets the indexer
- L101 _public function_ `TArrayView<const int32> Find(int32 KeyIndex, int32 KeyChannelIndex = 0)` — Retrieve all referencer indices whose named attribute refers to KeyIndex. Non-const because finding a stale index might cause a rebuild.
- L118 _public function_ `template <typename ElementIDType> TArrayView<const ElementIDType> Find(int32 KeyIndex, int32 KeyChannelIndex = 0)`
- L138 _public prototype_ `void RemoveKey(int32 KeyIndex, int32 KeyChannelIndex = 0);` — Remove the specified key from the indexer
- L144 _public prototype_ `void RemoveReferenceFromKey(int32 KeyIndex, int32 ReferenceIndex, int32 KeyChannelIndex = 0);` — Remove reference from key. This will take immediate effect.
- L151 _public prototype_ `void AddReferenceToKey(int32 KeyIndex, int32 ReferenceIndex, int32 KeyChannelIndex = 0);` — Add a reference to a key. This will be queued and take effect in batch when an affected key is looked up. This is preferable to regenerating the index entirely.
- L156 _public function_ `void Suspend()` — Suspend indexing until the next rebuild
- L161 _public function_ `void Resume()` — Resume indexing and mark indexer as stale, but do not force an immediate rebuild
- L170 _public prototype_ `void ForceRebuild();` — Force the indexer to be completely rebuilt.
- L175 _public prototype_ `void Build();` — Build any stale indices
- L179 _private prototype_ `void UpdatePerChannelIndices();` — Ensure that the right number of per channel indices are allocated
- L182 _private prototype_ `void BuildIndex(int32 Index);` — Incrementally builds the index based on the lists of stale keys and referencers
- L185 _private prototype_ `void RebuildIndex(int32 Index);` — Does a full rebuild of the index from scratch, directly from referencing attributes
- L188 _private prototype_ `void ConditionalBuild(int32 KeyIndex, int32 KeyChannelIndex);` — Performs an incremental build if the specified key is stale
- L191 _private prototype_ `void AddUnchunked(int32 KeyIndex, int32 ReferenceIndex, int32 KeyChannelIndex = 0);` — Add a reference to a key in unchunked mode
- L194 _private function_ `int32 GetChunkForKey(int32 ElementIndex) const` — Return the chunk index relating to this key index
- L201 _private function_ `int32 GetChunkElementForKey(int32 ElementIndex) const` — Return the chunk element index relating to this key index
- L208 _private function_ `int32 GetChunkSize() const` — Return the currently configured chunk size
- L211 _private function_ `int32 GetNumChunksForKeys(int32 NumElements) const` — Return the number of chunks required to accommodate the specified number of keys
- L304 _private member_ `TArray<FIndexPerChannel> PerChannelIndices;`
- L307 _private member_ `const FMeshElementChannels* ReferencedElementType;` — The element type used as the key for this index
- L310 _private member_ `TMeshAttributesRef<int, TArrayView<const int32>> ReferencingAttributeRef;` — The attribute ref used to reference the above key
- L313 _private member_ `int32 InitialSize = 1;` — The initial size for key chunks
- L316 _private member_ `uint32 ChunkBits = 8;` — Chunk size
- L317 _private member_ `uint32 ChunkMask = (1U << ChunkBits) - 1;`
- L320 _private member_ `bool bSuspended = false;` — Whether indexing is temporarily suspended
- L323 _private member_ `bool bEverythingStale = true;` — True if the entire data needs to be rebuilt

#### struct `FMeshElementIndexer::FChunk`  
`struct FChunk`  
_L221-290_
- desc: We are modelling a one-to-many relationship, where a single key yields multiple indices, e.g. obtaining all the vertex instances which reference a given vertex ID (the key). We consolidate the data into chunks, each representing a set number of keys. This provides a balance between the number of separate allocations, and the cost of inserting a new value at a key.
- L223 _public function_ `FChunk(int32 InitialSize, int32 ChunkSize)`
- L249 _public prototype_ `bool Add(int32 Index, int32 Value);` — Add a value to the chunk at the given index
- L252 _public prototype_ `bool AddUnsorted(int32 Index, int32 Value);` — Add a value to the chunk at the given index, without inserting it in sorted order
- L255 _public prototype_ `bool Remove(int32 Index, int32 Value);` — Remove a value from the chunk at the given index
- L258 _public prototype_ `bool Contains(int32 Index, int32 Value) const;` — Determine whether a value exists at the given index
- L261 _public prototype_ `void Sort(int32 Index);` — Sort values at the given index
- L264 _public function_ `TArrayView<const int32> Get(int32 Index) const` — Get the range of data corresponding to this element
- L272 _public function_ `template <typename ElementIDType, typename TEnableIf<TIsDerivedFrom<ElementIDType, FElementID>::Value, int>::Type = 0> TArrayView<const ElementIDType> Get(int32 Index) const`
- L281 _public member_ `TArray<int32> Data;` — All the data for this chunk
- L287 _public member_ `TArray<int32, TInlineAllocator<1>> StartIndex;` — This is how we determine the location and size of a given key's data in the consolidated data. Note: deleting a value will not shrink the data.
- L288 _public member_ `TArray<int32, TInlineAllocator<1>> Count;`
- L289 _public member_ `TArray<int32, TInlineAllocator<1>> MaxCount;`

#### struct `FMeshElementIndexer::FIndexPerChannel`  
`struct FIndexPerChannel`  
_L292-302_
- L295 _public member_ `TArray<FChunk> Chunks;` — List of chunks for the keyed data
- L298 _public member_ `TSet<int32> StaleKeyIndices;` — List of keys which need to be rebuilt
- L301 _public member_ `TSet<int32> StaleReferencerIndices;` — List of referencers which should be examined to rebuild the index

### `Source/Runtime/MeshDescription/Public/MeshElementRemappings.h` (Public)


#### struct `FElementIDRemappings`  
`struct FElementIDRemappings`  
_L11-62_
- desc: This is a structure which holds the ID remappings returned by a Compact operation, or passed to a Remap operation.
- L13 _public member_ `TSparseArray<int32> NewVertexIndexLookup;`
- L14 _public member_ `TSparseArray<int32> NewVertexInstanceIndexLookup;`
- L15 _public member_ `TSparseArray<int32> NewEdgeIndexLookup;`
- L16 _public member_ `TSparseArray<int32> NewTriangleIndexLookup;`
- L17 _public member_ `TSparseArray<int32> NewUVIndexLookup;`
- L18 _public member_ `TSparseArray<int32> NewPolygonIndexLookup;`
- L19 _public member_ `TSparseArray<int32> NewPolygonGroupIndexLookup;`
- L21 _public function_ `FVertexID GetRemappedVertexID( FVertexID VertexID ) const`
- L27 _public function_ `FVertexInstanceID GetRemappedVertexInstanceID( FVertexInstanceID VertexInstanceID ) const`
- L33 _public function_ `FEdgeID GetRemappedEdgeID( FEdgeID EdgeID ) const`
- L39 _public function_ `FUVID GetRemappedUVID( FUVID UVID ) const`
- L45 _public function_ `FTriangleID GetRemappedTriangleID( FTriangleID TriangleID ) const`
- L51 _public function_ `FPolygonID GetRemappedPolygonID( FPolygonID PolygonID ) const`
- L57 _public function_ `FPolygonGroupID GetRemappedPolygonGroupID( FPolygonGroupID PolygonGroupID ) const`

### `Source/Runtime/MeshDescription/Public/MeshTypes.h` (Public)


#### struct `FElementID`  
`struct FElementID`  
_L21-85_
- reflection: `USTRUCT(BlueprintType)`
- desc: @todo mesheditor script: BP doesn't have name spaces, so we might need a more specific display name, or just rename our various types
- L25 _public function_ `FElementID() : IDValue(INDEX_NONE)`
- L30 _public function_ `FElementID( const int32 InitIDValue ) : IDValue( InitIDValue )`
- L35 _public function_ `inline int32 GetValue() const`
- L40 _public function_ `inline operator int32() const`
- L45 _public function_ `inline bool operator==( const FElementID& Other ) const`
- L50 _public function_ `inline bool operator==( const int32 Other ) const`
- L55 _public function_ `inline bool operator!=( const FElementID& Other ) const`
- L60 _public function_ `inline bool operator!=( const int32 Other ) const`
- L65 _public function_ `FString ToString() const`
- L78 _public member_ `static const FElementID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid element ID
- L84 _protected member_ `int32 IDValue;` — `UPROPERTY(BlueprintReadOnly, Category="Editable Mesh")` — The actual mesh element index this ID represents.  Read-only.

#### struct `FVertexID`  
`struct FVertexID : public FElementID`  
_L89-115_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L93 _public function_ `FVertexID()`
- L97 _public function_ `FVertexID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L102 _public function_ `FVertexID( const int32 InitIDValue ) : FElementID( InitIDValue )`
- L114 _public member_ `static const FVertexID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid vertex ID

#### struct `FVertexInstanceID`  
`struct FVertexInstanceID : public FElementID`  
_L119-145_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L123 _public function_ `FVertexInstanceID()`
- L127 _public function_ `FVertexInstanceID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L132 _public function_ `FVertexInstanceID( const int32 InitIDValue ) : FElementID( InitIDValue )`
- L144 _public member_ `static const FVertexInstanceID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid rendering vertex ID

#### struct `FEdgeID`  
`struct FEdgeID : public FElementID`  
_L149-175_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L153 _public function_ `FEdgeID()`
- L157 _public function_ `FEdgeID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L162 _public function_ `FEdgeID( const int32 InitIDValue ) : FElementID( InitIDValue )`
- L174 _public member_ `static const FEdgeID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid edge ID

#### struct `FUVID`  
`struct FUVID : public FElementID`  
_L179-201_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L183 _public function_ `FUVID()`
- L187 _public function_ `FUVID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L192 _public function_ `FUVID( const int32 InitIDValue ) : FElementID( InitIDValue )`

#### struct `FTriangleID`  
`struct FTriangleID : public FElementID`  
_L205-231_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L209 _public function_ `FTriangleID()`
- L213 _public function_ `FTriangleID(const FElementID InitElementID) : FElementID(InitElementID.GetValue())`
- L218 _public function_ `FTriangleID( const int32 InitIDValue ) : FElementID( InitIDValue )`
- L230 _public member_ `static const FTriangleID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid edge ID

#### struct `FPolygonGroupID`  
`struct FPolygonGroupID : public FElementID`  
_L235-261_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L239 _public function_ `FPolygonGroupID()`
- L243 _public function_ `FPolygonGroupID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L248 _public function_ `FPolygonGroupID( const int32 InitIDValue ) : FElementID( InitIDValue )`
- L260 _public member_ `static const FPolygonGroupID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid section ID

#### struct `FPolygonID`  
`struct FPolygonID : public FElementID`  
_L265-291_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FElementID`
- L269 _public function_ `FPolygonID()`
- L273 _public function_ `FPolygonID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L278 _public function_ `FPolygonID( const int32 InitIDValue ) : FElementID( InitIDValue )`
- L290 _public member_ `static const FPolygonID Invalid;` — `UE_DEPRECATED(4.26, "Please use INDEX_NONE as an invalid ID.")` — Invalid polygon ID

#### Free symbols / members of external scopes

- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogMeshDescription, Log, All );`
- L70 _function_ `friend FArchive& operator<<( FArchive& Ar, FElementID& Element )`
- L107 _function_ `inline friend uint32 GetTypeHash( const FVertexID& Other )`
- L137 _function_ `inline friend uint32 GetTypeHash( const FVertexInstanceID& Other )`
- L167 _function_ `inline friend uint32 GetTypeHash( const FEdgeID& Other )`
- L197 _function_ `inline friend uint32 GetTypeHash( const FUVID& Other )`
- L223 _function_ `inline friend uint32 GetTypeHash(const FTriangleID& Other)`
- L253 _function_ `inline friend uint32 GetTypeHash( const FPolygonGroupID& Other )`
- L283 _function_ `inline friend uint32 GetTypeHash( const FPolygonID& Other )`
