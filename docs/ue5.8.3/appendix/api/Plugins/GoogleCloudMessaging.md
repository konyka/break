# Plugins / GoogleCloudMessaging

- module root: `Plugins/Runtime/GoogleCloudMessaging/Source/GoogleCloudMessaging`
- headers: 1; symbols: 7
- symbol kinds: class=1, delegate=1, function=2, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Launch, UnrealEd
- PublicIncludePathModuleNames: Launch

### `Plugins/Runtime/GoogleCloudMessaging/Source/GoogleCloudMessaging/Public/GoogleCloudMessaging.h` (Public)


#### class `IGoogleCloudMessagingModuleInterface`  
`class IGoogleCloudMessagingModuleInterface : public IModuleInterface`  
_L14-43_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IGoogleCloudMessagingModuleInterface& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L41 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L42 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGoogleCloudMessaging, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGoogleCloudMessaging, Log, All);`
