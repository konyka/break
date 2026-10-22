# Runtime / uLangCore

- module root: `Source/Runtime/Solaris/uLangCore`
- headers: 70; symbols: 2240
- symbol kinds: class=53, enum=46, enumerator=61, externvar=2, function=1211, macro=97, member=185, namespace=88, prototype=177, struct=153, typedef=145, union=1, variable=21
- PublicDependencyModuleNames: AutoRTFM, Core

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/AllOf.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L10 _function_ `template <typename FirstIterator, typename LastIterator, typename Function> bool AllOf(FirstIterator First, LastIterator Last, Function F)` (scope `uLang`)
- L23 _function_ `template <typename Range, typename Function> bool AllOf(Range&& R, Function&& F)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/AnyOf.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L10 _function_ `template <typename FirstIterator, typename LastIterator, typename Function> bool AnyOf(FirstIterator First, LastIterator Last, Function F)` (scope `uLang`)
- L23 _function_ `template <typename Range, typename Function> bool AnyOf(Range&& R, Function&& F)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/BinarySearch.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L13 _namespace_ `namespace AlgoImpl` (scope `uLang`)
- L27 _function_ `template <typename RangeValueType, typename SizeType, typename PredicateValueType, typename ProjectionType, typename SortPredicateType> SizeType LowerBoundInternal(RangeValueType* First, const SizeType Num, const PredicateValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate)` (scope `uLang::AlgoImpl`) — Performs binary search, resulting in position of the first element >= Value @param First Pointer to array @param Num Number of elements in array @param Value Value to look for @param Projection Called on values in array to get type that can be compared to Value @param SortPredicate Predicate for sort comparison @returns Position of the first element >= Value, may be == Num
- L60 _function_ `template <typename RangeValueType, typename SizeType, typename PredicateValueType, typename ProjectionType, typename SortPredicateType> SizeType UpperBoundInternal(RangeValueType* First, const SizeType Num, const PredicateValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate)` (scope `uLang::AlgoImpl`) — Performs binary search, resulting in position of the first element that is larger than the given value @param First Pointer to array @param Num Number of elements in array @param Value Value to look for @param SortPredicate Predicate for sort comparison @returns Position of the first element > Value, may be == Num
- L84 _namespace_ `namespace Algo` (scope `uLang`)
- L96 _function_ `template <typename RangeType, typename ValueType, typename SortPredicateType> [[nodiscard]] auto LowerBound(const RangeType& Range, const ValueType& Value, SortPredicateType SortPredicate) -> decltype(GetNum(Range))` (scope `uLang::Algo`) — Performs binary search, resulting in position of the first element >= Value using predicate @param Range Range to search through, must be already sorted by SortPredicate @param Value Value to look for @param SortPredicate Predicate for sort comparison, defaults to < @returns Position of the first element >= Value, may be position after last element in range
- L101 _function_ `template <typename RangeType, typename ValueType> [[nodiscard]] auto LowerBound(const RangeType& Range, const ValueType& Value) -> decltype(GetNum(Range))` (scope `uLang::Algo`)
- L117 _function_ `template <typename RangeType, typename ValueType, typename ProjectionType, typename SortPredicateType> [[nodiscard]] auto LowerBoundBy(const RangeType& Range, const ValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate) -> decltype(GetNum(Range))` (scope `uLang::Algo`) — Performs binary search, resulting in position of the first element with projected value >= Value using predicate @param Range Range to search through, must be already sorted by SortPredicate @param Value Value to look for @param Projection Functor or data member pointer, called via Invoke to compare to Value @param SortPredicate Predicate for sort comparison, defaults to < @returns Position of the first element >= Value, may be position after last element in range
- L122 _function_ `template <typename RangeType, typename ValueType, typename ProjectionType> [[nodiscard]] auto LowerBoundBy(const RangeType& Range, const ValueType& Value, ProjectionType Projection) -> decltype(GetNum(Range))` (scope `uLang::Algo`)
- L137 _function_ `template <typename RangeType, typename ValueType, typename SortPredicateType> [[nodiscard]] auto UpperBound(const RangeType& Range, const ValueType& Value, SortPredicateType SortPredicate) -> decltype(GetNum(Range))` (scope `uLang::Algo`) — Performs binary search, resulting in position of the first element > Value using predicate @param Range Range to search through, must be already sorted by SortPredicate @param Value Value to look for @param SortPredicate Predicate for sort comparison, defaults to < @returns Position of the first element > Value, may be past end of range
- L142 _function_ `template <typename RangeType, typename ValueType> [[nodiscard]] auto UpperBound(const RangeType& Range, const ValueType& Value) -> decltype(GetNum(Range))` (scope `uLang::Algo`)
- L158 _function_ `template <typename RangeType, typename ValueType, typename ProjectionType, typename SortPredicateType> [[nodiscard]] auto UpperBoundBy(const RangeType& Range, const ValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate) -> decltype(GetNum(Range))` (scope `uLang::Algo`) — Performs binary search, resulting in position of the first element with projected value > Value using predicate @param Range Range to search through, must be already sorted by SortPredicate @param Value Value to look for @param Projection Functor or data member pointer, called via Invoke to compare to Value @param SortPredicate Predicate for sort comparison, defaults to < @returns Position of the first element > Value, may be past end of range
- L163 _function_ `template <typename RangeType, typename ValueType, typename ProjectionType> [[nodiscard]] auto UpperBoundBy(const RangeType& Range, const ValueType& Value, ProjectionType Projection) -> decltype(GetNum(Range))` (scope `uLang::Algo`)
- L177 _function_ `template <typename RangeType, typename ValueType, typename SortPredicateType> [[nodiscard]] auto BinarySearch(const RangeType& Range, const ValueType& Value, SortPredicateType SortPredicate) -> decltype(GetNum(Range))` (scope `uLang::Algo`) — Returns index to the first found element matching a value in a range, the range must be sorted by < @param Range The range to search, must be already sorted by SortPredicate @param Value The value to search for @param SortPredicate Predicate for sort comparison, defaults to < @return Index of found element, or IndexNone
- L192 _function_ `template <typename RangeType, typename ValueType> [[nodiscard]] auto BinarySearch(const RangeType& Range, const ValueType& Value)` (scope `uLang::Algo`)
- L207 _function_ `template <typename RangeType, typename ValueType, typename ProjectionType, typename SortPredicateType> [[nodiscard]] auto BinarySearchBy(const RangeType& Range, const ValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate) -> decltype(GetNum(Range))` (scope `uLang::Algo`) — Returns index to the first found element with projected value matching Value in a range, the range must be sorted by predicate @param Range The range to search, must be already sorted by SortPredicate @param Value The value to search for @param Projection Functor or data member pointer, called via Invoke to compare to Value @param SortPredicate Predicate for sort comparison, defaults to < @return Index of found element, or IndexNone
- L222 _function_ `template <typename RangeType, typename ValueType, typename ProjectionType> [[nodiscard]] auto BinarySearchBy(const RangeType& Range, const ValueType& Value, ProjectionType Projection)` (scope `uLang::Algo`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/Cases.h` (Public)


#### struct `uLang::TCases`  
`template <auto... Args> struct TCases`  
_L7-32_

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace uLang`
- L10 _function_ `template <typename U> constexpr friend bool operator==(const U& Left, TCases Right)` (scope `uLang`)
- L16 _function_ `template <typename U> constexpr friend bool operator==(TCases Left, const U& Right)` (scope `uLang`)
- L22 _function_ `template <typename U> constexpr friend bool operator!=(const U& Left, TCases Right)` (scope `uLang`)
- L28 _function_ `template <typename U> constexpr friend bool operator!=(TCases Left, const U& Right)` (scope `uLang`)
- L35 _variable_ `template <auto... Args> constexpr TCases<Args...> Cases{};` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/Contains.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L10 _function_ `template <typename TFirst, typename TLast, typename T> bool Contains(TFirst First, TLast Last, T&& Arg)` (scope `uLang`)
- L16 _function_ `template <typename TRange, typename T> bool Contains(TRange&& Range, T&& Arg)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/Find.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L9 _function_ `template <typename TFirst, typename TLast, typename T> TFirst Find(TFirst First, TLast Last, T&& Arg)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/FindIf.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L9 _function_ `template <typename TFirst, typename TLast, typename TFunction> TFirst FindIf(TFirst First, TLast Last, TFunction Function)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/HeapSort.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L14 _namespace_ `namespace AlgoImpl` (scope `uLang`)
- L22 _function_ `inline int32_t HeapGetLeftChildIndex(int32_t Index)` (scope `uLang::AlgoImpl`) — Gets the index of the left child of node at Index. @param   Index Node for which the left child index is to be returned. @returns Index of the left child.
- L33 _function_ `inline bool HeapIsLeaf(int32_t Index, int32_t Count)` (scope `uLang::AlgoImpl`) — Checks if node located at Index is a leaf or not. @param   Index Node index. @returns true if node is a leaf, false otherwise.
- L44 _function_ `inline int32_t HeapGetParentIndex(int32_t Index)` (scope `uLang::AlgoImpl`) — Gets the parent index for node at Index. @param   Index node index. @returns Parent index.
- L59 _function_ `template <typename RangeValueType, typename ProjectionType, typename PredicateType> void HeapSiftDown(RangeValueType* Heap, int32_t Index, const int32_t Count, const ProjectionType& Projection, const PredicateType& Predicate)` (scope `uLang::AlgoImpl`) — Fixes a possible violation of order property between node at Index and a child. @param   Heap        Pointer to the first element of a binary heap. @param   Index       Node index. @param   Count       Size of the heap. @param   Projection  The projection to apply to the elements. @param   Predicate   A binary predicate object used to specify if one element should precede another.
- L94 _function_ `template <class RangeValueType, typename ProjectionType, class PredicateType> int32_t HeapSiftUp(RangeValueType* Heap, int32_t RootIndex, int32_t NodeIndex, const ProjectionType& Projection, const PredicateType& Predicate)` (scope `uLang::AlgoImpl`) — Fixes a possible violation of order property between node at NodeIndex and a parent. @param   Heap        Pointer to the first element of a binary heap. @param   RootIndex   How far to go up? @param   NodeIndex   Node index. @param   Projection  The projection to apply to the elements. @param   Predicate   A binary predicate object used to specify if one element should precede another. @return  The new index of the node that was at NodeIndex
- L121 _function_ `template <typename RangeValueType, typename ProjectionType, typename PredicateType> void HeapifyInternal(RangeValueType* First, int32_t Num, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::AlgoImpl`) — Builds an implicit min-heap from a range of elements. This is the internal function used by Heapify overrides. @param   First       pointer to the first element to heapify @param   Num         the number of items to heapify @param   Projection  The projection to apply to the elements. @param   Predicate   A binary predicate object used to specify if one element should precede another.
- L138 _function_ `template <typename RangeValueType, typename ProjectionType, class PredicateType> void HeapSortInternal(RangeValueType* First, int32_t Num, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::AlgoImpl`) — Performs heap sort on the elements. This is the internal sorting function used by HeapSort overrides. @param   First       pointer to the first element to sort @param   Num         the number of elements to sort @param   Predicate   predicate class
- L152 _namespace_ `namespace Algo` (scope `uLang`)
- L160 _function_ `template <typename RangeType> void HeapSort(RangeType& Range)` (scope `uLang::Algo`) — Performs heap sort on the elements. Assumes < operator is defined for the element type. @param Range     The range to sort.
- L172 _function_ `template <typename RangeType, typename PredicateType> void HeapSort(RangeType& Range, PredicateType Predicate)` (scope `uLang::Algo`) — Performs heap sort on the elements. @param Range     The range to sort. @param Predicate A binary predicate object used to specify if one element should precede another.
- L184 _function_ `template <typename RangeType, typename ProjectionType> void HeapSortBy(RangeType& Range, ProjectionType Projection)` (scope `uLang::Algo`) — Performs heap sort on the elements. Assumes < operator is defined for the projected element type. @param Range     The range to sort. @param Projection    The projection to sort by when applied to the element.
- L197 _function_ `template <typename RangeType, typename ProjectionType, typename PredicateType> void HeapSortBy(RangeType& Range, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::Algo`) — Performs heap sort on the elements. @param Range     The range to sort. @param Projection    The projection to sort by when applied to the element. @param Predicate A binary predicate object, applied to the projection, used to specify if one element should precede another.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/IntroSort.h` (Public)


#### struct `uLang::AlgoImpl::IntroSortInternal::SStack`  
`struct SStack`  
_L29-34_
- L31 _public member_ `T* Min;`
- L32 _public member_ `T* Max;`
- L33 _public member_ `uint32_t MaxDepth;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L14 _namespace_ `namespace AlgoImpl` (scope `uLang`)
- L27 _function_ `template <typename T, typename ProjectionType, typename PredicateType> void IntroSortInternal(T* First, size_t Num, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::AlgoImpl`) — Implementation of an introspective sort. Starts with quick sort and switches to heap sort when the iteration depth is too big. The sort is unstable, meaning that the ordering of equal items is not necessarily preserved. This is the internal sorting function used by IntroSort overrides. @param First         pointer to the first element to sort @param Num           the number of items to sort @param Projection    The projection to sort by when applied to the element. @param Predicate     predicate class
- L130 _namespace_ `namespace Algo` (scope `uLang`)
- L138 _function_ `template <typename RangeType> void IntroSort(RangeType&& Range)` (scope `uLang::Algo`) — Sort a range of elements using its operator<. The sort is unstable. @param Range The range to sort.
- L150 _function_ `template <typename RangeType, typename PredicateType> void IntroSort(RangeType&& Range, PredicateType Predicate)` (scope `uLang::Algo`) — Sort a range of elements using a user-defined predicate class. The sort is unstable. @param Range     The range to sort. @param Predicate A binary predicate object used to specify if one element should precede another.
- L162 _function_ `template <typename RangeType, typename ProjectionType> void IntroSortBy(RangeType&& Range, ProjectionType Projection)` (scope `uLang::Algo`) — Sort a range of elements by a projection using the projection's operator<. The sort is unstable. @param Range         The range to sort. @param Projection    The projection to sort by when applied to the element.
- L175 _function_ `template <typename RangeType, typename ProjectionType, typename PredicateType> void IntroSortBy(RangeType&& Range, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::Algo`) — Sort a range of elements by a projection using a user-defined predicate class. The sort is unstable. @param Range         The range to sort. @param Projection    The projection to sort by when applied to the element. @param Predicate     A binary predicate object, applied to the projection, used to specify if one element should precede another.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/Rotate.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L12 _namespace_ `namespace AlgoImpl` (scope `uLang`)
- L15 _function_ `template <typename T> size_t RotateInternal(T* First, size_t Num, size_t Count)` (scope `uLang::AlgoImpl`)
- L52 _namespace_ `namespace Algo` (scope `uLang`)
- L63 _function_ `template <typename RangeType> size_t Rotate(RangeType&& Range, size_t Count)` (scope `uLang::Algo`) — Rotates a given amount of elements from the front of the range to the end of the range. @param  Range  The range to rotate. @param  Num    The number of elements to rotate from the front of the range. @return The new index of the element that was previously at the start of the range.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/Sort.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L10 _namespace_ `namespace Algo` (scope `uLang`)
- L18 _function_ `template <typename RangeType> void Sort(RangeType&& Range)` (scope `uLang::Algo`) — Sort a range of elements using its operator<.  The sort is unstable. @param  Range  The range to sort.
- L30 _function_ `template <typename RangeType, typename PredicateType> void Sort(RangeType&& Range, PredicateType Pred)` (scope `uLang::Algo`) — Sort a range of elements using a user-defined predicate class.  The sort is unstable. @param  Range      The range to sort. @param  Predicate  A binary predicate object used to specify if one element should precede another.
- L42 _function_ `template <typename RangeType, typename ProjectionType> void SortBy(RangeType&& Range, ProjectionType Proj)` (scope `uLang::Algo`) — Sort a range of elements by a projection using the projection's operator<.  The sort is unstable. @param  Range  The range to sort. @param  Proj   The projection to sort by when applied to the element.
- L55 _function_ `template <typename RangeType, typename ProjectionType, typename PredicateType> void SortBy(RangeType&& Range, ProjectionType Proj, PredicateType Pred)` (scope `uLang::Algo`) — Sort a range of elements by a projection using a user-defined predicate class.  The sort is unstable. @param  Range      The range to sort. @param  Proj       The projection to sort by when applied to the element. @param  Predicate  A binary predicate object, applied to the projection, used to specify if one element should precede another.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Algo/StableSort.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L13 _namespace_ `namespace AlgoImpl` (scope `uLang`)
- L16 _function_ `template <typename T, typename ProjectionType, typename PredicateType> void Merge(T* First, size_t Mid, size_t Num, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::AlgoImpl`)
- L38 _variable_ `inline constexpr size_t MinMergeSubgroupSize = 2;` (scope `uLang::AlgoImpl`)
- L50 _function_ `template <typename T, typename ProjectionType, typename PredicateType> void StableSortInternal(T* First, size_t Num, ProjectionType Projection, PredicateType Predicate)` (scope `uLang::AlgoImpl`) — Sort elements using user defined projection and predicate classes.  The sort is stable, meaning that the ordering of equal items is preserved. This is the internal sorting function used by the Algo::Sort overloads. @param  First       Pointer to the first element to sort. @param  Num         The number of items to sort. @param  Projection  A projection to apply to each element to get the value to sort by. @param  Predicate   A predicate class which compares two projected elements and returns whether one occurs before the other.
- L117 _namespace_ `namespace Algo` (scope `uLang`)
- L125 _function_ `template <typename RangeType> void StableSort(RangeType&& Range)` (scope `uLang::Algo`) — Sort a range of elements using its operator<.  The sort is stable. @param  Range  The range to sort.
- L137 _function_ `template <typename RangeType, typename PredicateType> void StableSort(RangeType&& Range, PredicateType Pred)` (scope `uLang::Algo`) — Sort a range of elements using a user-defined predicate class.  The sort is stable. @param  Range      The range to sort. @param  Predicate  A binary predicate object used to specify if one element should precede another.
- L149 _function_ `template <typename RangeType, typename ProjectionType> void StableSortBy(RangeType&& Range, ProjectionType Proj)` (scope `uLang::Algo`) — Sort a range of elements by a projection using the projection's operator<.  The sort is stable. @param  Range  The range to sort. @param  Proj   The projection to sort by when applied to the element.
- L162 _function_ `template <typename RangeType, typename ProjectionType, typename PredicateType> void StableSortBy(RangeType&& Range, ProjectionType Proj, PredicateType Pred)` (scope `uLang::Algo`) — Sort a range of elements by a projection using a user-defined predicate class.  The sort is stable. @param  Range      The range to sort. @param  Proj       The projection to sort by when applied to the element. @param  Predicate  A binary predicate object, applied to the projection, used to specify if one element should precede another.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Common.h` (Public)


#### enum `uLang::EVisitResult`  
`enum class EVisitResult : int8_t`  
_L333-338_
- desc: Result returned from a visitor functor indicating how to continue or to quit early.
- L335 _public enumerator_ `Continue = 0` — Continue to exhaustively iterate through all items
- L336 _public enumerator_ `SkipChildren = 1` — Skip iterating through any children/sub-items and continue though other items in hierarchy
- L337 _public enumerator_ `Stop = 2` — Stop iterating through items and early exit

#### enum `uLang::EIterateResult`  
`enum class EIterateResult : int8_t`  
_L341-345_
- desc: Iteration result returned from an iteration
- L343 _public enumerator_ `Stopped = 0` — Iteration was terminated early by the visitor functor and wants the caller to exit early
- L344 _public enumerator_ `Completed = 1` — Iteration is done iterating and wants the caller to continue iterating if there are more elements to iterate over

#### enum `uLang::EResult`  
`enum class EResult : int8_t`  
_L348-353_
- desc: Generic error codes
- L350 _public enumerator_ `Unspecified = -1` — Not sure if success or failure
- L351 _public enumerator_ `OK = 0` — Success
- L352 _public enumerator_ `Error` — Some error occurred

#### enum `uLang::EErrorAction`  
`enum class EErrorAction : int8_t`  
_L356-360_
- desc: Generic action after error has occurred
- L358 _public enumerator_ `Continue = 0`
- L359 _public enumerator_ `Break`

#### enum `uLang::EEquate`  
`enum class EEquate : int8_t`  
_L363-368_
- desc: Comparison result value
- L365 _public enumerator_ `Less = -1`
- L366 _public enumerator_ `Equal = 0`
- L367 _public enumerator_ `Greater = 1`

#### enum `uLang::ENoInit`  
`enum ENoInit`  
_L372-372_
- desc: Enum used in constructors to indicate they should not initialize anything
- L372 _public enumerator_ `enum ENoInit { NoInit }; enum EDefaultInit { DefaultInit }; enum EIndex { IndexNone = -1 };` — Enum used in constructors to indicate they should not initialize anything

#### enum `uLang::EDefaultInit`  
`enum EDefaultInit`  
_L375-375_
- desc: Enum used to force default initialization
- L375 _public enumerator_ `enum EDefaultInit { DefaultInit }; enum EIndex { IndexNone = -1 };` — Enum used to force default initialization

#### enum `uLang::EIndex`  
`enum EIndex`  
_L378-378_
- desc: Used to signify an unspecified index
- L378 _public enumerator_ `enum EIndex { IndexNone = -1 }; enum class EAssertSeverity : int8_t { Fatal = 0,` — Used to signify an unspecified index

#### enum `uLang::EAssertSeverity`  
`enum class EAssertSeverity : int8_t`  
_L383-387_
- L385 _public enumerator_ `Fatal = 0`
- L386 _public enumerator_ `Recoverable`

#### enum `uLang::ELogVerbosity`  
`enum class ELogVerbosity : int8_t`  
_L389-396_
- L391 _public enumerator_ `Error` — Prints an error to console (and log file)
- L392 _public enumerator_ `Warning` — Prints a warning to console (and log file)
- L393 _public enumerator_ `Display` — Prints a message to console (and log file)
- L394 _public enumerator_ `Verbose` — Prints a verbose message to console (and log file)
- L395 _public enumerator_ `Log` — Prints a message to a log file (does not print to console)

#### struct `uLang::SSystemParams`  
`struct SSystemParams`  
_L399-418_
- desc: Parameters to initialize the uLang module
- L401 _public typedef_ `using FMalloc = void * (*)(size_t);`
- L402 _public typedef_ `using FRealloc = void * (*)(void *, size_t);`
- L403 _public typedef_ `using FFree = void (*)(void *);`
- L405 _public typedef_ `using FAssert = EErrorAction(*)(EAssertSeverity , const char * , const char * , int32_t , const char * , ...);`
- L406 _public typedef_ `using FLog = void(*)(ELogVerbosity , const char* , ...);`
- L408 _public member_ `int _APIVersion = 0;` — Set this to ULANG_API_VERSION
- L410 _public member_ `FMalloc _HeapMalloc = nullptr;` — Allocate system heap memory
- L411 _public member_ `FRealloc _HeapRealloc = nullptr;` — Reallocate system heap memory
- L412 _public member_ `FFree _HeapFree = nullptr;` — Free system heap memory
- L414 _public member_ `FAssert _AssertFailed = nullptr;` — Called when an assert fails
- L415 _public member_ `FLog _LogMessage = nullptr;` — Print a message
- L417 _public member_ `ELogVerbosity _Verbosity = ELogVerbosity::Display;` — Won't print anything under the _Verbosity level

#### Free symbols / members of external scopes

- L20 _macro_ `#define ULANG_PLATFORM_WINDOWS 0` — Windows requires special handling for now...
- L24 _macro_ `#define ULANG_PLATFORM_MAC 0`
- L28 _macro_ `#define ULANG_PLATFORM_LINUX 0`
- L31 _macro_ `#define ULANG_PLATFORM_POSIX (ULANG_PLATFORM_MAC || ULANG_PLATFORM_LINUX)`
- L34 _macro_ `#define ULANG_PLATFORM_EXTENSION 0`
- L39 _macro_ `#define ULANG_STRINGIFY(x) ULANG_STRINGIFY_INNER(x)` — Define macros to help with the inclusion of platform specific headers
- L40 _macro_ `#define ULANG_STRINGIFY_INNER(x) #x`
- L42 _macro_ `#define ULANG_PREPROCESSOR_JOIN(x, y) ULANG_PREPROCESSOR_JOIN_INNER(x, y)`
- L43 _macro_ `#define ULANG_PREPROCESSOR_JOIN_INNER(x, y) x##y`
- L47 _macro_ `#define ULANG_PLATFORM_HEADER_NAME(Suffix) ULANG_STRINGIFY(ULANG_PREPROCESSOR_JOIN(ULANG_PLATFORM, Suffix))`
- L49 _macro_ `#define ULANG_PLATFORM_HEADER_NAME(Suffix) ULANG_STRINGIFY(ULANG_PREPROCESSOR_JOIN(ULANG_PLATFORM/ULANG_PLATFORM, Suffix))`
- L54 _macro_ `#define ULANG_PLATFORM_HEADER_NAME_WITH_PREFIX(Prefix, Suffix) ULANG_STRINGIFY(Prefix/ULANG_PREPROCESSOR_JOIN(ULANG_PLATFORM, Suffix))`
- L56 _macro_ `#define ULANG_PLATFORM_HEADER_NAME_WITH_PREFIX(Prefix, Suffix) ULANG_STRINGIFY(Prefix/ULANG_PLATFORM/ULANG_PREPROCESSOR_JOIN(ULANG_PLATFORM, Suffix))`
- L65 _macro_ `#define ULANG_API_VERSION 2` — To prevent API mismatch in dynamic linking situations
- L71 _macro_ `#define DLLIMPORT ULANG_DLLIMPORT`
- L72 _macro_ `#define DLLEXPORT ULANG_DLLEXPORT`
- L76 _macro_ `#define DLLIMPORT_VTABLE ULANG_DLLIMPORT_VTABLE`
- L77 _macro_ `#define DLLEXPORT_VTABLE ULANG_DLLEXPORT_VTABLE`
- L84 _macro_ `#define ULANG_THIRD_PARTY_INCLUDES_START \`
- L90 _macro_ `#define ULANG_THIRD_PARTY_INCLUDES_END \`
- L115 _macro_ `#define ULANG_IGNORE_CLASS_MEMACCESS_WARNING_START \`
- L119 _macro_ `#define ULANG_IGNORE_CLASS_MEMACCESS_WARNING_END \`
- L135 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_START`
- L138 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_END`
- L145 _macro_ `#define ULANG_DLLIMPORT __declspec(dllimport)`
- L146 _macro_ `#define ULANG_DLLEXPORT __declspec(dllexport)`
- L147 _macro_ `#define ULANG_DLLIMPORT_VTABLE`
- L148 _macro_ `#define ULANG_DLLEXPORT_VTABLE`
- L175 _macro_ `#define ULANG_GCC_PACK(n) __attribute__((packed,aligned(n)))`
- L176 _macro_ `#define ULANG_GCC_ALIGN(n) __attribute__((aligned(n)))`
- L182 _macro_ `#define ULANG_MS_ALIGN(n) __declspec(align(n))`
- L191 _macro_ `#define ULANG_FORCEINLINE __forceinline`
- L192 _macro_ `#define ULANG_FORCENOINLINE __declspec(noinline)`
- L204 _macro_ `#define ULANG_RESTRICT __restrict`
- L210 _macro_ `#define ULANG_LIKELY(x) __builtin_expect(!!(x), 1)`
- L211 _macro_ `#define ULANG_UNLIKELY(x) __builtin_expect(!!(x), 0)`
- L221 _macro_ `#define ULANG_COUNTOF(x) _countof(x)`
- L230 _macro_ `#define ULANG_FALLTHROUGH [[fallthrough]]`
- L240 _macro_ `#define ULANG_UNREACHABLE() while(true) { ULANG_BREAK(); }`
- L248 _prototype_ `void ULANG_CA_AssumeNoReturn() __attribute__((analyzer_noreturn));` — A fake function marked with noreturn that acts as a marker for CA_ASSUME to ensure the static analyzer doesn't take an analysis path that is assumed not to be navigable.
- L250 _macro_ `#define ULANG_CA_ASSUME(Expr) (__builtin_expect(!bool(Expr), 0) ? ULANG_CA_AssumeNoReturn() : (void)0)`
- L265 _macro_ `#define ULANG_ASSERT(expr) { if (ULANG_UNLIKELY((bool)!(expr))) { if ((*::uLang::GetSystemParams()._AssertFailed)(::uLang::EAssertSeverity::Fatal, #expr, __FILE__, __LINE__, "") == ::uLang::EErrorAction::Break) { ULANG_BREAK(); } ULANG_CA_A`
- L266 _macro_ `#define ULANG_VERIFY(expr) { if (ULANG_UNLIKELY((bool)!(expr)) && (*::uLang::GetSystemParams()._AssertFailed)(::uLang::EAssertSeverity::Recoverable, #expr, __FILE__, __LINE__, "") == ::uLang::EErrorAction::Break) ULANG_BREAK(); }`
- L267 _macro_ `#define ULANG_ENSURE(expr) ( ULANG_LIKELY(!!(expr)) || (\`
- L273 _macro_ `#define ULANG_ERRORF(format, ...) { if ((*::uLang::GetSystemParams()._AssertFailed)(::uLang::EAssertSeverity::Fatal, "", __FILE__, __LINE__, format, ##__VA_ARGS__) == ::uLang::EErrorAction::Break) ULANG_BREAK(); }`
- L274 _macro_ `#define ULANG_ASSERTF(expr, format, ...) { if (ULANG_UNLIKELY((bool)!(expr))) { if ((*::uLang::GetSystemParams()._AssertFailed)(::uLang::EAssertSeverity::Fatal, #expr, __FILE__, __LINE__, format, ##__VA_ARGS__) == ::uLang::EErrorAction::Bre`
- L275 _macro_ `#define ULANG_VERIFYF(expr, format, ...) { if (ULANG_UNLIKELY((bool)!(expr)) && (*::uLang::GetSystemParams()._AssertFailed)(::uLang::EAssertSeverity::Recoverable, #expr, __FILE__, __LINE__, format, ##__VA_ARGS__) == ::uLang::EErrorAction::B`
- L276 _macro_ `#define ULANG_ENSUREF(expr, format, ...) ( ULANG_LIKELY(!!(expr)) || (\`
- L282 _macro_ `#define ULANG_ASSERT(expr) (void(sizeof(!!(expr))))`
- L283 _macro_ `#define ULANG_VERIFY(expr) (void(sizeof(!!(expr))))`
- L284 _macro_ `#define ULANG_ENSURE(expr) (!!(expr))`
- L286 _macro_ `#define ULANG_ERRORF(format, ...) (void(0))`
- L287 _macro_ `#define ULANG_ASSERTF(expr, format, ...) (void(sizeof(!!(expr))))`
- L288 _macro_ `#define ULANG_VERIFYF(expr, format, ...) (void(sizeof(!!(expr))))`
- L289 _macro_ `#define ULANG_ENSUREF(expr, format, ...) (!!(expr))`
- L295 _macro_ `#define VERSE_SUPPRESS_UNUSED(_Variable) (void)(_Variable);`
- L298 _macro_ `#define USING_ELogVerbosity \` — Ensure either just enumerator (Error), fully qualified (ELogVerbosity::Error) or variable (MyVerbosity) work equally well.
- L305 _macro_ `#define ULANG_LOGF(verbosity, format, ...) \`
- L314 _macro_ `#define ULANG_AGGRESSIVE_MEMORY_SAVING 0`
- L318 _namespace_ `namespace uLang`
- L322 _typedef_ `using NullPtrType = std::nullptr_t;` (scope `uLang`) — Type of nullptr
- L326 _typedef_ `using Integer = int64_t;` (scope `uLang`) — Default size for uLang Integer Type
- L327 _typedef_ `using Float = double;` (scope `uLang`) — Default size for uLang Float Type
- L328 _typedef_ `using Boolean = bool;` (scope `uLang`) — Default size for uLang Boolean Type
- L330 _variable_ `inline const uint32_t uint32_invalid = UINT32_MAX;` (scope `uLang`)
- L419 _prototype_ `bool operator==(const SSystemParams& Lhs, const SSystemParams& Rhs);` (scope `uLang`)
- L422 _externvar_ `extern SSystemParams GSystemParams;` (scope `uLang`) — Global variable for efficient access
- L423 _function_ `inline SSystemParams& GetSystemParams()` (scope `uLang`)
- L430 _externvar_ `extern const CAllocatorInstance GSystemAllocatorInstance;` (scope `uLang`)
- L438 _prototype_ `EResult Initialize(const SSystemParams & Params);` (scope `uLang`) — Initialize the uLang Module @param Params Parameters to initialize the uLang module @return EResult indicating outcome of operation
- L443 _prototype_ `bool IsInitialized();` (scope `uLang`) — Utility function for uLang modules to verify against.
- L450 _prototype_ `EResult DeInitialize();` (scope `uLang`) — Deinitialize the uLang Module @return EResult indicating outcome of operation
- L455 _prototype_ `void SetGlobalVerbosity(const uLang::ELogVerbosity GlobalVerbosity);` (scope `uLang`) — Setter function for the global verbosity level in SSystemParams

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/Array.h` (Public)


#### struct `uLang::Private::TCanMoveTArrayPointersBetweenArrayTypes`  
`template <typename FromArrayType, typename ToArrayType> struct TCanMoveTArrayPointersBetweenArrayTypes`  
_L21-35_
- L23 _public typedef_ `using FromAllocatorType = typename FromArrayType::ElementAllocatorType;`
- L24 _public typedef_ `using ToAllocatorType = typename ToArrayType::ElementAllocatorType;`
- L25 _public typedef_ `using FromElementType = typename FromArrayType::ElementType;`
- L26 _public typedef_ `using ToElementType = typename ToArrayType::ElementType;`
- L28 _public member_ `static constexpr bool Value = std::is_same_v<FromAllocatorType, ToAllocatorType> &&`

#### struct `uLang::Private::TLessThanComparable`  
`template <typename Type, typename = void> struct TLessThanComparable`  
_L38-41_
- L40 _public member_ `static constexpr bool Value = false;`
- L46 _public member_ `static constexpr bool Value = std::is_convertible_v<decltype(std::declval<const Type&>() < std::declval<const Type&>()), bool>;`

#### struct `uLang::Private::TLessThanComparable`  
`template <typename Type> struct TLessThanComparable<Type, std::void_t<decltype(std::declval<const Type&>() < std::declval<const Type&>())>>`  
_L44-47_
- L40 _public member_ `static constexpr bool Value = false;`
- L46 _public member_ `static constexpr bool Value = std::is_convertible_v<decltype(std::declval<const Type&>() < std::declval<const Type&>()), bool>;`

#### class `uLang::TArrayG`  
`template<typename InElementType, typename InElementAllocatorType, typename... RawAllocatorArgsType> class TArrayG`  
_L62-2149_
- desc: Templated dynamic array A dynamically sized array of typed elements.  Makes the assumption that your elements are relocate-able; i.e. that they can be transparently moved to new memory without a copy constructor.  The main implication is that pointers to elements in the TArrayG may be invalidated by adding or removing other elements to the array. Removal of elements is O(N) and invalidates the indices of subsequent elements. Caution: as noted below some methods are not safe for element types that require constructors.
- L69 _public typedef_ `using ElementType = InElementType;`
- L70 _public typedef_ `using ElementAllocatorType = InElementAllocatorType;`
- L75 _public function_ `TArrayG(RawAllocatorArgsType&&... RawAllocatorArgs) : _ElementStorage(ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...) , _ArrayNum(0) , _ArrayMax(0)` — Constructor with given raw allocator arguments (none required for heap allocator).
- L84 _public function_ `TArrayG(const typename ElementAllocatorType::RawAllocatorType & RawAllocator) : _ElementStorage(RawAllocator) , _ArrayNum(0) , _ArrayMax(0)` — Constructor with given raw allocator.
- L97 _public function_ `TArrayG(const ElementType* Ptr, int32_t Count, RawAllocatorArgsType&&... RawAllocatorArgs) : _ElementStorage(ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — Constructor from a raw array of elements. @param Ptr   A pointer to an array of elements to copy. @param Count The number of elements to copy from Ptr. @see Append
- L105 _public prototype_ `TArrayG(bool, const ElementType& = ElementType(), RawAllocatorArgsType&&...) = delete;`
- L107 _public function_ `TArrayG(int32_t Count, const ElementType& Value = ElementType(), RawAllocatorArgsType&&... RawAllocatorArgs) : _ElementStorage(ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)`
- L121 _public function_ `TArrayG(std::initializer_list<InElementType> InitList, RawAllocatorArgsType&&... RawAllocatorArgs) : _ElementStorage(ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — Initializer list constructor
- L132 _public function_ `template <typename OtherElementType> TArrayG(std::initializer_list<OtherElementType> InitList, RawAllocatorArgsType&&... RawAllocatorArgs) : _ElementStorage(ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — @overload This templated version of the constructor above allows for types aliased by using-declarations to also work with it.
- L143 _public function_ `template <typename OtherElementType, typename OtherElementAllocatorType, typename... OtherRawAllocatorArgsType> explicit TArrayG(const TArrayG<OtherElementType, OtherElementAllocatorType, OtherRawAllocatorArgsType...>& Other, RawAllocatorArgsType&&... RawAllocatorArgs) : _ElementStorage(ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — Copy constructor with changed allocator. Use the common routine to perform the copy. @param Other The source array to copy.
- L154 _public function_ `TArrayG(const TArrayG& Other) : _ElementStorage(Other._ElementStorage.GetRawAllocator())` — Copy constructor. Use the common routine to perform the copy. @param Other The source array to copy.
- L167 _public function_ `TArrayG(const TArrayG& Other, int32_t ExtraSlack) : _ElementStorage(Other._ElementStorage.GetRawAllocator())` — Copy constructor. Use the common routine to perform the copy. @param Other The source array to copy. @param ExtraSlack Tells how much extra memory should be preallocated at the end of the array in the number of elements.
- L179 _public function_ `TArrayG& operator=(const TArrayG& Other)` — Assignment operator. First deletes all currently contained elements and then copies from other array. @param Other The source array to assign from.
- L202 _private function_ `template <typename FromArrayType, typename ToArrayType> requires (Private::TCanMoveTArrayPointersBetweenArrayTypes<FromArrayType, ToArrayType>::Value) static void MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray, int32_t PrevMax)` — Moves or copies array. Depends on the array type traits. This override moves. @param ToArray Array to move into. @param FromArray Array to move from.
- L224 _private function_ `template <typename FromArrayType, typename ToArrayType> requires (!Private::TCanMoveTArrayPointersBetweenArrayTypes<FromArrayType, ToArrayType>::Value) static void MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray, int32_t PrevMax)` — Moves or copies array. Depends on the array type traits. This override copies. @param ToArray Array to move into. @param FromArray Array to move from. @param ExtraSlack Tells how much extra memory should be preallocated at the end of the array in the number of elements.
- L242 _private function_ `template <typename FromArrayType, typename ToArrayType> requires (Private::TCanMoveTArrayPointersBetweenArrayTypes<FromArrayType, ToArrayType>::Value) static void MoveOrCopyWithSlack(ToArrayType& ToArray, FromArrayType& FromArray, int32_t PrevMax, int32_t ExtraSlack)` — Moves or copies array. Depends on the array type traits. This override moves. @param ToArray Array to move into. @param FromArray Array to move from. @param ExtraSlack Tells how much extra memory should be preallocated at the end of the array in the number of elements.
- L261 _private function_ `template <typename FromArrayType, typename ToArrayType> requires (!Private::TCanMoveTArrayPointersBetweenArrayTypes<FromArrayType, ToArrayType>::Value) static void MoveOrCopyWithSlack(ToArrayType& ToArray, FromArrayType& FromArray, int32_t PrevMax, int32_t ExtraSlack)` — Moves or copies array. Depends on the array type traits. This override copies. @param ToArray Array to move into. @param FromArray Array to move from. @param ExtraSlack Tells how much extra memory should be preallocated at the end of the array in the number of elements.
- L273 _public function_ `TArrayG(TArrayG && Other)` — Move constructor. @param Other Array to move from.
- L285 _public function_ `TArrayG(TArrayG && Other, int32_t ExtraSlack)` — Move constructor. @param Other Array to move from. @param ExtraSlack Tells how much extra memory should be preallocated at the end of the array in the number of elements.
- L300 _public function_ `template <typename OtherElementAllocatorType, typename... OtherRawAllocatorArgsType> explicit TArrayG(TArrayG<ElementType, OtherElementAllocatorType, OtherRawAllocatorArgsType...>&& Other)` — Move constructor. @param Other Array to move from.
- L310 _public function_ `TArrayG& operator=(TArrayG && Other)` — Move assignment operator. @param Other Array to assign and move from.
- L321 _public function_ `~TArrayG()` — Destructor.
- L331 _public function_ `ElementType* GetData()` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if ArrayMax == 0.
- L341 _public function_ `const ElementType* GetData() const` — Helper function for returning a typed pointer to the first array entry. @returns Pointer to first array entry or nullptr if ArrayMax == 0.
- L351 _public function_ `uint32_t GetTypeSize() const` — Helper function returning the size of the inner type. @returns Size in bytes of array type.
- L363 _public function_ `uint32_t GetAllocatedSize(void) const` — Helper function to return the amount of memory allocated by this container. Only returns the size of allocations made directly by the container, not the elements themselves. @returns Number of bytes allocated by this container.
- L373 _public function_ `int32_t GetSlack() const` — Returns the amount of slack in this array in elements. @see Num, Shrink
- L382 _public function_ `void CheckInvariants() const` — Checks array invariants: if array size is greater than zero and less than maximum.
- L392 _public function_ `void RangeCheck(int32_t Index) const` — Checks if index is in array range. @param Index Index to check.
- L409 _public function_ `bool IsValidIndex(int32_t Index) const` — Tests if index is valid, i.e. greater than or equal to zero, and less than the number of elements in the array. @param Index Index to test. @returns True if index is valid. False otherwise.
- L420 _public function_ `int32_t Num() const` — Returns number of elements in array. @returns Number of elements in array. @see GetSlack
- L431 _public function_ `int32_t Max() const` — Returns maximum number of elements in array. @returns Maximum number of elements in array. @see GetSlack
- L437 _public function_ `const typename ElementAllocatorType::RawAllocatorType & GetRawAllocator() const` — Accesses the raw allocator.
- L448 _public function_ `bool IsEmpty() const` — Returns true if no elements in array @returns true if no elements in array or false if one or more elements. @see IsFull, Num
- L459 _public function_ `bool IsFilled() const` — Returns true if any elements in array @returns true if one or more elements in array or false no elements. @see IsEmpty, Num
- L469 _public function_ `ElementType& operator[](int32_t Index)` — Array bracket operator. Returns reference to element at give index. @returns Reference to indexed element.
- L482 _public function_ `const ElementType& operator[](int32_t Index) const` — Array bracket operator. Returns reference to element at give index. Const version of the above. @returns Reference to indexed element.
- L494 _public function_ `ElementType Pop(bool bAllowShrinking = true)` — Pops element from the array. @param bAllowShrinking If this call allows shrinking of the array during element remove. @returns Popped element.
- L507 _public function_ `void Push(ElementType&& Item)` — Pushes element into the array. @param Item Item to push.
- L520 _public function_ `void Push(const ElementType& Item)` — Pushes element into the array. Const ref version of the above. @param Item Item to push. @see Pop, Top
- L531 _public function_ `ElementType& Top()` — Returns the top element, i.e. the last one. @returns Reference to the top element. @see Pop, Push
- L544 _public function_ `const ElementType& Top() const` — Returns the top element, i.e. the last one. Const version of the above. @returns Reference to the top element. @see Pop, Push
- L555 _public function_ `ElementType& Last(int32_t IndexFromTheEnd = 0)` — Returns n-th last element from the array. @param IndexFromTheEnd (Optional) Index from the end of array (default = 0). @returns Reference to n-th last element from the array.
- L569 _public function_ `const ElementType& Last(int32_t IndexFromTheEnd = 0) const` — Returns n-th last element from the array. Const version of the above. @param IndexFromTheEnd (Optional) Index from the end of array (default = 0). @returns Reference to n-th last element from the array.
- L580 _public function_ `void Shrink()` — Shrinks the array's used memory to smallest possible to store elements currently in it. @see Slack
- L597 _public function_ `bool Find(const ElementType& Item, int32_t& Index) const` — Finds element within the array. @param Item Item to look for. @param Index Will contain the found index. @returns True if found. False otherwise. @see FindLast, FindLastByPredicate
- L610 _public function_ `int32_t Find(const ElementType& Item) const` — Finds element within the array. @param Item Item to look for. @returns Index of the found element. IndexNone otherwise. @see FindLast, FindLastByPredicate
- L631 _public function_ `bool FindLast(const ElementType& Item, int32_t& Index) const` — Finds element within the array starting from the end. @param Item Item to look for. @param Index Output parameter. Found index. @returns True if found. False otherwise. @see Find, FindLastByPredicate
- L643 _public function_ `int32_t FindLast(const ElementType& Item) const` — Finds element within the array starting from the end. @param Item Item to look for. @returns Index of the found element. IndexNone otherwise.
- L664 _public function_ `template <typename Predicate> int32_t FindLastByPredicate(Predicate Pred, int32_t Count) const` — Searches an initial subrange of the array for the last occurrence of an element which matches the specified predicate. @param Pred Predicate taking array element and returns true if element matches search criteria, false otherwise. @param Count The number of elements from the front of the array through which to search. @returns Index of the found element. IndexNone otherwise.
- L685 _public function_ `template <typename Predicate> int32_t FindLastByPredicate(Predicate Pred) const` — Searches the array for the last occurrence of an element which matches the specified predicate. @param Pred Predicate taking array element and returns true if element matches search criteria, false otherwise. @returns Index of the found element. IndexNone otherwise.
- L698 _public function_ `template <typename KeyType> int32_t IndexOfByKey(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Index to the first matching element, or IndexNone if none is found.
- L718 _public function_ `template <typename Predicate> int32_t IndexOfByPredicate(Predicate Pred) const` — Finds an item by predicate. @param Pred The predicate to match. @returns Index to the first matching element, or IndexNone if none is found.
- L740 _public function_ `template <typename KeyType> const ElementType* FindByKey(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Pointer to the first matching element, or nullptr if none is found. @see Find
- L754 _public function_ `template <typename KeyType> ElementType* FindByKey(const KeyType& Key)` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). Time Complexity: O(n), starts iteration from the beginning so better performance if Key is in the front @param Key The key to search by. @returns Pointer to the first matching element, or nullptr if none is found. @see Find
- L775 _public function_ `template <typename Predicate> const ElementType* FindByPredicate(Predicate Pred) const` — Finds an element which matches a predicate functor. @param Pred The functor to apply to each element. @returns Pointer to the first element for which the predicate returns true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L787 _public function_ `template <typename Predicate> ElementType* FindByPredicate(Predicate Pred)` — Finds an element which matches a predicate functor. @param Pred The functor to apply to each element. true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L809 _public function_ `template <typename Predicate> TArrayG FilterByPredicate(Predicate Pred) const` — Filters the elements in the array based on a predicate functor. @param Pred The functor to apply to each element. @returns TArrayG with the same type as this object which contains the subset of elements for which the functor returns true. @see FindByPredicate, ContainsByPredicate
- L829 _public function_ `template <typename ComparisonType> bool Contains(const ComparisonType& Item) const` — Checks if this array contains the element. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L849 _public function_ `template <typename Predicate> bool ContainsByPredicate(Predicate Pred) const` — Checks if this array contains element for which the predicate is true. @param Predicate to use @returns True if found. False otherwise. @see Contains, Find
- L860 _public function_ `bool operator==(const TArrayG& OtherArray) const` — Equality operator. @param OtherArray Array to compare. @returns True if this array is the same as OtherArray. False otherwise.
- L873 _public function_ `bool operator!=(const TArrayG& OtherArray) const` — Inequality operator. @param OtherArray Array to compare. @returns True if this array is NOT the same as OtherArray. False otherwise.
- L884 _public function_ `bool operator<(const TArrayG& OtherArray) const requires (Private::TLessThanComparable<InElementType>::Value)` — Less than operator. @param OtherArray Array to compare. @returns True if this array is less than OtherArray. False otherwise.
- L929 _public function_ `int32_t AddUninitialized(int32_t Count = 1)` — Adds a given number of uninitialized elements into the array. Caution, AddUninitialized() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param Count Number of elements to add. @returns Number of elements in array before addition.
- L954 _public function_ `void InsertUninitialized(int32_t Index, int32_t Count = 1)` — Inserts a given number of uninitialized elements into the array at given location. Caution, InsertUninitialized() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param Index Tells where to insert the new elements. @param Count Number of elements to add. @see Insert, InsertZeroed, InsertDefaulted
- L980 _public function_ `void InsertZeroed(int32_t Index, int32_t Count = 1)` — Inserts a given number of zeroed elements into the array at given location. Caution, InsertZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param Index Tells where to insert the new elements. @param Count Number of elements to add. @see Insert, InsertUninitialized, InsertDefaulted
- L1000 _public function_ `ElementType& InsertZeroed_GetRef(int32_t Index)` — Inserts a zeroed element into the array at given location. Caution, InsertZeroed_GetRef() will create an element without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param Index Tells where to insert the new element. @return A reference to the newly-inserted element. @see Insert_GetRef, InsertDefaulted_GetRef
- L1016 _public function_ `void InsertDefaulted(int32_t Index, int32_t Count = 1)` — Inserts a given number of default-constructed elements into the array at a given location. @param Index Tells where to insert the new elements. @param Count Number of elements to add. @see Insert, InsertUninitialized, InsertZeroed
- L1030 _public function_ `ElementType& InsertDefaulted_GetRef(int32_t Index)` — Inserts a default-constructed element into the array at a given location. @param Index Tells where to insert the new element. @return A reference to the newly-inserted element. @see Insert_GetRef, InsertZeroed_GetRef
- L1045 _public function_ `int32_t Insert(std::initializer_list<ElementType> InitList, const int32_t InIndex)` — Inserts given elements into the array at given location. @param Items Array of elements to insert. @param InIndex Tells where to insert the new elements. @returns Location at which the item was inserted.
- L1063 _public function_ `template <typename OtherElementAllocatorType, typename... OtherRawAllocatorArgsType> int32_t Insert(const TArrayG<ElementType, OtherElementAllocatorType, OtherRawAllocatorArgsType...>& Items, const int32_t InIndex)` — Inserts given elements into the array at given location. @param Items Array of elements to insert. @param InIndex Tells where to insert the new elements. @returns Location at which the item was inserted.
- L1083 _public function_ `template <typename OtherElementAllocatorType, typename... OtherRawAllocatorArgsType> int32_t Insert(TArrayG<ElementType, OtherElementAllocatorType, OtherRawAllocatorArgsType...>&& Items, const int32_t InIndex)` — Inserts given elements into the array at given location. @param Items Array of elements to insert. @param InIndex Tells where to insert the new elements. @returns Location at which the item was inserted.
- L1105 _public function_ `int32_t Insert(const ElementType* Ptr, int32_t Count, int32_t Index)` — Inserts a raw array of elements at a particular index in the TArrayG. @param Ptr A pointer to an array of elements to add. @param Count The number of elements to insert from Ptr. @param Index The index to insert the elements at. @return The index of the first element inserted. @see Add, Remove
- L1123 _public function_ `void CheckAddress(void const* Addr) const` — Checks that the specified address is not part of an element within the container. Used for implementations to ULANG_ASSERTF that reference arguments aren't going to be invalidated by possible reallocation. @param Addr The address to check. @see Add, Remove
- L1137 _public function_ `int32_t Insert(ElementType&& Item, int32_t Index)` — Inserts a given element into the array at given location. Move semantics version. @param Item The element to insert. @param Index Tells where to insert the new elements. @returns Location at which the insert was done. @see Add, Remove
- L1156 _public function_ `int32_t Insert(const ElementType& Item, int32_t Index)` — Inserts a given element into the array at given location. @param Item The element to insert. @param Index Tells where to insert the new elements. @returns Location at which the insert was done. @see Add, Remove
- L1176 _public function_ `ElementType& Insert_GetRef(ElementType&& Item, int32_t Index)` — Inserts a given element into the array at given location. Move semantics version. @param Item The element to insert. @param Index Tells where to insert the new element. @return A reference to the newly-inserted element. @see Add, Remove
- L1196 _public function_ `ElementType& Insert_GetRef(const ElementType& Item, int32_t Index)` — Inserts a given element into the array at given location. @param Item The element to insert. @param Index Tells where to insert the new element. @return A reference to the newly-inserted element. @see Add, Remove
- L1209 _private function_ `void RemoveAtImpl(int32_t Index, int32_t Count, bool bAllowShrinking)`
- L1247 _public function_ `void RemoveAt(int32_t Index)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L1261 _public function_ `template <typename CountType> void RemoveAt(int32_t Index, CountType Count, bool bAllowShrinking = true)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L1268 _private function_ `void RemoveAtSwapImpl(int32_t Index, int32_t Count = 1, bool bAllowShrinking = true)`
- L1311 _public function_ `void RemoveAtSwap(int32_t Index)` — Removes an element (or elements) at given location optionally shrinking the array. This version is much more efficient than RemoveAt (O(Count) instead of O(ArrayNum)), but does not preserve the order. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L1329 _public function_ `template <typename CountType> void RemoveAtSwap(int32_t Index, CountType Count, bool bAllowShrinking = true)` — Removes an element (or elements) at given location optionally shrinking the array. This version is much more efficient than RemoveAt (O(Count) instead of O(ArrayNum)), but does not preserve the order. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L1343 _public function_ `int32_t Replace(const ElementType& OldItem, const ElementType& NewItem)` — Replaces specified element with the supplied element. @param OldItem The element to replace. @param NewItem The element to replace with. @returns Location at which the replace was done. @see Add, Remove, Insert
- L1362 _public function_ `void Reset(int32_t NewSize = 0)` — Same as empty, but doesn't change memory allocations, unless the new size is larger than the current array. It calls the destructors on held items if needed and then zeros the ArrayNum. @param NewSize The expected usage size after calling this function.
- L1381 _public function_ `void Empty(int32_t Slack = 0)` — Empties the array. It calls the destructors on held items if needed. @param Slack (Optional) The expected usage size after empty operation. Default is 0.
- L1400 _public function_ `void SetNum(int32_t NewNum, bool bAllowShrinking = true)` — Resizes array to given number of elements. @param NewNum New size of the array. @param bAllowShrinking Tell if this function can shrink the memory in-use if suitable.
- L1419 _public function_ `void SetNumZeroed(int32_t NewNum, bool bAllowShrinking = true)` — Resizes array to given number of elements. New elements will be zeroed. @param NewNum New size of the array.
- L1436 _public function_ `void SetNumUninitialized(int32_t NewNum, bool bAllowShrinking = true)` — Resizes array to given number of elements. New elements will be uninitialized. @param NewNum New size of the array.
- L1452 _public function_ `void SetNumUnsafeInternal(int32_t NewNum)` — Does nothing except setting the new number of elements in the array. Does not destruct items, does not de-allocate memory. @param NewNum New number of elements in the array, must be <= the current number of elements in the array.
- L1467 _public function_ `template <typename OtherElementAllocatorType, typename... OtherRawAllocatorArgsType> void Append(const TArrayG<ElementType, OtherElementAllocatorType, OtherRawAllocatorArgsType...>& Source)` — Appends the specified array to this array. Allocator changing version. @param Source The array to append. @see Add, Insert
- L1493 _public function_ `template <typename OtherElementAllocatorType, typename... OtherRawAllocatorArgsType> void Append(TArrayG<ElementType, OtherElementAllocatorType, OtherRawAllocatorArgsType...>&& Source)` — Appends the specified array to this array. @param Source The array to append. @see Add, Insert
- L1520 _public function_ `void Append(const ElementType* Ptr, int32_t Count)` — Adds a raw array of elements to the end of the TArrayG. @param Ptr   A pointer to an array of elements to add. @param Count The number of elements to insert from Ptr. @see Add, Insert
- L1534 _public function_ `void Append(std::initializer_list<ElementType> InitList)` — Adds an initializer list of elements to the end of the TArrayG. @param InitList The initializer list of elements to add. @see Add, Insert
- L1550 _public function_ `TArrayG& operator+=(TArrayG&& Other)` — Appends the specified array to this array. Cannot append to self. Move semantics version. @param Other The array to append.
- L1562 _public function_ `TArrayG& operator+=(const TArrayG& Other)` — Appends the specified array to this array. Cannot append to self. @param Other The array to append.
- L1573 _public function_ `TArrayG& operator+=(std::initializer_list<ElementType> InitList)` — Appends the specified initializer list to this array. @param InitList The initializer list to append.
- L1586 _public function_ `template <typename... ArgsType> int32_t Emplace(ArgsType&&... Args)` — Constructs a new item at the end of the array, possibly reallocating the whole array to fit. @param Args  The arguments to forward to the constructor of the new item. @return      Index to the new item
- L1600 _public function_ `template <typename... ArgsType> ElementType& Emplace_GetRef(ArgsType&&... Args)` — Constructs a new item at the end of the array, possibly reallocating the whole array to fit. @param Args  The arguments to forward to the constructor of the new item. @return A reference to the newly-inserted element.
- L1615 _public function_ `template <typename... ArgsType> void EmplaceAt(int32_t Index, ArgsType&&... Args)` — Constructs a new item at a specified index, possibly reallocating the whole array to fit. @param Index The index to add the item at. @param Args  The arguments to forward to the constructor of the new item.
- L1629 _public function_ `template <typename... ArgsType> ElementType& EmplaceAt_GetRef(int32_t Index, ArgsType&&... Args)` — Constructs a new item at a specified index, possibly reallocating the whole array to fit. @param Index The index to add the item at. @param Args  The arguments to forward to the constructor of the new item. @return A reference to the newly-inserted element.
- L1646 _public function_ `int32_t Add(ElementType&& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. Move semantics version. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L1659 _public function_ `int32_t Add(const ElementType& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L1674 _public function_ `ElementType& Add_GetRef(ElementType&& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. Move semantics version. @param Item The item to add @return A reference to the newly-inserted element. @see AddDefaulted_GetRef, AddUnique_GetRef, AddZeroed_GetRef, Insert_GetRef
- L1687 _public function_ `ElementType& Add_GetRef(const ElementType& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. @param Item The item to add @return A reference to the newly-inserted element. @see AddDefaulted_GetRef, AddUnique_GetRef, AddZeroed_GetRef, Insert_GetRef
- L1705 _public function_ `int32_t AddZeroed(int32_t Count = 1)` — Adds new items to the end of the array, possibly reallocating the whole array to fit. The new items will be zeroed. Caution, AddZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param  Count  The number of new items to add. @return Index to the first of the new items. @see Add, AddDefaulted, AddUnique, Append, Insert
- L1726 _public function_ `ElementType& AddZeroed_GetRef()` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. The new item will be zeroed. Caution, AddZeroed_GetRef() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @return A reference to the newly-inserted element. @see Add_GetRef, AddDefaulted_GetRef, AddUnique_GetRef, Insert_GetRef
- L1742 _public function_ `int32_t AddDefaulted(int32_t Count = 1)` — Adds new items to the end of the array, possibly reallocating the whole array to fit. The new items will be default-constructed. @param  Count  The number of new items to add. @return Index to the first of the new items. @see Add, AddZeroed, AddUnique, Append, Insert
- L1756 _public function_ `ElementType& AddDefaulted_GetRef()` — Add a new item to the end of the array, possibly reallocating the whole array to fit. The new item will be default-constructed. @return A reference to the newly-inserted element. @see Add_GetRef, AddZeroed_GetRef, AddUnique_GetRef, Insert_GetRef
- L1773 _private function_ `template <typename ArgsType> int32_t AddUniqueImpl(ArgsType&& Args)` — Adds unique element to array if it doesn't exist. @param Args Item to add. @returns Index of the element in the array.
- L1795 _public function_ `int32_t AddUnique(ElementType&& Item)` — Adds unique element to array if it doesn't exist. Move semantics version. @param Args Item to add. @returns Index of the element in the array. @see Add, AddDefaulted, AddZeroed, Append, Insert
- L1804 _public function_ `int32_t AddUnique(const ElementType& Item)` — Adds unique element to array if it doesn't exist. @param Args Item to add. @returns Index of the element in the array. @see Add, AddDefaulted, AddZeroed, Append, Insert
- L1812 _public function_ `void Reserve(int32_t Number)` — Reserves memory such that the array can contain at least Number elements. @param Number The number of elements that the array should be able to contain after allocation. @see Shrink
- L1826 _public function_ `void Init(const ElementType& Element, int32_t Number)` — Sets the size of the array, filling it with the given element. @param Element The element to fill array with. @param Number The number of elements that the array should be able to contain after allocation.
- L1843 _public function_ `int32_t RemoveSingle(const ElementType& Item)` — Removes the first occurrence of the specified item in the array, maintaining order but not indices. @param Item The item to remove. @returns The number of items removed. For RemoveSingleItem, this is always either 0 or 1. @see Add, Insert, Remove, RemoveAll, RemoveAllSwap
- L1873 _public function_ `template <typename OtherElementType> int32_t Remove(const OtherElementType& Item)` — Removes as many instances of Item as there are in the array, maintaining order but not indices. @param Item Item to remove from array. @returns Number of removed elements. @see Add, Insert, RemoveAll, RemoveAllSwap, RemoveSingle, RemoveSwap
- L1890 _public function_ `template <class PREDICATE_CLASS> int32_t RemoveAll(const PREDICATE_CLASS& Predicate)` — Remove all instances that match the predicate, maintaining order but not indices Optimized to work with runs of matches/non-matches @param Predicate Predicate class instance @returns Number of removed elements. @see Add, Insert, RemoveAllSwap, RemoveSingle, RemoveSwap
- L1938 _public function_ `template <class PREDICATE_CLASS> void RemoveAllSwap(const PREDICATE_CLASS& Predicate, bool bAllowShrinking = true)` — Remove all instances that match the predicate @param Predicate Predicate class instance @see Remove, RemoveSingle, RemoveSingleSwap, RemoveSwap
- L1962 _public function_ `int32_t RemoveSingleSwap(const ElementType& Item, bool bAllowShrinking = true)` — Removes the first occurrence of the specified item in the array. This version is much more efficient O(Count) instead of O(ArrayNum), but does not preserve the order @param Item The item to remove @returns The number of items removed. For RemoveSingleItem, this is always either 0 or 1. @see Add, Insert, Remove, RemoveAll, RemoveAllSwap, RemoveSwap
- L1986 _public function_ `int32_t RemoveSwap(const ElementType& Item)` — Removes item from the array. This version is much more efficient, because it uses RemoveAtSwap internally which is O(Count) instead of RemoveAt which is O(ArrayNum), but does not preserve the order. @returns Number of elements removed. @see Add, Insert, Remove, RemoveAll, RemoveAllSwap
- L2007 _public function_ `ElementType * begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L2008 _public function_ `const ElementType * begin() const`
- L2009 _public function_ `ElementType * end()`
- L2010 _public function_ `const ElementType * end() const`
- L2022 _public function_ `void Sort()` — Sorts the array assuming < operator is defined for the item type. @note: If your array contains raw pointers, they will be automatically dereferenced during sorting. Therefore, your array will be sorted by the values being pointed to, rather than the pointers' values. If this is not desirable, please use Algo::Sort(MyArray) instead. The auto-dereferencing behavior does not occur with smart pointers.
- L2038 _public function_ `template <class PredicateType> void Sort(const PredicateType& Predicate)` — Sorts the array using user define predicate class. @param Predicate Predicate instance or lambda. @note: If your array contains raw pointers, they will be automatically dereferenced during sorting. Therefore, your predicate will be passed references rather than pointers. If this is not desirable, please use Algo::Sort(MyArray, Predicate) instead. The auto-dereferencing behavior does not occur with smart pointers.
- L2044 _public function_ `template <class PredicateType> void StableSort(const PredicateType& Predicate)`
- L2052 _public function_ `void RemoveSuccessiveDuplicates()` — Remove successive duplicates. Assumes that elements of the array have ==.
- L2071 _private function_ `ULANG_FORCENOINLINE void ResizeGrow(int32_t OldNum)`
- L2076 _private function_ `ULANG_FORCENOINLINE void ResizeShrink()`
- L2086 _private function_ `ULANG_FORCENOINLINE void ResizeTo(int32_t NewMax)`
- L2098 _private function_ `ULANG_FORCENOINLINE void ResizeForCopy(int32_t NewMax, int32_t PrevMax)`
- L2123 _private function_ `template <typename OtherElementType> void CopyToEmpty(const OtherElementType* OtherData, int32_t OtherNum, int32_t PrevMax, int32_t ExtraSlack)` — Copies data from one array into this array. Uses the fast path if the data in question does not need a constructor. @param Source The source array to copy @param PrevMax The previous allocated size @param ExtraSlack Additional amount of memory to allocate at the end of the buffer. Counted in elements. Zero by default.
- L2140 _protected typedef_ `using ElementStorageType = typename std::conditional_t< ElementAllocatorType::NeedsElementType, typename ElementAllocatorType::template ForElementType<ElementType>, typename ElementAllocatorType::ForAnyElementType>;`
- L2145 _protected member_ `ElementStorageType _ElementStorage;`
- L2146 _protected member_ `int32_t _ArrayNum;`
- L2147 _protected member_ `int32_t _ArrayMax;`

#### struct `uLang::TIsZeroConstructType`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsZeroConstructType<TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2160-2163_
- L2162 _public member_ `static constexpr bool Value = TAllocatorTraits<ElementAllocatorType>::IsZeroConstruct;`

#### struct `uLang::TContainerTraits`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TContainerTraits<TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>> : public TContainerTraitsBase<TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2166-2170_
- inherits: `TContainerTraitsBase<TArrayG<ElementType,ElementAllocatorType,RawAllocatorArgsType...>>`
- L2169 _public member_ `static constexpr bool MoveWillEmptyContainer = TAllocatorTraits<ElementAllocatorType>::SupportsMove;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsContiguousContainer<TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2173-2176_
- L2175 _public member_ `static constexpr bool Value = true;`

#### enum `uLang::TIsTArray::(anonymous)`  
`template <typename T> struct TIsTArray`  
_L2182-2182_
- desc: Traits class which determines whether or not a type is a TArray.

#### struct `uLang::TIsTArray`  
`template <typename T> struct TIsTArray`  
_L2182-2182_
- desc: Traits class which determines whether or not a type is a TArray.

#### enum `uLang::TIsTArray::(anonymous)`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2184-2184_

#### struct `uLang::TIsTArray`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2184-2184_

#### enum `uLang::TIsTArray::(anonymous)`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2185-2185_

#### struct `uLang::TIsTArray`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2185-2185_

#### enum `uLang::TIsTArray::(anonymous)`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2186-2186_

#### struct `uLang::TIsTArray`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2186-2186_

#### enum `uLang::TIsTArray::(anonymous)`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2187-2187_

#### struct `uLang::TIsTArray`  
`template <typename ElementType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsTArray< TArrayG<ElementType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L2187-2187_

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace uLang`
- L18 _namespace_ `namespace Private` (scope `uLang`)
- L1878 _function_ `return RemoveAll([&Item](ElementType& Element) { return Element == Item; });` (scope `uLang::TArrayG::Remove`) — Element is non-const to preserve compatibility with existing code with a non-const operator==() member function
- L2153 _typedef_ `template<class ElementType> using TArray = TArrayG<ElementType, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Array that allocates elements on the heap
- L2157 _typedef_ `template<class ElementType> using TArrayA = TArrayG<ElementType, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Array that allocates object using a given allocator instance
- L2182 _enumerator_ `template <typename T> struct TIsTArray { enum { Value = false }; }; template <typename ElementType` (scope `uLang::TIsTArray::__anon441a4d0a0203`) — Traits class which determines whether or not a type is a TArray.
- L2184 _enumerator_ `template <typename ElementType` (scope `uLang::TIsTArray::__anon441a4d0a0303`)
- L2185 _enumerator_ `template <typename ElementType` (scope `uLang::TIsTArray::__anon441a4d0a0403`)
- L2186 _enumerator_ `template <typename ElementType` (scope `uLang::TIsTArray::__anon441a4d0a0503`)
- L2187 _enumerator_ `template <typename ElementType` (scope `uLang::TIsTArray::__anon441a4d0a0603`)
- L2190 _function_ `template <typename T> uint32_t GetTypeHash(const TArray<T> Array)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/DirectedGraph.h` (Public)


#### class `uLang::TDirectedGraph`  
`template<typename InElementType> class TDirectedGraph`  
_L13-103_
- L16 _public typedef_ `using NodeId = int32_t;`
- L17 _public member_ `constexpr static NodeId InvalidNodeId = uLang::IndexNone;`
- L19 _public function_ `NodeId AddNode(const InElementType& Item)`
- L24 _public function_ `NodeId AddNode(InElementType&& Item)`
- L29 _public function_ `bool AddDirectedEdge(const NodeId From, const NodeId To)`
- L40 _public function_ `bool AddDirectedEdgeUnique(const NodeId From, const NodeId To)`
- L56 _public function_ `void Reserve(int32_t NodesSlack, int32_t EdgesSlack = 0)`
- L61 _public function_ `void Empty(int32_t NodesSlack = 0, int32_t EdgesSlack = 0)`
- L66 _public function_ `int32_t NumNodes() const`
- L71 _public function_ `const InElementType& operator[](NodeId Index) const`
- L76 _public function_ `InElementType& operator[](NodeId Index)`
- L81 _public prototype_ `bool TopologicalSort(TArray<InElementType>& OutItems) const;`
- L82 _public prototype_ `bool TopologicalSort_Pointers(TArray<const InElementType*>& OutItems) const;`
- L83 _public prototype_ `bool TopologicalSort_Pointers(TArray<InElementType*>& OutItems);`
- L85 _public prototype_ `TArray<TArray<NodeId>> FindCycles() const;`
- L102 _private member_ `TArray<SNode> _Nodes;`
- L254 _function_ `template<typename InElementType> bool TDirectedGraph<InElementType>::TopologicalSort(TArray<InElementType>& OutItems) const`
- L267 _function_ `template<typename InElementType> bool TDirectedGraph<InElementType>::TopologicalSort_Pointers(TArray<const InElementType*>& OutItems) const`
- L280 _function_ `template<typename InElementType> bool TDirectedGraph<InElementType>::TopologicalSort_Pointers(TArray<InElementType*>& OutItems)`
- L293 _function_ `template<typename InElementType> TArray<TArray<typename TDirectedGraph<InElementType>::NodeId>> TDirectedGraph<InElementType>::FindCycles() const`

#### struct `uLang::TDirectedGraph::SNode`  
`struct SNode`  
_L90-101_
- L92 _public function_ `SNode(const InElementType& Item) : _Item(Item)`
- L93 _public function_ `SNode(InElementType&& Item) : _Item(Move(Item))`
- L95 _public member_ `InElementType _Item;`
- L98 _public member_ `int32_t _InDegree = 0;` — Tracks how many incoming edges this node has
- L100 _public member_ `TArrayG<int32_t, TInlineElementAllocator<4>> _Successors;` — Node indices for outgoing edges

#### struct `uLang::TDiGraphTopologicalIterator_Base`  
`template<typename InElementType> struct TDiGraphTopologicalIterator_Base`  
_L107-177_
- desc: Base functionality for both const and non-const directed-graph iterators.
- L109 _public typedef_ `using DiGraphType = TDirectedGraph<InElementType>;`
- L111 _public function_ `TDiGraphTopologicalIterator_Base(const DiGraphType& InContainer)`
- L116 _public function_ `explicit operator bool() const`
- L122 _public function_ `typename DiGraphType::NodeId SkipCurrent()` — This automatically increments the iterator to the next element. You don't need to increment the iterator after calling this.
- L127 _public function_ `void Enqueue(TArray<typename DiGraphType::NodeId>&& NodesToVisit)`
- L133 _protected function_ `void Increment(const DiGraphType& Container)`
- L153 _protected function_ `typename DiGraphType::NodeId CurrentNodeIndex() const`
- L158 _protected function_ `void Reset(const DiGraphType& Container)`
- L175 _private member_ `TArray<typename DiGraphType::NodeId> _NodesToVisit;`
- L176 _private member_ `TArray<int32_t> _VisitCounters;`

#### struct `uLang::TDiGraphTopologicalIterator`  
`template<typename InElementType> struct TDiGraphTopologicalIterator : public TDiGraphTopologicalIterator_Base<InElementType>`  
_L181-214_
- inherits: `TDiGraphTopologicalIterator_Base<InElementType>`
- desc: Iterator for directed-graph elements.
- L183 _public typedef_ `using Super = TDiGraphTopologicalIterator_Base<InElementType>;`
- L184 _public typedef_ `using DiGraphType = typename Super::DiGraphType;`
- L186 _public function_ `TDiGraphTopologicalIterator(DiGraphType& InContainer) : TDiGraphTopologicalIterator_Base<InElementType>(InContainer) , _Container(InContainer)`
- L191 _public function_ `TDiGraphTopologicalIterator& operator++()`
- L197 _public function_ `InElementType& operator*()`
- L202 _public function_ `InElementType* operator->() const`
- L207 _public function_ `void Reset()`
- L213 _private member_ `DiGraphType& _Container;`

#### struct `uLang::TDiGraphConstTopologicalIterator`  
`template<typename InElementType> struct TDiGraphConstTopologicalIterator : public TDiGraphTopologicalIterator_Base<InElementType>`  
_L218-251_
- inherits: `TDiGraphTopologicalIterator_Base<InElementType>`
- desc: Const iterator for directed-graph elements.
- L220 _public typedef_ `using Super = TDiGraphTopologicalIterator_Base<InElementType>;`
- L221 _public typedef_ `using DiGraphType = typename Super::DiGraphType;`
- L223 _public function_ `TDiGraphConstTopologicalIterator(const DiGraphType& InContainer) : TDiGraphTopologicalIterator_Base<InElementType>(InContainer) , _Container(InContainer)`
- L228 _public function_ `TDiGraphConstTopologicalIterator& operator++()`
- L234 _public function_ `const InElementType& operator*()`
- L239 _public function_ `const InElementType* operator->() const`
- L244 _public function_ `void Reset()`
- L250 _private member_ `const DiGraphType& _Container;`

#### struct `uLang::TDirectedGraph::FindCycles::SStackEntry`  
`struct SStackEntry`  
_L299-303_
- L301 _public member_ `int32_t _NodeIndex;`
- L302 _public member_ `int32_t _NextSuccessorIndex;`

#### struct `uLang::TDiGraphVisitor`  
`template<typename InElementType> struct TDiGraphVisitor`  
_L374-428_
- desc: Stateful helper for visiting, skipping, and revisiting directed graph nodes. Useful for performing pass, fail, retry operations on a dependency graph.
- L376 _public typedef_ `using DiGraphType = TDirectedGraph<InElementType>;`
- L377 _public typedef_ `using IteratorType = TDiGraphTopologicalIterator<InElementType>;`
- L379 _public function_ `TDiGraphVisitor(DiGraphType& DiGraph) : _GraphIterator(DiGraph)`
- L395 _public function_ `template<typename VisitorType> bool Iterate(VisitorType Visitor)` — Iterates the associated directed-graph using a specified Visitor. @param  Visitor  A functor of the form: bool(InElementType&). NOTE: Returning false from the specified Visitor will skip that node along with any of its children, enquing them for subsequent iterations. @return `true` if the full graph was processed, otherwise `false` if it subsequent `Iterate()` calls are required.
- L417 _public function_ `bool IsComplete() const`
- L422 _public function_ `void Reset()`
- L427 _public member_ `IteratorType _GraphIterator;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/Function.h` (Public)


#### enum `uLang::TIsTFunction::(anonymous)`  
`template <typename T> struct TIsTFunction`  
_L61-61_
- desc: Traits class which checks if T is a TFunction<> type.

#### struct `uLang::TIsTFunction`  
`template <typename T> struct TIsTFunction`  
_L61-61_
- desc: Traits class which checks if T is a TFunction<> type.

#### enum `uLang::TIsTFunction::(anonymous)`  
`template <typename T> struct TIsTFunction`  
_L62-62_
- desc: Traits class which checks if T is a TFunction<> type.

#### struct `uLang::TIsTFunction`  
`template <typename T> struct TIsTFunction`  
_L62-62_
- desc: Traits class which checks if T is a TFunction<> type.

#### enum `uLang::TIsTFunction::(anonymous)`  
`template <typename T> struct TIsTFunction<const T>`  
_L64-64_

#### struct `uLang::TIsTFunction`  
`template <typename T> struct TIsTFunction<const T>`  
_L64-64_

#### enum `uLang::TIsTFunction::(anonymous)`  
`template <typename T> struct TIsTFunction<const T>`  
_L65-65_

#### struct `uLang::TIsTFunction`  
`template <typename T> struct TIsTFunction<const T>`  
_L65-65_

#### enum `uLang::TIsTFunction::(anonymous)`  
`template <typename T> struct TIsTFunction<const T>`  
_L66-66_

#### struct `uLang::TIsTFunction`  
`template <typename T> struct TIsTFunction<const T>`  
_L66-66_

#### enum `uLang::TIsTUniqueFunction::(anonymous)`  
`template <typename T> struct TIsTUniqueFunction`  
_L71-71_
- desc: Traits class which checks if T is a TFunction<> type.

#### struct `uLang::TIsTUniqueFunction`  
`template <typename T> struct TIsTUniqueFunction`  
_L71-71_
- desc: Traits class which checks if T is a TFunction<> type.

#### enum `uLang::TIsTUniqueFunction::(anonymous)`  
`template <typename T> struct TIsTUniqueFunction`  
_L72-72_
- desc: Traits class which checks if T is a TFunction<> type.

#### struct `uLang::TIsTUniqueFunction`  
`template <typename T> struct TIsTUniqueFunction`  
_L72-72_
- desc: Traits class which checks if T is a TFunction<> type.

#### enum `uLang::TIsTUniqueFunction::(anonymous)`  
`template <typename T> struct TIsTUniqueFunction<const T>`  
_L74-74_

#### struct `uLang::TIsTUniqueFunction`  
`template <typename T> struct TIsTUniqueFunction<const T>`  
_L74-74_

#### enum `uLang::TIsTUniqueFunction::(anonymous)`  
`template <typename T> struct TIsTUniqueFunction<const T>`  
_L75-75_

#### struct `uLang::TIsTUniqueFunction`  
`template <typename T> struct TIsTUniqueFunction<const T>`  
_L75-75_

#### enum `uLang::TIsTUniqueFunction::(anonymous)`  
`template <typename T> struct TIsTUniqueFunction<const T>`  
_L76-76_

#### struct `uLang::TIsTUniqueFunction`  
`template <typename T> struct TIsTUniqueFunction<const T>`  
_L76-76_

#### enum `uLang::TIsTFunctionRef::(anonymous)`  
`template <typename T> struct TIsTFunctionRef`  
_L81-81_
- desc: Traits class which checks if T is a TFunctionRef<> type.

#### struct `uLang::TIsTFunctionRef`  
`template <typename T> struct TIsTFunctionRef`  
_L81-81_
- desc: Traits class which checks if T is a TFunctionRef<> type.

#### enum `uLang::TIsTFunctionRef::(anonymous)`  
`template <typename T> struct TIsTFunctionRef`  
_L82-82_
- desc: Traits class which checks if T is a TFunctionRef<> type.

#### struct `uLang::TIsTFunctionRef`  
`template <typename T> struct TIsTFunctionRef`  
_L82-82_
- desc: Traits class which checks if T is a TFunctionRef<> type.

#### enum `uLang::TIsTFunctionRef::(anonymous)`  
`template <typename T> struct TIsTFunctionRef<const T>`  
_L84-84_

#### struct `uLang::TIsTFunctionRef`  
`template <typename T> struct TIsTFunctionRef<const T>`  
_L84-84_

#### enum `uLang::TIsTFunctionRef::(anonymous)`  
`template <typename T> struct TIsTFunctionRef<const T>`  
_L85-85_

#### struct `uLang::TIsTFunctionRef`  
`template <typename T> struct TIsTFunctionRef<const T>`  
_L85-85_

#### enum `uLang::TIsTFunctionRef::(anonymous)`  
`template <typename T> struct TIsTFunctionRef<const T>`  
_L86-86_

#### struct `uLang::TIsTFunctionRef`  
`template <typename T> struct TIsTFunctionRef<const T>`  
_L86-86_

#### struct `uLang::Private::IFunction_OwnedObject`  
`struct IFunction_OwnedObject`  
_L102-123_
- desc: Common interface to a callable object owned by TFunction.
- L107 _public prototype_ `virtual void* CloneToEmptyStorage(void* Storage) const = 0;` — Creates a copy of itself into the storage and returns a pointer to the new object within it.
- L112 _public prototype_ `virtual void* GetAddress() = 0;` — Returns the address of the object.
- L117 _public prototype_ `virtual void Destroy() = 0;` — Destructor.
- L122 _public prototype_ `virtual ~IFunction_OwnedObject() = default;` — Destructor.

#### struct `uLang::Private::IFunction_OwnedObject_OnHeap`  
`template <typename T> struct IFunction_OwnedObject_OnHeap : public IFunction_OwnedObject`  
_L129-142_
- inherits: `IFunction_OwnedObject`
- desc: Common interface to a callable object owned by TFunction.
- L134 _public function_ `virtual void Destroy() override` — Destructor.
- L141 _public prototype_ `~IFunction_OwnedObject_OnHeap() override = default;`

#### struct `uLang::Private::IFunction_OwnedObject_Inline`  
`template <typename T> struct IFunction_OwnedObject_Inline : public IFunction_OwnedObject`  
_L148-159_
- inherits: `IFunction_OwnedObject`
- desc: Common interface to a callable object owned by TFunction.
- L153 _public function_ `virtual void Destroy() override` — Destructor.
- L158 _public prototype_ `~IFunction_OwnedObject_Inline() override = default;`

#### struct `uLang::Private::TFunction_OwnedObject`  
`template <typename T, bool bOnHeap> struct TFunction_OwnedObject : public #if ULANG_FUNCTION_USES_INLINE_STORAGE std::conditional_t<bOnHeap, IFunction_OwnedObject_OnHeap<T>, IFunction_OwnedObject_Inline<T>> #else IFunction_OwnedObject_OnHeap<T> #endif`  
_L162-181_
- inherits: `std::conditional_t<bOnHeap,IFunction_OwnedObject_OnHeap<T>,IFunction_OwnedObject_Inline<T>>`
- L170 _public function_ `template <typename... ArgTypes> explicit TFunction_OwnedObject(ArgTypes&&... Args) : Obj(ForwardArg<ArgTypes>(Args)...)`
- L175 _public function_ `virtual void* GetAddress() override`
- L180 _public member_ `T Obj;`

#### struct `uLang::Private::TFunction_CopyableOwnedObject`  
`template <typename T, bool bOnHeap> struct TFunction_CopyableOwnedObject final : public TFunction_OwnedObject<T, bOnHeap>`  
_L187-206_
- inherits: `TFunction_OwnedObject<T,bOnHeap>`
- desc: Implementation of IFunction_OwnedObject for a given copyable T.
- L192 _public function_ `explicit TFunction_CopyableOwnedObject(const T& InObj) : TFunction_OwnedObject<T, bOnHeap>(InObj)` — Constructor which creates its T by copying.
- L200 _public function_ `explicit TFunction_CopyableOwnedObject(T&& InObj) : TFunction_OwnedObject<T, bOnHeap>(Move(InObj))` — Constructor which creates its T by moving.
- L205 _public prototype_ `void* CloneToEmptyStorage(void* UntypedStorage) const override;`
- L392 _function_ `template <typename T, bool bOnHeap> void* TFunction_CopyableOwnedObject<T, bOnHeap>::CloneToEmptyStorage(void* UntypedStorage) const`

#### struct `uLang::Private::TFunction_UniqueOwnedObject`  
`template <typename T, bool bOnHeap> struct TFunction_UniqueOwnedObject final : public TFunction_OwnedObject<T, bOnHeap>`  
_L212-228_
- inherits: `TFunction_OwnedObject<T,bOnHeap>`
- desc: Implementation of IFunction_OwnedObject for a given non-copyable T.
- L217 _public function_ `explicit TFunction_UniqueOwnedObject(T&& InObj) : TFunction_OwnedObject<T, bOnHeap>(Move(InObj))` — Constructor which creates its T by moving.
- L222 _public function_ `void* CloneToEmptyStorage(void* Storage) const override`

#### struct `uLang::Private::TIsNullableBinding`  
`template <typename T> struct TIsNullableBinding`  
_L231-236_
- L233 _public member_ `static constexpr bool Value = std::is_pointer_v<T> || std::is_member_pointer_v<T> || TIsTFunction<T>::Value;`

#### struct `uLang::Private::TStorageOwnerType`  
`template <typename FunctorType, bool bOnHeap> struct TStorageOwnerType<FunctorType, true, bOnHeap>`  
_L259-262_
- L261 _public typedef_ `using Type = TFunction_UniqueOwnedObject<typename TDecay<FunctorType>::Type, bOnHeap>;`
- L267 _public typedef_ `using Type = TFunction_CopyableOwnedObject<typename TDecay<FunctorType>::Type, bOnHeap>;`

#### struct `uLang::Private::TStorageOwnerType`  
`template <typename FunctorType, bool bOnHeap> struct TStorageOwnerType<FunctorType, false, bOnHeap>`  
_L265-268_
- L261 _public typedef_ `using Type = TFunction_UniqueOwnedObject<typename TDecay<FunctorType>::Type, bOnHeap>;`
- L267 _public typedef_ `using Type = TFunction_CopyableOwnedObject<typename TDecay<FunctorType>::Type, bOnHeap>;`

#### struct `uLang::Private::FFunctionStorage`  
`struct FFunctionStorage`  
_L273-344_
- L275 _public function_ `FFunctionStorage() : HeapAllocation(nullptr)`
- L280 _public function_ `FFunctionStorage(FFunctionStorage&& Other) : HeapAllocation(Other.HeapAllocation)`
- L289 _public prototype_ `FFunctionStorage(const FFunctionStorage& Other) = delete;`
- L290 _public prototype_ `FFunctionStorage& operator=(FFunctionStorage&& Other) = delete;`
- L291 _public prototype_ `FFunctionStorage& operator=(const FFunctionStorage& Other) = delete;`
- L293 _public function_ `void* BindCopy(const FFunctionStorage& Other)`
- L299 _public function_ `IFunction_OwnedObject* GetBoundObject() const`
- L315 _public function_ `void* GetPtr() const` — Returns a pointer to the callable object - needed by TFunctionRefBase.
- L333 _public function_ `void Unbind()` — Destroy any owned bindings - called by TFunctionRefBase only if Bind() or BindCopy() was called.
- L339 _public member_ `void* HeapAllocation;`
- L342 _public member_ `alignas(ULANG_FUNCTION_INLINE_ALIGNMENT) uint8_t InlineAllocation[ULANG_FUNCTION_INLINE_SIZE];` — Inline storage for an owned object

#### struct `uLang::Private::TFunctionStorage`  
`template <bool bUnique> struct TFunctionStorage : FFunctionStorage`  
_L347-389_
- inherits: `FFunctionStorage`
- L349 _public prototype_ `TFunctionStorage() = default;`
- L351 _public function_ `TFunctionStorage(FFunctionStorage&& Other) : FFunctionStorage(Move(Other))`
- L357 _public function_ `template <typename FunctorType> typename TDecay<FunctorType>::Type* Bind(FunctorType&& InFunc)`

#### struct `uLang::Private::IDebugHelper`  
`struct IDebugHelper`  
_L419-422_
- desc: Helper classes to help debugger visualization.
- L421 _public prototype_ `virtual ~IDebugHelper() = 0;`
- L424 _function_ `inline IDebugHelper::~IDebugHelper()`

#### struct `uLang::Private::TDebugHelper`  
`template <typename T> struct TDebugHelper : IDebugHelper`  
_L429-432_
- inherits: `IDebugHelper`
- L431 _public member_ `T* Ptr = nullptr;`

#### struct `uLang::Private::TFunctionRefCaller`  
`template <typename Functor, typename Ret, typename... ParamTypes> struct TFunctionRefCaller<Functor, Ret (ParamTypes...)>`  
_L442-448_
- L444 _public function_ `AUTORTFM_INFER static Ret Call(void* Obj, ParamTypes&... Params)`
- L453 _public function_ `AUTORTFM_INFER static void Call(void* Obj, ParamTypes&... Params)`

#### struct `uLang::Private::TFunctionRefCaller`  
`template <typename Functor, typename... ParamTypes> struct TFunctionRefCaller<Functor, void (ParamTypes...)>`  
_L451-457_
- L444 _public function_ `AUTORTFM_INFER static Ret Call(void* Obj, ParamTypes&... Params)`
- L453 _public function_ `AUTORTFM_INFER static void Call(void* Obj, ParamTypes&... Params)`

#### struct `uLang::Private::TFunctionRefBase`  
`template <typename StorageType, typename Ret, typename... ParamTypes> struct TFunctionRefBase<StorageType, Ret (ParamTypes...)>`  
_L466-614_
- L471 _public function_ `TFunctionRefBase() : Callable(nullptr)`
- L476 _public function_ `TFunctionRefBase(TFunctionRefBase&& Other) : Callable(Other.Callable) , Storage (Move(Other.Storage))`
- L496 _public function_ `template <typename OtherStorage> TFunctionRefBase(TFunctionRefBase<OtherStorage, Ret (ParamTypes...)>&& Other) : Callable(Other.Callable) , Storage (Move(Other.Storage))`
- L516 _public function_ `template <typename OtherStorage> TFunctionRefBase(const TFunctionRefBase<OtherStorage, Ret (ParamTypes...)>& Other) : Callable(Other.Callable)`
- L535 _public function_ `TFunctionRefBase(const TFunctionRefBase& Other) : Callable(Other.Callable)`
- L556 _public function_ `template <typename FunctorType> requires (!std::is_same_v<TFunctionRefBase, typename TDecay<FunctorType>::Type>) TFunctionRefBase(FunctorType&& InFunc)`
- L575 _public prototype_ `TFunctionRefBase& operator=(TFunctionRefBase&&) = delete;`
- L576 _public prototype_ `TFunctionRefBase& operator=(const TFunctionRefBase&) = delete;`
- L579 _public function_ `void CheckCallable() const` — Move all of the assert code out of line
- L584 _public function_ `Ret operator()(ParamTypes... Params) const`
- L590 _public function_ `~TFunctionRefBase()`
- L599 _protected function_ `bool IsSet() const`
- L606 _private member_ `Ret (*Callable)(void*, ParamTypes&...) = nullptr;` — A pointer to a function which invokes the call operator on the callable object
- L608 _private member_ `StorageType Storage;`
- L612 _private member_ `TDebugHelper<void> DebugPtrStorage;` — To help debug visualizers

#### struct `uLang::Private::TFunctorReturnTypeIsCompatible`  
`template <typename FunctorType, typename Ret, typename... ParamTypes> struct TFunctorReturnTypeIsCompatible : TIsConstructible<Ret, decltype(DeclVal<FunctorType>()(DeclVal<ParamTypes>()...))>`  
_L617-620_
- inherits: `TIsConstructible<Ret,decltype(DeclVal<FunctorType>()(DeclVal<ParamTypes>()...))>`

#### struct `uLang::Private::TFunctorReturnTypeIsCompatible`  
`template <typename MemberRet, typename Class, typename Ret, typename... ParamTypes> struct TFunctorReturnTypeIsCompatible<MemberRet Class::*, Ret, ParamTypes...> : TIsConstructible<Ret, MemberRet>`  
_L623-626_
- inherits: `TIsConstructible<Ret,MemberRet>`

#### struct `uLang::Private::TFunctorReturnTypeIsCompatible`  
`template <typename MemberRet, typename Class, typename Ret, typename... ParamTypes> struct TFunctorReturnTypeIsCompatible<MemberRet Class::* const, Ret, ParamTypes...> : TIsConstructible<Ret, MemberRet>`  
_L629-632_
- inherits: `TIsConstructible<Ret,MemberRet>`

#### struct `uLang::Private::TFunctorReturnTypeIsCompatible`  
`template <typename MemberRet, typename Class, typename... MemberParamTypes, typename Ret, typename... ParamTypes> struct TFunctorReturnTypeIsCompatible<MemberRet (Class::*)(MemberParamTypes...), Ret, ParamTypes...> : TIsConstructible<Ret, MemberRet>`  
_L635-638_
- inherits: `TIsConstructible<Ret,MemberRet>`

#### struct `uLang::Private::TFunctorReturnTypeIsCompatible`  
`template <typename MemberRet, typename Class, typename... MemberParamTypes, typename Ret, typename... ParamTypes> struct TFunctorReturnTypeIsCompatible<MemberRet (Class::*)(MemberParamTypes...) const, Ret, ParamTypes...> : TIsConstructible<Ret, MemberRet>`  
_L641-644_
- inherits: `TIsConstructible<Ret,MemberRet>`

#### struct `uLang::Private::TFuncCanBindToFunctor`  
`template <typename FunctorType, typename Ret, typename... ParamTypes> struct TFuncCanBindToFunctor<Ret(ParamTypes...), FunctorType>`  
_L650-654_
- L652 _public member_ `static constexpr bool Value = TIsInvocable<FunctorType, ParamTypes...>::Value && TFunctorReturnTypeIsCompatible<FunctorType, Ret, ParamTypes...>::Value;`

#### struct `uLang::Private::TFuncCanBindToFunctor`  
`template <typename FunctorType, typename... ParamTypes> struct TFuncCanBindToFunctor<void(ParamTypes...), FunctorType> : TIsInvocable<FunctorType, ParamTypes...>`  
_L657-660_
- inherits: `TIsInvocable<FunctorType,ParamTypes...>`
- L652 _public member_ `static constexpr bool Value = TIsInvocable<FunctorType, ParamTypes...>::Value && TFunctorReturnTypeIsCompatible<FunctorType, Ret, ParamTypes...>::Value;`

#### struct `uLang::Private::FFunctionRefStoragePolicy`  
`struct FFunctionRefStoragePolicy`  
_L662-699_
- L665 _public function_ `template <typename FunctorType> typename std::remove_reference_t<FunctorType>* Bind(FunctorType&& InFunc)`
- L673 _public function_ `void* BindCopy(const FFunctionRefStoragePolicy& Other)`
- L683 _public function_ `void* GetPtr() const` — Returns a pointer to the callable object - needed by TFunctionRefBase.
- L691 _public function_ `void Unbind() const` — Destroy any owned bindings - called by TFunctionRefBase only if Bind() or BindCopy() was called.
- L698 _private member_ `void* Ptr;` — A pointer to the callable object

#### class `uLang::TFunctionRef`  
`template <typename FuncType> class TFunctionRef : public Private::TFunctionRefBase<Private::FFunctionRefStoragePolicy, FuncType>`  
_L754-777_
- inherits: `Private::TFunctionRefBase<Private::FFunctionRefStoragePolicy,FuncType>`
- desc: TFunctionRef<FuncType> A class which represents a reference to something callable.  The important part here is *reference* - if you bind it to a lambda and the lambda goes out of scope, you will be left with an invalid reference. FuncType represents a function type and so TFunctionRef should be defined as follows: // A function taking a string and float and returning int32.  Parameter names are optional. TFunctionRef<int32 (const FString& Name, float Scale)> If you also want to take ownership of the callable thing, e.g. you want to return a lambda from a function, you should use TFunction.  TFunctionRef does not concern itself with ownership because it's intended to be FAST. TFunctionRef is most useful when you want to parameterize a function with some caller-defined code without making it a template. Example: // Something.h void DoSomethingWithConvertingStringsToInts(TFunctionRef<int32 (const FString& Str)> Convert); // Something.cpp void DoSomethingWithConvertingStringsToInts(TFunctionRef<int32 (const FString& Str)> Convert) { for (const FString& Str : SomeBunchOfStrings) { int32 Int = Convert(Str); DoSomething(Int); } } // SomewhereElse.cpp #include "Something.h" void Func() { // First do something using string length DoSomethingWithConvertingStringsToInts([](const FString& Str) { return Str.Len(); }); // Then do something using string conversion DoSomethingWithConvertingStringsToInts([](const FString& Str) { int32 Result; TTypeFromString<int32>::FromString(Result, *Str); 
- L756 _private typedef_ `using Super = Private::TFunctionRefBase<Private::FFunctionRefStoragePolicy, FuncType>;`
- L764 _public function_ `template <typename FunctorType> requires (!TIsTFunctionRef<typename TDecay<FunctorType>::Type>::Value && Private::TFuncCanBindToFunctor<FuncType, typename TDecay<FunctorType>::Type>::Value) TFunctionRef(FunctorType&& InFunc) : Super(ForwardArg<FunctorType>(InFunc))` — Constructor which binds a TFunctionRef to a callable object.
- L770 _public prototype_ `TFunctionRef(const TFunctionRef&) = default;`
- L775 _public prototype_ `TFunctionRef& operator=(const TFunctionRef&) const = delete;` — We delete the assignment operators because we don't want it to be confused with being related to regular C++ reference assignment - i.e. calling the assignment operator of whatever the reference is bound to - because that's not what TFunctionRef does, nor is it even capable of doing that.
- L776 _public prototype_ `~TFunctionRef() = default;`

#### class `uLang::TFunction`  
`template <typename FuncType> class TFunction final : public Private::TFunctionRefBase<Private::TFunctionStorage<false>, FuncType>`  
_L817-888_
- inherits: `Private::TFunctionRefBase<Private::TFunctionStorage<false>,FuncType>`
- desc: TFunction<FuncType> A class which represents a copy of something callable.  FuncType represents a function type and so TFunction should be defined as follows: // A function taking a string and float and returning int32.  Parameter names are optional. TFunction<int32 (const FString& Name, float Scale)> Unlike TFunctionRef, this object is intended to be used like a UE version of std::function.  That is, it takes a copy of whatever is bound to it, meaning you can return it from functions and store them in objects without caring about the lifetime of the original object being bound. Example: // Something.h TFunction<FString (int32)> GetTransform(); // Something.cpp TFunction<FString (int32)> GetTransform(const FString& Prefix) { // Squares number and returns it as a string with the specified prefix return [=](int32 Num) { return Prefix + TEXT(": ") + TTypeToString<int32>::ToString(Num * Num); }; } // SomewhereElse.cpp #include "Something.h" void Func() { TFunction<FString (int32)> Transform = GetTransform(TEXT("Hello")); FString Result = Transform(5); // "Hello: 25" }
- L819 _private typedef_ `using Super = Private::TFunctionRefBase<Private::TFunctionStorage<false>, FuncType>;`
- L825 _public function_ `TFunction(NullPtrType = nullptr)` — Default constructor.
- L834 _public function_ `template <typename FunctorType> requires (!TIsTFunction<typename TDecay<FunctorType>::Type>::Value && Private::TFuncCanBindToFunctor<FuncType, FunctorType>::Value) TFunction(FunctorType&& InFunc) : Super(ForwardArg<FunctorType>(InFunc))` — Constructor which binds a TFunction to any function object.
- L850 _public prototype_ `TFunction(TFunction&&) = default;`
- L851 _public prototype_ `TFunction(const TFunction& Other) = default;`
- L852 _public prototype_ `~TFunction() = default;`
- L857 _public function_ `TFunction& operator=(TFunction&& Other)` — Move assignment operator.
- L866 _public function_ `TFunction& operator=(const TFunction& Other)` — Copy assignment operator.
- L876 _public function_ `void Reset()` — Removes any bound callable from the TFunction, restoring it to the default 'empty' state.
- L884 _public function_ `explicit operator bool() const` — Tests if the TFunction is callable.

#### class `uLang::TUniqueFunction`  
`template <typename FuncType> class TUniqueFunction final : public Private::TFunctionRefBase<Private::TFunctionStorage<true>, FuncType>`  
_L907-986_
- inherits: `Private::TFunctionRefBase<Private::TFunctionStorage<true>,FuncType>`
- desc: TUniqueFunction<FuncType> Used like TFunction above, but is move-only.  This allows non-copyable functors to be bound to it. Example: TUniquePtr<FThing> Thing = MakeUnique<FThing>(); TFunction      <void()> CopyableFunc = [Thing = Move(Thing)](){ Thing->DoSomething(); }; // error - lambda is not copyable TUniqueFunction<void()> MovableFunc  = [Thing = Move(Thing)](){ Thing->DoSomething(); }; // ok void Foo(TUniqueFunction<void()> Func); Foo(MovableFunc);           // error - TUniqueFunction is not copyable Foo(Move(MovableFunc)); // ok
- L909 _private typedef_ `using Super = Private::TFunctionRefBase<Private::TFunctionStorage<true>, FuncType>;`
- L915 _public function_ `TUniqueFunction(NullPtrType = nullptr)` — Default constructor.
- L925 _public function_ `TUniqueFunction(FunctorType&& InFunc) : Super(ForwardArg<FunctorType>(InFunc))`
- L944 _public function_ `TUniqueFunction(TFunction<FuncType>&& Other) : Super(Move(*(Private::TFunctionRefBase<Private::TFunctionStorage<false>, FuncType>*)&Other))` — Constructor which takes ownership of a TFunction's functor.
- L952 _public function_ `TUniqueFunction(const TFunction<FuncType>& Other) : Super(*(const Private::TFunctionRefBase<Private::TFunctionStorage<false>, FuncType>*)&Other)` — Constructor which takes ownership of a TFunction's functor.
- L960 _public function_ `TUniqueFunction& operator=(TUniqueFunction&& Other)` — Copy/move assignment operator.
- L966 _public prototype_ `TUniqueFunction(TUniqueFunction&&) = default;`
- L967 _public prototype_ `TUniqueFunction(const TUniqueFunction& Other) = delete;`
- L968 _public prototype_ `TUniqueFunction& operator=(const TUniqueFunction& Other) = delete;`
- L969 _public prototype_ `~TUniqueFunction() = default;`
- L974 _public function_ `void Reset()` — Removes any bound callable from the TFunction, restoring it to the default 'empty' state.
- L982 _public function_ `explicit operator bool() const` — Tests if the TUniqueFunction is callable.

#### Free symbols / members of external scopes

- L14 _macro_ `#define ULANG_ENABLE_TFUNCTIONREF_VISUALIZATION 1`
- L16 _macro_ `#define ULANG_ENABLE_TFUNCTIONREF_VISUALIZATION 0`
- L21 _macro_ `#define ULANG_FUNCTION_USES_INLINE_STORAGE 0` — Don't use inline storage on Win32, because that will affect the alignment of TFunction, and we can't pass extra-aligned types by value on Win32.
- L23 _macro_ `#define ULANG_FUNCTION_USES_INLINE_STORAGE 1`
- L24 _macro_ `#define ULANG_FUNCTION_INLINE_SIZE 24`
- L25 _macro_ `#define ULANG_FUNCTION_INLINE_ALIGNMENT 8`
- L28 _namespace_ `namespace uLang`
- L61 _enumerator_ `template <typename T> struct TIsTFunction { enum { Value = false }; }; template <typename T> struct TIsTFunction<TFunction<T>> { enum { Value = true }; }; template <typename T> struct TIsTFunction<const T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction< volatile T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction<const volatile T> { enum { Value = TIsTFunction<T>::Value }; }; /**` (scope `uLang::TIsTFunction::__anon833782f10103`) — Traits class which checks if T is a TFunction<> type.
- L62 _enumerator_ `template <typename T> struct TIsTFunction<TFunction<T>> { enum { Value = true }; }; template <typename T> struct TIsTFunction<const T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction< volatile T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction<const volatile T> { enum { Value = TIsTFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunction<> type.` (scope `uLang::TIsTFunction::__anon833782f10203`)
- L64 _enumerator_ `template <typename T> struct TIsTFunction<const T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction< volatile T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction<const volatile T> { enum { Value = TIsTFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunction<> type. */ template <typename T> struct TIsTUniqueFunction { enum { Value = false }; };` (scope `uLang::TIsTFunction::__anon833782f10303`)
- L65 _enumerator_ `template <typename T> struct TIsTFunction< volatile T> { enum { Value = TIsTFunction<T>::Value }; }; template <typename T> struct TIsTFunction<const volatile T> { enum { Value = TIsTFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunction<> type. */ template <typename T> struct TIsTUniqueFunction { enum { Value = false }; }; template <typename T> struct TIsTUniqueFunction<TUniqueFunction<T>> { enum { Value = true }; };` (scope `uLang::TIsTFunction::__anon833782f10403`)
- L66 _enumerator_ `template <typename T> struct TIsTFunction<const volatile T> { enum { Value = TIsTFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunction<> type. */ template <typename T> struct TIsTUniqueFunction { enum { Value = false }; }; template <typename T> struct TIsTUniqueFunction<TUniqueFunction<T>> { enum { Value = true }; };` (scope `uLang::TIsTFunction::__anon833782f10503`)
- L71 _enumerator_ `template <typename T> struct TIsTUniqueFunction { enum { Value = false }; }; template <typename T> struct TIsTUniqueFunction<TUniqueFunction<T>> { enum { Value = true }; }; template <typename T> struct TIsTUniqueFunction<const T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction< volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction<const volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; /**` (scope `uLang::TIsTUniqueFunction::__anon833782f10603`) — Traits class which checks if T is a TFunction<> type.
- L72 _enumerator_ `template <typename T> struct TIsTUniqueFunction<TUniqueFunction<T>> { enum { Value = true }; }; template <typename T> struct TIsTUniqueFunction<const T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction< volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction<const volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunctionRef<> type.` (scope `uLang::TIsTUniqueFunction::__anon833782f10703`)
- L74 _enumerator_ `template <typename T> struct TIsTUniqueFunction<const T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction< volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction<const volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunctionRef<> type. */ template <typename T> struct TIsTFunctionRef { enum { Value = false }; };` (scope `uLang::TIsTUniqueFunction::__anon833782f10803`)
- L75 _enumerator_ `template <typename T> struct TIsTUniqueFunction< volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; template <typename T> struct TIsTUniqueFunction<const volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunctionRef<> type. */ template <typename T> struct TIsTFunctionRef { enum { Value = false }; }; template <typename T> struct TIsTFunctionRef<TFunctionRef<T>> { enum { Value = true }; };` (scope `uLang::TIsTUniqueFunction::__anon833782f10903`)
- L76 _enumerator_ `template <typename T> struct TIsTUniqueFunction<const volatile T> { enum { Value = TIsTUniqueFunction<T>::Value }; }; /** * Traits class which checks if T is a TFunctionRef<> type. */ template <typename T> struct TIsTFunctionRef { enum { Value = false }; }; template <typename T> struct TIsTFunctionRef<TFunctionRef<T>> { enum { Value = true }; };` (scope `uLang::TIsTUniqueFunction::__anon833782f10a03`)
- L81 _enumerator_ `template <typename T> struct TIsTFunctionRef { enum { Value = false }; }; template <typename T> struct TIsTFunctionRef<TFunctionRef<T>> { enum { Value = true }; }; template <typename T> struct TIsTFunctionRef<const T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef< volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef<const volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; /**` (scope `uLang::TIsTFunctionRef::__anon833782f10b03`) — Traits class which checks if T is a TFunctionRef<> type.
- L82 _enumerator_ `template <typename T> struct TIsTFunctionRef<TFunctionRef<T>> { enum { Value = true }; }; template <typename T> struct TIsTFunctionRef<const T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef< volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef<const volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; /** * Private implementation details of TFunction and TFunctionRef.` (scope `uLang::TIsTFunctionRef::__anon833782f10c03`)
- L84 _enumerator_ `template <typename T> struct TIsTFunctionRef<const T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef< volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef<const volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; /** * Private implementation details of TFunction and TFunctionRef. */ namespace Private` (scope `uLang::TIsTFunctionRef::__anon833782f10d03`)
- L85 _enumerator_ `template <typename T> struct TIsTFunctionRef< volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; template <typename T> struct TIsTFunctionRef<const volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; /** * Private implementation details of TFunction and TFunctionRef. */ namespace Private {` (scope `uLang::TIsTFunctionRef::__anon833782f10e03`)
- L86 _enumerator_ `template <typename T> struct TIsTFunctionRef<const volatile T> { enum { Value = TIsTFunctionRef<T>::Value }; }; /** * Private implementation details of TFunction and TFunctionRef. */ namespace Private { template <typename T, bool bOnHeap>` (scope `uLang::TIsTFunctionRef::__anon833782f10f03`)
- L91 _namespace_ `namespace Private` (scope `uLang`)
- L240 _function_ `template <typename T> requires (TIsNullableBinding<T>::Value) bool IsBound(const T& Func)` (scope `uLang::Private`)
- L249 _function_ `template <typename T> requires (!TIsNullableBinding<T>::Value) bool IsBound(const T& Func)` (scope `uLang::Private`)
- L271 _typedef_ `template <typename FunctorType, bool bUnique, bool bOnHeap> using TStorageOwnerTypeT = typename TStorageOwnerType<FunctorType, bUnique, bOnHeap>::Type;` (scope `uLang::Private`)
- L370 _typedef_ `using OwnedType = TStorageOwnerTypeT<FunctorType, bUnique, !bUseInline>;` (scope `uLang::Private::TFunctionStorage::Bind`)
- L560 _typedef_ `using DecayedFunctorType = typename TRemovePointer<decltype(Binding)>::Type;` (scope `uLang::Private::TFunctionRefBase::TFunctionRefBase`)
- L992 _function_ `template <typename FuncType> bool operator==(NullPtrType, const TFunction<FuncType>& Func)` (scope `uLang`) — Nullptr equality operator.
- L1001 _function_ `template <typename FuncType> bool operator==(const TFunction<FuncType>& Func, NullPtrType)` (scope `uLang`) — Nullptr equality operator.
- L1010 _function_ `template <typename FuncType> bool operator!=(NullPtrType, const TFunction<FuncType>& Func)` (scope `uLang`) — Nullptr inequality operator.
- L1019 _function_ `template <typename FuncType> bool operator!=(const TFunction<FuncType>& Func, NullPtrType)` (scope `uLang`) — Nullptr inequality operator.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/HashTable.h` (Public)


#### struct `uLang::TKeyValuePair`  
`template<class KeyType, class ValueType> struct TKeyValuePair`  
_L18-25_
- L20 _public member_ `KeyType _Key;`
- L21 _public member_ `ValueType _Value;`
- L23 _public function_ `bool operator==(const KeyType& Key) const`
- L24 _public function_ `operator const KeyType&() const`

#### class `uLang::THashTable`  
`template<class KeyType, class KeyValueType, class HashTraits, class AllocatorType, typename... AllocatorArgsType> class THashTable`  
_L31-564_
- desc: A Robin-Hood hash table Inspired by https://www.sebastiansylvan.com/post/robin-hood-hashing-should-be-your-default-hash-table-implementation/ and http://codecapsule.com/2013/11/17/robin-hood-hashing-backward-shift-deletion/
- L34 _public function_ `THashTable(AllocatorArgsType&&... AllocatorArgs) : _Allocator(ForwardArg<AllocatorArgsType>(AllocatorArgs)...)`
- L39 _public prototype_ `THashTable(const THashTable& Other) = delete;`
- L41 _public function_ `THashTable(THashTable&& Other)`
- L46 _public function_ `THashTable& operator=(THashTable Other)`
- L52 _public function_ `void Swap(THashTable& Other)`
- L60 _public function_ `~THashTable()`
- L69 _public function_ `uint32_t Num() const`
- L74 _public function_ `bool Contains(const KeyType& Key) const`
- L79 _public function_ `KeyValueType* Find(const KeyType& Key)`
- L85 _public function_ `const KeyValueType* Find(const KeyType& Key) const`
- L100 _public function_ `template <typename Predicate> const KeyValueType* FindByPredicate(Predicate Pred) const` — Finds an key-value pair which matches a predicate functor. The predicate must take a `TKeyValuePair<KeyType, ValueType>`. @param Pred The functor to apply to each key-value pair. @returns Pointer to the first key-value pair for which the predicate returns true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L122 _public function_ `template <typename Predicate> KeyValueType* FindByPredicate(Predicate Pred)` — Finds a key-value pair which matches a predicate functor. The predicate must take a `TKeyValuePair<KeyType, ValueType>`. @param Pred The functor to apply to each key-value pair. `true`, or `nullptr` if none is found. @returns Pointer to the first key-value pair for which the predicate returns true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L135 _public function_ `KeyValueType& Insert(const KeyValueType& KeyValue)`
- L140 _public function_ `KeyValueType& Insert(KeyValueType&& KeyValue)`
- L145 _public function_ `KeyValueType& FindOrInsert(KeyValueType&& KeyValue)`
- L157 _public function_ `bool Remove(const KeyType& Key)`
- L227 _public function_ `bool IsEmpty() const`
- L232 _public function_ `void Empty()`
- L342 _public function_ `Iterator<false> begin()`
- L351 _public function_ `Iterator<false> end()`
- L356 _public function_ `Iterator<true> begin() const`
- L361 _public function_ `Iterator<false> end() const`
- L366 _public function_ `Iterator<true> cbegin() const`
- L375 _public function_ `Iterator<true> cend() const`
- L382 _protected member_ `static constexpr uint64_t MaxLoadFactorNumerator = 7;` — Load factor = what fraction of entries are occupied
- L383 _protected member_ `static constexpr uint64_t MaxLoadFactorDenominator = 8;`
- L392 _protected function_ `static uint32_t ComputeNonZeroHash(const KeyType& Key)` — Hash values in the table must not be zero
- L399 _protected function_ `uint32_t DesiredPos(uint32_t Hash) const` — Get desired position for an entry given a hash value
- L405 _protected function_ `uint32_t ProbeDistance(uint32_t Hash, uint32_t Pos) const` — Get probe distance of an entry with given hash and position in entry array
- L410 _protected function_ `KeyValueType& InsertInternal(KeyValueType&& KeyValue)`
- L428 _protected function_ `uint32_t InsertInternal(uint32_t Hash, KeyValueType&& Value, bool* bAlreadyExists)` — Create a new entry Use Robin Hood mechanism to rearrange entries to minimize probe distance Returns position of new entry
- L485 _protected function_ `uint32_t Lookup(const KeyType& Key) const` — Look up a key, return its index
- L519 _protected function_ `void Allocate()` — Allocate memory according to currently set _NumEntries
- L535 _protected function_ `void Grow()` — Double the size of the table
- L557 _protected member_ `SEntry* _Entries{};`
- L558 _protected member_ `uint32_t _NumEntries{};` — How many entries we have allocated in total
- L559 _protected member_ `uint32_t _NumOccupied{};` — How many entries are actually occupied
- L563 _protected member_ `AllocatorType _Allocator;` — How to allocate the memory This allocator can be 0 in size

#### class `uLang::THashTable::Iterator`  
`template <bool bConst> class Iterator`  
_L257-340_
- L260 _public typedef_ `using iterator_category = std::forward_iterator_tag;`
- L261 _public typedef_ `using value_type = KeyValueType;`
- L262 _public typedef_ `using pointer = typename std::conditional_t<bConst, const KeyValueType*, KeyValueType*>;`
- L263 _public typedef_ `using reference = typename std::conditional_t<bConst, const KeyValueType&, KeyValueType&>;`
- L266 _private function_ `explicit Iterator(SEntry* InEntry, SEntry* InEnd) : _CurrentEntry(InEntry), _End(InEnd)`
- L273 _public function_ `Iterator& operator++()` — Prefix increment overload.
- L284 _public function_ `Iterator operator++(int)` — Postfix increment overload.
- L291 _public function_ `bool operator!=(const Iterator& Other) const`
- L297 _public function_ `bool operator==(const Iterator& Other) const`
- L303 _public function_ `template <bool _bConst = bConst> std::enable_if_t<!_bConst, reference> operator*()`
- L309 _public function_ `template <bool _bConst = bConst> std::enable_if_t<_bConst, reference> operator*() const`
- L315 _public function_ `template <bool _bConst = bConst> std::enable_if_t<!_bConst, pointer> operator->()`
- L321 _public function_ `template <bool _bConst = bConst> std::enable_if_t<_bConst, pointer> operator->() const`
- L327 _private function_ `void EnsureOccupiedOrEnd()`
- L336 _private member_ `SEntry* _CurrentEntry;`
- L337 _private member_ `SEntry* _End;`

#### struct `uLang::THashTable::SEntry`  
`struct SEntry`  
_L385-389_
- L387 _public member_ `uint32_t _Hash;` — 0 means unused
- L388 _public member_ `KeyValueType _KeyValue;` — Some value, e.g. index into some external array

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace uLang`
- L160 _function_ `` (scope `uLang::THashTable::Remove`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/HashTraits.h` (Public)


#### struct `uLang::TDefaultHashTraits`  
`template<class KeyType> struct TDefaultHashTraits`  
_L66-69_
- L68 _public function_ `static uint32_t GetKeyHash(const KeyType& Key)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L10 _function_ `inline uint32_t GetTypeHash(const void* Key)` (scope `uLang`) — Default hash function for pointers.
- L22 _function_ `inline uint32_t MurmurFinalize32(uint32_t Hash)` (scope `uLang`)
- L40 _function_ `[[nodiscard]] inline constexpr uint32_t HashCombineFast(uint32_t A, uint32_t B)` (scope `uLang`) — Combines two hash values to get a third. Note - this function is not commutative. WARNING!  This function is subject to change and should only be used for creating combined hash values which don't leave the running process, e.g. GetTypeHash() overloads.
- L45 _function_ `inline uint32_t GetTypeHash(uint32_t I)` (scope `uLang`)
- L50 _function_ `inline uint32_t GetTypeHash(int32_t I)` (scope `uLang`)
- L55 _function_ `inline uint32_t GetTypeHash(uint64_t I)` (scope `uLang`)
- L60 _function_ `inline uint32_t GetTypeHash(int64_t I)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/Map.h` (Public)


#### class `uLang::TMapG`  
`template<class KeyType, class ValueType, class HashTraits, class AllocatorType, typename... AllocatorArgsType> class TMapG`  
_L11-107_
- L13 _private typedef_ `using PairType = TKeyValuePair<KeyType, ValueType>;`
- L16 _public function_ `TMapG(AllocatorArgsType&&... AllocatorArgs) : _HashTable(ForwardArg<AllocatorArgsType>(AllocatorArgs)...)`
- L18 _public function_ `uint32_t Num() const`
- L19 _public function_ `bool Contains(const KeyType& Key) const`
- L20 _public function_ `ValueType* Find(const KeyType& Key)`
- L21 _public function_ `const ValueType* Find(const KeyType& Key) const`
- L24 _public function_ `template <typename Predicate> const PairType* FindByPredicate(Predicate Pred) const`
- L30 _public function_ `template <typename Predicate> PairType* FindByPredicate(Predicate Pred)`
- L35 _public function_ `PairType& Insert(const KeyType& Key, ValueType&& Value)`
- L36 _public function_ `PairType& Insert(KeyType&& Key, const ValueType& Value)`
- L37 _public function_ `PairType& Insert(const KeyType& Key, const ValueType& Value)`
- L38 _public function_ `PairType& Insert(KeyType&& Key, ValueType&& Value)`
- L41 _public function_ `template <typename OtherKeyType, typename OtherValueType> PairType& FindOrInsert(OtherKeyType&& Key, OtherValueType&& Value)`
- L47 _public function_ `template <typename OtherKeyType> PairType& FindOrInsert(OtherKeyType&& Key)`
- L52 _public function_ `bool Remove(const KeyType& Key)`
- L53 _public function_ `void Empty()`
- L55 _public function_ `ValueType& operator[](const KeyType& Key)`
- L71 _public typedef_ `using HashTableType = THashTable<KeyType, PairType, HashTraits, AllocatorType, AllocatorArgsType...>;`
- L72 _public typedef_ `using ConstIterator = typename HashTableType::template Iterator<true>;`
- L73 _public typedef_ `using Iterator = typename HashTableType::template Iterator<false>;`
- L75 _public function_ `Iterator begin()`
- L80 _public function_ `Iterator end()`
- L85 _public function_ `ConstIterator begin() const`
- L90 _public function_ `ConstIterator end() const`
- L95 _public function_ `ConstIterator cbegin() const`
- L100 _public function_ `ConstIterator cend() const`
- L106 _protected member_ `HashTableType _HashTable;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L111 _typedef_ `template<class KeyType, class ValueType> using TMap = TMapG<KeyType, ValueType, TDefaultHashTraits<KeyType>, CHeapRawAllocator>;` (scope `uLang`) — A map that assumes that the KeyType has a method `GetTypeHash`(), and that allocates memory from the heap

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/ObserverPointer.h` (Public)


#### class `uLang::CObservedMix`  
`class CObservedMix`  
_L23-36_
- desc: A convenience mixin class, storing an observer id Derive from this if you want an object to be observed by a TObserverPointer
- L27 _public function_ `CObservedMix() : _ObserverId(ObserverId_Null)`
- L28 _public function_ `~CObservedMix()`
- L34 _private member_ `mutable EObserverId _ObserverId;`

#### class `uLang::TOPtr`  
`template<class ObjectType> class TOPtr`  
_L42-128_
- desc: Observer pointer using a unique id to tell if an object has gone stale
- L48 _public function_ `TOPtr() : _Object(nullptr), _ObserverId(ObserverId_Null)`
- L49 _public function_ `TOPtr(const TOPtr & Other) : _Object(Other._Object), _ObserverId(Other._ObserverId)`
- L52 _public function_ `template<class OtherObjectType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TOPtr(const TOPtr<OtherObjectType> & Other) : _Object(Other._Object), _ObserverId(Other._ObserverId)`
- L55 _public function_ `template<class OtherObjectType, bool OtherAllowNull, class AllocatorType, typename... AllocatorArgsType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TOPtr(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & SharedPtr) : _Object(SharedPtr.Get()), _ObserverId(GetId(SharedPtr.Get(), SharedPtr.GetAllocator()))`
- L58 _public function_ `template<class OtherObjectType, bool OtherAllowNull, class AllocatorType, typename... AllocatorArgsType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TOPtr(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & UniquePtr) : _Object(UniquePtr.Get()), _ObserverId(GetId(UniquePtr.Get(), UniquePtr.GetAllocator()))`
- L62 _public function_ `TOPtr & operator=(const TOPtr & Other)`
- L65 _public function_ `template<class OtherObjectType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TOPtr & operator=(const TOPtr<OtherObjectType> & Other)`
- L68 _public function_ `template<class OtherObjectType, bool OtherAllowNull, class AllocatorType, typename... AllocatorArgsType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TOPtr & operator=(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & SharedPtr)`
- L71 _public function_ `template<class OtherObjectType, bool OtherAllowNull, class AllocatorType, typename... AllocatorArgsType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TOPtr & operator=(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & UniquePtr)`
- L75 _public function_ `operator ObjectType*() const`
- L76 _public function_ `ObjectType & operator*() const`
- L77 _public function_ `ObjectType * operator->() const`
- L78 _public function_ `ObjectType * Get() const`
- L79 _public function_ `void Reset()`
- L83 _public function_ `bool operator==(const TOPtr & Other) const`
- L84 _public function_ `bool operator!=(const TOPtr & Other) const`
- L86 _public function_ `template<class OtherObjectType> bool operator==(const TOPtr<OtherObjectType> & Other) const`
- L88 _public function_ `template<class OtherObjectType> bool operator!=(const TOPtr<OtherObjectType> & Other) const`
- L90 _public function_ `template<class OtherObjectType> bool operator==(OtherObjectType * Object) const`
- L92 _public function_ `template<class OtherObjectType> bool operator!=(OtherObjectType * Object) const`
- L96 _public function_ `bool IsValid() const`
- L97 _public function_ `bool IsStale() const`
- L98 _public function_ `bool IsNull() const`
- L99 _public function_ `bool IsSet() const`
- L100 _public function_ `operator bool() const`
- L101 _public function_ `bool operator !() const`
- L105 _public function_ `EObserverId GetObserverId() const`
- L111 _protected function_ `template<class AllocatorType> static EObserverId GetId(const ObjectType * Object, const AllocatorType & Allocator)`
- L123 _protected member_ `ObjectType * _Object;` — Direct pointer to actual object - might be stale It is only valid if its _ObserverId is the same as _ObserverId in this smart pointer
- L126 _protected member_ `EObserverId _ObserverId;` — Unique id shared between the object and its id smart pointers

#### Free symbols / members of external scopes

- L9 _macro_ `#define ULANG_CHECK_OBSERVER_POINTERS ULANG_DO_CHECK`
- L12 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/PointerSetHelper.h` (Public)


#### class `uLang::TPointerSetHelper`  
`template<typename ElementType, typename KeyType> class TPointerSetHelper`  
_L14-73_
- desc: Useful helper function for maintaining sets of pointers
- L18 _public typedef_ `using PointerStorageType = TArray<ElementType *>;`
- L21 _public function_ `static int32_t GetUpperBound(const PointerStorageType& This, const KeyType& Key)` — Merge other sorted array into this array
- L47 _public function_ `static void Merge(PointerStorageType& This, const PointerStorageType& Other)` — Merge other sorted array into this array

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/Queue.h` (Public)


#### enum `uLang::EQueueMode`  
`enum class EQueueMode : int8_t`  
_L13-17_
- desc: Concurrent queue modes.
- L15 _public enumerator_ `MultipleProducersSingleConsumer`
- L16 _public enumerator_ `SingleProducerSingleConsumer`

#### class `uLang::TQueueG`  
`template <typename InElementType, EQueueMode Mode = EQueueMode::SingleProducerSingleConsumer> class TQueueG`  
_L27-193_
- desc: Simple templated queue following Unreal's `TQueue` implementation using a lock-free linked list. We're doing this instead of using a simple array/etc. since it matches Unreal's implementation 1:1 apart from usage of the standard library for atomics. TODO: (yiliang.siew) Allow for custom allocators as the rest of `uLang` does. TODO: (yiliang.siew) See if some of the memory ordering requirements can be relaxed. For now since it guarantees an `MFENCE` instruction on x86-64 arch. Unreal issues a `_mm_sfence` intrinsic, which I'm not sure if I can guarantee via `std::atomic`.
- L30 _public function_ `TQueueG()`
- L35 _public function_ `~TQueueG()`
- L52 _public function_ `bool Enqueue(const InElementType& InElement)` — Adds an item to the head of the queue. @param InElement 	The item to add. @return 			`true` if the item was added, `false` otherwise.
- L76 _public function_ `bool Enqueue(const InElementType&& InElement)`
- L107 _public function_ `bool Dequeue(InElementType& OutElement)` — Removes and returns the item from the tail of the queue. @param OutElement 	The item from the tail of the queue. @return 			`true` if a value was returned, `false` if the queue was empty.
- L127 _public function_ `bool Pop()` — Removes the item from the tail of the queue. @return true if a value was removed, false if the queue was empty.
- L145 _public function_ `void Empty()` — Empty the queue, discarding all items.
- L158 _public function_ `bool IsEmpty()` — Checks whether the queue is empty. @return 	`true` if the queue is empty, `false` otherwise.
- L182 _private member_ `std::atomic<TNode*> Head;` — Holds a pointer to the head of the list.
- L185 _private member_ `TNode* Tail;` — Holds a pointer to the tail of the list.
- L189 _protected prototype_ `TQueueG(const TQueueG&) = delete;` — Hidden copy constructor.
- L192 _protected prototype_ `TQueueG& operator=(const TQueueG&) = delete;` — Hidden assignment operator.

#### struct `uLang::TQueueG::TNode`  
`struct TNode`  
_L165-179_
- desc: Structure for the internal linked list.
- L167 _public function_ `TNode() : Next(nullptr)`
- L170 _public function_ `explicit TNode(const InElementType& InElement) : Next(nullptr), Element(InElement)`
- L174 _public function_ `explicit TNode(const InElementType&& InElement) : Next(nullptr), Element(std::move(InElement))` — @overload move constructor.
- L177 _public member_ `std::atomic<TNode*> Next;`
- L178 _public member_ `InElementType Element;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L197 _typedef_ `template <typename InElementType> using TQueue = TQueueG<InElementType>;` (scope `uLang`) — Queue that allocates elements on the heap.
- L201 _typedef_ `template <typename InElementType> using TMQueue = TQueueG<InElementType, EQueueMode::MultipleProducersSingleConsumer>;` (scope `uLang`) — Queue that supports multiple producers adding elements that are allocated on the heap.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/RangeView.h` (Public)


#### struct `uLang::TRangeView`  
`template <typename TFirst, typename TLast> struct TRangeView`  
_L8-59_
- L10 _public member_ `TFirst First;`
- L11 _public member_ `TLast Last;`
- L13 _public function_ `TRangeView() : First() , Last()`
- L19 _public function_ `template <typename TRange> explicit TRangeView(TRange&& Arg) : TRangeView(Arg.begin(), Arg.end())`
- L23 _public function_ `TRangeView(TFirst InFirst, TLast InLast) : First(InFirst) , Last(InLast)`
- L28 _public function_ `TFirst begin() const`
- L33 _public function_ `TLast end() const`
- L38 _public function_ `bool IsEmpty() const`
- L43 _public function_ `int32_t Num() const`
- L49 _public function_ `template <typename TArg> decltype(auto) operator[](TArg&& Arg)`
- L55 _public function_ `template <typename TArg> decltype(auto) operator[](TArg&& Arg) const`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace uLang`
- L62 _prototype_ `template <typename T> TRangeView(T&& Arg) -> TRangeView<decltype(Arg.begin()), decltype(Arg.end())>;` (scope `uLang`)
- L65 _function_ `template <typename TFirst, typename TLast> TFirst begin(TRangeView<TFirst, TLast> const& Range)` (scope `uLang`)
- L71 _function_ `template <typename TFirst, typename TLast> TLast end(TRangeView<TFirst, TLast> const& Range)` (scope `uLang`)
- L77 _function_ `template <typename T> TRangeView<T*, T*> SingletonRangeView(T& Arg)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/Set.h` (Public)


#### class `uLang::TSetG`  
`template<class ElementType, class KeyType, class HashTraits, class AllocatorType, typename... AllocatorArgsType> class TSetG`  
_L11-82_
- L14 _public function_ `explicit TSetG(AllocatorArgsType&&... AllocatorArgs) : _HashTable(Move(AllocatorArgs)...)`
- L16 _public function_ `uint32_t Num() const`
- L17 _public function_ `bool Contains(const ElementType& Element) const`
- L18 _public function_ `ElementType* Find(const KeyType& Key)`
- L19 _public function_ `const ElementType* Find(const KeyType& Key) const`
- L22 _public function_ `template <typename Predicate> const ElementType* FindByPredicate(Predicate Pred) const`
- L28 _public function_ `template <typename Predicate> ElementType* FindByPredicate(Predicate Pred)`
- L34 _public function_ `template <typename ArgType> ElementType& Insert(ArgType&& Arg)`
- L39 _public function_ `ElementType& FindOrInsert(ElementType&& Element)`
- L40 _public function_ `bool Remove(const ElementType& Element)`
- L42 _public function_ `bool IsEmpty() const`
- L44 _public function_ `void Empty()`
- L46 _public typedef_ `using HashTableType = THashTable<ElementType, ElementType, HashTraits, AllocatorType, AllocatorArgsType...>;`
- L47 _public typedef_ `using ConstIterator = typename HashTableType::template Iterator<true>;`
- L48 _public typedef_ `using Iterator = typename HashTableType::template Iterator<false>;`
- L50 _public function_ `Iterator begin()`
- L55 _public function_ `Iterator end()`
- L60 _public function_ `ConstIterator begin() const`
- L65 _public function_ `ConstIterator end() const`
- L70 _public function_ `ConstIterator cbegin() const`
- L75 _public function_ `ConstIterator cend() const`
- L81 _protected member_ `HashTableType _HashTable;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L86 _typedef_ `template<class ElementType, class KeyType = ElementType> using TSet = TSetG<ElementType, KeyType, TDefaultHashTraits<ElementType>, CHeapRawAllocator>;` (scope `uLang`) — A set that assumes that the KeyType has a method `GetTypeHash()`, and that allocates memory from the heap

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/SharedPointer.h` (Public)


#### class `uLang::CSharedMix`  
`class CSharedMix`  
_L27-62_
- desc: Mixin super/base class for objects that need to be reference counted. As a mixin it avoids the (minor) speed cost of virtual function calls and the virtual table memory cost (1 pointer).  It uses the coding technique known as "mix-in from above"/"Curiously Recurring Template Pattern".
- L31 _public function_ `CSharedMix() : _RefCount(0)`
- L32 _public prototype_ `virtual ~CSharedMix();`
- L34 _public prototype_ `CSharedMix(const CSharedMix & Other) = delete;` — Do not copy
- L35 _public prototype_ `CSharedMix & operator=(const CSharedMix & Other) = delete;` — Do not assign
- L37 _public function_ `uint32_t GetRefCount() const`
- L41 _protected function_ `template<class ObjectType> static TSPtrG<ObjectType, false, CHeapRawAllocator> SharedThis(ObjectType* This)`
- L47 _protected function_ `template<class ObjectType> static TSPtrG<const ObjectType, false, CHeapRawAllocator> SharedThis(const ObjectType* This)`
- L57 _private function_ `void Reference() const`
- L58 _private prototype_ `bool Dereference() const;`
- L61 _private member_ `mutable uint32_t _RefCount;` — Number of references to this object
- L322 _function_ `inline bool CSharedMix::Dereference() const` — Decrements the reference count to this object and if the reference count becomes 0 return true

#### class `uLang::TSPtrG`  
`template<class ObjectType, bool AllowNull, class AllocatorType, typename... AllocatorArgsType> class AUTORTFM_INFER TSPtrG`  
_L72-290_
- desc: TSPtr is a convenience class - it wraps around a pointer to an object that is a subclass of CSharedMix [or any class that has the methods: Reference() & Dereference()] and acts just like a regular pointer except that it automatically references and dereferences the object as needed. The AllocatorType must provide the methods void * Allocate(size_t) and void Deallocate(void *)
- L78 _public function_ `TSPtrG(NullPtrType NullPtr = nullptr) : _Object(nullptr), _Allocator(DefaultInit), _ReleaseFunc(nullptr)`
- L79 _public function_ `TSPtrG(const TSPtrG & Other) : _Object(Other._Object), _Allocator(Other._Allocator)`
- L82 _public function_ `template<class OtherObjectType, bool OtherAllowNull> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> && (AllowNull || !OtherAllowNull)) TSPtrG(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) : _Object(Other._Object), _Allocator(Other._Allocator)`
- L83 _public function_ `TSPtrG(TSPtrG && Other) : _Object(Other._Object), _Allocator(Other._Allocator)` — Note: We null here even when OtherAllowNull==false since 99% likely will be destructed immediately after anyway
- L86 _public function_ `template<class OtherObjectType, bool OtherAllowNull> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> && (AllowNull || !OtherAllowNull)) TSPtrG(TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> && Other) : _Object(Other._Object), _Allocator(Other._Allocator)` — Note: We null here even when OtherAllowNull==false since 99% likely will be destructed immediately after anyway
- L87 _public function_ `~TSPtrG()`
- L90 _public function_ `template<typename... CtorArgsType> TSPtrG& SetNew(CtorArgsType&&... CtorArgs)`
- L92 _public function_ `template<typename... CtorArgsType> static TSPtrG New(AllocatorArgsType&&... AllocatorArgs, CtorArgsType&&... CtorArgs)`
- L96 _public function_ `TSPtrG & operator=(NullPtrType)`
- L97 _public function_ `TSPtrG & operator=(const TSPtrG & Other)`
- L100 _public function_ `template<class OtherObjectType, bool OtherAllowNull> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> && (AllowNull || !OtherAllowNull)) TSPtrG & operator=(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other)`
- L101 _public function_ `TSPtrG & operator=(TSPtrG && Other)`
- L104 _public function_ `template<class OtherObjectType, bool OtherAllowNull> requires (std::is_convertible_v<OtherObjectType*, ObjectType*>) TSPtrG & operator=(TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> && Other)`
- L108 _public function_ `operator ObjectType*() const`
- L109 _public function_ `ObjectType & operator*() const`
- L110 _public function_ `ObjectType * operator->() const`
- L111 _public function_ `ObjectType * Get() const`
- L112 _public function_ `const AllocatorType & GetAllocator() const`
- L113 _public function_ `void Reset()`
- L115 _public function_ `TSPtrG<ObjectType, false, AllocatorType, AllocatorArgsType...>& AsRef()&`
- L121 _public function_ `TSPtrG<ObjectType, false, AllocatorType, AllocatorArgsType...> AsRef()&&`
- L127 _public function_ `const TSPtrG<ObjectType, false, AllocatorType, AllocatorArgsType...>& AsRef() const&`
- L136 _public function_ `template<class OtherObjectType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> || std::is_convertible_v<ObjectType*, OtherObjectType*>) TSPtrG<OtherObjectType, AllowNull, AllocatorType, AllocatorArgsType...>& As()`
- L139 _public function_ `template<class OtherObjectType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> || std::is_convertible_v<ObjectType*, OtherObjectType*>) const TSPtrG<OtherObjectType, AllowNull, AllocatorType, AllocatorArgsType...>& As() const`
- L143 _public function_ `bool operator==(NullPtrType) const`
- L144 _public function_ `bool operator!=(NullPtrType) const`
- L145 _public function_ `bool operator==(const TSPtrG & Other) const`
- L147 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator==(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L149 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator==(OtherObjectType * Object) const`
- L150 _public function_ `bool operator!=(const TSPtrG & Other) const`
- L152 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator!=(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L154 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator!=(OtherObjectType * Object) const`
- L155 _public function_ `bool operator< (const TSPtrG & Other) const`
- L157 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator< (const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L159 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator< (OtherObjectType * Object) const`
- L160 _public function_ `bool operator> (const TSPtrG & Other) const`
- L162 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator> (const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L164 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator> (OtherObjectType * Object) const`
- L168 _public function_ `operator bool()`
- L169 _public function_ `operator bool() const`
- L170 _public function_ `bool operator!() const`
- L171 _public function_ `bool IsValid() const`
- L179 _public function_ `template <typename FuncType, typename... ArgTypes> TSPtrG Map(FuncType&& Func, ArgTypes&&... Args) &&` — Composability methods
- L186 _public function_ `TSPtrG(ObjectType& Object, const AllocatorType& Allocator) : _Object(&Object) , _Allocator(Allocator) , _ReleaseFunc(nullptr)`
- L200 _protected function_ `TSPtrG(ObjectType* Object, const AllocatorType& Allocator) : _Object(Object) , _Allocator(Allocator) , _ReleaseFunc(nullptr)`
- L217 _protected function_ `template<class OtherObjectType, bool OtherAllowNull> TSPtrG & AssignCopy(const TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other)`
- L240 _protected function_ `template<class OtherObjectType, bool OtherAllowNull> TSPtrG & AssignMove(TSPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> && Other)`
- L257 _protected function_ `void EnableRelease()` — Set the release function pointer to a valid value
- L271 _protected function_ `void Release()` — Let go of our object
- L278 _protected member_ `ObjectType * _Object;` — Pointer to original object
- L282 _protected member_ `AllocatorType _Allocator;` — How to deallocate the object This allocator can be 0 in size
- L288 _protected typedef_ `using ReleaseFuncType = void(*)(ObjectType *, const AllocatorType &);` — Indirection to keep knowledge about ObjectType out of default constructor and destructor so that TSPtrG can be forward declared with an incomplete ObjectType argument The price we pay is 8 more bytes of memory, indirect function call on each release, and that we have to (re-)initialize this function pointer in all methods that can set the pointer to something non-null
- L289 _protected member_ `ReleaseFuncType _ReleaseFunc;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ULANGCORE_API`
- L13 _namespace_ `namespace uLang`
- L175 _function_ `friend void Swap(TSPtrG& A, TSPtrG& B)` (scope `uLang`) — Needed to avoid ambiguous function resolution between uLang and UnrealTemplate.h versions of Swap
- L260 _function_ `` (scope `uLang::TSPtrG::EnableRelease`)
- L293 _function_ `template<class ObjectType> decltype(auto) SharedThis(ObjectType&& This)` (scope `uLang`)
- L300 _typedef_ `template<class ObjectType> using TSPtr = TSPtrG<ObjectType, true, CHeapRawAllocator>;` (scope `uLang`) — Shared pointer that allocates object on the heap
- L304 _typedef_ `template<class ObjectType> using TSRef = TSPtrG<ObjectType, false, CHeapRawAllocator>;` (scope `uLang`) — Shared reference that allocates object on the heap
- L308 _typedef_ `template<class ObjectType> using TSPtrA = TSPtrG<ObjectType, true, CInstancedRawAllocator, CAllocatorInstance *>;` (scope `uLang`) — Shared pointer that allocates object using a given allocator instance
- L312 _typedef_ `template<class ObjectType> using TSRefA = TSPtrG<ObjectType, false, CInstancedRawAllocator, CAllocatorInstance *>;` (scope `uLang`) — Shared reference that allocates object using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/SharedPointerArray.h` (Public)


#### class `uLang::TSPtrArrayG`  
`template<typename InElementType, bool AllowNull, typename InElementAllocatorType, typename... RawAllocatorArgsType> class TSPtrArrayG`  
_L20-1134_
- desc: Templated dynamic array of shared pointers to elements
- L27 _public typedef_ `using ElementType = InElementType;`
- L28 _public typedef_ `using ElementAllocatorType = InElementAllocatorType;`
- L29 _public typedef_ `using PointerType = TSPtrG<ElementType, AllowNull, typename InElementAllocatorType::RawAllocatorType, RawAllocatorArgsType...>;`
- L30 _public typedef_ `using PointerStorageType = TArrayG<ElementType *, InElementAllocatorType, RawAllocatorArgsType...>;`
- L35 _public function_ `TSPtrArrayG(RawAllocatorArgsType&&... RawAllocatorArgs) : _PointerStorage(uLang::ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...) , _DereferenceFunc(nullptr)` — Constructor
- L45 _public function_ `template<typename OtherElementType, bool OtherAllowNull> requires (std::is_convertible_v<OtherElementType*, InElementType*> && (AllowNull || !OtherAllowNull)) TSPtrArrayG(std::initializer_list<TSPtrG<OtherElementType, OtherAllowNull, typename InElementAllocatorType::RawAllocatorType, RawAllocatorArgsType...>> InitList, RawAllocatorArgsType&&... RawAllocatorArgs) : _PointerStorage(uLang::ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...) , _DereferenceFunc(nullptr)` — Initializer list constructor
- L62 _public function_ `template<typename OtherElementType, bool OtherAllowNull> requires (std::is_convertible_v<OtherElementType*, InElementType*> && (AllowNull || !OtherAllowNull)) TSPtrArrayG(const TSPtrArrayG<OtherElementType, OtherAllowNull, InElementAllocatorType, RawAllocatorArgsType...>& Other) : _PointerStorage(Other._PointerStorage)` — Implicitly casting copy-ish constructor. @param Other The source array to copy.
- L74 _public function_ `TSPtrArrayG(const TSPtrArrayG& Other) : _PointerStorage(Other._PointerStorage)` — Copy constructor. @param Other The source array to copy.
- L105 _public function_ `template<typename OtherElementType, bool OtherAllowNull> requires (std::is_convertible_v<OtherElementType*, InElementType*> && (AllowNull || !OtherAllowNull)) TSPtrArrayG& operator=(const TSPtrArrayG<OtherElementType, OtherAllowNull, InElementAllocatorType, RawAllocatorArgsType...>& Other)` — Implicitly casting copying assignment-ish operator. First deletes all currently contained elements and then copies from other array. @param Other The source array to assign from.
- L122 _public function_ `TSPtrArrayG& operator=(const TSPtrArrayG& Other)` — Copying assignment operator. First deletes all currently contained elements and then copies from other array. @param Other The source array to assign from.
- L140 _public function_ `template<typename OtherElementType, bool OtherAllowNull> requires (std::is_convertible_v<OtherElementType*, InElementType*> && (AllowNull || !OtherAllowNull)) TSPtrArrayG(TSPtrArrayG<OtherElementType, OtherAllowNull, InElementAllocatorType, RawAllocatorArgsType...>&& Other) : _PointerStorage(ForwardArg<PointerStorageType>(Other._PointerStorage))` — Implicitly casting move-ish constructor. @param Other Array to move from.
- L151 _public function_ `TSPtrArrayG(TSPtrArrayG&& Other) : _PointerStorage(ForwardArg<PointerStorageType>(Other._PointerStorage))` — Move constructor. @param Other Array to move from.
- L166 _public function_ `template<class OtherElementType, bool OtherAllowNull> requires (std::is_convertible_v<OtherElementType*, InElementType*> && (AllowNull || !OtherAllowNull)) TSPtrArrayG(TSPtrArrayG<OtherElementType, OtherAllowNull, InElementAllocatorType, RawAllocatorArgsType...>&& Other, int32_t ExtraSlack) : _PointerStorage(ForwardArg<PointerStorageType>(Other._PointerStorage), ExtraSlack)` — Implicitly casting move-ish constructor with extra slack. @param Other Array to move from. @param ExtraSlack Tells how much extra pointer memory should be preallocated at the end of the array in the number of elements.
- L179 _public function_ `template<class OtherElementType, bool OtherAllowNull> requires (std::is_convertible_v<OtherElementType*, InElementType*> && (AllowNull || !OtherAllowNull)) TSPtrArrayG& operator=(TSPtrArrayG<OtherElementType, OtherAllowNull, InElementAllocatorType, RawAllocatorArgsType...>&& Other)` — Implicitly casting move assignment operator. @param Other Array to assign and move from.
- L195 _public function_ `TSPtrArrayG& operator=(TSPtrArrayG&& Other)` — Move assignment operator. @param Other Array to assign and move from.
- L207 _public function_ `~TSPtrArrayG()` — Destructor.
- L217 _public function_ `int32_t GetSlack() const` — Returns the amount of slack in this array in elements. @see Num, Shrink
- L228 _public function_ `bool IsValidIndex(int32_t Index) const` — Tests if index is valid, i.e. greater than or equal to zero, and less than the number of elements in the array. @param Index Index to test. @returns True if index is valid. False otherwise.
- L239 _public function_ `int32_t Num() const` — Returns number of elements in array. @returns Number of elements in array. @see GetSlack
- L250 _public function_ `int32_t Max() const` — Returns maximum number of elements in array. @returns Maximum number of elements in array. @see GetSlack
- L261 _public function_ `bool IsEmpty() const` — Returns true if no elements in array @returns true if no elements in array or false if one or more elements. @see IsFull, Num
- L272 _public function_ `bool IsFilled() const` — Returns true if any elements in array @returns true if one or more elements in array or false no elements. @see IsEmpty, Num
- L280 _public function_ `PointerType operator[](int32_t Index) const` — Array bracket operator. Returns shared pointer to element at given index.
- L291 _public function_ `PointerType Pop(bool bAllowShrinking = true)` — Pops element from the array. @param bAllowShrinking If this call allows shrinking of the array during element remove. @returns Popped element.
- L306 _public function_ `void Push(const PointerType & Item)` — Pushes element into the array. @param Item Item to push.
- L322 _public function_ `PointerType First() const` — Returns the first element. @returns Reference to the first element. @see Last, Pop, Push
- L333 _public function_ `PointerType Top() const` — Returns the top element, i.e. the last one. @returns Reference to the top element. @see Pop, Push
- L344 _public function_ `PointerType Last(int32_t IndexFromTheEnd = 0) const` — Returns n-th last element from the array. @param IndexFromTheEnd (Optional) Index from the end of array (default = 0). @returns Reference to n-th last element from the array.
- L354 _public function_ `void Shrink()` — Shrinks the array's used pointer memory to smallest possible to store elements currently in it. @see Slack
- L367 _public function_ `bool Find(const ElementType* Item, int32_t& Index) const` — Finds element within the array (by address comparison). @param Item Item to look for. @param Index Will contain the found index. @returns True if found. False otherwise. @see FindLast, FindLastByPredicate
- L371 _public function_ `bool Find(const PointerType& Item, int32_t& Index) const`
- L384 _public function_ `int32_t Find(const ElementType* Item) const` — Finds element within the array (by address comparison). @param Item Item to look for. @returns Index of the found element. IndexNone otherwise. @see FindLast, FindLastByPredicate
- L388 _public function_ `int32_t Find(const PointerType& Item) const`
- L401 _public function_ `bool FindLast(const PointerType & Item, int32_t& Index) const` — Finds element within the array starting from the end (by address comparison). @param Item Item to look for. @param Index Output parameter. Found index. @returns True if found. False otherwise. @see Find, FindLastByPredicate
- L412 _public function_ `int32_t FindLast(const PointerType & Item) const` — Finds element within the array starting from the end (by address comparison). @param Item Item to look for. @returns Index of the found element. IndexNone otherwise.
- L425 _public function_ `template <typename Predicate> int32_t FindLastByPredicate(Predicate Pred, int32_t Count) const` — Searches an initial subrange of the array for the last occurrence of an element which matches the specified predicate. @param Pred Predicate taking const pointer to array element and returns true if element matches search criteria, false otherwise. @param Count The number of elements from the front of the array through which to search. @returns Index of the found element. IndexNone otherwise.
- L437 _public function_ `template <typename Predicate> int32_t FindLastByPredicate(Predicate Pred) const` — Searches the array for the last occurrence of an element which matches the specified predicate. @param Pred Predicate taking const pointer to array element and returns true if element matches search criteria, false otherwise. @returns Index of the found element. IndexNone otherwise.
- L450 _public function_ `template <typename KeyType> int32_t IndexOfByKey(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Index to the first matching element, or IndexNone if none is found.
- L462 _public function_ `template <typename Predicate> int32_t IndexOfByPredicate(Predicate Pred) const` — Finds an item by predicate. @param Pred The predicate to match, taking const pointer to array element. @returns Index to the first matching element, or IndexNone if none is found.
- L476 _public function_ `template <typename KeyType> TOptional<PointerType> FindByKey(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Pointer to the first matching element, or nullptr if none is found. @see Find
- L495 _public function_ `template <typename Predicate> TOptional<PointerType> FindByPredicate(Predicate Pred) const` — Finds an element which matches a predicate functor. @param Pred The functor to apply to each element, taking const pointer to array element. @returns Pointer to the first element for which the predicate returns true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L512 _public function_ `bool Contains(const PointerType& Pointer) const` — Checks if this array contains the exact pointer. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L524 _public function_ `template <typename ComparisonType> bool ContainsByKey(const ComparisonType& Key) const` — Checks if this array contains the element. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L537 _public function_ `template <typename Predicate> bool ContainsByPredicate(Predicate Pred) const` — Checks if this array contains element for which the predicate is true. @param Predicate to use, taking const pointer to array element @returns True if found. False otherwise. @see Contains, Find
- L554 _public function_ `void InsertZeroed(int32_t Index, int32_t Count = 1)` — Inserts a given number of zeroed elements into the array at given location. Caution, InsertZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param Index Tells where to insert the new elements. @param Count Number of elements to add. @see Insert, InsertUninitialized, InsertDefaulted
- L567 _public function_ `int32_t Insert(const TSPtrArrayG& Items, const int32_t InIndex)` — Inserts given elements into the array at given location. @param Items Array of elements to insert. @param InIndex Tells where to insert the new elements. @returns Location at which the item was inserted.
- L582 _public function_ `int32_t Insert(TSPtrArrayG&& Items, const int32_t InIndex)` — Inserts given elements into the array at given location. @param Items Array of elements to insert. @param InIndex Tells where to insert the new elements. @returns Location at which the item was inserted.
- L596 _public function_ `int32_t Insert(const PointerType& Item, int32_t Index)` — Inserts a given element into the array at given location. @param Item The element to insert. @param Index Tells where to insert the new elements. @returns Location at which the insert was done. @see Add, Remove
- L615 _public function_ `PointerType RemoveAt(int32_t Index)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true. @returns The element removed from the array.
- L636 _public function_ `template <typename CountType> void RemoveAt(int32_t Index, CountType Count, bool bAllowShrinking = true)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L654 _public function_ `void RemoveAtSwap(int32_t Index)` — Removes an element (or elements) at given location optionally shrinking the array. This version is much more efficient than RemoveAt (O(Count) instead of O(ArrayNum)), but does not preserve the order. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L673 _public function_ `template <typename CountType> void RemoveAtSwap(int32_t Index, CountType Count, bool bAllowShrinking = true)` — Removes an element (or elements) at given location optionally shrinking the array. This version is much more efficient than RemoveAt (O(Count) instead of O(ArrayNum)), but does not preserve the order. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L687 _public function_ `int32_t ReplaceAt(const PointerType& Item, int32_t Index)` — Replaces a given element at a given location. @param Item The element to insert. @param Index Tells where to insert the new element. @returns Location at which the replacement was done. @see Add, Remove
- L705 _public function_ `void Reset(int32_t NewSize = 0)` — Same as empty, but doesn't change memory allocations, unless the new size is larger than the current array. It calls the destructors on held items if needed and then zeros the ArrayNum. @param NewSize The expected usage size after calling this function.
- L716 _public function_ `void Empty(int32_t Slack = 0)` — Empties the array. It calls the destructors on held items if needed. @param Slack (Optional) The expected usage size after empty operation. Default is 0.
- L727 _public function_ `void SetNumZeroed(int32_t NewNum, bool bAllowShrinking = true)` — Resizes array to given number of elements. New elements will be zeroed. @param NewNum New size of the array.
- L744 _public function_ `void Append(TSPtrArrayG& Source)` — Appends the specified array to this array. Allocator changing version. @param Source The array to append. @see Add, Insert
- L757 _public function_ `void Append(TSPtrArrayG&& Source)` — Appends the specified array to this array. @param Source The array to append. @see Add, Insert
- L771 _public function_ `TSPtrArrayG& operator+=(TSPtrArrayG&& Other)` — Appends the specified array to this array. Cannot append to self. Move semantics version. @param Other The array to append.
- L783 _public function_ `TSPtrArrayG& operator+=(const TSPtrArrayG& Other)` — Appends the specified array to this array. Cannot append to self. @param Other The array to append.
- L796 _public function_ `template <typename... CtorArgsType> int32_t AddNew(CtorArgsType&&... CtorArgs)` — Constructs a new item at the end of the array, possibly reallocating the whole array to fit. @param Args  The arguments to forward to the constructor of the new item. @return      Index to the new item
- L811 _public function_ `template <typename... CtorArgsType> void InsertNew(int32_t Index, CtorArgsType&&... CtorArgs)` — Constructs a new item at a specified index, possibly reallocating the whole array to fit. @param Index The index to add the item at. @param Args  The arguments to forward to the constructor of the new item.
- L828 _public function_ `int32_t Add(const PointerType& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. Move semantics version. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L849 _public function_ `int32_t AddZeroed()` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. The new item will be zeroed. Caution, AddZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @return Index to the first of the new items. @see Add, AddDefaulted, AddUnique, Append, Insert
- L862 _public function_ `int32_t AddUnique(const PointerType& Item)` — Adds unique element to array if it doesn't exist. @param Args Item to add. @returns Index of the element in the array. @see Add, AddDefaulted, AddZeroed, Append, Insert
- L880 _public function_ `void Reserve(int32_t Number)` — Reserves memory such that the array can contain at least Number elements. @param Number The number of elements that the array should be able to contain after allocation. @see Shrink
- L893 _public function_ `int32_t RemoveSingle(const PointerType& Item)` — Removes the first occurrence of the specified item in the array, maintaining order but not indices. @param Item The item to remove. @returns The number of items removed. For RemoveSingleItem, this is always either 0 or 1. @see Add, Insert, Remove, RemoveAll, RemoveAllSwap
- L911 _public function_ `int32_t Remove(const PointerType& Item)` — Removes as many instances of Item as there are in the array, maintaining order but not indices. @param Item Item to remove from array. @returns Number of removed elements. @see Add, Insert, RemoveAll, RemoveAllSwap, RemoveSingle, RemoveSwap
- L930 _public function_ `template <typename Predicate> int32_t RemoveAll(const Predicate& Pred)` — Remove all instances that match the predicate, maintaining order but not indices Optimized to work with runs of matches/non-matches @param Pred Predicate, taking const pointer to array element @returns Number of removed elements. @see Add, Insert, RemoveAllSwap, RemoveSingle, RemoveSwap
- L951 _public function_ `template <class Predicate> void RemoveAllSwap(const Predicate& Pred, bool bAllowShrinking = true)` — Remove all instances that match the predicate @param Pred Predicate, taking const pointer to array element @see Remove, RemoveSingle, RemoveSingleSwap, RemoveSwap
- L974 _public function_ `int32_t RemoveSingleSwap(const PointerType& Item, bool bAllowShrinking = true)` — Removes the first occurrence of the specified item in the array. This version is much more efficient O(Count) instead of O(ArrayNum), but does not preserve the order @param Item The item to remove @returns The number of items removed. For RemoveSingleItem, this is always either 0 or 1. @see Add, Insert, Remove, RemoveAll, RemoveAllSwap, RemoveSwap
- L994 _public function_ `int32_t RemoveSwap(const PointerType& Item)` — Removes item from the array. This version is much more efficient, because it uses RemoveAtSwap internally which is O(Count) instead of RemoveAt which is O(ArrayNum), but does not preserve the order. @returns Number of elements removed. @see Add, Insert, Remove, RemoveAll, RemoveAllSwap
- L1007 _public function_ `void Sort()` — Sorts the array assuming < operator is defined for ElementType.
- L1018 _public function_ `template <class PredicateType> void Sort(const PredicateType& Predicate)` — Sorts the array using user define predicate class. @param Predicate Predicate instance or lambda, taking const pointer to array element
- L1028 _public function_ `template<class OtherElementType, bool OtherAllowNull = AllowNull> requires ((std::is_convertible_v<OtherElementType*, ElementType*> || std::is_convertible_v<ElementType*, OtherElementType*>) && (AllowNull == OtherAllowNull || OtherAllowNull)) TSPtrArrayG<OtherElementType, OtherAllowNull, ElementAllocatorType, RawAllocatorArgsType...>& As()` — Casts TSPtrArray<T>& -> TSPtrArray<U>& if T is castable to U.
- L1053 _public function_ `friend Iterator operator+(const Iterator& Left, int32_t Right)`
- L1054 _public function_ `friend Iterator operator+(int32_t Left, const Iterator& Right)`
- L1055 _public function_ `friend int32_t operator-(const Iterator& Left, const Iterator& Right)`
- L1064 _public function_ `Iterator begin()`
- L1065 _public function_ `Iterator begin() const`
- L1066 _public function_ `Iterator end()`
- L1067 _public function_ `Iterator end() const`
- L1072 _protected function_ `void EnableDereference()` — Set the release function pointer to a valid value
- L1086 _protected function_ `void Dereference(int32_t Index)` — Decrement reference count on an element
- L1093 _protected function_ `void ReferenceRange(int32_t BeginIndex, int32_t EndIndex)` — Increment reference count on a range of elements
- L1106 _protected function_ `void DereferenceRange(int32_t BeginIndex, int32_t EndIndex)` — Decrement reference count on a range of elements
- L1115 _protected function_ `void ReferenceAll()` — Increment reference count on all elements
- L1121 _protected function_ `void DereferenceAll()` — Decrement reference count on all elements. Delete elements whose reference count reaches zero.
- L1126 _protected member_ `PointerStorageType _PointerStorage;`
- L1132 _protected typedef_ `using DereferenceFuncType = void(*)(ElementType *, const typename ElementAllocatorType::RawAllocatorType &);` — Indirection to keep knowledge about ElementType out of default constructor and destructor so that TSPtrArrayG can be forward declared with an incomplete ElementType argument The price we pay is 8 more bytes of memory, indirect function call on each dereference, and that we have to (re-)initialize this function pointer in all methods that can make an empty array non-empty
- L1133 _protected member_ `DereferenceFuncType _DereferenceFunc;`

#### class `uLang::TSPtrArrayG::Iterator`  
`class Iterator`  
_L1039-1062_
- L1042 _public function_ `Iterator() : _Item(nullptr)` — -V730
- L1043 _public function_ `Iterator(ElementType * const * Item, const typename InElementAllocatorType::RawAllocatorType & Allocator) : _Item(Item)` — -V730
- L1044 _public prototype_ `~Iterator() = default;`
- L1045 _public function_ `const PointerType& operator*() const`
- L1046 _public function_ `const ElementType* operator->() const`
- L1047 _public function_ `bool operator==(const Iterator & Other) const`
- L1048 _public function_ `bool operator!=(const Iterator & Other) const`
- L1049 _public function_ `Iterator& operator++()`
- L1050 _public function_ `Iterator operator++(int)`
- L1051 _public function_ `Iterator& operator--()`
- L1052 _public function_ `Iterator operator--(int)`
- L1058 _protected function_ `PointerType& Ptr() const`
- L1060 _protected member_ `ElementType * const * _Item;`
- L1061 _protected member_ `TTypeCompatibleBytes<PointerType> _DummyPtr;` — Dummy shared pointer to avoid copy & unnecessary reference/dereference of object

#### struct `uLang::TIsZeroConstructType`  
`template <typename ElementType, bool AllowNull, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsZeroConstructType<TSPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L1154-1157_
- L1156 _public member_ `static constexpr bool Value = TAllocatorTraits<ElementAllocatorType>::IsZeroConstruct;`

#### struct `uLang::TContainerTraits`  
`template <typename ElementType, bool AllowNull, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TContainerTraits<TSPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>> : public TContainerTraitsBase<TSPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L1160-1164_
- inherits: `TContainerTraitsBase<TSPtrArrayG<ElementType,AllowNull,ElementAllocatorType,RawAllocatorArgsType...>>`
- L1163 _public member_ `static constexpr bool MoveWillEmptyContainer = TAllocatorTraits<ElementAllocatorType>::SupportsMove;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename ElementType, bool AllowNull, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsContiguousContainer<TSPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L1167-1170_
- L1169 _public member_ `static constexpr bool Value = true;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace uLang`
- L452 _function_ `return _PointerStorage.IndexOfByPredicate([=](ElementType * Item) -> bool { return *Item == Key; });` (scope `uLang::TSPtrArrayG::IndexOfByKey`)
- L478 _function_ `ElementType * const * Element = _PointerStorage.FindByPredicate([=](ElementType * Item) -> bool { return *Item == Key; });` (scope `uLang::TSPtrArrayG::FindByKey`)
- L514 _function_ `return _PointerStorage.FindByPredicate([=](ElementType * Item) -> bool { return Item == Pointer.Get(); }) != nullptr;` (scope `uLang::TSPtrArrayG::Contains`)
- L526 _function_ `return _PointerStorage.FindByPredicate([=](ElementType * Item) -> bool { return *Item == Key; }) != nullptr;` (scope `uLang::TSPtrArrayG::ContainsByKey`)
- L933 _function_ `return _PointerStorage.RemoveAll([&](ElementType* Item) -> bool { bool RemoveIt = Pred(Item); if (RemoveIt && Item->Dereference()) { Item->~ElementType(); RawAllocator.Deallocate(Item); } return RemoveIt; });` (scope `uLang::TSPtrArrayG::RemoveAll`)
- L954 _function_ `return _PointerStorage.RemoveAllSwap([&](ElementType* Item) -> bool { bool RemoveIt = Pred(Item); if (RemoveIt && Item->Dereference()) { Item->~ElementType(); RawAllocator.Deallocate(Item); } return RemoveIt; });` (scope `uLang::TSPtrArrayG::RemoveAllSwap`)
- L1075 _function_ `` (scope `uLang::TSPtrArrayG::EnableDereference`)
- L1138 _typedef_ `template<typename ElementType> using TSPtrArray = TSPtrArrayG<ElementType, true, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Array of shared pointers that allocates elements on the heap
- L1142 _typedef_ `template<typename ElementType> using TSRefArray = TSPtrArrayG<ElementType, false, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Array of shared references that allocates elements on the heap
- L1146 _typedef_ `template<typename ElementType> using TSPtrArrayA = TSPtrArrayG<ElementType, true, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Array of shared pointers that allocates object using a given allocator instance
- L1150 _typedef_ `template<typename ElementType> using TSRefArrayA = TSPtrArrayG<ElementType, false, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Array of shared references that allocates object using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/SharedPointerSet.h` (Public)


#### class `uLang::TSPtrSetG`  
`template<typename InElementType, bool AllowNull, typename InKeyType, typename InElementAllocatorType, typename... RawAllocatorArgsType> class TSPtrSetG : protected TSPtrArrayG<InElementType, AllowNull, InElementAllocatorType, RawAllocatorArgsType...>`  
_L17-267_
- inherits: `TSPtrArrayG<InElementType,AllowNull,InElementAllocatorType,RawAllocatorArgsType...>`
- desc: Templated dynamic set of shared pointers to elements This is similar to TSPtrArrayG, plus elements are always kept in sorted order and looked up via binary search
- L23 _private typedef_ `using Super = TSPtrArrayG<InElementType, AllowNull, InElementAllocatorType, RawAllocatorArgsType...>;`
- L25 _private typedef_ `using Helper = TPointerSetHelper<InElementType, InKeyType>;`
- L29 _public typedef_ `using KeyType = InKeyType;`
- L37 _public function_ `TSPtrSetG(RawAllocatorArgsType&&... RawAllocatorArgs) : Super(uLang::ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — Constructor
- L46 _public function_ `TSPtrSetG(const TSPtrSetG & Other) : Super(Other)` — Copy constructor. @param Other The source array to copy.
- L58 _public function_ `TSPtrSetG(const TSPtrSetG & Other, int32_t ExtraSlack) : Super(Other, ExtraSlack)` — Copy constructor. @param Other The source array to copy. @param ExtraSlack Tells how much extra memory should be preallocated at the end of the array in the number of elements.
- L68 _public function_ `TSPtrSetG(TSPtrSetG && Other) : Super(ForwardArg<Super>(Other))` — Move constructor. @param Other Array to move from.
- L80 _public function_ `TSPtrSetG(TSPtrSetG && Other, int32_t ExtraSlack) : Super(ForwardArg<Super>(Other), ExtraSlack)` — Move constructor. @param Other Array to move from. @param ExtraSlack Tells how much extra pointer memory should be preallocated at the end of the array in the number of elements.
- L88 _public function_ `TSPtrSetG& operator=(const TSPtrSetG& Other)` — Assignment operators.
- L89 _public function_ `TSPtrSetG& operator=(TSPtrSetG&& Other)`
- L118 _public function_ `int32_t IndexOf(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator< and operator== for the comparison). @param Key The key to search by. @returns Index to the first matching element, or IndexNone if none is found.
- L132 _public function_ `TOptional<PointerType> Find(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Pointer to the first matching element, or nullptr if none is found. @see Find
- L152 _public function_ `bool Contains(const KeyType& Key) const` — Checks if this array contains the element. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L166 _public function_ `void Append(const TSPtrSetG& Other)` — Appends the specified array to this array. Allocator changing version. @param Source The array to append. @see Add, Insert
- L179 _public function_ `void Append(TSPtrSetG&& Other)` — Appends the specified array to this array. @param Source The array to append. @see Add, Insert
- L194 _public function_ `TSPtrSetG& operator+=(TSPtrSetG&& Other)` — Appends the specified array to this array. Cannot append to self. Move semantics version. @param Other The array to append.
- L206 _public function_ `TSPtrSetG& operator+=(const TSPtrSetG& Other)` — Appends the specified array to this array. Cannot append to self. @param Other The array to append.
- L219 _public function_ `template <typename... CtorArgsType> int32_t AddNew(CtorArgsType&&... CtorArgs)` — Constructs a new item at the end of the array, possibly reallocating the whole array to fit. @param Args  The arguments to forward to the constructor of the new item. @return      Index to the new item
- L239 _public function_ `int32_t Add(const PointerType& Item)` — Adds a new item. Must not exist yet. Move semantics version. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L254 _public function_ `int32_t Remove(const KeyType& Key)` — Removes as many instances of Item as there are in the array, maintaining order but not indices. @param Item Item to remove from array. @returns Number of removed elements. @see Add, Insert, RemoveAll, RemoveAllSwap, RemoveSingle, RemoveSwap

#### struct `uLang::TIsZeroConstructType`  
`template <typename ElementType, bool AllowNull, typename KeyType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsZeroConstructType<TSPtrSetG<ElementType, AllowNull, KeyType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L287-290_
- L289 _public member_ `static constexpr bool Value = TAllocatorTraits<ElementAllocatorType>::IsZeroConstruct;`

#### struct `uLang::TContainerTraits`  
`template <typename ElementType, bool AllowNull, typename KeyType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TContainerTraits<TSPtrSetG<ElementType, AllowNull, KeyType, ElementAllocatorType, RawAllocatorArgsType...>> : public TContainerTraitsBase<TSPtrSetG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L293-297_
- inherits: `TContainerTraitsBase<TSPtrSetG<ElementType,AllowNull,ElementAllocatorType,RawAllocatorArgsType...>>`
- L296 _public member_ `static constexpr bool MoveWillEmptyContainer = TAllocatorTraits<ElementAllocatorType>::SupportsMove;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename ElementType, bool AllowNull, typename KeyType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsContiguousContainer<TSPtrSetG<ElementType, AllowNull, KeyType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L300-303_
- L302 _public member_ `static constexpr bool Value = true;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L271 _typedef_ `template<typename ElementType, typename KeyType> using TSPtrSet = TSPtrSetG<ElementType, true, KeyType, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Set of shared pointers that allocates elements on the heap
- L275 _typedef_ `template<typename ElementType, typename KeyType> using TSRefSet = TSPtrSetG<ElementType, false, KeyType, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Set of shared references that allocates elements on the heap
- L279 _typedef_ `template<typename ElementType, typename KeyType> using TSPtrSetA = TSPtrSetG<ElementType, true, KeyType, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Set of shared pointers that allocates object using a given allocator instance
- L283 _typedef_ `template<typename ElementType, typename KeyType> using TSRefSetA = TSPtrSetG<ElementType, false, KeyType, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Set of shared references that allocates object using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/UniquePointer.h` (Public)


#### class `uLang::TUPtrG`  
`template <typename ObjectType, bool AllowNull, class AllocatorType, typename... AllocatorArgsType> class TUPtrG`  
_L14-150_
- L20 _public function_ `TUPtrG(NullPtrType NullPtr = nullptr) : _Object(nullptr), _Allocator(DefaultInit)`
- L21 _public function_ `TUPtrG(TUPtrG && Other) : _Object(Other._Object), _Allocator(Other._Allocator)` — Note: We null here even when AllowNull==false since 99% likely will be destructed immediately after anyway
- L24 _public function_ `template<class OtherObjectType, bool OtherAllowNull> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> && (AllowNull || !OtherAllowNull)) TUPtrG(TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> && Other) : _Object(Other._Object), _Allocator(Other._Allocator)` — Note: We null here even when AllowNull==false since 99% likely will be destructed immediately after anyway
- L25 _public function_ `~TUPtrG()`
- L28 _public function_ `template<typename... CtorArgsType> TUPtrG& SetNew(CtorArgsType&&... CtorArgs)`
- L30 _public function_ `template<typename... CtorArgsType> static TUPtrG New(AllocatorArgsType&&... AllocatorArgs, CtorArgsType&&... CtorArgs)`
- L34 _public prototype_ `TUPtrG(const TUPtrG &) = delete;`
- L35 _public prototype_ `template<class OtherObjectType, bool OtherAllowNull> TUPtrG(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) = delete;`
- L36 _public prototype_ `template<class OtherObjectType, bool OtherAllowNull> TUPtrG(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) = delete;`
- L37 _public prototype_ `template<class OtherObjectType, bool OtherAllowNull> TUPtrG & operator=(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) = delete;`
- L41 _public function_ `TUPtrG & operator=(NullPtrType)`
- L42 _public function_ `TUPtrG & operator=(TUPtrG && Other)`
- L45 _public function_ `template<class OtherObjectType, bool OtherAllowNull> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> && (AllowNull || !OtherAllowNull)) TUPtrG & operator=(TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> && Other)`
- L49 _public function_ `operator ObjectType*() const`
- L50 _public function_ `ObjectType & operator*() const`
- L51 _public function_ `ObjectType * operator->() const`
- L52 _public function_ `ObjectType * Get() const`
- L53 _public function_ `const AllocatorType & GetAllocator() const`
- L54 _public function_ `void Reset()`
- L56 _public function_ `TUPtrG<ObjectType, false, AllocatorType, AllocatorArgsType...>& AsRef() &`
- L62 _public function_ `const TUPtrG<ObjectType, false, AllocatorType, AllocatorArgsType...>&& AsRef() &&`
- L68 _public function_ `const TUPtrG<ObjectType, false, AllocatorType, AllocatorArgsType...>& AsRef() const&`
- L76 _public function_ `template<class OtherObjectType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> || std::is_convertible_v<ObjectType*, OtherObjectType*>) TUPtrG<OtherObjectType, AllowNull, AllocatorType, AllocatorArgsType...>& As()`
- L79 _public function_ `template<class OtherObjectType> requires (std::is_convertible_v<OtherObjectType*, ObjectType*> || std::is_convertible_v<ObjectType*, OtherObjectType*>) const TUPtrG<OtherObjectType, AllowNull, AllocatorType, AllocatorArgsType...>& As() const`
- L83 _public function_ `bool operator==(NullPtrType) const`
- L84 _public function_ `bool operator==(const TUPtrG & Other) const`
- L86 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator==(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L88 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator==(OtherObjectType * Object) const`
- L89 _public function_ `bool operator!=(const TUPtrG & Other) const`
- L91 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator!=(const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L93 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator!=(OtherObjectType * Object) const`
- L94 _public function_ `bool operator< (const TUPtrG & Other) const`
- L96 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator< (const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L98 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator< (OtherObjectType * Object) const`
- L99 _public function_ `bool operator> (const TUPtrG & Other) const`
- L101 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator> (const TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> & Other) const`
- L103 _public function_ `template<class OtherObjectType, bool OtherAllowNull> bool operator> (OtherObjectType * Object) const`
- L107 _public function_ `operator bool()`
- L108 _public function_ `operator bool() const`
- L109 _public function_ `bool operator!() const`
- L110 _public function_ `bool IsValid() const`
- L116 _private function_ `TUPtrG(ObjectType * Object, const AllocatorType & Allocator) : _Object(Object) , _Allocator(Allocator)`
- L123 _private function_ `template<class OtherObjectType, bool OtherAllowNull> TUPtrG & AssignMove(TUPtrG<OtherObjectType, OtherAllowNull, AllocatorType, AllocatorArgsType...> && Other)`
- L138 _private function_ `void Release()` — Let go of our object
- L145 _private member_ `ObjectType* _Object;` — Pointer to original object
- L149 _private member_ `AllocatorType _Allocator;` — How to deallocate the object This allocator can be 0 in size

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L154 _typedef_ `template<class ObjectType> using TUPtr = TUPtrG<ObjectType, true, CHeapRawAllocator>;` (scope `uLang`) — Unique pointer that allocates object on the heap
- L158 _typedef_ `template<class ObjectType> using TURef = TUPtrG<ObjectType, false, CHeapRawAllocator>;` (scope `uLang`) — Unique reference that allocates object on the heap
- L162 _typedef_ `template<class ObjectType> using TUPtrA = TUPtrG<ObjectType, true, CInstancedRawAllocator, CAllocatorInstance *>;` (scope `uLang`) — Unique pointer that allocates object using a given allocator instance
- L166 _typedef_ `template<class ObjectType> using TURefA = TUPtrG<ObjectType, false, CInstancedRawAllocator, CAllocatorInstance *>;` (scope `uLang`) — Unique reference that allocates object using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/UniquePointerArray.h` (Public)


#### class `uLang::TUPtrArrayG`  
`template<typename InElementType, bool AllowNull, typename InElementAllocatorType, typename... RawAllocatorArgsType> class TUPtrArrayG`  
_L15-759_
- desc: Templated dynamic array of unique pointers to elements
- L22 _public typedef_ `using ElementType = InElementType;`
- L23 _public typedef_ `using ElementAllocatorType = InElementAllocatorType;`
- L24 _public typedef_ `using PointerType = TUPtrG<ElementType, AllowNull, typename InElementAllocatorType::RawAllocatorType, RawAllocatorArgsType...>;`
- L25 _public typedef_ `using PointerStorageType = TArrayG<ElementType *, InElementAllocatorType, RawAllocatorArgsType...>;`
- L30 _public function_ `TUPtrArrayG(RawAllocatorArgsType&&... RawAllocatorArgs) : _PointerStorage(uLang::ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — Constructor
- L39 _public function_ `TUPtrArrayG(TUPtrArrayG && Other) : _PointerStorage(ForwardArg<PointerStorageType>(Other._PointerStorage))` — Move constructor. @param Other Array to move from.
- L51 _public function_ `TUPtrArrayG(TUPtrArrayG && Other, int32_t ExtraSlack) : _PointerStorage(ForwardArg<PointerStorageType>(Other._PointerStorage), ExtraSlack)` — Move constructor. @param Other Array to move from. @param ExtraSlack Tells how much extra pointer memory should be preallocated at the end of the array in the number of elements.
- L61 _public function_ `TUPtrArrayG& operator=(TUPtrArrayG&& Other)` — Move assignment operator. @param Other Array to assign and move from.
- L72 _public function_ `~TUPtrArrayG()` — Destructor.
- L82 _public function_ `int32_t GetSlack() const` — Returns the amount of slack in this array in elements. @see Num, Shrink
- L93 _public function_ `bool IsValidIndex(int32_t Index) const` — Tests if index is valid, i.e. greater than or equal to zero, and less than the number of elements in the array. @param Index Index to test. @returns True if index is valid. False otherwise.
- L104 _public function_ `int32_t Num() const` — Returns number of elements in array. @returns Number of elements in array. @see GetSlack
- L115 _public function_ `int32_t Max() const` — Returns maximum number of elements in array. @returns Maximum number of elements in array. @see GetSlack
- L126 _public function_ `bool IsEmpty() const` — Returns true if no elements in array @returns true if no elements in array or false if one or more elements. @see IsFull, Num
- L137 _public function_ `bool IsFilled() const` — Returns true if any elements in array @returns true if one or more elements in array or false no elements. @see IsEmpty, Num
- L145 _public function_ `ElementType* operator[](int32_t Index) const` — Array bracket operator. Returns naked pointer to element at given index.
- L156 _public function_ `PointerType Pop(bool bAllowShrinking = true)` — Pops element from the array. @param bAllowShrinking If this call allows shrinking of the array during element remove. @returns Popped element.
- L166 _public function_ `void Push(PointerType && Item)` — Pushes element into the array. @param Item Item to push.
- L179 _public function_ `ElementType* Top() const` — Returns the top element, i.e. the last one. @returns Naked pointer to the top element. @see Pop, Push
- L190 _public function_ `ElementType* Last(int32_t IndexFromTheEnd = 0) const` — Returns n-th last element from the array. @param IndexFromTheEnd (Optional) Index from the end of array (default = 0). @returns Reference to n-th last element from the array.
- L200 _public function_ `void Shrink()` — Shrinks the array's used pointer memory to smallest possible to store elements currently in it. @see Slack
- L213 _public function_ `bool Find(ElementType * Item, int32_t& Index) const` — Finds element within the array (by address comparison). @param Item Item to look for. @param Index Will contain the found index. @returns True if found. False otherwise. @see FindLast, FindLastByPredicate
- L225 _public function_ `int32_t Find(ElementType * Item) const` — Finds element within the array (by address comparison). @param Item Item to look for. @returns Index of the found element. IndexNone otherwise. @see FindLast, FindLastByPredicate
- L238 _public function_ `bool FindLast(const PointerType & Item, int32_t& Index) const` — Finds element within the array starting from the end (by address comparison). @param Item Item to look for. @param Index Output parameter. Found index. @returns True if found. False otherwise. @see Find, FindLastByPredicate
- L249 _public function_ `int32_t FindLast(const PointerType & Item) const` — Finds element within the array starting from the end (by address comparison). @param Item Item to look for. @returns Index of the found element. IndexNone otherwise.
- L262 _public function_ `template <typename Predicate> int32_t FindLastByPredicate(Predicate Pred, int32_t Count) const` — Searches an initial subrange of the array for the last occurrence of an element which matches the specified predicate. @param Pred Predicate taking const pointer to array element and returns true if element matches search criteria, false otherwise. @param Count The number of elements from the front of the array through which to search. @returns Index of the found element. IndexNone otherwise.
- L274 _public function_ `template <typename Predicate> int32_t FindLastByPredicate(Predicate Pred) const` — Searches the array for the last occurrence of an element which matches the specified predicate. @param Pred Predicate taking const pointer to array element and returns true if element matches search criteria, false otherwise. @returns Index of the found element. IndexNone otherwise.
- L287 _public function_ `template <typename KeyType> int32_t IndexOfByKey(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Index to the first matching element, or IndexNone if none is found.
- L299 _public function_ `template <typename Predicate> int32_t IndexOfByPredicate(Predicate Pred) const` — Finds an item by predicate. @param Pred The predicate to match, taking const pointer to array element. @returns Index to the first matching element, or IndexNone if none is found.
- L313 _public function_ `template <typename KeyType> ElementType* FindByKey(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Pointer to the first matching element, or nullptr if none is found. @see Find
- L327 _public function_ `template <typename Predicate> ElementType* FindByPredicate(Predicate Pred) const` — Finds an element which matches a predicate functor. @param Pred The functor to apply to each element, taking const pointer to array element. @returns Pointer to the first element for which the predicate returns true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L339 _public function_ `bool Contains(const ElementType* Pointer) const` — Checks if this array contains the exact pointer. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L351 _public function_ `template <typename ComparisonType> bool ContainsByKey(const ComparisonType& Key) const` — Checks if this array contains the element. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L364 _public function_ `template <typename Predicate> bool ContainsByPredicate(Predicate Pred) const` — Checks if this array contains element for which the predicate is true. @param Predicate to use, taking const pointer to array element @returns True if found. False otherwise. @see Contains, Find
- L381 _public function_ `void InsertZeroed(int32_t Index, int32_t Count = 1)` — Inserts a given number of zeroed elements into the array at given location. Caution, InsertZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @param Index Tells where to insert the new elements. @param Count Number of elements to add. @see Insert, InsertUninitialized, InsertDefaulted
- L393 _public function_ `int32_t Insert(TUPtrArrayG&& Items, const int32_t InIndex)` — Inserts given elements into the array at given location. @param Items Array of elements to insert. @param InIndex Tells where to insert the new elements. @returns Location at which the item was inserted.
- L406 _public function_ `int32_t Insert(PointerType&& Item, int32_t Index)` — Inserts a given element into the array at given location. @param Item The element to insert. @param Index Tells where to insert the new elements. @returns Location at which the insert was done. @see Add, Remove
- L419 _public function_ `PointerType RemoveAt(int32_t Index)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove.
- L435 _public function_ `template <typename CountType> void RemoveAt(int32_t Index, CountType Count, bool bAllowShrinking = true)` — Removes an element (or elements) at given location optionally shrinking the array. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L453 _public function_ `PointerType RemoveAtSwap(int32_t Index)` — Removes an element (or elements) at given location optionally shrinking the array. This version is much more efficient than RemoveAt (O(Count) instead of O(ArrayNum)), but does not preserve the order. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L473 _public function_ `template <typename CountType> void RemoveAtSwap(int32_t Index, CountType Count, bool bAllowShrinking = true)` — Removes an element (or elements) at given location optionally shrinking the array. This version is much more efficient than RemoveAt (O(Count) instead of O(ArrayNum)), but does not preserve the order. @param Index Location in array of the element to remove. @param Count (Optional) Number of elements to remove. Default is 1. @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
- L487 _public function_ `int32_t ReplaceAt(PointerType&& Item, int32_t Index)` — Replaces a given element at a given location. @param Item The element to insert. @param Index Tells where to insert the new element. @returns Location at which the replacement was done. @see Add, Remove
- L502 _public function_ `void Reset(int32_t NewSize = 0)` — Same as empty, but doesn't change memory allocations, unless the new size is larger than the current array. It calls the destructors on held items if needed and then zeros the ArrayNum. @param NewSize The expected usage size after calling this function.
- L513 _public function_ `void Empty(int32_t Slack = 0)` — Empties the array. It calls the destructors on held items if needed. @param Slack (Optional) The expected usage size after empty operation. Default is 0.
- L524 _public function_ `void SetNumZeroed(int32_t NewNum, bool bAllowShrinking = true)` — Resizes array to given number of elements. New elements will be zeroed. @param NewNum New size of the array.
- L539 _public function_ `void Append(TUPtrArrayG&& Source)` — Appends the specified array to this array. @param Source The array to append. @see Add, Insert
- L552 _public function_ `TUPtrArrayG& operator+=(TUPtrArrayG&& Other)` — Appends the specified array to this array. Cannot append to self. Move semantics version. @param Other The array to append.
- L565 _public function_ `template <typename... CtorArgsType> int32_t AddNew(CtorArgsType&&... CtorArgs)` — Constructs a new item at the end of the array, possibly reallocating the whole array to fit. @param Args  The arguments to forward to the constructor of the new item. @return      Index to the new item
- L578 _public function_ `template <typename... CtorArgsType> void InsertNew(int32_t Index, CtorArgsType&&... CtorArgs)` — Constructs a new item at a specified index, possibly reallocating the whole array to fit. @param Index The index to add the item at. @param Args  The arguments to forward to the constructor of the new item.
- L593 _public function_ `int32_t Add(PointerType&& Item)` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. Move semantics version. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L611 _public function_ `int32_t AddZeroed()` — Adds a new item to the end of the array, possibly reallocating the whole array to fit. The new item will be zeroed. Caution, AddZeroed() will create elements without calling the constructor and this is not appropriate for element types that require a constructor to function properly. @return Index to the first of the new items. @see Add, AddDefaulted, AddUnique, Append, Insert
- L623 _public function_ `int32_t AddUnique(PointerType&& Item)` — Adds unique element to array if it doesn't exist. @param Args Item to add. @returns Index of the element in the array. @see Add, AddDefaulted, AddZeroed, Append, Insert
- L640 _public function_ `void Reserve(int32_t Number)` — Reserves memory such that the array can contain at least Number elements. @param Number The number of elements that the array should be able to contain after allocation. @see Shrink
- L654 _public function_ `template <typename Predicate> int32_t RemoveAll(const Predicate& Pred)` — Remove all instances that match the predicate, maintaining order but not indices Optimized to work with runs of matches/non-matches @param Pred Predicate, taking const pointer to array element @returns Number of removed elements. @see Add, Insert, RemoveAllSwap, RemoveSingle, RemoveSwap
- L675 _public function_ `template <class Predicate> void RemoveAllSwap(const Predicate& Pred, bool bAllowShrinking = true)` — Remove all instances that match the predicate @param Pred Predicate, taking const pointer to array element @see Remove, RemoveSingle, RemoveSingleSwap, RemoveSwap
- L692 _public function_ `void Sort()` — Sorts the array assuming < operator is defined for ElementType.
- L703 _public function_ `template <class PredicateType> void Sort(const PredicateType& Predicate)` — Sorts the array using user define predicate class. @param Predicate Predicate instance or lambda, taking const pointer to array element
- L713 _public function_ `template<class OtherElementType, bool OtherAllowNull = AllowNull> requires ((std::is_convertible_v<OtherElementType*, ElementType*> || std::is_convertible_v<ElementType*, OtherElementType*>) && (AllowNull == OtherAllowNull || OtherAllowNull)) TUPtrArrayG<OtherElementType, OtherAllowNull, ElementAllocatorType, RawAllocatorArgsType...>& As()` — Casts TUPtrArray<T>& -> TUPtrArray<U>& if T is castable to U.
- L724 _public function_ `ElementType ** begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L725 _public function_ `ElementType * const * begin() const`
- L726 _public function_ `ElementType ** end()`
- L727 _public function_ `ElementType * const * end() const`
- L732 _protected function_ `void Delete(int32_t Index)` — Delete a single element
- L743 _protected function_ `void DeleteRange(int32_t BeginIndex, int32_t EndIndex)` — Delete a range of elements
- L752 _protected function_ `void DeleteAll()` — Delete all elements
- L757 _protected member_ `PointerStorageType _PointerStorage;`

#### struct `uLang::TIsZeroConstructType`  
`template <typename ElementType, bool AllowNull, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsZeroConstructType<TUPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L779-782_
- L781 _public member_ `static constexpr bool Value = TAllocatorTraits<ElementAllocatorType>::IsZeroConstruct;`

#### struct `uLang::TContainerTraits`  
`template <typename ElementType, bool AllowNull, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TContainerTraits<TUPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>> : public TContainerTraitsBase<TUPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L785-789_
- inherits: `TContainerTraitsBase<TUPtrArrayG<ElementType,AllowNull,ElementAllocatorType,RawAllocatorArgsType...>>`
- L788 _public member_ `static constexpr bool MoveWillEmptyContainer = TAllocatorTraits<ElementAllocatorType>::SupportsMove;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename ElementType, bool AllowNull, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsContiguousContainer<TUPtrArrayG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L792-795_
- L794 _public member_ `static constexpr bool Value = true;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L289 _function_ `return _PointerStorage.IndexOfByPredicate([=](ElementType * Item) -> bool { return *Item == Key; });` (scope `uLang::TUPtrArrayG::IndexOfByKey`)
- L315 _function_ `ElementType * const * Element = _PointerStorage.FindByPredicate([=](ElementType * Item) -> bool { return *Item == Key; });` (scope `uLang::TUPtrArrayG::FindByKey`)
- L341 _function_ `return _PointerStorage.FindByPredicate([=](ElementType * Item) -> bool { return Item == Pointer; }) != nullptr;` (scope `uLang::TUPtrArrayG::Contains`)
- L353 _function_ `return _PointerStorage.FindByPredicate([=](ElementType * Item) -> bool { return *Item == Key; }) != nullptr;` (scope `uLang::TUPtrArrayG::ContainsByKey`)
- L657 _function_ `return _PointerStorage.RemoveAll([&](ElementType* Item) -> bool { bool RemoveIt = Pred(Item); if (RemoveIt) { Item->~ElementType(); RawAllocator.Deallocate(Item); } return RemoveIt; });` (scope `uLang::TUPtrArrayG::RemoveAll`)
- L678 _function_ `return _PointerStorage.RemoveAllSwap([&](ElementType* Item) -> bool { bool RemoveIt = Pred(Item); if (RemoveIt) { Item->~ElementType(); RawAllocator.Deallocate(Item); } return RemoveIt; });` (scope `uLang::TUPtrArrayG::RemoveAllSwap`)
- L763 _typedef_ `template<typename ElementType> using TUPtrArray = TUPtrArrayG<ElementType, true, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Array of unique pointers that allocates elements on the heap
- L767 _typedef_ `template<typename ElementType> using TURefArray = TUPtrArrayG<ElementType, false, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Array of unique references that allocates elements on the heap
- L771 _typedef_ `template<typename ElementType> using TUPtrArrayA = TUPtrArrayG<ElementType, true, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Array of unique pointers that allocates object using a given allocator instance
- L775 _typedef_ `template<typename ElementType> using TURefArrayA = TUPtrArrayG<ElementType, false, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Array of unique references that allocates object using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/UniquePointerSet.h` (Public)


#### class `uLang::TUPtrSetG`  
`template<typename InElementType, bool AllowNull, typename InKeyType, typename InElementAllocatorType, typename... RawAllocatorArgsType> class TUPtrSetG : protected TUPtrArrayG<InElementType, AllowNull, InElementAllocatorType, RawAllocatorArgsType...>`  
_L16-231_
- inherits: `TUPtrArrayG<InElementType,AllowNull,InElementAllocatorType,RawAllocatorArgsType...>`
- desc: Templated dynamic set of shared pointers to elements This is similar to TUPtrArrayG, plus elements are always kept in sorted order and looked up via binary search
- L22 _private typedef_ `using Super = TUPtrArrayG<InElementType, AllowNull, InElementAllocatorType, RawAllocatorArgsType...>;`
- L24 _private typedef_ `using Helper = TPointerSetHelper<InElementType, InKeyType>;`
- L28 _public typedef_ `using KeyType = InKeyType;`
- L35 _public function_ `TUPtrSetG(RawAllocatorArgsType&&... RawAllocatorArgs) : Super(uLang::ForwardArg<RawAllocatorArgsType>(RawAllocatorArgs)...)` — Constructor
- L44 _public function_ `TUPtrSetG(TUPtrSetG && Other) : Super(ForwardArg<Super>(Other))` — Move constructor. @param Other Array to move from.
- L56 _public function_ `TUPtrSetG(TUPtrSetG && Other, int32_t ExtraSlack) : Super(ForwardArg<Super>(Other), ExtraSlack)` — Move constructor. @param Other Array to move from. @param ExtraSlack Tells how much extra pointer memory should be preallocated at the end of the array in the number of elements.
- L86 _public function_ `int32_t IndexOf(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator< and operator== for the comparison). @param Key The key to search by. @returns Index to the first matching element, or IndexNone if none is found.
- L100 _public function_ `ElementType* Find(const KeyType& Key) const` — Finds an item by key (assuming the ElementType overloads operator== for the comparison). @param Key The key to search by. @returns Pointer to the first matching element, or nullptr if none is found. @see Find
- L120 _public function_ `bool Contains(const KeyType& Key) const` — Checks if this array contains the element. @returns True if found. False otherwise. @see ContainsByPredicate, FilterByPredicate, FindByPredicate
- L134 _public function_ `void Append(const TUPtrSetG& Other)` — Appends the specified array to this array. Allocator changing version. @param Source The array to append. @see Add, Insert
- L146 _public function_ `void Append(TUPtrSetG&& Other)` — Appends the specified array to this array. @param Source The array to append. @see Add, Insert
- L160 _public function_ `TUPtrSetG& operator+=(TUPtrSetG&& Other)` — Appends the specified array to this array. Cannot append to self. Move semantics version. @param Other The array to append.
- L172 _public function_ `TUPtrSetG& operator+=(const TUPtrSetG& Other)` — Appends the specified array to this array. Cannot append to self. @param Other The array to append.
- L185 _public function_ `template <typename... CtorArgsType> int32_t AddNew(CtorArgsType&&... CtorArgs)` — Constructs a new item at the end of the array, possibly reallocating the whole array to fit. @param Args  The arguments to forward to the constructor of the new item. @return      Index to the new item
- L203 _public function_ `int32_t Add(PointerType&& Item)` — Adds a new item. Must not exist yet. Move semantics version. @param Item The item to add @return Index to the new item @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
- L218 _public function_ `int32_t Remove(const KeyType& Key)` — Removes as many instances of Item as there are in the array, maintaining order but not indices. @param Item Item to remove from array. @returns Number of removed elements. @see Add, Insert, RemoveAll, RemoveAllSwap, RemoveSingle, RemoveSwap

#### struct `uLang::TIsZeroConstructType`  
`template <typename ElementType, bool AllowNull, typename KeyType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsZeroConstructType<TUPtrSetG<ElementType, AllowNull, KeyType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L251-254_
- L253 _public member_ `static constexpr bool Value = TAllocatorTraits<ElementAllocatorType>::IsZeroConstruct;`

#### struct `uLang::TContainerTraits`  
`template <typename ElementType, bool AllowNull, typename KeyType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TContainerTraits<TUPtrSetG<ElementType, AllowNull, KeyType, ElementAllocatorType, RawAllocatorArgsType...>> : public TContainerTraitsBase<TUPtrSetG<ElementType, AllowNull, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L257-261_
- inherits: `TContainerTraitsBase<TUPtrSetG<ElementType,AllowNull,ElementAllocatorType,RawAllocatorArgsType...>>`
- L260 _public member_ `static constexpr bool MoveWillEmptyContainer = TAllocatorTraits<ElementAllocatorType>::SupportsMove;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename ElementType, bool AllowNull, typename KeyType, typename ElementAllocatorType, typename... RawAllocatorArgsType> struct TIsContiguousContainer<TUPtrSetG<ElementType, AllowNull, KeyType, ElementAllocatorType, RawAllocatorArgsType...>>`  
_L264-267_
- L266 _public member_ `static constexpr bool Value = true;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L235 _typedef_ `template<typename ElementType, typename KeyType> using TUPtrSet = TUPtrSetG<ElementType, true, KeyType, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Set of unique pointers that allocates elements on the heap
- L239 _typedef_ `template<typename ElementType, typename KeyType> using TURefSet = TUPtrSetG<ElementType, false, KeyType, TDefaultElementAllocator<CHeapRawAllocator>>;` (scope `uLang`) — Set of unique references that allocates elements on the heap
- L243 _typedef_ `template<typename ElementType, typename KeyType> using TUPtrSetA = TUPtrSetG<ElementType, true, KeyType, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Set of unique pointers that allocates object using a given allocator instance
- L247 _typedef_ `template<typename ElementType, typename KeyType> using TURefSetA = TUPtrSetG<ElementType, false, KeyType, TDefaultElementAllocator<CInstancedRawAllocator>, CAllocatorInstance *>;` (scope `uLang`) — Set of unique references that allocates object using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Containers/ValueRange.h` (Public)


#### struct `uLang::TValueIterator`  
`template <typename T> struct TValueIterator`  
_L9-40_
- L11 _public function_ `TValueIterator& operator++()`
- L17 _public function_ `TValueIterator operator++(int)`
- L24 _public function_ `T const& operator*() const`
- L39 _public member_ `T _Value;`

#### struct `uLang::TUntil`  
`template <typename T> struct TUntil`  
_L46-59_
- L48 _public function_ `TValueIterator<T> begin() const`
- L53 _public function_ `TValueIterator<T> end() const`
- L58 _public member_ `T _Last;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L29 _function_ `friend bool operator==(const TValueIterator& Left, const TValueIterator& Right)` (scope `uLang`)
- L34 _function_ `friend bool operator!=(const TValueIterator& Left, const TValueIterator& Right)` (scope `uLang`)
- L43 _prototype_ `template <typename T> TValueIterator(T&&) -> TValueIterator<TDecayT<T>>;` (scope `uLang`)
- L62 _prototype_ `template <typename T> TUntil(T&&) -> TUntil<TDecayT<T>>;` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Memory/Allocator.h` (Public)


#### enum `uLang::EObserverId`  
`enum EObserverId : uint32_t`  
_L14-17_
- desc: Id type for observer pointers
- L16 _public enumerator_ `ObserverId_Null = 0`

#### class `uLang::CAllocatorInstance`  
`class CAllocatorInstance`  
_L34-59_
- desc: This allows smart pointers to free object memory they are holding on to Passing the allocator itself to the free function allows allocation from multiple instances of an allocator and returning memory to the appropriate instance it was allocated from
- L37 _public typedef_ `using FAllocate = void * (*)(const CAllocatorInstance *, size_t);`
- L38 _public typedef_ `using FReallocate = void * (*)(const CAllocatorInstance *, void *, size_t);`
- L39 _public typedef_ `using FDeallocate = void (*)(const CAllocatorInstance *, void *);`
- L42 _public function_ `CAllocatorInstance(FAllocate Allocate, FReallocate Reallocate, FDeallocate Deallocate) : _Allocate(Allocate), _Reallocate(Reallocate), _Deallocate(Deallocate), _ObserverIdGenerator(EObserverId(uintptr_t(this) | 1))` — Use the memory address of this object to seed the observer id generator
- L45 _public function_ `void * Allocate(size_t NumBytes) const`
- L46 _public function_ `void * Reallocate(void * Memory, size_t NumBytes) const`
- L47 _public function_ `void Deallocate(void * Memory) const`
- L49 _public function_ `EObserverId GenerateObserverId()`
- L52 _private member_ `FAllocate _Allocate;`
- L53 _private member_ `FReallocate _Reallocate;`
- L54 _private member_ `FDeallocate _Deallocate;`
- L58 _private member_ `uint32_t _ObserverIdGenerator;` — Id generator for observer pointers Kept here so it does not need to be thread safe

#### class `uLang::CHeapRawAllocator`  
`class CHeapRawAllocator`  
_L63-88_
- desc: Raw memory allocator that allocates memory from the global heap
- L66 _public function_ `CHeapRawAllocator()`
- L67 _public function_ `CHeapRawAllocator(EDefaultInit)`
- L69 _public function_ `static void * Allocate(size_t NumBytes)`
- L70 _public function_ `static void * Reallocate(void * Memory, size_t NumBytes)`
- L71 _public function_ `static void Deallocate(void * Memory)`
- L73 _public function_ `static EObserverId GenerateObserverId()`
- L86 _public function_ `bool operator == (const CHeapRawAllocator& Other) const` — Any instance of this allocator is as good as any other
- L87 _public function_ `bool operator != (const CHeapRawAllocator& Other) const`

#### class `uLang::CInstancedRawAllocator`  
`class CInstancedRawAllocator`  
_L91-104_
- desc: Raw memory allocator that keeps a pointer to an allocator instance which is used for allocation
- L94 _public function_ `CInstancedRawAllocator(CAllocatorInstance * AllocatorInstance) : _AllocatorInstance(AllocatorInstance)`
- L95 _public function_ `CInstancedRawAllocator(EDefaultInit) : _AllocatorInstance(nullptr)` — Requires explicit argument to prevent default initialization by simply passing no arguments
- L97 _public function_ `void * Allocate(size_t NumBytes) const`
- L98 _public function_ `void * Reallocate(void * Memory, size_t NumBytes)`
- L99 _public function_ `void Deallocate(void * Memory) const`
- L101 _public function_ `EObserverId GenerateObserverId() const`
- L103 _public member_ `CAllocatorInstance * _AllocatorInstance;`

#### enum `uLang::(anonymous)`  
``  
_L124-132_

#### struct `uLang::SScriptContainerElement`  
`struct SScriptContainerElement`  
_L225-227_
- desc: A type which is used to represent a script type that is unknown at compile time.

#### struct `uLang::TAllocatorTraitsBase`  
`template <typename AllocatorType> struct TAllocatorTraitsBase`  
_L230-234_

#### enum `uLang::TAllocatorTraitsBase::(anonymous)`  
`enum`  
_L232-232_

#### enum `uLang::TAllocatorTraitsBase::(anonymous)`  
`enum`  
_L233-233_

#### struct `uLang::TAllocatorTraits`  
`template <typename AllocatorType> struct TAllocatorTraits : TAllocatorTraitsBase<AllocatorType>`  
_L237-239_
- inherits: `TAllocatorTraitsBase<AllocatorType>`

#### class `uLang::TDefaultElementAllocator`  
`template<class InRawAllocatorType, typename... AllocatorArgsType> class TDefaultElementAllocator`  
_L244-399_
- desc: The indirect allocation policy always allocates the elements indirectly.
- L248 _public typedef_ `using RawAllocatorType = InRawAllocatorType;`

#### enum `uLang::TDefaultElementAllocator::(anonymous)`  
`enum`  
_L250-250_

#### enum `uLang::TDefaultElementAllocator::(anonymous)`  
`enum`  
_L251-251_

#### class `uLang::TDefaultElementAllocator::ForAnyElementType`  
`class ForAnyElementType`  
_L257-379_
- desc: A class that may be used when NeedsElementType=false is specified. If NeedsElementType=true, then this must be present but will not be used, and so can simply be a typedef to void
- L261 _public function_ `ForAnyElementType(EDefaultInit) : _Data(nullptr), _RawAllocator(DefaultInit)` — Default constructor.
- L264 _public function_ `ForAnyElementType(const RawAllocatorType & Allocator) : _Data(nullptr), _RawAllocator(Allocator)` — Constructor with given allocator
- L265 _public function_ `ForAnyElementType(AllocatorArgsType... AllocatorArgs) : _Data(nullptr), _RawAllocator(AllocatorArgs...)`
- L272 _public function_ `void MoveToEmpty(ForAnyElementType& Other)` — Moves the state of another allocator into this one. Assumes that the allocator is currently empty, i.e. memory may be allocated but any existing elements have already been destructed (if necessary). @param Other - The allocator to move the state from.  This allocator should be left in a valid empty state.
- L287 _public function_ `~ForAnyElementType()` — Destructor.
- L296 _public function_ `SScriptContainerElement* GetAllocation() const` — Accesses the container's current data.
- L302 _public function_ `const RawAllocatorType & GetRawAllocator() const` — Accesses the container's raw allocator.
- L313 _public function_ `void ResizeAllocation(int32_t PreviousNumElements, int32_t NumElements, size_t NumBytesPerElement)` — Resizes the container's allocation. @param PreviousNumElements - The number of elements that were stored in the previous allocation. @param NumElements - The number of elements to allocate space for. @param NumBytesPerElement - The number of bytes/element.
- L332 _public function_ `int32_t CalculateSlackReserve(int32_t NumElements, int32_t NumBytesPerElement) const` — Calculates the amount of slack to allocate for an array that has just grown or shrunk to a given number of elements. @param NumElements - The number of elements to allocate space for. @param CurrentNumSlackElements - The current number of elements allocated. @param NumBytesPerElement - The number of bytes/element.
- L343 _public function_ `int32_t CalculateSlackShrink(int32_t NumElements, int32_t NumAllocatedElements, int32_t NumBytesPerElement) const` — Calculates the amount of slack to allocate for an array that has just shrunk to a given number of elements. @param NumElements - The number of elements to allocate space for. @param CurrentNumSlackElements - The current number of elements allocated. @param NumBytesPerElement - The number of bytes/element.
- L354 _public function_ `int32_t CalculateSlackGrow(int32_t NumElements, int32_t NumAllocatedElements, int32_t NumBytesPerElement) const` — Calculates the amount of slack to allocate for an array that has just grown to a given number of elements. @param NumElements - The number of elements to allocate space for. @param CurrentNumSlackElements - The current number of elements allocated. @param NumBytesPerElement - The number of bytes/element.
- L359 _public function_ `size_t GetAllocatedSize(int32_t NumAllocatedElements, size_t NumBytesPerElement) const`
- L364 _public function_ `bool HasAllocation()`
- L370 _private prototype_ `ForAnyElementType(const ForAnyElementType &) = delete;`
- L371 _private prototype_ `ForAnyElementType& operator=(const ForAnyElementType &) = delete;`
- L374 _private member_ `SScriptContainerElement * _Data;` — A pointer to the container's elements.
- L378 _private member_ `RawAllocatorType _RawAllocator;` — How to allocate/deallocate the data This allocator can be 0 in size

#### class `uLang::TDefaultElementAllocator::ForElementType`  
`template<typename ElementType> class ForElementType : public ForAnyElementType`  
_L386-398_
- inherits: `ForAnyElementType`
- desc: A class that may be used when NeedsElementType=true is specified. If NeedsElementType=false, then this must be present but will not be used, and so can simply be a typedef to void
- L390 _public function_ `ForElementType(EDefaultInit) : ForAnyElementType(DefaultInit)`
- L391 _public function_ `ForElementType(const RawAllocatorType & Allocator) : ForAnyElementType(Allocator)`
- L392 _public function_ `ForElementType(AllocatorArgsType&&... AllocatorArgs) : ForAnyElementType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...)`
- L394 _public function_ `ElementType* GetAllocation() const`

#### struct `uLang::TAllocatorTraits`  
`template<class RawAllocatorType> struct TAllocatorTraits<TDefaultElementAllocator<RawAllocatorType>> : TAllocatorTraitsBase<TDefaultElementAllocator<RawAllocatorType>>`  
_L402-406_
- inherits: `TAllocatorTraitsBase<TDefaultElementAllocator<RawAllocatorType>>`

#### enum `uLang::TAllocatorTraits::(anonymous)`  
`enum`  
_L404-404_

#### enum `uLang::TAllocatorTraits::(anonymous)`  
`enum`  
_L405-405_

#### class `uLang::TInlineElementAllocator`  
`template <uint32_t NumInlineElements, typename SecondaryAllocator = TDefaultElementAllocator<CHeapRawAllocator>, typename... AllocatorArgsType> class TInlineElementAllocator`  
_L413-558_
- desc: The inline allocation policy allocates up to a specified number of elements in the same allocation as the container. Any allocation needed beyond that causes all data to be moved into an indirect allocation.
- L417 _public typedef_ `using RawAllocatorType = typename SecondaryAllocator::RawAllocatorType;`
- L557 _public typedef_ `typedef void ForAnyElementType;`

#### enum `uLang::TInlineElementAllocator::(anonymous)`  
`enum`  
_L419-419_

#### enum `uLang::TInlineElementAllocator::(anonymous)`  
`enum`  
_L420-420_

#### class `uLang::TInlineElementAllocator::ForElementType`  
`template<typename ElementType> class ForElementType`  
_L423-555_
- L428 _public function_ `ForElementType(EDefaultInit)` — Default constructor.
- L433 _public function_ `ForElementType(const RawAllocatorType& Allocator) : _SecondaryData(Allocator)` — Constructor with given allocator
- L434 _public function_ `ForElementType(AllocatorArgsType... AllocatorArgs) : _SecondaryData(AllocatorArgs...)` — -V730
- L441 _public function_ `void MoveToEmpty(ForElementType& Other)` — Moves the state of another allocator into this one. Assumes that the allocator is currently empty, i.e. memory may be allocated but any existing elements have already been destructed (if necessary). @param Other - The allocator to move the state from.  This allocator should be left in a valid empty state.
- L456 _public function_ `ElementType* GetAllocation() const`
- L462 _public function_ `const RawAllocatorType& GetRawAllocator() const` — Accesses the container's raw allocator.
- L467 _public function_ `void ResizeAllocation(int32_t PreviousNumElements, int32_t NumElements, size_t NumBytesPerElement)`
- L499 _public function_ `int32_t CalculateSlackReserve(int32_t NumElements, int32_t NumBytesPerElement) const`
- L506 _public function_ `int32_t CalculateSlackShrink(int32_t NumElements, int32_t NumAllocatedElements, int32_t NumBytesPerElement) const`
- L513 _public function_ `int32_t CalculateSlackGrow(int32_t NumElements, int32_t NumAllocatedElements, int32_t NumBytesPerElement) const`
- L521 _public function_ `size_t GetAllocatedSize(int32_t NumAllocatedElements, size_t NumBytesPerElement) const`
- L530 _public function_ `bool HasAllocation() const`
- L535 _public function_ `uint32_t GetInitialCapacity() const`
- L541 _private prototype_ `ForElementType(const ForElementType&);`
- L542 _private prototype_ `ForElementType& operator=(const ForElementType&);`
- L545 _private member_ `TTypeCompatibleBytes<ElementType> InlineData[NumInlineElements];` — The data is stored in this array if less than NumInlineElements is needed.
- L548 _private member_ `typename SecondaryAllocator::template ForElementType<ElementType> _SecondaryData;` — The data is allocated through the indirect allocation policy if more than NumInlineElements is needed.
- L551 _private function_ `ElementType* GetInlineElements() const` — @return the base of the aligned inline element data

#### struct `uLang::TAllocatorTraits`  
`template <uint32_t NumInlineElements, typename SecondaryAllocator> struct TAllocatorTraits<TInlineElementAllocator<NumInlineElements, SecondaryAllocator>> : TAllocatorTraitsBase<TInlineElementAllocator<NumInlineElements, SecondaryAllocator>>`  
_L561-564_
- inherits: `TAllocatorTraitsBase<TInlineElementAllocator<NumInlineElements,SecondaryAllocator>>`

#### enum `uLang::TAllocatorTraits::(anonymous)`  
`enum`  
_L563-563_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L21 _function_ `inline uint32_t RotateCRC32(uint32_t CRC)` (scope `uLang`) — Compute a new CRC32 from a given CRC32 by rotating one bit Due to the nature of CRCs, this will exactly iterate through all possible 32-bit values except for 0
- L111 _function_ `inline void * operator new(size_t NumBytes, const ::uLang::CHeapRawAllocator & Allocator)` — Deliberately NOT implementing new[] and delete[] here
- L113 _function_ `inline void operator delete(void * Memory, const ::uLang::CHeapRawAllocator & Allocator)` — Unfortunately, C++ does not have a clean syntax to invoke custom delete operators so this is a bit useless...
- L116 _function_ `inline void * operator new(size_t NumBytes, const ::uLang::CInstancedRawAllocator & Allocator)` — Deliberately NOT implementing new[] and delete[] here
- L118 _function_ `inline void operator delete(void * Memory, const ::uLang::CInstancedRawAllocator & Allocator)` — Unfortunately, C++ does not have a clean syntax to invoke custom delete operators so this is a bit useless...
- L120 _namespace_ `namespace uLang`
- L128 _enumerator_ `DEFAULT_ALIGNMENT = 0` (scope `uLang::__anon8ab0514f0103`) — Default allocator alignment. If the default is specified, the allocator applies to engine rules. Blocks >= 16 bytes will be 16-byte-aligned, Blocks < 16 will be 8-byte aligned. If the allocator does not support allocation alignment, the alignment will be ignored.
- L131 _enumerator_ `MIN_ALIGNMENT = 8` (scope `uLang::__anon8ab0514f0103`) — Minimum allocator alignment
- L137 _function_ `inline size_t DefaultQuantizeSize(size_t Count, uint32_t Alignment)` (scope `uLang`) — TODO: Implement for special allocators such as binned allocators
- L142 _function_ `inline int32_t DefaultCalculateSlackShrink(int32_t NumElements, int32_t NumAllocatedElements, size_t BytesPerElement, bool bAllowQuantize, uint32_t Alignment = DEFAULT_ALIGNMENT)` (scope `uLang`)
- L171 _function_ `inline int32_t DefaultCalculateSlackGrow(int32_t NumElements, int32_t NumAllocatedElements, size_t BytesPerElement, bool bAllowQuantize, uint32_t Alignment = DEFAULT_ALIGNMENT)` (scope `uLang`)
- L207 _function_ `inline int32_t DefaultCalculateSlackReserve(int32_t NumElements, size_t BytesPerElement, bool bAllowQuantize, uint32_t Alignment = DEFAULT_ALIGNMENT)` (scope `uLang`)
- L232 _enumerator_ `enum { SupportsMove = false }; enum { IsZeroConstruct = false };` (scope `uLang::TAllocatorTraitsBase::__anon8ab0514f0203`)
- L233 _enumerator_ `enum { IsZeroConstruct = false };` (scope `uLang::TAllocatorTraitsBase::__anon8ab0514f0303`)
- L250 _enumerator_ `enum { NeedsElementType = false }; enum { RequireRangeCheck = true }; /** * A class that may be used when NeedsElementType=false is specified. * If NeedsElementType=true` (scope `uLang::TDefaultElementAllocator::__anon8ab0514f0403`)
- L251 _enumerator_ `enum { RequireRangeCheck = true }; /** * A class that may be used when NeedsElementType=false is specified. * If NeedsElementType=true` (scope `uLang::TDefaultElementAllocator::__anon8ab0514f0503`)
- L404 _enumerator_ `enum { SupportsMove = true }; enum { IsZeroConstruct = true };` (scope `uLang::TAllocatorTraits::__anon8ab0514f0603`)
- L405 _enumerator_ `enum { IsZeroConstruct = true };` (scope `uLang::TAllocatorTraits::__anon8ab0514f0703`)
- L419 _enumerator_ `enum { NeedsElementType = true }; enum { RequireRangeCheck = true }; template<typename ElementType> class ForElementType { public:` (scope `uLang::TInlineElementAllocator::__anon8ab0514f0803`)
- L420 _enumerator_ `enum { RequireRangeCheck = true }; template<typename ElementType> class ForElementType { public:` (scope `uLang::TInlineElementAllocator::__anon8ab0514f0903`)
- L563 _enumerator_ `enum { SupportsMove = TAllocatorTraits<SecondaryAllocator>::SupportsMove };` (scope `uLang::TAllocatorTraits::__anon8ab0514f0a03`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Memory/ArenaAllocator.h` (Public)


#### class `uLang::CArenaAllocator`  
`class CArenaAllocator : public CAllocatorInstance`  
_L17-56_
- inherits: `CAllocatorInstance`
- desc: Allocates from a series of arenas Memory blocks can not be individually deallocated Deleting this allocator will free all allocated memory NOT thread safe (on purpose, for efficiency)
- L21 _public prototype_ `CArenaAllocator(uint32_t ArenaSize);`
- L22 _public prototype_ `~CArenaAllocator();`
- L24 _public prototype_ `void Merge(CArenaAllocator && Other);`
- L26 _public prototype_ `void * Allocate(uint32_t NumBytes);`
- L27 _public prototype_ `void DeallocateAll();`
- L33 _protected prototype_ `static void * Allocate(const CAllocatorInstance * This, size_t NumBytes);`
- L34 _protected prototype_ `static void * Reallocate(const CAllocatorInstance * This, void * Memory, size_t NumBytes);`
- L35 _protected prototype_ `static void Deallocate(const CAllocatorInstance * This, void * Memory);`
- L38 _protected prototype_ `void AllocateNewArena();` — Get more memory
- L46 _protected member_ `SArenaHeader * _First;` — The first in the list of arenas
- L47 _protected member_ `const uint32_t _ArenaSize;` — Memory in each arena, in bytes
- L48 _protected member_ `uint32_t _BytesLeftInFirstArena;` — How much memory is available in the first arena
- L51 _protected member_ `uint32_t _NumAllocations;`
- L52 _protected member_ `bool _MatchDeallocations;`
- L53 _protected member_ `uint32_t _NumArenas;`
- L54 _protected member_ `uint32_t _BytesAllocatedTotal;`
- L62 _function_ `inline void * CArenaAllocator::Allocate(uint32_t NumBytes)`

#### enum `uLang::CArenaAllocator::(anonymous)`  
`enum`  
_L31-31_
- desc: Alignment is hardcoded to 8 for now

#### struct `uLang::CArenaAllocator::SArenaHeader`  
`struct SArenaHeader`  
_L41-44_
- desc: Header of an arena, the allocated memory follows
- L43 _public member_ `SArenaHeader * _Next;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ULANGCORE_API`
- L10 _namespace_ `namespace uLang`
- L31 _enumerator_ `enum { Alignment = 8 }; static UE_API void * Allocate(const CAllocatorInstance * This, size_t NumBytes); static UE_API void * Reallocate(const CAllocatorInstance * This, void * Memory, size_t NumBytes); static UE_API void Deallocate(const CAllocatorInstance * This, void * Memory); UE_API void AllocateNewArena();` (scope `uLang::CArenaAllocator::__anone03e0e160103`) — Alignment is hardcoded to 8 for now

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Memory/MemoryOps.h` (Public)


#### struct `uLang::Private::TCanBitwiseRelocate`  
`template <typename DestinationElementType, typename SourceElementType> struct TCanBitwiseRelocate`  
_L16-21_
- L18 _public member_ `static constexpr bool Value = std::is_same_v<DestinationElementType, SourceElementType> || (TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value && std::is_trivially_destructible_v<SourceElementType>);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L13 _namespace_ `namespace Private` (scope `uLang`)
- L32 _function_ `template <typename ElementType> requires (!TIsZeroConstructType<ElementType>::Value) void DefaultConstructElements(void* Address, int32_t Count)` (scope `uLang`) — Default constructs a range of items in memory. @param   Elements    The address of the first memory location to construct at. @param   Count       The number of elements to destruct.
- L46 _function_ `template <typename ElementType> requires (TIsZeroConstructType<ElementType>::Value) void DefaultConstructElements(void* Elements, int32_t Count)` (scope `uLang`)
- L64 _function_ `template <typename ElementType> requires (!std::is_trivially_destructible_v<ElementType>) void DestructElement(ElementType* Element)` (scope `uLang`) — Destructs a single item in memory. @param   Elements    A pointer to the item to destruct. @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
- L67 _typedef_ `using DestructItemsElementTypeTypedef = ElementType;` (scope `uLang::DestructElement`) — We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
- L75 _function_ `template <typename ElementType> requires (std::is_trivially_destructible_v<ElementType>) void DestructElement(ElementType* Element)` (scope `uLang`)
- L90 _function_ `template <typename ElementType> requires (!std::is_trivially_destructible_v<ElementType>) void DestructElements(ElementType* Element, int32_t Count)` (scope `uLang`) — Destructs a range of items in memory. @param   Elements    A pointer to the first item to destruct. @param   Count       The number of elements to destruct. @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
- L95 _typedef_ `using DestructItemsElementTypeTypedef = ElementType;` (scope `uLang::DestructElements`) — We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
- L106 _function_ `template <typename ElementType> requires (std::is_trivially_destructible_v<ElementType>) void DestructElements(ElementType* Elements, int32_t Count)` (scope `uLang`)
- L120 _function_ `template <typename DestinationElementType, typename SourceElementType> requires (!TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value) void ConstructElements(void* Dest, const SourceElementType* Source, int32_t Count)` (scope `uLang`) — Constructs a range of items into memory from a set of arguments.  The arguments come from an another array. @param   Dest        The memory location to start copying into. @param   Source      A pointer to the first argument to pass to the constructor. @param   Count       The number of elements to copy.
- L134 _function_ `template <typename DestinationElementType, typename SourceElementType> requires (TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value) void ConstructElements(void* Dest, const SourceElementType* Source, int32_t Count)` (scope `uLang`)
- L153 _function_ `template <typename DestinationElementType, typename SourceElementType> requires (!Private::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value) void RelocateConstructElements(void* Dest, const SourceElementType* Source, int32_t Count)` (scope `uLang`) — Relocates a range of items to a new memory location as a new type. This is a so-called 'destructive move' for which there is no single operation in C++ but which can be implemented very efficiently in general. @param   Dest        The memory location to relocate to. @param   Source      A pointer to the first item to relocate. @param   Count       The number of elements to relocate.
- L158 _typedef_ `using RelocateConstructItemsElementTypeTypedef = SourceElementType;` (scope `uLang::RelocateConstructElements`) — We need a typedef here because VC won't compile the destructor call below if SourceElementType itself has a member called SourceElementType
- L169 _function_ `template <typename DestinationElementType, typename SourceElementType> requires (Private::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value) void RelocateConstructElements(void* Dest, const SourceElementType* Source, int32_t Count)` (scope `uLang`)
- L187 _function_ `template <typename ElementType> requires (TTypeTraits<ElementType>::IsBytewiseComparable) bool CompareElements(const ElementType* A, const ElementType* B, int32_t Count)` (scope `uLang`)
- L200 _function_ `template <typename ElementType> requires (!TTypeTraits<ElementType>::IsBytewiseComparable) bool CompareElements(const ElementType* A, const ElementType* B, int32_t Count)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/Archive.h` (Public)


#### class `uLang::CArchive`  
`class CArchive`  
_L18-92_
- desc: Abstract archive base class, similar to UE FArchive Assumes same endian on all platforms
- L21 _public prototype_ `CArchive() = default;`
- L22 _public prototype_ `~CArchive() = default;`
- L24 _public prototype_ `CArchive(const CArchive&) = delete;`
- L25 _public prototype_ `CArchive& operator=(const CArchive& ArchiveToCopy) = delete;`
- L28 _public function_ `bool IsLoading() const` — Whether this archive is for loading data
- L31 _public prototype_ `virtual void Serialize(void* Data, int64_t NumBytes) = 0;` — The core serialization function - called for serialization of anything
- L90 _protected member_ `bool _bIsLoading = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace uLang`
- L36 _function_ `template<class T> requires (std::is_arithmetic_v<T>) friend CArchive& operator<<(CArchive& Ar, T& Value)` (scope `uLang`) — Convenience operator for serializing integers and floats
- L39 _function_ `friend CArchive& operator<<(CArchive& Ar, CUTF8String& Value)` (scope `uLang`) — Convenience operator for serializing a string
- L45 _function_ `Value = CUTF8String(ByteLength, [&Ar, ByteLength](UTF8Char* Memory) { Ar.Serialize(Memory, ByteLength); });` (scope `uLang::CArchive::operator <<`)
- L56 _function_ `template<class T> friend CArchive& operator<<(CArchive& Ar, TOptional<T>& Value)` (scope `uLang`) — Convenience operator for serializing an optional
- L73 _function_ `template<class ElementType> friend CArchive& operator<<(CArchive& Ar, TArray<ElementType>& Value)` (scope `uLang`) — Convenience operator for serializing an array

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/Arithmetic.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L13 _variable_ `constexpr int32_t Int32Min = INT32_MIN;` (scope `uLang`)
- L14 _variable_ `constexpr int32_t Int32Max = INT32_MAX;` (scope `uLang`)
- L15 _variable_ `constexpr uint32_t Int32MaxMagnitude = ((uint32_t)(INT32_MAX))+1;` (scope `uLang`)
- L16 _variable_ `constexpr uint32_t UInt32Max = UINT32_MAX;` (scope `uLang`)
- L18 _variable_ `constexpr int64_t Int64Min = INT64_MIN;` (scope `uLang`)
- L19 _variable_ `constexpr int64_t Int64Max = INT64_MAX;` (scope `uLang`)
- L20 _variable_ `constexpr uint64_t Int64MaxMagnitude = ((uint64_t)(INT64_MAX))+1;` (scope `uLang`)
- L21 _variable_ `constexpr uint64_t UInt64Max = UINT64_MAX;` (scope `uLang`)
- L23 _variable_ `constexpr float Float32Min = FLT_MIN;` (scope `uLang`)
- L24 _variable_ `constexpr float Float32Max = FLT_MAX;` (scope `uLang`)
- L25 _variable_ `constexpr double Float64Min = DBL_MIN;` (scope `uLang`)
- L26 _variable_ `constexpr double Float64Max = DBL_MAX;` (scope `uLang`)
- L36 _function_ `constexpr bool CheckedI64Negate(int64_t Rhs, int64_t* OutResult)` (scope `uLang`) — todo: implement the rest of the types (int32_t, int16_t, ...), and then also provide platform specific optimized versions of this. in particular, platforms  that use the Clang and GCC compilers have intrinsics available such as '__builtin_add_overflow' that will perform the operation and return whether or not overflow happened, which should yield more optimal code.
- L43 _function_ `constexpr bool CheckedI64Abs(int64_t Rhs, int64_t* OutResult)` (scope `uLang`)
- L57 _function_ `constexpr bool CheckedConvertI32I64(int64_t Rhs, int32_t* OutResult)` (scope `uLang`)
- L66 _function_ `constexpr bool CheckedI64Add(int64_t Lhs, int64_t Rhs, int64_t* OutResult)` (scope `uLang`)
- L81 _function_ `constexpr bool CheckedI64Subtract(int64_t Lhs, int64_t Rhs, int64_t* OutResult)` (scope `uLang`)
- L92 _function_ `constexpr bool CheckedI64Multiply(int64_t Lhs, int64_t Rhs, int64_t* OutResult)` (scope `uLang`)
- L141 _function_ `constexpr bool CheckedI64Divide(int64_t Lhs, int64_t Rhs, int64_t* OutResult)` (scope `uLang`)
- L156 _function_ `constexpr bool CheckedI64Modulo(int64_t Lhs, int64_t Rhs, int64_t* OutResult)` (scope `uLang`)
- L171 _function_ `constexpr bool IsFactor(int64_t Left, int64_t Right)` (scope `uLang`)
- L175 _function_ `constexpr bool SameSign(int64_t Left, int64_t Right)` (scope `uLang`)
- L179 _function_ `inline TOptional<int64_t> CheckedI64DivideAndRoundUp(int64_t Left, int64_t Right)` (scope `uLang`)
- L189 _function_ `inline TOptional<int64_t> CheckedI64DivideAndRoundDown(int64_t Left, int64_t Right)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/CRC.h` (Public)


#### class `uLang::CCRC16`  
`class CCRC16`  
_L13-34_
- desc: Helper class for computing a 16 bit CRC We are using the CRC-16-CCITT polynomial (0x1021), but are using a bit reversed algorithm akin to CRC32 and CRC64 algorithms which saves one bit shift
- L20 _public function_ `static uint16_t Generate(const uint8_t * Begin, const uint8_t * End, uint16_t PrevCRC = 0)` — Generate CRC16 from a string of bytes You can compute the CRC of two concatenated strings by computing the CRC of the first string, then passing the result into the PrevCRC argument when computing the CRC of the second string
- L33 _private member_ `static const uint16_t* _Table;`

#### class `uLang::CCRC32`  
`class CCRC32`  
_L39-60_
- desc: Helper class for computing a 32 bit CRC We are using the CRC-32 polynomial 0x04c11db7 as used by zip, PHP etc., but are using a bit reversed which saves one bit shift
- L46 _public function_ `static uint32_t Generate(const uint8_t * Begin, const uint8_t * End, uint32_t PrevCRC = 0)` — Generate CRC32 from a string of bytes You can compute the CRC of two concatenated strings by computing the CRC of the first string, then passing the result into the PrevCRC argument when computing the CRC of the second string
- L59 _private member_ `static const uint32_t* _Table;`

#### class `uLang::CCRC64`  
`class CCRC64`  
_L64-72_
- desc: Helper class for computing a 64 bit CRC We are using the ECMA CRC-64 polynomial 0x42F0E1EBA9EA3693
- L71 _public prototype_ `static uint64_t GenerateSlow(const uint8_t* Begin, const uint8_t* End, uint64_t PrevCRC = 0);` — Generate CRC64 from a string of bytes - slow but needs no table You can compute the CRC of two concatenated strings by computing the CRC of the first string, then passing the result into the PrevCRC argument when computing the CRC of the second string

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/EnumUtils.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define ULANG_ENUM_BIT_FLAGS(Enum, ...) \` — Defines all bitwise operators for enum classes so it can be (mostly) used as a regular flags enum
- L16 _namespace_ `namespace uLang`
- L20 _function_ `template<typename Enum> inline bool Enum_HasAllFlags(Enum Flags, Enum Contains)` (scope `uLang`)
- L26 _function_ `template<typename Enum> inline bool Enum_HasAnyFlags(Enum Flags, Enum Contains)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/Event.h` (Public)


#### class `uLang::TEventRegistrar`  
`template <typename... ParamTypes> class TEventRegistrar`  
_L27-93_
- desc: Registration portion of an TEvent<>. Split out as a standalone class, so systems can expose direct registration functionality without exposing execution rights, like so: class CMySystem { public: using CMyEvent = TEvent<int> CMyEvent::Registrar& GetEvent() { return MyEvent; } // For external subscription private: CMyEvent MyEvent;
- L30 _public typedef_ `using FunctionType = uLang::TFunction<void(ParamTypes...)>;`
- L31 _public typedef_ `using SubscriberId = EventSubscriberId;`
- L35 _public function_ `template <typename FunctorType> requires (!TIsTFunction<typename TDecay<FunctorType>::Type>::Value && Private::TFuncCanBindToFunctor<void(ParamTypes...), FunctorType>::Value) SubscriberId Subscribe(FunctorType&& InFunc)`
- L41 _public function_ `SubscriberId Subscribe(const FunctionType& Listener)`
- L47 _public function_ `bool Unsubscribe(const SubscriberId ListenerId)`
- L62 _public function_ `bool IsBound() const`
- L71 _public function_ `int32_t Num() const`
- L76 _public function_ `void Reset()`
- L82 _private function_ `TEventRegistrar()`
- L86 _protected member_ `SubscriberId _NextId = 0;`
- L92 _protected member_ `TArray<SRegisteredListener> _Listeners;`

#### struct `uLang::TEventRegistrar::SRegisteredListener`  
`struct SRegisteredListener`  
_L87-91_
- L89 _public member_ `SubscriberId _Id;`
- L90 _public member_ `FunctionType _Callback;`

#### class `uLang::TEvent`  
`template <typename... ParamTypes> class TEvent : public TEventRegistrar<ParamTypes...>`  
_L101-116_
- inherits: `TEventRegistrar<ParamTypes...>`
- desc: Generic event dispatcher. Declared using a comma separated parameter list to define its signature: TEvent<int, float, bool> MyEvent;
- L104 _public typedef_ `using Registrar = TEventRegistrar<ParamTypes...>;`
- L106 _public function_ `void Broadcast(ParamTypes... Params)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L11 _typedef_ `using EventSubscriberId = uint32_t;` (scope `uLang`)
- L50 _function_ `` (scope `uLang::TEventRegistrar::Unsubscribe`)
- L65 _function_ `` (scope `uLang::TEventRegistrar::IsBound`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/FloatingPointState.h` (Public)


#### class `uLang::CFloatStateSaveRestore`  
`class CFloatStateSaveRestore`  
_L19-28_
- desc: Scope guard that saves current FP state (rounding mode, flush-to-zero etc.) and puts us into fully IEEE compliant mode for the duration of the scope.
- L22 _public prototype_ `CFloatStateSaveRestore();`
- L23 _public prototype_ `~CFloatStateSaveRestore();`
- L27 _private member_ `uint32_t _SavedState;` — The relevant control register is 32-bit on all current targets.

#### class `uLang::CFloatStateCheckOnly`  
`class CFloatStateCheckOnly`  
_L33-40_
- desc: Scope guard that asserts the current FP state has the IEEE-compliant settings we expect on entry, but never changes state. Drop-in compatible with CFloatStateSaveRestore.
- L36 _public function_ `CFloatStateCheckOnly()`

#### class `uLang::CFloatStateDoNothing`  
`class CFloatStateDoNothing`  
_L45-47_
- desc: Scope guard that doesn't actually do anything. This is here to make it as easy as possible to swap out either of CFloatStateSaveRestore or CFloatStateCheckOnly for a no-op by changing a single type.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L11 _prototype_ `void AssertExpectedFloatingPointState();` (scope `uLang`) — Asserts that the active FP state is what is expected (IEEE compliant, round to nearest)
- L15 _prototype_ `void SetProblematicFloatingPointStateForTesting();` (scope `uLang`) — Sets machine floating point state to problematic values (round to zero, flush-to-zero on). Intended for FP state save/restore tests.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/MathUtils.h` (Public)


#### class `uLang::CMath`  
`class CMath`  
_L13-116_
- L19 _public function_ `template<typename T> static constexpr T Max(const T A, const T B)` — Returns higher value in a generic way
- L26 _public function_ `template<typename T> static constexpr T Min(const T A, const T B)` — Returns lower value in a generic way
- L33 _public function_ `template<typename T> static constexpr T Clamp(const T X, const T Min, const T Max)` — Clamps X to be between Min and Max, inclusive
- L40 _public function_ `template <class T> static constexpr bool IsPowerOf2(const T X)` — Checks if a number is a power of two
- L46 _public function_ `static float Loge(float Value)` — Computes natural logarithm
- L51 _public prototype_ `static double Extensionalize(double Value);`
- L53 _public prototype_ `static double ToFloat(int64_t Value);`
- L58 _public prototype_ `static double FloatAdd(double Left, double Right);` — Arithmetic operations in a non-fast-math environment (IEEE compliant). These can (mostly) be removed when callers are guaranteed to not be compiled with fast-math or similar enabled.
- L59 _public prototype_ `static double FloatSubtract(double Left, double Right);`
- L60 _public prototype_ `static double FloatMultiply(double Left, double Right);`
- L61 _public prototype_ `static double FloatDivide(double Left, double Right);`
- L64 _public function_ `static double ReinterpretInt64AsDouble(uint64_t Int)` — FP special constants: NaN and infinity.
- L71 _public function_ `static double FloatNaN()`
- L72 _public function_ `static double FloatInfinity()`
- L75 _public prototype_ `static bool FloatIsFinite(double Value);` — Predicates for different FP specials.
- L76 _public prototype_ `static bool FloatIsInfinite(double Value);`
- L77 _public prototype_ `static bool FloatIsNaN(double Value);`
- L81 _public prototype_ `static bool FloatEqual(double Left, double Right);` — We use an ordering relationship different from the default IEEE float ordering (because we require NaNs to compare equal to each other).
- L82 _public prototype_ `static bool FloatLess(double Left, double Right);`
- L83 _public prototype_ `static bool FloatLessEqual(double Left, double Right);`
- L87 _public function_ `static bool FloatNotEqual(double Left, double Right)`
- L92 _public function_ `static bool FloatGreater(double Left, double Right)`
- L97 _public function_ `static bool FloatGreaterEqual(double Left, double Right)`
- L115 _public prototype_ `static int64_t FloatRanking(double Value);` — Ranking function that turns a double into an int64 that defines a total order compatible with the ordering implied for floats, to be precise FloatLess(a,b)  =>  FloatRanking(a) < FloatRanking(b) FloatEqual(a,b) <=> FloatRanking(a) == FloatRanking(b) For FloatLess(a,b), we only have implication in one direction because when a single NaN is involved, the strict "less" ordering relationship is partial. In the total order implied by FloatRanking, NaN compares larger than all other floats. Unlike normal IEEE semantics, NaNs compare equal to each other in our ordering, so for FloatEqual we have full equivalence. FloatRanking can be used directly or as a key for sorted maps and hashes.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/Optional.h` (Public)


#### struct `uLang::TOptional`  
`template<typename OptionalType> struct AUTORTFM_INFER TOptional`  
_L23-186_
- desc: When we have an optional value IsSet() returns true, and GetValue() is meaningful. Otherwise GetValue() is not meaningful.
- L27 _public function_ `TOptional(const OptionalType& Value)` — Construct an OptionaType with a valid value.
- L32 _public function_ `TOptional(OptionalType&& Value)`
- L39 _public function_ `TOptional(EResult Result = EResult::Unspecified) : _Result(Result)` — Construct an OptionalType with no value; i.e. unset
- L45 _public function_ `~TOptional()`
- L51 _public function_ `TOptional(const TOptional& Value) : _Result(Value._Result)` — Copy/Move construction
- L59 _public function_ `TOptional(TOptional&& Value) : _Result(Value._Result)`
- L68 _public function_ `TOptional& operator=(const TOptional& Value)`
- L81 _public function_ `TOptional& operator=(TOptional&& Value)`
- L95 _public function_ `TOptional& operator=(const OptionalType& Value)`
- L105 _public function_ `TOptional& operator=(OptionalType&& Value)`
- L116 _public function_ `void Reset()`
- L128 _public function_ `template <typename... ArgsType> void Emplace(ArgsType&&... Args)`
- L162 _public function_ `bool IsSet() const` — @return true when the value is meaningful; false if calling GetValue() is undefined.
- L163 _public function_ `EResult GetResult() const`
- L164 _public function_ `explicit operator bool() const`
- L166 _public function_ `operator OptionalType*()`
- L167 _public function_ `operator const OptionalType*() const`
- L170 _public function_ `const OptionalType& GetValue() const` — @return The optional value; undefined when IsSet() returns false.
- L171 _public function_ `OptionalType& GetValue()`
- L174 _public function_ `const OptionalType& operator*() const` — @return The optional value; undefined when IsSet() returns false.
- L175 _public function_ `OptionalType& operator*()`
- L177 _public function_ `const OptionalType* operator->() const`
- L178 _public function_ `OptionalType* operator->()`
- L181 _public function_ `const OptionalType& Get(const OptionalType& DefaultValue) const` — @return The optional value when set; DefaultValue otherwise.
- L184 _private member_ `TTypeCompatibleBytes<OptionalType> _Value;`
- L185 _private member_ `EResult _Result;`

#### enum `uLang::TIsOptional::(anonymous)`  
`template <typename T> struct TIsOptional`  
_L188-188_

#### struct `uLang::TIsOptional`  
`template <typename T> struct TIsOptional`  
_L188-188_

#### enum `uLang::TIsOptional::(anonymous)`  
`template <typename T> struct TIsOptional`  
_L189-189_

#### struct `uLang::TIsOptional`  
`template <typename T> struct TIsOptional`  
_L189-189_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L121 _typedef_ `using OptionalDestructOptionalType = OptionalType;` (scope `uLang::TOptional::Reset`) — We need a typedef here because VC won't compile the destructor call below if OptionalType itself has a member called OptionalType
- L135 _function_ `friend bool operator==(const TOptional& lhs, const TOptional& rhs)` (scope `uLang`)
- L148 _function_ `friend bool operator!=(const TOptional& lhs, const TOptional& rhs)` (scope `uLang`)
- L188 _enumerator_ `template <typename T> struct TIsOptional { enum { Value = false }; }; template <typename T> struct TIsOptional<TOptional<T>> { enum { Value = true }; };` (scope `uLang::TIsOptional::__anon16cd1d270103`)
- L189 _enumerator_ `template <typename T> struct TIsOptional<TOptional<T>> { enum { Value = true }; };` (scope `uLang::TIsOptional::__anon16cd1d270203`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/RandomStream.h` (Public)


#### class `uLang::CRandomStream`  
`class CRandomStream`  
_L15-74_
- desc: Implements a thread-safe random number stream. Very bad quality in the lower bits. Don't use the modulus (%) operator.
- L20 _public function_ `CRandomStream(int32_t Seed = 0) : _Seed(Seed)` — Default constructor.
- L28 _public function_ `void Initialize(int32_t Seed)` — Initializes this random stream with the specified seed value. @param Seed The seed value.
- L34 _public function_ `int32_t RandRange(int32_t Min, int32_t Max)` — @return A random number >= Min and <= Max
- L43 _public function_ `float FRandRange(float Min, float Max)` — @return A random number >= Min and < Max
- L55 _public function_ `bool RandBool()` — @return A random boolean
- L64 _protected function_ `void MutateSeed()` — Mutates the current seed into the next seed.
- L73 _private member_ `uint32_t _Seed;` — Holds the current seed. This should be an uint32 so that any shift to obtain top bits is a logical shift, rather than an arithmetic shift (which smears down the negative bit).

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/Threading.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace uLang`
- L17 _function_ `inline uint32_t InterlockedCompareExchange(volatile uint32_t* Value, uint32_t ReplaceWithThis, uint32_t IfEqualToThis)` (scope `uLang`)
- L22 _function_ `inline void* InterlockedCompareExchange(void* volatile* Value, void* ReplaceWithThis, void* IfEqualToThis)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Misc/Union.h` (Public)


#### struct `uLang::TDisambiguater`  
`template<uint32_t> struct TDisambiguater`  
_L23-26_
- desc: Used to disambiguate methods that are overloaded for all possible subtypes of a TUnion where the subtypes may not be distinct.
- L25 _public function_ `TDisambiguater()`

#### class `uLang::FNull`  
`class FNull`  
_L29-42_
- L33 _public function_ `bool operator==(const FNull&) const`
- L38 _public function_ `bool operator!=(const FNull&) const`

#### class `uLang::TUnion`  
`template<typename TypeA, typename TypeB = FNull, typename TypeC = FNull, typename TypeD = FNull, typename TypeE = FNull, typename TypeF = FNull> class TUnion`  
_L51-335_
- desc: Represents a type which is the union of several other types; i.e. it can have a value whose type is of any the union's subtypes. This differs from C union types by being type-safe, and supporting non-trivial data types as subtypes. Since a value for the union must be of a single subtype, the union stores potential values of different subtypes in overlapped memory, and keeps track of which one is currently valid.
- L56 _public function_ `TUnion()` — Default constructor.
- L61 _public function_ `explicit TUnion(typename TCallTraits<TypeA>::ParamType InValue, TDisambiguater<0> Disambiguater = TDisambiguater<0>()) : CurrentSubtypeIndex(uint8_t(-1))` — Initialization constructor.
- L68 _public function_ `explicit TUnion(typename TCallTraits<TypeB>::ParamType InValue, TDisambiguater<1> Disambiguater = TDisambiguater<1>()) : CurrentSubtypeIndex(uint8_t(-1))` — Initialization constructor.
- L75 _public function_ `explicit TUnion(typename TCallTraits<TypeC>::ParamType InValue, TDisambiguater<2> Disambiguater = TDisambiguater<2>()) : CurrentSubtypeIndex(uint8_t(-1))` — Initialization constructor.
- L82 _public function_ `explicit TUnion(typename TCallTraits<TypeD>::ParamType InValue, TDisambiguater<3> Disambiguater = TDisambiguater<3>()) : CurrentSubtypeIndex(uint8_t(-1))` — Initialization constructor.
- L89 _public function_ `explicit TUnion(typename TCallTraits<TypeE>::ParamType InValue, TDisambiguater<4> Disambiguater = TDisambiguater<4>()) : CurrentSubtypeIndex(uint8_t(-1))` — Initialization constructor.
- L96 _public function_ `explicit TUnion(typename TCallTraits<TypeF>::ParamType InValue, TDisambiguater<5> Disambiguater = TDisambiguater<5>()) : CurrentSubtypeIndex(uint8_t(-1))` — Initialization constructor.
- L103 _public function_ `TUnion(const TUnion& Other) : CurrentSubtypeIndex(uint8_t(-1))` — Copy constructor.
- L110 _public function_ `~TUnion()` — Destructor.
- L118 _public function_ `template<typename Subtype> bool HasSubtype() const` — @return True if the union's value is of the given subtype.
- L130 _public function_ `template<typename Subtype> void ResetSubtype()` — If the union's current value is of the given subtype, sets the union's value to a NULL value.
- L149 _public function_ `template<typename Subtype> const Subtype& GetSubtype() const` — @return A reference to the union's value of the given subtype.  May only be called if the union's HasSubtype()==true for the given subtype.
- L164 _public function_ `template<typename Subtype> Subtype& GetSubtype()` — @return A reference to the union's value of the given subtype.  May only be called if the union's HasSubtype()==true for the given subtype.
- L179 _public function_ `template<typename Subtype> Subtype* SetSubtype(typename TCallTraits<Subtype>::ParamType NewValue)` — Replaces the value of the union with a value of the given subtype.
- L194 _public function_ `uint8_t GetCurrentSubtypeIndex() const` — @return The index corresponding to the type currently stored in this union; useful for writing switches and indexing into tables.
- L200 _public function_ `void Reset()` — Sets the union's value to NULL.
- L215 _public function_ `TUnion& operator=(const TUnion& Other)`
- L234 _public function_ `bool operator==(const TUnion& Other) const` — Equality comparison.
- L265 _private member_ `} Values;`
- L268 _private member_ `uint8_t CurrentSubtypeIndex;` — The index of the subtype that the union's current value is of.
- L272 _private function_ `template<typename Subtype> Subtype& InitSubtype()` — Sets the union's value to a default value of the given subtype.
- L280 _private function_ `template<typename Subtype, typename PointerType> static void GetSubtypeIndexAndReference( const TUnion& Union, int32_t& OutIndex, PointerType& OutValuePointer )` — Determines the index and reference to the potential value for the given union subtype.
- L331 _private function_ `static void FatalErrorUndefinedSubtype()`

#### union `uLang::TUnion::(anonymous)`  
``  
_L258-265_

#### Free symbols / members of external scopes

- L17 _macro_ `#define TEMPLATE_PARAMETERS2(X,Y) X,Y`
- L19 _namespace_ `namespace uLang`
- L259 _member_ `TTypeCompatibleBytes<TypeA> A;` (scope `uLang::TUnion::__anon05c6c90a010a`)
- L260 _member_ `TTypeCompatibleBytes<TypeB> B;` (scope `uLang::TUnion::__anon05c6c90a010a`)
- L261 _member_ `TTypeCompatibleBytes<TypeC> C;` (scope `uLang::TUnion::__anon05c6c90a010a`)
- L262 _member_ `TTypeCompatibleBytes<TypeD> D;` (scope `uLang::TUnion::__anon05c6c90a010a`)
- L263 _member_ `TTypeCompatibleBytes<TypeE> E;` (scope `uLang::TUnion::__anon05c6c90a010a`)
- L264 _member_ `TTypeCompatibleBytes<TypeF> F;` (scope `uLang::TUnion::__anon05c6c90a010a`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/Android/AndroidCommon.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define ULANG_BREAK() __asm__(".inst 0xd4200000")`
- L11 _macro_ `#define ULANG_BREAK() __asm__("trap")`
- L13 _macro_ `#define ULANG_BREAK() __asm__("int $3")`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/IOS/IOSCommon.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define ULANG_BREAK() __asm__("int $3")`
- L11 _macro_ `#define ULANG_BREAK() __asm__("svc 0")`
- L13 _macro_ `#define ULANG_BREAK() __asm__("trap")`
- L20 _macro_ `#define RAPIDJSON_SYMBOL_VISIBILITY_OVERRIDE 1`
- L22 _macro_ `#define RAPIDJSON_SYMBOL_VISIBILITY_OVERRIDE 0`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/Linux/LinuxCommon.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_START \`
- L12 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_END \`
- L20 _macro_ `#define ULANG_BREAK() __asm__(".inst 0xd4200000")`
- L22 _macro_ `#define ULANG_BREAK() __asm__("trap")`
- L24 _macro_ `#define ULANG_BREAK() __asm__ volatile("int $3")`
- L27 _namespace_ `namespace uLang`
- L33 _function_ `inline bool IsDebuggerPresent()` (scope `uLang`)
- L41 _function_ `inline void LogDebugMessage(const char* Message)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/Mac/MacCommon.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_START _Pragma("clang diagnostic push") \`
- L10 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_END _Pragma("clang diagnostic pop")`
- L16 _macro_ `#define ULANG_BREAK() __asm__(".inst 0xd4200000")`
- L18 _macro_ `#define ULANG_BREAK() __asm__("trap")`
- L20 _macro_ `#define ULANG_BREAK() __asm__("int $3")`
- L23 _namespace_ `namespace uLang`
- L29 _function_ `inline bool IsDebuggerPresent()` (scope `uLang`)
- L37 _function_ `inline void LogDebugMessage(const char* Message)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/TVOS/TVOSCommon.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define ULANG_BREAK() __asm__("int $3")`
- L11 _macro_ `#define ULANG_BREAK() __asm__("svc 0")`
- L13 _macro_ `#define ULANG_BREAK() __asm__("trap")`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/Windows/WindowsCommon.h` (Public)


#### Free symbols / members of external scopes

- L11 _prototype_ `extern "C"`
- L12 _prototype_ `extern "C"`
- L18 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_START \`
- L21 _macro_ `#define ULANG_SILENCE_SECURITY_WARNING_END \`
- L28 _macro_ `#define ULANG_BREAK() __debugbreak()`
- L30 _namespace_ `namespace uLang`
- L36 _function_ `inline bool IsDebuggerPresent()` (scope `uLang`)
- L44 _function_ `inline void LogDebugMessage(const char* Message)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Platform/Windows/WindowsThreading.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L10 _function_ `inline uint32_t InterlockedCompareExchange(volatile uint32_t* Value, uint32_t ReplaceWithThis, uint32_t IfEqualToThis)` (scope `uLang`)
- L15 _function_ `inline void* InterlockedCompareExchange(void* volatile* Value, void* ReplaceWithThis, void* IfEqualToThis)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Templates/IdentityFunctor.h` (Public)


#### struct `uLang::FIdentityFunctor`  
`struct FIdentityFunctor`  
_L14-21_
- desc: A functor which returns whatever is passed to it.  Mainly used for generic composition.
- L17 _public function_ `template <typename T> T&& operator()(T&& Val) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Templates/Invoke.h` (Public)


#### struct `uLang::Private::TVoid`  
`template <typename T> struct TVoid`  
_L126-129_
- L128 _public typedef_ `typedef void Type;`

#### struct `uLang::Private::TIsInvocableImpl`  
`template <typename, typename CallableType, typename... ArgTypes> struct TIsInvocableImpl`  
_L132-135_
- L134 _public member_ `static constexpr bool Value = false;`
- L140 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::Private::TIsInvocableImpl`  
`template <typename CallableType, typename... ArgTypes> struct TIsInvocableImpl<typename TVoid<decltype(uLang::Invoke(DeclVal<CallableType>(), DeclVal<ArgTypes>()...))>::Type, CallableType, ArgTypes...>`  
_L138-141_
- L134 _public member_ `static constexpr bool Value = false;`
- L140 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsInvocable`  
`template <typename CallableType, typename... ArgTypes> struct TIsInvocable : Private::TIsInvocableImpl<void, CallableType, ArgTypes...>`  
_L159-161_
- inherits: `Private::TIsInvocableImpl<void,CallableType,ArgTypes...>`
- desc: Traits class which tests if an instance of CallableType can be invoked with a list of the arguments of the types provided. Examples: IsInvocable<void()>::Value == true IsInvocable<void(), FString>::Value == false IsInvocable<void(FString), FString>::Value == true IsInvocable<void(FString), const TCHAR*>::Value == true IsInvocable<void(FString), int32>::Value == false IsInvocable<void(char, float, bool), int, int, int>::Value == true IsInvocable<TFunction<void(FString)>, FString>::Value == true IsInvocable<TFunction<void(FString)>, int32>::Value == false

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L17 _namespace_ `namespace Private` (scope `uLang`)
- L21 _function_ `template <typename BaseType, typename CallableType> requires (std::is_convertible_v<typename TDecay<CallableType>::Type*, typename TDecay<BaseType>::Type*>) auto DereferenceIfNecessary(CallableType&& Callable) -> decltype((CallableType&&)Callable)` (scope `uLang::Private`)
- L28 _function_ `template <typename BaseType, typename CallableType> requires (!std::is_convertible_v<typename TDecay<CallableType>::Type*, typename TDecay<BaseType>::Type*>) auto DereferenceIfNecessary(CallableType&& Callable) -> decltype(*(CallableType&&)Callable)` (scope `uLang::Private`)
- L48 _function_ `template <typename FuncType, typename... ArgTypes> AUTORTFM_INFER auto Invoke(FuncType&& Func, ArgTypes&&... Args) -> decltype(uLang::ForwardArg<FuncType>(Func)(uLang::ForwardArg<ArgTypes>(Args)...))` (scope `uLang`) — Invokes a callable with a set of arguments.  Allows the following: - Calling a functor object given a set of arguments. - Calling a function pointer given a set of arguments. - Calling a member function given a reference to an object and a set of arguments. - Calling a member function given a pointer (including smart pointers) to an object and a set of arguments. - Projecting via a data member pointer given a reference to an object. - Projecting via a data member pointer given a pointer (including smart pointers) to an object. See: http://en.cppreference.com/w/cpp/utility/functional/invoke
- L55 _function_ `template <typename ReturnType, typename ObjType, typename CallableType> auto Invoke(ReturnType ObjType::*pdm, CallableType&& Callable) -> decltype(Private::DereferenceIfNecessary<ObjType>(uLang::ForwardArg<CallableType>(Callable)).*pdm)` (scope `uLang`)
- L62 _function_ `template <typename ReturnType, typename ObjType, typename... PMFArgTypes, typename CallableType, typename... ArgTypes> auto Invoke(ReturnType (ObjType::*PtrMemFun)(PMFArgTypes...), CallableType&& Callable, ArgTypes&&... Args) -> decltype((Private::DereferenceIfNecessary<ObjType>(uLang::ForwardArg<CallableType>(Callable)).*PtrMemFun)(uLang::ForwardArg<ArgTypes>(Args)...))` (scope `uLang`)
- L69 _function_ `template <typename ReturnType, typename ObjType, typename... PMFArgTypes, typename CallableType, typename... ArgTypes> auto Invoke(ReturnType (ObjType::*PtrMemFun)(PMFArgTypes...) const, CallableType&& Callable, ArgTypes&&... Args) -> decltype((Private::DereferenceIfNecessary<ObjType>(uLang::ForwardArg<CallableType>(Callable)).*PtrMemFun)(uLang::ForwardArg<ArgTypes>(Args)...))` (scope `uLang`)
- L90 _macro_ `#define ULANG_PROJECTION(FuncName) \` — Wraps up a named non-member function so that it can easily be passed as a callable. This allows functions with overloads or default arguments to be treated correctly. Example: TArray<FMyType> Array = ...; // Doesn't compile, because you can't take the address of an overloaded function when its type needs to be deduced. Algo::SortBy(Array, &LexToString); // Works as expected Algo::SortBy(Array, PROJECTION(LexToString));
- L111 _macro_ `#define ULANG_PROJECTION_MEMBER(Type, FuncName) \` — Wraps up a named member function so that it can easily be passed as a callable. This allows functions with overloads or default arguments to be treated correctly. Example: TArray<UObject*> Array = ...; // Doesn't compile, because &UObject::GetFullName loses the default argument and passes // FString (UObject::*)(const UObject*) to Algo::SortBy<>(), which is not a valid projection. Algo::SortBy(Array, &UObject::GetFullName); // Works as expected Algo::SortBy(Array, PROJECTION_MEMBER(UObject, GetFullName));
- L120 _namespace_ `namespace Private` (scope `uLang`)
- L123 _prototype_ `template <typename T> T&& DeclVal();` (scope `uLang::Private`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Templates/References.h` (Public)


#### struct `uLang::Private::TDecayNonReference`  
`template <typename T> struct TDecayNonReference`  
_L19-22_
- L21 _public typedef_ `using Type = typename std::remove_cv_t<T>;`
- L27 _public typedef_ `using Type = T*;`
- L39 _public typedef_ `using Type = RetType (*)(Params...);`

#### struct `uLang::Private::TDecayNonReference`  
`template <typename T> struct TDecayNonReference<T[]>`  
_L25-28_
- L21 _public typedef_ `using Type = typename std::remove_cv_t<T>;`
- L27 _public typedef_ `using Type = T*;`
- L39 _public typedef_ `using Type = RetType (*)(Params...);`

#### struct `uLang::Private::TDecayNonReference`  
`template <typename T, uint32_t N> struct TDecayNonReference<T[N]>`  
_L31-34_
- L21 _public typedef_ `using Type = typename std::remove_cv_t<T>;`
- L27 _public typedef_ `using Type = T*;`
- L39 _public typedef_ `using Type = RetType (*)(Params...);`

#### struct `uLang::Private::TDecayNonReference`  
`template <typename RetType, typename... Params> struct TDecayNonReference<RetType(Params...)>`  
_L37-40_
- L21 _public typedef_ `using Type = typename std::remove_cv_t<T>;`
- L27 _public typedef_ `using Type = T*;`
- L39 _public typedef_ `using Type = RetType (*)(Params...);`

#### struct `uLang::TDecay`  
`template <typename T> struct TDecay`  
_L50-53_
- desc: Returns the decayed type of T, meaning it removes all references, qualifiers and applies array-to-pointer and function-to-pointer conversions. http://en.cppreference.com/w/cpp/types/decay
- L52 _public typedef_ `using Type = typename Private::TDecayNonReference<typename std::remove_reference_t<T>>::Type;`

#### struct `uLang::TRemovePointer`  
`template <typename T> struct TRemovePointer`  
_L69-69_
- desc: Removes one level of pointer from a type, e.g.: TRemovePointer<      int32  >::Type == int32 TRemovePointer<      int32* >::Type == int32 TRemovePointer<      int32**>::Type == int32* TRemovePointer<const int32* >::Type == const int32
- L69 _public typedef_ `template <typename T> struct TRemovePointer { typedef T Type; };` — Removes one level of pointer from a type, e.g.: TRemovePointer<      int32  >::Type == int32 TRemovePointer<      int32* >::Type == int32 TRemovePointer<      int32**>::Type == int32* TRemovePointer<const int32* >::Type == const int32

#### struct `uLang::TRemovePointer`  
`template <typename T> struct TRemovePointer`  
_L70-70_
- desc: Removes one level of pointer from a type, e.g.: TRemovePointer<      int32  >::Type == int32 TRemovePointer<      int32* >::Type == int32 TRemovePointer<      int32**>::Type == int32* TRemovePointer<const int32* >::Type == const int32
- L69 _public typedef_ `template <typename T> struct TRemovePointer { typedef T Type; };` — Removes one level of pointer from a type, e.g.: TRemovePointer<      int32  >::Type == int32 TRemovePointer<      int32* >::Type == int32 TRemovePointer<      int32**>::Type == int32* TRemovePointer<const int32* >::Type == const int32

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L16 _namespace_ `namespace Private` (scope `uLang`)
- L56 _typedef_ `template <typename T> using TDecayT = typename TDecay<T>::Type;` (scope `uLang`)
- L78 _function_ `template <typename T> typename std::remove_reference_t<T>&& Move(T&& Obj)` (scope `uLang`) — Move will cast a reference to an rvalue reference. This is UE's equivalent of std::move except that it will not compile when passed an rvalue or const object, because we would prefer to be informed when Move will have no effect.
- L80 _typedef_ `using CastType = typename std::remove_reference_t<T>;` (scope `uLang::Move`)
- L96 _function_ `template <typename T> typename std::remove_reference_t<T>&& MoveIfPossible(T&& Obj)` (scope `uLang`) — MoveIfPossible will cast a reference to an rvalue reference. This is UE's equivalent of std::move.  It doesn't static assert like Move, because it is useful in templates or macros where it's not obvious what the argument is, but you want to take advantage of move semantics where you can but not stop compilation.
- L98 _typedef_ `using CastType = typename std::remove_reference_t<T>;` (scope `uLang::MoveIfPossible`)
- L107 _function_ `template <typename T> T&& ForwardArg(typename std::remove_reference_t<T>& Obj)` (scope `uLang`) — ForwardArg will cast a reference to an rvalue reference. This is UE's equivalent of std::forward.
- L113 _function_ `template <typename T> T&& ForwardArg(typename std::remove_reference_t<T>&& Obj)` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Templates/Sorting.h` (Public)


#### struct `uLang::SIdentityFunctor`  
`struct SIdentityFunctor`  
_L19-26_
- desc: A functor which returns whatever is passed to it.  Mainly used for generic composition.
- L22 _public function_ `template <typename T> T&& operator()(T&& Val) const`

#### struct `uLang::TLess`  
`template <typename T = void> struct TLess`  
_L37-43_
- desc: Binary predicate class for sorting elements in order.  Assumes < operator is defined for the template type. See: http://en.cppreference.com/w/cpp/utility/functional/less
- L39 _public function_ `bool operator()(const T& A, const T& B) const`
- L49 _public function_ `template <typename T> bool operator()(const T& A, const T& B) const`

#### struct `uLang::TLess`  
`template <> struct TLess<void>`  
_L46-53_
- L39 _public function_ `bool operator()(const T& A, const T& B) const`
- L49 _public function_ `template <typename T> bool operator()(const T& A, const T& B) const`

#### class `uLang::TReversePredicate`  
`template <typename PredicateType> class TReversePredicate`  
_L63-74_
- desc: Helper class to reverse a predicate. Performs Predicate(B, A)
- L65 _private member_ `const PredicateType& _Predicate;`
- L68 _public function_ `TReversePredicate( const PredicateType& Predicate ) : _Predicate( Predicate )`
- L73 _public function_ `template <typename T> bool operator()( T&& A, T&& B ) const`

#### struct `uLang::TDereferenceWrapper`  
`template<class PredicateType> struct TDereferenceWrapper`  
_L83-97_
- desc: Helper class for dereferencing pointer types in Sort function
- L85 _public member_ `const PredicateType& _Predicate;`
- L87 _public function_ `TDereferenceWrapper( const PredicateType& Predicate ) : _Predicate( Predicate )`
- L93 _public function_ `template<class T> requires (std::is_pointer_v<T>) bool operator()(const T A, const T B) const` — Pass through for non-pointer types
- L96 _public function_ `template<class T> requires (!std::is_pointer_v<T>) bool operator()(const T& A, const T& B) const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Templates/Storage.h` (Public)


#### struct `uLang::TTypeCompatibleBytes`  
`template<typename ElementType> struct TTypeCompatibleBytes`  
_L106-119_
- desc: An untyped array of data with compile-time alignment and size derived from another type.
- L108 _public function_ `ElementType& Get()`
- L112 _public function_ `const ElementType& Get() const`
- L118 _private member_ `alignas(ElementType) uint8_t _Bytes[sizeof(ElementType)];`

#### struct `uLang::TUseBitwiseSwap`  
`template <typename T> struct TUseBitwiseSwap`  
_L128-132_
- desc: A traits class which specifies whether a Swap of a given type should swap the bits or use a traditional value-based swap.
- L131 _public member_ `static constexpr bool Value = !(std::is_enum_v<T> || std::is_pointer_v<T> || std::is_arithmetic_v<T>);` — We don't use bitwise swapping for 'register' types because this will force them into memory and be slower.

#### class `uLang::CNoncopyable`  
`class CNoncopyable`  
_L166-179_
- desc: utility template for a class that should not be copyable. Derive from this class to make your class non-copyable
- L170 _protected prototype_ `CNoncopyable() = default;` — ensure the class cannot be constructed directly
- L172 _protected prototype_ `~CNoncopyable() = default;` — the class should not be used polymorphically
- L175 _private prototype_ `CNoncopyable(const CNoncopyable&) = delete;`
- L176 _private prototype_ `CNoncopyable(CNoncopyable&&) = delete;`
- L177 _private prototype_ `CNoncopyable& operator=(const CNoncopyable&) = delete;`
- L178 _private prototype_ `CNoncopyable& operator=(CNoncopyable&&) = delete;`

#### struct `uLang::TGuardValue`  
`template <typename RefType, typename AssignedType = RefType> struct TGuardValue : private CNoncopyable`  
_L189-221_
- inherits: `CNoncopyable`
- desc: exception-safe guard around saving/restoring a value. Commonly used to make sure a value is restored even if the code early outs in the future. Usage: TGuardValue<bool> GuardSomeBool(bSomeBool, false); // Sets bSomeBool to false, and restores it in dtor.
- L191 _public function_ `TGuardValue(RefType& ReferenceValue, const AssignedType& NewValue) : RefValue(ReferenceValue), OldValue(Move(ReferenceValue))`
- L197 _public function_ `explicit TGuardValue(RefType& ReferenceValue) : RefValue(ReferenceValue), OldValue(ReferenceValue)`
- L202 _public function_ `~TGuardValue()`
- L213 _public function_ `const AssignedType& operator*() const` — Overloaded dereference operator. Provides read-only access to the original value of the data being tracked by this struct @return	a const reference to the original data value
- L219 _private member_ `RefType& RefValue;`
- L220 _private member_ `AssignedType OldValue;`

#### struct `uLang::TGuard`  
`template <typename Function> struct TGuard : private CNoncopyable`  
_L224-240_
- inherits: `CNoncopyable`
- L228 _public function_ `template <typename... TArgs> requires (std::is_constructible_v<Function, TArgs&&...>) explicit TGuard(TArgs&&... Args) : _Function(uLang::ForwardArg<TArgs>(Args)...)`
- L233 _public function_ `~TGuard()`
- L239 _private member_ `Function _Function;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace uLang`
- L30 _function_ `template<typename T> requires (TIsContiguousContainer<T>::Value) auto ULangGetData(T&& Container) -> decltype(Container.GetData())` (scope `uLang`) — Generically gets the data pointer of a contiguous container Named differently from GetData() in UnrealTemplate.h to avoid ambiguous overload resolution.
- L36 _function_ `template <typename T, size_t N> constexpr T* ULangGetData(T (&Container)[N])` (scope `uLang`)
- L42 _function_ `template <typename T> constexpr T* ULangGetData(std::initializer_list<T> List)` (scope `uLang`)
- L48 _function_ `template <typename FirstIterator, typename LastIterator> constexpr FirstIterator ULangGetData(const TRangeView<FirstIterator, LastIterator>& View)` (scope `uLang`)
- L59 _function_ `template<typename T> requires (TIsContiguousContainer<T>::Value) size_t ULangGetNum(T&& Container)` (scope `uLang`) — Generically gets the number of items in a contiguous container Named differently from GetNum() in UnrealTemplate.h to avoid ambiguous overload resolution.
- L65 _function_ `template <typename T, size_t N> constexpr size_t ULangGetNum(T (&Container)[N])` (scope `uLang`)
- L71 _function_ `template <typename T> constexpr size_t ULangGetNum(std::initializer_list<T> List)` (scope `uLang`)
- L77 _function_ `template <typename FirstIterator, typename LastIterator> constexpr int32_t ULangGetNum(const TRangeView<FirstIterator, LastIterator>& View)` (scope `uLang`)
- L94 _function_ `template <typename T> constexpr T AlignUp(T Val, uint64_t Alignment)` (scope `uLang`) — Aligns a value to the nearest higher multiple of 'Alignment', which must be a power of two. @param  Val        The value to align. @param  Alignment  The alignment value, must be a power of two. @return The value aligned up to the specified alignment.
- L140 _function_ `template <typename T> requires (TUseBitwiseSwap<T>::Value) inline void Swap(T& A, T& B)` (scope `uLang`) — Swap two values.  Assumes the types are trivially relocatable.
- L155 _function_ `template <typename T> requires (!TUseBitwiseSwap<T>::Value) inline void Swap(T& A, T& B)` (scope `uLang`)
- L243 _prototype_ `template <typename Function> TGuard(Function&&) -> TGuard<std::decay_t<Function>>;` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Templates/TypeTraits.h` (Public)


#### struct `uLang::TIsConstructible`  
`template <typename T, typename... Args> struct TIsConstructible`  
_L20-23_
- desc: Determines if T is constructible from a set of arguments.
- L22 _public member_ `static constexpr bool Value = __is_constructible(T, Args...);`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer`  
_L34-37_
- desc: Traits class which tests if a type is a contiguous container. Requires: [ &Container[0], &Container[0] + Num ) is a valid range
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer< T& > : TIsContiguousContainer<T>`  
_L39-39_
- inherits: `TIsContiguousContainer<T>`
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer< T& > : TIsContiguousContainer<T>`  
_L40-40_
- inherits: `TIsContiguousContainer<T>`
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer< T& > : TIsContiguousContainer<T>`  
_L41-41_
- inherits: `TIsContiguousContainer<T>`
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer< T& > : TIsContiguousContainer<T>`  
_L42-42_
- inherits: `TIsContiguousContainer<T>`
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer< T&&> : TIsContiguousContainer<T>`  
_L43-43_
- inherits: `TIsContiguousContainer<T>`
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T, size_t N> struct TIsContiguousContainer< T[N]>`  
_L48-48_
- desc: Specialization for C arrays (always contiguous)
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T, size_t N> struct TIsContiguousContainer< T[N]>`  
_L49-49_
- desc: Specialization for C arrays (always contiguous)
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T, size_t N> struct TIsContiguousContainer< T[N]>`  
_L50-50_
- desc: Specialization for C arrays (always contiguous)
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T, size_t N> struct TIsContiguousContainer< T[N]>`  
_L51-51_
- desc: Specialization for C arrays (always contiguous)
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsContiguousContainer`  
`template <typename T> struct TIsContiguousContainer<std::initializer_list<T>>`  
_L57-60_
- desc: Specialization for initializer lists (also always contiguous)
- L36 _public member_ `static constexpr bool Value = false;`
- L48 _public member_ `template <typename T, size_t N> struct TIsContiguousContainer< T[N]> { static constexpr bool Value = true; };` — Specialization for C arrays (always contiguous)
- L59 _public member_ `static constexpr bool Value = true;`

#### struct `uLang::TIsZeroConstructType`  
`template<typename T> struct TIsZeroConstructType`  
_L69-72_
- desc: TIsZeroConstructType
- L71 _public member_ `static constexpr bool Value = std::is_enum_v<T> || std::is_arithmetic_v<T> || std::is_pointer_v<T>;`

#### struct `uLang::TCallTraitsParamTypeHelper`  
`template <typename T, bool TypeIsSmall> struct TCallTraitsParamTypeHelper`  
_L82-86_
- desc: Call traits helpers
- L84 _public typedef_ `using ParamType = const T&;`
- L85 _public typedef_ `using ConstParamType = const T&;`
- L90 _public typedef_ `using ParamType = const T;`
- L91 _public typedef_ `using ConstParamType = const T;`
- L96 _public typedef_ `using ParamType = T*;`
- L97 _public typedef_ `using ConstParamType = const T*;`

#### struct `uLang::TCallTraitsParamTypeHelper`  
`template <typename T> struct TCallTraitsParamTypeHelper<T, true>`  
_L88-92_
- L84 _public typedef_ `using ParamType = const T&;`
- L85 _public typedef_ `using ConstParamType = const T&;`
- L90 _public typedef_ `using ParamType = const T;`
- L91 _public typedef_ `using ConstParamType = const T;`
- L96 _public typedef_ `using ParamType = T*;`
- L97 _public typedef_ `using ConstParamType = const T*;`

#### struct `uLang::TCallTraitsParamTypeHelper`  
`template <typename T> struct TCallTraitsParamTypeHelper<T*, true>`  
_L94-98_
- L84 _public typedef_ `using ParamType = const T&;`
- L85 _public typedef_ `using ConstParamType = const T&;`
- L90 _public typedef_ `using ParamType = const T;`
- L91 _public typedef_ `using ConstParamType = const T;`
- L96 _public typedef_ `using ParamType = T*;`
- L97 _public typedef_ `using ConstParamType = const T*;`

#### struct `uLang::TCallTraitsBase`  
`template <typename T> struct TCallTraitsBase`  
_L115-126_
- desc: base class for call traits. Used to more easily refine portions when specializing
- L118 _private member_ `static constexpr bool PassByValue = ((sizeof(T) <= sizeof(void*)) && std::is_trivial_v<T> && std::is_standard_layout_v<T>) || std::is_arithmetic_v<T> || std::is_pointer_v<T>;`
- L121 _public typedef_ `using ValueType = T;`
- L122 _public typedef_ `using Reference = T&;`
- L123 _public typedef_ `using ConstReference = const T&;`
- L124 _public typedef_ `using ParamType = typename TCallTraitsParamTypeHelper<T, PassByValue>::ParamType;`
- L125 _public typedef_ `using ConstPointerType = typename TCallTraitsParamTypeHelper<T, PassByValue>::ConstParamType;`

#### struct `uLang::TCallTraits`  
`template <typename T> struct TCallTraits : public TCallTraitsBase<T>`  
_L132-132_
- inherits: `TCallTraitsBase<T>`
- desc: TCallTraits
- L138 _public typedef_ `using ValueType = T&;`
- L139 _public typedef_ `using Reference = T&;`
- L140 _public typedef_ `using ConstReference = const T&;`
- L141 _public typedef_ `using ParamType = T&;`
- L142 _public typedef_ `using ConstPointerType = T&;`
- L150 _private typedef_ `using ArrayType = T[N];`
- L152 _public typedef_ `using ValueType = const T*;`
- L153 _public typedef_ `using Reference = ArrayType&;`
- L154 _public typedef_ `using ConstReference = const ArrayType&;`
- L155 _public typedef_ `using ParamType = const T* const;`
- L156 _public typedef_ `using ConstPointerType = const T* const;`

#### struct `uLang::TCallTraits`  
`template <typename T> struct TCallTraits<T&>`  
_L136-143_
- desc: Fix reference-to-reference problems.
- L138 _public typedef_ `using ValueType = T&;`
- L139 _public typedef_ `using Reference = T&;`
- L140 _public typedef_ `using ConstReference = const T&;`
- L141 _public typedef_ `using ParamType = T&;`
- L142 _public typedef_ `using ConstPointerType = T&;`
- L150 _private typedef_ `using ArrayType = T[N];`
- L152 _public typedef_ `using ValueType = const T*;`
- L153 _public typedef_ `using Reference = ArrayType&;`
- L154 _public typedef_ `using ConstReference = const ArrayType&;`
- L155 _public typedef_ `using ParamType = const T* const;`
- L156 _public typedef_ `using ConstPointerType = const T* const;`

#### struct `uLang::TCallTraits`  
`template <typename T, size_t N> struct TCallTraits<T [N]>`  
_L147-157_
- desc: Array types
- L138 _public typedef_ `using ValueType = T&;`
- L139 _public typedef_ `using Reference = T&;`
- L140 _public typedef_ `using ConstReference = const T&;`
- L141 _public typedef_ `using ParamType = T&;`
- L142 _public typedef_ `using ConstPointerType = T&;`
- L150 _private typedef_ `using ArrayType = T[N];`
- L152 _public typedef_ `using ValueType = const T*;`
- L153 _public typedef_ `using Reference = ArrayType&;`
- L154 _public typedef_ `using ConstReference = const ArrayType&;`
- L155 _public typedef_ `using ParamType = const T* const;`
- L156 _public typedef_ `using ConstPointerType = const T* const;`

#### struct `uLang::TCallTraits`  
`template <typename T, size_t N> struct TCallTraits<const T [N]>`  
_L161-171_
- desc: const array types
- L138 _public typedef_ `using ValueType = T&;`
- L139 _public typedef_ `using Reference = T&;`
- L140 _public typedef_ `using ConstReference = const T&;`
- L141 _public typedef_ `using ParamType = T&;`
- L142 _public typedef_ `using ConstPointerType = T&;`
- L150 _private typedef_ `using ArrayType = T[N];`
- L152 _public typedef_ `using ValueType = const T*;`
- L153 _public typedef_ `using Reference = ArrayType&;`
- L154 _public typedef_ `using ConstReference = const ArrayType&;`
- L155 _public typedef_ `using ParamType = const T* const;`
- L156 _public typedef_ `using ConstPointerType = const T* const;`

#### struct `uLang::TTypeTraitsBase`  
`template<typename T> struct TTypeTraitsBase`  
_L178-186_
- desc: Helper for array traits. Provides a common base to more easily refine a portion of the traits when specializing. Mainly used by MemoryOps.h which is used by the contiguous storage containers like TArray.
- L180 _public typedef_ `using ConstInitType = typename TCallTraits<T>::ParamType;`
- L181 _public typedef_ `using ConstPointerType = typename TCallTraits<T>::ConstPointerType;`
- L185 _public member_ `static constexpr bool IsBytewiseComparable = std::is_enum_v<T> || std::is_arithmetic_v<T> || std::is_pointer_v<T>;` — There's no good way of detecting this so we'll just assume it to be true for certain known types and expect users to customize it for their custom types.

#### struct `uLang::TTypeTraits`  
`template<typename T> struct TTypeTraits : public TTypeTraitsBase<T>`  
_L191-191_
- inherits: `TTypeTraitsBase<T>`
- desc: Traits for types.

#### struct `uLang::TContainerTraitsBase`  
`template<typename T> struct TContainerTraitsBase`  
_L196-200_
- desc: Traits for containers.
- L199 _public member_ `static constexpr bool MoveWillEmptyContainer = false;` — This should be overridden by every container that supports emptying its contents via a move operation.

#### struct `uLang::TContainerTraits`  
`template<typename T> struct TContainerTraits : public TContainerTraitsBase<T>`  
_L202-202_
- inherits: `TContainerTraitsBase<T>`

#### struct `uLang::TIsBitwiseConstructible`  
`template <typename T, typename Arg> struct TIsBitwiseConstructible`  
_L218-232_
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <typename T> struct TIsBitwiseConstructible<T, T>`  
_L235-239_
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <typename T, typename U> struct TIsBitwiseConstructible<const T, U> : TIsBitwiseConstructible<T, U>`  
_L242-245_
- inherits: `TIsBitwiseConstructible<T,U>`
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <typename T> struct TIsBitwiseConstructible<const T*, T*>`  
_L251-255_
- desc: Const pointers can be bitwise constructed from non-const pointers. This is not true for pointer conversions in general, e.g. where an offset may need to be applied in the case of multiple inheritance, but there is no way of detecting that at compile-time.
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible< uint8_t, int8_t>`  
_L259-259_
- desc: Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible< uint8_t, int8_t>`  
_L260-260_
- desc: Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible< uint8_t, int8_t>`  
_L261-261_
- desc: Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible< uint8_t, int8_t>`  
_L262-262_
- desc: Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible< int8_t, uint8_t>`  
_L263-263_
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible<uint16_t, int16_t>`  
_L264-264_
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible< int16_t, uint16_t>`  
_L265-265_
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### struct `uLang::TIsBitwiseConstructible`  
`template <> struct TIsBitwiseConstructible<uint32_t, int32_t>`  
_L266-266_
- L231 _public member_ `static constexpr bool Value = false;` — Assume no bitwise construction in general
- L238 _public member_ `static constexpr bool Value = std::is_trivially_copy_constructible_v<T>;` — Ts can always be bitwise constructed from itself if it is trivially copyable.
- L254 _public member_ `static constexpr bool Value = true;` — Constructing a const T is the same as constructing a T
- L259 _public member_ `template <> struct TIsBitwiseConstructible< uint8_t, int8_t> { static constexpr bool Value = true; };` — Unsigned types can be bitwise converted to their signed equivalents, and vice versa. (assuming two's-complement, which we are)
- L263 _public member_ `template <> struct TIsBitwiseConstructible< int8_t, uint8_t> { static constexpr bool Value = true; };`
- L264 _public member_ `template <> struct TIsBitwiseConstructible<uint16_t, int16_t> { static constexpr bool Value = true; };`
- L265 _public member_ `template <> struct TIsBitwiseConstructible< int16_t, uint16_t> { static constexpr bool Value = true; };`
- L266 _public member_ `template <> struct TIsBitwiseConstructible<uint32_t, int32_t> { static constexpr bool Value = true; };`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/CppMangling.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L11 _namespace_ `namespace CppMangling` (scope `uLang`)
- L13 _prototype_ `CUTF8String Mangle(const CUTF8StringView& StringView);` (scope `uLang::CppMangling`)
- L14 _prototype_ `CUTF8String Demangle(const CUTF8StringView& StringView);` (scope `uLang::CppMangling`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/FilePathUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L9 _namespace_ `namespace FilePathUtils` (scope `uLang`)
- L15 _prototype_ `CUTF8String NormalizePath(const CUTF8StringView& Path);` (scope `uLang::FilePathUtils`) — Replaces backslashes with slashes and make drive letters uppercase
- L20 _prototype_ `bool IsPathRelative(const CUTF8StringView& Path);` (scope `uLang::FilePathUtils`) — Determine if a path is relative (i.e. not fully qualified)
- L27 _prototype_ `bool SplitPath(const CUTF8StringView& FilePath, CUTF8StringView& OutDir, CUTF8StringView& OutFileName, bool bIncludeDirEndSlash = false);` (scope `uLang::FilePathUtils`) — Splits a path into the file name and the directory in front of it The directory will have a slash or no slash at the end as specified by bIncludeDirEndSlash If there's no slash in the path, returns false.
- L34 _function_ `template<typename FunctionType> void ForeachPartOfPath(const CUTF8StringView& Path, FunctionType&& Lambda)` (scope `uLang::FilePathUtils`) — Invoke a lambda with each part of a path from left to right Slashes at either begin or end of path, as well as double slashes, will result in an invocation with an empty part
- L50 _prototype_ `CUTF8String AppendSlash(const CUTF8StringView& Path);` (scope `uLang::FilePathUtils`) — Appends a slash to the path if there isn't one already
- L55 _prototype_ `CUTF8String GetDirectory(const CUTF8StringView& Path, bool bIncludeDirEndSlash = false);` (scope `uLang::FilePathUtils`) — Gets the containing directory of a file or directory
- L60 _prototype_ `CUTF8String GetFileName(const CUTF8StringView& Path);` (scope `uLang::FilePathUtils`) — Gets the unqualified name of a file or directory (without the containing path)
- L65 _prototype_ `void SplitFileName(const CUTF8StringView& FileName, CUTF8StringView& Stem, CUTF8StringView& Extension);` (scope `uLang::FilePathUtils`) — Splits a file name into stem (name) and extension (including the dot)
- L70 _prototype_ `CUTF8String CombinePaths(const CUTF8StringView& LhsPath, const CUTF8StringView& RhsPath);` (scope `uLang::FilePathUtils`) — Combines two paths
- L75 _prototype_ `CUTF8String ConvertRelativePathToFull(const CUTF8StringView& Path, const CUTF8StringView& BasePath);` (scope `uLang::FilePathUtils`) — Checks if a path is relative, and if so, combines it with given base path
- L80 _prototype_ `CUTF8String ConvertFullPathToRelative(const CUTF8StringView& FullPath, const CUTF8StringView& BasePath);` (scope `uLang::FilePathUtils`) — Creates a relative path by removing BasePath from the head of FullPath. Result will be empty if this is not possible.
- L85 _prototype_ `CUTF8StringView GetNameFromFileOrDir(const CUTF8StringView& FilePath);` (scope `uLang::FilePathUtils`) — Gets stem/name of given file, or if stem is empty, name of enclosing directory
- L91 _prototype_ `bool IsDescendantOfDirectory(const CUTF8StringView& ParentDirectory, const CUTF8StringView& PotentialChildDirectory);` (scope `uLang::FilePathUtils`) — Check if a file/directory is a descendant of a given directory NOTE: This fails in a number of cases, but the most obvious one is when the parent directory passed in is a symbolic link and the second argument is the actual file/directory path.

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/IdxRange.h` (Public)


#### struct `uLang::SIdxRange`  
`struct SIdxRange`  
_L15-46_
- desc: Specifies a range using both beginning and ending indexes. Often used with CUTF8StringView and SAxisRange (row and column) CUTF8StringView can convert to and from SIdxRange and SAxisRange.
- L21 _public member_ `uint32_t _Begin;` — Beginning of index range
- L22 _public member_ `uint32_t _End;` — End of index range
- L26 _public function_ `SIdxRange() : _Begin(0u), _End(0u)`
- L27 _public function_ `SIdxRange(ENoInit)` — Do nothing - use with care!
- L28 _public function_ `SIdxRange(uint32_t Length) : _Begin(0u), _End(Length)`
- L29 _public function_ `SIdxRange(uint32_t Begin, uint32_t End) : _Begin(Begin), _End(End)`
- L30 _public function_ `static SIdxRange MakeSpan(uint32_t Begin, uint32_t Length)`
- L31 _public function_ `void Reset()`
- L35 _public function_ `uint32_t GetLength() const`
- L36 _public function_ `bool IsEmpty() const`
- L37 _public function_ `bool IsOrdered() const`
- L38 _public function_ `void Set(uint32_t Begin, uint32_t End)`
- L39 _public function_ `void AdvanceToEnd()`
- L43 _public function_ `bool operator==(const SIdxRange & Other) const`
- L44 _public function_ `bool operator!=(const SIdxRange & Other) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/Named.h` (Public)


#### class `uLang::CNamed`  
`class CNamed`  
_L14-54_
- desc: Common parent class for objects with a name. Used for identifying, sorting, etc.
- L20 _public function_ `CNamed()`
- L21 _public function_ `explicit CNamed(const CSymbol& Name) : _Name(Name)`
- L22 _public function_ `CNamed(const CNamed& Source) : _Name(Source._Name)`
- L23 _public function_ `CNamed & operator=(const CNamed & Source)`
- L27 _public function_ `operator const CSymbol& () const`
- L31 _public function_ `EEquate Compare(const CSymbol& Name) const`
- L32 _public function_ `bool operator==(const CSymbol& Name) const`
- L33 _public function_ `bool operator!=(const CSymbol& Name) const`
- L34 _public function_ `bool operator<=(const CSymbol& Name) const`
- L35 _public function_ `bool operator>=(const CSymbol& Name) const`
- L36 _public function_ `bool operator<(const CSymbol& Name) const`
- L37 _public function_ `bool operator>(const CSymbol& Name) const`
- L41 _public function_ `const CSymbol& GetName() const`
- L42 _public function_ `SymbolId GetNameId() const`
- L44 _public function_ `CUTF8StringView AsNameStringView() const`
- L45 _public function_ `const char* AsNameCString() const`
- L46 _public function_ `UTF8Char AsNameFirstByte() const`
- L52 _protected member_ `CSymbol _Name;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/StringUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L12 _prototype_ `bool SplitString(const char* ToSplit, const char* Delim, CUTF8StringView& OutLeft, CUTF8StringView& OutRight);` (scope `uLang`)
- L13 _prototype_ `bool SplitString(const char* ToSplit, const UTF8Char Delim, CUTF8StringView& OutLeft, CUTF8StringView& OutRight, bool bReverse = false);` (scope `uLang`)
- L14 _prototype_ `CUTF8String ToUpper(const CUTF8StringView& Str);` (scope `uLang`)
- L24 _prototype_ `STextRange IndexRangeToTextRange(const SIdxRange& IndexRange, const CUTF8StringView& SourceText);` (scope `uLang`) — Converts an index-based range of Unicode code points (start, end) to a row/column-based range (start row/column, end row/column). @param IndexRange    The range of Unicode code points to convert. @param SourceText    The full source text that corresponds to the range about to be converted. @return              A row-column range that is equivalent to the index-based range.
- L26 _prototype_ `int32_t CountNumLeadingNewLines(const CUTF8StringView& Text);` (scope `uLang`)
- L28 _prototype_ `int32_t CountNumTrailingNewLines(const CUTF8StringView& Text);` (scope `uLang`)
- L30 _prototype_ `bool HasTrailingNewLine(const CUTF8StringView& Text);` (scope `uLang`)
- L32 _prototype_ `int32_t GetCurrentIndentationLevel(const int32_t IndentSize, const CUTF8StringView& Text);` (scope `uLang`)
- L34 _prototype_ `CUTF8String FindLongestCommonPrefix(const TArray<CUTF8String> Strings);` (scope `uLang`)

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/Symbol.h` (Public)


#### enum `uLang::(anonymous)`  
`enum`  
_L21-21_
- desc: The id of the empty string, hardcoded to a fixed value

#### class `uLang::CSymbolTable`  
`class CSymbolTable : public CSharedMix`  
_L26-94_
- inherits: `CSharedMix`
- desc: Database keeping track of symbols and their text equivalent
- L31 _public prototype_ `CSymbolTable(uint32_t NumHashBuckets = 1024, uint32_t IdChunkShift = 10);` — @param NumHashBuckets How many hash buckets are used for lookup by text (use 0 to disable text lookup) @param IdChunkShift   2^IdChunkShift pointers are stored in a chunk for lookup by id (use 0 to disable id lookup)
- L33 _public prototype_ `~CSymbolTable();`
- L36 _public prototype_ `CSymbol Get(SymbolId Id) const;` — Gets a symbol by id - id must exist
- L39 _public prototype_ `TOptional<CSymbol> Find(const CUTF8StringView& Text, bool bIsGenerated = false) const;` — Looks up a symbol by text
- L42 _public prototype_ `TOptional<CSymbol> Add(const CUTF8StringView& Text, bool bIsGenerated = false);` — Looks up a symbol by text, and if not present yet, adds it. Return empty optional if text is to long.
- L45 _public prototype_ `CSymbol AddChecked(const CUTF8StringView& Text, bool bIsGenerated = false);` — Looks up a symbol by text, and if not present yet, adds it. Asserts if text is to long.
- L49 _public prototype_ `void ReAdd(CSymbol& Symbol);` — Remaps a symbol from another symbol table to this symbol table I.e. symbol tables are merged by iterating through all symbols of one table and re-adding them to the other table
- L52 _public member_ `static constexpr uint32_t MaxSymbolLength = 1024;` — The max length of a symbol.
- L78 _private prototype_ `uint32_t GetBucketIndex(const CUTF8StringView& Text) const;`
- L79 _private prototype_ `const SEntry * AddInternal(const CUTF8StringView& Text, uint32_t BucketIndex, bool bIsGenerated);`
- L80 _private prototype_ `const SEntry * FindOrAddInternal(const CUTF8StringView& Text, bool bIsGenerated);`
- L83 _private prototype_ `CSymbolTable(const CSymbolTable&) = delete;` — No copying allowed
- L84 _private prototype_ `void operator = (const CSymbolTable&) = delete;`
- L85 _private prototype_ `void operator = (CSymbolTable&&) = delete;`
- L87 _private member_ `TArray<SEntry*> _HashBuckets;` — The heads of the lists of each string hash bucket
- L88 _private member_ `CArenaAllocator _Allocator;` — For allocating entries
- L89 _private member_ `TArray<SEntry**> _IdLookupTable;` — Array of chunks for lookup by id
- L90 _private member_ `uint32_t _IdChunkShift;` — 2^_IdLookupChunkShift pointers are stored per chunk
- L91 _private member_ `SymbolId _HighestUsedId;` — Highest id used so far in this table
- L93 _private member_ `static const SEntry _EntryNull;` — Entry representing the null symbol (= empty string)
- L137 _function_ `inline CSymbol CSymbolTable::Get(SymbolId Id) const`

#### struct `uLang::CSymbolTable::SEntry`  
`struct SEntry`  
_L59-76_
- desc: Entry in the symbol table that stores the id and string The string is stored in the memory following this data structure
- L61 _public member_ `SEntry* _HashNext;` — Next entry with the same hash
- L62 _public member_ `SymbolId _Id;` — The ID of this symbol
- L63 _public member_ `uint32_t _ByteLength : 31;` — Length of text string in bytes
- L64 _public member_ `uint32_t _bIsGenerated : 1;` — Whether the symbol is generated.
- L65 _public member_ `UTF8Char _Data[1];`
- L67 _public function_ `CUTF8StringView AsStringView() const`
- L72 _public function_ `const char* AsCString() const`

#### class `uLang::CSymbol`  
`class CSymbol`  
_L97-131_
- desc: Symbol representing a text string with an associated id
- L100 _public function_ `CSymbol() : _Entry(&CSymbolTable::_EntryNull)`
- L102 _public function_ `SymbolId GetId() const`
- L103 _public function_ `bool IsNull() const`
- L104 _public function_ `bool IsGenerated() const`
- L106 _public function_ `CUTF8String AsString() const`
- L107 _public function_ `CUTF8StringView AsStringView() const`
- L108 _public function_ `const char* AsCString() const`
- L109 _public function_ `UTF8Char FirstByte() const`
- L111 _public function_ `EEquate Compare(const CSymbol& Other) const`
- L112 _public function_ `bool operator == (const CSymbol& Other) const`
- L113 _public function_ `bool operator != (const CSymbol& Other) const`
- L114 _public function_ `bool operator <= (const CSymbol& Other) const`
- L115 _public function_ `bool operator >= (const CSymbol& Other) const`
- L116 _public function_ `bool operator < (const CSymbol& Other) const`
- L117 _public function_ `bool operator > (const CSymbol& Other) const`
- L128 _private function_ `CSymbol(const CSymbolTable::SEntry* Entry) : _Entry(Entry)`
- L130 _private member_ `const CSymbolTable::SEntry * _Entry;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ULANGCORE_API`
- L14 _namespace_ `namespace uLang`
- L18 _typedef_ `using SymbolId = uint32_t;` (scope `uLang`) — A unique id representing a symbol
- L21 _enumerator_ `enum { SymbolId_Null = 0 }; class CSymbol; class CSymbolTable : public CSharedMix { public:` (scope `uLang::__anon8496c8500103`) — The id of the empty string, hardcoded to a fixed value
- L120 _function_ `friend uint32_t GetTypeHash(CSymbol Symbol)` (scope `uLang`) — Hash function for maps, sets

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/TextRange.h` (Public)


#### struct `uLang::STextPosition`  
`struct STextPosition`  
_L19-40_
- desc: Position in a text document/string expressed as zero-based row/line and zero-based column/character offset. A position is between two characters like an ‘insert’ cursor in an editor.  The column is a byte offset into the UTF-8 encoded line. Similar to a LSP Position - https://microsoft.github.io/language-server-protocol/specifications/specification-3-14/#position Also similar to UE `FIntPoint`
- L24 _public member_ `uint32_t _Row = uint32_invalid;`
- L25 _public member_ `uint32_t _Column = uint32_invalid;`
- L29 _public function_ `void Invalidate()`
- L30 _public function_ `void Reset()`
- L31 _public function_ `bool IsValid() const`
- L32 _public function_ `bool IsInvalid() const`
- L34 _public function_ `bool operator==(const STextPosition& Other) const`
- L35 _public function_ `bool operator!=(const STextPosition& Other) const`
- L36 _public function_ `bool operator<=(const STextPosition& Other) const`
- L37 _public function_ `bool operator< (const STextPosition& Other) const`
- L38 _public function_ `bool operator>=(const STextPosition& Other) const`
- L39 _public function_ `bool operator> (const STextPosition& Other) const`

#### struct `uLang::STextRange`  
`struct STextRange`  
_L57-145_
- desc: A range in a text document/string expressed as (zero-based) begin and end row/column. A range is comparable to a selection in an editor. Therefore the end position is exclusive. Columns are byte offsets into the UTF-8 encoded line. To specify a range that contains a line including the line ending character(s), use an end position denoting the start of the next line (or) same row and the column just past the last character on the row. Often used with CUTF8StringView and SIdxRange. CUTF8StringView should do the converting to and from SIdxRange and STextRange. Similar to a LSP Range - https://microsoft.github.io/language-server-protocol/specifications/specification-3-14/#range Also similar to UE `FIntRect`
- L63 _public function_ `uint32_t BeginRow() const`
- L64 _public function_ `uint32_t BeginColumn() const`
- L65 _public function_ `uint32_t EndRow() const`
- L66 _public function_ `uint32_t EndColumn() const`
- L68 _public function_ `void SetBeginRow(uint32_t Row)`
- L69 _public function_ `void SetBeginColumn(uint32_t Col)`
- L70 _public function_ `void SetEndRow(uint32_t Row)`
- L71 _public function_ `void SetEndColumn(uint32_t Col)`
- L75 _public function_ `STextRange() : _Begin`
- L76 _public function_ `STextRange(ENoInit)` — Do nothing - use with care!
- L77 _public function_ `STextRange(uint32_t BeginRow, uint32_t BeginColumn, uint32_t EndRow, uint32_t EndColumn) : _Begin`
- L78 _public function_ `STextRange(const STextPosition& Begin, const STextPosition& End) : _Begin(Begin), _End(End)`
- L79 _public function_ `STextRange(const STextPosition& BeginAndEnd) : _Begin(BeginAndEnd), _End(BeginAndEnd)`
- L83 _public function_ `STextPosition GetBegin() const`
- L84 _public function_ `STextPosition GetEnd() const`
- L85 _public function_ `void SetBegin(const STextPosition& Begin)`
- L86 _public function_ `void SetEnd(const STextPosition& End)`
- L88 _public function_ `void Invalidate()`
- L89 _public function_ `void InvalidateEnd()`
- L90 _public function_ `void Reset()`
- L91 _public function_ `bool IsEmpty() const`
- L92 _public function_ `bool IsOrdered() const`
- L93 _public function_ `bool IsRowSingle() const`
- L94 _public function_ `bool IsRowMulti() const`
- L95 _public function_ `bool IsInvalid() const`
- L96 _public function_ `bool IsValid() const`
- L97 _public function_ `bool IsInvalidEnd() const`
- L98 _public function_ `bool IsValidEnd() const`
- L102 _public function_ `bool operator==(const STextRange & Other) const`
- L103 _public function_ `bool operator!=(const STextRange & Other) const`
- L105 _public function_ `bool Overlaps(const STextRange& Other) const` — = "there is at least one byte of overlap"
- L106 _public function_ `bool IsContainedIn(const STextRange& ContainingRange) const` — = "no character of this is outside of ContainingRange"
- L108 _public function_ `bool IsInRange(const STextPosition& Position) const`
- L109 _public function_ `bool IsInRangeInclusive(const STextPosition& Position) const`
- L114 _public function_ `STextRange operator|(const STextRange& Other) const` — Compute the union of two text ranges
- L122 _public function_ `STextRange& operator|=(const STextRange& Other)` — Make this text range the union of this and another
- L140 _private member_ `STextPosition _Begin;` — Beginning position (zero-based, inclusive)
- L143 _private member_ `STextPosition _End;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/UTF8String.h` (Public)


#### class `uLang::TUTF8String`  
`template<class AllocatorType, typename... AllocatorArgsType> class TUTF8String : AllocatorType`  
_L20-270_
- inherits: `AllocatorType`
- desc: Simple string class, used mostly for string storage Implements null termination, so can be used as a C-style string (via operator *) The AllocatorType must provide the methods void * Allocate(size_t) and void Deallocate(void *)
- L26 _public function_ `TUTF8String() : AllocatorType(DefaultInit)`
- L27 _public prototype_ `TUTF8String(const char* NullTerminatedString, AllocatorArgsType&&... AllocatorArgs);`
- L28 _public prototype_ `TUTF8String(const CUTF8StringView& StringView, AllocatorArgsType&&... AllocatorArgs);`
- L30 _public prototype_ `template<typename... FormatterArgsType> TUTF8String(AllocatorArgsType&&... AllocatorArgs, const char* NullTerminatedFormat, FormatterArgsType&&... FormatterArgs);`
- L31 _public prototype_ `TUTF8String(AllocatorArgsType&&... AllocatorArgs, const char* NullTerminatedFormat, va_list FormatterArgs);`
- L33 _public prototype_ `template<typename InitializerFunctorType>`
- L34 _public prototype_ `TUTF8String(const TUTF8String& Other);`
- L36 _public prototype_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> TUTF8String(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other, AllocatorArgsType&&... AllocatorArgs);`
- L37 _public prototype_ `TUTF8String(TUTF8String&& Other);`
- L39 _public function_ `~TUTF8String()`
- L40 _public function_ `void Reset()`
- L41 _public function_ `void Empty()`
- L42 _public function_ `UTF8Char* Resize(int32_t NewByteLen)`
- L46 _public function_ `int32_t ByteLen() const`
- L47 _public function_ `bool IsEmpty() const`
- L48 _public function_ `bool IsFilled() const`
- L49 _public function_ `const UTF8Char* AsUTF8() const`
- L50 _public function_ `const char* AsCString() const`
- L51 _public function_ `const char* operator*() const`
- L54 _public function_ `const UTF8Char& operator[](int32_t ByteIndex) const` — @return specific byte from this string
- L63 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator==(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L65 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator!=(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L67 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator<(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L69 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator<=(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L71 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator>(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L73 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator>=(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L74 _public function_ `bool operator==(const CUTF8StringView& StringView) const`
- L75 _public function_ `bool operator!=(const CUTF8StringView& StringView) const`
- L79 _public prototype_ `TUTF8String& operator=(const TUTF8String& Other);`
- L80 _public prototype_ `TUTF8String& operator=(TUTF8String&& Other);`
- L83 _public prototype_ `TUTF8String& operator+=(const CUTF8StringView& OtherStringView);` — Append
- L85 _public prototype_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> TUTF8String& operator+=(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other);`
- L86 _public prototype_ `TUTF8String& operator+=(const char* OtherNullTerminatedString);`
- L88 _public prototype_ `TUTF8String operator+(const CUTF8StringView& OtherStringView) const;`
- L90 _public prototype_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> TUTF8String operator+(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const;`
- L91 _public prototype_ `TUTF8String operator+(const char* OtherNullTerminatedString) const;`
- L95 _public function_ `operator const CUTF8StringView&() const`
- L96 _public function_ `const CUTF8StringView& ToStringView() const`
- L100 _public function_ `CUTF8StringView::UnicodeConstIterator begin() const`
- L101 _public function_ `CUTF8StringView::UnicodeConstIterator end() const`
- L105 _public function_ `TUTF8String Replace(UTF8Char Old, UTF8Char New) const`
- L116 _public function_ `TUTF8String Replace(const CUTF8StringView& Old, const CUTF8StringView& New) const`
- L184 _public prototype_ `static const TUTF8String& GetEmpty();`
- L188 _protected function_ `int32_t InputByteIdxToDirectIdx(int32_t InIdx) const`
- L189 _protected function_ `bool InputByteIdxSpan(int32_t& InOutIdx, int32_t& InOutSpan) const`
- L196 _private function_ `TUTF8String(ENoInit)` — Do nothing - friends only!
- L197 _private function_ `TUTF8String(ENoInit, const AllocatorType& Allocator) : AllocatorType(Allocator), _String(NoInit)`
- L199 _private function_ `UTF8Char* AllocateUninitialized(size_t ByteLength)`
- L208 _private function_ `UTF8Char* Reallocate(size_t ByteLength)`
- L241 _private function_ `void AllocateInitialized(const UTF8Char* String, size_t ByteLength)` — Initialize from a given char array
- L253 _private function_ `void Release()` — Let go of our data
- L258 _private function_ `AllocatorType& GetAllocator()`
- L263 _private function_ `const AllocatorType& GetAllocator() const`
- L269 _private member_ `CUTF8StringView _String;` — The text storage
- L273 _function_ `template<class AllocatorType, typename... AllocatorArgsType> const TUTF8String<AllocatorType, AllocatorArgsType...>& TUTF8String<AllocatorType, AllocatorArgsType...>::GetEmpty()`
- L294 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(const char* NullTerminatedString, AllocatorArgsType&&... AllocatorArgs) : AllocatorType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...) , _String(NoInit)`
- L302 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(const CUTF8StringView& StringView, AllocatorArgsType&&... AllocatorArgs) : AllocatorType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...) , _String(NoInit)`
- L311 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<typename... FormatterArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(AllocatorArgsType&&... AllocatorArgs, const char* NullTerminatedFormat, FormatterArgsType&&... FormatterArgs) : AllocatorType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...) , _String(NoInit)`
- L333 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(AllocatorArgsType&&... AllocatorArgs, const char* NullTerminatedFormat, va_list FormatterArgs) : AllocatorType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...) , _String(NoInit)`
- L362 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<typename InitializerFunctorType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(size_t ByteLength, InitializerFunctorType&& InitializerFunctor, AllocatorArgsType&&... AllocatorArgs) : AllocatorType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...) , _String(NoInit)`
- L376 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(const TUTF8String& Other) : AllocatorType(Other.GetAllocator()) , _String(NoInit)`
- L385 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<class OtherAllocatorType, typename... OtherAllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other, AllocatorArgsType&&... AllocatorArgs) : AllocatorType(uLang::ForwardArg<AllocatorArgsType>(AllocatorArgs)...) , _String(NoInit)`
- L393 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>::TUTF8String(TUTF8String&& Other) : AllocatorType(Other.GetAllocator()) , _String(Other._String)`
- L401 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>& TUTF8String<AllocatorType, AllocatorArgsType...>::operator=(const TUTF8String& Other)`
- L410 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>& TUTF8String<AllocatorType, AllocatorArgsType...>::operator=(TUTF8String&& Other)`
- L420 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>& TUTF8String<AllocatorType, AllocatorArgsType...>::operator+=(const CUTF8StringView& OtherStringView)`
- L436 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<class OtherAllocatorType, typename... OtherAllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>& TUTF8String<AllocatorType, AllocatorArgsType...>::operator+=(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other)`
- L442 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...>& TUTF8String<AllocatorType, AllocatorArgsType...>::operator+=(const char* OtherNullTerminatedString)`
- L449 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...> TUTF8String<AllocatorType, AllocatorArgsType...>::operator+(const CUTF8StringView& OtherStringView) const`
- L457 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<class OtherAllocatorType, typename... OtherAllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...> TUTF8String<AllocatorType, AllocatorArgsType...>::operator+(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L463 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...> TUTF8String<AllocatorType, AllocatorArgsType...>::operator+(const char* OtherNullTerminatedString) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L108 _function_ `` (scope `uLang::TUTF8String::Replace`)
- L280 _typedef_ `using CUTF8String = uLang::TUTF8String<CHeapRawAllocator>;` (scope `uLang`) — A string allocated on the heap
- L283 _typedef_ `using CUTF8StringA = uLang::TUTF8String<CInstancedRawAllocator, CAllocatorInstance*>;` (scope `uLang`) — A string allocated using a given allocator instance
- L287 _function_ `template<class AllocatorType, typename... AllocatorArgsType> uint32_t GetTypeHash(const TUTF8String<AllocatorType, AllocatorArgsType...>& String)` (scope `uLang`) — Hash function for maps, sets

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/UTF8StringBuilder.h` (Public)


#### class `uLang::TUTF8StringBuilder`  
`template<class AllocatorType, typename... AllocatorArgsType> class TUTF8StringBuilder`  
_L23-191_
- desc: String builder class Used to modify and manipulate strings
- L27 _public typedef_ `using StringType = TUTF8String<AllocatorType, AllocatorArgsType...>;`
- L31 _public function_ `TUTF8StringBuilder(uint32_t ReserveBytes = 0) : _AllocatedBytes(0)`
- L32 _public prototype_ `TUTF8StringBuilder(const char* NullTerminatedString, AllocatorArgsType&&... AllocatorArgs);`
- L33 _public prototype_ `TUTF8StringBuilder(const CUTF8StringView& StringView, AllocatorArgsType&&... AllocatorArgs);`
- L35 _public prototype_ `template<typename... FormatterArgsType> TUTF8StringBuilder(AllocatorArgsType&&... AllocatorArgs, const char* NullTerminatedFormat, FormatterArgsType&&... FormatterArgs);`
- L36 _public prototype_ `TUTF8StringBuilder(const TUTF8StringBuilder& Other);`
- L37 _public prototype_ `TUTF8StringBuilder(TUTF8StringBuilder&& Other);`
- L39 _public prototype_ `~TUTF8StringBuilder() = default;` — Memory will be released via the embedded string object
- L41 _public function_ `void Reset()` — Just reset length but hold on to memory
- L42 _public function_ `void EnsureAllocatedExtra(size_t ExtraBytes)`
- L47 _public function_ `int32_t ByteLen() const`
- L48 _public function_ `bool IsEmpty() const`
- L49 _public function_ `bool IsFilled() const`
- L52 _public function_ `const UTF8Char& operator[](int32_t ByteIndex) const` — @return specific byte from this string
- L58 _public function_ `UTF8Char LastByte() const` — @return the last byte in this string (UTF-8 agnostic) or null character if empty
- L63 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator==(const TUTF8StringBuilder<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L65 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator!=(const TUTF8StringBuilder<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L67 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator==(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L69 _public function_ `template<class OtherAllocatorType, typename... OtherAllocatorArgsType> bool operator!=(const TUTF8String<OtherAllocatorType, OtherAllocatorArgsType...>& Other) const`
- L70 _public function_ `bool operator==(const CUTF8StringView& StringView) const`
- L71 _public function_ `bool operator!=(const CUTF8StringView& StringView) const`
- L75 _public prototype_ `TUTF8StringBuilder& operator=(const TUTF8StringBuilder& Other);`
- L76 _public prototype_ `TUTF8StringBuilder& operator=(TUTF8StringBuilder&& Other);`
- L77 _public prototype_ `TUTF8StringBuilder& operator=(const CUTF8StringView& StringView);`
- L81 _public function_ `operator const CUTF8StringView&() const`
- L82 _public function_ `const CUTF8StringView& ToStringView() const`
- L83 _public function_ `const char* AsCString() const`
- L84 _public function_ `const char* operator*() const`
- L86 _public prototype_ `StringType MoveToString();` — Move string and reset the builder (most efficient)
- L87 _public function_ `StringType CopyToString() const` — Make copy of string and keep builder as-is (less efficient)
- L91 _public prototype_ `TUTF8StringBuilder& Append(UTF8Char Char);`
- L92 _public prototype_ `TUTF8StringBuilder& Append(const CUTF8StringView& String);`
- L94 _public prototype_ `template<typename... FormatterArgsType> TUTF8StringBuilder& AppendFormat(const char* NullTerminatedFormat, FormatterArgsType&&... FormatterArgs);`
- L104 _public prototype_ `UTF8Char* AppendBuffer(size_t ByteSize);` — Grows the String for serialization purposes -- the _End pointer is moved to the end of the buffer, expecting serialization to occur immediately following this call. NOTE: This inserts a terminating '\0' character preliminary into the buffer, but expects serialization to overwrite it with a '\0' of its own. @return A pointer to the appended buffer's start -- useful for subsequent serialization.
- L107 _public prototype_ `TUTF8StringBuilder& TrimEnd(UTF8Char Ch);` — Trim character from end if exists
- L110 _public prototype_ `TUTF8StringBuilder& ReplaceRange(SIdxRange ToBeReplaced, const CUTF8StringView& Replacement);` — Replace a range of bytes with the provided replacement string
- L113 _public prototype_ `TUTF8StringBuilder& ReplaceAt(int32_t Index, const UTF8Char Replacement);` — Replace a single character with the provided character
- L116 _public prototype_ `TUTF8StringBuilder& ReplaceAll(const UTF8Char Search, const UTF8Char Replacement);` — Replace all instances of a single character with the provided character
- L119 _public prototype_ `TUTF8StringBuilder& InsertAt(int32_t Index, const CUTF8StringView& StringToInsert);` — Inserts a string before the given index.
- L137 _public prototype_ `int32_t LineIndentEditor(int32_t Idx = 0, int32_t SpanCount = -1, int32_t SpaceCount = DefaultIndentEffectiveSpaceCount);` — Indents rows/lines by specified `SpaceCount` spaces from `Idx` over the span of `Count` characters using behavior similar to the MS Visual Studio editor. Works on line breaks that are in Unix style `\n` or DOS style `\r\n`. @returns: number of line breaks over the specified range @param: StartIdx - starting index to begin indentation. If negative it indicates index position from end of string - so -1 = last char, -2 = char before last, etc. @param: SpanCount - Span of characters to indent. If negative it indicates remainder of string after `Idx` - so -1 = include last, -2 = include char before last, etc. @param: SpaceCount - number of space characters to indent @notes: - Spaces inserted at the beginning of each row. - Rows with no non-space characters are not indented. - If the range ends just after a line break, the following row is not indented - at least one character on a row must be included for it to be indented - Similar to Visual Studio editor behavior.
- L141 _protected function_ `int32_t InputByteIdxToDirectIdx(int32_t InIdx) const`
- L142 _protected function_ `bool InputByteIdxSpan(int32_t& InOutIdx, int32_t& InOutSpan) const`
- L147 _private function_ `static size_t CalculateBytesToAllocate(size_t RequestedBytes)` — Compute allocation size from requested size
- L156 _private function_ `void Construct(const UTF8Char* String, size_t ByteLength, const AllocatorType& Allocator)` — Initialize from a given char array
- L172 _private function_ `void EnsureAllocated(size_t BytesNeeded)` — Ensure string builder has a given size
- L187 _private member_ `StringType _String;` — We repurpose a TUTF8String to store the string
- L190 _private member_ `uint32_t _AllocatedBytes;` — How many bytes we have actually allocated
- L204 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::TUTF8StringBuilder(const char* NullTerminatedString, AllocatorArgsType&&... AllocatorArgs) : _String(NoInit)`
- L211 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::TUTF8StringBuilder(const CUTF8StringView& StringView, AllocatorArgsType&&... AllocatorArgs) : _String(NoInit)`
- L220 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<typename... FormatterArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::TUTF8StringBuilder(AllocatorArgsType&&... AllocatorArgs, const char* NullTerminatedFormat, FormatterArgsType&&... FormatterArgs) : _String(NoInit)`
- L242 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::TUTF8StringBuilder(const TUTF8StringBuilder& Other) : _String(NoInit)`
- L249 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::TUTF8StringBuilder(TUTF8StringBuilder&& Other) : _String(ForwardArg<StringType>(Other._String)) , _AllocatedBytes(Other._AllocatedBytes)`
- L257 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8String<AllocatorType, AllocatorArgsType...> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::MoveToString()`
- L281 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::operator=(const TUTF8StringBuilder& Other)`
- L296 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::operator=(TUTF8StringBuilder&& Other)`
- L305 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::operator=(const CUTF8StringView& StringView)`
- L323 _function_ `template<class AllocatorType, typename... AllocatorArgsType> inline TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::Append(UTF8Char Char)`
- L334 _function_ `template<class AllocatorType, typename... AllocatorArgsType> inline TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::Append(const CUTF8StringView& String)`
- L352 _function_ `template<class AllocatorType, typename... AllocatorArgsType> template<typename... FormatterArgsType> inline TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::AppendFormat(const char* NullTerminatedFormat, FormatterArgsType&&... FormatterArgs)`
- L371 _function_ `template<class AllocatorType, typename... AllocatorArgsType> UTF8Char* TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::AppendBuffer(size_t ByteSize)`
- L389 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::ReplaceRange(SIdxRange ToBeReplaced, const CUTF8StringView& Replacement)`
- L405 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::ReplaceAt(int32_t Index, const UTF8Char Replacement)`
- L413 _function_ `template <class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::ReplaceAll(const UTF8Char Search, const UTF8Char Replacement)`
- L426 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::InsertAt(int32_t Index, const CUTF8StringView& StringToInsert)`
- L442 _function_ `template<class AllocatorType, typename... AllocatorArgsType> TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>& TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::TrimEnd(UTF8Char Ch)`
- L452 _function_ `template<class AllocatorType, typename... AllocatorArgsType> inline int32_t TUTF8StringBuilder<AllocatorType, AllocatorArgsType...>::LineIndentEditor(int32_t Idx, int32_t SpanCount, int32_t SpaceCount)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L14 _variable_ `static const char * DefaultIndentCString = "` (scope `uLang`) — Indent defaults
- L15 _variable_ `static const uint32_t DefaultIndentCStringByteCount = 4u;` (scope `uLang`) — Number of bytes for DefaultIndentCString
- L16 _variable_ `static const uint32_t DefaultIndentEffectiveSpaceCount = 4u;` (scope `uLang`)
- L17 _variable_ `static const CUTF8StringView DefaultIndentString = CUTF8StringView(DefaultIndentCString);` (scope `uLang`)
- L194 _typedef_ `using CUTF8StringBuilder = TUTF8StringBuilder<CHeapRawAllocator>;` (scope `uLang`) — A string allocated on the heap
- L197 _typedef_ `using CUTF8StringBuilderA = TUTF8StringBuilder<CInstancedRawAllocator, CAllocatorInstance*>;` (scope `uLang`) — A string allocated using a given allocator instance

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/UTF8StringView.h` (Public)


#### class `uLang::CUTF8StringView`  
`class CUTF8StringView`  
_L14-428_
- L19 _public member_ `const UTF8Char* _Begin;` — Points to first byte
- L20 _public member_ `const UTF8Char* _End;` — Points to the byte after the last byte
- L24 _public function_ `CUTF8StringView() : _Begin(nullptr), _End(nullptr)`
- L25 _public function_ `CUTF8StringView(ENoInit)` — Do nothing - use with care!
- L26 _public function_ `CUTF8StringView(const UTF8Char* Begin, const UTF8Char* End) : _Begin(Begin), _End(End)`
- L27 _public function_ `CUTF8StringView(const char * NullterminatedString) : _Begin((UTF8Char *)NullterminatedString), _End((UTF8Char *)NullterminatedString + ::strlen(NullterminatedString))`
- L28 _public function_ `CUTF8StringView(const char * String, size_t ByteLen) : _Begin((UTF8Char *)String), _End((UTF8Char *)String + ByteLen)`
- L30 _public function_ `void Reset()`
- L31 _public function_ `void Set(const UTF8Char* Begin, const UTF8Char* End)`
- L34 _public function_ `const UTF8Char* Data() const` — Accessors
- L35 _public function_ `int32_t ByteLen() const`
- L36 _public function_ `bool IsEmpty() const`
- L37 _public function_ `bool IsFilled() const`
- L40 _public function_ `const UTF8Char& operator[](int32_t ByteIndex) const` — @return specific byte from this string
- L47 _public function_ `UTF8Char FirstByte() const` — @return the first byte in this string (UTF-8 agnostic) or null character if empty
- L53 _public function_ `UTF8Char SecondByte() const` — @return the second byte in this string (UTF-8 agnostic) or null character if no such character
- L59 _public function_ `UTF8Char LastByte() const` — @return the last byte in this string (UTF-8 agnostic) or null character if empty
- L65 _public function_ `UTF8Char NextByte(const CUTF8StringView& Enclosing) const` — @return the first byte that follows this view (UTF-8 agnostic) or null character if past enclosing string view.
- L71 _public function_ `UTF8Char NextNextByte(const CUTF8StringView& Enclosing) const` — @return the second byte that follows this view (UTF-8 agnostic) or null character if past enclosing string view.
- L77 _public function_ `SUniCodePointLength FirstCodePoint() const` — @return the first code point in this string (decodes UTF-8)
- L82 _public function_ `bool StartsWith(const CUTF8StringView& Text) const`
- L91 _public function_ `bool EndsWith(const CUTF8StringView& Text) const`
- L105 _public function_ `int32_t Find(UTF8Char Char) const`
- L117 _public function_ `int32_t Find(const CUTF8StringView& Text) const`
- L141 _public function_ `bool Contains(UTF8Char Char) const`
- L146 _public function_ `bool Contains(const CUTF8StringView& Text) const`
- L151 _public function_ `bool ContainsCaseIndependent(const CUTF8StringView& Text) const`
- L173 _public function_ `bool operator==(const CUTF8StringView& Other) const`
- L183 _public function_ `bool operator!=(const CUTF8StringView& Other) const`
- L188 _public function_ `bool operator<(const CUTF8StringView& Other) const`
- L198 _public function_ `bool operator>(const CUTF8StringView& Other) const`
- L208 _public function_ `bool operator<=(const CUTF8StringView& Other) const`
- L213 _public function_ `bool operator>=(const CUTF8StringView& Other) const`
- L218 _public function_ `bool operator==(const char* NullTerminatedString) const`
- L228 _public function_ `bool operator!=(const char* NullterminatedString) const`
- L233 _public function_ `bool IsEqualCaseIndependent(const CUTF8StringView& Other) const`
- L246 _public function_ `UTF8Char PopFirstByte()` — @return the first byte in this string (UTF-8 agnostic), and remove it from string
- L253 _public function_ `SUniCodePointLength PopFirstCodePoint()` — @return the first code point in this string (decodes UTF-8), and remove it from string
- L263 _public function_ `CUTF8StringView SubViewBegin(int32_t ByteCount) const` — @return the leftmost given number of bytes
- L269 _public function_ `CUTF8StringView SubViewEnd(int32_t ByteCount) const` — @return the string to the right of the specified byte location, counting back from the right (end of the string)
- L275 _public function_ `CUTF8StringView SubViewTrimBegin(int32_t ByteIndex) const` — @return the string to the right of the specified location, counting forward from the left (from the beginning of the string)
- L281 _public function_ `CUTF8StringView SubViewTrimEnd(int32_t ByteCount) const` — @return the leftmost bytes from the string chopping the given number of characters from the end
- L287 _public function_ `CUTF8StringView SubView(int32_t ByteIndex, int32_t ByteCount = INT32_MAX) const` — @return the substring from ByteIndex position for ByteCount bytes
- L296 _public function_ `CUTF8StringView SubView(const SIdxRange& Range) const` — @return a sub view as specified by the range
- L303 _public function_ `CUTF8StringView SubViewEmpty(int32_t ByteIndex) const` — @return a sub view with both begin and end referring to the byte with the specified index
- L311 _public function_ `SIdxRange SubRange(const CUTF8StringView& SubView) const` — @return Create index range based on sub view of this view.
- L362 _public function_ `UnicodeConstIterator begin() const`
- L363 _public function_ `UnicodeConstIterator end() const`
- L372 _protected function_ `int32_t InputByteIdxToDirectIdx(int32_t InIdx) const` — Convert index that may be relative (negative) to the length of the string to direct index and assert if out of bounds. -1=last char, -2=second to last char, etc. @return: Converted direct index
- L392 _protected function_ `bool InputByteIdxSpan(int32_t& InOutIdx, int32_t& InOutSpan) const` — Convert index and span count that may be relative (negative) to the length of the string to direct index and span. Assert if the index is out of bounds. @param: InOutIdx - index to convert. If negative it is relative to the end of the string -1=last char, -2=second to last char, etc. @param: InOutSpan - number of characters in span. If negative it indicates remainder of string after `InOutIdx` - so -1 = include last, -2 = include char before last, etc. @return: true if there is a valid span of characters and false if the span or string is empty

#### class `uLang::CUTF8StringView::UnicodeConstIterator`  
`class UnicodeConstIterator`  
_L319-360_
- L322 _public function_ `UnicodeConstIterator(const UTF8Char* CurrentByte, size_t CurrentByteLen) : _CurrentByte(CurrentByte) , _CurrentByteLen(CurrentByteLen)`
- L329 _public function_ `UnicodeConstIterator operator++(int)`
- L336 _public function_ `UnicodeConstIterator &operator++()`
- L344 _public function_ `UniCodePoint operator* () const`
- L346 _public function_ `bool operator==(const UnicodeConstIterator& Other) const`
- L347 _public function_ `bool operator!=(const UnicodeConstIterator& Other) const`
- L348 _public function_ `const UTF8Char* CurrentByte() const`
- L352 _private function_ `void Eval()`
- L357 _private member_ `SUniCodePointLength _CurrentValue;`
- L358 _private member_ `const UTF8Char* _CurrentByte;`
- L359 _private member_ `size_t _CurrentByteLen;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L431 _function_ `inline uint32_t GetTypeHash(const CUTF8StringView& String)` (scope `uLang`) — Hash function for maps, sets

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/Unicode.h` (Public)


#### struct `uLang::SUniCodePointLength`  
`struct SUniCodePointLength`  
_L26-30_
- desc: Pair of code point and its length in bytes in UTF-8
- L28 _public member_ `UniCodePoint _CodePoint;` — :24
- L29 _public member_ `uint32_t _ByteLengthUTF8;` — :8

#### struct `uLang::SUTF8CodePoint`  
`struct SUTF8CodePoint`  
_L32-36_
- L34 _public member_ `UTF8Char Units[4];`
- L35 _public member_ `uint8_t NumUnits;` — NumUnits==0 indicates an invalid codepoint.

#### class `uLang::CUnicode`  
`class CUnicode`  
_L40-71_
- desc: Helper class providing useful unicode functionality
- L45 _public member_ `static const bool _ASCIITable_Whitespace[BYTE_RANGE];` — Tables for doing fast whitespace character lookup [Any non-ASCII character will result in false.]
- L46 _public member_ `static const bool _ASCIITable_Identifier[BYTE_RANGE];` — A-Z, a-z, 1-9, _
- L48 _public function_ `static bool IsWhitespaceASCII(const UTF8Char Ch)`
- L49 _public function_ `static bool IsDigitASCII(const UTF8Char Ch)`
- L50 _public function_ `static bool IsUpperASCII(const UTF8Char Ch)`
- L51 _public function_ `static bool IsLowerASCII(const UTF8Char Ch)`
- L52 _public function_ `static bool IsAlphaASCII(const UTF8Char Ch)`
- L53 _public function_ `static UTF8Char ToLower_ASCII(const UTF8Char Ch)`
- L54 _public function_ `static UTF8Char ToUpper_ASCII(const UTF8Char Ch)`
- L56 _public prototype_ `static SUniCodePointLength DecodeUTF8(const UTF8Char * Text, size_t TextByteLength);`
- L57 _public prototype_ `static SUTF8CodePoint EncodeUTF8(UniCodePoint CodePoint);`
- L60 _public prototype_ `static bool IsIdentifierStart(UniCodePoint CodePoint);` — uLang-specific detection of identifier code points
- L61 _public prototype_ `static bool IsIdentifierTail(UniCodePoint CodePoint);` — Identifier continuation/middle?
- L66 _private prototype_ `static SUniCodePointLength DecodeUTF8NonASCII(const UTF8Char * Text, size_t TextByteLength);`
- L68 _private prototype_ `static bool IsIdentifierStartNonASCII(UniCodePoint CodePoint);`
- L69 _private prototype_ `static bool IsIdentifierTailNonASCII(UniCodePoint CodePoint);`
- L79 _function_ `inline SUniCodePointLength CUnicode::DecodeUTF8(const UTF8Char * Text, size_t TextByteLength)` — This inline function optimizes for the most common case that the code point is ASCII Only for non-ASCII code points an actual function call is made
- L97 _function_ `inline bool CUnicode::IsIdentifierStart(UniCodePoint CodePoint)` — This inline function optimizes for the most common case that the code point is ASCII Only for non-ASCII code points an actual function call is made
- L112 _function_ `inline bool CUnicode::IsIdentifierTail(UniCodePoint CodePoint)` — This inline function optimizes for the most common case that the code point is ASCII Only for non-ASCII code points an actual function call is made

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ULANGCORE_API`
- L9 _namespace_ `namespace uLang`
- L16 _variable_ `inline constexpr size_t ASCII_RANGE = 128;` (scope `uLang`) — ASCII Character range is from 0 to 127 so any byte less than this is a valid ASCII character.
- L17 _variable_ `inline constexpr size_t BYTE_RANGE = 256;` (scope `uLang`)
- L20 _typedef_ `using UTF8Char = uint8_t;` (scope `uLang`) — UTF-8 octet
- L23 _typedef_ `using UniCodePoint = uint32_t;` (scope `uLang`) — UTF-32 character / code point

### `Source/Runtime/Solaris/uLangCore/Public/uLang/Common/Text/VerseStringEscaping.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L11 _namespace_ `namespace VerseStringEscaping` (scope `uLang`)
- L13 _prototype_ `CUTF8String EscapeString(const CUTF8StringView& StringView);` (scope `uLang::VerseStringEscaping`)
