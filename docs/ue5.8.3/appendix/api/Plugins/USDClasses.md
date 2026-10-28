# Plugins / USDClasses

- module root: `Plugins/Runtime/USDCore/Source/USDClasses`
- headers: 18; symbols: 425
- symbol kinds: class=18, enum=10, enumerator=38, function=16, macro=5, member=139, namespace=9, prototype=162, struct=12, typedef=2, variable=14
- PrivateDependencyModuleNames: DeveloperSettings, GeometryCache, GeometryFramework, HairStrandsCore, Json, LevelSequence, MaterialEditor, MeshDescription, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: Analytics, Core, CoreUObject, Engine, Slate, SlateCore

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDAssetCache.h` (Public)


#### class `UUsdAssetCache`  
`class UE_DEPRECATED(all, "Use the UUsdAssetCache2 class instead, which is an actual asset you can create on the Content Browser") UUsdAssetCache : public UObject`  
_L12-107_
- reflection: `UCLASS(meta = (ScriptName = "UsdAssetCache_Deprecated"))`
- inherits: `UObject`
- L17 _public prototype_ `UUsdAssetCache();`
- L20 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L23 _public prototype_ `void CacheAsset(const FString& Hash, UObject* Asset, const FString& PrimPath = FString());`
- L24 _public prototype_ `void DiscardAsset(const FString& Hash);`
- L25 _public prototype_ `UObject* GetCachedAsset(const FString& Hash) const;`
- L27 _public function_ `TMap<FString, TObjectPtr<UObject>> GetCachedAssets() const`
- L35 _public prototype_ `void LinkAssetToPrim(const FString& PrimPath, UObject* Asset);`
- L36 _public prototype_ `void RemoveAssetPrimLink(const FString& PrimPath);`
- L37 _public prototype_ `UObject* GetAssetForPrim(const FString& PrimPath) const;`
- L40 _public prototype_ `FString GetPrimForAsset(UObject* Asset) const;` — Returns the first prim path associated with an asset (see TMap::FindKey)
- L46 _public prototype_ `FString GetHashForAsset(UObject* Asset) const;` — Returns the hash used as a key for an asset, in case we own it. Returns the empty string otherwise.
- L48 _public function_ `TMap<FString, TWeakObjectPtr<UObject>> GetAssetPrimLinks() const`
- L53 _public function_ `bool IsAssetOwnedByCache(UObject* Asset) const`
- L58 _public function_ `int32 GetNumAssets() const`
- L63 _public prototype_ `void Reset();`
- L73 _public prototype_ `void MarkAssetsAsStale();` — Every time an asset is retrieved/inserted we add it to ActiveAssets. With these functions that container can be reset/returned. When importing via the USDStageImporter we will move assets from this cache to the content folder. The problem is that some of those assets may not be currently used (e.g. inactive variant, purpose, etc.). The USDStageImporter will then use these functions before/after translating the scene to know which items from the cache that are actually used for the current scene.
- L76 _public prototype_ `TSet<UObject*> GetActiveAssets() const;` — Returns assets that aren't marked as stale
- L79 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — We need to be serializable so that AUsdStageActor can duplicate us for PIE
- L86 _private member_ `TMap<FString, TObjectPtr<UObject>> TransientStorage;` — `UPROPERTY(NonPIEDuplicateTransient, Transient, VisibleAnywhere, Category = "Assets")` — For now everything is NonPIEDuplicateTransient as this is mostly a subobject of AUsdStageActor. When the actor is duplicated it will need to reload the stage anyway to rebuild its prim links to components and assets, so there is no point in duplicating the properties here just yet. Obviously we want to duplicate these properties
- L89 _private member_ `TMap<FString, TObjectPtr<UObject>> PersistentStorage;` — `UPROPERTY(NonPIEDuplicateTransient, VisibleAnywhere, Category = "Assets")`
- L92 _private member_ `bool bAllowPersistentStorage;` — `UPROPERTY(EditAnywhere, Category = "Assets", AdvancedDisplay)`
- L96 _private member_ `TSet<TWeakObjectPtr<UObject>> OwnedAssets;` — `UPROPERTY(NonPIEDuplicateTransient)` — Points to the assets in primary storage, used to quickly check if we own an asset
- L100 _private member_ `TMap<FString, TWeakObjectPtr<UObject>> PrimPathToAssets;` — `UPROPERTY(NonPIEDuplicateTransient)` — Keeps associations from prim paths to assets that we own in primary storage
- L103 _private member_ `mutable TSet<UObject*> ActiveAssets;` — Assets that were added/retrieved since the last call to MarkAssetsAsSlate();
- L106 _private member_ `mutable FCriticalSection CriticalSection;` — Used to ensure thread safety

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDCLASSES_API`

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDAssetCache2.h` (Public)


#### class `UUsdAssetCache2`  
`class UE_DEPRECATED(5.8, "Use the UUsdAssetCache3 class instead, which exposes the cached assets on the Content Browser") UUsdAssetCache2 : public UObject`  
_L15-250_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UObject`
- L29 _public member_ `double UnreferencedAssetStorageSizeMB = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — The asset cache will always retain all currently used assets. In addition to that, this limit specifies how much size is allocated to storing assets that remain only for the current session and that aren't being used by any stage. Set this to 0 to disable storing unreferenced assets.
- L39 _public member_ `double PersistentAssetStorageSizeMB = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — This limit specifies how much size is allocated to storing all persistent assets (i.e. assets that will be saved to disk, even if unused by any stage). Set this to 0 to disable persistent asset storage. This has no effect on temporary asset caches (e.g. the ones automatically generated when opening a stage without an asset cache asset assigned)
- L44 _public prototype_ `void CacheAsset(const FString& Hash, UObject* Asset, const UObject* Referencer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Adds an asset to the cache attached to a particular hash, and optionally registering a referencer
- L51 _public prototype_ `bool CanRemoveAsset(const FString& Hash);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Returns true if the asset with the given hash can be removed from the cache. It will return false in case the asset is still being used, either by another consumer asset or directly by some referencer.
- L61 _public prototype_ `UObject* RemoveAsset(const FString& Hash);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — If an asset is associated with `Hash`, it will be returned and the asset cache will stop tracking this asset entirely. Returns nullptr otherwise. See CanRemoveAsset. WARNING: The asset will still be outer'd to the asset cache, however. The caller is in charge of properly placing the asset at a new Outer object.
- L69 _public prototype_ `UObject* GetCachedAsset(const FString& Hash);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Returns an asset associated with a particular `Hash`. If the asset is persistent, unloaded and the "USD.OnDemandCachedAssetLoading" cvar is true, this may cause the asset to be read from the asset cache's file on disk.
- L76 _public prototype_ `bool TouchAsset(const UObject* Asset, const UObject* Referencer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Marks the provided asset as being used at this point, optionally adding a specific referencer. This is useful because the asset cache will always prioritize retaining the most recently used assets
- L86 _public prototype_ `bool AddAssetReference(const UObject* Asset, const UObject* Referencer);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Adds a new UObject referencer to a particular asset, returning true if the operation succeeded. Assets will not be evicted or removed from the cache while the referencer is registered. Note that internally the cache keeps FObjectKey structs constructed from the referencers, instead of direct pointers to them.
- L93 _public prototype_ `bool RemoveAssetReference(const UObject* Asset, const UObject* Referencer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Removes an UObject referencer from a particular asset, returning true if the operation succeeded. If no specific Referencer is provided, all referencers to Asset will be removed.
- L100 _public prototype_ `bool RemoveAllAssetReferences(const UObject* Referencer);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Removes the particular referencer to all assets tracked by the cache, if it was a referencer to any of them. Returns true if at least one asset referencer count was altered by this.
- L107 _public prototype_ `FString GetHashForAsset(const UObject* Asset) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the hash associated with an asset, in case we own it. Returns the empty string otherwise. Note: This has O(1) time complexity.
- L114 _public prototype_ `bool IsAssetOwnedByCache(const FString& AssetPath) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns true in case the asset at `AssetPath` is tracked by the cache in any way (persistent asset, unreferenced or referenced). An example AssetPath would be "/Game/MyTextures/RedBrick.RedBrick".
- L121 _public prototype_ `int32 GetNumAssets() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns how many assets are tracked by the asset cache in total (summing up persistent, referenced and unreferenced storage)
- L128 _public prototype_ `TArray<FString> GetAllAssetHashes() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns all asset hashes tracked by the asset cache, for all storage types. This includes unloaded persistent assets
- L135 _public prototype_ `TArray<UObject*> GetAllLoadedAssets() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns all assets that are currently loaded in the asset cache. This will not include persistent assets that haven't been loaded yet.
- L142 _public prototype_ `TArray<FString> GetAllCachedAssetPaths() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns all asset paths tracked by the asset cache, for all storage types. (e.g. "/Game/MyTextures/RedBrick.RedBrick"). This includes unloaded persistent assets
- L146 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (CallInEditor = "true"))` — Discards all tracked assets across all storage types
- L153 _public prototype_ `void RefreshStorage();` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (CallInEditor = "true"))` — Updates which assets belong to each storage type. You must call this in case you perform direct operations on the asset cache, after those operations are fully complete.
- L156 _public prototype_ `UUsdAssetCache2();`
- L162 _public prototype_ `void MarkAssetsAsStale();` — Every time an asset is retrieved/inserted we add it to ActiveAssets. With these functions that container can be reset/returned.
- L165 _public prototype_ `TSet<UObject*> GetActiveAssets() const;` — Returns assets that aren't marked as stale
- L169 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L171 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L172 _public prototype_ `virtual void PostLoad() override;`
- L177 _private prototype_ `bool TryUnloadAsset(FCachedAssetInfo& InOutInfo);` — Tries unloading unreferenced, persistent assets back to bulkdata on disk if we can
- L178 _private prototype_ `bool IsAssetOwnedByCacheInternal(const FString& AssetPath) const;`
- L179 _private prototype_ `bool AddAssetReferenceInternal(const UObject* Asset, const UObject* Referencer);`
- L180 _private prototype_ `void TouchAssetInternal(const UObject* Asset, const UObject* Referencer = nullptr);`
- L231 _private member_ `TMap<FString, TObjectPtr<UObject>> AssetStorage;` — `UPROPERTY(Transient, VisibleAnywhere, Category = "Owned Assets")` — Main hash to asset storage for all assets that we're currently using and shouldn't be GC'd
- L235 _private member_ `TMap<FString, FSoftObjectPath> PendingPersistentStorage;` — Storage of paths to additional assets that we know are persisted on disk (and tracked on LRUCache), but that we haven't loaded from bulkdata in this session yet
- L239 _private member_ `TLruCache<FSoftObjectPath, FCachedAssetInfo> LRUCache;` — Main storage of assets in most recent to least recently used. This also doubles as an inverse map from object to hash, and as a quick way of checking if we own an asset
- L242 _private member_ `mutable TSet<UObject*> ActiveAssets;` — Assets that were added/retrieved since the last call to MarkAssetsAsSlate();
- L245 _private member_ `mutable FRWLock RWLock;` — Used to ensure thread safety
- L249 _private member_ `const UObject* CurrentScopedReferencer = nullptr;` — When this is set to something, we will track that it is referencing any new asset that we cache. See FUsdScopedAssetCacheReferencer just below

#### enum `UUsdAssetCache2::ECacheStorageType`  
`enum class ECacheStorageType : uint8`  
_L189-195_
- desc: Describes the different "types of storage" we allow on the asset cache. Note: Order is very important here. The rule of thumb is that it should always be OK for an asset in a storage of lower value to have dependencies on assets in storage of higher value (e.g. it's OK for a material in referenced storage to depend on textures in persistent storage, but *not* the other way around!)
- L191 _public enumerator_ `None = 0`
- L192 _public enumerator_ `Unreferenced`
- L193 _public enumerator_ `Referenced`
- L194 _public enumerator_ `Persistent`

#### class `UUsdAssetCache2::FCachedAssetInfo`  
`class FCachedAssetInfo`  
_L200-227_
- desc: Describes all information we know about an asset in storage. Have to put definition here because of how TLruCache is header-only
- L204 _public member_ `FString Hash;` — We also store the asset hash in here as it is handy and allows O(1) asset to hash mapping via the LRUCache
- L207 _public member_ `FByteBulkData BulkData;` — Where the cached asset is actually serialized into
- L210 _public member_ `FSoftObjectPath AssetClassName;` — Information we need separately in order to deserialize the UObject from bulkdata
- L211 _public member_ `FString AssetName;`
- L212 _public member_ `EObjectFlags AssetFlags;`
- L216 _public member_ `uint64 SizeOnDiskInBytes = 0;` — Information fetched on-demand during RefreshStorage, but that persists to disk. Note that "on disk" here really means "on the byte buffer", although the idea is the same
- L217 _public member_ `uint64 SizeOnMemoryInBytes = 0;`
- L218 _public member_ `TSet<FSoftObjectPath> Dependencies;`
- L219 _public member_ `TSet<FSoftObjectPath> Consumers;`
- L222 _public member_ `ECacheStorageType CurrentStorageType = ECacheStorageType::None;` — Transient stuff
- L223 _public member_ `TSet<FObjectKey> Referencers;`
- L226 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner);`

#### struct `FUsdScopedAssetCacheReferencer`  
`struct UE_DEPRECATED(5.8, "No longer used as it's not needed by the UsdAssetCache3") FUsdScopedAssetCacheReferencer`  
_L253-267_
- L256 _public prototype_ `explicit FUsdScopedAssetCacheReferencer(UUsdAssetCache2* InAssetCache, const UObject* Referencer);`
- L257 _public prototype_ `~FUsdScopedAssetCacheReferencer();`
- L259 _public prototype_ `FUsdScopedAssetCacheReferencer() = delete;`
- L260 _public prototype_ `FUsdScopedAssetCacheReferencer(const FUsdScopedAssetCacheReferencer&) = delete;`
- L261 _public prototype_ `FUsdScopedAssetCacheReferencer(FUsdScopedAssetCacheReferencer&&) = delete;`
- L262 _public prototype_ `FUsdScopedAssetCacheReferencer& operator=(const FUsdScopedAssetCacheReferencer&) = delete;`
- L263 _public prototype_ `FUsdScopedAssetCacheReferencer& operator=(FUsdScopedAssetCacheReferencer&&) = delete;`
- L266 _private member_ `TWeakObjectPtr<UUsdAssetCache2> AssetCache;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API USDCLASSES_API`

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDAssetCache3.h` (Public)


#### class `UUsdAssetCache3`  
`class UUsdAssetCache3 : public UObject`  
_L26-429_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, meta = (DisplayName = "USD Asset Cache", ScriptName = "UsdAssetCache"))`
- inherits: `UObject`
- desc: This class is an asset that can be created via the Content Browser and assigned to AUsdStageActors. Its main purpose is to track generated assets based on the hash of the source prim data: Whenever the AUsdStageActor needs to generate e.g. a MaterialInstance, it will first hash the Material prim, and check whether its UUsdAssetCache3 already has an asset of that class for the resulting hash. The cache can then be shared by multiple AUsdStageActors to prevent recreating UObjects from identical, already translated prim data. A "Default Asset Cache" can be set on the project settings, and will be automatically used for any AUsdStageActor that hasn't had an asset cache manually set beforehand.
- L48 _public prototype_ `UObject* GetOrCreateCachedAsset( const FString& Hash, UClass* Class, const FString& DesiredName, int32 DesiredFlags, bool& bOutCreatedAsset, const UObject* Referencer = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the cached UObject of the provided Class for the provided Hash if one exists. Otherwise, finds a new package for it on the cache's AssetDirectory and creates the asset via a NewObject<Class> call, using with a sanitized version of the desired name and flags. WARNING: As this may try loading a package from disk or call NewObject, this can only be called from the game thread! @param Hash - The string key to check with @param Class - The class of the object that we want to retrieve or create from the asset cache @param DesiredName - The name we want the created object to have (the actual name may have additional suffixes) @param DesiredFlags - The flags we want the created object to have (the actual applied flags may differ depending on context) @param bOutCreatedAsset - Set to true if we created the asset that was return, but false if we returned an existing asset @param Referencer - The asset will not be deleted or untracked until this referencer is removed (via any of the RemoveAssetReferencer member functions) @return The asset that was returned or created
- L70 _public function_ `template<typename T> T* GetOrCreateCachedAsset( const FString& Hash, FString DesiredName, EObjectFlags DesiredFlags, bool* bOutCreatedAsset = nullptr, const UObject* Referencer = nullptr )` — Templated version of GetOrCreateCachedAsset for convenience WARNING: As this may try loading a package from disk or call NewObject, this can only be called from the game thread! @param Hash - The string key to check with @param DesiredName - The name we want the created object to have (the actual name may have additional suffixes) @param DesiredFlags - The flags we want the created object to have (the actual applied flags may differ depending on context) @param bOutCreatedAsset - Set to true if we created the asset that was return, but false if we returned an existing asset @param Referencer - The asset will not be deleted or untracked until this referencer is removed (via any of the RemoveAssetReferencer member functions) @return The asset that was returned or created
- L105 _public prototype_ `UObject* GetOrCreateCustomCachedAsset( const FString& Hash, UClass* Class, const FString& DesiredName, EObjectFlags DesiredFlags, TFunctionRef<UObject*(UPackage* PackageOuter, FName SanitizedName, EObjectFlags FlagsToUse)> ObjectCreationFunc, bool* bOutCreatedAsset = nullptr, const UObject* Referencer = nullptr );` — For most asset types GetOrCreateCachedAsset should suffice: It will internally call NewObject<Class>(). Some asset types or workflows have different ways of instantiating the assets though, like textures which must go through the UTextureFactory, MIDs that must be constructed via UMaterialInstanceDynamic::Create, and others. For those cases you can call this function, and provide a lambda that actually creates the UObject* itself based on the provided package Outer and sanitized FName. WARNING: As this may try loading a package from disk or call NewObject, this can only be called from the game thread! @param Hash - The string key to check with @param Class - The class of the object that we want to retrieve or create from the asset cache @param DesiredName - The name we want the created object to have (the actual name may have additional suffixes) @param DesiredFlags - The flags we want the created object to have (the actual applied flags may differ depending on context) @param ObjectCreationFunc - Lambda that will be called to actually create the UObject. The lambda should internally use the PackageOuter parameter as its outer, and the provided SanitizeName and FlagsToUse. @param bOutCreatedAsset - Set to true if we created the asset that was return, but false if we returned an existing asset @param Referencer - The asset will not be deleted or untracked until this referencer is removed (via any of the RemoveAssetReferencer member functions) @return The asset that was returne
- L129 _public function_ `template<typename T> T* GetOrCreateCustomCachedAsset( const FString& Hash, FString DesiredName, EObjectFlags DesiredFlags, TFunctionRef<UObject*(UPackage* PackageOuter, FName SanitizedName, EObjectFlags FlagsToUse)> ObjectCreationFunc, bool* bOutCreatedAsset = nullptr, const UObject* Referencer = nullptr )` — Templated version of GetOrCreateCachedAsset for convenience WARNING: As this may try loading a package from disk or call NewObject, this can only be called from the game thread! @param Hash - The string key to check with @param DesiredName - The name we want the created object to have (the actual name may have additional suffixes) @param DesiredFlags - The flags we want the created object to have (the actual applied flags may differ depending on context) @param ObjectCreationFunc - Lambda that will be called to actually create the UObject. The lambda should internally use the PackageOuter parameter as its outer, and the provided SanitizeName and FlagsToUse. @param bOutCreatedAsset - Set to true if we created the asset that was return, but false if we returned an existing asset @param Referencer - The asset will not be deleted or untracked until this referencer is removed (via any of the RemoveAssetReferencer member functions) @return The asset that was returned or created
- L145 _public prototype_ `void CacheAsset(const FString& Hash, const FSoftObjectPath& AssetPath, const UObject* Referencer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Adds an existing asset to the cache attached to a particular hash, and optionally registering a referencer
- L153 _public prototype_ `FSoftObjectPath StopTrackingAsset(const FString& Hash);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Removes all info about the asset associated with Hash from this cache, if there is any. Note: This will not delete the asset however: Only tracked, *unreferenced* assets can be deleted by the asset cache, and only when manually created by it or if flagged with SetAssetDeletable
- L162 _public prototype_ `UObject* GetCachedAsset(const FString& Hash) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the asset associated with a particular Hash, if any. Returns nullptr if there isn't any associated path to this Hash, or if the associated path doesn't resolve to an asset. WARNING: As this may try loading a package from disk, this can only be called from the game thread!
- L170 _public function_ `template<typename T> T* GetCachedAsset(const FString& Hash)` — Templated version of GetCachedAsset for convenience WARNING: As this may try loading a package from disk, this can only be called from the game thread!
- L180 _public prototype_ `FSoftObjectPath GetCachedAssetPath(const FString& Hash) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the internal FSoftObjectPath associated with Hash, without trying to load the asset. If there is no asset associated with Hash, will return an invalid (empty) FSoftObjectPath.
- L187 _public prototype_ `FString GetHashForAsset(const FSoftObjectPath& AssetPath) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the hash associated with a particular asset, or the empty string if there isn't any. Note: The asset cache keeps internal reverse maps, so this should be O(1)
- L193 _public prototype_ `bool IsAssetTrackedByCache(const FSoftObjectPath& AssetPath) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns true if this asset is currently tracked by the asset cache's main hash to asset maps
- L199 _public prototype_ `int32 GetNumAssets() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns the total number of cached asset paths, whether these resolve to assets or not
- L205 _public prototype_ `TMap<FString, FSoftObjectPath> GetAllTrackedAssets() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns a copy of the internal mapping between hashes and asset paths
- L214 _public prototype_ `TMap<FString, UObject*> LoadAndGetAllTrackedAssets() const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — The same as GetAllTrackedAssets, except that it will automatically try loading all the asset paths before returning, which should be convenient for Python or Blueprint callers. WARNING: As this may try loading a package from disk, this can only be called from the game thread!
- L221 _public prototype_ `bool AddAssetReferencer(const UObject* Asset, const UObject* Referencer);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (CallInEditor = "true"))` — Adds a new UObject referencer to a particular asset, returning true if the operation succeeded. Assets will not be deleted or untracked by the asset cache while the referencer is registered.
- L228 _public prototype_ `bool RemoveAssetReferencer(const UObject* Asset, const UObject* Referencer);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Removes an UObject referencer from a particular asset, returning true if anything was removed. Will do nothing in case Asset or Referencer are invalid.
- L235 _public prototype_ `bool RemoveAllReferencersForAsset(const UObject* Asset);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Removes all UObject referencers from a particular asset, returning true if anything was removed. Will do nothing in case Asset is invalid.
- L242 _public prototype_ `bool RemoveAllReferencerAssets(const UObject* Referencer);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Removes a particular UObject referencer from all tracked assets, returning true if anything was removed. Will do nothing in case Referencer is invalid.
- L248 _public prototype_ `bool RemoveAllAssetReferencers();` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Removes all UObject referencer from all tracked assets, returning true if anything was removed.
- L257 _public prototype_ `void SetAssetDeletable(const UObject* Asset, bool bIsDeletable);` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Sets a particular asset as deletable or not. Assets not flagged as deletable will never be deleted by the asset cache when DeleteUnreferencedAssets is called. Assets the cache creates itself via GetOrCreateCachedAsset or GetOrCreateCustomCachedAsset are automatically set as deletable.
- L261 _public prototype_ `bool IsAssetDeletable(const UObject* Asset) const;` — `UFUNCTION(BlueprintCallable, Category = "USD", meta = (CallInEditor = "true"))` — Returns whether a particular asset is currently marked as deletable or not
- L277 _public prototype_ `void DeleteUnreferencedAssets(const bool bShowConfirmation = false);` — `UFUNCTION(BlueprintCallable, Category = "Cleanup", meta = (CallInEditor = "true"))` — Deletes all assets that: - Are currently tracked by the asset cache; - Are set as deletable; - Are not used by other UObjects (by external assets, components, undo buffer, Python scripting variables, etc.). - Have no referencers; - Have not been saved to disk; If bShowConfirmation is true, this will fallback to using engine code for deleting the assets, showing a confirmation dialog listing the assets that will be deleted. If false, it will silently try deleting the assets it can. WARNING: This will clear the undo buffer (i.e. transaction history) and run garbage collection after deleting.
- L287 _public prototype_ `void DeleteUnreferencedAssetsWithConfirmation();` — `UFUNCTION(BlueprintCallable, Category = "Cleanup", meta = (CallInEditor = "true", DisplayName = "Delete Unreferenced Assets"))` — This is the same as calling DeleteUnreferencedAssets and providing true for bShowConfirmation. It is just exposed in this manner so we automatically get a button for calling this function on details panels of the asset cache. WARNING: This will clear the undo buffer (i.e. transaction history) and run garbage collection after deleting.
- L297 _public prototype_ `void RescanAssetDirectory();` — `UFUNCTION(BlueprintCallable, Category = "Storage", meta = (CallInEditor = "true"))` — Checks the current AssetDirectory for any new assets that were generated from USD, and automatically caches them if possible. Note: This will never overwrite any existing information on the asset cache (i.e. if the newly found asset is associated with a hash that is already in use, it will be ignored)
- L329 _public prototype_ `UUsdAssetCache3();`
- L331 _public prototype_ `virtual void PostLoad() override;`
- L332 _public prototype_ `virtual void BeginDestroy() override;`
- L333 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L335 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L338 _public prototype_ `void OnRegistryAssetRenamed(const FAssetData& NewAssetData, const FString& OldName);`
- L340 _public prototype_ `void RequestDelayedAssetAutoCleanup();`
- L341 _public prototype_ `void TouchAsset(const FString& Hash, const UObject* Referencer = nullptr);`
- L342 _public prototype_ `void TouchAssetPath(const FSoftObjectPath& AssetPath, const UObject* Referencer = nullptr);`
- L343 _public prototype_ `void MarkAssetsAsStale();`
- L344 _public prototype_ `TSet<FSoftObjectPath> GetActiveAssets() const;`
- L345 _public prototype_ `const UObject* SetCurrentScopedReferencer(const UObject* NewReferencer);`
- L355 _public member_ `FDirectoryPath AssetDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage", meta = (ContentDir, NoResetToDefault))` — Content directory where the asset cache will place newly created assets. Changing this directory to a new location will automatically try to cache any existing assets on that location, if they were generated from USD.
- L365 _public member_ `bool bOnlyHandleAssetsWithinAssetDirectory = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage")` — When true, it means the asset cache will only ever return assets that are currently inside of the AssetDirectory folder. Move the assets out of the folder or change the folder and the asset cache will act as if these assets don't exist, potentially even losing track of them. When false, it means the asset cache will fully track and use its provided assets wherever they are in the content browser.
- L376 _public member_ `TMap<FString, FSoftObjectPath> HashToAssetPaths;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage")` — This is the main internal property that maps hashes to asset paths. Add entries to this property (or modify existing entries) and they will be returned by the asset cache whenever that hash is queried. WARNING: Asset modifications are not currently tracked! Change a static mesh's vertex color from red to green, and it will show the green cube when opening a stage with this asset cache, even if you open stages where the prim contains red as its vertex color.
- L392 _public member_ `bool bCleanUpUnreferencedAssets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cleanup")` — If this is true, every time a UsdStageActor using this asset cache closes a stage or swaps asset caches it will attempt to call DeleteUnreferencedAssets, potentially dropping *any* unreferenced asset, due to this operation or previous ones. Enable this if you want your AssetDirectory folder to be automatically cleaned up as stages close, and don't plan on keeping other external references to those assets. Note: Some asset types may have complicated setups, and may end up with references from other properties, actors and components for some time (e.g. due to a component in a transient package or undo/redo buffer). This means any automatically cleanup may not manage to clean up *all* untracked assets. Subsequent cleanups should eventually collect all assets, however. WARNING: This will clear the undo buffer (i.e. transaction history) and run garbage collection after any cleanup operation!
- L395 _protected prototype_ `void AddReferenceInternal(const FString& Hash, const UObject* Referencer);`
- L396 _protected prototype_ `FSoftObjectPath StopTrackingAssetInternal(const FString& Hash);`
- L397 _protected prototype_ `bool RemoveAllAssetReferencersInternal(const FString& Hash);`
- L398 _protected prototype_ `void TouchAssetInternal(const FSoftObjectPath& AssetPath, const UObject* Referencer = nullptr);`
- L399 _protected prototype_ `void TryCachingAssetFromAssetUserData(const FAssetData& NewAssetData);`
- L400 _protected prototype_ `bool IsTransientCache();`
- L401 _protected prototype_ `void ForceValidAssetDirectoryInternal(bool bEmitWarning = true);`
- L406 _private member_ `TMap<FSoftObjectPath, FString> AssetPathToHashes;` — `UPROPERTY()` — Reverse map, to speed up queries like GetHashForAsset and IsAssetTrackedByCache. Should always match HashToAssetPaths
- L412 _private member_ `TMap<FString, TObjectPtr<UObject>> TransientObjectStorage;` — `UPROPERTY(Transient)` — If we're a transient asset cache, our assets will be placed on the transient package and there wouldn't necessarily be anything holding a strong reference to them. This member is used for that. This is useful during direct import for example, where a rogue GC call could otherwise cause our transient assets to be collected, if it happened at a bad time
- L414 _private member_ `TMap<FString, TArray<FObjectKey>> HashToReferencer;`
- L415 _private member_ `TMap<FObjectKey, TArray<FString>> ReferencerToHash;`
- L416 _private member_ `TSet<FObjectKey> DeletableAssetKeys;`
- L419 _private member_ `const UObject* CurrentScopedReferencer = nullptr;` — When this is set to something, we will automatically flag it as a referencer of any cached/touched asset
- L421 _private member_ `bool bPendingCleanup = false;`
- L422 _private member_ `mutable FRWLock RWLock;`
- L428 _private member_ `mutable TSet<FSoftObjectPath> ActiveAssets;` — This member is mostly used by the UsdStageImporter: Assets are added to it whenever they are cached or fetched, and reset by calling MarkAssetsAsStale(). The idea is that by resetting before the import, and then calling GetActiveAssets() after the stage has been parsed, the importer can easily see which of the assets tracked by the asset cache are actually used by the stage it is about to import, and then publish exactly those.

#### struct `UUsdAssetCache3::FUsdScopedReferencer`  
`struct FUsdScopedReferencer`  
_L311-326_
- desc: The UUsdAssetCache3 can track all the UObjects that are referencing assets, so that it knows when to discard an unreferenced asset. This struct lets you specify a single UObject that will be automatically used as the referencer for the given asset cache for the duration of the scope. Usage: FUsdScopedReferencer ScopedReferencer{ StageActor->UsdAssetCache, StageActor }; StageActor->SetRootLayer(MyRootLayer);  // Adds assets to the cache
- L314 _public prototype_ `explicit FUsdScopedReferencer(UUsdAssetCache3* InAssetCache, const UObject* Referencer);`
- L315 _public prototype_ `~FUsdScopedReferencer();`
- L317 _public prototype_ `FUsdScopedReferencer() = delete;`
- L318 _public prototype_ `FUsdScopedReferencer(const FUsdScopedReferencer&) = delete;`
- L319 _public prototype_ `FUsdScopedReferencer(FUsdScopedReferencer&&) = delete;`
- L320 _public prototype_ `FUsdScopedReferencer& operator=(const FUsdScopedReferencer&) = delete;`
- L321 _public prototype_ `FUsdScopedReferencer& operator=(FUsdScopedReferencer&&) = delete;`
- L324 _private member_ `TWeakObjectPtr<UUsdAssetCache3> AssetCache;`
- L325 _private member_ `const UObject* OldReferencer = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDCLASSES_API`

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDAssetImportData.h` (Public)


#### class `UUsdAssetImportData`  
`class UUsdAssetImportData : public UAssetImportData`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- L19 _public member_ `FString PrimPath_DEPRECATED;` — `UE_DEPRECATED(all, "Use USD AssetUserData instead of AssetImportData for USD-specific info")` — `UPROPERTY()`
- L24 _public member_ `TObjectPtr<class UObject> ImportOptions;` — `UPROPERTY()` — Likely a UUSDStageImportOptions, but we don't declare it here to prevent an unnecessary module dependency on USDStageImporter

#### class `UUsdAnimSequenceAssetImportData`  
`class UE_DEPRECATED(all, "Use USD AssetUserData instead of AssetImportData for USD-specific info") UUsdAnimSequenceAssetImportData : public UUsdAssetImportData`  
_L29-37_
- reflection: `UCLASS()`
- inherits: `UUsdAssetImportData`
- L36 _public member_ `float LayerStartOffsetSeconds = 0.0f;` — `UPROPERTY()`

#### class `UUsdMeshAssetImportData`  
`class UE_DEPRECATED(all, "Use USD AssetUserData instead of AssetImportData for USD-specific info") UUsdMeshAssetImportData : public UUsdAssetImportData`  
_L40-48_
- reflection: `UCLASS()`
- inherits: `UUsdAssetImportData`
- L47 _public member_ `TMap<int32, FUsdPrimPathList> MaterialSlotToPrimPaths;` — `UPROPERTY()`

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDAssetUserData.h` (Public)


#### class `UUsdAssetUserData`  
`class UUsdAssetUserData : public UAssetUserData`  
_L12-31_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAssetUserData`
- L19 _public member_ `TArray<FString> PrimPaths;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Paths to prims that generated the asset that owns this AssetUserData
- L26 _public member_ `TMap<FString, FUsdCombinedPrimMetadata> StageIdentifierToMetadata;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Holds metadata collected for this asset, from all relevant Source prims. The asset that owns this user data may be shared via the asset cache, and reused for even entirely different stages. This map lets us keep track of which stage owns which bits of metadata
- L30 _public member_ `FString OriginalHash;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USD")` — Hash of the prim data that was used to generate this asset

#### class `UUsdAnimSequenceAssetUserData`  
`class UUsdAnimSequenceAssetUserData : public UUsdAssetUserData`  
_L34-63_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUsdAssetUserData`
- L50 _public member_ `float StageStartOffsetSeconds = 0.0f;` — `UPROPERTY()` — Offset into the stage in seconds to when this AnimSequence should start playing to match the skeletal animation in that stage. This is required because UAnimSequences just range from the first skeletal timeSample to the last, and the first sample is not necessarily the startTimeCode for the stage. Note that this is wrt. the startTimeCode of the *stage*, and not the individual layer. This is used for animating USkeletalMeshComponents via the AUsdStageActor and building the LevelSequences, and it is in seconds since it will need to drive the UAnimSequence with a time value in the [0, LengthSeconds] range. This should be applied *after* any offset/scale conversions on the time coordinate.
- L58 _public member_ `float StageScaleSeconds = 1.0f;` — `UPROPERTY()` — Total scale difference (as in, "MapToRoot") between the baked AnimSequence playback speed and the stage playback speed. E.g. If we have root.usda referencing ref1.usda with scale 2.0, and ref1.usda has sublayer animseq.usda with scale 3.0 (where the SkelAnimation prim is authored), then this property will hold 6.0
- L62 _public member_ `float LayerStartOffsetSeconds = 0.0f;` — `UE_DEPRECATED(5.7, "Use StageStartOffsetSeconds instead.")` — `UPROPERTY()`

#### struct `FUsdPrimPathList`  
`struct FUsdPrimPathList`  
_L67-73_
- reflection: `USTRUCT(BlueprintType)`
- desc: Simple wrapper because we're not allowed to have TMap properties with TArray<FString> as values
- L72 _public member_ `TArray<FString> PrimPaths;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`

#### class `UUsdMaterialAssetUserData`  
`class UUsdMaterialAssetUserData : public UUsdAssetUserData`  
_L77-101_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUsdAssetUserData`
- desc: AssetImportData assigned to Unreal materials that are generated when parsing USD Material prims
- L88 _public member_ `TMap<FString, FString> ParameterToPrimvar;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — In the context of our reference materials that just read a single texture for each material parameter, this describes the primvar that the USD material is sampling for each texture. e.g. {'BaseColor': 'st0', 'Metallic': 'st1'}
- L100 _public member_ `TMap<FString, int32> PrimvarToUVIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — In the context of our reference materials that just read a single texture for each material parameter, this describes the Unreal UV index that will be used for sampling by each USD primvar. The idea is to use this in combination with ParameterToPrimvar, in order to describe which UV index the material has currently assigned to each parameter. When assigning the material to meshes later, we'll compare this member with the UUsdMeshAssetImportData's own PrimvarToUVIndex to see if they are compatible or not, and if not spawn a new material instance that is. e.g. {'firstPrimvar': 0, 'st': 1, 'st1': 2}

#### class `UUsdMeshAssetUserData`  
`class UUsdMeshAssetUserData : public UUsdAssetUserData`  
_L105-121_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUsdAssetUserData`
- desc: We assign these to UStaticMeshes or USkeletalMeshes generated from USD
- L116 _public member_ `TMap<int32, FUsdPrimPathList> MaterialSlotToPrimPaths;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Maps from a material slot index of an UStaticMesh or USkeletalMesh to a list of source prims that contain this assignment. It can contain multiple prims in case we combine material slots and/or collapse prims (e.g. {0: ['/Root/mesh', '/Root/othermesh/geomsubset0', '/Root/othermesh/geomsubset1'] }).
- L120 _public member_ `TMap<FString, int32> PrimvarToUVIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Describes which primvars should be assigned to each UV index.

#### class `UUsdGeometryCacheAssetUserData`  
`class UUsdGeometryCacheAssetUserData : public UUsdMeshAssetUserData`  
_L125-137_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUsdMeshAssetUserData`
- desc: We assign these to UGeometryCaches generated from USD
- L132 _public member_ `float StageStartOffsetSeconds = 0.0f;` — `UPROPERTY()` — Check analogous comment on UUsdAnimSequenceAssetUserData
- L136 _public member_ `float LayerStartOffsetSeconds = 0.0f;` — `UE_DEPRECATED(5.7, "Use StageStartOffsetSeconds instead.")` — `UPROPERTY()`

#### class `UUsdLevelSequenceAssetUserData`  
`UUsdLevelSequenceAssetUserData : public UAssetUserData`  
_L141-151_
- reflection: `UCLASS(BlueprintType)`
- reflection: `UE_DEPRECATED(all, "This class is no longer used, as AUsdStageActors now use Sequencer Universal Object Locators for persistent bindings")`
- inherits: `UAssetUserData`
- L147 _public member_ `FGuid LastCheckedSignature;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`
- L150 _public member_ `TSet<FGuid> HandledBindingGuids;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`

#### class `UUsdSparseVolumeTextureAssetUserData`  
`class UUsdSparseVolumeTextureAssetUserData : public UUsdAssetUserData`  
_L157-184_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUsdAssetUserData`
- desc: We use this mainly to help in mapping between stage timeCode and the FrameIndex for animated SVTs
- L164 _public member_ `TArray<FString> SourceOpenVDBAssetPrimPaths;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Paths to all the OpenVDBAsset prims that led to the generation of this SVT asset
- L168 _public member_ `TArray<double> TimeSamplePathTimeCodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — TimeCodes of all the filePath attribute time samples as seen on the OpenVDBAsset prim in its own layer, in order
- L176 _public member_ `TArray<int32> TimeSamplePathIndices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — Corresponding indices of the frame of the SVT that should be played at a particular timeCode. Example: TimeSamplePathTimeCodes is [10, 20] and TimeSamplePathIndices is [2, 7] --> At timeCode 10 the frame index 2 of the SVT should be played, i.e. the .vdb file that is the third entry within TimeSamplePaths
- L183 _public member_ `TArray<FString> TimeSamplePaths;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — File paths that originated each of the SVT frames, in order. The SVT should have as many frames as there are entries in this array.

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDClassesModule.h` (Public)


#### class `IUsdClassesModule`  
`class IUsdClassesModule : public IModuleInterface`  
_L15-66_
- inherits: `IModuleInterface`
- L19 _public prototype_ `static void UpdatePlugInfoFiles(const FString& PluginDirectory, const FString& TargetDllFolder);` — Updates all plugInfo.json to point their LibraryPaths to TargetDllFolder
- L30 _public prototype_ `static void SendAnalytics( TArray<FAnalyticsEventAttribute>&& InAttributes, const FString& EventName, bool bAutomated, double ElapsedSeconds, double NumberOfFrames, const FString& Extension );` — Sends analytics about a USD operation @param InAttributes - Additional analytics events attributes to send, along with new ones collected within this function @param EventName - Name of the analytics event (e.g. "Export.StaticMesh", so that the full event name is "Engine.Usage.USD.Export.StaticMesh") @param bAutomated - If the operation was automated (e.g. came from a Python script) @param ElapsedSeconds - How long the operation took in seconds @param NumberOfFrames - Number of time codes in the exported/imported/opened stage @param Extension - Extension of the main USD file opened/emitted/imported (e.g. "usda" or "usd")
- L38 _public prototype_ `static void SendAnalytics(TArray<FAnalyticsEventAttribute>&& InAttributes, const FString& EventName);`
- L40 _public prototype_ `static FString GetClassNameForAnalytics(const UObject* Object);`
- L42 _public prototype_ `static void AddAssetCountAttributes(const TSet<UObject*>& Assets, TArray<FAnalyticsEventAttribute>& InOutAttributes);`
- L44 _public prototype_ `static void BlockAnalyticsEvents();`
- L45 _public prototype_ `static void ResumeAnalyticsEvents();`
- L46 _public prototype_ `static const TMap<FString, TArray<FAnalyticsEventAttribute>>& GetAccumulatedAnalytics();`
- L53 _public prototype_ `static bool HashObjectPackage(const UObject* Object, FSHA1& HashToUpdate);` — Updates HashToUpdate with the Object's package's persistent guid, the corresponding file save date and time, and the number of times the package has been dirtied since last being saved. This can be used to track the version of exported assets and levels, to prevent unnecessary re-exports.
- L56 _public prototype_ `static UWorld* GetCurrentWorld(bool bEditorWorldsOnly = false);` — Returns a world that could be suitably described as "the current world". (e.g. when in PIE, the PIE world)
- L62 _public prototype_ `static TSet<UObject*> GetAssetDependencies(UObject* Asset);` — Returns the set of assets that this object depends on (e.g. when given a material, will return its textures. When given a mesh, will return materials, etc.)
- L65 _public prototype_ `static UUsdAssetCache3* GetAssetCacheForProject();` — Returns the default asset cache for the project or create a new one at the project root

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDDrawModeComponent.h` (Public)


#### enum `EUsdDrawMode`  
`enum class EUsdDrawMode : int32`  
_L15-27_
- reflection: `UENUM()`
- L17 _public enumerator_ `Origin`
- L18 _public enumerator_ `Bounds`
- L19 _public enumerator_ `Cards`
- L25 _public enumerator_ `Default UMETA(Hidden)` — For now we just hide these, so that the user can't pick them on the component details panel. This because we don't yet have a good way of having component changes trigger resyncs: OnObjectPropertyChanged is fired immediately for each property change, and resyncing right away may cause some trouble in case it deletes components (which it will in this case) and the previous callstack of the OnObjectPropertyChanged still wants to interact with the component, or fire OnObjectPropertyChanged for other properties, etc.
- L26 _public enumerator_ `Inherited UMETA(Hidden)`

#### enum `EUsdModelCardGeometry`  
`enum class EUsdModelCardGeometry : int32`  
_L31-36_
- reflection: `UENUM()`
- desc: When we're on EUsdDrawMode::Cards, describes how to draw our cards
- L33 _public enumerator_ `Cross`
- L34 _public enumerator_ `Box`
- L35 _public enumerator_ `FromTexture UMETA(Hidden)` — We don't really support this one, and will fallback to "Box"

#### enum `EUsdModelCardFace`  
`enum class EUsdModelCardFace : int32`  
_L39-48_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L41 _public enumerator_ `None = 0 UMETA(Hidden)`
- L42 _public enumerator_ `XPos = 1`
- L43 _public enumerator_ `YPos = 2`
- L44 _public enumerator_ `ZPos = 4`
- L45 _public enumerator_ `XNeg = 8`
- L46 _public enumerator_ `YNeg = 16`
- L47 _public enumerator_ `ZNeg = 32`

#### class `UUsdDrawModeComponent`  
`class UUsdDrawModeComponent : public UPrimitiveComponent`  
_L61-175_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (USD), meta = (BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- desc: Component type that is used to draw bounds, cards and origin axes when translating a prim that has the UsdGeomModelAPI schema applied.
- L68 _public member_ `FVector BoundsMin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetBoundsMin, Category = "USD")` — Separate vectors instead of an FBox so we can get Sequencer tracks for these as is
- L71 _public member_ `FVector BoundsMax;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetBoundsMax, Category = "USD")`
- L74 _public member_ `EUsdDrawMode DrawMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDrawMode, Category = "USD")`
- L77 _public member_ `FLinearColor BoundsColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetBoundsColor, Category = "USD")`
- L80 _public member_ `EUsdModelCardGeometry CardGeometry;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardGeometry, Category = "USD|Cards")`
- L83 _public member_ `TObjectPtr<UTexture2D> CardTextureXPos;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardTextureXPos, Category = "USD|Cards")`
- L86 _public member_ `TObjectPtr<UTexture2D> CardTextureYPos;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardTextureYPos, Category = "USD|Cards")`
- L89 _public member_ `TObjectPtr<UTexture2D> CardTextureZPos;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardTextureZPos, Category = "USD|Cards")`
- L92 _public member_ `TObjectPtr<UTexture2D> CardTextureXNeg;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardTextureXNeg, Category = "USD|Cards")`
- L95 _public member_ `TObjectPtr<UTexture2D> CardTextureYNeg;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardTextureYNeg, Category = "USD|Cards")`
- L98 _public member_ `TObjectPtr<UTexture2D> CardTextureZNeg;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCardTextureZNeg, Category = "USD|Cards")`
- L102 _private member_ `TArray<TObjectPtr<UMaterialInstance>> MaterialInstances;` — `UPROPERTY()`
- L113 _private member_ `int32 AuthoredFaces;` — `UPROPERTY()` — EUsdModelCardFace flags to enable the card faces to draw. We need these because the required USD behavior specifies a difference between not having a texture because one wasn't authored (at which point we flip the opposite face), and not having a texture because it failed to resolve (at which point we draw vertex color). In both of those cases we'll end up with nullptr on the CardTexture property, but this will help us tell which case we're talking about. Note that this must be an int32 instead of the actual EUsdModelCardFace type because otherwise during any transaction the UPROPERTY Enum code will freak out if we have more than one flag set, presumably consider the combination of flags an invalid value for the enum, and then just set it to zero instead (see UE-200646).
- L117 _public prototype_ `void SetBoundsMin(const FVector& NewMin);` — `UFUNCTION(BlueprintSetter, Category = "USD")`
- L120 _public prototype_ `void SetBoundsMax(const FVector& NewMax);` — `UFUNCTION(BlueprintSetter, Category = "USD")`
- L123 _public prototype_ `void SetDrawMode(EUsdDrawMode NewDrawMode);` — `UFUNCTION(BlueprintSetter, Category = "USD")`
- L126 _public prototype_ `void SetBoundsColor(FLinearColor NewColor);` — `UFUNCTION(BlueprintSetter, Category = "USD")`
- L129 _public prototype_ `void SetCardGeometry(EUsdModelCardGeometry NewGeometry);` — `UFUNCTION(BlueprintSetter, Category = "USD")`
- L132 _public prototype_ `void SetCardTextureXPos(UTexture2D* NewTexture);` — `UFUNCTION(BlueprintSetter, Category = "USD|Cards")`
- L135 _public prototype_ `void SetCardTextureYPos(UTexture2D* NewTexture);` — `UFUNCTION(BlueprintSetter, Category = "USD|Cards")`
- L138 _public prototype_ `void SetCardTextureZPos(UTexture2D* NewTexture);` — `UFUNCTION(BlueprintSetter, Category = "USD|Cards")`
- L141 _public prototype_ `void SetCardTextureXNeg(UTexture2D* NewTexture);` — `UFUNCTION(BlueprintSetter, Category = "USD|Cards")`
- L144 _public prototype_ `void SetCardTextureYNeg(UTexture2D* NewTexture);` — `UFUNCTION(BlueprintSetter, Category = "USD|Cards")`
- L147 _public prototype_ `void SetCardTextureZNeg(UTexture2D* NewTexture);` — `UFUNCTION(BlueprintSetter, Category = "USD|Cards")`
- L150 _public prototype_ `UTexture2D* GetTextureForFace(EUsdModelCardFace Face) const;` — `UFUNCTION(BlueprintPure, Category = "USD|Cards")`
- L153 _public prototype_ `void SetTextureForFace(EUsdModelCardFace Face, UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "USD|Cards")`
- L156 _public prototype_ `UUsdDrawModeComponent();`
- L157 _public prototype_ `virtual ~UUsdDrawModeComponent() override= default;`
- L160 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L161 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L162 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L164 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L165 _public prototype_ `virtual HHitProxy* CreateMeshHitProxy(int32 SectionIndex, int32 MaterialIndex) const override;`
- L169 _public prototype_ `EUsdModelCardFace GetAuthoredFaces() const;`
- L170 _public prototype_ `void SetAuthoredFaces(EUsdModelCardFace NewAuthoredFaces);`
- L173 _private prototype_ `UMaterialInstance* GetOrCreateTextureMaterial(EUsdModelCardFace Face);`
- L174 _private prototype_ `void RefreshMaterialInstances();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDCLASSES_API`
- L49 _prototype_ `ENUM_CLASS_FLAGS(EUsdModelCardFace);`
- L51 _namespace_ `namespace UsdUtils`
- L53 _prototype_ `EUsdModelCardFace GetOppositeFaceOnSameAxis(EUsdModelCardFace Face);` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDDuplicateType.h` (Public)


#### enum `EUsdDuplicateType`  
`enum class EUsdDuplicateType : uint8`  
_L11-19_
- reflection: `UENUM(BlueprintType)`
- desc: Describes the different types of "prim duplication" operations we support with UsdUtils::DuplicatePrims
- L14 _public enumerator_ `FlattenComposedPrim` — Generate a flattened duplicate of the composed prim onto the current edit target
- L16 _public enumerator_ `SingleLayerSpecs` — Duplicate the prim's specs on the current edit target only
- L18 _public enumerator_ `AllLocalLayerSpecs` — Duplicate each of the prim's specs across the entire stage

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUsd, Log, All);`

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDMaterialUtils.h` (Public)


#### enum `EUsdReferenceMaterialProperties`  
`enum class EUsdReferenceMaterialProperties : uint8`  
_L12-18_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Translucent = 1`
- L16 _public enumerator_ `VT = 2`
- L17 _public enumerator_ `TwoSided = 4`

#### struct `UsdUnreal::MaterialUtils::FDisplayColorMaterial`  
`struct FDisplayColorMaterial`  
_L24-32_
- desc: Describes the type of vertex color/DisplayColor material that we would need in order to render a prim's displayColor data as intended
- L26 _public member_ `bool bHasOpacity = false;`
- L27 _public member_ `bool bIsDoubleSided = false;`
- L29 _public prototype_ `FString ToString() const;`
- L30 _public prototype_ `FString ToPrettyString() const;`
- L31 _public prototype_ `static TOptional<FDisplayColorMaterial> FromString(const FString& DisplayColorString);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDCLASSES_API`
- L21 _namespace_ `namespace UsdUnreal`
- L21 _namespace_ `namespace MaterialUtils` (scope `UsdUnreal`)
- L34 _prototype_ `const FSoftObjectPath* GetReferenceMaterialPath(const FDisplayColorMaterial& DisplayColorDescription);` (scope `UsdUnreal::MaterialUtils`)
- L36 _prototype_ `UMaterialInstanceDynamic* CreateDisplayColorMaterialInstanceDynamic(const FDisplayColorMaterial& DisplayColorDescription);` (scope `UsdUnreal::MaterialUtils`)
- L37 _prototype_ `UMaterialInstanceConstant* CreateDisplayColorMaterialInstanceConstant(const FDisplayColorMaterial& DisplayColorDescription);` (scope `UsdUnreal::MaterialUtils`)
- L41 _prototype_ `FSoftObjectPath GetReferencePreviewSurfaceMaterial(EUsdReferenceMaterialProperties ReferenceMaterialProperties);` (scope `UsdUnreal::MaterialUtils`) — Returns one of the alternatives of the UsdPreviewSurface reference material depending on the material overrides provided, and nullptr otherwise
- L49 _prototype_ `FSoftObjectPath GetVTVersionOfReferencePreviewSurfaceMaterial(const FSoftObjectPath& ReferenceMaterial);` (scope `UsdUnreal::MaterialUtils`) — Returns the VT version of the provided UsdPreviewSurface ReferenceMaterial. Returns the provided ReferenceMaterial back if it is already a VT-capable reference material, and returns nullptr if ReferenceMaterial isn't one of our reference material alternatives. Example: Receives UsdPreviewSurfaceTwoSided -> Returns UsdPreviewSurfaceTwoSidedVT Example: Receives UsdPreviewSurfaceTwoSidedVT -> Returns UsdPreviewSurfaceTwoSidedVT Example: Receives SomeOtherReferenceMaterial -> Returns nullptr
- L57 _prototype_ `FSoftObjectPath GetTwoSidedVersionOfReferencePreviewSurfaceMaterial(const FSoftObjectPath& ReferenceMaterial);` (scope `UsdUnreal::MaterialUtils`) — Returns the two-sided version of the provided UsdPreviewSurface ReferenceMaterial. Returns the provided ReferenceMaterial back if it is already a two-sided-capable reference material, and returns nullptr if ReferenceMaterial isn't one of our reference material alternatives. Example: Receives UsdPreviewSurfaceTranslucent -> Returns UsdPreviewSurfaceTwoSidedTranslucent Example: Receives UsdPreviewSurfaceTwoSidedTranslucent -> Returns UsdPreviewSurfaceTwoSidedTranslucent Example: Receives SomeOtherReferenceMaterial -> Returns nullptr
- L61 _prototype_ `bool IsReferencePreviewSurfaceMaterial(const FSoftObjectPath& ReferenceMaterial);` (scope `UsdUnreal::MaterialUtils`) — Returns whether the Material is one of the UsdPreviewSurface reference materials (which can be reassigned by the user on a per project basis)
- L63 _prototype_ `void RegisterRenderContext(const FName& RenderContextName);` (scope `UsdUnreal::MaterialUtils`)
- L64 _prototype_ `void UnregisterRenderContext(const FName& RenderContextName);` (scope `UsdUnreal::MaterialUtils`)
- L65 _prototype_ `const TArray<FName>& GetRegisteredRenderContexts();` (scope `UsdUnreal::MaterialUtils`)

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDMetadata.h` (Public)


#### struct `FUsdMetadataValue`  
`struct FUsdMetadataValue`  
_L9-28_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a single metadata value collected from USD
- L19 _public member_ `FString TypeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — USD typename. Anything from the "Value type token" column on the Basic data types tables from https://openusd.org/release/api/_usd__page__datatypes.html is allowed, including the array types (e.g. "uchar", "timecode", "matrix3d[]" and "half[]"). Exceptions are the "opaque" typeName that we don't support, and the "SdfListOp<Token>" typeName, that we *do* support (it's the typeName for list-editable attributes like "apiSchemas")
- L27 _public member_ `FString StringifiedValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")` — A stringified value that should match the type in TypeName (e.g. "[(1.0, 1.0, 0.5), (1.0, 1.0, 0.5)]" if TypeName is "double3[]"). You can use the functions on UsdConversionLibrary (USDConversionLibrary.h) and UsdUtils namespace (USDValueConversion.h) to help stringify/unstringify these types according to USD rules, from C++, Blueprint and Python

#### struct `FUsdPrimMetadata`  
`struct FUsdPrimMetadata`  
_L32-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes all the metadata values collected from a particular USD prim
- L37 _public member_ `TMap<FString, FUsdMetadataValue> Metadata;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`

#### struct `FUsdCombinedPrimMetadata`  
`struct FUsdCombinedPrimMetadata`  
_L46-52_
- reflection: `USTRUCT(BlueprintType)`
- desc: Tracks metadata collected from multiple prim paths. This is useful because often multiple prims will be read to generate an asset, like when collapsing or collecting skinned Mesh prims for a SkeletalMesh. This may also be used if multiple prims within the same stage end up generating the same asset, which is shared via the asset cache: Both prims will store their metadata here.
- L51 _public member_ `TMap<FString, FUsdPrimMetadata> PrimPathToMetadata;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDMetadataImportOptions.h` (Public)


#### struct `FUsdMetadataImportOptions`  
`struct FUsdMetadataImportOptions`  
_L10-46_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `bool bCollectMetadata = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config)` — Whether to collect USD prim metadata into AssetUserData objects at all
- L21 _public member_ `bool bCollectFromEntireSubtrees = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config, meta = (EditCondition = bCollectMetadata))` — Whether to collect USD metadata from not only a particular prim, but its entire subtree, when apropriate. This is useful when used together with collapsing settings, for example.
- L31 _public member_ `bool bCollectOnComponents = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config, meta = (EditCondition = bCollectMetadata))` — We will always add the collected metadata to AssetUserData objects assigned to all generated assets that support them. When this option is enabled, however, we will also separately collect USD prim metadata and add that to AssetUserData objects added to every spawned *component*. This can be useful for tracking metadata on prims that don't usually generate assets, like simple Xforms, cameras, lights, etc., or for collecting metadata for prims with alternative draw modes enabled, like bounds or cards: We won't generate the usual assets for those, but the metadata could still be collected on the components with this option.
- L38 _public member_ `TArray<FString> BlockedPrefixFilters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config, meta = (EditCondition = bCollectMetadata))` — When collecting metadata, we will ignore all entries that start with these prefixes. Note that you can use the ":" separator for nested dictionaries, so for example using "customData:ign" to ignore anything within the "ignoredValues" dictionary inside the "customData" dictionary
- L45 _public member_ `bool bInvertFilters = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config, meta = (EditCondition = bCollectMetadata))` — When this is false (default), the "BlockedPrefixFilters" property describe prefixes to block, and metadata entries that match any of those prefixes are ignored and not collected. When this is true, the "BlockedPrefixFilters" property is inverted, and describes prefixes to *allow*. In that case, entries are only allowed and collected if they match at least one of the provided prefixes.

#### Free symbols / members of external scopes

- L48 _namespace_ `namespace UsdUtils`
- L50 _prototype_ `void AddAnalyticsAttributes(const FUsdMetadataImportOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L51 _prototype_ `void HashForImport(const FUsdMetadataImportOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDObjectUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UsdUnreal`
- L13 _namespace_ `namespace ObjectUtils` (scope `UsdUnreal`)
- L21 _prototype_ `UAssetImportData* GetBaseAssetImportData(UObject* Asset);` (scope `UsdUnreal::ObjectUtils`) — Utilities to allow getting and setting our AssetImportData to an asset from a base UObject*. Note that not all asset types support AssetImportData, and in some cases when retrieving it for e.g. a Skeleton, we'll actually check it's preview mesh instead (since Skeletons don't have AssetImportData). The setter won't do anything if you try setting asset import data on e.g. a Skeleton, on the other hand.
- L22 _prototype_ `UUsdAssetImportData* GetAssetImportData(UObject* Asset);` (scope `UsdUnreal::ObjectUtils`)
- L23 _prototype_ `void SetAssetImportData(UObject* Asset, UAssetImportData* ImportData);` (scope `UsdUnreal::ObjectUtils`)
- L28 _prototype_ `UUsdAssetUserData* GetAssetUserData(const UObject* Object, TSubclassOf<UUsdAssetUserData> Class = {});` (scope `UsdUnreal::ObjectUtils`) — Returns the object's UsdAssetUserData of a particular subclass if it has one
- L31 _function_ `template<typename T> inline T* GetAssetUserData(UObject* Object)` (scope `UsdUnreal::ObjectUtils`)
- L39 _prototype_ `UUsdAssetUserData* GetOrCreateAssetUserData(UObject* Object, TSubclassOf<UUsdAssetUserData> Class = {});` (scope `UsdUnreal::ObjectUtils`) — Makes sure Object has an instance of UUsdAssetUserData of the provided subclass (defaulting to just UUsdAssetUserData itself) and returns it
- L42 _function_ `template<typename T> inline T* GetOrCreateAssetUserData(UObject* Object)` (scope `UsdUnreal::ObjectUtils`)
- L50 _prototype_ `bool SetAssetUserData(UObject* Object, UUsdAssetUserData* AssetUserData);` (scope `UsdUnreal::ObjectUtils`) — Removes all other UUsdAssetUserData instances from Object if they exist, then sets AssetUserData as Object's single UUsdAssetUserData
- L56 _prototype_ `TSubclassOf<UUsdAssetUserData> GetAssetUserDataClassForObject(UClass* ObjectClass);` (scope `UsdUnreal::ObjectUtils`) — Returns the ideal class of AssetUserData to use for a particular asset type (e.g. UStaticMesh::StaticClass() --> UUsdMeshAssetUserData::StaticClass())
- L59 _prototype_ `FString SanitizeObjectName(const FString& InObjectName);` (scope `UsdUnreal::ObjectUtils`) — Adapted from ObjectTools as it is within an Editor-only module
- L61 _prototype_ `FString GetPrefixedAssetName(const FString& DesiredName, UClass* AssetClass);` (scope `UsdUnreal::ObjectUtils`)
- L67 _prototype_ `bool RemoveNumberedSuffix(FString& Prefix);` (scope `UsdUnreal::ObjectUtils`) — Removes any numbered suffix, followed by any number of underscores (e.g. Asset_2, Asset__232_31 or Asset94 all become 'Asset'), making sure the string is kept at least one character long. Returns true if it removed anything.
- L77 _function_ `template<typename StringContainer> inline FString GetUniqueName(FString Name, const StringContainer& UsedNames)` (scope `UsdUnreal::ObjectUtils`) — Appends numbered suffixes to Name until the result is not contained in UsedNames, and returns it. Does not add the result to UsedNames before returning (as it is const). @param Name - Received string to make unique (e.g. "MyName") @param UsedNames - Strings that cannot be used for the result. Should have a .Contains() function that receives FString @return Modified Name so that it doesn't match anything in UsedNames (e.g. "MyName" again, or "MyName_0" or "MyName_423")

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDProjectSettings.h` (Public)


#### enum `EUsdSaveDialogBehavior`  
`enum class EUsdSaveDialogBehavior : uint8`  
_L12-17_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `NeverSave`
- L15 _public enumerator_ `AlwaysSave`
- L16 _public enumerator_ `ShowPrompt`

#### enum `EUsdEditInInstanceBehavior`  
`enum class EUsdEditInInstanceBehavior : uint8`  
_L20-25_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Ignore`
- L23 _public enumerator_ `RemoveInstanceable`
- L24 _public enumerator_ `ShowPrompt`

#### enum `EReferencerTypeHandling`  
`enum class EReferencerTypeHandling : uint8`  
_L28-34_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `Ignore`
- L31 _public enumerator_ `MatchReferencedType`
- L32 _public enumerator_ `ClearReferencerType`
- L33 _public enumerator_ `ShowPrompt`

#### class `UUsdProjectSettings`  
`class UUsdProjectSettings : public UDeveloperSettings`  
_L61-325_
- reflection: `UCLASS(BlueprintType, config = USDCore, defaultconfig, meta = (DisplayName = USDCore), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L79 _public member_ `TArray<FDirectoryPath> AdditionalPluginDirectories;` — `UPROPERTY(config, EditAnywhere, Category = USD, meta = (RelativeToGameContentDir))` — Additional paths to check for USD plugins. If you want the USD plugins to be included in a packaged game, you must use a relative path to a location within your project directory, and you must also add that same path to the "Additional Non-Asset Directories To Copy" Project Packaging setting. For example, this relative path could be used to locate USD plugins in a directory at the root of your project: ../USD_Plugins The packaging process cannot use an absolute path and will raise an error if given one when it tries to concatenate the game content directory path with an absolute path.
- L91 _public member_ `TArray<FDirectoryPath> DefaultResolverSearchPath;` — `UPROPERTY(config, EditAnywhere, Category = USD, meta = (ConfigRestartRequired = true))` — The directories that will be used as the default search path by USD's default resolver during asset resolution. Each directory in the search path should be an absolute path. If it is not, it will be anchored to the current working directory. Note that the default search path must be set before the first invocation of USD's resolver system, so changing this setting will require a restart of the engine in order for the new setting to take effect.
- L95 _public member_ `TArray<FName> AdditionalMaterialPurposes;` — `UPROPERTY(config, EditAnywhere, Category = USD)` — Material purposes to show on drop-downs in addition to the standard "preview" and "full"
- L99 _public member_ `TArray<FString> AdditionalCustomSchemaNames;` — `UPROPERTY(config, EditAnywhere, Category = USD)` — apiSchema names to show on the "Add Schema" right-click option, in addition to the standard common schemas
- L103 _public member_ `bool bLogUsdSdkErrors = true;` — `UPROPERTY(config, EditAnywhere, Category = USD)` — Whether to show on the output log messages, warnings and errors reported directly by the USD SDK
- L107 _public member_ `bool bOptimizeUsdLog = true;` — `UPROPERTY(config, EditAnywhere, Category = USD)` — Similar messages are merged into one. Disable this option to see the individual messages (may slow performance and use more memory).
- L114 _public member_ `FSoftObjectPath DefaultAssetCache;` — `UPROPERTY(config, EditAnywhere, Category = USD, meta = (AllowedClasses = "/Script/USDClasses.UsdAssetCache3"))` — USD Asset Cache to use for USD Stage Actors that don't have any asset cache specified. Leave this empty to have each stage actor generate it's on transient cache instead.
- L117 _public member_ `bool bShowCreateDefaultAssetCacheDialog = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")`
- L120 _public member_ `bool bShowConfirmationWhenClearingLayers = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")`
- L123 _public member_ `bool bShowConfirmationWhenMutingDirtyLayers = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")`
- L126 _public member_ `bool bShowConfirmationWhenReloadingDirtyLayers = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")`
- L130 _public member_ `bool bShowOverriddenOpinionsWarning = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show the warning dialog when authoring opinions that could have no effect on the composed stage
- L134 _public member_ `EUsdEditInInstanceBehavior EditInInstanceableBehavior = EUsdEditInInstanceBehavior::ShowPrompt;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show the warning dialog when authoring opinions inside an instance or instance proxy
- L138 _public member_ `EReferencerTypeHandling ReferencerTypeHandling = EReferencerTypeHandling::ClearReferencerType;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — How to behave when authoring a reference or payload to a prim whose type name differs from the one of the referencer prim
- L143 _public member_ `bool bShowWarningOnIncompleteDuplication = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show a warning whenever the "Duplicate All Local Layer Specs" option is picked, and the duplicated prim has some specs outside the local layer stack that will not be duplicated.
- L147 _public member_ `bool bShowTransformOnCameraComponentWarning = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show the warning dialog when authoring a transforms directly to a camera component
- L151 _public member_ `bool bShowTransformTrackOnCameraComponentWarning = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show the warning dialog when authoring a transform track directly to a camera component
- L155 _public member_ `bool bShowSubsectionSnappingWarning = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show the warning dialog when snapping a subsequence section to the playback range
- L159 _public member_ `bool bShowInheritedVisibilityWarning = true;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to show the warning dialog when authoring new visibility tracks from Unreal
- L163 _public member_ `EUsdSaveDialogBehavior ShowSaveLayersDialogWhenSaving = EUsdSaveDialogBehavior::ShowPrompt;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to display the pop up dialog asking what to do about dirty USD layers when saving the UE level
- L167 _public member_ `EUsdSaveDialogBehavior ShowSaveLayersDialogWhenClosing = EUsdSaveDialogBehavior::ShowPrompt;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Dialogs")` — Whether to display the pop up dialog asking what to do about dirty USD layers when closing USD stages
- L200 _public member_ `FSoftObjectPath ReferencePreviewSurfaceMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L209 _public member_ `FSoftObjectPath ReferencePreviewSurfaceTranslucentMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceTranslucentMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L218 _public member_ `FSoftObjectPath ReferencePreviewSurfaceTwoSidedMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceTwoSidedMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L227 _public member_ `FSoftObjectPath ReferencePreviewSurfaceTranslucentTwoSidedMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceTranslucentTwoSidedMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L236 _public member_ `FSoftObjectPath ReferencePreviewSurfaceVTMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceVTMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface with Virtual Textures", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L245 _public member_ `FSoftObjectPath ReferencePreviewSurfaceTranslucentVTMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceTranslucentVTMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface with Virtual Textures", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L254 _public member_ `FSoftObjectPath ReferencePreviewSurfaceTwoSidedVTMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceTwoSidedVTMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface with Virtual Textures", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L263 _public member_ `FSoftObjectPath ReferencePreviewSurfaceTranslucentTwoSidedVTMaterial = UsdDefaultReferenceMaterialPaths::ReferencePreviewSurfaceTranslucentTwoSidedVTMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface with Virtual Textures", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L273 _public member_ `FSoftObjectPath ReferenceSubstratePreviewSurfaceMaterial = UsdDefaultReferenceMaterialPaths::ReferenceSubstratePreviewSurfaceMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. Exclusively used by USD imports via the Interchange framework, when Substrate is enabled for the project. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L283 _public member_ `FSoftObjectPath ReferenceSubstratePreviewSurfaceVTMaterial = UsdDefaultReferenceMaterialPaths::ReferenceSubstratePreviewSurfaceVTMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|UsdPreviewSurface", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. Exclusively used by USD imports via the Interchange framework, when Substrate is enabled for the project. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L292 _public member_ `FSoftObjectPath ReferenceDisplayColorMaterial = UsdDefaultReferenceMaterialPaths::ReferenceDisplayColorMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|DisplayColor", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L301 _public member_ `FSoftObjectPath ReferenceDisplayColorAndOpacityMaterial = UsdDefaultReferenceMaterialPaths::ReferenceDisplayColorAndOpacityMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|DisplayColor", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L310 _public member_ `FSoftObjectPath ReferenceDisplayColorTwoSidedMaterial = UsdDefaultReferenceMaterialPaths::ReferenceDisplayColorTwoSidedMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|DisplayColor", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L319 _public member_ `FSoftObjectPath ReferenceDisplayColorAndOpacityTwoSidedMaterial = UsdDefaultReferenceMaterialPaths::ReferenceDisplayColorAndOpacityTwoSidedMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "USD|Reference Materials|DisplayColor", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))` — What material to use as reference material when creating material instances from USD materials. You can swap these with your own materials, but make sure that the replacement materials have parameters with the same names and types as the ones provided by the default material, otherwise the instances will not have the parameters filled with values extracted from the USD material when parsing.
- L323 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UsdDefaultReferenceMaterialPaths`
- L39 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L40 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceTranslucentMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L41 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceTwoSidedMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L42 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceTranslucentTwoSidedMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L43 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceVTMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L44 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceTranslucentVTMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L45 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceTwoSidedVTMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L46 _variable_ `const inline FSoftObjectPath ReferencePreviewSurfaceTranslucentTwoSidedVTMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L48 _variable_ `const inline FSoftObjectPath ReferenceSubstratePreviewSurfaceMaterial{TEXT("/Int` (scope `UsdDefaultReferenceMaterialPaths`)
- L49 _variable_ `const inline FSoftObjectPath ReferenceSubstratePreviewSurfaceVTMaterial{TEXT("/Int` (scope `UsdDefaultReferenceMaterialPaths`)
- L51 _variable_ `const inline FSoftObjectPath ReferenceDisplayColorMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L52 _variable_ `const inline FSoftObjectPath ReferenceDisplayColorAndOpacityMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L53 _variable_ `const inline FSoftObjectPath ReferenceDisplayColorTwoSidedMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)
- L54 _variable_ `const inline FSoftObjectPath ReferenceDisplayColorAndOpacityTwoSidedMaterial{TEXT("/USD` (scope `UsdDefaultReferenceMaterialPaths`)

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDReferenceOptions.h` (Public)


#### class `UUsdReferenceOptions`  
`class UUsdReferenceOptions : public UObject`  
_L11-39_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: Options to display when adding a reference or a payload for a prim
- L18 _public member_ `bool bInternalReference = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")` — When enabled, the reference/payload will target a prim on this stage
- L22 _public member_ `FFilePath TargetFile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (EditCondition = "!bInternalReference", EditConditionHides))` — File to use as the reference
- L26 _public member_ `bool bUseDefaultPrim = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (EditCondition = "!bInternalReference", EditConditionHides))` — Use the default prim of the target stage as the referenced/payload prim
- L30 _public member_ `FString TargetPrimPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (EditCondition = "!bUseDefaultPrim || bInternalReference"))` — Use a specific prim of the target stage as the referenced/payload prim
- L34 _public member_ `float TimeCodeOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", AdvancedDisplay)` — Offset to apply to the referenced/payload prim's time sampled attributes
- L38 _public member_ `float TimeCodeScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", AdvancedDisplay)` — TimeCode scaling factor to apply to the referenced/payload prim's time sampled attributes

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDSetUtils.h` (Public)


#### struct `UsdUtils::FCaseSensitiveStringMapFuncs`  
`template<typename ValueType> struct FCaseSensitiveStringMapFuncs : BaseKeyFuncs<ValueType, FString, false>`  
_L12-28_
- inherits: `BaseKeyFuncs<ValueType,FString,false>`
- desc: Case sensitive hashing function for TMap
- L14 _public function_ `static FORCEINLINE const FString& GetSetKey(const TPair<FString, ValueType>& Element)`
- L19 _public function_ `static FORCEINLINE bool Matches(const FString& A, const FString& B)`
- L24 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& Key)`

#### struct `UsdUtils::FCaseSensitiveStringSetFuncs`  
`struct FCaseSensitiveStringSetFuncs : BaseKeyFuncs<FString, FString>`  
_L31-45_
- inherits: `BaseKeyFuncs<FString,FString>`
- desc: Case sensitive hashing function for TSet
- L33 _public function_ `static FORCEINLINE const FString& GetSetKey(const FString& Element)`
- L37 _public function_ `static FORCEINLINE bool Matches(const FString& A, const FString& B)`
- L41 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& Key)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UsdUtils`
- L48 _typedef_ `template<typename ValueType> using TCaseSensitiveStringMap = TMap<FString, ValueType, FDefaultSetAllocator, FCaseSensitiveStringMapFuncs<ValueType>>;` (scope `UsdUtils`)
- L50 _typedef_ `using FCaseSensitiveStringSet = TSet<FString, FCaseSensitiveStringSetFuncs>;` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDStageOptions.h` (Public)


#### enum `EUsdUpAxis`  
`enum class EUsdUpAxis : uint8`  
_L10-14_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `YAxis`
- L13 _public enumerator_ `ZAxis`

#### struct `FUsdStageOptions`  
`struct FUsdStageOptions`  
_L17-28_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `double MetersPerUnit = 0.01;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options")` — MetersPerUnit to use for the stage. Defaults to 0.01 (i.e. 1cm per unit, which equals UE units)
- L27 _public member_ `EUsdUpAxis UpAxis = EUsdUpAxis::ZAxis;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options")` — UpAxis to use for the stage. Defaults to ZAxis, which equals the UE convention

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UsdUtils`
- L32 _prototype_ `void AddAnalyticsAttributes(const FUsdStageOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L34 _prototype_ `void HashForExport(const FUsdStageOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDUnrealAssetInfo.h` (Public)


#### struct `FUsdUnrealAssetInfo`  
`struct FUsdUnrealAssetInfo`  
_L11-43_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metadata added to a prim to indicate it was exported from a particular Unreal asset
- L18 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — Name of the Unreal asset
- L22 _public member_ `FString Identifier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — Filepath to the layer where the asset was exported to
- L26 _public member_ `FString Version;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — Identifier string for the current asset version. Whenever the asset is updated inside Unreal, this will change
- L30 _public member_ `FString UnrealContentPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — Path to the exported asset (e.g. "/Game/MyMaterials/Red.Red")
- L34 _public member_ `FString UnrealAssetType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — Class name of the exported asset (e.g. "StaticMesh")
- L38 _public member_ `FString UnrealExportTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — DateTime string of the moment of export (e.g. "2022.06.17-14.19.54")
- L42 _public member_ `FString UnrealEngineVersion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")` — Engine version string describing the engine that exported this asset (e.g. "5.1.0-21000000+UE5")
