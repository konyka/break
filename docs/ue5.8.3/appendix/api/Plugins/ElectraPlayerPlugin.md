# Plugins / ElectraPlayerPlugin

- module root: `Plugins/Media/ElectraPlayer/Source/ElectraPlayerPlugin`
- headers: 1; symbols: 8
- symbol kinds: class=1, prototype=7
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: Core, ElectraPlayerRuntime, Engine, RHI
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerPlugin/Public/IElectraPlayerPluginModule.h` (Public)


#### class `IElectraPlayerPluginModule`  
`class IElectraPlayerPluginModule : public IModuleInterface`  
_L16-41_
- inherits: `IModuleInterface`
- desc: Interface for the ElectraPlayerPlugin module.
- L20 _public prototype_ `virtual ~IElectraPlayerPluginModule() = default;`
- L26 _public prototype_ `virtual bool IsInitialized() const = 0;` — Is the ElectraPlayerPlugin module initialized? @return True if the module is initialized.
- L34 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Creates a media player @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L36 _public prototype_ `virtual void SendAnalyticMetrics(const TSharedPtr<IAnalyticsProviderET>& AnalyticsProvider, const FGuid& PlayerGuid) = 0;`
- L37 _public prototype_ `virtual void SendAnalyticMetricsPerMinute(const TSharedPtr<IAnalyticsProviderET>& AnalyticsProvider) = 0;`
- L39 _public prototype_ `virtual void ReportVideoStreamingError(const FGuid& PlayerGuid, const FString& LastError) = 0;`
- L40 _public prototype_ `virtual void ReportSubtitlesMetrics(const FGuid& PlayerGuid, const FString& URL, double ResponseTime, const FString& LastError) = 0;`
