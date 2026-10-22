# Plugins / RenderGraphInsights

- module root: `Plugins/RenderGraphInsights/Source/RenderGraphInsights`
- headers: 8; symbols: 433
- symbol kinds: class=23, enum=6, enumerator=36, function=58, member=173, namespace=31, prototype=89, struct=8, typedef=8, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, RHI, RenderCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphAnalyzer.h` (Private)


#### class `UE::RenderGraphInsights::FRenderGraphAnalyzer`  
`class FRenderGraphAnalyzer : public UE::Trace::IAnalyzer`  
_L16-39_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FRenderGraphAnalyzer(TraceServices::IAnalysisSession& InSession, FRenderGraphProvider& InRenderGraphProvider);`
- L21 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L22 _public function_ `virtual void OnAnalysisEnd() override`
- L23 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L36 _private member_ `TraceServices::IAnalysisSession& Session;`
- L37 _private member_ `FRenderGraphProvider& Provider;`
- L38 _private member_ `bool bIsValidGraph;`

#### enum `UE::RenderGraphInsights::FRenderGraphAnalyzer::(anonymous)`  
``  
_L27-34_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RenderGraphInsights` (scope `UE`)
- L28 _enumerator_ `RouteId_Graph` (scope `UE::RenderGraphInsights::FRenderGraphAnalyzer::__anon8928e0930103`)
- L29 _enumerator_ `RouteId_GraphEnd` (scope `UE::RenderGraphInsights::FRenderGraphAnalyzer::__anon8928e0930103`)
- L30 _enumerator_ `RouteId_Scope` (scope `UE::RenderGraphInsights::FRenderGraphAnalyzer::__anon8928e0930103`)
- L31 _enumerator_ `RouteId_Pass` (scope `UE::RenderGraphInsights::FRenderGraphAnalyzer::__anon8928e0930103`)
- L32 _enumerator_ `RouteId_Buffer` (scope `UE::RenderGraphInsights::FRenderGraphAnalyzer::__anon8928e0930103`)
- L33 _enumerator_ `RouteId_Texture` (scope `UE::RenderGraphInsights::FRenderGraphAnalyzer::__anon8928e0930103`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphInsightsModule.h` (Private)


#### class `UE::RenderGraphInsights::FRenderGraphInsightsModule`  
`class FRenderGraphInsightsModule : public IModuleInterface`  
_L17-31_
- inherits: `IModuleInterface`
- L20 _public prototype_ `static FRenderGraphInsightsModule& Get();`
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _private member_ `FRenderGraphTraceModule TraceModule;`
- L29 _private member_ `FRenderGraphTimingViewExtender TimingViewExtender;`
- L30 _private member_ `TWeakPtr<FTabManager> InsightsTabManager;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderGraphInsights` (scope `UE`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphProvider.h` (Private)


#### class `UE::RenderGraphInsights::FPacket`  
`class FPacket`  
_L39-51_
- L41 _private prototype_ `INSIGHTS_DECLARE_RTTI_BASE(FPacket);`
- L43 _public prototype_ `virtual ~FPacket() = default;`
- L45 _public member_ `const FGraphPacket* Graph{};`
- L46 _public member_ `FString Name;`
- L47 _public member_ `double StartTime{};`
- L48 _public member_ `double EndTime{};`
- L50 _public prototype_ `FPacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FPassIntervalPacket`  
`class FPassIntervalPacket : public FPacket`  
_L53-61_
- inherits: `FPacket`
- L57 _public member_ `FRDGPassHandle FirstPass;`
- L58 _public member_ `FRDGPassHandle LastPass;`
- L60 _public prototype_ `FPassIntervalPacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FScopePacket`  
`class FScopePacket : public FPassIntervalPacket`  
_L63-72_
- inherits: `FPassIntervalPacket`
- L67 _public member_ `uint32 Depth{};`
- L69 _public member_ `mutable uint32 VisibleIndex = kInvalidVisibleIndex;`
- L71 _public prototype_ `FScopePacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FResourcePacket`  
`class FResourcePacket : public FPassIntervalPacket`  
_L74-99_
- inherits: `FPassIntervalPacket`
- L78 _public member_ `uint32 Index{};`
- L79 _public member_ `uint32 Order{};`
- L80 _public member_ `uint64 SizeInBytes{};`
- L81 _public member_ `FRHITransientAllocationStats::FAllocationArray TransientAllocations;`
- L83 _public member_ `TArray<FRDGPassHandle> Passes;`
- L85 _public member_ `mutable TArray<uint32, TInlineAllocator<1>> VisibleItems;`
- L87 _public member_ `FRDGPassHandle TransientAcquirePass;`
- L88 _public member_ `FRDGPassHandle TransientDiscardPass;`
- L90 _public member_ `bool bExternal{};`
- L91 _public member_ `bool bExtracted{};`
- L92 _public member_ `bool bCulled{};`
- L93 _public member_ `bool bTrackingSkipped{};`
- L94 _public member_ `bool bTransient{};`
- L95 _public member_ `bool bTransientUntracked{};`
- L96 _public member_ `bool bTransientCacheHit{};`
- L98 _public prototype_ `FResourcePacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FTexturePacket`  
`class FTexturePacket : public FResourcePacket`  
_L101-111_
- inherits: `FResourcePacket`
- L105 _public member_ `FRDGTextureHandle Handle;`
- L106 _public member_ `FRDGTextureHandle NextOwnerHandle;`
- L107 _public member_ `FRDGTextureHandle PrevousOwnerHandle;`
- L108 _public member_ `FRDGTextureDesc Desc;`
- L110 _public prototype_ `FTexturePacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FBufferPacket`  
`class FBufferPacket : public FResourcePacket`  
_L113-123_
- inherits: `FResourcePacket`
- L117 _public member_ `FRDGBufferHandle Handle;`
- L118 _public member_ `FRDGBufferHandle NextOwnerHandle;`
- L119 _public member_ `FRDGBufferHandle PrevousOwnerHandle;`
- L120 _public member_ `FRDGBufferDesc Desc;`
- L122 _public prototype_ `FBufferPacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FPassPacket`  
`class FPassPacket : public FPacket`  
_L125-151_
- inherits: `FPacket`
- L129 _public member_ `TArray<FRDGTextureHandle> Textures;`
- L130 _public member_ `TArray<FRDGBufferHandle> Buffers;`
- L132 _public member_ `mutable uint32 VisibleIndex = kInvalidVisibleIndex;`
- L134 _public member_ `FRDGPassHandle Handle;`
- L135 _public member_ `FRDGPassHandle GraphicsForkPass;`
- L136 _public member_ `FRDGPassHandle GraphicsJoinPass;`
- L137 _public member_ `ERDGPassFlags Flags{};`
- L138 _public member_ `ERHIPipeline Pipeline{};`
- L139 _public member_ `bool bCulled{};`
- L140 _public member_ `bool bAsyncComputeBegin{};`
- L141 _public member_ `bool bAsyncComputeEnd{};`
- L142 _public member_ `bool bSkipRenderPassBegin{};`
- L143 _public member_ `bool bSkipRenderPassEnd{};`
- L144 _public member_ `bool bParallelExecuteBegin{};`
- L145 _public member_ `bool bParallelExecuteEnd{};`
- L146 _public member_ `bool bParallelExecute{};`
- L147 _public member_ `bool bParallelExecuteAllowed{};`
- L148 _public member_ `bool bParallelExecuteAsyncAllowed{};`
- L150 _public prototype_ `FPassPacket(const UE::Trace::IAnalyzer::FOnEventContext& Context);`

#### class `UE::RenderGraphInsights::FGraphPacket`  
`class FGraphPacket : public FPacket`  
_L153-201_
- inherits: `FPacket`
- L157 _public member_ `double NormalizedPassDuration{};`
- L159 _public member_ `TraceServices::TPagedArray<FScopePacket> Scopes;`
- L160 _public member_ `TraceServices::TPagedArray<FPassPacket> Passes;`
- L161 _public member_ `TraceServices::TPagedArray<FTexturePacket> Textures;`
- L162 _public member_ `TraceServices::TPagedArray<FBufferPacket> Buffers;`
- L164 _public member_ `TMap<FRDGBufferHandle, const FBufferPacket*> BufferHandleToPreviousOwner;`
- L165 _public member_ `TMap<FRDGTextureHandle, const FTexturePacket*> TextureHandleToPreviousOwner;`
- L167 _public member_ `mutable uint32 VisibleIndex = kInvalidVisibleIndex;`
- L169 _public member_ `uint32 ScopeDepth{};`
- L170 _public member_ `uint32 PassCount{};`
- L172 _public member_ `FRHITransientAllocationStats TransientAllocationStats;`
- L173 _public member_ `TArray<uint64> TransientMemoryRangeByteOffsets;`
- L175 _public prototype_ `FGraphPacket(TraceServices::ILinearAllocator& Allocator, const UE::Trace::IAnalyzer::FOnEventContext& Context);`
- L177 _public function_ `const FPassPacket* GetProloguePass() const`
- L182 _public function_ `const FPassPacket* GetEpiloguePass() const`
- L187 _public function_ `const FPassPacket* GetPass(FRDGPassHandle Handle) const`
- L192 _public function_ `const FTexturePacket* GetTexture(FRDGTextureHandle Handle) const`
- L197 _public function_ `const FBufferPacket* GetBuffer(FRDGBufferHandle Handle) const`

#### class `UE::RenderGraphInsights::FRenderGraphProvider`  
`class FRenderGraphProvider : public TraceServices::IProvider`  
_L203-232_
- inherits: `TraceServices::IProvider`
- L206 _public member_ `static FName ProviderName;`
- L208 _public prototype_ `FRenderGraphProvider(TraceServices::IAnalysisSession& InSession);`
- L210 _public prototype_ `void AddGraph(const UE::Trace::IAnalyzer::FOnEventContext& Context, double& OutEndTime);`
- L211 _public prototype_ `void AddGraphEnd();`
- L212 _public prototype_ `void AddScope(FScopePacket Scope);`
- L213 _public prototype_ `void AddPass(FPassPacket Pass);`
- L214 _public prototype_ `void AddTexture(FTexturePacket Texture);`
- L215 _public prototype_ `void AddBuffer(FBufferPacket Buffer);`
- L217 _public typedef_ `using TGraphTimeline = TraceServices::TIntervalTimeline<TSharedPtr<FGraphPacket>>;`
- L218 _public function_ `const TGraphTimeline& GetGraphTimeline() const`
- L225 _private prototype_ `void SetupResource(FResourcePacket& ResourcePacket);`
- L227 _private member_ `TraceServices::IAnalysisSession& Session;`
- L229 _private member_ `TSharedPtr<FGraphPacket> CurrentGraph;`
- L231 _private member_ `TGraphTimeline GraphTimeline;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderGraphInsights` (scope `UE`)
- L21 _function_ `inline void SanitizeName(FString& Name)` (scope `UE::RenderGraphInsights`)
- L29 _function_ `inline FString GetSanitizedName(FString Name)` (scope `UE::RenderGraphInsights`)
- L37 _variable_ `const uint32 kInvalidVisibleIndex = ~0u;` (scope `UE::RenderGraphInsights`)
- L234 _function_ `inline bool Intersects(const FPassIntervalPacket& A, const FPassPacket& B)` (scope `UE::RenderGraphInsights`)
- L239 _function_ `inline bool Intersects(const FPassIntervalPacket& A, const FPassIntervalPacket& B)` (scope `UE::RenderGraphInsights`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphTimingViewExtender.h` (Private)


#### class `UE::RenderGraphInsights::FRenderGraphTimingViewExtender`  
`class FRenderGraphTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L18-36_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L22 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L23 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L24 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L25 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L35 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;` — The data we host per-session

#### struct `UE::RenderGraphInsights::FRenderGraphTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L29-32_
- L31 _public member_ `TUniquePtr<FRenderGraphTimingViewSession> SharedData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L9 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGraphInsights` (scope `UE`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphTimingViewSession.h` (Private)


#### class `UE::RenderGraphInsights::FRenderGraphTimingViewSession`  
`class FRenderGraphTimingViewSession`  
_L19-45_
- L22 _public prototype_ `FRenderGraphTimingViewSession() = default;`
- L24 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L25 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L26 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L27 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L30 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const` — Get the last cached analysis session
- L33 _public function_ `bool IsAnalysisSessionValid() const` — Check whether the analysis session is valid
- L36 _public prototype_ `void ToggleRenderGraphTrack();` — Show/Hide the RenderGraph track
- L38 _public function_ `UE::Insights::Timing::ITimingViewSession* GetTimingViewSession() const`
- L41 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L42 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession;`
- L43 _private member_ `TSharedPtr<FRenderGraphTrack> Track;`
- L44 _private member_ `bool bTrackVisible = true;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)
- L9 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGraphInsights` (scope `UE`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphTraceModule.h` (Private)


#### class `UE::RenderGraphInsights::FRenderGraphTraceModule`  
`class FRenderGraphTraceModule : public TraceServices::IModule`  
_L12-25_
- inherits: `TraceServices::IModule`
- L16 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L17 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L18 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L19 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L20 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L24 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGraphInsights` (scope `UE`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphTrack.h` (Private)


#### class `UE::RenderGraphInsights::FBoundingBox`  
`class FBoundingBox`  
_L23-35_
- L26 _public prototype_ `FBoundingBox() = default;`
- L28 _public function_ `FBoundingBox(FVector2D InMin, FVector2D InMax) : Min(InMin) , Max(InMax)`
- L33 _public member_ `FVector2D Min = FVector2D::ZeroVector;`
- L34 _public member_ `FVector2D Max = FVector2D::ZeroVector;`

#### class `UE::RenderGraphInsights::FVisibleItem`  
`class FVisibleItem`  
_L37-79_
- L40 _public function_ `FVisibleItem(const FTimingTrackViewport& InViewport, const FPacket& InPacket, uint32 InColor, double InStartTime, double InEndTime, float InDepthY, float InDepthH = 1.0f) : Packet(&InPacket) , Name(*InPacket.Name) , StartTime(InStartTime) , EndTime(InEndTime) , DepthY(InDepthY) , DepthH(InDepthH) , Color(InColor)`
- L53 _public function_ `virtual bool Intersects(float InSlateX, float InDepthY, bool& bOutFilterable) const`
- L59 _public function_ `bool Intersects(float InSlateX, float InDepthY) const`
- L65 _public prototype_ `FBoundingBox GetBoundingBox(const FTimingViewLayout& Layout) const;`
- L67 _public prototype_ `virtual void Draw(FRenderGraphTrackDrawStateBuilder& Builder) const;`
- L69 _public member_ `const FPacket* Packet{};`
- L70 _public member_ `const TCHAR* Name{};`
- L71 _public member_ `double StartTime{};`
- L72 _public member_ `double EndTime{};`
- L73 _public member_ `float DepthY{};`
- L74 _public member_ `float DepthH{};`
- L75 _public member_ `float SlateX{};`
- L76 _public member_ `float SlateW{};`
- L77 _public member_ `uint32 Color{};`
- L78 _public member_ `uint32 Index{};`

#### class `UE::RenderGraphInsights::TVisibleItemHelper`  
`template <typename InPacketType> class TVisibleItemHelper : public FVisibleItem`  
_L82-95_
- inherits: `FVisibleItem`
- L85 _public typedef_ `using PacketType = InPacketType;`
- L87 _public function_ `TVisibleItemHelper(const FTimingTrackViewport& Viewport, const PacketType& InPacket, uint32 InColor, double InStartTime, double InEndTime, float InDepthY, float InDepthH = 1.0f) : FVisibleItem(Viewport, InPacket, InColor, InStartTime, InEndTime, InDepthY, InDepthH)`
- L91 _public function_ `const PacketType& GetPacket() const`

#### class `UE::RenderGraphInsights::FVisiblePass`  
`class FVisiblePass final : public TVisibleItemHelper<FPassPacket>`  
_L97-116_
- inherits: `TVisibleItemHelper<FPassPacket>`
- L100 _public function_ `FVisiblePass(const FTimingTrackViewport& Viewport, const FPassPacket& InPacket, uint32 InColor, double InStartTime, double InEndTime, float InDepthY, float InDepthH = 1.0f) : TVisibleItemHelper(Viewport, InPacket, InColor, InStartTime, InEndTime, InDepthY, InDepthH)`
- L104 _public function_ `bool Intersects(float InSlateX, float InDepthY, bool& bOutFilterable) const override`

#### class `UE::RenderGraphInsights::TVisibleResourceHelper`  
`template <typename InPacketType> class TVisibleResourceHelper : public FVisibleItem`  
_L121-137_
- inherits: `FVisibleItem`
- L124 _public typedef_ `using PacketType = InPacketType;`
- L126 _public function_ `TVisibleResourceHelper(const FTimingTrackViewport& Viewport, const PacketType& InPacket, uint32 InColor, double InStartTime, double InEndTime, float InDepthY, float InDepthH = 1.0f, uint32 InAllocationIndex = 0) : FVisibleItem(Viewport, InPacket, InColor, InStartTime, InEndTime, InDepthY, InDepthH) , AllocationIndex(InAllocationIndex)`
- L131 _public function_ `const PacketType& GetPacket() const`
- L136 _public member_ `uint32 AllocationIndex;`

#### class `UE::RenderGraphInsights::FVisibleGraph`  
`class FVisibleGraph final : public TVisibleItemHelper<FGraphPacket>`  
_L142-201_
- inherits: `TVisibleItemHelper<FGraphPacket>`
- L145 _public function_ `FVisibleGraph(const FTimingTrackViewport& Viewport, const FGraphPacket& InGraph, uint32 InColor, float InDepthH) : TVisibleItemHelper(Viewport, InGraph, InColor, InGraph.StartTime, InGraph.EndTime, 0.0f, InDepthH)`
- L149 _public prototype_ `void AddScope(const FVisibleScope& VisibleScope);`
- L150 _public prototype_ `void AddPass(const FVisiblePass& VisiblePass);`
- L151 _public prototype_ `void AddTexture(const FVisibleTexture& VisibleTexture);`
- L152 _public prototype_ `void AddBuffer(const FVisibleBuffer& VisibleBuffer);`
- L154 _public prototype_ `void Reset();`
- L156 _public prototype_ `const FVisibleItem* FindItem(float InSlateX, float InDepthY) const;`
- L158 _public function_ `const FVisibleScope& GetVisibleScope(const FScopePacket& Scope) const`
- L163 _public function_ `const FVisiblePass& GetVisiblePass(const FPassPacket& Pass) const`
- L169 _public function_ `template <typename FunctionType> void EnumerateVisibleTextures(const FTexturePacket& Texture, FunctionType Function) const`
- L178 _public function_ `template <typename FunctionType> void EnumerateVisibleBuffers(const FBufferPacket& Buffer, FunctionType Function) const`
- L186 _public prototype_ `void Draw(FRenderGraphTrackDrawStateBuilder& Builder) const override;`
- L188 _public function_ `bool IsCulled() const`
- L193 _public member_ `TArray<FVisibleScope> Scopes;`
- L194 _public member_ `TArray<FVisiblePass> Passes;`
- L195 _public member_ `TArray<FVisibleTexture> Textures;`
- L196 _public member_ `TArray<FVisibleBuffer> Buffers;`
- L197 _public member_ `TArray<uint32> AsyncComputePasses;`
- L198 _public member_ `TArray<float> TransientMemoryRangeDepthOffsets;`
- L199 _public member_ `float HeaderEndDepth{};`
- L200 _public member_ `float HeaderPassBarDepth{};`

#### class `UE::RenderGraphInsights::FRenderGraphTrack`  
`class FRenderGraphTrack final : public FBaseTimingTrack`  
_L203-351_
- inherits: `FBaseTimingTrack`
- L206 _private typedef_ `using Super = FBaseTimingTrack;`
- L209 _public prototype_ `FRenderGraphTrack(const FRenderGraphTimingViewSession& InSharedData);`
- L212 _public prototype_ `void Reset() override;`
- L213 _public prototype_ `void PreUpdate(const ITimingTrackUpdateContext& Context) override;`
- L214 _public prototype_ `void Update(const ITimingTrackUpdateContext& Context) override;`
- L215 _public prototype_ `void PostUpdate(const ITimingTrackUpdateContext& Context) override;`
- L216 _public prototype_ `void Draw(const ITimingTrackDrawContext& Context) const override;`
- L217 _public prototype_ `void PostDraw(const ITimingTrackDrawContext& Context) const override;`
- L218 _public prototype_ `void DrawEvent(const ITimingTrackDrawContext& Context, const ITimingEvent& InTimingEvent, EDrawEventMode InDrawMode) const override;`
- L219 _public prototype_ `const TSharedPtr<const ITimingEvent> GetEvent(float InPosX, float InPosY, const FTimingTrackViewport& Viewport) const override;`
- L220 _public prototype_ `TSharedPtr<ITimingEventFilter> GetFilterByEvent(const TSharedPtr<const ITimingEvent> InTimingEvent) const;`
- L221 _public prototype_ `void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L222 _public prototype_ `void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& HoveredTimingEvent) const override;`
- L226 _private member_ `const FRenderGraphTimingViewSession& SharedData;`
- L228 _private prototype_ `void BuildDrawState(FRenderGraphTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context);`
- L229 _private prototype_ `void BuildFilteredDrawState(FRenderGraphTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context);`
- L231 _private function_ `FVisibleGraph& AddVisibleGraph(const FTimingTrackViewport& Viewport, const FGraphPacket& Graph, uint32 Color)`
- L247 _private function_ `const FVisibleGraph* GetVisibleGraph(const FGraphPacket& Packet) const`
- L256 _private prototype_ `float TransientByteOffsetToDepth(uint64 ByteOffset) const;`
- L257 _private prototype_ `float TransientByteOffsetToDepthAligned(uint64 ByteOffset) const;`
- L258 _private prototype_ `float TransientByteOffsetToSlateY(const FTimingViewLayout& Layout, uint64 ByteOffset) const;`
- L260 _private member_ `float MouseSlateX{};`
- L261 _private member_ `float MouseSlateY{};`
- L262 _private member_ `float MouseDepthY{};`
- L264 _private member_ `TArray<FVisibleGraph> VisibleGraphs;`
- L276 _private member_ `TArray<FSpline> Splines;`
- L278 _private prototype_ `uint32 GetTextureColor(const FTexturePacket& Texture, uint64 MaxSizeInBytes) const;`
- L279 _private prototype_ `uint32 GetBufferColor(const FBufferPacket& Buffer, uint64 MaxSizeInBytes) const;`
- L281 _private function_ `bool ShowTextures() const`
- L282 _private function_ `bool ShowBuffers() const`
- L283 _private function_ `bool ShowTransient() const`
- L284 _private function_ `bool ShowExternal() const`
- L285 _private function_ `bool ShowInternal() const`
- L286 _private function_ `bool ShowExtracted() const`
- L287 _private function_ `bool ShowPooled() const`
- L288 _private function_ `bool ShowTracked() const`
- L302 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(FRenderGraphTrack::EResourceShow);`
- L327 _private member_ `EResourceShow ResourceShow = EResourceShow::All;`
- L328 _private member_ `EResourceSort ResourceSort = EResourceSort::Creation;`
- L329 _private member_ `EResourceColor ResourceColor = EResourceColor::Name;`
- L330 _private member_ `EVisualizer Visualizer = EVisualizer::Resources;`
- L331 _private member_ `FString FilterText;`
- L332 _private member_ `float FilterSize{};`
- L333 _private member_ `uint64 TransientBytesPerDepthSlot = 1024 * 1024;`
- L335 _private member_ `FTooltipDrawState SelectedTooltipState;`
- L337 _private member_ `int32 NumLanes;`
- L338 _private member_ `TSharedRef<struct FRenderGraphTrackDrawState> DrawState;`
- L339 _private member_ `TSharedRef<struct FRenderGraphTrackDrawState> FilteredDrawState;`
- L350 _private member_ `FFilteredDrawStateInfo FilteredDrawStateInfo;`

#### struct `UE::RenderGraphInsights::FRenderGraphTrack::FSpline`  
`struct FSpline`  
_L266-274_
- L268 _public member_ `float Thickness{};`
- L269 _public member_ `FVector2D Start = FVector2D::ZeroVector;`
- L270 _public member_ `FVector2D StartDir = FVector2D::ZeroVector;`
- L271 _public member_ `FVector2D End = FVector2D::ZeroVector;`
- L272 _public member_ `FVector2D EndDir = FVector2D::ZeroVector;`
- L273 _public member_ `FLinearColor Tint = FLinearColor::White;`

#### enum `UE::RenderGraphInsights::FRenderGraphTrack::EResourceShow`  
`enum class EResourceShow`  
_L290-301_
- L292 _public enumerator_ `Textures = 1 << 0`
- L293 _public enumerator_ `Buffers = 1 << 1`
- L294 _public enumerator_ `Transient = 1 << 2`
- L295 _public enumerator_ `External = 1 << 3`
- L296 _public enumerator_ `Internal = 1 << 4`
- L297 _public enumerator_ `Extracted = 1 << 5`
- L298 _public enumerator_ `Pooled = 1 << 6`
- L299 _public enumerator_ `Tracked = 1 << 7`
- L300 _public enumerator_ `All = Textures | Buffers | Transient | External | Internal | Extracted | Pooled | Tracked`

#### enum `UE::RenderGraphInsights::FRenderGraphTrack::EResourceSort`  
`enum class EResourceSort`  
_L304-311_
- L306 _public enumerator_ `Creation`
- L307 _public enumerator_ `LargestSize`
- L308 _public enumerator_ `SmallestSize`
- L309 _public enumerator_ `StartOfLifetime`
- L310 _public enumerator_ `EndOfLifetime`

#### enum `UE::RenderGraphInsights::FRenderGraphTrack::EResourceColor`  
`enum class EResourceColor`  
_L313-319_
- L315 _public enumerator_ `Name`
- L316 _public enumerator_ `Type`
- L317 _public enumerator_ `Size`
- L318 _public enumerator_ `TransientCache`

#### enum `UE::RenderGraphInsights::FRenderGraphTrack::EVisualizer`  
`enum class EVisualizer`  
_L321-325_
- L323 _public enumerator_ `Resources`
- L324 _public enumerator_ `TransientMemory`

#### struct `UE::RenderGraphInsights::FRenderGraphTrack::FFilteredDrawStateInfo`  
`struct FFilteredDrawStateInfo`  
_L341-349_
- L343 _public member_ `double ViewportStartTime = 0.0;`
- L344 _public member_ `double ViewportScaleX = 0.0;`
- L345 _public member_ `double LastBuildDuration = 0.0;`
- L346 _public member_ `TWeakPtr<ITimingEventFilter> LastEventFilter;`
- L347 _public member_ `uint32 Counter = 0;`
- L348 _public member_ `mutable float Opacity = 0.0f;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGraphInsights` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderGraphInsights` (scope `UE`)
- L118 _typedef_ `using FVisibleScope = TVisibleItemHelper<FScopePacket>;` (scope `UE::RenderGraphInsights`)
- L139 _typedef_ `using FVisibleTexture = TVisibleResourceHelper<FTexturePacket>;` (scope `UE::RenderGraphInsights`)
- L140 _typedef_ `using FVisibleBuffer = TVisibleResourceHelper<FBufferPacket>;` (scope `UE::RenderGraphInsights`)
- L353 _prototype_ `ENUM_CLASS_FLAGS(FRenderGraphTrack::EResourceShow);` (scope `UE::RenderGraphInsights`)

### `Plugins/RenderGraphInsights/Source/RenderGraphInsights/Private/RenderGraphTrackDrawHelper.h` (Private)


#### enum `UE::RenderGraphInsights::EDrawLayer`  
`enum class EDrawLayer : int32`  
_L49-61_
- L51 _public enumerator_ `Background`
- L52 _public enumerator_ `EventBorder`
- L53 _public enumerator_ `EventFill`
- L54 _public enumerator_ `EventText`
- L55 _public enumerator_ `EventHighlight`
- L56 _public enumerator_ `Relation`
- L57 _public enumerator_ `HeaderBackground`
- L58 _public enumerator_ `HeaderText`
- L59 _public enumerator_ `Foreground`
- L60 _public enumerator_ `Count`

#### struct `UE::RenderGraphInsights::FSplinePrimitive`  
`struct FSplinePrimitive`  
_L63-71_
- L65 _public member_ `float Thickness = 1.0f;`
- L66 _public member_ `FVector2D Start = FVector2D::ZeroVector;`
- L67 _public member_ `FVector2D StartDir = FVector2D::ZeroVector;`
- L68 _public member_ `FVector2D End = FVector2D::ZeroVector;`
- L69 _public member_ `FVector2D EndDir = FVector2D::ZeroVector;`
- L70 _public member_ `FLinearColor Tint = FLinearColor::White;`

#### struct `UE::RenderGraphInsights::FRenderGraphTrackDrawState`  
`struct FRenderGraphTrackDrawState`  
_L73-107_
- L93 _public function_ `void Reset()`
- L102 _public member_ `TArray<FBoxPrimitive> Boxes;`
- L103 _public member_ `TArray<FBoxPrimitive> InsideBoxes;`
- L104 _public member_ `TArray<FBoxPrimitive> Borders;`
- L105 _public member_ `TArray<FTextPrimitive> Texts;`
- L106 _public member_ `TArray<FSplinePrimitive> Splines;`

#### struct `UE::RenderGraphInsights::FRenderGraphTrackDrawState::FBoxPrimitive`  
`struct FBoxPrimitive`  
_L75-82_
- L77 _public member_ `float DepthY{};`
- L78 _public member_ `float DepthH{};`
- L79 _public member_ `float X{};`
- L80 _public member_ `float W{};`
- L81 _public member_ `FLinearColor Color = FLinearColor::White;`

#### struct `UE::RenderGraphInsights::FRenderGraphTrackDrawState::FTextPrimitive`  
`struct FTextPrimitive`  
_L84-91_
- L86 _public member_ `float Depth{};`
- L87 _public member_ `float X{};`
- L88 _public member_ `FString Text{};`
- L89 _public member_ `bool bWhite{};`
- L90 _public member_ `FLinearColor Color = FLinearColor::White;`

#### class `UE::RenderGraphInsights::FRenderGraphTrackDrawStateBuilder`  
`class FRenderGraphTrackDrawStateBuilder`  
_L109-159_
- L123 _public prototype_ `explicit FRenderGraphTrackDrawStateBuilder(FRenderGraphTrackDrawState& InState, const FTimingTrackViewport& InViewport);`
- L125 _public prototype_ `FRenderGraphTrackDrawStateBuilder(const FRenderGraphTrackDrawStateBuilder&) = delete;`
- L126 _public prototype_ `FRenderGraphTrackDrawStateBuilder& operator=(const FRenderGraphTrackDrawStateBuilder&) = delete;`
- L128 _public function_ `const FTimingTrackViewport& GetViewport() const`
- L130 _public typedef_ `using GetEventNameCallback = TFunctionRef<const FString(float )>;`
- L132 _public prototype_ `void AddEvent(double InEventStartTime, double InEventEndTime, uint32 InEventDepth, const TCHAR* InEventName, uint64 InEventType = 0, uint32 InEventColor = 0);`
- L133 _public prototype_ `void AddEvent(double InEventStartTime, double InEventEndTime, uint32 InEventDepth, uint32 InEventColor, GetEventNameCallback InGetEventNameCallback);`
- L134 _public prototype_ `void AddEvent(double InEventStartTime, double InEventEndTime, float InEventDepthY, float InEventDepthH, uint32 InEventColor, GetEventNameCallback InGetEventNameCallback);`
- L135 _public prototype_ `void Flush();`
- L137 _public function_ `void AddSpline(const FSplinePrimitive& Spline)`
- L142 _public function_ `int32 GetMaxDepth() const`
- L145 _private prototype_ `void FlushBox(const FBoxData& Box, const int32 Depth);`
- L147 _private prototype_ `static void AppendDurationToEventName(FString& InOutEventName, const double InDuration);`
- L149 _private member_ `FRenderGraphTrackDrawState& DrawState;` — cached draw state to build
- L150 _private member_ `const FTimingTrackViewport& Viewport;`
- L152 _private member_ `int32 MaxDepth = -1;`
- L153 _private member_ `int32 MaxDepthCached = -1;`
- L155 _private member_ `TArray<float> LastEventX2;` — X2 value for last event on each depth
- L156 _private member_ `TArray<FBoxData> LastBox;`
- L158 _private member_ `const FSlateFontInfo EventFont;`

#### struct `UE::RenderGraphInsights::FRenderGraphTrackDrawStateBuilder::FBoxData`  
`struct FBoxData`  
_L112-120_
- L114 _public member_ `float X1{};`
- L115 _public member_ `float X2{};`
- L116 _public member_ `uint32 Color{};`
- L117 _public member_ `FLinearColor LinearColor;`
- L119 _public function_ `void Reset()`

#### class `UE::RenderGraphInsights::FRenderGraphTrackDrawHelper`  
`class FRenderGraphTrackDrawHelper final`  
_L161-207_
- L164 _public prototype_ `explicit FRenderGraphTrackDrawHelper(const ITimingTrackDrawContext& Context);`
- L166 _public prototype_ `FRenderGraphTrackDrawHelper(const FRenderGraphTrackDrawHelper&) = delete;`
- L167 _public prototype_ `FRenderGraphTrackDrawHelper& operator=(const FRenderGraphTrackDrawHelper&) = delete;`
- L169 _public function_ `const FDrawContext& GetDrawContext() const`
- L170 _public function_ `const FTimingTrackViewport& GetViewport() const`
- L172 _public prototype_ `void DrawEvents(const FRenderGraphTrackDrawState& DrawState, const FBaseTimingTrack& Track) const;`
- L173 _public prototype_ `void DrawFadedEvents(const FRenderGraphTrackDrawState& DrawState, const FBaseTimingTrack& Track, const float Opacity = 0.1f) const;`
- L175 _public prototype_ `void DrawTimingEventHighlight(const FBaseTimingTrack& Track, double StartTime, double EndTime, float DepthY, float DepthH, EDrawEventMode Mode) const;`
- L177 _public prototype_ `void DrawTrackHeader(const FBaseTimingTrack& Track) const;`
- L178 _public prototype_ `void DrawTrackHeader(const FBaseTimingTrack& Track, const int32 HeaderLayerId, const int32 HeaderTextLayerId) const;`
- L180 _public prototype_ `void DrawSpline(const FBaseTimingTrack& Track, const FSplinePrimitive& Spline, EDrawLayer Layer) const;`
- L182 _public prototype_ `void DrawBox(const FBaseTimingTrack& Track, float SlateX, float DepthY, float SlateW, float DepthH, FLinearColor Color, EDrawLayer Layer) const;`
- L184 _public prototype_ `FLinearColor GetTrackNameTextColor(const FBaseTimingTrack& Track) const;`
- L186 _public function_ `FLinearColor GetEdgeColor() const`
- L187 _public function_ `const FSlateFontInfo& GetEventFont() const`
- L188 _public function_ `const FSlateBrush* GetWhiteBrush() const`
- L189 _public function_ `int32 GetFirstLayerId() const`
- L190 _public function_ `int32 GetNumLayerIds() const`
- L194 _private member_ `const FDrawContext& DrawContext;`
- L195 _private member_ `const FTimingTrackViewport& Viewport;`
- L196 _private member_ `const ITimingViewDrawHelper& ParentHelper;`
- L198 _private member_ `const FSlateBrush* WhiteBrush;`
- L199 _private member_ `const FSlateBrush* EventBorderBrush;`
- L200 _private member_ `const FSlateBrush* HoveredEventBorderBrush;`
- L201 _private member_ `const FSlateBrush* SelectedEventBorderBrush;`
- L202 _private member_ `const FLinearColor ValidAreaColor;`
- L203 _private member_ `const FLinearColor InvalidAreaColor;`
- L204 _private member_ `const FLinearColor EdgeColor;`
- L205 _private member_ `const FSlateFontInfo EventFont;`
- L206 _private member_ `const int32 ReservedLayerId{};`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RenderGraphInsights` (scope `UE`)
- L22 _function_ `inline float GetChildLaneY(const FTimingViewLayout& Layout, float DepthY)` (scope `UE::RenderGraphInsights`)
- L27 _function_ `inline float GetLaneY(float TopLaneY, const FTimingViewLayout& Layout, float DepthY)` (scope `UE::RenderGraphInsights`)
- L32 _function_ `inline float GetLaneY(const FTimingViewLayout& Layout, float DepthY)` (scope `UE::RenderGraphInsights`)
- L37 _function_ `inline float GetLaneHeight(const FTimingViewLayout& Layout, float DepthH)` (scope `UE::RenderGraphInsights`)
- L42 _function_ `inline float GetDepthFromLaneY(const FTimingViewLayout& Layout, float Y)` (scope `UE::RenderGraphInsights`)
