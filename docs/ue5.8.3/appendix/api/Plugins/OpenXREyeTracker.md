# Plugins / OpenXREyeTracker

- module root: `Plugins/Runtime/OpenXREyeTracker/Source/OpenXREyeTracker`
- headers: 2; symbols: 42
- symbol kinds: class=3, function=5, member=11, prototype=23
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, InputDevice, OpenXRHMD, OpenXRInput, UnrealEd, XRBase
- PublicDependencyModuleNames: EyeTracker

### `Plugins/Runtime/OpenXREyeTracker/Source/OpenXREyeTracker/Private/OpenXREyeTracker.h` (Private)


#### class `FOpenXREyeTracker`  
`class FOpenXREyeTracker : public IEyeTracker, public IOpenXRExtensionPlugin`  
_L13-61_
- inherits: `IEyeTracker,IOpenXRExtensionPlugin`
- L16 _public prototype_ `FOpenXREyeTracker();`
- L17 _public prototype_ `virtual ~FOpenXREyeTracker();`
- L22 _public prototype_ `void Destroy();` — /
- L23 _public function_ `virtual void SetEyeTrackedPlayer(APlayerController* PlayerController) override`
- L24 _public prototype_ `virtual bool GetEyeTrackerGazeData(FEyeTrackerGazeData& OutGazeData) const override;`
- L25 _public prototype_ `virtual bool GetEyeTrackerStereoGazeData(FEyeTrackerStereoGazeData& OutGazeData) const override;`
- L26 _public prototype_ `virtual EEyeTrackerStatus GetEyeTrackerStatus() const override;`
- L27 _public prototype_ `virtual bool IsStereoGazeDataAvailable() const override;`
- L33 _public function_ `virtual FString GetDisplayName() override`
- L37 _public prototype_ `virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L38 _public prototype_ `virtual void PostCreateInstance(XrInstance InInstance) override;`
- L39 _public prototype_ `virtual bool GetInteractionProfiles(XrInstance InInstance, TArray<FString>& OutKeyPrefixes, TArray<XrPath>& OutPaths, TArray<bool>& OutHasHaptics) override;`
- L40 _public prototype_ `virtual void AttachActionSets(TSet<XrActionSet>& OutActionSets) override;`
- L41 _public prototype_ `virtual const void* OnBeginSession(XrSession InSession, const void* InNext) override;`
- L42 _public prototype_ `virtual void OnDestroySession(XrSession InSession) override;`
- L43 _public prototype_ `virtual void GetActiveActionSetsForSync(TArray<XrActiveActionSet>& OutActiveSets) override;`
- L44 _public prototype_ `virtual void PostSyncActions(XrSession InSession) override;`
- L45 _public prototype_ `virtual void UpdateDeviceLocations(XrSession InSession, XrTime DisplayTime, XrSpace TrackingSpace) override;`
- L47 _public prototype_ `void DrawDebug(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L50 _private member_ `class IXRTrackingSystem* XRTrackingSystem = nullptr;`
- L51 _private member_ `XrInstance Instance = XR_NULL_HANDLE;`
- L52 _private member_ `bool bSessionStarted = false;`
- L53 _private member_ `XrActionsSyncInfo SyncInfo{ XR_TYPE_ACTIONS_SYNC_INFO };`
- L54 _private member_ `XrAction EyeTrackerAction = XR_NULL_HANDLE;`
- L55 _private member_ `XrActionSet EyeTrackerActionSet = XR_NULL_HANDLE;`
- L56 _private member_ `XrSpace GazeActionSpace = XR_NULL_HANDLE;`
- L57 _private member_ `XrActionStatePose ActionStatePose{ XR_TYPE_ACTION_STATE_POSE };`
- L60 _private member_ `XrSpaceLocation EyeTrackerSpaceLocation{ XR_TYPE_SPACE_LOCATION };` — EyeTracker cached data

#### class `FOpenXREyeTrackerModule`  
`class FOpenXREyeTrackerModule : public IOpenXREyeTrackerModule`  
_L63-85_
- inherits: `IOpenXREyeTrackerModule`
- L69 _public prototype_ `FOpenXREyeTrackerModule();`
- L70 _public prototype_ `virtual void StartupModule() override;`
- L71 _public prototype_ `virtual void ShutdownModule() override;`
- L72 _public prototype_ `virtual TSharedPtr< class IEyeTracker, ESPMode::ThreadSafe > CreateEyeTracker() override;`
- L78 _public prototype_ `virtual bool IsEyeTrackerConnected() const override;`
- L81 _private member_ `TSharedPtr<FOpenXREyeTracker, ESPMode::ThreadSafe> EyeTracker;`
- L82 _private member_ `FDelegateHandle OnDrawDebugHandle;`
- L84 _private prototype_ `void OnDrawDebug(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`

### `Plugins/Runtime/OpenXREyeTracker/Source/OpenXREyeTracker/Public/IOpenXREyeTrackerModule.h` (Public)


#### class `IOpenXREyeTrackerModule`  
`class IOpenXREyeTrackerModule : public IEyeTrackerModule`  
_L13-43_
- inherits: `IEyeTrackerModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L23 _public function_ `static inline IOpenXREyeTrackerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L39 _public function_ `virtual FString GetModuleKeyName() const override`
