# Developer / DeveloperToolSettings

- module root: `Source/Developer/DeveloperToolSettings`
- headers: 4; symbols: 219
- symbol kinds: class=3, enum=10, enumerator=41, function=8, macro=3, member=124, prototype=26, struct=4
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, DeveloperSettings, Projects

### `Source/Developer/DeveloperToolSettings/Classes/CookerSettings.h` (Public)


#### enum `ECookProgressDisplayMode`  
`enum class ECookProgressDisplayMode : int32`  
_L19-47_
- reflection: `UENUM()`
- L22 _public enumerator_ `Nothing = 0` — Don't display any progress messages
- L25 _public enumerator_ `RemainingPackages = 1` — Display the number of remaining packages
- L28 _public enumerator_ `PackageNames = 2` — Display names of cooked packages
- L31 _public enumerator_ `NamesAndRemainingPackages = 3` — Display the number of remaining packages and package names
- L34 _public enumerator_ `Instigators = 4` — Display names and instigators of cooked packages
- L37 _public enumerator_ `InstigatorsAndCount = 5` — Display instigators and count of remaining packages
- L40 _public enumerator_ `InstigatorsAndNames = 6` — Display instigators and names of cooked packages
- L43 _public enumerator_ `InstigatorsAndNamesAndCount = 7` — Display instigators and names and count of cooked packages
- L46 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### enum `EBlueprintComponentDataCookingMethod`  
`enum class EBlueprintComponentDataCookingMethod`  
_L50-60_
- reflection: `UENUM()`
- L53 _public enumerator_ `Disabled` — Do not generate optimized component data. No additional memory will be used.
- L56 _public enumerator_ `AllBlueprints` — Generate optimized component data for all Blueprint types. This option will require the most additional memory.
- L59 _public enumerator_ `EnabledBlueprintsOnly` — Generate optimized component data only for Blueprint types that have explicitly enabled this feature in the class settings.

#### enum `EBlueprintPropertyGuidsCookingMethod`  
`enum class EBlueprintPropertyGuidsCookingMethod`  
_L63-73_
- reflection: `UENUM()`
- L66 _public enumerator_ `Disabled` — Do not include the property GUIDs in a cooked build. No additional memory will be used.
- L69 _public enumerator_ `AllBlueprints` — Include the property GUIDs in a cooked build for all Blueprint types. This option will require the most additional memory.
- L72 _public enumerator_ `EnabledBlueprintsOnly` — Include the property GUIDs in a cooked build only for Blueprint types that have explicitly enabled this feature in their class settings.

#### enum `ETextureFormatASTCCompressor`  
`enum class ETextureFormatASTCCompressor`  
_L76-85_
- reflection: `UENUM()`
- L79 _public enumerator_ `IntelISPC` — ThirdParty/Intel/ISPCTexComp
- L82 _public enumerator_ `Arm` — /ThirdParty/ARM
- L84 _public enumerator_ `Max UMETA(Hidden)`

#### class `UCookerSettings`  
`class UCookerSettings : public UDeveloperSettings`  
_L90-207_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig, meta=(DisplayName="Cooker"))`
- inherits: `UDeveloperSettings`
- desc: Various cooker settings.
- L94 _private prototype_ `virtual void PostInitProperties() override;`
- L96 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L104 _private function_ `virtual void OverrideConfigSection(FString& InOutSectionName) override` — This class was moved from UnrealEd module, but to allow it to be used by developer tools, like UFE, it has moved to this module. However, for back-compat, we want to use the old name in the ini files, so that everything works without needing to touch every Game.ini file
- L112 _public member_ `bool bEnableCookOnTheSide;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, meta = (DisplayName = "Enable cooking via network in the background of the editor, launch on uses this setting, requires device to have network access to editor", ConfigRestartRequired = true))`
- L115 _public member_ `bool bEnableBuildDDCInBackground;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, meta = (DisplayName = "Generate DDC data in background for desired launch on platform (speeds up launch on)"))`
- L119 _public member_ `bool bIterativeCookingForLaunchOn;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, meta = (DisplayName = "Use Incremental Cook for builds launched from the editor (launch on)"))` — Enable IncrementalCooks for launch on
- L123 _public member_ `bool bIterativeCookingForFileCookContent;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, meta = (DisplayName = "Use Incremental Cook for the Platforms->Cook Content menu item"))` — Enable IncrementalCooks when triggering from Platforms dropdown menu
- L127 _public member_ `bool bCookOnTheFlyForLaunchOn;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, meta = (DisplayName = "Cooking on the fly when launching from the editor (launch on)"))` — Enable -cookonthefly for launch on
- L132 _public member_ `ECookProgressDisplayMode CookProgressDisplayMode;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, meta = ( ConsoleVariable = "cook.displaymode", DisplayName = "Cooker Progress Display Mode", ToolTip = "Controls log output of the cooker"))`
- L136 _public member_ `bool bIgnoreIniSettingsOutOfDateForIteration;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay)` — Ignore ini changes when doing iterative cooking, either in editor or out of editor
- L140 _public member_ `bool bIgnoreScriptPackagesOutOfDateForIteration;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay)` — Ignore native header file changes when doing iterative cooking, either in editor or out of editor
- L144 _public member_ `bool bCompileBlueprintsInDevelopmentMode;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay)` — Whether or not to compile Blueprints in development mode when cooking.
- L148 _public member_ `EBlueprintComponentDataCookingMethod BlueprintComponentDataCookingMethod;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "Generate optimized Blueprint component data"))` — Generate optimized component data to speed up Blueprint construction at runtime. This option can increase the overall Blueprint memory usage in a cooked build. Requires Event-Driven Loading (EDL), which is enabled by default.
- L155 _public member_ `EBlueprintPropertyGuidsCookingMethod BlueprintPropertyGuidsCookingMethod = EBlueprintPropertyGuidsCookingMethod::EnabledBlueprintsOnly;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "Cook Blueprint property GUIDs?"))` — Should we include the property GUIDs for a Blueprint class in a cooked build, so that SaveGame archives can redirect property names via the GUIDs? @note This option can increase the overall Blueprint memory usage in a cooked build, but can avoid needing to add CoreRedirect data for Blueprint classes stored within SaveGame archives.
- L159 _public member_ `TArray<FString> ClassesExcludedOnDedicatedServer;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "Classes excluded when cooking for dedicated server"))` — List of class names to exclude when cooking for dedicated server
- L163 _public member_ `TArray<FString> ModulesExcludedOnDedicatedServer;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "Modules excluded when cooking for dedicated server"))` — List of module names to exclude when cooking for dedicated server
- L167 _public member_ `TArray<FString> ClassesExcludedOnDedicatedClient;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "Classes excluded when cooking for dedicated client"))` — List of class names to exclude when cooking for dedicated client
- L171 _public member_ `TArray<FString> ModulesExcludedOnDedicatedClient;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "Modules excluded when cooking for dedicated client"))` — List of module names to exclude when cooking for dedicated client
- L175 _public member_ `TArray<FString> VersionedIntRValues;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Cooker, AdvancedDisplay, meta = (DisplayName = "r values that need to be versioned"))` — List of r values that need to be versioned
- L179 _public member_ `int32 DefaultASTCQualityBySpeed;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Textures, meta = (DisplayName = "ASTC Compression Speed (0-3, 0 is fastest)"))` — Quality of 0 means fastest, 3 means best quality
- L183 _public member_ `int32 DefaultASTCQualityBySize;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Textures, meta = (DisplayName = "ASTC Compression Block Size (0-4, 0 is smallest)"))` — Quality of 0 means smallest (12x12 block size), 4 means best (4x4 block size)
- L187 _public member_ `int32 DefaultASTCQualityBySizeHQ;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Textures, meta = (DisplayName = "ASTC Compression Block Size for High Quality (BC7) (0-4, 0 is smallest)"))` — Quality of 0 means smallest (12x12 block size), 4 means best (4x4 block size)
- L194 _public member_ `uint32 bAllowASTCHDRProfile : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Textures, meta = ( ConsoleVariable = "cook.AllowASTCHDRProfile", DisplayName = "ASTC HDR Profile", ToolTip = "Whether to allow ASTC HDR profile, the HDR format is only supported on some devices, e.g. Apple A13, Mali-G72, Adreno (TM) 660", ConfigRestartRequired = true))` — Whether to allow ASTC HDR profile
- L201 _public member_ `uint32 bAllowCookedDataInEditorBuilds : 1;` — `UPROPERTY(EditAnywhere, config, Category = Editor, meta = ( ConsoleVariable = "cook.AllowCookedDataInEditorBuilds", DisplayName = "Allow Cooked Content In The Editor", ToolTip = "If true, the editor will be able to open cooked assets (limited to a subset of supported asset types).", ConfigRestartRequired = true))` — Allows opening cooked assets in the editor
- L206 _private member_ `bool bCookBlueprintComponentTemplateData;` — `UPROPERTY(GlobalConfig)` — Deprecated. Use BlueprintComponentDataCookingMethod instead.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DEVELOPERTOOLSETTINGS_API`

### `Source/Developer/DeveloperToolSettings/Classes/Settings/PlatformsMenuSettings.h` (Public)


#### enum `ECustomBuildType`  
`enum class ECustomBuildType : uint8`  
_L16-20_
- desc: ProjectPackagingSettings has two arrays of custom builds: EngineCustomBuilds and ProjectCustomBuilds. That makes it possible to have two builds with the same name (one in each list). For this reason, we need to store the settings separately for both.
- L18 _public enumerator_ `EngineCustomBuilds`
- L19 _public enumerator_ `ProjectCustomBuilds`

#### class `UPlatformsMenuSettings`  
`class UPlatformsMenuSettings : public UObject`  
_L23-139_
- reflection: `UCLASS(MinimalAPI, config=Game)`
- inherits: `UObject`
- L30 _private member_ `FDirectoryPath StagingDirectory;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — The directory to which the packaged project will be copied.
- L34 _private member_ `FString LaunchOnTarget;` — `UPROPERTY(config)` — Name of the target to use for LaunchOn (only Game/Client targets)
- L38 _private member_ `FName CookPlatform;` — `UPROPERTY(config)` — Name of the platform (IniPlatformName) to use when the "Cook Content" button is clicked in the menu
- L42 _private member_ `FString CookBuildTarget;` — `UPROPERTY(config)` — Build target to use when the "Cook Content" button is clicked in the menu
- L46 _private member_ `FName PackagePlatform;` — `UPROPERTY(config)` — Name of the platform (IniPlatformName) to use when the "Package Project" button is clicked in the menu
- L50 _private member_ `FString PackageBuildTarget;` — `UPROPERTY(config)` — Build target to use when the "Package Project" button is clicked in the menu
- L54 _private member_ `FName PrepareForDebuggingPlatform;` — `UPROPERTY(config)` — Name of the platform (IniPlatformName) to use when the "Prepare for Debugging" button is clicked in the menu
- L58 _private member_ `FString PrepareForDebuggingBuildTarget;` — `UPROPERTY(config)` — Build target to use when the "Prepare for Debugging" button is clicked in the menu
- L61 _private prototype_ `const FTargetInfo* GetLaunchOnTargetInfo() const;` — Gets the current launch on target, checking that it's valid, and the default build target if it is not
- L63 _private prototype_ `FName GetTargetFlavorForPlatform(FName IniPlatformName) const;`
- L64 _private prototype_ `void SetTargetFlavorForPlatform(FName IniPlatformName, FName TargetFlavorName);`
- L66 _private prototype_ `FString GetArchitectureForPlatform(FName IniPlatformName) const;`
- L67 _private prototype_ `void SetArchitectureForPlatform(FName IniPlatformName, FString ArchitectureName);`
- L69 _private prototype_ `const FTargetInfo* GetBuildTargetInfo(const FString& TargetName, bool& bOutIsProjectTarget) const;`
- L71 _private prototype_ `EProjectPackagingBuildConfigurations GetLaunchOnBuildConfiguration() const;`
- L72 _private prototype_ `void SetLaunchOnBuildConfiguration(EProjectPackagingBuildConfigurations BuildConfiguration);`
- L74 _private prototype_ `EProjectPackagingBuildConfigurations GetPackageBuildConfiguration() const;`
- L75 _private prototype_ `void SetPackageBuildConfiguration(EProjectPackagingBuildConfigurations BuildConfiguration);`
- L78 _private prototype_ `FName GetPlatformForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName) const;` — Returns the IniPlatformName selected for the custom build
- L79 _private prototype_ `void SetPlatformForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName, FName IniPlatformName);`
- L81 _private prototype_ `FString GetDeviceIdForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName) const;`
- L82 _private prototype_ `void SetDeviceIdForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName, const FString& DeviceId);`
- L84 _private prototype_ `EProjectPackagingBuildConfigurations GetBuildConfigurationForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName) const;`
- L85 _private prototype_ `void SetBuildConfigurationForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName, EProjectPackagingBuildConfigurations BuildConfiguration);`
- L87 _private prototype_ `FString GetBuildTargetForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName) const;`
- L88 _private prototype_ `void SetBuildTargetForCustomBuild(ECustomBuildType Type, const FString& CustomBuildName, const FString& TargetName);`
- L94 _private member_ `TMap<FName, FName> PerPlatformTargetFlavorName;` — `UPROPERTY(config)` — Per platform flavor cooking target
- L98 _private member_ `TMap<FName, FString> PerPlatformArchitecture;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — Per platform architecture
- L102 _private member_ `TMap<FString, FName> PerEngineCustomBuildPlatformName;` — `UPROPERTY(config)` — Platform name setting stored per entry in EngineCustomBuilds
- L106 _private member_ `TMap<FString, FName> PerProjectCustomBuildPlatformName;` — `UPROPERTY(config)` — Platform name setting stored per entry in ProjectCustomBuilds
- L110 _private member_ `TMap<FString, FString> PerEngineCustomBuildDeviceId;` — `UPROPERTY(config)` — Device ID setting stored per entry in EngineCustomBuilds
- L114 _private member_ `TMap<FString, FString> PerProjectCustomBuildDeviceId;` — `UPROPERTY(config)` — Device ID setting stored per entry in ProjectCustomBuilds
- L118 _private member_ `TMap<FString, EProjectPackagingBuildConfigurations> PerEngineCustomBuildBuildConfiguration;` — `UPROPERTY(config)` — Build configuration setting stored per entry in EngineCustomBuilds
- L122 _private member_ `TMap<FString, EProjectPackagingBuildConfigurations> PerProjectCustomBuildBuildConfiguration;` — `UPROPERTY(config)` — Build configuration setting stored per entry in ProjectCustomBuilds
- L126 _private member_ `TMap<FString, FString> PerEngineCustomBuildBuildTargetName;` — `UPROPERTY(config)` — Build target name setting stored per entry in EngineCustomBuilds
- L130 _private member_ `TMap<FString, FString> PerProjectCustomBuildBuildTargetName;` — `UPROPERTY(config)` — Build target name setting stored per entry in ProjectCustomBuilds
- L134 _private member_ `TOptional<EProjectPackagingBuildConfigurations> LaunchOnBuildConfiguration;` — `UPROPERTY(config)` — Build configuration to use for LaunchOn
- L138 _private member_ `TOptional<EProjectPackagingBuildConfigurations> PackageBuildConfiguration;` — `UPROPERTY(config)` — Build configuration to use when the "Package Project" button is clicked in the menu

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DEVELOPERTOOLSETTINGS_API`

### `Source/Developer/DeveloperToolSettings/Classes/Settings/ProjectPackagingSettings.h` (Public)


#### enum `EProjectPackagingBuildConfigurations`  
`enum class EProjectPackagingBuildConfigurations : uint8`  
_L18-37_
- reflection: `UENUM()`
- desc: Enumerates the available build configurations for project packaging.
- L21 _public enumerator_ `PPBC_Debug UMETA(DisplayName="Debug")` — Debug configuration.
- L24 _public enumerator_ `PPBC_DebugGame UMETA(DisplayName="DebugGame")` — DebugGame configuration.
- L27 _public enumerator_ `PPBC_Development UMETA(DisplayName="Development")` — Development configuration.
- L30 _public enumerator_ `PPBC_Test UMETA(DisplayName="Test")` — Test configuration.
- L33 _public enumerator_ `PPBC_Shipping UMETA(DisplayName="Shipping")` — Shipping configuration.
- L36 _public enumerator_ `PPBC_MAX UMETA(Hidden)` — Number of entries in the enum.

#### enum `EProjectPackagingInternationalizationPresets`  
`enum class EProjectPackagingInternationalizationPresets : uint8`  
_L43-59_
- reflection: `UENUM()`
- desc: Enumerates the available internationalization data presets for project packaging.
- L46 _public enumerator_ `English` — English only.
- L49 _public enumerator_ `EFIGS` — English, French, Italian, German, Spanish.
- L52 _public enumerator_ `EFIGSCJK` — English, French, Italian, German, Spanish, Chinese, Japanese, Korean.
- L55 _public enumerator_ `CJK` — Chinese, Japanese, Korean.
- L58 _public enumerator_ `All` — All known cultures.

#### enum `EProjectPackagingBuild`  
`enum class EProjectPackagingBuild`  
_L65-78_
- reflection: `UENUM()`
- desc: Determines whether to build the executable when packaging. Note the equivalence between these settings and EPlayOnBuildMode.
- L68 _public enumerator_ `Always UMETA(DisplayName="Always")` — Always build.
- L71 _public enumerator_ `Never UMETA(DisplayName="Never")` — Never build.
- L74 _public enumerator_ `IfProjectHasCode UMETA(DisplayName="If project has code, or running a locally built editor")` — Default (if the never build.)
- L77 _public enumerator_ `IfEditorWasBuiltLocally UMETA(DisplayName="If running a locally built editor")` — If we're not packaging from a promoted or installed build.

#### enum `EProjectPackagingBlueprintNativizationMethod`  
`enum class EProjectPackagingBlueprintNativizationMethod : uint8`  
_L84-94_
- reflection: `UENUM()`
- desc: Enumerates the available methods for Blueprint nativization during project packaging.
- L87 _public enumerator_ `Disabled` — Disable Blueprint nativization (default).
- L90 _public enumerator_ `Inclusive` — Enable nativization for all Blueprint assets.
- L93 _public enumerator_ `Exclusive` — Enable nativization for selected Blueprint assets only.

#### enum `EAssetRegistryWritebackMethod`  
`enum class EAssetRegistryWritebackMethod : uint8`  
_L106-116_
- reflection: `UENUM()`
- desc: The list of possible registry writebacks. During staging, iostore can optionally write back data that is only available during the staging process so that asset registry tools can associate this data with their respective assets. Note that this is used in UnrealPak and thus can't use StaticEnum<>, so if you add any types here, be sure to add the parsing of the strings to IoStoreUtilities.cpp.
- L109 _public enumerator_ `Disabled` — Do not write-back staging metadata to the asset registry
- L112 _public enumerator_ `OriginalFile` — The development asset registry from the source cooked directory will be re-used.
- L115 _public enumerator_ `AdjacentFile` — A duplicate asset registry will be created with the metadata added to it, adjacent to the cooked development asset registry.

#### struct `FPakOrderFileSpec`  
`struct FPakOrderFileSpec`  
_L119-139_
- reflection: `USTRUCT()`
- L124 _public member_ `FString Pattern;` — `UPROPERTY()`
- L127 _public member_ `int32 Priority;` — `UPROPERTY()`
- L129 _public function_ `FPakOrderFileSpec() : Priority(0)`
- L134 _public function_ `FPakOrderFileSpec(FString InPattern) : Pattern(MoveTemp(InPattern)) , Priority(0)`

#### struct `FProjectBuildSettings`  
`struct FProjectBuildSettings`  
_L142-173_
- reflection: `USTRUCT()`
- L148 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category="Packaging")` — The name for this custom build. It will be shown in menus for selection.
- L152 _public member_ `FString HelpText;` — `UPROPERTY(EditAnywhere, Category="Packaging")` — Any help that you would like to include in the ToolTip of the menu option (or shown in interactive mode Turnkey)
- L156 _public member_ `TArray<FString> SpecificPlatforms;` — `UPROPERTY(EditAnywhere, Category="Packaging")` — If this build step is specific to one or more platforms, add them here by name (note: use Windows, not Win64)
- L172 _public member_ `FString BuildCookRunParams;` — `UPROPERTY(EditAnywhere, Category="Packaging")` — The commandline for BuildCookRun UAT command. Some substitutions are allowed: {Project} - Replaced with the path to the project's .uproject file {Platform} - Replaced with the platform name this is run for {inivalue:Config:Section:Key} - Replaced with the value for Key in Config's Section. Ex: -archivedirectory={inivalue:Engine:CustomSettings:OverrideArchiveDir} {iniif:Token:Config:Section:Key} - Replaced with Token if the vlaue for Key in Config's Section evaluates to True. Ex: {iniif:-iostore:/Script/UnrealEd.ProjectPackagingSettings:bUseIoStore} Because ProjectPackagingSettings is a common section to read, if Config:Section: are not specified for 'iniif' or 'inivalue', it will use the ProjectPackagingSettings settings: {iniif:-iostore:bUseIoStore} Additionally, the ini settings can have an optional search and replace modifier, to easily modify the string. The Replace can be blank: {inivalue:BuildConfiguration|PPBC_=} - This will get the BuildConfiguration from the settings, and then remove the PPBC_ enum prefix from the string, to just get say Development Adding -device={DeviceId} will show the command per-device in the platforms menu

#### class `UProjectPackagingSettings`  
`class UProjectPackagingSettings : public UObject`  
_L179-685_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig)`
- inherits: `UObject`
- desc: Implements the Editor's user settings.
- L190 _private function_ `virtual void OverrideConfigSection(FString& InOutSectionName) override` — This class was moved from UnrealEd module, but to allow it to be used by developer tools, like UFE, it has moved to this module. However, for back-compat, we want to use the old name in the ini files, so that everything works without needing to touch every Game.ini file
- L210 _public member_ `static const FConfigurationInfo ConfigurationInfo[(int)EProjectPackagingBuildConfigurations::PPBC_MAX];` — Static array of information about each configuration
- L214 _public member_ `EProjectPackagingBuild Build;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — Specifies whether to build the game executable during packaging.
- L218 _public member_ `EProjectPackagingBuildConfigurations BuildConfiguration;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — The build configuration for which the project is packaged.
- L222 _public member_ `FString BuildTarget;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — Name of the target to build
- L230 _public member_ `bool FullRebuild;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — If enabled, a full rebuild will be enforced each time the project is being packaged. If disabled, only modified files will be built, which can improve iteration time. Unless you iterate on packaging, we recommend full rebuilds when packaging.
- L238 _public member_ `bool ForDistribution;` — `UPROPERTY(config, EditAnywhere, Category=Project)` — If enabled, a distribution build will be created and the shipping configuration will be used If disabled, a development build will be created Distribution builds are for publishing to the App Store
- L242 _public member_ `bool IncludeDebugFiles;` — `UPROPERTY(config, EditAnywhere, Category=Project, meta = (DisplayName = "Include Debug Files in Shipping Builds"))` — If enabled, debug files will be included in staged shipping builds.
- L246 _public member_ `bool UsePakFile;` — `UPROPERTY(config, EditAnywhere, Category=Packaging)` — If enabled, all content will be put into a one or more .pak files instead of many individual files (default = enabled).
- L250 _public member_ `bool bUseIoStore;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — If enabled, use .utoc/.ucas container files for staged/packaged package data instead of pak.
- L254 _public member_ `bool bUseZenStore;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, meta=(DisplayName="Use Zen Server as cooked output store"))` — If enabled, use Zen Server for storing and fetching cooked data instead of using the local file system.
- L258 _public member_ `bool bMakeBinaryConfig;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — If enabled, staging will make a binary config file for faster loading.
- L265 _public member_ `bool bGenerateChunks;` — `UPROPERTY(config, EditAnywhere, Category=Packaging)` — If enabled, will generate pak file chunks.  Assets can be assigned to chunks in the editor or via a delegate (See ShooterGameDelegates.cpp). Can be used for streaming installs (PS4 Playgo, XboxOne Streaming Install, etc)
- L271 _public member_ `bool bGenerateNoChunks;` — `UPROPERTY(config, EditAnywhere, Category=Packaging)` — If enabled, no platform will generate chunks, regardless of settings in platform-specific ini files.
- L278 _public member_ `bool bChunkHardReferencesOnly;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — Normally during chunk generation all dependencies of a package in a chunk will be pulled into that package's chunk. If this is enabled then only hard dependencies are pulled in. Soft dependencies stay in their original chunk.
- L285 _public member_ `bool bForceOneChunkPerFile;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay)` — If true, individual files are only allowed to be in a single chunk and it will assign it to the lowest number requested If false, it may end up in multiple chunks if requested by the cooker
- L292 _public member_ `int64 MaxChunkSize;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay)` — If > 0 this sets a maximum size per chunk. Chunks larger than this size will be split into multiple pak files such as pakchunk0_s1 This can be set in platform specific game.ini files
- L298 _public member_ `bool bBuildHttpChunkInstallData;` — `UPROPERTY(config, EditAnywhere, Category=Packaging)` — If enabled, will generate data for HTTP Chunk Installer. This data can be hosted on webserver to be installed at runtime. Requires "Generate Chunks" enabled.
- L304 _public member_ `FDirectoryPath HttpChunkInstallDataDirectory;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — When "Build HTTP Chunk Install Data" is enabled this is the directory where the data will be build to.
- L311 _public member_ `EAssetRegistryWritebackMethod WriteBackMetadataToAssetRegistry;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay)` — Whether to write staging metadata back to the asset registry. This metadata contains information such as the actual compressed chunk sizes of the assets as well as some bulk data diff blame support information.
- L317 _public member_ `bool bWritePluginSizeSummaryJsons;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (EditCondition = "WriteBackMetadataToAssetRegistry != EAssetRegistryWritebackMethod::Disabled"))` — Whether or not to write a json summary file that contains size information to the cooked Metadata directory
- L323 _public member_ `bool bCompressed;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Create compressed cooked packages"))` — Create compressed cooked packages (decreased deployment size)
- L331 _public member_ `FString PackageCompressionFormat;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Package Compression Format"))` — A comma separated list of formats to use for .pak file and IoStore compression. If more than one is specified, the list is in order of priority, with fallbacks to other formats in case of errors or unavailability of the format (plugin not enabled, etc). Commonly PackageCompressionFormat=Oodle or PackageCompressionFormat=None
- L337 _public member_ `bool bForceUseProjectCompressionFormatIgnoreHardwareOverride;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Use this Compression Format not hardware override"))` — Force use of PackageCompressionFormat (do not use override HardwareCompressionFormat from DDPI)
- L344 _public member_ `FString PackageAdditionalCompressionOptions;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Package Compression Commandline Options"))` — A generic setting for allowing a project to control compression settings during .pak file and iostore compression. For instance PackageAdditionalCompressionOptions=-compressionblocksize=1MB -asynccompression
- L350 _public member_ `FString PackageCompressionMethod;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Package Compression Method"))` — For compressors with multiple methods, select one.  eg. for Oodle you may use one of {Kraken,Mermaid,Selkie,Leviathan}
- L357 _public member_ `int32 PackageCompressionLevel_DebugDevelopment;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Compressor Effort Level for Debug & Development"))` — For compressors with variable levels, select the compressor effort level, which makes packages smaller but takes more time to encode. This does not affect decode speed.  For faster iteration, use lower effort levels (eg. 1)
- L360 _public member_ `int32 PackageCompressionLevel_TestShipping;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Compressor Effort Level for Test & Shipping"))`
- L363 _public member_ `int32 PackageCompressionLevel_Distribution;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Compressor Effort Level for Distribution"))`
- L372 _public member_ `int32 PackageCompressionMinBytesSaved;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Minimum amount of bytes which should be saved when compressing a block of data, otherwise data remains uncompressed"))` — A generic setting which is used to determine whether it is worth using compression for a block of data when creating IoStore or .pak files. If the amount of saved bytes is smaller than the specified value, then the block of data remains uncompressed. The optimal value of this setting depends on the capabilities of the target platform. For instance PackageCompressionMinBytesSaved=1024 Note that some compressors (for example Oodle) do their own internal worth it check and only use this value to determine the minimal size of a block which should be compressed.
- L381 _public member_ `int32 PackageCompressionMinPercentSaved;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Minimum percentage of a block of data which should be saved when performing compression, otherwise data remains uncompressed"))` — A generic setting which is used to determine whether it is worth using compression for a block of data when creating IoStore or .pak files. If the saved percentage of a compressed block of data is smaller than the specified value, then the block remains uncompressed. The optimal value of this setting depends on the capabilities of the target platform. For instance PackageCompressionMinPercentSaved=5 Note that some compressors (for example Oodle) do their own internal worth it check and ignore this value.
- L387 _public member_ `bool bPackageCompressionEnableDDC;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Enable DDC for IoStore compression"))` — Specifies if DDC should be used to store and retrieve compressed data when creating IoStore containers.
- L393 _public member_ `int32 PackageCompressionMinSizeToConsiderDDC;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — Specifies the minimum (uncompressed) size for storing a compressed IoStore chunk in DDC.
- L399 _public member_ `FString HttpChunkInstallDataVersion;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — Version name for HTTP Chunk Install Data.
- L403 _public member_ `bool IncludePrerequisites;` — `UPROPERTY(config, EditAnywhere, Category=Prerequisites, meta=(DisplayName="Include prerequisites installer"))` — Specifies whether to include an installer for prerequisites of packaged games, such as redistributable operating system components, on platforms that support it.
- L407 _public member_ `bool IncludeAppLocalPrerequisites;` — `UPROPERTY(config, EditAnywhere, Category = Prerequisites, meta = (DisplayName = "Include app-local prerequisites"))` — Specifies whether to include prerequisites alongside the game executable.
- L415 _public member_ `bool bShareMaterialShaderCode;` — `UPROPERTY(config, EditAnywhere, Category=Packaging)` — By default shader code gets saved inline inside material assets, enabling this option will store only shader code once as individual files This will reduce overall package size but might increase loading time
- L424 _public member_ `bool bDeterministicShaderCodeOrder;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, meta = (EditCondition = "bShareMaterialShaderCode"))` — With this option off, the shader code will be stored in the library essentially in a random order, squarely the same in which the assets were loaded by the cooker. Enabling this will sort the shaders by their hash, which makes the shader library more similar between the builds which can help patching, but can adversely affect loading times.
- L432 _public member_ `bool bSharedMaterialNativeLibraries;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, meta = (EditCondition = "bShareMaterialShaderCode", ConfigRestartRequired = true))` — By default shader shader code gets saved into individual platform agnostic files, enabling this option will use the platform-specific library format if and only if one is available This will reduce overall package size but might increase loading time
- L436 _public member_ `FDirectoryPath ApplocalPrerequisitesDirectory;` — `UPROPERTY(config, EditAnywhere, Category=Prerequisites, AdvancedDisplay)` — A directory containing additional prerequisite packages that should be staged in the executable directory. Can be relative to $(EngineDir) or $(ProjectDir)
- L443 _public member_ `bool IncludeCrashReporter;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay)` — Specifies whether to include the crash reporter in the packaged project. This is included by default for Blueprint based projects, but can optionally be disabled.
- L447 _public member_ `EProjectPackagingInternationalizationPresets InternationalizationPreset;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Internationalization Support"))` — Predefined sets of culture whose internationalization data should be packaged.
- L451 _public member_ `TArray<FString> CulturesToStage;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Languages to Package"))` — Languages whose data should be cooked, staged, and packaged.
- L455 _public member_ `TArray<FString> LocalizationTargetsToChunk;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay)` — List of localization targets that should be chunked during cooking (if using chunks)
- L459 _public member_ `int32 LocalizationTargetCatchAllChunkId = 0;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay)` — The chunk ID that should be used as the catch-all chunk for any non-asset localized strings
- L465 _public member_ `bool bCookAll;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Cook everything in the project content directory (ignore list of maps below)"))` — Cook all things in the project content directory
- L471 _public member_ `bool bCookMapsOnly;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Cook only maps (this only affects cookall)"))` — Cook only maps (this only affects the cookall flag)
- L477 _public member_ `bool bTreatWarningsAsErrorsOnCook;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Cook with Warnings As Errors enabled"))` — Cook with Warnings As Errors
- L484 _public member_ `bool bEncryptIniFiles_DEPRECATED;` — `UPROPERTY(config)` — Encrypt ini files inside of the pak file NOTE: Replaced by the settings inside the cryptokeys system. Kept here for legacy migration purposes.
- L491 _public member_ `bool bEncryptPakIndex_DEPRECATED;` — `UPROPERTY(config)` — Encrypt the pak index NOTE: Replaced by the settings inside the cryptokeys system. Kept here for legacy migration purposes.
- L498 _public member_ `bool GenerateEarlyDownloaderPakFile_DEPRECATED;` — `UPROPERTY(config)` — Enable the early downloader pak file pakearly.txt This has been superseded by the functionality in DefaultPakFileRules.ini
- L504 _public member_ `bool bSkipEditorContent;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Exclude editor content when cooking"))` — Don't include content in any editor folders when cooking.  This can cause issues with missing content in cooked games if the content is being used.
- L511 _public member_ `bool bSkipMovies;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Exclude movie files when staging"))` — Don't include movies by default when staging/packaging Specific movies can be specified below, and this can be in a platform ini
- L518 _public member_ `TArray<FString> UFSMovies;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Specific movies to Package"))` — If SkipMovies is true, these specific movies will still be added to the .pak file (if using a .pak file; otherwise they're copied as individual files) This should be the name with no extension
- L525 _public member_ `TArray<FString> NonUFSMovies;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Specific movies to Copy"))` — If SkipMovies is true, these specific movies will be copied when packaging your project, but are not supposed to be part of the .pak file This should be the name with no extension
- L532 _public member_ `TArray<FString> CompressedChunkWildcard;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay)` — If set, only these specific pak files will be compressed. This should take the form of "*pakchunk0*" This can be set in a platform-specific ini file
- L536 _public member_ `TArray<FString> IniKeyBlacklist;` — `UE_DEPRECATED(5.1, "This property is no longer supported. Use IniKeyDenylist.")` — `UPROPERTY(config /*, EditAnywhere, Category = Packaging */, meta = (DeprecatedProperty, DeprecationMessage = "This property is no longer supported. Use IniKeyDenylist."))`
- L540 _public member_ `TArray<FString> IniKeyDenylist;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — List of ini file keys to strip when packaging
- L544 _public member_ `TArray<FString> IniSectionBlacklist;` — `UE_DEPRECATED(5.1, "This property is no longer supported. Use IniSectionDenylist.")` — `UPROPERTY(config /*, EditAnywhere, Category = Packaging */, meta = (DeprecatedProperty, DeprecationMessage = "This property is no longer supported. Use IniSectionDenylist."))`
- L548 _public member_ `TArray<FString> IniSectionDenylist;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — List of ini file sections to strip when packaging
- L554 _public member_ `TArray<FString> EarlyDownloaderPakFileFiles_DEPRECATED;` — `UPROPERTY(config)` — List of specific files to include with GenerateEarlyDownloaderPakFile
- L561 _public member_ `TArray<FFilePath> MapsToCook;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "List of maps to include in a packaged build", RelativeToGameContentDir, LongPackageName))` — List of maps to include when no other map list is specified on commandline
- L568 _public member_ `TArray<FDirectoryPath> DirectoriesToAlwaysCook;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Additional Asset Directories to Cook", LongPackageName))` — Directories containing .uasset files that should always be cooked regardless of whether they're referenced by anything in your project These paths are stored either as a full package path (e.g. /Game/Folder, /Engine/Folder, /PluginName/Folder) or as a relative package path from /Game
- L575 _public member_ `TArray<FDirectoryPath> DirectoriesToNeverCook;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Directories to never cook", LongPackageName))` — Directories containing .uasset files that should never be cooked even if they are referenced by your project These paths are stored either as a full package path (e.g. /Game/Folder, /Engine/Folder, /PluginName/Folder) or as a relative package path from /Game
- L583 _public member_ `TArray<FDirectoryPath> TestDirectoriesToNotSearch;` — `UPROPERTY(config, EditAnywhere, Category = Packaging, AdvancedDisplay, meta = (DisplayName = "Test directories to not search", LongPackageName))` — Directories containing .uasset files that are for editor testing purposes and should not be included in enumerations of all packages in a root directory, because they will cause errors on load These paths are stored either as a full package path (e.g. /Game/Folder, /Engine/Folder, /PluginName/Folder) or as a relative package path from /Game
- L591 _public member_ `TArray<FDirectoryPath> DirectoriesToAlwaysStageAsUFS;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Additional Non-Asset Directories to Package", RelativeToGameContentDir))` — Directories containing files that should always be added to the .pak file (if using a .pak file; otherwise they're copied as individual files) This is used to stage additional files that you manually load via the UFS (Unreal File System) file IO API Note: These paths are relative to your project Content directory
- L599 _public member_ `TArray<FDirectoryPath> DirectoriesToAlwaysStageAsNonUFS;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Additional Non-Asset Directories To Copy", RelativeToGameContentDir))` — Directories containing files that should always be copied when packaging your project, but are not supposed to be part of the .pak file This is used to stage additional files that you manually load without using the UFS (Unreal File System) file IO API, eg, third-party libraries that perform their own internal file IO Note: These paths are relative to your project Content directory
- L607 _public member_ `TArray<FDirectoryPath> DirectoriesToAlwaysStageAsUFSServer;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Additional Non-Asset Directories to Package for dedicated server only", RelativeToGameContentDir))` — Directories containing files that should always be added to the .pak file for a dedicated server (if using a .pak file; otherwise they're copied as individual files) This is used to stage additional files that you manually load via the UFS (Unreal File System) file IO API Note: These paths are relative to your project Content directory
- L615 _public member_ `TArray<FDirectoryPath> DirectoriesToAlwaysStageAsNonUFSServer;` — `UPROPERTY(config, EditAnywhere, Category=Packaging, AdvancedDisplay, meta=(DisplayName="Additional Non-Asset Directories To Copy for dedicated server only", RelativeToGameContentDir))` — Directories containing files that should always be copied when packaging your project for a dedicated server, but are not supposed to be part of the .pak file This is used to stage additional files that you manually load without using the UFS (Unreal File System) file IO API, eg, third-party libraries that perform their own internal file IO Note: These paths are relative to your project Content directory
- L621 _public member_ `TArray<FProjectBuildSettings> ProjectCustomBuilds;` — `UPROPERTY(config, EditAnywhere, Category=CustomBuilds, meta=(DisplayName = "Additional builds for this project.", TitleProperty="Name"))` — A list of custom builds that will show up in the Platforms menu to allow customized builds that make sense for your project. Will show up near Package Project in the Platforms menu.
- L625 _public member_ `bool bRetainStagedDirectory;` — `UPROPERTY(config, EditAnywhere, Category = Packaging)` — If set, platforms that destructively edit the iostore containers during packaging will save a copy prior to doing so.
- L631 _public member_ `TArray<FProjectBuildSettings> EngineCustomBuilds;` — `UPROPERTY(config)` — A list of custom builds, specified in engine ini files, and not editable in editor, that will show up in the Platforms menu to allow customized builds for all projects
- L637 _public member_ `FString CustomStageCopyHandler;` — `UPROPERTY(config)` — The type name of a CustomStageCopyHandler subclass to instanciate during the copy build to staging directory step. See SetupCustomStageCopyHandler() in CopyBuildToStagingDirectory.Automation.cs and CustomStageCopyHandler.cs
- L642 _private member_ `FString ConfigPlatform;` — The platform to LoadConfig for to get platform-specific packaging settings
- L648 _public prototype_ `virtual void PostInitProperties() override;`
- L650 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;`
- L651 _public prototype_ `virtual bool CanEditChange( const FProperty* InProperty ) const override;`
- L655 _public prototype_ `static TArray<EProjectPackagingBuildConfigurations> GetValidPackageConfigurations();` — Gets a list of all valid packaging configurations for the current project
- L658 _public prototype_ `const FTargetInfo* GetBuildTargetInfo() const;` — Gets the current build target, checking that it's valid, and the default build target if it is not
- L661 _public function_ `void LoadSettingsForPlatform(FString PlatformName)` — For non-default object instances, this will LoadConfig for a specific platform,
- L667 _public function_ `bool GetUseZenStoreEffective() const`
- L672 _public function_ `FString GetConfigPlatform() const`
- L677 _public function_ `virtual const TCHAR* GetConfigOverridePlatform() const override`
- L684 _private prototype_ `void FixCookingPaths();` — Fix up cooking paths after they've been edited or laoded

#### struct `UProjectPackagingSettings::FConfigurationInfo`  
`struct FConfigurationInfo`  
_L200-205_
- desc: Information about each packaging configuration
- L202 _public member_ `EBuildConfiguration Configuration;`
- L203 _public member_ `FText Name;`
- L204 _public member_ `FText ToolTip;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DEVELOPERTOOLSETTINGS_API`

### `Source/Developer/DeveloperToolSettings/Public/DeveloperToolSettingsDelegates.h` (Public)


#### struct `FDeveloperToolSettingsDelegates`  
`struct FDeveloperToolSettingsDelegates`  
_L11-14_
- desc: FDeveloperToolSettingsDelegates Delegates that are needed for developer tools to talk to engine/editor
