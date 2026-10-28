# Plugins / VirtualScoutingOpenXR

- module root: `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScoutingOpenXR`
- headers: 2; symbols: 29
- symbol kinds: class=2, function=4, member=9, prototype=14
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, OpenXRHMD, VREditor

### `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScoutingOpenXR/Internal/VirtualScoutingOpenXR.h` (Internal)


#### class `FVirtualScoutingOpenXRExtension`  
`class FVirtualScoutingOpenXRExtension : public IOpenXRExtensionPlugin , public TSharedFromThis<FVirtualScoutingOpenXRExtension>`  
_L14-64_
- inherits: `IOpenXRExtensionPlugin,TSharedFromThis<FVirtualScoutingOpenXRExtension>`
- L19 _public prototype_ `FVirtualScoutingOpenXRExtension();`
- L20 _public prototype_ `virtual ~FVirtualScoutingOpenXRExtension();`
- L23 _public function_ `virtual FString GetDisplayName() override`
- L28 _public prototype_ `virtual bool GetOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L29 _public prototype_ `virtual void OnEvent(XrSession InSession, const XrEventDataBaseHeader* InHeader) override;`
- L30 _public prototype_ `virtual void PostCreateInstance(XrInstance InInstance) override;`
- L31 _public prototype_ `virtual void PostCreateSession(XrSession InSession) override;`
- L32 _public prototype_ `virtual void PostSyncActions(XrSession InSession) override;`
- L35 _public function_ `TFuture<FName>& GetHmdDeviceTypeFuture()`
- L38 _private prototype_ `void OnVREditingModeEnter();`
- L39 _private prototype_ `void OnVREditingModeExit();`
- L41 _private prototype_ `TOptional<FName> TryGetHmdDeviceType();`
- L42 _private prototype_ `void TryFulfillDeviceTypePromise();`
- L45 _private member_ `FDelegateHandle InitCompleteDelegate;`
- L47 _private member_ `XrDebugUtilsMessengerEXT Messenger = XR_NULL_HANDLE;`
- L49 _private member_ `XrInstance Instance = XR_NULL_HANDLE;`
- L50 _private member_ `XrSession Session = XR_NULL_HANDLE;`
- L51 _private member_ `XrActionSet ActionSet = XR_NULL_HANDLE;`
- L53 _private member_ `bool bIsVrEditingModeActive = false;`
- L55 _private member_ `TPromise<FName> DeviceTypePromise;`
- L56 _private member_ `TFuture<FName> DeviceTypeFuture;`
- L59 _private prototype_ `static XrBool32 XRAPI_CALL XrDebugUtilsMessengerCallback_Trampoline( XrDebugUtilsMessageSeverityFlagsEXT InMessageSeverity, XrDebugUtilsMessageTypeFlagsEXT InMessageTypes, const XrDebugUtilsMessengerCallbackDataEXT* InCallbackData, void* InUserData);`

### `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScoutingOpenXR/Internal/VirtualScoutingOpenXRModule.h` (Internal)


#### class `FVirtualScoutingOpenXRModule`  
`class FVirtualScoutingOpenXRModule : public IModuleInterface`  
_L11-33_
- inherits: `IModuleInterface`
- L20 _public function_ `static FVirtualScoutingOpenXRModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `const TSharedPtr<FVirtualScoutingOpenXRExtension>& GetOpenXRExt()`
- L32 _private member_ `TSharedPtr<FVirtualScoutingOpenXRExtension> OpenXRExt;`
