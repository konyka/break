# Plugins / WebBrowserNativeProxy

- module root: `Plugins/Runtime/WebBrowserNativeProxy/Source/WebBrowserNativeProxy`
- headers: 1; symbols: 8
- symbol kinds: class=1, delegate=1, function=3, prototype=3
- PrivateDependencyModuleNames: Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, WebBrowser

### `Plugins/Runtime/WebBrowserNativeProxy/Source/WebBrowserNativeProxy/Public/WebBrowserNativeProxyModule.h` (Public)


#### class `IWebBrowserNativeProxyModule`  
`class IWebBrowserNativeProxyModule : public IModuleInterface`  
_L12-61_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L20 _public function_ `static inline const TCHAR* GetModuleName()` — Name of this module
- L31 _public function_ `static inline IWebBrowserNativeProxyModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L54 _public prototype_ `virtual TSharedPtr<IWebBrowserWindow> GetBrowser(bool bCreate=false) = 0;` — Get the single browser window associated with the module @param bCreate if true then create the window if not already created @return ptr to the browser window
- L59 _public prototype_ `DECLARE_EVENT_OneParam(IWebBrowserNativeProxyModule, FOnBrowserAvailableEvent, const TSharedRef<IWebBrowserWindow>& );` — Callback for when the browser window has been created and is available
- L60 _public prototype_ `virtual FOnBrowserAvailableEvent& OnBrowserAvailable() = 0;`

#### Free symbols / members of external scopes

- L59 _delegate_ `DECLARE_EVENT_OneParam(IWebBrowserNativeProxyModule, FOnBrowserAvailableEvent, const TSharedRef<IWebBrowserWindow>& );` — Callback for when the browser window has been created and is available
