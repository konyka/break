# Plugins / SecuritySandbox

- module root: `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox`
- headers: 6; symbols: 41
- symbol kinds: class=5, delegate=1, function=9, member=10, prototype=13, typedef=3
- PrivateDependencyModuleNames: DeveloperSettings
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine

### `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Private/GenericPlatform/GenericPlatformSecuritySandbox.h` (Private)


#### class `FGenericPlatformSecuritySandbox`  
`class FGenericPlatformSecuritySandbox : public ISecuritySandbox, public TSharedFromThis<FGenericPlatformSecuritySandbox>`  
_L8-39_
- inherits: `ISecuritySandbox,TSharedFromThis<FGenericPlatformSecuritySandbox>`
- L11 _public function_ `virtual ~FGenericPlatformSecuritySandbox()`
- L12 _public function_ `FGenericPlatformSecuritySandbox()`
- L15 _public prototype_ `virtual void Init();` — Initialize the sandbox, will be called exactly once.
- L18 _public prototype_ `virtual void RestrictSelf() override final;` — Public interface function from ISecuritySandbox that user code can call without validation.
- L21 _public prototype_ `virtual bool IsEnabled() override final;` — True if restriction can be attempted. If false, RestrictSelf does nothing.
- L25 _protected function_ `virtual void PlatformRestrictSelf()` — Implementation function for derived platform classes which we guarantee will be called at most once with configuration options taken into consideration.
- L29 _private member_ `bool bIsSandboxEnabled = false;` — True if restriction can be attempted. If false, RestrictSelf does nothing.
- L32 _private member_ `bool bHasRestrictedSelf = false;` — True if RestrictSelf has run. This doesn't convey success or failure, just that it was attempted.
- L35 _private prototype_ `bool InitIsSandboxEnabled();` — Set the initial value of bIsSandboxEnabled based on config and command line.
- L38 _private prototype_ `void OnEngineInitComplete();` — Used for automatic RestrictSelf if configured in the plugin's settings.

### `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Private/PlatformSecuritySandbox.h` (Private)


#### Free symbols / members of external scopes

- L6 _typedef_ `typedef FWindowsPlatformSecuritySandbox FPlatformSecuritySandbox;`
- L9 _typedef_ `typedef FGenericPlatformSecuritySandbox FPlatformSecuritySandbox;`

### `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Private/Windows/WindowsPlatformSecuritySandbox.h` (Private)


#### class `FWindowsPlatformSecuritySandbox`  
`class FWindowsPlatformSecuritySandbox : public FGenericPlatformSecuritySandbox`  
_L6-22_
- inherits: `FGenericPlatformSecuritySandbox`
- L9 _public function_ `virtual ~FWindowsPlatformSecuritySandbox()`
- L10 _public prototype_ `virtual void PlatformRestrictSelf() override;`
- L13 _private prototype_ `void SetLowIntegrityLevel();`
- L14 _private prototype_ `void SetProcessMitigations();`
- L15 _private prototype_ `void ApplyJobRestrictions();`
- L17 _private prototype_ `void CustomHandlerForURL(const FString& URL, FString* ErrorMsg);`
- L19 _private typedef_ `typedef FGenericPlatformSecuritySandbox Super;`
- L21 _private member_ `bool bNeedsCustomHandlerForURL = false;`

### `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Public/ISecuritySandbox.h` (Public)


#### class `ISecuritySandbox`  
`class ISecuritySandbox`  
_L8-33_
- L23 _public prototype_ `virtual void RestrictSelf() = 0;` — Permanently restrict this process. The exact restrictions applied depend on operating system and configuration. Your game can initialize with normal operating system access then call this function before activating online features or loading user generated content to reduce risks. USecuritySandboxSettings can also be configured to automatically apply restrictions without needing to call this function. If SecuritySandbox is disabled by config or command line parameter then this function will do nothing. NOTE: State initialized/acquired prior to this call may allow bypassing restrictions, e.g. on Windows file handles that were opened beforehand and not closed can still be used.
- L32 _public prototype_ `virtual bool IsEnabled() = 0;` — Check if SecuritySandbox as a whole is enabled. If this returns false then it may be disabled due to build configuration or command line override. Individual components may still be disabled in USecuritySandboxSettings. @return True if SecuritySandbox is enabled, otherwise false

#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSecuritySandbox, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSecuritySandbox, Log, All);`

### `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Public/ISecuritySandboxModule.h` (Public)


#### class `ISecuritySandboxModule`  
`class ISecuritySandboxModule : public IModuleInterface, public ISecuritySandbox`  
_L11-52_
- inherits: `IModuleInterface,ISecuritySandbox`
- desc: Provides features to help minimize the operating system permissions your game client runs with and therefore minimize the impact to players if an attacker takes control of it through a vulnerability. See ISecuritySandbox for the API.
- L20 _public function_ `static inline ISecuritySandboxModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L48 _public function_ `static inline bool IsSandboxEnabled()` — Helper for calling ISecuritySandbox::IsEnabled. See that function for details. @return True if SecuritySandbox is enabled, otherwise false.

### `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Public/SecuritySandboxSettings.h` (Public)


#### class `USecuritySandboxSettings`  
`class USecuritySandboxSettings : public UDeveloperSettings`  
_L11-47_
- reflection: `UCLASS(config = Engine, defaultconfig, meta=(DisplayName="Security Sandbox"))`
- inherits: `UDeveloperSettings`
- desc: Implements settings for the Security Sandbox plugin. These are visible in the Project Settings section of the editor.
- L16 _public function_ `USecuritySandboxSettings()`
- L18 _public function_ `virtual FName GetCategoryName() const override`
- L22 _public member_ `bool bIsEnabledByDefault = true;` — `UPROPERTY(EditAnywhere, config, Category = General)` — If true, no command line arguments are needed to activate the sandbox features. If false, -WithSecuritySandbox must be passed to activate them.
- L26 _public member_ `bool bAutoRestrictSelf = true;` — `UPROPERTY(EditAnywhere, config, Category = General)` — If true, the game will automatically restrict itself after engine initialization completes. Otherwise you must explicitly call ISecuritySandboxModule::RestrictSelf at an appropriate time.
- L30 _public member_ `bool bAllowSandboxInEditor = false;` — `UPROPERTY(EditAnywhere, config, Category = General)` — If true, the sandbox will attempt to operate in editor builds. This may be useful for debugging an uncooked game build but many features of the editor itself will not work. You must restart the editor instance for changes to take effect.
- L34 _public member_ `bool bUseLowIntegrityLevel = true;` — `UPROPERTY(EditAnywhere, config, Category = Windows)` — If true, the game will be reduced to low integrity level after restricting itself. This means most files and registry keys will become read only in addition to other limitations. See Microsoft documentation for details.
- L38 _public member_ `bool bDisallowLowIntegrityLibraries = true;` — `UPROPERTY(EditAnywhere, config, Category = Windows)` — If true, the game will be prevented from loading low integrity level libraries after restricting itself. This blocks loading of any executable files written to disk by a low integrity level process.
- L42 _public member_ `bool bDisallowChildProcesses = false;` — `UPROPERTY(EditAnywhere, config, Category = Windows)` — If true, the game will be prevented from spawning child processes after restricting itself. Currently not compatible with Unreal's default crash reporter.
- L46 _public member_ `bool bDisallowSystemOperations = false;` — `UPROPERTY(EditAnywhere, config, Category = Windows)` — If true, the game will be prevented from performing system operations that are usually unnecessary like logging the user out of Windows after restricting itself. This unfortunately also blocks clipboard paste from other applications.
