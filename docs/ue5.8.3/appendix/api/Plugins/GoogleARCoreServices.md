# Plugins / GoogleARCoreServices

- module root: `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices`
- headers: 7; symbols: 131
- symbol kinds: class=6, enum=4, enumerator=26, function=9, macro=4, member=19, namespace=1, prototype=53, struct=2, typedef=4, union=1, variable=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, GoogleARCoreSDK, XRBase
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: AugmentedReality, HeadMountedDisplay

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Private/GoogleARCoreCloudARPinManager.h` (Private)


#### class `FGoogleARCoreCloudARPinManager`  
`class FGoogleARCoreCloudARPinManager : public FGCObject`  
_L11-90_
- inherits: `FGCObject`
- L15 _public prototype_ `static FGoogleARCoreCloudARPinManager* CreateCloudARPinManager(TSharedRef<FARSupportInterface, ESPMode::ThreadSafe> InArSystem);`
- L18 _public prototype_ `virtual bool IsCloudARPinModeSupported(EARPinCloudMode NewMode) = 0;` — public member method:
- L20 _public prototype_ `virtual bool SetCloudARPinMode(EARPinCloudMode NewMode) = 0;`
- L23 _public prototype_ `virtual UCloudARPin* CreateAndHostCloudARPin(UARPin* PinToHost, int32 LifetimeInDays, EARPinCloudTaskResult& OutTaskResult);` — Start a background task to host a CloudARPin.
- L26 _public prototype_ `virtual UCloudARPin* ResolveAndCreateCloudARPin(FString CloudID, EARPinCloudTaskResult& OutTaskResult);` — Start a background task to create a new CloudARPin and resolve it from the CloudID.
- L28 _public prototype_ `virtual void RemoveCloudARPin(UCloudARPin* PinToRemove);`
- L31 _public function_ `TArray<UCloudARPin*> GetAllCloudARPin()` — Return all the CloudARPin in the current session.
- L37 _public prototype_ `virtual void Tick();` — Tick the CloudARPinManager.
- L41 _public function_ `virtual ~FGoogleARCoreCloudARPinManager()` — public properties:
- L45 _protected function_ `FGoogleARCoreCloudARPinManager(TSharedRef<FARSupportInterface, ESPMode::ThreadSafe> InArSystem) : ARSystem(InArSystem)` — protected methods:
- L51 _protected prototype_ `virtual void UpdateAllCloudARPins();`
- L53 _protected function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L61 _protected function_ `virtual FString GetReferencerName() const override`
- L66 _protected function_ `virtual void OnAlignmentTransformUpdated(const FTransform& NewAlignmentTransform)`
- L75 _protected member_ `TSharedRef<FARSupportInterface, ESPMode::ThreadSafe> ARSystem;` — protected properties:
- L76 _protected member_ `TArray<TObjectPtr<UCloudARPin>> AllCloudARPins;`
- L78 _protected member_ `TArray<TObjectPtr<UCloudARPin>> PendingCloudARPins;` — CloudARPins that have an async action pending.
- L82 _protected prototype_ `virtual void UpdateCloudARPin(UCloudARPin* CloudARPin, ArSession* SessionHandle);`
- L84 _protected prototype_ `virtual ArSession* GetSessionHandle() = 0;`
- L86 _protected prototype_ `virtual ArFrame* GetARFrameHandle() = 0;`
- L88 _protected member_ `TMap<ArAnchor*, UCloudARPin*> HandleToCloudPinMap;`

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Private/GoogleARCoreServicesEditorSettings.h` (Private)


#### class `UGoogleARCoreServicesEditorSettings`  
`class UGoogleARCoreServicesEditorSettings : public UObject`  
_L10-22_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: Helper class used to expose GoogleARCoreServices setting in the Editor plugin settings.
- L17 _public member_ `FString AndroidAPIKey;` — `UPROPERTY(EditAnywhere, config, Category = "ARCore Services Plugin Settings", meta = (ShowOnlyInnerProperties))` — The API key for GoogleARCoreServices on Android platform.
- L21 _public member_ `FString IOSAPIKey;` — `UPROPERTY(EditAnywhere, config, Category = "ARCore Services Plugin Settings", meta = (ShowOnlyInnerProperties))` — The API key for GoogleARCoreServices on iOS platform.

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Private/GoogleARCoreServicesManager.h` (Private)


#### class `FGoogleARCoreServicesManager`  
`class FGoogleARCoreServicesManager`  
_L12-44_
- L16 _public prototype_ `FGoogleARCoreServicesManager();`
- L18 _public prototype_ `~FGoogleARCoreServicesManager();`
- L20 _public prototype_ `bool ConfigGoogleARCoreServices(FGoogleARCoreServicesConfig& ServiceConfig);`
- L22 _public prototype_ `UCloudARPin* CreateAndHostCloudARPin(UARPin* ARPinToHost, int32 InLifetimeInDays, EARPinCloudTaskResult& OutTaskResult);`
- L24 _public prototype_ `UCloudARPin* ResolveAncCreateCloudARPin(FString CloudId, EARPinCloudTaskResult& OutTaskResult);`
- L26 _public prototype_ `void RemoveCloudARPin(UCloudARPin* PinToRemove);`
- L28 _public prototype_ `TArray<UCloudARPin*> GetAllCloudARPin();`
- L31 _private prototype_ `bool InitARSystem();`
- L33 _private prototype_ `EARPinCloudTaskResult CheckCloudTaskError();`
- L35 _private prototype_ `void OnARSessionStarted();`
- L36 _private prototype_ `void OnWorldTickStart(UWorld* World, ELevelTick TickType, float DeltaTime);`
- L38 _private member_ `bool bHasValidARSystem;`
- L39 _private member_ `bool bCloudARPinEnabled;`
- L40 _private member_ `FGoogleARCoreServicesConfig CurrentServicesConfig;`
- L42 _private member_ `TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARSystem;`
- L43 _private member_ `TUniquePtr<FGoogleARCoreCloudARPinManager> CloudARPinManager;`

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Private/GoogleARCoreServicesModule.h` (Private)


#### class `FGoogleARCoreServicesModule`  
`class FGoogleARCoreServicesModule : public IModuleInterface`  
_L8-20_
- inherits: `IModuleInterface`
- L14 _public prototype_ `static FGoogleARCoreServicesManager* GetARCoreServicesManager();` — This function will always return a valid FGoogleARCoreServicesManager. Or it will cause a crash if the function is called before the module startup.
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation.
- L18 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Private/GoogleARCoreUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define ARCORE_SERVICE_SUPPORTED_PLATFORM 1`
- L10 _macro_ `#define ARCORE_SERVICE_SUPPORTED_PLATFORM 0`
- L24 _namespace_ `namespace (anonymous)`
- L25 _function_ `EARTrackingState ToARTrackingState(ArTrackingState State)` (scope `__anon1db6f4ca0111`)
- L38 _variable_ `const FMatrix ARCoreToUnrealTransform = FMatrix( FPlane(0.0f, 0.0f, -1.0f, 0.0f), FPlane(1.0f, 0.0f, 0.0f, 0.0f), FPlane(0.0f, 1.0f, 0.0f, 0.0f), FPlane(0.0f, 0.0f, 0.0f, 1.0f));` (scope `__anon1db6f4ca0111`)
- L44 _variable_ `const FMatrix ARCoreToUnrealTransformInverse = ARCoreToUnrealTransform.InverseFast();` (scope `__anon1db6f4ca0111`)
- L46 _function_ `FTransform ARCorePoseToUnrealTransform(ArPose* ArPoseHandle, const ArSession* SessionHandle, float WorldToMeterScale)` (scope `__anon1db6f4ca0111`)
- L56 _function_ `void UnrealTransformToARCorePose(const FTransform& UnrealTransform, const ArSession* SessionHandle, ArPose** OutARPose, float WorldToMeterScale)` (scope `__anon1db6f4ca0111`)

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Public/GoogleARCoreServicesFunctionLibrary.h` (Public)


#### class `UGoogleARCoreServicesFunctionLibrary`  
`class UGoogleARCoreServicesFunctionLibrary : public UBlueprintFunctionLibrary`  
_L15-93_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: A function library that provides static/Blueprint functions for Google ARCore Services.
- L31 _public prototype_ `static bool ConfigGoogleARCoreServices(FGoogleARCoreServicesConfig ServiceConfig);` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|Configuration", meta = (Keywords = "googlear ar service config"))` — Configure the current Unreal AR session with the desired GoogleARCoreServices configuration. If there is an running AR session, the configuration will take effect immediately. Otherwise, it will take effect when the next AR session is running. @param ServiceConfig	 The desired GoogleARCoreServices configuration. @return               True if GoogleARCoreServices is configured successfully. False if the configuration failed to apply.
- L48 _public prototype_ `static void CreateAndHostCloudARPinLatentAction(UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, UARPin* ARPinToHost, int32 LifetimeInDays, EARPinCloudTaskResult& OutHostingResult, UCloudARPin*& OutCloudARPin);` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|CloudARPin", meta = (Latent, LatentInfo = "LatentInfo", LifetimeInDays = 1, WorldContext = "WorldContextObject", Keywords = "googlear ar service host cloud"))` — This will start a Latent Action to host the ARPin and creating a UCloudARPin from it. The complete flow of this Latent Action will be triggered if the hosting is complete or an error has occurred. Note that a UCloudARPin will be always created when this function is called, even in the case that the CloudId is failed to host. You can check the CloudState of returning UCloudARPin to see why the hosting failed. @param ARPinToHost       The ARPin to host. @param LifetimeInDays	The lifetime of the cloud anchor in days. @param OutHostingResult  The ARPin hosting result. @param OutCloudARPin     A new instance of UCloudARPin created using the input ARPinToHost.
- L64 _public prototype_ `static void CreateAndResolveCloudARPinLatentAction(UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, FString CloudId, EARPinCloudTaskResult& OutAcquiringResult, UCloudARPin*& OutCloudARPin);` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|CloudARPin", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", Keywords = "googlear ar service resolve cloud"))` — This will start a Latent Action to create UCloudARPin using the given CloudId. The complete flow of this Latent Action will be triggered if creating the UCloudARPin is successfully or an error has occurred. Note that a UCloudARPin will be always created when this function is called, even in the case that the CloudId is failed to resolve. You can check the CloudState of returning UCloudARPin to see why the resolving failed. @param CloudId               The CloudId that will be used to resolve the ARPin @param OutAcquiringResult    The ARPin acquiring result. @param OutARPin              The ARPin that is created when calling this function.
- L72 _public prototype_ `static UCloudARPin* CreateAndHostCloudARPin(UARPin* ARPinToHost, int32 LifetimeInDays, EARPinCloudTaskResult& OutTaskResult);` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|CloudARPin", meta = (LifetimeInDays = 1, Keywords = "googlear ar service remove "))` — Creating and hosting a CloudARPin and return it immediately. Note that this function only start the hosting process. Call GetARPinCloudState to check if the hosting is finished or failed with error.
- L80 _public prototype_ `static UCloudARPin* CreateAndResolveCloudARPin(FString CloudId, EARPinCloudTaskResult& OutTaskResult);` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|CloudARPin", meta = (Keywords = "googlear ar service remove "))` — Creating and Resolving a CloudARPin and return it immediately. Note that this function only start the acquiring process. Call GetARPinCloudState to check if the acquiring is finished or failed with error.
- L86 _public prototype_ `static void RemoveCloudARPin(UCloudARPin* PinToRemove);` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|CloudARPin", meta = (Keywords = "googlear ar service remove "))` — Remove the given CloudARPin from the current ARSession.
- L92 _public prototype_ `static TArray<UCloudARPin*> GetAllCloudARPin();` — `UFUNCTION(BlueprintCallable, Category = "GoogleARCoreServices|CloudARPin", meta = (Keywords = "googlear ar service all"))` — Get a list of all CloudARPin in the current ARSession.

### `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Public/GoogleARCoreServicesTypes.h` (Public)


#### enum `EARPinCloudMode`  
`enum class EARPinCloudMode : uint8`  
_L35-39_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCoreServices|Configuration")`
- desc: @ingroup GoogleARCoreServices This is an enum that can be set in a FGoogleARCoreServicesConfig to enable/disable cloud ARPin. When EARPinCloudMode is Enabled, ARCoreServices will provides functionalities of hosting and resolving cloud ARPins, with the overhead of maintaining the rolling buffer of feature/IMU measurements, and the requirements of INTERNET permissions.
- L37 _public enumerator_ `Disabled = 0`
- L38 _public enumerator_ `Enabled = 1`

#### struct `FGoogleARCoreServicesConfig`  
`struct FGoogleARCoreServicesConfig`  
_L46-53_
- reflection: `USTRUCT(BlueprintType, Category = "GoogleARCoreServices|Configuration")`
- desc: @ingroup GoogleARCoreServices A struct describes the configuration in GoogleARCore Services
- L52 _public member_ `EARPinCloudMode ARPinCloudMode = EARPinCloudMode::Disabled;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GoogleARCoreServices|Configuration")` — Whether enabling ARPin hosting/resolving in GoogleARCoreServices.

#### enum `EARPinCloudTaskResult`  
`enum class EARPinCloudTaskResult : uint8`  
_L60-85_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCoreServices|CloudARPin")`
- desc: @ingroup GoogleARCoreServices A enum describes the CloudARPin task result.
- L65 _public enumerator_ `Success` — CloudARPin hosting/resolving task is successfully completed. Only used the latent action UGoogleARCoreServicesFunctionLibrary::CreateAndHostCloudARPinLatentAction and UGoogleARCoreServicesFunctionLibrary::CreateAndResolveCloudARPinLatentAction.
- L69 _public enumerator_ `Failed` — CloudARPin hosting/resolving is failed. Check the CloudARPin cloud state for details why it failed. Only used the latent action UGoogleARCoreServicesFunctionLibrary::CreateAndHostCloudARPinLatentAction and UGoogleARCoreServicesFunctionLibrary::CreateAndResolveCloudARPinLatentAction.
- L73 _public enumerator_ `Started` — CloudARPin hosting/resolving is started successfully. Only used the non-latent UGoogleARCoreServicesFunctionLibrary::HostARPin and UGoogleARCoreServicesFunctionLibrary::AcquireHostedARPin.
- L75 _public enumerator_ `CloudARPinNotEnabled` — CloudARPin hosting/resolving failed because ARPin hosting isn't enabled.
- L77 _public enumerator_ `NotTracking` — CloudARPin hosting/resolving failed because ARPin is not in Tracking State.
- L79 _public enumerator_ `SessionPaused` — CloudARPin hosting/resolving failed because there is no valid ARSession or the session is paused.
- L81 _public enumerator_ `InvalidPin` — CloudARPin hosting failed because the input ARPin is invalid.
- L84 _public enumerator_ `ResourceExhausted` — CloudARPin hosting failed because a new CloudARPin couldn't be created in ARSystem due to resource exhausted.

#### enum `ECloudARPinCloudState`  
`enum class ECloudARPinCloudState : uint8`  
_L92-154_
- reflection: `UENUM(BlueprintType, Category = "GoogleARCoreServices|CloudARPin")`
- desc: @ingroup GoogleARCoreServices A enum describes the cloud state of a CloudARPin.
- L96 _public enumerator_ `NotHosted` — The CloudARPin just got created and the background task for hosting/resolving the CloudARPin hasn't started yet.
- L102 _public enumerator_ `InProgress` — A hosting/resolving task for the CloudARPin has been scheduled. Once the task completes in the background, the CloudARPin will get a new cloud state in the next frame. NOTE: this does not correspond to an ArCloudAnchorState, this value results with the ArFuture is pending.
- L106 _public enumerator_ `Cancelled` — A hosting/resolving task has been cancelled.  This CloudARPin would not be cloud hosted. NOTE: this does not correspond to an ArCloudAnchorState, this value results with the ArFuture is canccelled.
- L109 _public enumerator_ `Success` — A hosting/resolving task for this CloudARPin completed successfully.
- L114 _public enumerator_ `ErrorInternalError` — A hosting/resolving task for this CloudARPin finished with an internal error. This error is hard to recover from, and there is likely nothing that the developer can do to mitigate it.
- L118 _public enumerator_ `ErrorNotAuthorized` — The app cannot communicate with the Google AR Cloud Service because of a bad/invalid/nonexistent API key in the manifest.
- L122 _public enumerator_ `ErrorLocalizationFailure` — The server could not localize the device for the requested Cloud ID. This means that the ARPin was not present in the user's surroundings.
- L129 _public enumerator_ `ErrorServiceUnavailable` — The Google AR Cloud Service was unreachable. This can happen because of a number of reasons. The request sent to the server could have timed out with no response, there could be a bad network connection, DNS unavailability, firewall issues, or anything that could affect the device's ability to connect to the Google AR cloud service.
- L134 _public enumerator_ `ErrorResourceExhausted` — The application has exhausted the request quota allotted to the given API key. The developer should request more quota for the Google AR Cloud Service for their API key from the Google Developer Console.
- L139 _public enumerator_ `ErrorHostingDatasetProcessingFailed` — Hosting failed, because the server could not successfully process the dataset for the given anchor. The developer should try again after the device has gathered more data from the environment.
- L143 _public enumerator_ `ErrorResolvingCloudIDNotFound` — Resolving failed, because the AR Cloud Service could not find the provided cloud anchor ID.
- L148 _public enumerator_ `ErrorSDKVersionTooOld` — The CloudARPin could not be resolved because the SDK used to host the CloudARPin was newer than the version being used to acquire it. These versions must be an exact match.
- L153 _public enumerator_ `ErrorSDKVersionTooNew` — The CloudARPin could not be acquired because the SDK used to host the CloudARPin was older than the version being used to acquire it. These versions must be an exact match.

#### enum `ECloudAnchorFutureType`  
`enum class ECloudAnchorFutureType : uint8`  
_L158-163_
- L160 _public enumerator_ `Unknown`
- L161 _public enumerator_ `Host`
- L162 _public enumerator_ `Resolve`

#### struct `FGoogleARFutureHolder`  
`struct FGoogleARFutureHolder`  
_L167-190_
- L169 _public prototype_ `static GoogleARFutureHolderPtr MakeHostFuture();`
- L170 _public prototype_ `static GoogleARFutureHolderPtr MakeResolveFuture();`
- L172 _public prototype_ `FGoogleARFutureHolder(ECloudAnchorFutureType InFutureType);`
- L173 _public prototype_ `~FGoogleARFutureHolder();`
- L175 _public prototype_ `ArHostCloudAnchorFuture** GetHostFuturePtr();`
- L176 _public prototype_ `ArResolveCloudAnchorFuture** GetResolveFuturePtr();`
- L177 _public prototype_ `ECloudAnchorFutureType GetFutureType() const;`
- L178 _public prototype_ `ArFuture* const AsFuture() const;`
- L179 _public prototype_ `ArHostCloudAnchorFuture* const AsHostFuture() const;`
- L180 _public prototype_ `ArResolveCloudAnchorFuture* const AsResolveFuture() const;`
- L183 _private member_ `const ECloudAnchorFutureType FutureType;`

#### union `FGoogleARFutureHolder::(anonymous)`  
``  
_L185-189_

#### class `UCloudARPin`  
`class UCloudARPin : public UARPin`  
_L199-242_
- reflection: `UCLASS(BlueprintType, Experimental, Category = "GoogleARCoreServices|CloudARPin")`
- inherits: `UARPin`
- desc: A CloudARPin will be created when you host an existing ARPin, or resolved a previous hosted CloudARPin. It is a subclass of UARPin so all functions on UARPin works on CloudARPin, besides that you can query its CloudState and CloudID
- L205 _public prototype_ `UCloudARPin();`
- L213 _public prototype_ `FString GetCloudID();` — `UFUNCTION(BlueprintPure, Category = "GoogleARCoreServices|CloudARPin")` — Gets the CloudID of this CloudARPin. @return	Return a non-empty FString if the CloudARPin is ready. otherwise, return an empty FString.
- L220 _public prototype_ `ECloudARPinCloudState GetARPinCloudState();` — `UFUNCTION(BlueprintPure, Category = "GoogleARCoreServices|CloudARPin")` — Gets the current cloud state of this CloudARPin. Note that the cloud state will only be updated once per frame.
- L223 _public prototype_ `void UpdateCloudState(ECloudARPinCloudState NewCloudState, FString NewCloudID);`
- L225 _public prototype_ `void SetFuture(GoogleARFutureHolderPtr FutureHolder);`
- L226 _public prototype_ `GoogleARFutureHolderPtr GetFuture() const;`
- L227 _public prototype_ `bool IsPending() const;`
- L228 _public prototype_ `void ReleaseFuture();`
- L230 _public prototype_ `void UpdateCloudState(ECloudARPinCloudState NewCloudState);`
- L232 _public prototype_ `void SetCloudID(FString NewCloudID);`
- L236 _private member_ `ECloudARPinCloudState CloudState;`
- L237 _private member_ `FString CloudID;`
- L240 _private member_ `GoogleARFutureHolderPtr Future;`

#### Free symbols / members of external scopes

- L9 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogGoogleARCoreServices, Log, All);`
- L13 _macro_ `#define ARCORE_USE_OLD_CLOUD_ANCHOR_ASYNC 1`
- L15 _macro_ `#define ARCORE_USE_OLD_CLOUD_ANCHOR_ASYNC 0`
- L19 _typedef_ `typedef struct ArFuture_ ArFuture;`
- L20 _typedef_ `typedef struct ArHostCloudAnchorFuture_ ArHostCloudAnchorFuture;`
- L21 _typedef_ `typedef struct ArResolveCloudAnchorFuture_ ArResolveCloudAnchorFuture;`
- L166 _typedef_ `typedef TSharedPtr<struct FGoogleARFutureHolder> GoogleARFutureHolderPtr;` — An raii holder for ArFutures of the types we use, to ensure they are released.
- L186 _member_ `ArFuture* Future;` (scope `FGoogleARFutureHolder::__anon9f976d56010a`)
- L187 _member_ `ArHostCloudAnchorFuture* HostFuture;` (scope `FGoogleARFutureHolder::__anon9f976d56010a`)
- L188 _member_ `ArResolveCloudAnchorFuture* ResolveFuture;` (scope `FGoogleARFutureHolder::__anon9f976d56010a`)
