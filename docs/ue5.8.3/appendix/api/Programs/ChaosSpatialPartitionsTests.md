# Programs / ChaosSpatialPartitionsTests

- module root: `Source/Programs/ChaosSpatialPartitionsTests`
- headers: 14; symbols: 296
- symbol kinds: class=4, function=104, member=64, namespace=26, prototype=56, struct=16, typedef=26
- PrivateDependencyModuleNames: ChaosCore, ChaosSpatialPartitions, ChaosTestHarness, Core, CoreUObject, Engine

### `Source/Programs/ChaosSpatialPartitionsTests/Private/AabbTreeTestHelpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L13 _function_ `inline FAABB3 Union(const FAABB3& Aabb0, const FAABB3& Aabb1)` (scope `Chaos::SpatialPartition`)
- L20 _function_ `inline bool IsValidNodeIndex(int32 NodeIndex)` (scope `Chaos::SpatialPartition`)
- L25 _function_ `inline void Compare(const TArray<FAabbTreeNode>& ExpectedNodes, const int32 ExpectedIndex, const TArray<FAabbTreeNode>& ActualNodes, const int32 ActualIndex)` (scope `Chaos::SpatialPartition`)
- L46 _function_ `inline void BuildNodeList(TArray<FAabbTreeNode>& Nodes, const int32 CountX = 1, const int32 CountY = 1, const int32 CountZ = 1, const FVec3& Spacing = FVec3(1), const FVec3& AabbSize = FVec3(1))` (scope `Chaos::SpatialPartition`)
- L71 _function_ `inline int32 BuildAndAppendNode(TArray<FAabbTreeNode>& Nodes, const int32 LeftIndex, const int32 RightIndex)` (scope `Chaos::SpatialPartition`) — Adds a new node the the node list that is the parent of the given two nodes. This automatically computes the aabb of the parent node from the two children and links them child/parent indices up.
- L89 _function_ `inline int32 BuildSimpleTree(TArray<FAabbTreeNode>& Nodes)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/ChaosTestHarness.h` (Private)
_(no declarations extracted)_

### `Source/Programs/ChaosSpatialPartitionsTests/Private/Collections/LegacySpatialPartitionCollection.h` (Private)


#### class `Chaos::SpatialPartition::FLegacySpatialPartitionCollection`  
`class FLegacySpatialPartitionCollection : public ISpatialPartition`  
_L17-124_
- inherits: `ISpatialPartition`
- desc: A collection that uses the legacy data structures (aabb tree). Used for testing and incremental migration.
- L40 _public prototype_ `FLegacySpatialPartitionCollection(const FConfig& InConfig = FConfig());`
- L41 _public prototype_ `FLegacySpatialPartitionCollection(FLegacySpatialPartitionCollection&&) = default;`
- L42 _public prototype_ `virtual ~FLegacySpatialPartitionCollection() override = default;`
- L44 _public prototype_ `FLegacySpatialPartitionCollection& operator=(FLegacySpatialPartitionCollection&&) = default;`
- L46 _public prototype_ `virtual void Insert(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& OutHandle) override;`
- L47 _public prototype_ `virtual void Update(const FUserDataType& UserData, const FAABB3& Aabb, const FSpatialClassification& Classification, FSpatialHandle& InOutHandle) override;`
- L48 _public prototype_ `virtual void Remove(FSpatialHandle& InOutHandle) override;`
- L50 _public prototype_ `virtual void Overlap(const FOverlapQueryData& QueryData, FOverlapVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L51 _public prototype_ `virtual void Raycast(const FRaycastQueryData& QueryData, FRaycastVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L52 _public prototype_ `virtual void Sweep(const FSweepQueryData& QueryData, FSweepVisitor& Visitor, ESpatialCategoryMask CategoryMask = ESpatialCategoryMask::All) const override;`
- L54 _public prototype_ `virtual bool NeedsRebuilding() const;`
- L55 _public prototype_ `virtual ERebuildStatus Rebuild();`
- L65 _private typedef_ `using FEntryHandleArray = THandleArray<FEntry>;`
- L66 _private typedef_ `using FEntryHandle = typename FEntryHandleArray::FHandle;`
- L67 _private typedef_ `using FConstEntryHandle = typename FEntryHandleArray::FConstHandle;`
- L68 _private typedef_ `using FSpatialVisitor = ISpatialVisitor<int32>;`
- L69 _private typedef_ `using FSpatialAcceleration = ISpatialAcceleration<int32, FReal, 3>;`
- L70 _private typedef_ `using FStaticAabbTreeType = TAABBTree<FUserDataType, TAABBTreeLeafArray<FUserDataType>>;`
- L71 _private typedef_ `using FDynamicAabbTreeType = TAABBTree<FUserDataType, TAABBTreeLeafArray<FUserDataType>>;`
- L88 _private prototype_ `void Query(const FSpatialAcceleration* SpatialAcceleration, FOverlapQueryRuntimeData& QueryRuntimeData, FSpatialVisitor& Visitor) const;`
- L89 _private prototype_ `void Query(const FSpatialAcceleration* SpatialAcceleration, FRaycastQueryRuntimeData& QueryRuntimeData, FSpatialVisitor& Visitor) const;`
- L90 _private prototype_ `void Query(const FSpatialAcceleration* SpatialAcceleration, FSweepQueryRuntimeData& QueryRuntimeData, FSpatialVisitor& Visitor) const;`
- L93 _private function_ `template <typename ... ArgTypes> void RunQueries(ESpatialCategoryMask CategoryMask, ArgTypes... Args) const`
- L114 _private prototype_ `bool TryGetUserData(const TSpatialVisitorData<int32>& Instance, const ESpatialCategoryMask CategoryMask, FUserDataType& OutUserData) const;`
- L115 _private prototype_ `ESpatialCategory GetCategory(const FSpatialClassification& Classification) const;`
- L116 _private prototype_ `FSpatialAcceleration* GetAccelerationStructure(const FSpatialClassification& Classification);`
- L117 _private prototype_ `const FSpatialAcceleration* GetAccelerationStructure(const FSpatialClassification& Classification) const;`
- L119 _private member_ `FConfig Config;`
- L120 _private member_ `FEntryHandleArray Entries;`
- L121 _private member_ `TUniquePtr<FStaticAabbTreeType> StaticAcceleration;`
- L122 _private member_ `TUniquePtr<FDynamicAabbTreeType> DynamicAcceleration;`
- L123 _private member_ `bool bIsTimeSliceRebuilding = false;`

#### struct `Chaos::SpatialPartition::FLegacySpatialPartitionCollection::FConfig`  
`struct FConfig`  
_L20-38_
- L22 _public prototype_ `FConfig();`
- L35 _public member_ `bool bStaticOnly = false;` — Controls if this has split static/dynamic. Used to emulate the legacy mode of non-split structures.
- L36 _public member_ `FSettings StaticSettings;`
- L37 _public member_ `FSettings DynamicSettings;`

#### struct `Chaos::SpatialPartition::FLegacySpatialPartitionCollection::FConfig::FSettings`  
`struct FSettings`  
_L24-32_
- L26 _public member_ `int32 MaxChildrenInLeaf = 500;`
- L27 _public member_ `int32 MaxTreeDepth = 200;`
- L28 _public member_ `FRealSingle MaxPayloadSize = 100000;`
- L29 _public member_ `int32 IterationsPerTimeSlice = 4000;`
- L30 _public member_ `bool bBuildOverlapCache = false;`
- L31 _public member_ `bool bUseDirtyTree = false;`

#### struct `Chaos::SpatialPartition::FLegacySpatialPartitionCollection::FEntry`  
`struct FEntry`  
_L58-63_
- L60 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L61 _public member_ `FSpatialClassification Classification;`
- L62 _public member_ `FUserDataType UserData = INDEX_NONE;`

#### class `Chaos::SpatialPartition::FLegacySpatialPartitionCollection::FLegacyVisitor`  
`class FLegacyVisitor : public FLegacyVisitorBase`  
_L73-86_
- inherits: `FLegacyVisitorBase`
- L76 _public prototype_ `FLegacyVisitor(const FLegacySpatialPartitionCollection* Collection, ESpatialCategoryMask CategoryMask, FOverlapQueryRuntimeData* InQueryData, FOverlapVisitor* InVisitor);`
- L77 _public prototype_ `FLegacyVisitor(const FLegacySpatialPartitionCollection* Collection, ESpatialCategoryMask CategoryMask, FRaycastQueryRuntimeData* InQueryData, FRaycastVisitor* InVisitor);`
- L78 _public prototype_ `FLegacyVisitor(const FLegacySpatialPartitionCollection* Collection, ESpatialCategoryMask CategoryMask, FSweepQueryRuntimeData* InQueryData, FSweepVisitor* InVisitor);`
- L80 _public prototype_ `virtual bool Overlap(const TSpatialVisitorData<int32>& Instance) override;`
- L81 _public prototype_ `virtual bool Raycast(const TSpatialVisitorData<int32>& Instance, FQueryFastData& CurData) override;`
- L82 _public prototype_ `virtual bool Sweep(const TSpatialVisitorData<int32>& Instance, FQueryFastData& CurData) override;`
- L84 _public member_ `const FLegacySpatialPartitionCollection* Collection = nullptr;`
- L85 _public member_ `ESpatialCategoryMask CategoryMask;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/LegacyVisitorBase.h` (Private)


#### class `Chaos::SpatialPartition::FLegacyVisitorBase`  
`class FLegacyVisitorBase : public ISpatialVisitor<int32>`  
_L13-32_
- inherits: `ISpatialVisitor<int32>`
- desc: This class wraps the new visitors with the old visitor API. The old API is not directly implemented as this allows any individual visitor to do their own mapping of the legacy payload to the new user data.
- L16 _public prototype_ `FLegacyVisitorBase(FOverlapQueryRuntimeData* InQueryData, FOverlapVisitor* InVisitor);`
- L17 _public prototype_ `FLegacyVisitorBase(FRaycastQueryRuntimeData* InQueryData, FRaycastVisitor* InVisitor);`
- L18 _public prototype_ `FLegacyVisitorBase(FSweepQueryRuntimeData* InQueryData, FSweepVisitor* InVisitor);`
- L20 _public prototype_ `bool OverlapInternal(const FUserDataType& UserData);`
- L21 _public prototype_ `bool RaycastInternal(const FUserDataType& UserData, FQueryFastData& CurData);`
- L22 _public prototype_ `bool SweepInternal(const FUserDataType& UserData, FQueryFastData& CurData);`
- L24 _public member_ `FOverlapQueryRuntimeData* OverlapQueryData = nullptr;`
- L25 _public member_ `FOverlapVisitor* OverlapVisitor = nullptr;`
- L27 _public member_ `FRaycastQueryRuntimeData* RaycastQueryData = nullptr;`
- L28 _public member_ `FRaycastVisitor* RaycastVisitor = nullptr;`
- L30 _public member_ `FSweepQueryRuntimeData* SweepQueryData = nullptr;`
- L31 _public member_ `FSweepVisitor* SweepVisitor = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/Library/LegacyAabbTree.h` (Private)


#### struct `Chaos::SpatialPartition::FLegacyAabbTreeCVarCacheContext`  
`struct FLegacyAabbTreeCVarCacheContext`  
_L14-22_
- desc: A context to cache certain cvars that we want to change during tests and then reset afterwards.
- L16 _public prototype_ `FLegacyAabbTreeCVarCacheContext();`
- L17 _public prototype_ `~FLegacyAabbTreeCVarCacheContext();`
- L19 _public member_ `int32 DynamicTreeLeafCapacity;`
- L20 _public member_ `FReal DynamicTreeLeafEnlargePercent;`
- L21 _public member_ `FReal DynamicTreeBoundingBoxPadding;`

#### class `Chaos::SpatialPartition::FLegacyAabbTree`  
`class FLegacyAabbTree`  
_L24-90_
- L36 _public prototype_ `FLegacyAabbTree() = default;`
- L37 _public prototype_ `FLegacyAabbTree(const FConfig& Config);`
- L39 _public prototype_ `void Insert(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& OutHandle);`
- L40 _public prototype_ `void Update(const FUserDataType& UserData, const FAABB3& Aabb, FSpatialHandle& InOutHandle);`
- L41 _public prototype_ `void Remove(FSpatialHandle& InOutHandle);`
- L43 _public prototype_ `EVisitResult Overlap(FOverlapQueryRuntimeData& QueryData, FOverlapVisitor& Visitor) const;`
- L44 _public prototype_ `EVisitResult Raycast(FRaycastQueryRuntimeData& QueryData, FRaycastVisitor& Visitor) const;`
- L45 _public prototype_ `EVisitResult Sweep(FSweepQueryRuntimeData& QueryData, FSweepVisitor& Visitor) const;`
- L46 _public prototype_ `void SelfQuery(FSelfQueryVisitor& Visitor);`
- L85 _private member_ `FConfig Config;`
- L86 _private member_ `FLegacyAabbTreeCVarCacheContext CVarCacheContext;`
- L87 _private member_ `TArray<FEntry> Entries;`
- L88 _private typedef_ `using AABBDynamicTreeType = TAABBTree<int, TAABBTreeLeafArray<int>>;`
- L89 _private member_ `AABBDynamicTreeType Tree;`

#### struct `Chaos::SpatialPartition::FLegacyAabbTree::FConfig`  
`struct FConfig`  
_L27-34_
- L29 _public member_ `bool bDynamicTree = true;`
- L30 _public member_ `int32 MaxChildrenInLeaf = 8;`
- L31 _public member_ `int32 MaxTreeDepth = 200;`
- L32 _public member_ `FReal MaxPayloadBounds = 100000;`
- L33 _public member_ `int32 MaxNumToProcess = 4000;`

#### struct `Chaos::SpatialPartition::FLegacyAabbTree::FVisitorWrapper`  
`struct FVisitorWrapper : public FLegacyVisitorBase`  
_L50-61_
- inherits: `FLegacyVisitorBase`
- desc: A wrapper for the legacy visitor to call into the new visitors.
- L52 _public prototype_ `FVisitorWrapper(const FLegacyAabbTree* Tree, FOverlapQueryRuntimeData* InQueryData, FOverlapVisitor* InVisitor);`
- L53 _public prototype_ `FVisitorWrapper(const FLegacyAabbTree* Tree, FRaycastQueryRuntimeData* InQueryData, FRaycastVisitor* InVisitor);`
- L54 _public prototype_ `FVisitorWrapper(const FLegacyAabbTree* Tree, FSweepQueryRuntimeData* InQueryData, FSweepVisitor* InVisitor);`
- L56 _public prototype_ `virtual bool Overlap(const TSpatialVisitorData<int32>& Instance) override;`
- L57 _public prototype_ `virtual bool Raycast(const TSpatialVisitorData<int32>& Instance, FQueryFastData& CurData) override;`
- L58 _public prototype_ `virtual bool Sweep(const TSpatialVisitorData<int32>& Instance, FQueryFastData& CurData) override;`
- L60 _public member_ `const FLegacyAabbTree* Tree = nullptr;`

#### struct `Chaos::SpatialPartition::FLegacyAabbTree::FSelfQueryVisitorWrapper`  
`struct FSelfQueryVisitorWrapper : public ISpatialVisitor<int32>`  
_L63-76_
- inherits: `ISpatialVisitor<int32>`
- L65 _public prototype_ `FSelfQueryVisitorWrapper(const FLegacyAabbTree* Tree, const int32 Entry0Index, const FUserDataType& UserData0, FSelfQueryVisitor* InVisitor);`
- L66 _public prototype_ `virtual bool Overlap(const TSpatialVisitorData<int32>& Instance) override;`
- L67 _public prototype_ `virtual bool Raycast(const TSpatialVisitorData<int32>& Instance, FQueryFastData& CurData) override;`
- L68 _public prototype_ `virtual bool Sweep(const TSpatialVisitorData<int32>& Instance, FQueryFastData& CurData) override;`
- L70 _public prototype_ `virtual const void* GetQueryPayload() const override;`
- L72 _public member_ `FSelfQueryVisitor* Visitor = nullptr;`
- L73 _public member_ `const FLegacyAabbTree* Tree = nullptr;`
- L74 _public member_ `int32 Entry0Index;`
- L75 _public member_ `FUserDataType UserData0;`

#### struct `Chaos::SpatialPartition::FLegacyAabbTree::FEntry`  
`struct FEntry`  
_L78-83_
- L80 _public member_ `FAABB3 Aabb;`
- L81 _public member_ `FUserDataType UserData;`
- L82 _public member_ `bool bIsUsed = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace SpatialPartition` (scope `Chaos`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/ObjectData.h` (Private)


#### struct `Chaos::SpatialPartition::FObjectData`  
`struct FObjectData`  
_L14-23_
- desc: Helper class to represent an object. This just makes it a bit easier to manage groups of objects for tests.
- L16 _public function_ `FVec3 GetCenter() const`
- L17 _public function_ `const FAABB3& GetAabb() const`
- L19 _public member_ `FAABB3 Aabb = FAABB3::EmptyAABB();`
- L20 _public member_ `FUserDataType UserData = INDEX_NONE;`
- L21 _public member_ `FSpatialClassification Classification;`
- L22 _public member_ `FSpatialHandle Handle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L25 _function_ `inline void BuildObjectList(TArray<FObjectData>& Objects, const int32 CountX = 1, const int32 CountY = 1, const int32 CountZ = 1, const FVec3& Spacing = FVec3(1), const FVec3& AabbSize = FVec3(1))` (scope `Chaos::SpatialPartition`)
- L49 _function_ `template <typename SpatialPartitionType> void InsertObject(SpatialPartitionType& SpatialPartition, FObjectData& Object)` (scope `Chaos::SpatialPartition`)
- L55 _function_ `template <typename SpatialPartitionType> void UpdateObject(SpatialPartitionType& SpatialPartition, FObjectData& Object)` (scope `Chaos::SpatialPartition`)
- L61 _function_ `template <typename SpatialPartitionType> void RemoveObject(SpatialPartitionType& SpatialPartition, FObjectData& Object)` (scope `Chaos::SpatialPartition`)
- L67 _function_ `template <typename SpatialPartitionType> void BuildFromObjects(SpatialPartitionType& SpatialPartition, TArray<FObjectData>& Objects)` (scope `Chaos::SpatialPartition`)
- L77 _function_ `template <typename SpatialPartitionType> void Rebuild(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`) — Tell the spatial partition to fully rebuild itself (no dirty state)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/SharedCollectionTests.h` (Private)


#### struct `Chaos::SpatialPartition::TPerfContext`  
`template <typename SpatialPartitionType, typename SpatialPartitionCreationFunction> struct TPerfContext`  
_L134-161_
- L136 _public member_ `TArray<FObjectData> Objects;`
- L137 _public member_ `TUniquePtr<SpatialPartitionType> SpatialPartition;`
- L139 _public function_ `void Setup(SpatialPartitionCreationFunction CreationFn, const TArray<FSpatialClassification>& Classifications, int32 ObjectCount)`
- L145 _public function_ `static void Setup(TArray<TPerfContext>& OutContexts, SpatialPartitionCreationFunction CreationFn, const int32 ContextsCount, const TArray<FSpatialClassification>& Classifications, const int32 ObjectCount)`
- L154 _public function_ `static void BuildAllSpatialPartitions(TArray<TPerfContext>& Contexts)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Chaos`
- L15 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L17 _function_ `inline void BuildObjectList(TArray<FObjectData>& Objects, const int32 ObjectCount, const TArray<FSpatialClassification>& Classifications, const FVec3& AabbSize = FVec3(1))` (scope `Chaos::SpatialPartition`)
- L34 _function_ `inline void BuildExpectedResults(const TArray<FObjectData>& Objects, const int32 IndexToSkip, TArray<FUserDataType>& OutResults)` (scope `Chaos::SpatialPartition`)
- L45 _function_ `inline void BuildExpectedResults(const TArray<FObjectData>& Objects, const ESpatialCategory CategoryToInclude, TArray<FUserDataType>& OutResults)` (scope `Chaos::SpatialPartition`)
- L56 _function_ `inline void AddUserData(const TArray<FObjectData>& Objects, const ESpatialCategoryMask CategoriesToInclude, const int32 IndexToSkip, TArray<FUserDataType>& OutResults)` (scope `Chaos::SpatialPartition`)
- L67 _function_ `inline void AddUserData(const TArray<FObjectData>& Objects, const ESpatialCategoryMask CategoriesToInclude, TArray<FUserDataType>& OutResults)` (scope `Chaos::SpatialPartition`)
- L72 _function_ `inline void BuildExpectedResults(const TArray<FObjectData>& Objects, const ESpatialCategoryMask CategoriesToInclude, const int32 IndexToSkip, TArray<FUserDataType>& OutResults)` (scope `Chaos::SpatialPartition`)
- L77 _function_ `inline void BuildExpectedResults(const TArray<FObjectData>& Objects, const ESpatialCategoryMask CategoriesToInclude, TArray<FUserDataType>& OutResults)` (scope `Chaos::SpatialPartition`)
- L82 _function_ `inline TArray<FSpatialClassification> GetClassifications()` (scope `Chaos::SpatialPartition`)
- L93 _function_ `inline const TArray<ESpatialCategoryMask> GetTestMasks()` (scope `Chaos::SpatialPartition`)
- L105 _function_ `inline int32 GenerateCategoryIndex(const TArray<FSpatialClassification>& Classifications)` (scope `Chaos::SpatialPartition`)
- L113 _function_ `inline int32 GenerateCategoryOffset(const TArray<FSpatialClassification>& Classifications)` (scope `Chaos::SpatialPartition`)
- L120 _function_ `inline std::ostream& operator<<(std::ostream& Stream, const ESpatialCategory Category)` (scope `Chaos::SpatialPartition`)
- L127 _function_ `inline std::ostream& operator<<(std::ostream& Stream, const ESpatialCategoryMask Mask)` (scope `Chaos::SpatialPartition`) — This provides `tostring` functionality for catch2 when the test fails.
- L164 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicBuild(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications(), const TArray<ESpatialCategoryMask> MasksToTest = GetTestMasks())` (scope `Chaos::SpatialPartition`)
- L213 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicInsert(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications(), const TArray<ESpatialCategoryMask> MasksToTest = GetTestMasks())` (scope `Chaos::SpatialPartition`)
- L270 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicUpdateSameCategory(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications(), const TArray<ESpatialCategoryMask> MasksToTest = GetTestMasks())` (scope `Chaos::SpatialPartition`)
- L363 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicUpdateDifferentCategory(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications())` (scope `Chaos::SpatialPartition`)
- L420 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicRemove(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications(), const TArray<ESpatialCategoryMask> MasksToTest = GetTestMasks())` (scope `Chaos::SpatialPartition`)
- L474 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicSelfQuery(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications())` (scope `Chaos::SpatialPartition`)
- L479 _typedef_ `using FPair = FTestSelfQueryCollectorVisitor::FPair;` (scope `Chaos::SpatialPartition::TestCollectionBasicSelfQuery`)
- L553 _function_ `template <typename SpatialPartitionType, typename SpatialPartitionCreationFunction> void TestCollectionBasicInsertPerf(SpatialPartitionCreationFunction CreationFn, const TArray<FSpatialClassification> Classifications = GetClassifications(), const int32 ObjectsPerClassification = 1000)` (scope `Chaos::SpatialPartition`)
- L555 _typedef_ `using FPerfContext = TPerfContext<SpatialPartitionType, SpatialPartitionCreationFunction>;` (scope `Chaos::SpatialPartition::TestCollectionBasicInsertPerf`)
- L564 _function_ `` (scope `Chaos::SpatialPartition::TestCollectionBasicInsertPerf`)
- L575 _function_ `template <typename SpatialPartitionType, typename SpatialPartitionCreationFunction> void TestCollectionBasicUpdatePerf(SpatialPartitionCreationFunction CreationFn, const TArray<FSpatialClassification> Classifications = GetClassifications(), const int32 ObjectsPerClassification = 1000)` (scope `Chaos::SpatialPartition`)
- L577 _typedef_ `using FPerfContext = TPerfContext<SpatialPartitionType, SpatialPartitionCreationFunction>;` (scope `Chaos::SpatialPartition::TestCollectionBasicUpdatePerf`)
- L594 _function_ `` (scope `Chaos::SpatialPartition::TestCollectionBasicUpdatePerf`)
- L605 _function_ `template <typename SpatialPartitionType, typename SpatialPartitionCreationFunction> void TestCollectionBasicRemovePerf(SpatialPartitionCreationFunction CreationFn, const TArray<FSpatialClassification> Classifications = GetClassifications(), const int32 ObjectsPerClassification = 1000)` (scope `Chaos::SpatialPartition`)
- L607 _typedef_ `using FPerfContext = TPerfContext<SpatialPartitionType, SpatialPartitionCreationFunction>;` (scope `Chaos::SpatialPartition::TestCollectionBasicRemovePerf`)
- L617 _function_ `` (scope `Chaos::SpatialPartition::TestCollectionBasicRemovePerf`)
- L649 _function_ `template <typename SpatialPartitionType, typename SpatialPartitionCreationFunction> void TestCollectionBasicRemovePerfWithSplitClassifications(SpatialPartitionCreationFunction CreationFn, const int32 ObjectsPerClassification = 1000)` (scope `Chaos::SpatialPartition`)
- L681 _function_ `template <typename SpatialPartitionType, typename SpatialPartitionCreationFunction> void TestCollectionBasicRebuildPerf(SpatialPartitionCreationFunction CreationFn, const TArray<FSpatialClassification> Classifications = GetClassifications(), const int32 ObjectsPerClassification = 1000)` (scope `Chaos::SpatialPartition`)
- L683 _typedef_ `using FPerfContext = TPerfContext<SpatialPartitionType, SpatialPartitionCreationFunction>;` (scope `Chaos::SpatialPartition::TestCollectionBasicRebuildPerf`)
- L693 _function_ `` (scope `Chaos::SpatialPartition::TestCollectionBasicRebuildPerf`)
- L700 _function_ `template <typename SpatialPartitionType> void TestCollectionBasicOverlapPerf(SpatialPartitionType& SpatialPartition, const TArray<FSpatialClassification> Classifications = GetClassifications(), const int32 ObjectsPerClassification = 1000)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/SharedHelpers.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L7 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L9 _function_ `inline FAABB3 BuildAabbMinExtents(const FVec3& Min, const FVec3& Extents)` (scope `Chaos::SpatialPartition`)
- L14 _function_ `inline FAABB3 BuildAabbCenterExtents(const FVec3& Center, const FVec3& Extents)` (scope `Chaos::SpatialPartition`)
- L22 _function_ `inline int32 GetIndex(const int32 X, const int32 Y, const int32 Z, const int32 CountX, const int32 CountY, const int32 )` (scope `Chaos::SpatialPartition`) — Build the index for a 1D array using 3D coordinates.

### `Source/Programs/ChaosSpatialPartitionsTests/Private/SharedOverlapTests.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L17 _function_ `template <typename SpatialPartitionType> void TestOverlapBuildBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L75 _function_ `template <typename SpatialPartitionType> void TestOverlapInsert(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L109 _function_ `template <typename SpatialPartitionType> void TestOverlapRemove(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L144 _function_ `template <typename SpatialPartitionType> void TestOverlapUpdateBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L186 _function_ `template <typename SpatialPartitionType> void TestOverlapUpdateWithinBounds(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L220 _function_ `template <typename SpatialPartitionType> void TestOverlapWithEarlyVisitResultTermination(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L238 _function_ `template <typename SpatialPartitionType> void TestOverlapPerformanceEmpty(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L250 _function_ `template <typename SpatialPartitionType> void TestOverlapPerformanceBasic(SpatialPartitionType& SpatialPartition, const int32 CountX = 100, const int32 CountY = 100, const int32 CountZ = 100)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/SharedRaycastTests.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L17 _function_ `template <typename SpatialPartitionType> void TestRaycastBuildBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L94 _function_ `template <typename SpatialPartitionType> void TestRaycastInsert(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L134 _function_ `template <typename SpatialPartitionType> void TestRaycastRemove(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L175 _function_ `template <typename SpatialPartitionType> void TestRaycastUpdateBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L218 _function_ `template <typename SpatialPartitionType> void TestRaycastUpdateWithinBounds(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L255 _function_ `template <typename SpatialPartitionType> void TestRaycastWithEarlyVisitResultTermination(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L275 _function_ `template <typename SpatialPartitionType> void TestRaycastWithEarlyLengthTermination(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L297 _function_ `template <typename SpatialPartitionType> void TestRaycastPerformanceEmpty(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L310 _function_ `template <typename SpatialPartitionType> void TestRaycastPerformanceBasic(SpatialPartitionType& SpatialPartition, const int32 CountX = 10000, const int32 CountY = 10)` (scope `Chaos::SpatialPartition`)
- L421 _function_ `template <typename SpatialPartitionType> void TestRaycastPerformanceFirstHit(SpatialPartitionType& SpatialPartition, const int32 CountX = 100, const int32 CountY = 100, int32 CountZ = 100)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/SharedSelfQueryTests.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L17 _function_ `template <typename SpatialPartitionType> void TestSelfQueryBuildBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L24 _typedef_ `using FPair = FTestSelfQueryCollectorVisitor::FPair;` (scope `Chaos::SpatialPartition::TestSelfQueryBuildBasic`) — For basic build tests, we want to test: - An empty spatial partition - An empty result list - Multiple results Single result shouldn't really be necessary
- L72 _function_ `template <typename SpatialPartitionType> void TestSelfQueryInsert(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L78 _typedef_ `using FPair = FTestSelfQueryCollectorVisitor::FPair;` (scope `Chaos::SpatialPartition::TestSelfQueryInsert`) — For insertion, we want to test: - Insert: No changes - Insert: One new result - Insert: Multiple new results
- L137 _function_ `template <typename SpatialPartitionType> void TestSelfQueryRemove(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L143 _typedef_ `using FPair = FTestSelfQueryCollectorVisitor::FPair;` (scope `Chaos::SpatialPartition::TestSelfQueryRemove`) — For remove, we want to test: - Remove: No changes - Remove: One result removed - Remove: Multiple results removed
- L204 _function_ `template <typename SpatialPartitionType> void TestSelfQueryUpdateBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L212 _typedef_ `using FPair = FTestSelfQueryCollectorVisitor::FPair;` (scope `Chaos::SpatialPartition::TestSelfQueryUpdateBasic`) — For basic update tests, we need to test: - No change - One new result - One removed result - One new and one removed result - Multiple changes
- L310 _function_ `template <typename SpatialPartitionType> void TestSelfQueryUpdateMovement(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L317 _typedef_ `using FPair = FTestSelfQueryCollectorVisitor::FPair;` (scope `Chaos::SpatialPartition::TestSelfQueryUpdateMovement`) — In general, we want to test a few scenarios that simulate an object moving: 1. A small update along each axis, both in the positive and negative directions. 2. A large update along each axis. This is useful to make sure self pairs aren't created. - An example of this is SAP where moving far enough that a min crosses a max (or vice-versa) could cause a self pair to get created. 3. Growing on all axes (shrinking is handled separately).
- L409 _function_ `template <typename SpatialPartitionType> void TestSelfQueryUpdateWithinBounds(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L426 _function_ `template <typename SpatialPartitionType> void TestSelfQueryPerformanceEmpty(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L437 _function_ `template <typename SpatialPartitionType> void TestSelfQueryPerformanceBasic(SpatialPartitionType& SpatialPartition, const int32 CountX = 100, const int32 CountY = 100, int32 CountZ = 100)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/SharedSweepTests.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L17 _function_ `template <typename SpatialPartitionType> void TestSweepBuildBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L113 _function_ `template <typename SpatialPartitionType> void TestSweepInsert(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L155 _function_ `template <typename SpatialPartitionType> void TestSweepRemove(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L198 _function_ `template <typename SpatialPartitionType> void TestSweepUpdateBasic(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L241 _function_ `template <typename SpatialPartitionType> void TestSweepUpdateWithinBounds(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L278 _function_ `template <typename SpatialPartitionType> void TestSweepWithEarlyVisitResultTermination(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L298 _function_ `template <typename SpatialPartitionType> void TestSweepWithEarlyLengthTermination(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L319 _function_ `template <typename SpatialPartitionType> void TestSweepPerformanceEmpty(SpatialPartitionType& SpatialPartition)` (scope `Chaos::SpatialPartition`)
- L331 _function_ `template <typename SpatialPartitionType> void TestSweepPerformanceBasic(SpatialPartitionType& SpatialPartition, const int32 CountX = 10000, const int32 CountY = 10, const int32 CountZ = 2)` (scope `Chaos::SpatialPartition`)
- L447 _function_ `template <typename SpatialPartitionType> void TestSweepPerformanceFirstHit(SpatialPartitionType& SpatialPartition, const int32 CountX = 50, const int32 CountY = 50, int32 CountZ = 50)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/StaticAabbTreeHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L12 _function_ `inline TArray<FAabbTreeLeafElement> BuildElementsFromAabbs(const TArray<FAABB3>& Aabbs)` (scope `Chaos::SpatialPartition`)
- L25 _function_ `inline int32 FindLeafWithElementIndexValue(const TArray<FAabbTreeLeaf>& Leaves, const int32 SearchValue)` (scope `Chaos::SpatialPartition`) — Returns the index of the first leaf where there's an element with the given search value. This is used in tests to find where some input data ended up in the final tree.
- L41 _function_ `inline const FAabbTreeLeaf* FindLeafPointerWithHandleValue(const TArray<FAabbTreeLeaf>& Leaves, const int32 SearchValue)` (scope `Chaos::SpatialPartition`)
- L47 _function_ `inline void FindLeafAndNodePointers(const TArray<FAabbTreeLeaf>& Leaves, const TArray<FAabbTreeNode>& Nodes, const int32 IndexCount, TArray<const FAabbTreeLeaf*>& OutLeaves, TArray<const FAabbTreeNode*>& OutNodes)` (scope `Chaos::SpatialPartition`)

### `Source/Programs/ChaosSpatialPartitionsTests/Private/TestVisitors.h` (Private)


#### struct `Chaos::SpatialPartition::TTestAccumulatorVisitor`  
`template <typename QueryDataType, template <typename> typename AdapterType> struct TTestAccumulatorVisitor : public AdapterType<TTestAccumulatorVisitor<QueryDataType, AdapterType>>`  
_L13-27_
- inherits: `AdapterType<TTestAccumulatorVisitor<QueryDataType,AdapterType>>`
- desc: Visitor that accumulates the user data. This is primarily used for perf tests to guarantee the results are used.
- L15 _public function_ `EVisitResult Visit(const FUserDataType& UserData, QueryDataType& QueryData)`
- L21 _public function_ `void Reset()`
- L26 _public member_ `int32 Result = 0;`

#### struct `Chaos::SpatialPartition::FTestSelfQueryAccumulatorVisitor`  
`struct FTestSelfQueryAccumulatorVisitor : public TSelfQueryVisitorAdapter<FTestSelfQueryAccumulatorVisitor>`  
_L34-47_
- inherits: `TSelfQueryVisitorAdapter<FTestSelfQueryAccumulatorVisitor>`
- desc: Visitor that accumulates the user data. This is primarily used for perf tests to guarantee the results are used.
- L36 _public function_ `void Visit(const FUserDataType& UserData0, const FUserDataType& UserData1)`
- L41 _public function_ `void Reset()`
- L46 _public member_ `int32 Result = 0;`

#### struct `Chaos::SpatialPartition::TTestCollectorVisitor`  
`template <typename QueryDataType, template <typename> typename AdapterType> struct TTestCollectorVisitor : public AdapterType<TTestCollectorVisitor<QueryDataType, AdapterType>>`  
_L52-78_
- inherits: `AdapterType<TTestCollectorVisitor<QueryDataType,AdapterType>>`
- desc: Visitor that collects all results from visit calls. This is used to check all expected results are returned. As traversal order is not guaranteed, this sorts the results to ensure consistent and stable tests.
- L54 _public function_ `EVisitResult Visit(const FUserDataType& UserData, QueryDataType& QueryData)`
- L69 _public function_ `void Reset()`
- L74 _public member_ `int32 MaxResults = TNumericLimits<int32>::Max();`
- L75 _public member_ `bool bUpdateLength = false;`
- L76 _public member_ `FReal TargetLength = 1;`
- L77 _public member_ `TArray<FUserDataType> Results;`

#### struct `Chaos::SpatialPartition::FTestSelfQueryCollectorVisitor`  
`struct FTestSelfQueryCollectorVisitor : public TSelfQueryVisitorAdapter<FTestSelfQueryCollectorVisitor>`  
_L87-136_
- inherits: `TSelfQueryVisitorAdapter<FTestSelfQueryCollectorVisitor>`
- desc: Visitor that collects all results from visit calls. This is used to check all expected results are returned. As traversal order is not guaranteed, this sorts the results to ensure consistent and stable tests. Note: The results are sorted by UserData0 then UserData1.
- L121 _public function_ `EVisitResult Visit(const FUserDataType& UserData0, const FUserDataType& UserData1)`
- L129 _public function_ `void Reset()`
- L134 _public member_ `int32 MaxResults = TNumericLimits<int32>::Max();`
- L135 _public member_ `TArray<FPair> Results;`

#### struct `Chaos::SpatialPartition::FTestSelfQueryCollectorVisitor::FPair`  
`struct FPair`  
_L89-119_
- L91 _public prototype_ `FPair() = default;`
- L92 _public function_ `FPair(const FUserDataType& InUserData0, const FUserDataType& InUserData1)`
- L107 _public function_ `bool operator<(const FPair& Other) const`
- L115 _public prototype_ `bool operator==(const FPair& Other) const = default;`
- L117 _public member_ `FUserDataType UserData0;`
- L118 _public member_ `FUserDataType UserData1;`

#### struct `Chaos::SpatialPartition::TTestFindFirstObjectVisitor`  
`template <typename ObjectType, typename QueryDataType, template <typename> typename AdapterType> struct TTestFindFirstObjectVisitor : public AdapterType<TTestFindFirstObjectVisitor<ObjectType, QueryDataType, AdapterType>>`  
_L150-185_
- inherits: `AdapterType<TTestFindFirstObjectVisitor<ObjectType,QueryDataType,AdapterType>>`
- desc: Visitor that simulates typical "find first" behavior. This takes an array of objects that are assumed to have an "Aabb" field. For every hit object, the length of the query is truncated. This results in selecting the first hit object. This is primarily for performance tests and checking how early traversals can finish. Note: This also assumes the user data maps to the array index.
- L152 _public function_ `TTestFindFirstObjectVisitor(const TArray<ObjectType>& InObjects) : Objects(InObjects)`
- L157 _public function_ `EVisitResult Visit(const FUserDataType& UserData, QueryDataType& QueryData)`
- L174 _public function_ `void Reset()`
- L180 _public member_ `const TArray<ObjectType>& Objects;`
- L181 _public member_ `FUserDataType FirstHitUserData = INDEX_NONE;`
- L184 _public member_ `int32 VisitCount = 0;` — Visit count isn't too useful for CHECK tests since the initial traversal order often can't be relied on, however this value can be useful when debugging to check expectations.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace SpatialPartition` (scope `Chaos`)
- L29 _typedef_ `using FTestOverlapAccumulatorVisitor = TTestAccumulatorVisitor<FOverlapQueryRuntimeData, TOverlapVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L30 _typedef_ `using FTestRaycastAccumulatorVisitor = TTestAccumulatorVisitor<FRaycastQueryRuntimeData, TRaycastVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L31 _typedef_ `using FTestSweepAccumulatorVisitor = TTestAccumulatorVisitor<FSweepQueryRuntimeData, TSweepVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L80 _typedef_ `using FTestOverlapCollectorVisitor = TTestCollectorVisitor<FOverlapQueryRuntimeData, TOverlapVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L81 _typedef_ `using FTestRaycastCollectorVisitor = TTestCollectorVisitor<FRaycastQueryRuntimeData, TRaycastVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L82 _typedef_ `using FTestSweepCollectorVisitor = TTestCollectorVisitor<FSweepQueryRuntimeData, TSweepVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L139 _function_ `inline std::ostream& operator<<(std::ostream& stream, const FTestSelfQueryCollectorVisitor::FPair& value)` (scope `Chaos::SpatialPartition`) — This provides `tostring` functionality for catch2 when the test fails.
- L188 _typedef_ `template <typename ObjectType> using TTestFindFirstObjectRaycastVisitor = TTestFindFirstObjectVisitor<ObjectType, FRaycastQueryRuntimeData, TRaycastVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
- L190 _typedef_ `template <typename ObjectType> using TTestFindFirstObjectSweepVisitor = TTestFindFirstObjectVisitor<ObjectType, FSweepQueryRuntimeData, TSweepVisitorAdapter>;` (scope `Chaos::SpatialPartition`)
