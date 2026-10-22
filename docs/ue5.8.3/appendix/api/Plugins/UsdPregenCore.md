# Plugins / UsdPregenCore

- module root: `Plugins/Experimental/USDPregen/Source/USDPregenCore`
- headers: 28; symbols: 683
- symbol kinds: class=29, enum=7, enumerator=21, externvar=13, function=5, macro=31, member=145, namespace=14, prototype=349, struct=17, typedef=51, variable=1
- PublicDependencyModuleNames: Core, UnrealUSDWrapper

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/debugCodes.h` (Private)


#### Free symbols / members of external scopes

- L16 _prototype_ `TF_DEBUG_CODES( PREGEN_ASSET, PREGEN_DISCOVERY, PREGEN_ITEM, PREGEN_MANIFEST, PREGEN_PERMUTATION, PREGEN_REGISTRY, PREGEN_TARGET, PREGEN_TRACKING );`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/debugMacros.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define DEBUG_ASSET(fmt, ...) \`
- L16 _macro_ `#define DEBUG_DISCOVERY(fmt, ...) \`
- L19 _macro_ `#define DEBUG_ITEM(fmt, ...) \`
- L22 _macro_ `#define DEBUG_MANIFEST(fmt, ...) \`
- L25 _macro_ `#define DEBUG_PERMUTATION(fmt, ...) \`
- L28 _macro_ `#define DEBUG_REGISTRY(fmt, ...) \`
- L31 _macro_ `#define DEBUG_TARGET(fmt, ...) \`
- L34 _macro_ `#define DEBUG_TRACKING(fmt, ...) \`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/item.h` (Private)


#### struct `internal::ScopeHandle`  
`struct ScopeHandle`  
_L51-54_
- L53 _public member_ `pxr::SdfPath id;`

#### class `internal::ItemScope`  
`class ItemScope`  
_L85-235_
- desc: Instances of ItemScope are owned by Item objects.
- L93 _public prototype_ `ItemScope(const ScopeHandle& handle, const pxr::SdfPath& path, const ItemScope* parent, const Item* owner);` — This scope corresponds to the prim that introduced the asset definition and represents the non-permutation scene description.
- L102 _public prototype_ `ItemScope(const ScopeHandle& handle, const pxr::SdfPath& path, const ItemScope* parent, const PrimPermutationRefPtr& perm, bool consumesDescendants);` — Permutation scopes represent additional composition contexts created by permutation operations (variants, inherits, etc.).
- L116 _public prototype_ `const pxr::SdfPath& GetPath() const &;` — Returns the scene path associated with this scope.
- L119 _public prototype_ `ScopeHandle GetHandle() const;` — Returns the Sdf spec handle representing the scope.
- L122 _public prototype_ `const ItemScope* GetParent() const;` — Returns the parent scope.
- L126 _public prototype_ `types::int32 GetConsumerDepth() const;` — Returns the depth of the ancestor asset that consumes descendant targets originating in this scope.
- L129 _public prototype_ `types::int32 GetOpinionDepth() const;` — Returns the minimum depth at which overriding opinions were found.
- L132 _public prototype_ `bool AddContent(const pxr::TfToken& category, const pxr::SdfPath& path);` — Add content for the given category and path.
- L136 _public prototype_ `bool HasContent() const;` — Returns true if this scope holds content or false if the scope is effectively a grouping of other scopes.
- L139 _public prototype_ `pxr::TfTokenVector GetContentCategoryNames() const;` — Get all the content category names registered on this scope.
- L142 _public prototype_ `CategoryView GetCategoryView(const pxr::TfToken& category) const;` — Get the count and (optional) paths for the given category.
- L147 _public prototype_ `bool AddOverridePathIfNeeded(const pxr::SdfPath& path, types::int32 depth);` — Add the given property as an override path - if the property at the given depth is less than the scopes depth, add the property path to the list of overrides for this scope.
- L150 _public prototype_ `pxr::TfSpan<const pxr::SdfPath> GetOverridePaths() const;` — Returns paths whose opinions override ancestor assets.
- L153 _public prototype_ `bool HasDependencies() const;` — Returns true if this scope has one or more dependencies.
- L156 _public prototype_ `bool AddDependency(const pxr::SdfPath& path);` — Add a dependency to this scope.
- L159 _public prototype_ `const pxr::SdfPathSet& GetDependencies() const &;` — Get all dependencies for this scope.
- L164 _public prototype_ `bool AddDescendantDefinitionScenePath(const pxr::SdfPath& path, bool isEncapsulated);` — Adds an encapsulated/unencapsulated descendant scene path to the current scope. The scene path provided should represent the location of an asset definition.
- L168 _public prototype_ `const pxr::SdfPathSet& GetEncapsulatedDefinitionPaths() const &;` — Get the encapsulated definition paths.
- L171 _public prototype_ `const pxr::SdfPathSet& GetUnencapsulatedDefinitionPaths() const &;` — Get the unencapsulated definition paths.
- L174 _public prototype_ `PrimPermutationConstRefPtr GetPermutation() const;` — Returns the permutation associated with this scope, if any.
- L180 _private member_ `const ScopeHandle _handle;` — The spec representing this scope, either an SdfPrimSpec or SdfVariantSpec.
- L183 _private member_ `const pxr::SdfPath _path;` — Scene path associated with this scope.
- L186 _private member_ `const ItemScope* _parent = nullptr;` — Parent scope (null only for the root scope of an Item).
- L189 _private member_ `const Item* _owner = nullptr;` — The Item that owns this scope.
- L192 _private member_ `types::int32 _opinionDepth = types::InvalidIndex;` — Depth of the strongest opinion encountered within this scope.
- L195 _private member_ `types::int32 _consumerDepth = types::InvalidIndex;` — Depth of the ancestor asset that consumes descendant targets.
- L198 _private member_ `const PrimPermutationConstRefPtr _perm = nullptr;` — Permutation associated with this scope, if any.
- L201 _private member_ `pxr::SdfPathVector _unencapsulatedPropertyPaths;` — The property paths and depths of the overrides active on this scope.
- L202 _private member_ `std::vector<types::int32> _unencapsulatedPropertyDepths;`
- L205 _private member_ `pxr::SdfPathSet _dependsOn;` — The set of resolved targets this item depends on.
- L212 _private member_ `pxr::SdfPathSet _encapsulatedDefinitionScenePaths;` — The scene paths of the current scopes descendant definitions. This can be useful in order to quickly acquire the locations of nested assets. The paths are separated depending on whether or not the asset is fully encapsulated (has no overrides) or is unencapsulated (requires the opinions of one or more ancestor assets to faithfully reproduce its current state).
- L213 _private member_ `pxr::SdfPathSet _unencapsulatedDefinitionScenePaths;`
- L223 _private member_ `std::unordered_map<pxr::TfToken, std::int32_t, pxr::TfHash> _contentCountsByCategory;` — Content counts and paths. These are separated into two maps because the path storage can be expensive on large scenes. The counts are mandatory however the path storage can be disabled by setting environment variable: USDPREGEN_STORE_CONTENT_PATHS=0
- L227 _private member_ `std::unordered_map<pxr::TfToken, pxr::SdfPathVector, pxr::TfHash> _contentPathsByCategory;`
- L234 _private member_ `std::optional<pxr::SdfPathSet> _candidateOverridePaths;` — A list of prim paths provided by the user that controls the prims inside the asset that can contribute override options, and thus influence the eventual creation of a target. Supplying a specific subset of paths (if known) can accelerate the tracker traversal. If can also be used as a broad filter to prevent overrides getting picked up accidentally.

#### struct `internal::ItemScope::CategoryView`  
`struct CategoryView`  
_L109-113_
- desc: View on the internal map state of a specific content category.
- L111 _public member_ `std::int32_t count = 0;`
- L112 _public member_ `const pxr::SdfPathVector& paths;`

#### class `internal::Item`  
`class Item`  
_L261-367_
- desc: Item depth corresponds to the nesting level of asset definitions in the stage and is used to reason about override and dependency behavior.
- L265 _public prototype_ `Item(const pxr::UsdPrim& prim, const ExtAssetDefinition* assetDefn, const ScopeHandle& handle, Item* parent, const std::optional<pxr::SdfPathSet>& candidateOverridePaths);`
- L272 _public prototype_ `const pxr::SdfPath& GetPath() const &;` — Returns the scene path for the prim that introduced this item.
- L275 _public prototype_ `const ExtAssetDefinition* GetDefinition() const;` — Returns the asset definition for this item.
- L278 _public prototype_ `const std::string& GetUniqueId() const &;` — Returns the unique identifier of the active asset definition.
- L281 _public prototype_ `types::int32 GetDepth() const;` — Returns the depth of this item within the asset hierarchy.
- L283 _public prototype_ `const pxr::SdfAssetPath& GetIdentifier() const &;`
- L285 _public prototype_ `const pxr::TfToken& GetDefaultPrim() const &;`
- L287 _public prototype_ `const pxr::SdfPath& GetPathAtIntroduction() const &;`
- L289 _public prototype_ `bool ContainsPermutations() const;`
- L291 _public prototype_ `types::int32 GetOverrideDepth() const;`
- L293 _public prototype_ `ItemScope* PushScope(const ScopeHandle& handle, const pxr::SdfPath& path, const ItemScope* parent, const PrimPermutationRefPtr& perm, bool consumesDescendants);`
- L299 _public prototype_ `void PopScope();`
- L301 _public prototype_ `ItemScope* GetCurrentScope();`
- L303 _public prototype_ `const ItemScope* GetCurrentScope() const;`
- L305 _public prototype_ `Item* GetParentItem();`
- L307 _public prototype_ `const Item* GetParentItem() const;`
- L309 _public prototype_ `ItemScope* GetPrimScope();`
- L311 _public prototype_ `const ItemScope* GetPrimScope() const;`
- L313 _public prototype_ `bool IsRootItem() const;`
- L315 _public prototype_ `std::size_t NumScopes() const;`
- L317 _public prototype_ `ItemScope* GetScope(size_t idx);`
- L319 _public prototype_ `const ItemScope* GetScope(size_t idx) const;`
- L322 _public prototype_ `void UpdateAssetDefinition( const pxr::UsdPrim& prim, const ExtAssetDefinition* assetDefn, const ScopeHandle& handle, const std::optional<pxr::SdfPathSet>& candidateOverridePaths);` — Replace the active asset definition context.
- L329 _public prototype_ `bool ShouldCollectOverridesForPrim(const pxr::SdfPath& path) const;` — Returns true if the given path should be inspected for overrides.
- L333 _private typedef_ `using ItemScopeList = std::vector<std::unique_ptr<ItemScope>>;`
- L354 _private member_ `const pxr::SdfPath _path;` — The scene path of this location in namespace. This path will always be a regular prim path (in contrast to item scope paths which may include variant selections.
- L357 _private member_ `types::int32 _depth = 0;` — The depth of the asset this item represents
- L360 _private member_ `Item* _parent = nullptr;` — Parent item in the asset hierarchy.
- L363 _private member_ `std::unique_ptr<_Context> _ctx = nullptr;` — Active context for the current asset definition.
- L366 _private member_ `ItemScopeList* _scopes = nullptr;` — Pointer to the current scope list for convenience (owned by the context).

#### struct `internal::Item::_Context`  
`struct _Context`  
_L342-349_
- desc: The current context of this item - the asset definition, intro path, default prim, scope list, and allowed override paths. Variants, and composition changes in general, may swap the underlying external asset an item (location in namespace) reflects. Rather than attempt to construct a new in these cases, we instead update the context entry via UpdateAssetDefinition()
- L344 _public member_ `const ExtAssetDefinition* assetDefn;`
- L345 _public member_ `pxr::SdfPath pathAtIntroduction;`
- L346 _public member_ `pxr::TfToken defaultPrim;`
- L347 _public member_ `ItemScopeList scopes;`
- L348 _public member_ `std::optional<pxr::SdfPathSet> candidateOverridePaths;`

#### Free symbols / members of external scopes

- L37 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L38 _typedef_ `using SdfVariantSpecHandle = SdfHandle<SdfVariantSpec>;`
- L45 _typedef_ `using PrimPermutationRefPtr = std::shared_ptr<class PrimPermutation>;`
- L46 _typedef_ `using PrimPermutationConstRefPtr = std::shared_ptr<const class PrimPermutation>;`
- L48 _namespace_ `namespace internal`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/layerWriter.h` (Private)


#### class `internal::LayerWriter`  
`class LayerWriter`  
_L88-197_
- L91 _public prototype_ `LayerWriter(const pxr::UsdStageRefPtr& stage);`
- L93 _public prototype_ `~LayerWriter() = default;`
- L102 _public prototype_ `ScopeHandle AssetDefinitionAdded(const ExtAssetDefinition& assetDefn);` — \return A handle to the definition scope in the data layer.
- L110 _public prototype_ `ScopeHandle AddPermutation( const Item* curItem, const pxr::SdfPath& primPath, const PrimPermutationConstRefPtr& perm, types::int32 nestingLevel);` — \return A handle to the created variant spec.
- L120 _public prototype_ `void AddChildAssetDependencyToParent(const Item* curItem);` — This authors an inherits arc under the parent’s "assets" scope so that dependency relationships can later be reconstructed.
- L137 _public prototype_ `std::optional<TargetUid> GenerateOrReuseTarget(const pxr::TfSpan<Item*>& itemStack);` — \return The generated TargetUid, or nullopt if no target was produced.
- L148 _public prototype_ `TargetDataRefPtr BuildTargetData(const TargetUid& targetUid) const;` — \return A populated TargetData object, or null if invalid.
- L155 _public prototype_ `void AddNewScenePath(const pxr::SdfPath& path);` — This builds a structural representation of the scene under /__scene__, preserving the prim type information from the source stage when available. This data is only used for diagnostic purposes.
- L160 _public prototype_ `bool Save(const std::string& filename);` — \return True on success.
- L164 _private prototype_ `pxr::SdfPrimSpecHandle _CreatePrimInDataLayer(const pxr::SdfPath& primPath);`
- L166 _private prototype_ `pxr::SdfPrimSpecHandle _GetAssetsContainerSpec( const pxr::SdfSpecHandle& parentSpec);`
- L169 _private prototype_ `pxr::SdfSpecHandle _GetPrimAtPath(const ScopeHandle& handle);`
- L171 _private prototype_ `pxr::SdfPrimSpecHandle _GetPrimAtPath(const pxr::SdfPath& primPath) const;`
- L173 _private prototype_ `void _ConfigureTargetOpsForLevel( const pxr::TfSpan<Item*>& itemStack, const pxr::SdfPrimSpecHandle& curTarget, const size_t itemIdx, const size_t scopeIdx, const types::int32 overrideDepth, PersistentHasher& permHasher);`
- L181 _private prototype_ `void _ConfigureTarget( const pxr::TfSpan<Item*>& itemStack, const pxr::SdfPrimSpecHandle& curTarget, const size_t itemIdx, const types::int32 overrideDepth, PersistentHasher& permHasher);`
- L188 _private prototype_ `pxr::SdfPathVector _GetDependsOnPaths( const pxr::SdfPrimSpecHandle& targetSpec) const;`
- L191 _private prototype_ `std::vector<TargetUid> _GetTargetDependencies( const pxr::UsdPrim& target) const;`
- L194 _private member_ `pxr::SdfLayerRefPtr _dataLayer;`
- L196 _private member_ `pxr::UsdStageRefPtr _stage;`

#### Free symbols / members of external scopes

- L36 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L37 _typedef_ `using SdfSpecHandle = SdfHandle<SdfSpec>;`
- L46 _typedef_ `using TargetDataRefPtr = std::shared_ptr<class TargetData>;`
- L47 _typedef_ `using PrimPermutationConstRefPtr = std::shared_ptr<const class PrimPermutation>;`
- L49 _namespace_ `namespace internal`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/persistentHasher.h` (Private)


#### class `internal::PersistentHasher`  
`class PersistentHasher`  
_L17-43_
- L21 _public prototype_ `std::uint64_t GetHash64() const;`
- L23 _public prototype_ `std::uint32_t GetHash32() const;`
- L25 _public prototype_ `void AddString(const std::string& str);`
- L27 _public prototype_ `void AddFilePath(const std::string& path);`
- L29 _public prototype_ `void AddUint64(const std::uint64_t val);`
- L31 _public prototype_ `const std::vector<std::string>& GetEntries() const &;`
- L33 _public prototype_ `bool IsEmpty() const;`
- L37 _private prototype_ `void _AddBytes(const void* data, std::size_t size);`
- L39 _private member_ `static constexpr std::uint64_t _offset = 14695981039346656037ULL;`
- L40 _private member_ `static constexpr std::uint64_t _prime = 1099511628211ULL;`
- L41 _private member_ `std::uint64_t _hash = _offset;`
- L42 _private member_ `std::vector<std::string> _entries;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace internal`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/primPermutationSet.h` (Private)


#### class `internal::PrimPermutationSet`  
`class PrimPermutationSet`  
_L39-65_
- L42 _public prototype_ `PrimPermutationSet(const pxr::SdfPath& path);`
- L44 _public prototype_ `const pxr::SdfPath& GetPath() const &;`
- L46 _public prototype_ `void AddPermutations(const std::vector<PrimPermutation>& perms);`
- L48 _public prototype_ `std::vector<PrimPermutationRefPtr> GetPermutations() const;`
- L50 _public prototype_ `void FinalizeCurrentEntries();`
- L52 _public prototype_ `bool IsEmpty() const;`
- L56 _private prototype_ `void _AddPermutation(const PrimPermutationRefPtr& primPerm);`
- L58 _private member_ `pxr::SdfPath _path;`
- L60 _private member_ `std::vector<PrimPermutationRefPtr> _curEntries;`
- L62 _private member_ `std::set<std::string> _prevEntries;`
- L64 _private member_ `size_t _iterationNum = 0;`

#### Free symbols / members of external scopes

- L24 _typedef_ `using PrimPermutationRefPtr = std::shared_ptr<class PrimPermutation>;`
- L26 _namespace_ `namespace internal`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Private/UsdPregen/util.h` (Private)


#### struct `internal::util::SerializedOpArg`  
`struct SerializedOpArg`  
_L188-200_
- desc: Wire-format representation of a single argument extracted from the "opargs:" namespace of a serialized PermutationOp prim spec.
- L191 _public member_ `std::string name;` — Argument name with the "opargs:" prefix removed.
- L196 _public member_ `std::string typeName;` — Sdf value type name (see SdfValueTypeNames). For example "string" or "token". The deserializer uses this to construct the matching SdfAttributeSpec.
- L199 _public member_ `std::string value;` — String-encoded default value. Round-tripped via VtValue stringification.

#### struct `internal::util::SerializedOp`  
`struct SerializedOp`  
_L210-218_
- desc: Captures the prim-spec typeName authored by the op's Serialize() override and the list of opargs:* arguments. Intended as a shared intermediate between the JSON and UObject manifest backends so they can share the op (de)serialization logic.
- L214 _public member_ `std::string typeName;` — Prim-spec type name authored by the op's Serialize() override. For example "UsdVariantSelectionOp" or "UsdInheritOp".
- L217 _public member_ `std::vector<SerializedOpArg> args;` — Argument list extracted from the prim spec's "opargs:" namespace.

#### Free symbols / members of external scopes

- L23 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L41 _typedef_ `using SdfSpecHandle = SdfHandle<SdfSpec>;`
- L42 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L43 _typedef_ `using SdfVariantSpecHandle = SdfHandle<SdfVariantSpec>;`
- L44 _typedef_ `using SdfVariantSetSpecHandle = SdfHandle<SdfVariantSetSpec>;`
- L49 _typedef_ `using UsdStageConstRefPtr = TfRefPtr<const UsdStage>;`
- L55 _namespace_ `namespace internal`
- L55 _namespace_ `namespace util` (scope `internal`)
- L59 _prototype_ `GetAssetFromFirstDefiningSpec(const pxr::UsdPrim& prim);` (scope `internal::util`)
- L62 _prototype_ `GetAssetFromFirstDirectReferenceOrPayload(const pxr::UsdPrim& prim);` (scope `internal::util`)
- L65 _prototype_ `GetNodeReferencingAsset( const pxr::UsdPrim& prim, const pxr::SdfAssetPath& assetPath);` (scope `internal::util`)
- L70 _prototype_ `GetIntroPathAndDefaultPrim( const pxr::UsdPrim& prim, const pxr::SdfAssetPath& assetPath, pxr::SdfPath* targetedPrimPath, pxr::TfToken* defaultPrim);` (scope `internal::util`)
- L77 _prototype_ `PrimHasReferenceToAsset( const pxr::UsdPrim& prim, const pxr::SdfAssetPath& assetPath);` (scope `internal::util`)
- L83 _function_ `CartesianProduct(const std::vector<std::vector<T>>& sets)` (scope `internal::util`)
- L89 _function_ `` (scope `internal::util::CartesianProduct`)
- L107 _prototype_ `BlockAllVariantSets(const pxr::UsdPrim& prim);` (scope `internal::util`)
- L110 _prototype_ `GetOrCreateVariantSetSpec( const pxr::SdfSpecHandle& spec, const std::string& variantSetName);` (scope `internal::util`)
- L115 _prototype_ `GetOrCreateVariantSetSpec( const pxr::SdfPrimSpecHandle& primSpec, const std::string& variantSetName);` (scope `internal::util`)
- L120 _prototype_ `GetOrCreateVariantSetSpec( const pxr::SdfVariantSpecHandle& variantSpec, const std::string& variantSetName);` (scope `internal::util`)
- L125 _prototype_ `GetOrCreateVariantSpec( pxr::SdfVariantSetSpecHandle variantSetSpec, const std::string& variantName, const std::function<void(const pxr::SdfVariantSpecHandle&)>& onCreate);` (scope `internal::util`)
- L131 _prototype_ `GetOrCreateVariantSpec( pxr::SdfVariantSetSpecHandle variantSetSpec, const std::string& variantName);` (scope `internal::util`)
- L136 _prototype_ `GetChildSpec( const pxr::SdfPrimSpecHandle& parent, const pxr::TfToken& childName);` (scope `internal::util`)
- L141 _prototype_ `GetLocalLayerStackTimestampAndHash( const pxr::UsdStageConstRefPtr& stage, bool hashRealPaths = false);` (scope `internal::util`)
- L146 _prototype_ `FileTimeToSystemTimeSeconds(const std::filesystem::file_time_type& fileTime);` (scope `internal::util`)
- L149 _prototype_ `FormatTimestamp(const std::uint64_t seconds);` (scope `internal::util`)
- L152 _prototype_ `RandomUInt64();` (scope `internal::util`)
- L155 _prototype_ `HashStringArrayToUInt32(const std::vector<std::string>& values);` (scope `internal::util`)
- L171 _prototype_ `MetadataToUsdaBlob(const pxr::VtDictionary& metadata);` (scope `internal::util`)
- L181 _prototype_ `UsdaBlobToMetadata(const std::string& blob);` (scope `internal::util`)
- L228 _prototype_ `ToSerializedOp(const PermutationOpRefPtr& op);` (scope `internal::util`)
- L238 _prototype_ `FromSerializedOp(const SerializedOp& serializedOp);` (scope `internal::util`)

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/USDPregenCoreModule.h` (Public)


#### class `FUSDPregenCoreModule`  
`class FUSDPregenCoreModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/assetDefinitionRegistry.h` (Public)


#### class `AssetDefinitionRegistry`  
`class AssetDefinitionRegistry : public pxr::TfWeakBase`  
_L51-103_
- inherits: `pxr::TfWeakBase`
- desc: The registry is implemented as a TfSingleton and can be accessed via GetInstance().
- L56 _public prototype_ `static AssetDefinitionRegistry& GetInstance();` — Returns the global AssetDefinitionRegistry instance.
- L70 _public prototype_ `const ExtAssetDefinition* AddDefinition( const ExtAssetDefinition& assetDefn);` — \return Pointer to the stored definition instance, or nullptr if the definition could not be registered.
- L79 _public prototype_ `const ExtAssetDefinition* GetDefinition( const std::string& uniqueId) const;` — \return Pointer to the registered definition, or nullptr if no matching definition exists.
- L86 _public prototype_ `GetAllDefinitions() const;`
- L94 _private prototype_ `AssetDefinitionRegistry() = default;`
- L95 _private prototype_ `~AssetDefinitionRegistry() = default;`
- L100 _private member_ `std::unordered_map<pxr::TfToken, std::unique_ptr<ExtAssetDefinition>, pxr::TfHash> _entries;` — Registry storage mapping identifiers to definitions.
- L102 _private member_ `mutable std::mutex _mutex;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/discoveryOptions.h` (Public)


#### enum `DiscoveryMode`  
`enum class DiscoveryMode : std::uint8_t`  
_L24-31_
- desc: Controls how permutations are explored during discovery.
- L27 _public enumerator_ `AllPermutations` — Explore all permutations discovered for a prim.
- L30 _public enumerator_ `ComposedPermutationOnly` — Only process the currently composed configuration.

#### enum `VersionFallbackMode`  
`enum class VersionFallbackMode : std::uint8_t`  
_L35-47_
- desc: Controls how version strings are generated in the absence of explicit metadata.
- L38 _public enumerator_ `None` — No fallback
- L42 _public enumerator_ `LayerStackFilesAndTimestamps` — Build a version hash using the asset's local layer stack identifiers and timestamps.
- L46 _public enumerator_ `ResolvedLayerStackFilesAndTimestamps` — Build a version hash using the asset's local layer stack resolved paths and timestamps.

#### enum `IdentifierFallbackMode`  
`enum class IdentifierFallbackMode : std::uint8_t`  
_L51-59_
- desc: Controls how asset identifiers are generated in the absence of an explicitly provided asset path.
- L54 _public enumerator_ `None` — No fallback - an explicit, resolved SdfAssetPath must be provided.
- L58 _public enumerator_ `FirstDirectReferenceOrPayload` — Inspect the prim composition and extract the first direct reference or payload, if any.

#### struct `DiscoveryOptions`  
`struct DiscoveryOptions`  
_L62-110_
- desc: Configuration options controlling pregen tracker and discovery behavior.
- L65 _public member_ `DiscoveryMode discoveryMode = DiscoveryMode::AllPermutations;` — Permutation discovery mode.
- L69 _public member_ `std::string discoveryPluginName;` — Name of the discovery plugin to use. An empty string will use the built-in discovery plugin.
- L76 _public member_ `std::string definitionPrefix;` — A prefix that may be added to all newly created asset definition names. This allows for per-project definition UIDs, for example, or creating test assets using a temporary prefix. The default discovery plugin will always prepend the prefix, however custom plugins must manually validate and incorporate the prefix into the definitions they generate.
- L81 _public member_ `pxr::SdfPath initialPath;` — The path to use when starting the traversal. This allows discovery to be limited to a subsection of the input stage. Note that this value overrides the initial path specified by the discovery plugin.
- L85 _public member_ `pxr::TfTokenVector purposes;` — The UsdGeomImageable purposes to include during discovery. An empty vector is interpreted as all purposes.
- L91 _public member_ `pxr::TfTokenVector excludeVariantSets;` — A list of variant set names that should be ignored during discovery. This is typically used to filter out variant sets that are not relevant for asset permutations. An entry of "*" can be used to exclude all variant sets.
- L95 _public member_ `IdentifierFallbackMode assetIdentifierFallback = IdentifierFallbackMode::None;` — When an asset does not specify an explicit identifier, controls the strategy used to compute a fallback value.
- L99 _public member_ `VersionFallbackMode assetVersionFallback = VersionFallbackMode::None;` — When an asset does not specify a version, controls the strategy used to compute a fallback.
- L103 _public member_ `pxr::Usd_PrimFlagsPredicate traversalPredicate = pxr::UsdPrimDefaultPredicate;` — The predicate to use during traversal. This allows abstract or unloaded prims to be discovered if needed.
- L105 _public prototype_ `bool operator==(const DiscoveryOptions& rhs) const;`
- L107 _public prototype_ `bool operator!=(const DiscoveryOptions& rhs) const;`
- L109 _public prototype_ `std::string DumpToString() const;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/discoveryPlugin.h` (Public)


#### class `DiscoveryPlugin`  
`class DiscoveryPlugin`  
_L114-273_
- desc: Custom implementations can attach metadata to the generated definitions. The metadata will be available during the storage phase and can be used to organize product storage locations by asset category, for example.
- L118 _public prototype_ `DiscoveryPlugin(const DiscoveryOptions& options);`
- L120 _public prototype_ `virtual ~DiscoveryPlugin();`
- L123 _public prototype_ `virtual bool Initialize(const pxr::UsdStageRefPtr& stage);` — Initialize any internal data, prior to traversal.
- L126 _public prototype_ `virtual pxr::SdfPath GetInitialPath() const;` — Get the initial path from which to start traversals.
- L135 _public prototype_ `virtual bool IsAsset(const pxr::UsdPrim& prim) const;` — Discovery traversals will call this method for every prim encountered in the scene.
- L169 _public prototype_ `GetAssetDefinition(const pxr::UsdPrim& prim) const;`
- L185 _public prototype_ `CreateRootDefinition(const pxr::UsdPrim& rootPrim) const;`
- L198 _public prototype_ `virtual bool PrunePrim(const pxr::UsdPrim& prim) const;` — Returning true prevents traversal of this prim and its subtree.
- L208 _public prototype_ `GetCurrentPrimPermutation(const pxr::UsdPrim& prim) const;`
- L224 _public prototype_ `GetPrimPermutations(const pxr::UsdPrim& prim) const;`
- L237 _public prototype_ `GetContentCategoryForPrim( const pxr::UsdPrim& prim, const ExtAssetDefinition* defn) const;`
- L254 _public prototype_ `GetOverrideCandidatePrimPaths( const pxr::UsdPrim& assetPrim, const ExtAssetDefinition* defn) const;`
- L260 _public prototype_ `const DiscoveryOptions& GetOptions() const;` — Get the current options.
- L264 _private member_ `DiscoveryOptions _options;`
- L266 _private member_ `pxr::SdfPath _initialPath;`
- L268 _private member_ `bool _excludeAllVariantSets = false;`
- L270 _private member_ `pxr::TfToken::HashSet _excludeVariantSets;`
- L272 _private member_ `mutable std::unique_ptr<struct internal::_VersionCache> _versionCache;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L39 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L40 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L46 _namespace_ `namespace DiscoveryPluginTokens`
- L48 _externvar_ `extern const pxr::TfToken reservedMetadataPrefix;` (scope `DiscoveryPluginTokens`)
- L49 _externvar_ `extern const pxr::TfToken definitionPrefix;` (scope `DiscoveryPluginTokens`)
- L50 _externvar_ `extern const pxr::TfToken initialPrim;` (scope `DiscoveryPluginTokens`)
- L53 _namespace_ `namespace DefaultCategoryTokens`
- L55 _externvar_ `extern const pxr::TfToken boundables;` (scope `DefaultCategoryTokens`)
- L56 _externvar_ `extern const pxr::TfToken materials;` (scope `DefaultCategoryTokens`)
- L57 _externvar_ `extern const pxr::TfToken meshes;` (scope `DefaultCategoryTokens`)
- L58 _externvar_ `extern const pxr::TfToken shaders;` (scope `DefaultCategoryTokens`)
- L59 _externvar_ `extern const pxr::TfToken skeletons;` (scope `DefaultCategoryTokens`)
- L60 _externvar_ `extern const pxr::TfToken skelAnimations;` (scope `DefaultCategoryTokens`)
- L61 _externvar_ `extern const pxr::TfToken skelRoots;` (scope `DefaultCategoryTokens`)
- L62 _externvar_ `extern const pxr::TfToken lights;` (scope `DefaultCategoryTokens`)
- L63 _externvar_ `extern const pxr::TfToken noCategory;` (scope `DefaultCategoryTokens`)
- L66 _namespace_ `namespace internal`
- L71 _typedef_ `using DiscoveryPluginRefPtr = std::shared_ptr<class DiscoveryPlugin>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/discoveryPluginRegistry.h` (Public)


#### class `DiscoveryPluginRegistry`  
`class DiscoveryPluginRegistry : public pxr::TfWeakBase`  
_L49-91_
- inherits: `pxr::TfWeakBase`
- desc: Only a single plugin instance is typically active during a discovery pass over a composed USD stage.
- L57 _public typedef_ `using FactoryFn = std::function<DiscoveryPlugin*(const DiscoveryOptions&)>;` — The returned DiscoveryPlugin instance will be wrapped in a shared pointer by the registry.
- L68 _public prototype_ `bool RegisterFactory(const std::string& name, FactoryFn fn);` — \return True if the factory was successfully registered.
- L78 _public prototype_ `DiscoveryPluginRefPtr Create( const DiscoveryOptions& options) const;` — \return A shared pointer to the constructed plugin instance, or nullptr if the plugin name is not registered.
- L82 _public prototype_ `static DiscoveryPluginRegistry& GetInstance();` — Returns the global DiscoveryPluginRegistry instance.
- L87 _private prototype_ `DiscoveryPluginRegistry() = default;`
- L88 _private prototype_ `~DiscoveryPluginRegistry() = default;`
- L90 _private member_ `std::unordered_map<std::string, FactoryFn> _registry;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L30 _typedef_ `using DiscoveryPluginRefPtr = std::shared_ptr<class DiscoveryPlugin>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/extAssetDefinition.h` (Public)


#### class `ExtAssetDefinition`  
`class ExtAssetDefinition`  
_L48-201_
- desc: Various discovery plugin methods accept the active asset definition in addition to the current USD prim, so the plugin does not need to track the current definition.
- L56 _public prototype_ `ExtAssetDefinition();` — A default-constructed instance does not represent a valid asset and will return false from IsValid().
- L66 _public prototype_ `ExtAssetDefinition(const std::string& name, const std::string& version, const pxr::SdfAssetPath& identifier);` — If a definition prefix was provided by the discovery options, it will be prepended, resulting in "Prefix_Chair_v2"
- L78 _public prototype_ `ExtAssetDefinition(const std::string& name, const std::string& version, const pxr::SdfAssetPath& identifier, const std::string& customUniqueId);` — Note that the definition prefix is not automatically applied to the unique id, and must be applied by the caller by querying the current discovery options.
- L87 _public prototype_ `ExtAssetDefinition(const std::string& name, const std::string& version, const pxr::SdfAssetPath& identifier, const pxr::VtDictionary& metadata);`
- L93 _public prototype_ `ExtAssetDefinition(const std::string& name, const std::string& version, const pxr::SdfAssetPath& identifier, const std::string& customUniqueId, const pxr::VtDictionary& metadata);` — Constructs an asset definition with both custom unique id and metadata.
- L99 _public prototype_ `~ExtAssetDefinition() = default;`
- L101 _public prototype_ `ExtAssetDefinition(const ExtAssetDefinition&) = default;`
- L102 _public prototype_ `ExtAssetDefinition& operator=(const ExtAssetDefinition&) = default;`
- L104 _public prototype_ `ExtAssetDefinition(ExtAssetDefinition&&) = default;`
- L105 _public prototype_ `ExtAssetDefinition& operator=(ExtAssetDefinition&&) = default;`
- L107 _public prototype_ `bool operator==(const ExtAssetDefinition& rhs) const;`
- L108 _public prototype_ `bool operator!=(const ExtAssetDefinition& rhs) const;`
- L109 _public prototype_ `bool operator<(const ExtAssetDefinition& rhs) const;`
- L114 _public prototype_ `const std::string& GetName() const &;` — The name is an arbitrary identifier that describes the asset.
- L119 _public prototype_ `const std::string& GetVersion() const &;` — The version may be empty if the definition is unversioned.
- L125 _public prototype_ `const pxr::SdfAssetPath& GetIdentifier() const &;` — Typically this is an SdfAssetPath referencing the USD file or entry point of the external asset.
- L131 _public prototype_ `const std::string& GetUniqueId() const &;` — The unique id is either automatically generated from the name and version or explicitly supplied at construction.
- L137 _public prototype_ `const std::optional<pxr::VtDictionary>& GetMetadata() const &;` — Metadata is optional and may contain arbitrary key-value pairs used by discovery or asset processing systems.
- L140 _public prototype_ `bool HasMetadata() const;` — Returns true if metadata is present.
- L143 _public prototype_ `bool HasCustomUniqueId() const;` — Returns true if a custom unique id was supplied.
- L149 _public prototype_ `bool IsValid(std::string* reason = nullptr) const;` — If \p reason is provided, it will be populated with a description of the validation failure.
- L152 _public prototype_ `explicit operator bool() const noexcept;` — Convenience boolean conversion for validity checks.
- L155 _public prototype_ `static std::string MakeDefaultUniqueId( const std::string& name, const std::string& version);` — Generates the default unique id from the asset name and version.
- L162 _public prototype_ `static bool HasSameFields(const ExtAssetDefinition& defn1, const ExtAssetDefinition& defn2);` — This comparison includes differences in metadata.
- L168 _private prototype_ `ExtAssetDefinition(const std::string& name, const std::string& version, const pxr::SdfAssetPath& identifier, const std::string& customUniqueId, const std::optional<pxr::VtDictionary>& metadata);` — Internal constructor used to unify construction paths.
- L183 _private typedef_ `using _UniqueId = std::variant<_DefaultUniqueId, _CustomUniqueId>;`
- L186 _private member_ `std::string _name;` — The name of the asset. Must not be empty for the definition to be valid.
- L189 _private member_ `std::string _version;` — Optional version string for the asset.
- L193 _private member_ `pxr::SdfAssetPath _identifier;` — Identifier used to resolve and open the asset entry point. The asset is considered valid only if this identifier resolves.
- L197 _private member_ `_UniqueId _uniqueId;` — Unique identifier for the asset definition. Either generated automatically or explicitly supplied.
- L200 _private member_ `std::optional<pxr::VtDictionary> _metadata = std::nullopt;` — Optional metadata associated with the asset definition.

#### struct `ExtAssetDefinition::_DefaultUniqueId`  
`struct _DefaultUniqueId`  
_L173-176_
- L175 _public member_ `std::string value;`

#### struct `ExtAssetDefinition::_CustomUniqueId`  
`struct _CustomUniqueId`  
_L178-181_
- L180 _public member_ `std::string value;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/jsonManifestSerializer.h` (Public)


#### class `JsonManifestSerializer`  
`class JsonManifestSerializer : public ManifestSerializer`  
_L25-49_
- inherits: `ManifestSerializer`
- L29 _public prototype_ `JsonManifestSerializer() = default;`
- L31 _public prototype_ `virtual bool Serialize(const Manifest& manifest, ManifestPayload& payload) const override;`
- L34 _public prototype_ `virtual Manifest Deserialize(const ManifestPayload& payload) const override;`
- L36 _public prototype_ `virtual std::string GetEncoding() const override;`
- L38 _public prototype_ `virtual std::string GetFileExtension() const override;`
- L40 _public prototype_ `static std::string GetSchemaName();`
- L42 _public prototype_ `static std::int32_t GetSchemaVersion();`
- L44 _public prototype_ `static std::string Encoding();`
- L46 _public prototype_ `static std::string FileExtension();`
- L48 _public prototype_ `static std::size_t MaxFileSize();`

#### Free symbols / members of external scopes

- L17 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/jsonStoragePlugin.h` (Public)


#### class `JsonStoragePlugin`  
`class JsonStoragePlugin : public StoragePlugin`  
_L46-137_
- inherits: `StoragePlugin`
- desc: The storage directory may be overridden via the environment variable `USDPREGEN_DEFAULT_STORAGE_DIR`.
- L52 _public prototype_ `explicit JsonStoragePlugin(const StorageOptions& options = {});`
- L65 _public prototype_ `LoadManifestPayload(const TargetUid& targetUid) override;`
- L78 _public prototype_ `StoreManifestPayload(const TargetUid& targetUid, const ManifestPayload& payload) override;`
- L85 _public prototype_ `PersistManifestPayload(const TargetUid& targetUid) override;`
- L92 _public prototype_ `SerializeManifest(const Manifest& manifest) override;`
- L100 _public prototype_ `DeserializeManifestPayload(const ManifestPayload& payload) override;`
- L107 _public prototype_ `GetNameForUAsset(const TargetUid& targetUid, const std::vector<const ExtAssetDefinition*>& definitions, const std::string& assetType) override;`
- L116 _public prototype_ `GetPackageSubPathForUAsset(const TargetUid& targetUid, const std::vector<const ExtAssetDefinition*>& definitions, const std::string& assetType) override;`
- L122 _public prototype_ `GetPathForManifest(const TargetUid& targetUid) override;`
- L126 _private prototype_ `void _CheckOrCreateManifestDir(const std::string& manifestDir);` — Validate and optionally create the manifest directory.
- L129 _private member_ `std::string _manifestDir;` — Directory where manifest files are stored.
- L132 _private member_ `bool _manifestDirReady = false;` — True if the manifest directory is valid and usable.
- L136 _private member_ `std::string _packageSubPathTemplate;` — ${PLACEHOLDER} template used by GetPackageSubPathForUAsset. Falls back to StoragePlugin::DefaultPackageSubPathTemplate() if empty.

#### Free symbols / members of external scopes

- L22 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L26 _namespace_ `namespace JsonStoragePluginTokens`
- L28 _externvar_ `extern const pxr::TfToken manifestDirEnvvar;` (scope `JsonStoragePluginTokens`)
- L34 _typedef_ `using JsonStoragePluginRefPtr = std::shared_ptr<class JsonStoragePlugin>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/manifest.h` (Public)


#### struct `Product`  
`struct Product`  
_L34-50_
- desc: Multiple products may be associated with a single target depending on how the source USD asset expands during import.
- L37 _public member_ `std::string upackagePath;` — Unreal package path where the asset was created.
- L40 _public member_ `std::string uclass;` — Unreal object type
- L43 _public member_ `std::string unodeId;` — Node identifier for the generated Unreal node associated with the asset.
- L46 _public member_ `std::string usdPrimType;` — USD prim type responsible for producing this product.
- L49 _public member_ `std::string usdPrimPath;` — Absolute USD prim path of the source prim.

#### class `Manifest`  
`class Manifest`  
_L69-120_
- desc: A manifest is considered valid when it has TargetData attached, the TargetData is itself valid, and at least one product is present.
- L74 _public prototype_ `Manifest() = default;` — Constructs an empty manifest with no products and no attached target data.
- L79 _public prototype_ `TargetUid GetTargetUid() const;` — Returns an invalid TargetUid when no target data is attached.
- L85 _public prototype_ `void AddProduct(const Product& product);` — Products describe Unreal assets generated when this target is materialized.
- L88 _public prototype_ `const std::vector<Product>& GetProducts() const;` — Returns the list of products associated with this manifest.
- L99 _public prototype_ `void SetTargetData(const TargetDataRefPtr& targetData);` — May be set to a null pointer to clear any previously attached data.
- L104 _public prototype_ `const TargetDataRefPtr& GetTargetData() const;` — May return null if no target data was attached.
- L108 _public prototype_ `bool IsValid() const;` — Returns true if this manifest has valid target data attached and at least one product.
- L111 _public prototype_ `explicit operator bool() const noexcept;` — Convenience boolean conversion that returns IsValid().
- L116 _private member_ `std::vector<Product> _products;` — Products generated when this target is materialized.
- L119 _private member_ `TargetDataRefPtr _targetData;` — Originating target data. Required for the manifest to be valid.

#### Free symbols / members of external scopes

- L16 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L21 _typedef_ `using TargetDataRefPtr = std::shared_ptr<TargetData>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/manifestSerializer.h` (Public)


#### class `ManifestSerializer`  
`class ManifestSerializer`  
_L45-80_
- desc: Storage systems typically persist ManifestPayload objects directly without interpreting their contents. The serializer therefore forms the boundary between the in-memory Manifest representation and the encoded data stored on disk or transmitted between processes.
- L50 _public prototype_ `virtual ~ManifestSerializer();` — Virtual destructor.
- L56 _public prototype_ `virtual std::string GetFileExtension() const = 0;` — This value typically corresponds to the format used when writing serialized manifests to disk (for example ".json").
- L62 _public prototype_ `virtual std::string GetEncoding() const = 0;` — The returned string identifies the serialization format written into ManifestPayload::encoding (for example "application/json").
- L71 _public prototype_ `virtual bool Serialize(const Manifest& manifest, ManifestPayload& payload) const = 0;` — Returns true on successful serialization.
- L79 _public prototype_ `virtual Manifest Deserialize(const ManifestPayload& payload) const = 0;` — Implementations must interpret the payload according to the encoding used during serialization and reconstruct the original Manifest object.

#### Free symbols / members of external scopes

- L17 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/manifestTypes.h` (Public)


#### struct `ManifestPayload`  
`struct ManifestPayload`  
_L26-30_
- desc: `data` contains the serialized manifest contents and `encoding` identifies the serialization format (for example: application/json).
- L28 _public member_ `std::string encoding;`
- L29 _public member_ `std::vector<std::uint8_t> data;`

#### enum `ManifestLoadStatus`  
`enum class ManifestLoadStatus`  
_L33-43_
- desc: Status codes returned when requesting manifest data.
- L36 _public enumerator_ `Loaded` — Manifest was successfully located and loaded.
- L39 _public enumerator_ `DoesNotExist` — A manifest does not exist for the requested target.
- L42 _public enumerator_ `Error` — An error occurred while attempting to acquire the manifest.

#### struct `ManifestLoadResult`  
`struct ManifestLoadResult`  
_L46-51_
- L48 _public member_ `ManifestLoadStatus status = ManifestLoadStatus::Error;`
- L49 _public member_ `ManifestPayload payload;`
- L50 _public member_ `std::string message;`

#### enum `ManifestSaveStatus`  
`enum class ManifestSaveStatus`  
_L55-65_
- desc: Status codes returned when storing manifest data.
- L58 _public enumerator_ `Saved` — Manifest was successfully written.
- L61 _public enumerator_ `NotSaved` — Manifest was not written (implementation-specific decision).
- L64 _public enumerator_ `Error` — An error occurred while attempting to write the manifest.

#### struct `ManifestSaveResult`  
`struct ManifestSaveResult`  
_L67-71_
- L69 _public member_ `ManifestSaveStatus status = ManifestSaveStatus::Error;`
- L70 _public member_ `std::string message;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/permutationOps.h` (Public)


#### class `PermutationOp`  
`class PermutationOp`  
_L53-89_
- desc: The configuration of operations applied to a prim (see \ref PrimPermutation) must be hashable in order to contribute to a target's unique id.
- L57 _public prototype_ `virtual ~PermutationOp();`
- L60 _public prototype_ `virtual void Apply(pxr::UsdPrim& prim) = 0;` — Applies the operation to the given prim.
- L63 _public prototype_ `virtual std::string GetUniqueId() const = 0;` — Returns a stable unique identifier for the operation.
- L66 _public prototype_ `virtual void Serialize(pxr::SdfPrimSpecHandle& primSpec) const = 0;` — Serializes the operation into the provided prim spec.
- L70 _public typedef_ `using FromSpecFn = std::function< PermutationOpRefPtr(const pxr::SdfPrimSpecHandle& primSpec) >;` — Factory function used to reconstruct a PermutationOp from a serialized prim spec produced by an earlier call to Serialize().
- L79 _public prototype_ `static bool RegisterFactory(const std::string& typeName, FromSpecFn fn);` — Returns false if a factory for the type name was already registered.
- L87 _public prototype_ `static PermutationOpRefPtr CreateFromSpec( const pxr::SdfPrimSpecHandle& primSpec);` — The prim spec's type name is used to look up a factory previously registered via RegisterFactory(). Returns nullptr if no factory is registered for the spec's type name, or if the spec is null.

#### class `UsdVariantPermutationOp`  
`class UsdVariantPermutationOp : public PermutationOp`  
_L100-133_
- inherits: `PermutationOp`
- desc: This operation represents a variant selection authored on a prim's variant set.
- L105 _public prototype_ `UsdVariantPermutationOp(const std::string& variantSetName, const std::string& variantName);` — Constructs a variant permutation operation.
- L110 _public prototype_ `static PermutationOpRefPtr FromSerialized( const std::string& variantSetName, const std::string& variantName);` — Equivalent to calling the standard constructor; provided for symmetry with the other PermutationOp subclasses.
- L115 _public prototype_ `virtual void Apply(pxr::UsdPrim& prim) final;` — Applies the variant selection to the prim.
- L118 _public prototype_ `virtual std::string GetUniqueId() const final;` — Returns the unique identifier for this operation.
- L121 _public prototype_ `virtual void Serialize(pxr::SdfPrimSpecHandle& primSpec) const final;` — Serializes parameters to the given prim spec.
- L124 _public prototype_ `std::pair<std::string, std::string> GetVariantSelection() const;` — Returns the variant set and variant name.
- L126 _public prototype_ `bool operator==(const UsdVariantPermutationOp& rhs) const;`
- L127 _public prototype_ `bool operator!=(const UsdVariantPermutationOp& rhs) const;`
- L131 _private member_ `std::string _variantSetName;`
- L132 _private member_ `std::string _variantName;`

#### class `UsdInheritPermutationOp`  
`class UsdInheritPermutationOp : public PermutationOp`  
_L141-174_
- inherits: `PermutationOp`
- desc: Permutation operation that authors a USD inherit arc.
- L145 _public prototype_ `UsdInheritPermutationOp( const pxr::SdfPath& pathToInherit, pxr::SdfListOpType listOpType = pxr::SdfListOpTypePrepended);`
- L151 _public prototype_ `static PermutationOpRefPtr FromSerialized( const pxr::SdfPath& pathToInherit, pxr::SdfListOpType listOpType = pxr::SdfListOpTypePrepended);` — Equivalent to calling the standard constructor; provided for symmetry with the other PermutationOp subclasses.
- L156 _public prototype_ `virtual void Apply(pxr::UsdPrim& prim) final;` — Applies the inherit to the prim.
- L159 _public prototype_ `virtual std::string GetUniqueId() const final;` — Returns the unique identifier for this operation.
- L162 _public prototype_ `virtual void Serialize(pxr::SdfPrimSpecHandle& primSpec) const final;` — Serializes parameters to the given prim spec.
- L165 _public prototype_ `const pxr::SdfPath& GetPathToInherit() const;` — Returns the path that will be inherited.
- L168 _public prototype_ `pxr::SdfListOpType GetListOpType() const;` — Returns the list operation type used when authoring the inherit.
- L172 _private member_ `const pxr::SdfPath _pathToInherit;`
- L173 _private member_ `pxr::SdfListOpType _listOpType;`

#### class `SchemaApplyPermutationOp`  
`class SchemaApplyPermutationOp : public PermutationOp`  
_L182-209_
- inherits: `PermutationOp`
- desc: Permutation operation that applies a USD API schema.
- L187 _public prototype_ `SchemaApplyPermutationOp(const std::string& schemaName);` — Constructs an operation that applies the given schema.
- L193 _public prototype_ `static PermutationOpRefPtr FromSerialized(const std::string& schemaName);` — Equivalent to calling the standard constructor; provided for symmetry with the other PermutationOp subclasses.
- L196 _public prototype_ `virtual void Apply(pxr::UsdPrim& prim) final;` — Applies the schema to the prim.
- L199 _public prototype_ `virtual std::string GetUniqueId() const final;` — Returns the unique identifier for this operation.
- L202 _public prototype_ `virtual void Serialize(pxr::SdfPrimSpecHandle& primSpec) const final;` — Serializes parameters to the given prim spec.
- L204 _public prototype_ `std::string GetSchemaName() const;`
- L208 _private member_ `const std::string _schemaName;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L31 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L37 _typedef_ `using PermutationOpRefPtr = std::shared_ptr<class PermutationOp>;`
- L38 _typedef_ `using PermutationOpVector = std::vector<PermutationOpRefPtr>;`
- L91 _typedef_ `using UsdVariantPermutationOpRefPtr = std::shared_ptr<class UsdVariantPermutationOp>;`
- L135 _typedef_ `using UsdInheritPermutationOpRefPtr = std::shared_ptr<class UsdInheritPermutationOp>;`
- L176 _typedef_ `using SchemaApplyPermutationOpRefPtr = std::shared_ptr<class SchemaApplyPermutationOp>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/pregen.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define PREGEN_NS ue::usdpregen`
- L7 _macro_ `#define PREGEN_NAMESPACE_OPEN_SCOPE namespace PREGEN_NS {`
- L9 _macro_ `#define PREGEN_NAMESPACE_CLOSE_SCOPE }`
- L11 _macro_ `#define PREGEN_NAMESPACE_USING_DIRECTIVE using namespace PREGEN_NS;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/primPermutation.h` (Public)


#### class `PrimPermutation`  
`class PrimPermutation`  
_L42-108_
- desc: PrimPermutation objects are typically produced by DiscoveryPlugin implementations when enumerating possible asset configurations.
- L46 _public prototype_ `PrimPermutation();` — Constructs an empty permutation
- L49 _public prototype_ `PrimPermutation(const pxr::SdfPath& path);` — Constructs an empty permutation for the given prim path.
- L52 _public prototype_ `PrimPermutation(const pxr::SdfPath& path, const PermutationOpVector& ops);` — Constructs a permutation with an initial set of operations.
- L56 _public prototype_ `const pxr::SdfPath& GetPath() const &;` — Returns the prim path associated with this permutation.
- L62 _public prototype_ `std::string GetUniqueId() const;` — The identifier is derived from the prim path and the set of permutation operations.
- L68 _public prototype_ `bool AppendOp(const PermutationOpRefPtr& op);` — Returns false if an operation with the same unique identifier has already been added.
- L71 _public prototype_ `const PermutationOpVector& GetOps() const &;` — Returns the ordered set of permutation operations.
- L74 _public prototype_ `void RemoveOps(const PermutationOpVector& opsToRemove);` — Removes the specified operations from the permutation.
- L77 _public prototype_ `bool IsEmpty() const;` — Returns true if this permutation contains no operations.
- L86 _public prototype_ `bool GetConsumesDescendants() const;` — When enabled, all descendant scene description is treated as belonging to the asset owning this permutation, regardless of asset boundaries in descendant prims. This can needed if a schema modifies the ownership semantics of the asset hierarchy (the UE collapsing schema for example)
- L89 _public prototype_ `void SetConsumesDescendants(bool value);` — Sets whether this permutation consumes descendant scene description.
- L92 _public prototype_ `explicit operator bool() const noexcept;` — Convenience boolean conversion for validity checks.
- L96 _private member_ `const pxr::SdfPath _path;`
- L99 _private member_ `PermutationOpVector _ops;` — Ordered list of permutation operations.
- L102 _private member_ `std::set<std::string> _addedOps;` — Set of operation identifiers used to prevent duplicates.
- L107 _private member_ `bool _consumesDescendants = false;` — Whether this permutation causes descendant scene description to be treated as part of the owning asset regardless of the descendant asset hierarchy.

#### Free symbols / members of external scopes

- L20 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L24 _typedef_ `using PrimPermutationRefPtr = std::shared_ptr<class PrimPermutation>;`
- L25 _typedef_ `using PrimPermutationConstRefPtr = std::shared_ptr<const class PrimPermutation>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/sceneDiscovery.h` (Public)


#### class `SceneDiscovery`  
`class SceneDiscovery`  
_L53-104_
- desc: Internally, SceneDiscovery mirrors the standard traversal pattern required by SceneTracker and manages permutation exploration for each prim encountered.
- L59 _public typedef_ `using ResultMap = std::unordered_map<pxr::SdfPath, std::vector<class TargetUid>, pxr::TfHash>;` — Map from scene paths to the list of target identifiers discovered at that location.
- L64 _public prototype_ `SceneDiscovery(const pxr::UsdStageRefPtr& stage);` — Constructs a traversal using the default tracker configuration.
- L67 _public prototype_ `SceneDiscovery(const pxr::UsdStageRefPtr& stage, const DiscoveryOptions& options);` — Constructs a traversal with custom tracker options.
- L70 _public prototype_ `SceneDiscovery(const SceneDiscovery&) = default;`
- L71 _public prototype_ `SceneDiscovery& operator=(const SceneDiscovery&) = default;`
- L72 _public prototype_ `SceneDiscovery(SceneDiscovery&&) = default;`
- L73 _public prototype_ `SceneDiscovery& operator=(SceneDiscovery&&) = default;`
- L79 _public prototype_ `TargetDataRefPtr GetTargetData(const TargetUid& targetUid);` — The provided identifier must originate from the results returned by TraverseAndFindTargets.
- L87 _public prototype_ `bool TraverseAndFindTargets(ResultMap& results);` — Returns false if traversal encountered fatal tracking errors.
- L93 _public prototype_ `bool SaveDiscoveryData(const std::string& filename);` — This layer contains serialized target and definition data collected during traversal.
- L97 _private prototype_ `void _Traverse(const pxr::UsdPrim& prim);`
- L100 _private member_ `pxr::UsdStageRefPtr _stage;` — The stage being traversed.
- L103 _private member_ `SceneTrackerRefPtr _tracker;` — SceneTracker responsible for asset discovery and permutation management.

#### Free symbols / members of external scopes

- L19 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L30 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/sceneTracker.h` (Public)


#### class `TrackedPrim`  
`class TrackedPrim`  
_L148-246_
- desc: TrackedPrim behaves similarly to scoped guard types such as std::lock_guard or UsdEditContext. It is non-copyable and may only be move-constructed.
- L154 _public prototype_ `TrackedPrim(TrackedPrim&&) noexcept;` — Move construction is supported so the object can be returned directly from SceneTracker APIs.
- L156 _public prototype_ `TrackedPrim& operator=(TrackedPrim&&) = delete;`
- L157 _public prototype_ `TrackedPrim(const TrackedPrim&) = delete;`
- L158 _public prototype_ `TrackedPrim& operator=(const TrackedPrim&) = delete;`
- L161 _public prototype_ `~TrackedPrim();` — Finalizes tracking for the prim and restores tracker state.
- L165 _public prototype_ `bool HasUnprocessedPermutations() const;` — Returns true if additional permutations remain to be processed.
- L174 _public prototype_ `bool PrepareNextPermutation();` — Returns false when no further permutations remain.
- L176 _public prototype_ `explicit operator bool() const noexcept;`
- L229 _private prototype_ `TrackedPrim();`
- L231 _private prototype_ `TrackedPrim(const pxr::UsdPrim& prim, std::shared_ptr<class SceneTracker> tracker);`
- L234 _private prototype_ `bool _IsUsdPrimValid() const;`
- L237 _private member_ `pxr::UsdPrim _prim;` — The USD prim currently being tracked.
- L240 _private member_ `SceneTrackerWeakPtr _tracker;` — Weak reference to the owning tracker.
- L243 _private member_ `std::optional<_PermutationState> _permState = std::nullopt;` — The permutations and current index
- L245 _private member_ `mutable _Phase _phase = _Phase::Invalid;`

#### enum `TrackedPrim::_Phase`  
`enum class _Phase : uint8_t`  
_L207-214_
- desc: Completed All permutations have been processed and the prim's tracking lifecycle is complete.
- L209 _public enumerator_ `Invalid = 0`
- L210 _public enumerator_ `Started = 1`
- L211 _public enumerator_ `Ready = 2`
- L212 _public enumerator_ `Preparing = 3`
- L213 _public enumerator_ `Completed = 4`

#### struct `TrackedPrim::_PermutationState`  
`struct _PermutationState`  
_L220-227_
- desc: This is stored by value so that permutation iteration remains independent of the SceneTracker's internal traversal stack.
- L223 _public member_ `std::vector<PrimPermutationRefPtr> perms;` — All permutations discovered for this prim.
- L226 _public member_ `std::size_t currentIndex = 0;` — Index of the permutation currently being evaluated.

#### class `SceneTracker`  
`class SceneTracker : public std::enable_shared_from_this<SceneTracker>`  
_L265-585_
- inherits: `std::enable_shared_from_this<SceneTracker>`
- L269 _public typedef_ `using TargetCreatedCallback = std::function< void(const pxr::SdfPath& path, const TargetUid& targetUid) >;`
- L275 _public prototype_ `Create(const pxr::UsdStageRefPtr& stage);`
- L279 _public prototype_ `Create(const pxr::UsdStageRefPtr& stage, const DiscoveryOptions& options);`
- L282 _public prototype_ `const DiscoveryOptions& GetOptions() const;` — Returns the tracker configuration.
- L296 _public prototype_ `pxr::SdfPath GetInitialPath() const;` — Specifying a non-root initial path limits discovery to that subtree. Ancestor assets that would normally be discovered will be skipped and so this is not intended as a general-purpose filtering mechanism. To filter prims, implement the logic in the discovery plugin’s PrunePrim() method.
- L301 _public prototype_ `TargetDataRefPtr GetTargetData(const TargetUid& targetId) const;` — The identifier must originate from the target created callback.
- L304 _public prototype_ `bool HasErrors() const;` — Returns true if errors were encountered during tracking.
- L307 _public prototype_ `bool SaveDataLayer(const std::string& filename) const;` — Saves the internal Sdf data layer representation to disk.
- L315 _public prototype_ `TrackedPrim StartTrackingPrim(const pxr::UsdPrim& prim);` — The current implementation requires prims to be visited strictly in parent-to-child namespace order. Invoking this function on prims out of traversal order will lead to undefined behavior.
- L318 _public prototype_ `void SetTargetCreatedCallback(const TargetCreatedCallback& callback);` — Registers a callback invoked whenever a new target is created.
- L321 _public prototype_ `void RemoveTargetCreatedCallback();` — Removes the active target created callback.
- L327 _private typedef_ `using _PurposeMask = std::uint8_t;`
- L424 _private prototype_ `SceneTracker(const pxr::UsdStageRefPtr& stage);`
- L426 _private prototype_ `SceneTracker(const pxr::UsdStageRefPtr& stage, const DiscoveryOptions& options, const DiscoveryPluginRefPtr& discoveryPlugin);`
- L430 _private prototype_ `void _SetInitialPath();`
- L436 _private prototype_ `void _AddPrimPermutations(const pxr::UsdPrim& prim);`
- L438 _private prototype_ `_PermutationApplyResult _ApplyPermutationOps(const PrimPermutationRefPtr& perm);`
- L440 _private prototype_ `std::vector<PrimPermutationRefPtr> _GetCurrentPermutations(const pxr::UsdPrim& prim);`
- L442 _private prototype_ `types::int32 _GetNextPermutationIndex() const;`
- L444 _private prototype_ `bool _HasUnprocessedPermutations(const pxr::UsdPrim& prim) const;`
- L446 _private prototype_ `_PrimPermutationState* _FindPrimPermutationState(const pxr::SdfPath& path);`
- L448 _private prototype_ `const _PrimPermutationState* _FindPrimPermutationState(const pxr::SdfPath& path) const;`
- L454 _private prototype_ `const ExtAssetDefinition* _GetDefinitionFromPlugin(const pxr::UsdPrim& prim);`
- L456 _private prototype_ `const ExtAssetDefinition* _CreateRootDefinition(const pxr::UsdPrim& prim);`
- L458 _private prototype_ `void _CreateAndPushNewItem(const pxr::UsdPrim& prim, const ExtAssetDefinition* assetDefn);`
- L461 _private prototype_ `internal::Item* _GetCurrentItem();`
- L463 _private prototype_ `const internal::Item* _GetCurrentItem() const;`
- L465 _private prototype_ `bool _PushAsset(const pxr::UsdPrim& prim, const ExtAssetDefinition* assetDefn);`
- L467 _private prototype_ `void _PushPermutation(const PrimPermutationRefPtr& perm);`
- L469 _private prototype_ `void _PopAssetOrPermutation(const pxr::SdfPath& primPath);`
- L471 _private prototype_ `void _PopPurpose();`
- L478 _private prototype_ `void _GatherPrimData(const pxr::UsdPrim& prim);`
- L480 _private prototype_ `types::int32 _GetOverrideDepthForSpec( const pxr::PcpPrimIndex& index, const pxr::SdfPrimSpecHandle& spec) const;`
- L506 _private prototype_ `void _BlockNewlyDiscoveredVariantSets(const pxr::UsdPrim& prim);` — Blocks variant sets that have not yet been seen by the permutation state for this prim. Each time a discovery plugin reports variant sets for a prim in all-permutations mode, there are two scenarios: 1. The variant set is being reported for the first time, and its variants have not yet been visited (composed and traversed). 2. The variant set is already active, because the tracker has applied permutation ops that select it. For (1), we must block newly discovered variant sets so that their selections are not incorporated into the scene description we are inspecting. This effectively gives us a clean starting state. This is especially important for nested variants, where multiple variants that appear as siblings when queried via GetVariantSets may actually be nested—blocking one can cause others to disappear entirely. For (2), it is important that we do not block these variant sets, as they are already contributing to the composed scene state. The _PrimPermutationState structure maintains a list of variant sets it has blocked, and only applies blocking to those not already in the list.
- L513 _private prototype_ `bool _ScopeMatchesAuthoredPermutation(const internal::ItemScope* itemScope) const;` — Returns true if the given scope represents the original authored permutation state of the supplied stage (i.e. before any permutations were applied)  This is only needed right now so that the LayerWriter is able to author a mirror of the supplied scene hierarchy into the discovery data layer (which is purely for diagnostic purposes).
- L515 _private prototype_ `pxr::TfSpan<internal::Item*> _MakeItemView() const;`
- L517 _private prototype_ `std::string _MakeAssetHierarchyString() const;`
- L519 _private prototype_ `void _TrackPurpose(const pxr::UsdPrim& prim);`
- L521 _private prototype_ `static _PurposeMask _ToPurposeMask(const pxr::TfToken& purpose);`
- L526 _private member_ `pxr::UsdStageRefPtr _stage;` — The input stage to track
- L529 _private member_ `DiscoveryOptions _options;` — SceneTracker option configuration
- L532 _private member_ `DiscoveryPluginRefPtr _discoveryPlugin = nullptr;` — The active discovery plugin.
- L540 _private member_ `pxr::SdfPath _initialPath;` — The starting path for tracking purposes. Because overrides will get assigned using the asset definition hierarchy, a single initial path associated with a definition is important so that stage-level overrides can be associated with a definition uid. The ideal setup case is when the discovery plugin is able to provide a definition for the initial path. If not we must create one.
- L542 _private member_ `pxr::SdfPath _firstTrackedPath;`
- L546 _private member_ `std::vector<std::unique_ptr<internal::Item>> _itemStack;` — List of items that get pushed/popped as asset definitions are found and associated with the stages namespace.
- L549 _private member_ `std::vector<_PurposeInfo> _purposeStack;`
- L550 _private member_ `_PurposeMask _allowedPurposeMask = 0;`
- L554 _private member_ `std::unordered_map<std::string, _IdentifierEntry> _identifierInfo;` — Table used to accelerate resolved asset identifiers to their associated position in the item stack.
- L557 _private member_ `pxr::SdfPathSet _visitedScenePaths;` — Visited scene paths used to identify new paths.
- L562 _private member_ `std::unordered_map<pxr::SdfPath, std::unique_ptr<_PrimPermutationState>, pxr::TfHash> _permState;` — Permutation states, keyed by path.
- L565 _private member_ `std::unique_ptr<internal::LayerWriter> _writer;` — The layer that stores the discovered definitions and targets.
- L570 _private member_ `_ErrorMark _errorMark;` — Mark the depth of the most recent path that produced an invalid asset definition or a failed push. This is required to avoid tracking invalid chunks of namespace.
- L573 _private member_ `mutable std::vector<internal::Item*> _itemStore;` — Reusable storage to construct a view of the current item stack.
- L576 _private member_ `std::unordered_set<pxr::TfToken, pxr::TfHash> _invalidCategories;` — Invalid category names supplied by the discovery plugin, if any.
- L584 _private member_ `TargetCreatedCallback _targetCreatedCallback;` — Callback invoked whenever a target becomes fully resolved. This callback is currently invoked when the item or item scope is popped, in order to ensure that overrides on descendant prims are fully captured. In the future however, we will want the ability for users to opt out of override collection, or provide a list of known overrides up-front, so that targets can be generated without fully visiting all descendant prims.

#### enum `SceneTracker::_PermutationApplyResult`  
`enum class _PermutationApplyResult : uint8_t`  
_L329-334_
- L331 _public enumerator_ `InProgress`
- L332 _public enumerator_ `Completed`
- L333 _public enumerator_ `Invalid`

#### class `SceneTracker::_ErrorMark`  
`class _ErrorMark`  
_L341-374_
- desc: Helper class for tracking error regions in namespace traversal. TODO: This currently invalidates the entire prim and its subtree, which works in general. However, if an error occurs within a specific permutation, there is no way to invalidate just that permutation while keeping the prim and its other permutations usable.
- L343 _private member_ `std::optional<std::size_t> _errDepth = std::nullopt;`
- L344 _private member_ `pxr::SdfPathSet _paths;`
- L348 _public function_ `void Set(const pxr::SdfPath& path)`
- L354 _public function_ `bool Check(const pxr::SdfPath& path)`
- L371 _public function_ `bool HasErrors() const`

#### struct `SceneTracker::_IdentifierEntry`  
`struct _IdentifierEntry`  
_L376-380_
- L378 _public member_ `pxr::SdfPath scenePath;`
- L379 _public member_ `types::int32 assetDepth;`

#### struct `SceneTracker::_PrimPermutationState`  
`struct _PrimPermutationState`  
_L387-410_
- desc: Bundles the state required to track and resolve permutations for a specific prim. When visiting a prim, the tracker will create an instance of this struct (mapped by prim path) if either GetCurrentPrimPermutation or GetPrimPermutations on the discovery plugin return a non-empty result.
- L390 _public prototype_ `_PrimPermutationState(const PrimPermutationConstRefPtr& authoredPerm);` — Create a state and authored permutation, but no permutation set.
- L393 _public prototype_ `_PrimPermutationState(const pxr::SdfPath& path);` — Create permutation set for the given path, but no authored permutation.
- L396 _public prototype_ `bool HasAuthoredPermutation() const;` — Return true if the state has a valid authored permutation.
- L399 _public prototype_ `bool HasPermutationSet() const;` — Return true if the state has a valid permutation set.
- L403 _public member_ `PrimPermutationConstRefPtr authoredPerm = nullptr;` — The originally composed permutation, required so that the tracker can distinguish between a prim in its original and modified state.
- L406 _public member_ `internal::PrimPermutationSetPtr permSet = nullptr;` — The full set of possible permutations, as they are discovered.
- L409 _public member_ `std::set<std::string> blockedVariantSets;` — Variant sets blocked during previous iterations.

#### struct `SceneTracker::_PurposeInfo`  
`struct _PurposeInfo`  
_L412-418_
- L414 _public member_ `pxr::TfToken purpose;`
- L415 _public member_ `bool hasAuthoredPurpose = false;`
- L416 _public member_ `_PurposeMask mask = 0;`
- L417 _public member_ `bool isIncluded = true;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L41 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L42 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L48 _namespace_ `namespace internal`
- L54 _typedef_ `using PrimPermutationSetPtr = std::unique_ptr<PrimPermutationSet>;` (scope `internal`)
- L60 _typedef_ `using PrimPermutationRefPtr = std::shared_ptr<class PrimPermutation>;`
- L61 _typedef_ `using PrimPermutationConstRefPtr = std::shared_ptr<const class PrimPermutation>;`
- L62 _typedef_ `using TargetDataRefPtr = std::shared_ptr<class TargetData>;`
- L64 _typedef_ `using SceneTrackerRefPtr = std::shared_ptr<class SceneTracker>;`
- L65 _typedef_ `using SceneTrackerWeakPtr = std::weak_ptr<class SceneTracker>;`
- L67 _typedef_ `using DiscoveryPluginRefPtr = std::shared_ptr<class DiscoveryPlugin>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/storageOptions.h` (Public)


#### struct `StorageOptions`  
`struct StorageOptions`  
_L32-69_
- desc: Example: StorageOptions options; options.storagePluginName = "json_storage"; options.manifestDir = "/tmp/manifests"; options.packageSubPathTemplate = "assets/${DEFINITION_NAME}/${PERMUTATION_ID}"; auto storage = StoragePluginRegistry::GetInstance().Create(options);
- L38 _public member_ `std::string storagePluginName;` — Name of the storage plugin to use. An empty string will use the built-in JSON plugin ("json_storage"). The registry looks the name up in its factory map to construct the right plugin implementation.
- L49 _public member_ `std::string manifestDir;` — Empty => plugin default (JsonStoragePlugin falls back to the USDPREGEN_DEFAULT_STORAGE_DIR environment variable, and then to "<HOME>/UE_UsdPregen_Manifests").
- L62 _public member_ `std::string packageSubPathTemplate;` — Empty => plugin default (StoragePlugin::DefaultPackageSubPathTemplate).
- L64 _public prototype_ `bool operator==(const StorageOptions& rhs) const;`
- L66 _public prototype_ `bool operator!=(const StorageOptions& rhs) const;`
- L68 _public prototype_ `std::string DumpToString() const;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define PREGEN_API USDPREGENCORE_API`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/storagePlugin.h` (Public)


#### class `StoragePlugin`  
`class StoragePlugin`  
_L54-223_
- desc: StoragePlugin is intentionally stateless with respect to traversal. Each request operates independently based solely on the supplied target identifier.
- L58 _public prototype_ `StoragePlugin(const StorageOptions& options = {});`
- L60 _public prototype_ `virtual ~StoragePlugin();`
- L68 _public prototype_ `virtual bool Initialize();` — \return Returns true on success, or false if initialization failed.
- L82 _public prototype_ `virtual bool Shutdown();` — \return Returns true on success, or false if clean shutdown failed.
- L95 _public prototype_ `LoadManifestPayload(const TargetUid& targetUid) = 0;`
- L109 _public prototype_ `StoreManifestPayload(const TargetUid& targetUid, const ManifestPayload& payload) = 0;`
- L122 _public prototype_ `PersistManifestPayload(const TargetUid& targetUid);`
- L128 _public prototype_ `SerializeManifest(const Manifest& manifest) = 0;`
- L134 _public prototype_ `DeserializeManifestPayload(const ManifestPayload& payload) = 0;`
- L141 _public prototype_ `GetNameForUAsset(const TargetUid& targetUid, const std::vector<const ExtAssetDefinition*>& definitions, const std::string& assetType) = 0;`
- L151 _public prototype_ `GetPackageSubPathForUAsset(const TargetUid& targetUid, const std::vector<const ExtAssetDefinition*>& definitions, const std::string& assetType) = 0;`
- L162 _public prototype_ `GetPathForManifest(const TargetUid& targetUid) = 0;`
- L168 _public prototype_ `static const std::string& DefaultPackageSubPathTemplate();` — Default template used by ResolvePackageSubPathTemplate when no explicit template is provided. Matches the layout the built-in plugins used before the template became configurable, e.g. "assets/tree_02/versions/v01/permutations/2559017893".
- L174 _public prototype_ `static const std::string& EmptyValueSentinel();` — Sentinel substituted for placeholder values that resolve to empty (or to an entirely non-alphanumeric string). Keeps templates like "versions/${DEFINITION_VERSION}/" producing "versions/_/" rather than orphan "versions/" segments when a definition has no version.
- L210 _public prototype_ `ResolvePackageSubPathTemplate( const std::string& templateStr, const TargetUid& targetUid, const std::vector<const ExtAssetDefinition*>& definitions, const std::string& assetType, const std::unordered_map<std::string, std::string>& extraSubstitutions = {} );`
- L218 _public prototype_ `const StorageOptions& GetOptions() const;`
- L222 _private member_ `StorageOptions _options;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L32 _typedef_ `using StoragePluginRefPtr = std::shared_ptr<class StoragePlugin>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/storagePluginRegistry.h` (Public)


#### class `StoragePluginRegistry`  
`class StoragePluginRegistry : public pxr::TfWeakBase`  
_L53-103_
- inherits: `pxr::TfWeakBase`
- desc: StoragePluginRegistry is implemented as a TfSingleton and is accessed through GetInstance().
- L70 _public typedef_ `using FactoryFn = std::function<StoragePlugin*(const StorageOptions& options)>;` — A raw pointer return type is required to support plugin implementations authored in Python.
- L77 _public prototype_ `bool RegisterFactory(const std::string& name, FactoryFn fn);` — Returns true if the factory was successfully registered. If a factory with the same name already exists, registration will fail.
- L88 _public prototype_ `StoragePluginRefPtr Create( const StorageOptions& options ) const;` — Returns nullptr if no plugin has been registered under the requested name.
- L93 _public prototype_ `static StoragePluginRegistry& GetInstance();` — Returns the global StoragePluginRegistry instance.
- L99 _private prototype_ `StoragePluginRegistry();`
- L100 _private prototype_ `~StoragePluginRegistry() = default;`
- L102 _private member_ `std::unordered_map<std::string, FactoryFn> _registry;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L30 _typedef_ `using StoragePluginRefPtr = std::shared_ptr<class StoragePlugin>;`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/target.h` (Public)


#### class `TargetUid`  
`class TargetUid`  
_L48-105_
- desc: TargetUid objects are used as stable identifiers when tracking generated targets and associated manifest entries.
- L53 _public prototype_ `TargetUid() = default;` — Constructs an invalid TargetUid.
- L58 _public prototype_ `TargetUid(const std::string& definitionUid);` — \param definitionUid Unique identifier of the asset definition.
- L64 _public prototype_ `TargetUid(const std::string& definitionUid, const std::string& permutationUid);` — \param definitionUid Unique identifier of the asset definition. \param permutationUid Identifier of the specific permutation.
- L68 _public prototype_ `std::string GetDefinitionUid() const;` — Returns the definition UID string.
- L73 _public prototype_ `std::string GetPermutationUid() const;` — Returns an empty string if no permutation is present.
- L76 _public prototype_ `bool HasPermutationUid() const;` — Returns true if this TargetUid contains a permutation identifier.
- L79 _public prototype_ `std::string GetString() const;` — Returns the UID as a string.
- L82 _public prototype_ `bool IsValid() const;` — Returns true if this TargetUid represents a valid identifier.
- L85 _public prototype_ `explicit operator bool() const noexcept;` — Returns true if this TargetUid is valid.
- L87 _public prototype_ `bool operator==(const TargetUid& rhs) const;`
- L89 _public prototype_ `bool operator!=(const TargetUid& rhs) const;`
- L91 _public prototype_ `bool operator<(const TargetUid& rhs) const;`
- L97 _public prototype_ `static pxr::TfToken ConvertToUsdPrimName(const TargetUid& targetUid);` — Encodes the identifier into a form suitable for use as a prim name within a USD stage.
- L103 _private member_ `pxr::TfToken _definitionUid;`
- L104 _private member_ `pxr::TfToken _permutationUid;`

#### class `TargetDefinitionEntry`  
`class TargetDefinitionEntry`  
_L119-159_
- desc: A TargetDefinitionEntry associates an asset definition with a specific location in the USD scene graph. Multiple TargetDefinitionEntry objects may exist for a single TargetUid if asset definitions are hierarchically nested in namespace.
- L124 _public prototype_ `TargetDefinitionEntry() = default;` — Constructs an empty TargetDefinitionEntry.
- L130 _public prototype_ `TargetDefinitionEntry(const std::string& defnUid, const pxr::SdfPath& scenePath);` — \param defnUid Unique identifier of the asset definition. \param scenePath Path of the prim in the scene where the target occurs.
- L137 _public prototype_ `TargetDefinitionEntry(const std::string& defnUid, const pxr::SdfPath& scenePath, PermutationOpVector permutationOps);` — Used during target data construction to attach the permutation ops that produced this scope of the target.
- L144 _public prototype_ `const ExtAssetDefinition* GetDefinition() const;` — May return nullptr if the definition cannot be resolved.
- L147 _public prototype_ `const pxr::SdfPath& GetScenePath() const &;` — Returns the scene path associated with this target instance.
- L152 _public prototype_ `const PermutationOpVector& GetPermutationOps() const &;` — May be empty when no permutation ops are associated with this scope.
- L156 _private member_ `std::string _defnUid;`
- L157 _private member_ `pxr::SdfPath _scenePath;`
- L158 _private member_ `PermutationOpVector _permutationOps;`

#### class `TargetData`  
`class TargetData`  
_L174-231_
- desc: Instances of TargetData are typically produced during a discovery phase.
- L179 _public prototype_ `TargetData() = default;` — Constructs an invalid TargetData instance.
- L182 _public prototype_ `explicit TargetData(const TargetUid& targetUid);` — Constructs TargetData for the given TargetUid.
- L185 _public prototype_ `bool IsValid() const;` — Returns true if this TargetData instance contains valid data.
- L188 _public prototype_ `explicit operator bool() const noexcept;` — Convenience boolean conversion for validity checks.
- L191 _public prototype_ `TargetUid GetUniqueId() const;` — Returns the unique identifier of this target.
- L194 _public prototype_ `std::size_t NumDefinitionEntries() const;` — Returns the number of TargetDefinitionEntry entries associated with this target.
- L197 _public prototype_ `const TargetDefinitionEntry& GetDefinitionEntry(std::size_t index) const;` — Returns the TargetDefinitionEntry at the given index.
- L200 _public prototype_ `const std::vector<TargetDefinitionEntry>& GetDefinitionEntries() const &;` — Returns the list of TargetDefinitionEntry entries associated with this target.
- L203 _public prototype_ `const std::vector<TargetDefinitionEntry>& GetDefinitionEntries() const && = delete;` — Disallow access on rvalues to prevent dangling references.
- L208 _public prototype_ `pxr::SdfLayerRefPtr GetPermutationOverlay() const;` — May return null if no overlay layer is required.
- L211 _public prototype_ `const std::vector<TargetUid>& GetDependencies() const &;` — Returns the list of target dependencies for this target.
- L217 _public prototype_ `const pxr::SdfPathSet& GetEncapsulatedDefinitionPaths() const &;` — This can be useful for identifying override sources and avoiding processing of fully encapsulated regions of namespace.
- L218 _public prototype_ `const pxr::SdfPathSet& GetUnencapsulatedDefinitionPaths() const &;`
- L225 _private member_ `TargetUid _targetUid;`
- L226 _private member_ `std::vector<TargetDefinitionEntry> _definitionEntries;`
- L227 _private member_ `std::vector<TargetUid> _dependencies;`
- L228 _private member_ `pxr::SdfPathSet _encapsulatedDefinitions;`
- L229 _private member_ `pxr::SdfPathSet _unencapsulatedDefinitions;`
- L230 _private member_ `pxr::SdfLayerRefPtr _permOverlayLayer;`

#### class `internal::TargetDataBuilder`  
`class TargetDataBuilder`  
_L246-263_
- desc: Despite being declared in this public header, TargetDataBuilder lives in the internal:: namespace by design - downstream consumers should treat it as an implementation detail of the manifest storage backends.
- L249 _public prototype_ `explicit TargetDataBuilder(const TargetUid& targetUid);`
- L251 _public prototype_ `void AddInfo(TargetDefinitionEntry info);`
- L253 _public prototype_ `void SetDependencies(std::vector<TargetUid> dependencies);`
- L255 _public prototype_ `void SetEncapsulatedDefinitionPaths(pxr::SdfPathSet paths);`
- L257 _public prototype_ `void SetUnencapsulatedDefinitionPaths(pxr::SdfPathSet paths);`
- L259 _public prototype_ `TargetDataRefPtr Build();`
- L262 _private member_ `TargetDataRefPtr _targetData;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define PREGEN_API USDPREGENCORE_API`
- L29 _namespace_ `namespace internal`
- L108 _prototype_ `std::ostream& operator<<(std::ostream& os, const TargetUid& targetUid);` — Stream output operator for debugging and logging.
- L161 _typedef_ `using TargetDataRefPtr = std::shared_ptr<class TargetData>;`
- L162 _typedef_ `using TargetDataWeakPtr = std::weak_ptr<class TargetData>;`
- L233 _namespace_ `namespace internal`

### `Plugins/Experimental/USDPregen/Source/USDPregenCore/Public/UsdPregen/types.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace types`
- L13 _typedef_ `typedef std::int32_t int32;` (scope `types`)
- L14 _variable_ `inline constexpr int32 InvalidIndex = -1;` (scope `types`)
