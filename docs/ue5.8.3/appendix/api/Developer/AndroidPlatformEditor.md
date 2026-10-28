# Developer / AndroidPlatformEditor

- module root: `Source/Developer/Android/AndroidPlatformEditor`
- headers: 4; symbols: 61
- symbol kinds: class=4, function=1, macro=1, member=29, prototype=26
- PrivateDependencyModuleNames: AndroidDeviceDetection, AndroidRuntimeSettings, AudioSettingsEditor, Core, CoreUObject, DesktopPlatform, DesktopWidgets, EditorWidgets, Engine, InputCore, MainFrame, MaterialShaderQualitySettings, PropertyEditor, RHI, RenderCore, ShaderPlatformConfigEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl
- PrivateIncludePathModuleNames: Settings

### `Source/Developer/Android/AndroidPlatformEditor/Private/AndroidLicenseDialog.h` (Private)


#### class `SAndroidLicenseDialog`  
`class SAndroidLicenseDialog : public SCompoundWidget`  
_L16-44_
- inherits: `SCompoundWidget`
- desc: Credit screen widget that displays a scrolling list contributors.
- L19 _public function_ `SLATE_BEGIN_ARGS( SAndroidLicenseDialog )`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `bool HasLicense();`
- L30 _public prototype_ `void SetLicenseAcceptedCallback(const FSimpleDelegate& InOnLicenseAccepted);`
- L33 _private member_ `bool bLicenseValid;`
- L35 _private prototype_ `FReply OnAgree();`
- L36 _private prototype_ `FReply OnCancel();`
- L38 _private member_ `FSHAHash LicenseHash;`
- L41 _private member_ `TSharedPtr<SScrollBox> ScrollBox;` — The widget that scrolls the license text
- L43 _private member_ `FSimpleDelegate OnLicenseAccepted;`

### `Source/Developer/Android/AndroidPlatformEditor/Private/AndroidSDKSettings.h` (Private)


#### class `UAndroidSDKSettings`  
`class UAndroidSDKSettings : public UObject`  
_L20-56_
- reflection: `UCLASS(MinimalAPI, config=Engine, globaluserconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Android SDK setup.
- L27 _public member_ `FDirectoryPath SDKPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = SDKConfig, Meta = (DisplayName = "Location of Android SDK (the directory usually contains 'android-sdk-')"))` — Location on disk of the Android SDK (falls back to ANDROID_HOME environment variable if this is left blank)
- L31 _public member_ `FDirectoryPath NDKPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = SDKConfig, Meta = (DisplayName = "Location of Android NDK (the directory usually contains 'android-ndk-')"))` — Location on disk of the Android NDK (falls back to NDKROOT environment variable if this is left blank)
- L35 _public member_ `FDirectoryPath JavaPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = SDKConfig, Meta = (DisplayName = "Location of JAVA (the directory usually contains 'jdk')"))` — Location on disk of Java (falls back to JAVA_HOME environment variable if this is left blank)
- L39 _public member_ `FString SDKAPILevel;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = SDKConfig, Meta = (DisplayName = "SDK API Level (specific version e.g. 'android-NN', 'latest', or 'matchndk' - see tooltip)"))` — Which SDK to package and compile Java with (a specific version, usually (without quotes): 'android-NN' or (without quotes) 'latest' for latest version on disk, or 'matchndk' to match the NDK API Level)
- L43 _public member_ `FString NDKAPILevel;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = SDKConfig, Meta = (DisplayName = "NDK API Level (specific version or 'latest' - see tooltip)"))` — Which NDK to compile with (a specific version or (without quotes) 'latest' for latest version on disk). Note that choosing android-21 or later won't run on pre-5.0 devices.
- L48 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L50 _public prototype_ `void SetTargetModule(ITargetPlatformManagerModule * TargetManagerModule);`
- L51 _public prototype_ `void SetDeviceDetection(IAndroidDeviceDetection * AndroidDeviceDetection);`
- L52 _public prototype_ `void UpdateTargetModulePaths();`
- L53 _public member_ `ITargetPlatformManagerModule * TargetManagerModule;`
- L54 _public member_ `IAndroidDeviceDetection * AndroidDeviceDetection;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANDROIDPLATFORMEDITOR_API`

### `Source/Developer/Android/AndroidPlatformEditor/Private/AndroidSDKSettingsCustomization.h` (Private)


#### class `FAndroidSDKSettingsCustomization`  
`class FAndroidSDKSettingsCustomization : public IDetailCustomization`  
_L14-33_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L25 _private prototype_ `FAndroidSDKSettingsCustomization();`
- L27 _private prototype_ `void BuildSDKPathSection(IDetailLayoutBuilder& DetailLayout);`
- L30 _private member_ `IDetailLayoutBuilder* SavedLayoutBuilder;`
- L31 _private member_ `ITargetPlatformManagerModule * TargetPlatformManagerModule;`

### `Source/Developer/Android/AndroidPlatformEditor/Private/AndroidTargetSettingsCustomization.h` (Private)


#### class `FAndroidTargetSettingsCustomization`  
`class FAndroidTargetSettingsCustomization : public IDetailCustomization`  
_L17-83_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L28 _private prototype_ `FAndroidTargetSettingsCustomization();`
- L30 _private prototype_ `void BuildAppManifestSection(IDetailLayoutBuilder& DetailLayout);`
- L31 _private prototype_ `void BuildIconSection(IDetailLayoutBuilder& DetailLayout);`
- L32 _private prototype_ `void BuildLaunchImageSection(IDetailLayoutBuilder& DetailLayout);`
- L35 _private prototype_ `FReply OpenBuildFolder();` — Navigates to the build files in the explorer or finder
- L38 _private prototype_ `void CopySetupFilesIntoProject();` — Copies the setup files for the platform into the project
- L41 _private prototype_ `void CopyGooglePlayAppIDFileIntoProject();` — Copies the strings.xml file for the platform into the project
- L44 _private prototype_ `void OnAppIDModified();` — Called when the app id is modified
- L47 _private prototype_ `void OnLicenseAccepted();` — Called when License accepted
- L50 _private prototype_ `bool IsLicenseInvalid() const;` — returns whether Android SDK license valid
- L53 _private prototype_ `FReply OnAcceptSDKLicenseClicked();` — Show license agreement for user to accept
- L56 _private member_ `double LastLicenseChecktime;`
- L58 _private member_ `const FString AndroidRelativePath;`
- L60 _private member_ `const FString EngineAndroidPath;`
- L61 _private member_ `const FString GameAndroidPath;`
- L63 _private member_ `const FString EngineGooglePlayAppIDPath;`
- L64 _private member_ `const FString GameGooglePlayAppIDPath;`
- L66 _private member_ `const FString EngineProguardPath;`
- L67 _private member_ `const FString GameProguardPath;`
- L69 _private member_ `const FString EngineProjectPropertiesPath;`
- L70 _private member_ `const FString GameProjectPropertiesPath;`
- L72 _private member_ `TArray<struct FPlatformIconInfo> IconNames;`
- L73 _private member_ `TArray<struct FPlatformIconInfo> LaunchImageNames;`
- L76 _private member_ `TAttribute<bool> SetupForPlatformAttribute;` — Is the manifest writable?
- L79 _private member_ `TAttribute<bool> SetupForGooglePlayAttribute;` — Is the App ID string writable?
- L81 _private member_ `FAudioPluginWidgetManager AudioPluginWidgetManager;`
- L82 _private member_ `IDetailLayoutBuilder* SavedLayoutBuilder;`
