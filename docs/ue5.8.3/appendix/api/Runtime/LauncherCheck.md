# Runtime / LauncherCheck

- module root: `Source/Runtime/Portal/LauncherCheck`
- headers: 1; symbols: 12
- symbol kinds: class=1, delegate=1, enum=1, enumerator=4, function=1, prototype=4
- PublicDependencyModuleNames: Core, HTTP, LauncherPlatform

### `Source/Runtime/Portal/LauncherCheck/Public/ILauncherCheckModule.h` (Public)


#### enum `ELauncherAction`  
`enum class ELauncherAction : uint32`  
_L13-23_
- desc: Launch options when starting the Launcher
- L16 _public enumerator_ `AppLaunch` — Launch the App after the launcher is started
- L18 _public enumerator_ `AppUpdateCheck` — Check for an available update to the App after the launcher is started
- L20 _public enumerator_ `AppInstaller` — Modify the Apps installation - app has to support SD and be installed
- L22 _public enumerator_ `AppVerifyInstallation` — Notify the launcher that installation corruption was detected and that it should verify

#### class `ILauncherCheckModule`  
`class ILauncherCheckModule : public IModuleInterface`  
_L28-64_
- inherits: `IModuleInterface`
- desc: Interface for the Launcher checking system
- L39 _public function_ `static inline ILauncherCheckModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L49 _public prototype_ `virtual bool WasRanFromLauncher() const = 0;` — Checks to see if the current app was ran from the Launcher @return true, if it was
- L58 _public prototype_ `virtual bool RunLauncher(ELauncherAction Action, FString Payload = FString()) const = 0;` — Opens the launcher, appending our identifier to the cmdline @param Action - The Action we want the launcher to take @param Payload - (Optional) additional information we want to supply to the action uri @return true, if it was successful
- L63 _public prototype_ `virtual ~ILauncherCheckModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherCheck, Display, All);` — Log categories
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLauncherCheck, Display, All);` — Log categories
