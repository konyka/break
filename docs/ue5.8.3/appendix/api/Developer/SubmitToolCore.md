# Developer / SubmitToolCore

- module root: `Source/Developer/SubmitToolCore`
- headers: 29; symbols: 728
- symbol kinds: class=21, delegate=16, enum=8, enumerator=36, function=76, macro=2, member=351, namespace=1, prototype=146, struct=55, typedef=6, variable=10
- PrivateDependencyModuleNames: AppFramework, Core, CoreUObject, Json, OutputLog
- PublicIncludePathModuleNames: TargetPlatform

### `Source/Developer/SubmitToolCore/Public/CommandLine/CmdLineParameter.h` (Public)


#### class `FCmdLineParameter`  
`class FCmdLineParameter`  
_L7-47_
- L10 _public prototype_ `FCmdLineParameter() = delete;`
- L11 _public function_ `FCmdLineParameter(FString InKey, bool InIsRequired, FString InDescription, bool InIsFlag = false, TFunction<bool(const FString& InValue)> InValidator = nullptr, TFunction<void(FString& InValue)> InParseInPlace = nullptr) : Key(InKey), bIsRequired(InIsRequired), bIsFlag(InIsFlag), Description(InDescription), Validator(InValidator), Parser(InParseInPlace)`
- L20 _public member_ `FString Key;`
- L21 _public member_ `bool bIsRequired;`
- L22 _public member_ `bool bIsFlag;`
- L23 _public member_ `FString Description;`
- L25 _public function_ `bool IsValid(const FString& value) const`
- L35 _public function_ `void CustomParse(FString& InOutValue) const`
- L45 _private member_ `TFunction<bool(const FString& InParam)> Validator;`
- L46 _private member_ `TFunction<void(FString& InParam)> Parser;`

### `Source/Developer/SubmitToolCore/Public/CommandLine/CmdLineParameters.h` (Public)


#### class `FCmdLineParameters`  
`class FCmdLineParameters`  
_L70-90_
- L73 _public prototype_ `FCmdLineParameters();`
- L74 _public prototype_ `const TCHAR* InitializeParameters() const;`
- L75 _public prototype_ `bool ValidateParameters() const;`
- L76 _public prototype_ `void LogParameters() const;`
- L78 _public prototype_ `const static FCmdLineParameters& Get();`
- L80 _public prototype_ `bool Contains(const FString& InKey) const;`
- L81 _public prototype_ `bool GetValue(const FString& InKey, FString& OutValue) const;`
- L82 _public prototype_ `bool GetValueArray(const FString& InKey, TArray<FString>& OutValue, FString&& Delimiter = TEXT(",")) const`
- L84 _private member_ `const static FCmdLineParameters Instance;`
- L85 _private prototype_ `void ConfigureCoreLimit() const;`
- L86 _private prototype_ `void ConfigurePerforce() const;`
- L87 _private prototype_ `void ConfigureTrace() const;`
- L89 _private member_ `const TArray<TSharedPtr<FCmdLineParameter>> Parameters;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace FSubmitToolCmdLine`
- L11 _variable_ `const FString P4Server = TEXT("ser` (scope `FSubmitToolCmdLine`)
- L12 _variable_ `const FString P4Client = TEXT("cli` (scope `FSubmitToolCmdLine`)
- L13 _variable_ `const FString P4User = TEXT("use` (scope `FSubmitToolCmdLine`)
- L14 _variable_ `const FString P4ChangeList = TEXT("cl"` (scope `FSubmitToolCmdLine`)
- L15 _variable_ `const FString RootDir = TEXT("roo` (scope `FSubmitToolCmdLine`)
- L16 _variable_ `const FString EditorFlag = TEXT("fro` (scope `FSubmitToolCmdLine`)
- L17 _variable_ `const FString EnableLocks = TEXT("ena` (scope `FSubmitToolCmdLine`)
- L18 _variable_ `const FString TestMode = TEXT("tes` (scope `FSubmitToolCmdLine`)
- L19 _variable_ `const FString WaitForDebugger = TEXT("wai` (scope `FSubmitToolCmdLine`)
- L21 _variable_ `const TArray<TSharedPtr<FCmdLineParameter>> SubmitToolCmdLineArgs = { MakeShared<FCmdLineParameter>(P4Server, true, TEXT("Perforce Server information, expected with format '<address>:<port>'")), MakeShared<FCmdLineParameter>(P4Client, true, TEXT("Perforce workspace name.")), MakeShared<FCmdLineParameter>(P4User, true, TEXT("Perforce user name.")), MakeShared<FCmdLineParameter>(P4ChangeList, true, TEXT("Perforce changelist number to submit."), false, [](const FString& InValue) { return InValue.IsNumeric() || InValue.Equals(TEXT("default")); }), MakeShared<FCmdLineParameter>(RootDir, false, TEXT("Root directory for the branch this change is part of"), false, nullptr, [](FString& OutValue) { TArray<TCHAR> CharactersToRemove{ '\\', '\"' , '\''}; size_t Left = 0; size_t Right = OutValue.Len() - 1; bool bKeepLooping = true; while (bKeepLooping) { bKeepLooping = false; if (CharactersToRemove.Contains(OutValue[Left])) { Left++; bKeepLooping = true; } if (CharactersToRemove.Contains(OutValue[Right])) { Right--; bKeepLooping = true; } } OutValue.MidInline(Left, (Right - Left) + 1); #if PLATFORM_WINDOWS if (OutValue.Len() > 1 && OutValue[1] == ':') { OutValue[0] = FChar::ToUpper(OutValue[0]); } #endif` (scope `FSubmitToolCmdLine`)
- L26 _function_ `MakeShared<FCmdLineParameter>(P4Server, true, TEXT("Perforce Server information, expected with format '<address>:<port>'")), MakeShared<FCmdLineParameter>(P4Client, true, TEXT("Perforce workspace name.")), MakeShared<FCmdLineParameter>(P4User, true, TEXT("Perforce user name.")), MakeShared<FCmdLineParameter>(P4ChangeList, true, TEXT("Perforce changelist number to submit."), false, [](const FString& InValue) { return InValue.IsNumeric() || InValue.Equals(TEXT("default")); }), MakeShared<FCmdLineParameter>(RootDir, false, TEXT("Root directory for the branch this change is part of"), false, nullptr, [](FString& OutValue) { TArray<TCHAR> CharactersToRemove{ '\\', '\"' , '\''}; size_t Left = 0; size_t Right = OutValue.Len() - 1; bool bKeepLooping = true; while (bKeepLooping) { bKeepLooping = false; if (CharactersToRemove.Contains(OutValue[Left])) { Left++; bKeepLooping = true; } if (CharactersToRemove.Contains(OutValue[Right])) { Right--; bKeepLooping = true; } } OutValue.MidInline(Left, (Right - Left) + 1); #if PLATFORM_WINDOWS if (OutValue.Len() > 1 && OutValue[1] == ':') { OutValue[0] = FChar::ToUpper(OutValue[0]); } #endif FPaths::NormalizeDirectoryName(OutValue); }),` (scope `FSubmitToolCmdLine`)
- L29 _function_ `` (scope `FSubmitToolCmdLine`)

### `Source/Developer/SubmitToolCore/Public/Configuration/Configuration.h` (Public)


#### class `FConfiguration`  
`class FConfiguration`  
_L7-20_
- L10 _public prototype_ `static void Init();`
- L11 _public prototype_ `static FString Substitute(const FString& InStr);`
- L12 _public prototype_ `static FString SubstituteAndNormalizeFilename(const FString& InStr);`
- L13 _public prototype_ `static FString SubstituteAndNormalizeDirectory(const FString& InStr);`
- L14 _public prototype_ `static void AddOrUpdateEntry(const FString& Key, const FString& NewValue);`
- L17 _private prototype_ `static FString GetLastSyncedCLFromUGS(const FString& InRootDir);`
- L18 _private member_ `static TSharedPtr<FConfiguration> Instance;`
- L19 _private member_ `TMap<FString, FString> Values;`

### `Source/Developer/SubmitToolCore/Public/Logging/SubmitToolLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogValidators, Verbose, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogValidators, Verbose, All);`
- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogValidatorsResult, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogValidatorsResult, Verbose, All);`
- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPresubmit, Verbose, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPresubmit, Verbose, All);`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPresubmitResult, Verbose, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPresubmitResult, Verbose, All);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitTool, Verbose, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitTool, Verbose, All);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolDebug, Verbose, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolDebug, Verbose, All);`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolP4, Verbose, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolP4, Verbose, All);`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolP4Debug, Verbose, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolP4Debug, Verbose, All);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ICacheDataService.h` (Public)


#### class `ICacheDataService`  
`class ICacheDataService : public ISubmitToolService`  
_L12-27_
- inherits: `ISubmitToolService`
- L15 _public prototype_ `virtual bool GetChangelistCacheData(const FString& InCLId, FChangelistCacheData& OutCLData) const = 0;`
- L17 _public prototype_ `virtual const FDateTime GetLastValidationDate(const FString& InCLId, const FName& InValidatorId, const FString& InValidatorConfig, const FString& InDepotPath) const = 0;`
- L18 _public prototype_ `virtual void UpdateLastValidationForFiles(const FString& InCLId, const FName& InValidatorId, const FString& InValidatorConfig, const TArray<FSCFileRef>& InFiles, const FDateTime& InNewTimestamp) = 0;`
- L20 _public prototype_ `virtual FString GetIntegrationFieldValue(const FString& InCLId, const FString& InIntegrationFieldId) const = 0;`
- L21 _public prototype_ `virtual void SetIntegrationFieldValue(const FString& InCLId, const FString& InIntegrationFieldId, const FString& InValue) = 0;`
- L23 _public prototype_ `virtual FDateTime GetLastKnownShelfUpToDate(const FString& InCLId) const = 0;`
- L24 _public prototype_ `virtual void SetLastShelfKnownUpToDate(const FString& InCLId, const FDateTime& InDateTime) = 0;`
- L26 _public prototype_ `virtual void SaveCacheToDisk() = 0;`

#### Free symbols / members of external scopes

- L29 _prototype_ `Expose_TNameOf(ICacheDataService);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/IChangelistService.h` (Public)


#### class `IChangelistService`  
`class IChangelistService : public ISubmitToolService`  
_L14-44_
- inherits: `ISubmitToolService`
- L17 _public prototype_ `virtual const FString GetCLID() const = 0;`
- L18 _public prototype_ `virtual const FString& GetCLDescription() = 0;`
- L19 _public prototype_ `virtual bool SetCLDescription(const FString& NewDescription, bool bNotifyEvent = false) = 0;`
- L20 _public prototype_ `virtual const TArray<FSCFileRef>& GetFilesInCL() const = 0;`
- L21 _public prototype_ `virtual const TArray<FSCFileRef>& GetShelvedFilesInCL() const = 0;`
- L22 _public prototype_ `virtual bool HasShelvedFiles() const = 0;`
- L23 _public prototype_ `virtual bool HasP4OperationsRunning() const = 0;`
- L24 _public prototype_ `virtual bool IsShelfReady() const = 0;`
- L25 _public prototype_ `virtual bool IsShelfComplete() const = 0;`
- L26 _public prototype_ `virtual const TMap<FString, FString>& GetOpenFilesInChangelists() const = 0;`
- L28 _public prototype_ `virtual void Init() = 0;`
- L29 _public prototype_ `virtual void Submit(const FString& InDescriptionAddendum = TEXT(""), TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0;`
- L30 _public prototype_ `virtual void CreateCLFromDefaultCL() = 0;`
- L31 _public prototype_ `virtual void FetchChangelistDataAsync() = 0;`
- L32 _public prototype_ `virtual void RevertUnchangedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0;`
- L33 _public prototype_ `virtual void UpdateP4CLDescription() = 0;`
- L34 _public prototype_ `virtual void UpdateP4CLDescriptionSynchronously() = 0;`
- L35 _public prototype_ `virtual void DeleteShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0;`
- L36 _public prototype_ `virtual void ReplaceShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0;`
- L37 _public prototype_ `virtual void CreateShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0;`
- L38 _public prototype_ `virtual void UpdateShelvedFiles(TArray<FString> InFiles, TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0;`
- L39 _public prototype_ `virtual void CheckShelfIsUpToDate(TFunction<void(bool, TArray<FString>)> OnComplete) = 0;`
- L40 _public prototype_ `virtual void EnsureShelfIsCurrent() = 0;`
- L41 _public prototype_ `virtual void CancelP4Operations() = 0;`
- L43 _public member_ `FOnCLDescriptionUpdated OnCLDescriptionUpdated;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCLDescriptionUpdated) DECLARE_DELEGATE_OneParam(FOnChangeListReadyDelegate, bool ) DECLARE_DELEGATE_OneParam(FOnChangelistRefreshDelegate, ETaskArea ) class IChangelistService : public ISubmitToolService { public: virtual const FString GetCLID() const = 0; virtual const FString& GetCLDescription() = 0; virtual bool SetCLDescription(const FString& NewDescription, bool bNotifyEvent = false) = 0; virtual const TArray<FSCFileRef>& GetFilesInCL() const = 0; virtual const TArray<FSCFileRef>& GetShelvedFilesInCL() const = 0; virtual bool HasShelvedFiles() const = 0; virtual bool HasP4OperationsRunning() const = 0; virtual bool IsShelfReady() const = 0; virtual bool IsShelfComplete() const = 0; virtual const TMap<FString, FString>& GetOpenFilesInChangelists() const = 0; virtual void Init() = 0; virtual void Submit(const FString& InDescriptionAddendum = TEXT(""), TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void CreateCLFromDefaultCL() = 0; virtual void FetchChangelistDataAsync() = 0; virtual void RevertUnchangedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void UpdateP4CLDescription() = 0; virtual void UpdateP4CLDescriptionSynchronously() = 0; virtual void DeleteShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void ReplaceShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void CreateShelvedFiles(TFunction<void(const FSCCommand&)> OnCom`
- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChangeListReadyDelegate, bool ) DECLARE_DELEGATE_OneParam(FOnChangelistRefreshDelegate, ETaskArea ) class IChangelistService : public ISubmitToolService { public: virtual const FString GetCLID() const = 0; virtual const FString& GetCLDescription() = 0; virtual bool SetCLDescription(const FString& NewDescription, bool bNotifyEvent = false) = 0; virtual const TArray<FSCFileRef>& GetFilesInCL() const = 0; virtual const TArray<FSCFileRef>& GetShelvedFilesInCL() const = 0; virtual bool HasShelvedFiles() const = 0; virtual bool HasP4OperationsRunning() const = 0; virtual bool IsShelfReady() const = 0; virtual bool IsShelfComplete() const = 0; virtual const TMap<FString, FString>& GetOpenFilesInChangelists() const = 0; virtual void Init() = 0; virtual void Submit(const FString& InDescriptionAddendum = TEXT(""), TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void CreateCLFromDefaultCL() = 0; virtual void FetchChangelistDataAsync() = 0; virtual void RevertUnchangedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void UpdateP4CLDescription() = 0; virtual void UpdateP4CLDescriptionSynchronously() = 0; virtual void DeleteShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void ReplaceShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void CreateShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void UpdateShelvedFile`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChangelistRefreshDelegate, ETaskArea ) class IChangelistService : public ISubmitToolService { public: virtual const FString GetCLID() const = 0; virtual const FString& GetCLDescription() = 0; virtual bool SetCLDescription(const FString& NewDescription, bool bNotifyEvent = false) = 0; virtual const TArray<FSCFileRef>& GetFilesInCL() const = 0; virtual const TArray<FSCFileRef>& GetShelvedFilesInCL() const = 0; virtual bool HasShelvedFiles() const = 0; virtual bool HasP4OperationsRunning() const = 0; virtual bool IsShelfReady() const = 0; virtual bool IsShelfComplete() const = 0; virtual const TMap<FString, FString>& GetOpenFilesInChangelists() const = 0; virtual void Init() = 0; virtual void Submit(const FString& InDescriptionAddendum = TEXT(""), TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void CreateCLFromDefaultCL() = 0; virtual void FetchChangelistDataAsync() = 0; virtual void RevertUnchangedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void UpdateP4CLDescription() = 0; virtual void UpdateP4CLDescriptionSynchronously() = 0; virtual void DeleteShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void ReplaceShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void CreateShelvedFiles(TFunction<void(const FSCCommand&)> OnComplete = nullptr) = 0; virtual void UpdateShelvedFiles(TArray<FString> InFiles, TFunction<void(const FSCCommand&)>`
- L46 _prototype_ `Expose_TNameOf(IChangelistService);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ICredentialsService.h` (Public)


#### class `ICredentialsService`  
`class ICredentialsService : public ISubmitToolService`  
_L10-25_
- inherits: `ISubmitToolService`
- L13 _public prototype_ `virtual bool HasJiraCredentials() const = 0;`
- L14 _public prototype_ `virtual const FString& GetEncodedLoginString() const = 0;`
- L15 _public prototype_ `virtual FString GetUsername() const = 0;`
- L16 _public prototype_ `virtual bool IsOIDCTokenEnabled() = 0;`
- L17 _public prototype_ `virtual bool IsTokenReady() const = 0;`
- L18 _public prototype_ `virtual const FString& GetToken() const = 0;`
- L19 _public prototype_ `virtual UE::Tasks::TTask<void> QueueWorkForToken(TFunction<void(const FString&)> InFunction) = 0;`
- L21 _public prototype_ `virtual void InvalidateCredentials() = 0;`
- L22 _public prototype_ `virtual void SetLogin(const FString& InUsername, const FString& InPassword) = 0;`
- L23 _public prototype_ `virtual void SetJiraToken(FJiraToken&& InJiraToken) = 0;`
- L24 _public prototype_ `virtual const TUniquePtr<FJiraToken>& GetJiraToken() const = 0;`

#### Free symbols / members of external scopes

- L27 _prototype_ `Expose_TNameOf(ICredentialsService);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ILockdownService.h` (Public)


#### class `ILockdownService`  
`class ILockdownService : public ISubmitToolService`  
_L10-15_
- inherits: `ISubmitToolService`
- L13 _public prototype_ `virtual FSubmitToolLockdownData ArePathsInLockdown(const TArray<FSCFileRef>& InPaths, const TSet<FString>& InDynamicFiles = TSet<FString>()) = 0;`
- L14 _public prototype_ `virtual bool IsBlockingOperationRunning() const = 0;`

#### Free symbols / members of external scopes

- L17 _prototype_ `Expose_TNameOf(ILockdownService);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ISTSourceControlService.h` (Public)


#### struct `FAuthTicket`  
`struct FAuthTicket`  
_L12-40_
- L15 _public prototype_ `FAuthTicket() = default;`
- L16 _public function_ `FAuthTicket(const FString& InUsername, const FString& InPassword) : Username(InUsername), Password(InPassword)`
- L17 _public function_ `FAuthTicket(FStringView TicketString)`
- L26 _public function_ `virtual ~FAuthTicket()`
- L28 _public function_ `virtual FString ToString() const`
- L33 _public function_ `bool IsValid() const`
- L37 _public member_ `FString Username;`
- L39 _private member_ `FString Password;`

#### struct `FUserData`  
`struct FUserData`  
_L42-62_
- L44 _public function_ `FUserData(const FString& Username, const FString& Name, const FString& Email) : Name(Name), Username(Username), Email(Email)`
- L47 _public member_ `FString Name;`
- L48 _public member_ `FString Username;`
- L49 _public member_ `FString Email;`
- L51 _public function_ `bool Contains(const FString& SubString) const`
- L58 _public function_ `FString GetDisplayText()`

#### struct `FSCResultInfo`  
`struct FSCResultInfo`  
_L64-83_
- L67 _public function_ `void Append(const FSCResultInfo& InResultInfo)` — Append any messages from another FSCResultInfo, ensuring to keep any already accumulated info.
- L73 _public function_ `bool HasErrors() const`
- L79 _public member_ `TArray<FText> InfoMessages;` — Info and/or warning message storage
- L82 _public member_ `TArray<FText> ErrorMessages;` — Potential error message storage

#### struct `FSCCStream`  
`struct FSCCStream`  
_L86-97_
- L89 _public function_ `FSCCStream(const FString& InName, const FString& InParent, const FString& InType) : Name(InName), Parent(InParent), Type(InType)`
- L92 _public member_ `const FString Name;`
- L93 _public member_ `const FString Parent;`
- L94 _public member_ `const FString Type;`
- L96 _public member_ `TArray<const FString> AdditionalImportPaths;`

#### struct `FSCCommand`  
`struct FSCCommand`  
_L102-116_
- L105 _public member_ `FString Command;` — in
- L106 _public member_ `TArray<FString> Args;`
- L107 _public member_ `bool bCollectData = false;`
- L108 _public member_ `bool bSilentErrors = false;`
- L109 _public member_ `FString InputData;`
- L111 _public member_ `FSCCRecordSet Values;` — out
- L112 _public member_ `FSCResultInfo Results;`
- L113 _public member_ `TMap<FString, FSharedBuffer> Data;`
- L114 _public member_ `bool bSuccess = false;`
- L115 _public member_ `bool bDroppedConnection = false;`

#### class `ISTSourceControlService`  
`class ISTSourceControlService : public ISubmitToolService`  
_L124-198_
- inherits: `ISubmitToolService`
- L127 _public prototype_ `virtual void InitializeParameters(const FSubmitToolParameters& InParameters) = 0;`
- L128 _public prototype_ `virtual void GetUsers(const FOnUsersGet::FDelegate& Callback) = 0;`
- L129 _public prototype_ `virtual void GetGroups(const FOnGroupsGet::FDelegate& Callback) = 0;`
- L130 _public prototype_ `virtual void GetUsersAndGroups(const FOnUsersAndGroupsGet::FDelegate& Callback) = 0;`
- L132 _public prototype_ `virtual UE::Tasks::TTask<bool> DownloadFiles(TArray<FString>&& FilePaths, TMap<FString, FSharedBuffer>& OutFileBuffers, bool bSilentErrors = false) = 0;`
- L133 _public prototype_ `virtual const TArray<TSharedPtr<FUserData>>& GetRecentUsers() const = 0;`
- L134 _public prototype_ `virtual void AddRecentUser(TSharedPtr<FUserData>& User) = 0;`
- L135 _public prototype_ `virtual const TArray<TSharedPtr<FString>>& GetRecentGroups() const = 0;`
- L136 _public prototype_ `virtual void AddRecentGroup(TSharedPtr<FString>& Group) = 0;`
- L138 _public prototype_ `virtual TSharedPtr<FUserData> GetUserDataFromCache(const FString& Username) const = 0;`
- L140 _public prototype_ `virtual const TArray<FSCCStream*>& GetClientStreams() const = 0;`
- L141 _public prototype_ `virtual const FSCCStream* GetSCCStream(const FString& InStreamName) = 0;`
- L142 _public prototype_ `virtual const FString GetRootStreamName() = 0;`
- L143 _public prototype_ `virtual const FString GetCurrentStreamName() = 0;`
- L144 _public prototype_ `virtual int32 GetDepotStreamDepth(const FString& InDepotName) = 0;`
- L145 _public prototype_ `virtual const FAuthTicket& GetAuthTicket() = 0;`
- L146 _public prototype_ `virtual void RequestCancel() = 0;`
- L147 _public prototype_ `virtual bool IsBusy() const = 0;`
- L149 _public function_ `void RunCommand(FSCCommand&& InCommand, FOnSCCCommandComplete InCompleteCallback)`
- L166 _public function_ `void RunCommand(FString&& InCommand, TArray<FString>&& InAdditionalArgs, FOnSCCCommandComplete InCompleteCallback, bool bSilentErrors = false)` — Runs the command in a task thread and the provided callback in a dependent GT task.
- L173 _public function_ `UE::Tasks::TTask<TSharedRef<FSCCommand>> RunCommand(FString&& InCommand, TArray<FString>&& InAdditionalArgs, bool bSilentErrors = false)` — Runs the command in a task thread, calling GetResult() will wait until the task is completed and return the command data.
- L184 _public function_ `FSCCommand RunSyncCommand(FString&& InCommand, TArray<FString>&& InAdditionalArgs, bool bSilentErrors = false)` — Runs the command synchronously and returns the command data
- L191 _public function_ `void RunSyncCommand(FSCCommand& InCommand)`
- L196 _protected prototype_ `virtual bool RunCommandInternal(FSCCommand& InCommand) = 0;`

#### Free symbols / members of external scopes

- L99 _typedef_ `using FSCCRecord = TMap<FString, FString>;`
- L100 _typedef_ `using FSCCRecordSet = TArray<FSCCRecord>;`
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUsersGet, TArray<TSharedPtr<FUserData>>& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupsGet, TArray<TSharedPtr<FString>>& ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUsersAndGroupsGet, TArray<TSharedPtr<FUserData>>& , TArray<TSharedPtr<FString>>& ) using FOnSCCCommandComplete = TDelegate<void(const FSCCommand&)>;`
- L119 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupsGet, TArray<TSharedPtr<FString>>& ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUsersAndGroupsGet, TArray<TSharedPtr<FUserData>>& , TArray<TSharedPtr<FString>>& ) using FOnSCCCommandComplete = TDelegate<void(const FSCCommand&)>;`
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUsersAndGroupsGet, TArray<TSharedPtr<FUserData>>& , TArray<TSharedPtr<FString>>& ) using FOnSCCCommandComplete = TDelegate<void(const FSCCommand&)>;`
- L122 _typedef_ `using FOnSCCCommandComplete = TDelegate<void(const FSCCommand&)>;`
- L155 _function_ `` (scope `ISTSourceControlService::RunCommand`)
- L158 _function_ `` (scope `ISTSourceControlService::RunCommand::__anonb9d4e70f0102`)
- L200 _prototype_ `Expose_TNameOf(ISTSourceControlService);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ISubmitToolExtensions.h` (Public)


#### class `ISubmitToolExtensions`  
`class ISubmitToolExtensions : public ISubmitToolService`  
_L13-20_
- inherits: `ISubmitToolService`
- L16 _public prototype_ `virtual TOptional<FPreflightTemplateDefinition> SelectPreflightTemplate( const TArray<FSCFileRef>& InFilesInCL, const TSharedPtr<FSubmitToolServiceProvider>& InServiceProvider, const FHordeParameters& InHordeParams) const = 0;`

#### Free symbols / members of external scopes

- L22 _prototype_ `Expose_TNameOf(ISubmitToolExtensions);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ISubmitToolService.h` (Public)


#### class `ISubmitToolService`  
`class ISubmitToolService`  
_L7-11_
- L10 _public prototype_ `virtual ~ISubmitToolService() = default;`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/Interfaces/ITagService.h` (Public)


#### class `ITagService`  
`class ITagService : public ISubmitToolService`  
_L9-29_
- inherits: `ISubmitToolService`
- L12 _public prototype_ `virtual FTag* GetTag(const FString& InTagID) = 0;`
- L13 _public prototype_ `virtual FTag* GetTagOfType(const FString& InType) = 0;`
- L14 _public prototype_ `virtual FTag* GetTagOfSubtype(const FString& InTagSubtype) = 0;`
- L15 _public prototype_ `virtual const TArray<const FTag*>& GetTagsArray() const = 0;`
- L17 _public prototype_ `virtual void ParseCLDescription() = 0;`
- L18 _public prototype_ `virtual void ReApplyTags() = 0;`
- L19 _public prototype_ `virtual void ApplyTag(const FString& InTagID) = 0;`
- L20 _public prototype_ `virtual void ApplyTag(FTag& InTag) = 0;`
- L21 _public prototype_ `virtual void UpdateTagsInCL() = 0;`
- L22 _public prototype_ `virtual void RemoveTag(const FString& InTagID) = 0;`
- L23 _public prototype_ `virtual void RemoveTag(FTag& InTag) = 0;`
- L24 _public prototype_ `virtual void SetTagValues(const FString& InTagID, const FString& InValues) = 0;`
- L25 _public prototype_ `virtual void SetTagValues(FTag& InTag, const FString& InValues) = 0;`
- L26 _public prototype_ `virtual void SetTagValues(FTag& InTag, const TArray<FString>& InValues) = 0;`
- L28 _public member_ `FTagUpdated OnTagUpdated;`

#### Free symbols / members of external scopes

- L31 _prototype_ `Expose_TNameOf(ITagService);`

### `Source/Developer/SubmitToolCore/Public/Logic/Services/SubmitToolServiceProvider.h` (Public)


#### class `FSubmitToolServiceProvider`  
`class FSubmitToolServiceProvider final`  
_L14-73_
- L18 _public function_ `FSubmitToolServiceProvider()`
- L23 _public member_ `inline static FOnProviderReady OnProviderReady;`
- L26 _public function_ `template<DerivedFromISubmitToolService T> TSharedPtr<T> GetService()`
- L38 _public function_ `template<DerivedFromISubmitToolService T> bool HasService() const`
- L44 _public function_ `template<DerivedFromISubmitToolService T> TSharedPtr<T> GetService(const FString& InName)`
- L55 _public function_ `template<DerivedFromISubmitToolService T> void RegisterService(TSharedRef<T> InService)`
- L64 _public function_ `template<DerivedFromISubmitToolService T> void RegisterService(TSharedRef<T> InService, const FString& InName)`
- L72 _private member_ `TMap<FString, TSharedPtr<ISubmitToolService>> Services;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProviderReady, FSubmitToolServiceProvider& ) class FSubmitToolServiceProvider final { public: FSubmitToolServiceProvider() { OnProviderReady.Broadcast(*this); } inline static FOnProviderReady OnProviderReady; template<DerivedFromISubmitToolService T> TSharedPtr<T> GetService() { FString TypeIdx = TNameOf<T>::GetName(); if(Services.Contains(TypeIdx)) { return StaticCastSharedPtr<T>(Services[TypeIdx]); } return nullptr; } template<DerivedFromISubmitToolService T> bool HasService() const { return Services.Contains(TNameOf<T>::GetName()); } template<DerivedFromISubmitToolService T> TSharedPtr<T> GetService(const FString& InName) { if (Services.Contains(InName)) { return StaticCastSharedPtr<T>(Services[InName]); } return nullptr;`

### `Source/Developer/SubmitToolCore/Public/Logic/Validators/ValidatorDefinition.h` (Public)


#### enum `ETaskArea`  
`enum class ETaskArea : uint8`  
_L12-23_
- reflection: `UENUM()`
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Changelist = 1 << 0`
- L16 _public enumerator_ `LocalFiles = 1 << 1`
- L17 _public enumerator_ `ShelvedFiles = 1 << 2`
- L20 _public enumerator_ `ShelveAndLocalFiles = LocalFiles | ShelvedFiles`
- L21 _public enumerator_ `Everything = UINT8_MAX`

#### struct `FPathPerExtension`  
`struct FPathPerExtension`  
_L27-36_
- reflection: `USTRUCT()`
- L32 _public member_ `FString Extension;` — `UPROPERTY()`
- L35 _public member_ `FString Path;` — `UPROPERTY()`

#### struct `FValidatorDefinition`  
`struct FValidatorDefinition`  
_L39-306_
- reflection: `USTRUCT()`
- L50 _public member_ `FString Type;` — `UPROPERTY()`
- L57 _public member_ `bool bIsStealthMode = false;` — `UPROPERTY()` — <summary> This is a mode that will make the validator not report any errors or warnings to the program/user but still log them to telemetry It doesn't matter if it fails, it will always report as succeed and never block submission. </summary>
- L63 _public member_ `bool bIsDisabled = false;` — `UPROPERTY()`
- L69 _public member_ `bool bCanBeDisabledByUser = true;` — `UPROPERTY()`
- L75 _public member_ `bool bCanBeStoppedByUser = true;` — `UPROPERTY()`
- L81 _public member_ `bool IsRequired = true;` — `UPROPERTY()`
- L87 _public member_ `bool bRequireCompleteWhenOptional = false;` — `UPROPERTY()`
- L93 _public member_ `float TimeoutLimit = -1;` — `UPROPERTY()`
- L99 _public member_ `FString CustomName;` — `UPROPERTY()`
- L106 _public member_ `FString AppliesToCLRegex;` — `UPROPERTY()`
- L112 _public member_ `TArray<FString> CheckFileExists;` — `UPROPERTY()`
- L118 _public member_ `FString NotApplicableToCLMessage;` — `UPROPERTY()`
- L125 _public member_ `TArray<FString> IncludeFilesWithExtension;` — `UPROPERTY()`
- L132 _public member_ `FString IncludeFilesInDirectory;` — `UPROPERTY()`
- L146 _public member_ `TArray<FPathPerExtension> IncludeFilesInDirectoryPerExtension;` — `UPROPERTY()`
- L153 _public member_ `FString RequireFileInHierarchy;` — `UPROPERTY()`
- L160 _public member_ `FString ExcludeWhenFileInHierarchy;` — `UPROPERTY()`
- L166 _public member_ `FString ChangelistDescriptionAddendum;` — `UPROPERTY()`
- L172 _public member_ `bool bAppendAddendumOnAnyResult = false;` — `UPROPERTY()`
- L178 _public member_ `bool bSkipWhenAddendumInDescription = false;` — `UPROPERTY()`
- L184 _public member_ `bool bSkipWhenCalledFromEditor = false;` — `UPROPERTY()`
- L190 _public member_ `bool bRequiresSTLaunchedFromEditor = false;` — `UPROPERTY()` — <summary> This validator will only be applicable when running from editor (-from-editor is present) </summary>
- L196 _public member_ `bool bRequiresSTLaunchedStandalone = false;` — `UPROPERTY()` — <summary> This validator will only be applicable when NOT running from editor (-from-editor is not present) </summary>
- L202 _public member_ `TArray<FString> SkipForbiddenTags;` — `UPROPERTY()`
- L208 _public member_ `TArray<FString> SkipForbiddenFiles;` — `UPROPERTY()`
- L214 _public member_ `TArray<FString> SkipForbiddenStreams;` — `UPROPERTY()`
- L220 _public member_ `TArray<FName> DependsOn;` — `UPROPERTY()`
- L226 _public member_ `TArray<FName> ExecutionBlockGroups;` — `UPROPERTY()`
- L232 _public member_ `bool bAcceptDeletedFiles = false;` — `UPROPERTY()`
- L238 _public member_ `bool bTreatWarningsAsErrors = false;` — `UPROPERTY()`
- L241 _public member_ `bool bInvalidatesWhenOutOfDate = false;` — `UPROPERTY()`
- L247 _public member_ `bool bUsesIncrementalCache = false;` — `UPROPERTY()`
- L253 _public member_ `TArray<FString> AdditionalValidationErrorMessages;` — `UPROPERTY()`
- L259 _public member_ `FString ToolTip;` — `UPROPERTY()`
- L265 _public member_ `ETaskArea TaskArea = ETaskArea::Everything;` — `UPROPERTY()`
- L268 _public member_ `bool bBlocksPreflightStart = true;` — `UPROPERTY()`
- L275 _public member_ `FString PopupMessageWhenFailed = FString();` — `UPROPERTY()`
- L281 _public member_ `bool bRegisterFailureInCLDescription = false;` — `UPROPERTY()`
- L287 _public member_ `bool bRequireShelveOperation = false;` — `UPROPERTY()`
- L290 _public member_ `int32 MinMemoryGBRequired = 0;` — `UPROPERTY()`
- L293 _public member_ `FString NotEnoughMemoryMessage = TEXT("The` — `UPROPERTY()`
- L296 _public member_ `bool bAllowSkippingOnMemoryFail = false;` — `UPROPERTY()`
- L299 _public member_ `FString PreflightTemplate;` — `UPROPERTY()`
- L305 _public member_ `bool bIncludeWarningsInErrorSummary = true;` — `UPROPERTY()`

#### struct `FRegexLockdownTrigger`  
`struct FRegexLockdownTrigger`  
_L309-320_
- reflection: `USTRUCT()`
- L314 _public member_ `FString RegexPath;` — `UPROPERTY()`
- L316 _public member_ `TSharedPtr<FRegexPattern> BuiltRegex;`
- L319 _public member_ `FString LockdownId;` — `UPROPERTY()`

#### struct `FValidatorRunExecutableDefinition`  
`struct FValidatorRunExecutableDefinition : public FValidatorDefinition`  
_L324-452_
- reflection: `USTRUCT()`
- inherits: `FValidatorDefinition`
- L329 _public member_ `bool bLaunchHidden = true;` — `UPROPERTY()`
- L332 _public member_ `bool bLaunchReallyHidden = true;` — `UPROPERTY()`
- L335 _public member_ `bool bValidateExecutableExists = true;` — `UPROPERTY()`
- L338 _public member_ `bool bAllowProcessConcurrency = false;` — `UPROPERTY()`
- L344 _public member_ `FString ExecutablePath;` — `UPROPERTY()`
- L350 _public member_ `TMap<FString, FString> ExecutableCandidates;` — `UPROPERTY()`
- L356 _public member_ `bool bUseLatestExecutable;` — `UPROPERTY()`
- L362 _public member_ `FString ExecutableArguments;` — `UPROPERTY()`
- L368 _public member_ `FString FromEditorOnlyArguments;` — `UPROPERTY()`
- L371 _public member_ `FString FileInCLArgument;` — `UPROPERTY()`
- L378 _public member_ `FString FileListArgument;` — `UPROPERTY()`
- L384 _public member_ `TArray<FString> ErrorMessages;` — `UPROPERTY()`
- L390 _public member_ `TArray<FString> IgnoredErrorMessages;` — `UPROPERTY()`
- L396 _public member_ `TArray<int32> AllowedExitCodes = {0};` — `UPROPERTY()`
- L402 _public member_ `bool bOnlyLookAtExitCode = false;` — `UPROPERTY()`
- L408 _public member_ `FString DisableOutputErrorsAnchor;` — `UPROPERTY()`
- L414 _public member_ `FString EnableOutputErrorsAnchor;` — `UPROPERTY()`
- L420 _public member_ `FString DisableWarningsAsErrorsAnchor;` — `UPROPERTY()`
- L426 _public member_ `FString EnableWarningsAsErrorsAnchor;` — `UPROPERTY()`
- L432 _public member_ `FString RegexErrorParsing = TEXT("^(?` — `UPROPERTY()`
- L434 _public member_ `TSharedPtr<FRegexPattern> BuiltRegexError;`
- L440 _public member_ `FString RegexWarningParsing = TEXT("^(?` — `UPROPERTY()`
- L442 _public member_ `TSharedPtr<FRegexPattern> BuiltRegexWarning;`
- L448 _public member_ `TArray<FString> NonZeroExitCodeErrorMessages;` — `UPROPERTY()`
- L451 _public member_ `TArray<FRegexLockdownTrigger> LogLockdownTriggers;` — `UPROPERTY()`

#### struct `FUBTValidatorDefinition`  
`struct FUBTValidatorDefinition : public FValidatorRunExecutableDefinition`  
_L456-495_
- reflection: `USTRUCT()`
- inherits: `FValidatorRunExecutableDefinition`
- L461 _public member_ `FString Configuration;` — `UPROPERTY()`
- L464 _public member_ `FString Platform;` — `UPROPERTY()`
- L467 _public member_ `FString Target;` — `UPROPERTY()`
- L470 _public member_ `FString ProjectArgument;` — `UPROPERTY()`
- L473 _public member_ `FString TargetListArgument;` — `UPROPERTY()`
- L476 _public member_ `TArray<FString> Configurations;` — `UPROPERTY()`
- L479 _public member_ `TArray<FString> Platforms;` — `UPROPERTY()`
- L482 _public member_ `TArray<FString> Targets;` — `UPROPERTY()`
- L485 _public member_ `TArray<FString> StaticAnalysers;` — `UPROPERTY()`
- L488 _public member_ `FString StaticAnalyserArg;` — `UPROPERTY()`
- L491 _public member_ `FString StaticAnalyser;` — `UPROPERTY()`
- L494 _public member_ `bool bUseStaticAnalyser = false;` — `UPROPERTY()`

#### struct `FPackageDataValidatorDefinition`  
`struct FPackageDataValidatorDefinition : public FValidatorDefinition`  
_L498-504_
- reflection: `USTRUCT()`
- inherits: `FValidatorDefinition`
- L503 _public member_ `TArray<FString> ExcludedExtensions;` — `UPROPERTY()`

#### struct `FJsonValidatorDefinition`  
`struct FJsonValidatorDefinition : public FValidatorDefinition`  
_L507-516_
- reflection: `USTRUCT()`
- inherits: `FValidatorDefinition`
- L515 _public member_ `FString RegexLineExclusion;` — `UPROPERTY()`

#### struct `FPreflightValidatorDefinition`  
`struct FPreflightValidatorDefinition : public FValidatorDefinition`  
_L520-529_
- reflection: `USTRUCT()`
- inherits: `FValidatorDefinition`
- L528 _public member_ `int32 MaxPreflightAgeInHours = 12;` — `UPROPERTY()`

#### struct `FVirtualizationToolDefinition`  
`struct FVirtualizationToolDefinition : public FValidatorRunExecutableDefinition`  
_L533-548_
- reflection: `USTRUCT()`
- inherits: `FValidatorRunExecutableDefinition`
- L538 _public member_ `bool bIncludePackages;` — `UPROPERTY()`
- L541 _public member_ `bool bIncludeTextPackages;` — `UPROPERTY()`
- L544 _public member_ `FString BuildCommand;` — `UPROPERTY()`
- L547 _public member_ `FString BuildCommandArgs;` — `UPROPERTY()`

#### struct `FEditorCommandletValidatorDefinition`  
`struct FEditorCommandletValidatorDefinition : public FValidatorRunExecutableDefinition`  
_L551-569_
- reflection: `USTRUCT()`
- inherits: `FValidatorRunExecutableDefinition`
- L556 _public member_ `FString MainProject;` — `UPROPERTY()`
- L559 _public member_ `FString EditorRecordsFile;` — `UPROPERTY()`
- L562 _public member_ `TArray<FString> DisablePlugins;` — `UPROPERTY()`
- L565 _public member_ `TArray<FString> EnablePlugins;` — `UPROPERTY()`
- L568 _public member_ `bool bIgnoreUserEditorPrefs = false;` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Logic/Validators/ValidatorFactory.h` (Public)


#### class `FValidatorFactory`  
`class FValidatorFactory`  
_L9-31_
- L12 _public typedef_ `using FValidatorConstructor = TFunction<TSharedRef<FValidatorBase>( const FName&, const FSubmitToolParameters&, const TSharedRef<FSubmitToolServiceProvider>&, const FString&)>;`
- L18 _public prototype_ `static FValidatorFactory& Get();`
- L20 _public prototype_ `void Register(const FString& TypeName, FValidatorConstructor InCreator);`
- L22 _public prototype_ `TSharedPtr<FValidatorBase> Create( const FString& TypeName, const FName& Id, const FSubmitToolParameters& Params, const TSharedRef<FSubmitToolServiceProvider>& ServiceProvider, const FString& Definition) const;`
- L30 _private member_ `TMap<FString, FValidatorConstructor> Registry;`

#### struct `FValidatorRegistrar`  
`struct FValidatorRegistrar`  
_L33-39_
- L35 _public function_ `FValidatorRegistrar(const FString& TypeName, FValidatorFactory::FValidatorConstructor Creator)`

#### Free symbols / members of external scopes

- L41 _macro_ `#define REGISTER_VALIDATOR_TYPE(TypeNameConstant, ValidatorClass) \`
- L49 _macro_ `#define REGISTER_VALIDATOR_TYPE_ALIAS(TypeNameConstant, ValidatorClass, Alias) \`

### `Source/Developer/SubmitToolCore/Public/Models/CacheData.h` (Public)


#### struct `FValidationRecord`  
`struct FValidationRecord`  
_L10-19_
- reflection: `USTRUCT()`
- L15 _public member_ `FString ValidatorConfig = FString();` — `UPROPERTY()`
- L18 _public member_ `FDateTime LastValidationSuccess = FDateTime::MinValue();` — `UPROPERTY()`

#### struct `FValidationRecords`  
`struct FValidationRecords`  
_L22-28_
- reflection: `USTRUCT()`
- L27 _public member_ `TMap<FName , FValidationRecord> LastValidationDateTimes = TMap<FName, FValidationRecord>();` — `UPROPERTY()`

#### struct `FChangelistCacheData`  
`struct FChangelistCacheData`  
_L31-57_
- reflection: `USTRUCT()`
- L36 _public member_ `FDateTime LastShelfIsUpToDate = FDateTime::MinValue();` — `UPROPERTY()`
- L39 _public member_ `FDateTime LastAccessed = FDateTime::UtcNow();` — `UPROPERTY()`
- L42 _public member_ `TMap<FString , FValidationRecords> LastFileValidations = TMap<FString, FValidationRecords>();` — `UPROPERTY()`
- L45 _public member_ `TMap<FString , FString > IntegrationFields = TMap<FString, FString>();` — `UPROPERTY()`
- L48 _public function_ `const FDateTime GetLastValidationDate(const FString& InFilePath, const FName& InValidatorId, const FString& InValidatorConfig) const`

#### struct `FCacheFile`  
`struct FCacheFile`  
_L60-66_
- reflection: `USTRUCT()`
- L65 _public member_ `TMap<FString, FChangelistCacheData> CLCacheData = TMap<FString, FChangelistCacheData>();` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Models/HordeDeploymentData.h` (Public)


#### struct `FToolDeployment`  
`struct FToolDeployment`  
_L10-37_
- reflection: `USTRUCT()`
- L15 _public member_ `FString Id;` — `UPROPERTY()`
- L18 _public member_ `FString Version;` — `UPROPERTY()`
- L21 _public member_ `FString State;` — `UPROPERTY()`
- L24 _public member_ `int Progress;` — `UPROPERTY()`
- L27 _public member_ `FString StartedAt;` — `UPROPERTY()`
- L30 _public member_ `FString Duration;` — `UPROPERTY()`
- L33 _public member_ `FString RefName;` — `UPROPERTY()`
- L36 _public member_ `FString Locator;` — `UPROPERTY()`

#### struct `FDeploymentList`  
`struct FDeploymentList`  
_L40-47_
- reflection: `USTRUCT()`
- L45 _public member_ `TArray<FToolDeployment> Deployments;` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Models/IntegrationOptions.h` (Public)


#### class `FIntegrationOptionBase`  
`class FIntegrationOptionBase`  
_L8-21_
- L11 _public function_ `FIntegrationOptionBase(const FJiraIntegrationField& InFieldDefinition) : FieldDefinition(InFieldDefinition)`
- L13 _public function_ `virtual ~FIntegrationOptionBase()`
- L15 _public member_ `FJiraIntegrationField FieldDefinition;`
- L17 _public member_ `bool bInvalid = false;`
- L19 _public prototype_ `virtual bool GetJiraValue(FString& OutValue) = 0;`
- L20 _public prototype_ `virtual void SetValue(const FString& InValue) = 0;`

#### class `FIntegrationEmptyOption`  
`class FIntegrationEmptyOption : public FIntegrationOptionBase`  
_L24-38_
- inherits: `FIntegrationOptionBase`
- L27 _public function_ `FIntegrationEmptyOption(const FJiraIntegrationField& InFieldDefinition) : FIntegrationOptionBase(InFieldDefinition)`
- L30 _public function_ `virtual bool GetJiraValue(FString& OutValue) override`
- L35 _public function_ `virtual void SetValue(const FString& InValue)`

#### class `FIntegrationBoolOption`  
`class FIntegrationBoolOption : public FIntegrationOptionBase`  
_L40-78_
- inherits: `FIntegrationOptionBase`
- L43 _public function_ `FIntegrationBoolOption(const FJiraIntegrationField& InFieldDefinition, bool InDefaultValue = false) : FIntegrationOptionBase(InFieldDefinition), Value(InDefaultValue)`
- L47 _public member_ `bool Value = false;`
- L49 _public function_ `virtual bool GetJiraValue(FString& OutValue) override`
- L71 _public function_ `virtual void SetValue(const FString& InValue) override`

#### class `FIntegrationTextOption`  
`class FIntegrationTextOption : public FIntegrationOptionBase`  
_L80-100_
- inherits: `FIntegrationOptionBase`
- L83 _public function_ `FIntegrationTextOption(const FJiraIntegrationField& InFieldDefinition) : FIntegrationOptionBase(InFieldDefinition), Value(InFieldDefinition.Default)`
- L88 _public member_ `FString Value;`
- L90 _public function_ `virtual bool GetJiraValue(FString& OutValue) override`
- L96 _public function_ `virtual void SetValue(const FString& InValue) override`

#### class `FIntegrationComboOption`  
`class FIntegrationComboOption : public FIntegrationTextOption`  
_L102-113_
- inherits: `FIntegrationTextOption`
- L105 _public function_ `FIntegrationComboOption(const FJiraIntegrationField& InFieldDefinition) : FIntegrationTextOption(InFieldDefinition)`
- L112 _public member_ `TArray<TSharedPtr<FString>> ComboValues;`

### `Source/Developer/SubmitToolCore/Public/Models/JiraIssue.h` (Public)


#### struct `FJiraIssue`  
`struct FJiraIssue`  
_L10-45_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FJiraIssue() = default;`
- L15 _public function_ `FJiraIssue(const FString& InKey, const FString& InSummary, const FString& InLink, const FString& InDescription, const FString& InPriority, const FString& InStatus, const FString& InIssueType) : Key(InKey), Summary(InSummary), Link(InLink), Description(InDescription), Priority(InPriority), Status(InStatus), IssueType(InIssueType)`
- L26 _public member_ `FString Key;` — `UPROPERTY()`
- L29 _public member_ `FString Summary;` — `UPROPERTY()`
- L32 _public member_ `FString Link;` — `UPROPERTY()`
- L35 _public member_ `FString Description;` — `UPROPERTY()`
- L38 _public member_ `FString Priority;` — `UPROPERTY()`
- L41 _public member_ `FString Status;` — `UPROPERTY()`
- L44 _public member_ `FString IssueType;` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Models/JiraToken.h` (Public)


#### struct `FJiraToken`  
`struct FJiraToken`  
_L10-20_
- reflection: `USTRUCT()`
- L15 _public member_ `FString Access_Token;` — `UPROPERTY()`
- L17 _public member_ `int32 Expires_In = 0;` — `UPROPERTY()`
- L19 _public member_ `FString Refresh_Token;` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Models/LockdownData.h` (Public)


#### enum `ELockdownType`  
`enum class ELockdownType : int32`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `None = 0`
- L13 _public enumerator_ `Controlled`
- L14 _public enumerator_ `Hardcore`

#### struct `FCaseInsensitiveStringKeyFuncs`  
`struct FCaseInsensitiveStringKeyFuncs : DefaultKeyFuncs<FString, false>`  
_L17-28_
- inherits: `DefaultKeyFuncs<FString,false>`
- L19 _public function_ `static FORCEINLINE bool Matches(const FString& A, const FString& B)`
- L23 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& Key)`

#### struct `FSubmitToolLockdownData`  
`struct FSubmitToolLockdownData`  
_L30-62_
- L32 _public member_ `TSet<FString, FCaseInsensitiveStringKeyFuncs> GroupNames;`
- L33 _public member_ `TSet<FString, FCaseInsensitiveStringKeyFuncs> GroupMessages;`
- L34 _public member_ `ELockdownType LockdownType = ELockdownType::None;`
- L35 _public member_ `TMap<FString, TSet<FString, FCaseInsensitiveStringKeyFuncs>> RequiredTags;`
- L36 _public member_ `bool bIsAllowlisted = true;`
- L38 _public function_ `void Append(FSubmitToolLockdownData&& OtherLockdown)`

### `Source/Developer/SubmitToolCore/Public/Models/PreflightData.h` (Public)


#### enum `EPreflightOutcome`  
`enum class EPreflightOutcome : uint8`  
_L9-15_
- reflection: `UENUM()`
- L11 _public enumerator_ `Unspecified = 0`
- L12 _public enumerator_ `Failure`
- L13 _public enumerator_ `Warnings`
- L14 _public enumerator_ `Success`

#### enum `EPreflightState`  
`enum class EPreflightState : uint8`  
_L18-25_
- reflection: `UENUM()`
- L20 _public enumerator_ `Unspecified = 0`
- L21 _public enumerator_ `Ready`
- L22 _public enumerator_ `Running`
- L23 _public enumerator_ `Skipped`
- L24 _public enumerator_ `Completed`

#### struct `FPreflightResultData`  
`struct FPreflightResultData`  
_L38-63_
- reflection: `USTRUCT()`
- L43 _public member_ `EPreflightState State = EPreflightState::Unspecified;` — `UPROPERTY()`
- L45 _public member_ `EPreflightOutcome Outcome = EPreflightOutcome::Unspecified;` — `UPROPERTY()`
- L47 _public member_ `TArray<FString> Errors;` — `UPROPERTY()`
- L49 _public function_ `bool WasSuccessful() const`
- L54 _public function_ `bool operator==(const FPreflightResultData& other) const`
- L59 _public function_ `bool operator!=(const FPreflightResultData& other) const`

#### struct `FPFStep`  
`struct FPFStep`  
_L66-84_
- reflection: `USTRUCT()`
- L71 _public member_ `FString ID;` — `UPROPERTY()`
- L73 _public member_ `FString State;` — `UPROPERTY()`
- L75 _public member_ `FString Outcome;` — `UPROPERTY()`
- L77 _public member_ `FString Error;` — `UPROPERTY()`
- L79 _public member_ `FString RetryByUser;` — `UPROPERTY()`
- L82 _public prototype_ `bool operator==(const FPFStep& other) const = default;`
- L83 _public prototype_ `bool operator!=(const FPFStep& other) const = default;`

#### struct `FPFBatch`  
`struct FPFBatch`  
_L87-101_
- reflection: `USTRUCT()`
- L92 _public member_ `FString ID;` — `UPROPERTY()`
- L94 _public member_ `FString State;` — `UPROPERTY()`
- L96 _public member_ `TArray<FPFStep> Steps;` — `UPROPERTY()`
- L99 _public prototype_ `bool operator==(const FPFBatch& other) const = default;`
- L100 _public prototype_ `bool operator!=(const FPFBatch& other) const = default;`

#### struct `FPreflightData`  
`struct FPreflightData`  
_L104-177_
- reflection: `USTRUCT()`
- L109 _public member_ `FString ID;` — `UPROPERTY()`
- L111 _public member_ `FString Name;` — `UPROPERTY()`
- L113 _public member_ `FString TemplateId;` — `UPROPERTY()`
- L115 _public member_ `FDateTime CreateTime;` — `UPROPERTY()`
- L117 _public member_ `FDateTime UpdateTime;` — `UPROPERTY()`
- L119 _public member_ `TArray<FPFBatch> Batches;` — `UPROPERTY()`
- L121 _public member_ `FPreflightResultData CachedResults;`
- L123 _public function_ `void RecalculateCachedResults()`
- L175 _public prototype_ `bool operator==(const FPreflightData& other) const = default;`
- L176 _public prototype_ `bool operator!=(const FPreflightData& other) const = default;`

#### struct `FPreflightList`  
`struct FPreflightList`  
_L180-197_
- reflection: `USTRUCT()`
- L185 _public member_ `TArray<FPreflightData> PreflightList;` — `UPROPERTY()`
- L187 _public function_ `void Initialize()`
- L195 _public prototype_ `bool operator==(const FPreflightList& other) const = default;`
- L196 _public prototype_ `bool operator!=(const FPreflightList& other) const = default;`

#### Free symbols / members of external scopes

- L28 _function_ `template<typename PreflightEnum> PreflightEnum ParsePreflightEnum(const FString& String)`
- L159 _function_ `` (scope `FPreflightData::RecalculateCachedResults`)
- L199 _typedef_ `using FOnPreflightDataUpdated = TMulticastDelegate<void(const TUniquePtr<FPreflightList>&, const TMap<FString, FPreflightData>&)>;`

### `Source/Developer/SubmitToolCore/Public/Models/SCFile.h` (Public)


#### enum `ESCFileState`  
`enum ESCFileState : int64`  
_L10-17_
- reflection: `UENUM()`
- L12 _public enumerator_ `Edit`
- L13 _public enumerator_ `Add`
- L14 _public enumerator_ `Delete`
- L15 _public enumerator_ `Integrate`
- L16 _public enumerator_ `Unknown`

#### class `FSCFile`  
`class FSCFile final : public TSharedFromThis<class FSCFile, ESPMode::ThreadSafe>`  
_L19-47_
- inherits: `TSharedFromThis<classFSCFile,ESPMode::ThreadSafe>`
- L22 _public function_ `FSCFile(const FString& InFilename, const FString& InDepotPath, ESCFileState InState) : Filename(InFilename) , DepotPath(InDepotPath) , State(InState)`
- L30 _public function_ `~FSCFile()`
- L32 _public function_ `const FString& GetFilename() const`
- L33 _public function_ `const FString& GetDepotPath() const`
- L34 _public function_ `ESCFileState GetState() const`
- L35 _public function_ `void UpdateState(ESCFileState NewState)`
- L36 _public function_ `void UpdateFilename(const FString& NewFilename)`
- L38 _public function_ `bool IsAdded() const`
- L39 _public function_ `bool IsCheckedOut() const`
- L40 _public function_ `bool IsIntegrate() const`
- L41 _public function_ `bool IsDeleted() const`
- L44 _private member_ `FString Filename;`
- L45 _private member_ `FString DepotPath;`
- L46 _private member_ `ESCFileState State;`

#### Free symbols / members of external scopes

- L49 _typedef_ `using FSCFileRef = TSharedRef<FSCFile, ESPMode::ThreadSafe>;`

### `Source/Developer/SubmitToolCore/Public/Models/SubmitToolUserPrefs.h` (Public)


#### struct `FSubmitToolUserPrefs`  
`struct FSubmitToolUserPrefs`  
_L11-87_
- reflection: `USTRUCT()`
- L16 _public member_ `TMap<FString, FString> ValidatorOptions;` — `UPROPERTY()`
- L19 _public member_ `bool bCloseOnSubmit = true;` — `UPROPERTY()`
- L22 _public member_ `bool bOpenJiraOnSubmit = true;` — `UPROPERTY()`
- L25 _public member_ `bool bExpandFilesInCL = false;` — `UPROPERTY()`
- L28 _public member_ `bool bWindowMaximized = false;` — `UPROPERTY()`
- L31 _public member_ `bool bAutoUpdatePreflight = false;` — `UPROPERTY()`
- L34 _public member_ `bool bAutoCreateShelf = false;` — `UPROPERTY()`
- L37 _public member_ `bool bAutoStompShelf = false;` — `UPROPERTY()`
- L40 _public member_ `FVector2D WindowPosition = FVector2D();` — `UPROPERTY()`
- L43 _public member_ `FVector2D WindowSize = FVector2D();` — `UPROPERTY()`
- L46 _public member_ `float TagSectionSize = FLT_MAX;` — `UPROPERTY()`
- L49 _public member_ `float P4SectionSize = 34;` — `UPROPERTY()`
- L52 _public member_ `float ValidatorSectionSize = 22;` — `UPROPERTY()`
- L55 _public member_ `float LogSectionSize = 46;` — `UPROPERTY()`
- L58 _public member_ `TMap<FName, bool> UISectionExpandState = {};` — `UPROPERTY()`
- L62 _public member_ `bool bAutoUpdate = true;` — `UPROPERTY()`
- L65 _public member_ `bool bAppendAtForP4Users = true;` — `UPROPERTY()`
- L68 _public member_ `bool bAppendAtForP4Groups = true;` — `UPROPERTY()`
- L70 _public prototype_ `virtual ~FSubmitToolUserPrefs();`
- L72 _public function_ `static FSubmitToolUserPrefs* Get()`
- L82 _public prototype_ `static TUniquePtr<FSubmitToolUserPrefs> Initialize(const FString& InFilePath);`
- L85 _private member_ `static FString FilePath;`
- L86 _private member_ `static FSubmitToolUserPrefs* Instance;`

### `Source/Developer/SubmitToolCore/Public/Models/SwarmReview.h` (Public)


#### struct `FSwarmReviewVote`  
`struct FSwarmReviewVote`  
_L10-22_
- reflection: `USTRUCT()`
- L15 _public member_ `int32 Value;` — `UPROPERTY()`
- L18 _public member_ `int32 Version;` — `UPROPERTY()`
- L21 _public member_ `bool IsStale;` — `UPROPERTY()`

#### struct `FSwarmReviewParticipant`  
`struct FSwarmReviewParticipant`  
_L25-31_
- reflection: `USTRUCT()`
- L30 _public member_ `FSwarmReviewVote Vote;` — `UPROPERTY()`

#### struct `FSwarmReview`  
`struct FSwarmReview`  
_L34-49_
- reflection: `USTRUCT()`
- L39 _public member_ `int32 Id;` — `UPROPERTY()`
- L42 _public member_ `FString State;` — `UPROPERTY()`
- L45 _public member_ `FString Author;` — `UPROPERTY()`
- L48 _public member_ `TMap<FString, FSwarmReviewParticipant> Participants;` — `UPROPERTY()`

#### struct `FSwarmReviewCollection`  
`struct FSwarmReviewCollection`  
_L52-58_
- reflection: `USTRUCT()`
- L57 _public member_ `TArray<FSwarmReview> Reviews;` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Models/Tag.h` (Public)


#### enum `ETagState`  
`enum class ETagState : uint8`  
_L12-17_
- L14 _public enumerator_ `Unchecked = 0`
- L15 _public enumerator_ `Failed`
- L16 _public enumerator_ `Success`

#### class `FTag`  
`class FTag`  
_L19-98_
- L21 _public function_ `FTag(const FTagDefinition& def) : FTag(def, std::numeric_limits<size_t>::max())`
- L24 _public prototype_ `FTag(const FTagDefinition& def, size_t start);`
- L26 _public function_ `FTag(const FTag& InOther) : FTag(InOther.Definition, InOther.StartPos)`
- L36 _public function_ `FTag(FTag && InOther) : FTag(InOther.Definition, InOther.StartPos)`
- L46 _public prototype_ `FTag& operator=(const FTag& InOther) = delete;`
- L47 _public prototype_ `FTag& operator=(FTag&& InOther) = delete;`
- L49 _public prototype_ `FString GetFullTag() const;`
- L50 _public prototype_ `bool ParseTag(const FString& source);`
- L52 _public prototype_ `void SetValues(const FString& valuesText);`
- L53 _public prototype_ `FString GetValuesText() const;`
- L55 _public prototype_ `void SetValues(const TArray<FString>& InValues);`
- L56 _public prototype_ `void SetValues(TArray<FString>&& InValues );`
- L57 _public prototype_ `const TArray<FString> GetValues(bool bIncludeInactive = false) const;`
- L59 _public prototype_ `const FTagValidationConfig& GetCurrentValidationConfig(const TArray<FSCFileRef>& InDepotPaths) const;`
- L61 _public function_ `const ETagState GetTagState() const`
- L66 _public function_ `void SetTagState(ETagState InState) const`
- L71 _public function_ `bool IsEnabled() const`
- L76 _public member_ `FTagUpdated OnTagUpdated;`
- L78 _public member_ `bool bIsDirty = false;`
- L79 _public member_ `const FTagDefinition& Definition;`
- L80 _public member_ `size_t StartPos = std::numeric_limits<size_t>::max();`
- L81 _public member_ `size_t LastSize = std::numeric_limits<size_t>::max();`
- L83 _private function_ `void Reset()`
- L93 _private member_ `TArray<TCHAR const*> Delimiters;`
- L94 _private member_ `TArray<FString> SplittedDelims;`
- L95 _private member_ `TArray<FString> TagValues;`
- L96 _private member_ `FString TagKeyValue;`
- L97 _private member_ `mutable ETagState ValidationState;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FTagUpdated, const FTag&) enum class ETagState : uint8 { Unchecked = 0, Failed, Success };`

### `Source/Developer/SubmitToolCore/Public/Models/TagDefinition.h` (Public)


#### struct `FTagValidationConfig`  
`struct FTagValidationConfig`  
_L11-25_
- reflection: `USTRUCT()`
- L15 _public prototype_ `FTagValidationConfig() = default;`
- L18 _public member_ `FString RegexValidation = FString();` — `UPROPERTY()`
- L21 _public member_ `FString RegexErrorMessage = FString();` — `UPROPERTY()`
- L24 _public member_ `bool bIsMandatory = false;` — `UPROPERTY()`

#### struct `FTagValidationOverride`  
`struct FTagValidationOverride`  
_L28-37_
- reflection: `USTRUCT()`
- L33 _public member_ `FString RegexPath;` — `UPROPERTY()`
- L36 _public member_ `FTagValidationConfig ConfigOverride;` — `UPROPERTY()`

#### struct `FTagDefinition`  
`struct FTagDefinition`  
_L40-155_
- reflection: `USTRUCT()`
- L44 _public prototype_ `FTagDefinition() = default;`
- L46 _public function_ `inline const FString& GetTagId() const`
- L52 _public member_ `FString TagId;` — `UPROPERTY()`
- L58 _public member_ `FString RegexParseOverride;` — `UPROPERTY()`
- L64 _public member_ `FString TagLabel;` — `UPROPERTY()`
- L70 _public member_ `FString ToolTip = FString(TEXT("Ther` — `UPROPERTY()`
- L77 _public member_ `FString DocumentationUrl;` — `UPROPERTY()`
- L89 _public member_ `FString InputType;` — `UPROPERTY()`
- L100 _public member_ `FString InputSubType;` — `UPROPERTY()`
- L106 _public member_ `FString ValueDelimiter = TEXT(", "` — `UPROPERTY()`
- L112 _public member_ `int32 MinValues = 0;` — `UPROPERTY()`
- L118 _public member_ `int32 MaxValues = UINT8_MAX;` — `UPROPERTY()`
- L124 _public member_ `FTagValidationConfig Validation = FTagValidationConfig();` — `UPROPERTY()`
- L130 _public member_ `TArray<FTagValidationOverride> ValidationOverrides;` — `UPROPERTY()`
- L136 _public member_ `int32 OrdinalOverride = 0;` — `UPROPERTY()`
- L142 _public member_ `bool bIsDisabled = false;` — `UPROPERTY()`
- L148 _public member_ `TArray<FString> SelectValues;` — `UPROPERTY()`
- L154 _public member_ `TArray<FString> Filters;` — `UPROPERTY()`

### `Source/Developer/SubmitToolCore/Public/Parameters/SubmitToolParameters.h` (Public)


#### struct `FDocumentationLink`  
`struct FDocumentationLink`  
_L11-23_
- reflection: `USTRUCT()`
- L16 _public member_ `FString Text;` — `UPROPERTY()`
- L19 _public member_ `FString Tooltip;` — `UPROPERTY()`
- L22 _public member_ `FString Link;` — `UPROPERTY()`

#### struct `FGeneralParameters`  
`struct FGeneralParameters`  
_L26-87_
- reflection: `USTRUCT()`
- L31 _public member_ `FString NewChangelistMessage = TEXT("Sub` — `UPROPERTY()`
- L34 _public member_ `TArray<FString> ForbiddenDescriptions = { TEXT("Submit Tool generated changelist from default"), TEXT("<saved by perforce>") };` — `UPROPERTY()`
- L41 _public member_ `FString CacheFile = TEXT("$(l` — `UPROPERTY()`
- L44 _public member_ `uint8 InvalidateCacheHours = 36;` — `UPROPERTY()`
- L47 _public member_ `TArray<FDocumentationLink> HelpLinks;` — `UPROPERTY()`
- L50 _public member_ `uint8 EarlySubmitHour24 = 6;` — `UPROPERTY()`
- L53 _public member_ `uint8 LateSubmitHour24 = 16;` — `UPROPERTY()`
- L56 _public member_ `FString OutOfHoursSubmitMessage = TEXT("***` — `UPROPERTY()`
- L59 _public member_ `TArray<FString> GroupsToExclude;` — `UPROPERTY()`
- L62 _public member_ `TMap<FString, FString> PathOverrides;` — `UPROPERTY()`
- L65 _public member_ `TMap<FString, FString> PathOverridesInSourceBuild;` — `UPROPERTY()`
- L68 _public member_ `TArray<FString> AutomaticChangelistTags;` — `UPROPERTY()`
- L71 _public member_ `TArray<FString> SyncOnStartupPaths;` — `UPROPERTY()`
- L74 _public member_ `FString DescriptionGenProcess;` — `UPROPERTY()`
- L77 _public member_ `FString DescriptionGenTooltip;` — `UPROPERTY()`
- L80 _public member_ `FString DescriptionGenArgs;` — `UPROPERTY()`
- L83 _public member_ `FString DescriptionGenParsing;` — `UPROPERTY()`
- L86 _public member_ `FString DescriptionGenDocumentationUrl;` — `UPROPERTY()`

#### struct `FJiraParameters`  
`struct FJiraParameters`  
_L90-132_
- reflection: `USTRUCT()`
- L95 _public member_ `bool bDisableJira = false;` — `UPROPERTY()`
- L98 _public member_ `FString OAuthClientId;` — `UPROPERTY()`
- L101 _public member_ `FString OAuthClientSecret;` — `UPROPERTY()`
- L104 _public member_ `FString CloudID;` — `UPROPERTY()`
- L107 _public member_ `FString ServerAddress;` — `UPROPERTY()`
- L110 _public member_ `int64 ServiceDeskID;` — `UPROPERTY()`
- L113 _public member_ `int64 RequestFormID;` — `UPROPERTY()`
- L116 _public member_ `FString ServiceDeskToken;` — `UPROPERTY()`
- L119 _public member_ `FString SwarmUrlField;` — `UPROPERTY()`
- L122 _public member_ `FString RequestorField;` — `UPROPERTY()`
- L125 _public member_ `FString PreflightField;` — `UPROPERTY()`
- L128 _public member_ `FString JiraField;` — `UPROPERTY()`
- L131 _public member_ `FString StreamField;` — `UPROPERTY()`

#### struct `FPreflightAdditionalTask`  
`struct FPreflightAdditionalTask`  
_L135-144_
- reflection: `USTRUCT()`
- L140 _public member_ `FString RegexPath;` — `UPROPERTY()`
- L143 _public member_ `FString TaskId;` — `UPROPERTY()`

#### struct `FPreflightTemplateDefinition`  
`struct FPreflightTemplateDefinition`  
_L147-159_
- reflection: `USTRUCT()`
- L152 _public member_ `FString RegexPath;` — `UPROPERTY()`
- L155 _public member_ `FString Template;` — `UPROPERTY()`
- L158 _public member_ `TArray<FPreflightAdditionalTask> AdditionalTasks;` — `UPROPERTY()`

#### struct `FTelemetryParameters`  
`struct FTelemetryParameters`  
_L162-172_
- reflection: `USTRUCT()`
- L167 _public member_ `FString Url;` — `UPROPERTY()`
- L169 _public member_ `FString Instance;` — `UPROPERTY()`
- L171 _public member_ `FString RegexStreamAllowlist;` — `UPROPERTY()`

#### enum `EFieldType`  
`enum class EFieldType`  
_L175-185_
- reflection: `UENUM()`
- L177 _public enumerator_ `Bool = 0`
- L178 _public enumerator_ `Text = 1`
- L179 _public enumerator_ `MultiText = 2`
- L180 _public enumerator_ `Combo = 3`
- L181 _public enumerator_ `PerforceUser = 4`
- L183 _public enumerator_ `UILabel = 99`
- L184 _public enumerator_ `UISpace = 100`

#### enum `EJiraFieldType`  
`enum class EJiraFieldType`  
_L188-193_
- reflection: `UENUM()`
- L190 _public enumerator_ `Object = 0`
- L191 _public enumerator_ `Array = 1`
- L192 _public enumerator_ `String = 2`

#### struct `FJiraIntegrationField`  
`struct FJiraIntegrationField`  
_L196-224_
- reflection: `USTRUCT()`
- L201 _public member_ `FString Id;` — `UPROPERTY()`
- L203 _public member_ `FString Name;` — `UPROPERTY()`
- L205 _public member_ `FString LabelDisplay;` — `UPROPERTY()`
- L207 _public member_ `TArray<FString> JiraValues;` — `UPROPERTY()`
- L209 _public member_ `EFieldType Type;` — `UPROPERTY()`
- L211 _public member_ `EJiraFieldType JiraType;` — `UPROPERTY()`
- L213 _public member_ `FString Default;` — `UPROPERTY()`
- L215 _public member_ `TArray<FString> DependsOn;` — `UPROPERTY()`
- L217 _public member_ `FString DependsOnValue;` — `UPROPERTY()`
- L219 _public member_ `TArray<FString> ValidationGroups;` — `UPROPERTY()`
- L221 _public member_ `bool bRequiredValue;` — `UPROPERTY()`
- L223 _public member_ `FString Tooltip;` — `UPROPERTY()`

#### struct `FIntegrationParameters`  
`struct FIntegrationParameters`  
_L227-235_
- reflection: `USTRUCT()`
- L232 _public member_ `TArray<FJiraIntegrationField> Fields;` — `UPROPERTY()`
- L234 _public member_ `TArray<FString> OneOfValidationGroups;` — `UPROPERTY()`

#### struct `FCopyLogParameters`  
`struct FCopyLogParameters`  
_L238-244_
- reflection: `USTRUCT()`
- L243 _public member_ `TArray<FString> LogsToCollect;` — `UPROPERTY()`

#### struct `FP4LockdownParameters`  
`struct FP4LockdownParameters`  
_L247-259_
- reflection: `USTRUCT()`
- L252 _public member_ `TMap<FString, FString> ConfigPaths;` — `UPROPERTY()`
- L255 _public member_ `TArray<FString> AdditionalHardlockedPaths;` — `UPROPERTY()`
- L258 _public member_ `TMap<FString, FString> DynamicConfigPaths;` — `UPROPERTY()`

#### struct `FOAuthTokenParams`  
`struct FOAuthTokenParams`  
_L262-274_
- reflection: `USTRUCT()`
- L267 _public member_ `FString OAuthTokenTool;` — `UPROPERTY()`
- L270 _public member_ `FString OAuthArgs;` — `UPROPERTY()`
- L273 _public member_ `FString OAuthFile;` — `UPROPERTY()`

#### struct `FIncompatibleFilesGroup`  
`struct FIncompatibleFilesGroup`  
_L277-310_
- reflection: `USTRUCT()`
- L282 _public member_ `TArray<FString> FileGroups;` — `UPROPERTY()`
- L285 _public member_ `bool bIsError = false;` — `UPROPERTY()`
- L288 _public member_ `FString Title = TEXT("Fil` — `UPROPERTY()`
- L291 _public member_ `FString MessageFormat = TEXT("You` — `UPROPERTY()`
- L293 _public function_ `const FString GetMessage() const`

#### struct `FIncompatibleFilesParams`  
`struct FIncompatibleFilesParams`  
_L313-319_
- reflection: `USTRUCT()`
- L318 _public member_ `TArray<FIncompatibleFilesGroup> IncompatibleFileGroups;` — `UPROPERTY()`

#### struct `FHordeParameters`  
`struct FHordeParameters`  
_L323-343_
- reflection: `USTRUCT()`
- L328 _public member_ `FString HordeServerAddress;` — `UPROPERTY()`
- L330 _public member_ `FString StartPreflightURLFormat;` — `UPROPERTY()`
- L332 _public member_ `FString FindPreflightURLFormat;` — `UPROPERTY()`
- L334 _public member_ `FString FindSinglePreflightURLFormat;` — `UPROPERTY()`
- L336 _public member_ `float FetchPreflightEachSeconds = 180;` — `UPROPERTY()`
- L338 _public member_ `float FetchPreflightEachSecondsWhenInProgress = 90;` — `UPROPERTY()`
- L340 _public member_ `FString DefaultPreflightTemplate;` — `UPROPERTY()`
- L342 _public member_ `TArray<FPreflightTemplateDefinition> Definitions;` — `UPROPERTY()`

#### struct `FAutoUpdateParameters`  
`struct FAutoUpdateParameters`  
_L346-373_
- reflection: `USTRUCT()`
- L351 _public member_ `bool bIsAutoUpdateOn = false;` — `UPROPERTY()`
- L354 _public member_ `FString AutoUpdateScript;` — `UPROPERTY()`
- L357 _public member_ `FString LocalAutoUpdateScript;` — `UPROPERTY()`
- L360 _public member_ `FString AutoUpdateCommand;` — `UPROPERTY()`
- L363 _public member_ `FString AutoUpdateArgs;` — `UPROPERTY()`
- L366 _public member_ `FString DeployIdFilePath;` — `UPROPERTY()`
- L369 _public member_ `FString LocalDownloadZip;` — `UPROPERTY()`
- L372 _public member_ `FString LocalVersionFile;` — `UPROPERTY()`

#### struct `FSubmitToolParameters`  
`struct FSubmitToolParameters`  
_L375-390_
- L377 _public member_ `FGeneralParameters GeneralParameters;`
- L378 _public member_ `FTelemetryParameters Telemetry;`
- L379 _public member_ `TArray<FTagDefinition> AvailableTags;`
- L380 _public member_ `TMap<FString, FString> Validators;`
- L381 _public member_ `TMap<FString, FString> PresubmitOperations;`
- L382 _public member_ `FJiraParameters JiraParameters;`
- L383 _public member_ `FIntegrationParameters IntegrationParameters;`
- L384 _public member_ `FCopyLogParameters CopyLogParameters;`
- L385 _public member_ `FP4LockdownParameters P4LockdownParameters;`
- L386 _public member_ `FOAuthTokenParams OAuthParameters;`
- L387 _public member_ `FIncompatibleFilesParams IncompatibleFilesParams;`
- L388 _public member_ `FHordeParameters HordeParameters;`
- L389 _public member_ `FAutoUpdateParameters AutoUpdateParameters;`

### `Source/Developer/SubmitToolCore/Public/SubmitToolCoreUtils.h` (Public)


#### class `FSubmitToolCoreUtils`  
`class FSubmitToolCoreUtils`  
_L10-29_
- L13 _public prototype_ `static FString GetLocalAppDataPath();`
- L15 _public prototype_ `static void CopyDiagnosticFilesToClipboard(TConstArrayView<FString> Files);`
- L17 _public prototype_ `static bool IsFileInHierarchy(const FString& InWildcard, const FString& InPath);`
- L20 _public function_ `template <int32 BufferSize = 256, typename RangeType> static FString StringBuilderJoin(const RangeType& InRange, const FString&& Delimiter)`
- L28 _private member_ `static TMap<FString, TMap<bool, TSet<FString>>> HierarchyWildcardsCache;`
