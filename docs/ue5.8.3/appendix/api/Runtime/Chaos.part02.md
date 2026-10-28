# Runtime / Chaos (part 2/2)

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/ManagedArray.h` (Public)


#### class `FManagedArrayBase`  
`class FManagedArrayBase : public FNoncopyable`  
_L154-285_
- inherits: `FNoncopyable`
- desc: Managed Array Base The ManagedArrayBase allows a common base class for the the template class ManagedArray<T>. (see ManagedArray)
- L162 _protected function_ `virtual void Resize(const int32 Num)` — Protected access to array resizing. Only the managers of the Array are allowed to perform a resize. (see friend list above).
- L168 _protected function_ `virtual void Reserve(const int32 Num)` — Protected access to array reservation. Only the managers of the Array are allowed to perform a reserve. (see friend list above).
- L174 _protected prototype_ `virtual void Reorder(const TArray<int32>& NewOrder) = 0;` — Reorder elements given a new ordering. Sizes must match @param NewOrder Mapping from indices in the new array -> indices in the old array
- L181 _protected function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder)` — todo: this should really assert, but material is currently relying on both faces and vertices
- L186 _protected function_ `virtual void Init(const FManagedArrayBase& )` — Init from a predefined Array
- L191 _protected function_ `virtual void Convert(const FManagedArrayBase&)` — Convert from a predefined Array, the managed array itself should have defined its conversion procedure
- L196 _protected function_ `virtual void CopyRange(const FManagedArrayBase& ConstArray, int32 Start, int32 Stop, int32 Offset = 0)` — Copy a range of values from the ConstArray into this
- L201 _protected function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency)` — Set default values.
- L206 _protected function_ `virtual SIZE_T GetAllocatedSize() const` — Get allocated memory
- L209 _public function_ `FManagedArrayBase()`
- L214 _public prototype_ `virtual ~FManagedArrayBase() = default;`
- L216 _public function_ `FORCEINLINE void ClearDirtyFlag()`
- L221 _public function_ `FORCEINLINE_DEBUGGABLE void MarkDirty()`
- L226 _public function_ `FORCEINLINE bool IsDirty() const`
- L234 _public prototype_ `virtual void ExchangeArrays(FManagedArrayBase& Src) = 0;` — Perform a memory move between the two arrays
- L237 _public function_ `virtual void RemoveElements(const TArray<int32>& SortedDeletionList)` — Remove elements
- L243 _public function_ `virtual int32 Num() const` — The length of the array.
- L249 _public function_ `virtual int32 Max() const` — The reserved length of the array.
- L255 _public function_ `virtual void Serialize(Chaos::FChaosArchive& Ar)` — Serialization
- L261 _public function_ `virtual size_t GetTypeSize() const` — TypeSize
- L271 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32> & DeletionSet)` — Reindex - Adjust index dependent elements. Offsets is the size of the dependent group; Final is post resize of dependent group used for bounds checking on remapped indices.
- L279 _public function_ `virtual void Empty()` — Empty the array.
- L284 _private member_ `bool bIsDirty;`

#### class `TManagedArrayBase`  
`template<class InElementType> class TManagedArrayBase : public FManagedArrayBase`  
_L309-659_
- inherits: `FManagedArrayBase`
- desc: Managed Array Restricts clients ability to resize the array external to the containing manager.
- L314 _public typedef_ `using ElementType = InElementType;`
- L320 _public function_ `FORCEINLINE TManagedArrayBase()` — Constructor (default) Build an empty shared array
- L327 _public function_ `FORCEINLINE TManagedArrayBase(const TArray<ElementType>& Other) : Array(Other)` — Constructor (TArray)
- L334 _public prototype_ `FORCEINLINE TManagedArrayBase(const TManagedArrayBase<ElementType>& Other) = delete;` — Copy Constructor (default)
- L339 _public function_ `FORCEINLINE TManagedArrayBase(TManagedArrayBase<ElementType>&& Other) : Array(MoveTemp(Other.Array))` — Move Constructor
- L342 _public function_ `FORCEINLINE TManagedArrayBase(TArray<ElementType>&& Other) : Array(MoveTemp(Other))`
- L349 _public function_ `FORCEINLINE TManagedArrayBase& operator=(TManagedArrayBase<ElementType>&& Other)` — Assignment operator
- L354 _public function_ `FORCEINLINE TManagedArrayBase& operator=(TArray<ElementType>&& Other)`
- L366 _public prototype_ `virtual ~TManagedArrayBase() = default;` — Virtual Destructor
- L369 _public function_ `virtual void RemoveElements(const TArray<int32>& SortedDeletionList) override`
- L397 _public function_ `virtual void Init(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L407 _public function_ `virtual SIZE_T GetAllocatedSize() const override`
- L415 _public function_ `virtual void CopyRange(const FManagedArrayBase& ConstArray, int32 Start, int32 Stop, int32 Offset = 0) override` — Copy from a predefined Array of matching type
- L428 _public function_ `void Fill(const ElementType& Value)` — Fill the array with \p Value.
- L441 _public function_ `virtual void ExchangeArrays(FManagedArrayBase& NewArray) override`
- L455 _public function_ `FORCEINLINE ElementType & operator[](int Index)` — Returning a reference to the element at index. @returns Array element reference
- L464 _public function_ `FORCEINLINE const ElementType & operator[](int Index) const`
- L474 _public function_ `FORCEINLINE const TArray<ElementType>& GetConstArray()` — Helper function for returning the internal const array @returns const array of all the elements
- L479 _public function_ `FORCEINLINE const TArray<ElementType>& GetConstArray() const`
- L489 _public function_ `FORCEINLINE ElementType* GetData()` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if ArrayMax == 0.
- L499 _public function_ `FORCEINLINE const ElementType * GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if ArrayMax == 0.
- L509 _public function_ `FORCEINLINE size_t GetTypeSize() const override` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L519 _public function_ `FORCEINLINE int32 Num() const override` — Returning the size of the array @returns Array size
- L524 _public function_ `FORCEINLINE int32 Max() const override`
- L529 _public function_ `FORCEINLINE bool Contains(const ElementType& Item) const`
- L537 _public function_ `int32 Find(const ElementType& Item) const` — Find first index of the element
- L545 _public function_ `int32 Count(const ElementType& Item) const` — Count the number of entries match \p Item.
- L558 _public function_ `FORCEINLINE bool IsValidIndex(int32 Index) const` — return true if index is in array range. @param Index Index to check.
- L568 _public function_ `FORCEINLINE void RangeCheck(int32 Index) const` — Checks if index is in array range. @param Index Index to check.
- L578 _public function_ `virtual void Serialize(Chaos::FChaosArchive& Ar)` — Serialization Support @param Chaos::FChaosArchive& Ar
- L597 _public function_ `FORCEINLINE uint32 GetTypeHash() const` — This hash is using HashCombineFast and should not be serialized!
- L602 _public typedef_ `typedef typename TArray<InElementType>::RangedForIteratorType RangedForIteratorType;`
- L603 _public typedef_ `typedef typename TArray<InElementType>::RangedForConstIteratorType RangedForConstIteratorType;`
- L609 _public function_ `FORCEINLINE RangedForIteratorType begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L610 _public function_ `FORCEINLINE RangedForConstIteratorType begin() const`
- L611 _public function_ `FORCEINLINE RangedForIteratorType end ()`
- L612 _public function_ `FORCEINLINE RangedForConstIteratorType end () const`
- L620 _protected function_ `void Resize(const int32 Size)` — Protected Resize to prevent external resizing of the array @param New array size.
- L630 _protected function_ `void Reserve(const int32 Size)` — Protected Reserve to prevent external reservation of the array @param New array reservation size.
- L639 _protected function_ `void Empty()` — Protected clear to prevent external clearing of the array
- L644 _protected function_ `void Reorder(const TArray<int32>& NewOrder) override`
- L657 _protected member_ `TArray<InElementType> Array;`

#### class `FManagedBitArrayBase`  
`class FManagedBitArrayBase : public FManagedArrayBase`  
_L731-1072_
- inherits: `FManagedArrayBase`
- desc: BitArray Managed Array base
- L736 _public function_ `FORCEINLINE FManagedBitArrayBase()`
- L739 _public prototype_ `FORCEINLINE FManagedBitArrayBase(const FManagedBitArrayBase& Other) = delete;`
- L741 _public function_ `FORCEINLINE FManagedBitArrayBase(FManagedBitArrayBase&& Other) : Array(MoveTemp(Other.Array))`
- L745 _public function_ `FORCEINLINE FManagedBitArrayBase& operator=(FManagedBitArrayBase&& Other)`
- L750 _public function_ `FORCEINLINE FManagedBitArrayBase& operator=(TBitArray<>&& Other)`
- L758 _public prototype_ `virtual ~FManagedBitArrayBase() = default;`
- L760 _public function_ `virtual void RemoveElements(const TArray<int32>& SortedDeletionList) override`
- L787 _public function_ `virtual void Init(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L800 _public function_ `virtual SIZE_T GetAllocatedSize() const override`
- L808 _public function_ `virtual void CopyRange(const FManagedArrayBase& ConstArray, int32 Start, int32 Stop, int32 Offset = 0) override` — Copy from a predefined Array of matching type
- L824 _public function_ `void Fill(const bool Value)` — Fill the array with \p Value.
- L832 _public function_ `void Fill(const TArray<bool>& BoolArray)`
- L841 _public function_ `virtual void ExchangeArrays(FManagedArrayBase& NewArray) override`
- L855 _public function_ `FORCEINLINE bool IsValidIndex(int32 Index) const` — return true if index is in array range. @param Index Index to check.
- L865 _public function_ `FORCEINLINE FBitReference operator[](int Index)` — Returning a reference to the element at index. @returns Array element reference
- L874 _public function_ `FORCEINLINE const FConstBitReference operator[](int Index) const`
- L884 _public function_ `FORCEINLINE const TBitArray<>& GetConstArray()` — Helper function for returning the internal const array @returns const array of all the elements
- L889 _public function_ `FORCEINLINE const TBitArray<>& GetConstArray() const`
- L898 _public function_ `TArray<bool> GetAsBoolArray() const` — Helper function to convert the bitArray to a bool array this is creating a new array and copy convert each bit to a bool
- L935 _public function_ `FORCEINLINE size_t GetTypeSize() const override` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L946 _public function_ `FORCEINLINE int32 Num() const override` — Returning the size of the array @returns Array size
- L951 _public function_ `FORCEINLINE int32 Max() const override`
- L956 _public function_ `FORCEINLINE bool Contains(const bool Item) const`
- L964 _public function_ `int32 Find(const bool Item) const` — Find first index of the element
- L972 _public function_ `int32 Count(const bool Item) const` — Count the number of entries match \p Item.
- L983 _public function_ `FORCEINLINE void RangeCheck(int32 Index) const` — Checks if index is in array range. @param Index Index to check.
- L993 _public function_ `virtual void Serialize(Chaos::FChaosArchive& Ar)` — Serialization Support @param Chaos::FChaosArchive& Ar
- L1027 _protected function_ `void Resize(const int32 Size)` — Protected Resize to prevent external resizing of the array @param New array size.
- L1045 _protected function_ `void Reserve(const int32 Size)` — Protected Reserve to prevent external reservation of the array @param New array reservation size.
- L1054 _protected function_ `void Empty()` — Protected clear to prevent external clearing of the array
- L1059 _protected function_ `void Reorder(const TArray<int32>& NewOrder) override`
- L1071 _protected member_ `TBitArray<> Array;`

#### class `TManagedArray`  
`template<class InElementType> class TManagedArray : public TManagedArrayBase<InElementType>`  
_L1097-1124_
- inherits: `TManagedArrayBase<InElementType>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<int32> : public TManagedArrayBase<int32>`  
_L1127-1195_
- inherits: `TManagedArrayBase<int32>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<FTransform3f> : public TManagedArrayBase<FTransform3f>`  
_L1199-1232_
- inherits: `TManagedArrayBase<FTransform3f>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<bool> : public FManagedBitArrayBase`  
_L1235-1254_
- inherits: `FManagedBitArrayBase`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<TSet<int32>> : public TManagedArrayBase<TSet<int32>>`  
_L1257-1322_
- inherits: `TManagedArrayBase<TSet<int32>>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<FIntVector> : public TManagedArrayBase<FIntVector>`  
_L1325-1398_
- inherits: `TManagedArrayBase<FIntVector>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<FIntVector2> : public TManagedArrayBase<FIntVector2>`  
_L1401-1474_
- inherits: `TManagedArrayBase<FIntVector2>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<TArray<FIntVector2>> : public TManagedArrayBase<TArray<FIntVector2>>`  
_L1477-1547_
- inherits: `TManagedArrayBase<TArray<FIntVector2>>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<FIntVector4> : public TManagedArrayBase<FIntVector4>`  
_L1550-1623_
- inherits: `TManagedArrayBase<FIntVector4>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<TArray<int32>> : public TManagedArrayBase<TArray<int32>>`  
_L1626-1688_
- inherits: `TManagedArrayBase<TArray<int32>>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### class `TManagedArray`  
`template<> class TManagedArray<TArray<FIntVector3>> : public TManagedArrayBase<TArray<FIntVector3>>`  
_L1691-1762_
- inherits: `TManagedArrayBase<TArray<FIntVector3>>`
- L1100 _public function_ `FORCEINLINE TManagedArray()`
- L1103 _public function_ `FORCEINLINE TManagedArray(const TArray<InElementType>& Other) : TManagedArrayBase<InElementType>(Other)`
- L1107 _public function_ `FORCEINLINE TManagedArray(TManagedArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1111 _public function_ `FORCEINLINE TManagedArray(TArray<InElementType>&& Other) : TManagedArrayBase<InElementType>(MoveTemp(Other))`
- L1115 _public function_ `FORCEINLINE TManagedArray& operator=(TManagedArray<InElementType>&& Other)`
- L1121 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<InElementType>& Other) = delete;`
- L1123 _public prototype_ `virtual ~TManagedArray() = default;`
- L1135 _public function_ `FORCEINLINE TManagedArray(const TArray<int32>& Other) : TManagedArrayBase<int32>(Other)`
- L1139 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<int32>& Other) = delete;`
- L1140 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<int32>&& Other) = default;`
- L1141 _public function_ `FORCEINLINE TManagedArray(TArray<int32>&& Other) : TManagedArrayBase<int32>(MoveTemp(Other))`
- L1144 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<int32>&& Other) = default;`
- L1148 _public function_ `virtual void Reindex(const TArray<int32> & Offsets, const int32 & FinalSize, const TArray<int32> & SortedDeletionList, const TSet<int32>& DeletionSet) override`
- L1172 _public function_ `virtual void ReindexFromLookup(const TArray<int32>& InverseNewOrder) override`
- L1185 _public function_ `virtual void SetDefaults(uint32 StartSize, uint32 NumElements, bool bHasGroupIndexDependency) override`
- L1205 _public function_ `FORCEINLINE TManagedArray(const TArray<FTransform3f>& Other) : TManagedArrayBase<FTransform3f>(Other)`
- L1209 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FTransform3f>& Other) = delete;`
- L1210 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FTransform3f>&& Other) = default;`
- L1211 _public function_ `FORCEINLINE TManagedArray(TArray<FTransform3f>&& Other) : TManagedArrayBase<FTransform3f>(MoveTemp(Other))`
- L1214 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FTransform3f>&& Other) = default;`
- L1222 _protected function_ `virtual void Convert(const FManagedArrayBase& NewArray) override` — Init from a predefined Array of matching type
- L1265 _public function_ `FORCEINLINE TManagedArray(const TArray<TSet<int32>>& Other) : TManagedArrayBase< TSet<int32> >(Other)`
- L1269 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TSet<int32>>& Other) = delete;`
- L1270 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TSet<int32>>&& Other) = default;`
- L1271 _public function_ `FORCEINLINE TManagedArray(TArray<TSet<int32>>&& Other) : TManagedArrayBase<TSet<int32>>(MoveTemp(Other))`
- L1274 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TSet<int32>>&& Other) = default;`
- L1333 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector>& Other) : TManagedArrayBase<FIntVector>(Other)`
- L1337 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector>& Other) = delete;`
- L1338 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector>&& Other) = default;`
- L1339 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector>&& Other) : TManagedArrayBase<FIntVector>(MoveTemp(Other))`
- L1342 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector>&& Other) = default;`
- L1409 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector2>& Other) : TManagedArrayBase<FIntVector2>(Other)`
- L1413 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector2>& Other) = delete;`
- L1414 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector2>&& Other) = default;`
- L1415 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector2>&& Other) : TManagedArrayBase<FIntVector2>(MoveTemp(Other))`
- L1418 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector2>&& Other) = default;`
- L1485 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<FIntVector2>>& Other) : TManagedArrayBase<TArray<FIntVector2>>(Other)`
- L1489 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<FIntVector2>>& Other) = delete;`
- L1490 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1491 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<FIntVector2>>&& Other) : TManagedArrayBase<TArray<FIntVector2>>(MoveTemp(Other))`
- L1494 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<FIntVector2>>&& Other) = default;`
- L1558 _public function_ `FORCEINLINE TManagedArray(const TArray<FIntVector4>& Other) : TManagedArrayBase<FIntVector4>(Other)`
- L1562 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<FIntVector4>& Other) = delete;`
- L1563 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<FIntVector4>&& Other) = default;`
- L1564 _public function_ `FORCEINLINE TManagedArray(TArray<FIntVector4>&& Other) : TManagedArrayBase<FIntVector4>(MoveTemp(Other))`
- L1567 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<FIntVector4>&& Other) = default;`
- L1634 _public function_ `FORCEINLINE TManagedArray(const TArray<TArray<int32>>& Other) : TManagedArrayBase<TArray<int32>>(Other)`
- L1638 _public prototype_ `FORCEINLINE TManagedArray(const TManagedArray<TArray<int32>>& Other) = delete;`
- L1639 _public prototype_ `FORCEINLINE TManagedArray(TManagedArray<TArray<int32>>&& Other) = default;`
- L1640 _public function_ `FORCEINLINE TManagedArray(TArray<TArray<int32>>&& Other) : TManagedArrayBase<TArray<int32>>(MoveTemp(Other))`
- L1643 _public prototype_ `FORCEINLINE TManagedArray& operator=(TManagedArray<TArray<int32>>&& Other) = default;`
- L1696 _public prototype_ `TManagedArray() = default;`
- L1698 _public function_ `TManagedArray(const TArray<TArray<FIntVector3>>& Other) : TManagedArrayBase<TArray<FIntVector3>>(Other)`
- L1702 _public prototype_ `TManagedArray(const TManagedArray<TArray<FIntVector3>>& Other) = delete;`
- L1703 _public prototype_ `TManagedArray(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1704 _public function_ `TManagedArray(TArray<TArray<FIntVector3>>&& Other) : TManagedArrayBase<TArray<FIntVector3>>(MoveTemp(Other))`
- L1708 _public prototype_ `TManagedArray& operator=(TManagedArray<TArray<FIntVector3>>&& Other) = default;`
- L1710 _public prototype_ `virtual ~TManagedArray() override = default;`

#### Free symbols / members of external scopes

- L21 _function_ `template <typename T> void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<T>& Array)`
- L27 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FVector3f>& Array)` — Note: see TArray::BulkSerialize for requirements
- L32 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FGuid>& Array)`
- L37 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FIntVector>& Array)`
- L42 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FVector2f>& Array)`
- L47 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<float>& Array)`
- L52 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FQuat4f>& Array)`
- L57 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<bool>& Array)`
- L62 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<int32>& Array)`
- L67 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<uint8>& Array)`
- L72 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FUintVector2>& Array)`
- L77 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FIntVector2>& Array)`
- L82 _function_ `inline void TryBulkSerializeManagedArray(Chaos::FChaosArchive& Ar, TArray<FIntVector4>& Array)`
- L91 _namespace_ `namespace ManagedArrayTypeSize`
- L94 _function_ `template<typename T> inline SIZE_T GetAllocatedSize(const T& Value)` (scope `ManagedArrayTypeSize`)
- L100 _function_ `template<typename T> inline SIZE_T GetAllocatedSize(const TArray<T>& Array)` (scope `ManagedArrayTypeSize`)
- L106 _function_ `template<typename T> inline SIZE_T GetAllocatedSize(const TBitArray<>& Array)` (scope `ManagedArrayTypeSize`)
- L112 _function_ `template<typename T> inline SIZE_T GetAllocatedSize(const TSet<T>& Set)` (scope `ManagedArrayTypeSize`)
- L118 _function_ `template<typename T> inline SIZE_T GetAllocatedSize(const TUniquePtr<T>& Ptr)` (scope `ManagedArrayTypeSize`)
- L124 _function_ `template<typename T> inline SIZE_T GetAllocatedSize(const TRefCountPtr<T>& Ptr)` (scope `ManagedArrayTypeSize`)
- L130 _function_ `template<typename T, ESPMode Mode> inline SIZE_T GetAllocatedSize(const TSharedPtr<T, Mode>& Ptr)` (scope `ManagedArrayTypeSize`)
- L135 _function_ `inline SIZE_T GetAllocatedSize(const Chaos::FImplicitObject3* ImplicitObjectPtr)` (scope `ManagedArrayTypeSize`)
- L140 _function_ `inline SIZE_T GetAllocatedSize(const Chaos::FBVHParticlesFloat3& BVHParticles)` (scope `ManagedArrayTypeSize`)
- L291 _prototype_ `template <typename T> void InitHelper(TArray<T>& Array, const TManagedArrayBase<T>& NewTypedArray, int32 Size);`
- L293 _prototype_ `template <typename T> void InitHelper(TArray<TUniquePtr<T>>& Array, const TManagedArrayBase<TUniquePtr<T>>& NewTypedArray, int32 Size);`
- L295 _prototype_ `template <typename T> void InitHelper(TArray<TRefCountPtr<T>>& Array, const TManagedArrayBase<TRefCountPtr<T>>& NewTypedArray, int32 Size);`
- L297 _prototype_ `template <typename T> void CopyRangeHelper(TArray<T>& Target, const TManagedArrayBase<T>& Source, int32 Start, int32 Stop, int32 Offset);`
- L299 _prototype_ `template <typename T> void CopyRangeHelper(TArray<TUniquePtr<T>>& Array, const TManagedArrayBase<TUniquePtr<T>>& ConstArray, int32 Start, int32 Stop, int32 Offset);`
- L301 _prototype_ `template <typename T> void CopyRangeHelper(TArray<TRefCountPtr<T>>& Array, const TManagedArrayBase<TRefCountPtr<T>>& ConstArray, int32 Start, int32 Stop, int32 Offset);`
- L662 _function_ `template<class T> inline uint32 GetTypeHash(const TManagedArrayBase<T>& ManagedArray)`
- L668 _function_ `template <typename T> void InitHelper(TArray<T>& Array, const TManagedArrayBase<T>& NewTypedArray, int32 Size)`
- L676 _function_ `template <typename TSrc, typename TDst> void InitHelper(TArray<TDst>& Array, const TManagedArrayBase<TSrc>& NewTypedArray, int32 Size)`
- L685 _function_ `template <typename T> void InitHelper(TArray<TUniquePtr<T>>& Array, const TManagedArrayBase<TUniquePtr<T>>& NewTypedArray, int32 Size)`
- L691 _function_ `template <typename T> void InitHelper(TArray<TRefCountPtr<T>>& Array, const TManagedArrayBase<TRefCountPtr<T>>& NewTypedArray, int32 Size)`
- L703 _function_ `template <typename T> void CopyRangeHelper(TArray<T>& Target, const TManagedArrayBase<T>& Source, int32 Start, int32 Stop, int32 Offset)`
- L714 _function_ `template <typename T> void CopyRangeHelper(TArray<TUniquePtr<T>>& Target, const TManagedArrayBase<TUniquePtr<T>>& Source, int32 Start, int32 Stop, int32 Offset)`
- L720 _function_ `template <typename T> void CopyRangeHelper(TArray<TRefCountPtr<T>>& Target, const TManagedArrayBase<TRefCountPtr<T>>& Source, int32 Start, int32 Stop, int32 Offset)`
- L1077 _macro_ `#define UNSUPPORTED_UNIQUE_ARRAY_COPIES(TYPE, NAME) \`
- L1084 _typedef_ `typedef TUniquePtr<Chaos::TGeometryParticle<Chaos::FReal, 3>> LOCAL_MA_UniqueTGeometryParticle;`
- L1087 _typedef_ `typedef TUniquePtr<Chaos::TPBDRigidParticle<Chaos::FReal, 3>> LOCAL_MA_UniqueTPBDRigidParticle;`
- L1090 _typedef_ `typedef TUniquePtr<Chaos::FBVHParticles, TDefaultDelete<Chaos::FBVHParticles>> LOCAL_MA_UniqueTBVHParticles;`
- L1093 _typedef_ `typedef TUniquePtr<TArray<UE::Math::TVector<float>>> LOCAL_MA_UniqueTArrayTVector;`

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/ManagedArrayAccessor.h` (Public)


#### enum `ManageArrayAccessor::EPersistencePolicy`  
`enum class EPersistencePolicy : uint8`  
_L7-11_
- L9 _public enumerator_ `KeepExistingPersistence`
- L10 _public enumerator_ `MakePersistent`

#### struct `TManagedArrayAccessor`  
`template <typename T> struct TManagedArrayAccessor`  
_L19-214_
- desc: this class wraps a managed array this provides a convenient API for optional attributes in a collection facade
- L22 _public function_ `TManagedArrayAccessor(FManagedArrayCollection& InCollection, const FName& InAttributeName, const FName& InAttributeGroup, const FName& InDefaultGroupDependency = NAME_None) : ConstCollection(InCollection) , Collection(&InCollection) , Name(InAttributeName) , Group(InAttributeGroup) , DefaultGroupDependency(InDefaultGroupDependency) , AttributeArray(InCollection.FindAttributeTyped<T>(InAttributeName, InAttributeGroup)) , ConstAttributeArray(AttributeArray)`
- L32 _public function_ `TManagedArrayAccessor(const FManagedArrayCollection& InCollection, const FName& InAttributeName, const FName& InAttributeGroup, const FName& InDefaultGroupDependency = NAME_None) : ConstCollection(InCollection) , Collection(nullptr) , Name(InAttributeName) , Group(InAttributeGroup) , DefaultGroupDependency(InDefaultGroupDependency) , AttributeArray(nullptr) , ConstAttributeArray(InCollection.FindAttributeTyped<T>(InAttributeName, InAttributeGroup))`
- L42 _public function_ `const FManagedArrayCollection& GetConstCollection() const`
- L43 _public function_ `FManagedArrayCollection* GetCollection()`
- L45 _public function_ `FName GetName() const`
- L47 _public function_ `FName GetGroup() const`
- L49 _public function_ `FName GetGroupDependency() const`
- L51 _public function_ `bool IsConst() const`
- L53 _public function_ `bool IsValid() const`
- L55 _public function_ `bool IsPersistent() const`
- L57 _public function_ `bool IsValidIndex(int32 Index) const`
- L63 _public function_ `int32 AddElements(int32 NumElements) const`
- L69 _public function_ `void RemoveElements(int32 NumElements, int32 Position)`
- L75 _public function_ `void SetNumElements(int32 InNumElements)`
- L94 _public function_ `const T& operator[](int32 Index) const` — array style accessor
- L101 _public function_ `const TManagedArray<T>& Get() const` — get the attribute for read only
- L108 _public function_ `const TManagedArray<T>* Find() const` — find the attribute for read only
- L114 _public function_ `TManagedArray<T>& Modify()` — get the attribute for modification
- L122 _public function_ `void ModifyAt(int32 Index, const T& NewValue)` — per index modification
- L130 _public function_ `TManagedArray<T>& Add(ManageArrayAccessor::EPersistencePolicy PersistencePolicy = ManageArrayAccessor::EPersistencePolicy::MakePersistent, FName InGroupDependency = FName(NAME_None))` — add the attribute if it does not exists yet
- L157 _public function_ `void AddAndFill(const T& Value, ManageArrayAccessor::EPersistencePolicy PersistencePolicy = ManageArrayAccessor::EPersistencePolicy::MakePersistent, FName InGroupDependency = FName(NAME_None))` — add and fill the attribute if it does not exist yet
- L170 _public function_ `void Fill(const T& Value)` — Fill the attribute with a specific value
- L180 _public function_ `void Copy(const TManagedArrayAccessor<T>& FromAttribute )` — copy from another attribute ( create if necessary )
- L189 _public function_ `void Remove()`
- L196 _public function_ `int32 Num() const`
- L206 _private member_ `const FManagedArrayCollection& ConstCollection;` — the non-const Collection will be null if the accessor is const, while ConstCollection is always set
- L207 _private member_ `FManagedArrayCollection* Collection = nullptr;`
- L209 _private member_ `FName Name;`
- L210 _private member_ `FName Group;`
- L211 _private member_ `const FName DefaultGroupDependency;` — Will be used by Add if a non-NAME_None group dependency is specified by that method.
- L212 _private member_ `TManagedArray<T>* AttributeArray;`
- L213 _private member_ `const TManagedArray<T>* ConstAttributeArray;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace ManageArrayAccessor`

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/ManagedArrayCollection.h` (Public)


#### struct `FAttributeAndGroupId`  
`struct FAttributeAndGroupId`  
_L21-30_
- L23 _public member_ `FName AttributeName;`
- L24 _public member_ `FName GroupName;`
- L26 _public function_ `bool operator==(const FAttributeAndGroupId& Other) const`

#### struct `FManagedArrayCollection`  
`struct FManagedArrayCollection`  
_L55-836_
- reflection: `USTRUCT()`
- desc: ManagedArrayCollection The ManagedArrayCollection is an entity system that implements a homogeneous, dynamically allocated, manager of primitive TArray structures. The collection stores groups of TArray attributes, where each attribute within a group is the same length. The collection will make use of the TManagedArray class, providing limited interaction with the underlying TArray. For example: FManagedArrayCollection* Collection(NewObject<FManagedArrayCollection>()); Collection->AddElements(10, "GroupBar"); // Create a group GroupBar and add 10 elements. Collection->AddAttribute<FVector3f>("AttributeFoo", "GroupBar"); // Add a FVector array named AttributeFoo to GroupBar. TManagedArray<FVector3f>&  Foo = Collection->GetAttribute<FVector3f>("AttributeFoo", "GroupBar"); // Get AttributeFoo for (int32 i = 0; i < Foo.Num(); i++) { Foo[i] = FVector(i, i, i); // Update AttribureFoo's elements }
- L63 _public prototype_ `FManagedArrayCollection();`
- L64 _public prototype_ `virtual ~FManagedArrayCollection();`
- L66 _public prototype_ `FManagedArrayCollection(const FManagedArrayCollection& In);`
- L67 _public prototype_ `FManagedArrayCollection& operator=(const FManagedArrayCollection& In);`
- L68 _public prototype_ `FManagedArrayCollection(FManagedArrayCollection&&);`
- L69 _public prototype_ `FManagedArrayCollection& operator=(FManagedArrayCollection&&);`
- L71 _public prototype_ `bool operator==(const FManagedArrayCollection& Other) const;` — Slow, required for comparing to a default collection during UPROPERTY serialization
- L73 _public member_ `static int8 Invalid;`
- L74 _public typedef_ `typedef EManagedArrayType EArrayType;`
- L119 _public function_ `static FName StaticType()` — Type name for this class.
- L121 _public function_ `virtual bool IsAType(FName InTypeName) const`
- L124 _public function_ `template<typename T> bool IsA()`
- L127 _public function_ `template<class T> T* Cast()`
- L130 _public function_ `template<class T> const T* Cast() const`
- L139 _public function_ `template<typename T> TManagedArray<T>& AddAttribute(FName Name, FName Group, FConstructionParameters Parameters = FConstructionParameters())` — Add an attribute of Type(T) to the group @param Name - The name of the attribute @param Group - The group that manages the attribute @return reference to the created ManagedArray<T>
- L155 _public function_ `template<typename T> TManagedArray<T>* FindOrAddAttributeTyped(FName Name, FName Group, FConstructionParameters Parameters = FConstructionParameters())` — Add an attribute of Type(T) to the group or find the existing attribute with the same name and type. @param Name - The name of the attribute @param Group - The group that manages the attribute @return pointer to the added/found managed array. If there is a type mismatch with an existing attribute, returns nullptr.
- L170 _public function_ `template<class T = FManagedArrayCollection> T* NewCopy() const` — Duplicate the ManagedArrayCollection as the specified templated type @return unowned pointer to new collection.
- L190 _public function_ `template<typename T> void AddExternalAttribute(FName Name, FName Group, TManagedArray<T>& ValueIn, FConstructionParameters Parameters = FConstructionParameters())` — Add an external attribute of Type(T) to the group for size management. Lifetime is managed by the caller, must make sure the array is alive when the collection is @param Name - The name of the attribute @param Group - The group that manages the attribute @param ValueIn - The array to be managed
- L218 _public prototype_ `void AddGroup(FName Group);` — Create a group on the collection. Adding attribute will also create unknown groups. @param Group - The group name
- L223 _public prototype_ `int32 NumAttributes(FName Group) const;` — Returns the number of attributes in a group.
- L229 _public prototype_ `TArray<FName> AttributeNames(FName Group) const;` — List all the attributes in a group names. @return list of group names
- L237 _public prototype_ `int32 AddElements(int32 NumberElements, FName Group);` — Add elements to a group @param NumberElements - The number of array entries to add @param Group - The group to append entries to. @return starting index of the new ManagedArray<T> entries.
- L246 _public prototype_ `int32 InsertElements(int32 NumberElements, int32 Position, FName Group);` — Insert elements to a group @param NumberElements - The number of array entries to add @param Position - The position in the managed array where to insert entries. @param Group - The group to append entries to. @return starting index of the new ManagedArray<T> entries (same as Position).
- L252 _public prototype_ `virtual void Append(const FManagedArrayCollection& Collection);` — Append Collection and reindex dependencies on this collection. @param InCollection : Collection to add.
- L261 _public function_ `template<typename T> TManagedArray<T>* FindAttribute(FName Name, FName Group)` — Returns attribute(Name) of Type(T) from the group @param Name - The name of the attribute @param Group - The group that manages the attribute @return ManagedArray<T> &
- L272 _public function_ `template<typename T> const TManagedArray<T>* FindAttribute(FName Name, FName Group) const`
- L288 _public function_ `template<typename T> TManagedArray<T>* FindAttributeTyped(FName Name, FName Group)` — Returns attribute(Name) of Type(T) from the group if and only if the types of T and the array match @param Name - The name of the attribute @param Group - The group that manages the attribute @return ManagedArray<T> &
- L301 _public function_ `template<typename T> const TManagedArray<T>* FindAttributeTyped(FName Name, FName Group) const`
- L321 _public function_ `template<typename T> TManagedArray<T>& ModifyAttribute(FName Name, FName Group)` — Returns attribute access of Type(T) from the group for modification this will mark the collection dirty @param Name - The name of the attribute @param Group - The group that manages the attribute @return ManagedArray<T> &
- L335 _public function_ `template<typename T> TManagedArray<T>* ModifyAttributeTyped(FName Name, FName Group)` — Returns attribute access of Type(T) from the group for modification if and only if the types of T and the array match this will mark the collection dirty @param Name - The name of the attribute @param Group - The group that manages the attribute @return ManagedArray<T> *
- L354 _public function_ `template<typename T> const TManagedArray<T>& GetAttribute(FName Name, FName Group) const` — Returns attribute access of Type(T) from the group @param Name - The name of the attribute @param Group - The group that manages the attribute @return ManagedArray<T> &
- L363 _public function_ `virtual void Reset()` — Clear the internal data.
- L369 _public prototype_ `virtual void RemoveElements(const FName & Group, const TArray<int32> & SortedDeletionList, FProcessingParameters Params = FProcessingParameters());` — Remove the element at index and reindex the dependent arrays
- L375 _public prototype_ `virtual void MergeElements(const FName& Group, const TArray<int32>& SortedMergeList, const TArray<int32>& MergeRemapIndex, FProcessingParameters Params = FProcessingParameters());` — Merge the element indexed SortedMergeList[Idx] to the element indexed MergeRemapIndex[Idx] first redirect references of SortedMergeList[Idx] then delete
- L383 _public prototype_ `virtual void RemoveElements(const FName& Group, int32 NumberElements, int32 Position);` — Remove the elements at Position and reindex the dependent arrays @param Group - The group that manages the attributes @param NumberElements - The number of array entries to remove @param Position - The position from which to remove entries
- L391 _public prototype_ `void RemoveAttribute(FName Name, FName Group);` — Remove the attribute from the collection, and clear the memory. @param Name - The name of the attribute @param Group - The group that manages the attribute
- L398 _public prototype_ `void RemoveGroup(FName Group);` — Remove the group from the collection. @param Group - The group that manages the attribute
- L403 _public prototype_ `TArray<FName> GroupNames() const;` — List all the group names.
- L408 _public function_ `bool IsEmpty() const` — Whether the collection is ampty ( no group / no attributes )
- L418 _public prototype_ `bool HasAttribute(FName Name, FName Group) const;` — Check for the existence of a attribute @param Name - The name of the attribute @param Group - The group that manages the attribute
- L424 _public prototype_ `bool HasAttributes(const TArray<FManagedType>& Types) const;` — Check for the existence of a attribute @param TArray<ManagedType> - Attributes to search for
- L430 _public function_ `FORCEINLINE bool HasGroup(FName Group) const` — Check for the existence of a group @param Group - The group name
- L437 _public prototype_ `EArrayType GetAttributeType(FName Name, FName Group) const;` — Return attribute type @param Name - The name of the attribute @param Group - The group that manages the attribute
- L444 _public prototype_ `bool IsAttributeDirty(FName Name, FName Group) const;` — Check if an attribute is dirty @param Name - The name of the attribute @param Group - The group that manages the attribute
- L452 _public prototype_ `bool IsAttributePersistent(FName Name, FName Group) const;` — Check if an attribute is persistent - ie its data will be serialized If the attribute does not exists this will return false @param Name - The name of the attribute @param Group - The group that manages the attribute
- L457 _public prototype_ `void SetDependency(FName Name, FName Group, FName DependencyGroup, bool bAllowCircularDependency = false);`
- L464 _public prototype_ `FName GetDependency(FName Name, FName Group) const;` — Return the group index dependency for the specified attribute. @param Name - The name of the attribute @param Group - The group that manages the attribute
- L469 _public prototype_ `void RemoveDependencyFor(FName Group);`
- L476 _public prototype_ `void CopyAttribute(const FManagedArrayCollection& InCollection, FName Name, FName Group);` — Copy an attribute. Will perform an implicit group sync. Attribute must exist in both InCollection and this collection @param Name - The name of the attribute @param Group - The group that manages the attribute
- L484 _public prototype_ `void CopyAttribute(const FManagedArrayCollection& InCollection, FName SrcName, FName DestName, FName Group);` — Copy an attribute. Will perform an implicit group sync. @param SrcName - The name of the attribute being copied from @param DestName - The name of the attribute being copied to @param Group - The group that manages the attribute
- L493 _public prototype_ `void CopyAttribute(const FManagedArrayCollection& InCollection, FName SrcName, FName DestName, FName SrcGroup, FName DstGroup);` — Copy an attribute from one group to another group. Will perform an implicit group sync. @param SrcName - The name of the attribute being copied from @param DestName - The name of the attribute being copied to @param SrcGroup - The group that manages the attribute being copied from @param DstGroup - The group that manages the attribute being copied to
- L500 _public prototype_ `void CopyMatchingAttributesFrom(const FManagedArrayCollection& InCollection, const TMap<FName, TSet<FName>>* SkipList=nullptr);` — Copy attributes that match the input collection. This is a utility to easily sync collections @param InCollection - All groups from this collection found in the input will be sized accordingly @param SkipList - Group/Attrs to skip. Keys are group names, values are attributes in those groups.
- L511 _public prototype_ `void CopyMatchingAttributesFrom(const FManagedArrayCollection& FromCollection, const TArrayView<const FAttributeAndGroupId> SkipList);` — Copy attributes that match the input collection. This is a utility to easily sync collections This version is recommend to be used as it is more performant overall - it only resize the necessary groups - it takes a array view for the skip list - it has a more contained logic that reduces the number of lookups for attributes in the maps @param InCollection - All groups from this collection found in the input will be sized accordingly @param SkipList - Group/Attrs to skip. Keys are group names, values are attributes in those groups.
- L517 _public prototype_ `int32 NumElements(FName Group) const;` — Number of elements in a group @return the group size, and Zero(0) if group does not exist.
- L524 _public prototype_ `void Resize(int32 Size, FName Group);` — Resize a group @param Size - The size of the group @param Group - The group to resize
- L531 _public prototype_ `void Reserve(int32 Size, FName Group);` — Reserve a group @param Size - The size of the group @param Group - The group to reserve
- L537 _public prototype_ `void EmptyGroup(FName Group);` — Empty the group @param Group - The group to empty
- L542 _public prototype_ `virtual void ReorderElements(FName Group, const TArray<int32>& NewOrder);` — Reorders elements in a group. NewOrder must be the same length as the group.
- L556 _public function_ `void MakeDirty()` — Updated for Render ( Mark it dirty ) question: is this the right place for this?
- L557 _public function_ `void MakeClean()`
- L558 _public function_ `bool IsDirty() const`
- L563 _public prototype_ `virtual void Serialize(Chaos::FChaosArchive& Ar);` — Serialize
- L565 _public prototype_ `bool Serialize(FArchive& Ar);`
- L571 _public prototype_ `bool IsConnected(FName StartingNode, FName TargetNode);` — Cycle Checking. Search for TargetNode from the StartingNode.
- L577 _public prototype_ `FString ToString() const;` — Dump the contents to a FString
- L582 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Get allocated memory size
- L587 _public prototype_ `void GetElementSizeInfoForGroups(TArray<TPair<FName, SIZE_T>>& OutSizeInfo) const;` — Get information on the total storage required for each element in each group
- L592 _private function_ `template<typename T> void AddNewAttributeImpl(FName Name, FName Group, const FConstructionParameters& Parameters)`
- L625 _private prototype_ `TArray<int32> InsertElementsNoReorder(int32 NumberElements, int32 Position, FName Group);` — Insert elements to a group without reordering elements @param NumberElements - The number of array entries to add @param Position - The position in the managed array where to insert entries. @param Group - The group to append entries to. @return new order after insertion.
- L640 _private typedef_ `typedef TTuple<FName, FName> FKeyType;` — Mapping Key/Value The Key and Value pairs for the attribute arrays allow for grouping of array attributes based on the Name,Group pairs. Array attributes that share Group names will have the same lengths. The FKeyType is a tuple of <FName,FName> where the Get<0>() parameter is the AttributeName, and the Get<1>() parameter is the GroupName. Construction of the FKeyType will follow the following pattern: FKeyType("AttributeName","GroupName");
- L646 _private function_ `static inline FKeyType MakeMapKey(FName Name, FName Group)` — inline for linking issues
- L790 _private member_ `TMap< FKeyType, FValueType> Map;` — data is owned by the map explicitly
- L791 _private member_ `TMap< FName, FGroupInfo> GroupInfo;`
- L792 _private member_ `bool bDirty;`
- L796 _protected prototype_ `virtual void SetDefaults(FName Group, uint32 StartSize, uint32 NumElements);`
- L802 _protected function_ `virtual void MatchOptionalDefaultAttributes(const FManagedArrayCollection& InCollection)` — Virtual helper function called by CopyMatchingAttributesFrom; adds attributes 'default, but optional' attributes that are present in InCollection This is used by FGeometryCollection to make sure all UV layers are copied over by CopyMatchingAttributesFrom()
- L810 _protected prototype_ `void SyncGroupSizeFrom(const FManagedArrayCollection& InCollection, FName Group);` — Size and order a group so that it matches the group found in the input collection. @param InCollection - The collection we are ordering our group against. @param Group - The group that manages the attribute
- L818 _protected prototype_ `void SyncGroupSizeFrom(const FManagedArrayCollection& InCollection, FName SrcGroup, FName DstGroup);` — Size and order a dstgroup so that it matches the srcgroup found in the input collection. @param InCollection - The collection we are ordering our group against. @param SrcGroup - The group that manages the attribute in the input collection @param DstGroup - The group that manages the attribute in the output collection
- L823 _protected member_ `int32 Version;` — Version to indicate need for conditioning to current expected data layout during serialization loading.

#### struct `FManagedArrayCollection::FConstructionParameters`  
`struct FConstructionParameters`  
_L78-90_
- L80 _public function_ `FConstructionParameters(FName GroupIndexDependencyIn = NAME_None , bool SavedIn = true, bool bInAllowCircularDependency = false) : GroupIndexDependency(GroupIndexDependencyIn) , Saved(SavedIn) , bAllowCircularDependency(bInAllowCircularDependency)`
- L87 _public member_ `FName GroupIndexDependency;`
- L88 _public member_ `bool Saved;`
- L89 _public member_ `bool bAllowCircularDependency;`

#### struct `FManagedArrayCollection::FProcessingParameters`  
`struct FProcessingParameters`  
_L92-98_
- L94 _public function_ `FProcessingParameters() : bDoValidation(true), bReindexDependentAttibutes(true)`
- L96 _public member_ `bool bDoValidation ;`
- L97 _public member_ `bool bReindexDependentAttibutes;`

#### struct `FManagedArrayCollection::FManagedType`  
`struct FManagedType`  
_L100-107_
- L102 _public function_ `FManagedType(EManagedArrayType InType, FName InName, FName InGroup) : Type(InType), Name(InName), Group(InGroup)`
- L104 _public member_ `EManagedArrayType Type = EManagedArrayType::FNoneType;`
- L105 _public member_ `FName Name;`
- L106 _public member_ `FName Group;`

#### struct `FManagedArrayCollection::TManagedType`  
`template<class T> struct TManagedType : FManagedType`  
_L110-114_
- inherits: `FManagedType`
- L112 _public function_ `TManagedType(FName InName, FName InGroup) : FManagedType(ManagedArrayType<T>(), InName, InGroup)`

#### struct `FManagedArrayCollection::FGroupInfo`  
`struct FGroupInfo`  
_L641-644_
- L643 _public member_ `int32 Size;`

#### struct `FManagedArrayCollection::FValueType`  
`struct FValueType`  
_L652-787_
- L655 _private member_ `EArrayType ArrayType;`
- L656 _private member_ `FName GroupIndexDependency;`
- L657 _private member_ `bool bPersistent;`
- L658 _private member_ `bool bExternalValue;` — External arrays have external memory management.
- L660 _private member_ `TSharedPtr<FManagedArrayBase, ESPMode::ThreadSafe> SharedManagedArray;` — external arrays have this set this to null
- L661 _private member_ `FManagedArrayBase* ManagedArray = nullptr;`
- L669 _private function_ `template<typename T> FValueType(TUniquePtr<TManagedArray<T>>&& ArrayPtr, int32 InitialSize, FName InGroupIndexDependency, bool bInPersistent) : ArrayType(ManagedArrayType<T>()) , GroupIndexDependency(InGroupIndexDependency) , bPersistent(bInPersistent) , bExternalValue(false) , SharedManagedArray(ArrayPtr.Release()) , ManagedArray(SharedManagedArray.Get())` — Create a typed attribute the array is managed ( as opposed to being external ) and will be deleted by the destructor
- L687 _private function_ `template<typename T> FValueType(TManagedArray<T>* ExternalArrayPtr, int32 InitialSize, FName InGroupIndexDependency, bool bInPersistent) : ArrayType(ManagedArrayType<T>()) , GroupIndexDependency(InGroupIndexDependency) , bPersistent(bInPersistent) , bExternalValue(true) , SharedManagedArray(nullptr) , ManagedArray(ExternalArrayPtr)` — Create a external typed attribute the array is external and it is the responsability of the original owner to destroy it
- L699 _private prototype_ `void MakeUniqueForWrite();`
- L707 _public function_ `template <typename T> static FValueType MakeManaged(TUniquePtr<TManagedArray<T>>&& ArrayPtr, int32 InitialSize, FName InGroupIndexDependency, bool bInPersistent)` — Create a typed attribute the array is managed ( as opposed to being external ) and will be deleted by the destructor
- L713 _public function_ `template <typename T> static FValueType MakeExternal(TManagedArray<T>* ExternalArrayPtr, int32 InitialSize, FName InGroupIndexDependency, bool bInPersistent)`
- L718 _public prototype_ `FValueType();`
- L719 _public prototype_ `FValueType(const FValueType& Other);`
- L720 _public prototype_ `FValueType(FValueType&& Other);`
- L722 _public prototype_ `~FValueType();`
- L724 _public function_ `EArrayType GetArrayType() const`
- L725 _public function_ `FName GetGroupIndexDependency() const`
- L726 _public function_ `bool IsPersistent() const`
- L727 _public function_ `bool IsExternal() const`
- L728 _public function_ `bool IsDirty() const`
- L730 _public function_ `void SetGroupIndexDependency(FName NewGroupDependency)`
- L733 _public function_ `template <typename T> bool IsSameType() const`
- L736 _public function_ `template <typename T> const TManagedArray<T>* GetTypedPtr() const`
- L746 _public function_ `template <typename T> const TManagedArray<T>& GetTyped() const`
- L751 _public function_ `const FManagedArrayBase& Get() const`
- L754 _public function_ `template <typename T> TManagedArray<T>* ModifyTypedPtr()`
- L767 _public function_ `template <typename T> TManagedArray<T>& ModifyTyped()`
- L772 _public prototype_ `FManagedArrayBase& Modify();`
- L774 _public prototype_ `void Reserve(int32 ReservedSize);`
- L775 _public prototype_ `void Resize(int32 NewSize);`
- L776 _public prototype_ `void InitFrom(const FValueType& Other);`
- L777 _public prototype_ `void Exchange(FValueType& Other);`
- L778 _public prototype_ `void Convert(FValueType& Other);`
- L779 _public prototype_ `void CopyFrom(const FValueType& Other);`
- L780 _public prototype_ `void Empty();`
- L781 _public prototype_ `void RemoveGroupIndexDependency(FName Group);`
- L783 _public prototype_ `FValueType& operator=(const FValueType& Other) = delete;`
- L784 _public prototype_ `FValueType& operator=(FValueType&& Other) = delete;`
- L786 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FManagedArrayCollection> : public TStructOpsTypeTraitsBase2<FManagedArrayCollection>`  
_L838-845_
- inherits: `TStructOpsTypeTraitsBase2<FManagedArrayCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L841-844_

#### class `FManagedArrayInterface`  
`class FManagedArrayInterface`  
_L850-864_
- desc: FManagedArrayInterface
- L853 _public function_ `FManagedArrayInterface() : ManagedCollection(nullptr)`
- L854 _public function_ `FManagedArrayInterface(FManagedArrayCollection* InManagedArray) : ManagedCollection(InManagedArray)`
- L857 _public prototype_ `virtual void InitializeInterface() = 0;`
- L858 _public prototype_ `virtual void CleanInterfaceForCook() = 0;`
- L859 _public prototype_ `virtual void RemoveInterfaceAttributes() = 0;`
- L862 _protected member_ `FManagedArrayCollection* ManagedCollection;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`
- L842 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon8b5025e60103`)
- L843 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon8b5025e60103`) — Required for usage as a UPROPERTY, otherwise the reflection system won't see a difference with a default collection when serializing
- L867 _macro_ `#define MANAGED_ARRAY_COLLECTION_INTERNAL(TYPE_NAME) \`

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/ManagedArrayTypeValues.inl` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/ManagedArrayTypes.h` (Public)


#### enum `EManagedArrayType`  
`#define MANAGED_ARRAY_TYPE(a,A) F##A##Type, enum class EManagedArrayType : uint8`  
_L67-71_
- desc: General purpose EManagedArrayType definition. This defines things like EManagedArrayType::FVectorType see ManagedArrayTypeValues.inl for specific types.
- L69 _public enumerator_ `FNoneType`

#### Free symbols / members of external scopes

- L24 _function_ `inline FArchive& operator<<(FArchive& Ar, TArray<FVector3f>*& ValueIn)`
- L30 _function_ `inline FArchive& operator<<(FArchive& Ar, TUniquePtr<TArray<FVector3f>>& ValueIn)`
- L46 _function_ `inline FArchive& operator<<(FArchive& Ar, Chaos::FImplicitObject*& ValueIn)`
- L53 _function_ `template <typename T, int d, bool bPersistent> inline FArchive& operator<<(FArchive& Ar, Chaos::TPBDRigidParticleHandleImp<T, d, bPersistent>*& Particle)`
- L66 _macro_ `#define MANAGED_ARRAY_TYPE(a,A) F##A##Type,` — General purpose EManagedArrayType definition. This defines things like EManagedArrayType::FVectorType see ManagedArrayTypeValues.inl for specific types.
- L78 _prototype_ `template<class T> inline EManagedArrayType ManagedArrayType();` — ManagedArrayType<T> Templated function to return a EManagedArrayType.
- L79 _macro_ `#define MANAGED_ARRAY_TYPE(a,A) template<> inline EManagedArrayType ManagedArrayType<a>() { return EManagedArrayType::F##A##Type; }`
- L89 _function_ `inline FManagedArrayBase* NewManagedTypedArray(EManagedArrayType ArrayType)` — ManagedArrayType<T> Returns a new EManagedArray shared pointer based on passed type.
- L93 _macro_ `#define MANAGED_ARRAY_TYPE(a,A) case EManagedArrayType::F##A##Type:\`

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/RecordedTransformTrack.h` (Public)


#### struct `FSolverCollisionData`  
`struct FSolverCollisionData`  
_L14-100_
- reflection: `USTRUCT()`
- L18 _public function_ `FSolverCollisionData() : Location(FVector(0.f)) , AccumulatedImpulse(FVector(0.f)) , Normal(FVector(0.f)) , Velocity1(FVector(0.f)) , Velocity2(FVector(0.f)) , AngularVelocity1(FVector(0.f)) , AngularVelocity2(FVector(0.f)) , Mass1(0.f) , Mass2(0.f) , ParticleIndex(INDEX_NONE) , LevelsetIndex(INDEX_NONE) , ParticleIndexMesh(INDEX_NONE) , LevelsetIndexMesh(INDEX_NONE)`
- L34 _public function_ `FSolverCollisionData(FVector InLocation , FVector InAccumulatedImpulse , FVector InNormal , FVector InVelocity1 , FVector InVelocity2 , FVector InAngularVelocity1 , FVector InAngularVelocity2 , float InMass1 , float InMass2 , int32 InParticleIndex , int32 InLevelsetIndex , int32 InParticleIndexMesh , int32 InLevelsetIndexMesh) : Location(InLocation) , AccumulatedImpulse(InAccumulatedImpulse) , Normal(InNormal) , Velocity1(InVelocity1) , Velocity2(InVelocity2) , AngularVelocity1(InAngularVelocity1) , AngularVelocity2(InAngularVelocity2) , Mass1(InMass1) , Mass2(InMass2) , ParticleIndex(InParticleIndex) , LevelsetIndex(InLevelsetIndex) , ParticleIndexMesh(InParticleIndexMesh) , LevelsetIndexMesh(InLevelsetIndexMesh)`
- L63 _public member_ `FVector Location;` — `UPROPERTY()`
- L66 _public member_ `FVector AccumulatedImpulse;` — `UPROPERTY()`
- L69 _public member_ `FVector Normal;` — `UPROPERTY()`
- L72 _public member_ `FVector Velocity1;` — `UPROPERTY()`
- L75 _public member_ `FVector Velocity2;` — `UPROPERTY()`
- L78 _public member_ `FVector AngularVelocity1;` — `UPROPERTY()`
- L81 _public member_ `FVector AngularVelocity2;` — `UPROPERTY()`
- L84 _public member_ `float Mass1;` — `UPROPERTY()`
- L87 _public member_ `float Mass2;` — `UPROPERTY()`
- L90 _public member_ `int32 ParticleIndex;` — `UPROPERTY()`
- L93 _public member_ `int32 LevelsetIndex;` — `UPROPERTY()`
- L96 _public member_ `int32 ParticleIndexMesh;` — `UPROPERTY()`
- L99 _public member_ `int32 LevelsetIndexMesh;` — `UPROPERTY()`

#### struct `FSolverBreakingData`  
`struct FSolverBreakingData`  
_L103-133_
- reflection: `USTRUCT()`
- L107 _public function_ `FSolverBreakingData() : Location(FVector(0.f)) , Velocity(FVector(0.f)) , AngularVelocity(FVector(0.f)) , Mass(0.f) , ParticleIndex(INDEX_NONE) , ParticleIndexMesh(INDEX_NONE)`
- L117 _public member_ `FVector Location;` — `UPROPERTY()`
- L120 _public member_ `FVector Velocity;` — `UPROPERTY()`
- L123 _public member_ `FVector AngularVelocity;` — `UPROPERTY()`
- L126 _public member_ `float Mass;` — `UPROPERTY()`
- L129 _public member_ `int32 ParticleIndex;` — `UPROPERTY()`
- L132 _public member_ `int32 ParticleIndexMesh;` — `UPROPERTY()`

#### struct `FSolverTrailingData`  
`struct FSolverTrailingData`  
_L136-190_
- reflection: `USTRUCT()`
- L140 _public function_ `FSolverTrailingData() : Location(FVector(0.f)) , Velocity(FVector(0.f)) , AngularVelocity(FVector(0.f)) , Mass(0.f) , ParticleIndex(INDEX_NONE) , ParticleIndexMesh(INDEX_NONE)`
- L149 _public function_ `FSolverTrailingData(FVector InLocation , FVector InVelocity , FVector InAngularVelocity , float InMass , int32 InParticleIndex , int32 InParticleIndexMesh) : Location(InLocation) , Velocity(InVelocity) , AngularVelocity(InAngularVelocity) , Mass(InMass) , ParticleIndex(InParticleIndex) , ParticleIndexMesh(InParticleIndexMesh)`
- L164 _public member_ `FVector Location;` — `UPROPERTY()`
- L167 _public member_ `FVector Velocity;` — `UPROPERTY()`
- L170 _public member_ `FVector AngularVelocity;` — `UPROPERTY()`
- L173 _public member_ `float Mass;` — `UPROPERTY()`
- L176 _public member_ `int32 ParticleIndex;` — `UPROPERTY()`
- L179 _public member_ `int32 ParticleIndexMesh;` — `UPROPERTY()`

#### enum `EGeometryCollectionCacheType`  
`enum class EGeometryCollectionCacheType : uint8`  
_L193-199_
- reflection: `UENUM()`
- L195 _public enumerator_ `None`
- L196 _public enumerator_ `Record`
- L197 _public enumerator_ `Play`
- L198 _public enumerator_ `RecordAndPlay`

#### struct `FRecordedFrame`  
`struct FRecordedFrame`  
_L206-269_
- reflection: `USTRUCT()`
- desc: Structure describing necessary data to record the results of a physics simulation for rigids. Primarily for recording the results of a geometry collection simulation for later playback
- L216 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY()` — List of transforms recorded for this frame. During execution maps one-to-one with the number of particles. This is handed off for processing when written back to the collection. This processing will remove redundant transforms and populate the indices in FRecordedFrame to handle the remapping
- L223 _public member_ `TArray<int32> TransformIndices;` — `UPROPERTY()` — After processing, this will map a transform index within this frame out to a body/particle index for the component. This will map back to where the transform was before processing.
- L231 _public member_ `TArray<int32> PreviousTransformIndices;` — `UPROPERTY()` — Maps to the position in the Transforms array of the *previous* frame that this entry existed. They can move around as particles either become disabled/enabled or if a particle didn't move since the last frame. This allows us to pick up previous positions for velocities etc.
- L238 _public member_ `TArray<bool> DisabledFlags;` — `UPROPERTY()` — Per-particle list of whether or not they were disabled on this frame. #BGallagher change this to be event based - expensive on memory and beginframe iterations
- L241 _public member_ `TArray<FSolverCollisionData> Collisions;` — `UPROPERTY()`
- L244 _public member_ `TArray<FSolverBreakingData> Breakings;` — `UPROPERTY()`
- L247 _public member_ `TSet<FSolverTrailingData> Trailings;` — `UPROPERTY()`
- L250 _public member_ `float Timestamp = 0.0f;` — `UPROPERTY()`
- L252 _public function_ `void Reset(int32 InNum = 0)`

#### struct `FRecordedTransformTrack`  
`struct FRecordedTransformTrack`  
_L272-555_
- reflection: `USTRUCT()`
- L277 _public member_ `TArray<FRecordedFrame> Records;` — `UPROPERTY()`
- L279 _public function_ `float GetDt() const`
- L287 _public function_ `bool IsTimeValid(float InTime) const` — Validates that the time is within the track timestamp bounds (inclusive)
- L304 _public function_ `int32 FindLastKeyBefore(float InTime) const` — Finds the index of the key immediately before the provided time. Or the exact frame in the case of an exact time match
- L343 _public function_ `const FRecordedFrame* FindRecordedFrame(float InTime, float InTolerance = UE_SMALL_NUMBER) const` — Find a frame at InTime if available within a specified tolarance of the timestamp
- L359 _public function_ `FRecordedFrame* FindRecordedFrame(float InTime, float InTolerance = UE_SMALL_NUMBER)` — Find a frame at InTime if available within a specified tolarance of the timestamp
- L375 _public function_ `int32 FindRecordedFrameIndex(float InTime, float InTolerance = UE_SMALL_NUMBER) const` — Find a frame index at InTime if available within a specified tolarance of the timestamp
- L395 _public function_ `void GetFramesForTime(float InTime, const FRecordedFrame*& OutFirst, const FRecordedFrame*& OutSecond) const` — Given a time, return either one or two frames. If InTime is exactly on a frame then only that frame is returned. If we are beyond the end of the track only the last is returned. For times in the middle of the track that are not exactly on a frame then the frame before and after the time are returned.
- L426 _public function_ `FTransform GetTransformAtTime(int32 InIndex, float InTime) const` — Given a time, get an interpolated transform from the track for a provided particle
- L459 _public function_ `bool GetDisabledAtTime(int32 InIndex, float InTime) const` — Get whether a particle is disabled at a provided time
- L474 _public function_ `bool GetWasActiveInWindow(int32 InIndex, float InBeginTime, float InEndTime) const` — Given two times, find out if the provided particle was ever active within them
- L509 _public function_ `FVector GetLinearVelocityAtTime(int32 InIndex, float InTime, float SampleWidth = 1.0f / 120.0f) const` — Get an interpolated linear velocity for the specified particle at the provided time - using SampleWidth to pick out a window of interpolation
- L530 _public function_ `FVector GetAngularVelocityAtTime(int32 InIndex, float InTime, float SampleWidth = 1.0f / 120.0f) const` — Get an interpolated angular velocity for the specified particle at the provided time - using SampleWidth to pick out a window of interpolation
- L553 _public prototype_ `static FRecordedTransformTrack ProcessRawRecordedData(const FRecordedTransformTrack& InCache);`

#### Free symbols / members of external scopes

- L181 _function_ `friend inline uint32 GetTypeHash(const FSolverTrailingData& Other)`
- L186 _function_ `friend bool operator==(const FSolverTrailingData& A, const FSolverTrailingData& B)`

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollection/TransformCollection.h` (Public)


#### class `FTransformCollection`  
`class FTransformCollection : public FManagedArrayCollection`  
_L16-141_
- inherits: `FManagedArrayCollection`
- desc: TransformCollection (ManagedArrayCollection) Stores the TArray<T> groups necessary to process transform hierarchies. @see FTransformCollectionComponent
- L19 _public typedef_ `typedef FManagedArrayCollection Super;`
- L21 _public prototype_ `FTransformCollection();`
- L22 _public prototype_ `~FTransformCollection();`
- L23 _public prototype_ `FTransformCollection(FTransformCollection &) = delete;`
- L24 _public prototype_ `FTransformCollection& operator=(const FTransformCollection&) = delete;`
- L25 _public prototype_ `FTransformCollection(FTransformCollection&&) = default;`
- L26 _public prototype_ `FTransformCollection& operator=(FTransformCollection&&) = default;`
- L27 _public prototype_ `MANAGED_ARRAY_COLLECTION_INTERNAL(FTransformCollection);`
- L49 _public member_ `static const FName TransformGroup;` — Attribute Groups These attribute groups are predefined data member of the FTransformCollection. TransformGroup ("Transform") Default Attributes : FTransform3fArray Transform =  GetAttribute<FTransform3f>("Transform", TransformGroup) FInt32Array Level = GetAttribute<int32>("Level", TransformGroup) FIX FInt32Array Parent = GetAttribute<int32>("Parent", TransformGroup) FIX FInt32Array Children = GetAttribute<TSet<int32>>("Children", TransformGroup) FIX The TransformGroup defines transform information for each Vertex. All positional information stored within Vertices and Geometry groups should be relative to its TransformGroup Transform. Parent defines the parent index of one transform node relative to another (Invalid is no parent exists, i.e. is root) Children defines the child indices of the transform node in the transform hierarchy (leaf nodes will have no children) Level is the distance from the root node at level 0. Leaf nodes will have the highest level number.
- L50 _public member_ `static const FName TransformAttribute;`
- L51 _public member_ `static const FName ParentAttribute;`
- L52 _public member_ `static const FName ChildrenAttribute;`
- L53 _public member_ `static const FName ParticlesAttribute;`
- L54 _public member_ `static const FName LevelAttribute;`
- L55 _public member_ `static const FName ConvexGroup;`
- L56 _public member_ `static const FName ConvexHullAttribute;`
- L57 _public member_ `static const FName BoneNameAttribute;`
- L58 _public member_ `static const FName BoneColorAttribute;`
- L59 _public member_ `static const FName BoneHierarchyAttribute;`
- L60 _public member_ `static const FName GeometryIndexAttribute;`
- L63 _public prototype_ `static void DefineTransformSchema(FManagedArrayCollection&);` — Schema
- L67 _public prototype_ `virtual void Serialize(Chaos::FChaosArchive& Ar) override;` — Serialize
- L73 _public prototype_ `static FTransformCollection SingleTransform(const FTransform& TransformRoot = FTransform::Identity);` — SingleTransform: Create a single transform.
- L79 _public prototype_ `virtual void Append(const FManagedArrayCollection& Collection) override;` — Append Collection and reindex dependencies on this collection. @param InCollection : FManagedArrayCollection to add.
- L85 _public prototype_ `void AppendCollection(const FTransformCollection& Collection);` — Append Collection and reindex dependencies on this collection. @param InCollection : FTransformCollection to add.
- L92 _public prototype_ `int32 AppendTransform(const FTransformCollection & GeometryCollection, const FTransform& TransformRoot = FTransform::Identity);` — AppendTransform: Append a transform at the end of the collection without parenting.
- L99 _public prototype_ `void ParentTransforms(const int32 TransformIndex, const int32 ChildIndex);` — ParentTransforms Parent Transforms under the specified node using local parent hierarchy compensation. .
- L100 _public prototype_ `void ParentTransforms(const int32 TransformIndex, const TArray<int32>& SelectedBones);`
- L101 _public prototype_ `void UnparentTransform(const int32 ChildIndex);`
- L107 _public prototype_ `void RelativeTransformation(const int32& Index, const FTransform& LocalOffset);` — RelativeTransformation Modify the specified index by the local matrix offset.
- L115 _public prototype_ `virtual void RemoveElements(const FName & Group, const TArray<int32> & SortedDeletionList, FProcessingParameters Params = FProcessingParameters()) override;` — RemoveElements Remove elements from the transform collection. Transform children are re-parented under the deleted elements parent using local parent compensation [relative local matrices].
- L122 _public prototype_ `virtual void MergeElements(const FName& Group, const TArray<int32>& SortedMergeList, const TArray<int32>& MergeRemapIndex, FProcessingParameters Params = FProcessingParameters()) override;` — MergeElements Merge elements from the transform collection. Updates parent and children hierachy to the remapped index Deletes merged elements
- L127 _public prototype_ `virtual void Reset() override;` — reset internal state
- L130 _public member_ `TManagedArray<FTransform3f> Transform;` — Transform Group
- L131 _public member_ `TManagedArray<FString> BoneName;`
- L132 _public member_ `TManagedArray<FLinearColor> BoneColor;`
- L133 _public member_ `TManagedArray<int32> Parent;`
- L134 _public member_ `TManagedArray<TSet<int32>> Children;`
- L140 _protected prototype_ `void Construct();` — Construct

### `Source/Runtime/Experimental/Chaos/Public/GeometryCollectionProxyData.h` (Public)


#### class `FTransformDynamicCollection`  
`class FTransformDynamicCollection : public FManagedArrayCollection`  
_L20-80_
- inherits: `FManagedArrayCollection`
- desc: FTransformDynamicCollection (FManagedArrayCollection) Stores per instance data for transforms and hierarchy information
- L23 _public typedef_ `typedef FManagedArrayCollection Super;`
- L26 _public prototype_ `FTransformDynamicCollection(const FGeometryCollection* InRestCollection);` — `UE_DEPRECATED(5.4, "No longer handles a raw ptr, use the version taking TSharedPtr")`
- L27 _public prototype_ `FTransformDynamicCollection(TSharedPtr<const FGeometryCollection> InRestCollection);`
- L28 _public prototype_ `FTransformDynamicCollection(FTransformDynamicCollection&) = delete;`
- L29 _public prototype_ `FTransformDynamicCollection& operator=(const FTransformDynamicCollection&) = delete;`
- L30 _public prototype_ `FTransformDynamicCollection(FTransformDynamicCollection&&) = delete;`
- L31 _public prototype_ `FTransformDynamicCollection& operator=(FTransformDynamicCollection&&) = delete;`
- L33 _public prototype_ `const FTransform3f& GetTransform(int32 Index) const;`
- L34 _public prototype_ `void SetTransform(int32 Index, const FTransform3f& Transform);`
- L35 _public prototype_ `int32 GetNumTransforms() const;`
- L36 _public prototype_ `void ResetInitialTransforms();`
- L38 _public prototype_ `const TManagedArray<bool>& GetHasParent() const;`
- L39 _public prototype_ `bool GetHasParent(int32 Index) const;`
- L40 _public prototype_ `void SetHasParent(int32 Index, bool Value);`
- L41 _public prototype_ `int32 GetParent(int32 Index) const;`
- L43 _public prototype_ `bool HasChildren(int32 Index) const;`
- L46 _public prototype_ `bool IsCluster(int32 Index) const;` — check if the transform is a cluster - ie has originally children as per rest collection
- L49 _public function_ `template<typename Lambda> void IterateThroughChildren(int32 Index, Lambda&& LambdaIt) const`
- L70 _protected member_ `const FGeometryCollection* RestCollection;` — `UE_DEPRECATED(5.4, "Raw pointer no longer in use, instead access the shared version")`
- L71 _protected member_ `TSharedPtr<const FGeometryCollection> RestCollectionShared;`
- L73 _private member_ `TManagedArray<bool> HasParent;`
- L74 _private member_ `TManagedArray<FTransform3f> Transform;`
- L75 _private member_ `bool bTransformHasChanged;`
- L78 _private prototype_ `void Construct();` — Construct
- L79 _private prototype_ `void InitializeTransforms();`

#### class `FGeometryDynamicCollection`  
`class FGeometryDynamicCollection : public FTransformDynamicCollection`  
_L89-191_
- inherits: `FTransformDynamicCollection`
- L93 _public prototype_ `FGeometryDynamicCollection(const FGeometryCollection* InRestCollection);` — `UE_DEPRECATED(5.4, "No longer handles a raw ptr, use the version taking TSharedPtr")`
- L94 _public prototype_ `FGeometryDynamicCollection(TSharedPtr<const FGeometryCollection> InRestCollection);`
- L95 _public prototype_ `FGeometryDynamicCollection(FGeometryDynamicCollection&) = delete;`
- L96 _public prototype_ `FGeometryDynamicCollection& operator=(const FGeometryDynamicCollection&) = delete;`
- L97 _public prototype_ `FGeometryDynamicCollection(FGeometryDynamicCollection&&) = delete;`
- L98 _public prototype_ `FGeometryDynamicCollection& operator=(FGeometryDynamicCollection&&) = delete;`
- L100 _public typedef_ `typedef FTransformDynamicCollection Super;`
- L102 _public member_ `static const FName ActiveAttribute;`
- L103 _public member_ `static const FName DynamicStateAttribute;`
- L104 _public member_ `static const FName ImplicitsAttribute;`
- L105 _public member_ `static const FName ShapesQueryDataAttribute;`
- L106 _public member_ `static const FName ShapesSimDataAttribute;`
- L107 _public member_ `static const FName SharedImplicitsAttribute;`
- L108 _public member_ `static const FName SimplicialsAttribute;`
- L109 _public member_ `static const FName SimulatableParticlesAttribute;`
- L110 _public member_ `static const FName InternalClusterParentTypeAttribute;`
- L113 _public member_ `static const FName CollisionMaskAttribute;` — `UE_DEPRECATED(5.4, "CollisionMaskAttribute is no longer supported")`
- L116 _public member_ `static const FName CollisionGroupAttribute;` — `UE_DEPRECATED(5.4, "CollisionGroupAttribute is no longer supported")`
- L119 _public member_ `TManagedArray<bool> Active;` — Transform Group
- L121 _public member_ `TManagedArray<uint8> DynamicState;`
- L125 _public member_ `TManagedArray<TUniquePtr<FCollisionStructureManager::FSimplicial>> Simplicials;` — `UE_DEPRECATED(5.5, "Simplicials array is optional and should be queried using the FindAttribute method")`
- L127 _public member_ `TManagedArray<bool> SimulatableParticles;`
- L130 _public member_ `TManagedArray<int32> CollisionStructureID;` — `UE_DEPRECATED(5.4, "CollisionStructureID attribute is no longer supported")`
- L133 _public member_ `TManagedArray<int32> CollisionMask;` — `UE_DEPRECATED(5.4, "CollisionMask attribute is no longer supported")`
- L136 _public member_ `TManagedArray<int32> CollisionGroup;` — `UE_DEPRECATED(5.4, "CollisionGroup attribute is no longer supported - you can still set the collision group on the geometry collection")`
- L140 _public prototype_ `const TManagedArrayAccessor<int32> GetInitialLevels() const;`
- L142 _public function_ `const TManagedArray<uint8>& GetInternalClusterParentTypeAttribute() const`
- L143 _public function_ `TManagedArray<uint8>& GetInternalClusterParentTypeAttribute()`
- L145 _public prototype_ `void AddVelocitiesAttributes();`
- L146 _public function_ `const TManagedArray<FVector3f>* GetLinearVelocitiesAttribute() const`
- L147 _public function_ `const TManagedArray<FVector3f>* GetAngularVelocitiesAttribute() const`
- L148 _public function_ `TManagedArray<FVector3f>* GetLinearVelocitiesAttribute()`
- L149 _public function_ `TManagedArray<FVector3f>* GetAngularVelocitiesAttribute()`
- L151 _public prototype_ `void AddAnimateTransformAttribute();`
- L152 _public function_ `const TManagedArray<bool>* GetAnimateTransformAttribute() const`
- L153 _public function_ `TManagedArray<bool>* GetAnimateTransformAttribute()`
- L169 _public function_ `FInitialVelocityFacade GetInitialVelocityFacade()`
- L170 _public function_ `FInitialVelocityFacade GetInitialVelocityFacade() const`
- L172 _public prototype_ `void CopyInitialVelocityAttributesFrom(const FGeometryDynamicCollection& SourceCollection);`
- L174 _public function_ `void MakeDirty()`
- L175 _public function_ `void MakeClean()`
- L176 _public function_ `bool IsDirty() const`
- L178 _public function_ `virtual void Reset() override`
- L185 _private member_ `TManagedArray<uint8> InternalClusterParentType;`
- L187 _private member_ `TManagedArray<FVector3f>* OptionalLinearVelocityAttribute;`
- L188 _private member_ `TManagedArray<FVector3f>* OptionalAngularVelocityAttribute;`
- L189 _private member_ `TManagedArray<bool>* OptionalAnimateTransformAttribute;`
- L190 _private member_ `bool bDirty = false;`

#### struct `FGeometryDynamicCollection::FInitialVelocityFacade`  
`struct FInitialVelocityFacade`  
_L155-167_
- L157 _public prototype_ `FInitialVelocityFacade(FGeometryDynamicCollection& DynamicCollection);`
- L158 _public prototype_ `FInitialVelocityFacade(const FGeometryDynamicCollection& DynamicCollection);`
- L160 _public prototype_ `bool IsValid() const;`
- L161 _public prototype_ `void DefineSchema();`
- L162 _public prototype_ `void Fill(const FVector3f& InitialLinearVelocity, const FVector3f& InitialAngularVelocity);`
- L163 _public prototype_ `void CopyFrom(const FGeometryDynamicCollection& SourceCollection);`
- L165 _public member_ `TManagedArrayAccessor<FVector3f> InitialLinearVelocityAttribute;`
- L166 _public member_ `TManagedArrayAccessor<FVector3f> InitialAngularVelocityAttribute;`

#### class `FGeometryCollectionDynamicStateFacade`  
`class FGeometryCollectionDynamicStateFacade`  
_L198-241_
- desc: Provides an API for dynamic state related attributes physics state , broken state, current parent (normal or internal clusters ) To be used with the dynamic collection
- L201 _public prototype_ `FGeometryCollectionDynamicStateFacade(FGeometryDynamicCollection& InCollection);`
- L204 _public prototype_ `bool IsValid() const;` — returns true if all the necessary attributes are present
- L207 _public prototype_ `bool IsActive(int32 TransformIndex) const;` — return true if the transform is active
- L210 _public prototype_ `bool IsDynamicOrSleeping(int32 TransformIndex) const;` — return true if the transform is in a dynamic or sleeping state
- L213 _public prototype_ `bool IsSleeping(int32 TransformIndex) const;` — return true if the transform is in a sleeping state
- L216 _public prototype_ `bool HasChildren(int32 TransformIndex) const;` — whether there's children attached to this transform (Cluster)
- L219 _public prototype_ `bool HasBrokenOff(int32 TransformIndex) const;` — return true if the transform has broken off its parent
- L222 _public prototype_ `bool HasInternalClusterParent(int32 TransformIndex) const;` — return true if the transform has an internal cluster parent
- L225 _public prototype_ `bool HasDynamicInternalClusterParent(int32 TransformIndex) const;` — return true if the transform has an internal cluster parent in a dynamic state
- L228 _public prototype_ `bool HasClusterUnionParent(int32 TransformIndex) const;` — Return true if the transform has a cluster union parent.
- L232 _private member_ `TManagedArrayAccessor<bool> ActiveAttribute;` — Active state, true means that the transform is active or broken off from its parent
- L235 _private member_ `TManagedArrayAccessor<uint8> DynamicStateAttribute;` — physics state of the transform (Dynamic, kinematic, static, sleeping)
- L238 _private member_ `TManagedArrayAccessor<uint8> InternalClusterParentTypeAttribute;` — type of internal state parent
- L240 _private member_ `FGeometryDynamicCollection& DynamicCollection;`

#### class `FGeometryCollectionResults`  
`class FGeometryCollectionResults: public FRefCountedObject`  
_L247-399_
- inherits: `FRefCountedObject`
- desc: Buffer structure for communicating simulation state between game and physics threads.
- L250 _public prototype_ `FGeometryCollectionResults();`
- L252 _public function_ `int32 GetNumEntries() const`
- L254 _public prototype_ `void Reset();`
- L256 _public function_ `void InitArrays(const FGeometryDynamicCollection& Collection)`
- L268 _public typedef_ `using FEntryIndex = int32;`
- L308 _public function_ `void SetDamages(int32 TransformIndex, const FDamageData& DamageData)`
- L313 _public function_ `const FDamageData& GetDamages(int32 TransformIndex) const`
- L319 _public function_ `inline FEntryIndex GetEntryIndexByTransformIndex(int32 TransformIndex) const`
- L328 _public function_ `inline const FStateData& GetState(FEntryIndex EntryIndex) const`
- L333 _public function_ `inline const FPositionData& GetPositions(FEntryIndex EntryIndex) const`
- L338 _public function_ `inline const FVelocityData& GetVelocities(FEntryIndex EntryIndex) const`
- L343 _public function_ `inline void SetSolverDt(const Chaos::FReal SolverDtIn)`
- L348 _public function_ `inline void SetState(int32 EntryIndex, const FStateData& StateData)`
- L353 _public function_ `inline FEntryIndex AddEntry(int32 TransformIndex)`
- L363 _public function_ `inline void SetPositions(FEntryIndex EntryIndex, const FPositionData& PositionData)`
- L368 _public function_ `inline void SetVelocities(FEntryIndex EntryIndex, const FVelocityData& VelocityData)`
- L373 _public function_ `inline const TBitArray<>& GetModifiedTransformIndices() const`
- L379 _private member_ `Chaos::FReal SolverDt;`
- L384 _private member_ `TBitArray<> ModifiedTransformIndices;` — we only store the data for modified transforms ModifiedTransformIndices contains which transform has been set use the API to retrieve the entry Index matching a specific transform index
- L385 _private member_ `TArray<FStateData> States;`
- L386 _private member_ `TArray<FPositionData> Positions;`
- L387 _private member_ `TArray<FVelocityData> Velocities;`
- L392 _private member_ `TArray<FDamageData> Damages;` — use to display impulse statistics in editor this is indexed on the transform index
- L396 _public member_ `uint8 IsObjectDynamic: 1;`
- L397 _public member_ `uint8 IsObjectLoading: 1;`
- L398 _public member_ `uint8 IsRootBroken : 1;`

#### struct `FGeometryCollectionResults::FState`  
`struct FState`  
_L270-279_
- L272 _public member_ `uint16 DynamicState: 8;` — need to fit EObjectStateTypeEnum
- L273 _public member_ `uint16 DisabledState: 1;`
- L274 _public member_ `uint16 HasDecayed : 1;` — particle has been released but disabled right away
- L275 _public member_ `uint16 HasInternalClusterParent: 1;`
- L276 _public member_ `uint16 DynamicInternalClusterParent: 1;`
- L277 _public member_ `uint16 HasClusterUnionParent: 1;`

#### struct `FGeometryCollectionResults::FStateData`  
`struct FStateData`  
_L281-287_
- L283 _public member_ `int32 TransformIndex;`
- L284 _public member_ `int32 InternalClusterUniqueIdx;`
- L285 _public member_ `bool HasParent;`
- L286 _public member_ `FState State;`

#### struct `FGeometryCollectionResults::FPositionData`  
`struct FPositionData`  
_L289-293_
- L291 _public member_ `Chaos::FVec3 ParticleX;`
- L292 _public member_ `Chaos::FRotation3 ParticleR;`

#### struct `FGeometryCollectionResults::FVelocityData`  
`struct FVelocityData`  
_L295-299_
- L297 _public member_ `Chaos::FVec3f ParticleV;`
- L298 _public member_ `Chaos::FVec3f ParticleW;`

#### struct `FGeometryCollectionResults::FDamageData`  
`struct FDamageData`  
_L302-306_
- L304 _public member_ `float Damage = 0;`
- L305 _public member_ `float DamageThreshold = 0;`

### `Source/Runtime/Experimental/Chaos/Public/PBDRigidActiveParticlesBuffer.h` (Public)


#### struct `Chaos::FPBDRigidDirtyParticlesBufferOut`  
`struct FPBDRigidDirtyParticlesBufferOut`  
_L16-22_
- desc: Solver specific data buffered for use on Game thread
- L18 _public member_ `TArray<FSingleParticlePhysicsProxy*> DirtyGameThreadParticles;`
- L21 _public member_ `TSet<IPhysicsProxyBase*> PhysicsParticleProxies;` — Some particle types (clustered) only exist on the game thread, but we still need to pull data over via their proxies.

#### class `Chaos::FPBDRigidDirtyParticlesBuffer`  
`class FPBDRigidDirtyParticlesBuffer`  
_L25-64_
- L30 _public prototype_ `FPBDRigidDirtyParticlesBuffer(const Chaos::EMultiBufferMode& InBufferMode, bool bInSingleThreaded);`
- L32 _public prototype_ `void CaptureSolverData(FPBDRigidsSolver* Solver);`
- L34 _public prototype_ `void ReadLock();`
- L35 _public prototype_ `void ReadUnlock();`
- L36 _public prototype_ `void WriteLock();`
- L37 _public prototype_ `void WriteUnlock();`
- L40 _private function_ `const FPBDRigidDirtyParticlesBufferOut* GetSolverOutData() const`
- L48 _private prototype_ `void BufferPhysicsResults(FPBDRigidsSolver* Solver);` — Fill data from solver destined for the game thread - used to limit the number of objects updated on the game thread
- L53 _private function_ `void FlipDataOut()` — Flip should be performed on physics thread side non-game thread
- L58 _private member_ `Chaos::EMultiBufferMode BufferMode;`
- L59 _private member_ `FRWLock ResourceOutLock;`
- L60 _private member_ `bool bUseLock;`
- L63 _private member_ `TUniquePtr<IBufferResource<FPBDRigidDirtyParticlesBufferOut>> SolverDataOut;` — Physics thread to game thread

#### class `Chaos::FPBDRigidDirtyParticlesBufferAccessor`  
`class FPBDRigidDirtyParticlesBufferAccessor`  
_L66-87_
- L69 _public function_ `FPBDRigidDirtyParticlesBufferAccessor(FPBDRigidDirtyParticlesBuffer* InManager) : Manager(InManager)`
- L75 _public function_ `const FPBDRigidDirtyParticlesBufferOut* GetSolverOutData() const`
- L80 _public function_ `~FPBDRigidDirtyParticlesBufferAccessor()`
- L86 _private member_ `FPBDRigidDirtyParticlesBuffer* Manager;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PBDRigidsSolver.h` (Public)


#### enum `Chaos::ELockType`  
`enum class ELockType : uint8`  
_L72-76_
- L74 _public enumerator_ `Read`
- L75 _public enumerator_ `Write`

#### struct `Chaos::TSolverSimMaterialScope`  
`template<ELockType LockType> struct TSolverSimMaterialScope`  
_L79-82_
- L81 _public prototype_ `TSolverSimMaterialScope() = delete;`
- L517 _public function_ `explicit TSolverSimMaterialScope(FPhysicsSolverBase* InSolver) : Solver(InSolver)`
- L524 _public function_ `~TSolverSimMaterialScope()`
- L530 _private member_ `FPhysicsSolverBase* Solver;`

#### class `Chaos::FPBDRigidsSolver`  
`class FPBDRigidsSolver : public FPhysicsSolverBase`  
_L87-509_
- inherits: `FPhysicsSolverBase`
- L90 _private prototype_ `FPBDRigidsSolver(const EMultiBufferMode BufferingModeIn, UObject* InOwner, FReal AsyncDt);`
- L91 _private prototype_ `virtual ~FPBDRigidsSolver();`
- L95 _public typedef_ `typedef FPhysicsSolverBase Super;`
- L109 _public member_ `void* PhysSceneHack;` — This is a total hack for now to get at the owning scene
- L111 _public typedef_ `typedef FPBDRigidsSOAs FParticlesType;`
- L112 _public typedef_ `typedef FPBDRigidDirtyParticlesBuffer FDirtyParticlesBuffer;`
- L114 _public typedef_ `typedef Chaos::FGeometryParticle FParticle;`
- L115 _public typedef_ `typedef Chaos::FGeometryParticleHandle FHandle;`
- L116 _public typedef_ `typedef Chaos::FPBDRigidsEvolutionGBF FPBDRigidsEvolution;`
- L118 _public typedef_ `typedef FPBDRigidDynamicSpringConstraints FRigidDynamicSpringConstraints;`
- L119 _public typedef_ `typedef FPBDPositionConstraints FPositionConstraints;`
- L121 _public typedef_ `using FJointConstraints = FPBDJointCombinedConstraints;`
- L126 _public prototype_ `void ChangeBufferMode(Chaos::EMultiBufferMode InBufferMode);`
- L132 _public prototype_ `void RegisterObject(FSingleParticlePhysicsProxy* Proxy);`
- L133 _public prototype_ `void UnregisterObject(FSingleParticlePhysicsProxy* Proxy);`
- L135 _public prototype_ `void RegisterObject(FGeometryCollectionPhysicsProxy* InProxy);`
- L136 _public prototype_ `void UnregisterObject(FGeometryCollectionPhysicsProxy* InProxy);`
- L138 _public prototype_ `void RegisterObject(FClusterUnionPhysicsProxy* Proxy);`
- L139 _public prototype_ `void UnregisterObject(FClusterUnionPhysicsProxy* Proxy);`
- L141 _public prototype_ `void RegisterObject(Chaos::FJointConstraint* GTConstraint);`
- L142 _public prototype_ `void UnregisterObject(Chaos::FJointConstraint* GTConstraint);`
- L144 _public prototype_ `void RegisterObject(Chaos::FSuspensionConstraint* GTConstraint);`
- L145 _public prototype_ `void UnregisterObject(Chaos::FSuspensionConstraint* GTConstraint);`
- L147 _public prototype_ `void RegisterObject(Chaos::FCharacterGroundConstraint* GTConstraint);`
- L148 _public prototype_ `void UnregisterObject(Chaos::FCharacterGroundConstraint* GTConstraint);`
- L152 _public prototype_ `UE_INTERNAL FDelegateHandle AddParticleUnregisteredGTCallback(FSolverParticleUnregisteredGT::FDelegate InDelegate);` — Fired on the game thread when a single particle physics proxy is unregistered. Called during UnregisterObject before the proxy is enqueued for destruction.
- L153 _public prototype_ `UE_INTERNAL bool RemoveParticleUnregisteredGTCallback(FDelegateHandle InHandle);`
- L160 _public function_ `FDirtyParticlesBuffer* GetDirtyParticlesBuffer() const` — /
- L162 _public prototype_ `int32 NumJointConstraints() const;`
- L163 _public prototype_ `int32 NumCollisionConstraints() const;`
- L170 _public prototype_ `void Reset();` — /
- L173 _public prototype_ `void StartingSceneSimulation();` — /
- L176 _public prototype_ `void CompleteSceneSimulation();` — /
- L179 _public prototype_ `void UpdateGameThreadStructures();` — /
- L184 _public function_ `void SetCurrentFrame(const int32 CurrentFrameIn)` — /
- L185 _public function_ `int32& GetCurrentFrame()`
- L188 _public function_ `virtual int32 GetCVDFrameNumber() const override`
- L192 _public function_ `void SetPositionIterations(const int32 InNumIterations)` — /
- L193 _public function_ `void SetVelocityIterations(const int32 InNumIterations)`
- L194 _public function_ `void SetProjectionIterations(const int32 InNumIterations)`
- L195 _public function_ `void SetCollisionCullDistance(const FReal InCullDistance)`
- L196 _public prototype_ `void SetVelocityBoundsExpansion(const FReal BoundsVelocityMultiplier, const FReal MaxBoundsVelocityExpansion);`
- L197 _public prototype_ `void SetVelocityBoundsExpansionMACD(const FReal BoundsVelocityMultiplier, const FReal MaxBoundsVelocityExpansion);`
- L198 _public function_ `void SetCollisionMaxPushOutVelocity(const FReal InMaxPushOutVelocity)`
- L199 _public function_ `void SetCollisionDepenetrationVelocity(const FRealSingle InVelocity)`
- L202 _public function_ `void SetGenerateCollisionData(bool bDoGenerate)` — /
- L203 _public function_ `void SetGenerateBreakingData(bool bDoGenerate)`
- L208 _public function_ `void SetGenerateTrailingData(bool bDoGenerate)`
- L209 _public function_ `void SetGenerateRemovalData(bool bDoGenerate)`
- L210 _public function_ `void SetCollisionFilterSettings(const FSolverCollisionFilterSettings& InCollisionFilterSettings)`
- L211 _public function_ `void SetBreakingFilterSettings(const FSolverBreakingFilterSettings& InBreakingFilterSettings)`
- L212 _public function_ `void SetTrailingFilterSettings(const FSolverTrailingFilterSettings& InTrailingFilterSettings)`
- L213 _public function_ `void SetRemovalFilterSettings(const FSolverRemovalFilterSettings& InRemovalFilterSettings)`
- L220 _public prototype_ `bool IsDetemerministic() const;` — @brief True if the simulation is running in deterministic mode This will be true if determinism is explicitly requested (via SetIsDeterministic()) or if required by some other system like Rewind/Resim support.
- L227 _public prototype_ `void SetIsDeterministic(const bool bInIsDeterministic);` — @brief Request that the sim be deterministic (or not) @note Even if set to false, the sim may still be deterministic if some other feature is enabled and requires it. @see IsDetemerministic()
- L230 _public function_ `FPBDJointConstraints& GetJointConstraints()` — `UE_DEPRECATED(5.5, "No longer used, see combined constraint in FPBDRigidsSolver::GetJointCombinedConstraints")`
- L232 _public function_ `const FPBDJointConstraints& GetJointConstraints() const` — `UE_DEPRECATED(5.5, "No longer used, see combined constraint in FPBDRigidsSolver::GetJointCombinedConstraints")`
- L235 _public function_ `FJointConstraints& GetJointCombinedConstraints()` — /
- L236 _public function_ `const FJointConstraints& GetJointCombinedConstraints() const`
- L238 _public function_ `FPBDSuspensionConstraints& GetSuspensionConstraints()`
- L239 _public function_ `const FPBDSuspensionConstraints& GetSuspensionConstraints() const`
- L240 _public prototype_ `void SetSuspensionTarget(Chaos::FSuspensionConstraint* GTConstraint, const FVector& TargetPos, const FVector& Normal, bool Enabled, const IPhysicsProxyBase* GroundProxy = nullptr);`
- L242 _public function_ `FCharacterGroundConstraintContainer& GetCharacterGroundConstraints()`
- L243 _public function_ `const FCharacterGroundConstraintContainer& GetCharacterGroundConstraints() const`
- L245 _public prototype_ `void EnableRewindCapture(int32 NumFrames, bool InUseCollisionResimCache, TUniquePtr<IRewindCallback>&& RewindCallback);`
- L246 _public prototype_ `void EnableRewindCapture(int32 NumFrames, bool InUseCollisionResimCache);`
- L247 _public prototype_ `void EnableRewindCapture(int32 NumFrames);`
- L248 _public prototype_ `void EnableRewindCapture();`
- L251 _public function_ `FPBDRigidsEvolution* GetEvolution()` — /
- L252 _public function_ `FPBDRigidsEvolution* GetEvolution() const`
- L254 _public function_ `FParticlesType& GetParticles()`
- L255 _public function_ `const FParticlesType& GetParticles() const`
- L258 _public function_ `FEventManager* GetEventManager()` — /
- L259 _public function_ `virtual void FlipEventManagerBuffer()`
- L262 _public function_ `FSolverEventFilters* GetEventFilters()` — /
- L263 _public function_ `FSolverEventFilters* GetEventFilters() const`
- L266 _public prototype_ `void SyncEvents_GameThread();` — /
- L269 _public prototype_ `void PreIntegrateDebugDraw(FReal Dt) const;` — /
- L270 _public prototype_ `void PreSolveDebugDraw(FReal Dt) const;`
- L271 _public prototype_ `void PostTickDebugDraw(FReal Dt) const;`
- L275 _public function_ `void PostEvolutionVDBPush() const` — `UE_DEPRECATED(5.4, "This method will be removed in the future")` — Visual debugger (VDB) push methods
- L277 _public function_ `TArray<FGeometryCollectionPhysicsProxy*>& GetGeometryCollectionPhysicsProxies_Internal()`
- L282 _public function_ `TArray<FGeometryCollectionPhysicsProxy*>& GetGeometryCollectionPhysicsProxiesField_Internal()`
- L287 _public function_ `const TArray<FJointConstraintPhysicsProxy*>& GetJointConstraintPhysicsProxies_Internal() const`
- L293 _public prototype_ `void UpdateMaterial(Chaos::FMaterialHandle InHandle, const Chaos::FChaosPhysicsMaterial& InNewData);` — Events hooked up to the Chaos material manager
- L294 _public prototype_ `void CreateMaterial(Chaos::FMaterialHandle InHandle, const Chaos::FChaosPhysicsMaterial& InNewData);`
- L295 _public prototype_ `void DestroyMaterial(Chaos::FMaterialHandle InHandle);`
- L296 _public prototype_ `void UpdateMaterialMask(Chaos::FMaterialMaskHandle InHandle, const Chaos::FChaosPhysicsMaterialMask& InNewData);`
- L297 _public prototype_ `void CreateMaterialMask(Chaos::FMaterialMaskHandle InHandle, const Chaos::FChaosPhysicsMaterialMask& InNewData);`
- L298 _public prototype_ `void DestroyMaterialMask(Chaos::FMaterialMaskHandle InHandle);`
- L301 _public function_ `const THandleArray<FChaosPhysicsMaterial>& GetQueryMaterials_External() const` — Access to the internal material mirrors
- L302 _public function_ `const THandleArray<FChaosPhysicsMaterialMask>& GetQueryMaterialMasks_External() const`
- L303 _public function_ `const THandleArray<FChaosPhysicsMaterial>& GetSimMaterials() const`
- L304 _public function_ `const THandleArray<FChaosPhysicsMaterialMask>& GetSimMaterialMasks() const`
- L307 _public prototype_ `void SyncQueryMaterials_External();` — Copy the simulation material list to the query material list, to be done when the SQ commits an update
- L310 _public function_ `bool RewindUsesCollisionResimCache() const` — `UE_DEPRECATED(5.5, "Deprecated, use GetUseCollisionResimCache() instead")`
- L313 _public function_ `void FinalizeRewindData(const TParticleView<FPBDRigidParticles>& DirtyParticles)` — `UE_DEPRECATED(5.7, "Deprecated, This functionality is now handled by FRewindData::ProcessDirtyPTParticles")`
- L315 _public function_ `FPerSolverFieldSystem& GetPerSolverField()`
- L316 _public function_ `const FPerSolverFieldSystem& GetPerSolverField() const`
- L318 _public prototype_ `void UpdateExternalAccelerationStructure_External(ISpatialAccelerationCollection<FAccelerationStructureHandle,FReal,3>*& ExternalStructure);`
- L319 _public function_ `const ISpatialAccelerationCollection<FAccelerationStructureHandle, FReal, 3>* GetInternalAccelerationStructure_Internal() const`
- L325 _public prototype_ `void ApplyConfig(const FChaosSolverConfiguration& InConfig);` — Apply a solver configuration to this solver, set externally by the owner of a solver (see UPhysicsSettings for world solver settings)
- L327 _public function_ `virtual void KillSafeAsyncTasks() override`
- L332 _public function_ `virtual bool AreAnyTasksPending() const override`
- L342 _public prototype_ `void BeginDestroy();`
- L345 _public prototype_ `void FieldParameterUpdateCallback( Chaos::FPBDPositionConstraints& PositionTarget, TMap<int32, int32>& TargetedParticles);` — Update the particles parameters based on field evaluation
- L350 _public prototype_ `void FieldForcesUpdateCallback();` — Update the particles forces based on field evaluation
- L353 _public prototype_ `void ResetStatCounters();` — Update the counter in Stats and the CSV profiler
- L354 _public prototype_ `void UpdateStatCounters() const;`
- L355 _public prototype_ `void UpdateExpensiveStatCounters() const;`
- L358 _public prototype_ `FSingleParticlePhysicsProxy* GetParticleProxy_PT(const FUniqueIdx& Idx);` — Access particle proxy from physics thread useful for cross thread communication
- L359 _public prototype_ `const FSingleParticlePhysicsProxy* GetParticleProxy_PT(const FUniqueIdx& Idx) const;`
- L360 _public prototype_ `FSingleParticlePhysicsProxy* GetParticleProxy_PT(const FGeometryParticleHandle& Handle);`
- L361 _public prototype_ `const FSingleParticlePhysicsProxy* GetParticleProxy_PT(const FGeometryParticleHandle& Handle) const;`
- L364 _public prototype_ `void SetParticleDynamicMisc(FPBDRigidParticleHandle* Rigid, const FParticleDynamicMisc& DynamicMisc);` — Interop utilities
- L367 _public prototype_ `virtual void ApplyCallbacks_Internal() override;` — Apply callbacks internally
- L368 _public prototype_ `FSolverSerializer& GetSerializer();`
- L370 _public prototype_ `void OnEvolutionPreIntegrate(FReal Dt);`
- L371 _public prototype_ `void OnEvolutionPostIntegrate(FReal Dt);`
- L376 _protected prototype_ `virtual void OnDebugNameChanged() override final;`
- L383 _private prototype_ `template <typename LambdaType> int32 DispatchTasksBufferPhysicsResults(int32 DispatchBatchIndex, int32 NumDirty, LambdaType ReturnHandle);` — /
- L385 _private prototype_ `void BufferPhysicsResults();`
- L386 _private prototype_ `void BufferPhysicsResultsSingleThreaded( TArray<FSingleParticlePhysicsProxy*>& ActiveRigid, TArray<FGeometryCollectionPhysicsProxy*>& ActiveGC, TArray<FClusterUnionPhysicsProxy*>& ActiveClusterUnions);`
- L392 _private prototype_ `virtual void PrepareAdvanceBy(const FReal DeltaTime) override;` — /
- L393 _private prototype_ `virtual void AdvanceSolverBy(const FSubStepInfo& SubStepInfo) override;`
- L394 _private prototype_ `virtual void PushPhysicsState(const FReal ExternalDt, const int32 NumSteps, const int32 NumExternalSteps) override;`
- L395 _private prototype_ `virtual void SetExternalTimestampConsumed_Internal(const int32 Timestamp) override;`
- L397 _private prototype_ `void ClearCollisionEventsForProxy(const IPhysicsProxyBase* Proxy);`
- L399 _private prototype_ `void ApplyCVars();`
- L401 _private prototype_ `void UpdateIsDeterministic();`
- L403 _private prototype_ `void DebugDrawShapes(const bool bShowStatic, const bool bShowKinematic, const bool bShowDynamic) const;`
- L408 _private member_ `int32 CurrentFrame;` — Solver Data
- L409 _private member_ `bool bHasFloor;`
- L410 _private member_ `bool bIsFloorAnalytic;`
- L411 _private member_ `FReal FloorHeight;`
- L412 _private member_ `bool bIsDeterministic;`
- L415 _private member_ `TUniquePtr<Private::FTaskDispatcherSolver> TaskDispatcher;` — Task dispatcher manage the task graph logic
- L424 _private member_ `THandleArray<FChaosPhysicsMaterial> QueryMaterials_External;` — Physics material mirrors for the solver. These should generally stay in sync with the global material list from the game thread. This data is read only in the solver as we should never need to update it here. External threads can Enqueue commands to change parameters. There are two copies here to enable SQ to lock only the solvers that it needs to handle the material access during a query instead of having to lock the entire physics state of the runtime. NOTE: Must be before MEvolution because they are passed to it in the constructor
- L425 _private member_ `THandleArray<FChaosPhysicsMaterialMask> QueryMaterialMasks_External;`
- L426 _private member_ `THandleArray<FChaosPhysicsMaterial> SimMaterials;`
- L427 _private member_ `THandleArray<FChaosPhysicsMaterialMask> SimMaterialMasks;`
- L429 _private member_ `FParticleUniqueIndicesMultithreaded UniqueIndices;`
- L430 _private member_ `FParticlesType Particles;`
- L431 _private member_ `TUniquePtr<FPBDRigidsEvolution> MEvolution;`
- L432 _private member_ `TUniquePtr<FEventManager> MEventManager;`
- L433 _private member_ `TUniquePtr<FSolverEventFilters> MSolverEventFilters;`
- L434 _private member_ `TUniquePtr<FDirtyParticlesBuffer> MDirtyParticlesBuffer;`
- L439 _private member_ `TSharedPtr<FCriticalSection> MCurrentLock;` — Proxies
- L440 _private member_ `TSparseArray< FSingleParticlePhysicsProxy* > SingleParticlePhysicsProxies_PT;`
- L441 _private member_ `TArray< FGeometryCollectionPhysicsProxy* > GeometryCollectionPhysicsProxies_Internal;` — PT
- L442 _private member_ `TArray< FGeometryCollectionPhysicsProxy* > GeometryCollectionPhysicsProxiesField_Internal;` — PT
- L443 _private member_ `TArray< FClusterUnionPhysicsProxy* > ClusterUnionPhysicsProxies_Internal;` — PT
- L444 _private member_ `TArray< FJointConstraintPhysicsProxy* > JointConstraintPhysicsProxies_Internal;` — PT
- L445 _private member_ `TArray< FCharacterGroundConstraintProxy* > CharacterGroundConstraintProxies_Internal;`
- L447 _private member_ `TUniquePtr<FPerSolverFieldSystem> PerSolverField;`
- L449 _private member_ `FSolverSerializer Serializer;`
- L451 _private member_ `FSolverParticleUnregisteredGT EventParticleUnregisteredGT;`
- L478 _private member_ `TArray<FPendingDestroyInfo> PendingDestroyPhysicsProxy;`
- L479 _private member_ `TArray<FPendingProxyDestroyInfo<FGeometryCollectionPhysicsProxy>> PendingDestroyGeometryCollectionPhysicsProxy;`
- L480 _private member_ `TArray<FPendingProxyDestroyInfo<FClusterUnionPhysicsProxy>> PendingDestroyClusterUnionProxy;`
- L482 _private prototype_ `void ProcessSinglePushedData_Internal(FPushPhysicsData& PushData);`
- L483 _private prototype_ `virtual void ProcessPushedData_Internal(FPushPhysicsData& PushData) override;`
- L484 _private prototype_ `void DestroyPendingProxies_Internal();`
- L489 _private prototype_ `void ProcessSkippedFramePushData_Internal(FPushPhysicsData& PushData, int32 SkippedFrame);` — Process callback lifecycle (add/remove) and SimCommands from a skipped frame's PushData. Skips dirty proxy processing and input assignment. Used during adaptive resim coalescing. Caller must set MTime to the correct value for the skipped frame before calling.
- L491 _private prototype_ `virtual void ConditionalApplyRewind_Internal() override;`
- L494 _private function_ `virtual bool IsResimming() const` — Check if we are resimming or not
- L497 _private prototype_ `void SetIsResimming(bool bIsResimming);` — Sets if we are resimming or not
- L501 _public prototype_ `virtual void SetDebugDrawScene(const ChaosDD::Private::FChaosDDScenePtr& InCDDScene) override final;`
- L506 _private member_ `ChaosDD::Private::FChaosDDScenePtr CDDScene;` — NOTE: A physics frame may consist of multiple sub-steps (ticks) so this debug draw timeline only captures debug draw that happens outside of the tick(s). See FPBDRigidsEvolutionGBF::SetDebugDrawScene
- L507 _private member_ `ChaosDD::Private::FChaosDDTimelinePtr CDDFrameTimeline;`

#### struct `Chaos::FPBDRigidsSolver::FPendingDestroyInfo`  
`struct FPendingDestroyInfo`  
_L453-464_
- L455 _public member_ `FSingleParticlePhysicsProxy* Proxy;`
- L456 _public member_ `int32 DestroyOnStep;`
- L457 _public member_ `FGeometryParticleHandle* Handle;`
- L458 _public member_ `FUniqueIdx UniqueIdx;`
- L460 _public function_ `const bool operator==(const FPendingDestroyInfo Other) const`

#### struct `Chaos::FPBDRigidsSolver::FPendingProxyDestroyInfo`  
`template<typename ProxyType> struct FPendingProxyDestroyInfo`  
_L467-476_
- L469 _public member_ `ProxyType* Proxy;`
- L470 _public member_ `int32 DestroyOnStep;`
- L472 _public function_ `const bool operator==(const FPendingProxyDestroyInfo Other) const`

#### struct `Chaos::TSolverSimMaterialScope`  
`template<> struct TSolverSimMaterialScope<ELockType::Read>`  
_L512-531_
- L81 _public prototype_ `TSolverSimMaterialScope() = delete;`
- L517 _public function_ `explicit TSolverSimMaterialScope(FPhysicsSolverBase* InSolver) : Solver(InSolver)`
- L524 _public function_ `~TSolverSimMaterialScope()`
- L530 _private member_ `FPhysicsSolverBase* Solver;`

#### struct `Chaos::TSolverSimMaterialScope`  
`template<> struct TSolverSimMaterialScope<ELockType::Write>`  
_L534-552_
- L81 _public prototype_ `TSolverSimMaterialScope() = delete;`
- L517 _public function_ `explicit TSolverSimMaterialScope(FPhysicsSolverBase* InSolver) : Solver(InSolver)`
- L524 _public function_ `~TSolverSimMaterialScope()`
- L530 _private member_ `FPhysicsSolverBase* Solver;`

#### Free symbols / members of external scopes

- L38 _macro_ `#define PBDRIGID_PREALLOC_COUNT 1024`
- L39 _macro_ `#define KINEMATIC_GEOM_PREALLOC_COUNT 100`
- L40 _macro_ `#define GEOMETRY_PREALLOC_COUNT 100`
- L42 _externvar_ `extern int32 ChaosSolverParticlePoolNumFrameUntilShrink;`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSolverParticleUnregisteredGT, Chaos::FSingleParticlePhysicsProxy* , Chaos::FUniqueIdx );`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSolverParticleUnregisteredGT, Chaos::FSingleParticlePhysicsProxy* , Chaos::FUniqueIdx );`
- L46 _namespace_ `namespace ChaosTest`
- L49 _prototype_ `template <typename TSolver> void AdvanceSolverNoPushHelper(TSolver* Solver, Chaos::FReal Dt);` (scope `ChaosTest`)
- L52 _namespace_ `namespace Chaos`
- L52 _namespace_ `namespace Private` (scope `Chaos`)
- L56 _prototype_ `UE_INTERNAL bool IsUsingSingleThreadPullData();` (scope `Chaos::Private`)
- L61 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsCoreTypes.h` (Public)


#### enum `EChaosSolverTickMode`  
`enum class EChaosSolverTickMode : uint8`  
_L11-17_
- reflection: `UENUM()`
- L13 _public enumerator_ `Fixed`
- L14 _public enumerator_ `Variable`
- L15 _public enumerator_ `VariableCapped`
- L16 _public enumerator_ `VariableCappedWithTarget`

#### enum `EChaosThreadingMode`  
`enum class EChaosThreadingMode : uint8`  
_L20-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `DedicatedThread UMETA(Hidden)`
- L23 _public enumerator_ `TaskGraph`
- L24 _public enumerator_ `SingleThread`
- L25 _public enumerator_ `Num UMETA(Hidden)`
- L26 _public enumerator_ `Invalid UMETA(Hidden)`

#### enum `EChaosBufferMode`  
`enum class EChaosBufferMode : uint8`  
_L30-36_
- reflection: `UENUM()`
- L32 _public enumerator_ `Double`
- L33 _public enumerator_ `Triple`
- L34 _public enumerator_ `Num UMETA(Hidden)`
- L35 _public enumerator_ `Invalid UMETA(Hidden)`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace Chaos`
- L43 _typedef_ `typedef Chaos::TPBDRigidParticles<Chaos::FReal, 3> FParticlesType;`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsObjectHelper.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/AnalyticImplicitGroup.h` (Public)


#### class `FAnalyticImplicitGroup`  
`class FAnalyticImplicitGroup`  
_L23-652_
- desc: A collection of analytic implicit shapes parented to a single transform, in a hierarchy of transforms. Currently we use this class to represent bones even if they don't have any implicit shapes.
- L26 _public function_ `FAnalyticImplicitGroup() : BoneName(NAME_None) , BoneIndex(INDEX_NONE) , ParentBoneIndex(INDEX_NONE) , RigidBodyId(INDEX_NONE) , RigidBodyState(EObjectStateTypeEnum::Chaos_Object_Kinematic) , Parent(nullptr)`
- L34 _public function_ `FAnalyticImplicitGroup(const FName &InBoneName, const int32 InBoneIndex) : BoneName(InBoneName) , BoneIndex(InBoneIndex) , ParentBoneIndex(INDEX_NONE) , RigidBodyId(INDEX_NONE) , RigidBodyState(EObjectStateTypeEnum::Chaos_Object_Kinematic) , Parent(nullptr)`
- L42 _public prototype_ `FAnalyticImplicitGroup(const FAnalyticImplicitGroup &) = delete;`
- L43 _public function_ `FAnalyticImplicitGroup(FAnalyticImplicitGroup &&Other) : BoneName(MoveTemp(Other.BoneName)) , BoneIndex(MoveTemp(Other.BoneIndex)) , ParentBoneIndex(MoveTemp(Other.ParentBoneIndex)) , RigidBodyId(MoveTemp(Other.RigidBodyId)) , RigidBodyState(MoveTemp(Other.RigidBodyState)) , Spheres(MoveTemp(Other.Spheres)) , Boxes(MoveTemp(Other.Boxes)) , Capsules(MoveTemp(Other.Capsules)) , TaperedCylinders(MoveTemp(Other.TaperedCylinders)) , ConvexHulls(MoveTemp(Other.ConvexHulls)) , LevelSets(MoveTemp(Other.LevelSets)) , Transforms(MoveTemp(Other.Transforms)) , Parent(MoveTemp(Other.Parent)) , Children(MoveTemp(Other.Children))`
- L62 _public function_ `~FAnalyticImplicitGroup()`
- L72 _public function_ `void Init(const int32 NumStructures, const bool DoCollGeom=true)`
- L83 _public function_ `int32 NumStructures() const` — The number of analytic shapes in this group.
- L85 _public function_ `bool IsValid()`
- L87 _public function_ `const FName& GetBoneName() const`
- L88 _public function_ `const int32 GetBoneIndex() const`
- L90 _public function_ `void SetParentBoneIndex(const int32 InParentBoneIndex)`
- L91 _public function_ `const int32 GetParentBoneIndex() const`
- L93 _public function_ `void SetRigidBodyId(const int32 InRigidBodyId)`
- L94 _public function_ `int32 GetRigidBodyId() const`
- L96 _public function_ `void SetRigidBodyState(const EObjectStateTypeEnum State)`
- L97 _public function_ `EObjectStateTypeEnum GetRigidBodyState() const`
- L99 _public function_ `int32 Add(const FTransform &InitialXf, Chaos::FSphere *Sphere)`
- L100 _public function_ `int32 Add(const FTransform &InitialXf, Chaos::TBox<Chaos::FReal, 3> *Box)`
- L101 _public function_ `int32 Add(const FTransform &InitialXf, Chaos::FCapsule *Capsule)`
- L102 _public function_ `int32 Add(const FTransform &InitialXf, Chaos::FTaperedCylinder *TaperedCylinder)`
- L103 _public function_ `int32 Add(const FTransform &InitialXf, Chaos::FConvex *ConvexHull)`
- L104 _public function_ `int32 Add(const FTransform &InitialXf, Chaos::FLevelSet *LevelSet)`
- L106 _public function_ `void SetCollisionTopology( const int32 Index, TArray<Chaos::FVec3>&& Points, TArray<Chaos::TVec3<int32>>&& Triangles)`
- L112 _public function_ `const TArray<FTransform>& GetInitialStructureTransforms() const`
- L113 _public function_ `void ResetTransforms()`
- L115 _public function_ `Chaos::FMassProperties BuildMassProperties( const Chaos::FReal Density, Chaos::FReal& TotalMass)`
- L261 _public function_ `TArray<Chaos::FVec3>* BuildSamplePoints( const Chaos::FReal ParticlesPerUnitArea, const int32 MinParticles, const int32 MaxParticles)`
- L380 _public function_ `TArray<Chaos::TVec3<int32>> BuildSampleTopology() const`
- L408 _public function_ `Chaos::FImplicitObject* BuildSimImplicitObject()` — Build the implicit object representation of this object. Transfers ownership of sub structures to the returned implicit object.
- L467 _protected function_ `void SetParent(FAnalyticImplicitGroup *InParent)`
- L469 _protected function_ `const FAnalyticImplicitGroup* GetParent() const`
- L472 _protected function_ `void AddChild(FAnalyticImplicitGroup *Child)`
- L474 _protected function_ `const TArray<FAnalyticImplicitGroup*>& GetChildren() const`
- L477 _protected function_ `void ClearHierarchy()`
- L481 _protected function_ `template<class TImplicitShape> void CullDeepPoints(TArray<Chaos::FVec3>& Points, const TImplicitShape& Shape, const FTransform& Xf)`
- L512 _protected function_ `void CullDeepPoints(TArray<Chaos::FVec3>& Points, const int32 SkipIndex)`
- L565 _protected function_ `Chaos::FImplicitObject* TransferImplicitObj(int32 Idx)`
- L623 _protected member_ `FName BoneName;`
- L624 _protected member_ `int32 BoneIndex;`
- L625 _protected member_ `int32 ParentBoneIndex;`
- L627 _protected member_ `int32 RigidBodyId;`
- L628 _protected member_ `EObjectStateTypeEnum RigidBodyState;`
- L631 _protected member_ `TArray<Chaos::FSphere*> Spheres;` — FkSphereElem and FKTaperedCapsuleElem ends
- L633 _protected member_ `TArray<Chaos::TBox<Chaos::FReal, 3>*> Boxes;` — FKBoxElem
- L635 _protected member_ `TArray<Chaos::FCapsule*> Capsules;` — FKSphylElem - Z axis is capsule axis
- L637 _protected member_ `TArray<Chaos::FTaperedCylinder*> TaperedCylinders;` — FKTaperedCapsuleElem - Z axis is the capsule axis
- L639 _protected member_ `TArray<Chaos::FConvex*> ConvexHulls;` — FKConvexElem
- L641 _protected member_ `TArray<Chaos::FLevelSet*> LevelSets;` — Chaos::TConvex replacement
- L643 _protected member_ `TArray<Chaos::FVec3> ContiguousCollisionPoints;`
- L644 _protected member_ `TArray<TArray<Chaos::FVec3>> CollisionPoints;`
- L645 _protected member_ `TArray<TArray<Chaos::TVec3<int32>>> CollisionTriangles;`
- L647 _protected member_ `TArray<FTransform> Transforms;`
- L648 _protected member_ `FTransform RefBoneXf;`
- L650 _protected member_ `FAnalyticImplicitGroup* Parent;`
- L651 _protected member_ `TArray<FAnalyticImplicitGroup*> Children;`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/CharacterGroundConstraintProxy.h` (Public)


#### class `Chaos::FCharacterGroundConstraintProxy`  
`class FCharacterGroundConstraintProxy : public IPhysicsProxyBase`  
_L17-69_
- inherits: `IPhysicsProxyBase`
- desc: Proxy class to manage access to and syncing of character ground constraint data between the game thread and physics thread
- L20 _public typedef_ `using Base = IPhysicsProxyBase;`
- L22 _public prototype_ `FCharacterGroundConstraintProxy(FCharacterGroundConstraint* InConstraintGT, FCharacterGroundConstraintHandle* InConstraintPT = nullptr, UObject* InOwner = nullptr);`
- L27 _public function_ `FCharacterGroundConstraint* GetGameThreadAPI()`
- L28 _public function_ `const FCharacterGroundConstraint* GetGameThreadAPI() const`
- L30 _public function_ `FCharacterGroundConstraintHandle* GetPhysicsThreadAPI()`
- L31 _public function_ `const FCharacterGroundConstraintHandle* GetPhysicsThreadAPI() const`
- L37 _public prototype_ `void InitializeOnPhysicsThread(FPBDRigidsSolver* InSolver, FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData);` — Gets the data from the game thread via the RemoteData and creates a constraint on the physics thread
- L40 _public prototype_ `void PushStateOnGameThread(FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData);` — Pushes any changed data from the game thread constraint to the remote data
- L43 _public prototype_ `void PushStateOnPhysicsThread(FPBDRigidsSolver* InSolver, const FDirtyPropertiesManager& Manager, int32 DataIdx, const FDirtyChaosProperties& RemoteData);` — Reads changed data from the game thread constraint into the physics thread constraint via the remote data
- L46 _public prototype_ `void DestroyOnGameThread();` — Deletes the game thread constraint
- L49 _public prototype_ `void DestroyOnPhysicsThread(FPBDRigidsSolver* InSolver);` — Removes references to the physics thread constraint and deletes it
- L54 _public function_ `virtual void* GetHandleUnsafe() const override`
- L60 _public prototype_ `void BufferPhysicsResults(FDirtyCharacterGroundConstraintData& Buffer);` — Write the output constraint data from the physics thread to the buffer
- L63 _public prototype_ `bool PullFromPhysicsState(const FDirtyCharacterGroundConstraintData& Buffer, const int32 SolverSyncTimestamp);` — Write the output constraint data from the buffer to the game thread
- L66 _private member_ `FCharacterGroundConstraint* Constraint_GT;`
- L67 _private member_ `FCharacterGroundConstraintHandle* Constraint_PT;`
- L68 _private member_ `bool bInitialized = false;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/ClusterUnionPhysicsProxy.h` (Public)


#### struct `Chaos::FClusterUnionChildData`  
`struct FClusterUnionChildData`  
_L20-27_
- L22 _public member_ `FUniqueIdx ParticleIdx;`
- L23 _public member_ `FTransform ChildToParent;`
- L24 _public member_ `IPhysicsProxyBase* Proxy = nullptr;`
- L25 _public member_ `void* CachedOwner = nullptr;`
- L26 _public member_ `int32 BoneId = INDEX_NONE;`

#### struct `Chaos::FClusterUnionInitData`  
`struct FClusterUnionInitData`  
_L29-44_
- L31 _public member_ `void* UserData;`
- L32 _public member_ `FTransform InitialTransform;`
- L33 _public member_ `uint32 ActorId = INDEX_NONE;`
- L34 _public member_ `uint32 ComponentId = INDEX_NONE;`
- L35 _public member_ `bool bCheckConnectivity = true;`
- L36 _public member_ `bool bUnbreakable = false;`
- L37 _public member_ `bool bGenerateConnectivityEdges = true;`
- L38 _public member_ `int32 GravityGroupOverride = INDEX_NONE;`
- L39 _public member_ `bool bCCDEnabled = false;`
- L40 _public member_ `bool bMACDEnabled = false;`
- L42 _public member_ `TSharedPtr<FString, ESPMode::ThreadSafe> DebugName;`

#### struct `Chaos::FClusterUnionSyncedData`  
`struct FClusterUnionSyncedData`  
_L49-59_
- desc: Extra data that needs to be synced between the PT and GT for cluster unions.
- L52 _public member_ `bool bIsAnchored = true;` — Whether the cluster is anchored or not.
- L55 _public member_ `bool bDidSyncGeometry = false;` — Whether we assigned new geometry from the PT in PullFromPhysicsState
- L58 _public member_ `TArray<FClusterUnionChildData> ChildParticles;` — Data on every child particle in the cluster union.

#### class `Chaos::FClusterUnionPhysicsProxy`  
`class FClusterUnionPhysicsProxy : public TPhysicsProxy<FClusterUnionPhysicsProxy, void, FClusterUnionProxyTimestamp>`  
_L62-233_
- inherits: `TPhysicsProxy<FClusterUnionPhysicsProxy,void,FClusterUnionProxyTimestamp>`
- L64 _private typedef_ `using Base = TPhysicsProxy<FClusterUnionPhysicsProxy, void, FClusterUnionProxyTimestamp>;`
- L67 _public typedef_ `using FExternalParticle = TPBDRigidParticle<FReal, 3>;` — The mismatch here is fine since we really only need to sync a few properties between the PT and the GT.
- L68 _public typedef_ `using FInternalParticle = TPBDRigidClusteredParticleHandle<Chaos::FReal, 3>;`
- L70 _public prototype_ `FClusterUnionPhysicsProxy() = delete;`
- L71 _public prototype_ `FClusterUnionPhysicsProxy(UObject* InOwner, const FClusterCreationParameters& InParameters, const FClusterUnionInitData& InInitData);`
- L74 _public prototype_ `void AddPhysicsObjects_External(const TArray<FPhysicsObjectHandle>& Objects);` — Add physics objects to the cluster union. Should only be called from the game thread.
- L75 _public function_ `const FClusterUnionSyncedData& GetSyncedData_External() const`
- L78 _public prototype_ `void RemovePhysicsObjects_External(const TSet<FPhysicsObjectHandle>& Objects);` — Remove physics objects from the cluster union.
- L81 _public prototype_ `void SetIsAnchored_External(bool bIsAnchored);` — Set/Remove any anchors on the cluster particle.
- L84 _public prototype_ `EObjectStateType GetObjectState_External() const;` — Set Object State.
- L85 _public prototype_ `void SetObjectState_External(EObjectStateType State);`
- L87 _public prototype_ `ESleepType GetSleepType_External() const;`
- L88 _public prototype_ `void SetSleepType_External(const ESleepType SleepType);`
- L90 _public prototype_ `bool GetDisabled_External() const;`
- L91 _public prototype_ `void SetDisabled_External(const bool Disabled);`
- L93 _public prototype_ `bool GetGravityEnabled_External() const;`
- L94 _public prototype_ `void SetGravityEnabled_External(const bool Enabled);`
- L97 _public prototype_ `void Wake_External();` — Explicitly wake the physics object. The wakes the physics object if it is sleeping and resets any sleep state (whether awake or sleeping)
- L101 _public prototype_ `void SetMass_External(Chaos::FReal Mass);` — Set the cluster mass. NOTE: When a cluster breaks its mass will be recalculated from the remaining children on the PT, effectively undoing this work.
- L104 _public prototype_ `void SetGeometry_External(const Chaos::FImplicitObjectPtr& Geometry, const TArray<FPBDRigidParticle*>& ShapeParticles);` — Set GT geometry - this is only for smoothing over any changes until the PT syncs back to the GT.
- L107 _public prototype_ `void MergeGeometry_External(TArray<Chaos::FImplicitObjectPtr>&& ImplicitGeometries, const TArray<FPBDRigidParticle*>& ShapeParticles);` — Merge GT geometry into the existing union
- L110 _public prototype_ `void RemoveShapes_External(const TArray<FPBDRigidParticle*>& ShapeParticles);` — Remove GT shapes from the existing unions
- L113 _public function_ `void SetSharedGeometry_External(const TSharedPtr<Chaos::FImplicitObject, ESPMode::ThreadSafe>& Geometry, const TArray<FPBDRigidParticle*>& ShapeParticles)` — `UE_DEPRECATED(5.4, "Please use SetGeometry_External instead")`
- L122 _public prototype_ `void Initialize_External();` — Cluster union proxy initialization happens in two first on the game thread (external) then on the physics thread (internal). Cluster unions are a primarily physics concept so the things exposed to an external context is just there to be able to safely query the state on the physics thread and to be able to add/remove things to the proxy itself (rather than to move it, for example).
- L124 _public function_ `bool IsInitializedOnPhysicsThread() const`
- L125 _public prototype_ `void Initialize_Internal(FPBDRigidsSolver* RigidsSolver, FPBDRigidsSolver::FParticlesType& Particles);`
- L127 _public function_ `FExternalParticle* GetParticle_External() const`
- L128 _public function_ `FInternalParticle* GetParticle_Internal() const`
- L129 _public function_ `virtual void* GetHandleUnsafe() const override`
- L130 _public function_ `FPhysicsObjectHandle GetPhysicsObjectHandle() const`
- L132 _public function_ `bool HasChildren_External() const`
- L133 _public prototype_ `bool HasChildren_Internal() const;`
- L135 _public function_ `bool IsAnchored_External() const`
- L137 _public prototype_ `void SetXR_External(const FVector& X, const FQuat& R);`
- L138 _public prototype_ `void SetLinearVelocity_External(const FVector& V);`
- L139 _public prototype_ `void SetAngularVelocity_External(const FVector& W);`
- L140 _public prototype_ `void SetChildToParent_External(FPhysicsObjectHandle Child, const FTransform& RelativeTransform, bool bLock);`
- L141 _public prototype_ `void BulkSetChildToParent_External(const TArray<FPhysicsObjectHandle>& Objects, const TArray<FTransform>& Transforms, bool bLock);`
- L142 _public prototype_ `void ChangeMainParticleStatus_External(const TArray<FPhysicsObjectHandle>& Objects, bool bIsMain);`
- L148 _public prototype_ `void PushToPhysicsState(const FDirtyPropertiesManager& Manager, int32 DataIdx, const FDirtyProxy& Dirty);` — These functions take care of marshaling data back and forth between the game thread and the physics thread.
- L149 _public prototype_ `bool PullFromPhysicsState(const FDirtyClusterUnionData& PullData, int32 SolverSyncTimestamp, const FDirtyClusterUnionData* NextPullData = nullptr, const FRealSingle* Alpha = nullptr, const FDirtyRigidParticleReplicationErrorData* Error = nullptr, const Chaos::FReal AsyncFixedTimeStep = 0);`
- L151 _public prototype_ `void BufferPhysicsResults_Internal(FDirtyClusterUnionData& BufferData);`
- L152 _public prototype_ `void BufferPhysicsResults_External(FDirtyClusterUnionData& BufferData);`
- L154 _public prototype_ `void SyncRemoteData(FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData) const;`
- L155 _public prototype_ `void ClearAccumulatedData();`
- L157 _public function_ `FProxyInterpolationBase* GetInterpolationData()`
- L158 _public function_ `const FProxyInterpolationBase* GetInterpolationData() const`
- L160 _public function_ `FClusterUnionIndex GetClusterUnionIndex() const`
- L162 _public function_ `void ForceSetGeometryChildParticles_External(TArray<FExternalParticle*>&& InParticles)`
- L164 _public prototype_ `void SetEnableStrainOnCollision_External(bool bEnable);`
- L165 _public function_ `bool GetEnableStrainOnCollision_Internal() const`
- L168 _private member_ `bool bIsInitializedOnPhysicsThread: 1 = false;`
- L169 _private member_ `bool bEnableStrainOnCollision_Internal : 1 = true;`
- L171 _private member_ `FClusterCreationParameters ClusterParameters;`
- L172 _private member_ `const FClusterUnionInitData InitData;`
- L174 _private member_ `FPhysicsObjectUniquePtr PhysicsObject;`
- L175 _private member_ `TUniquePtr<FExternalParticle> Particle_External;`
- L176 _private member_ `FClusterUnionSyncedData SyncedData_External;`
- L178 _private member_ `FInternalParticle* Particle_Internal = nullptr;`
- L179 _private member_ `FClusterUnionIndex ClusterUnionIndex = INDEX_NONE;`
- L181 _private member_ `TUniquePtr<FProxyInterpolationBase> InterpolationData;`
- L186 _public function_ `template<typename ErrorDataType> ErrorDataType* GetOrCreateErrorInterpolationData()` — Get or create a derived FProxyInterpolationBase that handles render interpolation error corrections
- L201 _public function_ `template<typename ErrorDataType> const ErrorDataType* GetErrorInterpolationData() const`
- L206 _public function_ `void ResetInterpolationData()`
- L215 _private member_ `TArray<FExternalParticle*> GeometryChildParticles_External;` — An array of a particles that exist in the external implicit object union. Note that this array should only be used for book-keeping. It is generally unsafe to try and access the particles within this array.
- L219 _public function_ `bool IsSimulating() const`
- L220 _public function_ `void UpdateKinematicBodiesCallback(const FParticlesType& InParticles, const float InDt, const float InTime, FKinematicProxy& InKinematicProxy)`
- L221 _public function_ `void StartFrameCallback(const float InDt, const float InTime)`
- L222 _public function_ `void EndFrameCallback(const float InDt)`
- L223 _public function_ `void CreateRigidBodyCallback(FParticlesType& InOutParticles)`
- L224 _public function_ `void DisableCollisionsCallback(TSet<TTuple<int32, int32>>& InPairs)`
- L225 _public function_ `void AddForceCallback(FParticlesType& InParticles, const float InDt, const int32 InIndex)`
- L226 _public function_ `void BindParticleCallbackMapping(Chaos::TArrayCollectionArray<PhysicsProxyWrapper>& PhysicsProxyReverseMap, Chaos::TArrayCollectionArray<int32>& ParticleIDReverseMap)`
- L227 _public function_ `static constexpr EPhysicsProxyType ConcreteType()`
- L228 _public function_ `void SyncBeforeDestroy()`
- L229 _public function_ `void OnRemoveFromScene()`
- L230 _public function_ `bool IsDirty()`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/FieldSystemProxyHelper.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`
- L30 _function_ `template <typename PhysicsProxy> static bool BuildFieldSamplePoints( PhysicsProxy* LocalProxy, Chaos::FPBDRigidsSolver* RigidSolver, const FFieldSystemCommand& FieldCommand, FFieldExecutionDatas& ExecutionDatas, EFieldResolutionType& PrevResolutionType, EFieldFilterType& PrevFilterType, EFieldObjectType& PrevObjectType, EFieldPositionType& PrevPositionType)` (scope `Chaos`) — Build the sample points positions and indices based on the resolution and filter type @param    LocalProxy Physics proxy from which to extract the particle handles @param    RigidSolver Rigid solver owning the particles @param    FieldCommand Field command used to extract the resolution and filter meta data @param    ExecutionDatas Field Datas stored during evaluation @param    PrevResolutionType Resolution of the previous command @param    PrevFilterType Filter of the previous command @param    PrevObjectType Object Type of the previous command @param    PrevPositionType Position type of the previous command
- L86 _function_ `` (scope `Chaos::BuildFieldSamplePoints`)
- L159 _function_ `static void InitDynamicStateResults(const TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, FFieldContext& FieldContext, TArray<int32>& LocalResults)` (scope `Chaos`) — Init the dynamics state of the particle handles to be processed by the field @param    ParticleHandles Particle hadles that will be used to init the dynamic state @param    FieldContext Field context to retrieve the evaluated samples @param    LocalResults Array to store the dynamic state
- L175 _function_ `static void InitActivateDisabledResults(const TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, FFieldContext& FieldContext, TArray<int32>& LocalResults)` (scope `Chaos`) — Init the enable/disable boolean array of the particle handles to be processed by the field @param    ParticleHandles Particle hadles that will be used to init the enable/disable booleans @param    FieldContext Field context to retrieve the evaluated samples @param    LocalResults Array to store the enable/disable boolean
- L193 _function_ `static void SetParticleDynamicState(Chaos::FPBDRigidsSolver* RigidSolver, const Chaos::EObjectStateType FieldState, Chaos::FPBDRigidParticleHandle* RigidHandle)` (scope `Chaos`) — Set the dynamic state of a particle handle @param    Rigidsolver Rigid solver owning the particle handle @param    FieldState Field state that will be set on the handle @param    RigidHandle Particle hadle on which the state will be set
- L230 _function_ `static bool ReportDynamicStateResult(Chaos::FPBDRigidsSolver* RigidSolver, const Chaos::EObjectStateType FieldState, Chaos::FPBDRigidParticleHandle* RigidHandle, const bool HasInitialLinearVelocity, const Chaos::FVec3& InitialLinearVelocity, const bool HasInitialAngularVelocity, const Chaos::FVec3& InitialAngularVelocity)` (scope `Chaos`) — Report the dynamic state result onto the handle @param    Rigidsolver Rigid solver owning the particle handle @param    FieldState Field state that will be set on the handle @param    RigidHandle Particle hadle on which the state will be set @param    HasInitialLinearVelocity Boolean to check if we have to set the initial linear velocity @param    InitialLinearVelocity Initial linear velocity to potentially set onto the handle @param    HasInitialAngularVelocity Boolean to check if we have to set the initial angular velocity @param    InitialAngularVelocity Initial angular velocity to potentially set onto the handle
- L270 _function_ `static void UpdateSolverParticlesState(Chaos::FPBDRigidsSolver* RigidSolver, const TFieldArrayView<FFieldContextIndex>& UpdatedParticleIndices, const TArray<Chaos::FGeometryParticleHandle*>& Particles)` (scope `Chaos`) — Update all the clustered particles object state to static/kinematic if one of its children state has been changed to static/kinematic @param    Rigidsolver Rigid solver owning the particle handle @param    UpdatedParticles List of particles that had their state updated
- L317 _function_ `static void UpdateMaterialSleepingThreshold(Chaos::FPBDRigidsSolver* RigidSolver, Chaos::FPBDRigidParticleHandle* RigidHandle, const Chaos::FReal ResultThreshold)` (scope `Chaos`) — Update the handle sleeping linear and angular theshold @param    Rigidsolver Rigid solver owning the particle handle @param    RigidHandle Particle handle on which the threshold will be updated @param    ResultThreshold Threshoild to be set onto the handle
- L347 _function_ `static void UpdateMaterialDisableThreshold(Chaos::FPBDRigidsSolver* RigidSolver, Chaos::FPBDRigidParticleHandle* RigidHandle, const Chaos::FReal ResultThreshold)` (scope `Chaos`) — Update the handle disable linear and angular theshold @param    Rigidsolver Rigid solver owning the particle handle @param    RigidHandle Particle handle on which the threshold will be updated @param    ResultThreshold Threshoild to be set onto the handle
- L381 _function_ `static void FieldIntegerParameterUpdate(Chaos::FPBDRigidsSolver* RigidSolver, const FFieldSystemCommand& FieldCommand, TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, FFieldContext& FieldContext, Chaos::FPBDPositionConstraints& PositionTarget, TMap<int32, int32>& TargetedParticles, TArray<int32>& FinalResults)` (scope `Chaos`) — Update the particle handles integer parameters based on the field evaluation @param    RigidSolver Rigid solver owning the particles @param    FieldCommand Field command to be used for the parameter field evaluatation @param    ParticleHandles List of particle handles extracted from the field command meta data @param	 FieldContext Field context that will be used for field evaluation @param    PositionTarget Chaos position contraint in which each target will be added @param    TargetedParticles List of particles (source/target) that will be filled by the PositionTarget/static parameter @param    FinalResults Array in which will be stored the field nodes evaulation
- L495 _function_ `static void FieldScalarParameterUpdate(Chaos::FPBDRigidsSolver* RigidSolver, const FFieldSystemCommand& FieldCommand, TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, FFieldContext& FieldContext, Chaos::FPBDPositionConstraints& PositionTarget, TMap<int32, int32>& TargetedParticles, TArray<float>& FinalResults)` (scope `Chaos`) — Update the particle handles scalar parameters based on the field evaluation @param    RigidSolver Rigid solver owning the particles @param    FieldCommand Field command to be used for the parameter field evaluatation @param    ParticleHandles List of particle handles extracted from the field command meta data @param	 FieldContext Field context that will be used for field evaluation @param    PositionTarget Chaos position contraint in which each target will be added @param    TargetedParticles List of particles (source/target) that will be filled by the PositionTarget/Static parameter @param    FinalResults Array in which will be stored the field nodes evaulation
- L596 _function_ `static void FieldVectorParameterUpdate(Chaos::FPBDRigidsSolver* RigidSolver, const FFieldSystemCommand& FieldCommand, TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, FFieldContext& FieldContext, Chaos::FPBDPositionConstraints& PositionTarget, TMap<int32, int32>& TargetedParticles, TArray<FVector>& FinalResults)` (scope `Chaos`) — Update the particle handles vector parameters based on the field evaluation @param    RigidSolver Rigid solver owning the particles @param    FieldCommand Field command to be used for the parameter field evaluatation @param    ParticleHandles List of particle handles extracted from the field command meta data @param	 FieldContext Field context that will be used for field evaluation @param    PositionTarget Chaos position contraint in which each target will be added @param    TargetedParticles List of particles (source/target) that will be filled by the PositionTarget/Static parameter @param    FinalResults Array in which will be stored the field nodes evaulation
- L711 _function_ `static void FieldVectorForceUpdate(Chaos::FPBDRigidsSolver* RigidSolver, const FFieldSystemCommand& FieldCommand, TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, FFieldContext& FieldContext, TArray<FVector>& FinalResults)` (scope `Chaos`)
- L757 _function_ `FORCEINLINE bool IsParameterFieldValid(const FFieldSystemCommand& FieldCommand)`
- L783 _function_ `FORCEINLINE bool IsForceFieldValid(const FFieldSystemCommand& FieldCommand)`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/GeometryCollectionPhysicsProxy.h` (Public)


#### struct `FGeometryCollectionItemIndex`  
`struct FGeometryCollectionItemIndex`  
_L40-115_
- desc: index abstraction for HitResults this allows regular bones and internal clusters to be represented by a unique int32 index that can be passed to HitResults and in return understood by the geometry collection physics proxy
- L43 _public function_ `static FGeometryCollectionItemIndex CreateInternalClusterItemIndex(int32 ClusterUniqueIdx)`
- L48 _public function_ `static FGeometryCollectionItemIndex CreateTransformItemIndex(int32 TransformIndex)`
- L53 _public function_ `static FGeometryCollectionItemIndex CreateFromExistingItemIndex(int32 ItemIndex)`
- L60 _public function_ `static FGeometryCollectionItemIndex CreateInvalidItemIndex()`
- L66 _public function_ `FGeometryCollectionItemIndex(const FGeometryCollectionItemIndex& Other) : ItemIndex(Other.ItemIndex)`
- L70 _public function_ `bool IsInternalCluster() const`
- L75 _public function_ `int32 GetInternalClusterIndex() const`
- L81 _public function_ `int32 GetTransformIndex() const`
- L87 _public function_ `bool IsValid() const`
- L92 _public function_ `int32 GetItemIndex() const`
- L97 _public function_ `bool operator==(const FGeometryCollectionItemIndex& Other) const`
- L103 _private member_ `static const int32 InternalClusterBaseIndex = TNumericLimits<int32>::Lowest();`
- L105 _private function_ `FGeometryCollectionItemIndex(int32 Index, bool bInternalCluster) : ItemIndex(INDEX_NONE)`
- L114 _private member_ `int32 ItemIndex;`

#### class `FStubGeometryCollectionData`  
`class FStubGeometryCollectionData : public Chaos::FParticleData`  
_L117-136_
- inherits: `Chaos::FParticleData`
- L120 _public typedef_ `typedef Chaos::FParticleData Base;`
- L122 _public function_ `FStubGeometryCollectionData(const FGeometryCollectionResults* DataIn=nullptr) : Base(Chaos::EParticleType::GeometryCollection) , Data(DataIn)`
- L127 _public function_ `void Reset()`
- L132 _public function_ `const FGeometryCollectionResults* GetStateData() const`
- L135 _private member_ `const FGeometryCollectionResults* Data;`

#### class `FGeometryCollectionPhysicsProxy`  
`class FGeometryCollectionPhysicsProxy : public TPhysicsProxy<FGeometryCollectionPhysicsProxy, FStubGeometryCollectionData, FGeometryCollectionProxyTimestamp>`  
_L142-863_
- inherits: `TPhysicsProxy<FGeometryCollectionPhysicsProxy,FStubGeometryCollectionData,FGeometryCollectionProxyTimestamp>`
- desc: Class to manage sharing data between the game thread and the simulation thread (which may not be different than the game thread) for a \c FGeometryDynamicCollection.
- L145 _public typedef_ `typedef TPhysicsProxy<FGeometryCollectionPhysicsProxy, FStubGeometryCollectionData, FGeometryCollectionProxyTimestamp> Base;`
- L146 _public typedef_ `typedef FCollisionStructureManager::FSimplicial FSimplicial;`
- L147 _public typedef_ `typedef Chaos::TPBDRigidParticle<Chaos::FReal, 3> FParticle;`
- L148 _public typedef_ `typedef Chaos::TPBDRigidParticleHandle<Chaos::FReal, 3> FParticleHandle;`
- L149 _public typedef_ `typedef Chaos::TPBDRigidClusteredParticleHandle<Chaos::FReal, 3> FClusterHandle;`
- L154 _public prototype_ `FGeometryCollectionPhysicsProxy() = delete;`
- L163 _public prototype_ `FGeometryCollectionPhysicsProxy( UObject* InOwner, FGeometryDynamicCollection& GameThreadCollection, const FSimulationParameters& SimulationParameters, FCollisionFilterData InSimFilter, FCollisionFilterData InQueryFilter, FGuid InCollectorGuid = FGuid::NewGuid(), const Chaos::EMultiBufferMode BufferMode=Chaos::EMultiBufferMode::TripleGuarded);` — `UE_DEPRECATED(5.6, "Use the constructor that use a shared ref for the game thread collection")` — \p InOwner \p InDynamicCollection game thread owned geometry collection. \p InInitFunc callback invoked from \c Initialize(). \p InCacheSyncFunc callback invoked from \c PullFromPhysicsState(). \p InFinalSyncFunc callback invoked from \c SyncBeforeDestory().
- L173 _public prototype_ `FGeometryCollectionPhysicsProxy( UObject* InOwner, TSharedRef<FGeometryDynamicCollection> GameThreadCollection, const FSimulationParameters& SimulationParameters, FCollisionFilterData InSimFilter, FCollisionFilterData InQueryFilter, FGuid InCollectorGuid = FGuid::NewGuid(), const Chaos::EMultiBufferMode BufferMode = Chaos::EMultiBufferMode::TripleGuarded);` — `UE_DEPRECATED(5.8, "Use the constructor that takes FShapeFilterData and FInstanceData instead")`
- L182 _public prototype_ `FGeometryCollectionPhysicsProxy( UObject* InOwner, TSharedRef<FGeometryDynamicCollection> GameThreadCollection, const FSimulationParameters& SimulationParameters, const Chaos::Filter::FShapeFilterData& InShapeFilterData, const Chaos::Filter::FInstanceData& InShapeInstanceData, FGuid InCollectorGuid = FGuid::NewGuid(), const Chaos::EMultiBufferMode BufferMode = Chaos::EMultiBufferMode::TripleGuarded);`
- L191 _public prototype_ `virtual ~FGeometryCollectionPhysicsProxy();`
- L197 _public prototype_ `void Initialize(Chaos::FPBDRigidsEvolutionBase* Evolution);` — Construct \c PTDynamicCollection, copying attributes from the game thread, and prepare for simulation.
- L198 _public function_ `void Reset()`
- L200 _public function_ `bool IsInitializedOnPhysicsThread() const`
- L207 _public prototype_ `void InitializeBodiesPT( Chaos::FPBDRigidsSolver* RigidsSolver, typename Chaos::FPBDRigidsSolver::FParticlesType& Particles);` — Finish initialization on the physics thread. Called by solver command registered by \c FPBDRigidsSolver::RegisterObject().
- L212 _public prototype_ `static void InitializeDynamicCollection(FGeometryDynamicCollection& DynamicCollection, const FGeometryCollection& RestCollection, const FSimulationParameters& Params);`
- L215 _public function_ `bool IsSimulating() const`
- L223 _public function_ `Chaos::FParticleData* NewData()` — Pushes current game thread particle state into the \c GameToPhysInterchange. Redirects to \c BufferGameState(), and returns nullptr as this class manages data transport to the physics thread itself, without allocating memory.
- L224 _public prototype_ `void BufferGameState();`
- L227 _public function_ `void ClearAccumulatedData()` — Called at the end of \c FPBDRigidsSolver::PushPhysicsStateExec().
- L230 _public prototype_ `void BufferPhysicsResults_Internal(Chaos::FPBDRigidsSolver* CurrentSolver, Chaos::FDirtyGeometryCollectionData& BufferData);` — Push PT state into the \c PhysToGameInterchange.
- L233 _public prototype_ `void BufferPhysicsResults_External(Chaos::FDirtyGeometryCollectionData& BufferData);` — Push GT state into the \c PhysToGameInterchange for async physics
- L236 _public prototype_ `void PushStateOnGameThread(Chaos::FPBDRigidsSolver* InSolver);` — Push data from the game thread to the physics thread
- L239 _public prototype_ `void PushToPhysicsState();` — apply the state changes on the physics thread
- L242 _public prototype_ `void FlipBuffer();` — Does nothing as \c BufferPhysicsResults() already did this.
- L248 _public prototype_ `bool PullFromPhysicsState(const Chaos::FDirtyGeometryCollectionData& BufferData, const int32 SolverSyncTimestamp, const Chaos::FDirtyGeometryCollectionData* NextPullData = nullptr, const Chaos::FRealSingle* Alpha = nullptr, const Chaos::FDirtyRigidParticleReplicationErrorData* Error = nullptr, const Chaos::FReal AsyncFixedTimeStep = 0);` — Pulls data out of the PhysToGameInterchange and updates \c GTDynamicCollection. Called from FPhysScene_ChaosInterface::SyncBodies(), NOT the solver.
- L250 _public function_ `bool IsDirty()`
- L252 _public function_ `static constexpr EPhysicsProxyType ConcreteType()`
- L254 _public prototype_ `void SyncBeforeDestroy();`
- L255 _public prototype_ `void OnRemoveFromSolver(Chaos::FPBDRigidsSolver *RBDSolver);`
- L256 _public prototype_ `void OnRemoveFromScene();`
- L257 _public prototype_ `void OnUnregisteredFromSolver();`
- L259 _public function_ `void SetCollisionParticlesPerObjectFraction(float CollisionParticlesPerObjectFractionIn)`
- L263 _public function_ `TArray<FClusterHandle*>& GetSolverClusterHandles()` — `UE_DEPRECATED(5.4, "Use GetSolverClusterHandle_Internal instead")`
- L266 _public function_ `TArray<FClusterHandle*>& GetSolverParticleHandles()` — `UE_DEPRECATED(5.4, "Use GetParticle_Internal instead")`
- L268 _public function_ `FClusterHandle* GetSolverClusterHandle_Internal(int32 Index) const`
- L278 _public function_ `const FGeometryCollectionResults* GetConsumerResultsGT() const`
- L282 _public prototype_ `void BufferFieldCommand_External(FFieldSystemCommand&& Command);` — Enqueue a field \p Command to be processed by \c ProcessCommands() or \c FieldForcesUpdateCallback(). Game thread only
- L285 _public prototype_ `void BufferCommand(Chaos::FPBDRigidsSolver* RigidsSolver, const FFieldSystemCommand& Command);` — `UE_DEPRECATED(5.5, "Use BufferFieldCommand_Internal instead when calling on the physics thread or the _external version when calling on the gamethread")`
- L288 _public prototype_ `void BufferFieldCommand_Internal(Chaos::FPBDRigidsSolver* RigidsSolver, const FFieldSystemCommand& Command);` — Enqueue a field \p Command to be processed by \c ProcessCommands() or \c FieldForcesUpdateCallback(). Physics thread only
- L290 _public prototype_ `void FieldForcesUpdateCallback(Chaos::FPBDRigidsSolver* RigidSolver);`
- L292 _public prototype_ `void FieldParameterUpdateCallback(Chaos::FPBDRigidsSolver* RigidSolver, const bool bUpdateViews = true);`
- L294 _public prototype_ `static bool NeedToInitializeSharedCollisionStructures(const FGeometryCollection& RestCollection);`
- L295 _public prototype_ `static void InitializeSharedCollisionStructures(Chaos::FErrorReporter& ErrorReporter, FGeometryCollection& RestCollection, const FSharedSimulationParameters& SharedParams);`
- L297 _public function_ `void UpdateKinematicBodiesCallback(const FParticlesType& InParticles, const float InDt, const float InTime, FKinematicProxy& InKinematicProxy)`
- L298 _public function_ `void StartFrameCallback(const float InDt, const float InTime)`
- L299 _public function_ `void EndFrameCallback(const float InDt)`
- L300 _public function_ `void BindParticleCallbackMapping(Chaos::TArrayCollectionArray<PhysicsProxyWrapper>& PhysicsProxyReverseMap, Chaos::TArrayCollectionArray<int32>& ParticleIDReverseMap)`
- L301 _public function_ `void CreateRigidBodyCallback(FParticlesType& InOutParticles)`
- L302 _public function_ `void DisableCollisionsCallback(TSet<TTuple<int32, int32>>& InPairs)`
- L303 _public function_ `void AddForceCallback(FParticlesType& InParticles, const float InDt, const int32 InIndex)`
- L305 _public function_ `bool IsGTCollectionDirty() const`
- L308 _public prototype_ `void SetWorldTransform_External(const FTransform& WorldTransform);` — set the world transform ( this needs to be called on the game thread )
- L313 _public prototype_ `void UpdateWorldTransformCaches_External(const FTransform& WorldTransform);` — Update cached world transforms (GT side, and mirror Parameters.WorldTransform on PT) without dispatching kinematic targets or cluster-union updates. Use when the component moves on the game thread but the simulation must not be perturbed.
- L315 _public function_ `const FTransform& GetPreviousWorldTransform_External() const`
- L316 _public function_ `const FTransform& GetWorldTransform_External()`
- L320 _public prototype_ `void SetUseStaticMeshCollisionForTraces_External(bool bInUseStaticMeshCollisionForTraces);` — todo(chaos): Remove this and move to a cook time approach of the SM data based on the GC property Set whether the GC should be using collision from the Static Mesh or the GC itself for game thread traces ( this needs to be called on the game thread )
- L323 _public function_ `const TArray<FClusterHandle*> GetParticles() const` — `UE_DEPRECATED(5.4, "Use GetParticle_Internal instead")`
- L328 _public function_ `const TArray<FClusterHandle*>GetUnorderedParticles_Internal() const`
- L333 _public function_ `FClusterHandle* GetParticle_Internal(int32 Index) const`
- L346 _public function_ `const FSimulationParameters& GetSimParameters() const`
- L351 _public function_ `FSimulationParameters& GetSimParameters()`
- L356 _public function_ `FGeometryDynamicCollection& GetPhysicsCollection()`
- L361 _public function_ `FGeometryDynamicCollection& GetExternalCollection()`
- L367 _public function_ `TArray<TUniquePtr<FParticle>>& GetExternalParticles()` — `UE_DEPRECATED(5.4, "Use GetUnorderedParticles_External instead")`
- L372 _public function_ `TArray<TUniquePtr<FParticle>>& GetUnorderedParticles_External()`
- L377 _public prototype_ `FParticle* GetParticleByIndex_External(int32 Index);`
- L378 _public prototype_ `const FParticle* GetParticleByIndex_External(int32 Index) const;`
- L380 _public prototype_ `FParticleHandle* GetParticleByIndex_Internal(int32 Index);`
- L381 _public prototype_ `const FParticleHandle* GetParticleByIndex_Internal(int32 Index) const;`
- L383 _public function_ `FParticle* GetInitialRootParticle_External()`
- L384 _public function_ `const FParticle* GetInitialRootParticle_External() const`
- L386 _public function_ `FParticleHandle* GetInitialRootParticle_Internal()`
- L387 _public function_ `const FParticleHandle* GetInitialRootParticle_Internal() const`
- L392 _public prototype_ `void GetRelevantParticleHandles( TArray<Chaos::TGeometryParticleHandle<Chaos::FReal, 3>*>& Handles, const Chaos::FPBDRigidsSolver* RigidSolver, EFieldResolutionType ResolutionType);` — * Get all the geometry collection particle handles based on the processing resolution
- L400 _public prototype_ `void GetFilteredParticleHandles( TArray<Chaos::TGeometryParticleHandle<Chaos::FReal, 3>*>& Handles, const Chaos::FPBDRigidsSolver* RigidSolver, const EFieldFilterType FilterType, const EFieldObjectType ObjectType);` — Get all the geometry collection particle handles filtered by object state
- L407 _public function_ `virtual void* GetHandleUnsafe() const override` — Implemented so we can construct TAccelerationStructureHandle.
- L409 _public function_ `int32 GetTransformGroupIndexFromHandle(const FParticleHandle* Handle) const`
- L418 _public function_ `void GetTransformGroupIndicesFromHandles(const TArray<FParticleHandle*> Handles, TArray<int32>& IndicesOut) const`
- L431 _public function_ `FGeometryCollectionItemIndex GetInternalClusterParentItemIndex_External(int32 ChildTransformIndex) const`
- L453 _public function_ `const TArray<int32>* FindInternalClusterChildrenTransformIndices_External(FGeometryCollectionItemIndex ItemIndex) const`
- L462 _public function_ `FGeometryCollectionItemIndex GetItemIndexFromGTParticle_External(const FParticle* GTPParticle) const`
- L480 _public function_ `FGeometryCollectionItemIndex GetItemIndexFromGTParticleNoInternalCluster_External(const FParticle* GTPParticle) const`
- L492 _public prototype_ `FName GetTransformName_External(FGeometryCollectionItemIndex ItemIndex) const;`
- L494 _public function_ `bool GetIsObjectDynamic() const`
- L496 _public prototype_ `void DisableParticles_External(TArray<int32>&& TransformGroupIndices);`
- L498 _public prototype_ `void ApplyForceAt_External(FVector Force, FVector WorldLocation);`
- L499 _public prototype_ `void ApplyImpulseAt_External(FVector Force, FVector WorldLocation);`
- L500 _public prototype_ `void BreakClusters_External(TArray<FGeometryCollectionItemIndex>&& ItemIndices);`
- L501 _public prototype_ `void BreakActiveClusters_External();`
- L502 _public prototype_ `void SetAnchoredByIndex_External(int32 Index, bool bAnchored);`
- L503 _public prototype_ `void SetAnchoredByTransformedBox_External(const FBox& Box, const FTransform& Transform, bool bAnchored, int32 MaxLevel = INDEX_NONE);`
- L504 _public prototype_ `void RemoveAllAnchors_External();`
- L505 _public prototype_ `void ApplyExternalStrain_External(FGeometryCollectionItemIndex ItemIndex, const FVector& WorldLocation, float Radius, int32 PropagationDepth, float PropagationFactor, float StrainValue);`
- L506 _public prototype_ `void ApplyInternalStrain_External(FGeometryCollectionItemIndex ItemIndex, const FVector& WorldLocation, float Radius, int32 PropagationDepth, float PropagationFactor, float StrainValue);`
- L507 _public prototype_ `void ApplyBreakingLinearVelocity_External(FGeometryCollectionItemIndex ItemIndex, const FVector& LinearVelocity);`
- L508 _public prototype_ `void ApplyBreakingAngularVelocity_External(FGeometryCollectionItemIndex ItemIndex, const FVector& AngularVelocity);`
- L509 _public prototype_ `void ApplyLinearVelocity_External(FGeometryCollectionItemIndex ItemIndex, const FVector& LinearVelocity);`
- L510 _public prototype_ `void ApplyAngularVelocity_External(FGeometryCollectionItemIndex ItemIndex, const FVector& AngularVelocity);`
- L511 _public prototype_ `void SetLinearDamping_External(float InDamping);`
- L512 _public prototype_ `void SetLinearDampingPerTransform_External(const TArray<int32>& TransformIndices, float InDamping);`
- L513 _public prototype_ `void SetAngularDamping_External(float InDamping);`
- L514 _public prototype_ `void SetAngularDampingPerTransform_External(const TArray<int32>& TransformIndices, float InDamping);`
- L516 _public prototype_ `void SetProxyDirty_External();`
- L518 _public prototype_ `void SetEnableDamageFromCollision_External(bool bEnable);`
- L519 _public prototype_ `void SetNotifyBreakings_External(bool bNotify);`
- L520 _public prototype_ `void SetNotifyRemovals_External(bool bNotify);`
- L521 _public prototype_ `void SetNotifyCrumblings_External(bool bNotify, bool bIncludeChildren);`
- L522 _public prototype_ `void SetNotifyTrailings_External(bool bNotify);`
- L524 _public prototype_ `void SetNotifyGlobalBreakings_External(bool bNotify);`
- L525 _public prototype_ `void SetNotifyGlobalRemovals_External(bool bNotify);`
- L526 _public prototype_ `void SetNotifyGlobalCrumblings_External(bool bNotify, bool bIncludeChildren);`
- L527 _public prototype_ `void SetNotifyGlobalTrailings_External(bool bNotify);`
- L529 _public prototype_ `float ComputeMaterialBasedDamageThreshold_Internal(Chaos::FPBDRigidClusteredParticleHandle& ClusteredParticle) const;`
- L531 _public prototype_ `UE_INTERNAL void FlushDirtyParticles(Chaos::FPBDRigidsSolver& Solver);`
- L533 _public function_ `FProxyInterpolationBase* GetInterpolationData()`
- L534 _public function_ `const FProxyInterpolationBase* GetInterpolationData() const`
- L536 _public function_ `void ResetInterpolationData()`
- L548 _public function_ `void SetReplicationMode(EReplicationMode Mode)`
- L549 _public function_ `EReplicationMode GetReplicationMode() const`
- L551 _public prototype_ `UE_DEPRECATED(5.7, "Use the overload that takes a FCombinedShapeFilterData instead") void UpdateFilterData_External(const FCollisionFilterDa`
- L552 _public prototype_ `void UpdateFilterData_External(const Chaos::Filter::FCombinedShapeFilterData& NewShapeFilter);` — `UE_DEPRECATED(5.7, "Use the overload that takes a FCombinedShapeFilterData instead")`
- L578 _public prototype_ `void UpdatePerParticleFilterData_External(const TArray<FParticleCollisionFilterData>& Data);`
- L580 _public prototype_ `void SetDamageThresholds_External(const TArray<float>& DamageThresholds);`
- L581 _public prototype_ `void SetDamagePropagationData_External(bool bEnabled, float BreakDamagePropagationFactor, float ShockDamagePropagationFactor);`
- L582 _public prototype_ `void SetDamageModel_External(EDamageModelTypeEnum DamageModel);`
- L583 _public prototype_ `void SetUseMaterialDamageModifiers_External(bool bUseMaterialDamageModifiers);`
- L584 _public prototype_ `void SetMaterialOverrideMassScaleMultiplier_External(float InMultiplier);`
- L585 _public prototype_ `void SetEnableGravity_External(bool EnableGravity_External);`
- L586 _public prototype_ `void SetGravityGroupIndex_External(int32 GravityGroupIndex);`
- L587 _public prototype_ `void SetOneWayInteractionLevel_External(int32 OneWayInteractionLevel);`
- L588 _public prototype_ `void SetPhysicsMaterial_External(const Chaos::FMaterialHandle& MaterialHandle);`
- L595 _public prototype_ `static int32 CalculateAndSetLevel(int32 TransformGroupIdx, const TManagedArray<int32>& Parent, TManagedArray<int32>& Levels);` — Traverses the parents of TransformGroupIdx counting number of levels, and sets levels array value for TransformGroupIdx and its parents if not yet initialized. If level is already set, retrieve stored level. Uninitialized level array should be correct size and defaulted to zeros.
- L597 _public function_ `void SetPostPhysicsSyncCallback(TFunction<void()> Callback)`
- L602 _public function_ `void SetPostParticlesCreatedCallback(TFunction<void()> Callback)`
- L607 _public prototype_ `FClusterHandle* GetInitialRootHandle_Internal() const;`
- L609 _public prototype_ `TArray<Chaos::FPhysicsObjectHandle> GetAllPhysicsObjects() const ;`
- L610 _public prototype_ `TArray<Chaos::FPhysicsObjectHandle> GetAllPhysicsObjectIncludingNulls() const;`
- L611 _public prototype_ `Chaos::FPhysicsObjectHandle GetPhysicsObjectByIndex(int32 Index) const;`
- L612 _public prototype_ `void RebaseAllGameThreadCollectionTransformsOnNewWorldTransform_External();`
- L615 _public function_ `int32 GetNumParticles() const` — `UE_DEPRECATED(5.4, "Use GetNumTransforms instead")`
- L616 _public function_ `int32 GetNumTransforms() const`
- L619 _public typedef_ `using FCreateTraceCollisionGeometryCallback = TFunction<void(const FTransform& InToLocal, TArray<Chaos::FImplicitObjectPtr>& OutGeoms, Chaos::FShapesArray& OutShapes)>;` — todo(chaos): Remove this and move to a cook time approach of the SM data based on the GC property
- L620 _public function_ `void SetCreateTraceCollisionGeometryCallback(FCreateTraceCollisionGeometryCallback InCreateGeometryCallback)`
- L622 _public prototype_ `void CreateChildrenGeometry_Internal();`
- L624 _public function_ `int32 GetFromParticleToTransformIndex(int32 Index) const`
- L626 _public function_ `bool GetSkipChildToParentUpdateWhenInClusterUnion() const`
- L627 _public function_ `void SetSkipChildToParentUpdateWhenInClusterUnion(bool bValue)`
- L631 _protected prototype_ `bool RebaseParticleGameThreadCollectionTransformOnNewWorldTransform_External(int32 ParticleIndex, const TManagedArray<FTransform>& MassToLocal, bool bIsComponentTransformScaled, const FTransform& ComponentScaleTransform);`
- L633 _protected prototype_ `float ComputeMaterialBasedDamageThreshold_Internal(int32 TransformIndex) const;`
- L642 _protected prototype_ `float ComputeUserDefinedDamageThreshold_Internal(int32 TransformIndex) const;` — Compute user defined damage threshold for a specific transform this account for component level damage threshold as well as size specific ones @param DynamicCollection dynamic collection to use @param TransformIndex index of the transform to compute the threshold for #return damage threshold value
- L645 _protected prototype_ `float AdjustMassForScale(float Mass) const;` — adjust scalar mass to account for per component scale properties ( from material override and world transform scale )
- L648 _protected prototype_ `Chaos::FVec3f AdjustInertiaForScale(const Chaos::FVec3f& Inertia) const;` — adjust inertia to account for per component scale properties ( from material override and world transform scale )
- L650 _protected prototype_ `Chaos::TPBDGeometryCollectionParticleHandle<Chaos::FReal, 3>* BuildNonClusters_Internal(const uint32 CollectionClusterIndex, Chaos::FPBDRigidsSolver* RigidsSolver, float Mass, Chaos::FVec3f Inertia, const Chaos::FUniqueIdx* ExistingIndex);`
- L660 _protected prototype_ `Chaos::FPBDRigidClusteredParticleHandle* BuildClusters_Internal( const uint32 CollectionClusterIndex, TArray<Chaos::FPBDRigidParticleHandle*>& ChildHandles, const TArray<int32>& ChildTransformGroupIndices, const Chaos::FClusterCreationParameters & Parameters, const Chaos::FUniqueIdx* ExistingIndex);`
- L667 _protected prototype_ `void SetSleepingState(const Chaos::FPBDRigidsSolver& RigidsSolver);`
- L668 _protected prototype_ `void DirtyAllParticles(const Chaos::FPBDRigidsSolver& RigidsSolver);`
- L674 _protected prototype_ `static int32 CalculateHierarchyLevel(const FGeometryDynamicCollection& DynamicCollection, int32 TransformIndex);` — Traverses the parents of \p TransformIndex in \p GeometryCollection, counting the number of levels until the next parent is \c INDEX_NONE.
- L676 _protected prototype_ `void SetClusteredParticleKinematicTarget_Internal(Chaos::FPBDRigidClusteredParticleHandle* Handle, const FTransform& WorldTransform);`
- L678 _protected prototype_ `void PrepareBufferData(Chaos::FDirtyGeometryCollectionData& BufferData, const FGeometryDynamicCollection& ThreadCollection, Chaos::FReal SolverLastDt = 0.0);`
- L680 _protected prototype_ `void CreateNonClusteredParticles(Chaos::FPBDRigidsSolver* RigidsSolver, const FGeometryCollection& RestCollection, const FGeometryDynamicCollection& DynamicCollection);`
- L682 _protected prototype_ `Chaos::FPBDRigidClusteredParticleHandle* FindClusteredParticleHandleByItemIndex_Internal(FGeometryCollectionItemIndex ItemIndex) const;`
- L684 _protected prototype_ `void UpdateDamageThreshold_Internal();`
- L687 _protected prototype_ `void ScaleClusterGeometry_Internal(const FVector& WorldScale);` — Scale the cluster particles geometry (creates if necessary an additional TImplicitObjectScaled object into the implicits hierarchy)
- L689 _protected prototype_ `void SetWorldTransform_Internal(const FTransform& WorldTransform, bool bInSkipChildToParentUpdateWhenInClusterUnion = false);`
- L690 _protected prototype_ `UE_DEPRECATED(5.7, "Use the overload that takes a FCombinedShapeFilterData instead") void SetFilterData_Internal(const FCollisionFilterDa`
- L691 _protected prototype_ `void SetFilterData_Internal(const Chaos::Filter::FCombinedShapeFilterData& NewShapeFilter);` — `UE_DEPRECATED(5.7, "Use the overload that takes a FCombinedShapeFilterData instead")`
- L692 _protected prototype_ `void SetPerParticleFilterData_Internal(const TArray<FParticleCollisionFilterData>& PerParticleData);`
- L693 _protected prototype_ `void SetDamagePropagationData_Internal(bool bEnabled, float BreakDamagePropagationFactor, float ShockDamagePropagationFactor);`
- L694 _protected prototype_ `void SetEnableGravity_Internal(bool bEnabled);`
- L695 _protected prototype_ `void SetDamageThresholds_Internal(const TArray<float>& DamageThresholds);`
- L696 _protected prototype_ `void SetDamageModel_Internal(EDamageModelTypeEnum DamageModel);`
- L697 _protected prototype_ `void SetUseMaterialDamageModifiers_Internal(bool bUseMaterialDamageModifiers);`
- L698 _protected prototype_ `void SetMaterialOverrideMassScaleMultiplier_Internal(float InMultiplier);`
- L699 _protected prototype_ `void SetGravityGroupIndex_Internal(int32 GravityGroupIndex);`
- L700 _protected prototype_ `void SetOneWayInteractionLevel_Internal(int32 InOneWayInteractionLevel);`
- L701 _protected prototype_ `void SetPhysicsMaterial_Internal(const Chaos::FMaterialHandle& MaterialHandle);`
- L702 _protected prototype_ `void SetLinearDamping_Internal(float InDamping);`
- L703 _protected prototype_ `void SetLinearDampingPerTransform_Internal(const TArray<int32>& TransformIndices, float InDamping);`
- L704 _protected prototype_ `void SetAngularDamping_Internal(float InDamping);`
- L705 _protected prototype_ `void SetAngularDampingPerTransform_Internal(const TArray<int32>& TransformIndices ,float InDamping);`
- L709 _private prototype_ `static TBitArray<> CalculateClustersToCreateFromChildren(const FGeometryDynamicCollection& DynamicCollection, int32 NumTransforms);`
- L710 _private prototype_ `static int32 CalculateEffectiveParticles(const FGeometryDynamicCollection& DynamicCollection, int32 NumTransform, int32 MaxSimulatedLevel, bool bEnableClustering, const UObject* Owner, TBitArray<>& EffectiveParticles);`
- L712 _private prototype_ `void CreateGTParticles(TManagedArray<Chaos::FImplicitObjectPtr>& Implicits, Chaos::FPBDRigidsEvolutionBase* Evolution, bool bInitializeRootOnly);`
- L713 _private prototype_ `void CreateChildrenGeometry_External();`
- L714 _private prototype_ `void SyncParticles_External();`
- L727 _private prototype_ `bool PullNonInterpolatableDataFromSinglePhysicsState(const Chaos::FDirtyGeometryCollectionData& BufferData, bool bForcePullXRVW, const TBitArray<>* Seen);` — Since geometry collections only buffer data that has changed, when PullFromPhysicsState is given both PrevData and NextData it must examine *both* PrevData and NextData for data about a particle (since that particle's data coudl be in PrevData and not NextData). PullNonInterpolatableDataFromSinglePhysicsState will do the work to pull the non-interpolatable data (which could include X/R/V/W in certain scenarios) to the game thread. @param BufferData The buffered physics data to pull data from (could be PrevData or NextData). @param bForcePullXRVW Whether or not to pull interpolatable data as non-interpolatable data (i.e. X/R/V/W). This happens only when NextData doesn't exist. @param Seen The bit array of the previously handled FDirtyGeometryCollectionData (should be null in the case of handling NextData, and should be the TBitArray on NextData when handling PrevData). @return A boolean indicating whether or not a change to the GT state was detected.
- L729 _private member_ `FSimulationParameters Parameters;`
- L731 _private member_ `TArray<Chaos::FPhysicsObjectUniquePtr> PhysicsObjects;`
- L734 _private member_ `FTransform WorldTransform_External;` — todo : we should probably keep a simulation parameter copy on the game thread instead
- L735 _private member_ `FTransform PreviousWorldTransform_External;`
- L740 _private member_ `int32 NumTransforms;` — Proxy State Information
- L741 _private member_ `int32 NumEffectiveParticles;`
- L742 _private member_ `int32 BaseParticleIndex;`
- L744 _private member_ `float CollisionParticlesPerObjectFraction;` — Per object collision fraction.
- L756 _private member_ `TUniquePtr<FFieldData> FieldData_Internal;` — data is allocated on demand on the physics thread only ( see GetOrCreateFieldData_Internal )
- L758 _private prototype_ `FFieldData& GetOrCreateFieldData_Internal();`
- L760 _private member_ `EReplicationMode ReplicationMode = EReplicationMode::Unknown;`
- L762 _private member_ `uint8 bIsGameThreadWorldTransformDirty : 1;`
- L763 _private member_ `uint8 bHasBuiltGeometryOnPT : 1;`
- L764 _private member_ `uint8 bHasBuiltGeometryOnGT : 1;`
- L766 _private member_ `bool bIsInitializedOnPhysicsThread : 1 = false;` — set to true once InitializeBodiesPT has been called
- L770 _private member_ `bool IsObjectDynamic : 1;` — Buffer Results State Information
- L771 _private member_ `bool IsObjectLoading : 1;` — Indicate when loaded
- L772 _private member_ `bool IsObjectDeleting : 1;` — Indicate when pending deletion
- L775 _private member_ `bool bSkipChildToParentUpdateWhenInClusterUnion : 1;` — when true and part of a cluster union this will skip the Child to parent update part
- L777 _private member_ `TArray<FParticleHandle*> SolverClusterID;`
- L778 _private member_ `TArray<FClusterHandle*> SolverClusterHandles;` — make a TArray of the base clase with type
- L779 _private member_ `TArray<FClusterHandle*> SolverParticleHandles;` — make a TArray of base class and join with above
- L780 _private member_ `TMap<FParticleHandle*, int32> HandleToTransformGroupIndex;`
- L781 _private member_ `TMap<int32, FClusterHandle*> UniqueIdxToInternalClusterHandle;`
- L782 _private member_ `TArray<Chaos::FUniqueIdx> UniqueIdxs;`
- L783 _private member_ `TArray<int32> FromParticleToTransformIndex;`
- L784 _private member_ `TArray<int32> FromTransformToParticleIndex;`
- L785 _private member_ `TBitArray<> EffectiveParticles;`
- L786 _private member_ `TBitArray<> ParticlesToDirty;`
- L789 _private member_ `TArray<TUniquePtr<FParticle>> GTParticles;` — Game thread particles
- L800 _private member_ `TMap<FParticle*, FGTParticleIndices> GTParticleToIndices;`
- L801 _private member_ `TMap<int32, TArray<int32>> InternalClusterUniqueIdxToChildrenTransformIndices;`
- L804 _private member_ `Chaos::Filter::FShapeFilterData ShapeFilterData;` — These are read on both threads and should not be changed
- L805 _private member_ `Chaos::Filter::FInstanceData ShapeInstanceData;`
- L808 _private member_ `FCreateTraceCollisionGeometryCallback CreateTraceCollisionGeometryCallback;` — todo(chaos): Remove this and move to a cook time approach of the SM data based on the GC property
- L811 _private member_ `TFunction<void()> PostPhysicsSyncCallback;` — called after we sync the physics thread data ( called on the game thread )
- L812 _private member_ `TFunction<void()> PostParticlesCreatedCallback;`
- L818 _private member_ `FGeometryDynamicCollection PhysicsThreadCollection;` — The Simulation data is copied between the game and physics thread. It is expected that the two data sets will diverge, based on how the simulation uses the data, but at the start of the simulation the PhysicsThreadCollection is a deep copy from the GameThreadCollection.
- L819 _private member_ `FGeometryDynamicCollection& GameThreadCollection;` — now initialize from the SharedRef passed in the constructor
- L820 _private member_ `const TSharedPtr<FGeometryDynamicCollection> GameThreadCollectionSharedPtr;` — shoul dnever be null
- L831 _private member_ `Chaos::FGuardedTripleBuffer<FGeometryCollectionResults> PhysToGameInterchange;` — Currently this is using triple buffers for game-physics and physics-game thread communication, but not for any reason other than this is the only implementation we currently have of a guarded buffer - a buffer that tracks it's own state, rather than having other mechanisms determine whether or not the contents of the buffer have been updated.  A double buffer would probably be fine, as that seems to be the assumption the logic currently managing the exchange is built upon.  However, I believe that logic locks, and the triple buffer would enable a decoupled lock-free paradigm, at least for this component of the handshake.
- L833 _private member_ `TUniquePtr<FProxyInterpolationBase> InterpolationData;`
- L838 _public function_ `template<typename ErrorDataType> ErrorDataType* GetOrCreateErrorInterpolationData()` — Get or create a derived FProxyInterpolationBase that handles render interpolation error corrections
- L853 _public function_ `template<typename ErrorDataType> const ErrorDataType* GetErrorInterpolationData() const`
- L861 _private member_ `FGuid CollectorGuid;` — this is used as a unique ID when collecting data from runtime

#### enum `FGeometryCollectionPhysicsProxy::EReplicationMode`  
`enum class EReplicationMode: uint8`  
_L541-546_
- L543 _public enumerator_ `Unknown`
- L544 _public enumerator_ `Server`
- L545 _public enumerator_ `Client`

#### struct `FGeometryCollectionPhysicsProxy::FParticleCollisionFilterData`  
`struct FParticleCollisionFilterData`  
_L554-576_
- L558 _public prototype_ `FParticleCollisionFilterData() = default;` — These must be explicitly declared to get rid of deprecation warnings.
- L559 _public prototype_ `FParticleCollisionFilterData(const FParticleCollisionFilterData&) = default;`
- L560 _public prototype_ `FParticleCollisionFilterData(FParticleCollisionFilterData&&) = default;`
- L562 _public prototype_ `FParticleCollisionFilterData& operator=(const FParticleCollisionFilterData&) = default;`
- L563 _public prototype_ `FParticleCollisionFilterData& operator=(FParticleCollisionFilterData&&) = default;`
- L566 _public member_ `int32 ParticleIndex = INDEX_NONE;`
- L567 _public member_ `bool bIsValid = false;`
- L568 _public member_ `bool bQueryEnabled = false;`
- L569 _public member_ `bool bSimEnabled = false;`
- L571 _public member_ `FCollisionFilterData QueryFilter;` — `UE_DEPRECATED(5.8, "Use ShapeFilterData and FilterInstanceData")`
- L573 _public member_ `FCollisionFilterData SimFilter;` — `UE_DEPRECATED(5.8, "Use ShapeFilterData and FilterInstanceData")`
- L574 _public member_ `Chaos::Filter::FShapeFilterData ShapeFilterData;`
- L575 _public member_ `Chaos::Filter::FInstanceData FilterInstanceData;`

#### struct `FGeometryCollectionPhysicsProxy::FFieldData`  
`struct FFieldData`  
_L747-754_
- desc: structure that contains the necessary information for processing fields
- L750 _public member_ `TArray<FFieldSystemCommand> Commands;` — field command to execute
- L753 _public member_ `FFieldExecutionDatas ExecutionDatas;` — Field Datas stored during evaluation

#### struct `FGeometryCollectionPhysicsProxy::FGTParticleIndices`  
`struct FGTParticleIndices`  
_L791-798_
- L794 _public member_ `int32 TransformGroupIndex = INDEX_NONE;` — Correponding transform index of the GTparticle
- L797 _public member_ `int32 InternalClusterUniqueId = INDEX_NONE;` — unique index of the parent the GT particle is a child of internal cluster

#### struct `FDamageCollector`  
`struct FDamageCollector`  
_L869-892_
- desc: the watcher collects runtime data about damage on each piece of the geometry collection
- L879 _public prototype_ `void Reset(int32 NumTransforms);`
- L880 _public function_ `int32 Num() const`
- L881 _public function_ `const FDamageData& operator[](int32 TransformIndex) const`
- L888 _public prototype_ `void SampleDamage(int32 TransformIndex, float Damage, float DamageThreshold);`
- L891 _private member_ `TArray<FDamageData> DamageData;`

#### struct `FDamageCollector::FDamageData`  
`struct FDamageData`  
_L872-877_
- L874 _public member_ `float DamageThreshold= 0;`
- L875 _public member_ `float MaxDamages = 0;`
- L876 _public member_ `bool bIsBroken = false;`

#### struct `FRuntimeDataCollector`  
`struct FRuntimeDataCollector`  
_L894-908_
- L897 _public prototype_ `void Clear();`
- L898 _public prototype_ `void AddCollector(const FGuid& Guid, int32 TransformNum);`
- L899 _public prototype_ `void RemoveCollector(const FGuid& Guid);`
- L901 _public prototype_ `FDamageCollector* Find(const FGuid& Guid);`
- L903 _public prototype_ `static FRuntimeDataCollector& GetInstance();`
- L907 _private member_ `TMap<FGuid,FDamageCollector> Collectors;` — collectors by geometry collection Guids

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Chaos`
- L910 _prototype_ `TUniquePtr<Chaos::FTriangleMesh> CreateTriangleMesh(const int32 FaceStart,const int32 FaceCount,const TManagedArray<bool>& Visible,const TManagedArray<FIntVector>& Indices, bool bRotateWinding = true);`
- L911 _prototype_ `void BuildSimulationData(Chaos::FErrorReporter& ErrorReporter, FGeometryCollection& GeometryCollection, const FSharedSimulationParameters& SharedParams);`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/JointConstraintProxy.h` (Public)


#### class `Chaos::FJointConstraintPhysicsProxy`  
`class FJointConstraintPhysicsProxy : public IPhysicsProxyBase`  
_L32-108_
- inherits: `IPhysicsProxyBase`
- L34 _private typedef_ `using Base = IPhysicsProxyBase;`
- L37 _public prototype_ `FJointConstraintPhysicsProxy() = delete;`
- L38 _public prototype_ `FJointConstraintPhysicsProxy(FJointConstraint* InConstraint, FPBDJointConstraintHandle* InHandle, UObject* InOwner = nullptr);`
- L40 _public prototype_ `static FGeometryParticleHandle* GetParticleHandleFromProxy(IPhysicsProxyBase* ProxyBase);`
- L46 _public prototype_ `void InitializeOnPhysicsThread(FPBDRigidsSolver* InSolver, FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData);`
- L48 _public prototype_ `void PushStateOnGameThread(FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData);`
- L50 _public prototype_ `void PushStateOnPhysicsThread(FPBDRigidsSolver* InSolver, const FDirtyPropertiesManager& Manager, int32 DataIdx, const FDirtyChaosProperties& RemoteData);`
- L52 _public prototype_ `void DestroyOnPhysicsThread(FPBDRigidsSolver* InSolver);`
- L54 _public prototype_ `void DestroyOnGameThread();`
- L56 _public function_ `FORCEINLINE Chaos::FJointConstraintHandle_External& GetGameThreadAPI()`
- L61 _public function_ `FORCEINLINE const Chaos::FJointConstraintHandle_External& GetGameThreadAPI() const`
- L67 _public function_ `FORCEINLINE Chaos::FJointConstraintHandle_Internal* GetPhysicsThreadAPI()` — Note this is a pointer because the internal handle may have already been deleted
- L73 _public function_ `FORCEINLINE const Chaos::FJointConstraintHandle_Internal* GetPhysicsThreadAPI() const` — Note this is a pointer because the internal handle may have already been deleted
- L83 _public function_ `FPBDJointConstraintHandle* GetHandle()`
- L84 _public function_ `const FPBDJointConstraintHandle* GetHandle() const`
- L86 _public function_ `virtual void* GetHandleUnsafe() const override`
- L88 _public function_ `void SetHandle(FPBDJointConstraintHandle* InHandle)`
- L90 _public function_ `FJointConstraint* GetConstraint()`
- L91 _public function_ `const FJointConstraint* GetConstraint() const`
- L98 _public prototype_ `void BufferPhysicsResults(FDirtyJointConstraintData& Buffer);` — /
- L101 _public prototype_ `bool PullFromPhysicsState(const FDirtyJointConstraintData& Buffer, const int32 SolverSyncTimestamp);` — /
- L104 _private member_ `FJointConstraint* Constraint_GT;`
- L105 _private member_ `FPBDJointConstraintHandle* Constraint_PT;`
- L106 _private member_ `FParticlePair OriginalParticleHandles_PT;`
- L107 _private member_ `bool bInitialized = false;`

#### class `Chaos::TThreadedJointConstraintPhysicsProxyBase`  
`template <bool bExternal> class TThreadedJointConstraintPhysicsProxyBase : protected FJointConstraintPhysicsProxy`  
_L113-169_
- inherits: `FJointConstraintPhysicsProxy`
- desc: Wrapper class that routes all reads and writes to the appropriate joint data. This is helpful for cases where we want to both write to a joint and a network buffer for example
- L125 _private function_ `void VerifyContext() const`
- L147 _private function_ `template <typename TLambda> const auto& ReadRef(const TLambda& Lambda) const`
- L150 _private function_ `template <typename TLambda> void Write(const TLambda& Lambda)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`
- L29 _typedef_ `using FJointConstraintHandle_External = TThreadedJointConstraintPhysicsProxyBase<true>;` (scope `Chaos`)
- L30 _typedef_ `using FJointConstraintHandle_Internal = TThreadedJointConstraintPhysicsProxyBase<false>;` (scope `Chaos`)
- L117 _macro_ `#define CHAOS_INNER_JOINT_PROPERTY(OuterProp, FuncName, Inner, InnerType)\`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/JointConstraintProxyFwd.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Chaos`
- L12 _typedef_ `typedef FConstraintProxy< Chaos::FJointConstraint > FJointConstraintProxy;`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/PerSolverFieldSystem.h` (Public)


#### class `FPerSolverFieldSystem`  
`class FPerSolverFieldSystem`  
_L10-164_
- L33 _public prototype_ `void FieldParameterUpdateCallback( Chaos::FPBDRigidsSolver* InSolver, Chaos::FPBDPositionConstraints& PositionTarget, TMap<int32, int32>& TargetedParticles);` — Services queued \c FFieldSystemCommand commands. Supported fields: EFieldPhysicsType::Field_DynamicState EFieldPhysicsType::Field_ActivateDisabled EFieldPhysicsType::Field_ExternalClusterStrain (clustering) EFieldPhysicsType::Field_Kill EFieldPhysicsType::Field_LinearVelocity EFieldPhysicsType::Field_AngularVelociy EFieldPhysicsType::Field_SleepingThreshold EFieldPhysicsType::Field_DisableThreshold EFieldPhysicsType::Field_InternalClusterStrain (clustering) EFieldPhysicsType::Field_CollisionGroup EFieldPhysicsType::Field_PositionStatic EFieldPhysicsType::Field_PositionTarget EFieldPhysicsType::Field_PositionAnimated EFieldPhysicsType::Field_DynamicConstraint
- L45 _public prototype_ `void FieldForcesUpdateCallback( Chaos::FPBDRigidsSolver* RigidSolver);` — Services queued \c FFieldSystemCommand commands. Supported fields: EFieldPhysicsType::Field_LinearForce EFieldPhysicsType::Field_AngularTorque
- L57 _public prototype_ `void ComputeFieldRigidImpulse(const Chaos::FReal SolverTime);` — Compute field linear velocity/force and angular velocity/torque given a list of samples (positions + indices) Supported fields: FieldPhysicsType::Field_LinearVelocity EFieldPhysicsType::Field_LinearForce EFieldPhysicsType::Field_AngularVelocity EFieldPhysicsType::Field_AngularrTorque
- L66 _public prototype_ `void ComputeFieldLinearImpulse(const Chaos::FReal SolverTime);` — Compute field linear velocity/force given a list of samples (positions + indices) Supported fields: EFieldPhysicsType::Field_LinearVelocity EFieldPhysicsType::Field_LinearForce
- L69 _public prototype_ `void AddTransientCommand(const FFieldSystemCommand& FieldCommand);` — Add the transient field command
- L72 _public prototype_ `void AddPersistentCommand(const FFieldSystemCommand& FieldCommand);` — Add the persistent field command
- L75 _public prototype_ `void RemoveTransientCommand(const FFieldSystemCommand& FieldCommand);` — Remove the transient field command
- L78 _public prototype_ `void RemovePersistentCommand(const FFieldSystemCommand& FieldCommand);` — Remove the persistent field command
- L81 _public function_ `TArray<FFieldSystemCommand>& GetTransientCommands()` — Get all the non const transient field commands
- L84 _public function_ `const TArray<FFieldSystemCommand>& GetTransientCommands() const` — Get all the const transient field commands
- L87 _public function_ `TArray<FFieldSystemCommand>& GetPersistentCommands()` — Get all the non const persistent field commands
- L90 _public function_ `const TArray<FFieldSystemCommand>& GetPersistentCommands() const` — Get all the const persistent field commands
- L101 _public prototype_ `static void GetRelevantParticleHandles( TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, const Chaos::FPBDRigidsSolver* RigidSolver, const EFieldResolutionType ResolutionType);`
- L113 _public prototype_ `static void GetFilteredParticleHandles( TArray<Chaos::FGeometryParticleHandle*>& ParticleHandles, const Chaos::FPBDRigidsSolver* RigidSolver, const EFieldFilterType FilterType, const EFieldObjectType ObjectType);`
- L120 _public function_ `bool IsEmpty() const` — Check if a per solver field system has no commands.
- L123 _public function_ `const TArray<FVector>& GetSamplePositions() const` — Get the non const array of sample positions
- L126 _public function_ `TArray<FVector>& GetSamplePositions()` — Get the const array of sample positions
- L129 _public function_ `const TArray<FFieldContextIndex>& GetSampleIndices() const` — Get the const array of sample indices
- L132 _public function_ `TArray<FFieldContextIndex>& GetSampleIndices()` — Get the non const array of sample indices
- L135 _public function_ `TArray<FVector>& GetOutputResults(const EFieldCommandOutputType OutputType)` — Get the non const array of the output results given an output type
- L138 _public function_ `const TArray<FVector>& GetOutputResults(const EFieldCommandOutputType OutputType) const` — Get the const array of the output results given an output type
- L143 _private prototype_ `void FieldForcesUpdateInternal( Chaos::FPBDRigidsSolver* RigidSolver, TArray<FFieldSystemCommand>& Commands, const bool IsTransient);` — Forces update callback implementation
- L149 _private prototype_ `void FieldParameterUpdateInternal( Chaos::FPBDRigidsSolver* RigidSolver, Chaos::FPBDPositionConstraints& PositionTarget, TMap<int32, int32>& PositionTargetedParticles, TArray<FFieldSystemCommand>& Commands, const bool IsTransient);` — Parameter update callback implementation
- L157 _private member_ `FFieldExecutionDatas ExecutionDatas;` — Field Datas stored during evaluation
- L160 _private member_ `TArray<FFieldSystemCommand> TransientCommands;` — Transient commands to be processed by the chaos solver
- L163 _private member_ `TArray<FFieldSystemCommand> PersistentCommands;` — Persistent commands to be processed by the chaos solver

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/PhysicsProxies.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/SingleParticlePhysicsProxy.h` (Public)


#### class `Chaos::FInitialState`  
`class FInitialState`  
_L29-52_
- L32 _public function_ `FInitialState() : Mass(0.f) , InvMass(0.f) , InertiaTensor(1.f)`
- L38 _public function_ `FInitialState(FReal MassIn, FReal InvMassIn, FVector InertiaTensorIn) : Mass(MassIn) , InvMass(InvMassIn) , InertiaTensor(InertiaTensorIn)`
- L44 _public function_ `FReal GetMass() const`
- L45 _public function_ `FReal GetInverseMass() const`
- L46 _public function_ `FVector GetInertiaTensor() const`
- L49 _private member_ `FReal Mass;`
- L50 _private member_ `FReal InvMass;`
- L51 _private member_ `FVector InertiaTensor;`

#### class `Chaos::FSingleParticlePhysicsProxy`  
`class FSingleParticlePhysicsProxy : public IPhysicsProxyBase`  
_L57-214_
- inherits: `IPhysicsProxyBase`
- L60 _public typedef_ `using PARTICLE_TYPE = FGeometryParticle;`
- L61 _public typedef_ `using FParticleHandle = FGeometryParticleHandle;`
- L63 _public prototype_ `static FSingleParticlePhysicsProxy* Create(TUniquePtr<FGeometryParticle>&& Particle, UObject* InOwner);`
- L65 _public prototype_ `FSingleParticlePhysicsProxy() = delete;`
- L66 _public prototype_ `FSingleParticlePhysicsProxy(const FSingleParticlePhysicsProxy&) = delete;`
- L67 _public prototype_ `FSingleParticlePhysicsProxy(FSingleParticlePhysicsProxy&&) = delete;`
- L68 _public prototype_ `virtual ~FSingleParticlePhysicsProxy();`
- L70 _public function_ `FProxyInterpolationBase* GetInterpolationData()`
- L71 _public function_ `const FProxyInterpolationBase* GetInterpolationData() const`
- L73 _public function_ `void ResetInterpolationData()`
- L78 _public function_ `FORCEINLINE FRigidBodyHandle_External& GetGameThreadAPI()`
- L83 _public function_ `FORCEINLINE const FRigidBodyHandle_External& GetGameThreadAPI() const`
- L89 _public function_ `FORCEINLINE FRigidBodyHandle_Internal* GetPhysicsThreadAPI()` — Note this is a pointer because the internal handle may have already been deleted
- L95 _public function_ `FORCEINLINE const FRigidBodyHandle_Internal* GetPhysicsThreadAPI() const` — Note this is a pointer because the internal handle may have already been deleted
- L101 _public function_ `FParticleHandle* GetHandle_LowLevel()` — Returns the underlying physics thread particle. Note this should only be needed for internal book keeping type tasks. API may change, use GetPhysicsThreadAPI instead
- L107 _public function_ `const FParticleHandle* GetHandle_LowLevel() const` — Returns the underlying physics thread particle. Note this should only be needed for internal book keeping type tasks. API may change, use GetPhysicsThreadAPI instead
- L112 _public function_ `virtual void* GetHandleUnsafe() const override`
- L117 _public function_ `void SetHandle(FParticleHandle* InHandle)`
- L124 _public prototype_ `void PushToPhysicsState(const FDirtyPropertiesManager& Manager,int32 DataIdx,const FDirtyProxy& Dirty,FShapeDirtyData* ShapesData, FReal ExternalDt);`
- L127 _public prototype_ `void ClearAccumulatedData();` — /
- L130 _public prototype_ `void BufferPhysicsResults(FDirtyRigidParticleData&);` — /
- L133 _public prototype_ `void BufferPhysicsResults_External(FDirtyRigidParticleData&);` — /
- L136 _public prototype_ `bool PullFromPhysicsState(const FDirtyRigidParticleData& PullData, int32 SolverSyncTimestamp, const FDirtyRigidParticleData* NextPullData = nullptr, const FRealSingle* Alpha = nullptr, const FDirtyRigidParticleReplicationErrorData* Error = nullptr, const Chaos::FReal AsyncFixedTimeStep = 0);` — /
- L139 _public prototype_ `bool IsDirty();` — /
- L143 _public prototype_ `EWakeEventEntry GetWakeEvent() const;` — /
- L146 _public prototype_ `void ClearEvents();` — /
- L149 _public function_ `PARTICLE_TYPE* GetParticle_LowLevel()` — Returns the underlying game thread particle. Note this should only be needed for internal book keeping type tasks. API may change, use GetGameThreadAPI instead
- L155 _public function_ `const PARTICLE_TYPE* GetParticle_LowLevel() const` — Returns the underlying game thread particle. Note this should only be needed for internal book keeping type tasks. API may change, use GetGameThreadAPI instead
- L160 _public function_ `FPBDRigidParticle* GetRigidParticleUnsafe()`
- L165 _public function_ `const FPBDRigidParticle* GetRigidParticleUnsafe() const`
- L170 _public function_ `FPhysicsObjectHandle GetPhysicsObject()`
- L175 _public function_ `const FPhysicsObjectHandle GetPhysicsObject() const`
- L182 _public function_ `template<typename ErrorDataType> ErrorDataType* GetOrCreateErrorInterpolationData()` — Get or create a derived FProxyInterpolationBase that handles render interpolation error corrections
- L197 _public function_ `template<typename ErrorDataType> const ErrorDataType* GetErrorInterpolationData() const`
- L203 _protected member_ `TUniquePtr<PARTICLE_TYPE> Particle;`
- L204 _protected member_ `FParticleHandle* Handle;`
- L205 _protected member_ `FPhysicsObjectUniquePtr Reference;`
- L207 _protected member_ `int32 GravityGroupIndex;`
- L210 _private member_ `TUniquePtr<FProxyInterpolationBase> InterpolationData;`
- L213 _private prototype_ `FSingleParticlePhysicsProxy(TUniquePtr<PARTICLE_TYPE>&& InParticle, FParticleHandle* InHandle, UObject* InOwner = nullptr);` — use static Create
- L1678 _function_ `inline FSingleParticlePhysicsProxy* FSingleParticlePhysicsProxy::Create(TUniquePtr<FGeometryParticle>&& Particle, UObject* InOwner = nullptr)`

#### class `Chaos::TThreadedSingleParticlePhysicsProxyBase`  
`template <bool bExternal> class TThreadedSingleParticlePhysicsProxyBase : protected FSingleParticlePhysicsProxy`  
_L218-1161_
- inherits: `FSingleParticlePhysicsProxy`
- desc: Wrapper class that routes all reads and writes to the appropriate particle data. This is helpful for cases where we want to both write to a particle and a network buffer for example
- L220 _private prototype_ `TThreadedSingleParticlePhysicsProxyBase() = delete;` — You should only ever new FSingleParticlePhysicsProxy, derived types are simply there for API constraining, no new data
- L223 _public function_ `FSingleParticlePhysicsProxy* GetProxy()`
- L225 _public function_ `bool CanTreatAsKinematic() const`
- L230 _public function_ `bool CanTreatAsRigid() const`
- L236 _public function_ `const FVec3& X() const` — API for static particle
- L237 _public function_ `const FVec3& GetX() const`
- L240 _protected function_ `void SetXBase(const FVec3& InX, bool bInvalidate = true)`
- L254 _public function_ `FUniqueIdx UniqueIdx() const`
- L255 _public function_ `void SetUniqueIdx(const FUniqueIdx UniqueIdx, bool bInvalidate = true)`
- L257 _public function_ `FRotation3 R() const`
- L258 _public function_ `FRotation3 GetR() const`
- L261 _protected function_ `void SetRBase(const FRotation3& InR, bool bInvalidate = true)`
- L276 _public function_ `const TSharedPtr<FImplicitObject, ESPMode::ThreadSafe>& SharedGeometryLowLevel() const` — `UE_DEPRECATED(5.4, "Use GetGeometry instead.")`
- L285 _public function_ `const TSharedPtr<FString, ESPMode::ThreadSafe>& DebugName() const`
- L286 _public function_ `void SetDebugName(const TSharedPtr<FString, ESPMode::ThreadSafe>& InDebugName)`
- L289 _public function_ `const FImplicitObjectRef GetGeometry() const`
- L292 _public function_ `TSerializablePtr<FImplicitObject> Geometry() const` — `UE_DEPRECATED(5.4, "Please use GetGeometry instead")`
- L294 _public function_ `const FShapesArray& ShapesArray() const`
- L296 _public function_ `EObjectStateType ObjectState() const`
- L298 _public function_ `EParticleType ObjectType() const`
- L300 _public function_ `FSpatialAccelerationIdx SpatialIdx() const`
- L301 _public function_ `void SetSpatialIdx(FSpatialAccelerationIdx Idx)`
- L304 _public function_ `const FVec3 V() const` — API for kinematic particle
- L316 _public function_ `const FVec3 GetV() const`
- L322 _protected function_ `void SetVBase(const FVec3& InV, bool bInvalidate = true)`
- L343 _public function_ `const FVec3 W() const`
- L356 _public function_ `const FVec3 GetW() const`
- L362 _protected function_ `void SetWBase(const FVec3& InW, bool bInvalidate = true)`
- L383 _public function_ `void SetKinematicTarget(const FRigidTransform3& InTargetTransform, bool bInvalidate = true)`
- L388 _public function_ `void SetKinematicTarget(const FKinematicTarget& InKinematicTarget, bool bInvalidate = true)`
- L401 _public function_ `bool GravityEnabled() const`
- L414 _public function_ `void SetGravityEnabled(const bool InGravityEnabled)`
- L425 _public function_ `int32 GravityGroupIndex() const`
- L438 _public function_ `void SetGravityGroupIndex(const uint32 InGravityGroupIndex)`
- L449 _public function_ `bool UpdateKinematicFromSimulation() const`
- L462 _public function_ `void SetUpdateKinematicFromSimulation(const bool InUpdateKinematicFromSimulation)`
- L473 _public function_ `bool GyroscopicTorqueEnabled() const`
- L486 _public function_ `void SetGyroscopicTorqueEnabled(const bool InGyroscopicTorqueEnabled)`
- L497 _public function_ `bool CCDEnabled() const`
- L510 _public function_ `void SetCCDEnabled(const bool InCCDEnabled)`
- L521 _public function_ `bool MACDEnabled() const`
- L534 _public function_ `void SetMACDEnabled(const bool InMACDEnabled)`
- L545 _public function_ `bool PartialIslandSleepAllowed() const`
- L558 _public function_ `void SetPartialIslandSleepAllowed(const bool InPartialIslandSleepAllowed)`
- L569 _public function_ `void SetPositionSolverIterations(const int32 PositionSolverIterationsIn)`
- L580 _public function_ `void SetVelocitySolverIterations(const int32 VelocitySolverIterationsIn)`
- L591 _public function_ `void SetProjectionSolverIterations(const int32 ProjectionSolverIterationsIn)`
- L602 _public function_ `bool OneWayInteraction() const`
- L615 _public function_ `void SetOneWayInteraction(const bool bInOneWayInteraction)`
- L626 _public function_ `bool InertiaConditioningEnabled() const`
- L639 _public function_ `void SetInertiaConditioningEnabled(const bool bInEnabled)`
- L650 _public function_ `EResimType ResimType() const`
- L663 _public function_ `void SetResimType(EResimType ResimType)`
- L674 _public function_ `const FVec3 Acceleration() const`
- L687 _public function_ `void SetAcceleration(const FVec3& Acceleration, bool bInvalidate = true)`
- L706 _public function_ `void AddForce(const FVec3& InForce, bool bInvalidate = true)`
- L725 _public function_ `void SetAngularAcceleration(const FVec3& AngularAcceleration, bool bInvalidate = true)`
- L744 _public function_ `const FVec3 AngularAcceleration() const`
- L757 _public function_ `void AddTorque(const FVec3& InTorque, bool bInvalidate = true)`
- L776 _public function_ `const FVec3 LinearImpulseVelocity() const`
- L789 _public function_ `const FVec3 LinearImpulse() const`
- L802 _public function_ `void SetLinearImpulse(const FVec3& InLinearImpulse, bool bIsVelocity, bool bInvalidate = true)`
- L828 _public function_ `const FVec3 AngularImpulseVelocity() const`
- L841 _public function_ `const FVec3 AngularImpulse() const`
- L855 _public function_ `void SetAngularImpulse(const FVec3& InAngularImpulse, bool bIsVelocity, bool bInvalidate = true)`
- L882 _public function_ `const Chaos::TVec3<FRealSingle> I() const`
- L895 _public function_ `void SetI(const Chaos::TVec3<FRealSingle>& InI)`
- L906 _public function_ `const Chaos::TVec3<FRealSingle> InvI() const`
- L919 _public function_ `void SetInvI(const Chaos::TVec3<FRealSingle>& InInvI)`
- L930 _public function_ `const FReal M() const`
- L943 _public function_ `void SetM(const FReal InM)`
- L954 _public function_ `const FReal InvM() const`
- L967 _public function_ `void SetInvM(const FReal InInvM)`
- L978 _public function_ `const FVec3 CenterOfMass() const`
- L991 _public function_ `void SetCenterOfMass(const FVec3& InCenterOfMass, bool bInvalidate = true)`
- L1002 _public function_ `const FRotation3 RotationOfMass() const`
- L1015 _public function_ `void SetRotationOfMass(const FRotation3& InRotationOfMass, bool bInvalidate = true)`
- L1026 _public function_ `const FReal LinearEtherDrag() const`
- L1039 _public function_ `void SetLinearEtherDrag(const FReal InLinearEtherDrag)`
- L1050 _public function_ `const FReal AngularEtherDrag() const`
- L1063 _public function_ `void SetAngularEtherDrag(const FReal InAngularEtherDrag)`
- L1075 _protected function_ `void SetObjectStateBase(const EObjectStateType InState, bool bAllowEvents = false, bool bInvalidate = true)`
- L1087 _public function_ `void SetSleepType(ESleepType InSleepType)`
- L1098 _public function_ `ESleepType SleepType() const`
- L1109 _protected function_ `void VerifyContext() const`
- L1133 _private function_ `template <typename TLambda> auto Read(const TLambda& Lambda) const`
- L1136 _private function_ `template <typename TLambda> const auto& ReadRef(const TLambda& Lambda) const`
- L1139 _private function_ `template <typename TLambda> auto& ReadRef(const TLambda& Lambda)`
- L1142 _private function_ `template <typename TLambda> void Write(const TLambda& Lambda)`

#### class `Chaos::FRigidBodyHandle_External`  
`class FRigidBodyHandle_External : public TThreadedSingleParticlePhysicsProxyBase<true>`  
_L1167-1605_
- inherits: `TThreadedSingleParticlePhysicsProxyBase<true>`
- L1169 _private prototype_ `FRigidBodyHandle_External() = delete;` — You should only ever new FSingleParticlePhysicsProxy, derrived types are simply there for API constraining, no new data
- L1172 _public typedef_ `using Base = TThreadedSingleParticlePhysicsProxyBase<true>;`
- L1175 _public function_ `void SetIgnoreAnalyticCollisions(bool bIgnoreAnalyticCollisions)`
- L1176 _public function_ `void UpdateShapeBounds()`
- L1178 _public function_ `void UpdateShapeBounds(const FTransform& Transform)`
- L1180 _public function_ `void SetShapeCollisionTraceType(int32 InShapeIndex, EChaosCollisionTraceFlag TraceType)`
- L1182 _public function_ `void SetShapeSimCollisionEnabled(int32 InShapeIndex, bool bInEnabled)`
- L1183 _public function_ `void SetShapeQueryCollisionEnabled(int32 InShapeIndex, bool bInEnabled)`
- L1185 _public function_ `void SetShapeSimData(int32 InShapeIndex, const FCollisionFilterData& SimData)` — `UE_DEPRECATED(5.8, "Use SetShapeFilterData instead")`
- L1192 _public prototype_ `void SetShapeFilterData(int32 InShapeIndex, const Filter::FShapeFilterData& FilterData);`
- L1193 _public prototype_ `void SetShapeFilterInstanceData(int32 InShapeIndex, const Filter::FInstanceData& InstanceData);`
- L1195 _public function_ `void SetParticleID(const FParticleID& ParticleID)`
- L1201 _public function_ `void SetX(const FVec3& InX, bool bInvalidate = true)`
- L1209 _public function_ `void SetR(const FRotation3& InR, bool bInvalidate = true)`
- L1217 _public function_ `void SetV(const FVec3& InV, bool bInvalidate = true)`
- L1231 _public function_ `void SetW(const FVec3& InW, bool bInvalidate = true)`
- L1246 _public function_ `void SetObjectState(const EObjectStateType InState, bool bAllowEvents = false, bool bInvalidate = true)`
- L1272 _public function_ `int32 Island() const`
- L1283 _public function_ `void SetIsland(const int32 InIsland)` — TODO(stett): Make the setter private. It is public right now to provide access to proxies.
- L1292 _public function_ `void ClearEvents()`
- L1301 _public function_ `EWakeEventEntry GetWakeEvent()`
- L1312 _public function_ `void ClearForces(bool bInvalidate = true)`
- L1322 _public function_ `void ClearTorques(bool bInvalidate = true)`
- L1331 _public function_ `void* UserData() const`
- L1332 _public function_ `void SetUserData(void* InUserData)`
- L1334 _public function_ `void SetGeometry(const Chaos::FImplicitObjectPtr& ImplicitGeometryPtr)`
- L1340 _public function_ `void MarkNonFrequentDataDirty()`
- L1362 _public function_ `void SetGeometry(TUniquePtr<FImplicitObject>&& UniqueGeometry)` — `UE_DEPRECATED(5.4, "Use SetGeometry with FImplicitObjectPtr instead.")`
- L1368 _public function_ `void SetGeometry(TSharedPtr<const FImplicitObject, ESPMode::ThreadSafe> SharedGeometry)` — `UE_DEPRECATED(5.4, "Use SetGeometry with FImplicitObjectPtr instead.")`
- L1373 _public function_ `void RemoveShape(FPerShapeData* InShape, bool bWakeTouching)`
- L1375 _public function_ `void MergeShapesArray(FShapesArray&& OtherShapesArray)`
- L1377 _public function_ `void MergeGeometry(TArray<Chaos::FImplicitObjectPtr>&& Objects)`
- L1380 _public function_ `void MergeGeometry(TArray<TUniquePtr<FImplicitObject>>&& Objects)` — `UE_DEPRECATED(5.4, "Please use MergeGeometry with FImplicitObjectPtr instead.")`
- L1382 _public function_ `bool IsKinematicTargetDirty() const`
- L1392 _public function_ `void ClearKinematicTarget()`
- L1401 _public function_ `void SetSmoothEdgeCollisionsEnabled(bool bEnabled)`
- L1417 _public function_ `void SetCCDEnabled(bool bEnabled)`
- L1426 _public function_ `bool CCDEnabled() const`
- L1437 _public function_ `void SetMACDEnabled(bool bEnabled)`
- L1446 _public function_ `bool MACDEnabled() const`
- L1457 _public function_ `void SetPartialIslandSleepAllowed(bool bEnabled)`
- L1466 _public function_ `bool PartialIslandSleepAllowed() const`
- L1477 _public function_ `Private::FIterationSettings IterationSettings() const`
- L1488 _public function_ `void SetPositionSolverIterationCount(int32 PositionSolverIterationCountIn)`
- L1498 _public function_ `void SetVelocitySolverIterationCount(int32 VelocitySolverIterationCountIn)`
- L1508 _public function_ `void SetProjectionSolverIterationCount(int32 ProjectionSolverIterationCountIn)`
- L1517 _public function_ `void SetMaxLinearSpeedSq(FReal InNewSpeed)`
- L1526 _public function_ `FReal GetMaxLinearSpeedSq()`
- L1537 _public function_ `void SetMaxAngularSpeedSq(FReal InNewSpeed)`
- L1546 _public function_ `FReal GetMaxAngularSpeedSq()`
- L1557 _public function_ `FRealSingle GetInitialOverlapDepenetrationVelocity()`
- L1568 _public function_ `void SetInitialOverlapDepenetrationVelocity(FRealSingle InNewSpeed)`
- L1577 _public function_ `void SetSleepThresholdMultiplier(FRealSingle Multiplier)`
- L1586 _public function_ `void SetDisabled(bool bDisable)`
- L1595 _public function_ `bool Disabled() const`

#### class `Chaos::FRigidBodyHandle_Internal`  
`class FRigidBodyHandle_Internal : public TThreadedSingleParticlePhysicsProxyBase<false>`  
_L1610-1674_
- inherits: `TThreadedSingleParticlePhysicsProxyBase<false>`
- L1612 _private prototype_ `FRigidBodyHandle_Internal() = delete;` — You should only ever new FSingleParticlePhysicsProxy, derived types are simply there for API constraining, no new data
- L1615 _public typedef_ `using Base = TThreadedSingleParticlePhysicsProxyBase<false>;`
- L1617 _public function_ `const FVec3 PreV() const`
- L1627 _public function_ `const FVec3 PreW() const`
- L1637 _public function_ `void SetX(const FVec3& InX, bool bInvalidate = true)`
- L1647 _public function_ `void SetR(const FRotation3& InR, bool bInvalidate = true)`
- L1657 _public function_ `void SetV(const FVec3& InV, bool bInvalidate = true)`
- L1663 _public function_ `void SetW(const FVec3& InW, bool bInvalidate = true)`
- L1669 _public function_ `void SetObjectState(const EObjectStateType InState, bool bAllowEvents = false, bool bInvalidate = true)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Chaos`
- L227 _function_ `return Read([](auto* Particle) { return Particle->CastToKinematicParticle() != nullptr; });` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::CanTreatAsKinematic`)
- L232 _function_ `return Read([](auto* Particle) { return Particle->CastToRigidParticle() != nullptr; });` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::CanTreatAsRigid`)
- L236 _function_ `const FVec3& X() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::X`) — API for static particle
- L237 _function_ `const FVec3& GetX() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::GetX`)
- L241 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetXBase`)
- L254 _function_ `FUniqueIdx UniqueIdx() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::UniqueIdx`)
- L255 _function_ `void SetUniqueIdx(const FUniqueIdx UniqueIdx, bool bInvalidate = true)` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetUniqueIdx`)
- L257 _function_ `FRotation3 R() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::R`)
- L258 _function_ `FRotation3 GetR() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::GetR`)
- L262 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetRBase`)
- L285 _function_ `const TSharedPtr<FString, ESPMode::ThreadSafe>& DebugName() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::DebugName`)
- L286 _function_ `void SetDebugName(const TSharedPtr<FString, ESPMode::ThreadSafe>& InDebugName)` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetDebugName`)
- L289 _function_ `const FImplicitObjectRef GetGeometry() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::GetGeometry`)
- L294 _function_ `const FShapesArray& ShapesArray() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::ShapesArray`)
- L296 _function_ `EObjectStateType ObjectState() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::ObjectState`)
- L298 _function_ `EParticleType ObjectType() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::ObjectType`)
- L300 _function_ `FSpatialAccelerationIdx SpatialIdx() const` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SpatialIdx`)
- L301 _function_ `void SetSpatialIdx(FSpatialAccelerationIdx Idx)` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetSpatialIdx`)
- L307 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::V`)
- L325 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetVBase`)
- L346 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::W`)
- L365 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetWBase`)
- L391 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetKinematicTarget`)
- L404 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::GravityEnabled`)
- L417 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetGravityEnabled`)
- L428 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::GravityGroupIndex`)
- L441 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetGravityGroupIndex`)
- L452 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::UpdateKinematicFromSimulation`)
- L465 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetUpdateKinematicFromSimulation`)
- L476 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::GyroscopicTorqueEnabled`)
- L489 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetGyroscopicTorqueEnabled`)
- L500 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::CCDEnabled`)
- L513 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetCCDEnabled`)
- L524 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::MACDEnabled`)
- L537 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetMACDEnabled`)
- L548 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::PartialIslandSleepAllowed`)
- L561 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetPartialIslandSleepAllowed`)
- L572 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetPositionSolverIterations`)
- L583 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetVelocitySolverIterations`)
- L594 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetProjectionSolverIterations`)
- L605 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::OneWayInteraction`)
- L618 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetOneWayInteraction`)
- L629 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::InertiaConditioningEnabled`)
- L642 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetInertiaConditioningEnabled`)
- L653 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::ResimType`)
- L666 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetResimType`)
- L677 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::Acceleration`)
- L690 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetAcceleration`)
- L709 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::AddForce`)
- L728 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetAngularAcceleration`)
- L747 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::AngularAcceleration`)
- L760 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::AddTorque`)
- L779 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::LinearImpulseVelocity`)
- L792 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::LinearImpulse`)
- L805 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetLinearImpulse`)
- L831 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::AngularImpulseVelocity`)
- L844 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::AngularImpulse`)
- L858 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetAngularImpulse`)
- L885 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::I`)
- L898 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetI`)
- L909 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::InvI`)
- L922 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetInvI`)
- L933 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::M`)
- L946 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetM`)
- L957 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::InvM`)
- L970 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetInvM`)
- L981 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::CenterOfMass`)
- L994 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetCenterOfMass`)
- L1005 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::RotationOfMass`)
- L1018 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetRotationOfMass`)
- L1029 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::LinearEtherDrag`)
- L1042 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetLinearEtherDrag`)
- L1053 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::AngularEtherDrag`)
- L1066 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetAngularEtherDrag`)
- L1078 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetObjectStateBase`)
- L1090 _function_ `` (scope `Chaos::TThreadedSingleParticlePhysicsProxyBase::SetSleepType`)

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/SingleParticlePhysicsProxyFwd.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/SkeletalMeshPhysicsProxy.h` (Public)


#### struct `FSkeletalMeshPhysicsProxyParams`  
`struct FSkeletalMeshPhysicsProxyParams`  
_L18-93_
- L20 _public function_ `FSkeletalMeshPhysicsProxyParams() : Name("") , InitialTransform(FTransform::Identity) , InitialLinearVelocity(FVector::ZeroVector) , InitialAngularVelocity(FVector::ZeroVector) , ObjectType(EObjectStateTypeEnum::Chaos_Object_Kinematic) , CollisionType(ECollisionTypeEnum::Chaos_Volumetric) , ParticlesPerUnitArea(0.1f) , MinNumParticles(0) , MaxNumParticles(50) , MinRes(5) , MaxRes(10) , CollisionGroup(0) #if 0 , bEnableClustering(false) , ClusterGroupIndex(0) , MaxClusterLevel(100) , DamageThreshold(250.f) #endif , Density(2.4f) , MinMass(0.001f) , MaxMass(1.e6f) , bSimulating(false)`
- L48 _public member_ `FString Name;`
- L54 _public member_ `FBoneHierarchy BoneHierarchy;`
- L60 _public member_ `TArray<FVector> MeshVertexPositions;`
- L61 _public member_ `TArray<FIntVector> Triangles;`
- L67 _public member_ `FTransform InitialTransform;`
- L68 _public member_ `FTransform LocalToWorld;`
- L69 _public member_ `FVector InitialLinearVelocity;`
- L70 _public member_ `FVector InitialAngularVelocity;`
- L72 _public member_ `Chaos::TSerializablePtr<Chaos::FChaosPhysicsMaterial> PhysicalMaterial;` — @todo(ccaulfield): should be per-shape
- L73 _public member_ `EObjectStateTypeEnum ObjectType;` — @todo(ccaulfield): should be per-body
- L75 _public member_ `ECollisionTypeEnum CollisionType;`
- L76 _public member_ `float ParticlesPerUnitArea;`
- L77 _public member_ `int32 MinNumParticles;`
- L78 _public member_ `int32 MaxNumParticles;`
- L79 _public member_ `int32 MinRes;`
- L80 _public member_ `int32 MaxRes;`
- L81 _public member_ `int32 CollisionGroup;`
- L88 _public member_ `float Density;`
- L89 _public member_ `float MinMass;`
- L90 _public member_ `float MaxMass;`
- L92 _public member_ `bool bSimulating;`

#### struct `FSkeletalMeshPhysicsProxyInputs`  
`struct FSkeletalMeshPhysicsProxyInputs`  
_L96-101_
- desc: @todo(ccaulfield): make the IO structures private again - only the hierarchy should be required outside the PhysicsProxy
- L98 _public member_ `TArray<FTransform> Transforms;`
- L99 _public member_ `TArray<FVector> LinearVelocities;`
- L100 _public member_ `TArray<FVector> AngularVelocities;`

#### struct `FSkeletalMeshPhysicsProxyOutputs`  
`struct FSkeletalMeshPhysicsProxyOutputs`  
_L103-113_
- desc: : public Chaos::FParticleData
- L105 _public member_ `TArray<FTransform> Transforms;`
- L106 _public member_ `TArray<FVector> LinearVelocities;`
- L107 _public member_ `TArray<FVector> AngularVelocities;`
- L108 _public function_ `void Reset()`

#### class `FSkeletalMeshPhysicsProxy`  
`class FSkeletalMeshPhysicsProxy : public TPhysicsProxy<FSkeletalMeshPhysicsProxy, FSkeletalMeshPhysicsProxyOutputs, FProxyTimestampBase>`  
_L116-178_
- inherits: `TPhysicsProxy<FSkeletalMeshPhysicsProxy,FSkeletalMeshPhysicsProxyOutputs,FProxyTimestampBase>`
- L118 _private typedef_ `typedef TPhysicsProxy<FSkeletalMeshPhysicsProxy, FSkeletalMeshPhysicsProxyOutputs, FProxyTimestampBase> Base;`
- L122 _public typedef_ `using FInitFunc = TFunction<void(FSkeletalMeshPhysicsProxyParams& OutParams)>;`
- L123 _public typedef_ `using FInputFunc = TFunction<bool(const float Dt, FSkeletalMeshPhysicsProxyParams& OutParams)>;`
- L126 _public prototype_ `FSkeletalMeshPhysicsProxy() = delete;`
- L127 _public prototype_ `FSkeletalMeshPhysicsProxy(UObject* InOwner, const FInitFunc& InitFunc);`
- L128 _public prototype_ `~FSkeletalMeshPhysicsProxy();`
- L131 _public prototype_ `void Initialize();` — Solver Object interface
- L132 _public prototype_ `bool IsSimulating() const;`
- L133 _public prototype_ `void UpdateKinematicBodiesCallback(const FParticlesType& Particles, const float Dt, const float Time, FKinematicProxy& Proxy);`
- L134 _public prototype_ `void StartFrameCallback(const float InDt, const float InTime);`
- L135 _public prototype_ `void EndFrameCallback(const float InDt);`
- L136 _public prototype_ `void CreateRigidBodyCallback(FParticlesType& InOutParticles);`
- L137 _public prototype_ `void ParameterUpdateCallback(FParticlesType& InParticles, const float InTime);`
- L138 _public prototype_ `void DisableCollisionsCallback(TSet<TTuple<int32, int32>>& InPairs);`
- L139 _public prototype_ `void AddForceCallback(FParticlesType& InParticles, const float InDt, const int32 InIndex);`
- L141 _public prototype_ `void BindParticleCallbackMapping(Chaos::TArrayCollectionArray<PhysicsProxyWrapper>& PhysicsProxyReverseMap, Chaos::TArrayCollectionArray<int32>& ParticleIDReverseMap);`
- L143 _public function_ `void BufferCommand(Chaos::FPhysicsSolver* InSolver, const FFieldSystemCommand& InCommmand)`
- L145 _public function_ `FSkeletalMeshPhysicsProxyOutputs* NewData()`
- L146 _public prototype_ `void SyncBeforeDestroy();`
- L147 _public prototype_ `void OnRemoveFromScene();`
- L148 _public function_ `void PushToPhysicsState(const Chaos::FParticleData*)`
- L149 _public function_ `void ClearAccumulatedData()`
- L150 _public prototype_ `void BufferPhysicsResults();`
- L151 _public prototype_ `void FlipBuffer();`
- L152 _public prototype_ `bool PullFromPhysicsState(const int32 SolverSyncTimestamp);`
- L153 _public function_ `bool IsDirty()`
- L154 _public function_ `static constexpr EPhysicsProxyType ConcreteType()`
- L160 _public prototype_ `void Reset();`
- L166 _public prototype_ `void CaptureInputs(const float Dt, const FInputFunc& InputFunc);` — Capture the current animation pose for use by the physics. Called by game thread via the owning component's tick.
- L170 _public function_ `const FSkeletalMeshPhysicsProxyOutputs* GetOutputs() const`
- L172 _public function_ `const FBoneHierarchy& GetBoneHierarchy() const`
- L175 _private typedef_ `using FJointConstraints = Chaos::FPBDJointConstraints;`
- L177 _private member_ `FSkeletalMeshPhysicsProxyParams Parameters;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/StaticMeshPhysicsProxy.h` (Public)


#### struct `FPhysicsProxyKinematicUpdate`  
`struct FPhysicsProxyKinematicUpdate`  
_L16-20_
- L18 _public member_ `FTransform NewTransform;`
- L19 _public member_ `FVector NewVelocity;`

#### struct `FStubSkeletalMeshData`  
`struct FStubSkeletalMeshData`  
_L22-25_
- desc: : public Chaos::FParticleData
- L24 _public function_ `void Reset()`

#### class `FStaticMeshPhysicsProxy`  
`class FStaticMeshPhysicsProxy : public TPhysicsProxy<FStaticMeshPhysicsProxy, FStubSkeletalMeshData, FProxyTimestampBase>`  
_L27-115_
- inherits: `TPhysicsProxy<FStaticMeshPhysicsProxy,FStubSkeletalMeshData,FProxyTimestampBase>`
- L29 _private typedef_ `typedef TPhysicsProxy<FStaticMeshPhysicsProxy, FStubSkeletalMeshData, FProxyTimestampBase> Base;`
- L78 _public typedef_ `using FCallbackInitFunc = TFunction<void(FStaticMeshPhysicsProxy::Params&)>;` — Engine interface functions
- L79 _public typedef_ `using FSyncDynamicFunc = TFunction<void(const FTransform&)>;`
- L81 _public prototype_ `FStaticMeshPhysicsProxy() = delete;`
- L82 _public prototype_ `FStaticMeshPhysicsProxy(UObject* InOwner, FCallbackInitFunc InInitFunc, FSyncDynamicFunc InSyncFunc);`
- L84 _public prototype_ `void Initialize();`
- L85 _public prototype_ `void Reset();`
- L88 _public prototype_ `void BufferKinematicUpdate(const FPhysicsProxyKinematicUpdate& InParamUpdate);` — Stores latest update, to be applied at next opportunity (via UpdateKinematicBodiesCallback).
- L91 _public prototype_ `bool IsSimulating() const;` — Solver Object interface
- L92 _public prototype_ `void UpdateKinematicBodiesCallback(const FParticlesType& Particles, const float Dt, const float Time, FKinematicProxy& Proxy);`
- L93 _public prototype_ `void StartFrameCallback(const float InDt, const float InTime);`
- L94 _public prototype_ `void EndFrameCallback(const float InDt);`
- L95 _public prototype_ `void BindParticleCallbackMapping(Chaos::TArrayCollectionArray<PhysicsProxyWrapper> & PhysicsProxyReverseMap, Chaos::TArrayCollectionArray<int32> & ParticleIDReverseMap);`
- L96 _public prototype_ `void CreateRigidBodyCallback(FParticlesType& InOutParticles);`
- L97 _public prototype_ `void ParameterUpdateCallback(FParticlesType& InParticles, const float InTime);`
- L98 _public prototype_ `void DisableCollisionsCallback(TSet<TTuple<int32, int32>>& InPairs);`
- L99 _public prototype_ `void AddForceCallback(FParticlesType& InParticles, const float InDt, const int32 InIndex);`
- L100 _public function_ `void BufferCommand(Chaos::FPhysicsSolver* InSolver, const FFieldSystemCommand& InCommand)`
- L102 _public function_ `void SyncBeforeDestroy()`
- L103 _public prototype_ `void OnRemoveFromScene();`
- L104 _public function_ `void PushToPhysicsState(const Chaos::FParticleData*)`
- L105 _public function_ `void ClearAccumulatedData()`
- L106 _public prototype_ `void BufferPhysicsResults();`
- L107 _public prototype_ `void FlipBuffer();`
- L108 _public prototype_ `bool PullFromPhysicsState(const int32 SolverSyncTimestamp);`
- L109 _public function_ `bool IsDirty()`
- L110 _public function_ `FStubSkeletalMeshData* NewData()`
- L111 _public function_ `static constexpr EPhysicsProxyType ConcreteType()`

#### struct `FStaticMeshPhysicsProxy::FShapeParams`  
`struct FShapeParams`  
_L32-42_
- L34 _public member_ `FVector BoxExtents;`
- L35 _public member_ `FVector2D CapsuleHalfHeightAndRadius;`
- L36 _public member_ `float SphereRadius;`
- L38 _public function_ `FShapeParams()`

#### struct `FStaticMeshPhysicsProxy::Params`  
`struct Params`  
_L44-75_
- L46 _public function_ `Params() : Name("") , InitialTransform(FTransform::Identity) , InitialLinearVelocity(FVector::ZeroVector) , InitialAngularVelocity(FVector::ZeroVector) , ObjectType(EObjectStateTypeEnum::Chaos_Object_Dynamic) , ShapeType(EImplicitTypeEnum::Chaos_Max) , bSimulating(false) , TargetTransform(nullptr) , Mass(0.0f) , MinRes(5) , MaxRes(10)`
- L60 _public member_ `FString Name;`
- L61 _public member_ `Chaos::FParticles MeshVertexPositions;`
- L62 _public member_ `TArray<Chaos::TVector<int32, 3> > TriIndices;`
- L63 _public member_ `FShapeParams ShapeParams;`
- L64 _public member_ `FTransform InitialTransform;`
- L65 _public member_ `FVector InitialLinearVelocity;`
- L66 _public member_ `FVector InitialAngularVelocity;`
- L67 _public member_ `EObjectStateTypeEnum ObjectType;`
- L68 _public member_ `EImplicitTypeEnum ShapeType;`
- L69 _public member_ `bool bSimulating;`
- L70 _public member_ `FTransform* TargetTransform;`
- L71 _public member_ `Chaos::TSerializablePtr<Chaos::FChaosPhysicsMaterial> PhysicalMaterial;`
- L72 _public member_ `float Mass;`
- L73 _public member_ `int32 MinRes;`
- L74 _public member_ `int32 MaxRes;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsProxy/SuspensionConstraintProxy.h` (Public)


#### class `Chaos::FSuspensionConstraintPhysicsProxy`  
`class FSuspensionConstraintPhysicsProxy : public IPhysicsProxyBase`  
_L21-90_
- inherits: `IPhysicsProxyBase`
- L24 _public typedef_ `using Base = IPhysicsProxyBase;`
- L26 _public prototype_ `FSuspensionConstraintPhysicsProxy() = delete;`
- L27 _public prototype_ `FSuspensionConstraintPhysicsProxy(FSuspensionConstraint* InConstraint, FPBDSuspensionConstraintHandle* InHandle, UObject* InOwner = nullptr);`
- L29 _public function_ `bool IsInitialized() const`
- L30 _public function_ `void SetInitialized()`
- L32 _public prototype_ `static FGeometryParticleHandle* GetParticleHandleFromProxy(IPhysicsProxyBase* ProxyBase);`
- L38 _public prototype_ `void InitializeOnPhysicsThread(FPBDRigidsSolver* InSolver, FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData);`
- L41 _public prototype_ `void PushStateOnGameThread(FDirtyPropertiesManager& Manager, int32 DataIdx, FDirtyChaosProperties& RemoteData);` — Merge to perform a remote sync
- L43 _public prototype_ `void PushStateOnPhysicsThread(FPBDRigidsSolver* InSolver, const FDirtyPropertiesManager& Manager, int32 DataIdx, const FDirtyChaosProperties& RemoteData);`
- L46 _public prototype_ `void DestroyOnGameThread();`
- L47 _public prototype_ `void DestroyOnPhysicsThread(FPBDRigidsSolver* InSolver);`
- L49 _public prototype_ `void UpdateTargetOnPhysicsThread(FPBDRigidsSolver* InSolver, const FVector& TargetPos, const IPhysicsProxyBase* GroundProxy, const FVector& Normal, bool Enabled);`
- L56 _public function_ `FPBDSuspensionConstraintHandle* GetHandle()`
- L61 _public function_ `const FPBDSuspensionConstraintHandle* GetHandle() const`
- L66 _public function_ `virtual void* GetHandleUnsafe() const override`
- L71 _public function_ `void SetHandle(FPBDSuspensionConstraintHandle* InHandle)`
- L76 _public function_ `FSuspensionConstraint* GetConstraint()`
- L81 _public function_ `const FSuspensionConstraint* GetConstraint() const`
- L87 _private member_ `FSuspensionConstraint* Constraint_GT;`
- L88 _private member_ `FPBDSuspensionConstraintHandle* Constraint_PT;`
- L89 _private member_ `bool bInitialized;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/Chaos/Public/PhysicsSolver.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/Chaos/Public/RewindData.h` (Public)


#### struct `Chaos::FBaseRewindHistory`  
`struct FBaseRewindHistory`  
_L47-175_
- desc: Base rewind history used in the rewind data
- L49 _public prototype_ `FORCEINLINE virtual ~FBaseRewindHistory() = default;`
- L52 _public prototype_ `virtual TUniquePtr<FBaseRewindHistory> CreateNew() const = 0;` — Create a new, empty instance with the same concrete type as this object
- L55 _public prototype_ `virtual TUniquePtr<FBaseRewindHistory> Clone() const = 0;` — Create a polymorphic copy of the history
- L58 _public function_ `virtual void Initialize()` — Initialize history
- L61 _public function_ `FORCEINLINE virtual void SetPackageMap(class UPackageMap* InPackageMap)` — Set the package map for serialization
- L64 _public function_ `FORCEINLINE virtual bool HasValidData(const int32 ValidFrame) const` — Check if the history buffer contains an entry for the given frame
- L71 _public function_ `FORCEINLINE virtual int32 CountValidData(const uint32 StartFrame, const uint32 EndFrame, const bool bIncludeUnimportant = true, const bool bIncludeImportant = false)` — Find how many entries are valid in frame range @param StartFrame = Included @param EndFrame = Included @param bIncludeUnimportant = If to include unimportant data entries @param bIncludeImportant = If to include important data entries
- L74 _public function_ `FORCEINLINE virtual int32 CountAlteredData(const bool bIncludeUnimportant = true, const bool bIncludeImportant = false)` — Find how many entries that have been marked as altered, meaning the server has altered the data so that it doesn't match the received data from the client
- L78 _public function_ `FORCEINLINE virtual void SetImportant(const bool bImportant, const int32 Frame = INDEX_NONE)` — Mark frame important or unimportant @param Frame = use INDEX_NONE to set importance on all entries
- L81 _public function_ `FORCEINLINE virtual bool ExtractData(const int32 ExtractFrame, const bool bResetSolver, void* HistoryData, const bool bExactFrame = false)` — Extract data from the history buffer at a given time
- L84 _public function_ `FORCEINLINE virtual void ApplyDataRange(const int32 FromFrame, const int32 ToFrame, void* ActorComponent, const bool bOnlyImportant = false)` — Call ApplyData on each frame data within range
- L87 _public function_ `FORCEINLINE virtual void MergeData(const int32 FromFrame, void* ToData)` — Iterate over and merge data
- L90 _public function_ `FORCEINLINE virtual bool RecordData(const int32 RecordFrame, const void* HistoryData)` — Record data into the history buffer at a given time
- L93 _public function_ `FORCEINLINE virtual bool RecordDataGrowingOrdered(const void* HistoryData)` — Record data in order and allow growing the history
- L96 _public function_ `FORCEINLINE virtual void SetRecordDataIncremental(const bool bInIncremental)` — Set if this history should only allow overriding of data if it has a higher value than current recorded data
- L101 _public function_ `virtual bool CopyAllData(Chaos::FBaseRewindHistory& OutHistory, bool bIncludeUnimportant = true, bool bIncludeImportant = false)` — Copy all data from local history into into @param OutHistory @param bIncludeUnimportant = If to copy unimportant data entries @param bIncludeImportant = If to copy important data entries
- L106 _public function_ `virtual bool CopyAlteredData(Chaos::FBaseRewindHistory& OutHistory, bool bIncludeUnimportant = true, bool bIncludeImportant = false)` — Copy altered data from local history into into @param OutHistory @param bIncludeUnimportant = If to copy unimportant data entries @param bIncludeImportant = If to copy important data entries
- L113 _public function_ `virtual bool CopyData(Chaos::FBaseRewindHistory& OutHistory, const uint32 StartFrame, const uint32 EndFrame, bool bIncludeUnimportant = true, bool bIncludeImportant = false)` — Copy data from local history into @param OutHistory @param StartFrame = Included @param EndFrame = Included @param bIncludeUnimportant = If to copy unimportant data entries @param bIncludeImportant = If to copy important data entries
- L116 _public function_ `virtual bool CopyAllDataGrowingOrdered(Chaos::FBaseRewindHistory& OutHistory)` — Copy all data and record it ordered and growing
- L121 _public prototype_ `virtual TUniquePtr<FBaseRewindHistory> CopyFramesWithOffset(const uint32 StartFrame, const uint32 EndFrame, const int32 FrameOffset) = 0;` — Create a polymorphic copy of only a range of frames, applying the frame offset to the copies @param StartFrame = Included @param EndFrame = Excluded
- L126 _public function_ `virtual int32 ReceiveNewData(FBaseRewindHistory& NewData, const int32 FrameOffset, const bool CompareDataForRewind = false, const bool bImportant = false, int32 TryInjectAtFrame = INDEX_NONE)` — Copy new data (received from the network) into this history Returns frame to resimulate from if @param CompareDataForRewind is set to true and compared data differ enough @param TryInjectAtFrame puts the latest of the received data entries at the specified frame (if there isn't data for that frame yet), used to inject the latest data at the head of the buffer if it's empty
- L129 _public function_ `virtual int32 ReceiveNewData(FBaseRewindHistory& NewData, const int32 FrameOffset, const bool CompareDataForRewind = false, const bool bImportant = false)` — `UE_DEPRECATED(5.7, "Deprecated, use the ReceiveNewData call with parameter InjectAtFrameIfEmpty, pass in nullptr to opt out of implementing a function.")`
- L136 _public function_ `virtual void NetSerialize(FArchive& Ar, UPackageMap* PackageMap)` — `UE_DEPRECATED(5.6, "Deprecated, use the NetSerialize call with parameter that takes a function DataSetupFunction, pass in nullptr to opt out of implementing a function.")` — Serialize the data to or from a network archive
- L139 _public function_ `virtual void NetSerialize(FArchive& Ar, UPackageMap* PackageMap, TUniqueFunction<void(void* Data, const int32 DataIndex)> DataSetupFunction)` — Serialize the data to or from a network archive
- L142 _public function_ `virtual void ValidateDataInHistory(const void* ActorComponent)` — Validate data in history buffer received from clients on the server
- L145 _public function_ `FORCEINLINE virtual void DebugData(const FString& DebugText)` — Print custom string along with values for each entry in history
- L148 _public function_ `FORCEINLINE virtual void DebugData(const Chaos::FBaseRewindHistory& NewData, TArray<int32>& LocalFrames, TArray<int32>& ServerFrames, TArray<int32>& InputFrames)` — Get arrays of frame values for each entry in the history
- L152 _public function_ `FORCEINLINE virtual bool RewindStates(const int32 RewindFrame, const bool bResetSolver)` — `UE_DEPRECATED(5.6, "Deprecated, RewindStates is no longer viable. Any custom states can be applied during IRewindCallback::ProcessInputs_Internal during resimulation. Example FNetworkPhysicsCallback")` — Legacy interface to rewind states
- L156 _public function_ `FORCEINLINE virtual bool ApplyInputs(const int32 ApplyFrame, const bool bResetSolver)` — `UE_DEPRECATED(5.6, "Deprecated, ApplyInputs is no longer viable. Any custom inputs can be applied during IRewindCallback::ProcessInputs_Internal during resimulation. Example FNetworkPhysicsCallback")` — Legacy interface to apply inputs
- L159 _public function_ `virtual const int32 GetLatestFrame() const` — Return the most up to date frame entry in history, returns INDEX_NONE if no frame was found
- L162 _public function_ `virtual const int32 GetEarliestFrame() const` — Return the least up to date frame entry in history, returns INT_MAX if no frame was found
- L165 _public function_ `virtual const int32 GetHistorySize() const` — Return the max size of the history
- L168 _public function_ `virtual const bool HasDataInHistory() const` — Return if history has valid data
- L171 _public function_ `virtual void ResizeDataHistory(const int32 FrameCount, const EAllowShrinking AllowShrinking = EAllowShrinking::Default)` — Resize the history
- L174 _public function_ `virtual void ResetFast()` — Perform a fast reset, marking the data history as reset but not clearing the data or resetting collections

#### struct `Chaos::TDataRewindHistory`  
`template<typename DataType> struct TDataRewindHistory : public FBaseRewindHistory`  
_L179-640_
- inherits: `FBaseRewindHistory`
- desc: Templated data history holding a data buffer
- L181 _public function_ `FORCEINLINE TDataRewindHistory(const int32 FrameCount, const bool bIsHistoryLocal) : bIsLocalHistory(bIsHistoryLocal), bIncremental(false), DataHistory(), LatestFrame(INDEX_NONE), CurrentFrame(0), CurrentIndex(0), NumFrames(FrameCount)`
- L187 _public function_ `FORCEINLINE TDataRewindHistory(const int32 FrameCount) : bIsLocalHistory(false), bIncremental(false), DataHistory(), LatestFrame(INDEX_NONE), CurrentFrame(0), CurrentIndex(0), NumFrames(FrameCount)`
- L192 _public prototype_ `FORCEINLINE virtual ~TDataRewindHistory() = default;`
- L195 _public function_ `virtual void Initialize()` — Initialize history
- L208 _protected function_ `FORCEINLINE int32 ClosestData(const int32 DataFrame, const bool bMinData)` — Get the closest (min/max) valid data from the data frame
- L228 _public function_ `FORCEINLINE virtual bool HasValidData(const int32 ValidFrame) const override` — Check if the history buffer contains an entry for the given frame
- L235 _public function_ `FORCEINLINE virtual bool ExtractData(const int32 ExtractFrame, const bool bResetSolver, void* HistoryData, const bool bExactFrame = false) override` — Extract states at a given time
- L312 _public function_ `FORCEINLINE virtual void MergeData(int32 FromFrame, void* ToData) override`
- L385 _public function_ `FORCEINLINE bool LoadData(const int32 LoadFrame)` — Load the data from the buffer at a specific frame
- L394 _public function_ `FORCEINLINE bool EvalData(const int32 EvalFrame)` — Eval the data from the buffer at a specific frame
- L406 _public function_ `FORCEINLINE virtual bool RecordData(const int32 RecordFrame, const void* HistoryData) override`
- L424 _public function_ `FORCEINLINE virtual bool RecordDataGrowingOrdered(const void* HistoryData) override`
- L459 _public function_ `FORCEINLINE virtual void SetRecordDataIncremental(const bool bInIncremental) override`
- L464 _public function_ `virtual bool CopyAllDataGrowingOrdered(Chaos::FBaseRewindHistory& OutHistory) override`
- L477 _public function_ `DataType& GetCurrentData()` — Current data that is being loaded/recorded
- L479 _public function_ `const DataType& GetCurrentData() const`
- L482 _public function_ `DataType& GetAndLoadEarliestData()` — Returns the earliest data entry and loads it as the current data of the history
- L500 _public function_ `DataType* GetAndLoadNextIncrementalData()` — Returns the next incremental data entry after the CurrentIndex (and loads it as the current data of the history), if there isn't a data entry with a higher LocalFrame value, nullptr is returned
- L518 _public function_ `DataType* GetAndLoadNextData()` — Loads and returns the data on the next index
- L533 _public function_ `FORCEINLINE uint32 NumValidData(const uint32 StartFrame, const uint32 EndFrame) const` — Get the number of valid data in the buffer index range
- L547 _public function_ `TArray<DataType>& GetDataHistory()`
- L548 _public function_ `const TArray<DataType>& GetDataHistoryConst() const`
- L551 _public function_ `virtual const int32 GetLatestFrame() const override` — Return the most up to date frame entry in history
- L557 _public function_ `virtual const int32 GetEarliestFrame() const override` — Return the least up to date frame entry in history
- L573 _public function_ `virtual const int32 GetHistorySize() const` — Return the max size of the history
- L578 _public function_ `virtual const bool HasDataInHistory() const`
- L584 _public function_ `FORCEINLINE void ResizeDataHistory(const int32 FrameCount, const EAllowShrinking AllowShrinking = EAllowShrinking::Default) override` — Resize the history
- L595 _public function_ `FORCEINLINE const uint32 GetFrameIndex(const int32 Frame) const` — Return circular index for given frame value
- L611 _public function_ `FORCEINLINE virtual void ResetFast()`
- L621 _protected member_ `bool bIsLocalHistory;` — Check if the history is on the local/remote client
- L624 _protected member_ `bool bIncremental;` — If this history only record data that is of a higher frame value than previous recorded frame on the same index
- L627 _protected member_ `TArray<DataType> DataHistory;` — Data buffer holding the history
- L630 _protected member_ `int32 LatestFrame;` — The most up to date frame entry in history
- L633 _protected member_ `int32 CurrentFrame;` — Current frame that is being loaded/recorded
- L636 _protected member_ `int32 CurrentIndex;` — Current index that is being loaded/recorded
- L639 _protected member_ `int32 NumFrames = 0;` — Number of frames in data history

#### struct `Chaos::FFrameAndPhase`  
`struct FFrameAndPhase`  
_L642-679_
- L662 _public member_ `int32 Frame : 30;`
- L663 _public member_ `uint32 Phase : 2;`
- L665 _public function_ `bool operator<(const FFrameAndPhase& Other) const`
- L670 _public function_ `bool operator<=(const FFrameAndPhase& Other) const`
- L675 _public function_ `bool operator==(const FFrameAndPhase& Other) const`

#### enum `Chaos::FFrameAndPhase::EParticleHistoryPhase`  
`enum EParticleHistoryPhase : uint8`  
_L644-660_
- L650 _public enumerator_ `PrePushData = 0` — The particle state before PushData, server state update, or any sim callbacks are processed This is the results of the previous frame before any GT modifications are made in this frame This is what the server state should be compared against This is what we rewind to before a resim
- L653 _public enumerator_ `PostPushData` — The particle state after PushData is applied, but before any server state is applied
- L657 _public enumerator_ `PostCallbacks` — The particle state after sim callbacks are applied. This is used to detect desync of particles before simulation itself is run (these desyncs can come from server state or the sim callback itself)
- L659 _public enumerator_ `NumPhases`

#### struct `Chaos::NoEntryInSync`  
`template <typename THandle, typename T, bool bNoEntryIsHead> struct NoEntryInSync`  
_L682-689_
- L684 _public function_ `static bool Helper(const THandle& Handle)`

#### struct `Chaos::NoEntryInSync`  
`template <typename THandle, typename T> struct NoEntryInSync<THandle, T, false>`  
_L692-701_
- L684 _public function_ `static bool Helper(const THandle& Handle)`

#### struct `Chaos::FPropertyInterval`  
`struct FPropertyInterval`  
_L703-707_
- L705 _public member_ `FPropertyIdx Ref;`
- L706 _public member_ `FFrameAndPhase FrameAndPhase;`

#### class `Chaos::TParticlePropertyBuffer`  
`template <typename T, EChaosProperty PropName, bool bNoEntryIsHead = true> class TParticlePropertyBuffer`  
_L721-1033_
- L724 _public function_ `explicit TParticlePropertyBuffer(int32 InCapacity) : Next(0) , NumValid(0) , Capacity(InCapacity)`
- L731 _public function_ `TParticlePropertyBuffer(TParticlePropertyBuffer<T, PropName>&& Other) : Next(Other.Next) , NumValid(Other.NumValid) , Capacity(Other.Capacity) , Buffer(MoveTemp(Other.Buffer))`
- L741 _public prototype_ `TParticlePropertyBuffer(const TParticlePropertyBuffer<T, PropName>& Other) = delete;`
- L743 _public function_ `~TParticlePropertyBuffer()`
- L750 _public function_ `T& WriteAccessMonotonic(const FFrameAndPhase FrameAndPhase, FDirtyPropertiesPool& Manager)` — Gets access into buffer in monotonically increasing FrameAndPhase order: x_{n+1} > x_n
- L757 _public function_ `T* WriteAccessNonDecreasing(const FFrameAndPhase FrameAndPhase, FDirtyPropertiesPool& Manager)` — Gets access into buffer in non-decreasing FrameAndPhase order: x_{n+1} >= x_n If x_{n+1} == x_n we return null to inform the user (usefull when a single phase can have multiple writes)
- L763 _public function_ `const T* Read(const FFrameAndPhase FrameAndPhase, const FDirtyPropertiesPool& Manager) const` — Searches in reverse order for interval that contains FrameAndPhase
- L770 _public function_ `const bool GetHeadFrameAndPhase(FFrameAndPhase& OutFrameAndPhase) const` — Get the FrameAndPhase of the head / last entry
- L782 _public function_ `void Release(FDirtyPropertiesPool& Manager)` — Releases data back into the pool
- L794 _public function_ `void Reset()`
- L799 _public function_ `bool IsEmpty() const`
- L804 _public function_ `void ClearEntryAndFuture(const FFrameAndPhase FrameAndPhase)`
- L821 _public function_ `void ExtractBufferState(int32& ValidCount, int32& NextIterator) const`
- L827 _public function_ `void RestoreBufferState(const int32& ValidCount, const int32& NextIterator)`
- L833 _public function_ `bool IsClean(const FFrameAndPhase FrameAndPhase) const`
- L839 _public function_ `template <typename THandle> bool IsInSync(const THandle& Handle, const FFrameAndPhase FrameAndPhase, const FDirtyPropertiesPool& Pool) const`
- L851 _public function_ `T& Insert(const FFrameAndPhase FrameAndPhase, FDirtyPropertiesPool& Manager)`
- L913 _private function_ `const int32 FindIdx(const FFrameAndPhase FrameAndPhase) const`
- L948 _private function_ `TPropertyPool<T>& GetPool(FDirtyPropertiesPool& Manager)`
- L949 _private function_ `const TPropertyPool<T>& GetPool(const FDirtyPropertiesPool& Manager) const`
- L956 _private function_ `template <bool bEnsureMonotonic> T* WriteAccessImp(const FFrameAndPhase FrameAndPhase, FDirtyPropertiesPool& Manager)` — Gets access into buffer in FrameAndPhase order. It's assumed FrameAndPhase is monotonically increasing: x_{n+1} > x_n If bEnsureMonotonic is true we will always return a valid access (unless assert fires) If bEnsureMonotonic is false we will ensure x_{n+1} >= x_n. If x_{n+1} == x_n we return null to inform the user (can be useful when multiple writes happen in same phase)
- L1006 _private function_ `void ValidateOrder()`
- L1029 _private member_ `int32 Next;`
- L1030 _private member_ `int32 NumValid;`
- L1031 _private member_ `int32 Capacity;`
- L1032 _private member_ `TArray<FPropertyInterval> Buffer;`

#### enum `Chaos::EDesyncResult`  
`enum EDesyncResult`  
_L1036-1041_
- L1038 _public enumerator_ `InSync` — both have entries and are identical, or both have no entries
- L1039 _public enumerator_ `Desync` — both have entries but they are different
- L1040 _public enumerator_ `NeedInfo` — one of the entries is missing. Need more context to determine whether desynced

#### struct `Chaos::FDirtyPropData`  
`struct FDirtyPropData`  
_L1044-1051_
- desc: Wraps FDirtyPropertiesManager and its DataIdx to avoid confusion between Source and offset Dest indices
- L1046 _public function_ `FDirtyPropData(FDirtyPropertiesManager* InManager, int32 InDataIdx) : Ptr(InManager), DataIdx(InDataIdx)`
- L1049 _public member_ `FDirtyPropertiesManager* Ptr;`
- L1050 _public member_ `int32 DataIdx;`

#### struct `Chaos::FConstDirtyPropData`  
`struct FConstDirtyPropData`  
_L1053-1060_
- L1055 _public function_ `FConstDirtyPropData(const FDirtyPropertiesManager* InManager, int32 InDataIdx) : Ptr(InManager), DataIdx(InDataIdx)`
- L1058 _public member_ `const FDirtyPropertiesManager* Ptr;`
- L1059 _public member_ `int32 DataIdx;`

#### class `Chaos::TPerShapeDataStateProperty`  
`template <typename T, EShapeProperty PropName> class TPerShapeDataStateProperty`  
_L1063-1086_
- L1066 _public function_ `const T& Read() const`
- L1072 _public function_ `void Write(const T& InVal)`
- L1078 _public function_ `bool IsSet() const`
- L1084 _private member_ `T Val;`
- L1085 _private member_ `bool bSet = false;`

#### struct `Chaos::FPerShapeDataStateBase`  
`struct FPerShapeDataStateBase`  
_L1088-1108_
- L1090 _public member_ `TPerShapeDataStateProperty<FCollisionData, EShapeProperty::CollisionData> CollisionData;`
- L1091 _public member_ `TPerShapeDataStateProperty<FMaterialData, EShapeProperty::Materials> MaterialData;`
- L1095 _public function_ `template <typename TParticle> static Chaos::Filter::FCombinedShapeFilterData GetShapeCombinedFilterData(const FPerShapeDataStateBase* State, const TParticle& Particle, int32 ShapeIdx)` — helper functions for shape API
- L1102 _public function_ `static FCollisionFilterData GetQueryData(const FPerShapeDataStateBase* State, const TParticle& Particle, int32 ShapeIdx)` — `UE_DEPRECATED(5.8, "This is unused and will be removed. Use GetCombinedShapeFilterData instead")`

#### class `Chaos::FPerShapeDataState`  
`class FPerShapeDataState`  
_L1110-1136_
- L1113 _public function_ `FPerShapeDataState(const FPerShapeDataStateBase* InState, const FGeometryParticleHandle& InParticle, const int32 InShapeIdx) : State(InState) , Particle(InParticle) , ShapeIdx(InShapeIdx)`
- L1120 _public function_ `const Chaos::Filter::FCombinedShapeFilterData GetCombinedShapeFilterData() const`
- L1129 _public function_ `FCollisionFilterData GetQueryData() const` — `UE_DEPRECATED(5.8, "This is unused and will be removed. Use GetCombinedShapeFilterData instead")`
- L1132 _private member_ `const FPerShapeDataStateBase* State;`
- L1133 _private member_ `const FGeometryParticleHandle& Particle;`
- L1134 _private member_ `const int32 ShapeIdx;`

#### struct `Chaos::FShapesArrayStateBase`  
`struct FShapesArrayStateBase`  
_L1138-1152_
- L1140 _public member_ `TArray<FPerShapeDataStateBase> PerShapeData;`
- L1142 _public function_ `FPerShapeDataStateBase& FindOrAdd(const int32 ShapeIdx)`

#### class `Chaos::TShapesArrayState`  
`template <typename TParticle> class TShapesArrayState`  
_L1215-1227_
- L1218 _public function_ `TShapesArrayState(const TParticle& InParticle, const FShapesArrayStateBase* InState) : Particle(InParticle) , State(InState)`
- L1223 _public function_ `FPerShapeDataState operator[](const int32 ShapeIdx) const`
- L1225 _private member_ `const TParticle& Particle;`
- L1226 _private member_ `const FShapesArrayStateBase* State;`

#### struct `Chaos::FGeometryParticleStateBase`  
`struct FGeometryParticleStateBase`  
_L1274-1412_
- L1278 _public function_ `explicit FGeometryParticleStateBase(int32 NumFrames) : ParticlePositionRotation(ComputeCircularSize(NumFrames)) , NonFrequentData(ComputeCircularSize(NumFrames)) , Velocities(ComputeCircularSize(NumFrames)) , Dynamics(ComputeCircularSize(NumFrames)) , DynamicsMisc(ComputeCircularSize(NumFrames)) , MassProps(ComputeCircularSize(NumFrames)) , KinematicTarget(ComputeCircularSize(NumFrames)) , TargetPositions(ComputeCircularSize(NumFrames)) , TargetVelocities(ComputeCircularSize(NumFrames)) , TargetStates(ComputeCircularSize(NumFrames))` — `UE_DEPRECATED(5.6, "Use the constructor that takes a @param bCacheOnePhase")`
- L1292 _public function_ `explicit FGeometryParticleStateBase(int32 NumFrames, bool bCacheOnePhase) : ParticlePositionRotation(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , NonFrequentData(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , Velocities(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , Dynamics(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , DynamicsMisc(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , MassProps(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , KinematicTarget(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , TargetPositions(NumFrames) , TargetVelocities(NumFrames) , TargetStates(NumFrames)`
- L1306 _public prototype_ `FGeometryParticleStateBase(const FGeometryParticleStateBase& Other) = delete;`
- L1307 _public prototype_ `FGeometryParticleStateBase(FGeometryParticleStateBase&& Other) = default;`
- L1308 _public prototype_ `~FGeometryParticleStateBase() = default;`
- L1311 _public prototype_ `FGeometryParticleStateBase() = delete;` — Can be removed when Deprecations are removed
- L1313 _public prototype_ `FGeometryParticleStateBase& operator=(const FGeometryParticleStateBase&) = delete;` — Can be removed when Deprecations are removed
- L1315 _public prototype_ `FGeometryParticleStateBase& operator=(FGeometryParticleStateBase&&) = delete;` — Can be removed when Deprecations are removed
- L1318 _public function_ `void Release(FDirtyPropertiesPool& Manager)`
- L1332 _public function_ `void Reset()`
- L1346 _public function_ `void ClearEntryAndFuture(const FFrameAndPhase FrameAndPhase)`
- L1357 _public function_ `void ExtractHistoryState(int32& PositionValidCount, int32& VelocityValidCount, int32& PositionNextIterator, int32& VelocityNextIterator) const`
- L1363 _public function_ `void RestoreHistoryState(const int32& PositionValidCount, const int32& VelocityValidCount, const int32& PositionNextIterator, const int32& VelocityNextIterator)`
- L1369 _public function_ `bool IsClean(const FFrameAndPhase FrameAndPhase) const`
- L1374 _public function_ `bool IsCleanExcludingDynamics(const FFrameAndPhase FrameAndPhase) const`
- L1385 _public prototype_ `template <bool bSkipDynamics = false> bool IsInSync(const FGeometryParticleHandle& Handle, const FFrameAndPhase FrameAndPhase, const FDirtyPropertiesPool& Pool) const;`
- L1388 _public function_ `template <typename TParticle> static TShapesArrayState<TParticle> ShapesArray(const FGeometryParticleStateBase* State, const TParticle& Particle)`
- L1393 _public prototype_ `void SyncSimWritablePropsFromSim(FDirtyPropData Manager,const TPBDRigidParticleHandle<FReal,3>& Rigid);`
- L1394 _public prototype_ `void SyncDirtyDynamics(FDirtyPropData& DestManager,const FDirtyChaosProperties& Dirty,const FConstDirtyPropData& SrcManager);`
- L1399 _public member_ `TParticlePropertyBuffer<FParticlePositionRotation,EChaosProperty::XR> ParticlePositionRotation;` — Setting bNoEntryIsHead = false in TParticlePropertyBuffer allows us to not cache the data each frame and it will only return entries for a specific frame when fetched For example, we don't need to cache a kinematic target that is set to None, instead we only cache when it's not set to None and if we don't have an entry for a specific frame we can expect it to be a None kinematic target. Note that bNoEntryIsHead = true (which is default) will return the latest cached entry closest to the requested frame and phase without returning an earlier entry.
- L1400 _public member_ `TParticlePropertyBuffer<FParticleNonFrequentData,EChaosProperty::NonFrequentData> NonFrequentData;`
- L1401 _public member_ `TParticlePropertyBuffer<FParticleVelocities,EChaosProperty::Velocities> Velocities;`
- L1402 _public member_ `TParticlePropertyBuffer<FParticleDynamics,EChaosProperty::Dynamics, false> Dynamics;`
- L1403 _public member_ `TParticlePropertyBuffer<FParticleDynamicMisc,EChaosProperty::DynamicMisc> DynamicsMisc;`
- L1404 _public member_ `TParticlePropertyBuffer<FParticleMassProps,EChaosProperty::MassProps> MassProps;`
- L1405 _public member_ `TParticlePropertyBuffer<FKinematicTarget, EChaosProperty::KinematicTarget, false> KinematicTarget;`
- L1407 _public member_ `TParticlePropertyBuffer<FParticlePositionRotation, EChaosProperty::XR, false> TargetPositions;`
- L1408 _public member_ `TParticlePropertyBuffer<FParticleVelocities, EChaosProperty::Velocities, false> TargetVelocities;`
- L1409 _public member_ `TParticlePropertyBuffer<FParticleDynamicMisc, EChaosProperty::DynamicMisc, false> TargetStates;`
- L1411 _public member_ `FShapesArrayStateBase ShapesArrayState;`

#### struct `Chaos::FParticleSimpleState`  
`struct FParticleSimpleState`  
_L1414-1444_
- L1417 _private member_ `FGeometryParticleHandle* HandlePtr;`
- L1418 _private member_ `FVec3 X = { 0,0,0 };`
- L1419 _private member_ `FQuat R = FQuat::Identity;`
- L1420 _private member_ `FVec3 V = { 0,0,0 };`
- L1421 _private member_ `FVec3 W = { 0,0,0 };`
- L1424 _public function_ `FParticleSimpleState(FGeometryParticleHandle& InHandle) : HandlePtr(&InHandle)`
- L1428 _public function_ `void CacheXR(FVec3 InX, FQuat InR)`
- L1433 _public function_ `void CacheVW(FVec3 InV, FVec3 InW)`
- L1439 _public function_ `FGeometryParticleHandle* GetObjectPtr() const`
- L1440 _public function_ `FVec3 GetX() const`
- L1441 _public function_ `FQuat GetR() const`
- L1442 _public function_ `FVec3 GetV() const`
- L1443 _public function_ `FVec3 GetW() const`

#### class `Chaos::FGeometryParticleState`  
`class FGeometryParticleState`  
_L1446-1569_
- L1450 _public function_ `FGeometryParticleState(const FGeometryParticleHandle& InParticle, const FDirtyPropertiesPool& InPool) : Particle(InParticle) , Pool(InPool) , FrameAndPhase`
- L1457 _public function_ `FGeometryParticleState(const FGeometryParticleStateBase* InState, const FGeometryParticleHandle& InParticle, const FDirtyPropertiesPool& InPool, const FFrameAndPhase InFrameAndPhase) : Particle(InParticle) , Pool(InPool) , State(InState) , FrameAndPhase(InFrameAndPhase)`
- L1465 _public function_ `REWIND_PARTICLE_STATIC_PROPERTY(ParticlePositionRotation, GetX) REWIND_PARTICLE_STATIC_PROPERTY(ParticlePositionRotation, GetR) REWIND_PARTICLE_KINEMATIC_PROPERTY(Velocities, GetV) REWIND_PARTICLE_KINEMATIC_PROPERTY(Velocities, GetW) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, LinearEtherDrag) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, AngularEtherDrag) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, MaxLinearSpeedSq) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, MaxAngularSpeedSq) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, InitialOverlapDepenetrationVelocity) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, SleepThresholdMultiplier) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, ObjectState) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, CollisionGroup) REWIND_PARTICLE_RIGID_PROPERTY(DynamicsMisc, ControlFlags) REWIND_PARTICLE_RIGID_PROPERTY(MassProps, CenterOfMass) REWIND_PARTICLE_RIGID_PROPERTY(MassProps, RotationOfMass) REWIND_PARTICLE_RIGID_PROPERTY(MassProps, I) REWIND_PARTICLE_RIGID_PROPERTY(MassProps, M) REWIND_PARTICLE_RIGID_PROPERTY(MassProps, InvM) REWIND_PARTICLE_STATIC_PROPERTY(NonFrequentData, GetGeometry) REWIND_PARTICLE_STATIC_PROPERTY(NonFrequentData, UniqueIdx) REWIND_PARTICLE_STATIC_PROPERTY(NonFrequentData, SpatialIdx) #if CHAOS_DEBUG_NAME REWIND_PARTICLE_STATIC_PROPERTY(NonFrequentData, DebugName) #endif REWIND_PARTICLE_ZERO_PROPERTY(Dynamics, Acceleration) REWIND_PARTICLE_ZERO_PROPERTY(Dynamics, AngularAcceleration) REWIND_PARTICLE_ZERO_PROPERTY(Dynamics, Linea ...`
- L1504 _public function_ `const FGeometryParticleHandle& GetHandle() const`
- L1509 _public function_ `void SetState(const FGeometryParticleStateBase* InState)`
- L1514 _public function_ `FString ToString() const`
- L1562 _private member_ `const FGeometryParticleHandle& Particle;`
- L1563 _private member_ `const FDirtyPropertiesPool& Pool;`
- L1564 _private member_ `const FGeometryParticleStateBase* State = nullptr;`
- L1565 _private member_ `const FFrameAndPhase FrameAndPhase;`
- L1567 _private member_ `static FVec3 ZeroVector;`

#### struct `Chaos::FJointStateBase`  
`struct FJointStateBase`  
_L1572-1619_
- L1575 _public function_ `explicit FJointStateBase(int32 NumFrames) : JointSettings(ComputeCircularSize(NumFrames)) , JointProxies(ComputeCircularSize(NumFrames))` — `UE_DEPRECATED(5.6, "Use the constructor that takes a @param bCacheOnePhase")`
- L1581 _public function_ `explicit FJointStateBase(int32 NumFrames, bool bCacheOnePhase) : JointSettings(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames)) , JointProxies(bCacheOnePhase ? NumFrames : ComputeCircularSize(NumFrames))`
- L1587 _public prototype_ `FJointStateBase(const FJointStateBase& Other) = delete;`
- L1588 _public prototype_ `FJointStateBase(FJointStateBase&& Other) = default;`
- L1589 _public prototype_ `~FJointStateBase() = default;`
- L1591 _public function_ `void Release(FDirtyPropertiesPool& Manager)`
- L1597 _public function_ `void Reset()`
- L1603 _public function_ `void ClearEntryAndFuture(const FFrameAndPhase FrameAndPhase)`
- L1609 _public function_ `bool IsClean(const FFrameAndPhase FrameAndPhase) const`
- L1615 _public prototype_ `template <bool bSkipDynamics> bool IsInSync(const FPBDJointConstraintHandle& Handle, const FFrameAndPhase FrameAndPhase, const FDirtyPropertiesPool& Pool) const;`
- L1617 _public member_ `TParticlePropertyBuffer<FPBDJointSettings, EChaosProperty::JointSettings> JointSettings;`
- L1618 _public member_ `TParticlePropertyBuffer<FProxyBasePairProperty, EChaosProperty::JointParticleProxies> JointProxies;`

#### class `Chaos::FJointState`  
`class FJointState`  
_L1621-1661_
- L1624 _public function_ `FJointState(const FPBDJointConstraintHandle& InJoint, const FDirtyPropertiesPool& InPool) : Head(InJoint) , Pool(InPool)`
- L1630 _public function_ `FJointState(const FJointStateBase* InState, const FPBDJointConstraintHandle& InJoint, const FDirtyPropertiesPool& InPool, const FFrameAndPhase InFrameAndPhase) : Head(InJoint) , Pool(InPool) , State(InState) , FrameAndPhase(InFrameAndPhase)`
- L1644 _public function_ `FString ToString() const`
- L1657 _private member_ `const FPBDJointConstraintHandle& Head;`
- L1658 _private member_ `const FDirtyPropertiesPool& Pool;`
- L1659 _private member_ `const FJointStateBase* State = nullptr;`
- L1660 _private member_ `const FFrameAndPhase FrameAndPhase = { 0,0 };`

#### class `Chaos::TDirtyObjects`  
`template <typename TVal> class TDirtyObjects`  
_L1671-1767_
- L1674 _public typedef_ `using TKey = decltype(ConstifyHelper( ((TVal*)0)->GetObjectPtr() ));`
- L1678 _public function_ `TVal& Add(const TKey Key, TVal&& Val)`
- L1693 _public function_ `const TVal& FindChecked(const TKey Key) const`
- L1699 _public function_ `TVal& FindChecked(const TKey Key)`
- L1705 _public function_ `const TVal* Find(const TKey Key) const`
- L1715 _public function_ `TVal* Find(const TKey Key)`
- L1725 _public function_ `void Remove(const TKey Key, const EAllowShrinking AllowShrinking)`
- L1742 _public function_ `void Shrink()`
- L1747 _public function_ `void Reset()`
- L1753 _public function_ `int32 Num() const`
- L1755 _public function_ `auto begin()`
- L1756 _public function_ `auto end()`
- L1758 _public function_ `auto cbegin() const`
- L1759 _public function_ `auto cend() const`
- L1761 _public function_ `const TVal& GetDenseAt(const int32 Idx) const`
- L1762 _public function_ `TVal& GetDenseAt(const int32 Idx)`
- L1765 _private member_ `TMap<TKey, int32> KeyToIdx;`
- L1766 _private member_ `TArray<TVal> DenseVals;`

#### class `Chaos::FRewindData`  
`class FRewindData`  
_L1775-2385_
- L1778 _public prototype_ `FRewindData(FPBDRigidsSolver* InSolver, int32 NumFrames, bool InRewindDataOptimization, int32 InCurrentFrame);`
- L1779 _public prototype_ `FRewindData(FPBDRigidsSolver* InSolver, int32 NumFrames, int32 InCurrentFrame);`
- L1781 _public prototype_ `void Init(FPBDRigidsSolver* InSolver, int32 NumFrames, bool InRewindDataOptimization, int32 InCurrentFrame);`
- L1782 _public prototype_ `void Init(FPBDRigidsSolver* InSolver, int32 NumFrames, int32 InCurrentFrame);`
- L1785 _private prototype_ `void RegisterEvolutionCallbacks();`
- L1788 _public member_ `FOnRewindDataResizeInternal RewindDataResize;`
- L1790 _public function_ `int32 Capacity() const`
- L1791 _public function_ `int32 CurrentFrame() const`
- L1792 _public function_ `int32 GetLatestFrame() const`
- L1793 _public function_ `int32 GetFramesSaved() const`
- L1796 _public prototype_ `void ResizeRewindDataIfNeeded();` — Check if we need to resize the rewind data
- L1798 _public function_ `FReal GetDeltaTimeForFrame(int32 Frame) const`
- L1804 _public function_ `void RemoveObject(const FGeometryParticleHandle* Particle, const EAllowShrinking AllowShrinking=EAllowShrinking::Default)`
- L1811 _public function_ `void RemoveObject(const FPBDJointConstraintHandle* Joint, const EAllowShrinking AllowShrinking = EAllowShrinking::Default)`
- L1816 _public prototype_ `int32 GetEarliestFrame_Internal() const;`
- L1819 _public prototype_ `void ExtendHistoryWithFrame(const int32 Frame);` — Extend the current history size to be sure to include the given frame
- L1822 _public prototype_ `void ClearPhaseAndFuture(FGeometryParticleHandle& Handle, int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase);` — Clear all the simulation history after Frame
- L1825 _public prototype_ `void PushStateAtFrame(FGeometryParticleHandle& Handle, int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase, const FVector& Position, const FQuat& Quaternion, const FVector& LinVelocity, const FVector& AngVelocity, const bool bShouldSleep);` — Push a physics state in the rewind data at specified frame
- L1828 _public prototype_ `void SetTargetStateAtFrame(FGeometryParticleHandle& Handle, const int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase, const FVector& Position, const FQuat& Quaternion, const FVector& LinVelocity, const FVector& AngVelocity, const bool bShouldSleep);`
- L1831 _public prototype_ `void ForceResimAsFollower(FGeometryParticleHandle* Handle, bool bForceResim);`
- L1833 _public prototype_ `int32 GetLatestReceivedTargetStateFrame(FGeometryParticleHandle& Handle) const;`
- L1836 _public function_ `void ExtractHistoryState(FGeometryParticleHandle& Handle, int32& PositionValidCount, int32& VelocityValidCount, int32& PositionNextIterator, int32& VelocityNextIterator)` — Extract some history information before cleaning/pushing state
- L1843 _public function_ `void RestoreHistoryState(FGeometryParticleHandle& Handle, const int32& PositionValidCount, const int32& VelocityValidCount, const int32& PositionNextIterator, const int32& VelocityNextIterator)` — Restore some history information after cleaning/pushing state
- L1850 _public prototype_ `FGeometryParticleState GetPastStateAtFrame(const FGeometryParticleHandle& Handle, int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase = FFrameAndPhase::EParticleHistoryPhase::PostPushData) const;` — Query the state of particles from the past. Can only be used when not already resimming
- L1853 _public prototype_ `FJointState GetPastJointStateAtFrame(const FPBDJointConstraintHandle& Handle, int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase = FFrameAndPhase::EParticleHistoryPhase::PostPushData) const;` — Query the state of joints from the past. Can only be used when not already resimming
- L1855 _public function_ `IResimCacheBase* GetCurrentStepResimCache() const`
- L1860 _public prototype_ `void DumpHistory_Internal(const int32 FramePrintOffset, const FString& Filename = FString("Dump`
- L1863 _public prototype_ `bool GetUseCollisionResimCache() const;` — Check if a resim cache based on IResimCacheBase (FEvolutionResimCache by default) is being used. Read FPhysicsSolverBase.SetUseCollisionResimCache() for more info.
- L1867 _public function_ `template <typename CreateCache> void AdvanceFrame(FReal DeltaTime, const CreateCache& CreateCacheFunc)` — Called just before physics is solved
- L1904 _public prototype_ `void FinishFrame();`
- L1908 _public prototype_ `void SkipFrames(int32 NumFramesToSkip);` — Advance the frame counter without running desync checks or other per-frame logic. Used during adaptive resim coalescing to skip intermediate frames.
- L1910 _public function_ `bool IsResim() const`
- L1915 _public function_ `bool IsFinalResim() const`
- L1921 _public function_ `int32 GetNumDirtyParticles() const` — Number of particles that we're currently storing history for
- L1924 _public prototype_ `void PushGTDirtyData(const FDirtyPropertiesManager& SrcManager,const int32 SrcDataIdx,const FDirtyProxy& Dirty, const FShapeDirtyData* ShapeDirtyData);` — Called just before Proxy::PushToPhysicsState is called
- L1927 _public prototype_ `void PushPTDirtyData(TPBDRigidParticleHandle<FReal,3>& Rigid,const int32 SrcDataIdx);` — Called post solve but just before PQ are applied to XR
- L1930 _public prototype_ `void MarkDirtyFromPT(FGeometryParticleHandle& Handle);` — Call this to mark specific particle as dirty and cache its current data, expected to be called at the start of OnPreSimulate_Internal, it caches data in FFrameAndPhase::PostPushData
- L1933 _public prototype_ `void MarkDirtyJointFromPT(FPBDJointConstraintHandle& Handle);` — Call this to mark specific joint as dirty and cache its current data, expected to be called at the start of OnPreSimulate_Internal, it caches data in FFrameAndPhase::PostPushData
- L1935 _public prototype_ `void SpawnProxyIfNeeded(FSingleParticlePhysicsProxy& Proxy);`
- L1937 _public prototype_ `void DisableInHistoryFromFrame(IPhysicsProxyBase* PhysicsProxy, int32 DisableParticleOnFrame = INDEX_NONE);`
- L1940 _public function_ `void AddInputHistory(const TSharedPtr<FBaseRewindHistory>& InputHistory)` — Add input history to the rewind data for future use while resimulating
- L1946 _public function_ `void RemoveInputHistory(const TSharedPtr<FBaseRewindHistory>& InputHistory)` — Remove input history from the rewind data
- L1952 _public function_ `void AddInputHistory(const TSharedPtr<FBaseRewindHistory>& InputHistory, Chaos::FGeometryParticleHandle* Particle)` — Add input history for particle to the rewind data
- L1962 _public function_ `void RemoveInputHistory(const TSharedPtr<FBaseRewindHistory>& InputHistory, Chaos::FGeometryParticleHandle* Particle)` — Remove input history for particle from the rewind data
- L1972 _public function_ `void AddStateHistory(const TSharedPtr<FBaseRewindHistory>& StateHistory)` — Add state history to the rewind data for future use while rewinding
- L1978 _public function_ `void RemoveStateHistory(const TSharedPtr<FBaseRewindHistory>& StateHistory)` — Remove state history from the rewind data
- L1984 _public function_ `void AddStateHistory(const TSharedPtr<FBaseRewindHistory>& StateHistory, Chaos::FGeometryParticleHandle* Particle)` — Add state history for particle to the rewind data
- L1994 _public function_ `void RemoveStateHistory(const TSharedPtr<FBaseRewindHistory>& StateHistory, Chaos::FGeometryParticleHandle* Particle)` — Remove state history for particle from the rewind data
- L2005 _public prototype_ `void ApplyInputs(const int32 ApplyFrame, const bool bResetSolver);` — `UE_DEPRECATED(5.6, "Deprecated, ApplyInputs is no longer viable. Any custom states can be applied during IRewindCallback::ProcessInputs_Internal during resimulation. Example FNetworkPhysicsCallback")` — Apply inputs for specified frame from rewind data
- L2009 _public prototype_ `void RewindStates(const int32 RewindFrame, const bool bResetSolver);` — `UE_DEPRECATED(5.6, "Deprecated, RewindStates is no longer viable. Any custom states can be applied during IRewindCallback::ProcessInputs_Internal during resimulation. Example FNetworkPhysicsCallback")` — Rewind to state for a specified frame from rewind data
- L2012 _public prototype_ `void BufferPhysicsResults(TMap<const IPhysicsProxyBase*, struct FDirtyRigidParticleReplicationErrorData>& DirtyRigidErrors);` — Move post-resim error correction data from RewindData to FPullPhysicsData for marshaling to GT where it can be used in render interpolation
- L2015 _public function_ `const FPBDRigidsSolver* GetSolver() const` — Return the rewind data solver
- L2018 _public prototype_ `int32 FindValidResimFrame(const int32 RequestedFrame);` — Find the first previous valid frame having received physics target from the server
- L2021 _public function_ `const int32 GetResimFrame() const` — Get and set the frame we resimulate from
- L2022 _public function_ `void SetResimFrame(int32 Frame)`
- L2023 _public function_ `const bool IsResimCooldown() const`
- L2026 _public prototype_ `void EndResim();` — Called at the end of resim
- L2029 _public function_ `bool IsFrameWithinRewindHistory(int32 Frame) const` — Check if a frame number is within the currently allowed rewind span
- L2033 _public prototype_ `void RequestResimulation(int32 RequestedFrame, Chaos::FGeometryParticleHandle* Particle = nullptr);` — Request a resimulation by setting a requested frame to rewind to @param Particle can be used to mark a specific particle as the one triggering the resimulation
- L2036 _public prototype_ `void BlockResim();` — This blocks any future resimulation to rewind back past the frame this is called on
- L2039 _public function_ `const int32 GetBlockedResimFrame() const` — Get the latest frame resim has been blocked from rewinding past
- L2043 _public function_ `void SetRewindDataOptimization(bool InRewindDataOptimization)` — Set if RewindData optimizations should be enabled or not. Effect: Only alter the minimum required properties during a resim for particles not marked for FullResim
- L2048 _public prototype_ `const int32 CompareTargetsToLastFrame();` — Check if we have received targets already for the last frame simulated, if so compare those with the result of the simulation and if they desync return the frame value to request a rewind for to correct the desync NOTE: This only happens when the client has desynced and is behind the server, so we receive server states for frames not yet simulated
- L2051 _public prototype_ `void GetPreResimState(Chaos::FGeometryParticleHandle* GeometryParticle, FParticleSimpleState*& OutPreResimState);` — Get cached pre resimulation state for particle, if there is one
- L2054 _public prototype_ `void RemovePreResimState(Chaos::FGeometryParticleHandle* GeometryParticle);` — Remove cached pre resimulation state for particle
- L2056 _public prototype_ `static bool CheckVectorThreshold(FVec3 A, FVec3 B, float Threshold);`
- L2057 _public prototype_ `static bool CheckQuaternionThreshold(FQuat A, FQuat B, float ThresholdDegrees);`
- L2062 _private prototype_ `void AdvanceFrameImp(IResimCacheBase* ResimCache);`
- L2065 _private prototype_ `void ProcessDirtyPTParticles(const TParticleView<TPBDRigidParticles<FReal, 3>>& DirtyPTParticles);` — Called post-solve from the evolution with all particles that are dirty after solving physics. Note: Before PQ are applied to XR
- L2068 _private prototype_ `void ProcessDirtyKinematicTargets(const TParticleView<TPBDRigidParticles<FReal, 3>>& ActiveKinematicParticles);` — Called during integration just before KinematicTargets are processed with all active kinematic particles
- L2071 _private prototype_ `void CacheKinematicTarget(TPBDRigidParticleHandle<FReal, 3>& Rigid);` — Called during integration just before KinematicTargets are processed
- L2075 _private prototype_ `void CacheDirtyParticleData(FGeometryParticleHandle* Geometry, const FFrameAndPhase::EParticleHistoryPhase& CurrentPhase, const bool& bDirty);` — Called to cache a particles current state into a specified phase of the current frame @param bDirty will mark the particle as dirty in the rewind history which will continue to cache it for FRewindData::Capacity() amount of frames
- L2079 _private prototype_ `void CacheDirtyJointData(FPBDJointConstraintHandle* Joint, const FFrameAndPhase::EParticleHistoryPhase& CurrentPhase, const bool& bDirty);` — Called to cache a joints current state into a specified phase of the current frame @param bDirty will mark the joint as dirty in the rewind history which will continue to cache it for FRewindData::Capacity() amount of frames
- L2083 _private prototype_ `void CacheCurrentDirtyData(const FFrameAndPhase::EParticleHistoryPhase& CurrentPhase);` — Caches data for all particles and joints marked dirty in RewindData @param CurrentPhase Data gets cached under this phase for the current frame, be sure to call this from the corresponding phase during physics
- L2170 _private typedef_ `using FDirtyParticleInfo = TDirtyObjectInfo<FGeometryParticleStateBase, FGeometryParticleHandle>;`
- L2171 _private typedef_ `using FDirtyJointInfo = TDirtyObjectInfo<FJointStateBase, FPBDJointConstraintHandle>;`
- L2196 _private function_ `template <typename TDirtyObjs, typename TObj> auto* FindDirtyObjImp(TDirtyObjs& DirtyObjs, TObj& Handle)`
- L2202 _private function_ `template <typename TDirtyObjs, typename TObj> const auto* FindDirtyObjImp(const TDirtyObjs& DirtyObjs, TObj& Handle) const`
- L2207 _private function_ `FDirtyParticleInfo* FindDirtyObj(const FGeometryParticleHandle& Handle)`
- L2212 _private function_ `FDirtyJointInfo* FindDirtyObj(const FPBDJointConstraintHandle& Handle)`
- L2217 _private function_ `const FDirtyParticleInfo* FindDirtyObj(const FGeometryParticleHandle& Handle) const`
- L2222 _private function_ `const FDirtyJointInfo* FindDirtyObj(const FPBDJointConstraintHandle& Handle) const`
- L2228 _private function_ `template <typename TDirtyObjs, typename TObj> auto& FindOrAddDirtyObjImp(TDirtyObjs & DirtyObjs, TObj & Handle, const int32 InitializedOnFrame = INDEX_NONE)`
- L2241 _private function_ `FDirtyParticleInfo& FindOrAddDirtyObj(FGeometryParticleHandle& Handle, const int32 InitializedOnFrame = INDEX_NONE)`
- L2246 _private function_ `FDirtyJointInfo& FindOrAddDirtyObj(FPBDJointConstraintHandle& Handle, const int32 InitializedOnFrame = INDEX_NONE)`
- L2252 _private function_ `template <typename TObjState, typename TDirtyObjs, typename TObj> auto GetPastStateAtFrameImp(const TDirtyObjs& DirtyObjs, const TObj& Handle, int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase) const`
- L2263 _private prototype_ `bool CanRewindToFrame(int32 RewindFrame);` — Returns whether rewinding to RewindFrame is possible (if we have history for the frame etc.)
- L2266 _private prototype_ `bool AllowRewindToFrame(int32 RewindFrame) const;` — Returns whether rewinding to RewindFrame is allowed (if we are currently under cooldown etc.)
- L2269 _private prototype_ `void RewindToFrame(int32 RewindFrame);` — Apply the cached history state for the given frame cached particles and joints
- L2272 _private prototype_ `void ApplyTargets(const int32 Frame, const bool bResetSimulation);` — Apply targets positions and velocities while resimulating
- L2275 _private prototype_ `void StepNonResimParticles(const int32 Frame);` — Apply resim data for objects not simulating during resimulation
- L2278 _private function_ `template <typename TDirtyInfo> static void DesyncObject(TDirtyInfo& Info, const FFrameAndPhase FrameAndPhase)`
- L2284 _private member_ `TCircularBuffer<FFrameManagerInfo> Managers;`
- L2285 _private member_ `FDirtyPropertiesPool PropertiesPool;` — must come before DirtyParticles since it relies on it (and used in destruction)
- L2287 _private member_ `TDirtyObjects<FDirtyParticleInfo> DirtyParticles;`
- L2288 _private member_ `TDirtyObjects<FDirtyJointInfo> DirtyJoints;`
- L2289 _private member_ `TDirtyObjects<FParticleSimpleState> DirtyParticlePreResimState;`
- L2290 _private member_ `TDirtyObjects<FDirtyParticleErrorInfo> DirtyParticleErrors;`
- L2292 _private member_ `TArray<TWeakPtr<FBaseRewindHistory>> InputHistories;` — Todo, deprecate in favor of Particle->Input map?
- L2293 _private member_ `TArray<TWeakPtr<FBaseRewindHistory>> StateHistories;` — Todo, deprecate in favor of Particle->State map?
- L2295 _private member_ `TMap<Chaos::FGeometryParticleHandle*, TWeakPtr<FBaseRewindHistory>> InputParticleHistories;`
- L2296 _private member_ `TMap<Chaos::FGeometryParticleHandle*, TWeakPtr<FBaseRewindHistory>> StateParticleHistories;`
- L2298 _private member_ `FPBDRigidsSolver* Solver;`
- L2299 _private member_ `int32 CurFrame;`
- L2300 _private member_ `int32 LatestFrame;`
- L2301 _private member_ `int32 FramesSaved;`
- L2302 _private member_ `int32 DataIdxOffset;`
- L2303 _private member_ `bool bNeedsSave;` — Indicates that some data is pointing at head and requires saving before a rewind
- L2304 _private member_ `bool bRewindDataOptimization;`
- L2305 _private member_ `int32 ResimFrame = INDEX_NONE;`
- L2306 _private member_ `int32 ResimCooldownUntilFrame = INDEX_NONE;`
- L2307 _private member_ `int32 ResimClampedFrames = INDEX_NONE;`
- L2308 _private member_ `int32 LatestTargetFrame;`
- L2309 _private member_ `bool AllowResizingFromTickTrate = false;`
- L2310 _private member_ `Chaos::FReal InitializedDeltaTime = 0.0f;`
- L2313 _private member_ `uint64 ResimStartCycleCounter = 0;` — Used to measure how long a resim takes in realtime and then wait that much before allowing to trigger a new resim
- L2314 _private member_ `uint64 ResimPerformanceCooldownCycleCounter = 0;`
- L2317 _private member_ `int32 BlockResimFrame = INDEX_NONE;` — Used to block rewinding past a physics change we currently don't handle
- L2320 _private member_ `TArray<const Private::FPBDIsland*> IslandValidationIslands;` — Properties for EResimFrameValidation::IslandValidation logic
- L2321 _private member_ `TArray<const FGeometryParticleHandle*> IslandValidationIslandParticles;`
- L2324 _private member_ `TArray<FPBDRigidParticleHandle*> DynamicHandlesUpdateHolder;` — Dynamic particle handles to be set in bulk
- L2327 _private member_ `TArray<FPBDRigidParticleHandle*> SleepingHandlesUpdateHolder;` — Sleeping particle handles to be set in bulk
- L2330 _private member_ `TArray<FPBDRigidParticleHandle*> StaticHandlesUpdateHolder;` — Static particle handles to be set in bulk
- L2333 _private member_ `TArray<FPBDRigidParticleHandle*> KinematicHandlesUpdateHolder;` — Kinematic particle handles to be set in bulk
- L2335 _private member_ `TSet<const FGeometryParticleHandle*> ParticlesToForceResimAsFollower;`
- L2338 _private member_ `float NumPredictedFramesAverage = 0.0f;` — Average number of predicted frames, overall estimated value
- L2346 _public prototype_ `bool OverlapsAnyResimBubble(const Chaos::FAABB3& InAABB) const;` — This can be used to determine if an update that affects physics and restricts its effects to within an AABB can be skipped during a resim
- L2350 _public prototype_ `void TraceParticlesModifiedDuringRewind();` — Traces the particles that were modified during rewind. in the bubble resim case this also traces particles that were frozen.
- L2354 _private prototype_ `void FreezeParticlesOutsideResimBubbles();` — Freeze particles outside resim bubbles before rewind/resim
- L2356 _private prototype_ `void UnfreezeParticlesOutsideResimBubbles();` — Unfreeze particles that were frozen, this happens at the end of a resim (after all the resim frames have occurred)
- L2358 _private prototype_ `FAABB3 GetParticleSweptAABB(const FGeometryParticleHandle* ParticleHandle, FDirtyParticleInfo* DirtyParticleInfo, const FFrameAndPhase& AtFrameAndPhase, float HorizonDuration, float ExtraSweptDistance, float ExtraThickness) const;` — Util function to get a particle's swept AABB at a given frame and phase of the history
- L2361 _private prototype_ `void FindParticlesOverlappingResimBubbles(const FFrameAndPhase& RewindFrameAndPhase, float TotalResimDuration, TSet<FGeometryParticleHandle*>& OutParticlesOverlappingResimBubbles);` — Adds all particles needing resim and particle likely to interact with them during resim to OutParticlesOverlappingResimBubbles This is accomplished by creating resim "bubbles" around particles needing resim and growing them as they overlap other particles
- L2364 _private member_ `TArray<TPair<Chaos::FPhysicsProxyHandle, EObjectStateType>> FrozenParticles;` — Used to keep track of objects we "freeze" during resim (by making them kinematic and marking them FrozenDuringResim) and their object state prior to the freezing so it can be set back to its original value
- L2367 _private member_ `TArray<FGeometryParticleHandle*> ParticlesModifiedDuringRewind;` — Used to keep track of which particles were rewound during the last rewind. Emptied at the end of resim.
- L2372 _private member_ `TArray<Chaos::FAABB3> ResimBubbles;` — Resim bubbles start as the swept AABBs of particles needing resim, and grow to encompass nearby kinematic and dynamic particles involved in the resim Their formation happens in FindParticlesOverlappingResimBubbles()
- L2376 _private function_ `template <typename TObj> bool IsResimAndInSync(const TObj& Handle) const`
- L2379 _private prototype_ `template <bool bSkipDynamics, typename TDirtyInfo> void DesyncIfNecessary(TDirtyInfo& Info, const FFrameAndPhase FrameAndPhase);`
- L2381 _private prototype_ `void CachePreResimState(FGeometryParticleHandle& Handle);`
- L2384 _private function_ `template<typename TObj> void AccumulateErrorIfNecessary(TObj& Handle, const FFrameAndPhase FrameAndPhase)`

#### struct `Chaos::FRewindData::FFrameManagerInfo`  
`struct FFrameManagerInfo`  
_L2085-2094_
- L2087 _public member_ `TUniquePtr<IResimCacheBase> ExternalResimCache;`
- L2092 _public member_ `int32 FrameCreatedFor = INDEX_NONE;` — Note that this is not exactly the same as which frame this manager represents. A manager can have data for two frames at once, the important part is just knowing which frame it was created on so we know whether the physics data can rely on it Consider the case where nothing is dirty from GT and then an object moves from the simulation, in that case it needs a manager to record the data into
- L2093 _public member_ `FReal DeltaTime = 0.0f;`

#### struct `Chaos::FRewindData::TDirtyObjectInfo`  
`template <typename THistoryType, typename TObj> struct TDirtyObjectInfo`  
_L2097-2168_
- L2100 _private member_ `THistoryType History;`
- L2101 _private member_ `TObj* ObjPtr;`
- L2102 _private member_ `FDirtyPropertiesPool* PropertiesPool;`
- L2104 _public member_ `int32 DirtyDynamics = INDEX_NONE;` — Only used by particles, indicates the dirty properties was written to.
- L2105 _public member_ `int32 LastDirtyFrame;` — Track how recently this was made dirty
- L2106 _public member_ `int32 InitializedOnStep = INDEX_NONE;` — if not INDEX_NONE, it indicates we saw initialization during rewind history window
- L2107 _public member_ `bool bResimAsFollower = true;` — Indicates the particle will always resim in the exact same way from game thread data
- L2108 _public member_ `bool bNeedsResim = false;` — This particle needs resimulation, should have a higher priority when checking for valid rewind frames
- L2110 _public function_ `TDirtyObjectInfo(FDirtyPropertiesPool& InPropertiesPool, TObj& InObj, const int32 CurFrame, const int32 NumFrames, const bool bCacheOnePhase) : History(NumFrames, bCacheOnePhase) , ObjPtr(&InObj) , PropertiesPool(&InPropertiesPool) , LastDirtyFrame(CurFrame)`
- L2118 _public function_ `TDirtyObjectInfo(TDirtyObjectInfo&& Other) : History(MoveTemp(Other.History)) , ObjPtr(Other.ObjPtr) , PropertiesPool(Other.PropertiesPool) , LastDirtyFrame(Other.LastDirtyFrame) , InitializedOnStep(Other.InitializedOnStep) , bResimAsFollower(Other.bResimAsFollower) , bNeedsResim(Other.bNeedsResim)`
- L2130 _public function_ `~TDirtyObjectInfo()`
- L2138 _public prototype_ `TDirtyObjectInfo(const TDirtyObjectInfo& Other) = delete;`
- L2140 _public function_ `TObj* GetObjectPtr() const`
- L2143 _public function_ `THistoryType& AddFrame(const int32 Frame)` — `UE_DEPRECATED(5.7, "Deprecated, Use GetHistory() and MarkDirty() individually instead")`
- L2149 _public function_ `void ClearPhaseAndFuture(const FFrameAndPhase FrameAndPhase)`
- L2154 _public function_ `const THistoryType& GetHistory() const`
- L2159 _public function_ `THistoryType& GetHistory()`
- L2164 _public function_ `void MarkDirty(const int32 Frame)`

#### struct `Chaos::FRewindData::FDirtyParticleErrorInfo`  
`struct FDirtyParticleErrorInfo`  
_L2173-2193_
- L2176 _private member_ `FGeometryParticleHandle* HandlePtr;`
- L2177 _private member_ `FVec3 ErrorX = { 0,0,0 };`
- L2178 _private member_ `FQuat ErrorR = FQuat::Identity;`
- L2181 _public function_ `FDirtyParticleErrorInfo(FGeometryParticleHandle& InHandle) : HandlePtr(&InHandle)`
- L2184 _public function_ `void AccumulateError(FVec3 NewErrorX, FQuat NewErrorR)`
- L2190 _public function_ `FGeometryParticleHandle* GetObjectPtr() const`
- L2191 _public function_ `FVec3 GetErrorX() const`
- L2192 _public function_ `FQuat GetErrorR() const`

#### struct `Chaos::FResimDebugInfo`  
`struct FResimDebugInfo`  
_L2387-2392_
- L2389 _public member_ `double ResimTime = 0.0;`
- L2390 _public member_ `int32 FramesCoalesced = 0;`
- L2391 _public member_ `int32 MaxMultiplierUsed = 1;`

#### class `Chaos::IRewindCallback`  
`class IRewindCallback`  
_L2395-2463_
- desc: Used by user code to determine when rewind should occur and gives it the opportunity to record any additional data
- L2398 _public prototype_ `virtual ~IRewindCallback() = default;`
- L2401 _public function_ `virtual void PreProcessInputs_Internal(int32 PhysicsStep)` — Called just before ProcessInputs_Internal
- L2406 _public function_ `virtual void ProcessInputs_Internal(int32 PhysicsStep, const TArray<FSimCallbackInputAndObject>& SimCallbackInputs)` — Called before any sim callbacks are triggered but after physics data has marshaled over This means brand new physics particles are already created for example, and any pending game thread modifications have happened See ISimCallbackObject for recording inputs to callbacks associated with this PhysicsStep
- L2409 _public function_ `virtual void PostProcessInputs_Internal(int32 PhysicsStep)` — Called just after ProcessInputs_Internal
- L2412 _public function_ `virtual void ApplyCallbacks_Internal(int32 PhysicsStep, const TArray<ISimCallbackObject*>& SimCallbackObjects)` — Called after any presim callbacks are triggered and after physics data has marshaled over in order to modify the sim callback outputs
- L2418 _public function_ `virtual void ProcessInputs_External(int32 PhysicsStep, const TArray<FSimCallbackInputAndObject>& SimCallbackInputs)` — Called before any inputs are marshalled over to the physics thread. The physics state has not been applied yet, and cannot be inspected anyway because this is triggered from the external thread (game thread) Gives user the ability to modify inputs or record them - this can help with reducing latency if you want to act on inputs immediately
- L2425 _public function_ `virtual void InjectInputs_External(int32 PhysicsStep, int32 NumSteps)` — Called before inputs are split into potential sub-steps and marshaled over to the physics thread. The physics state has not been applied yet, and cannot be inspected anyway because this is triggered from the external thread (game thread) Gives user the ability to call GetProducerInputData_External one last time. Input data is shared amongst sub-steps. If NumSteps > 1 it means any input data injected will be shared for all sub-steps generated
- L2431 _public function_ `virtual void ProduceInputs_External(int32 PhysicsStep)` — Called on game thread for each physics thread task that gets queued up, before async inputs are marshaled. Gives user the ability to call GetProducerInputData_External for each physics step. Input data is shared amongst sub-steps. If NumSteps > 1 it means any input data injected will be shared for all sub-steps generated
- L2437 _public function_ `virtual int32 TriggerRewindIfNeeded_Internal(int32 LatestStepCompleted)` — Called after sim step to give the option to rewind. Any pending inputs for the next frame will remain in the queue Return the PhysicsStep to start resimulating from. Resim will run up until latest step passed into RecordInputs (i.e. latest physics sim simulated so far) Return INDEX_NONE to indicate no rewind
- L2440 _public function_ `virtual void AddResimulationRequest_Internal(const int32 PhysicsStep, const float DeltaSeconds)` — Add potential resimulation requests to the rewind data
- L2445 _public function_ `virtual void PreResimStep_Internal(int32 PhysicsStep, bool bFirstStep)` — Called before each rewind step. This is to give user code the opportunity to trigger other code before each rewind step Usually to simulate external systems that ran in lock step with the physics sim
- L2450 _public function_ `virtual void PostResimStep_Internal(int32 PhysicsStep)` — Called after each rewind step. This is to give user code the opportunity to trigger other code after each rewind step Usually to simulate external systems that ran in lock step with the physics sim
- L2453 _public function_ `virtual void RegisterRewindableSimCallback_Internal(ISimCallbackObject* Callback)` — Register a sim callback onto the rewind callback
- L2456 _public function_ `virtual void UnregisterRewindableSimCallback_Internal(ISimCallbackObject* Callback)` — Unregister a sim callback from the rewind callback
- L2459 _public function_ `virtual void SetResimDebugInfo_Internal(const FResimDebugInfo& ResimDebugInfo)` — Called When resim is finished with debug information about the resim
- L2462 _public member_ `Chaos::FRewindData* RewindData = nullptr;` — Rewind Data holding the callback

#### Free symbols / members of external scopes

- L15 _macro_ `#define VALIDATE_REWIND_DATA 0`
- L19 _macro_ `#define DEBUG_REWIND_DATA 0`
- L23 _macro_ `#define DEBUG_NETWORK_PHYSICS 0`
- L29 _namespace_ `namespace Chaos`
- L31 _namespace_ `namespace Private` (scope `Chaos`)
- L36 _namespace_ `namespace ResimDefines` (scope `Chaos`)
- L38 _externvar_ `extern const FName BubbleResimDebugDrawTag;` (scope `Chaos::ResimDefines`)
- L41 _namespace_ `namespace ResimulationCVars` (scope `Chaos`)
- L43 _externvar_ `extern float DesyncLeniencyValue;` (scope `Chaos::ResimulationCVars`)
- L136 _function_ `virtual void NetSerialize(FArchive& Ar, UPackageMap* PackageMap)` (scope `Chaos::FBaseRewindHistory::NetSerialize`) — `UE_DEPRECATED(5.6, "Deprecated, use the NetSerialize call with parameter that takes a function DataSetupFunction, pass in nullptr to opt out of implementing a function.")` — Serialize the data to or from a network archive
- L710 _function_ `template <typename TData, typename TObj> void CopyDataFromObject(TData& Data, const TObj& Obj)` (scope `Chaos`)
- L715 _function_ `inline void CopyDataFromObject(FPBDJointSettings& Data, const FPBDJointConstraintHandle& Joint)` (scope `Chaos`)
- L1155 _function_ `template <typename T> FString ToStringHelper(const T& Val)` (scope `Chaos`)
- L1161 _function_ `template <typename T> FString ToStringHelper(const TVector<T, 2>& Val)` (scope `Chaos`)
- L1166 _function_ `inline FString ToStringHelper(void* Val)` (scope `Chaos`)
- L1173 _function_ `inline FString ToStringHelper(const FReal Val)` (scope `Chaos`)
- L1178 _function_ `inline FString ToStringHelper(const FRealSingle Val)` (scope `Chaos`)
- L1183 _function_ `inline FString ToStringHelper(const EObjectStateType Val)` (scope `Chaos`)
- L1188 _function_ `inline FString ToStringHelper(const EPlasticityType Val)` (scope `Chaos`)
- L1193 _function_ `inline FString ToStringHelper(const EJointForceMode Val)` (scope `Chaos`)
- L1198 _function_ `inline FString ToStringHelper(const EJointMotionType Val)` (scope `Chaos`)
- L1203 _function_ `inline FString ToStringHelper(const bool Val)` (scope `Chaos`)
- L1208 _function_ `inline FString ToStringHelper(const int32 Val)` (scope `Chaos`)
- L1229 _macro_ `#define REWIND_CHAOS_PARTICLE_PROPERTY(PROP, NAME)\`
- L1233 _macro_ `#define REWIND_CHAOS_ZERO_PARTICLE_PROPERTY(PROP, NAME)\`
- L1237 _macro_ `#define REWIND_PARTICLE_STATIC_PROPERTY(PROP, NAME)\`
- L1244 _macro_ `#define REWIND_PARTICLE_KINEMATIC_PROPERTY(PROP, NAME)\`
- L1251 _macro_ `#define REWIND_PARTICLE_RIGID_PROPERTY(PROP, NAME)\`
- L1258 _macro_ `#define REWIND_PARTICLE_ZERO_PROPERTY(PROP, NAME)\`
- L1265 _macro_ `#define REWIND_JOINT_PROPERTY(PROP, FUNC_NAME, NAME)\`
- L1272 _function_ `inline int32 ComputeCircularSize(int32 NumFrames)` (scope `Chaos`)
- L1517 _macro_ `#define REWIND_PARTICLE_TO_STR(PropName) Out += FString::Printf(TEXT(#PropName":%s\n"), *ToStringHelper(PropName()));`
- L1640 _macro_ `#define CHAOS_INNER_JOINT_PROPERTY(OuterProp, FuncName, Inner, InnerType) REWIND_JOINT_PROPERTY(OuterProp, FuncName, Inner);` — See JointProperties for API Each CHAOS_INNER_JOINT_PROPERTY entry will have a Get*
- L1649 _macro_ `#define CHAOS_INNER_JOINT_PROPERTY(OuterProp, FuncName, Inner, InnerType) Out += FString::Printf(TEXT(#FuncName":%s\n"), *ToStringHelper(Get##FuncName()));`
- L1664 _function_ `template <typename T> const T* ConstifyHelper(T* Ptr)` (scope `Chaos`)
- L1668 _function_ `template <typename T> T NoRefHelper(const T& Ref)` (scope `Chaos`)
- L1769 _externvar_ `extern int32 SkipDesyncTest;` (scope `Chaos`)
- L1773 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRewindDataResizeInternal, const int32);`
- L1773 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRewindDataResizeInternal, const int32);` (scope `Chaos`)
- L2235 _typedef_ `using TDirtyObj = decltype(NoRefHelper(DirtyObjs.GetDenseAt(0)));` (scope `Chaos::FRewindData::FindOrAddDirtyObjImp`)

### `Source/Runtime/Experimental/Chaos/Public/SolverEventFilters.h` (Public)


#### struct `FSolverTrailingFilterSettings`  
`struct FSolverTrailingFilterSettings`  
_L13-39_
- reflection: `USTRUCT(Blueprintable)`
- L17 _public function_ `FSolverTrailingFilterSettings() : FilterEnabled(false) , MinMass(0.0f) , MinSpeed(0.f) , MinVolume(0.f)`
- L26 _public member_ `bool FilterEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|TrailingData Generation")` — Filter is enabled.
- L30 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|TrailingData Generation", meta = (DisplayName = "Min Mass Threshold"))` — The minimum mass threshold for the results (compared with min of particle 1 mass and particle 2 mass).
- L34 _public member_ `float MinSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|TrailingData Generation", meta = (DisplayName = "Min Speed Threshold"))`
- L38 _public member_ `float MinVolume;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|TrailingData Generation", meta = (DisplayName = "Min Volume Threshold"))`

#### struct `FSolverCollisionFilterSettings`  
`struct FSolverCollisionFilterSettings`  
_L42-69_
- reflection: `USTRUCT(BlueprintType)`
- L46 _public function_ `FSolverCollisionFilterSettings() : FilterEnabled(false) , MinMass(0.0f) , MinSpeed(0.0f) , MinImpulse(0.0f)`
- L55 _public member_ `bool FilterEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|CollisionData Generation")` — Filter is enabled.
- L59 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|CollisionData Generation", meta = (DisplayName = "Min Mass Threshold"))` — The minimum mass threshold for the results (compared with min of particle 1 mass and particle 2 mass).
- L63 _public member_ `float MinSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|CollisionData Generation", meta = (DisplayName = "Min Speed Threshold"))` — The min velocity threshold for the results (compared with min of particle 1 speed and particle 2 speed).
- L67 _public member_ `float MinImpulse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|CollisionData Generation", meta = (DisplayName = "Min Impulse Threshold"))` — The minimum impulse threshold for the results.

#### struct `FSolverBreakingFilterSettings`  
`struct FSolverBreakingFilterSettings`  
_L72-98_
- reflection: `USTRUCT(BlueprintType)`
- L76 _public function_ `FSolverBreakingFilterSettings() : FilterEnabled(false) , MinMass(0.0f) , MinSpeed(0.0f) , MinVolume(0.0f)`
- L85 _public member_ `bool FilterEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation")` — Filter is enabled.
- L89 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation", meta = (DisplayName = "Min Mass Threshold"))` — The minimum mass threshold for the results (compared with min of particle 1 mass and particle 2 mass).
- L93 _public member_ `float MinSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation", meta = (DisplayName = "Min Speed Threshold"))` — The min velocity threshold for the results (compared with min of particle 1 speed and particle 2 speed).
- L96 _public member_ `float MinVolume;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation", meta = (DisplayName = "Min Volume Threshold"))`

#### struct `FSolverRemovalFilterSettings`  
`struct FSolverRemovalFilterSettings`  
_L101-122_
- reflection: `USTRUCT(BlueprintType)`
- L105 _public function_ `FSolverRemovalFilterSettings() : FilterEnabled(false) , MinMass(0.0f) , MinVolume(0.0f)`
- L113 _public member_ `bool FilterEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation")` — Filter is enabled.
- L117 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation", meta = (DisplayName = "Min Mass Threshold"))` — The minimum mass threshold for the results (compared with min of particle 1 mass and particle 2 mass).
- L120 _public member_ `float MinVolume;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|BreakingData Generation", meta = (DisplayName = "Min Volume Threshold"))`

#### class `Chaos::FSolverCollisionEventFilter`  
`class FSolverCollisionEventFilter`  
_L136-147_
- L139 _public function_ `FSolverCollisionEventFilter()`
- L140 _public function_ `FSolverCollisionEventFilter(const FSolverCollisionFilterSettings& InSettings) : Settings(InSettings)`
- L142 _public prototype_ `bool Pass(const Chaos::FCollidingData& InData) const;`
- L143 _public function_ `bool Enabled() const`
- L144 _public function_ `void UpdateFilterSettings(const FSolverCollisionFilterSettings& InSettings)`
- L146 _public member_ `FSolverCollisionFilterSettings Settings;`

#### class `Chaos::FSolverTrailingEventFilter`  
`class FSolverTrailingEventFilter`  
_L149-160_
- L152 _public function_ `FSolverTrailingEventFilter()`
- L153 _public function_ `FSolverTrailingEventFilter(const FSolverTrailingFilterSettings &InSettings) : Settings(InSettings)`
- L155 _public prototype_ `bool Pass(const Chaos::FTrailingData& InData) const;`
- L156 _public function_ `bool Enabled() const`
- L157 _public function_ `void UpdateFilterSettings(const FSolverTrailingFilterSettings& InSettings)`
- L159 _public member_ `FSolverTrailingFilterSettings Settings;`

#### class `Chaos::FSolverBreakingEventFilter`  
`class FSolverBreakingEventFilter`  
_L162-173_
- L165 _public function_ `FSolverBreakingEventFilter()`
- L166 _public function_ `FSolverBreakingEventFilter(const FSolverBreakingFilterSettings& InSettings) : Settings(InSettings)`
- L168 _public prototype_ `bool Pass(const Chaos::FBreakingData& InData) const;`
- L169 _public function_ `bool Enabled() const`
- L170 _public function_ `void UpdateFilterSettings(const FSolverBreakingFilterSettings& InSettings)`
- L172 _public member_ `FSolverBreakingFilterSettings Settings;`

#### class `Chaos::FSolverRemovalEventFilter`  
`class FSolverRemovalEventFilter`  
_L175-186_
- L178 _public function_ `FSolverRemovalEventFilter()`
- L179 _public function_ `FSolverRemovalEventFilter(const FSolverRemovalFilterSettings& InSettings) : Settings(InSettings)`
- L181 _public prototype_ `bool Pass(const Chaos::FRemovalData& InData) const;`
- L182 _public function_ `bool Enabled() const`
- L183 _public function_ `void UpdateFilterSettings(const FSolverRemovalFilterSettings& InSettings)`
- L185 _public member_ `FSolverRemovalFilterSettings Settings;`

#### class `Chaos::FSolverEventFilters`  
`class FSolverEventFilters`  
_L192-239_
- desc: Container for the Solver Event Filters that have settings exposed through the Solver Actor
- L195 _public function_ `FSolverEventFilters() : CollisionFilter(new FSolverCollisionEventFilter()) , BreakingFilter(new FSolverBreakingEventFilter()) , TrailingFilter(new FSolverTrailingEventFilter()) , RemovalFilter(new FSolverRemovalEventFilter()) , CollisionEventsEnabled(false) , BreakingEventsEnabled(false) , TrailingEventsEnabled(false) , RemovalEventsEnabled(false)`
- L206 _public function_ `void SetGenerateCollisionEvents(bool bDoGenerate)`
- L207 _public function_ `void SetGenerateBreakingEvents(bool bDoGenerate)`
- L208 _public function_ `void SetGenerateTrailingEvents(bool bDoGenerate)`
- L209 _public function_ `void SetGenerateRemovalEvents(bool bDoGenerate)`
- L212 _public function_ `FSolverCollisionEventFilter* GetCollisionFilter() const` — Const access
- L213 _public function_ `FSolverBreakingEventFilter* GetBreakingFilter() const`
- L214 _public function_ `FSolverTrailingEventFilter* GetTrailingFilter() const`
- L215 _public function_ `FSolverRemovalEventFilter* GetRemovalFilter() const`
- L218 _public function_ `FSolverCollisionEventFilter* GetCollisionFilter()` — non-const access
- L219 _public function_ `FSolverBreakingEventFilter* GetBreakingFilter()`
- L220 _public function_ `FSolverTrailingEventFilter* GetTrailingFilter()`
- L221 _public function_ `FSolverRemovalEventFilter* GetRemovalFilter()`
- L223 _public function_ `bool IsCollisionEventEnabled() const`
- L224 _public function_ `bool IsBreakingEventEnabled() const`
- L225 _public function_ `bool IsTrailingEventEnabled() const`
- L226 _public function_ `bool IsRemovalEventEnabled() const`
- L230 _private member_ `TUniquePtr<FSolverCollisionEventFilter> CollisionFilter;`
- L231 _private member_ `TUniquePtr<FSolverBreakingEventFilter> BreakingFilter;`
- L232 _private member_ `TUniquePtr<FSolverTrailingEventFilter> TrailingFilter;`
- L233 _private member_ `TUniquePtr<FSolverRemovalEventFilter> RemovalFilter;`
- L235 _private member_ `bool CollisionEventsEnabled;`
- L236 _private member_ `bool BreakingEventsEnabled;`
- L237 _private member_ `bool TrailingEventsEnabled;`
- L238 _private member_ `bool RemovalEventsEnabled;`

#### Free symbols / members of external scopes

- L125 _namespace_ `namespace Chaos`
