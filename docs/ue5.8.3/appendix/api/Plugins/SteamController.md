# Plugins / SteamController

- module root: `Plugins/Runtime/Steam/SteamController/Source/SteamController`
- headers: 2; symbols: 4
- symbol kinds: class=1, function=2, macro=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, SteamShared
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: InputCore, InputDevice

### `Plugins/Runtime/Steam/SteamController/Source/SteamController/Private/SteamControllerPrivate.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/Steam/SteamController/Source/SteamController/Public/ISteamControllerPlugin.h` (Public)


#### class `ISteamControllerPlugin`  
`class ISteamControllerPlugin : public IInputDeviceModule`  
_L15-40_
- inherits: `IInputDeviceModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L26 _public function_ `static inline ISteamControllerPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_STEAM_CONTROLLER ((PLATFORM_LINUX || PLATFORM_WINDOWS))`
