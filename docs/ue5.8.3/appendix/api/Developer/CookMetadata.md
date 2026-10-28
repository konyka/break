# Developer / CookMetadata

- module root: `Source/Developer/CookMetadata`
- headers: 1; symbols: 119
- symbol kinds: class=1, enum=5, enumerator=30, function=31, macro=1, member=28, namespace=2, prototype=13, struct=6, typedef=1, variable=1
- PrivateDependencyModuleNames: Core

### `Source/Developer/CookMetadata/Public/CookMetadata.h` (Public)


#### enum `UE::Cook::ECookMetadataStateVersion`  
`enum class ECookMetadataStateVersion : uint8`  
_L19-36_
- L21 _public enumerator_ `InvalidVersion = 0`
- L22 _public enumerator_ `PluginHierarchy = 1`
- L23 _public enumerator_ `PostWritebackHash = 2`
- L24 _public enumerator_ `FixSerialization = 3`
- L25 _public enumerator_ `AddedCustomFields = 4`
- L28 _public enumerator_ `AddedShaderPseudoHierarchy = 5` — Note: This is a lie, the shader data wasn't actually serializing to file, use ActualAddShaderPseudoHierarchy
- L29 _public enumerator_ `AddedPluginEntryType = 6`
- L30 _public enumerator_ `ActualAddShaderPseudoHierarchy = 7`
- L31 _public enumerator_ `AdjustCustomFieldLayout = 8`
- L34 _public enumerator_ `VersionCount` — Add new versions above this.
- L35 _public enumerator_ `LatestVersion = VersionCount - 1`

#### enum `UE::Cook::EPluginSizeTypes`  
`enum class EPluginSizeTypes : uint8`  
_L45-64_
- desc: We classify various bits of the plugin data based on how it will be delivered to the end user in order to more appropriately track the user's experience. Each iostore chunk (note: NOT pak chunk!) gets compressed during staging and unreal pak will update the size for the plugin based on how the chunk gets deployed.
- L49 _public enumerator_ `Streaming` — The iostore chunks will be deployed to servers for downloading on-demand by the game using the Individual Asset Streaming system.
- L52 _public enumerator_ `Installed` — The iostore chunks are written to normal iostore containers that are expected to be distributed with the game. This includes the required global iostore container.
- L58 _public enumerator_ `Optional` — The iostore chunks are written to a separate container that isn't required to be distributed with the game. This is where e.g. OptionalMips go for textures. They appear as .uptnl files in the Cooked directory (if cooking to Loose Files), The CopyBuildToStagingDirectory script manually assigns the iostore chunk to a corresponding pak chunk with the name ending in "optional", e.g. pakChunk0optional.pak/ucas/utoc/sig. The only way to catch this in UnrealPak is to parse the filename.
- L62 _public enumerator_ `OptionalSegment` — These are sidecar files for distributing EditorOnly data for Cooked Editor builds. When cooking to loose files they will contain ".o" inside their filename, e.g. "myasset.o.ubulk". They are never intended to be shipped with a game.
- L63 _public enumerator_ `COUNT`

#### struct `UE::Cook::FPluginSizeInfo`  
`struct FPluginSizeInfo`  
_L67-107_
- L69 _public member_ `uint64 Sizes[EPluginSizeTypesCount] = {};`
- L71 _public function_ `void Zero()`
- L72 _public function_ `void AddSizes(uint64 SizesPerType[EPluginSizeTypesCount])`
- L79 _public function_ `void Add(const FPluginSizeInfo& Other)`
- L86 _public function_ `uint64 TotalSize() const`
- L105 _public function_ `uint64& operator[](EPluginSizeTypes InType)`
- L106 _public function_ `const uint64& operator[](EPluginSizeTypes InType) const`

#### enum `UE::Cook::ECookMetadataSizesPresent`  
`enum class ECookMetadataSizesPresent`  
_L114-126_
- desc: Unrealpak doesn't compress the data for all platforms. In those cases, the data written back during staging isn't compressed and is not representative of the final sizes that occurs after the corresponding SDK tools process them for deployment.
- L117 _public enumerator_ `NotPresent` — staging has not occured, or writeback wasn't enabled in project packaing settings.
- L120 _public enumerator_ `Compressed` — unrealpak compressed the iostore chunks and the data we have is compressed sizes
- L123 _public enumerator_ `Uncompressed` — the selected platform isn't compressed by unrealpak, or package compression was disabled.
- L125 _public enumerator_ `Count`

#### enum `UE::Cook::ECookMetadataPluginType`  
`enum class ECookMetadataPluginType`  
_L128-150_
- L131 _public enumerator_ `Unassigned` — For sanity tracking. All types _should_ be assigned when they are added.
- L133 _public enumerator_ `Normal`
- L136 _public enumerator_ `Root` — Root plugins are used to separate and classify game "modes" within a single project.
- L139 _public enumerator_ `EnginePseudo` — For assets under /Engine
- L142 _public enumerator_ `GamePseudo` — For assets under /Game
- L147 _public enumerator_ `ShaderPseudo` — When a shader is referenced by multiple plugins then it has no natural home for assigning its size. Instead we create a set of shader pseudo plugins based on the set of root plugins referencing the shader, including possibly an "Unrooted" plugin.
- L149 _public enumerator_ `Count`

#### enum `UE::Cook::ECookMetadataCustomFieldType`  
`enum class ECookMetadataCustomFieldType : uint8`  
_L152-159_
- L154 _public enumerator_ `Unknown` — This only happens in the upgrade from an older cook metadata
- L157 _public enumerator_ `Bool` — when there's nowhere to get the information from. This also means that there are no plugins that use this field so you can safely ignore it.
- L158 _public enumerator_ `String`

#### struct `UE::Cook::FCookMetadataPluginEntry`  
`struct FCookMetadataPluginEntry`  
_L162-207_
- desc: The name and dependency information for a plugin that was enabled during cooking.
- L164 _public member_ `FString Name;`
- L166 _public member_ `ECookMetadataPluginType Type = ECookMetadataPluginType::Unassigned;`
- L172 _public typedef_ `typedef TVariant<bool, FString> CustomFieldVariantType;` — These contain values pulled from the uplugin json file and hold fields that are not part of the engine FPluginDescriptor. They are for per-project values. The keys for the maps are indices in to FCookMetadataPluginHierarchy::CustomFieldEntries, where you'll also find what the type is. See the comment for CustomFieldEntries.
- L173 _public member_ `TMap<uint8, CustomFieldVariantType> CustomFields;`
- L184 _public member_ `uint32 DependencyIndexStart = 0;` — The dependencies are stored in the FCookMetadataPluginHierarchy::PluginDependencies array, and this is an index into it. From there you can get a further index into PluginsEnabledAtCook to get the plugin information. Example: for (uint32 DependencyIndex = Plugin->DependencyIndexStart; DependencyIndex < Plugin->DependencyIndexEnd; DependencyIndex++) { const UE::Cook::FCookMetadataPluginEntry& DependentPlugin = PluginHierarchy.PluginsEnabledAtCook[PluginHierarchy.PluginDependencies[DependencyIndex]]; }
- L185 _public member_ `uint32 DependencyIndexEnd = 0;`
- L192 _public member_ `FPluginSizeInfo InclusiveSizes;` — Theses sizes are set during staging by unrealpak if the option in project packaging is set. To determine if they are set, check FCookMetadataState::GetSizesPresent(). Inclusive contains the size of the plugin and all of its dependencies listed in its uplugin file.
- L193 _public member_ `FPluginSizeInfo ExclusiveSizes;`
- L195 _public function_ `uint32 DependencyCount() const`
- L197 _public prototype_ `FText GetPluginTypeAsText() const;`

#### struct `UE::Cook::FCookMetadataPluginHierarchy`  
`struct FCookMetadataPluginHierarchy`  
_L209-270_
- L212 _public member_ `TArray<FCookMetadataPluginEntry> PluginsEnabledAtCook;` — The list of plugins that were enabled during the cook that generated the FCookMetadataState
- L216 _public member_ `TArray<uint16> PluginDependencies;` — The list of plugin dependencies. FCookMetadataPluginEntry::DependencyIndexStart indexes into this array.
- L219 _public member_ `TArray<uint16> RootPlugins;` — The list of root plugins for the project as defined by the Editor.ini file.
- L256 _public function_ `friend FArchive& operator<<(FArchive& Ar, FCustomFieldEntry& Entry)`
- L261 _public member_ `TArray<FCustomFieldEntry> CustomFieldEntries;`

#### struct `UE::Cook::FCookMetadataPluginHierarchy::FCustomFieldEntry`  
`struct FCustomFieldEntry`  
_L252-260_
- desc: The list of custom field names. The values stored on an entry index in to this for the name. These values are copied from the plugins' json descriptor to allow for carrying through project specific data in to the metadata. To enable custom field replication, add the CookMetadataCustomPluginFields section to the relevant Editor.ini file and add to the follow arrays, as desired: BoolFields, StringFields, PerPlatformBoolFields, PerPlatformStringFields Bool and String refer to the json type, and will emit as bool or FString here. The PerPlatform arrays will check in the uplugin json for a field named PerPlatform<ArrayValue>. That field is expected to be an array of override objects. Each object is required to have the platform name and override value. E.g.: [CookMetadataCustomPluginFields] +PerPlatformBoolFields = ExampleProjectBool +StringField = ExampleProjectString Will look in the uplugin file for this: "ExampleProjectBool": true "PerPlatformExampleProjectBool": [ { "Platform": "Windows", "Value": false } ] "ExampleProjectString": "AProjectString" Note that in the per platform case, the base value is not required (i.e. ExampleProjectBool above), however it provides a default value for unlisted platforms. If it does not exist, false is used for bool fields, and an empty string for string fields.
- L254 _public member_ `FString Name;`
- L255 _public member_ `ECookMetadataCustomFieldType Type;`

#### struct `UE::Cook::FCookMetadataShaderPseudoAsset`  
`struct FCookMetadataShaderPseudoAsset`  
_L278-296_
- desc: After staging when sizes are written back we assign the sizes of shaders to these fake assets and we expose a dependency list for "normal" packages that use them. This can be used to determine an inclusive size for packages that also considers shader sizes.
- L286 _public member_ `FString Name;` — This is artificially generated based on the chunk the shader belongs to and its hash. It should be consistent across builds. The plugin the shader is assigned to is based on the packages that reference the shader. If the shader is only referenced by packages within a single plugin, the shader asset will be assigned to that plugin. Otherwise, it will be assigned to a shader pseudo plugin.
- L289 _public member_ `uint32 CompressedSize = 0;` — Shaders are always compressed, independent of what GetSizesPresent() says.

#### struct `UE::Cook::FCookMetadataShaderPseudoHierarchy`  
`struct FCookMetadataShaderPseudoHierarchy`  
_L298-315_
- L300 _public member_ `TArray<FCookMetadataShaderPseudoAsset> ShaderAssets;`
- L304 _public member_ `TArray<int32> DependencyList;` — Entries in this are indices in to ShaderAssets. Use PackageShaderDependencyMap to get a package's shaders.
- L308 _public member_ `TMap<FName, TPair<int32, int32>> PackageShaderDependencyMap;` — Keyed off a PackageName in the project, returns a [start, end) pair of indices into DependencyList for the shaders that package depends on.

#### class `UE::Cook::FCookMetadataState`  
`class FCookMetadataState`  
_L322-411_
- desc: Structure serialized to disk to contain non-asset related metadata about a cook. This should always exist alongside a Development Asset Registry, and to ensure that the pair is not out of sync, users should validate the development asset registry they are using with GetAssociatedDevelopmentAssetRegistryHash().
- L325 _public prototype_ `FCookMetadataState() = default;`
- L326 _public prototype_ `FCookMetadataState(const FCookMetadataState&) = default;`
- L327 _public prototype_ `FCookMetadataState(FCookMetadataState&& Rhs) = default;`
- L328 _public prototype_ `~FCookMetadataState() = default;`
- L330 _public prototype_ `FCookMetadataState& operator=(const FCookMetadataState&) = default;`
- L331 _public prototype_ `FCookMetadataState& operator=(FCookMetadataState&& O) = default;`
- L333 _public function_ `bool IsValid() const`
- L334 _public function_ `void Reset()`
- L336 _public prototype_ `bool Serialize(FArchive& Ar);`
- L337 _public prototype_ `bool ReadFromFile(const FString& FilePath);`
- L338 _public prototype_ `bool SaveToFile(const FString& FilePath);`
- L342 _public function_ `void SetPluginHierarchyInfo(FCookMetadataPluginHierarchy&& InPluginHierarchy)` — Plugin hierarchy information
- L343 _public function_ `const FCookMetadataPluginHierarchy& GetPluginHierarchy() const`
- L346 _public function_ `FCookMetadataPluginHierarchy& GetMutablePluginHierarchy()` — So that unrealpak can update the sizes.
- L365 _public function_ `void SetAssociatedDevelopmentAssetRegistryHash(uint64 InHash)` — Associated DevAR Hash. This is computed by reading the development asset registry file into a memory buffer and calling ComputeHashOfDevelopmentAssetRegistry on the data. Use this to ensure that the files you are working with were produced by the same cook and didn't get out of sync somehow. *IMPORTANT* If asset registry writeback is enabled during staging, then the hash of the development asset registry changes, and you'll need to check against GetAssociatedDevelopmentAssetRegistryHashPostWriteback. If you don't know which one you have, check both - they are both valid. e.g. uint64 CheckHash = GetAssociatedDevelopmentAssetRegistryHash(); bValidDevAr = ComputeHashOfDevelopmentAssetRegistry(MakeMemoryView(SerializedAssetRegistry)) == CheckHash;
- L366 _public function_ `void SetAssociatedDevelopmentAssetRegistryHashPostWriteback(uint64 InHash)`
- L368 _public function_ `uint64 GetAssociatedDevelopmentAssetRegistryHash() const`
- L369 _public function_ `uint64 GetAssociatedDevelopmentAssetRegistryHashPostWriteback() const`
- L371 _public function_ `void SetPlatformAndBuildVersion(const FString& InPlatform, const TCHAR* InBuildVersion)`
- L372 _public function_ `const FString& GetPlatform() const`
- L373 _public function_ `const FString GetBuildVersion() const`
- L375 _public function_ `void SetHordeJobId(FString&& InHordeJobId)`
- L376 _public function_ `const FString& GetHordeJobId() const`
- L378 _public prototype_ `static uint64 ComputeHashOfDevelopmentAssetRegistry(FMemoryView InSerializedDevelopmentAssetRegistry);`
- L382 _public prototype_ `FText GetSizesPresentAsText() const;` — Returns what size information is present in FCookMetadataPluginEntry. This varies based on the platform and settings.
- L383 _public function_ `ECookMetadataSizesPresent GetSizesPresent() const`
- L384 _public function_ `void SetSizesPresent(ECookMetadataSizesPresent InSizesPresent)`
- L386 _public function_ `void SetShaderPseudoHieararchy(FCookMetadataShaderPseudoHierarchy&& InHierarchy)`
- L387 _public function_ `const FCookMetadataShaderPseudoHierarchy& GetShaderPseudoHierarchy() const`
- L390 _private member_ `ECookMetadataStateVersion Version = ECookMetadataStateVersion::InvalidVersion;`
- L391 _private member_ `FCookMetadataPluginHierarchy PluginHierarchy;`
- L393 _private member_ `FCookMetadataShaderPseudoHierarchy ShaderPseudoHierarchy;`
- L395 _private member_ `uint64 AssociatedDevelopmentAssetRegistryHash = 0;`
- L399 _private member_ `uint64 AssociatedDevelopmentAssetRegistryHashPostWriteback = 0;` — Asset registry size writeback changes the AR, so we have a separate hash for that DevAR that this also matches.
- L401 _private member_ `FString Platform;`
- L404 _private member_ `FString BuildVersion;` — BUILD_VERSION definition from definitions.h for the cook.
- L407 _private member_ `FString HordeJobId;` — If cooked on Horde, this is the job id that cooked it.
- L410 _private member_ `ECookMetadataSizesPresent SizesPresent = ECookMetadataSizesPresent::NotPresent;` — Updated by unrealpak when plugin size information is added.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COOKMETADATA_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cook` (scope `UE`)
- L65 _variable_ `constexpr uint8 EPluginSizeTypesCount = (uint8)EPluginSizeTypes::COUNT;` (scope `UE::Cook`)
- L96 _function_ `friend FArchive& operator<<(FArchive& Ar, FPluginSizeInfo& SizeInfo)` (scope `UE::Cook`)
- L200 _function_ `friend FArchive& operator<<(FArchive& Ar, FCookMetadataPluginEntry& Entry)` (scope `UE::Cook`) — !!! If you edit this, be sure to update the upgrade paths in CookMetadata.cpp
- L264 _function_ `friend FArchive& operator<<(FArchive& Ar, FCookMetadataPluginHierarchy& Hierarchy)` (scope `UE::Cook`) — !!! If you edit this, be sure to update the upgrade paths in CookMetadata.cpp
- L291 _function_ `friend FArchive& operator<<(FArchive& Ar, FCookMetadataShaderPseudoAsset& PseudoAsset)` (scope `UE::Cook`)
- L310 _function_ `friend FArchive& operator<<(FArchive& Ar, FCookMetadataShaderPseudoHierarchy& PseudoHierarchy)` (scope `UE::Cook`)
- L413 _prototype_ `const FString& GetCookMetadataFilename();` (scope `UE::Cook`)
