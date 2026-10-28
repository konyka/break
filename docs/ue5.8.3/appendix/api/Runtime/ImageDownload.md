# Runtime / ImageDownload

- module root: `Source/Runtime/Online/ImageDownload`
- headers: 3; symbols: 45
- symbol kinds: class=2, delegate=2, function=10, member=13, prototype=16, typedef=2
- PrivateDependencyModuleNames: Core, HTTP, ImageCore, ImageWrapper, SlateCore

### `Source/Runtime/Online/ImageDownload/Private/ImageDownloadPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageDownload, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageDownload, Log, All);`

### `Source/Runtime/Online/ImageDownload/Public/WebImage.h` (Public)


#### class `FWebImage`  
`class FWebImage : public TSharedFromThis<FWebImage>`  
_L42-142_
- inherits: `TSharedFromThis<FWebImage>`
- desc: This class manages downloading an image and swapping it out a standin once it's done. Example (not cached): FWebImage Image; Image.SetStandInBrush(FStyle::Get()->GetBrush("Foo")); Image.BeginDownload(Url, OptionalCallback); SNew(SImage) .Image(Image.Attr()) You may want to get your FWebImage from a FWebImageCache so we're not re-downloading the same URL all the time. Example (cached): FWebImageCache ImageCache; // usually global ImageCache.SetStandInBrush(FStyle::Get()->GetBrush("Foo")); SNew(SImage) .Image(ImageCache.Download(Url)->Attr())
- L46 _public prototype_ `FWebImage();`
- L47 _public prototype_ `~FWebImage();`
- L53 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnImageDownloaded, bool);` — Fired when the image finishes downloading or is canceled. @param Success True if the downloaded image will now be returned by GetBrush()
- L56 _public function_ `inline FWebImage& SetStandInBrush(TAttribute<const FSlateBrush*> StandInBrushIn)` — Set the brush that is currently being returned (this will be overridden when any async download completes)
- L64 _public prototype_ `void SetDownloadedBrushDrawType(ESlateBrushDrawType::Type DrawType);` — Set draw type for the downloaded image brush
- L67 _public prototype_ `void SetDownloadedBrushOutlineSettings(FSlateBrushOutlineSettings OutlineSettings);` — Set outline settings for the downloaded image brush
- L70 _public prototype_ `bool BeginDownload(const FString& InUrl, const TOptional<FString>& StandInETag = TOptional<FString>(), const FOnImageDownloaded& DownloadCallback = FOnImageDownloaded());` — Begin downloading an image. This will automatically set the current brush to the downloaded image when it completes (if successful)
- L73 _public function_ `inline bool BeginDownload(const FString& InUrl, const FOnImageDownloaded& DownloadCallback)` — Begin downloading an image.
- L79 _public prototype_ `void CancelDownload();` — Cancel any download in progress
- L84 _public prototype_ `TAttribute< const FSlateBrush* > Attr() const;` — Use .Attr() to pass this brush into a slate attribute
- L87 _public function_ `inline const FSlateBrush* GetBrush() const` — Get the current brush displayed (will automatically change when download completes)
- L90 _public function_ `inline const FSlateBrush* GetDownloadedBrush() const` — Only returns the downloaded brush. May be null if the download hasn't finished or was unsuccessful
- L93 _public function_ `inline bool IsDownloadPending() const` — Is there a pending HTTP request
- L96 _public function_ `inline bool DidDownloadSucceed() const` — Has the download finished AND was it successful
- L99 _public function_ `inline bool DidDownloadFail() const` — Has the download finished AND did it fail
- L102 _public function_ `inline const FString& GetUrl() const` — What URL was requested
- L105 _public function_ `inline const TOptional<FString>& GetETag() const` — What is the ETag of the downloaded resource
- L109 _private prototype_ `void HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);` — request complete callback
- L110 _private prototype_ `bool ProcessHttpResponse(const FString& RequestUrl, FHttpResponsePtr HttpResponse);`
- L114 _private member_ `FString Url;` — The Url being downloaded
- L117 _private member_ `TAttribute< const FSlateBrush* > StandInBrush;` — The image resource to show
- L120 _private member_ `TSharedPtr<FSlateDynamicImageBrush> DownloadedBrush;` — The most recently downloaded and generated brush
- L123 _private member_ `FSlateBrushOutlineSettings DownloadedBrushOutlineSettings;` — Outline settings for the downloaded image brush
- L126 _private member_ `ESlateBrushDrawType::Type DownloadedBrushDrawType;` — Draw type for the downloaded image brush
- L129 _private member_ `TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> PendingRequest;` — Any pending request
- L132 _private member_ `FOnImageDownloaded PendingCallback;` — Callback to call upon completion
- L135 _private member_ `bool bDownloadSuccess;` — Have we successfully downloaded the URL we asked for
- L138 _private member_ `FDateTime DownloadTimeUtc;` — When did the download complete
- L141 _private member_ `TOptional<FString> ETag;` — The ETag of the downloaded image

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;`
- L20 _typedef_ `typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;`
- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnImageDownloaded, bool);` — Fired when the image finishes downloading or is canceled. @param Success True if the downloaded image will now be returned by GetBrush()

### `Source/Runtime/Online/ImageDownload/Public/WebImageCache.h` (Public)


#### class `FWebImageCache`  
`class FWebImageCache`  
_L17-49_
- desc: This class is designed to facilitate caching of web images and setting a global stand-in so we don't re-download the same image every time the UI shows it again. See WebImage.h for example usage.
- L20 _public prototype_ `FWebImageCache();`
- L23 _public prototype_ `void PreUnload();` — Signifies the module is being unloaded and to perform any actions that depend on other modules which may be unloaded as well
- L26 _public prototype_ `void Empty();` — Removes all cached images
- L29 _public prototype_ `TSharedRef<const FWebImage> Download(const FString& Url, const TOptional<FString>& DefaultImageUrl = TOptional<FString>());` — Find or create a WebImage object for this URL (you probably just want to call ->Attr() on this)
- L32 _public function_ `inline void SetDefaultStandInBrush(TAttribute<const FSlateBrush*> StandInBrushIn)` — Set the brush that will be returned until the download completes (only affects future downloads).
- L38 _public prototype_ `void RelinquishUnusedImages();` — This function causes the web image cache to stop holding on to strong references to images. Normally once downloaded, an image is cached forever. This allows us to release images that are not currently being displayed (those would have Strong pointers existing external to this class) to be released.
- L42 _private member_ `TMap<FString, TWeakPtr<FWebImage> > UrlToImageMap;` — Map of canonical URL to web images (weak pointer so we don't affect lifetime)
- L45 _private member_ `TArray< TSharedRef<FWebImage> > StrongRefCache;` — Strong references to keep images cached when not in use. Can be flushed manually
- L48 _private member_ `TAttribute< const FSlateBrush* > DefaultStandInBrush;` — The image resource to show
