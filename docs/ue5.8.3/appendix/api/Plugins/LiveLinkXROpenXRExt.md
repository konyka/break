# Plugins / LiveLinkXROpenXRExt

- module root: `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXROpenXRExt`
- headers: 2; symbols: 31
- symbol kinds: class=2, delegate=1, function=4, member=8, namespace=1, prototype=14, typedef=1
- PrivateDependencyModuleNames: CoreUObject, Engine, HeadMountedDisplay, InputCore, OpenXRHMD
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXROpenXRExt/Internal/LiveLinkXROpenXRExt.h` (Internal)


#### class `FLiveLinkXROpenXRExtension`  
`class FLiveLinkXROpenXRExtension : public IOpenXRExtensionPlugin , public TSharedFromThis<FLiveLinkXROpenXRExtension>`  
_L17-61_
- inherits: `IOpenXRExtensionPlugin,TSharedFromThis<FLiveLinkXROpenXRExtension>`
- L22 _public prototype_ `FLiveLinkXROpenXRExtension();`
- L23 _public prototype_ `virtual ~FLiveLinkXROpenXRExtension();`
- L25 _public function_ `bool IsSupported() const`
- L26 _public prototype_ `void GetSubjectPoses(TMap<FName, FTransform>& OutPoseMap);`
- L29 _public function_ `virtual FString GetDisplayName() override`
- L34 _public prototype_ `virtual bool GetOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L35 _public prototype_ `virtual void PostCreateInstance(XrInstance InInstance) override;`
- L36 _public prototype_ `virtual void PostCreateSession(XrSession InSession) override;`
- L37 _public prototype_ `virtual void OnDestroySession(XrSession InSession) override;`
- L41 _private prototype_ `XrSpace GetReferenceSpace() const;`
- L42 _private prototype_ `XrResult GetXrTimeNow(XrTime& OutXrTime) const;`
- L44 _private prototype_ `bool LocateSpace(XrSpace InSpace, XrSpace InRefSpace, XrTime InTime, FTransform& OutTransform);`
- L47 _private typedef_ `typedef XrResult(XRAPI_PTR* PFN_xrConvertWin32PerformanceCounterToTimeKHR)(XrInstance Instance, const Windows::LARGE_INTEGER* PerformanceCounter, XrTime* Time);`
- L48 _private member_ `PFN_xrConvertWin32PerformanceCounterToTimeKHR PfnXrConvertWin32PerformanceCounterToTimeKHR = nullptr;`
- L52 _private member_ `bool bIsSupported = false;`
- L54 _private member_ `XrInstance Instance = XR_NULL_HANDLE;`
- L56 _private member_ `XrReferenceSpaceType TrackingSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;`
- L57 _private member_ `XrSpace LocalSpace = XR_NULL_HANDLE;`
- L58 _private member_ `XrSpace StageSpace = XR_NULL_HANDLE;`
- L60 _private member_ `double WorldToMetersScale;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Windows`

### `Plugins/VirtualProduction/LiveLinkXR/Source/LiveLinkXROpenXRExt/Internal/LiveLinkXROpenXRExtModule.h` (Internal)


#### class `FLiveLinkXROpenXRExtModule`  
`class FLiveLinkXROpenXRExtModule : public IModuleInterface`  
_L15-47_
- inherits: `IModuleInterface`
- L24 _public function_ `static inline FLiveLinkXROpenXRExtModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L39 _public prototype_ `TSharedPtr<FLiveLinkXROpenXRExtension> GetExtension();`
- L42 _private prototype_ `virtual void StartupModule() override;`
- L43 _private prototype_ `virtual void ShutdownModule() override;`
- L46 _private member_ `TSharedPtr<FLiveLinkXROpenXRExtension> OpenXrExt;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkXROpenXRExt, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkXROpenXRExt, Log, All);`
