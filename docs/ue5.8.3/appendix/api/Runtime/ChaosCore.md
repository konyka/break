# Runtime / ChaosCore

- module root: `Source/Runtime/Experimental/ChaosCore`
- headers: 39; symbols: 1299
- symbol kinds: class=51, enum=1, enumerator=2, function=874, macro=11, member=111, namespace=37, prototype=106, struct=29, typedef=71, union=3, variable=3
- PublicDependencyModuleNames: Core, IntelISPC

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/AABB.h` (Public)


#### struct `Chaos::TAABBSpecializeSamplingHelper`  
`template<typename T, int d> struct TAABBSpecializeSamplingHelper`  
_L14-21_
- L16 _public function_ `static FORCEINLINE TArray<TVector<T, d>> ComputeLocalSamplePoints(const class TAABB<T, d>& AABB)`
- L729 _public function_ `static FORCEINLINE TArray<TVector<T, 2>> ComputeSamplePoints(const TAABB<T, 2>& AABB)`
- L758 _public function_ `static FORCEINLINE TArray<TVector<T, 3>> ComputeSamplePoints(const TAABB<T, 3>& AABB)`

#### struct `Chaos::FAABBEdge`  
`struct FAABBEdge`  
_L23-27_
- L25 _public member_ `int8 VertexIndex0;`
- L26 _public member_ `int8 VertexIndex1;`

#### struct `Chaos::FAABBFace`  
`struct FAABBFace`  
_L29-33_
- L31 _public member_ `int8 VertexIndex[4];`
- L32 _public member_ `int8 EdgeIndex[4];`

#### class `Chaos::TAABB`  
`template<class T, int d> class TAABB`  
_L36-717_
- L39 _public typedef_ `using TType = T;`
- L40 _public member_ `static constexpr int D = d;`
- L42 _public function_ `FORCEINLINE TAABB() : MMin(TVector<T, d>(TNumericLimits<T>::Max())) , MMax(TVector<T, d>(-TNumericLimits<T>::Max()))`
- L48 _public function_ `FORCEINLINE TAABB(const TVector<T, d>& Min, const TVector<T, d>&Max) : MMin(Min) , MMax(Max)`
- L54 _public function_ `FORCEINLINE TAABB(const TAABB<T, d>& Other) : MMin(Other.MMin) , MMax(Other.MMax)`
- L61 _public function_ `template<typename OtherType> explicit TAABB(const TAABB<OtherType, d>& Other) : MMin(TVector<T, d>(Other.Min())) , MMax(TVector<T, d>(Other.Max()))`
- L67 _public function_ `FORCEINLINE TAABB(TAABB<T, d>&& Other) : MMin(MoveTemp(Other.MMin)) , MMax(MoveTemp(Other.MMax))`
- L73 _public function_ `FORCEINLINE TAABB<T, d>& operator=(const TAABB<T, d>& Other)`
- L80 _public function_ `FORCEINLINE TAABB<T, d>& operator=(TAABB<T, d>&& Other)`
- L90 _public function_ `FORCEINLINE TArray<TVector<T, d>> ComputeLocalSamplePoints() const` — Returns sample points centered about the origin.
- L99 _public function_ `FORCEINLINE TArray<TVector<T, d>> ComputeSamplePoints() const` — Returns sample points at the current location of the box.
- L104 _public prototype_ `TAABB<T, d> TransformedAABB(const FTransform&) const;`
- L105 _public prototype_ `TAABB<T, d> TransformedAABB(const Chaos::TRigidTransform<FReal, 3>&) const;`
- L106 _public prototype_ `TAABB<T, d> TransformedAABB(const FMatrix&) const;`
- L107 _public prototype_ `TAABB<T, d> TransformedAABB(const Chaos::PMatrix<FReal, 4, 4>&) const;`
- L109 _public prototype_ `TAABB<T, d> InverseTransformedAABB(const Chaos::FRigidTransform3&) const;`
- L112 _public function_ `template <typename TReal> FORCEINLINE bool Intersects(const TAABB<TReal, d>& Other) const`
- L122 _public function_ `FORCEINLINE TAABB<T, d> GetIntersection(const TAABB<T, d>& Other) const`
- L127 _public function_ `FORCEINLINE bool Contains(const TVector<T, d>& Point) const`
- L139 _public function_ `FORCEINLINE bool Contains(const TVector<T, d>& Point, const T Tolerance) const`
- L151 _public function_ `FORCEINLINE bool Contains(const TAABB<T, d>& Other) const`
- L156 _public function_ `FORCEINLINE const TAABB<T, d>& BoundingBox() const`
- L158 _public function_ `FORCEINLINE uint16 GetMaterialIndex(uint32 HintIndex) const`
- L160 _public function_ `FORCEINLINE FReal SignedDistance(const TVector<FReal, d>& x) const`
- L166 _public function_ `FORCEINLINE FReal PhiWithNormal(const TVector<FReal, d>& X, TVector<FReal, d>& Normal) const`
- L215 _public prototype_ `bool Raycast(const TVector<FReal, d>& StartPoint, const TVector<FReal, d>& Dir, const FReal Length, const FReal Thickness, FReal& OutTime, TVector<FReal, d>& OutPosition, TVector<FReal, d>& OutNormal, int32& OutFaceIndex) const;`
- L217 _public function_ `FORCEINLINE bool RaycastFast(const TVector<FReal, d>& StartPoint, const TVector<FReal, d>& Dir, const TVector<FReal, d>& InvDir, const bool* bParallel, const FReal Length, FReal& OutEntryTime, FReal& OutExitTime) const`
- L222 _public function_ `FORCEINLINE bool RaycastFast(const TVector<FReal, d>& StartPoint, const TVector<FReal, d>& Dir, const TVector<FReal, d>& InvDir, const bool* bParallel, const FReal Length, const FReal InvLength, FReal& OutEntryTime, FReal& OutExitTime) const`
- L227 _public function_ `FORCEINLINE bool RaycastFast(const TVector<FReal, d>& StartPoint, const TVector<FReal, d>& Dir, const TVector<FReal, d>& InvDir, const bool* bParallel, const FReal Length, FReal& OutTime, TVector<FReal, d>& OutPosition) const`
- L240 _public function_ `FORCEINLINE bool RaycastFast(const TVector<FReal, d>& StartPoint, const TVector<FReal, d>& Dir, const TVector<FReal, d>& InvDir, const bool* bParallel, const FReal Length, const FReal InvLength, FReal& OutTime, TVector<FReal, d>& OutPosition) const`
- L245 _public prototype_ `TVector<T, d> FindClosestPoint(const TVector<T, d>& StartPoint, const T Thickness = (T)0) const;`
- L247 _public prototype_ `Pair<TVector<FReal, d>, bool> FindClosestIntersectionImp(const TVector<FReal, d>& StartPoint, const TVector<FReal, d>& EndPoint, const FReal Thickness) const;`
- L249 _public function_ `FORCEINLINE TVector<T, d> FindGeometryOpposingNormal(const TVector<T, d>& DenormDir, int32 FaceIndex, const TVector<T, d>& OriginalNormal) const`
- L283 _public function_ `FORCEINLINE_DEBUGGABLE TVector<T, d> Support(const TVector<T, d>& Direction, const T Thickness, int32& OutVertexIndex) const`
- L322 _public function_ `FORCEINLINE_DEBUGGABLE FVec3 SupportCore(const FVec3& Direction, const FReal InMargin, FReal* OutSupportDelta, int32& OutVertexIndex) const` — Support vertex in the specified direction, assuming each face has been moved inwards by InMargin
- L352 _public function_ `FORCEINLINE_DEBUGGABLE VectorRegister4Float SupportCoreSimd(const VectorRegister4Float& Direction, const FReal InMargin) const`
- L361 _public function_ `FORCEINLINE_DEBUGGABLE TVector<T, d> SupportCoreScaled(const TVector<T, d>& Direction, const T InMargin, const TVector<T, d>& Scale, T* OutSupportDelta, int32& OutVertexIndex) const`
- L393 _public function_ `FORCEINLINE void GrowToInclude(const TVector<T, d>& V)`
- L399 _public function_ `FORCEINLINE void GrowToInclude(const TAABB<T, d>& Other)`
- L405 _public function_ `FORCEINLINE void ShrinkToInclude(const TAABB<T, d>& Other)`
- L411 _public function_ `FORCEINLINE TAABB<T, d>& Thicken(const T Thickness)`
- L419 _public function_ `FORCEINLINE TAABB<T, d>& ThickenSymmetrically(const TVector<T, d>& Thickness)` — Grows the box by this vector symmetrically - Changed name because previous Thicken had different semantics which caused several bugs
- L427 _public function_ `FORCEINLINE TAABB<T, d>& ShrinkSymmetrically(const TVector<T, d>& Thickness)`
- L436 _public function_ `FORCEINLINE TAABB<T, d>& GrowByVector(const TVector<T, d>& V)` — Grow along a vector (as if swept by the vector's direction and magnitude)
- L444 _public function_ `FORCEINLINE void MoveByVector(TVector<T, d> InVector)` — Move the bounding box along a vector
- L450 _public function_ `FORCEINLINE TVector<T, d> Center() const`
- L451 _public function_ `FORCEINLINE TVector<T, d> GetCenter() const`
- L452 _public function_ `FORCEINLINE TVector<T, d> GetCenterOfMass() const`
- L453 _public function_ `FORCEINLINE TVector<T, d> Extents() const`
- L475 _public function_ `FORCEINLINE TVector<T, d> GetVertex(const int32 Index) const` — Get a vector one of the eight corners of the box. Each of the first three bits in an index are used to pick an axis value from either the min or max vector of the AABB. 0 = min, 1 = max. This algorithm produces the following index scheme, where the vertex at 0 is the "min" vertex and 7 is the "max": 6---------7 /|        /| / |       / | 4---------5  | |  |      |  | |  2------|--3 | /       | / |/        |/ 0---------1
- L492 _public function_ `FORCEINLINE int32 GetIndex(const FIntVector& AxisSelector) const` — Given a point on a unit cube expressed as an IntVector of 0s and 1s, get the vertex index of that point. 0 represents a negative axis and 1 represents a positive axis. All other values are invalid, but we do not check this as it would add overhead to support functions. This is used by the support functions and must invert the index logic in GetVertex().
- L518 _public function_ `FORCEINLINE FAABBEdge GetEdge(const int32 Index) const` — Get an array of two indices into the vertex list for one of the twelve edges of the box. Edges are ordered by increasing vertex indices. This algorithm produces the following index scheme, where the bottom left vertex is the "min" vertex and the top right is "max": 6-----11------7 /|            /| 9 |          10 | /  6          /  7 4------8------5   | |   |         |   | |   2------5--|---3 2  /          4  / | 1           | 3 |/            |/ 0------0------1
- L532 _public function_ `FORCEINLINE FAABBFace GetFace(const int32 Index) const`
- L548 _public function_ `FORCEINLINE int LargestAxis() const`
- L565 _public function_ `FORCEINLINE TAABB<T, d>& ScaleWithNegative(const TVector<T, d>& InScale)`
- L575 _public function_ `FORCEINLINE TAABB<T, d>& Scale(const TVector<T, d>& InScale)` — Scale the AABB relative to the origin IMPORTANT : this does not support negative scale
- L586 _public function_ `FORCEINLINE TAABB<T, d>& LocalScale(const TVector<T, d>& InScale)` — Scale the AABB relative to its center IMPORTANT : this does not support negative scale
- L595 _public function_ `FORCEINLINE const TVector<T, d>& Min() const`
- L596 _public function_ `FORCEINLINE const TVector<T, d>& Max() const`
- L599 _public function_ `FORCEINLINE T OriginRadius() const` — The radius of the sphere centered on the AABB origin (not the AABB center) which would encompass this AABB
- L605 _public function_ `FORCEINLINE T CenterRadius() const`
- L610 _public function_ `FORCEINLINE T GetArea() const`
- L611 _public function_ `FORCEINLINE static T GetArea(const TVector<T, d>& Dim)`
- L613 _public function_ `FORCEINLINE T GetVolume() const`
- L614 _public function_ `FORCEINLINE static T GetVolume(const TVector<T, 3>& Dim)`
- L616 _public function_ `FORCEINLINE T GetMargin() const`
- L617 _public function_ `FORCEINLINE T GetRadius() const`
- L618 _public function_ `FORCEINLINE FRealSingle GetMarginf() const`
- L619 _public function_ `FORCEINLINE FRealSingle GetRadiusf() const`
- L623 _public function_ `FORCEINLINE static TAABB<T, d> EmptyAABB()` — A bounding box that will fail all overlap tests. NOTE: this bounds cannot be transformed (all transform return EmptyAABB)
- L627 _public function_ `FORCEINLINE static TAABB<T, d> FullAABB()` — A bounding box that overlaps all space. NOTE: this bounds cannot be transformed (all transforms return FullAABB)
- L630 _public function_ `FORCEINLINE static TAABB<T, d> ZeroAABB()` — A single-point bounds at the origin
- L636 _public function_ `FORCEINLINE bool IsFull() const` — If this AABB covering all of space (all overlap tests will succeed) NOTE: This just checks if Max.X is Real::Max. The assumption is that max numeric values are only used when explicitly set in EmptyAABB() and FullAABB().
- L644 _public function_ `FORCEINLINE bool IsEmpty() const` — If this AABB empty (all overlap tests will fail) NOTE: This just checks if Min.X is Real::Max. The assumption is that max numeric values are only used when explicitly set in EmptyAABB() and FullAABB().
- L650 _public function_ `FORCEINLINE_DEBUGGABLE bool IsValid() const` — AABB is valid if it doesn't contain nan and it's non empty (min <= max)
- L656 _public function_ `FORCEINLINE void Clear()` — Shrink this AABB to being empty
- L666 _public function_ `FORCEINLINE void Serialize(FArchive &Ar)`
- L671 _public function_ `FORCEINLINE uint32 GetTypeHash() const`
- L676 _public function_ `FString ToString() const`
- L681 _public function_ `FORCEINLINE PMatrix<FReal, d, d> GetInertiaTensor(const FReal Mass) const`
- L682 _public function_ `FORCEINLINE static PMatrix<FReal, 3, 3> GetInertiaTensor(const FReal Mass, const TVector<FReal, 3>& Dim)`
- L692 _public function_ `FORCEINLINE static TRotation<FReal, d> GetRotationOfMass()`
- L697 _public function_ `FORCEINLINE constexpr bool IsConvex() const`
- L705 _public function_ `template<typename... Points> static TAABB<T, d> FromPoints(const TVector<T, d>& P0, const Points&... InPoints)` — Given a set of points, wrap an AABB around them @param P0 The first of the points to wrap @param InPoints Parameter pack of all subsequent points
- L716 _private member_ `TVector<T, d> MMin, MMax;`
- L716 _private member_ `TVector<T, d> MMin, MMax;`

#### struct `Chaos::TAABBSpecializeSamplingHelper`  
`template<typename T> struct TAABBSpecializeSamplingHelper<T, 2>`  
_L727-753_
- L16 _public function_ `static FORCEINLINE TArray<TVector<T, d>> ComputeLocalSamplePoints(const class TAABB<T, d>& AABB)`
- L729 _public function_ `static FORCEINLINE TArray<TVector<T, 2>> ComputeSamplePoints(const TAABB<T, 2>& AABB)`
- L758 _public function_ `static FORCEINLINE TArray<TVector<T, 3>> ComputeSamplePoints(const TAABB<T, 3>& AABB)`

#### struct `Chaos::TAABBSpecializeSamplingHelper`  
`template<typename T> struct TAABBSpecializeSamplingHelper<T, 3>`  
_L756-813_
- L16 _public function_ `static FORCEINLINE TArray<TVector<T, d>> ComputeLocalSamplePoints(const class TAABB<T, d>& AABB)`
- L729 _public function_ `static FORCEINLINE TArray<TVector<T, 2>> ComputeSamplePoints(const TAABB<T, 2>& AABB)`
- L758 _public function_ `static FORCEINLINE TArray<TVector<T, 3>> ComputeSamplePoints(const TAABB<T, 3>& AABB)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L720 _function_ `template<class T, int d> FORCEINLINE FArchive& operator<<(FArchive& Ar, TAABB<T, d>& AABB)` (scope `Chaos`)
- L815 _typedef_ `using FAABB3 = TAABB<FReal, 3>;` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Array.h` (Public)


#### class `TArray`  
`template<class T> class TArray : public std::vector<T>`  
_L12-51_
- inherits: `std::vector<T>`
- L15 _public function_ `TArray() : std::vector<T>()`
- L17 _public function_ `TArray(TArray<T>&& Other) : std::vector<T>(std::move(Other))`
- L19 _public function_ `TArray(const TArray<T>& Other) : std::vector<T>(Other)`
- L21 _public function_ `TArray(std::initializer_list<T> l) : std::vector<T>(l)`
- L23 _public function_ `void operator=(TArray<T>&& Other)`
- L27 _public function_ `void SetNum(const int32 Size)`
- L31 _public function_ `int32 Num() const`
- L35 _public function_ `void Add(const T& Elem)`
- L39 _public function_ `void Sort()`

#### struct `std::hash`  
`template<> struct hash<TArray<int32>>`  
_L56-65_
- L58 _public function_ `std::size_t operator()(const TArray<int32>& Array) const`

#### Free symbols / members of external scopes

- L44 _function_ `friend uint32 GetTypeHash(const TArray<int32>& Array)`
- L53 _namespace_ `namespace std`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ArrayCollection.h` (Public)


#### class `Chaos::TArrayCollection`  
`class TArrayCollection`  
_L10-220_
- L13 _public function_ `TArrayCollection() : MSize(0)`
- L15 _public prototype_ `TArrayCollection(const TArrayCollection& Other) = delete;`
- L16 _public prototype_ `TArrayCollection(TArrayCollection&& Other) = delete;`
- L17 _public function_ `virtual ~TArrayCollection()`
- L26 _public function_ `void ShrinkArrays(const float MaxSlackFraction, const int32 MinSlack)`
- L37 _public function_ `int32 AddArray(TArrayCollectionArrayBase* Array)`
- L53 _public function_ `void RemoveArray(TArrayCollectionArrayBase* Array)`
- L62 _public function_ `void RemoveAt(int32 Index, int32 Count)`
- L67 _public function_ `uint32 Size() const`
- L70 _public function_ `uint64 ComputeColumnSize() const`
- L85 _protected function_ `void AddElementsHelper(const int32 Num)`
- L94 _protected function_ `void ResizeHelper(const int32 Num)`
- L107 _protected function_ `void RemoveAtHelper(const int32 Index, const int32 Count)`
- L120 _protected function_ `void RemoveAtSwapHelper(const int32 Index)`
- L133 _protected function_ `void MoveToOtherArrayCollection(const int32 Index, TArrayCollection& Other)`
- L149 _protected function_ `void MoveToOtherArrayCollection(const TArrayView<int32>& Indices, TArrayCollection& Other)` — Move collection data from one array to another one
- L216 _private member_ `TArray<TArrayCollectionArrayBase*> MArrays;`
- L219 _protected member_ `uint32 MSize;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L182 _function_ `` (scope `Chaos::TArrayCollection::MoveToOtherArrayCollection`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ArrayCollectionArray.h` (Public)


#### class `Chaos::TArrayCollectionArray`  
`template<class T> class TArrayCollectionArray : public TArrayCollectionArrayBase, public TArray<T>`  
_L77-212_
- inherits: `TArrayCollectionArrayBase,TArray<T>`
- L87 _public member_ `constexpr static EAllowShrinking AllowShrinkOnRemove = EAllowShrinking::No;`
- L91 _public function_ `TArrayCollectionArray() : TArray<T>()`
- L93 _public prototype_ `TArrayCollectionArray(const TArrayCollectionArray<T>& Other) = delete;`
- L94 _public function_ `explicit TArrayCollectionArray(TArrayCollectionArray<T>&& Other) : TArray<T>(MoveTemp(Other))`
- L96 _public function_ `TArrayCollectionArray& operator=(TArrayCollectionArray<T>&& Other)`
- L102 _public function_ `TArrayCollectionArray(TArray<T>&& Other) : TArray<T>(MoveTemp(Other))`
- L107 _public prototype_ `virtual ~TArrayCollectionArray() = default;`
- L109 _public function_ `void Fill(const T& Value)`
- L117 _public function_ `TArrayCollectionArray<T> Clone()`
- L125 _public function_ `void ApplyShrinkPolicy(const float MaxSlackFraction, const int32 MinSlack) override` — If we have more slack space than MaxSlackFraction x Num(), run the default Shrink policy
- L142 _public function_ `void Resize(const int Num) override`
- L147 _public function_ `FORCEINLINE void RemoveAt(const int Idx, const int Count) override`
- L152 _public function_ `FORCEINLINE void RemoveAtSwap(const int Idx) override`
- L158 _public function_ `FORCEINLINE void RemoveAtSwap(const TArrayView<int32>& Indices) override` — Remove a list of elements from the array
- L172 _public function_ `FORCEINLINE void Shrink() override` — Shrink the array size once the removal has been done.
- L178 _public function_ `FORCEINLINE void MoveToOtherArray(const int Idx, TArrayCollectionArrayBase& Other)` — Move only one element from a collection to another one
- L187 _public function_ `FORCEINLINE void MoveToOtherArray(const TArrayView<int32>& Indices, TArrayCollectionArrayBase& Other, const bool bRemoveElements)` — Move a list of elements from a collection to another one
- L208 _public function_ `FORCEINLINE uint64 SizeOfElem() const override`

#### struct `TIsContiguousContainer`  
`template<class T> struct TIsContiguousContainer<Chaos::TArrayCollectionArray<T>>`  
_L216-219_
- L218 _public member_ `static constexpr bool Value = TIsContiguousContainer<TArrayView<T>>::Value;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L19 _function_ `template<typename RemoveIndexFunc> FORCEINLINE void RemoveAtSwapLambda(const int32 ArraySize, const TArrayView<int32>& Indices, const RemoveIndexFunc& RemoveFunc)` (scope `Chaos`) — Remove at swap function working on an unsorted array of indices to remove. Sorting the indices in place would be an option but the complexity being O(Nlog(N)), it is probably too slow to be used for a lot of indices to remove. This algorithm requires allocating a mapping buffer to keep track of where the moved elements are and that the RemoveFunc is not modifying the original memory order
- L161 _function_ `` (scope `Chaos::TArrayCollectionArray::RemoveAtSwap`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ArrayCollectionArrayBase.h` (Public)


#### class `Chaos::TArrayCollectionArrayBase`  
`class TArrayCollectionArrayBase`  
_L9-21_
- L12 _public prototype_ `virtual void ApplyShrinkPolicy(const float MaxSlackFraction, const int32 MinSlack) = 0;`
- L13 _public prototype_ `virtual void Resize(const int Num) = 0;`
- L14 _public prototype_ `virtual void RemoveAt(const int Idx, const int Count) = 0;`
- L15 _public prototype_ `virtual void RemoveAtSwap(const int Idx) = 0;`
- L16 _public prototype_ `virtual void RemoveAtSwap(const TArrayView<int32>& Indices) = 0;`
- L17 _public prototype_ `virtual uint64 SizeOfElem() const = 0;`
- L18 _public prototype_ `virtual void MoveToOtherArray(const int Idx, TArrayCollectionArrayBase& Other) = 0;`
- L19 _public prototype_ `virtual void MoveToOtherArray(const TArrayView<int32>& Indices, TArrayCollectionArrayBase& Other, const bool bRemoveElements) = 0;`
- L20 _public prototype_ `virtual void Shrink() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ArrayFaceND.h` (Public)


#### class `Chaos::TArrayFaceND`  
`template<class T, int d> class TArrayFaceND`  
_L13-38_
- L15 _private function_ `TArrayFaceND(const TUniformGrid<FReal, d>& Grid)`
- L24 _private function_ `TArrayFaceND(const TVec3<int32>& Counts)`
- L32 _private prototype_ `TArrayFaceND(const TArrayFaceND<T, d>& Other) = delete;`
- L33 _private function_ `TArrayFaceND(TArrayFaceND<T, d>&& Other) : MArray(MoveTemp(Other.MArray))`
- L37 _private member_ `TArray<TArrayND<T, d>, TFixedAllocator<d>> MArray;`
- L44 _public function_ `TArrayFaceND(const TUniformGrid<FReal, 3>& Grid)`
- L59 _public prototype_ `TArrayFaceND(const TArrayFaceND<T, 3>& Other) = delete;`
- L60 _public function_ `TArrayFaceND(TArrayFaceND<T, 3>&& Other) : MArray(MoveTemp(Other.MArray))`
- L62 _public function_ `TArrayFaceND<T, 3> Copy()`
- L66 _public function_ `T& operator()(const Pair<int32, TVec3<int32>>& Index)`
- L67 _public function_ `const T& operator()(const Pair<int32, TVec3<int32>>& Index) const`
- L68 _public function_ `T& operator()(const int32 Axis, const int32& x, const int32& y, const int32& z)`
- L69 _public function_ `const T& operator()(const int32 Axis, const int32& x, const int32& y, const int32& z) const`
- L70 _public function_ `void Fill(const T& Scalar)`
- L76 _public function_ `const TArrayND<T, 3>& GetComponent(const int32 Axis) const`
- L77 _public function_ `TArrayND<T, 3>& GetComponent(const int32 Axis)`
- L80 _private function_ `TArrayFaceND(const TArray<TArrayND<T, 3>, TFixedAllocator<3>>& Array)`
- L87 _private member_ `TArray<TArrayND<T, 3>, TFixedAllocator<3>> MArray;`

#### class `Chaos::TArrayFaceND`  
`template<class T> class TArrayFaceND<T, 3>`  
_L41-88_
- L15 _private function_ `TArrayFaceND(const TUniformGrid<FReal, d>& Grid)`
- L24 _private function_ `TArrayFaceND(const TVec3<int32>& Counts)`
- L32 _private prototype_ `TArrayFaceND(const TArrayFaceND<T, d>& Other) = delete;`
- L33 _private function_ `TArrayFaceND(TArrayFaceND<T, d>&& Other) : MArray(MoveTemp(Other.MArray))`
- L37 _private member_ `TArray<TArrayND<T, d>, TFixedAllocator<d>> MArray;`
- L44 _public function_ `TArrayFaceND(const TUniformGrid<FReal, 3>& Grid)`
- L59 _public prototype_ `TArrayFaceND(const TArrayFaceND<T, 3>& Other) = delete;`
- L60 _public function_ `TArrayFaceND(TArrayFaceND<T, 3>&& Other) : MArray(MoveTemp(Other.MArray))`
- L62 _public function_ `TArrayFaceND<T, 3> Copy()`
- L66 _public function_ `T& operator()(const Pair<int32, TVec3<int32>>& Index)`
- L67 _public function_ `const T& operator()(const Pair<int32, TVec3<int32>>& Index) const`
- L68 _public function_ `T& operator()(const int32 Axis, const int32& x, const int32& y, const int32& z)`
- L69 _public function_ `const T& operator()(const int32 Axis, const int32& x, const int32& y, const int32& z) const`
- L70 _public function_ `void Fill(const T& Scalar)`
- L76 _public function_ `const TArrayND<T, 3>& GetComponent(const int32 Axis) const`
- L77 _public function_ `TArrayND<T, 3>& GetComponent(const int32 Axis)`
- L80 _private function_ `TArrayFaceND(const TArray<TArrayND<T, 3>, TFixedAllocator<3>>& Array)`
- L87 _private member_ `TArray<TArrayND<T, 3>, TFixedAllocator<3>> MArray;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ArrayND.h` (Public)


#### class `Chaos::TArrayNDBase`  
`template<class T_DERIVED, class T, int d> class TArrayNDBase`  
_L91-176_
- L95 _public function_ `FORCEINLINE TArrayNDBase()`
- L97 _public function_ `FORCEINLINE TArrayNDBase(const TVector<int32, d>& Counts, const TArray<T>& Array) : MCounts(Counts), MArray(Array)`
- L99 _public prototype_ `FORCEINLINE TArrayNDBase(const TArrayNDBase<T_DERIVED, T, d>& Other) = delete;`
- L100 _public function_ `FORCEINLINE TArrayNDBase(TArrayNDBase<T_DERIVED, T, d>&& Other) : MCounts(Other.MCounts), MArray(MoveTemp(Other.MArray))`
- L103 _public function_ `FORCEINLINE TArrayNDBase(std::istream& Stream) : MCounts(Stream)`
- L109 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L115 _public function_ `void Serialize(FArchive& Ar)`
- L130 _public function_ `void Serialize(FChaosArchive& Ar)`
- L136 _public function_ `FORCEINLINE TArrayNDBase<T_DERIVED, T, d>& operator=(const TArrayNDBase<T_DERIVED, T, d>& Other)`
- L143 _public function_ `FORCEINLINE TArrayNDBase<T_DERIVED, T, d>& operator=(TArrayNDBase<T_DERIVED, T, d>&& Other)`
- L149 _public function_ `FORCEINLINE T_DERIVED Copy() const`
- L150 _public function_ `FORCEINLINE void Copy(const TArrayNDBase<T_DERIVED, T, d>& Source)`
- L151 _public function_ `FORCEINLINE void Fill(const T& Value)`
- L158 _public function_ `FORCEINLINE const T& operator[](const int32 i) const`
- L159 _public function_ `FORCEINLINE T& operator[](const int32 i)`
- L161 _public function_ `FORCEINLINE int32 Num() const`
- L162 _public function_ `FORCEINLINE TVector<int32, d> Counts() const`
- L164 _public function_ `FORCEINLINE void Reset()`
- L170 _public function_ `FORCEINLINE T* GetData()`
- L171 _public function_ `FORCEINLINE const T* GetData() const`
- L174 _protected member_ `TVector<int32, d> MCounts;`
- L175 _protected member_ `TArray<T> MArray;`

#### class `Chaos::TArrayND`  
`template<class T, int d> class TArrayND : public TArrayNDBase<TArrayND<T, d>, T, d>`  
_L193-231_
- inherits: `TArrayNDBase<TArrayND<T,d>,T,d>`
- L195 _private typedef_ `typedef TArrayNDBase<TArrayND<T, d>, T, d> Base;`
- L200 _public function_ `FORCEINLINE TArrayND(const TVector<int32, d>& Counts)`
- L201 _public function_ `FORCEINLINE TArrayND(const TVector<int32, d>& Counts, const TArray<T>& Array) : Base(Counts, Array)`
- L203 _public prototype_ `FORCEINLINE TArrayND(const TArrayND<T, d>& Other) = delete;`
- L204 _public function_ `FORCEINLINE TArrayND(TArrayND<T, d>&& Other) : Base(MoveTemp(Other))`
- L207 _public function_ `FORCEINLINE TArrayND(std::istream& Stream) : Base(Stream)`
- L210 _public function_ `FORCEINLINE TArrayND<T, d>& operator=(const TArrayND<T, d>& Other)`
- L215 _public function_ `FORCEINLINE TArrayND<T, d>& operator=(TArrayND<T, d>&& Other)`
- L220 _public function_ `FORCEINLINE T& operator()(const TVector<int32, d>& Index)`
- L236 _private typedef_ `typedef TArrayNDBase<TArrayND<T, 3>, T, 3> Base;`
- L242 _public function_ `FORCEINLINE TArrayND()`
- L247 _public function_ `template<typename U> FORCEINLINE TArrayND(const TUniformGrid<U, 3>& Grid, bool NodeValues = false)`
- L251 _public function_ `FORCEINLINE TArrayND(const TVec3<int32>& Counts)`
- L255 _public function_ `FORCEINLINE TArrayND(const TVec3<int32>& Counts, const TArray<T>& Array) : Base(Counts, Array)`
- L257 _public prototype_ `FORCEINLINE TArrayND(const TArrayND<T, 3>& Other) = delete;`
- L258 _public function_ `FORCEINLINE TArrayND(TArrayND<T, 3>&& Other) : Base(MoveTemp(Other))`
- L264 _public function_ `FORCEINLINE TArrayND<T, 3>& operator=(const TArrayND<T, 3>& Other)`
- L269 _public function_ `FORCEINLINE TArrayND<T, 3>& operator=(TArrayND<T, 3>&& Other)`
- L274 _public function_ `FORCEINLINE T& operator()(const TVec3<int32>& Index)`
- L275 _public function_ `FORCEINLINE const T& operator()(const TVec3<int32>& Index) const`
- L276 _public function_ `FORCEINLINE T& operator()(const int32& x, const int32& y, const int32& z)`
- L280 _public function_ `FORCEINLINE const T& operator()(const int32& x, const int32& y, const int32& z) const`
- L285 _public function_ `FORCEINLINE void SetCounts(const TVector<int32, 3>& Counts)`
- L292 _public function_ `template<typename U> FORCEINLINE void SetCounts(const TUniformGrid<U, 3>& Grid, bool NodeValues = false)`
- L304 _private typedef_ `typedef bool T;`
- L305 _private typedef_ `typedef TArrayNDBase<TArrayND<T, 3>, char, 3> Base;`
- L311 _public function_ `FORCEINLINE TArrayND(const TUniformGrid<float, 3>& grid)`
- L316 _public function_ `FORCEINLINE TArrayND(const Vector<int32, 3>& Counts)`
- L321 _public function_ `FORCEINLINE TArrayND(const Vector<int32, 3>& Counts, const TArray<char>& Array) : Base(Counts, Array)`
- L324 _public function_ `FORCEINLINE TArrayND(TArrayND<T, 3>&& Other) : Base(std::move(Other))`
- L326 _public function_ `FORCEINLINE char& operator()(const Vector<int32, 3>& Index)`
- L327 _public function_ `FORCEINLINE const T& operator()(const Vector<int32, 3>& Index) const`
- L328 _public function_ `FORCEINLINE char& operator()(const int32& x, const int32& y, const int32& z)`

#### class `Chaos::TArrayND`  
`template<class T> class TArrayND<T, 3> : public TArrayNDBase<TArrayND<T, 3>, T, 3>`  
_L234-298_
- inherits: `TArrayNDBase<TArrayND<T,3>,T,3>`
- L195 _private typedef_ `typedef TArrayNDBase<TArrayND<T, d>, T, d> Base;`
- L200 _public function_ `FORCEINLINE TArrayND(const TVector<int32, d>& Counts)`
- L201 _public function_ `FORCEINLINE TArrayND(const TVector<int32, d>& Counts, const TArray<T>& Array) : Base(Counts, Array)`
- L203 _public prototype_ `FORCEINLINE TArrayND(const TArrayND<T, d>& Other) = delete;`
- L204 _public function_ `FORCEINLINE TArrayND(TArrayND<T, d>&& Other) : Base(MoveTemp(Other))`
- L207 _public function_ `FORCEINLINE TArrayND(std::istream& Stream) : Base(Stream)`
- L210 _public function_ `FORCEINLINE TArrayND<T, d>& operator=(const TArrayND<T, d>& Other)`
- L215 _public function_ `FORCEINLINE TArrayND<T, d>& operator=(TArrayND<T, d>&& Other)`
- L220 _public function_ `FORCEINLINE T& operator()(const TVector<int32, d>& Index)`
- L236 _private typedef_ `typedef TArrayNDBase<TArrayND<T, 3>, T, 3> Base;`
- L242 _public function_ `FORCEINLINE TArrayND()`
- L247 _public function_ `template<typename U> FORCEINLINE TArrayND(const TUniformGrid<U, 3>& Grid, bool NodeValues = false)`
- L251 _public function_ `FORCEINLINE TArrayND(const TVec3<int32>& Counts)`
- L255 _public function_ `FORCEINLINE TArrayND(const TVec3<int32>& Counts, const TArray<T>& Array) : Base(Counts, Array)`
- L257 _public prototype_ `FORCEINLINE TArrayND(const TArrayND<T, 3>& Other) = delete;`
- L258 _public function_ `FORCEINLINE TArrayND(TArrayND<T, 3>&& Other) : Base(MoveTemp(Other))`
- L264 _public function_ `FORCEINLINE TArrayND<T, 3>& operator=(const TArrayND<T, 3>& Other)`
- L269 _public function_ `FORCEINLINE TArrayND<T, 3>& operator=(TArrayND<T, 3>&& Other)`
- L274 _public function_ `FORCEINLINE T& operator()(const TVec3<int32>& Index)`
- L275 _public function_ `FORCEINLINE const T& operator()(const TVec3<int32>& Index) const`
- L276 _public function_ `FORCEINLINE T& operator()(const int32& x, const int32& y, const int32& z)`
- L280 _public function_ `FORCEINLINE const T& operator()(const int32& x, const int32& y, const int32& z) const`
- L285 _public function_ `FORCEINLINE void SetCounts(const TVector<int32, 3>& Counts)`
- L292 _public function_ `template<typename U> FORCEINLINE void SetCounts(const TUniformGrid<U, 3>& Grid, bool NodeValues = false)`
- L304 _private typedef_ `typedef bool T;`
- L305 _private typedef_ `typedef TArrayNDBase<TArrayND<T, 3>, char, 3> Base;`
- L311 _public function_ `FORCEINLINE TArrayND(const TUniformGrid<float, 3>& grid)`
- L316 _public function_ `FORCEINLINE TArrayND(const Vector<int32, 3>& Counts)`
- L321 _public function_ `FORCEINLINE TArrayND(const Vector<int32, 3>& Counts, const TArray<char>& Array) : Base(Counts, Array)`
- L324 _public function_ `FORCEINLINE TArrayND(TArrayND<T, 3>&& Other) : Base(std::move(Other))`
- L326 _public function_ `FORCEINLINE char& operator()(const Vector<int32, 3>& Index)`
- L327 _public function_ `FORCEINLINE const T& operator()(const Vector<int32, 3>& Index) const`
- L328 _public function_ `FORCEINLINE char& operator()(const int32& x, const int32& y, const int32& z)`

#### class `Chaos::TArrayND`  
`template<> class TArrayND<bool, 3> : public TArrayNDBase<TArrayND<bool, 3>, char, 3>`  
_L302-336_
- inherits: `TArrayNDBase<TArrayND<bool,3>,char,3>`
- L195 _private typedef_ `typedef TArrayNDBase<TArrayND<T, d>, T, d> Base;`
- L200 _public function_ `FORCEINLINE TArrayND(const TVector<int32, d>& Counts)`
- L201 _public function_ `FORCEINLINE TArrayND(const TVector<int32, d>& Counts, const TArray<T>& Array) : Base(Counts, Array)`
- L203 _public prototype_ `FORCEINLINE TArrayND(const TArrayND<T, d>& Other) = delete;`
- L204 _public function_ `FORCEINLINE TArrayND(TArrayND<T, d>&& Other) : Base(MoveTemp(Other))`
- L207 _public function_ `FORCEINLINE TArrayND(std::istream& Stream) : Base(Stream)`
- L210 _public function_ `FORCEINLINE TArrayND<T, d>& operator=(const TArrayND<T, d>& Other)`
- L215 _public function_ `FORCEINLINE TArrayND<T, d>& operator=(TArrayND<T, d>&& Other)`
- L220 _public function_ `FORCEINLINE T& operator()(const TVector<int32, d>& Index)`
- L236 _private typedef_ `typedef TArrayNDBase<TArrayND<T, 3>, T, 3> Base;`
- L242 _public function_ `FORCEINLINE TArrayND()`
- L247 _public function_ `template<typename U> FORCEINLINE TArrayND(const TUniformGrid<U, 3>& Grid, bool NodeValues = false)`
- L251 _public function_ `FORCEINLINE TArrayND(const TVec3<int32>& Counts)`
- L255 _public function_ `FORCEINLINE TArrayND(const TVec3<int32>& Counts, const TArray<T>& Array) : Base(Counts, Array)`
- L257 _public prototype_ `FORCEINLINE TArrayND(const TArrayND<T, 3>& Other) = delete;`
- L258 _public function_ `FORCEINLINE TArrayND(TArrayND<T, 3>&& Other) : Base(MoveTemp(Other))`
- L264 _public function_ `FORCEINLINE TArrayND<T, 3>& operator=(const TArrayND<T, 3>& Other)`
- L269 _public function_ `FORCEINLINE TArrayND<T, 3>& operator=(TArrayND<T, 3>&& Other)`
- L274 _public function_ `FORCEINLINE T& operator()(const TVec3<int32>& Index)`
- L275 _public function_ `FORCEINLINE const T& operator()(const TVec3<int32>& Index) const`
- L276 _public function_ `FORCEINLINE T& operator()(const int32& x, const int32& y, const int32& z)`
- L280 _public function_ `FORCEINLINE const T& operator()(const int32& x, const int32& y, const int32& z) const`
- L285 _public function_ `FORCEINLINE void SetCounts(const TVector<int32, 3>& Counts)`
- L292 _public function_ `template<typename U> FORCEINLINE void SetCounts(const TUniformGrid<U, 3>& Grid, bool NodeValues = false)`
- L304 _private typedef_ `typedef bool T;`
- L305 _private typedef_ `typedef TArrayNDBase<TArrayND<T, 3>, char, 3> Base;`
- L311 _public function_ `FORCEINLINE TArrayND(const TUniformGrid<float, 3>& grid)`
- L316 _public function_ `FORCEINLINE TArrayND(const Vector<int32, 3>& Counts)`
- L321 _public function_ `FORCEINLINE TArrayND(const Vector<int32, 3>& Counts, const TArray<char>& Array) : Base(Counts, Array)`
- L324 _public function_ `FORCEINLINE TArrayND(TArrayND<T, 3>&& Other) : Base(std::move(Other))`
- L326 _public function_ `FORCEINLINE char& operator()(const Vector<int32, 3>& Index)`
- L327 _public function_ `FORCEINLINE const T& operator()(const Vector<int32, 3>& Index) const`
- L328 _public function_ `FORCEINLINE char& operator()(const int32& x, const int32& y, const int32& z)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L17 _function_ `template <typename T> void TryBulkSerializeArrayNDBase(FArchive& Ar, TArray<T>& Array)` (scope `Chaos`)
- L22 _function_ `inline void TryBulkSerializeArrayNDBase(FArchive& Ar, TArray<float>& Array)` (scope `Chaos`)
- L27 _function_ `inline void TryBulkSerializeArrayNDBase(FArchive& Ar, TArray<TVec3<FRealSingle>>& Array)` (scope `Chaos`)
- L32 _function_ `inline float ConvertDoubleToFloat(double DoubleValue)` (scope `Chaos`)
- L37 _function_ `inline TVec3<float> ConvertDoubleToFloat(TVec3<double> DoubleValue)` (scope `Chaos`)
- L42 _function_ `inline double ConvertFloatToDouble(float FloatValue)` (scope `Chaos`)
- L47 _function_ `inline TVec3<double> ConvertFloatToDouble(TVec3<float> FloatValue)` (scope `Chaos`)
- L54 _function_ `template<typename DOUBLE_T, typename FLOAT_T> inline void TryBulkSerializeArrayNDBaseForDoubles(FArchive& Ar, TArray<DOUBLE_T>& DoubleTypedArray)` (scope `Chaos`) — LWC_TODO : Perf pessimization : this is sub-optimal but will do until we sort the serialization out
- L79 _function_ `inline void TryBulkSerializeArrayNDBase(FArchive& Ar, TArray<double>& Array)` (scope `Chaos`) — LWC_TODO : Perf pessimization : this is sub-optimal but will do until we sort the serialization out
- L85 _function_ `inline void TryBulkSerializeArrayNDBase(FArchive& Ar, TArray<TVec3<FRealDouble>>& Array)` (scope `Chaos`) — LWC_TODO : Perf pessimization : this is sub-optimal but will do until we sort the serialization out
- L179 _function_ `template <typename Derived, typename T, int d> FArchive& operator<<(FArchive& Ar, TArrayNDBase<Derived, T,d>& ValueIn)` (scope `Chaos`)
- L186 _function_ `template <typename Derived, typename T, int d> FArchive& operator<<(FChaosArchive& Ar, TArrayNDBase<Derived, T, d>& ValueIn)` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ChaosCoreLogUtil.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L11 _prototype_ `FString ToString(const FRotation3& V);` (scope `Chaos`)
- L12 _prototype_ `FString ToString(const FRotation3f& V);` (scope `Chaos`)
- L13 _prototype_ `FString ToString(const FVec3& V);` (scope `Chaos`)
- L14 _prototype_ `FString ToString(const FVec3f& V);` (scope `Chaos`)
- L15 _prototype_ `FString ToString(const TBitArray<>& BitArray);` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Core.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L16 _typedef_ `using FVec2 = TVector<FReal, 2>;` (scope `Chaos`)
- L17 _typedef_ `using FVec3 = TVector<FReal, 3>;` (scope `Chaos`)
- L18 _typedef_ `using FVec4 = TVector<FReal, 4>;` (scope `Chaos`)
- L19 _typedef_ `using FRotation3 = TRotation<FReal, 3>;` (scope `Chaos`)
- L20 _typedef_ `using FMatrix33 = PMatrix<FReal, 3, 3>;` (scope `Chaos`)
- L21 _typedef_ `using FMatrix44 = PMatrix<FReal, 4, 4>;` (scope `Chaos`)
- L22 _typedef_ `using FRigidTransform3 = TRigidTransform<FReal, 3>;` (scope `Chaos`)
- L24 _typedef_ `using FAABB3 = TAABB<FReal, 3>;` (scope `Chaos`)
- L26 _typedef_ `using FVec2f = TVector<FRealSingle, 2>;` (scope `Chaos`)
- L27 _typedef_ `using FVec3f = TVector<FRealSingle, 3>;` (scope `Chaos`)
- L28 _typedef_ `using FRotation3f = TRotation<FRealSingle, 3>;` (scope `Chaos`)
- L29 _typedef_ `using FRigidTransform3f = TRigidTransform<FRealSingle, 3>;` (scope `Chaos`)
- L30 _typedef_ `using FTransformPair = TVector<FRigidTransform3, 2>;` (scope `Chaos`)
- L32 _typedef_ `using FAABB3f = TAABB<FRealSingle, 3>;` (scope `Chaos`)
- L35 _typedef_ `using FRigidTransformRealSingle3 = TRigidTransform<FRealSingle, 3>;` (scope `Chaos`) — @todo(chaos): deprecate this and use FRigidTransform3f
- L38 _typedef_ `template <typename T> using TVec2 = TVector<T, 2>;` (scope `Chaos`)
- L41 _typedef_ `template <typename T> using TVec3 = TVector<T, 3>;` (scope `Chaos`)
- L44 _typedef_ `template <typename T> using TVec4 = TVector<T, 4>;` (scope `Chaos`)
- L47 _typedef_ `template<typename T> using TRotation3 = TRotation<T, 3>;` (scope `Chaos`)
- L50 _typedef_ `template<typename T> using TMatrix33 = PMatrix<T, 3, 3>;` (scope `Chaos`)
- L55 _variable_ `inline const TCHAR* const ChaosVersionGUID = TEXT("5E0` (scope `Chaos`) — NOTE: if you get a merge conflict on the GUID, you must replace it with a new GUID - do not accept the source or target or you will likely get DDC version conflicts resulting in crashes during load. Core version string for Chaos data. Any DDC builder dependent on Chaos for serialization should depend on this version
- L57 _function_ `inline FString GetChaosVersionStringInner()` (scope `Chaos`)
- L62 _macro_ `#define ChaosVersionString \`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/CoreCapsule.h` (Public)


#### class `Chaos::FCoreCapsule`  
`class FCoreCapsule`  
_L13-44_
- L16 _public prototype_ `FCoreCapsule() = default;`
- L17 _public prototype_ `FCoreCapsule(const FCoreCapsule&) = default;`
- L18 _public prototype_ `FCoreCapsule(FCoreCapsule&&) = default;`
- L19 _public prototype_ `FCoreCapsule(const TSegment<FRealSingle>& InSegment, const FRealSingle InRadius);`
- L20 _public prototype_ `FCoreCapsule(const FVec3f& X1, const FVec3f& X2, const FRealSingle InRadius);`
- L22 _public prototype_ `FCoreCapsule& operator=(const FCoreCapsule&) = default;`
- L23 _public prototype_ `FCoreCapsule& operator=(FCoreCapsule&&) = default;`
- L25 _public prototype_ `FRealSingle GetRadius() const;`
- L26 _public prototype_ `void SetRadius(FRealSingle InRadius);`
- L28 _public prototype_ `const FVec3f GetX1() const;`
- L29 _public prototype_ `const FVec3f GetX2() const;`
- L30 _public prototype_ `const TSegment<FRealSingle>& GetSegment() const;`
- L32 _public prototype_ `FRealSingle GetHeight() const;`
- L33 _public prototype_ `const FVec3f GetAxis() const;`
- L34 _public prototype_ `FVec3f GetCenter() const;`
- L36 _public prototype_ `const FAABB3 BoundingBox() const;`
- L38 _public prototype_ `bool Raycast(const FVec3& StartPoint, const FVec3& Dir, const FReal Length, const FReal Thickness, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal) const;`
- L42 _private member_ `TSegment<FRealSingle> MSegment;`
- L43 _private member_ `FRealSingle Radius = 0.0f;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/CorePlane.h` (Public)


#### class `Chaos::TCorePlane`  
`template <typename T, int d = 3> class TCorePlane`  
_L11-243_
- L16 _public function_ `static TCorePlane<T> MakeScaledSafe(const TCorePlane<T>& Plane, const TVec3<T>& Scale)` — Scale the plane and assume that any of the scale components could be zero
- L72 _public function_ `template <typename U> static FORCEINLINE TCorePlane<T> MakeScaledUnsafe(const TCorePlane<U>& Plane, const TVec3<T>& Scale, const TVec3<T>& InvScale)` — Scale the plane and assume that none of the scale components are zero
- L92 _public function_ `template <typename U> static FORCEINLINE void MakeScaledUnsafe(const TVec3<U>& PlaneN, const TVec3<U>& PlaneX, const TVec3<T>& Scale, const TVec3<T>& InvScale, TVec3<T>& OutN, TVec3<T>& OutX)`
- L114 _public function_ `template <typename U> static FORCEINLINE TCorePlane<T> MakeFrom(const TCorePlane<U>& Plane)`
- L120 _public prototype_ `TCorePlane() = default;`
- L121 _public function_ `TCorePlane(const TVec3<T>& InX, const TVec3<T>& InNormal) : MX(InX) , MNormal(InNormal)`
- L132 _public function_ `template <typename U> U SignedDistance(const TVec3<U>& x) const` — Phi is positive on the side of the normal, and negative otherwise.
- L140 _public function_ `FReal PhiWithNormal(const FVec3& x, FVec3& Normal) const` — Phi is positive on the side of the normal, and negative otherwise.
- L146 _public function_ `FVec3 FindClosestPoint(const FVec3& x, const FReal Thickness = (FReal)0) const`
- L152 _public function_ `bool Raycast(const FVec3& StartPoint, const FVec3& Dir, const FReal Length, const FReal Thickness, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal, int32& OutFaceIndex) const`
- L199 _public function_ `Pair<FVec3, bool> FindClosestIntersection(const FVec3& StartPoint, const FVec3& EndPoint, const FReal Thickness) const`
- L225 _public function_ `const TVec3<T>& X() const`
- L226 _public function_ `const TVec3<T>& Normal() const`
- L227 _public function_ `const TVec3<T>& Normal(const TVec3<T>&) const`
- L229 _public function_ `FORCEINLINE void Serialize(FArchive& Ar)`
- L234 _public function_ `uint32 GetTypeHash() const`
- L241 _private member_ `TVec3<T> MX;`
- L242 _private member_ `TVec3<T> MNormal;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L246 _function_ `template <typename T> FArchive& operator<<(FArchive& Ar, TCorePlane<T>& PlaneConcrete)` (scope `Chaos`)
- L253 _typedef_ `template <typename T, int d = 3> using TPlaneConcrete = TCorePlane<T, d>;` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/CoreSegment.h` (Public)


#### class `Chaos::TCoreSegment`  
`template<class T> class TCoreSegment`  
_L9-87_
- L12 _public function_ `TCoreSegment()`
- L13 _public function_ `TCoreSegment(const TVec3<T>& X1, const TVec3<T>& X2) : MPoint(X1) , MAxis(X2 - X1) , MLength(MAxis.SafeNormalize())`
- L18 _public function_ `TCoreSegment(const TVec3<T>& X1, const TVec3<T>& Axis, const T Length) : MPoint(X1) , MAxis(Axis) , MLength(Length)`
- L24 _public function_ `FORCEINLINE bool IsConvex() const`
- L26 _public function_ `FORCEINLINE const TVec3<T> GetCenter() const`
- L28 _public function_ `FORCEINLINE const TVec3<T>& GetX1() const`
- L30 _public function_ `FORCEINLINE TVec3<T> GetX2() const`
- L32 _public function_ `FORCEINLINE const TVec3<T>& GetAxis() const`
- L34 _public function_ `FORCEINLINE T GetLength() const`
- L36 _public function_ `TVec3<T> Support(const TVec3<T>& Direction, const T Thickness, int32& VertexIndex) const`
- L53 _public function_ `FORCEINLINE_DEBUGGABLE TVec3<T> SupportCore(const TVec3<T>& Direction, int32& VertexIndex) const`
- L62 _public function_ `FORCEINLINE void Serialize(FArchive &Ar)`
- L71 _public function_ `FString ToString() const`
- L76 _public function_ `FORCEINLINE TAABB<T, 3> BoundingBox() const`
- L84 _private member_ `TVec3<T> MPoint;`
- L85 _private member_ `TVec3<T> MAxis;`
- L86 _private member_ `T MLength;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`
- L90 _typedef_ `template<class T> using TSegment = TCoreSegment<T>;` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/CoreSphere.h` (Public)


#### class `Chaos::TCoreSphere`  
`template<class T, int d> class TCoreSphere`  
_L10-53_
- L13 _public prototype_ `TCoreSphere() = default;`
- L14 _public prototype_ `TCoreSphere(const TCoreSphere&) = default;`
- L15 _public prototype_ `TCoreSphere(TCoreSphere&&) = default;`
- L16 _public function_ `TCoreSphere(const TVector<T, d>& InCenter, const T InRadius) : Center(InCenter) , Radius(FRealSingle(InRadius))`
- L22 _public prototype_ `TCoreSphere& operator=(const TCoreSphere&) = default;`
- L23 _public prototype_ `TCoreSphere& operator=(TCoreSphere&&) = default;`
- L25 _public function_ `FRealSingle GetRadius() const`
- L30 _public function_ `void SetRadius(const FRealSingle InRadius)`
- L35 _public function_ `const FVec3f& GetCenter() const`
- L40 _public function_ `void SetCenter(const FVec3f& InCenter)`
- L45 _public function_ `bool Raycast(const TVector<T, d>& StartPoint, const TVector<T, d>& Dir, const T Length, const T Thickness, T& OutTime, TVector<T, d>& OutPosition, TVector<T, d>& OutNormal) const`
- L51 _private member_ `FVec3f Center;`
- L52 _private member_ `FRealSingle Radius;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L55 _typedef_ `using FCoreSphere = TCoreSphere<FReal, 3>;` (scope `Chaos`)
- L56 _typedef_ `using FCoreSpheref = TCoreSphere<FRealSingle, 3>;` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/HandleArray.h` (Public)


#### class `Chaos::THandleData`  
`template<uint32 IndexWidth, uint32 GenerationWidth> class THandleData`  
_L21-88_
- L27 _public function_ `THandleData() : Index(0) , Generation(0)`
- L34 _public function_ `THandleData(uint32 InIndex, uint32 InGeneration) : Index(InIndex) , Generation(InGeneration)`
- L42 _public function_ `THandleData(uint32 FullHandle) : Index(FullHandle >> GenerationWidth) , Generation(FullHandle)` — Mainly for serialization of the handle container
- L49 _public function_ `bool IsValid() const`
- L55 _public function_ `uint32 AsUint() const`
- L61 _public function_ `uint32 GetIndex() const`
- L66 _public function_ `void FromUint(uint32 InUint)`
- L86 _protected member_ `uint32 Index : IndexWidth;`
- L87 _protected member_ `uint32 Generation : GenerationWidth;`

#### class `Chaos::THandle`  
`template<typename ElementType, uint32 IndexWidth, uint32 GenerationWidth> class THandle : public THandleData<IndexWidth, GenerationWidth>`  
_L91-115_
- inherits: `THandleData<IndexWidth,GenerationWidth>`
- L98 _public prototype_ `THandle() = default;`
- L99 _public function_ `THandle(uint32 InIndex, uint32 InGeneration) : THandleData<IndexWidth, GenerationWidth>(InIndex, InGeneration)`

#### class `Chaos::TConstHandle`  
`template<typename ElementType, uint32 IndexWidth, uint32 GenerationWidth> class TConstHandle : public THandleData<IndexWidth, GenerationWidth>`  
_L118-147_
- inherits: `THandleData<IndexWidth,GenerationWidth>`
- L124 _public prototype_ `TConstHandle() = default;`
- L125 _public function_ `TConstHandle(uint32 InIndex, uint32 InGeneration) : THandleData<IndexWidth, GenerationWidth>(InIndex, InGeneration)`
- L131 _public function_ `TConstHandle(const THandle<ElementType, IndexWidth, GenerationWidth>& InNonConstHandle) : THandleData<IndexWidth, GenerationWidth>(InNonConstHandle.Index, InNonConstHandle.Generation)`

#### class `Chaos::THandleArray`  
`template<typename ElementType, uint32 IndexWidth = 24, uint32 GenerationWidth = 8> class THandleArray`  
_L150-594_
- L154 _public typedef_ `using FHandle = THandle<ElementType, IndexWidth, GenerationWidth>;`
- L155 _public typedef_ `using FConstHandle = TConstHandle<ElementType, IndexWidth, GenerationWidth>;`
- L157 _public member_ `static constexpr uint32 ElementAlign = alignof(ElementType);`
- L158 _public member_ `static constexpr SIZE_T ElementSize = sizeof(ElementType);`
- L159 _public member_ `static constexpr uint32 ElementGrowth = 4;`
- L161 _public member_ `static constexpr uint32 InvalidFreeIndex = TNumericLimits<uint32>::Max() >> GenerationWidth;`
- L163 _public function_ `THandleArray(const THandleArray<ElementType, IndexWidth, GenerationWidth>& Other) : THandleArray(0)`
- L169 _public function_ `THandleArray(THandleArray<ElementType, IndexWidth, GenerationWidth>&& Other) : THandleArray(0)`
- L175 _public function_ `THandleArray& operator =(const THandleArray<ElementType, IndexWidth, GenerationWidth>& Other)`
- L181 _public function_ `THandleArray& operator =(THandleArray<ElementType, IndexWidth, GenerationWidth>&& Other)`
- L187 _public function_ `THandleArray() : THandleArray(0)`
- L191 _public function_ `explicit THandleArray(int32 InitialNum) : FreeList(InvalidFreeIndex) , Data(nullptr) , NumData(0) , Capacity(0) , NumActive(0)`
- L215 _public function_ `~THandleArray()`
- L220 _public function_ `ElementType* Get(FHandle InHandle) const`
- L240 _public function_ `const ElementType* Get(FConstHandle InHandle) const`
- L260 _public function_ `FHandle GetHandle(uint32 InIndex) const`
- L271 _public function_ `FConstHandle GetConstHandle(uint32 InIndex) const`
- L277 _public function_ `template<typename... ConstructionArgs> FHandle Create(ConstructionArgs&&... InConstructionArgs)`
- L311 _public function_ `void Destroy(FHandle InHandle)`
- L353 _public function_ `uint32 Num() const`
- L358 _public function_ `uint32 GetCapacity() const`
- L363 _public function_ `uint32 GetNumActive() const`
- L368 _public function_ `uint32 GetNumFree() const`
- L456 _public typedef_ `using TRangedForIterator = TIterator<false>;`
- L457 _public typedef_ `using TRangedForConstIterator = TIterator<true>;`
- L459 _public function_ `TRangedForIterator begin()`
- L464 _public function_ `TRangedForConstIterator begin() const`
- L469 _public function_ `TRangedForIterator end()`
- L474 _public function_ `TRangedForConstIterator end() const`
- L481 _private function_ `void DestroyItems()`
- L505 _private function_ `void CopyFrom(const THandleArray& Other)`
- L531 _private function_ `void MoveFrom(THandleArray& Other)`
- L572 _private function_ `friend FArchive& operator << (FArchive& Ar, FHandleEntry& InHandleEntry)`
- L587 _private member_ `uint32 FreeList;`
- L588 _private member_ `TArray<FHandleEntry> HandleEntries;`
- L589 _private member_ `TBitArray<> Validity;`
- L590 _private member_ `ElementType* Data;`
- L591 _private member_ `int32 NumData;`
- L592 _private member_ `int32 Capacity;`
- L593 _private member_ `int32 NumActive;`

#### struct `Chaos::THandleArray::TIterator`  
`template<bool bConst> struct TIterator`  
_L399-454_
- L401 _public typedef_ `typedef std::conditional_t<bConst, const THandleArray, THandleArray> ArrayType;`
- L402 _public typedef_ `typedef std::conditional_t<bConst, const ElementType, ElementType> ItElementType;`
- L404 _public function_ `explicit TIterator(ArrayType& InArray, int32 InIndex) : Array(InArray) , It(InArray.Validity, InIndex)`
- L410 _public function_ `FORCEINLINE TIterator& operator++()`
- L417 _public function_ `[[nodiscard]] FORCEINLINE bool operator==(const TIterator& Rhs) const`
- L422 _public function_ `[[nodiscard]] FORCEINLINE bool operator!=(const TIterator& Rhs) const`
- L427 _public function_ `FConstHandle GetConstHandle() const`
- L433 _public function_ `FHandle GetHandle() const`
- L439 _public function_ `[[nodiscard]] FORCEINLINE ItElementType& operator*() const`
- L446 _public function_ `[[nodiscard]] FORCEINLINE ItElementType* operator->() const`
- L452 _public member_ `ArrayType& Array;`
- L453 _public member_ `TConstSetBitIterator<> It;`

#### class `Chaos::THandleArray::FHandleEntry`  
`class FHandleEntry`  
_L558-585_
- L562 _public function_ `FHandleEntry() : NextFree(InvalidFreeIndex) , Generation(1)`
- L569 _public member_ `uint32 NextFree : IndexWidth;`
- L570 _public member_ `uint32 Generation : GenerationWidth;`

#### class `Chaos::THandleHeap`  
`template<typename ElementType, uint32 IndexWidth = 24, uint32 GenerationWidth = 8> class THandleHeap`  
_L597-880_
- L603 _public typedef_ `using FHandle = THandle<ElementType, IndexWidth, GenerationWidth>;`
- L604 _public typedef_ `using FConstHandle = TConstHandle < ElementType, IndexWidth, GenerationWidth>;`
- L606 _public member_ `static constexpr uint32 InvalidFreeIndex = TNumericLimits<uint32>::Max() >> GenerationWidth;`
- L608 _public function_ `explicit THandleHeap(int32 ReserveNum) : FreeList(InvalidFreeIndex) , NumActive(0)`
- L615 _public function_ `THandleHeap(const THandleHeap<ElementType, IndexWidth, GenerationWidth>& Other) : THandleHeap(0)`
- L621 _public function_ `THandleHeap(THandleHeap<ElementType, IndexWidth, GenerationWidth>&& Other)`
- L626 _public function_ `THandleHeap& operator =(const THandleHeap<ElementType, IndexWidth, GenerationWidth>& Other)`
- L632 _public function_ `THandleHeap& operator =(THandleHeap<ElementType, IndexWidth, GenerationWidth>&& Other)`
- L638 _public function_ `THandleHeap() : THandleHeap(0)`
- L642 _public function_ `~THandleHeap()`
- L647 _public function_ `ElementType* Get(FHandle InHandle)`
- L653 _public function_ `const ElementType* Get(FConstHandle InHandle) const`
- L659 _public function_ `FHandle GetHandle(uint32 InIndex)`
- L670 _public function_ `FConstHandle GetConstHandle(uint32 InIndex)`
- L676 _public function_ `template<typename... ConstructionArgs> FHandle Create(ConstructionArgs... Args)`
- L702 _public function_ `void Destroy(FHandle InHandle)`
- L748 _public function_ `int32 Num() const`
- L753 _public function_ `int32 GetNumActive() const`
- L758 _public function_ `void Empty(bool bShrink = true)`
- L811 _private function_ `void CopyFrom(const THandleHeap<ElementType, IndexWidth, GenerationWidth>& Other)`
- L830 _private function_ `void MoveFrom(THandleHeap<ElementType, IndexWidth, GenerationWidth>& Other)`
- L861 _private function_ `friend FArchive& operator << (FArchive& Ar, FHandleEntry& InHandleEntry)`
- L876 _private member_ `uint32 FreeList;`
- L877 _private member_ `TArray<FHandleEntry> HandleEntries;`
- L878 _private member_ `TBitArray<> Validity;`
- L879 _private member_ `int32 NumActive;`

#### class `Chaos::THandleHeap::FHandleEntry`  
`class FHandleEntry`  
_L845-874_
- L849 _public function_ `FHandleEntry() : NextFree(InvalidFreeIndex) , Generation(1) , Ptr(nullptr)`
- L857 _public member_ `uint32 NextFree : IndexWidth;`
- L858 _public member_ `uint32 Generation : GenerationWidth;`
- L859 _public member_ `ElementType* Ptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L73 _function_ `friend FArchive& operator <<(FArchive& Ar, THandleData<IndexWidth, GenerationWidth>& InHandle)` (scope `Chaos`)
- L105 _function_ `friend bool operator ==(const THandle<ElementType, IndexWidth, GenerationWidth>& A, const THandle<ElementType, IndexWidth, GenerationWidth>& B)` (scope `Chaos`)
- L110 _function_ `friend FArchive& operator <<(FArchive& Ar, THandle<ElementType, IndexWidth, GenerationWidth>& InHandle)` (scope `Chaos`)
- L137 _function_ `friend bool operator ==(const TConstHandle<ElementType, IndexWidth, GenerationWidth>& A, const TConstHandle<ElementType, IndexWidth, GenerationWidth>& B)` (scope `Chaos`)
- L142 _function_ `friend FArchive& operator <<(FArchive& Ar, TConstHandle<ElementType, IndexWidth, GenerationWidth>& InHandle)` (scope `Chaos`)
- L373 _function_ `friend FArchive& operator <<(FArchive& Ar, THandleArray& Array)` (scope `Chaos`)
- L772 _function_ `friend FArchive& operator <<(FArchive& Ar, THandleHeap& Array)` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ImplicitQRSVD.h` (Public)


#### class `Chaos::GivensRotation`  
`template <class T> class GivensRotation`  
_L32-170_
- desc: Class for givens rotation. Row rotation G*A corresponds to something like c -s  0 ( s  c  0 ) A 0  0  1 Column rotation A G' corresponds to something like c -s  0 A ( s  c  0 ) 0  0  1 c and s are always Computed so that ( c -s ) ( a )  =  ( * ) s  c     b       ( 0 ) Assume rowi<rowk.
- L34 _public member_ `int rowi;`
- L35 _public member_ `int rowk;`
- L36 _public member_ `T c;`
- L37 _public member_ `T s;`
- L39 _public function_ `inline GivensRotation() : rowi(0), rowk(0), c((T)0.), s((T)0.)`
- L41 _public function_ `inline GivensRotation(int rowi_in, int rowk_in) : rowi(rowi_in), rowk(rowk_in), c(1), s(0)`
- L43 _public function_ `inline GivensRotation(T a, T b, int rowi_in, int rowk_in) : rowi(rowi_in), rowk(rowk_in)`
- L47 _public prototype_ `~GivensRotation() = default;`
- L49 _public function_ `inline void TransposeInPlace()`
- L58 _public function_ `inline void Compute(const T a, const T b)` — Compute c and s from a and b so that ( c -s ) ( a )  =  ( * ) s  c     b       ( 0 )
- L75 _public function_ `inline void ComputeUnconventional(const T a, const T b)` — This function Computes c and s so that ( c -s ) ( a )  =  ( 0 ) s  c     b       ( * )
- L89 _public function_ `inline void Fill(const PMatrix<T, 2, 2>& R) const` — template <class T>
- L106 _public function_ `inline void RowRotation(PMatrix<T, 2, 2>& A) const` — template <class T>
- L116 _public function_ `inline void RowRotation(PMatrix<T, 3, 3>& A) const` — template <class T>
- L133 _public function_ `inline void ColumnRotation(PMatrix<T, 2, 2>& A) const` — template <class T>
- L143 _public function_ `inline void ColumnRotation(PMatrix<T, 3, 3>& A) const` — template <class T>
- L155 _public function_ `inline void operator*=(const GivensRotation<T>& A)` — Multiply givens must be for same row and column
- L165 _public function_ `inline GivensRotation<T> operator*(const GivensRotation<T>& A) const` — Multiply givens must be for same row and column

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L183 _function_ `template <class T> inline void ZeroChase(PMatrix<T, 3, 3>& H, PMatrix<T, 3, 3>& U, PMatrix<T, 3, 3>& V)` (scope `Chaos`) — \brief zero chasing the 3X3 matrix to bidiagonal form original form of H:   x x 0 x x x 0 0 x after zero chase: x x 0 0 x x 0 0 x
- L235 _function_ `template <class T> inline void MakeUpperBidiag(PMatrix<T, 3, 3>& H, PMatrix<T, 3, 3>& U, PMatrix<T, 3, 3>& V)` (scope `Chaos`) — \brief make a 3X3 matrix to upper bidiagonal form original form of H:   x x x x x x x x x after zero chase: x x 0 0 x x 0 0 x
- L263 _function_ `template <class T> inline void MakeLambdaShape(PMatrix<T, 3, 3>& H, PMatrix<T, 3, 3>& U, PMatrix<T, 3, 3>& V)` (scope `Chaos`) — \brief make a 3X3 matrix to lambda shape original form of H:   x x x x x x x x x after : x 0 0 x x 0 x 0 x
- L323 _function_ `template <class T> inline void PolarDecomposition(const PMatrix<T, 2, 2>& A, GivensRotation<T>& R, PMatrix<T, 2, 2>& S_Sym)` (scope `Chaos`) — \brief 2x2 polar decomposition. \param[in] A matrix. \param[out] R Robustly a rotation matrix in givens form \param[out] S_Sym Symmetric. Whole matrix is stored Whole matrix S is stored since its faster to calculate due to simd vectorization Polar guarantees negative sign is on the small magnitude singular value. S is guaranteed to be the closest one to identity. R is guaranteed to be the closest rotation to A.
- L353 _function_ `template <class T> inline void PolarDecomposition(const PMatrix<T, 2, 2>& A, PMatrix<T, 2, 2>& R, PMatrix<T, 2, 2>& S_Sym)` (scope `Chaos`) — \brief 2x2 polar decomposition. \param[in] A matrix. \param[out] R Robustly a rotation matrix. \param[out] S_Sym Symmetric. Whole matrix is stored Whole matrix S is stored since its faster to calculate due to simd vectorization Polar guarantees negative sign is on the small magnitude singular value. S is guaranteed to be the closest one to identity. R is guaranteed to be the closest rotation to A.
- L367 _function_ `template < class T> inline void SingularValueDecomposition(const PMatrix<T, 2, 2>& A, GivensRotation<T>& U, const TVector<T, 2>& Sigma, GivensRotation<T>& V, const T tol = std::numeric_limits<T>::epsilon())` (scope `Chaos`) — \brief 2x2 SVD (singular value decomposition) A=USV' \param[in] A Input matrix. \param[out] U Robustly a rotation matrix in Givens form \param[out] Sigma Vector of singular values sorted with decreasing magnitude. The second one can be negative. \param[out] V Robustly a rotation matrix in Givens form
- L433 _function_ `template <class T> inline void SingularValueDecomposition( const PMatrix<T, 2, 2>& A, const PMatrix<T, 2, 2>& U, const TVector<T, 2>& Sigma, const PMatrix<T, 2, 2>& V, const T tol = std::numeric_limits<T>::epsilon())` (scope `Chaos`) — \brief 2x2 SVD (singular value decomposition) A=USV' \param[in] A Input matrix. \param[out] U Robustly a rotation matrix. \param[out] Sigma Vector of singular values sorted with decreasing magnitude. The second one can be negative. \param[out] V Robustly a rotation matrix.
- L454 _function_ `template <class T> T WilkinsonShift(const T a1, const T b1, const T a2)` (scope `Chaos`) — \brief Compute WilkinsonShift of the block a1     b1 b1     a2 based on the WilkinsonShift formula mu = c + d - sign (d) \ sqrt (d*d + b*b), where d = (a-c)/2
- L468 _function_ `template <int t, class T> inline void Process(PMatrix<T, 3, 3>& B, PMatrix<T, 3, 3>& U, TVector<T, 3>& sigma, PMatrix<T, 3, 3>& V)` (scope `Chaos`) — \brief Helper function of 3X3 SVD for Processing 2X2 SVD
- L494 _function_ `template <class T> inline void FlipSign(int i, PMatrix<T, 3, 3>& U, TVector<T, 3>& sigma)` (scope `Chaos`) — \brief Helper function of 3X3 SVD for flipping signs due to flipping signs of sigma
- L501 _function_ `template <class T> inline void SwapCols(PMatrix<T, 3, 3>& A, const int i1, const int i2)` (scope `Chaos`) — IMPORTANT: test this function before testing polar:
- L512 _function_ `template <class T> void Sort0(PMatrix<T, 3, 3>& U, TVector<T, 3>& sigma, PMatrix<T, 3, 3>& V)` (scope `Chaos`) — \brief Helper function of 3X3 SVD for sorting singular values
- L553 _function_ `template <class T> void Sort1(PMatrix<T, 3, 3>& U, TVector<T, 3>& sigma, PMatrix<T, 3, 3>& V)` (scope `Chaos`) — \brief Helper function of 3X3 SVD for Sorting singular values
- L597 _function_ `template <class T> inline int SingularValueDecomposition(const PMatrix<T, 3, 3>& A, PMatrix<T, 3, 3>& U, TVector<T, 3>& sigma, PMatrix<T, 3, 3>& V, T tol = std::numeric_limits<T>::epsilon())` (scope `Chaos`) — \brief 3X3 SVD (singular value decomposition) A=USV' \param[in] A Input matrix. \param[out] U is a rotation matrix. \param[out] sigma Diagonal matrix, sorted with decreasing magnitude. The third one can be negative. \param[out] V is a rotation matrix.
- L769 _function_ `template <class T> inline void PolarDecomposition(const PMatrix<T, 3, 3>& A, PMatrix<T, 3, 3>& R, PMatrix<T, 3, 3>& S_Sym)` (scope `Chaos`) — \brief 3X3 polar decomposition. \param[in] A matrix. \param[out] R Robustly a rotation matrix. \param[out] S_Sym Symmetric. Whole matrix is stored Whole matrix S is stored Polar guarantees negative sign is on the small magnitude singular value. S is guaranteed to be the closest one to identity. R is guaranteed to be the closest rotation to A.
- L782 _function_ `template <class T> void dRdFCorotated(const PMatrix<T, 3, 3>& F, TVector<T, 81>& dRdF)` (scope `Chaos`) — 3X3 version of dRdF indexing of diff: dRdF[9*(i*3+j)+(m*3+n)] = dR.GetAt(m, n) /dF.GetAt (i, j):

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Matrix.h` (Public)


#### struct `UE::Math::TMatrix`  
`struct UE::Math::TMatrix<FReal>`  
_L10-14_
- L13 _public member_ `std::array<std::array<Chaos::FReal, 4>, 4> M;`

#### class `Chaos::PMatrix`  
`template<class T, int m, int n> class PMatrix`  
_L21-26_
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealDouble, 3, 2>`  
_L29-61_
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealSingle, 3, 2>`  
_L64-141_
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FReal, 2, 2>`  
_L144-195_
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealSingle, 2, 2>`  
_L198-280_
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealSingle, 4, 4> : public UE::Math::TMatrix<FRealSingle>`  
_L283-327_
- inherits: `UE::Math::TMatrix<FRealSingle>`
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealDouble, 4, 4> : public UE::Math::TMatrix<FRealDouble>`  
_L330-374_
- inherits: `UE::Math::TMatrix<FRealDouble>`
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealDouble, 3, 3> : public UE::Math::TMatrix<FRealDouble>`  
_L378-816_
- inherits: `UE::Math::TMatrix<FRealDouble>`
- desc: TODO(mlentine): Do not use 4x4 matrix for 3x3 implementation
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### class `Chaos::PMatrix`  
`template<> class PMatrix<FRealSingle, 3, 3> : public UE::Math::TMatrix<FRealSingle>`  
_L819-1258_
- inherits: `UE::Math::TMatrix<FRealSingle>`
- L24 _private function_ `PMatrix()`
- L25 _private prototype_ `~PMatrix() = default;`
- L32 _public member_ `FRealDouble M[6];`
- L34 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2)`
- L44 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21)`
- L54 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 2>& Other)`
- L67 _public member_ `FRealSingle M[6];`
- L69 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2)`
- L79 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21)`
- L89 _public function_ `PMatrix(const FRealSingle x00)`
- L99 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 2>& Other)`
- L107 _public function_ `PMatrix<FRealSingle, 3,2> operator-(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L118 _public function_ `PMatrix<FRealSingle, 3, 2> operator+(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L147 _public member_ `FReal M[4];`
- L149 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x01, const FReal x11)`
- L157 _public function_ `PMatrix(const FReal x00, const FReal x10, const FReal x11)`
- L165 _public function_ `PMatrix<FReal, 2, 2> SubtractDiagonal(const FReal Scalar) const`
- L174 _public function_ `TVector<FReal, 2> TransformPosition(const TVector<FReal, 2>& Other) const`
- L181 _public function_ `PMatrix<FReal, 2, 2> Inverse() const`
- L191 _public function_ `PMatrix<FReal, 2, 2> GetTransposed() const`
- L201 _public member_ `FRealSingle M[4];`
- L203 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x01, const FRealSingle x11)`
- L211 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x11)`
- L219 _public function_ `PMatrix<FRealSingle, 2, 2> SubtractDiagonal(const FRealSingle Scalar) const`
- L228 _public function_ `TVector<FRealSingle, 2> TransformPosition(const TVector<FRealSingle, 2>& Other) const`
- L235 _public function_ `PMatrix<FRealSingle, 2, 2> Inverse() const`
- L245 _public function_ `PMatrix<FRealSingle, 2, 2> GetTransposed() const`
- L250 _public function_ `FRealSingle Determinant() const`
- L255 _public function_ `FORCEINLINE FRealSingle GetAt(int32 RowIndex, int32 ColIndex) const`
- L261 _public function_ `PMatrix<FRealSingle, 2, 2> operator*(const PMatrix<FRealSingle, 2, 2>& Other) const` — This is not column major so no need to invert matrix order when multiply them
- L286 _public function_ `PMatrix() : UE::Math::TMatrix<FRealSingle>()`
- L288 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x30, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x31, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22, const FRealSingle x32, const FRealSingle x03, const FRealSingle x13, const FRealSingle x23, const FRealSingle x33) : UE::Math::TMatrix<FRealSingle>()`
- L308 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Matrix) : UE::Math::TMatrix<FRealSingle>(Matrix)`
- L313 _public function_ `Vector<FRealSingle, 4> operator*(const Vector<Chaos::FRealSingle, 4>& Other)`
- L323 _public function_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Other) const`
- L333 _public function_ `PMatrix() : UE::Math::TMatrix<FRealDouble>()`
- L335 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x30, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x31, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22, const FRealDouble x32, const FRealDouble x03, const FRealDouble x13, const FRealDouble x23, const FRealDouble x33) : UE::Math::TMatrix<FRealDouble>()`
- L355 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Matrix) : UE::Math::TMatrix<FRealDouble>(Matrix)`
- L360 _public function_ `Vector<FRealDouble, 4> operator*(const Vector<Chaos::FRealDouble, 4>& Other)`
- L370 _public function_ `PMatrix<FRealDouble, 4, 4> operator*(const PMatrix<FRealDouble, 4, 4>& Other) const`
- L383 _public function_ `PMatrix(UE::Math::TMatrix<FRealDouble>&& Other) : UE::Math::TMatrix<FRealDouble>(MoveTemp(Other))`
- L385 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L387 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealDouble>((UE::Math::TMatrix<FRealDouble>)Other)`
- L389 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x11, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L410 _public function_ `explicit PMatrix(const TVector<FRealDouble, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L430 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x11, const FRealDouble x21, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L451 _public function_ `PMatrix(const FRealDouble x00, const FRealDouble x10, const FRealDouble x20, const FRealDouble x01, const FRealDouble x11, const FRealDouble x21, const FRealDouble x02, const FRealDouble x12, const FRealDouble x22) : UE::Math::TMatrix<FRealDouble>()`
- L472 _public function_ `PMatrix(const FRealDouble x) : UE::Math::TMatrix<FRealDouble>()`
- L493 _public function_ `PMatrix(const TVector<FRealDouble, 3>& C1, const TVector<FRealDouble, 3>& C2, const TVector<FRealDouble, 3>& C3)`
- L514 _public function_ `PMatrix<FRealDouble, 3, 3> GetTransposed() const`
- L518 _public function_ `FRealDouble Determinant() const`
- L522 _public function_ `PMatrix<FRealDouble, 3, 3>& operator+=(const PMatrix<FRealDouble, 3, 3>& Other)`
- L537 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L544 _public function_ `PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L561 _public function_ `PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L587 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other) const`
- L592 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L606 _public function_ `PMatrix<FRealDouble, 3, 3> operator*=(const FRealDouble Other)` — Needs to be overridden because base version multiplies M[3][3]
- L623 _public function_ `PMatrix<FRealDouble, 3, 2> operator*(const PMatrix<FRealDouble, 3, 2>& Other) const`
- L633 _public function_ `PMatrix<FRealDouble, 3, 3> SubtractDiagonal(const FRealDouble Scalar) const`
- L646 _public function_ `PMatrix<FRealDouble, 3, 3> SymmetricCofactorMatrix() const`
- L656 _public function_ `TVector<FRealDouble, 3> LargestColumnNormalized() const`
- L683 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L692 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealDouble, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L705 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L715 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealDouble, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L728 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L738 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealDouble, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L746 _public function_ `FORCEINLINE TVector<FRealDouble, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L751 _public function_ `FORCEINLINE FRealDouble GetAt(int32 RowIndex, int32 ColIndex) const`
- L756 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealDouble V)`
- L764 _public function_ `static PMatrix<FRealDouble, 3, 3> FromDiagonal(const TVector<FRealDouble, 3>& D)` — Return a diagonal matrix with the specified elements
- L771 _public function_ `PMatrix<FRealDouble, 3, 3> operator*(const PMatrix<FRealDouble, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L785 _public function_ `inline bool Equals(const PMatrix<FRealDouble, 3, 3>& Other, FRealDouble Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L800 _public function_ `static PMatrix<FRealDouble, 3, 3> OuterProduct(const TVector<FRealDouble, 3>& X, const TVector<FRealDouble, 3>& Y)` — M[i][j] = x[i] * y[j]
- L814 _public member_ `static const PMatrix<FRealDouble, 3, 3> Zero;`
- L815 _public member_ `static const PMatrix<FRealDouble, 3, 3> Identity;`
- L824 _public function_ `PMatrix(UE::Math::TMatrix<FRealSingle>&& Other) : UE::Math::TMatrix<FRealSingle>(MoveTemp(Other))`
- L826 _public function_ `PMatrix(const UE::Math::TMatrix<FRealSingle>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L828 _public function_ `PMatrix(const UE::Math::TMatrix<FRealDouble>& Other) : UE::Math::TMatrix<FRealSingle>((UE::Math::TMatrix<FRealSingle>)Other)`
- L830 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x11, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L851 _public function_ `explicit PMatrix(const TVector<FRealSingle, 3>& Vector) : UE::Math::TMatrix<FReal>()`
- L871 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x11, const FRealSingle x21, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L892 _public function_ `PMatrix(const FRealSingle x00, const FRealSingle x10, const FRealSingle x20, const FRealSingle x01, const FRealSingle x11, const FRealSingle x21, const FRealSingle x02, const FRealSingle x12, const FRealSingle x22) : UE::Math::TMatrix<FRealSingle>()`
- L913 _public function_ `PMatrix(const FRealSingle x) : UE::Math::TMatrix<FRealSingle>()`
- L934 _public function_ `PMatrix(const TVector<FRealSingle, 3>& C1, const TVector<FRealSingle, 3>& C2, const TVector<FRealSingle, 3>& C3)`
- L955 _public function_ `PMatrix<FRealSingle, 3, 3> GetTransposed() const`
- L963 _public function_ `PMatrix<FRealSingle, 3, 3>& operator+=(const PMatrix<FRealSingle, 3, 3>& Other)`
- L978 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const` — TDOD(mlentine): This should really be a vector multiply and sum for each entry using sse
- L985 _public function_ `PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1002 _public function_ `PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1028 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other) const`
- L1033 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle Other) const` — Needs to be overridden because base version multiplies M[3][3]
- L1047 _public function_ `PMatrix<FRealSingle, 3, 3> operator*=(const FRealSingle Other)` — Needs to be overridden because base version multiplies M[3][3]
- L1064 _public function_ `PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& Other) const`
- L1074 _public function_ `PMatrix<FRealSingle, 3, 3> SubtractDiagonal(const FRealSingle Scalar) const`
- L1087 _public function_ `PMatrix<FRealSingle, 3, 3> SymmetricCofactorMatrix() const`
- L1097 _public function_ `TVector<FRealSingle, 3> LargestColumnNormalized() const`
- L1124 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetAxis(int32 AxisIndex) const` — Get the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1133 _public function_ `FORCEINLINE void SetAxis(int32 AxisIndex, const TVector<FRealSingle, 3>& Axis)` — Set the specified axis (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so axis elements are sequential in memory
- L1146 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetRow(int32 RowIndex) const` — Get the specified row (0-indexed, X,Y,Z). @note: we are treating matrices as column major, so rows are not sequential in memory @seealso GetAxis, GetColumn
- L1156 _public function_ `FORCEINLINE void SetRow(int32 RowIndex, const TVector<FRealSingle, 3>& V)` — Set the specified row. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetColumn
- L1169 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetColumn(int32 ColumnIndex) const` — Get the specified column (0-indexed, X,Y,Z). Equivalent to GetAxis. @note: we are treating matrices as column major, so columns are sequential in memory @seealso GetAxis, GetRow
- L1179 _public function_ `FORCEINLINE void SetColumn(int32 ColumnIndex, const TVector<FRealSingle, 3>& V)` — Set the specified column. Equivalent to SetAxis. @note: we are treating matrices as column major, so axis elements are sequential in memory @seealso SetAxis, SetRow
- L1187 _public function_ `FORCEINLINE TVector<FRealSingle, 3> GetDiagonal() const` — Get the diagonal elements as a vector.
- L1197 _public function_ `FORCEINLINE void SetAt(int32 RowIndex, int32 ColIndex, FRealSingle V)`
- L1205 _public function_ `static PMatrix<FRealSingle, 3, 3> FromDiagonal(const TVector<FRealSingle, 3>& D)` — Return a diagonal matrix with the specified elements
- L1212 _public function_ `PMatrix<FRealSingle, 3, 3> operator*(const PMatrix<FRealSingle, 3, 3>& Other)` — TODO(mlentine): Document which one is row and which one is column
- L1226 _public function_ `inline bool Equals(const PMatrix<FRealSingle, 3, 3>& Other, FRealSingle Tolerance = UE_KINDA_SMALL_NUMBER) const`
- L1241 _public function_ `static PMatrix<FRealSingle, 3, 3> OuterProduct(const TVector<FRealSingle, 3>& X, const TVector<FRealSingle, 3>& Y)` — M[i][j] = x[i] * y[j]
- L1256 _public member_ `static const PMatrix<FRealSingle, 3, 3> Zero;`
- L1257 _public member_ `static const PMatrix<FRealSingle, 3, 3> Identity;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`
- L129 _function_ `friend PMatrix<FRealSingle, 3, 2> operator*(const FRealSingle OtherF, const PMatrix<FRealSingle, 3, 2>& OtherM)` (scope `Chaos`)
- L270 _function_ `friend PMatrix<FRealSingle, 3, 2> operator*(const PMatrix<FRealSingle, 3, 2>& First, const PMatrix<FRealSingle, 2, 2>& Other)` (scope `Chaos`)
- L557 _function_ `friend PMatrix<FRealDouble, 3, 3> operator+(const PMatrix<FRealDouble, 3, 3>& Other)` (scope `Chaos`)
- L574 _function_ `friend PMatrix<FRealDouble, 3, 3> operator-(const PMatrix<FRealDouble, 3, 3>& Other)` (scope `Chaos`)
- L619 _function_ `friend PMatrix<FRealDouble, 3, 3> operator*(const FRealDouble OtherF, const PMatrix<FRealDouble, 3, 3>& OtherM)` (scope `Chaos`)
- L998 _function_ `friend PMatrix<FRealSingle, 3, 3> operator+(const PMatrix<FRealSingle, 3, 3>& Other)` (scope `Chaos`)
- L1015 _function_ `friend PMatrix<FRealSingle, 3, 3> operator-(const PMatrix<FRealSingle, 3, 3>& Other)` (scope `Chaos`)
- L1060 _function_ `friend PMatrix<FRealSingle, 3, 3> operator*(const FRealSingle OtherF, const PMatrix<FRealSingle, 3, 3>& OtherM)` (scope `Chaos`)
- L1260 _typedef_ `typedef PMatrix<double, 3, 3> PMatrix33d;` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/ObjectPool.h` (Public)


#### class `Chaos::TObjectPool`  
`template<typename ObjectType> class TObjectPool`  
_L24-558_
- L29 _public member_ `constexpr static int32 ItemAlign = alignof(ObjectType);` — Alignment of the stored type
- L31 _public typedef_ `using FObject = ObjectType;`
- L32 _public typedef_ `using FPtr = ObjectType*;`
- L34 _public function_ `explicit TObjectPool(int32 InNumPerBlock, int32 InitialBlocks = 1) : NumPerBlock(InNumPerBlock)`
- L40 _public function_ `~TObjectPool()`
- L48 _public prototype_ `TObjectPool() = delete;` — No copy, no move, no default #TODO possibly add move and copy if the internal type is copy constructible but likely better to discourage copying. Moving to another pool should be fine.
- L49 _public prototype_ `TObjectPool(const TObjectPool&) = delete;`
- L50 _public prototype_ `TObjectPool(TObjectPool&&) = delete;`
- L51 _public prototype_ `TObjectPool& operator=(const TObjectPool&) = delete;`
- L52 _public prototype_ `TObjectPool& operator=(TObjectPool&&) = delete;`
- L64 _public function_ `template<typename... TArgs> FPtr Alloc(TArgs&&... Args)` — Allocate an object from the pool Returns an instance of the object type specified for this pool, either from the next available on the final block, the free list or by allocating a new block to continue providing objects. As this method may defer to the runtime allocator it may sometimes run significantly slower when the pool is exhausted Requires that the object is default constructible @param Args - ObjectType constructor arguments @return The newly allocated object
- L119 _public function_ `void Free(FPtr Object)` — Free a single object provided by this pool Takes an object previously allocated in this pool and frees it, accessing the pointer beyond a call to free is an undefined operation and could return garbage or an entirely different object. Avoiding this case is the responsibility of the caller Behavior is also undefined if an object not owned by this pool is passed to Free. Outside of debug this will not be asserted @param Object The object to free
- L132 _public function_ `void Reset()` — Reset the whole pool This will invalidate every currently live object from the pool. If a pointer from this pool is dereferenced beyond a call to Reset then it may return garbage, or point to an entirely different object. Avoiding this case is the responsibility of the caller.
- L145 _public function_ `int32 GetNumAllocatedBlocks() const` — Get the number of blocks currently allocated in the pool
- L153 _public function_ `int32 GetNumPerBlock() const` — Get the max number of items per block
- L161 _public function_ `int32 GetAllocatedSize() const` — Get the allocated (total) size of all blocks in the pool
- L172 _public function_ `void ShrinkTo(int32 NumDesiredEmptyBlocks)` — Shrinks the number of blocks All blocks that are not empty are kept, plus a number of empty blocks specified by the caller Passing zero will remove all empty blocks, leaving any non-empty blocks behind @param NumDesiredEmptyBlocks - number of empty blocks to keep
- L200 _public function_ `void ReserveBlocks(int32 NumBlocks)` — Makes sure the pool has at least NumBlocks blocks allocated Note: This will never reduce the number of blocks, it will only make sure the pool has at least NumBlocks block allocated, empty or not. @param NumBlocks - Number of blocks to reserve
- L217 _public function_ `void ReserveItems(int32 NumItems)` — Makes sure the pool has at least enough blocks allocated to store NumItems Not: This isn't a number of free items, but total items. If a pool has 100 items in it and ReserveItems(100); is called - no action will be taken. This function will also never remove blocks from the pool - only ever increase. To reduce the number of blocks see ShrinkTo @see ShrinkTo @Param NumItems - Number of items to reserve
- L230 _public function_ `float GetRatio() const` — Calculates the storage/overhead ratio of the pool. Larger items that have a size close to the alignment boundary will be more efficient on space @return Ratio of storage to overhead
- L238 _public function_ `int32 GetNumAllocated() const` — Get the number of allocated items.
- L247 _public function_ `int32 GetNumFree() const` — Gets the number of free items the pool has remaining @return Number of free items
- L256 _public function_ `int32 GetCapacity() const` — Gets the total number of items the pool can currently stor @return The pool capacity
- L311 _private typedef_ `using FItem = TItem<ObjectType>;` — Helper alias for the item in this pool
- L315 _private member_ `constexpr static int32 PaddedItemSize = Align(int32(sizeof(FItem)), ItemAlign);` — Size of the item, plus padding up to the correct alignment so we can allocate the whole block with the correct size.
- L446 _private function_ `FBlock& AddBlock()` — Adds a block to the pool, updating internal tracking state as appropriate @return Reference to the new block
- L463 _private function_ `int32 FindBlock(ObjectType* InPtr)` — Find the index of the owning block for the provided pointer The provided pointer must have been provided from this pool otherwise an assert will fire. @param InPtr the pointer to search for @return Index for the found block
- L489 _private function_ `static ObjectType* Construct(ObjectType* At, TArgs&&... Args)`
- L528 _private function_ `static void ConditionalDestruct(ObjectType* At)`
- L550 _private function_ `static void ConditionalDestruct(ObjectType*)`
- L553 _private member_ `TArray<FBlock> Blocks;`
- L555 _private member_ `int32 NumPerBlock = 0;`
- L556 _private member_ `int32 Capacity = 0;`
- L557 _private member_ `int32 FreeCount = 0;`

#### struct `Chaos::TObjectPool::TItem`  
`template<typename T_ = ObjectType, typename Destructible = void> struct alignas(ItemAlign) TItem`  
_L265-280_
- desc: Storage for an item, and an index of the next free item if it's currently on the free list
- L267 _public function_ `TItem() : NextFree(INDEX_NONE)`
- L272 _public member_ `ObjectType Object;` — Object must always remain as the first item to enable casting between Item and Object
- L275 _public member_ `int32 NextFree;` — Free-list tracking, index of the next free item
- L278 _public function_ `void SetLive(bool)` — Set whether the object is live - encapsulated in a function as the base template performs no action
- L300 _public member_ `bool bLive : 1;` — Whether the object is live (constructed) and will require destruction
- L304 _public function_ `void SetLive(bool bInLive)` — Set whether the object is live - encapsulated in a function as the base template performs no action @param bInLive - new live flag value

#### struct `Chaos::TObjectPool::TItem`  
`template<typename T_> struct alignas(ItemAlign) TItem<T_, TRequiresDestructor<T_>>`  
_L287-308_
- desc: Specialized type for types that require a destructor as we need to add an extra flag for live/dead objects (calling Free will destruct the object but Reset/DestroyAll will need to destruct any non-free objects). This is specialized so that if the type is trivially destructible we can avoid adding the extra member.
- L267 _public function_ `TItem() : NextFree(INDEX_NONE)`
- L272 _public member_ `ObjectType Object;` — Object must always remain as the first item to enable casting between Item and Object
- L275 _public member_ `int32 NextFree;` — Free-list tracking, index of the next free item
- L278 _public function_ `void SetLive(bool)` — Set whether the object is live - encapsulated in a function as the base template performs no action
- L300 _public member_ `bool bLive : 1;` — Whether the object is live (constructed) and will require destruction
- L304 _public function_ `void SetLive(bool bInLive)` — Set whether the object is live - encapsulated in a function as the base template performs no action @param bInLive - new live flag value

#### struct `Chaos::TObjectPool::FBlock`  
`struct FBlock`  
_L319-440_
- desc: A block is an area of memory large enough to hold NumInBlock items, correctly aligned and provide items on demand to the pool
- L321 _public prototype_ `FBlock() = delete;`
- L323 _public function_ `explicit FBlock(int32 InNum) : Begin(static_cast<FItem*>(FMemory::Malloc(PaddedItemSize * InNum, ItemAlign))) , Next(Begin) , NumInBlock(InNum) , NumFree(NumInBlock)`
- L331 _public function_ `~FBlock()`
- L339 _public function_ `FPtr GetNextFree()`
- L369 _public function_ `void Free(ObjectType* Object)`
- L391 _public function_ `void Reset()`
- L401 _public function_ `void DestructAll()`
- L410 _public function_ `bool Owns(ObjectType* InPtr) const`
- L417 _public function_ `bool IsEmpty() const`
- L422 _public function_ `bool IsFull() const`
- L428 _public member_ `FItem* Begin = nullptr;` — Ptr to the beginning of the block
- L430 _public member_ `FItem* Next = nullptr;` — Ptr to the next free item when block is filling initially
- L433 _public member_ `const int32 NumInBlock;` — Number of items the block can hold
- L435 _public member_ `int32 NumFree = 0;` — Count of free items in the block
- L437 _public member_ `int32 NumValid = 0;` — The maximum number of valid items in the block (items are valid if they were ever allocated / constructed)
- L439 _public member_ `int32 FreeList = INDEX_NONE;` — Head of the free list for this block

#### class `Chaos::TObjectPoolDeleter`  
`template<typename ObjectPoolType> class TObjectPoolDeleter`  
_L565-592_
- desc: A deleter for use with TUniquePtr and a TObjectPool item
- L568 _public typedef_ `using FObjectPool = ObjectPoolType;`
- L569 _public typedef_ `using FObject = typename FObjectPool::FObject;`
- L571 _public function_ `TObjectPoolDeleter() : Pool(nullptr)`
- L576 _public function_ `TObjectPoolDeleter(FObjectPool& InPool) : Pool(&InPool)`
- L581 _public function_ `void operator()(FObject* Object)`
- L591 _private member_ `FObjectPool* Pool;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L17 _typedef_ `template<typename T> using TRequiresDestructor = std::enable_if_t<!std::is_trivially_destructible_v<T>>;` (scope `Chaos`) — The type needs to have a destructor run when the pool pointer is freed
- L21 _typedef_ `template<typename T> using TTrivialDestruct = std::enable_if_t<std::is_trivially_destructible_v<T>>;` (scope `Chaos`) — The type needs no destruction and can just be abandoned on free

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Pair.h` (Public)


#### struct `Chaos::Pair`  
`template<class T1, class T2> struct Pair`  
_L7-16_
- L9 _public function_ `Pair()`
- L11 _public function_ `Pair(const T1& First, const T2& Second) : First(First), Second(Second)`
- L14 _public member_ `T1 First;`
- L15 _public member_ `T2 Second;`

#### Free symbols / members of external scopes

- L4 _namespace_ `namespace Chaos`
- L19 _function_ `template<class T1, class T2> bool operator==(const Pair<T1, T2>& First, const Pair<T1, T2>& Second)` (scope `Chaos`)
- L25 _function_ `template<class T1, class T2> bool operator<(const Pair<T1, T2>& First, const Pair<T1, T2>& Second)` (scope `Chaos`)
- L35 _function_ `template<class T1, class T2> bool operator>(const Pair<T1, T2>& First, const Pair<T1, T2>& Second)` (scope `Chaos`)
- L45 _function_ `template<class T1, class T2> Pair<T1, T2> MakePair(const T1& First, const T2& Second)` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Range.h` (Public)


#### struct `Chaos::FRange`  
`struct FRange`  
_L8-13_
- L10 _public function_ `FRange(int32 InStart, int32 InCount) : Start(InStart), Count(InCount)`
- L11 _public member_ `int32 Start;`
- L12 _public member_ `int32 Count;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`
- L15 _function_ `inline bool operator==(const FRange& First, const FRange& Second)` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Raycasts.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`
- L6 _namespace_ `namespace Raycasts` (scope `Chaos`)
- L9 _prototype_ `template <typename T, int d> bool RayAabb(const TVector<FReal, d>& RayStart, const TVector<FReal, d>& RayDir, const FReal RayLength, const FReal RayThickness, const TVector<T, d>& AabbMin, const TVector<T, d>& AabbMax, FReal& OutTime, TVector<FReal, d>& OutPosition, TVector<FReal, d>& OutNormal, int32& OutFaceIndex);` (scope `Chaos::Raycasts`)
- L12 _function_ `template <typename T, int d> FORCEINLINE bool RayAabb(const TVector<FReal, d>& RayStart, const TVector<FReal, d>& RayDir, const TVector<FReal, d>& InvRayDir, const bool* bRayParallel, const FReal RayLength, const TVector<T, d>& AabbMin, const TVector<T, d>& AabbMax, FReal& OutEntryTime, FReal& OutExitTime)` (scope `Chaos::Raycasts`)
- L69 _prototype_ `bool RayCapsule(const FVec3& RayStart, const FVec3& RayDir, const FReal RayLength, const FReal RayThickness, FReal CapsuleRadius, FReal CapsuleHeight, const FVec3& CapsuleAxis, const FVec3& CapsuleX1, const FVec3& CapsuleX2, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal);` (scope `Chaos::Raycasts`)
- L72 _function_ `template <typename T, int d> bool RaySphere(const TVector<T, d>& RayStart, const TVector<T, d>& RayDir, const T RayLength, const T RayThickness, const FVec3f& SphereCenter, const FRealSingle SphereRadius, T& OutTime, TVector<T, d>& OutPosition, TVector<T, d>& OutNormal)` (scope `Chaos::Raycasts`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Real.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L13 _typedef_ `using FRealDouble = double;` (scope `Chaos`) — Specific precision types, this should be used in very targeted places where the use of a specific type is necessary over using FReal
- L14 _typedef_ `using FRealSingle = float;` (scope `Chaos`)
- L22 _typedef_ `using FReal = FRealDouble;` (scope `Chaos`)
- L28 _variable_ `inline constexpr bool bRealTypeCompatibleWithISPC = std::is_same_v<FReal, float> || std::is_same_v<FReal, double>;` (scope `Chaos`) — ISPC optimization supports float and double, this allows classes that uses ISPC to branch to the right implementation without having to check the actual underlying type of FReal

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Rotation.h` (Public)


#### struct `_FQuat`  
`struct _FQuat`  
_L15-33_
- L18 _public function_ `const Chaos::FReal operator[](const int32 i) const`
- L22 _public function_ `Chaos::FReal& operator[](const int32 i)`
- L26 _public member_ `std::array<Chaos::FReal, 3> angles;`
- L27 _public function_ `static MakeFromEuler(const Vector<Chaos::FReal, 3>& InAngles)`

#### class `Chaos::TRotation`  
`template<class T, int d> class TRotation`  
_L40-45_
- L43 _private function_ `TRotation()`
- L44 _private prototype_ `~TRotation() = default;`
- L50 _private typedef_ `using BaseQuat = UE::Math::TQuat<FRealSingle>;`
- L52 _public function_ `TRotation() : BaseQuat()`
- L54 _public function_ `TRotation(const BaseQuat& Quat) : BaseQuat(Quat)`
- L56 _public function_ `TRotation(const FMatrix44f& Matrix) : BaseQuat(Matrix)`
- L58 _public function_ `TRotation(const FMatrix44d& Matrix) : BaseQuat(FMatrix44f(Matrix))`
- L61 _public function_ `template<typename OtherType> TRotation(const UE::Math::TQuat<OtherType>& Other) : BaseQuat((FRealSingle)Other.X, (FRealSingle)Other.Y, (FRealSingle)Other.Z, (FRealSingle)Other.W)`
- L64 _public function_ `inline PMatrix<FRealSingle, 3, 3> ToMatrix() const`
- L82 _public function_ `inline bool ToAxisAndAngleSafe(TVector<FRealSingle, 3>& OutAxis, FRealSingle& OutAngle, const TVector<FRealSingle, 3>& DefaultAxis, FRealSingle EpsilionSq = 1e-6f) const` — Extract the axis and angle from the Quaternion. @param OutAxis The axis of rotation. @param OutAngle The angle of rotation about the axis (radians). @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L98 _public function_ `inline bool GetRotationAxisSafe(TVector<FRealSingle, 3>& OutAxis, const TVector<FRealSingle, 3>& DefaultAxis, FRealSingle EpsilionSq = 1e-6f) const` — Extract the axis from the Quaternion. @param OutAxis The axis of rotation. @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L118 _public function_ `inline void ToMatrixAxes(TVector<FRealSingle, 3>& OutX, TVector<FRealSingle, 3>& OutY, TVector<FRealSingle, 3>& OutZ)` — Convert to a matrix and return as the 3 matrix axes.
- L134 _public function_ `inline void ToSwingTwistX(BaseQuat& OutSwing, BaseQuat& OutTwist) const` — Extract the Swing and Twist rotations, assuming that the Twist Axis is (1,0,0). /see ToSwingTwist
- L143 _public function_ `FORCEINLINE FRealSingle GetAbsMax() const` — @brief Return the large absolute element value
- L151 _public function_ `static inline FRealSingle DotProduct(const TRotation<FRealSingle, 3>& L, const TRotation<FRealSingle, 3>& R)` — @brief Return the dot product of two quaternions
- L159 _public prototype_ `static TRotation<FRealSingle, 3> Conjugate(const ::Chaos::TRotation<FRealSingle, 3>& InR);` — Return the complex conjugate of the rotation
- L164 _public prototype_ `static TRotation<FRealSingle, 3> Negate(const ::Chaos::TRotation<FRealSingle, 3>& InR);` — Negate all values of the quaternion (note: not the inverse rotation. See Conjugate)
- L169 _public function_ `static inline TRotation<FRealSingle, 3> FromIdentity()` — Create an identity rotation
- L177 _public function_ `static inline TRotation<FRealSingle, 3> FromElements(const FRealSingle X, const FRealSingle Y, const FRealSingle Z, const FRealSingle W)` — Create a rotation by explicitly specifying all elements
- L186 _public function_ `static inline TRotation<FRealSingle, 3> FromElements(const ::Chaos::TVector<FRealSingle, 3>& V, const FRealSingle W)` — Create a rotation by explicitly specifying all elements
- L194 _public function_ `static inline TRotation<FRealSingle, 3> FromAxisAngle(const ::Chaos::TVector<FRealSingle, 3>& Axis, const FRealSingle AngleRad)` — Create a rotation about an axis by an angle specified in radians
- L202 _public prototype_ `static TRotation<FRealSingle, 3> FromVector(const ::Chaos::TVector<FRealSingle, 3>& V);` — Create a rotation about an axis V/|V| by angle |V| in radians
- L207 _public prototype_ `static TRotation<FRealSingle, 3> FromRotatedVector( const ::Chaos::TVector<FRealSingle, 3>& InitialVector, const ::Chaos::TVector<FRealSingle, 3>& FinalVector);` — Generate a Rotation that would rotate vector InitialVector to FinalVector
- L216 _public prototype_ `static TVector<FRealSingle, 3> CalculateAngularVelocity1(const TRotation<FRealSingle, 3>& R0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L223 _public prototype_ `static TVector<FRealSingle, 3> CalculateAngularVelocity2(const TRotation<FRealSingle, 3>& R0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the Quaternion to Axis/Angle method.
- L230 _public function_ `static inline TVector<FRealSingle, 3> CalculateAngularVelocity(const TRotation<FRealSingle, 3>& InR0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt)` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L240 _public function_ `static inline TVector<FRealSingle, 3> CalculateAngularDelta(const TRotation<FRealSingle, 3>& InR0, const TRotation<FRealSingle, 3>& InR1)` — Calculate the axis-angle delta (angular velocity * dt) required to take an object with orientation R0 to orientation R1. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L250 _public prototype_ `static TRotation<FRealSingle, 3> IntegrateRotationWithAngularVelocity(const TRotation<FRealSingle, 3>& InR0, const TVector<FRealSingle, 3>& InW, const FRealSingle InDt);` — Return a new rotation equal to the input rotation with angular velocity W applied over time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L257 _public function_ `static inline bool IsNearlyEqual(const TRotation<FRealSingle, 3>& A, const TRotation<FRealSingle, 3>& B, const FRealSingle Epsilon)` — Check that two rotations are approximately equal. Assumes the quaternions are normalized and in the same hemisphere. For small values of Epsilon, this is approximately equivalent to checking that the rotations are within 2*Epsilon radians of each other.
- L269 _private typedef_ `using BaseQuat = UE::Math::TQuat<FRealDouble>;`
- L275 _public function_ `TRotation(const FMatrix44d& Matrix) : BaseQuat(Matrix)`
- L277 _public function_ `TRotation(const FMatrix44f& Matrix) : BaseQuat(FMatrix44d(Matrix))`
- L280 _public function_ `template<typename OtherType> TRotation(const UE::Math::TQuat<OtherType>& Other) : BaseQuat((FRealDouble)Other.X, (FRealDouble)Other.Y, (FRealDouble)Other.Z, (FRealDouble)Other.W)`
- L283 _public function_ `inline PMatrix<FRealDouble, 3, 3> ToMatrix() const`
- L301 _public function_ `inline bool ToAxisAndAngleSafe(TVector<FRealDouble, 3>& OutAxis, FRealDouble& OutAngle, const TVector<FRealDouble, 3>& DefaultAxis, FRealDouble EpsilionSq = 1e-6f) const` — Extract the axis and angle from the Quaternion. @param OutAxis The axis of rotation. @param OutAngle The angle of rotation about the axis (radians). @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L317 _public function_ `inline bool GetRotationAxisSafe(TVector<FRealDouble, 3>& OutAxis, const TVector<FRealDouble, 3>& DefaultAxis, FRealDouble EpsilionSq = 1e-6f) const` — Extract the axis from the Quaternion. @param OutAxis The axis of rotation. @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L337 _public function_ `inline void ToMatrixAxes(TVector<FRealDouble, 3>& OutX, TVector<FRealDouble, 3>& OutY, TVector<FRealDouble, 3>& OutZ)` — Convert to a matrix and return as the 3 matrix axes.
- L362 _public function_ `FORCEINLINE FRealDouble GetAbsMax() const` — @brief Return the large absolute element value
- L370 _public function_ `static inline FRealDouble DotProduct(const TRotation<FRealDouble, 3>& L, const TRotation<FRealDouble, 3>& R)` — @brief Return the dot product of two quaternions
- L378 _public prototype_ `static TRotation<FRealDouble, 3> Conjugate(const ::Chaos::TRotation<FRealDouble, 3>& InR);` — Return the complex conjugate of the rotation
- L383 _public prototype_ `static TRotation<FRealDouble, 3> Negate(const ::Chaos::TRotation<FRealDouble, 3>& InR);` — Negate all values of the quaternion (note: not the inverse rotation. See Conjugate)
- L388 _public function_ `static inline TRotation<FRealDouble, 3> FromIdentity()` — Create an identity rotation
- L396 _public function_ `static inline TRotation<FRealDouble, 3> FromElements(const FRealDouble X, const FRealDouble Y, const FRealDouble Z, const FRealDouble W)` — Create a rotation by explicitly specifying all elements
- L405 _public function_ `static inline TRotation<FRealDouble, 3> FromElements(const ::Chaos::TVector<FRealDouble, 3>& V, const FRealDouble W)` — Create a rotation by explicitly specifying all elements
- L413 _public function_ `static inline TRotation<FRealDouble, 3> FromAxisAngle(const ::Chaos::TVector<FRealDouble, 3>& Axis, const FRealDouble AngleRad)` — Create a rotation about an axis by an angle specified in radians
- L421 _public prototype_ `static TRotation<FRealDouble, 3> FromVector(const ::Chaos::TVector<FRealDouble, 3>& V);` — Create a rotation about an axis V/|V| by angle |V| in radians
- L426 _public prototype_ `static TRotation<FRealDouble, 3> FromRotatedVector( const ::Chaos::TVector<FRealDouble, 3>& InitialVector, const ::Chaos::TVector<FRealDouble, 3>& FinalVector);` — Generate a Rotation that would rotate vector InitialVector to FinalVector
- L435 _public prototype_ `static TVector<FRealDouble, 3> CalculateAngularVelocity1(const TRotation<FRealDouble, 3>& R0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L442 _public prototype_ `static TVector<FRealDouble, 3> CalculateAngularVelocity2(const TRotation<FRealDouble, 3>& R0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the Quaternion to Axis/Angle method.
- L449 _public function_ `static inline TVector<FRealDouble, 3> CalculateAngularVelocity(const TRotation<FRealDouble, 3>& InR0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt)` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L459 _public function_ `static inline TVector<FRealDouble, 3> CalculateAngularDelta(const TRotation<FRealDouble, 3>& InR0, const TRotation<FRealDouble, 3>& InR1)` — Calculate the axis-angle delta (angular velocity * dt) required to take an object with orientation R0 to orientation R1. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L469 _public prototype_ `static TRotation<FRealDouble, 3> IntegrateRotationWithAngularVelocity(const TRotation<FRealDouble, 3>& InR0, const TVector<FRealDouble, 3>& InW, const FRealDouble InDt);` — Return a new rotation equal to the input rotation with angular velocity W applied over time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L476 _public function_ `static inline bool IsNearlyEqual(const TRotation<FRealDouble, 3>& A, const TRotation<FRealDouble, 3>& B, const FRealDouble Epsilon)` — Check that two rotations are approximately equal. Assumes the quaternions are normalized and in the same hemisphere. For small values of Epsilon, this is approximately equivalent to checking that the rotations are within 2*Epsilon radians of each other.

#### class `Chaos::TRotation`  
`template<> class TRotation<FRealSingle, 3> : public UE::Math::TQuat<FRealSingle>`  
_L48-264_
- inherits: `UE::Math::TQuat<FRealSingle>`
- L43 _private function_ `TRotation()`
- L44 _private prototype_ `~TRotation() = default;`
- L50 _private typedef_ `using BaseQuat = UE::Math::TQuat<FRealSingle>;`
- L52 _public function_ `TRotation() : BaseQuat()`
- L54 _public function_ `TRotation(const BaseQuat& Quat) : BaseQuat(Quat)`
- L56 _public function_ `TRotation(const FMatrix44f& Matrix) : BaseQuat(Matrix)`
- L58 _public function_ `TRotation(const FMatrix44d& Matrix) : BaseQuat(FMatrix44f(Matrix))`
- L61 _public function_ `template<typename OtherType> TRotation(const UE::Math::TQuat<OtherType>& Other) : BaseQuat((FRealSingle)Other.X, (FRealSingle)Other.Y, (FRealSingle)Other.Z, (FRealSingle)Other.W)`
- L64 _public function_ `inline PMatrix<FRealSingle, 3, 3> ToMatrix() const`
- L82 _public function_ `inline bool ToAxisAndAngleSafe(TVector<FRealSingle, 3>& OutAxis, FRealSingle& OutAngle, const TVector<FRealSingle, 3>& DefaultAxis, FRealSingle EpsilionSq = 1e-6f) const` — Extract the axis and angle from the Quaternion. @param OutAxis The axis of rotation. @param OutAngle The angle of rotation about the axis (radians). @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L98 _public function_ `inline bool GetRotationAxisSafe(TVector<FRealSingle, 3>& OutAxis, const TVector<FRealSingle, 3>& DefaultAxis, FRealSingle EpsilionSq = 1e-6f) const` — Extract the axis from the Quaternion. @param OutAxis The axis of rotation. @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L118 _public function_ `inline void ToMatrixAxes(TVector<FRealSingle, 3>& OutX, TVector<FRealSingle, 3>& OutY, TVector<FRealSingle, 3>& OutZ)` — Convert to a matrix and return as the 3 matrix axes.
- L134 _public function_ `inline void ToSwingTwistX(BaseQuat& OutSwing, BaseQuat& OutTwist) const` — Extract the Swing and Twist rotations, assuming that the Twist Axis is (1,0,0). /see ToSwingTwist
- L143 _public function_ `FORCEINLINE FRealSingle GetAbsMax() const` — @brief Return the large absolute element value
- L151 _public function_ `static inline FRealSingle DotProduct(const TRotation<FRealSingle, 3>& L, const TRotation<FRealSingle, 3>& R)` — @brief Return the dot product of two quaternions
- L159 _public prototype_ `static TRotation<FRealSingle, 3> Conjugate(const ::Chaos::TRotation<FRealSingle, 3>& InR);` — Return the complex conjugate of the rotation
- L164 _public prototype_ `static TRotation<FRealSingle, 3> Negate(const ::Chaos::TRotation<FRealSingle, 3>& InR);` — Negate all values of the quaternion (note: not the inverse rotation. See Conjugate)
- L169 _public function_ `static inline TRotation<FRealSingle, 3> FromIdentity()` — Create an identity rotation
- L177 _public function_ `static inline TRotation<FRealSingle, 3> FromElements(const FRealSingle X, const FRealSingle Y, const FRealSingle Z, const FRealSingle W)` — Create a rotation by explicitly specifying all elements
- L186 _public function_ `static inline TRotation<FRealSingle, 3> FromElements(const ::Chaos::TVector<FRealSingle, 3>& V, const FRealSingle W)` — Create a rotation by explicitly specifying all elements
- L194 _public function_ `static inline TRotation<FRealSingle, 3> FromAxisAngle(const ::Chaos::TVector<FRealSingle, 3>& Axis, const FRealSingle AngleRad)` — Create a rotation about an axis by an angle specified in radians
- L202 _public prototype_ `static TRotation<FRealSingle, 3> FromVector(const ::Chaos::TVector<FRealSingle, 3>& V);` — Create a rotation about an axis V/|V| by angle |V| in radians
- L207 _public prototype_ `static TRotation<FRealSingle, 3> FromRotatedVector( const ::Chaos::TVector<FRealSingle, 3>& InitialVector, const ::Chaos::TVector<FRealSingle, 3>& FinalVector);` — Generate a Rotation that would rotate vector InitialVector to FinalVector
- L216 _public prototype_ `static TVector<FRealSingle, 3> CalculateAngularVelocity1(const TRotation<FRealSingle, 3>& R0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L223 _public prototype_ `static TVector<FRealSingle, 3> CalculateAngularVelocity2(const TRotation<FRealSingle, 3>& R0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the Quaternion to Axis/Angle method.
- L230 _public function_ `static inline TVector<FRealSingle, 3> CalculateAngularVelocity(const TRotation<FRealSingle, 3>& InR0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt)` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L240 _public function_ `static inline TVector<FRealSingle, 3> CalculateAngularDelta(const TRotation<FRealSingle, 3>& InR0, const TRotation<FRealSingle, 3>& InR1)` — Calculate the axis-angle delta (angular velocity * dt) required to take an object with orientation R0 to orientation R1. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L250 _public prototype_ `static TRotation<FRealSingle, 3> IntegrateRotationWithAngularVelocity(const TRotation<FRealSingle, 3>& InR0, const TVector<FRealSingle, 3>& InW, const FRealSingle InDt);` — Return a new rotation equal to the input rotation with angular velocity W applied over time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L257 _public function_ `static inline bool IsNearlyEqual(const TRotation<FRealSingle, 3>& A, const TRotation<FRealSingle, 3>& B, const FRealSingle Epsilon)` — Check that two rotations are approximately equal. Assumes the quaternions are normalized and in the same hemisphere. For small values of Epsilon, this is approximately equivalent to checking that the rotations are within 2*Epsilon radians of each other.
- L269 _private typedef_ `using BaseQuat = UE::Math::TQuat<FRealDouble>;`
- L275 _public function_ `TRotation(const FMatrix44d& Matrix) : BaseQuat(Matrix)`
- L277 _public function_ `TRotation(const FMatrix44f& Matrix) : BaseQuat(FMatrix44d(Matrix))`
- L280 _public function_ `template<typename OtherType> TRotation(const UE::Math::TQuat<OtherType>& Other) : BaseQuat((FRealDouble)Other.X, (FRealDouble)Other.Y, (FRealDouble)Other.Z, (FRealDouble)Other.W)`
- L283 _public function_ `inline PMatrix<FRealDouble, 3, 3> ToMatrix() const`
- L301 _public function_ `inline bool ToAxisAndAngleSafe(TVector<FRealDouble, 3>& OutAxis, FRealDouble& OutAngle, const TVector<FRealDouble, 3>& DefaultAxis, FRealDouble EpsilionSq = 1e-6f) const` — Extract the axis and angle from the Quaternion. @param OutAxis The axis of rotation. @param OutAngle The angle of rotation about the axis (radians). @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L317 _public function_ `inline bool GetRotationAxisSafe(TVector<FRealDouble, 3>& OutAxis, const TVector<FRealDouble, 3>& DefaultAxis, FRealDouble EpsilionSq = 1e-6f) const` — Extract the axis from the Quaternion. @param OutAxis The axis of rotation. @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L337 _public function_ `inline void ToMatrixAxes(TVector<FRealDouble, 3>& OutX, TVector<FRealDouble, 3>& OutY, TVector<FRealDouble, 3>& OutZ)` — Convert to a matrix and return as the 3 matrix axes.
- L362 _public function_ `FORCEINLINE FRealDouble GetAbsMax() const` — @brief Return the large absolute element value
- L370 _public function_ `static inline FRealDouble DotProduct(const TRotation<FRealDouble, 3>& L, const TRotation<FRealDouble, 3>& R)` — @brief Return the dot product of two quaternions
- L378 _public prototype_ `static TRotation<FRealDouble, 3> Conjugate(const ::Chaos::TRotation<FRealDouble, 3>& InR);` — Return the complex conjugate of the rotation
- L383 _public prototype_ `static TRotation<FRealDouble, 3> Negate(const ::Chaos::TRotation<FRealDouble, 3>& InR);` — Negate all values of the quaternion (note: not the inverse rotation. See Conjugate)
- L388 _public function_ `static inline TRotation<FRealDouble, 3> FromIdentity()` — Create an identity rotation
- L396 _public function_ `static inline TRotation<FRealDouble, 3> FromElements(const FRealDouble X, const FRealDouble Y, const FRealDouble Z, const FRealDouble W)` — Create a rotation by explicitly specifying all elements
- L405 _public function_ `static inline TRotation<FRealDouble, 3> FromElements(const ::Chaos::TVector<FRealDouble, 3>& V, const FRealDouble W)` — Create a rotation by explicitly specifying all elements
- L413 _public function_ `static inline TRotation<FRealDouble, 3> FromAxisAngle(const ::Chaos::TVector<FRealDouble, 3>& Axis, const FRealDouble AngleRad)` — Create a rotation about an axis by an angle specified in radians
- L421 _public prototype_ `static TRotation<FRealDouble, 3> FromVector(const ::Chaos::TVector<FRealDouble, 3>& V);` — Create a rotation about an axis V/|V| by angle |V| in radians
- L426 _public prototype_ `static TRotation<FRealDouble, 3> FromRotatedVector( const ::Chaos::TVector<FRealDouble, 3>& InitialVector, const ::Chaos::TVector<FRealDouble, 3>& FinalVector);` — Generate a Rotation that would rotate vector InitialVector to FinalVector
- L435 _public prototype_ `static TVector<FRealDouble, 3> CalculateAngularVelocity1(const TRotation<FRealDouble, 3>& R0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L442 _public prototype_ `static TVector<FRealDouble, 3> CalculateAngularVelocity2(const TRotation<FRealDouble, 3>& R0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the Quaternion to Axis/Angle method.
- L449 _public function_ `static inline TVector<FRealDouble, 3> CalculateAngularVelocity(const TRotation<FRealDouble, 3>& InR0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt)` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L459 _public function_ `static inline TVector<FRealDouble, 3> CalculateAngularDelta(const TRotation<FRealDouble, 3>& InR0, const TRotation<FRealDouble, 3>& InR1)` — Calculate the axis-angle delta (angular velocity * dt) required to take an object with orientation R0 to orientation R1. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L469 _public prototype_ `static TRotation<FRealDouble, 3> IntegrateRotationWithAngularVelocity(const TRotation<FRealDouble, 3>& InR0, const TVector<FRealDouble, 3>& InW, const FRealDouble InDt);` — Return a new rotation equal to the input rotation with angular velocity W applied over time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L476 _public function_ `static inline bool IsNearlyEqual(const TRotation<FRealDouble, 3>& A, const TRotation<FRealDouble, 3>& B, const FRealDouble Epsilon)` — Check that two rotations are approximately equal. Assumes the quaternions are normalized and in the same hemisphere. For small values of Epsilon, this is approximately equivalent to checking that the rotations are within 2*Epsilon radians of each other.

#### class `Chaos::TRotation`  
`template<> class TRotation<FRealDouble, 3> : public UE::Math::TQuat<FRealDouble>`  
_L267-483_
- inherits: `UE::Math::TQuat<FRealDouble>`
- L43 _private function_ `TRotation()`
- L44 _private prototype_ `~TRotation() = default;`
- L50 _private typedef_ `using BaseQuat = UE::Math::TQuat<FRealSingle>;`
- L52 _public function_ `TRotation() : BaseQuat()`
- L54 _public function_ `TRotation(const BaseQuat& Quat) : BaseQuat(Quat)`
- L56 _public function_ `TRotation(const FMatrix44f& Matrix) : BaseQuat(Matrix)`
- L58 _public function_ `TRotation(const FMatrix44d& Matrix) : BaseQuat(FMatrix44f(Matrix))`
- L61 _public function_ `template<typename OtherType> TRotation(const UE::Math::TQuat<OtherType>& Other) : BaseQuat((FRealSingle)Other.X, (FRealSingle)Other.Y, (FRealSingle)Other.Z, (FRealSingle)Other.W)`
- L64 _public function_ `inline PMatrix<FRealSingle, 3, 3> ToMatrix() const`
- L82 _public function_ `inline bool ToAxisAndAngleSafe(TVector<FRealSingle, 3>& OutAxis, FRealSingle& OutAngle, const TVector<FRealSingle, 3>& DefaultAxis, FRealSingle EpsilionSq = 1e-6f) const` — Extract the axis and angle from the Quaternion. @param OutAxis The axis of rotation. @param OutAngle The angle of rotation about the axis (radians). @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L98 _public function_ `inline bool GetRotationAxisSafe(TVector<FRealSingle, 3>& OutAxis, const TVector<FRealSingle, 3>& DefaultAxis, FRealSingle EpsilionSq = 1e-6f) const` — Extract the axis from the Quaternion. @param OutAxis The axis of rotation. @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L118 _public function_ `inline void ToMatrixAxes(TVector<FRealSingle, 3>& OutX, TVector<FRealSingle, 3>& OutY, TVector<FRealSingle, 3>& OutZ)` — Convert to a matrix and return as the 3 matrix axes.
- L134 _public function_ `inline void ToSwingTwistX(BaseQuat& OutSwing, BaseQuat& OutTwist) const` — Extract the Swing and Twist rotations, assuming that the Twist Axis is (1,0,0). /see ToSwingTwist
- L143 _public function_ `FORCEINLINE FRealSingle GetAbsMax() const` — @brief Return the large absolute element value
- L151 _public function_ `static inline FRealSingle DotProduct(const TRotation<FRealSingle, 3>& L, const TRotation<FRealSingle, 3>& R)` — @brief Return the dot product of two quaternions
- L159 _public prototype_ `static TRotation<FRealSingle, 3> Conjugate(const ::Chaos::TRotation<FRealSingle, 3>& InR);` — Return the complex conjugate of the rotation
- L164 _public prototype_ `static TRotation<FRealSingle, 3> Negate(const ::Chaos::TRotation<FRealSingle, 3>& InR);` — Negate all values of the quaternion (note: not the inverse rotation. See Conjugate)
- L169 _public function_ `static inline TRotation<FRealSingle, 3> FromIdentity()` — Create an identity rotation
- L177 _public function_ `static inline TRotation<FRealSingle, 3> FromElements(const FRealSingle X, const FRealSingle Y, const FRealSingle Z, const FRealSingle W)` — Create a rotation by explicitly specifying all elements
- L186 _public function_ `static inline TRotation<FRealSingle, 3> FromElements(const ::Chaos::TVector<FRealSingle, 3>& V, const FRealSingle W)` — Create a rotation by explicitly specifying all elements
- L194 _public function_ `static inline TRotation<FRealSingle, 3> FromAxisAngle(const ::Chaos::TVector<FRealSingle, 3>& Axis, const FRealSingle AngleRad)` — Create a rotation about an axis by an angle specified in radians
- L202 _public prototype_ `static TRotation<FRealSingle, 3> FromVector(const ::Chaos::TVector<FRealSingle, 3>& V);` — Create a rotation about an axis V/|V| by angle |V| in radians
- L207 _public prototype_ `static TRotation<FRealSingle, 3> FromRotatedVector( const ::Chaos::TVector<FRealSingle, 3>& InitialVector, const ::Chaos::TVector<FRealSingle, 3>& FinalVector);` — Generate a Rotation that would rotate vector InitialVector to FinalVector
- L216 _public prototype_ `static TVector<FRealSingle, 3> CalculateAngularVelocity1(const TRotation<FRealSingle, 3>& R0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L223 _public prototype_ `static TVector<FRealSingle, 3> CalculateAngularVelocity2(const TRotation<FRealSingle, 3>& R0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the Quaternion to Axis/Angle method.
- L230 _public function_ `static inline TVector<FRealSingle, 3> CalculateAngularVelocity(const TRotation<FRealSingle, 3>& InR0, const TRotation<FRealSingle, 3>& InR1, const FRealSingle InDt)` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L240 _public function_ `static inline TVector<FRealSingle, 3> CalculateAngularDelta(const TRotation<FRealSingle, 3>& InR0, const TRotation<FRealSingle, 3>& InR1)` — Calculate the axis-angle delta (angular velocity * dt) required to take an object with orientation R0 to orientation R1. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L250 _public prototype_ `static TRotation<FRealSingle, 3> IntegrateRotationWithAngularVelocity(const TRotation<FRealSingle, 3>& InR0, const TVector<FRealSingle, 3>& InW, const FRealSingle InDt);` — Return a new rotation equal to the input rotation with angular velocity W applied over time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L257 _public function_ `static inline bool IsNearlyEqual(const TRotation<FRealSingle, 3>& A, const TRotation<FRealSingle, 3>& B, const FRealSingle Epsilon)` — Check that two rotations are approximately equal. Assumes the quaternions are normalized and in the same hemisphere. For small values of Epsilon, this is approximately equivalent to checking that the rotations are within 2*Epsilon radians of each other.
- L269 _private typedef_ `using BaseQuat = UE::Math::TQuat<FRealDouble>;`
- L275 _public function_ `TRotation(const FMatrix44d& Matrix) : BaseQuat(Matrix)`
- L277 _public function_ `TRotation(const FMatrix44f& Matrix) : BaseQuat(FMatrix44d(Matrix))`
- L280 _public function_ `template<typename OtherType> TRotation(const UE::Math::TQuat<OtherType>& Other) : BaseQuat((FRealDouble)Other.X, (FRealDouble)Other.Y, (FRealDouble)Other.Z, (FRealDouble)Other.W)`
- L283 _public function_ `inline PMatrix<FRealDouble, 3, 3> ToMatrix() const`
- L301 _public function_ `inline bool ToAxisAndAngleSafe(TVector<FRealDouble, 3>& OutAxis, FRealDouble& OutAngle, const TVector<FRealDouble, 3>& DefaultAxis, FRealDouble EpsilionSq = 1e-6f) const` — Extract the axis and angle from the Quaternion. @param OutAxis The axis of rotation. @param OutAngle The angle of rotation about the axis (radians). @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L317 _public function_ `inline bool GetRotationAxisSafe(TVector<FRealDouble, 3>& OutAxis, const TVector<FRealDouble, 3>& DefaultAxis, FRealDouble EpsilionSq = 1e-6f) const` — Extract the axis from the Quaternion. @param OutAxis The axis of rotation. @param DefaultAxis The axis to set when the angle is too small to accurately calculate the axis. @param EpsilonSq The squared tolerance used to check for small angles. @return Whether the axis was successfully calculated (true except for very small angles around or less than Epsilon). @warning The axis calculation cannot succeed for small angles due to numerical error. In this case, the function will return false, but set the axis to DefaultAxis. @note EpsilonSq is approximately the square of the angle below which we cannot calculate the axis. It needs to be "much greater" than square of the error in the quaternion values which is usually ~1e-4, so values around 1e-3^2 = 1e-6 or greater are about right.
- L337 _public function_ `inline void ToMatrixAxes(TVector<FRealDouble, 3>& OutX, TVector<FRealDouble, 3>& OutY, TVector<FRealDouble, 3>& OutZ)` — Convert to a matrix and return as the 3 matrix axes.
- L362 _public function_ `FORCEINLINE FRealDouble GetAbsMax() const` — @brief Return the large absolute element value
- L370 _public function_ `static inline FRealDouble DotProduct(const TRotation<FRealDouble, 3>& L, const TRotation<FRealDouble, 3>& R)` — @brief Return the dot product of two quaternions
- L378 _public prototype_ `static TRotation<FRealDouble, 3> Conjugate(const ::Chaos::TRotation<FRealDouble, 3>& InR);` — Return the complex conjugate of the rotation
- L383 _public prototype_ `static TRotation<FRealDouble, 3> Negate(const ::Chaos::TRotation<FRealDouble, 3>& InR);` — Negate all values of the quaternion (note: not the inverse rotation. See Conjugate)
- L388 _public function_ `static inline TRotation<FRealDouble, 3> FromIdentity()` — Create an identity rotation
- L396 _public function_ `static inline TRotation<FRealDouble, 3> FromElements(const FRealDouble X, const FRealDouble Y, const FRealDouble Z, const FRealDouble W)` — Create a rotation by explicitly specifying all elements
- L405 _public function_ `static inline TRotation<FRealDouble, 3> FromElements(const ::Chaos::TVector<FRealDouble, 3>& V, const FRealDouble W)` — Create a rotation by explicitly specifying all elements
- L413 _public function_ `static inline TRotation<FRealDouble, 3> FromAxisAngle(const ::Chaos::TVector<FRealDouble, 3>& Axis, const FRealDouble AngleRad)` — Create a rotation about an axis by an angle specified in radians
- L421 _public prototype_ `static TRotation<FRealDouble, 3> FromVector(const ::Chaos::TVector<FRealDouble, 3>& V);` — Create a rotation about an axis V/|V| by angle |V| in radians
- L426 _public prototype_ `static TRotation<FRealDouble, 3> FromRotatedVector( const ::Chaos::TVector<FRealDouble, 3>& InitialVector, const ::Chaos::TVector<FRealDouble, 3>& FinalVector);` — Generate a Rotation that would rotate vector InitialVector to FinalVector
- L435 _public prototype_ `static TVector<FRealDouble, 3> CalculateAngularVelocity1(const TRotation<FRealDouble, 3>& R0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L442 _public prototype_ `static TVector<FRealDouble, 3> CalculateAngularVelocity2(const TRotation<FRealDouble, 3>& R0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt);` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. Uses the Quaternion to Axis/Angle method.
- L449 _public function_ `static inline TVector<FRealDouble, 3> CalculateAngularVelocity(const TRotation<FRealDouble, 3>& InR0, const TRotation<FRealDouble, 3>& InR1, const FRealDouble InDt)` — Calculate the angular velocity required to take an object with orientation R0 to orientation R1 in time Dt. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L459 _public function_ `static inline TVector<FRealDouble, 3> CalculateAngularDelta(const TRotation<FRealDouble, 3>& InR0, const TRotation<FRealDouble, 3>& InR1)` — Calculate the axis-angle delta (angular velocity * dt) required to take an object with orientation R0 to orientation R1. This should match the algorithm used in PerParticleUpdateFromDeltaPosition rule.
- L469 _public prototype_ `static TRotation<FRealDouble, 3> IntegrateRotationWithAngularVelocity(const TRotation<FRealDouble, 3>& InR0, const TVector<FRealDouble, 3>& InW, const FRealDouble InDt);` — Return a new rotation equal to the input rotation with angular velocity W applied over time Dt. Uses the relation: DQ/DT = (W * Q)/2
- L476 _public function_ `static inline bool IsNearlyEqual(const TRotation<FRealDouble, 3>& A, const TRotation<FRealDouble, 3>& B, const FRealDouble Epsilon)` — Check that two rotations are approximately equal. Assumes the quaternions are normalized and in the same hemisphere. For small values of Epsilon, this is approximately equivalent to checking that the rotations are within 2*Epsilon radians of each other.

#### Free symbols / members of external scopes

- L34 _typedef_ `using FQuat = _FQuat;` — Work around include tool not understanding that this won't be compiled alongside MathFwd.h
- L37 _namespace_ `namespace Chaos`
- L179 _typedef_ `using FQuatReal = BaseQuat::FReal;` (scope `Chaos::TRotation::FromElements`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Simd4.h` (Public)


#### union `Chaos::Private::SimdGreaterEqual::(anonymous)`  
`union`  
_L205-205_

#### union `Chaos::Private::SimdGreater::(anonymous)`  
`union`  
_L230-230_

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace Private` (scope `Chaos`)
- L19 _typedef_ `using FSimd4Realf = TSimdRealf<4>;` (scope `Chaos::Private`)
- L20 _typedef_ `using FSimd4Vec3f = TSimdVec3f<4>;` (scope `Chaos::Private`)
- L21 _typedef_ `using FSimd4Int32 = TSimdInt32<4>;` (scope `Chaos::Private`)
- L22 _typedef_ `using FSimd4Selector = TSimdSelector<4>;` (scope `Chaos::Private`)
- L31 _function_ `template<> FORCEINLINE TSimdSelector<4> TSimdSelector<4>::True()` (scope `Chaos::Private::TSimdSelector`)
- L39 _function_ `template<> FORCEINLINE TSimdSelector<4> TSimdSelector<4>::False()` (scope `Chaos::Private::TSimdSelector`)
- L47 _function_ `template<> FORCEINLINE TSimdInt32<4> TSimdInt32<4>::Make(const int32 I)` (scope `Chaos::Private::TSimdInt32`)
- L55 _function_ `template<> FORCEINLINE TSimdInt32<4> TSimdInt32<4>::Zero()` (scope `Chaos::Private::TSimdInt32`)
- L63 _function_ `template<> FORCEINLINE TSimdRealf<4> TSimdRealf<4>::Make(const float F)` (scope `Chaos::Private::TSimdRealf`)
- L71 _function_ `template<> FORCEINLINE TSimdRealf<4> TSimdRealf<4>::Zero()` (scope `Chaos::Private::TSimdRealf`)
- L79 _function_ `template<> FORCEINLINE TSimdRealf<4> TSimdRealf<4>::One()` (scope `Chaos::Private::TSimdRealf`)
- L129 _function_ `FORCEINLINE bool SimdAnyTrue(const FSimd4Selector& InL)` (scope `Chaos::Private`)
- L135 _function_ `FORCEINLINE bool SimdAllTrue(const FSimd4Selector& InL)` (scope `Chaos::Private`)
- L141 _function_ `FORCEINLINE FSimd4Selector SimdNot(const FSimd4Selector& InL)` (scope `Chaos::Private`)
- L152 _function_ `FORCEINLINE FSimd4Selector SimdOr(const FSimd4Selector& InL, const FSimd4Selector& InR)` (scope `Chaos::Private`)
- L164 _function_ `FORCEINLINE FSimd4Selector SimdAnd(const FSimd4Selector& InL, const FSimd4Selector& InR)` (scope `Chaos::Private`)
- L176 _function_ `FORCEINLINE FSimd4Selector SimdEqual(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L188 _function_ `FORCEINLINE FSimd4Selector SimdNotEqual(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L200 _function_ `FORCEINLINE FSimd4Selector SimdGreaterEqual(const FSimd4Int32& InL, const FSimd4Int32& InR)` (scope `Chaos::Private`)
- L205 _member_ `union { VectorRegister4Float V; VectorRegister4Int I; } Mask;` (scope `Chaos::Private::SimdGreaterEqual::__anonabb53f6e010a`)
- L205 _member_ `union { VectorRegister4Float V; VectorRegister4Int I; } Mask;` (scope `Chaos::Private::SimdGreaterEqual::__anonabb53f6e010a`)
- L213 _function_ `FORCEINLINE FSimd4Selector SimdGreaterEqual(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L225 _function_ `FORCEINLINE FSimd4Selector SimdGreater(const FSimd4Int32& InL, const FSimd4Int32& InR)` (scope `Chaos::Private`)
- L230 _member_ `union { VectorRegister4Float V; VectorRegister4Int I; } Mask;` (scope `Chaos::Private::SimdGreater::__anonabb53f6e020a`)
- L230 _member_ `union { VectorRegister4Float V; VectorRegister4Int I; } Mask;` (scope `Chaos::Private::SimdGreater::__anonabb53f6e020a`)
- L238 _function_ `FORCEINLINE FSimd4Selector SimdGreater(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L250 _function_ `FORCEINLINE FSimd4Selector SimdLess(const FSimd4Int32& InL, const FSimd4Int32& InR)` (scope `Chaos::Private`)
- L262 _function_ `FORCEINLINE FSimd4Selector SimdLess(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L274 _function_ `FORCEINLINE FSimd4Realf SimdSelect(const FSimd4Selector& InSelector, const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L293 _function_ `FORCEINLINE FSimd4Realf SimdNegate(const FSimd4Realf& InL)` (scope `Chaos::Private`)
- L304 _function_ `FORCEINLINE FSimd4Realf SimdAdd(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L316 _function_ `FORCEINLINE FSimd4Vec3f SimdAdd(const FSimd4Vec3f& L, const FSimd4Vec3f& R)` (scope `Chaos::Private`)
- L333 _function_ `FORCEINLINE FSimd4Realf SimdSubtract(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L345 _function_ `FORCEINLINE FSimd4Vec3f SimdSubtract(const FSimd4Vec3f& L, const FSimd4Vec3f& R)` (scope `Chaos::Private`)
- L362 _function_ `FORCEINLINE FSimd4Realf SimdMultiply(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L374 _function_ `FORCEINLINE FSimd4Vec3f SimdMultiply(const FSimd4Vec3f& L, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L388 _function_ `FORCEINLINE FSimd4Vec3f SimdMultiply(const FSimd4Realf& L, const FSimd4Vec3f& R)` (scope `Chaos::Private`)
- L393 _function_ `FORCEINLINE FSimd4Vec3f SimdMultiply(const FSimd4Vec3f& L, const FSimd4Vec3f& R)` (scope `Chaos::Private`)
- L410 _function_ `FORCEINLINE FSimd4Vec3f SimdMultiplyAdd(const FSimd4Vec3f& L, const FSimd4Vec3f& R, const FSimd4Vec3f& Acc)` (scope `Chaos::Private`)
- L431 _function_ `FORCEINLINE FSimd4Realf SimdDivide(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L443 _function_ `FORCEINLINE FSimd4Vec3f SimdCrossProduct(const FSimd4Vec3f& L, const FSimd4Vec3f& R)` (scope `Chaos::Private`)
- L460 _function_ `FORCEINLINE FSimd4Realf SimdDotProduct(const FSimd4Vec3f& L, const FSimd4Vec3f& R)` (scope `Chaos::Private`)
- L479 _function_ `FORCEINLINE FSimd4Realf SimdSquare(const FSimd4Realf& InV)` (scope `Chaos::Private`)
- L490 _function_ `FORCEINLINE FSimd4Realf SimdSqrt(const FSimd4Realf& InV)` (scope `Chaos::Private`)
- L501 _function_ `FORCEINLINE FSimd4Realf SimdInvSqrt(const FSimd4Realf& InV)` (scope `Chaos::Private`)
- L512 _function_ `FORCEINLINE FSimd4Realf SimdMin(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L524 _function_ `FORCEINLINE FSimd4Realf SimdMax(const FSimd4Realf& InL, const FSimd4Realf& InR)` (scope `Chaos::Private`)
- L544 _function_ `FORCEINLINE FSimd4Vec3f SimdGatherAligned(const FVec3f& InA, const FVec3f& InB, const FVec3f& InC, const FVec3f& InD)` (scope `Chaos::Private`) — Convert 4 row-vectors into 3 column-vectors NOTE: The input vectors must be 16-byte aligned and padded to 16 bytes to avoid reading past valid memory

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/SimdTypes.h` (Public)


#### struct `Chaos::Private::TSimdSelector`  
`template<int TNumLanes> struct TSimdSelector`  
_L74-91_
- desc: The result of Simd comparison operations and used in SimdSelect. // Replace any non-positive values in R0 with the value from R1 FSim4Selector IsR0GreaterThanZero = SimdGreater(R0, FSimd4Realf::Zero()); R0 = SimdSelect(IsV0GreaterThanZero, R0, R1);
- L76 _public member_ `alignas(SimdAlignment) float V[TNumLanes];`
- L78 _public function_ `FORCEINLINE void SetValue(const int LaneIndex, bool B)`
- L83 _public function_ `FORCEINLINE bool GetValue(const int LaneIndex) const`
- L89 _public prototype_ `static TSimdSelector<TNumLanes> True();`
- L90 _public prototype_ `static TSimdSelector<TNumLanes> False();`

#### struct `Chaos::Private::TSimdValue`  
`template<typename T, int TNumLanes> struct TSimdValue`  
_L98-120_
- desc: Used to store any value type in a TNumLanes-wide set. This is used primarily whenyou have non-numeric data that varies per lane. E.g., a pointer to some per-lane shared data.
- L100 _public typedef_ `using ValueType = T;`
- L101 _public member_ `alignas(SimdAlignment) ValueType V[TNumLanes];`
- L103 _public function_ `FORCEINLINE void SetValue(const int32 LaneIndex, const ValueType F)`
- L108 _public function_ `FORCEINLINE ValueType GetValue(const int32 LaneIndex) const`
- L113 _public function_ `FORCEINLINE void SetValues(const ValueType F)`

#### struct `Chaos::Private::TSimdInt32`  
`template<int TNumLanes> struct TSimdInt32`  
_L126-161_
- desc: A TNumLanes-wide set of integers.
- L128 _public member_ `alignas(SimdAlignment) int32 V[TNumLanes];`
- L130 _public function_ `FORCEINLINE TSimdInt32()`
- L134 _public function_ `FORCEINLINE void SetValue(const int32 LaneIndex, const int32 I)`
- L139 _public function_ `FORCEINLINE int32 GetValue(const int32 LaneIndex) const`
- L144 _public function_ `FORCEINLINE void SetValues(const int32 I)`
- L149 _public function_ `FORCEINLINE int32 GetMaxValue() const`
- L159 _public prototype_ `static TSimdInt32<TNumLanes> Make(const int32 I);`
- L160 _public prototype_ `static TSimdInt32<TNumLanes> Zero();`

#### struct `Chaos::Private::TSimdRealf`  
`template<int TNumLanes> struct TSimdRealf`  
_L167-193_
- desc: A TNumLanes-wide set of single-precision floats.
- L169 _public member_ `alignas(SimdAlignment) float V[TNumLanes];`
- L171 _public function_ `FORCEINLINE TSimdRealf()`
- L175 _public function_ `FORCEINLINE void SetValue(const int32 LaneIndex, const float F)`
- L180 _public function_ `FORCEINLINE float GetValue(const int32 LaneIndex) const`
- L185 _public function_ `FORCEINLINE void SetValues(const float F)`
- L190 _public prototype_ `static TSimdRealf Make(const float F);`
- L191 _public prototype_ `static TSimdRealf Zero();`
- L192 _public prototype_ `static TSimdRealf One();`

#### struct `Chaos::Private::TSimdVec3f`  
`template<int TNumLanes> struct TSimdVec3f`  
_L203-260_
- desc: A TNumLanes-wide set of floating point 3-vectors. The vector elements are stored as 3 vectors of Xs, Ys and Zs. FSimd4Vec3f C = SimdCrossProduct(A, B);
- L207 _public member_ `alignas(SimdAlignment) float VX[TNumLanes];`
- L208 _public member_ `alignas(SimdAlignment) float VY[TNumLanes];`
- L209 _public member_ `alignas(SimdAlignment) float VZ[TNumLanes];`
- L211 _public function_ `FORCEINLINE TSimdVec3f()`
- L215 _public function_ `FORCEINLINE TSimdVec3f(const FVec3f& V)`
- L220 _public function_ `FORCEINLINE void SetValue(const int32 LaneIndex, const FVec3f& V)`
- L227 _public function_ `FORCEINLINE FVec3f GetValue(const int32 LaneIndex) const`
- L232 _public function_ `FORCEINLINE void SetValues(const FVec3f& V)`
- L237 _public function_ `FORCEINLINE static TSimdVec3f Make(const FVec3f& V)`
- L247 _public function_ `FORCEINLINE static TSimdVec3f Make(const FVec3f& V0, const FVec3f& V1, const FVec3f& V2, const FVec3f& V3)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace Private` (scope `Chaos`)
- L18 _variable_ `static const int SimdAlignment = 16;` (scope `Chaos::Private`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Sweeps.h` (Public)


#### enum `Chaos::Sweeps::ESweepFlags`  
`enum class ESweepFlags`  
_L8-12_
- L10 _public enumerator_ `None = 0`
- L11 _public enumerator_ `MTD = (1 << 9)`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`
- L6 _namespace_ `namespace Sweeps` (scope `Chaos`)
- L13 _prototype_ `ENUM_CLASS_FLAGS(ESweepFlags);` (scope `Chaos::Sweeps`)
- L15 _prototype_ `bool SweepSphereVsSphere(const FVec3& SweepStart, const FVec3& SweepDir, const FReal SweepLength, const FReal Sphere0Radius, const FVec3& Sphere1Center, const FReal Sphere1Radius, const ESweepFlags Flags, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal);` (scope `Chaos::Sweeps`)
- L17 _prototype_ `bool SweepSphereVsAabb(const FVec3& SweepStart, const FVec3& SweepDir, const FReal SweepLength, const FReal SphereRadius, const FVec3& AabbMin, const FVec3& AabbMax, const ESweepFlags Flags, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal, int32& OutFaceIndex);` (scope `Chaos::Sweeps`)
- L19 _prototype_ `bool SweepSphereVsCapsule(const FVec3& SweepStart, const FVec3& SweepDir, const FReal SweepLength, const FReal SphereRadius, const FReal CapsuleRadius, const FReal CapsuleHeight, const FVec3& CapsuleAxis, const FVec3& CapsuleX1, const FVec3& CapsuleX2, const ESweepFlags Flags, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal);` (scope `Chaos::Sweeps`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/SweepsMTD.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`
- L6 _namespace_ `namespace Sweeps` (scope `Chaos`)
- L8 _prototype_ `void SphereSphereMTD(const FVec3& Sphere0Center, const FReal Sphere0Radius, const FVec3& Sphere1Center, const FReal Sphere1Radius, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal);` (scope `Chaos::Sweeps`)
- L10 _prototype_ `void AabbSphereMTD(const FVec3& AabbMin, const FVec3& AabbMax, const FVec3& SphereCenter, const FReal SphereRadius, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal);` (scope `Chaos::Sweeps`)
- L12 _prototype_ `void CapsuleSphereMTD(const FVec3& CapsuleX1, const FVec3& CapsuleX2, const FReal CapsuleRadius, const FVec3& SphereCenter, const FReal SphereRadius, FReal& OutTime, FVec3& OutPosition, FVec3& OutNormal);` (scope `Chaos::Sweeps`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Transform.h` (Public)


#### struct `_FTransform`  
`struct _FTransform`  
_L13-107_
- desc: TODO(mlentine): If we use this class in engine we need to make it more efficient.
- L16 _public function_ `_FTransform()`
- L17 _public function_ `_FTransform(const Chaos::TRotation<Chaos::FReal, 3>& Rotation, const Chaos::TVector<Chaos::FReal, 3>& Translation) : MRotation(Rotation), MTranslation(Translation)`
- L21 _public function_ `_FTransform(const FMatrix& Matrix)`
- L41 _public function_ `_FTransform(const _FTransform& Transform) : MRotation(Transform.MRotation), MTranslation(Transform.MTranslation)`
- L45 _public function_ `Chaos::TVector<Chaos::FReal, 3> InverseTransformPosition(const Chaos::TVector<Chaos::FReal, 3>& Position)`
- L51 _public function_ `Chaos::TVector<Chaos::FReal, 3> TransformVector(const Chaos::TVector<Chaos::FReal, 3>& Vector)`
- L57 _public function_ `Chaos::TVector<Chaos::FReal, 3> InverseTransformVector(const Chaos::TVector<Chaos::FReal, 3>& Vector)`
- L63 _public function_ `Chaos::TVector<float, 3> InverseTransformVector(const Chaos::TVector<float, 3>& Vector)`
- L69 _public function_ `Chaos::PMatrix<Chaos::FReal, 3, 3> ToRotationMatrix()`
- L84 _public function_ `Chaos::PMatrix<Chaos::FReal, 4, 4> ToMatrix()`
- L93 _public function_ `Chaos::PMatrix<Chaos::FReal, 4, 4> ToInverseMatrix()`
- L105 _private member_ `Chaos::TRotation<Chaos::FReal, 3> MRotation;`
- L106 _private member_ `Chaos::TVector<Chaos::FReal, 3> MTranslation;`

#### class `Chaos::TRigidTransform`  
`template<class T, int d> class TRigidTransform`  
_L114-119_
- L117 _private function_ `TRigidTransform()`
- L118 _private prototype_ `~TRigidTransform() = default;`
- L124 _private typedef_ `using BaseTransform = UE::Math::TTransform<FReal>;`
- L126 _public function_ `TRigidTransform() : BaseTransform()`
- L128 _public function_ `TRigidTransform(const TVector<FReal, 3>& Translation, const TRotation<FReal, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L130 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(Matrix)`
- L132 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix(Matrix))`
- L134 _public function_ `TRigidTransform(const BaseTransform& Transform) : BaseTransform(Transform)`
- L136 _public function_ `TRigidTransform<FReal, 2> Inverse() const`
- L141 _public function_ `inline TRigidTransform<FReal, 2> operator*(const TRigidTransform<FReal, 2>& Other) const`
- L150 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealSingle>;`
- L154 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L156 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation, const TVector<FRealSingle, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L158 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(Matrix)`
- L160 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(FMatrix44f(Matrix))`
- L162 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Float1110)`
- L167 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealSingle, 3>(Other.GetRotation()), TVector<FRealSingle, 3>(Other.GetTranslation()))`
- L170 _public function_ `TRigidTransform<FRealSingle, 3> Inverse() const`
- L175 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixWithScale() const`
- L180 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixNoScale() const`
- L185 _public prototype_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Matrix) const;`
- L187 _public function_ `inline TRigidTransform<FRealSingle, 3> operator*(const TRigidTransform<FRealSingle, 3>& Other) const`
- L193 _public function_ `TRigidTransform<FRealSingle, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealSingle, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L222 _public function_ `TVector<FRealSingle, 3> TransformNormalNoScale(const TVector<FRealSingle, 3>& Normal) const`
- L228 _public function_ `TVector<FRealSingle, 3> TransformNormalUnsafe(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L243 _public function_ `TVector<FRealSingle, 3> TransformNormal(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L266 _public function_ `static TRigidTransform<FRealSingle, 3> MultiplyNoScale(const TRigidTransform<FRealSingle, 3>& A, const TRigidTransform<FRealSingle, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale
- L301 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealDouble>;`
- L305 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L307 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation, const TVector<FRealDouble, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L311 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix44d(Matrix))`
- L313 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Double1110)`
- L318 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealDouble, 3>(Other.GetRotation()), TVector<FRealDouble, 3>(Other.GetTranslation()))`
- L321 _public function_ `TRigidTransform<FRealDouble, 3> Inverse() const`
- L326 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixWithScale() const`
- L331 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixNoScale() const`
- L336 _public prototype_ `PMatrix<FRealDouble, 4, 4> operator*(const Chaos::PMatrix<FRealDouble, 4, 4>& Matrix) const;`
- L338 _public function_ `inline TRigidTransform<FRealDouble, 3> operator*(const TRigidTransform<FRealDouble, 3>& Other) const`
- L344 _public function_ `TRigidTransform<FRealDouble, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealDouble, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L373 _public function_ `TVector<FRealDouble, 3> TransformNormalNoScale(const TVector<FRealDouble, 3>& Normal) const`
- L379 _public function_ `TVector<FRealDouble, 3> TransformNormalUnsafe(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L394 _public function_ `TVector<FRealDouble, 3> TransformNormal(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L417 _public function_ `static TRigidTransform<FRealDouble, 3> MultiplyNoScale(const TRigidTransform<FRealDouble, 3>& A, const TRigidTransform<FRealDouble, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale

#### class `Chaos::TRigidTransform`  
`template<> class TRigidTransform<FReal, 2> : public UE::Math::TTransform<FReal>`  
_L122-145_
- inherits: `UE::Math::TTransform<FReal>`
- L117 _private function_ `TRigidTransform()`
- L118 _private prototype_ `~TRigidTransform() = default;`
- L124 _private typedef_ `using BaseTransform = UE::Math::TTransform<FReal>;`
- L126 _public function_ `TRigidTransform() : BaseTransform()`
- L128 _public function_ `TRigidTransform(const TVector<FReal, 3>& Translation, const TRotation<FReal, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L130 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(Matrix)`
- L132 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix(Matrix))`
- L134 _public function_ `TRigidTransform(const BaseTransform& Transform) : BaseTransform(Transform)`
- L136 _public function_ `TRigidTransform<FReal, 2> Inverse() const`
- L141 _public function_ `inline TRigidTransform<FReal, 2> operator*(const TRigidTransform<FReal, 2>& Other) const`
- L150 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealSingle>;`
- L154 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L156 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation, const TVector<FRealSingle, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L158 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(Matrix)`
- L160 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(FMatrix44f(Matrix))`
- L162 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Float1110)`
- L167 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealSingle, 3>(Other.GetRotation()), TVector<FRealSingle, 3>(Other.GetTranslation()))`
- L170 _public function_ `TRigidTransform<FRealSingle, 3> Inverse() const`
- L175 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixWithScale() const`
- L180 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixNoScale() const`
- L185 _public prototype_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Matrix) const;`
- L187 _public function_ `inline TRigidTransform<FRealSingle, 3> operator*(const TRigidTransform<FRealSingle, 3>& Other) const`
- L193 _public function_ `TRigidTransform<FRealSingle, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealSingle, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L222 _public function_ `TVector<FRealSingle, 3> TransformNormalNoScale(const TVector<FRealSingle, 3>& Normal) const`
- L228 _public function_ `TVector<FRealSingle, 3> TransformNormalUnsafe(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L243 _public function_ `TVector<FRealSingle, 3> TransformNormal(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L266 _public function_ `static TRigidTransform<FRealSingle, 3> MultiplyNoScale(const TRigidTransform<FRealSingle, 3>& A, const TRigidTransform<FRealSingle, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale
- L301 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealDouble>;`
- L305 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L307 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation, const TVector<FRealDouble, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L311 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix44d(Matrix))`
- L313 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Double1110)`
- L318 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealDouble, 3>(Other.GetRotation()), TVector<FRealDouble, 3>(Other.GetTranslation()))`
- L321 _public function_ `TRigidTransform<FRealDouble, 3> Inverse() const`
- L326 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixWithScale() const`
- L331 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixNoScale() const`
- L336 _public prototype_ `PMatrix<FRealDouble, 4, 4> operator*(const Chaos::PMatrix<FRealDouble, 4, 4>& Matrix) const;`
- L338 _public function_ `inline TRigidTransform<FRealDouble, 3> operator*(const TRigidTransform<FRealDouble, 3>& Other) const`
- L344 _public function_ `TRigidTransform<FRealDouble, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealDouble, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L373 _public function_ `TVector<FRealDouble, 3> TransformNormalNoScale(const TVector<FRealDouble, 3>& Normal) const`
- L379 _public function_ `TVector<FRealDouble, 3> TransformNormalUnsafe(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L394 _public function_ `TVector<FRealDouble, 3> TransformNormal(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L417 _public function_ `static TRigidTransform<FRealDouble, 3> MultiplyNoScale(const TRigidTransform<FRealDouble, 3>& A, const TRigidTransform<FRealDouble, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale

#### class `Chaos::TRigidTransform`  
`template<> class TRigidTransform<FRealSingle, 3> : public UE::Math::TTransform<FRealSingle>`  
_L148-296_
- inherits: `UE::Math::TTransform<FRealSingle>`
- L117 _private function_ `TRigidTransform()`
- L118 _private prototype_ `~TRigidTransform() = default;`
- L124 _private typedef_ `using BaseTransform = UE::Math::TTransform<FReal>;`
- L126 _public function_ `TRigidTransform() : BaseTransform()`
- L128 _public function_ `TRigidTransform(const TVector<FReal, 3>& Translation, const TRotation<FReal, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L130 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(Matrix)`
- L132 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix(Matrix))`
- L134 _public function_ `TRigidTransform(const BaseTransform& Transform) : BaseTransform(Transform)`
- L136 _public function_ `TRigidTransform<FReal, 2> Inverse() const`
- L141 _public function_ `inline TRigidTransform<FReal, 2> operator*(const TRigidTransform<FReal, 2>& Other) const`
- L150 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealSingle>;`
- L154 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L156 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation, const TVector<FRealSingle, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L158 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(Matrix)`
- L160 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(FMatrix44f(Matrix))`
- L162 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Float1110)`
- L167 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealSingle, 3>(Other.GetRotation()), TVector<FRealSingle, 3>(Other.GetTranslation()))`
- L170 _public function_ `TRigidTransform<FRealSingle, 3> Inverse() const`
- L175 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixWithScale() const`
- L180 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixNoScale() const`
- L185 _public prototype_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Matrix) const;`
- L187 _public function_ `inline TRigidTransform<FRealSingle, 3> operator*(const TRigidTransform<FRealSingle, 3>& Other) const`
- L193 _public function_ `TRigidTransform<FRealSingle, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealSingle, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L222 _public function_ `TVector<FRealSingle, 3> TransformNormalNoScale(const TVector<FRealSingle, 3>& Normal) const`
- L228 _public function_ `TVector<FRealSingle, 3> TransformNormalUnsafe(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L243 _public function_ `TVector<FRealSingle, 3> TransformNormal(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L266 _public function_ `static TRigidTransform<FRealSingle, 3> MultiplyNoScale(const TRigidTransform<FRealSingle, 3>& A, const TRigidTransform<FRealSingle, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale
- L301 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealDouble>;`
- L305 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L307 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation, const TVector<FRealDouble, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L311 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix44d(Matrix))`
- L313 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Double1110)`
- L318 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealDouble, 3>(Other.GetRotation()), TVector<FRealDouble, 3>(Other.GetTranslation()))`
- L321 _public function_ `TRigidTransform<FRealDouble, 3> Inverse() const`
- L326 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixWithScale() const`
- L331 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixNoScale() const`
- L336 _public prototype_ `PMatrix<FRealDouble, 4, 4> operator*(const Chaos::PMatrix<FRealDouble, 4, 4>& Matrix) const;`
- L338 _public function_ `inline TRigidTransform<FRealDouble, 3> operator*(const TRigidTransform<FRealDouble, 3>& Other) const`
- L344 _public function_ `TRigidTransform<FRealDouble, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealDouble, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L373 _public function_ `TVector<FRealDouble, 3> TransformNormalNoScale(const TVector<FRealDouble, 3>& Normal) const`
- L379 _public function_ `TVector<FRealDouble, 3> TransformNormalUnsafe(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L394 _public function_ `TVector<FRealDouble, 3> TransformNormal(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L417 _public function_ `static TRigidTransform<FRealDouble, 3> MultiplyNoScale(const TRigidTransform<FRealDouble, 3>& A, const TRigidTransform<FRealDouble, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale

#### class `Chaos::TRigidTransform`  
`template<> class TRigidTransform<FRealDouble, 3> : public UE::Math::TTransform<FRealDouble>`  
_L299-447_
- inherits: `UE::Math::TTransform<FRealDouble>`
- L117 _private function_ `TRigidTransform()`
- L118 _private prototype_ `~TRigidTransform() = default;`
- L124 _private typedef_ `using BaseTransform = UE::Math::TTransform<FReal>;`
- L126 _public function_ `TRigidTransform() : BaseTransform()`
- L128 _public function_ `TRigidTransform(const TVector<FReal, 3>& Translation, const TRotation<FReal, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L130 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(Matrix)`
- L132 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix(Matrix))`
- L134 _public function_ `TRigidTransform(const BaseTransform& Transform) : BaseTransform(Transform)`
- L136 _public function_ `TRigidTransform<FReal, 2> Inverse() const`
- L141 _public function_ `inline TRigidTransform<FReal, 2> operator*(const TRigidTransform<FReal, 2>& Other) const`
- L150 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealSingle>;`
- L154 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L156 _public function_ `TRigidTransform(const TVector<FRealSingle, 3>& Translation, const TRotation<FRealSingle, 3>& Rotation, const TVector<FRealSingle, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L158 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(Matrix)`
- L160 _public function_ `TRigidTransform(const FMatrix44d& Matrix) : BaseTransform(FMatrix44f(Matrix))`
- L162 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Float1110)`
- L167 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealSingle, 3>(Other.GetRotation()), TVector<FRealSingle, 3>(Other.GetTranslation()))`
- L170 _public function_ `TRigidTransform<FRealSingle, 3> Inverse() const`
- L175 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixWithScale() const`
- L180 _public function_ `PMatrix<FRealSingle, 4, 4> ToMatrixNoScale() const`
- L185 _public prototype_ `PMatrix<FRealSingle, 4, 4> operator*(const PMatrix<FRealSingle, 4, 4>& Matrix) const;`
- L187 _public function_ `inline TRigidTransform<FRealSingle, 3> operator*(const TRigidTransform<FRealSingle, 3>& Other) const`
- L193 _public function_ `TRigidTransform<FRealSingle, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealSingle, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L222 _public function_ `TVector<FRealSingle, 3> TransformNormalNoScale(const TVector<FRealSingle, 3>& Normal) const`
- L228 _public function_ `TVector<FRealSingle, 3> TransformNormalUnsafe(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L243 _public function_ `TVector<FRealSingle, 3> TransformNormal(const TVector<FRealSingle, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L266 _public function_ `static TRigidTransform<FRealSingle, 3> MultiplyNoScale(const TRigidTransform<FRealSingle, 3>& A, const TRigidTransform<FRealSingle, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale
- L301 _private typedef_ `using BaseTransform = UE::Math::TTransform<FRealDouble>;`
- L305 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation) : BaseTransform(Rotation, Translation)`
- L307 _public function_ `TRigidTransform(const TVector<FRealDouble, 3>& Translation, const TRotation<FRealDouble, 3>& Rotation, const TVector<FRealDouble, 3>& Scale) : BaseTransform(Rotation, Translation, Scale)`
- L311 _public function_ `TRigidTransform(const FMatrix44f& Matrix) : BaseTransform(FMatrix44d(Matrix))`
- L313 _public function_ `TRigidTransform(TransformVectorRegister InRotation, TransformVectorRegister InTranslation) : BaseTransform(InRotation, InTranslation, GlobalVectorConstants::Double1110)`
- L318 _public function_ `template<typename OtherType> explicit TRigidTransform(const OtherType& Other) : BaseTransform(TRotation<FRealDouble, 3>(Other.GetRotation()), TVector<FRealDouble, 3>(Other.GetTranslation()))`
- L321 _public function_ `TRigidTransform<FRealDouble, 3> Inverse() const`
- L326 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixWithScale() const`
- L331 _public function_ `PMatrix<FRealDouble, 4, 4> ToMatrixNoScale() const`
- L336 _public prototype_ `PMatrix<FRealDouble, 4, 4> operator*(const Chaos::PMatrix<FRealDouble, 4, 4>& Matrix) const;`
- L338 _public function_ `inline TRigidTransform<FRealDouble, 3> operator*(const TRigidTransform<FRealDouble, 3>& Other) const`
- L344 _public function_ `TRigidTransform<FRealDouble, 3> GetRelativeTransformNoScale(const TRigidTransform<FRealDouble, 3>& Other) const` — Get the transform which maps from Other to This, ignoring the scale on both.
- L373 _public function_ `TVector<FRealDouble, 3> TransformNormalNoScale(const TVector<FRealDouble, 3>& Normal) const`
- L379 _public function_ `TVector<FRealDouble, 3> TransformNormalUnsafe(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary. Assumes no scale components are zero.
- L394 _public function_ `TVector<FRealDouble, 3> TransformNormal(const TVector<FRealDouble, 3>& Normal) const` — Transform the normal when scale may be non-unitary.
- L417 _public function_ `static TRigidTransform<FRealDouble, 3> MultiplyNoScale(const TRigidTransform<FRealDouble, 3>& A, const TRigidTransform<FRealDouble, 3>& B)` — @brief Equivalent to (A * B) but assuming both have unit scale

#### Free symbols / members of external scopes

- L108 _typedef_ `using FTransform = _FTransform;` — Work around include tool not understanding that this can't be compiled alongside MathFwd.h
- L111 _namespace_ `namespace Chaos`
- L292 _function_ `friend inline uint32 GetTypeHash(const TRigidTransform<FRealSingle, 3>& InTransform)` (scope `Chaos`)
- L443 _function_ `friend inline uint32 GetTypeHash(const TRigidTransform<FRealDouble, 3>& InTransform)` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector.h` (Public)


#### struct `Chaos::TVectorTraits`  
`template<class T, int d> struct TVectorTraits`  
_L34-37_
- L36 _public member_ `static const bool RequireRangeCheck = true;`

#### class `Chaos::TVector`  
`template<class T, int d> class TVector`  
_L41-381_
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### class `Chaos::TVector`  
`template<> class TVector<FReal, 4> : public UE::Math::TVector4<FReal>`  
_L386-404_
- inherits: `UE::Math::TVector4<FReal>`
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### class `Chaos::TVector`  
`template<> class TVector<FRealSingle, 3> : public UE::Math::TVector<FRealSingle>`  
_L407-612_
- inherits: `UE::Math::TVector<FRealSingle>`
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### class `Chaos::TVector`  
`template<> class TVector<FRealDouble, 3> : public UE::Math::TVector<FRealDouble>`  
_L616-820_
- inherits: `UE::Math::TVector<FRealDouble>`
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### class `Chaos::TVector`  
`template<> class TVector<FRealSingle, 2> : public FVector2f`  
_L823-908_
- inherits: `FVector2f`
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### class `Chaos::TVector`  
`template<> class TVector<FRealDouble, 2> : public FVector2d`  
_L911-996_
- inherits: `FVector2d`
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### class `Chaos::TVector`  
`template<class T> class TVector<T, 3>`  
_L1000-1177_
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### union `Chaos::TVector::(anonymous)`  
``  
_L1166-1176_

#### struct `Chaos::TVector::__anon9d291f20010a::(anonymous)`  
``  
_L1168-1172_

#### class `Chaos::TVector`  
`template<> class TVector<int32, 2>`  
_L1190-1313_
- L44 _public typedef_ `using FElement = T;`
- L45 _public member_ `static const int NumElements = d;`
- L46 _public typedef_ `using FTraits = TVectorTraits<T, d>;`
- L48 _public prototype_ `TVector(const TVector&) = default;`
- L49 _public prototype_ `TVector& operator=(const TVector&) = default;`
- L51 _public prototype_ `TVector() = default;`
- L53 _public function_ `explicit TVector(const FElement& Element)`
- L61 _public function_ `TVector(std::initializer_list<T> InElements)`
- L72 _public function_ `template <int N=d, typename std::enable_if<N==2, int>::type = 0> TVector(const T& V0, const T& V1)`
- L79 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2)`
- L87 _public function_ `template <int N=d, typename std::enable_if<N==4, int>::type = 0> TVector(const T& V0, const T& V1, const T& V2, const T& V3)`
- L97 _public function_ `template <int N=d, typename std::enable_if<N==3, int>::type = 0> TVector(const FVector3f& Other)` — LWC_TODO: Make this explicit for FReal = double
- L104 _public function_ `template <int N = d, typename std::enable_if<N == 3, int>::type = 0> TVector(const FVector3d& Other)`
- L113 _public function_ `template<class T2> TVector(const TVector<T2, d>& Other)`
- L122 _public function_ `template<class T2> TVector<T, d>& operator=(const TVector<T2, d>& Other)`
- L131 _public function_ `FElement& operator[](int Index)`
- L141 _public function_ `const FElement& operator[](int Index) const`
- L151 _public function_ `int32 Num() const`
- L157 _public function_ `TVector(std::istream& Stream)`
- L164 _public function_ `void Write(std::ostream& Stream) const`
- L189 _public function_ `bool ContainsNaN() const`
- L380 _private member_ `FElement V[NumElements];`
- L389 _public typedef_ `using FElement = FReal;`
- L390 _public typedef_ `using BaseType = UE::Math::TVector4<FReal>;`
- L398 _public function_ `explicit TVector(const FReal x) : BaseType(x, x, x, x)`
- L400 _public function_ `TVector(const FReal x, const FReal y, const FReal z, const FReal w) : BaseType(x, y, z, w)`
- L402 _public function_ `TVector(const BaseType& vec) : BaseType(vec)`
- L410 _public typedef_ `using FElement = FRealSingle;`
- L417 _public function_ `explicit TVector(const FRealSingle x) : UE::Math::TVector<FRealSingle>(x, x, x)`
- L419 _public function_ `TVector(const FRealSingle x, const FRealSingle y, const FRealSingle z) : UE::Math::TVector<FRealSingle>(x, y, z)`
- L421 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>((UE::Math::TVector<FRealSingle>)vec)`
- L423 _public function_ `TVector(const UE::Math::TVector<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L425 _public function_ `TVector(const UE::Math::TVector4<FRealSingle>& vec) : UE::Math::TVector<FRealSingle>(vec.X, vec.Y, vec.Z)`
- L427 _public function_ `TVector(const UE::Math::TVector4<FRealDouble>& vec)` — LWC_TODO: Precision loss. Make explicit for FRealSingle = FRealSingle?
- L445 _public function_ `static inline TVector<FRealSingle, 3> Lerp(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2, const FRealSingle F)`
- L446 _public function_ `static inline TVector<FRealSingle, 3> CrossProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L447 _public function_ `static inline FRealSingle DotProduct(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L448 _public function_ `bool operator<=(const TVector<FRealSingle, 3>& V) const`
- L452 _public function_ `bool operator>=(const TVector<FRealSingle, 3>& V) const`
- L456 _public function_ `TVector<FRealSingle, 3> operator-() const`
- L460 _public function_ `TVector<FRealSingle, 3> operator+(const FRealSingle Other) const`
- L464 _public function_ `TVector<FRealSingle, 3> operator-(const FRealSingle Other) const`
- L468 _public function_ `TVector<FRealSingle, 3> operator*(const FRealSingle Other) const`
- L472 _public function_ `TVector<FRealSingle, 3> operator/(const FRealSingle Other) const`
- L480 _public function_ `TVector<FRealSingle, 3> operator+(const TVector<FRealSingle, 3>& Other) const`
- L484 _public function_ `TVector<FRealSingle, 3> operator-(const TVector<FRealSingle, 3>& Other) const`
- L488 _public function_ `TVector<FRealSingle, 3> operator*(const TVector<FRealSingle, 3>& Other) const`
- L492 _public function_ `TVector<FRealSingle, 3> operator/(const TVector<FRealSingle, 3>& Other) const`
- L497 _public function_ `template<class T2> TVector<FRealSingle, 3> operator+(const TVector<T2, 3>& Other) const`
- L502 _public function_ `template<class T2> TVector<FRealSingle, 3> operator-(const TVector<T2, 3>& Other) const`
- L507 _public function_ `template<class T2> TVector<FRealSingle, 3> operator*(const TVector<T2, 3>& Other) const`
- L512 _public function_ `template<class T2> TVector<FRealSingle, 3> operator/(const TVector<T2, 3>& Other) const`
- L516 _public function_ `FRealSingle Product() const`
- L520 _public function_ `FRealSingle Max() const`
- L524 _public function_ `FRealSingle Min() const`
- L528 _public function_ `int32 MaxAxis() const`
- L532 _public function_ `FRealSingle Mid() const`
- L536 _public function_ `TVector<FRealSingle, 3> ComponentwiseMin(const TVector<FRealSingle, 3>& Other) const`
- L537 _public function_ `TVector<FRealSingle, 3> ComponentwiseMax(const TVector<FRealSingle, 3>& Other) const`
- L538 _public function_ `static TVector<FRealSingle, 3> Max(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L542 _public function_ `inline void FlushToZero(FRealSingle Epsilon)`
- L548 _public function_ `static TVector<FRealSingle, 3> AxisVector(const int32 Axis)`
- L550 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L568 _public function_ `FRealSingle SafeNormalize(FRealSingle Epsilon = 1e-4f)`
- L580 _public function_ `TVector<FRealSingle, 3> GetOrthogonalVector() const`
- L596 _public function_ `static FRealSingle AngleBetween(const TVector<FRealSingle, 3>& V1, const TVector<FRealSingle, 3>& V2)`
- L603 _public function_ `static TVector<FRealSingle, 3> CalculateVelocity(const TVector<FRealSingle, 3>& P0, const TVector<FRealSingle, 3>& P1, const FRealSingle Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L608 _public function_ `static bool IsNearlyEqual(const TVector<FRealSingle, 3>& A, const TVector<FRealSingle, 3>& B, const FRealSingle Epsilon)`
- L619 _public typedef_ `using FElement = FRealDouble;`
- L626 _public function_ `explicit TVector(const FRealDouble x) : UE::Math::TVector<FRealDouble>(x, x, x)`
- L628 _public function_ `TVector(const FRealDouble x, const FRealDouble y, const FRealDouble z) : UE::Math::TVector<FRealDouble>(x, y, z)`
- L630 _public function_ `TVector(const UE::Math::TVector<FRealSingle>& vec) : UE::Math::TVector<FRealDouble>((UE::Math::TVector<FRealDouble>)vec)`
- L634 _public function_ `TVector(const FVector4& vec) : UE::Math::TVector<FRealDouble>(vec.X, vec.Y, vec.Z)`
- L651 _public function_ `static inline TVector<FRealDouble, 3> Lerp(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2, const FRealDouble F)`
- L652 _public function_ `static inline TVector<FRealDouble, 3> CrossProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L653 _public function_ `static inline FRealDouble DotProduct(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L654 _public function_ `bool operator<=(const TVector<FRealDouble, 3>& V) const`
- L658 _public function_ `bool operator>=(const TVector<FRealDouble, 3>& V) const`
- L662 _public function_ `TVector<FRealDouble, 3> operator-() const`
- L666 _public function_ `TVector<FRealDouble, 3> operator+(const FRealDouble Other) const`
- L670 _public function_ `TVector<FRealDouble, 3> operator-(const FRealDouble Other) const`
- L674 _public function_ `TVector<FRealDouble, 3> operator*(const FRealDouble Other) const`
- L678 _public function_ `TVector<FRealDouble, 3> operator/(const FRealDouble Other) const`
- L686 _public function_ `TVector<FRealDouble, 3> operator+(const TVector<FRealDouble, 3>& Other) const`
- L690 _public function_ `TVector<FRealDouble, 3> operator-(const TVector<FRealDouble, 3>& Other) const`
- L694 _public function_ `TVector<FRealDouble, 3> operator*(const TVector<FRealDouble, 3>& Other) const`
- L698 _public function_ `TVector<FRealDouble, 3> operator/(const TVector<FRealDouble, 3>& Other) const`
- L703 _public function_ `template<class T2> TVector<FRealDouble, 3> operator+(const TVector<T2, 3>& Other) const`
- L708 _public function_ `template<class T2> TVector<FRealDouble, 3> operator-(const TVector<T2, 3>& Other) const`
- L713 _public function_ `template<class T2> TVector<FRealDouble, 3> operator*(const TVector<T2, 3>& Other) const`
- L718 _public function_ `template<class T2> TVector<FRealDouble, 3> operator/(const TVector<T2, 3>& Other) const`
- L722 _public function_ `FRealDouble Product() const`
- L726 _public function_ `FRealDouble Max() const`
- L730 _public function_ `FRealDouble Min() const`
- L738 _public function_ `FRealDouble Mid() const`
- L742 _public function_ `TVector<FRealDouble, 3> ComponentwiseMin(const TVector<FRealDouble, 3>& Other) const`
- L743 _public function_ `TVector<FRealDouble, 3> ComponentwiseMax(const TVector<FRealDouble, 3>& Other) const`
- L744 _public function_ `static TVector<FRealDouble, 3> Max(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L748 _public function_ `inline void FlushToZero(FRealDouble Epsilon)`
- L754 _public function_ `static TVector<FRealDouble, 3> AxisVector(const int32 Axis)`
- L758 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L776 _public function_ `FRealDouble SafeNormalize(FRealDouble Epsilon = 1e-4f)`
- L788 _public function_ `TVector<FRealDouble, 3> GetOrthogonalVector() const`
- L804 _public function_ `static FRealDouble AngleBetween(const TVector<FRealDouble, 3>& V1, const TVector<FRealDouble, 3>& V2)`
- L811 _public function_ `static TVector<FRealDouble, 3> CalculateVelocity(const TVector<FRealDouble, 3>& P0, const TVector<FRealDouble, 3>& P1, const FRealDouble Dt)` — Calculate the velocity to move from P0 to P1 in time Dt. Exists just for symmetry with TRotation::CalculateAngularVelocity!
- L816 _public function_ `static bool IsNearlyEqual(const TVector<FRealDouble, 3>& A, const TVector<FRealDouble, 3>& B, const FRealDouble Epsilon)`
- L826 _public typedef_ `using FElement = decltype(FVector2f::X);`
- L832 _public function_ `TVector(const FRealSingle x) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))x)`
- L834 _public function_ `TVector(const FRealSingle x, const FRealSingle y) : FVector2f((decltype(FVector2f::X))x, (decltype(FVector2f::X))y)`
- L836 _public function_ `TVector(const FVector2f& vec) : FVector2f(vec)`
- L846 _public function_ `template <typename OtherT> TVector(const TVector<OtherT, 2>& InVector)`
- L858 _public function_ `static TVector<FRealSingle, 2> AxisVector(const int32 Axis)`
- L875 _public function_ `static TVector<FRealSingle, 2> Max(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L879 _public function_ `static Pair<FRealSingle, int32> MaxAndAxis(const TVector<FRealSingle, 2>& V1, const TVector<FRealSingle, 2>& V2)`
- L892 _public function_ `template<class T2> TVector<FRealSingle, 2> operator/(const TVector<T2, 2>& Other) const`
- L896 _public function_ `TVector<FRealSingle, 2> operator/(const FRealSingle Other) const`
- L900 _public function_ `TVector<FRealSingle, 2> operator*(const FRealSingle Other) const`
- L904 _public function_ `TVector<FRealSingle, 2> operator*(const TVector<FRealSingle, 2>& Other) const`
- L914 _public typedef_ `using FElement = decltype(FVector2d::X);`
- L920 _public function_ `TVector(const FRealDouble x) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))x)`
- L922 _public function_ `TVector(const FRealDouble x, const FRealDouble y) : FVector2d((decltype(FVector2d::X))x, (decltype(FVector2d::X))y)`
- L924 _public function_ `TVector(const FVector2d& vec) : FVector2d(vec)`
- L946 _public function_ `static TVector<FRealDouble, 2> AxisVector(const int32 Axis)`
- L963 _public function_ `static TVector<FRealDouble, 2> Max(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L967 _public function_ `static Pair<FRealDouble, int32> MaxAndAxis(const TVector<FRealDouble, 2>& V1, const TVector<FRealDouble, 2>& V2)`
- L980 _public function_ `template<class T2> TVector<FRealDouble, 2> operator/(const TVector<T2, 2>& Other) const`
- L984 _public function_ `TVector<FRealDouble, 2> operator/(const FRealDouble Other) const`
- L988 _public function_ `TVector<FRealDouble, 2> operator*(const FRealDouble Other) const`
- L992 _public function_ `TVector<FRealDouble, 2> operator*(const TVector<FRealDouble, 2>& Other) const`
- L1010 _public prototype_ `FORCEINLINE TVector() = default;`
- L1012 _public function_ `FORCEINLINE explicit TVector(T InX) : X(InX), Y(InX), Z(InX)`
- L1014 _public function_ `FORCEINLINE TVector(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ)`
- L1017 _public function_ `FORCEINLINE int32 Num() const`
- L1018 _public function_ `FORCEINLINE bool operator==(const TVector<T, 3>& Other) const`
- L1020 _public function_ `FORCEINLINE TVector(const UE::Math::TVector<FReal>& Other)`
- L1028 _public function_ `template<class T2> FORCEINLINE TVector(const TVector<T2, 3>& Other) : X(static_cast<T>(Other.X)) , Y(static_cast<T>(Other.Y)) , Z(static_cast<T>(Other.Z))`
- L1035 _public function_ `FORCEINLINE TVector(std::istream& Stream)`
- L1041 _public function_ `FORCEINLINE void Write(std::ostream& Stream) const`
- L1049 _public function_ `template<class T2> FORCEINLINE TVector<T, 3>& operator=(const TVector<T2, 3>& Other)`
- L1056 _public function_ `FORCEINLINE T Size() const`
- L1061 _public function_ `FORCEINLINE T Product() const`
- L1062 _public function_ `FORCEINLINE static TVector<T, 3> AxisVector(const int32 Axis)`
- L1068 _public function_ `FORCEINLINE T SizeSquared() const`
- L1070 _public function_ `FORCEINLINE T Min() const`
- L1071 _public function_ `FORCEINLINE T Max() const`
- L1072 _public function_ `T Mid() const`
- L1077 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMin(const TVector<T, 3>& Other) const`
- L1078 _public function_ `FORCEINLINE TVector<T, 3> ComponentwiseMax(const TVector<T, 3>& Other) const`
- L1080 _public function_ `TVector<T, 3> GetSafeNormal() const`
- L1089 _public function_ `FORCEINLINE T SafeNormalize()`
- L1102 _public function_ `FORCEINLINE bool ContainsNaN() const`
- L1108 _public function_ `FORCEINLINE T operator[](int32 Idx) const`
- L1109 _public function_ `FORCEINLINE T& operator[](int32 Idx)`
- L1112 _public function_ `FORCEINLINE TVector<T, 3> operator-() const`
- L1113 _public function_ `FORCEINLINE TVector<T, 3> operator*(const TVector<T, 3>& Other) const`
- L1114 _public function_ `FORCEINLINE TVector<T, 3> operator/(const TVector<T, 3>& Other) const`
- L1115 _public function_ `FORCEINLINE TVector<T, 3> operator/(const T Scalar) const`
- L1116 _public function_ `FORCEINLINE TVector<T, 3> operator+(const TVector<T, 3>& Other) const`
- L1117 _public function_ `FORCEINLINE TVector<T, 3> operator+(const T Scalar) const`
- L1118 _public function_ `FORCEINLINE TVector<T, 3> operator-(const TVector<T, 3>& Other) const`
- L1119 _public function_ `FORCEINLINE TVector<T, 3> operator-(const T Scalar) const`
- L1121 _public function_ `FORCEINLINE TVector<T, 3>& operator+=(const TVector<T, 3>& Other)`
- L1128 _public function_ `FORCEINLINE TVector<T, 3>& operator-=(const TVector<T, 3>& Other)`
- L1135 _public function_ `FORCEINLINE TVector<T, 3>& operator/=(const TVector<T, 3>& Other)`
- L1142 _public function_ `FORCEINLINE TVector<T, 3> operator*(const T S) const`
- L1143 _public function_ `FORCEINLINE TVector<T, 3>& operator*=(const T S)`
- L1151 _public function_ `FORCEINLINE static inline FReal DotProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1155 _public function_ `FORCEINLINE static inline Vector<FReal, 3> CrossProduct(const Vector<FReal, 3>& V1, const Vector<FReal, 3>& V2)`
- L1193 _public typedef_ `using FElement = int32;`
- L1202 _public function_ `FORCEINLINE explicit TVector(const FElement InX) : X(InX), Y(InX)`
- L1205 _public function_ `FORCEINLINE TVector(const FElement InX, const FElement InY) : X(InX), Y(InY)`
- L1209 _public function_ `template<typename OtherT> FORCEINLINE TVector(const TVector<OtherT, 2>& InVector) : X((int32)InVector.X) , Y((int32)InVector.Y)`
- L1222 _public function_ `FORCEINLINE FElement Product() const`
- L1227 _public function_ `FORCEINLINE static TVector<FElement, 2> AxisVector(const int32 Axis)`
- L1243 _public function_ `template<typename OtherT> FORCEINLINE TVector<int32, 2>& operator=(const TVector<OtherT, 2>& Other)`
- L1251 _public function_ `FORCEINLINE FElement operator[](const int32 Idx) const`
- L1252 _public function_ `FORCEINLINE FElement& operator[](const int32 Idx)`
- L1255 _public function_ `FORCEINLINE TVector<FElement, 2> operator-() const`
- L1256 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const TVector<FElement, 2>& Other) const`
- L1257 _public function_ `FORCEINLINE TVector<FElement, 2> operator/(const TVector<FElement, 2>& Other) const`
- L1258 _public function_ `FORCEINLINE TVector<FElement, 2> operator+(const TVector<FElement, 2>& Other) const`
- L1259 _public function_ `FORCEINLINE TVector<FElement, 2> operator-(const TVector<FElement, 2>& Other) const`
- L1261 _public function_ `FORCEINLINE TVector<FElement, 2>& operator+=(const TVector<FElement, 2>& Other)`
- L1267 _public function_ `FORCEINLINE TVector<FElement, 2>& operator-=(const TVector<FElement, 2>& Other)`
- L1273 _public function_ `FORCEINLINE TVector<FElement, 2>& operator/=(const TVector<FElement, 2>& Other)`
- L1279 _public function_ `FORCEINLINE TVector<FElement, 2> operator*(const FElement& S) const`
- L1283 _public function_ `FORCEINLINE TVector<FElement, 2>& operator*=(const FElement& S)`

#### struct `Chaos::TVector::__anon9d291f20030a::(anonymous)`  
``  
_L1305-1308_

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace FMath`
- L23 _function_ `float Sqrt(float v)` (scope `FMath`)
- L24 _function_ `double Sqrt(double v)` (scope `FMath`)
- L25 _function_ `float Atan2(float x, float y)` (scope `FMath`)
- L26 _function_ `double Atan2(double x, double y)` (scope `FMath`)
- L31 _namespace_ `namespace Chaos`
- L172 _function_ `friend bool operator==(const TVector<T, d>& L, const TVector<T, d>& R)` (scope `Chaos`)
- L184 _function_ `friend bool operator!=(const TVector<T, d>& L, const TVector<T, d>& R)` (scope `Chaos`)
- L476 _function_ `friend TVector<FRealSingle, 3> operator/(const FRealSingle S, const TVector<FRealSingle, 3>& V)` (scope `Chaos`)
- L682 _function_ `friend TVector<FRealDouble, 3> operator/(const FRealDouble S, const TVector<FRealDouble, 3>& V)` (scope `Chaos`)
- L1169 _member_ `T X;` (scope `Chaos::TVector::__anon9d291f20010a::__anon9d291f200208`)
- L1170 _member_ `T Y;` (scope `Chaos::TVector::__anon9d291f20010a::__anon9d291f200208`)
- L1171 _member_ `T Z;` (scope `Chaos::TVector::__anon9d291f20010a::__anon9d291f200208`)
- L1175 _member_ `T XYZ[3];` (scope `Chaos::TVector::__anon9d291f20010a`) — `UE_DEPRECATED(all, "For internal use only")`
- L1179 _function_ `template<class T> inline TVector<T, 3> operator*(const T S, const TVector<T, 3>& V)` (scope `Chaos`)
- L1184 _function_ `template<class T> inline TVector<T, 3> operator/(const T S, const TVector<T, 3>& V)` (scope `Chaos`)
- L1290 _function_ `FORCEINLINE friend bool operator==(const TVector<FElement, 2>& L, const TVector<FElement, 2>& R)` (scope `Chaos`)
- L1295 _function_ `FORCEINLINE friend bool operator!=(const TVector<FElement, 2>& L, const TVector<FElement, 2>& R)` (scope `Chaos`)
- L1306 _member_ `FElement X;` (scope `Chaos::TVector::__anon9d291f20030a::__anon9d291f200408`)
- L1307 _member_ `FElement Y;` (scope `Chaos::TVector::__anon9d291f20030a::__anon9d291f200408`)
- L1311 _member_ `FElement XY[2];` (scope `Chaos::TVector::__anon9d291f20030a`) — `UE_DEPRECATED(all, "For internal use only")`
- L1316 _function_ `template<class T> inline uint32 GetTypeHash(const Chaos::TVector<T, 2>& V)` (scope `Chaos`)
- L1324 _function_ `template<class T> inline uint32 GetTypeHash(const Chaos::TVector<T, 3>& V)` (scope `Chaos`)
- L1334 _function_ `template<typename T, int d> inline FArchive& SerializeReal(FArchive& Ar, TVector<T, d>& ValueIn)` (scope `Chaos`) — this is used as
- L1347 _function_ `template<int d> FArchive& operator<<(FArchive& Ar, TVector<FRealSingle, d>& ValueIn)` (scope `Chaos`)
- L1353 _function_ `template<int d> FArchive& operator<<(FArchive& Ar, TVector<FRealDouble, d>& ValueIn)` (scope `Chaos`)
- L1360 _function_ `template<typename T, int d> FArchive& operator<<(FArchive& Ar, TVector<T, d>& ValueIn)` (scope `Chaos`) — general for for all other vectors

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector16Int8.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector16Int8FPU.h` (Public)


#### struct `VectorRegister16Int8`  
`struct UE_INTERNAL VectorRegister16Int8`  
_L8-11_
- L10 _public member_ `int8 Value[16];`

#### Free symbols / members of external scopes

- L13 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 Vector16Int8Set1(int8 Value)`
- L23 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 VectorLoad16Int8(const int8* Ptr)`
- L33 _function_ `UE_INTERNAL FORCEINLINE void VectorStore(VectorRegister16Int8 Vec, int8* Ptr)`
- L41 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 VectorCompareEQ(VectorRegister16Int8 Vec1, VectorRegister16Int8 Vec2)`
- L51 _function_ `UE_INTERNAL FORCEINLINE uint16 VectorMaskBits(VectorRegister16Int8 VecMask)`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector16Int8Neon.h` (Public)


#### struct `VectorRegister16Int8`  
`struct UE_INTERNAL VectorRegister16Int8`  
_L10-13_
- L12 _public member_ `int8x16_t Value;`

#### Free symbols / members of external scopes

- L15 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 Vector16Int8Set1(int8 Value)`
- L22 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 VectorLoad16Int8(const int8* Ptr)`
- L29 _function_ `UE_INTERNAL FORCEINLINE void VectorStore(VectorRegister16Int8 Vec, int8* Ptr)`
- L34 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 VectorCompareEQ(VectorRegister16Int8 Vec1, VectorRegister16Int8 Vec2)`
- L41 _function_ `UE_INTERNAL FORCEINLINE uint16 VectorMaskBits(VectorRegister16Int8 VecMask)`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector16Int8SSE.h` (Public)


#### struct `VectorRegister16Int8`  
`struct UE_INTERNAL VectorRegister16Int8`  
_L10-13_
- L12 _public member_ `VectorRegister4Int Value;`

#### Free symbols / members of external scopes

- L15 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 Vector16Int8Set1(int8 Value)`
- L22 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 VectorLoad16Int8(const int8* Ptr)`
- L29 _function_ `UE_INTERNAL FORCEINLINE void VectorStore(VectorRegister16Int8 Vec, int8* Ptr)`
- L34 _function_ `UE_INTERNAL FORCEINLINE VectorRegister16Int8 VectorCompareEQ(VectorRegister16Int8 Vec1, VectorRegister16Int8 Vec2)`
- L41 _function_ `UE_INTERNAL FORCEINLINE uint16 VectorMaskBits(VectorRegister16Int8 VecMask)`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector32Int8.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector32Int8AVX.h` (Public)


#### struct `VectorRegister32Int8`  
`struct UE_INTERNAL VectorRegister32Int8`  
_L10-13_
- L12 _public member_ `__m256i V;`

#### Free symbols / members of external scopes

- L15 _function_ `UE_INTERNAL FORCEINLINE VectorRegister32Int8 Vector32Int8Set1(int8 Value)`
- L22 _function_ `UE_INTERNAL FORCEINLINE VectorRegister32Int8 VectorLoad32Int8(const int8* Ptr)`
- L29 _function_ `UE_INTERNAL FORCEINLINE void VectorStore(VectorRegister32Int8 Vec, int8* Ptr)`
- L34 _function_ `UE_INTERNAL FORCEINLINE VectorRegister32Int8 VectorCompareEQ(VectorRegister32Int8 Vec1, VectorRegister32Int8 Vec2)`
- L54 _function_ `UE_INTERNAL FORCEINLINE uint32 VectorMaskBits(VectorRegister32Int8 VecMask)`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/Vector32Int8Common.h` (Public)


#### struct `VectorRegister32Int8`  
`struct UE_INTERNAL VectorRegister32Int8`  
_L8-11_
- L10 _public member_ `VectorRegister16Int8 V[2];`

#### Free symbols / members of external scopes

- L13 _function_ `UE_INTERNAL FORCEINLINE VectorRegister32Int8 Vector32Int8Set1(int8 Value)`
- L20 _function_ `UE_INTERNAL FORCEINLINE VectorRegister32Int8 VectorLoad32Int8(const int8* Ptr)`
- L28 _function_ `UE_INTERNAL FORCEINLINE void VectorStore(VectorRegister32Int8 Vec, int8* Ptr)`
- L34 _function_ `UE_INTERNAL FORCEINLINE VectorRegister32Int8 VectorCompareEQ(VectorRegister32Int8 Vec1, VectorRegister32Int8 Vec2)`
- L42 _function_ `UE_INTERNAL FORCEINLINE uint32 VectorMaskBits(VectorRegister32Int8 VecMask)`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/VectorND.h` (Public)


#### class `Chaos::VectorND`  
`template<class T> class VectorND : public TArray<T>`  
_L9-18_
- inherits: `TArray<T>`
- L14 _public function_ `VectorND(const int32 Size)`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosCore/Public/Chaos/VectorUtility.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `template<typename T> T TVectorZero();`
- L12 _function_ `template<> inline VectorRegister4Float TVectorZero<VectorRegister4Float>()`
- L18 _function_ `template<> inline VectorRegister4Double TVectorZero<VectorRegister4Double>()`
- L24 _prototype_ `template<typename T> T TMakeVectorRegister(float X, float Y, float Z, float W);`
- L27 _function_ `template<> inline VectorRegister4Float TMakeVectorRegister<VectorRegister4Float>(float X, float Y, float Z, float W)`
- L33 _function_ `template<> inline VectorRegister4Double TMakeVectorRegister<VectorRegister4Double>(float X, float Y, float Z, float W)`
- L39 _prototype_ `template<typename T> constexpr T TMakeVectorRegisterConstant(float X, float Y, float Z, float W);`
- L42 _function_ `template<> constexpr VectorRegister4Float TMakeVectorRegisterConstant<VectorRegister4Float>(float X, float Y, float Z, float W)`
- L48 _function_ `template<> constexpr VectorRegister4Double TMakeVectorRegisterConstant<VectorRegister4Double>(float X, float Y, float Z, float W)`
- L54 _prototype_ `template<typename T> VectorRegister4Float TMakeVectorRegisterFloatFromDouble(const T& V);`
- L57 _function_ `template<> inline VectorRegister4Float TMakeVectorRegisterFloatFromDouble<VectorRegister4Double>(const VectorRegister4Double& V)`
- L64 _function_ `template<> constexpr VectorRegister4Float TMakeVectorRegisterFloatFromDouble<VectorRegister4Float>(const VectorRegister4Float& V)` — Should generate no op
- L75 _function_ `FORCEINLINE VectorRegister4Float VectorCast4IntTo4Float(const VectorRegister4Int& V)` — Cast VectorRegister4Int in VectorRegister4Float @param V	vector @return		VectorRegister4Float( B.x, A.y, A.z, A.w)
- L93 _function_ `FORCEINLINE VectorRegister4Int VectorCast4FloatTo4Int(const VectorRegister4Float& V)` — Cast VectorRegister4Float in VectorRegister4Int @param V	vector @return		VectorCast4FloatTo4Int( B.x, A.y, A.z, A.w)
- L112 _function_ `FORCEINLINE VectorRegister4Float VectorUnpackLo(const VectorRegister4Float& A, const VectorRegister4Float& B)` — Selects and interleaves the lower two SP FP values from A and B. @param A	1st vector @param B	2nd vector @return		VectorRegister4Float( A.x, B.x, A.y, B.y)
- L130 _function_ `FORCEINLINE VectorRegister4Double VectorUnpackLo(const VectorRegister4Double& A, const VectorRegister4Double& B)` — Selects and interleaves the lower two DP FP values from A and B. @param A	1st vector @param B	2nd vector @return		VectorRegister4Float( A.x, B.x, A.y, B.y)
- L159 _function_ `FORCEINLINE VectorRegister4Float VectorUnpackHi(const VectorRegister4Float& A, const VectorRegister4Float& B)` — Selects and interleaves the higher two SP FP values from A and B. @param A	1st vector @param B	2nd vector @return		VectorRegister4Float( A.z, B.z, A.w, B.w)
- L177 _function_ `FORCEINLINE VectorRegister4Float VectorMoveLh(const VectorRegister4Float& A, const VectorRegister4Float& B)` — Moves the lower 2 SP FP values of b to the upper 2 SP FP values of the result. The lower 2 SP FP values of a are passed through to the result. @param A	1st vector @param B	2nd vector @return		VectorRegister4Float( A.x, A.y, B.x, B.y)
- L187 _namespace_ `namespace Chaos`
- L187 _namespace_ `namespace Private` (scope `Chaos`)
- L197 _function_ `FORCEINLINE VectorRegister4Float VectorDot3FastX(const VectorRegister4Float& Vec1, const VectorRegister4Float& Vec2)` (scope `Chaos::Private`) — Calculates the dot product of two vectors and returns a vector with the result in the first component. W values should be set to 0 on the vector input. This function should be used with caution. Only the returned X should be read. @param Vec1	1st vector set with W equal to 0 @param Vec2	2nd vector set with W equal to 0 @return		d = dot3X(Vec1.xyz0, Vec2.xyz0), VectorRegister4Float( d, ?, ?, ? )
- L211 _function_ `FORCEINLINE VectorRegister4Float VectorMatrixMultiply(const VectorRegister4Float& Vec, const FMatrix33& M)` (scope `Chaos::Private`)
- L231 _function_ `FORCEINLINE VectorRegister4Float VectorCrossNoFMA(const VectorRegister4Float& Vec1, const VectorRegister4Float& Vec2)` (scope `Chaos::Private`) — Calculates the cross product of two vectors (XYZ components). W of the input should be 0, and will remain 0. This function is not using FMA for stability reason, rounding with FMA could cause numerical instability. @param Vec1	1st vector @param Vec2	2nd vector @return		cross(Vec1.xyz, Vec2.xyz). W of the input should be 0, and will remain 0.
- L260 _function_ `FORCEINLINE VectorRegister4Double VectorCrossNoFMA(const VectorRegister4Double& Vec1, const VectorRegister4Double& Vec2)` (scope `Chaos::Private`) — Calculates the cross product of two vectors (XYZ components). W of the input should be 0, and will remain 0. This function is not using FMA for stability reason, rounding with FMA could cause numerical instability. @param Vec1	1st vector @param Vec2	2nd vector @return		cross(Vec1.xyz, Vec2.xyz). W of the input should be 0, and will remain 0.
- L289 _function_ `FORCEINLINE VectorRegister4Float VectorBitwiseNotAnd(const VectorRegister4Float& A, const VectorRegister4Float& B)` — Combines two vectors using bitwise NOT AND (treating each vector as a 128 bit field) @param Vec1	1st vector @param Vec2	2nd vector @return		VectorRegister4Float( for each bit i: !Vec1[i] & Vec2[i] )
- L304 _function_ `FORCEINLINE VectorRegister4Double VectorBitwiseNotAnd(const VectorRegister4Double& A, const VectorRegister4Double& B)`

### `Source/Runtime/Experimental/ChaosCore/Public/ChaosCheck.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define CHAOS_CHECK(Condition) check(Condition)`
- L10 _macro_ `#define CHAOS_ENSURE(Condition) ensure(Condition)`
- L11 _macro_ `#define CHAOS_ENSURE_MSG(InExpression, InFormat, ... ) ensureMsgf(InExpression, InFormat, ##__VA_ARGS__)`
- L15 _macro_ `#define CHAOS_LOG(InLog, InSeverity, InFormat, ...) UE_LOG(InLog, Log, InFormat, ##__VA_ARGS__)` — #TODO: remove once cooking is working FORT-242999 downgrading all severity to Log
- L16 _macro_ `#define CHAOS_CLOG(InExpression, InLog, InSeverity, InFormat, ...) UE_CLOG(InExpression, InLog, Log, InFormat, ##__VA_ARGS__)`
- L21 _macro_ `#define CHAOS_CHECK(Condition) (!!(Condition))`
- L22 _macro_ `#define CHAOS_ENSURE(Condition) (!!(Condition))`
- L23 _macro_ `#define CHAOS_ENSURE_MSG(InExpression, InFormat, ... ) (!!(InExpression))`
- L24 _macro_ `#define CHAOS_LOG(InLog, InSeverity, InFormat, ...)`
- L25 _macro_ `#define CHAOS_CLOG(InExpression, InLog, InSeverity, InFormat, ...) (!!(InExpression))`

### `Source/Runtime/Experimental/ChaosCore/Public/ChaosCoreModule.h` (Public)


#### class `FChaosCoreEngineModule`  
`class FChaosCoreEngineModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public function_ `virtual void StartupModule() override`
- L12 _public function_ `virtual void ShutdownModule() override`
