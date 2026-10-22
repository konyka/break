# Plugins / SwitchboardEditor

- module root: `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor`
- headers: 11; symbols: 186
- symbol kinds: class=10, delegate=1, enum=7, enumerator=27, function=4, member=48, namespace=7, prototype=74, struct=5, typedef=3
- PrivateDependencyModuleNames: AssetRegistry, Blutility, Core, CoreUObject, DesktopPlatform, Engine, InputCore, Json, JsonUtilities, MessageLog, Projects, PropertyEditor, Settings, Slate, SlateCore, SwitchboardCommon, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/DisplayClusterRootActorReferenceDetailCustomization.h` (Private)


#### class `FDisplayClusterRootActorReferenceDetailCustomization`  
`class FDisplayClusterRootActorReferenceDetailCustomization : public IPropertyTypeCustomization`  
_L10-30_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L18 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;` — IDetailCustomization interface
- L19 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L24 _private prototype_ `FDisplayClusterRootActorReference* GetDisplayClusterRootActorReference() const;` — Returns the DCRA reference in the cached property handle
- L29 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the structure property we're editing

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardEditorModule.h` (Private)


#### class `FSwitchboardEditorModule`  
`class FSwitchboardEditorModule : public IModuleInterface`  
_L31-143_
- inherits: `IModuleInterface`
- L34 _public prototype_ `static const FString& GetSbScriptsPath();`
- L35 _public prototype_ `static const FString& GetSbThirdPartyPath();`
- L36 _public prototype_ `static const FString& GetSbExePath();`
- L44 _public function_ `static FSwitchboardEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L51 _public prototype_ `virtual void StartupModule() override;`
- L52 _public prototype_ `virtual void ShutdownModule() override;`
- L55 _public prototype_ `bool LaunchSwitchboard(const FString& Arguments = FString());`
- L56 _public prototype_ `bool LaunchListener();`
- L65 _public prototype_ `bool CreateNewConfig(const FSwitchboardNewConfigUserOptions& NewConfigUserOptions);` — Launches Switchboard with a new config that matches the current scene @param NewConfigUserOptions User options for New Config creation @return Returns true if successful
- L72 _public prototype_ `bool CompileSwitchboardListener() const;` — Compiles SwitchboardListener (Development configuration) @return Returns true if successful
- L83 _public prototype_ `ESwitchboardInstallState GetSwitchboardInstallState();`
- L85 _public prototype_ `TSharedFuture<FSwitchboardVerifyResult> GetVerifyResult(bool bForceRefresh = false);`
- L92 _public prototype_ `bool IsListenerAutolaunchEnabled(bool bForceRefreshCache = false);` — Returns whether (this engine's) SwitchboardListener is configured to run automatically. Defaults to returning a cached value to avoid hitting the registry.
- L95 _public prototype_ `bool SetListenerAutolaunchEnabled(bool bEnabled);` — Enables or disables auto-run of SwitchboardListener.
- L99 _public typedef_ `using EShortcutApp = UE::Switchboard::Private::Shorcuts::EShortcutApp;`
- L100 _public typedef_ `using EShortcutLocation = UE::Switchboard::Private::Shorcuts::EShortcutLocation;`
- L101 _public typedef_ `using EShortcutCompare = UE::Switchboard::Private::Shorcuts::EShortcutCompare;`
- L107 _public prototype_ `EShortcutCompare DoesShortcutExist(EShortcutApp App, EShortcutLocation Location, bool bForceRefreshCache = false);` — Returns whether shortcuts exist for (this engine's) Switchboard / Listener. Defaults to returning a cached value to avoid hitting the filesystem.
- L110 _public prototype_ `bool CreateOrUpdateShortcut(EShortcutApp App, EShortcutLocation Location);` — Creates (or replaces) shortcuts for Switchboard / Listener.
- L114 _public prototype_ `static UClass* GetDisplayClusterRootActorClass();` — Returns the DCRA class, nullptr if it doesn't exist (i.e. nDisplay plugin is not enabled)
- L117 _private prototype_ `void OnEngineInitComplete();`
- L118 _private prototype_ `bool OnEditorSettingsModified();`
- L120 _private prototype_ `void RunDefaultOSCListener();`
- L122 _private prototype_ `bool RunProcess(const FString& InExe, const FString& InArgs);`
- L126 _private member_ `FDelegateHandle DeferredStartDelegateHandle;`
- L128 _private member_ `FString VerifyPath;`
- L129 _private member_ `TSharedFuture<FSwitchboardVerifyResult> VerifyResult;`
- L132 _private prototype_ `bool GetListenerAutolaunchEnabled_Internal() const;`
- L134 _private member_ `bool bCachedAutolaunchEnabled;`
- L138 _private member_ `TMap< TPair<EShortcutApp, EShortcutLocation>, EShortcutCompare > CachedShortcutCompares;`
- L142 _private member_ `static TSoftObjectPtr<UClass> DisplayClusterRootActorClass;` — Cached DCRA Class

#### enum `FSwitchboardEditorModule::ESwitchboardInstallState`  
`enum class ESwitchboardInstallState`  
_L74-81_
- L76 _public enumerator_ `VerifyInProgress`
- L78 _public enumerator_ `NeedInstallOrRepair`
- L79 _public enumerator_ `ShortcutsMissing`
- L80 _public enumerator_ `Nominal`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboardPlugin, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSwitchboardPlugin, Log, All);`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Switchboard` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Switchboard`)
- L24 _function_ `template <typename... TPaths> FString ConcatPaths(FString BaseDir, TPaths... InPaths)` (scope `UE::Switchboard::Private`)

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardEditorStyle.h` (Private)


#### class `FSwitchboardEditorStyle`  
`class FSwitchboardEditorStyle : public FSlateStyleSet`  
_L11-19_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the Switchboard Toolbar
- L14 _public prototype_ `static FSwitchboardEditorStyle& Get();`
- L17 _private prototype_ `FSwitchboardEditorStyle();`
- L18 _private prototype_ `~FSwitchboardEditorStyle();`

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardMenuEntry.h` (Private)


#### class `FSwitchboardMenuEntry`  
`class FSwitchboardMenuEntry`  
_L8-15_
- L11 _public prototype_ `static void Register();`
- L12 _public prototype_ `static void AddMenu();`
- L13 _public prototype_ `static void RemoveMenu();`
- L14 _public prototype_ `static void Unregister();`

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardScriptInterop.h` (Private)


#### class `FSwitchboardUtilScript`  
`class FSwitchboardUtilScript`  
_L9-31_
- L12 _public prototype_ `static TSharedRef<FSwitchboardUtilScript> RunInstall(FStringView VenvPath);`
- L15 _public prototype_ `FSwitchboardUtilScript();` — Default constructor uses the engine python interpreter rather than a venv.
- L16 _public prototype_ `explicit FSwitchboardUtilScript(FStringView PythonVenvDir);`
- L18 _public prototype_ `~FSwitchboardUtilScript();`
- L20 _public prototype_ `bool Run(const FString& Args);`
- L22 _public prototype_ `TOptional<int32> PollStdoutAndReturnCode();`
- L25 _public member_ `FString PythonExe;`
- L26 _public member_ `FProcHandle ProcHandle;`
- L27 _public member_ `void* StdoutChildWritePipe = nullptr;`
- L28 _public member_ `void* StdoutParentReadPipe = nullptr;`
- L29 _public member_ `TArray<uint8> StdoutBuf;`
- L30 _public member_ `TOptional<int32> ReturnCode;`

#### struct `FSwitchboardVerifyResult`  
`struct FSwitchboardVerifyResult`  
_L34-54_
- L36 _public prototype_ `static TFuture<FSwitchboardVerifyResult> RunVerify(FStringView VenvPath);`
- L50 _public prototype_ `void SetFromJson(FStringView JsonSV);`
- L52 _public member_ `ESummary Summary;`
- L53 _public member_ `FString Log;`

#### enum `FSwitchboardVerifyResult::ESummary`  
`enum class ESummary`  
_L38-48_
- L40 _public enumerator_ `InterpreterMissing`
- L41 _public enumerator_ `LaunchFailed`
- L42 _public enumerator_ `Timeout`
- L43 _public enumerator_ `UnexpectedExitStatus`
- L44 _public enumerator_ `InvalidOutput`
- L45 _public enumerator_ `SelfTestFailed`
- L47 _public enumerator_ `Success`

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardSettingsCustomization.h` (Private)


#### class `FSwitchboardEditorSettingsCustomization`  
`class FSwitchboardEditorSettingsCustomization : public IDetailCustomization`  
_L12-24_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `FText GetHealthRowHintText() const;`
- L18 _public prototype_ `FText GetHealthRowButtonText() const;`
- L19 _public prototype_ `const FSlateBrush* GetHealthRowBorderBrush() const;`
- L20 _public prototype_ `const FSlateBrush* GetHealthRowIconBrush() const;`
- L23 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

#### class `FSwitchboardProjectSettingsCustomization`  
`class FSwitchboardProjectSettingsCustomization : public IDetailCustomization`  
_L27-34_
- inherits: `IDetailCustomization`
- L30 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L33 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardSetupWizard.h` (Private)


#### class `SSwitchboardSetupWizard`  
`class SSwitchboardSetupWizard : public SCompoundWidget`  
_L16-75_
- inherits: `SCompoundWidget`
- L18 _private function_ `SLATE_BEGIN_ARGS(SSwitchboardSetupWizard)`
- L39 _public prototype_ `static void OpenWindow(EWizardPage StartPage = EWizardPage::Intro);`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SWindow>& InWindow, EWizardPage InStartPage = EWizardPage::Intro);`
- L44 _protected prototype_ `TSharedRef<SWidget> Construct_Page_Intro();`
- L45 _protected prototype_ `TSharedRef<SWidget> Construct_Page_InstallProgress();`
- L46 _protected prototype_ `TSharedRef<SWidget> Construct_Page_Shortcuts();`
- L47 _protected prototype_ `TSharedRef<SWidget> Construct_Page_Autolaunch();`
- L48 _protected prototype_ `TSharedRef<SWidget> Construct_Page_Complete();`
- L50 _protected prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L52 _protected prototype_ `void SwitchToPage(EWizardPage NewPage);`
- L53 _protected prototype_ `FText GetTitleForPage(EWizardPage Page);`
- L54 _protected prototype_ `EInstallProgress GetProgress() const;`
- L56 _protected prototype_ `bool ConfirmAndInterruptInstall();`
- L58 _protected prototype_ `void Handle_RequestDestroyWindow(const TSharedRef<SWindow>& InWindow);`
- L60 _protected prototype_ `FReply Handle_Intro_InstallClicked();`
- L61 _protected prototype_ `FReply Handle_InstallProgress_ContinueClicked();`
- L64 _protected member_ `EWizardPage StartPage;`
- L65 _protected member_ `TSharedPtr<SWindow> ModalWindow;`
- L66 _protected member_ `TSharedPtr<SWidgetSwitcher> PageSwitcher;`
- L68 _protected member_ `int32 LastStdoutNumBytes = 0;`
- L69 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> InstallOutputTextBox;`
- L70 _protected member_ `TSharedPtr<SCheckBox> AutolaunchCheckbox;`
- L71 _protected member_ `TSharedPtr<SCheckBox> DesktopShortcutCheckbox;`
- L72 _protected member_ `TSharedPtr<SCheckBox> ProgramsShortcutCheckbox;`
- L74 _protected member_ `TSharedPtr<FSwitchboardUtilScript> RunningInstall;`

#### enum `SSwitchboardSetupWizard::EWizardPage`  
`enum class EWizardPage`  
_L22-29_
- L24 _public enumerator_ `Intro`
- L25 _public enumerator_ `InstallProgress`
- L26 _public enumerator_ `Shortcuts`
- L27 _public enumerator_ `Autolaunch`
- L28 _public enumerator_ `Complete`

#### enum `SSwitchboardSetupWizard::EInstallProgress`  
`enum class EInstallProgress`  
_L31-37_
- L33 _public enumerator_ `Idle`
- L34 _public enumerator_ `Running`
- L35 _public enumerator_ `Succeeded`
- L36 _public enumerator_ `Failed`

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardShortcuts.h` (Private)


#### enum `UE::Switchboard::Private::Shorcuts::EShortcutApp`  
`enum class EShortcutApp`  
_L11-15_
- L13 _public enumerator_ `Switchboard`
- L14 _public enumerator_ `Listener`

#### enum `UE::Switchboard::Private::Shorcuts::EShortcutLocation`  
`enum class EShortcutLocation`  
_L17-21_
- L19 _public enumerator_ `Desktop`
- L20 _public enumerator_ `Programs`

#### struct `UE::Switchboard::Private::Shorcuts::FShortcutParams`  
`struct FShortcutParams`  
_L23-32_
- L25 _public member_ `EShortcutLocation Location;`
- L26 _public member_ `FString BaseName;`
- L28 _public member_ `FString Target;`
- L29 _public member_ `FString Args;`
- L30 _public member_ `FString Description;`
- L31 _public member_ `FString IconPath;`

#### enum `UE::Switchboard::Private::Shorcuts::EShortcutCompare`  
`enum class EShortcutCompare`  
_L34-39_
- L36 _public enumerator_ `Missing`
- L37 _public enumerator_ `Different`
- L38 _public enumerator_ `AlreadyExists`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Switchboard` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Switchboard`)
- L9 _namespace_ `namespace Shorcuts` (scope `UE::Switchboard::Private`)
- L41 _prototype_ `FShortcutParams BuildShortcutParams(EShortcutApp App, EShortcutLocation Location);` (scope `UE::Switchboard::Private::Shorcuts`)
- L42 _prototype_ `FString GetShortcutLocationDir(EShortcutLocation Location);` (scope `UE::Switchboard::Private::Shorcuts`)
- L44 _prototype_ `bool CreateOrUpdateShortcut(const FShortcutParams& Params);` (scope `UE::Switchboard::Private::Shorcuts`)
- L45 _prototype_ `bool ReadShortcutParams(FShortcutParams& InOutParams);` (scope `UE::Switchboard::Private::Shorcuts`)
- L46 _prototype_ `EShortcutCompare CompareShortcut(const FShortcutParams& Params);` (scope `UE::Switchboard::Private::Shorcuts`)

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Private/SwitchboardTypes.h` (Private)


#### struct `FSwitchboardScriptArguments`  
`struct FSwitchboardScriptArguments`  
_L14-53_
- reflection: `USTRUCT()`
- desc: Structure that holds the parameters to the sb_script_new_config.py script that will be passed to Switchboard when auto-creating a new config. This structure is saved as a temporary json file and its path is passed to SB in the command line.
- L20 _public member_ `FString ConfigName;` — `UPROPERTY()` — Optional name of the new config. If left empty, a name will be autogenerated.
- L24 _public member_ `FString EngineDir;` — `UPROPERTY()` — Path to the Engine directory so that Switchboard knows which engine to launch
- L28 _public member_ `FString ProjectPath;` — `UPROPERTY()` — Path to the Project directory so that Switchboard knows which project to launch
- L32 _public member_ `FString Map;` — `UPROPERTY()` — Gamepath to map that Switchboard should launch
- L36 _public member_ `FString DisplayClusterConfigPath;` — `UPROPERTY()` — Path to nDisplay config that Switchboard should create the nDisplay cluster from
- L40 _public member_ `int32 NumEditorDevices = 1;` — `UPROPERTY()` — Number of Editor devices that it should create
- L44 _public member_ `bool bUseLocalhost = true;` — `UPROPERTY()` — Indicates that Switchboard should override IP addresses with localhost
- L48 _public member_ `bool bAutoConnect = true;` — `UPROPERTY()` — Indicates that Switchboard should auto-connect to the listeners of each created device
- L52 _public member_ `bool bAutoDeleteScriptArgsFile = true;` — `UPROPERTY()` — Indicates that Switchboard should delete the script arguments file

#### struct `FDisplayClusterRootActorReference`  
`struct FDisplayClusterRootActorReference`  
_L60-67_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure used to hold a reference of an nDisplay actor for detail customization purposes Note: The reason for not simply using <ADisplayClusterRootActor> is to avoid depending on the nDisplay plugin
- L66 _public member_ `TSoftObjectPtr<AActor> DCRA;` — `UPROPERTY()` — Points to the nDisplay actor

#### struct `FSwitchboardNewConfigUserOptions`  
`struct FSwitchboardNewConfigUserOptions`  
_L73-96_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure used to collect New Config options from the user
- L79 _public member_ `FString ConfigName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")` — Optional name of the new config. If left empty, a name will be autogenerated.
- L83 _public member_ `FDisplayClusterRootActorReference DCRA;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devices", meta = (DisplayName = "nDisplay Actor"))` — Indicates which nDisplay actor to use
- L87 _public member_ `int32 NumEditorDevices = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devices", meta = (DisplayName = "Editors"))` — Number of Editor devices that it should create
- L91 _public member_ `bool bUseLocalhost = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")` — Indicates that Switchboard should override IP addresses with localhost
- L95 _public member_ `bool bAutoConnect = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")` — Indicates that Switchboard should auto-connect to the listeners of each created device

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Public/SwitchboardEditorSettings.h` (Public)


#### class `USwitchboardEditorSettings`  
`class USwitchboardEditorSettings : public UObject`  
_L15-37_
- reflection: `UCLASS(Config=Engine, BlueprintType)`
- inherits: `UObject`
- L19 _private prototype_ `USwitchboardEditorSettings();`
- L24 _public member_ `FDirectoryPath VirtualEnvironmentPath;` — `UPROPERTY(Config, EditAnywhere, Category="Switchboard")` — Path to Switchboard's Python virtual environment, where third-party dependencies are installed.
- L28 _public member_ `FString ListenerCommandlineArguments;` — `UPROPERTY(Config, EditAnywhere, Category="Switchboard Listener")` — Arguments that should be passed to the Switchboard Listener.
- L32 _public prototype_ `static USwitchboardEditorSettings* GetSwitchboardEditorSettings();` — `UFUNCTION(BlueprintPure, Category="Switchboard")` — Get Editor Settings object for Switchboard
- L35 _public prototype_ `FString GetListenerPlatformPath() const;`
- L36 _public prototype_ `FString GetListenerInvocation() const;`

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Public/SwitchboardProjectSettings.h` (Public)


#### class `USwitchboardProjectSettings`  
`class USwitchboardProjectSettings : public UObject`  
_L15-31_
- reflection: `UCLASS(Config=Game, BlueprintType)`
- inherits: `UObject`
- L19 _private prototype_ `USwitchboardProjectSettings();`
- L26 _public member_ `FSoftObjectPath SwitchboardOSCListener = FSoftObjectPath(TEXT("/Swi` — `UPROPERTY(Config, EditAnywhere, Category="OSC", meta=( DisplayName="Default Switchboard OSC Listener", Tooltip="The OSC listener for Switchboard. An OSC server can be started on launch via the Virtual Production Editor section of the Project Settings. Switchboard uses port 8000 by default, but this can be configured in your Switchboard config settings."))` — OSC Listener for Switchboard. An OSC server can be started on launch via VPUtilitiesEditor
- L30 _public prototype_ `static USwitchboardProjectSettings* GetSwitchboardProjectSettings();` — `UFUNCTION(BlueprintPure, Category="Switchboard")` — Get Project Settings object for Switchboard
