# Plugins / ImgMediaFactory

- module root: `Plugins/Media/ImgMedia/Source/ImgMediaFactory`
- headers: 2; symbols: 26
- symbol kinds: class=1, delegate=2, function=1, macro=1, member=14, prototype=7
- DynamicallyLoadedModuleNames: ImgMedia, Media, Settings, TmvMedia
- PrivateIncludePathModuleNames: ImgMedia, Media, Settings, TmvMedia
- PublicDependencyModuleNames: Core, CoreUObject, TimeManagement

### `Plugins/Media/ImgMedia/Source/ImgMediaFactory/Private/ImgMediaFactoryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImgMediaFactory, Log, All);` — Log category for the ImgMedia module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImgMediaFactory, Log, All);` — Log category for the ImgMedia module.

### `Plugins/Media/ImgMedia/Source/ImgMediaFactory/Public/ImgMediaSettings.h` (Public)


#### class `UImgMediaSettings`  
`class UImgMediaSettings : public UObject`  
_L20-175_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- desc: Settings for the ImgMedia module.
- L29 _public member_ `FFrameRate DefaultFrameRate;` — `UPROPERTY(config, EditAnywhere, Category=General)` — Default frame rate to use if none was specified in image sequence or media source (default = 1/24).
- L33 _public member_ `bool BandwidthThrottlingEnabled;` — `UPROPERTY(config, EditAnywhere, Category = General)` — If there is not enough bandwidth to play the media, then lower it (for example by skipping frames) to try and get playback.
- L39 _public member_ `float CacheBehindPercentage;` — `UPROPERTY(config, EditAnywhere, Category=Caching, meta=(ClampMin=0.0, ClampMax=100.0))` — Percentage of cache to use for frames behind the play head (default = 25%).
- L48 _public member_ `float CacheSizeGB;` — `UPROPERTY(config, EditAnywhere, Category=Caching, meta=(ClampMin=0))` — Maximum memory size of the pre-caching sliding interval (in GB; default = 1 GB). The pre-caching sliding interval can further be configured by specifying a time interval (see PrecachingTimeInterval). In that case, the effective interval will be the minimum of those two settings (size in GB or time span).
- L54 _public member_ `bool bEnablePrecachingTimeInterval;` — `UPROPERTY(config, EditAnywhere, Category=Caching, meta=(InlineEditConditionToggle))` — Enables pre-caching time interval strategy.
- L62 _public member_ `float PrecachingTimeInterval;` — `UPROPERTY(EditAnywhere, Category=Caching, meta=(ClampMin=0, EditCondition="bEnablePrecachingTimeInterval"))` — Specify the pre-caching sliding time interval, in seconds. The player will pre-cache the specified number of frames corresponding to the time interval relative to the play head. The cache behind percentage still applies to determine how much frames to pre-cache behind vs ahead of the play head.
- L66 _public member_ `int32 CacheThreads;` — `UPROPERTY(config, EditAnywhere, Category=Caching, meta=(ClampMin=0))` — Maximum number of image caching threads to use (0 = number of cores, default = 2).
- L70 _public member_ `int32 CacheThreadStackSizeKB;` — `UPROPERTY(config, EditAnywhere, Category=Caching, meta=(ClampMin=128), AdvancedDisplay)` — Size of the stack for each caching thread (in kB; default = 128).
- L74 _public member_ `float GlobalCacheSizeGB;` — `UPROPERTY(config, EditAnywhere, Category = Caching, meta = (ClampMin = 0))` — Maximum size of the global look-ahead cache (in GB; default = 1 GB). Must be greater or equal to CacheSizeGB.
- L78 _public member_ `bool UseGlobalCache;` — `UPROPERTY(config, EditAnywhere, Category = Caching)` — Whether to use the global cache or not.
- L84 _public member_ `uint32 ExrDecoderThreads;` — `UPROPERTY(config, EditAnywhere, Category=EXR, meta=(ClampMin=0))` — Number of worker threads to use when decoding EXR images (0 = auto).
- L89 _public prototype_ `UImgMediaSettings();` — Default constructor.
- L98 _public function_ `FString GetDefaultProxy() const` — Get the default media source proxy name tag. @return Proxy name tag, or empty string if not set or disabled.
- L108 _public prototype_ `virtual void PostInitProperties() override;`
- L111 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L114 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnImgMediaSettingsChanged, const UImgMediaSettings*);`
- L117 _public prototype_ `static FOnImgMediaSettingsChanged& OnSettingsChanged();` — Gets a multicast delegate which is called whenever one of the parameters in this settings object changes.
- L120 _protected member_ `static FOnImgMediaSettingsChanged SettingsChangedDelegate;`
- L146 _private member_ `FString DefaultProxy;` — `UPROPERTY(config, EditAnywhere, Category=Proxies)` — Name of default media source proxy URLs (default = 'proxy'). Image sequence media sources may contain more than one media source URL. Additional URLs are called media source proxies, and they are generally used for switching to lower resolution media content for improved performance during development and testing. Each proxy URL has a name associated with it, such as 'proxy', 'lowres', or any other user defined tag. It is up to the media source to interpret this value and map it to a media source URL. For example, a media source consisting of a sequence of uncompressed images may use a proxy name as the name of the sub-directory that contains proxy content, such as a low-res version of the image sequence. When default proxies are enabled via the UseDefaultProxy setting, media players will first try to locate the proxy content identified by the DefaultProxy tag. If no such proxy content is available, they will fall back to the media source's default URL. @see UseDefaultProxy
- L169 _private member_ `bool UseDefaultProxy;` — `UPROPERTY(config, EditAnywhere, Category=Proxies)` — Whether to enable image sequence proxies (default = false). Image sequence media sources may contain more than one media source URL. Additional URLs are called media source proxies, and they are generally used for switching to lower resolution media content for improved performance during development and testing. Each proxy URL has a name associated with it, such as 'proxy', 'lowres', or any other user defined tag. It is up to the media source to interpret this value and map it to a media source URL. For example, a media source consisting of a sequence of uncompressed images may use a proxy name as the name of the sub-directory that contains proxy content, such as a low-res version of the image sequence. When default proxies are enabled via the UseDefaultProxy setting, media players will first try to locate the proxy content identified by the DefaultProxy tag. If no such proxy content is available, they will fall back to the media source's default URL. @see DefaultProxy
- L174 _private prototype_ `void ValidateSettings();` — Ensures the settings are valid, and will change them if not.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API IMGMEDIAFACTORY_API`
- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnImgMediaSettingsChanged, const UImgMediaSettings*);`
