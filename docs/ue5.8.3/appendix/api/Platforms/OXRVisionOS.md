# Platforms / OXRVisionOS

- module root: `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS`
- headers: 15; symbols: 499
- symbol kinds: class=10, delegate=1, enum=7, enumerator=29, function=70, macro=5, member=159, namespace=5, prototype=179, struct=21, typedef=11, union=1, variable=1
- PrivateIncludePathModuleNames: OpenXRHMD
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MetalRHI, OXRVisionOSSettings, OpenXR, OpenXRHMD, RHI, RenderCore

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Internal/OXRVisionOS_openxr_platform.h` (Internal)


#### enum `XrOXRVisionOSStructureTypeEPIC`  
`typedef enum XrOXRVisionOSStructureTypeEPIC`  
_L15-18_
- L16 _public enumerator_ `XR_TYPE_GRAPHICS_BINDING_OXRVISIONOS_EPIC = XR_TYPE_OXRVISIONOS_EPIC + 0`
- L17 _public enumerator_ `XR_TYPE_SWAPCHAIN_IMAGE_OXRVISIONOS_EPIC = XR_TYPE_OXRVISIONOS_EPIC + 1`

#### struct `XrGraphicsBindingOXRVisionOSEPIC`  
`typedef struct XrGraphicsBindingOXRVisionOSEPIC`  
_L20-24_
- L21 _public member_ `XrStructureType type;`
- L22 _public member_ `const void* XR_MAY_ALIAS next;`

#### struct `XrSwapchainImageOXRVisionOS`  
`typedef struct XrSwapchainImageOXRVisionOS`  
_L26-30_
- L27 _public member_ `XrStructureType type;`
- L28 _public member_ `void* XR_MAY_ALIAS next;`
- L29 _public member_ `FTextureRHIRef image;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define XR_TYPE_OXRVISIONOS_EPIC 1000059100` — This number is in a block that is unused by openxr, and that seemed unlikely to be used soon based on the patterns of usage. But if it ever was used by openxr we would have to change it.
- L18 _typedef_ `XR_TYPE_GRAPHICS_BINDING_OXRVISIONOS_EPIC = XR_TYPE_OXRVISIONOS_EPIC + 0, XR_TYPE_SWAPCHAIN_IMAGE_OXRVISIONOS_EPIC = XR_TYPE_OXRVISIONOS_EPIC + 1, } XrOXRVisionOSStructureTypeEPIC;`
- L24 _typedef_ `} XrGraphicsBindingOXRVisionOSEPIC;` — More members here
- L30 _typedef_ `} XrSwapchainImageOXRVisionOS;`
- L35 _macro_ `#define XR_EPIC_oxrvisionos_controller 1`
- L36 _macro_ `#define XR_EPIC_oxrvisionos_controller_SPEC_VERSION 1`
- L37 _macro_ `#define XR_EPIC_OXRVISIONOS_CONTROLLER_NAME "XR_EPIC_oxrvisionos_controller"`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOS.h` (Private)


#### class `FOXRVisionOS`  
`class FOXRVisionOS : public IModuleInterface, public IOpenXRExtensionPlugin`  
_L43-135_
- inherits: `IModuleInterface,IOpenXRExtensionPlugin`
- L49 _public prototype_ `virtual void StartupModule() override;` — /
- L50 _public prototype_ `virtual void ShutdownModule() override;`
- L55 _public function_ `virtual FString GetDisplayName() override` — /
- L59 _public prototype_ `virtual bool GetCustomLoader(PFN_xrGetInstanceProcAddr* OutGetProcAddr) override;`
- L60 _public function_ `virtual bool IsStandaloneStereoOnlyDevice() override`
- L61 _public prototype_ `virtual class FOpenXRRenderBridge* GetCustomRenderBridge(XrInstance InInstance) override;`
- L62 _public function_ `virtual bool RequiresRHIContext() const override`
- L63 _public prototype_ `virtual void OnBeginRendering_GameThread(XrSession InSession, FSceneViewFamily& InViewFamily, TArrayView<const uint32> VisibleLayers) override;`
- L64 _public prototype_ `virtual void OnBeginRendering_RenderThread_PreDeviceLocationUpdate(XrSession InSession, FRDGBuilder& GraphBuilder) override;`
- L69 _public prototype_ `static FOXRVisionOS* Get();` — /
- L70 _public function_ `static const FOXRVisionOSInstance* GetInstance()`
- L73 _public prototype_ `XrResult XrEnumerateApiLayerProperties( uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrApiLayerProperties* properties);`
- L78 _public prototype_ `XrResult XrEnumerateInstanceExtensionProperties( const char* layerName, uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrExtensionProperties* properties);`
- L84 _public prototype_ `XrResult XrCreateInstance( const XrInstanceCreateInfo* createInfo, XrInstance* instance);`
- L88 _public prototype_ `XrResult XrDestroyInstance( XrInstance instance);`
- L91 _public function_ `static bool CheckInstance(XrInstance instance)`
- L93 _public function_ `FOpenXRRenderBridge* GetRenderBridge() const`
- L98 _public prototype_ `bool IsExtensionSupported(const ANSICHAR* InName) const;`
- L99 _public prototype_ `virtual void PostSyncActions(XrSession InSession) override;`
- L102 _private function_ `static FName GetFeatureName()`
- L132 _private member_ `TMap<const ANSICHAR*, int32_t, FDefaultSetAllocator, FStringToVersionKeyFunc> SupportedExtensions;`
- L133 _private member_ `static TSharedPtr<FOXRVisionOSInstance, ESPMode::ThreadSafe> Instance;`
- L134 _private member_ `FOpenXRRenderBridge* RenderBridge = nullptr;`

#### struct `FOXRVisionOS::FStringToVersionKeyFunc`  
`struct FStringToVersionKeyFunc`  
_L109-131_
- L111 _public typedef_ `typedef const ANSICHAR* KeyType;`
- L112 _public typedef_ `typedef const ANSICHAR* KeyInitType;`
- L113 _public typedef_ `typedef const TPairInitializer<const ANSICHAR*, int32_t>& ElementInitType;`
- L117 _public function_ `static FORCEINLINE bool Matches(const ANSICHAR* A, const ANSICHAR* B)`
- L122 _public function_ `static FORCEINLINE uint32 GetKeyHash(const ANSICHAR* Key)`
- L127 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)`

#### enum `FOXRVisionOS::FStringToVersionKeyFunc::(anonymous)`  
`enum`  
_L115-115_

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOXRVisionOS, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOXRVisionOS, Log, All);`
- L21 _function_ `static const TCHAR* VOSThreadString()`
- L115 _enumerator_ `enum { bAllowDuplicateKeys = false }; static FORCEINLINE bool Matches(const ANSICHAR* A, const ANSICHAR* B) { return TCString<ANSICHAR>::Stricmp(A, B) == 0; } static FORCEINLINE uint32 GetKeyHash(const ANSICHAR* Key)` (scope `FOXRVisionOS::FStringToVersionKeyFunc::__anona15653640103`)

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSAction.h` (Private)


#### class `FOXRVisionOSAction`  
`class FOXRVisionOSAction`  
_L14-73_
- L17 _public prototype_ `static XrResult Create(TSharedPtr<FOXRVisionOSAction, ESPMode::ThreadSafe>& OutAction, const XrActionCreateInfo* createInfo, FOXRVisionOSActionSet* ActionSet);`
- L18 _public prototype_ `FOXRVisionOSAction(const XrActionCreateInfo* createInfo, FOXRVisionOSActionSet* ActionSet);`
- L19 _public prototype_ `~FOXRVisionOSAction();`
- L20 _public prototype_ `XrResult XrDestroyAction();`
- L22 _public function_ `XrActionType GetActionType() const`
- L23 _public function_ `const FOXRVisionOSActionSet& GetActionSet() const`
- L25 _public prototype_ `void BindSource(XrPath AppPath, EOXRVisionOSControllerButton Button);`
- L26 _public prototype_ `const TArray<XrPath>& GetBoundSources() const;`
- L28 _public prototype_ `XrResult GetActionStateBoolean(XrPath SubActionPath, XrActionStateBoolean& OutState) const;`
- L29 _public prototype_ `XrResult GetActionStateFloat(XrPath SubActionPath, XrActionStateFloat& OutState) const;`
- L30 _public prototype_ `XrResult GetActionStateVector2f(XrPath SubActionPath, XrActionStateVector2f& OutState) const;`
- L31 _public prototype_ `XrResult GetActionStatePose(XrPath SubActionPath, XrActionStatePose& OutState) const;`
- L33 _public prototype_ `void Sync(TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe>& Controllers, TSharedPtr <FOXRVisionOSTracker, ESPMode::ThreadSafe>& Tracker);`
- L34 _public prototype_ `EOXRVisionOSControllerButton GetPoseButton(XrPath SubactionPath) const;`
- L36 _public function_ `FName GetActionName() const`
- L39 _private member_ `bool bCreateFailed = false;`
- L40 _private member_ `FOXRVisionOSActionSet* ActionSet = nullptr;`
- L42 _private member_ `FName ActionName;`
- L43 _private member_ `XrActionType ActionType;`
- L44 _private member_ `char LocalizedActionName[XR_MAX_LOCALIZED_ACTION_NAME_SIZE];`
- L46 _private member_ `TArray<XrPath> BoundPaths;`
- L65 _private member_ `TMap<XrPath, SubActionPathBinding> SubactionPathBoundSourcesAndStates;`
- L66 _private prototype_ `EActionStateTranslation GetActionStateTranslation(EOXRVisionOSControllerButton Button) const;`
- L69 _private prototype_ `void SyncPathsBoolean(TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe>& Controllers, const TArray<TPair<EOXRVisionOSControllerButton, EActionStateTranslation>>& Buttons, XrActionStateBoolean& OutActionState);`
- L70 _private prototype_ `void SyncPathsFloat(TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe>& Controllers, const TArray<TPair<EOXRVisionOSControllerButton, EActionStateTranslation>>& Buttons, XrActionStateFloat& OutActionState);`
- L71 _private prototype_ `void SyncPathsVector2f(TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe>& Controllers, const TArray<TPair<EOXRVisionOSControllerButton, EActionStateTranslation>>& Buttons, XrActionStateVector2f& OutActionState);`
- L72 _private prototype_ `void SyncPathsPose(TSharedPtr <FOXRVisionOSTracker, ESPMode::ThreadSafe>& Tracker, const TArray<TPair<EOXRVisionOSControllerButton, EActionStateTranslation>>& Buttons, XrActionStatePose& OutActionState);`

#### union `FOXRVisionOSAction::ActionStateUnion`  
`union ActionStateUnion`  
_L48-54_
- desc: Note we craftily use XR_NULL_PATH as a subaction path to handle the case where none is specified on query.
- L50 _public member_ `XrActionStateBoolean Boolean;`
- L51 _public member_ `XrActionStateFloat Float;`
- L52 _public member_ `XrActionStateVector2f Vector2f;`
- L53 _public member_ `XrActionStatePose Pose;`

#### enum `FOXRVisionOSAction::EActionStateTranslation`  
`enum class EActionStateTranslation`  
_L55-59_
- L57 _public enumerator_ `None`
- L58 _public enumerator_ `FloatAsBool`

#### struct `FOXRVisionOSAction::SubActionPathBinding`  
`struct SubActionPathBinding`  
_L60-64_
- L62 _public member_ `TArray<TPair<EOXRVisionOSControllerButton, EActionStateTranslation>> Buttons;`
- L63 _public member_ `ActionStateUnion ActionState = {};`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSActionSet.h` (Private)


#### class `FOXRVisionOSActionSet`  
`class FOXRVisionOSActionSet`  
_L13-44_
- L16 _public prototype_ `static XrResult Create(TSharedPtr<FOXRVisionOSActionSet, ESPMode::ThreadSafe>& OutActionSet, const XrActionSetCreateInfo* createInfo, FOXRVisionOSInstance* Instance);`
- L17 _public prototype_ `FOXRVisionOSActionSet(const XrActionSetCreateInfo* createInfo, FOXRVisionOSInstance* Instance);`
- L18 _public prototype_ `~FOXRVisionOSActionSet();`
- L19 _public prototype_ `XrResult XrDestroyActionSet();`
- L21 _public prototype_ `XrResult XrCreateAction( const XrActionCreateInfo* createInfo, XrAction* action);`
- L24 _public prototype_ `XrResult DestroyAction(FOXRVisionOSAction* Action);`
- L26 _public prototype_ `XrResult Attach(FOXRVisionOSSession* Session);`
- L27 _public function_ `bool IsAttached() const`
- L29 _public function_ `const TArray<TSharedPtr<FOXRVisionOSAction, ESPMode::ThreadSafe>>& GetActions() const`
- L30 _public prototype_ `void ClearActive();`
- L31 _public prototype_ `void SetActive(XrPath SubActionPath);`
- L33 _public prototype_ `void SyncActions(TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe>& Controllers, TSharedPtr <FOXRVisionOSTracker, ESPMode::ThreadSafe>& Tracker);` — uint32 GetPriority() const { return CreateInfo.priority; } //Note: action set priority currently unsupported
- L35 _public function_ `const FOXRVisionOSInstance* GetInstance() const`
- L38 _private member_ `bool bCreateFailed = false;`
- L39 _private member_ `FOXRVisionOSInstance* Instance = nullptr;`
- L40 _private member_ `FOXRVisionOSSession* Session = nullptr;`
- L41 _private member_ `XrActionSetCreateInfo CreateInfo;`
- L42 _private member_ `TArray<TSharedPtr<FOXRVisionOSAction, ESPMode::ThreadSafe>> Actions;`
- L43 _private member_ `bool bAllActive = false;`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSAppDelegate.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace OXRVisionOS`
- L9 _prototype_ `CP_OBJECT_cp_layer_renderer* GetSwiftLayerRenderer();` (scope `OXRVisionOS`)
- L11 _prototype_ `int GetSwiftNumViewports();` (scope `OXRVisionOS`)
- L13 _prototype_ `CGRect GetSwiftViewportRect(int Index);` (scope `OXRVisionOS`)

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSController.h` (Private)


#### enum `EOXRVisionOSControllerButton`  
`enum class EOXRVisionOSControllerButton : int32`  
_L14-42_
- L16 _public enumerator_ `LeftButtonStart = 0`
- L17 _public enumerator_ `PushL = LeftButtonStart`
- L18 _public enumerator_ `LeftButtonCount`
- L20 _public enumerator_ `RightButtonStart = LeftButtonCount`
- L21 _public enumerator_ `PushR = RightButtonStart`
- L22 _public enumerator_ `RightButtonCount`
- L24 _public enumerator_ `PhysicalButtonCount = RightButtonCount`
- L27 _public enumerator_ `TotalButtonCount` — Max number of controller buttons
- L30 _public enumerator_ `GripL = TotalButtonCount` — Pose inputs, handled by OXRVisionOSTracker
- L31 _public enumerator_ `AimL`
- L32 _public enumerator_ `GripSurfaceL`
- L33 _public enumerator_ `GripR`
- L34 _public enumerator_ `AimR`
- L35 _public enumerator_ `GripSurfaceR`
- L36 _public enumerator_ `HMDPose`
- L41 _public enumerator_ `NullInput` — This input is never mapped to hardware.

#### class `VrControllerAPI`  
`class VrControllerAPI`  
_L49-66_
- L59 _public prototype_ `static bool Init();` — VrControllerAPI Initialization and termination
- L60 _public prototype_ `static void Term();`
- L63 _public prototype_ `static int32 ControllerOpen(EControllerHand ControllerHand);` — Controller methods
- L64 _public prototype_ `static void ControllerClose(int32 Handle);`
- L65 _public prototype_ `static bool ControllerIsReady(int32 Handle);`

#### struct `VrControllerAPI::EVrControllerButton`  
`struct EVrControllerButton`  
_L53-56_
- L55 _public member_ `static const int32 Mask[(int32)EOXRVisionOSControllerButton::PhysicalButtonCount];`

#### class `FOXRVisionOSController`  
`class FOXRVisionOSController`  
_L72-120_
- desc: Implementation of the OXRVisionOS motion controllers. One instance of this handles both controllers.
- L75 _public prototype_ `static bool Create(TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe>& OutController, FOXRVisionOSSession* InSession);`
- L76 _public prototype_ `FOXRVisionOSController(FOXRVisionOSSession* InSession);`
- L77 _public prototype_ `~FOXRVisionOSController();`
- L79 _public prototype_ `void OnBeginSession(FOXRVisionOSTracker* Tracker);`
- L80 _public prototype_ `void OnEndSession(FOXRVisionOSTracker* Tracker);`
- L82 _public prototype_ `void SyncActions();`
- L83 _public prototype_ `bool GetActionStateBoolean(EOXRVisionOSControllerButton Button, bool& OutValue, bool& OutActive, XrTime& OutTimeStamp);`
- L84 _public prototype_ `bool GetActionStateFloat(EOXRVisionOSControllerButton Button, float& OutValue, bool& OutActive, XrTime& OutTimeStamp);`
- L85 _public prototype_ `bool GetActionStateVector2f(EOXRVisionOSControllerButton Button, XrVector2f& OutValue, bool& OutActive, XrTime& OutTimeStamp);`
- L87 _public prototype_ `int32 GetLeftControllerHandle() const;`
- L88 _public prototype_ `int32 GetRightControllerHandle() const;`
- L89 _public prototype_ `static bool IsFloatButton(EOXRVisionOSControllerButton Button);`
- L92 _private prototype_ `static int32 ControllerHandToIndex(EControllerHand ControllerHand);`
- L93 _private prototype_ `static EControllerHand ControllerIndexToHand(int32 ControllerIndex);`
- L95 _private member_ `bool bCreateFailed = false;`
- L96 _private member_ `FOXRVisionOSSession* Session = nullptr;`
- L108 _private member_ `static constexpr int32 LeftHandIndex = 0;`
- L109 _private member_ `static constexpr int32 RightHandIndex = 1;`
- L116 _private member_ `} UserState;`
- L119 _private prototype_ `bool GetActionStateBooleanAsFloat(EOXRVisionOSControllerButton Button, float& OutValue, bool& OutActive, XrTime& OutTimeStamp);` — Helper for using boolean inputs as float inputs

#### struct `FOXRVisionOSController::FControllerState`  
`struct FControllerState`  
_L99-106_
- desc: State for a controller
- L102 _public member_ `int32 Handle;` — TODO
- L105 _public member_ `EControllerHand Hand;` — Left or right hand which the controller represents

#### struct `FOXRVisionOSController::FUserState`  
`struct FUserState`  
_L112-116_
- desc: State for user connections
- L115 _public member_ `FControllerState ControllerStates[2];` — Per controller state, 2 per user for left & right hands

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace OXRVisionOS`
- L46 _prototype_ `const TCHAR* OXRVisionOSControllerButtonToTCHAR(EOXRVisionOSControllerButton Button);` (scope `OXRVisionOS`)

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSInstance.h` (Private)


#### class `FOXRVisionOSInstance`  
`class FOXRVisionOSInstance`  
_L18-247_
- L21 _public prototype_ `static XrResult Create(TSharedPtr<FOXRVisionOSInstance, ESPMode::ThreadSafe>& OutInstance, const XrInstanceCreateInfo* createInfo, FOXRVisionOS* InModule);`
- L22 _public prototype_ `FOXRVisionOSInstance(const XrInstanceCreateInfo* createInfo, FOXRVisionOS* Module);`
- L24 _public prototype_ `~FOXRVisionOSInstance();`
- L26 _public prototype_ `XrResult XrGetInstanceProperties( XrInstanceProperties* instanceProperties);`
- L29 _public prototype_ `XrResult XrGetSystemProperties( XrSystemId systemId, XrSystemProperties* properties);`
- L33 _public prototype_ `XrResult XrEnumerateEnvironmentBlendModes( XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t environmentBlendModeCapacityInput, uint32_t* environmentBlendModeCountOutput, XrEnvironmentBlendMode* environmentBlendModes);`
- L40 _public prototype_ `XrResult XrEnumerateViewConfigurations( XrSystemId systemId, uint32_t viewConfigurationTypeCapacityInput, uint32_t* viewConfigurationTypeCountOutput, XrViewConfigurationType* viewConfigurationTypes);`
- L46 _public prototype_ `XrResult XrGetViewConfigurationProperties( XrSystemId systemId, XrViewConfigurationType viewConfigurationType, XrViewConfigurationProperties* configurationProperties);`
- L51 _public prototype_ `XrResult XrEnumerateViewConfigurationViews( XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrViewConfigurationView* views);`
- L58 _public prototype_ `XrResult XrGetSystem( const XrSystemGetInfo* getInfo, XrSystemId* systemId);`
- L62 _public prototype_ `bool IsHMDAvailable();`
- L64 _public prototype_ `XrResult XrCreateSession( const XrSessionCreateInfo* createInfo, XrSession* session);`
- L68 _public function_ `XrResult DestroySession()`
- L70 _public function_ `static bool CheckSession(XrSession session)`
- L72 _public prototype_ `XrResult XrStringToPath( const char* pathString, XrPath* path);`
- L76 _public prototype_ `XrResult XrPathToString( XrPath path, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer);`
- L82 _public function_ `char* PathToString(XrPath Path) const`
- L87 _public prototype_ `XrResult XrCreateActionSet( const XrActionSetCreateInfo* createInfo, XrActionSet* actionSet);`
- L91 _public prototype_ `XrResult DestroyActionSet(FOXRVisionOSActionSet* ActionSet);`
- L93 _public prototype_ `XrResult XrSuggestInteractionProfileBindings( const XrInteractionProfileSuggestedBinding* suggestedBindings);`
- L96 _public prototype_ `XrResult XrPollEvent( XrEventDataBuffer* eventData);`
- L100 _public function_ `template <typename T1> void EnqueueEvent(T1& InEvent)`
- L106 _public function_ `bool IsExtensionEnabled(const ANSICHAR* ExtensionName) const`
- L109 _private member_ `bool bCreateFailed = false;`
- L110 _private member_ `FOXRVisionOS* Module = nullptr;`
- L111 _private member_ `static TSharedPtr<FOXRVisionOSSession, ESPMode::ThreadSafe> Session;`
- L113 _private prototype_ `void OnWorldTickStart(UWorld* World, ELevelTick TickType, float DeltaTime);`
- L114 _private member_ `FDelegateHandle OnWorldTickStartDelegateHandle;`
- L115 _private member_ `bool bHMDWorn = false;`
- L144 _private member_ `TSet<const ANSICHAR*, FAnsiKeyFunc> EnabledExtensions;`
- L146 _private member_ `XrInstanceProperties InstanceProperties;`
- L147 _private member_ `XrSystemProperties SystemProperties;`
- L170 _private member_ `TQueue<TSharedPtr<IEventDataHolder, ESPMode::ThreadSafe>, EQueueMode::Mpsc> EventQueue;`
- L172 _private prototype_ `XrPath StringToPath(const char* pathString);`
- L173 _private prototype_ `XrPath StringToPath(const char* pathString, uint32 PathSize);`
- L174 _private member_ `TArray<TUniquePtr<ANSICHAR[]>> XrPaths;` — An XrPath is an index into this array
- L198 _private member_ `TMap<const ANSICHAR*, XrPath, FDefaultSetAllocator, FStringToXrPathKeyFunc> StringToXrPathMap;`
- L199 _private member_ `TArray<TSharedPtr<FOXRVisionOSActionSet, ESPMode::ThreadSafe>> ActionSets;`
- L201 _public prototype_ `TSharedPtr<FOXRVisionOSActionSet, ESPMode::ThreadSafe> GetActionSetSharedPtr(XrActionSet ActionSet);`
- L210 _private member_ `TMap<XrPath, TMap<XrPath, EOXRVisionOSControllerButton>> InteractionProfiles;` — Interaction profiles define a set of 'input paths' and how they should map to runtime hardware, like controllers. We have a set of source buttons that are 1:1 with specific hardware. The OXRVisionOS native interaction profile, therefore, simply maps every path to its button. Other profiles will map their input paths to one button. Interaction profiles will, currently, never bind multiple source buttons to a single profile path.
- L211 _private prototype_ `void CreateInteractionProfiles();`
- L214 _private prototype_ `bool IsFirstInputProfilePreferred(XrPath First, XrPath Second) const;` — The runtime must select one interaction profile for each top level path from among those the application attempts to bind.
- L215 _private member_ `TMap<XrPath, XrPath> TopLevelPathInteractionProfileMap;` — Map of top level paths to most preferred bound input profile
- L216 _private member_ `TMap<XrPath, XrPath> InputPathToTopLevelPathMap;` — Map of input paths to Top level paths (eg /user/hand/left)
- L240 _public member_ `TMap<XrPath, FInteractionProfileBinding> InteractionProfileBindings;`
- L241 _public member_ `TArray<XrPath> PreferredInteractionProfileBindingList;` — The list of supported interaction profiles ordered from most to least preferred.
- L242 _public function_ `const TMap<XrPath, FInteractionProfileBinding>& GetInteractionProfileBindings() const`
- L243 _public function_ `const TArray<XrPath>& GetPreferredInteractionProfileBindingList() const`
- L244 _public function_ `XrPath GetCurrentInteractionProfile(XrPath TopLevelUserPath) const`
- L245 _public function_ `XrPath InputPathToTopLevelPath(XrPath InPath) const`
- L246 _public function_ `XrPath TopLevelPathToInteractionProfile(XrPath InPath) const`

#### struct `FOXRVisionOSInstance::FAnsiKeyFunc`  
`struct FAnsiKeyFunc : BaseKeyFuncs<const ANSICHAR*, const ANSICHAR*, false>`  
_L117-143_
- inherits: `BaseKeyFuncs<constANSICHAR*,constANSICHAR*,false>`
- L119 _public typedef_ `typedef typename TTypeTraits<const ANSICHAR*>::ConstPointerType KeyInitType;`
- L120 _public typedef_ `typedef typename TCallTraits<const ANSICHAR*>::ParamType ElementInitType;`
- L125 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)` — @return The key used to index the given element.
- L133 _public function_ `static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)` — @return True if the keys match.
- L139 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)` — Calculates a hash index for a key.

#### struct `FOXRVisionOSInstance::IEventDataHolder`  
`struct IEventDataHolder`  
_L150-154_
- L152 _public function_ `virtual ~IEventDataHolder()`
- L153 _public prototype_ `virtual void CopyInto(XrEventDataBuffer* eventData) = 0;`

#### struct `FOXRVisionOSInstance::FEventDataHolder`  
`template <typename T1> struct FEventDataHolder : public IEventDataHolder`  
_L157-168_
- inherits: `IEventDataHolder`
- L159 _public function_ `FEventDataHolder(T1 InEvent)`
- L160 _public function_ `virtual ~FEventDataHolder()`
- L161 _public function_ `virtual void CopyInto(XrEventDataBuffer* EventData) override`
- L167 _private member_ `T1 Event;`

#### struct `FOXRVisionOSInstance::FStringToXrPathKeyFunc`  
`struct FStringToXrPathKeyFunc`  
_L175-197_
- L177 _public typedef_ `typedef const ANSICHAR* KeyType;`
- L178 _public typedef_ `typedef const ANSICHAR* KeyInitType;`
- L179 _public typedef_ `typedef const TPairInitializer<const ANSICHAR*, XrPath>& ElementInitType;`
- L183 _public function_ `static FORCEINLINE bool Matches(const ANSICHAR* A, const ANSICHAR* B)`
- L188 _public function_ `static FORCEINLINE uint32 GetKeyHash(const ANSICHAR* Key)`
- L193 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)`

#### enum `FOXRVisionOSInstance::FStringToXrPathKeyFunc::(anonymous)`  
`enum`  
_L181-181_

#### struct `FOXRVisionOSInstance::FInteractionProfileBinding`  
`struct FInteractionProfileBinding`  
_L222-239_
- L224 _public member_ `XrPath InteractionProfilePath = XR_NULL_PATH;`
- L238 _public member_ `TArray<FBinding> Bindings;`

#### struct `FOXRVisionOSInstance::FInteractionProfileBinding::FBinding`  
`struct FBinding`  
_L225-237_
- L227 _public function_ `FBinding()`
- L229 _public function_ `FBinding(XrAction InAction, XrPath InPath, EOXRVisionOSControllerButton InButton) : Action(InAction) , Path(InPath) , Button(InButton)`
- L234 _public member_ `XrAction Action;`
- L235 _public member_ `XrPath Path = XR_NULL_PATH;`
- L236 _public member_ `EOXRVisionOSControllerButton Button;`

#### Free symbols / members of external scopes

- L181 _enumerator_ `enum { bAllowDuplicateKeys = false }; static FORCEINLINE bool Matches(const ANSICHAR* A, const ANSICHAR* B) { return TCString<ANSICHAR>::Stricmp(A, B) == 0; } static FORCEINLINE uint32 GetKeyHash(const ANSICHAR* Key)` (scope `FOXRVisionOSInstance::FStringToXrPathKeyFunc::__anon85d67e590103`)

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSPlatformRHI.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define XR_USE_GRAPHICS_API_OXRVISIONOS`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSPlatformUtils.h` (Private)


#### struct `OXRVisionOS::TrackerPoseData`  
`struct TrackerPoseData`  
_L14-18_
- L16 _public member_ `simd_float3 position = {0.0f,0.0f,0.0f};`
- L17 _public member_ `simd_float4 orientation = {0.0f,0.0f,0.0f,1.0f};`

#### struct `OXRVisionOS::TrackerResultData`  
`struct TrackerResultData`  
_L20-23_
- L22 _public member_ `TrackerPoseData Pose;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace OXRVisionOS`
- L26 _variable_ `const XrVector3f XrZeroVector = {};` (scope `OXRVisionOS`)
- L28 _function_ `FORCEINLINE FVector ToFVector(const simd_float3& InVector)` (scope `OXRVisionOS`)
- L36 _function_ `FORCEINLINE simd_float3 ToSimdFVector3(const FVector& InVector)` (scope `OXRVisionOS`)
- L44 _function_ `FORCEINLINE simd_float3 ToSimdFVector3(const XrVector3f& InVector)` (scope `OXRVisionOS`)
- L52 _function_ `FORCEINLINE XrVector3f ToXrVector3f(const FVector& InVector)` (scope `OXRVisionOS`)
- L61 _function_ `FORCEINLINE XrVector3f ToXrVector3f(const simd_float3& InVector)` (scope `OXRVisionOS`)
- L70 _function_ `FORCEINLINE FQuat ToFQuat(const simd_float4& InQuaternion)` (scope `OXRVisionOS`)
- L79 _function_ `FORCEINLINE simd_float4 ToSimdFQuaternion(const FQuat& InQuaternion)` (scope `OXRVisionOS`)
- L88 _function_ `FORCEINLINE simd_float4 ToSimdFQuaternion(const XrQuaternionf& InQuaternion)` (scope `OXRVisionOS`)
- L97 _function_ `FORCEINLINE XrQuaternionf ToXrQuaternionf(const FQuat& InQuaternion)` (scope `OXRVisionOS`)
- L113 _function_ `static FORCEINLINE FTransform ToFTransform(const matrix_float4x4& RawYUpMatrix)` (scope `OXRVisionOS`) — Convert's an ARKit 'Y up' 'right handed' coordinate system transform to Unreal's 'Z up' 'left handed' coordinate system. Scale is removed because some ARKit transforms are less normalized than unreal requires.
- L136 _function_ `FORCEINLINE FTransform ToFTransform(const TrackerPoseData& InPoseData)` (scope `OXRVisionOS`)
- L143 _function_ `FORCEINLINE TrackerPoseData ToPoseData(const FTransform& InTransform)` (scope `OXRVisionOS`)
- L151 _function_ `FORCEINLINE XrPosef ToXrPose(const TrackerPoseData& InPoseData)` (scope `OXRVisionOS`)
- L165 _function_ `FORCEINLINE XrPosef ToXrPose(const simd_float4x4& RawYUpMatrix)` (scope `OXRVisionOS`)
- L193 _function_ `FORCEINLINE XrPosef ToXrPose(const FTransform& InTransform)` (scope `OXRVisionOS`)
- L201 _function_ `FORCEINLINE XrSpaceLocationFlags ToXrSpaceLocationFlags(TrackerResultData& InResultData)` (scope `OXRVisionOS`)
- L216 _function_ `FORCEINLINE XrSpaceVelocityFlags ToXrSpaceVelocityFlags(TrackerResultData& InResultData)` (scope `OXRVisionOS`)
- L229 _function_ `FORCEINLINE XrTime APITimeToXrTime(CFTimeInterval TimeInterval)` (scope `OXRVisionOS`) — CFTimeInterval is a double of seconds.  XrTime is uint64 nanoseconds.
- L234 _function_ `FORCEINLINE CFTimeInterval XrTimeToAPITime(XrTime xrTime)` (scope `OXRVisionOS`)

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSSession.h` (Private)


#### class `FOXRVisionOSSession`  
`class FOXRVisionOSSession`  
_L29-300_
- L32 _public prototype_ `static XrResult Create(TSharedPtr<FOXRVisionOSSession, ESPMode::ThreadSafe>& OutSession, const XrSessionCreateInfo* createInfo, FOXRVisionOSInstance* Instance);`
- L33 _public prototype_ `FOXRVisionOSSession(const XrSessionCreateInfo* createInfo, FOXRVisionOSInstance* Instance);`
- L34 _public prototype_ `~FOXRVisionOSSession();`
- L35 _public prototype_ `XrResult XrDestroySession();`
- L37 _public prototype_ `XrResult XrEnumerateReferenceSpaces( uint32_t spaceCapacityInput, uint32_t* spaceCountOutput, XrReferenceSpaceType* spaces);`
- L42 _public prototype_ `XrResult XrCreateReferenceSpace( const XrReferenceSpaceCreateInfo* createInfo, XrSpace* space);`
- L46 _public prototype_ `XrResult XrGetReferenceSpaceBoundsRect( XrReferenceSpaceType referenceSpaceType, XrExtent2Df* bounds);`
- L50 _public prototype_ `XrResult XrCreateActionSpace( const XrActionSpaceCreateInfo* createInfo, XrSpace* space);`
- L54 _public prototype_ `const FOXRVisionOSSpace* ToFOXRVisionOSSpace(const XrSpace& Space);`
- L56 _public prototype_ `XrResult DestroySpace( FOXRVisionOSSpace* Space);`
- L59 _public prototype_ `XrResult XrEnumerateSwapchainFormats( uint32_t formatCapacityInput, uint32_t* formatCountOutput, int64_t* formats);`
- L64 _public prototype_ `XrResult XrCreateSwapchain( const XrSwapchainCreateInfo* createInfo, XrSwapchain* swapchain);`
- L68 _public prototype_ `XrResult DestroySwapchain( FOXRVisionOSSwapchain* Swapchain);`
- L71 _public prototype_ `XrResult XrAttachSessionActionSets( const XrSessionActionSetsAttachInfo* attachInfo);`
- L74 _public prototype_ `XrResult XrGetCurrentInteractionProfile( XrPath topLevelUserPath, XrInteractionProfileState* interactionProfile);`
- L78 _public prototype_ `XrResult XrGetActionStateBoolean( const XrActionStateGetInfo* getInfo, XrActionStateBoolean* state);`
- L82 _public prototype_ `XrResult XrGetActionStateFloat( const XrActionStateGetInfo* getInfo, XrActionStateFloat* state);`
- L86 _public prototype_ `XrResult XrGetActionStateVector2f( const XrActionStateGetInfo* getInfo, XrActionStateVector2f* state);`
- L90 _public prototype_ `XrResult XrGetActionStatePose( const XrActionStateGetInfo* getInfo, XrActionStatePose* state);`
- L94 _public prototype_ `XrResult XrSyncActions( const XrActionsSyncInfo* syncInfo);`
- L97 _public prototype_ `XrResult XrEnumerateBoundSourcesForAction( const XrBoundSourcesForActionEnumerateInfo* enumerateInfo, uint32_t sourceCapacityInput, uint32_t* sourceCountOutput, XrPath* sources);`
- L103 _public prototype_ `XrResult XrApplyHapticFeedback( const XrHapticActionInfo* hapticActionInfo, const XrHapticBaseHeader* hapticFeedback);`
- L107 _public prototype_ `XrResult XrStopHapticFeedback( const XrHapticActionInfo* hapticActionInfo);`
- L110 _public prototype_ `XrResult XrBeginSession( const XrSessionBeginInfo* beginInfo);`
- L113 _public prototype_ `XrResult XrEndSession();`
- L115 _public prototype_ `void EndSessionInternal();`
- L117 _public prototype_ `XrResult XrRequestExitSession();`
- L119 _public prototype_ `XrResult XrWaitFrame( const XrFrameWaitInfo* frameWaitInfo, XrFrameState* frameState);`
- L123 _public prototype_ `void OnBeginRendering_GameThread();`
- L125 _public prototype_ `void OnBeginRendering_RenderThread_PreDeviceLocationUpdate();`
- L127 _public prototype_ `void OnBeginFrame_RHIThread(FRHICommandListImmediate* InRHICommandList);`
- L129 _public prototype_ `XrResult XrBeginFrame( const XrFrameBeginInfo* frameBeginInfo);`
- L132 _public prototype_ `XrResult XrEndFrame( const XrFrameEndInfo* frameEndInfo);`
- L135 _public prototype_ `XrResult XrLocateViews( const XrViewLocateInfo* viewLocateInfo, XrViewState* viewState, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrView* views);`
- L142 _public prototype_ `XrResult XrCreateHandTrackerEXT( const XrHandTrackerCreateInfoEXT* createInfo, XrHandTrackerEXT* handTracker);`
- L146 _public prototype_ `XrTime GetCurrentTime() const;`
- L148 _public prototype_ `void SetSessionState(XrSessionState NewState);`
- L149 _public function_ `XrSessionState GetSessionState() const`
- L151 _public prototype_ `bool IsSessionRunning() const;`
- L153 _public function_ `FOXRVisionOSTracker& GetTrackerChecked() const`
- L182 _public prototype_ `void RenderToGameFrameStateRead(FPipelinedFrameState& InOutFrameState);`
- L183 _public prototype_ `void RenderToGameFrameStateWrite(const FPipelinedFrameState& FrameState);`
- L185 _public prototype_ `const FPipelinedFrameState& GetPipelinedFrameStateForThread() const;`
- L186 _public prototype_ `FPipelinedFrameState& GetPipelinedFrameStateForThread();`
- L187 _public prototype_ `void GetHMDTransform(XrTime DisplayTime, FTransform& OutTransform, XrSpaceLocationFlags& OutLocationFlags);`
- L188 _public prototype_ `void GetTransformForButton(EOXRVisionOSControllerButton Button, XrTime DisplayTime, FTransform& OutTransform, XrSpaceLocationFlags& OutLocationFlags, FVector& OutLinearVelocity, FVector& OutAngularVelocity, XrSpaceVelocityFlags& OutVelocityFlags);`
- L189 _public prototype_ `void SetTriggerEffectVRControllers(int32 ControllerId, const FInputDeviceProperty* Property);`
- L191 _public prototype_ `void OnPostSyncActions();` — FOpenXRInput::Tick, game thread, after xrSyncActions
- L199 _public member_ `static constexpr int LocateViewInfoBufferLength = 3;`
- L200 _public member_ `FLocateViewInfo LocateViewInfoBuffer[LocateViewInfoBufferLength];`
- L201 _public function_ `void LocateViewInfoIndexAdvance()`
- L202 _public function_ `const FLocateViewInfo& GetLocateViewInfo_GameThread()`
- L203 _public function_ `FLocateViewInfo& GetLocateViewInfo_RenderThread()`
- L206 _private member_ `bool bCreateFailed = false;`
- L207 _private member_ `bool bIsRunning = false;`
- L208 _private member_ `bool bExitRequested = false;`
- L209 _private member_ `FOXRVisionOSInstance* Instance = nullptr;`
- L210 _private member_ `uint64_t XRTimeScale = 1;`
- L211 _private member_ `XrSessionState SessionState = XR_SESSION_STATE_UNKNOWN;`
- L212 _private member_ `bool ActionSetsAlreadyAttached = false;`
- L213 _private member_ `TArray<TSharedPtr<FOXRVisionOSActionSet, ESPMode::ThreadSafe>> ActionSets;`
- L214 _private member_ `TSharedPtr<FOXRVisionOSController, ESPMode::ThreadSafe> Controllers;`
- L215 _private member_ `TArray<TSharedPtr<FOXRVisionOSSpace, ESPMode::ThreadSafe>> Spaces;`
- L216 _private member_ `FQuat GripPoseAdjustment;`
- L217 _private member_ `FQuat AimPoseAdjustment;`
- L218 _private member_ `FQuat GripSurfacePoseAdjustment;`
- L220 _private member_ `FPlatformMemory::FPlatformVirtualMemoryBlock m_reprojectionData;`
- L221 _private member_ `FPlatformMemory::FPlatformVirtualMemoryBlock m_displayData;`
- L223 _private member_ `TArray<TSharedPtr<FOXRVisionOSSwapchain, ESPMode::ThreadSafe>> Swapchains;`
- L225 _private member_ `int32 NextBackBufferIndex = 0;`
- L226 _private member_ `int32 PreviousBackBufferIndexInBegin = -1;`
- L227 _private member_ `int32 SessionFrameCounter = 0;`
- L229 _private member_ `static const int32 INVALID_DEVICE_HANDLE = -1;`
- L230 _private member_ `int32 HMDHandle = INVALID_DEVICE_HANDLE;`
- L232 _private member_ `TSharedPtr <FOXRVisionOSTracker, ESPMode::ThreadSafe> Tracker;`
- L235 _private member_ `static const int32 RESULT_OK = 0;` — TEMP
- L238 _private prototype_ `void OnWorldTickStart(UWorld* World, ELevelTick TickType, float DeltaTime);`
- L239 _private member_ `FDelegateHandle OnWorldTickStartDelegateHandle;`
- L241 _private prototype_ `void WaitUntil();`
- L242 _private prototype_ `void StartSubmission();`
- L243 _private member_ `FEvent* XrWaitFrameEvent = nullptr;`
- L244 _private member_ `FPipelinedFrameState PipelinedFrameStateGame;`
- L245 _private member_ `FPipelinedFrameState PipelinedFrameStateRendering;`
- L246 _private member_ `FPipelinedFrameState PipelinedFrameStateRHI;`
- L247 _private member_ `int32 CachedBeginFlipFrameCounter = INT32_MAX;`
- L249 _private member_ `static const int32 RenderToGameFrameStateBufferLength = 3;`
- L250 _private member_ `FRenderToGameFrameState RenderToGameFrameState[RenderToGameFrameStateBufferLength];`
- L252 _private member_ `FOpenXRRenderBridge* RenderBridge = nullptr;`
- L254 _private member_ `CP_OBJECT_cp_layer_renderer* VOSLayerRenderer = nullptr;`
- L255 _private member_ `ar_session_t ARKitSession = nullptr;`
- L256 _private member_ `ar_world_tracking_provider_t ARKitWorldTrackingProvider = nullptr;`
- L257 _private member_ `ar_device_anchor_t ARKitHMDAnchor = nullptr;`
- L261 _private member_ `mutable FCriticalSection CpLayerMutex;` — mutexes to protect apple api functions from concurrent calls We do not protect the early startup calls, before OXRVisionOSSession is involved.  They should be single threaded.
- L291 _private prototype_ `void BeginHandTracking();`
- L292 _private member_ `ar_hand_tracking_provider_t ARKitHandTrackingProvider = nullptr;`
- L293 _private member_ `TArray<TPair<ar_hand_skeleton_joint_name_t,XrHandJointEXT>> JointMap;`
- L294 _private member_ `FOXRVisionOSHandTracker HandTrackers[2];`
- L296 _private function_ `FOXRVisionOSHandTracker& GetHandTracker(XrHandEXT Hand)`
- L297 _private function_ `const FOXRVisionOSHandTracker& GetHandTracker(XrHandEXT Hand) const`
- L298 _private function_ `bool ValidateXrHandTrackerEXT(XrHandTrackerEXT HandTracker)`
- L299 _private prototype_ `void SyncHandTracking();`

#### struct `FOXRVisionOSSession::FPipelinedFrameState`  
`struct FPipelinedFrameState`  
_L155-175_
- L157 _public member_ `int32 FrameCounter = -1;`
- L158 _public member_ `XrTime PredictedDisplayTime = 0;`
- L161 _public member_ `cp_frame_t SwiftFrame = nullptr;` — FTransform HMDPoseInTrackerSpace = FTransform::Identity; PoseData HmdPose = {};
- L162 _public member_ `cp_frame_timing_t SwiftFrameTiming = nullptr;` — Used for the cp_time_wait_until
- L163 _public member_ `CFTimeInterval PreviousPredictionTime = 0;`
- L164 _public member_ `cp_drawable_t SwiftDrawable = nullptr;`
- L165 _public member_ `cp_frame_timing_t SwiftFinalFrameTiming = nullptr;` — TODO should we do this or should we overwrite SwifFrameTiming???
- L166 _public member_ `simd_float4x4 HeadTransform = matrix_identity_float4x4;`
- L167 _public member_ `CFTimeInterval SwiftFinalFrameTimeInterval = 0;`
- L168 _public member_ `ar_device_anchor_t DeviceAnchor = nullptr;`
- L169 _public member_ `bool bSynchronizing = true;` — when true we are in the process of starting up a new session and the new frame state has not yet propagated.
- L170 _public member_ `bool bShouldRender = false;`
- L171 _public member_ `bool bSessionLost = false;`
- L172 _public member_ `XrFovf HmdFovs[2];`
- L173 _public member_ `int32 LocateViewInfoBufferIndex = 0;`
- L174 _public member_ `int32 RenderToGameFrameStateIndex = -1;`

#### struct `FOXRVisionOSSession::FRenderToGameFrameState`  
`struct FRenderToGameFrameState`  
_L177-181_
- L179 _public member_ `simd_float4x4 HeadTransform = matrix_identity_float4x4;`
- L180 _public member_ `CFTimeInterval PredictionTime = 0;`

#### struct `FOXRVisionOSSession::FLocateViewInfo`  
`struct FLocateViewInfo`  
_L193-198_
- L195 _public member_ `uint32_t NumViews = 0;`
- L196 _public member_ `simd_float4x4 ViewTransforms[2];`
- L197 _public member_ `XrFovf HmdFovs[2];`

#### struct `FOXRVisionOSSession::FOXRVisionOSHandTracker`  
`struct FOXRVisionOSHandTracker`  
_L266-289_
- L268 _public function_ `FOXRVisionOSHandTracker()`
- L277 _public prototype_ `XrResult XrDestroyHandTrackerEXT();`
- L279 _public prototype_ `XrResult XrLocateHandJointsEXT( const XrHandJointsLocateInfoEXT* locateInfo, XrHandJointLocationsEXT* locations);`
- L283 _public member_ `bool bCreated = false;`
- L284 _public member_ `bool bIsActive = false;`
- L285 _public member_ `ar_hand_anchor_t Anchor;`
- L286 _public member_ `simd_float4x4 HandTransform;`
- L287 _public member_ `simd_float4x4 JointLocalTransforms[XR_HAND_JOINT_COUNT_EXT];`
- L288 _public member_ `XrHandJointLocationEXT JointLocations[XR_HAND_JOINT_COUNT_EXT] = {};`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSSpace.h` (Private)


#### class `FOXRVisionOSSpace`  
`class FOXRVisionOSSpace`  
_L11-57_
- L14 _public prototype_ `static XrResult CreateActionSpace(TSharedPtr<FOXRVisionOSSpace, ESPMode::ThreadSafe>& OutSpace, const XrActionSpaceCreateInfo* createInfo, FOXRVisionOSSession* Session);`
- L15 _public prototype_ `FOXRVisionOSSpace(const XrActionSpaceCreateInfo* createInfo, FOXRVisionOSSession* Session);`
- L16 _public prototype_ `static XrResult CreateReferenceSpace(TSharedPtr<FOXRVisionOSSpace, ESPMode::ThreadSafe>& OutSpace, const XrReferenceSpaceCreateInfo* createInfo, FOXRVisionOSSession* Session);`
- L17 _public prototype_ `FOXRVisionOSSpace(const XrReferenceSpaceCreateInfo* createInfo, FOXRVisionOSSession* Session);`
- L18 _public prototype_ `~FOXRVisionOSSpace();`
- L19 _public prototype_ `XrResult XrDestroySpace();`
- L21 _public prototype_ `XrResult XrLocateSpace( XrSpace baseSpace, XrTime time, XrSpaceLocation* location);`
- L25 _public prototype_ `void GetTransform(XrTime Time, FTransform& OutTransform, XrSpaceLocationFlags& OutLocationFlags, FVector& OutLinearVelocity, FVector& OutAngularVelocity, XrSpaceVelocityFlags& OutVelocityFlags);`
- L26 _public prototype_ `void GetInverseTransform(XrTime DisplayTime, FTransform& OutTransform, XrSpaceLocationFlags& OutLocationFlags, FVector& OutLinearVelocity, FVector& OutAngularVelocity, XrSpaceVelocityFlags& OutVelocityFlags);`
- L28 _public function_ `bool IsReferenceSpace() const`
- L29 _public function_ `XrReferenceSpaceType GetReferenceSpaceType() const`
- L39 _private member_ `const XrPosef XrPosefIdentity = { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } };`
- L41 _private prototype_ `bool IsSpaceRelativeToSameEntity(FOXRVisionOSSpace& OtherSpace) const;`
- L43 _private member_ `bool bCreateFailed = false;`
- L44 _private member_ `FOXRVisionOSSession* Session = nullptr;`
- L47 _private member_ `bool bIsReferenceSpace = false;` — EITHER a reference space
- L48 _private member_ `XrReferenceSpaceType ReferenceSpaceType;`
- L50 _private member_ `XrAction Action = XR_NULL_HANDLE;` — OR an action space
- L51 _private member_ `XrPath SubactionPath = XR_NULL_PATH;`
- L54 _private member_ `XrPosef Pose;` — TODO support recenter past timestamps for 50ms
- L55 _private member_ `FTransform UEPose;`
- L56 _private member_ `FTransform UEPoseInverse;`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSSwapchain.h` (Private)


#### class `FOXRVisionOSSwapchain`  
`class FOXRVisionOSSwapchain`  
_L17-79_
- L37 _public prototype_ `static XrResult Create(TSharedPtr<FOXRVisionOSSwapchain, ESPMode::ThreadSafe>& OutSwapchain, const XrSwapchainCreateInfo* createInfo, uint32 SwapchainLength, FOXRVisionOSSession* Session);`
- L39 _public prototype_ `FOXRVisionOSSwapchain(const XrSwapchainCreateInfo* createInfo, uint32 SwapchainLength, FOXRVisionOSSession* Session);`
- L40 _public prototype_ `~FOXRVisionOSSwapchain();`
- L41 _public prototype_ `XrResult XrDestroySwapchain();`
- L43 _public prototype_ `XrResult XrEnumerateSwapchainImages( uint32_t imageCapacityInput, uint32_t* imageCountOutput, XrSwapchainImageBaseHeader* images);`
- L48 _public prototype_ `XrResult XrAcquireSwapchainImage( const XrSwapchainImageAcquireInfo* acquireInfo, uint32_t* index);`
- L52 _public prototype_ `XrResult XrWaitSwapchainImage( const XrSwapchainImageWaitInfo* waitInfo);`
- L55 _public prototype_ `XrResult XrReleaseSwapchainImage( const XrSwapchainImageReleaseInfo* releaseInfo);`
- L58 _public prototype_ `const FSwapchainImage& GetLastWaitedImage() const;`
- L60 _public prototype_ `const FSwapchainImage& GetLastReleasedImage() const;`
- L64 _private prototype_ `void ReleaseLabel_RHIThread(uint32 ReleaseImageIndex, uint64 LabelValue);` — bool WaitLabel_RHIThread(uint32 AcquireImageIndex);
- L66 _private member_ `XrResult CreateFailureResult = XrResult::XR_SUCCESS;`
- L67 _private member_ `FOXRVisionOSSession* Session = nullptr;`
- L69 _private member_ `XrSwapchainCreateInfo CreateInfo;`
- L71 _private member_ `TArray<FSwapchainImage> Images;`
- L72 _private member_ `uint32_t NextImageToAcquire = 0;`
- L73 _private member_ `uint32_t NextImageToWait = 0;`
- L74 _private member_ `uint32_t NextImageToRelease = 0;`
- L77 _private member_ `TQueue<uint32_t> AcquiredImageQueue;`
- L78 _private member_ `uint32_t OutstandingWaits = 0;`

#### enum `FOXRVisionOSSwapchain::EImageState`  
`enum class EImageState`  
_L20-26_
- L22 _public enumerator_ `Released`
- L23 _public enumerator_ `Aquired`
- L24 _public enumerator_ `Waiting`
- L25 _public enumerator_ `WaitComplete`

#### struct `FOXRVisionOSSwapchain::FSwapchainImage`  
`struct FSwapchainImage`  
_L28-35_
- L30 _public prototype_ `FSwapchainImage(FTextureRHIRef InImage, EImageState InImageState);`
- L31 _public prototype_ `~FSwapchainImage();`
- L33 _public member_ `FTextureRHIRef Image;`
- L34 _public member_ `EImageState ImageState = EImageState::Released;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace MetalRHIOXRVisionOS`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOSTracker.h` (Private)


#### enum `TrackerDeviceType`  
`enum class TrackerDeviceType : int32`  
_L19-24_
- L21 _public enumerator_ `DEVICE_VR_HMD`
- L22 _public enumerator_ `DEVICE_VR_CONTROLLER_LEFT`
- L23 _public enumerator_ `DEVICE_VR_CONTROLLER_RIGHT`

#### class `FOXRVisionOSTracker`  
`class FOXRVisionOSTracker`  
_L26-75_
- L29 _public prototype_ `static bool Create(TSharedPtr<FOXRVisionOSTracker, ESPMode::ThreadSafe>& OutTracker, bool bEnableGaze);`
- L30 _public prototype_ `FOXRVisionOSTracker(bool bEnableGaze);`
- L31 _public prototype_ `~FOXRVisionOSTracker();`
- L33 _public prototype_ `bool RegisterDevice(TrackerDeviceType DeviceType, int32 DeviceHandle);`
- L34 _public prototype_ `bool UnregisterDevice(int32 DeviceHandle);`
- L36 _public prototype_ `bool GetResult(int32 DeviceHandle, XrTime DisplayTime, OXRVisionOS::TrackerResultData& OutResultData);`
- L38 _public prototype_ `bool UpdateReferenceSpaces(FOXRVisionOSInstance* Instance, FOXRVisionOSSession* Session, int32 DeviceHandle, XrTime DisplayTime, int32 FrameNumber);` — bool GetGazeResult(int32 DeviceHandle, XrTime DisplayTime, GazeResult& OutResult, ResultData& OutHmdResult);
- L39 _public prototype_ `bool GetStagePose(OXRVisionOS::TrackerPoseData& OutPoseData) const;` — Get the pose of the stage space in device tracking space.
- L41 _public prototype_ `void GetActionStatePose(EOXRVisionOSControllerButton Button, bool& OutActive);`
- L43 _public prototype_ `void SyncActions(int32 FrameCounter, XrTime PredictedDisplayTime);`
- L46 _private member_ `const int32 RESULT_OK = 0;` — TEMP
- L48 _private member_ `bool bCreateFailed = false;`
- L49 _private member_ `void* TrackingRam = nullptr;`
- L72 _private member_ `TMap< TrackerDeviceType, FDeviceInfo> DeviceInfoMap;`
- L73 _private member_ `mutable FCriticalSection DeviceInfoMapCriticalSection;`
- L74 _private prototype_ `void TryRegisterDevice(TrackerDeviceType DeviceType, FDeviceInfo& Info);`

#### struct `FOXRVisionOSTracker::FDeviceInfo`  
`struct FDeviceInfo`  
_L51-59_
- L53 _public function_ `explicit FDeviceInfo(int32 InHandle) : Handle(InHandle)`
- L57 _public member_ `int32 Handle = -1;`
- L58 _public member_ `bool bIsActive = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace OXRVisionOS`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOS_RenderBridge.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `FOpenXRRenderBridge* CreateRenderBridge_OXRVisionOS(XrInstance InInstance);`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOS/Private/OXRVisionOS_Swapchain.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `FXRSwapChainPtr CreateSwapchain_OXRVisionOS(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding);`
