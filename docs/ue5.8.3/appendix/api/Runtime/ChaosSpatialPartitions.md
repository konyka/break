# Runtime / ChaosSpatialPartitions

- module root: `Source/Runtime/Experimental/ChaosSpatialPartitions`
- headers: 18; symbols: 545
- symbol kinds: class=10, enum=10, enumerator=36, function=29, member=150, namespace=40, prototype=218, struct=33, typedef=19
- PublicDependencyModuleNames: ChaosCore, Core

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Private/ChaosSpatialPartitions/Algorithms/AabbTreeAlgorithm.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L10 _namespace_ `namespace AabbTreeAlgorithm` (scope `Chaos::SpatialPartition`)
- L12 _prototype_ `FAABB3 Union(const FAABB3& Aabb0, const FAABB3& Aabb1);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)
- L13 _prototype_ `FReal ComputeDeltaSurfaceArea(const FAABB3& OldAabb, const FAABB3& AabbToInclude);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)
- L15 _prototype_ `int32 AllocateNode(TArray<FAabbTreeNode>& Nodes, int32& FreeListHead);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)
- L16 _prototype_ `void DeallocateNode(TArray<FAabbTreeNode>& Nodes, int32& FreeListHead, int32 IndexToFree);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)
- L18 _prototype_ `bool IsLeaf(const FAabbTreeNode& Node);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)
- L20 _prototype_ `int32& GetIndexRef(FAabbTreeNode& ParentNode, const int32 NodeIndex);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Given a node and an expected child, returns the reference to the child on the parent.
- L22 _prototype_ `int32& GetSiblingRef(FAabbTreeNode& ParentNode, const int32 NodeIndex);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Given a node and an expected child, returns the reference to the sibling on the parent.
- L25 _prototype_ `void RecomputeAabb(TArray<FAabbTreeNode>& Nodes, const int32 Index);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Recomputes the aabb of the given node from the two children. Only valid for non-leaf nodes.
- L27 _prototype_ `bool RotateNodes(TArray<FAabbTreeNode>& Nodes, const int32 Index);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Attempts to perform a rotation of the children of the given node by minimizing surface area.
- L30 _prototype_ `void RecomputeAncestorAabbsAndRotate(TArray<FAabbTreeNode>& Nodes, int32 Index, bool bDoRotation);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Recomputes the aabbs of all nodes from the given node up through the root. This may also performs rotations if necessary to keep the tree balanced.
- L33 _prototype_ `int32 FindBestSiblingGreedy(const TArray<FAabbTreeNode>& Nodes, const int32 RootIndex, const FAABB3& NewAabb);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Finds the best sibling to insert a node at using a greedy surface area heuristic.
- L36 _prototype_ `int32 FindBestSiblingAdvancedGreedySAH(const TArray<FAabbTreeNode>& Nodes, const int32 RootIndex, const FAABB3& NewAabb);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Finds the best sibling to insert a node at using a more advanced greedy surface area heuristic. This version keeps track of the overall SA increase and can select internal nodes.
- L38 _prototype_ `int32 FindBestSiblingGlobalSearch(const TArray<FAabbTreeNode>& Nodes, const int32 RootIndex, const FAABB3& NewAabb);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Finds the best sibling to insert a node at using a global search. This is slow and primarily used for testing / validation.
- L40 _prototype_ `int32 FindBestSiblingBranchAndBound(const TArray<FAabbTreeNode>& Nodes, const int32 RootIndex, const FAABB3& NewAabb);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Finds the best sibling to insert a node at by using an efficient global search.
- L43 _prototype_ `int32 FindBestSiblingBranchAndBound(const TArray<FAabbTreeNode>& Nodes, const int32 RootIndex, const FAABB3& NewAabb, TArray<TPair<int32, FReal>>& PriorityQueue);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Finds the best sibling to insert a node at by using an efficient global search. This takes a priority queue for performance so as to minimize allocations between calls.
- L46 _function_ `template <typename QueryDataType, typename LeafCallbackType> EVisitResult Query(const TArray<FAabbTreeNode>& Nodes, const int32 RootIndex, const QueryDataType& QueryData, LeafCallbackType LeafCallback)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Private/ChaosSpatialPartitions/Algorithms/PartitioningAlgorithms.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L8 _namespace_ `namespace AabbTreeAlgorithm` (scope `Chaos::SpatialPartition`)
- L10 _prototype_ `int32 PickLargestAxis(const FVec3& Vector);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`)
- L15 _function_ `template <typename ElementType> void ComputeCentroidAabb(const TArrayView<const ElementType>& Elements, FAABB3& OutAabb)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Computes the aabb of the element centers (not the element aabbs). This does not reset the given aabb so this method can be used incrementally.
- L25 _prototype_ `void ComputeScaledVariance(const FVec3& Center, int32& InOutCurrentCount, FVec3& OutAverageCenter, FVec3& OutScaledCenterVariance);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Compute the scaled variance using Welford's method. Assumes Count, OutAverageCenter, and OutScaledCenterVariance are all initialized to zero before the first call. This method is meant to be used incrementally.
- L30 _function_ `template <typename ElementType> void ComputeScaledVariance(const TArrayView<const ElementType>& Elements, int32& InOutCurrentCount, FVec3& OutAverageCenter, FVec3& OutScaledCenterVariance)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Compute the scaled variance using Welford's method. Assumes Count, OutAverageCenter, and OutScaledCenterVariance are all initialized to zero before the first call. This method is meant to be used incrementally.
- L39 _prototype_ `void ComputeBoundsForBins(const FAABB3& CentroidAabb, const int32 Axis, FReal& OutBinsLowerBound, FReal& OutBinBoundsInvSize);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Computes the bounds information for all of the bins given the centroid aabb.
- L41 _prototype_ `void ComputeBin(const FAABB3& ElementAabb, const int32 Axis, const FReal BinsLowerBound, const FReal BinBoundsInvSize, TArray<FAabbBin>& Bins, int32& OutBinIndex);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Given a full bounds range (min + inverse size) on an axis, partitions an element into a binned area.
- L44 _function_ `template <typename ElementType> void ComputeBins(TArrayView<const ElementType>& Elements, const int32 Axis, const FReal BoundsLowerBound, const FReal InvBoundsSize, TArray<FAabbBin>& Bins, TArrayView<int32>& BinIndices)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Given a full bounds range (min + inverse size) on an axis, partitions elements into a binned area.
- L55 _prototype_ `void ComputeBinSplitPlanes(const TArray<FAabbBin>& Bins, TArray<FBinSplitPlane>& BinSplitPlanes);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Computes all of the potential "split planes" for the bins. The split plane N lies between bin N and N + 1.
- L57 _prototype_ `int32 PickBestBinSplitPlane(const TArray<FBinSplitPlane>& BinSplitPlanes);` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Returns the index of the split plane with the lowest cost (using a surface area heuristic).
- L63 _function_ `template <typename ElementType> bool PartitionElementsInPlace(TArrayView<const ElementType>& Elements, const int32 SplitAxis, const FReal SplitPosition, const int32 MaxCount, int32& Start, int32& End, int32& OutSplitIndex)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the elements into two sets: left < split <= right. The return value is the size of the left split. This will swap up to MaxCount items.
- L95 _function_ `template <typename ElementType> int32 PartitionElementsInPlace(TArrayView<const ElementType>& Elements, const int32 SplitAxis, const FReal SplitPosition)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the elements into two sets: left < split <= right. The return value is the size of the left split.
- L109 _function_ `template <typename ElementType> bool PartitionElementsInPlace(TArrayView<const ElementType>& Elements, const TArrayView<int32>& BinIndices, const int32 BestSplit, const int32 MaxCount, int32& Start, int32& End, int32& OutSplitIndex)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the elements into two sets using the bin indices: left < split <= right. The bin indices are not updated. The return value is the size of the left split. This will swap up to MaxCount items.
- L144 _function_ `template <typename ElementType> int32 PartitionElementsInPlace(TArrayView<const ElementType>& Elements, const TArrayView<int32>& BinIndices, const int32 BestSplit)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the elements into two sets using the bin indices: left < split <= right. The bin indices are not updated. The return value is the size of the left split.
- L157 _function_ `template <typename ElementType> void ComputeSplitPlaneWithSpatialMedianHeuristic(const TArrayView<const ElementType>& Elements, int32& OutSplitAxis, FReal& OutSplitPosition)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Computes an axis aligned split plane (axis + value) from the spatial median of the objects. The axis with the largest spread is picked as the split axis. The center of the centroid aabb on the split axis is picked as the split value.
- L173 _function_ `template <typename ElementType> void ComputeSplitPlaneWithMedianVarianceHeuristic(const TArrayView<const ElementType>& Elements, int32& OutSplitAxis, FReal& OutSplitPosition)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Computes an axis aligned split plane (axis + value) by using the variance of the centroid. The axis with the largest variance on the centroid is picked as the split axis. The average of the centroids on the split axis is picked as the split value.
- L189 _function_ `template <typename ElementType> int32 ComputeSplitPlaneWithSurfaceAreaHeuristic(TArrayView<const ElementType>& Elements, const int32 BinCount, TArrayView<int32>& BinIndices)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Returns the bin index that should be used to split the data into two sets such that: left < index <= right
- L215 _function_ `template <typename ElementType> int32 PartitionEntriesWithSpatialMedian(TArrayView<const ElementType>& Elements)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the given entries into two sets using the spatial median heuristic. The result is the size of the left partition.
- L225 _function_ `template <typename ElementType> int32 PartitionEntriesWithMedianVariance(TArrayView<const ElementType>& Elements)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the given entries into two sets using the median variance heuristic. The result is the size of the left partition.
- L235 _function_ `template <typename ElementType> int32 PartitionEntriesWithSurfaceArea(TArrayView<const ElementType>& Elements, const int32 BinCount, TArrayView<int32>& BinIndices)` (scope `Chaos::SpatialPartition::AabbTreeAlgorithm`) — Partitions the given entries into two sets using a binned surface area heuristic. The result is the size of the left partition.

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Algorithms/PartitioningMethod.h` (Public)


#### enum `Chaos::SpatialPartition::EPartitioningMethod`  
`enum EPartitioningMethod`  
_L11-19_
- desc: Methods for partitioning objects when building a spatial partition.
- L14 _public enumerator_ `CentroidSpatialMedian` — Split using the spatial median (aabb center) of the object centers.
- L16 _public enumerator_ `CentroidVariance` — Split using the variance of the object centers.
- L18 _public enumerator_ `SurfaceArea` — Split using a surface area heuristic.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Algorithms/PartitioningStructures.h` (Public)


#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FAabbBin`  
`struct UE_INTERNAL FAabbBin`  
_L10-14_
- L12 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L13 _public member_ `int32 Count = 0;`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FBinSplitPlane`  
`struct UE_INTERNAL FBinSplitPlane`  
_L16-22_
- L18 _public member_ `FAABB3 LeftAabb = FAABB3::EmptyAABB();`
- L19 _public member_ `FAABB3 RightAabb = FAABB3::EmptyAABB();`
- L20 _public member_ `int32 LeftCount = 0;`
- L21 _public member_ `int32 RightCount = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L8 _namespace_ `namespace AabbTreeAlgorithm` (scope `Chaos::SpatialPartition`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Algorithms/StaticAabbTreeTimeSlicer.h` (Public)


#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer`  
`struct UE_INTERNAL FStaticAabbTreeTimeSlicer`  
_L14-158_
- desc: Builds a static aabb tree incrementally. This allows building over several frames to fit within a time budget.
- L27 _public prototype_ `FStaticAabbTreeTimeSlicer() = default;`
- L28 _public prototype_ `UE_INTERNAL FStaticAabbTreeTimeSlicer(const FConfig& InConfig, TArray<FAabbTreeLeafElement>&& InElements);`
- L29 _public prototype_ `FStaticAabbTreeTimeSlicer(FStaticAabbTreeTimeSlicer&&) = default;`
- L31 _public prototype_ `FStaticAabbTreeTimeSlicer& operator=(FStaticAabbTreeTimeSlicer&&) = default;`
- L34 _public prototype_ `UE_INTERNAL bool Run();` — Runs the next iteration of work. Returns true as long as there is remaining work to do.
- L35 _public prototype_ `UE_INTERNAL bool IsFinished() const;`
- L37 _public prototype_ `UE_INTERNAL int32 GetRootIndex() const;`
- L38 _public prototype_ `UE_INTERNAL TArray<FAabbTreeNode>& GetNodes();`
- L39 _public prototype_ `UE_INTERNAL TArray<FAabbTreeLeaf>& GetLeaves();`
- L51 _private prototype_ `int32 AllocateNode();`
- L52 _private prototype_ `int32 BuildLeaf(const TArrayView<const FAabbTreeLeafElement>& Elements, const int32 NodeIndex);`
- L54 _private prototype_ `void AddNewWorkload(const TArrayView<const FAabbTreeLeafElement>& Elements, const int32 NodeIndex, const int32 Depth);`
- L55 _private prototype_ `void SplitWorkload(const FWorkload& ParentWorkload, const int32 SplitIndex);`
- L57 _private prototype_ `void Initialize(FWorkload& Workload);`
- L58 _private prototype_ `void RunSetup(FWorkload& Workload);`
- L59 _private prototype_ `void RunPartition(FWorkload& Workload);`
- L60 _private prototype_ `void RunFinish(FWorkload& Workload);`
- L63 _private prototype_ `bool ComputeCentroidAabb(FWorkload& Workload, int32& Start, FAABB3& OutCentroidAabb) const;` — Incrementally compute the centroid aabb for a workload. Returns true if the computation is finished.
- L65 _private prototype_ `bool ComputeCentroidVariance(FWorkload& Workload, int32& Start, int32& ProcessedCount, FVec3& OutAverageCenter, FVec3& OutScaledCenterVariance) const;` — Incrementally compute the variance of the centroids for a workload. Returns true if the computation is finished.
- L146 _private member_ `FConfig Config;`
- L147 _private member_ `TArray<FAabbTreeLeafElement> Elements;`
- L148 _private member_ `TArray<FAabbTreeNode> Nodes;`
- L149 _private member_ `TArray<FAabbTreeLeaf> Leaves;`
- L152 _private member_ `FCentroidSpatialMedianWorkload CentroidSpatialMedianWorkload;` — This data is shared across all workloads since we only ever process one workload at a time. This allows sharing memory/allocations.
- L153 _private member_ `FCentroidVarianceWorkload CentroidVarianceWorkload;`
- L154 _private member_ `FBinnedSurfaceAreaWorkload BinnedSurfaceAreaWorkload;`
- L156 _private member_ `int32 RootIndex = INDEX_NONE;`
- L157 _private member_ `TArray<FWorkload> WorkloadStack;`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FConfig`  
`struct FConfig`  
_L17-25_
- L19 _public member_ `EPartitioningMethod PartitioningMethod = EPartitioningMethod::CentroidVariance;`
- L21 _public member_ `int32 BatchSize = std::numeric_limits<int32>::max();`
- L22 _public member_ `int32 MaxElementsPerLeaf = 8;`
- L23 _public member_ `int32 MaxTreeDepth = 200;`
- L24 _public member_ `int32 SurfaceAreaHeuristicBinCount = 8;`

#### enum `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::EState`  
`enum class EState`  
_L42-47_
- L44 _public enumerator_ `Setup`
- L45 _public enumerator_ `Partition`
- L46 _public enumerator_ `Finish`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FMedianWorkloadCommon`  
`struct FMedianWorkloadCommon`  
_L67-81_
- L74 _public member_ `EPartitionState PartitionState = EPartitionState::Select;`
- L76 _public member_ `FAABB3 CentroidAabb = FAABB3::EmptyAABB();`
- L77 _public member_ `int32 Start = 0;`
- L78 _public member_ `int32 End = 0;`
- L79 _public member_ `int32 SplitAxis = 0;`
- L80 _public member_ `FReal SplitPosition = 0;`

#### enum `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FMedianWorkloadCommon::EPartitionState`  
`enum class EPartitionState`  
_L69-73_
- L71 _public enumerator_ `Select`
- L72 _public enumerator_ `Partition`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FCentroidSpatialMedianWorkload`  
`struct FCentroidSpatialMedianWorkload : public FMedianWorkloadCommon`  
_L83-91_
- inherits: `FMedianWorkloadCommon`
- L85 _public prototype_ `void Reset();`
- L86 _public prototype_ `void Run(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L89 _private prototype_ `void RunSelect(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L90 _private prototype_ `void RunPartition(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FCentroidVarianceWorkload`  
`struct FCentroidVarianceWorkload : public FMedianWorkloadCommon`  
_L93-105_
- inherits: `FMedianWorkloadCommon`
- L95 _public prototype_ `void Reset();`
- L96 _public prototype_ `void Run(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L99 _private prototype_ `void RunSelect(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L100 _private prototype_ `void RunPartition(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L102 _private member_ `FVec3 AverageCenter = FVec3::Zero();`
- L103 _private member_ `FVec3 ScaledCenterVariance = FVec3::Zero();`
- L104 _private member_ `int32 ProcessedCount = 0;`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FBinnedSurfaceAreaWorkload`  
`struct FBinnedSurfaceAreaWorkload`  
_L107-136_
- L109 _public prototype_ `void Reset();`
- L110 _public prototype_ `void Run(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L113 _private prototype_ `void RunComputeBounds(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L114 _private prototype_ `void RunComputeBins(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L115 _private prototype_ `void RunPartition(FStaticAabbTreeTimeSlicer& TimeSlicer, FWorkload& Workload);`
- L123 _private member_ `EPartitionState State = EPartitionState::ComputeBounds;`
- L125 _private member_ `FAABB3 CentroidAabb = FAABB3::EmptyAABB();`
- L126 _private member_ `TArray<FAabbBin> Bins;`
- L127 _private member_ `TArray<int32> BinIndices;`
- L128 _private member_ `TArray<FBinSplitPlane> BinSplitPlanes;`
- L129 _private member_ `FReal BoundsLowerBound = 0;`
- L130 _private member_ `FReal InvBoundsSize = 0;`
- L131 _private member_ `int32 Start = 0;`
- L132 _private member_ `int32 End = 0;`
- L133 _private member_ `int32 SplitAxis = 0;`
- L134 _private member_ `int32 BinSplitIndex = 0;`
- L135 _private member_ `int32 SplitIndex = 0;`

#### enum `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FBinnedSurfaceAreaWorkload::EPartitionState`  
`enum class EPartitionState`  
_L117-122_
- L119 _public enumerator_ `ComputeBounds`
- L120 _public enumerator_ `ComputeBins`
- L121 _public enumerator_ `Partition`

#### struct `Chaos::SpatialPartition::AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer::FWorkload`  
`struct FWorkload`  
_L138-144_
- L140 _public member_ `TArrayView<const FAabbTreeLeafElement> Elements;`
- L141 _public member_ `int32 NodeIndex = INDEX_NONE;`
- L142 _public member_ `int32 Depth = 0;`
- L143 _public member_ `EState State = EState::Setup;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L11 _namespace_ `namespace AabbTreeAlgorithm` (scope `Chaos::SpatialPartition`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Collections/DefaultSpatialPartitionCollection.h` (Public)


#### class `Chaos::SpatialPartition::FDefaultSpatialPartitionCollection`  
`class FDefaultSpatialPartitionCollection : public ISpatialPartition`  
_L19-166_
- inherits: `ISpatialPartition`
- desc: The default spatial partition collection to manage dynamic and static objects. Static object updates are handled by moving objects between clean/dirty states where the structures can be fully rebuilt at a larger cost. This is meant to be the default implementation for Chaos.
- L28 _public prototype_ `FDefaultSpatialPartitionCollection(const FConfig& Config = FConfig());`
- L29 _public prototype_ `FDefaultSpatialPartitionCollection(FDefaultSpatialPartitionCollection&&) = default;`
- L30 _public prototype_ `virtual ~FDefaultSpatialPartitionCollection() override = default;`
- L32 _public prototype_ `FDefaultSpatialPartitionCollection& operator=(FDefaultSpatialPartitionCollection&&) = default;`
- L34 _public prototype_ `virtual void Insert(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& OutHandle) override;`
- L35 _public prototype_ `virtual void Update(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& InOutHandle) override;`
- L36 _public prototype_ `virtual void Remove(FSpatialHandle& InOutHandle) override;`
- L38 _public prototype_ `virtual void Overlap(const FOverlapQueryData& QueryData, FOverlapVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L39 _public prototype_ `virtual void Raycast(const FRaycastQueryData& QueryData, FRaycastVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L40 _public prototype_ `virtual void Sweep(const FSweepQueryData& QueryData, FSweepVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L42 _public prototype_ `virtual bool NeedsRebuilding() const override;`
- L43 _public prototype_ `virtual ERebuildStatus Rebuild() override;`
- L59 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EInternalCategory);`
- L68 _private typedef_ `using FEntryArray = Chaos::THandleArray<FEntry>;`
- L69 _private typedef_ `using FEntryHandle = typename FEntryArray::FHandle;`
- L98 _private typedef_ `using FInternalOverlapVisitor = TInternalVisitor<FOverlapVisitor, FOverlapQueryRuntimeData>;`
- L99 _private typedef_ `using FInternalRaycastVisitor = TInternalVisitor<FRaycastVisitor, FRaycastQueryRuntimeData>;`
- L100 _private typedef_ `using FInternalSweepVisitor = TInternalVisitor<FSweepVisitor, FSweepQueryRuntimeData>;`
- L103 _private function_ `template <typename SpatialPartitionType> static EVisitResult Query(const SpatialPartitionType& SpatialPartition, FOverlapQueryRuntimeData& QueryRuntimeData, FOverlapVisitor& Visitor)`
- L109 _private function_ `template <typename SpatialPartitionType> static EVisitResult Query(const SpatialPartitionType& SpatialPartition, FRaycastQueryRuntimeData& QueryRuntimeData, FRaycastVisitor& Visitor)`
- L115 _private function_ `template <typename SpatialPartitionType> static EVisitResult Query(const SpatialPartitionType& SpatialPartition, FSweepQueryRuntimeData& QueryRuntimeData, FSweepVisitor& Visitor)`
- L121 _private function_ `template <typename QueryRuntimeDataType, typename VisitorType> void QueryInternal(const ESpatialCategoryMask QueryCategoryMask, QueryRuntimeDataType& QueryRuntimeData, VisitorType& Visitor) const`
- L148 _private prototype_ `bool IsGlobal(const FAABB3& Aabb) const;`
- L149 _private prototype_ `static EInternalCategory ToInternalCategory(const ESpatialCategory& Category, const bool bDirty, const bool bGlobal);`
- L150 _private prototype_ `static EInternalCategory SetOrClearFlag(const EInternalCategory Flags, const EInternalCategory Flag, bool bState);`
- L151 _private prototype_ `const FEntry* GetEntryFromHandleValue(uint32 Index) const;`
- L152 _private prototype_ `bool IsRebuilding() const;`
- L154 _private prototype_ `void InsertInternal(const FEntryHandle& EntryHandle, const FAABB3& Aabb, const EInternalCategory Category, FSpatialHandle& OutHandle);`
- L155 _private prototype_ `void UpdateInternal(const FEntryHandle& EntryHandle, const FAABB3& Aabb, const EInternalCategory Category, FSpatialHandle& InOutHandle);`
- L156 _private prototype_ `void RemoveInternal(const EInternalCategory Category, FSpatialHandle& InOutHandle);`
- L158 _private member_ `FEntryArray Entries;`
- L159 _private member_ `FStaticAabbTree StaticTree;`
- L160 _private member_ `FDynamicAabbTree StaticDirty;`
- L161 _private member_ `FNSquaredAabb StaticGlobal;`
- L162 _private member_ `FDynamicAabbTree DynamicTree;`
- L163 _private member_ `FNSquaredAabb DynamicGlobal;`
- L164 _private member_ `TUniquePtr<FStaticAabbTree::FRebuildContext> StaticRebuildContext;`
- L165 _private member_ `TArray<FEntryHandle> DirtyStaticEntries;`

#### struct `Chaos::SpatialPartition::FDefaultSpatialPartitionCollection::FConfig`  
`struct FConfig`  
_L22-26_
- L24 _public member_ `FStaticAabbTree::FConfig StaticConfig;`
- L25 _public member_ `FDynamicAabbTree::FConfig DynamicConfig;`

#### enum `Chaos::SpatialPartition::FDefaultSpatialPartitionCollection::EInternalCategory`  
`enum class EInternalCategory : uint8`  
_L47-58_
- L49 _public enumerator_ `None = 0`
- L50 _public enumerator_ `Static = 1 << 1`
- L51 _public enumerator_ `Dynamic = 1 << 2`
- L52 _public enumerator_ `Dirty = 1 << 3`
- L53 _public enumerator_ `Global = 1 << 4`
- L54 _public enumerator_ `StaticDirty = Static | Dirty`
- L55 _public enumerator_ `StaticGlobal = Static | Global`
- L56 _public enumerator_ `DynamicDirty = Dynamic | Dirty`
- L57 _public enumerator_ `DynamicGlobal = Dynamic | Global`

#### struct `Chaos::SpatialPartition::FDefaultSpatialPartitionCollection::FEntry`  
`struct FEntry`  
_L60-67_
- L62 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L63 _public member_ `FSpatialHandle Handle;`
- L64 _public member_ `FUserDataType UserData = INDEX_NONE;`
- L65 _public member_ `ESpatialCategory Category = ESpatialCategory::Invalid;`
- L66 _public member_ `EInternalCategory InternalCategory = EInternalCategory::None;`

#### struct `Chaos::SpatialPartition::FDefaultSpatialPartitionCollection::TInternalVisitor`  
`template <typename InternalVisitorType, typename QueryRuntimeDataType> struct TInternalVisitor : public TVisitorAdapter<TInternalVisitor<InternalVisitorType, QueryRuntimeDataType>, InternalVisitorType, QueryRuntimeDataType>`  
_L72-96_
- inherits: `TVisitorAdapter<TInternalVisitor<InternalVisitorType,QueryRuntimeDataType>,InternalVisitorType,QueryRuntimeDataType>`
- L74 _public function_ `TInternalVisitor(const FDefaultSpatialPartitionCollection* Collection, const ESpatialCategoryMask QueryCategoryMask, InternalVisitorType& ExternalVisitor) : Collection(Collection) , ExternalVisitor(ExternalVisitor) , QueryCategoryMask(QueryCategoryMask)`
- L81 _public function_ `EVisitResult Visit(const FUserDataType& UserData, QueryRuntimeDataType& QueryRuntimeData)`
- L93 _public member_ `const FDefaultSpatialPartitionCollection* Collection = nullptr;`
- L94 _public member_ `InternalVisitorType& ExternalVisitor;`
- L95 _public member_ `ESpatialCategoryMask QueryCategoryMask;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L13 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Collections/NSquaredAabbCollection.h` (Public)


#### class `Chaos::SpatialPartition::FNSquaredAabbCollection`  
`class FNSquaredAabbCollection : public ISpatialPartition`  
_L16-70_
- inherits: `ISpatialPartition`
- desc: A simple test spatial partition collection that shows basic usage. Mostly a proof of concept and used to validate basic tests. Can also be used for validation when comparing against other spatial partitions due to its simplicity.
- L19 _public prototype_ `virtual ~FNSquaredAabbCollection() override = default;`
- L21 _public prototype_ `FNSquaredAabbCollection& operator=(const FNSquaredAabbCollection&) = default;`
- L22 _public prototype_ `FNSquaredAabbCollection& operator=(FNSquaredAabbCollection&&) = default;`
- L24 _public prototype_ `virtual void Insert(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& OutHandle) override;`
- L25 _public prototype_ `virtual void Update(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& InOutHandle) override;`
- L26 _public prototype_ `virtual void Remove(FSpatialHandle& InOutHandle) override;`
- L28 _public prototype_ `virtual void Overlap(const FOverlapQueryData& QueryData, FOverlapVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L29 _public prototype_ `virtual void Raycast(const FRaycastQueryData& QueryData, FRaycastVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L30 _public prototype_ `virtual void Sweep(const FSweepQueryData& QueryData, FSweepVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L41 _private typedef_ `using FEntryArray = Chaos::THandleArray<FEntry>;`
- L42 _private typedef_ `using FEntryHandle = typename FEntryArray::FHandle;`
- L44 _private prototype_ `EVisitResult Query(int32 CategoryIndex, FOverlapQueryRuntimeData& QueryRuntimeData, FOverlapVisitor& Visitor) const;`
- L45 _private prototype_ `EVisitResult Query(int32 CategoryIndex, FRaycastQueryRuntimeData& QueryRuntimeData, FRaycastVisitor& Visitor) const;`
- L46 _private prototype_ `EVisitResult Query(int32 CategoryIndex, FSweepQueryRuntimeData& QueryRuntimeData, FSweepVisitor& Visitor) const;`
- L49 _private function_ `template <typename ... ArgTypes> void RunQueries(ESpatialCategoryMask CategoryMask, ArgTypes... Args) const`
- L65 _private prototype_ `bool ValidateCategory(const ESpatialCategory Category) const;`
- L67 _private member_ `static constexpr int32 SpatialPartitionCount = 3;`
- L68 _private member_ `FEntryArray Entries;`
- L69 _private member_ `FNSquaredAabb SpatialPartitions[SpatialPartitionCount];`

#### struct `Chaos::SpatialPartition::FNSquaredAabbCollection::FEntry`  
`struct FEntry`  
_L33-39_
- L35 _public member_ `FUserDataType UserData = INDEX_NONE;`
- L36 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L37 _public member_ `FSpatialClassification Classification;`
- L38 _public member_ `FSpatialHandle Handle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Common.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L14 _typedef_ `using FReal = Chaos::FReal;` (scope `Chaos::SpatialPartition`) — Bring some types into our namespace.
- L15 _typedef_ `using FVec3 = Chaos::FVec3;` (scope `Chaos::SpatialPartition`)
- L16 _typedef_ `using FAABB3 = Chaos::FAABB3;` (scope `Chaos::SpatialPartition`)
- L20 _typedef_ `using FUserDataType = int32;` (scope `Chaos::SpatialPartition`) — The user data type is what is inserted into any spatial partition. This is a typedef to allow us to easily swap/upgrade if needed.

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/ISpatialPartition.h` (Public)


#### class `Chaos::SpatialPartition::ISpatialPartition`  
`class ISpatialPartition`  
_L12-34_
- L15 _public prototype_ `virtual ~ISpatialPartition() = default;`
- L17 _public prototype_ `virtual void Insert(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& OutHandle) = 0;`
- L18 _public prototype_ `virtual void Update(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& InOutHandle) = 0;`
- L19 _public prototype_ `virtual void Remove(FSpatialHandle& InOutHandle) = 0;`
- L21 _public prototype_ `virtual void Overlap(const FOverlapQueryData& QueryData, FOverlapVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const = 0;`
- L22 _public prototype_ `virtual void Raycast(const FRaycastQueryData& QueryData, FRaycastVisitor& Visitor, ESpatialCategoryMask CategCategoryMaskory = ESpatialCategoryMask::All) const = 0;`
- L23 _public prototype_ `virtual void Sweep(const FSweepQueryData& QueryData, FSweepVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const = 0;`
- L30 _public function_ `virtual bool NeedsRebuilding() const`
- L31 _public function_ `virtual ERebuildStatus Rebuild()`

#### enum `Chaos::SpatialPartition::ISpatialPartition::ERebuildStatus`  
`enum class ERebuildStatus`  
_L25-29_
- L27 _public enumerator_ `Continue`
- L28 _public enumerator_ `Finished`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Library/AabbTreeLeaf.h` (Public)


#### struct `Chaos::SpatialPartition::FAabbTreeLeafElement`  
`struct FAabbTreeLeafElement`  
_L10-17_
- L12 _public prototype_ `FVec3 GetCenter() const;`
- L13 _public prototype_ `const FAABB3& GetAabb() const;`
- L15 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L16 _public member_ `int32 Index = INDEX_NONE;`

#### struct `Chaos::SpatialPartition::FAabbTreeLeaf`  
`struct FAabbTreeLeaf`  
_L19-27_
- L21 _public prototype_ `void Build(const TArrayView<const FAabbTreeLeafElement>& InElements, const int32 InNodeIndex);`
- L22 _public prototype_ `void RecomputeAabb();`
- L24 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L25 _public member_ `TArray<FAabbTreeLeafElement> Elements;`
- L26 _public member_ `int32 NodeIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Library/AabbTreeNode.h` (Public)


#### struct `Chaos::SpatialPartition::FAabbTreeNode`  
`struct FAabbTreeNode`  
_L13-25_
- L15 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L16 _public member_ `int32 Parent = INDEX_NONE;`
- L17 _public member_ `int32 Left = INDEX_NONE;`
- L18 _public member_ `int32 Right = INDEX_NONE;`
- L20 _public member_ `int32 UserData = INDEX_NONE;` — Note: The user data could be packed into the Right since it's only valid on leaves. Currently the node is 64 bytes with this so it's unneeded.
- L23 _public member_ `UE_INTERNAL TArray<FAabbTreeNode>* DebugNodeList = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Library/DynamicAabbTree.h` (Public)


#### class `Chaos::SpatialPartition::FDynamicAabbTree`  
`class FDynamicAabbTree`  
_L15-72_
- desc: A binary tree of aabbs that allows efficient runtime changes. The tree will attempt to balance itself for optimal query performance (typically a surface area heuristic). Insertion, Update, and Removal are typical log(n). Queries are also typically log(n).
- L30 _public prototype_ `FDynamicAabbTree() = default;`
- L31 _public prototype_ `FDynamicAabbTree(const FConfig& Config);`
- L32 _public prototype_ `FDynamicAabbTree(const FDynamicAabbTree&) = default;`
- L33 _public prototype_ `FDynamicAabbTree(FDynamicAabbTree&&) = default;`
- L35 _public prototype_ `FDynamicAabbTree& operator=(const FDynamicAabbTree&) = default;`
- L36 _public prototype_ `FDynamicAabbTree& operator=(FDynamicAabbTree&&) = default;`
- L39 _public prototype_ `void Insert(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& OutHandle);` — Inserts an object with the given aabb. The aabb will be expanded by the PaddingFactor of the config.
- L41 _public prototype_ `void Insert(const FUserDataType& UserData, const FAABB3& Aabb, const FAABB3& ExpandedAabb, FSpatialHandle& OutHandle);` — Inserts an object with the given aabb and expanded aabb. The expanded aabb is used to determine the true node size.
- L43 _public prototype_ `void Update(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& InOutHandle);` — Updates an object in the tree, possibly performing a rebalance.
- L46 _public prototype_ `void Update(const FUserDataType& UserData, const FAABB3& Aabb, const FAABB3& ExpandedAabb, FSpatialHandle& InOutHandle);` — Updates an object in the tree. If the given aabb is contained within the old aabb, no work will be done. Otherwise rebalancing will happen using the expanded aabb.
- L47 _public prototype_ `void Remove(FSpatialHandle& InOutHandle);`
- L50 _public prototype_ `bool CheckNeedsUpdate(const FAABB3& Aabb, const FSpatialHandle& InHandle);` — Checks if an update is needed. An update is needed if the handle's node does not fully contains the given aabb.
- L52 _public prototype_ `EVisitResult Overlap(FOverlapQueryRuntimeData& QueryData, FOverlapVisitor& Visitor) const;`
- L53 _public prototype_ `EVisitResult Raycast(FRaycastQueryRuntimeData& QueryData, FRaycastVisitor& Visitor) const;`
- L54 _public prototype_ `EVisitResult Sweep(FSweepQueryRuntimeData& QueryData, FSweepVisitor& Visitor) const;`
- L55 _public prototype_ `void SelfQuery(FSelfQueryVisitor& Visitor) const;`
- L57 _public prototype_ `UE_INTERNAL void Dump(TArray<FAabbTreeNode>& OutData, int32& OutRootIndex) const;`
- L60 _private prototype_ `FAABB3 Expand(const FAABB3& Aabb) const;`
- L61 _private prototype_ `void InsertLeaf(int32 LeafIndex, bool bDoRotation);`
- L62 _private prototype_ `void RemoveLeaf(int32 LeafIndex, bool bDoRotation);`
- L64 _private prototype_ `void SelfQuery(FSelfQueryVisitor& Visitor, const int32 NodeIndex) const;`
- L65 _private prototype_ `void SelfQuery(FSelfQueryVisitor& Visitor, const int32 NodeIndex0, const int32 NodeIndex1) const;`
- L67 _private member_ `FConfig Config;`
- L68 _private member_ `int32 RootIndex = INDEX_NONE;`
- L69 _private member_ `int32 FreeListHeadIndex = INDEX_NONE;`
- L70 _private member_ `TArray<FAabbTreeNode> Nodes;`
- L71 _private member_ `TArray<TPair<int32, FReal>> PriorityQueue;`

#### struct `Chaos::SpatialPartition::FDynamicAabbTree::FConfig`  
`struct FConfig`  
_L18-28_
- L25 _public member_ `FReal PaddingFactor = 0;`
- L26 _public member_ `bool bRebalanceOnRemove = false;`
- L27 _public member_ `ESearchAlgorithm SearchAlgorithm = ESearchAlgorithm::BranchAndBound;`

#### enum `Chaos::SpatialPartition::FDynamicAabbTree::FConfig::ESearchAlgorithm`  
`enum class ESearchAlgorithm`  
_L20-24_
- L22 _public enumerator_ `Greedy`
- L23 _public enumerator_ `BranchAndBound`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Library/NSquaredAabb.h` (Public)


#### class `Chaos::SpatialPartition::FNSquaredAabb`  
`class FNSquaredAabb`  
_L15-46_
- desc: A simple spatial partition that just stores a list of aabbs. Self query is O(n^2) and all other queries are O(n). This is exceptionally useful for comparing correctness due to its simplicity. This also is useful for cases where the known data set is small or cases like the "global object list".
- L18 _public prototype_ `void Insert(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& OutHandle);`
- L19 _public prototype_ `void Update(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& InOutHandle);`
- L20 _public prototype_ `void Remove(FSpatialHandle& InOutHandle);`
- L22 _public prototype_ `EVisitResult Overlap(FOverlapQueryRuntimeData& QueryData, FOverlapVisitor& Visitor) const;`
- L23 _public prototype_ `EVisitResult Raycast(FRaycastQueryRuntimeData& QueryData, FRaycastVisitor& Visitor) const;`
- L24 _public prototype_ `EVisitResult Sweep(FSweepQueryRuntimeData& QueryData, FSweepVisitor& Visitor) const;`
- L25 _public prototype_ `void SelfQuery(FSelfQueryVisitor& Visitor) const;`
- L35 _private prototype_ `int32 AllocateEntry();`
- L36 _private prototype_ `void DeallocateEntry(int32 Index);`
- L39 _private prototype_ `template <typename QueryDataType, typename VisitorType> EVisitResult QueryImpl(QueryDataType& QueryData, VisitorType& Visitor) const;`
- L40 _private prototype_ `bool ShouldVisitEntry(const FEntry& Entry, const FOverlapQueryRuntimeData& QueryData) const;`
- L41 _private prototype_ `bool ShouldVisitEntry(const FEntry& Entry, const FRaycastQueryRuntimeData& QueryData) const;`
- L42 _private prototype_ `bool ShouldVisitEntry(const FEntry& Entry, const FSweepQueryRuntimeData& QueryData) const;`
- L44 _private member_ `TArray<int32> FreeIndices;`
- L45 _private member_ `TArray<FEntry> Entries;`

#### struct `Chaos::SpatialPartition::FNSquaredAabb::FEntry`  
`struct FEntry`  
_L28-33_
- L30 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L31 _public member_ `FUserDataType UserData = INDEX_NONE;`
- L32 _public member_ `bool bIsUsed = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Library/StaticAabbTree.h` (Public)


#### class `Chaos::SpatialPartition::FStaticAabbTree`  
`class FStaticAabbTree`  
_L22-137_
- desc: An aabb tree meant for infrequently moving / updated objects. Building this tree is more computationally expensive than its dynamic counterpart, but should produce a better quality tree. When Insert/Updating/Removing objects, there are two primary APIs: 1. Deferred: does the minimal work to make sure the tree will be correct the next build and won't return removed objects. 2. Incremental (TODO): does incremental changes to the tree (similar to the dynamic tree) to ensure everything is up-to-date for all queries. In general, incremental changes are faster to perform but will result in a slightly worse quality tree. Thus, it is recommended to perform periodic full rebuilds.
- L25 _public typedef_ `using ERebuildStatus = ISpatialPartition::ERebuildStatus;`
- L53 _public prototype_ `FStaticAabbTree();`
- L54 _public prototype_ `FStaticAabbTree(const FConfig& Config);`
- L55 _public prototype_ `FStaticAabbTree(const FStaticAabbTree&) = default;`
- L56 _public prototype_ `FStaticAabbTree(FStaticAabbTree&&) = default;`
- L58 _public prototype_ `FStaticAabbTree& operator=(const FStaticAabbTree&) = default;`
- L59 _public prototype_ `FStaticAabbTree& operator=(FStaticAabbTree&&) = default;`
- L62 _public prototype_ `void InsertDeferred(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& OutHandle);` — Inserts an object such that it will be included the next time the tree is built. This object will not be returned in any queries.
- L65 _public prototype_ `bool UpdateIfWithinLeaf(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& InOutHandle);` — Updates only if the object stays within the old leaf node.
- L68 _public prototype_ `void UpdateDeferred(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& InOutHandle);` — Updates the object such that its new aabb will be reflected in the next build. Any changes to the user data will be immediate, however changes to the aabb will be deferred.
- L73 _public prototype_ `void RemoveMinimal(FSpatialHandle& InOutHandle);` — Does the minimal work to remove an entry so it won't be returned from any queries. This will not shrink any aabbs or remove empty nodes. The quality of the tree will deteriorate over time if it is not periodically rebuilt.
- L75 _public prototype_ `void BeginRebuild(FRebuildContext& Context) const;`
- L80 _public prototype_ `void CommitRebuild(FRebuildContext& Context);` — Commits the result of a tree rebuild. The context must be from this same tree. The only change guaranteed to be observed correctly during a rebuild is a remove. Insert and Update will typically be treated like a deferred operation, but some combined operations (e.g. remove + insert) will be caught in an in-between state. A subsequent rebuild is necessary to pickup inserts/updates.
- L82 _public prototype_ `EVisitResult Overlap(FOverlapQueryRuntimeData& QueryData, FOverlapVisitor& Visitor) const;`
- L83 _public prototype_ `EVisitResult Raycast(FRaycastQueryRuntimeData& QueryData, FRaycastVisitor& Visitor) const;`
- L84 _public prototype_ `EVisitResult Sweep(FSweepQueryRuntimeData& QueryData, FSweepVisitor& Visitor) const;`
- L97 _public prototype_ `UE_INTERNAL FStats ComputeStats() const;`
- L100 _public prototype_ `UE_INTERNAL void Dump(TArray<FAabbTreeNode>& OutNodes, int32& OutRootNodeIndex, TArray<FAabbTreeLeaf>& OutLeaves) const;` — Returns the structure of the tree, mostly for tests. The leaf elements will have the user data in the Index field.
- L110 _private prototype_ `int32 AllocateEntry();`
- L111 _private prototype_ `void UpdateEntry(const int32 EntryIndex, const FUserDataType& UserData, const FAABB3& Aabb);`
- L112 _private prototype_ `void FreeEntry(const int32 EntryIndex);`
- L113 _private prototype_ `int32 AllocateNode();`
- L114 _private prototype_ `void FreeNode(const int32 NodeIndex);`
- L115 _private prototype_ `int32 AllocateLeaf();`
- L116 _private prototype_ `void FreeLeaf(const int32 LeafIndex);`
- L118 _private prototype_ `FStats ComputeStats(const int32 NodeIndex) const;`
- L120 _private prototype_ `void GatherUsedElements(TArray<FAabbTreeLeafElement>& Elements) const;`
- L121 _private prototype_ `void RecomputeElementLeafIndices();`
- L123 _private prototype_ `void RemoveEntryFromLeaf(const int32 EntryIndex);`
- L126 _private prototype_ `template <typename QueryDataType, typename VisitorType> EVisitResult CastLeafCallback(const FAabbTreeNode& Node, QueryDataType& QueryData, VisitorType& Visitor) const;`
- L128 _private member_ `FConfig Config;`
- L129 _private member_ `int32 EntriesFreeListHead = INDEX_NONE;`
- L130 _private member_ `TArray<FEntry> Entries;`
- L131 _private member_ `TBitArray<> UsedEntries;`
- L132 _private member_ `int32 RootIndex = INDEX_NONE;`
- L133 _private member_ `int32 NodesFreeListHead = INDEX_NONE;`
- L134 _private member_ `TArray<FAabbTreeNode> Nodes;`
- L135 _private member_ `int32 LeavesFreeListHead = INDEX_NONE;`
- L136 _private member_ `TArray<FAabbTreeLeaf> Leaves;`

#### struct `Chaos::SpatialPartition::FStaticAabbTree::FConfig`  
`struct FConfig`  
_L27-35_
- L29 _public member_ `EPartitioningMethod PartitioningMethod = EPartitioningMethod::SurfaceArea;`
- L30 _public member_ `int32 BatchSize = std::numeric_limits<int32>::max();`
- L31 _public member_ `int32 MaxElementsPerLeaf = 8;`
- L32 _public member_ `int32 MaxTreeDepth = 200;`
- L33 _public member_ `int32 SurfaceAreaHeuristicBinCount = 8;`
- L34 _public member_ `double TargetProcessingTimeInSeconds = 0.001;`

#### struct `Chaos::SpatialPartition::FStaticAabbTree::FRebuildContext`  
`struct FRebuildContext`  
_L38-51_
- desc: Stores information about a pending rebuild of the tree.
- L41 _public prototype_ `FRebuildContext();`
- L42 _public prototype_ `FRebuildContext(const FStaticAabbTree* OwningTree, AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer&& TimeSlicer);`
- L44 _public prototype_ `ERebuildStatus Run();`
- L48 _private member_ `const FStaticAabbTree* OwningTree = nullptr;`
- L49 _private member_ `AabbTreeAlgorithm::FStaticAabbTreeTimeSlicer TimeSlicer;`
- L50 _private member_ `double TargetTimeSeconds = 0;`

#### struct `Chaos::SpatialPartition::FStaticAabbTree::FStats`  
`struct FStats`  
_L86-96_
- L88 _public member_ `int32 MinHeight = 0;`
- L89 _public member_ `int32 MaxHeight = 0;`
- L90 _public member_ `int32 MinElementsPerLeaf = 0;`
- L91 _public member_ `int32 MaxElementsPerLeaf = 0;`
- L93 _public member_ `FReal NodeSurfaceArea = 0;` — Surface area of all the nodes
- L95 _public member_ `FReal TotalSurfaceArea = 0;` — Surface area of everything (nodes + leaf elements)

#### struct `Chaos::SpatialPartition::FStaticAabbTree::FEntry`  
`struct FEntry`  
_L103-108_
- L105 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L106 _public member_ `FUserDataType UserData = INDEX_NONE;`
- L107 _public member_ `int32 LeafIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/QueryData.h` (Public)


#### struct `Chaos::SpatialPartition::FOverlapQueryData`  
`struct FOverlapQueryData`  
_L10-13_
- L12 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`

#### struct `Chaos::SpatialPartition::FRaycastQueryData`  
`struct FRaycastQueryData`  
_L15-20_
- L17 _public member_ `FVec3 Start = FVec3::Zero();`
- L18 _public member_ `FVec3 Direction = FVec3::Zero();`
- L19 _public member_ `FReal Length = 0;`

#### struct `Chaos::SpatialPartition::FSweepQueryData`  
`struct FSweepQueryData`  
_L22-28_
- L24 _public member_ `FVec3 Start = FVec3::Zero();`
- L25 _public member_ `FVec3 Direction = FVec3::Zero();`
- L26 _public member_ `FVec3 HalfExtents = FVec3::Zero();`
- L27 _public member_ `FReal Length = 0;`

#### struct `Chaos::SpatialPartition::FQueryRuntimeData`  
`struct FQueryRuntimeData`  
_L30-43_
- L32 _public prototype_ `FQueryRuntimeData() = default;`
- L33 _public prototype_ `FQueryRuntimeData(const FVec3& Dir, const FReal Length);`
- L35 _public prototype_ `void SetLength(const FReal Length);`
- L37 _public member_ `FVec3 InvDir = FVec3::Zero();`
- L39 _public member_ `bool bParallel[3] = {false};`
- L41 _public member_ `FReal CurrentLength = 0;`
- L42 _public member_ `FReal InvCurrentLength = 0;`

#### struct `Chaos::SpatialPartition::FOverlapQueryRuntimeData`  
`struct FOverlapQueryRuntimeData`  
_L45-61_
- L47 _public prototype_ `FOverlapQueryRuntimeData(const FOverlapQueryData& InputData);`
- L48 _public prototype_ `FOverlapQueryRuntimeData(const FAABB3& Aabb);`
- L50 _public prototype_ `FOverlapQueryRuntimeData(const FOverlapQueryRuntimeData&) = default;`
- L51 _public prototype_ `FOverlapQueryRuntimeData(FOverlapQueryRuntimeData&&) = default;`
- L52 _public prototype_ `FOverlapQueryRuntimeData& operator=(const FOverlapQueryRuntimeData&) = default;`
- L53 _public prototype_ `FOverlapQueryRuntimeData& operator=(FOverlapQueryRuntimeData&&) = default;`
- L55 _public prototype_ `const FOverlapQueryData& GetInputData() const;`
- L57 _public prototype_ `bool Test(const FAABB3& Aabb) const;`
- L60 _private member_ `FOverlapQueryData InputData;`

#### struct `Chaos::SpatialPartition::FRaycastQueryRuntimeData`  
`struct FRaycastQueryRuntimeData`  
_L63-82_
- L65 _public prototype_ `FRaycastQueryRuntimeData(const FRaycastQueryData& InputData);`
- L67 _public prototype_ `FRaycastQueryRuntimeData(const FRaycastQueryRuntimeData&) = default;`
- L68 _public prototype_ `FRaycastQueryRuntimeData(FRaycastQueryRuntimeData&&) = default;`
- L69 _public prototype_ `FRaycastQueryRuntimeData& operator=(const FRaycastQueryRuntimeData&) = default;`
- L70 _public prototype_ `FRaycastQueryRuntimeData& operator=(FRaycastQueryRuntimeData&&) = default;`
- L72 _public prototype_ `const FRaycastQueryData& GetInputData() const;`
- L73 _public prototype_ `FReal GetCurrentLength() const;`
- L74 _public prototype_ `void SetCurrentLength(const FReal InLength);`
- L76 _public prototype_ `bool Test(const FAABB3& Aabb) const;`
- L77 _public prototype_ `bool Test(const FAABB3& Aabb, FReal& OutTime) const;`
- L80 _private member_ `FRaycastQueryData InputData;`
- L81 _private member_ `FQueryRuntimeData RuntimeData;`

#### struct `Chaos::SpatialPartition::FSweepQueryRuntimeData`  
`struct FSweepQueryRuntimeData`  
_L84-103_
- L86 _public prototype_ `FSweepQueryRuntimeData(const FSweepQueryData& InputData);`
- L88 _public prototype_ `FSweepQueryRuntimeData(const FSweepQueryRuntimeData&) = default;`
- L89 _public prototype_ `FSweepQueryRuntimeData(FSweepQueryRuntimeData&&) = default;`
- L90 _public prototype_ `FSweepQueryRuntimeData& operator=(const FSweepQueryRuntimeData&) = default;`
- L91 _public prototype_ `FSweepQueryRuntimeData& operator=(FSweepQueryRuntimeData&&) = default;`
- L93 _public prototype_ `const FSweepQueryData& GetInputData() const;`
- L94 _public prototype_ `FReal GetCurrentLength() const;`
- L95 _public prototype_ `void SetCurrentLength(const FReal InLength);`
- L97 _public prototype_ `bool Test(const FAABB3& Aabb) const;`
- L98 _public prototype_ `bool Test(const FAABB3& Aabb, FReal& OutTime) const;`
- L101 _private member_ `FSweepQueryData InputData;`
- L102 _private member_ `FQueryRuntimeData RuntimeData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/SpatialClassification.h` (Public)


#### enum `Chaos::SpatialPartition::ESpatialCategory`  
`enum class ESpatialCategory : uint8`  
_L14-21_
- desc: Used to separate objects into different buckets based upon common usage/movement patterns. Currently just used to separate out dynamic, static, etc...
- L16 _public enumerator_ `Invalid = static_cast<uint8>(-1)`
- L17 _public enumerator_ `Static = 0`
- L18 _public enumerator_ `Kinematic = 1`
- L19 _public enumerator_ `Dynamic = 2`
- L20 _public enumerator_ `Count`

#### enum `Chaos::SpatialPartition::ESpatialCategoryMask`  
`enum class ESpatialCategoryMask : uint8`  
_L22-29_
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `Static = 1 << 0`
- L26 _public enumerator_ `Kinematic = 1 << 1`
- L27 _public enumerator_ `Dynamic = 1 << 2`
- L28 _public enumerator_ `All = (1 << 3) - 1`

#### struct `Chaos::SpatialPartition::FSpatialClassification`  
`struct FSpatialClassification`  
_L38-56_
- desc: Contains information used to specify how a spatial partition should treat an object when it's inserted/updated/removed. Currently, this only contains the category, but this may be extended.
- L40 _public prototype_ `FSpatialClassification() = default;`
- L41 _public prototype_ `FSpatialClassification(ESpatialCategory InCategory);`
- L42 _public prototype_ `FSpatialClassification(const FSpatialClassification&) = default;`
- L43 _public prototype_ `FSpatialClassification(FSpatialClassification&&) = default;`
- L45 _public prototype_ `FSpatialClassification& operator=(const FSpatialClassification&) = default;`
- L46 _public prototype_ `FSpatialClassification& operator=(FSpatialClassification&&) = default;`
- L48 _public prototype_ `ESpatialCategory GetCategory() const;`
- L49 _public prototype_ `void SetCategory(ESpatialCategory InCategory);`
- L52 _private member_ `ESpatialCategory Category = ESpatialCategory::Static;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L30 _prototype_ `ENUM_CLASS_FLAGS(ESpatialCategoryMask);` (scope `Chaos::SpatialPartition`)
- L32 _prototype_ `FString ToString(ESpatialCategory Category);` (scope `Chaos::SpatialPartition`)
- L33 _prototype_ `FString ToString(ESpatialCategoryMask Mask);` (scope `Chaos::SpatialPartition`)
- L34 _prototype_ `ESpatialCategoryMask ToCategoryMask(const ESpatialCategory Category);` (scope `Chaos::SpatialPartition`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/SpatialHandle.h` (Public)


#### struct `Chaos::SpatialPartition::FSpatialHandle`  
`struct FSpatialHandle`  
_L13-21_
- desc: This handle is used by a spatial partition to uniquely identify an insert and provide O(1) lookup times. All subsequent update/remove operations require the same handle to be passed back in. This data is expected to be stored by the user.
- L16 _public prototype_ `UE_INTERNAL int64 GetValue() const;` — Note: These methods should only be used by a spatial partition.
- L17 _public prototype_ `UE_INTERNAL void SetValue(int64 InValue);`
- L20 _private member_ `int64 Value = INDEX_NONE;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSpatialPartitions/Public/ChaosSpatialPartitions/Visitors.h` (Public)


#### enum `Chaos::SpatialPartition::EVisitResult`  
`enum class EVisitResult`  
_L11-11_
- L11 _public enumerator_ `enum class EVisitResult { Continue, Stop }; class FOverlapVisitor { public: typedef EVisitResult(*FCallbackType)(void* CallbackData, const FUserDataType& UserData, FOverlapQueryRuntimeData& QueryData); CHAOSSPATIALPARTITIONS_API FOverlapVisitor(FCallbackType Callback, void* CallbackData);`
- L11 _public enumerator_ `enum class EVisitResult { Continue, Stop }; class FOverlapVisitor { public: typedef EVisitResult(*FCallbackType)(void* CallbackData, const FUserDataType& UserData, FOverlapQueryRuntimeData& QueryData); CHAOSSPATIALPARTITIONS_API FOverlapVisitor(FCallbackType Callback, void* CallbackData);`

#### class `Chaos::SpatialPartition::FOverlapVisitor`  
`class FOverlapVisitor`  
_L13-25_
- L16 _public typedef_ `typedef EVisitResult(*FCallbackType)(void* CallbackData, const FUserDataType& UserData, FOverlapQueryRuntimeData& QueryData);`
- L18 _public prototype_ `FOverlapVisitor(FCallbackType Callback, void* CallbackData);`
- L20 _public prototype_ `EVisitResult Visit(const FUserDataType& UserData, FOverlapQueryRuntimeData& QueryRuntimeData);`
- L23 _private member_ `FCallbackType Callback = nullptr;`
- L24 _private member_ `void* CallbackData = nullptr;`

#### class `Chaos::SpatialPartition::FRaycastVisitor`  
`class FRaycastVisitor`  
_L27-39_
- L30 _public typedef_ `typedef EVisitResult(*FCallbackType)(void* CallbackData, const FUserDataType& UserData, FRaycastQueryRuntimeData& QueryData);`
- L32 _public prototype_ `FRaycastVisitor(FCallbackType Callback, void* CallbackData);`
- L34 _public prototype_ `EVisitResult Visit(const FUserDataType& UserData, FRaycastQueryRuntimeData& QueryRuntimeData);`
- L37 _private member_ `FCallbackType Callback = nullptr;`
- L38 _private member_ `void* CallbackData = nullptr;`

#### class `Chaos::SpatialPartition::FSweepVisitor`  
`class FSweepVisitor`  
_L41-53_
- L44 _public typedef_ `typedef EVisitResult(*FCallbackType)(void* CallbackData, const FUserDataType& UserData, FSweepQueryRuntimeData& QueryData);`
- L46 _public prototype_ `FSweepVisitor(FCallbackType Callback, void* CallbackData);`
- L48 _public prototype_ `EVisitResult Visit(const FUserDataType& UserData, FSweepQueryRuntimeData& QueryRuntimeData);`
- L51 _private member_ `FCallbackType Callback = nullptr;`
- L52 _private member_ `void* CallbackData = nullptr;`

#### class `Chaos::SpatialPartition::FSelfQueryVisitor`  
`class FSelfQueryVisitor`  
_L55-67_
- L58 _public typedef_ `typedef void(*FCallbackType)(void* CallbackData, const FUserDataType& UserData0, const FUserDataType& UserData1);`
- L60 _public prototype_ `FSelfQueryVisitor(FCallbackType Callback, void* CallbackData);`
- L62 _public prototype_ `void Visit(const FUserDataType& UserData0, const FUserDataType& UserData1);`
- L65 _private member_ `FCallbackType Callback = nullptr;`
- L66 _private member_ `void* CallbackData = nullptr;`

#### struct `Chaos::SpatialPartition::TVisitorAdapter`  
`template <typename SelfType, typename InternalVisitorType, typename QueryRuntimeDataType> struct TVisitorAdapter`  
_L72-93_
- desc: Adapters to make it easier to take a class. These expect the class to have a Visit method with the same signature as the underlying visitor type. TODO: Investigate some kind of a concept.
- L74 _public function_ `TVisitorAdapter() : InternalVisitor(&Callback, this)`
- L80 _public function_ `operator InternalVisitorType& ()` — This implicit operator allows the user to pass in the adapter directly.
- L85 _public function_ `static EVisitResult Callback(void* CallbackData, const FUserDataType& UserData, QueryRuntimeDataType& QueryData)`
- L92 _private member_ `InternalVisitorType InternalVisitor;`

#### struct `Chaos::SpatialPartition::TSelfQueryVisitorAdapter`  
`template <typename SelfType> struct TSelfQueryVisitorAdapter`  
_L105-125_
- L107 _public function_ `TSelfQueryVisitorAdapter() : InternalVisitor(&Callback, this)`
- L112 _public function_ `operator FSelfQueryVisitor& ()`
- L117 _public function_ `static void Callback(void* CallbackData, const FUserDataType& UserData0, const FUserDataType& UserData1)`
- L124 _private member_ `FSelfQueryVisitor InternalVisitor;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L96 _typedef_ `template <typename SelfType> using TOverlapVisitorAdapter = TVisitorAdapter<SelfType, FOverlapVisitor, FOverlapQueryRuntimeData>;` (scope `Chaos::SpatialPartition`)
- L99 _typedef_ `template <typename SelfType> using TRaycastVisitorAdapter = TVisitorAdapter<SelfType, FRaycastVisitor, FRaycastQueryRuntimeData>;` (scope `Chaos::SpatialPartition`)
- L102 _typedef_ `template <typename SelfType> using TSweepVisitorAdapter = TVisitorAdapter<SelfType, FSweepVisitor, FSweepQueryRuntimeData>;` (scope `Chaos::SpatialPartition`)
