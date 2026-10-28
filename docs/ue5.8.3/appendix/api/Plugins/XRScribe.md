# Plugins / XRScribe

- module root: `Plugins/Runtime/XR/XRScribe/Source/XRScribe`
- headers: 11; symbols: 1000
- symbol kinds: class=9, enum=3, enumerator=132, function=32, member=309, namespace=19, prototype=429, struct=60, typedef=7
- PrivateDependencyModuleNames: DeveloperSettings, Projects
- PublicDependencyModuleNames: Core, CoreUObject, Engine, OpenXR, OpenXRHMD, RHI

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Private/XRScribeAPIPassthrough.h` (Private)


#### struct `UE::XRScribe::FOpenXRAPIPassthrough`  
`struct FOpenXRAPIPassthrough`  
_L10-88_
- L13 _public member_ `PFN_xrGetInstanceProcAddr GetInstanceProcAddr = nullptr;` — Global
- L14 _public member_ `PFN_xrEnumerateApiLayerProperties EnumerateApiLayerProperties = nullptr;`
- L15 _public member_ `PFN_xrEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties = nullptr;`
- L16 _public member_ `PFN_xrCreateInstance CreateInstance = nullptr;`
- L19 _public member_ `PFN_xrDestroyInstance DestroyInstance = nullptr;` — Instance
- L20 _public member_ `PFN_xrGetInstanceProperties GetInstanceProperties = nullptr;`
- L21 _public member_ `PFN_xrPollEvent PollEvent = nullptr;`
- L22 _public member_ `PFN_xrResultToString ResultToString = nullptr;`
- L23 _public member_ `PFN_xrStructureTypeToString StructureTypeToString = nullptr;`
- L24 _public member_ `PFN_xrGetSystem GetSystem = nullptr;`
- L25 _public member_ `PFN_xrGetSystemProperties GetSystemProperties = nullptr;`
- L26 _public member_ `PFN_xrEnumerateEnvironmentBlendModes EnumerateEnvironmentBlendModes = nullptr;`
- L27 _public member_ `PFN_xrCreateSession CreateSession = nullptr;`
- L28 _public member_ `PFN_xrDestroySession DestroySession = nullptr;`
- L29 _public member_ `PFN_xrEnumerateReferenceSpaces EnumerateReferenceSpaces = nullptr;`
- L30 _public member_ `PFN_xrCreateReferenceSpace CreateReferenceSpace = nullptr;`
- L31 _public member_ `PFN_xrGetReferenceSpaceBoundsRect GetReferenceSpaceBoundsRect = nullptr;`
- L32 _public member_ `PFN_xrCreateActionSpace CreateActionSpace = nullptr;`
- L33 _public member_ `PFN_xrLocateSpace LocateSpace = nullptr;`
- L34 _public member_ `PFN_xrDestroySpace DestroySpace = nullptr;`
- L35 _public member_ `PFN_xrEnumerateViewConfigurations EnumerateViewConfigurations = nullptr;`
- L36 _public member_ `PFN_xrGetViewConfigurationProperties GetViewConfigurationProperties = nullptr;`
- L37 _public member_ `PFN_xrEnumerateViewConfigurationViews EnumerateViewConfigurationViews = nullptr;`
- L38 _public member_ `PFN_xrEnumerateSwapchainFormats EnumerateSwapchainFormats = nullptr;`
- L39 _public member_ `PFN_xrCreateSwapchain CreateSwapchain = nullptr;`
- L40 _public member_ `PFN_xrDestroySwapchain DestroySwapchain = nullptr;`
- L41 _public member_ `PFN_xrEnumerateSwapchainImages EnumerateSwapchainImages = nullptr;`
- L42 _public member_ `PFN_xrAcquireSwapchainImage AcquireSwapchainImage = nullptr;`
- L43 _public member_ `PFN_xrWaitSwapchainImage WaitSwapchainImage = nullptr;`
- L44 _public member_ `PFN_xrReleaseSwapchainImage ReleaseSwapchainImage = nullptr;`
- L45 _public member_ `PFN_xrBeginSession BeginSession = nullptr;`
- L46 _public member_ `PFN_xrEndSession EndSession = nullptr;`
- L47 _public member_ `PFN_xrRequestExitSession RequestExitSession = nullptr;`
- L48 _public member_ `PFN_xrWaitFrame WaitFrame = nullptr;`
- L49 _public member_ `PFN_xrBeginFrame BeginFrame = nullptr;`
- L50 _public member_ `PFN_xrEndFrame EndFrame = nullptr;`
- L51 _public member_ `PFN_xrLocateViews LocateViews = nullptr;`
- L52 _public member_ `PFN_xrStringToPath StringToPath = nullptr;`
- L53 _public member_ `PFN_xrPathToString PathToString = nullptr;`
- L54 _public member_ `PFN_xrCreateActionSet CreateActionSet = nullptr;`
- L55 _public member_ `PFN_xrDestroyActionSet DestroyActionSet = nullptr;`
- L56 _public member_ `PFN_xrCreateAction CreateAction = nullptr;`
- L57 _public member_ `PFN_xrDestroyAction DestroyAction = nullptr;`
- L58 _public member_ `PFN_xrSuggestInteractionProfileBindings SuggestInteractionProfileBindings = nullptr;`
- L59 _public member_ `PFN_xrAttachSessionActionSets AttachSessionActionSets = nullptr;`
- L60 _public member_ `PFN_xrGetCurrentInteractionProfile GetCurrentInteractionProfile = nullptr;`
- L61 _public member_ `PFN_xrGetActionStateBoolean GetActionStateBoolean = nullptr;`
- L62 _public member_ `PFN_xrGetActionStateFloat GetActionStateFloat = nullptr;`
- L63 _public member_ `PFN_xrGetActionStateVector2f GetActionStateVector2f = nullptr;`
- L64 _public member_ `PFN_xrGetActionStatePose GetActionStatePose = nullptr;`
- L65 _public member_ `PFN_xrSyncActions SyncActions = nullptr;`
- L66 _public member_ `PFN_xrEnumerateBoundSourcesForAction EnumerateBoundSourcesForAction = nullptr;`
- L67 _public member_ `PFN_xrGetInputSourceLocalizedName GetInputSourceLocalizedName = nullptr;`
- L68 _public member_ `PFN_xrApplyHapticFeedback ApplyHapticFeedback = nullptr;`
- L69 _public member_ `PFN_xrStopHapticFeedback StopHapticFeedback = nullptr;`
- L73 _public member_ `PFN_xrInitializeLoaderKHR InitializeLoaderKHR = nullptr;` — Global extensions XR_KHR_loader_init
- L78 _public member_ `PFN_xrGetVisibilityMaskKHR GetVisibilityMaskKHR = nullptr;` — XR_KHR_visibility_mask
- L81 _public member_ `PFN_xrGetD3D11GraphicsRequirementsKHR GetD3D11GraphicsRequirementsKHR = nullptr;` — XR_KHR_D3D11_enable
- L85 _public member_ `PFN_xrGetD3D12GraphicsRequirementsKHR GetD3D12GraphicsRequirementsKHR = nullptr;` — XR_KHR_D3D12_enable

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Private/XRScribeModule.h` (Private)


#### class `FXRScribeModule`  
`class FXRScribeModule : public IModuleInterface, public IOpenXRExtensionPlugin`  
_L10-39_
- inherits: `IModuleInterface,IOpenXRExtensionPlugin`
- L16 _public prototype_ `virtual void StartupModule() override;` — /
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `virtual FString GetDisplayName() override;` — /
- L23 _public prototype_ `virtual bool InsertOpenXRAPILayer(PFN_xrGetInstanceProcAddr& InOutGetProcAddr) override;`
- L28 _public prototype_ `static FXRScribeModule* Get();` — /
- L31 _private function_ `static FName GetFeatureName()`
- L38 _private member_ `PFN_xrGetInstanceProcAddr ChainedGetProcAddr = nullptr;`

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeAPIDecoder.h` (Public)


#### class `UE::XRScribe::FOpenXRCaptureDecoder`  
`class FOpenXRCaptureDecoder`  
_L17-186_
- L20 _public prototype_ `explicit FOpenXRCaptureDecoder();`
- L21 _public prototype_ `~FOpenXRCaptureDecoder();`
- L23 _public prototype_ `bool DecodeDataFromMemory();`
- L26 _public function_ `[[nodiscard]] const TArray<XrExtensionProperties>& GetInstanceExtensionProperties()` — state accessors
- L27 _public function_ `[[nodiscard]] const TArray<XrApiLayerProperties>& GetApiLayerProperties()`
- L28 _public function_ `[[nodiscard]] XrInstanceCreateFlags GetInstanceCreateFlags()`
- L29 _public function_ `[[nodiscard]] const TArray<TStaticArray<ANSICHAR, XR_MAX_API_LAYER_NAME_SIZE>>& GetRequestedApiLayerNames()`
- L30 _public function_ `[[nodiscard]] const TArray<TStaticArray<ANSICHAR, XR_MAX_EXTENSION_NAME_SIZE>>& GetRequestedExtensionNames()`
- L31 _public function_ `[[nodiscard]] const XrInstanceProperties& GetInstanceProperties()`
- L32 _public function_ `[[nodiscard]] const XrSystemGetInfo& GetSystemInfo()`
- L33 _public function_ `[[nodiscard]] const XrSystemProperties& GetSystemProperties()`
- L34 _public function_ `[[nodiscard]] const TArray<XrEnvironmentBlendMode>& GetEnvironmentBlendModes()`
- L35 _public function_ `[[nodiscard]] const TArray<XrViewConfigurationType>& GetViewConfigurationTypes()`
- L36 _public function_ `[[nodiscard]] const TMap<XrViewConfigurationType, XrViewConfigurationProperties>& GetViewConfigurationProperties()`
- L37 _public function_ `[[nodiscard]] const TMap<XrViewConfigurationType, TArray<XrViewConfigurationView>>& GetViewConfigurationViews()`
- L38 _public function_ `[[nodiscard]] const TMap<XrViewConfigurationType, TArray<FOpenXRLocateViewsPacket>>& GetViewLocations()`
- L39 _public function_ `[[nodiscard]] const TArray<FOpenXRCreateReferenceSpacePacket>& GetCreatedReferenceSpaces()`
- L40 _public function_ `[[nodiscard]] const TArray<FOpenXRCreateActionSpacePacket>& GetCreatedActionSpaces()`
- L41 _public function_ `[[nodiscard]] const TMap<XrSpace, TArray<FOpenXRLocateSpacePacket>>& GetSpaceLocations()`
- L42 _public function_ `[[nodiscard]] const TArray<XrReferenceSpaceType>& GetReferenceSpaceTypes()`
- L43 _public function_ `[[nodiscard]] const TMap<XrReferenceSpaceType, XrExtent2Df>& GetReferenceSpaceBounds()`
- L44 _public function_ `[[nodiscard]] const TArray<int64>& GetSwapchainFormats()`
- L45 _public function_ `[[nodiscard]] const TArray<FOpenXRCreateActionPacket>& GetCreatedActions()`
- L46 _public function_ `[[nodiscard]] const TArray<FOpenXRWaitFramePacket>& GetWaitFrames()`
- L47 _public function_ `[[nodiscard]] const TArray<FOpenXRSyncActionsPacket>& GetSyncActions()`
- L48 _public function_ `[[nodiscard]] const TMap<XrAction, TArray<FOpenXRGetActionStateBooleanPacket>>& GetBooleanActionStates()`
- L49 _public function_ `[[nodiscard]] const TMap<XrAction, TArray<FOpenXRGetActionStateFloatPacket>>& GetFloatActionStates()`
- L50 _public function_ `[[nodiscard]] const TMap<XrAction, TArray<FOpenXRGetActionStateVector2fPacket>>& GetVectorActionStates()`
- L51 _public function_ `[[nodiscard]] const TMap<XrAction, TArray<FOpenXRGetActionStatePosePacket>>& GetPoseActionStates()`
- L52 _public function_ `[[nodiscard]] const TMap<XrPath, FName>& GetPathToStringMap()`
- L54 _public function_ `TArray<uint8>& GetEncodedData()`
- L62 _protected prototype_ `bool DecodeEnumerateApiLayerProperties(const FOpenXRAPIPacketBase& BasePacket);` — packet decoders
- L63 _protected prototype_ `bool DecodeEnumerateInstanceExtensionProperties(const FOpenXRAPIPacketBase& BasePacket);`
- L64 _protected prototype_ `bool DecodeCreateInstance(const FOpenXRAPIPacketBase& BasePacket);`
- L65 _protected prototype_ `bool DecodeDestroyInstance(const FOpenXRAPIPacketBase& BasePacket);`
- L66 _protected prototype_ `bool DecodeGetInstanceProperties(const FOpenXRAPIPacketBase& BasePacket);`
- L70 _protected prototype_ `bool DecodeGetSystem(const FOpenXRAPIPacketBase& BasePacket);` — bool DecodePollEvent(const FOpenXRAPIPacketBase& BasePacket); bool DecodeResultToString(const FOpenXRAPIPacketBase& BasePacket); bool DecodeStructureTypeToString(const FOpenXRAPIPacketBase& BasePacket);
- L71 _protected prototype_ `bool DecodeGetSystemProperties(const FOpenXRAPIPacketBase& BasePacket);`
- L72 _protected prototype_ `bool DecodeEnumerateEnvironmentBlendModes(const FOpenXRAPIPacketBase& BasePacket);`
- L73 _protected prototype_ `bool DecodeCreateSession(const FOpenXRAPIPacketBase& BasePacket);`
- L74 _protected prototype_ `bool DecodeDestroySession(const FOpenXRAPIPacketBase& BasePacket);`
- L75 _protected prototype_ `bool DecodeEnumerateReferenceSpaces(const FOpenXRAPIPacketBase& BasePacket);`
- L76 _protected prototype_ `bool DecodeCreateReferenceSpace(const FOpenXRAPIPacketBase& BasePacket);`
- L77 _protected prototype_ `bool DecodeGetReferenceSpaceBoundsRect(const FOpenXRAPIPacketBase& BasePacket);`
- L78 _protected prototype_ `bool DecodeCreateActionSpace(const FOpenXRAPIPacketBase& BasePacket);`
- L79 _protected prototype_ `bool DecodeLocateSpace(const FOpenXRAPIPacketBase& BasePacket);`
- L80 _protected prototype_ `bool DecodeDestroySpace(const FOpenXRAPIPacketBase& BasePacket);`
- L81 _protected prototype_ `bool DecodeEnumerateViewConfigurations(const FOpenXRAPIPacketBase& BasePacket);`
- L82 _protected prototype_ `bool DecodeGetViewConfigurationProperties(const FOpenXRAPIPacketBase& BasePacket);`
- L83 _protected prototype_ `bool DecodeEnumerateViewConfigurationViews(const FOpenXRAPIPacketBase& BasePacket);`
- L84 _protected prototype_ `bool DecodeEnumerateSwapchainFormats(const FOpenXRAPIPacketBase& BasePacket);`
- L85 _protected prototype_ `bool DecodeCreateSwapchain(const FOpenXRAPIPacketBase& BasePacket);`
- L86 _protected prototype_ `bool DecodeDestroySwapchain(const FOpenXRAPIPacketBase& BasePacket);`
- L87 _protected prototype_ `bool DecodeEnumerateSwapchainImages(const FOpenXRAPIPacketBase& BasePacket);`
- L88 _protected prototype_ `bool DecodeAcquireSwapchainImage(const FOpenXRAPIPacketBase& BasePacket);`
- L89 _protected prototype_ `bool DecodeWaitSwapchainImage(const FOpenXRAPIPacketBase& BasePacket);`
- L90 _protected prototype_ `bool DecodeReleaseSwapchainImage(const FOpenXRAPIPacketBase& BasePacket);`
- L91 _protected prototype_ `bool DecodeBeginSession(const FOpenXRAPIPacketBase& BasePacket);`
- L92 _protected prototype_ `bool DecodeEndSession(const FOpenXRAPIPacketBase& BasePacket);`
- L93 _protected prototype_ `bool DecodeRequestExitSession(const FOpenXRAPIPacketBase& BasePacket);`
- L94 _protected prototype_ `bool DecodeWaitFrame(const FOpenXRAPIPacketBase& BasePacket);`
- L95 _protected prototype_ `bool DecodeBeginFrame(const FOpenXRAPIPacketBase& BasePacket);`
- L96 _protected prototype_ `bool DecodeEndFrame(const FOpenXRAPIPacketBase& BasePacket);`
- L97 _protected prototype_ `bool DecodeLocateViews(const FOpenXRAPIPacketBase& BasePacket);`
- L98 _protected prototype_ `bool DecodeStringToPath(const FOpenXRAPIPacketBase& BasePacket);`
- L99 _protected prototype_ `bool DecodePathToString(const FOpenXRAPIPacketBase& BasePacket);`
- L100 _protected prototype_ `bool DecodeCreateActionSet(const FOpenXRAPIPacketBase& BasePacket);`
- L101 _protected prototype_ `bool DecodeDestroyActionSet(const FOpenXRAPIPacketBase& BasePacket);`
- L102 _protected prototype_ `bool DecodeCreateAction(const FOpenXRAPIPacketBase& BasePacket);`
- L103 _protected prototype_ `bool DecodeDestroyAction(const FOpenXRAPIPacketBase& BasePacket);`
- L105 _protected prototype_ `bool DecodeSuggestInteractionProfileBindings(const FOpenXRAPIPacketBase& BasePacket);`
- L106 _protected prototype_ `bool DecodeAttachSessionActionSets(const FOpenXRAPIPacketBase& BasePacket);`
- L107 _protected prototype_ `bool DecodeGetCurrentInteractionProfile(const FOpenXRAPIPacketBase& BasePacket);`
- L108 _protected prototype_ `bool DecodeGetActionStateBoolean(const FOpenXRAPIPacketBase& BasePacket);`
- L109 _protected prototype_ `bool DecodeGetActionStateFloat(const FOpenXRAPIPacketBase& BasePacket);`
- L110 _protected prototype_ `bool DecodeGetActionStateVector2f(const FOpenXRAPIPacketBase& BasePacket);`
- L111 _protected prototype_ `bool DecodeGetActionStatePose(const FOpenXRAPIPacketBase& BasePacket);`
- L112 _protected prototype_ `bool DecodeSyncActions(const FOpenXRAPIPacketBase& BasePacket);`
- L116 _protected prototype_ `bool DecodeApplyHapticFeedback(const FOpenXRAPIPacketBase& BasePacket);`
- L117 _protected prototype_ `bool DecodeStopHapticFeedback(const FOpenXRAPIPacketBase& BasePacket);`
- L118 _protected prototype_ `bool DecodeInitializeLoaderKHR(const FOpenXRAPIPacketBase& BasePacket);`
- L119 _protected prototype_ `bool DecodeGetVisibilityMaskKHR(const FOpenXRAPIPacketBase& BasePacket);`
- L121 _protected prototype_ `bool DecodeGetD3D11GraphicsRequirementsKHR(const FOpenXRAPIPacketBase& BasePacket);`
- L124 _protected prototype_ `bool DecodeGetD3D12GraphicsRequirementsKHR(const FOpenXRAPIPacketBase& BasePacket);`
- L127 _protected member_ `FArrayReader EncodedData;`
- L129 _protected typedef_ `typedef bool(FOpenXRCaptureDecoder::* ApiDecodeFn)(const FOpenXRAPIPacketBase& BasePacket);`
- L130 _protected member_ `TStaticArray<ApiDecodeFn, (uint32)EOpenXRAPIPacketId::NumValidAPIPacketIds> DecodeFnTable;`
- L134 _protected member_ `TArray<XrExtensionProperties> InstanceExtensionProperties;`
- L135 _protected member_ `TArray<XrApiLayerProperties> ApiLayerProperties;`
- L138 _protected member_ `XrInstanceCreateFlags ValidInstanceCreateFlags = 0;`
- L139 _protected member_ `TArray<TStaticArray<ANSICHAR, XR_MAX_API_LAYER_NAME_SIZE>> RequestedLayerNames;`
- L140 _protected member_ `TArray<TStaticArray<ANSICHAR, XR_MAX_EXTENSION_NAME_SIZE>> RequestedExtensionNames;`
- L142 _protected member_ `XrInstanceProperties InstanceProperties = {};`
- L144 _protected member_ `XrSystemGetInfo SystemGetInfo = {};`
- L145 _protected member_ `XrSystemProperties SystemProperties = {};`
- L146 _protected member_ `TArray<XrEnvironmentBlendMode> EnvironmentBlendModes;`
- L148 _protected member_ `XrSessionCreateInfo SessionCreateInfo = {};`
- L150 _protected member_ `TArray<XrReferenceSpaceType> ReferenceSpaceTypes;`
- L151 _protected member_ `TMap<XrReferenceSpaceType, XrExtent2Df> ReferenceSpaceBounds;`
- L152 _protected member_ `TMap<XrSpace, XrReferenceSpaceType> ReferenceSpaceMap;`
- L153 _protected member_ `TArray<FOpenXRCreateReferenceSpacePacket> CreatedReferenceSpaces;`
- L155 _protected member_ `TArray<FOpenXRCreateActionSpacePacket> CreatedActionSpaces;`
- L156 _protected member_ `TMap<XrSpace, XrAction> ActionSpaceMap;`
- L158 _protected member_ `TMap<XrSpace, TArray<FOpenXRLocateSpacePacket>> SpaceLocations;`
- L160 _protected member_ `TArray<XrViewConfigurationType> ViewConfigurationTypes;`
- L161 _protected member_ `TMap<XrViewConfigurationType, XrViewConfigurationProperties> ViewConfigurationProperties;`
- L162 _protected member_ `TMap<XrViewConfigurationType, TArray<XrViewConfigurationView>> ViewConfigurationViews;`
- L164 _protected member_ `TArray<int64> SwapchainFormats;`
- L166 _protected member_ `TMap<XrViewConfigurationType, TArray<FOpenXRLocateViewsPacket>> ViewLocations;`
- L168 _protected member_ `TMap<XrPath, FName> PathToStringMap;`
- L169 _protected member_ `TMap<FName, TArray<XrActionSuggestedBinding>> StringToSuggestedBindingsMap;`
- L171 _protected member_ `TArray<FOpenXRCreateActionPacket> CreatedActions;`
- L173 _protected member_ `TArray<FOpenXRWaitFramePacket> WaitFrames;`
- L175 _protected member_ `TArray<FOpenXRSyncActionsPacket> SyncActions;`
- L177 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStateBooleanPacket>> BooleanActionStates;`
- L178 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStateFloatPacket>> FloatActionStates;`
- L179 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStateVector2fPacket>> VectorActionStates;`
- L180 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStatePosePacket>> PoseActionStates;`

#### Free symbols / members of external scopes

- L12 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogXRScribeEmulate, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeAPIEncoder.h` (Public)


#### class `UE::XRScribe::FOpenXRCaptureEncoder`  
`class FOpenXRCaptureEncoder : public TBufferArchive<32>`  
_L14-112_
- inherits: `TBufferArchive<32>`
- L17 _public prototype_ `FOpenXRCaptureEncoder();`
- L18 _public prototype_ `~FOpenXRCaptureEncoder();`
- L23 _public prototype_ `void EncodeEnumerateApiLayerProperties(const XrResult Result, const uint32_t propertyCapacityInput, const uint32_t* propertyCountOutput, const XrApiLayerProperties* properties);` — Global
- L24 _public prototype_ `void EncodeEnumerateInstanceExtensionProperties(const XrResult Result, const char* layerName, const uint32_t propertyCapacityInput, const uint32_t* propertyCountOutput, const XrExtensionProperties* properties);`
- L25 _public prototype_ `void EncodeCreateInstance(const XrResult Result, const XrInstanceCreateInfo* createInfo, const XrInstance* instance);`
- L28 _public prototype_ `void EncodeDestroyInstance(const XrResult Result, const XrInstance instance);` — Instance
- L29 _public prototype_ `void EncodeGetInstanceProperties(const XrResult Result, const XrInstance instance, const XrInstanceProperties* instanceProperties);`
- L31 _public prototype_ `void EncodePollEvent(const XrResult Result, const XrInstance instance, const XrEventDataBuffer* eventData);`
- L33 _public prototype_ `void EncodeResultToString(const XrResult Result, const XrInstance instance, const XrResult value, const char buffer[XR_MAX_RESULT_STRING_SIZE]);`
- L34 _public prototype_ `void EncodeStructureTypeToString(const XrResult Result, const XrInstance instance, const XrStructureType value, const char buffer[XR_MAX_STRUCTURE_NAME_SIZE]);`
- L36 _public prototype_ `void EncodeGetSystem(const XrResult Result, const XrInstance instance, const XrSystemGetInfo* getInfo, const XrSystemId* systemId);`
- L37 _public prototype_ `void EncodeGetSystemProperties(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const XrSystemProperties* properties);`
- L38 _public prototype_ `void EncodeEnumerateEnvironmentBlendModes(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const XrViewConfigurationType viewConfigurationType, const uint32_t environmentBlendModeCapacityInput, const uint32_t* environmentBlendModeCountOutput, const XrEnvironmentBlendMode* environmentBlendModes);`
- L40 _public prototype_ `void EncodeCreateSession(const XrResult Result, const XrInstance instance, const XrSessionCreateInfo* createInfo, const XrSession* session);`
- L41 _public prototype_ `void EncodeDestroySession(const XrResult Result, const XrSession session);`
- L43 _public prototype_ `void EncodeEnumerateReferenceSpaces(const XrResult Result, const XrSession session, const uint32_t spaceCapacityInput, const uint32_t* spaceCountOutput, const XrReferenceSpaceType* spaces);`
- L44 _public prototype_ `void EncodeCreateReferenceSpace(const XrResult Result, const XrSession session, const XrReferenceSpaceCreateInfo* createInfo, const XrSpace* space);`
- L45 _public prototype_ `void EncodeGetReferenceSpaceBoundsRect(const XrResult Result, const XrSession session, const XrReferenceSpaceType referenceSpaceType, const XrExtent2Df* bounds);`
- L46 _public prototype_ `void EncodeCreateActionSpace(const XrResult Result, const XrSession session, const XrActionSpaceCreateInfo* createInfo, const XrSpace* space);`
- L47 _public prototype_ `void EncodeLocateSpace(const XrResult Result, const XrSpace space, const XrSpace baseSpace, const XrTime time, const XrSpaceLocation* location);`
- L48 _public prototype_ `void EncodeDestroySpace(const XrResult Result, const XrSpace space);`
- L50 _public prototype_ `void EncodeEnumerateViewConfigurations(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const uint32_t viewConfigurationTypeCapacityInput, const uint32_t* viewConfigurationTypeCountOutput, const XrViewConfigurationType* viewConfigurationTypes);`
- L51 _public prototype_ `void EncodeGetViewConfigurationProperties(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const XrViewConfigurationType viewConfigurationType, const XrViewConfigurationProperties* configurationProperties);`
- L52 _public prototype_ `void EncodeEnumerateViewConfigurationViews(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const XrViewConfigurationType viewConfigurationType, const uint32_t viewCapacityInput, const uint32_t* viewCountOutput, const XrViewConfigurationView* views);`
- L54 _public prototype_ `void EncodeEnumerateSwapchainFormats(const XrResult Result, const XrSession session, const uint32_t formatCapacityInput, const uint32_t* formatCountOutput, int64_t* formats);`
- L55 _public prototype_ `void EncodeCreateSwapchain(const XrResult Result, const XrSession session, const XrSwapchainCreateInfo* createInfo, const XrSwapchain* swapchain);`
- L56 _public prototype_ `void EncodeDestroySwapchain(const XrResult Result, const XrSwapchain swapchain);`
- L57 _public prototype_ `void EncodeEnumerateSwapchainImages(const XrResult Result, const XrSwapchain swapchain, const uint32_t imageCapacityInput, const uint32_t* imageCountOutput, const XrSwapchainImageBaseHeader* images);`
- L58 _public prototype_ `void EncodeAcquireSwapchainImage(const XrResult Result, const XrSwapchain swapchain, const XrSwapchainImageAcquireInfo* acquireInfo, const uint32_t* index);`
- L59 _public prototype_ `void EncodeWaitSwapchainImage(const XrResult Result, const XrSwapchain swapchain, const XrSwapchainImageWaitInfo* waitInfo);`
- L60 _public prototype_ `void EncodeReleaseSwapchainImage(const XrResult Result, const XrSwapchain swapchain, const XrSwapchainImageReleaseInfo* releaseInfo);`
- L62 _public prototype_ `void EncodeBeginSession(const XrResult Result, const XrSession session, const XrSessionBeginInfo* beginInfo);`
- L63 _public prototype_ `void EncodeEndSession(const XrResult Result, const XrSession session);`
- L64 _public prototype_ `void EncodeRequestExitSession(const XrResult Result, const XrSession session);`
- L66 _public prototype_ `void EncodeWaitFrame(const XrResult Result, const XrSession session, const XrFrameWaitInfo* frameWaitInfo, const XrFrameState* frameState);`
- L67 _public prototype_ `void EncodeBeginFrame(const XrResult Result, const XrSession session, const XrFrameBeginInfo* frameBeginInfo);`
- L68 _public prototype_ `void EncodeEndFrame(const XrResult Result, const XrSession session, const XrFrameEndInfo* frameEndInfo);`
- L69 _public prototype_ `void EncodeLocateViews(const XrResult Result, const XrSession session, const XrViewLocateInfo* viewLocateInfo, const XrViewState* viewState, const uint32_t viewCapacityInput, const uint32_t* viewCountOutput, const XrView* views);`
- L71 _public prototype_ `void EncodeStringToPath(const XrResult Result, const XrInstance instance, const char* pathString, const XrPath* path);`
- L72 _public prototype_ `void EncodePathToString(const XrResult Result, const XrInstance instance, const XrPath path, const uint32_t bufferCapacityInput, const uint32_t* bufferCountOutput, const char* buffer);`
- L74 _public prototype_ `void EncodeCreateActionSet(const XrResult Result, const XrInstance instance, const XrActionSetCreateInfo* createInfo, const XrActionSet* actionSet);`
- L75 _public prototype_ `void EncodeDestroyActionSet(const XrResult Result, const XrActionSet actionSet);`
- L76 _public prototype_ `void EncodeCreateAction(const XrResult Result, const XrActionSet actionSet, const XrActionCreateInfo* createInfo, const XrAction* action);`
- L77 _public prototype_ `void EncodeDestroyAction(const XrResult Result, const XrAction action);`
- L79 _public prototype_ `void EncodeSuggestInteractionProfileBindings(const XrResult Result, const XrInstance instance, const XrInteractionProfileSuggestedBinding* suggestedBindings);`
- L80 _public prototype_ `void EncodeAttachSessionActionSets(const XrResult Result, const XrSession session, const XrSessionActionSetsAttachInfo* attachInfo);`
- L81 _public prototype_ `void EncodeGetCurrentInteractionProfile(const XrResult Result, const XrSession session, const XrPath topLevelUserPath, const XrInteractionProfileState* interactionProfile);`
- L83 _public prototype_ `void EncodeGetActionStateBoolean(const XrResult Result, const XrSession session, const XrActionStateGetInfo* getInfo, const XrActionStateBoolean* state);`
- L84 _public prototype_ `void EncodeGetActionStateFloat(const XrResult Result, const XrSession session, const XrActionStateGetInfo* getInfo, const XrActionStateFloat* state);`
- L85 _public prototype_ `void EncodeGetActionStateVector2f(const XrResult Result, const XrSession session, const XrActionStateGetInfo* getInfo, const XrActionStateVector2f* state);`
- L86 _public prototype_ `void EncodeGetActionStatePose(const XrResult Result, const XrSession session, const XrActionStateGetInfo* getInfo, const XrActionStatePose* state);`
- L87 _public prototype_ `void EncodeSyncActions(const XrResult Result, const XrSession session, const XrActionsSyncInfo* syncInfo);`
- L89 _public prototype_ `void EncodeEnumerateBoundSourcesForAction(const XrResult Result, const XrSession session, const XrBoundSourcesForActionEnumerateInfo* enumerateInfo, const uint32_t sourceCapacityInput, const uint32_t* sourceCountOutput, const XrPath* sources);`
- L90 _public prototype_ `void EncodeGetInputSourceLocalizedName(const XrResult Result, const XrSession session, const XrInputSourceLocalizedNameGetInfo* getInfo, const uint32_t bufferCapacityInput, const uint32_t* bufferCountOutput, const char* buffer);`
- L92 _public prototype_ `void EncodeApplyHapticFeedback(const XrResult Result, const XrSession session, const XrHapticActionInfo* hapticActionInfo, const XrHapticBaseHeader* hapticFeedback);`
- L93 _public prototype_ `void EncodeStopHapticFeedback(const XrResult Result, const XrSession session, const XrHapticActionInfo* hapticActionInfo);`
- L95 _public prototype_ `void EncodeInitializeLoaderKHR(const XrResult Result, const XrLoaderInitInfoBaseHeaderKHR* loaderInitInfo);`
- L97 _public prototype_ `void EncodeGetVisibilityMaskKHR(const XrResult Result, const XrSession session, const XrViewConfigurationType viewConfigurationType, const uint32_t viewIndex, const XrVisibilityMaskTypeKHR visibilityMaskType, const XrVisibilityMaskKHR* visibilityMask);`
- L100 _public prototype_ `void EncodeGetD3D11GraphicsRequirementsKHR(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const XrGraphicsRequirementsD3D11KHR* graphicsRequirements);`
- L103 _public prototype_ `void EncodeGetD3D12GraphicsRequirementsKHR(const XrResult Result, const XrInstance instance, const XrSystemId systemId, const XrGraphicsRequirementsD3D12KHR* graphicsRequirements);`
- L109 _protected prototype_ `template <typename PacketType> void WritePacketData(PacketType& Data);`
- L111 _protected member_ `FRWLock CaptureWriteMutex;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeAPILayer.h` (Public)


#### class `UE::XRScribe::IOpenXRAPILayer`  
`class IOpenXRAPILayer`  
_L11-121_
- L18 _public function_ `virtual ~IOpenXRAPILayer()`
- L19 _public function_ `virtual void SetChainedGetProcAddr(PFN_xrGetInstanceProcAddr InChainedGetProcAddr)`
- L20 _public prototype_ `virtual bool SupportsInstanceExtension(const ANSICHAR* ExtensionName) = 0;`
- L28 _public prototype_ `virtual XrResult XrLayerEnumerateApiLayerProperties(uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrApiLayerProperties* properties) = 0;` — Global
- L29 _public prototype_ `virtual XrResult XrLayerEnumerateInstanceExtensionProperties(const char* layerName, uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrExtensionProperties* properties) = 0;`
- L30 _public prototype_ `virtual XrResult XrLayerCreateInstance(const XrInstanceCreateInfo* createInfo, XrInstance* instance) = 0;`
- L33 _public prototype_ `virtual XrResult XrLayerDestroyInstance(XrInstance instance) = 0;` — Instance
- L34 _public prototype_ `virtual XrResult XrLayerGetInstanceProperties(XrInstance instance, XrInstanceProperties* instanceProperties) = 0;`
- L35 _public prototype_ `virtual XrResult XrLayerPollEvent(XrInstance instance, XrEventDataBuffer* eventData) = 0;`
- L36 _public prototype_ `virtual XrResult XrLayerResultToString(XrInstance instance, XrResult value, char buffer[XR_MAX_RESULT_STRING_SIZE]) = 0;`
- L37 _public prototype_ `virtual XrResult XrLayerStructureTypeToString(XrInstance instance, XrStructureType value, char buffer[XR_MAX_STRUCTURE_NAME_SIZE]) = 0;`
- L38 _public prototype_ `virtual XrResult XrLayerGetSystem(XrInstance instance, const XrSystemGetInfo* getInfo, XrSystemId* systemId) = 0;`
- L39 _public prototype_ `virtual XrResult XrLayerGetSystemProperties(XrInstance instance, XrSystemId systemId, XrSystemProperties* properties) = 0;`
- L40 _public prototype_ `virtual XrResult XrLayerEnumerateEnvironmentBlendModes(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t environmentBlendModeCapacityInput, uint32_t* environmentBlendModeCountOutput, XrEnvironmentBlendMode* environmentBlendModes) = 0;`
- L41 _public prototype_ `virtual XrResult XrLayerCreateSession(XrInstance instance, const XrSessionCreateInfo* createInfo, XrSession* session) = 0;`
- L42 _public prototype_ `virtual XrResult XrLayerDestroySession(XrSession session) = 0;`
- L43 _public prototype_ `virtual XrResult XrLayerEnumerateReferenceSpaces(XrSession session, uint32_t spaceCapacityInput, uint32_t* spaceCountOutput, XrReferenceSpaceType* spaces) = 0;`
- L44 _public prototype_ `virtual XrResult XrLayerCreateReferenceSpace(XrSession session, const XrReferenceSpaceCreateInfo* createInfo, XrSpace* space) = 0;`
- L45 _public prototype_ `virtual XrResult XrLayerGetReferenceSpaceBoundsRect(XrSession session, XrReferenceSpaceType referenceSpaceType, XrExtent2Df* bounds) = 0;`
- L46 _public prototype_ `virtual XrResult XrLayerCreateActionSpace(XrSession session, const XrActionSpaceCreateInfo* createInfo, XrSpace* space) = 0;`
- L47 _public prototype_ `virtual XrResult XrLayerLocateSpace(XrSpace space, XrSpace baseSpace, XrTime time, XrSpaceLocation* location) = 0;`
- L48 _public prototype_ `virtual XrResult XrLayerDestroySpace(XrSpace space) = 0;`
- L49 _public prototype_ `virtual XrResult XrLayerEnumerateViewConfigurations(XrInstance instance, XrSystemId systemId, uint32_t viewConfigurationTypeCapacityInput, uint32_t* viewConfigurationTypeCountOutput, XrViewConfigurationType* viewConfigurationTypes) = 0;`
- L50 _public prototype_ `virtual XrResult XrLayerGetViewConfigurationProperties(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, XrViewConfigurationProperties* configurationProperties) = 0;`
- L51 _public prototype_ `virtual XrResult XrLayerEnumerateViewConfigurationViews(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrViewConfigurationView* views) = 0;`
- L52 _public prototype_ `virtual XrResult XrLayerEnumerateSwapchainFormats(XrSession session, uint32_t formatCapacityInput, uint32_t* formatCountOutput, int64_t* formats) = 0;`
- L53 _public prototype_ `virtual XrResult XrLayerCreateSwapchain(XrSession session, const XrSwapchainCreateInfo* createInfo, XrSwapchain* swapchain) = 0;`
- L54 _public prototype_ `virtual XrResult XrLayerDestroySwapchain(XrSwapchain swapchain) = 0;`
- L55 _public prototype_ `virtual XrResult XrLayerEnumerateSwapchainImages(XrSwapchain swapchain, uint32_t imageCapacityInput, uint32_t* imageCountOutput, XrSwapchainImageBaseHeader* images) = 0;`
- L56 _public prototype_ `virtual XrResult XrLayerAcquireSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageAcquireInfo* acquireInfo, uint32_t* index) = 0;`
- L57 _public prototype_ `virtual XrResult XrLayerWaitSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageWaitInfo* waitInfo) = 0;`
- L58 _public prototype_ `virtual XrResult XrLayerReleaseSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageReleaseInfo* releaseInfo) = 0;`
- L59 _public prototype_ `virtual XrResult XrLayerBeginSession(XrSession session, const XrSessionBeginInfo* beginInfo) = 0;`
- L60 _public prototype_ `virtual XrResult XrLayerEndSession(XrSession session) = 0;`
- L61 _public prototype_ `virtual XrResult XrLayerRequestExitSession(XrSession session) = 0;`
- L62 _public prototype_ `virtual XrResult XrLayerWaitFrame(XrSession session, const XrFrameWaitInfo* frameWaitInfo, XrFrameState* frameState) = 0;`
- L63 _public prototype_ `virtual XrResult XrLayerBeginFrame(XrSession session, const XrFrameBeginInfo* frameBeginInfo) = 0;`
- L64 _public prototype_ `virtual XrResult XrLayerEndFrame(XrSession session, const XrFrameEndInfo* frameEndInfo) = 0;`
- L65 _public prototype_ `virtual XrResult XrLayerLocateViews(XrSession session, const XrViewLocateInfo* viewLocateInfo, XrViewState* viewState, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrView* views) = 0;`
- L66 _public prototype_ `virtual XrResult XrLayerStringToPath(XrInstance instance, const char* pathString, XrPath* path) = 0;`
- L67 _public prototype_ `virtual XrResult XrLayerPathToString(XrInstance instance, XrPath path, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer) = 0;`
- L68 _public prototype_ `virtual XrResult XrLayerCreateActionSet(XrInstance instance, const XrActionSetCreateInfo* createInfo, XrActionSet* actionSet) = 0;`
- L69 _public prototype_ `virtual XrResult XrLayerDestroyActionSet(XrActionSet actionSet) = 0;`
- L70 _public prototype_ `virtual XrResult XrLayerCreateAction(XrActionSet actionSet, const XrActionCreateInfo* createInfo, XrAction* action) = 0;`
- L71 _public prototype_ `virtual XrResult XrLayerDestroyAction(XrAction action) = 0;`
- L72 _public prototype_ `virtual XrResult XrLayerSuggestInteractionProfileBindings(XrInstance instance, const XrInteractionProfileSuggestedBinding* suggestedBindings) = 0;`
- L73 _public prototype_ `virtual XrResult XrLayerAttachSessionActionSets(XrSession session, const XrSessionActionSetsAttachInfo* attachInfo) = 0;`
- L74 _public prototype_ `virtual XrResult XrLayerGetCurrentInteractionProfile(XrSession session, XrPath topLevelUserPath, XrInteractionProfileState* interactionProfile) = 0;`
- L75 _public prototype_ `virtual XrResult XrLayerGetActionStateBoolean(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateBoolean* state) = 0;`
- L76 _public prototype_ `virtual XrResult XrLayerGetActionStateFloat(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateFloat* state) = 0;`
- L77 _public prototype_ `virtual XrResult XrLayerGetActionStateVector2f(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateVector2f* state) = 0;`
- L78 _public prototype_ `virtual XrResult XrLayerGetActionStatePose(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStatePose* state) = 0;`
- L79 _public prototype_ `virtual XrResult XrLayerSyncActions(XrSession session, const XrActionsSyncInfo* syncInfo) = 0;`
- L80 _public prototype_ `virtual XrResult XrLayerEnumerateBoundSourcesForAction(XrSession session, const XrBoundSourcesForActionEnumerateInfo* enumerateInfo, uint32_t sourceCapacityInput, uint32_t* sourceCountOutput, XrPath* sources) = 0;`
- L81 _public prototype_ `virtual XrResult XrLayerGetInputSourceLocalizedName(XrSession session, const XrInputSourceLocalizedNameGetInfo* getInfo, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer) = 0;`
- L82 _public prototype_ `virtual XrResult XrLayerApplyHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo, const XrHapticBaseHeader* hapticFeedback) = 0;`
- L83 _public prototype_ `virtual XrResult XrLayerStopHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo) = 0;`
- L88 _public prototype_ `virtual XrResult XrLayerInitializeLoaderKHR(const XrLoaderInitInfoBaseHeaderKHR* loaderInitInfo) = 0;` — XR_KHR_loader_init
- L93 _public prototype_ `virtual XrResult XrLayerGetVisibilityMaskKHR(XrSession session, XrViewConfigurationType viewConfigurationType, uint32_t viewIndex, XrVisibilityMaskTypeKHR visibilityMaskType, XrVisibilityMaskKHR* visibilityMask) = 0;` — XR_KHR_visibility_mask
- L97 _public prototype_ `virtual XrResult XrLayerGetD3D11GraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements) = 0;` — XR_KHR_D3D11_enable
- L102 _public prototype_ `virtual XrResult XrLayerGetD3D12GraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements) = 0;` — XR_KHR_D3D12_enable
- L107 _public prototype_ `virtual XrResult XrLayerGetOpenGLGraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements) = 0;` — XR_KHR_opengl_enable
- L112 _public prototype_ `virtual XrResult XrLayerGetVulkanGraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements) = 0;` — XR_KHR_vulkan_enable

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeAPISurface.h` (Public)


#### class `UE::XRScribe::IOpenXRAPILayerManager`  
`class IOpenXRAPILayerManager`  
_L20-30_
- L23 _public prototype_ `virtual IOpenXRAPILayer* GetActiveLayer() const = 0;`
- L25 _public prototype_ `virtual void SetFallbackRunMode(int32_t Fallback) = 0;`
- L27 _public prototype_ `virtual bool SetChainedGetProcAddr(PFN_xrGetInstanceProcAddr InChainedGetProcAddr) = 0;`
- L29 _public prototype_ `static IOpenXRAPILayerManager& Get();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace XRScribe` (scope `UE`)
- L12 _prototype_ `void BuildFunctionMaps();` (scope `UE::XRScribe`)
- L13 _prototype_ `void ClearFunctionMaps();` (scope `UE::XRScribe`)
- L15 _prototype_ `XRAPI_ATTR XrResult XRAPI_CALL xrGetInstanceProcAddr( XrInstance instance, const char* name, PFN_xrVoidFunction* function);` (scope `UE::XRScribe`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeCaptureLayer.h` (Public)


#### class `UE::XRScribe::FOpenXRCaptureLayer`  
`class FOpenXRCaptureLayer : public IOpenXRAPILayer`  
_L15-122_
- inherits: `IOpenXRAPILayer`
- L18 _public prototype_ `FOpenXRCaptureLayer();`
- L21 _public prototype_ `virtual void SetChainedGetProcAddr(PFN_xrGetInstanceProcAddr InChainedGetProcAddr) override;`
- L23 _public prototype_ `virtual bool SupportsInstanceExtension(const ANSICHAR* ExtensionName) override;`
- L26 _public prototype_ `virtual XrResult XrLayerEnumerateApiLayerProperties(uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrApiLayerProperties* properties) override;` — Global
- L27 _public prototype_ `virtual XrResult XrLayerEnumerateInstanceExtensionProperties(const char* layerName, uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrExtensionProperties* properties) override;`
- L28 _public prototype_ `virtual XrResult XrLayerCreateInstance(const XrInstanceCreateInfo* createInfo, XrInstance* instance) override;`
- L31 _public prototype_ `virtual XrResult XrLayerDestroyInstance(XrInstance instance) override;` — Instance
- L32 _public prototype_ `virtual XrResult XrLayerGetInstanceProperties(XrInstance instance, XrInstanceProperties* instanceProperties) override;`
- L33 _public prototype_ `virtual XrResult XrLayerPollEvent(XrInstance instance, XrEventDataBuffer* eventData) override;`
- L34 _public prototype_ `virtual XrResult XrLayerResultToString(XrInstance instance, XrResult value, char buffer[XR_MAX_RESULT_STRING_SIZE]) override;`
- L35 _public prototype_ `virtual XrResult XrLayerStructureTypeToString(XrInstance instance, XrStructureType value, char buffer[XR_MAX_STRUCTURE_NAME_SIZE]) override;`
- L36 _public prototype_ `virtual XrResult XrLayerGetSystem(XrInstance instance, const XrSystemGetInfo* getInfo, XrSystemId* systemId) override;`
- L37 _public prototype_ `virtual XrResult XrLayerGetSystemProperties(XrInstance instance, XrSystemId systemId, XrSystemProperties* properties) override;`
- L38 _public prototype_ `virtual XrResult XrLayerEnumerateEnvironmentBlendModes(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t environmentBlendModeCapacityInput, uint32_t* environmentBlendModeCountOutput, XrEnvironmentBlendMode* environmentBlendModes) override;`
- L39 _public prototype_ `virtual XrResult XrLayerCreateSession(XrInstance instance, const XrSessionCreateInfo* createInfo, XrSession* session) override;`
- L40 _public prototype_ `virtual XrResult XrLayerDestroySession(XrSession session) override;`
- L41 _public prototype_ `virtual XrResult XrLayerEnumerateReferenceSpaces(XrSession session, uint32_t spaceCapacityInput, uint32_t* spaceCountOutput, XrReferenceSpaceType* spaces) override;`
- L42 _public prototype_ `virtual XrResult XrLayerCreateReferenceSpace(XrSession session, const XrReferenceSpaceCreateInfo* createInfo, XrSpace* space) override;`
- L43 _public prototype_ `virtual XrResult XrLayerGetReferenceSpaceBoundsRect(XrSession session, XrReferenceSpaceType referenceSpaceType, XrExtent2Df* bounds) override;`
- L44 _public prototype_ `virtual XrResult XrLayerCreateActionSpace(XrSession session, const XrActionSpaceCreateInfo* createInfo, XrSpace* space) override;`
- L45 _public prototype_ `virtual XrResult XrLayerLocateSpace(XrSpace space, XrSpace baseSpace, XrTime time, XrSpaceLocation* location) override;`
- L46 _public prototype_ `virtual XrResult XrLayerDestroySpace(XrSpace space) override;`
- L47 _public prototype_ `virtual XrResult XrLayerEnumerateViewConfigurations(XrInstance instance, XrSystemId systemId, uint32_t viewConfigurationTypeCapacityInput, uint32_t* viewConfigurationTypeCountOutput, XrViewConfigurationType* viewConfigurationTypes) override;`
- L48 _public prototype_ `virtual XrResult XrLayerGetViewConfigurationProperties(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, XrViewConfigurationProperties* configurationProperties) override;`
- L49 _public prototype_ `virtual XrResult XrLayerEnumerateViewConfigurationViews(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrViewConfigurationView* views) override;`
- L50 _public prototype_ `virtual XrResult XrLayerEnumerateSwapchainFormats(XrSession session, uint32_t formatCapacityInput, uint32_t* formatCountOutput, int64_t* formats) override;`
- L51 _public prototype_ `virtual XrResult XrLayerCreateSwapchain(XrSession session, const XrSwapchainCreateInfo* createInfo, XrSwapchain* swapchain) override;`
- L52 _public prototype_ `virtual XrResult XrLayerDestroySwapchain(XrSwapchain swapchain) override;`
- L53 _public prototype_ `virtual XrResult XrLayerEnumerateSwapchainImages(XrSwapchain swapchain, uint32_t imageCapacityInput, uint32_t* imageCountOutput, XrSwapchainImageBaseHeader* images) override;`
- L54 _public prototype_ `virtual XrResult XrLayerAcquireSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageAcquireInfo* acquireInfo, uint32_t* index) override;`
- L55 _public prototype_ `virtual XrResult XrLayerWaitSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageWaitInfo* waitInfo) override;`
- L56 _public prototype_ `virtual XrResult XrLayerReleaseSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageReleaseInfo* releaseInfo) override;`
- L57 _public prototype_ `virtual XrResult XrLayerBeginSession(XrSession session, const XrSessionBeginInfo* beginInfo) override;`
- L58 _public prototype_ `virtual XrResult XrLayerEndSession(XrSession session) override;`
- L59 _public prototype_ `virtual XrResult XrLayerRequestExitSession(XrSession session) override;`
- L60 _public prototype_ `virtual XrResult XrLayerWaitFrame(XrSession session, const XrFrameWaitInfo* frameWaitInfo, XrFrameState* frameState) override;`
- L61 _public prototype_ `virtual XrResult XrLayerBeginFrame(XrSession session, const XrFrameBeginInfo* frameBeginInfo) override;`
- L62 _public prototype_ `virtual XrResult XrLayerEndFrame(XrSession session, const XrFrameEndInfo* frameEndInfo) override;`
- L63 _public prototype_ `virtual XrResult XrLayerLocateViews(XrSession session, const XrViewLocateInfo* viewLocateInfo, XrViewState* viewState, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrView* views) override;`
- L64 _public prototype_ `virtual XrResult XrLayerStringToPath(XrInstance instance, const char* pathString, XrPath* path) override;`
- L65 _public prototype_ `virtual XrResult XrLayerPathToString(XrInstance instance, XrPath path, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer) override;`
- L66 _public prototype_ `virtual XrResult XrLayerCreateActionSet(XrInstance instance, const XrActionSetCreateInfo* createInfo, XrActionSet* actionSet) override;`
- L67 _public prototype_ `virtual XrResult XrLayerDestroyActionSet(XrActionSet actionSet) override;`
- L68 _public prototype_ `virtual XrResult XrLayerCreateAction(XrActionSet actionSet, const XrActionCreateInfo* createInfo, XrAction* action) override;`
- L69 _public prototype_ `virtual XrResult XrLayerDestroyAction(XrAction action) override;`
- L70 _public prototype_ `virtual XrResult XrLayerSuggestInteractionProfileBindings(XrInstance instance, const XrInteractionProfileSuggestedBinding* suggestedBindings) override;`
- L71 _public prototype_ `virtual XrResult XrLayerAttachSessionActionSets(XrSession session, const XrSessionActionSetsAttachInfo* attachInfo) override;`
- L72 _public prototype_ `virtual XrResult XrLayerGetCurrentInteractionProfile(XrSession session, XrPath topLevelUserPath, XrInteractionProfileState* interactionProfile) override;`
- L73 _public prototype_ `virtual XrResult XrLayerGetActionStateBoolean(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateBoolean* state) override;`
- L74 _public prototype_ `virtual XrResult XrLayerGetActionStateFloat(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateFloat* state) override;`
- L75 _public prototype_ `virtual XrResult XrLayerGetActionStateVector2f(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateVector2f* state) override;`
- L76 _public prototype_ `virtual XrResult XrLayerGetActionStatePose(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStatePose* state) override;`
- L77 _public prototype_ `virtual XrResult XrLayerSyncActions(XrSession session, const XrActionsSyncInfo* syncInfo) override;`
- L78 _public prototype_ `virtual XrResult XrLayerEnumerateBoundSourcesForAction(XrSession session, const XrBoundSourcesForActionEnumerateInfo* enumerateInfo, uint32_t sourceCapacityInput, uint32_t* sourceCountOutput, XrPath* sources) override;`
- L79 _public prototype_ `virtual XrResult XrLayerGetInputSourceLocalizedName(XrSession session, const XrInputSourceLocalizedNameGetInfo* getInfo, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer) override;`
- L80 _public prototype_ `virtual XrResult XrLayerApplyHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo, const XrHapticBaseHeader* hapticFeedback) override;`
- L81 _public prototype_ `virtual XrResult XrLayerStopHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo) override;`
- L86 _public prototype_ `virtual XrResult XrLayerInitializeLoaderKHR(const XrLoaderInitInfoBaseHeaderKHR* loaderInitInfo) override;` — XR_KHR_loader_init
- L91 _public prototype_ `virtual XrResult XrLayerGetVisibilityMaskKHR(XrSession session, XrViewConfigurationType viewConfigurationType, uint32_t viewIndex, XrVisibilityMaskTypeKHR visibilityMaskType, XrVisibilityMaskKHR* visibilityMask) override;` — XR_KHR_visibility_mask
- L95 _public prototype_ `virtual XrResult XrLayerGetD3D11GraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements) override;` — XR_KHR_D3D11_enable
- L100 _public prototype_ `virtual XrResult XrLayerGetD3D12GraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements) override;` — XR_KHR_D3D12_enable
- L105 _public prototype_ `virtual XrResult XrLayerGetOpenGLGraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements) override;` — XR_KHR_opengl_enable
- L110 _public prototype_ `virtual XrResult XrLayerGetVulkanGraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements) override;` — XR_KHR_vulkan_enable
- L114 _protected prototype_ `void SaveCaptureToFile();`
- L116 _protected member_ `FOpenXRAPIPassthrough FunctionPassthroughs;`
- L117 _protected member_ `FOpenXRCaptureEncoder CaptureEncoder;`
- L119 _protected member_ `TArray<FString> NativeSupportedExtensionNames;`
- L120 _protected member_ `TArray<XrExtensionProperties> PassthruInstanceSupportedExtensions;`
- L121 _protected member_ `TArray<FString> CaptureActiveExtensionNames;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeDeveloperSettings.h` (Public)


#### enum `EXRScribeRunMode::Type`  
`enum Type : int`  
_L19-23_
- L21 _public enumerator_ `Capture = 0 UMETA(ToolTip = "Capture OpenXR API calls and store to Saved/Capture.xrs.")`
- L22 _public enumerator_ `Emulate = 1 UMETA(ToolTip = "Emulate OpenXR runtime and playback Saved/Capture.xrs.")`

#### class `UXRScribeDeveloperSettings`  
`class UXRScribeDeveloperSettings : public UDeveloperSettings`  
_L28-49_
- reflection: `UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "XRScribe"))`
- inherits: `UDeveloperSettings`
- desc: Developer settings for XRScribe
- L33 _public prototype_ `UXRScribeDeveloperSettings(const FObjectInitializer& Initializer);`
- L40 _public member_ `TEnumAsByte<EXRScribeRunMode::Type> RunMode = EXRScribeRunMode::Type::Emulate;` — `UPROPERTY(config, EditAnywhere, Category = "XRScribe", meta = ( ConsoleVariable = "XRScribe.RunMode", DisplayName = "Run Mode", ToolTip = "0 - Capture, 1 - Emulate", ConfigRestartRequired = true))` — Controls whether XRScribe runs in capture or emulation mode. Currently needed at engine startup, but will be runtime switchable.
- L48 _public prototype_ `virtual FName GetCategoryName() const;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace EXRScribeRunMode`

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeEmulatedPoseManager.h` (Public)


#### class `UE::XRScribe::FOpenXRActionPoseManager`  
`class FOpenXRActionPoseManager`  
_L28-337_
- L34 _public member_ `static const int32 PoseHistorySize = 5;` — Number of poses the manager will keep available relative to 'current' pose, in order for multi-frame pose queries
- L42 _public prototype_ `void RegisterCapturedPathStrings(const TMap<XrPath, FName>& PathStringMap);` — Register information about paths to path strings from the capture @param PathStringMap Captured map of path handles to FNames
- L51 _public prototype_ `void RegisterCapturedWaitFrames(const TArray<FOpenXRWaitFramePacket>& InWaitFrameHistory);` — Register information about wait frames from a capture file, in order to build a history of display times @param InWaitFrameHistory The WaitFrame packets from the capture
- L60 _public prototype_ `void RegisterCapturedReferenceSpaces(const TArray<FOpenXRCreateReferenceSpacePacket>& CreateReferenceSpacePackets);` — Register information about reference spaces from a capture file, in order to build a history of space locations relative to those reference spaces. @param CreateReferenceSpacePackets The create infos for the captured reference spaces
- L68 _public prototype_ `void RegisterCapturedActions(const TArray<FOpenXRCreateActionPacket>& CreateActionPackets);` — Register information about actions from capture file, in order to fetch action name for mapping between capture and emulation @param CreateActionPackets The create infos for the captured actions
- L78 _public prototype_ `void RegisterCapturedActionSpaces(const TArray<FOpenXRCreateActionSpacePacket>& CreateActionSpacePackets);` — Register information about action spaces from capture file, which we need to build a history of space locations for XR devices @param CreateActionSpacePackets The create infos for the captured action spaces
- L86 _public prototype_ `void RegisterCapturedSpaceHistories(const TMap<XrSpace, TArray<FOpenXRLocateSpacePacket>>& SpaceHistories);` — Register history of LocateSpace calls @param SpaceHistories List of LocateSpace histories, with a unified Space per history (but possibly varying BaseSpace)
- L99 _public prototype_ `void RegisterCapturedActionStates(const TArray<FOpenXRSyncActionsPacket>& SyncActionsPackets, const TMap<XrAction, TArray<FOpenXRGetActionStateBooleanPacket>>& BooleanActionStates, const TMap<XrAction, TArray<FOpenXRGetActionStateFloatPacket>>& FloatActionStates, const TMap<XrAction, TArray<FOpenXRGetActionStateVector2fPacket>>& VectorActionStates, const TMap<XrAction, TArray<FOpenXRGetActionStatePosePacket>>& PoseActionStates);` — Register history of GetActionState + SyncActions calls @param SyncActionsPackets List of SyncActions calls @param BooleanActionStates Per-action history of boolean action states @param FloatActionStates Per-action history of float action states @param VectorActionStates Per-action history of Vector2f action states @param PoseActionStates Per-action history of Pose action states (indicating whether pose is valid or not, not actual pose data)
- L109 _public prototype_ `void ProcessCapturedHistories();` — Process all captured pose and action state histories at once, in order to create a unified timeline
- L118 _public prototype_ `void RegisterEmulatedPath(FName PathString, XrPath Path);` — Register emulated path. Manager needs this to match paths between capture and emulation. @param PathString String used to create path @param Path Emulation-created path handle
- L128 _public prototype_ `void RegisterEmulatedAction(FName ActionName, XrAction Action, XrActionType ActionType);` — Register emulated action. Manager needs this to match emulated actions against captured action state histories @param ActionName String used for action name @param Action Emulation-created action handle @param ActionType Action-type to facilitate history type lookup
- L138 _public prototype_ `void RegisterEmulatedReferenceSpace(const XrReferenceSpaceCreateInfo& CreateInfo, XrSpace SpaceHandle);` — Register emulated reference space. Pose manager needs this to match the new emulated reference space against a captured reference space of similar attributes. @param CreateInfo Create info for emulated reference space, in order to match against captured history of similarly configured space @param SpaceHandle Emulation generated handle for new space
- L149 _public prototype_ `void RegisterEmulatedActionSpace(TStaticArray<ANSICHAR, XR_MAX_ACTION_NAME_SIZE>& ActionName, const XrActionSpaceCreateInfo& SpaceCreateInfo, XrSpace SpaceHandle);` — Register emulated action space. Pose manager needs this to match emulated action space against a captured action space with matching action name. @param ActionName Name from action create info @param SpaceCreateInfo Create info for emulated action space, in order to match against captured history of similarly configured space @param SpaceHandle Emulation generated handle for new space
- L160 _public prototype_ `void AddEmulatedFrameTime(XrTime Time, int32 FrameNum);` — Add time and frame number in order to generate interpolated poses We use the frame numbers to index into a relative history of the poses, and the time for frame matching + interpolation, because LocateSpace calls only provide a time argument @param Time Emulation generated time for new frame @param FrameNum Emulation generated frame index
- L170 _public prototype_ `bool DoesActionContainPoseHistory(TStaticArray<ANSICHAR, XR_MAX_ACTION_NAME_SIZE>& ActionName);` — If we have a pose history for the action, then xrGetActionStatePose can tell the client that the action is active, and poses are ready to fetch @param ActionName Name from action create info return ActionName has available pose history
- L181 _public prototype_ `XrSpaceLocation GetEmulatedPoseForTime(XrSpace LocatingSpace, XrSpace BaseSpace, XrTime Time);` — Fetch a pose generated from the captured history, by using space handles and times generated by the emulated runtime @param LocatingSpace Generated pose is associated with this space @param BaseSpace Generated pose is relative to this space @param Time Time of requested pose, relative to the known times from the emulated runtime return Location derived from captured history if available, or default location if request is unknown or invalid
- L192 _public prototype_ `XrActionStateBoolean GetEmulatedActionStateBoolean(const XrActionStateGetInfo* GetInfo, XrTime LastSyncTime);` — Fetch an action state generated from the captured history, by using XrActionStateGetInfo and most recent sync time The function itself is used to designate between different action state histories (bool, float, vector2f). @param GetInfo provides an action handle and subpath @param LastSyncTime The sync time is managed by the emulation layer, and used to offset into the captured history. return Action state derived from captured history if available, or default inactive state if action/subpath aren't available.
- L193 _public prototype_ `XrActionStateFloat GetEmulatedActionStateFloat(const XrActionStateGetInfo* GetInfo, XrTime LastSyncTime);`
- L194 _public prototype_ `XrActionStateVector2f GetEmulatedActionStateVector2f(const XrActionStateGetInfo* GetInfo, XrTime LastSyncTime);`
- L200 _public function_ `void OnSessionTeardown()` — Reset internal emulation state based on session teardown.
- L223 _protected typedef_ `using FBooleanActionState = TActionState<XrBool32>;`
- L224 _protected typedef_ `using FFloatActionState = TActionState<float>;`
- L225 _protected typedef_ `using FVector2fActionState = TActionState<XrVector2f>;`
- L227 _protected typedef_ `using FBooleanActionStateHistory = TActionStateHistory<XrBool32>;`
- L228 _protected typedef_ `using FFloatActionStateHistory = TActionStateHistory<float>;`
- L229 _protected typedef_ `using FVector2fActionStateHistory = TActionStateHistory<XrVector2f>;`
- L234 _protected prototype_ `XrReferenceSpaceType GetCapturedReferenceSpaceType(XrSpace CapturedSpace);` — Helper function to fetch underlying reference space type from opaque XrSpace handle
- L239 _protected prototype_ `bool VerifyCapturedActionSpace(XrSpace CapturedSpace);` — Helper function to validate captured space is an action space
- L244 _protected prototype_ `void CalculateCapturedTimeRange();` — Helper function to determine full time range of capture
- L249 _protected prototype_ `bool FilterSpaceHistory(const TArray<FOpenXRLocateSpacePacket>& RawHistory, TArray<FOpenXRLocateSpacePacket>& FilteredHistory);` — sort and remove duplicates in history for single space
- L254 _protected prototype_ `TArray<FOpenXRLocateSpacePacket> SliceFilteredSpaceHistory(const TArray<FOpenXRLocateSpacePacket>& FilteredHistory);` — Resample the filtered history in order to ease reading poses back based on time offsets during emulation
- L256 _protected prototype_ `void ProcessCapturedReferenceSpaceHistory(const TArray<FOpenXRLocateSpacePacket>& SpaceHistory);`
- L257 _protected prototype_ `void ProcessCapturedActionSpaceHistory(const TArray<FOpenXRLocateSpacePacket>& SpaceHistory);`
- L259 _protected prototype_ `FName GetEmulatedActionName(XrAction Action);`
- L264 _protected prototype_ `int64 GenerateReplaySliceIndexFromTime(XrTime EmulatedTime);` — Helper function to generate index into captured history from emulated time (offset from emulated session start)
- L266 _protected prototype_ `bool ValidateSubpath(const TSet<FName>& ValidSubpaths, XrPath ActionSubPath);`
- L271 _protected prototype_ `const XrActionStateBoolean GetCachedEmulatedBooleanState(FName ActionName);` — Helper function to managed 'cached' action states, because we're only supposed to update on state changes
- L272 _protected prototype_ `void SetCachedEmulatedBooleanState(FName ActionName, const XrActionStateBoolean& EmulatedState);`
- L273 _protected prototype_ `const XrActionStateFloat GetCachedEmulatedFloatState(FName ActionName);`
- L274 _protected prototype_ `void SetCachedEmulatedFloatState(FName ActionName, const XrActionStateFloat& EmulatedState);`
- L275 _protected prototype_ `const XrActionStateVector2f GetCachedEmulatedVector2fState(FName ActionName);`
- L276 _protected prototype_ `void SetCachedEmulatedVector2fState(FName ActionName, const XrActionStateVector2f& EmulatedState);`
- L278 _protected member_ `TMap<XrPath, FName> CapturedPaths;`
- L279 _protected member_ `TMap<XrPath, FName> EmulatedPaths;`
- L281 _protected member_ `TMap<XrAction, FName> EmulatedActionNames;`
- L282 _protected member_ `TMap<FName, XrActionStateBoolean> CachedEmulatedBooleanStates;`
- L283 _protected member_ `TMap<FName, XrActionStateFloat> CachedEmulatedFloatStates;`
- L284 _protected member_ `TMap<FName, XrActionStateVector2f> CachedEmulatedVector2fStates;`
- L287 _protected member_ `TArray<FOpenXRCreateReferenceSpacePacket> CapturedReferenceSpaces;` — Known spaces and relevant actions from capture
- L288 _protected member_ `TArray<FOpenXRCreateActionSpacePacket> CapturedActionSpaces;`
- L289 _protected member_ `TMap<XrAction, FOpenXRCreateActionPacket> CapturedActions;`
- L291 _protected member_ `TMap<XrSpace, TArray<FOpenXRLocateSpacePacket>> CapturedRawSpaceHistories;`
- L294 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStateBooleanPacket>> CapturedRawBooleanActionStates;` — TArray<FOpenXRSyncActionsPacket> CapturedRawSyncActionsPackets;
- L295 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStateFloatPacket>> CapturedRawFloatActionStates;`
- L296 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStateVector2fPacket>> CapturedRawVectorActionStates;`
- L297 _protected member_ `TMap<XrAction, TArray<FOpenXRGetActionStatePosePacket>> CapturedRawPoseActionStates;`
- L303 _protected member_ `TMap<XrReferenceSpaceType, TArray<FOpenXRLocateSpacePacket>> ReferencePoseHistories;` — Processed pose histories for space types, which could be unified across different space handles with the same underlying reference space type.
- L304 _protected member_ `TMap<FName, TArray<FOpenXRLocateSpacePacket>> ActionPoseHistories;`
- L306 _protected member_ `TMap<FName, TArray<FOpenXRGetActionStateBooleanPacket>> BooleanActionStateHistories;`
- L307 _protected member_ `TMap<FName, TArray<FOpenXRGetActionStateFloatPacket>> FloatActionStateHistories;`
- L308 _protected member_ `TMap<FName, TArray<FOpenXRGetActionStateVector2fPacket>> VectorActionStateHistories;`
- L309 _protected member_ `TMap<FName, TArray<FOpenXRGetActionStatePosePacket>> PoseActionStateHistories;`
- L311 _protected member_ `TMap<FName, FBooleanActionStateHistory> BooleanProcessedHistories;`
- L312 _protected member_ `TMap<FName, FFloatActionStateHistory> FloatProcessedHistories;`
- L313 _protected member_ `TMap<FName, FVector2fActionStateHistory> Vector2fProcessedHistories;`
- L316 _protected member_ `TMap<XrSpace, XrReferenceSpaceType> EmulatedReferenceSpaceTypeMap;` — Map of emulated spaces to their underlying reference space type (if applicable)
- L318 _protected member_ `TMap< XrSpace, FName> EmulatedActionSpaceNameMap;`
- L327 _protected member_ `TStaticArray <FrameTimeHistoryEntry, PoseHistorySize> FrameTimeHistory;` — History of frame times, in order for pose manager to look into to estimate the relative frame index for times
- L328 _protected member_ `int32 LastInsertedFrameIndex = 0;`
- L330 _protected member_ `int64 CapturedSliceCount = 0;`
- L331 _protected member_ `TArray<FOpenXRWaitFramePacket> WaitFrameHistory;`
- L333 _protected member_ `XrTime CapturedRangeStart = 0;`
- L334 _protected member_ `XrTime CapturedRangeEnd = 0;`
- L336 _protected member_ `XrTime EmulatedBaseTime = INT64_MAX;`

#### struct `UE::XRScribe::FOpenXRActionPoseManager::TActionState`  
`template <typename StateType> struct TActionState`  
_L210-214_
- L212 _public member_ `StateType State{};`
- L213 _public member_ `XrBool32 Active = 0;`

#### struct `UE::XRScribe::FOpenXRActionPoseManager::TActionStateHistory`  
`template <typename StateType> struct TActionStateHistory`  
_L217-221_
- L219 _public member_ `TArray<TActionState<StateType>> StateValues;`
- L220 _public member_ `TSet<FName> ValidSubpaths;`

#### struct `UE::XRScribe::FOpenXRActionPoseManager::FrameTimeHistoryEntry`  
`struct FrameTimeHistoryEntry`  
_L320-324_
- L322 _public member_ `XrTime Time = 0;`
- L323 _public member_ `int32 FrameIndex = -1;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeEmulationLayer.h` (Public)


#### class `UE::XRScribe::FOpenXREmulationLayer`  
`class FOpenXREmulationLayer : public IOpenXRAPILayer`  
_L23-166_
- inherits: `IOpenXRAPILayer`
- L28 _public prototype_ `FOpenXREmulationLayer();` — The constructor + destructor need to be defined in cpp file in order for TUniquePtr of forward decl to work (FOpenXREmulatedInstance)
- L31 _public prototype_ `virtual bool SupportsInstanceExtension(const ANSICHAR* ExtensionName) override;`
- L33 _public prototype_ `bool LoadCaptureFromFile(const FString& EmulationLoadPath);`
- L34 _public prototype_ `bool LoadCaptureFromData(const TArray<uint8>& EncodedData);`
- L37 _public prototype_ `virtual XrResult XrLayerEnumerateApiLayerProperties(uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrApiLayerProperties* properties) override;` — Global
- L38 _public prototype_ `virtual XrResult XrLayerEnumerateInstanceExtensionProperties(const char* layerName, uint32_t propertyCapacityInput, uint32_t* propertyCountOutput, XrExtensionProperties* properties) override;`
- L39 _public prototype_ `virtual XrResult XrLayerCreateInstance(const XrInstanceCreateInfo* createInfo, XrInstance* instance) override;`
- L42 _public prototype_ `virtual XrResult XrLayerDestroyInstance(XrInstance instance) override;` — Instance
- L43 _public prototype_ `virtual XrResult XrLayerGetInstanceProperties(XrInstance instance, XrInstanceProperties* instanceProperties) override;`
- L44 _public prototype_ `virtual XrResult XrLayerPollEvent(XrInstance instance, XrEventDataBuffer* eventData) override;`
- L45 _public prototype_ `virtual XrResult XrLayerResultToString(XrInstance instance, XrResult value, char buffer[XR_MAX_RESULT_STRING_SIZE]) override;`
- L46 _public prototype_ `virtual XrResult XrLayerStructureTypeToString(XrInstance instance, XrStructureType value, char buffer[XR_MAX_STRUCTURE_NAME_SIZE]) override;`
- L47 _public prototype_ `virtual XrResult XrLayerGetSystem(XrInstance instance, const XrSystemGetInfo* getInfo, XrSystemId* systemId) override;`
- L48 _public prototype_ `virtual XrResult XrLayerGetSystemProperties(XrInstance instance, XrSystemId systemId, XrSystemProperties* properties) override;`
- L49 _public prototype_ `virtual XrResult XrLayerEnumerateEnvironmentBlendModes(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t environmentBlendModeCapacityInput, uint32_t* environmentBlendModeCountOutput, XrEnvironmentBlendMode* environmentBlendModes) override;`
- L50 _public prototype_ `virtual XrResult XrLayerCreateSession(XrInstance instance, const XrSessionCreateInfo* createInfo, XrSession* session) override;`
- L51 _public prototype_ `virtual XrResult XrLayerDestroySession(XrSession session) override;`
- L52 _public prototype_ `virtual XrResult XrLayerEnumerateReferenceSpaces(XrSession session, uint32_t spaceCapacityInput, uint32_t* spaceCountOutput, XrReferenceSpaceType* spaces) override;`
- L53 _public prototype_ `virtual XrResult XrLayerCreateReferenceSpace(XrSession session, const XrReferenceSpaceCreateInfo* createInfo, XrSpace* space) override;`
- L54 _public prototype_ `virtual XrResult XrLayerGetReferenceSpaceBoundsRect(XrSession session, XrReferenceSpaceType referenceSpaceType, XrExtent2Df* bounds) override;`
- L55 _public prototype_ `virtual XrResult XrLayerCreateActionSpace(XrSession session, const XrActionSpaceCreateInfo* createInfo, XrSpace* space) override;`
- L56 _public prototype_ `virtual XrResult XrLayerLocateSpace(XrSpace space, XrSpace baseSpace, XrTime time, XrSpaceLocation* location) override;`
- L57 _public prototype_ `virtual XrResult XrLayerDestroySpace(XrSpace space) override;`
- L58 _public prototype_ `virtual XrResult XrLayerEnumerateViewConfigurations(XrInstance instance, XrSystemId systemId, uint32_t viewConfigurationTypeCapacityInput, uint32_t* viewConfigurationTypeCountOutput, XrViewConfigurationType* viewConfigurationTypes) override;`
- L59 _public prototype_ `virtual XrResult XrLayerGetViewConfigurationProperties(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, XrViewConfigurationProperties* configurationProperties) override;`
- L60 _public prototype_ `virtual XrResult XrLayerEnumerateViewConfigurationViews(XrInstance instance, XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrViewConfigurationView* views) override;`
- L61 _public prototype_ `virtual XrResult XrLayerEnumerateSwapchainFormats(XrSession session, uint32_t formatCapacityInput, uint32_t* formatCountOutput, int64_t* formats) override;`
- L62 _public prototype_ `virtual XrResult XrLayerCreateSwapchain(XrSession session, const XrSwapchainCreateInfo* createInfo, XrSwapchain* swapchain) override;`
- L63 _public prototype_ `virtual XrResult XrLayerDestroySwapchain(XrSwapchain swapchain) override;`
- L64 _public prototype_ `virtual XrResult XrLayerEnumerateSwapchainImages(XrSwapchain swapchain, uint32_t imageCapacityInput, uint32_t* imageCountOutput, XrSwapchainImageBaseHeader* images) override;`
- L65 _public prototype_ `virtual XrResult XrLayerAcquireSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageAcquireInfo* acquireInfo, uint32_t* index) override;`
- L66 _public prototype_ `virtual XrResult XrLayerWaitSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageWaitInfo* waitInfo) override;`
- L67 _public prototype_ `virtual XrResult XrLayerReleaseSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageReleaseInfo* releaseInfo) override;`
- L68 _public prototype_ `virtual XrResult XrLayerBeginSession(XrSession session, const XrSessionBeginInfo* beginInfo) override;`
- L69 _public prototype_ `virtual XrResult XrLayerEndSession(XrSession session) override;`
- L70 _public prototype_ `virtual XrResult XrLayerRequestExitSession(XrSession session) override;`
- L71 _public prototype_ `virtual XrResult XrLayerWaitFrame(XrSession session, const XrFrameWaitInfo* frameWaitInfo, XrFrameState* frameState) override;`
- L72 _public prototype_ `virtual XrResult XrLayerBeginFrame(XrSession session, const XrFrameBeginInfo* frameBeginInfo) override;`
- L73 _public prototype_ `virtual XrResult XrLayerEndFrame(XrSession session, const XrFrameEndInfo* frameEndInfo) override;`
- L74 _public prototype_ `virtual XrResult XrLayerLocateViews(XrSession session, const XrViewLocateInfo* viewLocateInfo, XrViewState* viewState, uint32_t viewCapacityInput, uint32_t* viewCountOutput, XrView* views) override;`
- L75 _public prototype_ `virtual XrResult XrLayerStringToPath(XrInstance instance, const char* pathString, XrPath* path) override;`
- L76 _public prototype_ `virtual XrResult XrLayerPathToString(XrInstance instance, XrPath path, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer) override;`
- L77 _public prototype_ `virtual XrResult XrLayerCreateActionSet(XrInstance instance, const XrActionSetCreateInfo* createInfo, XrActionSet* actionSet) override;`
- L78 _public prototype_ `virtual XrResult XrLayerDestroyActionSet(XrActionSet actionSet) override;`
- L79 _public prototype_ `virtual XrResult XrLayerCreateAction(XrActionSet actionSet, const XrActionCreateInfo* createInfo, XrAction* action) override;`
- L80 _public prototype_ `virtual XrResult XrLayerDestroyAction(XrAction action) override;`
- L81 _public prototype_ `virtual XrResult XrLayerSuggestInteractionProfileBindings(XrInstance instance, const XrInteractionProfileSuggestedBinding* suggestedBindings) override;`
- L82 _public prototype_ `virtual XrResult XrLayerAttachSessionActionSets(XrSession session, const XrSessionActionSetsAttachInfo* attachInfo) override;`
- L83 _public prototype_ `virtual XrResult XrLayerGetCurrentInteractionProfile(XrSession session, XrPath topLevelUserPath, XrInteractionProfileState* interactionProfile) override;`
- L84 _public prototype_ `virtual XrResult XrLayerGetActionStateBoolean(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateBoolean* state) override;`
- L85 _public prototype_ `virtual XrResult XrLayerGetActionStateFloat(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateFloat* state) override;`
- L86 _public prototype_ `virtual XrResult XrLayerGetActionStateVector2f(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStateVector2f* state) override;`
- L87 _public prototype_ `virtual XrResult XrLayerGetActionStatePose(XrSession session, const XrActionStateGetInfo* getInfo, XrActionStatePose* state) override;`
- L88 _public prototype_ `virtual XrResult XrLayerSyncActions(XrSession session, const XrActionsSyncInfo* syncInfo) override;`
- L89 _public prototype_ `virtual XrResult XrLayerEnumerateBoundSourcesForAction(XrSession session, const XrBoundSourcesForActionEnumerateInfo* enumerateInfo, uint32_t sourceCapacityInput, uint32_t* sourceCountOutput, XrPath* sources) override;`
- L90 _public prototype_ `virtual XrResult XrLayerGetInputSourceLocalizedName(XrSession session, const XrInputSourceLocalizedNameGetInfo* getInfo, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer) override;`
- L91 _public prototype_ `virtual XrResult XrLayerApplyHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo, const XrHapticBaseHeader* hapticFeedback) override;`
- L92 _public prototype_ `virtual XrResult XrLayerStopHapticFeedback(XrSession session, const XrHapticActionInfo* hapticActionInfo) override;`
- L97 _public prototype_ `virtual XrResult XrLayerInitializeLoaderKHR(const XrLoaderInitInfoBaseHeaderKHR* loaderInitInfo) override;` — XR_KHR_loader_init
- L102 _public prototype_ `virtual XrResult XrLayerGetVisibilityMaskKHR(XrSession session, XrViewConfigurationType viewConfigurationType, uint32_t viewIndex, XrVisibilityMaskTypeKHR visibilityMaskType, XrVisibilityMaskKHR* visibilityMask) override;` — XR_KHR_visibility_mask
- L106 _public prototype_ `virtual XrResult XrLayerGetD3D11GraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements) override;` — XR_KHR_D3D11_enable
- L111 _public prototype_ `virtual XrResult XrLayerGetD3D12GraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements) override;` — XR_KHR_D3D12_enable
- L116 _public prototype_ `virtual XrResult XrLayerGetOpenGLGraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements) override;` — XR_KHR_opengl_enable
- L121 _public prototype_ `virtual XrResult XrLayerGetVulkanGraphicsRequirementsKHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements) override;` — XR_KHR_vulkan_enable
- L125 _protected prototype_ `void PostLoadActions();`
- L127 _protected prototype_ `bool InstanceHandleCheck(XrInstance InputInstance);`
- L128 _protected prototype_ `bool SystemIdCheck(XrSystemId InputSystemId);`
- L129 _protected prototype_ `bool SessionHandleCheck(XrSession InputSession);`
- L131 _protected prototype_ `bool SpaceHandleCheck(XrSpace InputSpace);`
- L132 _protected prototype_ `bool SwapchainHandleCheck(XrSwapchain InputSwapchain);`
- L133 _protected prototype_ `bool ActionSetHandleCheck(XrActionSet InputActionSet);`
- L134 _protected prototype_ `bool ActionHandleCheck(XrAction InputAction);`
- L136 _protected prototype_ `bool IsCurrentSessionRunning();`
- L138 _protected prototype_ `void UpdateSessionState(FOpenXREmulatedSession& Session, XrSessionState AfterState);`
- L139 _protected prototype_ `XrResult SetupGraphicsBinding(const XrSystemId SystemId, const void* InBinding, TUniquePtr<FOpenXREmulatedSession>& Session);`
- L141 _protected prototype_ `EPixelFormat ConvertPlatformFormat(int64 PlatformFormat);`
- L142 _protected prototype_ `static ETextureCreateFlags ConvertXrSwapchainFlagsToTextureCreateFlags(const XrSwapchainCreateInfo* CreateInfo);`
- L144 _protected member_ `int64 StartTimeTicks = 0;`
- L145 _protected member_ `int64 LastSyncTimeTicks = 0;`
- L147 _protected member_ `FOpenXRCaptureDecoder CaptureDecoder;`
- L149 _protected member_ `TArray<XrApiLayerProperties> SupportedEmulatedLayers;`
- L150 _protected member_ `TArray<XrExtensionProperties> SupportedEmulatedExtensions;`
- L152 _protected member_ `FRWLock InstanceMutex;`
- L153 _protected member_ `TUniquePtr<FOpenXREmulatedInstance> CurrentInstance;`
- L154 _protected member_ `XrInstanceProperties EmulatedInstanceProperties = {};`
- L156 _protected member_ `const XrSystemId MagicSystemId = 0xdeadbeef;`
- L157 _protected member_ `XrSystemProperties EmulatedSystemProperties = {};`
- L159 _protected member_ `FRWLock SessionMutex;`
- L160 _protected member_ `TUniquePtr<FOpenXREmulatedSession> CurrentSession;`
- L163 _protected member_ `TSpscQueue<FOpenXRUpdateEvent> PendingApplicationUpdateQueue;` — TMpscQueue<FOpenXRUpdateEvent> InternalUpdateQueue;
- L165 _protected member_ `FOpenXRActionPoseManager ActionPoseManager;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace XRScribe` (scope `UE`)

### `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeFileFormat.h` (Public)


#### enum `UE::XRScribe::EOpenXRAPIThreadId`  
`enum class EOpenXRAPIThreadId : uint8`  
_L20-26_
- L22 _public enumerator_ `GameThread = 0`
- L23 _public enumerator_ `RenderThread = 1`
- L24 _public enumerator_ `RHIThread = 2`

#### enum `UE::XRScribe::EOpenXRAPIPacketId`  
`enum class EOpenXRAPIPacketId : uint8`  
_L28-172_
- L34 _public enumerator_ `EnumerateApiLayerProperties = 0` — Global GetInstanceProcAddr = 0,
- L35 _public enumerator_ `EnumerateInstanceExtensionProperties`
- L36 _public enumerator_ `CreateInstance`
- L39 _public enumerator_ `DestroyInstance` — Instance
- L40 _public enumerator_ `GetInstanceProperties`
- L41 _public enumerator_ `PollEvent`
- L42 _public enumerator_ `ResultToString`
- L43 _public enumerator_ `StructureTypeToString`
- L44 _public enumerator_ `GetSystem`
- L45 _public enumerator_ `GetSystemProperties`
- L46 _public enumerator_ `EnumerateEnvironmentBlendModes`
- L47 _public enumerator_ `CreateSession`
- L48 _public enumerator_ `DestroySession`
- L49 _public enumerator_ `EnumerateReferenceSpaces`
- L50 _public enumerator_ `CreateReferenceSpace`
- L51 _public enumerator_ `GetReferenceSpaceBoundsRect`
- L52 _public enumerator_ `CreateActionSpace`
- L53 _public enumerator_ `LocateSpace`
- L54 _public enumerator_ `DestroySpace`
- L55 _public enumerator_ `EnumerateViewConfigurations`
- L56 _public enumerator_ `GetViewConfigurationProperties`
- L57 _public enumerator_ `EnumerateViewConfigurationViews`
- L58 _public enumerator_ `EnumerateSwapchainFormats`
- L59 _public enumerator_ `CreateSwapchain`
- L60 _public enumerator_ `DestroySwapchain`
- L61 _public enumerator_ `EnumerateSwapchainImages`
- L62 _public enumerator_ `AcquireSwapchainImage`
- L63 _public enumerator_ `WaitSwapchainImage`
- L64 _public enumerator_ `ReleaseSwapchainImage`
- L65 _public enumerator_ `BeginSession`
- L66 _public enumerator_ `EndSession`
- L67 _public enumerator_ `RequestExitSession`
- L68 _public enumerator_ `WaitFrame`
- L69 _public enumerator_ `BeginFrame`
- L70 _public enumerator_ `EndFrame`
- L71 _public enumerator_ `LocateViews`
- L72 _public enumerator_ `StringToPath`
- L73 _public enumerator_ `PathToString`
- L74 _public enumerator_ `CreateActionSet`
- L75 _public enumerator_ `DestroyActionSet`
- L76 _public enumerator_ `CreateAction`
- L77 _public enumerator_ `DestroyAction`
- L78 _public enumerator_ `SuggestInteractionProfileBindings`
- L79 _public enumerator_ `AttachSessionActionSets`
- L80 _public enumerator_ `GetCurrentInteractionProfile`
- L81 _public enumerator_ `GetActionStateBoolean`
- L82 _public enumerator_ `GetActionStateFloat`
- L83 _public enumerator_ `GetActionStateVector2F`
- L84 _public enumerator_ `GetActionStatePose`
- L85 _public enumerator_ `SyncActions`
- L86 _public enumerator_ `EnumerateBoundSourcesForAction`
- L87 _public enumerator_ `GetInputSourceLocalizedName`
- L88 _public enumerator_ `ApplyHapticFeedback`
- L89 _public enumerator_ `StopHapticFeedback`
- L94 _public enumerator_ `InitializeLoaderKHR` — Global
- L97 _public enumerator_ `GetVisibilityMaskKHR` — Instance
- L98 _public enumerator_ `PerfSettingsSetPerformanceLevelEXT`
- L99 _public enumerator_ `ThermalGetTemperatureTrendEXT`
- L100 _public enumerator_ `SetDebugUtilsObjectNameEXT`
- L101 _public enumerator_ `CreateDebugUtilsMessengerEXT`
- L102 _public enumerator_ `DestroyDebugUtilsMessengerEXT`
- L103 _public enumerator_ `SubmitDebugUtilsMessageEXT`
- L104 _public enumerator_ `SessionBeginDebugUtilsLabelRegionEXT`
- L105 _public enumerator_ `SessionEndDebugUtilsLabelRegionEXT`
- L106 _public enumerator_ `SessionInsertDebugUtilsLabelEXT`
- L107 _public enumerator_ `CreateSpatialAnchorMsft`
- L108 _public enumerator_ `CreateSpatialAnchorSpaceMsft`
- L109 _public enumerator_ `DestroySpatialAnchorMsft`
- L110 _public enumerator_ `SetInputDeviceActiveEXT`
- L111 _public enumerator_ `SetInputDeviceStateBoolEXT`
- L112 _public enumerator_ `SetInputDeviceStateFloatEXT`
- L113 _public enumerator_ `SetInputDeviceStateVector2FEXT`
- L114 _public enumerator_ `SetInputDeviceLocationEXT`
- L115 _public enumerator_ `CreateSpatialGraphNodeSpaceMsft`
- L116 _public enumerator_ `CreateHandTrackerEXT`
- L117 _public enumerator_ `DestroyHandTrackerEXT`
- L118 _public enumerator_ `LocateHandJointsEXT`
- L119 _public enumerator_ `CreateHandMeshSpaceMsft`
- L120 _public enumerator_ `UpdateHandMeshMsft`
- L121 _public enumerator_ `GetControllerModelKeyMsft`
- L122 _public enumerator_ `LoadControllerModelMsft`
- L123 _public enumerator_ `GetControllerModelPropertiesMsft`
- L124 _public enumerator_ `GetControllerModelStateMsft`
- L125 _public enumerator_ `EnumerateReprojectionModesMsft`
- L126 _public enumerator_ `UpdateSwapchainFb`
- L127 _public enumerator_ `GetSwapchainStateFb`
- L128 _public enumerator_ `EnumerateSceneComputeFeaturesMsft`
- L129 _public enumerator_ `CreateSceneObserverMsft`
- L130 _public enumerator_ `DestroySceneObserverMsft`
- L131 _public enumerator_ `CreateSceneMsft`
- L132 _public enumerator_ `DestroySceneMsft`
- L133 _public enumerator_ `ComputeNewSceneMsft`
- L134 _public enumerator_ `GetSceneComputeStateMsft`
- L135 _public enumerator_ `GetSceneComponentsMsft`
- L136 _public enumerator_ `LocateSceneComponentsMsft`
- L137 _public enumerator_ `GetSceneMeshBuffersMsft`
- L138 _public enumerator_ `DeserializeSceneMsft`
- L139 _public enumerator_ `GetSerializedSceneFragmentDataMsft`
- L140 _public enumerator_ `EnumerateDisplayRefreshRatesFb`
- L141 _public enumerator_ `GetDisplayRefreshRateFb`
- L142 _public enumerator_ `RequestDisplayRefreshRateFb`
- L143 _public enumerator_ `EnumerateColorSpacesFb`
- L144 _public enumerator_ `SetColorSpaceFb`
- L145 _public enumerator_ `SetEnvironmentDepthEstimationVarjo`
- L148 _public enumerator_ `SetAndroidApplicationThreadKHR` — Platform Instance
- L149 _public enumerator_ `CreateSwapchainAndroidSurfaceKHR`
- L150 _public enumerator_ `GetOpenGLGraphicsRequirementsKHR`
- L151 _public enumerator_ `GetOpenGLESGraphicsRequirementsKHR`
- L152 _public enumerator_ `GetVulkanInstanceExtensionsKHR`
- L153 _public enumerator_ `GetVulkanDeviceExtensionsKHR`
- L154 _public enumerator_ `GetVulkanGraphicsDeviceKHR`
- L155 _public enumerator_ `GetVulkanGraphicsRequirementsKHR`
- L156 _public enumerator_ `CreateVulkanInstanceKHR`
- L157 _public enumerator_ `CreateVulkanDeviceKHR`
- L158 _public enumerator_ `GetVulkanGraphicsDevice2KHR`
- L159 _public enumerator_ `GetVulkanGraphicsRequirements2KHR`
- L160 _public enumerator_ `GetD3D11GraphicsRequirementsKHR`
- L161 _public enumerator_ `GetD3D12GraphicsRequirementsKHR`
- L162 _public enumerator_ `ConvertWin32PerformanceCounterToTimeKHR`
- L163 _public enumerator_ `ConvertTimeToWin32PerformanceCounterKHR`
- L164 _public enumerator_ `CreateSpatialAnchorFromPerceptionAnchorMSFT`
- L165 _public enumerator_ `TryGetPerceptionAnchorFromSpatialAnchorMSFT`
- L166 _public enumerator_ `GetAudioOutputDeviceGuidOculus`
- L167 _public enumerator_ `GetAudioInputDeviceGuidOculus`
- L168 _public enumerator_ `ConvertTimespecTimeToTimeKHR`
- L169 _public enumerator_ `ConvertTimeToTimespecTimeKHR`
- L171 _public enumerator_ `NumValidAPIPacketIds`

#### struct `UE::XRScribe::FOpenXRAPIPacketBase`  
`struct FOpenXRAPIPacketBase`  
_L174-193_
- L177 _public member_ `static constexpr uint8 MagicPacketByte = 0xab;`
- L179 _public member_ `uint64 TimeInCycles;`
- L180 _public member_ `XrResult Result;`
- L181 _public member_ `EOpenXRAPIPacketId ApiId;`
- L182 _public member_ `EOpenXRAPIThreadId ThreadId;`
- L184 _public member_ `uint16 Padding0;`
- L189 _protected prototype_ `FOpenXRAPIPacketBase(XrResult InResult, EOpenXRAPIPacketId InApiId);`
- L192 _protected prototype_ `FOpenXRAPIPacketBase() = delete;`

#### struct `UE::XRScribe::FOpenXREnumerateApiLayerPropertiesPacket`  
`struct FOpenXREnumerateApiLayerPropertiesPacket : public FOpenXRAPIPacketBase`  
_L204-211_
- inherits: `FOpenXRAPIPacketBase`
- L206 _public member_ `TArray<XrApiLayerProperties> LayerProperties;`
- L208 _public prototype_ `FOpenXREnumerateApiLayerPropertiesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateInstanceExtensionPropertiesPacket`  
`struct FOpenXREnumerateInstanceExtensionPropertiesPacket : public FOpenXRAPIPacketBase`  
_L213-221_
- inherits: `FOpenXRAPIPacketBase`
- L215 _public member_ `TStaticArray<ANSICHAR, XR_MAX_API_LAYER_NAME_SIZE> LayerName;`
- L216 _public member_ `TArray<XrExtensionProperties> ExtensionProperties;`
- L218 _public prototype_ `FOpenXREnumerateInstanceExtensionPropertiesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateInstancePacket`  
`struct FOpenXRCreateInstancePacket : public FOpenXRAPIPacketBase`  
_L223-252_
- inherits: `FOpenXRAPIPacketBase`
- L237 _public member_ `XrInstanceCreateFlags CreateFlags;`
- L238 _public member_ `XrApplicationInfo ApplicationInfo;`
- L239 _public member_ `TArray<TStaticArray<ANSICHAR, XR_MAX_API_LAYER_NAME_SIZE>> EnabledLayerNames;`
- L240 _public member_ `TArray<TStaticArray<ANSICHAR, XR_MAX_EXTENSION_NAME_SIZE>> EnabledExtensionNames;`
- L242 _public member_ `XrInstance GeneratedInstance;`
- L249 _public prototype_ `FOpenXRCreateInstancePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRDestroyInstancePacket`  
`struct FOpenXRDestroyInstancePacket : public FOpenXRAPIPacketBase`  
_L254-261_
- inherits: `FOpenXRAPIPacketBase`
- L256 _public member_ `XrInstance Instance;`
- L258 _public prototype_ `FOpenXRDestroyInstancePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetInstancePropertiesPacket`  
`struct FOpenXRGetInstancePropertiesPacket : public FOpenXRAPIPacketBase`  
_L263-271_
- inherits: `FOpenXRAPIPacketBase`
- L265 _public member_ `XrInstance Instance;`
- L266 _public member_ `XrInstanceProperties InstanceProperties;`
- L268 _public prototype_ `FOpenXRGetInstancePropertiesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetSystemPacket`  
`struct FOpenXRGetSystemPacket : public FOpenXRAPIPacketBase`  
_L273-282_
- inherits: `FOpenXRAPIPacketBase`
- L275 _public member_ `XrInstance Instance;`
- L276 _public member_ `XrSystemGetInfo SystemGetInfo;`
- L277 _public member_ `XrSystemId SystemId;`
- L279 _public prototype_ `FOpenXRGetSystemPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetSystemPropertiesPacket`  
`struct FOpenXRGetSystemPropertiesPacket : public FOpenXRAPIPacketBase`  
_L284-293_
- inherits: `FOpenXRAPIPacketBase`
- L286 _public member_ `XrInstance Instance;`
- L287 _public member_ `XrSystemId SystemId;`
- L288 _public member_ `XrSystemProperties SystemProperties;`
- L290 _public prototype_ `FOpenXRGetSystemPropertiesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateEnvironmentBlendModesPacket`  
`struct FOpenXREnumerateEnvironmentBlendModesPacket : public FOpenXRAPIPacketBase`  
_L295-305_
- inherits: `FOpenXRAPIPacketBase`
- L297 _public member_ `XrInstance Instance;`
- L298 _public member_ `XrSystemId SystemId;`
- L299 _public member_ `XrViewConfigurationType ViewConfigurationType;`
- L300 _public member_ `TArray<XrEnvironmentBlendMode> EnvironmentBlendModes;`
- L302 _public prototype_ `FOpenXREnumerateEnvironmentBlendModesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateSessionPacket`  
`struct FOpenXRCreateSessionPacket : public FOpenXRAPIPacketBase`  
_L307-316_
- inherits: `FOpenXRAPIPacketBase`
- L309 _public member_ `XrInstance Instance;`
- L310 _public member_ `XrSessionCreateInfo SessionCreateInfo;`
- L311 _public member_ `XrSession Session;`
- L313 _public prototype_ `FOpenXRCreateSessionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRDestroySessionPacket`  
`struct FOpenXRDestroySessionPacket : public FOpenXRAPIPacketBase`  
_L318-325_
- inherits: `FOpenXRAPIPacketBase`
- L320 _public member_ `XrSession Session;`
- L322 _public prototype_ `FOpenXRDestroySessionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateReferenceSpacesPacket`  
`struct FOpenXREnumerateReferenceSpacesPacket : public FOpenXRAPIPacketBase`  
_L327-335_
- inherits: `FOpenXRAPIPacketBase`
- L329 _public member_ `XrSession Session;`
- L330 _public member_ `TArray<XrReferenceSpaceType> Spaces;`
- L332 _public prototype_ `FOpenXREnumerateReferenceSpacesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateReferenceSpacePacket`  
`struct FOpenXRCreateReferenceSpacePacket : public FOpenXRAPIPacketBase`  
_L337-346_
- inherits: `FOpenXRAPIPacketBase`
- L339 _public member_ `XrSession Session;`
- L340 _public member_ `XrReferenceSpaceCreateInfo ReferenceSpaceCreateInfo;`
- L341 _public member_ `XrSpace Space;`
- L343 _public prototype_ `FOpenXRCreateReferenceSpacePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetReferenceSpaceBoundsRectPacket`  
`struct FOpenXRGetReferenceSpaceBoundsRectPacket : public FOpenXRAPIPacketBase`  
_L348-357_
- inherits: `FOpenXRAPIPacketBase`
- L350 _public member_ `XrSession Session;`
- L351 _public member_ `XrReferenceSpaceType ReferenceSpaceType;`
- L352 _public member_ `XrExtent2Df Bounds;`
- L354 _public prototype_ `FOpenXRGetReferenceSpaceBoundsRectPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateActionSpacePacket`  
`struct FOpenXRCreateActionSpacePacket : public FOpenXRAPIPacketBase`  
_L359-368_
- inherits: `FOpenXRAPIPacketBase`
- L361 _public member_ `XrSession Session;`
- L362 _public member_ `XrActionSpaceCreateInfo ActionSpaceCreateInfo;`
- L363 _public member_ `XrSpace Space;`
- L365 _public prototype_ `FOpenXRCreateActionSpacePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRLocateSpacePacket`  
`struct FOpenXRLocateSpacePacket : public FOpenXRAPIPacketBase`  
_L370-380_
- inherits: `FOpenXRAPIPacketBase`
- L372 _public member_ `XrSpace Space;`
- L373 _public member_ `XrSpace BaseSpace;`
- L374 _public member_ `XrTime Time;`
- L375 _public member_ `XrSpaceLocation Location;`
- L377 _public prototype_ `FOpenXRLocateSpacePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRDestroySpacePacket`  
`struct FOpenXRDestroySpacePacket : public FOpenXRAPIPacketBase`  
_L382-389_
- inherits: `FOpenXRAPIPacketBase`
- L384 _public member_ `XrSpace Space;`
- L386 _public prototype_ `FOpenXRDestroySpacePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateViewConfigurationsPacket`  
`struct FOpenXREnumerateViewConfigurationsPacket : public FOpenXRAPIPacketBase`  
_L391-400_
- inherits: `FOpenXRAPIPacketBase`
- L393 _public member_ `XrInstance Instance;`
- L394 _public member_ `XrSystemId SystemId;`
- L395 _public member_ `TArray<XrViewConfigurationType> ViewConfigurationTypes;`
- L397 _public prototype_ `FOpenXREnumerateViewConfigurationsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetViewConfigurationPropertiesPacket`  
`struct FOpenXRGetViewConfigurationPropertiesPacket : public FOpenXRAPIPacketBase`  
_L402-412_
- inherits: `FOpenXRAPIPacketBase`
- L404 _public member_ `XrInstance Instance;`
- L405 _public member_ `XrSystemId SystemId;`
- L406 _public member_ `XrViewConfigurationType ViewConfigurationType;`
- L407 _public member_ `XrViewConfigurationProperties ConfigurationProperties;`
- L409 _public prototype_ `FOpenXRGetViewConfigurationPropertiesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateViewConfigurationViewsPacket`  
`struct FOpenXREnumerateViewConfigurationViewsPacket : public FOpenXRAPIPacketBase`  
_L414-424_
- inherits: `FOpenXRAPIPacketBase`
- L416 _public member_ `XrInstance Instance;`
- L417 _public member_ `XrSystemId SystemId;`
- L418 _public member_ `XrViewConfigurationType ViewConfigurationType;`
- L419 _public member_ `TArray<XrViewConfigurationView> Views;`
- L421 _public prototype_ `FOpenXREnumerateViewConfigurationViewsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateSwapchainFormatsPacket`  
`struct FOpenXREnumerateSwapchainFormatsPacket : public FOpenXRAPIPacketBase`  
_L426-434_
- inherits: `FOpenXRAPIPacketBase`
- L428 _public member_ `XrSession Session;`
- L429 _public member_ `TArray<int64> Formats;`
- L431 _public prototype_ `FOpenXREnumerateSwapchainFormatsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateSwapchainPacket`  
`struct FOpenXRCreateSwapchainPacket : public FOpenXRAPIPacketBase`  
_L436-445_
- inherits: `FOpenXRAPIPacketBase`
- L438 _public member_ `XrSession Session;`
- L439 _public member_ `XrSwapchainCreateInfo SwapchainCreateInfo;`
- L440 _public member_ `XrSwapchain Swapchain;`
- L442 _public prototype_ `FOpenXRCreateSwapchainPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRDestroySwapchainPacket`  
`struct FOpenXRDestroySwapchainPacket : public FOpenXRAPIPacketBase`  
_L447-454_
- inherits: `FOpenXRAPIPacketBase`
- L449 _public member_ `XrSwapchain Swapchain;`
- L451 _public prototype_ `FOpenXRDestroySwapchainPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateSwapchainImagesPacket`  
`struct FOpenXREnumerateSwapchainImagesPacket : public FOpenXRAPIPacketBase`  
_L456-464_
- inherits: `FOpenXRAPIPacketBase`
- L458 _public member_ `XrSwapchain Swapchain;`
- L459 _public member_ `TArray<XrSwapchainImageBaseHeader> Images;` — This will have...another 'real' array of images tied to API
- L461 _public prototype_ `FOpenXREnumerateSwapchainImagesPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRAcquireSwapchainImagePacket`  
`struct FOpenXRAcquireSwapchainImagePacket : public FOpenXRAPIPacketBase`  
_L466-475_
- inherits: `FOpenXRAPIPacketBase`
- L468 _public member_ `XrSwapchain Swapchain;`
- L469 _public member_ `XrSwapchainImageAcquireInfo AcquireInfo;`
- L470 _public member_ `uint32 Index;`
- L472 _public prototype_ `FOpenXRAcquireSwapchainImagePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRWaitSwapchainImagePacket`  
`struct FOpenXRWaitSwapchainImagePacket : public FOpenXRAPIPacketBase`  
_L477-485_
- inherits: `FOpenXRAPIPacketBase`
- L479 _public member_ `XrSwapchain Swapchain;`
- L480 _public member_ `XrSwapchainImageWaitInfo WaitInfo;`
- L482 _public prototype_ `FOpenXRWaitSwapchainImagePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRReleaseSwapchainImagePacket`  
`struct FOpenXRReleaseSwapchainImagePacket : public FOpenXRAPIPacketBase`  
_L487-495_
- inherits: `FOpenXRAPIPacketBase`
- L489 _public member_ `XrSwapchain Swapchain;`
- L490 _public member_ `XrSwapchainImageReleaseInfo ReleaseInfo;`
- L492 _public prototype_ `FOpenXRReleaseSwapchainImagePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRBeginSessionPacket`  
`struct FOpenXRBeginSessionPacket : public FOpenXRAPIPacketBase`  
_L497-505_
- inherits: `FOpenXRAPIPacketBase`
- L499 _public member_ `XrSession Session;`
- L500 _public member_ `XrSessionBeginInfo SessionBeginInfo;`
- L502 _public prototype_ `FOpenXRBeginSessionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREndSessionPacket`  
`struct FOpenXREndSessionPacket : public FOpenXRAPIPacketBase`  
_L507-514_
- inherits: `FOpenXRAPIPacketBase`
- L509 _public member_ `XrSession Session;`
- L511 _public prototype_ `FOpenXREndSessionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRRequestExitSessionPacket`  
`struct FOpenXRRequestExitSessionPacket : public FOpenXRAPIPacketBase`  
_L516-523_
- inherits: `FOpenXRAPIPacketBase`
- L518 _public member_ `XrSession Session;`
- L520 _public prototype_ `FOpenXRRequestExitSessionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRWaitFramePacket`  
`struct FOpenXRWaitFramePacket : public FOpenXRAPIPacketBase`  
_L525-534_
- inherits: `FOpenXRAPIPacketBase`
- L527 _public member_ `XrSession Session;`
- L528 _public member_ `XrFrameWaitInfo FrameWaitInfo;`
- L529 _public member_ `XrFrameState FrameState;`
- L531 _public prototype_ `FOpenXRWaitFramePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRBeginFramePacket`  
`struct FOpenXRBeginFramePacket : public FOpenXRAPIPacketBase`  
_L536-544_
- inherits: `FOpenXRAPIPacketBase`
- L538 _public member_ `XrSession Session;`
- L539 _public member_ `XrFrameBeginInfo FrameBeginInfo;`
- L541 _public prototype_ `FOpenXRBeginFramePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREndFramePacket`  
`struct FOpenXREndFramePacket : public FOpenXRAPIPacketBase`  
_L546-567_
- inherits: `FOpenXRAPIPacketBase`
- L548 _public member_ `XrSession Session;`
- L557 _public member_ `XrTime DisplayTime;` — typedef struct XrFrameEndInfo { XrStructureType                               type; const void* XR_MAY_ALIAS                      next; XrTime                                        displayTime; XrEnvironmentBlendMode                        environmentBlendMode; uint32_t                                      layerCount; const XrCompositionLayerBaseHeader* const* layers; } XrFrameEndInfo;
- L558 _public member_ `XrEnvironmentBlendMode EnvironmentBlendMode;`
- L559 _public member_ `TArray<XrCompositionLayerBaseHeader> Layers;` — source memory is not contiguous
- L560 _public member_ `TArray<XrCompositionLayerQuad> QuadLayers;`
- L561 _public member_ `TArray<XrCompositionLayerProjection> ProjectionLayers;`
- L562 _public member_ `TArray<XrCompositionLayerProjectionView> ProjectionViews;`
- L564 _public prototype_ `FOpenXREndFramePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRLocateViewsPacket`  
`struct FOpenXRLocateViewsPacket : public FOpenXRAPIPacketBase`  
_L569-579_
- inherits: `FOpenXRAPIPacketBase`
- L571 _public member_ `XrSession Session;`
- L572 _public member_ `XrViewLocateInfo ViewLocateInfo;`
- L573 _public member_ `XrViewState ViewState;`
- L574 _public member_ `TArray<XrView> Views;`
- L576 _public prototype_ `FOpenXRLocateViewsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRStringToPathPacket`  
`struct FOpenXRStringToPathPacket : public FOpenXRAPIPacketBase`  
_L581-590_
- inherits: `FOpenXRAPIPacketBase`
- L583 _public member_ `XrInstance Instance;`
- L584 _public member_ `TStaticArray<ANSICHAR, XR_MAX_PATH_LENGTH> PathStringToWrite;`
- L585 _public member_ `XrPath GeneratedPath;`
- L587 _public prototype_ `FOpenXRStringToPathPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRPathToStringPacket`  
`struct FOpenXRPathToStringPacket : public FOpenXRAPIPacketBase`  
_L592-601_
- inherits: `FOpenXRAPIPacketBase`
- L594 _public member_ `XrInstance Instance;`
- L595 _public member_ `XrPath ExistingPath;`
- L596 _public member_ `TStaticArray<ANSICHAR, XR_MAX_PATH_LENGTH> PathStringToRead;`
- L598 _public prototype_ `FOpenXRPathToStringPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateActionSetPacket`  
`struct FOpenXRCreateActionSetPacket : public FOpenXRAPIPacketBase`  
_L603-612_
- inherits: `FOpenXRAPIPacketBase`
- L605 _public member_ `XrInstance Instance;`
- L606 _public member_ `XrActionSetCreateInfo ActionSetCreateInfo;`
- L607 _public member_ `XrActionSet ActionSet;`
- L609 _public prototype_ `FOpenXRCreateActionSetPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRDestroyActionSetPacket`  
`struct FOpenXRDestroyActionSetPacket : public FOpenXRAPIPacketBase`  
_L614-621_
- inherits: `FOpenXRAPIPacketBase`
- L616 _public member_ `XrActionSet ActionSet;`
- L618 _public prototype_ `FOpenXRDestroyActionSetPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRCreateActionPacket`  
`struct FOpenXRCreateActionPacket : public FOpenXRAPIPacketBase`  
_L623-645_
- inherits: `FOpenXRAPIPacketBase`
- L625 _public member_ `XrActionSet ActionSet;`
- L635 _public member_ `TStaticArray<ANSICHAR, XR_MAX_ACTION_NAME_SIZE> ActionName;` — typedef struct XrActionCreateInfo { XrStructureType             type; const void* XR_MAY_ALIAS    next; char                        actionName[XR_MAX_ACTION_NAME_SIZE]; XrActionType                actionType; uint32_t                    countSubactionPaths; const XrPath* subactionPaths; char                        localizedActionName[XR_MAX_LOCALIZED_ACTION_NAME_SIZE]; } XrActionCreateInfo;
- L636 _public member_ `XrActionType ActionType;`
- L637 _public member_ `TArray<XrPath> SubactionPaths;`
- L638 _public member_ `TStaticArray<ANSICHAR, XR_MAX_LOCALIZED_ACTION_NAME_SIZE> LocalizedActionName;`
- L640 _public member_ `XrAction Action;`
- L642 _public prototype_ `FOpenXRCreateActionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRDestroyActionPacket`  
`struct FOpenXRDestroyActionPacket : public FOpenXRAPIPacketBase`  
_L647-654_
- inherits: `FOpenXRAPIPacketBase`
- L649 _public member_ `XrAction Action;`
- L651 _public prototype_ `FOpenXRDestroyActionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRSuggestInteractionProfileBindingsPacket`  
`struct FOpenXRSuggestInteractionProfileBindingsPacket : public FOpenXRAPIPacketBase`  
_L656-673_
- inherits: `FOpenXRAPIPacketBase`
- L658 _public member_ `XrInstance Instance;`
- L667 _public member_ `XrPath InteractionProfile;` — typedef struct XrInteractionProfileSuggestedBinding { XrStructureType                    type; const void* XR_MAY_ALIAS           next; XrPath                             interactionProfile; uint32_t                           countSuggestedBindings; const XrActionSuggestedBinding* suggestedBindings; } XrInteractionProfileSuggestedBinding;
- L668 _public member_ `TArray<XrActionSuggestedBinding> SuggestedBindings;`
- L670 _public prototype_ `FOpenXRSuggestInteractionProfileBindingsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRAttachSessionActionSetsPacket`  
`struct FOpenXRAttachSessionActionSetsPacket : public FOpenXRAPIPacketBase`  
_L675-689_
- inherits: `FOpenXRAPIPacketBase`
- L677 _public member_ `XrSession Session;`
- L684 _public member_ `TArray<XrActionSet> ActionSets;` — typedef struct XrSessionActionSetsAttachInfo { XrStructureType             type; const void* XR_MAY_ALIAS    next; uint32_t                    countActionSets; const XrActionSet* actionSets; } XrSessionActionSetsAttachInfo;
- L686 _public prototype_ `FOpenXRAttachSessionActionSetsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetCurrentInteractionProfilePacket`  
`struct FOpenXRGetCurrentInteractionProfilePacket : public FOpenXRAPIPacketBase`  
_L691-700_
- inherits: `FOpenXRAPIPacketBase`
- L693 _public member_ `XrSession Session;`
- L694 _public member_ `XrPath TopLevelUserPath;`
- L695 _public member_ `XrInteractionProfileState InteractionProfile;`
- L697 _public prototype_ `FOpenXRGetCurrentInteractionProfilePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetActionStateBooleanPacket`  
`struct FOpenXRGetActionStateBooleanPacket : public FOpenXRAPIPacketBase`  
_L702-711_
- inherits: `FOpenXRAPIPacketBase`
- L704 _public member_ `XrSession Session;`
- L705 _public member_ `XrActionStateGetInfo GetInfoBoolean;`
- L706 _public member_ `XrActionStateBoolean BooleanState;`
- L708 _public prototype_ `FOpenXRGetActionStateBooleanPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetActionStateFloatPacket`  
`struct FOpenXRGetActionStateFloatPacket : public FOpenXRAPIPacketBase`  
_L713-722_
- inherits: `FOpenXRAPIPacketBase`
- L715 _public member_ `XrSession Session;`
- L716 _public member_ `XrActionStateGetInfo GetInfoFloat;`
- L717 _public member_ `XrActionStateFloat FloatState;`
- L719 _public prototype_ `FOpenXRGetActionStateFloatPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetActionStateVector2fPacket`  
`struct FOpenXRGetActionStateVector2fPacket : public FOpenXRAPIPacketBase`  
_L724-733_
- inherits: `FOpenXRAPIPacketBase`
- L726 _public member_ `XrSession Session;`
- L727 _public member_ `XrActionStateGetInfo GetInfoVector2f;`
- L728 _public member_ `XrActionStateVector2f Vector2fState;`
- L730 _public prototype_ `FOpenXRGetActionStateVector2fPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetActionStatePosePacket`  
`struct FOpenXRGetActionStatePosePacket : public FOpenXRAPIPacketBase`  
_L735-744_
- inherits: `FOpenXRAPIPacketBase`
- L737 _public member_ `XrSession Session;`
- L738 _public member_ `XrActionStateGetInfo GetInfoPose;`
- L739 _public member_ `XrActionStatePose PoseState;`
- L741 _public prototype_ `FOpenXRGetActionStatePosePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRSyncActionsPacket`  
`struct FOpenXRSyncActionsPacket : public FOpenXRAPIPacketBase`  
_L746-760_
- inherits: `FOpenXRAPIPacketBase`
- L748 _public member_ `XrSession Session;`
- L755 _public member_ `TArray<XrActiveActionSet> ActiveActionSets;` — typedef struct XrActionsSyncInfo { XrStructureType             type; const void* XR_MAY_ALIAS    next; uint32_t                    countActiveActionSets; const XrActiveActionSet* activeActionSets; } XrActionsSyncInfo;
- L757 _public prototype_ `FOpenXRSyncActionsPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXREnumerateBoundSourcesForActionPacket`  
`struct FOpenXREnumerateBoundSourcesForActionPacket : public FOpenXRAPIPacketBase`  
_L762-771_
- inherits: `FOpenXRAPIPacketBase`
- L764 _public member_ `XrSession Session;`
- L765 _public member_ `XrBoundSourcesForActionEnumerateInfo EnumerateInfo;`
- L766 _public member_ `TArray<XrPath> Sources;`
- L768 _public prototype_ `FOpenXREnumerateBoundSourcesForActionPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetInputSourceLocalizedNamePacket`  
`struct FOpenXRGetInputSourceLocalizedNamePacket : public FOpenXRAPIPacketBase`  
_L773-782_
- inherits: `FOpenXRAPIPacketBase`
- L775 _public member_ `XrSession Session;`
- L776 _public member_ `XrInputSourceLocalizedNameGetInfo NameGetInfo;`
- L777 _public member_ `TStaticArray<ANSICHAR, XR_MAX_PATH_LENGTH> LocalizedName;` — Not sure if this size is correct
- L779 _public prototype_ `FOpenXRGetInputSourceLocalizedNamePacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRApplyHapticFeedbackPacket`  
`struct FOpenXRApplyHapticFeedbackPacket : public FOpenXRAPIPacketBase`  
_L784-793_
- inherits: `FOpenXRAPIPacketBase`
- L786 _public member_ `XrSession Session;`
- L787 _public member_ `XrHapticActionInfo HapticActionInfo;`
- L788 _public member_ `XrHapticBaseHeader HapticFeedback;` — This is actually a different struct underneath
- L790 _public prototype_ `FOpenXRApplyHapticFeedbackPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRStopHapticFeedbackPacket`  
`struct FOpenXRStopHapticFeedbackPacket : public FOpenXRAPIPacketBase`  
_L795-803_
- inherits: `FOpenXRAPIPacketBase`
- L797 _public member_ `XrSession Session;`
- L798 _public member_ `XrHapticActionInfo HapticActionInfo;`
- L800 _public prototype_ `FOpenXRStopHapticFeedbackPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRInitializeLoaderKHRPacket`  
`struct FOpenXRInitializeLoaderKHRPacket : public FOpenXRAPIPacketBase`  
_L806-815_
- inherits: `FOpenXRAPIPacketBase`
- desc: XR_KHR_loader_init
- L808 _public member_ `XrLoaderInitInfoBaseHeaderKHR LoaderInitInfo;`
- L812 _public prototype_ `FOpenXRInitializeLoaderKHRPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetVisibilityMaskKHRPacket`  
`struct FOpenXRGetVisibilityMaskKHRPacket : public FOpenXRAPIPacketBase`  
_L818-841_
- inherits: `FOpenXRAPIPacketBase`
- desc: XR_KHR_visibility_mask
- L820 _public member_ `XrSession Session;`
- L821 _public member_ `XrViewConfigurationType ViewConfigurationType;`
- L822 _public member_ `uint32_t ViewIndex;`
- L823 _public member_ `XrVisibilityMaskTypeKHR VisibilityMaskType;`
- L835 _public member_ `TArray<XrVector2f> Vertices;` — typedef struct XrVisibilityMaskKHR { XrStructureType       type; void* XR_MAY_ALIAS    next; uint32_t              vertexCapacityInput; uint32_t              vertexCountOutput; XrVector2f* vertices; uint32_t              indexCapacityInput; uint32_t              indexCountOutput; uint32_t* indices; } XrVisibilityMaskKHR;
- L836 _public member_ `TArray<uint32> Indices;`
- L838 _public prototype_ `FOpenXRGetVisibilityMaskKHRPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetD3D11GraphicsRequirementsKHRPacket`  
`struct FOpenXRGetD3D11GraphicsRequirementsKHRPacket : public FOpenXRAPIPacketBase`  
_L845-854_
- inherits: `FOpenXRAPIPacketBase`
- desc: XR_KHR_D3D11_enable
- L847 _public member_ `XrInstance Instance;`
- L848 _public member_ `XrSystemId SystemId;`
- L849 _public member_ `XrGraphicsRequirementsD3D11KHR GraphicsRequirementsD3D11;`
- L851 _public prototype_ `FOpenXRGetD3D11GraphicsRequirementsKHRPacket(XrResult InResult);`

#### struct `UE::XRScribe::FOpenXRGetD3D12GraphicsRequirementsKHRPacket`  
`struct FOpenXRGetD3D12GraphicsRequirementsKHRPacket : public FOpenXRAPIPacketBase`  
_L859-868_
- inherits: `FOpenXRAPIPacketBase`
- desc: XR_KHR_D3D12_enable
- L861 _public member_ `XrInstance Instance;`
- L862 _public member_ `XrSystemId SystemId;`
- L863 _public member_ `XrGraphicsRequirementsD3D12KHR GraphicsRequirementsD3D12;`
- L865 _public prototype_ `FOpenXRGetD3D12GraphicsRequirementsKHRPacket(XrResult InResult);`

#### Free symbols / members of external scopes

- L12 _prototype_ `FArchive& operator<<(FArchive& Ar, XrApiLayerProperties& LayerProperty);` — OpenXR types operator<< implementation has to be in the global namespace
- L13 _prototype_ `FArchive& operator<<(FArchive& Ar, XrExtensionProperties& ExtensionProperty);`
- L14 _prototype_ `FArchive& operator<<(FArchive& Ar, XrSystemGetInfo& SystemGetInfo);`
- L15 _prototype_ `FArchive& operator<<(FArchive& Ar, XrSystemProperties& SystemProperties);`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace XRScribe` (scope `UE`)
