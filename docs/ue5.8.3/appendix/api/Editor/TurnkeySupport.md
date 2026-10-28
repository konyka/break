# Editor / TurnkeySupport

- module root: `Source/Editor/TurnkeySupport`
- headers: 4; symbols: 82
- symbol kinds: class=3, delegate=2, enum=3, enumerator=13, function=2, macro=1, member=13, prototype=43, struct=2
- PrivateDependencyModuleNames: Analytics, ApplicationCore, Core, CoreUObject, DesktopPlatform, DeveloperToolSettings, EngineSettings, InputCore, LauncherServices, MessageLog, Projects, RHI, RenderCore, SettingsEditor, Slate, SlateCore, SourceControl, TargetPlatform, ToolMenus, TurnkeyIO, UATHelper, UnrealEd, Zen
- PrivateIncludePathModuleNames: DerivedDataCache, GameProjectGeneration, LevelEditor, MainFrame, ProjectTargetPlatformEditor, Settings

### `Source/Editor/TurnkeySupport/Private/TurnkeyEditorSupport.h` (Private)


#### class `FTurnkeyEditorSupport`  
`class FTurnkeyEditorSupport`  
_L10-30_
- L14 _public prototype_ `static FString GetUATOptions();`
- L16 _public prototype_ `static void PrepareToLaunchRunningMap(const FString& DeviceId, const FString& DeviceName);`
- L17 _public prototype_ `static void LaunchRunningMap(const FString& DeviceId, const FString& DeviceName, const FString& ProjectPath, bool bUseTurnkey, bool bOnSimulator = false, FStringView Architecture = {});`
- L18 _public prototype_ `static void AddEditorOptions(struct FToolMenuSection& MenuBuilder);`
- L20 _public prototype_ `static void SaveAll();`
- L21 _public prototype_ `static bool DoesProjectHaveCode();`
- L22 _public prototype_ `static void RunUAT(const FString& CommandLine, const FText& PlatformDisplayName, const FText& TaskName, const FText& TaskShortName, const struct FSlateBrush* TaskIcon, const TArray<struct FAnalyticsEventAttribute>* OptionalAnalyticsParamArray = nullptr, TFunction<void(FString, double)> ResultCallback=TFunction<void(FString, double)>(), const FText& ExtraSubText = FText::GetEmpty());`
- L24 _public prototype_ `static bool ShowOKCancelDialog(FText Message, FText Title);`
- L25 _public prototype_ `static void ShowRestartToast();`
- L26 _public prototype_ `static void ShowRebuildToast();`
- L27 _public prototype_ `static bool CheckSupportedPlatforms(FName IniPlatformName);`
- L28 _public prototype_ `static void ShowInstallationHelp(FName IniPlatformName, FString DocLink);`
- L29 _public prototype_ `static bool IsPIERunning();`

### `Source/Editor/TurnkeySupport/Private/TurnkeySupportModule.h` (Private)


#### class `FTurnkeySupportModule`  
`class FTurnkeySupportModule : public ITurnkeySupportModule #if WITH_EDITOR , public FSelfRegisteringExec #endif`  
_L17-67_
- inherits: `ITurnkeySupportModule,FSelfRegisteringExec`
- desc: Editor main frame module
- L24 _public prototype_ `virtual void MakeTurnkeyMenu(FToolMenuSection& MenuSection, const FToolMenuInsert& InsertPosition) const override;`
- L25 _public prototype_ `virtual void MakeQuickLaunchItems(class UToolMenu* Menu, FOnQuickLaunchSelected ExternalOnClickDelegate) const override;`
- L26 _public prototype_ `virtual void RepeatQuickLaunch(FString DeviceId) override;`
- L30 _public prototype_ `virtual void UpdateSdkInfo() override;`
- L31 _public prototype_ `void UpdateSdkInfoForAllDevices();`
- L32 _public prototype_ `void UpdateSdkInfoForProxy(const TSharedRef<class ITargetDeviceProxy>& AddedProxy);`
- L33 _public prototype_ `virtual void UpdateSdkInfoForDevices(TArray<FString> DeviceIds) override;`
- L35 _public prototype_ `virtual FTurnkeySdkInfo GetSdkInfo(FName PlatformName, bool bBlockIfQuerying = true) const override;`
- L36 _public prototype_ `virtual FTurnkeySdkInfo GetSdkInfoForDeviceId(const FString& DeviceId) const override;`
- L37 _public prototype_ `virtual void ClearDeviceStatus(FName PlatformName=NAME_None) override;`
- L42 _public prototype_ `virtual void StartupModule( ) override;`
- L43 _public prototype_ `virtual void ShutdownModule( ) override;`
- L45 _public function_ `virtual bool SupportsDynamicReloading( ) override`
- L53 _private member_ `TMap<FName, FTurnkeySdkInfo> PerPlatformSdkInfo;` — Information about the validity of using a platform, discovered via Turnkey
- L56 _private member_ `TMap<FString, FTurnkeySdkInfo> PerDeviceSdkInfo;` — Information about the validity of each connected device (by string, discovered by Turnkey)
- L60 _private prototype_ `TSharedRef<SWidget> MakeTurnkeyMenuWidget() const;` — menu helpers
- L64 _private prototype_ `virtual bool Exec_Editor( class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar ) override;` — FSelfRegisteringExec interface

### `Source/Editor/TurnkeySupport/Public/Interfaces/ITurnkeySupportModule.h` (Public)


#### enum `ETurnkeyPlatformSdkStatus`  
`enum class ETurnkeyPlatformSdkStatus : uint8`  
_L20-29_
- L22 _public enumerator_ `Unknown`
- L23 _public enumerator_ `Querying`
- L24 _public enumerator_ `Valid`
- L25 _public enumerator_ `OutOfDate`
- L26 _public enumerator_ `NoSdk`
- L27 _public enumerator_ `Error`

#### enum `ETurnkeyDeviceStatus`  
`enum class ETurnkeyDeviceStatus : uint8`  
_L31-37_
- L33 _public enumerator_ `Unknown`
- L34 _public enumerator_ `InvalidPrerequisites`
- L35 _public enumerator_ `SoftwareValid`
- L36 _public enumerator_ `SoftwareInvalid`

#### enum `ETurnkeyDeviceAutoSoftwareUpdateMode`  
`enum class ETurnkeyDeviceAutoSoftwareUpdateMode : uint8`  
_L39-44_
- L41 _public enumerator_ `Unknown`
- L42 _public enumerator_ `Disabled`
- L43 _public enumerator_ `Enabled`

#### struct `FTurnkeySdkInfo`  
`struct FTurnkeySdkInfo`  
_L46-57_
- L49 _public member_ `ETurnkeyPlatformSdkStatus Status = ETurnkeyPlatformSdkStatus::Unknown;`
- L50 _public member_ `ETurnkeyDeviceStatus DeviceStatus = ETurnkeyDeviceStatus::Unknown;`
- L51 _public member_ `ETurnkeyDeviceAutoSoftwareUpdateMode DeviceAutoSoftwareUpdates = ETurnkeyDeviceAutoSoftwareUpdateMode::Unknown;`
- L52 _public member_ `FText SdkErrorInformation;`
- L53 _public member_ `TMap<FString, Version> SDKVersions;`
- L54 _public member_ `bool bCanInstallFullSdk;`
- L55 _public member_ `bool bCanInstallAutoSdk;`
- L56 _public member_ `bool bHasBestSdk;`

#### struct `FTurnkeySdkInfo::Version`  
`struct Version`  
_L48-48_
- L48 _public member_ `struct Version { FString Min, Max, Current; };`
- L48 _public member_ `struct Version { FString Min, Max, Current; };`
- L48 _public member_ `struct Version { FString Min, Max, Current; };`

#### class `ITurnkeySupportModule`  
`class ITurnkeySupportModule : public IModuleInterface`  
_L67-123_
- inherits: `IModuleInterface`
- desc: Interface for turnkey support module
- L75 _public prototype_ `virtual void MakeTurnkeyMenu(FToolMenuSection& MenuSection, const FToolMenuInsert& InsertPosition) const = 0;` — Make a Platforms menu in the given MenuSection at the specified InsertPosition
- L80 _public prototype_ `virtual void MakeQuickLaunchItems(class UToolMenu* Menu, FOnQuickLaunchSelected ExternalOnClickDelegate) const = 0;` — Make menu items for Quick Launch, so they can be added to the Play menu
- L85 _public prototype_ `virtual void RepeatQuickLaunch(FString DeviceId) = 0;` — Runs Turnkey to get the Sdk information for all known platforms
- L90 _public prototype_ `virtual void UpdateSdkInfo() = 0;` — Runs Turnkey to get the Sdk information for all known platforms
- L95 _public prototype_ `virtual void UpdateSdkInfoForDevices(TArray<FString> DeviceIds) = 0;` — Runs Turnkey to get the Sdk information for a list of devices
- L98 _public prototype_ `virtual FTurnkeySdkInfo GetSdkInfo(FName PlatformName, bool bBlockIfQuerying = true) const = 0;`
- L99 _public prototype_ `virtual FTurnkeySdkInfo GetSdkInfoForDeviceId(const FString& DeviceId) const = 0;`
- L101 _public prototype_ `virtual void ClearDeviceStatus(FName PlatformName=NAME_None) = 0;` — @todo turnkey look into remove this
- L111 _public function_ `static ITurnkeySupportModule& Get( )` — Gets a reference to the search module instance. @todo gmp: better implementation using dependency injection. @return A reference to the MainFrame module.
- L122 _public prototype_ `virtual ~ITurnkeySupportModule( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_WITH_TURNKEY_SUPPORT 1`
- L61 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQuickLaunchSelected, FString);`
- L61 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQuickLaunchSelected, FString);`

### `Source/Editor/TurnkeySupport/Public/TurnkeySupport.h` (Public)


#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTurnkeySupport, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTurnkeySupport, Log, All);`
- L28 _prototype_ `FString ConvertToDDPIPlatform(const FString& Platform);`
- L29 _prototype_ `FName ConvertToDDPIPlatform(const FName& Platform);`
- L30 _prototype_ `FString ConvertToUATPlatform(const FString& Platform);`
- L31 _prototype_ `FString ConvertToUATDeviceId(const FString& DeviceId);`
- L32 _prototype_ `FString ConvertToDDPIDeviceId(const FString& DeviceId);`
