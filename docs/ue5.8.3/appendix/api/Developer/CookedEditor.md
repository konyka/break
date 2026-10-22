# Developer / CookedEditor

- module root: `Source/Developer/CookedEditor`
- headers: 3; symbols: 98
- symbol kinds: class=6, enum=1, enumerator=2, function=34, member=13, prototype=30, typedef=12
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreOnline, CoreUObject, Engine, NetCore, Projects
- PublicDependencyModuleNames: TargetPlatform
- PublicIncludePathModuleNames: LinuxTargetPlatformControls, LinuxTargetPlatformSettings, MacTargetPlatformControls, MacTargetPlatformSettings, WindowsTargetPlatformControls, WindowsTargetPlatformSettings

### `Source/Developer/CookedEditor/Public/CookedEditorPackageManager.h` (Public)


#### class `ICookedEditorPackageManager`  
`class ICookedEditorPackageManager`  
_L74-156_
- desc: Allows a project to control how packages are cooked when making a cooked editor. Unlike a runtime game, a cooked editor typically needs to include all engine and plugin content, to make all resources available for the crafting of future games in the cooked editor with asset needs that are not yet known. When cooking a cooked editor target platform, an instance of this class adds the requests for all of that extra content. The default implementation is FIniCookedEditorPackageManager which allows for Game.ini settings to control most functionality. By default (as set in BaseGame.ini) all content is cooked with a few class types and plugns that are not due to incompatibility with having been cooked and loaded by the editor. If "Cook Against Release" mode is enabled, then making the cooked editor will act like "DLC" where it uses an already created Game or Client release and will not cook pacakges that are already in the release. To override this class, generally you will want to override the Project functions in the first public section. In GetProjectPackagesToCook(), you can call AddPackagesFromPath to cook spefic project content subdirectories as needed You likely can use just this class without needing to subclass TCookedEditorTargetPlatform at all, but you can do that if needed.
- L81 _public prototype_ `static TUniquePtr<ICookedEditorPackageManager> FactoryForTargetPlatform(bool bIsCookedCooker);` — Construct a package manager for the given TP
- L83 _public prototype_ `virtual ~ICookedEditorPackageManager() = default;`
- L89 _public prototype_ `virtual void InitializeForCook() = 0;` — Hook called when the manager's TargetPlatform is selected for cooking. Load any required assets or data. May be called multiple times per process; it is called each time a cook starts for the platform.
- L94 _public prototype_ `virtual void GetEnginePackagesToCook(TArray<FName>& PackagesToCook) const = 0;` — Override to control engine packages to cook
- L99 _public prototype_ `virtual void GetProjectPackagesToCook(TArray<FName>& PackagesToCook) const = 0;` — Override to add project specific packages to cook
- L105 _public prototype_ `virtual bool AllowObjectToBeCooked(const class UObject* Obj) const = 0;` — Allows the subclass to exclude specific objects in packages discovered during the cook. By default, will disallow UBlueprint objects
- L112 _public prototype_ `virtual bool AllowAssetToBeGathered(const struct FAssetData& AssetData) const = 0;` — Allows the subclass to disallow some assets to be gathered during AddPackagesFromPath, for instance This is similar to AllowObjectToBeCooked, but it can help with, for instance, removing maps from subdirectories, while still allowing the normal maps that come from the standard cooking process
- L117 _public prototype_ `virtual bool AllowEnginePluginContentToBeCooked(const TSharedRef<IPlugin>) const = 0;` — Should the given enabled engine plugin be cooked?
- L122 _public prototype_ `virtual bool AllowProjectPluginContentToBeCooked(const TSharedRef<IPlugin>) const = 0;` — Should the given enabled project plugin be cooked?
- L127 _public prototype_ `virtual void GatherAllPackages(TArray<FName>& PackageNames) const = 0;` — Gathers the packages this PackageManager wants to manage (ie cook)
- L143 _protected prototype_ `void AddPackagesFromPath(TArray<FName>& Packages, const TCHAR* Path, EPackageSearchMode SearchMode) const;` — Use the asset registry to find packages to be cooked @param Packages output array of paths @param Path rooted path to look in ("/Engine", etc) @param SeachMode Recurse or TopDirectoryOnly
- L148 _protected prototype_ `virtual void FilterGatheredPackages(TArray<FName>& PackageNames) const;` — Allow a subclass to remove packages found in GatherAllPackages
- L155 _protected prototype_ `void GatherAllPackagesExceptDisabled(TArray<FName>& PackageNames, const TArray<FString>& DisabledPlugins) const;` — Meat of this class, this calls other functions that generally will be overridden - subclass needs to pass in disabled plugins

#### enum `ICookedEditorPackageManager::EPackageSearchMode`  
`enum class EPackageSearchMode`  
_L131-135_
- L133 _public enumerator_ `TopDirectoryOnly`
- L134 _public enumerator_ `Recurse`

#### class `FIniCookedEditorPackageManager`  
`class FIniCookedEditorPackageManager : public ICookedEditorPackageManager`  
_L164-204_
- inherits: `ICookedEditorPackageManager`
- desc: An implentation of ICookedEditorPackageManager that uses BaseGame.ini / DefaultGame.ini to control cooked editor packaging setup
- L166 _private member_ `TArray<FString> EngineAssetPaths;`
- L167 _private member_ `TArray<FString> ProjectAssetPaths;`
- L168 _private member_ `TArray<FString> DisabledPlugins;`
- L169 _private member_ `TSet<FTopLevelAssetPath> DisallowedObjectClassesToLoad;`
- L170 _private member_ `TArray<UClass*> DisallowedAssetClassesToGather;`
- L171 _private member_ `TArray<FString> DisallowedPathsToGather;`
- L174 _private member_ `bool bIsCookedCooker;` — true if this is a cooked cooker (false for cooker editor)
- L177 _private member_ `bool bClassesInitialized = false;` — Guard to prevent multiple InitializeClasses calls
- L180 _private member_ `int32 CookProgressDisplayMode = 0;` — Used to control logging of certain warnings.
- L183 _private prototype_ `TArray<FString> GetConfigArray(const TCHAR* Key) const;` — gets an array from two sections, depending on bIsCookedCooker setting
- L186 _private prototype_ `void InitializeClasses();` — Load the classes specified from config settings that we need to reference
- L189 _public prototype_ `FIniCookedEditorPackageManager(bool bIsCookedCooker);`
- L192 _public prototype_ `static TArray<FString> GetConfigArray(const TCHAR* Key, bool bIsCookedCooker);` — gets an array from two sections, depending on bIsCookedCooker setting
- L194 _public prototype_ `virtual void FilterGatheredPackages(TArray<FName>& PackageNames) const override;`
- L195 _public prototype_ `virtual void InitializeForCook() override;`
- L196 _public prototype_ `virtual void GetEnginePackagesToCook(TArray<FName>& PackagesToCook) const override;`
- L197 _public prototype_ `virtual void GetProjectPackagesToCook(TArray<FName>& PackagesToCook) const override;`
- L198 _public prototype_ `virtual bool AllowObjectToBeCooked(const class UObject* Obj) const override;`
- L199 _public prototype_ `virtual bool AllowAssetToBeGathered(const struct FAssetData& AssetData) const override;`
- L200 _public prototype_ `virtual bool AllowEnginePluginContentToBeCooked(const TSharedRef<IPlugin>) const override;`
- L201 _public prototype_ `virtual bool AllowProjectPluginContentToBeCooked(const TSharedRef<IPlugin>) const override;`
- L203 _public prototype_ `virtual void GatherAllPackages(TArray<FName>& PackageNames) const override;`

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TGenericWindowsTargetPlatformSettings<FWindowsPlatformProperties<false, false, false>> FWindowsEditorTargetPlatformSettingsParent;`
- L28 _typedef_ `typedef TGenericWindowsTargetPlatformControls<FWindowsPlatformProperties<false, false, false>> FWindowsEditorTargetPlatformControlsParent;`
- L32 _typedef_ `typedef TLinuxTargetPlatformSettings<FLinuxPlatformProperties<false, false, false, false>> FLinuxEditorTargetPlatformSettingsParent;`
- L33 _typedef_ `typedef TLinuxTargetPlatformControls<FLinuxPlatformProperties<false, false, false, false>> FLinuxEditorTargetPlatformControlsParent;`
- L37 _typedef_ `typedef TGenericMacTargetPlatformSettings<false, false, false> FMacEditorTargetPlatformSettingsParent;`
- L38 _typedef_ `typedef TGenericMacTargetPlatformControls<false, false, false> FMacEditorTargetPlatformControlsParent;`
- L42 _typedef_ `typedef FWindowsEditorTargetPlatformSettingsParent FHostPlatformEditorTargetPlatformSettingsParent;`
- L43 _typedef_ `typedef FWindowsEditorTargetPlatformControlsParent FHostPlatformEditorTargetPlatformControlsParent;`
- L45 _typedef_ `typedef FLinuxEditorTargetPlatformSettingsParent FHostPlatformEditorTargetPlatformSettingsParent;`
- L46 _typedef_ `typedef FLinuxEditorTargetPlatformControlsParent FHostPlatformEditorTargetPlatformControlsParent;`
- L48 _typedef_ `typedef FMacEditorTargetPlatformSettingsParent FHostPlatformEditorTargetPlatformSettingsParent;`
- L49 _typedef_ `typedef FMacEditorTargetPlatformControlsParent FHostPlatformEditorTargetPlatformControlsParent;`

### `Source/Developer/CookedEditor/Public/CookedEditorTargetPlatformControls.h` (Public)


#### class `TCookedEditorTargetPlatformControls`  
`template<typename Base> class TCookedEditorTargetPlatformControls : public Base`  
_L18-102_
- inherits: `Base`
- desc: Templated class for a target platform used to cook a cooked editor. It needs to inherit from a desktop platform's target platform such as TGenericWindowsTargetPlatformControls. See CookedEditorPackageManager.h for some typedef'd standard base classes that can be used. The majority of the functionality is performed in an instance of a ICookedEditorPackageManager subclass. See that class for more information.
- L22 _public function_ `TCookedEditorTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) :Base(TargetPlatformSettings)`
- L30 _public function_ `explicit TCookedEditorTargetPlatformControls(TUniquePtr<ICookedEditorPackageManager>&& ExistingManager, ITargetPlatformSettings* TargetPlatformSettings) :Base(TargetPlatformSettings)` — Allows for a custom target platform module to initialize this TargetPlatform with an existing PackageManager instead of going through the standard factory function
- L36 _public prototype_ `~TCookedEditorTargetPlatformControls() = default;`
- L38 _public function_ `virtual FString PlatformName() const override`
- L44 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L52 _public function_ `virtual bool AllowsEditorObjects() const override` — If you override this to return false, you will have to stage uncooked assets to allow the editor to run properly
- L57 _public function_ `virtual bool AllowObject(const class UObject* Obj) const override`
- L68 _public function_ `virtual void InitializeForCook() override`
- L73 _public function_ `virtual void GetExtraPackagesToCook(TArray<FName>& PackageNames) const override`
- L81 _public function_ `virtual float GetVariantPriority() const override`
- L88 _public function_ `virtual void GetAllDevices(TArray<ITargetDevicePtr>& OutDevices) const override`
- L92 _public function_ `virtual ITargetDevicePtr GetDefaultDevice() const override`
- L100 _protected member_ `TUniquePtr<ICookedEditorPackageManager> PackageManager;`

#### class `TCookedCookerTargetPlatformControls`  
`template<typename Base> class TCookedCookerTargetPlatformControls : public Base`  
_L106-211_
- inherits: `Base`
- L110 _public function_ `TCookedCookerTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : Base(TargetPlatformSettings)`
- L116 _public function_ `TCookedCookerTargetPlatformControls(TUniquePtr<ICookedEditorPackageManager>&& ExistingManager, ITargetPlatformSettings* TargetPlatformSettings) : Base(TargetPlatformSettings)`
- L122 _public prototype_ `~TCookedCookerTargetPlatformControls() = default;`
- L125 _public function_ `virtual FString PlatformName() const override`
- L131 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L136 _public function_ `virtual bool AllowsEditorObjects() const override`
- L141 _public function_ `virtual bool AllowsDevelopmentObjects() const override`
- L146 _public function_ `virtual bool AllowObject(const UObject* Obj) const override`
- L157 _public function_ `virtual void InitializeForCook() override`
- L162 _public function_ `virtual void GetExtraPackagesToCook(TArray<FName>& PackageNames) const override`
- L176 _public function_ `virtual void GetTextureFormats(const class UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override`
- L181 _public function_ `virtual bool SupportsVariants() const override`
- L186 _public function_ `virtual bool AllowAudioVisualData() const override`
- L191 _public function_ `virtual float GetVariantPriority() const override`
- L198 _public function_ `virtual void GetAllDevices(TArray<ITargetDevicePtr>& OutDevices) const override`
- L202 _public function_ `virtual ITargetDevicePtr GetDefaultDevice() const override`
- L209 _public member_ `TUniquePtr<ICookedEditorPackageManager> PackageManager;`

### `Source/Developer/CookedEditor/Public/CookedEditorTargetPlatformSettings.h` (Public)


#### class `TCookedEditorTargetPlatformSettings`  
`template<typename Base> class TCookedEditorTargetPlatformSettings : public Base`  
_L18-51_
- inherits: `Base`
- desc: Templated class for a target platform used to cook a cooked editor. It needs to inherit from a desktop platform's target platform such as TGenericWindowsTargetPlatformSettings. See CookedEditorPackageManager.h for some typedef'd standard base classes that can be used. The majority of the functionality is performed in an instance of a ICookedEditorPackageManager subclass. See that class for more information.
- L22 _public function_ `TCookedEditorTargetPlatformSettings()`
- L29 _public function_ `explicit TCookedEditorTargetPlatformSettings(TUniquePtr<ICookedEditorPackageManager>&& ExistingManager)` — Allows for a custom target platform module to initialize this TargetPlatform with an existing PackageManager instead of going through the standard factory function
- L34 _public prototype_ `~TCookedEditorTargetPlatformSettings() = default;`
- L36 _public function_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const override`
- L49 _protected member_ `TUniquePtr<ICookedEditorPackageManager> PackageManager;`

#### class `TCookedCookerTargetPlatformSettings`  
`template<typename Base> class TCookedCookerTargetPlatformSettings : public Base`  
_L55-104_
- inherits: `Base`
- L59 _public function_ `TCookedCookerTargetPlatformSettings()`
- L64 _public function_ `TCookedCookerTargetPlatformSettings(TUniquePtr<ICookedEditorPackageManager>&& ExistingManager)`
- L69 _public prototype_ `~TCookedCookerTargetPlatformSettings() = default;`
- L75 _public function_ `virtual void GetAllPossibleShaderFormats(TArray<FName>& OutFormats) const override`
- L80 _public function_ `virtual void GetAllTargetedShaderFormats(TArray<FName>& OutFormats) const override`
- L85 _public function_ `virtual bool SupportsFeature(ETargetPlatformFeatures Feature) const override`
- L102 _public member_ `TUniquePtr<ICookedEditorPackageManager> PackageManager;`
