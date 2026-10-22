# Plugins / UAFAnimNodeEditor

- module root: `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor`
- headers: 9; symbols: 223
- symbol kinds: class=16, enum=2, enumerator=4, externvar=1, function=34, member=69, namespace=19, prototype=66, struct=10, typedef=2
- PrivateDependencyModuleNames: AssetDefinition, BlueprintGraph, CoreUObject, EditorFramework, EditorWidgets, Engine, GameplayInsights, GraphEditor, InputCore, Kismet, MessageLog, Persona, PropertyEditor, RewindDebuggerInterface, RigVM, RigVMDeveloper, RigVMEditor, Settings, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFAnimNode, UAFAnimNodeUncookedOnly, UAFEditor, UAFUncookedOnly, UnrealEd, WorkspaceEditor
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/RewindDebugger/UAFAnimNodeAnalyzer.h` (Private)


#### class `FUAFAnimNodeAnalyzer`  
`class FUAFAnimNodeAnalyzer : public UE::Trace::IAnalyzer`  
_L10-29_
- inherits: `UE::Trace::IAnalyzer`
- L13 _public prototype_ `FUAFAnimNodeAnalyzer(TraceServices::IAnalysisSession& InSession, FUAFAnimNodeProvider& InProvider);`
- L15 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L16 _public function_ `virtual void OnAnalysisEnd() override`
- L17 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L27 _private member_ `TraceServices::IAnalysisSession& Session;`
- L28 _private member_ `FUAFAnimNodeProvider& Provider;`

#### enum `FUAFAnimNodeAnalyzer::(anonymous)`  
``  
_L21-25_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L22 _enumerator_ `RouteId_AnimOpList` (scope `FUAFAnimNodeAnalyzer::__anonc708998c0103`)
- L23 _enumerator_ `RouteId_AnimNodeUpdate` (scope `FUAFAnimNodeAnalyzer::__anonc708998c0103`)
- L24 _enumerator_ `RouteId_AnimNodeValue` (scope `FUAFAnimNodeAnalyzer::__anonc708998c0103`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/RewindDebugger/UAFAnimNodeProvider.h` (Private)


#### struct `FSmallPageSettings`  
`struct FSmallPageSettings`  
_L20-26_

#### enum `FSmallPageSettings::(anonymous)`  
``  
_L23-25_

#### struct `FAnimOpData`  
`struct FAnimOpData`  
_L28-39_
- L30 _public function_ `FAnimOpData(TraceServices::IAnalysisSession& Session) : GraphInstanceId(0), AnimOpTimeline(Session.GetLinearAllocator())`
- L37 _public member_ `uint64 GraphInstanceId;`
- L38 _public member_ `TraceServices::TPointTimeline<TArray<uint8>, FSmallPageSettings> AnimOpTimeline;`

#### struct `FAnimNodeUpdateData`  
`struct FAnimNodeUpdateData`  
_L41-48_
- L43 _public member_ `double ProfileTime;`
- L44 _public member_ `double RecordingTime;`
- L45 _public member_ `uint64 ParentNodeId;`
- L46 _public member_ `uint64 NodeId;`
- L47 _public member_ `float TotalWeight;`

#### struct `FAnimNodeUpdateTimelineData`  
`struct FAnimNodeUpdateTimelineData`  
_L50-60_
- L52 _public function_ `FAnimNodeUpdateTimelineData(TraceServices::IAnalysisSession& Session) : GraphInstanceId(0), NodeUpdateTimeline(Session.GetLinearAllocator())`
- L58 _public member_ `uint64 GraphInstanceId;`
- L59 _public member_ `TraceServices::TPointTimeline<FAnimNodeUpdateData,FSmallPageSettings> NodeUpdateTimeline;`

#### struct `FAnimNodeValueData`  
`struct FAnimNodeValueData`  
_L62-71_
- L64 _public member_ `double ProfileTime;`
- L65 _public member_ `double RecordingTime;`
- L66 _public member_ `uint64 NodeId;`
- L67 _public member_ `uint32 NameId;`
- L68 _public member_ `uint8 Type;`
- L69 _public member_ `TArray<uint8, TInlineAllocator<8>> Value;`
- L70 _public member_ `const UScriptStruct* StructType = nullptr;`

#### struct `FAnimNodeValueTimelineData`  
`struct FAnimNodeValueTimelineData`  
_L74-84_
- L76 _public function_ `FAnimNodeValueTimelineData(TraceServices::IAnalysisSession& Session) : GraphInstanceId(0), NodeValueTimeline(Session.GetLinearAllocator())`
- L82 _public member_ `uint64 GraphInstanceId;`
- L83 _public member_ `TraceServices::TPointTimeline<FAnimNodeValueData,FSmallPageSettings> NodeValueTimeline;`

#### class `FUAFAnimNodeProvider`  
`class FUAFAnimNodeProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L86-145_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L89 _public member_ `static FName ProviderName;`
- L91 _public prototype_ `FUAFAnimNodeProvider(TraceServices::IAnalysisSession& InSession);`
- L94 _public function_ `virtual void BeginRead() const override`
- L99 _public function_ `virtual void EndRead() const override`
- L104 _public function_ `virtual void ReadAccessCheck() const override`
- L110 _public function_ `virtual void BeginEdit() const override`
- L115 _public function_ `virtual void EndEdit() const override`
- L120 _public function_ `virtual void EditAccessCheck() const override`
- L125 _public prototype_ `const FAnimOpData* GetAnimOpData(uint64 GraphInstanceId) const;`
- L126 _public prototype_ `const FAnimNodeUpdateTimelineData* GetAnimNodeTimelineData(uint64 GraphInstanceId) const;`
- L127 _public prototype_ `const FAnimNodeValueTimelineData* GetAnimNodeValueTimelineData(uint64 GraphInstanceId) const;`
- L129 _public prototype_ `void AppendAnimOpList(double ProfileTime, double RecordingTime, uint64 ObjectInstanceId, uint64 GraphInstanceId, const TArrayView<const uint8>& ListData);`
- L130 _public prototype_ `void AppendAnimNodeUpdate(double ProfileTime, double RecordingTime, uint64 RootGraphId, uint64 NodeId, uint64 ParentNodeId, float TotalWeight);`
- L131 _public prototype_ `void AppendAnimNodeValue(double ProfileTime, double RecordingTime, uint64 RootGraphId, uint64 NodeId, uint8 TypeId, uint64 StructType, uint32 NameId, TConstArrayView<uint8> Value);`
- L133 _public prototype_ `void EnumerateEvaluationGraphs(uint64 OuterObjectId, TFunctionRef<void(uint64 GraphInstanceId)> Callback) const;`
- L136 _private member_ `TraceServices::IAnalysisSession& Session;`
- L137 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L139 _private member_ `TMap<uint64, TSharedRef<FAnimOpData>> AnimOpData;`
- L140 _private member_ `TMap<uint64, TSharedRef<FAnimNodeUpdateTimelineData>> AnimNodeUpdateTimelineData;`
- L141 _private member_ `TMap<uint64, TSharedRef<FAnimNodeValueTimelineData>> AnimNodeValueTimelineData;`
- L144 _private member_ `TMultiMap<uint64, uint64> EvaluationGraphs;` — map from object id to a list of graph instance ids that have evaluation data

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L16 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GUAFAnimNodeProviderLockState;` (scope `TraceServices`)
- L24 _enumerator_ `EventsPerPage = 4096` (scope `FSmallPageSettings::__anon9c183d310103`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/RewindDebugger/UAFAnimNodeTraceModule.h` (Private)


#### class `FUAFAnimNodeTraceModule`  
`class FUAFAnimNodeTraceModule : public TraceServices::IModule`  
_L10-22_
- inherits: `TraceServices::IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L15 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L17 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L18 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L21 _private member_ `static FName ModuleName;`

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/RewindDebugger/UAFAnimNodeTrack.h` (Private)


#### class `UUAFAnimNodeTrackDetailsObject`  
`class UUAFAnimNodeTrackDetailsObject : public UObject`  
_L18-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- L23 _public member_ `FInstancedPropertyBag Properties;` — `UPROPERTY(EditAnywhere, Category = Details, meta=(ShowOnlyInnerProperties))`

#### class `UE::UAF::Editor::FUAFAnimNodeTrack`  
`class FUAFAnimNodeTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L29-57_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L32 _public prototype_ `FUAFAnimNodeTrack(uint64 InObjectId);`
- L33 _public prototype_ `virtual ~FUAFAnimNodeTrack();`
- L35 _public member_ `static constexpr const TCHAR* TrackName = TEXT("Ani`
- L38 _private prototype_ `virtual bool UpdateInternal() override;`
- L39 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L40 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L42 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L43 _private function_ `virtual FName GetNameInternal() const override`
- L44 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L45 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L47 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L48 _private member_ `FSlateIcon Icon;`
- L49 _private member_ `uint64 NodeId;`
- L50 _private member_ `uint64 GraphId = 0;`
- L51 _private member_ `double PreviousScrubTime = -1.0;`
- L52 _private member_ `TStrongObjectPtr<UUAFAnimNodeTrackDetailsObject> DetailsObject;`
- L54 _private prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;`
- L55 _private member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;`
- L56 _private member_ `mutable int CurvesUpdateRequested = 0;`

#### class `UE::UAF::Editor::FUAFAnimNodeTrackCreator`  
`class FUAFAnimNodeTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L59-68_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L62 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L63 _private function_ `virtual FName GetNameInternal() const override`
- L64 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L65 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L66 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L67 _private function_ `virtual bool IsCreatingPrimaryChildTrackInternal() const override`

#### class `UE::UAF::Editor::FUAFTransitionTrackCreator`  
`class FUAFTransitionTrackCreator : public FUAFAnimNodeTrackCreator`  
_L70-74_
- inherits: `FUAFAnimNodeTrackCreator`
- L73 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/RewindDebugger/UAFAnimOpTrack.h` (Private)


#### class `UAnimOpListDetailsObject`  
`class UAnimOpListDetailsObject : public UObject`  
_L15-22_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public member_ `UE::UAF::FUAFInstancedAnimOpList AnimOps;` — `UPROPERTY(EditAnywhere, Category=Details, meta=(ShowOnlyInnerProperties))`

#### class `UE::UAF::Editor::FUAFAnimOpTrack`  
`class FUAFAnimOpTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L27-54_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L30 _public prototype_ `FUAFAnimOpTrack(uint64 InObjectId);`
- L31 _public prototype_ `FUAFAnimOpTrack(uint64 InObjectId, uint64 InstanceId);`
- L32 _public prototype_ `virtual ~FUAFAnimOpTrack();`
- L34 _public function_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetExistenceRange() const`
- L36 _private prototype_ `virtual bool UpdateInternal() override;`
- L37 _private function_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override`
- L39 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L40 _private function_ `virtual FName GetNameInternal() const override`
- L41 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L42 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L44 _private prototype_ `void Initialize();`
- L45 _private prototype_ `UAnimOpListDetailsObject* InitializeDetailsObject();`
- L47 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L48 _private member_ `FSlateIcon Icon;`
- L49 _private member_ `uint64 ObjectId;`
- L50 _private member_ `uint64 InstanceId = 0;`
- L51 _private member_ `double PreviousScrubTime = -1.0;`
- L52 _private member_ `TWeakObjectPtr<UAnimOpListDetailsObject> DetailsObjectWeakPtr;`
- L53 _private member_ `TSharedPtr<SEventTimelineView::FTimelineEventData> ExistenceRange;`

#### class `UE::UAF::Editor::FUAFAnimOpTrackCreator`  
`class FUAFAnimOpTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L57-65_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L60 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L61 _private function_ `virtual FName GetNameInternal() const override`
- L62 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L63 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L64 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/RewindDebugger/UAFSequenceInfoTrack.h` (Private)


#### struct `FUAFSyncMarkerTraceInfo`  
`struct FUAFSyncMarkerTraceInfo`  
_L17-26_
- reflection: `USTRUCT()`
- L22 _public member_ `float Time = 0.0f;` — `UPROPERTY()`
- L25 _public member_ `FName Name;` — `UPROPERTY()`

#### struct `FUAFSequenceTraceInfo`  
`struct FUAFSequenceTraceInfo`  
_L29-49_
- reflection: `USTRUCT()`
- L33 _public function_ `FORCEINLINE float CalcAnimTimeRatio() const`
- L39 _public member_ `TWeakObjectPtr<const UAnimSequence> AnimSequence;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L42 _public member_ `float DurationSeconds = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L45 _public member_ `float CurrentTimeSeconds = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L48 _public member_ `TArray<FUAFSyncMarkerTraceInfo> SyncMarkers;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`

#### class `UUAFSequenceInfoDetailsObject`  
`class UUAFSequenceInfoDetailsObject : public UObject`  
_L52-59_
- reflection: `UCLASS()`
- inherits: `UObject`
- L58 _public member_ `TArray<FUAFSequenceTraceInfo> SequenceTraceInfo;` — `UPROPERTY(EditAnywhere, Category=Details, meta=(ShowOnlyInnerProperties, FullyExpand=true))`

#### class `UE::UAF::Editor::FUAFSequenceTraceInfoCustomization`  
`class FUAFSequenceTraceInfoCustomization : public IPropertyTypeCustomization`  
_L63-72_
- inherits: `IPropertyTypeCustomization`
- L66 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L69 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::UAF::Editor::FUAFSequenceInfoTrack`  
`class FUAFSequenceInfoTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L74-106_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L77 _public prototype_ `FUAFSequenceInfoTrack(uint64 InObjectId);`
- L78 _public prototype_ `FUAFSequenceInfoTrack(uint64 InObjectId, uint64 InstanceId);`
- L79 _public prototype_ `virtual ~FUAFSequenceInfoTrack();`
- L81 _public function_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetExistenceRange() const`
- L83 _public member_ `static constexpr const TCHAR* TrackName = TEXT("Seq`
- L86 _private prototype_ `virtual bool UpdateInternal() override;`
- L87 _private function_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override`
- L89 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L90 _private function_ `virtual FName GetNameInternal() const override`
- L91 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L92 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L94 _private prototype_ `void Initialize();`
- L95 _private prototype_ `UUAFSequenceInfoDetailsObject* InitializeDetailsObject();`
- L97 _private prototype_ `static void RefreshSequenceInfoFromAnimOps(TArray<FUAFSequenceTraceInfo>& OutSequenceInfo, const FUAFInstancedAnimOpList& AnimOps);`
- L99 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L100 _private member_ `FSlateIcon Icon;`
- L101 _private member_ `uint64 ObjectId;`
- L102 _private member_ `uint64 InstanceId = 0;`
- L103 _private member_ `double PreviousScrubTime = -1.0;`
- L104 _private member_ `TWeakObjectPtr<UUAFSequenceInfoDetailsObject> DetailsObjectWeakPtr;`
- L105 _private member_ `TSharedPtr<SEventTimelineView::FTimelineEventData> ExistenceRange;`

#### class `UE::UAF::Editor::FUAFSequenceInfoTrackCreator`  
`class FUAFSequenceInfoTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L109-117_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L112 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L113 _private function_ `virtual FName GetNameInternal() const override`
- L114 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L115 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L116 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L61 _namespace_ `namespace UE`
- L61 _namespace_ `namespace UAF` (scope `UE`)
- L61 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/UAF/AnimNodeCore/UAFAnimNodeDataExDetails.h` (Private)


#### class `UE::UAF::AnimNodeEditor::FUAFAnimNodeDataExDetails`  
`class FUAFAnimNodeDataExDetails : public IPropertyTypeCustomization`  
_L10-28_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _private prototype_ `void GenerateNodeDataWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);`
- L24 _private prototype_ `void OnNodeDataChanged();`
- L26 _private member_ `TSharedPtr<IPropertyHandle> DataListHandle;`
- L27 _private member_ `TSharedPtr<IPropertyUtilities> CachedUtils;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace AnimNodeEditor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Private/UAFAnimNodeEditorModule.h` (Private)


#### class `UE::UAF::AnimNodeEditor::FModule`  
`class FModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- L15 _private prototype_ `virtual void StartupModule() override;`
- L16 _private prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `FTopLevelAssetPath AnimSequenceClassPath;`
- L20 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace AnimNodeEditor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimNode/Source/UAFAnimNodeEditor/Public/UAFAnimNodeDataFactory.h` (Public)


#### struct `UE::UAF::FUAFAnimNodeDataFactory`  
`struct FUAFAnimNodeDataFactory`  
_L23-87_
- desc: The FUAFAnimNodeDataFactory is used to produce FUAFAnimNodeData from UObjects. This is used for UI interactions in editor when users drop objects on to FUAFAnimNodeData slots This factory links UObject class types to FUAFAnimNodeData types. Note: It is not a requirement for a FUAFAnimNodeData be created from a UObject. It could also be created manually
- L28 _public prototype_ `static TInstancedStruct<FUAFAnimNodeData> CreateUAFAnimNodeDataFromObject(UObject* Object);` — Create a UAFAnimNodeData object from the supplied Object
- L31 _public typedef_ `template<typename TAnimNodeDataType, typename TObjectType> using TAnimNodeDataInitializer = TFunction<TAnimNodeDataType(TObjectType*)>;`
- L38 _public function_ `template<typename TAnimNodeDataType, typename TObjectType> [[nodiscard]] static FTopLevelAssetPath RegisterAsset(TAnimNodeDataInitializer<TAnimNodeDataType, TObjectType>&& Initializer)` — Register an UAF asset with the factory This defines a relationship between the TObjectType and the TAnimNodeDataType. The initializer definnes how to create a TAnimNodeDataType from a TObjectType instance @return a FTopLevelAssetPath that can be used to unregister the asset type via UnregisterAsset
- L48 _public prototype_ `static void UnregisterAsset(const FTopLevelAssetPath& InObjectClassPath);` — Unregister an UAF asset with the factory
- L51 _public prototype_ `static bool IsAssetRegistered(const UClass* AssetClass);` — Checks if an asset type is registered with the factory
- L54 _public prototype_ `static TArray<UClass*> GetRegisteredObjectClasses();` — Get all registered UClass types
- L57 _public prototype_ `static TArray<UClass*> GetRegisteredObjectClasses(TSubScriptStructOf<FUAFAnimNodeData> BaseAssetType);` — Get registered UClass types that correspond to a specific baseclass of FUAFAnimNodeData
- L60 _public function_ `template<typename TAnimNodeDataType> static TArray<UClass*> GetRegisteredObjectClasses()`
- L68 _private typedef_ `using FAssetInitializer = TFunction<TInstancedStruct<FUAFAnimNodeData>(UObject*)>;` — Untyped UObject initializer
- L83 _private prototype_ `static FTopLevelAssetPath RegisterAsset(TSubScriptStructOf<FUAFAnimNodeData> AnimNodeDataType, UClass* ObjectClass, FAssetInitializer&& Initializer);` — Register how to create a FUAFAnimNodeData from a ObjectClass
- L84 _private prototype_ `static const FInitializerInfo* FindAssetInitializer(const UClass* Class);`
- L85 _private member_ `static TMap<FTopLevelAssetPath, FInitializerInfo> AssetInitializers;`
- L86 _private member_ `static TArray<FTopLevelAssetPath> AllSupportedObjectClassPaths;`

#### struct `UE::UAF::FUAFAnimNodeDataFactory::FInitializerInfo`  
`struct FInitializerInfo`  
_L70-79_
- L72 _public function_ `FInitializerInfo(TSubScriptStructOf<FUAFAnimNodeData> Type, FAssetInitializer Initializer) : AnimNodeDataType(Type), Initializer(Initializer)`
- L75 _public prototype_ `FInitializerInfo() = default;`
- L77 _public member_ `TSubScriptStructOf<FUAFAnimNodeData> AnimNodeDataType;`
- L78 _public member_ `FAssetInitializer Initializer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L42 _function_ `` (scope `UE::UAF::FUAFAnimNodeDataFactory::RegisterAsset`)
