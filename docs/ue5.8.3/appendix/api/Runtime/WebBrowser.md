# Runtime / WebBrowser

- module root: `Source/Runtime/WebBrowser`
- headers: 50; symbols: 1894
- symbol kinds: class=51, delegate=80, enum=8, enumerator=44, function=228, macro=1, member=468, namespace=6, prototype=959, struct=23, typedef=14, union=1, variable=11
- PrivateDependencyModuleNames: ApplicationCore, CEF3Utils, Core, CoreUObject, Engine, HTTP, InputCore, Json, JsonUtilities, Launch, RHI, RenderCore, Serialization, WebBrowserTexture
- PublicDependencyModuleNames: Slate, SlateCore

### `Source/Runtime/WebBrowser/Private/Android/AndroidCookieManager.h` (Private)


#### class `FAndroidCookieManager`  
`class FAndroidCookieManager : public IWebBrowserCookieManager , public TSharedFromThis<FAndroidCookieManager>`  
_L13-28_
- inherits: `IWebBrowserCookieManager,TSharedFromThis<FAndroidCookieManager>`
- desc: Implementation of interface for dealing with a Web Browser cookies for iOS.
- L21 _public prototype_ `virtual void SetCookie(const FString& URL, const FCookie& Cookie, TFunction<void(bool)> Completed = nullptr) override;`
- L22 _public prototype_ `virtual void DeleteCookies(const FString& URL = TEXT(""), const FString& CookieName = TEXT(""), TFunction<void(int)> Completed = nullptr) override;`
- L26 _public prototype_ `FAndroidCookieManager();`
- L27 _public prototype_ `virtual ~FAndroidCookieManager();`

### `Source/Runtime/WebBrowser/Private/Android/AndroidJavaWebBrowser.h` (Private)


#### class `FJavaAndroidWebBrowser`  
`class FJavaAndroidWebBrowser : public UE::Jni::TClassObject<UE::Jni::FWebViewControl>`  
_L16-100_
- inherits: `UE::Jni::TClassObject<UE::Jni::FWebViewControl>`
- desc: Wrapper for com/epicgames/unreal/WebViewControl.java.
- L19 _public prototype_ `FJavaAndroidWebBrowser(bool swizzlePixels, bool vulkanRenderer, int32 width, int32 height, jlong widgetPtr, bool bEnableRemoteDebugging, bool bUseTransparency, bool bEnableDomStorage, bool bShouldUseBitmapRender, const FString& UserAgentApplication, bool bEnableFloatingCloseButton, bool bEnablePaymentRequest);`
- L20 _public prototype_ `virtual ~FJavaAndroidWebBrowser();`
- L21 _public prototype_ `void Release();`
- L22 _public prototype_ `bool GetVideoLastFrameBitmap(void* outPixels, int64 outCount);`
- L23 _public prototype_ `bool GetVideoLastFrameData(void* & outPixels, int64 & outCount, bool *bRegionChanged);`
- L24 _public prototype_ `bool GetVideoLastFrame(int32 destTexture);`
- L25 _public prototype_ `bool DidResolutionChange();`
- L26 _public prototype_ `bool UpdateVideoFrame(int32 ExternalTextureId, bool *bRegionChanged);`
- L27 _public prototype_ `void ExecuteJavascript(const FString& Script);`
- L28 _public prototype_ `void LoadURL(const FString& NewURL);`
- L29 _public prototype_ `void LoadString(const FString& Contents, const FString& BaseUrl);`
- L30 _public prototype_ `void StopLoad();`
- L31 _public prototype_ `void Reload();`
- L32 _public prototype_ `void Close();`
- L33 _public prototype_ `void ShowFloatingCloseButton(bool bShow, bool bDraggable);`
- L34 _public prototype_ `void GoBack();`
- L35 _public prototype_ `void GoForward();`
- L36 _public prototype_ `void SendTouchDown(float x, float y);`
- L37 _public prototype_ `void SendTouchUp(float x, float y);`
- L38 _public prototype_ `void SendTouchMove(float x, float y);`
- L39 _public prototype_ `bool SendKeyDown(int32 KeyCode);`
- L40 _public prototype_ `bool SendKeyUp(int32 KeyCode);`
- L41 _public prototype_ `void SetAndroid3DBrowser(bool InIsAndroid3DBrowser);`
- L42 _public prototype_ `void SetVisibility(bool InIsVisible);`
- L43 _public prototype_ `void Update(const int posX, const int posY, const int sizeX, const int sizeY);`
- L45 _private prototype_ `static FName GetClassName();`
- L47 _private member_ `FJavaClassMethod ReleaseMethod;`
- L48 _private member_ `FJavaClassMethod GetVideoLastFrameBitmapMethod;`
- L49 _private member_ `FJavaClassMethod GetVideoLastFrameDataMethod;`
- L50 _private member_ `FJavaClassMethod GetVideoLastFrameMethod;`
- L51 _private member_ `FJavaClassMethod DidResolutionChangeMethod;`
- L52 _private member_ `FJavaClassMethod UpdateVideoFrameMethod;`
- L53 _private member_ `FJavaClassMethod UpdateMethod;`
- L54 _private member_ `FJavaClassMethod ExecuteJavascriptMethod;`
- L55 _private member_ `FJavaClassMethod LoadURLMethod;`
- L56 _private member_ `FJavaClassMethod LoadStringMethod;`
- L57 _private member_ `FJavaClassMethod StopLoadMethod;`
- L58 _private member_ `FJavaClassMethod ReloadMethod;`
- L59 _private member_ `FJavaClassMethod CloseMethod;`
- L60 _private member_ `FJavaClassMethod ShowFloatingCloseButtonMethod;`
- L61 _private member_ `FJavaClassMethod GoBackOrForwardMethod;`
- L62 _private member_ `FJavaClassMethod SendTouchEventMethod;`
- L63 _private member_ `FJavaClassMethod SendKeyEventMethod;`
- L64 _private member_ `FJavaClassMethod SetAndroid3DBrowserMethod;`
- L65 _private member_ `FJavaClassMethod SetVisibilityMethod;`
- L68 _private member_ `jclass FrameUpdateInfoClass;` — FrameUpdateInfo member field ids
- L69 _private member_ `jfieldID FrameUpdateInfo_Buffer;`
- L70 _private member_ `jfieldID FrameUpdateInfo_Bitmap;`
- L71 _private member_ `jfieldID FrameUpdateInfo_FrameReady;`
- L72 _private member_ `jfieldID FrameUpdateInfo_RegionChanged;`
- L74 _private member_ `FTextureRHIRef VideoTexture;`
- L75 _private member_ `bool bVideoTextureValid;`
- L78 _public function_ `FTextureRHIRef GetVideoTexture()`
- L83 _public function_ `void SetVideoTexture(FTextureRHIRef Texture)`
- L90 _public function_ `void SetVideoTextureValid(bool Condition)`
- L95 _public function_ `bool IsVideoTextureValid()`

### `Source/Runtime/WebBrowser/Private/Android/AndroidJniWebViewControl.h` (Private)


#### struct `UE::Jni::Android::WebKit::FWebView`  
`struct FWebView: Java::Lang::FObject`  
_L11-14_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr FAnsiStringView ClassName = "an`

#### struct `UE::Jni::Android::WebKit::FJsResult`  
`struct FJsResult: Java::Lang::FObject`  
_L16-19_
- inherits: `Java::Lang::FObject`
- L18 _public member_ `static constexpr FAnsiStringView ClassName = "an`

#### struct `UE::Jni::Android::WebKit::FJsPromptResult`  
`struct FJsPromptResult: Java::Lang::FObject`  
_L21-24_
- inherits: `Java::Lang::FObject`
- L23 _public member_ `static constexpr FAnsiStringView ClassName = "an`

#### struct `UE::Jni::FWebViewControl`  
`struct FWebViewControl: Java::Lang::FObject`  
_L29-84_
- inherits: `Java::Lang::FObject`
- L69 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L71 _public member_ `inline static TConstructor<FWebViewControl(jlong InNativePtr, jint Width, jint Height, jboolean bSwizzlePixels, jboolean bVulkanRenderer, jboolean bEnableRemoteDebugging, jboolean bUseTransparency, jboolean bEnableDomStorage, jboolean bShouldUseBitmapRender, jstring UserAgentApplication, jboolean bEnableFloatingCloseButton, jboolean bEnablePaymentRequest)> New;`
- L73 _public prototype_ `static void JNICALL FloatingCloseButtonPressed(JNIEnv* JEnv, jobject thiz);`
- L75 _public member_ `static constexpr FMember Members[] { UE_JNI_MEMBER(New) };`
- L80 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(FloatingCloseButtonPressed) };`

#### struct `UE::Jni::FWebViewControl::FViewClient`  
`struct FViewClient: Java::Lang::FObject`  
_L31-47_
- inherits: `Java::Lang::FObject`
- L33 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L35 _public prototype_ `static Java::Lang::TArray<jbyte>* JNICALL shouldInterceptRequestImpl(JNIEnv* env, jobject thiz, jstring JUrl);`
- L36 _public prototype_ `static jboolean JNICALL shouldOverrideUrlLoading(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jstring JUrl);`
- L37 _public prototype_ `static void JNICALL onPageLoad(JNIEnv* env, jobject thiz, jstring JUrl, jboolean bIsLoading, jint HistorySize, jint HistoryPosition);`
- L38 _public prototype_ `static void JNICALL onReceivedError(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jint ErrorCode, jstring Description, jstring JUrl);`
- L40 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(shouldInterceptRequestImpl), UE_JNI_NATIVE_METHOD(shouldOverrideUrlLoading), UE_JNI_NATIVE_METHOD(onPageLoad), UE_JNI_NATIVE_METHOD(onReceivedError) };`

#### struct `UE::Jni::FWebViewControl::FChromeClient`  
`struct FChromeClient: Java::Lang::FObject`  
_L49-67_
- inherits: `Java::Lang::FObject`
- L51 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L53 _public prototype_ `static jboolean JNICALL onJsAlert(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jstring JUrl, jstring Message, Android::WebKit::FJsResult* Result);`
- L54 _public prototype_ `static jboolean JNICALL onJsBeforeUnload(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jstring JUrl, jstring Message, Android::WebKit::FJsResult* Result);`
- L55 _public prototype_ `static jboolean JNICALL onJsConfirm(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jstring JUrl, jstring Message, Android::WebKit::FJsResult* Result);`
- L56 _public prototype_ `static jboolean JNICALL onJsPrompt(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jstring JUrl, jstring Message, jstring DefaultValue, Android::WebKit::FJsPromptResult* Result);`
- L57 _public prototype_ `static void JNICALL onReceivedTitle(JNIEnv* env, jobject thiz, Android::WebKit::FWebView* , jstring Title);`
- L59 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(onJsAlert), UE_JNI_NATIVE_METHOD(onJsBeforeUnload), UE_JNI_NATIVE_METHOD(onJsConfirm), UE_JNI_NATIVE_METHOD(onJsPrompt), UE_JNI_NATIVE_METHOD(onReceivedTitle) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L9 _namespace_ `namespace Android` (scope `UE::Jni`)
- L9 _namespace_ `namespace WebKit` (scope `UE::Jni::Android`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Jni` (scope `UE`)
- L86 _variable_ `template struct TInitialize<FWebViewControl::FViewClient>;` (scope `UE::Jni`)

### `Source/Runtime/WebBrowser/Private/Android/AndroidWebBrowserDialog.h` (Private)


#### class `FAndroidWebBrowserDialog`  
`class FAndroidWebBrowserDialog : public IWebBrowserDialog`  
_L15-62_
- inherits: `IWebBrowserDialog`
- L19 _public prototype_ `virtual ~FAndroidWebBrowserDialog() = default;`
- L23 _public function_ `virtual EWebBrowserDialogType GetType() override`
- L28 _public function_ `virtual const FText& GetMessageText() override`
- L33 _public function_ `virtual const FText& GetDefaultPrompt() override`
- L38 _public function_ `virtual bool IsReload() override`
- L44 _public prototype_ `virtual void Continue(bool Success = true, const FText& UserResponse = FText::GetEmpty()) override;`
- L48 _private member_ `EWebBrowserDialogType Type;`
- L49 _private member_ `FText MessageText;`
- L50 _private member_ `FText DefaultPrompt;`
- L52 _private member_ `jobject Callback;` — Either a reference to a JsResult or a JsPromptResult object depending on Type
- L55 _private prototype_ `FAndroidWebBrowserDialog(jstring InMessageText, jstring InDefaultPrompt, jobject InCallback);` — Create a dialog from OnJSPrompt arguments
- L58 _private prototype_ `FAndroidWebBrowserDialog(EWebBrowserDialogType InDialogType, jstring InMessageText, jobject InCallback);` — Create a dialog from OnJSAlert|Confirm|BeforeUnload arguments

#### Free symbols / members of external scopes

- L64 _typedef_ `typedef FAndroidWebBrowserDialog FWebBrowserDialog;`

### `Source/Runtime/WebBrowser/Private/Android/AndroidWebBrowserWidget.h` (Private)


#### class `SAndroidWebBrowserWidget`  
`class SAndroidWebBrowserWidget : public SViewport`  
_L28-144_
- inherits: `SViewport`
- L30 _private function_ `SLATE_BEGIN_ARGS(SAndroidWebBrowserWidget) : _InitialURL("about:blank") , _UseTransparency(false) , _EnablePaymentRequest(false)`
- L36 _private prototype_ `SLATE_ARGUMENT(FString, InitialURL);`
- L37 _private prototype_ `SLATE_ARGUMENT(bool, UseTransparency);`
- L38 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<FAndroidWebBrowserWindow>, WebBrowserWindow);`
- L39 _private prototype_ `SLATE_ARGUMENT(FString, UserAgentApplication);`
- L40 _private prototype_ `SLATE_ARGUMENT(bool, EnablePaymentRequest);`
- L45 _public prototype_ `virtual ~SAndroidWebBrowserWidget();`
- L47 _public prototype_ `void Construct(const FArguments& Args);`
- L49 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L50 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L51 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L53 _public prototype_ `void ExecuteJavascript(const FString& Script);`
- L54 _public prototype_ `void LoadURL(const FString& NewURL);`
- L55 _public prototype_ `void LoadString(const FString& Content, const FString& BaseUrl);`
- L57 _public prototype_ `void StopLoad();`
- L58 _public prototype_ `void Reload();`
- L59 _public prototype_ `void Close();`
- L60 _public prototype_ `void ShowFloatingCloseButton(bool bShow, bool bDraggable);`
- L61 _public prototype_ `void GoBack();`
- L62 _public prototype_ `void GoForward();`
- L63 _public prototype_ `bool CanGoBack();`
- L64 _public prototype_ `bool CanGoForward();`
- L65 _public prototype_ `void FloatingCloseButtonPressed();`
- L67 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L68 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L69 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L71 _public prototype_ `void SendTouchDown(FVector2D Position);`
- L72 _public prototype_ `void SendTouchUp(FVector2D Position);`
- L73 _public prototype_ `void SendTouchMove(FVector2D Position);`
- L75 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L76 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L77 _public prototype_ `virtual FReply OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) override;`
- L81 _public prototype_ `jbyteArray HandleShouldInterceptRequest(jstring JUrl);`
- L83 _public prototype_ `bool HandleShouldOverrideUrlLoading(jstring JUrl);`
- L84 _public function_ `bool HandleJsDialog(EWebBrowserDialogType Type, jstring JUrl, jstring MessageText, jobject ResultCallback)`
- L90 _public function_ `bool HandleJsPrompt(jstring JUrl, jstring MessageText, jstring DefaultPrompt, jobject ResultCallback)`
- L96 _public prototype_ `void HandleReceivedTitle(jstring JTitle);`
- L97 _public prototype_ `void HandlePageLoad(jstring JUrl, bool bIsLoading, int InHistorySize, int InHistoryPosition);`
- L98 _public prototype_ `void HandleReceivedError(jint ErrorCode, jstring JMessage, jstring JUrl);`
- L102 _public prototype_ `static TSharedPtr<SAndroidWebBrowserWidget> GetWidgetPtr(JNIEnv* JEnv, jobject Jobj);` — Helper to get the native widget pointer from a Java callback. Jobj can either be a WebViewControl, a WebViewControl.ViewClient or WebViewControl.ChromeClient instance
- L105 _public prototype_ `void SetWebBrowserVisibility(bool InIsVisible);` — set the native control's visibility
- L107 _protected member_ `static FCriticalSection WebControlsCS;`
- L108 _protected member_ `static TMap<int64, TWeakPtr<SAndroidWebBrowserWidget>> AllWebControls;`
- L110 _protected prototype_ `bool HandleJsDialog(TSharedPtr<IWebBrowserDialog>& Dialog);`
- L111 _protected member_ `int HistorySize;`
- L112 _protected member_ `int HistoryPosition;`
- L114 _protected member_ `TWeakPtr<FAndroidWebBrowserWindow> WebBrowserWindowPtr;`
- L116 _private prototype_ `FVector2D ConvertMouseEventToLocal(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L119 _private member_ `bool IsAndroid3DBrowser;` — Enable 3D appearance for Android.
- L122 _private member_ `bool bShouldUseBitmapRender;` — Should use bitmap rendering for 3D.
- L125 _private member_ `bool bMouseCapture;` — Mouse captured
- L128 _private member_ `TSharedPtr<FJavaAndroidWebBrowser, ESPMode::ThreadSafe> JavaWebBrowser;` — The Java side webbrowser interface.
- L131 _private member_ `UWebBrowserTexture* WebBrowserTexture;` — The external texture to render the webbrowser output.
- L134 _private member_ `UMaterialInstanceDynamic* WebBrowserMaterial;` — The material for the external texture.
- L137 _private member_ `TSharedPtr<FSlateBrush> WebBrowserBrush;` — The Slate brush that renders the material.
- L140 _private member_ `TSharedPtr<FWebBrowserTextureSampleQueue, ESPMode::ThreadSafe> WebBrowserTextureSamplesQueue;` — The sample queue.
- L143 _private member_ `FWebBrowserTextureSamplePool* TextureSamplePool;` — Texture sample object pool.

### `Source/Runtime/WebBrowser/Private/Android/AndroidWebBrowserWindow.h` (Private)


#### class `FAndroidWebBrowserWindow`  
`class FAndroidWebBrowserWindow : public IWebBrowserWindow , public TSharedFromThis<FAndroidWebBrowserWindow>`  
_L19-376_
- inherits: `IWebBrowserWindow,TSharedFromThis<FAndroidWebBrowserWindow>`
- desc: Implementation of interface for dealing with a Web Browser window.
- L42 _private prototype_ `FAndroidWebBrowserWindow(FString Url, TOptional<FString> ContentsToLoad, bool bShowErrorMessage, bool bThumbMouseButtonNavigation, bool bUseTransparency, bool bJSBindingToLoweringEnabled, const FString& InUserAgentApplication, bool bMobileJSReturnInDict, bool bInEnablePaymentRequest);` — Creates and initializes a new instance. @param Url The Initial URL that will be loaded. @param ContentsToLoad Optional string to load as a web page. @param bShowErrorMessage Whether to show an error message in case of loading errors. @param bThumbMouseButtonNavigation Whether to allow forward and back navigation via the mouse thumb buttons. @param bUseTransparency Whether to enable transparency. @param bJSBindingToLoweringEnabled Whether we ToLower all JavaScript member names. @param bMobileJSReturnInDict Whether to pass a UObject wrapper function's return value in a dictionary with the property's name or not. @param bInEnablePaymentRequest Whether to enable the W3C PaymentRequest API on this window
- L47 _private prototype_ `TSharedRef<SWidget> CreateWidget();` — Create the SWidget for this WebBrowserWindow
- L51 _public prototype_ `virtual ~FAndroidWebBrowserWindow();` — Virtual Destructor.
- L57 _public prototype_ `virtual void LoadURL(FString NewURL) override;`
- L58 _public prototype_ `virtual void LoadString(FString Contents, FString DummyURL) override;`
- L59 _public prototype_ `virtual void SetViewportSize(FIntPoint WindowSize, FIntPoint WindowPos) override;`
- L60 _public prototype_ `virtual FIntPoint GetViewportSize() const override;`
- L61 _public prototype_ `virtual FSlateShaderResource* GetTexture(bool bIsPopup = false) override;`
- L62 _public prototype_ `virtual bool IsValid() const override;`
- L63 _public prototype_ `virtual bool IsInitialized() const override;`
- L64 _public prototype_ `virtual bool IsClosing() const override;`
- L65 _public prototype_ `virtual EWebBrowserDocumentState GetDocumentLoadingState() const override;`
- L66 _public prototype_ `virtual FString GetTitle() const override;`
- L67 _public prototype_ `virtual FString GetUrl() const override;`
- L68 _public prototype_ `virtual void GetSource(TFunction<void (const FString&)> Callback) const override;`
- L69 _public prototype_ `virtual bool OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L70 _public prototype_ `virtual bool OnKeyUp(const FKeyEvent& InKeyEvent) override;`
- L71 _public prototype_ `virtual bool OnKeyChar(const FCharacterEvent& InCharacterEvent) override;`
- L72 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L73 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L74 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L75 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L76 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L77 _public prototype_ `virtual void SetSupportsMouseWheel(bool bValue) override;`
- L78 _public prototype_ `virtual bool GetSupportsMouseWheel() const override;`
- L79 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L80 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent, bool bIsPopup) override;`
- L81 _public prototype_ `virtual void OnFocus(bool SetFocus, bool bIsPopup) override;`
- L82 _public prototype_ `virtual void OnCaptureLost() override;`
- L83 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L84 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L85 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L86 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L87 _public prototype_ `virtual bool CanGoBack() const override;`
- L88 _public prototype_ `virtual void GoBack() override;`
- L89 _public prototype_ `virtual bool CanGoForward() const override;`
- L90 _public prototype_ `virtual void GoForward() override;`
- L91 _public prototype_ `virtual bool IsLoading() const override;`
- L92 _public prototype_ `virtual void Reload() override;`
- L93 _public prototype_ `virtual void StopLoad() override;`
- L94 _public prototype_ `virtual void ExecuteJavascript(const FString& Script) override;`
- L95 _public prototype_ `virtual void CloseBrowser(bool bForce, bool bBlockTillClosed) override;`
- L96 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L97 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L98 _public prototype_ `virtual int GetLoadError() override;`
- L99 _public prototype_ `virtual void SetIsDisabled(bool bValue) override;`
- L100 _public prototype_ `virtual TSharedPtr<SWindow> GetParentWindow() const override;`
- L101 _public prototype_ `virtual void SetParentWindow(TSharedPtr<SWindow> Window) override;`
- L102 _public prototype_ `virtual void ShowFloatingCloseButton(bool bShow, bool bDraggable) override;`
- L104 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);`
- L105 _public function_ `virtual FOnDocumentStateChanged& OnDocumentStateChanged() override`
- L110 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L111 _public function_ `virtual FOnTitleChanged& OnTitleChanged() override`
- L116 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L117 _public function_ `virtual FOnUrlChanged& OnUrlChanged() override`
- L122 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L123 _public function_ `virtual FOnToolTip& OnToolTip() override`
- L128 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L129 _public function_ `virtual FOnNeedsRedraw& OnNeedsRedraw() override`
- L134 _public function_ `virtual FOnBeforeBrowse& OnBeforeBrowse() override`
- L139 _public function_ `virtual FOnLoadUrl& OnLoadUrl() override`
- L144 _public function_ `virtual FOnCreateWindow& OnCreateWindow() override`
- L149 _public function_ `virtual FOnCloseWindow& OnCloseWindow() override`
- L154 _public function_ `virtual FOnFloatingCloseButtonPressed& OnFloatingCloseButtonPressed() override`
- L159 _public function_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) override`
- L164 _public function_ `virtual FOnBeforePopupDelegate& OnBeforePopup() override`
- L169 _public function_ `virtual FOnBeforeResourceLoadDelegate& OnBeforeResourceLoad() override`
- L174 _public function_ `virtual FOnResourceLoadCompleteDelegate& OnResourceLoadComplete() override`
- L179 _public function_ `virtual FOnConsoleMessageDelegate& OnConsoleMessage() override`
- L184 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L185 _public function_ `virtual FOnShowPopup& OnShowPopup() override`
- L190 _public prototype_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`
- L191 _public function_ `virtual FOnDismissPopup& OnDismissPopup() override`
- L196 _public function_ `virtual FOnShowDialog& OnShowDialog() override`
- L201 _public function_ `virtual FOnDismissAllDialogs& OnDismissAllDialogs() override`
- L206 _public function_ `virtual FOnSuppressContextMenu& OnSuppressContextMenu() override`
- L211 _public function_ `virtual FOnDragWindow& OnDragWindow() override`
- L216 _public function_ `virtual FOnUnhandledKeyDown& OnUnhandledKeyDown() override`
- L221 _public function_ `virtual FOnUnhandledKeyUp& OnUnhandledKeyUp() override`
- L226 _public function_ `virtual FOnUnhandledKeyChar& OnUnhandledKeyChar() override`
- L236 _public prototype_ `void CheckTickActivity() override;` — Called from the WebBrowserSingleton tick event. Should test whether the widget got a tick from Slate last frame and set the state to hidden if not.
- L241 _public prototype_ `void SetTickLastFrame();` — Signal from the widget, meaning that the widget is still active
- L246 _public prototype_ `bool IsVisible();` — Browser's visibility
- L251 _public prototype_ `void FloatingCloseButtonPressed();` — Webvew floating close button was pressed
- L254 _private function_ `void SetTitle(const FString& InTitle)`
- L260 _private prototype_ `void NotifyDocumentError(const FString& InCurrentUrl, int InErrorCode);`
- L261 _private prototype_ `void NotifyDocumentLoadingStateChange(const FString& InCurrentUrl, bool IsLoading);`
- L263 _private prototype_ `bool OnJsMessageReceived(const FString& Command, const TArray<FString>& Params, const FString& Origin);`
- L265 _private prototype_ `FVector2D ConvertMouseEventToLocal(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup);`
- L267 _private member_ `TSharedPtr<SAndroidWebBrowserWidget> BrowserWidget;`
- L270 _private member_ `FString Title;` — Current title of this window.
- L273 _private member_ `FString CurrentUrl;` — Current Url of this window.
- L276 _private member_ `TOptional<FString> ContentsToLoad;` — Optional text to load as a web page.
- L279 _private member_ `FString UserAgentApplication;` — User Agent Application to report
- L282 _private member_ `bool bUseTransparency;` — Whether to enable background transparency
- L285 _private member_ `bool bEnablePaymentRequest;` — Whether to enable the W3C PaymentRequest API on this window.
- L288 _private member_ `FOnDocumentStateChanged DocumentStateChangedEvent;` — Delegate for broadcasting load state changes.
- L291 _private member_ `FOnTitleChanged TitleChangedEvent;` — Delegate for broadcasting title changes.
- L294 _private member_ `FOnUrlChanged UrlChangedEvent;` — Delegate for broadcasting address changes.
- L297 _private member_ `FOnToolTip ToolTipEvent;` — Delegate for broadcasting when the browser wants to show a tool tip.
- L300 _private member_ `FOnNeedsRedraw NeedsRedrawEvent;` — Delegate for notifying that the window needs refreshing.
- L303 _private member_ `FOnBeforeBrowse BeforeBrowseDelegate;` — Delegate that is executed prior to browser navigation.
- L306 _private member_ `FOnLoadUrl LoadUrlDelegate;` — Delegate for overriding Url contents.
- L309 _private member_ `FOnBeforePopupDelegate BeforePopupDelegate;` — Delegate for notifying that a popup window is attempting to open.
- L312 _private member_ `FOnBeforeResourceLoadDelegate BeforeResourceLoadDelegate;` — Delegate for notifying that the browser is about to load a resource.
- L315 _private member_ `FOnResourceLoadCompleteDelegate ResourceLoadCompleteDelegate;` — Delegate that allows for responses to resource loads
- L318 _private member_ `FOnConsoleMessageDelegate ConsoleMessageDelegate;` — Delegate that allows for response to console logs.  Typically used to capture and mirror web logs in client application logs.
- L321 _private member_ `FOnCreateWindow CreateWindowDelegate;` — Delegate for handling requests to create new windows.
- L324 _private member_ `FOnCloseWindow CloseWindowDelegate;` — Delegate for handling requests to close new windows that were created.
- L327 _private member_ `FOnFloatingCloseButtonPressed FloatingCloseButtonPressedDelegate;` — Delegate for handling requests to close from the webview floating close button.
- L330 _private member_ `FOnShowPopup ShowPopupEvent;` — Delegate for handling requests to show the popup menu.
- L333 _private member_ `FOnDismissPopup DismissPopupEvent;` — Delegate for handling requests to dismiss the current popup menu.
- L336 _private member_ `FOnShowDialog ShowDialogDelegate;` — Delegate for showing dialogs.
- L339 _private member_ `FOnDismissAllDialogs DismissAllDialogsDelegate;` — Delegate for dismissing all dialogs.
- L342 _private member_ `FOnSuppressContextMenu SuppressContextMenuDelgate;` — Delegate for suppressing context menu
- L345 _private member_ `FOnUnhandledKeyDown UnhandledKeyDownDelegate;` — Delegate for handling key down events not handled by the browser.
- L348 _private member_ `FOnUnhandledKeyUp UnhandledKeyUpDelegate;` — Delegate for handling key up events not handled by the browser.
- L351 _private member_ `FOnUnhandledKeyChar UnhandledKeyCharDelegate;` — Delegate for handling key char events not handled by the browser.
- L354 _private member_ `FOnDragWindow DragWindowDelegate;` — Delegate that is executed when a drag event is detected in an area of the web page tagged as a drag region.
- L357 _private member_ `EWebBrowserDocumentState DocumentState;` — Current state of the document being loaded.
- L358 _private member_ `int ErrorCode;`
- L360 _private member_ `FMobileJSScriptingPtr Scripting;`
- L362 _private member_ `mutable TOptional<TFunction<void (const FString&)>> GetPageSourceCallback;`
- L364 _private member_ `TSharedPtr<SWindow> ParentWindow;`
- L366 _private member_ `FIntPoint AndroidWindowSize;`
- L369 _private member_ `bool bIsDisabled;` — Tracks whether the widget is currently disabled or not
- L372 _private member_ `bool bIsVisible;` — Tracks whether the widget is currently visible or not
- L375 _private member_ `bool bTickedLastFrame;` — Used to detect when the widget is hidden

#### Free symbols / members of external scopes

- L104 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);`
- L110 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L116 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L122 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L128 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L184 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L190 _delegate_ `DECLARE_DERIVED_EVENT(FAndroidWebBrowserWindow, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`
- L378 _typedef_ `typedef FAndroidWebBrowserWindow FWebBrowserWindow;`

### `Source/Runtime/WebBrowser/Private/Apple/AppleCookieManager.h` (Private)


#### class `FAppleCookieManager`  
`class FAppleCookieManager : public IWebBrowserCookieManager , public TSharedFromThis<FAppleCookieManager>`  
_L14-31_
- inherits: `IWebBrowserCookieManager,TSharedFromThis<FAppleCookieManager>`
- desc: Implementation of interface for dealing with a Web Browser cookies for iOS.
- L20 _public member_ `static NSUUID *CookieManagerIdentifier;` — This is a hack for now until I figure out how to persist cookie managers' UUIDs
- L24 _public prototype_ `virtual void SetCookie(const FString& URL, const FCookie& Cookie, TFunction<void(bool)> Completed = nullptr) override;`
- L25 _public prototype_ `virtual void DeleteCookies(const FString& URL = TEXT(""), const FString& CookieName = TEXT(""), TFunction<void(int)> Completed = nullptr) override;`
- L29 _public prototype_ `FAppleCookieManager();`
- L30 _public prototype_ `virtual ~FAppleCookieManager();`

### `Source/Runtime/WebBrowser/Private/Apple/ApplePlatformWebBrowser.h` (Private)


#### class `FWebBrowserWindow`  
`class FWebBrowserWindow : public IWebBrowserWindow , public TSharedFromThis<FWebBrowserWindow>`  
_L133-493_
- inherits: `IWebBrowserWindow,TSharedFromThis<FWebBrowserWindow>`
- desc: Implementation of interface for dealing with a Web Browser window.
- L150 _private prototype_ `FWebBrowserWindow(FString InUrl, TOptional<FString> InContentsToLoad, bool ShowErrorMessage, bool bThumbMouseButtonNavigation, bool bUseTransparency, bool bInJSBindingToLoweringEnabled, FString InUserAgentApplication, bool bMobileJSReturnInDict);` — Creates and initializes a new instance. @param InUrl The Initial URL that will be loaded. @param InContentsToLoad Optional string to load as a web page. @param InShowErrorMessage Whether to show an error message in case of loading errors.
- L155 _private prototype_ `TSharedRef<SViewport> CreateWidget();` — Create the SWidget for this WebBrowserWindow
- L159 _public prototype_ `virtual ~FWebBrowserWindow();` — Virtual Destructor.
- L165 _public prototype_ `virtual void LoadURL(FString NewURL) override;`
- L166 _public prototype_ `virtual void LoadString(FString Contents, FString DummyURL) override;`
- L167 _public prototype_ `virtual void SetViewportSize(FIntPoint ViewportWindowSize, FIntPoint WindowPos) override;`
- L168 _public prototype_ `virtual FIntPoint GetViewportSize() const override;`
- L169 _public prototype_ `virtual FSlateShaderResource* GetTexture(bool bIsPopup = false) override;`
- L170 _public prototype_ `virtual bool IsValid() const override;`
- L171 _public prototype_ `virtual bool IsInitialized() const override;`
- L172 _public prototype_ `virtual bool IsClosing() const override;`
- L173 _public prototype_ `virtual EWebBrowserDocumentState GetDocumentLoadingState() const override;`
- L174 _public prototype_ `virtual FString GetTitle() const override;`
- L175 _public prototype_ `virtual FString GetUrl() const override;`
- L176 _public prototype_ `virtual bool OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L177 _public prototype_ `virtual bool OnKeyUp(const FKeyEvent& InKeyEvent) override;`
- L178 _public prototype_ `virtual bool OnKeyChar(const FCharacterEvent& InCharacterEvent) override;`
- L179 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L180 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L181 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L182 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L183 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L184 _public prototype_ `virtual void SetSupportsMouseWheel(bool bValue) override;`
- L185 _public prototype_ `virtual bool GetSupportsMouseWheel() const override;`
- L186 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L187 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent, bool bIsPopup) override;`
- L188 _public prototype_ `virtual void OnFocus(bool SetFocus, bool bIsPopup) override;`
- L189 _public prototype_ `virtual void OnCaptureLost() override;`
- L190 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L191 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L192 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L193 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L194 _public prototype_ `virtual bool CanGoBack() const override;`
- L195 _public prototype_ `virtual void GoBack() override;`
- L196 _public prototype_ `virtual bool CanGoForward() const override;`
- L197 _public prototype_ `virtual void GoForward() override;`
- L198 _public prototype_ `virtual bool IsLoading() const override;`
- L199 _public prototype_ `virtual void Reload() override;`
- L200 _public prototype_ `virtual void StopLoad() override;`
- L201 _public prototype_ `virtual void ExecuteJavascript(const FString& Script) override;`
- L202 _public prototype_ `virtual void CloseBrowser(bool bForce, bool bBlockTillClosed) override;`
- L203 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L204 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L205 _public prototype_ `virtual void GetSource(TFunction<void (const FString&)> Callback) const;`
- L206 _public prototype_ `virtual int GetLoadError() override;`
- L207 _public prototype_ `virtual void SetIsDisabled(bool bValue) override;`
- L208 _public prototype_ `virtual TSharedPtr<SWindow> GetParentWindow() const override;`
- L209 _public prototype_ `virtual void SetParentWindow(TSharedPtr<SWindow> Window) override;`
- L210 _public prototype_ `virtual void ShowFloatingCloseButton(bool bShow, bool bDraggable) override;`
- L214 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);`
- L215 _public function_ `virtual FOnDocumentStateChanged& OnDocumentStateChanged() override`
- L220 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L221 _public function_ `virtual FOnTitleChanged& OnTitleChanged() override`
- L226 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L227 _public function_ `virtual FOnUrlChanged& OnUrlChanged() override`
- L232 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L233 _public function_ `virtual FOnToolTip& OnToolTip() override`
- L238 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L239 _public function_ `virtual FOnNeedsRedraw& OnNeedsRedraw() override`
- L244 _public function_ `virtual FOnBeforeBrowse& OnBeforeBrowse() override`
- L249 _public function_ `virtual FOnLoadUrl& OnLoadUrl() override`
- L254 _public function_ `virtual FOnCreateWindow& OnCreateWindow() override`
- L259 _public function_ `virtual FOnCloseWindow& OnCloseWindow() override`
- L264 _public function_ `virtual FOnFloatingCloseButtonPressed& OnFloatingCloseButtonPressed() override`
- L269 _public function_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) override`
- L275 _public function_ `virtual FOnBeforeResourceLoadDelegate& OnBeforeResourceLoad() override`
- L280 _public function_ `virtual FOnResourceLoadCompleteDelegate& OnResourceLoadComplete() override`
- L285 _public function_ `virtual FOnConsoleMessageDelegate& OnConsoleMessage() override`
- L290 _public function_ `virtual FOnBeforePopupDelegate& OnBeforePopup() override`
- L295 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L296 _public function_ `virtual FOnShowPopup& OnShowPopup() override`
- L301 _public prototype_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`
- L302 _public function_ `virtual FOnDismissPopup& OnDismissPopup() override`
- L307 _public function_ `virtual FOnShowDialog& OnShowDialog() override`
- L312 _public function_ `virtual FOnDismissAllDialogs& OnDismissAllDialogs() override`
- L317 _public function_ `virtual FOnSuppressContextMenu& OnSuppressContextMenu() override`
- L322 _public function_ `virtual FOnDragWindow& OnDragWindow() override`
- L327 _public prototype_ `void NotifyDocumentLoadingStateChange(const FString& InCurrentUrl, bool IsLoading);`
- L329 _public prototype_ `void NotifyDocumentError(const FString& InCurrentUrl, int InErrorCode);`
- L331 _public prototype_ `bool OnJsMessageReceived(const FString& Command, const TArray<FString>& Params, const FString& Origin);`
- L333 _public function_ `virtual FOnUnhandledKeyDown& OnUnhandledKeyDown() override`
- L338 _public function_ `virtual FOnUnhandledKeyUp& OnUnhandledKeyUp() override`
- L343 _public function_ `virtual FOnUnhandledKeyChar& OnUnhandledKeyChar() override`
- L348 _public prototype_ `void NotifyUrlChanged(const FString& InCurrentUrl);`
- L353 _public prototype_ `void CheckTickActivity() override;` — Called from the WebBrowserSingleton tick event. Should test whether the widget got a tick from Slate last frame and set the state to hidden if not.
- L358 _public prototype_ `void SetTickLastFrame();` — Signal from the widget, meaning that the widget is still active
- L363 _public prototype_ `bool IsVisible();` — Browser's visibility
- L365 _public prototype_ `bool Is3D();`
- L370 _public prototype_ `void FloatingCloseButtonPressed();` — Webview floating close button was pressed
- L373 _public function_ `void SetTitle(const FString& InTitle)`
- L381 _private prototype_ `TOptional<FSlateRenderTransform> GetWebBrowserRenderTransform() const;`
- L382 _private prototype_ `void RedirectNSEvent();`
- L384 _private member_ `TSharedPtr<SAppleWebBrowserWidget> BrowserWidget;`
- L387 _private member_ `FString Title;` — Current title of this window.
- L390 _private member_ `FString CurrentUrl;` — Current Url of this window.
- L393 _private member_ `FString UserAgentApplication;` — User-Agent Application to report.
- L396 _private member_ `TOptional<FString> ContentsToLoad;` — Optional text to load as a web page.
- L399 _private member_ `bool bUseTransparency;` — Whether to enable background transparency
- L404 _private member_ `FOnDocumentStateChanged DocumentStateChangedEvent;` — Delegate for broadcasting load state changes.
- L407 _private member_ `FOnTitleChanged TitleChangedEvent;` — Delegate for broadcasting title changes.
- L410 _private member_ `FOnUrlChanged UrlChangedEvent;` — Delegate for broadcasting address changes.
- L413 _private member_ `FOnToolTip ToolTipEvent;` — Delegate for broadcasting when the browser wants to show a tool tip.
- L416 _private member_ `FOnNeedsRedraw NeedsRedrawEvent;` — Delegate for notifying that the window needs refreshing.
- L419 _private member_ `FOnBeforeBrowse BeforeBrowseDelegate;` — Delegate that is executed prior to browser navigation.
- L422 _private member_ `FOnLoadUrl LoadUrlDelegate;` — Delegate for overriding Url contents.
- L425 _private member_ `FOnBeforePopupDelegate BeforePopupDelegate;` — Delegate for notifying that a popup window is attempting to open.
- L428 _private member_ `FOnBeforeResourceLoadDelegate BeforeResourceLoadDelegate;` — Delegate for notifying that the browser is about to load a resource.
- L431 _private member_ `FOnResourceLoadCompleteDelegate ResourceLoadCompleteDelegate;` — Delegate that allows for responses to resource loads
- L434 _private member_ `FOnConsoleMessageDelegate ConsoleMessageDelegate;` — Delegate that allows for response to console logs.  Typically used to capture and mirror web logs in client application logs.
- L437 _private member_ `FOnCreateWindow CreateWindowDelegate;` — Delegate for handling requests to create new windows.
- L440 _private member_ `FOnCloseWindow CloseWindowDelegate;` — Delegate for handling requests to close new windows that were created.
- L443 _private member_ `FOnFloatingCloseButtonPressed FloatingCloseButtonPressedDelegate;` — Delegate for handling requests to close from the webview floating close button.
- L446 _private member_ `FOnShowPopup ShowPopupEvent;` — Delegate for handling requests to show the popup menu.
- L449 _private member_ `FOnDismissPopup DismissPopupEvent;` — Delegate for handling requests to dismiss the current popup menu.
- L452 _private member_ `FOnShowDialog ShowDialogDelegate;` — Delegate for showing dialogs.
- L455 _private member_ `FOnDismissAllDialogs DismissAllDialogsDelegate;` — Delegate for dismissing all dialogs.
- L458 _private member_ `FOnSuppressContextMenu SuppressContextMenuDelgate;` — Delegate for suppressing context menu
- L461 _private member_ `FOnDragWindow DragWindowDelegate;` — Delegate that is executed when a drag event is detected in an area of the web page tagged as a drag region.
- L464 _private member_ `EWebBrowserDocumentState DocumentState;` — Current state of the document being loaded.
- L465 _private member_ `int ErrorCode;`
- L467 _private member_ `FMobileJSScriptingPtr Scripting;`
- L468 _private member_ `TSharedPtr<FWebView3DInputHandler> WebView3DInput;`
- L470 _private member_ `mutable TOptional<TFunction<void(const FString&)>> GetPageSourceCallback;`
- L472 _private member_ `FOnUnhandledKeyDown UnhandledKeyDownDelegate;` — Delegate for handling key down events not handled by the browser.
- L475 _private member_ `FOnUnhandledKeyUp UnhandledKeyUpDelegate;` — Delegate for handling key up events not handled by the browser.
- L478 _private member_ `FOnUnhandledKeyChar UnhandledKeyCharDelegate;` — Delegate for handling key char events not handled by the browser.
- L480 _private member_ `TWeakPtr<SWindow> ParentWindow;`
- L481 _private member_ `FDelegateHandle ParentDockTabDelegate;`
- L483 _private member_ `FIntPoint WindowSize;`
- L486 _private member_ `bool bIsDisabled;` — Tracks whether the widget is currently disabled or not
- L489 _private member_ `bool bIsVisible;` — Tracks whether the widget is currently visible or not
- L492 _private member_ `bool bTickedLastFrame;` — Used to detect when the widget is hidden

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleWebBrowser, Log, All);`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleWebBrowser, Log, All);`
- L47 _variable_ `SAppleWebBrowserWidget* WebBrowserWidget;`
- L48 _variable_ `FTextureRHIRef VideoTexture;`
- L49 _variable_ `TWeakPtr<SWindow> Current3DWindow;`
- L50 _variable_ `bool bNeedsAddToView;`
- L51 _variable_ `bool Is3DBrowser;`
- L52 _variable_ `bool bVideoTextureValid;`
- L53 _variable_ `bool bUsingIndirectRendering;`
- L54 _variable_ `bool bAllowScreenshots;`
- L58 _variable_ `std::atomic<bool> bShuttingDown;` — needs to be atomic as it is set on the game thread but read from AppKit/UIKit's UI thread during WebKit callbacks
- L59 _variable_ `bool bReadyToAddToNativeLayer;`
- L214 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);`
- L220 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L226 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L232 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L238 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L295 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L301 _delegate_ `DECLARE_DERIVED_EVENT(FWebBrowserWindow, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`

### `Source/Runtime/WebBrowser/Private/Apple/WebView3DInputHandler.h` (Private)


#### class `FWebView3DInputHandler`  
`class FWebView3DInputHandler`  
_L18-48_
- desc: Helper class for ApplePlatformWebBrowser's FWebBrowserWindow to handle input with 3D WKWebView Web Browser widgets. @warning Due to WebKit limitations, all input events dispatched in 3D mode will be untrusted (i.e. Event.isTrusted will be false).
- L22 _public prototype_ `FWebView3DInputHandler();`
- L24 _public prototype_ `void SendMouseEventToJS(IWebBrowserWindow& InWindow, const FString& EventName, const FPointerEvent& MouseEvent);`
- L26 _public prototype_ `void SendCharEventToJS(IWebBrowserWindow& InWindow, const FCharacterEvent& CharEvent);`
- L27 _public prototype_ `void SendKeyEventToJS(IWebBrowserWindow& InWindow, const FString& EventName, const FKeyEvent& KeyEvent);`
- L31 _private prototype_ `FString BoolToString(bool InBool);`
- L32 _private prototype_ `FString GetCurrentJSElement();`
- L34 _private prototype_ `void DispatchInputEvent(IWebBrowserWindow& InWindow, const FString& InputType, TCHAR* InputData);`
- L36 _private prototype_ `FString GetModifierKeyStatus();`
- L37 _private prototype_ `bool CheckIfCharacterIsInputable(TCHAR CharToInput);`
- L39 _private prototype_ `void UpdateModifierKeys(const FKey& Key, bool KeyDown);`
- L41 _private member_ `bool bCtrlKeyDown;`
- L42 _private member_ `bool bAltKeyDown;`
- L43 _private member_ `bool bCmdKeyDown;`
- L44 _private member_ `bool bShiftKeyDown;`
- L45 _private member_ `bool bCapsLockOn;`
- L47 _private member_ `FVector2f MousePos;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebView3DInputHandler, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebView3DInputHandler, Log, All);`

### `Source/Runtime/WebBrowser/Private/Apple/WebViewCloseButton.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/WebBrowser/Private/CEF/CEFBrowserApp.h` (Private)


#### class `FCEFBrowserApp`  
`class FCEFBrowserApp : public CefApp, public CefBrowserProcessHandler`  
_L17-46_
- inherits: `CefApp,CefBrowserProcessHandler`
- desc: Implements CEF App and other Process level interfaces
- L25 _public prototype_ `FCEFBrowserApp();` — Default Constructor
- L28 _public prototype_ `bool TickMessagePump(float DeltaTime, bool bForce);` — Used to pump the CEF message loop whenever OnScheduleMessagePumpWork is triggered
- L32 _private function_ `virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override` — CefApp methods.
- L33 _private prototype_ `virtual void OnBeforeCommandLineProcessing(const CefString& ProcessType, CefRefPtr< CefCommandLine > CommandLine) override;`
- L35 _private prototype_ `virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> CommandLine) override;` — CefBrowserProcessHandler methods:
- L36 _private prototype_ `virtual void OnScheduleMessagePumpWork(int64_t delay_ms) override;`
- L37 _private prototype_ `virtual bool OnAlreadyRunningAppRelaunch(CefRefPtr<CefCommandLine> CommandLine, const CefString& CurrentDirectory) override;`
- L40 _private prototype_ `IMPLEMENT_REFCOUNTING(FCEFBrowserApp);` — Include the default reference counting implementation.
- L43 _private member_ `FCriticalSection MessagePumpCountdownCS;` — Lock for access MessagePumpCountdown
- L45 _private member_ `int64 MessagePumpCountdown;` — Countdown in milliseconds until CefDoMessageLoopWork is called.  Updated by OnScheduleMessagePumpWork

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCEFBrowser, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCEFBrowser, Log, All);`

### `Source/Runtime/WebBrowser/Private/CEF/CEFBrowserByteResource.h` (Private)


#### class `FCEFBrowserByteResource`  
`class FCEFBrowserByteResource : public CefResourceHandler`  
_L17-40_
- inherits: `CefResourceHandler`
- desc: Implements a resource handler that will return the contents of a string as the result.
- L23 _public prototype_ `FCEFBrowserByteResource(const CefRefPtr<CefPostDataElement>& PostData, const FString& InMimeType);`
- L24 _public prototype_ `~FCEFBrowserByteResource();`
- L27 _public prototype_ `virtual void Cancel() override;` — CefResourceHandler interface
- L28 _public prototype_ `virtual void GetResponseHeaders(CefRefPtr<CefResponse> Response, int64_t& ResponseLength, CefString& RedirectUrl) override;`
- L29 _public prototype_ `virtual bool ProcessRequest(CefRefPtr<CefRequest> Request, CefRefPtr<CefCallback> Callback) override;`
- L30 _public prototype_ `virtual bool ReadResponse(void* DataOut, int BytesToRead, int& BytesRead, CefRefPtr<CefCallback> Callback) override;`
- L33 _private member_ `int32 Position;`
- L34 _private member_ `int32 Size;`
- L35 _private member_ `unsigned char* Buffer;`
- L36 _private member_ `FString MimeType;`
- L39 _private prototype_ `IMPLEMENT_REFCOUNTING(FCEFBrowserByteResource);` — Include the default reference counting implementation.

### `Source/Runtime/WebBrowser/Private/CEF/CEFBrowserClosureTask.h` (Private)


#### class `FCEFBrowserClosureTask`  
`class FCEFBrowserClosureTask : public CefTask`  
_L11-29_
- inherits: `CefTask`
- desc: Helper for posting a closure as a task
- L15 _public function_ `FCEFBrowserClosureTask(CefRefPtr<CefBaseRefCounted> InHandle, TFunction<void ()> InClosure) : Handle(InHandle) , Closure(InClosure)`
- L20 _public function_ `virtual void Execute() override`
- L26 _private member_ `CefRefPtr<CefBaseRefCounted> Handle;` — Used so the handler will not go out of scope before the closure is executed.
- L27 _private member_ `TFunction<void ()> Closure;`
- L28 _private prototype_ `IMPLEMENT_REFCOUNTING(FCEFBrowserClosureTask);`

### `Source/Runtime/WebBrowser/Private/CEF/CEFBrowserHandler.h` (Private)


#### class `FCEFBrowserHandler`  
`class FCEFBrowserHandler : public CefClient , public CefDisplayHandler , public CefLifeSpanHandler , public CefLoadHandler , public CefRenderHandler , public CefRequestHandler , public CefKeyboardHandler , public CefJSDialogHandler , public CefContextMenuHandler , public CefDragHandler , public CefResourceRequestHandler , public CefRequestContextHandler , public CefCookieAccessFilter , public CefDialogHandler`  
_L27-236_
- inherits: `CefClient,CefDisplayHandler,CefLifeSpanHandler,CefLoadHandler,CefRenderHandler,CefRequestHandler,CefKeyboardHandler,CefJSDialogHandler,CefContextMenuHandler,CefDragHandler,CefResourceRequestHandler,CefRequestContextHandler,CefCookieAccessFilter,CefDialogHandler`
- desc: Implements CEF Client and other Browser level interfaces.
- L46 _public prototype_ `FCEFBrowserHandler(bool InUseTransparency, bool InInterceptLoadRequests, const TArray<FString>& AltRetryDomains = TArray<FString>(), const TArray<FString>& AuthorizationHeaderAllowListURLS = TArray<FString>());` — Default constructor.
- L53 _public prototype_ `void SetBrowserWindow(TSharedPtr<FCEFWebBrowserWindow> InBrowserWindow);` — Pass in a pointer to our Browser Window so that events can be passed on. @param InBrowserWindow The browser window this will be handling.
- L60 _public function_ `void SetPopupFeatures(const TSharedPtr<FCEFBrowserPopupFeatures>& InPopupFeatures)` — Sets the browser window features and settings for popups which will be passed along when creating the new window. @param InPopupFeatures The popup features and settings for the window.
- L66 _public function_ `virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override` — CefClient Interface
- L67 _public function_ `virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override`
- L68 _public function_ `virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override`
- L69 _public function_ `virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override`
- L70 _public function_ `virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override`
- L71 _public function_ `virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override`
- L72 _public function_ `virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override`
- L73 _public function_ `virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override`
- L74 _public function_ `virtual CefRefPtr<CefDragHandler> GetDragHandler() override`
- L75 _public function_ `virtual CefRefPtr<CefDialogHandler> GetDialogHandler() override`
- L76 _public prototype_ `virtual CefRefPtr<CefCookieAccessFilter> GetCookieAccessFilter(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request) override;`
- L77 _public prototype_ `virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> frame, CefProcessId SourceProcess, CefRefPtr<CefProcessMessage> Message) override;`
- L80 _public prototype_ `virtual void OnTitleChange(CefRefPtr<CefBrowser> Browser, const CefString& Title) override;` — CefDisplayHandler Interface
- L81 _public prototype_ `virtual void OnAddressChange(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, const CefString& Url) override;`
- L82 _public prototype_ `virtual bool OnTooltip(CefRefPtr<CefBrowser> Browser, CefString& Text) override;`
- L83 _public prototype_ `virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> Browser, cef_log_severity_t level, const CefString& Message, const CefString& Source, int Line) override;`
- L86 _public prototype_ `virtual void OnAfterCreated(CefRefPtr<CefBrowser> Browser) override;` — CefLifeSpanHandler Interface
- L87 _public prototype_ `virtual bool DoClose(CefRefPtr<CefBrowser> Browser) override;`
- L88 _public prototype_ `virtual void OnBeforeClose(CefRefPtr<CefBrowser> Browser) override;`
- L89 _public function_ `virtual bool OnBeforePopup(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, #if CEF_VERSION_MAJOR >= 147 int , #endif const CefString& Target_Url, const CefString& Target_Frame_Name, CefLifeSpanHandler::WindowOpenDisposition , bool , const CefPopupFeatures& PopupFeatures, CefWindowInfo& WindowInfo, CefRefPtr<CefClient>& Client, CefBrowserSettings& Settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access) override`
- L107 _public prototype_ `virtual bool OnBeforePopup(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, const CefString& Target_Url, const CefString& Target_Frame_Name, const CefPopupFeatures& PopupFeatures, CefWindowInfo& WindowInfo, CefRefPtr<CefClient>& Client, CefBrowserSettings& Settings, bool* no_javascript_access);`
- L110 _public prototype_ `virtual void OnLoadError(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefLoadHandler::ErrorCode InErrorCode, const CefString& ErrorText, const CefString& FailedUrl) override;` — CefLoadHandler Interface
- L111 _public prototype_ `virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override;`
- L112 _public prototype_ `virtual void OnLoadStart(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, TransitionType CefTransitionType) override;`
- L115 _public prototype_ `virtual bool GetRootScreenRect(CefRefPtr<CefBrowser> Browser, CefRect& Rect) override;` — CefRenderHandler Interface
- L116 _public prototype_ `virtual void GetViewRect(CefRefPtr<CefBrowser> Browser, CefRect& Rect) override;`
- L117 _public prototype_ `virtual void OnPaint(CefRefPtr<CefBrowser> Browser, PaintElementType Type, const RectList& DirtyRects, const void* Buffer, int Width, int Height) override;`
- L118 _public prototype_ `virtual void OnAcceleratedPaint(CefRefPtr<CefBrowser> Browser, PaintElementType Type, const RectList& DirtyRects, const CefAcceleratedPaintInfo& SharedHandle) override;`
- L119 _public prototype_ `virtual void OnPopupShow(CefRefPtr<CefBrowser> Browser, bool bShow) override;`
- L120 _public prototype_ `virtual void OnPopupSize(CefRefPtr<CefBrowser> Browser, const CefRect& Rect) override;`
- L121 _public prototype_ `virtual bool GetScreenInfo(CefRefPtr<CefBrowser> Browser, CefScreenInfo& ScreenInfo) override;`
- L124 _public prototype_ `virtual bool OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, cef_cursor_type_t type, const CefCursorInfo& custom_cursor_info) override;` — CefDisplayHandler interface
- L126 _public prototype_ `virtual void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> Browser, const CefRange& SelectionRange, const CefRenderHandler::RectList& CharacterBounds) override;`
- L127 _public prototype_ `virtual void OnTextSelectionChanged(CefRefPtr<CefBrowser> Browser, const CefString& SelectedText, const CefRange& SelectionRange) override;`
- L131 _public prototype_ `virtual CefResourceRequestHandler::ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, CefRefPtr<CefCallback> Callback) override;` — CefRequestHandler Interface
- L132 _public prototype_ `virtual void OnResourceLoadComplete(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, CefRefPtr<CefResponse> Response, URLRequestStatus Status, int64_t Received_content_length) override;`
- L133 _public prototype_ `virtual void OnResourceRedirect(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response, CefString& new_url) override;`
- L134 _public prototype_ `virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> Browser, TerminationStatus Status, int error_code, const CefString& error_string) override;`
- L135 _public prototype_ `virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, bool user_gesture, bool IsRedirect) override;`
- L136 _public prototype_ `virtual CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request) override;`
- L137 _public prototype_ `virtual bool OnCertificateError(CefRefPtr<CefBrowser> Browser, cef_errorcode_t CertError, const CefString& RequestUrl, CefRefPtr<CefSSLInfo> SslInfo, CefRefPtr<CefCallback> Callback) override;`
- L138 _public prototype_ `virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling) override;`
- L141 _public prototype_ `virtual bool OnKeyEvent(CefRefPtr<CefBrowser> Browser, const CefKeyEvent& Event, CefEventHandle OsEvent) override;` — CefKeyboardHandler interface
- L144 _public prototype_ `virtual bool CanSaveCookie(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, CefRefPtr<CefResponse> Response, const CefCookie& Cookie) override;` — CefCookieAccessFilter interface
- L145 _public prototype_ `virtual bool CanSendCookie(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, const CefCookie& Cookie) override;`
- L148 _public prototype_ `virtual bool OnJSDialog(CefRefPtr<CefBrowser> Browser, const CefString& OriginUrl, JSDialogType DialogType, const CefString& MessageText, const CefString& DefaultPromptText, CefRefPtr<CefJSDialogCallback> Callback, bool& OutSuppressMessage) override;` — CefJSDialogHandler interface
- L149 _public prototype_ `virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> Browser, const CefString& MessageText, bool IsReload, CefRefPtr<CefJSDialogCallback> Callback) override;`
- L150 _public prototype_ `virtual void OnResetDialogState(CefRefPtr<CefBrowser> Browser) override;`
- L153 _public prototype_ `virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefContextMenuParams> Params, CefRefPtr<CefMenuModel> Model) override;` — CefContextMenuHandler interface
- L156 _public prototype_ `virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& Regions) override;` — CefDragHandler interface
- L159 _public prototype_ `virtual bool OnFileDialog(CefRefPtr<CefBrowser> Browser, FileDialogMode Mode, const CefString& Title, const CefString& DefaultFilePath, const std::vector<CefString>& AcceptFilters, const std::vector<CefString>& AcceptExtensions, const std::vector<CefString>& AcceptDescriptions, CefRefPtr<CefFileDialogCallback> Callback) override;` — CefDialogHandler interface
- L162 _public function_ `IWebBrowserWindow::FOnBeforePopupDelegate& OnBeforePopup()`
- L167 _public function_ `IWebBrowserWindow::FOnCreateWindow& OnCreateWindow()`
- L172 _public typedef_ `typedef TMap<FString, FString> FRequestHeaders;`
- L173 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnBeforeResourceLoadDelegate, const CefString& , CefRequest::ResourceType , FRequestHeaders& , const bool );`
- L174 _public function_ `FOnBeforeResourceLoadDelegate& OnBeforeResourceLoad()`
- L179 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnResourceLoadCompleteDelegate, const CefString& , CefRequest::ResourceType , CefResourceRequestHandler::URLRequestStatus , int64 );`
- L180 _public function_ `FOnResourceLoadCompleteDelegate& OnResourceLoadComplete()`
- L185 _public prototype_ `DECLARE_DELEGATE_FiveParams(FOnConsoleMessageDelegate, CefRefPtr<CefBrowser> , cef_log_severity_t , const CefString& , const CefString& , int32 );`
- L186 _public function_ `FOnConsoleMessageDelegate& OnConsoleMessage()`
- L191 _public prototype_ `bool URLRequestAllowsCredentials(const FString& URL) const;`
- L195 _private prototype_ `bool ShowDevTools(const CefRefPtr<CefBrowser>& Browser);`
- L197 _private member_ `bool bUseTransparency;`
- L198 _private member_ `bool bAllowAllCookies;`
- L199 _private member_ `bool bInterceptLoadRequests;`
- L201 _private member_ `TArray<FString> AltRetryDomains;`
- L202 _private member_ `uint32 AltRetryDomainIdx = 0;`
- L205 _private member_ `TArray<FString> AuthorizationHeaderAllowListURLS;` — Domains we allow sending an authorization header too even if the request doesn't otherwise indicate support
- L208 _private member_ `TMap<FString, CefRequest::ResourceType> MainFrameLoadTypes;` — Keep track of URLs we see being loaded and the type of load it is
- L211 _private member_ `IWebBrowserWindow::FOnBeforePopupDelegate BeforePopupDelegate;` — Delegate for notifying that a popup window is attempting to open.
- L214 _private member_ `IWebBrowserWindow::FOnCreateWindow CreateWindowDelegate;` — Delegate for handling requests to create new windows.
- L217 _private member_ `FOnBeforeResourceLoadDelegate BeforeResourceLoadDelegate;` — Delegate for handling adding additional headers to requests
- L220 _private member_ `FOnResourceLoadCompleteDelegate ResourceLoadCompleteDelegate;` — Delegate that allows response to the status of resource loads
- L223 _private member_ `FOnConsoleMessageDelegate ConsoleMessageDelegate;` — Delegate that allows for response to console logs.  Typically used to capture and mirror web logs in client application logs.
- L226 _private member_ `TWeakPtr<FCEFWebBrowserWindow> BrowserWindowPtr;` — Weak Pointer to our Web Browser window so that events can be passed on while it's valid.
- L229 _private member_ `CefRefPtr<FCEFBrowserHandler> ParentHandler;` — Pointer to the parent web browser handler
- L232 _private member_ `TSharedPtr<FCEFBrowserPopupFeatures> BrowserPopupFeatures;` — Stores popup window features and settings
- L235 _private prototype_ `IMPLEMENT_REFCOUNTING(FCEFBrowserHandler);` — Include the default reference counting implementation.

#### Free symbols / members of external scopes

- L173 _delegate_ `DECLARE_DELEGATE_FourParams(FOnBeforeResourceLoadDelegate, const CefString& , CefRequest::ResourceType , FRequestHeaders& , const bool );`
- L179 _delegate_ `DECLARE_DELEGATE_FourParams(FOnResourceLoadCompleteDelegate, const CefString& , CefRequest::ResourceType , CefResourceRequestHandler::URLRequestStatus , int64 );`
- L185 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnConsoleMessageDelegate, CefRefPtr<CefBrowser> , cef_log_severity_t , const CefString& , const CefString& , int32 );`

### `Source/Runtime/WebBrowser/Private/CEF/CEFBrowserPopupFeatures.h` (Private)


#### class `FCEFBrowserPopupFeatures`  
`class FCEFBrowserPopupFeatures : public IWebBrowserPopupFeatures`  
_L19-68_
- inherits: `IWebBrowserPopupFeatures`
- L23 _public prototype_ `FCEFBrowserPopupFeatures();`
- L24 _public prototype_ `FCEFBrowserPopupFeatures(const CefPopupFeatures& PopupFeatures);`
- L25 _public prototype_ `virtual ~FCEFBrowserPopupFeatures();`
- L26 _public prototype_ `void SetResizable(const bool bResize);`
- L30 _public prototype_ `virtual int GetX() const override;`
- L31 _public prototype_ `virtual bool IsXSet() const override;`
- L32 _public prototype_ `virtual int GetY() const override;`
- L33 _public prototype_ `virtual bool IsYSet() const override;`
- L34 _public prototype_ `virtual int GetWidth() const override;`
- L35 _public prototype_ `virtual bool IsWidthSet() const override;`
- L36 _public prototype_ `virtual int GetHeight() const override;`
- L37 _public prototype_ `virtual bool IsHeightSet() const override;`
- L38 _public prototype_ `virtual bool IsMenuBarVisible() const override;`
- L39 _public prototype_ `virtual bool IsStatusBarVisible() const override;`
- L40 _public prototype_ `virtual bool IsToolBarVisible() const override;`
- L41 _public prototype_ `virtual bool IsLocationBarVisible() const override;`
- L42 _public prototype_ `virtual bool IsScrollbarsVisible() const override;`
- L43 _public prototype_ `virtual bool IsResizable() const override;`
- L44 _public prototype_ `virtual bool IsFullscreen() const override;`
- L45 _public prototype_ `virtual bool IsDialog() const override;`
- L46 _public prototype_ `virtual TArray<FString> GetAdditionalFeatures() const override;`
- L50 _private member_ `int X;`
- L51 _private member_ `bool bXSet;`
- L52 _private member_ `int Y;`
- L53 _private member_ `bool bYSet;`
- L54 _private member_ `int Width;`
- L55 _private member_ `bool bWidthSet;`
- L56 _private member_ `int Height;`
- L57 _private member_ `bool bHeightSet;`
- L59 _private member_ `bool bMenuBarVisible;`
- L60 _private member_ `bool bStatusBarVisible;`
- L61 _private member_ `bool bToolBarVisible;`
- L62 _private member_ `bool bLocationBarVisible;`
- L63 _private member_ `bool bScrollbarsVisible;`
- L64 _private member_ `bool bResizable;`
- L66 _private member_ `bool bIsFullscreen;`
- L67 _private member_ `bool bIsDialog;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFCapturedFrame.h` (Private)


#### struct `FCEFCapturedFrame`  
`struct FCEFCapturedFrame`  
_L12-31_
- reflection: `USTRUCT()`
- L19 _public prototype_ `bool SetBufferAsB8G8R8A8(const void* InBufferB8G8R8A8, const int32 InBufferWidth, const int32 InBufferHeight, const bool bSkipTransparencyTest);`
- L20 _public prototype_ `bool ClearBuffer();`
- L22 _public prototype_ `bool IsEmpty() const;`
- L24 _public prototype_ `FSlateTextureData* CreateSlateTextureData(const FIntPoint& TextureSize) const;`
- L28 _private member_ `TArray<uint8> BufferData;`
- L29 _private member_ `FUintPoint BufferDimensions = FUintPoint::ZeroValue;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFImeHandler.h` (Private)


#### class `FCEFImeHandler`  
`class FCEFImeHandler : public TSharedFromThis<FCEFImeHandler>`  
_L39-124_
- inherits: `TSharedFromThis<FCEFImeHandler>`
- L43 _public prototype_ `FCEFImeHandler(CefRefPtr<CefBrowser> Browser);`
- L45 _public prototype_ `void UnbindCefBrowser();`
- L46 _public prototype_ `void CacheBrowserSlateInfo(const TSharedRef<SWidget>& Widget);`
- L47 _public prototype_ `void SetFocus(bool bInFocus);`
- L48 _public prototype_ `void UpdateCachedGeometry(const FGeometry& AllottedGeometry);`
- L56 _public prototype_ `void CEFCompositionRangeChanged(const CefRange& SelectionRange, const CefRenderHandler::RectList& CharacterBounds);` — Called when the IME composition DOM node has changed. @param SelectionRange The range of characters that have been selected. @param CharacterBounds The bounds of each character in view coordinates.
- L63 _public prototype_ `void CEFTextSelectionChanged(const CefString& SelectedText, const CefRange& SelectionRange);` — Called when the text selection has changed for a text field in a web page, used for IME. @param SelectedText The selected text. @param SelectionRange The range of characters that have been selected.
- L73 _public prototype_ `bool OnProcessMessageReceived(CefRefPtr<CefBrowser> Browser, CefProcessId SourceProcess, CefRefPtr<CefProcessMessage> Message);` — Called when a message was received from the renderer process. @param Browser The CefBrowser for this window. @param SourceProcess The process id of the sender of the message. Currently always PID_RENDERER. @param Message The actual message. @return true if the message was handled, else false.
- L81 _public prototype_ `void SendProcessMessage(CefRefPtr<CefProcessMessage> Message);` — Sends a message to the renderer process. See https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage#markdown-header-inter-process-communication-ipc for more information. @param Message the message to send to the renderer process
- L85 _public prototype_ `void BindInputMethodSystem(ITextInputMethodSystem* InTextInputMethodSystem);`
- L86 _public prototype_ `void UnbindInputMethodSystem();`
- L91 _private function_ `bool IsValid()`
- L96 _private prototype_ `void ActivateContext();`
- L97 _private prototype_ `void DeactivateContext();`
- L98 _private prototype_ `void DestroyContext();`
- L101 _private prototype_ `bool HandleFocusChangedMessage(CefRefPtr<CefListValue> MessageArguments);` — Message handling helpers
- L104 _private member_ `CefRefPtr<CefBrowser> InternalCefBrowser;` — Pointer to the CEF Browser for this window.
- L106 _private member_ `TWeakPtr<SWidget> InternalBrowserSlateWidget;`
- L108 _private member_ `ITextInputMethodSystem* TextInputMethodSystem;`
- L111 _private member_ `TSharedPtr<FCEFTextInputMethodContext> TextInputMethodContext;` — IME context for this browser window.  This gets recreated whenever we change focus to an editable input field.
- L114 _private member_ `TSharedPtr<ITextInputMethodChangeNotifier> TextInputMethodChangeNotifier;` — Notification interface object for IMEs
- L117 _private member_ `bool bHasFocus;` — Caches the focus state from Slate.
- L120 _private member_ `bool bContextWasActiveWhenFocusLost;` — Saves the active state of the TextInputMethodContext when the browser loses focus.

### `Source/Runtime/WebBrowser/Private/CEF/CEFJSScripting.h` (Private)


#### class `FCEFJSScripting`  
`class FCEFJSScripting : public FWebJSScripting , public TSharedFromThis<FCEFJSScripting>`  
_L43-159_
- inherits: `FWebJSScripting,TSharedFromThis<FCEFJSScripting>`
- desc: Implements handling of bridging UObjects client side with JavaScript renderer side.
- L48 _public function_ `FCEFJSScripting(CefRefPtr<CefBrowser> Browser, bool bJSBindingToLoweringEnabled) : FWebJSScripting(bJSBindingToLoweringEnabled) , InternalCefBrowser(Browser)`
- L53 _public prototype_ `void UnbindCefBrowser();`
- L55 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L56 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L66 _public prototype_ `bool OnProcessMessageReceived(CefRefPtr<CefBrowser> Browser, CefProcessId SourceProcess, CefRefPtr<CefProcessMessage> Message);` — Called when a message was received from the renderer process. @param Browser The CefBrowser for this window. @param SourceProcess The process id of the sender of the message. Currently always PID_RENDERER. @param Message The actual message. @return true if the message was handled, else false.
- L74 _public prototype_ `void SendProcessMessage(CefRefPtr<CefProcessMessage> Message);` — Sends a message to the renderer process. See https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage#markdown-header-inter-process-communication-ipc for more information. @param Message the message to send to the renderer process
- L76 _public prototype_ `CefRefPtr<CefDictionaryValue> ConvertStruct(UStruct* TypeInfo, const void* StructPtr);`
- L77 _public prototype_ `CefRefPtr<CefDictionaryValue> ConvertObject(UObject* Object);`
- L81 _public function_ `template<typename ContainerType, typename KeyType> bool SetConverted(CefRefPtr<ContainerType> Container, KeyType Key, FWebJSParam& Param)` — Works for CefListValue and CefDictionaryValues
- L138 _public prototype_ `CefRefPtr<CefDictionaryValue> GetPermanentBindings();`
- L140 _public prototype_ `void InvokeJSFunction(FGuid FunctionId, int32 ArgCount, FWebJSParam Arguments[], bool bIsError=false) override;`
- L141 _public prototype_ `void InvokeJSFunction(FGuid FunctionId, const CefRefPtr<CefListValue>& FunctionArguments, bool bIsError=false);`
- L142 _public prototype_ `void InvokeJSErrorResult(FGuid FunctionId, const FString& Error) override;`
- L145 _private prototype_ `bool ConvertStructArgImpl(uint8* Args, FProperty* Param, CefRefPtr<CefListValue> List, int32 Index);`
- L147 _private function_ `bool IsValid()`
- L154 _private prototype_ `bool HandleExecuteUObjectMethodMessage(CefRefPtr<CefListValue> MessageArguments);`
- L155 _private prototype_ `bool HandleReleaseUObjectMessage(CefRefPtr<CefListValue> MessageArguments);`
- L158 _private member_ `CefRefPtr<CefBrowser> InternalCefBrowser;` — Pointer to the CEF Browser for this window.

### `Source/Runtime/WebBrowser/Private/CEF/CEFJSStructDeserializerBackend.h` (Private)


#### class `ICefContainerWalker`  
`class ICefContainerWalker : public TSharedFromThis<ICefContainerWalker>`  
_L45-58_
- inherits: `TSharedFromThis<ICefContainerWalker>`
- L49 _public function_ `ICefContainerWalker(TSharedPtr<ICefContainerWalker> InParent) : Parent(InParent)`
- L52 _public prototype_ `virtual ~ICefContainerWalker() = default;`
- L54 _public prototype_ `virtual TSharedPtr<ICefContainerWalker> GetNextToken( EStructDeserializerBackendTokens& OutToken, FString& PropertyName ) = 0;`
- L55 _public prototype_ `virtual bool ReadProperty(TSharedPtr<FCEFJSScripting> Scripting, FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex) = 0;`
- L57 _public member_ `TSharedPtr<ICefContainerWalker> Parent;`

#### class `FCefListValueWalker`  
`class FCefListValueWalker : public ICefContainerWalker`  
_L60-75_
- inherits: `ICefContainerWalker`
- L64 _public function_ `FCefListValueWalker(TSharedPtr<ICefContainerWalker> InParent, CefRefPtr<CefListValue> InList) : ICefContainerWalker(InParent) , List(InList) , Index(-2)`
- L70 _public prototype_ `virtual TSharedPtr<ICefContainerWalker> GetNextToken( EStructDeserializerBackendTokens& OutToken, FString& PropertyName ) override;`
- L71 _public prototype_ `virtual bool ReadProperty(TSharedPtr<FCEFJSScripting> Scripting, FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) override;`
- L73 _public member_ `CefRefPtr<CefListValue> List;`
- L74 _public member_ `size_t Index;`

#### class `FCefDictionaryValueWalker`  
`class FCefDictionaryValueWalker : public ICefContainerWalker`  
_L77-96_
- inherits: `ICefContainerWalker`
- L81 _public function_ `FCefDictionaryValueWalker(TSharedPtr<ICefContainerWalker> InParent, CefRefPtr<CefDictionaryValue> InDictionary) : ICefContainerWalker(InParent) , Dictionary(InDictionary) , Index(-2)`
- L89 _public prototype_ `virtual TSharedPtr<ICefContainerWalker> GetNextToken( EStructDeserializerBackendTokens& OutToken, FString& PropertyName ) override;`
- L90 _public prototype_ `virtual bool ReadProperty(TSharedPtr<FCEFJSScripting> Scripting, FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) override;`
- L93 _private member_ `CefRefPtr<CefDictionaryValue> Dictionary;`
- L94 _private member_ `size_t Index;`
- L95 _private member_ `CefDictionaryValue::KeyList Keys;`

#### class `FCEFJSStructDeserializerBackend`  
`class FCEFJSStructDeserializerBackend : public IStructDeserializerBackend`  
_L101-134_
- inherits: `IStructDeserializerBackend`
- desc: Implements a writer for UStruct serialization using CefDictionary.
- L111 _public function_ `FCEFJSStructDeserializerBackend(TSharedPtr<FCEFJSScripting> InScripting, CefRefPtr<CefDictionaryValue> InDictionary) : Scripting(InScripting) , Walker(new FCefDictionaryValueWalker(nullptr, InDictionary)) , CurrentPropertyName()` — Creates and initializes a new instance. @param Archive The archive to deserialize from.
- L121 _public prototype_ `virtual const FString& GetCurrentPropertyName() const override;`
- L122 _public prototype_ `virtual FString GetDebugString() const override;`
- L123 _public prototype_ `virtual const FString& GetLastErrorMessage() const override;`
- L124 _public prototype_ `virtual bool GetNextToken( EStructDeserializerBackendTokens& OutToken ) override;`
- L125 _public prototype_ `virtual bool ReadProperty( FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) override;`
- L126 _public prototype_ `virtual void SkipArray() override;`
- L127 _public prototype_ `virtual void SkipStructure() override;`
- L130 _private member_ `TSharedPtr<FCEFJSScripting> Scripting;`
- L132 _private member_ `TSharedPtr<ICefContainerWalker> Walker;` — Holds the source CEF dictionary containing a serialized verion of the structure.
- L133 _private member_ `FString CurrentPropertyName;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFJSStructSerializerBackend.h` (Private)


#### class `FCEFJSStructSerializerBackend`  
`class FCEFJSStructSerializerBackend : public IStructSerializerBackend`  
_L51-114_
- inherits: `IStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using CefDictionary.
- L59 _public function_ `FCEFJSStructSerializerBackend(TSharedPtr<FCEFJSScripting> InScripting) : Scripting(InScripting), Stack(), Result()` — Creates and initializes a new instance.
- L63 _public function_ `CefRefPtr<CefDictionaryValue> GetResult()`
- L72 _public prototype_ `virtual void BeginArray(const FStructSerializerState& State) override;`
- L73 _public prototype_ `virtual void BeginStructure(const FStructSerializerState& State) override;`
- L74 _public prototype_ `virtual void EndArray(const FStructSerializerState& State) override;`
- L75 _public prototype_ `virtual void EndStructure(const FStructSerializerState& State) override;`
- L76 _public prototype_ `virtual void WriteComment(const FString& Comment) override;`
- L77 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override;`
- L104 _private member_ `TSharedPtr<FCEFJSScripting> Scripting;`
- L105 _private member_ `TArray<StackItem> Stack;`
- L106 _private member_ `CefRefPtr<CefDictionaryValue> Result;`
- L108 _private prototype_ `void AddNull(const FStructSerializerState& State);`
- L109 _private prototype_ `void Add(const FStructSerializerState& State, bool Value);`
- L110 _private prototype_ `void Add(const FStructSerializerState& State, int32 Value);`
- L111 _private prototype_ `void Add(const FStructSerializerState& State, double Value);`
- L112 _private prototype_ `void Add(const FStructSerializerState& State, FString Value);`
- L113 _private prototype_ `void Add(const FStructSerializerState& State, UObject* Value);`

#### struct `FCEFJSStructSerializerBackend::StackItem`  
`struct StackItem`  
_L81-102_
- L83 _public member_ `enum {STYPE_DICTIONARY, STYPE_LIST} Kind;`
- L84 _public member_ `FString Name;`
- L85 _public member_ `CefRefPtr<CefDictionaryValue> DictionaryValue;`
- L86 _public member_ `CefRefPtr<CefListValue> ListValue;`
- L88 _public function_ `StackItem(const FString& InName, CefRefPtr<CefDictionaryValue> InDictionary) : Kind(STYPE_DICTIONARY) , Name(InName) , DictionaryValue(InDictionary) , ListValue()`
- L95 _public function_ `StackItem(const FString& InName, CefRefPtr<CefListValue> InList) : Kind(STYPE_LIST) , Name(InName) , DictionaryValue() , ListValue(InList)`

#### enum `FCEFJSStructSerializerBackend::StackItem::(anonymous)`  
`enum`  
_L83-83_

#### Free symbols / members of external scopes

- L83 _enumerator_ `enum {STYPE_DICTIONARY, STYPE_LIST} Kind; FString Name; CefRefPtr<CefDictionaryValue> DictionaryValue; CefRefPtr<CefListValue> ListValue; StackItem(const FString& InName, CefRefPtr<CefDictionaryValue> InDictionary) : Kind(STYPE_DICTIONARY)` (scope `FCEFJSStructSerializerBackend::StackItem::__anon1a76d6c90103`)
- L83 _enumerator_ `enum {STYPE_DICTIONARY, STYPE_LIST} Kind; FString Name; CefRefPtr<CefDictionaryValue> DictionaryValue; CefRefPtr<CefListValue> ListValue; StackItem(const FString& InName, CefRefPtr<CefDictionaryValue> InDictionary) : Kind(STYPE_DICTIONARY)` (scope `FCEFJSStructSerializerBackend::StackItem::__anon1a76d6c90103`)

### `Source/Runtime/WebBrowser/Private/CEF/CEFLibCefIncludes.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `# define OVERRIDE override`

### `Source/Runtime/WebBrowser/Private/CEF/CEFResourceContextHandler.h` (Private)


#### class `FCEFResourceContextHandler`  
`class FCEFResourceContextHandler : public CefRequestContextHandler , public CefResourceRequestHandler`  
_L21-54_
- inherits: `CefRequestContextHandler,CefResourceRequestHandler`
- desc: Implements CEF Request handling for when a browser window is still being constructed
- L28 _public prototype_ `FCEFResourceContextHandler(FWebBrowserSingleton *InOwningSingleton);` — Default constructor.
- L33 _public prototype_ `virtual CefResourceRequestHandler::ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, CefRefPtr<CefCallback> Callback) override;` — CefResourceRequestHandler Interface
- L36 _public prototype_ `virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling) override;` — CefRequestContextHandler Interface
- L40 _public function_ `FOnBeforeContextResourceLoadDelegate& OnBeforeLoad()`
- L47 _private member_ `FOnBeforeContextResourceLoadDelegate BeforeResourceLoadDelegate;` — Delegate for handling resource load requests
- L50 _private member_ `FWebBrowserSingleton* OwningSingleton;` — Singleton that owns this context handler, so we can lookup browser objects from it
- L53 _private prototype_ `IMPLEMENT_REFCOUNTING(FCEFResourceContextHandler);` — Include the default reference counting implementation.

#### Free symbols / members of external scopes

- L14 _prototype_ `FString ResourceTypeToString(const CefRequest::ResourceType& Type);`

### `Source/Runtime/WebBrowser/Private/CEF/CEFSchemeHandler.h` (Private)


#### class `FCefSchemeHandlerFactories`  
`class FCefSchemeHandlerFactories`  
_L14-53_
- desc: Implementation for managing CEF custom scheme handlers.
- L24 _public prototype_ `void AddSchemeHandlerFactory(FString Scheme, FString Domain, IWebBrowserSchemeHandlerFactory* WebBrowserSchemeHandlerFactory);` — Adds a custom scheme handler factory, for a given scheme and domain. The domain is ignored if the scheme is not a browser built in scheme, and all requests will go through this factory. @param Scheme                            The scheme name to handle. @param Domain                            The domain name to handle on the scheme. Ignored if scheme is not a built in scheme. @param WebBrowserSchemeHandlerFactory    The factory implementation for creating request handlers for this scheme.
- L30 _public prototype_ `void RemoveSchemeHandlerFactory(IWebBrowserSchemeHandlerFactory* WebBrowserSchemeHandlerFactory);` — Remove a custom scheme handler factory. The factory may still be used by existing open browser windows, but will no longer be provided for new ones. @param WebBrowserSchemeHandlerFactory    The factory implementation to remove.
- L36 _public prototype_ `void RegisterFactoriesWith(CefRefPtr<CefRequestContext>& Context);` — Register all scheme handler factories with the provided request context. @param Context   The context.
- L52 _private member_ `TArray<FFactory> SchemeHandlerFactories;` — Array of registered handler factories.

#### struct `FCefSchemeHandlerFactories::FFactory`  
`struct FFactory`  
_L42-49_
- desc: A struct to wrap storage of a factory with it's provided scheme and domain, inc ref counting for the cef representation.
- L45 _public prototype_ `FFactory(FString Scheme, FString Domain, CefRefPtr<CefSchemeHandlerFactory> Factory);`
- L46 _public member_ `FString Scheme;`
- L47 _public member_ `FString Domain;`
- L48 _public member_ `CefRefPtr<CefSchemeHandlerFactory> Factory;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFTextInputMethodContext.h` (Private)


#### class `FCEFTextInputMethodContext`  
`class FCEFTextInputMethodContext : public ITextInputMethodContext`  
_L42-98_
- inherits: `ITextInputMethodContext`
- L46 _public prototype_ `virtual ~FCEFTextInputMethodContext() = default;`
- L48 _public prototype_ `static TSharedRef<FCEFTextInputMethodContext> Create(const TSharedRef<FCEFImeHandler>& InOwner);`
- L50 _public prototype_ `void AbortComposition();`
- L52 _public prototype_ `bool UpdateCachedGeometry(const FGeometry& AllottedGeometry);`
- L53 _public prototype_ `bool UpdateCachedSlateWindow();`
- L55 _public prototype_ `bool CEFCompositionRangeChanged(const CefRange& SelectionRange, const CefRenderHandler::RectList& CharacterBounds);`
- L56 _public prototype_ `bool CEFTextSelectionChanged(const CefString& SelectedText, const CefRange& SelectionRange);`
- L59 _private prototype_ `void ResetComposition();`
- L64 _public prototype_ `virtual bool IsComposing() override;` — ITextInputMethodContext Interface
- L67 _private prototype_ `virtual bool IsReadOnly() override;`
- L68 _private prototype_ `virtual uint32 GetTextLength() override;`
- L69 _private prototype_ `virtual void GetSelectionRange(uint32& BeginIndex, uint32& Length, ECaretPosition& CaretPosition) override;`
- L70 _private prototype_ `virtual void SetSelectionRange(const uint32 BeginIndex, const uint32 Length, const ECaretPosition CaretPosition) override;`
- L71 _private prototype_ `virtual void GetTextInRange(const uint32 BeginIndex, const uint32 Length, FString& OutString) override;`
- L72 _private prototype_ `virtual void SetTextInRange(const uint32 BeginIndex, const uint32 Length, const FString& InString) override;`
- L73 _private prototype_ `virtual int32 GetCharacterIndexFromPoint(const FVector2D& Point) override;`
- L74 _private prototype_ `virtual bool GetTextBounds(const uint32 BeginIndex, const uint32 Length, FVector2D& Position, FVector2D& Size) override;`
- L75 _private prototype_ `virtual void GetScreenBounds(FVector2D& Position, FVector2D& Size) override;`
- L76 _private prototype_ `virtual TSharedPtr<FGenericWindow> GetWindow() override;`
- L77 _private prototype_ `virtual void BeginComposition() override;`
- L78 _private prototype_ `virtual void UpdateCompositionRange(const int32 InBeginIndex, const uint32 InLength) override;`
- L79 _private prototype_ `virtual void EndComposition() override;`
- L82 _private prototype_ `FCEFTextInputMethodContext(const TSharedRef<FCEFImeHandler>& InOwner);`
- L83 _private member_ `TSharedRef<FCEFImeHandler> Owner;`
- L84 _private member_ `TWeakPtr<SWindow> CachedSlateWindow;`
- L86 _private member_ `FGeometry CachedGeometry;`
- L87 _private member_ `bool bIsComposing;`
- L88 _private member_ `int32 CompositionBeginIndex;`
- L90 _private member_ `uint32 SelectionRangeBeginIndex;`
- L91 _private member_ `uint32 SelectionRangeLength;`
- L92 _private member_ `ECaretPosition SelectionCaretPosition;`
- L94 _private member_ `std::vector<CefRect> CefCompositionBounds;`
- L96 _private member_ `FString CompositionSequence;`
- L97 _private member_ `FString CompositionString;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFWebBrowserDialog.h` (Private)


#### class `FCEFWebBrowserDialog`  
`class FCEFWebBrowserDialog : public IWebBrowserDialog`  
_L34-98_
- inherits: `IWebBrowserDialog`
- L38 _public prototype_ `virtual ~FCEFWebBrowserDialog() = default;`
- L42 _public function_ `virtual EWebBrowserDialogType GetType() override`
- L47 _public function_ `virtual const FText& GetMessageText() override`
- L52 _public function_ `virtual const FText& GetDefaultPrompt() override`
- L57 _public function_ `virtual bool IsReload() override`
- L63 _public function_ `virtual void Continue(bool Success = true, const FText& UserResponse = FText::GetEmpty()) override`
- L72 _private member_ `EWebBrowserDialogType Type;`
- L73 _private member_ `FText MessageText;`
- L74 _private member_ `FText DefaultPrompt;`
- L75 _private member_ `bool bIsReload;`
- L77 _private member_ `CefRefPtr<CefJSDialogCallback> Callback;`
- L80 _private function_ `FCEFWebBrowserDialog(CefJSDialogHandler::JSDialogType InDialogType, const CefString& InMessageText, const CefString& InDefaultPrompt, CefRefPtr<CefJSDialogCallback> InCallback) : Type((EWebBrowserDialogType)InDialogType) , MessageText(FText::FromString(WCHAR_TO_TCHAR(InMessageText.ToWString().c_str()))) , DefaultPrompt(FText::FromString(WCHAR_TO_TCHAR(InDefaultPrompt.ToWString().c_str()))) , bIsReload(false) , Callback(InCallback)` — Create a dialog from OnJSDialog arguments
- L89 _private function_ `FCEFWebBrowserDialog(const CefString& InMessageText, bool InIsReload, CefRefPtr<CefJSDialogCallback> InCallback) : Type(EWebBrowserDialogType::Unload) , MessageText(FText::FromString(WCHAR_TO_TCHAR(InMessageText.ToWString().c_str()))) , DefaultPrompt(FText::GetEmpty()) , bIsReload(InIsReload) , Callback(InCallback)` — Create a dialog from OnBeforeUnloadDialog arguments

#### Free symbols / members of external scopes

- L100 _typedef_ `typedef FCEFWebBrowserDialog FWebBrowserDialog;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFWebBrowserWindow.h` (Private)


#### struct `FWebBrowserWindowInfo`  
`struct FWebBrowserWindowInfo`  
_L46-54_
- desc: Helper for containing items required for CEF browser window creation.
- L48 _public function_ `FWebBrowserWindowInfo(CefRefPtr<CefBrowser> InBrowser, CefRefPtr<FCEFBrowserHandler> InHandler) : Browser(InBrowser) , Handler(InHandler)`
- L52 _public member_ `CefRefPtr<CefBrowser> Browser;`
- L53 _public member_ `CefRefPtr<FCEFBrowserHandler> Handler;`

#### struct `FWebBrowserDragRegion`  
`struct FWebBrowserDragRegion`  
_L59-68_
- desc: Representation of a window drag region.
- L61 _public function_ `FWebBrowserDragRegion(const FIntRect& InRect, bool bInDraggable) : Rect(InRect) , bDraggable(bInDraggable)`
- L66 _public member_ `FIntRect Rect;`
- L67 _public member_ `bool bDraggable;`

#### class `FCEFWebBrowserWindow`  
`class FCEFWebBrowserWindow : public IWebBrowserWindow , public TSharedFromThis<FCEFWebBrowserWindow>`  
_L73-841_
- inherits: `IWebBrowserWindow,TSharedFromThis<FCEFWebBrowserWindow>`
- desc: Implementation of interface for dealing with a Web Browser window.
- L100 _private prototype_ `FCEFWebBrowserWindow(CefRefPtr<CefBrowser> Browser, CefRefPtr<FCEFBrowserHandler> Handler, FString Url, TOptional<FString> ContentsToLoad, FString UserAgentProduct, bool bShowErrorMessage, bool bThumbMouseButtonNavigation, bool bUseTransparency, bool bJSBindingToLoweringEnabled, bool bUsingAcceleratedPaint);` — Creates and initializes a new instance. @param Browser The CefBrowser object representing this browser window. @param Handler Pointer to the CEF handler for this window. @param Url The Initial URL that will be loaded. @param ContentsToLoad Optional string to load as a web page. @param UserAgentProduct the product part of the user agent string for HTTP requests sent by this window. @param bShowErrorMessage Whether to show an error message in case of loading errors. @param bThumbMouseButtonNavigation Whether to allow forward and back navigation via the mouse thumb buttons. @param bUseTransparency Whether to enable transparency. @param bJSBindingToLoweringEnabled Whether we ToLower all JavaScript member names.
- L105 _private prototype_ `TSharedRef<SViewport> CreateWidget();` — Create the SWidget for this WebBrowserWindow
- L109 _public prototype_ `virtual ~FCEFWebBrowserWindow();` — Virtual Destructor.
- L111 _public function_ `bool IsShowingErrorMessages() const`
- L112 _public function_ `bool IsThumbMouseButtonNavigationEnabled() const`
- L113 _public function_ `bool UseTransparency() const`
- L114 _public function_ `bool UsingAcceleratedPaint() const`
- L115 _public function_ `FString GetUserAgentProduct() const`
- L121 _public prototype_ `virtual void LoadURL(FString NewURL) override;`
- L122 _public prototype_ `virtual void LoadString(FString Contents, FString DummyURL) override;`
- L123 _public prototype_ `virtual void SetViewportSize(FIntPoint WindowSize, FIntPoint WindowPos) override;`
- L124 _public function_ `virtual FIntPoint GetViewportSize() const override`
- L125 _public prototype_ `virtual FSlateShaderResource* GetTexture(bool bIsPopup = false) override;`
- L126 _public prototype_ `virtual bool IsValid() const override;`
- L127 _public prototype_ `virtual bool IsInitialized() const override;`
- L128 _public prototype_ `virtual bool IsClosing() const override;`
- L129 _public prototype_ `virtual EWebBrowserDocumentState GetDocumentLoadingState() const override;`
- L130 _public prototype_ `virtual FString GetTitle() const override;`
- L131 _public prototype_ `virtual FString GetUrl() const override;`
- L132 _public prototype_ `virtual void GetSource(TFunction<void (const FString&)> Callback) const override;`
- L133 _public prototype_ `virtual bool OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L134 _public prototype_ `virtual bool OnKeyUp(const FKeyEvent& InKeyEvent) override;`
- L135 _public prototype_ `virtual bool OnKeyChar(const FCharacterEvent& InCharacterEvent) override;`
- L136 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L137 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L138 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L139 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L140 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L141 _public prototype_ `virtual void SetSupportsMouseWheel(bool bValue) override;`
- L142 _public prototype_ `virtual bool GetSupportsMouseWheel() const override;`
- L143 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L144 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent, bool bIsPopup) override;`
- L145 _public prototype_ `virtual void OnFocus(bool SetFocus, bool bIsPopup) override;`
- L146 _public prototype_ `virtual void OnCaptureLost() override;`
- L147 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L148 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L149 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L150 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L152 _public prototype_ `virtual bool CanGoBack() const override;`
- L153 _public prototype_ `virtual void GoBack() override;`
- L154 _public prototype_ `virtual bool CanGoForward() const override;`
- L155 _public prototype_ `virtual void GoForward() override;`
- L156 _public prototype_ `virtual bool IsLoading() const override;`
- L157 _public prototype_ `virtual void Reload() override;`
- L158 _public prototype_ `virtual void StopLoad() override;`
- L159 _public prototype_ `virtual void ExecuteJavascript(const FString& Script) override;`
- L160 _public prototype_ `virtual void CloseBrowser(bool bForce, bool bBlockTillClosed) override;`
- L161 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L162 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L163 _public prototype_ `virtual void BindInputMethodSystem(ITextInputMethodSystem* TextInputMethodSystem) override;`
- L164 _public prototype_ `virtual void UnbindInputMethodSystem() override;`
- L165 _public prototype_ `virtual int GetLoadError() override;`
- L166 _public prototype_ `virtual void SetIsDisabled(bool bValue) override;`
- L167 _public prototype_ `virtual TSharedPtr<SWindow> GetParentWindow() const override;`
- L168 _public prototype_ `virtual void SetParentWindow(TSharedPtr<SWindow> Window) override;`
- L169 _public function_ `virtual void ShowFloatingCloseButton(bool bShow, bool bDraggable) override`
- L173 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);`
- L174 _public function_ `virtual FOnDocumentStateChanged& OnDocumentStateChanged() override`
- L179 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L180 _public function_ `virtual FOnTitleChanged& OnTitleChanged() override`
- L185 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L186 _public function_ `virtual FOnUrlChanged& OnUrlChanged() override`
- L191 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L192 _public function_ `virtual FOnToolTip& OnToolTip() override`
- L197 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L198 _public function_ `virtual FOnNeedsRedraw& OnNeedsRedraw() override`
- L203 _public function_ `virtual FOnBeforeBrowse& OnBeforeBrowse() override`
- L208 _public function_ `virtual FOnLoadUrl& OnLoadUrl() override`
- L213 _public function_ `virtual FOnCreateWindow& OnCreateWindow() override`
- L218 _public function_ `virtual FOnCloseWindow& OnCloseWindow() override`
- L223 _public function_ `virtual FOnFloatingCloseButtonPressed& OnFloatingCloseButtonPressed() override`
- L228 _public function_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) override`
- L233 _public function_ `virtual FOnBeforePopupDelegate& OnBeforePopup() override`
- L238 _public function_ `virtual FOnBeforeResourceLoadDelegate& OnBeforeResourceLoad() override`
- L248 _public function_ `virtual FOnResourceLoadCompleteDelegate& OnResourceLoadComplete() override`
- L258 _public function_ `virtual FOnConsoleMessageDelegate& OnConsoleMessage() override`
- L268 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L269 _public function_ `virtual FOnShowPopup& OnShowPopup() override`
- L274 _public prototype_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`
- L275 _public function_ `virtual FOnDismissPopup& OnDismissPopup() override`
- L280 _public function_ `virtual FOnShowDialog& OnShowDialog() override`
- L285 _public function_ `virtual FOnDismissAllDialogs& OnDismissAllDialogs() override`
- L290 _public function_ `virtual FOnSuppressContextMenu& OnSuppressContextMenu() override`
- L295 _public function_ `virtual FOnDragWindow& OnDragWindow() override`
- L300 _public function_ `virtual FOnUnhandledKeyDown& OnUnhandledKeyDown() override`
- L305 _public function_ `virtual FOnUnhandledKeyUp& OnUnhandledKeyUp() override`
- L310 _public function_ `virtual FOnUnhandledKeyChar& OnUnhandledKeyChar() override`
- L322 _private prototype_ `CefRefPtr<CefBrowser> GetCefBrowser();` — Used to obtain the internal CEF browser. @return The bound CEF browser.
- L329 _private prototype_ `void SetTitle(const CefString& InTitle);` — Sets the Title of this window. @param InTitle The new title of this window.
- L336 _private prototype_ `void SetUrl(const CefString& InUrl);` — Sets the url of this window. @param InUrl The new url of this window.
- L343 _private prototype_ `void SetToolTip(const CefString& InToolTip);` — Sets the tool tip for this window. @param InToolTip The text to show in the ToolTip. Empty string for no tool tip.
- L351 _private prototype_ `void GetViewRect(CefRect& Rect);` — Get the current proportions of this window. @param Rect Reference to CefRect to store sizes. @return Whether Rect was set up correctly.
- L354 _private prototype_ `void NotifyDocumentError(CefLoadHandler::ErrorCode InErrorCode, const CefString& ErrorText, const CefString& FailedUrl);` — Notifies when document loading has failed.
- L357 _private prototype_ `void NotifyDocumentError(int ErrorCode);` — Notifies clients that document loading has failed.
- L364 _private prototype_ `void NotifyDocumentLoadingStateChange(bool IsLoading);` — Notifies clients that the loading state of the document has changed. @param IsLoading Whether the document is loading (false = completed).
- L375 _private prototype_ `void OnPaint(CefRenderHandler::PaintElementType Type, const CefRenderHandler::RectList& DirtyRects, const void* Buffer, int Width, int Height);` — Called when there is an update to the rendered web page. @param Type Paint type. @param DirtyRects List of image areas that have been changed. @param Buffer Pointer to the raw texture data. @param Width Width of the texture. @param Height Height of the texture.
- L384 _private prototype_ `void OnAcceleratedPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList& DirtyRects, const CefAcceleratedPaintInfo& Info);` — Called when there is an update to the rendered web page. @param Type Paint type. @param DirtyRects List of image areas that have been changed. @param SharedHandle the handle for a D3D11 Texture2D that can be accessed via ID3D11Device using the OpenSharedResource method
- L391 _private prototype_ `bool OnCursorChange(CefCursorHandle Cursor, cef_cursor_type_t Type, const CefCursorInfo& CustomCursorInfo);` — Called when cursor would change due to web browser interaction. @param Cursor Handle to CEF mouse cursor.
- L401 _private prototype_ `bool OnProcessMessageReceived(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> frame, CefProcessId SourceProcess, CefRefPtr<CefProcessMessage> Message);` — Called when a message was received from the renderer process. @param Browser The CefBrowser for this window. @param SourceProcess The process id of the sender of the message. Currently always PID_RENDERER. @param Message The actual message. @return true if the message was handled, else false.
- L413 _private prototype_ `bool OnBeforeBrowse(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefRequest> Request, bool user_gesture, bool bIsRedirect);` — Called before browser navigation. @param Browser The CefBrowser for this window. @param Frame The CefFrame the request came from. @param Request The CefRequest containing web request info. @param user_gesture true if the navigation was a result of a gesture, false otherwise. @param bIsRedirect true if the navigation was a result of redirection, false otherwise. @return true if the navigation was handled and no further processing of the navigation request should be disabled, false if the navigation should be handled by the default CEF implementation.
- L415 _private prototype_ `void HandleOnBeforeResourceLoad(const CefString& URL, CefRequest::ResourceType Type, FRequestHeaders& AdditionalHeaders, const bool AllowUserCredentials);`
- L416 _private prototype_ `void HandleOnResourceLoadComplete(const CefString& URL, CefRequest::ResourceType Type, CefResourceRequestHandler::URLRequestStatus Status, int64 ContentLength);`
- L417 _private prototype_ `void HandleOnConsoleMessage(CefRefPtr<CefBrowser> Browser, cef_log_severity_t Level, const CefString& Message, const CefString& Source, int32 Line);`
- L424 _private prototype_ `TOptional<FString> GetResourceContent(CefRefPtr< CefFrame > Frame, CefRefPtr< CefRequest > Request);` — Called before loading a resource to allow overriding the content for a request. @return string content representing the content to show for the URL or an unset value to fetch the URL normally.
- L429 _private prototype_ `FModifierKeysState SlateModifiersFromCefModifiers(const CefKeyEvent& CefEvent);` — Convenience function to translate modifier keys from Cef keyboard event
- L434 _private prototype_ `bool OnUnhandledKeyEvent(const CefKeyEvent& CefEvent);` — Called when browser reports a key event that was not handled by it
- L439 _private prototype_ `bool OnJSDialog(CefJSDialogHandler::JSDialogType DialogType, const CefString& MessageText, const CefString& DefaultPromptText, CefRefPtr<CefJSDialogCallback> Callback, bool& OutSuppressMessage);` — Handle showing javascript dialogs
- L444 _private prototype_ `bool OnFileDialog(CefDialogHandler::FileDialogMode Mode, const CefString& DialogTitle, const CefString& DefaultFilePath, const std::vector<CefString>& AcceptFilters, const std::vector<CefString>& AcceptExtensions, const std::vector<CefString>& AcceptDescriptions, CefRefPtr<CefFileDialogCallback> Callback);` — Handle showing the file select / upload dialogs
- L449 _private prototype_ `bool OnBeforeUnloadDialog(const CefString& MessageText, bool IsReload, CefRefPtr<CefJSDialogCallback> Callback);` — Handle showing unload confirmation dialogs
- L454 _private prototype_ `void OnResetDialogState();` — Notify when any and all pending dialogs should be canceled
- L459 _private prototype_ `void OnRenderProcessTerminated(CefRequestHandler::TerminationStatus Status);` — Called when render process was terminated abnormally.
- L468 _private prototype_ `bool RequestCreateWindow(const TSharedRef<IWebBrowserWindow>& NewBrowserWindow, const TSharedPtr<IWebBrowserPopupFeatures>& BrowserPopupFeatures);` — Called when the browser requests a new UI window @param NewBrowserWindow The web browser window to display in the new UI window. @param BrowserPopupFeatures The popup features and settings for the browser window. @return true if the UI window was created, false otherwise.
- L477 _private prototype_ `void OnBrowserClosing();` — Called once the browser begins closing procedures.
- L482 _private prototype_ `void OnBrowserClosed();` — Called once the browser is closed.
- L490 _private prototype_ `void SetPopupMenuPosition(CefRect PopupSize);` — Called to set the popup menu position and size. For the accelerated paint path, the size is used to pre-create the popup texture at the correct dimensions. @param PopupSize The location and size of the popup widget.
- L497 _private prototype_ `void ShowPopupMenu(bool bShow);` — Called to request that the popup widget is shown or hidden. @param bShow true for showing the popup, false for hiding it.
- L505 _private prototype_ `void OnImeCompositionRangeChanged( CefRefPtr<CefBrowser> Browser, const CefRange& SelectionRange, const CefRenderHandler::RectList& CharacterBounds);` — Called when the IME composition DOM node has changed. @param Browser The CefBrowser for this window. @param SelectionRange The range of characters that have been selected. @param CharacterBounds The bounds of each character in view coordinates.
- L516 _private prototype_ `void OnTextSelectionChanged( CefRefPtr<CefBrowser> Browser, const CefString& SelectedText, const CefRange& SelectionRange);` — Called when the text selection has changed for a text field in a web page, used for IME. @param Browser The CefBrowser for this window. @param SelectedText The selected text. @param SelectionRange The range of characters that have been selected.
- L521 _private prototype_ `void UpdateDragRegions(const TArray<FWebBrowserDragRegion>& Regions);`
- L531 _public prototype_ `static int32 GetCefKeyboardModifiers(const FKeyEvent& KeyEvent);` — Gets the Cef Keyboard Modifiers based on a Key Event. @param KeyEvent The Key event. @return Bits representing keyboard modifiers.
- L539 _public prototype_ `static int32 GetCefMouseModifiers(const FPointerEvent& InMouseEvent);` — Gets the Cef Mouse Modifiers based on a Mouse Event. @param InMouseEvent The Mouse event. @return Bits representing mouse modifiers.
- L547 _public prototype_ `static int32 GetCefInputModifiers(const FInputEvent& InputEvent);` — Gets the Cef Input Modifiers based on an Input Event. @param InputEvent The Input event. @return Bits representing input modifiers.
- L555 _public prototype_ `static bool CanSupportAcceleratedPaint();` — Is this platform able to support the accelerated paint path for CEF. @return true if supported AND enabled on this platform, false otherwise.
- L561 _public prototype_ `void UpdateCachedGeometry(const FGeometry& AllottedGeometry);` — Called from the WebBrowserViewport tick event. Allows us to cache the geometry and use it for coordinate transformations.
- L566 _public prototype_ `void CheckTickActivity() override;` — Called from the WebBrowserSingleton tick event. Should test wether the widget got a tick from Slate last frame and set the state to hidden if not.
- L571 _public prototype_ `void UpdateVideoBuffering();` — Called from the engine tick.
- L577 _public prototype_ `CefRefPtr<CefDictionaryValue> GetProcessInfo();` — Called on every browser window when CEF launches a new render process. Used to ensure global JS objects are registered as soon as possible.
- L582 _public function_ `bool URLRequestAllowsCredentials(const FString& URL) const` — Return true if this URL will support adding an Authorization header to it
- L588 _public prototype_ `void SetCaptureCefFrames(const bool bValue);` — Whether we should use a workaround for this bug - https://github.com/chromiumembedded/cef/issues/3826
- L593 _public prototype_ `bool HasResizeBug() const;` — Whether the CEF version we're using has a resize bug that sometimes requires requesting new frames after a resize.
- L598 _public prototype_ `bool IsCefResizeNeeded() const;` — Indicates a CEF resize is needed, using heuristics to avoid too many resize requests during an active drag-resize.
- L603 _public prototype_ `void RequestCefResize();` — Requests a resize of the CEF webview to ViewportSize
- L608 _private prototype_ `FSlateRenderer* const GetRenderer();` — @return the currently valid renderer, if available
- L611 _private prototype_ `void HandleRenderingError();` — Checks whether an error with the renderer occurred and handles it if one has
- L614 _private prototype_ `void ReleaseTextures();` — Releases the updatable textures
- L617 _private prototype_ `bool CreateInitialTextures();` — Creates the initial updatable textures
- L620 _private prototype_ `void RequestNavigationInternal(FString Url, FString Contents);` — Executes or defers a LoadUrl navigation
- L623 _private prototype_ `bool HasPendingNavigation();` — Specifies whether or not we have a pending deferred navigation
- L626 _private prototype_ `void ProcessPendingNavigation();` — Executes navigation on a pending deferred navigation
- L629 _private prototype_ `void SetIsHidden(bool bValue);` — Helper that calls WasHidden on the CEF host object when the value changes
- L632 _private prototype_ `void PopulateCefKeyEvent(const FKeyEvent& InKeyEvent, CefKeyEvent& OutKeyEvent);` — Used by the key down and up handlers to convert Slate key events to the CEF equivalent.
- L635 _private prototype_ `CefMouseEvent GetCefMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup);` — Used to convert a FPointerEvent to a CefMouseEvent
- L638 _private prototype_ `bool IsInDragRegion(const FIntPoint& Point);` — Specifies whether or not a point falls within any tagged drag regions that are draggable.
- L640 _private prototype_ `bool BlockInputInDirectHwndMode() const;`
- L644 _private prototype_ `bool LoadCustomCEF3Cursor(cef_cursor_type_t Type);` — manually load cursor icons from the CEF3 dll if needed, working around a CEF3 bug
- L649 _private member_ `EWebBrowserDocumentState DocumentState;` — Current state of the document being loaded.
- L652 _private member_ `FSlateUpdatableTexture* UpdatableTextures[2];` — Interface to the texture we are rendering to.
- L655 _private member_ `CefRefPtr<CefBrowser> InternalCefBrowser;` — Pointer to the CEF Browser for this window.
- L658 _private member_ `CefRefPtr<FCEFBrowserHandler> WebBrowserHandler;` — Pointer to the CEF handler for this window.
- L661 _private member_ `FString Title;` — Current title of this window.
- L664 _private member_ `FString CurrentUrl;` — Current Url of this window.
- L667 _private member_ `FString ToolTipText;` — Current tool tip.
- L670 _private member_ `FString UserAgentProduct;` — The product part for the user agent string of this window.
- L673 _private member_ `FIntPoint ViewportSize;` — Current size of this window.
- L676 _private member_ `FIntPoint ViewportPos;` — Current position of this window.
- L679 _private member_ `float ViewportDPIScaleFactor;` — Current DPI scale factor of this window (from the OS).
- L682 _private member_ `float ViewportScaleFactor;` — Current scale factor of this window (from the game viewport).
- L685 _private member_ `bool bIsClosing;` — Whether this window is closing.
- L688 _private member_ `bool bIsInitialized;` — Whether this window has been painted at least once.
- L691 _private member_ `TOptional<FString> ContentsToLoad;` — Optional text to load as a web page.
- L694 _private member_ `FOnDocumentStateChanged DocumentStateChangedEvent;` — Delegate for broadcasting load state changes.
- L697 _private member_ `bool bShowErrorMessage;` — Whether to show an error message in case of loading errors.
- L700 _private member_ `bool bThumbMouseButtonNavigation;` — Whether to allow forward and back navigation via the mouse thumb buttons.
- L703 _private member_ `bool bUseTransparency;` — Whether transparency is enabled.
- L706 _private member_ `bool bUsingAcceleratedPaint;` — Whether the accelerated paint path is enabled (i.e shared texture handles)
- L709 _private member_ `FOnTitleChanged TitleChangedEvent;` — Delegate for broadcasting title changes.
- L712 _private member_ `FOnUrlChanged UrlChangedEvent;` — Delegate for broadcasting address changes.
- L715 _private member_ `FOnToolTip ToolTipEvent;` — Delegate for showing or hiding tool tips.
- L718 _private member_ `FOnNeedsRedraw NeedsRedrawEvent;` — Delegate for notifying that the window needs refreshing.
- L721 _private member_ `FOnBeforeBrowse BeforeBrowseDelegate;` — Delegate that is executed prior to browser navigation.
- L724 _private member_ `FOnLoadUrl LoadUrlDelegate;` — Delegate for overriding Url contents.
- L727 _private member_ `FOnCloseWindow CloseWindowDelegate;` — Delegate for handling requests to close new windows that were created.
- L730 _private member_ `FOnFloatingCloseButtonPressed FloatingCloseButtonPressedDelegate;` — Delegate for handling requests to close from the webview floating close button.
- L733 _private member_ `FOnBeforeResourceLoadDelegate BeforeResourceLoadDelegate;` — Delegate for handling resource load requests
- L736 _private member_ `FOnResourceLoadCompleteDelegate ResourceLoadCompleteDelegate;` — Delegate that allows for responses to resource loads
- L739 _private member_ `FOnConsoleMessageDelegate ConsoleMessageDelegate;` — Delegate that allows for response to console logs.  Typically used to capture and mirror web logs in client application logs.
- L742 _private member_ `FOnShowPopup ShowPopupEvent;` — Delegate for handling requests to show the popup menu.
- L745 _private member_ `FOnDismissPopup DismissPopupEvent;` — Delegate for handling requests to dismiss the current popup menu.
- L748 _private member_ `FOnShowDialog ShowDialogDelegate;` — Delegate for showing dialogs.
- L751 _private member_ `FOnDismissAllDialogs DismissAllDialogsDelegate;` — Delegate for dismissing all dialogs.
- L754 _private member_ `FOnSuppressContextMenu SuppressContextMenuDelgate;` — Delegate for suppressing context menu
- L757 _private member_ `FOnDragWindow DragWindowDelegate;` — Delegate that is executed when a drag event is detected in an area of the web page tagged as a drag region.
- L760 _private member_ `FOnUnhandledKeyDown UnhandledKeyDownDelegate;` — Delegate for handling key down events not handled by the browser.
- L763 _private member_ `FOnUnhandledKeyUp UnhandledKeyUpDelegate;` — Delegate for handling key up events not handled by the browser.
- L766 _private member_ `FOnUnhandledKeyChar UnhandledKeyCharDelegate;` — Delegate for handling key char events not handled by the browser.
- L769 _private member_ `EMouseCursor::Type Cursor;` — Tracks the current mouse cursor
- L772 _private member_ `bool bIsDisabled;` — Tracks whether the widget is currently disabled or not
- L775 _private member_ `bool bIsHidden;` — Tracks whether the widget is currently hidden or not
- L778 _private member_ `bool bTickedLastFrame;` — Used to detect when the widget is hidden
- L781 _private member_ `bool bDraggingWindow;` — Tracks whether or not the user initiated a window drag by clicking on a page's drag region.
- L784 _private member_ `TOptional<FKeyEvent> PreviousKeyDownEvent;` — Used for unhandled key events forwarding
- L785 _private member_ `TOptional<FKeyEvent> PreviousKeyUpEvent;`
- L786 _private member_ `TOptional<FCharacterEvent> PreviousCharacterEvent;`
- L787 _private member_ `bool bIgnoreKeyDownEvent;`
- L788 _private member_ `bool bIgnoreKeyUpEvent;`
- L789 _private member_ `bool bIgnoreCharacterEvent;`
- L792 _private member_ `bool bMainHasFocus;` — Used to ignore any popup menus when forwarding focus gained/lost events
- L793 _private member_ `bool bPopupHasFocus;`
- L795 _private member_ `bool bSupportsMouseWheel;`
- L797 _private member_ `FIntRect PopupRect;`
- L798 _private member_ `bool bShowPopupRequested;`
- L801 _private member_ `bool bRecoverFromRenderProcessCrash;` — This is set to true when reloading after render process crash.
- L803 _private member_ `int ErrorCode;`
- L806 _private member_ `bool bDeferNavigations;` — Used to defer navigations
- L809 _private member_ `FString PendingAbortUrl;` — Used to identify a navigation that needs to fully abort before we can stop deferring navigations.
- L812 _private member_ `FString PendingLoadUrl;` — Used to store the url of pending navigation requests while we need to defer navigations.
- L814 _private member_ `TUniquePtr<FBrowserBufferedVideo> BufferedVideo;`
- L816 _private member_ `void *LastPaintedSharedHandle;`
- L820 _private member_ `TSharedPtr<FCEFJSScripting> Scripting;` — Handling of passing and marshalling messages for JS integration is delegated to a helper class
- L824 _private member_ `TSharedPtr<FCEFImeHandler> Ime;` — Handling of foreign language character input is delegated to a helper class
- L827 _private member_ `TArray<FWebBrowserDragRegion> DragRegions;`
- L829 _private member_ `TWeakPtr<SWindow> ParentWindow;`
- L831 _private member_ `TUniquePtr<FCEFWebBrowserWindowRHIHelper> RHIRenderHelper;`
- L834 _private member_ `bool bInDirectHwndMode;`
- L837 _private member_ `bool bHasCorrectNativeCefBuffer;`
- L838 _private member_ `TSharedPtr<FCEFCapturedFrame> CapturedCefFrame;`
- L840 _private member_ `size_t NumFramesSinceViewportResize;`

#### Free symbols / members of external scopes

- L173 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);`
- L179 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L185 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L191 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L197 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L268 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L274 _delegate_ `DECLARE_DERIVED_EVENT(FCEFWebBrowserWindow, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`
- L843 _typedef_ `typedef FCEFWebBrowserWindow FWebBrowserWindow;`

### `Source/Runtime/WebBrowser/Private/CEF/CEFWebBrowserWindowRHIHelper.h` (Private)


#### class `FCEFWebBrowserWindowRHIHelper`  
`class FCEFWebBrowserWindowRHIHelper`  
_L25-50_
- desc: Implementation of RHI renderer details for the CEF accelerated rendering path
- L28 _public prototype_ `FCEFWebBrowserWindowRHIHelper();`
- L29 _public prototype_ `virtual ~FCEFWebBrowserWindowRHIHelper() = default;`
- L31 _public prototype_ `static bool BUseSupportedRHIRenderer();`
- L32 _public prototype_ `static uint64_t GetRHIAdapterLuid();`
- L35 _public prototype_ `FSlateUpdatableTexture* CreateSlateUpdatableTexture(const FIntPoint& TextureSize);`
- L36 _public prototype_ `void ReleaseSlateUpdatableTexture(FSlateUpdatableTexture* SlateTexture);`
- L37 _public prototype_ `FSlateUpdatableTexture* ResizeSlateUpdatableTexture(FSlateUpdatableTexture* SlateTexture, const FIntPoint& TextureSize);`
- L39 _public prototype_ `bool CopySharedTextureSync(FSlateUpdatableTexture* SlateTexture, void* SharedHandle, const FIntRect& DirtyIn);`
- L42 _private prototype_ `bool EnsureShareable(FSlateUpdatableTexture* SlateTexture);`
- L44 _private member_ `TMap<FSlateUpdatableTexture*, TSharedPtr<void>> SlateTextureHandles;`
- L47 _private member_ `TComPtr<ID3D11Device> D3D11Device;`
- L48 _private member_ `TComPtr<ID3D11DeviceContext> D3D11DeviceContext;`

### `Source/Runtime/WebBrowser/Private/MobileJS/MobileJSScripting.h` (Private)


#### class `FMobileJSScripting`  
`class FMobileJSScripting : public FWebJSScripting , public TSharedFromThis<FMobileJSScripting>`  
_L19-73_
- inherits: `FWebJSScripting,TSharedFromThis<FMobileJSScripting>`
- desc: Implements handling of bridging UObjects client side with JavaScript renderer side.
- L24 _public member_ `static const FString JSMessageTag;`
- L25 _public member_ `static const FString JSMessageHandler;`
- L27 _public prototype_ `FMobileJSScripting(bool bJSBindingToLoweringEnabled, bool bInjectJSOnPageStarted, bool bDefaultJSReturnInDict);`
- L29 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L30 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L31 _public prototype_ `void BindUObject(const TSharedRef<class IWebBrowserWindow>& InWindow, const FString& Name, UObject* Object, bool bIsPermanent = true);`
- L32 _public prototype_ `void UnbindUObject(const TSharedRef<class IWebBrowserWindow>& InWindow, const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true);`
- L41 _public prototype_ `bool OnJsMessageReceived(const FString& Command, const TArray<FString>& Params, const FString& Origin);` — Called when a message was received from the browser process. @param Command The command sent from the browser. @param Params Command-specific data. @return true if the message was handled, else false.
- L43 _public prototype_ `FString ConvertStruct(UStruct* TypeInfo, const void* StructPtr);`
- L44 _public prototype_ `FString ConvertObject(UObject* Object);`
- L46 _public prototype_ `virtual void InvokeJSFunction(FGuid FunctionId, int32 ArgCount, FWebJSParam Arguments[], bool bIsError=false) override;`
- L47 _public prototype_ `virtual void InvokeJSErrorResult(FGuid FunctionId, const FString& Error) override;`
- L48 _public prototype_ `void PageStarted(const TSharedRef<class IWebBrowserWindow>& InWindow);` — Called when page load started
- L49 _public prototype_ `void PageLoaded(const TSharedRef<class IWebBrowserWindow>& InWindow);` — Called on page completely loaded
- L50 _public prototype_ `void SetWindow(const TSharedRef<class IWebBrowserWindow>& InWindow);`
- L53 _private prototype_ `void InitializeScript(const TSharedRef<class IWebBrowserWindow>& InWindow);`
- L54 _private prototype_ `void InjectJavascript(const TSharedRef<class IWebBrowserWindow>& InWindow);`
- L55 _private prototype_ `void InvokeJSFunctionRaw(FGuid FunctionId, const FString& JSValue, bool bIsError=false);`
- L56 _private function_ `bool IsValid()`
- L60 _private prototype_ `void AddPermanentBind(const FString& Name, UObject* Object);`
- L61 _private prototype_ `void RemovePermanentBind(const FString& Name, UObject* Object);`
- L65 _private prototype_ `bool HandleExecuteUObjectMethodMessage(const TArray<FString>& Params);`
- L68 _private member_ `TWeakPtr<class IWebBrowserWindow> WindowPtr;` — Pointer to the Mobile Browser for this window.
- L71 _private member_ `bool bInjectJSOnPageStarted;` — When to inject JS code
- L72 _private member_ `bool bDefaultJSReturnInDict;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMobileJSScripting, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMobileJSScripting, Log, All);`
- L13 _typedef_ `typedef TSharedRef<class FMobileJSScripting> FMobileJSScriptingRef;`
- L14 _typedef_ `typedef TSharedPtr<class FMobileJSScripting> FMobileJSScriptingPtr;`

### `Source/Runtime/WebBrowser/Private/MobileJS/MobileJSStructDeserializerBackend.h` (Private)


#### class `FMobileJSStructDeserializerBackend`  
`class FMobileJSStructDeserializerBackend : public FJsonStructDeserializerBackend`  
_L13-25_
- inherits: `FJsonStructDeserializerBackend`
- L17 _public prototype_ `FMobileJSStructDeserializerBackend(FMobileJSScriptingRef InScripting, const FString& JsonString);`
- L19 _public prototype_ `virtual bool ReadProperty( FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) override;`
- L22 _private member_ `FMobileJSScriptingRef Scripting;`
- L23 _private member_ `TArray<uint8> JsonData;`
- L24 _private member_ `FMemoryReader Reader;`

### `Source/Runtime/WebBrowser/Private/MobileJS/MobileJSStructSerializerBackend.h` (Private)


#### class `FMobileJSStructSerializerBackend`  
`class FMobileJSStructSerializerBackend : public FJsonStructSerializerBackend`  
_L20-43_
- inherits: `FJsonStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using JavaScript. Based on FJsonStructSerializerBackend, it adds support for certain object types not representable in pure JSON
- L30 _public prototype_ `FMobileJSStructSerializerBackend(FMobileJSScriptingRef InScripting);` — Creates and initializes a new instance. @param InScripting An instance of a web browser scripting obnject.
- L33 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override;`
- L35 _public prototype_ `FString ToString();`
- L38 _private prototype_ `void WriteUObject(const FStructSerializerState& State, UObject* Value);`
- L40 _private member_ `FMobileJSScriptingRef Scripting;`
- L41 _private member_ `TArray<uint8> ReturnBuffer;`
- L42 _private member_ `FMemoryWriter Writer;`

### `Source/Runtime/WebBrowser/Private/Native/NativeJSScripting.h` (Private)


#### class `FNativeJSScripting`  
`class FNativeJSScripting : public FWebJSScripting , public TSharedFromThis<FNativeJSScripting>`  
_L17-52_
- inherits: `FWebJSScripting,TSharedFromThis<FNativeJSScripting>`
- desc: Implements handling of bridging UObjects client side with JavaScript renderer side.
- L24 _public prototype_ `FNativeJSScripting(bool bJSBindingToLoweringEnabled, TSharedRef<FNativeWebBrowserProxy> Window);`
- L26 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L27 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L29 _public prototype_ `bool OnJsMessageReceived(const FString& Message);`
- L31 _public prototype_ `FString ConvertStruct(UStruct* TypeInfo, const void* StructPtr);`
- L32 _public prototype_ `FString ConvertObject(UObject* Object);`
- L34 _public prototype_ `virtual void InvokeJSFunction(FGuid FunctionId, int32 ArgCount, FWebJSParam Arguments[], bool bIsError=false) override;`
- L35 _public prototype_ `virtual void InvokeJSErrorResult(FGuid FunctionId, const FString& Error) override;`
- L36 _public prototype_ `void PageLoaded();`
- L39 _private prototype_ `FString GetInitializeScript();`
- L40 _private prototype_ `void InvokeJSFunctionRaw(FGuid FunctionId, const FString& JSValue, bool bIsError=false);`
- L41 _private function_ `bool IsValid()`
- L47 _private prototype_ `bool HandleExecuteUObjectMethodMessage(const TArray<FString>& Params);` — Message handling helpers
- L48 _private prototype_ `void ExecuteJavascript(const FString& Javascript);`
- L50 _private member_ `TWeakPtr<FNativeWebBrowserProxy> WindowPtr;`
- L51 _private member_ `bool bLoaded;`

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TSharedRef<class FNativeJSScripting> FNativeJSScriptingRef;`
- L10 _typedef_ `typedef TSharedPtr<class FNativeJSScripting> FNativeJSScriptingPtr;`

### `Source/Runtime/WebBrowser/Private/Native/NativeJSStructDeserializerBackend.h` (Private)


#### class `FNativeJSStructDeserializerBackend`  
`class FNativeJSStructDeserializerBackend : public FJsonStructDeserializerBackend`  
_L10-21_
- inherits: `FJsonStructDeserializerBackend`
- L14 _public prototype_ `FNativeJSStructDeserializerBackend(FNativeJSScriptingRef InScripting, FMemoryReader& Reader);`
- L16 _public prototype_ `virtual bool ReadProperty( FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) override;`
- L19 _private member_ `FNativeJSScriptingRef Scripting;`

### `Source/Runtime/WebBrowser/Private/Native/NativeJSStructSerializerBackend.h` (Private)


#### class `FNativeJSStructSerializerBackend`  
`class FNativeJSStructSerializerBackend : public FJsonStructSerializerBackend`  
_L17-36_
- inherits: `FJsonStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using JavaScript. Based on FJsonStructSerializerBackend, it adds support for certain object types not representable in pure JSON
- L27 _public prototype_ `FNativeJSStructSerializerBackend(FNativeJSScriptingRef InScripting, FMemoryWriter& Writer);` — Creates and initializes a new instance. @param InScripting An instance of a web browser scripting obnject.
- L30 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override;`
- L33 _private prototype_ `void WriteUObject(const FStructSerializerState& State, UObject* Value);`
- L35 _private member_ `FNativeJSScriptingRef Scripting;`

### `Source/Runtime/WebBrowser/Private/Native/NativeWebBrowserProxy.h` (Private)


#### class `FNativeWebBrowserProxy`  
`class FNativeWebBrowserProxy : public IWebBrowserWindow , public TSharedFromThis<FNativeWebBrowserProxy>`  
_L8-271_
- inherits: `IWebBrowserWindow,TSharedFromThis<FNativeWebBrowserProxy>`
- L16 _private prototype_ `FNativeWebBrowserProxy(bool bJSBindingToLoweringEnabled);`
- L17 _private prototype_ `void Initialize();`
- L18 _private prototype_ `void HandleEmbeddedCommunication(const struct FEmbeddedCallParamsHelper& Params);`
- L19 _private prototype_ `bool OnJsMessageReceived(const FString& Message);`
- L22 _public prototype_ `virtual ~FNativeWebBrowserProxy();`
- L27 _public prototype_ `virtual void LoadURL(FString NewURL) override;`
- L28 _public prototype_ `virtual void LoadString(FString Contents, FString DummyURL) override;`
- L29 _public prototype_ `virtual void SetViewportSize(FIntPoint WindowSize, FIntPoint WindowPos) override;`
- L30 _public prototype_ `virtual FIntPoint GetViewportSize() const override;`
- L32 _public prototype_ `virtual class FSlateShaderResource* GetTexture(bool bIsPopup = false) override;`
- L33 _public prototype_ `virtual bool IsValid() const override;`
- L34 _public prototype_ `virtual bool IsInitialized() const override;`
- L35 _public prototype_ `virtual bool IsClosing() const override;`
- L36 _public prototype_ `virtual EWebBrowserDocumentState GetDocumentLoadingState() const override;`
- L37 _public prototype_ `virtual FString GetTitle() const override;`
- L38 _public prototype_ `virtual FString GetUrl() const override;`
- L39 _public prototype_ `virtual void GetSource(TFunction<void(const FString&)> Callback) const override;`
- L40 _public prototype_ `virtual bool OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L41 _public prototype_ `virtual bool OnKeyUp(const FKeyEvent& InKeyEvent) override;`
- L42 _public prototype_ `virtual bool OnKeyChar(const FCharacterEvent& InCharacterEvent) override;`
- L43 _public prototype_ `virtual void SetSupportsMouseWheel(bool bValue) override;`
- L44 _public prototype_ `virtual bool GetSupportsMouseWheel() const override;`
- L46 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L47 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L48 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L49 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L50 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) override;`
- L52 _public function_ `virtual FOnDragWindow& OnDragWindow() override`
- L56 _public prototype_ `virtual void OnFocus(bool SetFocus, bool bIsPopup) override;`
- L57 _public prototype_ `virtual void OnCaptureLost() override;`
- L58 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L59 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L60 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L61 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L62 _public prototype_ `virtual bool CanGoBack() const override;`
- L63 _public prototype_ `virtual void GoBack() override;`
- L64 _public prototype_ `virtual bool CanGoForward() const override;`
- L65 _public prototype_ `virtual void GoForward() override;`
- L66 _public prototype_ `virtual bool IsLoading() const override;`
- L67 _public prototype_ `virtual void Reload() override;`
- L68 _public prototype_ `virtual void StopLoad() override;`
- L69 _public prototype_ `virtual void ExecuteJavascript(const FString& Script) override;`
- L70 _public prototype_ `virtual void CloseBrowser(bool bForce, bool bBlockTillClosed) override;`
- L71 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L72 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) override;`
- L73 _public prototype_ `virtual int GetLoadError() override;`
- L74 _public prototype_ `virtual void SetIsDisabled(bool bValue) override;`
- L75 _public prototype_ `virtual TSharedPtr<SWindow> GetParentWindow() const override;`
- L76 _public prototype_ `virtual void SetParentWindow(TSharedPtr<SWindow> Window) override;`
- L77 _public function_ `virtual void ShowFloatingCloseButton(bool bShow, bool bDraggable) override`
- L82 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);` — @todo: None of these are actually called at the moment.
- L83 _public function_ `virtual FOnDocumentStateChanged& OnDocumentStateChanged() override`
- L88 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L89 _public function_ `virtual FOnTitleChanged& OnTitleChanged() override`
- L94 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L95 _public function_ `virtual FOnUrlChanged& OnUrlChanged() override`
- L100 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L101 _public function_ `virtual FOnToolTip& OnToolTip() override`
- L106 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L107 _public function_ `virtual FOnNeedsRedraw& OnNeedsRedraw() override`
- L112 _public function_ `virtual FOnBeforeBrowse& OnBeforeBrowse() override`
- L117 _public function_ `virtual FOnLoadUrl& OnLoadUrl() override`
- L122 _public function_ `virtual FOnCreateWindow& OnCreateWindow() override`
- L127 _public function_ `virtual FOnCloseWindow& OnCloseWindow() override`
- L132 _public function_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) override`
- L137 _public function_ `virtual FOnBeforePopupDelegate& OnBeforePopup() override`
- L142 _public function_ `virtual FOnBeforeResourceLoadDelegate& OnBeforeResourceLoad() override`
- L147 _public function_ `virtual FOnResourceLoadCompleteDelegate& OnResourceLoadComplete() override`
- L152 _public function_ `virtual FOnConsoleMessageDelegate& OnConsoleMessage() override`
- L157 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L158 _public function_ `virtual FOnShowPopup& OnShowPopup() override`
- L163 _public prototype_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`
- L164 _public function_ `virtual FOnDismissPopup& OnDismissPopup() override`
- L169 _public function_ `virtual FOnShowDialog& OnShowDialog() override`
- L174 _public function_ `virtual FOnDismissAllDialogs& OnDismissAllDialogs() override`
- L179 _public function_ `virtual FOnSuppressContextMenu& OnSuppressContextMenu() override`
- L184 _public function_ `virtual FOnUnhandledKeyDown& OnUnhandledKeyDown() override`
- L189 _public function_ `virtual FOnUnhandledKeyUp& OnUnhandledKeyUp() override`
- L194 _public function_ `virtual FOnUnhandledKeyChar& OnUnhandledKeyChar() override`
- L202 _private member_ `FOnDocumentStateChanged DocumentStateChangedEvent;` — Delegate for broadcasting load state changes.
- L205 _private member_ `FOnTitleChanged TitleChangedEvent;` — Delegate for broadcasting title changes.
- L208 _private member_ `FOnUrlChanged UrlChangedEvent;` — Delegate for broadcasting address changes.
- L211 _private member_ `FOnToolTip ToolTipEvent;` — Delegate for broadcasting when the browser wants to show a tool tip.
- L214 _private member_ `FOnNeedsRedraw NeedsRedrawEvent;` — Delegate for notifying that the window needs refreshing.
- L217 _private member_ `FOnBeforeBrowse BeforeBrowseDelegate;` — Delegate that is executed prior to browser navigation.
- L220 _private member_ `FOnLoadUrl LoadUrlDelegate;` — Delegate for overriding Url contents.
- L223 _private member_ `FOnBeforePopupDelegate BeforePopupDelegate;` — Delegate for notifying that a popup window is attempting to open.
- L226 _private member_ `FOnBeforeResourceLoadDelegate BeforeResourceLoadDelegate;` — Delegate that is invoked before the browser loads a resource. Its primary purpose is to inject headers into the request.
- L229 _private member_ `FOnResourceLoadCompleteDelegate ResourceLoadCompleteDelegate;` — Delegate that is invoked on completion of browser resource loads. Its primary purpose is to allow response to failures.
- L232 _private member_ `FOnConsoleMessageDelegate ConsoleMessageDelegate;` — Delegate that is invoked for each console message
- L235 _private member_ `FOnCreateWindow CreateWindowDelegate;` — Delegate for handling requests to create new windows.
- L238 _private member_ `FOnCloseWindow CloseWindowDelegate;` — Delegate for handling requests to close new windows that were created.
- L241 _private member_ `FOnFloatingCloseButtonPressed FloatingCloseButtonPressedDelegate;` — Delegate for handling requests to close from the webview floating close button.
- L244 _private member_ `FOnShowPopup ShowPopupEvent;` — Delegate for handling requests to show the popup menu.
- L247 _private member_ `FOnDismissPopup DismissPopupEvent;` — Delegate for handling requests to dismiss the current popup menu.
- L250 _private member_ `FOnShowDialog ShowDialogDelegate;` — Delegate for showing dialogs.
- L253 _private member_ `FOnDismissAllDialogs DismissAllDialogsDelegate;` — Delegate for dismissing all dialogs.
- L256 _private member_ `FOnSuppressContextMenu SuppressContextMenuDelgate;` — Delegate for suppressing context menu
- L259 _private member_ `FOnUnhandledKeyDown UnhandledKeyDownDelegate;` — Delegate for handling key down events not handled by the browser.
- L262 _private member_ `FOnUnhandledKeyUp UnhandledKeyUpDelegate;` — Delegate for handling key up events not handled by the browser.
- L265 _private member_ `FOnUnhandledKeyChar UnhandledKeyCharDelegate;` — Delegate for handling key char events not handled by the browser.
- L267 _private member_ `FOnDragWindow DragWindowDelegate;`
- L269 _private member_ `bool bJSBindingToLoweringEnabled;`
- L270 _private member_ `FNativeJSScriptingPtr Scripting;`

#### Free symbols / members of external scopes

- L82 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnDocumentStateChanged, FOnDocumentStateChanged);` — @todo: None of these are actually called at the moment.
- L88 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnTitleChanged, FOnTitleChanged);`
- L94 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnUrlChanged, FOnUrlChanged);`
- L100 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnToolTip, FOnToolTip);`
- L106 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnNeedsRedraw, FOnNeedsRedraw);`
- L157 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnShowPopup, FOnShowPopup);`
- L163 _delegate_ `DECLARE_DERIVED_EVENT(FNativeWebBrowserProxy, IWebBrowserWindow::FOnDismissPopup, FOnDismissPopup);`

### `Source/Runtime/WebBrowser/Private/WebBrowserLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebBrowser, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebBrowser, Log, All);`

### `Source/Runtime/WebBrowser/Private/WebBrowserSingleton.h` (Private)


#### class `FWebBrowserSingleton`  
`class FWebBrowserSingleton : public IWebBrowserSingleton , public FTSTickerObjectBase`  
_L53-218_
- inherits: `IWebBrowserSingleton,FTSTickerObjectBase`
- desc: Implementation of singleton class that takes care of general web browser tasks
- L60 _public prototype_ `FWebBrowserSingleton(const FWebBrowserInitSettings& WebBrowserInitSettings);` — Constructor.
- L63 _public prototype_ `virtual ~FWebBrowserSingleton();` — Virtual destructor.
- L70 _public prototype_ `static FString GetCurrentLocaleCode();` — Gets the Current Locale Code in the format CEF expects @return Locale code as either "xx" or "xx-YY"
- L77 _public prototype_ `virtual bool IsShuttingDown() const override;`
- L79 _public prototype_ `virtual FString ApplicationCacheDir() const override;`
- L81 _public prototype_ `virtual TSharedRef<IWebBrowserWindowFactory> GetWebBrowserWindowFactory() const override;`
- L83 _public prototype_ `TSharedPtr<IWebBrowserWindow> CreateBrowserWindow( TSharedPtr<FCEFWebBrowserWindow>& BrowserWindowParent, TSharedPtr<FWebBrowserWindowInfo>& BrowserWindowInfo) override;`
- L87 _public prototype_ `TSharedPtr<IWebBrowserWindow> CreateBrowserWindow(const FCreateBrowserWindowSettings& Settings) override;`
- L90 _public prototype_ `TSharedPtr<IWebBrowserWindow> CreateNativeBrowserProxy() override;`
- L93 _public function_ `virtual TSharedPtr<IWebBrowserCookieManager> GetCookieManager() const override`
- L98 _public prototype_ `virtual TSharedPtr<IWebBrowserCookieManager> GetCookieManager(TOptional<FString> ContextId) const override;`
- L100 _public prototype_ `virtual bool RegisterContext(const FBrowserContextSettings& Settings) override;`
- L102 _public prototype_ `virtual bool UnregisterContext(const FString& ContextId) override;`
- L104 _public prototype_ `virtual bool RegisterSchemeHandlerFactory(FString Scheme, FString Domain, IWebBrowserSchemeHandlerFactory* WebBrowserSchemeHandlerFactory) override;`
- L106 _public prototype_ `virtual bool UnregisterSchemeHandlerFactory(IWebBrowserSchemeHandlerFactory* WebBrowserSchemeHandlerFactory) override;`
- L108 _public function_ `virtual bool IsDevToolsShortcutEnabled() override`
- L113 _public function_ `virtual void SetDevToolsShortcutEnabled(bool Value) override`
- L118 _public function_ `virtual void SetJSBindingToLoweringEnabled(bool bEnabled) override`
- L123 _public prototype_ `virtual void ClearOldCacheFolders(const FString& CachePathRoot, const FString& CachePrefix) override;`
- L126 _public function_ `virtual void SetDefaultMaterial(UMaterialInterface* InDefaultMaterial) override` — Set a reference to UWebBrowser's default material
- L134 _public function_ `virtual void SetDefaultTranslucentMaterial(UMaterialInterface* InDefaultMaterial) override` — Set a reference to UWebBrowser's translucent material
- L142 _public function_ `virtual UMaterialInterface* GetDefaultMaterial() override` — Get a reference to UWebBrowser's default material
- L152 _public function_ `virtual UMaterialInterface* GetDefaultTranslucentMaterial() override` — Get a reference to UWebBrowser's translucent material
- L164 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L168 _public prototype_ `bool URLRequestAllowsCredentials(const FString& URL);` — Return true if this URL will support adding an Authorization header to it
- L173 _private member_ `FCriticalSection WindowInterfacesCS;` — Critical section for thread safe modification of WindowInterfaces array.
- L175 _private member_ `TSharedRef<IWebBrowserWindowFactory> WebBrowserWindowFactory;`
- L177 _private member_ `TSharedPtr<IWebBrowserCookieManager> DefaultCookieManager;`
- L181 _private prototype_ `FString GenerateWebCacheFolderName(const FString &InputPath);` — Helper function to generate the CEF build unique name for the cache_path
- L183 _private prototype_ `void WaitForTaskQueueFlush();` — Helper function that blocks until the CEF task queue has processed a posted task, flushing the queue
- L185 _private member_ `bool bCEFInitialized;`
- L186 _private member_ `bool bTaskQueueFlushed;`
- L189 _private member_ `CefRefPtr<FCEFBrowserApp> CEFBrowserApp;` — Pointer to the CEF App implementation
- L191 _private member_ `TMap<FString, CefRefPtr<CefRequestContext>> RequestContexts;`
- L192 _private member_ `TMap<FString, CefRefPtr<FCEFResourceContextHandler>> RequestResourceHandlers;`
- L193 _private member_ `FCefSchemeHandlerFactories SchemeHandlerFactories;`
- L196 _private member_ `TArray<TWeakPtr<FCEFWebBrowserWindow>> WindowInterfaces;` — List of currently existing browser windows
- L199 _private member_ `TArray<TWeakPtr<IWebBrowserWindow>> WindowInterfaces;` — List of currently existing browser windows
- L203 _private member_ `FString UserAgentApplication;` — Application part of user agent string passed to HTTP requests
- L205 _private member_ `bool bDevToolsShortcutEnabled;`
- L207 _private member_ `bool bJSBindingsToLoweringEnabled;`
- L209 _private member_ `bool bAppIsFocused;`
- L213 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultMaterial;` — Reference to UWebBrowser's default material
- L216 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultTranslucentMaterial;` — Reference to UWebBrowser's translucent material

#### class `FCefWebBrowserCookieManagerFactory`  
`class FCefWebBrowserCookieManagerFactory`  
_L226-231_
- L229 _public prototype_ `static TSharedRef<IWebBrowserCookieManager> Create( const CefRefPtr<CefCookieManager>& CookieManager);`

### `Source/Runtime/WebBrowser/Private/WebJSScripting.h` (Private)


#### class `FWebJSScripting`  
`class FWebJSScripting : public FGCObject`  
_L15-149_
- inherits: `FGCObject`
- desc: Implements handling of bridging UObjects client side with JavaScript renderer side.
- L19 _public function_ `FWebJSScripting(bool bInJSBindingToLoweringEnabled) : BaseGuid(FGuid::NewGuid()) , bJSBindingToLoweringEnabled(bInJSBindingToLoweringEnabled)`
- L24 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) =0;`
- L25 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object = nullptr, bool bIsPermanent = true) =0;`
- L28 _public prototype_ `virtual void InvokeJSFunction(FGuid FunctionId, int32 ArgCount, FWebJSParam Arguments[], bool bIsError=false) =0;`
- L29 _public prototype_ `virtual void InvokeJSErrorResult(FGuid FunctionId, const FString& Error) =0;`
- L31 _public function_ `FString GetBindingName(const FString& Name, UObject* Object) const`
- L36 _public function_ `FString GetBindingName(const FFieldVariant& Property) const`
- L44 _public function_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override` — FGCObject API
- L52 _public function_ `virtual FString GetReferencerName() const override`
- L61 _protected function_ `FGuid PtrToGuid(UObject* Ptr)` — Creates a reversible memory addres -> psuedo-guid mapping. This is done by xoring the address with the first 64 bits of a base guid owned by the instance. Used to identify UObjects from the render process withough exposing internal pointers.
- L81 _protected function_ `UObject* GuidToPtr(const FGuid& Guid)` — In addition to reversing the mapping, it verifies that we are currently holding on to an instance of that UObject
- L101 _protected function_ `void RetainBinding(UObject* Object)`
- L116 _protected function_ `void ReleaseBinding(UObject* Object)`
- L139 _protected member_ `FGuid BaseGuid;` — Private data
- L142 _protected member_ `TMap<TObjectPtr<UObject>, ObjectBinding> BoundObjects;` — UObjects currently visible on the renderer side.
- L145 _protected member_ `TMap<FString, UObject*> PermanentUObjectsByName;` — Reverse lookup for permanent bindings
- L148 _protected member_ `const bool bJSBindingToLoweringEnabled;` — The to-lowering option enable for the binding names.

#### struct `FWebJSScripting::ObjectBinding`  
`struct ObjectBinding`  
_L132-136_
- L134 _public member_ `bool bIsPermanent;`
- L135 _public member_ `int32 Refcount;`

### `Source/Runtime/WebBrowser/Public/IWebBrowserAdapter.h` (Public)


#### class `IWebBrowserAdapter`  
`class IWebBrowserAdapter`  
_L7-19_
- L11 _public prototype_ `virtual FString GetName() const = 0;`
- L13 _public prototype_ `virtual bool IsPermanent() const = 0;`
- L15 _public prototype_ `virtual void ConnectTo(const TSharedRef<IWebBrowserWindow>& BrowserWindow) = 0;`
- L17 _public prototype_ `virtual void DisconnectFrom(const TSharedRef<IWebBrowserWindow>& BrowserWindow) = 0;`

#### class `FWebBrowserAdapterFactory`  
`class FWebBrowserAdapterFactory`  
_L21-28_
- L25 _public prototype_ `static TSharedRef<IWebBrowserAdapter> Create(const FString& Name, UObject* JSBridge, bool IsPermanent);`
- L27 _public prototype_ `static TSharedRef<IWebBrowserAdapter> Create(const FString& Name, UObject* JSBridge, bool IsPermanent, const FString& ConnectScriptText, const FString& DisconnectScriptText);`

### `Source/Runtime/WebBrowser/Public/IWebBrowserCookieManager.h` (Public)


#### struct `FWebBrowserCookie`  
`struct FWebBrowserCookie`  
_L6-35_
- L10 _public member_ `FString Name;` — The cookie name.
- L13 _public member_ `FString Value;` — The cookie value.
- L18 _public member_ `FString Domain;` — If is empty a host cookie will be created instead of a domain cookie. Domain cookies are stored with a leading "." and are visible to sub-domains whereas host cookies are not.
- L22 _public member_ `FString Path;` — If is non-empty only URLs at or below the path will get the cookie value.
- L25 _public member_ `bool bSecure;` — If true the cookie will only be sent for HTTPS requests.
- L28 _public member_ `bool bHttpOnly;` — If true the cookie will only be sent for HTTP requests.
- L31 _public member_ `bool bHasExpires;` — If true the cookie will expire at the specified Expires datetime.
- L34 _public member_ `FDateTime Expires;` — The cookie expiration date is only valid if bHasExpires is true.

#### class `IWebBrowserCookieManager`  
`class IWebBrowserCookieManager`  
_L37-68_
- L40 _public typedef_ `typedef struct FWebBrowserCookie FCookie;`
- L55 _public prototype_ `virtual void SetCookie(const FString& URL, const FCookie& Cookie, TFunction<void(bool)> Completed = nullptr) = 0;` — Sets a cookie given a valid URL. This function expects each attribute to be well-formed. It will check for disallowed characters (e.g. the ';' character is disallowed within the cookie Value field) and fail without setting the cookie if such characters are found. @param URL The base URL to match when searching for cookies to remove. Use blank to match all URLs. @param Cookie The struct defining the state of the cookie to set @param Completed A callback function that will be invoked asynchronously on the game thread when the set is complete passing success bool.
- L67 _public prototype_ `virtual void DeleteCookies(const FString& URL = TEXT(""), const FString& CookieName = TEXT(""), TFunction<void(int)> Completed = nullptr) = 0;` — Delete all browser cookies. Removes all matching cookies. Leave both URL and CookieName blank to delete the entire cookie database. The actual deletion will be scheduled on the browser IO thread, so the operation may not have completed when the function returns. @param URL The base URL to match when searching for cookies to remove. Use blank to match all URLs. @param CookieName The name of the cookie to delete. If left unspecified, all cookies will be removed. @param Completed A callback function that will be invoked asynchronously on the game thread when the deletion is complete passing in the number of deleted objects.

### `Source/Runtime/WebBrowser/Public/IWebBrowserDialog.h` (Public)


#### enum `EWebBrowserDialogType`  
`enum class EWebBrowserDialogType`  
_L11-21_
- L14 _public enumerator_ `Alert = 0` — Alert dialog. Used to show a message to a user. It should only have a single button to dismiss it.
- L16 _public enumerator_ `Confirm` — Confirm dialog. Shows a message to the user. It should have two buttons to either accept or decline the prompt.
- L18 _public enumerator_ `Prompt` — Prompt dialog. Shows a prompt asking for user input. The user can enter text and either confirm or dismiss it.
- L20 _public enumerator_ `Unload = 127` — Unload dialog. This type of dialog is shown to confirm navigating away from a page containing user-edited content.

#### enum `EWebBrowserDialogEventResponse`  
`enum class EWebBrowserDialogEventResponse`  
_L26-36_
- desc: Return value from dialog event handle specifying what action should be taken.
- L29 _public enumerator_ `Unhandled` — Return Unhandled to use the default dialog implementation. This is the default behavior when no handler is attached.
- L31 _public enumerator_ `Continue` — Do not show any dialog and return as if the user accepted the action.
- L33 _public enumerator_ `Ignore` — Do not show any dialog and return as if the user dismissed the action.
- L35 _public enumerator_ `Handled` — The event handler will take care of showing the dialog. It must call IWebBrowserDialog::Continue once it has been dismissed.

#### class `IWebBrowserDialog`  
`class IWebBrowserDialog`  
_L41-81_
- desc: Browser dialog parameters passed to OnBrowserDialog event handlers.
- L45 _public prototype_ `virtual ~IWebBrowserDialog() = default;`
- L51 _public prototype_ `virtual EWebBrowserDialogType GetType() = 0;` — What kind of dialog should be shown. @return the dialog type
- L60 _public prototype_ `virtual void Continue(bool Success = true, const FText& UserResponse = FText::GetEmpty()) = 0;` — Tell the browser to continue with the result of the dialog. If this method is used, the original event handler must return EWebBrowserDialogEventResponse::Handled. @param Success Did the user accept the dialog or not? @param UserResponse Only for Prompt dialog, the text entered by the user.
- L66 _public prototype_ `virtual const FText& GetMessageText() = 0;` — Get the dialog message. @return the message to show in the dialog.
- L72 _public prototype_ `virtual const FText& GetDefaultPrompt() = 0;` — Only valid for Prompt dialogs. @return the default value to show in the text entry box.
- L78 _public prototype_ `virtual bool IsReload() = 0;` — Only valid for Unload dialogs. @return true if the dialog is confirming a reload of the current page.

### `Source/Runtime/WebBrowser/Public/IWebBrowserPopupFeatures.h` (Public)


#### class `IWebBrowserPopupFeatures`  
`class IWebBrowserPopupFeatures`  
_L7-29_
- L10 _public prototype_ `virtual ~IWebBrowserPopupFeatures() = default;`
- L12 _public prototype_ `virtual int GetX() const = 0;`
- L13 _public prototype_ `virtual bool IsXSet() const = 0;`
- L14 _public prototype_ `virtual int GetY() const = 0;`
- L15 _public prototype_ `virtual bool IsYSet() const = 0;`
- L16 _public prototype_ `virtual int GetWidth() const = 0;`
- L17 _public prototype_ `virtual bool IsWidthSet() const = 0;`
- L18 _public prototype_ `virtual int GetHeight() const = 0;`
- L19 _public prototype_ `virtual bool IsHeightSet() const = 0;`
- L20 _public prototype_ `virtual bool IsMenuBarVisible() const = 0;`
- L21 _public prototype_ `virtual bool IsStatusBarVisible() const = 0;`
- L22 _public prototype_ `virtual bool IsToolBarVisible() const = 0;`
- L23 _public prototype_ `virtual bool IsLocationBarVisible() const = 0;`
- L24 _public prototype_ `virtual bool IsScrollbarsVisible() const = 0;`
- L25 _public prototype_ `virtual bool IsResizable() const = 0;`
- L26 _public prototype_ `virtual bool IsFullscreen() const = 0;`
- L27 _public prototype_ `virtual bool IsDialog() const = 0;`
- L28 _public prototype_ `virtual TArray<FString> GetAdditionalFeatures() const = 0;`

### `Source/Runtime/WebBrowser/Public/IWebBrowserResourceLoader.h` (Public)


#### Free symbols / members of external scopes

- L7 _typedef_ `typedef TMap<FString, FString> FContextRequestHeaders;`
- L8 _delegate_ `DECLARE_DELEGATE_FourParams(FOnBeforeContextResourceLoadDelegate, FString , FString , FContextRequestHeaders& , const bool );`
- L8 _prototype_ `DECLARE_DELEGATE_FourParams(FOnBeforeContextResourceLoadDelegate, FString , FString , FContextRequestHeaders& , const bool );`

### `Source/Runtime/WebBrowser/Public/IWebBrowserSchemeHandler.h` (Public)


#### class `IWebBrowserSchemeHandler`  
`class IWebBrowserSchemeHandler`  
_L10-86_
- desc: This is the interface that needs to be implemented to handle a request made via a custom scheme. It will be created by implementing an IWebBrowserSchemeHandlerFactory, given to the web browser singleton.
- L52 _public prototype_ `virtual ~IWebBrowserSchemeHandler() = default;`
- L62 _public prototype_ `virtual bool ProcessRequest(const FString& Verb, const FString& Url, const FSimpleDelegate& OnHeadersReady) = 0;` — Process an incoming request. @param   Verb            This is the verb used for the request (GET, PUT, POST, etc). @param   Url             This is the full url for the request being made. @param   OnHeadersReady  You must execute this delegate once the response headers are ready to be retrieved with GetResponseHeaders. You may execute it during this call to state headers are available now. @return You should return true if the request has been accepted and will be processed, otherwise false to cancel this request.
- L68 _public prototype_ `virtual void GetResponseHeaders(IHeaders& OutHeaders) = 0;` — Retrieves the headers for this request. @param   OutHeaders      The interface to use to set headers.
- L80 _public prototype_ `virtual bool ReadResponse(uint8* OutBytes, int32 BytesToRead, int32& BytesRead, const FSimpleDelegate& OnMoreDataReady) = 0;` — Retrieves the headers for this request. @param   OutBytes            You should copy up to BytesToRead of data to this ptr. @param   BytesToRead         The maximum number of bytes that can be copied to OutBytes. @param   BytesRead           You should set this to the number of bytes that were copied. This can be set to zero, to indicate more data is not ready yet, and OnMoreDataReady must then be executed when there is. @param   OnMoreDataReady     You should execute this delegate when more data is available to read. @return You should return true if more data needs to be read, otherwise false if this is the end of the response data.
- L85 _public prototype_ `virtual void Cancel() = 0;` — Called if the request should be canceled.

#### class `IWebBrowserSchemeHandler::IHeaders`  
`class IHeaders`  
_L16-49_
- desc: An interface for setting response headers emulating a http implementation.
- L23 _public prototype_ `virtual void SetMimeType(const TCHAR* MimeType) = 0;` — Sets the mime type for the response. @param   MimeType        The Mime Type.
- L29 _public prototype_ `virtual void SetStatusCode(int32 StatusCode) = 0;` — Sets the status code for the response. @param   StatusCode      The status code.
- L35 _public prototype_ `virtual void SetContentLength(int32 ContentLength) = 0;` — Sets the content length for the response. @param   ContentLength   The size of the response content in bytes.
- L41 _public prototype_ `virtual void SetRedirect(const TCHAR* Url) = 0;` — Sets a redirect url for the response. Other calls will be ignored if this is used. @param   Url             The url to redirect to.
- L48 _public prototype_ `virtual void SetHeader(const TCHAR* Key, const TCHAR* Value) = 0;` — Sets a header for the response. @param   Key             The header key. @param   Value           The header value.

#### class `IWebBrowserSchemeHandlerFactory`  
`class IWebBrowserSchemeHandlerFactory`  
_L91-102_
- desc: This is the interface that needs to be implemented to instantiate a scheme request handler.
- L94 _public prototype_ `virtual ~IWebBrowserSchemeHandlerFactory() = default;`
- L101 _public prototype_ `virtual TUniquePtr<IWebBrowserSchemeHandler> Create(FString Verb, FString Url) = 0;` — Instantiates an appropriate handler for the given request details. @param   Verb            This is the verb used for the request (GET, PUT, POST, etc). @param   Url             This is the full url for the request being made.

### `Source/Runtime/WebBrowser/Public/IWebBrowserSingleton.h` (Public)


#### class `IWebBrowserWindowFactory`  
`class IWebBrowserWindowFactory`  
_L15-34_
- L19 _public prototype_ `virtual TSharedPtr<IWebBrowserWindow> Create( TSharedPtr<FCEFWebBrowserWindow>& BrowserWindowParent, TSharedPtr<FWebBrowserWindowInfo>& BrowserWindowInfo) = 0;`
- L23 _public prototype_ `virtual TSharedPtr<IWebBrowserWindow> Create( void* OSWindowHandle, FString InitialURL, bool bUseTransparency, bool bThumbMouseButtonNavigation, bool InterceptLoadRequests = true, TOptional<FString> ContentsToLoad = TOptional<FString>(), TOptional<FString> UserAgentApplication = TOptional<FString>(), bool ShowErrorMessage = true, FColor BackgroundColor = FColor(255, 255, 255, 255), bool bMobileJSReturnInDict = true) = 0;`

#### struct `FBrowserContextSettings`  
`struct FBrowserContextSettings`  
_L36-54_
- L38 _public function_ `FBrowserContextSettings(const FString& InId) : Id(InId) , AcceptLanguageList() , CookieStorageLocation() , bPersistSessionCookies(false) , bIgnoreCertificateErrors(false) , bEnableNetSecurityExpiration(true)`
- L47 _public member_ `FString Id;`
- L48 _public member_ `FString AcceptLanguageList;`
- L49 _public member_ `FString CookieStorageLocation;`
- L50 _public member_ `bool bPersistSessionCookies;`
- L51 _public member_ `bool bIgnoreCertificateErrors;`
- L52 _public member_ `bool bEnableNetSecurityExpiration;`
- L53 _public member_ `FOnBeforeContextResourceLoadDelegate OnBeforeContextResourceLoad;`

#### struct `FCreateBrowserWindowSettings`  
`struct FCreateBrowserWindowSettings`  
_L57-74_
- L59 _public member_ `void* OSWindowHandle = nullptr;`
- L60 _public member_ `FString InitialURL;`
- L61 _public member_ `FColor BackgroundColor = FColor(255, 255, 255, 255);`
- L62 _public member_ `int BrowserFrameRate = 24;`
- L63 _public member_ `bool bUseTransparency = false;`
- L64 _public member_ `bool bInterceptLoadRequests = true;`
- L65 _public member_ `bool bThumbMouseButtonNavigation = false;`
- L66 _public member_ `bool bShowErrorMessage = true;`
- L67 _public member_ `bool bMobileJSReturnInDict = true;`
- L69 _public member_ `bool bEnablePaymentRequest = false;` — Whether to enable the W3C PaymentRequest API in this WebView.
- L70 _public member_ `TOptional<FBrowserContextSettings> Context;`
- L71 _public member_ `TOptional<FString> ContentsToLoad;`
- L72 _public member_ `TOptional<FString> UserAgentApplication;`
- L73 _public member_ `TArray<FString> AltRetryDomains;`

#### class `IWebBrowserSingleton`  
`class IWebBrowserSingleton`  
_L79-197_
- desc: A singleton class that takes care of general web browser tasks
- L85 _public prototype_ `virtual ~IWebBrowserSingleton() = default;` — Virtual Destructor
- L88 _public prototype_ `virtual bool IsShuttingDown() const = 0;` — Indicates whether the browser engine is in the shutdown phase.
- L91 _public prototype_ `virtual TSharedRef<IWebBrowserWindowFactory> GetWebBrowserWindowFactory() const = 0;` — @return A factory object that can be used to construct additional WebBrowserWindows on demand.
- L101 _public prototype_ `virtual TSharedPtr<IWebBrowserWindow> CreateBrowserWindow( TSharedPtr<FCEFWebBrowserWindow>& BrowserWindowParent, TSharedPtr<FWebBrowserWindowInfo>& BrowserWindowInfo ) = 0;` — Create a new web browser window @param BrowserWindowParent The parent browser window @param BrowserWindowInfo Info for setting up the new browser window @return New Web Browser Window Interface (may be null if not supported)
- L112 _public prototype_ `virtual TSharedPtr<IWebBrowserWindow> CreateBrowserWindow(const FCreateBrowserWindowSettings& Settings) = 0;` — Create a new web browser window @param Settings Struct containing browser window settings @return New Web Browser Window Interface (may be null if not supported)
- L115 _public prototype_ `virtual TSharedPtr<IWebBrowserWindow> CreateNativeBrowserProxy() = 0;`
- L118 _public prototype_ `virtual TSharedPtr<class IWebBrowserCookieManager> GetCookieManager() const = 0;`
- L120 _public prototype_ `virtual TSharedPtr<class IWebBrowserCookieManager> GetCookieManager(TOptional<FString> ContextId) const = 0;`
- L122 _public prototype_ `virtual bool RegisterContext(const FBrowserContextSettings& Settings) = 0;`
- L124 _public prototype_ `virtual bool UnregisterContext(const FString& ContextId) = 0;`
- L127 _public prototype_ `virtual FString ApplicationCacheDir() const = 0;` — @return the application cache dir where the cookies are stored
- L135 _public prototype_ `virtual bool RegisterSchemeHandlerFactory(FString Scheme, FString Domain, IWebBrowserSchemeHandlerFactory* WebBrowserSchemeHandlerFactory) = 0;` — Registers a custom scheme handler factory, for a given scheme and domain. The domain is ignored if the scheme is not a browser built in scheme and all requests will go through this factory. @param Scheme                            The scheme name to handle. @param Domain                            The domain name to handle. @param WebBrowserSchemeHandlerFactory    The factory implementation for creating request handlers for this scheme.
- L141 _public prototype_ `virtual bool UnregisterSchemeHandlerFactory(IWebBrowserSchemeHandlerFactory* WebBrowserSchemeHandlerFactory) = 0;` — Unregister a custom scheme handler factory. The factory may still be used by existing open browser windows, but will no longer be provided for new ones. @param WebBrowserSchemeHandlerFactory    The factory implementation to remove.
- L151 _public prototype_ `virtual void SetDevToolsShortcutEnabled(bool Value) = 0;` — Enable or disable CTRL/CMD-SHIFT-I shortcut to show the Chromium Dev tools window. The value defaults to true on debug builds, otherwise false. The relevant handlers for spawning new browser windows have to be set up correctly in addition to this flag being true before anything is shown. @param Value a boolean value to enable or disable the keyboard shortcut.
- L161 _public prototype_ `virtual bool IsDevToolsShortcutEnabled() = 0;` — Returns whether the CTRL/CMD-SHIFT-I shortcut to show the Chromium Dev tools window is enabled. The relevant handlers for spawning new browser windows have to be set up correctly in addition to this flag being true before anything is shown. @return a boolean value indicating whether the keyboard shortcut is enabled or not.
- L175 _public prototype_ `virtual void SetJSBindingToLoweringEnabled(bool bEnabled) = 0;` — Enable or disable to-lowering of JavaScript object member bindings. Due to how JavaScript to UObject bridges require the use of FNames for building up the JS API objects, it is possible for case-sensitivity issues to develop if an FName has been previously created with differing case to your function or property names. To-lowering the member names allows a guaranteed casing for the web page's JS to reference. Default behavior is enabled, so that all JS side objects have only lowercase members. @param bEnabled a boolean value to enable or disable the to-lowering.
- L185 _public prototype_ `virtual void ClearOldCacheFolders(const FString &CachePathRoot, const FString &CachePrefix) = 0;` — Delete old/unused web cache paths. Some Web implementations (i.e CEF) use version specific cache folders, this call lets you schedule a deletion of any now unused folders. Calling this may resulting in async disk I/O. @param CachePathRoot the base path used for saving the webcache folder @param CachePrefix the filename prefix we use for the cache folder (i.e "webcache")
- L189 _public prototype_ `virtual void SetDefaultMaterial(UMaterialInterface* InDefaultMaterial) = 0;` — Set a reference to UWebBrowser's default material
- L191 _public prototype_ `virtual void SetDefaultTranslucentMaterial(UMaterialInterface* InDefaultMaterial) = 0;` — Set a reference to UWebBrowser's translucent material
- L194 _public prototype_ `virtual UMaterialInterface* GetDefaultMaterial() = 0;` — Get a reference to UWebBrowser's default material
- L196 _public prototype_ `virtual UMaterialInterface* GetDefaultTranslucentMaterial() = 0;` — Get a reference to UWebBrowser's transparent material

### `Source/Runtime/WebBrowser/Public/IWebBrowserWindow.h` (Public)


#### enum `EWebBrowserDocumentState`  
`enum class EWebBrowserDocumentState`  
_L18-24_
- L20 _public enumerator_ `Completed`
- L21 _public enumerator_ `Error`
- L22 _public enumerator_ `Loading`
- L23 _public enumerator_ `NoDocument`

#### enum `EWebBrowserConsoleLogSeverity`  
`enum class EWebBrowserConsoleLogSeverity`  
_L26-35_
- L28 _public enumerator_ `Default`
- L29 _public enumerator_ `Verbose`
- L30 _public enumerator_ `Debug`
- L31 _public enumerator_ `Info`
- L32 _public enumerator_ `Warning`
- L33 _public enumerator_ `Error`
- L34 _public enumerator_ `Fatal`

#### enum `EWebTransitionSource`  
`enum class EWebTransitionSource`  
_L38-53_
- L40 _public enumerator_ `Unknown`
- L42 _public enumerator_ `Link` — Source is a link click or the JavaScript window.open function.
- L44 _public enumerator_ `Explicit` — Source is some other "explicit" navigation action such as creating a new browser or using the LoadURL function.
- L46 _public enumerator_ `AutoSubframe` — Source is a subframe navigation.
- L48 _public enumerator_ `ManualSubframe` — Source is a subframe navigation explicitly requested by the user.
- L50 _public enumerator_ `FormSubmit` — Source is a form submission by the user.
- L52 _public enumerator_ `Reload` — Source is a "reload" of the page via the Reload function

#### enum `EWebTransitionSourceQualifier`  
`enum class EWebTransitionSourceQualifier`  
_L55-70_
- L57 _public enumerator_ `Unknown`
- L59 _public enumerator_ `Blocked` — Attempted to visit a URL but was blocked.
- L61 _public enumerator_ `ForwardBack` — Used the Forward or Back function to navigate among browsing history.
- L63 _public enumerator_ `ChainStart` — The beginning of a navigation chain.
- L65 _public enumerator_ `ChainEnd` — The last transition in a redirect chain.
- L67 _public enumerator_ `ClientRedirect` — Redirects caused by JavaScript or a meta refresh tag on the page.
- L69 _public enumerator_ `ServerRedirect` — Used to test whether a transition involves a redirect.

#### struct `FWebNavigationRequest`  
`struct FWebNavigationRequest`  
_L73-80_
- L75 _public member_ `bool bIsRedirect;`
- L76 _public member_ `bool bIsMainFrame;`
- L77 _public member_ `bool bIsExplicitTransition;`
- L78 _public member_ `EWebTransitionSource TransitionSource;`
- L79 _public member_ `EWebTransitionSourceQualifier TransitionSourceQualifier;`

#### class `IWebBrowserWindow`  
`class IWebBrowserWindow`  
_L85-527_
- desc: Interface for dealing with a Web Browser window
- L94 _public prototype_ `virtual void LoadURL(FString NewURL) = 0;` — Load the specified URL @param NewURL New URL to load
- L102 _public prototype_ `virtual void LoadString(FString Contents, FString DummyURL) = 0;` — Load a string as data to create a web page @param Contents String to load @param DummyURL Dummy URL for the page
- L109 _public prototype_ `virtual void SetViewportSize(FIntPoint WindowSize, FIntPoint WindowPos = FIntPoint::NoneValue) = 0;` — Set the desired size of the web browser viewport @param WindowSize Desired viewport size
- L116 _public prototype_ `virtual FIntPoint GetViewportSize() const = 0;` — Gets the current size of the web browser viewport if available, FIntPoint::NoneValue otherwise @param WindowSize Desired viewport size
- L124 _public prototype_ `virtual FSlateShaderResource* GetTexture(bool bIsPopup = false) = 0;` — Gets interface to the texture representation of the browser @param bISpopup Whether to return the popup menu texture instead of the main browser window. @return A slate shader resource that can be rendered
- L129 _public prototype_ `virtual bool IsValid() const = 0;` — Checks whether the web browser is valid and ready for use
- L134 _public prototype_ `virtual bool IsInitialized() const = 0;` — Checks whether the web browser has finished loaded the initial page.
- L139 _public prototype_ `virtual bool IsClosing() const = 0;` — Checks whether the web browser is currently being shut down
- L142 _public prototype_ `virtual EWebBrowserDocumentState GetDocumentLoadingState() const = 0;` — Gets the loading state of the current document.
- L147 _public prototype_ `virtual FString GetTitle() const = 0;` — Gets the current title of the Browser page
- L154 _public prototype_ `virtual FString GetUrl() const = 0;` — Gets the currently loaded URL. @return The URL, or empty string if no document is loaded.
- L163 _public prototype_ `virtual void GetSource(TFunction<void (const FString&)> Callback) const = 0;` — Gets the source of the main frame as raw HTML. This method has to be called asynchronously by passing a callback function, which will be called at a later point when the result is ready. @param	Callback	A callable that takes a single string reference for handling the result.
- L170 _public prototype_ `virtual bool OnKeyDown(const FKeyEvent& InKeyEvent) = 0;` — Notify the browser that a key has been pressed @param  InKeyEvent  Key event
- L177 _public prototype_ `virtual bool OnKeyUp(const FKeyEvent& InKeyEvent) = 0;` — Notify the browser that a key has been released @param  InKeyEvent  Key event
- L184 _public prototype_ `virtual bool OnKeyChar(const FCharacterEvent& InCharacterEvent) = 0;` — Notify the browser of a character event @param InCharacterEvent Character event
- L195 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;` — Notify the browser that a mouse button was pressed within it @param MyGeometry The Geometry of the browser @param MouseEvent Information about the input event @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false. @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
- L206 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;` — Notify the browser that a mouse button was released within it @param MyGeometry The Geometry of the browser @param MouseEvent Information about the input event @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false. @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
- L217 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;` — Notify the browser of a double click event @param MyGeometry The Geometry of the browser @param MouseEvent Information about the input event @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false. @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
- L228 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;` — Notify the browser that a mouse moved within it @param MyGeometry The Geometry of the browser @param MouseEvent Information about the input event @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false. @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
- L235 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) = 0;` — Notify the browser that a mouse has left the window @param MouseEvent Information about the input event
- L240 _public prototype_ `virtual void SetSupportsMouseWheel(bool bValue) = 0;` — Sets whether mouse wheel events should be handled by the window
- L245 _public prototype_ `virtual bool GetSupportsMouseWheel() const = 0;` — Returns whether mouse wheel events should be handled by the window
- L256 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bIsPopup) = 0;` — Called when the mouse wheel is spun @param MyGeometry The Geometry of the browser @param MouseEvent Information about the input event @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false. @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
- L267 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent, bool bIsPopup) = 0;` — Called when a touch gesture is performed. @param MyGeometry The Geometry of the browser @param GestureEvent Information about the input event @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false. @return FReply::Handled() if the mouse event was handled, FReply::Unhandled() oterwise
- L274 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) = 0;` — The system asks each widget under the mouse to provide a cursor. This event is bubbled. @return FCursorReply::Unhandled() if the event is not handled; return FCursorReply::Cursor() otherwise.
- L281 _public prototype_ `virtual void OnFocus(bool SetFocus, bool bIsPopup) = 0;` — Called when browser receives/loses focus @param SetFocus Whether the window gained or lost focus. @param bIsPopup True if the coordinates are relative to a popup menu window, otherwise false.
- L284 _public prototype_ `virtual void OnCaptureLost() = 0;` — Called when Capture lost
- L292 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) = 0;` — Notify the browser that a drag operation has entered the window. @param MyGeometry The Geometry of the browser @param DragDropEvent Information about the drag event
- L301 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) = 0;` — Notify the browser that a drag operation is moving over the window. @param MyGeometry The Geometry of the browser @param DragDropEvent Information about the drag event @return FReply indicating how the event was handled
- L308 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) = 0;` — Notify the browser that a drag operation has left the window. @param DragDropEvent Information about the drag event
- L317 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) = 0;` — Notify the browser that a drag operation has been released on it. @param MyGeometry The Geometry of the browser @param DragDropEvent Information about the drag event @return FReply indicating how the event was handled
- L322 _public prototype_ `virtual bool CanGoBack() const = 0;` — Returns true if the browser can navigate backwards.
- L325 _public prototype_ `virtual void GoBack() = 0;` — Navigate backwards.
- L330 _public prototype_ `virtual bool CanGoForward() const = 0;` — Returns true if the browser can navigate forwards.
- L333 _public prototype_ `virtual void GoForward() = 0;` — Navigate forwards.
- L338 _public prototype_ `virtual bool IsLoading() const = 0;` — Returns true if the browser is currently loading.
- L341 _public prototype_ `virtual void Reload() = 0;` — Reload the current page.
- L344 _public prototype_ `virtual void StopLoad() = 0;` — Stop loading the page.
- L347 _public prototype_ `virtual void ExecuteJavascript(const FString& Script) = 0;` — Execute Javascript on the page.
- L355 _public prototype_ `virtual void CloseBrowser(bool bForce, bool bBlockTillClosed = false) = 0;` — Close this window so that it can no longer be used. @param bForce Designates whether the web browser close should be forced. @param bBlockTillClosed Don't return until this browser object is fully closed.
- L366 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) = 0;` — Expose a UObject instance to the browser runtime. Properties and Functions will be accessible from JavaScript side. As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects. @param Name The name of the object. The object will show up as window.ue.{Name} on the javascript side. If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed. @param Object The object instance. @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
- L375 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) = 0;` — Remove an existing script binding registered by BindUObject. @param Name The name of the object to remove. @param Object The object will only be removed if it is the same object as the one passed in. @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
- L377 _public function_ `virtual void BindInputMethodSystem(ITextInputMethodSystem* TextInputMethodSystem)`
- L379 _public function_ `virtual void UnbindInputMethodSystem()`
- L386 _public prototype_ `virtual int GetLoadError() = 0;` — Get current load error. @return an error code if the last page load resulted in an error, otherwise 0.
- L393 _public prototype_ `virtual void SetIsDisabled(bool bValue) = 0;` — Disable or enable web view. @param bValue Setting this to true will prevent any updates from the background web browser.
- L398 _public prototype_ `virtual TSharedPtr<class SWindow> GetParentWindow() const = 0;` — Get parent SWindow for this window
- L403 _public prototype_ `virtual void SetParentWindow(TSharedPtr<class SWindow> Window) = 0;` — Set parent SWindow for this window
- L408 _public prototype_ `virtual void ShowFloatingCloseButton(bool bShow, bool bDraggable) = 0;` — Shows floating button in the browser if supported by platform
- L410 _public function_ `virtual void CheckTickActivity()`
- L415 _public prototype_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnDocumentStateChanged, EWebBrowserDocumentState );` — A delegate that is invoked when the loading state of a document changed.
- L416 _public prototype_ `virtual FOnDocumentStateChanged& OnDocumentStateChanged() = 0;`
- L419 _public prototype_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnTitleChanged, FString );` — A delegate to allow callbacks when a browser title changes.
- L420 _public prototype_ `virtual FOnTitleChanged& OnTitleChanged() = 0;`
- L423 _public prototype_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnUrlChanged, FString );` — A delegate to allow callbacks when a frame url changes.
- L424 _public prototype_ `virtual FOnUrlChanged& OnUrlChanged() = 0;`
- L427 _public prototype_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnToolTip, FString );` — A delegate to allow callbacks when a frame url changes.
- L428 _public prototype_ `virtual FOnToolTip& OnToolTip() = 0;`
- L431 _public prototype_ `DECLARE_EVENT(IWebBrowserWindow, FOnNeedsRedraw) virtual FOnNeedsRedraw& OnNeedsRedraw() = 0;` — A delegate that is invoked when the off-screen window has been repainted and requires an update.
- L435 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString& , const FWebNavigationRequest& ) virtual FOnBeforeBrowse& OnBeforeBrowse() = 0;` — A delegate that is invoked prior to browser navigation.
- L439 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) virtual FOnLoadUrl& OnLoadUrl() = 0;` — A delegate that is invoked to allow user code to override the contents of a Url.
- L443 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopupDelegate, FString, FString);` — A delegate that is invoked when a popup window is attempting to open.
- L444 _public prototype_ `virtual FOnBeforePopupDelegate& OnBeforePopup() = 0;`
- L447 _public typedef_ `typedef TMap<FString, FString> FRequestHeaders;` — A delegate that is invoked before the browser loads a resource. Its primary purpose is to inject headers into the request.
- L448 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnBeforeResourceLoadDelegate, FString , FString , FRequestHeaders& , const bool );`
- L449 _public prototype_ `virtual FOnBeforeResourceLoadDelegate& OnBeforeResourceLoad() = 0;`
- L452 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnResourceLoadCompleteDelegate, FString , FString , FString , int64 );` — A delegate that is invoked on completion of browser resource loads. Its primary purpose is to allow response to failures.
- L453 _public prototype_ `virtual FOnResourceLoadCompleteDelegate& OnResourceLoadComplete() = 0;`
- L456 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnConsoleMessageDelegate, const FString& , const FString& , int32 , EWebBrowserConsoleLogSeverity );` — A delegate that is invoked for each console message
- L457 _public prototype_ `virtual FOnConsoleMessageDelegate& OnConsoleMessage() = 0;`
- L460 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCreateWindow, const TWeakPtr<IWebBrowserWindow>& , const TWeakPtr<IWebBrowserPopupFeatures>& ) virtual FOnCreateWindow& OnCreateWindow() = 0;` — A delegate that is invoked when an existing browser requests creation of a new browser window.
- L464 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCloseWindow, const TWeakPtr<IWebBrowserWindow>& ) virtual FOnCloseWindow& OnCloseWindow() = 0;` — A delegate that is invoked when closing created popup windows.
- L468 _public prototype_ `DECLARE_DELEGATE(FOnFloatingCloseButtonPressed) virtual FOnFloatingCloseButtonPressed& OnFloatingCloseButtonPressed() = 0;` — A delegate that is invoked when close is requested from the floating close button.
- L472 _public prototype_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnShowPopup, const FIntRect& ) virtual FOnShowPopup& OnShowPopup() = 0;` — A delegate that is invoked when the browser needs to show a popup menu.
- L476 _public prototype_ `DECLARE_EVENT(IWebBrowserWindow, FOnDismissPopup) virtual FOnDismissPopup& OnDismissPopup() = 0;` — A delegate that is invoked when the browser no longer wants to show the popup menu.
- L480 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>& ) virtual FOnShowDialog& OnShowDialog() = 0;` — A delegate that is invoked when the browser needs to show a dialog.
- L484 _public prototype_ `DECLARE_DELEGATE(FOnDismissAllDialogs) virtual FOnDismissAllDialogs& OnDismissAllDialogs() = 0;` — A delegate that is invoked when the browser needs to dismiss and reset all dialogs.
- L488 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnSuppressContextMenu);` — Should return true if this dialog wants to suppress the context menu
- L489 _public prototype_ `virtual FOnSuppressContextMenu& OnSuppressContextMenu() = 0;`
- L492 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyDown, const FKeyEvent& );` — A delegate that is invoked for each key down event not handled by the browser, return true if event is handled to prevent it from bubbling up.
- L493 _public prototype_ `virtual FOnUnhandledKeyDown& OnUnhandledKeyDown() = 0;`
- L496 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyUp, const FKeyEvent& );` — A delegate that is invoked for each up down event not handled by the browser, return true if event is handled to prevent it from bubbling up.
- L497 _public prototype_ `virtual FOnUnhandledKeyUp& OnUnhandledKeyUp() = 0;`
- L500 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyChar, const FCharacterEvent& );` — A delegate that is invoked for each key char event not handled by the browser, return true if event is handled to prevent it from bubbling up.
- L501 _public prototype_ `virtual FOnUnhandledKeyChar& OnUnhandledKeyChar() = 0;`
- L503 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragWindow, const FPointerEvent& ) virtual FOnDragWindow& OnDragWindow() = 0;` — A delegate that is invoked when drag is detected in an area specified as a drag region on the web page.
- L507 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnCheckVisibility);` — A delegate that is invoked to check the visibility of the native browser
- L508 _public function_ `virtual FOnCheckVisibility& OnCheckVisibility()`
- L513 _public function_ `virtual bool CheckVisibility()`
- L521 _protected prototype_ `virtual ~IWebBrowserWindow() = default;` — Virtual Destructor.
- L525 _private member_ `FOnCheckVisibility OnCheckVisibilityDelegate;` — Delegate for veritying the window's visibility

#### Free symbols / members of external scopes

- L415 _delegate_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnDocumentStateChanged, EWebBrowserDocumentState );` — A delegate that is invoked when the loading state of a document changed.
- L419 _delegate_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnTitleChanged, FString );` — A delegate to allow callbacks when a browser title changes.
- L423 _delegate_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnUrlChanged, FString );` — A delegate to allow callbacks when a frame url changes.
- L427 _delegate_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnToolTip, FString );` — A delegate to allow callbacks when a frame url changes.
- L431 _delegate_ `DECLARE_EVENT(IWebBrowserWindow, FOnNeedsRedraw) virtual FOnNeedsRedraw& OnNeedsRedraw() = 0;` — A delegate that is invoked when the off-screen window has been repainted and requires an update.
- L435 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString& , const FWebNavigationRequest& ) virtual FOnBeforeBrowse& OnBeforeBrowse() = 0;` — A delegate that is invoked prior to browser navigation.
- L439 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) virtual FOnLoadUrl& OnLoadUrl() = 0;` — A delegate that is invoked to allow user code to override the contents of a Url.
- L443 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopupDelegate, FString, FString);` — A delegate that is invoked when a popup window is attempting to open.
- L448 _delegate_ `DECLARE_DELEGATE_FourParams(FOnBeforeResourceLoadDelegate, FString , FString , FRequestHeaders& , const bool );`
- L452 _delegate_ `DECLARE_DELEGATE_FourParams(FOnResourceLoadCompleteDelegate, FString , FString , FString , int64 );` — A delegate that is invoked on completion of browser resource loads. Its primary purpose is to allow response to failures.
- L456 _delegate_ `DECLARE_DELEGATE_FourParams(FOnConsoleMessageDelegate, const FString& , const FString& , int32 , EWebBrowserConsoleLogSeverity );` — A delegate that is invoked for each console message
- L460 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCreateWindow, const TWeakPtr<IWebBrowserWindow>& , const TWeakPtr<IWebBrowserPopupFeatures>& ) virtual FOnCreateWindow& OnCreateWindow() = 0;` — A delegate that is invoked when an existing browser requests creation of a new browser window.
- L464 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCloseWindow, const TWeakPtr<IWebBrowserWindow>& ) virtual FOnCloseWindow& OnCloseWindow() = 0;` — A delegate that is invoked when closing created popup windows.
- L468 _delegate_ `DECLARE_DELEGATE(FOnFloatingCloseButtonPressed) virtual FOnFloatingCloseButtonPressed& OnFloatingCloseButtonPressed() = 0;` — A delegate that is invoked when close is requested from the floating close button.
- L472 _delegate_ `DECLARE_EVENT_OneParam(IWebBrowserWindow, FOnShowPopup, const FIntRect& ) virtual FOnShowPopup& OnShowPopup() = 0;` — A delegate that is invoked when the browser needs to show a popup menu.
- L476 _delegate_ `DECLARE_EVENT(IWebBrowserWindow, FOnDismissPopup) virtual FOnDismissPopup& OnDismissPopup() = 0;` — A delegate that is invoked when the browser no longer wants to show the popup menu.
- L480 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>& ) virtual FOnShowDialog& OnShowDialog() = 0;` — A delegate that is invoked when the browser needs to show a dialog.
- L484 _delegate_ `DECLARE_DELEGATE(FOnDismissAllDialogs) virtual FOnDismissAllDialogs& OnDismissAllDialogs() = 0;` — A delegate that is invoked when the browser needs to dismiss and reset all dialogs.
- L488 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnSuppressContextMenu);` — Should return true if this dialog wants to suppress the context menu
- L492 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyDown, const FKeyEvent& );` — A delegate that is invoked for each key down event not handled by the browser, return true if event is handled to prevent it from bubbling up.
- L496 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyUp, const FKeyEvent& );` — A delegate that is invoked for each up down event not handled by the browser, return true if event is handled to prevent it from bubbling up.
- L500 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyChar, const FCharacterEvent& );` — A delegate that is invoked for each key char event not handled by the browser, return true if event is handled to prevent it from bubbling up.
- L503 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragWindow, const FPointerEvent& ) virtual FOnDragWindow& OnDragWindow() = 0;` — A delegate that is invoked when drag is detected in an area specified as a drag region on the web page.
- L507 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnCheckVisibility);` — A delegate that is invoked to check the visibility of the native browser

### `Source/Runtime/WebBrowser/Public/SWebBrowser.h` (Public)


#### class `SWebBrowser`  
`class SWebBrowser : public SCompoundWidget`  
_L21-340_
- inherits: `SCompoundWidget`
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString&, const FWebNavigationRequest& ) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragWindow, const FPointerEvent& );`
- L30 _public function_ `SLATE_BEGIN_ARGS(SWebBrowser) : _InitialURL(TEXT("https:`
- L46 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(FString, InitialURL) SLATE_ARGUMENT(TOptional<FString>, ContentsToLoad) SLATE_ARGUMENT(TOptional<FString>, UserAgentApplication) SLATE_ARGUMENT(bool, ShowControls) SLATE_ARGUMENT(bool, ShowAddressBar) SLATE_ARGUMENT(bool, ShowErrorMessage) SLATE_ARGUMENT(bool, SupportsTransparency) SLATE_ARGUMENT(bool, SupportsThumbMouseButtonNavigation) SLATE_ARGUMENT(bool, ShowInitialThrobber) SLATE_ARGUMENT(FColor, BackgroundColor) SLATE_ARGUMENT(int , BrowserFrameRate) SLATE_ARGUMENT(TOptional<EPopupMethod>, PopupMenuMethod) SLATE_ARGUMENT(bool, UseSmoothResizing);` — A reference to the parent window.
- L88 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, ViewportSize);` — Desired size of the web browser viewport.
- L91 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnLoadCompleted) SLATE_EVENT(FSimpleDelegate, OnLoadError) SLATE_EVENT(FSimpleDelegate, OnLoadStarted) SLATE_EVENT(FOnTextChanged, OnTitleChanged) SLATE_EVENT(FOnTextChanged, OnUrlChanged) SLATE_EVENT(FOnBeforePopupDelegate, OnBeforePopup) SLATE_EVENT(FOnCreateWindowDelegate, OnCreateWindow) SLATE_EVENT(FOnCloseWindowDelegate, OnCloseWindow) SLATE_EVENT(FOnBeforeBrowse, OnBeforeNavigation) SLATE_EVENT(FOnLoadUrl, OnLoadUrl) SLATE_EVENT(FOnShowDialog, OnShowDialog) SLATE_EVENT(FSimpleDelegate, OnDismissAllDialogs) SLATE_EVENT(FOnSuppressContextMenu, OnSuppressContextMenu);` — Called when document loading completed.
- L129 _public prototype_ `SLATE_EVENT(FOnDragWindow, OnDragWindow);` — Called when drag is detected in a web page area tagged as a drag region.
- L132 _public prototype_ `SLATE_EVENT(FOnConsoleMessageDelegate, OnConsoleMessage);` — Called for each console message
- L138 _public prototype_ `SWebBrowser();` — Default constructor.
- L140 _public prototype_ `~SWebBrowser();`
- L142 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L143 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L145 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L152 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<IWebBrowserWindow>& InWebBrowserWindow = nullptr);` — Construct the widget. @param InArgs  Declaration from which to construct the widget.
- L159 _public prototype_ `void LoadURL(FString NewURL);` — Load the specified URL. @param NewURL New URL to load.
- L167 _public prototype_ `void LoadString(FString Contents, FString DummyURL);` — Load a string as data to create a web page. @param Contents String to load. @param DummyURL Dummy URL for the page.
- L170 _public prototype_ `void Reload();` — Reload the current page.
- L173 _public prototype_ `void StopLoad();` — Stop loading the page.
- L176 _public prototype_ `FText GetTitleText() const;` — Get the current title of the web page.
- L183 _public prototype_ `FString GetUrl() const;` — Gets the currently loaded URL. @return The URL, or empty string if no document is loaded.
- L190 _public prototype_ `FText GetAddressBarUrlText() const;` — Gets the URL that appears in the address bar, this may not be the URL that is currently loaded in the frame. @return The address bar URL.
- L193 _public prototype_ `bool IsLoaded() const;` — Whether the document finished loading.
- L196 _public prototype_ `bool IsLoading() const;` — Whether the document is currently being loaded.
- L199 _public prototype_ `void ExecuteJavascript(const FString& ScriptText);` — Execute javascript on the current window
- L208 _public prototype_ `void GetSource(TFunction<void (const FString&)> Callback) const;` — Gets the source of the main frame as raw HTML. This method has to be called asynchronously by passing a callback function, which will be called at a later point when the result is ready. @param	Callback	A callable that takes a single string reference for handling the result.
- L219 _public prototype_ `void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true);` — Expose a UObject instance to the browser runtime. Properties and Functions will be accessible from JavaScript side. As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects. @param Name The name of the object. The object will show up as window.ue.{Name} on the javascript side. Note: All object names, function names, and property names will be converted to lower case when bound on the javascript side.  If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed. @param Object The object instance. @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
- L228 _public prototype_ `void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true);` — Remove an existing script binding registered by BindUObject. @param Name The name of the object to remove. @param Object The object will only be removed if it is the same object as the one passed in. @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
- L230 _public prototype_ `void BindAdapter(const TSharedRef<IWebBrowserAdapter>& Adapter);`
- L232 _public prototype_ `void UnbindAdapter(const TSharedRef<IWebBrowserAdapter>& Adapter);`
- L234 _public prototype_ `void BindInputMethodSystem(ITextInputMethodSystem* TextInputMethodSystem);`
- L236 _public prototype_ `void UnbindInputMethodSystem();`
- L239 _public prototype_ `bool CanGoBack() const;` — Returns true if the browser can navigate backwards.
- L242 _public prototype_ `void GoBack();` — Navigate backwards.
- L245 _public prototype_ `bool CanGoForward() const;` — Returns true if the browser can navigate forwards.
- L248 _public prototype_ `void GoForward();` — Navigate forwards.
- L251 _public prototype_ `void SetParentWindow(TSharedPtr<SWindow> Window);` — Set parent SWindow for this browser.
- L254 _public prototype_ `void ShowThrobber();` — Show the throbber and hide the web browser content.
- L257 _public prototype_ `void HideThrobber();` — Hide the throbber and show the web browser content.
- L262 _private prototype_ `FReply OnBackClicked();` — Navigate backwards.
- L265 _private prototype_ `FReply OnForwardClicked();` — Navigate forwards.
- L268 _private prototype_ `FText GetReloadButtonText() const;` — Get text for reload button depending on status
- L271 _private prototype_ `FReply OnReloadClicked();` — Reload or stop loading
- L274 _private prototype_ `void OnUrlTextCommitted( const FText& NewText, ETextCommit::Type CommitType );` — Invoked whenever text is committed in the address bar.
- L277 _private prototype_ `EVisibility GetViewportVisibility() const;` — Get whether the page viewport should be visible
- L280 _private prototype_ `EVisibility GetLoadingThrobberVisibility() const;` — Get whether loading throbber should be visible
- L285 _private member_ `TSharedPtr<SWebBrowserView> BrowserView;` — The actual web browser view
- L288 _private member_ `TSharedPtr< SEditableTextBox > InputText;` — Editable text widget used for an address bar
- L291 _private member_ `FSimpleDelegate OnLoadCompleted;` — A delegate that is invoked when document loading completed.
- L294 _private member_ `FSimpleDelegate OnLoadError;` — A delegate that is invoked when document loading failed.
- L297 _private member_ `FSimpleDelegate OnLoadStarted;` — A delegate that is invoked when document loading started.
- L300 _private member_ `FOnTextChanged OnTitleChanged;` — A delegate that is invoked when document title changed.
- L303 _private member_ `FOnTextChanged OnUrlChanged;` — A delegate that is invoked when document address changed.
- L306 _private member_ `FOnBeforePopupDelegate OnBeforePopup;` — A delegate that is invoked when the browser attempts to pop up a new window
- L309 _private member_ `FOnConsoleMessageDelegate OnConsoleMessage;` — A delegate that is invoked when the browser writes console output
- L312 _private member_ `FOnCreateWindowDelegate OnCreateWindow;` — A delegate that is invoked when the browser requests a UI window for another browser it spawned
- L315 _private member_ `FOnCloseWindowDelegate OnCloseWindow;` — A delegate that is invoked when a window close event is detected
- L318 _private member_ `FOnBeforeBrowse OnBeforeNavigation;` — A delegate that is invoked prior to browser navigation
- L321 _private member_ `FOnLoadUrl OnLoadUrl;` — A delegate that is invoked when loading a resource, allowing the application to provide contents directly
- L324 _private member_ `FOnShowDialog OnShowDialog;` — A delegate that is invoked when when the browser needs to present a dialog to the user
- L327 _private member_ `FSimpleDelegate OnDismissAllDialogs;` — A delegate that is invoked when when the browser needs to dismiss all dialogs
- L330 _private member_ `bool bShowInitialThrobber;` — The initial throbber setting
- L333 _private member_ `bool bForceThrobber = false;` — Whether to force the throbber to appear
- L336 _private member_ `TSharedPtr<IWebBrowserWindow> WebBrowserWindow;` — The WebBrowserWindow itself.
- L339 _private member_ `FDelegateHandle InputMethodSystemSlatePreShutdownDelegateHandle;` — Pre-shutdown delegate handle, to unbind the Input Method System.

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnSuppressContextMenu);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnSuppressContextMenu);`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString&, const FWebNavigationRequest& ) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragWindow, const FPointerEvent& );`

### `Source/Runtime/WebBrowser/Public/SWebBrowserView.h` (Public)


#### class `SWebBrowserView`  
`class SWebBrowserView : public SCompoundWidget`  
_L38-483_
- inherits: `SCompoundWidget`
- L42 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString& , const FWebNavigationRequest& ) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L45 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnSuppressContextMenu);`
- L46 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragWindow, const FPointerEvent& );`
- L47 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyDown, const FKeyEvent& );`
- L48 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyUp, const FKeyEvent& );`
- L49 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyChar, const FCharacterEvent& );`
- L52 _public function_ `SLATE_BEGIN_ARGS(SWebBrowserView) : _InitialURL(TEXT("https:`
- L68 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(FString, InitialURL) SLATE_ARGUMENT(TOptional<FString>, ContentsToLoad) SLATE_ARGUMENT(TOptional<FString>, UserAgentApplication) SLATE_ARGUMENT(bool, ShowErrorMessage) SLATE_ARGUMENT(bool, SupportsTransparency) SLATE_ARGUMENT(bool, InterceptLoadRequests) SLATE_ARGUMENT(bool, SupportsThumbMouseButtonNavigation) SLATE_ARGUMENT(FColor, BackgroundColor) SLATE_ARGUMENT(int, BrowserFrameRate) SLATE_ARGUMENT(TOptional<EPopupMethod>, PopupMenuMethod) SLATE_ARGUMENT(TOptional<FBrowserContextSettings>, ContextSettings) SLATE_ARGUMENT(TArray<FString>, AltRetryDomains) SLATE_ARGUMENT(bool, EnablePaymentRequest)` — A reference to the parent window.
- L113 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnLoadCompleted) SLATE_EVENT(FSimpleDelegate, OnLoadError) SLATE_EVENT(FSimpleDelegate, OnLoadStarted) SLATE_EVENT(FOnTextChanged, OnTitleChanged) SLATE_EVENT(FOnTextChanged, OnUrlChanged) SLATE_EVENT(FOnBeforePopupDelegate, OnBeforePopup) SLATE_EVENT(FOnCreateWindowDelegate, OnCreateWindow) SLATE_EVENT(FOnCloseWindowDelegate, OnCloseWindow) SLATE_EVENT(FOnFloatingCloseButtonPressedDelegate, OnFloatingCloseButtonPressed) SLATE_EVENT(FOnBeforeBrowse, OnBeforeNavigation) SLATE_EVENT(FOnLoadUrl, OnLoadUrl) SLATE_EVENT(FOnShowDialog, OnShowDialog) SLATE_EVENT(FSimpleDelegate, OnDismissAllDialogs) SLATE_EVENT(FOnSuppressContextMenu, OnSuppressContextMenu);` — Called when document loading completed.
- L155 _public prototype_ `SLATE_EVENT(FOnCreateToolTip, OnCreateToolTip) SLATE_EVENT(FOnDragWindow, OnDragWindow) SLATE_EVENT(FOnUnhandledKeyDown, OnUnhandledKeyDown) SLATE_EVENT(FOnUnhandledKeyUp, OnUnhandledKeyUp) SLATE_EVENT(FOnUnhandledKeyChar, OnUnhandledKeyChar) SLATE_EVENT(FOnConsoleMessageDelegate, OnConsoleMessage) SLATE_END_ARGS() SWebBrowserView();` — Called to allow overriding of ToolTip widget construction.
- L178 _public prototype_ `~SWebBrowserView();`
- L180 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L182 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L184 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L185 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L186 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L187 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L194 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<IWebBrowserWindow>& InWebBrowserWindow = nullptr);` — Construct the widget. @param InArgs  Declaration from which to construct the widget.
- L196 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L203 _public prototype_ `void LoadURL(FString NewURL);` — Load the specified URL. @param NewURL New URL to load.
- L211 _public prototype_ `void LoadString(FString Contents, FString DummyURL);` — Load a string as data to create a web page. @param Contents String to load. @param DummyURL Dummy URL for the page.
- L214 _public prototype_ `void Reload();` — Reload the current page.
- L217 _public prototype_ `void StopLoad();` — Stop loading the page.
- L220 _public prototype_ `FText GetTitleText() const;` — Get the current title of the web page.
- L227 _public prototype_ `FString GetUrl() const;` — Gets the currently loaded URL. @return The URL, or empty string if no document is loaded.
- L234 _public prototype_ `FText GetAddressBarUrlText() const;` — Gets the URL that appears in the address bar, this may not be the URL that is currently loaded in the frame. @return The address bar URL.
- L237 _public prototype_ `bool IsLoaded() const;` — Whether the document finished loading.
- L240 _public prototype_ `bool IsLoading() const;` — Whether the document is currently being loaded.
- L243 _public prototype_ `bool IsInitialized() const;` — Whether the browser widget is done initializing.
- L246 _public prototype_ `void ExecuteJavascript(const FString& ScriptText);` — Execute javascript on the current window
- L255 _public prototype_ `void GetSource(TFunction<void (const FString&)> Callback) const ;` — Gets the source of the main frame as raw HTML. This method has to be called asynchronously by passing a callback function, which will be called at a later point when the result is ready. @param	Callback	A callable that takes a single string reference for handling the result.
- L266 _public prototype_ `void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true);` — Expose a UObject instance to the browser runtime. Properties and Functions will be accessible from JavaScript side. As all communication with the rendering procesis asynchronous, return values (both for properties and function results) are wrapped into JS Future objects. @param Name The name of the object. The object will show up as window.ue.{Name} on the javascript side. If there is an existing object of the same name, this object will replace it. If bIsPermanent is false and there is an existing permanent binding, the permanent binding will be restored when the temporary one is removed. @param Object The object instance. @param bIsPermanent If true, the object will be visible to all pages loaded through this browser widget, otherwise, it will be deleted when navigating away from the current page. Non-permanent bindings should be registered from inside an OnLoadStarted event handler in order to be available before JS code starts loading.
- L275 _public prototype_ `void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true);` — Remove an existing script binding registered by BindUObject. @param Name The name of the object to remove. @param Object The object will only be removed if it is the same object as the one passed in. @param bIsPermanent Must match the bIsPermanent argument passed to BindUObject.
- L277 _public prototype_ `void BindAdapter(const TSharedRef<IWebBrowserAdapter>& Adapter);`
- L279 _public prototype_ `void UnbindAdapter(const TSharedRef<IWebBrowserAdapter>& Adapter);`
- L281 _public prototype_ `void BindInputMethodSystem(ITextInputMethodSystem* TextInputMethodSystem);`
- L283 _public prototype_ `void UnbindInputMethodSystem();`
- L286 _public prototype_ `bool CanGoBack() const;` — Returns true if the browser can navigate backwards.
- L289 _public prototype_ `void GoBack();` — Navigate backwards.
- L292 _public prototype_ `bool CanGoForward() const;` — Returns true if the browser can navigate forwards.
- L295 _public prototype_ `void GoForward();` — Navigate forwards.
- L298 _public prototype_ `void SetParentWindow(TSharedPtr<SWindow> Window);` — Set parent SWindow for this browser.
- L302 _public prototype_ `void SetBrowserKeyboardFocus();` — Update the underlying browser widget to match the KB focus in slate. This is used to work around a CEF bug that loses focus state on navigations
- L307 _public prototype_ `void CloseBrowser();` — Close the underlying browser object before we destruct this view. This will block until that object is fully destroyed. Calling this is optional, CEF has object lifetime requirements that mean on shutdown you must destroy browsers before exit.
- L310 _public prototype_ `void ShowFloatingCloseButton(bool bShow, bool bDraggable);` — Shows floating close button.
- L313 _public prototype_ `TSharedPtr<IWebBrowserWindow> GetBrowserWindow() const;` — Gets the internal web browser window
- L317 _private prototype_ `void SetupParentWindowHandlers();`
- L320 _private prototype_ `void HandleBrowserWindowDocumentStateChanged(EWebBrowserDocumentState NewState);` — Callback for document loading state changes.
- L323 _private prototype_ `void HandleBrowserWindowNeedsRedraw();` — Callback to tell slate we want to update the contents of the web view based on changes inside the view.
- L326 _private prototype_ `void HandleTitleChanged(FString NewTitle);` — Callback for document title changes.
- L329 _private prototype_ `void HandleUrlChanged(FString NewUrl);` — Callback for loaded url changes.
- L332 _private prototype_ `void HandleToolTip(FString ToolTipText);` — Callback for showing browser tool tips.
- L339 _private prototype_ `bool HandleBeforeNavigation(const FString& Url, const FWebNavigationRequest& Request);` — A delegate that is executed prior to browser navigation. @return true if the navigation was handled an no further action should be taken by the browser, false if the browser should handle.
- L341 _private prototype_ `bool HandleLoadUrl(const FString& Method, const FString& Url, FString& OutResponse);`
- L348 _private prototype_ `bool HandleCreateWindow(const TWeakPtr<IWebBrowserWindow>& NewBrowserWindow, const TWeakPtr<IWebBrowserPopupFeatures>& PopupFeatures);` — A delegate that is executed when the browser requests window creation. @return true if if the window request was handled, false if the browser requesting the new window should be closed.
- L355 _private prototype_ `bool HandleCloseWindow(const TWeakPtr<IWebBrowserWindow>& BrowserWindow);` — A delegate that is executed when closing the browser window. @return true if if the window close was handled, false otherwise.
- L358 _private prototype_ `void HandleFloatingCloseButtonPressed();` — Callback for handling requests from floating close button
- L361 _private prototype_ `EWebBrowserDialogEventResponse HandleShowDialog(const TWeakPtr<IWebBrowserDialog>& DialogParams);` — Callback for showing dialogs to the user
- L364 _private prototype_ `void HandleDismissAllDialogs();` — Callback for dismissing any dialogs previously shown
- L367 _private prototype_ `bool HandleBeforePopup(FString URL, FString Target);` — Callback for popup window permission
- L370 _private prototype_ `void HandleShowPopup(const FIntRect& PopupSize);` — Callback for showing a popup menu
- L373 _private prototype_ `void HandleDismissPopup();` — Callback for hiding the popup menu
- L376 _private prototype_ `void HandleMenuDismissed(TSharedRef<IMenu>);` — Callback from the popup menu notifiying it has been dismissed
- L378 _private function_ `virtual FPopupMethodReply OnQueryPopupMethod() const override`
- L385 _private prototype_ `void HandleWindowDeactivated();`
- L386 _private prototype_ `void HandleWindowActivated();`
- L387 _private prototype_ `bool UnhandledKeyDown(const FKeyEvent& KeyEvent);`
- L388 _private prototype_ `bool UnhandledKeyUp(const FKeyEvent& KeyEvent);`
- L389 _private prototype_ `bool UnhandledKeyChar(const FCharacterEvent& CharacterEvent);`
- L391 _private prototype_ `bool HandleDrag(const FPointerEvent& MouseEvent);`
- L392 _private prototype_ `void HandleConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Serverity);`
- L397 _private member_ `TSharedPtr<IWebBrowserWindow> BrowserWindow;` — Interface for dealing with a web browser window.
- L399 _private member_ `mutable TWeakPtr<SWindow> SlateParentWindowPtr;` — The slate window that contains this widget. This must be stored weak otherwise we create a circular reference.
- L401 _private member_ `TSharedPtr<FWebBrowserViewport> BrowserViewport;` — Viewport interface for rendering the web page.
- L403 _private member_ `TSharedPtr<FWebBrowserViewport> MenuViewport;` — Viewport interface for rendering popup menus.
- L405 _private member_ `TSharedPtr<SWebBrowserWidget> BrowserWidget;` — The implementation dependent widget that renders the browser contents.
- L407 _private member_ `TArray<TSharedRef<IWebBrowserAdapter>> Adapters;`
- L413 _private member_ `TWeakPtr<IMenu> PopupMenuPtr;` — An interface pointer to a menu object presenting a popup. Pointer is null when a popup is not visible.
- L416 _private member_ `TOptional<EPopupMethod> PopupMenuMethod;` — Can be set to override the popup menu method used for popup menus. If not set, parent widgets will be queried instead.
- L419 _private member_ `FText AddressBarUrl;` — The url that appears in the address bar which can differ from the url of the loaded page
- L422 _private member_ `FSimpleDelegate OnLoadCompleted;` — A delegate that is invoked when document loading completed.
- L425 _private member_ `FSimpleDelegate OnLoadError;` — A delegate that is invoked when document loading failed.
- L428 _private member_ `FSimpleDelegate OnLoadStarted;` — A delegate that is invoked when document loading started.
- L431 _private member_ `FOnTextChanged OnTitleChanged;` — A delegate that is invoked when document title changed.
- L434 _private member_ `FOnTextChanged OnUrlChanged;` — A delegate that is invoked when document address changed.
- L437 _private member_ `FOnBeforePopupDelegate OnBeforePopup;` — A delegate that is invoked when the browser attempts to pop up a new window
- L440 _private member_ `FOnCreateWindowDelegate OnCreateWindow;` — A delegate that is invoked when the browser requests a UI window for another browser it spawned
- L443 _private member_ `FOnCloseWindowDelegate OnCloseWindow;` — A delegate that is invoked when a window close event is detected
- L446 _private member_ `FOnFloatingCloseButtonPressedDelegate OnFloatingCloseButtonPressed;` — A delegate that is invoked when the floating close button is pressed
- L449 _private member_ `FOnBeforeBrowse OnBeforeNavigation;` — A delegate that is invoked prior to browser navigation
- L452 _private member_ `FOnLoadUrl OnLoadUrl;` — A delegate that is invoked when loading a resource, allowing the application to provide contents directly
- L455 _private member_ `FOnShowDialog OnShowDialog;` — A delegate that is invoked when when the browser needs to present a dialog to the user
- L458 _private member_ `FSimpleDelegate OnDismissAllDialogs;` — A delegate that is invoked when when the browser needs to dismiss all dialogs
- L460 _private member_ `FOnSuppressContextMenu OnSuppressContextMenu;`
- L463 _private member_ `FOnCreateToolTip OnCreateToolTip;` — A delegate that is invoked when when the browser wishes to create a tooltip
- L466 _private member_ `FOnDragWindow OnDragWindow;` — A delegate that is invoked when the browser detects drag event in within drag region
- L469 _private member_ `FOnUnhandledKeyDown OnUnhandledKeyDown;` — A delegate for handling key down events not handled by browser.
- L472 _private member_ `FOnUnhandledKeyUp OnUnhandledKeyUp;` — A delegate for handling key up events not handled by browser.
- L475 _private member_ `FOnUnhandledKeyChar OnUnhandledKeyChar;` — A delegate for handling key char events not handled by browser.
- L478 _private member_ `FOnConsoleMessageDelegate OnConsoleMessage;` — A delegate that is invoked for each console message
- L481 _protected prototype_ `bool HandleSuppressContextMenu();`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopupDelegate, FString, FString);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforePopupDelegate, FString, FString);`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCreateWindowDelegate, const TWeakPtr<IWebBrowserWindow>&, const TWeakPtr<IWebBrowserPopupFeatures>&);`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCreateWindowDelegate, const TWeakPtr<IWebBrowserWindow>&, const TWeakPtr<IWebBrowserPopupFeatures>&);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCloseWindowDelegate, const TWeakPtr<IWebBrowserWindow>&);`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCloseWindowDelegate, const TWeakPtr<IWebBrowserWindow>&);`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IToolTip>, FOnCreateToolTip, const FText&);`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IToolTip>, FOnCreateToolTip, const FText&);`
- L29 _delegate_ `DECLARE_DELEGATE_FourParams(FOnConsoleMessageDelegate, const FString& , const FString& , int32 , EWebBrowserConsoleLogSeverity );`
- L29 _prototype_ `DECLARE_DELEGATE_FourParams(FOnConsoleMessageDelegate, const FString& , const FString& , int32 , EWebBrowserConsoleLogSeverity );`
- L30 _delegate_ `DECLARE_DELEGATE(FOnFloatingCloseButtonPressedDelegate);`
- L30 _prototype_ `DECLARE_DELEGATE(FOnFloatingCloseButtonPressedDelegate);`
- L33 _typedef_ `typedef SViewport SWebBrowserWidget;`
- L35 _typedef_ `typedef SWidget SWebBrowserWidget;`
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString& , const FWebNavigationRequest& ) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString& , const FString& , FString& ) DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EWebBrowserDialogEventResponse, FOnShowDialog, const TWeakPtr<IWebBrowserDialog>&);`
- L45 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnSuppressContextMenu);`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDragWindow, const FPointerEvent& );`
- L47 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyDown, const FKeyEvent& );`
- L48 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyUp, const FKeyEvent& );`
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnhandledKeyChar, const FCharacterEvent& );`

### `Source/Runtime/WebBrowser/Public/WebBrowserModule.h` (Public)


#### struct `FWebBrowserInitSettings`  
`struct FWebBrowserInitSettings`  
_L14-24_
- desc: WebBrowser initialization settings, can be used to override default init behaviors.
- L20 _public prototype_ `FWebBrowserInitSettings();` — Default constructor. Initializes all members with default behavior values.
- L23 _public member_ `FString ProductVersion;` — The string which is appended to the browser's user-agent value.

#### class `IWebBrowserModule`  
`class IWebBrowserModule : public IModuleInterface`  
_L29-84_
- inherits: `IModuleInterface`
- desc: WebBrowserModule interface
- L37 _public function_ `static inline IWebBrowserModule& Get()` — Get or load the Web Browser Module @return The loaded module
- L47 _public function_ `static inline bool IsAvailable()` — Check whether the module has already been loaded @return True if the module is loaded
- L60 _public prototype_ `static FString MakeUserAgentApplication(const FString& ApplicationName, const FString& ApplicationVersion = FString());` — Returns a string suitable for use as the application (or product) part of a browser's user agent string. Includes the formatted application/product name and version, followed by the engine name and version. @param ApplicationName the application/product name @param ApplicationVersion the application/product version, will default to 1.0 if empty @return The user agent application string
- L68 _public prototype_ `virtual bool CustomInitialize(const FWebBrowserInitSettings& WebBrowserInitSettings) = 0;` — Customize initialization settings. You must call this before the first GetSingleton call, in order to override init settings. @param WebBrowserInitSettings The custom settings. @return true if the settings were used to initialize the singleton. False if the call was ignored due to singleton already existing.
- L75 _public prototype_ `virtual IWebBrowserSingleton* GetSingleton() = 0;` — Get the Web Browser Singleton @return The Web Browser Singleton
- L83 _public prototype_ `virtual bool IsWebModuleAvailable() const = 0;` — Check whether the web module loaded its requirements successfully @return True if the module load worked

### `Source/Runtime/WebBrowser/Public/WebBrowserViewport.h` (Public)


#### class `FWebBrowserViewport`  
`class FWebBrowserViewport : public ISlateViewport`  
_L16-61_
- inherits: `ISlateViewport`
- desc: A Slate viewport to display a Web Browser Window
- L26 _public function_ `FWebBrowserViewport(TSharedPtr<IWebBrowserWindow> InWebBrowserWindow, bool InIsPopup = false) : WebBrowserWindow(InWebBrowserWindow) , bIsPopup(InIsPopup)` — Default Constructor @param InWebBrowserWindow The Web Browser Window this viewport will display @param InViewportWidget The Widget displaying this viewport (needed to capture mouse) @param InIsPopup Used to initialize a viewport for showing browser popup menus instead of the main window.
- L34 _public prototype_ `~FWebBrowserViewport( ) = default;` — Destructor.
- L37 _public prototype_ `virtual FIntPoint GetSize() const override;` — ISlateViewport interface
- L38 _public prototype_ `virtual FSlateShaderResource* GetViewportRenderTargetTexture() const override;`
- L39 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, double InCurrentTime, float DeltaTime ) override;`
- L40 _public prototype_ `virtual bool RequiresVsync() const override;`
- L41 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) override;`
- L42 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L43 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L44 _public prototype_ `virtual void OnMouseEnter( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L45 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L46 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L47 _public prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L48 _public prototype_ `virtual FReply OnTouchGesture( const FGeometry& MyGeometry, const FPointerEvent& GestureEvent ) override;`
- L49 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L50 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L51 _public prototype_ `virtual FReply OnKeyUp( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L52 _public prototype_ `virtual FReply OnKeyChar( const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent ) override;`
- L53 _public prototype_ `virtual FReply OnFocusReceived( const FFocusEvent& InFocusEvent ) override;`
- L54 _public prototype_ `virtual void OnFocusLost( const FFocusEvent& InFocusEvent ) override;`
- L58 _private member_ `TSharedPtr<IWebBrowserWindow> WebBrowserWindow;` — The web browser this viewport will display
- L60 _private member_ `bool const bIsPopup;` — Whether this viewport is showing the browser window or a popup menu widget

### `Source/Runtime/WebBrowser/Public/WebJSFunction.h` (Public)


#### struct `FWebJSParam`  
`struct FWebJSParam`  
_L25-127_
- L58 _public function_ `FWebJSParam() : Tag(PTYPE_NULL)`
- L59 _public function_ `FWebJSParam(bool Value) : Tag(PTYPE_BOOL), BoolValue(Value)`
- L60 _public function_ `FWebJSParam(int8 Value) : Tag(PTYPE_INT), IntValue(Value)`
- L61 _public function_ `FWebJSParam(int16 Value) : Tag(PTYPE_INT), IntValue(Value)`
- L62 _public function_ `FWebJSParam(int32 Value) : Tag(PTYPE_INT), IntValue(Value)`
- L63 _public function_ `FWebJSParam(uint8 Value) : Tag(PTYPE_INT), IntValue(Value)`
- L64 _public function_ `FWebJSParam(uint16 Value) : Tag(PTYPE_INT), IntValue(Value)`
- L65 _public function_ `FWebJSParam(uint32 Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value)`
- L66 _public function_ `FWebJSParam(int64 Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value)`
- L67 _public function_ `FWebJSParam(uint64 Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value)`
- L68 _public function_ `FWebJSParam(double Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value)`
- L69 _public function_ `FWebJSParam(float Value) : Tag(PTYPE_DOUBLE), DoubleValue(Value)`
- L70 _public function_ `FWebJSParam(const FString& Value) : Tag(PTYPE_STRING), StringValue(new FString(Value))`
- L71 _public function_ `FWebJSParam(const FText& Value) : Tag(PTYPE_STRING), StringValue(new FString(Value.ToString()))`
- L72 _public function_ `FWebJSParam(const FName& Value) : Tag(PTYPE_STRING), StringValue(new FString(Value.ToString()))`
- L73 _public function_ `FWebJSParam(const TCHAR* Value) : Tag(PTYPE_STRING), StringValue(new FString(Value))`
- L74 _public function_ `FWebJSParam(UObject* Value) : Tag(PTYPE_OBJECT), ObjectValue(Value)`
- L75 _public function_ `template <typename T> FWebJSParam(const T& Value, typename TEnableIf<!TIsPointer<T>::Value, UStruct>::Type* InTypeInfo=T::StaticStruct()) : Tag(PTYPE_STRUCT) , StructValue(new FStructWrapper<T>(Value))`
- L80 _public function_ `template <typename T> FWebJSParam(const TArray<T>& Value) : Tag(PTYPE_ARRAY)`
- L90 _public function_ `template <typename T> FWebJSParam(const TMap<FString, T>& Value) : Tag(PTYPE_MAP)`
- L100 _public function_ `template <typename K, typename T> FWebJSParam(const TMap<K, T>& Value) : Tag(PTYPE_MAP)`
- L110 _public prototype_ `FWebJSParam(const FWebJSParam& Other);`
- L111 _public prototype_ `FWebJSParam(FWebJSParam&& Other);`
- L112 _public prototype_ `~FWebJSParam();`
- L114 _public member_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag;`

#### struct `FWebJSParam::IStructWrapper`  
`struct IStructWrapper`  
_L28-34_
- L30 _public prototype_ `virtual ~IStructWrapper() = default;`
- L31 _public prototype_ `virtual UStruct* GetTypeInfo() = 0;`
- L32 _public prototype_ `virtual const void* GetData() = 0;`
- L33 _public prototype_ `virtual IStructWrapper* Clone() = 0;`

#### struct `FWebJSParam::FStructWrapper`  
`template <typename T> struct FStructWrapper : public IStructWrapper`  
_L36-56_
- inherits: `IStructWrapper`
- L39 _public member_ `T StructValue;`
- L40 _public function_ `FStructWrapper(const T& InValue) : StructValue(InValue)`
- L43 _public prototype_ `virtual ~FStructWrapper() = default;`
- L44 _public function_ `virtual UStruct* GetTypeInfo() override`
- L48 _public function_ `virtual const void* GetData() override`
- L52 _public function_ `virtual IStructWrapper* Clone() override`

#### enum `FWebJSParam::(anonymous)`  
`enum`  
_L114-114_

#### union `FWebJSParam::(anonymous)`  
``  
_L116-125_

#### struct `FWebJSCallbackBase`  
`struct FWebJSCallbackBase`  
_L133-157_
- reflection: `USTRUCT()`
- desc: Base class for JS callback objects.
- L136 _public function_ `FWebJSCallbackBase()`
- L139 _public function_ `bool IsValid() const`
- L146 _protected function_ `FWebJSCallbackBase(TSharedPtr<FWebJSScripting> InScripting, const FGuid& InCallbackId) : ScriptingPtr(InScripting) , CallbackId(InCallbackId)`
- L151 _protected prototype_ `void Invoke(int32 ArgCount, FWebJSParam Arguments[], bool bIsError = false) const;`
- L155 _private member_ `TWeakPtr<FWebJSScripting> ScriptingPtr;`
- L156 _private member_ `FGuid CallbackId;`

#### struct `FWebJSFunction`  
`struct FWebJSFunction : public FWebJSCallbackBase`  
_L166-184_
- reflection: `USTRUCT()`
- inherits: `FWebJSCallbackBase`
- desc: Representation of a remote JS function. FWebJSFunction objects represent a JS function and allow calling them from native code. FWebJSFunction objects can also be added to delegates and events using the Bind/AddLambda method.
- L171 _public function_ `FWebJSFunction() : FWebJSCallbackBase()`
- L175 _public function_ `FWebJSFunction(TSharedPtr<FWebJSScripting> InScripting, const FGuid& InFunctionId) : FWebJSCallbackBase(InScripting, InFunctionId)`
- L179 _public function_ `template<typename ...ArgTypes> void operator()(ArgTypes... Args) const`

#### struct `FWebJSResponse`  
`struct FWebJSResponse : public FWebJSCallbackBase`  
_L196-241_
- reflection: `USTRUCT()`
- inherits: `FWebJSCallbackBase`
- desc: Representation of a remote JS async response object. UFUNCTIONs taking a FWebJSResponse will get it passed in automatically when called from a web browser. Pass a result or error back by invoking Success or Failure on the object. UFunctions accepting a FWebJSResponse should have a void return type, as any value returned from the function will be ignored. Calling the response methods does not have to happen before returning from the function, which means you can use this to implement asynchronous functionality. Note that the remote object will become invalid as soon as a result has been delivered, so you can only call either Success or Failure once.
- L201 _public function_ `FWebJSResponse() : FWebJSCallbackBase()`
- L205 _public function_ `FWebJSResponse(TSharedPtr<FWebJSScripting> InScripting, const FGuid& InCallbackId) : FWebJSCallbackBase(InScripting, InCallbackId)`
- L213 _public function_ `void Success() const` — Indicate successful completion without a return value. The remote Promise's then() handler will be executed without arguments.
- L223 _public function_ `template<typename T> void Success(T Arg) const` — Indicate successful completion passing a return value back. The remote Promise's then() handler will be executed with the value passed as its single argument.
- L234 _public function_ `template<typename T> void Failure(T Arg) const` — Indicate failed completion, passing an error message back to JS. The remote Promise's catch() handler will be executed with the value passed as the error reason.

#### Free symbols / members of external scopes

- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L114 _enumerator_ `enum { PTYPE_NULL, PTYPE_BOOL, PTYPE_INT, PTYPE_DOUBLE, PTYPE_STRING, PTYPE_OBJECT, PTYPE_STRUCT, PTYPE_ARRAY, PTYPE_MAP } Tag; union { bool BoolValue; double DoubleValue; int32 IntValue; UObject* ObjectValue; const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f0103`)
- L117 _member_ `bool BoolValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L118 _member_ `double DoubleValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L119 _member_ `int32 IntValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L120 _member_ `UObject* ObjectValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L121 _member_ `const FString* StringValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L122 _member_ `IStructWrapper* StructValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L123 _member_ `TArray<FWebJSParam>* ArrayValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
- L124 _member_ `TMap<FString, FWebJSParam>* MapValue;` (scope `FWebJSParam::__anonc7a69c3f020a`)
