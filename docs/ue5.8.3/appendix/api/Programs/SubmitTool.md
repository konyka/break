# Programs / SubmitTool

- module root: `Source/Programs/SubmitTool`
- headers: 59; symbols: 1423
- symbol kinds: class=61, delegate=22, enum=11, enumerator=63, function=224, macro=16, member=422, namespace=12, prototype=567, struct=9, typedef=3, variable=13
- DynamicallyLoadedModuleNames: SlateReflector
- PrivateDependencyModuleNames: Analytics, AnalyticsET, AppFramework, ApplicationCore, Core, CoreUObject, DesktopPlatform, HTTP, HTTPServer, InputCore, Json, JsonUtilities, OutputLog, PakFile, Projects, RenderCore, Settings, ShaderCompilerCommon, Slate, SlateCore, StandaloneRenderer, StudioTelemetry, SubmitToolCore, SubmitToolRestricted, ToolWidgets, UnixCommonStartup, Virtualization
- PrivateIncludePathModuleNames: SlateReflector
- PublicDependencyModuleNames: RPCBase
- PublicIncludePathModuleNames: Launch, TargetPlatform

### `Source/Programs/SubmitTool/Private/Logging/SubmitToolOutputLog.h` (Private)


#### class `SSubmitToolOutputLog`  
`class SSubmitToolOutputLog : public SOutputLog`  
_L7-13_
- inherits: `SOutputLog`
- L10 _public typedef_ `using FArguments = SOutputLog::FArguments;`
- L12 _public prototype_ `void ScrollToEnd();`

### `Source/Programs/SubmitTool/Private/Logging/SubmitToolOutputLogHistory.h` (Private)


#### class `FSubmitToolOutputLogHistory`  
`class FSubmitToolOutputLogHistory : public FOutputDevice`  
_L10-46_
- inherits: `FOutputDevice`
- L13 _public function_ `FSubmitToolOutputLogHistory()`
- L18 _public function_ `virtual ~FSubmitToolOutputLogHistory()`
- L23 _public function_ `void Release()`
- L31 _public prototype_ `FSubmitToolOutputLogHistory(const FSubmitToolOutputLogHistory&) = delete;`
- L32 _public prototype_ `FSubmitToolOutputLogHistory(FSubmitToolOutputLogHistory&&) = delete;`
- L34 _public function_ `const TArray<TSharedPtr<FOutputLogMessage>>& GetMessages() const`
- L40 _private function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override`
- L45 _private member_ `TArray<TSharedPtr<FOutputLogMessage>> Messages;`

### `Source/Programs/SubmitTool/Private/Logic/ChangelistService.h` (Private)


#### struct `FChangelistData`  
`struct FChangelistData`  
_L18-32_
- L20 _public member_ `FString Description;`
- L21 _public member_ `TArray<FSCFileRef> Files;` — <Filename, DepotPath, State>
- L22 _public member_ `TArray<FSCFileRef> ShelvedFiles;` — <{}, DepotPath, State>
- L23 _public member_ `TMap<FString, FString> AllOpenFiles;` — <DepotPath, Change>
- L24 _public member_ `bool bIsValid = false;` — Changelist data could be fetched and parsed correctly
- L25 _public member_ `bool bIsShelfComplete = false;` — OpenFilesSet == ShelvedFilesSet, content may differ
- L27 _public prototype_ `static FChangelistData Parse( const FString& CLID, const FSCCommand& DescribeCmd, const FSCCommand& OpenedCmd, const TMap<FString, FString>& DepotFileToLocalFile);`

#### class `FChangelistService`  
`class FChangelistService final : public IChangelistService`  
_L34-171_
- inherits: `IChangelistService`
- L38 _public prototype_ `FChangelistService(const FGeneralParameters& InParameters, const TSharedPtr<FSubmitToolServiceProvider> InServiceProvider, const FOnChangeListReadyDelegate& InCLReadyCallback, const FOnChangelistRefreshDelegate& InCLRefreshCallback);`
- L39 _public prototype_ `~FChangelistService();`
- L41 _public function_ `virtual const FString GetCLID() const override`
- L52 _public function_ `virtual const FString& GetCLDescription() override`
- L58 _public function_ `virtual bool SetCLDescription(const FString& newDescription, bool bNotifyEvent = false) override`
- L78 _public function_ `virtual const TArray<FSCFileRef>& GetFilesInCL() const override`
- L84 _public function_ `virtual const TArray<FSCFileRef>& GetShelvedFilesInCL() const override`
- L90 _public function_ `virtual bool HasShelvedFiles() const override`
- L96 _public function_ `virtual bool IsShelfComplete() const override`
- L102 _public function_ `virtual const TMap<FString, FString>& GetOpenFilesInChangelists() const override`
- L108 _public function_ `virtual bool HasP4OperationsRunning() const override`
- L114 _public function_ `virtual bool IsShelfReady() const override`
- L119 _public prototype_ `virtual void Init() override;`
- L120 _public prototype_ `virtual void Submit(const FString& InDescriptionAddendum = TEXT(""), TFunction<void(const FSCCommand&)> OnComplete = nullptr) override;`
- L123 _public prototype_ `virtual void CreateCLFromDefaultCL() override;` — void Submit(const FString& InDescriptionAddendum = TEXT(""), const FSourceControlOperationComplete& OnSubmitComplete = FSourceControlOperationComplete());
- L124 _public prototype_ `virtual void FetchChangelistDataAsync() override;`
- L125 _public prototype_ `virtual void RevertUnchangedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) override;`
- L127 _public prototype_ `virtual void UpdateP4CLDescription() override;`
- L128 _public prototype_ `virtual void UpdateP4CLDescriptionSynchronously() override;`
- L129 _public prototype_ `virtual void DeleteShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) override;`
- L130 _public prototype_ `virtual void ReplaceShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) override;`
- L131 _public prototype_ `virtual void CreateShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) override;`
- L132 _public prototype_ `virtual void UpdateShelvedFiles(TArray<FString> InFiles, TFunction<void(const FSCCommand&)> OnComplete = nullptr) override;`
- L133 _public prototype_ `virtual void CheckShelfIsUpToDate(TFunction<void(bool, TArray<FString>)> OnComplete) override;`
- L134 _public prototype_ `virtual void EnsureShelfIsCurrent() override;`
- L135 _public prototype_ `bool P4Tick(float DeltaTime);`
- L137 _public prototype_ `virtual void CancelP4Operations() override;`
- L140 _private member_ `mutable FCriticalSection Mutex;`
- L142 _private member_ `FString CLID;`
- L143 _private member_ `FString CurrentStream;`
- L144 _private member_ `const FGeneralParameters& Parameters;`
- L145 _private member_ `const FOnChangeListReadyDelegate& CLReadyCallback;`
- L146 _private member_ `const FOnChangelistRefreshDelegate& CLRefreshCallback;`
- L148 _private member_ `const FTSTicker::FDelegateHandle TickHandle;`
- L149 _private member_ `const TSharedPtr<FSubmitToolServiceProvider> ServiceProvider;`
- L150 _private member_ `const TSharedPtr<ISTSourceControlService> SourceControlService;`
- L152 _private member_ `FChangelistData Changelist;`
- L153 _private member_ `FString CLDescription;`
- L154 _private member_ `bool bIsShelfReady = false;`
- L155 _private member_ `bool bDiffTaskRunning = false;`
- L156 _private member_ `TOptional<bool> BroadcastReadyIsValid;`
- L157 _private member_ `TOptional<ETaskArea> BroadcastRefreshChangeType;`
- L159 _private member_ `UE::Tasks::TTask<TSharedRef<FSCCommand>> OpenedTask;`
- L160 _private member_ `UE::Tasks::TTask<TSharedRef<FSCCommand>> DescribeTask;`
- L161 _private member_ `UE::Tasks::TTask<FChangelistData> ParseChangelistTask;`
- L162 _private member_ `UE::Tasks::FTask UpdateChangelistTask;`
- L164 _private prototype_ `void WaitForChangelistData();`
- L165 _private prototype_ `FString ParseP4ChangesOutput(const FSCCRecord& InP4ChangeOutputRecords, const FString& InReplaceDescription);`
- L166 _private prototype_ `void CacheChangelistData();`
- L167 _private prototype_ `void UpdateCachedChangelistData();`
- L168 _private prototype_ `void PrintFilesAndShelvedFiles() const;`
- L169 _private prototype_ `TArray<FSCFileRef> ParseShelvedFilesFromP4(const FSCCommand& InCmd);`
- L170 _private prototype_ `TMap<FString, FString> RunWhereCommandSync(TArray<FString>&& InDepotPaths);`

#### Free symbols / members of external scopes

- L13 _typedef_ `using FSourceControlOperationRef = TSharedRef<class ISourceControlOperation, ESPMode::ThreadSafe>;`
- L16 _delegate_ `DECLARE_DELEGATE(FOnP4OperationCompleteDelegate) struct FChangelistData { FString Description; TArray<FSCFileRef> Files;`
- L173 _prototype_ `Expose_TNameOf(FChangelistService);`

### `Source/Programs/SubmitTool/Private/Logic/CredentialsService.h` (Private)


#### class `FHttpServerListener`  
`class FHttpServerListener`  
_L14-39_
- L17 _public function_ `FHttpServerListener(const FString& InURI, const EHttpServerRequestVerbs& InVerb, uint32 InPort, FHttpRequestHandler InCallback) : URI(InURI), Verb(InVerb), Port(InPort), Callback(InCallback)`
- L19 _public function_ `~FHttpServerListener()`
- L24 _public prototype_ `bool StartListening();`
- L25 _public prototype_ `void StopListening();`
- L27 _public function_ `bool IsListening() const`
- L33 _private member_ `TSharedPtr<IHttpRouter> HttpRouter = nullptr;`
- L34 _private member_ `FHttpRouteHandle RouteHandle = nullptr;`
- L35 _private member_ `FString URI;`
- L36 _private member_ `EHttpServerRequestVerbs Verb;`
- L37 _private member_ `uint32 Port;`
- L38 _private member_ `FHttpRequestHandler Callback;`

#### class `FCredentialsService`  
`class FCredentialsService : public ICredentialsService`  
_L41-129_
- inherits: `ICredentialsService`
- L44 _public prototype_ `FCredentialsService(const FSubmitToolParameters& InParameters);`
- L45 _public prototype_ `virtual ~FCredentialsService();`
- L47 _public function_ `virtual bool HasJiraCredentials() const override`
- L52 _public function_ `virtual void InvalidateCredentials() override`
- L58 _public function_ `virtual const FString& GetEncodedLoginString() const override`
- L63 _public prototype_ `virtual FString GetUsername() const override;`
- L64 _public prototype_ `virtual void SetLogin(const FString& InUsername, const FString& InPassword) override;`
- L66 _public function_ `virtual bool IsOIDCTokenEnabled() override`
- L71 _public function_ `virtual bool IsTokenReady() const override`
- L76 _public function_ `virtual const FString& GetToken() const override`
- L81 _public function_ `static const TUniquePtr<FAES::FAESKey>& GetEncryptionKey()`
- L91 _public prototype_ `virtual UE::Tasks::TTask<void> QueueWorkForToken(TFunction<void(const FString&)> InFunction) override;`
- L93 _public function_ `virtual void SetJiraToken(FJiraToken&& InJiraToken) override`
- L99 _public function_ `virtual const TUniquePtr<FJiraToken>& GetJiraToken() const override`
- L105 _private member_ `TUniquePtr<FJiraToken> JiraOAuthToken;`
- L106 _private member_ `static TUniquePtr<FAES::FAESKey> Key;`
- L107 _private prototype_ `static void LoadKey();`
- L108 _private prototype_ `static void GenerateKey();`
- L109 _private prototype_ `static const FString GetKeyFilepath();`
- L111 _private member_ `UE::Tasks::TTask<bool> GetOIDCTask;`
- L112 _private member_ `TUniquePtr<FProcessWrapper> OIDCProcess;`
- L113 _private member_ `FString OIDCToken;`
- L114 _private member_ `FDateTime TokenExpiration;`
- L115 _private member_ `const FSubmitToolParameters Parameters;`
- L117 _private prototype_ `void GetOIDCToken();`
- L118 _private prototype_ `bool ParseOIDCTokenData(const FString& InToken);`
- L119 _private prototype_ `FString GetPassword() const;`
- L120 _private prototype_ `void SaveCredentials() const;`
- L121 _private prototype_ `void LoadCredentials();`
- L123 _private prototype_ `bool Tick(float DeltaTime);`
- L125 _private prototype_ `const FString GetCredentialsFilepath() const;`
- L127 _private member_ `FString LoginString;`
- L128 _private member_ `bool bValidatedCredentials = true;`

#### Free symbols / members of external scopes

- L131 _prototype_ `Expose_TNameOf(FCredentialsService);`

### `Source/Programs/SubmitTool/Private/Logic/DialogFactory.h` (Private)


#### enum `EDialogFactoryResult`  
`enum class EDialogFactoryResult : size_t`  
_L7-18_
- L9 _public enumerator_ `FirstButton = 0`
- L10 _public enumerator_ `SecondButton`
- L11 _public enumerator_ `ThirdButton`
- L12 _public enumerator_ `FourthButton`
- L13 _public enumerator_ `ClosedWithX = std::numeric_limits<size_t>::max()`
- L14 _public enumerator_ `Confirm = FirstButton`
- L15 _public enumerator_ `Cancel = SecondButton`
- L16 _public enumerator_ `Yes = FirstButton`
- L17 _public enumerator_ `No = SecondButton`

#### class `FDialogFactory`  
`class FDialogFactory`  
_L20-48_
- L23 _public prototype_ `static EDialogFactoryResult ShowDialog(const FText& Title, const FText& Description, const TArray<FString>& AvailableButtons, const TSharedPtr<SWidget> AdditionalContent = nullptr, TFunction<bool(size_t)> InIsBtnEnabled = nullptr);`
- L31 _public prototype_ `static EDialogFactoryResult ShowConfirmDialog(const FText& Title, const FText& Description, const TSharedPtr<SWidget> AdditionalContent = nullptr);` — @brief Shows a dialog screen with the Cancel and Confirm buttons @param Title The title of the dialog @param Description The description of the dialog @return The button idx that is pressed
- L39 _public prototype_ `static EDialogFactoryResult ShowInformationDialog(const FText& Title, const FText& Description, const TSharedPtr<SWidget> AdditionalContent = nullptr);` — @brief Shows a dialog screen with the Confirm button @param Title The title of the dialog @param Description The description of the dialog @return The button idx that is pressed
- L47 _public prototype_ `static EDialogFactoryResult ShowYesNoDialog(const FText& Title, const FText& Description, const TSharedPtr<SWidget> AdditionalContent = nullptr);` — @brief Shows a dialog screen with the Yes and No buttons @param Title The title of the dialog @param Description The description of the dialog @return The button idx that is pressed

### `Source/Programs/SubmitTool/Private/Logic/IntegrationService.h` (Private)


#### class `FIntegrationService`  
`class FIntegrationService final : public ISubmitToolService`  
_L19-38_
- inherits: `ISubmitToolService`
- L22 _public prototype_ `FIntegrationService(const FIntegrationParameters& InParameters, TWeakPtr<FSubmitToolServiceProvider> InServiceProvider);`
- L24 _public prototype_ `void RequestIntegration(const FOnBooleanValueChanged OnComplete) const;`
- L26 _public function_ `const TMap<FString, TSharedPtr<FIntegrationOptionBase>>& GetIntegrationOptions() const`
- L31 _public prototype_ `bool ValidateIntegrationOptions(bool bSilent) const;`
- L34 _private member_ `TMap<FString, TSharedPtr<FIntegrationOptionBase>> IntegrationOptions;`
- L36 _private member_ `FIntegrationParameters Parameters;`
- L37 _private member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;`

#### Free symbols / members of external scopes

- L40 _prototype_ `Expose_TNameOf(FIntegrationService);`

### `Source/Programs/SubmitTool/Private/Logic/JiraService.h` (Private)


#### enum `EJiraServerRequest`  
`enum EJiraServerRequest`  
_L15-20_
- L17 _public enumerator_ `AuthorizationCode`
- L18 _public enumerator_ `AccessToken`

#### class `FJiraService`  
`class FJiraService final : public ISubmitToolService`  
_L27-80_
- inherits: `ISubmitToolService`
- L30 _public prototype_ `FJiraService() = delete;`
- L31 _public prototype_ `FJiraService(const FJiraParameters& InJiraSettings, const int32 InMaxResults, TWeakPtr<FSubmitToolServiceProvider> InServiceProvider);`
- L32 _public prototype_ `~FJiraService();`
- L33 _public prototype_ `void ObtainOAuth(TFunction<void(bool)> InCallback);`
- L35 _public prototype_ `bool FetchJiraTickets(bool InForce = false, bool bInFailSilently = false);`
- L36 _public prototype_ `void Reset();`
- L38 _public function_ `const TMap<FString, FJiraIssue>& GetIssues()`
- L40 _public member_ `FOnJiraIssuesRetrieved OnJiraIssuesRetrievedCallback;`
- L42 _public member_ `bool bOngoingRequest = false;`
- L43 _public function_ `bool IsBlockingRequestRunning()`
- L48 _public prototype_ `void GetIssueAndCreateServiceDeskRequest(const FString& Key, const FString& Description, const FString& SwarmURL, const FString& InCurrentStream, const TMap<FString, TSharedPtr<FIntegrationOptionBase>>& InIntegrationOptions, const FOnBooleanValueChanged OnComplete);`
- L49 _public prototype_ `void CreateServiceDeskRequest(TSharedPtr<FJsonObject> InBaseJiraJsonObject, const FString& Description, const FString& SwarmURL, const FString& InCurrentStream, const TMap<FString, TSharedPtr<FIntegrationOptionBase>>& InIntegrationOptions, const FOnBooleanValueChanged OnComplete);`
- L51 _private prototype_ `void QueryIssues(bool bInFailSilently = false, bool bAllowTokenRefresh = true);`
- L52 _private prototype_ `void QueryIssues_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, bool bFailSilently, bool bAllowTokenRefresh);`
- L53 _private prototype_ `void RefreshOAuthToken(TFunction<void(bool)> InCallback);`
- L55 _private prototype_ `bool ParseJsonObject(const TSharedPtr<FJsonObject>* InJsonObject, FJiraIssue& OutJiraIssue) const;`
- L57 _private prototype_ `const FString GetJiraIssuesFilepath() const;`
- L59 _private prototype_ `void SaveJiraIssues() const;`
- L60 _private prototype_ `void LoadJiraIssues();`
- L62 _private prototype_ `void ExchangeOAuthCode(TFunction<void(bool)> InCallback);`
- L64 _private prototype_ `void CreateServiceDeskRequest_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, const FOnBooleanValueChanged OnComplete);`
- L65 _private prototype_ `void GetIssueAndCreateServiceDeskRequest_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, const FString& Description, const FString& SwarmURL, const FString& InCurrentStream, const TMap<FString, TSharedPtr<FIntegrationOptionBase>>& InIntegrationOptions, const FOnBooleanValueChanged OnComplete);`
- L68 _private member_ `FGuid UserId = FGuid::NewGuid();`
- L69 _private member_ `FString AuthCode;`
- L70 _private member_ `const FJiraParameters Definition;`
- L71 _private member_ `FHttpRequestPtr JiraRequest = nullptr;`
- L72 _private member_ `FHttpRequestPtr ServiceDeskRequest = nullptr;`
- L73 _private member_ `const int32 MaxResults;`
- L74 _private member_ `TMap<FString, FJiraIssue> JiraIssues;`
- L76 _private member_ `TUniquePtr<FHttpServerListener> HttpServerListener;`
- L77 _private member_ `bool bWaitingOAuth = false;`
- L79 _private member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnJiraIssuesRetrieved, bool ) enum EJiraServerRequest { AuthorizationCode, AccessToken };`
- L82 _prototype_ `Expose_TNameOf(FJiraService);`

### `Source/Programs/SubmitTool/Private/Logic/P4LockdownService.h` (Private)


#### class `FP4LockdownService`  
`class FP4LockdownService : public ILockdownService`  
_L17-74_
- inherits: `ILockdownService`
- L21 _public prototype_ `FP4LockdownService() = delete;`
- L22 _public prototype_ `FP4LockdownService(const FP4LockdownParameters& InParameters, TWeakPtr<FSubmitToolServiceProvider> InServiceProvider);`
- L23 _public prototype_ `virtual FSubmitToolLockdownData ArePathsInLockdown(const TArray<FSCFileRef>& InPaths, const TSet<FString>& InDynamicFiles = TSet<FString>()) override;`
- L24 _public function_ `virtual bool IsBlockingOperationRunning() const override`
- L56 _private prototype_ `FSubmitToolLockdownData IsPathInLockdown(const FSCFileRef& InPath, const TSet<FString>& InDynamicFiles) const;`
- L57 _private prototype_ `void DownloadAllowListData();`
- L58 _private prototype_ `bool WaitForAllowListData();`
- L59 _private prototype_ `void ParseAllowListData();`
- L60 _private prototype_ `void ParseAllowListFiles(const TMap<FString, FString>& InFiles, bool bEnabled = true);`
- L62 _private prototype_ `void GetAdditionalHardlockedPaths();`
- L63 _private prototype_ `FString GetFilePath(const FString& InConfigId);`
- L65 _private member_ `TMap<FString, FSharedBuffer> DownloadedFiles;`
- L66 _private member_ `UE::Tasks::TTask<bool> DownloadTask;`
- L67 _private member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;`
- L68 _private member_ `const FP4LockdownParameters& Parameters;`
- L69 _private member_ `TArray<FAllowListData> AllowListData;`
- L70 _private member_ `TArray<FOverrideData> OverrideData;`
- L71 _private member_ `TArray<FString> AdditionalHardlocks;`
- L72 _private member_ `EAllowListState AllowListState = EAllowListState::Missing;`
- L73 _private member_ `FCriticalSection Mutex;`

#### enum `FP4LockdownService::EAllowListState`  
`enum EAllowListState`  
_L31-36_
- L33 _public enumerator_ `Missing`
- L34 _public enumerator_ `Cached`
- L35 _public enumerator_ `Downloaded`

#### struct `FP4LockdownService::FAllowListData`  
`struct FAllowListData`  
_L38-49_
- L40 _public member_ `bool bIsEnabled = true;`
- L41 _public member_ `FString FileId;`
- L42 _public member_ `FString GroupName;`
- L43 _public member_ `FString Message;`
- L44 _public member_ `ELockdownType LockdownType = ELockdownType::None;`
- L45 _public member_ `FString ValidTag;`
- L46 _public member_ `TSet<FString, FCaseInsensitiveStringKeyFuncs> AllowListers;`
- L47 _public member_ `TSet<FString, FCaseInsensitiveStringKeyFuncs> Members;`
- L48 _public member_ `TArray<TPair<bool, FString>> Views;`

#### struct `FP4LockdownService::FOverrideData`  
`struct FOverrideData : public FAllowListData`  
_L52-55_
- inherits: `FAllowListData`
- L54 _public member_ `TSet<FString> Sections;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnConfigFileRetrieved, bool ) class FSubmitToolServiceProvider;`
- L76 _prototype_ `Expose_TNameOf(FP4LockdownService);`

### `Source/Programs/SubmitTool/Private/Logic/PreSubmitOperations/VirtualizationOperation.h` (Private)


#### class `FVirtualizationOperation`  
`class FVirtualizationOperation : public FValidatorRunExecutable`  
_L13-74_
- inherits: `FValidatorRunExecutable`
- L18 _public prototype_ `FVirtualizationOperation(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L19 _public prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L20 _public prototype_ `virtual bool Activate() override;`
- L21 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L22 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L27 _public prototype_ `virtual void Tick(float InDeltatime) override;`
- L28 _public prototype_ `virtual void StopInternalValidations() override;`
- L31 _protected prototype_ `virtual void OnProcessComplete(const FString& ProcessId, int32 ReturnCode) override;`
- L32 _protected prototype_ `virtual const TArray<FAnalyticsEventAttribute> GetTelemetryAttributes() const override;`
- L36 _private prototype_ `bool StartBuildingTool();`
- L37 _private prototype_ `void StartVirtualization();`
- L38 _private prototype_ `void ProcessOutput(const FString& InOutput);`
- L40 _private function_ `bool IsBuildingTool() const`
- L46 _private member_ `TUniquePtr<FProcHandle> BuildProcessHandle;`
- L47 _private member_ `FProcessPipes Pipes;`
- L49 _private member_ `bool bCompileRequired = false;`
- L50 _private member_ `int32 CompileResult = 0;`
- L52 _private member_ `double CompileStartTime = 0.0;`
- L53 _private member_ `double TotalCompileTime = 0.0;`
- L55 _private member_ `bool bLaunchProcess = false;`
- L57 _private member_ `FString OutputRemainder;`
- L71 _private member_ `EVirtualizationErrorCode ErrorCode = EVirtualizationErrorCode::Success;`

#### enum `FVirtualizationOperation::EVirtualizationErrorCode`  
`enum class EVirtualizationErrorCode`  
_L59-69_
- L61 _public enumerator_ `Success = 0`
- L63 _public enumerator_ `NoBuildCommand`
- L64 _public enumerator_ `UBTNotFound`
- L65 _public enumerator_ `UBTProcFailure`
- L66 _public enumerator_ `CompileFailed`
- L67 _public enumerator_ `UVTProcFailure`
- L68 _public enumerator_ `UVTError`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SubmitToolParseConstants`
- L10 _variable_ `const FString VirtualizationToolOp = TEXT("Vir` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/PreflightService.h` (Private)


#### enum `EPreflightServiceState`  
`enum class EPreflightServiceState`  
_L18-24_
- L20 _public enumerator_ `Idle`
- L21 _public enumerator_ `WaitingForShelf`
- L22 _public enumerator_ `StartPreflight`
- L23 _public enumerator_ `Error`

#### class `FPreflightService`  
`class FPreflightService final : public ISubmitToolService`  
_L27-117_
- inherits: `ISubmitToolService`
- L30 _public prototype_ `FPreflightService() = delete;`
- L31 _public prototype_ `FPreflightService( const FHordeParameters& InSettings, FModelInterface* InModelInterface, TWeakPtr<FSubmitToolServiceProvider> InServiceProvider);`
- L35 _public prototype_ `~FPreflightService();`
- L37 _public prototype_ `void RequestPreflight(const FString InTemplate = TEXT(""));`
- L38 _public prototype_ `void FetchPreflightInfo(bool bRequeue = false, const FString& InOAuthToken = TEXT(""));`
- L40 _public function_ `EPreflightServiceState GetState() const`
- L44 _public function_ `bool IsRequestInProgress() const`
- L48 _public function_ `const TUniquePtr<FPreflightList>& GetPreflightData() const`
- L52 _public function_ `const TMap<FString, FPreflightData>& GetUnlinkedPreflights() const`
- L56 _public function_ `const FString& GetHordeServerAddress() const`
- L60 _public function_ `const FString& GetDefaultPreflightTemplate() const`
- L64 _public function_ `bool GetIsHordeInformationReady() const`
- L69 _public prototype_ `TArray<const FPreflightData*> GetTaggedPreflights() const;`
- L70 _public prototype_ `TMap<FString, FStringFormatArg> GetFormatParameters(const FString& InTemplate = FString());`
- L72 _public prototype_ `bool SelectPreflightTemplate(FPreflightTemplateDefinition& OutTemplate) const;`
- L74 _public member_ `FOnPreflightDataUpdated OnPreflightDataUpdated;`
- L75 _public member_ `FSimpleMulticastDelegate OnHordeConnectionFailed;`
- L78 _private prototype_ `void QueueFetch(bool bRequeue, float InSeconds);`
- L80 _private prototype_ `void Requeue();`
- L82 _private prototype_ `void StartPreflight();`
- L83 _private prototype_ `FString GetAdditionalTasksString(const FPreflightTemplateDefinition& InTemplate) const;`
- L84 _private prototype_ `void RefreshStreamName();`
- L86 _private prototype_ `void FetchUnlinkedPreflight(const FString& InPreflightId, bool bRequeue, const FString& InOAuthToken);`
- L88 _private prototype_ `EDialogFactoryResult ShowUpdatePreflightTagDialog() const;`
- L89 _private prototype_ `bool Tick(float DeltaTime);`
- L92 _private member_ `const FHordeParameters Definition;` — Definitions from the ini
- L95 _private member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;` — services we depend on
- L96 _private member_ `FTag* PreflightTag;`
- L97 _private member_ `FModelInterface* ModelInterface;`
- L100 _private member_ `bool bCheckShelveInstead = false;` — local data
- L101 _private member_ `bool bStopAskingTagUpdate = false;`
- L102 _private member_ `bool bHordeInformationReady = false;`
- L103 _private member_ `FDateTime LastRequest = FDateTime::MinValue();`
- L104 _private member_ `EPreflightServiceState State;`
- L105 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L106 _private member_ `FString LastErrorMessage;`
- L107 _private member_ `TUniquePtr<FPreflightList> HordePreflights;`
- L108 _private member_ `TMap<FString, FPreflightData> UnlinkedHordePreflights;`
- L110 _private member_ `FString StreamName;`
- L111 _private member_ `FString TemplateId;`
- L114 _private member_ `TSharedPtr<IHttpRequest> LinkedPFRequest = nullptr;` — Fetch Preflight
- L115 _private member_ `TMap<FString, TSharedPtr<IHttpRequest>> UnlinkedPFRequests;`
- L116 _private member_ `int8 ActiveUnlinkedRequests = 0;`

#### Free symbols / members of external scopes

- L119 _prototype_ `Expose_TNameOf(FPreflightService);`

### `Source/Programs/SubmitTool/Private/Logic/ProcessPipes.h` (Private)


#### struct `FProcessPipes`  
`struct FProcessPipes`  
_L6-62_
- desc: Wrapper around stdin, stderr and stdout pipes created by a call to FPlatformProcess::CreatePipe
- L8 _public prototype_ `FProcessPipes() = default;`
- L10 _public function_ `~FProcessPipes()`
- L15 _public prototype_ `bool Create();`
- L17 _public prototype_ `void Reset();`
- L19 _public prototype_ `bool IsValid() const;`
- L21 _public function_ `void* GetStdInForProcess() const`
- L26 _public function_ `void* GetStdInForWriting() const`
- L31 _public function_ `void* GetStdOutForProcess() const`
- L36 _public function_ `void* GetStdOutForReading() const`
- L41 _public function_ `void* GetStdErrForProcess() const`
- L46 _public function_ `void* GetStdErrForReading() const`
- L53 _private member_ `void* StdOutReadPipe = nullptr;`
- L54 _private member_ `void* StdOutWritePipe = nullptr;`
- L56 _private member_ `void* StdErrReadPipe = nullptr;`
- L57 _private member_ `void* StdErrWritePipe = nullptr;`
- L59 _private member_ `void* StdInReadPipe = nullptr;`
- L60 _private member_ `void* StdInWritePipe = nullptr;`

### `Source/Programs/SubmitTool/Private/Logic/ProcessWrapper.h` (Private)


#### enum `EProcessOutputType`  
`enum EProcessOutputType`  
_L7-13_
- L9 _public enumerator_ `STDOutput`
- L10 _public enumerator_ `STDErr`
- L11 _public enumerator_ `ProcessInfo`
- L12 _public enumerator_ `ProcessError`

#### class `FProcessWrapper`  
`class FProcessWrapper`  
_L18-60_
- L21 _public prototype_ `FProcessWrapper(const FString& InProcessName, const FString& InPath, const FString& InArgs, const FOnCompleted& InOnCompleted = FOnCompleted(), const FOnOutputLine& InOnOutputLine = FOnOutputLine(), const FString& InWorkingDir = FString(), const bool bLaunchHidden = true, const bool bLaunchReallyHidden = true, const bool bLaunchDetached = false, bool InbOwnsProcessLifetime = true);`
- L22 _public prototype_ `~FProcessWrapper();`
- L23 _public prototype_ `bool Start(bool bWaitForExit = false);`
- L24 _public prototype_ `void Stop();`
- L25 _public prototype_ `bool IsRunning() const;`
- L27 _public function_ `const FString& GetProcessName() const`
- L28 _public function_ `const FString& GetExecutable() const`
- L29 _public function_ `const FString& GetArgs() const`
- L31 _public member_ `int32 ExitCode;`
- L32 _public member_ `float ExecutingTime = 0;`
- L33 _public member_ `bool bIsComplete = false;`
- L34 _public member_ `bool bStarted = false;`
- L36 _private prototype_ `bool OnTick(float Delta);`
- L37 _private prototype_ `void Cleanup();`
- L38 _private prototype_ `void ReadOutput(bool FlushOutput);`
- L39 _private prototype_ `void ProcessLines(bool bFlushOutput, bool bIsStdErr);`
- L40 _private prototype_ `void OutputLine(FString&& Output, const EProcessOutputType& OutputType);`
- L42 _private member_ `FString ProcessName;`
- L43 _private member_ `FString Path;`
- L44 _private member_ `FString Args;`
- L45 _private member_ `FString WorkingDir;`
- L46 _private member_ `const bool bLaunchesHidden;`
- L47 _private member_ `const bool bLaunchesReallyHidden;`
- L48 _private member_ `const bool bLaunchDetached;`
- L49 _private member_ `const bool bOwnsProcessLifetime;`
- L51 _private member_ `TUniquePtr<FProcHandle> ProcessHandle;`
- L52 _private member_ `TUniquePtr<FProcessPipes> Pipes;`
- L53 _private member_ `FString OutputRemainder;`
- L54 _private member_ `FString StdErrOutputRemainder;`
- L56 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L58 _private member_ `const FOnCompleted OnCompleted = nullptr;`
- L59 _private member_ `const FOnOutputLine OnOutputLine = nullptr;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnOutputLine, FString , const EProcessOutputType&) DECLARE_DELEGATE_OneParam(FOnCompleted, const int32 ) class FProcessWrapper { public: FProcessWrapper(const FString& InProcessName, const FString& InPath, const FString& InArgs, const FOnCompleted& InOnCompleted = FOnCompleted(), const FOnOutputLine& InOnOutputLine = FOnOutputLine(), const FString& InWorkingDir = FString(), const bool bLaunchHidden = true, const bool bLaunchReallyHidden = true, const bool bLaunchDetached = false, bool InbOwnsProcessLifetime = true); ~FProcessWrapper(); bool Start(bool bWaitForExit = false); void Stop(); bool IsRunning() const; const FString& GetProcessName() const { return ProcessName; } const FString& GetExecutable() const { return Path; } const FString& GetArgs() const { return Args; } int32 ExitCode; float ExecutingTime = 0; bool bIsComplete = false; bool bStarted = false; private: bool OnTick(float Delta); void Cleanup(); void ReadOutput(bool FlushOutput); void ProcessLines(bool bFlushOutput, bool bIsStdErr); void OutputLine(FString&& Output, const EProcessOutputType& OutputType); FString ProcessName; FString Path; FString Args; FString WorkingDir; const bool bLaunchesHidden; const bool bLaunchesReallyHidden; const bool bLaunchDetached; const bool bOwnsProcessLifetime; TUniquePtr<FProcHandle> ProcessHandle; TUniquePtr<FProcessPipes> Pipes; FString OutputRemainder; FString StdErrOutputRemainder;`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCompleted, const int32 ) class FProcessWrapper { public: FProcessWrapper(const FString& InProcessName, const FString& InPath, const FString& InArgs, const FOnCompleted& InOnCompleted = FOnCompleted(), const FOnOutputLine& InOnOutputLine = FOnOutputLine(), const FString& InWorkingDir = FString(), const bool bLaunchHidden = true, const bool bLaunchReallyHidden = true, const bool bLaunchDetached = false, bool InbOwnsProcessLifetime = true); ~FProcessWrapper(); bool Start(bool bWaitForExit = false); void Stop(); bool IsRunning() const; const FString& GetProcessName() const { return ProcessName; } const FString& GetExecutable() const { return Path; } const FString& GetArgs() const { return Args; } int32 ExitCode; float ExecutingTime = 0; bool bIsComplete = false; bool bStarted = false; private: bool OnTick(float Delta); void Cleanup(); void ReadOutput(bool FlushOutput); void ProcessLines(bool bFlushOutput, bool bIsStdErr); void OutputLine(FString&& Output, const EProcessOutputType& OutputType); FString ProcessName; FString Path; FString Args; FString WorkingDir; const bool bLaunchesHidden; const bool bLaunchesReallyHidden; const bool bLaunchDetached; const bool bOwnsProcessLifetime; TUniquePtr<FProcHandle> ProcessHandle; TUniquePtr<FProcessPipes> Pipes; FString OutputRemainder; FString StdErrOutputRemainder;`

### `Source/Programs/SubmitTool/Private/Logic/Services/CacheDataService.h` (Private)


#### class `FNoOpCacheDataService`  
`class FNoOpCacheDataService final : public ICacheDataService`  
_L11-26_
- inherits: `ICacheDataService`
- L14 _public function_ `virtual bool GetChangelistCacheData(const FString& InCLId, FChangelistCacheData& OutCLData) const override`
- L16 _public function_ `virtual const FDateTime GetLastValidationDate(const FString& InCLId, const FName& InValidatorId, const FString& InValidatorConfig, const FString& InDepotPath) const override`
- L17 _public function_ `virtual void UpdateLastValidationForFiles(const FString& InCLId, const FName& InValidatorId, const FString& InValidatorConfig, const TArray<FSCFileRef>& InFiles, const FDateTime& InNewTimestamp) override`
- L19 _public function_ `virtual FString GetIntegrationFieldValue(const FString& InCLId, const FString& InIntegrationFieldId) const override`
- L20 _public function_ `virtual void SetIntegrationFieldValue(const FString& InCLId, const FString& InIntegrationFieldId, const FString& InValue)`
- L21 _public function_ `virtual FDateTime GetLastKnownShelfUpToDate(const FString& InCLId) const`
- L22 _public function_ `virtual void SetLastShelfKnownUpToDate(const FString& InCLId, const FDateTime& InDateTime)`
- L24 _public function_ `virtual void SaveCacheToDisk()`

#### class `FCacheDataService`  
`class FCacheDataService final : public ICacheDataService`  
_L28-54_
- inherits: `ICacheDataService`
- L31 _public prototype_ `FCacheDataService(const FGeneralParameters& InGeneralParameters);`
- L32 _public prototype_ `~FCacheDataService();`
- L34 _public prototype_ `virtual bool GetChangelistCacheData(const FString& InCLId, FChangelistCacheData& OutCLData) const override;`
- L36 _public prototype_ `virtual const FDateTime GetLastValidationDate(const FString& InCLId, const FName& InValidatorId, const FString& InValidatorConfig, const FString& InDepotPath) const override;`
- L37 _public prototype_ `virtual void UpdateLastValidationForFiles(const FString& InCLId, const FName& InValidatorId, const FString& InValidatorConfig, const TArray<FSCFileRef>& InFiles, const FDateTime& InNewTimestamp) override;`
- L39 _public prototype_ `virtual FString GetIntegrationFieldValue(const FString& InCLId, const FString& InIntegrationFieldId) const override;`
- L40 _public prototype_ `virtual void SetIntegrationFieldValue(const FString& InCLId, const FString& InIntegrationFieldId, const FString& InValue);`
- L41 _public prototype_ `virtual FDateTime GetLastKnownShelfUpToDate(const FString& InCLId) const;`
- L42 _public prototype_ `virtual void SetLastShelfKnownUpToDate(const FString& InCLId, const FDateTime& InDateTime);`
- L44 _public prototype_ `virtual void SaveCacheToDisk();`
- L48 _private prototype_ `void LoadFromFile(const FString& InFilePath);`
- L49 _private prototype_ `void SaveToFile(const FString& InFilePath) const;`
- L50 _private prototype_ `void CleanOldData();`
- L52 _private member_ `const FGeneralParameters& Parameters;`
- L53 _private member_ `TUniquePtr<FCacheFile> CacheData;`

### `Source/Programs/SubmitTool/Private/Logic/Services/SourceControl/PerforceData.h` (Private)


#### enum `EP4ClientUserFlags`  
`enum class EP4ClientUserFlags : uint64`  
_L20-31_
- reflection: `UENUM()`
- L22 _public enumerator_ `None = 0`
- L24 _public enumerator_ `UnicodeServer = 1 << 0` — The server uses unicode
- L26 _public enumerator_ `CollectData = 1 << 1` — Binary data returned by commands should be collected in the DataBuffer member
- L27 _public enumerator_ `UseZTag = 1 << 2`
- L28 _public enumerator_ `UseClient = 1 << 3`
- L29 _public enumerator_ `UseUser = 1 << 4`
- L30 _public enumerator_ `SilentErrors = 1 << 5`

#### class `FP4File`  
`class FP4File`  
_L39-148_
- desc: A utility class to make it easier to gather a depot file from perforce when running p4 print.
- L42 _public prototype_ `FP4File() = default;`
- L43 _public prototype_ `~FP4File() = default;`
- L52 _public function_ `void Initialize(const TMap<FString, FString>& Record)` — Start gathering the file in the given record. If the record is missing data then the gather will not begin. The calling code should check for this and raise errors or warnings accordingly. This class does not actually do any perforce work itself, and relies on a ClientUser to actually provide the data as it is downloaded.
- L67 _public function_ `bool IsValid() const` — Returns true if the FP4DepotFile was set up correctly and can gather a file.
- L73 _public function_ `bool IsFileComplete() const` — Returns true if all of the files data has been acquired.
- L79 _public function_ `int64 GetRemainingBytes() const` — Returns the number of bytes in the file that have not yet been acquired.
- L85 _public function_ `const FString& GetDepotPath() const` — Returns the depot path of the file we are gathering
- L95 _public function_ `FSharedBuffer Release()` — Returns the currently acquired file data and then invalidates the FP4DepotFile. It is up to the caller to ensure that the entire file has been acquired or to decide if a partially acquired file is okay.
- L105 _public function_ `void Reset()` — Used to reset the FP4DepotFile if an error is encountered
- L124 _public function_ `bool OnDataDownloaded(const char* DataPtr, int DataLength)` — Called when new data for the file has been downloaded and we can add it to the data that we have already required. @param DataPtr		The pointer to the downloaded data @param DataLength	The size of the downloaded data in bytes @return				True if the FP4DepotFile is valid and there was enough space for the downloaded data. False if the FP4DepotFile is invalid or if there is not enough space.
- L142 _private member_ `FString DepotFilePath;` — The path of the file in the perforce depot
- L145 _private member_ `FUniqueBuffer Data;` — The buffer containing the file data, allocated up front.
- L147 _private member_ `int64 Offset = INDEX_NONE;` — Tracks where the next set on downloaded data should be placed in the buffer.

#### class `FSTClientUser`  
`class FSTClientUser : public ClientUser`  
_L151-358_
- inherits: `ClientUser`
- desc: Custom ClientUser class for handling results and errors from Perforce commands
- L155 _public function_ `FSTClientUser(FSCCommand& InCommand, EP4ClientUserFlags InFlags) : ClientUser() , Flags(InFlags) , Command(InCommand)`
- L165 _public function_ `virtual void InputData(StrBuf* OutBuffer, Error* OutError) override` — Called by P4API on "change -i" command to fill OutBuffer.
- L175 _public function_ `virtual void OutputStat(StrDict* VarList) override` — Called by P4API when the results from running a command are ready.
- L205 _public function_ `virtual void OutputText(const char* DataPtr, int DataLength) override` — Called by P4API when it output a chunk of text data from a file (commonly via P4 Print)
- L239 _public function_ `void OutputBinary(const char* DataPtr, int DataLength)` — Called by P4API when it output a chunk of binary data from a file (commonly via P4 Print)
- L285 _public function_ `virtual void Message(Error* err) override`
- L311 _public function_ `virtual void OutputInfo(char Indent, const char* InInfo) override`
- L321 _public function_ `virtual void OutputError(const char* errBuf) override`
- L334 _public function_ `inline bool IsUnicodeServer() const`
- L339 _public function_ `inline bool IsCollectingData() const`
- L345 _public function_ `inline TMap<FString, FSharedBuffer> ReleaseData()` — Returns DataBuffer as a FSharedBuffer, note that once called DataBuffer will be empty
- L350 _public member_ `EP4ClientUserFlags Flags;`
- L352 _public member_ `FSCCommand& Command;`
- L355 _private member_ `TMap<FString, FSharedBuffer> Files;`
- L357 _private member_ `FP4File File;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define FROM_TCHAR(InText, bIsUnicodeServer) (bIsUnicodeServer ? TCHAR_TO_UTF8(InText) : TCHAR_TO_ANSI(InText))`
- L15 _macro_ `#define TO_TCHAR(InText, bIsUnicodeServer) (bIsUnicodeServer ? UTF8_TO_TCHAR(InText) : ANSI_TO_TCHAR(InText))`
- L17 _macro_ `#define LOCTEXT_NAMESPACE "SubmitToolPerforce"`

### `Source/Programs/SubmitTool/Private/Logic/Services/SourceControl/SubmitToolPerforce.h` (Private)


#### class `FSTP4KeepAlive`  
`class FSTP4KeepAlive : public KeepAlive`  
_L15-34_
- inherits: `KeepAlive`
- L18 _public function_ `FSTP4KeepAlive(FOnIsCancelled InIsCancelled) : IsCancelled(InIsCancelled)`
- L23 _public function_ `virtual int IsAlive() override` — Called when the perforce connection wants to know if it should stay connected
- L33 _public member_ `FOnIsCancelled IsCancelled;`

#### struct `FClientApiWrapper`  
`struct FClientApiWrapper`  
_L36-48_
- L38 _public function_ `FClientApiWrapper(TUniquePtr<ClientApi>&& InConnection) : bIsReady(true), KeepAlive(FOnIsCancelled::CreateLambda([this] { return bWantsCancel.load(); })), Connection(MoveTemp(InConnection))`
- L39 _public function_ `: bIsReady(true), KeepAlive(FOnIsCancelled::CreateLambda([this] { return bWantsCancel.load(); })), Connection(MoveTemp(InConnection))`
- L44 _public member_ `std::atomic<bool> bIsReady = true;`
- L45 _public member_ `FSTP4KeepAlive KeepAlive;`
- L46 _public member_ `TUniquePtr<ClientApi> Connection;`
- L47 _public member_ `std::atomic<bool> bWantsCancel = false;`

#### struct `FP4Connection`  
`struct FP4Connection`  
_L50-60_
- L53 _public prototype_ `FP4Connection(FClientApiWrapper& InConnection);`
- L54 _public prototype_ `~FP4Connection();`
- L56 _public function_ `ClientApi& GetConnection() const`
- L59 _private member_ `FClientApiWrapper& Connection;`

#### class `FConnectionPool`  
`class FConnectionPool`  
_L62-74_
- L65 _public prototype_ `FConnectionPool() = default;`
- L66 _public prototype_ `~FConnectionPool();`
- L67 _public prototype_ `TUniquePtr<FP4Connection> GetAvailableConnection();`
- L68 _public prototype_ `void CancelCurrentRequests();`
- L70 _private prototype_ `int32 CreateConnection();`
- L71 _private member_ `std::atomic<bool> bConnectionFailed = false;`
- L72 _private member_ `TArray<TUniquePtr<FClientApiWrapper>> P4Connections;`
- L73 _private member_ `FCriticalSection Mutex;`

#### class `FSubmitToolPerforce`  
`class FSubmitToolPerforce final : public ISTSourceControlService`  
_L76-151_
- inherits: `ISTSourceControlService`
- L79 _public prototype_ `FSubmitToolPerforce();`
- L80 _public prototype_ `~FSubmitToolPerforce();`
- L83 _public prototype_ `virtual void InitializeParameters(const FSubmitToolParameters& InParameters);`
- L84 _public prototype_ `virtual void GetUsers(const FOnUsersGet::FDelegate& Callback) override;`
- L85 _public prototype_ `virtual void GetGroups(const FOnGroupsGet::FDelegate& Callback) override;`
- L86 _public prototype_ `virtual void GetUsersAndGroups(const FOnUsersAndGroupsGet::FDelegate& Callback) override;`
- L88 _public prototype_ `virtual UE::Tasks::TTask<bool> DownloadFiles(TArray<FString>&& FilePaths, TMap<FString, FSharedBuffer>& OutFileBuffers, bool bSilentErrors = false) override;`
- L90 _public prototype_ `virtual const TArray<TSharedPtr<FUserData>>& GetRecentUsers() const override;`
- L91 _public prototype_ `virtual void AddRecentUser(TSharedPtr<FUserData>& User) override;`
- L92 _public prototype_ `virtual const TArray<TSharedPtr<FString>>& GetRecentGroups() const override;`
- L93 _public prototype_ `virtual void AddRecentGroup(TSharedPtr<FString>& Group) override;`
- L95 _public prototype_ `virtual TSharedPtr<FUserData> GetUserDataFromCache(const FString& Username) const override;`
- L97 _public prototype_ `virtual const TArray<FSCCStream*>& GetClientStreams() const override;`
- L98 _public prototype_ `virtual const FSCCStream* GetSCCStream(const FString& InStreamName) override;`
- L99 _public prototype_ `virtual const FString GetRootStreamName() override;`
- L100 _public prototype_ `virtual const FString GetCurrentStreamName() override;`
- L101 _public prototype_ `virtual int32 GetDepotStreamDepth(const FString& InDepotName) override;`
- L102 _public prototype_ `virtual const FAuthTicket& GetAuthTicket() override;`
- L103 _public prototype_ `virtual void RequestCancel() override;`
- L104 _public prototype_ `virtual bool IsBusy() const override;`
- L107 _protected prototype_ `virtual bool RunCommandInternal(FSCCommand& Command) override;`
- L110 _private prototype_ `bool RunP4Command(FSCCommand& Command, EP4ClientUserFlags CmdFlags = DefaultFlags);`
- L112 _private prototype_ `UE::Tasks::TTask<TSharedRef<FSCCommand>> GetStream(const FString& InStream = FString());`
- L113 _private prototype_ `void ParseStreamCommand(const FSCCommand& InCompletedCommand, const FString& InRequestedStream = FString(), bool bParseHierarchy = true);`
- L114 _private prototype_ `void WaitForInitialStreamTask();`
- L116 _private member_ `TArray<FString> GroupsToExclude;`
- L117 _private member_ `TMap<FString, TSharedPtr<FUserData>> CachedUsers;`
- L118 _private member_ `TArray<TSharedPtr<FUserData>> CachedUsersArray;`
- L119 _private member_ `TArray<TSharedPtr<FString>> CachedGroupsArray;`
- L120 _private member_ `UE::Tasks::TTask<TSharedRef<FSCCommand>> InitialStreamTask;`
- L121 _private member_ `bool bUserTaskIsRunning = false;`
- L122 _private member_ `std::atomic<bool> bGroupTaskIsRunning = false;`
- L123 _private member_ `bool bIsUnicodeServer = false;`
- L124 _private member_ `bool bUsersReady = false;`
- L125 _private member_ `bool bGroupsReady = false;`
- L126 _private member_ `FOnUsersGet OnUsersGetCallbacks;`
- L127 _private member_ `FOnGroupsGet OnGroupsGetCallbacks;`
- L128 _private member_ `FOnUsersAndGroupsGet OnUsersAndGroupsGetCallbacks;`
- L129 _private member_ `std::atomic<uint64> ActiveCommands = 0;`
- L131 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L133 _private prototype_ `void LoadRecentUsers();`
- L134 _private prototype_ `void SaveRecentUsers();`
- L135 _private prototype_ `const FString GetRecentUsersFilepath() const;`
- L136 _private member_ `TArray<TSharedPtr<FUserData>> RecentUsers;`
- L137 _private prototype_ `void LoadRecentGroups();`
- L138 _private prototype_ `void SaveRecentGroups();`
- L139 _private prototype_ `const FString GetRecentGroupsFilepath() const;`
- L140 _private member_ `TArray<TSharedPtr<FString>> RecentGroups;`
- L142 _private member_ `TMap<FString, TUniquePtr<FSCCStream>> Streams;`
- L143 _private member_ `TMap<FString, int32> DepotStreamDepths;`
- L145 _private member_ `TArray<FSCCStream*> StreamHierarchy;`
- L146 _private member_ `FAuthTicket P4Ticket;`
- L148 _private member_ `FConnectionPool Connections;`
- L150 _private member_ `static constexpr EP4ClientUserFlags DefaultFlags = EP4ClientUserFlags::UseClient | EP4ClientUserFlags::UseUser | EP4ClientUserFlags::UseZTag;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsCancelled);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsCancelled);`

### `Source/Programs/SubmitTool/Private/Logic/SwarmService.h` (Private)


#### class `FSwarmService`  
`class FSwarmService : public ISubmitToolService`  
_L18-75_
- inherits: `ISubmitToolService`
- L21 _public prototype_ `FSwarmService(TWeakPtr<FSubmitToolServiceProvider> InServiceProvider);`
- L22 _public prototype_ `void FetchReview(const OnGetReviewComplete& OnComplete);`
- L24 _public prototype_ `void CreateReview(const TArray<FString>& InReviewers, const OnCreateReviewComplete& OnComplete);`
- L26 _public prototype_ `void UpdateReviewDescription(const TDelegate<void(bool)>& OnComplete, const FString& InDescription);`
- L29 _public function_ `const TUniquePtr<FSwarmReview>& GetReview() const`
- L30 _public function_ `bool GetCurrentReviewUrl(FString& OutUrl) const`
- L40 _public function_ `FString BuildReviewURL(const FString& InReviewId) const`
- L45 _public function_ `void CancelOperations()`
- L53 _public function_ `bool IsRequestRunning() const`
- L59 _public prototype_ `const TArray<FString> GetUsersInSwarmTag() const;`
- L62 _private prototype_ `FString ReviewsURL();`
- L65 _private member_ `TSharedPtr<IHttpRequest> CreateSwarmRequest;`
- L66 _private member_ `TSharedPtr<IHttpRequest> UpdateSwarmRequest;`
- L68 _private member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;`
- L69 _private member_ `UE::Tasks::TTask<TSharedRef<FSCCommand>> GetSwarmURLTask;`
- L70 _private member_ `FString SwarmURL;`
- L71 _private member_ `TUniquePtr<FSwarmReview> Review = nullptr;`
- L73 _private member_ `TArray<TSharedPtr<FUserData>>* Users = nullptr;`
- L74 _private member_ `TArray<TSharedPtr<FString>>* Groups = nullptr;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(OnGetReviewComplete, const TUniquePtr<FSwarmReview>&, const FString&) DECLARE_DELEGATE_TwoParams(OnCreateReviewComplete, bool, const FString&) class FSwarmService : public ISubmitToolService { public: FSwarmService(TWeakPtr<FSubmitToolServiceProvider> InServiceProvider); void FetchReview(const OnGetReviewComplete& OnComplete); void CreateReview(const TArray<FString>& InReviewers, const OnCreateReviewComplete& OnComplete); void UpdateReviewDescription(const TDelegate<void(bool)>& OnComplete, const FString& InDescription); const TUniquePtr<FSwarmReview>& GetReview() const { return Review; } bool GetCurrentReviewUrl(FString& OutUrl) const { if(Review.IsValid()) { OutUrl = BuildReviewURL(FString::FromInt(Review->Id)); } return Review.IsValid(); } FString BuildReviewURL(const FString& InReviewId) const { return FString::Printf(TEXT("%s/reviews/%s"), *SwarmURL, *InReviewId); } void CancelOperations() { if(CreateSwarmRequest.IsValid()) { CreateSwarmRequest->CancelRequest(); } } bool IsRequestRunning() const {`
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(OnCreateReviewComplete, bool, const FString&) class FSwarmService : public ISubmitToolService { public: FSwarmService(TWeakPtr<FSubmitToolServiceProvider> InServiceProvider); void FetchReview(const OnGetReviewComplete& OnComplete); void CreateReview(const TArray<FString>& InReviewers, const OnCreateReviewComplete& OnComplete); void UpdateReviewDescription(const TDelegate<void(bool)>& OnComplete, const FString& InDescription); const TUniquePtr<FSwarmReview>& GetReview() const { return Review; } bool GetCurrentReviewUrl(FString& OutUrl) const { if(Review.IsValid()) { OutUrl = BuildReviewURL(FString::FromInt(Review->Id)); } return Review.IsValid(); } FString BuildReviewURL(const FString& InReviewId) const { return FString::Printf(TEXT("%s/reviews/%s"), *SwarmURL, *InReviewId); } void CancelOperations() { if(CreateSwarmRequest.IsValid()) { CreateSwarmRequest->CancelRequest(); } } bool IsRequestRunning() const { return (CreateSwarmRequest.IsValid() && CreateSwarmRequest->GetStatus() == EHttpRequestStatus::Processing)`
- L77 _prototype_ `Expose_TNameOf(FSwarmService);`

### `Source/Programs/SubmitTool/Private/Logic/TagService.h` (Private)


#### class `FTagService`  
`class FTagService : public ITagService`  
_L11-77_
- inherits: `ITagService`
- L14 _public prototype_ `FTagService(const FSubmitToolParameters& InParameters, TSharedPtr<IChangelistService> clService);`
- L16 _public prototype_ `virtual void ParseCLDescription() override;`
- L17 _public prototype_ `virtual void ReApplyTags() override;`
- L19 _public prototype_ `virtual void ApplyTag(const FString& tagID) override;`
- L20 _public prototype_ `virtual void ApplyTag(FTag& tag) override;`
- L21 _public prototype_ `virtual void UpdateTagsInCL() override;`
- L22 _public prototype_ `virtual void RemoveTag(const FString& tagID) override;`
- L23 _public prototype_ `virtual void RemoveTag(FTag& tag) override;`
- L24 _public prototype_ `virtual void SetTagValues(const FString& tagID, const FString& values) override;`
- L25 _public prototype_ `virtual void SetTagValues(FTag& tag, const FString& values) override;`
- L26 _public prototype_ `virtual void SetTagValues(FTag& tag, const TArray<FString>& values) override;`
- L28 _public function_ `virtual FTag* GetTag(const FString& tagID) override`
- L38 _public function_ `virtual FTag* GetTagOfType(const FString& InType) override`
- L51 _public function_ `virtual FTag* GetTagOfSubtype(const FString& InTagSubtype) override`
- L64 _public prototype_ `virtual const TArray<const FTag*>& GetTagsArray() const override;`
- L67 _private function_ `FString& GetCLDescription()`
- L69 _private member_ `mutable TArray<const FTag*> CachedTags;`
- L71 _private member_ `const FSubmitToolParameters& Parameters;`
- L72 _private member_ `TMap<FString, FTag> RegisteredTags;`
- L73 _private member_ `TSharedPtr<IChangelistService> ChangelistService;`
- L75 _private prototype_ `void RegisterTags();`
- L76 _private prototype_ `void UpdateTagsPositions(size_t changePos, int32 delta);`

#### Free symbols / members of external scopes

- L79 _prototype_ `Expose_TNameOf(FTagService);`

### `Source/Programs/SubmitTool/Private/Logic/TasksService.h` (Private)


#### class `FTasksService`  
`class FTasksService : public ISubmitToolService`  
_L19-74_
- inherits: `ISubmitToolService`
- L22 _public prototype_ `FTasksService(const TMap<FString, FString>& Tasks, const FString& InTelemetryCustomEvent);`
- L23 _public prototype_ `virtual ~FTasksService();`
- L25 _public prototype_ `virtual void InitializeTasks(const TArray<TSharedRef<FValidatorBase>>& InTasks);`
- L27 _public prototype_ `virtual bool QueueAll();`
- L28 _public prototype_ `virtual void QueueSingle(const FName& InId, bool InbForceRun);`
- L29 _public prototype_ `virtual void QueueTypes(const FString& TaskType);`
- L30 _public prototype_ `virtual void QueueByArea(const ETaskArea& InArea);`
- L31 _public prototype_ `virtual void InvalidateForChanges(ETaskArea InChangeType);`
- L32 _public prototype_ `virtual void CheckForLocalFileEdit();`
- L33 _public prototype_ `virtual void CheckForTagSkips();`
- L34 _public prototype_ `virtual void ToggleEnabled(const FName& InTaskId);`
- L36 _public prototype_ `virtual bool GetIsRunSuccessful(bool bWaitForOptionalCompletes = true) const;`
- L37 _public prototype_ `virtual bool GetIsAnyTaskRunning() const;`
- L38 _public prototype_ `virtual bool AreTasksPendingQueue() const;`
- L40 _public prototype_ `virtual const TWeakPtr<const FValidatorBase> GetTask(const FName& InId) const;`
- L41 _public prototype_ `virtual const TArray<TWeakPtr<const FValidatorBase>>& GetTasks() const;`
- L42 _public prototype_ `virtual const TArray<TWeakPtr<const FValidatorBase>> GetTasksOfType(const FString& TaskType) const;`
- L44 _public prototype_ `virtual bool Tick(float InDeltaTime);`
- L45 _public prototype_ `virtual void ResetStates();`
- L47 _public prototype_ `virtual const TArray<FString> GetAddendums() const;`
- L49 _public prototype_ `virtual void StopTasks(const FName& InValidatorId = FName(), bool InbAsFailed = false);`
- L50 _public prototype_ `virtual void StopTasksByArea(const ETaskArea& InArea);`
- L52 _public member_ `FOnTaskFinished OnTasksQueueFinished;`
- L53 _public member_ `FOnSingleTaskFinished OnSingleTaskFinished;`
- L54 _public member_ `FOnTaskRunStateChanged OnTasksRunResultUpdated;`
- L56 _protected function_ `virtual bool QueueForExecution(const TSharedPtr<FValidatorBase>& InTask, bool InbForceRun)`
- L57 _protected prototype_ `virtual bool QueueForExecution(const TSharedPtr<FValidatorBase>& InTask, bool InbForceRun, TSet<FName>&);`
- L59 _protected prototype_ `virtual void OnTaskFinishedCallback(const FValidatorBase& InValidator);`
- L60 _protected prototype_ `virtual void PrintErrorSummary();`
- L62 _protected prototype_ `virtual void InvalidateDependants(const TSharedPtr<FValidatorBase>& InTask);`
- L64 _protected member_ `TMap<FName, TSharedPtr<FValidatorBase>> Tasks;`
- L65 _protected member_ `TArray<TWeakPtr<const FValidatorBase>> CachedTasksArray;`
- L66 _protected member_ `TArray<TWeakPtr<const FValidatorBase>> CachedTasksWithGroups;`
- L67 _protected member_ `bool bLastTasksRunState;`
- L68 _protected member_ `bool bLastRunningTasks;`
- L70 _protected member_ `const FString TelemetryBaseId;`
- L71 _protected member_ `uint64_t Execution = 1;`
- L73 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskFinished, bool ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSingleTaskFinished, const FValidatorBase& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskRunStateChanged, bool ) class FTasksService : public ISubmitToolService { public: FTasksService(const TMap<FString, FString>& Tasks, const FString& InTelemetryCustomEvent); virtual ~FTasksService(); virtual void InitializeTasks(const TArray<TSharedRef<FValidatorBase>>& InTasks); virtual bool QueueAll(); virtual void QueueSingle(const FName& InId, bool InbForceRun); virtual void QueueTypes(const FString& TaskType); virtual void QueueByArea(const ETaskArea& InArea); virtual void InvalidateForChanges(ETaskArea InChangeType); virtual void CheckForLocalFileEdit(); virtual void CheckForTagSkips(); virtual void ToggleEnabled(const FName& InTaskId); virtual bool GetIsRunSuccessful(bool bWaitForOptionalCompletes = true) const; virtual bool GetIsAnyTaskRunning() const; virtual bool AreTasksPendingQueue() const; virtual const TWeakPtr<const FValidatorBase> GetTask(const FName& InId) const; virtual const TArray<TWeakPtr<const FValidatorBase>>& GetTasks() const; virtual const TArray<TWeakPtr<const FValidatorBase>> GetTasksOfType(const FString& TaskType) const; virtual bool Tick(float InDeltaTime); virtual void ResetStates(); virtual const TArray<FString> GetAddendums() const; virtual void StopTasks(const FName& InValidatorId = FName(), bool InbAsFailed = false); virtual void StopTasksByArea(const ETaskArea`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSingleTaskFinished, const FValidatorBase& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskRunStateChanged, bool ) class FTasksService : public ISubmitToolService { public: FTasksService(const TMap<FString, FString>& Tasks, const FString& InTelemetryCustomEvent); virtual ~FTasksService(); virtual void InitializeTasks(const TArray<TSharedRef<FValidatorBase>>& InTasks); virtual bool QueueAll(); virtual void QueueSingle(const FName& InId, bool InbForceRun); virtual void QueueTypes(const FString& TaskType); virtual void QueueByArea(const ETaskArea& InArea); virtual void InvalidateForChanges(ETaskArea InChangeType); virtual void CheckForLocalFileEdit(); virtual void CheckForTagSkips(); virtual void ToggleEnabled(const FName& InTaskId); virtual bool GetIsRunSuccessful(bool bWaitForOptionalCompletes = true) const; virtual bool GetIsAnyTaskRunning() const; virtual bool AreTasksPendingQueue() const; virtual const TWeakPtr<const FValidatorBase> GetTask(const FName& InId) const; virtual const TArray<TWeakPtr<const FValidatorBase>>& GetTasks() const; virtual const TArray<TWeakPtr<const FValidatorBase>> GetTasksOfType(const FString& TaskType) const; virtual bool Tick(float InDeltaTime); virtual void ResetStates(); virtual const TArray<FString> GetAddendums() const; virtual void StopTasks(const FName& InValidatorId = FName(), bool InbAsFailed = false); virtual void StopTasksByArea(const ETaskArea& InArea); FOnTaskFinished OnTasksQueueFinished; FOnSingleTa`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskRunStateChanged, bool ) class FTasksService : public ISubmitToolService { public: FTasksService(const TMap<FString, FString>& Tasks, const FString& InTelemetryCustomEvent); virtual ~FTasksService(); virtual void InitializeTasks(const TArray<TSharedRef<FValidatorBase>>& InTasks); virtual bool QueueAll(); virtual void QueueSingle(const FName& InId, bool InbForceRun); virtual void QueueTypes(const FString& TaskType); virtual void QueueByArea(const ETaskArea& InArea); virtual void InvalidateForChanges(ETaskArea InChangeType); virtual void CheckForLocalFileEdit(); virtual void CheckForTagSkips(); virtual void ToggleEnabled(const FName& InTaskId); virtual bool GetIsRunSuccessful(bool bWaitForOptionalCompletes = true) const; virtual bool GetIsAnyTaskRunning() const; virtual bool AreTasksPendingQueue() const; virtual const TWeakPtr<const FValidatorBase> GetTask(const FName& InId) const; virtual const TArray<TWeakPtr<const FValidatorBase>>& GetTasks() const; virtual const TArray<TWeakPtr<const FValidatorBase>> GetTasksOfType(const FString& TaskType) const; virtual bool Tick(float InDeltaTime); virtual void ResetStates(); virtual const TArray<FString> GetAddendums() const; virtual void StopTasks(const FName& InValidatorId = FName(), bool InbAsFailed = false); virtual void StopTasksByArea(const ETaskArea& InArea); FOnTaskFinished OnTasksQueueFinished; FOnSingleTaskFinished OnSingleTaskFinished; FOnTaskRunStateChanged OnTasksRunResultUpdated; pr`

### `Source/Programs/SubmitTool/Private/Logic/UpdateService.h` (Private)


#### class `FUpdateService`  
`class FUpdateService final: public ISubmitToolService`  
_L13-56_
- inherits: `ISubmitToolService`
- L16 _public prototype_ `FUpdateService() = delete;`
- L17 _public prototype_ `FUpdateService(const FHordeParameters& InHordeParameters, const FAutoUpdateParameters& InAutoUpdateParameters, TWeakPtr<FSubmitToolServiceProvider> InServiceProvider);`
- L18 _public prototype_ `~FUpdateService();`
- L20 _public prototype_ `bool CheckForNewVersion();`
- L22 _public prototype_ `const FString& GetDeployId();`
- L23 _public prototype_ `const FString& GetLocalVersion();`
- L24 _public prototype_ `const FString& GetLatestVersion(bool bForce = false);`
- L26 _public prototype_ `void InstallLatestVersion();`
- L27 _public prototype_ `void Cancel();`
- L29 _public prototype_ `const FString GetDownloadMessage();`
- L32 _private prototype_ `bool DownloadLatestVersion(const FString& DeployId, const FString& LatestVersion);`
- L33 _private prototype_ `FString GetSubmitToolArgs() const;`
- L34 _private prototype_ `void StartAutoUpdateScript();`
- L35 _private prototype_ `void SaveLocalVersionToFile() const;`
- L37 _private prototype_ `void OnProcessDownloadRequestStream(void* InDataPtr, int64& InOutLength);`
- L38 _private prototype_ `const FString GetReadableDownloadSize();`
- L41 _private member_ `const FHordeParameters& HordeParameters;`
- L42 _private member_ `const FAutoUpdateParameters& AutoUpdateParameters;`
- L43 _private member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;`
- L45 _private member_ `FArchive* DownloadFile;`
- L46 _private member_ `TSharedPtr<IHttpRequest> DownloadRequest;`
- L47 _private member_ `long Downloaded = 0;`
- L49 _private member_ `FString LatestVersionDownloaded;`
- L51 _private member_ `FString DeployId;`
- L52 _private member_ `FString LocalVersion;`
- L53 _private member_ `FString RemoteVersion;`
- L55 _private member_ `FString DownloadErrorMessage;`

#### Free symbols / members of external scopes

- L58 _prototype_ `Expose_TNameOf(FUpdateService);`

### `Source/Programs/SubmitTool/Private/Logic/Validators/CoreRedirectsValidator.h` (Private)


#### class `FCoreRedirectsValidator`  
`class FCoreRedirectsValidator : public FValidatorBaseAsync`  
_L13-35_
- inherits: `FValidatorBaseAsync`
- L17 _public prototype_ `virtual void StartAsyncWork(const FString& CLDescription, const TArray<FSCFileRef>& FilteredFilesInCL, const TArray<const FTag*>& Tags) override;`
- L21 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L25 _private member_ `TArray<const FTag*> TagStatus;`
- L26 _private member_ `TArray<FSCFileRef> FilesToValidate;`
- L28 _private prototype_ `bool DoWork(const UE::Tasks::FCancellationToken& InCancellationToken);`
- L30 _private prototype_ `void PopulateSetFromStringViewOfFile(FAnsiStringView InFile, TSet<FAnsiStringView>& OutSet);`
- L32 _private prototype_ `virtual bool ContainsModifiedRedirects(const TSet<FAnsiStringView>& DepotContents, const TArray<FString>& WorkspaceContents);`
- L34 _private prototype_ `bool ContainsAnyRedirects(const TArray<FString>& FileContents);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SubmitToolParseConstants`
- L10 _variable_ `const FString CoreRedirectsValidator = TEXT("Cor` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/CrossChangelistValidator.h` (Private)


#### class `FCrossChangelistValidator`  
`class FCrossChangelistValidator : public FValidatorBase`  
_L12-28_
- inherits: `FValidatorBase`
- L17 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L18 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L21 _private prototype_ `bool CheckHeaderAndCppInDifferentChangelist();`
- L22 _private prototype_ `bool CheckForFilesInUncontrolledCLFile(const TSet<FString>& InUProjects, const TSet<FString>& InUEFNProjects);`
- L23 _private prototype_ `TMap<FString, TArray<FString>> LoadUncontrolledCLs(const FString& InFile) const;`
- L25 _private prototype_ `TSet<FString> ExtractUProjectFiles(const TArray<FString>& InFiles);`
- L26 _private prototype_ `TSet<FString> ExtractSubProjectFiles(const TArray<FString>& InFiles);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SubmitToolParseConstants`
- L9 _variable_ `const FString CrossChangelistValidator = TEXT("Cro` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/EditorCommandletValidator.h` (Private)


#### struct `FEditorParameters`  
`struct FEditorParameters`  
_L7-11_
- L9 _public member_ `FString EditorExePath;`
- L10 _public member_ `FString EditorArguments;`

#### class `FEditorCommandletValidator`  
`class FEditorCommandletValidator : public FValidatorRunExecutable`  
_L18-44_
- inherits: `FValidatorRunExecutable`
- L22 _public prototype_ `FEditorCommandletValidator(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L23 _public prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L24 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L25 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L26 _public prototype_ `virtual bool Activate() override;`
- L29 _protected prototype_ `virtual void ProcessSingleMessageForTelemetry(FString& InOutMessage) const override;`
- L30 _protected prototype_ `void GetEditorsForPaths(const TArray<FSCFileRef>& InFilteredFilesInCL, TMap<FString, FEditorParameters>& OutProjectEditorParameters) const;`
- L31 _protected prototype_ `void SortFilesByProjects(const TArray<FSCFileRef>& InFiles, TMap<FString, TArray<FSCFileRef>>& OutProjects, TMap<FString, TArray<FSCFileRef>>& OutSubProjects) const;`
- L32 _protected prototype_ `TMap<FString, TSet<FString>> GetEnableDisablePluginArguments(const TArray<FSCFileRef>& InFilesInCL) const;`
- L34 _protected prototype_ `void ExtractArgumentValues(FString& InArguments, const FString& InKey, TSet<FString>& InOutValues, const TCHAR InDelimiter = TCHAR(',')) const;`
- L36 _protected member_ `TMap<FString, TUniquePtr<FProcessWrapper>> Processes;`
- L39 _private prototype_ `FString MakeTemporaryUserDirectory() const;`
- L42 _private member_ `FString RegexMessageProcessing = TEXT(".*]` — Regex used for clearing the editor log timestamp, looks for "]Log******:" and removes everything before it
- L43 _private member_ `TSharedPtr<FRegexPattern> BuiltRegexProcessing;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace SubmitToolParseConstants`
- L15 _variable_ `const FString EditorValidator = TEXT("Edi` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/JsonValidator.h` (Private)


#### class `FJsonValidator`  
`class FJsonValidator final : public FValidatorBaseAsync`  
_L13-28_
- inherits: `FValidatorBaseAsync`
- L16 _public prototype_ `FJsonValidator(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L18 _public prototype_ `virtual void StartAsyncWork(const FString& CLDescription, const TArray<FSCFileRef>& FilteredFilesInCL, const TArray<const FTag*>& Tags) override;`
- L21 _protected prototype_ `bool ValidateJson(const TArray<FSCFileRef>& InFilteredFilesInCL, const UE::Tasks::FCancellationToken& InCancellationToken) const;`
- L22 _protected prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L24 _protected function_ `virtual const FString& GetValidatorTypeName() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SubmitToolParseConstants`
- L10 _variable_ `const FString JsonValidator = TEXT("Jso` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/PackageDataValidator.h` (Private)


#### class `FPackageDataValidator`  
`class FPackageDataValidator final : public FValidatorBaseAsync`  
_L12-31_
- inherits: `FValidatorBaseAsync`
- L17 _public prototype_ `FPackageDataValidator(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L18 _public prototype_ `virtual ~FPackageDataValidator() = default;`
- L20 _public prototype_ `virtual void StartAsyncWork(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L23 _private prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L27 _private function_ `virtual const FString& GetValidatorTypeName() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SubmitToolParseConstants`
- L9 _variable_ `const FString PackageDataValidator = TEXT("Pac` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/PreflightValidator.h` (Private)


#### class `FPreflightValidator`  
`class FPreflightValidator : public FValidatorBase`  
_L15-43_
- inherits: `FValidatorBase`
- L18 _public prototype_ `FPreflightValidator(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L20 _public prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L21 _public prototype_ `virtual bool Activate() override;`
- L23 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L24 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L26 _public prototype_ `virtual const FString GetPopupMessageWhenFailedText() const override;`
- L28 _protected prototype_ `const FString GetURLTextblock(const FString& InPFId) const;`
- L30 _protected prototype_ `void ValidatePreflights(const TUniquePtr<FPreflightList>& InPreflightList, const TMap<FString, FPreflightData>& InUnlinkedPreflights);`
- L31 _protected prototype_ `virtual void Skip() override;`
- L33 _protected prototype_ `void RemoveCallbacks();`
- L35 _protected member_ `FTag* PreflightTag;`
- L37 _protected member_ `FPreflightTemplateDefinition SuggestedTemplate;`
- L39 _protected prototype_ `virtual void ValidationFinished(bool bSuccess) override;`
- L40 _protected member_ `FDelegateHandle PreflightUpdateHandler;`
- L41 _protected member_ `FDelegateHandle HordeConnectionFailedHandler;`
- L42 _protected member_ `FDelegateHandle TagUpdateHandler;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace SubmitToolParseConstants`
- L12 _variable_ `const FString PreflightValidator = TEXT("Pre` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/ShaderValidator.h` (Private)


#### class `FShaderValidator`  
`class FShaderValidator final : public FValidatorBaseAsync`  
_L12-24_
- inherits: `FValidatorBaseAsync`
- L15 _public prototype_ `FShaderValidator(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L16 _public prototype_ `virtual ~FShaderValidator() = default;`
- L18 _public prototype_ `virtual void StartAsyncWork(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L20 _public function_ `virtual const FString& GetValidatorTypeName() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SubmitToolParseConstants`
- L9 _variable_ `const FString ShaderValidator = TEXT("Sha` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/TagValidator.h` (Private)


#### class `FTagValidator`  
`class FTagValidator : public FValidatorBase`  
_L14-31_
- inherits: `FValidatorBase`
- L19 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L20 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L23 _protected prototype_ `bool ValidateTag(const FTag* InTag, const TArray<TSharedPtr<FUserData>>& InP4Users, const TArray<TSharedPtr<FString>>& InP4Groups) const;`
- L25 _protected prototype_ `virtual void Tick(float InDeltaTime) override;`
- L28 _private member_ `TArray<const FTag*> P4UserTags;`
- L29 _private member_ `bool bHasFinished = false;`
- L30 _private member_ `bool bResult = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace SubmitToolParseConstants`
- L11 _variable_ `const FString TagValidator = TEXT("Tag` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/UBTValidator.h` (Private)


#### class `FUBTValidator`  
`class FUBTValidator : public FValidatorRunExecutable`  
_L12-37_
- inherits: `FValidatorRunExecutable`
- L16 _public prototype_ `FUBTValidator(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L17 _public prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L18 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L19 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L20 _public prototype_ `virtual bool Activate() override;`
- L23 _protected prototype_ `TSet<FString> ExtractUprojectFiles(const TArray<FString>& InFiles);`
- L24 _protected prototype_ `FString CreateFileList(const TArray<FString>& InFiles, const FString& InDirectory);`
- L25 _protected prototype_ `TArray<FString> FilterFiles(const TArray<FString>& InFiles, const FString& InDirectory, const TArray<FString>& InExcludeDirectories);`
- L26 _protected prototype_ `void FilterProgramFiles(const TArray<FString>& InFiles, TArray<FString>& OutNotProgramFiles, TMap<FString, TArray<FString>>& OutProgramFiles);`
- L29 _protected prototype_ `void PrepareUBTOptions();`
- L32 _protected member_ `const FString ConfigurationOptions = TEXT("Con`
- L33 _protected member_ `const FString PlatformOptions = TEXT("Pla`
- L34 _protected member_ `const FString StaticAnalyserOptions = TEXT("Sta`
- L35 _protected member_ `const FString TargetOptions = TEXT("Tar`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SubmitToolParseConstants`
- L9 _variable_ `const FString UBTValidator = TEXT("UBT` (scope `SubmitToolParseConstants`)

### `Source/Programs/SubmitTool/Private/Logic/Validators/ValidatorBase.h` (Private)


#### enum `EValidationStates`  
`enum class EValidationStates : uint8`  
_L23-34_
- reflection: `UENUM()`
- L25 _public enumerator_ `Not_Run`
- L26 _public enumerator_ `Skipped`
- L27 _public enumerator_ `Not_Applicable`
- L28 _public enumerator_ `Running`
- L29 _public enumerator_ `Valid`
- L30 _public enumerator_ `Failed`
- L31 _public enumerator_ `Timeout`
- L32 _public enumerator_ `Queued`
- L33 _public enumerator_ `Disabled`

#### enum `EFailureReason`  
`enum class EFailureReason : uint8`  
_L38-48_
- reflection: `UENUM()`
- L40 _public enumerator_ `None`
- L41 _public enumerator_ `InvalidSetup`
- L42 _public enumerator_ `OutOfMemory`
- L43 _public enumerator_ `SkippedOOM`
- L44 _public enumerator_ `Cancelled`
- L45 _public enumerator_ `InvalidExitCode`
- L46 _public enumerator_ `Errors`
- L47 _public enumerator_ `UnspecifiedFailure`

#### class `FValidatorBase`  
`class FValidatorBase`  
_L61-276_
- desc: @brief Base class for validator.
- L64 _public prototype_ `FValidatorBase() = delete;`
- L66 _public prototype_ `FValidatorBase(const FName& InNameId, const FSubmitToolParameters& InParameters, const TWeakPtr<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);` — if signature changes, need to update FValidatorFactory
- L67 _public prototype_ `virtual ~FValidatorBase();`
- L69 _public prototype_ `virtual void ParseDefinition(const FString& InDefinition);`
- L71 _public prototype_ `virtual const FString& GetValidatorTypeName() const = 0;`
- L72 _public function_ `const FName& GetValidatorNameId() const`
- L76 _public function_ `const FString& GetValidatorName() const`
- L81 _public prototype_ `virtual void StartValidation();`
- L83 _public prototype_ `virtual void ToggleEnabled();`
- L85 _public function_ `void Invalidate(bool bForce = false)`
- L102 _public function_ `bool GetHasPassed() const`
- L107 _public function_ `EValidationStates GetStealthState() const`
- L112 _public function_ `bool GetIsRunningOrQueued() const`
- L117 _public function_ `bool GetIsRunning() const`
- L122 _public function_ `bool GetIsQueued() const`
- L127 _public function_ `float GetRunTime() const`
- L132 _public function_ `EValidationStates GetState() const`
- L137 _public function_ `EFailureReason GetFailureReason() const`
- L142 _public prototype_ `virtual void Tick(float InDeltaTime);`
- L144 _public prototype_ `virtual void CancelValidation(const bool bInAsFailed = false);`
- L146 _public function_ `virtual void SetQueued(bool InbForceRun = false)`
- L157 _public function_ `void SetNotApplicable()`
- L162 _public prototype_ `virtual bool CanStartTask() const;`
- L164 _public prototype_ `virtual bool Activate();`
- L166 _public prototype_ `virtual void InvalidateLocalFileModifications();`
- L167 _public prototype_ `virtual bool EvaluateTagSkip();`
- L168 _public prototype_ `virtual bool IsRelevantToCL() const;`
- L169 _public function_ `virtual const FString GetPopupMessageWhenFailedText() const`
- L174 _public function_ `virtual bool IsEnabled() const`
- L179 _public function_ `virtual const TSet<FString>& GetLockdownIds() const`
- L184 _public prototype_ `const FString GetStatusText() const;`
- L185 _public function_ `const EValidationStates GetValidatorState() const`
- L190 _public function_ `const TMap<FString, TMap<FString, FString>>& GetValidatorOptions() const`
- L195 _public function_ `const FString GetSelectedOptionValue(const FString& InOptionName) const`
- L199 _public function_ `const FString GetSelectedOptionKey(const FString& InOptionName) const`
- L203 _public function_ `EValidatorOptionType GetOptionType(const FString& InOptionName) const`
- L208 _public prototype_ `void SetSelectedOption(const FString& InOptionName, const FString& InOptionValue);`
- L210 _public prototype_ `virtual const TArray<FAnalyticsEventAttribute> GetTelemetryAttributes() const;`
- L212 _public prototype_ `bool CanPrintErrors() const;`
- L213 _public prototype_ `void PrintErrorSummary() const;`
- L215 _public prototype_ `const FString GetValidationConfigId() const;`
- L218 _public prototype_ `template<DerivedFromDefinition T> const T* GetTypedDefinition() const;`
- L220 _public member_ `TArray<FName> Dependants;`
- L221 _public member_ `TUniquePtr<const FValidatorDefinition> Definition;`
- L222 _public member_ `TMap<FString, TArray<FString>> PathsPerExtension;` — Digested from Definition->IncludeFilesInDirectoryPerExtension
- L223 _public member_ `FOnValidatorFinished OnValidationFinished;`
- L224 _public member_ `FOnLockdownIdsChanged OnLockdownIdsChanged;`
- L226 _public member_ `FGuid CorrelationId;` — Automatically set to a new GUID each time before Validate is called
- L229 _protected member_ `FName ValidatorNameID;`
- L230 _protected member_ `FString ValidatorName;`
- L231 _protected member_ `EFailureReason FailureReason;`
- L232 _protected member_ `FValidatorOptionsProvider OptionsProvider;`
- L233 _protected member_ `TWeakPtr<FSubmitToolServiceProvider> ServiceProvider;`
- L234 _protected member_ `TArray<FSCFileRef> FilteredFiles;`
- L235 _protected member_ `TArray<FString> ActivationErrors;`
- L236 _protected member_ `mutable TArray<FString> ErrorListCache;`
- L237 _protected member_ `mutable TArray<FString> WarningListCache;`
- L238 _protected member_ `bool bIsValidSetup = false;`
- L239 _protected member_ `TSet<FString> LockdownIds;`
- L240 _protected member_ `bool bForceRun = false;`
- L241 _protected member_ `const FSubmitToolParameters& SubmitToolParameters;`
- L242 _protected member_ `bool bStealthFailure = false;`
- L243 _protected member_ `EValidationStates StealthState = EValidationStates::Not_Run;`
- L244 _protected member_ `FDateTime Start;`
- L245 _protected member_ `float RunTime = 0;`
- L252 _protected prototype_ `virtual bool Validate(const FString& CLDescription, const TArray<FSCFileRef>& FilteredFilesInCL, const TArray<const FTag*>& Tags) = 0;` — @brief Starts the validator. @param SubmitSettings The submit settings to use for this validation cycle. @return Returns true if validation has started successfully, false if validation failed.
- L254 _protected prototype_ `virtual bool AppliesToFile(const FSCFileRef InFile, bool InbAllowIncremental, bool& OutbIsIncrementalSkip) const;`
- L255 _protected prototype_ `virtual bool AppliesToCL(const FString& CLDescription, const TArray<FSCFileRef>& FilesInCL, const TArray<const FTag*>& Tags, TArray<FSCFileRef>& OutFilteredFiles, TArray<FSCFileRef>& OutIncrementalSkips, bool InbAllowIncremental) const;`
- L256 _protected function_ `virtual void StopInternalValidations()`
- L258 _protected prototype_ `virtual void ValidationFinished(const bool bHasPassed);`
- L260 _protected prototype_ `virtual void LogFailure(const FString& FormattedMsg) const;`
- L262 _protected prototype_ `virtual void Skip();`
- L263 _protected prototype_ `virtual TArray<FString> ProcessMessagesForTelemetry(const TArray<FString>& InMessages) const;`
- L264 _protected prototype_ `virtual void ProcessSingleMessageForTelemetry(FString& InOutMessage) const;`
- L265 _protected prototype_ `virtual TArray<FAnalyticsEventAttribute> GetSingleMessageTelemetryAttributes(const FString& InMessage) const;`
- L268 _protected member_ `EValidationStates State = EValidationStates::Not_Run;`
- L271 _protected member_ `mutable TMap<uint32, bool> FileHashes;`
- L272 _protected member_ `mutable FCriticalSection ErrorLogsMutex;`
- L275 _private prototype_ `void SetValidationFinished(EValidationStates NewState);`
- L279 _function_ `template<DerivedFromDefinition T> inline const T* FValidatorBase::GetTypedDefinition() const`

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnValidatorFinished, const FValidatorBase& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnLockdownIdsChanged, const FValidatorBase& ) class FValidatorBase { public: FValidatorBase() = delete;`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLockdownIdsChanged, const FValidatorBase& ) class FValidatorBase { public: FValidatorBase() = delete;`

### `Source/Programs/SubmitTool/Private/Logic/Validators/ValidatorBaseAsync.h` (Private)


#### class `FValidatorBaseAsync`  
`class FValidatorBaseAsync : public FValidatorBase`  
_L8-33_
- inherits: `FValidatorBase`
- L11 _public prototype_ `FValidatorBaseAsync(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L13 _public prototype_ `virtual bool Validate(const FString& CLDescription, const TArray<FSCFileRef>& FilteredFilesInCL, const TArray<const FTag*>& Tags) override final;`
- L19 _public prototype_ `virtual void StartAsyncWork(const FString& CLDescription, const TArray<FSCFileRef>& FilteredFilesInCL, const TArray<const FTag*>& Tags) = 0;` — Override this method to start the async work Please make sure to check that the CancellationToken has not been cancelled and stop processing in that case
- L21 _public prototype_ `virtual void Tick(float InDeltaTime) override final;`
- L22 _public prototype_ `virtual void StopInternalValidations() override final;`
- L25 _protected prototype_ `void StartAsyncTask(TFunction<bool(const UE::Tasks::FCancellationToken&)>&& InTask);`
- L29 _private prototype_ `bool HasWorkPending() const;`
- L31 _private member_ `TUniquePtr<UE::Tasks::FCancellationToken> CancellationToken;`
- L32 _private member_ `TArray<UE::Tasks::TTask<bool>> CurrentTasks;`

### `Source/Programs/SubmitTool/Private/Logic/Validators/ValidatorOptionsProvider.h` (Private)


#### enum `EValidatorOptionType`  
`enum class EValidatorOptionType`  
_L8-13_
- L10 _public enumerator_ `Standard`
- L11 _public enumerator_ `FilePath`
- L12 _public enumerator_ `Invalid`

#### class `FValidatorOptionsProvider`  
`class FValidatorOptionsProvider`  
_L15-41_
- L18 _public prototype_ `FValidatorOptionsProvider(const FName& InValidatorId);`
- L20 _public prototype_ `void InitializeValidatorOptions( const FString& InOptionName, const TMap<FString, FString>& InOptions, const FString& InSelectedOption, const EValidatorOptionType InOptionType);`
- L26 _public prototype_ `const TMap<FString, TMap<FString, FString>>& GetValidatorOptions() const;`
- L27 _public prototype_ `const TMap<FString, FString>& GetSelectedOptions() const;`
- L29 _public prototype_ `const FString GetSelectedOptionKey(const FString& InOptionName) const;`
- L30 _public prototype_ `const FString GetSelectedOptionValue(const FString& InOptionName) const;`
- L31 _public prototype_ `EValidatorOptionType GetOptionType(const FString& InOptionName) const;`
- L33 _public prototype_ `void SetSelectedOption(const FString& InOptionName, const FString& InOptionValue);`
- L34 _public prototype_ `FString GetUserPrefsKey(const FString& InOptionName);`
- L37 _private member_ `const FName ValidatorId;`
- L38 _private member_ `TMap<FString, TMap<FString, FString>> Options;`
- L39 _private member_ `TMap<FString, FString> SelectedOptions;`
- L40 _private member_ `TMap<FString, EValidatorOptionType> OptionTypes;`

### `Source/Programs/SubmitTool/Private/Logic/Validators/ValidatorRunExecutable.h` (Private)


#### struct `FProcessTrackingData`  
`struct FProcessTrackingData`  
_L10-17_
- L12 _public member_ `TOptional<bool> bSuccess;`
- L13 _public member_ `bool bIgnoringOutputError = false;`
- L14 _public member_ `bool bIgnoringWarningsAsErrors = false;`
- L15 _public member_ `TArray<FString> ErrorList;`
- L16 _public member_ `TArray<FString> WarningList;`

#### class `FValidatorRunExecutable`  
`class FValidatorRunExecutable : public FValidatorBase`  
_L29-67_
- inherits: `FValidatorBase`
- desc: @brief Runs an executable with optional arguments. Return code 0 on the executable means success. Validator values: "ExecutablePath" (required), "ExecutableArguments" (optional)
- L32 _public prototype_ `FValidatorRunExecutable(const FName& InNameId, const FSubmitToolParameters& InParameters, TSharedRef<FSubmitToolServiceProvider> InServiceProvider, const FString& InDefinition);`
- L33 _public prototype_ `virtual void ParseDefinition(const FString& InDefinition) override;`
- L35 _public prototype_ `virtual void StartValidation() override;`
- L36 _public prototype_ `virtual bool Validate(const FString& InCLDescription, const TArray<FSCFileRef>& InFilteredFilesInCL, const TArray<const FTag*>& InTags) override;`
- L37 _public function_ `virtual const FString& GetValidatorTypeName() const override`
- L38 _public prototype_ `virtual bool Activate() override;`
- L40 _public prototype_ `virtual void StopInternalValidations() override;`
- L43 _protected prototype_ `virtual bool QueueProcess(const FString& ProcessId, const FString& LocalPath, const FString& Args);`
- L44 _protected prototype_ `virtual void OnProcessOutputLine(const FString& ProcessId, FString&& Line, const EProcessOutputType& OutputType);`
- L45 _protected prototype_ `virtual bool IsLineAnError(const FString& InLine, const EProcessOutputType OutputType, bool& OutbIsWarning, bool& InOutbIgnoringOutputErrors, bool& InOutbIgnoringWarningsAsErrors);`
- L46 _protected prototype_ `virtual void OnProcessComplete(const FString& ProcessId, int32 ReturnCode);`
- L48 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L50 _protected prototype_ `virtual const TArray<FAnalyticsEventAttribute> GetTelemetryAttributes() const override;`
- L52 _protected prototype_ `bool DoesExecutableNeedBuilding() const;`
- L53 _protected prototype_ `bool FindBuildVersionForExecutable(const FString& ExecutablePath, FBuildVersion& OutBuildVersion) const;`
- L55 _protected prototype_ `void PrepareExecutableOptions();`
- L57 _protected prototype_ `static FString GetProcessName(FStringView ExecutablePath);`
- L61 _protected member_ `const FString ExecutableOptions = TEXT("Sel`
- L62 _protected member_ `TMap<FString, FProcessTrackingData> ProcessesData;`
- L63 _protected member_ `TArray<FProcessWrapper> Processes;`
- L66 _private member_ `static int32 ProcessCounter;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace SubmitToolParseConstants`
- L21 _variable_ `const FString CustomValidator = TEXT("Cus` (scope `SubmitToolParseConstants`)
- L22 _variable_ `const FString ExecutableValidator = TEXT("Exe` (scope `SubmitToolParseConstants`) — Same as Custom Validator, renaming to keep in line with class

### `Source/Programs/SubmitTool/Private/Models/ModelInterface.h` (Private)


#### enum `ESubmitToolAppState`  
`enum class ESubmitToolAppState : uint8`  
_L27-35_
- reflection: `UENUM()`
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `Initializing = 1`
- L30 _public enumerator_ `WaitingUserInput = 2`
- L31 _public enumerator_ `Errored = 3`
- L32 _public enumerator_ `P4BlockingOperation = 4`
- L33 _public enumerator_ `Submitting = 5`
- L34 _public enumerator_ `Finished = 7`

#### class `FModelInterface`  
`class FModelInterface`  
_L78-304_
- L81 _public prototype_ `FModelInterface(FSubmitToolParameters&& InParameters, const TSharedPtr<ISTSourceControlService>& InSourceControlService);`
- L82 _public prototype_ `~FModelInterface();`
- L83 _public prototype_ `void Dispose() const;`
- L84 _public prototype_ `void ParseTasksConfig(const TMap<FString, FString>& InTasksConfig, TSharedRef<FTasksService> InOutTaskService);`
- L86 _public function_ `void SetMainTab(TSharedPtr<SDockTab> InMainTab)`
- L87 _public function_ `TWeakPtr<SDockTab> GetMainTab() const`
- L88 _public function_ `void SetDescriptionBox(const TWeakPtr<SWidget> InDescriptionBox)`
- L90 _public function_ `void ApplyTag(const FString& tagID) const`
- L91 _public function_ `void ApplyTag(const FTag& tag) const`
- L92 _public function_ `void RemoveTag(const FString& tagID) const`
- L93 _public function_ `void RemoveTag(const FTag& tag) const`
- L94 _public function_ `void SetTagValues(const FString& tagID, const FString& values) const`
- L95 _public function_ `void SetTagValues(const FTag& tag, const FString& values) const`
- L96 _public function_ `void SetTagValues(const FTag& tag, const TArray<FString>& values) const`
- L97 _public function_ `void UpdateTagsInCL() const`
- L98 _public function_ `const FTag* GetTag(const FString& tagID) const`
- L99 _public function_ `const TArray<const FTag*>& GetTagsArray() const`
- L100 _public function_ `void RegisterTagUpdatedCallback(const FTagUpdated::FDelegate Callback)`
- L102 _public prototype_ `void SetCLDescription(const FText& newDescription, bool DoNotInvalidate = false);`
- L103 _public prototype_ `void GenerateCLDescription();`
- L104 _public prototype_ `void SendDescriptionToP4() const;`
- L105 _public prototype_ `void UpdateCLFromP4Async() const;`
- L106 _public function_ `const FString& GetCLDescription() const`
- L107 _public function_ `const FString GetCLID() const`
- L109 _public function_ `FOnCLDescriptionUpdated& GetCLDescriptionUpdatedDelegate()`
- L111 _public function_ `const TArray<FSCFileRef>& GetFilesInCL() const`
- L112 _public function_ `bool HasShelvedFiles() const`
- L114 _public function_ `bool IsP4OperationRunning() const`
- L115 _public function_ `bool IsBlockingOperationRunning() const`
- L116 _public function_ `void CancelP4Operations(FName OperationName = FName()) const`
- L118 _public prototype_ `void ValidateChangelist() const;`
- L119 _public prototype_ `void ValidateSingle(const FName& ValidatorId, bool bForce = true) const;`
- L120 _public prototype_ `void ValidateByArea(const ETaskArea InValidateArea) const;`
- L121 _public prototype_ `void ToggleValidator(const FName& ValidatorId);`
- L122 _public function_ `void ValidateCLDescription() const`
- L123 _public function_ `bool IsCLValid() const`
- L124 _public prototype_ `bool CanLaunchPreflight() const;`
- L125 _public prototype_ `void EvaluateDisabledValidatorsTag();`
- L126 _public prototype_ `void EvaluateFailedValidatorsTag();`
- L127 _public prototype_ `void ReevaluateSubmitToolTag();`
- L128 _public prototype_ `void UpdateSubmitToolTag(bool InbAdd);`
- L129 _public prototype_ `bool HasSubmitToolTag() const;`
- L130 _public function_ `bool IsValidationRunning() const`
- L131 _public function_ `const TArray<TWeakPtr<const FValidatorBase>>& GetValidators() const`
- L132 _public function_ `const TArray<TWeakPtr<const FValidatorBase>>& GetPreSubmitOperations() const`
- L133 _public function_ `void CancelValidations(const FName& InValidatorId = FName(), bool InbAsFailed = false) const`
- L134 _public function_ `void CheckForFileEdits() const`
- L136 _public function_ `bool IsDescriptionGenerationRunning() const`
- L138 _public function_ `FDelegateHandle AddSingleValidatorFinishedCallback (const FOnSingleTaskFinished::FDelegate& Callback) const`
- L141 _public function_ `void RemoveSingleValidatorFinishedCallback(const FDelegateHandle& Handle) const`
- L143 _public function_ `FDelegateHandle AddValidationFinishedCallback (const FOnTaskFinished::FDelegate& Callback) const`
- L146 _public function_ `void RemoveValidationFinishedCallback(const FDelegateHandle& Handle) const`
- L148 _public function_ `FDelegateHandle AddValidationUpdatedCallback (const FOnTaskRunStateChanged::FDelegate& Callback) const`
- L150 _public function_ `void RemoveValidationUpdatedCallback(const FDelegateHandle& Handle) const`
- L152 _public function_ `void GetUsers(const FOnUsersGet::FDelegate& Callback) const`
- L153 _public function_ `const TArray<TSharedPtr<FUserData>>& GetRecentUsers() const`
- L154 _public function_ `void AddRecentUser(TSharedPtr<FUserData>& User)`
- L156 _public function_ `void GetGroups(const FOnGroupsGet::FDelegate& Callback) const`
- L157 _public function_ `const TArray<TSharedPtr<FString>>& GetRecentGroups() const`
- L158 _public function_ `void AddRecentGroup(TSharedPtr<FString>& Group)`
- L159 _public function_ `FString GetUsername() const`
- L160 _public function_ `const FString GetRootStreamName() const`
- L161 _public function_ `const FString GetCurrentStream() const`
- L163 _public function_ `void SetLogin(const FString& InUsername, const FString& InPassword)`
- L165 _public prototype_ `static bool GetInputEnabled();`
- L166 _public function_ `static void SetErrorState()`
- L167 _public function_ `static const ESubmitToolAppState GetState()`
- L168 _public function_ `void DeleteShelvedFiles() const`
- L169 _public function_ `void ReplaceShelvedFiles() const`
- L172 _public prototype_ `void RequestPreflight(bool bForceStart = false);`
- L173 _public function_ `bool IsPreflightRequestInProgress() const`
- L174 _public function_ `bool IsShelfReady() const`
- L175 _public function_ `bool IsPreflightQueued() const`
- L176 _public function_ `void RefreshPreflightInformation() const`
- L177 _public function_ `const TUniquePtr<FPreflightList>& GetPreflightData()`
- L180 _public prototype_ `void ShowSwarmReview();`
- L181 _public prototype_ `void RequestSwarmReview(const TArray<FString>& InReviewers);`
- L182 _public function_ `FDelegateHandle AddPreflightUpdateCallback (const FOnPreflightDataUpdated::FDelegate& Callback) const`
- L185 _public function_ `void RemovePreflightUpdateCallback(const FDelegateHandle& Handle) const`
- L187 _public prototype_ `void StartSubmitProcess(bool bSkipShelfDialog = false);`
- L189 _public function_ `TSharedRef<FSubmitToolServiceProvider> GetServiceProvider()`
- L191 _public function_ `TWeakPtr<FJiraService> GetJiraService()`
- L192 _public function_ `TWeakPtr<FSwarmService> GetSwarmService()`
- L193 _public function_ `TWeakPtr<FPreflightService> GetPreflightService()`
- L195 _public member_ `FSubmitToolLockdownData LockdownStatus;`
- L196 _public member_ `TSet<FString> FixedLockdownIds;`
- L197 _public member_ `TMap<FName, TSet<FString>> DynamicValidatorLockdownIds;`
- L198 _public prototype_ `void DynamicValidatorLockdownRefreshed(const FValidatorBase& InValidator);`
- L199 _public prototype_ `void ReevaluateControlledLockdown();`
- L200 _public prototype_ `bool EvaluateControlledLockdownAllowed();`
- L202 _public function_ `const FSubmitToolParameters& GetParameters() const`
- L204 _public prototype_ `const FString& GetTitleMessage() const;`
- L205 _public function_ `bool IsIntegrationRequired() const`
- L206 _public function_ `bool IsSubmissionBlocked() const`
- L207 _public prototype_ `void RequestIntegration();`
- L208 _public function_ `const TMap<FString, TSharedPtr<FIntegrationOptionBase>>& GetIntegrationOptions()`
- L209 _public function_ `bool ValidateIntegrationOptions(bool bSilent) const`
- L224 _public member_ `static FOnStateChanged OnStateChanged;`
- L225 _public member_ `FOnSubmit SubmitFinishedCallback;`
- L226 _public member_ `FPreSubmitCallBack PrepareSubmitCallBack;`
- L227 _public member_ `FFilesRefresh FileRefreshedCallback;`
- L228 _public member_ `bool bSubmitOnSuccessfulValidation = false;`
- L230 _public function_ `const TUniquePtr<FSwarmReview>& GetSwarmReview() const`
- L231 _public function_ `const void RefreshSwarmReview()`
- L233 _public function_ `bool GetSwarmReviewUrl(FString& OutUrl) const`
- L236 _public function_ `bool IsAutoUpdateOn() const` — AUTO-UPDATE
- L237 _public function_ `bool CheckForNewVersion()`
- L238 _public function_ `FString GetDeployId() const`
- L239 _public function_ `FString GetLocalVersion() const`
- L240 _public function_ `FString GetLatestVersion() const`
- L241 _public function_ `void InstallLatestVersion()`
- L242 _public function_ `void CancelInstallLatestVersion()`
- L243 _public function_ `const FString GetDownloadMessage()`
- L245 _public function_ `const bool IsSwarmServiceValid()`
- L246 _public function_ `const bool HasSwarmReview()`
- L260 _private member_ `const FSubmitToolParameters Parameters;`
- L261 _private prototype_ `void OnChangelistRefresh(ETaskArea InChangeType);`
- L262 _private prototype_ `void PreValidate(const TArray<const TWeakPtr<const FValidatorBase>>& InValidators) const;`
- L263 _private prototype_ `void RefreshStateBasedOnFiles();`
- L264 _private prototype_ `void OnChangelistReady(bool bIsValid);`
- L265 _private prototype_ `void Submit();`
- L266 _private prototype_ `void OnPresubmitOperationsComplete(bool bInSuccess);`
- L267 _private prototype_ `void OnSubmitOperationComplete(const FSCCommand& InCmd);`
- L268 _private prototype_ `void OnGetUsersFromSwarmCompleted(const TUniquePtr<FSwarmReview>& InReview, const FString& InErrorMessage);`
- L269 _private prototype_ `void OnSwarmCreateCompleted(bool InResult, const FString& InErrorMessage);`
- L270 _private prototype_ `bool RemoveTagFromDescription(const FString& InTag, FString& InOutCLDescription) const;`
- L272 _private member_ `FOnChangeListReadyDelegate CLReadyCallback;`
- L273 _private member_ `FOnChangelistRefreshDelegate CLRefreshCallback;`
- L274 _private member_ `FDelegateHandle OnValidationStateUpdatedHandle;`
- L275 _private member_ `FDelegateHandle OnValidationFinishedHandle;`
- L276 _private member_ `FDelegateHandle OnPresubmitFinishedHandle;`
- L277 _private member_ `FDelegateHandle OnSingleValidationFinishedHandle;`
- L278 _private member_ `TUniquePtr<FProcessWrapper> DescGenProcess;`
- L279 _private member_ `FString GeneratedDescription;`
- L281 _private member_ `TSharedPtr<ISTSourceControlService> SourceControlService;`
- L282 _private member_ `TSharedPtr<IChangelistService> ChangelistService;`
- L283 _private member_ `TSharedPtr<ILockdownService> P4LockdownService;`
- L284 _private member_ `TSharedPtr<ITagService> TagService;`
- L285 _private member_ `TSharedPtr<FTasksService> ValidationService;`
- L286 _private member_ `TSharedPtr<FJiraService> JiraService;`
- L287 _private member_ `TSharedPtr<FPreflightService> PreflightService;`
- L288 _private member_ `TWeakPtr<SDockTab> MainTab;`
- L289 _private member_ `TWeakPtr<SWidget> DescriptionBox;`
- L290 _private member_ `TSharedPtr<FTasksService> PresubmitOperationsService;`
- L291 _private member_ `TSharedPtr<FIntegrationService> IntegrationService;`
- L292 _private member_ `TSharedPtr<FSwarmService> SwarmService;`
- L293 _private member_ `TSharedPtr<ICredentialsService> CredentialsService;`
- L294 _private member_ `TSharedPtr<FUpdateService> UpdateService;`
- L295 _private member_ `TSharedPtr<FSubmitToolServiceProvider> ServiceProvider;`
- L296 _private member_ `bool bPreflightQueued = false;`
- L297 _private member_ `bool bIsControlledLock = false;`
- L298 _private member_ `mutable FString TitleMessage;`
- L299 _private prototype_ `bool Tick(float InDeltaTime);`
- L301 _private member_ `static ESubmitToolAppState SubmitToolState;`
- L303 _private prototype_ `static void ChangeState(ESubmitToolAppState newState, bool bForce = false);`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace SubmitToolAppState`
- L39 _typedef_ `using StateList = const TArray<ESubmitToolAppState>;` (scope `SubmitToolAppState`)
- L42 _variable_ `const TMap<const ESubmitToolAppState, StateList> AllowedTransitions = { { ESubmitToolAppState::Initializing, StateList { ESubmitToolAppState::WaitingUserInput, ESubmitToolAppState::P4BlockingOperation, ESubmitToolAppState::Errored }}, { ESubmitToolAppState::WaitingUserInput, StateList { ESubmitToolAppState::Submitting, ESubmitToolAppState::Errored, ESubmitToolAppState::P4BlockingOperation }}, { ESubmitToolAppState::Errored, StateList { ESubmitToolAppState::WaitingUserInput }}, { ESubmitToolAppState::P4BlockingOperation, StateList { ESubmitToolAppState::WaitingUserInput, ESubmitToolAppState::Errored, ESubmitToolAppState::Finished }}, { ESubmitToolAppState::Submitting, StateList { ESubmitToolAppState::WaitingUserInput, ESubmitToolAppState::Errored, ESubmitToolAppState::Finished }}, { ESubmitToolAppState::Finished, StateList { ESubmitToolAppState::Errored }} };` (scope `SubmitToolAppState`) — Allowed states to transition from the original state.
- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPreSubmitCallBack) DECLARE_MULTICAST_DELEGATE(FFilesRefresh) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubmit, bool ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const ESubmitToolAppState , const ESubmitToolAppState ) class FModelInterface { public: FModelInterface(FSubmitToolParameters&& InParameters, const TSharedPtr<ISTSourceControlService>& InSourceControlService); ~FModelInterface(); void Dispose() const; void ParseTasksConfig(const TMap<FString, FString>& InTasksConfig, TSharedRef<FTasksService> InOutTaskService); void SetMainTab(TSharedPtr<SDockTab> InMainTab) { MainTab = InMainTab; } TWeakPtr<SDockTab> GetMainTab() const { return MainTab; } void SetDescriptionBox(const TWeakPtr<SWidget> InDescriptionBox) { DescriptionBox = InDescriptionBox; } void ApplyTag(const FString& tagID) const { TagService->ApplyTag(tagID);} void ApplyTag(const FTag& tag) const { TagService->ApplyTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void RemoveTag(const FString& tagID) const { TagService->RemoveTag(tagID); } void RemoveTag(const FTag& tag) const { TagService->RemoveTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void SetTagValues(const FString& tagID, const FString& values) const { TagService->SetTagValues(tagID, values); } void SetTagValues(const FTag& tag, const FString& values) const { TagService->SetTagValues(const_cast<FTag&>(tag), values); ValidationS`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE(FFilesRefresh) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubmit, bool ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const ESubmitToolAppState , const ESubmitToolAppState ) class FModelInterface { public: FModelInterface(FSubmitToolParameters&& InParameters, const TSharedPtr<ISTSourceControlService>& InSourceControlService); ~FModelInterface(); void Dispose() const; void ParseTasksConfig(const TMap<FString, FString>& InTasksConfig, TSharedRef<FTasksService> InOutTaskService); void SetMainTab(TSharedPtr<SDockTab> InMainTab) { MainTab = InMainTab; } TWeakPtr<SDockTab> GetMainTab() const { return MainTab; } void SetDescriptionBox(const TWeakPtr<SWidget> InDescriptionBox) { DescriptionBox = InDescriptionBox; } void ApplyTag(const FString& tagID) const { TagService->ApplyTag(tagID);} void ApplyTag(const FTag& tag) const { TagService->ApplyTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void RemoveTag(const FString& tagID) const { TagService->RemoveTag(tagID); } void RemoveTag(const FTag& tag) const { TagService->RemoveTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void SetTagValues(const FString& tagID, const FString& values) const { TagService->SetTagValues(tagID, values); } void SetTagValues(const FTag& tag, const FString& values) const { TagService->SetTagValues(const_cast<FTag&>(tag), values); ValidationService->InvalidateForChanges(ETaskArea::Changel`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubmit, bool ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const ESubmitToolAppState , const ESubmitToolAppState ) class FModelInterface { public: FModelInterface(FSubmitToolParameters&& InParameters, const TSharedPtr<ISTSourceControlService>& InSourceControlService); ~FModelInterface(); void Dispose() const; void ParseTasksConfig(const TMap<FString, FString>& InTasksConfig, TSharedRef<FTasksService> InOutTaskService); void SetMainTab(TSharedPtr<SDockTab> InMainTab) { MainTab = InMainTab; } TWeakPtr<SDockTab> GetMainTab() const { return MainTab; } void SetDescriptionBox(const TWeakPtr<SWidget> InDescriptionBox) { DescriptionBox = InDescriptionBox; } void ApplyTag(const FString& tagID) const { TagService->ApplyTag(tagID);} void ApplyTag(const FTag& tag) const { TagService->ApplyTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void RemoveTag(const FString& tagID) const { TagService->RemoveTag(tagID); } void RemoveTag(const FTag& tag) const { TagService->RemoveTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void SetTagValues(const FString& tagID, const FString& values) const { TagService->SetTagValues(tagID, values); } void SetTagValues(const FTag& tag, const FString& values) const { TagService->SetTagValues(const_cast<FTag&>(tag), values); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void SetTagValues(const FTag& tag,`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const ESubmitToolAppState , const ESubmitToolAppState ) class FModelInterface { public: FModelInterface(FSubmitToolParameters&& InParameters, const TSharedPtr<ISTSourceControlService>& InSourceControlService); ~FModelInterface(); void Dispose() const; void ParseTasksConfig(const TMap<FString, FString>& InTasksConfig, TSharedRef<FTasksService> InOutTaskService); void SetMainTab(TSharedPtr<SDockTab> InMainTab) { MainTab = InMainTab; } TWeakPtr<SDockTab> GetMainTab() const { return MainTab; } void SetDescriptionBox(const TWeakPtr<SWidget> InDescriptionBox) { DescriptionBox = InDescriptionBox; } void ApplyTag(const FString& tagID) const { TagService->ApplyTag(tagID);} void ApplyTag(const FTag& tag) const { TagService->ApplyTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void RemoveTag(const FString& tagID) const { TagService->RemoveTag(tagID); } void RemoveTag(const FTag& tag) const { TagService->RemoveTag(const_cast<FTag&>(tag)); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void SetTagValues(const FString& tagID, const FString& values) const { TagService->SetTagValues(tagID, values); } void SetTagValues(const FTag& tag, const FString& values) const { TagService->SetTagValues(const_cast<FTag&>(tag), values); ValidationService->InvalidateForChanges(ETaskArea::Changelist); } void SetTagValues(const FTag& tag, const TArray<FString>& values) const { TagService->Se`

### `Source/Programs/SubmitTool/Private/Parameters/SubmitToolParametersBuilder.h` (Private)


#### class `FSubmitToolParametersBuilder`  
`class FSubmitToolParametersBuilder`  
_L9-37_
- L12 _public prototype_ `FSubmitToolParametersBuilder();`
- L13 _public prototype_ `FSubmitToolParameters LoadConfigFromFiles();`
- L15 _public prototype_ `FGeneralParameters ReadGeneralParametersFromLocalConfig();`
- L18 _private member_ `TArray<FConfigLayer> ConfigHierarchy;`
- L19 _private member_ `TArray<FString> ProjectNames;`
- L21 _private prototype_ `FGeneralParameters BuildGeneralParameters(const FConfigFile& InConfigFile);`
- L22 _private prototype_ `FJiraParameters BuildJiraParameters(const FConfigFile& InConfigFile);`
- L23 _private prototype_ `FTelemetryParameters GetTelemetryParameters(const FConfigFile& InConfigFile);`
- L24 _private prototype_ `FIntegrationParameters BuildIntegrationParameters(const FConfigFile& InConfigFile);`
- L25 _private prototype_ `TArray<FTagDefinition> BuildAvailableTags(const FConfigFile& InConfigFile);`
- L26 _private prototype_ `TMap<FString, FString> BuildValidators(const FConfigFile& InConfigFile);`
- L27 _private prototype_ `TMap<FString, FString> BuildPresubmitOperations(const FConfigFile& InConfigFile);`
- L28 _private prototype_ `FCopyLogParameters BuildCopyLogParameters(const FConfigFile& InConfigFile);`
- L29 _private prototype_ `FP4LockdownParameters BuildP4LockdownParameters(const FConfigFile& InConfigFile);`
- L30 _private prototype_ `FOAuthTokenParams BuildOAuthParameters(const FConfigFile& InConfigFile);`
- L31 _private prototype_ `FIncompatibleFilesParams BuildIncompatibleFilesParameters(const FConfigFile& InConfigFile);`
- L32 _private prototype_ `FHordeParameters BuildHordeParameters(const FConfigFile& InConfigFile);`
- L33 _private prototype_ `FAutoUpdateParameters BuildAutoUpdateParameters(const FConfigFile& InConfigFile);`
- L36 _private prototype_ `FString SectionToText(const FConfigSection& InSection) const;`

### `Source/Programs/SubmitTool/Private/SubmitToolUtils.h` (Private)


#### class `FSubmitToolUtils`  
`class FSubmitToolUtils`  
_L10-17_
- L13 _public prototype_ `static void EnsureWindowIsInView(TSharedRef<SWindow> InWindow, bool bSingleWindow);`
- L14 _public prototype_ `static TSharedRef<SHorizontalBox> BuildUserPrefCheckboxUI(bool& InUserPrefOption, const FText&& InText);`
- L16 _private member_ `static TMap<FString, TMap<bool, TSet<FString>>> HierarchyWildcardsCache;`

### `Source/Programs/SubmitTool/Private/Telemetry/ITelemetry.h` (Private)


#### class `ITelemetry`  
`class ITelemetry`  
_L9-21_
- L12 _public prototype_ `virtual void Start(const FString& InCurrentStream) const = 0;`
- L13 _public prototype_ `virtual void BlockFlush(float InTimeout) const = 0;`
- L14 _public prototype_ `virtual void SubmitSucceeded(TArray<FAnalyticsEventAttribute>&& InAttribs) const = 0;`
- L15 _public prototype_ `virtual void CustomEvent(const FString& InEventId, const TArray<FAnalyticsEventAttribute>& InAttribs) const = 0;`
- L16 _public prototype_ `virtual void Exit() = 0;`
- L20 _protected member_ `bool bExiting = false;`

### `Source/Programs/SubmitTool/Private/Telemetry/NullTelemetry.h` (Private)


#### class `FNullTelemetry`  
`class FNullTelemetry : public ITelemetry`  
_L7-16_
- inherits: `ITelemetry`
- L10 _public function_ `virtual void Start(const FString& InCurrentStream) const override`
- L11 _public function_ `virtual void BlockFlush(float InTimeout) const`
- L12 _public function_ `virtual void SubmitSucceeded(TArray<FAnalyticsEventAttribute>&& InAttribs) const override`
- L13 _public function_ `virtual void CustomEvent(const FString& InEventId, const TArray<FAnalyticsEventAttribute>& InAttribs) const override`
- L14 _public function_ `virtual void Exit()`

### `Source/Programs/SubmitTool/Private/Telemetry/StandAloneTelemetry.h` (Private)


#### class `FStandAloneTelemetry`  
`class FStandAloneTelemetry : public ITelemetry`  
_L11-25_
- inherits: `ITelemetry`
- L14 _public prototype_ `FStandAloneTelemetry(const FString& InUrl, const FGuid& InSessionID);`
- L15 _public prototype_ `virtual ~FStandAloneTelemetry();`
- L16 _public prototype_ `virtual void Start(const FString& InCurrentStream) const override;`
- L17 _public prototype_ `virtual void BlockFlush(float InTimeout) const override;`
- L18 _public prototype_ `virtual void SubmitSucceeded(TArray<FAnalyticsEventAttribute>&& InAttribs) const override;`
- L19 _public prototype_ `virtual void CustomEvent(const FString& InEventId, const TArray<FAnalyticsEventAttribute>& InAttribs) const override;`
- L20 _public prototype_ `virtual void Exit() override;`
- L24 _private member_ `TSharedPtr<IAnalyticsProviderET> Provider;`

### `Source/Programs/SubmitTool/Private/Telemetry/SubmitToolStudioTelemetry.h` (Private)


#### class `FSubmitToolStudioTelemetry`  
`class FSubmitToolStudioTelemetry : public ITelemetry`  
_L7-17_
- inherits: `ITelemetry`
- L10 _public prototype_ `FSubmitToolStudioTelemetry();`
- L11 _public prototype_ `virtual ~FSubmitToolStudioTelemetry();`
- L12 _public prototype_ `virtual void Start(const FString& InCurrentStream) const override;`
- L13 _public prototype_ `virtual void BlockFlush(float InTimeout) const override;`
- L14 _public prototype_ `virtual void SubmitSucceeded(TArray<FAnalyticsEventAttribute>&& InAttribs) const override;`
- L15 _public prototype_ `virtual void CustomEvent(const FString& InEventId, const TArray<FAnalyticsEventAttribute>& InAttribs) const override;`
- L16 _public prototype_ `virtual void Exit() override;`

### `Source/Programs/SubmitTool/Private/Telemetry/TelemetryService.h` (Private)


#### class `FTelemetryService`  
`class FTelemetryService`  
_L12-23_
- L15 _public prototype_ `static const TSharedPtr<ITelemetry> & Get();`
- L16 _public prototype_ `static void Init(const FTelemetryParameters& InTelemetryParameters, const FString& InStreamName);`
- L17 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static void BlockFlush(float InTimeout);`
- L20 _private prototype_ `static void Set(TSharedPtr<ITelemetry> InInstance);`
- L21 _private member_ `static TSharedPtr<ITelemetry> TelemetryInstance;`
- L22 _private member_ `static FCriticalSection InstanceCriticalSection;`

### `Source/Programs/SubmitTool/Private/Version/AppVersion.h` (Private)


#### class `FAppVersion`  
`class FAppVersion`  
_L7-14_
- L10 _public prototype_ `static FString GetVersion();`
- L13 _private member_ `static FString Version;`

### `Source/Programs/SubmitTool/Private/Version/AppVersionDefines.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define VERSION_TEXT(x) TEXT(x)` — Macros for encoding strings
- L7 _macro_ `#define VERSION_STRINGIFY_2(x) VERSION_TEXT(#x)`
- L8 _macro_ `#define VERSION_STRINGIFY(x) VERSION_STRINGIFY_2(x)`
- L10 _macro_ `#define SUBMIT_TOOL_APPNAME TEXT("SubmitTool-Source")`
- L14 _macro_ `#define SUBMIT_TOOL_APPNAME TEXT("SubmitTool-PreRelease")`
- L19 _macro_ `#define SUBMIT_TOOL_APPNAME TEXT("SubmitTool")`
- L22 _macro_ `#define SUBMIT_TOOL_VERSION_MAJOR 6`
- L23 _macro_ `#define SUBMIT_TOOL_VERSION_MINOR 8`
- L24 _macro_ `#define SUBMIT_TOOL_VERSION_PATCH 0`
- L27 _macro_ `#define SUBMIT_TOOL_CHANGELIST_STRING TEXT("NoCL")`
- L31 _macro_ `#define SUBMIT_TOOL_CHANGELIST_STRING TEXT("CL-") VERSION_STRINGIFY(SUBMIT_TOOL_CHANGELIST)`
- L34 _macro_ `#define SUBMIT_TOOL_VERSION_STRING \`

### `Source/Programs/SubmitTool/Private/View/SubmitToolCommandHandler.h` (Private)


#### class `FSubmitToolCommandHandler`  
`class FSubmitToolCommandHandler`  
_L11-28_
- L14 _public prototype_ `void AddToCommandList(FModelInterface * InModelInterface, TSharedRef<FUICommandList> CommandList);`
- L19 _private prototype_ `void OnWidgetReflectCommandPressed();`
- L20 _private prototype_ `void OnForceCrashCommandPressed();`
- L23 _private prototype_ `void OnHelpCommandPressed();`
- L24 _private prototype_ `void OnExitCommandPressed();`
- L27 _private member_ `FModelInterface* ModelInterface;`

### `Source/Programs/SubmitTool/Private/View/SubmitToolCommandList.h` (Private)


#### class `FSubmitToolCommandList`  
`class FSubmitToolCommandList : public TCommands<FSubmitToolCommandList>`  
_L11-39_
- inherits: `TCommands<FSubmitToolCommandList>`
- L14 _public function_ `FSubmitToolCommandList() : TCommands<FSubmitToolCommandList>("SubmitToolCommands", LOCTEXT("SubmitToolCommands","Submit Tool Commands"), NAME_None, FSubmitToolStyle::Get().GetStyleSetName())`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ForceCrashCommandInfo;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> WidgetReflectCommandInfo;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> HelpCommandInfo;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ExitCommandInfo;`
- L29 _public function_ `void RegisterCommands()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "FSubmitToolCommandList"`

### `Source/Programs/SubmitTool/Private/View/SubmitToolMenu.h` (Private)


#### class `FSubmitToolMenu`  
`class FSubmitToolMenu`  
_L7-15_
- L10 _public prototype_ `static void FillMainMenuEntries(FMenuBuilder& MenuBuilder);`
- L13 _public prototype_ `static void FillDebugMenuEntries(FMenuBuilder& MenuBuilder);`

### `Source/Programs/SubmitTool/Private/View/SubmitToolStyle.h` (Private)


#### class `FSubmitToolStyle`  
`class FSubmitToolStyle : public FSlateStyleSet`  
_L8-28_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L13 _public prototype_ `static const FSubmitToolStyle& Get();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `~FSubmitToolStyle();`
- L19 _private prototype_ `FSubmitToolStyle();`
- L22 _private member_ `FSlateColor BranchedColor;` — The specific color we use for all the "Branched" icons
- L24 _private member_ `FSlateColor StatusCheckedOutColor;` — The specific colors we use for all the "Status" icons
- L26 _private member_ `static FName StyleName;`
- L27 _private member_ `static TUniquePtr<FSubmitToolStyle> Inst;`

### `Source/Programs/SubmitTool/Private/View/SubmitToolWindow.h` (Private)


#### class `SubmitToolWindow`  
`class SubmitToolWindow`  
_L11-27_
- L14 _public prototype_ `SubmitToolWindow(FModelInterface* modelInterface);`
- L16 _public prototype_ `TSharedRef<SDockTab> BuildMainTab(TSharedPtr<SWindow> InParentWindow, TSharedPtr<FSubmitToolOutputLogHistory> InLogHistory);`
- L19 _private member_ `TSharedPtr<SDockTab> MainTab;`
- L21 _private prototype_ `bool OnCanCloseTab();`
- L23 _private prototype_ `void CreateAutoUpdateSubmitToolContent(TSharedPtr<SWindow> InParentWindow, TSharedPtr<FSubmitToolOutputLogHistory> InLogHistory);`
- L24 _private prototype_ `void CreateMainSubmitToolContent(TSharedPtr<SWindow> InParentWindow, TSharedPtr<FSubmitToolOutputLogHistory> InLogHistory);`
- L26 _private member_ `FModelInterface* ModelInterface;`

### `Source/Programs/SubmitTool/Private/View/Widgets/AutoUpdateWidget.h` (Private)


#### class `SAutoUpdateWidget`  
`class SAutoUpdateWidget : public SCompoundWidget`  
_L14-32_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAutoUpdateWidget)`
- L18 _public function_ `SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_EVENT(FOnAutoUpdateCancelledSignature, OnAutoUpdateCancelled) SLATE_END_ARGS() virtual ~SAutoUpdateWidget()`
- L24 _public prototype_ `void Construct(const FArguments& InArgs);`
- L26 _private prototype_ `void Cancel();`
- L27 _private prototype_ `FString HumanReadableSize(long bytes);`
- L30 _private member_ `FModelInterface* ModelInterface;`
- L31 _private member_ `FOnAutoUpdateCancelledSignature OnAutoUpdateCancelled;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE(FOnAutoUpdateCancelledSignature) class SAutoUpdateWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SAutoUpdateWidget) {} SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_EVENT(FOnAutoUpdateCancelledSignature, OnAutoUpdateCancelled) SLATE_END_ARGS() virtual ~SAutoUpdateWidget() {} void Construct(const FArguments& InArgs); private: void Cancel(); FString HumanReadableSize(long bytes); private: FModelInterface* ModelInterface; FOnAutoUpdateCancelledSignature OnAutoUpdateCancelled; };`

### `Source/Programs/SubmitTool/Private/View/Widgets/ConfirmDialogWidget.h` (Private)


#### class `SConfirmDialogWidget`  
`class SConfirmDialogWidget : public SCompoundWidget`  
_L11-34_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SConfirmDialogWidget)`
- L15 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FText, DescriptionText) SLATE_ARGUMENT(TSharedPtr<SWidget>, AdditionalContent) SLATE_ARGUMENT(TArray<FString>, Buttons) SLATE_ARGUMENT(TFunction<bool(size_t)>, IsBtnEnabled) SLATE_EVENT(FOnResult, ResultCallback) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _private member_ `FOnResult ResultsCallback;`
- L27 _private member_ `TFunction<bool(size_t)> IsBtnEnabled = nullptr;`
- L29 _private prototype_ `void ConstructButton( const TSharedRef<SHorizontalBox> Container, size_t Idx, const FString& ButtonText, bool IsPrimary);`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DELEGATE_OneParam(FOnResult, size_t) class SHorizontalBox;`

### `Source/Programs/SubmitTool/Private/View/Widgets/SIntegrationWidget.h` (Private)


#### class `SIntegrationWidget`  
`class SIntegrationWidget final : public SCompoundWidget`  
_L24-65_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SIntegrationWidget)`
- L29 _public prototype_ `SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_ARGUMENT(TSharedPtr<SWindow>, MainWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `void Open();`
- L40 _private prototype_ `TSharedRef<SWidget> BuildOptions();`
- L41 _private prototype_ `TSharedRef<SHorizontalBox> CheckboxWithLabel(TSharedPtr<FIntegrationBoolOption> InOutOption);`
- L42 _private prototype_ `TSharedRef<SHorizontalBox> TextWithLabel(TSharedPtr<FIntegrationTextOption> InOutOption);`
- L43 _private prototype_ `TSharedRef<SVerticalBox> MultiTextWithLabel(TSharedPtr<FIntegrationTextOption> InOutOption);`
- L44 _private prototype_ `TSharedRef<SHorizontalBox> ComboWithLabel(TSharedPtr<FIntegrationComboOption> InOutOption);`
- L45 _private prototype_ `TSharedRef<SVerticalBox> PerforceUserSelect(TSharedPtr<FIntegrationTextOption> InOutOption);`
- L47 _private prototype_ `void IntegrationValueChanged(const TSharedPtr<FIntegrationOptionBase>& InOption);`
- L49 _private prototype_ `void UpdateUIOptions();`
- L51 _private prototype_ `FReply OnRequestIntegrationClicked();`
- L53 _private prototype_ `FReply OnCloseClicked();`
- L55 _private member_ `TMap<FString, TSharedRef<SWidget>> UIOptionsWidget;`
- L57 _private member_ `TSharedPtr<SWindow> MainWindow;`
- L58 _private member_ `TSharedPtr<SWindow> ParentWindow;`
- L59 _private member_ `FModelInterface* ModelInterface;`
- L60 _private member_ `bool bAreFieldsValid;`
- L62 _private prototype_ `FString GetSwarmLinkText();`
- L64 _private member_ `FString SwarmReviewID;`

### `Source/Programs/SubmitTool/Private/View/Widgets/SJiraWidget.h` (Private)


#### class `SJiraWidget`  
`class SJiraWidget : public SCompoundWidget`  
_L20-82_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SJiraWidget)`
- L24 _public prototype_ `SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `virtual ~SJiraWidget();`
- L32 _public prototype_ `void Open(const FTag* InTargetTag);`
- L33 _public prototype_ `void ProcessIssueSelected(TSharedPtr<FJiraIssue> InIssue);`
- L36 _private prototype_ `TSharedPtr<SWidget> BuildCredentialsWidget();`
- L37 _private prototype_ `TSharedPtr<SWidget> BuildIssuesWidget();`
- L39 _private prototype_ `FReply Login();`
- L40 _private prototype_ `void JiraIssuesAvailable(bool bValidResponse);`
- L42 _private prototype_ `FReply OnListKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L44 _private prototype_ `FReply OnSelectIssueClicked();`
- L46 _private prototype_ `void OnJiraDoubleClicked(TSharedPtr<FJiraIssue> InIssue);`
- L47 _private prototype_ `FReply OnCloseClicked();`
- L49 _private member_ `FDelegateHandle PresubmitCallbackHandle;`
- L50 _private prototype_ `void OnSubmitCallback();`
- L52 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<FJiraIssue> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L54 _private prototype_ `void OnColumnSort(EColumnSortPriority::Type InSortPriority, const FName& InColumnId, EColumnSortMode::Type InSortDirection);`
- L56 _private member_ `TSharedPtr<FJiraIssue> SelectedIssue;`
- L57 _private prototype_ `EColumnSortMode::Type GetSortMode(const FName ColumnId) const;`
- L59 _private member_ `FName SortByColumn;`
- L60 _private member_ `EColumnSortMode::Type SortMode;`
- L62 _private member_ `TSharedPtr<SWindow> MainWindow;`
- L64 _private member_ `TSharedPtr<SWindow> ParentWindow;`
- L66 _private member_ `TSharedPtr<SWidget> IssuesSection;`
- L67 _private member_ `TSharedPtr<SListView<TSharedPtr<FJiraIssue>>> ListView;`
- L69 _private member_ `TSharedPtr<SWidget> CredentialSection;`
- L70 _private member_ `TSharedPtr<SEditableTextBox> UsernameField;`
- L71 _private member_ `TSharedPtr<SEditableTextBox> PasswordField;`
- L73 _private member_ `TArray<TSharedPtr<FJiraIssue>> JiraIssues;`
- L74 _private member_ `TArray<TSharedPtr<FJiraIssue>> JiraIssuesFiltered;`
- L75 _private member_ `TWeakPtr<FJiraService> JiraService;`
- L76 _private member_ `FModelInterface* ModelInterface;`
- L77 _private member_ `const FTag* TargetTag;`
- L78 _private member_ `bool bIncludeClosedJira = false;`
- L80 _private member_ `FString FilterText;`
- L81 _private prototype_ `void ApplyFilter(const FString& InText);`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnJiraIssueSelected, FString) class FModelInterface;`

### `Source/Programs/SubmitTool/Private/View/Widgets/SelectSourceControlGroupWidget.h` (Private)


#### class `SSelectSourceControlGroupWidget`  
`class SSelectSourceControlGroupWidget : public SCompoundWidget`  
_L9-60_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SSelectSourceControlGroupWidget)`
- L13 _public prototype_ `SLATE_ATTRIBUTE(FText, ButtonText) SLATE_ATTRIBUTE(FModelInterface*, ModelInterface) SLATE_ATTRIBUTE(const FTag*, Tag) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `virtual ~SSelectSourceControlGroupWidget();`
- L23 _public prototype_ `FReply OnListKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L26 _private prototype_ `FReply OpenDialog();`
- L27 _private member_ `TSharedPtr<SWindow> DialogWindow;`
- L28 _private member_ `FModelInterface* ModelInterface;`
- L29 _private member_ `const FTag* TargetTag;`
- L31 _private member_ `FDelegateHandle PresubmitCallbackHandle;`
- L32 _private prototype_ `void OnSubmitCallback();`
- L34 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> GroupListView;`
- L35 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<FString> InGroup, const TSharedRef<STableViewBase>& InTableView);`
- L37 _private member_ `FString FilterText;`
- L38 _private prototype_ `void OnFilterTextChanged(const FString& InText);`
- L39 _private member_ `TArray<TSharedPtr<FString>> AllGroups;`
- L40 _private member_ `TArray<TSharedPtr<FString>> FilteredGroups;`
- L41 _private member_ `TArray<TSharedPtr<FString>> RecentGroups;`
- L43 _private prototype_ `FReply OnSelectGroupClicked();`
- L44 _private member_ `TSharedPtr<FString> SelectedGroup;`
- L46 _private prototype_ `void OnSelectGroupDoubleClicked(TSharedPtr<FString> InGroup);`
- L48 _private prototype_ `void OnGetGroups(TArray<TSharedPtr<FString>>& Groups);`
- L50 _private member_ `bool bIsLoadingGroups = true;`
- L52 _private prototype_ `FReply OnCancelClicked();`
- L54 _private prototype_ `void ProcessGroupSelected(TSharedPtr<FString> InGroup);`
- L56 _private member_ `FName SortByColumn;`
- L57 _private member_ `EColumnSortMode::Type SortMode;`
- L58 _private prototype_ `void OnColumnSort(EColumnSortPriority::Type InSortPriority, const FName& InColumnId, EColumnSortMode::Type InSortDirection);`
- L59 _private prototype_ `EColumnSortMode::Type GetSortMode(const FName ColumnId) const;`

### `Source/Programs/SubmitTool/Private/View/Widgets/SelectSourceControlUserWidget.h` (Private)


#### class `SSelectSourceControlUserWidget`  
`class SSelectSourceControlUserWidget : public SCompoundWidget`  
_L9-65_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SSelectSourceControlUserWidget)`
- L13 _public prototype_ `SLATE_ATTRIBUTE(FText, ButtonText) SLATE_ATTRIBUTE(FModelInterface*, ModelInterface) SLATE_ATTRIBUTE(FString*, TargetText) SLATE_ATTRIBUTE(FString, TargetName) SLATE_ATTRIBUTE(const FTag*, Tag) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `virtual ~SSelectSourceControlUserWidget();`
- L25 _public prototype_ `FReply OnListKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L28 _private prototype_ `FReply OpenDialog();`
- L29 _private member_ `TSharedPtr<SWindow> DialogWindow;`
- L30 _private member_ `FModelInterface* ModelInterface;`
- L31 _private member_ `const FTag* TargetTag;`
- L32 _private member_ `FString* TargetText;`
- L33 _private member_ `FString TargetName;`
- L35 _private member_ `FDelegateHandle PresubmitCallbackHandle;`
- L36 _private prototype_ `void OnSubmitCallback();`
- L38 _private member_ `TSharedPtr<SListView<TSharedPtr<FUserData>>> UserListView;`
- L39 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<FUserData> InUser, const TSharedRef<STableViewBase>& InTableView);`
- L41 _private member_ `FString FilterText;`
- L42 _private prototype_ `void OnFilterTextChanged(const FString& InText);`
- L43 _private member_ `TArray<TSharedPtr<FUserData>> AllUsers;`
- L44 _private member_ `TArray<TSharedPtr<FUserData>> FilteredUsers;`
- L45 _private member_ `TArray<TSharedPtr<FUserData>> RecentUsers;`
- L47 _private prototype_ `FReply OnSelectUserClicked();`
- L48 _private member_ `TSharedPtr<FUserData> SelectedUser;`
- L50 _private prototype_ `void OnSelectUserDoubleClicked(TSharedPtr<FUserData> InUser);`
- L52 _private prototype_ `void OnGetUsers(TArray<TSharedPtr<FUserData>>& Users);`
- L54 _private member_ `bool bIsLoadingUsers = true;`
- L55 _private member_ `bool bFilterUsers = true;`
- L57 _private prototype_ `FReply OnCancelClicked();`
- L59 _private prototype_ `void ProcessUserSelected(TSharedPtr<FUserData> InUser);`
- L61 _private member_ `FName SortByColumn;`
- L62 _private member_ `EColumnSortMode::Type SortMode;`
- L63 _private prototype_ `void OnColumnSort(EColumnSortPriority::Type InSortPriority, const FName& InColumnId, EColumnSortMode::Type InSortDirection);`
- L64 _private prototype_ `EColumnSortMode::Type GetSortMode(const FName ColumnId) const;`

### `Source/Programs/SubmitTool/Private/View/Widgets/SubmitToolHelpWidget.h` (Private)


#### class `SSubmitToolHelpWidget`  
`class SSubmitToolHelpWidget final : public SCompoundWidget`  
_L9-19_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SSubmitToolHelpWidget)`
- L13 _public prototype_ `SLATE_ATTRIBUTE(FModelInterface*, ModelInterface) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L18 _private member_ `const FModelInterface* ModelInterface;`

### `Source/Programs/SubmitTool/Private/View/Widgets/SubmitToolWidget.h` (Private)


#### class `SubmitToolWidget`  
`class SubmitToolWidget final : public SCompoundWidget`  
_L22-80_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SubmitToolWidget)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SDockTab>, ParentTab) SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FSubmitToolOutputLogHistory> InLogHistory);`
- L34 _public prototype_ `FReply SubmitClicked();`
- L35 _public prototype_ `FReply ValidateClicked();`
- L37 _private prototype_ `void OnCLDescriptionUpdated();`
- L38 _private prototype_ `void HandleApplicationActivationStateChanged(bool bActive);`
- L39 _private member_ `TWeakPtr<SDockTab> ParentTab;`
- L40 _private member_ `FModelInterface* ModelInterface;`
- L41 _private prototype_ `FText GetMainButtonText() const;`
- L42 _private prototype_ `FText GetValidateButtonText() const;`
- L43 _private prototype_ `FText GetValidateButtonTooltip() const;`
- L45 _private member_ `TSharedPtr<FTabManager> LogTabManager;`
- L46 _private member_ `TSharedPtr<SButton> ValidateBtn;`
- L47 _private prototype_ `TSharedRef<SHorizontalBox> BuildButtonRow();`
- L48 _private prototype_ `TSharedRef<SWidget> BuildOutputLogWidget(const TSharedPtr<FSubmitToolOutputLogHistory>& InLogHistory);`
- L49 _private prototype_ `TSharedRef<SExpandableArea> BuildFilesInCLWidget();`
- L52 _private member_ `TSharedPtr<SDockTab> ValidatorLogTab;`
- L53 _private member_ `const FName ValidatorLogTabId = "Va`
- L54 _private member_ `TSharedPtr<SSubmitToolOutputLog> ValidatorLogWidget;`
- L55 _private member_ `TSharedPtr<SDockTab> PresubmitLogTab;`
- L56 _private member_ `const FName PresubmitLogTabId = "Pr`
- L57 _private member_ `TSharedPtr<SSubmitToolOutputLog> PresubmitLogWidget;`
- L58 _private member_ `TSharedPtr<SDockTab> SummaryLogDockTab;`
- L59 _private member_ `const FName SummaryTabId = "Su`
- L60 _private member_ `TSharedPtr<SSubmitToolOutputLog> SummaryLogWidget;`
- L62 _private member_ `TSharedPtr<SMultiLineEditableTextBox> DescriptionBox;`
- L63 _private member_ `TSharedPtr<SIntegrationWidget> IntegrationWidget;`
- L65 _private member_ `SSplitter::FSlot* P4SectionSlot;`
- L66 _private member_ `SSplitter::FSlot* ValidatorSectionSlot;`
- L67 _private member_ `SSplitter::FSlot* LogSectionSlot;`
- L69 _private member_ `FDelegateHandle OnValidatorFinishedHandle;`
- L70 _private member_ `FDelegateHandle OnValidationQueueFinishedHandle;`
- L71 _private member_ `FDelegateHandle OnValidationUpdateHandle;`
- L72 _private member_ `FDelegateHandle OnCLDescriptionUpdatedHandle;`
- L73 _private prototype_ `void OnSingleValidatorFinished(const FValidatorBase& InValidator);`
- L74 _private prototype_ `void OnValidationQueueFinished(const bool bInSuccess);`
- L75 _private prototype_ `void OnValidationUpdated(bool bValid);`
- L78 _private prototype_ `FReply CopyAllLogsClicked();`

### `Source/Programs/SubmitTool/Private/View/Widgets/TagSectionWidget.h` (Private)


#### class `STagSectionWidget`  
`class STagSectionWidget final : public SCompoundWidget`  
_L9-18_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(STagSectionWidget)`
- L13 _public prototype_ `SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Source/Programs/SubmitTool/Private/View/Widgets/TagWidget.h` (Private)


#### class `STagWidget`  
`class STagWidget : public SCompoundWidget`  
_L17-52_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(STagWidget)`
- L21 _public prototype_ `SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_ARGUMENT(TSharedPtr<SJiraWidget>, JiraWidget) SLATE_ARGUMENT(const FTag*, Tag) SLATE_EVENT(FOnCheckboxChangedSignature, OnCheckboxChanged) SLATE_END_ARGS() virtual ~STagWidget();`
- L29 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _private prototype_ `void OnTextChanged(const FText& InText);`
- L33 _private prototype_ `void OnCheckboxChangedEvent(ECheckBoxState newState);`
- L34 _private prototype_ `void OnSelectedChangedFromMultiselect(TSharedPtr<FString> Value);`
- L35 _private prototype_ `FSlateColor GetPreflightGlobalColor() const;`
- L37 _private prototype_ `FReply OnLabelClick();`
- L38 _private prototype_ `FReply OnJiraClick();`
- L39 _private prototype_ `FReply OnPreflightClick();`
- L40 _private prototype_ `FReply OnSwarmClick();`
- L42 _private member_ `FModelInterface* ModelInterface;`
- L43 _private member_ `const FTag* Tag;`
- L44 _private member_ `FDelegateHandle PreflightUpdatedHandle;`
- L45 _private member_ `UE::Slate::Containers::TObservableArray<TSharedPtr<FString>> SelectValues;`
- L46 _private member_ `TSharedPtr<UE::Slate::Containers::TObservableArray<TSharedPtr<FPreflightData>>> PreflightListUI;`
- L49 _private member_ `TSharedPtr<SJiraWidget> JiraWidget;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCheckboxChangedSignature, ECheckBoxState) class STagWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(STagWidget) {} SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_ARGUMENT(TSharedPtr<SJiraWidget>, JiraWidget) SLATE_ARGUMENT(const FTag*, Tag) SLATE_EVENT(FOnCheckboxChangedSignature, OnCheckboxChanged) SLATE_END_ARGS() virtual ~STagWidget(); void Construct(const FArguments& InArgs); private: void OnTextChanged(const FText& InText); void OnCheckboxChangedEvent(ECheckBoxState newState); void OnSelectedChangedFromMultiselect(TSharedPtr<FString> Value); FSlateColor GetPreflightGlobalColor() const; FReply OnLabelClick(); FReply OnJiraClick(); FReply OnPreflightClick(); FReply OnSwarmClick(); FModelInterface* ModelInterface; const FTag* Tag; FDelegateHandle PreflightUpdatedHandle; UE::Slate::Containers::TObservableArray<TSharedPtr<FString>> SelectValues; TSharedPtr<UE::Slate::Containers::TObservableArray<TSharedPtr<FPreflightData>>> PreflightListUI; TSharedPtr<SJiraWidget> JiraWidget; };`

### `Source/Programs/SubmitTool/Private/View/Widgets/ValidatorsWidget.h` (Private)


#### struct `FValidatorColumn`  
`struct FValidatorColumn`  
_L14-28_
- L16 _public function_ `FValidatorColumn(FName InName, float InWidth, bool InbIsFill, const TFunction<FString(TWeakPtr<const FValidatorBase>)> InSortingFunc) : SortingFunc(InSortingFunc)`
- L24 _public member_ `FName Name;`
- L25 _public member_ `float Width;`
- L26 _public member_ `bool bIsFill;`
- L27 _public member_ `const TFunction<FString(TWeakPtr<const FValidatorBase>)> SortingFunc;`

#### class `SValidatorsWidget`  
`class SValidatorsWidget : public SCompoundWidget`  
_L30-71_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS(SValidatorsWidget)`
- L34 _public prototype_ `SLATE_ARGUMENT(FModelInterface*, ModelInterface) SLATE_EVENT(FOnViewValidatorLog, OnViewLog) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `virtual ~SValidatorsWidget();`
- L41 _public prototype_ `void ReevaluateValidatorSection();`
- L42 _public member_ `bool bDontShowDisablePopup = false;`
- L45 _private prototype_ `TSharedRef<SWidget> BuildValidatorsView(bool bListPreSubmitOperations = false);`
- L46 _private prototype_ `void AddValidatorSectionToWidget(TSharedRef<SVerticalBox> InVBox, const FName& InDisplayName, bool InbListPreSubmitOperations);`
- L47 _private prototype_ `void RefreshValidatorView(bool bListPreSubmitOperations = false);`
- L49 _private member_ `FModelInterface* ModelInterface;`
- L51 _private member_ `TSharedPtr<SListView<TWeakPtr<const FValidatorBase>>> ValidatorsListView;`
- L52 _private member_ `TSharedPtr<SListView<TWeakPtr<const FValidatorBase>>> PreSubmitListView;`
- L54 _private member_ `TMap<FName, TArray<TWeakPtr<const FValidatorBase>>> Validators;`
- L55 _private member_ `TArray<FValidatorColumn> Columns;`
- L57 _private prototype_ `TSharedRef<SHeaderRow> ConstructHeadersRow(const FName& GroupName);`
- L58 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TWeakPtr<const FValidatorBase> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L60 _private prototype_ `void OnColumnSort(const FName& GroupName, EColumnSortPriority::Type InSortPriority, const FName& InColumnId, EColumnSortMode::Type InSortDirection);`
- L61 _private prototype_ `EColumnSortMode::Type GetSortMode(const FName ColumnId) const;`
- L63 _private member_ `FName ActiveSection;`
- L64 _private member_ `FName InactiveSection;`
- L66 _private member_ `FName SortByColumn;`
- L67 _private member_ `EColumnSortMode::Type SortMode;`
- L68 _private member_ `FOnViewValidatorLog OnViewLog;`
- L69 _private member_ `FDelegateHandle OnFilesRefreshed;`
- L70 _private member_ `FDelegateHandle OnPrepareSubmit;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnViewValidatorLog, TSharedPtr<const FValidatorBase>) struct FValidatorColumn { FValidatorColumn(FName InName, float InWidth, bool InbIsFill, const TFunction<FString(TWeakPtr<const FValidatorBase>)> InSortingFunc) : SortingFunc(InSortingFunc) { Name = InName; Width = InWidth; bIsFill = InbIsFill; } FName Name; float Width; bool bIsFill; const TFunction<FString(TWeakPtr<const FValidatorBase>)> SortingFunc; };`

### `Source/Programs/SubmitTool/Public/SubmitToolApp.h` (Public)


#### Free symbols / members of external scopes

- L14 _prototype_ `int RunSubmitTool(const TCHAR* Commandline);` — Run the SubmitTool .
- L15 _prototype_ `UE::Tasks::TTask<TUniquePtr<FModelInterface>> SyncConfigAndInitializeModelInterface();`
- L16 _prototype_ `FString GetUserPrefsPath();`
