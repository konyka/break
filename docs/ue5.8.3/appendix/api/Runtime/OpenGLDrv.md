# Runtime / OpenGLDrv

- module root: `Source/Runtime/OpenGLDrv`
- headers: 35; symbols: 2279
- symbol kinds: class=45, delegate=43, enum=13, enumerator=48, externvar=62, function=601, macro=311, member=532, namespace=10, prototype=508, struct=65, typedef=40, variable=1
- DynamicallyLoadedModuleNames: ImageWrapper
- PrivateDependencyModuleNames: ApplicationCore, ArmlibGPUInfo, CoreUObject, Engine, GoogleGameSDK, PreLoadScreen, RHICore, RenderCore, TraceLog, detex
- PrivateIncludePathModuleNames: ImageWrapper, Launch
- PublicDependencyModuleNames: Core, RHI
- PublicIncludePathModuleNames: OpenGL

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidEGL.h` (Private)


#### struct `EGLConfigParms`  
`struct EGLConfigParms`  
_L34-69_
- L37 _public member_ `int validConfig = 0;` — Whether this is a valid configuration or not
- L39 _public member_ `int redSize = 8;` — The number of bits requested for the red component
- L41 _public member_ `int greenSize = 8;` — The number of bits requested for the green component
- L43 _public member_ `int blueSize = 8;` — The number of bits requested for the blue component
- L45 _public member_ `int alphaSize = 0;` — The number of bits requested for the alpha component
- L47 _public member_ `int depthSize = 24;` — The number of bits requested for the depth component
- L49 _public member_ `int stencilSize = 0;` — The number of bits requested for the stencil component
- L51 _public member_ `int sampleBuffers = 0;` — The number of multisample buffers requested
- L53 _public member_ `int sampleSamples = 0;` — The number of samples requested
- L55 _public function_ `EGLConfigParms()`

#### struct `FAndroidEGLDisplayInfo`  
`struct FAndroidEGLDisplayInfo`  
_L71-84_
- L73 _public member_ `EGLDisplay eglDisplay = EGL_NO_DISPLAY;`
- L74 _public member_ `EGLConfig eglConfigParam = nullptr;`
- L76 _public member_ `EGLConfigParms Parms;`
- L77 _public member_ `EGLint eglNumConfigs = 0;`
- L79 _public member_ `EGLint NativeVisualID = 0;`
- L80 _public member_ `int DepthSize = 0;`
- L83 _public member_ `EGLSurface auxSurface = EGL_NO_SURFACE;` — this is an offscreen temp surface used when no HW window is supplied.

#### struct `FPlatformOpenGLContext`  
`struct FPlatformOpenGLContext`  
_L86-103_
- L88 _public function_ `FPlatformOpenGLContext()`
- L93 _public function_ `void Reset()`
- L100 _public member_ `GLuint DefaultVertexArrayObject;`
- L101 _public member_ `bool bIsDebug;`
- L102 _public member_ `EGLContext eglContext;`

#### struct `FPlatformOpenGLSurfaceContext`  
`struct FPlatformOpenGLSurfaceContext`  
_L105-160_
- L108 _public prototype_ `FPlatformOpenGLSurfaceContext(void* InWindowHandle);`
- L109 _public prototype_ `FPlatformOpenGLSurfaceContext(TOptional<FAndroidWindow::FNativeAccessor> WindowContainerIn);`
- L111 _public member_ `GLuint ViewportFramebuffer;`
- L113 _public member_ `GLuint BackBufferResource;`
- L114 _public member_ `GLenum BackBufferTarget;`
- L115 _public member_ `FPlatformRect CachedWindowRect{};`
- L117 _public member_ `bool TargetDirty = false;`
- L120 _public member_ `EGLint eglFormat = -1;` — EGLProperties
- L121 _public member_ `EGLSurface eglSurface = EGL_NO_SURFACE;`
- L122 _public member_ `EGLint eglWidth = 8;` — required for Gear VR apps with internal win surf mgmt
- L123 _public member_ `EGLint eglHeight = 8;` — required for Gear VR apps with internal win surf mgmt
- L124 _public member_ `float eglRatio = 0;`
- L125 _public member_ `ANativeWindow* Window = nullptr;`
- L126 _public member_ `bool bIsWndSurface = false;` — True when the surface is attached to a HW window.
- L128 _public function_ `EGLSurface GetSurface() const`
- L132 _private member_ `FAndroidWindow* AndroidWindow = nullptr;` — android window properties:
- L135 _public function_ `FAndroidWindow* GetAndroidWindow()`
- L137 _public function_ `bool IsUsingWindowedSurface() const`
- L139 _public function_ `FPlatformOpenGLSurfaceContext()`
- L144 _public function_ `void Reset()`

#### class `AndroidEGL`  
`class AndroidEGL`  
_L162-269_
- L171 _public prototype_ `static AndroidEGL* GetInstance();`
- L172 _public prototype_ `~AndroidEGL();`
- L174 _public prototype_ `bool IsInitialized();`
- L176 _public prototype_ `void InitBackBuffer(struct FPlatformOpenGLSurfaceContext* Surface);`
- L177 _public prototype_ `void DestroyBackBuffer(struct FPlatformOpenGLSurfaceContext* Surface);`
- L179 _public prototype_ `void Init(APIVariant API, uint32 MajorVersion, uint32 MinorVersion);`
- L181 _public prototype_ `void UnBindRender(struct FPlatformOpenGLSurfaceContext* Surface);`
- L182 _public prototype_ `void OnLostNativeWindow(FPlatformOpenGLSurfaceContext* Surface);`
- L184 _public prototype_ `void Terminate();`
- L189 _public prototype_ `void InitRenderSurface(bool bUseSmallSurface, bool bCreateWndSurface, FPlatformOpenGLSurfaceContext* Surface);` — Initialize the surface of the context. when using the new window locking behavior, if WindowContainer is not set an off screen surface will be used. TODO: remove bCreateWndSurface (and possibly bUseSmallSurface), these can be inferred from WindowContainer.
- L190 _public prototype_ `void UpdateBuffersTransform();`
- L191 _public prototype_ `bool IsOfflineSurfaceRequired();`
- L193 _public function_ `bool IsUsingRobustContext() const`
- L195 _public prototype_ `EGLDisplay GetDisplay() const;`
- L196 _public prototype_ `EGLSurface GetSurface() const;`
- L197 _public prototype_ `EGLConfig GetConfig() const;`
- L198 _public prototype_ `ANativeWindow* GetNativeWindow() const;`
- L199 _public prototype_ `void GetSwapIntervalRange(EGLint& OutMinSwapInterval, EGLint& OutMaxSwapInterval) const;`
- L201 _public prototype_ `EGLContext CreateContext(EGLContext InParentContext);`
- L202 _public prototype_ `int32 GetError();`
- L203 _public prototype_ `EGLBoolean SetCurrentContext(EGLContext InContext, FPlatformOpenGLSurfaceContext* InSurfaceInfo);`
- L205 _public prototype_ `void AcquireCurrentRenderingContext();`
- L206 _public prototype_ `void ReleaseContextOwnership();`
- L209 _public function_ `void SetWaitingForWindowCreated(bool bWaiting)` — Methods to control rendering blocking during window recreation
- L210 _public function_ `bool IsWaitingForWindowCreated() const`
- L212 _public prototype_ `EGLContext GetCurrentContext();`
- L213 _public prototype_ `EGLSurface GetCurrentSurface(EGLint readdraw);`
- L216 _public prototype_ `void SetCurrentRenderingContext(FPlatformOpenGLSurfaceContext* InSurface);`
- L217 _public prototype_ `bool ThreadHasRenderingContext();`
- L218 _public prototype_ `FPlatformOpenGLContext* GetRenderingContext();`
- L220 _public prototype_ `bool GetSupportsNoErrorContext();`
- L223 _public prototype_ `void SetRenderContextWindowSurface(const TOptional<FAndroidWindow::FNativeAccessor>& WindowHandle);` — recreate the EGL surface for the current hardware window.
- L226 _public prototype_ `void RefreshWindowSize(const TOptional<FAndroidWindow::FNativeAccessor>& WindowContainer);` — Called from game thread when a window is reinited.
- L229 _public prototype_ `bool IsUsingWindowedSurface() const;` — true if the current surface is associated with a window.
- L231 _public prototype_ `FPlatformOpenGLSurfaceContext* CreateSurfaceContextFromWindow(FAndroidWindow* InWindow);`
- L232 _public prototype_ `FPlatformOpenGLSurfaceContext* FindSurfaceContextFromWindow(FAndroidWindow* InWindow);`
- L233 _public prototype_ `void DestroySurfaceContext(FPlatformOpenGLSurfaceContext* SurfaceContext);`
- L236 _protected prototype_ `AndroidEGL();`
- L237 _protected member_ `static AndroidEGL* Singleton;`
- L240 _private prototype_ `void InitEGL(APIVariant API);`
- L241 _private prototype_ `void TerminateEGL();`
- L243 _private prototype_ `void CreateEGLRenderSurface(FPlatformOpenGLSurfaceContext* Surface, bool bCreateWndSurface);`
- L244 _private prototype_ `void DestroyRenderSurface(FPlatformOpenGLSurfaceContext* Surface);`
- L246 _private prototype_ `bool InitContexts();`
- L247 _private prototype_ `void DestroyContext(EGLContext InContext);`
- L249 _private prototype_ `void ResetDisplay();`
- L251 _private member_ `AndroidESPImpl* PImplData;`
- L253 _private prototype_ `void ResetInternal();`
- L254 _private prototype_ `void LogConfigInfo(EGLConfig EGLConfigInfo);`
- L257 _private prototype_ `void ResizeRenderContextSurface(FPlatformOpenGLSurfaceContext* Surface);` — Actual Update to the egl surface to match the GT's requested size.
- L259 _private member_ `bool bSupportsKHRCreateContext = false;`
- L260 _private member_ `bool bSupportsKHRSurfacelessContext = false;`
- L261 _private member_ `bool bSupportsKHRNoErrorContext = false;`
- L262 _private member_ `bool bSupportsEXTRobustContext = false;`
- L263 _private member_ `bool bIsEXTRobustContextActive = false;`
- L266 _private member_ `std::atomic<bool> bWaitingForWindowCreated{false};` — Flag to block rendering while waiting for APP_EVENT_STATE_WINDOW_CREATED to be processed
- L268 _private member_ `int* ContextAttributes = nullptr;`

#### enum `AndroidEGL::APIVariant`  
`enum APIVariant`  
_L165-169_
- L167 _public enumerator_ `AV_OpenGLES`
- L168 _public enumerator_ `AV_OpenGLCore`

#### class `FEGLErrorScope`  
`class FEGLErrorScope`  
_L310-344_
- L313 _public function_ `FEGLErrorScope( const TCHAR* InFunctionName, const TCHAR* InFilename, const uint32 InLine) : FunctionName(InFunctionName) , Filename(InFilename) , Line(InLine)`
- L327 _public function_ `~FEGLErrorScope()`
- L336 _private member_ `const TCHAR* FunctionName;`
- L337 _private member_ `const TCHAR* Filename;`
- L338 _private member_ `const uint32 Line;`
- L340 _private function_ `void CheckForErrors(const TCHAR* PrefixString)`

#### Free symbols / members of external scopes

- L25 _macro_ `#define USE_ANDROID_EGL_NO_ERROR_CONTEXT 1`
- L27 _macro_ `#define USE_ANDROID_EGL_NO_ERROR_CONTEXT 0`
- L31 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEGL, Log, All);`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEGL, Log, All);`
- L271 _macro_ `#define ENABLE_CONFIG_FILTER 1`
- L272 _macro_ `#define ENABLE_EGL_DEBUG 0`
- L273 _macro_ `#define ENABLE_VERIFY_EGL 0`
- L274 _macro_ `#define ENABLE_VERIFY_EGL_TRACE 0`
- L278 _macro_ `#define VERIFY_EGL(msg) { VerifyEGLResult(eglGetError(),TEXT(#msg),TEXT(""),TEXT(__FILE__),__LINE__); }`
- L280 _function_ `void VerifyEGLResult(EGLint ErrorCode, const TCHAR* Msg1, const TCHAR* Msg2, const TCHAR* Filename, uint32 Line)`
- L346 _macro_ `#define MACRO_TOKENIZER(IdentifierName, Msg, FileName, LineNumber) FEGLErrorScope IdentifierName_ ## LineNumber (Msg, FileName, LineNumber)`
- L347 _macro_ `#define MACRO_TOKENIZER2(IdentifierName, Msg, FileName, LineNumber) MACRO_TOKENIZER(IdentiferName, Msg, FileName, LineNumber)`
- L348 _macro_ `#define VERIFY_EGL_SCOPE_WITH_MSG_STR(MsgStr) MACRO_TOKENIZER2(ErrorScope_, MsgStr, TEXT(__FILE__), __LINE__)`
- L349 _macro_ `#define VERIFY_EGL_SCOPE() VERIFY_EGL_SCOPE_WITH_MSG_STR(ANSI_TO_TCHAR(__FUNCTION__))`
- L350 _macro_ `#define VERIFY_EGL_FUNC(Func, ...) { VERIFY_EGL_SCOPE_WITH_MSG_STR(TEXT(#Func)); Func(__VA_ARGS__); }`
- L352 _macro_ `#define VERIFY_EGL(...)`
- L353 _macro_ `#define VERIFY_EGL_SCOPE(...)`

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidJniBitmapRendererLegacy.h` (Private)


#### struct `UE::Jni::FBitmapRendererLegacy`  
`struct FBitmapRendererLegacy: Java::Lang::FObject`  
_L11-21_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L15 _public prototype_ `static void JNICALL nativeClearCachedAttributeState(JNIEnv* jenv, jobject thiz, jint PositionAttrib, jint TexCoordsAttrib);`
- L17 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeClearCachedAttributeState) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L23 _variable_ `template struct TInitialize<FBitmapRendererLegacy>;` (scope `UE::Jni`)

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidOpenGL.h` (Private)


#### struct `FAndroidOpenGL`  
`struct FAndroidOpenGL : public FOpenGLES`  
_L14-127_
- inherits: `FOpenGLES`
- L16 _public function_ `static FORCEINLINE bool HasHardwareHiddenSurfaceRemoval()`
- L18 _public prototype_ `static bool SupportsFramebufferSRGBEnable();`
- L20 _public function_ `static FORCEINLINE void DeleteSync(UGLsync Sync)`
- L28 _public function_ `static FORCEINLINE UGLsync FenceSync(GLenum Condition, GLbitfield Flags)`
- L33 _public function_ `static FORCEINLINE bool IsSync(UGLsync Sync)`
- L42 _public function_ `static FORCEINLINE EFenceResult ClientWaitSync(UGLsync Sync, GLbitfield Flags, GLuint64 Timeout)`
- L60 _public function_ `static FORCEINLINE bool SupportsTimestampQueries()` — Disable all queries except occlusion Query is a limited resource on Android and we better spent them all on occlusion
- L61 _public function_ `static FORCEINLINE bool SupportsDisjointTimeQueries()`
- L71 _public function_ `static FORCEINLINE bool SupportsImageExternal()`
- L73 _public function_ `static FORCEINLINE EImageExternalType GetImageExternalType()`
- L75 _public function_ `static FORCEINLINE GLint GetMaxComputeUniformComponents()`
- L76 _public function_ `static FORCEINLINE GLint GetFirstComputeUAVUnit()`
- L77 _public function_ `static FORCEINLINE GLint GetMaxComputeUAVUnits()`
- L78 _public function_ `static FORCEINLINE GLint GetFirstVertexUAVUnit()`
- L79 _public function_ `static FORCEINLINE GLint GetFirstPixelUAVUnit()`
- L80 _public function_ `static FORCEINLINE GLint GetMaxPixelUAVUnits()`
- L81 _public function_ `static FORCEINLINE GLint GetMaxCombinedUAVUnits()`
- L83 _public function_ `static FORCEINLINE void FrameBufferFetchBarrier()`
- L91 _public prototype_ `static void ProcessExtensions(const FString& ExtensionsString);`
- L92 _public prototype_ `static void SetupDefaultGLContextState(const FString& ExtensionsString);`
- L94 _public prototype_ `static bool RequiresAdrenoTilingModeHint();`
- L95 _public prototype_ `static void EnableAdrenoTilingModeHint(bool bEnable);`
- L96 _public member_ `static bool bRequiresAdrenoTilingHint;`
- L98 _public prototype_ `static bool ResetNonCoherentFramebufferFetch();`
- L99 _public prototype_ `static void DisableNonCoherentFramebufferFetch();`
- L100 _public member_ `static bool bDefaultStateNonCoherentFramebufferFetchEnabled;`
- L103 _public member_ `static int32 GLMajorVerion;` — supported OpenGL ES version queried from the system
- L104 _public member_ `static int32 GLMinorVersion;`
- L106 _public function_ `static FORCEINLINE GLuint GetMajorVersion()`
- L111 _public function_ `static FORCEINLINE GLuint GetMinorVersion()`
- L117 _public member_ `static bool bSupportsImageExternal;` — Whether device supports image external
- L120 _public member_ `static EImageExternalType ImageExternalType;` — Type of image external supported
- L123 _public prototype_ `static TArray<uint8> DispatchAndWaitForRemoteGLProgramCompile(FGraphicsPipelineStateInitializer::EPSOPrecacheCompileType PSOCompileType,const TArrayView<uint8> ContextData, const TArray<ANSICHAR>& VertexGlslCode, const TArray<ANSICHAR>& PixelGlslCode, const TArray<ANSICHAR>& ComputeGlslCode, FString& FailureMessageOUT);` — interface to remote GLES program compiler
- L124 _public prototype_ `static bool AreRemoteCompileServicesActive();`
- L125 _public prototype_ `static bool StartRemoteCompileServices(int NumServices);`
- L126 _public prototype_ `static void StopRemoteCompileServices();`

#### enum `FAndroidOpenGL::EImageExternalType`  
`enum class EImageExternalType : uint8`  
_L63-69_
- L65 _public enumerator_ `None`
- L66 _public enumerator_ `ImageExternal100`
- L67 _public enumerator_ `ImageExternal300`
- L68 _public enumerator_ `ImageExternalESSL300`

#### Free symbols / members of external scopes

- L129 _typedef_ `using FOpenGL = FAndroidOpenGL;`

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidOpenGLFramePacer.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidOpenGLFunctions.h` (Private)


#### Free symbols / members of external scopes

- L7 _typedef_ `typedef khronos_stime_nanoseconds_t EGLnsecsANDROID;`
- L9 _typedef_ `typedef GLboolean(GL_APIENTRYP PFNeglPresentationTimeANDROID) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID time);`
- L10 _typedef_ `typedef GLboolean(GL_APIENTRYP PFNeglGetNextFrameIdANDROID) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR* frameId);`
- L11 _typedef_ `typedef GLboolean(GL_APIENTRYP PFNeglGetCompositorTimingANDROID) (EGLDisplay dpy, EGLSurface surface, EGLint numTimestamps, const EGLint* names, EGLnsecsANDROID* values);`
- L12 _typedef_ `typedef GLboolean(GL_APIENTRYP PFNeglGetFrameTimestampsANDROID) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR frameId, EGLint numTimestamps, const EGLint* timestamps, EGLnsecsANDROID* values);`
- L13 _typedef_ `typedef GLboolean(GL_APIENTRYP PFNeglQueryTimestampSupportedANDROID) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);`
- L15 _typedef_ `typedef EGLClientBuffer(GL_APIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (const struct AHardwareBuffer* buffer);`
- L19 _externvar_ `extern PFNEGLGETSYSTEMTIMENVPROC eglGetSystemTimeNV_p;`
- L20 _externvar_ `extern PFNEGLCREATESYNCKHRPROC eglCreateSyncKHR_p;`
- L21 _externvar_ `extern PFNEGLDESTROYSYNCKHRPROC eglDestroySyncKHR_p;`
- L22 _externvar_ `extern PFNEGLCLIENTWAITSYNCKHRPROC eglClientWaitSyncKHR_p;`
- L23 _externvar_ `extern PFNEGLGETSYNCATTRIBKHRPROC eglGetSyncAttribKHR_p;`
- L25 _externvar_ `extern PFNeglPresentationTimeANDROID eglPresentationTimeANDROID_p;`
- L26 _externvar_ `extern PFNeglGetNextFrameIdANDROID eglGetNextFrameIdANDROID_p;`
- L27 _externvar_ `extern PFNeglGetCompositorTimingANDROID eglGetCompositorTimingANDROID_p;`
- L28 _externvar_ `extern PFNeglGetFrameTimestampsANDROID eglGetFrameTimestampsANDROID_p;`
- L29 _externvar_ `extern PFNeglQueryTimestampSupportedANDROID eglQueryTimestampSupportedANDROID_p;`
- L30 _externvar_ `extern PFNeglQueryTimestampSupportedANDROID eglGetCompositorTimingSupportedANDROID_p;`
- L31 _externvar_ `extern PFNeglQueryTimestampSupportedANDROID eglGetFrameTimestampsSupportedANDROID_p;`
- L33 _externvar_ `extern PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC eglGetNativeClientBufferANDROID_p;`
- L34 _externvar_ `extern PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR_p;`
- L35 _externvar_ `extern PFNEGLDESTROYIMAGEKHRPROC eglDestroyImageKHR_p;`
- L36 _externvar_ `extern PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES_p;`
- L39 _namespace_ `namespace GLFuncPointers`
- L42 _externvar_ `extern PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC glFramebufferFetchBarrierQCOM;` (scope `GLFuncPointers`) — GL_QCOM_shader_framebuffer_fetch_noncoherent
- L46 _typedef_ `typedef void (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);` — FIXME: include gl32.h
- L48 _namespace_ `namespace GLFuncPointers`
- L51 _externvar_ `extern PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC glFramebufferTexture2DMultisampleEXT;` (scope `GLFuncPointers`) — GL_EXT_multisampled_render_to_texture
- L52 _externvar_ `extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glRenderbufferStorageMultisampleEXT;` (scope `GLFuncPointers`)
- L55 _externvar_ `extern PFNGLPUSHGROUPMARKEREXTPROC glPushGroupMarkerEXT;` (scope `GLFuncPointers`) — GL_EXT_debug_marker
- L56 _externvar_ `extern PFNGLPOPGROUPMARKEREXTPROC glPopGroupMarkerEXT;` (scope `GLFuncPointers`)
- L59 _externvar_ `extern PFNGLLABELOBJECTEXTPROC glLabelObjectEXT;` (scope `GLFuncPointers`) — GL_EXT_debug_label
- L60 _externvar_ `extern PFNGLGETOBJECTLABELEXTPROC glGetObjectLabelEXT;` (scope `GLFuncPointers`)
- L62 _externvar_ `extern PFNGLBUFFERSTORAGEEXTPROC glBufferStorageEXT;` (scope `GLFuncPointers`) — GL_EXT_buffer_storage
- L64 _externvar_ `extern PFNGLDEBUGMESSAGECONTROLKHRPROC glDebugMessageControlKHR;` (scope `GLFuncPointers`)
- L65 _externvar_ `extern PFNGLDEBUGMESSAGEINSERTKHRPROC glDebugMessageInsertKHR;` (scope `GLFuncPointers`)
- L66 _externvar_ `extern PFNGLDEBUGMESSAGECALLBACKKHRPROC glDebugMessageCallbackKHR;` (scope `GLFuncPointers`)
- L67 _externvar_ `extern PFNGLGETDEBUGMESSAGELOGKHRPROC glDebugMessageLogKHR;` (scope `GLFuncPointers`)
- L68 _externvar_ `extern PFNGLGETPOINTERVKHRPROC glGetPointervKHR;` (scope `GLFuncPointers`)
- L69 _externvar_ `extern PFNGLPUSHDEBUGGROUPKHRPROC glPushDebugGroupKHR;` (scope `GLFuncPointers`)
- L70 _externvar_ `extern PFNGLPOPDEBUGGROUPKHRPROC glPopDebugGroupKHR;` (scope `GLFuncPointers`)
- L71 _externvar_ `extern PFNGLOBJECTLABELKHRPROC glObjectLabelKHR;` (scope `GLFuncPointers`)
- L72 _externvar_ `extern PFNGLGETOBJECTLABELKHRPROC glGetObjectLabelKHR;` (scope `GLFuncPointers`)
- L73 _externvar_ `extern PFNGLOBJECTPTRLABELKHRPROC glObjectPtrLabelKHR;` (scope `GLFuncPointers`)
- L74 _externvar_ `extern PFNGLGETOBJECTPTRLABELKHRPROC glGetObjectPtrLabelKHR;` (scope `GLFuncPointers`)
- L77 _externvar_ `extern PFNGLQUERYCOUNTEREXTPROC glQueryCounterEXT;` (scope `GLFuncPointers`) — GL_EXT_disjoint_timer_query
- L78 _externvar_ `extern PFNGLGETQUERYOBJECTUI64VEXTPROC glGetQueryObjectui64vEXT;` (scope `GLFuncPointers`)
- L81 _externvar_ `extern PFNGLTEXBUFFEREXTPROC glTexBufferEXT;` (scope `GLFuncPointers`) — ES 3.2
- L82 _externvar_ `extern PFNGLTEXBUFFERRANGEEXTPROC glTexBufferRangeEXT;` (scope `GLFuncPointers`)
- L83 _externvar_ `extern PFNGLCOPYIMAGESUBDATAEXTPROC glCopyImageSubData;` (scope `GLFuncPointers`)
- L84 _externvar_ `extern PFNGLENABLEIEXTPROC glEnableiEXT;` (scope `GLFuncPointers`)
- L85 _externvar_ `extern PFNGLDISABLEIEXTPROC glDisableiEXT;` (scope `GLFuncPointers`)
- L86 _externvar_ `extern PFNGLBLENDEQUATIONIEXTPROC glBlendEquationiEXT;` (scope `GLFuncPointers`)
- L87 _externvar_ `extern PFNGLBLENDEQUATIONSEPARATEIEXTPROC glBlendEquationSeparateiEXT;` (scope `GLFuncPointers`)
- L88 _externvar_ `extern PFNGLBLENDFUNCIEXTPROC glBlendFunciEXT;` (scope `GLFuncPointers`)
- L89 _externvar_ `extern PFNGLBLENDFUNCSEPARATEIEXTPROC glBlendFuncSeparateiEXT;` (scope `GLFuncPointers`)
- L90 _externvar_ `extern PFNGLCOLORMASKIEXTPROC glColorMaskiEXT;` (scope `GLFuncPointers`)
- L91 _externvar_ `extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;` (scope `GLFuncPointers`)
- L94 _externvar_ `extern PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC glFramebufferTextureMultiviewOVR;` (scope `GLFuncPointers`) — Mobile multi-view
- L95 _externvar_ `extern PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC glFramebufferTextureMultisampleMultiviewOVR;` (scope `GLFuncPointers`)

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidOpenGLPlatform.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UGL_PLATFORM_SUPPORTS_GLES 1`
- L8 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL3 0`
- L9 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL4 0`
- L11 _typedef_ `typedef GLsync UGLsync;`
- L12 _macro_ `#define GLdouble GLfloat`
- L13 _typedef_ `typedef khronos_int64_t GLint64;`
- L14 _typedef_ `typedef khronos_uint64_t GLuint64;`
- L15 _macro_ `#define GL_CLAMP GL_CLAMP_TO_EDGE`
- L17 _macro_ `#define EGL_TIMESTAMPS_ANDROID 0x3430`
- L18 _macro_ `#define EGL_COMPOSITE_DEADLINE_ANDROID 0x3431`
- L19 _macro_ `#define EGL_COMPOSITE_INTERVAL_ANDROID 0x3432`
- L20 _macro_ `#define EGL_COMPOSITE_TO_PRESENT_LATENCY_ANDROID 0x3433`
- L21 _macro_ `#define EGL_REQUESTED_PRESENT_TIME_ANDROID 0x3434`
- L22 _macro_ `#define EGL_RENDERING_COMPLETE_TIME_ANDROID 0x3435`
- L23 _macro_ `#define EGL_COMPOSITION_LATCH_TIME_ANDROID 0x3436`
- L24 _macro_ `#define EGL_FIRST_COMPOSITION_START_TIME_ANDROID 0x3437`
- L25 _macro_ `#define EGL_LAST_COMPOSITION_START_TIME_ANDROID 0x3438`
- L26 _macro_ `#define EGL_FIRST_COMPOSITION_GPU_FINISHED_TIME_ANDROID 0x3439`
- L27 _macro_ `#define EGL_DISPLAY_PRESENT_TIME_ANDROID 0x343A`
- L28 _macro_ `#define EGL_DEQUEUE_READY_TIME_ANDROID 0x343B`
- L29 _macro_ `#define EGL_READS_DONE_TIME_ANDROID 0x343C`
- L36 _macro_ `#define UGL_DRAW_FRAMEBUFFER GL_DRAW_FRAMEBUFFER_NV` — Unreal tokens that maps to different OpenGL tokens by platform.
- L37 _macro_ `#define UGL_READ_FRAMEBUFFER GL_READ_FRAMEBUFFER_NV`
- L38 _macro_ `#define UGL_ABGR8 GL_UNSIGNED_BYTE`
- L39 _macro_ `#define UGL_ANY_SAMPLES_PASSED GL_ANY_SAMPLES_PASSED`
- L40 _macro_ `#define UGL_SAMPLES_PASSED GL_SAMPLES_PASSED`
- L41 _macro_ `#define UGL_TIME_ELAPSED GL_TIME_ELAPSED_EXT`
- L42 _macro_ `#define UGL_CLAMP_TO_BORDER GL_CLAMP_TO_EDGE`
- L46 _macro_ `#define GL_FILL 0x1B02`
- L49 _macro_ `#define GL_GEOMETRY_SHADER 0x8DD9`
- L52 _macro_ `#define GL_SAMPLER_1D 0x8B5D`
- L55 _macro_ `#define GL_SAMPLER_1D_SHADOW 0x8B61`
- L58 _macro_ `#define GL_DOUBLE 0x140A`
- L61 _macro_ `#define GL_BGRA GL_BGRA_EXT`
- L64 _macro_ `#define GL_TEXTURE_BUFFER 0x8C2A`
- L68 _macro_ `#define GL_RGBA16 GL_RGBA16_EXT` — GL_EXT_texture_norm16
- L72 _macro_ `#define GL_R16 GL_R16_EXT` — GL_EXT_texture_norm16
- L75 _macro_ `#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F`
- L78 _macro_ `#define GL_POLYGON_OFFSET_LINE 0x2A02`
- L81 _macro_ `#define GL_POLYGON_OFFSET_POINT 0x2A01`
- L84 _macro_ `#define GL_TEXTURE_LOD_BIAS 0x8501`
- L87 _macro_ `#define GL_FRAMEBUFFER_SRGB 0x8DB9`
- L90 _macro_ `#define GL_SAMPLES_PASSED 0x8914`
- L93 _macro_ `#define GL_POINT 0x1B00`
- L96 _macro_ `#define GL_LINE 0x1B01`
- L99 _macro_ `#define GL_TEXTURE_1D 0x0DE0`
- L102 _macro_ `#define GL_TEXTURE_1D_ARRAY 0x8C18`
- L105 _macro_ `#define GL_TEXTURE_RECTANGLE 0x84F5`
- L108 _macro_ `#define GL_MAX_TEXTURE_BUFFER_SIZE 0x8C2B`
- L111 _macro_ `#define GL_DEPTH_CLAMP 0x864F`
- L115 _macro_ `#define GL_GEOMETRY_SHADER_BIT 0x00000000` — For the shader stage bits that don't exist just use 0
- L116 _macro_ `#define GL_TESS_CONTROL_SHADER_BIT 0x00000000`
- L117 _macro_ `#define GL_TESS_EVALUATION_SHADER_BIT 0x00000000`
- L121 _macro_ `#define GL_DEBUG_SOURCE_OTHER_ARB GL_DEBUG_SOURCE_OTHER_KHR`
- L122 _macro_ `#define GL_DEBUG_SOURCE_API_ARB GL_DEBUG_SOURCE_API_KHR`
- L123 _macro_ `#define GL_DEBUG_TYPE_ERROR_ARB GL_DEBUG_TYPE_ERROR_KHR`
- L124 _macro_ `#define GL_DEBUG_TYPE_OTHER_ARB GL_DEBUG_TYPE_OTHER_KHR`
- L125 _macro_ `#define GL_DEBUG_TYPE_MARKER GL_DEBUG_TYPE_MARKER_KHR`
- L126 _macro_ `#define GL_DEBUG_TYPE_PUSH_GROUP GL_DEBUG_TYPE_PUSH_GROUP_KHR`
- L127 _macro_ `#define GL_DEBUG_TYPE_POP_GROUP GL_DEBUG_TYPE_POP_GROUP_KHR`
- L128 _macro_ `#define GL_DEBUG_SEVERITY_HIGH_ARB GL_DEBUG_SEVERITY_HIGH_KHR`
- L129 _macro_ `#define GL_DEBUG_SEVERITY_LOW_ARB GL_DEBUG_SEVERITY_LOW_KHR`
- L130 _macro_ `#define GL_DEBUG_SEVERITY_NOTIFICATION GL_DEBUG_SEVERITY_NOTIFICATION_KHR`

### `Source/Runtime/OpenGLDrv/Private/Android/AndroidOpenGLPrivate.h` (Private)


#### class `FAndroidGPUInfo`  
`class FAndroidGPUInfo`  
_L20-49_
- L23 _public prototype_ `static FAndroidGPUInfo& Get();`
- L25 _public member_ `FString GLVersion;`
- L26 _public member_ `FString VendorName;`
- L27 _public member_ `bool bSupportsFloatingPointRenderTargets;`
- L28 _public member_ `bool bSupportsFrameBufferFetch;`
- L29 _public member_ `TArray<FString> TargetPlatformNames;`
- L31 _public function_ `void RemoveTargetPlatform(FString PlatformName)`
- L37 _public function_ `FString& GetGPUFamily()` — computing GPU family needs regex access, which might not be available early in init
- L45 _private member_ `FString GPUFamily;`
- L47 _private prototype_ `FAndroidGPUInfo();`
- L48 _private prototype_ `void ReadGPUFamily();`

#### Free symbols / members of external scopes

- L14 _externvar_ `extern bool GAndroidGPUInfoReady;`
- L17 _prototype_ `extern bool AndroidThunkCpp_IsXRImmersiveHMDApplication();` — call out to JNI to see if the application was packaged for XRImmersiveHMD
- L18 _prototype_ `extern bool ShouldUseGPUFencesToLimitLatency();`

### `Source/Runtime/OpenGLDrv/Private/Linux/LinuxOpenGL.h` (Private)


#### struct `FLinuxOpenGL`  
`struct FLinuxOpenGL : public FOpenGL4`  
_L10-100_
- inherits: `FOpenGL4`
- L12 _public function_ `static FORCEINLINE void InitDebugContext()`
- L17 _public function_ `static FORCEINLINE void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)`
- L25 _public function_ `static FORCEINLINE void PushGroupMarker(const ANSICHAR* Name)`
- L33 _public function_ `static FORCEINLINE void PopGroupMarker()`
- L41 _public function_ `static FORCEINLINE bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, ETextureCreateFlags Flags)`
- L52 _public function_ `static FORCEINLINE void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type)`
- L80 _public function_ `static FORCEINLINE void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth)`
- L85 _public function_ `static void ProcessExtensions(const FString& ExtensionsString)`

#### Free symbols / members of external scopes

- L102 _typedef_ `using FOpenGL = FLinuxOpenGL;`

### `Source/Runtime/OpenGLDrv/Private/Linux/LinuxOpenGLFunctions.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define ENUM_GL_ENTRYPOINTS(EnumMacro) \` — List all OpenGL entry points used by Unreal.
- L288 _macro_ `#define ENUM_GL_ENTRYPOINTS_OPTIONAL(EnumMacro) \`
- L349 _macro_ `#define ENUM_GL_ENTRYPOINTS_ALL(EnumMacro) \` — List of all OpenGL entry points.
- L354 _macro_ `#define DECLARE_GL_ENTRYPOINTS(Type,Func) extern Type OPENGLDRV_API Func;` — Declare all GL functions.
- L358 _namespace_ `namespace GLFuncPointers`
- L360 _prototype_ `ENUM_GL_ENTRYPOINTS_ALL(DECLARE_GL_ENTRYPOINTS);` (scope `GLFuncPointers`)

### `Source/Runtime/OpenGLDrv/Private/Linux/LinuxOpenGLPlatform.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UGL_PLATFORM_SUPPORTS_GLES 0`
- L8 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL3 1`
- L9 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL4 1`
- L12 _macro_ `#define UGL_DRAW_FRAMEBUFFER GL_DRAW_FRAMEBUFFER` — Unreal tokens that maps to different OpenGL tokens by platform.
- L13 _macro_ `#define UGL_READ_FRAMEBUFFER GL_READ_FRAMEBUFFER`
- L14 _macro_ `#define UGL_ABGR8 GL_UNSIGNED_INT_8_8_8_8_REV`
- L15 _macro_ `#define UGL_ANY_SAMPLES_PASSED GL_ANY_SAMPLES_PASSED`
- L16 _macro_ `#define UGL_SAMPLES_PASSED GL_SAMPLES_PASSED`
- L17 _macro_ `#define UGL_TIME_ELAPSED GL_TIME_ELAPSED`
- L18 _macro_ `#define UGL_CLAMP_TO_BORDER GL_CLAMP_TO_BORDER`

### `Source/Runtime/OpenGLDrv/Private/OpenGL.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/OpenGLDrv/Private/OpenGL3.h` (Private)


#### struct `FOpenGL3`  
`struct FOpenGL3 : public FOpenGLBase`  
_L23-641_
- inherits: `FOpenGLBase`
- L25 _public function_ `static FORCEINLINE bool IsDebugContent()`
- L27 _public function_ `static FORCEINLINE bool SupportsTimestampQueries()`
- L28 _public function_ `static FORCEINLINE bool SupportsSeamlessCubeMap()`
- L29 _public function_ `static FORCEINLINE bool SupportsVolumeTextureRendering()`
- L30 _public function_ `static FORCEINLINE bool AmdWorkaround()`
- L31 _public function_ `static FORCEINLINE bool SupportsBufferStorage()`
- L34 _public function_ `static FORCEINLINE void QueryTimestampCounter(GLuint QueryID)` — Optional
- L39 _public function_ `static FORCEINLINE void BeginQuery(GLenum QueryType, GLuint QueryId)`
- L44 _public function_ `static FORCEINLINE void EndQuery(GLenum QueryType)`
- L49 _public function_ `static FORCEINLINE void GetQueryObject(GLuint QueryId, EQueryMode QueryMode, GLuint64* OutResult)`
- L57 _public function_ `static FORCEINLINE void ReadBuffer(GLenum Mode)`
- L62 _public function_ `static FORCEINLINE void DrawBuffer(GLenum Mode)`
- L67 _public function_ `static FORCEINLINE void DeleteSync(UGLsync Sync)`
- L72 _public function_ `static FORCEINLINE UGLsync FenceSync(GLenum Condition, GLbitfield Flags)`
- L77 _public function_ `static FORCEINLINE bool IsSync(UGLsync Sync)`
- L82 _public function_ `static FORCEINLINE EFenceResult ClientWaitSync(UGLsync Sync, GLbitfield Flags, GLuint64 Timeout)`
- L94 _public function_ `static FORCEINLINE void GenSamplers(GLsizei Count, GLuint* Samplers)`
- L99 _public function_ `static FORCEINLINE void DeleteSamplers(GLsizei Count, GLuint* Samplers)`
- L104 _public function_ `static FORCEINLINE void SetSamplerParameter(GLuint Sampler, GLenum Parameter, GLint Value)`
- L109 _public function_ `static FORCEINLINE void BindSampler(GLuint Unit, GLuint Sampler)`
- L114 _public function_ `static FORCEINLINE void PolygonMode(GLenum Face, GLenum Mode)`
- L119 _public function_ `static FORCEINLINE void VertexAttribDivisor(GLuint Index, GLuint Divisor)`
- L125 _public function_ `static FORCEINLINE void* MapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize, EResourceLockMode LockMode)` — Required
- L156 _public function_ `static FORCEINLINE void UnmapBuffer(GLenum Type)`
- L161 _public function_ `static FORCEINLINE void UnmapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize)`
- L166 _public function_ `static FORCEINLINE void GenQueries(GLsizei NumQueries, GLuint* QueryIDs)`
- L171 _public function_ `static FORCEINLINE void DeleteQueries(GLsizei NumQueries, const GLuint* QueryIDs )`
- L176 _public function_ `static FORCEINLINE void GetQueryObject(GLuint QueryId, EQueryMode QueryMode, GLuint* OutResult)`
- L182 _public function_ `static FORCEINLINE void BindBufferBase(GLenum Target, GLuint Index, GLuint Buffer)`
- L187 _public function_ `static FORCEINLINE void BindBufferRange(GLenum Target, GLuint Index, GLuint Buffer, GLintptr Offset, GLsizeiptr Size)`
- L192 _public function_ `static FORCEINLINE GLuint GetUniformBlockIndex(GLuint Program, const GLchar* UniformBlockName)`
- L197 _public function_ `static FORCEINLINE void UniformBlockBinding(GLuint Program, GLuint UniformBlockIndex, GLuint UniformBlockBinding)`
- L202 _public function_ `static FORCEINLINE void BindFragDataLocation(GLuint Program, GLuint Color, const GLchar* Name)`
- L207 _public function_ `static FORCEINLINE void TexParameter(GLenum Target, GLenum Parameter, GLint Value)`
- L212 _public function_ `static FORCEINLINE void FramebufferTexture(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level)`
- L217 _public function_ `static FORCEINLINE void FramebufferTexture3D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint ZOffset)`
- L222 _public function_ `static FORCEINLINE void FramebufferTextureLayer(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint Layer)`
- L227 _public function_ `static FORCEINLINE void Uniform4uiv(GLint Location, GLsizei Count, const GLuint* Value)`
- L232 _public function_ `static FORCEINLINE void BlitFramebuffer(GLint SrcX0, GLint SrcY0, GLint SrcX1, GLint SrcY1, GLint DstX0, GLint DstY0, GLint DstX1, GLint DstY1, GLbitfield Mask, GLenum Filter)`
- L237 _public function_ `static FORCEINLINE void DrawBuffers(GLsizei NumBuffers, const GLenum* Buffers)`
- L242 _public function_ `static FORCEINLINE void DepthRange(GLdouble Near, GLdouble Far)`
- L247 _public function_ `static FORCEINLINE void EnableIndexed(GLenum Parameter, GLuint Index)`
- L252 _public function_ `static FORCEINLINE void DisableIndexed(GLenum Parameter, GLuint Index)`
- L257 _public function_ `static FORCEINLINE void ColorMaskIndexed(GLuint Index, GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha)`
- L262 _public function_ `static FORCEINLINE void VertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid* Pointer)`
- L267 _public function_ `static FORCEINLINE void VertexAttribIPointer(GLuint Index, GLint Size, GLenum Type, GLsizei Stride, const GLvoid* Pointer)`
- L272 _public function_ `static FORCEINLINE void VertexAttrib4Nsv(GLuint AttributeIndex, const GLshort* Values)`
- L277 _public function_ `static FORCEINLINE void VertexAttrib4sv(GLuint AttributeIndex, const GLshort* Values)`
- L282 _public function_ `static FORCEINLINE void VertexAttribI4sv(GLuint AttributeIndex, const GLshort* Values)`
- L287 _public function_ `static FORCEINLINE void VertexAttribI4usv(GLuint AttributeIndex, const GLushort* Values)`
- L292 _public function_ `static FORCEINLINE void VertexAttrib4Nubv(GLuint AttributeIndex, const GLubyte* Values)`
- L297 _public function_ `static FORCEINLINE void VertexAttrib4ubv(GLuint AttributeIndex, const GLubyte* Values)`
- L302 _public function_ `static FORCEINLINE void VertexAttribI4ubv(GLuint AttributeIndex, const GLubyte* Values)`
- L307 _public function_ `static FORCEINLINE void VertexAttrib4Nbv(GLuint AttributeIndex, const GLbyte* Values)`
- L312 _public function_ `static FORCEINLINE void VertexAttrib4bv(GLuint AttributeIndex, const GLbyte* Values)`
- L317 _public function_ `static FORCEINLINE void VertexAttribI4bv(GLuint AttributeIndex, const GLbyte* Values)`
- L322 _public function_ `static FORCEINLINE void VertexAttrib4dv(GLuint AttributeIndex, const GLdouble* Values)`
- L327 _public function_ `static FORCEINLINE void VertexAttribI4iv(GLuint AttributeIndex, const GLint* Values)`
- L332 _public function_ `static FORCEINLINE void VertexAttribI4uiv(GLuint AttributeIndex, const GLuint* Values)`
- L337 _public function_ `static FORCEINLINE void DrawArraysInstanced(GLenum Mode, GLint First, GLsizei Count, GLsizei InstanceCount)`
- L342 _public function_ `static FORCEINLINE void DrawElementsInstanced(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid* Indices, GLsizei InstanceCount)`
- L347 _public function_ `static FORCEINLINE void DrawRangeElements(GLenum Mode, GLuint Start, GLuint End, GLsizei Count, GLenum Type, const GLvoid* Indices)`
- L352 _public function_ `static FORCEINLINE void ClearBufferfv(GLenum Buffer, GLint DrawBufferIndex, const GLfloat* Value)`
- L357 _public function_ `static FORCEINLINE void ClearBufferfi(GLenum Buffer, GLint DrawBufferIndex, GLfloat Depth, GLint Stencil)`
- L362 _public function_ `static FORCEINLINE void ClearBufferiv(GLenum Buffer, GLint DrawBufferIndex, const GLint* Value)`
- L367 _public function_ `static FORCEINLINE void ClearDepth(GLdouble Depth)`
- L372 _public function_ `static FORCEINLINE void TexImage3D(GLenum Target, GLint Level, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLenum Format, GLenum Type, const GLvoid* PixelData)`
- L377 _public function_ `static FORCEINLINE void CompressedTexImage3D(GLenum Target, GLint Level, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLsizei ImageSize, const GLvoid* PixelData)`
- L382 _public function_ `static FORCEINLINE void CompressedTexSubImage2D(GLenum Target, GLint Level, GLsizei Width, GLsizei Height, GLenum Format, GLsizei ImageSize, const GLvoid* PixelData)`
- L387 _public function_ `static FORCEINLINE void TexImage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations)`
- L392 _public function_ `static FORCEINLINE void TexBuffer(GLenum Target, GLenum InternalFormat, GLuint Buffer)`
- L397 _public function_ `static FORCEINLINE void TexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type, const GLvoid* PixelData)`
- L402 _public function_ `static FORCEINLINE void CopyTexSubImage1D(GLenum Target, GLint Level, GLint XOffset, GLint X, GLint Y, GLsizei Width)`
- L407 _public function_ `static FORCEINLINE void CopyTexSubImage2D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height)`
- L412 _public function_ `static FORCEINLINE void CopyTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height)`
- L417 _public function_ `static FORCEINLINE void GetCompressedTexImage(GLenum Target, GLint Level, GLvoid* OutImageData)`
- L422 _public function_ `static FORCEINLINE void GetTexImage(GLenum Target, GLint Level, GLenum Format, GLenum Type, GLvoid* OutPixelData)`
- L427 _public function_ `static FORCEINLINE void CopyBufferSubData(GLenum ReadTarget, GLenum WriteTarget, GLintptr ReadOffset, GLintptr WriteOffset, GLsizeiptr Size)`
- L432 _public function_ `static FORCEINLINE GLuint CreateShader(GLenum Type)`
- L451 _public function_ `static FORCEINLINE GLuint CreateProgram()`
- L469 _public function_ `static FORCEINLINE void GenBuffers( GLsizei n, GLuint *buffers)`
- L503 _public function_ `static FORCEINLINE void GenTextures( GLsizei n, GLuint *textures)`
- L537 _public function_ `static FORCEINLINE void CompressedTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLsizei ImageSize, const GLvoid* PixelData)`
- L542 _public function_ `static FORCEINLINE void GenerateMipmap( GLenum Target )`
- L547 _public function_ `static FORCEINLINE const ANSICHAR* GetStringIndexed(GLenum Name, GLuint Index)`
- L552 _public function_ `static FORCEINLINE GLuint GetMajorVersion()`
- L559 _public function_ `static FORCEINLINE GLuint GetMinorVersion()`
- L565 _public function_ `static FORCEINLINE void ProgramParameter(GLuint Program, GLenum PName, GLint Value)`
- L570 _public function_ `static FORCEINLINE void ProgramUniform1i(GLuint Program, GLint Location, GLint V0)`
- L574 _public function_ `static FORCEINLINE void ProgramUniform4iv(GLuint Program, GLint Location, GLsizei Count, const GLint *Value)`
- L578 _public function_ `static FORCEINLINE void ProgramUniform4fv(GLuint Program, GLint Location, GLsizei Count, const GLfloat *Value)`
- L582 _public function_ `static FORCEINLINE void ProgramUniform4uiv(GLuint Program, GLint Location, GLsizei Count, const GLuint *Value)`
- L586 _public function_ `static FORCEINLINE void GetProgramPipelineiv(GLuint Pipeline, GLenum Pname, GLint* Params)`
- L590 _public function_ `static FORCEINLINE void ValidateProgramPipeline(GLuint Pipeline)`
- L594 _public function_ `static FORCEINLINE void GetProgramPipelineInfoLog(GLuint Pipeline, GLsizei BufSize, GLsizei* Length, GLchar* InfoLog)`
- L598 _public function_ `static FORCEINLINE bool IsProgramPipeline(GLuint Pipeline)`
- L603 _public function_ `static FORCEINLINE ERHIFeatureLevel::Type GetFeatureLevel()`
- L608 _public function_ `static FORCEINLINE EShaderPlatform GetShaderPlatform()`
- L613 _public function_ `static FORCEINLINE FString GetAdapterName()`
- L618 _public prototype_ `static FPlatformOpenGLDevice* CreateDevice() UGL_REQUIRED(NULL) static FPlatformOpenGLContext* CreateContext( FPlatformOpenGLDevice* Device, void* WindowHandle ) UGL_REQUIRED(NULL) static void ProcessQueryGLInt();`
- L622 _public prototype_ `static void ProcessExtensions(const FString& ExtensionsString);`
- L624 _public function_ `static FORCEINLINE int32 GetReadHalfFloatPixelsEnum()`
- L626 _public function_ `static FORCEINLINE bool IsAndroidGLESCompatibilityModeEnabled()`
- L628 _public function_ `static GLenum GetPlatfrom5551Format()`
- L630 _protected member_ `static GLsizei NextTextureName;`
- L631 _protected member_ `static GLuint TextureNamesCache[OPENGL_NAME_CACHE_SIZE];`
- L632 _protected member_ `static GLsizei NextBufferName;`
- L633 _protected member_ `static GLuint BufferNamesCache[OPENGL_NAME_CACHE_SIZE];`
- L634 _protected member_ `static GLsizei NextPipelineName;`
- L635 _protected member_ `static GLuint PipelineNamesCache[OPENGL_NAME_CACHE_SIZE];`
- L637 _protected member_ `static GLint TimestampQueryBits;`
- L639 _protected member_ `static bool bDebugContext;`
- L640 _protected member_ `static bool bAndroidGLESCompatibilityMode;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define USE_OPENGL_NAME_CACHE 1`
- L21 _macro_ `#define OPENGL_NAME_CACHE_SIZE 1024`

### `Source/Runtime/OpenGLDrv/Private/OpenGL4.h` (Private)


#### struct `FOpenGL4`  
`struct FOpenGL4 : public FOpenGL3`  
_L17-125_
- inherits: `FOpenGL3`
- L19 _public function_ `static FORCEINLINE bool SupportsDrawIndirect()`
- L24 _public function_ `static FORCEINLINE void BlendFuncSeparatei(GLuint Buf, GLenum SrcRGB, GLenum DstRGB, GLenum SrcAlpha, GLenum DstAlpha)` — Required
- L28 _public function_ `static FORCEINLINE void BlendEquationSeparatei(GLuint Buf, GLenum ModeRGB, GLenum ModeAlpha)`
- L32 _public function_ `static FORCEINLINE void BlendFunci(GLuint Buf, GLenum Src, GLenum Dst)`
- L36 _public function_ `static FORCEINLINE void BlendEquationi(GLuint Buf, GLenum Mode)`
- L40 _public function_ `static FORCEINLINE void PatchParameteri(GLenum Pname, GLint Value)`
- L44 _public function_ `static FORCEINLINE void BindImageTexture(GLuint Unit, GLuint Texture, GLint Level, GLboolean Layered, GLint Layer, GLenum Access, GLenum Format)`
- L48 _public function_ `static FORCEINLINE void DispatchCompute(GLuint NumGroupsX, GLuint NumGroupsY, GLuint NumGroupsZ)`
- L52 _public function_ `static FORCEINLINE void DispatchComputeIndirect(GLintptr Offset)`
- L56 _public function_ `static FORCEINLINE void MemoryBarrier(GLbitfield Barriers)`
- L60 _public function_ `static FORCEINLINE void DrawArraysIndirect (GLenum Mode, const void *Offset)`
- L64 _public function_ `static FORCEINLINE void DrawElementsIndirect (GLenum Mode, GLenum Type, const void *Offset)`
- L68 _public function_ `static FORCEINLINE void BindVertexBuffer(GLuint BindingIndex, GLuint Buffer, GLintptr Offset, GLsizei Stride)`
- L72 _public function_ `static FORCEINLINE void VertexAttribFormat(GLuint AttribIndex, GLint Size, GLenum Type, GLboolean Normalized, GLuint RelativeOffset)`
- L76 _public function_ `static FORCEINLINE void VertexAttribIFormat(GLuint AttribIndex, GLint Size, GLenum Type, GLuint RelativeOffset)`
- L80 _public function_ `static FORCEINLINE void VertexAttribBinding(GLuint AttribIndex, GLuint BindingIndex)`
- L84 _public function_ `static FORCEINLINE void VertexBindingDivisor(GLuint BindingIndex, GLuint Divisor)`
- L88 _public function_ `static FORCEINLINE void TexBufferRange(GLenum Target, GLenum InternalFormat, GLuint Buffer, GLintptr Offset, GLsizeiptr Size)`
- L92 _public function_ `static FORCEINLINE void TextureView(GLuint ViewName, GLenum ViewTarget, GLuint SrcName, GLenum InternalFormat, GLuint MinLevel, GLuint NumLevels, GLuint MinLayer, GLuint NumLayers)`
- L96 _public function_ `static FORCEINLINE void ClearBufferData(GLenum Target, GLenum InternalFormat, GLenum Format, GLenum Type, const uint32* Data)`
- L101 _public prototype_ `static void ProcessQueryGLInt();`
- L102 _public prototype_ `static void ProcessExtensions( const FString& ExtensionsString );`
- L104 _public function_ `static FORCEINLINE GLint GetMaxComputeUniformComponents()`
- L106 _public function_ `static FORCEINLINE GLint GetFirstComputeUAVUnit()`
- L107 _public function_ `static FORCEINLINE GLint GetMaxComputeUAVUnits()`
- L108 _public function_ `static FORCEINLINE GLint GetFirstVertexUAVUnit()`
- L109 _public function_ `static FORCEINLINE GLint GetFirstPixelUAVUnit()`
- L110 _public function_ `static FORCEINLINE GLint GetMaxPixelUAVUnits()`
- L111 _public function_ `static FORCEINLINE GLint GetMaxCombinedUAVUnits()`
- L113 _public prototype_ `static uint64 GetVideoMemorySize();`
- L115 _public function_ `static FORCEINLINE int32 GetReadHalfFloatPixelsEnum()`
- L118 _protected member_ `static GLint MaxComputeUniformComponents;`
- L120 _protected member_ `static GLint MaxCombinedUAVUnits;`
- L121 _protected member_ `static GLint MaxComputeUAVUnits;`
- L122 _protected member_ `static GLint MaxPixelUAVUnits;`
- L124 _protected member_ `static bool bSupportsGPUMemoryInfo;`

### `Source/Runtime/OpenGLDrv/Private/OpenGLBase.h` (Private)


#### class `FOpenGLBase`  
`class FOpenGLBase`  
_L37-377_
- desc: Base static class
- L64 _public prototype_ `static void ProcessQueryGLInt();`
- L65 _public prototype_ `static void ProcessExtensions(const FString& ExtensionsString);`
- L66 _public function_ `static void SetupDefaultGLContextState(const FString& ExtensionsString)`
- L68 _public function_ `static FORCEINLINE bool SupportsUniformBuffers()`
- L69 _public function_ `static FORCEINLINE bool SupportsStructuredBuffers()`
- L70 _public function_ `static FORCEINLINE bool SupportsTimestampQueries()`
- L71 _public function_ `static FORCEINLINE bool SupportsDisjointTimeQueries()`
- L72 _public function_ `static FORCEINLINE bool SupportsExactOcclusionQueries()`
- L73 _public function_ `static FORCEINLINE bool SupportsDepthStencilReadSurface()`
- L74 _public function_ `static FORCEINLINE bool SupportsFloatReadSurface()`
- L75 _public function_ `static FORCEINLINE bool SupportsWideMRT()`
- L76 _public function_ `static FORCEINLINE bool SupportsPolygonMode()`
- L77 _public function_ `static FORCEINLINE bool SupportsTexture3D()`
- L78 _public function_ `static FORCEINLINE bool SupportsMobileMultiView()`
- L79 _public function_ `static FORCEINLINE bool SupportsImageExternal()`
- L80 _public function_ `static FORCEINLINE bool SupportsTextureLODBias()`
- L81 _public function_ `static FORCEINLINE bool SupportsTextureCompare()`
- L82 _public function_ `static FORCEINLINE bool SupportsDrawIndexOffset()`
- L83 _public function_ `static FORCEINLINE bool SupportsDiscardFrameBuffer()`
- L84 _public function_ `static FORCEINLINE bool SupportsIndexedExtensions()`
- L85 _public function_ `static FORCEINLINE bool SupportsColorBufferFloat()`
- L86 _public function_ `static FORCEINLINE bool SupportsColorBufferHalfFloat()`
- L87 _public function_ `static FORCEINLINE bool SupportsVolumeTextureRendering()`
- L88 _public function_ `static FORCEINLINE bool SupportsShaderFramebufferFetch()`
- L89 _public function_ `static FORCEINLINE bool SupportsShaderFramebufferFetchProgrammableBlending()`
- L90 _public function_ `static FORCEINLINE bool SupportsShaderMRTFramebufferFetch()`
- L91 _public function_ `static FORCEINLINE bool SupportsShaderDepthStencilFetch()`
- L92 _public function_ `static FORCEINLINE bool SupportsPixelLocalStorage()`
- L93 _public function_ `static FORCEINLINE bool SupportsVertexArrayBGRA()`
- L94 _public function_ `static FORCEINLINE bool SupportsBGRA8888()`
- L95 _public function_ `static FORCEINLINE bool SupportsDXT()`
- L96 _public function_ `static FORCEINLINE bool SupportsASTC()`
- L97 _public function_ `static FORCEINLINE bool SupportsASTCHDR()`
- L98 _public function_ `static FORCEINLINE bool SupportsETC2()`
- L99 _public function_ `static FORCEINLINE bool SupportsFramebufferSRGBEnable()`
- L100 _public function_ `static FORCEINLINE bool SupportsFastBufferData()`
- L101 _public function_ `static FORCEINLINE bool SupportsTextureFilterAnisotropic()`
- L102 _public function_ `static FORCEINLINE bool SupportsSeparateAlphaBlend()`
- L103 _public function_ `static FORCEINLINE void EnableSupportsClipControl()`
- L104 _public function_ `static FORCEINLINE bool SupportsClipControl()`
- L105 _public function_ `static FORCEINLINE bool SupportsSeamlessCubeMap()`
- L106 _public function_ `static FORCEINLINE bool SupportsDrawIndirect()`
- L107 _public function_ `static FORCEINLINE bool SupportsBufferStorage()`
- L108 _public function_ `static FORCEINLINE bool SupportsDepthBoundsTest()`
- L109 _public function_ `static FORCEINLINE bool SupportsTextureRange()`
- L110 _public function_ `static FORCEINLINE bool HasHardwareHiddenSurfaceRemoval()`
- L111 _public function_ `static FORCEINLINE bool AmdWorkaround()`
- L112 _public function_ `static FORCEINLINE bool SupportsProgramBinary()`
- L113 _public function_ `static FORCEINLINE bool SupportsDepthClamp()`
- L115 _public function_ `static FORCEINLINE bool SupportsASTCDecodeMode()`
- L117 _public function_ `static FORCEINLINE GLenum GetDepthFormat()`
- L118 _public function_ `static FORCEINLINE GLenum GetShadowDepthFormat()`
- L120 _public function_ `static FORCEINLINE GLint GetMaxTextureImageUnits()`
- L121 _public function_ `static FORCEINLINE GLint GetMaxVertexTextureImageUnits()`
- L122 _public function_ `static FORCEINLINE GLint GetMaxGeometryTextureImageUnits()`
- L123 _public function_ `static FORCEINLINE GLint GetMaxComputeTextureImageUnits()`
- L124 _public function_ `static FORCEINLINE GLint GetMaxCombinedTextureImageUnits()`
- L125 _public function_ `static FORCEINLINE GLint GetTextureBufferAlignment()`
- L129 _public function_ `static FORCEINLINE GLint GetFirstPixelTextureUnit()` — Indices per unit are set in this order [Pixel, Vertex, Geometry]
- L130 _public function_ `static FORCEINLINE GLint GetFirstVertexTextureUnit()`
- L131 _public function_ `static FORCEINLINE GLint GetFirstGeometryTextureUnit()`
- L133 _public function_ `static FORCEINLINE GLint GetFirstComputeTextureUnit()`
- L136 _public function_ `static FORCEINLINE GLint GetFirstComputeUAVUnit()` — Image load/store units
- L137 _public function_ `static FORCEINLINE GLint GetMaxComputeUAVUnits()`
- L138 _public function_ `static FORCEINLINE GLint GetFirstVertexUAVUnit()`
- L139 _public function_ `static FORCEINLINE GLint GetFirstPixelUAVUnit()`
- L140 _public function_ `static FORCEINLINE GLint GetMaxPixelUAVUnits()`
- L141 _public function_ `static FORCEINLINE GLint GetMaxCombinedUAVUnits()`
- L143 _public function_ `static FORCEINLINE GLint GetMaxVaryingVectors()`
- L144 _public function_ `static FORCEINLINE GLint GetMaxPixelUniformComponents()`
- L145 _public function_ `static FORCEINLINE GLint GetMaxVertexUniformComponents()`
- L146 _public function_ `static FORCEINLINE GLint GetMaxGeometryUniformComponents()`
- L147 _public function_ `static FORCEINLINE GLint GetMaxComputeUniformComponents()`
- L149 _public function_ `static FORCEINLINE uint64 GetVideoMemorySize()`
- L151 _public function_ `static FORCEINLINE bool IsDebugContent()`
- L152 _public function_ `static FORCEINLINE void InitDebugContext()`
- L154 _public function_ `static FORCEINLINE int32 GetReadHalfFloatPixelsEnum() UGL_REQUIRED(0) static FORCEINLINE GLint GetMaxMSAASamplesTileMem()`
- L159 _public function_ `static FORCEINLINE void QueryTimestampCounter(GLuint QueryID) UGL_OPTIONAL_VOID static FORCEINLINE void BeginQuery(GLenum QueryType, GLuint QueryId) UGL_OPTIONAL_VOID static FORCEINLINE void EndQuery(GLenum QueryType) UGL_OPTIONAL_VOID static FORCEINLINE void GetQueryObject(GLuint QueryId, EQueryMode QueryMode, GLuint64 *OutResult) UGL_OPTIONAL_VOID static FORCEINLINE void BindFragDataLocation(GLuint Program, GLuint Color, const GLchar *Name) UGL_OPTIONAL_VOID static FORCEINLINE void ReadBuffer(GLenum Mode) UGL_OPTIONAL_VOID static FORCEINLINE void DrawBuffer(GLenum Mode) UGL_OPTIONAL_VOID static FORCEINLINE void DeleteSync(UGLsync Sync) UGL_OPTIONAL_VOID static FORCEINLINE UGLsync FenceSync(GLenum Condition, GLbitfield Flags) UGL_OPTIONAL(UGLsync()) static FORCEINLINE bool IsSync(UGLsync Sync) UGL_OPTIONAL(false) static FORCEINLINE EFenceResult ClientWaitSync(UGLsync Sync, GLbitfield Flags, GLuint64 Timeout) UGL_OPTIONAL(FR_WaitFailed) static FORCEINLINE void GenSamplers(GLsizei Count, GLuint *Samplers) UGL_OPTIONAL_VOID static FORCEINLINE void DeleteSamplers(GLsizei Count, GLuint *Samplers) UGL_OPTIONAL_VOID static FORCEINLINE void SetSamplerParameter(GLuint Sampler, GLenum Parameter, GLint Value) UGL_OPTIONAL_VOID static FORCEINLINE void BindSampler(GLuint Unit, GLuint Sampler) UGL_OPTIONAL_VOID static FORCEINLINE void PolygonMode(GLenum Face, GLenum Mode) UGL_OPTIONAL_VOID static FORCEINLINE void VertexAttribDivisor(GLuint Index, GLuint Divisor) UGL_OPTIONAL_VOID static F ...` — Silently ignored if not implemented:
- L200 _public function_ `static FORCEINLINE void FramebufferTexture2DMultisample(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint NumSamples) UGL_REQUIRED_VOID static FORCEINLINE void FramebufferTexture3D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint ZOffset) UGL_REQUIRED_VOID static FORCEINLINE void FramebufferTextureLayer(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint Layer) UGL_REQUIRED_VOID static FORCEINLINE void FramebufferRenderbuffer(GLenum Target, GLenum Attachment, GLenum RenderBufferTarget, GLuint RenderBuffer)`
- L207 _public function_ `static FORCEINLINE void FramebufferTextureMultiviewOVR(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint BaseViewIndex, GLsizei NumViews) UGL_REQUIRED_VOID static FORCEINLINE void FramebufferTextureMultisampleMultiviewOVR(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLsizei NumSamples, GLint BaseViewIndex, GLsizei NumViews) UGL_REQUIRED_VOID static FORCEINLINE void BlitFramebuffer(GLint SrcX0, GLint SrcY0, GLint SrcX1, GLint SrcY1, GLint DstX0, GLint DstY0, GLint DstX1, GLint DstY1, GLbitfield Mask, GLenum Filter) UGL_REQUIRED_VOID static FORCEINLINE void DrawBuffers(GLsizei NumBuffers, const GLenum *Buffers) UGL_REQUIRED_VOID static FORCEINLINE void DepthRange(GLdouble Near, GLdouble Far) UGL_REQUIRED_VOID static FORCEINLINE void EnableIndexed(GLenum Parameter, GLuint Index) UGL_REQUIRED_VOID static FORCEINLINE void DisableIndexed(GLenum Parameter, GLuint Index) UGL_REQUIRED_VOID static FORCEINLINE void ColorMaskIndexed(GLuint Index, GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha) UGL_REQUIRED_VOID static FORCEINLINE void VertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid* Pointer) UGL_REQUIRED_VOID static FORCEINLINE void VertexAttribIPointer(GLuint Index, GLint Size, GLenum Type, GLsizei Stride, const GLvoid* Pointer) UGL_REQUIRED_VOID static FORCEINLINE void VertexAttrib4Nsv(GLuint AttributeIndex, const GLshort* Values) UGL_REQUIRED_VOID static FORCEINLINE void ...`
- L284 _public function_ `static FORCEINLINE void BindProgramPipeline(GLuint Pipeline)`
- L285 _public function_ `static FORCEINLINE void DeleteShader(GLuint Program)`
- L286 _public function_ `static FORCEINLINE void DeleteProgramPipelines(GLsizei Number, const GLuint *Pipelines)`
- L287 _public function_ `static FORCEINLINE void GenProgramPipelines(GLsizei Number, GLuint *Pipelines)`
- L288 _public function_ `static FORCEINLINE void ProgramUniform1i(GLuint Program, GLint Location, GLint V0)`
- L289 _public function_ `static FORCEINLINE void ProgramUniform4iv(GLuint Program, GLint Location, GLsizei Count, const GLint *Value)`
- L290 _public function_ `static FORCEINLINE void ProgramUniform4fv(GLuint Program, GLint Location, GLsizei Count, const GLfloat *Value)`
- L291 _public function_ `static FORCEINLINE void ProgramUniform4uiv(GLuint Program, GLint Location, GLsizei Count, const GLuint *Value) UGL_REQUIRED_VOID static FORCEINLINE void GetProgramPipelineiv(GLuint Pipeline, GLenum Pname, GLint* Params) UGL_OPTIONAL_VOID static FORCEINLINE void ValidateProgramPipeline(GLuint Pipeline) UGL_OPTIONAL_VOID static FORCEINLINE void GetProgramPipelineInfoLog(GLuint Pipeline, GLsizei BufSize, GLsizei* Length, GLchar* InfoLog) UGL_OPTIONAL_VOID static FORCEINLINE bool IsProgramPipeline(GLuint Pipeline) UGL_OPTIONAL(false) static FORCEINLINE GLuint64 GetTextureSamplerHandle(GLuint Texture, GLuint Sampler) UGL_REQUIRED(0) static FORCEINLINE GLuint64 GetTextureHandle(GLuint Texture) UGL_REQUIRED(0) static FORCEINLINE void MakeTextureHandleResident(GLuint64 TextureHandle) UGL_REQUIRED_VOID static FORCEINLINE void MakeTextureHandleNonResident(GLuint64 TextureHandle) UGL_REQUIRED_VOID static FORCEINLINE void UniformHandleui64(GLint Location, GLuint64 Value) UGL_REQUIRED_VOID static FORCEINLINE void GetProgramBinary(GLuint Program, GLsizei BufSize, GLsizei *Length, GLenum *BinaryFormat, void *Binary) UGL_OPTIONAL_VOID static FORCEINLINE void ProgramBinary(GLuint Program, GLenum BinaryFormat, const void *Binary, GLsizei Length) UGL_OPTIONAL_VOID static FORCEINLINE void FrameBufferFetchBarrier() UGL_OPTIONAL_VOID static FPlatformOpenGLDevice* CreateDevice() UGL_REQUIRED(NULL) static FPlatformOpenGLContext* CreateContext( FPlatformOpenGLDevice* Device, void* WindowHandle ) UGL_ ...`
- L322 _public function_ `static FORCEINLINE void BufferSubData(GLenum Target, GLintptr Offset, GLsizeiptr Size, const GLvoid* Data)`
- L323 _public function_ `static FORCEINLINE void DeleteBuffers(GLsizei Number, const GLuint* Buffers)`
- L324 _public function_ `static FORCEINLINE void DeleteTextures(GLsizei Number, const GLuint* Textures)`
- L325 _public function_ `static FORCEINLINE void Flush()`
- L326 _public function_ `static FORCEINLINE GLuint CreateShader(GLenum Type)`
- L327 _public function_ `static FORCEINLINE GLuint CreateProgram()`
- L328 _public function_ `static FORCEINLINE bool TimerQueryDisjoint()`
- L333 _public function_ `static FORCEINLINE bool DiscardFrameBufferToResize()` — Calling glBufferData() to discard-reupload is slower than calling glBufferSubData() on some platforms, because changing glBufferData() with a different size (from before) may incur extra validation. To use glBufferData() discard trick: set to this to true - otherwise, glBufferSubData() will used.
- L336 _public prototype_ `static void PE_GetCurrentOpenGLShaderDeviceCapabilities(FOpenGLShaderDeviceCapabilities& Capabilities);` — for platform extensions
- L342 _protected member_ `static GLint MaxTextureImageUnits;`
- L343 _protected member_ `static GLint MaxCombinedTextureImageUnits;`
- L344 _protected member_ `static GLint MaxComputeTextureImageUnits;`
- L345 _protected member_ `static GLint MaxVertexTextureImageUnits;`
- L346 _protected member_ `static GLint MaxGeometryTextureImageUnits;`
- L347 _protected member_ `static GLint MaxVertexUniformComponents;`
- L348 _protected member_ `static GLint MaxPixelUniformComponents;`
- L349 _protected member_ `static GLint MaxGeometryUniformComponents;`
- L350 _protected member_ `static GLint MaxVaryingVectors;`
- L351 _protected member_ `static GLint TextureBufferAlignment;`
- L354 _protected member_ `static bool bSupportsClipControl;` — GL_ARB_clip_control
- L357 _protected member_ `static bool bSupportsASTC;` — GL_KHR_texture_compression_astc_ldr
- L360 _protected member_ `static bool bSupportsASTCHDR;` — GL_KHR_texture_compression_astc_hdr
- L363 _protected member_ `static bool bSupportsSeamlessCubemap;` — GL_ARB_seamless_cube_map
- L366 _protected member_ `static bool bSupportsVolumeTextureRendering;` — Can we render to texture 2D array or 3D
- L369 _protected member_ `static bool bSupportsTextureFilterAnisotropic;` — GL_EXT_texture_filter_anisotropic Can we use anisotropic filtering?
- L372 _protected member_ `static bool bSupportsDrawBuffersBlend;` — GL_ARB_draw_buffers_blend
- L375 _protected member_ `static bool bAmdWorkaround;` — Workaround AMD driver issues.

#### enum `FOpenGLBase::EResourceLockMode`  
`enum class EResourceLockMode : uint8`  
_L40-48_
- L42 _public enumerator_ `RLM_ReadWrite`
- L43 _public enumerator_ `RLM_ReadOnly`
- L44 _public enumerator_ `RLM_WriteOnly`
- L45 _public enumerator_ `RLM_WriteOnlyUnsynchronized`
- L46 _public enumerator_ `RLM_WriteOnlyPersistent`
- L47 _public enumerator_ `RLM_ReadOnlyPersistent`

#### enum `FOpenGLBase::EQueryMode`  
`enum EQueryMode`  
_L50-54_
- L52 _public enumerator_ `QM_Result`
- L53 _public enumerator_ `QM_ResultAvailable`

#### enum `FOpenGLBase::EFenceResult`  
`enum EFenceResult`  
_L56-62_
- L58 _public enumerator_ `FR_AlreadySignaled`
- L59 _public enumerator_ `FR_TimeoutExpired`
- L60 _public enumerator_ `FR_ConditionSatisfied`
- L61 _public enumerator_ `FR_WaitFailed`

#### Free symbols / members of external scopes

- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenGL, Log, VeryVerbose);` — OpenGL Logging.
- L19 _macro_ `#define UGL_REQUIRED_VOID { UE_LOGF(LogOpenGL,Fatal,"%ls is not supported.", ANSI_TO_TCHAR(__FUNCTION__)); }`
- L20 _macro_ `#define UGL_REQUIRED(ReturnValue) { UE_LOGF(LogOpenGL,Fatal,"%ls is not supported.", ANSI_TO_TCHAR(__FUNCTION__)); return (ReturnValue); }`
- L21 _macro_ `#define UGL_OPTIONAL_VOID { }`
- L22 _macro_ `#define UGL_OPTIONAL(ReturnValue) { return (ReturnValue); }`
- L24 _macro_ `#define UGL_SUPPORTS_PIXELBUFFERS 1`
- L25 _macro_ `#define UGL_SUPPORTS_UNIFORMBUFFERS 1`
- L31 _typedef_ `typedef TArray<ANSICHAR> FAnsiCharArray;` — for platform extensions: from OpenGLResources.h

### `Source/Runtime/OpenGLDrv/Private/OpenGLBinaryProgramUtils.h` (Private)


#### class `FOpenGLProgramBinary`  
`class FOpenGLProgramBinary`  
_L10-54_
- L13 _public function_ `FOpenGLProgramBinary()`
- L14 _public function_ `FOpenGLProgramBinary(TArray<uint8>&& ProgramMemory) : OwnedData(MoveTemp(ProgramMemory)), DataView(OwnedData)`
- L22 _public function_ `FOpenGLProgramBinary(TArrayView<const uint8> ProgramMemory) : DataView(ProgramMemory)` — No ownership, just a view to a region within the mmapped PSO cache.
- L29 _public prototype_ `FOpenGLProgramBinary& operator= (FOpenGLProgramBinary&& rhs) = default;`
- L31 _public prototype_ `FOpenGLProgramBinary(FOpenGLProgramBinary&& Src) = default;`
- L33 _public function_ `~FOpenGLProgramBinary()`
- L46 _public function_ `bool IsValid() const`
- L47 _public function_ `bool IsOwned() const`
- L48 _public function_ `const TArrayView<const uint8> GetDataView() const`
- L51 _private member_ `TArray<uint8> OwnedData;` — The data when programs are owned.
- L53 _private member_ `TArrayView<const uint8> DataView;` — a view to the raw program binary, either points to OwnedData or an array view within the mmapped prebuilt PSO cache.

#### struct `UE::OpenGL::FCompressedProgramBinaryHeader`  
`struct FCompressedProgramBinaryHeader`  
_L64-68_
- L66 _public member_ `static const uint32 NotCompressed = 0xFFFFFFFF;`
- L67 _public member_ `uint32 UncompressedSize;`

#### Free symbols / members of external scopes

- L56 _namespace_ `namespace UE`
- L58 _namespace_ `namespace OpenGL` (scope `UE`)
- L62 _prototype_ `bool IsStoringCompressedBinaryPrograms();` (scope `UE::OpenGL`)
- L70 _prototype_ `FOpenGLProgramBinary GetProgramBinaryFromGLProgram(GLuint Program);` (scope `UE::OpenGL`)
- L71 _prototype_ `bool GetUncompressedProgramBinaryFromGLProgram(GLuint Program, TArray<uint8>& ProgramBinaryOUT);` (scope `UE::OpenGL`)
- L72 _prototype_ `bool GetCompressedProgramBinaryFromGLProgram(GLuint Program, TArray<uint8>& ProgramBinaryOUT);` (scope `UE::OpenGL`)
- L73 _prototype_ `void CompressProgramBinary(const TArrayView<const uint8>& UncompressedProgramBinary, TArray<uint8>& ProgramBinaryOUT);` (scope `UE::OpenGL`)
- L74 _prototype_ `bool UncompressCompressedBinaryProgram(const TArrayView<const uint8>& CompressedProgramBinary, TArray<uint8>& UncompressedProgramBinaryOUT);` (scope `UE::OpenGL`)

### `Source/Runtime/OpenGLDrv/Private/OpenGLDrv.h` (Private)


#### class `FOpenGLDynamicRHI`  
`class FOpenGLDynamicRHI final : public IOpenGLDynamicRHI, public IRHICommandContextPSOFallback`  
_L40-609_
- inherits: `IOpenGLDynamicRHI,IRHICommandContextPSOFallback`
- desc: The interface which is implemented by the dynamically bound RHI.
- L42 _private member_ `static inline FOpenGLDynamicRHI* Singleton = nullptr;`
- L45 _public function_ `static inline FOpenGLDynamicRHI& Get()`
- L50 _public prototype_ `FOpenGLDynamicRHI();` — Initialization constructor.
- L53 _public prototype_ `~FOpenGLDynamicRHI() = default;` — Destructor
- L56 _public prototype_ `virtual int32 RHIGetGLMajorVersion() const final override;` — IOpenGLDynamicRHI interface.
- L57 _public prototype_ `virtual int32 RHIGetGLMinorVersion() const final override;`
- L58 _public prototype_ `virtual bool RHISupportsFramebufferSRGBEnable() const final override;`
- L59 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 NumMips, uint32 NumSamples, uint32 NumSamplesTileMem, const FClearValueBinding& ClearValueBinding, GLuint Resource, ETextureCreateFlags Flags) final override;`
- L61 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromAndroidHardwareBuffer(FRHICommandListBase& RHICmdList, AHardwareBuffer* HardwareBuffer) override;`
- L64 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, uint32 NumSamplesTileMem, const FClearValueBinding& ClearValueBinding, GLuint Resource, ETextureCreateFlags Flags) final override;`
- L65 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, uint32 Size, bool bArray, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, uint32 NumSamplesTileMem, const FClearValueBinding& ClearValueBinding, GLuint Resource, ETextureCreateFlags Flags) final override;`
- L66 _public prototype_ `virtual GLuint RHIGetResource(FRHITexture* InTexture) const final override;`
- L67 _public prototype_ `virtual bool RHIIsValidTexture(GLuint InTexture) const final override;`
- L68 _public prototype_ `virtual void RHISetExternalGPUTime(uint64 InExternalGPUTime) final override;`
- L71 _public prototype_ `virtual EGLDisplay RHIGetEGLDisplay() const final override;`
- L72 _public prototype_ `virtual EGLSurface RHIGetEGLSurface() const final override;`
- L73 _public prototype_ `virtual EGLConfig RHIGetEGLConfig() const final override;`
- L74 _public prototype_ `virtual EGLContext RHIGetEGLContext() const final override;`
- L75 _public prototype_ `virtual ANativeWindow* RHIGetEGLNativeWindow() const final override;`
- L76 _public prototype_ `virtual bool RHIEGLSupportsNoErrorContext() const final override;`
- L77 _public prototype_ `virtual void RHIInitEGLInstanceGLES2() final override;`
- L78 _public prototype_ `virtual void RHIInitEGLBackBuffer() final override;`
- L79 _public prototype_ `virtual void RHIEGLSetCurrentRenderingContext() final override;`
- L80 _public prototype_ `virtual void RHIEGLTerminateContext() final override;`
- L84 _public prototype_ `virtual void Init() override;` — FDynamicRHI interface.
- L86 _public prototype_ `virtual void Shutdown() override;`
- L87 _public function_ `virtual const TCHAR* GetName() override`
- L90 _public function_ `template<typename TRHIType> static auto* ResourceCast(TRHIType* Resource)`
- L95 _public function_ `static FOpenGLTexture* ResourceCast(FRHITexture* TextureRHI)`
- L107 _public prototype_ `void BindUniformBuffer(EShaderFrequency ShaderFrequency, uint32 BufferIndex, FRHIUniformBuffer* BufferRHI);`
- L109 _public prototype_ `void SetShaderParametersCommon(EShaderFrequency ShaderFrequency, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters);`
- L110 _public prototype_ `void SetShaderUnbindsCommon(EShaderFrequency ShaderFrequency, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds);`
- L112 _public prototype_ `virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override;`
- L113 _public prototype_ `virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override;`
- L114 _public prototype_ `virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override;`
- L115 _public prototype_ `virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override;`
- L117 _public prototype_ `virtual FPixelShaderRHIRef RHICreatePixelShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L118 _public prototype_ `virtual FVertexShaderRHIRef RHICreateVertexShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L119 _public prototype_ `virtual FGeometryShaderRHIRef RHICreateGeometryShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L120 _public prototype_ `virtual FComputeShaderRHIRef RHICreateComputeShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L123 _public prototype_ `virtual FShaderResourceViewRHIRef RHICreateShaderResourceView (class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;` — SRV / UAV creation functions
- L124 _public prototype_ `virtual FUnorderedAccessViewRHIRef RHICreateUnorderedAccessView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;`
- L126 _public prototype_ `virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation) final override;`
- L127 _public prototype_ `virtual void RHIUpdateUniformBuffer(FRHICommandListBase& RHICmdList, FRHIUniformBuffer* UniformBufferRHI, const void* Contents) final override;`
- L129 _public prototype_ `[[nodiscard]] virtual FRHIBufferInitializer RHICreateBufferInitializer(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc) final override;`
- L131 _public prototype_ `virtual void RHIReplaceResources(FRHICommandListBase& RHICmdList, TArray<FRHIResourceReplaceInfo>&& ReplaceInfos) final override;`
- L132 _public prototype_ `virtual void* LockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;`
- L133 _public prototype_ `virtual void UnlockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L135 _public prototype_ `virtual void RHIUpdateAllocationTags(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L137 _public prototype_ `virtual FRHICalcTextureSizeResult RHICalcTexturePlatformSize(FRHITextureDesc const& Desc, uint32 FirstMipIndex) final override;`
- L138 _public prototype_ `virtual void RHIGetTextureMemoryStats(FTextureMemoryStats& OutStats) final override;`
- L139 _public prototype_ `virtual bool RHIGetTextureMemoryVisualizeData(FColor* TextureData,int32 SizeX,int32 SizeY,int32 Pitch,int32 PixelSize) final override;`
- L140 _public prototype_ `[[nodiscard]] virtual FRHITextureInitializer RHICreateTextureInitializer(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc) final override;`
- L141 _public prototype_ `virtual FTextureRHIRef RHIAsyncCreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, ERHIAccess InResourceState, void** InitialMipData, uint32 NumInitialMips, const TCHAR* DebugName, FGraphEventRef& OutCompletionEvent) final override;`
- L142 _public prototype_ `virtual void RHIGenerateMips(FRHITexture* Texture) final override;`
- L143 _public prototype_ `virtual uint32 RHIComputeMemorySize(FRHITexture* TextureRHI) final override;`
- L145 _public prototype_ `virtual FRHILockTextureResult RHILockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L146 _public prototype_ `virtual void RHIUnlockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L148 _public prototype_ `virtual void RHIUpdateTexture2D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData) final override;`
- L149 _public prototype_ `virtual void RHIUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData) final override;`
- L150 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const TCHAR* Name) final override;`
- L151 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture,FIntRect Rect,TArray<FColor>& OutData,FReadSurfaceDataFlags InFlags) final override;`
- L152 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture, FIntRect Rect, TArray<FLinearColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L153 _public prototype_ `virtual void RHIMapStagingSurface(FRHITexture* Texture, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight, uint32 GPUIndex = 0) final override;`
- L154 _public prototype_ `virtual void RHIUnmapStagingSurface(FRHITexture* Texture, uint32 GPUIndex = 0) final override;`
- L155 _public prototype_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,TArray<FFloat16Color>& OutData,ECubeFace CubeFace,int32 ArrayIndex,int32 MipIndex) final override;`
- L156 _public prototype_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,FIntPoint ZMinMax,TArray<FFloat16Color>& OutData) final override;`
- L157 _public prototype_ `virtual FRenderQueryRHIRef RHICreateRenderQuery(ERenderQueryType QueryType) final override;`
- L158 _public prototype_ `virtual bool RHIGetRenderQueryResult(FRHIRenderQuery* RenderQuery, uint64& OutResult, bool bWait, uint32 GPUIndex = INDEX_NONE) final override;`
- L159 _public prototype_ `virtual FTextureRHIRef RHIGetViewportBackBuffer(FRHIViewport* Viewport) final override;`
- L160 _public prototype_ `virtual void RHIAliasTextureResources(FTextureRHIRef& DestTextureRHI, FTextureRHIRef& SrcTextureRHI) final override;`
- L161 _public prototype_ `virtual FTextureRHIRef RHICreateAliasedTexture(FTextureRHIRef& SourceTexture) final override;`
- L162 _public prototype_ `virtual void RHIAcquireThreadOwnership() final override;`
- L163 _public prototype_ `virtual void RHIReleaseThreadOwnership() final override;`
- L164 _public prototype_ `virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L165 _public prototype_ `virtual void RHIResizeViewport(FRHIViewport* Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L166 _public prototype_ `virtual void RHITick(float DeltaTime) final override;`
- L167 _public prototype_ `virtual void RHIBlockUntilGPUIdle() final override;`
- L168 _public prototype_ `virtual bool RHIGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate) final override;`
- L169 _public prototype_ `virtual void RHIGetSupportedResolution(uint32& Width, uint32& Height) final override;`
- L170 _public prototype_ `virtual void* RHIGetNativeDevice() final override;`
- L171 _public prototype_ `virtual class IRHICommandContext* RHIGetDefaultContext() final override;`
- L172 _public prototype_ `virtual IRHIComputeContext* RHIGetCommandContext(ERHIPipeline Pipeline) final override;`
- L173 _public prototype_ `virtual FRHIFinalizeContextsResult RHIFinalizeContexts(FRHIFinalizeContextsArgs&& Args) final override;`
- L174 _public prototype_ `virtual void RHISubmitCommandLists(FRHISubmitCommandListsArgs&& Args) final override;`
- L176 _public prototype_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName) final override;`
- L177 _public prototype_ `virtual void RHIEndRenderPass() final override;`
- L178 _public prototype_ `virtual void RHINextSubpass() final override;`
- L180 _public prototype_ `virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions) override final;`
- L181 _public prototype_ `virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions) override final;`
- L183 _public prototype_ `virtual void RHISetComputeShader(FRHIComputeShader* ComputeShader) final override;`
- L184 _public prototype_ `virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L185 _public prototype_ `virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L186 _public prototype_ `virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override;`
- L187 _public prototype_ `virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override;`
- L188 _public prototype_ `virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override;`
- L190 _public prototype_ `virtual void RHIBeginRenderQuery_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) override final;`
- L191 _public prototype_ `virtual void RHIEndRenderQuery_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) override final;`
- L192 _public prototype_ `virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L193 _public prototype_ `virtual void RHIEndRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L195 _public prototype_ `virtual void RHIEndDrawingViewport(FRHICommandListImmediate& RHICmdList, FRHIViewport* Viewport, const FRHIPresentArgs& PresentArgs) final override;`
- L196 _public prototype_ `virtual void RHIEndFrame(const FRHIEndFrameArgs& Args) final override;`
- L197 _public prototype_ `virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override;`
- L198 _public prototype_ `virtual void RHISetRasterizerState(FRHIRasterizerState* NewState) final override;`
- L199 _public prototype_ `virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override;`
- L200 _public prototype_ `virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override;`
- L201 _public prototype_ `virtual void RHISetBoundShaderState(FRHIBoundShaderState* BoundShaderState) final override;`
- L202 _public prototype_ `virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override;`
- L203 _public prototype_ `virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* Buffer) final override;`
- L204 _public prototype_ `virtual void RHISetUniformBufferDynamicOffset(FUniformBufferStaticSlot Slot, uint32 Offset) final override;`
- L205 _public prototype_ `virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L206 _public prototype_ `virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L207 _public prototype_ `virtual void RHISetShaderUnbinds(FRHIComputeShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override;`
- L208 _public prototype_ `virtual void RHISetShaderUnbinds(FRHIGraphicsShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override;`
- L209 _public prototype_ `virtual void RHISetDepthStencilState(FRHIDepthStencilState* NewState, uint32 StencilRef) final override;`
- L210 _public prototype_ `virtual void RHISetStencilRef(uint32 StencilRef) final override;`
- L211 _public prototype_ `virtual void RHISetBlendState(FRHIBlendState* NewState, const FLinearColor& BlendFactor) final override;`
- L212 _public function_ `virtual void RHISetBlendFactor(const FLinearColor& BlendFactor) final override`
- L217 _public prototype_ `void SetRenderTargets(uint32 NumSimultaneousRenderTargets, const FRHIRenderTargetView* NewRenderTargets, const FRHIDepthRenderTargetView* NewDepthStencilTarget);`
- L218 _public prototype_ `void SetRenderTargetsAndClear(const FRHISetRenderTargetsInfo& RenderTargetsInfo);`
- L220 _public prototype_ `virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L221 _public prototype_ `virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L222 _public prototype_ `virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L223 _public prototype_ `virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L224 _public prototype_ `virtual void RHIEnableDepthBoundsTest(bool bEnable) final override;`
- L225 _public prototype_ `virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override;`
- L227 _public prototype_ `virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override;`
- L228 _public prototype_ `virtual void RHIEndBreadcrumbGPU (FRHIBreadcrumbNode* Breadcrumb) final override;`
- L230 _public prototype_ `void DiscardRenderTargets(bool Depth, bool Stencil, uint32 ColorBitMask);`
- L233 _public prototype_ `virtual void RHICopyTexture(FRHITexture* SourceTexture, FRHITexture* DestTexture, const FRHICopyTextureInfo& CopyInfo) final override;` — FIXME: Broken on Android for cubemaps
- L235 _public prototype_ `virtual void RHICopyBufferRegion(FRHIBuffer* DestBuffer, uint64 DstOffset, FRHIBuffer* SourceBuffer, uint64 SrcOffset, uint64 NumBytes) final override;`
- L238 _public prototype_ `virtual void RHICopyToStagingBuffer(FRHIBuffer* SourceBufferRHI, FRHIStagingBuffer* DestinationStagingBufferRHI, uint32 InOffset, uint32 InNumBytes) final override;` — Inline copy
- L239 _public prototype_ `virtual void RHIWriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIGPUFence* FenceRHI) final override;`
- L240 _public prototype_ `virtual void RHIWriteGPUFence(FRHIGPUFence* FenceRHI) final override;`
- L241 _public prototype_ `virtual void* RHILockStagingBuffer(FRHIStagingBuffer* StagingBuffer, FRHIGPUFence* Fence, uint32 Offset, uint32 SizeRHI) final override;`
- L242 _public prototype_ `virtual void RHIUnlockStagingBuffer(FRHIStagingBuffer* StagingBuffer) final override;`
- L243 _public prototype_ `virtual void* LockStagingBuffer_RenderThread(class FRHICommandListImmediate& RHICmdList, FRHIStagingBuffer* StagingBuffer, FRHIGPUFence* Fence, uint32 Offset, uint32 SizeRHI) final override;`
- L244 _public prototype_ `virtual void UnlockStagingBuffer_RenderThread(class FRHICommandListImmediate& RHICmdList, FRHIStagingBuffer* StagingBuffer) final override;`
- L245 _public prototype_ `virtual void RHIMapStagingSurface_RenderThread(class FRHICommandListImmediate& RHICmdList, FRHITexture* Texture, uint32 GPUIndex, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight) final override;`
- L246 _public prototype_ `virtual void RHIUnmapStagingSurface_RenderThread(class FRHICommandListImmediate& RHICmdList, FRHITexture* Texture, uint32 GPUIndex) final override;`
- L248 _public prototype_ `virtual FStagingBufferRHIRef RHICreateStagingBuffer() final override;`
- L249 _public prototype_ `virtual FGPUFenceRHIRef RHICreateGPUFence(const FName &Name) final override;`
- L251 _public prototype_ `virtual uint64 RHIGetMinimumAlignmentForBufferBackedSRV(EPixelFormat Format) final override;`
- L254 _public prototype_ `virtual uint64 RHIComputeStatePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;` — Compute the hash of the state components of the PSO initializer for PSO Precaching (only hash data relevant for the RHI specific PSO)
- L257 _public prototype_ `virtual uint64 RHIComputePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;` — Compute the hash of the PSO initializer for PSO Precaching (only hash data relevant for the RHI specific PSO)
- L260 _public prototype_ `virtual bool RHIMatchPrecachePSOInitializers(const FGraphicsPipelineStateInitializer& LHS, const FGraphicsPipelineStateInitializer& RHS) final override;` — Check if PSO Initializers are the same used during PSO Precaching (only compare data relevant for the RHI specific PSO)
- L262 _public prototype_ `void Cleanup();`
- L264 _public prototype_ `void PurgeFramebufferFromCaches(GLuint Framebuffer);`
- L265 _public prototype_ `void OnBufferDeletion(GLenum Type, GLuint BufferResource);`
- L266 _public prototype_ `void OnProgramDeletion(GLint ProgramResource);`
- L267 _public prototype_ `void InvalidateTextureResourceInCache(GLuint Resource);`
- L268 _public prototype_ `void InvalidateUAVResourceInCache(GLuint Resource);`
- L271 _public function_ `FORCEINLINE void CachedSetupTextureStage(GLint TextureIndex, GLenum Target, GLuint Resource, GLint BaseMip, GLint NumMips)` — Set a resource on texture target of a specific real OpenGL stage. Goes through cache to eliminate redundant calls.
- L288 _public prototype_ `void CachedSetupTextureStageInner(GLint TextureIndex, GLenum Target, GLuint Resource, GLint BaseMip, GLint NumMips);`
- L289 _public prototype_ `void CachedSetupUAVStage(GLint UAVIndex, GLenum Format, GLuint Resource, bool bLayered, GLint Layer, GLenum Access, GLint Level);`
- L290 _public prototype_ `void UpdateSRV(FOpenGLShaderResourceView* SRV);`
- L292 _public function_ `void CachedBindUniformBuffer(GLuint Buffer)`
- L304 _public function_ `void CachedBindBuffer(GLenum Type, GLuint Buffer)`
- L347 _public function_ `FOpenGLSamplerState* GetPointSamplerState() const`
- L349 _public prototype_ `void InitializeGLTexture(FOpenGLTexture* Texture, const void* BulkDataPtr, uint64 BulkDataSize);`
- L351 _public prototype_ `void SetCustomPresent(class FRHICustomPresent* InCustomPresent);`
- L418 _public prototype_ `virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override;`
- L420 _public function_ `virtual FGraphicsPipelineStateRHIRef RHICreateGraphicsPipelineState(const FGraphicsPipelineStateInitializer& Initializer) override`
- L427 _public prototype_ `virtual void RHISetGraphicsPipelineState(FRHIGraphicsPipelineState* GraphicsState, uint32 StencilRef, bool bApplyAdditionalState) final override;`
- L429 _public function_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState( FRHIVertexDeclaration* VertexDeclarationRHI, FRHIVertexShader* VertexShaderRHI, FRHIPixelShader* PixelShaderRHI, FRHIGeometryShader* GeometryShaderRHI ) final override`
- L440 _public prototype_ `void LinkComputeProgram(FRHIComputeShader* ComputeShaderRHI);`
- L443 _public prototype_ `virtual void RHIPostExternalCommandsReset() final override;`
- L445 _public prototype_ `GLuint GetOpenGLFramebuffer(uint32 NumSimultaneousRenderTargets, FOpenGLTexture** RenderTargets, const uint32* ArrayIndices, const uint32* MipmapLevels, FOpenGLTexture* DepthStencilTarget);`
- L446 _public prototype_ `GLuint GetOpenGLFramebuffer(uint32 NumSimultaneousRenderTargets, FOpenGLTexture** RenderTargets, const uint32* ArrayIndices, const uint32* MipmapLevels, FOpenGLTexture* DepthStencilTarget, FExclusiveDepthStencil DepthStencilAccess, int32 NumRenderingSamples);`
- L448 _public prototype_ `void ResolveTexture(FOpenGLTexture* Texture, uint32 MipIndex, uint32 ArrayIndex);`
- L451 _public prototype_ `FGLViewportContainer GetViewportContainer();`
- L477 _private prototype_ `FBoundShaderStateRHIRef RHICreateBoundShaderState_Internal(FRHIVertexDeclaration* VertexDeclaration, FRHIVertexShader* VertexShader, FRHIPixelShader* PixelShader, FRHIGeometryShader* GeometryShader, bool FromPSOFileCache);`
- L479 _private prototype_ `void PrepareGFXBoundShaderState(const FGraphicsPipelineStateInitializer& Initializer);`
- L482 _private prototype_ `void EndFrameTick();` — called once per frame, used for resource processing
- L485 _private member_ `FOpenGLRHIState PendingState;` — RHI device state, independent of underlying OpenGL context used
- L486 _private member_ `FSamplerStateRHIRef PointSamplerState;`
- L489 _private member_ `TArray<FOpenGLViewport*> Viewports;` — A list of all viewport RHIs that have been created.
- L490 _private member_ `bool bRevertToSharedContextAfterDrawingViewport = false;`
- L492 _private member_ `EPrimitiveType PrimitiveType = PT_Num;`
- L495 _private member_ `TGlobalResource< TBoundShaderStateHistory<10000> > BoundShaderStateHistory;` — A history of the most recently used bound shader states, used to keep transient bound shader states from being recreated for each use.
- L497 _private member_ `FOpenGLContextState ContextState;`
- L500 _private prototype_ `template <typename TRHIShader> void ApplyStaticUniformBuffers(TRHIShader* Shader);`
- L502 _private member_ `TArray<FRHIUniformBuffer*> GlobalUniformBuffers;`
- L505 _private member_ `TMap<GLuint, TPair<GLenum, GLenum>> TextureMipLimits;` — Cached mip-limits for textures when ARB_texture_view is unavailable
- L508 _private member_ `struct FPlatformOpenGLDevice* PlatformDevice = nullptr;` — Underlying platform-specific data
- L512 _private member_ `FOpenGLProfiler Profiler;`
- L514 _private function_ `void FlushProfilerStats()`
- L524 _private member_ `FCriticalSection CustomPresentSection;`
- L525 _private member_ `TRefCountPtr<class FRHICustomPresent> CustomPresent;`
- L527 _private prototype_ `void InitializeStateResources();`
- L529 _private prototype_ `void SetupVertexArrays(uint32 BaseVertexIndex, FOpenGLStream* Streams, uint32 NumStreams, uint32 MaxVertices);`
- L531 _private prototype_ `void SetupDraw(FOpenGLBuffer* IndexBuffer, uint32 BaseVertexIndex, uint32 MaxVertices);`
- L532 _private prototype_ `void SetupDispatch();`
- L535 _private prototype_ `void BindPendingFramebuffer();` — needs to be called before each draw call
- L536 _private prototype_ `void BindPendingShaderState();`
- L537 _private prototype_ `void BindPendingComputeShaderState(FOpenGLComputeShader* ComputeShader);`
- L538 _private prototype_ `void UpdateRasterizerStateInOpenGLContext();`
- L539 _private prototype_ `void UpdateDepthStencilStateInOpenGLContext();`
- L540 _private prototype_ `void UpdateScissorRectInOpenGLContext();`
- L541 _private prototype_ `void UpdateViewportInOpenGLContext();`
- L543 _private prototype_ `template <class ShaderType> void SetResourcesFromTables(ShaderType* Shader);`
- L544 _private function_ `template <class ShaderType> void SetResourcesFromTables(ShaderType* Shader);`
- L551 _private prototype_ `void CommitGraphicsResourceTablesInner();`
- L552 _private prototype_ `void CommitComputeResourceTables(FOpenGLComputeShader* ComputeShader);`
- L553 _private prototype_ `void CommitNonComputeShaderConstants();`
- L554 _private prototype_ `void CommitComputeShaderConstants(FOpenGLComputeShader* ComputeShader);`
- L555 _private prototype_ `void SetPendingBlendStateForActiveRenderTargets();`
- L558 _private prototype_ `template <typename StateType> void SetupTexturesForDraw(const StateType& ShaderState, int32 MaxTexturesNeeded);`
- L559 _private prototype_ `void SetupTexturesForDraw();`
- L561 _private prototype_ `void SetupUAVsForDraw();`
- L562 _private prototype_ `void SetupUAVsForCompute(const FOpenGLComputeShader* ComputeShader);`
- L563 _private prototype_ `void SetupUAVsForProgram(const TBitArray<>& NeededBits, int32 MaxUAVUnitUsed);`
- L565 _private prototype_ `void RHIClearMRT(const bool* bClearColorArray, int32 NumClearColors, const FLinearColor* ColorArray, bool bClearDepth, float Depth, bool bClearStencil, uint32 Stencil);`
- L569 _public prototype_ `void InternalSetShaderTexture(FOpenGLTexture* Texture, FOpenGLShaderResourceView* SRV, GLint TextureIndex, GLenum Target, GLuint Resource, int NumMips, int LimitMip);` — Remember what RHI user wants set on a specific OpenGL texture stage, translating from Stage and TextureIndex for stage pair.
- L570 _public prototype_ `void InternalSetShaderImageUAV(GLint UAVIndex, GLenum Format, GLuint Resource, bool bLayered, GLint Layer, GLenum Access, GLint Level);`
- L571 _public prototype_ `void InternalSetShaderBufferUAV(GLint UAVIndex, GLuint Resource);`
- L572 _public prototype_ `void InternalSetSamplerStates(GLint TextureIndex, FOpenGLSamplerState* SamplerState);`
- L573 _public prototype_ `void InitializeGLTextureInternal(FOpenGLTexture* Texture, void const* BulkDataPtr, uint64 BulkDataSize);`
- L575 _public prototype_ `void ClearCachedAttributeState(int32 PositionAttrib, int32 TexCoordsAttrib);`
- L579 _private prototype_ `void ApplyTextureStage(GLint TextureIndex, const FTextureStage& TextureStage, FOpenGLSamplerState* SamplerState);`
- L581 _private prototype_ `void ReadSurfaceDataRaw(FRHITexture* TextureRHI, FIntRect Rect, TArray<uint8>& OutData, FReadSurfaceDataFlags InFlags);`
- L583 _private prototype_ `void BindUniformBufferBase(int32 NumUniformBuffers, FRHIUniformBuffer** BoundUniformBuffers, uint32* DynamicOffsets, uint32 FirstUniformBuffer, bool ForceUpdate);`
- L585 _private prototype_ `void ClearCurrentFramebufferWithCurrentScissor(int8 ClearType, int32 NumClearColors, const bool* bClearColorArray, const FLinearColor* ClearColorArray, float Depth, uint32 Stencil);`
- L587 _private member_ `FTextureLockTracker GLLockTracker;`
- L608 _private member_ `} KickHint { this };`

#### struct `FOpenGLDynamicRHI::FTextureLockTracker`  
`struct FTextureLockTracker`  
_L362-416_
- L385 _public member_ `TArray<FLockParams, TInlineAllocator<16> > OutstandingLocks;`
- L387 _public function_ `FTextureLockTracker()`
- L390 _public function_ `FORCEINLINE_DEBUGGABLE void Lock(void* RHIBuffer, void* Buffer, uint32 ArrayIndex, uint32 MipIndex, uint32 Stride, uint32 SizeRHI, EResourceLockMode LockMode)`
- L401 _public function_ `FORCEINLINE_DEBUGGABLE FLockParams Unlock(void* RHIBuffer, uint32 ArrayIndex, uint32 MipIndex)`

#### struct `FOpenGLDynamicRHI::FTextureLockTracker::FLockParams`  
`struct FLockParams`  
_L364-384_
- L366 _public member_ `void* RHIBuffer;`
- L367 _public member_ `void* Buffer;`
- L368 _public member_ `uint32 MipIndex;`
- L369 _public member_ `uint32 ArrayIndex;`
- L370 _public member_ `uint32 BufferSize;`
- L371 _public member_ `uint32 Stride;`
- L372 _public member_ `EResourceLockMode LockMode;`
- L374 _public function_ `FORCEINLINE_DEBUGGABLE FLockParams(void* InRHIBuffer, void* InBuffer, uint32 InArrayIndex, uint32 InMipIndex, uint32 InStride, uint32 InBufferSize, EResourceLockMode InLockMode) : RHIBuffer(InRHIBuffer) , Buffer(InBuffer) , MipIndex(InMipIndex) , ArrayIndex(InArrayIndex) , BufferSize(InBufferSize) , Stride(InStride) , LockMode(InLockMode)`

#### class `FOpenGLDynamicRHI::FGLViewportContainer`  
`class FGLViewportContainer`  
_L453-474_
- L457 _private member_ `static inline UE::FMutex ViewportMutex;`
- L458 _private member_ `UE::TUniqueLock<UE::FMutex> ScopeLock;`
- L459 _private member_ `TArray<FOpenGLViewport*>& Viewports;`
- L461 _private function_ `FGLViewportContainer(TArray<FOpenGLViewport*>& ViewportsIn) : ScopeLock(ViewportMutex), Viewports(ViewportsIn)`
- L466 _public function_ `~FGLViewportContainer()`
- L470 _public function_ `TArray<FOpenGLViewport*>& Get()`

#### class `FOpenGLDynamicRHI::FOpenGLFenceKick`  
`class FOpenGLFenceKick`  
_L589-608_
- L592 _public function_ `FOpenGLFenceKick(FOpenGLDynamicRHI* RHI) : RHI(*RHI)`
- L595 _public prototype_ `~FOpenGLFenceKick();`
- L597 _public prototype_ `void OnDrawCall();`
- L598 _public prototype_ `void Reset();`
- L601 _private prototype_ `void InsertKick();`
- L603 _private member_ `TArray<UGLsync> Syncs;`
- L604 _private member_ `int32 DrawCounter = 0;`
- L605 _private member_ `GLuint LastSeenFramebuffer = 0;`
- L607 _private member_ `FOpenGLDynamicRHI& RHI;`

#### class `FOpenGLDynamicRHIModule`  
`class FOpenGLDynamicRHIModule : public IDynamicRHIModule`  
_L614-625_
- inherits: `IDynamicRHIModule`
- desc: Implements the OpenGLDrv module as a dynamic RHI providing module.
- L619 _public function_ `virtual bool SupportsDynamicReloading() override` — IModuleInterface
- L622 _public prototype_ `virtual bool IsSupported() override;` — IDynamicRHIModule
- L624 _public prototype_ `virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API OPENGLDRV_API`
- L30 _macro_ `#define GL_TEXTURE_EXTERNAL_OES 0x8D65`
- L33 _macro_ `#define FOpenGLCachedUniformBuffer_Invalid 0xFFFFFFFF`
- L353 _macro_ `#define RHITHREAD_GLTRACE 1`
- L355 _macro_ `#define RHITHREAD_GLTRACE_BLOCKING QUICK_SCOPE_CYCLE_COUNTER(STAT_OGLRHIThread_Flush);`
- L359 _macro_ `#define RHITHREAD_GLTRACE_BLOCKING`
- L627 _externvar_ `extern ERHIFeatureLevel::Type GRequestedFeatureLevel;`

### `Source/Runtime/OpenGLDrv/Private/OpenGLDrvPrivate.h` (Private)


#### struct `FOpenGLTextureFormat`  
`struct FOpenGLTextureFormat`  
_L234-257_
- L237 _public member_ `GLenum InternalFormat[2] = { GL_NONE, GL_NONE };` — [0]: without sRGB, [1]: with sRGB
- L238 _public member_ `GLenum Format = GL_NONE;`
- L239 _public member_ `GLenum Type = GL_NONE;`
- L240 _public member_ `bool bCompressed = false;`
- L242 _public member_ `bool bBGRA = false;` — Reorder to B and R elements using texture swizzle
- L244 _public prototype_ `FOpenGLTextureFormat() = default;`
- L246 _public function_ `FOpenGLTextureFormat( GLenum InInternalFormat, GLenum InInternalFormatSRGB, GLenum InFormat, GLenum InType, bool bInCompressed, bool bInBGRA)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define SUBALLOCATED_CONSTANT_BUFFER 0`
- L17 _macro_ `#define GL_CHECK(x) x; do { GLint Err = glGetError(); if (Err != 0) {FPlatformMisc::LowLevelOutputDebugStringf(TEXT("(%s:%d) GL_CHECK Failed '%s'! %d (%x)\n"), ANSI_TO_TCHAR(__FILE__), __LINE__, ANSI_TO_TCHAR( #x ), Err, Err); check(!Err);}`
- L30 _macro_ `#define LOG_AND_GET_GL_INT(IntEnum, Default, Dest) \`
- L56 _macro_ `#define GET_GL_INT(IntEnum, Default, Dest) \`
- L70 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Present time"),STAT_OpenGLPresentTime,STATGROUP_O` — The OpenGL RHI stats.
- L71 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Triangles drawn"),STAT_OpenGLTriangles,STATGROU`
- L72 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Lines drawn"),STAT_OpenGLLines,STATGROUP_Op`
- L73 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateTexture time"),STAT_OpenGLCreateTextureTime,STATG`
- L74 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("LockTexture time"),STAT_OpenGLLockTextureTime,STATGRO`
- L75 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UnlockTexture time"),STAT_OpenGLUnlockTextureTime,STATG`
- L76 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CopyTexture time"),STAT_OpenGLCopyTextureTime,STATGRO`
- L77 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CopyMipToMipAsync time"),STAT_OpenGLCopyMipToMipAsyncTime,S`
- L78 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UploadTextureMip time"),STAT_OpenGLUploadTextureMipTime,ST`
- L79 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateBoundShaderState time"),STAT_OpenGLCreateBoundShaderStateT`
- L80 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Constant buffer update time"),STAT_OpenGLConstantBufferUpdateT`
- L81 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Uniform commit time"),STAT_OpenGLUniformCommitTime,STAT`
- L82 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Shader compile time"),STAT_OpenGLShaderCompileTime,STAT`
- L83 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Shader compile verify time"),STAT_OpenGLShaderCompileVerifyTi`
- L84 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Shader link time"),STAT_OpenGLShaderLinkTime,STATGRO`
- L85 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Shader link verify time"),STAT_OpenGLShaderLinkVerifyTime,`
- L86 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Shader bind param time"),STAT_OpenGLShaderBindParameterTime,S`
- L87 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Uniform buffer pool cleanup time"),STAT_OpenGLUniformBufferCle`
- L88 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Uniform buffer pool memory"),STAT_OpenGLFreeUniformBufferMemo`
- L89 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Emulated Uniform buffer time"), STAT_OpenGLEmulatedUniformBuffer`
- L90 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Uniform buffer pool num free"),STAT_OpenGLNumFreeUniformBuf`
- L91 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Time for first draw of shader programs"), STAT_OpenGLShade`
- L92 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Active Program binary memory (estimate driver use)"), STAT_`
- L93 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("GL Program count"), STAT_OpenGLProgramCount, STATGRO`
- L94 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Program get from cache time"),STAT_OpenGLUseCachedProgramT`
- L95 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Program create from binary time"),STAT_OpenGLCreateProgramFromBin`
- L97 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Program LRU cache eviction time"), STAT_OpenGLShaderLRUEvi`
- L98 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Program LRU cache miss time"), STAT_OpenGLShaderLRUMissTi`
- L99 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Program LRU count"), STAT_OpenGLShaderLRUProgramCount, STATGR`
- L100 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Program LRU evicted count"), STAT_OpenGLShaderLRUEvictedProgramCount`
- L101 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Program LRU miss count"), STAT_OpenGLShaderLRUMissCount, S`
- L102 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Program LRU memory (evicted, heap)"), STAT_OpenGLShaderLRUProg`
- L103 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Program LRU mem mapped (evicted, filemapped)"), STAT_OpenGLShaderLRU`
- L106 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("DrawPrimitive Time"),STAT_OpenGLDrawPrimitiveTime,STATG`
- L107 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("DrawPrimitive Driver Time"),STAT_OpenGLDrawPrimitiveDriverTim`
- L108 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("DrawPrimitiveUP Time"),STAT_OpenGLDrawPrimitiveUPTime,STA`
- L109 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Shader bind time"),STAT_OpenGLShaderBindTime,STATGRO`
- L110 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Texture bind time"),STAT_OpenGLTextureBindTime,STATGR`
- L111 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Uniform bind time"),STAT_OpenGLUniformBindTime,STATGR`
- L112 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("VBO setup time"),STAT_OpenGLVBOSetupTime,STATGROUP`
- L130 _prototype_ `bool PlatformInitOpenGL();` — Initialize OpenGL on this platform. This must be called once before device contexts can be created. @returns true if initialization was successful.
- L136 _prototype_ `int32 PlatformGlGetError();` — Just a glGetError() call. Added to make it possible to compile GL_VERIFY macros in other projects than OpenGLDrv.
- L141 _prototype_ `bool PlatformOpenGLThreadHasRenderingContext();` — Returns true when the calling thread owns the OpenGL rendering context.
- L151 _prototype_ `FPlatformOpenGLDevice* PlatformCreateOpenGLDevice();` — Create the OpenGL device, encompassing all data needed to handle set of OpenGL contexts for a single OpenGL RHI. This contains shared context (to be used for resource loading), rendering context (to be used for rendering), and viewport contexts (to be used for blitting for various platform-specific viewports). On different platforms implementation details differ, by a lot. This should be called when creating the OpenGL RHI.
- L156 _prototype_ `bool PlatformCanEnableGPUCapture();` — Returns true if the platform supports a GPU capture tool (eg RenderDoc)
- L161 _prototype_ `void PlatformDestroyOpenGLDevice(FPlatformOpenGLDevice* Device);` — Destroy the OpenGL device for single OpenGL RHI. This should happen when destroying the RHI.
- L167 _prototype_ `FPlatformOpenGLContext* PlatformCreateOpenGLContext(FPlatformOpenGLDevice* Device, void* InWindowHandle);` — Create an OpenGL context connected to some window, or fullscreen. This will be used to transfer the rendering results to screen by rendering thread, inside RHIEndDrawingViewport().
- L172 _prototype_ `void PlatformDestroyOpenGLContext(FPlatformOpenGLDevice* Device, FPlatformOpenGLContext* Context);` — Destroy a viewport OpenGL context.
- L178 _prototype_ `struct FPlatformOpenGLSurfaceContext* PlatformCreateOpenGLSurfaceContext(FPlatformOpenGLContext* SourceContext, void* InWindowHandle);` — Create an FPlatformOpenGLSurfaceContext that contains properties required for an individual output surface attached to the FPlatformOpenGLContext.
- L183 _prototype_ `void PlatformDestroyOpenGLSurfaceContext(FPlatformOpenGLDevice* Device, FPlatformOpenGLContext* Context, FPlatformOpenGLSurfaceContext* SurfaceContext);` — destroy the FPlatformOpenGLSurfaceContext
- L189 _prototype_ `void PlatformRenderingContextSetup(FPlatformOpenGLDevice* Device);` — Set up rendering OpenGL context on current thread. This is the only context that can be used for rendering, and not only loading resources and framebuffer blitting (due to limitations of Windows OpenGL).
- L194 _prototype_ `void PlatformNULLContextSetup();` — This is used to detach an OpenGL context from current thread.
- L197 _prototype_ `class FOpenGLTexture* PlatformCreateBuiltinBackBuffer(FOpenGLDynamicRHI* OpenGLRHI, struct FPlatformOpenGLSurfaceContext* SurfaceContext, uint32 SizeX, uint32 SizeY);` — Creates a platform-specific back buffer
- L204 _prototype_ `bool PlatformBlitToViewport(IRHICommandContext& RHICmdContext, FPlatformOpenGLDevice* Device, FOpenGLViewport& Viewport, uint32 BackbufferSizeX, uint32 BackbufferSizeY, bool bPresent,bool bLockToVsync);` — Main function for transferring data to on-screen buffers. On Windows it temporarily switches OpenGL context, on Mac only context's output view. Should return true if frame was presented and it is necessary to finish frame rendering.
- L209 _prototype_ `void PlatformResizeGLContext( FPlatformOpenGLDevice* Device, FPlatformOpenGLContext* Context, struct FPlatformOpenGLSurfaceContext* SurfaceContext, uint32 SizeX, uint32 SizeY, bool bFullscreen, bool bWasFullscreen, GLenum BackBufferTarget, GLuint BackBufferResource);` — Resize the GL context for platform.
- L215 _prototype_ `void PlatformGetSupportedResolution(uint32 &Width, uint32 &Height);` — Returns a supported screen resolution that most closely matches input.
- L220 _prototype_ `bool PlatformGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate);` — Retrieve available screen resolutions.
- L225 _prototype_ `void PlatformRestoreDesktopDisplayMode();` — Restore the original display mode
- L228 _prototype_ `void* PlatformGetWindow(FPlatformOpenGLContext* Context, void** AddParam);` — Returns native window handle.
- L259 _externvar_ `extern FOpenGLTextureFormat GOpenGLTextureFormats[PF_MAX];`
- L261 _function_ `inline uint32 FindMaxMipmapLevel(uint32 Size)`
- L271 _function_ `inline uint32 FindMaxMipmapLevel(uint32 Width, uint32 Height)`
- L276 _function_ `inline uint32 FindMaxMipmapLevel(uint32 Width, uint32 Height, uint32 Depth)`
- L281 _function_ `inline void FindPrimitiveType(uint32 InPrimitiveType, uint32 InNumPrimitives, GLenum &DrawMode, GLsizei &NumElements)`
- L310 _function_ `inline uint32 FindUniformElementSize(GLenum UniformType)`
- L369 _function_ `inline uint32 CalcDynamicBufferSize(uint32 Size)` — Calculate the dynamic buffer size needed for a given allocation.
- L378 _prototype_ `void InitDefaultGLContextState(void);` — Call after creating a context to initialise default state values to correct values for UE.
- L380 _externvar_ `extern bool GUseEmulatedUniformBuffers;`

### `Source/Runtime/OpenGLDrv/Private/OpenGLES.h` (Private)


#### struct `FOpenGLES`  
`struct FOpenGLES : public FOpenGLBase`  
_L21-763_
- inherits: `FOpenGLBase`
- L23 _public function_ `static FORCEINLINE bool IsES31Usable()`
- L29 _public function_ `static FORCEINLINE bool IsES32Usable()`
- L35 _public prototype_ `static void ProcessQueryGLInt();`
- L36 _public prototype_ `static void ProcessExtensions(const FString& ExtensionsString);`
- L38 _public function_ `static FORCEINLINE bool SupportsUniformBuffers()`
- L39 _public function_ `static FORCEINLINE bool SupportsStructuredBuffers()`
- L40 _public function_ `static FORCEINLINE bool SupportsExactOcclusionQueries()`
- L42 _public function_ `static FORCEINLINE bool SupportsTimestampQueries()` — MLCHANGES BEGIN -- changed to use bSupportsDisjointTimeQueries
- L44 _public prototype_ `static bool SupportsDisjointTimeQueries();` — MLCHANGES END
- L45 _public function_ `static FORCEINLINE bool SupportsDepthStencilRead()`
- L46 _public function_ `static FORCEINLINE bool SupportsFloatReadSurface()`
- L47 _public function_ `static FORCEINLINE bool SupportsWideMRT()`
- L48 _public function_ `static FORCEINLINE bool SupportsPolygonMode()`
- L49 _public function_ `static FORCEINLINE bool SupportsTexture3D()`
- L50 _public function_ `static FORCEINLINE bool SupportsMobileMultiView()`
- L51 _public function_ `static FORCEINLINE bool SupportsImageExternal()`
- L52 _public function_ `static FORCEINLINE bool SupportsTextureLODBias()`
- L53 _public function_ `static FORCEINLINE bool SupportsTextureCompare()`
- L54 _public function_ `static FORCEINLINE bool SupportsDrawIndexOffset()`
- L55 _public function_ `static FORCEINLINE bool SupportsDiscardFrameBuffer()`
- L56 _public function_ `static FORCEINLINE bool SupportsIndexedExtensions()`
- L57 _public function_ `static FORCEINLINE bool SupportsColorBufferFloat()`
- L58 _public function_ `static FORCEINLINE bool SupportsColorBufferHalfFloat()`
- L59 _public function_ `static FORCEINLINE bool SupportsShaderFramebufferFetch()`
- L60 _public function_ `static FORCEINLINE bool SupportsShaderMRTFramebufferFetch()`
- L61 _public function_ `static FORCEINLINE bool SupportsShaderFramebufferFetchProgrammableBlending()`
- L62 _public function_ `static FORCEINLINE bool SupportsShaderDepthStencilFetch()`
- L63 _public function_ `static FORCEINLINE bool SupportsPixelLocalStorage()`
- L64 _public function_ `static FORCEINLINE bool SupportsMultisampledRenderToTexture()`
- L65 _public function_ `static FORCEINLINE bool SupportsVertexArrayBGRA()`
- L66 _public function_ `static FORCEINLINE bool SupportsBGRA8888()`
- L67 _public function_ `static FORCEINLINE bool SupportsDXT()`
- L68 _public function_ `static FORCEINLINE bool SupportsETC2()`
- L69 _public function_ `static FORCEINLINE GLenum GetDepthFormat()`
- L70 _public function_ `static FORCEINLINE GLenum GetShadowDepthFormat()`
- L71 _public function_ `static FORCEINLINE bool SupportsFramebufferSRGBEnable()`
- L72 _public function_ `static FORCEINLINE bool SupportsRGB10A2()`
- L73 _public function_ `static FORCEINLINE bool SupportsDrawIndirect()`
- L74 _public function_ `static FORCEINLINE bool SupportsBufferStorage()`
- L75 _public function_ `static FORCEINLINE bool SupportsDepthClamp()`
- L78 _public function_ `static FORCEINLINE bool HasBinaryProgramRetrievalFailed()`
- L79 _public function_ `static FORCEINLINE bool RequiresDisabledEarlyFragmentTests()`
- L80 _public function_ `static FORCEINLINE bool RequiresReadOnlyBuffersWorkaround()`
- L81 _public function_ `static FORCEINLINE bool RequiresPreciseQualifierWorkaround()`
- L82 _public function_ `static FORCEINLINE bool RequiresARMShaderFramebufferFetchDepthStencilUndef()`
- L85 _public function_ `static FORCEINLINE int32 GetReadHalfFloatPixelsEnum()` — Adreno doesn't support HALF_FLOAT
- L86 _public function_ `static FORCEINLINE GLint GetMaxMSAASamplesTileMem()`
- L92 _public function_ `static FORCEINLINE bool SupportsFastBufferData()` — On iOS both glMapBufferOES() and glBufferSubData() for immediate vertex and index data is the slow path (they both hit GPU sync and data cache flush in driver according to profiling in driver symbols). Turning this to false reverts back to not using vertex and index buffers for glDrawArrays() and glDrawElements() on dynamic data.
- L94 _public function_ `static FORCEINLINE bool SupportsASTCDecodeMode()`
- L97 _public function_ `static FORCEINLINE void BeginQuery(GLenum QueryType, GLuint QueryId)` — Optional
- L102 _public function_ `static FORCEINLINE void EndQuery(GLenum QueryType)`
- L107 _public function_ `static FORCEINLINE void GenQueries(GLsizei NumQueries, GLuint* QueryIDs)`
- L112 _public function_ `static FORCEINLINE void DeleteQueries(GLsizei NumQueries, const GLuint* QueryIDs)`
- L117 _public function_ `static FORCEINLINE void QueryTimestampCounter(GLuint QueryID)`
- L124 _public function_ `static FORCEINLINE void GetQueryObject(GLuint QueryId, EQueryMode QueryMode, GLuint* OutResult)`
- L130 _public function_ `static FORCEINLINE void GetQueryObject(GLuint QueryId, EQueryMode QueryMode, GLuint64* OutResult)`
- L136 _public function_ `static FORCEINLINE void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)`
- L144 _public function_ `static FORCEINLINE GLsizei GetLabelObject(GLenum Type, GLuint Object, GLsizei BufferSize, ANSICHAR* OutName)`
- L154 _public function_ `static FORCEINLINE void PushGroupMarker(const ANSICHAR* Name)`
- L162 _public function_ `static FORCEINLINE void PopGroupMarker()`
- L170 _public function_ `static FORCEINLINE void* MapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize, EResourceLockMode LockMode)`
- L197 _public function_ `static FORCEINLINE void UnmapBuffer(GLenum Type)`
- L202 _public function_ `static FORCEINLINE void UnmapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize)`
- L207 _public function_ `static FORCEINLINE void TexImage3D(GLenum Target, GLint Level, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLenum Format, GLenum Type, const GLvoid* PixelData)`
- L212 _public function_ `static FORCEINLINE void CompressedTexImage3D(GLenum Target, GLint Level, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLsizei ImageSize, const GLvoid* PixelData)`
- L217 _public function_ `static FORCEINLINE void CompressedTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLsizei ImageSize, const GLvoid* PixelData)`
- L222 _public function_ `static FORCEINLINE void TexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type, const GLvoid* PixelData)`
- L227 _public function_ `static FORCEINLINE void CopyTexSubImage1D(GLenum Target, GLint Level, GLint XOffset, GLint X, GLint Y, GLsizei Width)`
- L231 _public function_ `static FORCEINLINE void CopyTexSubImage2D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height)`
- L236 _public function_ `static FORCEINLINE void CopyTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height)`
- L241 _public function_ `static FORCEINLINE void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth)`
- L246 _public function_ `static FORCEINLINE bool TexStorage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations)`
- L252 _public function_ `static FORCEINLINE void RenderbufferStorageMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height)`
- L258 _public function_ `static FORCEINLINE void ClearBufferfv(GLenum Buffer, GLint DrawBufferIndex, const GLfloat* Value)`
- L263 _public function_ `static FORCEINLINE void ClearBufferfi(GLenum Buffer, GLint DrawBufferIndex, GLfloat Depth, GLint Stencil)`
- L268 _public function_ `static FORCEINLINE void ClearBufferiv(GLenum Buffer, GLint DrawBufferIndex, const GLint* Value)`
- L273 _public function_ `static FORCEINLINE void DrawBuffers(GLsizei NumBuffers, const GLenum* Buffers)`
- L278 _public function_ `static FORCEINLINE void ReadBuffer(GLenum Mode)`
- L283 _public function_ `static FORCEINLINE void DrawBuffer(GLenum Mode)`
- L288 _public function_ `static FORCEINLINE void EnableIndexed(GLenum Parameter, GLuint Index)`
- L301 _public function_ `static FORCEINLINE void DisableIndexed(GLenum Parameter, GLuint Index)`
- L314 _public function_ `static FORCEINLINE void ColorMaskIndexed(GLuint Index, GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha)`
- L327 _public function_ `static FORCEINLINE void BlendEquationi(GLuint Buf, GLenum Mode)`
- L332 _public function_ `static FORCEINLINE void BlendEquationSeparatei(GLuint Buf, GLenum ModeRGB, GLenum ModeAlpha)`
- L337 _public function_ `static FORCEINLINE void BlendFunci(GLuint Buf, GLenum Src, GLenum Dst)`
- L342 _public function_ `static FORCEINLINE void BlendFuncSeparatei(GLuint Buf, GLenum SrcRGB, GLenum DstRGB, GLenum SrcAlpha, GLenum DstAlpha)`
- L348 _public function_ `static FORCEINLINE void TexBuffer(GLenum Target, GLenum InternalFormat, GLuint Buffer)`
- L354 _public function_ `static FORCEINLINE void TexBufferRange(GLenum Target, GLenum InternalFormat, GLuint Buffer, GLintptr Offset, GLsizeiptr Size)`
- L360 _public function_ `static FORCEINLINE void ProgramUniform4uiv(GLuint Program, GLint Location, GLsizei Count, const GLuint* Value)`
- L365 _public function_ `static FORCEINLINE bool SupportsProgramBinary()`
- L367 _public function_ `static FORCEINLINE void GetProgramBinary(GLuint Program, GLsizei BufSize, GLsizei* Length, GLenum* BinaryFormat, void* Binary)`
- L372 _public function_ `static FORCEINLINE void ProgramBinary(GLuint Program, GLenum BinaryFormat, const void* Binary, GLsizei Length)`
- L377 _public function_ `static FORCEINLINE void ProgramParameter(GLuint Program, GLenum PName, GLint Value)`
- L382 _public function_ `static FORCEINLINE void BindBufferBase(GLenum Target, GLuint Index, GLuint Buffer)`
- L387 _public function_ `static FORCEINLINE void BindBufferRange(GLenum Target, GLuint Index, GLuint Buffer, GLintptr Offset, GLsizeiptr Size)`
- L392 _public function_ `static FORCEINLINE GLuint GetUniformBlockIndex(GLuint Program, const GLchar* UniformBlockName)`
- L397 _public function_ `static FORCEINLINE void UniformBlockBinding(GLuint Program, GLuint UniformBlockIndex, GLuint UniformBlockBinding)`
- L402 _public function_ `static FORCEINLINE void BufferSubData(GLenum Target, GLintptr Offset, GLsizeiptr Size, const GLvoid* Data)`
- L407 _public function_ `static FORCEINLINE void VertexAttribIPointer(GLuint Index, GLint Size, GLenum Type, GLsizei Stride, const GLvoid* Pointer)`
- L412 _public function_ `static FORCEINLINE void GenSamplers(GLsizei Count, GLuint* Samplers)`
- L417 _public function_ `static FORCEINLINE void DeleteSamplers(GLsizei Count, GLuint* Samplers)`
- L422 _public function_ `static FORCEINLINE void SetSamplerParameter(GLuint Sampler, GLenum Parameter, GLint Value)`
- L427 _public function_ `static FORCEINLINE void BindSampler(GLuint Unit, GLuint Sampler)`
- L432 _public function_ `static FORCEINLINE void MemoryBarrier(GLbitfield Barriers)`
- L437 _public function_ `static FORCEINLINE void DispatchCompute(GLuint NumGroupsX, GLuint NumGroupsY, GLuint NumGroupsZ)`
- L442 _public function_ `static FORCEINLINE void DispatchComputeIndirect(GLintptr Offset)`
- L447 _public function_ `static FORCEINLINE void BindImageTexture(GLuint Unit, GLuint Texture, GLint Level, GLboolean Layered, GLint Layer, GLenum Access, GLenum Format)`
- L452 _public function_ `static FORCEINLINE void DepthRange(GLdouble Near, GLdouble Far)`
- L457 _public function_ `static FORCEINLINE void VertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid* Pointer)`
- L463 _public function_ `static FORCEINLINE void ClearDepth(GLdouble Depth)`
- L468 _public function_ `static FORCEINLINE void GenerateMipmap( GLenum Target )`
- L473 _public function_ `static FORCEINLINE GLuint GetMajorVersion()`
- L478 _public function_ `static FORCEINLINE GLuint GetMinorVersion()`
- L483 _public function_ `static FORCEINLINE EShaderPlatform GetShaderPlatform()`
- L488 _public function_ `static FORCEINLINE ERHIFeatureLevel::Type GetFeatureLevel()`
- L493 _public function_ `static FORCEINLINE FString GetAdapterName()`
- L498 _public function_ `static FORCEINLINE void TexParameter(GLenum Target, GLenum Parameter, GLint Value)`
- L503 _public function_ `static FORCEINLINE void FramebufferTexture(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level)`
- L509 _public function_ `static FORCEINLINE void FramebufferTexture3D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint ZOffset)`
- L515 _public function_ `static FORCEINLINE void FramebufferTextureLayer(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint Layer)`
- L520 _public function_ `static FORCEINLINE void FramebufferTexture2D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level)`
- L532 _public function_ `static FORCEINLINE void FramebufferTexture2DMultisample(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint NumSamples)`
- L538 _public function_ `static FORCEINLINE void FramebufferTextureMultiviewOVR(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint BaseViewIndex, GLsizei NumViews)`
- L544 _public function_ `static FORCEINLINE void FramebufferTextureMultisampleMultiviewOVR(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLsizei NumSamples, GLint BaseViewIndex, GLsizei NumViews)`
- L550 _public function_ `static FORCEINLINE void BlitFramebuffer(GLint SrcX0, GLint SrcY0, GLint SrcX1, GLint SrcY1, GLint DstX0, GLint DstY0, GLint DstX1, GLint DstY1, GLbitfield Mask, GLenum Filter)`
- L555 _public function_ `static FORCEINLINE bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, ETextureCreateFlags Flags)`
- L562 _public function_ `static FORCEINLINE void DrawArraysInstanced(GLenum Mode, GLint First, GLsizei Count, GLsizei InstanceCount)`
- L567 _public function_ `static FORCEINLINE void DrawElementsInstanced(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid* Indices, GLsizei InstanceCount)`
- L572 _public function_ `static FORCEINLINE void CopyBufferSubData(GLenum ReadTarget, GLenum WriteTarget, GLintptr ReadOffset, GLintptr WriteOffset, GLsizeiptr Size)`
- L577 _public function_ `static FORCEINLINE void DrawArraysIndirect(GLenum Mode, const void* Offset)`
- L582 _public function_ `static FORCEINLINE void DrawElementsIndirect(GLenum Mode, GLenum Type, const void* Offset)`
- L587 _public function_ `static FORCEINLINE void VertexAttribDivisor(GLuint Index, GLuint Divisor)`
- L592 _public function_ `static FORCEINLINE void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type)`
- L597 _public function_ `static FPlatformOpenGLDevice* CreateDevice() UGL_REQUIRED(NULL) static FPlatformOpenGLContext* CreateContext(FPlatformOpenGLDevice* Device, void* WindowHandle) UGL_REQUIRED(NULL) static FORCEINLINE void InvalidateFramebuffer(GLenum Target, GLsizei NumAttachments, const GLenum* Attachments)`
- L605 _public function_ `static FORCEINLINE void GenBuffers(GLsizei n, GLuint* buffers)`
- L610 _public function_ `static FORCEINLINE void GenTextures(GLsizei n, GLuint* textures)`
- L615 _public function_ `static FORCEINLINE bool TimerQueryDisjoint()`
- L629 _public function_ `static FORCEINLINE void BindVertexBuffer(GLuint BindingIndex, GLuint Buffer, GLintptr Offset, GLsizei Stride)`
- L633 _public function_ `static FORCEINLINE void VertexAttribFormat(GLuint AttribIndex, GLint Size, GLenum Type, GLboolean Normalized, GLuint RelativeOffset)`
- L637 _public function_ `static FORCEINLINE void VertexAttribIFormat(GLuint AttribIndex, GLint Size, GLenum Type, GLuint RelativeOffset)`
- L641 _public function_ `static FORCEINLINE void VertexAttribBinding(GLuint AttribIndex, GLuint BindingIndex)`
- L645 _public function_ `static FORCEINLINE void VertexBindingDivisor(GLuint BindingIndex, GLuint Divisor)`
- L650 _public function_ `static FORCEINLINE void BufferStorage(GLenum Target, GLsizeiptr Size, const void* Data, GLbitfield Flags)`
- L656 _protected member_ `static bool bSupportsDisjointTimeQueries;` — GL_EXT_disjoint_timer_query
- L659 _protected member_ `static bool bTimerQueryCanBeDisjoint;` — Some timer query implementations are never disjoint
- L662 _protected member_ `static bool bSupportsBGRA8888;` — GL_APPLE_texture_format_BGRA8888
- L665 _protected member_ `static bool bSupportsETC2;` — OpenGL ES 3.0 profile
- L668 _protected member_ `static bool bSupportsColorBufferFloat;` — GL_EXT_color_buffer_float
- L671 _protected member_ `static bool bSupportsColorBufferHalfFloat;` — GL_EXT_color_buffer_half_float
- L674 _protected member_ `static bool bSupportsShaderFramebufferFetch;` — GL_EXT_shader_framebuffer_fetch
- L677 _protected member_ `static bool bSupportsShaderMRTFramebufferFetch;` — GL_EXT_shader_framebuffer_fetch (MRT's)
- L681 _protected member_ `static bool bSupportsShaderDepthStencilFetch;` — GL_ARM_shader_framebuffer_fetch_depth_stencil
- L684 _protected member_ `static bool bSupportsMultisampledRenderToTexture;` — GL_EXT_MULTISAMPLED_RENDER_TO_TEXTURE
- L687 _protected member_ `static bool bSupportsPixelLocalStorage;` — workaround for GL_EXT_shader_pixel_local_storage
- L690 _protected member_ `static int ShaderLowPrecision;` — GL_FRAGMENT_SHADER, GL_LOW_FLOAT
- L693 _protected member_ `static int ShaderMediumPrecision;` — GL_FRAGMENT_SHADER, GL_MEDIUM_FLOAT
- L696 _protected member_ `static int ShaderHighPrecision;` — GL_FRAGMENT_SHADER, GL_HIGH_FLOAT
- L699 _protected member_ `static bool bSupportsNVFrameBufferBlit;` — GL_NV_framebuffer_blit
- L702 _protected member_ `static bool bSupportsStandardDerivativesExtension;` — GL_OES_standard_derivations
- L705 _protected member_ `static GLint MaxMSAASamplesTileMem;` — Maximum number of MSAA samples supported on chip in tile memory, or 1 if not available
- L708 _protected member_ `static bool bSupportsASTCDecodeMode;` — GL_EXT_texture_compression_astc_decode_mode
- L712 _public member_ `static bool bBinaryProgramRetrievalFailed;` — This indicates failure when attempting to retrieve driver's binary representation of the hack program
- L715 _public member_ `static bool bRequiresDisabledEarlyFragmentTests;` — Some Mali devices do not work correctly with early_fragment_test enabled
- L718 _public member_ `static bool bRequiresReadOnlyBuffersWorkaround;` — This is a workaround for a Mali bug where read-only buffers do not work when passed to functions
- L721 _public member_ `static bool bRequiresPreciseQualifierWorkaround;` — This is a workaround for Samsung xclipse that fails to compile shaders that use the 'precise' qualifier
- L724 _public member_ `static bool bRequiresARMShaderFramebufferFetchDepthStencilUndef;` — This is to avoid a bug in Adreno drivers that define GL_ARM_shader_framebuffer_fetch_depth_stencil even when device does not support this extension
- L727 _public member_ `static bool bSupportsShaderFramebufferFetchProgrammableBlending;` — Framebuffer fetch can be used to do programmable blending without running into driver issues
- L730 _public member_ `static bool bSupportsRGB10A2;` — GL_OES_vertex_type_10_10_10_2
- L733 _public member_ `static bool bSupportsProgramBinary;` — GL_OES_get_program_binary
- L736 _public member_ `static bool bSupportsBufferStorage;` — GL_EXT_buffer_storage
- L739 _public member_ `static bool bSupportsDepthClamp;` — GL_EXT_depth_clamp
- L750 _public member_ `static EFeatureLevelSupport CurrentFeatureLevelSupport;` — Describes which feature level is currently being supported
- L753 _public member_ `static bool bHasHardwareHiddenSurfaceRemoval;` — Whether device supports Hidden Surface Removal
- L756 _public member_ `static bool bSupportsMobileMultiView;` — Whether device supports mobile multi-view
- L758 _public member_ `static GLint MaxComputeUniformComponents;`
- L760 _public member_ `static GLint MaxCombinedUAVUnits;`
- L761 _public member_ `static GLint MaxComputeUAVUnits;`
- L762 _public member_ `static GLint MaxPixelUAVUnits;`

#### enum `FOpenGLES::EFeatureLevelSupport`  
`enum class EFeatureLevelSupport : uint8`  
_L741-747_
- L743 _public enumerator_ `Invalid` — no feature level has yet been determined
- L744 _public enumerator_ `ES2`
- L745 _public enumerator_ `ES31`
- L746 _public enumerator_ `ES32`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace OpenGLConsoleVariables`
- L18 _externvar_ `extern int32 bUseUnsynchronizedBufferMapping;` (scope `OpenGLConsoleVariables`)

### `Source/Runtime/OpenGLDrv/Private/OpenGLFunctions.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/OpenGLDrv/Private/OpenGLPlatform.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using UGLsync = GLsync;`
- L13 _macro_ `#define GL_HALF_FLOAT 0x140B`
- L17 _macro_ `#define GL_RGBA16F 0x881A`
- L24 _macro_ `#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0`
- L25 _macro_ `#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1`
- L26 _macro_ `#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2`
- L27 _macro_ `#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3`
- L32 _macro_ `#define GL_SRGB_EXT 0x8C40`
- L33 _macro_ `#define GL_SRGB8_EXT 0x8C41`
- L34 _macro_ `#define GL_SRGB_ALPHA_EXT 0x8C42`
- L35 _macro_ `#define GL_SRGB8_ALPHA8_EXT 0x8C43`
- L36 _macro_ `#define GL_SLUMINANCE_ALPHA_EXT 0x8C44`
- L37 _macro_ `#define GL_SLUMINANCE8_ALPHA8_EXT 0x8C45`
- L38 _macro_ `#define GL_SLUMINANCE_EXT 0x8C46`
- L39 _macro_ `#define GL_SLUMINANCE8_EXT 0x8C47`
- L40 _macro_ `#define GL_COMPRESSED_SRGB_EXT 0x8C48`
- L41 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_EXT 0x8C49`
- L42 _macro_ `#define GL_COMPRESSED_SLUMINANCE_EXT 0x8C4A`
- L43 _macro_ `#define GL_COMPRESSED_SLUMINANCE_ALPHA_EXT 0x8C4B`
- L44 _macro_ `#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT 0x8C4C`
- L45 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D`
- L46 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E`
- L47 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F`
- L52 _macro_ `#define GL_COMPRESSED_RED_RGTC1 0x8DBB`
- L53 _macro_ `#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC`
- L54 _macro_ `#define GL_COMPRESSED_RG_RGTC2 0x8DBD`
- L55 _macro_ `#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE`
- L60 _macro_ `#define GL_SLUMINANCE_NV 0x8C46`
- L61 _macro_ `#define GL_SLUMINANCE_ALPHA_NV 0x8C44`
- L62 _macro_ `#define GL_SRGB8_NV 0x8C41`
- L63 _macro_ `#define GL_SLUMINANCE8_NV 0x8C47`
- L64 _macro_ `#define GL_SLUMINANCE8_ALPHA8_NV 0x8C45`
- L65 _macro_ `#define GL_COMPRESSED_SRGB_S3TC_DXT1_NV 0x8C4C`
- L66 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D`
- L67 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E`
- L68 _macro_ `#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F`
- L73 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR 0x93B0`
- L74 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR 0x93B1`
- L75 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR 0x93B2`
- L76 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR 0x93B3`
- L77 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR 0x93B4`
- L78 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR 0x93B5`
- L79 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR 0x93B6`
- L80 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR 0x93B7`
- L81 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR 0x93B8`
- L82 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR 0x93B9`
- L83 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR 0x93BA`
- L84 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB`
- L85 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC`
- L86 _macro_ `#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD`
- L88 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0`
- L89 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1`
- L90 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2`
- L91 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3`
- L92 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4`
- L93 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5`
- L94 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6`
- L95 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7`
- L96 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8`
- L97 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9`
- L98 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA`
- L99 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB`
- L100 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC`
- L101 _macro_ `#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD`
- L105 _macro_ `#define GL_TESS_EVALUATION_SHADER 0x8E87`
- L108 _macro_ `#define GL_TESS_CONTROL_SHADER 0x8E88`
- L111 _macro_ `#define GL_PATCHES 0x000E`
- L114 _macro_ `#define GL_PATCH_VERTICES 0x8E72`
- L117 _macro_ `#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29`
- L120 _macro_ `#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81`
- L123 _macro_ `#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82`
- L126 _macro_ `#define GL_READ_WRITE 0x88BA`
- L129 _macro_ `#define GL_ALL_BARRIER_BITS 0xFFFFFFFF`
- L132 _macro_ `#define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009`
- L135 _macro_ `#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0`
- L138 _macro_ `#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1`
- L141 _macro_ `#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90EC`
- L144 _macro_ `#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F`
- L147 _macro_ `#define GL_TIME_ELAPSED_EXT 0x88BF`
- L150 _macro_ `#define GL_TIMESTAMP_EXT 0x8E28`
- L153 _macro_ `#define GL_DISPATCH_INDIRECT_BUFFER 0x90EE`
- L156 _macro_ `#define GL_DRAW_INDIRECT_BUFFER 0x8F3F`
- L159 _macro_ `#define GL_MAP_WRITE_BIT 0x0002`
- L162 _macro_ `#define GL_MAP_PERSISTENT_BIT 0x0040`
- L165 _macro_ `#define GL_MAP_COHERENT_BIT 0x0080`
- L168 _macro_ `#define GL_DEPTH_BOUNDS_TEST_EXT 0x8890`
- L171 _macro_ `#define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90EA`
- L174 _macro_ `#define GL_TEXTURE_SWIZZLE_R 0x8E42`
- L177 _macro_ `#define GL_TEXTURE_SWIZZLE_G 0x8E43`
- L180 _macro_ `#define GL_TEXTURE_SWIZZLE_B 0x8E44`
- L183 _macro_ `#define GL_TEXTURE_SWIZZLE_A 0x8E45`
- L186 _macro_ `#define GL_RED 0x1903`
- L189 _macro_ `#define GL_BLUE 0x1905`
- L192 _macro_ `#define GL_STENCIL_INDEX 0x1901`
- L195 _macro_ `#define GL_RGBA_INTEGER 0x8D99`
- L199 _macro_ `#define GL_COMPUTE_SHADER 0x91B9`
- L200 _macro_ `#define GL_MAX_COMPUTE_UNIFORM_BLOCKS 0x91BB`
- L201 _macro_ `#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC`
- L202 _macro_ `#define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91BD`
- L203 _macro_ `#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262`
- L204 _macro_ `#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263`
- L205 _macro_ `#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264`
- L206 _macro_ `#define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265`
- L207 _macro_ `#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266`
- L208 _macro_ `#define GL_MAX_COMPUTE_LOCAL_INVOCATIONS 0x90EB`
- L209 _macro_ `#define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0x91BE`
- L210 _macro_ `#define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0x91BF`
- L211 _macro_ `#define GL_COMPUTE_LOCAL_WORK_SIZE 0x8267`
- L213 _macro_ `#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED`
- L215 _macro_ `#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF`
- L216 _macro_ `#define GL_COMPUTE_SHADER_BIT 0x00000020`
- L220 _macro_ `#define GL_GPU_DISJOINT_EXT 0x8FBB`
- L224 _macro_ `#define GL_UNPACK_CLIENT_STORAGE_APPLE 0x85B2`
- L228 _macro_ `#define GL_TEXTURE_RANGE_LENGTH_APPLE 0x85B7`
- L229 _macro_ `#define GL_TEXTURE_RANGE_POINTER_APPLE 0x85B8`
- L230 _macro_ `#define GL_TEXTURE_STORAGE_HINT_APPLE 0x85BC`
- L231 _macro_ `#define GL_TEXTURE_MINIMIZE_STORAGE_APPLE 0x85B6`
- L232 _macro_ `#define GL_STORAGE_PRIVATE_APPLE 0x85BD`
- L233 _macro_ `#define GL_STORAGE_CACHED_APPLE 0x85BE`
- L234 _macro_ `#define GL_STORAGE_SHARED_APPLE 0x85BF`
- L238 _macro_ `#define TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69`
- L242 _macro_ `#define GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT 0x8F63`
- L243 _macro_ `#define GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT 0x8F67`
- L244 _macro_ `#define GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64`

### `Source/Runtime/OpenGLDrv/Private/OpenGLProgramBinaryFileCache.h` (Private)


#### class `FOpenGLProgramBinaryCache`  
`class FOpenGLProgramBinaryCache`  
_L17-148_
- L20 _public prototype_ `static void Initialize();`
- L21 _public prototype_ `static void Shutdown();`
- L23 _public prototype_ `static bool IsEnabled();`
- L26 _public prototype_ `static bool RequiresCaching(const FOpenGLProgramKey& ProgramKey);` — has the program already been encountered
- L30 _public prototype_ `static void CacheProgramBinary(const FOpenGLProgramKey& ProgramKey, TUniqueObj<FOpenGLProgramBinary>&& ProgramBinary);` — Take an existing program binary and store on disk. Only when ProgramBinaryCache is enabled
- L33 _public prototype_ `static void TickBinaryCache();` — Create any pending GL programs that have come from shader library requests
- L36 _public prototype_ `static bool CheckSinglePendingGLProgramCreateRequest(const FOpenGLProgramKey& ProgramKey);` — Create any single GL program that have come from shader library requests
- L39 _public prototype_ `static bool IsBuildingCache();` — true if the program binary cache is currently in cache build mode
- L42 _public prototype_ `static void EnqueueBinaryForGLProgramContainer(const FOpenGLProgramKey& ProgramKey, TUniqueObj<FOpenGLProgramBinary>&& ProgramBinary);` — Add a binary program to the GL container queue, it is moved at a later point to the GL program container
- L45 _private prototype_ `FOpenGLProgramBinaryCache(const FString& InCachePath);`
- L46 _private prototype_ `~FOpenGLProgramBinaryCache();`
- L48 _private prototype_ `FString GetProgramBinaryCacheFilePath() const;`
- L58 _private member_ `static TAutoConsoleVariable<int32> CVarPBCEnable;`
- L59 _private member_ `static TAutoConsoleVariable<int32> CVarRestartAndroidAfterPrecompile;`
- L60 _private member_ `static FOpenGLProgramBinaryCache* CachePtr;`
- L65 _private member_ `FString CachePathRoot;` — Path to root directory where the binary program subdir will be created
- L67 _private member_ `FString CacheSubDir;` — Subdir is a hash of the device's version info, anything within CachePathRoot that does not == CacheSubDir is deleted.
- L83 _private member_ `FCurrentShaderPipelineProperties CurrentShaderPipelineProperties;`
- L89 _private member_ `TMap<GLuint, FPendingShaderCode> ShadersPendingCompilation;` — Shaders that were requested for compilation They will be compiled just before linking a program only in case when there is no saved binary program
- L91 _private prototype_ `void Reset();`
- L93 _private prototype_ `void ScanProgramCacheFile();`
- L95 _private prototype_ `bool OpenCacheWriteHandle(const FString& ProgramCacheFilenameToWrite, bool bAppendToExisting);`
- L98 _private prototype_ `bool MarkValidContent(int32 NumPrograms);` — set the file header to the current write position and program count, then flush the cache to storage.
- L101 _private prototype_ `bool CloseCacheWriteHandle(int32 NumProgramsAdded);` — finalize the current cache file, returns true if a valid file was created.
- L103 _private prototype_ `bool RequiresCaching_Internal(const FOpenGLProgramKey& ProgramKey);`
- L105 _private prototype_ `void AddProgramBinaryDataToBinaryCache(const FOpenGLProgramKey& ProgramKey, const FOpenGLProgramBinary& BinaryProgramData);`
- L107 _private prototype_ `void CheckPendingGLProgramCreateRequests_internal();`
- L108 _private prototype_ `bool CheckSinglePendingGLProgramCreateRequest_internal(const FOpenGLProgramKey& ProgramKey);`
- L111 _private prototype_ `void OnShaderPipelineCacheOpened(FString const& Name, EShaderPlatform Platform, uint32 Count, const FGuid& VersionGuid, FShaderPipelineCache::FShaderCachePrecompileContext& ShaderCachePrecompileContext);` — Delegate handlers to track the ShaderPipelineCache precompile.
- L112 _private prototype_ `void OnShaderPipelineCachePrecompilationComplete(uint32 Count, double Seconds, const FShaderPipelineCache::FShaderCachePrecompileContext& ShaderCachePrecompileContext);`
- L114 _private prototype_ `void InitPrecaching();`
- L115 _private prototype_ `void UpdatePrecacheMapping();`
- L118 _private prototype_ `TRefCountPtr<FOpenGLProgramBinaryMapping> GetOrAddFileMapping(const FString& ProgramCacheFilename, int32 ProgramCount, int64 Offset, int64 Size);`
- L120 _private function_ `FString GetProgramBinaryCacheDir() const`
- L121 _private prototype_ `bool ReadProgramFile_Internal(uint32 ProgramsToRead, int64 EndOffset, const FString& ProgramCacheFilename, FArchive& Ar);`
- L123 _private member_ `FDelegateHandle OnShaderPipelineCacheOpenedDelegate;`
- L124 _private member_ `FDelegateHandle OnShaderPipelineCachePrecompilationCompleteDelegate;`
- L126 _private member_ `TSet<FOpenGLProgramKey> ProgramsInCurrentCache;` — Only populated during PSO precompile delegates.
- L130 _private member_ `TMap<FOpenGLProgramKey, TUniqueObj<FOpenGLProgramBinary>> PendingGLContainerPrograms;` — All of the binary programs encountered during PSO cache processing. The contents are moved to OpenGL's program cache during RHI's end of frame tick.
- L132 _private member_ `FArchive* BinaryCacheWriteFileHandle;`
- L133 _private member_ `bool bShownLoadingScreen;`
- L142 _private function_ `bool IsBuildingCache_internal() const`
- L144 _private member_ `EBinaryFileState CurrentBinaryFileState;`
- L147 _private member_ `TMap<FGuid, TRefCountPtr<FOpenGLProgramBinaryMapping>> MappedCacheFiles;` — Container of all currently open program cache files.

#### struct `FOpenGLProgramBinaryCache::FPendingShaderCode`  
`struct FPendingShaderCode`  
_L50-55_
- L52 _public member_ `TArray<ANSICHAR> GlslCode;`
- L53 _public member_ `int32 UncompressedSize;`
- L54 _public member_ `bool bCompressed;`

#### struct `FOpenGLProgramBinaryCache::FCurrentShaderPipelineProperties`  
`struct FCurrentShaderPipelineProperties`  
_L69-82_
- L72 _public member_ `FGuid CacheVersionGuid;` — Guid of the PSO cache being procesed.
- L74 _public member_ `FString PipelineCacheName;` — String name of the current cache.
- L77 _public member_ `int32 NumProgramsFlushed = 0;` — contains the count of programs when the write cache was last flushed.
- L79 _public member_ `int64 LastMappedPosition = 0;` — Last mmapped position
- L81 _public member_ `int32 MappedPrograms = 0;` — Last number of programs mapped

#### enum `FOpenGLProgramBinaryCache::EBinaryFileState`  
`enum class EBinaryFileState : uint8`  
_L135-140_
- L137 _public enumerator_ `Uninitialized` — No binary file is yet established and we should not read or write to it.
- L138 _public enumerator_ `BuildingCacheFile` — We are precompiling shaders from the PSO and storing them in a new binary cache. Do not attempt to read.
- L139 _public enumerator_ `ValidCacheFile` — We have a valid cache file we can use for reading.

### `Source/Runtime/OpenGLDrv/Private/OpenGLResources.h` (Private)


#### class `FOpenGLViewableResource`  
`class FOpenGLViewableResource`  
_L78-97_
- L81 _public function_ `~FOpenGLViewableResource()`
- L86 _public function_ `bool HasLinkedViews() const`
- L91 _public prototype_ `void UpdateLinkedViews();`
- L96 _private member_ `class FOpenGLView* LinkedViews = nullptr;`

#### class `FOpenGLBufferBase`  
`class FOpenGLBufferBase`  
_L99-112_
- L102 _protected function_ `FOpenGLBufferBase(GLenum Type) : Type(Type)`
- L107 _public member_ `GLenum Type;`
- L108 _public member_ `GLuint Resource = 0;`
- L110 _public prototype_ `void Bind();`
- L111 _public prototype_ `void OnBufferDeletion();`

#### class `TOpenGLBuffer`  
`template <typename BaseType> class TOpenGLBuffer : public BaseType, public FOpenGLBufferBase`  
_L115-500_
- inherits: `BaseType,FOpenGLBufferBase`
- L117 _private function_ `void LoadData(uint32 InOffset, uint32 InSize, const void* InData)`
- L142 _private function_ `GLenum GetAccess()`
- L150 _public function_ `TOpenGLBuffer(FRHICommandListBase* RHICmdList, GLenum InType, const FRHIBufferCreateDesc& CreateDesc, const void *InData) : BaseType(CreateDesc) , FOpenGLBufferBase(InType)`
- L192 _public function_ `virtual ~TOpenGLBuffer()`
- L197 _public function_ `uint8* Lock(uint32 InOffset, uint32 InSize, bool bReadOnly, bool bDiscard)`
- L272 _public function_ `uint8* LockWriteOnlyUnsynchronized(uint32 InOffset, uint32 InSize, bool bDiscard)`
- L344 _public function_ `void Unlock()`
- L407 _public function_ `void Update(void *InData, uint32 InOffset, uint32 InSize, bool bDiscard)`
- L419 _public function_ `bool IsDynamic() const`
- L420 _public function_ `bool IsLocked() const`
- L421 _public function_ `bool IsLockReadOnly() const`
- L422 _public function_ `void* GetLockedBuffer() const`
- L424 _public function_ `void ReleaseCachedBuffer()`
- L435 _public function_ `void TakeOwnership(TOpenGLBuffer& Other)`
- L455 _public function_ `void ReleaseOwnership()`
- L488 _private member_ `uint32 bIsLocked : 1 = false;`
- L489 _private member_ `uint32 bIsLockReadOnly : 1 = false;`
- L490 _private member_ `uint32 bLockBufferWasAllocated : 1 = false;`
- L492 _private member_ `GLuint LockSize = 0;`
- L493 _private member_ `GLuint LockOffset = 0;`
- L494 _private member_ `void* LockBuffer = nullptr;`
- L497 _private member_ `void* CachedBuffer = nullptr;` — A cached allocation that can be reused. The same allocation can never be in CachedBuffer and LockBuffer at the same time.
- L499 _private member_ `GLuint CachedBufferSize = 0;` — The size of the cached buffer allocation. Can be non zero even though CachedBuffer is  null, to preserve the allocation size.

#### class `FOpenGLBasePixelBuffer`  
`class FOpenGLBasePixelBuffer : public FRefCountedObject`  
_L502-532_
- inherits: `FRefCountedObject`
- L505 _public function_ `FOpenGLBasePixelBuffer(const FRHIBufferCreateDesc& CreateDesc) : Desc(CreateDesc)`
- L509 _public function_ `const FRHIBufferDesc& GetDesc() const`
- L510 _public function_ `uint32 GetSize() const`
- L511 _public function_ `EBufferUsageFlags GetUsage() const`
- L513 _public function_ `void TakeOwnership(FOpenGLBasePixelBuffer& Other)`
- L519 _public function_ `void ReleaseOwnership()`
- L525 _private member_ `FRHIBufferDesc Desc;`
- L528 _protected function_ `void UpdateBufferStats(bool bAllocating)`

#### class `FOpenGLBaseBuffer`  
`class FOpenGLBaseBuffer : public FRHIBuffer, public FOpenGLViewableResource`  
_L534-552_
- inherits: `FRHIBuffer,FOpenGLViewableResource`
- L537 _public function_ `FOpenGLBaseBuffer(const FRHIBufferCreateDesc& InCreateDesc) : FRHIBuffer(InCreateDesc)`
- L544 _protected function_ `void UpdateBufferStats(bool bAllocating)`

#### struct `FOpenGLEUniformBufferData`  
`struct FOpenGLEUniformBufferData : public FRefCountedObject`  
_L557-573_
- inherits: `FRefCountedObject`
- L559 _public function_ `FOpenGLEUniformBufferData(uint32 SizeInBytes)`
- L567 _public function_ `~FOpenGLEUniformBufferData()`
- L572 _public member_ `TArray<uint32> Data;`

#### class `FOpenGLUniformBuffer`  
`class FOpenGLUniformBuffer : public FRHIUniformBuffer`  
_L576-622_
- inherits: `FRHIUniformBuffer`
- L580 _public member_ `GLuint Resource;` — The GL resource for this uniform buffer.
- L583 _public member_ `uint32 Offset;` — The offset of the uniform buffer's contents in the resource.
- L586 _public member_ `uint32 RangeSize;` — The data range size of uniform buffer's contents in the resource.
- L589 _public member_ `uint8* PersistentlyMappedBuffer;` — When using a persistently mapped buffer this is a pointer to the CPU accessible data.
- L592 _public member_ `uint32 UniqueID;` — Unique ID for state shadowing purposes.
- L595 _public member_ `FOpenGLEUniformBufferDataRef EmulatedBufferData;` — Emulated uniform data for ES2.
- L598 _public member_ `uint32 AllocatedSize;` — The size of the buffer allocated to hold the uniform buffer contents. May be larger than necessary.
- L601 _public member_ `bool bStreamDraw;` — True if the uniform buffer is not used across frames.
- L604 _public member_ `bool bIsEmulatedUniformBuffer;` — True if the uniform buffer is emulated
- L607 _public member_ `bool bOwnsResource;` — True if Resource belongs to this UniformBuffer
- L610 _public prototype_ `FOpenGLUniformBuffer(const FRHIUniformBufferLayout* InLayout);` — Initialization constructor.
- L612 _public prototype_ `void SetGLUniformBufferParams(GLuint InResource, uint32 InOffset, uint8* InPersistentlyMappedBuffer, uint32 InAllocatedSize, FOpenGLEUniformBufferDataRef InEmulatedBuffer, bool bInStreamDraw);`
- L615 _public prototype_ `~FOpenGLUniformBuffer();` — Destructor.
- L619 _public function_ `TArray<TRefCountPtr<FRHIResource>>& GetResourceTable()` — Provides public non-const access to ResourceTable. @todo refactor uniform buffers to perform updates as a member function, so this isn't necessary.
- L621 _public prototype_ `void SetLayoutTable(const void* Contents, EUniformBufferValidation Validation);`

#### class `TOpenGLStreamedBufferArray`  
`template <typename BaseType, uint32 Stride> class TOpenGLStreamedBufferArray`  
_L628-710_
- L632 _public function_ `TOpenGLStreamedBufferArray( void )`
- L633 _public prototype_ `virtual ~TOpenGLStreamedBufferArray( void ) = default;`
- L635 _public function_ `void Init( uint32 InitialBufferSize )`
- L647 _public function_ `void Cleanup( void )`
- L655 _public function_ `uint8* Lock( uint32 DataSize )`
- L695 _public function_ `void Unlock( void )`
- L701 _public function_ `BaseType* GetPendingBuffer( void )`
- L702 _public function_ `uint32 GetPendingOffset( void )`
- L705 _private member_ `TRefCountPtr<BaseType> Buffer[MAX_STREAMED_BUFFERS_IN_ARRAY];`
- L706 _private member_ `uint32 CurrentBufferIndex;`
- L707 _private member_ `uint32 CurrentOffset;`
- L708 _private member_ `uint32 LastOffset;`
- L709 _private member_ `uint32 MinNeededBufferSize;`

#### struct `FOpenGLVertexElement`  
`struct FOpenGLVertexElement`  
_L712-729_
- L714 _public member_ `GLenum Type;`
- L715 _public member_ `GLuint StreamIndex;`
- L716 _public member_ `GLuint Offset;`
- L717 _public member_ `GLuint Size;`
- L718 _public member_ `GLuint Divisor;`
- L719 _public member_ `GLuint HashStride;`
- L720 _public member_ `uint8 bNormalized;`
- L721 _public member_ `uint8 AttributeIndex;`
- L722 _public member_ `uint8 bShouldConvertToFloat;`
- L723 _public member_ `uint8 Padding;`
- L725 _public function_ `FOpenGLVertexElement() : Padding(0)`

#### class `FOpenGLVertexDeclaration`  
`class FOpenGLVertexDeclaration : public FRHIVertexDeclaration`  
_L735-751_
- inherits: `FRHIVertexDeclaration`
- desc: This represents a vertex declaration that hasn't been combined with a specific shader to create a bound shader.
- L739 _public member_ `FOpenGLVertexElements VertexElements;` — Elements of the vertex declaration.
- L741 _public member_ `uint16 StreamStrides[MaxVertexElementCount];`
- L744 _public function_ `FOpenGLVertexDeclaration(const FOpenGLVertexElements& InElements, const uint16* InStrides) : VertexElements(InElements)` — Initialization constructor.
- L750 _public prototype_ `virtual bool GetInitializer(FVertexDeclarationElementList& Init) override final;`

#### class `FOpenGLBoundShaderState`  
`class FOpenGLBoundShaderState : public FRHIBoundShaderState`  
_L758-808_
- inherits: `FRHIBoundShaderState`
- desc: Combined shader state and vertex definition for rendering geometry. Each unique instance consists of a vertex decl, vertex shader, and pixel shader.
- L760 _private prototype_ `static FOpenGLLinkedProgram* FindOrCreateLinkedProgram(FOpenGLVertexShader* VertexShader, FOpenGLPixelShader* PixelShader, FOpenGLGeometryShader* GeometryShader);`
- L764 _public member_ `FCachedBoundShaderStateLink CacheLink;`
- L766 _public member_ `uint16 StreamStrides[MaxVertexElementCount];`
- L768 _public member_ `FOpenGLLinkedProgram* const LinkedProgram;`
- L769 _public member_ `TRefCountPtr<FOpenGLVertexDeclaration> const VertexDeclaration;`
- L770 _public member_ `TRefCountPtr<FOpenGLVertexShader > const VertexShader;`
- L771 _public member_ `TRefCountPtr<FOpenGLPixelShader > const PixelShader;`
- L772 _public member_ `TRefCountPtr<FOpenGLGeometryShader > const GeometryShader;`
- L775 _public prototype_ `FOpenGLBoundShaderState( FOpenGLVertexDeclaration* InVertexDeclarationRHI, FOpenGLVertexShader* InVertexShaderRHI, FOpenGLPixelShader* InPixelShaderRHI, FOpenGLGeometryShader* InGeometryShaderRHI );` — Initialization constructor.
- L782 _public prototype_ `const TBitArray<>& GetTextureNeeds(int32& OutMaxTextureStageUsed);`
- L783 _public prototype_ `const TBitArray<>& GetUAVNeeds(int32& OutMaxUAVUnitUsed) const;`
- L784 _public prototype_ `void GetNumUniformBuffers(int32 NumVertexUniformBuffers[SF_NumGraphicsFrequencies]);`
- L786 _public prototype_ `bool NeedsTextureStage(int32 TextureStageIndex);`
- L787 _public prototype_ `int32 MaxTextureStageUsed();`
- L788 _public prototype_ `bool RequiresDriverInstantiation();`
- L790 _public function_ `FOpenGLVertexShader* GetVertexShader()`
- L796 _public function_ `FOpenGLPixelShader* GetPixelShader()`
- L802 _public function_ `FOpenGLGeometryShader* GetGeometryShader()`
- L807 _public prototype_ `virtual ~FOpenGLBoundShaderState();`

#### class `FTextureEvictionLRU`  
`class FTextureEvictionLRU`  
_L810-837_
- L813 _private typedef_ `typedef TPsoLruCache<FOpenGLTexture*, FOpenGLTexture*> FOpenGLTextureLRUContainer;`
- L814 _private member_ `FCriticalSection TextureLRULock;`
- L816 _private function_ `static FORCEINLINE_DEBUGGABLE FOpenGLTextureLRUContainer& GetLRUContainer()`
- L825 _public function_ `static FORCEINLINE_DEBUGGABLE FTextureEvictionLRU& Get()`
- L830 _public function_ `uint32 Num() const`
- L832 _public prototype_ `void Remove(FOpenGLTexture* TextureBase);`
- L833 _public prototype_ `bool Add(FOpenGLTexture* TextureBase);`
- L834 _public prototype_ `void Touch(FOpenGLTexture* TextureBase);`
- L835 _public prototype_ `void TickEviction();`
- L836 _public prototype_ `FOpenGLTexture* GetLeastRecent();`

#### class `FTextureEvictionParams`  
`class FTextureEvictionParams`  
_L838-883_
- L841 _public prototype_ `FTextureEvictionParams(uint32 NumMips);`
- L842 _public prototype_ `~FTextureEvictionParams();`
- L843 _public member_ `TArray<TArray<uint8>> MipImageData;`
- L845 _public member_ `uint32 bHasRestored : 1;`
- L846 _public member_ `FSetElementId LRUNode;`
- L847 _public member_ `uint32 FrameLastRendered;`
- L850 _public member_ `FAnsiString TextureDebugName;`
- L851 _public function_ `void SetDebugLabelName(const FAnsiString& TextureDebugNameIn)`
- L852 _public function_ `void SetDebugLabelName(const ANSICHAR * TextureDebugNameIn)`
- L853 _public function_ `FAnsiString& GetDebugLabelName()`
- L856 _public function_ `FAnsiCharArray& GetDebugLabelName()`
- L859 _public prototype_ `void SetMipData(uint32 MipIndex, const void* Data, uint32 Bytes);`
- L860 _public prototype_ `void ReleaseMipData(uint32 RetainMips);`
- L862 _public prototype_ `void CloneMipData(const FTextureEvictionParams& Src, uint32 NumMips, int32 SrcOffset, int DstOffset);`
- L864 _public function_ `uint32 GetTotalAllocated() const`
- L874 _public function_ `bool AreAllMipsPresent() const`

#### class `FOpenGLTextureDesc`  
`class FOpenGLTextureDesc`  
_L885-905_
- L888 _public prototype_ `FOpenGLTextureDesc(FRHITextureDesc const& InDesc);`
- L890 _public member_ `GLenum Target = GL_NONE;`
- L891 _public member_ `GLenum Attachment = GL_NONE;`
- L893 _public member_ `uint32 MemorySize = 0;`
- L895 _public member_ `uint8 bCubemap : 1;`
- L896 _public member_ `uint8 bArrayTexture : 1;`
- L897 _public member_ `uint8 bStreamable : 1;`
- L898 _public member_ `uint8 bDepthStencil : 1;`
- L899 _public member_ `uint8 bCanCreateAsEvicted : 1;`
- L900 _public member_ `uint8 bIsPowerOfTwo : 1;`
- L901 _public member_ `uint8 bMultisampleRenderbuffer : 1;`
- L904 _private prototype_ `static bool CanDeferTextureCreation();`

#### class `FOpenGLTextureCreateDesc`  
`class FOpenGLTextureCreateDesc : public FRHITextureCreateDesc, public FOpenGLTextureDesc`  
_L907-915_
- inherits: `FRHITextureCreateDesc,FOpenGLTextureDesc`
- L910 _public function_ `FOpenGLTextureCreateDesc(FRHITextureCreateDesc const& CreateDesc) : FRHITextureCreateDesc(CreateDesc) , FOpenGLTextureDesc(CreateDesc)`

#### class `FOpenGLTexture`  
`class FOpenGLTexture : public FRHITexture, public FOpenGLViewableResource`  
_L917-1111_
- inherits: `FRHITexture,FOpenGLViewableResource`
- L920 _private prototype_ `FOpenGLTexture(FOpenGLTexture const&) = delete;` — Prevent copying
- L921 _private prototype_ `FOpenGLTexture& operator = (FOpenGLTexture const&) = delete;`
- L925 _public prototype_ `explicit FOpenGLTexture(FOpenGLTextureCreateDesc const& CreateDesc);` — Standard constructor.
- L928 _public prototype_ `explicit FOpenGLTexture(FRHICommandListBase& RHICmdList, FOpenGLTextureCreateDesc const& CreateDesc, const AHardwareBuffer_Desc& HardwareBufferDesc, AHardwareBuffer* HardwareBuffer);` — Constructor for external hardware buffer.
- L932 _public prototype_ `explicit FOpenGLTexture(FOpenGLTextureCreateDesc const& CreateDesc, GLuint Resource);` — Constructor for external resources (RHICreateTexture2DFromResource etc).
- L936 _public prototype_ `explicit FOpenGLTexture(FOpenGLTexture& Texture, const FString& Name, EAliasConstructorParam);`
- L938 _public prototype_ `virtual ~FOpenGLTexture();`
- L940 _public prototype_ `void Initialize(FRHICommandListBase& RHICmdList);`
- L941 _public prototype_ `void AliasResources(FOpenGLTexture& Texture);`
- L943 _public function_ `GLuint GetResource()`
- L949 _public function_ `GLuint& GetResourceRef()`
- L958 _public function_ `GLuint GetRawResourceName() const` — GetRawResourceName - A const accessor to the resource name, this could potentially be an evicted resource. It will not trigger the GL resource's creation.
- L965 _public function_ `const GLuint& GetRawResourceNameRef() const` — GetRawResourceNameRef - A const accessor to the resource name, this could potentially be an evicted resource. It will not trigger the GL resource's creation.
- L970 _public function_ `void SetResource(GLuint InResource)`
- L976 _public function_ `bool IsEvicted() const`
- L978 _public function_ `virtual void* GetTextureBaseRHI() override final`
- L987 _public prototype_ `void* Lock(uint32 MipIndex, uint32 ArrayIndex, EResourceLockMode LockMode, uint32& DestStride);` — Locks one of the texture's mip-maps. @return A pointer to the specified texture data.
- L992 _public prototype_ `uint32 GetLockSize(uint32 MipIndex, EResourceLockMode LockMode, uint32& DestStride);` — Returns the size of the memory block that is returned from Lock, threadsafe
- L995 _public prototype_ `void Unlock(uint32 MipIndex, uint32 ArrayIndex);` — Unlocks a previously locked mip-map.
- L998 _public function_ `virtual void* GetNativeResource() const override` — FRHITexture override.  See FRHITexture::GetNativeResource()
- L1008 _public function_ `bool GetAllocatedStorageForMip(uint32 MipIndex, uint32 FaceIndex) const` — Accessors to mark whether or not we have allocated storage for each mip/face. For non-cubemaps FaceIndex should always be zero.
- L1012 _public function_ `void SetAllocatedStorageForMip(uint32 MipIndex, uint32 FaceIndex)`
- L1018 _public function_ `void SetAllocatedStorage(bool bInAllocatedStorage)` — Set allocated storage state for all mip/faces
- L1026 _public prototype_ `void Resolve(uint32 MipIndex, uint32 ArrayIndex);` — Resolved the specified face for a read Lock, for non-renderable, CPU readable surfaces this eliminates the readback inside Lock itself.
- L1029 _public prototype_ `void RestoreEvictedGLResource(bool bAttemptToRetainMips);` — Texture eviction
- L1030 _public prototype_ `bool CanBeEvicted();`
- L1031 _public prototype_ `void TryEvictGLResource();`
- L1032 _public prototype_ `void RemoveEvictionData();`
- L1035 _private prototype_ `static void UpdateTextureStats(FOpenGLTexture* Texture, bool bAllocating);`
- L1037 _private function_ `void TryRestoreGLResource()`
- L1056 _private prototype_ `void DeleteGLResource();`
- L1058 _private prototype_ `void FillGLTextureImage(const FOpenGLTextureFormat& GLFormat, bool bSRGB, uint32 MipIndex, uint32 ArrayIndex, const FUintVector3& MipExtents, const void* BufferOrPBOOffset, size_t ImageSize);`
- L1061 _public function_ `uint32 GetEffectiveSizeZ() const`
- L1072 _private member_ `GLuint Resource = GL_NONE;` — The OpenGL texture resource.
- L1076 _public member_ `GLenum const Target = 0;` — The OpenGL texture target.
- L1079 _public member_ `GLenum const Attachment = 0;` — The OpenGL attachment point. This should always be GL_COLOR_ATTACHMENT0 in case of color buffer, but the actual texture may be attached on other color attachments.
- L1081 _public member_ `TUniquePtr<FTextureEvictionParams> EvictionParamsPtr;`
- L1084 _public member_ `class FOpenGLSamplerState* SamplerState = nullptr;` — Pointer to current sampler state in this unit
- L1086 _public member_ `TArray<TRefCountPtr<FOpenGLPixelBuffer>> PixelBuffers;`
- L1088 _public member_ `bool bInStencilTextureMode = false;`
- L1092 _public member_ `EGLImageKHR HardwareBufferImage;` — The image created from an external hardware buffer.
- L1097 _private member_ `TBitArray<TInlineAllocator<1> > bAllocatedStorage;` — Bitfields marking whether we have allocated storage for each mip
- L1100 _public member_ `uint32 const MemorySize;`
- L1103 _public member_ `uint8 const bIsPowerOfTwo : 1;`
- L1104 _public member_ `uint8 const bCanCreateAsEvicted : 1;`
- L1105 _public member_ `uint8 const bStreamable : 1;`
- L1106 _public member_ `uint8 const bCubemap : 1;`
- L1107 _public member_ `uint8 const bArrayTexture : 1;`
- L1108 _public member_ `uint8 const bDepthStencil : 1;`
- L1109 _public member_ `uint8 const bAlias : 1;`
- L1110 _public member_ `uint8 const bMultisampleRenderbuffer : 1;`

#### enum `FOpenGLTexture::EAliasConstructorParam`  
`enum EAliasConstructorParam`  
_L935-935_
- desc: Constructor for RHICreateAliasedTexture
- L935 _public enumerator_ `enum EAliasConstructorParam { AliasResource }; UE_API explicit FOpenGLTexture(FOpenGLTexture& Texture, const FString& Name, EAliasConstructorParam); UE_API virtual ~FOpenGLTexture(); UE_API void Initialize(FRHICommandListBase& RHICmdList); UE_API void AliasResources(FOpenGLTexture& Texture);` — Constructor for RHICreateAliasedTexture

#### struct `FOpenGLProfiler`  
`struct FOpenGLProfiler`  
_L1113-1168_
- L1144 _public member_ `bool bEnabled = false;`
- L1146 _public member_ `TUniquePtr<FFrame> Current;`
- L1147 _public member_ `TQueue<TUniquePtr<FFrame>> Pending;`
- L1149 _public member_ `TArray<FOpenGLRenderQuery*> QueryPool;`
- L1151 _public member_ `TOptional<uint32> ExternalGPUTime;`
- L1153 _public prototype_ `FOpenGLRenderQuery* GetQuery();`
- L1154 _public prototype_ `FOpenGLRenderQuery* InsertQuery(uint64* Target);`
- L1156 _public prototype_ `uint64 ResolveQuery(uint64 Value, uint64* Target, bool bDisjoint);`
- L1158 _public prototype_ `void Setup();`
- L1159 _public prototype_ `void Shutdown();`
- L1161 _public prototype_ `void EndFrame(FRHIEndFrameArgs const& Args);`
- L1164 _public function_ `template <typename TEventType, typename... TArgs> TEventType& EmplaceEvent(TArgs&&... Args)`

#### struct `FOpenGLProfiler::FCalibration`  
`struct FCalibration`  
_L1115-1126_
- L1118 _public member_ `int64 CPUTimestamp = 0;` — FPlatformTime::Cycles64()
- L1119 _public member_ `int64 CPUFrequency = 0;`
- L1122 _public member_ `int64 GLTimestamp = 0;` — The GL timestamp as queried directly from the driver by the CPU
- L1125 _public member_ `static constexpr int64 GLFrequency = 1'000'000'000;` — Frequency of the GLTimestamp clock

#### struct `FOpenGLProfiler::FFrame`  
`struct FFrame`  
_L1128-1142_
- L1130 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L1131 _public member_ `FCalibration Calibration;`
- L1133 _public member_ `class FOpenGLRenderQuery* EndWorkQuery = nullptr;`
- L1134 _public member_ `UE::RHI::GPUProfiler::FEvent::FFrameBoundary* FrameBoundaryEvent = nullptr;`
- L1139 _public member_ `bool bDisjoint = false;` — True if this frame contained any timestamp queries which the driver flagged as disjoint. If this happens, we discard all the timestamp events from this frame, leaving only the frame boundary, since the timing will be unreliable.
- L1141 _public prototype_ `FFrame(FOpenGLProfiler& Profiler);`

#### class `FOpenGLRenderQuery`  
`class FOpenGLRenderQuery`  
_L1170-1247_
- L1189 _private member_ `} static ActiveQueries;`
- L1194 _private member_ `} static PooledQueries;`
- L1197 _private member_ `FOpenGLRenderQuery** Prev = nullptr;` — Linked list pointers. Used to build a list of "active" queries, i.e. queries that need data to be polled from the GPU.
- L1198 _private member_ `FOpenGLRenderQuery* Next = nullptr;`
- L1200 _private member_ `uint64 Result = 0;`
- L1203 _private member_ `GLuint Resource = 0;` — The query resource.
- L1206 _private member_ `uint64* Target = nullptr;` — Additional data used for profiler timestamps
- L1209 _protected member_ `EType const Type;`
- L1211 _protected member_ `std::atomic<uint8> LastCachedBOPCounter = 0;`
- L1212 _protected member_ `uint8 BOPCounter = 0;`
- L1213 _protected member_ `uint8 TOPCounter = 0;`
- L1216 _public function_ `FOpenGLRenderQuery(EType Type) : Type(Type)`
- L1220 _public prototype_ `~FOpenGLRenderQuery();`
- L1222 _public prototype_ `void AcquireGlQuery();`
- L1223 _public prototype_ `void ReleaseGlQuery();`
- L1225 _public function_ `bool IsLinked() const`
- L1227 _public prototype_ `void Begin();`
- L1228 _public prototype_ `void End(uint64* InTarget = nullptr);`
- L1230 _public function_ `uint64 GetResult() const`
- L1235 _public prototype_ `bool CacheResult(bool bWait);`
- L1237 _public prototype_ `static bool PollQueryResults(FOpenGLRenderQuery* TargetQuery = nullptr);`
- L1238 _public prototype_ `static void Cleanup();`
- L1241 _private prototype_ `void Link();`
- L1242 _private prototype_ `void Unlink();`
- L1244 _private prototype_ `void SetResult(uint64 Value);`
- L1246 _private prototype_ `bool IsCached();`

#### enum `FOpenGLRenderQuery::EType`  
`enum class EType : uint8`  
_L1173-1180_
- L1175 _public enumerator_ `Timestamp`
- L1176 _public enumerator_ `Occlusion`
- L1177 _public enumerator_ `Profiler`
- L1179 _public enumerator_ `Num`

#### struct `FOpenGLRenderQuery::FActiveQueries`  
`struct FActiveQueries`  
_L1184-1189_
- desc: Render queries that should be polled by the RHI thread.
- L1186 _public member_ `FOpenGLRenderQuery* First = nullptr;`
- L1187 _public member_ `FOpenGLRenderQuery* Last = nullptr;`
- L1188 _public member_ `int32 Count = 0;`

#### struct `FOpenGLRenderQuery::FQueryPool`  
`struct FQueryPool : public TStaticArray<TArray<GLuint>, (uint32)EType::Num>`  
_L1191-1194_
- inherits: `TStaticArray<TArray<GLuint>,(uint32)EType::Num>`
- L1193 _public function_ `TArray<GLuint>& operator [](EType InType)`

#### class `FOpenGLRenderQuery_RHI`  
`class FOpenGLRenderQuery_RHI : public FRHIRenderQuery, public FOpenGLRenderQuery`  
_L1249-1262_
- inherits: `FRHIRenderQuery,FOpenGLRenderQuery`
- L1252 _public function_ `FOpenGLRenderQuery_RHI(ERenderQueryType QueryType) : FOpenGLRenderQuery(QueryType == RQT_Occlusion ? EType::Occlusion : EType::Timestamp)`
- L1256 _public function_ `void End_TopOfPipe()`
- L1261 _public prototype_ `bool GetResult(bool bWait, uint64& OutResult);`

#### class `FOpenGLView`  
`class FOpenGLView : public TIntrusiveLinkedList<FOpenGLView>`  
_L1264-1268_
- inherits: `TIntrusiveLinkedList<FOpenGLView>`
- L1267 _public prototype_ `virtual void UpdateView() = 0;`

#### class `FOpenGLUnorderedAccessView`  
`class FOpenGLUnorderedAccessView final : public FRHIUnorderedAccessView, public FOpenGLView`  
_L1270-1304_
- inherits: `FRHIUnorderedAccessView,FOpenGLView`
- L1273 _public prototype_ `FOpenGLUnorderedAccessView(FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc);`
- L1274 _public prototype_ `virtual ~FOpenGLUnorderedAccessView();`
- L1276 _public prototype_ `FOpenGLViewableResource* GetBaseResource() const;`
- L1278 _public prototype_ `void UpdateView() override;`
- L1280 _public member_ `GLuint Resource = 0;`
- L1281 _public member_ `GLuint BufferResource = 0;`
- L1282 _public member_ `GLenum Format = 0;`
- L1283 _public member_ `uint8 UnrealFormat = 0;`
- L1284 _public member_ `uint8 Level = 0;`
- L1286 _public function_ `uint32 GetBufferSize() const`
- L1291 _public function_ `bool IsLayered() const`
- L1296 _public function_ `GLint GetLayer() const`
- L1302 _private prototype_ `void Invalidate();`
- L1303 _private member_ `bool OwnsResource = false;`

#### class `FOpenGLShaderResourceView`  
`class FOpenGLShaderResourceView final : public FRHIShaderResourceView, public FOpenGLView`  
_L1306-1325_
- inherits: `FRHIShaderResourceView,FOpenGLView`
- L1309 _public prototype_ `FOpenGLShaderResourceView(FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc);`
- L1310 _public prototype_ `virtual ~FOpenGLShaderResourceView();`
- L1312 _public prototype_ `FOpenGLViewableResource* GetBaseResource() const;`
- L1314 _public prototype_ `void UpdateView() override;`
- L1317 _public member_ `GLuint Resource = GL_NONE;` — OpenGL texture the buffer is bound with
- L1318 _public member_ `GLenum Target = GL_TEXTURE_BUFFER;`
- L1320 _public member_ `int32 LimitMip = -1;`
- L1323 _private prototype_ `void Invalidate();`
- L1324 _private member_ `bool OwnsResource = false;`

#### class `FOpenGLEventQuery`  
`class FOpenGLEventQuery`  
_L1330-1345_
- desc: A OpenGL event query resource.
- L1334 _public prototype_ `FOpenGLEventQuery();` — Initialization constructor.
- L1335 _public prototype_ `~FOpenGLEventQuery();`
- L1338 _public prototype_ `void IssueEvent();` — Issues an event for the query to poll.
- L1341 _public prototype_ `void WaitForCompletion();` — Waits for the event query to finish.
- L1344 _private member_ `UGLsync Sync = {};`

#### class `FOpenGLViewport`  
`class FOpenGLViewport : public FRHIViewport`  
_L1347-1395_
- inherits: `FRHIViewport`
- L1351 _public prototype_ `FOpenGLViewport(class FOpenGLDynamicRHI* InOpenGLRHI,void* InWindowHandle,uint32 InSizeX,uint32 InSizeY,bool bInIsFullscreen,EPixelFormat PreferredPixelFormat);`
- L1352 _public prototype_ `~FOpenGLViewport();`
- L1354 _public prototype_ `void Resize(uint32 InSizeX,uint32 InSizeY,bool bInIsFullscreen);`
- L1357 _public function_ `FIntPoint GetSizeXY() const` — Accessors.
- L1358 _public function_ `FOpenGLTexture* GetBackBuffer() const`
- L1359 _public function_ `bool IsFullscreen( void ) const`
- L1361 _public prototype_ `virtual void WaitForFrameEventCompletion() override;`
- L1362 _public prototype_ `virtual void IssueFrameEvent() override;`
- L1364 _public prototype_ `virtual void* GetNativeWindow(void** AddParam) const override;`
- L1366 _public function_ `struct FPlatformOpenGLContext* GetGLContext() const`
- L1367 _public function_ `FOpenGLDynamicRHI* GetOpenGLRHI() const`
- L1369 _public function_ `struct FPlatformOpenGLSurfaceContext* GetGLSurfaceContext() const`
- L1371 _public function_ `virtual void SetCustomPresent(FRHICustomPresent* InCustomPresent) override`
- L1375 _public function_ `FRHICustomPresent* GetCustomPresent() const`
- L1377 _public function_ `void* GetWindowHandle()`
- L1383 _private member_ `FOpenGLDynamicRHI* OpenGLRHI;`
- L1384 _private member_ `struct FPlatformOpenGLContext* OpenGLContext;`
- L1385 _private member_ `FPlatformOpenGLSurfaceContext* OpenGLSurfaceContext;`
- L1386 _private member_ `uint32 SizeX;`
- L1387 _private member_ `uint32 SizeY;`
- L1388 _private member_ `bool bIsFullscreen;`
- L1389 _private member_ `EPixelFormat PixelFormat;`
- L1390 _private member_ `bool bIsValid;`
- L1391 _private member_ `TRefCountPtr<FOpenGLTexture> BackBuffer;`
- L1392 _private member_ `TUniquePtr<FOpenGLEventQuery> FrameSyncEvent;`
- L1393 _private member_ `FCustomPresentRHIRef CustomPresent;`
- L1394 _private member_ `void* WindowHandle;`

#### class `FOpenGLGPUFence`  
`class FOpenGLGPUFence final : public FRHIGPUFence`  
_L1397-1433_
- inherits: `FRHIGPUFence`
- L1415 _private member_ `static TQueue<FGLSync, EQueueMode::SingleThreaded> ActiveSyncs;`
- L1416 _private prototype_ `static void PollFencesUntil(FGraphEvent* Target);`
- L1418 _private member_ `FGraphEventRef Event;`
- L1421 _public prototype_ `FOpenGLGPUFence(FName InName);`
- L1423 _public prototype_ `void Clear() override;`
- L1424 _public prototype_ `bool Poll() const override;`
- L1425 _public prototype_ `void Wait(FRHICommandListImmediate& RHICmdList, FRHIGPUMask GPUMask) const override;`
- L1427 _public prototype_ `void WriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList);`
- L1429 _public function_ `static void PollFences()`

#### struct `FOpenGLGPUFence::FGLSync`  
`struct FGLSync`  
_L1400-1413_
- L1403 _public member_ `FGraphEventRef Event;` — The graph event to trigger when the sync is resolved.
- L1406 _public member_ `UGLsync GLSync;` — The GL API sync object to poll / wait on.
- L1408 _public prototype_ `FGLSync() = default;`
- L1409 _public function_ `FGLSync(FGraphEventRef Event, UGLsync GLSync) : Event(MoveTemp(Event)) , GLSync(GLSync)`

#### class `FOpenGLStagingBuffer`  
`class FOpenGLStagingBuffer final : public FRHIStagingBuffer`  
_L1435-1459_
- inherits: `FRHIStagingBuffer`
- L1439 _public function_ `FOpenGLStagingBuffer() : FRHIStagingBuffer()`
- L1447 _public prototype_ `void *Lock(uint32 Offset, uint32 NumBytes) override;` — Locks the shadow of VertexBuffer for read. This will stall the RHI thread.
- L1450 _public prototype_ `void Unlock() override;` — Unlocks the shadow. This is an error if it was not locked previously.
- L1452 _public function_ `uint64 GetGPUSizeBytes() const override`
- L1454 _private prototype_ `void Initialize();`
- L1456 _private member_ `GLuint ShadowBuffer;`
- L1457 _private member_ `uint32 ShadowSize;`
- L1458 _private member_ `void* Mapping;`

#### struct `TOpenGLResourceTraits`  
`template<class T> struct TOpenGLResourceTraits`  
_L1462-1464_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIGPUFence>`  
_L1466-1469_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIStagingBuffer>`  
_L1471-1474_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIVertexDeclaration>`  
_L1476-1479_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIVertexShader>`  
_L1481-1484_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIGeometryShader>`  
_L1486-1489_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIPixelShader>`  
_L1491-1494_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIComputeShader>`  
_L1496-1499_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIBoundShaderState>`  
_L1501-1504_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIRenderQuery>`  
_L1506-1509_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIUniformBuffer>`  
_L1511-1514_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIBuffer>`  
_L1516-1519_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIShaderResourceView>`  
_L1521-1524_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIUnorderedAccessView>`  
_L1526-1529_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIViewport>`  
_L1532-1535_
- L1468 _public typedef_ `typedef FOpenGLGPUFence TConcreteType;`
- L1473 _public typedef_ `typedef FOpenGLStagingBuffer TConcreteType;`
- L1478 _public typedef_ `typedef FOpenGLVertexDeclaration TConcreteType;`
- L1483 _public typedef_ `typedef FOpenGLVertexShader TConcreteType;`
- L1488 _public typedef_ `typedef FOpenGLGeometryShader TConcreteType;`
- L1493 _public typedef_ `typedef FOpenGLPixelShader TConcreteType;`
- L1498 _public typedef_ `typedef FOpenGLComputeShader TConcreteType;`
- L1503 _public typedef_ `typedef FOpenGLBoundShaderState TConcreteType;`
- L1508 _public typedef_ `typedef FOpenGLRenderQuery_RHI TConcreteType;`
- L1513 _public typedef_ `typedef FOpenGLUniformBuffer TConcreteType;`
- L1518 _public typedef_ `typedef FOpenGLBuffer TConcreteType;`
- L1523 _public typedef_ `typedef FOpenGLShaderResourceView TConcreteType;`
- L1528 _public typedef_ `typedef FOpenGLUnorderedAccessView TConcreteType;`
- L1534 _public typedef_ `typedef FOpenGLViewport TConcreteType;`

#### Free symbols / members of external scopes

- L34 _macro_ `#define UE_API OPENGLDRV_API`
- L39 _typedef_ `typedef TArray<ANSICHAR> FAnsiCharArray;`
- L41 _namespace_ `namespace OpenGLConsoleVariables`
- L43 _externvar_ `extern int32 bUseMapBuffer;` (scope `OpenGLConsoleVariables`)
- L44 _externvar_ `extern int32 MaxSubDataSize;` (scope `OpenGLConsoleVariables`)
- L45 _externvar_ `extern int32 bUseStagingBuffer;` (scope `OpenGLConsoleVariables`)
- L46 _externvar_ `extern int32 bUseBufferDiscard;` (scope `OpenGLConsoleVariables`)
- L50 _macro_ `#define RESTRICT_SUBDATA_SIZE 1`
- L52 _macro_ `#define RESTRICT_SUBDATA_SIZE 0`
- L55 _namespace_ `namespace OpenGLBufferStats`
- L57 _prototype_ `void UpdateUniformBufferStats(int64 BufferSize, bool bAllocating);` (scope `OpenGLBufferStats`)
- L58 _prototype_ `void UpdateBufferStats(const FRHIBufferDesc& BufferDesc, bool bAllocating);` (scope `OpenGLBufferStats`)
- L63 _macro_ `#define OPENGLRHI_DETAILED_STATS 0` — Extra stats for finer-grained timing They shouldn't always be on, as they may impact overall performance
- L67 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("MapBuffer time"),STAT_OpenGLMapBufferTime,STATGROUP`
- L68 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UnmapBuffer time"),STAT_OpenGLUnmapBufferTime,STATGRO`
- L69 _macro_ `#define SCOPE_CYCLE_COUNTER_DETAILED(Stat) SCOPE_CYCLE_COUNTER(Stat)`
- L70 _macro_ `#define DETAILED_QUICK_SCOPE_CYCLE_COUNTER(x) QUICK_SCOPE_CYCLE_COUNTER(x)`
- L72 _macro_ `#define SCOPE_CYCLE_COUNTER_DETAILED(Stat)`
- L73 _macro_ `#define DETAILED_QUICK_SCOPE_CYCLE_COUNTER(x)`
- L76 _macro_ `#define GLDEBUG_LABELS_ENABLED (!UE_BUILD_SHIPPING)`
- L160 _function_ `` (scope `TOpenGLBuffer::TOpenGLBuffer`)
- L183 _function_ `RHICmdList->EnqueueLambda([Lambda = MoveTemp(InitLambda)](FRHICommandListBase&) { Lambda(); });` (scope `TOpenGLBuffer::TOpenGLBuffer`)
- L554 _typedef_ `typedef TOpenGLBuffer<FOpenGLBasePixelBuffer> FOpenGLPixelBuffer;`
- L555 _typedef_ `typedef TOpenGLBuffer<FOpenGLBaseBuffer > FOpenGLBuffer;`
- L574 _typedef_ `typedef TRefCountPtr<FOpenGLEUniformBufferData> FOpenGLEUniformBufferDataRef;`
- L624 _macro_ `#define MAX_STREAMED_BUFFERS_IN_ARRAY 2 // must be > 1!`
- L625 _macro_ `#define MIN_DRAWS_IN_SINGLE_BUFFER 16`
- L732 _typedef_ `typedef TArray<FOpenGLVertexElement,TFixedAllocator<MaxVertexElementCount> > FOpenGLVertexElements;` — Convenience typedef: preallocated array of OpenGL input element descriptions.
- L1327 _prototype_ `void ReleaseOpenGLFramebuffers(FRHITexture* TextureRHI);`

### `Source/Runtime/OpenGLDrv/Private/OpenGLShaders.h` (Private)


#### enum `EOpenGLShaderTargetPlatform`  
`enum EOpenGLShaderTargetPlatform`  
_L12-18_
- L14 _public enumerator_ `OGLSTP_Unknown`
- L15 _public enumerator_ `OGLSTP_Desktop`
- L16 _public enumerator_ `OGLSTP_Android`
- L17 _public enumerator_ `OGLSTP_iOS`

#### struct `FOpenGLShaderDeviceCapabilities`  
`struct FOpenGLShaderDeviceCapabilities`  
_L23-33_
- desc: GL device capabilities for generating GLSL compilable on platform with described capabilities
- L25 _public member_ `EOpenGLShaderTargetPlatform TargetPlatform;`
- L26 _public member_ `EShaderPlatform MaxRHIShaderPlatform;`
- L27 _public member_ `bool bRequiresARMShaderFramebufferFetchDepthStencilUndef;`
- L28 _public member_ `GLint MaxVaryingVectors;`
- L29 _public member_ `bool bRequiresDisabledEarlyFragmentTests;`
- L30 _public member_ `bool bRequiresReadOnlyBuffersWorkaround;`
- L31 _public member_ `bool bRequiresPreciseQualifierWorkaround;`
- L32 _public member_ `bool bRequiresControlFlowOptimizerWorkaround;`

#### Free symbols / members of external scopes

- L40 _prototype_ `void GetCurrentOpenGLShaderDeviceCapabilities(FOpenGLShaderDeviceCapabilities& Capabilities);` — Gets the GL device capabilities for the current device. @param Capabilities [out] The current platform's capabilities on device for shader compiling
- L54 _prototype_ `void GLSLToDeviceCompatibleGLSL(FAnsiCharArray& GlslCodeOriginal, const FString& ShaderName, GLenum TypeEnum, const FOpenGLShaderDeviceCapabilities& Capabilities, FAnsiCharArray& GlslCode);` — Processes the GLSL output of the shader cross compiler to get GLSL that can be compiled on a platform with the specified capabilities. Works around inconsistencies between OpenGL implementations, including lack of support for certain extensions and drivers with non-conformant behavior. @param GlslCodeOriginal - [in,out] GLSL output from shader cross compiler to be modified.  Process is destructive; pass in a copy if still need original! @param ShaderName - [in] Shader name @param TypeEnum - [in] Type of shader (GL_[VERTEX, FRAGMENT, GEOMETRY, TESS_CONTROL, TESS_EVALUATION]_SHADER) @param Capabilities - [in] GL Device capabilities @param GlslCode - [out] Compilable GLSL
- L58 _prototype_ `extern "C" void PE_AppendCString(TArray<ANSICHAR> & Dest, const ANSICHAR * Source)` — make some anon ns functions available to platform extensions
- L59 _prototype_ `extern "C" void PE_ReplaceCString(TArray<ANSICHAR> & Dest, const ANSICHAR * Source, const ANSICHAR * Replacement)`

### `Source/Runtime/OpenGLDrv/Private/OpenGLState.h` (Private)


#### struct `FOpenGLSamplerStateData`  
`struct FOpenGLSamplerStateData`  
_L25-64_
- L42 _public member_ `GLint WrapS;`
- L43 _public member_ `GLint WrapT;`
- L44 _public member_ `GLint WrapR;`
- L45 _public member_ `GLint LODBias;`
- L46 _public member_ `GLint MagFilter;`
- L47 _public member_ `GLint MinFilter;`
- L48 _public member_ `GLint MaxAnisotropy;`
- L49 _public member_ `GLint CompareMode;`
- L50 _public member_ `GLint CompareFunc;`
- L52 _public function_ `FOpenGLSamplerStateData() : WrapS(GL_REPEAT) , WrapT(GL_REPEAT) , WrapR(GL_REPEAT) , LODBias(0) , MagFilter(GL_NEAREST) , MinFilter(GL_NEAREST) , MaxAnisotropy(1) , CompareMode(GL_NONE) , CompareFunc(GL_ALWAYS)`

#### enum `FOpenGLSamplerStateData::EGLSamplerData`  
`enum EGLSamplerData`  
_L28-40_
- desc: These enum is just used to count the number of members in this struct
- L30 _public enumerator_ `EGLSamplerData_WrapS`
- L31 _public enumerator_ `EGLSamplerData_WrapT`
- L32 _public enumerator_ `EGLSamplerData_WrapR`
- L33 _public enumerator_ `EGLSamplerData_LODBias`
- L34 _public enumerator_ `EGLSamplerData_MagFilter`
- L35 _public enumerator_ `EGLSamplerData_MinFilter`
- L36 _public enumerator_ `EGLSamplerData_MaxAniso`
- L37 _public enumerator_ `EGLSamplerData_CompareMode`
- L38 _public enumerator_ `EGLSamplerData_CompareFunc`
- L39 _public enumerator_ `EGLSamplerData_Num`

#### class `FOpenGLSamplerState`  
`class FOpenGLSamplerState : public FRHISamplerState`  
_L66-73_
- inherits: `FRHISamplerState`
- L69 _public member_ `GLuint Resource;`
- L70 _public member_ `FOpenGLSamplerStateData Data;`
- L72 _public prototype_ `~FOpenGLSamplerState();`

#### struct `FOpenGLRasterizerStateData`  
`struct FOpenGLRasterizerStateData`  
_L75-82_
- L77 _public member_ `GLenum FillMode = GL_FILL;`
- L78 _public member_ `GLenum CullMode = GL_NONE;`
- L79 _public member_ `float DepthBias = 0.0f;`
- L80 _public member_ `float SlopeScaleDepthBias = 0.0f;`
- L81 _public member_ `ERasterizerDepthClipMode DepthClipMode = ERasterizerDepthClipMode::DepthClip;`

#### class `FOpenGLRasterizerState`  
`class FOpenGLRasterizerState : public FRHIRasterizerState`  
_L84-90_
- inherits: `FRHIRasterizerState`
- L87 _public prototype_ `virtual bool GetInitializer(FRasterizerStateInitializerRHI& Init) override final;`
- L89 _public member_ `FOpenGLRasterizerStateData Data;`

#### struct `FOpenGLDepthStencilStateData`  
`struct FOpenGLDepthStencilStateData`  
_L92-130_
- L94 _public member_ `bool bZEnable;`
- L95 _public member_ `bool bZWriteEnable;`
- L96 _public member_ `GLenum ZFunc;`
- L99 _public member_ `bool bStencilEnable;`
- L100 _public member_ `bool bTwoSidedStencilMode;`
- L101 _public member_ `GLenum StencilFunc;`
- L102 _public member_ `GLenum StencilFail;`
- L103 _public member_ `GLenum StencilZFail;`
- L104 _public member_ `GLenum StencilPass;`
- L105 _public member_ `GLenum CCWStencilFunc;`
- L106 _public member_ `GLenum CCWStencilFail;`
- L107 _public member_ `GLenum CCWStencilZFail;`
- L108 _public member_ `GLenum CCWStencilPass;`
- L109 _public member_ `uint32 StencilReadMask;`
- L110 _public member_ `uint32 StencilWriteMask;`
- L112 _public function_ `FOpenGLDepthStencilStateData() : bZEnable(false) , bZWriteEnable(true) , ZFunc(GL_LESS) , bStencilEnable(false) , bTwoSidedStencilMode(false) , StencilFunc(GL_ALWAYS) , StencilFail(GL_KEEP) , StencilZFail(GL_KEEP) , StencilPass(GL_KEEP) , CCWStencilFunc(GL_ALWAYS) , CCWStencilFail(GL_KEEP) , CCWStencilZFail(GL_KEEP) , CCWStencilPass(GL_KEEP) , StencilReadMask(0xFFFFFFFF) , StencilWriteMask(0xFFFFFFFF)`

#### class `FOpenGLDepthStencilState`  
`class FOpenGLDepthStencilState : public FRHIDepthStencilState`  
_L132-138_
- inherits: `FRHIDepthStencilState`
- L135 _public prototype_ `virtual bool GetInitializer(FDepthStencilStateInitializerRHI& Init) override final;`
- L137 _public member_ `FOpenGLDepthStencilStateData Data;`

#### struct `FOpenGLBlendStateData`  
`struct FOpenGLBlendStateData`  
_L140-182_
- L158 _public member_ `TStaticArray<FRenderTarget,MaxSimultaneousRenderTargets> RenderTargets;`
- L160 _public member_ `bool bUseAlphaToCoverage;`
- L162 _public function_ `FOpenGLBlendStateData()`

#### struct `FOpenGLBlendStateData::FRenderTarget`  
`struct FRenderTarget`  
_L142-156_
- L144 _public member_ `bool bAlphaBlendEnable;`
- L145 _public member_ `GLenum ColorBlendOperation;`
- L146 _public member_ `GLenum ColorSourceBlendFactor;`
- L147 _public member_ `GLenum ColorDestBlendFactor;`
- L148 _public member_ `bool bSeparateAlphaBlendEnable;`
- L149 _public member_ `GLenum AlphaBlendOperation;`
- L150 _public member_ `GLenum AlphaSourceBlendFactor;`
- L151 _public member_ `GLenum AlphaDestBlendFactor;`
- L152 _public member_ `uint32 ColorWriteMaskR : 1;`
- L153 _public member_ `uint32 ColorWriteMaskG : 1;`
- L154 _public member_ `uint32 ColorWriteMaskB : 1;`
- L155 _public member_ `uint32 ColorWriteMaskA : 1;`

#### class `FOpenGLBlendState`  
`class FOpenGLBlendState : public FRHIBlendState`  
_L184-196_
- inherits: `FRHIBlendState`
- L186 _private member_ `FBlendStateInitializerRHI RHIInitializer;`
- L188 _public function_ `FOpenGLBlendState(const FBlendStateInitializerRHI& Initializer) : RHIInitializer(Initializer)`
- L189 _public function_ `virtual bool GetInitializer(FBlendStateInitializerRHI& Init) override final`
- L195 _public member_ `FOpenGLBlendStateData Data;`

#### struct `FTextureStage`  
`struct FTextureStage`  
_L198-218_
- L200 _public member_ `class FOpenGLTexture* Texture;`
- L201 _public member_ `class FOpenGLShaderResourceView* SRV;`
- L202 _public member_ `GLenum Target;`
- L203 _public member_ `GLuint Resource;`
- L204 _public member_ `int32 LimitMip;`
- L205 _public member_ `bool bHasMips;`
- L206 _public member_ `int32 NumMips;`
- L208 _public function_ `FTextureStage() : Texture(NULL) , SRV(NULL) , Target(GL_NONE) , Resource(0) , LimitMip(-1) , bHasMips(false) , NumMips(0)`

#### struct `FUAVStage`  
`struct FUAVStage`  
_L220-238_
- L222 _public member_ `GLenum Format;`
- L223 _public member_ `GLuint Resource;`
- L224 _public member_ `GLenum Access;`
- L225 _public member_ `GLint Layer;`
- L226 _public member_ `bool bLayered;`
- L227 _public member_ `GLint Level;`
- L229 _public function_ `FUAVStage() : Format(GL_NONE) , Resource(0) , Access(GL_READ_WRITE) , Layer(0) , bLayered(false) , Level(0)`

#### struct `FOpenGLCachedAttr`  
`struct FOpenGLCachedAttr`  
_L242-260_
- L244 _public member_ `GLuint Size;`
- L245 _public member_ `GLenum Type;`
- L246 _public member_ `GLuint StreamOffset;`
- L247 _public member_ `GLuint StreamIndex;`
- L248 _public member_ `GLboolean bNormalized;`
- L249 _public member_ `GLboolean bShouldConvertToFloat;`
- L251 _public function_ `FOpenGLCachedAttr() : Size(), Type(0), StreamOffset(), StreamIndex(0xFFFFFFFF), bNormalized(), bShouldConvertToFloat()`

#### struct `FOpenGLStream`  
`struct FOpenGLStream`  
_L262-275_
- L264 _public member_ `GLuint VertexBufferResource;`
- L265 _public member_ `uint32 Stride;`
- L266 _public member_ `uint32 Offset;`
- L267 _public member_ `uint32 Divisor;`
- L269 _public function_ `FOpenGLStream() : VertexBufferResource(0) , Stride(0) , Offset(0) , Divisor(0)`

#### struct `FOpenGLCommonState`  
`struct FOpenGLCommonState`  
_L279-313_
- L281 _public member_ `TArray<FTextureStage> Textures;`
- L282 _public member_ `TArray<FOpenGLSamplerState*> SamplerStates;`
- L283 _public member_ `TArray<FUAVStage> UAVs;`
- L285 _public function_ `FOpenGLCommonState()`
- L288 _public function_ `virtual ~FOpenGLCommonState()`
- L295 _public function_ `virtual void InitializeResources(int32 NumCombinedTextures, int32 NumCombinedUAVUnits)` — NumCombinedTextures must be greater than or equal to FOpenGL::GetMaxCombinedTextureImageUnits() NumCombinedUAVUnits must be greater than or equal to FOpenGL::GetMaxCombinedUAVUnits()
- L307 _public function_ `virtual void CleanupResources()`

#### struct `FOpenGLContextState`  
`struct FOpenGLContextState final : public FOpenGLCommonState`  
_L315-418_
- inherits: `FOpenGLCommonState`
- L317 _public member_ `FOpenGLRasterizerStateData RasterizerState;`
- L318 _public member_ `FOpenGLDepthStencilStateData DepthStencilState;`
- L319 _public member_ `uint32 StencilRef;`
- L320 _public member_ `FOpenGLBlendStateData BlendState;`
- L321 _public member_ `GLuint Framebuffer;`
- L322 _public member_ `uint32 RenderTargetWidth;`
- L323 _public member_ `uint32 RenderTargetHeight;`
- L324 _public member_ `GLuint OcclusionQuery;`
- L325 _public member_ `GLuint Program;`
- L326 _public member_ `GLuint UniformBuffers[CrossCompiler::NUM_SHADER_STAGES*OGL_MAX_UNIFORM_BUFFER_BINDINGS];`
- L327 _public member_ `GLuint UniformBufferOffsets[CrossCompiler::NUM_SHADER_STAGES*OGL_MAX_UNIFORM_BUFFER_BINDINGS];`
- L328 _public member_ `TArray<FOpenGLSamplerState*> CachedSamplerStates;`
- L329 _public member_ `GLenum ActiveTexture;`
- L330 _public member_ `bool bScissorEnabled;`
- L331 _public member_ `FIntRect Scissor;`
- L332 _public member_ `FIntRect Viewport;`
- L333 _public member_ `float DepthMinZ;`
- L334 _public member_ `float DepthMaxZ;`
- L335 _public member_ `GLuint ArrayBufferBound;`
- L336 _public member_ `GLuint ElementArrayBufferBound;`
- L337 _public member_ `GLuint StorageBufferBound;`
- L338 _public member_ `GLuint PixelUnpackBufferBound;`
- L339 _public member_ `GLuint UniformBufferBound;`
- L340 _public member_ `FLinearColor ClearColor;`
- L341 _public member_ `uint16 ClearStencil;`
- L342 _public member_ `float ClearDepth;`
- L343 _public member_ `int32 FirstNonzeroRenderTarget;`
- L344 _public member_ `bool bAlphaToCoverageEnabled;`
- L345 _public member_ `bool bNonCoherentFramebufferFetchEnabled;`
- L347 _public member_ `FOpenGLVertexDeclaration* VertexDecl;`
- L348 _public member_ `FOpenGLCachedAttr VertexAttrs[NUM_OPENGL_VERTEX_STREAMS];`
- L349 _public member_ `FOpenGLStream VertexStreams[NUM_OPENGL_VERTEX_STREAMS];`
- L351 _public member_ `uint32 ActiveStreamMask;`
- L352 _public member_ `uint32 VertexAttrs_EnabledBits;`
- L353 _public function_ `FORCEINLINE bool GetVertexAttrEnabled(int32 Index) const`
- L358 _public function_ `FORCEINLINE void SetVertexAttrEnabled(int32 Index, bool bEnable)`
- L370 _public member_ `uint32 ActiveUAVMask;`
- L372 _public function_ `FOpenGLContextState() : StencilRef(0) , Framebuffer(0) , Program(0) , ActiveTexture(GL_TEXTURE0) , bScissorEnabled(false) , DepthMinZ(0.0f) , DepthMaxZ(1.0f) , ArrayBufferBound(0) , ElementArrayBufferBound(0) , StorageBufferBound(0) , PixelUnpackBufferBound(0) , UniformBufferBound(0) , ClearColor(-1, -1, -1, -1) , ClearStencil(0xFFFF) , ClearDepth(-1.0f) , FirstNonzeroRenderTarget(0) , bAlphaToCoverageEnabled(false) , bNonCoherentFramebufferFetchEnabled(false) , VertexDecl(0) , VertexAttrs() , VertexStreams() , ActiveStreamMask(0) , VertexAttrs_EnabledBits(0) , ActiveUAVMask(0)`
- L404 _public function_ `virtual void InitializeResources(int32 NumCombinedTextures, int32 NumCombinedUAVUnits) override`
- L413 _public function_ `virtual void CleanupResources() override`

#### struct `FOpenGLRHIState`  
`struct FOpenGLRHIState final : public FOpenGLCommonState`  
_L420-541_
- inherits: `FOpenGLCommonState`
- L422 _public member_ `FOpenGLRasterizerStateData RasterizerState;`
- L423 _public member_ `FOpenGLDepthStencilStateData DepthStencilState;`
- L424 _public member_ `uint32 StencilRef;`
- L425 _public member_ `FOpenGLBlendStateData BlendState;`
- L426 _public member_ `GLuint Framebuffer;`
- L427 _public member_ `bool bScissorEnabled;`
- L428 _public member_ `FIntRect Scissor;`
- L429 _public member_ `FIntRect Viewport;`
- L430 _public member_ `float DepthMinZ;`
- L431 _public member_ `float DepthMaxZ;`
- L432 _public member_ `GLuint ZeroFilledDummyUniformBuffer;`
- L433 _public member_ `uint32 RenderTargetWidth;`
- L434 _public member_ `uint32 RenderTargetHeight;`
- L435 _public member_ `bool bAlphaToCoverageEnabled;`
- L438 _public member_ `int32 NumRenderingSamples;` — Pending framebuffer setup
- L439 _public member_ `int32 FirstNonzeroRenderTarget;`
- L440 _public member_ `FOpenGLTexture* RenderTargets[MaxSimultaneousRenderTargets];`
- L441 _public member_ `uint32 RenderTargetMipmapLevels[MaxSimultaneousRenderTargets];`
- L442 _public member_ `uint32 RenderTargetArrayIndex[MaxSimultaneousRenderTargets];`
- L443 _public member_ `FOpenGLTexture* DepthStencil;`
- L444 _public member_ `ERenderTargetStoreAction StencilStoreAction;`
- L445 _public member_ `uint32 DepthTargetWidth;`
- L446 _public member_ `uint32 DepthTargetHeight;`
- L447 _public member_ `bool bFramebufferSetupInvalid;`
- L450 _public member_ `FOpenGLStream DynamicVertexStream;` — Information about pending BeginDraw[Indexed]PrimitiveUP calls.
- L451 _public member_ `uint32 NumVertices;`
- L452 _public member_ `uint32 PrimitiveType;`
- L453 _public member_ `uint32 NumPrimitives;`
- L454 _public member_ `uint32 MinVertexIndex;`
- L455 _public member_ `uint32 IndexDataStride;`
- L457 _public member_ `FOpenGLStream Streams[NUM_OPENGL_VERTEX_STREAMS];`
- L460 _public member_ `FOpenGLLinkedProgram* LinkedProgramAndDirtyFlag;` — we null this when the we dirty PackedGlobalUniformDirty. Thus we can skip all of CommitNonComputeShaderConstants if it matches the current program
- L461 _public member_ `FOpenGLShaderParameterCache* ShaderParameters;`
- L463 _public member_ `TRefCountPtr<FOpenGLBoundShaderState> BoundShaderState;`
- L464 _public member_ `TRefCountPtr<FOpenGLComputeShader> CurrentComputeShader;`
- L470 _public member_ `FRHIUniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE];` — Track the currently bound uniform buffers.
- L471 _public member_ `uint32 BoundUniformBuffersDynamicOffset[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE];`
- L474 _public member_ `bool bAnyDirtyRealUniformBuffers[SF_NumStandardFrequencies];` — Array to track if any real (not emulated) uniform buffers have been bound since the last draw call
- L476 _public member_ `bool bAnyDirtyGraphicsUniformBuffers;` — Bit array to track which uniform buffers have changed since the last draw call.
- L477 _public member_ `uint16 DirtyUniformBuffers[SF_NumStandardFrequencies];`
- L480 _public member_ `uint32 UpVertexBufferBytes;` — Used for if(!FOpenGL::SupportsFastBufferData())
- L481 _public member_ `uint32 UpIndexBufferBytes;`
- L482 _public member_ `uint32 UpStride;`
- L483 _public member_ `void* UpVertexBuffer;`
- L484 _public member_ `void* UpIndexBuffer;`
- L486 _public function_ `FOpenGLRHIState() : StencilRef(0) , Framebuffer(0) , bScissorEnabled(false) , DepthMinZ(0.0f) , DepthMaxZ(1.0f) , ZeroFilledDummyUniformBuffer(0) , RenderTargetWidth(0) , RenderTargetHeight(0) , bAlphaToCoverageEnabled(false) , NumRenderingSamples(1) , FirstNonzeroRenderTarget(-1) , DepthStencil(0) , StencilStoreAction(ERenderTargetStoreAction::ENoAction) , DepthTargetWidth(0) , DepthTargetHeight(0) , bFramebufferSetupInvalid(true) , NumVertices(0) , PrimitiveType(0) , NumPrimitives(0) , MinVertexIndex(0) , IndexDataStride(0) , LinkedProgramAndDirtyFlag(nullptr) , ShaderParameters(NULL) , BoundShaderState(NULL) , CurrentComputeShader(NULL) , UpVertexBufferBytes(0) , UpIndexBufferBytes(0) , UpVertexBuffer(0) , UpIndexBuffer(0)`
- L526 _public function_ `~FOpenGLRHIState()`
- L531 _public prototype_ `virtual void InitializeResources(int32 NumCombinedTextures, int32 NumComputeUAVUnits) override;`
- L533 _public function_ `virtual void CleanupResources() override`

#### enum `FOpenGLRHIState::(anonymous)`  
`enum`  
_L467-467_
- desc: The RHI does not allow more than 14 constant buffers per shader stage due to D3D11 limits.

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHISamplerState>`  
_L544-547_
- L546 _public typedef_ `typedef FOpenGLSamplerState TConcreteType;`
- L551 _public typedef_ `typedef FOpenGLRasterizerState TConcreteType;`
- L556 _public typedef_ `typedef FOpenGLDepthStencilState TConcreteType;`
- L561 _public typedef_ `typedef FOpenGLBlendState TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIRasterizerState>`  
_L549-552_
- L546 _public typedef_ `typedef FOpenGLSamplerState TConcreteType;`
- L551 _public typedef_ `typedef FOpenGLRasterizerState TConcreteType;`
- L556 _public typedef_ `typedef FOpenGLDepthStencilState TConcreteType;`
- L561 _public typedef_ `typedef FOpenGLBlendState TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIDepthStencilState>`  
_L554-557_
- L546 _public typedef_ `typedef FOpenGLSamplerState TConcreteType;`
- L551 _public typedef_ `typedef FOpenGLRasterizerState TConcreteType;`
- L556 _public typedef_ `typedef FOpenGLDepthStencilState TConcreteType;`
- L561 _public typedef_ `typedef FOpenGLBlendState TConcreteType;`

#### struct `TOpenGLResourceTraits`  
`template<> struct TOpenGLResourceTraits<FRHIBlendState>`  
_L559-562_
- L546 _public typedef_ `typedef FOpenGLSamplerState TConcreteType;`
- L551 _public typedef_ `typedef FOpenGLRasterizerState TConcreteType;`
- L556 _public typedef_ `typedef FOpenGLDepthStencilState TConcreteType;`
- L561 _public typedef_ `typedef FOpenGLBlendState TConcreteType;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define ZERO_FILLED_DUMMY_UNIFORM_BUFFER_SIZE 65536`
- L239 _macro_ `#define FOpenGLCachedAttr_Invalid (void*)(UPTRINT)0xFFFFFFFF`
- L240 _macro_ `#define FOpenGLCachedAttr_SingleVertex (void*)(UPTRINT)0xFFFFFFFE`
- L277 _macro_ `#define NUM_OPENGL_VERTEX_STREAMS 16`
- L467 _enumerator_ `enum { MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE = 14 }; FRHIUniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE]; uint32 BoundUniformBuffersDynamicOffset[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE]; bool bAnyDirtyRealUniformBuffers[SF_NumStandardFrequencies];` (scope `FOpenGLRHIState::__anond6775f8f0103`) — The RHI does not allow more than 14 constant buffers per shader stage due to D3D11 limits.

### `Source/Runtime/OpenGLDrv/Private/Windows/WindowsOpenGL.h` (Private)


#### struct `FWindowsOpenGL`  
`struct FWindowsOpenGL : public FOpenGL4`  
_L19-169_
- inherits: `FOpenGL4`
- L21 _public function_ `static FORCEINLINE void InitDebugContext()`
- L27 _public function_ `static FORCEINLINE void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)`
- L35 _public function_ `static FORCEINLINE void PushGroupMarker(const ANSICHAR* Name)`
- L43 _public function_ `static FORCEINLINE void PopGroupMarker()`
- L51 _public function_ `static FORCEINLINE bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, ETextureCreateFlags Flags)`
- L64 _public function_ `static FORCEINLINE bool TexStorage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations)`
- L77 _public function_ `static FORCEINLINE void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type)`
- L105 _public function_ `static FORCEINLINE void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth)`
- L110 _public function_ `static FORCEINLINE bool SupportsBufferStorage()`
- L115 _public function_ `static FORCEINLINE bool SupportsDepthBoundsTest()`
- L120 _public function_ `static FORCEINLINE void BufferStorage(GLenum Target, GLsizeiptr Size, const void* Data, GLbitfield Flags)`
- L125 _public function_ `static FORCEINLINE void DepthBounds(GLfloat Min, GLfloat Max)`
- L130 _public function_ `static FORCEINLINE GLuint64 GetTextureSamplerHandle(GLuint Texture, GLuint Sampler)`
- L135 _public function_ `static FORCEINLINE GLuint64 GetTextureHandle(GLuint Texture)`
- L140 _public function_ `static FORCEINLINE void MakeTextureHandleResident(GLuint64 TextureHandle)`
- L145 _public function_ `static FORCEINLINE void MakeTextureHandleNonResident(GLuint64 TextureHandle)`
- L150 _public function_ `static FORCEINLINE void UniformHandleui64(GLint Location, GLuint64 Value)`
- L155 _public function_ `static FORCEINLINE bool SupportsProgramBinary()`
- L160 _public function_ `static FORCEINLINE void GetProgramBinary(GLuint Program, GLsizei BufSize, GLsizei* Length, GLenum* BinaryFormat, void* Binary)`
- L165 _public function_ `static FORCEINLINE void ProgramBinary(GLuint Program, GLenum BinaryFormat, const void* Binary, GLsizei Length)`
- L203 _public function_ `static FORCEINLINE EShaderPlatform GetShaderPlatform()`

#### struct `FWindowsOpenGL`  
`struct FWindowsOpenGL : public FOpenGLESDeferred`  
_L201-282_
- inherits: `FOpenGLESDeferred`
- L21 _public function_ `static FORCEINLINE void InitDebugContext()`
- L27 _public function_ `static FORCEINLINE void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)`
- L35 _public function_ `static FORCEINLINE void PushGroupMarker(const ANSICHAR* Name)`
- L43 _public function_ `static FORCEINLINE void PopGroupMarker()`
- L51 _public function_ `static FORCEINLINE bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, ETextureCreateFlags Flags)`
- L64 _public function_ `static FORCEINLINE bool TexStorage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations)`
- L77 _public function_ `static FORCEINLINE void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type)`
- L105 _public function_ `static FORCEINLINE void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth)`
- L110 _public function_ `static FORCEINLINE bool SupportsBufferStorage()`
- L115 _public function_ `static FORCEINLINE bool SupportsDepthBoundsTest()`
- L120 _public function_ `static FORCEINLINE void BufferStorage(GLenum Target, GLsizeiptr Size, const void* Data, GLbitfield Flags)`
- L125 _public function_ `static FORCEINLINE void DepthBounds(GLfloat Min, GLfloat Max)`
- L130 _public function_ `static FORCEINLINE GLuint64 GetTextureSamplerHandle(GLuint Texture, GLuint Sampler)`
- L135 _public function_ `static FORCEINLINE GLuint64 GetTextureHandle(GLuint Texture)`
- L140 _public function_ `static FORCEINLINE void MakeTextureHandleResident(GLuint64 TextureHandle)`
- L145 _public function_ `static FORCEINLINE void MakeTextureHandleNonResident(GLuint64 TextureHandle)`
- L150 _public function_ `static FORCEINLINE void UniformHandleui64(GLint Location, GLuint64 Value)`
- L155 _public function_ `static FORCEINLINE bool SupportsProgramBinary()`
- L160 _public function_ `static FORCEINLINE void GetProgramBinary(GLuint Program, GLsizei BufSize, GLsizei* Length, GLenum* BinaryFormat, void* Binary)`
- L165 _public function_ `static FORCEINLINE void ProgramBinary(GLuint Program, GLenum BinaryFormat, const void* Binary, GLsizei Length)`
- L203 _public function_ `static FORCEINLINE EShaderPlatform GetShaderPlatform()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define EMULATE_ES31 0` — Set to 1 to enable creating an ES 3.1 context and use ES 3.1 shaders on Windows
- L15 _macro_ `#define GL_DEBUG_TOOL_EXT 0x6789` — RenderDoc defines
- L16 _macro_ `#define GL_DEBUG_TOOL_NAME_EXT 0x678A`
- L17 _macro_ `#define GL_DEBUG_TOOL_PURPOSE_EXT 0x678B`
- L23 _externvar_ `extern bool GRunningUnderRenderDoc;` (scope `FWindowsOpenGL::InitDebugContext`)
- L174 _macro_ `#define glMapBufferOES glMapBuffer` — fix-up naming differences between OpenGL and OpenGL ES
- L175 _macro_ `#define glUnmapBufferOES glUnmapBuffer`
- L176 _macro_ `#define GL_CLAMP_TO_BORDER_EXT GL_CLAMP_TO_BORDER`
- L177 _macro_ `#define GL_WRITE_ONLY_OES GL_WRITE_ONLY`
- L178 _macro_ `#define GL_ANY_SAMPLES_PASSED_EXT GL_ANY_SAMPLES_PASSED`
- L179 _macro_ `#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS`
- L180 _macro_ `#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS`
- L181 _macro_ `#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS`
- L182 _macro_ `#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS`
- L183 _macro_ `#define GL_DEBUG_SOURCE_API_KHR GL_DEBUG_SOURCE_API`
- L184 _macro_ `#define GL_DEBUG_SOURCE_OTHER_KHR GL_DEBUG_SOURCE_OTHER`
- L186 _macro_ `#define GL_DEBUG_TYPE_ERROR_KHR GL_DEBUG_TYPE_ERROR`
- L187 _macro_ `#define GL_DEBUG_TYPE_OTHER_KHR GL_DEBUG_TYPE_OTHER`
- L189 _macro_ `#define GL_DEBUG_TYPE_MARKER_KHR GL_DEBUG_TYPE_MARKER`
- L190 _macro_ `#define GL_DEBUG_TYPE_POP_GROUP_KHR GL_DEBUG_TYPE_POP_GROUP`
- L192 _macro_ `#define GL_DEBUG_SEVERITY_HIGH_KHR GL_DEBUG_SEVERITY_HIGH`
- L193 _macro_ `#define GL_DEBUG_SEVERITY_LOW_KHR GL_DEBUG_SEVERITY_LOW`
- L195 _macro_ `#define GL_DEBUG_SEVERITY_NOTIFICATION_KHR GL_DEBUG_SEVERITY_NOTIFICATION`
- L285 _typedef_ `using FOpenGL = FWindowsOpenGL;`

### `Source/Runtime/OpenGLDrv/Private/Windows/WindowsOpenGLFunctions.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UGL_PLATFORM_SUPPORTS_GLES 0`
- L8 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL3 1`
- L9 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL4 1`
- L12 _macro_ `#define ENUM_GL_ENTRYPOINTS_DLL(EnumMacro) \` — List all OpenGL entry points used by Unreal that must be loaded from opengl32.dll
- L77 _macro_ `#define ENUM_GL_ENTRYPOINTS(EnumMacro) \` — List all OpenGL entry points used by Unreal.
- L291 _macro_ `#define ENUM_GL_ENTRYPOINTS_OPTIONAL(EnumMacro) \`
- L384 _macro_ `#define ENUM_GL_ENTRYPOINTS_ALL(EnumMacro) \` — List of all OpenGL entry points.
- L390 _macro_ `#define DECLARE_GL_ENTRYPOINTS(Type,Func) extern Type OPENGLDRV_API Func;` — Declare all GL functions.
- L391 _prototype_ `ENUM_GL_ENTRYPOINTS_ALL(DECLARE_GL_ENTRYPOINTS);`
- L395 _externvar_ `extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;` — This function is handled separately because it is used to get a real context.
- L398 _externvar_ `extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT_ProcAddress;` — set in OpenGLDevice.cpp

### `Source/Runtime/OpenGLDrv/Private/Windows/WindowsOpenGLPlatform.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UGL_PLATFORM_SUPPORTS_GLES 0`
- L8 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL3 1`
- L9 _macro_ `#define UGL_PLATFORM_SUPPORTS_GL4 1`
- L12 _macro_ `#define UGL_DRAW_FRAMEBUFFER GL_DRAW_FRAMEBUFFER` — Unreal tokens that maps to different OpenGL tokens by platform.
- L13 _macro_ `#define UGL_READ_FRAMEBUFFER GL_READ_FRAMEBUFFER`
- L14 _macro_ `#define UGL_ABGR8 GL_UNSIGNED_INT_8_8_8_8_REV`
- L15 _macro_ `#define UGL_ANY_SAMPLES_PASSED GL_ANY_SAMPLES_PASSED`
- L16 _macro_ `#define UGL_SAMPLES_PASSED GL_SAMPLES_PASSED`
- L17 _macro_ `#define UGL_TIME_ELAPSED GL_TIME_ELAPSED`
- L18 _macro_ `#define UGL_CLAMP_TO_BORDER GL_CLAMP_TO_BORDER`

### `Source/Runtime/OpenGLDrv/Public/Android/AndroidOpenGLThirdParty.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/OpenGLDrv/Public/IOpenGLDynamicRHI.h` (Public)


#### struct `IOpenGLDynamicRHI`  
`struct IOpenGLDynamicRHI : public FDynamicRHIPSOFallback`  
_L8-43_
- inherits: `FDynamicRHIPSOFallback`
- L10 _public function_ `virtual ERHIInterfaceType GetInterfaceType() const override final`
- L12 _public prototype_ `virtual int32 RHIGetGLMajorVersion() const = 0;`
- L13 _public prototype_ `virtual int32 RHIGetGLMinorVersion() const = 0;`
- L15 _public prototype_ `virtual bool RHISupportsFramebufferSRGBEnable() const = 0;`
- L17 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 NumMips, uint32 NumSamples, uint32 NumSamplesTileMem, const FClearValueBinding& ClearValueBinding, GLuint Resource, ETextureCreateFlags Flags) = 0;`
- L18 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, uint32 NumSamplesTileMem, const FClearValueBinding& ClearValueBinding, GLuint Resource, ETextureCreateFlags Flags) = 0;`
- L19 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, uint32 Size, bool bArray, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, uint32 NumSamplesTileMem, const FClearValueBinding& ClearValueBinding, GLuint Resource, ETextureCreateFlags Flags) = 0;`
- L21 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromAndroidHardwareBuffer(FRHICommandListBase& RHICmdList, AHardwareBuffer* HardwareBuffer) = 0;`
- L24 _public prototype_ `virtual GLuint RHIGetResource(FRHITexture* InTexture) const = 0;`
- L25 _public prototype_ `virtual bool RHIIsValidTexture(GLuint InTexture) const = 0;`
- L26 _public prototype_ `virtual void RHISetExternalGPUTime(uint64 InExternalGPUTime) = 0;`
- L28 _public prototype_ `virtual void RHIGenerateMips(FRHITexture* Texture) = 0;`
- L31 _public prototype_ `virtual EGLDisplay RHIGetEGLDisplay() const = 0;`
- L32 _public prototype_ `virtual EGLSurface RHIGetEGLSurface() const = 0;`
- L33 _public prototype_ `virtual EGLConfig RHIGetEGLConfig() const = 0;`
- L34 _public prototype_ `virtual EGLContext RHIGetEGLContext() const = 0;`
- L35 _public prototype_ `virtual ANativeWindow* RHIGetEGLNativeWindow() const = 0;`
- L36 _public prototype_ `virtual bool RHIEGLSupportsNoErrorContext() const = 0;`
- L38 _public prototype_ `virtual void RHIInitEGLInstanceGLES2() = 0;`
- L39 _public prototype_ `virtual void RHIInitEGLBackBuffer() = 0;`
- L40 _public prototype_ `virtual void RHIEGLSetCurrentRenderingContext() = 0;`
- L41 _public prototype_ `virtual void RHIEGLTerminateContext() = 0;`

#### Free symbols / members of external scopes

- L45 _function_ `inline IOpenGLDynamicRHI* GetIOpenGLDynamicRHI()`

### `Source/Runtime/OpenGLDrv/Public/Linux/LinuxOpenGLThirdParty.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/OpenGLDrv/Public/Mac/MacOpenGLThirdParty.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define GL_COMPUTE_SHADER 0x91B9`
- L13 _macro_ `#define GL_TESS_EVALUATION_SHADER 0x8E87`
- L16 _macro_ `#define GL_TESS_CONTROL_SHADER 0x8E88`

### `Source/Runtime/OpenGLDrv/Public/OpenGLShaderResources.h` (Public)


#### enum `(anonymous)`  
``  
_L23-27_

#### struct `FOpenGLShaderVarying`  
`struct FOpenGLShaderVarying`  
_L29-49_
- L31 _public member_ `TArray<ANSICHAR> Varying;`
- L32 _public member_ `int32 Location;`

#### struct `FOpenGLShaderBindings`  
`struct FOpenGLShaderBindings`  
_L61-77_
- desc: Shader binding information.
- L63 _public member_ `TArray<TArray<CrossCompiler::FPackedArrayInfo>> PackedUniformBuffers;`
- L64 _public member_ `TArray<CrossCompiler::FPackedArrayInfo> PackedGlobalArrays;`
- L65 _public member_ `TArray<FOpenGLShaderVarying> InputVaryings;`
- L66 _public member_ `TArray<FOpenGLShaderVarying> OutputVaryings;`
- L67 _public member_ `CrossCompiler::FShaderBindingInOutMask InOutMask;`
- L69 _public member_ `uint8 NumSamplers = 0;`
- L70 _public member_ `uint8 NumUniformBuffers = 0;`
- L71 _public member_ `uint8 NumUAVs = 0;`
- L72 _public member_ `bool bFlattenUB = false;`
- L74 _public member_ `FSHAHash VaryingHash;` — Not serialized, built during load to allow us to diff varying info but avoid the memory overhead.
- L76 _public prototype_ `inline FArchive& Serialize(FArchive& Ar, FShaderResourceTable& ShaderResourceTable);`
- L79 _function_ `inline FArchive& FOpenGLShaderBindings::Serialize(FArchive& Ar, FShaderResourceTable& ShaderResourceTable)`

#### struct `FOpenGLCodeHeader`  
`struct FOpenGLCodeHeader`  
_L120-129_
- desc: Code header information.
- L122 _public member_ `uint32 GlslMarker;`
- L123 _public member_ `uint16 FrequencyMarker;`
- L124 _public member_ `FOpenGLShaderBindings Bindings;`
- L125 _public member_ `FString ShaderName;`
- L126 _public member_ `TArray<CrossCompiler::FUniformBufferCopyInfo> UniformBuffersCopyInfo;`
- L128 _public prototype_ `inline FArchive& Serialize(FArchive& Ar, FShaderResourceTable& SRT);`
- L131 _function_ `inline FArchive& FOpenGLCodeHeader::Serialize(FArchive& Ar, FShaderResourceTable& SRT)`

#### class `FOpenGLCompiledShaderKey`  
`class FOpenGLCompiledShaderKey`  
_L161-192_
- L164 _public prototype_ `FOpenGLCompiledShaderKey() = default;`
- L165 _public function_ `FOpenGLCompiledShaderKey( GLenum InTypeEnum, uint32 InCodeSize, uint32 InCodeCRC ) : TypeEnum(InTypeEnum) , CodeSize(InCodeSize) , CodeCRC(InCodeCRC)`
- L186 _public function_ `uint32 GetCodeCRC() const`
- L189 _private member_ `GLenum TypeEnum = 0;`
- L190 _private member_ `uint32 CodeSize = 0;`
- L191 _private member_ `uint32 CodeCRC = 0;`

#### class `FOpenGLShader`  
`class FOpenGLShader`  
_L197-224_
- desc: OpenGL shader resource.
- L201 _public member_ `GLuint Resource = 0;` — The OpenGL resource ID.
- L204 _public member_ `FOpenGLShaderBindings Bindings;` — External bindings for this shader.
- L207 _public member_ `TArray<CrossCompiler::FUniformBufferCopyInfo> UniformBuffersCopyInfo;` — List of memory copies from RHIUniformBuffer to packed uniforms
- L209 _public member_ `FOpenGLCompiledShaderKey ShaderCodeKey;`
- L211 _public member_ `bool bUsesProgrammableBlending = false;`
- L214 _public member_ `TArray<ANSICHAR> GlslCode;`
- L215 _public member_ `const ANSICHAR* GlslCodeString;` — make it easier in VS to see shader code in debug mode; points to begin of GlslCode
- L218 _public prototype_ `FOpenGLShader(TArrayView<const uint8> Code, GLenum TypeEnum, FShaderResourceTable& SRT, FRHIShader* RHIShader);`
- L220 _public prototype_ `~FOpenGLShader() = default;`
- L223 _protected prototype_ `void Compile(GLenum TypeEnum);`

#### class `FOpenGLVertexShader`  
`class FOpenGLVertexShader : public FRHIVertexShader, public FOpenGLShader`  
_L226-234_
- inherits: `FRHIVertexShader,FOpenGLShader`
- L229 _public member_ `static constexpr EShaderFrequency Frequency = SF_Vertex;`
- L231 _public prototype_ `FOpenGLVertexShader(TArrayView<const uint8> Code);`
- L233 _public prototype_ `void ConditionalyCompile();`

#### class `FOpenGLPixelShader`  
`class FOpenGLPixelShader : public FRHIPixelShader, public FOpenGLShader`  
_L236-244_
- inherits: `FRHIPixelShader,FOpenGLShader`
- L239 _public member_ `static constexpr EShaderFrequency Frequency = SF_Pixel;`
- L241 _public prototype_ `FOpenGLPixelShader(TArrayView<const uint8> Code);`
- L243 _public prototype_ `void ConditionalyCompile();`

#### class `FOpenGLGeometryShader`  
`class FOpenGLGeometryShader : public FRHIGeometryShader, public FOpenGLShader`  
_L246-254_
- inherits: `FRHIGeometryShader,FOpenGLShader`
- L249 _public member_ `static constexpr EShaderFrequency Frequency = SF_Geometry;`
- L251 _public prototype_ `FOpenGLGeometryShader(TArrayView<const uint8> Code);`
- L253 _public prototype_ `void ConditionalyCompile();`

#### class `FOpenGLComputeShader`  
`class FOpenGLComputeShader : public FRHIComputeShader, public FOpenGLShader`  
_L256-272_
- inherits: `FRHIComputeShader,FOpenGLShader`
- L259 _public member_ `static constexpr EShaderFrequency Frequency = SF_Compute;`
- L261 _public prototype_ `FOpenGLComputeShader(TArrayView<const uint8> Code);`
- L263 _public prototype_ `void ConditionalyCompile();`
- L265 _public prototype_ `bool NeedsTextureStage(int32 TextureStageIndex);`
- L266 _public prototype_ `int32 MaxTextureStageUsed();`
- L267 _public prototype_ `const TBitArray<>& GetTextureNeeds(int32& OutMaxTextureStageUsed);`
- L268 _public prototype_ `const TBitArray<>& GetUAVNeeds(int32& OutMaxUAVUnitUsed) const;`
- L269 _public prototype_ `bool NeedsUAVStage(int32 UAVStageIndex) const;`
- L271 _public member_ `FOpenGLLinkedProgram* LinkedProgram = nullptr;`

#### class `FOpenGLShaderParameterCache`  
`class FOpenGLShaderParameterCache`  
_L277-326_
- desc: Caching of OpenGL uniform parameters.
- L281 _public prototype_ `FOpenGLShaderParameterCache();` — Constructor.
- L284 _public prototype_ `~FOpenGLShaderParameterCache();` — Destructor.
- L286 _public prototype_ `void InitializeResources(int32 UniformArraySize);`
- L291 _public prototype_ `void MarkAllDirty();` — Marks all uniform arrays as dirty.
- L296 _public prototype_ `void Set(uint32 BufferIndex, uint32 ByteOffset, uint32 NumBytes, const void* NewValues);` — Sets values directly into the packed uniform array
- L302 _public prototype_ `void CommitPackedGlobals(const FOpenGLLinkedProgram* LinkedProgram, CrossCompiler::EShaderStage Stage);` — Commit shader parameters to the currently bound program. @param ParameterTable - Information on the bound uniform arrays for the program.
- L304 _public prototype_ `void CommitPackedUniformBuffers(FOpenGLLinkedProgram* LinkedProgram, CrossCompiler::EShaderStage Stage, FRHIUniformBuffer** UniformBuffers, const TArray<CrossCompiler::FUniformBufferCopyInfo>& UniformBuffersCopyInfo);`
- L309 _private member_ `uint8* PackedGlobalUniforms[CrossCompiler::PACKED_TYPEINDEX_MAX];` — CPU memory block for storing uniform values.
- L319 _private member_ `FRange PackedGlobalUniformDirty[CrossCompiler::PACKED_TYPEINDEX_MAX];` — Dirty ranges for each uniform array.
- L322 _private member_ `uint8* PackedUniformsScratch[CrossCompiler::PACKED_TYPEINDEX_MAX];` — Scratch CPU memory block for uploading packed uniforms.
- L325 _private member_ `int32 GlobalUniformArraySize;` — in bytes

#### struct `FOpenGLShaderParameterCache::FRange`  
`struct FRange`  
_L311-317_
- L313 _public member_ `uint32 StartVector;`
- L314 _public member_ `uint32 NumVectors;`
- L316 _public prototype_ `void MarkDirtyRange(uint32 NewStartVector, uint32 NewNumVectors);`

#### class `FOpenGLProgramKey`  
`class FOpenGLProgramKey`  
_L329-387_
- desc: unique identifier for a program. (composite of shader keys)
- L332 _public prototype_ `FOpenGLProgramKey() = default;`
- L333 _public prototype_ `FOpenGLProgramKey(FRHIComputeShader* ComputeShaderRHI);`
- L334 _public prototype_ `FOpenGLProgramKey(FRHIVertexShader* VertexShaderRHI, FRHIPixelShader* PixelShaderRHI, FRHIGeometryShader* GeometryShaderRHI);`
- L365 _public function_ `FString ToString() const`
- L386 _public member_ `FShaderHash ShaderHashes[CrossCompiler::NUM_SHADER_STAGES];`

#### Free symbols / members of external scopes

- L17 _macro_ `#define DEBUG_GL_SHADERS (UE_BUILD_DEBUG || UE_EDITOR)` — Set to 1 to enable shader debugging which e.g. keeps the GLSL source as members of TOpenGLShader
- L24 _enumerator_ `OGL_MAX_UNIFORM_BUFFER_BINDINGS = 12` (scope `__anon29f91f840103`) — @todo-mobile: Remove me
- L25 _enumerator_ `OGL_FIRST_UNIFORM_BUFFER = 0` (scope `__anon29f91f840103`) — @todo-mobile: Remove me
- L26 _enumerator_ `OGL_UAV_NOT_SUPPORTED_FOR_GRAPHICS_UNIT = -1` (scope `__anon29f91f840103`) — for now, only CS and PS supports UAVs/ images
- L34 _function_ `friend bool operator==(const FOpenGLShaderVarying& A, const FOpenGLShaderVarying& B)`
- L43 _function_ `friend uint32 GetTypeHash(const FOpenGLShaderVarying &Var)`
- L51 _function_ `inline FArchive& operator<<(FArchive& Ar, FOpenGLShaderVarying& Var)`
- L98 _function_ `` (scope `FOpenGLShaderBindings::Serialize`)
- L176 _function_ `friend bool operator == (const FOpenGLCompiledShaderKey& A, const FOpenGLCompiledShaderKey& B)`
- L181 _function_ `friend uint32 GetTypeHash(const FOpenGLCompiledShaderKey& Key)`
- L336 _function_ `friend bool operator == (const FOpenGLProgramKey& A, const FOpenGLProgramKey& B)`
- L346 _function_ `friend bool operator != (const FOpenGLProgramKey& A, const FOpenGLProgramKey& B)`
- L351 _function_ `friend uint32 GetTypeHash(const FOpenGLProgramKey& Key)`
- L356 _function_ `friend FArchive& operator<<(FArchive& Ar, FOpenGLProgramKey& HashSet)`

### `Source/Runtime/OpenGLDrv/Public/OpenGLThirdParty.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/OpenGLDrv/Public/OpenGLUtil.h` (Public)


#### struct `FOpenGLErrorScope`  
`struct FOpenGLErrorScope`  
_L75-116_
- L77 _public member_ `const char* FunctionName;`
- L78 _public member_ `const TCHAR* Filename;`
- L79 _public member_ `const uint32 Line;`
- L81 _public function_ `FOpenGLErrorScope( const char* InFunctionName, const TCHAR* InFilename, const uint32 InLine) : FunctionName(InFunctionName) , Filename(InFilename) , Line(InLine)`
- L95 _public function_ `~FOpenGLErrorScope()`
- L105 _public function_ `void CheckForErrors(int32 BeforeOrAfter)`

#### struct `FRHICommandGLCommandString`  
`struct FRHICommandGLCommandString`  
_L136-139_
- L138 _public function_ `static const TCHAR* TStr()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define ENABLE_VERIFY_GL (0 & DO_CHECK)` — Set to 1 to enable the VERIFY_GL macros which call glGetError
- L17 _macro_ `#define ENABLE_VERIFY_GL_TRACE 0`
- L21 _macro_ `#define ENABLE_DEBUG_OUTPUT (!UE_BUILD_SHIPPING)` — Include GL debug output functionality on everything but shipping configs. to enable the debug output specify '-OpenGLDebugLevel=[1-5]' via the command line.
- L23 _function_ `inline bool IsOGLDebugOutputEnabled()`
- L24 _function_ `inline int32 GetOGLDebugOutputLevel()`
- L26 _prototype_ `bool IsOGLDebugOutputEnabled();`
- L27 _prototype_ `int32 GetOGLDebugOutputLevel();`
- L31 _macro_ `#define ENABLE_VERIFY_GL_THREAD (!(UE_BUILD_TEST || UE_BUILD_SHIPPING))` — Additional check that our GL calls are occurring on the expected thread
- L34 _macro_ `#define ENABLE_UNIFORM_BUFFER_LAYOUT_VERIFICATION ( 0 & UE_BUILD_DEBUG & (!PLATFORM_ANDROID))` — Set to 1 to verify that the the engine side uniform buffer layout matches the driver side of the GLSL shader
- L37 _macro_ `#define ENABLE_UNIFORM_BUFFER_LAYOUT_DUMP 0` — Set to 1 to additinally dump uniform buffer layout at shader link time, this assumes ENABLE_UNIFORM_BUFFER_LAYOUT_VERIFICATION == 1
- L43 _macro_ `#define ENABLE_OPENGL_DEBUG_GROUPS 1`
- L45 _macro_ `#define OPENGL_PERFORMANCE_DATA_INVALID (ENABLE_VERIFY_GL | ENABLE_UNIFORM_BUFFER_LAYOUT_VERIFICATION | DEBUG_GL_SHADERS)`
- L47 _prototype_ `void SetOpenGLResourceName(FOpenGLTexture* Texture, const ANSICHAR* Name);`
- L48 _prototype_ `void SetOpenGLResourceName(FOpenGLTexture* Texture, const TCHAR* Name);`
- L55 _prototype_ `GLenum GetOpenGLCubeFace(ECubeFace Face);` — Convert from ECubeFace to GLenum type @param Face - ECubeFace type to convert @return OpenGL cube face enum value
- L57 _prototype_ `extern bool PlatformOpenGLThreadHasRenderingContext();`
- L60 _macro_ `#define CHECK_EXPECTED_GL_THREAD() \`
- L66 _macro_ `#define CHECK_EXPECTED_GL_THREAD()`
- L70 _prototype_ `extern int32 PlatformGlGetError();`
- L72 _prototype_ `void VerifyOpenGLResult(GLenum ErrorCode, const TCHAR* Msg1, const TCHAR* Msg2, const TCHAR* Filename, uint32 Line);`
- L73 _macro_ `#define VERIFY_GL(msg) { CHECK_EXPECTED_GL_THREAD(); GLenum ErrorCode = PlatformGlGetError(); if (ErrorCode != GL_NO_ERROR) { VerifyOpenGLResult(ErrorCode,TEXT(#msg),TEXT(""),TEXT(__FILE__),__LINE__); } }`
- L117 _macro_ `#define MACRO_TOKENIZER(IdentifierName, Msg, FileName, LineNumber) FOpenGLErrorScope IdentifierName_ ## LineNumber (Msg, FileName, LineNumber)`
- L118 _macro_ `#define MACRO_TOKENIZER2(IdentifierName, Msg, FileName, LineNumber) MACRO_TOKENIZER(IdentiferName, Msg, FileName, LineNumber)`
- L119 _macro_ `#define VERIFY_GL_SCOPE_WITH_MSG_STR(MsgStr) CHECK_EXPECTED_GL_THREAD(); MACRO_TOKENIZER2(ErrorScope_, MsgStr, TEXT(__FILE__), __LINE__)`
- L120 _macro_ `#define VERIFY_GL_SCOPE() VERIFY_GL_SCOPE_WITH_MSG_STR(__FUNCTION__)`
- L121 _macro_ `#define VERIFY_GL_FUNC(Func, ...) { VERIFY_GL_SCOPE_WITH_MSG_STR((#Func)); Func(__VA_ARGS__); }`
- L126 _macro_ `#define glBlitFramebuffer(...) VERIFY_GL_FUNC(glBlitFramebuffer, __VA_ARGS__)` — Some important GL calls are trapped individually.
- L127 _macro_ `#define glTexImage2D(...) VERIFY_GL_FUNC(glTexImage2D, __VA_ARGS__)`
- L128 _macro_ `#define glTexSubImage2D(...) VERIFY_GL_FUNC(glTexSubImage2D, __VA_ARGS__)`
- L129 _macro_ `#define glCompressedTexImage2D(...) VERIFY_GL_FUNC(glCompressedTexImage2D, __VA_ARGS__)`
- L132 _macro_ `#define VERIFY_GL(...) CHECK_EXPECTED_GL_THREAD()`
- L133 _macro_ `#define VERIFY_GL_SCOPE(...) CHECK_EXPECTED_GL_THREAD()`
- L141 _macro_ `#define GL_CAPTURE_CALLSTACK 0 // Capture the callstack at the point of enqueuing the command.`

### `Source/Runtime/OpenGLDrv/Public/Windows/WindowsOpenGLThirdParty.h` (Public)
_(no declarations extracted)_
