# Plugins / OpenXRViveTracker

- module root: `Plugins/Runtime/OpenXRViveTracker/Source/OpenXRViveTracker`
- headers: 2; symbols: 55
- symbol kinds: class=2, function=5, member=15, prototype=32, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, OpenXRHMD, OpenXRInput, Slate, SlateCore, UnrealEd, XRBase
- PrivateIncludePathModuleNames: OpenXR
- PublicDependencyModuleNames: InputDevice

### `Plugins/Runtime/OpenXRViveTracker/Source/OpenXRViveTracker/Private/OpenXRViveTracker.h` (Private)


#### class `FOpenXRViveTracker`  
`class FOpenXRViveTracker : public IOpenXRExtensionPlugin, public IInputDevice, public FXRMotionControllerBase, public IHapticDevice`  
_L19-103_
- inherits: `IOpenXRExtensionPlugin,IInputDevice,FXRMotionControllerBase,IHapticDevice`
- desc: OpenXR ViveTracker
- L41 _public prototype_ `FOpenXRViveTracker(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);`
- L42 _public prototype_ `virtual ~FOpenXRViveTracker();`
- L45 _public function_ `virtual FString GetDisplayName() override` — IOpenXRExtensionPlugin
- L49 _public prototype_ `virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L50 _public prototype_ `virtual void PostCreateInstance(XrInstance InInstance) override;`
- L51 _public prototype_ `virtual const void* OnCreateSession(XrInstance InInstance, XrSystemId InSystem, const void* InNext) override;`
- L52 _public prototype_ `virtual void OnDestroySession(XrSession InSession) override;`
- L53 _public prototype_ `virtual void AttachActionSets(TSet<XrActionSet>& OutActionSets) override;`
- L54 _public prototype_ `virtual void GetActiveActionSetsForSync(TArray<XrActiveActionSet>& OutActiveSets) override;`
- L57 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override;` — IMotionController interface
- L58 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override;`
- L59 _public prototype_ `virtual bool GetControllerOrientationAndPositionForTime(const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& OutTimeWasUsed, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override;`
- L60 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override;`
- L61 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const override;`
- L62 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const override;`
- L65 _public prototype_ `virtual void Tick(float DeltaTime) override;` — IInputDevice interface
- L66 _public prototype_ `virtual void SendControllerEvents() override;`
- L67 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L68 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L69 _public prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L70 _public prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;`
- L71 _public function_ `virtual bool SupportsForceFeedback(int32 ControllerId) override`
- L72 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L75 _public function_ `IHapticDevice* GetHapticDevice() override` — IHapticDevice overrides
- L76 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L78 _public prototype_ `virtual void GetHapticFrequencyRange(float& MinFrequency, float& MaxFrequency) const override;`
- L79 _public prototype_ `virtual float GetHapticAmplitudeScale() const override;`
- L82 _private prototype_ `void AddKeys();`
- L84 _private prototype_ `XrAction GetActionForMotionSource(FName MotionSource) const;`
- L85 _private prototype_ `int32 GetDeviceIDForMotionSource(FName MotionSource) const;`
- L86 _private prototype_ `XrPath GetRolePathForMotionSource(FName MotionSource) const;`
- L88 _private member_ `bool bActionsAttached = false;`
- L90 _private member_ `PFN_xrEnumerateViveTrackerPathsHTCX xrEnumerateViveTrackerPathsHTCX = nullptr;`
- L92 _private member_ `class IXRTrackingSystem* XRTrackingSystem = nullptr;`
- L93 _private member_ `class IOpenXRHMD* OpenXRHMD = nullptr;`
- L95 _private member_ `TSharedPtr<FGenericApplicationMessageHandler> MessageHandler;`
- L96 _private member_ `int32 DeviceIndex;`
- L98 _private member_ `XrActionSet TrackerActionSet;`
- L99 _private member_ `TMap<EControllerHand, FViveTracker> Trackers;`
- L100 _private member_ `TArray<FViveTracker> UnassignedTrackers;`
- L102 _private member_ `TMap<FName, EControllerHand> MotionSourceToEControllerHandMap;`

#### struct `FOpenXRViveTracker::FViveTracker`  
`struct FViveTracker`  
_L26-38_
- L28 _public member_ `XrActionSet ActionSet;`
- L29 _public member_ `FOpenXRPath RolePath;`
- L30 _public member_ `XrAction GripAction;`
- L31 _public member_ `XrAction VibrationAction;`
- L32 _public member_ `int32 DeviceId;`
- L34 _public prototype_ `FViveTracker(XrActionSet InActionSet, FOpenXRPath InRolePath, const char* InName);`
- L36 _public prototype_ `void AddTrackedDevices(class IOpenXRHMD* HMD);`
- L37 _public prototype_ `void GetSuggestedBindings(TArray<XrActionSuggestedBinding>& OutSuggestedBindings);`

### `Plugins/Runtime/OpenXRViveTracker/Source/OpenXRViveTracker/Public/IOpenXRViveTrackerModule.h` (Public)


#### class `IOpenXRViveTrackerModule`  
`class IOpenXRViveTrackerModule : public IInputDeviceModule`  
_L16-48_
- inherits: `IInputDeviceModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L26 _public function_ `static inline IOpenXRViveTrackerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L47 _public prototype_ `virtual TSharedPtr<IInputDevice> GetInputDevice() = 0;` — Returns the Input Device associated with this InputDeviceModule. @return Shared pointer to the Input Device.
