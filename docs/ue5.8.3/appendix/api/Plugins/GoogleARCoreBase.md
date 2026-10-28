# Plugins / GoogleARCoreBase

- module root: `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase`
- headers: 23; symbols: 623
- symbol kinds: class=34, delegate=4, enum=15, enumerator=81, function=62, macro=6, member=121, prototype=278, struct=5, typedef=17
- PrivateDependencyModuleNames: AndroidPermission, Core, CoreUObject, Engine, EngineSettings, GoogleARCoreRendering, GoogleARCoreSDK, Launch, MRMesh, OpenGL, OpenGLDrv, ProceduralMeshComponent, RHI, RenderCore, Slate, SlateCore, UElibPNG, Vulkan, VulkanRHI, XRBase, zlib
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: AugmentedReality, HeadMountedDisplay
- PublicIncludePathModuleNames: TargetPlatform

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreAPI.h` (Private)


#### enum `EGoogleARCoreAPIStatus`  
`enum class EGoogleARCoreAPIStatus : int`  
_L26-117_
- L29 _public enumerator_ `AR_SUCCESS = 0` — The operation was successful.
- L33 _public enumerator_ `AR_ERROR_INVALID_ARGUMENT = -1` — One of the arguments was invalid, either null or not appropriate for the operation requested.
- L37 _public enumerator_ `AR_ERROR_FATAL = -2` — An internal error occurred that the application should not attempt to recover from.
- L41 _public enumerator_ `AR_ERROR_SESSION_PAUSED = -3` — An operation was attempted that requires the session be running, but the session was paused.
- L45 _public enumerator_ `AR_ERROR_SESSION_NOT_PAUSED = -4` — An operation was attempted that requires the session be paused, but the session was running.
- L49 _public enumerator_ `AR_ERROR_NOT_TRACKING = -5` — An operation was attempted that the session be in the TRACKING state, but the session was not.
- L53 _public enumerator_ `AR_ERROR_TEXTURE_NOT_SET = -6` — A texture name was not set by calling ArSession_setCameraTextureName() before the first call to ArSession_update()
- L56 _public enumerator_ `AR_ERROR_MISSING_GL_CONTEXT = -7` — An operation required GL context but one was not available.
- L60 _public enumerator_ `AR_ERROR_UNSUPPORTED_CONFIGURATION = -8` — The configuration supplied to ArSession_configure() was unsupported. To avoid this error, ensure that Session_checkSupported() returns true.
- L64 _public enumerator_ `AR_ERROR_CAMERA_PERMISSION_NOT_GRANTED = -9` — The android camera permission has not been granted prior to calling ArSession_resume()
- L70 _public enumerator_ `AR_ERROR_DEADLINE_EXCEEDED = -10` — Acquire failed because the object being acquired is already released. For example, this happens if the application holds an ::ArFrame beyond the next call to ArSession_update(), and then tries to acquire its point cloud.
- L75 _public enumerator_ `AR_ERROR_RESOURCE_EXHAUSTED = -11` — There are no available resources to complete the operation.  In cases of @c acquire methods returning this error, This can be avoided by releasing previously acquired objects before acquiring new ones.
- L80 _public enumerator_ `AR_ERROR_NOT_YET_AVAILABLE = -12` — Acquire failed because the data isn't available yet for the current frame. For example, acquire the image metadata may fail with this error because the camera hasn't fully started.
- L84 _public enumerator_ `AR_ERROR_CAMERA_NOT_AVAILABLE = -13` — The android camera has been reallocated to a higher priority app or is otherwise unavailable.
- L87 _public enumerator_ `AR_ERROR_DATA_INVALID_FORMAT = -18` — The data passed in for this operation was not in a valid format.
- L91 _public enumerator_ `AR_ERROR_DATA_UNSUPPORTED_VERSION = -19` — The data passed in for this operation is not supported by this version of the SDK.
- L98 _public enumerator_ `AR_ERROR_ILLEGAL_STATE = -20` — A function has been invoked at an illegal or inappropriate time. A message will be printed to logcat with additional details for the developer.  For example, ArSession_resume() will return this status if the camera configuration was changed and there are any unreleased images
- L101 _public enumerator_ `AR_UNAVAILABLE_ARCORE_NOT_INSTALLED = -100` — The ARCore APK is not installed on this device.
- L104 _public enumerator_ `AR_UNAVAILABLE_DEVICE_NOT_COMPATIBLE = -101` — The device is not currently compatible with ARCore.
- L108 _public enumerator_ `AR_UNAVAILABLE_APK_TOO_OLD = -103` — The ARCore APK currently installed on device is too old and needs to be updated.
- L112 _public enumerator_ `AR_UNAVAILABLE_SDK_TOO_OLD = -104` — The ARCore APK currently installed no longer supports the ARCore SDK that the application was built with.
- L116 _public enumerator_ `AR_UNAVAILABLE_USER_DECLINED_INSTALLATION = -105` — The user declined installation of the ARCore APK during this run of the application and the current request was not marked as user-initiated.

#### struct `FARCorePointer`  
`struct FARCorePointer`  
_L155-181_
- reflection: `USTRUCT()`
- desc: A wrapper class that stores a native pointer internally, which can be used as the key type for TMap
- L159 _public prototype_ `FARCorePointer() = default;`
- L161 _public function_ `FARCorePointer(void* InPointer) : RawPointer(InPointer)`
- L164 _public function_ `template<class T> T* AsRawPointer() const`
- L174 _public function_ `bool operator==(const FARCorePointer& Other) const`
- L180 _private member_ `void* RawPointer = nullptr;`

#### class `UGoogleARCoreUObjectManager`  
`class UGoogleARCoreUObjectManager : public UObject`  
_L184-237_
- reflection: `UCLASS()`
- inherits: `UObject`
- L188 _private prototype_ `UGoogleARCoreUObjectManager();`
- L189 _private prototype_ `virtual ~UGoogleARCoreUObjectManager();`
- L193 _public member_ `TObjectPtr<UGoogleARCorePointCloud> LatestPointCloud;` — `UPROPERTY()`
- L197 _public member_ `TMap<FARCorePointer, FTrackedGeometryGroup> TrackableHandleMap;` — `UPROPERTY()` — pointer type is ArTrackable*
- L201 _public member_ `TMap<FARCorePointer, TObjectPtr<UARPin>> HandleToAnchorMap;` — `UPROPERTY()` — pointer type is ArAnchor*
- L203 _public prototype_ `void ClearTrackables();`
- L206 _public prototype_ `UARTrackedGeometry* RemoveTrackable(FARCorePointer Pointer);` — Returns the removed geometry
- L209 _public prototype_ `const FTrackedGeometryGroup* GetBaseTrackableFromHandle(ArTrackable* TrackableHandle, FGoogleARCoreSession* Session);`
- L212 _public function_ `template<class T> T* GetTrackableFromHandle(ArTrackable* TrackableHandle, FGoogleARCoreSession* Session)`
- L218 _public prototype_ `void DumpTrackableHandleMap(const ArSession* SessionHandle);`
- L220 _public prototype_ `void RemoveInvalidTrackables(const TArray<ArTrackable*>& ValidTrackables, TArray<UARPin*>& ARPinsToRemove);`
- L223 _public prototype_ `UARSessionConfig& AccessSessionConfig();`
- L225 _public prototype_ `void OnSpawnARActor(AARActor* NewARActor, UARComponent* NewARComponent, FGuid NativeID);`
- L228 _public member_ `FDelegateHandle SpawnARActorDelegateHandle;` — for networked callbacks
- L233 _private prototype_ `FGuid TrackableHandleToGuid(const ArTrackable* TrackableHandle);` — for mapping ArTrackable* to FGuids and back
- L234 _private prototype_ `ArTrackable* GuidToTrackableHandle(const FGuid& Guid);`
- L236 _private member_ `FGuid BaseGuid;`

#### class `FGoogleARCoreAPKManager`  
`class FGoogleARCoreAPKManager`  
_L239-244_
- L242 _public prototype_ `static EGoogleARCoreAvailability CheckARCoreAPKAvailability();`
- L243 _public prototype_ `static EGoogleARCoreAPIStatus RequestInstall(bool bUserRequestedInstall, EGoogleARCoreInstallStatus& OutInstallStatus);`

#### class `FGoogleARCoreSession`  
`class FGoogleARCoreSession : public TSharedFromThis<FGoogleARCoreSession>, public FGCObject`  
_L247-323_
- inherits: `TSharedFromThis<FGoogleARCoreSession>,FGCObject`
- L251 _public prototype_ `static TSharedPtr<FGoogleARCoreSession> CreateARCoreSession();`
- L253 _public prototype_ `FGoogleARCoreSession();`
- L254 _public prototype_ `~FGoogleARCoreSession();`
- L257 _public prototype_ `EGoogleARCoreAPIStatus GetSessionCreateStatus();` — Properties
- L258 _public prototype_ `UGoogleARCoreUObjectManager* GetUObjectManager();`
- L259 _public prototype_ `float GetWorldToMeterScale();`
- L260 _public function_ `void SetARSystem(TSharedRef<FARSupportInterface, ESPMode::ThreadSafe> InArSystem)`
- L261 _public function_ `TSharedRef<FARSupportInterface, ESPMode::ThreadSafe> GetARSystem()`
- L263 _public prototype_ `ArSession* GetHandle();`
- L267 _public prototype_ `bool IsConfigSupported(const UARSessionConfig& Config);` — Lifecycle
- L268 _public prototype_ `EGoogleARCoreAPIStatus ConfigSession(const UARSessionConfig& Config);`
- L269 _public prototype_ `const UARSessionConfig* GetCurrentSessionConfig();`
- L270 _public prototype_ `TArray<FGoogleARCoreCameraConfig> GetSupportedCameraConfig(EGoogleARCoreCameraFacing CameraFacing);`
- L271 _public prototype_ `EGoogleARCoreAPIStatus SetCameraConfig(FGoogleARCoreCameraConfig CameraConfig);`
- L272 _public prototype_ `void GetARCameraConfig(FGoogleARCoreCameraConfig& OutCurrentCameraConfig);`
- L273 _public prototype_ `int AddRuntimeAugmentedImage(UGoogleARCoreAugmentedImageDatabase* TargetImageDatabase, const TArray<uint8>& ImageGrayscalePixels, int ImageWidth, int ImageHeight, FString ImageName, float ImageWidthInMeter);`
- L275 _public prototype_ `bool AddRuntimeCandidateImage(UARSessionConfig* SessionConfig, const TArray<uint8>& ImageGrayscalePixels, int ImageWidth, int ImageHeight, FString FriendlyName, float PhysicalWidth);`
- L277 _public prototype_ `EGoogleARCoreAPIStatus Resume();`
- L278 _public prototype_ `EGoogleARCoreAPIStatus Pause();`
- L279 _public prototype_ `EGoogleARCoreAPIStatus Update(float WorldToMeterScale);`
- L280 _public prototype_ `const FGoogleARCoreFrame* GetLatestFrame();`
- L281 _public prototype_ `uint32 GetFrameNum();`
- L283 _public prototype_ `void SetCameraTextureIds(const TArray<uint32_t>& TextureIds);`
- L284 _public prototype_ `void SetDisplayGeometry(int Rotation, int Width, int Height);`
- L287 _public prototype_ `EGoogleARCoreAPIStatus CreateARAnchor(const FTransform& TransfromInTrackingSpace, UARTrackedGeometry* TrackedGeometry, USceneComponent* ComponentToPin, FName InDebugName, UARPin*& OutAnchor);` — Anchor API
- L288 _public prototype_ `bool TryGetOrCreatePinForNativeResource(void* InNativeResource, const FString& InPinName, UARPin*& OutPin);`
- L289 _public prototype_ `void DetachAnchor(UARPin* Anchor);`
- L291 _public prototype_ `void GetAllAnchors(TArray<UARPin*>& OutAnchors) const;`
- L292 _public prototype_ `template< class T > void GetAllTrackables(TArray<T*>& OutARCoreTrackableList);`
- L294 _public prototype_ `void* GetLatestFrameRawPointer();`
- L296 _public prototype_ `bool IsSceneDepthEnabled() const;`
- L298 _public function_ `bool HasNewFrame() const`
- L301 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L302 _private function_ `virtual FString GetReferencerName() const override`
- L307 _private member_ `EGoogleARCoreAPIStatus SessionCreateStatus;`
- L308 _private member_ `TObjectPtr<const UARSessionConfig> SessionConfig;`
- L309 _private member_ `FGoogleARCoreFrame* LatestFrame;`
- L310 _private member_ `TObjectPtr<UGoogleARCoreUObjectManager> UObjectManager;`
- L311 _private member_ `float CachedWorldToMeterScale;`
- L312 _private member_ `uint32 FrameNumber;`
- L314 _private member_ `TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSystem;`
- L316 _private member_ `ArSession* SessionHandle = nullptr;`
- L317 _private member_ `ArConfig* ConfigHandle = nullptr;`
- L318 _private member_ `TMap<const UARSessionConfig*, ArAugmentedImageDatabase*> ImageDatabaseMap;`
- L322 _private member_ `bool bHasNewFrame = false;` — Stores if current frame has new data. Set on every Update() call.
- L433 _function_ `template< class T > void FGoogleARCoreSession::GetAllTrackables(TArray<T*>& OutARCoreTrackableList)`

#### class `FGoogleARCoreFrame`  
`class FGoogleARCoreFrame`  
_L325-397_
- L330 _public prototype_ `FGoogleARCoreFrame(FGoogleARCoreSession* Session);`
- L331 _public prototype_ `~FGoogleARCoreFrame();`
- L333 _public prototype_ `void Init();`
- L335 _public prototype_ `void Update(float WorldToMeterScale);`
- L337 _public prototype_ `bool UpdateCameraTexture(UARCoreCameraTexture* InCameraTexture) const;`
- L338 _public prototype_ `void UpdateDepthTexture(UARCoreDepthTexture*& OutDepthTexture) const;`
- L340 _public prototype_ `FTransform GetCameraPose() const;`
- L341 _public prototype_ `int64 GetCameraTimestamp() const;`
- L342 _public prototype_ `EGoogleARCoreTrackingState GetCameraTrackingState() const;`
- L343 _public prototype_ `EGoogleARCoreTrackingFailureReason GetCameraTrackingFailureReason() const;`
- L345 _public prototype_ `void GetUpdatedAnchors(TArray<UARPin*>& OutUpdatedAnchors) const;`
- L346 _public prototype_ `template< class T > void GetUpdatedTrackables(TArray<T*>& OutARCoreTrackableList) const;`
- L348 _public prototype_ `void ARLineTrace(const FVector2D& ScreenPosition, EGoogleARCoreLineTraceChannel RequestedTraceChannels, TArray<FARTraceResult>& OutHitResults) const;`
- L349 _public prototype_ `void ARLineTrace(const FVector& Start, const FVector& End, EGoogleARCoreLineTraceChannel RequestedTraceChannels, TArray<FARTraceResult>& OutHitResults) const;`
- L351 _public prototype_ `bool IsDisplayRotationChanged() const;`
- L352 _public prototype_ `FMatrix GetProjectionMatrix() const;`
- L353 _public prototype_ `void TransformDisplayUvCoords(const TArray<float>& UvCoords, TArray<float>& OutUvCoords) const;`
- L355 _public prototype_ `FGoogleARCoreLightEstimate GetLightEstimate() const;`
- L356 _public prototype_ `EGoogleARCoreAPIStatus GetPointCloud(UGoogleARCorePointCloud*& OutLatestPointCloud) const;`
- L357 _public prototype_ `EGoogleARCoreAPIStatus AcquirePointCloud(UGoogleARCorePointCloud*& OutLatestPointCloud) const;`
- L358 _public prototype_ `EGoogleARCoreAPIStatus AcquireCameraImage(UGoogleARCoreCameraImage *&OutCameraImage) const;`
- L359 _public prototype_ `EGoogleARCoreAPIStatus GetCameraImageIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const;`
- L360 _public prototype_ `EGoogleARCoreAPIStatus GetCameraTextureIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const;`
- L362 _public prototype_ `void TransformARCoordinates2D(EGoogleARCoreCoordinates2DType InputCoordinatesType, const TArray<FVector2D>& InputCoordinates, EGoogleARCoreCoordinates2DType OutputCoordinatesType, TArray<FVector2D>& OutputCoordinates) const;`
- L365 _public function_ `uint32 GetCameraTextureId() const`
- L368 _public function_ `ArFrame* GetHandle()`
- L369 _public prototype_ `static TArray<ArTrackable*> GetTrackables(const ArSession* SessionHandle, ArTrackableList* ListHandle, bool bRemoveSubsumedPlanes);`
- L373 _private member_ `FGoogleARCoreSession* Session;`
- L374 _private member_ `FTransform LatestCameraPose;`
- L375 _private member_ `int64 LatestCameraTimestamp;`
- L376 _private member_ `uint32 CameraTextureId = 0;`
- L377 _private member_ `EGoogleARCoreTrackingState LatestCameraTrackingState;`
- L378 _private member_ `EGoogleARCoreTrackingFailureReason LatestCameraTrackingFailureReason;`
- L380 _private member_ `EGoogleARCoreAPIStatus LatestPointCloudStatus;`
- L381 _private member_ `EGoogleARCoreAPIStatus LatestImageMetadataStatus;`
- L383 _private member_ `TArray<UARPin*> UpdatedAnchors;`
- L386 _private member_ `const ArSession* SessionHandle = nullptr;`
- L387 _private member_ `ArFrame* FrameHandle = nullptr;`
- L388 _private member_ `ArCamera* CameraHandle = nullptr;`
- L389 _private member_ `ArPose* SketchPoseHandle = nullptr;`
- L390 _private member_ `ArImageMetadata* LatestImageMetadata = nullptr;`
- L392 _private member_ `void* VulkanHardwareBuffer = nullptr;` — This is used instead of CameraTextureId when using Vulkan
- L394 _private prototype_ `void FilterLineTraceResults(ArHitResultList* HitResultList, EGoogleARCoreLineTraceChannel RequestedTraceChannels, TArray<FARTraceResult>& OutHitResults, float MaxDistance = TNumericLimits<float>::Max()) const;`
- L400 _function_ `template< class T > void FGoogleARCoreFrame::GetUpdatedTrackables(TArray<T*>& OutARCoreTrackableList) const`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGoogleARCoreAPI, Log, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGoogleARCoreAPI, Log, All);`
- L120 _function_ `static ArTrackableType GetTrackableType(UClass* ClassType)`
- L169 _function_ `friend uint32 GetTypeHash(const FARCorePointer& Pointer)`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreAndroidHelper.h` (Private)


#### enum `ARCoreDisplayRotation`  
`enum class ARCoreDisplayRotation : int32`  
_L11-18_
- desc: Matches return values from android.view.display.getRotation()
- L13 _public enumerator_ `Rotation0 = 0`
- L14 _public enumerator_ `Rotation90 = 1`
- L15 _public enumerator_ `Rotation180 = 2`
- L16 _public enumerator_ `Rotation270 = 3`
- L17 _public enumerator_ `Max = 3`

#### class `FGoogleARCoreAndroidHelper`  
`class FGoogleARCoreAndroidHelper`  
_L21-50_
- desc: Wrappers for accessing Android Java stuff
- L28 _public prototype_ `static void UpdateDisplayRotation();` — Update the Android display orientation as per the android.view.Display class' getRotation() method.
- L33 _public prototype_ `static ARCoreDisplayRotation GetDisplayRotation();` — Get Andriod display orientation.
- L35 _public prototype_ `static void QueueStartSessionOnUiThread();`
- L39 _public prototype_ `static void OnApplicationCreated();` — Helpers for redirecting Android events.
- L40 _public prototype_ `static void OnApplicationDestroyed();`
- L41 _public prototype_ `static void OnApplicationPause();`
- L42 _public prototype_ `static void OnApplicationResume();`
- L43 _public prototype_ `static void OnApplicationStop();`
- L44 _public prototype_ `static void OnApplicationStart();`
- L45 _public prototype_ `static void OnDisplayOrientationChanged();`
- L49 _private member_ `static ARCoreDisplayRotation CurrentDisplayRotation;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreBaseLogCategory.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogGoogleARCore, Log, All);`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreCameraTextureResourceVulkan.h` (Private)


#### class `FARCoreCameraTextureResourceVulkan`  
`class FARCoreCameraTextureResourceVulkan : public FTextureResource`  
_L23-61_
- inherits: `FTextureResource`
- desc: Camera texture resource using the Vulkan hardware buffer provided. Known Vulkan Validation error: VUID-VkWriteDescriptorSet-descriptorType-01946 Vulkan RHI will create the image and its view with a VkSamplerYcbcrConversion, and bind it as a VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE. But using a VkSamplerYcbcrConversion requires the sampler and the image view to be bound together with a VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, which is not supported. As a workaround we perform the YCbCr conversion ourselves in the shader and do not pass VkSamplerYcbcrConversion to the sampler. The VkSamplerYcbcrConversion is still necessary for the view, which reports the validation error, and it will read the values from the external image. In the future if support for combined image sampler descriptors is provided, then it would possible to use VkSamplerYcbcrConversion natively and remove the YCbCr conversion inside the shader.
- L26 _public prototype_ `FARCoreCameraTextureResourceVulkan(const FGuid& InExternalTextureGuid, void* InHardwareBuffer, uint32 InSizeX, uint32 InSizeY);`
- L28 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L29 _public prototype_ `virtual void ReleaseRHI() override;`
- L31 _public function_ `virtual uint32 GetSizeX() const override`
- L36 _public function_ `virtual uint32 GetSizeY() const override`
- L41 _public function_ `uint32 GetTextureId() const`
- L46 _public function_ `FYCbCrConversion GetCameraYCbCrConversion() const`
- L52 _private prototype_ `void FillCameraYCbCrConversionParameters();`
- L54 _private member_ `uint32 TextureId = 0;`
- L55 _private member_ `const FGuid ExternalTextureGuid;`
- L56 _private member_ `const uint32 SizeX;`
- L57 _private member_ `const uint32 SizeY;`
- L59 _private member_ `void* HardwareBuffer = nullptr;`
- L60 _private member_ `FYCbCrConversion CameraYCbCrConversion;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreCookSupport.h` (Private)


#### class `FGoogleARCoreSessionConfigCookSupport`  
`class FGoogleARCoreSessionConfigCookSupport : public IARSessionConfigCookSupport`  
_L10-22_
- inherits: `IARSessionConfigCookSupport`
- L13 _public prototype_ `static bool SaveTextureToPNG(class UTexture2D *Tex, const FString &Filename);`
- L15 _public prototype_ `static bool PlatformSetExecutable(const TCHAR* Filename, bool bIsExecutable);`
- L18 _public prototype_ `void RegisterModuleFeature();`
- L19 _public prototype_ `void UnregisterModuleFeature();`
- L21 _public prototype_ `virtual void OnSerializeSessionConfig(UARSessionConfig* SessionConfig, FArchive& Ar, TArray<uint8>& SerializedARCandidateImageDatabase) override;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreDependencyHandler.h` (Private)


#### class `UGoogleARCoreDependencyHandler`  
`class UGoogleARCoreDependencyHandler : public UARDependencyHandler`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UARDependencyHandler`
- L16 _public prototype_ `void StartARSessionLatent(UObject* WorldContextObject, UARSessionConfig* SessionConfig, FLatentActionInfo LatentInfo) override;`
- L17 _public prototype_ `void CheckARServiceAvailability(UObject* WorldContextObject, FLatentActionInfo LatentInfo, EARServiceAvailability& OutAvailability) override;`
- L18 _public prototype_ `void InstallARService(UObject* WorldContextObject, FLatentActionInfo LatentInfo, EARServiceInstallRequestResult& OutInstallResult) override;`
- L19 _public prototype_ `void RequestARSessionPermission(UObject* WorldContextObject, UARSessionConfig* SessionConfig, FLatentActionInfo LatentInfo, EARServicePermissionRequestResult& OutPermissionResult) override;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreDevice.h` (Private)


#### enum `EARCorePermissionStatus`  
`enum class EARCorePermissionStatus : uint8`  
_L22-28_
- L24 _public enumerator_ `Unknown`
- L25 _public enumerator_ `Requested`
- L26 _public enumerator_ `Granted`
- L27 _public enumerator_ `Denied`

#### class `FGoogleARCoreDevice`  
`class FGoogleARCoreDevice`  
_L30-235_
- L33 _public prototype_ `static FGoogleARCoreDevice* GetInstance();`
- L35 _public prototype_ `FGoogleARCoreDevice();`
- L37 _public prototype_ `EGoogleARCoreAvailability CheckARCoreAPKAvailability();`
- L39 _public prototype_ `EGoogleARCoreAPIStatus RequestInstall(bool bUserRequestedInstall, EGoogleARCoreInstallStatus& OutInstallStatus);`
- L41 _public prototype_ `bool GetIsTrackingTypeSupported(EARSessionType SessionType);`
- L43 _public prototype_ `bool GetIsARCoreSessionRunning();`
- L45 _public prototype_ `FARSessionStatus GetSessionStatus();`
- L48 _public prototype_ `float GetWorldToMetersScale();` — Get Unreal Units per meter, based off of the current map's VR World to Meters setting.
- L51 _public prototype_ `void StartARCoreSessionRequest(UARSessionConfig* SessionConfig);` — Start ARSession with custom session config.
- L53 _public prototype_ `bool SetARCameraConfig(FGoogleARCoreCameraConfig CameraConfig);`
- L55 _public prototype_ `bool GetARCameraConfig(FGoogleARCoreCameraConfig& OutCurrentCameraConfig);`
- L57 _public prototype_ `bool GetIsFrontCameraSession();`
- L59 _public prototype_ `bool GetShouldInvertCulling();`
- L63 _public prototype_ `int AddRuntimeAugmentedImage(UGoogleARCoreAugmentedImageDatabase* TargetImageDatabase, const TArray<uint8>& ImageGrayscalePixels, int ImageWidth, int ImageHeight, FString ImageName, float ImageWidthInMeter);` — Add image to TargetImageDatabase and return the image index. Return -1 if the image cannot be processed.
- L66 _public prototype_ `bool AddRuntimeCandidateImage(UARSessionConfig* SessionConfig, const TArray<uint8>& ImageGrayscalePixels, int ImageWidth, int ImageHeight, FString FriendlyName, float PhysicalWidth);`
- L69 _public prototype_ `bool GetStartSessionRequestFinished();`
- L71 _public prototype_ `void PauseARCoreSession();`
- L73 _public prototype_ `void ResetARCoreSession();`
- L75 _public prototype_ `void AllocatePassthroughCameraTextures();`
- L78 _public prototype_ `FMatrix GetPassthroughCameraProjectionMatrix(FIntPoint ViewRectSize) const;` — Passthrough Camera
- L79 _public prototype_ `void GetPassthroughCameraImageUVs(const TArray<float>& InUvs, TArray<float>& OutUVs) const;`
- L80 _public prototype_ `int64 GetPassthroughCameraTimestamp() const;`
- L83 _public prototype_ `void UpdateGameFrame(UWorld* World);` — Frame
- L84 _public prototype_ `EGoogleARCoreTrackingState GetTrackingState() const;`
- L85 _public prototype_ `EGoogleARCoreTrackingFailureReason GetTrackingFailureReason() const;`
- L86 _public prototype_ `FTransform GetLatestPose() const;`
- L87 _public prototype_ `FGoogleARCoreLightEstimate GetLatestLightEstimate() const;`
- L88 _public prototype_ `EGoogleARCoreFunctionStatus GetLatestPointCloud(UGoogleARCorePointCloud*& OutLatestPointCloud) const;`
- L89 _public prototype_ `EGoogleARCoreFunctionStatus AcquireLatestPointCloud(UGoogleARCorePointCloud*& OutLatestPointCloud) const;`
- L90 _public prototype_ `EGoogleARCoreFunctionStatus AcquireCameraImage(UGoogleARCoreCameraImage *&OutLatestCameraImage);`
- L92 _public prototype_ `void TransformARCoordinates2D(EGoogleARCoreCoordinates2DType InputCoordinatesType, const TArray<FVector2D>& InputCoordinates, EGoogleARCoreCoordinates2DType OutputCoordinatesType, TArray<FVector2D>& OutputCoordinates) const;`
- L96 _public prototype_ `void ARLineTrace(const FVector2D& ScreenPosition, EGoogleARCoreLineTraceChannel TraceChannels, TArray<FARTraceResult>& OutHitResults);` — Hit test
- L97 _public prototype_ `void ARLineTrace(const FVector& Start, const FVector& End, EGoogleARCoreLineTraceChannel TraceChannels, TArray<FARTraceResult>& OutHitResults);`
- L100 _public prototype_ `EGoogleARCoreFunctionStatus CreateARPin(const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry, USceneComponent* ComponentToPin, const FName DebugName, UARPin*& OutARAnchorObject);` — Anchor, Planes
- L101 _public prototype_ `bool TryGetOrCreatePinForNativeResource(void* InNativeResource, const FString& InPinName, UARPin*& OutPin);`
- L102 _public prototype_ `void RemoveARPin(UARPin* ARAnchorObject);`
- L104 _public prototype_ `void GetAllARPins(TArray<UARPin*>& ARCoreAnchorList);`
- L105 _public prototype_ `void GetUpdatedARPins(TArray<UARPin*>& ARCoreAnchorList);`
- L108 _public function_ `template< class T > void GetUpdatedTrackables(TArray<T*>& OutARCoreTrackableList)`
- L118 _public function_ `template< class T > void GetAllTrackables(TArray<T*>& OutARCoreTrackableList)`
- L128 _public prototype_ `EGoogleARCoreFunctionStatus GetCameraImageIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics);` — Camera Intrinsics
- L129 _public prototype_ `EGoogleARCoreFunctionStatus GetCameraTextureIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics);`
- L131 _public function_ `void RunOnGameThread(TFunction<void()> Func)`
- L136 _public function_ `void GetRequiredRuntimePermissionsForConfiguration(const UARSessionConfig& Config, TArray<FString>& RuntimePermissions)`
- L142 _public prototype_ `void HandleRuntimePermissionsGranted(const TArray<FString>& Permissions, const TArray<bool>& Granted);`
- L145 _public prototype_ `void StartSessionWithRequestedConfig();` — Function that is used to call from the Android UI thread:
- L147 _public prototype_ `TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> GetARSystem();`
- L148 _public prototype_ `void SetARSystem(TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> InARSystem);`
- L150 _public prototype_ `void* GetARSessionRawPointer();`
- L151 _public prototype_ `void* GetGameThreadARFrameRawPointer();`
- L153 _public prototype_ `UARTexture* GetLastCameraTexture() const;`
- L154 _public prototype_ `UARTexture* GetDepthTexture() const;`
- L156 _public prototype_ `IYCbCrConversionQuery* GetLastCameraYCbCrConversionQuery() const;`
- L158 _public prototype_ `EARCorePermissionStatus CheckAndRequrestPermission(const UARSessionConfig& ConfigurationData);`
- L162 _private prototype_ `void OnApplicationCreated();` — Android lifecycle events.
- L163 _private prototype_ `void OnApplicationDestroyed();`
- L164 _private prototype_ `void OnApplicationPause();`
- L165 _private prototype_ `void OnApplicationResume();`
- L166 _private prototype_ `void OnApplicationStart();`
- L167 _private prototype_ `void OnApplicationStop();`
- L168 _private prototype_ `void OnDisplayOrientationChanged();`
- L171 _private prototype_ `void OnModuleLoaded();` — Unreal plugin events.
- L172 _private prototype_ `void OnModuleUnloaded();`
- L174 _private prototype_ `TSharedPtr<FGoogleARCoreSession> CreateSession();`
- L175 _private prototype_ `void StartSession();`
- L180 _private prototype_ `UARSessionConfig* AccessSessionConfig() const;`
- L183 _private member_ `TSharedPtr<FGoogleARCoreSession> ARCoreSession;`
- L184 _private member_ `TSharedPtr<FGoogleARCoreSession> FrontCameraARCoreSession;`
- L185 _private member_ `TSharedPtr<FGoogleARCoreSession> BackCameraARCoreSession;`
- L187 _private member_ `TMap<uint32, TObjectPtr<UARCoreCameraTexture>> PassthroughCameraTextures;`
- L188 _private member_ `TArray<uint32> PassthroughCameraTextureKeys;`
- L190 _private member_ `TObjectPtr<UARCoreDepthTexture> DepthTexture;`
- L192 _private member_ `FTextureRHIRef LastCameraTexture;`
- L194 _private member_ `FCriticalSection LastCameraTextureLock;`
- L196 _private member_ `uint32 LastCameraTextureId = 0;`
- L198 _private member_ `bool bIsARCoreSessionRunning;`
- L200 _private member_ `EARCorePermissionStatus PermissionStatus = EARCorePermissionStatus::Unknown;`
- L202 _private member_ `bool bStartSessionRequested;` — User called StartSession
- L203 _private member_ `bool bShouldSessionRestart;` — Start tracking on activity start
- L204 _private member_ `bool bARCoreInstallRequested;`
- L205 _private member_ `bool bARCoreInstalled;`
- L206 _private member_ `float WorldToMeterScale;`
- L207 _private member_ `TObjectPtr<class UARCoreAndroidPermissionHandler> PermissionHandler;`
- L208 _private member_ `FThreadSafeBool bDisplayOrientationChanged;`
- L210 _private member_ `FARSessionStatus CurrentSessionStatus;`
- L212 _private member_ `FGoogleARCoreCameraConfig SessionCameraConfig;`
- L214 _private member_ `TQueue<TFunction<void()>> RunOnGameThreadQueue;`
- L216 _private member_ `TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSystem;`
- L234 _private member_ `TSharedPtr<FInternalGCObject, ESPMode::ThreadSafe> GCObject;`

#### class `FGoogleARCoreDevice::FInternalGCObject`  
`class FInternalGCObject : FGCObject`  
_L220-231_
- inherits: `FGCObject`
- desc: FGoogleARCoreDevice itself cannot be a FGCObject since it's initialize too early. So we use an internal class instead, which can be created only when it's needed.
- L223 _public function_ `FInternalGCObject(FGoogleARCoreDevice* InARCoreDevice) : ARCoreDevice(InARCoreDevice)`
- L224 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L225 _public function_ `virtual FString GetReferencerName() const override`
- L230 _private member_ `FGoogleARCoreDevice* ARCoreDevice = nullptr;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreMotionController.h` (Private)


#### class `FGoogleARCoreMotionController`  
`class FGoogleARCoreMotionController : public IMotionController`  
_L11-88_
- inherits: `IMotionController`
- L14 _public prototype_ `FGoogleARCoreMotionController();`
- L16 _public prototype_ `void RegisterController();`
- L18 _public prototype_ `void UnregisterController();`
- L25 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const override;` — Returns the device type of the controller. @return	Device type of the controller.
- L38 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override;` — Returns the calibration-space orientation of the requested controller's hand. @param ControllerIndex	The Unreal controller (player) index of the controller set @param MotionSource		Which source, within the motion controller to get the orientation and position for @param OutOrientation	(out) If tracked, the orientation (in calibrated-space) of the controller in the specified hand @param OutPosition		(out) If tracked, the position (in calibrated-space) of the controller in the specified hand @param WorldToMetersScale The world scaling factor. @return					True if the device requested is valid and tracked, false otherwise
- L40 _public function_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override`
- L48 _public function_ `virtual bool GetControllerOrientationAndPositionForTime(const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& OutTimeWasUsed, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const override`
- L62 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override;` — Returns the tracking status (e.g. not tracked, intertial-only, fully tracked) of the specified controller @return	Tracking status of the specified controller, or ETrackingStatus::NotTracked if the device is not found
- L69 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const override;` — Called to request the motion sources that this IMotionController provides @param Sources	A motion source enumerator object that IMotionControllers can add source names to
- L80 _public function_ `virtual float GetCustomParameterValue(const FName MotionSource, FName ParameterName, bool& bOutValueFound) const override` — Returns a custom names parameter value @param MotionSource		The name of the motion source we want parameters for @param ParameterName		The specific value we are looking for @param bOutValueFound	(out) Whether the parameter could be found @return			The value of the parameter
- L82 _public function_ `virtual bool GetHandJointPosition(const FName MotionSource, int jointIndex, FVector& OutPosition) const`
- L85 _private member_ `static FName ARCoreMotionSourceId;`
- L87 _private member_ `FGoogleARCoreDevice* ARCoreDeviceInstance;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCorePermissionHandler.h` (Private)


#### class `UARCoreAndroidPermissionHandler`  
`class UARCoreAndroidPermissionHandler: public UObject`  
_L12-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public prototype_ `static bool CheckRuntimePermission(const FString& RuntimePermission);`
- L19 _public prototype_ `void RequestRuntimePermissions(const TArray<FString>& RuntimePermissions);`
- L22 _public prototype_ `void OnPermissionsGranted(const TArray<FString>& Permissions, const TArray<bool>& Granted);` — `UFUNCTION()`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreResources.h` (Private)


#### class `FGoogleARCoreTrackableResource`  
`class FGoogleARCoreTrackableResource : public IARRef`  
_L12-56_
- inherits: `IARRef`
- L16 _public function_ `virtual void AddRef() override` — IARRef interface
- L18 _public function_ `virtual void RemoveRef() override`
- L28 _public function_ `FGoogleARCoreTrackableResource(TSharedPtr<FGoogleARCoreSession> InSession, ArTrackable* InTrackableHandle, UARTrackedGeometry* InTrackedGeometry) : Session(InSession) , TrackableHandle(InTrackableHandle) , TrackedGeometry(InTrackedGeometry)`
- L36 _public function_ `virtual ~FGoogleARCoreTrackableResource()`
- L42 _public prototype_ `EARTrackingState GetTrackingState();`
- L44 _public prototype_ `virtual void UpdateGeometryData();`
- L46 _public function_ `TWeakPtr<FGoogleARCoreSession> GetSession()`
- L47 _public function_ `ArTrackable* GetNativeHandle()`
- L49 _public prototype_ `void ResetNativeHandle(ArTrackable* InTrackableHandle);`
- L52 _protected member_ `TWeakPtr<FGoogleARCoreSession> Session;`
- L53 _protected member_ `ArTrackable* TrackableHandle;`
- L54 _protected member_ `UARTrackedGeometry* TrackedGeometry;`

#### class `FGoogleARCoreTrackedPlaneResource`  
`class FGoogleARCoreTrackedPlaneResource : public FGoogleARCoreTrackableResource`  
_L58-72_
- inherits: `FGoogleARCoreTrackableResource`
- L62 _public function_ `FGoogleARCoreTrackedPlaneResource(TSharedPtr<FGoogleARCoreSession> InSession, ArTrackable* InTrackableHandle, UARTrackedGeometry* InTrackedGeometry) : FGoogleARCoreTrackableResource(InSession, InTrackableHandle, InTrackedGeometry)`
- L68 _public prototype_ `void UpdateGeometryData() override;`
- L70 _public function_ `ArPlane* GetPlaneHandle()`

#### class `FGoogleARCoreTrackedPointResource`  
`class FGoogleARCoreTrackedPointResource : public FGoogleARCoreTrackableResource`  
_L74-88_
- inherits: `FGoogleARCoreTrackableResource`
- L78 _public function_ `FGoogleARCoreTrackedPointResource(TSharedPtr<FGoogleARCoreSession> InSession, ArTrackable* InTrackableHandle, UARTrackedGeometry* InTrackedGeometry) : FGoogleARCoreTrackableResource(InSession, InTrackableHandle, InTrackedGeometry)`
- L84 _public prototype_ `void UpdateGeometryData() override;`
- L86 _public function_ `ArPoint* GetPointHandle()`

#### class `FGoogleARCoreAugmentedImageResource`  
`class FGoogleARCoreAugmentedImageResource : public FGoogleARCoreTrackableResource`  
_L90-104_
- inherits: `FGoogleARCoreTrackableResource`
- L94 _public function_ `FGoogleARCoreAugmentedImageResource(TSharedPtr<FGoogleARCoreSession> InSession, ArTrackable* InTrackableHandle, UARTrackedGeometry* InTrackedGeometry) : FGoogleARCoreTrackableResource(InSession, InTrackableHandle, InTrackedGeometry)`
- L100 _public prototype_ `void UpdateGeometryData() override;`
- L102 _public function_ `ArAugmentedImage* GetImageHandle()`

#### class `FGoogleARCoreAugmentedFaceResource`  
`class FGoogleARCoreAugmentedFaceResource : public FGoogleARCoreTrackableResource`  
_L106-120_
- inherits: `FGoogleARCoreTrackableResource`
- L110 _public function_ `FGoogleARCoreAugmentedFaceResource(TSharedPtr<FGoogleARCoreSession> InSession, ArTrackable* InTrackableHandle, UARTrackedGeometry* InTrackedGeometry) : FGoogleARCoreTrackableResource(InSession, InTrackableHandle, InTrackedGeometry)`
- L116 _public prototype_ `void UpdateGeometryData() override;`
- L118 _public function_ `ArAugmentedFace* GetFaceHandle()`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreTexture.h` (Private)


#### class `UARCoreCameraTexture`  
`class UARCoreCameraTexture : public UARTexture , public IYCbCrConversionQuery`  
_L17-38_
- reflection: `UCLASS()`
- inherits: `UARTexture,IYCbCrConversionQuery`
- L24 _public prototype_ `virtual FTextureResource* CreateResource() override;` — UTexture interface implementation
- L25 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L28 _public prototype_ `uint32 GetTextureId() const;`
- L31 _public prototype_ `void UpdateCameraImage(void* InVulkanHardwareBuffer);` — Recreates image resource using Vulkan's external Hardware Buffer.
- L34 _public prototype_ `FYCbCrConversion GetYCbCrConversion_RenderThread() const override;` — IYCbCrConversionQuery overrides
- L37 _private member_ `void* VukanHardwareBuffer = nullptr;`

#### class `UARCoreDepthTexture`  
`class UARCoreDepthTexture : public UARTexture`  
_L42-55_
- reflection: `UCLASS()`
- inherits: `UARTexture`
- L48 _public prototype_ `virtual FTextureResource* CreateResource() override;` — UTexture interface implementation
- L49 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L53 _public prototype_ `void UpdateDepthImage(const ArSession* SessionHandle, const ArImage* Image);`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreXRCamera.h` (Private)


#### class `FGoogleARCoreXRCamera`  
`class FGoogleARCoreXRCamera : public FDefaultXRCamera`  
_L12-40_
- inherits: `FDefaultXRCamera`
- L15 _public prototype_ `FGoogleARCoreXRCamera(const FAutoRegister&, FGoogleARCoreXRTrackingSystem& InARCoreSystem, int32 InDeviceID);`
- L18 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L19 _public prototype_ `virtual void SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData) override;`
- L20 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L21 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L22 _public prototype_ `virtual void PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures) override;`
- L23 _public prototype_ `virtual void PostRenderBasePassMobile_RenderThread(FRHICommandList& RHICmdList, FSceneView& InView) override;`
- L24 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L25 _public prototype_ `virtual bool GetPassthroughCameraUVs_RenderThread(TArray<FVector2D>& OutUVs) override;`
- L28 _public prototype_ `void ConfigXRCamera(bool bInMatchDeviceCameraFOV, bool bInEnablePassthroughCameraRendering);`
- L30 _public prototype_ `void UpdateCameraTextures(UTexture* NewCameraTexture, UTexture* DepthTexture, bool bEnableOcclusion);`
- L32 _public prototype_ `void UpdateCameraYCbCrConversion(IYCbCrConversionQuery* NewYCbCrConversionQuery);`
- L35 _private member_ `FGoogleARCoreXRTrackingSystem& GoogleARCoreTrackingSystem;`
- L36 _private member_ `FGoogleARCorePassthroughCameraRenderer* PassthroughRenderer;`
- L38 _private member_ `bool bMatchDeviceCameraFOV;`
- L39 _private member_ `bool bEnablePassthroughCameraRendering_RT;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/GoogleARCoreXRTrackingSystem.h` (Private)


#### class `FGoogleARCoreXRTrackingSystem`  
`class FGoogleARCoreXRTrackingSystem : public FARSystemSupportBase, public FXRTrackingSystemBase, public FGCObject, public TSharedFromThis<FGoogleARCoreXRTrackingSystem, ESPMode::ThreadSafe>`  
_L17-124_
- inherits: `FARSystemSupportBase,FXRTrackingSystemBase,FGCObject,TSharedFromThis<FGoogleARCoreXRTrackingSystem,ESPMode::ThreadSafe>`
- L22 _public prototype_ `static FGoogleARCoreXRTrackingSystem* GetInstance();`
- L24 _public prototype_ `FGoogleARCoreXRTrackingSystem();`
- L25 _public prototype_ `~FGoogleARCoreXRTrackingSystem();`
- L28 _public prototype_ `void ConfigARCoreXRCamera(bool bMatchCameraFOV, bool bEnablePassthroughRendering);` — FGoogleARCoreXRTrackingSystem Class Method
- L29 _public prototype_ `void EnableColorCameraRendering(bool bEnableColorCameraRnedering);`
- L30 _public prototype_ `bool GetColorCameraRenderingEnabled();`
- L33 _public prototype_ `virtual FName GetSystemName() const override;` — IXRTrackingSystem
- L34 _public prototype_ `virtual int32 GetXRSystemFlags() const override;`
- L35 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition) override;`
- L36 _public prototype_ `virtual FString GetVersionString() const override;`
- L37 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;`
- L38 _public prototype_ `virtual TSharedPtr<class IXRCamera, ESPMode::ThreadSafe> GetXRCamera(int32 DeviceId = HMDDeviceId) override;`
- L40 _public prototype_ `virtual bool IsHeadTrackingAllowed() const override;` — @todo : can I get rid of this? At least rename to IsCameraTracking / IsTrackingAllowed()
- L41 _public prototype_ `virtual bool OnStartGameFrame(FWorldContext& WorldContext) override;`
- L43 _public function_ `virtual void ResetOrientationAndPosition(float yaw = 0.f) override` — TODO: Figure out if we need to allow developer set/reset base orientation and position.
- L45 _public prototype_ `virtual float GetWorldToMetersScale() const override;` — @todo move this to some interface
- L47 _public prototype_ `void* GetARSessionRawPointer() override;`
- L48 _public prototype_ `void* GetGameThreadARFrameRawPointer() override;`
- L50 _public prototype_ `UGoogleARCoreEventManager* GetEventManager();`
- L52 _public prototype_ `bool AddRuntimeGrayscaleImage(UARSessionConfig* SessionConfig, const TArray<uint8>& ImageGrayscalePixels, int ImageWidth, int ImageHeight, FString FriendlyName, float PhysicalWidth);`
- L55 _public prototype_ `void OnTrackableAdded(UARTrackedGeometry* InTrackedGeometry);`
- L56 _public prototype_ `void OnTrackableUpdated(UARTrackedGeometry* InTrackedGeometry);`
- L57 _public prototype_ `void OnTrackableRemoved(UARTrackedGeometry* InTrackedGeometry);`
- L61 _protected prototype_ `virtual bool IsARAvailable() const override;` — IARSystemSupport
- L62 _protected prototype_ `virtual void OnARSystemInitialized() override;`
- L63 _protected prototype_ `virtual EARTrackingQuality OnGetTrackingQuality() const override;`
- L64 _protected prototype_ `virtual EARTrackingQualityReason OnGetTrackingQualityReason() const override;`
- L65 _protected prototype_ `virtual void OnStartARSession(UARSessionConfig* SessionConfig) override;`
- L66 _protected prototype_ `virtual void OnPauseARSession() override;`
- L67 _protected prototype_ `virtual void OnStopARSession() override;`
- L68 _protected prototype_ `virtual FARSessionStatus OnGetARSessionStatus() const override;`
- L69 _protected prototype_ `virtual void OnSetAlignmentTransform(const FTransform& InAlignmentTransform) override;`
- L70 _protected prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects(const FVector2D ScreenCoord, EARLineTraceChannels TraceChannels) override;`
- L71 _protected prototype_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects(const FVector Start, const FVector End, EARLineTraceChannels TraceChannels) override;`
- L72 _protected prototype_ `virtual TArray<UARTrackedGeometry*> OnGetAllTrackedGeometries() const override;`
- L73 _protected prototype_ `virtual TArray<UARPin*> OnGetAllPins() const override;`
- L74 _protected prototype_ `virtual bool OnIsTrackingTypeSupported(EARSessionType SessionType) const override;`
- L75 _protected prototype_ `virtual UARLightEstimate* OnGetCurrentLightEstimate() const override;`
- L77 _protected prototype_ `virtual UARPin* FindARPinByComponent(const USceneComponent* Component) const override;`
- L78 _protected prototype_ `virtual UARPin* OnPinComponent(USceneComponent* ComponentToPin, const FTransform& PinToWorldTransform, UARTrackedGeometry* TrackedGeometry = nullptr, const FName DebugName = NAME_None) override;`
- L79 _protected prototype_ `virtual void OnRemovePin(UARPin* PinToRemove) override;`
- L80 _protected prototype_ `virtual bool OnTryGetOrCreatePinForNativeResource(void* InNativeResource, const FString& InPinName, UARPin*& OutPin) override;`
- L82 _protected function_ `virtual bool OnAddManualEnvironmentCaptureProbe(FVector Location, FVector Extent) override`
- L83 _protected function_ `virtual TSharedPtr<FARGetCandidateObjectAsyncTask, ESPMode::ThreadSafe> OnGetCandidateObject(FVector Location, FVector Extent) const override`
- L84 _protected function_ `virtual TSharedPtr<FARSaveWorldAsyncTask, ESPMode::ThreadSafe> OnSaveWorld() const override`
- L86 _protected function_ `virtual EARWorldMappingState OnGetWorldMappingStatus() const override` — @todo -- support these properly
- L87 _protected prototype_ `virtual TArray<FARVideoFormat> OnGetSupportedVideoFormats(EARSessionType SessionType) const override;`
- L88 _protected prototype_ `virtual TArray<FVector> OnGetPointCloud() const override;`
- L89 _protected prototype_ `virtual UARTexture* OnGetARTexture(EARTextureType TextureType) const override;`
- L90 _protected prototype_ `bool OnGetCameraIntrinsics(FARCameraIntrinsics& OutCameraIntrinsics) const override;`
- L91 _protected prototype_ `bool OnIsSessionTrackingFeatureSupported(EARSessionType SessionType, EARSessionTrackingFeature SessionTrackingFeature) const override;`
- L94 _protected prototype_ `virtual bool OnAddRuntimeCandidateImage(UARSessionConfig* SessionConfig, UTexture2D* CandidateTexture, FString FriendlyName, float PhysicalWidth) override;`
- L96 _protected prototype_ `FGoogleARCoreXRCamera* GetARCoreCamera();`
- L100 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L101 _private function_ `virtual FString GetReferencerName() const override`
- L108 _private member_ `FGoogleARCoreDevice* ARCoreDeviceInstance;`
- L110 _private member_ `bool bMatchDeviceCameraFOV;`
- L111 _private member_ `bool bEnablePassthroughCameraRendering;`
- L112 _private member_ `bool bHasValidPose;`
- L113 _private member_ `bool bWantsDepthOcclusion = false;`
- L115 _private member_ `FVector CachedPosition;`
- L116 _private member_ `FQuat CachedOrientation;`
- L117 _private member_ `FRotator DeltaControlRotation;` — same as DeltaControlOrientation but as rotator
- L118 _private member_ `FQuat DeltaControlOrientation;` — same as DeltaControlRotation but as quat
- L120 _private member_ `TSharedPtr<class ISceneViewExtension, ESPMode::ThreadSafe> ViewExtension;`
- L122 _private member_ `TObjectPtr<UARBasicLightEstimate> LightEstimate;`
- L123 _private member_ `TObjectPtr<UGoogleARCoreEventManager> EventManager;`

#### Free symbols / members of external scopes

- L126 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogGoogleARCoreTrackingSystem, Log, All);`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Private/Ndk/NdkImageAPI.h` (Private)


#### struct `NdkImageAPI`  
`struct NdkImageAPI`  
_L18-26_
- L20 _public member_ `AImage_getWidth_ptr AImage_getWidth = nullptr;`
- L21 _public member_ `AImage_getHeight_ptr AImage_getHeight = nullptr;`
- L22 _public member_ `AImage_getNumberOfPlanes_ptr AImage_getNumberOfPlanes = nullptr;`
- L23 _public member_ `AImage_getPlanePixelStride_ptr AImage_getPlanePixelStride = nullptr;`
- L24 _public member_ `AImage_getPlaneRowStride_ptr AImage_getPlaneRowStride = nullptr;`
- L25 _public member_ `AImage_getPlaneData_ptr AImage_getPlaneData = nullptr;`

#### Free symbols / members of external scopes

- L8 _typedef_ `typedef struct AImage AImage;`
- L11 _typedef_ `typedef int32_t(*AImage_getWidth_ptr)(const AImage* image, int32_t* width);` — Function ptr;
- L12 _typedef_ `typedef int32_t(*AImage_getHeight_ptr)(const AImage* image, int32_t* height);`
- L13 _typedef_ `typedef int32_t(*AImage_getNumberOfPlanes_ptr)(const AImage* image, int32_t* numPlanes);`
- L14 _typedef_ `typedef int32_t(*AImage_getPlanePixelStride_ptr)(const AImage* image, int planeIdx, int32_t* pixelStride);`
- L15 _typedef_ `typedef int32_t(*AImage_getPlaneRowStride_ptr)(const AImage* image, int planeIdx, int32_t* rowStride);`
- L16 _typedef_ `typedef int32_t(*AImage_getPlaneData_ptr)(const AImage* image, int planeIdx, uint8_t** data, int* dataLength);`
- L28 _prototype_ `NdkImageAPI* GetNdkImageAPI();`
- L30 _macro_ `#define AImage_getWidth_dynamic GetNdkImageAPI()->AImage_getWidth`
- L31 _macro_ `#define AImage_getHeight_dynamic GetNdkImageAPI()->AImage_getHeight`
- L32 _macro_ `#define AImage_getNumberOfPlanes_dynamic GetNdkImageAPI()->AImage_getNumberOfPlanes`
- L33 _macro_ `#define AImage_getPlanePixelStride_dynamic GetNdkImageAPI()->AImage_getPlanePixelStride`
- L34 _macro_ `#define AImage_getPlaneRowStride_dynamic GetNdkImageAPI()->AImage_getPlaneRowStride`
- L35 _macro_ `#define AImage_getPlaneData_dynamic GetNdkImageAPI()->AImage_getPlaneData`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreAugmentedFace.h` (Public)


#### enum `EGoogleARCoreAugmentedFaceRegion`  
`enum class EGoogleARCoreAugmentedFaceRegion : uint8`  
_L17-25_
- reflection: `UENUM(BlueprintType)`
- desc: @ingroup GoogleARCoreBase Describes the face regions for which the pose can be queried. Left and right are defined relative to the actor (the person that the mesh belongs to).
- L20 _public enumerator_ `NoseTip = 0` — A region around the nose of the AugmentedFace.
- L22 _public enumerator_ `ForeheadLeft = 1` — A region around the left forehead of the AugmentedFace.
- L24 _public enumerator_ `ForeheadRight = 2` — A region around the right forehead of the AugmentedFace.

#### class `UGoogleARCoreAugmentedFace`  
`class UGoogleARCoreAugmentedFace : public UARFaceGeometry`  
_L31-59_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UARFaceGeometry`
- desc: An UObject representing a face detected by ARCore.
- L41 _public prototype_ `virtual void DebugDraw(UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;` — Draws the face mesh wireframe using debug lines.
- L47 _public prototype_ `FTransform GetLocalToWorldTransformOfRegion(EGoogleARCoreAugmentedFaceRegion Region);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|AugmentedImage")` — Returns the latest known local-to-world transform of the given face region.
- L53 _public prototype_ `FTransform GetLocalToTrackingTransformOfRegion(EGoogleARCoreAugmentedFaceRegion Region);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|AugmentedImage")` — Returns the latest known local-to-tracking transform of the given face region.
- L56 _private prototype_ `void UpdateRegionTransforms(TMap<EGoogleARCoreAugmentedFaceRegion, FTransform>& InRegionLocalToTrackingTransforms);`
- L58 _private member_ `TMap<EGoogleARCoreAugmentedFaceRegion, FTransform> RegionLocalToTrackingTransforms;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreAugmentedImage.h` (Public)


#### class `UGoogleARCoreAugmentedImage`  
`class UGoogleARCoreAugmentedImage : public UARTrackedImage`  
_L15-64_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UARTrackedImage`
- desc: An object representing an augmented image currently in the scene.
- L29 _public prototype_ `virtual void DebugDraw( UWorld* World, const FLinearColor& OutlineColor, float OutlineThickness, float PersistForSeconds = 0.0f) const override;` — Draw a box around the image, for debugging purposes. @param World				World context object. @param OutlineColor		Color of the lines. @param OutlineThickness	Thickness of the lines. @param PersistForSeconds	Number of seconds to keep the lines on-screen.
- L50 _public prototype_ `void UpdateTrackedGeometry( const TSharedRef<FARSupportInterface, ESPMode::ThreadSafe>& InTrackingSystem, uint32 FrameNumber, double Timestamp, const FTransform& InLocalToTrackingTransform, const FTransform& InAlignmentTransform, FVector2D InEstimatedSize, UARCandidateImage* InDetectedImage, int32 InImageIndex, const FString& ImageName);` — Update the tracked object. This is called by FGoogleARCoreAugmentedImageResource::UpdateGeometryData() to adjust the tracked position of the object. @param InTrackingSystem				The AR system to use. @param FrameNumber					The current frame number. @param Timestamp						The current time stamp. @param InLocalToTrackingTransform	Local to tracking space transformation. @param InAlignmentTransform			Alignment transform. @param InEstimatedSize				The estimated size of the object. @param InDetectedImage				The image that was found, in Unreal's cross-platform augmente reality API. @param InImageIndex					Which image in the augmented image database is being tracked. @param ImageName						The name of the image being tracked.
- L59 _private member_ `int32 ImageIndex;` — `UPROPERTY()`
- L62 _private member_ `FString ImageName;` — `UPROPERTY()`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreAugmentedImageDatabase.h` (Public)


#### struct `FGoogleARCoreAugmentedImageDatabaseEntry`  
`struct FGoogleARCoreAugmentedImageDatabaseEntry`  
_L21-49_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single entry in a UGoogleARCoreAugmentedImageDatabase. Deprecated. Please use the cross-platform UARCandidateImage instead.
- L30 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoogleARCore|AugmentedImages")` — Name of the image. This can be retrieved from an active UGoogleARCoreAugmentedImage with the GetImageName function.
- L37 _public member_ `TObjectPtr<UTexture2D> ImageAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoogleARCore|AugmentedImages")` — Texture to use for this image. Valid formats are RGBA8 and BGRA8.
- L43 _public member_ `float Width;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoogleARCore|AugmentedImages")` — Width of the image in meters.
- L45 _public function_ `FGoogleARCoreAugmentedImageDatabaseEntry() : ImageAsset(nullptr) , Width(0.0f)`

#### class `UGoogleARCoreAugmentedImageDatabase`  
`class UGoogleARCoreAugmentedImageDatabase : public UDataAsset`  
_L58-88_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- L68 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Overridden serialization function.
- L75 _public member_ `TArray<FGoogleARCoreAugmentedImageDatabaseEntry> Entries;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GoogleARCore|AugmentedImages")` — The individual instances of FGoogleARCoreAugmentedImageDatabaseEntry objects.
- L82 _public member_ `TArray<uint8> SerializedDatabase;` — `UPROPERTY()` — The serialized database, in the ARCore augmented image database serialization format.
- L86 _private member_ `ArAugmentedImageDatabase* NativeHandle = nullptr;`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef struct ArAugmentedImageDatabase_ ArAugmentedImageDatabase;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreBaseModule.h` (Public)


#### class `IGoogleARCoreBaseModule`  
`class IGoogleARCoreBaseModule : public IHeadMountedDisplayModule`  
_L12-38_
- inherits: `IHeadMountedDisplayModule`
- desc: The public interface to this module.
- L23 _public function_ `static inline IGoogleARCoreBaseModule& Get()` — Singleton-like access to this module's interface.  Provided for convenience only. Beware of calling this method during the shutdown phase because your module might already have been unloaded. @return Returns singleton instance, loading the module on demand if needed.
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use.

#### Free symbols / members of external scopes

- L40 _delegate_ `DECLARE_STATS_GROUP(TEXT("ARCore"), STATGROUP_ARCore, STATCAT_Adva`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreCameraImage.h` (Public)


#### class `UGoogleARCoreCameraImage`  
`class UGoogleARCoreCameraImage : public UObject`  
_L14-65_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UObject`
- desc: An object that represents an acquired CPU-accessible camera image.
- L19 _public prototype_ `~UGoogleARCoreCameraImage();`
- L25 _public prototype_ `void Release();` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCore|CameraImage", meta = (Keywords = "googlear arcore cameraimage"))` — Explicitly release the ARCore resources owned by this object.
- L33 _public prototype_ `int32 GetWidth() const;` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCore|CameraImage", meta = (Keywords = "googlear arcore cameraimage"))` — Get the width of the image in pixels. @return The width.
- L41 _public prototype_ `int32 GetHeight() const;` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCore|CameraImage", meta = (Keywords = "googlear arcore cameraimage"))` — Get the height of the image in pixels. @return The height.
- L49 _public prototype_ `int32 GetPlaneCount() const;` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCore|CameraImage", meta = (Keywords = "googlear arcore cameraimage"))` — Get the number of data planes in the image. @return The plane count.
- L54 _public prototype_ `const uint8 *GetPlaneData( int32 Plane, int32 &PixelStride, int32 &RowStride, int32 &DataLength) const;` — Get the raw image data of a given plane.
- L60 _private member_ `ArImage *ArImage = nullptr;`
- L61 _private member_ `const ArSession* SessionHandle = nullptr;`

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef struct ArImage_ ArImage;`
- L8 _typedef_ `typedef struct ArSession_ ArSession;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreCameraIntrinsics.h` (Public)


#### class `UGoogleARCoreCameraIntrinsics`  
`class UGoogleARCoreCameraIntrinsics : public UObject`  
_L21-57_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: An object wrapping the ArCameraIntrinsics data from the ARCore SDK.
- L33 _public prototype_ `void GetFocalLength(float &OutFX, float &OutFY);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|CameraIntrinsics")` — Get the focal length in pixels. @param OutFX  The focal length on the X axis. @param OutFY  The focal length on the Y axis.
- L42 _public prototype_ `void GetPrincipalPoint(float &OutCX, float &OutCY);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|CameraIntrinsics")` — Get the principal point in pixels. @param OutCX  The principle point on the X axis. @param OutCY  The principle point the Y axis.
- L51 _public prototype_ `void GetImageDimensions(int32 &OutWidth, int32 &OutHeight);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|CameraIntrinsics")` — Get the image's width and height in pixels. @param OutWidth   The width. @param OutHeight  The height.
- L53 _public prototype_ `void SetCameraIntrinsics(const FARCameraIntrinsics& InCameraIntrinsics);`
- L56 _private member_ `FARCameraIntrinsics CameraIntrinsics;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef struct ArCameraIntrinsics_ ArCameraIntrinsics;`

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreFunctionLibrary.h` (Public)


#### class `UGoogleARCoreSessionFunctionLibrary`  
`class UGoogleARCoreSessionFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-33_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: A function library that provides static/Blueprint functions associated with GoogleARCore session.
- L31 _public prototype_ `static UARCandidateImage* AddRuntimeCandidateImageFromRawbytes(UARSessionConfig* SessionConfig, const TArray<uint8>& ImageGrayscalePixels, int ImageWidth, int ImageHeight, FString FriendlyName, float PhysicalWidth, UTexture2D* CandidateTexture = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "AR AugmentedReality|Session", meta = (Keywords = "ar augmentedreality augmented reality candidate image"))` — Create an ARCandidateImage object from the raw pixel data and add it to the ARCandidateImageList of the given \c UARSessionConfig object. Note that you need to restart the AR session with the \c UARSessionConfig you are adding to to make the change take effect. On ARCore platform, you can leave the PhysicalWidth and PhysicalHeight to 0 if you don't know the physical size of the image or the physical size is dynamic. And this function takes time to perform non-trivial image processing (20ms - 30ms), and should be run on a background thread. @return A \c UARCandidateImage Object pointer if the underlying ARPlatform added the candidate image at runtime successfully. Return nullptr otherwise.

#### class `UGoogleARCoreFrameFunctionLibrary`  
`class UGoogleARCoreFrameFunctionLibrary : public UBlueprintFunctionLibrary`  
_L37-54_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: A function library that provides static/Blueprint functions associated with most recent GoogleARCore tracking frame.
- L52 _public function_ `static EGoogleARCoreFunctionStatus GetCameraMetadata(const ACameraMetadata*& OutCameraMetadata)` — `UE_DEPRECATED(5.3, "GetCameraMetadata is deprecated and non-functional. It does not have an exact replacement. ArImageMetadata seems to be the closest thing, but we do not currently expose it.")` — Gets the camera metadata for the latest camera image. Note that ACameraMetadata is a Ndk type. Include the Ndk header <camera/NdkCameraMetadata.h> to use query value from ACameraMetadata. @param OutCameraMetadata		A pointer to a ACameraMetadata struct which is only valid in one frame. @return An EGoogleARCoreFunctionStatus. Possible value: Success, SessionPaused, NotAvailable.

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreSessionConfig.h` (Public)


#### class `UGoogleARCoreSessionConfig`  
`class UGoogleARCoreSessionConfig : public UARSessionConfig`  
_L18-86_
- reflection: `UCLASS(BlueprintType, Category = "AR AugmentedReality")`
- inherits: `UARSessionConfig`
- desc: A UDataAsset that can be used to configure ARCore specific settings on top of UARSessionConfig.
- L30 _public function_ `UGoogleARCoreAugmentedImageDatabase* GetAugmentedImageDatabase()` — `UFUNCTION(BlueprintPure, Category = "google arcore augmentedimages")` — Get the augmented image database being used.
- L39 _public function_ `void SetAugmentedImageDatabase(UGoogleARCoreAugmentedImageDatabase* NewImageDatabase)` — `UFUNCTION(BlueprintCallable, Category = "google arcore augmentedimages")` — Set the augmented image database to use.
- L49 _public member_ `TObjectPtr<UGoogleARCoreAugmentedImageDatabase> AugmentedImageDatabase;` — `UPROPERTY(EditAnywhere, Category = "google arcore augmentedimages")` — A UGoogleARCoreAugmentedImageDatabase asset to use use for image tracking.
- L53 _public member_ `EGoogleARCoreCameraFacing CameraFacing = EGoogleARCoreCameraFacing::Back;` — `UPROPERTY(EditAnywhere, Category = "ARCore Settings")` — Configure which camera will be used to in the AR session.
- L57 _public member_ `EGoogleARCoreAugmentedFaceMode AugmentedFaceMode = EGoogleARCoreAugmentedFaceMode::Disabled;` — `UPROPERTY(EditAnywhere, Category = "ARCore Settings")` — Configure which Augmented Face mode will be used in the AR session.
- L72 _public function_ `static UGoogleARCoreSessionConfig* CreateARCoreSessionConfig(bool bHorizontalPlaneDetection, bool bVerticalPlaneDetection, EARLightEstimationMode InLightEstimationMode, EARFrameSyncMode InFrameSyncMode, bool bInEnableAutoFocus, bool bInEnableAutomaticCameraOverlay, bool bInEnableAutomaticCameraTracking)` — Create a new ARCore session configuration. @param bHorizontalPlaneDetection			True to enable horizontal plane detection. @param bVerticalPlaneDetection			True to enable vertical plane detection. @param InLightEstimationMode				The light estimation mode to use. @param InFrameSyncMode					The frame synchronization mode to use. @param bInEnableAutoFocus				True to enable auto-focus. @param bInEnableAutomaticCameraOverlay	True to enable the camera overlay. @param bInEnableAutomaticCameraTracking	True to enable automatic camera tracking. @return The new configuration object.

### `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreTypes.h` (Public)


#### enum `EGoogleARCoreAvailability`  
`enum class EGoogleARCoreAvailability : uint8`  
_L29-51_
- L32 _public enumerator_ `UnknownError = 0` — An internal error occurred while determining ARCore availability.
- L34 _public enumerator_ `UnknownChecking = 1` — ARCore is not installed, and a query has been issued to check if ARCore is is supported.
- L39 _public enumerator_ `UnknownTimedOut = 2` — ARCore is not installed, and the query to check if ARCore is supported timed out. This may be due to the device being offline.
- L41 _public enumerator_ `UnsupportedDeviceNotCapable = 100` — ARCore is not supported on this device.
- L43 _public enumerator_ `SupportedNotInstalled = 201` — The device and Android version are supported, but the ARCore APK is not installed.
- L48 _public enumerator_ `SupportedApkTooOld = 202` — The device and Android version are supported, and a version of the ARCore APK is installed, but that ARCore APK version is too old.
- L50 _public enumerator_ `SupportedInstalled = 203` — ARCore is supported, installed, and available to use.

#### enum `EGoogleARCoreInstallStatus`  
`enum class EGoogleARCoreInstallStatus : uint8`  
_L53-59_
- L56 _public enumerator_ `Installed = 0` — The requested resource is already installed.
- L58 _public enumerator_ `Requrested = 1` — Installation of the resource was requested. The current activity will be paused.

#### enum `EGoogleARCoreFunctionStatus`  
`enum class EGoogleARCoreFunctionStatus : uint8`  
_L66-86_
- reflection: `UENUM(BlueprintType)`
- desc: @ingroup GoogleARCoreBase Describes the status of most ARCore functions.
- L69 _public enumerator_ `Success` — Function returned successfully.
- L71 _public enumerator_ `Fatal` — Function failed due to Fatal error.
- L73 _public enumerator_ `SessionPaused` — Function failed due to the session isn't running.
- L75 _public enumerator_ `NotTracking` — Function failed due to ARCore session isn't in tracking state.
- L77 _public enumerator_ `ResourceExhausted` — Function failed due to the requested resource is exhausted.
- L79 _public enumerator_ `NotAvailable` — Function failed due to ARCore session hasn't started or the requested resource isn't available yet.
- L81 _public enumerator_ `InvalidType` — Function failed due to the function augment has invalid type.
- L83 _public enumerator_ `IllegalState` — Function failed due to it is invoked at an illegal or inappropriate time.
- L85 _public enumerator_ `Unknown` — Function failed with unknown reason.

#### enum `EGoogleARCoreTrackingState`  
`enum class EGoogleARCoreTrackingState : uint8`  
_L92-100_
- desc: @ingroup GoogleARCoreBase Describes the tracking state of the current ARCore session.
- L95 _public enumerator_ `Tracking = 0` — Tracking is valid.
- L97 _public enumerator_ `NotTracking = 1` — Tracking is temporary lost but could recover in the future.
- L99 _public enumerator_ `StoppedTracking = 2` — Tracking is lost will not recover.

#### enum `EGoogleARCoreCoordinates2DType`  
`enum class EGoogleARCoreCoordinates2DType : uint8`  
_L106-114_
- desc: @ingroup GoogleARCoreBase 2d coordinate systems referenced by ARCore.
- L109 _public enumerator_ `Texture = 0` — ARCore normalized pass-through camera texture(for GPU usage) space with top-left (0.0f, 0.0f) and bottom-right(1.0f, 1.0f).
- L111 _public enumerator_ `Image = 1` — ARCore normalized pass-through camera image(for CPU usage) space with top-left (0.0f, 0.0f) and bottom-right(1.0f, 1.0f).
- L113 _public enumerator_ `Viewport = 2` — UE normalized viewport space with top-left(0,0f ,0.0f) and bottom-right(1.0f, 1.0f)

#### struct `FGoogleARCoreLightEstimate`  
`struct FGoogleARCoreLightEstimate`  
_L120-132_
- desc: A struct describes the ARCore light estimation.
- L123 _public member_ `bool bIsValid = false;` — Whether this light estimation is valid.
- L126 _public member_ `float PixelIntensity = 0.0f;` — The average pixel intensity of the passthrough camera image.
- L131 _public member_ `FVector RGBScaleFactor = FVector(0.0f);` — The RGB scale to match the color of the light in the real environment.

#### enum `EGoogleARCoreLineTraceChannel`  
`enum class EGoogleARCoreLineTraceChannel : uint8`  
_L139-157_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCore|TraceChannel", meta = (Bitflags))`
- desc: @ingroup GoogleARCoreBase Describes which channel ARLineTrace will be performed on.
- L141 _public enumerator_ `None = 0`
- L143 _public enumerator_ `FeaturePoint = 1` — Trace against feature point cloud.
- L145 _public enumerator_ `InfinitePlane = 2` — Trace against the infinite plane.
- L147 _public enumerator_ `PlaneUsingExtent = 4` — Trace against the plane using its extent.
- L149 _public enumerator_ `PlaneUsingBoundaryPolygon = 8` — Trace against the plane using its boundary polygon.
- L154 _public enumerator_ `FeaturePointWithSurfaceNormal = 16` — Trace against feature point and attempt to estimate the normal of the surface centered around the trace hit point. Surface normal estimation is most likely to succeed on textured surfaces and with camera motion.
- L156 _public enumerator_ `AugmentedImage = 32` — Trace against augmented images.

#### enum `EGoogleARCoreCameraFacing`  
`enum class EGoogleARCoreCameraFacing : uint8`  
_L165-172_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCore|CameraConfig")`
- desc: @ingroup GoogleARCoreBase Describes the orientation of the selected camera relative to the device display.
- L167 _public enumerator_ `None = 0 UMETA(Hidden)`
- L169 _public enumerator_ `Back = 1` — Camera facing away from user.
- L171 _public enumerator_ `Front = 2` — Camera facing towards user.

#### enum `EGoogleARCoreAugmentedFaceMode`  
`enum class EGoogleARCoreAugmentedFaceMode : uint8`  
_L179-185_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCore|AugmentedFace")`
- desc: @ingroup GoogleARCoreBase Describes the possible modes for Augmented Face detection.
- L182 _public enumerator_ `Disabled = 0` — A mode where AugmentedFace detection is disabled.
- L184 _public enumerator_ `PoseAndMesh = 2` — A mode where AugmentedFace detection performs face pose, region pose and face mesh estimation.

#### enum `EGoogleARCoreTrackingFailureReason`  
`enum class EGoogleARCoreTrackingFailureReason : uint8`  
_L192-210_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCore|AugmentedFace")`
- desc: @ingroup GoogleARCoreBase Describes the possible tracking failure reasons in ARCore.
- L195 _public enumerator_ `None = 0` — Tracking is working normally, or ARCore session is not currently running.
- L200 _public enumerator_ `BadState = 1` — Tracking lost due to bad internal state. Please try restarting the AR experience. This should be seen rarely, and should be reported to and fixed by ARCore team.
- L202 _public enumerator_ `InsufficientLight = 2` — Tracking lost due to poor lighting conditions. Please move to a more brightly lit area
- L204 _public enumerator_ `ExcessiveMotion = 3` — Tracking lost due to excessive motion. Please  move device more slowly.
- L209 _public enumerator_ `InsufficientFeatures = 4` — Tracking lost due to insufficient trackable features. Please move to area with more features, such as corners, objects, surfaces with texture. Avoid blank walls and surfaces without detail.

#### enum `EGoogleARCoreCameraFPS`  
`enum class EGoogleARCoreCameraFPS : uint8`  
_L217-227_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCore|CameraConfig")`
- desc: @ingroup GoogleARCoreBase Describes the target FPS of the ARCore camera.
- L220 _public enumerator_ `FPS_Any = 0` — Targeting any FPS.
- L223 _public enumerator_ `FPS_30 = 1 << 0` — Targeting 30 FPS.
- L226 _public enumerator_ `FPS_60 = 1 << 1` — Targeting 60 FPS.

#### enum `EGoogleARCoreCameraDepthSensorUsage`  
`enum class EGoogleARCoreCameraDepthSensorUsage : uint8`  
_L234-244_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCore|CameraConfig")`
- desc: @ingroup GoogleARCoreBase Describes the usage of the depth sensor of the ARCore camera.
- L237 _public enumerator_ `DepthSensor_Any = 0` — Do not specify the depth sensor usage.
- L240 _public enumerator_ `DepthSensor_RequireAndUse = 1 << 0` — Require and use the depth sensor.
- L243 _public enumerator_ `DepthSensor_DoNotUse = 1 << 1` — Do not use the depth sensor.

#### struct `FGoogleARCoreCameraConfig`  
`struct FGoogleARCoreCameraConfig`  
_L250-287_
- reflection: `USTRUCT(BlueprintType)`
- desc: Camera configuration from ARCore.
- L258 _public member_ `FIntPoint CameraImageResolution = FIntPoint::ZeroValue;` — `UPROPERTY(BlueprintReadOnly, Category = "GoogleARCore|CameraConfig")` — CPU-accessible camera image resolution.
- L265 _public member_ `FIntPoint CameraTextureResolution = FIntPoint::ZeroValue;` — `UPROPERTY(BlueprintReadOnly, Category = "GoogleARCore|CameraConfig")` — Texture resolution for the camera image accessible to the graphics API and shaders.
- L269 _public member_ `FString CameraID;` — `UPROPERTY(BlueprintReadOnly, Category = "GoogleARCore|CameraConfig")` — The id of the camera will be used in this CameraConfig.
- L273 _public member_ `int32 TargetFPS = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "GoogleARCore|CameraConfig", meta = (Bitmask, BitmaskEnum = "/Script/GoogleARCoreBase.EGoogleARCoreCameraFPS"))` — The target FPS of the camera.
- L277 _public member_ `int32 DepthSensorUsage = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "GoogleARCore|CameraConfig", meta = (Bitmask, BitmaskEnum = "/Script/GoogleARCoreBase.EGoogleARCoreCameraDepthSensorUsage"))` — The desired depth sensor usage of the camera.
- L279 _public member_ `EGoogleARCoreCameraFacing CameraFacing = EGoogleARCoreCameraFacing::Back;`
- L282 _public prototype_ `FGoogleARCoreCameraConfig();` — Below are for internal use only
- L283 _public prototype_ `bool IsCompatibleWith(const FGoogleARCoreCameraConfig& OtherConfig) const;`
- L284 _public prototype_ `int32 GetMaxFPS() const;`
- L285 _public prototype_ `void SetMaxFPS(int32 MaxFPS);`
- L286 _public prototype_ `FString ToLogString() const;`

#### class `FGoogleARCoreDelegates`  
`class FGoogleARCoreDelegates`  
_L292-308_
- desc: Delegate to call on camera configuration.
- L296 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGoogleARCoreOnConfigCameraDelegate, const TArray<FGoogleARCoreCameraConfig>&);` — @cond EXCLUDE_FROM_DOXYGEN
- L307 _public member_ `static FGoogleARCoreOnConfigCameraDelegate OnCameraConfig;` — A delegate can be bound through C++. It will be called before ARSession started and returns a list of supported ARCore camera configurations. Bind this delegate if you want to choose a specific camera config in your app. Call UGoogleARCoreSessionFunctionLibrary::ConfigARCoreCamera after the delegate is triggered.

#### class `UGoogleARCoreEventManager`  
`class UGoogleARCoreEventManager : public UObject`  
_L314-363_
- reflection: `UCLASS(BlueprintType, Category = "AR AugmentedReality")`
- inherits: `UObject`
- desc: Manager for ARCore delegates.
- L319 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGoogleARCoreOnConfigCameraDynamicDelegate, const TArray<FGoogleARCoreCameraConfig>&, SupportedCameraConfig);` — @cond EXCLUDE_FROM_DOXYGEN
- L322 _public function_ `UGoogleARCoreEventManager()`
- L327 _public function_ `~UGoogleARCoreEventManager()`
- L347 _public member_ `FGoogleARCoreOnConfigCameraDynamicDelegate OnConfigCamera;` — `UPROPERTY(BlueprintAssignable)` — A dynamic delegate can be assigned through blueprint. Will be called before ARSession started and returns an array of supported ARCore camera config. The array will always return 3 camera configs. The GPU texture resolutions are the same in all three configs. Currently, most devices provide GPU texture resolution of 1920 x 1080, but devices might provide higher or lower resolution textures, depending on device capabilities. The CPU image resolutions returned are VGA, 720p, and a resolution matching the GPU texture. Bind this delegate if you want to choose a specific camera config in your app. Call UGoogleARCoreSessionFunctionLibrary::ConfigARCoreCamera after the delegate is triggered.
- L350 _private function_ `void RegisterDelegates()`
- L354 _private function_ `void UnregisterDelegates()`
- L359 _private function_ `void OnConfigCamera_Handler(const TArray<FGoogleARCoreCameraConfig>& SupportedCameraConfig)`

#### class `UGoogleARCorePointCloud`  
`class UGoogleARCorePointCloud : public UObject`  
_L370-419_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: A UObject that contains a set of observed 3D points and confidence values.
- L378 _public prototype_ `~UGoogleARCorePointCloud();` — Destructor
- L381 _public prototype_ `int64 GetUpdateTimestamp();` — Returns the timestamp in nanosecond when this point cloud was observed.
- L385 _public prototype_ `bool IsUpdated();` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|PointCloud")` — Checks if this point cloud has been updated in this frame.
- L389 _public prototype_ `int GetPointNum();` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|PointCloud")` — Returns the number of point inside this point cloud.
- L393 _public prototype_ `void GetPoint(int Index, FVector& OutWorldPosition, float& OutConfidence);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|PointCloud")` — Returns the point position in Unreal world space and it's confidence value from 0 ~ 1.
- L403 _public prototype_ `int GetPointId(int Index);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|PointCloud")` — Returns the point Id of the point at the given index. Each point has a unique identifier (within a session) that is persistent across frames. That is, if a point from point cloud 1 has the same id as the point from point cloud 2, then it represents the same point in space.
- L407 _public prototype_ `void GetPointInTrackingSpace(int Index, FVector& OutTrackingSpaceLocation, float& OutConfidence);` — `UFUNCTION(BlueprintPure, Category = "GoogleARCore|PointCloud")` — Returns the point position in Unreal AR Tracking space.
- L411 _public prototype_ `void ReleasePointCloud();` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCore|PointCloud")` — Release PointCloud's resources back to ArCore. Data will not be available after releasePointCloud is called.
- L414 _private member_ `TWeakPtr<FGoogleARCoreSession> Session;`
- L415 _private member_ `bool bIsUpdated = false;`
- L417 _private member_ `ArPointCloud* PointCloudHandle;`

#### class `UGoogleARCoreEditorSettings`  
`class UGoogleARCoreEditorSettings : public UObject`  
_L425-433_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: Helper class used to expose FGoogleARCoreSessionConfig setting in the Editor plugin settings.
- L432 _public member_ `bool bARCoreRequiredApp = true;` — `UPROPERTY(EditAnywhere, config, Category = "ARCore Plugin Settings", meta = (ShowOnlyInnerProperties))` — Check this option if you app require ARCore to run on Android.

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef struct ACameraMetadata ACameraMetadata;` — Include <Camera/NdkCameraMetadata.h> to use this type.
- L22 _typedef_ `typedef struct ArTrackable_ ArTrackable;` — Forward decalare type defined in arcore_c_api.h
- L23 _typedef_ `typedef struct ArPlane_ ArPlane;`
- L24 _typedef_ `typedef struct ArPoint_ ArPoint;`
- L25 _typedef_ `typedef struct ArPointCloud_ ArPointCloud;`
- L26 _typedef_ `typedef struct ArAnchor_ ArAnchor;`
- L158 _prototype_ `ENUM_CLASS_FLAGS(EGoogleARCoreLineTraceChannel);`
- L296 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGoogleARCoreOnConfigCameraDelegate, const TArray<FGoogleARCoreCameraConfig>&);` — @cond EXCLUDE_FROM_DOXYGEN
- L319 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGoogleARCoreOnConfigCameraDynamicDelegate, const TArray<FGoogleARCoreCameraConfig>&, SupportedCameraConfig);` — @cond EXCLUDE_FROM_DOXYGEN
