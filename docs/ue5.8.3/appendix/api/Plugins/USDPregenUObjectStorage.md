# Plugins / USDPregenUObjectStorage

- module root: `Plugins/Experimental/USDPregen/Source/USDPregenUObjectStorage`
- headers: 3; symbols: 62
- symbol kinds: class=3, member=28, namespace=4, prototype=22, struct=5
- PrivateDependencyModuleNames: USDPregenCore, USDPregenInterchange, USDPregenWrapper, UnrealUSDWrapper
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/USDPregen/Source/USDPregenUObjectStorage/Public/USDPregenManifestAsset.h` (Public)


#### struct `FUsdPregenProductEntry`  
`struct FUsdPregenProductEntry`  
_L21-47_
- reflection: `USTRUCT()`
- desc: Reflected product entry for UObject-backed manifest storage.
- L27 _public member_ `FString UPackagePath;` — `UPROPERTY(VisibleAnywhere, Category = "Products")`
- L30 _public member_ `FString UClass;` — `UPROPERTY(VisibleAnywhere, Category = "Products")`
- L33 _public member_ `FString UNodeId;` — `UPROPERTY(VisibleAnywhere, Category = "Products")`
- L36 _public member_ `FString UsdPrimType;` — `UPROPERTY(VisibleAnywhere, Category = "Products")`
- L39 _public member_ `FString UsdPrimPath;` — `UPROPERTY(VisibleAnywhere, Category = "Products")`
- L42 _public prototype_ `FUsdPregenProductEntry() = default;`
- L44 _public prototype_ `explicit FUsdPregenProductEntry(const UE::UsdPregen::FProduct& InProduct);`
- L46 _public prototype_ `UE::UsdPregen::FProduct ToWrapper() const;`

#### struct `FUsdPregenSerializedOpArgEntry`  
`struct FUsdPregenSerializedOpArgEntry`  
_L53-69_
- reflection: `USTRUCT()`
- desc: Reflected serialized PermutationOp argument (one entry under "opargs:").
- L60 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Op Arg")` — Argument name with the "opargs:" prefix removed.
- L64 _public member_ `FString TypeName;` — `UPROPERTY(VisibleAnywhere, Category = "Op Arg")` — Sdf value type name (e.g. "string").
- L68 _public member_ `FString Value;` — `UPROPERTY(VisibleAnywhere, Category = "Op Arg")` — String-encoded default value.

#### struct `FUsdPregenSerializedOpEntry`  
`struct FUsdPregenSerializedOpEntry`  
_L75-86_
- reflection: `USTRUCT()`
- desc: Reflected serialized PermutationOp.
- L82 _public member_ `FString TypeName;` — `UPROPERTY(VisibleAnywhere, Category = "Op")` — Op type name as authored by the op's Serialize() override.
- L85 _public member_ `TArray<FUsdPregenSerializedOpArgEntry> Args;` — `UPROPERTY(VisibleAnywhere, Category = "Op")`

#### struct `FUsdPregenTargetUidEntry`  
`struct FUsdPregenTargetUidEntry`  
_L93-103_
- reflection: `USTRUCT()`
- desc: Reflected paired (definitionUid, permutationUid) tuple, used both for the manifest's own target uid and for each entry in the dependencies array.
- L99 _public member_ `FString DefinitionUid;` — `UPROPERTY(VisibleAnywhere, Category = "Target Uid")`
- L102 _public member_ `FString PermutationUid;` — `UPROPERTY(VisibleAnywhere, Category = "Target Uid")`

#### struct `FUsdPregenDefinitionEntry`  
`struct FUsdPregenDefinitionEntry`  
_L116-156_
- reflection: `USTRUCT()`
- desc: Reflected ExtAssetDefinition snapshot, with the scene path and permutation ops that the originating TargetDefinitionEntry carried for this definition folded directly onto the definition entry. One entry per unique definition reachable from the originating TargetData (deduped by UniqueId); the array is ordered by the asset definition stack walk so the entries preserve namespace nesting order. Definitions are re-registered into the AssetDefinitionRegistry on load.
- L122 _public member_ `FString UniqueId;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")`
- L125 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")`
- L128 _public member_ `FString Version;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")`
- L131 _public member_ `FString IdentifierAuthored;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")`
- L134 _public member_ `FString IdentifierResolved;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")`
- L137 _public member_ `bool bHasCustomUniqueId = false;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")`
- L144 _public member_ `FString Metadata;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")` — Round-tripped VtDictionary metadata. Stored as a USDA-format string blob; the encoding format is an implementation detail and may evolve.
- L148 _public member_ `FString ScenePath;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")` — Scene path of the TargetDefinitionEntry that introduced this definition.
- L155 _public member_ `TArray<FUsdPregenSerializedOpEntry> PermutationOps;` — `UPROPERTY(VisibleAnywhere, Category = "Definition")` — Permutation ops applied at this definition's scope of the target. Empty when this scope didn't contribute any ops.

#### class `UUsdPregenManifestAsset`  
`class UUsdPregenManifestAsset : public UObject`  
_L168-193_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: UObject-backed manifest asset that can be serialized by Unreal and shown in the Content Browser. Note: only a subset of the originating TargetData is persisted on the UAsset (target uid, dependencies, deduped definition snapshots with their scene path and permutation ops). The full TargetData remains available to downstream code via FManifest::GetTargetData() and can be persisted by a custom storage plugin if richer state is needed.
- L174 _public member_ `TArray<FUsdPregenProductEntry> Products;` — `UPROPERTY(VisibleAnywhere, Category = "USD Pregen Manifest")`
- L177 _public member_ `FUsdPregenTargetUidEntry Uid;` — `UPROPERTY(VisibleAnywhere, Category = "USD Pregen Manifest|Target")`
- L180 _public member_ `TArray<FUsdPregenTargetUidEntry> Dependencies;` — `UPROPERTY(VisibleAnywhere, Category = "USD Pregen Manifest|Target")`
- L184 _public member_ `TArray<FUsdPregenDefinitionEntry> Definitions;` — `UPROPERTY(VisibleAnywhere, Category = "USD Pregen Manifest")` — Deduped definition snapshots, keyed by UniqueId, ordered by namespace stack walk.
- L188 _public prototype_ `bool IsValidManifest() const;` — `UFUNCTION(BlueprintCallable, Category = "USD Pregen Manifest")`
- L190 _public prototype_ `void FromWrapper(const UE::UsdPregen::FManifest& InManifest);`
- L192 _public prototype_ `UE::UsdPregen::FManifest ToWrapper() const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UsdPregen` (scope `UE`)

### `Plugins/Experimental/USDPregen/Source/USDPregenUObjectStorage/Public/USDPregenUObjectStorageModule.h` (Public)


#### class `FUSDPregenUObjectStorageModule`  
`class FUSDPregenUObjectStorageModule : public IModuleInterface`  
_L8-17_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `FDelegateHandle OnPostEngineInitHandle;`

### `Plugins/Experimental/USDPregen/Source/USDPregenUObjectStorage/Public/USDPregenUObjectStoragePlugin.h` (Public)


#### class `UE::UsdPregen::FUsdPregenUObjectStoragePlugin`  
`class FUsdPregenUObjectStoragePlugin : public IStoragePlugin`  
_L26-76_
- inherits: `IStoragePlugin`
- desc: A storage plugin instance is expected to live for a single import. The constructor captures the user's import content folder from UUSDPregenSettings and uses it to place each manifest UAsset in the same content folder as that target's products. Reusing one instance across imports with different content paths would surface stale paths.
- L29 _public prototype_ `FUsdPregenUObjectStoragePlugin();`
- L31 _public prototype_ `explicit FUsdPregenUObjectStoragePlugin(const FPregenStorageOptions& Options);`
- L33 _public prototype_ `virtual FManifestLoadResult LoadManifestPayload(const FTargetUid& TargetUid) override;`
- L35 _public prototype_ `virtual FManifestSaveResult StoreManifestPayload( const FTargetUid& TargetUid, const FManifestPayload& Payload ) override;`
- L40 _public prototype_ `virtual FManifestSaveResult PersistManifestPayload(const FTargetUid& TargetUid) override;`
- L42 _public prototype_ `virtual FManifestPayload SerializeManifest(const FManifest& Manifest) override;`
- L44 _public prototype_ `virtual FManifest DeserializeManifestPayload(const FManifestPayload& Payload) override;`
- L46 _public prototype_ `virtual FString GetNameForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) override;`
- L52 _public prototype_ `virtual FString GetPackageSubPathForUAsset( const FTargetUid& TargetUid, const TArray<FExtAssetDefinition>& Definitions, const FString& AssetType ) override;`
- L58 _public prototype_ `virtual FString GetPathForManifest(const FTargetUid& TargetUid) override;`
- L61 _private prototype_ `static FString GetPayloadEncoding();`
- L63 _private prototype_ `FString MakeManifestAssetName(const FTargetUid& TargetUid) const;`
- L64 _private prototype_ `FString MakeManifestObjectPath(const FTargetUid& TargetUid);`
- L66 _private prototype_ `UUsdPregenManifestAsset* LoadManifestAsset(const FTargetUid& TargetUid);`
- L69 _private member_ `FString ContentBasePath;`
- L75 _private member_ `FString PackageSubPathTemplate;` — ${PLACEHOLDER} template used to build the package sub-path for generated UAssets. See IStoragePlugin::ResolvePackageSubPathTemplate. Falls back to UUSDPregenSettings::PackageSubPathTemplate, then to IStoragePlugin::DefaultPackageSubPathTemplate().

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UsdPregen` (scope `UE`)
