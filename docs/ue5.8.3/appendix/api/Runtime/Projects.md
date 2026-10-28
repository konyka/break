# Runtime / Projects

- module root: `Source/Runtime/Projects`
- headers: 19; symbols: 728
- symbol kinds: class=8, delegate=8, enum=10, enumerator=61, function=40, member=176, namespace=18, prototype=391, struct=14, typedef=2
- PrivateDependencyModuleNames: DesktopPlatform
- PublicDependencyModuleNames: Core, Json

### `Source/Runtime/Projects/Internal/ICoreUObjectPluginManager.h` (Internal)


#### class `UE::PluginManager::Private::ICoreUObjectPluginManager`  
`class ICoreUObjectPluginManager`  
_L12-23_
- desc: @brief Interface to get around dependency problems between Projects and CoreUObject interface allows CoreUObject to run login in PluginManager that Projects can't run
- L15 _public prototype_ `virtual void OnPluginLoad(IPlugin& Plugin) = 0;`
- L16 _public prototype_ `virtual void OnPluginUnload(IPlugin& Plugin) = 0;`
- L21 _public prototype_ `virtual void SuppressPluginUnloadGC() = 0;` — API for deferring calls to CollectGarbage (and leak detection).
- L22 _public prototype_ `virtual void ResumePluginUnloadGC() = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PluginManager` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::PluginManager`)
- L25 _prototype_ `void SetCoreUObjectPluginManager(ICoreUObjectPluginManager& Handler);` (scope `UE::PluginManager::Private`)

### `Source/Runtime/Projects/Private/JsonExtensions.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace JsonExtensions`
- L10 _function_ `inline bool TryGetStringArrayFieldWithDeprecatedFallback(const FJsonObject& JsonObject, const FString& FieldName, const FString& DeprecatedFieldName, TArray<FString>& OutArray)` (scope `JsonExtensions`) — Get the field named FieldName as an array of strings. Returns false if it doesn't exist or any member cannot be converted.
- L29 _function_ `template<typename TEnum> inline bool TryGetEnumArrayFieldWithDeprecatedFallback(const FJsonObject& JsonObject, const FString& FieldName, const FString& DeprecatedFieldName, TArray<TEnum>& OutArray)` (scope `JsonExtensions`) — Get the field named FieldName as an array of enums. Returns false if it doesn't exist or any member is not a string.

### `Source/Runtime/Projects/Private/PluginManager.h` (Private)


#### class `FPlugin`  
`class FPlugin final : public IPlugin`  
_L15-152_
- inherits: `IPlugin`
- desc: Instance of a plugin in memory
- L19 _public member_ `FString Name;` — The name of the plugin
- L22 _public member_ `FString FileName;` — The filename that the plugin was loaded from
- L25 _public member_ `TArray<FString> PluginExtensionFileNameList;` — The filenames from which any child plugins that have been merged were loaded
- L28 _public member_ `FPluginDescriptor Descriptor;` — The plugin's settings
- L31 _public member_ `EPluginType Type;` — Type of plugin
- L34 _public member_ `bool bEnabled : 1;` — True if the plugin is marked as enabled
- L43 _public member_ `bool bIsMounted : 1;` — True if this plugin has been mounted/loaded. A 'mounted' plugin is one whose content has been registered, and modules set to load. NOTE: Usually plugins are 'enabled' and 'mounted' at the same time, with the exception of 'ExplicitlyLoaded' plugins (which can be set 'enabled' but not mounted until much later)
- L49 _public member_ `uint8 ExplicitlyLoadedLocalizationDataMountedRefCount = 0;` — >0 if an explicitly loaded plugin has also mounted its localization data. @note Unused for non-explicitly loaded plugins.
- L54 _public prototype_ `FPlugin(const FString &FileName, const FPluginDescriptor& InDescriptor, EPluginType InType);` — FPlugin constructor
- L59 _public prototype_ `virtual ~FPlugin();` — Destructor.
- L62 _public function_ `virtual const FString& GetName() const override` — IPlugin interface
- L67 _public function_ `virtual const FString& GetFriendlyName() const override`
- L72 _public function_ `virtual const FString& GetDescriptorFileName() const override`
- L77 _public prototype_ `virtual FString GetBaseDir() const override;`
- L78 _public prototype_ `virtual TArray<FString> GetExtensionBaseDirs() const override;`
- L79 _public prototype_ `virtual FString GetContentDir() const override;`
- L80 _public prototype_ `virtual FString GetMountedAssetPath() const override;`
- L82 _public function_ `virtual bool IsEnabled() const override`
- L87 _public prototype_ `virtual bool IsEnabledByDefault(bool bAllowEnginePluginsEnabledByDefault) const override;`
- L89 _public function_ `virtual bool IsMounted() const override`
- L94 _public function_ `virtual bool IsHidden() const override`
- L99 _public function_ `virtual bool CanContainContent() const override`
- L104 _public function_ `virtual bool CanContainVerse() const override`
- L109 _public function_ `virtual const FString& GetVersePath() const override`
- L114 _public function_ `virtual TOptional<uint32> GetVerseVersion() const override`
- L119 _public function_ `virtual const FString& GetDeprecatedEngineVersion() const override`
- L124 _public function_ `virtual bool IsSceneGraphEnabled() const override`
- L129 _public function_ `virtual bool IsSceneGraphAnimationEnabled() const override`
- L134 _public function_ `virtual bool IsRootPlugin() const override`
- L139 _public function_ `virtual EPluginType GetType() const override`
- L144 _public prototype_ `virtual EPluginLoadedFrom GetLoadedFrom() const override;`
- L145 _public prototype_ `virtual const FPluginDescriptor& GetDescriptor() const override;`
- L146 _public prototype_ `virtual bool UpdateDescriptor(const FPluginDescriptor& NewDescriptor, FText& OutFailReason) override;`
- L148 _public prototype_ `virtual const TSharedPtr<FJsonObject>& GetDescriptorJson() override;`
- L151 _public function_ `void SetIsMounted(bool bInIsMounted)`

#### class `FPluginManager`  
`class FPluginManager final : public IPluginManager`  
_L157-437_
- inherits: `IPluginManager`
- desc: FPluginManager manages available code and content extensions (both loaded and not loaded.)
- L161 _public prototype_ `FPluginManager();` — Constructor
- L164 _public prototype_ `~FPluginManager();` — Destructor
- L167 _public prototype_ `virtual void RefreshPluginsList() override;` — IPluginManager interface
- L168 _public prototype_ `virtual bool AddToPluginsList(const FString& PluginFilename, FText* OutFailReason = nullptr) override;`
- L169 _public prototype_ `virtual bool RemoveFromPluginsList(const FString& PluginFilename, FText* OutFailReason = nullptr) override;`
- L170 _public prototype_ `virtual bool LoadModulesForEnabledPlugins( const ELoadingPhase::Type LoadingPhase ) override;`
- L171 _public prototype_ `virtual FLoadingModulesForPhaseEvent& OnLoadingPhaseComplete() override;`
- L172 _public prototype_ `virtual ELoadingPhase::Type GetLastCompletedLoadingPhase() const override;`
- L173 _public prototype_ `virtual void GetLocalizationPathsForEnabledPlugins( TArray<FString>& OutLocResPaths ) override;`
- L174 _public prototype_ `virtual void SetRegisterMountPointDelegate( const FRegisterMountPointDelegate& Delegate ) override;`
- L175 _public prototype_ `virtual void SetUnRegisterMountPointDelegate( const FRegisterMountPointDelegate& Delegate ) override;`
- L176 _public prototype_ `virtual bool AreRequiredPluginsAvailable() override;`
- L177 _public prototype_ `virtual FGetExplanationForUnavailablePackageWithPluginInfoDelegate& GetExplanationForUnavailablePackageWithPluginInfoDelegate() override;`
- L179 _public prototype_ `virtual void SuppressPluginUnloadGC() override;`
- L180 _public prototype_ `virtual void ResumePluginUnloadGC() override;`
- L183 _public prototype_ `virtual bool CheckModuleCompatibility(TArray<FString>& OutIncompatibleModules, TArray<FString>& OutIncompatibleEngineModules) override;`
- L185 _public prototype_ `virtual TSharedPtr<IPlugin> FindPlugin(const FStringView Name) override;`
- L186 _public function_ `virtual TSharedPtr<IPlugin> FindPlugin(const ANSICHAR* Name) override`
- L191 _public prototype_ `virtual TSharedPtr<IPlugin> FindPluginFromPath(const FString& PluginPath) override;`
- L192 _public prototype_ `virtual TSharedPtr<IPlugin> FindPluginFromDescriptor(const FPluginReferenceDescriptor& PluginDesc) override;`
- L194 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPlugin(const FStringView Name) override;`
- L195 _public function_ `virtual TSharedPtr<IPlugin> FindEnabledPlugin(const ANSICHAR* Name) override`
- L200 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPluginFromPath(const FString& PluginPath) override;`
- L201 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPluginFromDescriptor(const FPluginReferenceDescriptor& PluginDesc) override;`
- L203 _public prototype_ `virtual bool CanEnablePluginInCurrentTarget(const FStringView Name) override;`
- L204 _public function_ `virtual bool CanEnablePluginInCurrentTarget(const ANSICHAR* Name) override`
- L210 _public prototype_ `virtual void FindPluginsUnderDirectory(const FString& Directory, TArray<FString>& OutPluginFilePaths) override;`
- L212 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPlugins() override;`
- L213 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPluginsWithContent() const override;`
- L214 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPluginsWithVerse() const override;`
- L215 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPluginsWithContentOrVerse() const override;`
- L216 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetDiscoveredPlugins() override;`
- L218 _public prototype_ `virtual const TSet<FString>& GetPluginsEnabledAtStartup() const override;`
- L220 _public prototype_ `virtual const TSet<FString>& GetBuiltInPluginNames() const override;`
- L221 _public prototype_ `virtual TSharedPtr<IPlugin> GetModuleOwnerPlugin(FName ModuleName) const override;`
- L224 _public prototype_ `virtual bool AddPluginSearchPath(const FString& ExtraDiscoveryPath, bool bRefresh = true) override;`
- L225 _public prototype_ `virtual bool RemovePluginSearchPath(const FString& PathToRemove, bool bRefresh = true) override;`
- L226 _public prototype_ `virtual const TSet<FString>& GetAdditionalPluginSearchPaths() const override;`
- L227 _public prototype_ `virtual void GetExternalPluginSources(TSet<FExternalPluginPath>& OutPluginSources) const override;`
- L228 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetPluginsWithPakFile() const override;`
- L229 _public prototype_ `virtual FNewPluginMountedEvent& OnNewPluginCreated() override;`
- L230 _public prototype_ `virtual FNewPluginMountedEvent& OnNewPluginMounted() override;`
- L231 _public prototype_ `virtual FNewPluginMountedEvent& OnNewPluginContentMounted() override;`
- L232 _public prototype_ `virtual FNewPluginMountedEvent& OnPluginEdited() override;`
- L233 _public prototype_ `virtual FNewPluginMountedEvent& OnPluginUnmounted() override;`
- L234 _public prototype_ `virtual void MountNewlyCreatedPlugin(const FString& PluginName) override;`
- L235 _public prototype_ `virtual bool MountExplicitlyLoadedPlugin(const FString& PluginName, ELoadingPhase::Type MaxLoadingPhase = ELoadingPhase::Max) override;`
- L236 _public prototype_ `virtual bool MountExplicitlyLoadedPlugin_FromFileName(const FString& PluginFileName) override;`
- L237 _public prototype_ `virtual bool MountExplicitlyLoadedPlugin_FromDescriptor(const FPluginReferenceDescriptor& PluginDescriptor) override;`
- L238 _public prototype_ `virtual bool MountExplicitlyLoadedPluginLocalizationData(const FString& PluginName, TUniqueFunction<void(bool bLoadedLocalization, const FString& PluginName)>&& Notification = nullptr) override;`
- L239 _public prototype_ `virtual bool UnmountExplicitlyLoadedPluginLocalizationData(const FString& PluginName, TUniqueFunction<void(bool bUnloadedLocalization, const FString& PluginName)>&& Notification = nullptr) override;`
- L240 _public function_ `virtual bool UnmountExplicitlyLoadedPlugin(const FString& PluginName, FText* OutReason) override`
- L241 _public prototype_ `virtual bool UnmountExplicitlyLoadedPlugin(const FString& PluginName, FText* OutReason, bool bAllowUnloadCode) override;`
- L242 _public prototype_ `virtual bool GetPluginDependencies(const FString& PluginName, TArray<FPluginReferenceDescriptor>& PluginDependencies) override;`
- L243 _public prototype_ `virtual bool GetPluginDependencies_FromFileName(const FString& PluginFileName, TArray<FPluginReferenceDescriptor>& PluginDependencies) override;`
- L244 _public prototype_ `virtual bool GetPluginDependencies_FromDescriptor(const FPluginReferenceDescriptor& PluginDescriptor, TArray<FPluginReferenceDescriptor>& PluginDependencies) override;`
- L245 _public prototype_ `virtual FName PackageNameFromModuleName(FName ModuleName) override;`
- L246 _public prototype_ `virtual void EnumerateVersePathMountPoints(const UE::Core::FVersePath& VersePath, TFunctionRef<bool(FStringView , FStringView )> Callback) override;`
- L247 _public prototype_ `virtual bool RequiresTempTargetForCodePlugin(const FProjectDescriptor* ProjectDescriptor, const FString& Platform, EBuildConfiguration Configuration, EBuildTargetType TargetType, FText& OutReason) override;`
- L249 _public prototype_ `virtual void SetBinariesRootDirectories(const FString& EngineBinariesRootDir, const FString& ProjectBinariesRootDir) override;`
- L250 _public prototype_ `virtual void SetPreloadBinaries() override;`
- L251 _public prototype_ `virtual bool GetPreloadBinaries() override;`
- L252 _public prototype_ `virtual FLeakedPackagesFoundEvent& OnLeakedPackagesFound() override;`
- L254 _public prototype_ `void GetExplanationForUnavailablePackage(const FName& UnavailablePackageName, FStringBuilderBase& InOutExplanation) override;`
- L257 _private typedef_ `using FDiscoveredPluginMap = TMap<FString, TArray<TSharedRef<FPlugin>>>;`
- L263 _private prototype_ `void DiscoverAllPlugins();` — Searches for all plugins on disk and builds up the array of plugin objects.  Doesn't load any plugins. This is called when the plugin manager singleton is first accessed.
- L288 _private prototype_ `void FindCompileTimePlugins(FPluginDiscoveryContext& Context);`
- L289 _private prototype_ `bool FindCommandLinePlugins(FPluginDiscoveryContext& Context);`
- L290 _private prototype_ `bool FindTargetPlugins(FPluginDiscoveryContext& Context);`
- L291 _private prototype_ `bool FindProgramPlugins(FPluginDiscoveryContext& Context);`
- L292 _private prototype_ `void MarkEnabledPlugins(FPluginDiscoveryContext& Context);`
- L293 _private prototype_ `void ProcessEnabledPlugins(FPluginDiscoveryContext& Context);`
- L294 _private prototype_ `void MountContentPlugins(FPluginDiscoveryContext& Context);`
- L297 _private prototype_ `static void ReadAllPlugins(FDiscoveredPluginMap& Plugins, const TSet<FString>& ExtraSearchPaths, TArray<FString>* OutPluginSources=nullptr);` — Reads all the plugin descriptors
- L301 _private prototype_ `static void ReadPluginsInDirectory(const FString& PluginsDirectory, const EPluginType Type, FDiscoveredPluginMap& Plugins, TArray<TSharedRef<FPlugin>>& ChildPlugins);` — Reads all the plugin descriptors from disk
- L304 _private prototype_ `static void CreatePluginObject(const FString& FileName, const FPluginDescriptor& Descriptor, const EPluginType Type, FDiscoveredPluginMap& Plugins, TArray<TSharedRef<FPlugin>>& ChildPlugins);` — Creates a FPlugin object and adds it to the given map
- L307 _private prototype_ `static void FindPluginsInDirectory(const FString& PluginsDirectory, TArray<FString>& FileNames, IPlatformFile& PlatformFile);` — Finds all the plugin descriptors underneath a given directory
- L310 _private prototype_ `static void FindPluginManifestsInDirectory(const FString& PluginManifestDirectory, TArray<FString>& FileNames);` — Finds all the plugin manifests in a given directory
- L313 _private prototype_ `static bool GetCodePluginsForProject(const FProjectDescriptor* ProjectDescriptor, const FString& Platform, EBuildConfiguration Configuration, EBuildTargetType TargetType, FDiscoveredPluginMap& AllPlugins, TSet<FString>& CodePluginNames, const TSet<FString>& AllowedOptionalPluginReferences, FConfigurePluginResultInfo& OutResultInfo);` — Gets all the code plugins that are enabled for a content only project
- L316 _private prototype_ `bool ConfigureEnabledPlugins();` — Sets the bPluginEnabled flag on all plugins found from DiscoverAllPlugins that are enabled in config
- L319 _private prototype_ `bool ConfigureEnabledPluginForCurrentTarget(const FPluginReferenceDescriptor& FirstReference, TMap<FString, FPlugin*>& EnabledPlugins, FStringView SourceOfPluginRequest, const TSet<FString>& AllowedOptionalDependencies);` — Adds a single enabled plugin, and all its dependencies. If AllowedOptionalDependencies is not empty, only enable optional dependencies that are listed
- L323 _private prototype_ `static bool ConfigureEnabledPluginForTarget(const FPluginReferenceDescriptor& FirstReference, const FProjectDescriptor* ProjectDescriptor, const FString& TargetName, const FString& Platform, EBuildConfiguration Configuration, EBuildTargetType TargetType, bool bLoadPluginsForTargetPlatforms, FDiscoveredPluginMap& AllPlugins, TMap<FString, FPlugin*>& EnabledPlugins, const TSet<FString>& AllowedOptionalDependencies, FConfigurePluginResultInfo& OutResultInfo);` — Adds a single enabled plugin and all its dependencies. If AllowedOptionalDependencies is not empty, only enable optional dependencies that are listed
- L326 _private prototype_ `static bool PromptToDownloadPlugin(const FString& PluginName, const FString& MarketplaceURL);` — Prompts the user to download a missing plugin from the given URL
- L329 _private prototype_ `static bool PromptToDisableSealedPlugin(const FString& PluginName, const FString& SealedPluginName);` — Prompts the user to disable a plugin
- L332 _private prototype_ `static bool PromptToDisableDisalowedPlugin(const FString& PluginName, const FString& DisallowedPluginName);` — Prompts the user to disable a plugin
- L335 _private prototype_ `static bool PromptToDisableMissingPlugin(const FString& PluginName, const FString& MissingPluginName);` — Prompts the user to disable a plugin
- L338 _private prototype_ `static bool PromptToDisableIncompatiblePlugin(const FString& PluginName, const FString& IncompatiblePluginName);` — Prompts the user to disable a plugin
- L341 _private prototype_ `static bool PromptToDisablePlugin(const FText& Caption, const FText& Message, const FString& PluginName);` — Prompts the user to disable a plugin
- L344 _private prototype_ `static bool IsPluginCompatible(const FPlugin& Plugin);` — Checks whether a plugin is compatible with the current engine version
- L347 _private prototype_ `static bool PromptToLoadIncompatiblePlugin(const FPlugin& Plugin);` — Prompts the user to disable a plugin
- L350 _private prototype_ `bool TryLoadModulesForPlugin(const FPlugin& Plugin, const ELoadingPhase::Type LoadingPhase) const;` — Attempt to load all the modules for the given plugin
- L353 _private prototype_ `bool TryUnloadModulesForPlugin(const FPlugin& Plugin, const ELoadingPhase::Type LoadingPhase, FText* OutFailureMessage = nullptr, bool bSkipUnload = false, bool bAllowUnloadCode = true) const;` — Attempt to unload all the modules for the given plugin
- L356 _private prototype_ `TSharedPtr<FPlugin> FindPluginInstance(const FString& Name);` — Gets the instance of a given plugin
- L365 _private prototype_ `bool TryMountExplicitlyLoadedPluginVersion(TSharedRef<FPlugin>* AllPlugins_PluginPtr);` — Attempts to mount a spectific plugin version. Can fail if the plugin isn't marked 'ExplicitlyLoaded', or if there's a different version already mounted. NOTE: It's expected that `AllPlugins_PluginPtr` directly addresses an entry in `AllPlugins` (so that it can reorder the versions in `AllPlugins` since that's how we track the mounted/choice version).
- L368 _private prototype_ `void MountPluginFromExternalSource(const TSharedRef<FPlugin>& Plugin, ELoadingPhase::Type MaxLoadingPhase = ELoadingPhase::Max);` — Mounts a plugin that was requested to be mounted from external code (either by MountNewlyCreatedPlugin or MountExplicitlyLoadedPlugin)
- L371 _private prototype_ `void AddToModuleNameToPluginMap(const TSharedRef<FPlugin>& Plugin);`
- L372 _private prototype_ `void RemoveFromModuleNameToPluginMap(const TSharedRef<FPlugin>& Plugin);`
- L377 _private member_ `FDiscoveredPluginMap AllPlugins;` — All of the plugins that we know about
- L380 _private member_ `TSet<FString> PluginsToConfigure;` — Plugins that need to be configured to see if they should be enabled
- L383 _private member_ `TSet<FString> PluginsEnabledForTarget;` — Set of plugins enabled for the current target. Plugins in list might not be currently enabled.
- L386 _private member_ `TSet<FString> PluginsEnabledAtStartup;` — Set of plugins which were compiled for the target and enabled at startup.
- L390 _private member_ `TSet<FString> BuiltInPluginNames;` — Names of built-in plugins
- L392 _private member_ `TMap<FName, TSharedRef<IPlugin>> ModuleNameToPluginMap;`
- L395 _private member_ `TArray<TSharedRef<IPlugin>> PluginsWithPakFile;`
- L399 _private member_ `FRegisterMountPointDelegate RegisterMountPointDelegate;` — Delegate for mounting content paths.  Bound by FPackageName code in CoreUObject, so that we can access content path mounting functionality from Core.
- L403 _private member_ `FRegisterMountPointDelegate UnRegisterMountPointDelegate;` — Delegate for unmounting content paths.  Bound by FPackageName code in CoreUObject, so that we can access content path unmounting functionality from Core.
- L406 _private member_ `bool bHaveAllRequiredPlugins = false;` — Set if all the required plugins are available
- L409 _private member_ `bool bAllPluginsEnabledViaCommandLine = false;` — Set if we were asked to load all plugins via the command line
- L411 _private member_ `bool bPreloadedBinaries = false;`
- L414 _private member_ `TSet<FExternalPluginPath> ExternalPluginSources;` — List of additional directory paths to search for plugins within
- L417 _private member_ `TSet<FString> PluginDiscoveryPaths;` — Projection of ExternalPluginSources paths only; maintained for backward compatibility
- L420 _private member_ `FNewPluginMountedEvent NewPluginCreatedEvent;` — Callback for notifications that a new plugin was mounted
- L421 _private member_ `FNewPluginMountedEvent NewPluginMountedEvent;`
- L422 _private member_ `FNewPluginMountedEvent NewPluginContentMountedEvent;`
- L423 _private member_ `FNewPluginMountedEvent PluginEditedEvent;`
- L424 _private member_ `FNewPluginMountedEvent PluginUnmountedEvent;`
- L427 _private member_ `FLoadingModulesForPhaseEvent LoadingPhaseCompleteEvent;` — Callback for notifications that a loading phase was completed
- L430 _private member_ `ELoadingPhase::Type LastCompletedLoadingPhase = ELoadingPhase::None;` — The highest LoadingPhase that has so far completed
- L432 _private member_ `FString EngineBinariesRootDir;`
- L433 _private member_ `FString ProjectBinariesRootDir;`
- L436 _private member_ `FLeakedPackagesFoundEvent LeakedPackagesFoundEvent;` — The callback that is called from within the PluginHandler when leaked packages are found

#### struct `FPluginManager::FPluginDiscoveryContext`  
`struct FPluginDiscoveryContext`  
_L268-287_
- desc: Helper functions just to split up the massive size of ConfigureEnabledPlugins()
- L271 _public member_ `TMap<FString, FPlugin*> EnabledPlugins;` — Set of all the plugins which have been enabled
- L274 _public member_ `TSet<FString> ConfiguredPluginNames;` — Keep a set of all the plugin names that have been configured. We read configuration data from different places, but only configure a plugin from the first place that it's referenced.
- L277 _public member_ `TArray<FString> AdditionalLocResPaths;` — Keep the list of newly available localization targets
- L281 _public member_ `const TSet<FString> AllowedOptionalDependencies;` — const to ensure it to stays empty
- L284 _public member_ `TSet<FString> AllowedOptionalDependencies;` — Set of all the plugin names that are allowed to be enabled for a plugin with optional dependencies. Only read in Editor

### `Source/Runtime/Projects/Private/ProjectManager.h` (Private)


#### class `FProjectManager`  
`class FProjectManager final : public IProjectManager`  
_L13-73_
- inherits: `IProjectManager`
- desc: ProjectAndPluginManager manages available code and content extensions (both loaded and not loaded.)
- L16 _public prototype_ `FProjectManager();`
- L19 _public prototype_ `virtual const FProjectDescriptor *GetCurrentProject() const override;` — IProjectManager interface
- L20 _public prototype_ `virtual bool LoadProjectFile( const FString& ProjectFile ) override;`
- L21 _public prototype_ `virtual bool LoadModulesForProject( const ELoadingPhase::Type LoadingPhase ) override;`
- L22 _public function_ `virtual FLoadingModulesForPhaseEvent& OnLoadingPhaseComplete() override`
- L23 _public prototype_ `virtual bool SubstituteModule(const FString& OriginalModuleName, const FString& NewModuleName) override;`
- L25 _public prototype_ `virtual bool CheckModuleCompatibility( TArray<FString>& OutIncompatibleModules ) override;`
- L27 _public prototype_ `virtual const FString& GetAutoLoadProjectFileName() override;`
- L28 _public prototype_ `virtual bool SignSampleProject(const FString& FilePath, const FString& Category, FText& OutFailReason) override;`
- L29 _public prototype_ `virtual bool QueryStatusForProject(const FString& FilePath, FProjectStatus& OutProjectStatus) const override;`
- L30 _public prototype_ `virtual bool QueryStatusForCurrentProject(FProjectStatus& OutProjectStatus) const override;`
- L31 _public prototype_ `virtual void UpdateSupportedTargetPlatformsForProject(const FString& FilePath, const FName& InPlatformName, const bool bIsSupported) override;`
- L32 _public prototype_ `virtual void UpdateSupportedTargetPlatformsForCurrentProject(const FName& InPlatformName, const bool bIsSupported) override;`
- L33 _public prototype_ `virtual void ClearSupportedTargetPlatformsForProject(const FString& FilePath) override;`
- L34 _public prototype_ `virtual void ClearSupportedTargetPlatformsForCurrentProject() override;`
- L35 _public function_ `virtual FOnTargetPlatformsForCurrentProjectChangedEvent& OnTargetPlatformsForCurrentProjectChanged() override`
- L36 _public prototype_ `virtual bool HasDefaultPluginSettings() const override;`
- L37 _public prototype_ `virtual bool SetPluginEnabled(const FString& PluginName, bool bEnabled, FText& OutFailReason) override;`
- L38 _public prototype_ `virtual bool RemovePluginReference(const FString& PluginName, FText& OutFailReason) override;`
- L39 _public prototype_ `virtual bool UpdateAdditionalPluginDirectory(const FString& Dir, const bool bAddOrRemove) override;`
- L40 _public prototype_ `virtual const TArray<FString>& GetAdditionalPluginDirectories() const override;`
- L41 _public prototype_ `virtual bool IsCurrentProjectDirty() const override;`
- L42 _public prototype_ `virtual bool SaveCurrentProjectToDisk(FText& OutFailReason) override;`
- L43 _public prototype_ `virtual bool IsEnterpriseProject() override;`
- L44 _public prototype_ `virtual void SetIsEnterpriseProject(bool bValue) override;`
- L45 _public prototype_ `virtual TArray<FModuleContextInfo>& GetCurrentProjectModuleContextInfos() override;`
- L46 _public prototype_ `virtual bool IsSuppressingProjectFileWrite() const override;`
- L47 _public prototype_ `virtual void AddSuppressProjectFileWrite(const FName InName) override;`
- L48 _public prototype_ `virtual void RemoveSuppressProjectFileWrite(const FName InName) override;`
- L51 _private prototype_ `static void QueryStatusForProjectImpl(const FProjectDescriptor& Project, const FString& FilePath, FProjectStatus& OutProjectStatus);`
- L54 _private prototype_ `static void GetDefaultEnabledPlugins(TArray<FString>& PluginNames, bool bIncludeInstalledPlugins, bool bAllowEnginePluginsEnabledByDefault);` — Gets the list of plugins enabled by default, excluding the project overrides
- L57 _private member_ `TSharedPtr< FProjectDescriptor > CurrentProject;` — The project that is currently loaded in the editor
- L60 _private member_ `TArray<FModuleContextInfo> CurrentProjectModuleContextInfos;` — Cached list of module infos for the project that is currently loaded in the editor
- L63 _private member_ `bool bIsCurrentProjectDirty;` — Whether the current project has been modified but not saved to disk
- L66 _private member_ `FOnTargetPlatformsForCurrentProjectChangedEvent OnTargetPlatformsForCurrentProjectChangedEvent;` — Delegate called when the target platforms for the current project are changed
- L69 _private member_ `FLoadingModulesForPhaseEvent OnLoadingPhaseCompleteEvent;` — Delegate called when LoadModulesForProject() completes for a particular phase
- L72 _private member_ `TArray<FName> SuppressProjectFileWriteList;` — Array of names that have disabled project file writes

### `Source/Runtime/Projects/Private/RapidJsonPluginLoading.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Projects` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Projects`)
- L26 _prototype_ `bool TryGetBoolField(Json::FConstObject Object, const TCHAR* FieldName, bool& Out);` (scope `UE::Projects::Private`)
- L27 _prototype_ `bool TryGetNumberField(Json::FConstObject Object, const TCHAR* FieldName, int32& Out);` (scope `UE::Projects::Private`)
- L28 _prototype_ `bool TryGetNumberField(Json::FConstObject Object, const TCHAR* FieldName, uint32& Out);` (scope `UE::Projects::Private`)
- L29 _prototype_ `bool TryGetStringField(Json::FConstObject Object, const TCHAR* FieldName, FString& Out);` (scope `UE::Projects::Private`)
- L30 _prototype_ `bool TryGetStringField(Json::FConstObject Object, const TCHAR* FieldName, FStringView& Out);` (scope `UE::Projects::Private`)
- L31 _prototype_ `bool TryGetStringArrayField(Json::FConstObject Object, const TCHAR* FieldName, TArray<FString>& Out);` (scope `UE::Projects::Private`)
- L32 _prototype_ `bool TryGetStringArrayField(Json::FConstObject Object, const TCHAR* FieldName, TArray<FName>& Out);` (scope `UE::Projects::Private`)
- L34 _prototype_ `bool TryGetStringArrayFieldWithDeprecatedFallback(Json::FConstObject Object, const TCHAR* FieldName, const TCHAR* DeprecatedFieldName, TArray<FString>& OutArray);` (scope `UE::Projects::Private`)
- L36 _prototype_ `FText GetArrayObjectTypeError(const TCHAR* FieldName, int32 Index);` (scope `UE::Projects::Private`)
- L37 _prototype_ `FText GetArrayObjectChildParseError(const TCHAR* FieldName, int32 Index, const FText& PropagateError);` (scope `UE::Projects::Private`)
- L42 _function_ `template<typename TEnum> inline bool TryGetEnumArrayField(Json::FConstObject Object, const TCHAR* FieldName, TArray<TEnum>& OutArray)` (scope `UE::Projects::Private`) — Get the field named FieldName as an array of strings. Returns false if it doesn't exist or any member cannot be converted.
- L68 _function_ `template<typename TEnum> inline bool TryGetEnumArrayFieldWithDeprecatedFallback(Json::FConstObject Object, const TCHAR* FieldName, const TCHAR* DeprecatedFieldName, TArray<TEnum>& OutArray)` (scope `UE::Projects::Private`)
- L87 _prototype_ `TOptional<FText> Read(Json::FConstObject Object, FPluginManifest& Out);` (scope `UE::Projects::Private`)
- L88 _prototype_ `TOptional<FText> Read(Json::FConstObject Object, FPluginDescriptor& Out);` (scope `UE::Projects::Private`)
- L89 _prototype_ `TOptional<FText> Read(Json::FConstObject Object, FModuleDescriptor& Out);` (scope `UE::Projects::Private`)
- L90 _prototype_ `TOptional<FText> Read(Json::FConstObject Object, FLocalizationTargetDescriptor& Out);` (scope `UE::Projects::Private`)
- L91 _prototype_ `TOptional<FText> Read(Json::FConstObject Object, FPluginReferenceDescriptor& Out);` (scope `UE::Projects::Private`)
- L92 _prototype_ `TOptional<FText> Read(Json::FConstObject Object, FPluginDisallowedDescriptor& Out);` (scope `UE::Projects::Private`)
- L94 _prototype_ `FCustomBuildSteps ReadCustomBuildSteps(Json::FConstObject Object, const TCHAR* FieldName);` (scope `UE::Projects::Private`)
- L98 _function_ `template<typename FUNCTOR> bool ReadFromDefaultJsonHelper(const FJsonObject& Object, FUNCTOR && Functor)` (scope `UE::Projects::Private`) — Helper functions to convert and call the rapidjson functions from default json sources
- L116 _function_ `template<typename TYPE> bool ReadFromDefaultJson(const FJsonObject& Object, TYPE& Out, FText* OutFailReason)` (scope `UE::Projects::Private`)
- L121 _function_ `` (scope `UE::Projects::Private::ReadFromDefaultJson`)
- L139 _function_ `template<typename TYPE> TOptional<FText> ReadArray(Json::FConstObject Object, const TCHAR* FieldName, TArray<TYPE>& OutArray)` (scope `UE::Projects::Private`)
- L168 _function_ `template<typename TYPE> bool ReadArrayFromDefaultJson(const FJsonObject& Object, const TCHAR* Name, TArray<TYPE>& OutArray, FText* OutFailReason)` (scope `UE::Projects::Private`)
- L173 _function_ `` (scope `UE::Projects::Private::ReadArrayFromDefaultJson`)

### `Source/Runtime/Projects/Public/CustomBuildSteps.h` (Public)


#### struct `FCustomBuildSteps`  
`struct FCustomBuildSteps`  
_L16-32_
- desc: Descriptor for projects. Contains all the information contained within a .uproject file.
- L19 _public member_ `TMap<FString, TArray<FString>> HostPlatformToCommands;` — Mapping from host platform to list of commands
- L22 _public prototype_ `bool IsEmpty() const;` — Whether this object is empty
- L25 _public prototype_ `void Read(const FJsonObject& Object, const FString& FieldName);` — Reads the descriptor from the given JSON object
- L28 _public prototype_ `void Write(TJsonWriter<>& Writer, const FString& FieldName) const;` — Writes the CustomBuildSteps to JSON
- L31 _public prototype_ `void UpdateJson(FJsonObject& JsonObject, const FString& FieldName) const;` — Updates the given json object with this CustomBuildSteps

### `Source/Runtime/Projects/Public/Interfaces/IPluginManager.h` (Public)


#### enum `EPluginLoadedFrom`  
`enum class EPluginLoadedFrom`  
_L18-25_
- desc: Enum for where a plugin is loaded from
- L21 _public enumerator_ `Engine` — Plugin is built-in to the engine
- L24 _public enumerator_ `Project` — Project-specific plugin, stored within a game project directory

#### enum `EPluginType`  
`enum class EPluginType`  
_L30-46_
- desc: Enum for the type of a plugin
- L33 _public enumerator_ `Engine` — Plugin is built-in to the engine
- L36 _public enumerator_ `Enterprise` — Standard enterprise plugin
- L39 _public enumerator_ `Project` — Project-specific plugin, stored within a game project directory
- L42 _public enumerator_ `External` — Plugin found in an external directory (found in an AdditionalPluginDirectory listed in the project file, or referenced on the command line)
- L45 _public enumerator_ `Mod` — Project-specific mod plugin

#### enum `EPluginExternalSource`  
`enum class EPluginExternalSource`  
_L51-64_
- desc: Enum describing a source of EPluginType::External plugins
- L54 _public enumerator_ `ProjectDescriptor` — .uproject `AdditionalPluginDirectories` field
- L57 _public enumerator_ `CommandLine` — Passed via `-plugin=` command line switch.
- L60 _public enumerator_ `Environment` — Inherited from `UE_ADDITIONAL_PLUGIN_PATHS` environment variable.
- L63 _public enumerator_ `Other` — None of the above (e.g. added explicitly by external code).

#### struct `FExternalPluginPath`  
`struct FExternalPluginPath`  
_L69-83_
- desc: Combination of a directory searched for external plugins, and its configuration source.
- L71 _public member_ `FString Path;`
- L72 _public member_ `EPluginExternalSource Source;`
- L74 _public function_ `inline bool operator==(const FExternalPluginPath& Other) const`

#### struct `FPluginStatus`  
`struct FPluginStatus`  
_L88-104_
- desc: Simple data structure that is filled when querying information about plug-ins.
- L91 _public member_ `FString Name;` — The name of this plug-in.
- L94 _public member_ `FString PluginDirectory;` — Path to plug-in directory on disk.
- L97 _public member_ `bool bIsEnabled;` — True if plug-in is currently enabled.
- L100 _public member_ `EPluginLoadedFrom LoadedFrom;` — Where the plugin was loaded from
- L103 _public member_ `FPluginDescriptor Descriptor;` — The plugin descriptor

#### class `IPlugin`  
`class IPlugin : public TSharedFromThis<IPlugin>`  
_L110-279_
- inherits: `TSharedFromThis<IPlugin>`
- desc: Information about an enabled plugin.
- L114 _public prototype_ `virtual ~IPlugin()= default;` — Virtual destructor
- L121 _public prototype_ `virtual const FString& GetName() const = 0;` — Gets the plugin name. @return Name of the plugin.
- L126 _public prototype_ `virtual const FString& GetFriendlyName() const = 0;` — Return plugin friendly name if available or the same name as GetName() otherwise.
- L133 _public prototype_ `virtual const FString& GetDescriptorFileName() const = 0;` — Get a filesystem path to the plugin's descriptor @return Filesystem path to the plugin's descriptor.
- L140 _public prototype_ `virtual FString GetBaseDir() const = 0;` — Get a filesystem path to the plugin's directory. @return Filesystem path to the plugin's base directory.
- L147 _public prototype_ `virtual TArray<FString> GetExtensionBaseDirs() const = 0;` — Get a filesystem path to the plugin's directory. @return Filesystem path to the plugin's base directory.
- L154 _public prototype_ `virtual FString GetContentDir() const = 0;` — Get a filesystem path to the plugin's content directory. @return Filesystem path to the plugin's content directory.
- L161 _public prototype_ `virtual FString GetMountedAssetPath() const = 0;` — Get the virtual root path for assets. @return The mounted root path for assets in this plugin's content folder; typically /PluginName/.
- L168 _public prototype_ `virtual EPluginType GetType() const = 0;` — Gets the type of a plugin @return The plugin type
- L175 _public prototype_ `virtual bool IsEnabled() const = 0;` — Determines if the plugin is enabled. @return True if the plugin is currently enabled.
- L182 _public prototype_ `virtual bool IsEnabledByDefault(bool bAllowEnginePluginsEnabledByDefault) const = 0;` — Determines if the plugin is enabled by default. @return True if the plugin is currently enabled by default.
- L189 _public prototype_ `virtual bool IsMounted() const = 0;` — Determines if the plugin is mounted. @return True if the plugin is currently mounted.
- L196 _public prototype_ `virtual bool IsHidden() const = 0;` — Determines if the plugin is should be displayed in-editor for the user to enable/disable freely. @return True if the plugin should be hidden.
- L203 _public prototype_ `virtual bool CanContainContent() const = 0;` — Determines if the plugin can contain content. @return True if the plugin can contain content.
- L210 _public prototype_ `virtual bool CanContainVerse() const = 0;` — Determines if the plugin can contain Verse code. @return True if the plugin can contain Verse code.
- L217 _public prototype_ `virtual const FString& GetVersePath() const = 0;` — Gets the Verse path to the root of the plugin's content directory @return Verse path to the root of the plugin's content directory
- L225 _public prototype_ `virtual const FString& GetDeprecatedEngineVersion() const = 0;` — Gets the engine version that this plugin was deprecated.  If unset then this plugin is not deprecated. @return Deprecated engine version.  This may be an empty string.
- L230 _public prototype_ `virtual TOptional<uint32> GetVerseVersion() const = 0;` — Return the Verse language version to compile the plugin with (if unspecified, the latest stable version is used)
- L235 _public prototype_ `virtual bool IsSceneGraphEnabled() const = 0;` — Return whether Scene Graph is enabled or not. This impacts which Verse asset digest is generated.
- L240 _public prototype_ `virtual bool IsSceneGraphAnimationEnabled() const = 0;` — Return whether Scene Graph Animation is enabled or not. This impacts which Verse asset digest is generated.
- L246 _public prototype_ `virtual bool IsRootPlugin() const = 0;` — Returns true if this is a root plugin. A root plugin is meant as a collection of other plugins. Root plugins should only have plugin dependencies and be used to designate some group of plugins.
- L253 _public prototype_ `virtual EPluginLoadedFrom GetLoadedFrom() const = 0;` — Returns the plugin's location @return Where the plugin was loaded from
- L260 _public prototype_ `virtual const FPluginDescriptor& GetDescriptor() const = 0;` — Gets the plugin's descriptor @return Reference to the plugin's descriptor
- L269 _public prototype_ `virtual bool UpdateDescriptor(const FPluginDescriptor& NewDescriptor, FText& OutFailReason) = 0;` — Updates the plugin's descriptor @param NewDescriptor The new plugin descriptor @param OutFailReason The error message if the plugin's descriptor could not be updated @return True if the descriptor was updated, false otherwise.
- L277 _public prototype_ `virtual const TSharedPtr<FJsonObject>& GetDescriptorJson() = 0;` — Gets the cached plugin descriptor json @return Reference to the cached plugin descriptor json

#### class `IPluginManager`  
`class IPluginManager`  
_L284-668_
- desc: PluginManager manages available code and content extensions (both loaded and not loaded).
- L287 _public prototype_ `virtual ~IPluginManager() = default;`
- L292 _public prototype_ `virtual void RefreshPluginsList() = 0;` — Updates the list of plugins.
- L299 _public prototype_ `virtual bool AddToPluginsList(const FString& PluginFilename, FText* OutFailReason = nullptr) = 0;` — Adds a single plugin to the list of plugins. Faster than refreshing all plugins with RefreshPluginsList() when you only want to add one. Does nothing if already in the list. @return True if the plugin was added or already in the list. False if it failed to load.
- L306 _public prototype_ `virtual bool RemoveFromPluginsList(const FString& PluginFilename, FText* OutFailReason = nullptr) = 0;` — Remove a single plugin from the list of plugins. @return True if the plugin was not in the list. False if it can't be removed (see OutFailReason).
- L314 _public prototype_ `virtual bool LoadModulesForEnabledPlugins( const ELoadingPhase::Type LoadingPhase ) = 0;` — Loads all plug-ins @param	LoadingPhase	Which loading phase we're loading plug-in modules from.  Only modules that are configured to be loaded at the specified loading phase will be loaded during this call.
- L317 _public prototype_ `virtual ELoadingPhase::Type GetLastCompletedLoadingPhase() const = 0;` — Returns the highest loading phase that has so far completed
- L322 _public prototype_ `DECLARE_EVENT_TwoParams(IPluginManager, FLoadingModulesForPhaseEvent, ELoadingPhase::Type , bool );` — Callback for when modules for when LoadModulesForEnabledPlugins() completes loading for a specific phase.
- L323 _public prototype_ `virtual FLoadingModulesForPhaseEvent& OnLoadingPhaseComplete() = 0;`
- L330 _public prototype_ `virtual void GetLocalizationPathsForEnabledPlugins( TArray<FString>& OutLocResPaths ) = 0;` — Get the localization paths for all enabled plugins. @param	OutLocResPaths	Array to populate with the localization paths for all enabled plugins.
- L333 _public prototype_ `DECLARE_DELEGATE_TwoParams( FRegisterMountPointDelegate, const FString& , const FString& );` — Delegate type for mounting content paths.  Used internally by FPackageName code.
- L341 _public prototype_ `virtual void SetRegisterMountPointDelegate( const FRegisterMountPointDelegate& Delegate ) = 0;` — Sets the delegate to call to register a new content mount point.  This is used internally by the plug-in manager system and should not be called by you.  This is registered at application startup by FPackageName code in CoreUObject. @param	Delegate	The delegate to that will be called when plug-in manager needs to register a mount point
- L349 _public prototype_ `virtual void SetUnRegisterMountPointDelegate( const FRegisterMountPointDelegate& Delegate ) = 0;` — Sets the delegate to call to unregister a new content mount point.  This is used internally by the plug-in manager system and should not be called by you.  This is registered at application startup by FPackageName code in CoreUObject. @param	Delegate	The delegate to that will be called when plug-in manager needs to unregister a mount point
- L356 _public prototype_ `virtual bool AreRequiredPluginsAvailable() = 0;` — Checks if all the required plug-ins are available. If not, will present an error dialog the first time a plug-in is loaded or this function is called. @returns true if all the required plug-ins are available.
- L359 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FGetExplanationForUnavailablePackageWithPluginInfoDelegate, const FString& , class IPlugin* , FStringBuilderBase& );` — Delegate type for allowing higher levels systems to provide additional context for why a package was skipped during loading
- L366 _public prototype_ `virtual FGetExplanationForUnavailablePackageWithPluginInfoDelegate& GetExplanationForUnavailablePackageWithPluginInfoDelegate() = 0;` — Accessor for adding/removing FGetExplanationForUnavailablePackageWithPluginInfoDelegate delegates. @returns the FGetExplanationForUnavailablePackageWithPluginInfoDelegate to which callbacks can be bound
- L375 _public prototype_ `virtual void GetExplanationForUnavailablePackage(const FName& UnavailablePackageName, FStringBuilderBase& InOutExplanation) = 0;` — Attempts to fill out InOutExplanation with information from various sources (registered via GetExplanationForUnavailablePackageWithPluginInfoDelegate) about why UnavailablePackageName is not available @param UnavailablePackageName the name of the package about which to get information @param InOutExplanation a stringbuilder to which to append explanatory information
- L385 _public prototype_ `virtual bool CheckModuleCompatibility( TArray<FString>& OutIncompatibleModules, TArray<FString>& OutIncompatibleEngineModules ) = 0;` — Checks whether modules for the enabled plug-ins are up to date. @param OutIncompatibleModules Array to receive a list of incompatible module names. @param OutIncompatibleEngineModules Array to receive a list of incompatible engine module names. @returns true if the enabled plug-in modules are up to date.
- L393 _public prototype_ `virtual TSharedPtr<IPlugin> FindPlugin(const FStringView Name) = 0;` — Finds information for a plugin. @return	 Pointer to the plugin's information, or nullptr.
- L394 _public prototype_ `virtual TSharedPtr<IPlugin> FindPlugin(const ANSICHAR* Name) = 0;`
- L396 _public prototype_ `virtual TSharedPtr<IPlugin> FindPluginFromPath(const FString& PluginPath) = 0;`
- L397 _public prototype_ `virtual TSharedPtr<IPlugin> FindPluginFromDescriptor(const FPluginReferenceDescriptor& PluginDesc) = 0;`
- L404 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPlugin(const FStringView Name) = 0;` — Finds information for an enabled plugin. @return	 Pointer to the enabled plugin's information, or nullptr if not enabled or can't be found.
- L405 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPlugin(const ANSICHAR* Name) = 0;`
- L407 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPluginFromPath(const FString& PluginPath) = 0;`
- L408 _public prototype_ `virtual TSharedPtr<IPlugin> FindEnabledPluginFromDescriptor(const FPluginReferenceDescriptor& PluginDesc) = 0;`
- L413 _public prototype_ `virtual bool CanEnablePluginInCurrentTarget(const FStringView Name) = 0;` — Returns true when the given plugin can be enabled for the current running exe.
- L414 _public prototype_ `virtual bool CanEnablePluginInCurrentTarget(const ANSICHAR* Name) = 0;`
- L421 _public prototype_ `virtual void FindPluginsUnderDirectory(const FString& Directory, TArray<FString>& OutPluginFilePaths) = 0;` — Finds all plugin descriptors underneath a given directory (recursively) @param Directory Search folder @param OutPluginFilePaths Receives found plugin descriptor file paths
- L428 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPlugins() = 0;` — Gets an array of all the enabled plugins. @return	Array of the enabled plugins.
- L435 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPluginsWithContent() const = 0;` — Gets an array of all enabled plugins that can have content. @return	Array of plugins with IsEnabled() and CanContainContent() both true.
- L442 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPluginsWithVerse() const = 0;` — Gets an array of all enabled plugins that can have Verse code. @return	Array of plugins with IsEnabled() and CanContainVerse() both true.
- L447 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetEnabledPluginsWithContentOrVerse() const = 0;` — Gets an array of all enabled plugins that can have content or Verse code.
- L454 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetDiscoveredPlugins() = 0;` — Gets an array of all the discovered plugins. @return	Array of the discovered plugins.
- L463 _public prototype_ `UE_INTERNAL virtual const TSet<FString>& GetPluginsEnabledAtStartup() const = 0;` — Returns the set of plugins compiled into the current application and enabled at startup. For internal use only. TODO: Needs improved for the GameFeaturePlugin system to one day remove the concept of LoadedAsBuiltIn @return set of plugin names.
- L469 _public prototype_ `virtual const TSet<FString>& GetBuiltInPluginNames() const = 0;` — Returns the set of built-in plugin names
- L474 _public prototype_ `virtual TSharedPtr<IPlugin> GetModuleOwnerPlugin(FName ModuleName) const = 0;` — Returns the plugin that owns the specified module, if any
- L486 _public prototype_ `virtual bool AddPluginSearchPath(const FString& ExtraDiscoveryPath, bool bRefresh = true) = 0;` — Stores the specified path, utilizing it in future search passes when searching for available plugins. Optionally refreshes the manager after the new path has been added. @param  ExtraDiscoveryPath	The path you want searched for additional plugins. @param  bRefresh				Signals the function to refresh the plugin database after the new path has been added @return Whether the plugin search path was modified
- L496 _public prototype_ `virtual bool RemovePluginSearchPath(const FString& PathToRemove, bool bRefresh = true) = 0;` — Removes the specified path from consideration for available plugins. Optionally refreshes the manager after the path has been removed. @param  PathToRemove			The path no longer searched for additional plugins. @param  bRefresh				Signals the function to refresh the plugin database after the path has been removed @return Whether the plugin search path was modified
- L502 _public prototype_ `virtual const TSet<FString>& GetAdditionalPluginSearchPaths() const = 0;` — Returns the list of extra directories that are recursively searched for plugins (aside from the engine and project plugin directories). NOTE: You may also want to check IProjectManager::GetAdditionalPluginDirectories, which are not included here!
- L508 _public prototype_ `virtual void GetExternalPluginSources(TSet<FExternalPluginPath>& OutPluginSources) const = 0;` — Similar to GetAdditionalPluginSearchPaths, but also returns configuration sources for each path. Unlike GetAdditionalPluginSearchPaths, this DOES include AdditionalPluginDirectories from the uproject descriptor.
- L513 _public prototype_ `virtual TArray<TSharedRef<IPlugin>> GetPluginsWithPakFile() const = 0;` — Gets an array of plugins that loaded their own content pak file
- L518 _public prototype_ `DECLARE_EVENT_OneParam(IPluginManager, FNewPluginMountedEvent, IPlugin&);` — Event signature for being notified that a new plugin has been mounted
- L523 _public prototype_ `virtual FNewPluginMountedEvent& OnNewPluginCreated() = 0;` — Event signature for being notified that a new plugin has been created
- L528 _public prototype_ `virtual FNewPluginMountedEvent& OnNewPluginMounted() = 0;` — Event for being notified that a new plugin has been mounted
- L533 _public prototype_ `virtual FNewPluginMountedEvent& OnNewPluginContentMounted() = 0;` — Event for being notified that a new plugin and its content have been mounted
- L538 _public prototype_ `virtual FNewPluginMountedEvent& OnPluginEdited() = 0;` — Event for being notified that a plugin has been edited
- L543 _public prototype_ `virtual FNewPluginMountedEvent& OnPluginUnmounted() = 0;` — Event for being notified that a plugin has been unmounted
- L548 _public prototype_ `virtual void MountNewlyCreatedPlugin(const FString& PluginName) = 0;` — Marks a newly created plugin as enabled, mounts its content and tries to load its modules
- L556 _public prototype_ `virtual bool MountExplicitlyLoadedPlugin(const FString& PluginName, ELoadingPhase::Type MaxLoadingPhase = ELoadingPhase::Max) = 0;` — Marks an explicitly loaded plugin as enabled, mounts its content and tries to load its modules. These plugins are not loaded implicitly, but instead wait for this function to be called. @note Call MountExplicitlyLoadedPluginLocalizationData if you also want to load any localization data for this plugin.
- L557 _public prototype_ `virtual bool MountExplicitlyLoadedPlugin_FromFileName(const FString& PluginFileName) = 0;`
- L558 _public prototype_ `virtual bool MountExplicitlyLoadedPlugin_FromDescriptor(const FPluginReferenceDescriptor& PluginDescriptor) = 0;`
- L570 _public prototype_ `virtual bool MountExplicitlyLoadedPluginLocalizationData(const FString& PluginName, TUniqueFunction<void(bool bLoadedLocalization, const FString& PluginName)>&& Notification = nullptr) = 0;` — Start loading localization data for an explicitly loaded plugin that has previously been mounted via one of the MountExplicitlyLoadedPlugin functions. @note Localization data is ref-counted, so this should be paired with a call to UnmountExplicitlyLoadedPluginLocalizationData. @param PluginName The name of the plugin to load the localization data for. @param Notification An optional notification function to call when the localization data load has finished (from any thread), or immediately if there was no localization data to load. bLoadedLocalization corresponds to the return value of this function. @return True if localization data started to load, or false if the plugin was missing or had no localization data to load.
- L583 _public prototype_ `virtual bool UnmountExplicitlyLoadedPluginLocalizationData(const FString& PluginName, TUniqueFunction<void(bool bUnloadedLocalization, const FString& PluginName)>&& Notification = nullptr) = 0;` — Start unloading localization data for an explicitly loaded plugin that had its localization data mounted via MountExplicitlyLoadedPluginLocalizationData. @note Localization data is ref-counted, so this should be paired with a call to MountExplicitlyLoadedPluginLocalizationData. @note Localization data is also automatically (and regardless of ref-count) unloaded when calling UnmountExplicitlyLoadedPlugin. @param PluginName The name of the plugin to unload the localization data for. @param Notification An optional notification function to call when the localization data unload has finished (from any thread), or immediately if there was no localization data to unload. bUnloadedLocalization corresponds to the return value of this function. @return True if localization data started to unload, or false if the plugin was missing or had no localization data to unload.
- L588 _public prototype_ `virtual bool UnmountExplicitlyLoadedPlugin(const FString& PluginName, FText* OutReason) = 0;` — Marks an explicitly loaded plugin as disabled, unmounts its content (does not work on plugins with compiled modules).
- L589 _public prototype_ `virtual bool UnmountExplicitlyLoadedPlugin(const FString& PluginName, FText* OutReason, bool bAllowUnloadCode) = 0;`
- L594 _public prototype_ `virtual bool GetPluginDependencies(const FString& PluginName, TArray<FPluginReferenceDescriptor>& PluginDependencies) = 0;` — Tries to get a list of plugin dependencies for a given plugin. Returns false if the plugin provided was not found
- L595 _public prototype_ `virtual bool GetPluginDependencies_FromFileName(const FString& PluginFileName, TArray<FPluginReferenceDescriptor>& PluginDependencies) = 0;`
- L596 _public prototype_ `virtual bool GetPluginDependencies_FromDescriptor(const FPluginReferenceDescriptor& PluginDescriptor, TArray<FPluginReferenceDescriptor>& PluginDependencies) = 0;`
- L601 _public prototype_ `virtual FName PackageNameFromModuleName(FName ModuleName) = 0;` — Does a reverse lookup to try to figure out what the UObject package name is for a plugin
- L609 _public prototype_ `UE_INTERNAL virtual void EnumerateVersePathMountPoints(const UE::Core::FVersePath& VersePath, TFunctionRef<bool(FStringView , FStringView )> Callback) = 0;` — Enumerates all mounted plug-ins to find mount points that the Verse path maps to. @param VersePath The full Verse path to check against the plug-in Verse path. @param Callback Function to call for each plug-in that maps to the Verse path. Return false to stop enumerating.
- L621 _public prototype_ `virtual bool RequiresTempTargetForCodePlugin(const FProjectDescriptor* ProjectDescriptor, const FString& Platform, EBuildConfiguration Configuration, EBuildTargetType TargetType, FText& OutReason) = 0;` — Determines if a content-only project requires a temporary target due to having a plugin enabled @param ProjectDescriptor The project being built @param Platform The platform the target is being built for @param Configuration The configuration being built @param TargetType The type of target being built @param OutReason If a temporary target is required, receives a message indicating why @return True if the project requires a temp target to be generated
- L633 _public function_ `virtual bool IntegratePluginsIntoConfig(FConfigCacheIni& ConfigSystem, const TCHAR* EngineIniName, const TCHAR* PlatformName, const TCHAR* StagedPluginsFile)` — `UE_DEPRECATED(5.6, "This has never worked and is unsafe. Do not call this function")` — Scans a set of given plugins and adds them to the passed in ConfigSystem so that the runtime can load faster without needing to scan all plugins looking for config/paks @param ConfigSystem The config system to insert settings into @param EngineIniName The name of the engine ini file in ConfigSystem @param PlatformName The name of the platform this config is made for @param StagedPluginsFile A path to a file that contains all plugins that have been staged, and should be evaluated
- L638 _public prototype_ `virtual void SetBinariesRootDirectories(const FString& EngineBinariesRootDir, const FString& ProjectBinariesRootDir) = 0;` — Set root directories for where to find binaries for plugins.
- L644 _public prototype_ `virtual void SetPreloadBinaries() = 0;` — If preload binaries is set all plugin binaries will be loaded in an early Loading phase. This is a temporary solution to work around issues with pak/iostore for modular builds
- L645 _public prototype_ `virtual bool GetPreloadBinaries() = 0;`
- L650 _public prototype_ `UE_INTERNAL virtual void SuppressPluginUnloadGC() = 0;` — Internal API for handling plugin garbage collection in a batch-friendly way.
- L651 _public prototype_ `UE_INTERNAL virtual void ResumePluginUnloadGC() = 0;`
- L656 _public typedef_ `using FLeakedPackageCountPerPluginMap = TMap<FString, int32>;` — Callback for when leaked packages in plugins have been found after unmount.
- L657 _public prototype_ `DECLARE_EVENT_OneParam(IPluginManager, FLeakedPackagesFoundEvent, const FLeakedPackageCountPerPluginMap& );`
- L658 _public prototype_ `virtual FLeakedPackagesFoundEvent& OnLeakedPackagesFound() = 0;`
- L667 _public prototype_ `static IPluginManager& Get();` — Static: Access singleton instance. @return	Reference to the singleton object.

#### Free symbols / members of external scopes

- L79 _function_ `friend uint32 GetTypeHash(const FExternalPluginPath& ExternalPluginPath)`
- L322 _delegate_ `DECLARE_EVENT_TwoParams(IPluginManager, FLoadingModulesForPhaseEvent, ELoadingPhase::Type , bool );` — Callback for when modules for when LoadModulesForEnabledPlugins() completes loading for a specific phase.
- L333 _delegate_ `DECLARE_DELEGATE_TwoParams( FRegisterMountPointDelegate, const FString& , const FString& );` — Delegate type for mounting content paths.  Used internally by FPackageName code.
- L359 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FGetExplanationForUnavailablePackageWithPluginInfoDelegate, const FString& , class IPlugin* , FStringBuilderBase& );` — Delegate type for allowing higher levels systems to provide additional context for why a package was skipped during loading
- L518 _delegate_ `DECLARE_EVENT_OneParam(IPluginManager, FNewPluginMountedEvent, IPlugin&);` — Event signature for being notified that a new plugin has been mounted
- L657 _delegate_ `DECLARE_EVENT_OneParam(IPluginManager, FLeakedPackagesFoundEvent, const FLeakedPackageCountPerPluginMap& );`

### `Source/Runtime/Projects/Public/Interfaces/IProjectManager.h` (Public)


#### class `FProjectStatus`  
`class FProjectStatus`  
_L14-65_
- desc: Simple data structure that is filled when querying information about projects
- L19 _public member_ `FString Name;` — The name of this project
- L22 _public member_ `FString Description;` — The description of this project
- L25 _public member_ `FString Category;` — The UI category of this project
- L28 _public member_ `bool bSignedSampleProject;` — True if this project is a sample provided by epic
- L31 _public member_ `bool bCodeBasedProject;` — True if the project is code-based
- L34 _public member_ `bool bRequiresUpdate;` — True if this project needs to be updated
- L37 _public member_ `TArray<FName> TargetPlatforms;` — Array of platforms that this project is targeting
- L39 _public function_ `FProjectStatus() : bSignedSampleProject(false) , bCodeBasedProject(false) , bRequiresUpdate(false)`
- L52 _public function_ `bool IsTargetPlatformSupported(const FName& InPlatformName, const bool bAllowSupportedIfEmptyList = true) const` — Check to see if the given platform name is supported as a target by the current project @todo platformcleanup: Make this use IniPlatformName, not TargetPlatformName!! And other related functions in here @param	InPlatformName				Name of the platform to target (eg, WindowsClient) @param	bAllowSupportedIfEmptyList	Consider an empty list to mean that all platforms are supported targets?
- L61 _public function_ `bool SupportsAllPlatforms() const` — Check to see if the given the current project supports all platforms

#### class `IProjectManager`  
`class IProjectManager`  
_L70-277_
- desc: ProjectAndPluginManager manages available code and content extensions (both loaded and not loaded.)
- L74 _public prototype_ `virtual ~IProjectManager() = default;`
- L81 _public prototype_ `static IProjectManager& Get();` — Static: Access singleton instance @return	Reference to the singleton object
- L88 _public prototype_ `virtual const FProjectDescriptor* GetCurrentProject() const = 0;` — Gets the current project descriptor. @return Pointer to the currently loaded project descriptor. NULL if none is loaded.
- L99 _public prototype_ `virtual bool LoadProjectFile( const FString& ProjectFile ) = 0;` — Loads the specified project file. @param ProjectFile - The project file to load. @return true if the project was loaded successfully, false otherwise. @see GetLoadedGameProjectFile
- L107 _public prototype_ `virtual bool LoadModulesForProject( const ELoadingPhase::Type LoadingPhase ) = 0;` — Loads all modules for the currently loaded project in the specified loading phase @param	LoadingPhase	Which loading phase we're loading modules from.  Only modules that are configured to be loaded at the specified loading phase will be loaded during this call.
- L116 _public prototype_ `virtual bool SubstituteModule(const FString& OriginalModuleName, const FString& NewModuleName) = 0;` — Replaces a referenced module with a new name @param	OriginalModuleName	Name of module to replace @param	NewModuleName		Name of replacement module
- L121 _public prototype_ `DECLARE_EVENT_TwoParams(IProjectManager, FLoadingModulesForPhaseEvent, ELoadingPhase::Type , bool );` — Callback for when modules for when LoadModulesForProject() completes loading for a specific phase.
- L122 _public prototype_ `virtual FLoadingModulesForPhaseEvent& OnLoadingPhaseComplete() = 0;`
- L130 _public prototype_ `virtual bool CheckModuleCompatibility(TArray<FString>& OutIncompatibleModules) = 0;` — Checks if the modules for a project are up to date @return	false if UBT needs to be run to recompile modules for a project.
- L140 _public prototype_ `virtual const FString& GetAutoLoadProjectFileName() = 0;` — Gets the name of the text file that contains the most recently loaded filename. This is NOT the name of the recently loaded .uproject file. @return File name.
- L153 _public prototype_ `virtual bool SignSampleProject(const FString& FilePath, const FString& Category, FText& OutFailReason) = 0;` — Sets the project's EpicSampleNameHash (based on its filename) and category, then saves the file to disk. This marks the project as a sample and fixes its filename so that it isn't mistaken for a sample if a copy of the file is made. @param FilePath				The filepath where the sample project is stored. @param Category				Category to place the sample in @param OutFailReason			When returning false, this provides a display reason why the file could not be created. @return true if the file was successfully updated and saved to disk
- L163 _public prototype_ `virtual bool QueryStatusForProject(const FString& FilePath, FProjectStatus& OutProjectStatus) const = 0;` — Gets status about the specified project @param FilePath				The filepath where the project is stored. @param OutProjectStatus		The status for the project. @return	 true if the file was successfully open and read
- L172 _public prototype_ `virtual bool QueryStatusForCurrentProject(FProjectStatus& OutProjectStatus) const = 0;` — Gets status about the current project @param OutProjectStatus		The status for the project. @return	 true if the file was successfully open and read
- L181 _public prototype_ `virtual void UpdateSupportedTargetPlatformsForProject(const FString& FilePath, const FName& InPlatformName, const bool bIsSupported) = 0;` — Update the list of supported target platforms for the target project based upon the parameters provided @param	FilePath			The filepath where the project is stored. @param	InPlatformName		Name of the platform to target (eg, WindowsClient) @param	bIsSupported		true if the platform should be supported by this project, false if it should not
- L189 _public prototype_ `virtual void UpdateSupportedTargetPlatformsForCurrentProject(const FName& InPlatformName, const bool bIsSupported) = 0;` — Update the list of supported target platforms for the current project based upon the parameters provided @param	InPlatformName		Name of the platform to target (eg, WindowsClient) @param	bIsSupported		true if the platform should be supported by this project, false if it should not
- L192 _public prototype_ `virtual void ClearSupportedTargetPlatformsForProject(const FString& FilePath) = 0;` — Clear the list of supported target platforms for the target project
- L195 _public prototype_ `virtual void ClearSupportedTargetPlatformsForCurrentProject() = 0;` — Clear the list of supported target platforms for the current project
- L198 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTargetPlatformsForCurrentProjectChangedEvent);` — Called when the target platforms for the current project are changed
- L199 _public prototype_ `virtual FOnTargetPlatformsForCurrentProjectChangedEvent& OnTargetPlatformsForCurrentProjectChanged() = 0;`
- L206 _public prototype_ `virtual bool HasDefaultPluginSettings() const = 0;` — Checks whether the current project has default settings for plugins (ie. does not enable any new plugins, or disable any default plugins) @return	True if the project has the default plugin settings.
- L218 _public prototype_ `virtual bool SetPluginEnabled(const FString& PluginName, bool bEnabled, FText& OutFailReason) = 0;` — Sets whether a plugin is enabled for the current project configuration. Potentially updates the current project descriptor, but does not save to disk and may require restarting to load it. @note Use IsCurrentProjectDirty() to tell whether the project was actually modified. @param	PluginName		Name of the plugin @param	bEnabled		Whether to enable or disable the plugin @param	OutFailReason	On failure, gives an error message @return	False on failure to update the current project descriptor.
- L223 _public prototype_ `virtual bool RemovePluginReference(const FString& PluginName, FText& OutFailReason) = 0;`
- L232 _public prototype_ `virtual bool UpdateAdditionalPluginDirectory(const FString& Dir, const bool bAddOrRemove) = 0;` — Updates a directory to be scanned for plugins (added or removed) @param Dir the directory to scan @param bAddOrRemove whether to add or remove the directory @return Whether the plugin directory list was changed.
- L235 _public prototype_ `virtual const TArray<FString>& GetAdditionalPluginDirectories() const = 0;` — Returns the list of additional directories to be scanned for plugins (aside from the engine and project plugin directories).
- L240 _public prototype_ `virtual bool IsCurrentProjectDirty() const = 0;` — Checks whether the current loaded project has been modified but not saved to disk
- L248 _public prototype_ `virtual bool SaveCurrentProjectToDisk(FText& OutFailReason) = 0;` — Saves the current project to the project path @param	OutFailReason	On failure, gives an error message @return	True if the project was saved successfully
- L255 _public prototype_ `virtual bool IsEnterpriseProject() = 0;` — Gets the enterprise flag value on the current project @return	True if the project is an Enterprise project
- L262 _public prototype_ `virtual void SetIsEnterpriseProject(bool bValue) = 0;` — Sets the enterprise flag value on the current project @param	bValue	The value to set the enterprise flag to
- L267 _public prototype_ `virtual TArray<FModuleContextInfo>& GetCurrentProjectModuleContextInfos() = 0;` — Access array used to cache current project's list of module context infos
- L270 _public prototype_ `virtual bool IsSuppressingProjectFileWrite() const = 0;` — Returns true if project file write should be suppressed.
- L273 _public prototype_ `virtual void AddSuppressProjectFileWrite(const FName InName) = 0;` — Suppress project file writes.
- L276 _public prototype_ `virtual void RemoveSuppressProjectFileWrite(const FName InName) = 0;` — Removes suppression of project file writes.

#### Free symbols / members of external scopes

- L121 _delegate_ `DECLARE_EVENT_TwoParams(IProjectManager, FLoadingModulesForPhaseEvent, ELoadingPhase::Type , bool );` — Callback for when modules for when LoadModulesForProject() completes loading for a specific phase.
- L198 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTargetPlatformsForCurrentProjectChangedEvent);` — Called when the target platforms for the current project are changed

### `Source/Runtime/Projects/Public/LocalizationDescriptor.h` (Public)


#### enum `ELocalizationTargetDescriptorLoadingPolicy::Type`  
`enum Type`  
_L19-35_
- L22 _public enumerator_ `Never` — The localization data will never be loaded automatically.
- L24 _public enumerator_ `Always` — The localization data will always be loaded automatically.
- L26 _public enumerator_ `Editor` — The localization data will only be loaded when running the editor. Use if the target localizes the editor.
- L28 _public enumerator_ `Game` — The localization data will only be loaded when running the game. Use if the target localizes your game.
- L30 _public enumerator_ `PropertyNames` — The localization data will only be loaded if the editor is displaying localized property names.
- L32 _public enumerator_ `ToolTips` — The localization data will only be loaded if the editor is displaying localized tool tips.
- L34 _public enumerator_ `Max` — NOTE: If you add a new value, make sure to update the ToString() method below!.

#### enum `ELocalizationConfigGenerationPolicy::Type`  
`enum Type`  
_L57-67_
- L60 _public enumerator_ `Never` — This localization target does not have localization config files associated with it and no localization content files will be generated for it during the localizaiton pipeline.
- L62 _public enumerator_ `User` — The user has provided localization config files for this localization target and they will be used to generate the localization content files for the localization target.
- L64 _public enumerator_ `Auto` — Temporary localization config files will be generated for the localization target during the localization pipeline to generate the localization content files. After the localization pipeline is complete, the temporary files will be deleted.
- L66 _public enumerator_ `Max` — NOTE: If you add a new value, make sure to update the ToString() method below!.

#### struct `FLocalizationTargetDescriptor`  
`struct FLocalizationTargetDescriptor`  
_L90-130_
- desc: Description of a localization target.
- L93 _public member_ `FString Name;` — Name of this target
- L96 _public member_ `ELocalizationTargetDescriptorLoadingPolicy::Type LoadingPolicy;` — When should the localization data associated with a target should be loaded?
- L99 _public member_ `ELocalizationConfigGenerationPolicy::Type ConfigGenerationPolicy;` — How the localizationc config files associated with the localization target are generated
- L102 _public prototype_ `FLocalizationTargetDescriptor(FString InName = FString(), ELocalizationTargetDescriptorLoadingPolicy::Type InLoadingPolicy = ELocalizationTargetDescriptorLoadingPolicy::Never, ELocalizationConfigGenerationPolicy::Type InGenerationPolicy = ELocalizationConfigGenerationPolicy::Never);` — Normal constructor
- L105 _public prototype_ `bool Read(const FJsonObject& InObject, FText* OutFailReason = nullptr);` — Reads a descriptor from the given JSON object
- L108 _public prototype_ `bool Read(const FJsonObject& InObject, FText& OutFailReason);` — Reads a descriptor from the given JSON object
- L111 _public prototype_ `static bool ReadArray(const FJsonObject& InObject, const TCHAR* InName, TArray<FLocalizationTargetDescriptor>& OutTargets, FText* OutFailReason = nullptr);` — Reads an array of targets from the given JSON object
- L114 _public prototype_ `static bool ReadArray(const FJsonObject& InObject, const TCHAR* InName, TArray<FLocalizationTargetDescriptor>& OutTargets, FText& OutFailReason);` — Reads an array of targets from the given JSON object
- L117 _public prototype_ `void Write(TJsonWriter<>& Writer) const;` — Writes a descriptor to JSON
- L120 _public prototype_ `void UpdateJson(FJsonObject& JsonObject) const;` — Updates the given json object with values in this descriptor
- L123 _public prototype_ `static void WriteArray(TJsonWriter<>& Writer, const TCHAR* ArrayName, const TArray<FLocalizationTargetDescriptor>& Descriptors);` — Writes an array of targets to JSON
- L126 _public prototype_ `static void UpdateArray(FJsonObject& JsonObject, const TCHAR* ArrayName, const TArray<FLocalizationTargetDescriptor>& Descriptors);` — Updates an array of descriptors in the specified JSON field (indexed by name)
- L129 _public prototype_ `bool ShouldLoadLocalizationTarget() const;` — Returns true if we should load this localization target based upon the current runtime environment

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ELocalizationTargetDescriptorLoadingPolicy`
- L43 _prototype_ `ELocalizationTargetDescriptorLoadingPolicy::Type FromString(const TCHAR *Text);` (scope `ELocalizationTargetDescriptorLoadingPolicy`) — Converts a string to a ELocalizationTargetDescriptorLoadingPolicy::Type value @param	The string to convert to a value @return	The corresponding value, or 'Max' if the string is not valid.
- L51 _prototype_ `const TCHAR* ToString(const ELocalizationTargetDescriptorLoadingPolicy::Type Value);` (scope `ELocalizationTargetDescriptorLoadingPolicy`) — Returns the name of a localization loading policy. @param	The value to convert to a string @return	The string representation of this enum value
- L55 _namespace_ `namespace ELocalizationConfigGenerationPolicy`
- L75 _prototype_ `ELocalizationConfigGenerationPolicy::Type FromString(const TCHAR* Text);` (scope `ELocalizationConfigGenerationPolicy`) — Converts a string to a ELocalizationConfigGenerationPolicy::Type value @param	The string to convert to a value @return	The corresponding value, or 'Max' if the string is not valid.
- L83 _prototype_ `const TCHAR* ToString(const ELocalizationConfigGenerationPolicy::Type Value);` (scope `ELocalizationConfigGenerationPolicy`) — Returns the name of a ELocalizationConfigGenerationPolicy::Type @param	The value to convert to a string @return	The string representation of this enum value

### `Source/Runtime/Projects/Public/ModuleDescriptor.h` (Public)


#### enum `ELoadingPhase::Type`  
`enum Type`  
_L26-60_
- L29 _public enumerator_ `EarliestPossible` — As soon as possible - in other words, uplugin files are loadable from a pak file (as well as right after PlatformFile is set up in case pak files aren't used) Used for plugins needed to read files (compression formats, etc)
- L32 _public enumerator_ `PostConfigInit` — Loaded before the engine is fully initialized, immediately after the config system has been initialized.  Necessary only for very low-level hooks
- L35 _public enumerator_ `PostSplashScreen` — The first screen to be rendered after system splash screen
- L38 _public enumerator_ `PreEarlyLoadingScreen` — Loaded before coreUObject for setting up manual loading screens, used for our chunk patching system
- L41 _public enumerator_ `PreLoadingScreen` — Loaded before the engine is fully initialized for modules that need to hook into the loading screen before it triggers
- L44 _public enumerator_ `PreDefault` — Right before the default phase
- L47 _public enumerator_ `Default` — Loaded at the default loading point during startup (during engine init, after game modules are loaded.)
- L50 _public enumerator_ `PostDefault` — Right after the default phase
- L53 _public enumerator_ `PostEngineInit` — After the engine has been initialized
- L56 _public enumerator_ `None` — Do not automatically load this module
- L59 _public enumerator_ `Max` — NOTE: If you add a new value, make sure to update the ToString() method below!

#### enum `EHostType::Type`  
`enum Type : int`  
_L84-132_
- L87 _public enumerator_ `Runtime` — Loads on all targets, except programs.
- L90 _public enumerator_ `RuntimeNoCommandlet` — Loads on all targets, except programs and the editor running commandlets.
- L93 _public enumerator_ `RuntimeAndProgram` — Loads on all targets, including supported programs.
- L96 _public enumerator_ `CookedOnly` — Loads only in cooked games.
- L99 _public enumerator_ `UncookedOnly` — Only loads in uncooked games.
- L104 _public enumerator_ `Developer` — Deprecated due to ambiguities. Only loads in editor and program targets, but loads in any editor mode (eg. -game, -server). Use UncookedOnly for the same behavior (eg. for editor blueprint nodes needed in uncooked games), or DeveloperTool for modules that can also be loaded in cooked games but should not be shipped (eg. debugging utilities).
- L107 _public enumerator_ `DeveloperTool` — Loads on any targets where bBuildDeveloperTools is enabled.
- L110 _public enumerator_ `Editor` — Loads only when the editor is starting up.
- L113 _public enumerator_ `EditorNoCommandlet` — Loads only when the editor is starting up, but not in commandlet mode.
- L116 _public enumerator_ `EditorAndProgram` — Loads only on editor and program targets
- L119 _public enumerator_ `Program` — Only loads on program targets.
- L122 _public enumerator_ `ServerOnly` — Loads on all targets except dedicated clients.
- L125 _public enumerator_ `ClientOnly` — Loads on all targets except dedicated servers.
- L128 _public enumerator_ `ClientOnlyNoCommandlet` — Loads in editor and client but not in commandlets.
- L131 _public enumerator_ `Max`

#### struct `FModuleDescriptor`  
`struct FModuleDescriptor`  
_L154-254_
- desc: Description of a loadable module.
- L157 _public member_ `FName Name;` — Name of this module
- L160 _public member_ `EHostType::Type Type;` — Usage type of module
- L163 _public member_ `ELoadingPhase::Type LoadingPhase;` — When should the module be loaded during the startup sequence?  This is sort of an advanced setting.
- L166 _public member_ `TArray<FString> PlatformAllowList;` — List of allowed platforms
- L169 _public member_ `TArray<FString> PlatformDenyList;` — List of disallowed platforms
- L172 _public member_ `TMap<FString,TArray<FString>> PlatformArchitectureAllowList;` — List of allowed platform architectures
- L175 _public member_ `TMap<FString,TArray<FString>> PlatformArchitectureDenyList;` — List of disallowed platform architectures
- L178 _public member_ `TArray<EBuildTargetType> TargetAllowList;` — List of allowed targets
- L181 _public member_ `TArray<EBuildTargetType> TargetDenyList;` — List of disallowed targets
- L184 _public member_ `TArray<EBuildConfiguration> TargetConfigurationAllowList;` — List of allowed target configurations
- L187 _public member_ `TArray<EBuildConfiguration> TargetConfigurationDenyList;` — List of disallowed target configurations
- L190 _public member_ `TArray<FString> ProgramAllowList;` — List of allowed programs
- L193 _public member_ `TArray<FString> ProgramDenyList;` — List of disallowed programs
- L196 _public member_ `TArray<FString> GameTargetAllowList;` — List of allowed game targets
- L199 _public member_ `TArray<FString> GameTargetDenyList;` — List of disallowed game targets
- L202 _public member_ `TArray<FString> AdditionalDependencies;` — List of additional dependencies for building this module.
- L205 _public member_ `bool bHasExplicitPlatforms;` — When true, an empty PlatformAllowList is interpeted as 'no platforms' with the expectation that explict platforms will be added in plugin extensions
- L209 _public prototype_ `FModuleDescriptor(const FName InName = NAME_None, EHostType::Type InType = EHostType::Runtime, ELoadingPhase::Type InLoadingPhase = ELoadingPhase::Default);` — Normal constructor
- L212 _public prototype_ `bool Read(const FJsonObject& Object, FText* OutFailReason = nullptr);` — Reads a descriptor from the given JSON object
- L215 _public prototype_ `bool Read(const FJsonObject& Object, FText& OutFailReason);` — Reads a descriptor from the given JSON object
- L218 _public prototype_ `static bool ReadArray(const FJsonObject& Object, const TCHAR* Name, TArray<FModuleDescriptor>& OutModules, FText* OutFailReason = nullptr);` — Reads an array of modules from the given JSON object
- L221 _public prototype_ `static bool ReadArray(const FJsonObject& Object, const TCHAR* Name, TArray<FModuleDescriptor>& OutModules, FText& OutFailReason);` — Reads an array of modules from the given JSON object
- L224 _public prototype_ `void Write(TJsonWriter<>& Writer) const;` — Writes a descriptor to JSON
- L227 _public prototype_ `void UpdateJson(FJsonObject& JsonObject) const;` — Updates the given json object with values in this descriptor
- L230 _public prototype_ `static void WriteArray(TJsonWriter<>& Writer, const TCHAR* ArrayName, const TArray<FModuleDescriptor>& Modules);` — Writes an array of modules to JSON
- L233 _public prototype_ `static void UpdateArray(FJsonObject& JsonObject, const TCHAR* ArrayName, const TArray<FModuleDescriptor>& Modules);` — Updates an array of module descriptors in the specified JSON field (indexed by module name)
- L236 _public prototype_ `bool IsCompiledInConfiguration(const FString& Platform, EBuildConfiguration Configuration, const FString& TargetName, EBuildTargetType TargetType, bool bBuildDeveloperTools, bool bBuildRequiresCookedData, const FString& Architecture = FString()) const;` — Tests whether the module should be built for the given target
- L239 _public prototype_ `bool IsCompiledInCurrentConfiguration() const;` — Tests whether the module should be built for the current engine configuration
- L242 _public prototype_ `bool IsLoadedInCurrentConfiguration() const;` — Tests whether the module should be loaded for the current engine configuration
- L245 _public prototype_ `static void LoadModulesForPhase(ELoadingPhase::Type LoadingPhase, const TArray<FModuleDescriptor>& Modules, TMap<FName, EModuleLoadResult>& ModuleLoadErrors);` — Loads all the modules for a given loading phase. Returns a map of module names to load errors
- L248 _public prototype_ `static void UnloadModulesForPhase(ELoadingPhase::Type LoadingPhase, const TArray<FModuleDescriptor>& Modules, TMap<FName, EModuleUnloadResult>& OutErrors, bool bSkipUnload = false, bool bAllowUnloadCode = true);` — Unloads all the modules for a given loading phase. Returns a map of module names to load errors. bSkipUnload can be used to simulate unloading
- L252 _public prototype_ `static bool CheckModuleCompatibility(const TArray<FModuleDescriptor>& Modules, TArray<FString>& OutIncompatibleFiles);` — Checks that all modules are compatible with the current engine version. Returns false and appends a list of names to OutIncompatibleFiles if not.

#### struct `FModuleContextInfo`  
`struct FModuleContextInfo`  
_L257-267_
- desc: Context information used when validating that source code is being placed in the correct place for a given module
- L260 _public member_ `FString ModuleSourcePath;` — Path to the Source folder of the module
- L263 _public member_ `FString ModuleName;` — Name of the module
- L266 _public member_ `EHostType::Type ModuleType;` — Type of this module, eg, Runtime, Editor, etc

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace ELoadingPhase`
- L68 _prototype_ `ELoadingPhase::Type FromString( const TCHAR *Text );` (scope `ELoadingPhase`) — Converts a string to a ELoadingPhase::Type value @param	The string to convert to a value @return	The corresponding value, or 'Max' if the string is not valid.
- L76 _prototype_ `const TCHAR* ToString( const ELoadingPhase::Type Value );` (scope `ELoadingPhase`) — Returns the name of a module load phase. @param	The value to convert to a string @return	The string representation of this enum value
- L82 _namespace_ `namespace EHostType`
- L140 _prototype_ `EHostType::Type FromString( const TCHAR *Text );` (scope `EHostType`) — Converts a string to a EHostType::Type value @param	The string to convert to a value @return	The corresponding value, or 'Max' if the string is not valid.
- L148 _prototype_ `const TCHAR* ToString( const EHostType::Type Value );` (scope `EHostType`) — Converts an EHostType::Type value to a string literal @param	The value to convert to a string @return	The string representation of this enum value

### `Source/Runtime/Projects/Public/PluginDescriptor.h` (Public)


#### enum `EPluginEnabledByDefault`  
`enum class EPluginEnabledByDefault : uint8`  
_L28-33_
- desc: Setting for whether a plugin is enabled by default
- L30 _public enumerator_ `Unspecified`
- L31 _public enumerator_ `Enabled`
- L32 _public enumerator_ `Disabled`

#### struct `FPluginDescriptor`  
`struct FPluginDescriptor`  
_L38-257_
- desc: Descriptor for plugins. Contains all the information contained within a .uplugin file.
- L43 _public member_ `int32 Version;` — Version number for the plugin.  The version number must increase with every version of the plugin, so that the system can determine whether one version of a plugin is newer than another, or to enforce other requirements.  This version number is not displayed in front-facing UI.  Use the VersionName for that.
- L47 _public member_ `FString VersionName;` — Name of the version for this plugin.  This is the front-facing part of the version number.  It doesn't need to match the version number numerically, but should be updated when the version number is increased accordingly.
- L50 _public member_ `FString FriendlyName;` — Friendly name of the plugin
- L53 _public member_ `FString Description;` — Description of the plugin
- L56 _public member_ `FString Category;` — The name of the category this plugin
- L59 _public member_ `FString CreatedBy;` — The company or individual who created this plugin.  This is an optional field that may be displayed in the user interface.
- L62 _public member_ `FString CreatedByURL;` — Hyperlink URL string for the company or individual who created this plugin.  This is optional.
- L65 _public member_ `FString DocsURL;` — Documentation URL string.
- L68 _public member_ `FString MarketplaceURL;` — Marketplace URL for this plugin. This URL will be embedded into projects that enable this plugin, so we can redirect to the marketplace if a user doesn't have it installed.
- L71 _public member_ `FString SupportURL;` — Support URL/email for this plugin.
- L74 _public member_ `FString EngineVersion;` — Version of the engine that this plugin is compatible with
- L77 _public member_ `FString EditorCustomVirtualPath;` — Optional custom virtual path to display in editor to better organize. Inserted just before this plugin's directory in the path: /All/Plugins/EditorCustomVirtualPath/PluginName
- L81 _public member_ `TArray<FString> SupportedTargetPlatforms;` — Controls a subset of platforms that can use this plugin, and which ones will stage the .uplugin file and content files. Generally, for code plugins, it should be the union of platforms that the modules in the plugin are compiled for.
- L84 _public member_ `TArray<FString> SupportedPrograms;` — List of programs that are supported by this plugin.
- L87 _public member_ `FString ParentPluginName;` — If specified, this is the real plugin that this one is just extending
- L90 _public member_ `TArray<FModuleDescriptor> Modules;` — List of all modules associated with this plugin
- L93 _public member_ `TArray<FLocalizationTargetDescriptor> LocalizationTargets;` — List of all localization targets associated with this plugin
- L96 _public member_ `FString VersePath;` — The Verse path to the root of this plugin's content directory
- L99 _public member_ `FString DeprecatedEngineVersion;` — Set when a plugin is loaded that has the DeprecatedEngineVersion set.
- L103 _public member_ `TOptional<uint32> VerseVersion;` — The version of the Verse language that this plugin targets. If no value is specified, the latest stable version is used.
- L106 _public member_ `EVerseScope::Type VerseScope = EVerseScope::PublicUser;` — Origin/visibility of Verse code in this plugin's Content/Verse folder
- L109 _public member_ `bool bEnableSceneGraph = false;` — Whether this plugin has SceneGraph enabled, which impacts the generated Verse Asset Digest.
- L112 _public member_ `bool bEnableSceneGraphAnimation = false;` — Whether this plugin has SceneGraph Animation enabled, which impacts the generated Verse Asset Digest.
- L115 _public member_ `bool bEnableVerseAssetReflection = false;` — If to generate Verse source code definitions from assets contained in this plugin
- L118 _public member_ `bool bEnableIAD = false;` — Use IAD for this plugin
- L121 _public member_ `bool bEnableIAS = true;` — Use IAS for this plugin. This is likely to be removed in the near future.
- L124 _public member_ `EPluginEnabledByDefault EnabledByDefault;` — Whether this plugin should be enabled by default for all projects
- L127 _public member_ `bool bCanContainContent;` — Can this plugin contain content?
- L130 _public member_ `bool bCanContainVerse;` — Can this plugin contain Verse code?
- L133 _public member_ `bool bIsBetaVersion;` — Marks the plugin as beta in the UI
- L136 _public member_ `bool bIsExperimentalVersion;` — Marks the plugin as experimental in the UI
- L139 _public member_ `bool bInstalled;` — Signifies that the plugin was installed on top of the engine
- L142 _public member_ `bool bRequiresBuildPlatform;` — For plugins that are under a platform folder (eg. /PS4/), determines whether compiling the plugin requires the build platform and/or SDK to be available
- L145 _public member_ `bool bIsHidden;` — For auto-generated plugins that should not be listed in the plugin browser for users to disable freely.
- L148 _public member_ `bool bIsSealed;` — Prevents other plugins from depending on this plugin.
- L151 _public member_ `bool bNoCode;` — Prevents this plugin from containing code or modules.
- L154 _public member_ `bool bExplicitlyLoaded;` — When true, this plugin's modules will not be loaded automatically nor will it's content be mounted automatically. It will load/mount when explicitly requested and LoadingPhases will be ignored
- L157 _public member_ `bool bHasExplicitPlatforms;` — When true, an empty SupportedTargetPlatforms is interpreted as 'no platforms' with the expectation that explicit platforms will be added in plugin platform extensions
- L160 _public member_ `bool bIsPluginExtension;` — If true, this plugin from a platform extension extending another plugin
- L163 _public member_ `bool bNoGameFeatureContent = false;` — If true, the GameFeaturePlugin this is on should have no content other than the GameFeatureData asset.
- L167 _public member_ `FCustomBuildSteps PreBuildSteps;` — Pre-build steps for each host platform
- L170 _public member_ `FCustomBuildSteps PostBuildSteps;` — Post-build steps for each host platform
- L174 _public member_ `TArray<FPluginReferenceDescriptor> Plugins;` — Plugins used by this plugin
- L177 _public member_ `TArray<FPluginDisallowedDescriptor> DisallowedPlugins;` — Plugins that cannot be used by this plugin
- L182 _public member_ `mutable TSharedPtr<FJsonObject> CachedJson;` — Cached json for custom data
- L185 _public member_ `TMap<FString, TSharedPtr<FJsonValue>> AdditionalFieldsToWrite;` — Additional fields to write
- L188 _public member_ `TSet<FString> AdditionalFieldsToRemove;` — Additional fields to remove when updating the Json
- L192 _public prototype_ `static const FString& GetFileExtension();` — Return the .uplugin extension (with dot)
- L195 _public prototype_ `FPluginDescriptor();` — Constructor.
- L198 _public prototype_ `bool Load(const TCHAR* FileName, FText* OutFailReason = nullptr);` — Loads the descriptor from the given file.
- L201 _public prototype_ `bool Load(const FString& FileName, FText* OutFailReason = nullptr);` — Loads the descriptor from the given file.
- L204 _public prototype_ `bool Load(const FString& FileName, FText& OutFailReason);` — Loads the descriptor from the given file.
- L207 _public prototype_ `bool ReadWithCustomPluginDescriptorReader(const TCHAR* FileName, FText* OutFailReason = nullptr);` — Reads the descriptor using the global CustomPluginDescriptorReaderDelegate
- L210 _public prototype_ `bool Read(const FString& Text, FText* OutFailReason = nullptr);` — Reads the descriptor from the given string
- L213 _public prototype_ `bool Read(const FString& Text, FText& OutFailReason);` — Reads the descriptor from the given string
- L216 _public prototype_ `bool Read(const FJsonObject& Object, FText* OutFailReason = nullptr);` — Reads the descriptor from the given JSON object
- L219 _public prototype_ `bool Read(const FJsonObject& Object, FText& OutFailReason);` — Reads the descriptor from the given JSON object
- L222 _public prototype_ `bool Save(const TCHAR* FileName, FText* OutFailReason = nullptr) const;` — Saves the descriptor to the given file.
- L225 _public prototype_ `bool Save(const FString& FileName, FText* OutFailReason = nullptr) const;` — Saves the descriptor to the given file.
- L228 _public prototype_ `bool Save(const FString& FileName, FText& OutFailReason) const;` — Saves the descriptor to the given file.
- L231 _public prototype_ `void Write(FString& Text) const;` — Writes a descriptor to JSON
- L234 _public prototype_ `void Write(TJsonWriter<>& Writer) const;` — Writes a descriptor to JSON
- L237 _public prototype_ `void UpdateJson(FJsonObject& JsonObject) const;` — Updates the given json object with values in this descriptor
- L243 _public prototype_ `bool UpdatePluginFile(const FString& FileName, FText* OutFailReason = nullptr) const;` — Updates the content of the specified plugin file with values in this descriptor (hence preserving json fields that the plugin descriptor doesn't know about)
- L249 _public prototype_ `bool UpdatePluginFile(const FString& FileName, FText& OutFailReason) const;` — Updates the content of the specified plugin file with values in this descriptor (hence preserving json fields that the plugin descriptor doesn't know about)
- L252 _public prototype_ `bool SupportsTargetPlatform(const FString& Platform) const;` — Determines whether the plugin supports the given platform
- L255 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FPluginDescriptorReaderDelegate, const TCHAR* , FText* , TSharedPtr<FJsonObject>& , bool& );` — Custom hook for providing a plugin descriptor (as an FJsonObject) based on a filename
- L256 _public member_ `static FPluginDescriptorReaderDelegate CustomPluginDescriptorReaderDelegate;`

#### Free symbols / members of external scopes

- L255 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FPluginDescriptorReaderDelegate, const TCHAR* , FText* , TSharedPtr<FJsonObject>& , bool& );` — Custom hook for providing a plugin descriptor (as an FJsonObject) based on a filename
- L259 _namespace_ `namespace UE`
- L259 _namespace_ `namespace PluginDescriptor` (scope `UE`)
- L259 _namespace_ `namespace Internal` (scope `UE::PluginDescriptor`)
- L261 _prototype_ `bool ReadFile(const TCHAR* FileName, FString& Text, FText* OutFailReason = nullptr);` (scope `UE::PluginDescriptor::Internal`)
- L262 _prototype_ `TSharedPtr<FJsonObject> DeserializeJson(const FString& Text, FText* OutFailReason = nullptr);` (scope `UE::PluginDescriptor::Internal`)

### `Source/Runtime/Projects/Public/PluginDisallowedDescriptor.h` (Public)


#### struct `FPluginDisallowedDescriptor`  
`struct FPluginDisallowedDescriptor`  
_L14-38_
- L16 _public member_ `FString Name;`
- L19 _public member_ `FString Comment;`
- L23 _public prototype_ `bool Read(const FJsonObject& Object, FText* OutFailReason = nullptr);` — Reads the descriptor from the given JSON object
- L26 _public prototype_ `void Write(TJsonWriter<>& Writer) const;` — Writes a descriptor to JSON
- L29 _public prototype_ `void UpdateJson(FJsonObject& JsonObject) const;` — Updates the given json object with values in this descriptor
- L31 _public prototype_ `static bool ReadArray(const FJsonObject& Object, const TCHAR* Name, TArray<FPluginDisallowedDescriptor>& OutPlugins, FText* OutFailReason = nullptr);`
- L34 _public prototype_ `static void WriteArray(TJsonWriter<>& Writer, const TCHAR* ArrayName, const TArray<FPluginDisallowedDescriptor>& Plugins);` — Writes an array of plugin references to JSON
- L37 _public prototype_ `static void UpdateArray(FJsonObject& JsonObject, const TCHAR* ArrayName, const TArray<FPluginDisallowedDescriptor>& Plugins);` — Updates an array of plugin references in the specified JSON field (indexed by plugin name)

### `Source/Runtime/Projects/Public/PluginManifest.h` (Public)


#### struct `FPluginManifestEntry`  
`struct FPluginManifestEntry`  
_L16-23_
- desc: Descriptor for plugins. Contains all the information contained within a .uplugin file.
- L19 _public member_ `FString File;` — Normalized path to the plugin file
- L22 _public member_ `FPluginDescriptor Descriptor;` — The plugin descriptor

#### struct `FPluginManifest`  
`struct FPluginManifest`  
_L28-38_
- desc: Manifest of plugins. Descriptor for plugins. Contains all the information contained within a .uplugin file.
- L31 _public member_ `TArray<FPluginManifestEntry> Contents;` — List of plugins in this manifest
- L34 _public prototype_ `bool Load(const FString& FileName, FText& OutFailReason);` — Loads the descriptor from the given file.
- L37 _public prototype_ `bool Read(const FJsonObject& Object, FText& OutFailReason);` — Reads the descriptor from the given JSON object

### `Source/Runtime/Projects/Public/PluginReferenceDescriptor.h` (Public)


#### struct `FPluginReferenceDescriptor`  
`struct FPluginReferenceDescriptor`  
_L26-130_
- desc: Descriptor for a plugin reference. Contains the information required to enable or disable a plugin for a given platform.
- L29 _public member_ `FString Name;` — Name of the plugin
- L32 _public member_ `bool bEnabled;` — Whether it should be enabled by default
- L35 _public member_ `bool bOptional;` — Whether this plugin is optional, and the game should silently ignore it not being present
- L38 _public member_ `bool bActivate;` — Whether this plugin dependency should also activate when the parent plugin is activated by the GameFeaturePlugin system.
- L41 _public member_ `bool bHasExplicitPlatforms;` — When true, empty SupportedTargetPlatforms and PlatformAllowList are interpreted as 'no platforms' with the expectation that explicit platforms will be added in plugin platform extensions
- L44 _public member_ `FString Description;` — Description of the plugin for users that do not have it installed.
- L47 _public member_ `FString MarketplaceURL;` — URL for this plugin on the marketplace, if the user doesn't have it installed.
- L50 _public member_ `TArray<FString> PlatformAllowList;` — If enabled, list of platforms for which the plugin should be enabled (or all platforms if blank).
- L53 _public member_ `TArray<FString> PlatformDenyList;` — If enabled, list of platforms for which the plugin should be disabled.
- L56 _public member_ `TArray<EBuildConfiguration> TargetConfigurationAllowList;` — If enabled, list of target configurations for which the plugin should be enabled (or all target configurations if blank).
- L59 _public member_ `TArray<EBuildConfiguration> TargetConfigurationDenyList;` — If enabled, list of target configurations for which the plugin should be disabled.
- L62 _public member_ `TArray<EBuildTargetType> TargetAllowList;` — If enabled, list of targets for which the plugin should be enabled (or all targets if blank).
- L65 _public member_ `TArray<EBuildTargetType> TargetDenyList;` — If enabled, list of targets for which the plugin should be disabled.
- L68 _public member_ `TArray<EBuildTargetType> TargetsToExplicitlyLoad;` — Overrides the loading phase in uplugin so that a plugin can be explicitly loaded for specified targets.
- L71 _public member_ `TArray<FString> SupportedTargetPlatforms;` — The list of supported target platforms for this plugin. This field is copied from the plugin descriptor, and supplements the user's allowed/denied platforms.
- L74 _public member_ `TOptional<int32> RequestedVersion;` — When set, specifies a specific version of the plugin that this references.
- L78 _public member_ `mutable TSharedPtr<FJsonObject> CachedJson;` — Cached json for custom data
- L81 _public member_ `TMap<FString, TSharedPtr<FJsonValue>> AdditionalFieldsToWrite;` — Additional fields to write
- L85 _public prototype_ `FPluginReferenceDescriptor(FString InName = TEXT(""), bool bInEnabled = false);` — Constructor
- L88 _public prototype_ `bool IsEnabledForPlatform(const FString& Platform) const;` — Determines whether the plugin is enabled for the given platform
- L91 _public prototype_ `bool IsEnabledForTargetConfiguration(EBuildConfiguration Configuration) const;` — Determines whether the plugin is enabled for the given target configuration
- L94 _public prototype_ `bool IsEnabledForTarget(EBuildTargetType TargetType) const;` — Determines whether the plugin is enabled for the given target
- L97 _public prototype_ `bool IsSupportedTargetPlatform(const FString& Platform) const;` — Determines if the referenced plugin is supported for the given platform
- L100 _public prototype_ `bool Read(const TSharedRef<FJsonObject>& Object, FText* OutFailReason = nullptr);` — Reads the descriptor from the given JSON object
- L103 _public prototype_ `bool Read(const FJsonObject& Object, FText* OutFailReason = nullptr, TSharedPtr<FJsonObject> ObjectPtr = nullptr);` — `UE_DEPRECATED(5.1, "Use Read(const TSharedRef<FJsonObject>&) instead.")`
- L106 _public prototype_ `bool Read(const FJsonObject& Object, FText& OutFailReason, TSharedPtr<FJsonObject> ObjectPtr = nullptr);` — `UE_DEPRECATED(5.1, "Use Read(const TSharedRef<FJsonObject>&) instead.")`
- L109 _public prototype_ `static bool ReadArray(const FJsonObject& Object, const TCHAR* Name, TArray<FPluginReferenceDescriptor>& OutModules, FText* OutFailReason = nullptr);` — Reads an array of modules from the given JSON object
- L112 _public prototype_ `static bool ReadArray(const FJsonObject& Object, const TCHAR* Name, TArray<FPluginReferenceDescriptor>& OutModules, FText& OutFailReason);` — Reads an array of modules from the given JSON object
- L115 _public prototype_ `void Write(TJsonWriter<>& Writer) const;` — Writes a descriptor to JSON
- L118 _public prototype_ `void UpdateJson(FJsonObject& JsonObject) const;` — Updates the given json object with values in this descriptor
- L121 _public prototype_ `static void WriteArray(TJsonWriter<>& Writer, const TCHAR* ArrayName, const TArray<FPluginReferenceDescriptor>& Plugins);` — Writes an array of plugin references to JSON
- L124 _public prototype_ `static void UpdateArray(FJsonObject& JsonObject, const TCHAR* ArrayName, const TArray<FPluginReferenceDescriptor>& Plugins);` — Updates an array of plugin references in the specified JSON field (indexed by plugin name)
- L128 _public prototype_ `bool GetAdditionalStringField(const FString& Key, FString& OutValue) const;` — Gets the string value for a given key by first looking into AdditionalFieldsToWrite and then CachedJson

### `Source/Runtime/Projects/Public/ProjectDescriptor.h` (Public)


#### enum `EProjectDescriptorVersion::Type`  
`enum Type`  
_L25-36_
- L27 _public enumerator_ `Invalid = 0`
- L28 _public enumerator_ `Initial = 1`
- L29 _public enumerator_ `NameHash = 2`
- L30 _public enumerator_ `ProjectPluginUnification = 3`
- L34 _public enumerator_ `LatestPlusOne` — !!!!!!!!!! IMPORTANT: Remember to also update LatestPluginDescriptorFileVersion in Plugins.cs (and Plugin system documentation) when this changes!!!!!!!!!!! -----<new versions can be added before this line>------------------------------------------------- - this needs to be the last line (see note below)
- L35 _public enumerator_ `Latest = LatestPlusOne - 1`

#### struct `FProjectDescriptor`  
`struct FProjectDescriptor`  
_L42-208_
- desc: Descriptor for projects. Contains all the information contained within a .uproject file.
- L45 _public member_ `EProjectDescriptorVersion::Type FileVersion;` — Descriptor version number.
- L76 _public member_ `FString EngineAssociation;` — The engine to open this project with. Set this value using IDesktopPlatform::SetEngineIdentifierForProject to ensure that the most portable value for this field is used. This field allows us to open the right version of the engine when you double-click on a .uproject file, and to detect when you open a project with a different version of the editor and need the upgrade/downgrade UI flow. The normal engine version doesn't work for those purposes, because you can have multiple 4.x branches in various states on one machine. For Launcher users, this field gets set to something stable like "4.7" or "4.8", so you can swap projects and game binaries between users, and it'll automatically work on any platform or machine regardless of where the engine is installed. You can only have one binary release of each major engine version installed at once. For Perforce or Git users that branch the engine along with their games, this field is left blank. You can sync the repository down on any platform and machine, and it can figure out which engine a project should use by looking up the directory hierarchy until it finds one. For other cases, where you have a source build of the engine but are working with a foreign project, we use a random identifier for each local engine installation and use the registry to map it back to the engine directory. All bets are off as to which engine you should use to open it on a different machine, and using a random GUID ensures that every new machine triggers
- L79 _public member_ `FString Category;` — Category to show under the project browser
- L82 _public member_ `FString Description;` — Description to show in the project browser
- L85 _public member_ `TArray<FModuleDescriptor> Modules;` — List of all modules associated with this project
- L88 _public member_ `TArray<FPluginReferenceDescriptor> Plugins;` — List of plugins for this project (may be enabled/disabled)
- L91 _public member_ `TArray<FName> TargetPlatforms;` — Array of platforms that this project is targeting
- L94 _public member_ `uint32 EpicSampleNameHash;` — A hash that is used to determine if the project was forked from a sample
- L97 _public member_ `FCustomBuildSteps PreBuildSteps;` — Custom steps to execute before building targets in this project
- L100 _public member_ `FCustomBuildSteps PostBuildSteps;` — Custom steps to execute after building targets in this project
- L103 _public member_ `bool bIsEnterpriseProject;` — Indicates if this project is an Enterprise project
- L106 _public member_ `bool bDisableEnginePluginsByDefault;` — Indicates that enabled by default engine plugins should not be enabled unless explicitly enabled by the project or target files.
- L109 _public prototype_ `FProjectDescriptor();` — Constructor.
- L112 _public prototype_ `void Sign(const FString& FilePath);` — Signs the project given for the given filename
- L115 _public prototype_ `bool IsSigned(const FString& FilePath) const;` — Checks whether the descriptor is signed
- L118 _public prototype_ `int32 FindPluginReferenceIndex(const FString& PluginName) const;` — Finds the index of a plugin in the references array
- L121 _public prototype_ `void UpdateSupportedTargetPlatforms(const FName& InPlatformName, bool bIsSupported);` — Updates the supported target platforms list
- L124 _public prototype_ `bool Load(const FString& FileName, FText& OutFailReason);` — Loads the descriptor from the given file.
- L127 _public prototype_ `bool Read(const FJsonObject& Object, const FString& PathToProject, FText& OutFailReason);` — Reads the descriptor from the given JSON object
- L130 _public prototype_ `bool Save(const FString& FileName, FText& OutFailReason);` — Saves the descriptor to the given file.
- L133 _public prototype_ `void Write(TJsonWriter<>& Writer, const FString& PathToProject) const;` — Writes the descriptor to the given JSON object
- L136 _public prototype_ `static FString GetExtension();` — Returns the extension used for project descriptors (uproject)
- L139 _public function_ `const TArray<FString>& GetAdditionalPluginDirectories() const` — @return - Access to the additional plugin directories
- L150 _public prototype_ `bool AddPluginDirectory(const FString& Dir);` — Adds a directory to the additional plugin directories list. @param Dir - the new directory to add (must be a full path) @return whether the plugin directory list was changed
- L157 _public prototype_ `bool RemovePluginDirectory(const FString& Dir);` — Removes the directory from the list to scan @param Dir the directory to remove (must be a full path) @return whether the plugin directory list was changed
- L160 _public function_ `const TArray<FString>& GetAdditionalRootDirectories() const` — @return - Access to the additional root directories
- L171 _public prototype_ `bool AddRootDirectory(const FString& Dir);` — Adds a directory to the additional root directories list. @param Dir - the new directory to add (must be a full path) @return whether the root directory list was changed
- L178 _public prototype_ `bool RemoveRootDirectory(const FString& Dir);` — Removes the directory from the list to scan @param Dir the directory to remove (must be a full path) @return whether the root directory list was changed
- L182 _public prototype_ `bool HasModule(FName ModuleName) const;` — Returns whether the project has a module of the given name
- L187 _private prototype_ `const FString MakePathRelativeToProject(const FString& Dir, const FString& PathToProject) const;` — @return the path relative to this project if possible
- L193 _private member_ `TArray<FString> AdditionalPluginDirectories;` — List of additional directories to scan for plugins. Paths are in memory as absolute paths. Conversion to/from path relative happens during Save/Load
- L199 _private member_ `TArray<FString> AdditionalRootDirectories;` — List of additional root directories to scan for modules. Paths are in memory as absolute paths. Conversion to/from path relative happens during Save/Load
- L203 _private member_ `mutable TSet<FName> ModuleNamesCache;` — Set of project module names
- L207 _private prototype_ `bool Read(const UE::Json::FConstObject Object, const FString& PathToProject, FText& OutFailReason);`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace EProjectDescriptorVersion`

### `Source/Runtime/Projects/Public/ProjectEditorRecords.h` (Public)


#### struct `FProjectEditorRecord`  
`struct FProjectEditorRecord`  
_L17-103_
- desc: Struct specifying the structure of the records file, this is used to maintain an association between recently opened projects and the location of the editor engine used to open them. This is meant to be a machine wide record to facilitate locating the right engine executable. Usage: - QueueUpdate to update the record - Load to read from the record
- L20 _public member_ `static const FString ProjectsProperty;` — Property used to specify a Projects list
- L23 _public member_ `static const FString SubProjectProperty;` — Property used to specify a SubProjects list
- L26 _public member_ `static const FString EngineLocationProperty;` — Property used to specify the path of the engine used to open the project
- L29 _public member_ `static const FString BaseDirProperty;` — Property used to specify the path of the base dir of the engine used for the project
- L32 _public member_ `static const FString TimestampProperty;` — Property used to specify a last accessed timestamp
- L35 _public member_ `static const FString EpicAppProperty;` — Property used to specify an Epic App
- L38 _public member_ `TSharedPtr<FJsonObject> ProjectEditorJson;` — The json contents of the records loaded/saved to disk
- L52 _public prototype_ `static void QueueUpdate(TUniqueFunction<void(FProjectEditorRecord&)>&& InUpdateFunction);` — This is the main way to interact with the json contents to add entries in a safe way. QueueUpdate schedules a task that will try to run in another thread and perform these operations: - Acquires a system wide lock - Loads the latest records from disk - Runs the function passed as a parameter with the loaded contents - Saves the records to disk - Releases system wide lock @param Function used to update the records in a worker thread
- L60 _public prototype_ `static FProjectEditorRecord Load();` — Loads a project editor record from disk, using the default location %LOCALAPPDATA%/UnrealEngine/Editor/ProjectEditorRecords.json location can be overriden by cvar r.Editor.ProjectEditorRecordsFile @return	The struct loaded from disk, or an empty one.
- L68 _public prototype_ `const TSharedPtr<FJsonObject> FindOrAddProperty(const FString& InProperty);` — Finds or adds an object property to the root of the json @param The name of the property to find or add @return Shared pointer to the json object corresponding to the property input
- L78 _public prototype_ `static TSharedPtr<FJsonObject> MakeDefaultProperties();` — Creates a JsonObject containing the default entries - Path to the UnrealEditor.exe used when calling this function (meant to be UnrealEditor.exe) - Path to the base directory when calling this function - Current timestamp @return JsonObject containing the default entries for a project
- L84 _public prototype_ `static void TearDown();` — Waits for any queued async tasks to finish if there are any
- L87 _private prototype_ `FProjectEditorRecord() = default;`
- L90 _private member_ `static FGraphEventRef AsyncUpdateTask;` — Handle for the latest async task
- L93 _private member_ `const int32 DaysToKeepRecords = 60;` — Number of days that have to pass for an entry to be considered stale and be removed on save
- L96 _private prototype_ `void PruneOldEntries(const TSharedPtr<FJsonObject>& JsonObject);` — Goes over the json object and prunes anything older than DaysToKeepRecords
- L99 _private prototype_ `static const FString GetFileLocation();` — Gets the location of the file on disk
- L102 _private prototype_ `bool Save();` — Saves the contents of this structure to disk

### `Source/Runtime/Projects/Public/ProjectUtilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ProjectUtilities` (scope `UE`)
- L12 _prototype_ `void ParseProjectDirFromCommandline(int32 ArgC, TCHAR* ArgV[]);` (scope `UE::ProjectUtilities`) — Allows a monolithic target to control the game directory by the presence of commandline arguments for the project.

### `Source/Runtime/Projects/Public/Projects.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Projects/Public/VerseScope.h` (Public)


#### enum `EVerseScope::Type`  
`enum Type : uint8`  
_L14-20_
- L16 _public enumerator_ `PublicAPI` — Created by Epic and only public definitions will be visible to public users
- L17 _public enumerator_ `InternalAPI` — Created by Epic and is entirely hidden from public users
- L18 _public enumerator_ `PublicUser` — Created by a public user
- L19 _public enumerator_ `InternalUser` — Created by an Epic internal user

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace EVerseScope`
- L25 _prototype_ `TOptional<EVerseScope::Type> FromString(const TCHAR* Text);` (scope `EVerseScope`) — Converts a string to a EVerseScope::Type value
- L30 _prototype_ `const TCHAR* ToString(const EVerseScope::Type Value);` (scope `EVerseScope`) — Returns the name of a Verse scope.
