# Plugins / USDPregenWrapper

- module root: `Plugins/Experimental/USDPregen/Source/USDPregenWrapper`
- headers: 14; symbols: 490
- symbol kinds: class=17, enum=5, enumerator=13, function=4, macro=12, member=49, namespace=49, prototype=300, struct=11, typedef=30
- PublicDependencyModuleNames: Core, CoreUObject, USDPregenCore, UnrealUSDWrapper

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/USDPregenWrapper.h` (Public)


#### struct `UE::UsdPregen::Internal::HasLock`  
`template<typename T, typename = void> struct HasLock : std::false_type`  
_L55-55_
- inherits: `std::false_type`

#### struct `UE::UsdPregen::Internal::HasLock`  
`template<typename T> struct HasLock<T, std::void_t<decltype(std::declval<T>().lock())>> : std::true_type`  
_L58-58_
- inherits: `std::true_type`

#### enum `EPregenDiscoveryMode`  
`enum class EPregenDiscoveryMode : uint8`  
_L89-93_
- reflection: `UENUM(BlueprintType)`
- L91 _public enumerator_ `AllPermutations`
- L92 _public enumerator_ `ComposedPermutationOnly`

#### enum `EPregenVersionFallbackMode`  
`enum class EPregenVersionFallbackMode : uint8`  
_L96-101_
- reflection: `UENUM(BlueprintType)`
- L98 _public enumerator_ `None`
- L99 _public enumerator_ `LayerStackFilesAndTimestamps`
- L100 _public enumerator_ `ResolvedLayerStackFilesAndTimestamps`

#### enum `EPregenIdentifierFallbackMode`  
`enum class EPregenIdentifierFallbackMode : uint8`  
_L104-108_
- reflection: `UENUM(BlueprintType)`
- L106 _public enumerator_ `None`
- L107 _public enumerator_ `FirstDirectReferenceOrPayload`

#### struct `FPregenDiscoveryOptions`  
`struct FPregenDiscoveryOptions`  
_L111-156_
- reflection: `USTRUCT(BlueprintType)`
- L117 _public member_ `EPregenDiscoveryMode DiscoveryMode = EPregenDiscoveryMode::AllPermutations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Permutation discovery mode (all variants vs. composed-only).
- L122 _public member_ `FString DiscoveryPluginName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Name of the discovery plugin to use. Empty resolves to the built-in default discovery plugin.
- L126 _public member_ `FString DefinitionPrefix;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Prefix prepended to every discovered asset definition's name.
- L135 _public member_ `FString InitialPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Stored as FString for USTRUCT/UPROPERTY compatibility; converted to pxr::SdfPath at the wrapper -> native boundary.
- L140 _public member_ `TArray<FString> Purposes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — UsdGeomImageable purposes to include during discovery. Empty means "include all purposes".
- L145 _public member_ `TArray<FString> ExcludeVariantSets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Variant set names to exclude from permutation enumeration. Use "*" to exclude all variant sets.
- L149 _public member_ `EPregenIdentifierFallbackMode AssetIdentifierFallback = EPregenIdentifierFallbackMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Strategy used when an asset has no authored identifier.
- L153 _public member_ `EPregenVersionFallbackMode AssetVersionFallback = EPregenVersionFallbackMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Strategy used when an asset has no authored version.
- L155 _public prototype_ `bool operator==(const FPregenDiscoveryOptions& Other) const = default;`

#### struct `FPregenStorageOptions`  
`struct FPregenStorageOptions`  
_L159-193_
- reflection: `USTRUCT(BlueprintType)`
- L166 _public member_ `FString StoragePluginName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Name of the storage plugin to use. An empty string will use the built-in JSON plugin ("json_storage").
- L178 _public member_ `FString ManifestDir;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Empty => plugin default (JsonStoragePlugin falls back to the USDPREGEN_DEFAULT_STORAGE_DIR environment variable, then to "<HOME>/UE_UsdPregen_Manifests").
- L190 _public member_ `FString PackageSubPathTemplate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD Pregen")` — Empty => plugin default (IStoragePlugin::DefaultPackageSubPathTemplate).
- L192 _public prototype_ `bool operator==(const FPregenStorageOptions& Other) const = default;`

#### class `USDPregenWrapper`  
`class USDPregenWrapper`  
_L195-204_
- L198 _public prototype_ `static UE::UsdPregen::FSceneTracker CreateSceneTracker( const UE::FUsdStage& Stage);`
- L201 _public prototype_ `static UE::UsdPregen::FSceneTracker CreateSceneTracker( const UE::FUsdStage& Stage, const FPregenDiscoveryOptions& Options);`

#### Free symbols / members of external scopes

- L21 _typedef_ `using StoragePluginRefPtr = std::shared_ptr<StoragePlugin>;`
- L22 _typedef_ `using StoragePluginWeakPtr = std::weak_ptr<StoragePlugin>;`
- L25 _typedef_ `using SceneTrackerRefPtr = std::shared_ptr<SceneTracker>;`
- L26 _typedef_ `using SceneTrackerWeakPtr = std::weak_ptr<SceneTracker>;`
- L29 _typedef_ `using TargetDataRefPtr = std::shared_ptr<TargetData>;`
- L30 _typedef_ `using TargetDataWeakPtr = std::weak_ptr<TargetData>;`
- L36 _namespace_ `namespace UE`
- L38 _namespace_ `namespace UsdPregen` (scope `UE`)
- L44 _typedef_ `using FSceneTracker = FSceneTrackerBase<PREGEN_NS::SceneTrackerRefPtr>;` (scope `UE::UsdPregen`)
- L45 _typedef_ `using FSceneTrackerWeak = FSceneTrackerBase<PREGEN_NS::SceneTrackerWeakPtr>;` (scope `UE::UsdPregen`)
- L47 _typedef_ `using FSceneTracker = FSceneTrackerBase<FDummyRefPtrType>;` (scope `UE::UsdPregen`)
- L48 _typedef_ `using FSceneTrackerWeak = FSceneTrackerBase<FDummyWeakPtrType>;` (scope `UE::UsdPregen`)
- L50 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)
- L61 _function_ `template<typename T> auto ToStrongPtr(const T& Ptr) -> std::enable_if_t<!HasLock<T>::value, T>` (scope `UE::UsdPregen::Internal`)
- L67 _function_ `template<typename T> auto ToStrongPtr(const T& Ptr) -> decltype(Ptr.lock())` (scope `UE::UsdPregen::Internal`)
- L73 _function_ `template<typename To, typename From> To ConvertPtr(From&& Ptr)` (scope `UE::UsdPregen::Internal`)
- L79 _function_ `template<typename T> std::shared_ptr<T> ConvertPtr(const std::weak_ptr<T>& Ptr)` (scope `UE::UsdPregen::Internal`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/USDPregenWrapperModule.h` (Public)


#### class `FUSDPregenWrapperModule`  
`class FUSDPregenWrapperModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/AssetDefinitionRegistry.h` (Public)


#### class `UE::UsdPregen::FAssetDefinitionRegistry`  
`class FAssetDefinitionRegistry`  
_L20-40_
- L25 _public prototype_ `explicit FAssetDefinitionRegistry(PREGEN_NS::AssetDefinitionRegistry* InRegistry);`
- L27 _public prototype_ `operator PREGEN_NS::AssetDefinitionRegistry* ();`
- L28 _public prototype_ `operator const PREGEN_NS::AssetDefinitionRegistry* () const;`
- L32 _public prototype_ `static FAssetDefinitionRegistry GetInstance();`
- L34 _public prototype_ `FExtAssetDefinition GetDefinition(const FString& UniqueId) const;`
- L38 _private member_ `const PREGEN_NS::AssetDefinitionRegistry* PregenRegistry = nullptr;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L10 _namespace_ `namespace PREGEN_NS`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UsdPregen` (scope `UE`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/ExtAssetDefinition.h` (Public)


#### class `UE::UsdPregen::FExtAssetDefinition`  
`class FExtAssetDefinition`  
_L31-65_
- desc: Minimal PREGEN_NS::ExtAssetDefinition wrapper for Unreal that can be used from no-rtti modules. This is a lightweight non-owning wrapper around an immutable ExtAssetDefinition instance that is owned elsewhere (typically by AssetDefinitionRegistry).
- L34 _public prototype_ `FExtAssetDefinition() = default;`
- L37 _public prototype_ `explicit FExtAssetDefinition(const PREGEN_NS::ExtAssetDefinition* InDefinition);`
- L39 _public prototype_ `operator const PREGEN_NS::ExtAssetDefinition* () const;`
- L42 _public prototype_ `bool operator==(const FExtAssetDefinition& Other) const;`
- L43 _public prototype_ `bool operator!=(const FExtAssetDefinition& Other) const;`
- L44 _public prototype_ `bool operator<(const FExtAssetDefinition& Other) const;`
- L46 _public prototype_ `explicit operator bool() const;`
- L48 _public prototype_ `FString GetName() const;`
- L49 _public prototype_ `FString GetVersion() const;`
- L50 _public prototype_ `FSdfAssetPath GetIdentifier() const;`
- L52 _public prototype_ `FString GetUniqueId() const;`
- L54 _public prototype_ `bool GetMetadata(UE::FVtValue& OutMetadata) const;`
- L56 _public prototype_ `bool HasMetadata() const;`
- L57 _public prototype_ `bool HasCustomUniqueId() const;`
- L59 _public prototype_ `bool IsValid(FString* OutReason = nullptr) const;`
- L63 _private member_ `const PREGEN_NS::ExtAssetDefinition* PregenDefinition = nullptr;`

#### struct `UE::UsdPregen::FExtAssetDefinitionSnapshot`  
`struct FExtAssetDefinitionSnapshot`  
_L72-105_
- desc: Captures the authoritative fields so that downstream backends can persist a definition and re-register it later without depending on USD headers or RTTI. Round-trip is via the USDA-blob metadata field.
- L74 _public member_ `FString UniqueId;`
- L75 _public member_ `FString Name;`
- L76 _public member_ `FString Version;`
- L77 _public member_ `FString IdentifierAuthored;`
- L78 _public member_ `FString IdentifierResolved;`
- L79 _public member_ `bool bHasCustomUniqueId = false;`
- L84 _public member_ `FString Metadata;` — Round-tripped metadata VtDictionary, encoded as a USDA-format blob. Empty when the source definition had no metadata. The encoding format is an implementation detail and may evolve.
- L91 _public prototype_ `From(const FExtAssetDefinition& Defn);`
- L104 _public prototype_ `bool RegisterIntoRegistry() const;` — On reconstruction, the stored UniqueId is always passed through the customUniqueId form so it round-trips exactly. As a result HasCustomUniqueId() will always report true post-load even when the source had a default-derived UID; the bHasCustomUniqueId field is informational only.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L10 _namespace_ `namespace PREGEN_NS`
- L18 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UsdPregen` (scope `UE`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/IStoragePlugin.h` (Public)


#### class `UE::UsdPregen::IStoragePlugin`  
`class IStoragePlugin`  
_L19-101_
- L22 _public prototype_ `virtual ~IStoragePlugin();`
- L24 _public prototype_ `virtual FManifestLoadResult LoadManifestPayload(const FTargetUid& TargetUid) = 0;`
- L26 _public prototype_ `virtual FManifestSaveResult StoreManifestPayload( const FTargetUid& TargetUid, const FManifestPayload& Payload ) = 0;`
- L31 _public prototype_ `virtual FManifestSaveResult PersistManifestPayload(const FTargetUid& TargetUid);`
- L33 _public prototype_ `virtual FManifestPayload SerializeManifest(const FManifest& Manifest) = 0;`
- L35 _public prototype_ `virtual FManifest DeserializeManifestPayload(const FManifestPayload& Payload) = 0;`
- L37 _public prototype_ `virtual FString GetNameForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) = 0;`
- L43 _public prototype_ `virtual FString GetPackageSubPathForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) = 0;`
- L49 _public prototype_ `virtual FString GetPathForManifest(const FTargetUid& TargetUid) = 0;`
- L54 _public prototype_ `static const FString& DefaultPackageSubPathTemplate();` — Default template used by ResolvePackageSubPathTemplate when no explicit template is provided. Matches the layout the built-in plugins used before the template became configurable.
- L60 _public prototype_ `static const FString& EmptyValueSentinel();` — Sentinel substituted for placeholder values that resolve to empty (or to an entirely non-alphanumeric string). E.g. "versions/${DEFINITION_VERSION}/" with no version becomes "versions/_/" rather than orphan "versions/".
- L94 _public prototype_ `static FString ResolvePackageSubPathTemplate( const FString& Template, const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType, const TMap<FString, FString>& ExtraSubstitutions = {} );` — Example: Template "assets/${DEFINITION_NAME}/${PERMUTATION_ID}" with name "chemistry_bottle02" and permutation "2559017893" resolves to "assets/chemistry_bottle02/2559017893".

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UsdPregen` (scope `UE`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/JsonStoragePlugin.h` (Public)


#### class `UE::UsdPregen::FJsonStoragePluginBase`  
`template<typename PtrType> class FJsonStoragePluginBase`  
_L46-101_
- L49 _public prototype_ `FJsonStoragePluginBase();`
- L51 _public prototype_ `explicit FJsonStoragePluginBase(const FPregenStorageOptions& Options);`
- L53 _public prototype_ `FJsonStoragePluginBase(const FJsonStoragePlugin& Other);`
- L54 _public prototype_ `FJsonStoragePluginBase(FJsonStoragePlugin&& Other);`
- L56 _public prototype_ `FJsonStoragePluginBase& operator=(const FJsonStoragePlugin& Other);`
- L57 _public prototype_ `FJsonStoragePluginBase& operator=(FJsonStoragePlugin&& Other);`
- L59 _public prototype_ `~FJsonStoragePluginBase();`
- L61 _public prototype_ `explicit operator bool() const;`
- L64 _public prototype_ `explicit FJsonStoragePluginBase(const PREGEN_NS::JsonStoragePluginRefPtr& InPtr);`
- L65 _public prototype_ `explicit FJsonStoragePluginBase(PREGEN_NS::JsonStoragePluginRefPtr&& InPtr);`
- L67 _public prototype_ `operator PtrType& ();`
- L68 _public prototype_ `operator const PtrType& () const;`
- L70 _public prototype_ `operator PREGEN_NS::JsonStoragePluginRefPtr() const;`
- L74 _public prototype_ `FManifestLoadResult LoadManifestPayload(const FTargetUid& TargetUid) const;`
- L76 _public prototype_ `FManifestSaveResult StoreManifestPayload( const FTargetUid& TargetUid, const FManifestPayload& Payload ) const;`
- L81 _public prototype_ `FManifestSaveResult PersistManifestPayload(const FTargetUid& TargetUid) const;`
- L83 _public prototype_ `FManifestPayload SerializeManifest(const FManifest& Manifest) const;`
- L85 _public prototype_ `FManifest DeserializeManifestPayload(const FManifestPayload& Payload) const;`
- L87 _public prototype_ `FString GetNameForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) const;`
- L93 _public prototype_ `FString GetPackageSubPathForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) const;`
- L100 _private member_ `TUniquePtr<Internal::FJsonStoragePluginImpl<PtrType>> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L12 _namespace_ `namespace PREGEN_NS`
- L16 _typedef_ `using JsonStoragePluginRefPtr = std::shared_ptr<JsonStoragePlugin>;` (scope `PREGEN_NS`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UsdPregen` (scope `UE`)
- L22 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)
- L40 _typedef_ `using FJsonStoragePlugin = FJsonStoragePluginBase<PREGEN_NS::JsonStoragePluginRefPtr>;` (scope `UE::UsdPregen`)
- L42 _typedef_ `using FJsonStoragePlugin = FJsonStoragePluginBase<FDummyRefPtrType>;` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/Manifest.h` (Public)


#### struct `UE::UsdPregen::FProduct`  
`struct FProduct`  
_L27-54_
- L30 _public member_ `FString UPackagePath;`
- L31 _public member_ `FString UClass;`
- L32 _public member_ `FString UNodeId;`
- L33 _public member_ `FString UsdPrimType;`
- L34 _public member_ `FString UsdPrimPath;`
- L37 _public prototype_ `FProduct();`
- L39 _public prototype_ `FProduct(const FProduct& Other);`
- L40 _public prototype_ `FProduct(FProduct&& Other);`
- L42 _public prototype_ `FProduct& operator=(const FProduct& Other);`
- L43 _public prototype_ `FProduct& operator=(FProduct&& Other);`
- L46 _public prototype_ `explicit FProduct(const PREGEN_NS::Product& InProduct);`
- L47 _public prototype_ `explicit FProduct(PREGEN_NS::Product&& InProduct);`
- L49 _public prototype_ `FProduct& operator=(const PREGEN_NS::Product& InProduct);`
- L50 _public prototype_ `FProduct& operator=(PREGEN_NS::Product&& InProduct);`
- L52 _public prototype_ `operator PREGEN_NS::Product() const;`

#### class `UE::UsdPregen::FManifest`  
`class FManifest`  
_L56-101_
- L59 _public prototype_ `FManifest();`
- L61 _public prototype_ `FManifest(const FManifest& Other);`
- L62 _public prototype_ `FManifest(FManifest&& Other);`
- L63 _public prototype_ `~FManifest();`
- L65 _public prototype_ `FManifest& operator=(const FManifest& Other);`
- L66 _public prototype_ `FManifest& operator=(FManifest&& Other);`
- L68 _public prototype_ `explicit operator bool() const;`
- L71 _public prototype_ `explicit FManifest(const PREGEN_NS::Manifest& InManifest);`
- L72 _public prototype_ `explicit FManifest(PREGEN_NS::Manifest&& InManifest);`
- L74 _public prototype_ `FManifest& operator=(const PREGEN_NS::Manifest& InManifest);`
- L75 _public prototype_ `FManifest& operator=(PREGEN_NS::Manifest&& InManifest);`
- L77 _public prototype_ `operator PREGEN_NS::Manifest& ();`
- L78 _public prototype_ `operator const PREGEN_NS::Manifest& () const;`
- L82 _public prototype_ `FTargetUid GetTargetUid() const;`
- L83 _public prototype_ `void AddProduct(const FProduct& Product);`
- L84 _public prototype_ `TArray<FProduct> GetProducts() const;`
- L90 _public prototype_ `void SetTargetData(const FTargetData& TargetData);` — Storage backends serialize the attached target data alongside the products. Pass an empty / invalid FTargetData to clear.
- L95 _public prototype_ `FTargetData GetTargetData() const;` — The returned wrapper evaluates to false when no data is attached.
- L97 _public prototype_ `bool IsValid() const;`
- L100 _private member_ `TUniquePtr<Internal::FManifestImpl> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L13 _namespace_ `namespace PREGEN_NS`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UsdPregen` (scope `UE`)
- L22 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/ManifestTypes.h` (Public)


#### enum `UE::UsdPregen::EManifestLoadStatus`  
`enum class EManifestLoadStatus`  
_L24-29_
- L26 _public enumerator_ `Loaded`
- L27 _public enumerator_ `DoesNotExist`
- L28 _public enumerator_ `Error`

#### enum `UE::UsdPregen::EManifestSaveStatus`  
`enum class EManifestSaveStatus`  
_L31-36_
- L33 _public enumerator_ `Saved`
- L34 _public enumerator_ `NotSaved`
- L35 _public enumerator_ `Error`

#### struct `UE::UsdPregen::FManifestPayload`  
`struct FManifestPayload`  
_L38-62_
- L41 _public member_ `FString Encoding;`
- L42 _public member_ `TArray<uint8> Data;`
- L45 _public prototype_ `FManifestPayload();`
- L47 _public prototype_ `FManifestPayload(const FManifestPayload& Other);`
- L48 _public prototype_ `FManifestPayload(FManifestPayload&& Other);`
- L50 _public prototype_ `FManifestPayload& operator=(const FManifestPayload& Other);`
- L51 _public prototype_ `FManifestPayload& operator=(FManifestPayload&& Other);`
- L54 _public prototype_ `explicit FManifestPayload(const PREGEN_NS::ManifestPayload& InManifestPayload);`
- L55 _public prototype_ `explicit FManifestPayload(PREGEN_NS::ManifestPayload&& InManifestPayload);`
- L57 _public prototype_ `FManifestPayload& operator=(const PREGEN_NS::ManifestPayload& InManifestPayload);`
- L58 _public prototype_ `FManifestPayload& operator=(PREGEN_NS::ManifestPayload&& InManifestPayload);`
- L60 _public prototype_ `operator PREGEN_NS::ManifestPayload() const;`

#### struct `UE::UsdPregen::FManifestLoadResult`  
`struct FManifestLoadResult`  
_L64-89_
- L67 _public member_ `EManifestLoadStatus Status = EManifestLoadStatus::Error;`
- L68 _public member_ `FManifestPayload Payload;`
- L69 _public member_ `FString Message;`
- L72 _public prototype_ `FManifestLoadResult();`
- L74 _public prototype_ `FManifestLoadResult(const FManifestLoadResult& Other);`
- L75 _public prototype_ `FManifestLoadResult(FManifestLoadResult&& Other);`
- L77 _public prototype_ `FManifestLoadResult& operator=(const FManifestLoadResult& Other);`
- L78 _public prototype_ `FManifestLoadResult& operator=(FManifestLoadResult&& Other);`
- L81 _public prototype_ `explicit FManifestLoadResult(const PREGEN_NS::ManifestLoadResult& InManifestLoadResult);`
- L82 _public prototype_ `explicit FManifestLoadResult(PREGEN_NS::ManifestLoadResult&& InManifestLoadResult);`
- L84 _public prototype_ `FManifestLoadResult& operator=(const PREGEN_NS::ManifestLoadResult& InManifestLoadResult);`
- L85 _public prototype_ `FManifestLoadResult& operator=(PREGEN_NS::ManifestLoadResult&& InManifestLoadResult);`
- L87 _public prototype_ `operator PREGEN_NS::ManifestLoadResult() const;`

#### struct `UE::UsdPregen::FManifestSaveResult`  
`struct FManifestSaveResult`  
_L91-115_
- L94 _public member_ `EManifestSaveStatus Status = EManifestSaveStatus::Error;`
- L95 _public member_ `FString Message;`
- L98 _public prototype_ `FManifestSaveResult();`
- L100 _public prototype_ `FManifestSaveResult(const FManifestSaveResult& Other);`
- L101 _public prototype_ `FManifestSaveResult(FManifestSaveResult&& Other);`
- L103 _public prototype_ `FManifestSaveResult& operator=(const FManifestSaveResult& Other);`
- L104 _public prototype_ `FManifestSaveResult& operator=(FManifestSaveResult&& Other);`
- L107 _public prototype_ `explicit FManifestSaveResult(const PREGEN_NS::ManifestSaveResult& InManifestSaveResult);`
- L108 _public prototype_ `explicit FManifestSaveResult(PREGEN_NS::ManifestSaveResult&& InManifestSaveResult);`
- L110 _public prototype_ `FManifestSaveResult& operator=(const PREGEN_NS::ManifestSaveResult& InManifestSaveResult);`
- L111 _public prototype_ `FManifestSaveResult& operator=(PREGEN_NS::ManifestSaveResult&& InManifestSaveResult);`
- L113 _public prototype_ `operator PREGEN_NS::ManifestSaveResult() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L12 _namespace_ `namespace PREGEN_NS`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UsdPregen` (scope `UE`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/SceneDiscovery.h` (Public)


#### class `UE::UsdPregen::FSceneDiscovery`  
`class FSceneDiscovery`  
_L33-69_
- L36 _public typedef_ `using ResultMap = TMap<UE::FSdfPath, TArray<FTargetUid>>;`
- L39 _public prototype_ `explicit FSceneDiscovery(const UE::FUsdStage& Stage);`
- L40 _public prototype_ `FSceneDiscovery(const UE::FUsdStage& Stage, const FPregenDiscoveryOptions& Options);`
- L42 _public prototype_ `FSceneDiscovery(const FSceneDiscovery& Other);`
- L43 _public prototype_ `FSceneDiscovery(FSceneDiscovery&& Other);`
- L44 _public prototype_ `~FSceneDiscovery();`
- L46 _public prototype_ `FSceneDiscovery& operator=(const FSceneDiscovery& Other);`
- L47 _public prototype_ `FSceneDiscovery& operator=(FSceneDiscovery&& Other);`
- L50 _public prototype_ `explicit FSceneDiscovery(const PREGEN_NS::SceneDiscovery& InSceneDiscovery);`
- L51 _public prototype_ `explicit FSceneDiscovery(PREGEN_NS::SceneDiscovery&& InSceneDiscovery);`
- L53 _public prototype_ `FSceneDiscovery& operator=(const PREGEN_NS::SceneDiscovery& InSceneDiscovery);`
- L54 _public prototype_ `FSceneDiscovery& operator=(PREGEN_NS::SceneDiscovery&& InSceneDiscovery);`
- L56 _public prototype_ `operator PREGEN_NS::SceneDiscovery& ();`
- L57 _public prototype_ `operator const PREGEN_NS::SceneDiscovery& () const;`
- L61 _public prototype_ `FTargetData GetTargetData(const FTargetUid& TargetUid);`
- L63 _public prototype_ `bool TraverseAndFindTargets(ResultMap& Results);`
- L65 _public prototype_ `bool SaveDiscoveryData(const FString& Filename);`
- L68 _private member_ `TUniquePtr<Internal::FSceneDiscoveryImpl> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L13 _namespace_ `namespace PREGEN_NS`
- L19 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UsdPregen` (scope `UE`)
- L28 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/SceneTracker.h` (Public)


#### class `UE::UsdPregen::FTrackedPrim`  
`class FTrackedPrim`  
_L39-63_
- L42 _public prototype_ `FTrackedPrim();`
- L43 _public prototype_ `FTrackedPrim(FTrackedPrim&& Other);`
- L44 _public prototype_ `~FTrackedPrim();`
- L46 _public prototype_ `FTrackedPrim& operator=(FTrackedPrim&& Other);`
- L48 _public prototype_ `FTrackedPrim(const FTrackedPrim&) = delete;`
- L49 _public prototype_ `FTrackedPrim& operator=(const FTrackedPrim&) = delete;`
- L52 _public prototype_ `explicit FTrackedPrim(PREGEN_NS::TrackedPrim&& InTrackedPrim);`
- L54 _public prototype_ `FTrackedPrim& operator=(PREGEN_NS::TrackedPrim&& InTrackedPrim);`
- L58 _public prototype_ `bool HasUnprocessedPermutations() const;`
- L59 _public prototype_ `bool PrepareNextPermutation();`
- L62 _private member_ `TUniquePtr<Internal::FTrackedPrimImpl> Impl;`

#### class `UE::UsdPregen::FSceneTrackerBase`  
`template<typename PtrType> class FSceneTrackerBase`  
_L66-123_
- L69 _public prototype_ `FSceneTrackerBase();`
- L71 _public prototype_ `FSceneTrackerBase(const FSceneTracker& Other);`
- L72 _public prototype_ `FSceneTrackerBase(FSceneTracker&& Other);`
- L73 _public prototype_ `FSceneTrackerBase(const FSceneTrackerWeak& Other);`
- L74 _public prototype_ `FSceneTrackerBase(FSceneTrackerWeak&& Other);`
- L76 _public prototype_ `FSceneTrackerBase& operator=(const FSceneTracker& Other);`
- L77 _public prototype_ `FSceneTrackerBase& operator=(FSceneTracker&& Other);`
- L78 _public prototype_ `FSceneTrackerBase& operator=(const FSceneTrackerWeak& Other);`
- L79 _public prototype_ `FSceneTrackerBase& operator=(FSceneTrackerWeak&& Other);`
- L81 _public prototype_ `~FSceneTrackerBase();`
- L83 _public prototype_ `explicit operator bool() const;`
- L86 _public prototype_ `template<typename OtherPtrType> bool operator==(const FSceneTrackerBase<OtherPtrType>& Other) const;`
- L89 _public prototype_ `explicit FSceneTrackerBase(const PREGEN_NS::SceneTrackerRefPtr& InSceneTracker);`
- L90 _public prototype_ `explicit FSceneTrackerBase(PREGEN_NS::SceneTrackerRefPtr&& InSceneTracker);`
- L91 _public prototype_ `explicit FSceneTrackerBase(const PREGEN_NS::SceneTrackerWeakPtr& InSceneTracker);`
- L92 _public prototype_ `explicit FSceneTrackerBase(PREGEN_NS::SceneTrackerWeakPtr&& InSceneTracker);`
- L94 _public prototype_ `operator PtrType& ();`
- L95 _public prototype_ `operator const PtrType& () const;`
- L97 _public prototype_ `operator PREGEN_NS::SceneTrackerRefPtr() const;`
- L98 _public prototype_ `operator PREGEN_NS::SceneTrackerWeakPtr() const;`
- L102 _public prototype_ `FPregenDiscoveryOptions GetOptions() const;`
- L104 _public prototype_ `FTargetData GetTargetData(const FTargetUid& TargetId) const;`
- L106 _public prototype_ `bool HasErrors() const;`
- L108 _public prototype_ `bool SaveDataLayer(const FString& Filename) const;`
- L110 _public prototype_ `FTrackedPrim StartTrackingPrim(const UE::FUsdPrim& Prim);`
- L112 _public prototype_ `void SetTargetCreatedCallback( TFunction<void(const UE::FSdfPath&, const FTargetUid&)> Callback );`
- L116 _public prototype_ `void RemoveTargetCreatedCallback();`
- L122 _private member_ `TUniquePtr<Internal::FSceneTrackerImpl<PtrType>> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L13 _namespace_ `namespace PREGEN_NS`
- L18 _typedef_ `using SceneTrackerRefPtr = std::shared_ptr<SceneTracker>;` (scope `PREGEN_NS`)
- L19 _typedef_ `using SceneTrackerWeakPtr = std::weak_ptr<SceneTracker>;` (scope `PREGEN_NS`)
- L23 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UsdPregen` (scope `UE`)
- L31 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/StoragePlugin.h` (Public)


#### class `UE::UsdPregen::FStoragePluginBase`  
`template<typename PtrType> class FStoragePluginBase`  
_L49-123_
- L52 _public prototype_ `FStoragePluginBase();`
- L54 _public prototype_ `FStoragePluginBase(const FStoragePlugin& Other);`
- L55 _public prototype_ `FStoragePluginBase(FStoragePlugin&& Other);`
- L56 _public prototype_ `FStoragePluginBase(const FStoragePluginWeak& Other);`
- L57 _public prototype_ `FStoragePluginBase(FStoragePluginWeak&& Other);`
- L59 _public prototype_ `FStoragePluginBase& operator=(const FStoragePlugin& Other);`
- L60 _public prototype_ `FStoragePluginBase& operator=(FStoragePlugin&& Other);`
- L61 _public prototype_ `FStoragePluginBase& operator=(const FStoragePluginWeak& Other);`
- L62 _public prototype_ `FStoragePluginBase& operator=(FStoragePluginWeak&& Other);`
- L64 _public prototype_ `~FStoragePluginBase();`
- L66 _public prototype_ `explicit operator bool() const;`
- L69 _public prototype_ `template<typename OtherPtrType> bool operator==(const FStoragePluginBase<OtherPtrType>& Other) const;`
- L72 _public prototype_ `explicit FStoragePluginBase(const PREGEN_NS::StoragePluginRefPtr& InStorage);`
- L73 _public prototype_ `explicit FStoragePluginBase(PREGEN_NS::StoragePluginRefPtr&& InStorage);`
- L74 _public prototype_ `explicit FStoragePluginBase(const PREGEN_NS::StoragePluginWeakPtr& InStorage);`
- L75 _public prototype_ `explicit FStoragePluginBase(PREGEN_NS::StoragePluginWeakPtr&& InStorage);`
- L77 _public prototype_ `operator PtrType& ();`
- L78 _public prototype_ `operator const PtrType& () const;`
- L80 _public prototype_ `operator PREGEN_NS::StoragePluginRefPtr() const;`
- L81 _public prototype_ `operator PREGEN_NS::StoragePluginWeakPtr() const;`
- L85 _public prototype_ `bool IsValid() const;`
- L87 _public prototype_ `bool Initialize() const;`
- L89 _public prototype_ `bool Shutdown() const;`
- L91 _public prototype_ `FManifestLoadResult LoadManifestPayload(const FTargetUid& TargetUid) const;`
- L93 _public prototype_ `FManifestSaveResult StoreManifestPayload( const FTargetUid& TargetUid, const FManifestPayload& Payload ) const;`
- L98 _public prototype_ `FManifestSaveResult PersistManifestPayload(const FTargetUid& TargetUid) const;`
- L100 _public prototype_ `FManifestPayload SerializeManifest(const FManifest& Manifest) const;`
- L102 _public prototype_ `FManifest DeserializeManifestPayload(const FManifestPayload& Payload) const;`
- L104 _public prototype_ `FString GetNameForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) const;`
- L110 _public prototype_ `FString GetPackageSubPathForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) const;`
- L116 _public prototype_ `FString GetPathForManifest(const FTargetUid& TargetUid) const;`
- L122 _private member_ `TUniquePtr<Internal::FStoragePluginImpl<PtrType>> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L12 _namespace_ `namespace PREGEN_NS`
- L16 _typedef_ `using StoragePluginRefPtr = std::shared_ptr<StoragePlugin>;` (scope `PREGEN_NS`)
- L17 _typedef_ `using StoragePluginWeakPtr = std::weak_ptr<StoragePlugin>;` (scope `PREGEN_NS`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UsdPregen` (scope `UE`)
- L31 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)
- L41 _typedef_ `using FStoragePlugin = FStoragePluginBase<PREGEN_NS::StoragePluginRefPtr>;` (scope `UE::UsdPregen`)
- L42 _typedef_ `using FStoragePluginWeak = FStoragePluginBase<PREGEN_NS::StoragePluginWeakPtr>;` (scope `UE::UsdPregen`)
- L44 _typedef_ `using FStoragePlugin = FStoragePluginBase<FDummyRefPtrType>;` (scope `UE::UsdPregen`)
- L45 _typedef_ `using FStoragePluginWeak = FStoragePluginBase<FDummyWeakPtrType>;` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/StoragePluginAdapter.h` (Public)


#### class `UE::UsdPregen::FStoragePluginAdapter`  
`class FStoragePluginAdapter : public PREGEN_NS::StoragePlugin`  
_L32-80_
- inherits: `PREGEN_NS::StoragePlugin`
- L35 _public prototype_ `explicit FStoragePluginAdapter( const TSharedRef<IStoragePlugin, ESPMode::ThreadSafe>& InStoragePlugin );`
- L41 _public prototype_ `virtual PREGEN_NS::ManifestLoadResult LoadManifestPayload( const PREGEN_NS::TargetUid& TargetUid ) override;`
- L45 _public prototype_ `virtual PREGEN_NS::ManifestSaveResult StoreManifestPayload( const PREGEN_NS::TargetUid& TargetUid, const PREGEN_NS::ManifestPayload& Payload ) override;`
- L50 _public prototype_ `virtual PREGEN_NS::ManifestSaveResult PersistManifestPayload( const PREGEN_NS::TargetUid& TargetUid ) override;`
- L54 _public prototype_ `virtual PREGEN_NS::ManifestPayload SerializeManifest( const PREGEN_NS::Manifest& Manifest ) override;`
- L58 _public prototype_ `virtual PREGEN_NS::Manifest DeserializeManifestPayload( const PREGEN_NS::ManifestPayload& Payload ) override;`
- L62 _public prototype_ `virtual std::string GetNameForUAsset( const PREGEN_NS::TargetUid& TargetUid, const std::vector<const PREGEN_NS::ExtAssetDefinition*>& ExtAssetDefinitions, const std::string& AssetType ) override;`
- L68 _public prototype_ `virtual std::string GetPackageSubPathForUAsset( const PREGEN_NS::TargetUid& TargetUid, const std::vector<const PREGEN_NS::ExtAssetDefinition*>& ExtAssetDefinitions, const std::string& AssetType ) override;`
- L74 _public prototype_ `virtual std::string GetPathForManifest( const PREGEN_NS::TargetUid& TargetUid ) override;`
- L79 _private member_ `TSharedRef<IStoragePlugin, ESPMode::ThreadSafe> StoragePlugin;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L20 _namespace_ `namespace PREGEN_NS`
- L25 _typedef_ `using StoragePluginRefPtr = std::shared_ptr<StoragePlugin>;` (scope `PREGEN_NS`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UsdPregen` (scope `UE`)
- L82 _prototype_ `PREGEN_NS::StoragePluginRefPtr MakeStoragePluginAdapter( const TSharedRef<IStoragePlugin, ESPMode::ThreadSafe>& InStoragePlugin );` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/StoragePluginRegistry.h` (Public)


#### class `UE::UsdPregen::FStoragePluginRegistry`  
`class FStoragePluginRegistry`  
_L24-52_
- L27 _public prototype_ `FStoragePluginRegistry() = default;`
- L30 _public prototype_ `explicit FStoragePluginRegistry(PREGEN_NS::StoragePluginRegistry* InRegistry);`
- L32 _public prototype_ `operator PREGEN_NS::StoragePluginRegistry* ();`
- L33 _public prototype_ `operator const PREGEN_NS::StoragePluginRegistry* () const;`
- L37 _public prototype_ `static FStoragePluginRegistry GetInstance();`
- L39 _public prototype_ `bool RegisterFactory( const FString& Name, FCreateStoragePluginFunction Factory );`
- L44 _public prototype_ `FStoragePlugin Create( const FPregenStorageOptions& Options ) const;`
- L50 _private member_ `PREGEN_NS::StoragePluginRegistry* PregenRegistry = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L11 _namespace_ `namespace PREGEN_NS`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UsdPregen` (scope `UE`)
- L21 _typedef_ `using FCreateStoragePluginFunction = TFunction<TSharedRef<IStoragePlugin, ESPMode::ThreadSafe>(const FPregenStorageOptions& Options)>;` (scope `UE::UsdPregen`)

### `Plugins/Experimental/USDPregen/Source/USDPregenWrapper/Public/UsdPregenWrappers/Target.h` (Public)


#### class `UE::UsdPregen::FTargetUid`  
`class FTargetUid`  
_L52-93_
- L55 _public prototype_ `FTargetUid();`
- L57 _public prototype_ `FTargetUid(const FTargetUid& Other);`
- L58 _public prototype_ `FTargetUid(FTargetUid&& Other);`
- L59 _public prototype_ `~FTargetUid();`
- L61 _public prototype_ `FTargetUid& operator=(const FTargetUid& Other);`
- L62 _public prototype_ `FTargetUid& operator=(FTargetUid&& Other);`
- L64 _public prototype_ `explicit FTargetUid(const FString& DefinitionUid);`
- L65 _public prototype_ `FTargetUid(const FString& DefinitionUid, const FString& PermutationUid);`
- L67 _public prototype_ `bool operator==(const FTargetUid& Other) const;`
- L68 _public prototype_ `bool operator!=(const FTargetUid& Other) const;`
- L69 _public prototype_ `bool operator<(const FTargetUid& Other) const;`
- L71 _public prototype_ `explicit operator bool() const;`
- L74 _public prototype_ `explicit FTargetUid(const PREGEN_NS::TargetUid& InTargetUid);`
- L75 _public prototype_ `explicit FTargetUid(PREGEN_NS::TargetUid&& InTargetUid);`
- L77 _public prototype_ `FTargetUid& operator=(const PREGEN_NS::TargetUid& InTargetUid);`
- L78 _public prototype_ `FTargetUid& operator=(PREGEN_NS::TargetUid&& InTargetUid);`
- L80 _public prototype_ `operator PREGEN_NS::TargetUid& ();`
- L81 _public prototype_ `operator const PREGEN_NS::TargetUid& () const;`
- L85 _public prototype_ `FString GetDefinitionUid() const;`
- L86 _public prototype_ `FString GetPermutationUid() const;`
- L87 _public prototype_ `bool HasPermutationUid() const;`
- L88 _public prototype_ `FString GetString() const;`
- L89 _public prototype_ `bool IsValid() const;`
- L92 _private member_ `TUniquePtr<Internal::FTargetUidImpl> Impl;`

#### struct `UE::UsdPregen::FPermutationOpArg`  
`struct FPermutationOpArg`  
_L101-111_
- desc: Keeps the Sdf value type name alongside the string-encoded value so the op can be reconstructed faithfully on the deserialize side.
- L104 _public member_ `FString Name;` — Argument name with the "opargs:" prefix removed.
- L107 _public member_ `FString TypeName;` — Sdf value type name (e.g. "string", "token").
- L110 _public member_ `FString Value;` — String-encoded default value.

#### struct `UE::UsdPregen::FPermutationOp`  
`struct FPermutationOp`  
_L119-128_
- desc: Captures the prim-spec type name authored by the underlying op's Serialize() implementation plus its "opargs:*" attributes. Mirrors the Core SerializedOp shape one-for-one so wrapper consumers can round-trip an op without depending on Core or USD headers directly.
- L124 _public member_ `FString TypeName;` — Op type name (e.g. "UsdVariantSelectionOp", "UsdInheritOp", "UsdSchemaApplyOp"). Matches the value written by the underlying op's Serialize() override.
- L127 _public member_ `TArray<FPermutationOpArg> Opargs;` — Argument list extracted from the op's "opargs:" namespace.

#### class `UE::UsdPregen::FTargetDefinitionEntry`  
`class FTargetDefinitionEntry`  
_L130-166_
- L133 _public prototype_ `FTargetDefinitionEntry();`
- L135 _public prototype_ `FTargetDefinitionEntry(const FTargetDefinitionEntry& Other);`
- L136 _public prototype_ `FTargetDefinitionEntry(FTargetDefinitionEntry&& Other);`
- L137 _public prototype_ `~FTargetDefinitionEntry();`
- L139 _public prototype_ `FTargetDefinitionEntry& operator=(const FTargetDefinitionEntry& Other);`
- L140 _public prototype_ `FTargetDefinitionEntry& operator=(FTargetDefinitionEntry&& Other);`
- L142 _public prototype_ `FTargetDefinitionEntry(const FString& DefinitionUid, const UE::FSdfPath& ScenePath);`
- L145 _public prototype_ `explicit FTargetDefinitionEntry(const PREGEN_NS::TargetDefinitionEntry& InTargetDefinitionEntry);`
- L146 _public prototype_ `explicit FTargetDefinitionEntry(PREGEN_NS::TargetDefinitionEntry&& InTargetDefinitionEntry);`
- L148 _public prototype_ `FTargetDefinitionEntry& operator=(const PREGEN_NS::TargetDefinitionEntry& InTargetDefinitionEntry);`
- L149 _public prototype_ `FTargetDefinitionEntry& operator=(PREGEN_NS::TargetDefinitionEntry&& InTargetDefinitionEntry);`
- L151 _public prototype_ `operator PREGEN_NS::TargetDefinitionEntry& ();`
- L152 _public prototype_ `operator const PREGEN_NS::TargetDefinitionEntry& () const;`
- L156 _public prototype_ `FExtAssetDefinition GetDefinition() const;`
- L157 _public prototype_ `UE::FSdfPath GetScenePath() const;`
- L162 _public prototype_ `TArray<FPermutationOp> GetPermutationOps() const;` — May be empty when no permutation ops are associated with this scope.
- L165 _private member_ `TUniquePtr<Internal::FTargetDefinitionEntryImpl> Impl;`

#### class `UE::UsdPregen::FTargetDataBase`  
`template<typename PtrType> class FTargetDataBase`  
_L169-226_
- L172 _public prototype_ `FTargetDataBase();`
- L174 _public prototype_ `FTargetDataBase(const FTargetData& Other);`
- L175 _public prototype_ `FTargetDataBase(FTargetData&& Other);`
- L176 _public prototype_ `FTargetDataBase(const FTargetDataWeak& Other);`
- L177 _public prototype_ `FTargetDataBase(FTargetDataWeak&& Other);`
- L179 _public prototype_ `FTargetDataBase& operator=(const FTargetData& Other);`
- L180 _public prototype_ `FTargetDataBase& operator=(FTargetData&& Other);`
- L181 _public prototype_ `FTargetDataBase& operator=(const FTargetDataWeak& Other);`
- L182 _public prototype_ `FTargetDataBase& operator=(FTargetDataWeak&& Other);`
- L184 _public prototype_ `~FTargetDataBase();`
- L186 _public prototype_ `explicit operator bool() const;`
- L189 _public prototype_ `template<typename OtherPtrType> bool operator==(const FTargetDataBase<OtherPtrType>& Other) const;`
- L192 _public prototype_ `explicit FTargetDataBase(const PREGEN_NS::TargetDataRefPtr& InTargetData);`
- L193 _public prototype_ `explicit FTargetDataBase(PREGEN_NS::TargetDataRefPtr&& InTargetData);`
- L194 _public prototype_ `explicit FTargetDataBase(const PREGEN_NS::TargetDataWeakPtr& InTargetData);`
- L195 _public prototype_ `explicit FTargetDataBase(PREGEN_NS::TargetDataWeakPtr&& InTargetData);`
- L197 _public prototype_ `operator PtrType& ();`
- L198 _public prototype_ `operator const PtrType& () const;`
- L200 _public prototype_ `operator PREGEN_NS::TargetDataRefPtr() const;`
- L201 _public prototype_ `operator PREGEN_NS::TargetDataWeakPtr() const;`
- L205 _public prototype_ `bool IsValid() const;`
- L207 _public prototype_ `FTargetUid GetUniqueId() const;`
- L208 _public prototype_ `int32 NumDefinitionEntries() const;`
- L209 _public prototype_ `FTargetDefinitionEntry GetDefinitionEntry(size_t Index) const;`
- L210 _public prototype_ `TArray<FTargetDefinitionEntry> GetDefinitionEntries() const;`
- L211 _public prototype_ `TArray<FTargetUid> GetDependencies() const;`
- L214 _public prototype_ `TArray<FString> GetEncapsulatedDefinitionPaths() const;` — Returns the encapsulated definition paths as scene-path strings.
- L217 _public prototype_ `TArray<FString> GetUnencapsulatedDefinitionPaths() const;` — Returns the unencapsulated definition paths as scene-path strings.
- L219 _public prototype_ `UE::FSdfLayer GetPermutationOverlay() const;`
- L225 _private member_ `TUniquePtr<Internal::FTargetDataImpl<PtrType>> Impl;`

#### class `UE::UsdPregen::FTargetDataBuilder`  
`class FTargetDataBuilder`  
_L239-274_
- desc: Used by storage backends to rebuild a target data from serialized form without having to depend on Core or USD headers directly. Internally creates the underlying TargetData via Core's internal::TargetDataBuilder.
- L242 _public prototype_ `explicit FTargetDataBuilder(const FTargetUid& Uid);`
- L243 _public prototype_ `~FTargetDataBuilder();`
- L245 _public prototype_ `FTargetDataBuilder(const FTargetDataBuilder&) = delete;`
- L246 _public prototype_ `FTargetDataBuilder& operator=(const FTargetDataBuilder&) = delete;`
- L248 _public prototype_ `FTargetDataBuilder(FTargetDataBuilder&& Other);`
- L249 _public prototype_ `FTargetDataBuilder& operator=(FTargetDataBuilder&& Other);`
- L252 _public prototype_ `void AddInfo(const FString& DefinitionUid, const UE::FSdfPath& ScenePath, const TArray<FPermutationOp>& Ops);` — Adds a TargetDefinitionEntry entry with its associated permutation ops.
- L256 _public prototype_ `void SetDependencies(const TArray<FTargetUid>& Dependencies);`
- L260 _public prototype_ `void SetEncapsulatedDefinitionPaths(const TArray<FString>& Paths);` — Replaces the encapsulated definition path set. Invalid path strings are skipped with a warning.
- L264 _public prototype_ `void SetUnencapsulatedDefinitionPaths(const TArray<FString>& Paths);` — Replaces the unencapsulated definition path set. Invalid path strings are skipped with a warning.
- L270 _public prototype_ `FTargetData Build();` — The builder is consumed by this call - subsequent invocations return an empty FTargetData.
- L273 _private member_ `TUniquePtr<Internal::FTargetDataBuilderImpl> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDPREGENWRAPPER_API`
- L12 _namespace_ `namespace PREGEN_NS`
- L18 _typedef_ `using TargetDataRefPtr = std::shared_ptr<TargetData>;` (scope `PREGEN_NS`)
- L19 _typedef_ `using TargetDataWeakPtr = std::weak_ptr<TargetData>;` (scope `PREGEN_NS`)
- L23 _namespace_ `namespace UE`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace UsdPregen` (scope `UE`)
- L32 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)
- L45 _typedef_ `using FTargetData = FTargetDataBase<PREGEN_NS::TargetDataRefPtr>;` (scope `UE::UsdPregen`)
- L46 _typedef_ `using FTargetDataWeak = FTargetDataBase<PREGEN_NS::TargetDataWeakPtr>;` (scope `UE::UsdPregen`)
- L48 _typedef_ `using FTargetData = FTargetDataBase<FDummyRefPtrType>;` (scope `UE::UsdPregen`)
- L49 _typedef_ `using FTargetDataWeak = FTargetDataBase<FDummyWeakPtrType>;` (scope `UE::UsdPregen`)
- L95 _prototype_ `uint32 GetTypeHash(const FTargetUid& TargetUid);` (scope `UE::UsdPregen`)
- L228 _namespace_ `namespace Internal` (scope `UE::UsdPregen`)
