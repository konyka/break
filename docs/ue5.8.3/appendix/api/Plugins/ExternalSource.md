# Plugins / ExternalSource

- module root: `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource`
- headers: 6; symbols: 115
- symbol kinds: class=6, delegate=2, function=18, macro=1, member=14, namespace=14, prototype=57, struct=2, typedef=1
- PrivateDependencyModuleNames: DatasmithCore, Engine, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DatasmithTranslator

### `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource/Private/UriManager.h` (Private)


#### struct `UE::DatasmithImporter::FUriResolverRegisterInformation`  
`struct FUriResolverRegisterInformation`  
_L12-21_
- L14 _public function_ `FUriResolverRegisterInformation(FName InName, const TSharedRef<IUriResolver>& InUriResolver) : Name(InName) , UriResolver(InUriResolver)`
- L19 _public member_ `FName Name;`
- L20 _public member_ `TSharedRef<IUriResolver> UriResolver;`

#### class `UE::DatasmithImporter::FUriManager`  
`class FUriManager : public IUriManager`  
_L23-45_
- inherits: `IUriManager`
- L27 _public prototype_ `virtual TSharedPtr<FExternalSource> GetOrCreateExternalSource(const FSourceUri& URI) const override;` — IUriManager interface begin
- L28 _public prototype_ `virtual bool CanResolveUri(const FSourceUri& URI) const override;`
- L29 _public prototype_ `virtual void RegisterResolver(FName ResolverName, const TSharedRef<IUriResolver>& UriResolver) override;`
- L30 _public prototype_ `virtual bool UnregisterResolver(FName ResolverName) override;`
- L31 _public prototype_ `virtual const TArray<FName>& GetSupportedSchemes() const override;`
- L33 _public prototype_ `virtual TSharedPtr<FExternalSource> BrowseExternalSource(const FName& UriScheme, const FSourceUri& DefaultSourceUri) const override;`
- L38 _private prototype_ `TSharedPtr<IUriResolver> GetFirstCompatibleResolver(const FSourceUri& Uri) const;`
- L40 _private prototype_ `void InvalidateCache();`
- L42 _private member_ `TArray<FUriResolverRegisterInformation> RegisteredResolvers;`
- L44 _private member_ `mutable TArray<FName> CachedSchemes;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource/Public/ExternalSource.h` (Public)


#### struct `UE::DatasmithImporter::FExternalSourceCapabilities`  
`struct FExternalSourceCapabilities`  
_L37-47_
- L42 _public member_ `bool bSupportSynchronousLoading = false;` — FExternalSource::Load() should only be called when this capability is enabled.
- L46 _public member_ `bool bSupportAsynchronousLoading = false;` — FExternalSource::AsyncLoad() should only be called when this capability is enabled.

#### class `UE::DatasmithImporter::FExternalSource`  
`class FExternalSource : public TSharedFromThis<FExternalSource>`  
_L52-201_
- inherits: `TSharedFromThis<FExternalSource>`
- desc: Class allowing to load a IDatasmithScene from a source URI.
- L55 _public prototype_ `explicit FExternalSource(const FSourceUri& InSourceUri);`
- L57 _public prototype_ `virtual ~FExternalSource();`
- L59 _public prototype_ `virtual FString GetSourceName() const = 0;`
- L61 _public function_ `const FSourceUri& GetSourceUri() const`
- L66 _public prototype_ `virtual bool IsAvailable() const = 0;` — Return true if the resource pointed by this ExternalSource is available for being loaded.
- L71 _public prototype_ `virtual bool IsOutOfSync() const = 0;` — Return true if the loaded scene is out-of-sync and needs to be reloaded.
- L76 _public prototype_ `virtual FMD5Hash GetSourceHash() const = 0;` — Gives the hash of the source, only returns a valid hash after loading the scene.
- L78 _public prototype_ `virtual FExternalSourceCapabilities GetCapabilities() const = 0;`
- L83 _public prototype_ `virtual TSharedPtr<IDatasmithScene> GetDatasmithScene() const = 0;` — Return the DatasmithScene if it is loaded, return an invalid TSharedPtr otherwise.
- L88 _public prototype_ `virtual FString GetFallbackFilepath() const = 0;` — As long as UFactory does not offer a way to import FExternalSource directly, we must rely on using filepaths, even for source that are not on the file system.
- L95 _public prototype_ `const TSharedPtr<IDatasmithTranslator>& GetAssetTranslator();` — DISCLAIMER: The translator is exposed here as a temporary workaround in order to set the import option before the load and load assets with bulk data (StaticMeshes/LoadLevelSequence/etc.). We should not rely on this for anything else as this will be removed once Import options can be set directly on FExternalSource.
- L101 _public prototype_ `FString GetSceneName() const;` — Return the name of the scene that will be loaded. #ueent_todo This is only required because of the way the Datasmith reimport works. Consider removing it when we adapt the ExternalSource to interchange.
- L107 _public prototype_ `void SetSceneName(const TCHAR* SceneName);` — Override the name of the scene that will be loaded. If the pointer is nullptr, the override will be reset. #ueent_todo This is only required because of the way the Datasmith reimport works. Consider removing it when we adapt the ExternalSource to interchange.
- L112 _public prototype_ `TSharedPtr<IDatasmithScene> TryLoad();` — Attempt to load the FExternalSource according to its supported capabilities.
- L118 _public prototype_ `TSharedPtr<IDatasmithScene> Load();` — Load the external source and return a valid IDatasmithScene TSharedPtr if successful. The FExternalSource must have the FExternalSourceCapabilities::bSupportSynchronousLoading enabled to call this.
- L124 _public prototype_ `TFuture<TSharedPtr<IDatasmithScene>> AsyncLoad();` — Load the external source asynchronously, the returned TFuture gives a valid IDatasmithScene TSharedPtr if successful. The FExternalSource must have the FExternalSourceCapabilities::bSupportAsynchronousLoading enabled to call this.
- L129 _public function_ `bool IsAsyncLoading() const` — True when the ExternalSource is currently loading the source asynchronously.
- L134 _public prototype_ `void CancelAsyncLoad();` — Cancel any pending AsyncLoad() operation, pending TFuture will return invalid TSharedPtr.
- L140 _public member_ `OnExternalSourceChangedDelegate OnExternalSourceChanged;` — Delegate called on main thread every time the loaded data is updated. Used for registering auto-reimport on assets.
- L148 _protected prototype_ `virtual TSharedPtr<IDatasmithScene> LoadImpl() = 0;` — Synchronously load the DatasmithScene. Upon success, GetDatasmithScene() should return a valid scene. @return a valid SharedPtr if the operation was successful.
- L155 _protected prototype_ `virtual bool StartAsyncLoad() = 0;` — Starts an async task for loading the DatasmithScene. When the task is completed, TriggerOnExternalSourceLoaded() should be called to notify that the Scene is now available. @return true if the async loading task is running.
- L161 _protected prototype_ `void ClearOnExternalSourceLoadedDelegates();` — Interrupt async task notification and clear all registered delegates. Used for when a source becomes unavailable.
- L166 _protected prototype_ `void TriggerOnExternalSourceChanged();` — Broadcast OnExternalSourceChanged delegates and set pending TPromises.
- L171 _protected prototype_ `bool TranslatorLoadScene(const TSharedRef<IDatasmithScene>& Scene);` — Loads a scene from the translator and starts a new translator load lifecycle.
- L175 _private typedef_ `typedef TOptional<TPromise<TSharedPtr<IDatasmithScene>>> FOptionalScenePromise;`
- L177 _private prototype_ `void ValidateDatasmithVersion() const;`
- L184 _private member_ `TQueue<FOptionalScenePromise, EQueueMode::Mpsc> PendingPromiseQueue;` — Queue containing the unfulfilled promises added by AsyncLoad() We can't directly make a TQueue of TPromise, as the queue internally creates nodes for tracking the head/tail, those nodes would then hold default-constructed TPromises and would assert on deletion, since deleting an unset promise is a programming error.
- L189 _private member_ `TSharedPtr<FAsyncTaskNotification> AsyncTaskNotification;` — Async task notification, for when we are loading the Datasmith scene asynchronously.
- L194 _private member_ `FSourceUri SourceUri;` — The URI of the source this ExternalSource is accessing.
- L196 _private member_ `FString SceneName;`
- L198 _private member_ `TSharedPtr<IDatasmithTranslator> AssetTranslator;`
- L200 _private member_ `TUniquePtr<FDatasmithSceneGuard> SceneGuard;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L31 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogExternalSource, Log, All);`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogExternalSource, Log, All);`
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnExternalSourceChangedDelegate, const TSharedRef<UE::DatasmithImporter::FExternalSource>&);`
- L33 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnExternalSourceChangedDelegate, const TSharedRef<UE::DatasmithImporter::FExternalSource>&);`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource/Public/ExternalSourceModule.h` (Public)


#### class `IExternalSourceModule`  
`class IExternalSourceModule : public IModuleInterface`  
_L18-37_
- inherits: `IModuleInterface`
- L21 _public function_ `static inline IExternalSourceModule& Get()`
- L26 _public function_ `static inline bool IsAvailable()`
- L31 _public prototype_ `virtual UE::DatasmithImporter::IUriManager& GetManager() const = 0;`
- L33 _public function_ `static TSharedPtr<UE::DatasmithImporter::FExternalSource> GetOrCreateExternalSource(const UE::DatasmithImporter::FSourceUri& Uri)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define EXTERNALSOURCE_MODULE_NAME TEXT("ExternalSource")`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource/Public/IUriManager.h` (Public)


#### class `UE::DatasmithImporter::IUriManager`  
`class IUriManager`  
_L21-79_
- L24 _public prototype_ `virtual ~IUriManager() = default;`
- L30 _public prototype_ `virtual TSharedPtr<FExternalSource> GetOrCreateExternalSource(const FSourceUri& Uri) const = 0;` — Using the registered UriManagers, return the FExternalSource associated to the given Uri, either by creating it or returning a cached value. Returns nullptr if the Uri is not compatible.
- L35 _public prototype_ `virtual bool CanResolveUri(const FSourceUri& Uri) const = 0;` — Return true if there is a registered UriResolver that can generate a FExternalSource from the given Uri.
- L40 _public prototype_ `virtual void RegisterResolver(FName ResolverName, const TSharedRef<IUriResolver>& UriResolver) = 0;` — Register the provided UriResolver in the manager.
- L45 _public prototype_ `virtual bool UnregisterResolver(FName ResolverName) = 0;` — Unregister the UriResolver associated to the provided name.
- L50 _public prototype_ `virtual const TArray<FName>& GetSupportedSchemes() const = 0;` — Return an array containing all the scheme supported by the registered URiResolvers.
- L56 _public prototype_ `virtual TSharedPtr<FExternalSource> BrowseExternalSource(const FName& UriScheme, const FSourceUri& DefaultSourceUri = FSourceUri()) const = 0;` — Open a dialog window for browsing ExternalSource based on the passed URI Scheme
- L59 _public function_ `template<typename ImportDataType> TSharedPtr<FExternalSource> TryGetExternalSourceFromImportData(const ImportDataType& ImportSourceData) const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource/Public/IUriResolver.h` (Public)


#### class `UE::DatasmithImporter::IUriResolver`  
`class IUriResolver`  
_L14-41_
- L17 _public prototype_ `virtual ~IUriResolver() = default;`
- L23 _public prototype_ `virtual TSharedPtr<FExternalSource> GetOrCreateExternalSource(const FSourceUri& Uri) const = 0;` — Return the FExternalSource associated to the given Uri, either by creating it or returning a cached value. Returns nullptr if the Uri is not compatible.
- L28 _public prototype_ `virtual bool CanResolveUri(const FSourceUri& Uri) const = 0;` — Return true if the UriResolver can generate a FExternalSource from the given Uri.
- L33 _public prototype_ `virtual FName GetScheme() const = 0;` — Return the URI scheme handled by the UriResolver.
- L39 _public prototype_ `virtual TSharedPtr<FExternalSource> BrowseExternalSource(const FSourceUri& DefaultUri) const = 0;` — Open a dialog window for browsing ExternalSources associated to this UriResolver

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/ExternalSource/Public/SourceUri.h` (Public)


#### class `UE::DatasmithImporter::FSourceUri`  
`class FSourceUri`  
_L19-138_
- desc: URI container class used for referencing external sources. TODO - A proper standardized version should be implemented in a Runtime/Core module to unify all URI implementations across the engine. For example, a URI implementation is provided in Plugins\Media\ElectraPlayer\Source\ElectraPlayerRuntime\Private\Runtime\Utilities\URI.h
- L22 _public prototype_ `FSourceUri() = default;`
- L24 _public function_ `explicit FSourceUri(const FString& InUri) : Uri(InUri)`
- L28 _public function_ `FSourceUri(const FString& InScheme, const FString& InPath) : Uri(InScheme + GetSchemeDelimiter() + InPath)`
- L33 _public function_ `template<typename TContainer> FSourceUri(const FString& InScheme, const FString& InPath, const TContainer& QueryContainer) : Uri(InScheme + GetSchemeDelimiter() + InPath + BuildQueryString(QueryContainer))`
- L40 _public prototype_ `static FSourceUri FromFilePath(const FString& FilePath);` — Generate a FSourceUri from the given filepath.
- L45 _public prototype_ `static const FString& GetFileScheme();` — Return the scheme used for file URIs : "file"
- L50 _public prototype_ `static FSourceUri FromAssetData(const FAssetData& AssetData);` — Try to get the FSourceUri registered in the AssetData. If no SourceUri is registered, an invalid FSourceUri is returned.
- L55 _public prototype_ `static FName GetAssetDataTag();` — Returns the Tag that should be used for registering the SourceUri of an asset in its corresponding FAssetData.
- L60 _public prototype_ `bool IsValid() const;` — Return if the FSourceUri is a properly structure valid uri.
- L62 _public prototype_ `FStringView GetScheme() const;`
- L69 _public prototype_ `bool HasScheme(const FString& InScheme) const;` — Check if the FSourceUri has the provided scheme. @param InScheme	The scheme to look for. @return	True if the Uri has the provided scheme.
- L75 _public prototype_ `FStringView GetPath() const;` — Return the path of the FSourceUri @return	The path, for now no distinction is made between the authority and the path.
- L77 _public prototype_ `FStringView GetQuery() const;`
- L79 _public prototype_ `TMap<FString, FString> GetQueryMap() const;`
- L84 _public function_ `const FString& ToString() const` — Return the FSourceUri as a string.
- L86 _public function_ `bool operator==(const FSourceUri& Other) const`
- L91 _public function_ `bool operator!=(const FSourceUri& Other) const`
- L99 _private function_ `template<typename TContainer> static FString BuildQueryString(const TContainer& QueryContainer)`
- L128 _private prototype_ `static const FString& GetSchemeDelimiter();`
- L133 _private function_ `static TCHAR GetQueryStartCharacter()` — URI Queries are structured like so <RestOfURI>?<KeyA><ValueA>&<KeyB>=<ValueB>
- L134 _private function_ `static TCHAR GetQueryPairCharacter()`
- L135 _private function_ `static TCHAR GetQueryAppendPairCharacter()`
- L137 _private member_ `FString Uri;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L140 _function_ `inline uint32 GetTypeHash(const FSourceUri& SourceUri)` (scope `UE::DatasmithImporter`)
