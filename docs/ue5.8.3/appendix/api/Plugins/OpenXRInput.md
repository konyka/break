# Plugins / OpenXRInput

- module root: `Plugins/Runtime/OpenXR/Source/OpenXRInput`
- headers: 3; symbols: 106
- symbol kinds: class=4, function=5, member=47, prototype=46, struct=4
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, InputDevice, InputEditor, OpenXRHMD, SourceControl, UnrealEd, XRBase
- PublicDependencyModuleNames: EnhancedInput

### `Plugins/Runtime/OpenXR/Source/OpenXRInput/Private/OpenXRInput.h` (Private)


#### class `FOpenXRInputPlugin`  
`class FOpenXRInputPlugin : public IOpenXRInputPlugin`  
_L24-205_
- inherits: `IOpenXRInputPlugin`
- L197 _public prototype_ `FOpenXRInputPlugin();`
- L198 _public prototype_ `virtual ~FOpenXRInputPlugin();`
- L200 _public prototype_ `virtual void StartupModule() override;`
- L201 _public prototype_ `virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;`
- L204 _private member_ `TSharedPtr<FOpenXRInput> InputDevice;`

#### struct `FOpenXRInputPlugin::FOpenXRAction`  
`struct FOpenXRAction`  
_L27-56_
- L29 _public member_ `XrActionSet Set;`
- L30 _public member_ `XrActionType Type;`
- L31 _public member_ `FName Name;`
- L32 _public member_ `XrAction Handle;`
- L35 _public member_ `XrTime NextRepeatTime;` — Legacy Input
- L38 _public member_ `TObjectPtr<const UInputAction> Object;` — Enhanced Input
- L39 _public member_ `TMultiMap<TPair<XrPath, XrPath>, TObjectPtr<UInputTrigger>> Triggers;`
- L40 _public member_ `TMultiMap<TPair<XrPath, XrPath>, TObjectPtr<UInputModifier>> Modifiers;`
- L42 _public prototype_ `FOpenXRAction(XrActionSet InActionSet, XrActionType InActionType, const FName& InName, const FString& InLocalizedName, const TArray<XrPath>& InSubactionPaths, const TObjectPtr<const UInputAction>& InObject, IOpenXRHMD* OpenXRHMD = nullptr);`
- L50 _public prototype_ `FOpenXRAction(XrActionSet InActionSet, XrActionType InActionType, const FName& InName, const FString& InLocalizedName, const TArray<XrPath>& InSubactionPaths, IOpenXRHMD* OpenXRHMD = nullptr);`

#### struct `FOpenXRInputPlugin::FOpenXRActionSet`  
`struct FOpenXRActionSet`  
_L58-78_
- L60 _public member_ `XrActionSet Handle;`
- L61 _public member_ `FName Name;`
- L62 _public member_ `FString LocalizedName;`
- L64 _public member_ `TObjectPtr<const UInputMappingContext> Object;`
- L66 _public prototype_ `FOpenXRActionSet(XrInstance InInstance, const FName& InName, const FString& InLocalizedName, uint32 InPriority, const TObjectPtr<const UInputMappingContext>& InObject, IOpenXRHMD* OpenXRHMD = nullptr);`
- L73 _public prototype_ `FOpenXRActionSet(XrInstance InInstance, const FName& InName, const FString& InLocalizedName, uint32 InPriority, IOpenXRHMD* OpenXRHMD = nullptr);`

#### struct `FOpenXRInputPlugin::FOpenXRController`  
`struct FOpenXRController`  
_L80-97_
- L82 _public member_ `XrActionSet ActionSet;`
- L83 _public member_ `XrPath UserPath;`
- L84 _public member_ `XrAction GripAction;`
- L85 _public member_ `XrAction AimAction;`
- L86 _public member_ `XrAction PalmAction;`
- L87 _public member_ `XrAction VibrationAction;`
- L88 _public member_ `int32 GripDeviceId;`
- L89 _public member_ `int32 AimDeviceId;`
- L90 _public member_ `int32 PalmDeviceId;`
- L92 _public member_ `bool bHapticActive;`
- L94 _public prototype_ `FOpenXRController(XrActionSet InActionSet, XrPath InUserPath, const char* InName);`
- L96 _public prototype_ `void AddTrackedDevices(IOpenXRHMD* HMD);`

#### struct `FOpenXRInputPlugin::FInteractionProfile`  
`struct FInteractionProfile`  
_L99-107_
- L102 _public member_ `bool HasHaptics;`
- L103 _public member_ `XrPath Path;`
- L104 _public member_ `TArray<XrActionSuggestedBinding> Bindings;`
- L106 _public prototype_ `FInteractionProfile(XrPath InProfile, bool InHasHaptics);`

#### class `FOpenXRInputPlugin::FOpenXRInput`  
`class FOpenXRInput : public IOpenXRInputModule, public IInputDevice, public FXRMotionControllerBase, public IHapticDevice, public TSharedFromThis<FOpenXRInput>`  
_L109-195_
- inherits: `IOpenXRInputModule,IInputDevice,FXRMotionControllerBase,IHapticDevice,TSharedFromThis<FOpenXRInput>`
- L112 _public prototype_ `FOpenXRInput(IXRTrackingSystem* InTrackingSystem);`
- L113 _public function_ `virtual ~FOpenXRInput()`
- L116 _public prototype_ `virtual void OnBeginSession() override;` — IOpenXRAdditionalModule overrides
- L117 _public prototype_ `virtual void OnDestroySession() override;`
- L120 _public function_ `virtual void Tick(float DeltaTime) override` — IInputDevice overrides
- L121 _public prototype_ `virtual void SendControllerEvents() override;`
- L122 _public prototype_ `virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;`
- L123 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L124 _public prototype_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L125 _public prototype_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;`
- L126 _public prototype_ `virtual bool SupportsForceFeedback(int32 ControllerId) override;`
- L127 _public prototype_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;`
- L129 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const override;` — IMotionController overrides
- L130 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override;`
- L131 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override;`
- L132 _public prototype_ `virtual bool GetControllerOrientationAndPositionForTime(const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& OutTimeWasUsed, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override;`
- L133 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override;`
- L134 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const override;`
- L135 _public prototype_ `virtual bool SetEnhancedInputUserSettings(TObjectPtr<class UEnhancedInputUserSettings> InputSettings) override;`
- L136 _public prototype_ `virtual bool AttachInputMappingContexts(const TSet<TObjectPtr<UInputMappingContext>>& MappingContexts) override;`
- L139 _public function_ `IHapticDevice* GetHapticDevice() override` — IHapticDevice overrides
- L140 _public prototype_ `virtual void SetHapticFeedbackValues(int32 ControllerId, int32 Hand, const FHapticFeedbackValues& Values) override;`
- L142 _public prototype_ `virtual void GetHapticFrequencyRange(float& MinFrequency, float& MaxFrequency) const override;`
- L143 _public prototype_ `virtual float GetHapticAmplitudeScale() const override;`
- L146 _private member_ `IXRTrackingSystem* TrackingSystem;`
- L147 _private member_ `IOpenXRHMD* OpenXRHMD;`
- L148 _private member_ `XrInstance Instance;`
- L150 _private member_ `TUniquePtr<FOpenXRActionSet> ControllerActionSet;`
- L151 _private member_ `TArray<FOpenXRActionSet> ActionSets;`
- L152 _private member_ `TArray<XrPath> SubactionPaths;`
- L153 _private member_ `TArray<FOpenXRAction> LegacyActions, EnhancedActions;`
- L153 _private member_ `TArray<FOpenXRAction> LegacyActions, EnhancedActions;`
- L154 _private member_ `TMap<EControllerHand, FOpenXRController> Controllers;`
- L155 _private member_ `TMap<FName, EControllerHand> MotionSourceToControllerHandMap;`
- L156 _private member_ `TMap<FString, TArray<FInputKeyOpenXRProperties>> InputsKeysToPropertiesMap;`
- L160 _private member_ `TMap<TStrongObjectPtr<const UInputMappingContext>, uint32> InputMappingContextToPriorityMap;` — Holds Enhanced Input Mapping Contexts pulled from the Enhanced Input Settings and mapped to their priority These will be converted into OpenXR action sets
- L162 _private prototype_ `XrAction GetActionForMotionSource(FName MotionSource) const;`
- L163 _private prototype_ `int32 GetDeviceIDForMotionSource(FName MotionSource) const;`
- L164 _private prototype_ `XrPath GetUserPathForMotionSource(FName MotionSource) const;`
- L165 _private prototype_ `bool IsOpenXRInputSupportedMotionSource(const FName MotionSource) const;`
- L167 _private member_ `bool bActionsAttached;`
- L168 _private member_ `bool bDirectionalBindingSupported;`
- L169 _private member_ `bool bPalmPoseSupported;`
- L170 _private member_ `bool bGripSurfacePoseSupported;`
- L171 _private member_ `bool bActionSetPrioritySupported;`
- L176 _private member_ `float CurrentDeltaTime = 0.0f;` — Buffer for current delta time to get an accurate approximation of how long to play haptics for
- L179 _private member_ `const XrTime InitialButtonRepeatDelay = 2e8;` — Repeat key delays
- L180 _private member_ `const XrTime ButtonRepeatDelay = 1e8;`
- L182 _private prototype_ `bool BuildActions(XrSession Session);`
- L183 _private prototype_ `void SyncActions(XrSession Session);`
- L184 _private prototype_ `void BuildLegacyActions(TMap<FString, FInteractionProfile>& Profiles);`
- L185 _private prototype_ `void BuildEnhancedActions(TMap<FString, FInteractionProfile>& Profiles);`
- L186 _private prototype_ `void DestroyActions();`
- L189 _private prototype_ `template<typename T> int32 SuggestBindings(TMap<FString, FInteractionProfile>& Profiles, FOpenXRAction& Action, const TArray<T>& Mappings);`
- L190 _private prototype_ `bool SuggestBindingForKey(TMap<FString, FInteractionProfile>& Profiles, FOpenXRAction& Action, const FKey& Key, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers);`
- L191 _private prototype_ `bool SuggestBindingForKey(TMap<FString, FInteractionProfile>& Profiles, FOpenXRAction& Action, const FKey& Key);`
- L194 _private member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;` — handler to send all messages to

### `Plugins/Runtime/OpenXR/Source/OpenXRInput/Public/IOpenXRInputPlugin.h` (Public)


#### class `IOpenXRInputPlugin`  
`class IOpenXRInputPlugin : public IInputDeviceModule`  
_L13-38_
- inherits: `IInputDeviceModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IOpenXRInputPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/OpenXR/Source/OpenXRInput/Public/OpenXRInputFunctionLibrary.h` (Public)


#### class `UOpenXRInputFunctionLibrary`  
`class UOpenXRInputFunctionLibrary : public UBlueprintFunctionLibrary`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L24 _private prototype_ `static bool BeginXRSession(const TSet<UInputMappingContext*>& InputMappingContexts);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Begin an XR session with the provided input mapping. This will make the tracking system aware of the actions and bindings that are used for XR motion controllers. Attaching input configs to the session can only be done once, so this is a helper function to attach the input mapping contexts and start the XR session correctly. @param InputMappingContexts		The set of input mapping contexts used for XR @return			False if the input mapping contexts can't be attached to the session, true otherwise
- L28 _private prototype_ `static void EndXRSession();` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")`
