# Runtime / LauncherPlatform

- module root: `Source/Runtime/Portal/LauncherPlatform`
- headers: 6; symbols: 41
- symbol kinds: class=7, delegate=2, function=6, member=5, prototype=18, typedef=3
- PrivateDependencyModuleNames: Core, HTTP

### `Source/Runtime/Portal/LauncherPlatform/Private/LauncherPlatformPrivatePCH.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherPlatform, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherPlatform, Log, All);`

### `Source/Runtime/Portal/LauncherPlatform/Private/Linux/LauncherPlatformLinux.h` (Private)


#### class `FLauncherPlatformLinux`  
`class FLauncherPlatformLinux : public ILauncherPlatform`  
_L8-14_
- inherits: `ILauncherPlatform`
- L12 _public prototype_ `virtual bool CanOpenLauncher(bool Install) override;` — ILauncherPlatform Implementation
- L13 _public prototype_ `virtual bool OpenLauncher(const FOpenLauncherOptions& Options) override;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef FLauncherPlatformLinux FLauncherPlatform;`

### `Source/Runtime/Portal/LauncherPlatform/Private/Mac/LauncherPlatformMac.h` (Private)


#### class `FLauncherPlatformMac`  
`class FLauncherPlatformMac : public ILauncherPlatform`  
_L8-18_
- inherits: `ILauncherPlatform`
- L12 _public prototype_ `virtual bool CanOpenLauncher(bool Install) override;` — ILauncherPlatform Implementation
- L13 _public prototype_ `virtual bool OpenLauncher(const FOpenLauncherOptions& Options) override;`
- L16 _private prototype_ `bool IsLauncherInstalled() const;`
- L17 _private prototype_ `bool GetLauncherInstallerPath(FString& OutInstallerPath) const;`

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef FLauncherPlatformMac FLauncherPlatform;`

### `Source/Runtime/Portal/LauncherPlatform/Private/Windows/LauncherPlatformWindows.h` (Private)


#### class `FLauncherPlatformWindows`  
`class FLauncherPlatformWindows : public ILauncherPlatform`  
_L8-18_
- inherits: `ILauncherPlatform`
- L12 _public prototype_ `virtual bool CanOpenLauncher(bool Install) override;` — ILauncherPlatform Implementation
- L13 _public prototype_ `virtual bool OpenLauncher(const FOpenLauncherOptions& Options) override;`
- L16 _private prototype_ `bool IsLauncherInstalled() const;`
- L17 _private prototype_ `bool GetLauncherInstallerPath(FString& OutInstallerPath);`

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef FLauncherPlatformWindows FLauncherPlatform;`

### `Source/Runtime/Portal/LauncherPlatform/Public/ILauncherPlatform.h` (Public)


#### class `FOpenLauncherOptions`  
`class FOpenLauncherOptions`  
_L7-79_
- L10 _public function_ `FOpenLauncherOptions()`
- L12 _public function_ `FOpenLauncherOptions(FString InLauncherRelativeUrl) : LauncherRelativeUrl(InLauncherRelativeUrl)`
- L21 _public function_ `FOpenLauncherOptions(bool DoInstall, FString InLauncherRelativeUrl) : bInstall(DoInstall) , LauncherRelativeUrl(InLauncherRelativeUrl)`
- L31 _public function_ `FString GetLauncherUriRequest() const`
- L75 _public member_ `bool bInstall = false;`
- L76 _public member_ `bool bSilent = true;`
- L77 _public member_ `FString Action;`
- L78 _public member_ `FString LauncherRelativeUrl;`

#### class `ILauncherPlatform`  
`class ILauncherPlatform`  
_L82-105_
- L86 _public prototype_ `virtual ~ILauncherPlatform() = default;` — Virtual destructor
- L94 _public prototype_ `virtual bool CanOpenLauncher(bool Install) = 0;` — Determines whether the launcher can be opened. @param Install					Whether to include the possibility of installing the launcher in the check. @return true if the launcher can be opened (or installed).
- L104 _public prototype_ `virtual bool OpenLauncher(const FOpenLauncherOptions& Options) = 0;` — Opens the marketplace user interface. @param Install					Whether to install the marketplace if it is missing. @param LauncherRelativeUrl		A url relative to the launcher which you'd like the launcher to navigate to. Empty defaults to the UE homepage @param CommandLineParams			Optional command to open the launcher with if it is not already open @return true if the marketplace was opened, false if it is not installed or could not be installed/opened.

#### class `FLauncherMisc`  
`class FLauncherMisc`  
_L107-112_
- L111 _public prototype_ `static FString GetEncodedExePath();` — Return url encoded full path of currently running executable.

### `Source/Runtime/Portal/LauncherPlatform/Public/LauncherPlatformModule.h` (Public)


#### class `FLauncherPlatformModule`  
`class FLauncherPlatformModule : public IModuleInterface`  
_L10-26_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule();`
- L14 _public prototype_ `virtual void ShutdownModule();`
- L16 _public function_ `static ILauncherPlatform* Get()`
- L23 _private function_ `virtual ILauncherPlatform* GetSingleton() const`
- L25 _private member_ `ILauncherPlatform* LauncherPlatform;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherPlatform, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherPlatform, Log, All);`
