# Plugins / MassLOD

- module root: `Plugins/Runtime/MassGameplay/Source/MassLOD`
- headers: 13; symbols: 350
- symbol kinds: class=8, delegate=2, enum=7, enumerator=24, externvar=4, function=64, macro=7, member=98, namespace=9, prototype=84, struct=37, typedef=4, variable=2
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassSimulation, MassSpawner

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/IMassLODModule.h` (Public)


#### class `IMassLODModule`  
`class IMassLODModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassLODModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODCalculator.h` (Public)


#### struct `TMassLODCalculator`  
`template <typename FLODLogic = FLODDefaultLogic > struct TMassLODCalculator : public FMassLODBaseLogic`  
_L16-291_
- inherits: `FMassLODBaseLogic`
- desc: Helper struct to calculate LOD for each agent and maximize count per LOD Requires TViewerInfoFragment fragment collected by the TMassLODCollector. Stores information in TLODFragment fragment.
- L18 _public function_ `TMassLODCalculator() : FMassLODBaseLogic( FLODLogic::bDoVisibilityLogic)`
- L32 _public prototype_ `void Initialize(const float InBaseLODDistance[EMassLOD::Max], const float InBufferHysteresisOnDistanceRatio, const int32 InLODMaxCount[EMassLOD::Max], const int32 InLODMaxCountPerViewer[EMassLOD::Max] = nullptr, const float InVisibleDistanceToFrustum = 0.0f, const float InVisibleDistanceToFrustumHysteresis = 0.0f, const float InVisibleLODDistance[EMassLOD::Max] = nullptr);` — Initializes the LOD calculator, needed to be called once at initialization time @Param InBaseLODDistance distances used to calculate LOD @Param InBufferHysteresisOnFOVRatio distance hysteresis used to calculate LOD @Param InLODMaxCount the maximum count for each LOD - Supports nullptr being passed in now and will put INT_MAX everywhere by default @Param InLODMaxCountPerViewer the maximum count for each LOD per viewer (Only when FLODLogic::bMaximizeCountPerViewer is enabled) @Param InVisibleDistanceToFrustum is the distance from the frustum to start considering this entity is visible (Only when FLODLogic::bDoVisibilityLogic is enabled) @Param InVisibleDistanceToFrustumHysteresis once visible, what extra distance the entity need to be before considered not visible anymore (Only when FLODLogic::bDoVisibilityLogic is enabled) @Param InVisibleLODDistance the maximum count for each LOD per viewer (Only when FLODLogic::bDoVisibilityLogic is enabled)
- L44 _public prototype_ `void PrepareExecution(TConstArrayView<FViewerInfo> Viewers);` — Prepares execution for the current frame, needed to be called before every execution @Param Viewers is the array of all the known viewers
- L57 _public function_ `inline void CalculateLOD(FMassExecutionContext& Context, TConstArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TLODFragment> LODList)`
- L88 _public prototype_ `void CalculateLOD(FMassExecutionContext& Context, TConstArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TLODFragment> LODList, TConstArrayView<TPerViewerInfoFragment> PerViewerInfoList);`
- L100 _public prototype_ `bool AdjustDistancesFromCount();`
- L113 _public function_ `inline void AdjustLODFromCount(FMassExecutionContext& Context, TConstArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TLODFragment> LODList)`
- L145 _public prototype_ `void AdjustLODFromCount(FMassExecutionContext& Context, TConstArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TLODFragment> LODList, TConstArrayView<TPerViewerInfoFragment> PerViewerInfoList);`
- L156 _public prototype_ `template <typename TLODFragment> void ForceOffLOD(FMassExecutionContext& Context, TArrayView<TLODFragment> LODList);` — Turn Off all LOD, called for each entity chunks @Param Context of the chunk execution @Param LODList is the fragment where calculation are stored
- L167 _public prototype_ `template <typename TLODFragment, typename TTransformFragment> void DebugDisplayLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UWorld* World);` — Debug draw the current state of each agent as a color coded square @Param Context of the chunk execution @Param LODList is the fragment where calculation are stored @Param LocationList is the fragment transforms of the entities @Param World where the debug display should be drawn
- L178 _public prototype_ `template <typename TLODFragment, typename TTransformFragment> void DebugDisplaySignificantLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UWorld* World, float MaxLODSignificance);` — Debug draw the current state of each agent as a color coded square, within MaxLODSignificance range @Param Context of the chunk execution @Param LODList is the fragment where calculation are stored @Param LocationList is the fragment transforms of the entities @Param World where the debug display should be drawn @Param MaxLODSignificance is the max allowed value of LODList[i].LODSignificance for an agent's state to debug draw
- L188 _public prototype_ `template <typename TLODFragment, typename TTransformFragment> void VisLogLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UObject* LogOwner);` — Add Visual Log entries for the current state of each agent as a color coded location @Param Context of the chunk execution @Param LODList is the fragment where calculation are stored @Param LocationList is the fragment transforms of the entities @Param World where the debug display should be drawn
- L199 _public prototype_ `template <typename TLODFragment, typename TTransformFragment> void VisLogSignificantLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UObject* LogOwner, float MaxLODSignificance);` — Add Visual Log entries for the current state of each agent as a color coded location, within MaxLODSignificance range @Param Context of the chunk execution @Param LODList is the fragment where calculation are stored @Param LocationList is the fragment transforms of the entities @Param World where the debug display should be drawn @Param MaxLODSignificance is the max allowed value of LODList[i].LODSignificance for an agent's state to vislog
- L205 _public function_ `float GetMaxLODDistance() const` — Return the maximum distance at which the LOD will be turn off
- L250 _protected prototype_ `template <bool bCalculateVisibility, bool bCalculateLODSignificance> float AccumulateCountInRuntimeData(const EMassLOD::Type LOD, const float ViewerDistanceSq, const bool bIsVisible, FMassLODRuntimeData& Data) const;`
- L253 _protected prototype_ `template <bool bCalculateVisibility> bool AdjustDistancesFromCountForRuntimeData(const TStaticArray<int32, EMassLOD::Max>& MaxCount, FMassLODRuntimeData& RuntimeData) const;`
- L256 _protected prototype_ `template<bool bCalculateVisibility> EMassLOD::Type ComputeLODFromSettings(const EMassLOD::Type PrevLOD, const float DistanceToViewerSq, const bool bIsVisible, bool* bIsInAVisibleRange, const FMassLODRuntimeData& Data) const;`
- L258 _protected prototype_ `bool CalculateVisibility(const bool bWasVisible, const float DistanceToFrustum) const;`
- L261 _protected member_ `TStaticArray<float, EMassLOD::Max> BaseLODDistance;` — LOD distances
- L262 _protected member_ `TStaticArray<float, EMassLOD::Max> VisibleLODDistance;`
- L265 _protected member_ `TStaticArray<int32, EMassLOD::Max> LODMaxCount;` — MaxCount total
- L268 _protected member_ `TStaticArray<int32, EMassLOD::Max> LODMaxCountPerViewer;` — MaxCount total per viewers
- L271 _protected member_ `float BufferHysteresisOnDistanceRatio = 0.1f;` — Ratio for Buffer Distance Hysteresis
- L274 _protected member_ `float VisibleDistanceToFrustum = 0.0f;` — How far away from frustum does this entities are considered visible
- L277 _protected member_ `float VisibleDistanceToFrustumWithHysteresis = 0.0f;` — Once visible how much further than distance to frustum does the entities need to be before being consider not visible
- L280 _protected member_ `TStaticArray<float, EMassLOD::Max> BaseBucketSize;` — The size of each subdivision per LOD (LOD Size/MaxBucketsPerLOD)
- L281 _protected member_ `TStaticArray<float, EMassLOD::Max> VisibleBucketSize;`
- L284 _protected member_ `float MaxLODDistance = 0.0f;` — Maximum LOD Distance
- L287 _protected member_ `FMassLODRuntimeData RuntimeData;` — Runtime data for LOD calculation
- L290 _protected member_ `TArray<FMassLODRuntimeData> RuntimeDataPerViewer;` — Runtime data for each viewer specific LOD calculation, used only when bMaximizeCountPerViewer is true
- L294 _function_ `template <typename FLODLogic> void TMassLODCalculator<FLODLogic>::Initialize(const float InBaseLODDistance[EMassLOD::Max], const float InBufferHysteresisOnDistanceRatio, const int32 InLODMaxCount[EMassLOD::Max], const int32 InLODMaxCountPerViewer[EMassLOD::Max] , const float InVisibleDistanceToFrustum , const float InVisibleDistanceToFrustumHysteresis , const float InVisibleLODDistance[EMassLOD::Max] )`
- L358 _function_ `template <typename FLODLogic> bool TMassLODCalculator<FLODLogic>::CalculateVisibility(const bool bWasVisible, const float DistanceToFrustum) const`
- L364 _function_ `template <typename FLODLogic> void TMassLODCalculator<FLODLogic>::PrepareExecution(TConstArrayView<FViewerInfo> ViewersInfo)`
- L387 _function_ `template <typename FLODLogic> template <bool bCalculateVisibility, bool bCalculateLODSignificance> float TMassLODCalculator<FLODLogic>::AccumulateCountInRuntimeData(const EMassLOD::Type LOD, const float ViewerDistanceSq, const bool bIsVisible, FMassLODRuntimeData& Data) const`
- L425 _function_ `void TMassLODCalculator<FLODLogic>::CalculateLOD(FMassExecutionContext& Context, TConstArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TLODFragment> LODList, TConstArrayView<TPerViewerInfoFragment> PerViewerInfoList)`
- L534 _function_ `template <typename FLODLogic> template <bool bCalculateVisibility> bool TMassLODCalculator<FLODLogic>::AdjustDistancesFromCountForRuntimeData(const TStaticArray<int32, EMassLOD::Max>& MaxCount, FMassLODRuntimeData& Data) const`
- L647 _function_ `template <typename FLODLogic> template <bool bCalculateVisibility, bool bCalculateVisibilityPerViewer, bool bMaximizeCountPerViewer> bool TMassLODCalculator<FLODLogic>::AdjustDistancesFromCount()`
- L674 _function_ `void TMassLODCalculator<FLODLogic>::AdjustLODFromCount(FMassExecutionContext& Context, TConstArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TLODFragment> LODList, TConstArrayView<TPerViewerInfoFragment> PerViewerInfoList)`
- L764 _function_ `template <typename FLODLogic> template <typename TLODFragment> void TMassLODCalculator<FLODLogic>::ForceOffLOD(FMassExecutionContext& Context, TArrayView<TLODFragment> LODList)`
- L801 _function_ `template <typename FLODLogic> template <typename TLODFragment, typename TTransformFragment> void TMassLODCalculator<FLODLogic>::DebugDisplayLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UWorld* World)`
- L814 _function_ `template <typename FLODLogic> template <typename TLODFragment, typename TTransformFragment> void TMassLODCalculator<FLODLogic>::DebugDisplaySignificantLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UWorld* World, const float MaxLODSignificance)`
- L830 _function_ `template <typename FLODLogic> template <typename TLODFragment, typename TTransformFragment> void TMassLODCalculator<FLODLogic>::VisLogLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UObject* LogOwner)`
- L845 _function_ `template <typename FLODLogic> template <typename TLODFragment, typename TTransformFragment> void TMassLODCalculator<FLODLogic>::VisLogSignificantLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TConstArrayView<TTransformFragment> LocationList, UObject* LogOwner, const float MaxLODSignificance)`
- L864 _function_ `template <typename FLODLogic> template<bool bCalculateVisibility> EMassLOD::Type TMassLODCalculator<FLODLogic>::ComputeLODFromSettings(const EMassLOD::Type PrevLOD, const float DistanceToViewerSq, const bool bIsVisible, bool* bIsInAVisibleRange, const FMassLODRuntimeData& Data) const`

#### struct `TMassLODCalculator::FMassLODRuntimeData`  
`struct FMassLODRuntimeData`  
_L209-246_
- L212 _public function_ `void Reset(const TStaticArray<float, EMassLOD::Max>& InBaseLODDistance, const TStaticArray<float, EMassLOD::Max>& InVisibleLODDistance)` — Reset values to default
- L233 _public member_ `TStaticArray<float, EMassLOD::Max> AdjustedBaseLODDistanceSq;` — Distance where each LOD becomes relevant (Squared and Normal)
- L234 _public member_ `TStaticArray<float, EMassLOD::Max> AdjustedVisibleLODDistanceSq;`
- L235 _public member_ `TStaticArray<float, EMassLOD::Max> AdjustedBaseLODDistance;`
- L236 _public member_ `TStaticArray<float, EMassLOD::Max> AdjustedVisibleLODDistance;`
- L239 _public member_ `TStaticArray< TStaticArray<int32, UE::MassLOD::MaxBucketsPerLOD>, EMassLOD::Max > BaseBucketCounts;` — Count of entities in each subdivision
- L240 _public member_ `TStaticArray< TStaticArray<int32, UE::MassLOD::MaxBucketsPerLOD>, EMassLOD::Max > VisibleBucketCounts;`
- L244 _public member_ `TStaticArray<int32, EMassLOD::Max> LastCalculatedLODCount;` — Last calculation count per LOD

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODCollector.h` (Public)


#### struct `TMassLODCollector`  
`template <typename FLODLogic = FLODDefaultLogic > struct TMassLODCollector : public FMassLODBaseLogic`  
_L16-73_
- inherits: `FMassLODBaseLogic`
- desc: Helper struct to collect needed information on each agent that will be needed later for LOD calculation Requires TTransformFragment fragment. Stores information in TViewerInfoFragment fragment.
- L18 _public function_ `TMassLODCollector() : FMassLODBaseLogic( FLODLogic::bDoVisibilityLogic)`
- L26 _public prototype_ `void PrepareExecution(TConstArrayView<FViewerInfo> Viewers);` — Prepares execution for the current frame, needed to be called before every execution @Param Viewers is the array of all the known viewers
- L39 _public function_ `inline void CollectLODInfo(FMassExecutionContext& Context, TConstArrayView<TTransformFragment> TransformList, TArrayView<TViewerInfoFragment> ViewersInfoList)`
- L69 _public prototype_ `void CollectLODInfo(FMassExecutionContext& Context, TConstArrayView<TTransformFragment> TransformList, TArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TPerViewerInfoFragment> PerViewerInfoList);`
- L76 _function_ `template <typename FLODLogic> void TMassLODCollector<FLODLogic>::PrepareExecution(TConstArrayView<FViewerInfo> ViewersInfo)`
- L89 _function_ `void TMassLODCollector<FLODLogic>::CollectLODInfo(FMassExecutionContext& Context, TConstArrayView<TTransformFragment> TransformList, TArrayView<TViewerInfoFragment> ViewersInfoList, TArrayView<TPerViewerInfoFragment> PerViewerInfoList)`

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODCollectorProcessor.h` (Public)


#### struct `FMassGenericCollectorLogic`  
`struct FMassGenericCollectorLogic : public FLODDefaultLogic`  
_L14-20_
- inherits: `FLODDefaultLogic`

#### enum `FMassGenericCollectorLogic::(anonymous)`  
``  
_L17-19_

#### class `UMassLODCollectorProcessor`  
`class UMassLODCollectorProcessor : public UMassProcessor`  
_L26-54_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "LOD Collector"))`
- inherits: `UMassProcessor`
- desc: LOD collector which combines collection of LOD information for both Viewer and Simulation LODing when possible.
- L31 _public prototype_ `UMassLODCollectorProcessor();`
- L34 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L35 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L38 _protected prototype_ `template <bool bLocalViewersOnly> void CollectLODForChunk(FMassExecutionContext& Context);`
- L41 _protected prototype_ `template <bool bLocalViewersOnly> void ExecuteInternal(FMassEntityManager& EntityManager, FMassExecutionContext& Context);`
- L43 _protected member_ `TMassLODCollector<FMassGenericCollectorLogic> Collector;`
- L47 _protected member_ `FMassEntityQuery EntityQuery_VisibleRangeAndOnLOD;` — All entities that are in visible range and are On LOD
- L49 _protected member_ `FMassEntityQuery EntityQuery_VisibleRangeOnly;` — All entities that are in visible range but are Off LOD
- L51 _protected member_ `FMassEntityQuery EntityQuery_OnLODOnly;` — All entities that are NOT in visible range but are On LOD
- L53 _protected member_ `FMassEntityQuery EntityQuery_NotVisibleRangeAndOffLOD;` — All entities that are Not in visible range and are at Off LOD

#### Free symbols / members of external scopes

- L18 _enumerator_ `bDoVisibilityLogic = true` (scope `FMassGenericCollectorLogic::__anon4a67796d0103`)

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODDistanceCollectorProcessor.h` (Public)


#### class `UMassLODDistanceCollectorProcessor`  
`class UMassLODDistanceCollectorProcessor : public UMassProcessor`  
_L20-48_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "LOD Distance Collector"))`
- inherits: `UMassProcessor`
- desc: LOD Distance collector which combines collection of LOD information for both Viewer and Simulation LODing. This collector cares only about the entities' distance to LOD viewer location, nothing else. Matches MassDistanceLODProcessor logic which uses the same Calculator LODLogic
- L25 _public prototype_ `UMassLODDistanceCollectorProcessor();`
- L28 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L29 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L32 _protected prototype_ `template <bool bLocalViewersOnly> void CollectLODForChunk(FMassExecutionContext& Context);`
- L35 _protected prototype_ `template <bool bLocalViewersOnly> void ExecuteInternal(FMassEntityManager& EntityManager, FMassExecutionContext& Context);`
- L37 _protected member_ `TMassLODCollector<FMassDistanceLODLogic> Collector;`
- L41 _protected member_ `FMassEntityQuery EntityQuery_RelevantRangeAndOnLOD;` — All entities that are in relevant range and are On LOD
- L43 _protected member_ `FMassEntityQuery EntityQuery_RelevantRangeOnly;` — All entities that are in relevant range but are Off LOD
- L45 _protected member_ `FMassEntityQuery EntityQuery_OnLODOnly;` — All entities that are NOT in relevant range but are On LOD
- L47 _protected member_ `FMassEntityQuery EntityQuery_NotRelevantRangeAndOffLOD;` — All entities that are Not in relevant range and are at Off LOD

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODFragments.h` (Public)


#### struct `FMassHighLODTag`  
`struct FMassHighLODTag : public FMassTag`  
_L10-13_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassMediumLODTag`  
`struct FMassMediumLODTag : public FMassTag`  
_L16-19_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassLowLODTag`  
`struct FMassLowLODTag : public FMassTag`  
_L22-25_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassOffLODTag`  
`struct FMassOffLODTag : public FMassTag`  
_L28-31_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassViewerInfoFragment`  
`struct FMassViewerInfoFragment : public FMassFragment`  
_L37-48_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Data fragment to store the calculated distances to viewers
- L43 _public member_ `float ClosestViewerDistanceSq = FLT_MAX;` — `UPROPERTY()` — Closest viewer distance
- L47 _public member_ `float ClosestDistanceToFrustum = FLT_MAX;` — `UPROPERTY()` — Closest distance to frustum

#### struct `FMassVariableTickChunkFragment`  
`struct FMassVariableTickChunkFragment : public FMassChunkFragment`  
_L51-100_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L55 _public function_ `bool ShouldTickThisFrame() const`
- L60 _public function_ `float GetTimeUntilNextTick() const`
- L65 _public function_ `int32 GetLastChunkSerialModificationNumber() const`
- L70 _public function_ `EMassLOD::Type GetLOD() const`
- L75 _public function_ `void SetLOD(EMassLOD::Type InLOD)`
- L81 _public function_ `void Update(const bool bInShouldTickThisFrame, const float InTimeUntilNextTick, int32 ChunkSerialModificationNumber)`
- L90 _private member_ `bool bShouldTickThisFrame = true;` — `UPROPERTY()`
- L93 _private member_ `TEnumAsByte<EMassLOD::Type> LOD = EMassLOD::Max;` — `UPROPERTY()`
- L96 _private member_ `float TimeUntilNextTick = 0.0f;` — `UPROPERTY()`
- L99 _private member_ `int32 LastChunkSerialModificationNumber = INDEX_NONE;` — `UPROPERTY()`

#### struct `FMassCollectLODViewerInfoTag`  
`struct FMassCollectLODViewerInfoTag : public FMassTag`  
_L103-106_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassCollectDistanceLODViewerInfoTag`  
`struct FMassCollectDistanceLODViewerInfoTag : public FMassTag`  
_L112-115_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag to use to trigger the collector processor that uses the LODCollector without Visibility Logic, so strictly based of distance

#### struct `FMassVisibilityCanBeSeenTag`  
`struct FMassVisibilityCanBeSeenTag : public FMassTag`  
_L118-121_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassVisibilityCulledByFrustumTag`  
`struct FMassVisibilityCulledByFrustumTag : public FMassTag`  
_L124-127_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassVisibilityCulledByDistanceTag`  
`struct FMassVisibilityCulledByDistanceTag : public FMassTag`  
_L130-133_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FMassVisualizationChunkFragment`  
`struct FMassVisualizationChunkFragment : public FMassChunkFragment`  
_L136-248_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L147 _public function_ `static bool AreAnyEntitiesVisibleInChunk(const FMassExecutionContext& Context)` — Fetched existing chunk fragment to know if there is a possibility of an entity that is visible. In the case that there is not chunk information, we cannot assume that all entities are not visible. @param Context of the execution from the entity sub system @return true if there is a possibility that the chunk contains a visible entity
- L158 _public function_ `bool AreAnyEntitiesVisible() const` — Returns if there could be a visible entities in that chunk @return true if that is the case
- L172 _public function_ `static bool IsChunkHandledThisFrame(const FMassExecutionContext& Context)` — IsChunkHandledThisFrame This function is used by LOD collector query chunk filters to check that visual LOD will be updated this frame. It defaults to false (no LOD update), if visualization chunk fragment is NOT present. @param Context of the execution from the entity sub system @return true if the visual LOD will be updated this frame
- L187 _public function_ `static bool ShouldUpdateVisualizationForChunk(const FMassExecutionContext& Context)` — ShouldUpdateVisualizationForChunk This function is used by query chunk filters in processors that require variable visual LOD update. It defaults to true (always updating) if visualization chunk fragment is NOT present. @param Context of the execution from the entity sub system @return true if the chunk should update the visual this frame
- L199 _public function_ `bool ShouldUpdateVisualization() const` — Representation type of all currently visible entities are always updated But as an optimization, we use a frequency check on the not visible one. @return true if we should update the representation type for this chunk
- L204 _public function_ `void SetContainsNewlyVisibleEntity(bool bInContainsNewlyVisibleEntity)`
- L213 _public function_ `void SetVisibility(const EMassVisibility InVisibility)`
- L219 _public function_ `EMassVisibility GetVisibility() const`
- L224 _public function_ `float GetDeltaTime() const`
- L229 _public function_ `void Update(float InDeltaTime)`
- L239 _protected member_ `EMassVisibility Visibility = EMassVisibility::Max;` — `UPROPERTY()` — Visibility of the current chunk, should never change
- L243 _protected member_ `bool bContainsNewlyVisibleEntity = true;` — `UPROPERTY()` — Not visible chunks, might contains entity that are newly visible and not yet moved.
- L247 _protected member_ `float DeltaTime = 0;` — `UPROPERTY()` — Not visible chunks delta time until next update

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODLogic.h` (Public)


#### struct `FLODDefaultLogic`  
`struct FLODDefaultLogic`  
_L29-40_
- desc: Traits for LOD logic calculation behaviors

#### enum `FLODDefaultLogic::(anonymous)`  
``  
_L32-39_

#### struct `FMassSimulationLODLogic`  
`struct FMassSimulationLODLogic : public FLODDefaultLogic`  
_L42-44_
- inherits: `FLODDefaultLogic`

#### struct `FMassRepresentationLODLogic`  
`struct FMassRepresentationLODLogic : public FLODDefaultLogic`  
_L46-54_
- inherits: `FLODDefaultLogic`

#### enum `FMassRepresentationLODLogic::(anonymous)`  
``  
_L49-53_

#### struct `FMassCombinedLODLogic`  
`struct FMassCombinedLODLogic : public FLODDefaultLogic`  
_L56-64_
- inherits: `FLODDefaultLogic`

#### enum `FMassCombinedLODLogic::(anonymous)`  
``  
_L59-63_

#### struct `FMassDistanceLODLogic`  
`struct FMassDistanceLODLogic : public FLODDefaultLogic`  
_L71-78_
- inherits: `FLODDefaultLogic`
- desc: Simplest version of RepresentationLODLogic strictly based on Distance to Viewer Compared to FMassRepresentationLODLogic, we: * Do not care about doing the Visibility Logic * For now we will keep the Significance computation as it could allow for finer grained control later on

#### enum `FMassDistanceLODLogic::(anonymous)`  
``  
_L74-77_

#### struct `FViewerLODInfo`  
`struct FViewerLODInfo`  
_L141-158_
- L144 _public member_ `bool bLocal = false;` — Boolean indicating the viewer is local or not
- L147 _public member_ `bool bClearData = false;` — Boolean indicating the viewer data needs to be cleared
- L150 _public member_ `FMassViewerHandle Handle;` — The handle to the viewer
- L153 _public member_ `FVector Location;` — Viewer location and looking direction
- L154 _public member_ `FVector Direction;`
- L157 _public member_ `FConvexVolume Frustum;` — Viewer frustum (will not include near and far planes)

#### struct `FMassLODBaseLogic`  
`struct FMassLODBaseLogic`  
_L163-200_
- desc: Base struct for the LOD calculation helpers
- L165 _public function_ `FMassLODBaseLogic(bool bShouldBuildFrustumData) : bBuildFrustumData(bShouldBuildFrustumData)`
- L170 _protected prototype_ `void CacheViewerInformation(TConstArrayView<FViewerInfo> ViewerInfos);`
- L173 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS(Condition, EMassLOD::Type, LODPerViewer);` — Per viewer LOD information conditional fragment accessors
- L174 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS(Condition, EMassLOD::Type, PrevLODPerViewer);`
- L177 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ACCESSORS(Condition, float, LODSignificance);` — LOD Significance conditional fragment accessors
- L180 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ACCESSORS(Condition, float, ClosestDistanceToFrustum);` — Visibility conditional fragment accessors
- L181 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ACCESSORS(Condition, EMassVisibility, Visibility);`
- L182 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ACCESSORS(Condition, EMassVisibility, PrevVisibility);`
- L185 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS(Condition, float, DistanceToViewerSq);` — Per viewer distance conditional fragment accessors
- L188 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS(Condition, float, DistanceToFrustum);` — Per viewer visibility conditional fragment accessors
- L189 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS(Condition, EMassVisibility, VisibilityPerViewer);`
- L190 _protected prototype_ `DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS(Condition, EMassVisibility, PrevVisibilityPerViewer);`
- L192 _protected member_ `TArray<FViewerLODInfo> Viewers;`
- L199 _private member_ `bool bBuildFrustumData = true;` — Setting to false will prevent costly FViewerLODInfo.Frustum creation. Makes sense only if that data is not required. Note that this property is not expected to be changed at runtime.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSLOD_API`
- L12 _macro_ `#define DECLARE_CONDITIONAL_MEMBER_ACCESSORS( Condition, MemberType, MemberName ) \`
- L18 _macro_ `#define DECLARE_CONDITIONAL_MEMBER_ARRAY_ACCESSORS( Condition, MemberType, MemberName ) \`
- L33 _enumerator_ `bStoreInfoPerViewer = false` (scope `FLODDefaultLogic::__anon0b5602140103`) — Enable to store all calculated information per viewer
- L34 _enumerator_ `bCalculateLODPerViewer = false` (scope `FLODDefaultLogic::__anon0b5602140103`) — Enable to calculate and store the result LOD per viewer in the FMassLODResultInfo::LODPerViewer and FMassLODResultInfo::PrevLODPerViewer, requires bStoreInfoPerViewer to be true as well.
- L35 _enumerator_ `bMaximizeCountPerViewer = false` (scope `FLODDefaultLogic::__anon0b5602140103`) — Enable to maximize count per viewer, requires a valid InLODMaxCountPerViewer parameter during initialization of TMassLODCalculator.
- L36 _enumerator_ `bDoVisibilityLogic = false` (scope `FLODDefaultLogic::__anon0b5602140103`) — Enable to calculate visibility and apply its own LOD distances. Requires a valid InVisibleLODDistance parameter during initialization of TMassLODCalculator.
- L37 _enumerator_ `bCalculateLODSignificance = false` (scope `FLODDefaultLogic::__anon0b5602140103`) — Enable to calculate and set the a more precise LOD floating point significance in member FMassLODResultInfo::LODSignificance.
- L38 _enumerator_ `bLocalViewersOnly = false` (scope `FLODDefaultLogic::__anon0b5602140103`) — Enable to calculate LOD from LocalViewersOnly, otherwise will be done on all viewers.
- L50 _enumerator_ `bDoVisibilityLogic = true` (scope `FMassRepresentationLODLogic::__anon0b5602140203`)
- L51 _enumerator_ `bCalculateLODSignificance = true` (scope `FMassRepresentationLODLogic::__anon0b5602140203`)
- L52 _enumerator_ `bLocalViewersOnly = true` (scope `FMassRepresentationLODLogic::__anon0b5602140203`)
- L60 _enumerator_ `bDoVisibilityLogic = true` (scope `FMassCombinedLODLogic::__anon0b5602140303`)
- L61 _enumerator_ `bCalculateLODSignificance = true` (scope `FMassCombinedLODLogic::__anon0b5602140303`)
- L62 _enumerator_ `bLocalViewersOnly = true` (scope `FMassCombinedLODLogic::__anon0b5602140303`)
- L75 _enumerator_ `bCalculateLODSignificance = true` (scope `FMassDistanceLODLogic::__anon0b5602140403`)
- L76 _enumerator_ `bLocalViewersOnly = true` (scope `FMassDistanceLODLogic::__anon0b5602140403`)

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODSubsystem.h` (Public)


#### struct `FMassViewerHandle`  
`struct FMassViewerHandle : public FIndexedHandleBase`  
_L23-28_
- reflection: `USTRUCT()`
- inherits: `FIndexedHandleBase`
- desc: Handle that lets you reference the concept of a viewer

#### struct `FViewerInfo`  
`struct FViewerInfo`  
_L31-71_
- reflection: `USTRUCT()`
- L35 _public prototype_ `FViewerInfo() = default;`
- L37 _public prototype_ `FViewerInfo(const FViewerInfo& Other) = default;`
- L41 _public member_ `TObjectPtr<AActor> ActorViewer = nullptr;` — `UPROPERTY(transient)`
- L43 _public member_ `FName StreamingSourceName;`
- L46 _public member_ `int8 EditorViewportClientIndex = INDEX_NONE;`
- L49 _public member_ `FMassViewerHandle Handle;`
- L50 _public member_ `uint32 HashValue = 0;`
- L52 _public member_ `FVector Location;`
- L53 _public member_ `FRotator Rotation;`
- L56 _public member_ `float FOV = 90.0f;` — Effective horizontal field of view in degrees at the viewer's actual viewport.
- L59 _public member_ `float AspectRatio = 16.0f / 9.0f;` — Effective viewport aspect ratio (W/H) used when constructing the cull frustum.
- L61 _public member_ `bool bEnabled = true;`
- L63 _public prototype_ `void Reset();`
- L65 _public prototype_ `bool IsLocal() const;`
- L67 _public prototype_ `APlayerController* GetPlayerController() const;`
- L70 _private member_ `TObjectPtr<APlayerController> PlayerController = nullptr;` — `UE_DEPRECATED_FORGAME(5.4, "PlayerController member variable has been deprecated in favor of more generic ActorViewer. Use that instead.")`

#### class `UMassLODSubsystem`  
`class UMassLODSubsystem : public UMassSubsystemBase`  
_L77-210_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig)`
- inherits: `UMassSubsystemBase`
- desc: Manager responsible to manage and synchronized available viewers
- L81 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewerAdded, const FViewerInfo& ViewerInfo);`
- L82 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewerRemoved, const FViewerInfo& ViewerInfo);`
- L86 _public function_ `bool IsValidViewer(const FMassViewerHandle& ViewerHandle) const` — Checks the validity of a viewer handle
- L89 _public prototype_ `int32 GetValidViewerIdx(const FMassViewerHandle& ViewerHandle) const;` — Returns the index of the viewer if valid, otherwise INDEX_NONE is return
- L92 _public function_ `const TArray<FViewerInfo>& GetViewers() const` — Returns the array of viewers
- L95 _public prototype_ `const TArray<FViewerInfo>& GetSynchronizedViewers();` — Synchronize the viewers if not done this frame and returns the updated array
- L98 _public prototype_ `FMassViewerHandle GetViewerHandleFromActor(const AActor& Actor) const;` — Returns viewer handle from the PlayerController pointer
- L101 _public prototype_ `FMassViewerHandle GetViewerHandleFromStreamingSource(const FName StreamingSourceName) const;` — Returns viewer handle from the streaming source name
- L104 _public prototype_ `APlayerController* GetPlayerControllerFromViewerHandle(const FMassViewerHandle& ViewerHandle) const;` — Returns PlayerController pointer from the viewer handle
- L107 _public function_ `FOnViewerAdded& GetOnViewerAddedDelegate()` — Returns the delegate called when new viewer are added to the list
- L110 _public function_ `FOnViewerRemoved& GetOnViewerRemovedDelegate()` — Returns the delegate called when viewer are removed from the list
- L112 _public prototype_ `void RegisterActorViewer(AActor& ActorViewer);`
- L113 _public prototype_ `void UnregisterActorViewer(AActor& ActorViewer);`
- L115 _public function_ `bool IsUsingPlayerPawnLocationInsteadOfCamera() const`
- L118 _public function_ `void DebugSetGatherPlayers(const bool bInValue)`
- L119 _public function_ `void DebugSetUsePlayerPawnLocationInsteadOfCamera(const bool bInValue)`
- L120 _public prototype_ `void DebugUnregisterActorViewer();`
- L125 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L126 _protected prototype_ `virtual void Deinitialize() override;`
- L130 _protected prototype_ `void OnPrePhysicsPhaseStarted(float DeltaTime);` — Called at the start of the PrePhysics mass processing phase and calls SynchronizeViewers
- L133 _protected prototype_ `void SynchronizeViewers();` — Synchronizes the viewers from the engine PlayerController list
- L136 _protected prototype_ `void AddPlayerViewer(APlayerController& PlayerController);` — Adds the given player as a viewer to the list and sends notification about addition
- L139 _protected prototype_ `void AddStreamingSourceViewer(const FName StreamingSourceName);` — Adds the given streaming source as a viewer to the list and sends notification about addition
- L141 _protected prototype_ `void AddActorViewer(AActor& ActorViewer);`
- L145 _protected prototype_ `void AddEditorViewer(const int32 HashValue, const int32 ClientIndex);` — Adds the editor viewport client (identified via an index) as a viewer to the list and sends notification about addition
- L149 _protected prototype_ `void RemoveViewer(const FMassViewerHandle& ViewerHandle);` — Removes a viewer to the list and send notification about removal
- L152 _protected function_ `uint32 GetNextViewerSerialNumber()` — Returns the next new viewer serial number
- L156 _protected prototype_ `void OnPlayerControllerEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()` — Player controller EndPlay callback, removing viewers from the list
- L161 _protected member_ `uint8 bGatherPlayerControllers : 1 = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|LOD", config)` — If true, all PlayerControllers will be gathered as viewers for LOD calculations.
- L165 _protected member_ `uint8 bGatherStreamingSources : 1 = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|LOD", config)` — If true, all streaming sources will be gathered as viewers for LOD calculations.
- L169 _protected member_ `uint8 bAllowNonPlayerViwerActors : 1 = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|LOD", config)` — Whether using non-player actors as LOD Viewers is supported.
- L177 _protected member_ `uint8 bUsePlayerPawnLocationInsteadOfCamera : 1 = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Mass|LOD", config)` — If set to true will prefer to use Player-owned Pawn's location and rotation over Player's camera as the viewer's location and rotation. Note that this works best with distance-only LOD and can introduce subtle inaccuracies if Frustum-based LOD is being used.
- L181 _private prototype_ `void RemoveViewerInternal(const FMassViewerHandle& ViewerHandle);` — Removes a viewer to the list and send notification about removal
- L185 _private member_ `TArray<FViewerInfo> Viewers;` — `UPROPERTY(Transient)` — The actual array of viewer's information
- L189 _private member_ `TMap<uint32, FMassViewerHandle> ViewerMap;` — `UPROPERTY(Transient)` — The map that do reverse look up to get ViewerHandle
- L192 _private member_ `TArray<TObjectPtr<AActor>> RegisteredActorViewers;` — `UPROPERTY(Transient)`
- L194 _private member_ `uint64 LastSynchronizedFrame = 0;`
- L197 _private member_ `uint32 ViewerSerialNumberCounter = 0;` — Viewer serial number counter
- L200 _private member_ `bool bUseEditorLevelViewports = false;`
- L201 _private member_ `bool bIgnorePlayerControllersDueToSimulation = false;`
- L205 _private member_ `TArray<int32> ViewerFreeIndices;` — Free list of indices in the sparse viewer array
- L208 _private member_ `FOnViewerAdded OnViewerAddedDelegate;` — Delegates to notify anyone who needs to know about viewer changes
- L209 _private member_ `FOnViewerRemoved OnViewerRemovedDelegate;`

#### Free symbols / members of external scopes

- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewerAdded, const FViewerInfo& ViewerInfo);`
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewerRemoved, const FViewerInfo& ViewerInfo);`

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODTickRateController.h` (Public)


#### struct `TMassLODTickRateController`  
`template <typename TVariableTickChunkFragment, typename FLODLogic = FLODDefaultLogic > struct TMassLODTickRateController : public FMassLODBaseLogic`  
_L17-67_
- inherits: `FMassLODBaseLogic`
- desc: Helper struct to control LOD tick rate for each agent, It will add a fragment tag to group the agent of the same LOD together, that way the user can do tick rate logic per chunk.
- L20 _public function_ `TMassLODTickRateController() : FMassLODBaseLogic( false)`
- L29 _public prototype_ `void Initialize(const float InTickRate[EMassLOD::Max], const bool bInShouldSpreadFirstUpdate = false);` — Initializes the LOD trick rate controller, needed to be called once at initialization time (Only when FLODLogic::bDoVariableTickRate is enabled) @Param InTickRate the rate at which entities should be ticked per @Param bInShouldSpreadFirstUpdate over the period specified in InTickRate parameter
- L36 _public prototype_ `bool ShouldCalculateLODForChunk(const FMassExecutionContext& Context) const;` — Retrieve if it is needed to calculate the LOD for this chunk @return if the LOD needs to be calculated
- L43 _public prototype_ `bool ShouldAdjustLODFromCountForChunk(const FMassExecutionContext& Context) const;` — Retrieve if it is needed to adjust LOD from the newly calculated count for this chunk @return if the LOD needs to be adjusted
- L53 _public prototype_ `template <typename TLODFragment, typename TVariableTickRateFragment> bool UpdateTickRateFromLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TArrayView<TVariableTickRateFragment> TickRateList, const double Time);` — Updates tick rate for this chunk and its entities @param Context of the chunk execution @param LODList is the fragment where calculation are stored @param Time of the simulation to use for this update @return bool return if the chunk should be tick this frame
- L63 _protected member_ `TStaticArray<float, EMassLOD::Max> TickRates;` — Tick rate for each LOD
- L66 _protected member_ `bool bShouldSpreadFirstUpdate = false;` — Whether or not to spread the first update over the period specified in tick rate member for its LOD
- L70 _function_ `template <typename TVariableTickChunkFragment, typename FLODLogic> void TMassLODTickRateController<TVariableTickChunkFragment, FLODLogic>::Initialize(const float InTickRates[EMassLOD::Max], const bool bInShouldSpreadFirstUpdate )`
- L84 _function_ `template <typename TVariableTickChunkFragment, typename FLODLogic> bool TMassLODTickRateController<TVariableTickChunkFragment, FLODLogic>::ShouldCalculateLODForChunk(const FMassExecutionContext& Context) const`
- L92 _function_ `template <typename TVariableTickChunkFragment, typename FLODLogic> bool TMassLODTickRateController<TVariableTickChunkFragment, FLODLogic>::ShouldAdjustLODFromCountForChunk(const FMassExecutionContext& Context) const`
- L101 _function_ `template <typename TVariableTickChunkFragment, typename FLODLogic> template <typename TLODFragment, typename TVariableTickRateFragment> bool TMassLODTickRateController<TVariableTickChunkFragment, FLODLogic>::UpdateTickRateFromLOD(FMassExecutionContext& Context, TConstArrayView<TLODFragment> LODList, TArrayView<TVariableTickRateFragment> TickRateList, const double Time)`

#### Free symbols / members of external scopes

- L55 _function_ `friend inline uint32 GetTypeHash(const TMassLODTickRateController<TVariableTickChunkFragment, FLODLogic>& SharedFragmentInstance)`

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODTrait.h` (Public)


#### class `UMassLODCollectorTrait`  
`class UMassLODCollectorTrait : public UMassEntityTraitBase`  
_L12-24_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "LODCollector"))`
- inherits: `UMassEntityTraitBase`
- L19 _public member_ `bool bTestCollectorProcessor = true;` — `UPROPERTY(Category="LOD", EditAnywhere, meta=(AdvancedDisplay), config)` — Whether we should verify that the LOD collector processor associated with this trait is enabled by default
- L22 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L23 _protected prototype_ `virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const override;`

#### class `UMassDistanceLODCollectorTrait`  
`class UMassDistanceLODCollectorTrait : public UMassEntityTraitBase`  
_L28-40_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "DistanceLODCollector"))`
- inherits: `UMassEntityTraitBase`
- desc: Simplest version of UMassLODCollectorTrait that will ensure collection strictly based on Distance from Viewer
- L35 _public member_ `bool bTestCollectorProcessor = true;` — `UPROPERTY(Category="LOD", EditAnywhere, meta=(AdvancedDisplay), config)` — Whether we should verify that the LOD collector processor associated with this trait is enabled by default
- L38 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L39 _protected prototype_ `virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const override;`

#### class `UMassSimulationLODTrait`  
`class UMassSimulationLODTrait : public UMassEntityTraitBase`  
_L43-58_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "SimulationLOD"))`
- inherits: `UMassEntityTraitBase`
- L49 _protected member_ `FMassSimulationLODParameters Params;` — `UPROPERTY(Category = "Config", EditAnywhere)`
- L52 _protected member_ `bool bEnableVariableTicking = false;` — `UPROPERTY(Category = "Config", EditAnywhere)`
- L55 _protected member_ `FMassSimulationVariableTickParameters VariableTickParams;` — `UPROPERTY(Category = "Config", EditAnywhere, meta = (EditCondition = "bEnableVariableTicking", EditConditionHides))`
- L57 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSLOD_API`

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODTypes.h` (Public)


#### enum `EMassLOD::Type`  
`enum Type : int`  
_L40-47_
- L42 _public enumerator_ `High`
- L43 _public enumerator_ `Medium`
- L44 _public enumerator_ `Low`
- L45 _public enumerator_ `Off`
- L46 _public enumerator_ `Max`

#### enum `EMassVisibility`  
`enum class EMassVisibility : uint8`  
_L52-58_
- reflection: `UENUM()`
- L54 _public enumerator_ `CanBeSeen` — Not too far and within camera frustum
- L55 _public enumerator_ `CulledByFrustum` — Not in camera frustum but within visibility distance
- L56 _public enumerator_ `CulledByDistance` — Too far whether in or out of frustum
- L57 _public enumerator_ `Max`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_DEBUG_REPLICATION_DUPLICATE_VIEWERS_PER_CONTROLLER 0` — Debug option to allow multiple viewers per controller. Useful for testing and profiling purposes
- L15 _macro_ `#define UE_ALLOW_DEBUG_REPLICATION_DUPLICATE_VIEWERS_PER_CONTROLLER (UE_DEBUG_REPLICATION_DUPLICATE_VIEWERS_PER_CONTROLLER && !UE_BUILD_SHIPPING)`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MassLOD` (scope `UE`)
- L20 _variable_ `constexpr int32 DebugNumberViewersPerController = 50;` (scope `UE::MassLOD`)
- L23 _variable_ `constexpr int32 MaxBucketsPerLOD = 250;` (scope `UE::MassLOD`)
- L25 _externvar_ `extern FColor LODColors[];` (scope `UE::MassLOD`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Mass` (scope `UE`)
- L28 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L31 _externvar_ `extern const FName LODCollector;` (scope `UE::Mass::ProcessorGroupNames`) — Defined in MassLODSubsystem.cpp
- L32 _externvar_ `extern const FName LOD;` (scope `UE::Mass::ProcessorGroupNames`)
- L38 _namespace_ `namespace EMassLOD`

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODUtils.h` (Public)


#### struct `UE::MassLOD::TMassLODTagForLevel`  
`template <EMassLOD::Type Level> struct TMassLODTagForLevel`  
_L41-44_
- L43 _public typedef_ `typedef FMassOffLODTag FTag;`
- L49 _public typedef_ `typedef FMassHighLODTag FTag;`
- L55 _public typedef_ `typedef FMassMediumLODTag FTag;`
- L61 _public typedef_ `typedef FMassLowLODTag FTag;`

#### struct `UE::MassLOD::TMassLODTagForLevel`  
`template<> struct TMassLODTagForLevel<EMassLOD::High>`  
_L47-50_
- L43 _public typedef_ `typedef FMassOffLODTag FTag;`
- L49 _public typedef_ `typedef FMassHighLODTag FTag;`
- L55 _public typedef_ `typedef FMassMediumLODTag FTag;`
- L61 _public typedef_ `typedef FMassLowLODTag FTag;`

#### struct `UE::MassLOD::TMassLODTagForLevel`  
`template<> struct TMassLODTagForLevel<EMassLOD::Medium>`  
_L53-56_
- L43 _public typedef_ `typedef FMassOffLODTag FTag;`
- L49 _public typedef_ `typedef FMassHighLODTag FTag;`
- L55 _public typedef_ `typedef FMassMediumLODTag FTag;`
- L61 _public typedef_ `typedef FMassLowLODTag FTag;`

#### struct `UE::MassLOD::TMassLODTagForLevel`  
`template<> struct TMassLODTagForLevel<EMassLOD::Low>`  
_L59-62_
- L43 _public typedef_ `typedef FMassOffLODTag FTag;`
- L49 _public typedef_ `typedef FMassHighLODTag FTag;`
- L55 _public typedef_ `typedef FMassMediumLODTag FTag;`
- L61 _public typedef_ `typedef FMassLowLODTag FTag;`

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassLOD, Log, All);`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MassLOD` (scope `UE`)
- L19 _function_ `inline EMassLOD::Type GetLODFromArchetype(const FMassExecutionContext& Context)` (scope `UE::MassLOD`)
- L65 _function_ `inline const UScriptStruct* GetLODTagFromLOD(EMassLOD::Type LOD)` (scope `UE::MassLOD`)
- L84 _function_ `inline bool IsLODTagSet(const FMassExecutionContext& Context, EMassLOD::Type LOD)` (scope `UE::MassLOD`)
- L103 _prototype_ `void PushSwapTagsCommand(FMassCommandBuffer& CommandBuffer, const FMassEntityHandle Entity, const EMassLOD::Type PrevLOD, const EMassLOD::Type NewLOD);` (scope `UE::MassLOD`)
- L106 _namespace_ `namespace Debug` (scope `UE::MassLOD`)
- L108 _externvar_ `extern bool bLODCalculationsPaused;` (scope `UE::MassLOD::Debug`)

### `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassSimulationLOD.h` (Public)


#### struct `FMassSimulationLODFragment`  
`struct FMassSimulationLODFragment : public FMassFragment`  
_L17-29_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L22 _public member_ `float ClosestViewerDistanceSq = FLT_MAX;` — Saved closest ViewerDistance
- L25 _public member_ `TEnumAsByte<EMassLOD::Type> LOD = EMassLOD::Max;` — LOD information
- L28 _public member_ `TEnumAsByte<EMassLOD::Type> PrevLOD = EMassLOD::Max;` — Previous LOD information

#### struct `FMassSimulationVariableTickFragment`  
`struct FMassSimulationVariableTickFragment : public FMassFragment`  
_L32-39_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L37 _public member_ `double LastTickedTime = 0.;` — Accumulated delta time to use upon next tick
- L38 _public member_ `float DeltaTime = 0.0f;`

#### struct `FMassSimulationVariableTickChunkFragment`  
`struct FMassSimulationVariableTickChunkFragment : public FMassVariableTickChunkFragment`  
_L42-80_
- reflection: `USTRUCT()`
- inherits: `FMassVariableTickChunkFragment`
- L54 _public function_ `static bool IsChunkHandledThisFrame(const FMassExecutionContext& Context)` — IsChunkHandledThisFrame This function is used by LOD collector query chunk filters to check if the Simulation LOD will be updated this frame. It defaults to false (no LOD update), if simulation variable tick chunk fragment is NOT present. @return true if the simulation LOD will be updated this frame
- L68 _public function_ `static bool ShouldTickChunkThisFrame(const FMassExecutionContext& Context)` — ShouldTickChunkThisFrame This function is used by query chunk filters in processors that require variable rate ticking based on LOD. It defaults to true (always ticking) if simulation variable tick chunk fragment is NOT present. @return if the chunk should be ticked this frame
- L74 _public function_ `static EMassLOD::Type GetChunkLOD(const FMassExecutionContext& Context)`

#### struct `FMassSimulationLODParameters`  
`struct FMassSimulationLODParameters : public FMassConstSharedFragment`  
_L83-104_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L87 _public prototype_ `FMassSimulationLODParameters();`
- L91 _public member_ `float LODDistance[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "LOD", config)` — Distance where each LOD becomes relevant
- L95 _public member_ `float BufferHysteresisOnDistancePercentage = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)` — Hysteresis percentage on delta between the LOD distances
- L99 _public member_ `int32 LODMaxCount[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "LOD", config)` — Maximum limit of entity per LOD
- L103 _public member_ `bool bSetLODTags = false;` — `UPROPERTY(EditAnywhere, Category = "LOD", config)` — If true, will set the associated LOD tag on the entity

#### struct `FMassSimulationVariableTickParameters`  
`struct FMassSimulationVariableTickParameters : public FMassConstSharedFragment`  
_L107-120_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L111 _public prototype_ `FMassSimulationVariableTickParameters();`
- L115 _public member_ `float TickRates[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "VariableTick", config)` — Rate in seconds at which entities should update when in this LOD
- L119 _public member_ `bool bSpreadFirstSimulationUpdate = false;` — `UPROPERTY(EditAnywhere, Category = "VariableTick", config)` — If true, will spread the first simulation update over TickRate period

#### struct `FMassSimulationLODSharedFragment`  
`struct FMassSimulationLODSharedFragment : public FMassSharedFragment`  
_L123-133_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L127 _public prototype_ `FMassSimulationLODSharedFragment() = default;`
- L128 _public prototype_ `FMassSimulationLODSharedFragment(const FMassSimulationLODParameters& LODParams);`
- L131 _public member_ `TMassLODCalculator<FMassSimulationLODLogic> LODCalculator;` — Runtime data for matching the simulation LOD parameters
- L132 _public member_ `bool bHasAdjustedDistancesFromCount = false;`

#### struct `FMassSimulationVariableTickSharedFragment`  
`struct FMassSimulationVariableTickSharedFragment : public FMassSharedFragment`  
_L136-163_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L140 _public prototype_ `FMassSimulationVariableTickSharedFragment() = default;`
- L141 _public prototype_ `FMassSimulationVariableTickSharedFragment(const FMassSimulationVariableTickParameters& TickRateParams);`
- L144 _public member_ `TMassLODTickRateController<FMassSimulationVariableTickChunkFragment, FMassSimulationLODLogic> LODTickRateController;` — Runtime data for matching the simulation tick rate parameters
- L146 _public function_ `static bool ShouldCalculateLODForChunk(const FMassExecutionContext& Context)`
- L155 _public function_ `static bool ShouldAdjustLODFromCountForChunk(const FMassExecutionContext& Context)`

#### class `UMassSimulationLODProcessor`  
`class UMassSimulationLODProcessor : public UMassProcessor`  
_L166-188_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Simulation LOD"))`
- inherits: `UMassProcessor`
- L171 _public prototype_ `UMassSimulationLODProcessor();`
- L175 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L176 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L178 _protected prototype_ `void CalculateLODForConfig(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSimulationLODParameters& LODParams);`
- L180 _protected member_ `FMassEntityQuery EntityQuery;`
- L181 _protected member_ `FMassEntityQuery EntityQueryCalculateLOD;`
- L182 _protected member_ `FMassEntityQuery EntityQueryAdjustDistances;`
- L183 _protected member_ `FMassEntityQuery EntityQueryVariableTick;`
- L184 _protected member_ `FMassEntityQuery EntityQuerySetLODTag;`
- L187 _protected member_ `bool bDoAdjustmentFromCount = true;` — `UPROPERTY(config, EditDefaultsOnly, Category="Mass")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MASSLOD_API`
