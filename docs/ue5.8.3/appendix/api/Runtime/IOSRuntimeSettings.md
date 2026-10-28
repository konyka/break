# Runtime / IOSRuntimeSettings

- module root: `Source/Runtime/IOS/IOSRuntimeSettings`
- headers: 1; symbols: 153
- symbol kinds: class=1, enum=8, enumerator=27, function=4, member=105, prototype=4, struct=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: AudioPlatformConfiguration

### `Source/Runtime/IOS/IOSRuntimeSettings/Classes/IOSRuntimeSettings.h` (Public)


#### enum `EPowerUsageFrameRateLock`  
`enum class EPowerUsageFrameRateLock : uint8`  
_L15-28_
- reflection: `UENUM()`
- L18 _public enumerator_ `PUFRL_None = 0 UMETA(DisplayName="None")` — Frame rate is not limited.
- L21 _public enumerator_ `PUFRL_20 = 20 UMETA(DisplayName="20 FPS")` — Frame rate is limited to a maximum of 20 frames per second.
- L24 _public enumerator_ `PUFRL_30 = 30 UMETA(DisplayName="30 FPS")` — Frame rate is limited to a maximum of 30 frames per second.
- L27 _public enumerator_ `PUFRL_60 = 60 UMETA(DisplayName="60 FPS")` — Frame rate is limited to a maximum of 60 frames per second.

#### enum `EIOSVersion`  
`enum class EIOSVersion : uint8`  
_L31-39_
- reflection: `UENUM()`
- L33 _public enumerator_ `IOS_Minimum = 15 UMETA(DisplayName = "Minimum, Currently 15.0")`
- L34 _public enumerator_ `IOS_15 = 15 UMETA(DisplayName = "15.0")`
- L35 _public enumerator_ `IOS_16 = 16 UMETA(DisplayName = "16.0")`
- L36 _public enumerator_ `IOS_17 = 17 UMETA(DisplayName = "17.0")`
- L37 _public enumerator_ `IOS_18 = 18 UMETA(DisplayName = "18.0")`
- L38 _public enumerator_ `IOS_26 = 26 UMETA(DisplayName = "26.0")`

#### enum `EIOSMetalShaderStandard`  
`enum class EIOSMetalShaderStandard : uint8`  
_L43-54_
- reflection: `UENUM()`
- desc: https://support.apple.com/en-ca/HT205073
- L46 _public enumerator_ `IOSMetalSLStandard_Minimum = 0 UMETA(DisplayName="Minimum, Metal v2.4")` — Metal Shader 2.4 is the minimum as of UE5.3
- L48 _public enumerator_ `IOSMetalSLStandard_2_4 = 7 UMETA(DisplayName="Metal v2.4 (iOS 15.0/tvOS 15.0 for older devices)")` — Metal Shaders Compatible With iOS 16.0/tvOS 16.0 or later (std=metal2.4)
- L50 _public enumerator_ `IOSMetalSLStandard_3_0 = 8 UMETA(DisplayName="Metal v3.0 (iOS 16.0/tvOS 16.0)")` — Metal Shaders Compatible With iOS 16.0/tvOS 16.0 or later (std=metal3.0)
- L52 _public enumerator_ `IOSMetalSLStandard_3_1 = 9 UMETA(DisplayName="Metal v3.1 (iOS 17.0/tvOS 17.0)")` — Metal Shaders Compatible With iOS 17.0/tvOS 17.0 or later (std=metal3.1)

#### enum `EIOSLandscapeOrientation`  
`enum class EIOSLandscapeOrientation : uint8`  
_L57-64_
- reflection: `UENUM()`
- L60 _public enumerator_ `LandscapeLeft = 0 UMETA(DisplayName = "Landscape (left home button)")` — Landscape Left
- L63 _public enumerator_ `LandscapeRight = 1 UMETA(DisplayName = "Landscape (right home button)")` — Landscape Right

#### enum `EIOSCloudKitSyncStrategy`  
`enum class EIOSCloudKitSyncStrategy : uint8`  
_L67-77_
- reflection: `UENUM()`
- L70 _public enumerator_ `None = 0 UMETA(DisplayName = "Never (do not use iCloud for Load/Save Game)")` — Only at game start
- L73 _public enumerator_ `OnlyAtGameStart = 1 UMETA(DisplayName = "At game start only (iOS)")` — Only at game start
- L76 _public enumerator_ `Always = 2 UMETA(DisplayName = "Always (whenever LoadGame is called)")` — Always

#### enum `EIOSScreenEdge`  
`enum class EIOSScreenEdge : uint8`  
_L85-91_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Screen edges where the app suppresses iOS system gestures (home indicator, notification center, control center) on the first swipe so the app receives the touch. Selected edges require the user to swipe twice before the system gesture fires.
- L87 _public enumerator_ `Top = 1 << 0 UMETA(DisplayName = "Top")`
- L88 _public enumerator_ `Left = 1 << 1 UMETA(DisplayName = "Left")`
- L89 _public enumerator_ `Bottom = 1 << 2 UMETA(DisplayName = "Bottom")`
- L90 _public enumerator_ `Right = 1 << 3 UMETA(DisplayName = "Right")`

#### struct `FIOSBuildResourceFilePath`  
`struct FIOSBuildResourceFilePath`  
_L98-125_
- reflection: `USTRUCT()`
- desc: IOS Build resource file struct, used to serialize filepaths to the configs for use in the build system,
- L105 _public function_ `bool ExportTextItem(FString& ValueStr, FIOSBuildResourceFilePath const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const` — Custom export item used to serialize FIOSBuildResourceFilePath types as only a filename, no garland.
- L114 _public function_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText)` — Custom import item used to parse ini entries straight into the filename.
- L124 _public member_ `FString FilePath;` — `UPROPERTY(EditAnywhere, Category = FilePath)` — The path to the file.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIOSBuildResourceFilePath> : public TStructOpsTypeTraitsBase2<FIOSBuildResourceFilePath>`  
_L131-138_
- inherits: `TStructOpsTypeTraitsBase2<FIOSBuildResourceFilePath>`
- desc: Setup our resource filepath to make it easier to parse in UBT

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L134-137_

#### struct `FIOSBuildResourceDirectory`  
`struct FIOSBuildResourceDirectory`  
_L146-173_
- reflection: `USTRUCT()`
- desc: IOS Build resource file struct, used to serialize Directorys to the configs for use in the build system,
- L153 _public function_ `bool ExportTextItem(FString& ValueStr, FIOSBuildResourceDirectory const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const` — Custom export item used to serialize FIOSBuildResourceDirectory types as only a filename, no garland.
- L162 _public function_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText)` — Custom import item used to parse ini entries straight into the filename.
- L172 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, Category = Directory)` — The path to the file.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIOSBuildResourceDirectory> : public TStructOpsTypeTraitsBase2<FIOSBuildResourceDirectory>`  
_L179-186_
- inherits: `TStructOpsTypeTraitsBase2<FIOSBuildResourceDirectory>`
- desc: Setup our resource Directory to make it easier to parse in UBT

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L182-185_

#### class `UIOSRuntimeSettings`  
`class UIOSRuntimeSettings : public UObject`  
_L194-644_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the iOS target platform.
- L201 _public member_ `bool bEnableStoreKitSupport;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online, meta = (ConfigHierarchyEditable))` — Should StoreKit support be enabled?
- L205 _public member_ `bool bEnableGameCenterSupport;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online, meta = (ConfigHierarchyEditable))` — Should Game Center support (iOS Online Subsystem) be enabled?
- L209 _public member_ `bool bEnableCloudKitSupport;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online)` — Should Cloud Kit support (iOS Online Subsystem) be enabled?
- L213 _public member_ `EIOSCloudKitSyncStrategy IOSCloudKitSyncStrategy;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online, meta = (DisplayName = "iCloud save files sync strategy"), meta = (EditCondition = "bEnableCloudKitSupport"))` — iCloud Read stategy
- L217 _public member_ `bool bEnableRemoteNotificationsSupport;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online)` — Should push/remote notifications support (iOS Online Subsystem) be enabled?
- L221 _public member_ `bool bEnableBackgroundFetch;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online)` — Should background fetch support be enabled?
- L225 _public member_ `bool bSupportsMetal;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Rendering, meta = (DisplayName = "Metal Mobile Renderer"))` — Whether or not to compile iOS Metal shaders for the Mobile renderer (requires iOS 8+ and an A7 processor).
- L229 _public member_ `bool bSupportsMetalMobileSM5;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Rendering, meta = (DisplayName = "Metal Mobile SM5 Renderer"))` — Whether or not to compile iOS Metal shaders for the SM5 renderer (requires iOS 10+ and an A10 processor)
- L233 _public member_ `bool bSupportsMetalMobileSM6;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Rendering, meta = (DisplayName = "Metal Mobile SM6 Renderer (Experimental)"))` — Whether or not to compile iOS Metal shaders for the SM6 renderer (requires iOS 15+ and an A17 Pro processor or M2)
- L237 _public member_ `bool bEnableRayTracing = false;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Rendering, meta = (DisplayName = "Enable Ray Tracing (SM6 Experimental)", EditCondition = "bSupportsMetalMobileSM6"))` — Enable ray tracing support for Metal SM6 (requires iOS 18.0+ and an A17 Pro or M2 device)
- L241 _public member_ `bool bSupportHighRefreshRates;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Rendering, meta = (DisplayName = "Enable ProMotion 120Hz on supported iPhone devices"))` — Should the app be compatible for high refresh rate (iPhone only)
- L245 _public member_ `bool bStreamLandscapeMeshLODs;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Rendering, Meta = (DisplayName = "Stream landscape visual mesh LODs"))` — Whether to enable LOD streaming for landscape visual meshes. Requires Metal support.
- L249 _public member_ `EIOSVersion MinimumiOSVersion;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Minimum iOS Version"))` — Minimum iOS version this game supports
- L252 _public member_ `FIOSBuildResourceDirectory WindowsMetalToolchainOverride;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Override location of Metal toolchain"))`
- L256 _public member_ `bool bGeneratedSYMFile;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Generate dSYMs for code debugging and profiling"))` — Enable generation of dSYM file
- L260 _public member_ `bool bGeneratedSYMBundle;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Generate dSYMs as a bundle for third party crash tools"), meta = (EditCondition = "bGeneratedSYMFile"))` — Enable generation of dSYM bundle
- L264 _public member_ `bool bGenerateCrashReportSymbols;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Generate .udebugsymbols file"))` — Enable generation of a .udebugsymbols file, which allows offline, platform-independent symbolication for the Malloc Profiler or external crash reporting tools. Requires a dSYM file or bundle.
- L268 _public member_ `bool bGenerateXCArchive;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Generate xcode archive package"))` — Enable generation of xcode archive package
- L272 _public member_ `bool bUsesNonExemptEncryption;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "ITSAppUsesNonExemptEncryption plist value"))` — Does the app require use of NON-standard encryption
- L276 _public member_ `FString ITSEncryptionExportComplianceCode;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (EditCondition = "bUsesNonExemptEncryption", DisplayName = "Set ITSEncryptionExportComplianceCode"))` — If bUsesNonExemptEncryption, set the ITSEncryptionExportComplianceCode
- L280 _public member_ `bool bEnableAdvertisingIdentifier;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Enable Advertising Identified (IDFA)"))` — Enable Advertising Identified
- L284 _public member_ `FString AdditionalLinkerFlags;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Additional Non-Shipping Linker Flags", ConfigHierarchyEditable))` — Any additional linker flags to pass to the linker in non-shipping builds
- L288 _public member_ `FString AdditionalShippingLinkerFlags;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Additional Shipping Linker Flags", ConfigHierarchyEditable))` — Any additional linker flags to pass to the linker in shipping builds
- L292 _public member_ `FString AdditionalPlistData;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build)` — Any additional plist key/value data utilizing \n for a new line
- L296 _public member_ `TArray<FString> RequiredEntitlements;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build)` — List of any entitlements we require. The app will not initialize if the specified entitlements are not available.
- L300 _public member_ `bool bSupportsIPad;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Supports iPad"))` — Whether or not to add support for iPad devices
- L304 _public member_ `bool bSupportsIPhone;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Supports iPhone"))` — Whether or not to add support for iPhone devices
- L308 _public member_ `bool bEnableSplitView;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Enable iPad Split View"))` — Whether or not the iPad app supports Split View (also needed for StageManager support)
- L312 _public member_ `bool bEnableIOS16DynLinkerBugWAR;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Enable iOS 16 Dynamic Linker Bug Workaround (Experimental)"))` — Whether or not to enable iOS 16 dynamic linker bug workaround (bug fixed in iOS 17+, not necesssary if targetting 17.0 or higher Minimum iOS Version)
- L318 _public member_ `bool bUseSceneBasedLifecycle = false;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (DisplayName = "Use UIScene-based lifecycle (requires rebuild)"))` — Adopt the UIScene-based lifecycle as required by Apple. When true, the engine routes per-scene lifecycle through UIWindowSceneDelegate and Info.plist declares UIApplicationSceneManifest. Compile-time only - rebuild is required after changing.
- L322 _public member_ `EPowerUsageFrameRateLock FrameRateLock;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = PowerUsage, meta = (ConfigHierarchyEditable))` — Set the maximum frame rate to save on power consumption
- L326 _public member_ `bool bEnableDynamicMaxFPS;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = PowerUsage, meta = (ConfigHierarchyEditable))` — Whether or not to allow taking the MaxRefreshRate from the device instead of a constant (60fps) in IOSPlatformFramePacer
- L330 _public member_ `bool bUseRSync;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (DisplayName = "Use RSync for building IOS", ConfigHierarchyEditable))` — Enable the use of RSync for remote builds on a mac
- L334 _public member_ `FString RemoteServerName;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (ConfigHierarchyEditable))` — The name or ip address of the remote mac which will be used to build IOS
- L338 _public member_ `FString RSyncUsername;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bUseRSync", DisplayName = "Username on Remote Server", ConfigHierarchyEditable))` — The mac users name which matches the SSH Private Key, for remote builds using RSync.
- L342 _public member_ `FString RemoteServerOverrideBuildPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (ConfigHierarchyEditable))` — Optional path on the remote mac where the build files will be copied. If blank, ~/UE5/Builds will be used.
- L346 _public member_ `FIOSBuildResourceDirectory CwRsyncInstallPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bUseRSync", ConfigHierarchyEditable))` — The install directory of cwrsync.
- L350 _public member_ `FString SSHPrivateKeyLocation;` — `UPROPERTY(VisibleAnywhere, Category = "Remote Build", meta = (DisplayName = "Found Existing SSH permissions file"))` — The existing location of an SSH Key found by Unreal Engine.
- L354 _public member_ `FIOSBuildResourceFilePath SSHPrivateKeyOverridePath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bUseRSync", DisplayName = "Override existing SSH permissions file", ConfigHierarchyEditable))` — The path of the ssh permissions key to be used when connecting to the remote server.
- L358 _public member_ `bool bSupportSecondaryMac;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (DisplayName = "Enable Secondary remote Mac"))` — Support a secondary remote Mac to support to facilitate iOS/tvOS debug ?
- L362 _public member_ `FString SecondaryRemoteServerName;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bSupportSecondaryMac", ConfigHierarchyEditable))` — The name or ip address of the remote mac which will be used to build IOS
- L366 _public member_ `FString SecondaryRSyncUsername;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bSupportSecondaryMac", DisplayName = "Username on Secondary Remote Server", ConfigHierarchyEditable))` — The secondary mac users name which matches the SSH Private Key, for remote builds using RSync.
- L370 _public member_ `FString SecondaryRemoteServerOverrideBuildPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bSupportSecondaryMac", ConfigHierarchyEditable))` — Optional path on the secondary remote mac where the build files will be copied. If blank, ~/UE5/Builds will be used.
- L374 _public member_ `FIOSBuildResourceDirectory SecondaryCwRsyncInstallPath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bSupportSecondaryMac", ConfigHierarchyEditable))` — The install directory of cwrsync.
- L378 _public member_ `FString SecondarySSHPrivateKeyLocation;` — `UPROPERTY(VisibleAnywhere, Category = "Remote Build", meta = (EditCondition = "bSupportSecondaryMac", DisplayName = "Found Existing SSH permissions file for Secondary Mac"))` — The existing location of an SSH Key found by Unreal Engine.
- L382 _public member_ `FIOSBuildResourceFilePath SecondarySSHPrivateKeyOverridePath;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Remote Build", meta = (EditCondition = "bSupportSecondaryMac", DisplayName = "Override existing SSH permissions file for Secondary Mac", ConfigHierarchyEditable))` — The path of the ssh permissions key to be used when connecting to the remote server.
- L386 _public member_ `bool bUserSwitching;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Build", meta = (DisplayName = "Support user switching on tvOS"))` — Should the app be multi-users compatible on tvOS ? Requires the com.apple.developer.user-management entitlement.
- L390 _public member_ `bool bGameSupportsMultipleActiveControllers;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input, meta = (DisplayName = "Multiple gamepads support"))` — If checked, the game will be able to handle multiple gamepads at the same time (the Siri Remote is a gamepad)
- L394 _public member_ `bool bAllowRemoteRotation;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input, meta = (DisplayName = "Allow AppleTV Remote landscape mode"))` — If checked, the Siri Remote can be rotated to landscape view
- L398 _public member_ `bool bAllowControllers;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input, meta = (DisplayName = "Allow MFi (Bluetooth) controllers"))` — If checked, Bluetooth connected controllers will send input
- L402 _public member_ `bool bControllersBlockDeviceFeedback;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input, meta = (DisplayName = "Block force feedback on the device when controllers are attached"))` — Block force feedback on the device when controllers are attached.
- L406 _public member_ `bool bDisableMotionData;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input, meta = (DisplayName = "Disable Motion Controls"))` — Disables usage of device motion data. If application does not use motion data disabling it will improve battery life
- L410 _public member_ `int32 ScreenEdgesDeferredGestures;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input, meta = (DisplayName = "Screen Edges Deferred Gestures", Bitmask, BitmaskEnum = "/Script/IOSRuntimeSettings.EIOSScreenEdge"))` — Screen edges where iOS should defer its system gestures so the app receives the first swipe.
- L414 _public member_ `uint32 bSupportsPortraitOrientation : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = DeviceOrientations)` — Supports default portrait orientation. Landscape will not be supported.
- L418 _public member_ `uint32 bSupportsUpsideDownOrientation : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = DeviceOrientations)` — Supports upside down portrait orientation. Landscape will not be supported.
- L422 _public member_ `uint32 bSupportsLandscapeLeftOrientation : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = DeviceOrientations)` — Supports left landscape orientation. Portrait will not be supported.
- L426 _public member_ `uint32 bSupportsLandscapeRightOrientation : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = DeviceOrientations)` — Supports right landscape orientation. Portrait will not be supported.
- L430 _public member_ `uint32 bSupportsITunesFileSharing : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = FileSystem, meta = (DisplayName = "Support iTunes File Sharing"))` — Whether files created by the app will be accessible from the iTunes File Sharing feature
- L434 _public member_ `uint32 bSupportsFilesApp : 1;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = FileSystem, meta = (DisplayName = "Support Files App", EditCondition = "bSupportsITunesFileSharing"))` — Whether files created by the app will be accessible from within the device's Files app (requires iTunes File Sharing)
- L438 _public member_ `EIOSLandscapeOrientation PreferredLandscapeOrientation;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = DeviceOrientations, meta = (DisplayName = "Preferred Landscape Orientation"))` — The Preferred Orientation will be used as the initial orientation at launch when both Landscape Left and Landscape Right orientations are to be supported.
- L442 _public member_ `FString BundleDisplayName;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = BundleInformation)` — Specifies the the display name for the application. This will be displayed under the icon on the device.
- L446 _public member_ `FString BundleName;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = BundleInformation)` — Specifies the the name of the application bundle. This is the short name for the application bundle.
- L450 _public member_ `FString BundleIdentifier;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = BundleInformation)` — Specifies the bundle identifier for the application.
- L454 _public member_ `FString VersionInfo;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = BundleInformation)` — Specifies the version for the application.
- L463 _public member_ `bool bCustomLaunchscreenStoryboard;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = LaunchScreen, meta = (DisplayName = "Custom Launchscreen Storyboard (experimental)", EditCondition = "!MacTargetPlatform.XcodeProjectSettings.ShouldDisableIOSSettings"))` — Choose whether to use a custom LaunchScreen.Storyboard as a Launchscreen. To use this option, create a storyboard in Xcode and copy it named LaunchScreen.storyboard in Build/IOS/Resources/Interface under your Project folder. This will be compiled and copied to the bundle app and the Launch screen image above will not be included in the app. When using assets in your custom LaunchScreen.storyboard, add them in Build/IOS/Resources/Interface/Assets and they will be included.
- L467 _public member_ `bool bEnableFacebookSupport;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online)` — Whether the app supports Facebook
- L471 _public member_ `FString FacebookAppID;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online, meta = (EditCondition = "bEnableFacebookSupport"))` — Facebook App ID obtained from Facebook's Developer Centre
- L476 _public member_ `FString MobileProvision;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build)` — Mobile provision to utilize when signing. This value is stripped out when making builds.
- L481 _public member_ `FString SigningCertificate;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build)` — Signing certificate to utilize when signing. This value is stripped out when making builds.
- L485 _public member_ `bool bAutomaticSigning;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (EditCondition = "!MacTargetPlatform.XcodeProjectSettings.ShouldDisableIOSSettings"))` — Whether to use automatic signing through Xcode
- L491 _public member_ `FString IOSTeamID;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (ConfigHierarchyEditable))` — The team ID of the apple developer account to be used to autmatically sign IOS builds. This can be overridden in Turnkey with "RunUAT Turnkey -command=ManageSettings" This value is stripped out when making builds.
- L497 _public member_ `FString DevCenterUsername;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (ConfigHierarchyEditable))` — The username/email to use when logging in to DevCenter with Turnkey. This can be overridden in Turnkey with "RunUAT Turnkey -command=ManageSettings" This value is stripped out when making builds.
- L502 _public member_ `FString DevCenterPassword;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Build, meta = (ConfigHierarchyEditable))` — The password to use when logging in to DevCenter with Turnkey. NOTE: This is saved in plaintext, and is meant for shared accounts! This value is stripped out when making builds.
- L506 _public member_ `bool bDisableHTTPS;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Online, meta = (DisplayName = "Allow web connections to non-HTTPS websites"))` — Whether the app supports HTTPS
- L511 _public member_ `uint8 MetalLanguageVersion;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Metal Shader Standard To Target", ConfigRestartRequired = true))` — The Metal shader language version which will be used when compiling the shaders.
- L520 _public member_ `bool UseFastIntrinsics;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Use Fast-Math intrinsics", ConfigRestartRequired = true))` — Whether to use the Metal shading language's "fast" intrinsics. Fast intrinsics assume that no NaN or INF value will be provided as input, so are more efficient. However, they will produce undefined results if NaN/INF is present in the argument/s.
- L528 _public member_ `bool ForceFloats;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Force 32bit Floating Point Precision", ConfigRestartRequired = true))` — Whether to force Metal shaders to use 32bit floating point precision even when the shader uses half floats. Half floats are much more efficient when they are availble but have less accuracy over large ranges, as such some projects may need to use 32bit floats to ensure correct rendering.
- L537 _public member_ `bool EnableMathOptimisations;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Enable Fast-Math optimisations", ConfigRestartRequired = true))` — Whether to use of Metal shader-compiler's -ffast-math optimisations. Fast-Math performs algebraic-equivalent & reassociative optimisations not permitted by the floating point arithmetic standard (IEEE-754). These can improve shader performance at some cost to precision and can lead to NaN/INF propagation as they rely on shader inputs or variables not containing NaN/INF values. By default fast-math is enabled for performance.
- L541 _public member_ `bool bUseIntegratedKeyboard;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input)` — Whether or not the keyboard should be usable on it's own without a UITextField
- L545 _public member_ `bool bEnableVirtualKeyboardVisibilityEvent;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = Input)` — Whether or not we should receive the keyboard's visibility event (Shown/Hidden) regardless of the IntegratedKeyboard being activated or not.
- L549 _public member_ `bool bAllowWidgetEnablingIntegratedKeyboard;` — `UPROPERTY(GlobalConfig, EditAnywhere, Meta=(EditCondition = "!bUseIntegratedKeyboard"), Category = Input)` — Whether or not the EditableText Widget is allowed to enable IntegratedKeyboard. bUseIntegratedKeyboard enabled will disregard this setting.
- L553 _public member_ `int32 AudioSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", Meta = (DisplayName = "Audio Mixer Sample Rate"))` — Sample rate to run the audio mixer with.
- L557 _public member_ `int32 AudioCallbackBufferFrameSize;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "512", ClampMax = "4096", DisplayName = "Callback Buffer Size"))` — The amount of audio to compute each callback block. Lower values decrease latency but may increase CPU cost.
- L561 _public member_ `int32 AudioNumBuffersToEnqueue;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "1", UIMin = "1", DisplayName = "Number of Buffers To Enqueue"))` — The number of buffers to keep enqueued. More buffers increases latency, but can compensate for variable compute availability in audio callbacks on some platforms.
- L565 _public member_ `int32 AudioMaxChannels;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "0", UIMin = "0", DisplayName = "Max Channels"))` — The max number of channels (voices) to limit for this platform. The max channels used will be the minimum of this value and the global audio quality settings. A value of 0 will not apply a platform channel count max.
- L569 _public member_ `int32 AudioNumSourceWorkers;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "0", UIMin = "0", DisplayName = "Number of Source Workers"))` — The number of workers to use to compute source audio. Will only use up to the max number of sources. Will evenly divide sources to each source worker.
- L573 _public member_ `FString SpatializationPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled spatialization plugins to use.
- L577 _public member_ `FString SourceDataOverridePlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled source data override plugins to use.
- L581 _public member_ `FString ReverbPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled reverb plugins to use.
- L585 _public member_ `FString OcclusionPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled occlusion plugins to use.
- L589 _public member_ `FPlatformRuntimeAudioCompressionOverrides CompressionOverrides;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Various overrides for how this platform should handle compression and decompression
- L593 _public member_ `bool bSupportsBackgroundAudio;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (DisplayName = "Enable Background Audio"))` — Whether this app's audio can be played when using other apps or on the springboard
- L597 _public member_ `int32 CacheSizeKB;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|Stream Caching", meta = (DisplayName = "Max Cache Size (KB)"))` — This determines the max amount of memory that should be used for the cache at any given time. If set low (<= 8 MB), it lowers the size of individual chunks of audio during cook.
- L601 _public member_ `int32 MaxChunkSizeOverrideKB;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|Stream Caching", meta = (DisplayName = "Max Chunk Size Override (KB)"))` — This overrides the default max chunk size used when chunking audio for stream caching (ignored if < 0)
- L604 _public member_ `bool bResampleForDevice;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides")`
- L608 _public member_ `int32 SoundCueCookQualityIndex = INDEX_NONE;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides", meta = (DisplayName = "Sound Cue Cook Quality"))` — Quality Level to COOK SoundCues at (if set, all other levels will be stripped by the cooker).
- L613 _public member_ `float MaxSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Max"))`
- L616 _public member_ `float HighSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "High"))`
- L619 _public member_ `float MedSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Medium"))`
- L622 _public member_ `float LowSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Low"))`
- L625 _public member_ `float MinSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Min"))`
- L629 _public member_ `float CompressionQualityModifier;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides")` — Scales all compression qualities when cooking to this platform. For example, 0.5 will halve all compression qualities, and 1.0 will leave them unchanged.
- L633 _public member_ `float AutoStreamingThreshold;` — `UPROPERTY(GlobalConfig)` — When set to anything beyond 0, this will ensure any SoundWaves longer than this value, in seconds, to stream directly off of the disk.
- L635 _public prototype_ `virtual void PostReloadConfig(class FProperty* PropertyThatWasLoaded) override;`
- L639 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L640 _public prototype_ `virtual void PostInitProperties() override;`

#### Free symbols / members of external scopes

- L92 _prototype_ `ENUM_CLASS_FLAGS(EIOSScreenEdge);`
- L135 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon2e8b71250103`)
- L136 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon2e8b71250103`)
- L183 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon2e8b71250203`)
- L184 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon2e8b71250203`)
