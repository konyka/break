# Plugins / MassInsightsAnalysis

- module root: `Plugins/MassInsights/Source/MassInsightsAnalysis`
- headers: 1; symbols: 7
- symbol kinds: class=1, namespace=1, prototype=5
- PrivateDependencyModuleNames: CoreUObject, MassDeveloper, TraceAnalysis, TraceLog, TraceServices
- PublicDependencyModuleNames: Core

### `Plugins/MassInsights/Source/MassInsightsAnalysis/Private/MassInsightsAnalysisModule.h` (Private)


#### class `MassInsightsAnalysis::FMassInsightsAnalysisModule`  
`class FMassInsightsAnalysisModule : public IModuleInterface, TraceServices::IModule`  
_L14-28_
- inherits: `IModuleInterface,TraceServices::IModule`
- desc: Class to create and register the Analyzer and Provider for MassInsights. Implements both a plugin module and the TraceServices::IModule modular feature.
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L25 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L26 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace MassInsightsAnalysis`
