# Plugins / AndroidBackgroundService

- module root: `Plugins/Runtime/AndroidBackgroundService/Source/AndroidBackgroundService`
- headers: 2; symbols: 93
- symbol kinds: class=2, delegate=2, enum=1, enumerator=4, function=1, member=51, namespace=5, prototype=23, struct=3, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Launch

### `Plugins/Runtime/AndroidBackgroundService/Source/AndroidBackgroundService/Private/AndroidJniWorkManagerUEWorker.h` (Private)


#### struct `UE::Jni::WorkManager::FUEWorker`  
`struct FUEWorker: Java::Lang::FObject`  
_L11-23_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L15 _public prototype_ `static void JNICALL nativeAndroidBackgroundServicesOnWorkerStart(JNIEnv* env, jobject thiz, jstring WorkID);`
- L16 _public prototype_ `static void JNICALL nativeAndroidBackgroundServicesOnWorkerStop(JNIEnv* env, jobject thiz, jstring WorkID);`
- L18 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundServicesOnWorkerStart), UE_JNI_NATIVE_METHOD(nativeAndroidBackgroundServicesOnWorkerStop) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L9 _namespace_ `namespace WorkManager` (scope `UE::Jni`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Jni` (scope `UE`)
- L28 _variable_ `template struct TInitialize<WorkManager::FUEWorker>;` (scope `UE::Jni`)

### `Plugins/Runtime/AndroidBackgroundService/Source/AndroidBackgroundService/Public/UEWorkManagerNativeWrapper.h` (Public)


#### class `FUEWorkManagerNativeWrapper`  
`class FUEWorkManagerNativeWrapper`  
_L14-149_
- desc: This class mirrors the UEWorkManagerJavaInterface on the Java side. These 2 functions exist as the bridge between any UE C++ native code and the java workmanager code.
- L129 _public prototype_ `static bool ScheduleBackgroundWork(FString UniqueWorkName, FWorkRequestParametersNative& WorkParameters);` — Functions used to control work
- L130 _public prototype_ `static TOptional<bool> CheckIfBackgroundWorkerIsRunning(FString UniqueWorkName);`
- L131 _public prototype_ `static void CancelBackgroundWork(FString UniqueWorkName);`
- L133 _public member_ `static FJavaClassInfo JavaInfo;`
- L145 _public prototype_ `static void SetWorkResultOnWorker(jobject Worker, EAndroidBackgroundWorkResult Result);` — Wrapper for setting the work result on the underlying java worker through JNI
- L148 _public prototype_ `static EAndroidBackgroundWorkResult GetWorkResultOnWorker(jobject Worker);` — Wrapper for getting the work result on the underlying java worker through JNI

#### struct `FUEWorkManagerNativeWrapper::FWorkRequestParametersNative`  
`struct FWorkRequestParametersNative`  
_L18-95_
- L21 _public member_ `bool bRequireBatteryNotLow;`
- L22 _public member_ `bool bRequireCharging;`
- L23 _public member_ `bool bRequireDeviceIdle;`
- L24 _public member_ `bool bRequireWifi;`
- L25 _public member_ `bool bRequireAnyInternet;`
- L26 _public member_ `bool bAllowRoamingInternet;`
- L27 _public member_ `bool bRequireStorageNotLow;`
- L28 _public member_ `bool bStartAsForegroundService;`
- L30 _public member_ `bool bIsPeriodicWork;`
- L32 _public member_ `long InitialStartDelayInSeconds;`
- L34 _public member_ `bool bIsRecurringWork;`
- L36 _public member_ `int RepeatIntervalInMinutes;`
- L38 _public member_ `bool bUseLinearBackoffPolicy;`
- L39 _public member_ `int InitialBackoffDelayInSeconds;`
- L41 _public member_ `jclass WorkerJavaClass;`
- L45 _private member_ `jobject UnderlyingJavaObject;` — We spin up a version of the Java interface so that we can
- L48 _private prototype_ `void UpdateUnderlyingJavaFields();` — Calling this will update the underlying Java object with any changes we have made to our public fields on the C++ side.
- L53 _private prototype_ `void PopulateWorkRequestParameterJavaInfo();`
- L55 _private member_ `jmethodID WorkRequestParams_Method_AddExtraWorkDataObj;`
- L56 _private member_ `jmethodID WorkRequestParams_Method_AddExtraWorkDataInt;`
- L57 _private member_ `jmethodID WorkRequestParams_Method_AddExtraWorkDataLong;`
- L58 _private member_ `jmethodID WorkRequestParams_Method_AddExtraWorkDataFloat;`
- L59 _private member_ `jmethodID WorkRequestParams_Method_AddExtraWorkDataDouble;`
- L60 _private member_ `jmethodID WorkRequestParams_Method_AddExtraWorkDataBool;`
- L62 _private member_ `jfieldID WorkRequestParams_Field_bRequireBatteryNotLow;`
- L63 _private member_ `jfieldID WorkRequestParams_Field_bRequireCharging;`
- L64 _private member_ `jfieldID WorkRequestParams_Field_bRequireDeviceIdle;`
- L65 _private member_ `jfieldID WorkRequestParams_Field_bRequireWifi;`
- L66 _private member_ `jfieldID WorkRequestParams_Field_bRequireAnyInternet;`
- L67 _private member_ `jfieldID WorkRequestParams_Field_bAllowRoamingInternet;`
- L68 _private member_ `jfieldID WorkRequestParams_Field_bRequireStorageNotLow;`
- L69 _private member_ `jfieldID WorkRequestParams_Field_bStartAsForegroundService;`
- L70 _private member_ `jfieldID WorkRequestParams_Field_bIsPeriodicWork;`
- L71 _private member_ `jfieldID WorkRequestParams_Field_InitialStartDelayInSeconds;`
- L72 _private member_ `jfieldID WorkRequestParams_Field_bIsRecurringWork;`
- L73 _private member_ `jfieldID WorkRequestParams_Field_RepeatIntervalInMinutes;`
- L74 _private member_ `jfieldID WorkRequestParams_Field_bUseLinearBackoffPolicy;`
- L75 _private member_ `jfieldID WorkRequestParams_Field_InitialBackoffDelayInSeconds;`
- L76 _private member_ `jfieldID WorkRequestParams_Field_WorkerJavaClass;`
- L80 _public prototype_ `FWorkRequestParametersNative();`
- L81 _public prototype_ `~FWorkRequestParametersNative();`
- L84 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, jobject JObjIn);` — Add values to the eventual Worker's WorkParameters through these functions.
- L85 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, const FString& StringIn);`
- L86 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, const FText& TextIn);`
- L87 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, int IntIn);`
- L88 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, bool BoolIn);`
- L89 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, long LongIn);`
- L90 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, float FloatIn);`
- L91 _public prototype_ `void AddDataToWorkerParameters(const FString& DataKey, double DoubleIn);`
- L94 _public prototype_ `jobject GetUnderlyingJavaObject();` — Gets the underlying java object representing this struct

#### struct `FUEWorkManagerNativeWrapper::FJavaClassInfo`  
`struct FJavaClassInfo`  
_L99-125_
- desc: struct holding all our Java class, method, and field information in one location. Must call initialize on this before it is useful. Future calls to Initialize will not recalculate information
- L101 _public member_ `bool bHasInitialized = false;`
- L103 _public member_ `jclass DefaultUEWorkerJavaClass;`
- L104 _public member_ `jclass UEWorkManagerJavaInterfaceClass;`
- L105 _public member_ `jclass WorkRequestParametersJavaInterfaceClass;`
- L107 _public member_ `jmethodID GetApplicationContextMethod;`
- L109 _public member_ `jmethodID JavaInterface_Method_RegisterWork;`
- L110 _public member_ `jmethodID JavaInterface_Method_IsWorkActive;`
- L111 _public member_ `jmethodID JavaInterface_Method_CancelWork;`
- L112 _public member_ `jmethodID JavaInterface_Method_CreateWorkRequestParameters;`
- L114 _public prototype_ `void Initialize();`
- L116 _public function_ `FJavaClassInfo() : DefaultUEWorkerJavaClass(0) , UEWorkManagerJavaInterfaceClass(0) , WorkRequestParametersJavaInterfaceClass(0) , GetApplicationContextMethod(0) , JavaInterface_Method_RegisterWork(0) , JavaInterface_Method_CancelWork(0) , JavaInterface_Method_CreateWorkRequestParameters(0)`

#### enum `FUEWorkManagerNativeWrapper::EAndroidBackgroundWorkResult`  
`enum class EAndroidBackgroundWorkResult`  
_L136-142_
- desc: Possible results for work
- L138 _public enumerator_ `Success`
- L139 _public enumerator_ `Failure`
- L140 _public enumerator_ `Retry`
- L141 _public enumerator_ `NotSet`

#### class `FAndroidBackgroundServicesDelegates`  
`class FAndroidBackgroundServicesDelegates`  
_L152-160_
- desc: call backs so that we can bubble up UEWorker callbacks to UE systems
- L155 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAndroidBackgroundServices_OnWorkerStart, FString , jobject );`
- L156 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAndroidBackgroundServices_OnWorkerStop, FString , jobject );`
- L158 _public member_ `static FAndroidBackgroundServices_OnWorkerStart AndroidBackgroundServices_OnWorkerStart;`
- L159 _public member_ `static FAndroidBackgroundServices_OnWorkerStop AndroidBackgroundServices_OnWorkerStop;`

#### Free symbols / members of external scopes

- L155 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAndroidBackgroundServices_OnWorkerStart, FString , jobject );`
- L156 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAndroidBackgroundServices_OnWorkerStop, FString , jobject );`
