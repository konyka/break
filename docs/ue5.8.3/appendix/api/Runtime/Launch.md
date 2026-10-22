# Runtime / Launch

- module root: `Source/Runtime/Launch`
- headers: 12; symbols: 344
- symbol kinds: class=6, delegate=4, enum=1, enumerator=19, externvar=2, function=5, macro=37, member=171, namespace=2, prototype=92, struct=3, variable=2
- DynamicallyLoadedModuleNames: AndroidLocalNotification, AndroidRuntimeSettings, AudioMixerCoreAudio, AudioMixerPlatformAudioLink, AudioMixerSDL, AudioMixerWasapi, AudioMixerXAudio2, AutomationController, AutomationWindow, EditorStyle, HTTP, MainFrame, Media, MediaAssets, MeshUtilities, OpenGLDrv, OutputLog, ProfileVisualizer, Renderer, SlateNullRenderer, SlateRHIRenderer, SourceCodeAccess, TextureCompressor, WindowsPlatformFeatures, XMPP
- PrivateDependencyModuleNames: AgilitySDK, ApplicationCore, AudioMixerAndroid, AutomationWorker, ClothingSystemRuntimeInterface, ClothingSystemRuntimeNv, Core, CoreUObject, DerivedDataCache, DesktopPlatform, EditorFramework, Engine, FunctionalTesting, HeadMountedDisplay, InputCore, InstallBundleManager, Json, LauncherCheck, MRMesh, MainFrame, MediaUtils, MoviePlayer, MoviePlayerProxy, NetworkFile, Networking, OpenGLDrv, Overlay, PakFile, PreLoadScreen, Projects, RHI, RenderCore, SandboxFile, Serialization, Settings, Slate, SlateCore, Sockets, SourceControl, StorageServerClient, StorageServerClientDebug, StreamingFile, TraceLog, UnixCommonStartup, UnrealEd
- PrivateIncludePathModuleNames: AutomationController, AutomationTest, DerivedDataCache, Media, MessagingCommon, ProfileVisualizer, SlateNullRenderer, SlateRHIRenderer
- PublicDependencyModuleNames: CookOnTheFly, SessionServices

### `Source/Runtime/Launch/Private/Apple/LaunchCPPToSwift.h` (Private)


#### Free symbols / members of external scopes

- L9 _prototype_ `void KickoffEngine();`
- L14 _macro_ `#define SWIFT_IMPORT` — define this so we disable C++ etc bits swift doesn't beed
- L25 _prototype_ `void KickoffWithCompositingLayer(CP_OBJECT_cp_layer_renderer* Layer);`

### `Source/Runtime/Launch/Private/Apple/SwiftMainBridge.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SwiftMainBridgeNS` (scope `UE`)
- L14 _prototype_ `void ConfigureImmersiveSpace(int32 InImmersiveStyle, int32 InUpperLimbVisibility);` (scope `UE::SwiftMainBridgeNS`)

### `Source/Runtime/Launch/Private/IOS/GameLaunchDaemonMessageHandler.h` (Private)


#### class `FGameLaunchDaemonMessageHandler`  
`class FGameLaunchDaemonMessageHandler`  
_L15-31_
- L19 _public prototype_ `void Init();`
- L20 _public prototype_ `void Shutdown();`
- L24 _private prototype_ `void HandlePingMessage(const FIOSLaunchDaemonPing& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L25 _private prototype_ `void HandleLaunchRequest(const FIOSLaunchDaemonLaunchApp& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L29 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L30 _private member_ `FString AppId;`

### `Source/Runtime/Launch/Private/IOS/IOSAppDelegateConsoleHandling.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Launch/Private/IOS/TcpConsoleListener.h` (Private)


#### class `TcpConsoleListener`  
`class TcpConsoleListener : FRunnable`  
_L15-57_
- inherits: `FRunnable`
- L24 _public prototype_ `TcpConsoleListener(const FIPv4Endpoint& InListenEndpoint);` — Creates and initializes a new instance.
- L27 _public prototype_ `virtual ~TcpConsoleListener();` — Virtual destructor.
- L33 _public prototype_ `virtual void Exit() override;`
- L34 _public prototype_ `virtual bool Init() override;`
- L35 _public prototype_ `virtual uint32 Run() override;`
- L36 _public prototype_ `virtual void Stop() override;`
- L41 _private prototype_ `bool HandleListenerConnectionAccepted(FSocket* ClientSocket, const FIPv4Endpoint& ClientEndpoint);` — Callback for accepted connections to the local server.
- L44 _private member_ `TArray<FSocket*> Connections;` — Current connections
- L47 _private member_ `FIPv4Endpoint ListenEndpoint;` — Current settings
- L50 _private member_ `bool bStopping;` — For the thread
- L53 _private member_ `FTcpListener* Listener;` — Holds the local listener for incoming tunnel connections.
- L56 _private member_ `FRunnableThread* Thread;` — Holds the thread object.

### `Source/Runtime/Launch/Public/Android/AndroidEventManager.h` (Public)


#### enum `EAppEventState`  
`enum EAppEventState`  
_L15-36_
- L17 _public enumerator_ `APP_EVENT_STATE_WINDOW_CREATED`
- L18 _public enumerator_ `APP_EVENT_STATE_WINDOW_RESIZED`
- L19 _public enumerator_ `APP_EVENT_STATE_WINDOW_CHANGED`
- L20 _public enumerator_ `APP_EVENT_STATE_WINDOW_DESTROYED`
- L21 _public enumerator_ `APP_EVENT_STATE_WINDOW_REDRAW_NEEDED`
- L22 _public enumerator_ `APP_EVENT_STATE_ON_DESTROY`
- L23 _public enumerator_ `APP_EVENT_STATE_ON_PAUSE`
- L24 _public enumerator_ `APP_EVENT_STATE_ON_RESUME`
- L25 _public enumerator_ `APP_EVENT_STATE_ON_STOP`
- L26 _public enumerator_ `APP_EVENT_STATE_ON_START`
- L27 _public enumerator_ `APP_EVENT_STATE_WINDOW_LOST_FOCUS`
- L28 _public enumerator_ `APP_EVENT_STATE_WINDOW_GAINED_FOCUS`
- L29 _public enumerator_ `APP_EVENT_STATE_SAVE_STATE`
- L30 _public enumerator_ `APP_EVENT_STATE_APP_SUSPENDED`
- L31 _public enumerator_ `APP_EVENT_STATE_APP_ACTIVATED`
- L32 _public enumerator_ `APP_EVENT_STATE_SAFE_ZONE_UPDATED`
- L33 _public enumerator_ `APP_EVENT_RUN_CALLBACK`
- L34 _public enumerator_ `APP_EVENT_MAX_EVENTS`
- L35 _public enumerator_ `APP_EVENT_STATE_INVALID = -1`

#### struct `FAppEventData`  
`struct FAppEventData`  
_L38-52_
- L40 _public function_ `FAppEventData() : WindowWidth(-1), WindowHeight(-1)`
- L42 _public function_ `FAppEventData(TFunction<void(void)> CallbackFuncIN) : WindowWidth(-1), WindowHeight(-1), CallbackFunc(MoveTemp(CallbackFuncIN))`
- L46 _public prototype_ `FAppEventData(ANativeWindow* WindowIn);`
- L48 _public member_ `int32 WindowWidth;`
- L49 _public member_ `int32 WindowHeight;`
- L51 _public member_ `TFunction<void(void)> CallbackFunc;`

#### struct `FAppEventPacket`  
`struct FAppEventPacket`  
_L54-62_
- L56 _public member_ `EAppEventState State;`
- L57 _public member_ `FAppEventData Data;`
- L59 _public function_ `FAppEventPacket(): State(APP_EVENT_STATE_INVALID)`

#### class `FAppEventManager`  
`class FAppEventManager`  
_L64-146_
- L67 _public prototype_ `static FAppEventManager* GetInstance();`
- L69 _public prototype_ `void Tick();`
- L70 _public prototype_ `void EnqueueAppEvent(EAppEventState InState, FAppEventData&& InData = FAppEventData());`
- L71 _public prototype_ `void SetEventHandlerEvent(FEvent* InEventHandlerEvent);`
- L73 _public prototype_ `void HandleWindowCreated_EventThread(void* InWindow);` — These are called directly from the android event thread.
- L74 _public prototype_ `void HandleWindowClosed_EventThread();`
- L75 _public prototype_ `bool IsGamePaused();`
- L76 _public prototype_ `bool IsGameInFocus();`
- L77 _public prototype_ `bool WaitForEventInQueue(EAppEventState InState, double TimeoutSeconds);`
- L79 _public prototype_ `void SetEmptyQueueHandlerEvent(FEvent* InEventHandlerEvent);`
- L80 _public prototype_ `void TriggerEmptyQueue();`
- L82 _public prototype_ `void SetAppIsActive(bool bIsActive);`
- L84 _public prototype_ `void PauseAudio();`
- L85 _public prototype_ `void ResumeAudio();`
- L86 _public prototype_ `static void ReleaseMicrophone(bool shuttingDown);`
- L111 _protected prototype_ `FAppEventManager();`
- L113 _protected prototype_ `void ResumePausedGameThread();`
- L114 _protected prototype_ `void KeepGameThreadPaused();`
- L117 _private prototype_ `FAppEventPacket DequeueAppEvent();`
- L119 _private prototype_ `void ExecWindowCreated();`
- L120 _private prototype_ `void ExecWindowResized();`
- L122 _private prototype_ `static void OnScaleFactorChanged(IConsoleVariable* CVar);`
- L124 _private member_ `static FAppEventManager* sInstance;`
- L126 _private member_ `pthread_mutex_t QueueMutex;` — @todo android: can probably get rid of this now that we're using an mpsc queue
- L127 _private member_ `TQueue<FAppEventPacket, EQueueMode::Mpsc> Queue;`
- L129 _private member_ `FEvent* EventHandlerEvent;` — triggered every time the event handler thread fires off an event
- L130 _private member_ `FEvent* EmptyQueueHandlerEvent;` — triggered every time the queue is emptied
- L133 _private member_ `bool FirstInitialized;` — states
- L134 _private member_ `bool bCreateWindow;`
- L136 _private member_ `bool bWindowInFocus;`
- L137 _private member_ `bool bSaveState;`
- L138 _private member_ `bool bAudioPaused;`
- L140 _private member_ `bool bHaveWindow;`
- L141 _private member_ `bool bHaveGame;`
- L142 _private member_ `TAtomic<bool> bRunning;`
- L144 _private member_ `TAtomic<bool> bTempRunningTriggered;` — Flag to identify if the temporary running has been trigged so that APP_EVENT_STATE_APP_ACTIVATED will be only enqueued once.
- L145 _private member_ `TAtomic<bool> bAppIsActive;` — Synced with bAppIsActive_EventThread in LaunchAndroid

#### class `FAppEventManager::GameThreadTicker`  
`class GameThreadTicker`  
_L93-106_
- desc: When the game thread is stalled by operations like switching to background, GameThreadTicker can be used to resume the game thread for 1 frame and stall it again in the subsequent frame. If a wait call is behind a GameThreadTicker object on another thread, the GT will be resumed until the wait returns and the life time of the object ends.
- L97 _public function_ `GameThreadTicker()`
- L102 _public function_ `~GameThreadTicker()`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidEvents, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidEvents, Log, All);`
- L148 _prototype_ `bool IsInAndroidEventThread();`

### `Source/Runtime/Launch/Public/Android/AndroidJNI.h` (Public)


#### class `FJavaWrapper`  
`class FJavaWrapper`  
_L20-221_
- desc: Define all the Java classes/methods that the game will need to access to
- L25 _public member_ `static jclass GameActivityClassID;` — Nonstatic methods
- L26 _public member_ `static jobject GameActivityThis;`
- L27 _public member_ `static jmethodID AndroidThunkJava_ShowConsoleWindow;`
- L28 _public member_ `static jmethodID AndroidThunkJava_ShowVirtualKeyboardInputDialog;`
- L29 _public member_ `static jmethodID AndroidThunkJava_HideVirtualKeyboardInputDialog;`
- L30 _public member_ `static jmethodID AndroidThunkJava_ShowVirtualKeyboardInput;`
- L31 _public member_ `static jmethodID AndroidThunkJava_HideVirtualKeyboardInput;`
- L32 _public member_ `static jmethodID AndroidThunkJava_LaunchURL;`
- L33 _public member_ `static jmethodID AndroidThunkJava_GetAssetManager;`
- L34 _public member_ `static jmethodID AndroidThunkJava_Minimize;`
- L35 _public member_ `static jmethodID AndroidThunkJava_ClipboardCopy;`
- L36 _public member_ `static jmethodID AndroidThunkJava_ClipboardPaste;`
- L37 _public member_ `static jmethodID AndroidThunkJava_ForceQuit;`
- L38 _public member_ `static jmethodID AndroidThunkJava_GetFontDirectory;`
- L39 _public member_ `static jmethodID AndroidThunkJava_Vibrate;`
- L40 _public member_ `static jmethodID AndroidThunkJava_IsMusicActive;`
- L41 _public member_ `static jmethodID AndroidThunkJava_IsScreensaverEnabled;`
- L42 _public member_ `static jmethodID AndroidThunkJava_KeepScreenOn;`
- L43 _public member_ `static jmethodID AndroidThunkJava_InitHMDs;`
- L44 _public member_ `static jmethodID AndroidThunkJava_DismissSplashScreen;`
- L45 _public member_ `static jmethodID AndroidThunkJava_ShowProgressDialog;`
- L46 _public member_ `static jmethodID AndroidThunkJava_UpdateProgressDialog;`
- L47 _public member_ `static jmethodID AndroidThunkJava_GetInputDeviceInfo;`
- L48 _public member_ `static jmethodID AndroidThunkJava_SetInputDeviceVibrators;`
- L49 _public member_ `static jmethodID AndroidThunkJava_IsGamepadAttached;`
- L50 _public member_ `static jmethodID AndroidThunkJava_HasMetaDataKey;`
- L51 _public member_ `static jmethodID AndroidThunkJava_GetMetaDataBoolean;`
- L52 _public member_ `static jmethodID AndroidThunkJava_GetMetaDataInt;`
- L53 _public member_ `static jmethodID AndroidThunkJava_GetMetaDataLong;`
- L54 _public member_ `static jmethodID AndroidThunkJava_GetMetaDataFloat;`
- L55 _public member_ `static jmethodID AndroidThunkJava_GetMetaDataString;`
- L56 _public member_ `static jmethodID AndroidThunkJava_IsOpenXRImmersiveHMDApplication;`
- L57 _public member_ `static jmethodID AndroidThunkJava_IsOculusMobileApplication;`
- L58 _public member_ `static jmethodID AndroidThunkJava_ShowHiddenAlertDialog;`
- L59 _public member_ `static jmethodID AndroidThunkJava_LocalNotificationScheduleAtTime;`
- L60 _public member_ `static jmethodID AndroidThunkJava_LocalNotificationClearAll;`
- L61 _public member_ `static jmethodID AndroidThunkJava_LocalNotificationExists;`
- L62 _public member_ `static jmethodID AndroidThunkJava_LocalNotificationGetLaunchNotification;`
- L63 _public member_ `static jmethodID AndroidThunkJava_LocalNotificationDestroyIfExists;`
- L64 _public member_ `static jmethodID AndroidThunkJava_GetNetworkConnectionType;`
- L65 _public member_ `static jmethodID AndroidThunkJava_GetAndroidId;`
- L66 _public member_ `static jmethodID AndroidThunkJava_ShareURL;`
- L67 _public member_ `static jmethodID AndroidThunkJava_LaunchPackage;`
- L68 _public member_ `static jmethodID AndroidThunkJava_IsPackageInstalled;`
- L69 _public member_ `static jmethodID AndroidThunkJava_SendBroadcast;`
- L70 _public member_ `static jmethodID AndroidThunkJava_HasIntentExtrasKey;`
- L71 _public member_ `static jmethodID AndroidThunkJava_GetIntentExtrasBoolean;`
- L72 _public member_ `static jmethodID AndroidThunkJava_GetIntentExtrasInt;`
- L73 _public member_ `static jmethodID AndroidThunkJava_GetIntentExtrasString;`
- L74 _public member_ `static jmethodID AndroidThunkJava_GetIntentDataAsString;`
- L75 _public member_ `static jmethodID AndroidThunkJava_SetSustainedPerformanceMode;`
- L76 _public member_ `static jmethodID AndroidThunkJava_PushSensorEvents;`
- L77 _public member_ `static jmethodID AndroidThunkJava_SetOrientation;`
- L78 _public member_ `static jmethodID AndroidThunkJava_HasSharedPreference;`
- L79 _public member_ `static jmethodID AndroidThunkJava_SetSharedPreferenceBoolean;`
- L80 _public member_ `static jmethodID AndroidThunkJava_GetSharedPreferenceBoolean;`
- L81 _public member_ `static jmethodID AndroidThunkJava_SetSharedPreferenceInt;`
- L82 _public member_ `static jmethodID AndroidThunkJava_GetSharedPreferenceInt;`
- L83 _public member_ `static jmethodID AndroidThunkJava_SetSharedPreferenceString;`
- L84 _public member_ `static jmethodID AndroidThunkJava_GetSharedPreferenceString;`
- L85 _public member_ `static jmethodID AndroidThunkJava_DeleteSharedPreference;`
- L86 _public member_ `static jmethodID AndroidThunkJava_DeleteSharedPreferenceGroup;`
- L87 _public member_ `static jmethodID AndroidThunkJava_GetCacheDir;`
- L91 _public member_ `static jmethodID AndroidThunkJava_IsScreenCaptureDisabled;` — Screen capture/recording permission
- L92 _public member_ `static jmethodID AndroidThunkJava_DisableScreenCapture;`
- L95 _public member_ `static jmethodID AndroidThunkJava_HasExtraIgnoreView;` — Native view click filtering
- L98 _public member_ `static jclass InputDeviceInfoClass;` — InputDeviceInfo member field ids
- L99 _public member_ `static jfieldID InputDeviceInfo_VendorId;`
- L100 _public member_ `static jfieldID InputDeviceInfo_ProductId;`
- L101 _public member_ `static jfieldID InputDeviceInfo_ControllerId;`
- L102 _public member_ `static jfieldID InputDeviceInfo_Name;`
- L103 _public member_ `static jfieldID InputDeviceInfo_Descriptor;`
- L104 _public member_ `static jfieldID InputDeviceInfo_FeedbackMotorCount;`
- L105 _public member_ `static jfieldID InputDeviceInfo_IsExternal;`
- L108 _public member_ `static jclass GoogleServicesClassID;` — IDs related to google play services
- L109 _public member_ `static jobject GoogleServicesThis;`
- L110 _public member_ `static jmethodID AndroidThunkJava_ShowAdBanner;`
- L111 _public member_ `static jmethodID AndroidThunkJava_HideAdBanner;`
- L112 _public member_ `static jmethodID AndroidThunkJava_CloseAdBanner;`
- L113 _public member_ `static jmethodID AndroidThunkJava_LoadInterstitialAd;`
- L114 _public member_ `static jmethodID AndroidThunkJava_IsInterstitialAdAvailable;`
- L115 _public member_ `static jmethodID AndroidThunkJava_IsInterstitialAdRequested;`
- L116 _public member_ `static jmethodID AndroidThunkJava_ShowInterstitialAd;`
- L117 _public member_ `static jmethodID AndroidThunkJava_GetAdvertisingId;`
- L120 _public member_ `static jmethodID AndroidThunkJava_RegisterForRemoteNotifications;` — Optionally added if GCM plugin (or other remote notification system) enabled
- L121 _public member_ `static jmethodID AndroidThunkJava_UnregisterForRemoteNotifications;`
- L122 _public member_ `static jmethodID AndroidThunkJava_IsAllowedRemoteNotifications;`
- L125 _public member_ `static jclass JavaStringClass;` — In app purchase functionality
- L126 _public member_ `static jmethodID AndroidThunkJava_IapSetupService;`
- L127 _public member_ `static jmethodID AndroidThunkJava_IapQueryInAppPurchases;`
- L128 _public member_ `static jmethodID AndroidThunkJava_IapBeginPurchase;`
- L129 _public member_ `static jmethodID AndroidThunkJava_IapIsAllowedToMakePurchases;`
- L130 _public member_ `static jmethodID AndroidThunkJava_IapQueryExistingPurchases;`
- L131 _public member_ `static jmethodID AndroidThunkJava_IapAcknowledgePurchase;`
- L132 _public member_ `static jmethodID AndroidThunkJava_IapConsumePurchase;`
- L133 _public member_ `static jmethodID AndroidThunkJava_IapGetBillingCountryCode;`
- L134 _public member_ `static jmethodID AndroidThunkJava_IapGetIsAlternativeBillingOnlyAvailable;`
- L135 _public member_ `static jmethodID AndroidThunkJava_IapShowAlternativeBillingOnlyInformationDialog;`
- L138 _public member_ `static jmethodID AndroidThunkJava_UseSurfaceViewWorkaround;` — SurfaceView functionality for view scaling on some devices
- L139 _public member_ `static jmethodID AndroidThunkJava_SetDesiredViewSize;`
- L140 _public member_ `static jmethodID AndroidThunkJava_VirtualInputIgnoreClick;`
- L141 _public member_ `static jmethodID AndroidThunkJava_RestartApplication;`
- L144 _public member_ `static jmethodID AndroidThunkJava_GetNativeDisplayRefreshRate;` — Screen refresh rate
- L145 _public member_ `static jmethodID AndroidThunkJava_SetNativeDisplayRefreshRate;`
- L146 _public member_ `static jmethodID AndroidThunkJava_GetSupportedNativeDisplayRefreshRates;`
- L149 _public member_ `static jmethodID AndroidThunkJava_EnableMotion;` — Motion controls
- L152 _public member_ `static jmethodID AndroidThunkJava_AddNetworkListener;` — Network Connection Listener
- L153 _public member_ `static jmethodID AndroidThunkJava_RemoveNetworkListener;`
- L156 _public member_ `static jclass LaunchNotificationClass;` — member fields for getting the launch notification
- L157 _public member_ `static jfieldID LaunchNotificationUsed;`
- L158 _public member_ `static jfieldID LaunchNotificationEvent;`
- L159 _public member_ `static jfieldID LaunchNotificationFireDate;`
- L162 _public member_ `static jclass ThreadClass;` — method and classes for thread name change
- L163 _public member_ `static jmethodID CurrentThreadMethod;`
- L164 _public member_ `static jmethodID SetNameMethod;`
- L167 _public member_ `static jmethodID AndroidThunkJava_AcquireWifiManagerMulticastLock;` — WifiManager's Multicastlock handling
- L168 _public member_ `static jmethodID AndroidThunkJava_ReleaseWifiManagerMulticastLock;`
- L171 _public member_ `static jmethodID AndroidThunkJava_OnAudioFocusChangedListenersUpdated;` — audio focus
- L176 _public prototype_ `static void FindClassesAndMethods(JNIEnv* Env);` — Find all known classes and methods
- L181 _public prototype_ `static jclass FindClass(JNIEnv* Env, const ANSICHAR* ClassName, bool bIsOptional);` — Helper wrapper functions around the JNIEnv versions with NULL/error handling
- L182 _public prototype_ `static jclass FindClassGlobalRef(JNIEnv* Env, const ANSICHAR* ClassName, bool bIsOptional);`
- L183 _public prototype_ `static jmethodID FindMethod(JNIEnv* Env, jclass Class, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, bool bIsOptional);`
- L184 _public prototype_ `static jmethodID FindStaticMethod(JNIEnv* Env, jclass Class, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, bool bIsOptional);`
- L185 _public prototype_ `static jfieldID FindField(JNIEnv* Env, jclass Class, const ANSICHAR* FieldName, const ANSICHAR* FieldType, bool bIsOptional);`
- L187 _public prototype_ `static void CallVoidMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L188 _public prototype_ `static jobject CallObjectMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L189 _public prototype_ `static int32 CallIntMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L190 _public prototype_ `static int64 CallLongMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L191 _public prototype_ `static float CallFloatMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L192 _public prototype_ `static double CallDoubleMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L193 _public prototype_ `static bool CallBooleanMethod(JNIEnv* Env, jobject Object, jmethodID Method, ...);`
- L195 _public prototype_ `static void CallStaticVoidMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L196 _public prototype_ `static jobject CallStaticObjectMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L197 _public prototype_ `static int32 CallStaticIntMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L198 _public prototype_ `static int64 CallStaticLongMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L199 _public prototype_ `static float CallStaticFloatMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L200 _public prototype_ `static double CallStaticDoubleMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L201 _public prototype_ `static bool CallStaticBooleanMethod(JNIEnv* Env, jclass Clazz, jmethodID Method, ...);`
- L204 _public member_ `static FOnActivityResult OnActivityResultDelegate;` — Delegate that can be registered to that is called when an activity is finished
- L207 _public member_ `static FOnSafetyNetAttestationResult OnSafetyNetAttestationResultDelegate;` — Delegate that can be registered to that is called when an SafetyNet Attestation is finished
- L210 _public member_ `static FOnRouteServiceIntent OnRouteServiceIntentDelegate;` — Delegate that can be registered to be called when a service intent is received
- L215 _private prototype_ `static void FindGooglePlayMethods(JNIEnv* Env);` — Find GooglePlay "game services" classes and methods
- L217 _private prototype_ `static void FindGooglePlayBillingMethods(JNIEnv* Env);` — Find GooglePlay billing classes and methods
- L220 _private prototype_ `static void SetupEmbeddedCommunication(JNIEnv* Env);` — Setup communication with wrapper apps

#### Free symbols / members of external scopes

- L11 _externvar_ `extern JavaVM* GJavaVM;`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnActivityResult, JNIEnv *, jobject, jobject, jint, jint, jobject);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnActivityResult, JNIEnv *, jobject, jobject, jint, jint, jobject);`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSafetyNetAttestationResult, bool, const FString&, int32);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSafetyNetAttestationResult, bool, const FString&, int32);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRouteServiceIntent, const FString&, const FString&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRouteServiceIntent, const FString&, const FString&);`

### `Source/Runtime/Launch/Public/LaunchEngineLoop.h` (Public)


#### struct `FPreInitContext`  
`struct FPreInitContext`  
_L19-43_
- L21 _public member_ `bool bDumpEarlyConfigReads = false;`
- L22 _public member_ `bool bDumpEarlyPakFileReads = false;`
- L23 _public member_ `bool bForceQuitAfterEarlyReads = false;`
- L24 _public member_ `bool bWithConfigPatching = false;`
- L26 _public member_ `bool bDisableDisregardForGC = false;` — `UE_DEPRECATED(5.5, "Use gc.MaxObjectsNotConsideredByGC=0 ini setting instead")`
- L27 _public member_ `bool bHasEditorToken = false;`
- L28 _public member_ `bool bIsRegularClient = false;`
- L30 _public member_ `bool bTokenDoesNotHaveDash = false;` — `UE_DEPRECATED(5.1, "Use bIsPossiblyUnrecognizedCommandlet instead")`
- L31 _public member_ `bool bIsPossiblyUnrecognizedCommandlet = false;`
- L33 _public member_ `FString Token;`
- L34 _public member_ `FString CommandletCommandLine;`
- L36 _public member_ `FScopedSlowTask* SlowTaskPtr = nullptr;`
- L38 _public prototype_ `void Cleanup();`
- L41 _public member_ `TSharedPtr<FSlateRenderer> SlateRenderer;`

#### class `FEngineLoop`  
`class FEngineLoop #if WITH_ENGINE : public IEngineLoop #endif`  
_L48-205_
- inherits: `IEngineLoop`
- desc: Implements the main engine loop.
- L56 _public prototype_ `FEngineLoop();` — Default constructor.
- L58 _public prototype_ `virtual ~FEngineLoop() = default;`
- L70 _public prototype_ `int32 PreInit(int32 ArgC, TCHAR* ArgV[], const TCHAR* AdditionalCommandline = nullptr);` — Pre-Initialize the main loop, and generates the commandline from standard ArgC/ArgV from main(). @param ArgC The number of strings in ArgV. @param ArgV The command line parameters (ArgV[0] is expected to be the executable name). @param AdditionalCommandLine Optional string to append to the command line (after ArgV is put together). @return Returns the error level, 0 if successful and > 0 if there were errors.
- L78 _public prototype_ `int32 PreInit(const TCHAR* CmdLine);` — Pre-Initialize the main loop - parse command line, sets up GIsEditor, etc. @param CmdLine The command line. @return The error level; 0 if successful, > 0 if there were errors.
- L81 _public prototype_ `int32 PreInitPreStartupScreen(const TCHAR* CmdLine);` — First part of PreInit.
- L84 _public prototype_ `int32 PreInitPostStartupScreen(const TCHAR* CmdLine);` — Second part of PreInit.
- L87 _public prototype_ `void LoadPreInitModules();` — Load all modules needed before Init.
- L90 _public prototype_ `bool LoadCoreModules();` — Load core modules.
- L93 _public prototype_ `void OverrideProjectModule(const FString& InOriginalProjectModuleName, const FString& InReplacementProjectModuleName);` — Allow override of the project module loaded from project file
- L96 _public prototype_ `void CleanupPreInitContext();` — Clean up PreInit context.
- L101 _public prototype_ `bool LoadStartupCoreModules();` — Load all core modules needed at startup time.
- L104 _public prototype_ `bool LoadStartupModules();` — Load all modules needed at startup time.
- L111 _public prototype_ `virtual int32 Init() override;` — Initialize the main loop (the rest of the initialization). @return The error level; 0 if successful, > 0 if there were errors.
- L114 _public prototype_ `void InitTime();` — Initialize the timing options from the command line.
- L117 _public prototype_ `void Exit();` — Performs shut down.
- L120 _public prototype_ `bool ShouldUseIdleMode() const;` — Whether the engine should operate in an idle mode that uses no CPU or GPU time.
- L123 _public prototype_ `virtual void Tick() override;` — Advances the main loop.
- L126 _public prototype_ `virtual void ClearPendingCleanupObjects() override;` — Removes references to any objects pending cleanup by deleting them.
- L131 _public prototype_ `static void PostInitRHI();` — RHI post-init initialization
- L134 _public prototype_ `static void PreInitHMDDevice();` — Pre-init HMD device (if necessary).
- L139 _public prototype_ `static bool AppInit();` — Initializes the application.
- L142 _public prototype_ `static void AppInitLoggingOnly();` — Initializes the application sufficiently far to record a log, but then returns without any further setup.
- L149 _public prototype_ `static void AppPreExit();` — Prepares the application for shutdown. This function is called from within guarded exit code, only during non-error exits.
- L156 _public prototype_ `static void AppExit();` — Shuts down the application. This function called outside guarded exit code, during all exits (including error exits).
- L160 _private prototype_ `static void AppInitUpToSetupOutputDevices();` — The first part of AppInit, which is shared with AppInitLoggingOnly.
- L163 _private prototype_ `void ProcessLocalPlayerSlateOperations() const;` — Utility function that processes Slate operations.
- L168 _protected member_ `TArray<float> FrameTimes;` — Holds a dynamically expanding array of frame times in milliseconds (if FApp::IsBenchmarking() is set).
- L171 _protected member_ `double TotalTickTime;` — Holds the total time spent ticking engine.
- L174 _protected member_ `double MaxTickTime;` — Holds the maximum number of seconds engine should be ticked.
- L177 _protected member_ `uint64 MaxFrameCounter;` — Holds the maximum number of frames to render in benchmarking mode.
- L180 _protected member_ `uint32 LastFrameCycles;` — Holds the number of cycles in the last frame.
- L185 _protected member_ `FPendingCleanupObjects* PendingCleanupObjects;` — Holds the objects which need to be cleaned up when the rendering thread finishes the previous frame.
- L195 _private member_ `FEngineService* EngineService;` — Holds the engine service.
- L198 _private member_ `FTraceService* TraceService;` — Trace control service
- L201 _private member_ `TSharedPtr<ISessionService> SessionService;` — Holds the application session service.
- L204 _private member_ `FPreInitContext PreInitContext;`

#### Free symbols / members of external scopes

- L209 _externvar_ `extern FEngineLoop GEngineLoop;` — Global engine loop object. This is needed so wxWindows can access it.

### `Source/Runtime/Launch/Public/Mac/UEAppDelegate.h` (Public)


#### Free symbols / members of external scopes

- L9 _variable_ `NSString* Filename;`
- L10 _variable_ `bool bHasFinishedLaunching;`

### `Source/Runtime/Launch/Public/RequiredProgramMainCPPInclude.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Launch/Resources/Version.h` (Other)


#### Free symbols / members of external scopes

- L58 _macro_ `#define ENGINE_MAJOR_VERSION 5` — These numbers define the banner UE version, and are the most significant numbers when ordering two engine versions (that is, a 5.12.* version is always newer than a 5.11.* version, regardless of the changelist that it was built with) When updating these, also update the static_assert below
- L59 _macro_ `#define ENGINE_MINOR_VERSION 8`
- L60 _macro_ `#define ENGINE_PATCH_VERSION 3`
- L71 _macro_ `#define VERSION_TEXT(x) TEXT(x)` — Macros for encoding strings
- L72 _macro_ `#define VERSION_STRINGIFY_2(x) VERSION_TEXT(#x)`
- L73 _macro_ `#define VERSION_STRINGIFY(x) VERSION_STRINGIFY_2(x)`
- L76 _macro_ `#define EPIC_COMPANY_NAME "Epic Games, Inc."` — Various strings used for engine resources
- L77 _macro_ `#define EPIC_COPYRIGHT_STRING "Copyright Epic Games, Inc. All Rights Reserved."`
- L78 _macro_ `#define EPIC_PRODUCT_NAME "Unreal Engine"`
- L79 _macro_ `#define EPIC_PRODUCT_IDENTIFIER "UnrealEngine"`
- L82 _macro_ `#define ENGINE_VERSION_STRING \`

### `Source/Runtime/Launch/Resources/Windows/resource.h` (Other)


#### Free symbols / members of external scopes

- L7 _macro_ `#define IDD_OK 101` — {{NO_DEPENDENCIES}} Microsoft Visual C++ generated include file. Used by PCLaunch.rc
- L8 _macro_ `#define IDD_YESNO 102`
- L9 _macro_ `#define IDD_OKCANCEL 103`
- L10 _macro_ `#define IDD_YESNOCANCEL 104`
- L11 _macro_ `#define IDD_CANCELRETRYCONTINUE 105`
- L12 _macro_ `#define IDD_YESNO2ALL 106`
- L13 _macro_ `#define IDD_YESNO2ALLCANCEL 107`
- L14 _macro_ `#define IDD_YESNOYESTOALL 108`
- L15 _macro_ `#define IDICON_UEGame 123`
- L16 _macro_ `#define IDC_OK 1000`
- L17 _macro_ `#define IDC_YESTOALL 1001`
- L18 _macro_ `#define IDC_NOTOALL 1002`
- L19 _macro_ `#define IDC_YES 1003`
- L20 _macro_ `#define IDC_NO_B 1004`
- L21 _macro_ `#define IDC_MESSAGE 1005`
- L22 _macro_ `#define IDC_CANCEL 1006`
- L23 _macro_ `#define IDC_RETRY 1007`
- L24 _macro_ `#define IDC_CONTINUE 1008`
- L26 _macro_ `#define IDR_ACCEL1 101`
- L27 _macro_ `#define IDC_COPY 1009`
- L29 _macro_ `#define ID_HASHFILE 1010`
- L35 _macro_ `#define _APS_NEXT_RESOURCE_VALUE 109`
- L36 _macro_ `#define _APS_NEXT_COMMAND_VALUE 40001`
- L37 _macro_ `#define _APS_NEXT_CONTROL_VALUE 1010`
- L38 _macro_ `#define _APS_NEXT_SYMED_VALUE 101`
