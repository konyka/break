# Plugins / WorldStreamingInsights

- module root: `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights`
- headers: 11; symbols: 396
- symbol kinds: class=12, delegate=1, enum=5, enumerator=26, function=9, macro=1, member=141, namespace=2, prototype=187, struct=12
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceServices

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/Analyzers/WorldStreamingInsightsAnalyzer.h` (Private)


#### class `FWorldStreamingInsightsAnalyzer`  
`class FWorldStreamingInsightsAnalyzer : public UE::Trace::IAnalyzer`  
_L14-41_
- inherits: `UE::Trace::IAnalyzer`
- L17 _public prototype_ `FWorldStreamingInsightsAnalyzer(TraceServices::IAnalysisSession& InSession, FWorldStreamingInsightsProvider& InProvider);`
- L19 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L20 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L39 _private member_ `TraceServices::IAnalysisSession& Session;`
- L40 _private member_ `FWorldStreamingInsightsProvider& Provider;`

#### enum `FWorldStreamingInsightsAnalyzer::(anonymous)`  
``  
_L24-37_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L25 _enumerator_ `RouteId_WorldInitialization` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L26 _enumerator_ `RouteId_WorldDeinitialization` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L27 _enumerator_ `RouteId_ContainerDescription` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L28 _enumerator_ `RouteId_ContainerStateChange` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L29 _enumerator_ `RouteId_StreamingSourceDescription` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L30 _enumerator_ `RouteId_StreamingSourceUpdate` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L31 _enumerator_ `RouteId_StreamingSourceDeactivation` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L32 _enumerator_ `RouteId_TagGroupDescription` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L33 _enumerator_ `RouteId_TagDescription` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L34 _enumerator_ `RouteId_ContainerPriorityUpdate` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L35 _enumerator_ `RouteId_PackageNameMapping` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)
- L36 _enumerator_ `RouteId_ContainerDependencies` (scope `FWorldStreamingInsightsAnalyzer::__anonf64b20040103`)

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/Model/WorldStreamingInsightsProvider.h` (Private)


#### class `FWorldStreamingInsightsProvider`  
`class FWorldStreamingInsightsProvider : public IWorldStreamingInsightsProvider`  
_L8-86_
- inherits: `IWorldStreamingInsightsProvider`
- L11 _public prototype_ `FWorldStreamingInsightsProvider(TraceServices::IAnalysisSession& InSession);`
- L13 _public prototype_ `void AppendStreamingWorldStart(uint64 InWorldId, const TCHAR* InName, EStreamingWorldNetMode InNetMode, double InTimestamp);`
- L14 _public prototype_ `void AppendStreamingWorldEnd(uint64 InWorldId, double InTimestamp);`
- L15 _public prototype_ `void AppendStreamingContainerDescription(uint64 InContainerId, uint64 InWorldId, uint64 InParentId, const TCHAR* InName, const TCHAR* InPackageName, TOptional<FBox> InBounds, TArrayView<const uint64> InTags);`
- L16 _public prototype_ `void AppendStreamingSourceDescription(uint64 InStreamingSourceId, uint64 InWorldId, const TCHAR* InName);`
- L17 _public prototype_ `void AppendTagGroup(uint64 InGroupId, const TCHAR* InName);`
- L18 _public prototype_ `void AppendTag(uint64 InTagId, uint64 InTagGroupId, uint64 InParentId, const TCHAR* InName);`
- L19 _public prototype_ `void AppendStreamingContainerStateChange(uint64 InWorldId, double InTimestamp, uint64 InContainerId, EStreamingContainerState InNewState);`
- L20 _public prototype_ `void AppendStreamingContainerPriorities(uint64 InWorldId, double InTimestamp, TArrayView<const uint64> InContainerIds, TArrayView<const float> InPriorities);`
- L21 _public prototype_ `void AppendStreamingSourceUpdate(uint64 InWorldId, double InTimestamp, uint64 InSourceId, FVector InLocation);`
- L22 _public prototype_ `void AppendStreamingSourceDeactivation(uint64 InWorldId, double InTimestamp, uint64 InSourceId);`
- L23 _public prototype_ `void AppendPackageNameMapping(uint64 InPackageId, const TCHAR* InName);`
- L24 _public prototype_ `void AppendContainerDependencies(uint64 InContainerId, uint64 InWorldId, TArrayView<const uint64> InDependencyIds);`
- L26 _public prototype_ `virtual uint32 GetChangeSerial() const override;`
- L28 _public prototype_ `virtual uint32 GetStreamingWorldCount() const override;`
- L29 _public prototype_ `virtual void EnumerateStreamingWorlds(TFunctionRef<void(const FStreamingWorldInfo&)> InCallback) const override;`
- L30 _public prototype_ `virtual void EnumerateStreamingWorldsAtTime(double InTime, TFunctionRef<void(const FStreamingWorldInfo&)> InCallback) const override;`
- L31 _public prototype_ `virtual bool ReadStreamingWorld(uint64 InWorldId, TFunctionRef<void(const FStreamingWorldInfo&)> InCallback) const override;`
- L33 _public prototype_ `virtual uint32 GetStreamingContainerCount(uint64 InWorldId) const override;`
- L34 _public prototype_ `virtual void EnumerateStreamingContainers(uint64 InWorldId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const override;`
- L35 _public prototype_ `virtual bool ReadStreamingContainer(uint64 InWorldId, uint64 InContainerId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const override;`
- L36 _public prototype_ `virtual void EnumerateChildStreamingContainers(uint64 InWorldId, uint64 InContainerId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const override;`
- L37 _public prototype_ `virtual void EnumerateRootStreamingContainers(uint64 InWorldId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const override;`
- L39 _public prototype_ `virtual void EnumerateStreamingContainerStateChanges(uint64 InWorldId, uint64 InContainerId, double InStartTime, double InEndTime, TFunctionRef<void(const FStreamingContainerStateChange&)> InCallback) const override;`
- L40 _public prototype_ `virtual EStreamingContainerState GetStreamingContainerStateAtTime(uint64 InWorldId, uint64 InContainerId, double InTime) const override;`
- L42 _public prototype_ `virtual float GetStreamingContainerPriorityAtTime(uint64 InWorldId, uint64 InContainerId, double InTime) const override;`
- L44 _public prototype_ `virtual void EnumerateStreamingSources(uint64 InWorldId, TFunctionRef<void(const FStreamingSourceInfo&)> InCallback) const override;`
- L45 _public prototype_ `virtual void EnumerateStreamingSourcesAtTime(uint64 InWorldId, double InTime, TFunctionRef<void(const FStreamingSourceInfo&)> InCallback) const override;`
- L46 _public prototype_ `virtual bool ReadStreamingSourceAtTime(uint64 InWorldId, uint64 InSourceId, double InTime, TFunctionRef<void(const FStreamingSourceInfo&)> InCallback) const override;`
- L48 _public prototype_ `virtual void EnumerateStreamingSourceUpdates(uint64 InWorldId, uint64 InSourceId, double InStartTime, double InEndTime, TFunctionRef<void(const FStreamingSourceUpdate&)> InCallback) const override;`
- L49 _public prototype_ `virtual FVector GetStreamingSourceLocationAtTime(uint64 InWorldId, uint64 InSourceId, double InTime) const override;`
- L51 _public prototype_ `virtual void EnumerateStreamingTagGroups(TFunctionRef<void(const FStreamingTagGroup&)> InCallback) const override;`
- L52 _public prototype_ `virtual bool ReadStreamingTagGroup(uint64 InGroupId, TFunctionRef<void(const FStreamingTagGroup&)> InCallback) const override;`
- L54 _public prototype_ `virtual void EnumerateStreamingTagsInGroup(uint64 InGroupId, TFunctionRef<void(const FStreamingTag&)> InCallback) const override;`
- L55 _public prototype_ `virtual bool ReadStreamingTag(uint64 InTagId, TFunctionRef<void(const FStreamingTag&)> InCallback) const override;`
- L57 _public prototype_ `virtual const TCHAR* GetPackageName(uint64 InPackageId) const override;`
- L60 _private member_ `TraceServices::IAnalysisSession& Session;`
- L62 _private member_ `uint32 ChangeSerial = 0;`
- L64 _private member_ `TMap<uint64, FStreamingWorldInfo> Worlds;`
- L65 _private member_ `TMap<uint64, TMap<uint64, FStreamingContainerInfo> > ContainersPerWorld;`
- L66 _private member_ `TMap<uint64, TArray<FStreamingSourceInfo> > StreamingSourcesPerWorld;`
- L67 _private member_ `TMap<uint64, FStreamingTagGroup> TagGroups;`
- L68 _private member_ `TMap<uint64, FStreamingTag> Tags;`
- L69 _private member_ `TMap<uint64, TSet<uint64> > TagsPerGroup;`
- L71 _private member_ `TMap<uint64, TArray<FStreamingContainerStateChange> > ContainerStateChangesPerWorld;`
- L72 _private member_ `TMap<uint64, TArray<FStreamingSourceUpdate> > StreamingSourceUpdatesPerWorld;`
- L75 _private member_ `TMap<uint64, TMap<uint64, TArray<FStreamingContainerPriorityUpdate> > > ContainerPrioritiesPerWorld;` — Per world -> per container -> sorted array of priority updates
- L77 _private member_ `TMap<uint64, TMap<uint64, TSet<uint64> > > ContainerToChildContainersPerWorld;`
- L78 _private member_ `TMap<uint64, TSet<uint64> > RootContainersPerWorld;`
- L79 _private member_ `TMap<uint64, TMap<uint64, TArray<int32> > > ContainerToStateChangesPerWorld;`
- L80 _private member_ `TMap<uint64, TMap<uint64, TArray<int32> > > StreamingSourceToUpdatesPerWorld;`
- L82 _private member_ `TMap<uint64, TMap<uint64, int32> > ActiveStreamingSourceLookupPerWorld;`
- L83 _private member_ `TMap<uint64, TMap<uint64, const TCHAR*> > SourceNamesPerWorld;`
- L85 _private member_ `TMap<uint64, const TCHAR*> PackageNames;`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/ViewModels/ContainerMemoryEstimator.h` (Private)


#### struct `FPackageMemoryBreakdown`  
`struct FPackageMemoryBreakdown`  
_L24-27_
- L26 _public member_ `int64 TotalBytes = 0;`

#### struct `FContainerMemoryData`  
`struct FContainerMemoryData`  
_L29-37_
- L31 _public member_ `int64 UniqueMemoryBytes = 0;`
- L32 _public member_ `int64 SharedMemoryBytes = 0;`
- L33 _public member_ `int64 TotalMemoryBytes = 0;`
- L34 _public member_ `int32 UniquePackageCount = 0;`
- L35 _public member_ `int32 SharedPackageCount = 0;`
- L36 _public member_ `int32 TotalPackageCount = 0;`

#### class `IContainerMemorySource`  
`class IContainerMemorySource`  
_L43-60_
- L46 _public prototype_ `virtual ~IContainerMemorySource() = default;`
- L49 _public prototype_ `virtual bool IsSnapshotReady() const = 0;` — Returns true when the snapshot is ready for reading.
- L53 _public prototype_ `virtual bool Tick(double InCurrentTime) = 0;` — Drive the async state machine. Call each tick. Returns true if the snapshot changed this tick.
- L56 _public prototype_ `virtual const TMap<FString, FPackageMemoryBreakdown>& GetCachedSnapshot() const = 0;` — Pre-computed snapshot: package name -> memory breakdown.
- L59 _public prototype_ `virtual double GetLastQueriedTime() const = 0;` — The actual time used for the last completed query.

#### class `FAllocationsMemorySource`  
`class FAllocationsMemorySource : public IContainerMemorySource`  
_L66-111_
- inherits: `IContainerMemorySource`
- L69 _public prototype_ `FAllocationsMemorySource( const TraceServices::IAllocationsProvider& InAllocationsProvider, const TraceServices::IMetadataProvider& InMetadataProvider, const TraceServices::IDefinitionProvider& InDefinitionProvider);`
- L73 _public prototype_ `~FAllocationsMemorySource();`
- L75 _public prototype_ `virtual bool IsSnapshotReady() const override;`
- L76 _public prototype_ `virtual bool Tick(double InCurrentTime) override;`
- L77 _public prototype_ `virtual const TMap<FString, FPackageMemoryBreakdown>& GetCachedSnapshot() const override;`
- L78 _public function_ `virtual double GetLastQueriedTime() const override`
- L88 _private prototype_ `void StartQuery(double InTime);`
- L89 _private prototype_ `void ProcessResults();`
- L90 _private prototype_ `void CancelActiveQuery();`
- L92 _private member_ `const TraceServices::IAllocationsProvider& AllocationsProvider;`
- L93 _private member_ `const TraceServices::IMetadataProvider& MetadataProvider;`
- L94 _private member_ `const TraceServices::IDefinitionProvider& DefinitionProvider;`
- L96 _private member_ `EState State = EState::NoSnapshot;`
- L97 _private member_ `uint64 ActiveQueryHandle = 0;`
- L100 _private member_ `uint16 AssetMetadataType = TraceServices::IMetadataProvider::InvalidMetadataType;` — Resolved metadata type for "Asset" - cached once.
- L101 _private member_ `const TraceServices::FMetadataSchema* AssetSchema = nullptr;`
- L102 _private member_ `bool bMetadataResolved = false;`
- L105 _private member_ `static constexpr double TimeQuantizationMs = 100.0;` — Time quantization: only re-query when quantized bucket changes.
- L106 _private member_ `int64 LastQueriedBucket = INT64_MIN;`
- L107 _private member_ `double LastQueriedTime = 0.0;`
- L109 _private member_ `TMap<FString, FPackageMemoryBreakdown> CachedSnapshot;`
- L110 _private member_ `TMap<FString, FPackageMemoryBreakdown> PendingSnapshot;`

#### enum `FAllocationsMemorySource::EState`  
`enum class EState : uint8`  
_L81-86_
- L83 _public enumerator_ `NoSnapshot`
- L84 _public enumerator_ `SnapshotPending`
- L85 _public enumerator_ `SnapshotReady`

#### class `FContainerMemoryEstimator`  
`class FContainerMemoryEstimator`  
_L117-173_
- L120 _public prototype_ `void Init( const TraceServices::IAnalysisSession& InSession, const IWorldStreamingInsightsProvider& InStreamingProvider);`
- L124 _public prototype_ `void Shutdown();`
- L128 _public prototype_ `void Tick(double InCurrentTime, uint64 InWorldId);` — Drive the estimator. Call each tick with the current scrubber time and world ID. Caller must hold FAnalysisSessionReadScope.
- L131 _public prototype_ `bool IsReady() const;` — Results - valid after Tick() when IsReady() returns true.
- L132 _public prototype_ `const FContainerMemoryData* GetContainerMemoryData(uint64 InContainerId) const;`
- L133 _public function_ `int64 GetMaxContainerMemory() const`
- L134 _public function_ `int64 GetMaxContainerUniqueMemory() const`
- L135 _public function_ `int64 GetMaxContainerSharedMemory() const`
- L137 _public function_ `double GetLastQueriedTime() const`
- L138 _public prototype_ `void EnumerateContainerPackages(uint64 InContainerId, TFunctionRef<void(const FString& PackageName, int32 RefCount)> InCallback) const;`
- L141 _public prototype_ `bool HasMemorySource() const;` — Diagnostic state - for UI messaging when memory data is unavailable.
- L142 _public prototype_ `bool IsMemorySourceReady() const;`
- L143 _public prototype_ `bool HasDependencyData() const;`
- L144 _public prototype_ `bool HasDependencyDataForContainer(uint64 InContainerId) const;`
- L145 _public prototype_ `bool IsContainerIncluded(uint64 InContainerId) const;`
- L148 _private prototype_ `void BuildDependencyGraph();`
- L149 _private prototype_ `bool UpdateIncludedContainers(double InCurrentTime);`
- L150 _private prototype_ `void RecomputeRefCounts();`
- L151 _private prototype_ `void ComputeContainerMemory();`
- L153 _private member_ `const TraceServices::IAnalysisSession* Session = nullptr;`
- L154 _private member_ `const IWorldStreamingInsightsProvider* StreamingProvider = nullptr;`
- L156 _private member_ `TUniquePtr<IContainerMemorySource> MemorySource;`
- L158 _private member_ `uint64 CurrentWorldId = 0;`
- L159 _private member_ `uint32 LastStreamingChangeSerial = 0;`
- L160 _private member_ `bool bDependencyGraphDirty = true;`
- L161 _private member_ `bool bRefCountsDirty = true;`
- L162 _private member_ `int64 LastInclusionBucket = INT64_MIN;`
- L165 _private member_ `TMap<uint64, TSet<FString>> ContainerPackageSets;` — Rebuilt from provider topology when streaming data changes; refcounts re-aggregated when the included-container set changes.
- L166 _private member_ `TSet<uint64> IncludedContainerIds;`
- L167 _private member_ `TMap<FString, int32> PackageRefCounts;`
- L169 _private member_ `TMap<uint64, FContainerMemoryData> ContainerMemoryResults;`
- L170 _private member_ `int64 MaxContainerMemory = 0;`
- L171 _private member_ `int64 MaxContainerUniqueMemory = 0;`
- L172 _private member_ `int64 MaxContainerSharedMemory = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/ViewModels/WorldStreamingSpatialPlotViewExtender.h` (Private)


#### enum `EStreamingVisualizationMode`  
`enum class EStreamingVisualizationMode : uint8`  
_L16-23_
- L18 _public enumerator_ `State`
- L19 _public enumerator_ `Priority`
- L20 _public enumerator_ `MemoryTotal`
- L21 _public enumerator_ `MemoryUnique`
- L22 _public enumerator_ `MemoryShared`

#### enum `EStreamingPalette`  
`enum class EStreamingPalette : uint8`  
_L37-42_
- L39 _public enumerator_ `Viridis`
- L40 _public enumerator_ `Inferno`
- L41 _public enumerator_ `Grayscale`

#### class `FWorldStreamingSpatialPlotViewExtender`  
`class FWorldStreamingSpatialPlotViewExtender : public UE::Insights::SpatialProfiler::ISpatialPlotViewExtender`  
_L44-150_
- inherits: `UE::Insights::SpatialProfiler::ISpatialPlotViewExtender`
- L48 _public prototype_ `virtual void OnBeginSession(const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L49 _public prototype_ `virtual void OnEndSession() override;`
- L51 _public prototype_ `virtual FName GetLayerName() const override;`
- L52 _public prototype_ `virtual FText GetLayerDisplayName() const override;`
- L54 _public prototype_ `virtual void EnumerateRegions(TFunctionRef<void(const UE::Insights::SpatialProfiler::FSpatialPlotRegion&)> InCallback) override;`
- L55 _public prototype_ `virtual void EnumerateMarkers(TFunctionRef<void(const UE::Insights::SpatialProfiler::FSpatialPlotMarker&)> InCallback) override;`
- L57 _public prototype_ `virtual TOptional<UE::Insights::SpatialProfiler::FSpatialPlotLegend> GetLegend() const override;`
- L59 _public prototype_ `virtual bool AppendTooltip(FTooltipDrawState& InOutTooltip, const UE::Insights::SpatialProfiler::FSpatialPlotHitTestResult& InHitTestResult) const override;`
- L60 _public prototype_ `virtual bool ExtendContextMenu(FMenuBuilder& InOutMenuBuilder, const UE::Insights::SpatialProfiler::FSpatialPlotHitTestResult& InHitTestResult) const override;`
- L62 _public prototype_ `virtual void Tick(const UE::Insights::SpatialProfiler::FSpatialPlotViewExtenderTickParams& InTickParams) override;`
- L64 _public prototype_ `virtual uint32 GetChangeSerial() const override;`
- L65 _public prototype_ `virtual bool HasDataForSession(const TraceServices::IAnalysisSession& InAnalysisSession) const override;`
- L66 _public prototype_ `virtual bool HasControlPanel() const override;`
- L67 _public prototype_ `virtual TSharedPtr<SWidget> CreateControlPanel() override;`
- L71 _public prototype_ `void SetContainerVisibility(uint64 InContainerId, bool bInVisible);` — Filtering
- L72 _public prototype_ `void ClearContainerOverride(uint64 InContainerId);`
- L73 _public prototype_ `void ClearAllContainerOverrides();`
- L74 _public prototype_ `void HideAllRootContainers();`
- L75 _public prototype_ `bool IsContainerVisible(uint64 InContainerId) const;`
- L77 _public prototype_ `void SetTagVisibility(uint64 InTagId, bool bInVisible);`
- L78 _public prototype_ `void ClearTagOverride(uint64 InTagId);`
- L79 _public prototype_ `void SetUntaggedVisibility(uint64 InGroupId, bool bInVisible);`
- L80 _public prototype_ `void ClearAllTagOverrides();`
- L81 _public prototype_ `bool IsTagVisible(uint64 InTagId) const;`
- L82 _public prototype_ `bool IsUntaggedVisibleForGroup(uint64 InGroupId) const;`
- L84 _public prototype_ `void PropagateContainerHiddenToAncestors(uint64 InContainerId);`
- L85 _public prototype_ `void SetNewTagDefaultForGroup(uint64 InGroupId, bool bInVisible);`
- L86 _public prototype_ `bool GetNewTagDefaultForGroup(uint64 InGroupId) const;`
- L88 _public prototype_ `uint32 GetProviderChangeSerial() const;`
- L89 _public prototype_ `uint64 GetWorldId() const;`
- L90 _public prototype_ `void EnumerateRootContainers(TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const;`
- L91 _public prototype_ `void EnumerateChildContainers(uint64 InContainerId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const;`
- L92 _public prototype_ `void EnumerateContainers(TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const;`
- L93 _public prototype_ `void EnumerateTagGroups(TFunctionRef<void(const FStreamingTagGroup&)> InCallback) const;`
- L94 _public prototype_ `void EnumerateTagsInGroup(uint64 InGroupId, TFunctionRef<void(const FStreamingTag&)> InCallback) const;`
- L95 _public prototype_ `uint32 GetStreamingContainerCount() const;`
- L97 _public prototype_ `EStreamingVisualizationMode GetVisualizationMode() const;`
- L98 _public prototype_ `void SetVisualizationMode(EStreamingVisualizationMode InMode);`
- L100 _public prototype_ `EStreamingPalette GetPalette() const;`
- L101 _public prototype_ `void SetPalette(EStreamingPalette InPalette);`
- L103 _public prototype_ `bool IsFixedScaleEnabled() const;`
- L104 _public prototype_ `void SetFixedScaleEnabled(bool bInEnabled);`
- L105 _public prototype_ `int32 GetFixedScaleMax() const;`
- L106 _public prototype_ `void SetFixedScaleMax(int32 InMaxMiB);`
- L107 _public prototype_ `int32 GetAutoScaleMax(EStreamingVisualizationMode InMode) const;`
- L110 _public prototype_ `bool HasMemorySource() const;` — Diagnostic passthroughs for estimation status.
- L111 _public prototype_ `bool IsMemorySourceReady() const;`
- L112 _public prototype_ `bool HasDependencyData() const;`
- L113 _public prototype_ `bool HasPriorityData() const;`
- L116 _private prototype_ `uint64 FindWorldAtTime(double InTime) const;`
- L117 _private prototype_ `bool PassesTagFilter(const TArray<uint64>& InContainerTags, const TArray<uint64>& InKnownGroups) const;`
- L119 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L120 _private member_ `const IWorldStreamingInsightsProvider* WorldStreamingInsightsProvider = nullptr;`
- L123 _private member_ `TMap<uint64, bool> ContainerVisibilityOverrides;` — Override maps: present = explicit show/hide, absent = inherit from parent (containers/tags) or per-group default (NewTagDefaultPerGroup).
- L124 _private member_ `TMap<uint64, bool> TagVisibilityOverrides;`
- L125 _private member_ `TMap<uint64, bool> UntaggedVisibilityOverrides;`
- L126 _private member_ `TMap<uint64, bool> NewTagDefaultPerGroup;`
- L127 _private member_ `uint32 FilterChangeSerial = 0;`
- L129 _private member_ `TMap<uint64, bool> ResolvedContainerVisibility;`
- L130 _private member_ `TMap<uint64, bool> ResolvedTagVisibility;`
- L131 _private member_ `uint32 LastResolvedFilterChangeSerial = UINT32_MAX;`
- L132 _private member_ `uint32 LastResolvedProviderChangeSerial = UINT32_MAX;`
- L134 _private prototype_ `void RefreshVisibilityCacheIfNeeded();`
- L135 _private prototype_ `bool ResolveContainerVisibility(uint64 InContainerId) const;`
- L136 _private prototype_ `bool ResolveTagVisibility(uint64 InTagId) const;`
- L138 _private member_ `EStreamingVisualizationMode VisualizationMode = EStreamingVisualizationMode::State;`
- L139 _private member_ `EStreamingPalette Palette = EStreamingPalette::Viridis;`
- L141 _private member_ `uint64 CachedWorldId = UINT64_MAX;`
- L142 _private member_ `uint64 LastValidWorldId = UINT64_MAX;`
- L143 _private member_ `double CachedCurrentTraceTime = 0.0;`
- L145 _private member_ `bool bFixedScale = false;`
- L146 _private member_ `bool bHasPriorityData = false;`
- L147 _private member_ `int32 FixedScaleMaxMiB = 0;`
- L149 _private member_ `FContainerMemoryEstimator MemoryEstimator;`

#### Free symbols / members of external scopes

- L25 _function_ `inline bool IsMemoryVisualizationMode(EStreamingVisualizationMode InMode)`
- L32 _function_ `inline bool UsesColorGradient(EStreamingVisualizationMode InMode)`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/ViewModels/WorldStreamingTimingViewExtender.h` (Private)


#### class `FWorldStreamingTimingViewExtender`  
`class FWorldStreamingTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L9-23_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L12 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L13 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L14 _public prototype_ `virtual void Tick(const UE::Insights::Timing::FTimingViewExtenderTickParams& InParams) override;`
- L16 _public prototype_ `const TraceServices::IAnalysisSession* GetAnalysisSession() const;`
- L19 _private prototype_ `bool IsSessionSupported(UE::Insights::Timing::ITimingViewSession& InSession) const;`
- L21 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L22 _private member_ `TSharedPtr<FWorldStreamingTrack> WorldStreamingTrack;`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/ViewModels/WorldStreamingTrack.h` (Private)


#### class `FWorldStreamingTrack`  
`class FWorldStreamingTrack : public FTimingEventsTrack`  
_L9-19_
- inherits: `FTimingEventsTrack`
- L12 _public prototype_ `explicit FWorldStreamingTrack(FWorldStreamingTimingViewExtender& InExtender);`
- L13 _public prototype_ `virtual ~FWorldStreamingTrack() override = default;`
- L15 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L18 _private member_ `FWorldStreamingTimingViewExtender& Extender;`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/Widgets/SWorldStreamingFilterPanel.h` (Private)


#### struct `FContainerTreeItem`  
`struct FContainerTreeItem`  
_L13-20_
- L15 _public member_ `uint64 ContainerId = 0;`
- L16 _public member_ `FString Name;`
- L17 _public member_ `bool bIsVirtual = false;`
- L18 _public member_ `int32 RealDescendantCount = 0;`
- L19 _public member_ `TArray<TSharedPtr<FContainerTreeItem>> Children;`

#### struct `FTagTreeItem`  
`struct FTagTreeItem`  
_L24-39_
- L33 _public member_ `EKind Kind = EKind::Tag;`
- L34 _public member_ `uint64 Id = 0;`
- L35 _public member_ `uint64 GroupId = 0;`
- L36 _public member_ `FString Name;`
- L37 _public member_ `int32 ContainerCount = 0;`
- L38 _public member_ `TArray<TSharedPtr<FTagTreeItem>> Children;`

#### enum `FTagTreeItem::EKind`  
`enum class EKind : uint8`  
_L26-31_
- L28 _public enumerator_ `Group`
- L29 _public enumerator_ `Untagged`
- L30 _public enumerator_ `Tag`

#### class `SWorldStreamingFilterPanel`  
`class SWorldStreamingFilterPanel : public SCompoundWidget`  
_L43-112_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(SWorldStreamingFilterPanel)`
- L47 _public prototype_ `SLATE_ARGUMENT(FWorldStreamingSpatialPlotViewExtender*, Extender) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L53 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L56 _private prototype_ `void RebuildContainerTree();` — Container tree
- L57 _private prototype_ `TSharedRef<ITableRow> ContainerTree_OnGenerateRow(TSharedPtr<FContainerTreeItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L58 _private prototype_ `void ContainerTree_OnGetChildren(TSharedPtr<FContainerTreeItem> InItem, TArray<TSharedPtr<FContainerTreeItem>>& OutChildren);`
- L59 _private prototype_ `ECheckBoxState ContainerTree_GetCheckState(TSharedPtr<FContainerTreeItem> InItem) const;`
- L60 _private prototype_ `void ContainerTree_OnCheckStateChanged(ECheckBoxState InNewState, TSharedPtr<FContainerTreeItem> InItem);`
- L61 _private prototype_ `void ContainerTree_SetVisibilityRecursive(TSharedPtr<FContainerTreeItem> InItem, bool bInVisible);`
- L62 _private prototype_ `void ContainerTree_ClearOverridesRecursive(TSharedPtr<FContainerTreeItem> InItem);`
- L64 _private prototype_ `FReply OnShowAllContainers();`
- L65 _private prototype_ `FReply OnHideAllContainers();`
- L66 _private prototype_ `FReply OnExpandAllContainers();`
- L67 _private prototype_ `FReply OnCollapseAllContainers();`
- L68 _private prototype_ `void ExpandContainerTreeRecursive(TSharedPtr<FContainerTreeItem> InItem, bool bInExpand);`
- L71 _private prototype_ `void RebuildTagTree();` — Tag tree
- L72 _private prototype_ `TSharedRef<ITableRow> TagTree_OnGenerateRow(TSharedPtr<FTagTreeItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L73 _private prototype_ `void TagTree_OnGetChildren(TSharedPtr<FTagTreeItem> InItem, TArray<TSharedPtr<FTagTreeItem>>& OutChildren);`
- L74 _private prototype_ `ECheckBoxState TagTree_GetCheckState(TSharedPtr<FTagTreeItem> InItem) const;`
- L75 _private prototype_ `void TagTree_OnCheckStateChanged(ECheckBoxState InNewState, TSharedPtr<FTagTreeItem> InItem);`
- L76 _private prototype_ `void TagTree_SetVisibilityRecursive(TSharedPtr<FTagTreeItem> InItem, bool bInVisible);`
- L77 _private prototype_ `void TagTree_ClearOverridesRecursive(TSharedPtr<FTagTreeItem> InItem);`
- L80 _private prototype_ `TSharedRef<SWidget> GenerateVisualizationModeWidget(TSharedPtr<EStreamingVisualizationMode> InMode);` — Visualization mode combo box
- L81 _private prototype_ `void OnVisualizationModeSelected(TSharedPtr<EStreamingVisualizationMode> InMode, ESelectInfo::Type InSelectInfo);`
- L82 _private prototype_ `FText GetVisualizationModeLabel() const;`
- L84 _private member_ `TArray<TSharedPtr<EStreamingVisualizationMode>> VisualizationModeOptions;`
- L86 _private member_ `FWorldStreamingSpatialPlotViewExtender* Extender = nullptr;`
- L87 _private member_ `uint32 CachedProviderChangeSerial = 0;`
- L88 _private member_ `uint32 CachedContainerCount = 0;`
- L89 _private member_ `uint32 CachedTagGroupCount = 0;`
- L90 _private member_ `uint32 CachedTagCount = 0;`
- L92 _private member_ `FString ContainerFilterText;`
- L93 _private member_ `int32 SearchMatchCount = 0;`
- L94 _private member_ `int32 SearchTotalCount = 0;`
- L96 _private member_ `TSet<uint64> PreFilterExpandedIds;`
- L97 _private member_ `bool bHasPreFilterExpansion = false;`
- L99 _private member_ `TArray<TSharedPtr<FContainerTreeItem>> ContainerTreeRoots;`
- L100 _private member_ `TSharedPtr<STreeView<TSharedPtr<FContainerTreeItem>>> ContainerTreeView;`
- L102 _private member_ `bool bTagTreeNeedsDefaultExpansion = true;`
- L103 _private member_ `TArray<TSharedPtr<FTagTreeItem>> TagTreeRoots;`
- L104 _private member_ `TSharedPtr<STreeView<TSharedPtr<FTagTreeItem>>> TagTreeView;`
- L106 _private member_ `uint64 CachedWorldId = UINT64_MAX;`
- L109 _private prototype_ `EVisibility GetMemoryWarningVisibility() const;` — Memory estimation status - evaluated every frame by Slate via method binding.
- L110 _private prototype_ `EVisibility GetMemoryComputingVisibility() const;`
- L111 _private prototype_ `EVisibility GetPriorityWarningVisibility() const;`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/WorldStreamingInsightsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldStreamingInsights, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldStreamingInsights, Log, All);`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/WorldStreamingInsightsModule.h` (Private)


#### class `FWorldStreamingInsightsModule`  
`class FWorldStreamingInsightsModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public prototype_ `static FWorldStreamingInsightsModule& Get();`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `FWorldStreamingInsightsTraceModule TraceModule;`
- L20 _private member_ `FWorldStreamingSpatialPlotViewExtender SpatialPlotViewExtender;`
- L21 _private member_ `FWorldStreamingTimingViewExtender TimingViewExtender;`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Private/WorldStreamingInsightsTraceModule.h` (Private)


#### class `FWorldStreamingInsightsTraceModule`  
`class FWorldStreamingInsightsTraceModule : public TraceServices::IModule`  
_L7-20_
- inherits: `TraceServices::IModule`
- L11 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L12 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& InSession) override;`
- L13 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L14 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L15 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L19 _private member_ `static FName ModuleName;`

### `Plugins/WorldStreamingInsights/Source/WorldStreamingInsights/Public/IWorldStreamingInsightsProvider.h` (Public)


#### struct `FStreamingWorldInfo`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingWorldInfo`  
_L33-40_
- L35 _public member_ `uint64 WorldId = 0;`
- L36 _public member_ `const TCHAR* MapName = nullptr;`
- L37 _public member_ `EStreamingWorldNetMode NetMode = EStreamingWorldNetMode::Standalone;`
- L38 _public member_ `double StartTime = 0.0;`
- L39 _public member_ `double EndTime = 0.0;`

#### struct `FStreamingContainerInfo`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingContainerInfo`  
_L42-51_
- L44 _public member_ `uint64 ContainerId = 0;`
- L45 _public member_ `uint64 ParentId = 0;`
- L46 _public member_ `const TCHAR* Name = nullptr;`
- L47 _public member_ `const TCHAR* PackageName = nullptr;`
- L48 _public member_ `TOptional<FBox> Bounds;`
- L49 _public member_ `TArray<uint64> Tags;`
- L50 _public member_ `TArray<uint64> DependencyPackageIds;`

#### struct `FStreamingSourceInfo`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingSourceInfo`  
_L53-59_
- L55 _public member_ `uint64 SourceId = 0;`
- L56 _public member_ `const TCHAR* Name = nullptr;`
- L57 _public member_ `double StartTime = 0.0;`
- L58 _public member_ `double EndTime = 0.0;`

#### struct `FStreamingTagGroup`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingTagGroup`  
_L61-66_
- L63 _public member_ `uint64 GroupId = 0;`
- L64 _public member_ `const TCHAR* Name = nullptr;`
- L65 _public member_ `const TCHAR* UntaggedLabel = nullptr;`

#### struct `FStreamingTag`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingTag`  
_L68-74_
- L70 _public member_ `uint64 TagId = 0;`
- L71 _public member_ `uint64 GroupId = 0;`
- L72 _public member_ `uint64 ParentId = 0;`
- L73 _public member_ `const TCHAR* Name = nullptr;`

#### struct `FStreamingContainerStateChange`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingContainerStateChange`  
_L76-81_
- L78 _public member_ `double Timestamp = 0.0;`
- L79 _public member_ `uint64 ContainerId = 0;`
- L80 _public member_ `EStreamingContainerState NewState = EStreamingContainerState::Unloaded;`

#### struct `FStreamingContainerPriorityUpdate`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingContainerPriorityUpdate`  
_L83-87_
- L85 _public member_ `double Timestamp = 0.0;`
- L86 _public member_ `float Priority = 0.0f;`

#### struct `FStreamingSourceUpdate`  
`struct UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") FStreamingSourceUpdate`  
_L89-94_
- L91 _public member_ `double Timestamp = 0.0;`
- L92 _public member_ `uint64 SourceId = 0;`
- L93 _public member_ `FVector Location = FVector::ZeroVector;`

#### class `IWorldStreamingInsightsProvider`  
`class UE_EXPERIMENTAL(5.8, "World Streaming Insights API is experimental and subject to change.") IWorldStreamingInsightsProvider : public TraceServices::IProvider`  
_L96-131_
- inherits: `TraceServices::IProvider`
- L99 _public prototype_ `virtual uint32 GetChangeSerial() const =0;`
- L101 _public prototype_ `virtual uint32 GetStreamingWorldCount() const =0;`
- L102 _public prototype_ `virtual void EnumerateStreamingWorlds(TFunctionRef<void(const FStreamingWorldInfo&)> InCallback) const =0;`
- L103 _public prototype_ `virtual void EnumerateStreamingWorldsAtTime(double InTime, TFunctionRef<void(const FStreamingWorldInfo&)> InCallback) const =0;`
- L104 _public prototype_ `virtual bool ReadStreamingWorld(uint64 InWorldId, TFunctionRef<void(const FStreamingWorldInfo&)> InCallback) const =0;`
- L106 _public prototype_ `virtual uint32 GetStreamingContainerCount(uint64 InWorldId) const =0;`
- L107 _public prototype_ `virtual void EnumerateStreamingContainers(uint64 InWorldId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const =0;`
- L108 _public prototype_ `virtual bool ReadStreamingContainer(uint64 InWorldId, uint64 InContainerId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const =0;`
- L109 _public prototype_ `virtual void EnumerateChildStreamingContainers(uint64 InWorldId, uint64 InContainerId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const =0;`
- L110 _public prototype_ `virtual void EnumerateRootStreamingContainers(uint64 InWorldId, TFunctionRef<void(const FStreamingContainerInfo&)> InCallback) const =0;`
- L112 _public prototype_ `virtual void EnumerateStreamingContainerStateChanges(uint64 InWorldId, uint64 InContainerId, double InStartTime, double InEndTime, TFunctionRef<void(const FStreamingContainerStateChange&)> InCallback) const =0;`
- L113 _public prototype_ `virtual EStreamingContainerState GetStreamingContainerStateAtTime(uint64 InWorldId, uint64 InContainerId, double InTime) const =0;`
- L115 _public prototype_ `virtual float GetStreamingContainerPriorityAtTime(uint64 InWorldId, uint64 InContainerId, double InTime) const =0;`
- L117 _public prototype_ `virtual void EnumerateStreamingSources(uint64 InWorldId, TFunctionRef<void(const FStreamingSourceInfo&)> InCallback) const =0;`
- L118 _public prototype_ `virtual void EnumerateStreamingSourcesAtTime(uint64 InWorldId, double InTime, TFunctionRef<void(const FStreamingSourceInfo&)> InCallback) const =0;`
- L119 _public prototype_ `virtual bool ReadStreamingSourceAtTime(uint64 InWorldId, uint64 InSourceId, double InTime, TFunctionRef<void(const FStreamingSourceInfo&)> InCallback) const =0;`
- L121 _public prototype_ `virtual void EnumerateStreamingSourceUpdates(uint64 InWorldId, uint64 InSourceId, double InStartTime, double InEndTime, TFunctionRef<void(const FStreamingSourceUpdate&)> InCallback) const =0;`
- L122 _public prototype_ `virtual FVector GetStreamingSourceLocationAtTime(uint64 InWorldId, uint64 InSourceId, double InTime) const =0;`
- L124 _public prototype_ `virtual void EnumerateStreamingTagGroups(TFunctionRef<void(const FStreamingTagGroup&)> InCallback) const =0;`
- L125 _public prototype_ `virtual bool ReadStreamingTagGroup(uint64 InGroupId, TFunctionRef<void(const FStreamingTagGroup&)> InCallback) const =0;`
- L127 _public prototype_ `virtual void EnumerateStreamingTagsInGroup(uint64 InGroupId, TFunctionRef<void(const FStreamingTag&)> InCallback) const =0;`
- L128 _public prototype_ `virtual bool ReadStreamingTag(uint64 InTagId, TFunctionRef<void(const FStreamingTag&)> InCallback) const =0;`
- L130 _public prototype_ `virtual const TCHAR* GetPackageName(uint64 InPackageId) const =0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WORLDSTREAMINGINSIGHTS_API`
