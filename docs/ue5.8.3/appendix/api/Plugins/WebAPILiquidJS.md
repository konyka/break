# Plugins / WebAPILiquidJS

- module root: `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS`
- headers: 7; symbols: 46
- symbol kinds: class=5, delegate=2, enum=1, enumerator=4, function=2, member=17, prototype=15
- PrivateDependencyModuleNames: AssetRegistry, DeveloperSettings, EditorStyle, EditorWidgets, Engine, HTTP, InputCore, Projects, Slate, SlateCore, Sockets, UnrealEd, WebAPI, WebAPIEditor, WebSocketNetworking
- PublicDependencyModuleNames: AssetTools, Core, CoreUObject, Engine, Json, JsonUtilities

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSCodeGenerator.h` (Private)


#### class `UWebAPILiquidJSCodeGenerator`  
`class UWebAPILiquidJSCodeGenerator : public UWebAPICodeGeneratorBase`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UWebAPICodeGeneratorBase`
- L19 _public prototype_ `virtual TFuture<bool> IsAvailable() override;`
- L20 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> GenerateFile(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TSharedPtr<FWebAPICodeGenFile>& InFile) override;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPILiquidJS, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPILiquidJS, Log, All);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSModule.h` (Private)


#### class `FWebAPILiquidJSModule`  
`class FWebAPILiquidJSModule final : public IWebAPILiquidJSModuleInterface`  
_L9-21_
- inherits: `IWebAPILiquidJSModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `bool TryStartWebApp() const;`
- L20 _private member_ `TSharedPtr<class FWebAPILiquidJSProcess> WebApp;` — The actual process that runs the middleman server.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSProcess.h` (Private)


#### class `FWebAPILiquidJSProcess`  
`class FWebAPILiquidJSProcess : private FRunnable`  
_L13-63_
- inherits: `FRunnable`
- L26 _public prototype_ `FWebAPILiquidJSProcess();`
- L28 _public prototype_ `virtual ~FWebAPILiquidJSProcess() override = default;`
- L31 _public prototype_ `bool TryStart();` — Starts the webapp external process, first launch will take some time as it needs to compile the webapp
- L34 _public prototype_ `void Shutdown();` — Shutdown the webapp external process
- L37 _public prototype_ `EStatus GetStatus() const;` — Get the webapp's status.
- L40 _public prototype_ `void SetExternalLoggerEnabled(bool bEnableExternalLog) const;` — Enable / disable external logger
- L43 _protected prototype_ `virtual uint32 Run() override;`
- L47 _private member_ `FString Root;` — Plugin root folder
- L50 _private member_ `FProcHandle Process;` — WebApp Node.js process handle
- L53 _private member_ `FRunnableThread* Thread = nullptr;` — Thread for WebApp node.js process (read stdout and forward to log)
- L56 _private member_ `TUniquePtr<FAsyncTaskNotification> TaskNotification;` — Progress notification
- L59 _private member_ `std::atomic<EStatus> Status;` — The current status of the web app.
- L62 _private member_ `std::atomic<bool> bForceBuildWebApp;` — Can by used override Settings for retry.

#### enum `FWebAPILiquidJSProcess::EStatus`  
`enum class EStatus : uint8`  
_L16-23_
- L18 _public enumerator_ `Stopped = 0`
- L19 _public enumerator_ `Error = 1`
- L21 _public enumerator_ `Launching = 2`
- L22 _public enumerator_ `Running = 3`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSSettings.h` (Private)


#### class `UWebAPILiquidJSSettings`  
`class UWebAPILiquidJSSettings : public UDeveloperSettings`  
_L10-64_
- reflection: `UCLASS(BlueprintType, Config = Engine, DefaultConfig, meta = (DisplayName = "WebAPI LiquidJS"))`
- inherits: `UDeveloperSettings`
- L15 _public function_ `virtual FName GetContainerName() const override`
- L16 _public function_ `virtual FName GetCategoryName() const override`
- L20 _public member_ `uint32 Port = 33000;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Service")` — The web app http port.
- L24 _public member_ `bool bForceWebAppBuildAtStartup = false;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Service")` — Should force a build of the WebApp at startup.
- L28 _public member_ `bool bWebAppLogRequestDuration = false;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service")` — Should WebApp log timing.
- L32 _public member_ `bool bAutoStartWebServer = true;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service")` — Whether web server is started automatically.
- L36 _public member_ `bool bAutoStartWebSocketServer = true;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service")` — Whether web socket server is started automatically.
- L40 _public member_ `uint32 HttpServerPort = 33010;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service")` — The HTTP server's port.
- L44 _public member_ `uint32 WebSocketServerPort = 33020;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service")` — The WebSocket server's port.
- L47 _public prototype_ `FString GetServiceUrl(const FString& InSubPath = {});` — Returns a formatted Url.
- L50 _public prototype_ `FString GetServiceUrl(const FString& InSubPath = {}) const;` — Returns a formatted Url.
- L55 _private member_ `FString ServiceUrl = TEXT("127` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Service", meta = (AllowPrivateAccess))` — The web app url.
- L59 _private member_ `FString FormattedServiceUrl;` — `UPROPERTY(Transient)` — Cached formatted Url.
- L63 _private member_ `uint32 FormattedWithPort = 0;` — `UPROPERTY(Transient)` — What port the formatted Url was created with, used to re-cache on port change.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("WebAPILiquidJS"), STATGROUP_WebAPILiquidJS, STAT`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Public/IWebAPILiquidJSModule.h` (Public)


#### class `IWebAPILiquidJSModuleInterface`  
`class IWebAPILiquidJSModuleInterface : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`
