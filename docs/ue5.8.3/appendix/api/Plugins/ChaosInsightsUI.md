# Plugins / ChaosInsightsUI

- module root: `Plugins/ChaosInsights/Source/ChaosInsightsUI`
- headers: 2; symbols: 24
- symbol kinds: class=3, member=6, namespace=2, prototype=13
- PrivateDependencyModuleNames: ChaosInsightsAnalysis, Core, CoreUObject, InputCore, Slate, SlateCore, TraceInsights, TraceInsightsCore, TraceServices

### `Plugins/ChaosInsights/Source/ChaosInsightsUI/Private/ChaosInsightsUIModule.h` (Private)


#### class `ChaosInsights::FChaosInsightsUIModule`  
`class FChaosInsightsUIModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `FLockRegionsSharedState TimingViewExtender;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ChaosInsights`

### `Plugins/ChaosInsights/Source/ChaosInsightsUI/Private/LockRegionTrack.h` (Private)


#### class `ChaosInsights::FLockRegionsSharedState`  
`class FLockRegionsSharedState : public UE::Insights::Timing::ITimingViewExtender, public TSharedFromThis<FLockRegionsSharedState>`  
_L14-35_
- inherits: `UE::Insights::Timing::ITimingViewExtender,TSharedFromThis<FLockRegionsSharedState>`
- L22 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;` — ITimingViewExtender interface
- L23 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L24 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L26 _public prototype_ `void ShowHideRegionsTrack();`
- L27 _public prototype_ `bool IsRegionsTrackVisible() const;`
- L30 _private prototype_ `bool IsCurrentSession(UE::Insights::Timing::ITimingViewSession& Session);`
- L32 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingView = nullptr;`
- L33 _private member_ `TSharedPtr<FLockRegionsTrack> LockRegionsTrack;`
- L34 _private member_ `bool bShowHideRegionsTrack = true;`

#### class `ChaosInsights::FLockRegionsTrack`  
`class FLockRegionsTrack : public FTimingEventsTrack`  
_L37-55_
- inherits: `FTimingEventsTrack`
- L42 _public prototype_ `FLockRegionsTrack(FLockRegionsSharedState& InSharedState);`
- L45 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L46 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L47 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L50 _protected prototype_ `bool FindRegionEvent(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const ChaosInsightsAnalysis::FLockRegion&)> InFoundPredicate) const;`
- L53 _private member_ `FLockRegionsSharedState& SharedState;`
- L54 _private member_ `TSharedPtr<const TraceServices::IAnalysisSession> AnalysisSession;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ChaosInsights`
