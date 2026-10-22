# Runtime / DeveloperSettings

- module root: `Source/Runtime/DeveloperSettings`
- headers: 4; symbols: 52
- symbol kinds: class=4, delegate=1, function=10, member=11, prototype=24, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Projects

### `Source/Runtime/DeveloperSettings/Public/Engine/DeveloperSettings.h` (Public)


#### class `UDeveloperSettings`  
`class UDeveloperSettings : public UObject`  
_L23-77_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: The base class of any auto discovered settings object.
- L28 _public prototype_ `UDeveloperSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L31 _public prototype_ `virtual FName GetContainerName() const;` — Gets the settings container name for the settings, either Project or Editor
- L33 _public prototype_ `virtual FName GetCategoryName() const;` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L35 _public prototype_ `virtual FName GetSectionName() const;` — The unique name for your section of settings, uses the class's FName.
- L39 _public prototype_ `virtual FText GetSectionText() const;` — Gets the section text, uses the classes DisplayName by default.
- L41 _public prototype_ `virtual FText GetSectionDescription() const;` — Gets the description for the section, uses the classes ToolTip by default.
- L44 _public function_ `virtual bool SupportsAutoRegistration() const` — Whether or not this class supports auto registration or if the settings have a custom setup
- L47 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSettingsChanged, UObject*, struct FPropertyChangedEvent&);` — Returns a delegate that can be used to monitor for property changes to this object
- L48 _public prototype_ `FOnSettingsChanged& OnSettingChanged();`
- L51 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L55 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomSettingsWidget() const;` — Gets a custom widget for the settings.  This is only for very custom situations.
- L63 _protected member_ `FName CategoryName;` — The category name to use, overrides the one detected by looking at the config=... class metadata. Arbitrary category names are not supported, this must map to an existing category we support in the settings viewer.
- L66 _protected member_ `FName SectionName;` — The Section name, is the short name for the settings.  If not filled in, will be the FName of the class.
- L70 _protected prototype_ `void ImportConsoleVariableValues();` — Populates all properties that have 'ConsoleVariable' meta data with the respective console variable values
- L72 _protected prototype_ `void ExportValuesToConsoleVariables(FProperty* PropertyThatChanged);` — If property has 'ConsoleVariable' meta data, exports the property value to the specified console variable
- L75 _protected member_ `FOnSettingsChanged SettingsChangedDelegate;` — Holds a delegate that is executed after the settings section has been modified.

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSettingsChanged, UObject*, struct FPropertyChangedEvent&);` — Returns a delegate that can be used to monitor for property changes to this object

### `Source/Runtime/DeveloperSettings/Public/Engine/DeveloperSettingsBackedByCVars.h` (Public)


#### class `UDeveloperSettingsBackedByCVars`  
`class UDeveloperSettingsBackedByCVars : public UDeveloperSettings`  
_L20-32_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: The base class of auto discovered settings object where some or all of the settings are stored in console variables instead of config variables.
- L25 _public prototype_ `UDeveloperSettingsBackedByCVars(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L27 _public prototype_ `virtual void PostInitProperties() override;`
- L29 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Runtime/DeveloperSettings/Public/Engine/PlatformSettings.h` (Public)


#### struct `FPerPlatformSettings`  
`struct FPerPlatformSettings`  
_L24-35_
- reflection: `USTRUCT()`
- L28 _public prototype_ `void Initialize(TSubclassOf<UPlatformSettings> SettingsClass);`
- L32 _private member_ `TArray<TObjectPtr<UPlatformSettings>> Settings;` — `UPROPERTY(Instanced, Transient, EditAnywhere, EditFixedSize, Category = Layout)`

#### class `UPlatformSettings`  
`class UPlatformSettings : public UObject`  
_L58-82_
- reflection: `UCLASS(Abstract, perObjectConfig, MinimalAPI)`
- inherits: `UObject`
- desc: The base class of any per platform settings.  The pattern for using these is as follows. Step 1) Subclass UPlatformSettings, UMyPerPlatformSettings : public UPlatformSettings. Step 2) For your system should already have a UDeveloperSettings that you created so that users can customize other properties for your system in the project.  On that class you need to create a property of type FPerPlatformSettings, e.g. UPROPERTY(EditAnywhere, Category=Platform) FPerPlatformSettings PlatformOptions Step 3) In your UDeveloperSettings subclasses construct, there should be a line like this, PlatformOptions.Settings.Initialize(UMyPerPlatformSettings::StaticClass()); This will actually ensure that you initialize the settings exposed in the editor to whatever the current platform configuration is for them. Step 4) Nothing else needed.  In your system code, you will just call UMyPerPlatformSettings* MySettings = UPlatformSettingsManager::Get().GetSettingsForPlatform<UMyPerPlatformSettings>() that will get you the current settings for the active platform, or the simulated platform in the editor.
- L63 _public prototype_ `UPlatformSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L65 _public function_ `virtual void InitializePlatformDefaults()`
- L67 _public function_ `FName GetPlatformIniName() const`
- L70 _public function_ `virtual const TCHAR* GetConfigOverridePlatform() const override`
- L78 _private member_ `FName ConfigPlatformName;` — The platform we are an instance of settings for
- L79 _private member_ `FString ConfigPlatformNameStr;`

### `Source/Runtime/DeveloperSettings/Public/Engine/PlatformSettingsManager.h` (Public)


#### struct `FPlatformSettingsInstances`  
`struct FPlatformSettingsInstances`  
_L25-36_
- reflection: `USTRUCT()`
- desc: List of platform-specific instances for a class
- L31 _public member_ `TObjectPtr<UPlatformSettings> PlatformInstance = nullptr;` — `UPROPERTY(Transient)` — The instance for the native platform
- L35 _public member_ `TMap<FName, TObjectPtr<UPlatformSettings>> OtherPlatforms;` — `UPROPERTY(Transient)` — Instances for other platforms (only used in the editor)

#### class `UPlatformSettingsManager`  
`class UPlatformSettingsManager : public UObject`  
_L40-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The manager for all platform-specific settings
- L45 _public prototype_ `UPlatformSettingsManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L47 _public function_ `static const UPlatformSettingsManager& Get()`
- L53 _public prototype_ `UPlatformSettings* GetSettingsForPlatform(TSubclassOf<UPlatformSettings> SettingsClass) const;` — Returns the platform settings for the specified class for the current platform
- L56 _public prototype_ `UPlatformSettings* GetSettingsForPlatform(TSubclassOf<UPlatformSettings> SettingsClass, FName DesiredPlatformIniName) const;` — Returns the platform settings for the specified class for the specified platform
- L58 _public prototype_ `FName GetCurrentPlatformName() const;`
- L62 _public function_ `static FName GetEditorSimulatedPlatform()` — Gets the simulated platform
- L65 _public function_ `static void SetEditorSimulatedPlatform(FName PlatformIniName)` — Sets the current simulated platform
- L71 _public function_ `template <typename TPlatformSettingsClass> inline TPlatformSettingsClass* GetSettingsForPlatform() const`
- L77 _public prototype_ `static TArray<FName> GetKnownAndEnablePlatformIniNames();`
- L80 _public function_ `template <typename TPlatformSettingsClass> inline TArray<TObjectPtr<UPlatformSettings>> GetAllPlatformSettings() const`
- L85 _public prototype_ `TArray<TObjectPtr<UPlatformSettings>> GetAllPlatformSettings(TSubclassOf<UPlatformSettings> SettingsClass) const;`
- L88 _public function_ `template <typename TPlatformSettingsClass> inline TPlatformSettingsClass* GetSettingsForPlatform(FName TargetIniPlatformName) const`
- L97 _private prototype_ `UPlatformSettings* CreateSettingsObjectForPlatform(TSubclassOf<UPlatformSettings> SettingsClass, FName TargetIniPlatformName) const;` — Creates a settings object for the specified class and platform
- L103 _private member_ `mutable TMap<TSubclassOf<UPlatformSettings>, FPlatformSettingsInstances> SettingsMap;` — `UPROPERTY(Transient)` — Created platform-specific settings
- L106 _private member_ `FName IniPlatformName;` — The true platform name for the current platform (unaffected by previews, etc...)
- L110 _private member_ `static FName SimulatedEditorPlatform;` — Current simulated platform
