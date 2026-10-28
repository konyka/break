# Plugins / TedsQueryStack

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack`
- headers: 24; symbols: 662
- symbol kinds: class=28, delegate=4, enum=6, enumerator=19, function=10, member=158, namespace=125, prototype=278, struct=21, typedef=13
- DynamicallyLoadedModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, TypedElementFramework

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Private/Sorting/SortTasks.h` (Private)


#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FPrefix`  
`struct FPrefix`  
_L22-27_
- L24 _public member_ `uint64 Prefix;`
- L25 _public member_ `RowHandle Row;`
- L26 _public member_ `bool bHasRemainingBytes;`

#### class `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks`  
`class FSortTasks`  
_L30-190_
- desc: Simple task queue system for the various operations needed to sort row handles using a column sorter.
- L33 _public prototype_ `void AddBarrier();`
- L34 _public prototype_ `void CollectPrefixes(TArrayView<FPrefix> Output, TConstArrayView<RowHandle> Input, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, int32 BatchSize);`
- L36 _public prototype_ `void RefreshPrefixes(TArrayView<FPrefix> Prefixes, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, uint32 ByteIndex, int32 BatchSize);`
- L38 _public prototype_ `void RadixSortPrefixes(TArrayView<FPrefix> Output);`
- L39 _public prototype_ `void CopyPrefixesToRowHandleArray(TArrayView<RowHandle> Output, TConstArrayView<FPrefix> Input);`
- L40 _public prototype_ `void ComparativeSortRowHandleRanges(TArrayView<RowHandle> Rows, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, int32 BatchSize);`
- L42 _public prototype_ `void MergeSortedAdjacentRanges(TArrayView<RowHandle> Array, TArrayView<RowHandle> Scratch, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, int32 SplitPosition);`
- L44 _public prototype_ `void BucketizeRange(TArrayView<RowHandle> Array, TArrayView<FPrefix> Prefixes, TArrayView<FPrefix> PrefixesShadow, TSharedPtr<const FColumnSorterInterface> Sorter, const ICoreProvider& Storage, int32 PrefixBatchSize, int32 SortBatchSize);`
- L47 _public prototype_ `void Update(FTimespan AllottedTime);`
- L50 _public prototype_ `bool HasRemainingTasks() const;` — Whether or not there are still any tasks remaining. If this is called during update it may not provide accurate results.
- L55 _public prototype_ `void PrintRemainingTaskList(FString& Output);` — Collects all tasks pending on various threads and compile them together into a list of remaining tasks. This cannot be safely called if Update is doing work.
- L113 _private typedef_ `using TaskVariant = TVariant< FTaskBarrier, FCollectPrefixesTask, FRefreshPrefixesTask, FRadixSortPrefixesTask, FCopyPrefixesToRowHandleArrayTask, FComparativeSortRowHandleRangeTask, FComparativeSortRowHandlePrefixRangeTask, FMergeSortedAdjacentRangesTask, FBucketizeRangesTask >;`
- L161 _private typedef_ `using TaskChain = TArray<FPrefixCollectionBatch>;`
- L162 _private typedef_ `using TaskReferenceChain = TArray<FPrefixCollectionBatch*>;`
- L164 _private prototype_ `void AddBarrier(TaskChain& Tasks);`
- L165 _private prototype_ `void CollectPrefixes(TaskChain& Tasks, TArrayView<FPrefix> Output, TConstArrayView<RowHandle> Input, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, int32 BatchSize);`
- L167 _private prototype_ `void RefreshPrefixes(TaskChain& Tasks, TArrayView<FPrefix> Prefixes, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, uint32 ByteIndex, int32 BatchSize);`
- L169 _private prototype_ `void RadixSortPrefixes(TaskChain& Tasks, TArrayView<FPrefix> Output);`
- L170 _private prototype_ `void CopyPrefixesToRowHandleArray(TaskChain& Tasks, TArrayView<RowHandle> Output, TConstArrayView<FPrefix> Input);`
- L171 _private prototype_ `void ComparativeSortRowHandleRanges(TaskChain& Tasks, TArrayView<RowHandle> Rows, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, int32 BatchSize);`
- L173 _private prototype_ `void ComparativeSortRowHandlePrefixRanges(TaskChain& Tasks, TArrayView<FPrefix> Rows, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter);`
- L175 _private prototype_ `void MergeSortedAdjacentRanges(TaskChain& Tasks, TArrayView<RowHandle> Array, TArrayView<RowHandle> Scratch, const ICoreProvider& Storage, TSharedPtr<const FColumnSorterInterface> Sorter, int32 SplitPosition);`
- L177 _private prototype_ `void BucketizeRange(TaskChain& Tasks, TArrayView<RowHandle> Array, TArrayView<FPrefix> Prefixes, TArrayView<FPrefix> PrefixesShadow, TSharedPtr<const FColumnSorterInterface> Sorter, const ICoreProvider& Storage, int32 PrefixBatchSize, int32 SortBatchSize, uint32 ByteIndex);`
- L181 _private prototype_ `void BuildTaskChain(TaskReferenceChain& Output);`
- L182 _private prototype_ `void RemoveCompletedTasks();`
- L184 _private member_ `TMpscQueue<TaskChain> PendingTasksQueue;`
- L185 _private member_ `TArray<TaskChain> PendingTasks;`
- L186 _private member_ `TaskChain MainTaskList;`
- L187 _private member_ `TaskReferenceChain LocalTaskChain;`
- L189 _private member_ `bool bIsUpdating = false;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FTaskBarrier`  
`struct FTaskBarrier`  
_L58-58_

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FCollectPrefixesTask`  
`struct FCollectPrefixesTask`  
_L59-65_
- L61 _public member_ `TArrayView<FPrefix> Output;`
- L62 _public member_ `TConstArrayView<RowHandle> Input;`
- L63 _public member_ `TSharedPtr<const FColumnSorterInterface> Sorter;`
- L64 _public member_ `const ICoreProvider& Storage;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FRefreshPrefixesTask`  
`struct FRefreshPrefixesTask`  
_L66-72_
- L68 _public member_ `TArrayView<FPrefix> Prefixes;`
- L69 _public member_ `TSharedPtr<const FColumnSorterInterface> Sorter;`
- L70 _public member_ `const ICoreProvider& Storage;`
- L71 _public member_ `uint32 ByteIndex;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FRadixSortPrefixesTask`  
`struct FRadixSortPrefixesTask`  
_L73-76_
- L75 _public member_ `TArrayView<FPrefix> Output;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FCopyPrefixesToRowHandleArrayTask`  
`struct FCopyPrefixesToRowHandleArrayTask`  
_L77-81_
- L79 _public member_ `TArrayView<RowHandle> Output;`
- L80 _public member_ `TConstArrayView<FPrefix> Input;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FComparativeSortRowHandleRangeTask`  
`struct FComparativeSortRowHandleRangeTask`  
_L82-87_
- L84 _public member_ `TArrayView<RowHandle> Rows;`
- L85 _public member_ `TSharedPtr<const FColumnSorterInterface> Sorter;`
- L86 _public member_ `const ICoreProvider& Storage;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FComparativeSortRowHandlePrefixRangeTask`  
`struct FComparativeSortRowHandlePrefixRangeTask`  
_L88-93_
- L90 _public member_ `TArrayView<FPrefix> Rows;`
- L91 _public member_ `TSharedPtr<const FColumnSorterInterface> Sorter;`
- L92 _public member_ `const ICoreProvider& Storage;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FMergeSortedAdjacentRangesTask`  
`struct FMergeSortedAdjacentRangesTask`  
_L94-101_
- L96 _public member_ `TArrayView<RowHandle> Array;`
- L97 _public member_ `TArrayView<RowHandle> Scratch;`
- L98 _public member_ `TSharedPtr<const FColumnSorterInterface> Sorter;`
- L99 _public member_ `const ICoreProvider& Storage;`
- L100 _public member_ `int32 SplitPosition;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FBucketizeRangesTask`  
`struct FBucketizeRangesTask`  
_L102-112_
- L104 _public member_ `TArrayView<RowHandle> Array;`
- L105 _public member_ `TArrayView<FPrefix> Prefixes;`
- L106 _public member_ `TArrayView<FPrefix> PrefixesShadow;`
- L107 _public member_ `TSharedPtr<const FColumnSorterInterface> Sorter;`
- L108 _public member_ `const ICoreProvider& Storage;`
- L109 _public member_ `int32 PrefixBatchSize;`
- L110 _public member_ `int32 SortBatchSize;`
- L111 _public member_ `uint32 Index;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FPrefixCollectionBatch`  
`struct FPrefixCollectionBatch`  
_L125-129_
- L127 _public member_ `TaskVariant Task;`
- L128 _public member_ `bool bCompleted = false;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FTaskVisitor`  
`struct FTaskVisitor`  
_L131-144_
- L133 _public prototype_ `void operator()(const FTaskBarrier& Task);`
- L134 _public prototype_ `void operator()(const FCollectPrefixesTask& Task);`
- L135 _public prototype_ `void operator()(const FRefreshPrefixesTask& Task);`
- L136 _public prototype_ `void operator()(const FRadixSortPrefixesTask& Task);`
- L137 _public prototype_ `void operator()(const FCopyPrefixesToRowHandleArrayTask& Task);`
- L138 _public prototype_ `void operator()(const FComparativeSortRowHandleRangeTask& Task);`
- L139 _public prototype_ `void operator()(const FComparativeSortRowHandlePrefixRangeTask& Task);`
- L140 _public prototype_ `void operator()(const FMergeSortedAdjacentRangesTask& Task);`
- L141 _public prototype_ `void operator()(const FBucketizeRangesTask& Task);`
- L143 _public member_ `FSortTasks& Owner;`

#### struct `UE::Editor::DataStorage::QueryStack::Sorting::FSortTasks::FTaskPrinter`  
`struct FTaskPrinter`  
_L146-159_
- L148 _public prototype_ `void operator()(const FTaskBarrier& Task);`
- L149 _public prototype_ `void operator()(const FCollectPrefixesTask& Task);`
- L150 _public prototype_ `void operator()(const FRefreshPrefixesTask& Task);`
- L151 _public prototype_ `void operator()(const FRadixSortPrefixesTask& Task);`
- L152 _public prototype_ `void operator()(const FCopyPrefixesToRowHandleArrayTask& Task);`
- L153 _public prototype_ `void operator()(const FComparativeSortRowHandleRangeTask& Task);`
- L154 _public prototype_ `void operator()(const FComparativeSortRowHandlePrefixRangeTask& Task);`
- L155 _public prototype_ `void operator()(const FMergeSortedAdjacentRangesTask& Task);`
- L156 _public prototype_ `void operator()(const FBucketizeRangesTask& Task);`
- L158 _public member_ `FString& Output;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L20 _namespace_ `namespace Sorting` (scope `UE::Editor::DataStorage::QueryStack`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Private/TedsQueryStackLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTedsQueryStack, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTedsQueryStack, Log, All);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/Searching/SearchUtils.h` (Public)


#### struct `UE::Editor::DataStorage::QueryStack::Searching::MemberPointerTraits`  
`template <typename T> struct MemberPointerTraits;`  
_L19-23_
- L21 _public typedef_ `using MemberType = Type;`
- L22 _public typedef_ `using ClassType = Class;`

#### struct `UE::Editor::DataStorage::QueryStack::Searching::FCaseInsensitiveHash`  
`struct FCaseInsensitiveHash`  
_L38-41_
- L40 _public prototype_ `size_t operator()(FString::ElementType Value) const;`

#### struct `UE::Editor::DataStorage::QueryStack::Searching::FCaseInsensitiveCompare`  
`struct FCaseInsensitiveCompare`  
_L42-45_
- L44 _public prototype_ `bool operator()(FString::ElementType Lhs, FString::ElementType Rhs) const;`

#### struct `UE::Editor::DataStorage::QueryStack::Searching::FSearchContext`  
`struct FSearchContext`  
_L48-55_
- L50 _public prototype_ `FSearchContext(FString InSearchString);`
- L52 _public member_ `FString SearchString;`
- L53 _public member_ `FStringSearcher StringSearcher;`
- L54 _public member_ `int32 CurrentSearcher = 0;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L15 _namespace_ `namespace Searching` (scope `UE::Editor::DataStorage::QueryStack`)
- L46 _typedef_ `using FStringSearcher = std::boyer_moore_horspool_searcher<const FString::ElementType*, FCaseInsensitiveHash, FCaseInsensitiveCompare>;` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L57 _typedef_ `using StringSearchFunction = bool(*)(const Searching::FSearchContext& Context, const FProperty* Property, const void* Column, FString& TempString);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L60 _prototype_ `template<auto MemberVariable> requires Searching::SearchableMemberColumn<MemberVariable> StringSearchFunction CreateSearchFunction();` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L61 _prototype_ `StringSearchFunction CreateSearchFunction(const FProperty* Property);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L64 _prototype_ `template<auto MemberVariable> requires SearchableMemberColumn<MemberVariable> bool Search(const void* Column, const FSearchContext& Context, FString& TempString);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L65 _prototype_ `bool Search(const FString& String, const FSearchContext& Context, FString& TempString);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L66 _prototype_ `bool Search(const FName& String, const FSearchContext& Context, FString& TempString);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L67 _prototype_ `bool Search(const FText& String, const FSearchContext& Context, FString& TempString);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L69 _prototype_ `void ListSearchableColumns(TFunctionRef<void(const UScriptStruct*)> Callback);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L70 _prototype_ `void ListSearchableProperties(const UScriptStruct* ColumnType, TFunctionRef<void(const FProperty*)> Callback);` (scope `UE::Editor::DataStorage::QueryStack::Searching`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/Searching/SearchUtils.inl` (Public)


#### Free symbols / members of external scopes

- L3 _namespace_ `namespace UE`
- L3 _namespace_ `namespace Editor` (scope `UE`)
- L3 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L3 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L3 _namespace_ `namespace Searching` (scope `UE::Editor::DataStorage::QueryStack`)
- L6 _function_ `template<auto MemberVariable> requires Searching::SearchableMemberColumn<MemberVariable> StringSearchFunction CreateSearchFunction()` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L9 _function_ `` (scope `UE::Editor::DataStorage::QueryStack::Searching::CreateSearchFunction`)
- L15 _function_ `template<auto MemberVariable> requires SearchableMemberColumn<MemberVariable> bool Search(const void* Column, const FSearchContext& Context, FString& TempString)` (scope `UE::Editor::DataStorage::QueryStack::Searching`)
- L17 _typedef_ `using Class = typename Searching::MemberPointerTraits<decltype(MemberVariable)>::ClassType;` (scope `UE::Editor::DataStorage::QueryStack::Searching::Search`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsColumnsSearchNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FColumnsSearchNode`  
`class FColumnsSearchNode final : public IRowNode`  
_L34-123_
- inherits: `IRowNode`
- desc: Searches through the provided list of columns and generates a list of rows for all columns with a property that match the search string.
- L43 _public prototype_ `FColumnsSearchNode(ICoreProvider& Storage, ESyncActions SyncAction);`
- L50 _public prototype_ `void StartSearch(FString SearchString);` — Starts searching for the provided string in all searchable columns that were selected in the query. Results may not be collected and can take several frames to arrive.
- L52 _public prototype_ `void ClearSearch();` — Resets a search.
- L54 _public prototype_ `bool IsSearching() const;` — Returns true if a search is still being processed.
- L61 _public prototype_ `FTimespan GetQuerySearchTime() const;` — The total time spend on performing the search. The returned time span represents the time spend performing search operations. This differs from the wall clock time in that it exclusively tracks the time spend on performing one or more steps in the search.
- L64 _public prototype_ `uint64 CalculateTotalSearchedCellCount() const;` — The total number of cells that will be searched through.
- L71 _public prototype_ `template<TDataColumnType Column> void RegisterColumn(Queries::FConditions Conditions = {});` — Register a column to search. All properties in the column that are marked with "Searchable" will be included.
- L76 _public prototype_ `void RegisterColumn(const UScriptStruct* ColumnType, const Queries::FConditions& Conditions = {});` — Register a column to search. All properties in the column that are marked with "Searchable" will be included.
- L82 _public prototype_ `void RegisterColumn(const UScriptStruct* ColumnType, const FProperty* Property, Queries::FConditions Conditions = {});` — Register a specific property in a column to search. Only the provided property will be searched if it contains a type that can be searched. It does not require to be marked with the "Searchable" metadata.
- L88 _public prototype_ `template<auto MemberVariable> requires Searching::SearchableMemberColumn<MemberVariable> void RegisterColumn(Queries::FConditions Conditions = {});` — Register a specific variable in a column to search. Only the provided variable will be searched if it contains a type that can be searched.
- L90 _public prototype_ `void UnregisterAllColumns();` — Clear all registered columns, properties and variables.
- L92 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L93 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L94 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L95 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L98 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L111 _private prototype_ `QueryHandle CreateQuery(const UScriptStruct* ColumnType, Queries::FConditions&& Conditions);` — Exported because it's used in the template to bind to a member variable.
- L112 _private prototype_ `void RunSearch(const Searching::FSearchContext& Context, const FSearchQuery& Searcher);`
- L113 _private prototype_ `void ResetSearch();`
- L115 _private member_ `TArray<FSearchQuery> Searchers;`
- L117 _private member_ `TUniquePtr<Searching::FSearchContext> SearchContext;`
- L118 _private member_ `FRowHandleArray Rows;`
- L119 _private member_ `ICoreProvider& Storage;`
- L120 _private member_ `FTimespan TotalSearchTime;` — actual time spend processing.
- L121 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L122 _private member_ `ESyncActions SyncAction;`
- L127 _function_ `template<TDataColumnType Column> void FColumnsSearchNode::RegisterColumn(Queries::FConditions Conditions)` — Implementations
- L133 _function_ `template<auto MemberVariable> requires Searching::SearchableMemberColumn<MemberVariable> void FColumnsSearchNode::RegisterColumn(Queries::FConditions Conditions)`

#### enum `UE::Editor::DataStorage::QueryStack::FColumnsSearchNode::ESyncActions`  
`enum ESyncActions`  
_L37-41_
- L39 _public enumerator_ `None`
- L40 _public enumerator_ `Refresh` — None,   Do nothing when there are changes to the tables that have columns that are being searched.

#### struct `UE::Editor::DataStorage::QueryStack::FColumnsSearchNode::FSearchQuery`  
`struct FSearchQuery`  
_L101-108_
- L103 _public member_ `QueryHandle Query = InvalidQueryHandle;`
- L104 _public member_ `uint64 Hash = 0;`
- L105 _public member_ `Searching::StringSearchFunction SearchFunction = nullptr;`
- L106 _public member_ `const FProperty* Property = nullptr;`
- L107 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L23 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L25 _namespace_ `namespace Searching` (scope `UE::Editor::DataStorage::QueryStack`)
- L135 _typedef_ `using Class = typename Searching::MemberPointerTraits<decltype(MemberVariable)>::ClassType;` (scope `UE::Editor::DataStorage::QueryStack::FColumnsSearchNode::RegisterColumn`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsHierarchyNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FHierarchyRowNode`  
`class FHierarchyRowNode final : public IRowNode`  
_L11-74_
- inherits: `IRowNode`
- desc: Row which enumerates and stores all children of the given TopLevelRows (including the TopLevelRows) Warning: The resulting row array is not guaranteed to be sorted in depth order
- L42 _public typedef_ `using EmitRowFn = TFunctionRef<void(TArrayView<const RowHandle>)>;`
- L44 _public prototype_ `FHierarchyRowNode( ICoreProvider& Storage, FHierarchyHandle InHierarchyHandle, TSharedPtr<QueryStack::IRowNode>& InTopLevelRows, ESyncFlags SyncFlags, EFilterFlags FilterFlags = EFilterFlags::None);`
- L51 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L52 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L53 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L54 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L57 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L60 _private prototype_ `void RefreshInternal(ICoreProvider& InCoreProvider, FRowHandleArray& NewRows) const;`
- L61 _private prototype_ `FRowHandleArray& GetTempRowHandleArray();`
- L63 _private member_ `FRowHandleArray Rows;`
- L64 _private member_ `FRowHandleArray NewRows;`
- L65 _private member_ `TSharedPtr<QueryStack::IRowNode> TopLevelRows;`
- L66 _private member_ `RevisionId ParentRevision = UninitializedRevisionId;`
- L68 _private member_ `ICoreProvider& Storage;`
- L69 _private member_ `FHierarchyHandle HierarchyHandle;`
- L71 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L72 _private member_ `ESyncFlags SyncFlags;`
- L73 _private member_ `EFilterFlags FilterFlags;`

#### enum `UE::Editor::DataStorage::QueryStack::FHierarchyRowNode::ESyncFlags`  
`enum class ESyncFlags`  
_L14-28_
- L19 _public enumerator_ `ParentRevisionDifferent = 0` — Increment the revision only when the parent's revision changed
- L23 _public enumerator_ `IncrementWhenDifferent = 1` — Compares the previous row list with the current and only updates the revision if there are differences.
- L27 _public enumerator_ `Always` — Update the row list whenever "Update" is called.

#### enum `UE::Editor::DataStorage::QueryStack::FHierarchyRowNode::EFilterFlags`  
`enum class EFilterFlags`  
_L30-40_
- L35 _public enumerator_ `None = 0` — No filtering will be applied
- L39 _public enumerator_ `OnlyIncludeChildRows = 1` — Root parent rows will not be included in the row list

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L6 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L76 _prototype_ `ENUM_CLASS_FLAGS(FHierarchyRowNode::ESyncFlags);` (scope `UE::Editor::DataStorage::QueryStack`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQueryChangeNotifyNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FQueryChangeNotifyNode`  
`class FQueryChangeNotifyNode final : public IQueryNode`  
_L13-32_
- inherits: `IQueryNode`
- desc: Query node that will broadcast a message when one or more of its parent nodes has been updated.
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryNodeChange, const TSharedPtr<IQueryNode>&);`
- L18 _public prototype_ `FQueryChangeNotifyNode(TSharedPtr<IQueryNode> Parent, FOnQueryNodeChange ChangeEvent);`
- L19 _public prototype_ `virtual ~FQueryChangeNotifyNode() override = default;`
- L21 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L22 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L23 _public prototype_ `virtual QueryHandle GetQuery() const override;`
- L26 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L29 _private member_ `TSharedPtr<IQueryNode> Parent;`
- L30 _private member_ `RevisionId CachedParentRevision = UninitializedRevisionId;`
- L31 _private member_ `FOnQueryNodeChange OnChangeEvent;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryNodeChange, const TSharedPtr<IQueryNode>&);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQueryHandleNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FQueryHandleNode`  
`class FQueryHandleNode : public IQueryNode`  
_L12-31_
- inherits: `IQueryNode`
- desc: Stores a handle to a query. This should be used to pass an externally created query into the Query Stack.
- L15 _public prototype_ `FQueryHandleNode() = default;`
- L16 _public prototype_ `explicit FQueryHandleNode(QueryHandle Query);`
- L17 _public prototype_ `virtual ~FQueryHandleNode() override = default;`
- L19 _public prototype_ `void SetQuery(QueryHandle InQuery);`
- L21 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L22 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L23 _public prototype_ `virtual QueryHandle GetQuery() const override;`
- L26 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L29 _private member_ `QueryHandle Query = InvalidQueryHandle;`
- L30 _private member_ `RevisionId Revision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L7 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQueryMergeNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FQueryMergeNode`  
`class FQueryMergeNode : public IQueryNode`  
_L19-45_
- inherits: `IQueryNode`
- desc: Merges one or more parent queries into a composite query A merge of two query nodes has the same result of the intersection of the rows when you run the queries individually
- L22 _public prototype_ `explicit FQueryMergeNode(ICoreProvider& InStorage, TConstArrayView<TSharedPtr<IQueryNode>> InParents);`
- L25 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L26 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L27 _public prototype_ `virtual QueryHandle GetQuery() const override;`
- L30 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L31 _protected prototype_ `void Rebuild();`
- L41 _private member_ `QueryHandle QueryHandle = InvalidQueryHandle;`
- L42 _private member_ `TArray<FParentInfo> Parents;`
- L43 _private member_ `ICoreProvider& Storage;`
- L44 _private member_ `RevisionId Revision = UninitializedRevisionId;`

#### struct `UE::Editor::DataStorage::QueryStack::FQueryMergeNode::FParentInfo`  
`struct FParentInfo`  
_L35-39_
- L37 _public member_ `TSharedPtr<IQueryNode> Parent;`
- L38 _public member_ `RevisionId Revision;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQueryNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FQueryNode`  
`class FQueryNode : public IQueryNode`  
_L18-39_
- inherits: `IQueryNode`
- desc: Stores a query and manages its registration.
- L21 _public prototype_ `explicit FQueryNode(ICoreProvider& Storage);`
- L22 _public prototype_ `FQueryNode(ICoreProvider& Storage, UE::Editor::DataStorage::FQueryDescription Query);`
- L25 _public prototype_ `void SetQuery(UE::Editor::DataStorage::FQueryDescription Query);`
- L26 _public prototype_ `void ClearQuery();`
- L28 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L29 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L30 _public prototype_ `virtual QueryHandle GetQuery() const override;`
- L33 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L36 _private member_ `QueryHandle QueryHandle = InvalidQueryHandle;`
- L37 _private member_ `ICoreProvider& Storage;`
- L38 _private member_ `RevisionId Revision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQuerySearchNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FQuerySearchNode`  
`class FQuerySearchNode final : public FRowQueryResultsNode`  
_L35-82_
- inherits: `FRowQueryResultsNode`
- desc: Query Stack node that takes a query and searches all selected columns that have searchable properties. If the search is disabled, either by calling "ClearSearch" or providing an empty string, this node acts as a pass through and behaves the same way as FRowQueryResultsNode.
- L38 _public prototype_ `explicit FQuerySearchNode(ICoreProvider& Storage, TSharedRef<IQueryNode> Query);`
- L39 _public prototype_ `explicit FQuerySearchNode(ICoreProvider& Storage, TSharedRef<IQueryNode> Query, ESyncActions SyncAction);`
- L40 _public prototype_ `virtual ~FQuerySearchNode() override = default;`
- L46 _public prototype_ `void StartSearch(FString SearchString);` — Starts searching for the provided string in all searchable columns that were selected in the query. Results may not be collected and can take several frames to arrive.
- L48 _public prototype_ `void ClearSearch();` — Resets a search and makes this node behave as a pass-through, resulting in similar behavior to FRowQueryResultsNode.
- L50 _public prototype_ `bool IsSearching() const;` — Returns true if a search is still being processed.
- L56 _public prototype_ `FTimespan GetQuerySearchTime() const;` — The total time spent on performing the search. This exclusively tracks the time spend on performing one or more steps in the search.
- L59 _protected member_ `static constexpr uint32 InlineColumnCount = 32;`
- L61 _protected prototype_ `virtual void RefreshInternal(FTimespan AllottedTime, FRowHandleArray& TargetRows) override;`
- L62 _protected prototype_ `virtual void QueryUpdated();`
- L73 _private prototype_ `void UpdateSearchersList();`
- L74 _private prototype_ `void RunSearch(const Searching::FSearchContext& Context, FRowHandleArray& TargetRows);`
- L75 _private prototype_ `void ResetSearch();`
- L77 _private member_ `TArray<FSearchQuery> Searchers;`
- L79 _private member_ `TUniquePtr<Searching::FSearchContext> SearchContext;`
- L80 _private member_ `FTimespan TotalSearchTime;` — actual time spent processing.
- L81 _private member_ `bool bHasPendingSearch = false;`

#### struct `UE::Editor::DataStorage::QueryStack::FQuerySearchNode::FSearchQuery`  
`struct FSearchQuery`  
_L65-71_
- L67 _public member_ `Searching::StringSearchFunction SearchFunction = nullptr;`
- L68 _public member_ `const FProperty* Property = nullptr;`
- L69 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`
- L70 _public member_ `int32 ColumnSize = 0;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L23 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L25 _namespace_ `namespace Searching` (scope `UE::Editor::DataStorage::QueryStack`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQueryStackExecutor.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FExecutorBase`  
`class FExecutorBase`  
_L14-45_
- L17 _public prototype_ `virtual ~FExecutorBase() = 0;`
- L19 _public prototype_ `const FName& GetStackName() const;`
- L20 _public prototype_ `TSharedPtr<const INode> GetRootNode() const;`
- L21 _public prototype_ `TSharedPtr<INode> GetRootNode();`
- L25 _protected prototype_ `FExecutorBase() = default;`
- L26 _protected prototype_ `FExecutorBase(const FName& InStackName, TSharedPtr<INode> InRootNode);`
- L30 _protected prototype_ `FExecutorBase(const FExecutorBase&) = delete;` — Delete copying to keep the guarantee that the name is unique and remove the risk of the same query stack being updated multiple times.
- L31 _protected prototype_ `FExecutorBase& operator=(const FExecutorBase&) = delete;`
- L33 _protected prototype_ `FExecutorBase(FExecutorBase&&) = default;`
- L34 _protected prototype_ `FExecutorBase& operator=(FExecutorBase&&) = default;`
- L36 _protected prototype_ `void FullUpdate();`
- L37 _protected prototype_ `void TimedUpdate(FTimespan AllottedTime);`
- L39 _protected member_ `TSharedPtr<INode> RootNode;`
- L40 _protected member_ `FName StackName;`
- L43 _private prototype_ `static void FullNodeUpdate(const FName& StackName, const TSharedPtr<INode>& Node);`
- L44 _private prototype_ `static void TimedNodeUpdate(const FName& StackName, const TSharedPtr<INode>& Node, uint64 StartTime, FTimespan AllottedTime);`

#### class `UE::Editor::DataStorage::QueryStack::FCooperativeExecutor`  
`class FCooperativeExecutor final : public FExecutorBase`  
_L52-67_
- inherits: `FExecutorBase`
- desc: Updates the query stack cooperatively with other background tasks. Preferred default as it reduces overall cost to the editor by allowing TEDS to fairly distribute available CPU cycles. The cooperative executor may stop partially through updating the stack and continue at a later time.
- L55 _public prototype_ `FCooperativeExecutor() = default;`
- L56 _public prototype_ `FCooperativeExecutor(const FName& InStackName, ICoreProvider& InDataStorage, TSharedPtr<INode> InRootNode, ICoreProvider::ECooperativeTaskPriority InPriority);`
- L59 _public prototype_ `FCooperativeExecutor(FCooperativeExecutor&& Rhs);`
- L60 _public prototype_ `FCooperativeExecutor& operator=(FCooperativeExecutor&& Rhs);`
- L65 _private member_ `ICoreProvider* DataStorage = nullptr;`
- L66 _private member_ `ICoreProvider::ECooperativeTaskPriority Priority;`

#### class `UE::Editor::DataStorage::QueryStack::FOnUpdateExecutor`  
`class FOnUpdateExecutor final : public FExecutorBase`  
_L72-88_
- inherits: `FExecutorBase`
- desc: Automatically updates the query stack just before TEDS starts running queries.
- L75 _public prototype_ `FOnUpdateExecutor() = default;`
- L76 _public prototype_ `FOnUpdateExecutor(const FName& InStackName, ICoreProvider& InDataStorage, TSharedPtr<INode> InRootNode);`
- L78 _public prototype_ `FOnUpdateExecutor(FOnUpdateExecutor&& Rhs);`
- L79 _public prototype_ `FOnUpdateExecutor& operator=(FOnUpdateExecutor&& Rhs);`
- L84 _private prototype_ `void OnUpdate();`
- L86 _private member_ `FDelegateHandle Delegate;`
- L87 _private member_ `ICoreProvider* DataStorage = nullptr;`

#### class `UE::Editor::DataStorage::QueryStack::FOnUpdateCompletedExecutor`  
`class FOnUpdateCompletedExecutor final : public FExecutorBase`  
_L93-109_
- inherits: `FExecutorBase`
- desc: Automatically updates the query stack at the very end of TEDS' update cycle.
- L96 _public prototype_ `FOnUpdateCompletedExecutor() = default;`
- L97 _public prototype_ `FOnUpdateCompletedExecutor(const FName& InStackName, ICoreProvider& InDataStorage, TSharedPtr<INode> InRootNode);`
- L99 _public prototype_ `FOnUpdateCompletedExecutor(FOnUpdateCompletedExecutor&& Rhs);`
- L100 _public prototype_ `FOnUpdateCompletedExecutor& operator=(FOnUpdateCompletedExecutor&& Rhs);`
- L105 _private prototype_ `void OnUpdateCompleted();`
- L107 _private member_ `FDelegateHandle Delegate;`
- L108 _private member_ `ICoreProvider* DataStorage = nullptr;`

#### class `UE::Editor::DataStorage::QueryStack::FExplicitCooperativeExecutor`  
`class FExplicitCooperativeExecutor final : public FExecutorBase`  
_L115-127_
- inherits: `FExecutorBase`
- desc: Allows explicit calls to update the query stack as part of a cooperative task. Does not update the provided query stack automatically but depends on calling Update.
- L118 _public prototype_ `FExplicitCooperativeExecutor() = default;`
- L119 _public prototype_ `FExplicitCooperativeExecutor(const FName& StackName, TSharedPtr<INode> RootNode);`
- L121 _public prototype_ `FExplicitCooperativeExecutor(FExplicitCooperativeExecutor&&) = default;`
- L122 _public prototype_ `FExplicitCooperativeExecutor& operator=(FExplicitCooperativeExecutor&&) = default;`
- L124 _public prototype_ `virtual ~FExplicitCooperativeExecutor() override = default;`
- L126 _public prototype_ `void Update(FTimespan AllottedTime);`

#### class `UE::Editor::DataStorage::QueryStack::FExplicitUpdateExecutor`  
`class FExplicitUpdateExecutor final : public FExecutorBase`  
_L133-145_
- inherits: `FExecutorBase`
- desc: Allows explicit calls to update the query stack. Does not update the provided query stack automatically but depends on calling Update.
- L136 _public prototype_ `FExplicitUpdateExecutor() = default;`
- L137 _public prototype_ `FExplicitUpdateExecutor(const FName& StackName, TSharedPtr<INode> RootNode);`
- L139 _public prototype_ `FExplicitUpdateExecutor(FExplicitUpdateExecutor&&) = default;`
- L140 _public prototype_ `FExplicitUpdateExecutor& operator=(FExplicitUpdateExecutor&&) = default;`
- L142 _public prototype_ `virtual ~FExplicitUpdateExecutor() override = default;`
- L144 _public prototype_ `void Update();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsQueryStackInterfaces.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::INode`  
`class INode`  
_L15-46_
- desc: Base interface for a all query stack nodes.
- L20 _public typedef_ `using RevisionId = uint32;`
- L22 _public member_ `static constexpr RevisionId UninitializedRevisionId = 0;` — The default uninitialized revision Id is zero to signify it is empty and needs to be updated/rows need to be initialized
- L24 _public typedef_ `using ParentListCallback = TFunctionRef<void(const TSharedPtr<INode>& Parent)>;`
- L25 _public member_ `static inline FTimespan UnlimitedTime = FTimespan::MaxValue();`
- L27 _public prototype_ `virtual ~INode() = default;`
- L33 _public prototype_ `virtual RevisionId GetRevision() const = 0;` — Get the current revision of the node. Whenever its internal state changes the revision should be incremented to signal a need to update to downstream nodes.
- L36 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) = 0;` — List all direct parent nodes.
- L45 _protected prototype_ `virtual void Update(FTimespan AllottedTime) = 0;` — Periodically called to allow a node to perform some work or to verify its internal state. @AllottedTime The maximum amount of time for the update. The update should try to stay below this time. In case the allotted time is equal to "UnlimitedTime" it means there is no upper bound to the amount of time that can be spend on the update.

#### class `UE::Editor::DataStorage::QueryStack::IQueryNode`  
`class IQueryNode : public INode`  
_L49-55_
- inherits: `INode`
- desc: Query stack node that works on queries handles. These nodes are typically run in some fashion to be turned into a row node.
- L52 _public prototype_ `virtual ~IQueryNode() = default;`
- L54 _public prototype_ `virtual QueryHandle GetQuery() const = 0;` — Returns the handle to the query this node represents.

#### class `UE::Editor::DataStorage::QueryStack::IRowNode`  
`class IRowNode : public INode`  
_L58-66_
- inherits: `INode`
- desc: Query stack node that works on row handles.
- L61 _public prototype_ `virtual ~IRowNode() = default;`
- L63 _public prototype_ `virtual FRowHandleArrayView GetRows() const = 0;` — Retrieve access to the rows used by this node.
- L65 _public prototype_ `virtual FRowHandleArray& GetMutableRows() = 0;` — Retrieve write access to the rows used by this node. Is allowed to return null if write access can't be granted.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowArrayNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowArrayNode`  
`class FRowArrayNode : public IRowNode`  
_L16-36_
- inherits: `IRowNode`
- desc: Stores row handle array. The array can be directly manipulated, but any changes outside the Query Stack require MarkDirty to inform the Query Stack that it needs to update dependent nodes.
- L19 _public prototype_ `FRowArrayNode() = default;`
- L20 _public prototype_ `explicit FRowArrayNode(FRowHandleArray Rows);`
- L21 _public prototype_ `virtual ~FRowArrayNode() override = default;`
- L23 _public prototype_ `void MarkDirty();`
- L25 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L26 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L27 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L28 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L31 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L34 _private member_ `FRowHandleArray Rows;`
- L35 _private member_ `RevisionId Revision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L9 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowChangeNotifyNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowChangeNotifyNode`  
`class FRowChangeNotifyNode final : public IRowNode`  
_L13-33_
- inherits: `IRowNode`
- desc: Row node that will broadcast a message when one or more of its parent nodes has been updated.
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRowNodeChange, const TSharedPtr<IRowNode>&);`
- L18 _public prototype_ `FRowChangeNotifyNode(TSharedPtr<IRowNode> ParentNode, FOnRowNodeChange ChangeEvent);`
- L19 _public prototype_ `virtual ~FRowChangeNotifyNode() override = default;`
- L21 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L22 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L23 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L24 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L27 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L30 _private member_ `TSharedPtr<IRowNode> Parent;`
- L31 _private member_ `RevisionId CachedParentRevision = UninitializedRevisionId;`
- L32 _private member_ `FOnRowNodeChange OnChangeEvent;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRowNodeChange, const TSharedPtr<IRowNode>&);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowCopyNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowCopyNode`  
`class FRowCopyNode : public IRowNode`  
_L17-39_
- inherits: `IRowNode`
- desc: Copies the content of the parent node to a local array. This node can be used to avoid changes to the parent node being made. An example usage would be if the parent node is sorted by row handle for performance reasons but the final list needs to be sorted based on other criteria.
- L20 _public prototype_ `explicit FRowCopyNode(TSharedPtr<IRowNode> InParent);`
- L21 _public prototype_ `virtual ~FRowCopyNode() override = default;`
- L24 _public prototype_ `void Reset();` — Clears out the current row list and gets a fresh copy from the parent.
- L26 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L27 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L28 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L29 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L32 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L35 _private member_ `FRowHandleArray Rows;`
- L36 _private member_ `TSharedPtr<IRowNode> Parent;`
- L37 _private member_ `RevisionId ParentRevision = UninitializedRevisionId;`
- L38 _private member_ `RevisionId Revision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L9 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowFilterNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowFilterNode`  
`class FRowFilterNode final : public IRowNode`  
_L22-90_
- inherits: `IRowNode`
- desc: Query stack node that filters out rows based on the provided filter. Performance-wise this will be slower than using filters on queries, but this node can be used when using query level filters is not possible.
- L25 _public function_ `FRowFilterNode(ICoreProvider* Storage, const TSharedPtr<IRowNode>& ParentRowNode, ICoreProvider::EFilterOptions Options, const Queries::TConstQueryFunction<bool>& Filter) : Storage(Storage) , Filter(Filter) , ParentRowNode(ParentRowNode) , Options(Options)`
- L34 _public function_ `FRowFilterNode(ICoreProvider* Storage, const TSharedPtr<IRowNode>& ParentRowNode, const Queries::TConstQueryFunction<bool>& Filter) : FRowFilterNode( Storage, ParentRowNode, ICoreProvider::EFilterOptions::Default, Filter)`
- L47 _public function_ `FRowFilterNode(ICoreProvider* Storage, const TSharedPtr<IRowNode>& ParentRowNode, ICoreProvider::EFilterOptions Options, FilterFunction&& Filter) : FRowFilterNode( Storage, ParentRowNode, Options, Queries::BuildConstQueryFunction<bool>(Forward<FilterFunction>(Filter)))`
- L61 _public function_ `FRowFilterNode(ICoreProvider* Storage, const TSharedPtr<IRowNode>& ParentRowNode, FilterFunction&& Filter) : FRowFilterNode( Storage, ParentRowNode, ICoreProvider::EFilterOptions::Default, Queries::BuildConstQueryFunction<bool>(Forward<FilterFunction>(Filter)))`
- L69 _public prototype_ `virtual ~FRowFilterNode() override = default;`
- L71 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L72 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L73 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L74 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L77 _public prototype_ `void ForceRefresh();` — Call this when external inputs into the filter, such as search strings or filtering groups, have been updated.
- L80 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L83 _private member_ `ICoreProvider* Storage;`
- L84 _private member_ `Queries::TConstQueryFunction<bool> Filter;`
- L85 _private member_ `FRowHandleArray Rows;`
- L86 _private member_ `TSharedPtr<IRowNode> ParentRowNode;`
- L87 _private member_ `RevisionId CachedParentRevisionID = UninitializedRevisionId;`
- L88 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L89 _private member_ `ICoreProvider::EFilterOptions Options;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowHandleSortNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowHandleSortNode`  
`class FRowHandleSortNode : public IRowNode`  
_L15-32_
- inherits: `IRowNode`
- desc: Sorts the rows in the parent by row handle. Prefer this over using the FRowSortNode when sorting by row handle as this is somewhat faster and allows the row handle array to keep its sorted status. If the row handle array is already sorted this node doesn't do any work, making it even faster than using FRowSortNode.
- L18 _public prototype_ `explicit FRowHandleSortNode(TSharedPtr<IRowNode> InParent);`
- L19 _public prototype_ `virtual ~FRowHandleSortNode() override = default;`
- L21 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L22 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L23 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L24 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L27 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L30 _private member_ `TSharedPtr<IRowNode> Parent;`
- L31 _private member_ `RevisionId ParentRevision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L7 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowMergeNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowMergeNode`  
`class FRowMergeNode : public IRowNode`  
_L12-47_
- inherits: `IRowNode`
- L23 _public prototype_ `FRowMergeNode(TConstArrayView<TSharedPtr<IRowNode>> InParents, EMergeApproach InMergeApproach);`
- L24 _public prototype_ `virtual ~FRowMergeNode() override = default;`
- L26 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L27 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L28 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L29 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L32 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L35 _private prototype_ `void Merge();`
- L43 _private member_ `TArray<FParentInfo> Parents;`
- L44 _private member_ `FRowHandleArray Rows;`
- L45 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L46 _private member_ `EMergeApproach MergeApproach;`

#### enum `UE::Editor::DataStorage::QueryStack::FRowMergeNode::EMergeApproach`  
`enum class EMergeApproach`  
_L15-21_
- L17 _public enumerator_ `Append` — The rows in each parent are added at the end of the final array.
- L18 _public enumerator_ `Sorted` — The rows in each parent are combined together in a final sorted array.
- L19 _public enumerator_ `Unique` — The rows in each parent are combined then sorted and all duplicates are removed from the final array.
- L20 _public enumerator_ `Repeating` — The rows in each parent are combined then sorted and only rows that appear in at least 2 parents are kept.

#### struct `UE::Editor::DataStorage::QueryStack::FRowMergeNode::FParentInfo`  
`struct FParentInfo`  
_L37-41_
- L39 _public member_ `TSharedPtr<IRowNode> Parent;`
- L40 _public member_ `RevisionId Revision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L10 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowMonitorNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowMonitorNode`  
`class FRowMonitorNode : public IRowNode`  
_L20-75_
- inherits: `IRowNode`
- desc: Monitors tables for the addition and removal of one or more column types and updates the internal status if a change is detected.
- L24 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowsChanged, FRowHandleArrayView );`
- L26 _public prototype_ `FRowMonitorNode( ICoreProvider& InStorage, TSharedPtr<IRowNode> InParentNode, TSharedPtr<IQueryNode> InQueryNode);`
- L28 _public prototype_ `FRowMonitorNode( ICoreProvider& InStorage, TSharedPtr<IRowNode> InParentNode, TArray<TObjectPtr<const UScriptStruct>> InColumns);`
- L30 _public prototype_ `FRowMonitorNode( ICoreProvider& InStorage, TSharedPtr<IQueryNode> InQueryNode, TSharedPtr<IRowNode> InParentNode, TArray<TObjectPtr<const UScriptStruct>> InMonitoredColumns);`
- L36 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L37 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L38 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L39 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L46 _public prototype_ `FOnRowsChanged& OnMonitoredRowsAdded();` — Event that is called during Update() to allow systems to respond to monitored rows being added
- L49 _public prototype_ `FOnRowsChanged& OnMonitoredRowsRemoved();` — Event that is called during Update() to allow systems to respond to monitored rows being removed
- L52 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L55 _private prototype_ `void UpdateColumnsFromQuery();`
- L56 _private prototype_ `void UpdateMonitoredColumns();`
- L57 _private prototype_ `void ResolveRemovedRows();`
- L59 _private member_ `FRowHandleArray AddedRows;`
- L60 _private member_ `FRowHandleArray RemovedRows;`
- L62 _private member_ `TArray<QueryHandle> Observers;`
- L63 _private member_ `TArray<TObjectPtr<const UScriptStruct>> MonitoredColumns;`
- L65 _private member_ `TSharedPtr<IQueryNode> QueryNode;`
- L66 _private member_ `TSharedPtr<IRowNode> ParentNode;`
- L67 _private member_ `ICoreProvider& Storage;`
- L68 _private member_ `RevisionId QueryRevision = UninitializedRevisionId;`
- L69 _private member_ `RevisionId ParentRevision = UninitializedRevisionId;`
- L70 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L71 _private member_ `bool bFixedColumns = false;`
- L73 _private member_ `FOnRowsChanged RowsAddedEvent;`
- L74 _private member_ `FOnRowsChanged RowsRemovedEvent;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRowsChanged, FRowHandleArrayView );`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowOrderInversionNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowOrderInversionNode`  
`class FRowOrderInversionNode : public IRowNode`  
_L15-41_
- inherits: `IRowNode`
- desc: When enabled, orders the rows on the parent in reverse. If disabled, this row has no effect, but if the order on the parent was inverted it will remain inverted.
- L18 _public prototype_ `FRowOrderInversionNode(TSharedPtr<IRowNode> InParent, bool bInIsEnabled);`
- L19 _public prototype_ `virtual ~FRowOrderInversionNode() override = default;`
- L22 _public prototype_ `void Enable(bool bInIsEnabled);` — Clears out the current row list and gets a fresh copy from the parent.
- L23 _public prototype_ `bool IsEnabled() const;`
- L25 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L26 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L27 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L28 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L31 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L34 _private prototype_ `void ApplyOrder();`
- L36 _private member_ `TSharedPtr<IRowNode> Parent;`
- L37 _private member_ `RevisionId ParentRevision = UninitializedRevisionId;`
- L38 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L39 _private member_ `bool bIsEnabled = true;`
- L40 _private member_ `bool bRequiresSync = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L9 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowQueryResultsNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowQueryResultsNode`  
`class FRowQueryResultsNode : public IRowNode`  
_L23-84_
- inherits: `IRowNode`
- desc: Used to convert an IQueryNode into an IRowNode by extracting the rows the query references optionally during update. This node is cheap to setup, but has diminishing returns when the number of rows increases and when updates happen frequently as it has to fully extract all rows from TEDS whenever Refresh is called. Use on small tables when the number of calls to Refresh can be minimized.
- L33 _public typedef_ `using ESyncFlags UE_DEPRECATED(5.8, "'ESyncFlags' has been depr`
- L56 _public prototype_ `FRowQueryResultsNode(ICoreProvider& Storage, TSharedPtr<IQueryNode> InQueryNode);`
- L57 _public prototype_ `FRowQueryResultsNode(ICoreProvider& Storage, TSharedPtr<IQueryNode> InQueryNode, ESyncActions InSyncAction);`
- L58 _public prototype_ `virtual ~FRowQueryResultsNode() override = default;`
- L60 _public prototype_ `void Refresh();`
- L61 _public prototype_ `void Refresh(FTimespan AllottedTime);`
- L63 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L64 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L65 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L66 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L69 _public prototype_ `FRowQueryResultsNode(ICoreProvider& Storage, TSharedPtr<IQueryNode> InQueryNode, EDeprecatedSyncFlags InSyncFlags);` — `UE_DEPRECATED(5.8, "'ESyncFlags' has been deprecated, please use 'ESyncActions'.")`
- L72 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L73 _protected prototype_ `virtual void RefreshInternal(FTimespan AllottedTime, FRowHandleArray& TargetRows);`
- L74 _protected prototype_ `virtual void RefreshInternal(FRowHandleArray& TargetRows);`
- L75 _protected function_ `virtual void QueryUpdated()`
- L77 _protected member_ `FRowHandleArray Rows;`
- L78 _protected member_ `TSharedPtr<IQueryNode> QueryNode;`
- L79 _protected member_ `ICoreProvider& Storage;`
- L80 _protected member_ `uint64 TopologyHash = 0;`
- L81 _protected member_ `RevisionId QueryRevision = UninitializedRevisionId;`
- L82 _protected member_ `RevisionId Revision = UninitializedRevisionId;`
- L83 _protected member_ `ESyncActions SyncAction = ESyncActions::RefreshOnUpdate;`

#### enum `UE::Editor::DataStorage::QueryStack::FRowQueryResultsNode::EDeprecatedSyncFlags`  
`enum class EDeprecatedSyncFlags`  
_L26-32_
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `RefreshOnUpdate = 1 << 0`
- L30 _public enumerator_ `RefreshOnQueryChange = 1 << 1`
- L31 _public enumerator_ `IncrementWhenDifferent = 1 << 2`

#### enum `UE::Editor::DataStorage::QueryStack::FRowQueryResultsNode::ESyncActions`  
`enum class ESyncActions`  
_L35-54_
- L40 _public enumerator_ `None` — The node is never updated and requires an explicit call to "Refresh".
- L45 _public enumerator_ `RefreshOnUpdate` — Each time "Update" is called the state of the query is checked and compared with the cached state. If any row additions/removals are detected to any of the tables associated with the query it is rerun.
- L47 _public enumerator_ `RefreshOnQueryChange` — Only update the row list whenever the parent query changes.
- L53 _public enumerator_ `ForceRefreshOnUpdate` — Each time "Update" is called the query is run again and replaces the current set of rows. Unlike "RefreshOnUpdate", there is no caching done to mitigate the cost of running a query. This options is only recommended for debugging purposes as it can significantly impact performance.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowSortNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowSortNode`  
`class FRowSortNode : public IRowNode`  
_L31-70_
- inherits: `IRowNode`
- desc: Sorts the rows in the parent node using a provided column sorter. Column sorters can be found on on TEDS UI widget constructors, or custom sorters can be created.
- L34 _public prototype_ `FRowSortNode(ICoreProvider& InStorage, TSharedPtr<IRowNode> InParent, FTimespan InMaxFrameDuration = FTimespan::FromMilliseconds(10));`
- L36 _public prototype_ `FRowSortNode(ICoreProvider& InStorge, TSharedPtr<IRowNode> InParent, TSharedPtr<const FColumnSorterInterface> InColumnSorter, FTimespan InMaxFrameDuration = FTimespan::FromMilliseconds(10));`
- L38 _public prototype_ `virtual ~FRowSortNode() override = default;`
- L40 _public prototype_ `void SetColumnSorter(TSharedPtr<const FColumnSorterInterface> InColumnSorter);`
- L41 _public prototype_ `TSharedPtr<const FColumnSorterInterface> GetColumnSorter() const;`
- L42 _public prototype_ `bool IsSorting() const;`
- L44 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L45 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L46 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L47 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L50 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L53 _private prototype_ `void SetupFixedSize64();`
- L54 _private prototype_ `void SetupFixedSizeOnly();`
- L55 _private prototype_ `void SetupComparativeSort();`
- L56 _private prototype_ `void SetupHybridSort();`
- L58 _private member_ `TSharedPtr<const FColumnSorterInterface> ColumnSorter;`
- L59 _private member_ `TSharedPtr<IRowNode> Parent;`
- L61 _private member_ `TPimplPtr<Private::FSortContext> SortContext;`
- L63 _private member_ `FTimespan MaxFrameDuration;`
- L64 _private member_ `RevisionId LastUpdatedRevision = TNumericLimits<RevisionId>::Max();`
- L65 _private member_ `RevisionId Revision = UninitializedRevisionId;`
- L67 _private member_ `ICoreProvider& Storage;`
- L69 _private member_ `bool bIsParentUnique = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L21 _namespace_ `namespace Private` (scope `UE::Editor::DataStorage::QueryStack`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsQueryStack/Public/TedsRowViewNode.h` (Public)


#### class `UE::Editor::DataStorage::QueryStack::FRowViewNode`  
`class FRowViewNode : public IRowNode`  
_L14-34_
- inherits: `IRowNode`
- desc: Stores a reference to row handle array. The row handle array that this view is pointing to needs to be kept alive for as long as this Query Stack node is alive.
- L17 _public prototype_ `explicit FRowViewNode(FRowHandleArray& Rows);`
- L18 _public prototype_ `virtual ~FRowViewNode() override = default;`
- L20 _public prototype_ `void MarkDirty();`
- L21 _public prototype_ `void ResetView(FRowHandleArray& InRows);`
- L23 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L24 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L25 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;`
- L26 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L29 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L32 _private member_ `FRowHandleArray* Rows = nullptr;`
- L33 _private member_ `RevisionId Revision = 1;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
