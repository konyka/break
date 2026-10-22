# Plugins / StormSyncDrives

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives`
- headers: 6; symbols: 49
- symbol kinds: class=4, delegate=1, enum=1, enumerator=7, function=4, member=7, prototype=24, struct=1
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, MessageLog, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Private/StormSyncDrivesLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncDrives, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncDrives, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Private/StormSyncDrivesModule.h` (Private)


#### class `FStormSyncDrivesModule`  
`class FStormSyncDrivesModule : public IStormSyncDrivesModule`  
_L18-85_
- inherits: `IStormSyncDrivesModule`
- desc: Main entry point and implementation of StormSync Mounted Drives Runtime module.
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `virtual bool RegisterMountPoint(const FStormSyncMountPointConfig& InMountPoint, FText& ErrorText, EStormSyncDriveErrorCode* OutErrorCode = nullptr) override;`
- L28 _public prototype_ `virtual bool UnregisterMountPoint(const FStormSyncMountPointConfig& InMountPoint, FText& ErrorText) override;`
- L33 _private member_ `static constexpr const TCHAR* LogName = TEXT("Sto` — The name of the message output log we will send messages to
- L39 _private member_ `TMap<FString, FStormSyncMountPointConfig> CachedMountPoints;` — Stores a cache of the currently mounted paths. This will allow us to determine when the user changes settings and require us to update our mount mapping.
- L43 _private member_ `TSharedPtr<IMessageLogListing> LogListing;` — Listing used in the editor by the Message Log.
- L47 _private prototype_ `void OnPostEngineInit();` — Core OnPostEngineInit delegate used to mount any stored config in developer settings
- L50 _private prototype_ `TArray<FStormSyncMountPointConfig> GetCommandLineConfigs() const;` — Return the storm sync mount point config that was set on the command line.
- L53 _private prototype_ `bool RemoveFromCacheIfNotInConfigs(const TArray<FStormSyncMountPointConfig>& Configs);` — If the cache configs are not in the given list then unregister and remove them from the cache.
- L60 _private prototype_ `void OnSettingsChanged(UObject* InSettings, FPropertyChangedEvent& InPropertyChangedEvent);` — Developer settings changed handler. Called anytime settings changed. Used to validate user config and if successful, mount the set of Mount Points to Mount Directories.
- L66 _private prototype_ `bool IsMountPointInCache(const FStormSyncMountPointConfig& InMountPoint) const;` — Checks to see if the given mount point is currently in the cache.  If yes, then that implies that that we have already mapped the mount point and we do not need to re-process.
- L71 _private prototype_ `bool MountDriveHelper(const FStormSyncMountPointConfig& InMountPoint);` — Helper function that unregisters an existing mount point and remaps it.
- L79 _private prototype_ `void ResetMountedDrivesFromSettings(const UStormSyncDrivesSettings* InSettings);` — Unregisters previously mounted drives, cache (update internal list of MountedDrives shared pointers), and register / mount the new config. Happens once on engine init, and anytime the user settings changed.
- L81 _private prototype_ `void UnregisterMountedDrives();`
- L84 _private prototype_ `static void AddMessageError(const FText& Text);` — Static helper to log an error to the message log. Used during validation process.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Public/IStormSyncDrivesModule.h` (Public)


#### class `IStormSyncDrivesModule`  
`class IStormSyncDrivesModule : public IModuleInterface`  
_L12-48_
- inherits: `IModuleInterface`
- desc: Public interface for Storm Sync Drives module and API
- L15 _public function_ `static bool IsAvailable()`
- L21 _public function_ `static IStormSyncDrivesModule& Get()`
- L37 _public prototype_ `virtual bool RegisterMountPoint(const FStormSyncMountPointConfig& InMountPoint, FText& ErrorText, EStormSyncDriveErrorCode* OutError = nullptr) = 0;` — Register and mount the provided mount point config (with a Mount Point root path and Mount Directory filesystem path) Mount root path and directory will be validated first, and errors will be logged into Message Logs. @param InMountPoint The config with root mount path & directory to mount @param ErrorText Localized text describing the error in case mounting failed @param OutError optional enum for further details on the operation's error if any @returns true if we were able to register the mount point
- L47 _public prototype_ `virtual bool UnregisterMountPoint(const FStormSyncMountPointConfig& InMountPoint, FText& ErrorText) = 0;` — Unregisters the provided mount point config, if it was previously mounted. @param InMountPoint The config with root mount path & directory to unmount @param ErrorText Localized text describing the error in case unmounting failed @returns true if we were able to unregister the mount point

### `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Public/StormSyncDrivesEnums.h` (Public)


#### enum `EStormSyncDriveErrorCode`  
`enum class EStormSyncDriveErrorCode : uint8`  
_L7-29_
- L10 _public enumerator_ `None` — No error
- L13 _public enumerator_ `EmptyRootPath` — Root path is empty
- L16 _public enumerator_ `TopLevelRootDisallowed` — Path is "/". No mounting allowed at the top level root
- L19 _public enumerator_ `InvalidPackageNameFormat` — Path does not have a standard package name format
- L22 _public enumerator_ `InvalidPathLevel` — Path is expected to be within /Game or one level path e.g. /Example when not within /Game
- L25 _public enumerator_ `EmptyDirectoryPath` — Directory path is empty
- L28 _public enumerator_ `DirectoryNotFound` — Directory path does not exist

### `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Public/StormSyncDrivesSettings.h` (Public)


#### struct `FStormSyncMountPointConfig`  
`struct FStormSyncMountPointConfig`  
_L10-41_
- reflection: `USTRUCT()`
- desc: Holds config for a given Mount Point (eg. /RootPath) to a filesystem directory (can be local, could be networked)
- L16 _public member_ `FString MountPoint;` — `UPROPERTY(EditAnywhere, Category="Mounted Drives")` — Represents the root Mount Point for the drive (eg. /MyDrive or /Game/MyDrive)
- L20 _public member_ `FDirectoryPath MountDirectory;` — `UPROPERTY(EditAnywhere, Category="Mounted Drives")` — Represents the absolute path of the mounted directory
- L24 _public member_ `bool bResolveAsRelativePath = false;` — `UPROPERTY(EditAnywhere, Category = "Mounted Drives")` — The path in MountDirectory should be interpreted as a relative path to the content directory of the active project.
- L26 _public prototype_ `FStormSyncMountPointConfig() = default;`
- L28 _public function_ `FStormSyncMountPointConfig(const FString& InMountPoint, const FDirectoryPath& InMountDirectory, bool bInResolveAsRelativePath = false) : MountPoint(InMountPoint) , MountDirectory(InMountDirectory) , bResolveAsRelativePath(bInResolveAsRelativePath)`
- L35 _public function_ `FStormSyncMountPointConfig(const FString& InMountPoint, const FString& InMountDirectory, bool bInResolveAsRelativePath = false) : MountPoint(InMountPoint) , bResolveAsRelativePath(bInResolveAsRelativePath)`

#### class `UStormSyncDrivesSettings`  
`class UStormSyncDrivesSettings : public UDeveloperSettings`  
_L62-72_
- reflection: `UCLASS(MinimalAPI, Config=Game, DefaultConfig, DisplayName="Mount Points Settings")`
- inherits: `UDeveloperSettings`
- desc: Settings for the StormSyncDrives module. Handle configuration for shared network or local mounted drives. Configuration must adhere to the following rules: * Should not have multiple entries with same mount point and / or directory (Mount Paths / Directories must have unique values) * Mount Points and Directories must not be empty * Mount Point cannot be "/", must start with a leading "/" and should not end with a trailing "/" * Mount Point cannot contain "//" or any other invalid characters (\\:*?\"<*|' ,.&!~\n\r\t@#) * Mount Point when outside "/Game" must be one level only (eg. /Example is ok, /Example/Path is not) * Mount Directory must match an existing filesystem path Changes done here will be validated and errors logged to message log. If successful, mount points will be updated and should be available in the content browser.
- L67 _public prototype_ `UStormSyncDrivesSettings();`
- L71 _public member_ `TArray<FStormSyncMountPointConfig> MountPoints;` — `UPROPERTY(config, EditAnywhere, Category = "Mounted Drives", meta=(TitleProperty="{MountPoint} mapped to {MountDirectory}"))` — List of mounted drives configuration

### `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Public/StormSyncDrivesUtils.h` (Public)


#### class `FStormSyncDrivesUtils`  
`class FStormSyncDrivesUtils`  
_L12-41_
- desc: Provides validation helpers
- L16 _public prototype_ `static bool ValidateMountPoint(const FStormSyncMountPointConfig& InMountPoint, FText& ErrorText, EStormSyncDriveErrorCode* OutErrorCode = nullptr);` — Checks validity for a mount point
- L19 _public prototype_ `static bool ValidateRootPath(const FString& InRootPath, FText& ErrorText, EStormSyncDriveErrorCode* OutErrorCode = nullptr);` — Checks validity for a mount point
- L22 _public prototype_ `static bool ValidateDirectory(const FDirectoryPath& InDirectory, FText& ErrorText, EStormSyncDriveErrorCode* OutErrorCode = nullptr);` — Checks validity for a mount directory
- L25 _public prototype_ `static bool ValidateNonDuplicates(const TArray<FStormSyncMountPointConfig> InMountPoints, TArray<FText>& ValidationErrors);` — Checks validity for any duplicates regarding Mount Point (Root Paths) and filesystem directory
- L28 _public prototype_ `static bool IsValidRootPathLevel(const FString& InRootPath);` — Checks validity of mount points and only allow one level packages (eg. /Foo again /Foo/Bar)
- L40 _public prototype_ `static bool IsValidTextForLongPackageName(FStringView InLongPackageName, FPackageName::EErrorCode* OutReason = nullptr);` — Report whether a given name is the proper format for a PackageName, without checking whether it is in one of the registered mount points. Notable difference from FPackageName::IsValidTextForLongPackageName is that we don't check for minimal path length requirement, we are only interested in testing the front path (eg. /Foo vs /Foo/Dummy) @param InLongPackageName The package name to test @param OutReason When returning false, this will provide a description of what was wrong with the name. @return true if valid text for a long package name
