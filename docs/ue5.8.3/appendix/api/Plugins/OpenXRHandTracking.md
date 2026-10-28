# Plugins / OpenXRHandTracking

- module root: `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking`
- headers: 5; symbols: 120
- symbol kinds: class=5, enum=1, enumerator=8, function=7, member=42, prototype=55, struct=1, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, InputEditor, LiveLinkAnimationCore, LiveLinkInterface, OpenXRHMD, OpenXRInput, Slate, SlateCore, UnrealEd, XRBase
- PublicDependencyModuleNames: InputDevice

### `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking/Private/LiveLinkOpenXRHandTrackingSourceFactory.h` (Private)


#### class `ULiveLinkOpenXRHandTrackingSourceFactory`  
`class ULiveLinkOpenXRHandTrackingSourceFactory : public ULiveLinkSourceFactory`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L15 _public prototype_ `virtual FText GetSourceDisplayName() const;`
- L16 _public prototype_ `virtual FText GetSourceTooltip() const;`
- L18 _public prototype_ `virtual EMenuType GetMenuType() const override;`
- L19 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L21 _public member_ `TSharedPtr<class SLiveLinkOpenXRHandTrackingSourceEditor> ActiveSourceEditor;`

### `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking/Private/OpenXRHandTracking.h` (Private)


#### class `FOpenXRHandTracking`  
`class FOpenXRHandTracking : public IOpenXRExtensionPlugin, public IInputDevice, public FXRMotionControllerBase, public IHandTracker, public ILiveLinkSource`  
_L19-154_
- inherits: `IOpenXRExtensionPlugin,IInputDevice,FXRMotionControllerBase,IHandTracker,ILiveLinkSource`
- desc: OpenXR HandTracking
- L48 _public prototype_ `FOpenXRHandTracking(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);`
- L49 _public prototype_ `virtual ~FOpenXRHandTracking();`
- L52 _public function_ `virtual FString GetDisplayName() override` — IOpenXRExtensionPlugin
- L56 _public prototype_ `virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L57 _public prototype_ `virtual const void* OnGetSystem(XrInstance InInstance, const void* InNext) override;`
- L58 _public prototype_ `virtual const void* OnCreateSession(XrInstance InInstance, XrSystemId InSystem, const void* InNext) override;`
- L59 _public prototype_ `virtual const void* OnBeginSession(XrSession InSession, const void* InNext) override;`
- L60 _public prototype_ `virtual void UpdateDeviceLocations(XrSession InSession, XrTime DisplayTime, XrSpace TrackingSpace) override;`
- L63 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override;` — IMotionController interface
- L64 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override;`
- L65 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const override;`
- L66 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const override;`
- L69 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;` — ILiveLinkSource interface
- L70 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L71 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L72 _public prototype_ `virtual FText GetSourceMachineName() const override;`
- L73 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L74 _public prototype_ `virtual FText GetSourceType() const override;`
- L78 _public prototype_ `virtual void Tick(float DeltaTime) override;` — IInputDevice interface
- L79 _public prototype_ `virtual void SendControllerEvents() override;`
- L80 _public prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L81 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L82 _public function_ `virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override`
- L83 _public function_ `virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override`
- L84 _public function_ `virtual bool SupportsForceFeedback(int32 ControllerId) override`
- L85 _public prototype_ `virtual bool IsGamepadAttached() const override;`
- L88 _public prototype_ `virtual FName GetHandTrackerDeviceTypeName() const override;` — IHandTracker
- L89 _public prototype_ `virtual bool IsHandTrackingStateValid() const override;`
- L90 _public prototype_ `virtual bool GetKeypointState(EControllerHand Hand, EHandKeypoint Keypoint, FTransform& OutTransform, float& OutRadius) const override;`
- L91 _public prototype_ `virtual bool GetAllKeypointStates(EControllerHand Hand, TArray<FVector>& OutPositions, TArray<FQuat>& OutRotations, TArray<float>& OutRadii, bool& OutIsTracked) const override;`
- L94 _private prototype_ `FHandState& GetLeftHandState();`
- L95 _private prototype_ `FHandState& GetRightHandState();`
- L97 _public prototype_ `const FHandState& GetLeftHandState() const;`
- L98 _public prototype_ `const FHandState& GetRightHandState() const;`
- L99 _public prototype_ `bool IsHandTrackingSupportedByDevice() const;`
- L102 _public function_ `static FName ParseEOpenXRHandKeypointEnumName(FName EnumName)` — Parses the enum name removing the prefix
- L110 _private prototype_ `void AddKeys();`
- L111 _private prototype_ `void BuildMotionSourceToKeypointMap();`
- L113 _private prototype_ `void SetupLiveLinkData();`
- L114 _private prototype_ `void UpdateLiveLink();`
- L115 _private prototype_ `void UpdateLiveLinkTransforms(TArray<FTransform>& OutTransforms, const FOpenXRHandTracking::FHandState& HandState);`
- L116 _private prototype_ `void CreateHandTracker(XrSession InSession, XrHandEXT HandEXT, FHandState& HandState);`
- L118 _private member_ `bool bHandTrackingAvailable = false;`
- L120 _private member_ `PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT = nullptr;`
- L121 _private member_ `PFN_xrDestroyHandTrackerEXT xrDestroyHandTrackerEXT = nullptr;`
- L122 _private member_ `PFN_xrLocateHandJointsEXT xrLocateHandJointsEXT = nullptr;`
- L124 _private member_ `class IXRTrackingSystem* XRTrackingSystem = nullptr;`
- L126 _private member_ `TSharedPtr<FGenericApplicationMessageHandler> MessageHandler;`
- L127 _private member_ `int32 DeviceIndex;`
- L129 _private member_ `int32 CurrentHandTrackingDataIndex = 0;`
- L131 _private member_ `TArray<int32> BoneParents;`
- L132 _private member_ `TArray<EHandKeypoint> BoneKeypoints;`
- L133 _private typedef_ `typedef TPair<EHandKeypoint, bool> MotionSourceInfo;` — bool true == left, false == right
- L134 _private member_ `TMap<FName, MotionSourceInfo> MotionSourceToKeypointMap;`
- L135 _private member_ `bool bSupportLegacyControllerMotionSources = true;`
- L137 _private member_ `FHandState HandStates[2];`
- L141 _private member_ `ILiveLinkClient* LiveLinkClient = nullptr;` — The local client to push data updates to
- L143 _private member_ `FGuid LiveLinkSourceGuid;` — Our identifier in LiveLink
- L145 _private member_ `static FLiveLinkSubjectName LiveLinkLeftHandTrackingSubjectName;`
- L146 _private member_ `static FLiveLinkSubjectName LiveLinkRightHandTrackingSubjectName;`
- L147 _private member_ `FLiveLinkSubjectKey LiveLinkLeftHandTrackingSubjectKey;`
- L148 _private member_ `FLiveLinkSubjectKey LiveLinkRightHandTrackingSubjectKey;`
- L149 _private member_ `bool bNewLiveLinkClient = false;`
- L150 _private member_ `FLiveLinkStaticDataStruct LiveLinkSkeletonStaticData;`
- L152 _private member_ `TArray<FTransform> LeftAnimationTransforms;`
- L153 _private member_ `TArray<FTransform> RightAnimationTransforms;`

#### struct `FOpenXRHandTracking::FHandState`  
`struct FHandState : public FNoncopyable`  
_L27-45_
- inherits: `FNoncopyable`
- L29 _public prototype_ `FHandState();`
- L31 _public member_ `XrHandTrackerEXT HandTracker{};`
- L32 _public member_ `XrHandJointLocationEXT JointLocations[XR_HAND_JOINT_COUNT_EXT];`
- L33 _public member_ `XrHandJointVelocityEXT JointVelocities[XR_HAND_JOINT_COUNT_EXT];`
- L34 _public member_ `XrHandJointVelocitiesEXT Velocities{ XR_TYPE_HAND_JOINT_VELOCITIES_EXT };`
- L35 _public member_ `XrHandJointLocationsEXT Locations{ XR_TYPE_HAND_JOINT_LOCATIONS_EXT };`
- L38 _public member_ `FTransform KeypointTransforms[EHandKeypointCount];` — Transforms are cached in Unreal Tracking Space
- L39 _public member_ `float Radii[EHandKeypointCount];`
- L40 _public member_ `bool HasReceivedJointPoses = false;` — true if this hand has ever been tracked, and therefore its poses are valid.
- L41 _public member_ `bool bTracked = false;` — true if tracked right now.
- L43 _public prototype_ `bool GetTransform(EHandKeypoint KeyPoint, FTransform& OutTransform) const;`
- L44 _public prototype_ `const FTransform& GetTransform(EHandKeypoint KeyPoint) const;`

#### Free symbols / members of external scopes

- L156 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogOpenXRHandTracking, Display, All);`

### `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking/Private/OpenXRHandTrackingLiveLinkRemapAsset.h` (Private)


#### enum `EQuatSwizzleAxisB`  
`enum class EQuatSwizzleAxisB : uint8`  
_L10-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `X UMETA(DisplayName = "X")`
- L13 _public enumerator_ `Y UMETA(DisplayName = "Y")`
- L14 _public enumerator_ `Z UMETA(DisplayName = "Z")`
- L15 _public enumerator_ `W UMETA(DisplayName = "W")`
- L16 _public enumerator_ `MinusX UMETA(DisplayName = "-X")`
- L17 _public enumerator_ `MinusY UMETA(DisplayName = "-Y")`
- L18 _public enumerator_ `MinusZ UMETA(DisplayName = "-Z")`
- L19 _public enumerator_ `MinusW UMETA(DisplayName = "-W")`

#### class `UOpenXRHandTrackingLiveLinkRemapAsset`  
`class UOpenXRHandTrackingLiveLinkRemapAsset : public ULiveLinkRetargetAsset`  
_L28-65_
- reflection: `UCLASS(Blueprintable)`
- inherits: `ULiveLinkRetargetAsset`
- desc: OpenXR HandTracking LiveLink remapping asset
- L34 _public prototype_ `virtual void BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose) override;`
- L38 _public member_ `bool bHasMetacarpals = true;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — If true, remap the full human hand skeleton including metacarpals
- L42 _public member_ `bool bRetargetRotationOnly = false;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — Only apply the orientation to each bone
- L46 _public member_ `EQuatSwizzleAxisB SwizzleX = EQuatSwizzleAxisB::X;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — Reorient the skeleton (swizzle the quaternion) to adjust for base skeleton and incoming skeleton differences
- L48 _public member_ `EQuatSwizzleAxisB SwizzleY = EQuatSwizzleAxisB::Y;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L50 _public member_ `EQuatSwizzleAxisB SwizzleZ = EQuatSwizzleAxisB::Z;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L52 _public member_ `EQuatSwizzleAxisB SwizzleW = EQuatSwizzleAxisB::W;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")`
- L55 _public member_ `TMap<FName, FName> HandTrackingBoneNameMap;` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L58 _public prototype_ `virtual void PostInitProperties() override;`
- L62 _private prototype_ `FName GetRemappedBoneName(FName BoneName) const;`
- L64 _private prototype_ `FTransform GetRetargetedTransform(const FLiveLinkAnimationFrameData* InFrameData, int TransformIndex) const;`

#### Free symbols / members of external scopes

- L22 _prototype_ `int Sign(const EQuatSwizzleAxisB& QuatSwizzleAxis);`

### `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking/Public/IOpenXRHandTrackingModule.h` (Public)


#### class `IOpenXRHandTrackingModule`  
`class IOpenXRHandTrackingModule : public IInputDeviceModule`  
_L16-65_
- inherits: `IInputDeviceModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L26 _public function_ `static inline IOpenXRHandTrackingModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L47 _public prototype_ `virtual TSharedPtr<IInputDevice> GetInputDevice() = 0;` — Returns the Input Device associated with this InputDeviceModule. @return Shared pointer to the Input Device.
- L54 _public prototype_ `virtual TSharedPtr<class ILiveLinkSource> GetLiveLinkSource() = 0;` — Returns the LiveLinkSource associated with this OpenXRHandTrackingPlugin. @return Shared pointer to the Input Device.
- L61 _public prototype_ `virtual bool IsLiveLinkSourceValid() const = 0;` — Checks if the LiveLinkSource as been created. @return True if the LiveLinkSource has been created with GetLiveLinkSource or AddLiveLinkSource
- L63 _public prototype_ `virtual void AddLiveLinkSource() = 0;`
- L64 _public prototype_ `virtual void RemoveLiveLinkSource() = 0;`

### `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking/Public/OpenXRHandTrackingSettings.h` (Public)


#### class `UOpenXRHandTrackingSettings`  
`class UOpenXRHandTrackingSettings : public UObject`  
_L13-25_
- reflection: `UCLASS(config = Input, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the OpenXR Input plugin.
- L20 _public member_ `bool bUseMoreSpecificMotionSourceNames = false;` — `UPROPERTY(config, EditAnywhere, Category = "Motion Sources")` — If false (the default) the motion sources for hand tracking will be of the form '[Left|Right][Keypoint]'.  If true they will be of the form 'HandTracking[Left|Right][Keypoint]'.  True is reccomended to avoid collisions between motion sources from different device types.
- L24 _public member_ `bool bSupportLegacyControllerMotionSources = true;` — `UPROPERTY(config, EditAnywhere, Category = "Motion Sources")` — If true hand tracking supports the 'Left' and 'Right' legacy motion sources.  If false it does not.  False is reccomended unless you need legacy compatibility in an older unreal projects.
