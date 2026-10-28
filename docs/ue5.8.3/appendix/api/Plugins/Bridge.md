# Plugins / Bridge

- module root: `Plugins/Bridge/Source/Bridge`
- headers: 8; symbols: 116
- symbol kinds: class=9, delegate=6, function=2, macro=1, member=36, prototype=61, struct=1
- PublicDependencyModuleNames: ApplicationCore, ContentBrowserData, Core, CoreUObject, Engine, InputCore, Json, MegascansPlugin, MetaHumanSDKEditor, Networking, PlacementMode, Projects, RHI, RenderCore, Slate, SlateCore, Sockets, ToolMenus, UMG, UnrealEd, WebBrowser

### `Plugins/Bridge/Source/Bridge/Private/NodeCommManager.h` (Private)


#### class `FNodeCommManager`  
`class FNodeCommManager`  
_L5-15_
- L8 _private prototype_ `FNodeCommManager() = default;`
- L9 _private member_ `static TSharedPtr<FNodeCommManager> NodeCommManager;`
- L12 _public prototype_ `static TSharedPtr<FNodeCommManager> Get();`
- L13 _public prototype_ `void NodeDataReceived(const FString& NodeData);`

#### struct `FBifrostNodeInfo`  
`struct FBifrostNodeInfo`  
_L19-28_
- reflection: `USTRUCT()`
- desc: Dummy data structure, all json data to be converted to ustructs
- L24 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere,Category = "NodeData")`
- L27 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category = "NodeData")`

### `Plugins/Bridge/Source/Bridge/Private/NodePort.h` (Private)


#### class `UNodePort`  
`class UNodePort : public UObject`  
_L8-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- L13 _public member_ `FString PortFilePath = FPaths::Combine(FPaths::EnginePluginsDir(), TEXT("Bridge"), TEXT("ThirdPar`
- L14 _public member_ `bool bIsNodeRunning;`
- L16 _public prototype_ `FString GetNodePort();` — `UFUNCTION()`
- L19 _public prototype_ `bool IsNodeRunning();` — `UFUNCTION()`

### `Plugins/Bridge/Source/Bridge/Private/NodeProcess.h` (Private)


#### class `FNodeProcessManager`  
`class FNodeProcessManager`  
_L9-27_
- L12 _private prototype_ `FNodeProcessManager() = default;`
- L13 _private member_ `static TSharedPtr<FNodeProcessManager> NodeProcessManager;`
- L15 _private member_ `const FString BridgePluginName = TEXT("Bri`
- L16 _private member_ `uint32 OutProcessId = 0;`
- L17 _private member_ `FProcHandle NodeProcessHandle;`
- L19 _private prototype_ `const FString GetProcessURL() const;`
- L20 _private prototype_ `const FString GetPluginPath() const;`
- L23 _public prototype_ `static TSharedPtr<FNodeProcessManager> Get();`
- L24 _public member_ `TArray<NodeProcessRunnableThread*> NodeThreads;`
- L25 _public prototype_ `void StartNodeProcess();`
- L26 _public prototype_ `void RestartNodeProcess();`

### `Plugins/Bridge/Source/Bridge/Private/NodeProcessRunnableThread.h` (Private)


#### class `NodeProcessRunnableThread`  
`class NodeProcessRunnableThread : public FRunnable`  
_L7-19_
- inherits: `FRunnable`
- L10 _public prototype_ `NodeProcessRunnableThread();`
- L11 _public prototype_ `virtual ~NodeProcessRunnableThread();`
- L14 _public prototype_ `virtual uint32 Run() override;` — FRunnable functions
- L17 _protected member_ `FRunnableThread* Thread = nullptr;`
- L18 _protected member_ `bool bStopThread = false;`

### `Plugins/Bridge/Source/Bridge/Private/UI/BridgeStyle.h` (Private)


#### class `FBridgeStyle`  
`class FBridgeStyle`  
_L7-22_
- L10 _public prototype_ `static void Initialize();`
- L11 _public prototype_ `static void Shutdown();`
- L13 _public prototype_ `static const ISlateStyle& Get();`
- L14 _public prototype_ `static FName GetStyleSetName();`
- L15 _public prototype_ `static FName GetContextName();`
- L17 _public prototype_ `static void SetIcon(const FString& StyleName, const FString& ResourcePath);`
- L18 _public prototype_ `static void SetSVGIcon(const FString& StyleName, const FString& ResourcePath);`
- L20 _private prototype_ `static TUniquePtr<FSlateStyleSet> Create();`
- L21 _private member_ `static TUniquePtr<FSlateStyleSet> MSStyleInstance;`

### `Plugins/Bridge/Source/Bridge/Private/UI/BridgeUIManager.h` (Private)


#### class `FBridgeUIManagerImpl`  
`class FBridgeUIManagerImpl : public TSharedFromThis<FBridgeUIManagerImpl>`  
_L19-39_
- inherits: `TSharedFromThis<FBridgeUIManagerImpl>`
- L22 _public prototype_ `void Initialize();`
- L23 _public prototype_ `void Shutdown();`
- L24 _public prototype_ `void HandleBrowserUrlChanged(const FText& Url);`
- L25 _public member_ `TSharedPtr<SWebBrowser> WebBrowserWidget;`
- L26 _public member_ `TSharedPtr<SDockTab> LocalBrowserDock;`
- L27 _public member_ `TSharedPtr<SWindow> DragDropWindow;`
- L30 _private prototype_ `void SetupMenuItem();`
- L31 _private prototype_ `void CreateWindow();`
- L32 _private prototype_ `TSharedRef<SDockTab> CreateBridgeTab(const FSpawnTabArgs& Args);`
- L33 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L34 _private prototype_ `void AddPluginMenu(FMenuBuilder& MenuBuilder);`
- L37 _protected member_ `const FText BridgeTabDisplay = FText::FromString("Bri`
- L38 _protected member_ `const FText BridgeToolTip = FText::FromString("Lau`

#### class `FBridgeUIManager`  
`class FBridgeUIManager`  
_L41-48_
- L44 _public prototype_ `static void Initialize();`
- L45 _public prototype_ `static void Shutdown();`
- L46 _public member_ `static TSharedPtr<FBridgeUIManagerImpl> Instance;`
- L47 _public member_ `static UBrowserBinding* BrowserBinding;`

### `Plugins/Bridge/Source/Bridge/Private/UI/BrowserBinding.h` (Private)


#### class `UBrowserBinding`  
`class UBrowserBinding : public UObject`  
_L23-115_
- reflection: `UCLASS()`
- inherits: `UObject`
- L28 _private prototype_ `void SwitchDragDropOp(TArray<FString> URLs, TSharedRef<FAssetDragDropOp> DragDropOperation);`
- L30 _private prototype_ `void OnNewActorsDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors);`
- L31 _private prototype_ `void OnApplyObjectToActor(UObject* DroppedObj, AActor* TargetActor);`
- L34 _public member_ `FOnDialogSuccess DialogSuccessDelegate;`
- L35 _public member_ `FOnDialogFail DialogFailDelegate;`
- L36 _public member_ `FOnDropped OnDroppedDelegate;`
- L37 _public member_ `FOnDropDiscarded OnDropDiscardedDelegate;`
- L38 _public member_ `FOnExit OnExitDelegate;`
- L39 _public member_ `FOnBulkExportMetahumans OnBulkExportMetahumansDelegate;`
- L41 _public member_ `TSharedPtr<SWindow> DialogMainWindow;`
- L42 _public member_ `TSharedPtr<SWebBrowser> DialogMainBrowser;`
- L45 _public prototype_ `void DialogSuccessCallback(FWebJSFunction DialogJSCallback);` — `UFUNCTION()`
- L48 _public prototype_ `void DialogFailCallback(FWebJSFunction DialogJSCallback);` — `UFUNCTION()`
- L51 _public prototype_ `void OnDroppedCallback(FWebJSFunction OnDroppedJSCallback);` — `UFUNCTION()`
- L54 _public prototype_ `void OnDropDiscardedCallback(FWebJSFunction OnDropDiscardedJSCallback);` — `UFUNCTION()`
- L57 _public prototype_ `void OnExitCallback(FWebJSFunction OnExitJSCallback);` — `UFUNCTION()`
- L60 _public prototype_ `void OnBulkExportMetahumansCallback(FWebJSFunction OnBulkExportMetahumansJSCallback);` — `UFUNCTION()`
- L63 _public prototype_ `void SaveAuthToken(FString Value);` — `UFUNCTION()`
- L66 _public prototype_ `FString GetAuthToken();` — `UFUNCTION()`
- L69 _public prototype_ `void SendSuccess(FString Value);` — `UFUNCTION()`
- L72 _public prototype_ `void SendFailure(FString Message);` — `UFUNCTION()`
- L75 _public prototype_ `void ShowDialog(FString Type, FString Url);` — `UFUNCTION()`
- L78 _public prototype_ `void DragStarted(TArray<FString> ImageUrl, TArray<FString> IDs, TArray<FString> Types);` — `UFUNCTION()`
- L81 _public prototype_ `void ShowLoginDialog(FString LoginUrl, FString ResponseCodeUrl);` — `UFUNCTION()`
- L84 _public prototype_ `void OpenExternalUrl(FString Url);` — `UFUNCTION()`
- L87 _public prototype_ `void ExportDataToMSPlugin(FString Data);` — `UFUNCTION()`
- L90 _public prototype_ `FString GetProjectPath();` — `UFUNCTION()`
- L93 _public prototype_ `void Logout();` — `UFUNCTION()`
- L96 _public prototype_ `void StartNodeProcess();` — `UFUNCTION()`
- L99 _public prototype_ `void RestartNodeProcess();` — `UFUNCTION()`
- L102 _public prototype_ `void OpenMegascansPluginSettings();` — `UFUNCTION()`
- L106 _public member_ `bool bWasSwitchDragOperation = false;`
- L107 _public member_ `bool bIsDragging = false;`
- L108 _public member_ `bool bIsDropEventBound = false;`
- L110 _public member_ `TArray<FAssetData> InAssetData;`
- L111 _public member_ `TArray<FString> DragDropIDs;`
- L112 _public member_ `TArray<FString> DragDropTypes;`
- L113 _public member_ `TMap<FString, AActor*> AssetToSphereMap;`
- L114 _public member_ `TMap<FString, TArray<FString>> DragOperationToAssetsMap;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDialogSuccess, FString, FString);`
- L15 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnDialogSuccess, FString, FString);`
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDialogFail, FString, FString);`
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnDialogFail, FString, FString);`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDropped, FString);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDropped, FString);`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDropDiscarded, FString);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDropDiscarded, FString);`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExit, FString);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnExit, FString);`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBulkExportMetahumans, TArray<FString>);`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBulkExportMetahumans, TArray<FString>);`

### `Plugins/Bridge/Source/Bridge/Public/IBridgeModule.h` (Public)


#### class `IBridgeModule`  
`class IBridgeModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L12 _public function_ `static inline IBridgeModule& Get()`
- L17 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L6 _macro_ `#define MS_MODULE_NAME TEXT("Bridge")`
