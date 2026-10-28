# Plugins / SemanticSearch

- module root: `Plugins/Experimental/SemanticSearch/Source/SemanticSearch`
- headers: 26; symbols: 664
- symbol kinds: class=24, delegate=2, enum=4, enumerator=10, function=62, member=177, namespace=65, prototype=297, struct=20, typedef=3
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, DeveloperSettings, Engine, FAISS, HTTP, ImageCore, Json, PhysicsCore, Projects, Slate, UnrealEd
- PublicDependencyModuleNames: DerivedDataCache

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/AssetProcessorUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)
- L22 _prototype_ `void SetMetadata( const TSharedPtr<FJsonObject>& Metadata, const TSharedRef<const FAssetData>& InAsset, FName AssetDataTag, FStringView CaptionMetadataKey);` (scope `UE::SemanticSearch::Private`) — Reads AssetDataTag from InAsset and, if present, writes the raw value into Metadata under CaptionMetadataKey. @param Metadata              JSON object to write the field into @param InAsset               Asset whose tag store is queried @param AssetDataTag          Tag name to look up on the asset @param CaptionMetadataKey    Key used when writing the field into Metadata
- L38 _prototype_ `void SetMetadataWithDisplayString( const TSharedPtr<FJsonObject>& Metadata, const TSharedRef<const FAssetData>& InAsset, FName AssetDataTag, FStringView CaptionMetadataKey, const TMap<FString, FString>& DisplayMap);` (scope `UE::SemanticSearch::Private`) — Reads AssetDataTag from InAsset and, if present, writes the value into Metadata under CaptionMetadataKey. If DisplayMap contains an entry for the raw value, the mapped display string is written instead. @param Metadata              JSON object to write the field into @param InAsset               Asset whose tag store is queried @param AssetDataTag          Tag name to look up on the asset @param CaptionMetadataKey    Key used when writing the field into Metadata @param DisplayMap            Optional remapping from raw enum name strings to human-readable display strings
- L52 _prototype_ `void PopulateFromEnum(TMap<FString, FString>& OutMap, const UEnum* Enum);` (scope `UE::SemanticSearch::Private`) — Populates OutMap with name-to-display-string entries for every enumerator in Enum. Must be called on the game thread as reflection data is not thread safe in the editor. @param OutMap    Map to populate with enumerator name to display string pairs @param Enum      Enum whose enumerators are iterated
- L57 _prototype_ `void RegisterDefaultAssetProcessors();` (scope `UE::SemanticSearch::Private`) — Register the build in asset processor that ship with this plugin

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/BlueprintAssetProcessor.h` (Private)


#### class `UE::SemanticSearch::Private::FBlueprintProcessor`  
`class FBlueprintProcessor : public FThumbnailBaseAssetProcessor`  
_L10-23_
- inherits: `FThumbnailBaseAssetProcessor`
- L13 _public function_ `constexpr virtual FStringView GetProcessSubBucketName() const override`
- L19 _public prototype_ `virtual UClass& GetSupportedClass() const override;` — Thread safe
- L20 _public prototype_ `virtual bool SupportDerivedClasses() const override;`
- L22 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/MaterialAssetProcessor.h` (Private)


#### class `UE::SemanticSearch::Private::FMaterialProcessor`  
`class FMaterialProcessor : public FThumbnailBaseAssetProcessor`  
_L10-35_
- inherits: `FThumbnailBaseAssetProcessor`
- L14 _public prototype_ `FMaterialProcessor();` — Must be created on the game thread
- L16 _public function_ `constexpr virtual FStringView GetProcessSubBucketName() const override`
- L22 _public prototype_ `virtual UClass& GetSupportedClass() const override;` — Thread safe
- L23 _public prototype_ `virtual bool SupportDerivedClasses() const override;`
- L25 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const override;`
- L28 _private prototype_ `FString DecodeShadingModelsBitmask(const FString& BitmaskStr) const;`
- L31 _private member_ `TMap<FString, FString> MetaDataValueStringToDisplayString;` — Cache the display values as those are not thread safe
- L34 _private member_ `TArray<FString> ShadingModelIndexToName;` — Cache of EMaterialShadingModel index to name string — reflection data is not thread safe

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/MaterialInstanceAssetProcessor.h` (Private)


#### class `UE::SemanticSearch::Private::FMaterialInstanceProcessor`  
`class FMaterialInstanceProcessor : public FThumbnailBaseAssetProcessor`  
_L10-25_
- inherits: `FThumbnailBaseAssetProcessor`
- L13 _public prototype_ `FMaterialInstanceProcessor();`
- L15 _public function_ `constexpr virtual FStringView GetProcessSubBucketName() const override`
- L21 _public prototype_ `virtual UClass& GetSupportedClass() const override;` — Thread safe
- L22 _public prototype_ `virtual bool SupportDerivedClasses() const override;`
- L24 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/SkeletalMeshAssetProcessor.h` (Private)


#### class `UE::SemanticSearch::Private::FSkeletalMeshProcessor`  
`class FSkeletalMeshProcessor : public FThumbnailBaseAssetProcessor`  
_L10-25_
- inherits: `FThumbnailBaseAssetProcessor`
- L13 _public prototype_ `FSkeletalMeshProcessor();`
- L15 _public function_ `constexpr virtual FStringView GetProcessSubBucketName() const override`
- L21 _public prototype_ `virtual UClass& GetSupportedClass() const override;` — Thread safe
- L22 _public prototype_ `virtual bool SupportDerivedClasses() const override;`
- L24 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/StaticMeshAssetProcessor.h` (Private)


#### class `UE::SemanticSearch::Private::FStaticMeshProcessor`  
`class FStaticMeshProcessor : public FThumbnailBaseAssetProcessor`  
_L10-30_
- inherits: `FThumbnailBaseAssetProcessor`
- L14 _public prototype_ `FStaticMeshProcessor();` — Must be created on the game thread
- L16 _public function_ `constexpr virtual FStringView GetProcessSubBucketName() const override`
- L22 _public prototype_ `virtual UClass& GetSupportedClass() const override;` — Thread safe
- L23 _public prototype_ `virtual bool SupportDerivedClasses() const override;`
- L25 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const override;`
- L29 _private member_ `TMap<FString, FString> MetaDataValueStringToDisplayString;` — Cache the display values as those are not thread safe

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/AssetProcessors/TextureAssetProcessor.h` (Private)


#### class `UE::SemanticSearch::Private::FTextureProcessor`  
`class FTextureProcessor : public FThumbnailBaseAssetProcessor`  
_L10-30_
- inherits: `FThumbnailBaseAssetProcessor`
- L14 _public prototype_ `FTextureProcessor();` — Must be created on the game thread
- L16 _public function_ `constexpr virtual FStringView GetProcessSubBucketName() const override`
- L22 _public prototype_ `virtual UClass& GetSupportedClass() const override;` — Thread safe
- L23 _public prototype_ `virtual bool SupportDerivedClasses() const override;`
- L25 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const override;`
- L29 _private member_ `TMap<FString, FString> MetaDataValueStringToDisplayString;` — Cache the display value as those are not thread safe

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/EmbeddingProviders/OpenAIEmbeddingProvider.h` (Private)


#### struct `UE::SemanticSearch::Private::FOpenAIConfig`  
`struct FOpenAIConfig`  
_L19-31_
- desc: Configuration for the OpenAI provider, snapshotted from USemanticSearchSettings at construction. Snapshotting (not live-reading) keeps GetConfigHash() stable across the provider's lifetime, which the DDC cache key path depends on.
- L21 _public member_ `FString CaptioningBaseUrl;`
- L22 _public member_ `FString CaptioningApiKey;`
- L23 _public member_ `FString CaptioningModel;`
- L24 _public member_ `FString EmbeddingBaseUrl;`
- L25 _public member_ `FString EmbeddingApiKey;`
- L26 _public member_ `FString EmbeddingModel;`
- L27 _public member_ `int32 EmbeddingDimension = 512;`
- L30 _public prototype_ `uint32 GetHash() const;` — Hash of the embedding model + dimension. Affects DDC cache key.

#### class `UE::SemanticSearch::Private::FOpenAIEmbeddingProvider`  
`class FOpenAIEmbeddingProvider : public IEmbeddingProvider`  
_L40-55_
- inherits: `IEmbeddingProvider`
- desc: OpenAI-compatible embedding provider. Calls /chat/completions for captioning (with structured JSON output enforcing {tags, caption}) and /embeddings for embeddings. Works against any OpenAI-compatible server (api.openai.com, Google/Anthropic OpenAI compatibitle endpoints, Ollama, LiteLLM).
- L43 _public prototype_ `FOpenAIEmbeddingProvider();`
- L45 _public prototype_ `virtual int32 GetEmbeddingDimension() const override;`
- L46 _public prototype_ `virtual void GenerateCaptionAsync(FCaptionRequest&& Request, FOnCaptionComplete&& OnComplete, DerivedData::FRequestOwner* RequestOwner) override;`
- L47 _public prototype_ `virtual void GenerateEmbeddingAsync(const FStringView Text, FOnEmbeddingComplete&& OnComplete, DerivedData::FRequestOwner* RequestOwner) override;`
- L49 _public prototype_ `uint32 GetConfigHash() const override;`
- L50 _public prototype_ `void CancelAllPendingRequests() override;`
- L53 _private member_ `FOpenAIConfig Config;`
- L54 _private member_ `FSemanticHttpClient HttpClient;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/EmbeddingProviders/SemanticHttpUtils.h` (Private)


#### struct `UE::SemanticSearch::Private::FThrottledRequestQueue`  
`struct FThrottledRequestQueue`  
_L29-76_
- desc: Async-friendly concurrency limiter for HTTP requests. Limits the number of in-flight requests and queues excess for later dispatch.
- L31 _public member_ `FCriticalSection Lock;`
- L32 _public member_ `TQueue<TFunction<void()>> PendingRequests;`
- L33 _public member_ `int32 InFlightCount = 0;`
- L34 _public member_ `int32 MaxConcurrent = 8;`
- L37 _public function_ `inline void Enqueue(TFunction<void()>&& DispatchFn)` — Try to dispatch a request. If at capacity, queues it for later.
- L52 _public function_ `inline void OnRequestComplete()` — Called when a request completes. Dispatches next queued request if any.
- L70 _public function_ `inline void CancelPending()` — Clear all pending (not yet dispatched) requests. In-flight requests are not affected.

#### class `UE::SemanticSearch::Private::FSemanticHttpClient`  
`class FSemanticHttpClient`  
_L85-136_
- desc: Shared HTTP plumbing for embedding providers: owns the FHttpRetrySystem manager and the two throttled queues (caption + embed), and exposes a CreateRetryRequest() factory that applies the standard retry policy (retry on 429/5xx, POST only). Providers compose this instead of duplicating retry/queue/concurrency wiring.
- L88 _public function_ `FSemanticHttpClient(int32 MaxRetries, double RetryTimeoutSeconds, int32 MaxConcurrentCaption, int32 MaxConcurrentEmbed) : RetryManager(MakeShared<FHttpRetrySystem::FManager>( FHttpRetrySystem::RetryLimitCount(MaxRetries), FHttpRetrySystem::RetryTimeoutRelativeSeconds(RetryTimeoutSeconds)))`
- L98 _public function_ `static FSemanticHttpClient CreateFromSettings()` — Build a client snapshotting retry/concurrency knobs from USemanticSearchSettings.
- L109 _public function_ `TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateRetryRequest() const` — Create a retry-aware HTTP request (retries on 429/5xx, POST only).
- L122 _public function_ `FThrottledRequestQueue& GetCaptionQueue()`
- L123 _public function_ `FThrottledRequestQueue& GetEmbedQueue()`
- L126 _public function_ `void CancelAllPendingRequests()` — Clear pending (un-dispatched) requests in both queues. In-flight requests are unaffected.
- L133 _private member_ `TSharedRef<FHttpRetrySystem::FManager> RetryManager;`
- L134 _private member_ `FThrottledRequestQueue CaptionQueue;`
- L135 _private member_ `FThrottledRequestQueue EmbedQueue;`

#### class `UE::SemanticSearch::Private::FSemanticHttpRequest`  
`class FSemanticHttpRequest : public DerivedData::FRequestBase`  
_L143-262_
- inherits: `DerivedData::FRequestBase`
- desc: Wraps an IHttpRequest as a DerivedData::FRequest so it can be tracked / canceled by the DDC subsystem. Mirrors the priority and cancel signals from the owner down to the underlying HTTP request.
- L146 _public function_ `FSemanticHttpRequest( const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& InHttpRequest, DerivedData::FRequestOwner& InRequestOwner, TSharedRef<std::atomic<bool>, ESPMode::ThreadSafe> InCanceledBeforeSendFlag) : FRequestBase() , HttpRequest(InHttpRequest) , RequestOwner(&static_cast<DerivedData::IRequestOwner&>(InRequestOwner)) , CanceledBeforeSendFlag(MoveTemp(InCanceledBeforeSendFlag))`
- L165 _public function_ `bool Start()` — Start the HTTP request. Separated from construction so Begin() can run in the caller's DDC context. Returns true if HTTP was dispatched, false if the request was canceled before it could be sent (in which case the caller must release the throttled queue slot).
- L176 _public function_ `virtual ~FSemanticHttpRequest()`
- L181 _public function_ `virtual void SetPriority(DerivedData::EPriority Priority) override`
- L213 _public function_ `virtual void Cancel() override`
- L233 _public function_ `virtual void Wait() override`
- L239 _private function_ `void OnRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)`
- L257 _private member_ `TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;`
- L258 _private member_ `DerivedData::IRequestOwner* RequestOwner;`
- L259 _private member_ `FHttpRequestCompleteDelegate RequestCompleteDelegate;`
- L260 _private member_ `TSharedRef<std::atomic<bool>, ESPMode::ThreadSafe> CanceledBeforeSendFlag;`
- L261 _private member_ `std::atomic<EState> State { EState::Pending };`

#### enum `UE::SemanticSearch::Private::FSemanticHttpRequest::EState`  
`enum class EState : uint8`  
_L255-255_
- L255 _public enumerator_ `enum class EState : uint8 { Pending, Started, Canceled, Completed }; TSharedRef<IHttpRequest`
- L255 _public enumerator_ `enum class EState : uint8 { Pending, Started, Canceled, Completed }; TSharedRef<IHttpRequest`
- L255 _public enumerator_ `enum class EState : uint8 { Pending, Started, Canceled, Completed }; TSharedRef<IHttpRequest`
- L255 _public enumerator_ `enum class EState : uint8 { Pending, Started, Canceled, Completed }; TSharedRef<IHttpRequest`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)
- L246 _function_ `` (scope `UE::SemanticSearch::Private::FSemanticHttpRequest::OnRequestComplete`)
- L249 _function_ `` (scope `UE::SemanticSearch::Private::FSemanticHttpRequest::OnRequestComplete::__anonb06529470102`)
- L270 _function_ `template <typename ResponseT, typename BodyParserT> inline ResponseT ParseHttpJsonResponse(FHttpResponsePtr Resp, bool bConnected, BodyParserT&& ParseBody)` (scope `UE::SemanticSearch::Private`) — Validate an HTTP/JSON response and populate the standard error cases. On success, invokes ParseBody(Json, Response) to fill in response-specific fields. ResponseT must expose an FString ErrorMessage member.
- L316 _function_ `template <typename ResponseT, typename OnCompleteT, typename BodyParserT> inline void DispatchHttpJsonRequest( const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Http, FThrottledRequestQueue& Queue, DerivedData::FRequestOwner* RequestOwner, OnCompleteT&& InOnComplete, BodyParserT&& ParseBody)` (scope `UE::SemanticSearch::Private`) — Bind the cancel-aware completion delegate on Http, then enqueue the request through Queue. When RequestOwner is provided, wraps the request as an FSemanticHttpRequest so DDC can cancel it; when null, dispatches directly through the queue.
- L340 _function_ `` (scope `UE::SemanticSearch::Private::DispatchHttpJsonRequest`)
- L374 _function_ `Queue.Enqueue([Http]() { Http->ProcessRequest(); });` (scope `UE::SemanticSearch::Private::DispatchHttpJsonRequest`)
- L379 _function_ `inline void ConfigureJsonPostRequest(const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Http, const FString& URL)` (scope `UE::SemanticSearch::Private`) — Apply POST/timeout/thread-policy settings common to every request.

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/Implementations/SemanticSearchImplementationUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)
- L36 _prototype_ `bool ShouldForceSequentialIndexWorker();` (scope `UE::SemanticSearch::Private`) — Returns true while SemanticSearch.ForceSequentialSemanticSearchIndexWorker is non-zero.
- L39 _prototype_ `bool ShouldKeepParallelFor();` (scope `UE::SemanticSearch::Private`) — Returns true while SemanticSearch.KeepParallelFor is non-zero (the default).
- L46 _prototype_ `EParallelForFlags GetSearchParallelForFlags(EParallelForFlags BaseFlags = EParallelForFlags::None);` (scope `UE::SemanticSearch::Private`) — Returns BaseFlags with EParallelForFlags::ForceSingleThread OR'd in when SemanticSearch.KeepParallelFor is off. Use at every ParallelFor call site in the search path so the CVar can flatten the trace.
- L56 _prototype_ `void RunOrDispatchIndexWorker( TUniqueFunction<void()> Body, const FGraphEventArray* Prereqs = nullptr, ENamedThreads::Type DesiredThread = ENamedThreads::AnyBackgroundHiPriTask);` (scope `UE::SemanticSearch::Private`) — Either runs Body inline (when SemanticSearch.ForceSequentialSemanticSearchIndexWorker is non-zero) or dispatches it onto the task graph with the supplied prereqs. In force-sequential mode Prereqs is ignored by design: upstream stages have already run synchronously on the calling thread, so the dependency is trivially satisfied.
- L81 _function_ `template <typename TItem> void RadixSort(TArray<TItem>& InOut, TArray<uint32>& Scratch, auto KeyAccessor, bool bDescending = false)` (scope `UE::SemanticSearch::Private`) — In-place radix sort of an item array by a non-negative float key. Why this exists: The default Algo::Sort (introsort) is O(N log N) with random-access compare- and-swap and gets cache-unfriendly past a few hundred thousand items. Restriction: - Key must be a NON-NEGATIVE float. @param InOut         Items to sort, in place. Must be trivially copyable. @param Scratch       Caller-owned scratch buffer, all packed into one TArray<uint32>: [ Counts        : 256·NumStripes ] [ ItemsScratch  : ceil(N·sizeof(TItem)/4) ]. @param KeyAccessor   Callable mapping `const TItem&` → `float`. Must return a non-negative value. @param bDescending   When true, sort by descending key.
- L106 _function_ `` (scope `UE::SemanticSearch::Private::RadixSort`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/SemanticSearchDerivedDataBuilder.h` (Private)


#### struct `UE::SemanticSearch::Private::FEmbeddingDerivedData`  
`struct FEmbeddingDerivedData`  
_L31-34_
- L33 _public member_ `TArray<float> Embedding;`

#### struct `UE::SemanticSearch::Private::FQuantizedEmbeddingDerivedData`  
`struct FQuantizedEmbeddingDerivedData`  
_L36-39_
- L38 _public member_ `TArray<uint8> QuantizedEmbedding;`

#### struct `UE::SemanticSearch::Private::FCaptionDerivedData`  
`struct FCaptionDerivedData`  
_L41-45_
- L43 _public member_ `FString Caption;`
- L44 _public member_ `TArray<FString> Keywords;`

#### struct `UE::SemanticSearch::Private::FBatchDDCEntry`  
`struct FBatchDDCEntry`  
_L59-64_
- desc: Entry for batch DDC operations. Populated by AssetProcessorManager, consumed by static batch methods.
- L61 _public member_ `FAssetData Asset;`
- L62 _public member_ `TSharedPtr<FSemanticSearchBuildCacheTask> Task;`
- L63 _public member_ `DerivedData::FCacheKey CacheKey;`

#### class `UE::SemanticSearch::Private::FSemanticSearchBuildCacheTask`  
`class FSemanticSearchBuildCacheTask : public DerivedData::FRequestOwner , public TSharedFromThis<FSemanticSearchBuildCacheTask>`  
_L66-153_
- inherits: `DerivedData::FRequestOwner,TSharedFromThis<FSemanticSearchBuildCacheTask>`
- L72 _public prototype_ `static TSharedPtr<FSemanticSearchBuildCacheTask> Create(const FAssetData& InAssetData, const TSharedRef<IAssetProcessor>& InAssetProcessor, DerivedData::FCacheKey&& InKey);` — InKey must not be empty — passing an empty key will crash. Use GenerateCacheKey and validate before calling.
- L73 _public prototype_ `static TSharedPtr<FSemanticSearchBuildCacheTask> Create(FAssetData&& InAssetData, const TSharedRef<IAssetProcessor>& InAssetProcessor, DerivedData::FCacheKey&& InKey);`
- L75 _public prototype_ `FSemanticSearchBuildCacheTask(FAssetData&& InAssetData, const TSharedRef<IAssetProcessor>& InAssetProcessor, DerivedData::FCacheKey&& InAssetKey);`
- L77 _public prototype_ `void GetEmbeddingData(TUniqueFunction<void (FEmbeddingDerivedData&& EmbeddingData, FString&& ErrorMessage, EAssetIndexFailureReason Reason)>&& InOnDataAvailable, bool bBuildOnMiss = true);`
- L78 _public prototype_ `void GetCaptionData(TUniqueFunction<void (FCaptionDerivedData&& CaptionData, FString&& ErrorMessage, EAssetIndexFailureReason Reason)>&& InOnDataAvailable);`
- L81 _public prototype_ `void GetQuantizedEmbeddingData(const FIoHash& CodebookHash, TUniqueFunction<void(FQuantizedEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable, bool bBuildOnMiss = true);` — Retrieve quantized embedding data from DDC. On miss, builds by fetching the float embedding and quantizing.
- L86 _public prototype_ `void GetRecordData( TUniqueFunction<void(FEmbeddingDerivedData&&, FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable, bool bBuildOnMiss = true);` — Retrieve both embedding and caption in a single DDC Get() call instead of 2x GetChunks().
- L90 _public prototype_ `void CacheData();`
- L92 _public function_ `const DerivedData::FCacheKey& GetAssetKey() const`
- L93 _public function_ `const FSharedString& GetDDCRequestName() const`
- L95 _public prototype_ `static DerivedData::FCacheKey GenerateCacheKey(const FAssetData& InAssetData, const TSharedRef<IAssetProcessor>& InAssetProcessor);`
- L96 _public prototype_ `static DerivedData::FCacheKey GenerateQuantizedCacheKey(const DerivedData::FCacheKey& BaseCacheKey, const FIoHash& CodebookHash);`
- L97 _public prototype_ `static DerivedData::FCacheBucket GetCacheKeyBucket(const TSharedRef<IAssetProcessor>& InAssetProcessor);`
- L100 _public prototype_ `static void BatchGetRecordData( TArray<FBatchDDCEntry>&& Entries, TFunction<void(const FAssetData&, FEmbeddingDerivedData&&, FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)> OnAssetResult, bool bBuildOnMiss = true);` — Batch-fetch embedding + caption from DDC for multiple assets. Falls back to per-asset GetRecordData on miss.
- L106 _public prototype_ `static void BatchGetQuantizedRecordData( TArray<FBatchDDCEntry>&& Entries, const FIoHash& CodebookHash, TFunction<void(const FAssetData&, FCaptionDerivedData&&, FQuantizedEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)> OnAssetResult, bool bBuildOnMiss = true);` — Batch-fetch caption + quantized codes from DDC for multiple assets (two parallel batch Get calls).
- L114 _private prototype_ `void BuildDerivedData();`
- L115 _private prototype_ `void BuildQuantizedDerivedData(const FIoHash& CodebookHash, bool bBuildOnMiss);`
- L118 _private prototype_ `void BuildCaptionData(TUniqueFunction<void(FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable);` — Like GetCaptionData, but skips the DDC lookup. Use when a prior batch Get has already confirmed a miss.
- L121 _private prototype_ `void BuildRecordData(TUniqueFunction<void(FEmbeddingDerivedData&&, FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable);` — Like GetRecordData, but skips the DDC lookup. Use when a prior batch Get has already confirmed a miss.
- L124 _private prototype_ `void BuildQuantizedEmbeddingData(const FIoHash& CodebookHash, TUniqueFunction<void(FQuantizedEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable);` — Like GetQuantizedEmbeddingData, but skips the DDC lookup. Use when a prior batch Get has already confirmed a miss.
- L125 _private prototype_ `void BroadcastQueuedRequests(FEmbeddingDerivedData&& EmbeddingData, FCaptionDerivedData&& CaptionData, FString&& ErrorMessage, EAssetIndexFailureReason Reason);`
- L126 _private prototype_ `void BroadcastQueuedCaptionRequest(FCaptionDerivedData&& CaptionData, FString&& ErrorMessage, EAssetIndexFailureReason Reason);`
- L127 _private prototype_ `void BroadcastQueuedEmbeddingRequest(FEmbeddingDerivedData&& EmbeddingData, FString&& ErrorMessage, EAssetIndexFailureReason Reason);`
- L128 _private prototype_ `void BroadcastQueuedQuantizedRequest(FQuantizedEmbeddingDerivedData&& QuantizedData, FString&& ErrorMessage, EAssetIndexFailureReason Reason);`
- L129 _private prototype_ `void BroadcastQueuedRecordRequest(FEmbeddingDerivedData&& EmbeddingData, FCaptionDerivedData&& CaptionData, FString&& ErrorMessage, EAssetIndexFailureReason Reason);`
- L131 _private prototype_ `TUniqueFunction<void(FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)> NoLock_GetCaptionRequests();`
- L132 _private prototype_ `TUniqueFunction<void(FEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)> NoLock_GetEmbeddingRequest();`
- L133 _private prototype_ `TUniqueFunction<void(FQuantizedEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)> NoLock_GetQuantizedRequests();`
- L134 _private prototype_ `TUniqueFunction<void(FEmbeddingDerivedData&&, FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)> NoLock_GetRecordRequests();`
- L137 _private member_ `TSharedRef<const FAssetData> Asset;`
- L138 _private member_ `TSharedRef<IAssetProcessor> AssetProcessor;`
- L139 _private member_ `DerivedData::FCacheKey AssetKey;`
- L140 _private member_ `FSharedString DDCRequestName;`
- L143 _private member_ `FRWLock IsBuildingDerivedDataLock;` — Acs has a lock for the IsBuildingDerivedData flag but also avoid race condition with the queued Requests
- L144 _private member_ `bool bIsBuildingDerivedData = false;`
- L145 _private member_ `TQueue<TUniqueFunction<void (FEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)>, EQueueMode::Mpsc> QueuedEmbeddingRequests;`
- L146 _private member_ `TQueue<TUniqueFunction<void (FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)>, EQueueMode::Mpsc> QueuedCaptionRequests;`
- L147 _private member_ `TQueue<TUniqueFunction<void (FQuantizedEmbeddingDerivedData&&, FString&&, EAssetIndexFailureReason)>, EQueueMode::Mpsc> QueuedQuantizedRequests;`
- L148 _private member_ `TQueue<TUniqueFunction<void (FEmbeddingDerivedData&&, FCaptionDerivedData&&, FString&&, EAssetIndexFailureReason)>, EQueueMode::Mpsc> QueuedRecordRequests;`
- L149 _private member_ `std::atomic<bool> HasActiveEmbeddingRequest = false;`
- L150 _private member_ `std::atomic<bool> HasActiveCaptionRequest = false;`
- L151 _private member_ `std::atomic<bool> HasActiveQuantizedRequest = false;`
- L152 _private member_ `std::atomic<bool> HasActiveRecordRequest = false;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L25 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)
- L48 _prototype_ `DerivedData::FValueId GetEmbeddingDatachunkId();` (scope `UE::SemanticSearch::Private`) — DDC value IDs, serialization, and cache policy helpers (defined in SemanticSearchDerivedDataBuilder.cpp)
- L49 _prototype_ `DerivedData::FValueId GetCaptionDatachunkId();` (scope `UE::SemanticSearch::Private`)
- L50 _prototype_ `DerivedData::FValueId GetQuantizedEmbeddingDatachunkId();` (scope `UE::SemanticSearch::Private`)
- L51 _prototype_ `void SerializeEmbedding(FEmbeddingDerivedData& Embedding, FArchive& Archive);` (scope `UE::SemanticSearch::Private`)
- L52 _prototype_ `void SerializeQuantizedEmbedding(FQuantizedEmbeddingDerivedData& QuantizedEmbedding, FArchive& Archive);` (scope `UE::SemanticSearch::Private`)
- L53 _prototype_ `void SerializeCaption(FCaptionDerivedData& Caption, FArchive& Archive);` (scope `UE::SemanticSearch::Private`)
- L54 _prototype_ `DerivedData::ECachePolicy GetCachePolicy();` (scope `UE::SemanticSearch::Private`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/SemanticSearchIndexCommandlet.h` (Private)


#### class `USemanticSearchIndexCommandlet`  
`class USemanticSearchIndexCommandlet : public UCommandlet`  
_L18-25_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Commandlet that indexes all project assets for semantic search and saves the index to the shared project Config directory for Perforce distribution. Usage: UnrealEditor-Cmd <Project> -run=SemanticSearchIndex [-Timeout=<seconds>] The generated index is written to <ProjectDir>/Config/SemanticSearch/SearchIndex.bin and is intended to be submitted to source control by a BuildGraph Submit step.
- L23 _public prototype_ `USemanticSearchIndexCommandlet();`
- L24 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/SemanticSearchModule.h` (Private)


#### class `UE::SemanticSearch::Private::FSemanticSearchModule`  
`class FSemanticSearchModule : public ISemanticSearchModule`  
_L26-132_
- inherits: `ISemanticSearchModule`
- L29 _public prototype_ `static FSemanticSearchModule& Get();`
- L30 _public prototype_ `virtual TSharedPtr<IEmbeddingProvider> GetEmbeddingProvider() const override;`
- L32 _public prototype_ `virtual void StartupModule() override;`
- L33 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public prototype_ `virtual void RegisterEmbeddingProvider(TUniquePtr<IEmbeddingProvider>&& EmbeddingProvider, bool bRebuildIndex) override;`
- L36 _public prototype_ `virtual void Initialize() override;`
- L37 _public function_ `virtual bool IsInitialized() const override`
- L38 _public prototype_ `virtual void IndexAsset(const FAssetData& AssetData) override;`
- L39 _public prototype_ `virtual void IndexAssets(TConstArrayView<FAssetData> Assets) override;`
- L40 _public prototype_ `virtual FSemanticSearchIndexStats GetIndexStats() const override;`
- L41 _public prototype_ `virtual void SwitchIndexType(ESemanticSearchIndexType NewType) override;`
- L42 _public prototype_ `virtual void IndexAllAssets(bool bForceBuild = false) override;`
- L43 _public prototype_ `virtual void RetrainIndex() override;`
- L44 _public prototype_ `virtual void CancelIndexing() override;`
- L45 _public prototype_ `virtual void SetIndexingPending() override;`
- L46 _public prototype_ `virtual bool IsIndexingInProgress() const override;`
- L47 _public prototype_ `virtual void SearchAsync(const FString& QueryText, TConstArrayView<float> QueryEmbedding, int32 K, TConstArrayView<int64> IDFilter, float DistanceCutoff, TFunction<void(TArray<FHybridSearchResult>&&)> Callback) override;`
- L52 _private prototype_ `void SwitchToFlatIndex();`
- L53 _private prototype_ `void SwitchToQuantizedIndex(ESemanticSearchIndexType NewType, bool bForceTrain = false);`
- L54 _private prototype_ `void TriggerIndexing(const FAssetData& AssetData, bool bBuildOnMiss);`
- L59 _private prototype_ `void RebuildVectorIndexAsFlat(int32 NewDimension);` — Discard the current vector index and BM25 state and create a fresh Flat index sized to NewDimension. Pins USemanticSearchSettings::IndexType to Flat so the choice survives a restart. Caller is responsible for clearing LoadedPackageHashes when those no longer apply.
- L63 _private prototype_ `void IndexAssetsBatch(TArray<FAssetData> AssetsToIndex, bool bBuildOnMiss);` — Dispatch a filtered batch to the processor manager (flat or quantized). Extracted from IndexAllAssets so the async failed-set filter can call it after the IsFailedAsync callback fires.
- L65 _private prototype_ `void OnAssetAdded(const FAssetData& AssetData);`
- L66 _private prototype_ `void OnPackageSaved(const FString& PackageFileName, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);`
- L67 _private prototype_ `void OnPackageSavedDeferred(FName PackageName, FIoHash ExpectedHash, int32 RetryCount);`
- L68 _private prototype_ `void OnAssetRenamed(const FAssetData& NewAssetData, const FString& OldObjectPath);`
- L69 _private prototype_ `void OnAssetRemoved(const FAssetData& AssetData);`
- L70 _private prototype_ `void OnFilesLoaded();`
- L72 _private prototype_ `void OnIndexingStarted();`
- L73 _private prototype_ `void OnBatchIndexingStarted(int32 Count);`
- L77 _private prototype_ `void OnIndexingFinished(bool bSuccess, uint32 Epoch, EAssetIndexFailureReason Reason = EAssetIndexFailureReason::None);` — Reason is None on success and on "not-really-failed" outcomes (cancel, cache miss without build); PreProcessor / Provider on actual failures. The progress notification splits PreProcessor out of "Failed" so the progress chip reconciles with the persistent retryable-only FailedCount.
- L78 _private prototype_ `void UpdateProgressNotification();`
- L79 _private prototype_ `void DismissProgressNotification();`
- L80 _private prototype_ `void ResetProgressState();`
- L81 _private prototype_ `void SaveIndex();`
- L83 _private prototype_ `static FString GetSavedIndexPath();`
- L84 _private prototype_ `static FString GetPreProcessorFailedPath();`
- L86 _private member_ `TSharedPtr<IEmbeddingProvider> RegisteredEmbeddingProvider;`
- L89 _private member_ `bool bIsInitialized = false;` — True after Initialize() has loaded the index, started the consumer queue, and bound delegates.
- L91 _private member_ `FDelegateHandle AssetAddedDelegateHandle;`
- L92 _private member_ `FDelegateHandle PackageSavedDelegateHandle;`
- L93 _private member_ `FDelegateHandle AssetRenamedDelegateHandle;`
- L94 _private member_ `FDelegateHandle AssetRemovedDelegateHandle;`
- L95 _private member_ `FDelegateHandle FilesLoadedDelegateHandle;`
- L96 _private member_ `FDelegateHandle PreExitDelegateHandle;`
- L98 _private member_ `FProgressNotificationHandle ProgressHandle;`
- L99 _private member_ `int32 IndexingTotal = 0;`
- L100 _private member_ `int32 IndexingCompleted = 0;`
- L102 _private member_ `int32 IndexingFailed = 0;` — Retryable failures (Provider). Progress chip shows this under "Failed".
- L104 _private member_ `int32 IndexingPreProcessorFailed = 0;` — Pre-processor failures (permanent). Progress chip shows this under "Errors" separately.
- L105 _private member_ `uint32 IndexingEpoch = 0;`
- L106 _private member_ `FTimerHandle DismissTimerHandle;`
- L107 _private member_ `FTimerHandle ProgressUpdateTimerHandle;`
- L108 _private member_ `FTimerHandle PeriodicSaveTimerHandle;`
- L109 _private member_ `FTimerHandle PendingOpTimeoutHandle;`
- L114 _private member_ `bool bHasPendingIndexingOp = false;` — Set synchronously by UI handlers on click; makes bIsIndexing true before async indexing actually starts, so buttons disable visibly at click time. Cleared in OnIndexingStarted/OnBatchIndexingStarted, by a safety timer, or by ClearIndexingPending. Game-thread only.
- L116 _private prototype_ `void ClearIndexingPending();`
- L119 _private member_ `bool bIsSwitchingIndexType = false;` — Guards against concurrent SwitchIndexType calls. Only accessed on game thread.
- L123 _private member_ `static constexpr int32 SaveIndexThreshold = 100;` — Minimum number of completed indexing operations before auto-saving on dismiss.
- L126 _private member_ `TMap<int64, FIoHash> LoadedPackageHashes;` — Package hashes loaded from saved index, used for staleness checks during startup.
- L127 _private member_ `TMap<FName, FTimerHandle> PendingPackageSavedTimers;`
- L128 _private member_ `bool bFilesLoaded = false;`
- L131 _private member_ `std::atomic<bool> bIndexingInProgress{false};` — Tracks whether a batch indexing operation is in flight (thread-safe, Slate-independent).

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSemanticSearch, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSemanticSearch, Log, All);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/TextIndex/BM25Index.h` (Private)


#### struct `UE::SemanticSearch::FBM25Result`  
`struct FBM25Result`  
_L18-22_
- L20 _public member_ `int64 ID = -1;`
- L21 _public member_ `float Score = 0.0f;`

#### struct `UE::SemanticSearch::FPostingEntry`  
`struct FPostingEntry`  
_L24-33_
- L26 _public member_ `int64 DocID;`
- L27 _public member_ `uint8 TermFreq;` — capped at 255

#### class `UE::SemanticSearch::FBM25Index`  
`class FBM25Index`  
_L41-157_
- desc: Memory-efficient BM25 inverted index for text search over asset captions, keywords, and paths.
- L44 _public prototype_ `FBM25Index() = default;`
- L47 _public prototype_ `void Add(int64 ID, FStringView AssetPath, FStringView Caption, TConstArrayView<FString> Keywords);` — Add a document to the index. Tokenizes path, caption, and keywords.
- L50 _public prototype_ `void Remove(int64 ID);` — Remove a document from the index.
- L53 _public prototype_ `void Remove(TConstArrayView<int64> IDs);` — Batch remove multiple documents. Single sweep through affected posting lists.
- L56 _public prototype_ `void Add(TConstArrayView<int64> IDs, TConstArrayView<FString> Paths, TConstArrayView<FString> Captions, const TArray<TArray<FString>>& AllKeywords);` — Batch add multiple documents. Groups posting list insertions for efficiency.
- L88 _public prototype_ `void Search( FStringView Query, int32 K, const TSharedRef<const TArray<int64>>& IDFilter, TArray<uint32>& Scratch, FGraphEventRef IndexReadCompleteEvent, int32 MinShouldMatchPercent, TFunction<void(TArray<FBM25Result>&&)> Continuation) const;` — Search for documents matching the query. Continuation receives the top K results sorted by score descending. The continuation is owned (by-value TFunction) so the implementation may move it into a deferred task and invoke it asynchronously off the calling thread. @param Query                    Text query to tokenize and score against the index. @param K                        Maximum number of results to return. @param IDFilter                 Shared, immutable list of IDs to restrict the search to. Empty array means "no filter". Passed by TSharedRef so the deferred task body can keep ownership without copying — IDFilter can be large (the whole post-filter set of a previous query, hundreds of thousands of int64s) and the deep copy used to dominate setup time. @param Scratch                  Caller-owned scratch buffer reused across calls. @param IndexReadCompleteEvent   Optional event fired after the index-touching phase finishes (before sort + continuation), letting waiters release index mutations early. Pass an unset FGraphEventRef when not needed. @param MinShouldMatchPercent    Minimum percentage of unique productive query tokens a document must match to be eligible. 0 = pure OR (any single term match returns the doc). 100 = strict AND. Required match count is computed via ceiling against the number of query tokens that appear in at least one doc, e.g. 75% of 4 terms = 3. @param Continuation             Invoked exactly once with the result array.
- L98 _public prototype_ `void Clear();` — Remove all documents from the index.
- L101 _public prototype_ `int64 GetCount() const;` — Number of documents in the index.
- L104 _public prototype_ `bool Contains(int64 ID) const;` — Check if a document is already indexed.
- L107 _public prototype_ `void Serialize(FArchive& Ar);` — Serialize the index to an archive. Compacts before writing.
- L110 _public prototype_ `static TUniquePtr<FBM25Index> Deserialize(FArchive& Ar);` — Deserialize a BM25 index from an archive. Returns null on version mismatch or corrupt data.
- L113 _public prototype_ `int64 EstimateMemoryBytes() const;` — Estimate the memory footprint of this index in bytes.
- L120 _public prototype_ `void Compact();` — Compact the index: encode all staging posting lists into a consolidated byte buffer with frequency grouping + delta + varint encoding. Purges RemovedIDs. Call after bulk indexing completes.
- L123 _public prototype_ `bool IsCompacted() const;` — True if the index has been compacted and staging is empty.
- L133 _private prototype_ `static void DecodePostingList(const uint8* Data, uint32 Length, TArray<FPostingEntry>& OutEntries);` — Decode a compacted posting list, appending entries to OutEntries.
- L136 _private prototype_ `void GetMergedPostingList(uint32 TokenHash, FMergedPostingSet& OutEntries) const;` — Get the combined (compacted + staging) posting list for a token hash, keyed by DocID.
- L138 _private member_ `static constexpr float K1 = 1.5f;`
- L139 _private member_ `static constexpr float B = 0.75f;`
- L142 _private member_ `TArray<uint8> PostingData;` — --- Compacted data (read-only after Compact()) ---
- L143 _private member_ `TMap<uint32, FPostingListRef> PostingIndex;`
- L146 _private member_ `TMap<uint32, TArray<FPostingEntry>> StagingPostings;` — --- Staging (mutable, used during indexing and for post-compact edits) ---
- L149 _private member_ `TSet<int64> RemovedIDs;` — --- Lazy-delete set (filtered during search, purged on Compact) ---
- L152 _private member_ `TMap<int64, uint16> DocLengths;` — Per-document: doc length (token count)
- L155 _private member_ `int64 TotalTokenCount = 0;` — Global stats

#### struct `UE::SemanticSearch::FBM25Index::FPostingListRef`  
`struct FPostingListRef`  
_L126-130_
- L128 _public member_ `uint32 Offset;` — byte offset into PostingData
- L129 _public member_ `uint32 Length;` — byte length of encoded posting list

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L29 _function_ `friend FArchive& operator<<(FArchive& Ar, FPostingEntry& Entry)` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/VectorIndex/FlatVectorIndex.h` (Private)


#### class `UE::SemanticSearch::FFlatVectorIndex`  
`class FFlatVectorIndex : public IVectorIndex`  
_L22-58_
- inherits: `IVectorIndex`
- desc: Flat (brute-force) vector index using L2 distance. Stores raw vectors without compression. Exact search results. No training required. Good for small datasets or ground-truth comparison.
- L25 _public prototype_ `explicit FFlatVectorIndex(int32 InDimension);`
- L28 _public prototype_ `FFlatVectorIndex(const FFlatVectorIndex&) = delete;`
- L29 _public prototype_ `FFlatVectorIndex& operator=(const FFlatVectorIndex&) = delete;`
- L32 _public prototype_ `virtual void Train(TConstArrayView<float> Vectors, int64 NumVectors) override;` — IVectorIndex batch overrides
- L33 _public function_ `virtual bool IsTrained() const override`
- L34 _public prototype_ `virtual void Add(TConstArrayView<int64> IDs, TConstArrayView<float> Vectors) override;`
- L35 _public prototype_ `virtual void Remove(TConstArrayView<int64> IDs) override;`
- L36 _public prototype_ `virtual void Search( TConstArrayView<float> QueryVector, int32 K, const TSharedRef<const TArray<int64>>& IDFilter, float DistanceCutoff, TArray<uint32>& Scratch, FGraphEventRef IndexReadCompleteEvent, TFunction<void(TArray<FSearchResult>&&)> Continuation) const override;`
- L44 _public prototype_ `virtual int64 GetCount() const override;`
- L45 _public function_ `virtual int32 GetDimension() const override`
- L46 _public prototype_ `virtual TArray<uint8> Serialize() const override;`
- L47 _public prototype_ `virtual bool Contains(int64 ID) const override;`
- L48 _public prototype_ `virtual bool TryGetEmbedding(int64 ID, TArray<float>& OutEmbedding) const override;`
- L49 _public prototype_ `virtual int64 EstimateMemoryBytes() const override;`
- L51 _public prototype_ `static TUniquePtr<FFlatVectorIndex> Deserialize(TConstArrayView<uint8> Data, int32 ExpectedDimension);` — Deserialize a full flat index.
- L54 _private prototype_ `FFlatVectorIndex(int32 InDimension, faiss::IndexIDMap2* InIndex);`
- L56 _private member_ `int32 Dimension;`
- L57 _private member_ `faiss::IndexIDMap2* IndexWithIDs = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/VectorIndex/PQVectorIndex.h` (Private)


#### class `UE::SemanticSearch::FPQVectorIndex`  
`class FPQVectorIndex : public IQuantizedVectorIndex`  
_L28-88_
- inherits: `IQuantizedVectorIndex`
- desc: Product Quantization vector index. Compresses each vector into M subvectors of SubvectorSize dimensions each, quantized to nbits per subvector. With nbits=8 and SubvectorSize=8, a 768-dim vector compresses from 3072 bytes to 96 bytes (~32x). Must be trained before use. @param InSubvectorSize  Number of dimensions per subquantizer. Dimension must be divisible by this. @param InNBits          Bits per subquantizer code (8 = 256 centroids per subvector).
- L31 _public prototype_ `FPQVectorIndex(int32 InDimension, int32 InSubvectorSize = 8, int32 InNBits = 8);`
- L34 _public prototype_ `FPQVectorIndex(const FPQVectorIndex&) = delete;`
- L35 _public prototype_ `FPQVectorIndex& operator=(const FPQVectorIndex&) = delete;`
- L38 _public prototype_ `virtual void Train(TConstArrayView<float> Vectors, int64 NumVectors) override;` — IVectorIndex batch overrides
- L39 _public prototype_ `virtual bool IsTrained() const override;`
- L40 _public prototype_ `virtual void Add(TConstArrayView<int64> IDs, TConstArrayView<float> Vectors) override;`
- L41 _public prototype_ `virtual void Remove(TConstArrayView<int64> IDs) override;`
- L42 _public prototype_ `virtual void Search( TConstArrayView<float> QueryVector, int32 K, const TSharedRef<const TArray<int64>>& IDFilter, float DistanceCutoff, TArray<uint32>& Scratch, FGraphEventRef IndexReadCompleteEvent, TFunction<void(TArray<FSearchResult>&&)> Continuation) const override;`
- L50 _public prototype_ `virtual int64 GetCount() const override;`
- L51 _public function_ `virtual int32 GetDimension() const override`
- L52 _public prototype_ `virtual TArray<uint8> Serialize() const override;`
- L53 _public prototype_ `virtual TArray<uint8> Quantize(TConstArrayView<float> Vectors, int64 NumVectors) const override;`
- L54 _public prototype_ `virtual void AddQuantized(TConstArrayView<int64> IDs, TConstArrayView<uint8> Codes) override;`
- L55 _public prototype_ `virtual bool Contains(int64 ID) const override;`
- L56 _public prototype_ `virtual bool TryGetEmbedding(int64 ID, TArray<float>& OutEmbedding) const override;`
- L57 _public prototype_ `virtual bool Update(int64 OldID, int64 NewID) override;`
- L58 _public prototype_ `virtual int64 EstimateMemoryBytes() const override;`
- L60 _public function_ `int32 GetNumSubquantizers() const` — Number of subquantizers (Dimension / SubvectorSize).
- L63 _public function_ `int32 GetSubvectorSize() const` — Dimensions per subquantizer.
- L66 _public function_ `int32 GetNBits() const` — Bits per subquantizer code.
- L69 _public prototype_ `virtual TArray<uint8> SerializeCodebook() const override;` — IQuantizedVectorIndex overrides
- L70 _public prototype_ `virtual FIoHash GetCodebookHash() const override;`
- L73 _public prototype_ `static TUniquePtr<FPQVectorIndex> DeserializeCodebook(TConstArrayView<uint8> Data, int32 ExpectedDimension);` — Create a trained empty index from a serialized codebook.
- L76 _public prototype_ `static TUniquePtr<FPQVectorIndex> Deserialize(TConstArrayView<uint8> Data, int32 ExpectedDimension);` — Deserialize a full index.
- L79 _private prototype_ `FPQVectorIndex(int32 InDimension, int32 InSubvectorSize, int32 InNBits, faiss::IndexIDMap2* InIndex);`
- L81 _private member_ `int32 Dimension;`
- L82 _private member_ `int32 SubvectorSize;`
- L83 _private member_ `int32 NumSubquantizers;` — = Dimension / SubvectorSize
- L84 _private member_ `int32 NBits;`
- L85 _private member_ `faiss::IndexIDMap2* IndexWithIDs = nullptr;`
- L86 _private member_ `mutable FIoHash CachedCodebookHash;`
- L87 _private member_ `mutable bool bCodebookHashCached = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Private/VectorIndex/VectorIndexFactory.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L13 _prototype_ `TSharedPtr<IVectorIndex> CreateVectorIndex(ESemanticSearchIndexType Type, int32 Dimension, const USemanticSearchSettings* Settings);` (scope `UE::SemanticSearch`) — Create a fresh vector index for the given type. Quantized types start untrained.
- L16 _prototype_ `TSharedPtr<IVectorIndex> DeserializeVectorIndex(ESemanticSearchIndexType Type, TConstArrayView<uint8> Data, int32 Dimension);` (scope `UE::SemanticSearch`) — Deserialize a full index (with vectors) from bytes. Returns nullptr on failure.
- L19 _prototype_ `TSharedPtr<IVectorIndex> DeserializeCodebook(ESemanticSearchIndexType Type, TConstArrayView<uint8> Data, int32 Dimension);` (scope `UE::SemanticSearch`) — Deserialize a trained-but-empty codebook. Returns nullptr for Flat or on failure.
- L22 _prototype_ `FString GetCodebookFilename(ESemanticSearchIndexType Type);` (scope `UE::SemanticSearch`) — Get the codebook filename for an index type (e.g. "PQCodebook.bin"). Returns empty for types without codebooks.

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/AssetProcessorManager.h` (Public)


#### struct `UE::SemanticSearch::FAssetCaptionResult`  
`struct FAssetCaptionResult`  
_L27-31_
- L29 _public member_ `FString Caption;`
- L30 _public member_ `TArray<FString> Keywords;`

#### struct `UE::SemanticSearch::FAssetEmbeddingResult`  
`struct FAssetEmbeddingResult`  
_L33-36_
- L35 _public member_ `TArray<float> Embedding;`

#### struct `UE::SemanticSearch::FAssetQuantizedEmbeddingResult`  
`struct FAssetQuantizedEmbeddingResult`  
_L38-41_
- L40 _public member_ `TArray<uint8> QuantizedCodes;`

#### struct `UE::SemanticSearch::FAssetIndexingResult`  
`struct FAssetIndexingResult`  
_L44-50_
- desc: Combined result for a single-call indexing data fetch (caption + embedding or quantized codes).
- L46 _public member_ `FString Caption;`
- L47 _public member_ `TArray<FString> Keywords;`
- L48 _public member_ `TArray<float> Embedding;` — Non-empty for flat path
- L49 _public member_ `TArray<uint8> QuantizedCodes;` — Non-empty for quantized path

#### class `UE::SemanticSearch::FAssetProcessorManager`  
`class FAssetProcessorManager`  
_L52-148_
- L56 _public prototype_ `static FAssetProcessorManager& Get();`
- L58 _public prototype_ `bool GetCaptionData(const FAssetData& InAssetData, TUniqueFunction<void(FAssetCaptionResult&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable);`
- L59 _public prototype_ `bool GetEmbeddingData(const FAssetData& InAssetData, TUniqueFunction<void(FAssetEmbeddingResult&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable, bool bBuildOnMiss = true);`
- L60 _public prototype_ `bool GetQuantizedEmbeddingData(const FAssetData& InAssetData, const FIoHash& CodebookHash, TUniqueFunction<void(FAssetQuantizedEmbeddingResult&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable, bool bBuildOnMiss = true);`
- L67 _public prototype_ `bool GetIndexingData(const FAssetData& InAssetData, TUniqueFunction<void(FAssetIndexingResult&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable, bool bBuildOnMiss = true);` — Fetch caption + float embedding in a single call (both DDC requests issued in parallel). The callback fires once, after both have completed. Reason classifies any failure.
- L74 _public prototype_ `bool GetQuantizedIndexingData(const FAssetData& InAssetData, const FIoHash& CodebookHash, TUniqueFunction<void(FAssetIndexingResult&&, FString&&, EAssetIndexFailureReason)>&& InOnDataAvailable, bool bBuildOnMiss = true);` — Fetch caption + quantized codes in a single call (both DDC requests issued in parallel). The callback fires once, after both have completed. Reason classifies any failure.
- L82 _public prototype_ `void BatchGetIndexingData( TConstArrayView<FAssetData> Assets, TFunction<void(const FAssetData& Asset, FAssetIndexingResult&&, FString&&, EAssetIndexFailureReason)> OnAssetResult, bool bBuildOnMiss = true);` — Batch-fetch indexing data for multiple assets in a single DDC Get() call. On cache hit, the per-asset callback fires with the result. On cache miss, falls back to per-asset BuildDerivedData().
- L88 _public prototype_ `void BatchGetQuantizedIndexingData( TConstArrayView<FAssetData> Assets, const FIoHash& CodebookHash, TFunction<void(const FAssetData& Asset, FAssetIndexingResult&&, FString&&, EAssetIndexFailureReason)> OnAssetResult, bool bBuildOnMiss = true);` — Same as BatchGetIndexingData but for the quantized path.
- L95 _public prototype_ `void CancelAllTasks();` — Cancel all in-flight build tasks and clear the jobs map.
- L98 _public prototype_ `TSharedPtr<IAssetProcessor> GetProcessorForAsset(const FAssetData& InAssetData) const;` — Returns the processor for the asset's class. May return null.
- L103 _public prototype_ `TSet<FName> GetSupportedClassNames() const;` — Returns short class names of every asset class currently handled by a registered processor, including derived subclasses populated via PopulateChildClassesCache.
- L106 _public prototype_ `int32 GetSupportedAssetCount() const;` — Returns the total number of supported assets in indexed folders. Cached; invalidated on asset registry changes.
- L109 _public prototype_ `void InvalidateSupportedAssetCount();` — Force-invalidate the supported asset count cache (e.g. when IndexedPaths changes).
- L112 _public prototype_ `void ClearBuildCache();` — Clear all cached build tasks. Necessary before re-indexing to ensure fresh DDC lookups.
- L115 _public prototype_ `template<typename FAssetProcessor> void RegisterAssetProcessor();`
- L118 _public prototype_ `template<typename FAssetProcessor> void UnregisterAssetProcessor();`
- L122 _private prototype_ `FAssetProcessorManager();`
- L123 _private prototype_ `~FAssetProcessorManager();`
- L125 _private prototype_ `void RegisterAssetProcessor(TSharedRef<IAssetProcessor>&& AssetProcessor);`
- L126 _private prototype_ `void UnregisterAssetProcessor(UClass& Class);`
- L127 _private prototype_ `void PopulateChildClassesCache(UClass& Class, TSharedPtr<IAssetProcessor> Processor);`
- L128 _private prototype_ `int32 ComputeSupportedAssetCount() const;`
- L129 _private prototype_ `void InvalidateSupportedAssetCount(const FAssetData&);`
- L131 _private prototype_ `bool GetOrCreateTask(const FAssetData& InAssetData, TFunctionRef<void(const TSharedRef<Private::FSemanticSearchBuildCacheTask>&)> InApply);`
- L133 _private prototype_ `void OnObjectsReinstanced(const TMap<UObject*, UObject*>& InReplacementObjects);`
- L134 _private prototype_ `void OnModuleUnloaded(TConstArrayView<UPackage*> UnloadingPackages);`
- L135 _private prototype_ `void OnHotReloadComplete();`
- L137 _private member_ `FDelegateHandle OnObjectsReinstancedHandle;`
- L138 _private member_ `FDelegateHandle OnModuleUnloadedHandle;`
- L139 _private member_ `FDelegateHandle OnHotReloadCompleteHandle;`
- L140 _private member_ `FDelegateHandle OnAssetAddedHandle;`
- L141 _private member_ `FDelegateHandle OnAssetRemovedHandle;`
- L143 _private member_ `mutable TAtomic<int32> CachedSupportedAssetCount{-1};`
- L144 _private member_ `mutable FRWLock AssetTypeToProcessorLock;`
- L145 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<IAssetProcessor>> AssetTypeToProcessor;`
- L147 _private member_ `TStripedMap<32, DerivedData::FCacheKey, TSharedRef<Private::FSemanticSearchBuildCacheTask>> BuildsJobs;`
- L151 _function_ `template<typename FAssetProcessor> void FAssetProcessorManager::RegisterAssetProcessor()`
- L158 _function_ `template<typename FAssetProcessor> void FAssetProcessorManager::UnregisterAssetProcessor()`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/HybridSearchIndex.h` (Public)


#### struct `UE::SemanticSearch::FHybridSearchResult`  
`struct FHybridSearchResult`  
_L24-30_
- L26 _public member_ `int64 ID = -1;`
- L27 _public member_ `float RRFScore = 0.0f;`
- L28 _public member_ `float VectorDistance = -1.0f;` — -1 if not in vector results
- L29 _public member_ `float BM25Score = -1.0f;` — -1 if not in BM25 results

#### enum `UE::SemanticSearch::EAssetIndexFailureReason`  
`enum class EAssetIndexFailureReason : uint8`  
_L37-42_
- desc: Classification of an indexing failure. Populated by the layer that knows the cause (processor vs. embedding provider) and carried through to FHybridSearchIndex::MarkFailed so retryable (Provider) failures can be separated from permanent (PreProcessor) ones.
- L39 _public enumerator_ `None = 0` — Success.
- L40 _public enumerator_ `PreProcessor = 1` — Error before the backend call (e.g. missing thumbnail). Permanent, persisted.
- L41 _public enumerator_ `Provider = 2` — Error from the backend (connection, HTTP status, parse, server error). Retryable.

#### struct `UE::SemanticSearch::FSemanticSearchIndexStats`  
`struct FSemanticSearchIndexStats`  
_L50-67_
- L52 _public member_ `ESemanticSearchIndexType IndexType = ESemanticSearchIndexType::Flat;`
- L53 _public member_ `int32 VectorCount = 0;`
- L54 _public member_ `int32 BM25Count = 0;`
- L55 _public member_ `int32 Dimension = 0;`
- L56 _public member_ `int64 EstimatedVectorMemoryBytes = 0;`
- L57 _public member_ `int64 EstimatedBM25MemoryBytes = 0;`
- L58 _public member_ `bool bIsTrained = false;`
- L59 _public member_ `bool bSupportsQuantization = false;`
- L60 _public member_ `bool bIsInitialized = false;`
- L61 _public member_ `int32 SupportedAssetCount = 0;`
- L63 _public member_ `int32 FailedCount = 0;` — Retryable failures (e.g. provider/connection errors). Cleared on restart.
- L65 _public member_ `int32 PreProcessorFailedCount = 0;` — Permanent failures (e.g. asset has no thumbnail). Persisted via sidecar file; skipped by auto-retry.
- L66 _public member_ `bool bIsIndexing = false;`

#### class `UE::SemanticSearch::FHybridSearchIndex`  
`class FHybridSearchIndex`  
_L84-329_
- desc: Singleton that owns all search indices (vector + BM25) and fuses results using Reciprocal Rank Fusion (RRF). All mutations, searches, and index queries are serialized through an internal command queue with a dedicated consumer thread. Public methods enqueue work (microsecond lock) and return immediately; async operations deliver results via game-thread callbacks. GetCachedIndexStats() provides a lock-free snapshot of index metrics that is safe to call from any thread.
- L87 _public prototype_ `static FHybridSearchIndex& Get();`
- L92 _public prototype_ `void StartCommandQueue();` — Start the background consumer thread.
- L95 _public prototype_ `void StopCommandQueue();` — Stop the background consumer thread and join.
- L98 _public prototype_ `void DiscardPendingMutations();` — Discard all pending mutations (used during cancel).
- L103 _public prototype_ `void Add(FAssetData Asset, TArray<float> Embedding, FString Caption, TArray<FString> Keywords, uint32 IndexId);` — Add a single asset to both indices. Lazily creates vector index on first call.
- L107 _public prototype_ `void AddQuantized(FAssetData Asset, TArray<uint8> QuantizedCodes, FString Caption, TArray<FString> Keywords, uint32 IndexId);` — Add a single asset using pre-quantized codes (no float embedding).
- L115 _public prototype_ `void MarkFailed(int64 AssetId, EAssetIndexFailureReason Reason, uint32 IndexId);` — Record that an asset failed to index. The reason decides which bucket it lands in: - EAssetIndexFailureReason::PreProcessor  → permanent bucket (persisted; not auto-retried). - EAssetIndexFailureReason::Provider      → retryable bucket (in-session; cleared by "Retry failed").
- L118 _public prototype_ `void ClearFailedState(int64 AssetId);` — Remove an asset ID from both failed sets. Used by the retry button.
- L125 _public prototype_ `void PurgePreProcessorFailedNotIn(TSet<int64> ValidIDs);` — Purge pre-processor-failed IDs that are not in the given set of currently-valid IDs. Called after OnFilesLoaded to drop stale entries left over from deletions or re-saves (where the DDC key changed and the old ID is no longer meaningful).
- L128 _public prototype_ `void Remove(FAssetData Asset);` — Remove a single asset from both indices.
- L131 _public prototype_ `void RemoveByPath(FString AssetPath);` — Remove by path string (for when the asset has already been deleted).
- L134 _public prototype_ `void RemoveById(int64 AssetId);` — Remove by pre-computed ID.
- L137 _public prototype_ `void SetVectorIndex(TSharedPtr<IVectorIndex> NewIndex);` — Replace the vector index. Used during index type switching.
- L140 _public prototype_ `void ClearBM25();` — Clear the BM25 text index.
- L149 _public prototype_ `void Save(FString FilePath, FString PreProcessorFailedPath, TMap<int64, FIoHash> PackageHashes);` — Save the full index (vector + BM25 + package hashes) to a file, and the pre-processor-failed ID list to a sidecar file alongside it. @param FilePath					Destination file path for the main index. @param PreProcessorFailedPath	Sidecar file path for the pre-processor-failed IDs. @param PackageHashes				Per-asset PackageSavedHash for staleness detection on next load.
- L164 _public prototype_ `void SearchAsync(FString QueryText, TArray<float> QueryEmbedding, int32 K, TArray<int64> IDFilter, float DistanceCutoff, TFunction<void(TArray<FHybridSearchResult>&&)> Callback);` — Async search. Fuses vector + BM25 results via RRF. @param QueryText			Text query for BM25 search. @param QueryEmbedding	Embedding for vector search. Can be empty if not yet available. @param K					Number of results to return. @param IDFilter			If non-empty, only search among these IDs. @param DistanceCutoff	Forwarded to the vector search; results with Distance >= cutoff are dropped before fusion. Pass TNumericLimits<float>::Max() for "no cutoff". @param Callback			Receives results on the game thread.
- L175 _public prototype_ `void QuantizeAsync(TArray<float> Embedding, TFunction<void(TArray<uint8>&&, bool bSuccess)> Callback);` — Async quantize. Encodes a float embedding into quantized codes on the consumer thread, avoiding races with concurrent index mutations. @param Embedding		Float embedding to quantize. @param Callback		Receives quantized codes on the consumer thread. bSuccess is false if no trained quantized index is available.
- L183 _public prototype_ `void ContainsAsync(TArray<int64> IDs, TFunction<void(TSet<int64>&&)> Callback);` — Async contains check. Tests which IDs are present in the index on the consumer thread. @param IDs		IDs to check. @param Callback	Receives the set of IDs that are present, on the game thread.
- L191 _public prototype_ `void ExtractEmbeddingsAsync(TArray<int64> CandidateIDs, TFunction<void(TArray<int64>&& IDs, TArray<float>&& Vectors, int32 Dimension)> Callback);` — Async extraction of all stored vectors for training. Runs on the consumer thread. @param CandidateIDs	IDs to try extracting embeddings for. @param Callback		Receives matched IDs, concatenated vectors, and dimension on the game thread.
- L197 _public prototype_ `bool IsHybridEnabled() const;` — Whether BM25 hybrid search is enabled (from settings).
- L200 _public prototype_ `void ResetBM25AndFailedState();` — Reset BM25 and failed sets (enqueued to consumer thread). Used when re-indexing all assets from scratch.
- L206 _public prototype_ `void IsFailedAsync(TArray<int64> IDs, TFunction<void(TSet<int64>&&)> Callback);` — Async failed-set check. Returns the union of retryable and pre-processor failed IDs on the game thread. Used by pre-index skip paths that treat any failure as "don't retry".
- L214 _public prototype_ `void IsRetryableFailedAsync(TArray<int64> IDs, TFunction<void(TSet<int64>&&)> Callback);` — Async retryable-failed check. Returns only the in-session retryable failed IDs (NOT pre-processor failures). Used by the "Retry failed" button so permanent failures are excluded from retries.
- L221 _public prototype_ `FSemanticSearchIndexStats GetCachedIndexStats() const;` — Get a snapshot of index stats. Updated atomically by the consumer thread after each mutation batch — safe to call from any thread with no locking. Fills IndexType and SupportedAssetCount are left to the caller.
- L224 _public prototype_ `FIoHash GetCachedCodebookHash() const;` — Get the codebook hash from cached stats. Returns default FIoHash if not quantized/trained.
- L231 _public prototype_ `bool LoadFromFile(const FString& FilePath, TMap<int64, FIoHash>& OutPackageHashes);` — Load a previously saved index from a file. Replaces current index state. Must be called before StartCommandQueue (not thread-safe with the consumer thread). @param OutPackageHashes	Filled with per-asset PackageSavedHash from save time (for staleness checks).
- L238 _public prototype_ `void LoadPreProcessorFailedFromFile(const FString& FilePath);` — Load the pre-processor-failed ID list from a sidecar file. Missing file = empty set, no warning (expected on first run and after user deletes the file to reset). Corrupt file logs one warning and initializes empty. Must be called before StartCommandQueue.
- L241 _public prototype_ `static FString GetCodebookPath(ESemanticSearchIndexType Type);` — Get the path to the shared codebook file for the given index type (in plugin Resources/).
- L244 _public prototype_ `uint32 GetIndexId() const;` — Get the current index ID (changes on index swap/invalidation).
- L247 _public prototype_ `void InvalidateIndexId();` — Invalidate the current IndexId so stale callbacks are dropped.
- L250 _public prototype_ `void EnsureInitialized(int32 EmbeddingDimension);` — Ensure the index is initialized with a valid (possibly empty) vector index.
- L253 _public function_ `FOnIndexChanged& OnIndexChanged()` — Delegate broadcast when the index changes (e.g. after switching type or retraining). Game thread only.
- L260 _private prototype_ `FHybridSearchIndex();`
- L261 _private prototype_ `~FHybridSearchIndex();`
- L265 _private prototype_ `void ProcessCommandBatch();`
- L266 _private prototype_ `void EnsureProcessingTask(UE::Tasks::ETaskPriority Priority = UE::Tasks::ETaskPriority::BackgroundNormal);`
- L267 _private prototype_ `void UpdateCachedStats();`
- L271 _private prototype_ `TSharedPtr<IVectorIndex> GetVectorIndex() const;`
- L272 _private prototype_ `bool Contains(const FAssetData& Asset) const;`
- L273 _private prototype_ `FBM25Index& GetBM25Index();`
- L277 _private prototype_ `void AddDirect(const FAssetData& Asset, TConstArrayView<float> Embedding, FStringView Caption, TConstArrayView<FString> Keywords);`
- L279 _private prototype_ `void AddDirect(TConstArrayView<FAssetData> Assets, TConstArrayView<float> AllEmbeddings, TConstArrayView<FString> Captions, const TArray<TArray<FString>>& AllKeywords);`
- L284 _private prototype_ `void AddQuantizedDirect(const FAssetData& Asset, TConstArrayView<uint8> QuantizedCodes, FStringView Caption, TConstArrayView<FString> Keywords);`
- L286 _private prototype_ `void AddQuantizedDirect(TConstArrayView<FAssetData> Assets, const TArray<TArray<uint8>>& AllQuantizedCodes, TConstArrayView<FString> Captions, const TArray<TArray<FString>>& AllKeywords);`
- L291 _private prototype_ `void RemoveDirect(const FAssetData& Asset);`
- L292 _private prototype_ `void RemoveDirect(FStringView AssetPath);`
- L293 _private prototype_ `void RemoveDirect(int64 AssetID);`
- L294 _private prototype_ `void RemoveDirect(TConstArrayView<int64> IDs);`
- L296 _private prototype_ `void SetVectorIndexDirect(TSharedPtr<IVectorIndex> NewIndex);`
- L298 _private prototype_ `void MarkFailedDirect(int64 AssetID, EAssetIndexFailureReason Reason);`
- L299 _private prototype_ `void ClearFailedStateDirect(int64 AssetID);`
- L300 _private prototype_ `void PurgePreProcessorFailedNotInDirect(const TSet<int64>& ValidIDs);`
- L302 _private prototype_ `void SearchDirect( FString QueryText, TArray<float> QueryEmbedding, int32 K, TArray<int64> IDFilter, float DistanceCutoff, FGraphEventArray* OutIndexReadEvents, TFunction<void(TArray<FHybridSearchResult>&&)> Continuation) const;`
- L311 _private prototype_ `TArray64<uint8> SerializeIndexForSave(const TMap<int64, FIoHash>& PackageHashes) const;`
- L312 _private prototype_ `TArray64<uint8> SerializePreProcessorFailedForSave() const;`
- L314 _private prototype_ `static void WriteBytesToFile(const FString& FilePath, TArray64<uint8> Bytes);`
- L319 _private member_ `TSet<int64> FailedAssets;` — Retryable failures. In-session only; cleared by the "Retry failed" button and on force-rebuild.
- L322 _private member_ `TSet<int64> PreProcessorFailedAssets;` — Permanent failures. Persisted via sidecar file; skipped by auto-retry and the "Retry failed" button.
- L323 _private member_ `std::atomic<bool> bInitialized{false};`
- L324 _private member_ `std::atomic<uint32> IndexId{0};`
- L325 _private member_ `TSharedPtr<IVectorIndex> VectorIndex;`
- L326 _private member_ `TUniquePtr<FBM25Index> BM25Index;`
- L327 _private member_ `TUniquePtr<FCommandQueueData> QueueData;`
- L328 _private member_ `FOnIndexChanged OnIndexChangedDelegate;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L45 _function_ `inline bool IsPreProcessorFailure(EAssetIndexFailureReason Reason)` (scope `UE::SemanticSearch`) — Pre-processor failures are permanent; Provider failures are retryable.
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIndexChanged, bool );`
- L72 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIndexChanged, bool );` (scope `UE::SemanticSearch`)
- L332 _prototype_ `int64 GetAssetIndexID(const FAssetData& Asset);` (scope `UE::SemanticSearch`) — Compute the stable int64 ID used for an asset in the indices.
- L333 _prototype_ `int64 GetAssetIndexID(FStringView AssetPath);` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/ISemanticSearchModule.h` (Public)


#### class `UE::SemanticSearch::ISemanticSearchModule`  
`class ISemanticSearchModule : public IModuleInterface`  
_L16-103_
- inherits: `IModuleInterface`
- L19 _public function_ `static ISemanticSearchModule& Get()`
- L25 _public prototype_ `virtual void RegisterEmbeddingProvider(TUniquePtr<IEmbeddingProvider>&& EmbeddingProvider, bool bRebuildIndex) = 0;`
- L28 _public prototype_ `virtual TSharedPtr<IEmbeddingProvider> GetEmbeddingProvider() const = 0;` — Returns the active embedding provider, or nullptr if none has been registered.
- L45 _public prototype_ `virtual void Initialize() = 0;` — Load the saved index, start the consumer queue, and subscribe to asset-registry events using the currently registered embedding provider. Idempotent — repeat calls are no-ops. StartupModule() invokes this automatically unless the console variable `SemanticSearch.DelayInitialization=true` is set. Modules that want to install a custom embedding provider before the index is built must set this CVar via a config file — for example, add to a project's DefaultEngine.ini: [ConsoleVariables] SemanticSearch.DelayInitialization=1 Then register the provider via RegisterEmbeddingProvider() and call Initialize() to finalize startup. Must be invoked on the game thread.
- L48 _public prototype_ `virtual bool IsInitialized() const = 0;` — True once Initialize() has run successfully.
- L50 _public prototype_ `virtual void IndexAsset(const FAssetData& AssetData) = 0;` — Index a single asset, always building from the backend if not already cached.
- L53 _public prototype_ `virtual void IndexAssets(TConstArrayView<FAssetData> Assets) = 0;` — Index a batch of assets. Filters through processor check, uses batch DDC paths, and shows progress.
- L56 _public prototype_ `static bool IsInIndexedFolder(const FAssetData& AssetData);` — Returns true if the asset is in a folder configured for indexing.
- L59 _public prototype_ `static bool IsInIndexedFolder(FStringView PackagePath);` — Returns true if the given package path is in a folder configured for indexing.
- L61 _public prototype_ `virtual FSemanticSearchIndexStats GetIndexStats() const = 0;` — Get current index statistics.
- L64 _public prototype_ `virtual void SwitchIndexType(ESemanticSearchIndexType NewType) = 0;` — Switch to a different index type. Re-indexes all assets.
- L67 _public prototype_ `virtual void IndexAllAssets(bool bForceBuild = false) = 0;` — Re-index all supported assets. When bForceBuild is true, clears the index and always builds on DDC miss.
- L70 _public prototype_ `virtual void RetrainIndex() = 0;` — Retrain the current quantized index from scratch (new codebook). No-op for flat index.
- L73 _public prototype_ `virtual void CancelIndexing() = 0;` — Cancel all in-flight indexing tasks, drop the job queue, and dismiss progress UI.
- L76 _public prototype_ `virtual bool IsIndexingInProgress() const = 0;` — Returns true while a batch indexing operation is in flight (safe to call from any thread).
- L86 _public prototype_ `virtual void SetIndexingPending() = 0;` — Mark an indexing-related operation as pending. Call from UI button handlers immediately on click so `FSemanticSearchIndexStats::bIsIndexing` flips true synchronously (before the async enumeration / filter / DDC work that would normally set it), keeping the button visibly disabled instead of clickable while we spin up. Cleared automatically when real indexing activity starts (OnIndexingStarted / OnBatchIndexingStarted), when no work ends up being queued, or on a safety timeout.
- L96 _public prototype_ `virtual void SearchAsync( const FString& QueryText, TConstArrayView<float> QueryEmbedding, int32 K, TConstArrayView<int64> IDFilter, float DistanceCutoff, TFunction<void(TArray<FHybridSearchResult>&&)> Callback) = 0;` — Perform a hybrid search asynchronously via the index command queue. The callback is invoked on the game thread with the results. @param DistanceCutoff  Forwarded to the vector search; results with Distance >= cutoff are dropped before fusion. Pass TNumericLimits<float>::Max() for "no cutoff".

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Implementations/ThumbnailBaseProcessor.h` (Public)


#### class `UE::SemanticSearch::FThumbnailBaseAssetProcessor`  
`class FThumbnailBaseAssetProcessor : public IAssetProcessor`  
_L25-36_
- inherits: `IAssetProcessor`
- desc: Reusable base class for asset processors that operate via on-disk thumbnails. Derived classes must: - Implement GetProcessSubBucketName() tell the system where to store the derived - Implement GetMetadata(InAsset) to supply structured per-asset metadata. Derived classes may optionally override GetRevision() to bump cached data if they their implementation details.
- L29 _public prototype_ `virtual TSharedPtr<FJsonObject> GetMetadata(const TSharedRef<const FAssetData>& InAsset) const = 0;` — Returns structured metadata for the asset. Called from GenerateCaptionRequest.
- L32 _public function_ `virtual int32 GetRevision() const` — Bump this to invalidate previously cached derived data.
- L34 _public prototype_ `virtual bool GenerateAssetHash(const FAssetData& Asset, FMemoryHasherBlake3& InHasher) const override;`
- L35 _public prototype_ `virtual void GenerateCaptionRequest(const TSharedRef<const FAssetData>& InAsset, bool bCanDisruptUser, DerivedData::FRequestOwner& RequestOwner, FOnRequestComplete OnRequestComplete) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Interfaces/IAssetProcessor.h` (Public)


#### class `UE::SemanticSearch::IAssetProcessor`  
`class IAssetProcessor`  
_L32-49_
- L40 _public prototype_ `constexpr virtual FStringView GetProcessSubBucketName() const = 0;` — Used to separate the generated data into their own bucket Use using the name of your type is acceptable value if it is unique
- L42 _public prototype_ `virtual UClass& GetSupportedClass() const = 0;`
- L43 _public prototype_ `virtual bool SupportDerivedClasses() const = 0;`
- L45 _public prototype_ `virtual bool GenerateAssetHash(const FAssetData& Asset, FMemoryHasherBlake3& InHasher) const = 0;`
- L46 _public prototype_ `virtual void GenerateCaptionRequest(const TSharedRef<const FAssetData>& InAsset, bool bCanDisruptUser, DerivedData::FRequestOwner& RequestOwner, FOnRequestComplete OnRequestComplete) const = 0;`
- L48 _public prototype_ `virtual ~IAssetProcessor() = default;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L30 _typedef_ `using FOnRequestComplete = TUniqueFunction<void(bool bHasGeneratedCaptionRequest, FCaptionRequest&& CaptionRequest, FString&& ErrorMessage, EAssetIndexFailureReason Reason)>;` (scope `UE::SemanticSearch`) — Processor-generated caption-request result. On success, bHasGeneratedCaptionRequest=true and Reason=None. On failure, bHasGeneratedCaptionRequest=false and Reason classifies the failure: - PreProcessor: thumbnail missing, unsupported media format, etc. Permanent. - Provider:     reserved; processors normally only emit PreProcessor failures.

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Interfaces/IEmbeddingProvider.h` (Public)


#### struct `UE::SemanticSearch::FAssetMedia`  
`struct FAssetMedia`  
_L20-27_
- desc: A single media payload attached to a caption request.
- L23 _public member_ `FString MimeType;` — MIME type: "image/png", "application/json", "audio/mpeg", etc.
- L26 _public member_ `TArray<uint8> Data;` — Raw media bytes

#### struct `UE::SemanticSearch::FCaptionRequest`  
`struct FCaptionRequest`  
_L33-43_
- desc: Request to generate a caption (and keywords) for an asset. Can include media content and structured metadata.
- L35 _public member_ `FString AssetPath;`
- L36 _public member_ `FString AssetType;`
- L39 _public member_ `TArray<FAssetMedia> AssetMedia;` — Asset content — can be combination of images, text, JSON
- L42 _public member_ `TSharedPtr<FJsonObject> Metadata;` — Structured metadata (asset dimension, properties, etc.)

#### struct `UE::SemanticSearch::FCaptionResponse`  
`struct FCaptionResponse`  
_L49-59_
- desc: Response from caption generation. Success if ErrorMessage is empty (FailureReason == None).
- L51 _public member_ `FString ErrorMessage;`
- L54 _public member_ `EAssetIndexFailureReason FailureReason = EAssetIndexFailureReason::None;` — Classification of the failure, if any. Populated by the provider layer.
- L56 _public member_ `FString Caption;`
- L58 _public member_ `TArray<FString> Keywords;`

#### struct `UE::SemanticSearch::FEmbeddingResponse`  
`struct FEmbeddingResponse`  
_L65-76_
- desc: Response from embedding generation. Success if ErrorMessage is empty (FailureReason == None).
- L67 _public member_ `FString ErrorMessage;`
- L70 _public member_ `EAssetIndexFailureReason FailureReason = EAssetIndexFailureReason::None;` — Classification of the failure, if any. Populated by the provider layer.
- L72 _public member_ `TArray<float> Embedding;`
- L75 _public member_ `FString ModelVersion;` — Version of the model that generated this embedding

#### class `UE::SemanticSearch::IEmbeddingProvider`  
`class IEmbeddingProvider`  
_L87-131_
- desc: Interface for embedding generation providers. Can support both remote (HTTP API) and local (on-device) implementations.
- L90 _public prototype_ `virtual ~IEmbeddingProvider() = default;`
- L93 _public prototype_ `virtual int32 GetEmbeddingDimension() const = 0;` — Embedding vector dimensionality
- L103 _public prototype_ `virtual void GenerateCaptionAsync( FCaptionRequest&& Request, FOnCaptionComplete&& OnComplete, DerivedData::FRequestOwner* RequestOwner) = 0;` — Generate a caption and keywords for an asset. Called during indexing to describe the asset content. @param Request The caption request with asset media and metadata @param OnComplete Callback invoked when caption is ready @param RequestOwner The request owner is optional argument to help the derived data build track it subtasks
- L116 _public prototype_ `virtual void GenerateEmbeddingAsync( const FStringView Text, FOnEmbeddingComplete&& OnComplete, DerivedData::FRequestOwner* RequestOwner) = 0;` — Generate embedding for a text string. Called during indexing (with caption text) and at search time (with query text). @param Text The text to embed (caption or search query) @param OnComplete Callback invoked when embedding is ready @param RequestOwner The request owner is optional argument to help the derived data build track it subtasks
- L124 _public prototype_ `virtual uint32 GetConfigHash() const = 0;` — Get a hash that represents the configuration of this embedding provider
- L130 _public function_ `virtual void CancelAllPendingRequests()` — Cancel all pending requests that have not yet been dispatched. Default implementation is no-op for providers that don't queue requests.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SemanticSearch` (scope `UE`)
- L79 _typedef_ `using FOnCaptionComplete = TUniqueFunction<void (FCaptionResponse&&)>;` (scope `UE::SemanticSearch`)
- L81 _typedef_ `using FOnEmbeddingComplete = TUniqueFunction<void (FEmbeddingResponse&&)>;` (scope `UE::SemanticSearch`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Interfaces/IQuantizedVectorIndex.h` (Public)


#### class `UE::SemanticSearch::IQuantizedVectorIndex`  
`class IQuantizedVectorIndex : public IVectorIndex`  
_L20-50_
- inherits: `IVectorIndex`
- desc: Interface for vector indices that support quantization (PQ, RaBitQ, etc.). Adds quantization, codebook serialization, and pre-quantized insertion to the base IVectorIndex interface. Callers should check IVectorIndex::SupportsQuantization() before casting to this type via static_cast.
- L23 _public function_ `virtual bool SupportsQuantization() const override final`
- L28 _public prototype_ `virtual TArray<uint8> Quantize(TConstArrayView<float> Vectors, int64 NumVectors) const = 0;` — Quantize vectors into compressed form (e.g. PQ codes, RaBitQ codes).
- L30 _public function_ `TArray<uint8> Quantize(TConstArrayView<float> Vector) const`
- L38 _public prototype_ `virtual void AddQuantized(TConstArrayView<int64> IDs, TConstArrayView<uint8> Codes) = 0;` — Add pre-quantized vectors directly, skipping encoding.
- L40 _public function_ `void AddQuantized(int64 ID, TConstArrayView<uint8> Codes)`
- L46 _public prototype_ `virtual TArray<uint8> SerializeCodebook() const = 0;` — Serialize the trained codebook/quantizer state (no vector data).
- L49 _public prototype_ `virtual FIoHash GetCodebookHash() const = 0;` — Blake3 hash of the serialized codebook. Used for DDC invalidation and save-file validation.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Interfaces/IVectorIndex.h` (Public)


#### struct `UE::SemanticSearch::FSearchResult`  
`struct FSearchResult`  
_L16-20_
- L18 _public member_ `int64 ID = -1;`
- L19 _public member_ `float Distance = 0.0f;`

#### class `UE::SemanticSearch::IVectorIndex`  
`class IVectorIndex`  
_L25-124_
- desc: Abstract interface for vector similarity search indices.
- L28 _public prototype_ `virtual ~IVectorIndex() = default;`
- L33 _public prototype_ `virtual void Train(TConstArrayView<float> Vectors, int64 NumVectors) = 0;` — Train the index on representative vectors. No-op for flat indices.
- L36 _public prototype_ `virtual bool IsTrained() const = 0;` — Whether the index has been trained and is ready for Add/Search.
- L39 _public prototype_ `virtual void Add(TConstArrayView<int64> IDs, TConstArrayView<float> Vectors) = 0;` — Add multiple vectors with corresponding IDs. Index must be trained first.
- L42 _public prototype_ `virtual void Remove(TConstArrayView<int64> IDs) = 0;` — Remove vectors by IDs.
- L64 _public prototype_ `virtual void Search( TConstArrayView<float> QueryVector, int32 K, const TSharedRef<const TArray<int64>>& IDFilter, float DistanceCutoff, TArray<uint32>& Scratch, FGraphEventRef IndexReadCompleteEvent, TFunction<void(TArray<FSearchResult>&&)> Continuation) const = 0;` — Search for K nearest neighbors. Continuation receives the results sorted by ascending distance. The continuation is owned (by-value TFunction) so implementations may move it into a deferred task and invoke it asynchronously off the calling thread. @param IDFilter        Shared, immutable list of IDs to restrict the search to. Empty array means "no filter". @param DistanceCutoff  Drop results whose distance is >= this value before returning. Pass TNumericLimits<float>::Max() for "no cutoff". Lets callers push their distance threshold down so the index can avoid materializing results that would be discarded downstream anyway. @param Scratch         Caller-owned scratch buffer that can be reused to speed up some algo @param IndexReadCompleteEvent Optional FGraphEventRef the implementation must DispatchSubsequents() on after its index-touching phase finishes. @param Continuation    Invoked exactly once with the result array.
- L74 _public prototype_ `virtual int64 GetCount() const = 0;` — Number of vectors currently in the index.
- L77 _public prototype_ `virtual int32 GetDimension() const = 0;` — Embedding dimension.
- L80 _public prototype_ `virtual TArray<uint8> Serialize() const = 0;` — Serialize the full index to a byte array.
- L83 _public function_ `virtual bool SupportsQuantization() const` — Whether this index supports quantization. If true, can static_cast to IQuantizedVectorIndex.
- L87 _public function_ `void Add(int64 ID, TConstArrayView<float> Vector)`
- L92 _public function_ `bool Remove(int64 ID)`
- L101 _public function_ `virtual bool Contains(int64 ID) const` — Returns true if a vector with the given ID exists in the index.
- L104 _public function_ `virtual bool TryGetEmbedding(int64 ID, TArray<float>& OutEmbedding) const` — Retrieve the embedding for a given ID. Returns false if not supported or ID not found.
- L107 _public function_ `virtual int64 EstimateMemoryBytes() const` — Estimated memory usage in bytes. Returns 0 if not implemented.
- L113 _public function_ `virtual bool Update(int64 OldID, int64 NewID)` — Re-key a vector from OldID to NewID, preserving the embedding data. Returns true if the vector was found and updated, false if OldID was not in the index.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SemanticSearch` (scope `UE`)

### `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Settings/SemanticSearchSettings.h` (Public)


#### enum `ESemanticSearchIndexType`  
`enum class ESemanticSearchIndexType : uint8`  
_L9-13_
- reflection: `UENUM()`
- L11 _public enumerator_ `Flat UMETA(DisplayName = "Flat (Exact)")`
- L12 _public enumerator_ `PQ UMETA(DisplayName = "PQ (Compressed)")`

#### enum `ESemanticSearchEmbeddingProvider`  
`enum class ESemanticSearchEmbeddingProvider : uint8`  
_L16-19_
- reflection: `UENUM()`
- L18 _public enumerator_ `OpenAI UMETA(DisplayName = "OpenAI-compatible API")`

#### class `USemanticSearchSettings`  
`class USemanticSearchSettings : public UDeveloperSettings`  
_L22-170_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, DefaultConfig, MinimalAPI, meta = (DisplayName = "Semantic Search"))`
- inherits: `UDeveloperSettings`
- L27 _public function_ `static const USemanticSearchSettings* Get()`
- L32 _public function_ `virtual FName GetContainerName() const override`
- L33 _public function_ `virtual FName GetCategoryName() const override`
- L34 _public function_ `virtual FName GetSectionName() const override`
- L36 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _public member_ `TArray<FDirectoryPath> IndexedPaths = { {TEXT("/")} }` — `UPROPERTY(EditAnywhere, Config, Category = "Indexing", meta = (ToolTip = "Content browser paths to include in the semantic search index.", ContentDir, LongPackageName, ForceShowEngineContent, ForceShowPluginContent))`
- L45 _public member_ `bool bAutoIndexCachedOnStartup = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Indexing", meta = (ToolTip = "When true, automatically loads cached embeddings from DDC on editor startup, avoiding the need to manually refresh the index."))`
- L49 _public member_ `bool bAutoIndexUncachedOnStartup = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Indexing", meta = (ToolTip = "When true, assets without cached embeddings are sent to the backend during auto-indexing on startup. When false, only DDC-cached assets are loaded. Ignored if Auto Index Cached On Startup is disabled. WARNING: This can be slow for large projects with many uncached assets."))`
- L53 _public member_ `bool bAutoIndexOnSave = true;` — `UPROPERTY(EditAnywhere, Config, Category = "Indexing", meta = (ToolTip = "When true, assets are automatically re-indexed when saved or updated on disk."))`
- L57 _public member_ `ESemanticSearchEmbeddingProvider Provider = ESemanticSearchEmbeddingProvider::OpenAI;` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (ToolTip = "Which embedding/captioning backend to use. Changes take effect immediately; the vector index is rebuilt as Flat at the new dimension."))`
- L63 _public member_ `FString CaptioningBaseUrl = TEXT("htt` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, ToolTip = "Base URL for the captioning endpoint. Provider appends '/chat/completions'. Defaults to OpenAI; can point at any OpenAI-compatible server like LiteLLM or Ollama."))` — api.openai.com/v1");
- L70 _public member_ `FString CaptioningApiKey;` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, PasswordField, ToolTip = "API key for the captioning endpoint. Sent as 'Authorization: Bearer <key>'."))`
- L76 _public member_ `FString CaptioningModel = TEXT("gpt` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, ToolTip = "Vision-capable chat completions model used to generate tags + caption for an asset."))`
- L82 _public member_ `FString EmbeddingBaseUrl = TEXT("htt` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, ToolTip = "Base URL for the embedding endpoint. Provider appends '/embeddings'. Can differ from the captioning base URL (e.g., embeddings on a local server, captions on OpenAI)."))` — api.openai.com/v1");
- L89 _public member_ `FString EmbeddingApiKey;` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, PasswordField, ToolTip = "API key for the embedding endpoint. Sent as 'Authorization: Bearer <key>'."))`
- L95 _public member_ `FString EmbeddingModel = TEXT("tex` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, ToolTip = "Embedding model used to embed the asset caption returned from the captioning model."))`
- L102 _public member_ `int32 EmbeddingDimension = 512;` — `UPROPERTY(EditAnywhere, Config, Category = "Provider", meta = (EditCondition = "Provider == ESemanticSearchEmbeddingProvider::OpenAI", EditConditionHides, ClampMin = "1", ClampMax = "3072", ToolTip = "Embedding vector dimension. Sent as the 'dimensions' parameter to OpenAI embeddings endpoint."))`
- L107 _public member_ `int32 MaxRetries = 1;` — `UPROPERTY(EditAnywhere, Config, Category = "HTTP", meta = (ClampMin = "0", ClampMax = "10", ToolTip = "Number of times to retry an HTTP request on a retryable failure (429, 5xx)."))`
- L112 _public member_ `float RetryTimeoutSeconds = 300.0f;` — `UPROPERTY(EditAnywhere, Config, Category = "HTTP", meta = (ClampMin = "1.0", ClampMax = "3600.0", ToolTip = "Maximum total wall-clock seconds the retry manager will keep retrying a single request before giving up."))`
- L117 _public member_ `int32 MaxConcurrentCaptionRequests = 256;` — `UPROPERTY(EditAnywhere, Config, Category = "HTTP", meta = (ClampMin = "1", ClampMax = "10000", ToolTip = "Maximum concurrent caption HTTP requests in flight. Excess requests are queued."))`
- L122 _public member_ `int32 MaxConcurrentEmbedRequests = 256;` — `UPROPERTY(EditAnywhere, Config, Category = "HTTP", meta = (ClampMin = "1", ClampMax = "10000", ToolTip = "Maximum concurrent embedding HTTP requests in flight. Excess requests are queued."))`
- L126 _public member_ `ESemanticSearchIndexType IndexType = ESemanticSearchIndexType::PQ;` — `UPROPERTY(VisibleAnywhere, Config, Category = "Vector Index", meta = (ToolTip = "Index type is managed via Tools > Semantic Search."))`
- L132 _public member_ `int32 PQSubvectorSize = 8;` — `UPROPERTY(EditAnywhere, Config, Category = "Vector Index", meta = (EditCondition = "IndexType == ESemanticSearchIndexType::PQ", EditConditionHides, ClampMin = "1", ClampMax = "64", ToolTip = "Number of dimensions per subquantizer. Embedding dimension must be divisible by this."))`
- L138 _public member_ `int32 PQNBits = 8;` — `UPROPERTY(EditAnywhere, Config, Category = "Vector Index", meta = (EditCondition = "IndexType == ESemanticSearchIndexType::PQ", EditConditionHides, ClampMin = "4", ClampMax = "16", ToolTip = "Bits per subquantizer code. 8 = 256 centroids per subvector."))`
- L141 _public member_ `bool bEnableHybridSearch = true;` — `UPROPERTY(EditAnywhere, Config, Category = "Search")`
- L147 _public member_ `int32 RRFConstant = 60;` — `UPROPERTY(EditAnywhere, Config, Category = "Search", meta = (EditCondition = "bEnableHybridSearch", EditConditionHides, ClampMin = "1", ClampMax = "1000", ToolTip = "RRF constant (k). Higher values reduce the impact of rank differences."))`
- L153 _public member_ `int32 RRFOversample = 3;` — `UPROPERTY(EditAnywhere, Config, Category = "Search", meta = (EditCondition = "bEnableHybridSearch", EditConditionHides, ClampMin = "1", ClampMax = "10", ToolTip = "Oversample multiplier for RRF. Each source fetches K * this many candidates before fusion."))`
- L159 _public member_ `int32 BM25MinShouldMatchPercent = 75;` — `UPROPERTY(EditAnywhere, Config, Category = "Search", meta = (EditCondition = "bEnableHybridSearch", EditConditionHides, ClampMin = "0", ClampMax = "100", ToolTip = "Minimum percentage of unique query terms a document must match to be returned by BM25. 0 = any term (pure OR), 100 = all terms (strict AND). Default 75 prevents single-term matches like 'green' from polluting results for queries like 'green chair'. Computed via ceiling, e.g. 75% of 4 terms requires 3."))`
- L164 _public member_ `float VectorDistanceCutoff = 1.0f;` — `UPROPERTY(EditAnywhere, Config, Category = "Search", meta = (ClampMin = "0.1", ClampMax = "3.0", ToolTip = "Maximum L2 distance for a result to be considered a semantic match. Lower values are stricter. Results must pass this threshold OR have a BM25 keyword match to appear."))`
- L169 _public member_ `float SimilarityDistanceCutoff = 0.5f;` — `UPROPERTY(EditAnywhere, Config, Category = "Search", meta = (ClampMin = "0.1", ClampMax = "3.0", ToolTip = "Maximum L2 distance for 'Find Similar' results. Lower values are stricter."))`
