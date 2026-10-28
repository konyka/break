# Plugins / DirectLinkExtension

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension`
- headers: 9; symbols: 165
- symbol kinds: class=10, delegate=2, function=24, macro=1, member=38, namespace=19, prototype=67, struct=2, typedef=2
- PrivateDependencyModuleNames: Engine, InputCore, UdpMessaging, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DirectLink, ExternalSource

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Private/AutoReimportManager.h` (Private)


#### class `UE::DatasmithImporter::FAutoReimportManager`  
`class FAutoReimportManager : public FTickableGameObject, public TSharedFromThis<FAutoReimportManager>`  
_L20-69_
- inherits: `FTickableGameObject,TSharedFromThis<FAutoReimportManager>`
- L25 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Begin FTickableGameObject Interface
- L26 _public function_ `virtual bool IsTickable() const override`
- L27 _public prototype_ `virtual TStatId GetStatId() const override;`
- L28 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L29 _public function_ `virtual bool IsTickableInEditor() const override`
- L32 _public prototype_ `bool IsAssetAutoReimportEnabled(UObject* InAsset) const;`
- L34 _public prototype_ `bool SetAssetAutoReimport(UObject* InAsset, bool bEnabled);`
- L36 _public prototype_ `void OnExternalSourceInvalidated(const TSharedRef<FExternalSource>& ExternalSource);`
- L42 _public prototype_ `void UpdateModifiedRegisteredAsset(UObject* InAsset);` — Update the internal registration a given asset registered for auto-reimport. Modified assets may no longer have a DirectLink source and we must keep track of such changes.
- L46 _private prototype_ `bool CanTriggerReimport() const;`
- L48 _private prototype_ `bool EnableAssetAutoReimport(UObject* InAsset);`
- L50 _private prototype_ `bool DisableAssetAutoReimport(UObject* InAsset);`
- L52 _private prototype_ `void OnExternalSourceChanged(const TSharedRef<FExternalSource>& ExternalSource);`
- L54 _private prototype_ `void TriggerAutoReimportOnExternalSource(const TSharedRef<FExternalSource>& ExternalSource);`
- L56 _private prototype_ `void TriggerAutoReimportOnAsset(UObject* Asset);`
- L60 _private member_ `TSet<TSoftObjectPtr<UObject>> PendingAutoReimportObjects;`
- L62 _private member_ `TMap<UObject*, TSharedRef<FAutoReimportInfo>> AutoReimportObjectsMap;`
- L64 _private member_ `TMultiMap<TSharedRef<FExternalSource>, TSharedRef<FAutoReimportInfo>> AutoReimportExternalSourcesMap;`
- L66 _private member_ `TQueue<TSharedPtr<FExternalSource>> PendingReimportQueue;`
- L68 _private member_ `TQueue<TSharedPtr<FExternalSource>> PendingInvalidateQueue;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Private/DirectLinkAssetObserver.h` (Private)


#### class `UE::DatasmithImporter::FDirectLinkAssetObserver`  
`class FDirectLinkAssetObserver`  
_L17-33_
- L20 _public prototype_ `FDirectLinkAssetObserver(FDirectLinkManager& Manager);`
- L22 _public prototype_ `~FDirectLinkAssetObserver();`
- L25 _private prototype_ `void AssetRemovedEvent(const FAssetData& AssetData);`
- L27 _private prototype_ `void AssetUpdatedEvent(const FAssetData& AssetData);`
- L29 _private prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L32 _private member_ `FDirectLinkManager& Manager;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Private/DirectLinkManager.h` (Private)


#### class `UE::DatasmithImporter::FDirectLinkAutoReconnectManager`  
`class FDirectLinkAutoReconnectManager`  
_L29-54_
- L32 _public prototype_ `FDirectLinkAutoReconnectManager(FDirectLinkManager& InManager);`
- L34 _public prototype_ `~FDirectLinkAutoReconnectManager();`
- L36 _public prototype_ `bool Start();`
- L38 _public prototype_ `void Stop();`
- L41 _private prototype_ `void Run();`
- L43 _private member_ `FDirectLinkManager& Manager;`
- L45 _private member_ `TAtomic<bool> bShouldRun;`
- L47 _private member_ `TFuture<void> CompletedFuture;`
- L49 _private member_ `float LastTryTime = 0;`
- L51 _private member_ `bool bAutoReconnectEnabled = false;`
- L53 _private member_ `float ReconnectionDelayInSeconds = 1;`

#### class `UE::DatasmithImporter::FDirectLinkManager`  
`class FDirectLinkManager: public IDirectLinkManager, public DirectLink::IEndpointObserver`  
_L56-173_
- inherits: `IDirectLinkManager,DirectLink::IEndpointObserver`
- L60 _public prototype_ `virtual ~FDirectLinkManager();`
- L65 _public function_ `static FDirectLinkManager& GetInstance()` — Static instance that can be used internally to avoid relying on IDirectLinkExtensionModule to get the DirectLink manager.
- L75 _public function_ `static void ResetInstance()`
- L85 _public prototype_ `virtual void OnStateChanged(const DirectLink::FRawInfo& RawInfo) override;` — IEndpointObserver interface begin
- L89 _public prototype_ `virtual TSharedPtr<FDirectLinkExternalSource> GetOrCreateExternalSource(const DirectLink::FSourceHandle& SourceHandle) override;` — IDirectLinkManager interface begin
- L90 _public prototype_ `virtual TSharedPtr<FDirectLinkExternalSource> GetOrCreateExternalSource(const FSourceUri& Uri) override;`
- L91 _public prototype_ `virtual DirectLink::FEndpoint& GetEndpoint() override;`
- L92 _public prototype_ `virtual FSourceUri GetUriFromSourceHandle(const DirectLink::FSourceHandle& SourceHandle) override;`
- L94 _public function_ `virtual bool IsAssetAutoReimportEnabled(UObject* InAsset) const override`
- L95 _public function_ `virtual bool SetAssetAutoReimport(UObject* InAsset, bool bEnabled) override`
- L100 _public prototype_ `virtual TArray<TSharedRef<FDirectLinkExternalSource>> GetExternalSourceList() const override;`
- L101 _public prototype_ `virtual void UnregisterDirectLinkExternalSource(FName InName) override;`
- L103 _protected prototype_ `virtual void RegisterDirectLinkExternalSource(FDirectLinkExternalSourceRegisterInformation&& ExternalSourceClass) override;`
- L112 _public function_ `void UpdateModifiedRegisteredAsset(UObject* InAsset)` — Update the internal registration a given asset registered for auto-reimport. Modified assets may no longer have a DirectLink source and we must keep track of such changes.
- L116 _private prototype_ `FDirectLinkManager();`
- L121 _private prototype_ `void Clear();` — Should be called before destructing the FDirectLinkManager.
- L127 _private prototype_ `void InvalidateSource(const DirectLink::FSourceHandle& InvalidSourceHandle);` — Remove a DirectLink source from cache and invalidate its associated DirectLinkExternalSource object. @param InvalidSourceId	The SourceHandle of the invalid DirectLink source.
- L134 _private prototype_ `DirectLink::FSourceHandle ResolveSourceHandleFromDescription(const FDirectLinkSourceDescription& SourceDescription) const;` — Return the first SourceHandle matching the description of the source without. Does not use the source id in the description. @param SourceDescription	The Description of the DirectLink source. @return	The DirectLink SourceHandle corresponding to the description. If no match was found the FSourceHandle is invalid.
- L139 _private prototype_ `void UpdateSourceCache();` — Update internal cache. Create FDirectLinkExternalSource for new DirectLink source and remove expired ones.
- L141 _private prototype_ `void CancelEmptySourcesLoading() const;`
- L145 _private member_ `static TUniquePtr<FDirectLinkManager> Instance;`
- L150 _private member_ `DirectLink::FRawInfo RawInfoCache;` — Cached DirectLink state.
- L155 _private member_ `mutable FRWLock RawInfoLock;` — Lock used to guard RawInfoCache, as the cache is updated from an async thread.
- L157 _private member_ `TUniquePtr<DirectLink::FEndpoint> Endpoint;`
- L159 _private member_ `TUniquePtr<FDirectLinkAssetObserver> AssetObserver;`
- L161 _private member_ `TArray<FDirectLinkExternalSourceRegisterInformation> RegisteredExternalSourcesInfo;`
- L163 _private member_ `TMap<DirectLink::FSourceHandle, TSharedRef<FDirectLinkExternalSource>> DirectLinkSourceToExternalSourceMap;`
- L165 _private member_ `FRWLock ReconnectionListLock;`
- L166 _private member_ `TArray<TSharedRef<FDirectLinkExternalSource>> ExternalSourcesToReconnect;`
- L168 _private member_ `TUniquePtr<FDirectLinkAutoReconnectManager> ReconnectionManager;`
- L170 _private member_ `TSharedRef<FAutoReimportManager> AutoReimportManger;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDirectLinkManager, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDirectLinkManager, Log, All);`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/DirectLinkExtensionBlueprintLibrary.h` (Public)


#### class `UDirectLinkExtensionBlueprintLibrary`  
`class UDirectLinkExtensionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L12-22_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "DirectLinkExtensionLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L18 _public prototype_ `static TArray<FString> GetAvailableDirectLinkSourcesUri();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | DirectLink")`
- L21 _public prototype_ `static bool ParseDirectLinkSourceUri(const FString& SourceUriString, FString& OutComputerName, FString& OutEndpointName, FString& OutExecutableName, FString& OutSourceName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | DirectLink")`

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/DirectLinkExtensionModule.h` (Public)


#### class `IDirectLinkExtensionModule`  
`class IDirectLinkExtensionModule : public IModuleInterface`  
_L22-59_
- inherits: `IModuleInterface`
- L30 _public function_ `static inline IDirectLinkExtensionModule& Get()` — Singleton-like access to IDirectLinkEditorModule @return Returns IDirectLinkEditorModule singleton instance, loading the module on demand if needed
- L40 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. @return True if the module is loaded and ready to use
- L45 _public function_ `static DirectLink::FEndpoint& GetEndpoint()`
- L53 _public prototype_ `virtual void OverwriteUriResolver(const TSharedRef<UE::DatasmithImporter::IUriResolver>& UriResolver) = 0;` — Overwrite the UriResolver of the DirectLinkExtension module.
- L58 _public prototype_ `virtual UE::DatasmithImporter::IDirectLinkManager& GetManager() const = 0;` — Return the DirectLinkManager singleton.

#### Free symbols / members of external scopes

- L10 _macro_ `#define DIRECTLINKEXTENSION_MODULE_NAME TEXT("DirectLinkExtension")`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L17 _namespace_ `namespace DirectLink`

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/DirectLinkExtensionSettings.h` (Public)


#### class `UDirectLinkExtensionSettings`  
`class UDirectLinkExtensionSettings : public UObject`  
_L12-28_
- reflection: `UCLASS(config=Editor)`
- inherits: `UObject`
- L21 _public member_ `bool bAutoReconnect = true;` — `UPROPERTY(config)` — Whether or not to attempt reconnecting lost connection.
- L27 _public member_ `float ReconnectionDelayInSeconds = 5.f;` — `UPROPERTY(config, meta = (ClampMin="0.1"))` — Time in seconds to wait between reconnection attempts.

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/DirectLinkExternalSource.h` (Public)


#### class `UE::DatasmithImporter::FDirectLinkExternalSource`  
`class FDirectLinkExternalSource : public FExternalSource, public DirectLink::IConnectionRequestHandler`  
_L24-95_
- inherits: `FExternalSource,DirectLink::IConnectionRequestHandler`
- desc: DirectLinkExternalSouce used for referencing DirectLink source at import.
- L27 _public function_ `explicit FDirectLinkExternalSource(const FSourceUri& InSourceUri) : FExternalSource(InSourceUri)`
- L31 _public prototype_ `virtual ~FDirectLinkExternalSource();`
- L34 _public function_ `virtual FString GetSourceName() const override` — FExternalSource interface begin
- L35 _public function_ `virtual bool IsAvailable() const override`
- L36 _public function_ `virtual bool IsOutOfSync() const override`
- L37 _public function_ `virtual FMD5Hash GetSourceHash() const override`
- L38 _public prototype_ `virtual FExternalSourceCapabilities GetCapabilities() const override;`
- L40 _protected function_ `virtual TSharedPtr<IDatasmithScene> LoadImpl() override`
- L41 _protected prototype_ `virtual bool StartAsyncLoad() override;`
- L46 _public prototype_ `virtual bool CanOpenNewConnection(const DirectLink::IConnectionRequestHandler::FSourceInformation& Source) = 0;` — DirectLink::IConnectionRequestHandler interface begin.
- L47 _public prototype_ `virtual TSharedPtr<DirectLink::ISceneReceiver> GetSceneReceiver(const DirectLink::IConnectionRequestHandler::FSourceInformation& Source) override final;`
- L53 _public prototype_ `void Initialize(const FString& InSourceName, const FGuid& InSourceHandle, const FGuid& InDestinationHandle);` — Initialize the FDirectLinkExternalSource after its creation.
- L59 _public prototype_ `bool OpenStream();` — Try to open a DirectLink stream to the source. @return True if the operation was successful.
- L61 _public prototype_ `void CloseStream();`
- L63 _public function_ `bool IsStreamOpen() const`
- L68 _public prototype_ `void Invalidate();` — Clear all delegates and make this FDirectLinkExternalSource stale and unavailable.
- L70 _public function_ `const FGuid& GetSourceHandle() const`
- L72 _public function_ `const FGuid& GetDestinationHandle() const`
- L78 _protected prototype_ `virtual TSharedPtr<DirectLink::ISceneReceiver> GetSceneReceiverInternal(const DirectLink::IConnectionRequestHandler::FSourceInformation& Source) = 0;` — Used by GetSceneReceiver() to create a wrapper around the ISceneReceiver returned by this function.
- L82 _private member_ `FGuid SourceHandle;`
- L84 _private member_ `FGuid DestinationHandle;`
- L86 _private member_ `FString SourceName;`
- L88 _private member_ `bool bIsStreamOpen = false;`
- L90 _private member_ `TSharedPtr<class FInternalDirectLinkSceneReceiverWrapper> InternalSceneReceiver;`
- L92 _private member_ `FMD5Hash CachedHash;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnSnapshotUpdateDelegate, const TSharedRef<UE::DatasmithImporter::FDirectLinkExternalSource>&) namespace UE::DatasmithImporter { class FDirectLinkExternalSource : public FExternalSource, public DirectLink::IConnectionRequestHandler { public: explicit FDirectLinkExternalSource(const FSourceUri& InSourceUri) : FExternalSource(InSourceUri) {} virtual ~FDirectLinkExternalSource();`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/DirectLinkUriResolver.h` (Public)


#### struct `UE::DatasmithImporter::FDirectLinkSourceDescription`  
`struct FDirectLinkSourceDescription`  
_L18-25_
- L20 _public member_ `FString ComputerName;`
- L21 _public member_ `FString ExecutableName;`
- L22 _public member_ `FString EndpointName;`
- L23 _public member_ `FString SourceName;`
- L24 _public member_ `TOptional<FGuid> SourceId;`

#### class `UE::DatasmithImporter::FDirectLinkUriResolver`  
`class FDirectLinkUriResolver : public IUriResolver`  
_L27-57_
- inherits: `IUriResolver`
- L31 _public prototype_ `virtual TSharedPtr<FExternalSource> GetOrCreateExternalSource(const FSourceUri& Uri) const override;` — IUriResolver interface begin
- L32 _public prototype_ `virtual bool CanResolveUri(const FSourceUri& Uri) const override;`
- L33 _public function_ `virtual FName GetScheme() const override`
- L35 _public function_ `virtual TSharedPtr<FExternalSource> BrowseExternalSource(const FSourceUri& DefaultSourceUri) const override`
- L46 _public prototype_ `static TOptional<FDirectLinkSourceDescription> TryParseDirectLinkUri(const FSourceUri& Uri);` — Try to parse the DirectLink source description components from an URI. Return an unset TOptional if the parsing failed.
- L51 _public prototype_ `static const FString& GetDirectLinkScheme();` — Return the scheme used for DirectLink URIs : "directlink"
- L56 _public prototype_ `static const FString& GetSourceIdPropertyName();` — Return the string "SourceId" used in URI queries for specifying the handle of the directlink source.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace DirectLink`
- L11 _typedef_ `using FSourceHandle = FGuid;` (scope `DirectLink`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/IDirectLinkManager.h` (Public)


#### struct `UE::DatasmithImporter::FDirectLinkExternalSourceRegisterInformation`  
`struct FDirectLinkExternalSourceRegisterInformation`  
_L23-27_
- L25 _public member_ `FName Name;`
- L26 _public member_ `TFunction<TSharedRef<FDirectLinkExternalSource>(const FSourceUri&)> SpawnFunction;`

#### class `UE::DatasmithImporter::IDirectLinkManager`  
`class IDirectLinkManager : public FNoncopyable`  
_L32-114_
- inherits: `FNoncopyable`
- desc: Interface used to manage the creation and lifetime of FDirectLinkExternalSource objects.
- L35 _public prototype_ `virtual ~IDirectLinkManager() = default;`
- L44 _public prototype_ `virtual TSharedPtr<FDirectLinkExternalSource> GetOrCreateExternalSource(const DirectLink::FSourceHandle& SourceHandle) = 0;` — Get the FDirectLinkExternalSource associated to the given DirectLink::FSourceHandle, either by creating it or returning a cached value. The FDirectLinkExternalSource is in a disconnected state by default. Return nullptr if the FSourceHandle is not recognized. @param SourceHandle	The handle of the DirectLink source. @return	The FDirectLinkExternalSource associated to the DirectLink source.
- L53 _public prototype_ `virtual TSharedPtr<FDirectLinkExternalSource> GetOrCreateExternalSource(const FSourceUri& Uri) = 0;` — Get the FDirectLinkExternalSource associated to the given Uri, either by creating it or returning a cached value. The FDirectLinkExternalSource is in a disconnected state by default. Return nullptr if the Uri is not compatible. @param Uri	The Uri describing a DirectLink source. @return	The FDirectLinkExternalSource associated to the DirectLink source.
- L58 _public prototype_ `virtual DirectLink::FEndpoint& GetEndpoint() = 0;` — Return the DirectLink Endpoint managed by the DirectLinkManager.
- L66 _public prototype_ `virtual FSourceUri GetUriFromSourceHandle(const DirectLink::FSourceHandle& SourceHandle) = 0;` — Get the SourceUri referencing the DirectLink source associated to the passed SourceHandle. @param SourceHandle	The DirectLink source handle for which we want the Uri. @return	The SourceUri associated to the DirectLink source. If the SourceHandle didn't match a source, the returned FSourceUri is invalid.
- L71 _public prototype_ `virtual TArray<TSharedRef<FDirectLinkExternalSource>> GetExternalSourceList() const = 0;` — Get the list of all FDirectLinkExternalSource currently available.
- L78 _public function_ `template<typename ExternalSourceType> void RegisterDirectLinkExternalSource(FName InName)` — Template function used to register a derived type of FDirectLinkExternalSource. Registered types are used to establish DirectLink streams with compatible sources.
- L95 _public prototype_ `virtual void UnregisterDirectLinkExternalSource(FName InName) = 0;` — Used to unregister a type of FDirectLinkExternalSource.
- L104 _public prototype_ `virtual bool SetAssetAutoReimport(UObject* Asset, bool bEnableAutoReimport) = 0;` — Enable or disable auto-reimport on the given UObject asset. The asset must have a DirectLink source. This effectively trigger a reimport operation on the asset every time its associated ExternalSource receives an update. @param Asset					The asset we want to @param bEnableAutoReimport @return	True if the operation was successful.
- L106 _public prototype_ `virtual bool IsAssetAutoReimportEnabled(UObject* InAsset) const = 0;`
- L113 _protected prototype_ `virtual void RegisterDirectLinkExternalSource(FDirectLinkExternalSourceRegisterInformation&& ExternalSourceClass) = 0;` — Internal function used to register a derived type. Type checking is done by the RegisterDirectLinkExternalSource<T>() function

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace DirectLink`
- L15 _typedef_ `using FSourceHandle = FGuid;` (scope `DirectLink`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L85 _function_ `` (scope `UE::DatasmithImporter::IDirectLinkManager::RegisterDirectLinkExternalSource`)
