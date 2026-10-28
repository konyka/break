# Plugins / GameplayInsights

- module root: `Plugins/Animation/GameplayInsights/Source/GameplayInsights`
- headers: 54; symbols: 1838
- symbol kinds: class=77, delegate=6, enum=17, enumerator=127, externvar=3, function=205, macro=2, member=601, namespace=72, prototype=650, struct=56, typedef=20, union=1, variable=1
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintEditor, ApplicationCore, AssetRegistry, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, GameplayInsightsEditor, InputCore, Kismet, Persona, RewindDebuggerInterface, Slate, SlateCore, SubobjectEditor, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices, UnrealEd
- PublicIncludePathModuleNames: TraceServices

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimCurvesTrack.h` (Private)


#### class `RewindDebugger::FAnimCurveTrack`  
`class FAnimCurveTrack : public FRewindDebuggerTrack`  
_L17-44_
- inherits: `FRewindDebuggerTrack`
- desc: Sub Track for a single curve
- L20 _public prototype_ `FAnimCurveTrack(uint64 InObjectId, uint32 InCurveId);`
- L22 _public function_ `uint32 GetCurveId()`
- L25 _private prototype_ `virtual bool UpdateInternal() override;`
- L26 _private prototype_ `TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L27 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L28 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L29 _private function_ `virtual FName GetNameInternal() const override`
- L30 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L31 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L32 _private prototype_ `virtual void UpdateCurvePointsInternal();`
- L34 _private prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;`
- L36 _protected member_ `uint32 CurveId;`
- L38 _protected member_ `FSlateIcon Icon;`
- L39 _protected member_ `FText CurveName;`
- L40 _protected member_ `uint64 ObjectId;`
- L42 _protected member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;`
- L43 _protected member_ `mutable int CurvesUpdateRequested = 0;`

#### class `RewindDebugger::FAnimCurvesTrack`  
`class FAnimCurvesTrack : public FRewindDebuggerTrack`  
_L47-68_
- inherits: `FRewindDebuggerTrack`
- desc: Parent track of all the curves
- L50 _public prototype_ `FAnimCurvesTrack(uint64 InObjectId);`
- L54 _private prototype_ `virtual bool UpdateInternal() override;`
- L55 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L57 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L58 _private function_ `virtual FName GetNameInternal() const override`
- L59 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L60 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L61 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L63 _private member_ `FSlateIcon Icon;`
- L64 _private member_ `uint64 ObjectId;`
- L66 _private member_ `TSharedPtr<FRewindDebuggerPlaceholderTrack> ChildPlaceholder;`
- L67 _private member_ `TArray<TSharedPtr<FAnimCurveTrack>> Children;`

#### class `RewindDebugger::FAnimationCurvesTrackCreator`  
`class FAnimationCurvesTrackCreator : public IRewindDebuggerTrackCreator`  
_L71-79_
- inherits: `IRewindDebuggerTrackCreator`
- L74 _private prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L75 _private prototype_ `virtual FName GetNameInternal() const override;`
- L76 _private prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L77 _private prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L78 _private prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimNodesTrack.h` (Private)


#### class `FAnimNodesTrack`  
`class FAnimNodesTrack : public FGameplayTimingEventsTrack #if WITH_ENGINE , public FGCObject #endif`  
_L21-82_
- inherits: `FGameplayTimingEventsTrack,FGCObject`
- L29 _public prototype_ `FAnimNodesTrack(const FAnimationSharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L30 _public prototype_ `~FAnimNodesTrack();`
- L32 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L33 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L34 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L35 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L36 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L40 _public prototype_ `void UpdateDebugData(const TraceServices::FFrame& InFrame);` — Update the debug data for any classes that are running on this track
- L43 _public prototype_ `void GetCustomDebugObjects(const IAnimationBlueprintEditor& InAnimationBlueprintEditor, TArray<FCustomDebugObject>& OutDebugList);` — Get custom debug objects for integration with anim blueprint debugging
- L48 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L49 _public function_ `virtual FString GetReferencerName() const override`
- L52 _public prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);` — Handle worlds being torn down
- L53 _public prototype_ `void RemoveWorld(UWorld* InWorld);`
- L58 _private prototype_ `void FindAnimGraphMessage(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FAnimGraphMessage&)> InFoundPredicate) const;` — Helper function used to find an anim graph message
- L61 _private prototype_ `UAnimInstance* LazyCreateAnimInstance(USkeletalMeshComponent* InComponent);`
- L66 _private member_ `const FAnimationSharedData& SharedData;` — The shared data
- L70 _private member_ `TSoftObjectPtr<UAnimBlueprintGeneratedClass> InstanceClass;` — Instance class, if any, used for instantiating debug info
- L73 _private member_ `TObjectPtr<UAnimInstance> AnimInstance;` — Data used for anim BP debugging
- L78 _private member_ `FDelegateHandle OnWorldCleanupHandle;` — Handles used to deal with world switching
- L79 _private member_ `FDelegateHandle OnWorldBeginTearDownHandle;`
- L80 _private member_ `FDelegateHandle OnPreWorldFinishDestroyHandle;`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimNotifiesTrack.h` (Private)


#### class `FAnimNotifiesTrack`  
`class FAnimNotifiesTrack : public FGameplayTimingEventsTrack`  
_L12-38_
- inherits: `FGameplayTimingEventsTrack`
- L17 _public prototype_ `FAnimNotifiesTrack(const FAnimationSharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L19 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L20 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L21 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L22 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L23 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L27 _private prototype_ `void FindAnimNotifyMessage(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FAnimNotifyMessage&)> InFoundPredicate) const;` — Helper function used to find an anim notify message
- L31 _private member_ `const FAnimationSharedData& SharedData;` — The shared data
- L34 _private member_ `TMap<uint64, uint32> IdToDepthMap;` — Map of notify ID->depth of notify states that are currently drawn
- L37 _private member_ `bool bHasNotifies;` — Whether we are currently drawing any notifies

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimationAnalyzer.h` (Private)


#### class `FAnimationAnalyzer`  
`class FAnimationAnalyzer : public UE::Trace::IAnalyzer`  
_L11-64_
- inherits: `UE::Trace::IAnalyzer`
- L14 _public prototype_ `FAnimationAnalyzer(TraceServices::IAnalysisSession& InSession, FAnimationProvider& InAnimationProvider);`
- L16 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L17 _public function_ `virtual void OnAnalysisEnd() override`
- L18 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L62 _private member_ `TraceServices::IAnalysisSession& Session;`
- L63 _private member_ `FAnimationProvider& AnimationProvider;`

#### enum `FAnimationAnalyzer::(anonymous)`  
``  
_L22-60_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L23 _enumerator_ `RouteId_TickRecord` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L24 _enumerator_ `RouteId_TickRecord2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L25 _enumerator_ `RouteId_TickRecord3` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L26 _enumerator_ `RouteId_SkeletalMesh` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L27 _enumerator_ `RouteId_SkeletalMesh2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L28 _enumerator_ `RouteId_SkeletalMesh3` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L29 _enumerator_ `RouteId_SkeletalMeshComponent` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L30 _enumerator_ `RouteId_SkeletalMeshComponent2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L31 _enumerator_ `RouteId_SkeletalMeshComponent3` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L32 _enumerator_ `RouteId_SkeletalMeshComponent4` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L33 _enumerator_ `RouteId_SkeletalMeshFrame` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L34 _enumerator_ `RouteId_AnimGraph` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L35 _enumerator_ `RouteId_AnimNodeStart` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L36 _enumerator_ `RouteId_AnimNodeAttribute` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L37 _enumerator_ `RouteId_AnimNodeValueBool` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L38 _enumerator_ `RouteId_AnimNodeValueInt` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L39 _enumerator_ `RouteId_AnimNodeValueFloat` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L40 _enumerator_ `RouteId_AnimNodeValueVector2D` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L41 _enumerator_ `RouteId_AnimNodeValueVector` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L42 _enumerator_ `RouteId_AnimNodeValueString` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L43 _enumerator_ `RouteId_AnimNodeValueObject` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L44 _enumerator_ `RouteId_AnimNodeValueClass` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L45 _enumerator_ `RouteId_AnimNodeValueAnimNode` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L46 _enumerator_ `RouteId_AnimSequencePlayer` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L47 _enumerator_ `RouteId_BlendSpacePlayer` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L48 _enumerator_ `RouteId_StateMachineState` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L49 _enumerator_ `RouteId_Name` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L50 _enumerator_ `RouteId_Notify` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L51 _enumerator_ `RouteId_Notify2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L52 _enumerator_ `RouteId_SyncMarker` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L53 _enumerator_ `RouteId_SyncMarker2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L54 _enumerator_ `RouteId_Montage` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L55 _enumerator_ `RouteId_Montage2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L56 _enumerator_ `RouteId_Sync` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L57 _enumerator_ `RouteId_PoseWatch` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L58 _enumerator_ `RouteId_PoseWatch2` (scope `FAnimationAnalyzer::__anon4627274c0103`)
- L59 _enumerator_ `RouteId_Inertialization` (scope `FAnimationAnalyzer::__anon4627274c0103`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimationProvider.h` (Private)


#### class `FAnimationProvider`  
`class FAnimationProvider : public IAnimationProvider, public TraceServices::IEditableProvider`  
_L23-270_
- inherits: `IAnimationProvider,TraceServices::IEditableProvider`
- L26 _public member_ `static FName ProviderName;`
- L28 _public prototype_ `FAnimationProvider(TraceServices::IAnalysisSession& InSession, FGameplayProvider& InGameplayProvider);`
- L31 _public function_ `virtual void BeginRead() const override`
- L36 _public function_ `virtual void EndRead() const override`
- L41 _public function_ `virtual void ReadAccessCheck() const override`
- L47 _public function_ `virtual void BeginEdit() const override`
- L52 _public function_ `virtual void EndEdit() const override`
- L57 _public function_ `virtual void EditAccessCheck() const override`
- L63 _public prototype_ `virtual void EnumerateSkeletalMeshPoseTimelines(TFunctionRef<void(uint64 ObjectId, const SkeletalMeshPoseTimeline&)> Callback) const override;` — IAnimationProvider interface
- L64 _public prototype_ `virtual bool ReadSkeletalMeshPoseTimeline(uint64 InObjectId, TFunctionRef<void(const SkeletalMeshPoseTimeline&, bool)> Callback) const override;`
- L65 _public prototype_ `virtual void GetSkeletalMeshComponentSpacePose(const FSkeletalMeshPoseMessage& InMessage, const FSkeletalMeshInfo& InMeshInfo, FTransform& OutComponentToWorld, TArray<FTransform>& OutTransforms) const override;`
- L66 _public prototype_ `virtual void GetPoseWatchData(const FPoseWatchMessage& InMessage, TArray<FTransform>& BoneTransforms, TArray<uint16>& RequiredBones) const;`
- L67 _public prototype_ `virtual void EnumerateSkeletalMeshCurveIds(uint64 InObjectId, TFunctionRef<void(uint32)> Callback) const override;`
- L68 _public prototype_ `virtual void EnumerateSkeletalMeshCurves(const FSkeletalMeshPoseMessage& InMessage, TFunctionRef<void(const FSkeletalMeshNamedCurve&)> Callback) const override;`
- L69 _public prototype_ `virtual void EnumeratePoseWatchCurves(const FPoseWatchMessage& InMessage, TFunctionRef<void(const FSkeletalMeshNamedCurve&)> Callback) const override;`
- L70 _public prototype_ `virtual void EnumerateExternalMorphSets(const FSkeletalMeshPoseMessage& InMessage, TFunctionRef<void(const FExternalMorphWeightMessage&)> Callback) const override;`
- L71 _public prototype_ `virtual bool ReadTickRecordTimeline(uint64 InObjectId, TFunctionRef<void(const TickRecordTimeline&)> Callback) const override;`
- L72 _public prototype_ `virtual bool ReadInertializationTimeline(uint64 InObjectId, TFunctionRef<void(const InertializationTimeline&)> Callback) const override;`
- L73 _public prototype_ `virtual void EnumerateInertializationNodes(uint64 InObjectId, TFunctionRef<void(int32 NodeId, EInertializationType Type)> Callback) const override;`
- L74 _public prototype_ `virtual void EnumerateTickRecordIds(uint64 InObjectId, TFunctionRef<void(uint64, int32)> Callback) const override;`
- L75 _public prototype_ `virtual void EnumerateAnimGraphTimelines(TFunctionRef<void(uint64 ObjectId, const AnimGraphTimeline&)> Callback) const override;`
- L76 _public prototype_ `virtual bool ReadAnimGraphTimeline(uint64 InObjectId, TFunctionRef<void(const AnimGraphTimeline&)> Callback) const override;`
- L77 _public prototype_ `virtual bool ReadAnimNodesTimeline(uint64 InObjectId, TFunctionRef<void(const AnimNodesTimeline&)> Callback) const override;`
- L78 _public prototype_ `virtual bool ReadAnimNodeValuesTimeline(uint64 InObjectId, TFunctionRef<void(const AnimNodeValuesTimeline&)> Callback) const override;`
- L79 _public prototype_ `virtual bool ReadAnimAttributesTimeline(uint64 InObjectId, TFunctionRef<void(const AnimAttributeTimeline&)> Callback) const override;`
- L80 _public prototype_ `virtual bool ReadAnimSequencePlayersTimeline(uint64 InObjectId, TFunctionRef<void(const AnimSequencePlayersTimeline&)> Callback) const override;`
- L81 _public prototype_ `virtual bool ReadAnimBlendSpacePlayersTimeline(uint64 InObjectId, TFunctionRef<void(const BlendSpacePlayersTimeline&)> Callback) const override;`
- L82 _public prototype_ `virtual bool ReadStateMachinesTimeline(uint64 InObjectId, TFunctionRef<void(const StateMachinesTimeline&)> Callback) const override;`
- L83 _public prototype_ `virtual bool ReadNotifyTimeline(uint64 InObjectId, TFunctionRef<void(const AnimNotifyTimeline&)> Callback) const override;`
- L84 _public prototype_ `virtual void EnumerateNotifyStateTimelines(uint64 InObjectId, TFunctionRef<void(uint64, const AnimNotifyTimeline&)> Callback) const override;`
- L85 _public prototype_ `virtual bool ReadMontageTimeline(uint64 InObjectId, TFunctionRef<void(const AnimMontageTimeline&)> Callback) const override;`
- L86 _public prototype_ `virtual void EnumerateMontageIds(uint64 InObjectId, TFunctionRef<void(uint64)> Callback) const override;`
- L87 _public prototype_ `virtual bool ReadAnimSyncTimeline(uint64 InObjectId, TFunctionRef<void(const AnimSyncTimeline&)> Callback) const override;`
- L88 _public prototype_ `virtual bool ReadPoseWatchTimeline(uint64 InObjectId, TFunctionRef<void(const PoseWatchTimeline&)> Callback) const override;`
- L89 _public prototype_ `virtual const FSkeletalMeshInfo* FindSkeletalMeshInfo(uint64 InObjectId) const override;`
- L90 _public prototype_ `virtual const FAnimNodeInfo* FindAnimNodeInfo(int32 InNodeId, uint64 InAnimInstanceId) const override;`
- L91 _public prototype_ `virtual const TCHAR* GetName(uint32 InId) const override;`
- L92 _public prototype_ `virtual FText FormatNodeKeyValue(const FAnimNodeValueMessage& InMessage) const override;`
- L93 _public prototype_ `virtual FText FormatNodeValue(const FAnimNodeValueMessage& InMessage) const override;`
- L96 _public prototype_ `bool HasExternalMorphSets(uint64 InObjectId) const;` — Does the given object have external morph sets?
- L99 _public prototype_ `bool HasAnyData() const;` — Check to see if any data is present for this provider. Used as an early-out when processing.
- L102 _public prototype_ `void AppendTickRecord(uint64 InAnimInstanceId, double InProfileTime, double InRecordingTime, uint64 InAssetId, int32 InNodeId, float InBlendWeight, float InPlaybackTime, float InRootMotionWeight, float InPlayRate, float InBlendSpacePositionX, float InBlendSpacePositionY, float InBlendSpaceFilteredPositionX, float InBlendSpaceFilteredPositionY, uint16 InFrameCounter, bool bInLooping, bool bInIsBlendSpace);` — Add a tick record
- L106 _public prototype_ `void AppendSkeletalMesh(uint64 InObjectId, uint64 SkeletonId, const TArrayView<const int32>& ParentIndices);` — Add a skeletal mesh
- L109 _public prototype_ `void AppendSkeletalMeshComponent(uint64 InObjectId, uint64 InMeshId, double InProfileTime, double InRecordingTime, uint16 InLodIndex, uint16 InFrameCounter, const TArrayView<const FTransform>& InPose, const TArrayView<const FSkeletalMeshNamedCurve>& InCurves);` — Add a skeletal mesh pose/curves etc.
- L110 _public prototype_ `void AppendSkeletalMeshComponent(uint64 InObjectId, uint64 InMeshId, double InProfileTime, double InRecordingTime, uint16 InLodIndex, uint16 InFrameCounter, const TArrayView<const float>& InComponentToWorldRaw, const TArrayView<const float>& InPoseRaw, const TArrayView<const uint32>& InCurveIds, const TArrayView<const float>& InCurveValues);`
- L111 _public prototype_ `void AppendSkeletalMeshComponent(uint64 InObjectId, uint64 InMeshId, double InProfileTime, double InRecordingTime, uint16 InLodIndex, uint16 InFrameCounter, bool bInIsVisible, const TArrayView<const float>& InComponentToWorldRaw, const TArrayView<const float>& InPoseRaw, const TArrayView<const uint32>& InCurveIds, const TArrayView<const float>& InCurveValues, const TArrayView<const float>& InExternalMorphWeights, const TArrayView<const int32>& InExternalMorphCounts);`
- L114 _public prototype_ `USkeletalMesh* GetSkeletalMesh(const TCHAR* InPath);` — Get a skeletal mesh for a specified path. If the mesh no longer exists, make a fake one
- L117 _public prototype_ `void AppendName(uint32 InId, const TCHAR* InName);` — Add a name, referenced by ID (for curves etc.)
- L120 _public prototype_ `void AppendSkeletalMeshFrame(uint64 InObjectId, double InTime, uint16 InFrameCounter);` — Add a skeletal mesh frame
- L123 _public prototype_ `void AppendAnimGraph(uint64 InAnimInstanceId, double InStartTime, double InEndTime, int32 InNodeCount, uint16 InFrameCounter, uint8 InPhase);` — Add an anim graph
- L126 _public prototype_ `void AppendAnimNodeStart(uint64 InAnimInstanceId, double InStartTime, uint16 InFrameCounter, int32 InTargetLinkId, int32 InSourceLinkId, const TCHAR* InTargetNodeName, float InWeight, float InRootMotionWeight, const TCHAR* InTargetNodeDisplayName, uint8 InPhase);` — Add an anim node
- L129 _public prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, bool bInValue);` — Add anim node values
- L130 _public prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, int32 InValue);`
- L131 _public prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, float InValue);`
- L132 _public prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, const FVector2D& InValue);`
- L133 _public prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, const FVector& InValue);`
- L134 _public prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, const TCHAR* InValue);`
- L135 _public prototype_ `void AppendAnimNodeValueObject(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, uint64 InValue);`
- L136 _public prototype_ `void AppendAnimNodeValueClass(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, uint64 InValue);`
- L137 _public prototype_ `void AppendAnimNodeValueAnimNode(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, int32 InValue, uint64 InValueAnimInstanceId);`
- L140 _public prototype_ `void AppendAnimGraphAttribute(uint64 InSourceAnimInstanceId, uint64 InTargetAnimInstanceId, double InTime, int32 InSourceNodeId, int32 InTargetNodeId, uint32 InAttributeNameId);` — Add anim graph attribute
- L143 _public prototype_ `void AppendAnimSequencePlayer(uint64 InAnimInstanceId, double InTime, int32 InNodeId, float InPosition, float InLength, uint16 InFrameCounter);` — Add a sequence player record
- L146 _public prototype_ `void AppendBlendSpacePlayer(uint64 InAnimInstanceId, double InTime, int32 InNodeId, uint64 InBlendSpaceId, const FVector& InBlendPosition, const FVector& InFilteredBlendPosition);` — Add a blend space player record
- L149 _public prototype_ `void AppendStateMachineState(uint64 InAnimInstanceId, double InTime, int32 InNodeId, int32 InStateMachineIndex, int32 InStateIndex, float InStateWeight, float InElapsedTime);` — Add a state machine state
- L152 _public prototype_ `void AppendNotify(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint64 InAssetId, uint64 InNotifyId, uint32 InNameId, float InNotifyTime, float InNotifyDuration, EAnimNotifyMessageType InNotifyEventType);` — Add an anim notify
- L155 _public prototype_ `void AppendMontage(uint64 InAnimInstanceId, double InProfileTime, double InRecordingTime, uint64 InMontageId, uint32 InCurrentSectionNameId, uint32 InNextSectionNameId, float InWeight, float InDesiredWeight, float InPosition, uint16 InFrameCounter);` — Append montage data
- L158 _public prototype_ `void AppendSync(uint64 InAnimInstanceId, double InTime, int32 InSourceNodeId, uint32 InGroupNameId);` — Append sync data
- L161 _public prototype_ `void AppendPoseWatch(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint64 PoseWatchId, const TArrayView<const float>& BoneTransformsRaw, const TArrayView<const uint16>& RequiredBones, const TArrayView<const float>& WorldTransformRaw, const bool bIsEnabled);` — Append pose watch data
- L162 _public prototype_ `void AppendPoseWatch(uint64 InComponentId, uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint64 PoseWatchId, uint32 NameId, FColor Color, const TArrayView<const float>& BoneTransformsRaw, const TArrayView<const uint32>& CurveIds, const TArrayView<const float>& CurveValues, const TArrayView<const uint16>& RequiredBones, const TArrayView<const float>& WorldTransformRaw, const bool bIsEnabled);`
- L165 _public prototype_ `void AppendInertialization(uint64 InAnimInstanceId, double InProfileTime, double InRecordingTime, int32 NodeId, float InWeight, EInertializationType InType);` — Append Inertialization data
- L169 _private prototype_ `void AppendAnimNodeValue(uint64 InAnimInstanceId, double InTime, double InRecordingTime, uint16 InFrameCounter, int32 InNodeId, const TCHAR* InKey, FAnimNodeValueMessage& InMessage);` — Add anim node values helper
- L172 _private prototype_ `void HandleObjectEndPlay(uint64 InObjectId, double InTime, const FObjectInfo& InObjectInfo);` — Handle an object ending play - terminate existing scopes
- L174 _private prototype_ `void UpdateSessionDurationSeconds(double InTime) const;`
- L177 _private member_ `TraceServices::IAnalysisSession& Session;`
- L178 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L179 _private member_ `FGameplayProvider& GameplayProvider;`
- L182 _private member_ `TMap<uint64, uint32> ObjectIdToTickRecordTimelineStorage;` — Maps into timeline arrays per-object
- L183 _private member_ `TMap<uint64, uint32> ObjectIdToSkeletalMeshPoseTimelines;`
- L184 _private member_ `TMap<uint64, uint32> ObjectIdToSkeletalMeshFrameTimelines;`
- L185 _private member_ `TMap<uint64, uint32> ObjectIdToAnimGraphTimelines;`
- L186 _private member_ `TMap<uint64, uint32> ObjectIdToAnimNodeTimelines;`
- L187 _private member_ `TMap<uint64, uint32> ObjectIdToStateMachineTimelines;`
- L188 _private member_ `TMap<uint64, uint32> ObjectIdToAnimNodeValueTimelines;`
- L189 _private member_ `TMap<uint64, uint32> ObjectIdToAnimSequencePlayerTimelines;`
- L190 _private member_ `TMap<uint64, uint32> ObjectIdToBlendSpacePlayerTimelines;`
- L191 _private member_ `TMap<uint64, uint32> ObjectIdToAnimNotifyStateTimelines;`
- L192 _private member_ `TMap<uint64, uint32> ObjectIdToAnimNotifyTimelines;`
- L193 _private member_ `TMap<uint64, uint32> ObjectIdToAnimMontageTimelines;`
- L194 _private member_ `TMap<uint64, uint32> ObjectIdToInertializationTimelines;`
- L195 _private member_ `TMap<uint64, uint32> ObjectIdToAnimAttributeTimelines;`
- L196 _private member_ `TMap<uint64, uint32> ObjectIdToAnimSyncTimelines;`
- L197 _private member_ `TMap<uint64, uint32> ObjectIdToPoseWatchTimelines;`
- L200 _private member_ `TArray<FSkeletalMeshInfo> SkeletalMeshInfos;` — All the skeletal mesh info we have seen, grow only for stable indices
- L203 _private member_ `TMap<uint64, uint32> SkeletalMeshIdToIndexMap;` — Map of skeletal mesh->index into SkeletalMeshInfos index
- L206 _private member_ `TArray<FAnimNodeInfo> AnimNodeInfos;` — All the anim node info we have seen, grow only for stable indices
- L209 _private member_ `TMap<TTuple<int32, uint64>, uint32> AnimNodeIdToIndexMap;` — Map of (node, anim instance)->index into AnimNodeInfos index
- L212 _private member_ `TMap<uint32, const TCHAR*> NameMap;` — Map of name IDs to name string
- L246 _private member_ `TArray<TSharedRef<FTickRecordTimelineStorage>> TickRecordTimelineStorage;` — Message storage
- L247 _private member_ `TArray<TSharedRef<FSkeletalMeshTimelineStorage>> SkeletalMeshPoseTimelineStorage;`
- L248 _private member_ `TArray<TSharedRef<TraceServices::TIntervalTimeline<FSkeletalMeshFrameMessage>>> SkeletalMeshFrameTimelines;`
- L249 _private member_ `TArray<TSharedRef<TraceServices::TIntervalTimeline<FAnimGraphMessage>>> AnimGraphTimelines;`
- L250 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimNodeMessage>>> AnimNodeTimelines;`
- L251 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimNodeValueMessage>>> AnimNodeValueTimelines;`
- L252 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimSequencePlayerMessage>>> AnimSequencePlayerTimelines;`
- L253 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FBlendSpacePlayerMessage>>> BlendSpacePlayerTimelines;`
- L254 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimStateMachineMessage>>> StateMachineTimelines;`
- L255 _private member_ `TArray<TSharedRef<FAnimNotifyStateTimelineStorage>> AnimNotifyStateTimelineStorage;`
- L256 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimNotifyMessage>>> AnimNotifyTimelines;`
- L257 _private member_ `TArray<TSharedRef<FMontageTimelineStorage>> AnimMontageTimelineStorage;`
- L258 _private member_ `TArray<TSharedRef<FInertializationTimelineStorage>> InertializationTimelineStorage;`
- L259 _private member_ `TraceServices::TPagedArray<FTransform> SkeletalMeshPoseTransforms;`
- L260 _private member_ `TraceServices::TPagedArray<FSkeletalMeshNamedCurve> SkeletalMeshCurves;`
- L261 _private member_ `TraceServices::TPagedArray<FExternalMorphWeightMessage> ExternalMorphWeights;`
- L262 _private member_ `TraceServices::TPagedArray<int32> SkeletalMeshParentIndices;`
- L263 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimAttributeMessage>>> AnimAttributeTimelines;`
- L264 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FAnimSyncMessage>>> AnimSyncTimelines;`
- L265 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FPoseWatchMessage>>> PoseWatchTimelines;`
- L266 _private member_ `TraceServices::TPagedArray<uint16> PoseWatchRequiredBones;`
- L269 _private member_ `bool bHasAnyData;` — Flag to indicate if any data is present

#### struct `FAnimationProvider::FTickRecordTimelineStorage`  
`struct FTickRecordTimelineStorage`  
_L214-218_
- L216 _public member_ `TSet<TTuple<uint64, int32>> AssetIdAndPlayers;`
- L217 _public member_ `TSharedPtr<TraceServices::TPointTimeline<FTickRecordMessage>> Timeline;`

#### struct `FAnimationProvider::FSkeletalMeshTimelineStorage`  
`struct FSkeletalMeshTimelineStorage`  
_L220-225_
- L222 _public member_ `TSharedPtr<TraceServices::TIntervalTimeline<FSkeletalMeshPoseMessage>> Timeline;`
- L223 _public member_ `TSet<uint32> AllCurveIds;`
- L224 _public member_ `int32 NumExternalMorphSets = 0;`

#### struct `FAnimationProvider::FAnimNotifyStateTimelineStorage`  
`struct FAnimNotifyStateTimelineStorage`  
_L227-231_
- L229 _public member_ `TMap<uint64, uint32> NotifyIdToAnimNotifyStateTimeline;`
- L230 _public member_ `TArray<TSharedRef<TraceServices::TIntervalTimeline<FAnimNotifyMessage>>> Timelines;`

#### struct `FAnimationProvider::FMontageTimelineStorage`  
`struct FMontageTimelineStorage`  
_L233-237_
- L235 _public member_ `TSharedPtr<TraceServices::TPointTimeline<FAnimMontageMessage>> Timeline;`
- L236 _public member_ `TSet<uint64> AllMontageIds;`

#### struct `FAnimationProvider::FInertializationTimelineStorage`  
`struct FInertializationTimelineStorage`  
_L239-243_
- L241 _public member_ `TSharedPtr<TraceServices::TPointTimeline<FInertializationMessage>> Timeline;`
- L242 _public member_ `TMap<int32,EInertializationType> NodeTypes;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L17 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GAnimationProviderLockState;` (scope `TraceServices`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimationSharedData.h` (Private)


#### class `FAnimationSharedData`  
`class FAnimationSharedData`  
_L25-141_
- L28 _public prototype_ `FAnimationSharedData(FGameplaySharedData& InGameplaySharedData);`
- L30 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L31 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L32 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L33 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L36 _public prototype_ `void DrawPoses(UWorld* InWorld);`
- L41 _public prototype_ `void GetCustomDebugObjects(const IAnimationBlueprintEditor& InAnimationBlueprintEditor, TArray<FCustomDebugObject>& OutDebugList);` — Get the debug objects to plug into the anim BP debugger
- L44 _public prototype_ `void InvalidateViewports() const;` — Helper function to invalidate all viewports so non-realtime viewports update correctly.
- L47 _public prototype_ `void ShowAllMeshes();` — Show all the meshes
- L50 _public prototype_ `void HideAllMeshes();` — Hide all the meshes
- L54 _public prototype_ `bool AreAllAnimationTracksEnabled() const;` — Check whether all animation tracks are enabled
- L57 _public prototype_ `bool AreAnyAnimationTracksEnabled() const;` — Check whether any animation tracks are enabled
- L60 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const` — Get the last cached analysis session
- L63 _public function_ `bool IsAnalysisSessionValid() const` — Check whether the analysis session is valid
- L66 _public function_ `const FGameplaySharedData& GetGameplaySharedData() const` — Get the gameplay shared data we are linked to
- L69 _public prototype_ `void EnumerateSkeletalMeshPoseTracks(TFunctionRef<void(const TSharedRef<FSkeletalMeshPoseTrack>&)> InCallback) const;` — Enumerate skeletal mesh pose tracks
- L72 _public prototype_ `TSharedPtr<FSkeletalMeshPoseTrack> FindSkeletalMeshPoseTrack(uint64 InComponentId) const;` — Find a skeletal mesh track with the specified component ID
- L75 _public prototype_ `void EnumerateAnimNodesTracks(TFunctionRef<void(const TSharedRef<FAnimNodesTrack>&)> InCallback) const;` — Enumerate anim nodes tracks
- L78 _public prototype_ `TSharedPtr<FAnimNodesTrack> FindAnimNodesTrack(uint64 InAnimInstanceId) const;` — Find an anim nodes track with the specified anim instance ID
- L81 _public prototype_ `void OpenAnimGraphTab(uint64 InAnimInstanceId) const;` — Open an anim graph tab to see its schematic view
- L84 _public function_ `bool GetCurrentMarkerFrame(TraceServices::FFrame& OutFrame) const` — Get the current marker frame, if any. @return true if the frame is valid
- L87 _public function_ `bool ShouldShowTransportControls()` — Returns true if the transport controls toolbar should be displayed.
- L91 _private prototype_ `void ToggleAnimationTracks();` — UI handlers
- L92 _private prototype_ `void OnTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);`
- L93 _private prototype_ `void ToggleSkeletalMeshPoseTracks();`
- L94 _private prototype_ `void ToggleSkeletalMeshCurveTracks();`
- L95 _private prototype_ `void ToggleTickRecordTracks();`
- L96 _private prototype_ `void ToggleAnimNodeTracks();`
- L97 _private prototype_ `void ToggleAnimNotifyTracks();`
- L98 _private prototype_ `void ToggleMontageTracks();`
- L99 _private prototype_ `void ToggleTransportControls();`
- L103 _private member_ `FGameplaySharedData& GameplaySharedData;` — The gameplay shared data we are linked to
- L106 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;` — Cached analysis session, set in Tick()
- L109 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession;` — Cached timing view session, set in OnBeginSession/OnEndSession
- L112 _private member_ `TArray<TSharedRef<FSkeletalMeshPoseTrack>> SkeletalMeshPoseTracks;` — All the tracks we manage
- L113 _private member_ `TArray<TSharedRef<FSkeletalMeshCurvesTrack>> SkeletalMeshCurvesTracks;`
- L114 _private member_ `TArray<TSharedRef<FAnimationTickRecordsTrack>> AnimationTickRecordsTracks;`
- L115 _private member_ `TArray<TSharedRef<FAnimNodesTrack>> AnimNodesTracks;`
- L116 _private member_ `TArray<TSharedRef<FAnimNotifiesTrack>> AnimNotifyTracks;`
- L117 _private member_ `TArray<TSharedRef<FMontageTrack>> MontageTracks;`
- L120 _private member_ `mutable TArray<TWeakPtr<SDockTab>> WeakAnimGraphDocumentTabs;` — All the documents we have spawned
- L123 _private member_ `FDelegateHandle TimeMarkerChangedHandle;` — Delegate handles for hooks into the timing view
- L126 _private member_ `double MarkerTime;` — Various times and ranges
- L127 _private member_ `TraceServices::FFrame MarkerFrame;`
- L130 _private member_ `bool bTimeMarkerValid;` — Validity flags for pose times/ranges
- L131 _private member_ `bool bMarkerFrameValid;`
- L134 _private member_ `bool bSkeletalMeshPoseTracksEnabled;` — Flags controlling whether check type of our animation tracks are enabled
- L135 _private member_ `bool bSkeletalMeshCurveTracksEnabled;`
- L136 _private member_ `bool bTickRecordTracksEnabled;`
- L137 _private member_ `bool bAnimNodeTracksEnabled;`
- L138 _private member_ `bool bAnimNotifyTracksEnabled;`
- L139 _private member_ `bool bMontageTracksEnabled;`
- L140 _private member_ `bool bShowTransportControls;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L10 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Insights` (scope `UE`)
- L11 _namespace_ `namespace Timing` (scope `UE::Insights`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/AnimationTickRecordsTrack.h` (Private)


#### class `FTickRecordSeries`  
`class FTickRecordSeries : public FGameplayGraphSeries`  
_L16-43_
- inherits: `FGameplayGraphSeries`
- L33 _public prototype_ `virtual FString FormatValue(double Value) const override;`
- L37 _public member_ `uint64 AssetId;` — The asset ID that this series uses
- L40 _public member_ `int32 NodeId;` — The node ID that this series' data comes from
- L42 _public member_ `ESeriesType Type;`

#### enum `FTickRecordSeries::ESeriesType`  
`enum class ESeriesType : uint32`  
_L19-31_
- L21 _public enumerator_ `BlendWeight`
- L22 _public enumerator_ `PlaybackTime`
- L23 _public enumerator_ `RootMotionWeight`
- L24 _public enumerator_ `PlayRate`
- L25 _public enumerator_ `BlendSpacePositionX`
- L26 _public enumerator_ `BlendSpacePositionY`
- L27 _public enumerator_ `BlendSpaceFilteredPositionX`
- L28 _public enumerator_ `BlendSpaceFilteredPositionY`
- L30 _public enumerator_ `Count`

#### class `FAnimationTickRecordsTrack`  
`class FAnimationTickRecordsTrack : public FGameplayGraphTrack`  
_L45-84_
- inherits: `FGameplayGraphTrack`
- L50 _public prototype_ `FAnimationTickRecordsTrack(const FAnimationSharedData& InSharedData, uint64 InObjectId, const TCHAR* InName);`
- L52 _public prototype_ `virtual void PostUpdate(const ITimingTrackUpdateContext& Context) override;`
- L53 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L54 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L55 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L56 _public prototype_ `virtual bool UpdateSeriesBounds(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport) override;`
- L57 _public prototype_ `virtual void UpdateSeries(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport) override;`
- L58 _public prototype_ `virtual void AddAllSeries() override;`
- L59 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L63 _private prototype_ `void FindTickRecordMessage(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FTickRecordMessage&)> InFoundPredicate) const;` — Helper function used to find a tick record
- L67 _private prototype_ `template<typename ProjectionType> bool UpdateSeriesBoundsHelper(FTickRecordSeries& InSeries, const FTimingTrackViewport& InViewport, ProjectionType Projection);` — Helper function for series bounds update
- L71 _private prototype_ `template<typename ProjectionType> void UpdateSeriesHelper(FTickRecordSeries& InSeries, const FTimingTrackViewport& InViewport, ProjectionType Projection);` — Helper function for series update
- L75 _private member_ `const FAnimationSharedData& SharedData;` — The shared data
- L79 _private member_ `TSoftObjectPtr<UAnimBlueprintGeneratedClass> InstanceClass;` — The class that output this tick record
- L83 _private member_ `TWeakPtr<const FGraphTrackEvent> CachedHoveredEvent;` — Cached hovered event

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/BlendWeightsTrack.h` (Private)


#### class `RewindDebugger::FBlendWeightTrack`  
`class FBlendWeightTrack : public FRewindDebuggerTrack`  
_L14-61_
- inherits: `FRewindDebuggerTrack`
- L29 _public prototype_ `FBlendWeightTrack(uint64 InObjectId, uint64 AssetId, uint32 NodeId, ECurveType CurveType = ECurveType::BlendWeight);`
- L31 _public function_ `uint32 GetNodeId() const`
- L32 _public function_ `uint64 GetAssetId() const`
- L35 _private prototype_ `virtual bool UpdateInternal() override;`
- L36 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L37 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L38 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L40 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L41 _private function_ `virtual FName GetNameInternal() const override`
- L42 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L43 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L44 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L46 _private prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;`
- L48 _private member_ `uint64 AssetId;`
- L49 _private member_ `uint32 NodeId;`
- L51 _private member_ `ECurveType CurveType;`
- L53 _private member_ `FSlateIcon Icon;`
- L54 _private member_ `FText CurveName;`
- L55 _private member_ `uint64 ObjectId;`
- L57 _private member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;`
- L58 _private member_ `mutable int CurvesUpdateRequested = 0;`
- L60 _private member_ `TArray<TSharedPtr<FBlendWeightTrack>> Children;`

#### enum `RewindDebugger::FBlendWeightTrack::ECurveType`  
`enum class ECurveType`  
_L17-27_
- L19 _public enumerator_ `BlendWeight`
- L20 _public enumerator_ `PlaybackTime`
- L21 _public enumerator_ `RootMotionWeight`
- L22 _public enumerator_ `PlayRate`
- L23 _public enumerator_ `BlendSpacePositionX`
- L24 _public enumerator_ `BlendSpacePositionY`
- L25 _public enumerator_ `BlendSpaceFilteredPositionX`
- L26 _public enumerator_ `BlendSpaceFilteredPositionY`

#### class `RewindDebugger::FBlendWeightsTrack`  
`class FBlendWeightsTrack : public FRewindDebuggerTrack`  
_L63-82_
- inherits: `FRewindDebuggerTrack`
- L66 _public prototype_ `FBlendWeightsTrack(uint64 InObjectId);`
- L69 _private prototype_ `virtual bool UpdateInternal() override;`
- L70 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L71 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L73 _private function_ `virtual FName GetNameInternal() const override`
- L74 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L75 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L77 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L79 _private member_ `FSlateIcon Icon;`
- L80 _private member_ `uint64 ObjectId;`
- L81 _private member_ `TArray<TSharedPtr<FBlendWeightTrack>> Children;`

#### class `RewindDebugger::FBlendWeightsTrackCreator`  
`class FBlendWeightsTrackCreator : public IRewindDebuggerTrackCreator`  
_L85-93_
- inherits: `IRewindDebuggerTrackCreator`
- L88 _public prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L89 _public prototype_ `virtual FName GetNameInternal() const override;`
- L90 _public prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L91 _public prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L92 _public prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/BoolPropertyTrack.h` (Private)


#### class `RewindDebugger::FBoolPropertyTrack`  
`class FBoolPropertyTrack : public FPropertyTrack`  
_L13-34_
- inherits: `FPropertyTrack`
- desc: Track that displays a object's boolean property value overtime
- L20 _public prototype_ `FBoolPropertyTrack(uint64 InObjectId, const TSharedPtr<FObjectPropertyInfo> & InObjectProperty, const TSharedPtr<FPropertyTrack> & InParentTrack);` — Constructor
- L25 _private prototype_ `virtual bool UpdateInternal() override;` — Begin IRewindDebuggerTrack interface
- L26 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L30 _private prototype_ `TSharedPtr<SSegmentedTimelineView::FSegmentData> GetSegmentData() const;` — @return Segmented boolean data for watched property
- L33 _private member_ `TSharedPtr<SSegmentedTimelineView::FSegmentData> EnabledSegments;` — Keep track of segments when the traced value was true

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/ExternalMorphTrack.h` (Private)


#### class `RewindDebugger::FExternalMorphTrack`  
`class FExternalMorphTrack : public FRewindDebuggerTrack`  
_L13-46_
- inherits: `FRewindDebuggerTrack`
- desc: Sub Track for a external morph target.
- L17 _public prototype_ `FExternalMorphTrack(uint64 InObjectId, int32 InMorphIndex, int32 InMorphSetIndex);`
- L19 _public function_ `int32 GetMorphIndex() const`
- L23 _private prototype_ `virtual bool UpdateInternal() override;` — FRewindDebuggerTrack overrides.
- L24 _private prototype_ `TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L25 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L26 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L27 _private function_ `virtual FName GetNameInternal() const override`
- L28 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L29 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L32 _private prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;`
- L35 _protected prototype_ `void UpdateCurvePointsInternal();`
- L39 _protected member_ `int32 MorphIndex = INDEX_NONE;`
- L40 _protected member_ `int32 MorphSetIndex = INDEX_NONE;`
- L41 _protected member_ `uint64 ObjectId = 0;`
- L42 _protected member_ `FText Name;`
- L43 _protected member_ `FSlateIcon Icon;`
- L44 _protected member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;`
- L45 _protected member_ `mutable int CurvesUpdateRequested = 0;`

#### class `RewindDebugger::FExternalMorphSetTrack`  
`class FExternalMorphSetTrack : public FRewindDebuggerTrack`  
_L50-72_
- inherits: `FRewindDebuggerTrack`
- desc: The external morph target set, which is the parent of a collection of FExternalMorphTrack items.
- L54 _public prototype_ `FExternalMorphSetTrack(uint64 InObjectId, int32 InMorphSetIndex);`
- L58 _private prototype_ `virtual bool UpdateInternal() override;` — FRewindDebuggerTrack overrides.
- L59 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L60 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L61 _private function_ `virtual FName GetNameInternal() const override`
- L62 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L63 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L64 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L68 _protected member_ `FSlateIcon Icon;`
- L69 _protected member_ `uint64 ObjectId;`
- L70 _protected member_ `int32 MorphSetIndex;`
- L71 _protected member_ `TArray<TSharedPtr<FExternalMorphTrack>> Children;`

#### class `RewindDebugger::FExternalMorphSetGroupTrack`  
`class FExternalMorphSetGroupTrack : public FRewindDebuggerTrack`  
_L76-97_
- inherits: `FRewindDebuggerTrack`
- desc: The external morph set group track, which is the parent of all morph sets.
- L80 _public prototype_ `FExternalMorphSetGroupTrack(uint64 InObjectId);`
- L84 _private prototype_ `virtual bool UpdateInternal() override;` — FRewindDebuggerTrack overrides.
- L85 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L86 _private function_ `virtual FName GetNameInternal() const override`
- L87 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L88 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L89 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L93 _protected member_ `FSlateIcon Icon;`
- L94 _protected member_ `uint64 ObjectId;`
- L95 _protected member_ `TArray<TSharedPtr<FExternalMorphSetTrack>> Children;`
- L96 _protected member_ `TArray<int32> PrevMorphSetIndexValues;`

#### class `RewindDebugger::FExternalMorphSetGroupTrackCreator`  
`class FExternalMorphSetGroupTrackCreator : public IRewindDebuggerTrackCreator`  
_L102-113_
- inherits: `IRewindDebuggerTrackCreator`
- desc: The creator for the external morph set track.
- L107 _private prototype_ `virtual FName GetTargetTypeNameInternal() const override;` — IRewindDebuggerTrackCreator overrides.
- L108 _private prototype_ `virtual FName GetNameInternal() const override;`
- L109 _private prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L110 _private prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L111 _private prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayAnalyzer.h` (Private)


#### class `FGameplayAnalyzer`  
`class FGameplayAnalyzer : public UE::Trace::IAnalyzer`  
_L10-45_
- inherits: `UE::Trace::IAnalyzer`
- L13 _public prototype_ `FGameplayAnalyzer(TraceServices::IAnalysisSession& InSession, FGameplayProvider& InGameplayProvider);`
- L15 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L16 _public function_ `virtual void OnAnalysisEnd() override`
- L17 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L43 _private member_ `TraceServices::IAnalysisSession& Session;`
- L44 _private member_ `FGameplayProvider& GameplayProvider;`

#### enum `FGameplayAnalyzer::(anonymous)`  
``  
_L21-41_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L22 _enumerator_ `RouteId_World` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L23 _enumerator_ `RouteId_Type` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L24 _enumerator_ `RouteId_Object` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L25 _enumerator_ `RouteId_ObjectTransform` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L26 _enumerator_ `RouteId_ObjectEvent` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L27 _enumerator_ `RouteId_ObjectLifetimeBegin` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L28 _enumerator_ `RouteId_ObjectLifetimeBegin2` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L29 _enumerator_ `RouteId_ObjectLifetimeEnd` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L30 _enumerator_ `RouteId_ObjectLifetimeEnd2` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L31 _enumerator_ `RouteId_PawnPossess` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L32 _enumerator_ `RouteId_View` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L33 _enumerator_ `RouteId_ClassPropertyStringId` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L34 _enumerator_ `RouteId_ClassProperty` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L35 _enumerator_ `RouteId_PropertiesStart` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L36 _enumerator_ `RouteId_PropertiesStart2` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L37 _enumerator_ `RouteId_PropertiesEnd` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L38 _enumerator_ `RouteId_PropertyValue2` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L39 _enumerator_ `RouteId_PropertyValue3` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)
- L40 _enumerator_ `RouteId_RecordingInfo` (scope `FGameplayAnalyzer::__anon444f8f3c0103`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayGraphTrack.h` (Private)


#### enum `EGameplayGraphLayout`  
`enum class EGameplayGraphLayout : int32`  
_L15-22_
- desc: The various layouts that we display series with
- L18 _public enumerator_ `Overlay` — Draw series overlaid one on top of the other
- L21 _public enumerator_ `Stack` — Draw series in a vertical stack

#### class `FGameplayGraphSeries`  
`class FGameplayGraphSeries : public FGraphSeries`  
_L25-40_
- inherits: `FGraphSeries`
- desc: Common functionality for gameplay-related graph series
- L29 _public prototype_ `void UpdateAutoZoom(const FTimingTrackViewport& InViewport, const FGameplayGraphTrack& InTrack, int32 InActiveSeriesIndex);` — Custom overload for auto zoom
- L32 _public function_ `bool IsDrawn() const` — Check whether this series has any events with the current view
- L35 _public prototype_ `void ComputePosition(const FTimingTrackViewport& InViewport, const FGameplayGraphTrack& InTrack, int32 InActiveSeriesIndex, float& OutTopY, float& OutBottomY) const;` — Helper for auto-zoom and drawing
- L38 _public member_ `float CurrentMin;`
- L39 _public member_ `float CurrentMax;`

#### class `FGameplayGraphTrack`  
`class FGameplayGraphTrack : public TGameplayTrackMixin<FGraphTrack>`  
_L43-103_
- inherits: `TGameplayTrackMixin<FGraphTrack>`
- desc: Track holding common functionality for gameplay-related graph tracks
- L49 _public member_ `static constexpr EGraphOptions ShowLabelsOption = EGraphOptions::FirstCustomOption;` — Whether to draw labels
- L52 _public prototype_ `FGameplayGraphTrack(const FGameplaySharedData& InGameplaySharedData, uint64 InObjectID, const FText& InName);`
- L54 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L55 _public prototype_ `virtual void PreUpdate(const ITimingTrackUpdateContext& Context) override;`
- L56 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L59 _public function_ `virtual void GetVariantsAtTime(double InTime, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const` — Get all variants at the specified time/frame
- L60 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const;`
- L63 _public function_ `float GetRequestedTrackSizeScale() const` — Get the requested track size scale
- L66 _public function_ `int32 GetNumActiveSeries() const` — Get the number of active series (i.e. visible)
- L69 _public function_ `EGameplayGraphLayout GetLayout() const` — Get the layout we are displaying out graphs as
- L73 _protected function_ `virtual void AddAllSeries()` — Add all the series to this track
- L76 _protected function_ `virtual void UpdateSeries(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport)` — Update a single series' data (from PreUpdate())
- L80 _protected function_ `virtual bool UpdateSeriesBounds(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport)` — Update a single series' bounds @return true from this if there are graph events in the current viewport
- L84 _private prototype_ `void UpdateTrackHeight(const ITimingTrackUpdateContext& Context);` — Helper for PreUpdate to update the track height
- L87 _private prototype_ `void UpdateSeriesInternal(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport, int32 InActiveSeriesIndex);` — Helper to update and zoom series
- L90 _protected member_ `const FGameplaySharedData& GameplaySharedData;`
- L93 _protected member_ `float RequestedTrackSizeScale;` — The track size we want to be displayed at
- L96 _protected member_ `float BorderY;` — The size of the border between tracks
- L99 _protected member_ `int32 NumActiveSeries;` — The current number of active series
- L102 _protected member_ `EGameplayGraphLayout Layout;` — The current series layout

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayInsightsModule.h` (Private)


#### class `FGameplayInsightsModule`  
`class FGameplayInsightsModule : public IGameplayInsightsModule`  
_L23-57_
- inherits: `IGameplayInsightsModule`
- L27 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L28 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `virtual void EnableObjectPropertyTrace(UObject* Object, bool bEnable = true) override;`
- L32 _public prototype_ `virtual bool IsObjectPropertyTraceEnabled(UObject* Object) override;`
- L33 _public function_ `virtual void StartTrace() override`
- L37 _public prototype_ `TSharedRef<SDockTab> SpawnTimingProfilerDocumentTab(const FTabManager::FSearchPreference& InSearchPreference);` — Spawn a document tab
- L40 _protected prototype_ `void RegisterTimingProfilerLayoutExtensions(FInsightsMajorTabExtender& InOutExtender);`
- L42 _protected prototype_ `void RegisterMenus();`
- L46 _private member_ `FGameplayTraceModule GameplayTraceModule;`
- L48 _private member_ `FGameplayTimingViewExtender GameplayTimingViewExtender;`
- L50 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L53 _private member_ `FDelegateHandle CustomDebugObjectHandle;`
- L56 _private member_ `TWeakPtr<FTabManager> WeakTimingProfilerTabManager;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Trace` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayInsightsStyle.h` (Private)


#### class `FGameplayInsightsStyle`  
`class FGameplayInsightsStyle final : public FSlateStyleSet`  
_L10-74_
- inherits: `FSlateStyleSet`
- L14 _public function_ `FGameplayInsightsStyle() : FSlateStyleSet("GameplayInsightsStyle") , SelectionColor_LinearRef(MakeShareable(new FLinearColor( 0.728f, 0.364f, 0.003f))) , SelectionColor_Pressed_LinearRef(MakeShareable(new FLinearColor( 0.701f, 0.225f, 0.003f))) , SelectionColor(SelectionColor_LinearRef) , SelectionColor_Pressed(SelectionColor_Pressed_LinearRef)`
- L59 _public function_ `static FGameplayInsightsStyle& Get()`
- L65 _public function_ `~FGameplayInsightsStyle()`
- L70 _public member_ `const TSharedRef<FLinearColor> SelectionColor_LinearRef;`
- L71 _public member_ `const TSharedRef<FLinearColor> SelectionColor_Pressed_LinearRef;`
- L72 _public member_ `const FSlateColor SelectionColor;`
- L73 _public member_ `const FSlateColor SelectionColor_Pressed;`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayProvider.h` (Private)


#### class `FGameplayProvider`  
`class FGameplayProvider : public IGameplayProvider`  
_L25-265_
- inherits: `IGameplayProvider`
- L28 _public member_ `static FName ProviderName;`
- L30 _public prototype_ `explicit FGameplayProvider(TraceServices::IAnalysisSession& InSession);`
- L33 _public function_ `virtual void BeginRead() const override`
- L38 _public function_ `virtual void EndRead() const override`
- L43 _public function_ `virtual void ReadAccessCheck() const override`
- L49 _public function_ `virtual void BeginEdit() const override`
- L54 _public function_ `virtual void EndEdit() const override`
- L59 _public function_ `virtual void EditAccessCheck() const override`
- L65 _public prototype_ `virtual bool ReadObjectEventsTimeline(const RewindDebugger::FObjectId& InObjectId, TFunctionRef<void(const ObjectEventsTimeline&)> Callback) const override;`
- L66 _public prototype_ `virtual bool ReadObjectEvent(const RewindDebugger::FObjectId& InObjectId, uint64 InMessageId, TFunctionRef<void(const FObjectEventMessage&)> Callback) const override;`
- L67 _public prototype_ `virtual bool ReadObjectPropertiesTimeline(uint64 InObjectId, TFunctionRef<void(const ObjectPropertiesTimeline&)> Callback) const override;`
- L68 _public prototype_ `virtual bool ReadObjectPropertiesStorage(uint64 InObjectId, const FObjectPropertiesMessage& InMessage, TFunctionRef<void(const TConstArrayView<FObjectPropertyValue>&)> Callback) const override;`
- L69 _public prototype_ `virtual void EnumerateObjectPropertyValues(uint64 InObjectId, const FObjectPropertiesMessage& InMessage, TFunctionRef<void(const FObjectPropertyValue&)> Callback) const override;`
- L70 _public prototype_ `virtual void EnumerateObjects(TFunctionRef<void(const FObjectInfo&)> Callback) const override;`
- L71 _public prototype_ `virtual void EnumerateObjects(double StartTime, double EndTime, TFunctionRef<void(const FObjectInfo&)> Callback) const override;`
- L72 _public prototype_ `virtual void EnumerateWorlds(TFunctionRef<void(const FWorldInfo&)> Callback) const override;`
- L73 _public prototype_ `virtual void EnumerateSubobjects(const RewindDebugger::FObjectId& InObjectId, TFunctionRef<void(const RewindDebugger::FObjectId& SubObjectId)> Callback) const override;`
- L74 _public prototype_ `virtual const FObjectPropertyValue* FindPropertyValueFromStorageIndex(uint64 InObjectId, int64 InStorageIndex) const override;`
- L75 _public prototype_ `virtual const FClassInfo* FindClassInfo(uint64 InClassId) const override;`
- L76 _public prototype_ `virtual const UStruct* FindType(uint64 InTypeId, bool bSearchBlueprints = true) const override;`
- L77 _public prototype_ `virtual const FClassInfo* FindClassInfo(const TCHAR* InClassPath) const override;`
- L78 _public prototype_ `virtual bool IsSubClassOf(uint64 InSubClassId, uint64 InParentClassId) const override;`
- L79 _public prototype_ `virtual const FObjectInfo* FindObjectInfo(const uint64 InObjectId) const override;`
- L80 _public prototype_ `virtual const FObjectInfo* FindObjectInfo(const RewindDebugger::FObjectId& InObjectId) const override;`
- L81 _public prototype_ `virtual const FWorldInfo* FindWorldInfo(uint64 InObjectId) const override;`
- L82 _public prototype_ `virtual const FWorldInfo* FindWorldInfoFromObject(uint64 InObjectId) const override;`
- L83 _public prototype_ `virtual bool IsWorld(uint64 InObjectId) const override;`
- L84 _public prototype_ `virtual const FClassInfo& GetClassInfo(uint64 InClassId) const override;`
- L85 _public prototype_ `virtual const FClassInfo& GetClassInfoFromObject(uint64 InObjectId) const override;`
- L86 _public prototype_ `virtual const FObjectInfo& GetObjectInfo(uint64 InObjectId) const override;`
- L87 _public prototype_ `virtual const FObjectInfo& GetObjectInfo(const RewindDebugger::FObjectId& InObjectId) const override;`
- L88 _public function_ `virtual FOnObjectEndPlay& OnObjectEndPlay() override`
- L92 _public prototype_ `virtual const TCHAR* GetPropertyName(uint32 InPropertyStringId) const override;`
- L93 _public prototype_ `virtual const RecordingInfoTimeline* GetRecordingInfo(uint32 RecordingId) const override;`
- L94 _public prototype_ `virtual void ReadViewTimeline(TFunctionRef<void(const ViewTimeline&)> Callback) const override;`
- L95 _public prototype_ `virtual double GetRecordingDuration() const override;`
- L96 _public prototype_ `virtual FSlateIcon FindIconForClass(uint64 ClassId) const override;`
- L99 _public prototype_ `void AppendClass(uint64 InClassId, uint64 InSuperId, const TCHAR* InClassName, const TCHAR* InClassPathName);` — Add a class message
- L102 _public prototype_ `void AppendObject(const RewindDebugger::FObjectId& InObjectId, const RewindDebugger::FObjectId& InOuterId, uint64 InClassId, const TCHAR* InObjectName, const TCHAR* InObjectPathName, EObjectInfoFlags Flags);` — Add an object message
- L105 _public prototype_ `void AppendObjectTransform(uint64 InObjectId, double InProfileTime, double InRecordingTime, const FTransform& Transform);` — Add an object transform
- L108 _public prototype_ `void AppendObjectLifetimeBegin(const RewindDebugger::FObjectId& InObjectId, double InProfileTime, double InRecordingTime);` — Add an object create message
- L111 _public prototype_ `void AppendObjectLifetimeEnd(const RewindDebugger::FObjectId& InObjectId, double InProfileTime, double InRecordingTime);` — Add an object destroy message
- L114 _public prototype_ `void AppendObjectEvent(const RewindDebugger::FObjectId& InObjectId, double InTime, const TCHAR* InEvent);` — Add an object event message
- L117 _public prototype_ `void AppendPawnPossess(uint64 InControllerId, uint64 InPawnId, double InTime);` — Add a Controller Attach message
- L120 _public prototype_ `void AppendView(uint64 InPlayerId, double InTime, const FVector& InPosition, const FRotator& InRotation, float InFov, float InAspectRatio);` — Add a view message
- L123 _public prototype_ `void AppendWorld(uint64 InWorldId, int32 InPIEInstanceId, uint8 InType, uint8 InNetMode, bool bInIsSimulating);` — Add a world message
- L126 _public prototype_ `void AppendRecordingInfo(uint64 InWorldId, double InProfileTime, uint32 InRecordingIndex, uint32 InFrameIndex, double InElapsedTime);` — Add a recording info message
- L129 _public prototype_ `void AppendClassPropertyStringId(uint32 InStringId, const FStringView& InString);` — Add a class property string ID message
- L132 _public prototype_ `void AppendPropertiesStart(uint64 InObjectId, double InTime, uint64 InEventId, double InRecordingTime);` — Add a 'properties start' message
- L135 _public prototype_ `void AppendPropertiesEnd(uint64 InObjectId, double InTime);` — Add a 'properties end' message
- L138 _public prototype_ `void AppendPropertyValue(uint64 InObjectId, double InTime, uint64 InEventId, int32 InParentId, uint32 InTypeStringId, uint32 InNameId, uint32 InParentNameId, const FStringView& InValue);` — Add a property value message
- L141 _public prototype_ `bool HasAnyData() const;` — Check whether we have any data
- L144 _public prototype_ `bool HasObjectProperties() const;` — Check whether we have any object property data
- L147 _public prototype_ `virtual uint64 FindPossessingController(uint64 Pawn, double Time) const override;` — Search PawnPossession timeline to find the Controller Object Id for a Pawn (or 0 if none)
- L150 _public prototype_ `virtual bool GetObjectTransform(uint64 InObjectId, double InStartTime, double InEndTime, FTransform& OutTransform) const override;` — find the Transform of an object within a frame that Starts at InStartTime, and ends at InEndTime
- L153 _public prototype_ `virtual TRange<double> GetObjectTraceLifetime(const RewindDebugger::FObjectId& InObjectId) const override;` — find the Trace time range for which an object existed
- L156 _public prototype_ `virtual TRange<double> GetObjectRecordingLifetime(const RewindDebugger::FObjectId& InObjectId) const override;` — find the Recording time range for which an object existed
- L159 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L160 _private member_ `TraceServices::IAnalysisSession& Session;`
- L163 _private member_ `TArray<FClassInfo> ClassInfos;` — All class info, grow only for stable indices
- L166 _private member_ `TArray<FObjectInfo> ObjectInfos;` — All object info, grow only for stable indices
- L169 _private member_ `TArray<FWorldInfo> WorldInfos;` — All world info, grow only for stable indices
- L172 _private member_ `TMap<uint64, int32> ClassIdToIndexMap;` — Classes that are in use. Map from Id to ClassInfo index
- L175 _private member_ `TMap<RewindDebugger::FObjectId, int32> ObjectIdToIndexMap;` — Objects that are in use. Map from Id to ObjectInfo index
- L178 _private member_ `TMap<uint64, int32> WorldIdToIndexMap;` — Worlds that are in use. Map from Id to WorldInfo index
- L181 _private member_ `TMap<RewindDebugger::FObjectId, uint32> ObjectIdToEventTimelines;` — Map from object Ids to timeline index
- L182 _private member_ `TMap<uint64, uint32> ObjectIdToTransformTimeline;`
- L183 _private member_ `TMap<uint64, uint32> ObjectIdToPropertiesStorage;`
- L213 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FObjectEventMessage>>> EventTimelines;` — Message storage
- L214 _private member_ `TraceServices::TPointTimeline<FObjectTransformMessage> TransformTimeline;`
- L215 _private member_ `TArray<TSharedRef<FObjectPropertiesStorage>> PropertiesStorage;`
- L216 _private member_ `TSharedPtr<TraceServices::TPointTimeline<FViewMessage>> ViewTimeline;`
- L219 _private member_ `TMap<FStringView, int32> ClassPathNameToIndexMap;` — Map of class path name to ClassInfo index
- L222 _private member_ `const TCHAR* EndPlayEvent;` — EndPlay event text
- L225 _private member_ `FOnObjectEndPlay OnObjectEndPlayDelegate;` — Delegate fired when an object receives an end play event
- L228 _private member_ `TMap<uint32, const TCHAR*> PropertyStrings;` — Map from string ID to stored string
- L231 _private member_ `TMap<uint32, TSharedRef<TraceServices::TPointTimeline<FRecordingInfoMessage>>> Recordings;` — Map of RecordingInfo Timelines by RecordingId - Each timeline is a mapping from Gameplay Elapsed time to Profiler Elapsed Time for one recording session
- L234 _private member_ `TraceServices::TIntervalTimeline<FPawnPossessMessage> PawnPossession;` — Timeline containing intervals where a controller is attached to a pawn
- L237 _private member_ `TraceServices::TIntervalTimeline<FObjectExistsMessage> ObjectLifetimes;` — Timeline containing intervals where an object exists
- L240 _private member_ `TraceServices::TIntervalTimeline<FObjectExistsMessage> ObjectRecordingLifetimes;` — Timeline containing intervals where an object exists - In Rewind Debugger recording time units, to avoid excessive conversions
- L243 _private member_ `TMap<uint64, uint64> ActivePawnPossession;` — map from controller id to index in the PawnPossession timeline, for lookup when ending events
- L246 _private member_ `TMap<RewindDebugger::FObjectId, uint64> ActiveObjectLifetimes;` — map from object id to index in ObjectLifetimes, for lookup when objects are destroyed
- L249 _private member_ `TMap<RewindDebugger::FObjectId, uint64> ActiveObjectRecordingLifetimes;` — map from object id to index in ObjectRecordingLifetimes, for lookup
- L252 _private member_ `TMultiMap<RewindDebugger::FObjectId, RewindDebugger::FObjectId> ObjectHierarchy;` — MultiMap from parent object to sub objects, to avoid slow reverse lookups
- L255 _private member_ `TOptional<EBuildTargetType> TargetType;` — The target type specified in the current analysis session
- L258 _private member_ `bool bHasAnyData = false;` — Whether we have any data
- L261 _private member_ `double RecordingDuration = 0.0;` — The elapsed world time
- L264 _private member_ `bool bHasObjectProperties = false;` — Whether we have any object properties

#### struct `FGameplayProvider::FPawnPossessMessage`  
`struct FPawnPossessMessage`  
_L185-189_
- L187 _public member_ `uint64 ControllerId = 0;`
- L188 _public member_ `uint64 PawnId = 0;`

#### struct `FGameplayProvider::FObjectTransformMessage`  
`struct FObjectTransformMessage`  
_L191-196_
- L193 _public member_ `uint64 ObjectId = 0;`
- L194 _public member_ `double RecordingTime;`
- L195 _public member_ `FTransform Transform;`

#### struct `FGameplayProvider::FObjectExistsMessage`  
`struct FObjectExistsMessage`  
_L198-201_
- L200 _public member_ `RewindDebugger::FObjectId ObjectId;`

#### struct `FGameplayProvider::FObjectPropertiesStorage`  
`struct FObjectPropertiesStorage`  
_L203-210_
- L205 _public member_ `double OpenStartTime;`
- L206 _public member_ `uint64 OpenEventId;`
- L207 _public member_ `FObjectPropertiesMessage OpenEvent;`
- L208 _public member_ `TSharedPtr<TraceServices::TIntervalTimeline<FObjectPropertiesMessage>> Timeline;`
- L209 _public member_ `TArray<FObjectPropertyValue> Values;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace RewindDebugger`
- L19 _namespace_ `namespace TraceServices`
- L22 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GGameplayProviderLockState;` (scope `TraceServices`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplaySharedData.h` (Private)


#### class `FGameplaySharedData`  
`class FGameplaySharedData`  
_L17-116_
- L20 _public prototype_ `FGameplaySharedData();`
- L22 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L23 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L24 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L25 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L28 _public prototype_ `TSharedRef<FObjectEventsTrack> GetObjectEventsTrackForId(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession, const FObjectInfo& InObjectInfo);` — Helper function. Builds object track hierarchy on-demand and returns a track for the supplied object info.
- L31 _public prototype_ `void MakeTrackAndAncestorsVisible(const TSharedRef<FObjectEventsTrack>& InObjectEventsTrack, bool bInVisible);` — Helper function to make tracks visible when children are first added
- L34 _public prototype_ `bool AreGameplayTracksEnabled() const;` — Check whether gameplay tacks are enabled
- L37 _public function_ `void InvalidateObjectTracksOrder()` — Invalidate object trcks order, so they get re-sorted next tick
- L40 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const` — Get the last cached analysis session
- L43 _public function_ `UE::Insights::Timing::ITimingViewSession& GetTimingViewSession()` — Get the timing view session
- L46 _public function_ `bool IsAnalysisSessionValid() const` — Check the validity of the analysis session
- L49 _public prototype_ `void EnumerateObjectTracks(TFunctionRef<void(const TSharedRef<FObjectEventsTrack>&)> InCallback) const;` — Enumerate object tracks
- L52 _public function_ `const TArray<TSharedRef<FBaseTimingTrack>>& GetRootTracks() const` — Get the root tracks
- L55 _public function_ `FSimpleMulticastDelegate& OnTracksChanged()` — Delegate fired when tracks change
- L74 _public prototype_ `static TSharedPtr<SDockTab> FindDocumentTab(const TArray<TWeakPtr<SDockTab>>& InWeakDocumentTabs, TFunction<bool(const TSharedRef<SDockTab>&)> InSearchFunction);` — Helper function to find an existing document tab
- L77 _public prototype_ `void OpenTrackVariantsTab(const FGameplayTrack& InGameplayTrack) const;` — Open a tab to see a track's variants
- L81 _private prototype_ `void SortTracks();` — Re-sort tracks if track ordering has changed
- L84 _private prototype_ `void ToggleGameplayTracks();` — UI handlers
- L85 _private prototype_ `void ToggleObjectPropertyTracks();`
- L86 _private prototype_ `bool AreObjectPropertyTracksEnabled() const;`
- L90 _private member_ `TMap<uint64, TSharedPtr<FObjectEventsTrack>> ObjectTracks;` — Track for each tracked object, mapped from Object ID -> track
- L91 _private member_ `TArray<TSharedRef<FObjectPropertiesTrack>> ObjectPropertyTracks;`
- L94 _private member_ `TArray<TSharedRef<FBaseTimingTrack>> RootTracks;` — The root tracks
- L97 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;` — Cached analysis session, set in Tick()
- L100 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession;` — Cached timing view session, set in OnBeginSession/OnEndSession
- L103 _private member_ `FSimpleMulticastDelegate OnTracksChangedDelegate;` — Delegate fired when tracks change
- L106 _private member_ `mutable TArray<TWeakPtr<SDockTab>> WeakTrackVariantsDocumentTabs;` — All the documents we have spawned
- L109 _private member_ `bool bObjectTracksDirty;` — Dirty flag for adding object tracks, used to trigger re-sorting
- L112 _private member_ `bool bObjectTracksEnabled;` — Whether all of our object tracks are enabled
- L115 _private member_ `bool bObjectPropertyTracksEnabled;` — Whether all of our object property tracks are enabled

#### struct `FGameplaySharedData::FSearchForTab`  
`struct FSearchForTab : public FTabManager::FSearchPreference`  
_L58-71_
- inherits: `FTabManager::FSearchPreference`
- desc: Search predicate wrapper for an open document
- L60 _public function_ `FSearchForTab(TFunction<TSharedPtr<SDockTab>(void)> InSearchFunction) : SearchFunction(InSearchFunction)`
- L65 _public function_ `virtual TSharedPtr<SDockTab> Search(const FTabManager& Manager, FName PlaceholderId, const TSharedRef<SDockTab>& UnmanagedTab) const override`
- L70 _public member_ `TFunction<TSharedPtr<SDockTab>(void)> SearchFunction;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)
- L9 _namespace_ `namespace Timing` (scope `UE::Insights`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayTimingViewExtender.h` (Private)


#### class `FGameplayTimingViewExtender`  
`class FGameplayTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L15-48_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L19 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;` — Insights::ITimingViewExtender interface
- L20 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L21 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L22 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L26 _public prototype_ `static UWorld* GetWorldToVisualize();` — Gets a world to perform visualizations within, depending on context
- L29 _public prototype_ `void GetCustomDebugObjects(const IAnimationBlueprintEditor& InAnimationBlueprintEditor, TArray<FCustomDebugObject>& OutDebugList);` — Get custom debug objects for integration with anim blueprint debugging
- L33 _public prototype_ `void TickVisualizers(float DeltaTime);` — Tick the visualizers
- L47 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;` — The data we host per-session

#### struct `FGameplayTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L36-44_
- L39 _public member_ `FGameplaySharedData* GameplaySharedData;` — Shared data
- L40 _public member_ `FAnimationSharedData* AnimationSharedData;`
- L42 _public member_ `TSharedPtr<SGameplayInsightsTransportControls> TransportControls;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Insights` (scope `UE`)
- L7 _namespace_ `namespace Timing` (scope `UE::Insights`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayTraceModule.h` (Private)


#### class `FGameplayTraceModule`  
`class FGameplayTraceModule : public TraceServices::IModule`  
_L10-22_
- inherits: `TraceServices::IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L15 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L17 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L18 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L21 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L24 _prototype_ `const IAnimationProvider* ReadAnimationProvider(const TraceServices::IAnalysisSession& Session);`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/GameplayTrack.h` (Private)


#### class `FGameplayTrack`  
`class FGameplayTrack`  
_L28-89_
- desc: Provides parent/child hierarchy structure and the owning object Id Designed as a compositional member of outer timing tracks
- L31 _public function_ `FGameplayTrack(FBaseTimingTrack& InTimingTrack, uint64 InObjectId) : TimingTrack(InTimingTrack) , ObjectId(InObjectId) , Parent(nullptr) , Indent(0)`
- L40 _public function_ `uint64 GetObjectId() const` — Get the object ID for this track
- L42 _public prototype_ `RewindDebugger::FObjectId GetAssociatedObjectId() const;`
- L45 _public function_ `FGameplayTrack* GetParentTrack()` — Get the parent track
- L48 _public function_ `TArrayView<FGameplayTrack*> GetChildTracks()` — Get child tracks
- L51 _public prototype_ `void AddChildTrack(FGameplayTrack& InChildTrack);` — Add a child track
- L54 _public prototype_ `TSharedPtr<FBaseTimingTrack> FindChildTrack(uint64 InObjectId, TFunctionRef<bool(const FBaseTimingTrack& InTrack)> Callback) const;` — Find a child track using the specified callback
- L57 _public prototype_ `void DrawHeaderForTimingTrack(const ITimingTrackDrawContext& InContext, const FBaseTimingTrack& InTrack, bool bUsePreallocatedLayers) const;` — Helper to draw the name for a timing track (uses indentation etc.)
- L60 _public function_ `TSharedRef<FBaseTimingTrack> GetTimingTrack() const` — Access the outer timing track
- L63 _public function_ `void SetIndent(uint32 InIndent)` — Access indent
- L66 _public function_ `uint32 GetIndent() const` — Access indent
- L69 _public prototype_ `FText GetWorldName(const TraceServices::IAnalysisSession& InAnalysisSession) const;` — Get the world name for this object
- L72 _public prototype_ `static FText GetWorldPostFix(const FWorldInfo& InWorldInfo);` — Helper function to find a postfix for a world (e.g. "Client 0", "Server" etc.)
- L76 _private member_ `FBaseTimingTrack& TimingTrack;` — Outer timing track
- L79 _private member_ `uint64 ObjectId;` — The object ID for this track
- L82 _private member_ `FGameplayTrack* Parent;` — Parent track
- L85 _private member_ `TArray<FGameplayTrack*> Children;` — Our child tracks
- L88 _private member_ `uint32 Indent;` — Our indent when drawn in a tree

#### class `TGameplayTrackMixin`  
`template <class Base> class TGameplayTrackMixin : public Base`  
_L92-111_
- inherits: `Base`
- L97 _public function_ `TGameplayTrackMixin(uint64 InObjectId, const FText& InName) : Base(InName.ToString()) , GameplayTrack(*this, InObjectId)`
- L104 _public function_ `FGameplayTrack& GetGameplayTrack()` — Access the underlying gameplay track
- L107 _public function_ `const FGameplayTrack& GetGameplayTrack() const` — Access the underlying gameplay track
- L110 _private member_ `FGameplayTrack GameplayTrack;`

#### class `FGameplayTimingEventsTrack`  
`class FGameplayTimingEventsTrack : public TGameplayTrackMixin<FTimingEventsTrack>`  
_L114-132_
- inherits: `TGameplayTrackMixin<FTimingEventsTrack>`
- desc: Common base class for timing-event tracks
- L119 _public function_ `FGameplayTimingEventsTrack(const FGameplaySharedData& InGameplaySharedData, uint64 InObjectId, const FText& InName) : TGameplayTrackMixin<FTimingEventsTrack>(InObjectId, InName) , GameplaySharedData(InGameplaySharedData)`
- L124 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L127 _public function_ `virtual void GetVariantsAtTime(double InTime, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const` — Get all variants at the specified time/frame
- L128 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const;`
- L131 _protected member_ `const FGameplaySharedData& GameplaySharedData;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GameplayTrackConstants`
- L9 _variable_ `constexpr float IndentSize = 12.0f;` (scope `GameplayTrackConstants`)
- L15 _namespace_ `namespace TraceServices`
- L21 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/InertializationsTrack.h` (Private)


#### class `RewindDebugger::FInertializationTrack`  
`class FInertializationTrack : public FRewindDebuggerTrack`  
_L14-42_
- inherits: `FRewindDebuggerTrack`
- L18 _public prototype_ `FInertializationTrack(uint64 InObjectId, int32 NodeId, const FText& Name);`
- L19 _public function_ `int32 GetNodeId() const`
- L22 _private prototype_ `virtual bool UpdateInternal() override;`
- L23 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L24 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L26 _private function_ `virtual FName GetNameInternal() const override`
- L27 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L28 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L29 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L30 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L32 _private prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;`
- L34 _private member_ `int32 NodeId = INDEX_NONE;`
- L36 _private member_ `FSlateIcon Icon;`
- L37 _private member_ `FText CurveName;`
- L38 _private member_ `uint64 ObjectId = INDEX_NONE;`
- L40 _private member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;`
- L41 _private member_ `mutable int CurvesUpdateRequested = 0;`

#### class `RewindDebugger::FInertializationsTrack`  
`class FInertializationsTrack : public FRewindDebuggerTrack`  
_L44-63_
- inherits: `FRewindDebuggerTrack`
- L47 _public prototype_ `FInertializationsTrack(uint64 InObjectId);`
- L50 _private prototype_ `virtual bool UpdateInternal() override;`
- L51 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L52 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L54 _private function_ `virtual FName GetNameInternal() const override`
- L55 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L56 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L58 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L60 _private member_ `FSlateIcon Icon;`
- L61 _private member_ `uint64 ObjectId = INDEX_NONE;`
- L62 _private member_ `TArray<TSharedPtr<FInertializationTrack>> Children;`

#### class `RewindDebugger::FInertializationsTrackCreator`  
`class FInertializationsTrackCreator : public IRewindDebuggerTrackCreator`  
_L66-74_
- inherits: `IRewindDebuggerTrackCreator`
- L69 _public prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L70 _public prototype_ `virtual FName GetNameInternal() const override;`
- L71 _public prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L72 _public prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L73 _public prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/MontageTrack.h` (Private)


#### class `FMontageSeries`  
`class FMontageSeries : public FGameplayGraphSeries`  
_L12-25_
- inherits: `FGameplayGraphSeries`
- L23 _public member_ `uint64 MontageId;`
- L24 _public member_ `ESeriesType Type;`

#### enum `FMontageSeries::ESeriesType`  
`enum class ESeriesType : uint32`  
_L15-21_
- L17 _public enumerator_ `Weight`
- L18 _public enumerator_ `Position`
- L20 _public enumerator_ `Count`

#### class `FMontageTrack`  
`class FMontageTrack : public FGameplayGraphTrack`  
_L27-56_
- inherits: `FGameplayGraphTrack`
- L32 _public prototype_ `FMontageTrack(const FAnimationSharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L34 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L35 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L36 _public prototype_ `virtual void AddAllSeries() override;`
- L37 _public prototype_ `virtual bool UpdateSeriesBounds(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport) override;`
- L38 _public prototype_ `virtual void UpdateSeries(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport) override;`
- L39 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L43 _private prototype_ `void FindMontageMessage(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FAnimMontageMessage&)> InFoundPredicate) const;` — Helper function used to find a montage message
- L47 _private prototype_ `template<typename ProjectionType> bool UpdateSeriesBoundsHelper(FMontageSeries& InSeries, const FTimingTrackViewport & InViewport, ProjectionType Projection);` — Helper function for series bounds update
- L51 _private prototype_ `template<typename ProjectionType> void UpdateSeriesHelper(FMontageSeries& InSeries, const FTimingTrackViewport & InViewport, ProjectionType Projection);` — Helper function for series update
- L55 _private member_ `const FAnimationSharedData& SharedData;` — The shared data

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/MontagesTrack.h` (Private)


#### class `RewindDebugger::FMontageTrack`  
`class FMontageTrack : public FRewindDebuggerTrack`  
_L14-54_
- inherits: `FRewindDebuggerTrack`
- L24 _public prototype_ `FMontageTrack(uint64 InObjectId, uint64 AssetId, ECurveType CurveType = ECurveType::BlendWeight);`
- L26 _public function_ `uint64 GetAssetId() const`
- L29 _private prototype_ `virtual bool UpdateInternal() override;`
- L30 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L31 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L32 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L33 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L35 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L36 _private function_ `virtual FName GetNameInternal() const override`
- L37 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L38 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L40 _private prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;`
- L42 _private member_ `uint64 AssetId;`
- L44 _private member_ `ECurveType CurveType;`
- L46 _private member_ `FSlateIcon Icon;`
- L47 _private member_ `FText CurveName;`
- L48 _private member_ `uint64 ObjectId;`
- L50 _private member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;`
- L51 _private member_ `mutable int CurvesUpdateRequested = 0;`
- L53 _private member_ `TArray<TSharedPtr<FMontageTrack>> Children;`

#### enum `RewindDebugger::FMontageTrack::ECurveType`  
`enum class ECurveType`  
_L17-22_
- L19 _public enumerator_ `BlendWeight`
- L20 _public enumerator_ `DesiredWeight`
- L21 _public enumerator_ `Position`

#### class `RewindDebugger::FMontagesTrack`  
`class FMontagesTrack : public FRewindDebuggerTrack`  
_L56-75_
- inherits: `FRewindDebuggerTrack`
- L59 _public prototype_ `FMontagesTrack(uint64 InObjectId);`
- L62 _private prototype_ `virtual bool UpdateInternal() override;`
- L63 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L64 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L66 _private prototype_ `virtual FName GetNameInternal() const override;`
- L67 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L68 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L70 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L72 _private member_ `FSlateIcon Icon;`
- L73 _private member_ `uint64 ObjectId;`
- L74 _private member_ `TArray<TSharedPtr<FMontageTrack>> Children;`

#### class `RewindDebugger::FMontagesTrackCreator`  
`class FMontagesTrackCreator : public IRewindDebuggerTrackCreator`  
_L78-86_
- inherits: `IRewindDebuggerTrackCreator`
- L81 _public prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L82 _public prototype_ `virtual FName GetNameInternal() const override;`
- L83 _public prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L84 _public prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L85 _public prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/NotifiesTrack.h` (Private)


#### class `RewindDebugger::FNotifyTrack`  
`class FNotifyTrack : public FRewindDebuggerTrack`  
_L13-72_
- inherits: `FRewindDebuggerTrack`
- L44 _public prototype_ `FNotifyTrack(uint64 InObjectId, const FNotifyTrackId& TrackId);`
- L45 _public function_ `const FNotifyTrackId& GetNotifyTrackId() const`
- L47 _private prototype_ `virtual bool UpdateInternal() override;`
- L48 _private prototype_ `TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L49 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L50 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L51 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L52 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L54 _private prototype_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetEventData() const;`
- L56 _private member_ `mutable TSharedPtr<SEventTimelineView::FTimelineEventData> EventData;`
- L57 _private member_ `mutable int EventUpdateRequested = 0;`
- L59 _private member_ `uint64 ObjectId;`
- L60 _private member_ `FNotifyTrackId NotifyTrackId;`
- L61 _private member_ `FSlateIcon Icon;`
- L62 _private member_ `FText TrackName;`
- L71 _private member_ `EFilterType FilterType = EFilterType::Notify;`

#### enum `RewindDebugger::FNotifyTrack::ENotifyTrackType`  
`enum class ENotifyTrackType`  
_L16-21_
- L18 _public enumerator_ `SyncMarker`
- L19 _public enumerator_ `Notify`
- L20 _public enumerator_ `NotifyState`

#### struct `RewindDebugger::FNotifyTrack::FNotifyTrackId`  
`struct FNotifyTrackId`  
_L23-42_
- L25 _public member_ `uint64 NameId;`
- L26 _public member_ `ENotifyTrackType Type;`
- L28 _public function_ `bool operator == (const FNotifyTrackId& Other) const`
- L33 _public function_ `bool operator <(const FNotifyTrack::FNotifyTrackId& Other) const`

#### enum `RewindDebugger::FNotifyTrack::EFilterType`  
`enum class EFilterType`  
_L64-69_
- L66 _public enumerator_ `Notify`
- L67 _public enumerator_ `NotifyState`
- L68 _public enumerator_ `SyncMarker`

#### class `RewindDebugger::FNotifiesTrack`  
`class FNotifiesTrack : public FRewindDebuggerTrack`  
_L77-96_
- inherits: `FRewindDebuggerTrack`
- desc: Parent track of all the curves
- L80 _public prototype_ `FNotifiesTrack(uint64 InObjectId);`
- L83 _private prototype_ `virtual bool UpdateInternal() override;`
- L84 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L86 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L87 _private function_ `virtual FName GetNameInternal() const override`
- L88 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L89 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L90 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L92 _private member_ `FSlateIcon Icon;`
- L93 _private member_ `uint64 ObjectId;`
- L95 _private member_ `TArray<TSharedPtr<FNotifyTrack>> Children;`

#### class `RewindDebugger::FNotifiesTrackCreator`  
`class FNotifiesTrackCreator : public IRewindDebuggerTrackCreator`  
_L99-107_
- inherits: `IRewindDebuggerTrackCreator`
- L102 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L103 _private prototype_ `virtual FName GetNameInternal() const override;`
- L104 _private prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L105 _private prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L106 _private prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/NumericPropertyTrack.h` (Private)


#### class `RewindDebugger::FNumericPropertyTrack`  
`class FNumericPropertyTrack : public FPropertyTrack`  
_L13-37_
- inherits: `FPropertyTrack`
- desc: Track that displays a object's numeric property value overtime
- L20 _public prototype_ `FNumericPropertyTrack(uint64 InObjectId, const TSharedPtr<FObjectPropertyInfo> & InObjectProperty, const TSharedPtr<FPropertyTrack> & InParentTrack);` — Constructor
- L23 _public prototype_ `TSharedPtr<SCurveTimelineView::FTimelineCurveData> GetCurveData() const;` — @return Property's timeline view curve data
- L28 _protected prototype_ `virtual bool UpdateInternal() override;` — Begin IRewindDebuggerTrack interface
- L29 _protected prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L33 _protected member_ `mutable TSharedPtr<SCurveTimelineView::FTimelineCurveData> CurveData;` — Curve data used to display value of property overtime
- L36 _protected member_ `mutable int CurvesUpdateRequested = 0;` — Keeps track of how many times the curve view has been requested to be drawn/computed

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/ObjectEventsTrack.h` (Private)


#### class `FObjectEventsTrack`  
`class FObjectEventsTrack : public FGameplayTimingEventsTrack`  
_L14-37_
- inherits: `FGameplayTimingEventsTrack`
- L19 _public prototype_ `FObjectEventsTrack(const FGameplaySharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L21 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L22 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L23 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L24 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L25 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L26 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L30 _private prototype_ `void FindObjectEvent(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FObjectEventMessage&)> InFoundPredicate) const;` — Helper function used to find an object event
- L33 _private prototype_ `FText MakeTrackName(const FGameplaySharedData& InSharedData, uint64 InObjectID, const TCHAR* InName) const;` — Helper function to build the track's name
- L36 _private member_ `const FGameplaySharedData& SharedData;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/ObjectPropertiesTrack.h` (Private)


#### class `FObjectPropertiesTrack`  
`class FObjectPropertiesTrack : public FGameplayTimingEventsTrack`  
_L14-36_
- inherits: `FGameplayTimingEventsTrack`
- L19 _public prototype_ `FObjectPropertiesTrack(const FGameplaySharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L21 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L22 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L23 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L24 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L25 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L29 _private prototype_ `void FindObjectEvent(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FObjectPropertiesMessage&)> InFoundPredicate) const;` — Helper function used to find an object event
- L32 _private prototype_ `FText MakeTrackName(const FGameplaySharedData& InSharedData, uint64 InObjectID, const TCHAR* InName) const;` — Helper function to build the track's name
- L35 _private member_ `const FGameplaySharedData& SharedData;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/PoseWatchTrack.h` (Private)


#### class `RewindDebugger::FPoseWatchCurveTrack`  
`class FPoseWatchCurveTrack : public FAnimCurveTrack`  
_L20-33_
- inherits: `FAnimCurveTrack`
- desc: Sub Track for a single curve in a pose watch
- L23 _public prototype_ `FPoseWatchCurveTrack(uint64 InObjectId, uint32 InCurveId, uint64 InPoseWatchTrackId);`
- L25 _public function_ `uint64 GetPoseWatchTrackId() const`
- L28 _private prototype_ `virtual void UpdateCurvePointsInternal() override;`
- L29 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L30 _private function_ `virtual FName GetNameInternal() const override`
- L32 _private member_ `uint64 PostWatchTrackId;`

#### class `RewindDebugger::FPoseWatchTrack`  
`class FPoseWatchTrack : public FRewindDebuggerTrack`  
_L35-62_
- inherits: `FRewindDebuggerTrack`
- L38 _public prototype_ `FPoseWatchTrack(uint64 InObjectId, const uint64 TrackId, FColor InColor, uint32 InNameId);`
- L39 _public function_ `uint64 GetPoseWatchTrackId() const`
- L42 _private prototype_ `virtual bool UpdateInternal() override;`
- L43 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L45 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L46 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L47 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L48 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L50 _private prototype_ `TSharedPtr<SSegmentedTimelineView::FSegmentData> GetSegmentData() const;`
- L52 _private member_ `uint64 ObjectId;`
- L53 _private member_ `uint64 PoseWatchTrackId;`
- L54 _private member_ `FSlateIcon Icon;`
- L55 _private member_ `FText TrackName;`
- L56 _private member_ `FColor Color;`
- L57 _private member_ `uint32 NameId;`
- L59 _private member_ `TSharedPtr<SSegmentedTimelineView::FSegmentData> EnabledSegments;`
- L61 _private member_ `TArray<TSharedPtr<FPoseWatchCurveTrack>> Children;`

#### class `RewindDebugger::FPoseWatchesTrack`  
`class FPoseWatchesTrack : public FRewindDebuggerTrack`  
_L66-84_
- inherits: `FRewindDebuggerTrack`
- desc: Parent track of all the pose watches
- L69 _public prototype_ `FPoseWatchesTrack(uint64 InObjectId);`
- L72 _private prototype_ `virtual bool UpdateInternal() override;`
- L73 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L75 _private function_ `virtual FName GetNameInternal() const override`
- L76 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L77 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L78 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L80 _private member_ `FSlateIcon Icon;`
- L81 _private member_ `uint64 ObjectId;`
- L83 _private member_ `TArray<TSharedPtr<FPoseWatchTrack>> Children;`

#### class `RewindDebugger::FPoseWatchesTrackCreator`  
`class FPoseWatchesTrackCreator : public IRewindDebuggerTrackCreator`  
_L87-95_
- inherits: `IRewindDebuggerTrackCreator`
- L90 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L91 _private prototype_ `virtual FName GetNameInternal() const override;`
- L92 _private prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L93 _private prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L94 _private prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/PropertiesTrack.h` (Private)


#### class `RewindDebugger::FPropertiesTrack`  
`class FPropertiesTrack : public FRewindDebuggerTrack, public TSharedFromThis<FPropertiesTrack>`  
_L18-68_
- inherits: `FRewindDebuggerTrack,TSharedFromThis<FPropertiesTrack>`
- desc: Root track used to store an object's traced properties information and property tracks
- L23 _public prototype_ `FPropertiesTrack(uint64 InObjectId);` — Constructor
- L26 _public prototype_ `void Initialize();` — Initialize properties track
- L29 _public prototype_ `int64 GetTotalPropertyCountAtStart() const;` — @return Total property count for traced object at the start of recording
- L32 _public prototype_ `void AddTrackedProperty(uint32 InPropertyNameId);` — Add a property from the Rewind Debugger timeline
- L35 _public prototype_ `void RemoveTrackedProperty(uint32 InPropertyNameId);` — Remove a property from the Rewind Debugger timeline
- L39 _private prototype_ `virtual bool UpdateInternal() override;` — Begin IRewindDebuggerTrack interface
- L40 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L41 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L42 _private prototype_ `virtual FName GetNameInternal() const override;`
- L43 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L44 _private prototype_ `virtual uint64 GetObjectIdInternal() const override;`
- L45 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L49 _private prototype_ `void OnPropertyWatched(uint64 InObjectId, uint32 InPropertyNameId);` — Event handler used to create tracks for watched properties
- L52 _private prototype_ `void OnPropertyUnwatched(uint64 InObjectId, uint32 InPropertyNameId);` — Event handler used to delete tracks for an unwatched properties
- L55 _private member_ `FSlateIcon Icon;` — Used to determine track icon
- L58 _private member_ `uint64 ObjectId;` — Id for traced/target object
- L61 _private member_ `TMap<uint32, TSharedPtr<FPropertyTrack>> ChildrenTracks;` — List of watch property tracks to display on Rewind Debugger timeline
- L64 _private member_ `bool bAreWatchedPropertiesDirty;` — Used to determine if watched tracks have been externally modified
- L67 _private member_ `int64 TotalPropertyCountAtStart;` — Count of recorded properties for traced object at the start of recording

#### class `RewindDebugger::FPropertiesTrackCreator`  
`class FPropertiesTrackCreator : public IRewindDebuggerTrackCreator`  
_L74-83_
- inherits: `IRewindDebuggerTrackCreator`
- desc: Used to automatically create an FPropertiesTrack in Rewind Debugger
- L77 _private prototype_ `virtual FName GetTargetTypeNameInternal() const override;` — Begin IRewindDebuggerTrackCreator interface
- L78 _private prototype_ `virtual FName GetNameInternal() const override;`
- L79 _private prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L80 _private prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L81 _private prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/PropertyHelpers.h` (Private)


#### class `FObjectPropertyHelpers`  
`class FObjectPropertyHelpers`  
_L18-47_
- desc: Helper class when working with traced object properties
- L23 _public prototype_ `static bool IsBoolProperty(const FString & InPropertyValueString, const FString & InPropertyTypeString);` — @return True if traced property was a FBoolProperty.
- L26 _public prototype_ `static FName GetPropertyDisplayName(const FObjectPropertyValue & InProperty, const IGameplayProvider& InGameplayProvider);` — @return Get formatted property display name
- L29 _public prototype_ `static FSlateIcon GetPropertyIcon(const FObjectPropertyValue & InProperty);` — @return Icon associated with the given property's type
- L32 _public prototype_ `static FLinearColor GetPropertyColor(const FObjectPropertyValue & InProperty);` — @return Color associated with the given property's type
- L37 _public prototype_ `static TSharedRef<FVariantTreeNode> GetVariantNodeFromProperty(uint32 InPropertyIndex, const IGameplayProvider & InGameplayProvider, const TConstArrayView<FObjectPropertyValue> & InStorage);` — @return Variant display node from traced property @note Assumes an FAnalysisSessionReadScope has been created before accessing data in InStorage variable.
- L40 _public prototype_ `static TPair<const FObjectPropertyValue *, uint32> ReadObjectPropertyValueCached(RewindDebugger::FObjectPropertyInfo & InProperty, uint64 InObjectId, const IGameplayProvider & InGameplayProvider, const FObjectPropertiesMessage& InMessage);` — @return Read track's property traced value
- L46 _public prototype_ `static bool FindPropertyValueFromNameId(uint32 InPropertyNameId, uint64 InObjectId, const TraceServices::IAnalysisSession & InSession, double InStartTime, double InEndTime, RewindDebugger::FObjectPropertyInfo & InOutProperty);` — Find object property value given a named id. @return True if property was found, false otherwise.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/PropertyTrack.h` (Private)


#### struct `RewindDebugger::FObjectPropertyInfo`  
`struct FObjectPropertyInfo`  
_L20-46_
- desc: Container item that stores information for a watched traced object's variable
- L23 _public function_ `FObjectPropertyInfo() : Name(NAME_None), Property(), CachedId(INDEX_NONE)` — Default Constructor
- L31 _public function_ `FObjectPropertyInfo(const FName & Name, const FObjectPropertyValue& TracedProperty, int64 CachedId = INDEX_NONE) : Name(Name), Property(TracedProperty), CachedId(CachedId)` — Constructor
- L39 _public member_ `FName Name = NAME_None;` — Traced variable name
- L42 _public member_ `FObjectPropertyValue Property;` — Traced variable data. Used to store identifiers.
- L45 _public member_ `int64 CachedId = INDEX_NONE;` — Previously found storage index

#### class `RewindDebugger::FPropertyTrack`  
`class FPropertyTrack : public FRewindDebuggerTrack, public TSharedFromThis<FPropertyTrack>`  
_L54-141_
- inherits: `FRewindDebuggerTrack,TSharedFromThis<FPropertyTrack>`
- desc: Track that displays a traced object's property or traced value over time
- L61 _public prototype_ `FPropertyTrack(uint64 InObjectId, const TSharedPtr<FObjectPropertyInfo> & InObjectProperty, const TSharedPtr<FPropertyTrack> & InParentTrack);` — Constructor
- L64 _public prototype_ `virtual void BuildContextMenu(FToolMenuSection& InMenuSection) override;` — Begin IRewindDebuggerTrack interface
- L68 _public prototype_ `const TSharedPtr<FObjectPropertyInfo> & GetObjectProperty() const;` — @return Internal data item for traced variable
- L71 _public prototype_ `const FName & GetPropertyName() const;` — @return Property name identifier
- L74 _public prototype_ `TConstArrayView<TSharedPtr<FPropertyTrack>> GetChildren() const;` — @return Children property tracks
- L77 _public prototype_ `const TSharedPtr<FPropertyTrack> & GetParent() const;` — @return Parent track
- L83 _public prototype_ `bool AddUniqueChild(const TSharedPtr<FPropertyTrack> & InTrack);` — Add a property track as a child @return True if property was successfully added as a child.
- L89 _public prototype_ `bool RemoveChild(const TSharedPtr<FPropertyTrack> & InTrack);` — Remove a child property track @return True if property was successfully removed from child container.
- L95 _public prototype_ `void SetParent(const TSharedPtr<FPropertyTrack> & InParent);` — Update the track's parent. @note This procedure does not validate if the parent - child relationship is valid.
- L98 _public typedef_ `typedef TFunctionRef<void(const FObjectPropertyValue & , uint32 , const FObjectPropertiesMessage & )> PropertyAtFrameCallback;` — Callback signature for reading a property at a given frame
- L105 _public prototype_ `bool ReadObjectPropertyValueAtFrame(const TraceServices::FFrame & InFrame, const IGameplayProvider& InGameplayProvider, PropertyAtFrameCallback InCallback) const;` — Read value for internal property at a given frame. @note Assumes function is called within a TraceServices::IAnalysisSession read access scope. @return True if property value at given frame was found.
- L108 _public typedef_ `typedef TFunctionRef<void(const FObjectPropertyValue & , uint32 , const FObjectPropertiesMessage& , const IGameplayProvider::ObjectPropertiesTimeline & , double , double )> PropertyOverTimeCallback;` — Callback signature for reading a property at over a time range
- L111 _public prototype_ `void ReadObjectPropertyValueOverTime(double InStartTime, double InEndTime, PropertyOverTimeCallback InCallback) const;` — Read value for internal property over a range of time.
- L114 _public prototype_ `static TSharedPtr<FPropertyTrack> Create(uint64 InObjectId, const TSharedPtr<FObjectPropertyInfo> & InObjectProperty, const TSharedPtr<FPropertyTrack> & InParentTrack);` — @return Specialized Property Track, if any, for given object property.
- L118 _protected prototype_ `virtual bool UpdateInternal() override;` — Begin IRewindDebuggerTrack interface
- L119 _protected prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L120 _protected prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L121 _protected prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L122 _protected prototype_ `virtual FName GetNameInternal() const override;`
- L123 _protected prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L124 _protected prototype_ `virtual uint64 GetObjectIdInternal() const override;`
- L128 _protected member_ `FSlateIcon Icon;` — Used to determine track icon
- L131 _protected member_ `uint64 ObjectId;` — Id for traced/target object
- L134 _protected member_ `TSharedPtr<FObjectPropertyInfo> ObjectProperty;` — Used to store traced variable information
- L137 _protected member_ `TSharedPtr<FPropertyTrack> Parent;` — Parent property track
- L140 _protected member_ `TArray<TSharedPtr<FPropertyTrack>> Children;` — Child properties tracks. Used if property is a struct, vector, etc.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace RewindDebugger`
- L48 _macro_ `#define BASE_PROPERTY_TRACK() \`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/PropertyWatchManager.h` (Private)


#### class `FPropertyWatchManager`  
`class FPropertyWatchManager`  
_L14-79_
- desc: Used to keep track of traced variables that are being watched.
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyWatched, uint64 , uint32 ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyUnwatched, uint64 , uint32 ) FPropertyWatchManager();`
- L25 _public prototype_ `~FPropertyWatchManager();` — Destructor
- L31 _public prototype_ `bool WatchProperty(uint64 InObjectId, uint32 InPropertyNameId);` — Start watching a property @return Whether property was started to being watched. If property is already being watched this will return false.
- L37 _public prototype_ `bool UnwatchProperty(uint64 InObjectId, uint32 InPropertyNameId);` — Stop watching a property @return Whether property was stopped being watched. If property is already not watched this will return false.
- L40 _public prototype_ `int32 GetWatchedPropertiesNum(uint64 InObjectId) const;` — @return The total number of watched properties for a specific object
- L43 _public prototype_ `TConstArrayView<uint32> GetWatchedProperties(uint64 InObjectId) const;` — @return A view of all the watched properties for a specific object
- L46 _public prototype_ `void ClearWatchedProperties(uint64 InObjetId);` — Stop watching all the registered properties of a given object
- L49 _public prototype_ `void ClearAllWatchedProperties();` — Stop watching all registered properties
- L52 _public prototype_ `FOnPropertyWatched & OnPropertyWatched();` — @return Delete that broadcast when any property has started to be watched
- L55 _public prototype_ `FOnPropertyUnwatched & OnPropertyUnwatched();` — @return Delete that broadcasts when any property has ceased to be watched
- L58 _public prototype_ `static void Initialize();` — Create singleton instance
- L61 _public prototype_ `static void Shutdown();` — Destroy singleton instance
- L64 _public prototype_ `static FPropertyWatchManager* Instance();` — @return Current PropertyWatchManager singleton instance
- L69 _protected member_ `TMap<uint64, TArray<uint32>> WatchedProperties;` — ObjectId -> Object's watched properties
- L72 _protected member_ `FOnPropertyWatched OnPropertyWatchedDelegate;` — Delete variable to broadcast when any property has started to be watched
- L75 _protected member_ `FOnPropertyUnwatched OnPropertyUnwatchedDelegate;` — Delete variable to broadcast when any property has ceased to be watched
- L78 _protected member_ `static FPropertyWatchManager* InternalInstance;` — Singleton instance

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace RewindDebugger`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyWatched, uint64 , uint32 ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyUnwatched, uint64 , uint32 ) FPropertyWatchManager();`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyUnwatched, uint64 , uint32 ) FPropertyWatchManager();`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SAnimGraphSchematicView.h` (Private)


#### class `SAnimGraphSchematicView`  
`class SAnimGraphSchematicView : public IRewindDebuggerView`  
_L25-118_
- inherits: `IRewindDebuggerView`
- L27 _private function_ `SLATE_BEGIN_ARGS(SAnimGraphSchematicView)`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, uint64 InAnimInstanceId, double InTimeMarker, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L32 _public function_ `uint64 GetAnimInstanceId() const`
- L34 _public prototype_ `virtual void SetTimeMarker(double InTimeMarker) override;`
- L35 _public prototype_ `virtual FName GetName() const override;`
- L36 _public function_ `virtual uint64 GetObjectId() const override`
- L40 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedRef<FAnimGraphSchematicNode> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row widget for an item
- L43 _private prototype_ `void HandleGetChildren(TSharedRef<FAnimGraphSchematicNode> InItem, TArray<TSharedRef<FAnimGraphSchematicNode>>& OutChildren);` — Get the children of an item
- L46 _private prototype_ `TSharedRef<ITableRow> HandleGeneratePropertyRow(TSharedRef<FAnimGraphSchematicPropertyNode> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row widget for a property item
- L49 _private prototype_ `void HandleGetPropertyChildren(TSharedRef<FAnimGraphSchematicPropertyNode> InItem, TArray<TSharedRef<FAnimGraphSchematicPropertyNode>>& OutChildren);` — Get the children of a property item
- L52 _private prototype_ `void HandleTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);` — Handle the time marker being scrubbed
- L55 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FAnimGraphSchematicNode> InNode, ESelectInfo::Type InSelectInfo);` — Handle tree selection changing
- L58 _private prototype_ `void RefreshNodes();` — Refresh the unfiltered and filtered nodes
- L61 _private prototype_ `EAnimGraphSchematicFilterState RefreshFilter_Helper(const TSharedRef<FAnimGraphSchematicNode>& InNode);` — Recursive helper to filter tree
- L64 _private prototype_ `void RefreshColumns();` — Refresh the displayed columns
- L67 _private prototype_ `void RefreshFilter();` — Refresh the filtered nodes
- L70 _private prototype_ `void RefreshDetails(const TArray<TSharedRef<FAnimGraphSchematicNode>>& InNodes);` — Refresh the details panel
- L73 _private prototype_ `TSharedRef<SWidget> HandleGetViewMenuContent();` — Handle getting content for the view menu
- L76 _private prototype_ `FSlateColor GetViewButtonForegroundColor() const;` — Handle inverting the color of the button text when hovered
- L79 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;`
- L81 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L83 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L85 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L87 _private member_ `TSharedPtr<STreeView<TSharedRef<FAnimGraphSchematicNode>>> TreeView;`
- L89 _private member_ `TSharedPtr<STreeView<TSharedRef<FAnimGraphSchematicPropertyNode>>> PropertyTreeView;`
- L91 _private member_ `TSharedPtr<SComboButton> ViewButton;`
- L93 _private member_ `TWeakPtr<SVerticalBox> DetailsContentBox;`
- L95 _private member_ `TArray<TSharedRef<FAnimGraphSchematicNode>> UnfilteredNodes;`
- L97 _private member_ `TArray<TSharedRef<FAnimGraphSchematicNode>> FilteredNodes;`
- L99 _private member_ `TArray<TSharedRef<FAnimGraphSchematicNode>> LinearNodes;`
- L101 _private member_ `TArray<TSharedRef<FAnimGraphSchematicPropertyNode>> PropertyNodes;`
- L103 _private member_ `TSet<int32> SelectedNodeIds;`
- L111 _private member_ `TMap<FName, FColumnState> Columns;`
- L113 _private member_ `FText FilterText;`
- L115 _private member_ `double TimeMarker;`
- L117 _private member_ `uint64 AnimInstanceId;`

#### struct `SAnimGraphSchematicView::FColumnState`  
`struct FColumnState`  
_L105-109_
- L107 _public member_ `int32 SortIndex = 0;`
- L108 _public member_ `bool bEnabled = false;`

#### class `FAnimGraphSchematicTrack`  
`class FAnimGraphSchematicTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L120-140_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L124 _public function_ `FAnimGraphSchematicTrack(uint64 InObjectId) : AnimInstanceId(InObjectId)`
- L130 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L131 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L132 _private prototype_ `virtual FName GetNameInternal() const override;`
- L133 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L134 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L135 _private prototype_ `virtual bool UpdateInternal() override;`
- L137 _private member_ `TWeakPtr<SAnimGraphSchematicView> View;`
- L138 _private member_ `FSlateIcon Icon;`
- L139 _private member_ `uint64 AnimInstanceId;`

#### class `FAnimGraphSchematicTrackCreator`  
`class FAnimGraphSchematicTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L143-151_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L146 _public prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L147 _public prototype_ `virtual FName GetNameInternal() const override;`
- L148 _public prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L149 _public prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L150 _public prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Insights` (scope `UE`)
- L13 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Insights` (scope `UE`)
- L14 _namespace_ `namespace Timing` (scope `UE::Insights`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SAnimationCurvesView.h` (Private)


#### class `SAnimationCurvesView`  
`class SAnimationCurvesView : public SPropertiesDebugViewBase`  
_L10-30_
- inherits: `SPropertiesDebugViewBase`
- L13 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L16 _public function_ `void SetCurveFilter(uint32 InCurveFilter)`
- L22 _public function_ `void ClearCurveFilter()`
- L28 _private member_ `uint32 CurveFilter = 0;`
- L29 _private member_ `bool bCurveFilterSet = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SBlendWeightsView.h` (Private)


#### class `SBlendWeightsView`  
`class SBlendWeightsView : public SPropertiesDebugViewBase`  
_L10-32_
- inherits: `SPropertiesDebugViewBase`
- L13 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L16 _public function_ `void SetAssetFilter(uint64 InAssetIdFilter, uint32 InNodeIdFilter)`
- L23 _public function_ `void ClearAssetFilter()`
- L29 _private member_ `uint64 AssetIdFilter = 0;`
- L30 _private member_ `uint32 NodeIdFilter = 0;`
- L31 _private member_ `bool bAssetFilterSet = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SGameplayInsightsTransportControls.h` (Private)


#### class `SGameplayInsightsTransportControls`  
`class SGameplayInsightsTransportControls : public SCompoundWidget`  
_L17-67_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGameplayInsightsTransportControls)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FGameplaySharedData& InSharedData);`
- L27 _private prototype_ `FReply OnClick_Forward_Step();`
- L29 _private prototype_ `FReply OnClick_Forward_End();`
- L31 _private prototype_ `FReply OnClick_Backward_Step();`
- L33 _private prototype_ `FReply OnClick_Backward_End();`
- L35 _private prototype_ `FReply OnClick_Forward();`
- L37 _private prototype_ `FReply OnClick_Backward();`
- L39 _private prototype_ `FReply OnClick_ToggleLooping();`
- L41 _private prototype_ `bool GetLooping() const;`
- L43 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L45 _private prototype_ `void SetTimeMarker(double InTime, bool bInScroll);`
- L47 _private prototype_ `void HandleTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);`
- L49 _private prototype_ `void HandleSelectionRangeChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InStartTime, double InEndTime);`
- L52 _private member_ `FGameplaySharedData* SharedData;`
- L54 _private member_ `double PlayRate;`
- L56 _private member_ `bool bPlaying;`
- L58 _private member_ `bool bReverse;`
- L60 _private member_ `bool bLooping;`
- L62 _private member_ `bool bSettingMarker;`
- L64 _private member_ `double SelectionStartTime;`
- L65 _private member_ `double SelectionEndTime;`
- L66 _private member_ `bool bSelectionRangeValid;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Insights` (scope `UE`)
- L15 _namespace_ `namespace Timing` (scope `UE::Insights`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SGameplayTrackTree.h` (Private)


#### class `SGameplayTrackTree`  
`class SGameplayTrackTree : public SCompoundWidget`  
_L16-61_
- inherits: `SCompoundWidget`
- desc: A widget representing all the gameplay tracks
- L19 _public function_ `SLATE_BEGIN_ARGS(SGameplayTrackTree)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FGameplaySharedData& InSharedData);`
- L25 _public prototype_ `void CacheVisibility();`
- L29 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedRef<FGameplayTrackTreeEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row for the tree
- L32 _private prototype_ `void OnGetChildren(TSharedRef<FGameplayTrackTreeEntry> InItem, TArray<TSharedRef<FGameplayTrackTreeEntry>>& OutChildren);` — Get the children of an item
- L35 _private prototype_ `void RefreshFilter();` — Refresh the tree as the filter has changed
- L38 _private prototype_ `EGameplayTrackFilterState RefreshFilter_Helper(const TSharedRef<FGameplayTrackTreeEntry>& InTreeEntry);` — Recursive helper to filter tree
- L41 _private prototype_ `void HandleTracksChanged();` — Handle the tracks changing under us
- L45 _private member_ `FGameplaySharedData* SharedData;` — Shared data source
- L48 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search widget
- L51 _private member_ `TSharedPtr<STreeView<TSharedRef<FGameplayTrackTreeEntry>>> TreeView;` — The list view widget
- L54 _private member_ `FText SearchText;` — Text we are searching for
- L57 _private member_ `TArray<TSharedRef<FGameplayTrackTreeEntry>> FilteredTracks;` — Filtered list of tracks
- L60 _private member_ `TArray<TSharedRef<FGameplayTrackTreeEntry>> RootEntries;` — Unfiltered list of tracks

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SInertializationDetailsView.h` (Private)


#### class `SInertializationDetailsView`  
`class SInertializationDetailsView : public SPropertiesDebugViewBase`  
_L10-30_
- inherits: `SPropertiesDebugViewBase`
- L13 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L16 _public function_ `void SetFilter(uint32 InNodeIdFilter)`
- L22 _public function_ `void ClearFilter()`
- L28 _private member_ `uint32 NodeIdFilter = 0;`
- L29 _private member_ `bool bFilterSet = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SMontageView.h` (Private)


#### class `SMontageView`  
`class SMontageView : public SPropertiesDebugViewBase`  
_L10-30_
- inherits: `SPropertiesDebugViewBase`
- L13 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L16 _public function_ `void SetAssetFilter(uint64 InAssetIdFilter)`
- L22 _public function_ `void ClearAssetFilter()`
- L28 _private member_ `uint64 AssetIdFilter = 0;`
- L29 _private member_ `bool bAssetFilterSet = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SNotifiesView.h` (Private)


#### class `SNotifiesView`  
`class SNotifiesView : public SPropertiesDebugViewBase`  
_L10-24_
- inherits: `SPropertiesDebugViewBase`
- L13 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L16 _public function_ `void SetNotifyFilter(uint64 NameId)`
- L22 _private member_ `uint64 FilterNotifyNameId = 0;`
- L23 _private member_ `bool bFilterIsSet = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SObjectPropertiesView.h` (Private)


#### class `SObjectPropertiesView`  
`class SObjectPropertiesView : public SPropertiesDebugViewBase`  
_L13-21_
- inherits: `SPropertiesDebugViewBase`
- desc: Used to display the properties of a traced object
- L17 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;` — Begin SPropertiesDebugViewBase interface
- L18 _public prototype_ `virtual FName GetName() const override;`
- L19 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SPoseWatchCurvesView.h` (Private)


#### class `SPoseWatchCurvesView`  
`class SPoseWatchCurvesView : public SPropertiesDebugViewBase`  
_L10-32_
- inherits: `SPropertiesDebugViewBase`
- L13 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L16 _public function_ `void SetPoseWatchCurveFilter(uint64 InPoseWatchFilter, uint32 InCurveFilter)`
- L23 _public function_ `void ClearPoseWatchCurveFilter()`
- L29 _private member_ `uint64 PoseWatchFilter = 0;`
- L30 _private member_ `uint32 CurveFilter = 0;`
- L31 _private member_ `bool bCurveFilterSet = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SPropertiesDebugViewBase.h` (Private)


#### class `SPropertiesDebugViewBase`  
`class SPropertiesDebugViewBase : public IRewindDebuggerView`  
_L13-57_
- inherits: `IRewindDebuggerView`
- L15 _private function_ `SLATE_BEGIN_ARGS(SPropertiesDebugViewBase)`
- L19 _public prototype_ `void Construct(const FArguments& InArgs, uint64 InObjectId, double InTimeMarker, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L22 _public prototype_ `virtual void SetTimeMarker(double InTimeMarker) override;` — Begin IRewindDebuggerView interface
- L23 _public function_ `virtual uint64 GetObjectId() const override`
- L27 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — Begin SWidget interface
- L31 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const = 0;` — Get all the variants / properties at the given frame
- L34 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder);` — Build the context menu for the view widget
- L37 _public function_ `const TSharedPtr<SVariantValueView> & GetView() const` — @return Inner view widget for the object variant
- L44 _protected prototype_ `TSharedPtr<SWidget> CreateContextMenu();` — Setup base context menu
- L47 _protected prototype_ `void HandleOnMouseButtonDown(const TSharedPtr<FVariantTreeNode> & InVariantValueNode, const TraceServices::FFrame & InFrame, const FPointerEvent& InKeyEvent);` — Handle mouse button event from widget
- L49 _protected member_ `TSharedPtr<SVariantValueView> View;`
- L51 _protected member_ `uint64 ObjectId;`
- L52 _protected member_ `double TimeMarker;`
- L53 _protected member_ `uint32 SelectedPropertyId;`
- L55 _protected member_ `TAttribute<double> CurrentTime;`
- L56 _protected member_ `const TraceServices::IAnalysisSession* AnalysisSession;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SPropertyTrackView.h` (Private)


#### class `SPropertyTrackView`  
`class SPropertyTrackView : public SPropertiesDebugViewBase`  
_L20-35_
- inherits: `SPropertiesDebugViewBase`
- desc: Used to display the properties of a single traced variable.
- L25 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;` — Begin SPropertiesDebugViewBase interface
- L26 _public prototype_ `virtual FName GetName() const override;`
- L27 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L31 _public prototype_ `void SetTrack(const TWeakPtr<RewindDebugger::FPropertyTrack> & InTrack);` — Update the track from which information will be queried and displayed
- L34 _private member_ `TWeakPtr<RewindDebugger::FPropertyTrack> Track = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`
- L15 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/STrackVariantValueView.h` (Private)


#### class `STrackVariantValueView`  
`class STrackVariantValueView : public SCompoundWidget`  
_L16-37_
- inherits: `SCompoundWidget`
- desc: Wrapper for a variant value view for a track
- L19 _public function_ `SLATE_BEGIN_ARGS(STrackVariantValueView)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FBaseTimingTrack>& InTimingTrack, UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L25 _public function_ `TSharedPtr<FBaseTimingTrack> GetTimingTrack() const`
- L29 _private prototype_ `void HandleTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);` — Handle the time marker being scrubbed
- L32 _private member_ `TWeakPtr<FBaseTimingTrack> TimingTrack;`
- L34 _private member_ `TSharedPtr<SVariantValueView> VariantValueView;`
- L36 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Insights` (scope `UE`)
- L11 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)
- L12 _namespace_ `namespace Timing` (scope `UE::Insights`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SVariantValueView.h` (Private)


#### class `SVariantValueView`  
`class SVariantValueView : public SCompoundWidget`  
_L23-110_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SVariantValueView)`
- L28 _public prototype_ `SLATE_EVENT(FOnGetVariantValues, OnGetVariantValues) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnMouseButtonDownOnVariantValue, OnMouseButtonDownOnVariantValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L36 _public function_ `void RequestRefresh(const TraceServices::FFrame& InFrame)` — Refresh the displayed variants.
- L39 _public function_ `const TraceServices::FFrame & GetFrame() const` — @return Trace frame that the view represents
- L42 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const` — @return Trace session that the view references
- L45 _public prototype_ `static TSharedRef<SWidget> MakeVariantValueWidget(const TraceServices::IAnalysisSession& InAnalysisSession, const FVariantValue& InValue, const TAttribute<FText>& InHighlightText);` — @return New Widget for the given Variant Value
- L49 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L52 _private prototype_ `void BindCommands();` — Bind commands to actions
- L55 _private prototype_ `TSharedRef<ITableRow> HandleGeneratePropertyRow(TSharedRef<FVariantTreeNode> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row widget for a property item
- L58 _private prototype_ `void HandleGetPropertyChildren(TSharedRef<FVariantTreeNode> InItem, TArray<TSharedRef<FVariantTreeNode>>& OutChildren);` — Get the children of a property item
- L61 _private prototype_ `void HandleExpansionChanged(TSharedRef<FVariantTreeNode> InItem, bool bInExpanded);` — Persist expansion state when it changes
- L64 _private prototype_ `void RefreshNodes();` — Refresh the nodes
- L67 _private prototype_ `EVariantTreeNodeFilterState RefreshFilter_Helper(const TSharedRef<FVariantTreeNode>& InNode);` — Helper function for RefreshFilter()
- L70 _private prototype_ `void RefreshFilter();` — Refresh the filtered nodes
- L73 _private prototype_ `void RefreshExpansionRecursive(const TSharedRef<FVariantTreeNode>& InVariantTreeNode);` — Refresh node expansion state
- L76 _private prototype_ `void CopyHelper(const TSharedRef<FVariantTreeNode>& InNode, TStringBuilder<512>& InOutStringBuilder);` — Recursive helper function for copying
- L79 _private prototype_ `void HandleCopy();` — Handle Ctrl+C
- L82 _private prototype_ `bool CanCopy() const;` — Check if copy can occur
- L85 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;`
- L87 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L89 _private member_ `TSharedPtr<STreeView<TSharedRef<FVariantTreeNode>>> VariantTreeView;`
- L91 _private member_ `TArray<TSharedRef<FVariantTreeNode>> VariantTreeNodes;`
- L93 _private member_ `TArray<TSharedRef<FVariantTreeNode>> FilteredNodes;`
- L95 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L97 _private member_ `TraceServices::FFrame Frame;`
- L99 _private member_ `FOnGetVariantValues OnGetVariantValues;`
- L101 _private member_ `FOnMouseButtonDownOnVariantValue OnMouseButtonDownOnVariantValue;`
- L103 _private member_ `bool bNeedsRefresh;`
- L105 _private member_ `bool bRecordExpansion;`
- L107 _private member_ `TSet<uint64> ExpandedIds;`
- L109 _private member_ `FText FilterText;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L19 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetVariantValues, const TraceServices::FFrame& , TArray<TSharedRef<FVariantTreeNode>>& );` — Delegate called to get variant values to display
- L19 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetVariantValues, const TraceServices::FFrame& , TArray<TSharedRef<FVariantTreeNode>>& );` — Delegate called to get variant values to display
- L20 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMouseButtonDownOnVariantValue, const TSharedPtr<FVariantTreeNode> & , const TraceServices::FFrame & , const FPointerEvent& );`
- L20 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnMouseButtonDownOnVariantValue, const TSharedPtr<FVariantTreeNode> & , const TraceServices::FFrame & , const FPointerEvent& );`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMouseButtonDownOnVariantValueNode, const TSharedPtr<FVariantTreeNode> & , const FPointerEvent& );`
- L21 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMouseButtonDownOnVariantValueNode, const TSharedPtr<FVariantTreeNode> & , const FPointerEvent& );`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SkeletalMeshCurvesTrack.h` (Private)


#### class `FSkeletalMeshCurveSeries`  
`class FSkeletalMeshCurveSeries : public FGameplayGraphSeries`  
_L12-16_
- inherits: `FGameplayGraphSeries`
- L15 _public member_ `uint32 CurveId;`

#### class `FSkeletalMeshCurvesTrack`  
`class FSkeletalMeshCurvesTrack : public FGameplayGraphTrack`  
_L18-39_
- inherits: `FGameplayGraphTrack`
- L23 _public prototype_ `FSkeletalMeshCurvesTrack(const FAnimationSharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L25 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L26 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L27 _public prototype_ `virtual void AddAllSeries() override;`
- L28 _public prototype_ `virtual bool UpdateSeriesBounds(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport) override;`
- L29 _public prototype_ `virtual void UpdateSeries(FGameplayGraphSeries& InSeries, const FTimingTrackViewport& InViewport) override;`
- L30 _public prototype_ `virtual void GetVariantsAtFrame(const TraceServices::FFrame& InFrame, TArray<TSharedRef<FVariantTreeNode>>& OutVariants) const override;`
- L34 _private prototype_ `void FindSkeletalMeshPoseMessage(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FSkeletalMeshPoseMessage&)> InFoundPredicate) const;` — Helper function used to find a skeletal mesh pose
- L38 _private member_ `const FAnimationSharedData& SharedData;` — The shared data

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/SkeletalMeshPoseTrack.h` (Private)


#### class `FSkeletalMeshPoseTrack`  
`class FSkeletalMeshPoseTrack : public FGameplayTimingEventsTrack #if WITH_ENGINE , public FGCObject #endif`  
_L23-127_
- inherits: `FGameplayTimingEventsTrack,FGCObject`
- L31 _public prototype_ `FSkeletalMeshPoseTrack(const FAnimationSharedData& InSharedData, uint64 InObjectID, const TCHAR* InName);`
- L32 _public prototype_ `~FSkeletalMeshPoseTrack();`
- L34 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L35 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L36 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L37 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L38 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L41 _public function_ `void SetDrawPose(bool bInDrawPose)` — Access drawing flags
- L42 _public function_ `bool ShouldDrawPose() const`
- L43 _public function_ `bool ShouldDrawSkeleton() const`
- L46 _public function_ `void MarkPotentiallyDebugged()` — Mark this track as potentially being debugged, so we might need to push through its transforms when time changes
- L47 _public function_ `bool IsPotentiallyDebugged() const`
- L51 _public prototype_ `USkeletalMeshComponent* GetComponent(UWorld* InWorld);` — Get the component for the specified world
- L54 _public prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);` — Handle worlds being torn down
- L55 _public prototype_ `void RemoveWorld(UWorld* InWorld);`
- L58 _public prototype_ `void DrawPoses(UWorld* InWorld, double InTime, double InFrameStartTime, double InFrameEndTime);` — Draw poses at the specified time
- L61 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L62 _public function_ `virtual FString GetReferencerName() const override`
- L67 _private prototype_ `void FindSkeletalMeshPoseMessage(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FSkeletalMeshPoseMessage&)> InFoundPredicate) const;` — Helper function used to find a skeletal mesh pose
- L71 _private prototype_ `void UpdateComponentVisibility();` — Updates component visibility based on draw pose flag
- L75 _private member_ `const FAnimationSharedData& SharedData;` — The shared data
- L78 _private member_ `FLinearColor Color;` — The color to use to draw this track
- L81 _private member_ `bool bDrawPose;` — Whether to draw the pose
- L84 _private member_ `bool bDrawSkeleton;` — Whether to draw the skeleton
- L87 _private member_ `bool bPotentiallyDebugged;` — Whether we might be being debugged
- L117 _private prototype_ `FWorldComponentCache& GetWorldCache(UWorld* InWorld);` — Get the cached data for a world
- L120 _private member_ `TMap<TWeakObjectPtr<UWorld>, FWorldComponentCache> WorldCache;` — Cached map of per-world data
- L123 _private member_ `FDelegateHandle OnWorldCleanupHandle;` — Handles used to deal with world switching
- L124 _private member_ `FDelegateHandle OnWorldBeginTearDownHandle;`
- L125 _private member_ `FDelegateHandle OnPreWorldFinishDestroyHandle;`

#### struct `FSkeletalMeshPoseTrack::FWorldComponentCache`  
`struct FWorldComponentCache`  
_L91-114_
- desc: Cached data per-world
- L93 _public function_ `FWorldComponentCache() : World(nullptr) , Actor(nullptr) , Component(nullptr) , Time(0.0)`
- L101 _public prototype_ `UInsightsSkeletalMeshComponent* GetComponent();` — Get a cached component for this world
- L104 _public member_ `UWorld* World;` — The world we populate
- L107 _public member_ `TObjectPtr<AActor> Actor;` — Cached actor used to hang the component off of
- L110 _public member_ `TObjectPtr<UInsightsSkeletalMeshComponent> Component;` — Cached component used to visualize in this world
- L113 _public member_ `double Time;` — The time we last cached on this component

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Private/VariantTreeNode.h` (Private)


#### enum `EVariantTreeNodeFilterState`  
`enum class EVariantTreeNodeFilterState`  
_L11-16_
- L13 _public enumerator_ `Hidden`
- L14 _public enumerator_ `Visible`
- L15 _public enumerator_ `Highlighted`

#### struct `FVariantTreeNode`  
`struct FVariantTreeNode : TSharedFromThis<FVariantTreeNode>`  
_L19-171_
- inherits: `TSharedFromThis<FVariantTreeNode>`
- desc: A wrapper around a variant value, used to display collections of values in a tree
- L21 _public function_ `FVariantTreeNode(const FText& InName, const FVariantValue& InValue, uint64 InId = INDEX_NONE) : Name(InName) , Value(InValue) , PropertyNameId(0) , Id(InId)`
- L28 _public function_ `FVariantTreeNode(const FText& InName, const FVariantValue& InValue, uint32 InPropertyNamedId = 0, uint64 InId = INDEX_NONE) : Name(InName) , Value(InValue) , PropertyNameId(InPropertyNamedId) , Id(InId)`
- L35 _public function_ `const TSharedRef<FVariantTreeNode>& AddChild(const TSharedRef<FVariantTreeNode>& InChild)`
- L42 _public function_ `FText GetName() const`
- L44 _public function_ `const FVariantValue& GetValue() const`
- L46 _public function_ `FVariantValue& GetValue()`
- L48 _public function_ `TSharedPtr<FVariantTreeNode> GetParent() const`
- L50 _public function_ `const TArray<TSharedRef<FVariantTreeNode>>& GetChildren() const`
- L52 _public function_ `uint64 GetId() const`
- L54 _public function_ `uint32 GetPropertyNamedId() const`
- L56 _public function_ `void SetPropertyNameId(uint32 InPropertyNameId)`
- L58 _public function_ `void SetFilterState(EVariantTreeNodeFilterState InFilterState)`
- L60 _public function_ `EVariantTreeNodeFilterState GetFilterState() const`
- L62 _public prototype_ `FString GetValueAsString(const TraceServices::IAnalysisSession& InAnalysisSession) const;`
- L64 _public function_ `static TSharedRef<FVariantTreeNode> MakeHeader(const FText& InName, uint64 InId)`
- L73 _public function_ `static TSharedRef<FVariantTreeNode> MakeBool(const FText& InName, bool InValue, uint64 InId = INDEX_NONE)`
- L82 _public function_ `static TSharedRef<FVariantTreeNode> MakeInt32(const FText& InName, int32 InValue, uint64 InId = INDEX_NONE)`
- L91 _public function_ `static TSharedRef<FVariantTreeNode> MakeFloat(const FText& InName, float InValue, uint64 InId = INDEX_NONE)`
- L100 _public function_ `static TSharedRef<FVariantTreeNode> MakeVector2D(const FText& InName, const FVector2D& InValue, uint64 InId = INDEX_NONE)`
- L110 _public function_ `static TSharedRef<FVariantTreeNode> MakeVector(const FText& InName, const FVector& InValue, uint64 InId = INDEX_NONE)`
- L119 _public function_ `static TSharedRef<FVariantTreeNode> MakeString(const FText& InName, const TCHAR* InValue, uint64 InId = INDEX_NONE)`
- L128 _public function_ `static TSharedRef<FVariantTreeNode> MakeObject(const FText& InName, uint64 InValue, uint64 InId = INDEX_NONE, float PlaybackTime = 0.0f, float BlendX = 0.0f, float BlendY = 0.0f)`
- L140 _public function_ `static TSharedRef<FVariantTreeNode> MakeClass(const FText& InName, uint64 InValue, uint64 InId = INDEX_NONE)`
- L149 _public function_ `static TSharedRef<FVariantTreeNode> MakeAnimNode(const FText& InName, uint64 InValue, uint64 InAnimInstanceId, uint64 InId = INDEX_NONE)`
- L160 _private member_ `FText Name;`
- L161 _private member_ `FVariantValue Value;`
- L162 _private member_ `TWeakPtr<FVariantTreeNode> Parent;`
- L163 _private member_ `TArray<TSharedRef<FVariantTreeNode>> Children;`
- L164 _private member_ `uint32 PropertyNameId;`
- L167 _private member_ `uint64 Id;` — Unique ID used to record expansion state
- L170 _private member_ `EVariantTreeNodeFilterState FilterState;` — Filter state given current filter text

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Public/IAnimationProvider.h` (Public)


#### struct `FSkeletalMeshInfo`  
`struct FSkeletalMeshInfo`  
_L11-17_
- L13 _public member_ `uint64 ParentIndicesStartIndex = 0;`
- L14 _public member_ `uint64 Id = 0;`
- L15 _public member_ `uint64 SkeletonId = 0;`
- L16 _public member_ `uint32 BoneCount = 0;`

#### struct `FAnimNodeInfo`  
`struct FAnimNodeInfo`  
_L19-25_
- L21 _public member_ `int32 Id = 0;`
- L22 _public member_ `uint64 AnimInstanceId = 0;`
- L23 _public member_ `const TCHAR* Name = nullptr;`
- L24 _public member_ `const TCHAR* TypeName = nullptr;`

#### struct `FSkeletalMeshNamedCurve`  
`struct FSkeletalMeshNamedCurve`  
_L27-31_
- L29 _public member_ `uint32 Id = 0;`
- L30 _public member_ `float Value = 0.0f;`

#### struct `FExternalMorphWeightMessage`  
`struct FExternalMorphWeightMessage`  
_L33-38_
- L35 _public member_ `int32 Index = 0;`
- L36 _public member_ `int32 NumMorphs = 0;`
- L37 _public member_ `TArray<float> Weights;`

#### struct `FSkeletalMeshPoseMessage`  
`struct FSkeletalMeshPoseMessage`  
_L40-56_
- L42 _public member_ `FTransform ComponentToWorld;`
- L43 _public member_ `double RecordingTime = 0.0;`
- L44 _public member_ `uint64 TransformStartIndex = 0;`
- L45 _public member_ `uint64 CurveStartIndex = 0;`
- L46 _public member_ `uint64 ComponentId = 0;`
- L47 _public member_ `uint64 MeshId = 0;`
- L48 _public member_ `uint64 ExternalMorphStartIndex = 0;`
- L49 _public member_ `const TCHAR* MeshName = nullptr;`
- L50 _public member_ `uint16 NumTransforms = 0;`
- L51 _public member_ `uint16 NumCurves = 0;`
- L52 _public member_ `uint16 FrameCounter = 0;`
- L53 _public member_ `uint16 LodIndex = 0;`
- L54 _public member_ `uint16 NumExternalMorphSets = 0;`
- L55 _public member_ `bool bIsVisible = true;`

#### struct `FPoseWatchMessage`  
`struct FPoseWatchMessage`  
_L58-74_
- L60 _public member_ `FTransform WorldTransform;`
- L61 _public member_ `FColor Color = FColor::Black;`
- L62 _public member_ `double RecordingTime = 0.0;`
- L63 _public member_ `uint64 ComponentId = 0;`
- L64 _public member_ `uint64 AnimInstanceId = 0;`
- L65 _public member_ `uint64 PoseWatchId = 0;`
- L66 _public member_ `uint64 BoneTransformsStartIndex = 0;`
- L67 _public member_ `uint64 CurveStartIndex = 0;`
- L68 _public member_ `uint64 RequiredBonesStartIndex = 0;`
- L69 _public member_ `uint32 NameId = 0;`
- L70 _public member_ `uint16 NumBoneTransforms = 0;`
- L71 _public member_ `uint16 NumRequiredBones = 0;`
- L72 _public member_ `uint16 NumCurves = 0;`
- L73 _public member_ `bool bIsEnabled = false;`

#### struct `FSkeletalMeshFrameMessage`  
`struct FSkeletalMeshFrameMessage`  
_L76-80_
- L78 _public member_ `uint64 ComponentId = 0;`
- L79 _public member_ `uint16 FrameCounter = 0;`

#### struct `FTickRecordMessage`  
`struct FTickRecordMessage`  
_L82-107_
- L84 _public member_ `uint64 ComponentId = 0;`
- L85 _public member_ `uint64 AnimInstanceId = 0;`
- L86 _public member_ `uint64 AssetId = 0;`
- L87 _public member_ `double RecordingTime = 0.0;`
- L88 _public member_ `int32 NodeId = -1;`
- L89 _public member_ `float BlendWeight = 0.0f;`
- L90 _public member_ `float PlaybackTime = 0.0f;`
- L91 _public member_ `float RootMotionWeight = 0.0f;`
- L92 _public member_ `float PlayRate = 0.0f;`
- L93 _public member_ `float BlendSpacePositionX = 0.0f;`
- L94 _public member_ `float BlendSpacePositionY = 0.0f;`
- L95 _public member_ `float BlendSpaceFilteredPositionX = 0.0f;`
- L96 _public member_ `float BlendSpaceFilteredPositionY = 0.0f;`
- L97 _public member_ `uint16 FrameCounter = 0;`
- L98 _public member_ `bool bLooping = false;`
- L99 _public member_ `bool bIsBlendSpace = false;`
- L100 _public member_ `uint32 bSyncGroupNameId = 0;`
- L101 _public member_ `bool bIsSyncGroupLeader = false;`
- L102 _public member_ `float SyncLeaderScore = 0.0f;`
- L103 _public member_ `float TimeToPrevMarker = 0.0f;`
- L104 _public member_ `float TimeToNextMarker = 0.0f;`
- L105 _public member_ `int32 PrevMarkerIndex = -1;`
- L106 _public member_ `int32 NextMarkerIndex = -1;`

#### enum `EAnimGraphPhase`  
`enum class EAnimGraphPhase : uint8`  
_L109-116_
- L111 _public enumerator_ `Initialize = 0`
- L112 _public enumerator_ `PreUpdate = 1`
- L113 _public enumerator_ `Update = 2`
- L114 _public enumerator_ `CacheBones = 3`
- L115 _public enumerator_ `Evaluate = 4`

#### struct `FAnimGraphMessage`  
`struct FAnimGraphMessage`  
_L118-124_
- L120 _public member_ `uint64 AnimInstanceId = 0;`
- L121 _public member_ `int32 NodeCount = 0;`
- L122 _public member_ `uint16 FrameCounter = 0;`
- L123 _public member_ `EAnimGraphPhase Phase = EAnimGraphPhase::Initialize;`

#### struct `FAnimNodeMessage`  
`struct FAnimNodeMessage`  
_L126-137_
- L128 _public member_ `const TCHAR* NodeName = nullptr;`
- L129 _public member_ `uint64 AnimInstanceId = 0;`
- L130 _public member_ `int32 PreviousNodeId = -1;`
- L131 _public member_ `int32 NodeId = -1;`
- L132 _public member_ `float Weight = 0.0f;`
- L133 _public member_ `float RootMotionWeight = 0.0f;`
- L134 _public member_ `uint16 FrameCounter = 0;`
- L135 _public member_ `EAnimGraphPhase Phase = EAnimGraphPhase::Initialize;`
- L136 _public member_ `const TCHAR* NodeTypeName = nullptr;`

#### enum `EAnimNodeValueType`  
`enum class EAnimNodeValueType : uint8`  
_L139-150_
- L141 _public enumerator_ `Bool`
- L142 _public enumerator_ `Int32`
- L143 _public enumerator_ `Float`
- L144 _public enumerator_ `Vector2D`
- L145 _public enumerator_ `Vector`
- L146 _public enumerator_ `String`
- L147 _public enumerator_ `Object`
- L148 _public enumerator_ `Class`
- L149 _public enumerator_ `AnimNode`

#### struct `FVariantValue`  
`struct FVariantValue`  
_L152-218_
- L154 _public function_ `FVariantValue() : Vector(FVector::ZeroVector)`
- L217 _public member_ `EAnimNodeValueType Type = EAnimNodeValueType::Bool;`

#### struct `FVariantValue::FVector2DEntry`  
`struct FVector2DEntry`  
_L159-166_
- L161 _public function_ `FVector2DEntry(const FVector2D& InVector) : Value(InVector)`
- L165 _public member_ `FVector2D Value;`

#### struct `FVariantValue::FVectorEntry`  
`struct FVectorEntry`  
_L168-175_
- L170 _public function_ `FVectorEntry(const FVector& InVector) : Value(InVector)`
- L174 _public member_ `FVector Value;`

#### union `FVariantValue::(anonymous)`  
``  
_L178-215_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L180-182_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L184-186_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L188-190_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L194-196_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L198-205_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L207-209_

#### struct `FVariantValue::__anon264fda7e010a::(anonymous)`  
``  
_L211-214_

#### struct `FAnimNodeValueMessage`  
`struct FAnimNodeValueMessage`  
_L220-228_
- L222 _public member_ `const TCHAR* Key = nullptr;`
- L223 _public member_ `uint64 AnimInstanceId = 0;`
- L224 _public member_ `FVariantValue Value;`
- L225 _public member_ `int32 NodeId = -1;`
- L226 _public member_ `uint16 FrameCounter = 0;`
- L227 _public member_ `double RecordingTime = 0.0f;`

#### struct `FAnimSequencePlayerMessage`  
`struct FAnimSequencePlayerMessage`  
_L230-237_
- L232 _public member_ `uint64 AnimInstanceId = 0;`
- L233 _public member_ `int32 NodeId = -1;`
- L234 _public member_ `float Position = 0.0f;`
- L235 _public member_ `float Length = 0.0f;`
- L236 _public member_ `uint16 FrameCounter = 0;`

#### struct `FBlendSpacePlayerMessage`  
`struct FBlendSpacePlayerMessage`  
_L239-250_
- L241 _public member_ `uint64 AnimInstanceId = 0;`
- L242 _public member_ `uint64 BlendSpaceId = 0;`
- L243 _public member_ `int32 NodeId = -1;`
- L244 _public member_ `float PositionX = 0.0f;`
- L245 _public member_ `float PositionY = 0.0f;`
- L246 _public member_ `float PositionZ = 0.0f;`
- L247 _public member_ `float FilteredPositionX = 0.0f;`
- L248 _public member_ `float FilteredPositionY = 0.0f;`
- L249 _public member_ `float FilteredPositionZ = 0.0f;`

#### struct `FAnimStateMachineMessage`  
`struct FAnimStateMachineMessage`  
_L252-260_
- L254 _public member_ `uint64 AnimInstanceId = 0;`
- L255 _public member_ `int32 NodeId = -1;`
- L256 _public member_ `int32 StateMachineIndex = -1;`
- L257 _public member_ `int32 StateIndex = -1;`
- L258 _public member_ `float StateWeight = 0.0f;`
- L259 _public member_ `float ElapsedTime = 0.0f;`

#### enum `EAnimNotifyMessageType`  
`enum class EAnimNotifyMessageType : uint8`  
_L262-269_
- L264 _public enumerator_ `Event = 0`
- L265 _public enumerator_ `Begin = 1`
- L266 _public enumerator_ `End = 2`
- L267 _public enumerator_ `Tick = 3`
- L268 _public enumerator_ `SyncMarker = 4` — We 'fake' sync markers with a notify type for convenience

#### struct `FAnimNotifyMessage`  
`struct FAnimNotifyMessage`  
_L271-282_
- L273 _public member_ `uint64 AnimInstanceId = 0;`
- L274 _public member_ `uint64 AssetId = 0;`
- L275 _public member_ `uint64 NotifyId = 0;`
- L276 _public member_ `const TCHAR* Name = nullptr;`
- L277 _public member_ `uint32 NameId = 0;`
- L278 _public member_ `double RecordingTime = 0.0f;`
- L279 _public member_ `float Time = 0.0f;`
- L280 _public member_ `float Duration = 0.0f;`
- L281 _public member_ `EAnimNotifyMessageType NotifyEventType = EAnimNotifyMessageType::Event;`

#### struct `FAnimMontageMessage`  
`struct FAnimMontageMessage`  
_L284-295_
- L286 _public member_ `uint64 AnimInstanceId = 0;`
- L287 _public member_ `uint64 MontageId = 0;`
- L288 _public member_ `double RecordingTime = 0.0;`
- L289 _public member_ `uint32 CurrentSectionNameId = 0;`
- L290 _public member_ `uint32 NextSectionNameId = 0;`
- L291 _public member_ `float Weight = 0.0f;`
- L292 _public member_ `float DesiredWeight = 0.0f;`
- L293 _public member_ `float Position = 0.0f;`
- L294 _public member_ `uint16 FrameCounter = 0;`

#### enum `EInertializationType`  
`enum class EInertializationType : uint8`  
_L297-301_
- L299 _public enumerator_ `Inertialization = 0`
- L300 _public enumerator_ `DeadBlending = 1`

#### struct `FInertializationMessage`  
`struct FInertializationMessage`  
_L303-311_
- L305 _public member_ `uint64 AnimInstanceId = 0;`
- L306 _public member_ `double ProfileTime;`
- L307 _public member_ `double RecordingTime;`
- L308 _public member_ `int32 NodeId;`
- L309 _public member_ `float Weight;`
- L310 _public member_ `EInertializationType Type;`

#### struct `FAnimAttributeMessage`  
`struct FAnimAttributeMessage`  
_L313-318_
- L315 _public member_ `int32 SourceNodeId = 0;`
- L316 _public member_ `int32 TargetNodeId = 0;`
- L317 _public member_ `uint32 AttributeNameId = 0;`

#### struct `FAnimSyncMessage`  
`struct FAnimSyncMessage`  
_L320-324_
- L322 _public member_ `int32 SourceNodeId = 0;`
- L323 _public member_ `uint32 GroupNameId = 0;`

#### class `IAnimationProvider`  
`class IAnimationProvider : public TraceServices::IProvider`  
_L326-375_
- inherits: `TraceServices::IProvider`
- L329 _public typedef_ `typedef TraceServices::ITimeline<FTickRecordMessage> TickRecordTimeline;`
- L330 _public typedef_ `typedef TraceServices::ITimeline<FSkeletalMeshPoseMessage> SkeletalMeshPoseTimeline;`
- L331 _public typedef_ `typedef TraceServices::ITimeline<FAnimGraphMessage> AnimGraphTimeline;`
- L332 _public typedef_ `typedef TraceServices::ITimeline<FAnimNodeMessage> AnimNodesTimeline;`
- L333 _public typedef_ `typedef TraceServices::ITimeline<FAnimNodeValueMessage> AnimNodeValuesTimeline;`
- L334 _public typedef_ `typedef TraceServices::ITimeline<FAnimSequencePlayerMessage> AnimSequencePlayersTimeline;`
- L335 _public typedef_ `typedef TraceServices::ITimeline<FAnimStateMachineMessage> StateMachinesTimeline;`
- L336 _public typedef_ `typedef TraceServices::ITimeline<FBlendSpacePlayerMessage> BlendSpacePlayersTimeline;`
- L337 _public typedef_ `typedef TraceServices::ITimeline<FAnimNotifyMessage> AnimNotifyTimeline;`
- L338 _public typedef_ `typedef TraceServices::ITimeline<FAnimMontageMessage> AnimMontageTimeline;`
- L339 _public typedef_ `typedef TraceServices::ITimeline<FAnimAttributeMessage> AnimAttributeTimeline;`
- L340 _public typedef_ `typedef TraceServices::ITimeline<FAnimSyncMessage> AnimSyncTimeline;`
- L341 _public typedef_ `typedef TraceServices::ITimeline<FPoseWatchMessage> PoseWatchTimeline;`
- L342 _public typedef_ `typedef TraceServices::ITimeline<FInertializationMessage> InertializationTimeline;`
- L344 _public prototype_ `virtual void EnumerateSkeletalMeshPoseTimelines(TFunctionRef<void(uint64 ObjectId, const SkeletalMeshPoseTimeline&)> Callback) const =0;`
- L345 _public prototype_ `virtual bool ReadSkeletalMeshPoseTimeline(uint64 InObjectId, TFunctionRef<void(const SkeletalMeshPoseTimeline&, bool)> Callback) const = 0;`
- L346 _public prototype_ `virtual void GetSkeletalMeshComponentSpacePose(const FSkeletalMeshPoseMessage& InMessage, const FSkeletalMeshInfo& InMeshInfo, FTransform& OutComponentToWorld, TArray<FTransform>& OutTransforms) const = 0;`
- L347 _public prototype_ `virtual void EnumerateSkeletalMeshCurveIds(uint64 InObjectId, TFunctionRef<void(uint32)> Callback) const = 0;`
- L348 _public prototype_ `virtual void GetPoseWatchData(const FPoseWatchMessage& InMessage, TArray<FTransform>& BoneTransforms, TArray<uint16>& RequiredBones) const = 0;`
- L349 _public prototype_ `virtual void EnumerateSkeletalMeshCurves(const FSkeletalMeshPoseMessage& InMessage, TFunctionRef<void(const FSkeletalMeshNamedCurve&)> Callback) const = 0;`
- L350 _public prototype_ `virtual void EnumeratePoseWatchCurves(const FPoseWatchMessage& InMessage, TFunctionRef<void(const FSkeletalMeshNamedCurve&)> Callback) const = 0;`
- L351 _public prototype_ `virtual void EnumerateExternalMorphSets(const FSkeletalMeshPoseMessage& InMessage, TFunctionRef<void(const FExternalMorphWeightMessage&)> Callback) const = 0;`
- L352 _public prototype_ `virtual bool ReadTickRecordTimeline(uint64 InObjectId, TFunctionRef<void(const TickRecordTimeline&)> Callback) const = 0;`
- L353 _public prototype_ `virtual bool ReadInertializationTimeline(uint64 InObjectId, TFunctionRef<void(const InertializationTimeline&)> Callback) const = 0;`
- L354 _public prototype_ `virtual void EnumerateInertializationNodes(uint64 InObjectId, TFunctionRef<void(int32, EInertializationType)> Callback) const = 0;`
- L355 _public prototype_ `virtual void EnumerateTickRecordIds(uint64 InObjectId, TFunctionRef<void(uint64, int32)> Callback) const = 0;`
- L356 _public prototype_ `virtual void EnumerateAnimGraphTimelines(TFunctionRef<void(uint64 ObjectId, const AnimGraphTimeline&)> Callback) const =0;`
- L357 _public prototype_ `virtual bool ReadAnimGraphTimeline(uint64 InObjectId, TFunctionRef<void(const AnimGraphTimeline&)> Callback) const = 0;`
- L358 _public prototype_ `virtual bool ReadAnimNodesTimeline(uint64 InObjectId, TFunctionRef<void(const AnimNodesTimeline&)> Callback) const = 0;`
- L359 _public prototype_ `virtual bool ReadAnimNodeValuesTimeline(uint64 InObjectId, TFunctionRef<void(const AnimNodeValuesTimeline&)> Callback) const = 0;`
- L360 _public prototype_ `virtual bool ReadAnimAttributesTimeline(uint64 InObjectId, TFunctionRef<void(const AnimAttributeTimeline&)> Callback) const = 0;`
- L361 _public prototype_ `virtual bool ReadAnimSequencePlayersTimeline(uint64 InObjectId, TFunctionRef<void(const AnimSequencePlayersTimeline&)> Callback) const = 0;`
- L362 _public prototype_ `virtual bool ReadAnimBlendSpacePlayersTimeline(uint64 InObjectId, TFunctionRef<void(const BlendSpacePlayersTimeline&)> Callback) const = 0;`
- L363 _public prototype_ `virtual bool ReadStateMachinesTimeline(uint64 InObjectId, TFunctionRef<void(const StateMachinesTimeline&)> Callback) const = 0;`
- L364 _public prototype_ `virtual bool ReadNotifyTimeline(uint64 InObjectId, TFunctionRef<void(const AnimNotifyTimeline&)> Callback) const = 0;`
- L365 _public prototype_ `virtual void EnumerateNotifyStateTimelines(uint64 InObjectId, TFunctionRef<void(uint64, const AnimNotifyTimeline&)> Callback) const = 0;`
- L366 _public prototype_ `virtual bool ReadMontageTimeline(uint64 InObjectId, TFunctionRef<void(const AnimMontageTimeline&)> Callback) const = 0;`
- L367 _public prototype_ `virtual void EnumerateMontageIds(uint64 InObjectId, TFunctionRef<void(uint64)> Callback) const = 0;`
- L368 _public prototype_ `virtual bool ReadAnimSyncTimeline(uint64 InObjectId, TFunctionRef<void(const AnimSyncTimeline&)> Callback) const = 0;`
- L369 _public prototype_ `virtual bool ReadPoseWatchTimeline(uint64 InObjectId, TFunctionRef<void(const PoseWatchTimeline&)> Callback) const = 0;`
- L370 _public prototype_ `virtual const FSkeletalMeshInfo* FindSkeletalMeshInfo(uint64 InObjectId) const = 0;`
- L371 _public prototype_ `virtual const FAnimNodeInfo* FindAnimNodeInfo(int32 InNodeId, uint64 InAnimInstanceId) const = 0;`
- L372 _public prototype_ `virtual const TCHAR* GetName(uint32 InId) const = 0;`
- L373 _public prototype_ `virtual FText FormatNodeKeyValue(const FAnimNodeValueMessage& InMessage) const = 0;`
- L374 _public prototype_ `virtual FText FormatNodeValue(const FAnimNodeValueMessage& InMessage) const = 0;`

#### Free symbols / members of external scopes

- L181 _member_ `bool bValue;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0208`)
- L182 _member_ `} Bool;` (scope `FVariantValue::__anon264fda7e010a`)
- L185 _member_ `int32 Value;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0308`)
- L186 _member_ `} Int32;` (scope `FVariantValue::__anon264fda7e010a`)
- L189 _member_ `float Value;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0408`)
- L190 _member_ `} Float;` (scope `FVariantValue::__anon264fda7e010a`)
- L191 _member_ `FVector2DEntry Vector2D;` (scope `FVariantValue::__anon264fda7e010a`)
- L192 _member_ `FVectorEntry Vector;` (scope `FVariantValue::__anon264fda7e010a`)
- L195 _member_ `const TCHAR* Value;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0508`)
- L196 _member_ `} String;` (scope `FVariantValue::__anon264fda7e010a`)
- L199 _member_ `uint64 Value;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0608`)
- L201 _member_ `float PlaybackTime;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0608`) — for animation assets, store the playback time so we can open the editor to a specific time
- L203 _member_ `float BlendX;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0608`) — for blend spaces, store the x/y parameters so we can open the editor at those parameters
- L204 _member_ `float BlendY;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0608`)
- L205 _member_ `} Object;` (scope `FVariantValue::__anon264fda7e010a`)
- L208 _member_ `uint64 Value;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0708`)
- L209 _member_ `} Class;` (scope `FVariantValue::__anon264fda7e010a`)
- L212 _member_ `int32 Value;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0808`)
- L213 _member_ `uint64 AnimInstanceId;` (scope `FVariantValue::__anon264fda7e010a::__anon264fda7e0808`)
- L214 _member_ `} AnimNode;` (scope `FVariantValue::__anon264fda7e010a`)

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Public/IGameplayInsightsModule.h` (Public)


#### class `IGameplayInsightsModule`  
`class IGameplayInsightsModule : public IModuleInterface`  
_L18-31_
- inherits: `IModuleInterface`
- L25 _public prototype_ `virtual void EnableObjectPropertyTrace(UObject* Object, bool bEnable = true) = 0;` — start or stop tracing all properties of this Object to Insights
- L27 _public prototype_ `virtual bool IsObjectPropertyTraceEnabled(UObject* Object) = 0;` — check if an Object has it's properties tracing to Insights
- L29 _public prototype_ `virtual void StartTrace() = 0;` — start tracing data

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace GameplayInsightsTabs`
- L10 _externvar_ `extern const FName DocumentTab;` (scope `GameplayInsightsTabs`)
- L13 _namespace_ `namespace TraceServices`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Public/IGameplayProvider.h` (Public)


#### struct `FClassInfo`  
`struct FClassInfo`  
_L15-21_
- L17 _public member_ `uint64 Id = 0;`
- L18 _public member_ `uint64 SuperId = 0;`
- L19 _public member_ `const TCHAR* Name = nullptr;`
- L20 _public member_ `const TCHAR* PathName = nullptr;`

#### enum `EObjectInfoFlags`  
`enum class EObjectInfoFlags : uint8`  
_L23-28_
- L25 _public enumerator_ `None = 0`
- L26 _public enumerator_ `TransientObject = 1 << 0`
- L27 _public enumerator_ `StructInstance = 1 << 1`

#### struct `FObjectInfo`  
`struct FObjectInfo`  
_L30-91_
- L33 _public prototype_ `FObjectInfo(const FObjectInfo& Other) = default;`
- L34 _public prototype_ `FObjectInfo(FObjectInfo&& Other) = default;`
- L35 _public prototype_ `FObjectInfo& operator=(const FObjectInfo& Other) = default;`
- L36 _public prototype_ `FObjectInfo& operator=(FObjectInfo&& Other) = default;`
- L39 _public function_ `FObjectInfo(const RewindDebugger::FObjectId& ObjectId, const RewindDebugger::FObjectId& OuterObjectId, const uint64 ClassId, const TCHAR* Name , const TCHAR* PathName, EObjectInfoFlags Flags) : ObjectId(ObjectId) , OuterObjectId(OuterObjectId) , ClassId(ClassId) , Name(Name) , PathName(PathName) , Flags(Flags)`
- L51 _public function_ `const RewindDebugger::FObjectId& GetId() const` — @return Id of an object recorded in the trace
- L57 _public function_ `const RewindDebugger::FObjectId& GetOuterId() const` — @return Id of the recorded object's parent
- L63 _public function_ `uint64 GetUObjectId() const` — @return Part of the Id representing the UObject
- L69 _public function_ `uint64 GetOuterUObjectId() const` — @return Part of the Id of the parent object representing the UObject
- L75 _private member_ `RewindDebugger::FObjectId ObjectId;`
- L76 _private member_ `RewindDebugger::FObjectId OuterObjectId;`
- L81 _public member_ `uint64 Id = 0;` — `UE_DEPRECATED(5.7, "Use ObjectId instead")`
- L83 _public member_ `uint64 OuterId = 0;` — `UE_DEPRECATED(5.7, "Use OuterObjectId instead")`
- L86 _public member_ `uint64 ClassId = 0;`
- L87 _public member_ `const TCHAR* Name = nullptr;`
- L88 _public member_ `const TCHAR* PathName = nullptr;`
- L89 _public member_ `EObjectInfoFlags Flags;`

#### struct `FObjectPropertiesMessage`  
`struct FObjectPropertiesMessage`  
_L93-99_
- L95 _public member_ `int64 PropertyValueStartIndex = INDEX_NONE;` — Inclusive
- L96 _public member_ `int64 PropertyValueEndIndex = INDEX_NONE;` — Exclusive
- L97 _public member_ `double ProfileTime;`
- L98 _public member_ `double ElapsedTime;`

#### struct `FObjectPropertyValue`  
`struct FObjectPropertyValue`  
_L101-109_
- L103 _public member_ `const TCHAR* Value = nullptr;`
- L104 _public member_ `int32 ParentId = 0;`
- L105 _public member_ `uint32 TypeStringId = 0;`
- L106 _public member_ `uint32 NameId = 0;`
- L107 _public member_ `uint32 ParentNameId = 0;`
- L108 _public member_ `float ValueAsFloat = 0.0f;`

#### struct `FObjectEventMessage`  
`struct FObjectEventMessage`  
_L111-128_
- L113 _public member_ `RewindDebugger::FObjectId ObjectId;`
- L114 _public member_ `const TCHAR* Name = nullptr;`
- L117 _public prototype_ `FObjectEventMessage() = default;`
- L118 _public prototype_ `FObjectEventMessage(const FObjectEventMessage& Other) = default;`
- L119 _public prototype_ `FObjectEventMessage(FObjectEventMessage&& Other) = default;`
- L120 _public prototype_ `FObjectEventMessage& operator=(const FObjectEventMessage& Other) = default;`
- L121 _public prototype_ `FObjectEventMessage& operator=(FObjectEventMessage&& Other) = default;`
- L126 _public member_ `uint64 Id = 0;` — `UE_DEPRECATED(5.7, "Use Identifier instead")`

#### struct `FRecordingInfoMessage`  
`struct FRecordingInfoMessage`  
_L130-137_
- L132 _public member_ `uint64 WorldId;`
- L133 _public member_ `double ProfileTime;`
- L134 _public member_ `double ElapsedTime;`
- L135 _public member_ `uint32 FrameIndex;`
- L136 _public member_ `uint32 RecordingIndex;`

#### struct `FViewMessage`  
`struct FViewMessage`  
_L139-146_
- L141 _public member_ `uint64 PlayerId;`
- L142 _public member_ `FVector Position;`
- L143 _public member_ `FRotator Rotation;`
- L144 _public member_ `float Fov;`
- L145 _public member_ `float AspectRatio;`

#### struct `FWorldInfo`  
`struct FWorldInfo`  
_L148-179_
- L174 _public member_ `uint64 Id = 0;`
- L175 _public member_ `int32 PIEInstanceId = 0;`
- L176 _public member_ `EType Type = EType::None;`
- L177 _public member_ `ENetMode NetMode = ENetMode::Standalone;`
- L178 _public member_ `bool bIsSimulating = false;`

#### enum `FWorldInfo::EType`  
`enum class EType : uint8`  
_L151-161_
- desc: Types of worlds that we know about - synced with EngineTypes.h
- L153 _public enumerator_ `None`
- L154 _public enumerator_ `Game`
- L155 _public enumerator_ `Editor`
- L156 _public enumerator_ `PIE`
- L157 _public enumerator_ `EditorPreview`
- L158 _public enumerator_ `GamePreview`
- L159 _public enumerator_ `GameRPC`
- L160 _public enumerator_ `Inactive`

#### enum `FWorldInfo::ENetMode`  
`enum class ENetMode : uint8`  
_L164-172_
- desc: Types of net modes that we know about - synced with EngineBaseTypes.h
- L166 _public enumerator_ `Standalone`
- L167 _public enumerator_ `DedicatedServer`
- L168 _public enumerator_ `ListenServer`
- L169 _public enumerator_ `Client`
- L171 _public enumerator_ `MAX`

#### class `IGameplayProvider`  
`class IGameplayProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L186-261_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L189 _public typedef_ `typedef TraceServices::ITimeline<FObjectEventMessage> ObjectEventsTimeline;`
- L190 _public typedef_ `typedef TraceServices::ITimeline<FObjectPropertiesMessage> ObjectPropertiesTimeline;`
- L191 _public typedef_ `typedef TraceServices::ITimeline<FRecordingInfoMessage> RecordingInfoTimeline;`
- L192 _public typedef_ `typedef TraceServices::ITimeline<FViewMessage> ViewTimeline;`
- L194 _public prototype_ `virtual bool ReadObjectEventsTimeline(const RewindDebugger::FObjectId& InObjectId, TFunctionRef<void(const ObjectEventsTimeline&)> Callback) const = 0;`
- L195 _public prototype_ `virtual bool ReadObjectEvent(const RewindDebugger::FObjectId& InObjectId, uint64 InMessageId, TFunctionRef<void(const FObjectEventMessage&)> Callback) const = 0;`
- L196 _public prototype_ `virtual bool ReadObjectPropertiesTimeline(uint64 InObjectId, TFunctionRef<void(const ObjectPropertiesTimeline&)> Callback) const = 0;`
- L197 _public prototype_ `virtual bool ReadObjectPropertiesStorage(uint64 InObjectId, const FObjectPropertiesMessage& InMessage, TFunctionRef<void(const TConstArrayView<FObjectPropertyValue> &)> Callback) const = 0;`
- L198 _public prototype_ `virtual void EnumerateObjectPropertyValues(uint64 InObjectId, const FObjectPropertiesMessage& InMessage, TFunctionRef<void(const FObjectPropertyValue&)> Callback) const = 0;`
- L199 _public prototype_ `virtual void EnumerateObjects(TFunctionRef<void(const FObjectInfo&)> Callback) const = 0;`
- L200 _public prototype_ `virtual void EnumerateObjects(double StartTime, double EndTime, TFunctionRef<void(const FObjectInfo&)> Callback) const = 0;`
- L201 _public prototype_ `virtual void EnumerateWorlds(TFunctionRef<void(const FWorldInfo&)> Callback) const = 0;`
- L202 _public prototype_ `virtual void EnumerateSubobjects(const RewindDebugger::FObjectId& InObjectId, TFunctionRef<void(const RewindDebugger::FObjectId& SubObjectId)> Callback) const = 0;`
- L203 _public prototype_ `virtual const FObjectPropertyValue * FindPropertyValueFromStorageIndex(uint64 InObjectId, int64 InStorageIndex) const = 0;`
- L204 _public prototype_ `virtual const FClassInfo* FindClassInfo(uint64 InClassId) const = 0;`
- L205 _public prototype_ `virtual const UStruct* FindType(uint64 InTypeId, bool bSearchBlueprints) const = 0;`
- L207 _public function_ `virtual const UClass* FindClass(const uint64 InClassId, const bool bSearchBlueprints) const final` — `UE_DEPRECATED(5.8, "Use FindType returning a UStruct instead.")`
- L211 _public prototype_ `virtual const FClassInfo* FindClassInfo(const TCHAR* InClassPath) const = 0;`
- L212 _public prototype_ `virtual bool IsSubClassOf(uint64 InSubClassId, uint64 InParentClassId) const = 0;`
- L213 _public prototype_ `virtual const FObjectInfo* FindObjectInfo(const uint64 InObjectId) const = 0;`
- L214 _public prototype_ `virtual const FObjectInfo* FindObjectInfo(const RewindDebugger::FObjectId& InObjectId) const = 0;`
- L215 _public prototype_ `virtual const FWorldInfo* FindWorldInfo(uint64 InObjectId) const = 0;`
- L216 _public prototype_ `virtual const FWorldInfo* FindWorldInfoFromObject(uint64 InObjectId) const = 0;`
- L217 _public prototype_ `virtual bool IsWorld(uint64 InObjectId) const = 0;`
- L218 _public prototype_ `virtual const FClassInfo& GetClassInfo(uint64 InClassId) const = 0;`
- L219 _public prototype_ `virtual const FClassInfo& GetClassInfoFromObject(uint64 InObjectId) const = 0;`
- L220 _public prototype_ `virtual const FObjectInfo& GetObjectInfo(const uint64 InObjectId) const = 0;`
- L221 _public prototype_ `virtual const FObjectInfo& GetObjectInfo(const RewindDebugger::FObjectId& InObjectId) const = 0;`
- L222 _public prototype_ `virtual FOnObjectEndPlay& OnObjectEndPlay() = 0;`
- L223 _public prototype_ `virtual const TCHAR* GetPropertyName(uint32 InPropertyStringId) const = 0;`
- L224 _public prototype_ `virtual const RecordingInfoTimeline* GetRecordingInfo(uint32 RecordingId) const = 0;`
- L225 _public prototype_ `virtual void ReadViewTimeline(TFunctionRef<void(const ViewTimeline&)> Callback) const = 0;`
- L226 _public prototype_ `virtual uint64 FindPossessingController(uint64 Pawn, double Time) const = 0;`
- L227 _public prototype_ `virtual TRange<double> GetObjectTraceLifetime(const RewindDebugger::FObjectId& InObjectId) const = 0;`
- L228 _public prototype_ `virtual TRange<double> GetObjectRecordingLifetime(const RewindDebugger::FObjectId& InObjectId) const = 0;`
- L229 _public prototype_ `virtual double GetRecordingDuration() const = 0;`
- L230 _public prototype_ `virtual FSlateIcon FindIconForClass(uint64 ClassId) const = 0;`
- L231 _public prototype_ `virtual bool GetObjectTransform(uint64 InObjectId, double InStartTime, double InEndTime, FTransform& OutTransform) const = 0;`
- L234 _public function_ `virtual bool ReadObjectEventsTimeline(uint64 InObjectId, TFunctionRef<void(const ObjectEventsTimeline&)> InCallback) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L240 _public function_ `virtual bool ReadObjectEvent(uint64 InObjectId, uint64 InMessageId, TFunctionRef<void(const FObjectEventMessage&)> InCallback) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L246 _public function_ `virtual void EnumerateSubobjects(uint64 InObjectId, TFunctionRef<void(uint64 SubobjectId)> InCallback) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L251 _public function_ `virtual TRange<double> GetObjectTraceLifetime(uint64 InObjectId) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L257 _public function_ `virtual TRange<double> GetObjectRecordingLifetime(uint64 InObjectId) const final` — `UE_DEPRECATED(5.7, "Use the version taking FObjectId instead")`
- L263 _function_ `inline const FObjectInfo* IGameplayProvider::FindObjectInfo(const uint64 InObjectId) const`
- L268 _function_ `inline const FObjectInfo& IGameplayProvider::GetObjectInfo(const uint64 InObjectId) const`

#### Free symbols / members of external scopes

- L184 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnObjectEndPlay, uint64 , double , const FObjectInfo& );` — Delegate fired when an object receives an end play event
- L184 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnObjectEndPlay, uint64 , double , const FObjectInfo& );` — Delegate fired when an object receives an end play event

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Public/ObjectAsTraceIdProxyArchiveReader.h` (Public)


#### struct `FObjectAsTraceIdProxyArchiveReader`  
`struct FObjectAsTraceIdProxyArchiveReader : public FObjectAsTraceIdProxyArchive`  
_L21-40_
- inherits: `FObjectAsTraceIdProxyArchive`
- L29 _public prototype_ `FObjectAsTraceIdProxyArchiveReader(FArchive& InInnerArchive, const class IGameplayProvider* InGameplayProvider);` — Creates and initializes a new instance. @param InInnerArchive - The inner archive to proxy. @param bInLoadIfFindFails - Indicates whether to try and load a ref'd object if we don't find it
- L31 _public prototype_ `virtual ~FObjectAsTraceIdProxyArchiveReader();`
- L33 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L34 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Obj) override;`
- L35 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& Value) override;`
- L36 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override;`
- L37 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`
- L39 _public member_ `const class IGameplayProvider* GameplayProvider;`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Public/RewindDebuggerPlaceholderTrack.h` (Public)


#### class `FRewindDebuggerPlaceholderTrack`  
`class FRewindDebuggerPlaceholderTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L8-22_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L11 _public function_ `FRewindDebuggerPlaceholderTrack(const FName& InObjectName, const FText& InDisplayName) : ObjectName(InObjectName), DisplayName(InDisplayName)`
- L17 _private function_ `virtual FName GetNameInternal() const override`
- L18 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L20 _private member_ `FName ObjectName;`
- L21 _private member_ `FText DisplayName;`

### `Plugins/Animation/GameplayInsights/Source/GameplayInsights/Public/SCurveTimelineView.h` (Public)


#### class `SCurveTimelineView`  
`class SCurveTimelineView : public SCompoundWidget`  
_L16-105_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SCurveTimelineView) : _ViewRange(TRange<double>(0,10)) , _DesiredSize(FVector2D(100.f,20.f)) , _RenderFill(false)`
- L37 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L40 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FTimelineCurveData>, CurveData);` — Data for curve to render
- L43 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, DesiredSize);` — Desired widget size
- L46 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, CurveColor);` — Curve Color
- L49 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, FillColor);` — Fill Color
- L52 _public prototype_ `SLATE_ATTRIBUTE(bool, RenderFill);` — Enable Fill rendering
- L55 _public prototype_ `SLATE_ATTRIBUTE(FText, TrackName);` — Track Name for tool tip
- L57 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L68 _public function_ `void SetFixedRange(float Min, float Max)` — render the curve with a fixed min/max range, rather than using the min/max from data
- L75 _public function_ `FText GetTrackName() const`
- L76 _public function_ `FText GetCurveToolTipInputText() const`
- L77 _public function_ `FText GetCurveToolTipOutputText() const`
- L81 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L82 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L83 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L85 _protected prototype_ `int32 PaintCurve(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;`
- L86 _protected prototype_ `void UpdateCurveToolTip(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L88 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L89 _protected member_ `TAttribute<TSharedPtr<FTimelineCurveData>> CurveData;`
- L90 _protected member_ `TAttribute<FVector2D> DesiredSize;`
- L91 _protected member_ `TAttribute<FLinearColor> CurveColor;`
- L92 _protected member_ `TAttribute<FLinearColor> FillColor;`
- L93 _protected member_ `TAttribute<bool> RenderFill;`
- L94 _protected member_ `TAttribute<FText> TrackName;`
- L96 _protected member_ `TSharedPtr<SToolTip> CurveToolTip;`
- L97 _protected member_ `FText CurveToolTipInputText;` — TSharedPtr<SToolTip> CurveToolTip;	  The tooltip control for the curve.
- L98 _protected member_ `FText CurveToolTipOutputText;`
- L100 _protected member_ `const FSlateBrush* FillBrush;`
- L102 _protected member_ `bool bUseFixedRange;`
- L103 _protected member_ `float FixedRangeMin;`
- L104 _protected member_ `float FixedRangeMax;`

#### struct `SCurveTimelineView::FTimelineCurveData`  
`struct FTimelineCurveData`  
_L19-29_
- L28 _public member_ `TArray<CurvePoint> Points;`

#### struct `SCurveTimelineView::FTimelineCurveData::CurvePoint`  
`struct CurvePoint`  
_L22-26_
- L24 _public member_ `double Time;`
- L25 _public member_ `float Value;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYINSIGHTS_API`
