# Plugins / Fab

- module root: `Plugins/Fab/Source/Fab`
- headers: 35; symbols: 931
- symbol kinds: class=43, delegate=11, enum=10, enumerator=45, function=98, macro=15, member=267, namespace=9, prototype=360, struct=43, typedef=26, variable=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, AssetTools, BuildPatchServices, ContentBrowser, CoreUObject, DesktopWidgets, DeveloperSettings, EOSSDK, EOSShared, EditorScriptingUtilities, EditorStyle, EditorSubsystem, Engine, FileUtilities, Foliage, GameProjectGeneration, HTTP, InputCore, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeImport, InterchangeNodes, InterchangePipelines, Json, JsonUtilities, LevelEditor, MainFrame, PlacementMode, Projects, RenderCore, Slate, SlateCore, ToolMenus, ToolWidgets, TypedElementFramework, UMG, UnrealEd, WebBrowser
- PublicDependencyModuleNames: Core

### `Plugins/Fab/Source/Fab/Private/FabAuthentication.h` (Private)


#### struct `FEosConstantsGameDev`  
`struct FEosConstantsGameDev`  
_L15-50_
- reflection: `USTRUCT()`
- L21 _public member_ `FString ProductId;` — `UPROPERTY()` — The product id for the running application, found on the dev portal
- L25 _public member_ `FString SandboxId;` — `UPROPERTY()` — The sandbox id for the running application, found on the dev portal
- L29 _public member_ `FString DeploymentId;` — `UPROPERTY()` — The deployment id for the running application, found on the dev portal
- L33 _public member_ `FString ClientCredentialsId;` — `UPROPERTY()` — Client id of the service permissions entry, found on the dev portal
- L37 _public member_ `FString ClientCredentialsSecret;` — `UPROPERTY()` — Client secret for accessing the set of permissions, found on the dev portal
- L41 _public member_ `FString GameName;` — `UPROPERTY()` — Game name
- L45 _public member_ `FString EncryptionKey;` — `UPROPERTY()` — Encryption key.
- L49 _public member_ `FString ProductVersion;` — `UPROPERTY()` — Product Version.

#### struct `FEosConstantsProd`  
`struct FEosConstantsProd`  
_L53-88_
- reflection: `USTRUCT()`
- L59 _public member_ `FString ProductId;` — `UPROPERTY()` — The product id for the running application, found on the dev portal
- L63 _public member_ `FString SandboxId;` — `UPROPERTY()` — The sandbox id for the running application, found on the dev portal
- L67 _public member_ `FString DeploymentId;` — `UPROPERTY()` — The deployment id for the running application, found on the dev portal
- L71 _public member_ `FString ClientCredentialsId;` — `UPROPERTY()` — Client id of the service permissions entry, found on the dev portal
- L75 _public member_ `FString ClientCredentialsSecret;` — `UPROPERTY()` — Client secret for accessing the set of permissions, found on the dev portal
- L79 _public member_ `FString GameName;` — `UPROPERTY()` — Game name
- L83 _public member_ `FString EncryptionKey;` — `UPROPERTY()` — Encryption key.
- L87 _public member_ `FString ProductVersion;` — `UPROPERTY()` — Product Version.

#### class `UEosConstants`  
`class UEosConstants : public UDataAsset`  
_L91-101_
- reflection: `UCLASS()`
- inherits: `UDataAsset`
- L97 _public member_ `FEosConstantsGameDev GameDev;` — `UPROPERTY()`
- L100 _public member_ `FEosConstantsProd Prod;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L103 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle>;`
- L108 _namespace_ `namespace FabAuthentication`
- L110 _variable_ `inline IEOSPlatformHandlePtr PlatformHandle;` (scope `FabAuthentication`)
- L111 _variable_ `inline EOS_HAuth AuthHandle;` (scope `FabAuthentication`)
- L112 _variable_ `inline EOS_EpicAccountId EpicAccountId;` (scope `FabAuthentication`)
- L114 _prototype_ `void Init();` (scope `FabAuthentication`)
- L115 _prototype_ `void Shutdown();` (scope `FabAuthentication`)
- L117 _prototype_ `bool LoginUsingExchangeCode(FString ExchangeCode);` (scope `FabAuthentication`)
- L118 _prototype_ `bool LoginUsingRefreshToken(FString RefreshToken);` (scope `FabAuthentication`)
- L119 _prototype_ `bool LoginUsingAccountPortal();` (scope `FabAuthentication`)
- L120 _prototype_ `bool LoginUsingPersist();` (scope `FabAuthentication`)
- L122 _prototype_ `FString GetAuthToken();` (scope `FabAuthentication`)
- L123 _prototype_ `FString GetRefreshToken();` (scope `FabAuthentication`)
- L128 _prototype_ `void DeletePersistentAuth();` (scope `FabAuthentication`) — Deletes any locally stored persistent auth credentials for the currently logged in user of the local device.
- L133 _prototype_ `void PrintAuthToken(const EOS_Auth_Token* InAuthToken);` (scope `FabAuthentication`) — Utility for printing auth token info
- L136 _prototype_ `void LoggedIn();` (scope `FabAuthentication`) — Called when successfully logged in
- L141 _prototype_ `static void EOS_CALL ExchangeCodeLoginCompleteCallbackFn(const EOS_Auth_LoginCallbackInfo* Data);` (scope `FabAuthentication`) — Callback that is fired when the login operation completes, either successfully or in error
- L146 _prototype_ `static void EOS_CALL AccountPortalLoginCompleteCallbackFn(const EOS_Auth_LoginCallbackInfo* Data);` (scope `FabAuthentication`) — Callback that is fired when the login operation completes, either successfully or in error
- L151 _prototype_ `static void EOS_CALL PersistLoginCompleteCallbackFn(const EOS_Auth_LoginCallbackInfo* Data);` (scope `FabAuthentication`) — Callback that is fired when the login operation completes, either successfully or in error
- L156 _prototype_ `static void EOS_CALL DeletePersistentAuthCompleteCallbackFn(const EOS_Auth_DeletePersistentAuthCallbackInfo* Data);` (scope `FabAuthentication`) — Callback that is fired when the delete persistent auth operation completes, either successfully or in error
- L158 _prototype_ `static void EOS_CALL OnLogoutCallbackFn(const EOS_Auth_LogoutCallbackInfo* Data);` (scope `FabAuthentication`)

### `Plugins/Fab/Source/Fab/Private/FabBrowser.h` (Private)


#### struct `FFabAnalyticsEventValue`  
`struct FFabAnalyticsEventValue`  
_L20-29_
- reflection: `USTRUCT()`
- L25 _public member_ `FString Platform;` — `UPROPERTY()`
- L28 _public member_ `FFabApiVersion ApiVersion;` — `UPROPERTY()`

#### struct `FFabAnalyticsPayload`  
`struct FFabAnalyticsPayload`  
_L32-53_
- reflection: `USTRUCT()`
- L37 _public member_ `FString InteractionType;` — `UPROPERTY()`
- L40 _public member_ `FString EventCategory;` — `UPROPERTY()`
- L43 _public member_ `FString EventAction;` — `UPROPERTY()`
- L46 _public member_ `FString EventLabel;` — `UPROPERTY()`
- L49 _public member_ `FString EventType;` — `UPROPERTY()`
- L52 _public member_ `FFabAnalyticsEventValue EventValue;` — `UPROPERTY()`

#### struct `FFabBrowserTabContext`  
`struct FFabBrowserTabContext`  
_L55-72_
- L57 _public member_ `FName TabId = NAME_None;`
- L60 _public member_ `TWeakPtr<SDockTab> DockTab;` — Slate/CEF objects
- L61 _public member_ `TSharedPtr<IWebBrowserWindow> WebBrowserWindow;`
- L62 _public member_ `TSharedPtr<SWebBrowser> WebBrowserInstance;`
- L68 _public member_ `TWeakObjectPtr<UFabBrowserApi> JavascriptApi;` — JS bridge Held as a weak pointer so access after GC returns null instead of dereferencing a dangling address. Liveness while in use is anchored by AddToRoot / RemoveFromRoot. Game-thread only: TWeakObjectPtr is not thread-safe.
- L70 _public member_ `bool bIsNativelyRendered = false;`
- L71 _public member_ `bool bIsClosing = false;`

#### class `FFabBrowser`  
`class FFabBrowser`  
_L74-143_
- L77 _private member_ `static TUniquePtr<FSlateStyleSet> SlateStyleSet;`
- L78 _private member_ `static TObjectPtr<const UFabSettings> FabPluginSettings;`
- L81 _private member_ `static int32 FabTabCounter;` — Tabs
- L82 _private member_ `static FName ActiveFabTabId;`
- L83 _private member_ `static TMap<FName, FFabBrowserTabContext> TabsById;`
- L84 _private member_ `static TSharedPtr<FTabManager> TabManager;`
- L85 _private member_ `static bool bIsShuttingDown;`
- L87 _private member_ `static const FText FabLabel;`
- L88 _private member_ `static const FText FabDefaultTabTitle;`
- L89 _private member_ `static const FText FabTooltip;`
- L90 _private member_ `static const FName FabMenuIconName;`
- L91 _private member_ `static const FName FabAssetIconName;`
- L92 _private member_ `static const FName FabToolbarIconName;`
- L94 _private prototype_ `static void RegisterSlateStyle();`
- L95 _private prototype_ `static void ExtendContextMenuInContentBrowser();`
- L96 _private prototype_ `static void SetupEntryPoints();`
- L99 _private prototype_ `static FName MakeNextFabTabId();` — Helpers
- L100 _private prototype_ `static bool EnsureWebBrowserAvailable();`
- L101 _private prototype_ `static FString BuildIndexFileUrl();`
- L102 _private prototype_ `static void PreventBrowserKeyConflictWithEditor(const FFabBrowserTabContext& Context);`
- L103 _private prototype_ `static void InstallUrlRestrictions(const FFabBrowserTabContext& Context);`
- L104 _private prototype_ `static void InstallDebugPopup(const FFabBrowserTabContext& Context);`
- L105 _private prototype_ `static bool InterceptNavigation(const TSharedPtr<IWebBrowserWindow>& BrowserWindow, const FString& CurrentUrl, const FString& FabBaseUrl);`
- L106 _private prototype_ `static void SetupDockTabListenersForNativeRendering(const TSharedRef<SDockTab>& DockTab, const FName TabId);`
- L107 _private prototype_ `static void SetupTabWindowMoveListenerForNativeRendering(const TSharedRef<SDockTab>& DockTab);`
- L108 _private prototype_ `static void ReparentDockTabs();`
- L109 _private prototype_ `static void RefreshNativeTabViewPort();`
- L112 _private prototype_ `static void CreateNewFabTab(const FString& Url = TEXT(""));` — Tab Creation
- L113 _private prototype_ `static void CreateOsrFabTab(const FString& Url);`
- L114 _private prototype_ `static void PreventWebBrowserFreezeInOsrMode(const FName& TabId, const FFabBrowserTabContext& Context);`
- L115 _private prototype_ `static void CreateNativeFabTab(const FString& Url);`
- L116 _private prototype_ `static void AttachBrowserToDockTab(const TSharedRef<SDockTab>& DockTab, const bool bNativeRendering, const FName TabId, const FString& Url);`
- L117 _private prototype_ `static void HandleTabClosed(TSharedRef<SDockTab> ClosedTab, FName TabId);`
- L118 _private prototype_ `static void HandleTabActivated(TSharedRef<SDockTab> ActivatedTab, ETabActivationCause Cause, FName TabId);`
- L120 _private prototype_ `static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);`
- L121 _private prototype_ `static TSharedRef<SWidget> OnFabAssetIconGenerate(const FAssetData& AssetData);`
- L124 _public prototype_ `static void Init();`
- L125 _public prototype_ `static void Shutdown();`
- L128 _public prototype_ `static void NotifyAllTabsLogout();` — Notify all open Fab tabs that a logout has occurred by invoking their OnLogout JS callback.
- L131 _public prototype_ `static void NotifyAllTabsLogin(const FString& AccessToken);` — Notify all open Fab tabs that a login has occurred by sending the access token via their OnLogin JS callback.
- L133 _public prototype_ `static void LogEvent(const FFabAnalyticsPayload& Payload);`
- L134 _public prototype_ `static void LoggedIn(const FString& InAccessToken);`
- L135 _public prototype_ `static TWeakObjectPtr<UFabBrowserApi> GetBrowserApi();`
- L136 _public prototype_ `static void ShowSettings();`
- L137 _public prototype_ `static void OpenURL(const FString& InURL = GetUrl());`
- L139 _public prototype_ `static void OpenInNewTab(const FString& Url);` — Opens the given URL in a new Fab plugin tab (native webview, not the system browser).
- L140 _public prototype_ `static FFabBrowserTabContext* GetActiveDockTabContext();`
- L141 _public prototype_ `static FString GetUrl();`
- L142 _public prototype_ `static const ISlateStyle& GetStyleSet();`

### `Plugins/Fab/Source/Fab/Private/FabBrowserApi.h` (Private)


#### struct `FFabSupportedFeatures`  
`struct FFabSupportedFeatures`  
_L13-23_
- reflection: `USTRUCT()`
- L22 _public member_ `bool banners = false;` — `UPROPERTY()`

#### struct `FFabApiVersion`  
`struct FFabApiVersion`  
_L26-54_
- reflection: `USTRUCT()`
- L35 _public member_ `FString ue;` — `UPROPERTY()`
- L38 _public member_ `FString api;` — `UPROPERTY()`
- L41 _public member_ `FString pluginversion;` — `UPROPERTY()`
- L44 _public member_ `FString platform;` — `UPROPERTY()`
- L47 _public member_ `FFabSupportedFeatures supportedfeatures;` — `UPROPERTY()`
- L50 _public member_ `FString selectedlocale;` — `UPROPERTY()`
- L53 _public member_ `FString selectedlocalename;` — `UPROPERTY()`

#### struct `FFabFrontendSettings`  
`struct FFabFrontendSettings`  
_L57-69_
- reflection: `USTRUCT()`
- L65 _public member_ `FString preferredformat;` — `UPROPERTY()` — These two uproperties need to be in this case (NOT PascalCase) otherwise we will break compatibility with the engine plugin Fab's JS on the macOS WebKit WebBrowser plugin backend.
- L68 _public member_ `FString preferredquality;` — `UPROPERTY()`

#### struct `FFabCallbacks`  
`struct FFabCallbacks`  
_L72-84_
- reflection: `USTRUCT()`
- L77 _public member_ `FWebJSFunction OnLogout;` — `UPROPERTY()`
- L80 _public member_ `FWebJSFunction OnLogin;` — `UPROPERTY()`
- L83 _public member_ `FWebJSFunction OnLogEvent;` — `UPROPERTY()`

#### class `UFabBrowserApi`  
`class UFabBrowserApi : public UObject`  
_L87-179_
- reflection: `UCLASS()`
- inherits: `UObject`
- L90 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSignedUrlGenerated, const FString& , FFabAssetMetadata );`
- L93 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnLogout, int32 );` — Frontend callbacks
- L94 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnLogin, const FString& );`
- L95 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnLogEvent, const FString& );`
- L98 _private member_ `FOnSignedUrlGenerated OnSignedUrlGeneratedDelegate;`
- L99 _private prototype_ `void CompleteWorkflow(const FString& Id);`
- L100 _private member_ `TArray<TSharedPtr<IFabWorkflow>> ActiveWorkflows;`
- L102 _private member_ `FOnLogout OnLogoutDelegate;`
- L103 _private member_ `FOnLogin OnLoginDelegate;`
- L104 _private member_ `FOnLogEvent OnLogEventDelegate;`
- L108 _public prototype_ `void RegisterCallbacks(const FFabCallbacks& Callbacks);` — `UFUNCTION()`
- L111 _public prototype_ `void ExecuteOnLogoutCallback() const;` — Invoke the stored OnLogout callback, if one has been registered by the frontend.
- L114 _public prototype_ `void ExecuteOnLoginCallback(const FString& AccessToken) const;` — Invoke the stored OnLogin callback, if one has been registered by the frontend.
- L117 _public prototype_ `void ExecuteOnLogEventCallback(const FString& JSONPayload) const;` — Invoke the stored OnLogEvent callback, if one has been registered by the frontend.
- L120 _public prototype_ `void AddToProject(const FString& DownloadUrl, const FFabAssetMetadata& AssetMetadata);` — `UFUNCTION()`
- L123 _public prototype_ `void InstallToProject(const FString& DownloadUrl, const FFabAssetMetadata& AssetMetadata);` — `UFUNCTION()`
- L126 _public prototype_ `void InstallToEngine(const FString& DownloadUrl, const FFabAssetMetadata& AssetMetadata);` — `UFUNCTION()`
- L129 _public prototype_ `void DragStart(const FFabAssetMetadata& AssetMetadata);` — `UFUNCTION()`
- L132 _public prototype_ `void OnDragInfoSuccess(const FString& DownloadUrl, const FFabAssetMetadata& AssetMetadata);` — `UFUNCTION()`
- L135 _public prototype_ `void OnDragInfoFailure(const FString& AssetId);` — `UFUNCTION()`
- L138 _public prototype_ `void Login();` — `UFUNCTION()`
- L141 _public prototype_ `void Logout();` — `UFUNCTION()`
- L144 _public prototype_ `FString GetAuthToken();` — `UFUNCTION()`
- L147 _public prototype_ `FString GetRefreshToken();` — `UFUNCTION()`
- L150 _public prototype_ `void OpenPluginSettings();` — `UFUNCTION()`
- L153 _public prototype_ `FFabFrontendSettings GetSettings();` — `UFUNCTION()`
- L156 _public prototype_ `void SetPreferredQualityTier(const FString& PreferredQuality);` — `UFUNCTION()`
- L159 _public prototype_ `static FFabApiVersion GetApiVersion();` — `UFUNCTION()`
- L162 _public prototype_ `void OpenInNewTab(const FString& Url);` — `UFUNCTION()`
- L165 _public prototype_ `void OpenUrlInBrowser(const FString& Url);` — `UFUNCTION()`
- L168 _public prototype_ `void CopyToClipboard(const FString& Content);` — `UFUNCTION()`
- L171 _public prototype_ `void PluginOpened();` — `UFUNCTION()`
- L174 _public prototype_ `FString GetUrl();` — `UFUNCTION()`
- L176 _public prototype_ `FDelegateHandle AddSignedUrlCallback(TFunction<void(const FString&, const FFabAssetMetadata&)> Callback);`
- L177 _public function_ `FOnSignedUrlGenerated& OnSignedUrlGenerated()`
- L178 _public function_ `void RemoveSignedUrlHandle(const FDelegateHandle& Handle)`

#### Free symbols / members of external scopes

- L90 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSignedUrlGenerated, const FString& , FFabAssetMetadata );`
- L93 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLogout, int32 );` — Frontend callbacks
- L94 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLogin, const FString& );`
- L95 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLogEvent, const FString& );`

### `Plugins/Fab/Source/Fab/Private/FabLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFab, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFab, Log, All);`
- L9 _macro_ `#define FAB_LOG(Format, ...) UE_LOG(LogFab, Display, TEXT(Format), ##__VA_ARGS__)`
- L10 _macro_ `#define FAB_LOG_ERROR(Format, ...) UE_LOG(LogFab, Error, TEXT(Format), ##__VA_ARGS__)`
- L11 _macro_ `#define FAB_LOG_VERBOSE(Format, ...) UE_LOG(LogFab, Display, TEXT(Format), ##__VA_ARGS__)`

### `Plugins/Fab/Source/Fab/Private/FabSettings.h` (Private)


#### enum `EFabEnvironment`  
`enum class EFabEnvironment : uint8`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `Prod UMETA(DisplayName = "Prod")`
- L15 _public enumerator_ `Gamedev UMETA(DisplayName = "Gamedev")`
- L16 _public enumerator_ `Test UMETA(DisplayName = "Test")`
- L17 _public enumerator_ `CustomUrl UMETA(DisplayName = "Custom URL")`

#### enum `EFabPreferredFormats`  
`enum class EFabPreferredFormats : uint8`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `GLTF UMETA(DisplayName = "gltf / glb")`
- L24 _public enumerator_ `FBX UMETA(DisplayName = "fbx")`

#### enum `EFabExperienceMode`  
`enum class EFabExperienceMode : uint8`  
_L28-32_
- reflection: `UENUM()`
- L30 _public enumerator_ `Standard UMETA(DisplayName = "Standard")`
- L31 _public enumerator_ `Performance UMETA(DisplayName = "Performance")`

#### enum `EFabPreferredQualityTier`  
`enum class EFabPreferredQualityTier : uint8`  
_L35-41_
- reflection: `UENUM()`
- L37 _public enumerator_ `Low UMETA(DisplayName = "low")`
- L38 _public enumerator_ `Medium UMETA(DisplayName = "medium")`
- L39 _public enumerator_ `High UMETA(DisplayName = "high")`
- L40 _public enumerator_ `Raw UMETA(DisplayName = "raw")`

#### class `UFabSettings`  
`class UFabSettings : public UObject`  
_L44-95_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, hideCategories=HiddenProperties)`
- inherits: `UObject`
- L49 _public prototype_ `UFabSettings();`
- L53 _public member_ `EFabEnvironment Environment = EFabEnvironment::Prod;` — `UPROPERTY(config, EditAnywhere, Category=Frontend, meta=(DevOnly=true))` — Frontend used by the Fab plugin (reopen the tab to see the change)
- L57 _public member_ `FString CustomUrl;` — `UPROPERTY(config, EditAnywhere, Category=Frontend, meta=(DevOnly=true))` — URL used when the [Fab (custom)] frontend is selected
- L61 _public member_ `FString CustomAuthToken;` — `UPROPERTY(config, EditAnywhere, Category=Frontend, meta=(DevOnly=true))` — Custom auth token used when it's non-empty
- L65 _public member_ `EFabExperienceMode ExperienceMode = EFabExperienceMode::Standard;` — `UPROPERTY(config, EditAnywhere, Category=General)` — Experience mode: Standard uses OSR rendering, Performance uses native rendering (Windows only; Mac uses a single OSR tab)
- L69 _public member_ `bool bEnableDebugOptions = false;` — `UPROPERTY(config, EditAnywhere, Category = General)` — Enable chrome debug options - default is false
- L73 _public member_ `FDirectoryPath CacheDirectoryPath { FPlatformProcess::UserTempDir() / FString("FabLi` — `UPROPERTY(config, EditAnywhere, Category = General)` — Path to the local library
- L77 _public member_ `FString CacheDirectorySize;` — `UPROPERTY(config, VisibleAnywhere, Category = General)` — Cache directory
- L82 _public member_ `FString ProductFormatsSectionSubText = "";` — `UPROPERTY(config, VisibleAnywhere, Category = ProductFormats, meta=(DevOnly=true))` — The preferred format will always be selected, if not available, the best available format for the product will be chosen.
- L86 _public member_ `EFabPreferredFormats PreferredDefaultFormat = EFabPreferredFormats::GLTF;` — `UPROPERTY(config, EditAnywhere, Category = ProductFormats, meta=(DevOnly=true))` — Preferred default format
- L90 _public member_ `EFabPreferredQualityTier PreferredQualityTier = EFabPreferredQualityTier::Medium;` — `UPROPERTY(config, EditAnywhere, Category = Megascans)` — Preferred default quality for MS assets
- L92 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L94 _public prototype_ `FString GetUrlFromEnvironment() const;`

### `Plugins/Fab/Source/Fab/Private/FabSettingsCustomization.h` (Private)


#### class `FFabSettingsCustomization`  
`class FFabSettingsCustomization : public IDetailCustomization`  
_L9-18_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L17 _private prototype_ `FReply OnButtonClick();`

### `Plugins/Fab/Source/Fab/Private/FabSettingsWindow.h` (Private)


#### struct `SFabSettingsWindow`  
`struct SFabSettingsWindow : public SCompoundWidget`  
_L14-48_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SFabSettingsWindow)`
- L20 _public function_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L45 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L47 _public member_ `TWeakPtr<SWindow> Window;`

#### Free symbols / members of external scopes

- L12 _variable_ `TObjectPtr<UFabSettings> FabPluginSettings = nullptr;`

### `Plugins/Fab/Source/Fab/Private/Importers/BuildPatchInstallerLibHelper.h` (Private)


#### class `BpiLib::FManifestStorage`  
`class FManifestStorage`  
_L39-63_
- L42 _public prototype_ `FManifestStorage(const BpiLibHelpers::FBpiLibHelper& InLibRef, const TArray<uint8>& Data);`
- L43 _public prototype_ `~FManifestStorage();`
- L45 _public function_ `IBuildManifestPtr operator->() const`
- L46 _public function_ `IBuildManifestPtr* GetManifestPtr() const`
- L48 _public function_ `bool IsValid() const`
- L50 _public prototype_ `bool SaveToFile(const FString& Filename) const;`
- L52 _public prototype_ `TArray<FString> GetBuildFileList() const;`
- L53 _public prototype_ `FString GetCustomStringField(const FString& Name) const;`
- L54 _public prototype_ `FString GetAppName() const;`
- L56 _public prototype_ `void SetCustomField(const FString& FieldName, const FString& Value) const;`
- L57 _public prototype_ `void SetCustomField(const FString& FieldName, const double& Value) const;`
- L58 _public prototype_ `void SetCustomField(const FString& FieldName, const int64& Value) const;`
- L61 _private member_ `const BpiLibHelpers::FBpiLibHelper& LibRef;`
- L62 _private member_ `IBuildManifestPtr* ManifestPtr;`
- L766 _function_ `inline FManifestStorage::FManifestStorage(const BpiLibHelpers::FBpiLibHelper& InLibRef, const TArray<uint8>& Data) : LibRef(InLibRef)`
- L772 _function_ `inline FManifestStorage::~FManifestStorage()`
- L777 _function_ `inline bool FManifestStorage::SaveToFile(const FString& Filename) const`
- L782 _function_ `inline TArray<FString> FManifestStorage::GetBuildFileList() const`
- L789 _function_ `inline FString FManifestStorage::GetCustomStringField(const FString& Name) const`
- L795 _function_ `inline void FManifestStorage::SetCustomField(const FString& FieldName, const FString& Value) const`
- L800 _function_ `inline void FManifestStorage::SetCustomField(const FString& FieldName, const double& Value) const`
- L805 _function_ `inline void FManifestStorage::SetCustomField(const FString& FieldName, const int64& Value) const`
- L810 _function_ `inline FString FManifestStorage::GetAppName() const`

#### class `BpiLib::IBpiLib`  
`class IBpiLib`  
_L65-80_
- L68 _public prototype_ `virtual ~IBpiLib() = default;`
- L69 _public prototype_ `virtual bool IsValid() const = 0;`
- L70 _public prototype_ `virtual IBuildInstallerRef CreateInstaller(FManifestStorage& ManifestStorage, const BuildPatchServices::FBuildInstallerConfiguration& Configuration, FBuildPatchInstallerDelegate CompleteDelegate) const = 0;`
- L71 _public prototype_ `virtual void CancelInstall(const IBuildInstallerRef& Installer) const = 0;`
- L72 _public prototype_ `virtual FManifestStorage MakeManifestFromData(const TArray<uint8>& Data) const = 0;`
- L73 _public prototype_ `virtual bool Tick(float) = 0;`
- L74 _public prototype_ `virtual FBuildInstallStats GetBuildStats(const IBuildInstallerRef& Installer) const = 0;`
- L75 _public prototype_ `virtual int64 GetTotalDownloaded(const IBuildInstallerRef& Installer) const = 0;`
- L76 _public prototype_ `virtual int64 GetState(const IBuildInstallerRef& Installer) const = 0;`
- L77 _public prototype_ `virtual float GetUpdateProgress(const IBuildInstallerRef& Installer) const = 0;`
- L78 _public prototype_ `virtual double GetDownloadSpeed(const IBuildInstallerRef& Installer) const = 0;`
- L79 _public prototype_ `virtual int64 GetTotalDownloadRequired(const IBuildInstallerRef& Installer) const = 0;`

#### class `BpiLib::FBpiLibHelperFactory`  
`class FBpiLibHelperFactory`  
_L82-86_
- L85 _public prototype_ `static TUniquePtr<IBpiLib> Create(const FString& FilePath);`
- L748 _function_ `inline TUniquePtr<IBpiLib> FBpiLibHelperFactory::Create(const FString& FilePath)`

#### struct `BpiLib::FBpiBuildInstallerConfiguration`  
`struct FBpiBuildInstallerConfiguration`  
_L88-137_
- L90 _public member_ `static const int MaxCloudDirs = 20;`
- L93 _public member_ `const TCHAR* InstallDirectory = nullptr;` — TArray<FInstallerAction> InstallerActions;
- L94 _public member_ `const TCHAR* StagingDirectory = nullptr;`
- L95 _public member_ `const TCHAR* BackupDirectory = nullptr;`
- L97 _public member_ `const TCHAR* CloudDirectories[MaxCloudDirs];` — TArray<FString> ChunkDatabaseFiles;
- L98 _public member_ `int32 CloudDirectoriesNum = 0;`
- L99 _public member_ `int32 InstallMode = int32(BuildPatchServices::EInstallMode::NonDestructiveInstall);`
- L100 _public member_ `int32 VerifyMode = int32(BuildPatchServices::EVerifyMode::ShaVerifyAllFiles);`
- L101 _public member_ `int32 DeltaPolicy = int32(BuildPatchServices::EDeltaPolicy::Skip);`
- L102 _public member_ `bool bRunRequiredPrereqs = true;`
- L103 _public member_ `bool bSkipPrereqIfAlreadyRan = true;`
- L104 _public member_ `bool bAllowConcurrentExecution = false;`
- L105 _public member_ `uint64 DownloadRateLimitBps = 0;`
- L106 _public member_ `bool bStageWithRawFilenames = false;`
- L107 _public member_ `bool bRejectSymlinks = false;`
- L109 _public function_ `static FBpiBuildInstallerConfiguration Create(const BuildPatchServices::FBuildInstallerConfiguration& InCfg)`

#### struct `BpiLib::FBpiBuildInstallStats`  
`struct FBpiBuildInstallStats`  
_L139-204_
- L141 _public member_ `uint32 NumFilesInBuild = 0;`
- L142 _public member_ `uint32 NumFilesOutdated = 0;`
- L143 _public member_ `uint32 NumFilesToRemove = 0;`
- L144 _public member_ `uint32 NumChunksRequired = 0;`
- L145 _public member_ `uint32 ChunksQueuedForDownload = 0;`
- L146 _public member_ `uint32 ChunksLocallyAvailable = 0;`
- L147 _public member_ `uint32 ChunksInChunkDbs = 0;`
- L148 _public member_ `uint32 NumChunksDownloaded = 0;`
- L149 _public member_ `uint32 NumChunksRecycled = 0;`
- L150 _public member_ `uint32 NumChunksReadFromChunkDbs = 0;`
- L151 _public member_ `uint32 NumFailedDownloads = 0;`
- L152 _public member_ `uint32 NumBadDownloads = 0;`
- L153 _public member_ `uint32 NumAbortedDownloads = 0;`
- L154 _public member_ `uint32 NumRecycleFailures = 0;`
- L155 _public member_ `uint32 NumDriveStoreChunkLoads = 0;`
- L156 _public member_ `uint32 NumDriveStoreLoadFailures = 0;`
- L157 _public member_ `uint32 NumChunkDbChunksFailed = 0;`
- L158 _public member_ `uint64 TotalDownloadedData = 0;`
- L159 _public member_ `uint32 ActiveRequestCountPeak = 0;`
- L160 _public member_ `double AverageDownloadSpeed = 0.0;`
- L161 _public member_ `double PeakDownloadSpeed = 0.0;`
- L162 _public member_ `double FinalDownloadSpeed = 0;`
- L163 _public member_ `float TheoreticalDownloadTime = 0.f;`
- L164 _public member_ `uint64 TotalReadData = 0;`
- L165 _public member_ `double AverageDiskReadSpeed = 0.0;`
- L166 _public member_ `double PeakDiskReadSpeed = 0.0;`
- L167 _public member_ `uint64 TotalWrittenData = 0;`
- L168 _public member_ `double AverageDiskWriteSpeed = 0.0;`
- L169 _public member_ `double PeakDiskWriteSpeed = 0.0;`
- L170 _public member_ `uint32 NumFilesConstructed = 0;`
- L171 _public member_ `float InitializeTime = 0.f;`
- L172 _public member_ `float ConstructTime = 0.f;`
- L173 _public member_ `float UninstallActionTime = 0.f;`
- L174 _public member_ `float MoveFromStageTime = 0.f;`
- L175 _public member_ `float FileAttributesTime = 0.f;`
- L176 _public member_ `float VerifyTime = 0.f;`
- L177 _public member_ `float CleanUpTime = 0.f;`
- L178 _public member_ `float PrereqTime = 0.f;`
- L179 _public member_ `float ProcessPausedTime = 0.f;`
- L180 _public member_ `float ProcessActiveTime = 0.f;`
- L181 _public member_ `float ProcessExecuteTime = 0.f;`
- L182 _public member_ `bool ProcessSuccess = false;`
- L183 _public member_ `uint32 NumInstallRetries = 0;`
- L184 _public member_ `int32 FailureType = 0;`
- L185 _public member_ `int32* RetryFailureTypes = nullptr;`
- L186 _public member_ `int32 RetryFailureTypesNum = 0;`
- L187 _public member_ `const TCHAR* ErrorCode = nullptr;`
- L188 _public member_ `const TCHAR** RetryErrorCodes = nullptr;`
- L189 _public member_ `int32 RetryErrorCodesNum = 0;`
- L190 _public member_ `const TCHAR* FailureReasonText = nullptr;`
- L191 _public member_ `float FinalProgress = 0.f;`
- L192 _public member_ `float OverallRequestSuccessRate = 0.f;`
- L193 _public member_ `float ExcellentDownloadHealthTime = 0.f;`
- L194 _public member_ `float GoodDownloadHealthTime = 0.f;`
- L195 _public member_ `float OkDownloadHealthTime = 0.f;`
- L196 _public member_ `float PoorDownloadHealthTime = 0.f;`
- L197 _public member_ `float DisconnectedDownloadHealthTime = 0.f;`
- L198 _public member_ `uint64 ProcessRequiredDiskSpace = 0;`
- L199 _public member_ `uint64 ProcessAvailableDiskSpace = 0;`
- L200 _public member_ `uint32 DriveStorePeakBytes = 0;`
- L201 _public member_ `uint32 NumDriveStoreLostChunks = 0;`
- L202 _public member_ `uint64 MemoryStoreSizePeakBytes = 0;`
- L203 _public member_ `uint64 MemoryStoreSizeLimitBytes = 0;`

#### class `BpiLib::BpiLibHelpers::TExportedFunc`  
`template<typename TTraits> class TExportedFunc`  
_L222-240_
- L225 _public function_ `TExportedFunc(void* DllHandle) : Ptr(ImportFunction<typename TTraits::FFuncType>(TTraits::GetName(), DllHandle))`
- L231 _public function_ `bool IsValid() const`
- L234 _public function_ `template<typename ...ArgsType> auto operator()(ArgsType&& ...Args) const`
- L239 _public member_ `typename TTraits::FFuncType Ptr = nullptr;`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FInit`  
`struct FInit`  
_L244-255_
- L246 _public typedef_ `using FFuncType = int (*)(const TCHAR*);`
- L247 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FShutdown`  
`struct FShutdown`  
_L257-268_
- L259 _public typedef_ `using FFuncType = void (*)();`
- L260 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FTick`  
`struct FTick`  
_L270-281_
- L272 _public typedef_ `using FFuncType = bool (*)(float);`
- L273 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FFree`  
`struct FFree`  
_L283-294_
- L285 _public typedef_ `using FFuncType = void (*)(void*);`
- L286 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FFreeArray`  
`struct FFreeArray`  
_L296-307_
- L298 _public typedef_ `using FFuncType = void (*)(void**, int32);`
- L299 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FCreateMakeInstall`  
`struct FCreateMakeInstall`  
_L309-325_
- L311 _public typedef_ `using FFuncType = IBuildInstallerRef(*)( IBuildManifestPtr*, const FBpiBuildInstallerConfiguration*, const void*, void(*)(const IBuildInstallerRef&, const void*));`
- L316 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FCancelInstall`  
`struct FCancelInstall`  
_L327-338_
- L329 _public typedef_ `using FFuncType = void (*)(IBuildInstaller*);`
- L330 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FMakeManifestFromData`  
`struct FMakeManifestFromData`  
_L340-351_
- L342 _public typedef_ `using FFuncType = IBuildManifestPtr * (*)(const uint8*, int32);`
- L343 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FDeleteManifest`  
`struct FDeleteManifest`  
_L353-364_
- L355 _public typedef_ `using FFuncType = void (*)(IBuildManifestPtr*);`
- L356 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FSaveManifestToFile`  
`struct FSaveManifestToFile`  
_L366-377_
- L368 _public typedef_ `using FFuncType = bool (*)(IBuildManifestPtr*, const TCHAR*);`
- L369 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetBuildFileList`  
`struct FGetBuildFileList`  
_L379-390_
- L381 _public typedef_ `using FFuncType = TCHAR * *(*)(IBuildManifestPtr*, int32*);`
- L382 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetCustomStringField`  
`struct FGetCustomStringField`  
_L392-403_
- L394 _public typedef_ `using FFuncType = TCHAR * (*)(IBuildManifestPtr*, const TCHAR*);`
- L395 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FSetCustomStringField`  
`struct FSetCustomStringField`  
_L405-416_
- L407 _public typedef_ `using FFuncType = TCHAR * (*)(IBuildManifestPtr*, const TCHAR*, const TCHAR*);`
- L408 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FSetCustomDoubleField`  
`struct FSetCustomDoubleField`  
_L418-429_
- L420 _public typedef_ `using FFuncType = TCHAR * (*)(IBuildManifestPtr*, const TCHAR*, double);`
- L421 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FSetCustomIntField`  
`struct FSetCustomIntField`  
_L431-442_
- L433 _public typedef_ `using FFuncType = TCHAR * (*)(IBuildManifestPtr*, const TCHAR*, int64);`
- L434 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetAppName`  
`struct FGetAppName`  
_L444-455_
- L446 _public typedef_ `using FFuncType = TCHAR * (*)(IBuildManifestPtr* Manifest);`
- L447 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetBuildStats`  
`struct FGetBuildStats`  
_L457-468_
- L459 _public typedef_ `using FFuncType = FBpiBuildInstallStats * (*)(IBuildInstaller* Installer);`
- L460 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetTotalDownloaded`  
`struct FGetTotalDownloaded`  
_L470-481_
- L472 _public typedef_ `using FFuncType = int64(*)(IBuildInstaller*);`
- L473 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetState`  
`struct FGetState`  
_L483-494_
- L485 _public typedef_ `using FFuncType = int64(*)(IBuildInstaller*);`
- L486 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetUpdateProgress`  
`struct FGetUpdateProgress`  
_L496-507_
- L498 _public typedef_ `using FFuncType = float(*)(IBuildInstaller*);`
- L499 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetDownloadSpeed`  
`struct FGetDownloadSpeed`  
_L509-520_
- L511 _public typedef_ `using FFuncType = double(*)(IBuildInstaller*);`
- L512 _public function_ `static const TCHAR* GetName()`

#### struct `BpiLib::BpiLibHelpers::FuncTraits::FGetTotalDownloadRequired`  
`struct FGetTotalDownloadRequired`  
_L522-533_
- L524 _public typedef_ `using FFuncType = int64(*)(IBuildInstaller*);`
- L525 _public function_ `static const TCHAR* GetName()`

#### class `BpiLib::BpiLibHelpers::FBpiLibHelper`  
`class FBpiLibHelper : public IBpiLib`  
_L536-745_
- inherits: `IBpiLib`
- L546 _public function_ `FBpiLibHelper(void* InDllHandle) : DllHandle(InDllHandle)`
- L556 _public function_ `virtual ~FBpiLibHelper()`
- L565 _public function_ `virtual bool IsValid() const override`
- L567 _public function_ `virtual IBuildInstallerRef CreateInstaller( FManifestStorage& ManifestStorage, const BuildPatchServices::FBuildInstallerConfiguration& Configuration, FBuildPatchInstallerDelegate InCompleteDelegate) const override`
- L588 _public function_ `virtual FManifestStorage MakeManifestFromData(const TArray<uint8>& Data) const override`
- L593 _public function_ `virtual bool Tick(float Delta) override`
- L595 _public function_ `virtual FBuildInstallStats GetBuildStats(const IBuildInstallerRef& Installer) const override`
- L672 _public function_ `virtual void CancelInstall(const IBuildInstallerRef& Installer) const override`
- L674 _public function_ `virtual int64 GetTotalDownloaded(const IBuildInstallerRef& Installer) const override`
- L675 _public function_ `virtual int64 GetState(const IBuildInstallerRef& Installer) const override`
- L676 _public function_ `virtual float GetUpdateProgress(const IBuildInstallerRef& Installer) const override`
- L677 _public function_ `virtual double GetDownloadSpeed(const IBuildInstallerRef& Installer) const override`
- L678 _public function_ `virtual int64 GetTotalDownloadRequired(const IBuildInstallerRef& Installer) const override`
- L681 _public function_ `template<typename Out, typename In> Out ConvertAndFree(In Data, int32 Num) const`
- L697 _public function_ `FString ConvertAndFree(const TCHAR* Data) const`
- L710 _private member_ `bool bIsInited = false;`
- L711 _private member_ `void* DllHandle = nullptr;`
- L717 _public prototype_ `DECLFUNC(FInit);`
- L718 _public prototype_ `DECLFUNC(FTick);`
- L719 _public prototype_ `DECLFUNC(FShutdown);`
- L720 _public prototype_ `DECLFUNC(FFreeArray);`
- L721 _public prototype_ `DECLFUNC(FFree);`
- L723 _public prototype_ `DECLFUNC(FCreateMakeInstall);`
- L724 _public prototype_ `DECLFUNC(FMakeManifestFromData);`
- L725 _public prototype_ `DECLFUNC(FDeleteManifest);`
- L726 _public prototype_ `DECLFUNC(FSaveManifestToFile);`
- L727 _public prototype_ `DECLFUNC(FGetBuildFileList);`
- L728 _public prototype_ `DECLFUNC(FGetCustomStringField);`
- L730 _public prototype_ `DECLFUNC(FSetCustomStringField);`
- L731 _public prototype_ `DECLFUNC(FSetCustomDoubleField);`
- L732 _public prototype_ `DECLFUNC(FSetCustomIntField);`
- L734 _public prototype_ `DECLFUNC(FGetAppName);`
- L735 _public prototype_ `DECLFUNC(FGetBuildStats);`
- L736 _public prototype_ `DECLFUNC(FGetTotalDownloaded);`
- L737 _public prototype_ `DECLFUNC(FGetState);`
- L738 _public prototype_ `DECLFUNC(FGetUpdateProgress);`
- L739 _public prototype_ `DECLFUNC(FGetDownloadSpeed);`
- L740 _public prototype_ `DECLFUNC(FGetTotalDownloadRequired);`
- L742 _public prototype_ `DECLFUNC(FCancelInstall);`

#### struct `BpiLib::BpiLibHelpers::FBpiLibHelper::FCallbackStorage`  
`struct FCallbackStorage`  
_L538-544_
- L540 _public function_ `FCallbackStorage(FBuildPatchInstallerDelegate&& InCompleteDelegate) : CompleteDelegate(MoveTemp(InCompleteDelegate))`
- L543 _public member_ `FBuildPatchInstallerDelegate CompleteDelegate;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define RTLD_DEEPBIND 0`
- L32 _namespace_ `namespace BpiLib`
- L34 _namespace_ `namespace BpiLibHelpers` (scope `BpiLib`)
- L206 _namespace_ `namespace BpiLibHelpers` (scope `BpiLib`)
- L209 _function_ `template<typename FuncType> FuncType ImportFunction(const FString& Name, void* DllHandle)` (scope `BpiLib::BpiLibHelpers`)
- L242 _namespace_ `namespace FuncTraits` (scope `BpiLib::BpiLibHelpers`)
- L577 _function_ `return FuncFCreateMakeInstall(ManifestStorage.GetManifestPtr(), &LibCfg, CbStorage, [](const IBuildInstallerRef& Installer, const void* UserPtr) { if (UserPtr) { const FCallbackStorage* ExtCbStorage = static_cast<const FCallbackStorage*>(UserPtr); ExtCbStorage->CompleteDelegate.ExecuteIfBound(Installer); delete ExtCbStorage; } } );` (scope `BpiLib::BpiLibHelpers::FBpiLibHelper::CreateInstaller`)
- L600 _macro_ `#define COPY(__x__) Out.__x__ = InStats->__x__`
- L715 _macro_ `#define DECLFUNC(__x__) TExportedFunc<FuncTraits::__x__> Func##__x__{ DllHandle }` — declare function by a class name

### `Plugins/Fab/Source/Fab/Private/Importers/QuixelGLTFImporter.h` (Private)


#### class `FQuixelGltfImporter`  
`class FQuixelGltfImporter`  
_L8-24_
- L11 _private prototype_ `static void SetupGlobalFoliageActor(const FString& ImportPath);`
- L13 _private prototype_ `static TArray<FSoftObjectPath> GetPipelinesForSourceData(const UInterchangeSourceData* InSourceData);`
- L14 _private prototype_ `static void GeneratePipelines(const TArray<FSoftObjectPath>& OriginalPipelines, TArray<UInterchangePipelineBase*>& GeneratedPipelines);`
- L15 _private prototype_ `static class UInterchangeGenericAssetsPipeline* GetGenericAssetPipeline(const TArray<UInterchangePipelineBase*>& GeneratedPipelines);`
- L16 _private prototype_ `static class UInterchangeMegascansPipeline* GetMegascanPipeline(const TArray<UInterchangePipelineBase*>& GeneratedPipelines);`
- L19 _public prototype_ `static void ImportGltfDecalAsset(const FString& SourcePath, const FString& DestinationPath, TFunction<void(const TArray<UObject*>&)> OnDone);`
- L20 _public prototype_ `static void ImportGltfImperfectionAsset(const FString& SourcePath, const FString& DestinationPath, TFunction<void(const TArray<UObject*>&)> OnDone);`
- L21 _public prototype_ `static void ImportGltfSurfaceAsset(const FString& SourcePath, const FString& DestinationPath, TFunction<void(const TArray<UObject*>&)> OnDone);`
- L22 _public prototype_ `static void ImportGltfPlantAsset(const FString& SourcePath, const FString& DestinationPath, const bool bBuildNanite, TFunction<void(const TArray<UObject*>&)> OnDone);`
- L23 _public prototype_ `static void ImportGltf3DAsset(const FString& SourcePath, const FString& DestinationPath, TFunction<void(const TArray<UObject*>&)> OnDone);`

### `Plugins/Fab/Source/Fab/Private/NotificationProgressWidget.h` (Private)


#### class `SNotificationProgressWidget`  
`class SNotificationProgressWidget : public SCompoundWidget, public INotificationWidget`  
_L20-109_
- inherits: `SCompoundWidget,INotificationWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SNotificationProgressWidget) : _ProgressText(FText::FromString("Downloading Content")) , _HasButton(false)`
- L28 _public prototype_ `SLATE_ARGUMENT(FText, ProgressText);`
- L29 _public prototype_ `SLATE_ARGUMENT(bool, HasButton);`
- L30 _public prototype_ `SLATE_ARGUMENT(FText, ButtonText);`
- L31 _public prototype_ `SLATE_ARGUMENT(FText, ButtonToolTip);`
- L32 _public prototype_ `SLATE_EVENT(FOnClicked, OnButtonClicked);`
- L36 _public function_ `void Construct(const FArguments& InArgs)`
- L84 _public function_ `void SetProgressPercent(const float Percent)`
- L91 _public function_ `void DisableCancel()`
- L97 _public function_ `virtual void OnSetCompletionState(SNotificationItem::ECompletionState) override` — INotificationWidget interface
- L100 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L106 _private member_ `TSharedPtr<SProgressBar> ProgressBar;`
- L107 _private member_ `TSharedPtr<STextBlock> PercentText;`
- L108 _private member_ `TSharedPtr<SButton> CancelButton;`

### `Plugins/Fab/Source/Fab/Private/Pipelines/Factories/InterchangeInstancedFoliageTypeFactory.h` (Private)


#### class `UInterchangeInstancedFoliageTypeFactory`  
`class UInterchangeInstancedFoliageTypeFactory : public UInterchangeFactoryBase`  
_L12-21_
- reflection: `UCLASS()`
- inherits: `UInterchangeFactoryBase`
- L17 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L18 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L19 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L20 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`

### `Plugins/Fab/Source/Fab/Private/Pipelines/InterchangeMegascansPipeline.h` (Private)


#### enum `EMegascanImportType`  
`enum class EMegascanImportType`  
_L32-39_
- reflection: `UENUM()`
- L34 _public enumerator_ `Model3D UMETA(DisplayName = "3D")`
- L35 _public enumerator_ `Surface UMETA(DisplayName = "Surface")`
- L36 _public enumerator_ `Decal UMETA(DisplayName = "Decal")`
- L37 _public enumerator_ `Imperfection UMETA(DisplayName = "Imperfection")`
- L38 _public enumerator_ `Plant UMETA(DisplayName = "Plant")`

#### enum `EMegascanImportTier`  
`enum class EMegascanImportTier: int8`  
_L42-49_
- reflection: `UENUM()`
- L44 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L45 _public enumerator_ `Raw = 0 UMETA(DisplayName = "Raw")`
- L46 _public enumerator_ `High = 1 UMETA(DisplayName = "High")`
- L47 _public enumerator_ `Medium = 2 UMETA(DisplayName = "Medium")`
- L48 _public enumerator_ `Low = 3 UMETA(DisplayName = "Low")`

#### enum `EMegascanMaterialType`  
`enum class EMegascanMaterialType : int32`  
_L52-75_
- reflection: `UENUM()`
- L54 _public enumerator_ `Invalid = 0 UMETA(Hidden)`
- L56 _public enumerator_ `Base UMETA(DisplayName = "3D")`
- L57 _public enumerator_ `BaseMasked UMETA(DisplayName = "3D Masked")`
- L58 _public enumerator_ `BaseFuzz UMETA(DisplayName="3D Fuzz")`
- L59 _public enumerator_ `BaseTransmission UMETA(DisplayName="3D Transmission")`
- L61 _public enumerator_ `Glass UMETA(DisplayName="Glass")`
- L63 _public enumerator_ `Surface UMETA(DisplayName = "Surface")`
- L64 _public enumerator_ `SurfaceMasked UMETA(DisplayName = "Surface Masked")`
- L65 _public enumerator_ `SurfaceFuzz UMETA(DisplayName="Surface Fuzz")`
- L66 _public enumerator_ `SurfaceTransmission UMETA(DisplayName="Surface Transmission")`
- L68 _public enumerator_ `Fabric UMETA(DisplayName="Fabric")`
- L69 _public enumerator_ `FabricMasked UMETA(DisplayName="Fabric Masked")`
- L71 _public enumerator_ `Decal UMETA(DisplayName = "Decal")`
- L73 _public enumerator_ `Plant UMETA(DisplayName = "Plant")`
- L74 _public enumerator_ `PlantBillboard UMETA(DisplayName = "Plant Billboard")`

#### struct `FMegascanMaterialPair`  
`struct FMegascanMaterialPair`  
_L78-87_
- reflection: `USTRUCT()`
- L83 _public member_ `TSoftObjectPtr<UMaterialInterface> StandardMaterial;` — `UPROPERTY(EditAnywhere, Config, Category = "Standard Material", meta = (DisplayName = "Material"))`
- L86 _public member_ `TSoftObjectPtr<UMaterialInterface> VTMaterial;` — `UPROPERTY(EditAnywhere, Config, Category = "Virtual Material", meta = (DisplayName = "Material (with VT support)"))`

#### class `UMegascansMaterialParentSettings`  
`class UMegascansMaterialParentSettings : public UDeveloperSettings`  
_L90-102_
- reflection: `UCLASS(Config=Fab, meta = (DisplayName = "Fab Megascans"))`
- inherits: `UDeveloperSettings`
- L96 _public member_ `TMap<EMegascanMaterialType, FMegascanMaterialPair> MaterialParents;` — `UPROPERTY(EditAnywhere, config, Category = "Parent Materials", meta = (DisplayName = "Megascan Parent Materials"))`
- L101 _public member_ `FString CopiedMaterialVersion;` — `UPROPERTY(config)` — Version of the plugin materials that were last copied into this project. Used to detect breaking changes when the plugin is updated.

#### class `UInterchangeMegascansPipeline`  
`class UInterchangeMegascansPipeline : public UInterchangePipelineBase`  
_L105-195_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangePipelineBase`
- L109 _private prototype_ `UInterchangeMegascansPipeline();`
- L113 _public member_ `EMegascanImportType MegascanImportType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Megascans", meta = (DisplayName = "Megascan Asset Import Type"))`
- L116 _public member_ `TObjectPtr<UMegascansMaterialParentSettings> MegascansMaterialParentSettings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Megascans", meta = (DisplayName = "Megascan Import Settings"))`
- L118 _public function_ `void SetCommonMeshesProperties(TWeakObjectPtr<UInterchangeGenericCommonMeshesProperties> InCommonMeshesProperties)`
- L121 _protected prototype_ `virtual void ExecutePipeline( UInterchangeBaseNodeContainer* NodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION > 3 , const FString& ContentBasePath #endif ) override;`
- L130 _protected prototype_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* NodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L131 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L134 _private prototype_ `bool LoadGltfSource(const FString& SourceFile);`
- L135 _private prototype_ `void ForEachGltfMaterial(const TFunction<void(const FString&, const TSharedPtr<FJsonObject>&)>& Callback) const;`
- L136 _private prototype_ `void ForEachGltfTexture(const TFunction<void(const FString&, const TSharedPtr<FJsonObject>&)>& Callback);`
- L137 _private prototype_ `void ForEachGltfMesh(const TFunction<void(const FString&, const TSharedPtr<FJsonObject>&)>& Callback);`
- L139 _private prototype_ `UInterchangeTextureFactoryNode* FindTextureFactoryNodeByName(const FString& DisplayName) const;`
- L140 _private prototype_ `UInterchangeStaticMeshFactoryNode* FindStaticMeshFactoryNodeByName(const FString& DisplayName) const;`
- L141 _private prototype_ `UInterchangeMaterialInstanceFactoryNode* FindMaterialInstanceFactoryNodeByName(const FString& DisplayName) const;`
- L142 _private prototype_ `const UInterchangeSceneNode* FindSceneNodeInstancingMesh(const UInterchangeStaticMeshFactoryNode* MeshFactoryNode) const;`
- L144 _private prototype_ `const TSharedPtr<FJsonObject>* GetMaterialAtIndex(uint32 Index) const;`
- L146 _private prototype_ `EMegascanMaterialType GetMegascanMaterialType(const UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode) const;`
- L147 _private prototype_ `bool SetMegascanMaterialType(UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode, EMegascanMaterialType MaterialType) const;`
- L148 _private prototype_ `bool UpdateParentMaterial(UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode, bool bVTMaterial = false, bool bUpdateReferencedObject = false);`
- L150 _private prototype_ `FString GetStaticMeshLodDataNodeUid(const UInterchangeMeshFactoryNode* MeshFactoryNode, int32 LodIndex);`
- L151 _private prototype_ `FString GetStaticMeshLodDataNodeDisplayName(int32 LodIndex);`
- L153 _private prototype_ `void SetupMeshLod(UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode, const UInterchangeSceneNode* MeshNode, int32 LodIndex);`
- L155 _private prototype_ `void SetFoliageType(const UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode);`
- L157 _private prototype_ `void SetupTextureParams(UInterchangeTextureFactoryNode* TextureFactoryNode, const TSharedPtr<FJsonObject>& TextureParams);`
- L158 _private prototype_ `void SetupStaticMesh(UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode);`
- L159 _private prototype_ `void SetupStaticMeshParams(const UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode, const TSharedPtr<FJsonObject>& MeshParams);`
- L160 _private prototype_ `void SetupStaticMeshLodScreenSizes(UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode) const;`
- L161 _private prototype_ `void SetupMaterial(UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode);`
- L162 _private prototype_ `void SetupMaterialParams(UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode, const TSharedPtr<FJsonObject>& MaterialParams);`
- L164 _private prototype_ `void SetupMaterialParents(UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode, const FString& CustomType = "");`
- L167 _private function_ `template <class NodeType> TArray<NodeType*> GetNodesOfType()`
- L181 _private member_ `TObjectPtr<UInterchangeBaseNodeContainer> BaseNodeContainer = nullptr;` — `UPROPERTY()`
- L184 _private member_ `TWeakObjectPtr<UInterchangeGenericCommonMeshesProperties> CommonMeshesProperties;` — `UPROPERTY(Transient)`
- L186 _private member_ `EMegascanImportTier MegascanAssetTier = EMegascanImportTier::Invalid;`
- L187 _private member_ `bool bVirtualTexturesImported = false;`
- L190 _private member_ `TSharedPtr<FJsonObject> GltfJson = nullptr;`
- L192 _private member_ `TArray<UInterchangeTextureFactoryNode*> TextureFactoryNodes;`
- L193 _private member_ `TArray<UInterchangeStaticMeshFactoryNode*> StaticMeshFactoryNodes;`
- L194 _private member_ `TArray<UInterchangeMaterialInstanceFactoryNode*> MaterialInstanceFactoryNodes;`

#### Free symbols / members of external scopes

- L172 _function_ `` (scope `UInterchangeMegascansPipeline::GetNodesOfType`)

### `Plugins/Fab/Source/Fab/Private/Pipelines/Nodes/InterchangeInstancedFoliageTypeFactoryNode.h` (Private)


#### class `UInterchangeInstancedFoliageTypeFactoryNode`  
`class UInterchangeInstancedFoliageTypeFactoryNode : public UInterchangeFactoryBaseNode`  
_L12-93_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _public prototype_ `static FString GetNodeUidFromStaticMeshFactoryUid(const FString& StaticMeshFactoryUid);`
- L20 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L23 _public prototype_ `bool GetCustomStaticMesh(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L26 _public prototype_ `bool SetCustomStaticMesh(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L29 _public prototype_ `bool GetCustomScaling(EFoliageScaling& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L32 _public prototype_ `bool SetCustomScaling(const EFoliageScaling AttributeValue, const bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L35 _public prototype_ `bool GetCustomScaleX(FVector2f& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L38 _public prototype_ `bool SetCustomScaleX(const FVector2f& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L41 _public prototype_ `bool GetCustomScaleY(FVector2f& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L44 _public prototype_ `bool SetCustomScaleY(const FVector2f& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L47 _public prototype_ `bool GetCustomScaleZ(FVector2f& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L50 _public prototype_ `bool SetCustomScaleZ(const FVector2f& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L53 _public prototype_ `bool GetCustomAlignToNormal(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L56 _public prototype_ `bool SetCustomAlignToNormal(const bool AttributeValue, const bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L59 _public prototype_ `bool GetCustomRandomYaw(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L62 _public prototype_ `bool SetCustomRandomYaw(const bool AttributeValue, const bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L65 _public prototype_ `bool GetCustomRandomPitchAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L68 _public prototype_ `bool SetCustomRandomPitchAngle(const float AttributeValue, const bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L71 _public prototype_ `bool GetCustomAffectDistanceFieldLighting(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L74 _public prototype_ `bool SetCustomAffectDistanceFieldLighting(const bool AttributeValue, const bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L77 _public prototype_ `bool GetCustomWorldPositionOffsetDisableDistance(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L80 _public prototype_ `bool SetCustomWorldPositionOffsetDisableDistance(const int32 AttributeValue, const bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | InstancedFoliageTypeFactory")`
- L83 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(StaticMesh);`
- L84 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Scaling);`
- L85 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ScaleX);`
- L86 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ScaleY);`
- L87 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ScaleZ);`
- L88 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AlignToNormal);`
- L89 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(RandomYaw);`
- L90 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(RandomPitchAngle);`
- L91 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(bAffectDistanceFieldLighting);`
- L92 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(WorldPositionOffsetDisableDistance);`

### `Plugins/Fab/Source/Fab/Private/Teds/FabContentSource.h` (Private)


#### class `FFabMyLibraryContentSource`  
`class FFabMyLibraryContentSource : public UE::Editor::ContentBrowser::IContentSource`  
_L6-15_
- inherits: `UE::Editor::ContentBrowser::IContentSource`
- L9 _public prototype_ `virtual ~FFabMyLibraryContentSource() override = default;`
- L11 _public prototype_ `virtual FName GetName() override;`
- L12 _public prototype_ `virtual FText GetDisplayName() override;`
- L13 _public prototype_ `virtual FSlateIcon GetIcon() override;`
- L14 _public prototype_ `virtual void GetAssetViewInitParams(UE::Editor::ContentBrowser::FTableViewerInitParams& OutInitParams) override;`

### `Plugins/Fab/Source/Fab/Private/Teds/FabMyFolderIntegration.h` (Private)


#### class `UFabFactory`  
`class UFabFactory : public UEditorDataStorageFactory`  
_L20-30_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L25 _public prototype_ `virtual ~UFabFactory() override = default;`
- L27 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L29 _public member_ `UE::Editor::DataStorage::TableHandle Table;`

#### struct `FFabDistributionMethodTag`  
`struct FFabDistributionMethodTag : public FEditorDataStorageTag`  
_L33-36_
- reflection: `USTRUCT(meta = (DisplayName = "Fab distribution method", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`

#### struct `FFabObjectNameColumn`  
`struct FFabObjectNameColumn : public FEditorDataStorageColumn`  
_L39-45_
- reflection: `USTRUCT(meta = (DisplayName = "Name"))`
- inherits: `FEditorDataStorageColumn`
- L44 _public member_ `FName Name;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FFabObjectColumn`  
`struct FFabObjectColumn : public FEditorDataStorageColumn`  
_L48-72_
- reflection: `USTRUCT(meta = (DisplayName = "Fab object"))`
- inherits: `FEditorDataStorageColumn`
- L53 _public member_ `FString Description;` — `UPROPERTY(meta = (Searchable))`
- L56 _public member_ `FGuid AssetId;` — `UPROPERTY()`
- L59 _public member_ `FGuid AssetNamespace;` — `UPROPERTY()`
- L62 _public member_ `FName ListingType;` — `UPROPERTY(meta = (Searchable))`
- L65 _public member_ `FString Seller;` — `UPROPERTY(meta = (Searchable))`
- L68 _public member_ `FName Source;` — `UPROPERTY()`
- L71 _public member_ `FString UrlString;` — `UPROPERTY()`

#### class `FFabTedsMyFolderIntegration`  
`class FFabTedsMyFolderIntegration`  
_L74-94_
- L77 _public prototype_ `static void QueueSyncRequest();`
- L78 _public prototype_ `static void QueueSyncRequest(uint32 BatchSize);`
- L81 _private typedef_ `using HttpRequestPtr = TSharedPtr<class IHttpRequest, ESPMode::ThreadSafe>;`
- L82 _private typedef_ `using HttpResponsePtr = TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe>;`
- L84 _private prototype_ `static void QueueSyncRequest(const FString& Cursor, uint32 BatchSize);`
- L85 _private prototype_ `static void ProcessSyncResults(uint32 BatchSize, HttpRequestPtr Request, HttpResponsePtr Response, bool bWasSuccessful);`
- L87 _private prototype_ `static void SetNameColumn(FFabObjectNameColumn& Target, const FJsonObject& Object, FString& Temp);`
- L88 _private prototype_ `static void SetFabObjectColumn(FFabObjectColumn& Target, const FJsonObject& Object, FString& Temp);`
- L89 _private prototype_ `static void SetUrlColumn(FEditorDataStorageUrlColumn& Target, const FJsonObject& Object, FString& Temp);`
- L90 _private prototype_ `static void AddDistributionMethod( UE::Editor::DataStorage::ICoreProvider* Storage, UE::Editor::DataStorage::RowHandle Row, const FJsonObject& Object, FString& Temp);`
- L92 _private prototype_ `static void AddImages( UE::Editor::DataStorage::ICoreProvider* Storage, UE::Editor::DataStorage::RowHandle Row, const FJsonObject& Object, FString& Temp);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Fab/Source/Fab/Private/Utilities/DragImportOperation.h` (Private)


#### enum `EDragDropState`  
`enum class EDragDropState`  
_L11-15_
- L13 _public enumerator_ `Dragging`
- L14 _public enumerator_ `Dropped`

#### class `FDragImportOperation`  
`class FDragImportOperation`  
_L17-43_
- L20 _public prototype_ `FDragImportOperation(const UObject* InDraggedObject = nullptr, EDragAssetType InDragAssetType = EDragAssetType::Mesh);`
- L21 _public prototype_ `FDragImportOperation(const FAssetData& InDraggedObject, EDragAssetType InDragAssetType = EDragAssetType::Mesh);`
- L23 _public prototype_ `~FDragImportOperation();`
- L25 _public prototype_ `void InitializeDrag();`
- L27 _public prototype_ `void UpdateDraggedAsset(UObject* InDraggedObject, const EDragAssetType InDragAssetType);`
- L28 _public prototype_ `void UpdateDraggedAsset(const FAssetData& InDraggedObject, const EDragAssetType InDragAssetType);`
- L30 _public prototype_ `void CancelOperation();`
- L32 _public prototype_ `TWeakObjectPtr<AActor> GetSpawnedActor() const;`
- L33 _public prototype_ `void DeleteSpawnedActor() const;`
- L34 _public prototype_ `void ReplaceSpawnedActor() const;`
- L37 _private member_ `FAssetData DraggedAsset;`
- L38 _private member_ `EDragAssetType DragAssetType;`
- L40 _private member_ `EDragDropState DragDropState;`
- L42 _private member_ `TSharedPtr<FFabDragDropOp> DragOperationHandle;`

### `Plugins/Fab/Source/Fab/Private/Utilities/FabLocalAssets.h` (Private)


#### class `UFabLocalAssets`  
`class UFabLocalAssets : public UObject`  
_L15-85_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UObject`
- L21 _public member_ `TMap<FString, FString> PathsListingID;` — `UPROPERTY(config)`
- L22 _public member_ `TMap<FString, FString> ListingIdPath;`
- L25 _public function_ `static void AddLocalAsset(const FString& Path, const FString& AssetID)`
- L55 _public function_ `static const FString* FindPath(const FString& AssetID)`
- L61 _public function_ `static const FString* FindListingID(const FString& Path)`
- L78 _public function_ `static void GetListingID(const FString& Path, FString& AssetID)`

#### Free symbols / members of external scopes

- L33 _function_ `` (scope `UFabLocalAssets::AddLocalAsset`)

### `Plugins/Fab/Source/Fab/Private/Utilities/QuixelAssetTypes.h` (Private)


#### struct `FSemanticTags`  
`struct FSemanticTags`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `FString Asset_Type;` — `UPROPERTY()`

#### struct `FAssetMetaDataJson`  
`struct FAssetMetaDataJson`  
_L19-37_
- reflection: `USTRUCT()`
- L24 _public member_ `FString Id;` — `UPROPERTY()`
- L27 _public member_ `TArray<FString> Categories;` — `UPROPERTY()`
- L30 _public member_ `FSemanticTags SemanticTags;` — `UPROPERTY()`
- L33 _public member_ `float Displacement_Bias_Tier1 = -1.0f;` — `UPROPERTY()`
- L36 _public member_ `float Displacement_Scale_Tier1 = -1.0f;` — `UPROPERTY()`

#### class `FQuixelAssetTypes`  
`class FQuixelAssetTypes`  
_L39-43_
- L42 _public prototype_ `static TTuple<FString, FString> ExtractMeta(const FString& JsonFile, const FString& GltfFile = "");`

### `Plugins/Fab/Source/Fab/Private/Workflows/GenericDragDropWorkflow.h` (Private)


#### class `FGenericDragDropWorkflow`  
`class FGenericDragDropWorkflow : public FGenericImportWorkflow`  
_L10-29_
- inherits: `FGenericImportWorkflow`
- L13 _public prototype_ `FGenericDragDropWorkflow(const FString& InAssetId, const FString& InAssetName);`
- L15 _public prototype_ `virtual void Execute() override;`
- L17 _public prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L19 _public prototype_ `virtual void CompleteWorkflow() override;`
- L20 _public prototype_ `virtual void CancelWorkflow() override;`
- L23 _private prototype_ `bool CheckForCachedAsset(const FString& SearchPath, FAssetData& CachedMeshData) const;`
- L26 _private member_ `FDelegateHandle SignedUrlHandle;`
- L28 _private member_ `TUniquePtr<FDragImportOperation> DragOperation;`

### `Plugins/Fab/Source/Fab/Private/Workflows/GenericImportWorkflow.h` (Private)


#### class `FGenericImportWorkflow`  
`class FGenericImportWorkflow : public IFabWorkflow`  
_L12-32_
- inherits: `IFabWorkflow`
- L15 _public prototype_ `FGenericImportWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InDownloadURL);`
- L17 _public prototype_ `virtual void Execute() override;`
- L20 _protected prototype_ `virtual void ImportContent(const TArray<FString>& SourceFiles) override;`
- L21 _protected prototype_ `virtual void DownloadContent() override;`
- L23 _protected prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L24 _protected prototype_ `virtual void OnContentDownloadComplete(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L26 _protected prototype_ `virtual void CompleteWorkflow() override;`
- L29 _protected member_ `bool bIsDragDropWorkflow = false;`
- L31 _protected member_ `TSharedPtr<FFabDownloadRequest> DownloadRequest;`

### `Plugins/Fab/Source/Fab/Private/Workflows/MetaHumanImportWorkflow.h` (Private)


#### class `FMetaHumanImportWorkflow`  
`class FMetaHumanImportWorkflow : public IFabWorkflow`  
_L11-29_
- inherits: `IFabWorkflow`
- L14 _public prototype_ `FMetaHumanImportWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InDownloadURL);`
- L16 _public prototype_ `virtual void Execute() override;`
- L19 _protected prototype_ `virtual void ImportContent(const TArray<FString>& SourceFiles) override;`
- L20 _protected prototype_ `virtual void DownloadContent() override;`
- L22 _protected prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L23 _protected prototype_ `virtual void OnContentDownloadComplete(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L26 _protected member_ `bool bIsDragDropWorkflow = false;`
- L28 _protected member_ `TSharedPtr<FFabDownloadRequest> DownloadRequest;`

### `Plugins/Fab/Source/Fab/Private/Workflows/PackImportWorkflow.h` (Private)


#### class `FPackImportWorkflow`  
`class FPackImportWorkflow : public IFabWorkflow`  
_L12-31_
- inherits: `IFabWorkflow`
- L15 _public prototype_ `FPackImportWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InManifestDownloadUrl, const FString& InBaseUrls);`
- L17 _public prototype_ `virtual void Execute() override;`
- L20 _protected prototype_ `virtual void DownloadContent() override;`
- L22 _protected prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L23 _protected prototype_ `virtual void OnContentDownloadComplete(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L25 _protected prototype_ `virtual void CreateDownloadNotification() override;`
- L28 _private member_ `FString BaseUrls;`
- L30 _private member_ `TSharedPtr<FFabDownloadRequest> DownloadRequest;`

### `Plugins/Fab/Source/Fab/Private/Workflows/PluginInstallWorkflow.h` (Private)


#### class `FPluginInstallWorkflow`  
`class FPluginInstallWorkflow : public IFabWorkflow`  
_L10-37_
- inherits: `IFabWorkflow`
- L13 _public prototype_ `FPluginInstallWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InManifestDownloadUrl, const FString& InBaseUrls, bool bInInstallToEngine);`
- L15 _public prototype_ `virtual void Execute() override;`
- L18 _protected prototype_ `virtual void DownloadContent() override;`
- L20 _protected prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L21 _protected prototype_ `virtual void OnContentDownloadComplete(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L24 _private prototype_ `virtual void CreateDownloadNotification() override;`
- L25 _private prototype_ `virtual void SetDownloadNotificationProgress(const float Progress) const override;`
- L26 _private prototype_ `virtual void ExpireDownloadNotification(bool bSuccess) const override;`
- L28 _private prototype_ `bool RelocatePlugin(const FFabDownloadStats& DownloadStats, FString& OutPluginName) const;`
- L30 _private member_ `FString BaseUrls;`
- L31 _private member_ `FString DownloadLocation;`
- L32 _private member_ `bool bInstallToEngine = false;`
- L33 _private member_ `TSharedPtr<FFabDownloadRequest> DownloadRequest;`
- L34 _private member_ `TSharedPtr<SNotificationItem> DownloadProgressNotification;`
- L35 _private member_ `TSharedPtr<SNotificationItem> ImportProgressNotification;`
- L36 _private member_ `TSharedPtr<SNotificationProgressWidget> ProgressWidget;`

### `Plugins/Fab/Source/Fab/Private/Workflows/QuixelDragDropWorkflow.h` (Private)


#### class `FQuixelDragDropWorkflow`  
`class FQuixelDragDropWorkflow : public FQuixelImportWorkflow`  
_L11-31_
- inherits: `FQuixelImportWorkflow`
- L14 _public prototype_ `FQuixelDragDropWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InListingType);`
- L16 _public prototype_ `virtual void Execute() override;`
- L18 _public prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L20 _public prototype_ `virtual void CompleteWorkflow() override;`
- L21 _public prototype_ `virtual void CancelWorkflow() override;`
- L24 _private prototype_ `bool CheckForCachedAsset(const FString& SearchPath, FAssetData& CachedMeshData) const;`
- L26 _private member_ `FString ListingType;`
- L28 _private member_ `FDelegateHandle SignedUrlHandle;`
- L30 _private member_ `TUniquePtr<FDragImportOperation> DragOperation;`

### `Plugins/Fab/Source/Fab/Private/Workflows/QuixelImportWorkflow.h` (Private)


#### class `FQuixelImportWorkflow`  
`class FQuixelImportWorkflow : public IFabWorkflow`  
_L15-37_
- inherits: `IFabWorkflow`
- L18 _public prototype_ `FQuixelImportWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InDownloadURL);`
- L20 _public prototype_ `virtual void Execute() override;`
- L23 _protected prototype_ `void CopyMaterialsToProject();`
- L25 _protected prototype_ `virtual void ImportContent(const TArray<FString>& SourceFiles) override;`
- L26 _protected prototype_ `virtual void DownloadContent() override;`
- L28 _protected prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L29 _protected prototype_ `virtual void OnContentDownloadComplete(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) override;`
- L31 _protected prototype_ `virtual void CompleteWorkflow() override;`
- L34 _protected member_ `bool bIsDragDropWorkflow = false;`
- L36 _protected member_ `TSharedPtr<FFabDownloadRequest> DownloadRequest;`

### `Plugins/Fab/Source/Fab/Public/FabDownloader.h` (Public)


#### enum `EFabDownloadType`  
`enum class EFabDownloadType`  
_L21-31_
- L24 _public enumerator_ `HTTP` — Download asset using HTTP
- L27 _public enumerator_ `BuildPatchRequest` — Download asset using BuildPatchServices (for Unreal Engine Marketplace Assets)
- L30 _public enumerator_ `BuildPatchInstallRequest` — Install plugin using BuildPatchServices (for Unreal Engine Marketplace Plugins)

#### struct `FFabDownloadStats`  
`struct FFabDownloadStats`  
_L33-49_
- L35 _public member_ `float PercentComplete = 0.0f;`
- L37 _public member_ `uint64 CompletedBytes = 0;`
- L38 _public member_ `uint64 TotalBytes = 0;`
- L40 _public member_ `uint64 DownloadStartedAt = 0;`
- L41 _public member_ `uint64 DownloadCompletedAt = 0;`
- L43 _public member_ `float DownloadSpeed = 0.0f;`
- L45 _public member_ `bool bIsSuccess = false;`
- L46 _public member_ `bool bIsCached = false;`
- L48 _public member_ `TArray<FString> DownloadedFiles;`

#### class `FFabDownloadRequest`  
`class FFabDownloadRequest`  
_L51-110_
- L53 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadProgress, const FFabDownloadRequest*, const FFabDownloadStats&);`
- L54 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadComplete, const FFabDownloadRequest*, const FFabDownloadStats&);`
- L57 _private prototype_ `FString GetFilenameFromURL(const FString& URL);`
- L59 _private prototype_ `void ExecuteHTTPRequest();`
- L61 _private prototype_ `static bool LoadBuildPatchServices();`
- L62 _private prototype_ `void ExecuteBuildPatchRequest();`
- L63 _private prototype_ `void ExecuteBuildPatchInstallRequest();`
- L64 _private prototype_ `void OnPackManifestDownloaded(const FString& BaseURL);`
- L65 _private prototype_ `void OnPluginManifestDownloaded(const FString& BaseURL);`
- L67 _private prototype_ `void StartDownload();`
- L70 _public prototype_ `FFabDownloadRequest(const FString& AssetID, const FString& InDownloadURL, const FString& InDownloadLocation, EFabDownloadType InDownloadType = EFabDownloadType::HTTP);`
- L73 _public prototype_ `~FFabDownloadRequest() = default;`
- L75 _public prototype_ `void ExecuteRequest();`
- L76 _public prototype_ `void Cancel();`
- L78 _public prototype_ `static void ShutdownBpsModule();`
- L80 _public function_ `const FFabDownloadStats& GetDownloadStats()`
- L82 _public function_ `FOnDownloadProgress& OnDownloadProgress()`
- L83 _public function_ `FOnDownloadComplete& OnDownloadComplete()`
- L86 _private member_ `FString AssetID;`
- L88 _private member_ `FString DownloadURL;`
- L90 _private member_ `FString DownloadLocation;`
- L92 _private member_ `EFabDownloadType DownloadType;`
- L94 _private member_ `FFabDownloadStats DownloadStats;`
- L96 _private member_ `FOnDownloadProgress OnDownloadProgressDelegate;`
- L97 _private member_ `FOnDownloadComplete OnDownloadCompleteDelegate;`
- L99 _private member_ `FHttpRequestPtr DownloadRequest;`
- L100 _private member_ `IBuildInstallerPtr BpsInstaller;`
- L102 _private member_ `bool bPendingCancel = false;`
- L104 _private member_ `TArray<uint8> ManifestData;`
- L105 _private member_ `FTSTicker::FDelegateHandle BpsProgressTickerHandle;`
- L106 _private member_ `static FTSTicker::FDelegateHandle BpsTickerHandle;`
- L107 _private member_ `static TUniquePtr<BpiLib::IBpiLib> BuildPatchServices;`

#### class `FFabDownloadQueue`  
`class FFabDownloadQueue`  
_L112-121_
- L115 _private member_ `static int32 DownloadQueueLimit;`
- L116 _private member_ `static TSet<FFabDownloadRequest*> DownloadQueue;`
- L117 _private member_ `static TQueue<FFabDownloadRequest*> WaitingQueue;`
- L120 _public prototype_ `static void AddDownloadToQueue(FFabDownloadRequest* DownloadRequest);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API FAB_API`
- L14 _namespace_ `namespace BpiLib`
- L19 _typedef_ `typedef TSharedPtr<class IBuildInstaller, ESPMode::ThreadSafe> IBuildInstallerPtr;`
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadProgress, const FFabDownloadRequest*, const FFabDownloadStats&);`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDownloadComplete, const FFabDownloadRequest*, const FFabDownloadStats&);`

### `Plugins/Fab/Source/Fab/Public/FabModule.h` (Public)


#### class `IFabModule`  
`class IFabModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L12 _public function_ `static inline IFabModule& Get()`
- L17 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define MS_MODULE_NAME TEXT("Fab")`

### `Plugins/Fab/Source/Fab/Public/FabWorkflowFactoryRegistry.h` (Public)


#### class `FFabWorkflowFactoryRegistry`  
`class FFabWorkflowFactoryRegistry`  
_L11-22_
- L14 _public prototype_ `static bool RegisterFactory(const TSharedPtr<IFabWorkflowFactory>& InFactory);`
- L15 _public prototype_ `static void UnregisterFactory(const TSharedPtr<IFabWorkflowFactory>& InFactory);`
- L17 _public prototype_ `static const TSharedPtr<IFabWorkflowFactory>& GetFactory(const FString& ImportType);`
- L18 _public prototype_ `static bool IsAssetTypeRegistered(const FString& AssetType);`
- L21 _private member_ `static TMap<FString, TSharedPtr<IFabWorkflowFactory>> Factories;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FAB_API`

### `Plugins/Fab/Source/Fab/Public/Importers/ActorSpawner.h` (Public)


#### class `UFabPlaceholderSpawner`  
`class UFabPlaceholderSpawner : public UActorFactory`  
_L16-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnActorSpawn, AActor*);`
- L22 _public function_ `FOnActorSpawn& OnActorSpawn()`
- L25 _protected member_ `FOnActorSpawn OnActorSpawnDelegate;`

#### class `UFabStaticMeshPlaceholderSpawner`  
`class UFabStaticMeshPlaceholderSpawner : public UFabPlaceholderSpawner`  
_L29-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFabPlaceholderSpawner`
- L33 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L34 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L35 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* Instance) override;`

#### class `UFabSkeletalMeshPlaceholderSpawner`  
`class UFabSkeletalMeshPlaceholderSpawner : public UFabPlaceholderSpawner`  
_L39-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFabPlaceholderSpawner`
- L43 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L44 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L45 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* Instance) override;`

#### class `UFabDecalPlaceholderSpawner`  
`class UFabDecalPlaceholderSpawner : public UFabPlaceholderSpawner`  
_L49-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFabPlaceholderSpawner`
- L53 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L54 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L55 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* Instance) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API FAB_API`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActorSpawn, AActor*);`

### `Plugins/Fab/Source/Fab/Public/Importers/FabDragDropOp.h` (Public)


#### enum `EDragAssetType`  
`enum class EDragAssetType`  
_L13-18_
- L15 _public enumerator_ `Mesh`
- L16 _public enumerator_ `Material`
- L17 _public enumerator_ `Decal`

#### class `FFabDragDropOp`  
`class FFabDragDropOp : public FAssetDragDropOp`  
_L20-56_
- inherits: `FAssetDragDropOp`
- L23 _public prototype_ `DECLARE_DELEGATE(FOnDrop);`
- L24 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FFabDragDropOp, FAssetDragDropOp) static TSharedPtr<FFabDragDropOp> New(FAssetData Asset, EDragAssetType InDragAssetType);`
- L28 _public prototype_ `FFabDragDropOp(const EDragAssetType InDragAssetType);`
- L31 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L32 _public function_ `FOnDrop& OnDrop()`
- L34 _public function_ `void SetCanDropHere(bool bCanDropHere)`
- L39 _public prototype_ `virtual void Construct() override;`
- L41 _public prototype_ `void Cancel();`
- L42 _public prototype_ `void DestroyWindow();`
- L43 _public prototype_ `void DestroySpawnedActor();`
- L45 _public prototype_ `virtual void OnDragged(const FDragDropEvent& DragDropEvent) override;`
- L46 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L48 _public member_ `TWeakObjectPtr<AActor> SpawnedActor;`
- L51 _protected member_ `FOnDrop OnDropDelegate;`
- L54 _private member_ `EDragAssetType DragAssetType;`
- L55 _private member_ `FDelegateHandle EditorApplyHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API FAB_API`
- L23 _delegate_ `DECLARE_DELEGATE(FOnDrop);`

### `Plugins/Fab/Source/Fab/Public/Importers/GenericAssetImporter.h` (Public)


#### class `FFabGenericImporter`  
`class FFabGenericImporter`  
_L12-20_
- L15 _private prototype_ `static UObject* GetImportOptions(const FString& SourceFile, UObject* const OptionsOuter);`
- L16 _private prototype_ `static void CleanImportOptions(UObject* const Options);`
- L19 _public prototype_ `static void ImportAsset(const TArray<FString>& Sources, const FString& Destination, const TFunction<void(const TArray<UObject*>&)>& Callback);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FAB_API`

### `Plugins/Fab/Source/Fab/Public/Utilities/AssetUtils.h` (Public)


#### class `FAssetUtils`  
`class FAssetUtils`  
_L9-18_
- L12 _public prototype_ `static void SanitizeFolderName(FString& AssetID);`
- L13 _public prototype_ `static void SanitizePath(FString& Path);`
- L14 _public prototype_ `static bool Unzip(const FString& Path, const FString& TargetPath);`
- L15 _public prototype_ `static void ScanForAssets(const FString& FolderPath);`
- L16 _public prototype_ `static void SyncContentBrowserToFolder(const FString& FolderPath, const bool bFocusContentBrowser = true);`
- L17 _public prototype_ `static void SyncContentBrowserToFolders(const TArray<FString>& Folders, const bool bFocusContentBrowser = true);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FAB_API`

### `Plugins/Fab/Source/Fab/Public/Utilities/FabAssetsCache.h` (Public)


#### class `FFabAssetsCache`  
`class FFabAssetsCache`  
_L9-23_
- L12 _private member_ `static int64 CacheExpirationTimeoutInDays;`
- L15 _public prototype_ `static FString GetCacheLocation();`
- L16 _public prototype_ `static TArray<FString> GetCachedAssets();`
- L17 _public prototype_ `static int64 GetCacheSize();`
- L18 _public prototype_ `static FText GetCacheSizeString();`
- L19 _public prototype_ `static void ClearCache();`
- L20 _public prototype_ `static bool IsCached(const FString& AssetId, int64 DownloadSize);`
- L21 _public prototype_ `static FString GetCachedFile(const FString AssetId);`
- L22 _public prototype_ `static FString CacheAsset(const FString& DownloadedAssetPath);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FAB_API`

### `Plugins/Fab/Source/Fab/Public/Workflows/FabWorkflow.h` (Public)


#### struct `FFabAssetMetadata`  
`struct FFabAssetMetadata`  
_L17-41_
- reflection: `USTRUCT()`
- L22 _public member_ `FString AssetId;` — `UPROPERTY()`
- L25 _public member_ `FString AssetName;` — `UPROPERTY()`
- L28 _public member_ `FString AssetType;` — `UPROPERTY()`
- L31 _public member_ `FString ListingType;` — `UPROPERTY()`
- L34 _public member_ `FString AssetNamespace;` — `UPROPERTY()`
- L37 _public member_ `TArray<FString> DistributionPointBaseUrls;` — `UPROPERTY()`
- L40 _public member_ `bool IsQuixel = false;` — `UPROPERTY()`

#### class `IFabWorkflow`  
`class IFabWorkflow : public TSharedFromThis<IFabWorkflow>`  
_L43-120_
- inherits: `TSharedFromThis<IFabWorkflow>`
- L46 _public prototype_ `DECLARE_DELEGATE(FOnFabWorkflowComplete);`
- L47 _public prototype_ `DECLARE_DELEGATE(FOnFabWorkflowCancel);`
- L50 _public function_ `IFabWorkflow(const FString& InAssetId, const FString& InAssetName, const FString& InDownloadUrl) : AssetId(InAssetId) , AssetName(InAssetName) , DownloadUrl(InDownloadUrl)`
- L56 _public prototype_ `virtual ~IFabWorkflow() = default;`
- L58 _public prototype_ `virtual void Execute() = 0;`
- L60 _public function_ `FOnFabWorkflowComplete& OnFabWorkflowComplete()`
- L61 _public function_ `FOnFabWorkflowCancel& OnFabWorkflowCancel()`
- L63 _public function_ `virtual const TArray<UObject*>& GetImportedObjects() const`
- L66 _public function_ `template <class T> T* GetImportedObjectOfType() const`
- L76 _protected function_ `virtual void ImportContent(const TArray<FString>& SourceFiles)`
- L77 _protected prototype_ `virtual void DownloadContent() = 0;`
- L79 _protected prototype_ `virtual void OnContentDownloadProgress(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) = 0;`
- L80 _protected prototype_ `virtual void OnContentDownloadComplete(const FFabDownloadRequest* Request, const FFabDownloadStats& DownloadStats) = 0;`
- L85 _protected function_ `virtual void CompleteWorkflow()` — Deferred via AsyncTask so the current call stack unwinds before the delegate fires, which may release the last shared reference to this workflow. Captures a shared pointer to prevent premature destruction.
- L90 _protected function_ `virtual void CancelWorkflow()`
- L96 _protected prototype_ `virtual void CreateDownloadNotification();`
- L97 _protected prototype_ `virtual void SetDownloadNotificationProgress(const float Progress) const;`
- L98 _protected prototype_ `virtual void ExpireDownloadNotification(bool bSuccess) const;`
- L100 _protected prototype_ `virtual void CreateImportNotification();`
- L101 _protected prototype_ `virtual void ExpireImportNotification(bool bSuccess) const;`
- L104 _public member_ `FString AssetId;`
- L107 _protected member_ `FString AssetName;`
- L108 _protected member_ `FString DownloadUrl;`
- L110 _protected member_ `FString ImportLocation;`
- L111 _protected member_ `TArray<UObject*> ImportedObjects;`
- L113 _protected member_ `TSharedPtr<SNotificationItem> DownloadProgressNotification;`
- L114 _protected member_ `TSharedPtr<SNotificationItem> ImportProgressNotification;`
- L115 _protected member_ `TSharedPtr<SNotificationProgressWidget> ProgressWidget;`
- L118 _private member_ `FOnFabWorkflowComplete OnFabWorkflowCompleteDelegate;`
- L119 _private member_ `FOnFabWorkflowCancel OnFabWorkflowCancelDelegate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API FAB_API`
- L46 _delegate_ `DECLARE_DELEGATE(FOnFabWorkflowComplete);`
- L47 _delegate_ `DECLARE_DELEGATE(FOnFabWorkflowCancel);`
- L68 _function_ `if (UObject* const* FoundObject = ImportedObjects.FindByPredicate([](const auto& O) { return O->IsA(T::StaticClass()); }))` (scope `IFabWorkflow::GetImportedObjectOfType`)
- L88 _function_ `AsyncTask(ENamedThreads::GameThread, [Self]() { Self->OnFabWorkflowComplete().ExecuteIfBound(); });` (scope `IFabWorkflow::CompleteWorkflow`)
- L93 _function_ `AsyncTask(ENamedThreads::GameThread, [Self]() { Self->OnFabWorkflowCancel().ExecuteIfBound(); });` (scope `IFabWorkflow::CancelWorkflow`)

### `Plugins/Fab/Source/Fab/Public/Workflows/FabWorkflowFactory.h` (Public)


#### class `IFabWorkflowFactory`  
`class IFabWorkflowFactory`  
_L7-27_
- L10 _public prototype_ `IFabWorkflowFactory() = default;`
- L11 _public prototype_ `virtual ~IFabWorkflowFactory() = default;`
- L13 _public prototype_ `IFabWorkflowFactory(const IFabWorkflowFactory&) = delete;`
- L14 _public prototype_ `IFabWorkflowFactory(IFabWorkflowFactory&&) = delete;`
- L16 _public prototype_ `IFabWorkflowFactory& operator=(const IFabWorkflowFactory&) = delete;`
- L17 _public prototype_ `IFabWorkflowFactory& operator=(IFabWorkflowFactory&&) = delete;`
- L19 _public function_ `virtual bool CanImportAssetType(const FString& InAssetType)`
- L24 _public prototype_ `virtual const TArray<FString>& GetImportAssetTypes() = 0;`
- L26 _public prototype_ `virtual TSharedPtr<IFabWorkflow> Create(const FFabAssetMetadata& InImportAssetMetadata, const FString& InDownloadUrl = "") = 0;`
