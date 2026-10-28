# Developer / DesktopPlatform

- module root: `Source/Developer/DesktopPlatform`
- headers: 19; symbols: 494
- symbol kinds: class=15, delegate=1, enum=8, enumerator=32, function=28, macro=5, member=101, namespace=7, prototype=279, struct=13, typedef=5
- DynamicallyLoadedModuleNames: SlateFileDialogs, SlateFontDialog
- PrivateDependencyModuleNames: ApplicationCore, Core, Json
- PrivateIncludePathModuleNames: DerivedDataCache, LauncherPlatform, SlateFileDialogs, SlateFontDialog

### `Source/Developer/DesktopPlatform/Internal/LockFile.h` (Internal)


#### struct `FLockFile`  
`struct FLockFile`  
_L10-13_
- L12 _public prototype_ `static bool TryReadAndClear(const TCHAR* FileName, FString& OutContents);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DESKTOPPLATFORM_API`

### `Source/Developer/DesktopPlatform/Private/DesktopPlatformBase.h` (Private)


#### class `FDesktopPlatformBase`  
`class FDesktopPlatformBase : public IDesktopPlatform`  
_L16-114_
- inherits: `IDesktopPlatform`
- L19 _public prototype_ `FDesktopPlatformBase();`
- L22 _public prototype_ `virtual FString GetEngineDescription(const FString& Identifier) override;` — IDesktopPlatform Implementation
- L23 _public prototype_ `virtual FString GetCurrentEngineIdentifier() override;`
- L25 _public prototype_ `virtual void EnumerateLauncherEngineInstallations(TMap<FString, FString> &OutInstallations) override;`
- L26 _public prototype_ `virtual void EnumerateLauncherSampleInstallations(TArray<FString> &OutInstallations) override;`
- L27 _public prototype_ `virtual void EnumerateLauncherSampleProjects(TArray<FString> &OutFileNames) override;`
- L28 _public prototype_ `virtual bool GetEngineRootDirFromIdentifier(const FString &Identifier, FString &OutRootDir) override;`
- L29 _public prototype_ `virtual bool GetEngineIdentifierFromRootDir(const FString &RootDir, FString &OutIdentifier) override;`
- L31 _public prototype_ `virtual bool GetDefaultEngineIdentifier(FString &OutIdentifier) override;`
- L32 _public prototype_ `virtual bool GetDefaultEngineRootDir(FString &OutRootDir) override;`
- L33 _public prototype_ `virtual FString GetEngineSavedConfigDirectory(const FString& Identifier) override;`
- L35 _public prototype_ `virtual bool IsPreferredEngineIdentifier(const FString &Identifier, const FString &OtherIdentifier) override;`
- L37 _public prototype_ `virtual bool TryGetEngineVersion(const FString& RootDir, FEngineVersion& OutVersion) override;`
- L38 _public prototype_ `virtual bool IsStockEngineRelease(const FString &Identifier) override;`
- L39 _public prototype_ `virtual bool TryParseStockEngineVersion(const FString& Identifier, FEngineVersion& OutVersion) override;`
- L40 _public prototype_ `virtual bool IsSourceDistribution(const FString &RootDir) override;`
- L41 _public prototype_ `virtual bool IsPerforceBuild(const FString &RootDir) override;`
- L42 _public prototype_ `virtual bool IsValidRootDirectory(const FString &RootDir) override;`
- L44 _public prototype_ `virtual bool SetEngineIdentifierForProject(const FString &ProjectFileName, const FString &Identifier) override;`
- L45 _public prototype_ `virtual bool GetEngineIdentifierForProject(const FString &ProjectFileName, FString &OutIdentifier) override;`
- L47 _public prototype_ `virtual bool OpenProject(const FString& ProjectFileName) override;`
- L49 _public prototype_ `virtual bool CleanGameProject(const FString& ProjectDir, FString& OutFailPath, FFeedbackContext* Warn) override;`
- L50 _public prototype_ `virtual bool CompileGameProject(const FString& RootDir, const FString& ProjectFileName, FFeedbackContext* Warn, ECompilationResult::Type* OutResult) override;`
- L51 _public prototype_ `virtual bool GenerateProjectFiles(const FString& RootDir, const FString& ProjectFileName, FFeedbackContext* Warn, FString LogFilePath = FString()) override;`
- L52 _public prototype_ `virtual bool IsUnrealBuildToolAvailable() override;`
- L53 _public prototype_ `virtual bool InvokeUnrealBuildToolSync(const FString& InCmdLineParams, FOutputDevice &Ar, bool bSkipBuildUBT, int32& OutReturnCode, FString& OutProcOutput) override;`
- L54 _public prototype_ `virtual FProcHandle InvokeUnrealBuildToolAsync(const FString& InCmdLineParams, FOutputDevice &Ar, void*& OutReadPipe, void*& OutWritePipe, bool bSkipBuildUBT = false) override;`
- L55 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn) override final;`
- L56 _public prototype_ `virtual bool IsUnrealBuildToolRunning() override;`
- L58 _public prototype_ `virtual bool GetOidcAccessToken(const FString& RootDir, const FString& ProjectFileName, const FString& ProviderIdentifier, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) override;`
- L59 _public prototype_ `virtual bool GetOidcAccessTokenWithRemoteConfig(const FString& RootDir, const FString& RemoteHost, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) override;`
- L60 _public prototype_ `virtual bool GetOidcAccessToken(const FString& RootDir, const FString& ProjectFileName, const FString& ProviderIdentifier, bool bUnattended, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) override;`
- L61 _public prototype_ `virtual bool GetOidcAccessTokenWithRemoteConfig(const FString& RootDir, const FString& RemoteHost, bool bUnattended, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) override;`
- L62 _public prototype_ `virtual bool GetOidcTokenStatus(const FString& RootDir, const FString& ProjectFileName, const FString& ProviderIdentifier, FFeedbackContext* Warn, int& OutStatus) override;`
- L64 _public prototype_ `virtual bool GetHordeUrl(FString& OutHordeUrl, FString* OutHordeUrlConfigSource = nullptr) override;`
- L65 _public prototype_ `virtual void SetHordeUrl(const FString& HordeUrl) override;`
- L66 _public prototype_ `virtual bool GetHordeAccessToken(const FString& HordeUrl, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) override;`
- L67 _public prototype_ `virtual bool GetHordeAccessToken(const FString& HordeUrl, bool bUnattended, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) override;`
- L69 _public prototype_ `virtual const TArray<FTargetInfo>& GetTargetsForProject(const FString& ProjectFile) const override;`
- L70 _public prototype_ `virtual const TArray<FTargetInfo>& GetTargetsForCurrentProject() const override;`
- L72 _public prototype_ `virtual bool EnumerateProjectsKnownByEngine(const FString &Identifier, bool bIncludeNativeProjects, TArray<FString> &OutProjectFileNames) override;`
- L73 _public prototype_ `virtual FString GetDefaultProjectCreationPath() override;`
- L76 _private member_ `FString CurrentEngineIdentifier;`
- L77 _private member_ `FDateTime LauncherInstallationTimestamp;`
- L78 _private member_ `TMap<FString, FString> LauncherInstallationList;`
- L79 _private member_ `TMap<FString, FUProjectDictionary> CachedProjectDictionaries;`
- L80 _private member_ `mutable TMap<FString, TArray<FTargetInfo>> ProjectFileToTargets;`
- L81 _private member_ `bool bInitializedHordeServerUrl = false;`
- L82 _private member_ `FString HordeServerUrl;`
- L83 _private member_ `FString HordeServerUrlConfigSource;`
- L85 _private prototype_ `static FString ReadHordeUrlWithoutCache(FString& OutHordeUrlConfigSource);`
- L87 _private prototype_ `void ReadLauncherInstallationList();`
- L88 _private prototype_ `void CheckForLauncherEngineInstallation(const FString &AppId, const FString &Identifier, TMap<FString, FString> &OutInstallations);`
- L89 _private prototype_ `int32 ParseReleaseVersion(const FString &Version);`
- L91 _private prototype_ `TSharedPtr<FJsonObject> LoadProjectFile(const FString &FileName);`
- L92 _private prototype_ `bool SaveProjectFile(const FString &FileName, TSharedPtr<FJsonObject> Object);`
- L94 _private prototype_ `const FUProjectDictionary &GetCachedProjectDictionary(const FString& RootDir);`
- L96 _private prototype_ `void GetProjectBuildProducts(const FString& ProjectFileName, TArray<FString> &OutFileNames, TArray<FString> &OutDirectoryNames);`
- L97 _private prototype_ `bool BuildUnrealBuildTool(const FString& RootDir, FOutputDevice &Ar);`
- L99 _private prototype_ `bool InvokeOidcTokenToolSync(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutReturnCode, FString& OutProcOutput);`
- L100 _private prototype_ `FProcHandle InvokeOidcTokenToolAsync(const FString& InArguments, void*& OutReadPipe, void*& OutWritePipe);`
- L101 _private prototype_ `bool GetOidcAccessTokenInternal(const FString& RootDir, const FString& Arguments, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin);`
- L102 _private prototype_ `bool GetOidcAccessTokenInteractive(const FString& RootDir, const FString& Arguments, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, int32& OutReturnCode);`
- L104 _private prototype_ `static bool ReadTargetInfo(const FString& FileName, TArray<FTargetInfo>& Targets);`
- L106 _private prototype_ `FString GetUserDir(const FString& Identifier);`
- L109 _private prototype_ `FString GetLegacyEngineSavedConfigDirectory(const FString& Identifier);` — Pre-UE5 location of saved configs
- L112 _protected prototype_ `FString GetUnrealBuildToolProjectFileName(const FString& RootDir) const;`
- L113 _protected prototype_ `FString GetUnrealBuildToolExecutableFilename(const FString& RootDir) const;`

### `Source/Developer/DesktopPlatform/Private/DesktopPlatformPrivate.h` (Private)


#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDesktopPlatform, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDesktopPlatform, Log, All);`

### `Source/Developer/DesktopPlatform/Private/DesktopPlatformStub.h` (Private)


#### class `FDesktopPlatformStub`  
`class FDesktopPlatformStub : public FDesktopPlatformBase`  
_L9-34_
- inherits: `FDesktopPlatformBase`
- L13 _public function_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override` — IDesktopPlatform Implementation
- L14 _public function_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override`
- L15 _public function_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override`
- L16 _public function_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override`
- L17 _public function_ `virtual bool OpenFontDialog(const void* ParentWindowHandle, FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags) override`
- L19 _public function_ `virtual bool RegisterEngineInstallation(const FString &RootDir, FString &OutIdentifier) override`
- L20 _public function_ `virtual void EnumerateEngineInstallations(TMap<FString, FString> &OutInstallations) override`
- L22 _public function_ `virtual bool VerifyFileAssociations() override`
- L23 _public function_ `virtual bool UpdateFileAssociations() override`
- L26 _public function_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutExitCode) override`
- L27 _public function_ `virtual bool IsUnrealBuildToolRunning() override`
- L29 _public function_ `virtual FString GetOidcTokenExecutableFilename(const FString& RootDir) const override`
- L31 _public function_ `virtual FFeedbackContext* GetNativeFeedbackContext() override`
- L33 _public function_ `virtual FString GetUserTempPath() override`

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef FDesktopPlatformStub FDesktopPlatform;`

### `Source/Developer/DesktopPlatform/Private/Linux/DesktopPlatformLinux.h` (Private)


#### class `FDesktopPlatformLinux`  
`class FDesktopPlatformLinux : public FDesktopPlatformBase`  
_L8-44_
- inherits: `FDesktopPlatformBase`
- L12 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;` — IDesktopPlatform Implementation
- L13 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override;`
- L14 _public prototype_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;`
- L15 _public prototype_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override;`
- L16 _public prototype_ `virtual bool OpenFontDialog(const void* ParentWindowHandle, FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags) override;`
- L18 _public prototype_ `virtual bool RegisterEngineInstallation(const FString &RootDir, FString &OutIdentifier) override;`
- L19 _public prototype_ `virtual void EnumerateEngineInstallations(TMap<FString, FString> &OutInstallations) override;`
- L20 _public prototype_ `virtual void EnumerateLauncherEngineInstallations(TMap<FString, FString> &OutInstallations) override;`
- L22 _public prototype_ `virtual bool IsSourceDistribution(const FString &RootDir) override;`
- L24 _public prototype_ `virtual bool VerifyFileAssociations() override;`
- L25 _public prototype_ `virtual bool UpdateFileAssociations() override;`
- L27 _public prototype_ `virtual bool OpenProject(const FString &ProjectFileName) override;`
- L30 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutExitCode) override;`
- L32 _public prototype_ `virtual FFeedbackContext* GetNativeFeedbackContext() override;`
- L34 _public prototype_ `virtual FString GetUserTempPath() override;`
- L36 _public prototype_ `FDesktopPlatformLinux();`
- L37 _public prototype_ `virtual ~FDesktopPlatformLinux();`
- L40 _protected prototype_ `virtual FString GetOidcTokenExecutableFilename(const FString& RootDir) const override;`
- L43 _private prototype_ `bool FileDialogShared(bool bSave, const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex);`

#### Free symbols / members of external scopes

- L46 _typedef_ `typedef FDesktopPlatformLinux FDesktopPlatform;`

### `Source/Developer/DesktopPlatform/Private/Mac/DesktopPlatformMac.h` (Private)


#### class `FDesktopPlatformMac`  
`class FDesktopPlatformMac : public FDesktopPlatformBase`  
_L7-35_
- inherits: `FDesktopPlatformBase`
- L11 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;` — IDesktopPlatform Implementation
- L12 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override;`
- L13 _public prototype_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;`
- L14 _public prototype_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override;`
- L15 _public prototype_ `virtual bool OpenFontDialog(const void* ParentWindowHandle, FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags) override;`
- L17 _public prototype_ `virtual bool RegisterEngineInstallation(const FString &RootDir, FString &OutIdentifier) override;`
- L18 _public prototype_ `virtual void EnumerateEngineInstallations(TMap<FString, FString> &OutInstallations) override;`
- L20 _public prototype_ `virtual bool VerifyFileAssociations() override;`
- L21 _public prototype_ `virtual bool UpdateFileAssociations() override;`
- L24 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutExitCode) override;`
- L26 _public prototype_ `virtual FFeedbackContext* GetNativeFeedbackContext() override;`
- L28 _public prototype_ `virtual FString GetUserTempPath() override;`
- L31 _protected prototype_ `virtual FString GetOidcTokenExecutableFilename(const FString& RootDir) const override;`
- L34 _private prototype_ `bool FileDialogShared(bool bSave, const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex);`

#### Free symbols / members of external scopes

- L37 _typedef_ `typedef FDesktopPlatformMac FDesktopPlatform;`

### `Source/Developer/DesktopPlatform/Private/Mac/MacNativeFeedbackContext.h` (Private)


#### class `FMacNativeFeedbackContext`  
`class FMacNativeFeedbackContext : public FFeedbackContext`  
_L36-72_
- inherits: `FFeedbackContext`
- desc: Feedback context implementation for Mac.
- L40 _public prototype_ `FMacNativeFeedbackContext();` — Constructor.
- L41 _public prototype_ `virtual ~FMacNativeFeedbackContext();`
- L43 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;`
- L44 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time) override;`
- L45 _public prototype_ `virtual void SerializeRecord(const UE::FLogRecord& Record) override;`
- L47 _public prototype_ `virtual bool YesNof(const FText& Text) override;`
- L49 _public prototype_ `virtual bool ReceivedUserCancel() override;`
- L51 _public prototype_ `virtual void StartSlowTask( const FText& Task, bool bShowCancelButton=false ) override;`
- L52 _public prototype_ `virtual void FinalizeSlowTask( ) override;`
- L53 _public prototype_ `virtual void ProgressReported( const float TotalProgressInterp, FText DisplayMessage ) override;`
- L55 _public prototype_ `FContextSupplier* GetContext() const override;`
- L56 _public prototype_ `void SetContext(FContextSupplier* InContext) override;`
- L59 _private prototype_ `void SerializeToWindow(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time);`
- L61 _private prototype_ `void SetDefaultTextColor();`
- L65 _private member_ `FCriticalSection CriticalSection;` — Critical section for Serialize()
- L66 _private member_ `FMacNativeFeedbackContextWindowController* WindowController;`
- L67 _private member_ `NSDictionary* TextViewTextColor;`
- L68 _private member_ `FContextSupplier* Context;`
- L69 _private member_ `uint64 OutstandingTasks;`
- L70 _private member_ `int32 SlowTaskCount;`
- L71 _private member_ `bool bShowingConsoleForSlowTask;`

### `Source/Developer/DesktopPlatform/Private/Null/DesktopPlatformNull.h` (Private)


#### class `FDesktopPlatformNull`  
`class FDesktopPlatformNull : public FDesktopPlatformBase`  
_L8-43_
- inherits: `FDesktopPlatformBase`
- L12 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;` — IDesktopPlatform Implementation
- L13 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override;`
- L14 _public prototype_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;`
- L15 _public prototype_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override;`
- L16 _public prototype_ `virtual bool OpenFontDialog(const void* ParentWindowHandle, FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags) override;`
- L18 _public prototype_ `virtual bool RegisterEngineInstallation(const FString &RootDir, FString &OutIdentifier) override;`
- L19 _public prototype_ `virtual void EnumerateEngineInstallations(TMap<FString, FString> &OutInstallations) override;`
- L21 _public prototype_ `virtual bool IsSourceDistribution(const FString &RootDir) override;`
- L23 _public prototype_ `virtual bool VerifyFileAssociations() override;`
- L24 _public prototype_ `virtual bool UpdateFileAssociations() override;`
- L26 _public prototype_ `virtual bool OpenProject(const FString &ProjectFileName) override;`
- L29 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutExitCode) override;`
- L31 _public prototype_ `virtual FFeedbackContext* GetNativeFeedbackContext() override;`
- L33 _public prototype_ `virtual FString GetUserTempPath() override;`
- L35 _public prototype_ `FDesktopPlatformNull();`
- L36 _public prototype_ `virtual ~FDesktopPlatformNull();`
- L39 _protected prototype_ `virtual FString GetOidcTokenExecutableFilename(const FString& RootDir) const override;`
- L42 _private prototype_ `bool FileDialogShared(bool bSave, const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex);`

### `Source/Developer/DesktopPlatform/Private/Windows/DesktopPlatformWindows.h` (Private)


#### class `FDesktopPlatformWindows`  
`class FDesktopPlatformWindows : public FDesktopPlatformBase`  
_L11-45_
- inherits: `FDesktopPlatformBase`
- L15 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;` — IDesktopPlatform Implementation
- L16 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override;`
- L17 _public prototype_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;`
- L18 _public prototype_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override;`
- L19 _public prototype_ `virtual bool OpenFontDialog(const void* ParentWindowHandle, FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags) override;`
- L21 _public prototype_ `virtual bool RegisterEngineInstallation(const FString &RootDir, FString &OutIdentifier) override;`
- L22 _public prototype_ `virtual void EnumerateEngineInstallations(TMap<FString, FString> &OutInstallations) override;`
- L24 _public prototype_ `virtual bool IsSourceDistribution(const FString &RootDir) override;`
- L26 _public prototype_ `virtual bool VerifyFileAssociations() override;`
- L27 _public prototype_ `virtual bool UpdateFileAssociations() override;`
- L29 _public prototype_ `virtual bool OpenProject(const FString &ProjectFileName) override;`
- L32 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutExitCode) override;`
- L34 _public prototype_ `virtual FFeedbackContext* GetNativeFeedbackContext() override;`
- L36 _public prototype_ `virtual FString GetUserTempPath() override;`
- L39 _protected prototype_ `virtual FString GetOidcTokenExecutableFilename(const FString& RootDir) const override;`
- L42 _private prototype_ `bool FileDialogShared(bool bSave, const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex);`
- L43 _private prototype_ `void GetRequiredRegistrySettings(TIndirectArray<FRegistryRootedKey> &RootedKeys);`
- L44 _private prototype_ `int32 GetShellIntegrationVersion(const FString &FileName);`

#### Free symbols / members of external scopes

- L47 _typedef_ `typedef FDesktopPlatformWindows FDesktopPlatform;`

### `Source/Developer/DesktopPlatform/Private/Windows/WindowsNativeFeedbackContext.h` (Private)


#### class `FWindowsNativeFeedbackContext`  
`class FWindowsNativeFeedbackContext : public FFeedbackContext`  
_L14-66_
- inherits: `FFeedbackContext`
- desc: Feedback context implementation for windows.
- L18 _public prototype_ `FWindowsNativeFeedbackContext();` — Constructor.
- L19 _public prototype_ `virtual ~FWindowsNativeFeedbackContext();`
- L21 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;`
- L22 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time) override;`
- L23 _public prototype_ `virtual void SerializeRecord(const UE::FLogRecord& Record) override;`
- L25 _public prototype_ `virtual bool ReceivedUserCancel() override;`
- L26 _public prototype_ `virtual void StartSlowTask( const FText& Task, bool bShouldShowCancelButton=false ) override;`
- L27 _public prototype_ `virtual void FinalizeSlowTask( ) override;`
- L28 _public prototype_ `virtual void ProgressReported( const float TotalProgressInterp, FText DisplayMessage ) override;`
- L30 _public prototype_ `FContextSupplier* GetContext() const;`
- L31 _public prototype_ `void SetContext( FContextSupplier* InSupplier );`
- L44 _private member_ `static const uint16 StatusCtlId = 200;`
- L45 _private member_ `static const uint16 ProgressCtlId = 201;`
- L46 _private member_ `static const uint16 ShowLogCtlId = 202;`
- L47 _private member_ `static const uint16 LogOutputCtlId = 203;`
- L49 _private member_ `FContextSupplier* Context;`
- L50 _private member_ `HANDLE hThread;`
- L51 _private member_ `HANDLE hCloseEvent;`
- L52 _private member_ `HANDLE hUpdateEvent;`
- L53 _private member_ `FCriticalSection CriticalSection;`
- L54 _private member_ `FString Status;`
- L55 _private member_ `float Progress;`
- L56 _private member_ `FString LogOutput;`
- L57 _private member_ `bool bReceivedUserCancel;`
- L58 _private member_ `bool bShowCancelButton;`
- L60 _private prototype_ `void CreateSlowTaskWindow(const FText &InStatus, bool bInShowCancelButton);`
- L61 _private prototype_ `void DestroySlowTaskWindow();`
- L63 _private prototype_ `static DWORD WINAPI SlowTaskThreadProc(void *Params);`
- L64 _private prototype_ `static LRESULT CALLBACK SlowTaskWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);`
- L65 _private prototype_ `static void LayoutControls(HWND hWnd, const FWindowParams* Params);`

#### struct `FWindowsNativeFeedbackContext::FWindowParams`  
`struct FWindowParams`  
_L34-42_
- L36 _public member_ `FWindowsNativeFeedbackContext* Context;`
- L37 _public member_ `int32 ScaleX;`
- L38 _public member_ `int32 ScaleY;`
- L39 _public member_ `int32 StandardW;`
- L40 _public member_ `int32 StandardH;`
- L41 _public member_ `bool bLogVisible;`

### `Source/Developer/DesktopPlatform/Private/Windows/WindowsRegistry.h` (Private)


#### struct `FRegistryValue`  
`struct FRegistryValue`  
_L12-25_
- L14 _public member_ `uint32 Type;`
- L15 _public member_ `TArray<uint8> Data;`
- L17 _public prototype_ `FRegistryValue();`
- L19 _public prototype_ `void Set(const FString &NewValue);`
- L20 _public prototype_ `void Set(uint32 NewValue);`
- L22 _public prototype_ `bool Read(HKEY hKey, const FString &Name);`
- L23 _public prototype_ `bool Write(HKEY hKey, const FString &Name) const;`
- L24 _public prototype_ `bool IsUpToDate(HKEY hKey, const FString &Name) const;`

#### struct `FRegistryKey`  
`struct FRegistryKey : FNoncopyable`  
_L27-49_
- inherits: `FNoncopyable`
- L29 _public member_ `TMap<FString, FRegistryKey*> Keys;`
- L30 _public member_ `TMap<FString, FRegistryValue*> Values;`
- L32 _public prototype_ `FRegistryKey();`
- L33 _public prototype_ `~FRegistryKey();`
- L35 _public prototype_ `FRegistryKey *FindOrAddKey(const FString &Name);`
- L36 _public prototype_ `FRegistryValue *FindOrAddValue(const FString &Name);`
- L38 _public prototype_ `void SetValue(const FString &Name, const FString &Value);`
- L39 _public prototype_ `void SetValue(const FString &Name, uint32 Value);`
- L41 _public prototype_ `bool Read(HKEY hKey);`
- L42 _public prototype_ `bool Read(HKEY hKey, const FString &Path);`
- L44 _public prototype_ `bool Write(HKEY hKey, bool bRemoveDifferences) const;`
- L45 _public prototype_ `bool Write(HKEY hKey, const FString &Path, bool bRemoveDifferences) const;`
- L47 _public prototype_ `bool IsUpToDate(HKEY hKey, bool bRemoveDifferences) const;`
- L48 _public prototype_ `bool IsUpToDate(HKEY hKey, const FString &Path, bool bRemoveDifferences) const;`

#### struct `FRegistryRootedKey`  
`struct FRegistryRootedKey`  
_L51-64_
- L53 _public member_ `HKEY hRootKey;`
- L54 _public member_ `FString Path;`
- L55 _public member_ `TUniquePtr<FRegistryKey> Key;`
- L57 _public prototype_ `FRegistryRootedKey(HKEY hInKeyRoot, const FString &InPath);`
- L59 _public prototype_ `bool Exists() const;`
- L61 _public prototype_ `bool Read();`
- L62 _public prototype_ `bool Write(bool bRemoveDifferences) const;`
- L63 _public prototype_ `bool IsUpToDate(bool bRemoveDifferences) const;`

#### Free symbols / members of external scopes

- L66 _prototype_ `bool EnumerateRegistryKeys(HKEY hKey, TArray<FString> &OutNames);`
- L67 _prototype_ `bool EnumerateRegistryValues(HKEY hKey, TArray<FString> &OutNames);`

### `Source/Developer/DesktopPlatform/Public/DesktopPlatformModule.h` (Public)


#### class `FDesktopPlatformModule`  
`class FDesktopPlatformModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
- L18 _public function_ `static IDesktopPlatform* Get()`
- L24 _public function_ `static IDesktopPlatform* TryGet()`
- L34 _private function_ `virtual IDesktopPlatform* GetSingleton() const`
- L36 _private member_ `IDesktopPlatform* DesktopPlatform;`

### `Source/Developer/DesktopPlatform/Public/IDesktopPlatform.h` (Public)


#### enum `EFileDialogFlags::Type`  
`enum Type`  
_L15-19_
- L17 _public enumerator_ `None = 0x00` — No flags
- L18 _public enumerator_ `Multiple = 0x01` — Allow multiple file selections

#### enum `EFontImportFlags`  
`enum class EFontImportFlags`  
_L22-35_
- L24 _public enumerator_ `None = 0x0` — No flags
- L25 _public enumerator_ `EnableAntialiasing = 0x1` — Whether the font should be antialiased or not.  Usually you should leave this enabled.
- L26 _public enumerator_ `EnableBold = 0x2` — Whether the font should be generated in bold or not
- L27 _public enumerator_ `EnableItalic = 0x4` — Whether the font should be generated in italics or not
- L28 _public enumerator_ `EnableUnderline = 0x8` — Whether the font should be generated with an underline or not
- L29 _public enumerator_ `AlphaOnly = 0x10` — Forces PF_G8 and only maintains Alpha value and discards color
- L30 _public enumerator_ `CreatePrintableOnly = 0x20` — Skips generation of glyphs for any characters that are not considered 'printable'
- L31 _public enumerator_ `IncludeASCIIRange = 0x40` — When specifying a range of characters and this is enabled, forces ASCII characters (0 thru 255) to be included as well
- L32 _public enumerator_ `EnableDropShadow = 0x80` — Enables a very simple, 1-pixel, black colored drop shadow for the generated font
- L33 _public enumerator_ `EnableLegacyMode = 0x100` — Enables legacy font import mode.  This results in lower quality antialiasing and larger glyph bounds, but may be useful when debugging problems
- L34 _public enumerator_ `UseDistanceFieldAlpha = 0x200` — Alpha channel of the font textures will store a distance field instead of a color mask

#### enum `EDesktopLoginInteractionLevel`  
`enum class EDesktopLoginInteractionLevel : uint8`  
_L39-44_
- L41 _public enumerator_ `None` — No user interaction permitted
- L42 _public enumerator_ `TimeLimited` — Allow user interaction within a limited window of time (eg: 30 seconds), but don't wait indefinitely for interaction
- L43 _public enumerator_ `Interactive` — Allow user interaction with an indefinite wait if necessary

#### class `FScopedSystemModalMode`  
`class FScopedSystemModalMode`  
_L50-66_
- desc: When constructed leaves system wide modal mode (all windows disabled except for the OS modal window) When destructed leaves this mode
- L53 _public function_ `FScopedSystemModalMode()`
- L60 _public function_ `~FScopedSystemModalMode()`

#### struct `FTargetInfo`  
`struct FTargetInfo`  
_L71-77_
- desc: Information about a target supported by a project
- L73 _public member_ `FString Name;`
- L74 _public member_ `FString Path;`
- L75 _public member_ `EBuildTargetType Type;`
- L76 _public member_ `TOptional<bool> DefaultTarget;`

#### class `IDesktopPlatform`  
`class IDesktopPlatform`  
_L82-592_
- desc: Interface for functionality supported by desktop platforms
- L86 _public prototype_ `virtual ~IDesktopPlatform() = default;` — Virtual destructor
- L100 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) = 0;` — Opens the "open file" dialog for the platform. @param ParentWindowHandle		The native handle to the parent window for this dialog. @param DialogTitle				The text for the title of the dialog window. @param DefaultPath				The path where the file dialog will open initially. @param DefaultFile				The file that the dialog will select initially. @param FileTypes					The type filters to show in the dialog. This string should be a "|" delimited list of (Description|Extensionlist) pairs. Extensionlists are ";" delimited. @param Flags						Details about the dialog. See EFileDialogFlags. @param OutFilenames				The filenames that were selected in the dialog. @return true if files were successfully selected.
- L115 _public prototype_ `virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) = 0;` — Opens the "open file" dialog for the platform. @param ParentWindowHandle		The native handle to the parent window for this dialog. @param DialogTitle				The text for the title of the dialog window. @param DefaultPath				The path where the file dialog will open initially. @param DefaultFile				The file that the dialog will select initially. @param FileTypes					The type filters to show in the dialog. This string should be a "|" delimited list of (Description|Extensionlist) pairs. Extensionlists are ";" delimited. @param Flags						Details about the dialog. See EFileDialogFlags. @param OutFilenames				The filenames that were selected in the dialog. @param OutFilterIndex			The type that was selected in the dialog. @return true if files were successfully selected.
- L129 _public prototype_ `virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) = 0;` — Opens the "save file" dialog for the platform. @param ParentWindowHandle		The native handle to the parent window for this dialog. @param DialogTitle				The text for the title of the dialog window. @param DefaultPath				The path where the file dialog will open initially. @param DefaultFile				The file that the dialog will select initially. @param FileTypes					The type filters to show in the dialog. This string should be a "|" delimited list of (Description|Extensionlist) pairs. Extensionlists are ";" delimited. @param Flags						Details about the dialog. See EFileDialogFlags. @param OutFilenames				The filenames that were selected in the dialog. @return true if files were successfully selected.
- L140 _public prototype_ `virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) = 0;` — Opens the "choose folder" dialog for the platform @param ParentWindowHandle		The native handle to the parent window for this dialog. @param DialogTitle				The text for the title of the dialog window. @param DefaultPath				The path where the file dialog will open initially. @param OutFolderName				The foldername that was selected in the dialog. @return true if folder choice was successfully selected.
- L151 _public prototype_ `virtual bool OpenFontDialog(const void* ParentWindowHandle, FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags) = 0;` — Opens the "choose font" dialog for the platform @param ParentWindowHandle		The native handle to the parent window for this dialog. @param OutFontName				The name of the font. @param OutHeight					The height of the font. @param OutFlags					Any special flags the font has been tagged with. @return true if font choice was successfully selected.
- L158 _public prototype_ `virtual FString GetEngineDescription(const FString& Identifier) = 0;` — Returns a description for the engine with the given identifier. @return	Description for the engine identifier. Empty string if it's unknown.
- L165 _public prototype_ `virtual FString GetCurrentEngineIdentifier() = 0;` — Gets the identifier for the currently executing engine installation. @return	Identifier for the current engine installation. Empty string if it isn't registered.
- L174 _public prototype_ `virtual bool RegisterEngineInstallation(const FString& RootDir, FString& OutIdentifier) = 0;` — Registers a directory as containing an engine installation. @param	RootDir				Root directory for the engine installation. @param	OutIdentifier		Identifier which is assigned to the engine. @return true if the directory was added. OutIdentifier will be set to the assigned identifier.
- L182 _public prototype_ `virtual void EnumerateEngineInstallations(TMap<FString, FString>& OutInstallations) = 0;` — Enumerates all the registered engine installations. @param	OutInstallations	Map of identifier/root-directory pairs for all known installations. Identifiers are typically version strings for canonical UE releases or GUID strings for GitHub releases.
- L189 _public prototype_ `virtual void EnumerateLauncherEngineInstallations(TMap<FString, FString>& OutInstallations) = 0;` — Enumerates all the registered binary engine installations. @param	OutInstallations	Map of identifier/root-directory pairs for all known binary installations.
- L196 _public prototype_ `virtual void EnumerateLauncherSampleInstallations(TArray<FString>& OutInstallations) = 0;` — Enumerates all the samples installed by the launcher. @param	OutInstallations	Array of sample installation paths.
- L203 _public prototype_ `virtual void EnumerateLauncherSampleProjects(TArray<FString>& OutFileNames) = 0;` — Enumerates all the sample projects installed by the launcher. @param	OutFileNames		Array of sample project filenames.
- L211 _public prototype_ `virtual bool GetEngineRootDirFromIdentifier(const FString& Identifier, FString& OutRootDir) = 0;` — Returns the root directory for the engine with the given identifier. @param	Identifier			Identifier used to refer to this installation. @param	OutRootDir			Root directory for the engine.
- L219 _public prototype_ `virtual bool GetEngineIdentifierFromRootDir(const FString& RootDir, FString& OutIdentifier) = 0;` — Returns the identifier for the engine with the given root directory. @param	RootDir				Root directory for the engine. @param	OutIdentifier		Identifier used to refer to this installation.
- L227 _public prototype_ `virtual bool GetDefaultEngineIdentifier(FString& OutIdentifier) = 0;` — Gets the identifier for the default engine. This will be the newest installed engine. @param	OutIdentifier		String to hold to the default engine's identifier @return	true if OutIdentifier is valid.
- L236 _public prototype_ `virtual bool IsPreferredEngineIdentifier(const FString& Identifier, const FString& OtherIdentifier) = 0;` — Compares two identifiers and checks whether the first is preferred to the second. @param	Identifier			First identifier @param	OtherIdentifier		Second identifier @return	true if Identifier is preferred over OtherIdentifier.
- L244 _public prototype_ `virtual bool GetDefaultEngineRootDir(FString& OutRootDir) = 0;` — Gets the root directory for the default engine installation. @param	OutRootDir			String to hold to the default engine's root directory. @return	true if OutRootDir is valid.
- L252 _public prototype_ `virtual FString GetEngineSavedConfigDirectory(const FString& Identifier) = 0;` — Gets the root directory for the engine's saved config files @param	Identifier			Identifier for the engine @return	The absoluate path to the engines Saved/Config directory
- L263 _public prototype_ `virtual bool TryGetEngineVersion(const FString& RootDir, FEngineVersion& OutVersion) = 0;` — Attempt to get the engine version from the supplied engine root directory. Tries to read the contents of Engine/Build/Build.version, but scrapes information from the Engine/Source/Launch/Resources/Version.h if it fails. @param	RootDir				Root directory for the engine to check @param	OutVersion			Engine version obtained from identifier @return	true if the engine version was successfully obtained
- L271 _public prototype_ `virtual bool IsStockEngineRelease(const FString& Identifier) = 0;` — Checks if the given engine identifier is for an stock engine release. @param	Identifier			Engine identifier to check @return	true if the identifier is for a binary engine release
- L280 _public prototype_ `virtual bool TryParseStockEngineVersion(const FString& Identifier, FEngineVersion& OutVersion) = 0;` — Attempt to get the engine version from the supplied identifier @param	Identifier			Engine identifier to check @param	OutVersion			Engine version obtained from identifier @return	true if the engine version was successfully obtained
- L287 _public prototype_ `virtual bool IsSourceDistribution(const FString& RootDir) = 0;` — Tests whether an engine installation is a source distribution. @return	true if the engine contains source.
- L294 _public prototype_ `virtual bool IsPerforceBuild(const FString& RootDir) = 0;` — Tests whether an engine installation is a perforce build. @return	true if the engine is a perforce build.
- L301 _public prototype_ `virtual bool IsValidRootDirectory(const FString& RootDir) = 0;` — Tests whether a root directory is a valid Unreal Engine installation @return	true if the engine is a valid installation
- L308 _public prototype_ `virtual bool VerifyFileAssociations() = 0;` — Checks that the current file associations are correct. @return	true if file associations are up to date.
- L315 _public prototype_ `virtual bool UpdateFileAssociations() = 0;` — Updates file associations. @return	true if file associations were successfully updated.
- L324 _public prototype_ `virtual bool SetEngineIdentifierForProject(const FString& ProjectFileName, const FString& Identifier) = 0;` — Sets the engine association for a project. @param ProjectFileName		Filename of the project to update @param Identifier			Identifier of the engine to associate it with @return true if the project was successfully updated
- L333 _public prototype_ `virtual bool GetEngineIdentifierForProject(const FString& ProjectFileName, FString& OutIdentifier) = 0;` — Gets the engine association for a project. @param ProjectFileName		Filename of the project to update @param OutIdentifier			Identifier of the engine to associate it with @return true if OutIdentifier is set to the project's engine association
- L341 _public prototype_ `virtual bool OpenProject(const FString& ProjectFileName) = 0;` — Opens the given project with the appropriate editor. Tries to use the shell association. @param ProjectFileName		Filename of the project to update @return true if the project was opened successfully.
- L351 _public prototype_ `virtual bool CleanGameProject(const FString& ProjectDir, FString& OutFailPath, FFeedbackContext* Warn) = 0;` — Cleans a game project. Removes the intermediate folder and binary build products. @param ProjectDir			Directory of the project to clean. @param OutFailPath			The path of the first file or directory that failed to delete, if any. @param Warn					Feedback context to use for progress updates. @return						true if the project was cleaned successfully, false if any file or directory could not be deleted.
- L362 _public prototype_ `virtual bool CompileGameProject(const FString& RootDir, const FString& ProjectFileName, FFeedbackContext* Warn, ECompilationResult::Type* OutResult = nullptr) = 0;` — Compiles a game project. @param RootDir				Engine root directory for the project to use. @param ProjectFileName		Filename of the project to update @param Warn					Feedback context to use for progress updates @param OutResult				The compilation result. May be null. @return true if project files were generated successfully.
- L372 _public prototype_ `virtual bool GenerateProjectFiles(const FString& RootDir, const FString& ProjectFileName, FFeedbackContext* Warn, FString LogFilePath = FString()) = 0;` — Generates project files for the given project. @param RootDir				Engine root directory for the project to use. @param ProjectFileName		Filename of the project to update @param Warn					Feedback context to use for progress updates @return true if project files were generated successfully.
- L379 _public prototype_ `virtual bool IsUnrealBuildToolAvailable() = 0;` — Determines whether UnrealBuildTool is available @return true if UnrealBuildTool is available
- L386 _public prototype_ `virtual bool InvokeUnrealBuildToolSync(const FString& InCmdLineParams, FOutputDevice& Ar, bool bSkipBuildUBT, int32& OutReturnCode, FString& OutProcOutput) = 0;` — Invokes UnrealBuildTool with the given arguments @return true if tool was invoked properly
- L393 _public prototype_ `virtual FProcHandle InvokeUnrealBuildToolAsync(const FString& InCmdLineParams, FOutputDevice& Ar, void*& OutReadPipe, void*& OutWritePipe, bool bSkipBuildUBT = false) = 0;` — Launches UnrealBuildTool with the specified command line parameters @return process handle to the new UBT process
- L404 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn) = 0;` — Runs UnrealBuildTool with the given arguments. @param Description		Task description for FFeedbackContext @param RootDir			Engine root directory for the project to use. @param Arguments			Parameters for UnrealBuildTool @param Warn				Feedback context to use for progress updates @return true if the task completed successfully.
- L416 _public prototype_ `virtual bool RunUnrealBuildTool(const FText& Description, const FString& RootDir, const FString& Arguments, FFeedbackContext* Warn, int32& OutExitCode) = 0;` — Runs UnrealBuildTool with the given arguments. @param Description		Task description for FFeedbackContext @param RootDir			Engine root directory for the project to use. @param Arguments			Parameters for UnrealBuildTool @param Warn				Feedback context to use for progress updates @param OutExitCode		Receives the process exit code @return true if the task completed successfully.
- L423 _public prototype_ `virtual bool IsUnrealBuildToolRunning() = 0;` — Checks if an instance of UnrealBuildTool is running. @return true if an instance of UnrealBuildTool is running.
- L430 _public prototype_ `virtual const TArray<FTargetInfo>& GetTargetsForProject(const FString& ProjectFile) const = 0;` — Gets information about the build targets supported by a particular project. @return Array of TargetInfo objects
- L437 _public prototype_ `virtual const TArray<FTargetInfo>& GetTargetsForCurrentProject() const = 0;` — Gets information about the build targets supported by the current project. @return Array of TargetInfo objects
- L444 _public prototype_ `virtual FString GetUserTempPath() = 0;` — Gets the path to the user's temporary directory @return The path to the user's temporary directory
- L451 _public prototype_ `virtual FFeedbackContext* GetNativeFeedbackContext() = 0;` — Gets a feedback context which can display progress information using the native platform GUI. @return FFeedbackContext for the native GUI.
- L461 _public prototype_ `virtual bool EnumerateProjectsKnownByEngine(const FString& Identifier, bool bIncludeNativeProjects, TArray<FString>& OutProjectFileNames) = 0;` — Finds all the projects which the engine (given by an identifier) has a record of. This includes all the recently opened projects, projects in the default project directory, and so on. @param Identifier				Identifier for the engine @param bIncludeNativeProjects	Flag indicating whether to include native projects. @param OutProjectFileNames		Array to receive the paths of the projects known by the engine. @return True if the enumeration was successful, false otherwise.
- L468 _public prototype_ `virtual FString GetDefaultProjectCreationPath() = 0;` — Gets the default folder for creating new projects. @return Path to the folder
- L483 _public prototype_ `virtual bool GetOidcAccessToken(const FString& RootDir, const FString& ProjectFileName, const FString& ProviderIdentifier, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) = 0;` — Get an access token for use by OIDC compliant Identity Providers @param RootDir					Engine root directory for the project to use. @param ProjectFileName			Filename of the current project @param ProviderIdentifier		The identifier for the provider as configured in oidc-token.json @param bUnattended				True to indicate that no user interaction should be assumed @param Warn						Feedback context to use for progress updates @param OutToken					The allocated access token @param OutTokenExpiresAt			When the token expires @param bOutWasInteractiveLogin	True if the interactive login flow was used @return true if the task completed successfully.
- L497 _public prototype_ `virtual bool GetOidcAccessTokenWithRemoteConfig(const FString& RootDir, const FString& RemoteHost, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) = 0;` — Get an access token for use by OIDC compliant Identity Providers using a remote configuration @param RootDir					Engine root directory for the project to use. @param RemoteHost				The url to the remote host to fetch the config from @param bUnattended				True to indicate that no user interaction should be assumed @param Warn						Feedback context to use for progress updates @param OutToken					The allocated access token @param OutTokenExpiresAt			When the token expires @param bOutWasInteractiveLogin	True if the interactive login flow was used @return true if the task completed successfully.
- L513 _public prototype_ `virtual bool GetOidcAccessToken(const FString& RootDir, const FString& ProjectFileName, const FString& ProviderIdentifier, bool bUnattended, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) = 0;` — `UE_DEPRECATED(5.7, "Please use overload that takes EDesktopLoginInteractionLevel instead")` — Get an access token for use by OIDC compliant Identity Providers @param RootDir					Engine root directory for the project to use. @param ProjectFileName			Filename of the current project @param ProviderIdentifier		The identifier for the provider as configured in oidc-token.json @param bUnattended				True to indicate that no user interaction should be assumed @param Warn						Feedback context to use for progress updates @param OutToken					The allocated access token @param OutTokenExpiresAt			When the token expires @param bOutWasInteractiveLogin	True if the interactive login flow was used @return true if the task completed successfully.
- L528 _public prototype_ `virtual bool GetOidcAccessTokenWithRemoteConfig(const FString& RootDir, const FString& RemoteHost, bool bUnattended, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) = 0;` — `UE_DEPRECATED(5.7, "Please use overload that takes EDesktopLoginInteractionLevel instead")` — Get an access token for use by OIDC compliant Identity Providers using a remote configuration @param RootDir					Engine root directory for the project to use. @param RemoteHost				The url to the remote host to fetch the config from @param bUnattended				True to indicate that no user interaction should be assumed @param Warn						Feedback context to use for progress updates @param OutToken					The allocated access token @param OutTokenExpiresAt			When the token expires @param bOutWasInteractiveLogin	True if the interactive login flow was used @return true if the task completed successfully.
- L540 _public prototype_ `virtual bool GetOidcTokenStatus(const FString& RootDir, const FString& ProjectFileName, const FString& ProviderIdentifier, FFeedbackContext* Warn, int& OutStatus) = 0;` — Get the status of an access token for use by OIDC compliant Identity Providers @param RootDir					Engine root directory for the project to use. @param ProjectFileName			Filename of the current project @param ProviderIdentifier		The identifier for the provider as configured in oidc-token.json @param Warn						Feedback context to use for progress updates @param OutStatus					The allocated access token @return true if the task completed successfully.
- L548 _public prototype_ `UE_INTERNAL virtual FString GetOidcTokenExecutableFilename(const FString& RootDir) const = 0;` — Get the path to the OIDC token executable @param RootDir					Engine root directory for the project to use. @return The path to the OIDC token executable.
- L557 _public prototype_ `virtual bool GetHordeUrl(FString& OutHordeUrl, FString* OutHordeUrlConfigSource = nullptr) = 0;` — Get the URL of the configured Horde server for the current user account. @param OutHordeUrl				URL of the Horde server @param OutHordeUrlConfigSource	Optional output parameter describing the source of the configuration. @return true if a valid URL is returned.
- L564 _public prototype_ `virtual void SetHordeUrl(const FString& HordeUrl) = 0;` — Set the URL of the configured Horde server for the current user account. This will set the source of the configuration to EConfigSource::Unspecified. @param HordeUrl					URL of the Horde server
- L577 _public prototype_ `virtual bool GetHordeAccessToken(const FString& HordeUrl, EDesktopLoginInteractionLevel InteractionLevel, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) = 0;` — Gets an access token for the given Horde Server. @param HordeUrl					URL of the Horde server. @param bUnattended				True to indicate that no user interaction should be assumed @param Warn						Feedback context to use for progress updates @param OutToken					The allocated access token @param OutTokenExpiresAt			When the token expires @param bOutWasInteractiveLogin	True if the interactive login flow was used @return true if the task completed successfully.
- L591 _public prototype_ `virtual bool GetHordeAccessToken(const FString& HordeUrl, bool bUnattended, FFeedbackContext* Warn, FString& OutToken, FDateTime& OutTokenExpiresAt, bool& bOutWasInteractiveLogin) = 0;` — `UE_DEPRECATED(5.7, "Please use overload that takes EDesktopLoginInteractionLevel instead")` — Gets an access token for the given Horde Server. @param HordeUrl					URL of the Horde server. @param bUnattended				True to indicate that no user interaction should be assumed @param Warn						Feedback context to use for progress updates @param OutToken					The allocated access token @param OutTokenExpiresAt			When the token expires @param bOutWasInteractiveLogin	True if the interactive login flow was used @return true if the task completed successfully.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EFileDialogFlags`

### `Source/Developer/DesktopPlatform/Public/InstalledPlatformInfo.h` (Public)


#### enum `EProjectType`  
`enum class EProjectType : uint8`  
_L17-23_
- desc: Forward declaration
- L19 _public enumerator_ `Unknown`
- L20 _public enumerator_ `Any`
- L21 _public enumerator_ `Code`
- L22 _public enumerator_ `Content`

#### enum `EInstalledPlatformState`  
`enum class EInstalledPlatformState`  
_L27-34_
- L30 _public enumerator_ `Supported` — Query whether the platform is supported
- L33 _public enumerator_ `Downloaded` — Query whether the platform has been downloaded

#### struct `FInstalledPlatformConfiguration`  
`struct FInstalledPlatformConfiguration`  
_L39-61_
- desc: Information about a single installed platform configuration
- L42 _public member_ `EBuildConfiguration Configuration;` — Build Configuration of this combination
- L45 _public member_ `FString PlatformName;` — Name of the Platform for this combination
- L48 _public member_ `EBuildTargetType PlatformType;` — Type of Platform for this combination
- L51 _public member_ `FString Architecture;` — Name of the Architecture for this combination
- L54 _public member_ `FString RequiredFile;` — Location of a file that must exist for this combination to be valid (optional)
- L57 _public member_ `EProjectType ProjectType;` — Type of project this configuration can be used for
- L60 _public member_ `bool bCanBeDisplayed;` — Whether to display this platform as an option even if it is not valid

#### class `FInstalledPlatformInfo`  
`class FInstalledPlatformInfo`  
_L66-152_
- desc: Singleton class for accessing information about installed platform configurations
- L72 _public prototype_ `static FInstalledPlatformInfo& Get();` — Accessor for singleton
- L77 _public prototype_ `bool IsValidConfiguration(const EBuildConfiguration Configuration, EProjectType ProjectType = EProjectType::Any) const;` — Queries whether a configuration is valid for any available platform
- L82 _public prototype_ `bool IsValidPlatform(const FString& PlatformName, EProjectType ProjectType = EProjectType::Any) const;` — Queries whether a platform has any valid configurations
- L87 _public prototype_ `bool IsValidPlatformAndConfiguration(const EBuildConfiguration Configuration, const FString& PlatformName, EProjectType ProjectType = EProjectType::Any) const;` — Queries whether a platform and configuration combination is valid
- L92 _public prototype_ `bool CanDisplayPlatform(const FString& PlatformName, EProjectType ProjectType) const;` — Queries whether a platform can be displayed as an option, even if it's not supported for the specified project type
- L97 _public prototype_ `bool IsValidTargetType(EBuildTargetType TargetType) const;` — Queries whether a target type is valid for any configuration
- L107 _public prototype_ `bool IsValid(TOptional<EBuildTargetType> TargetType, TOptional<FString> Platform, TOptional<EBuildConfiguration> Configuration, EProjectType ProjectType, EInstalledPlatformState State) const;` — Determines whether the given target type is supported @param TargetType The target type being built @param Platform The platform being built @param Configuration The configuration being built @param ProjectType The project type required @param State State of the given platform support @return True if the target can be built
- L114 _public prototype_ `bool IsValidPlatformArchitecture(const FString& PlatformName, const FString& Architecture) const;` — Queries whether a platform architecture is valid for any configuration @param PlatformName Name of the platform's binary folder (eg. Win64, Android) @param Architecture Either a full architecture name or a partial substring for CPU/GPU combinations (eg. "-armv7", "-es2")
- L119 _public prototype_ `bool IsPlatformMissingRequiredFile(const FString& PlatformName) const;` — Queries whether a platform has any missing required files
- L126 _public prototype_ `static bool OpenInstallerOptions();` — Attempts to open the Launcher to the Installer options so that additional platforms can be downloaded @return false if the engine is not a stock release, user cancels action or launcher fails to load
- L132 _private prototype_ `FInstalledPlatformInfo();` — Constructor
- L137 _private prototype_ `void ParsePlatformConfiguration(FString PlatformConfiguration);` — Parse platform configuration info from a config file entry
- L142 _private prototype_ `bool ContainsValidConfiguration(TFunctionRef<bool(const FInstalledPlatformConfiguration)> ConfigFilter) const;` — Given a filter function, checks whether any configuration passes that filter and has required file
- L148 _private prototype_ `bool ContainsMatchingConfiguration(TFunctionRef<bool(const FInstalledPlatformConfiguration)> ConfigFilter) const;` — Given a filter function, checks whether any configuration passes that filter Doesn't check whether required file exists, so that we can find platforms that can be optionally installed
- L151 _private member_ `TArray<FInstalledPlatformConfiguration> InstalledPlatformConfigurations;` — List of installed platform configuration combinations

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DESKTOPPLATFORM_API`
- L25 _prototype_ `EProjectType EProjectTypeFromString(const FString& ProjectTypeName);`

### `Source/Developer/DesktopPlatform/Public/MultiPlatformTargetReceiptBuildWorkers.h` (Public)


#### class `FMultiPlatformTargetReceiptBuildWorkers`  
`class FMultiPlatformTargetReceiptBuildWorkers final`  
_L16-36_
- desc: Globally registers a UE::DerivedData::IBuildWorkerFactory instance for each platform that build workers can be supported. Users should include a $(Platform) variable in their file path to indicate that this worker receipt can exist for any platform. If the receipt path does not include a $(Platform) variable, then no attempt will be made to find variations of it for other platforms.
- L19 _public prototype_ `FMultiPlatformTargetReceiptBuildWorkers(FStringView TargetReceiptFilePath);`
- L20 _public prototype_ `~FMultiPlatformTargetReceiptBuildWorkers();`
- L22 _public prototype_ `FMultiPlatformTargetReceiptBuildWorkers(const FMultiPlatformTargetReceiptBuildWorkers&) = delete;`
- L23 _public prototype_ `FMultiPlatformTargetReceiptBuildWorkers& operator=(const FMultiPlatformTargetReceiptBuildWorkers&) = delete;`
- L34 _private member_ `TTypeCompatibleBytes<FTargetReceiptBuildWorker> PlatformSpecificWorkerFactories[SupportedPlatform_MAX];`
- L35 _private member_ `bool bAllPlatformsInitialized = false;`

#### enum `FMultiPlatformTargetReceiptBuildWorkers::ESupportedPlatform`  
`enum ESupportedPlatform : uint8`  
_L26-33_
- L28 _public enumerator_ `SupportedPlatform_Win64 = 0`
- L29 _public enumerator_ `SupportedPlatform_Mac`
- L30 _public enumerator_ `SupportedPlatform_Linux`
- L32 _public enumerator_ `SupportedPlatform_MAX`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DESKTOPPLATFORM_API`

### `Source/Developer/DesktopPlatform/Public/PlatformInfo.h` (Public)


#### enum `PlatformInfo::EPlatformFlags::Flag`  
`enum Flag`  
_L22-32_
- L25 _public enumerator_ `None = 0` — Nothing of interest
- L28 _public enumerator_ `BuildFlavor = 1 << 0` — The flavor generates different output when building (eg, 32 or 64-bit)
- L31 _public enumerator_ `CookFlavor = 1 << 1` — The flavor generates different output when cooking (eg, ETC2 or ASTC texture format)

#### enum `PlatformInfo::EPlatformFilter`  
`enum class EPlatformFilter : uint8`  
_L36-46_
- desc: Flavor types used when filtering the platforms based upon their flags
- L39 _public enumerator_ `All` — Include all platform types
- L42 _public enumerator_ `BuildFlavor` — Include only build flavors
- L45 _public enumerator_ `CookFlavor` — Include only cook flavors

#### struct `PlatformInfo::FTargetPlatformInfo`  
`struct FTargetPlatformInfo`  
_L49-101_
- desc: Information about a given platform
- L51 _public prototype_ `FTargetPlatformInfo(const FString& InIniPlatformName, EBuildTargetType InType, const FString& InCookFlavor);`
- L54 _public member_ `FName Name;` — Name of the Info object as well as the ITargetPlatform that this Info describes
- L57 _public member_ `FName PlatformFlavor;` — Platform flavor, eg "ETC2" for "Android_ETC2"
- L60 _public member_ `FText DisplayName;` — The friendly (and localized) display name of this platform
- L63 _public member_ `EBuildTargetType PlatformType;` — Type of this platform
- L66 _public member_ `EPlatformFlags::Flags PlatformFlags;` — Flags for this platform
- L69 _public member_ `FString UATCommandLine;` — Additional argument string data to append to UAT commands relating to this platform
- L72 _public member_ `FName IniPlatformName;` — Name of this platform when loading INI files (and finding DataDrivenPlatformInfo)
- L75 _public member_ `FTargetPlatformInfo* VanillaInfo;` — For flavors, this points to the vanilla (parent) object - for vanilla objects, this points to itself so ->VanillaInfo can be used without checking for null
- L78 _public member_ `TArray<const FTargetPlatformInfo*> Flavors;` — For vanilla objects, this contains the flavors (children)
- L81 _public member_ `const FDataDrivenPlatformInfo* DataDrivenPlatformInfo;` — Cached pointer to the DDPI
- L84 _public function_ `FORCEINLINE bool IsVanilla() const` — Returns true if this platform is vanilla
- L90 _public function_ `FORCEINLINE bool IsFlavor() const` — Returns true if this platform is a flavor
- L96 _public function_ `FName GetIconStyleName(const EPlatformIconSize InIconSize) const` — convenience function

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace PlatformInfo`
- L19 _namespace_ `namespace EPlatformFlags` (scope `PlatformInfo`)
- L21 _typedef_ `typedef uint8 Flags;` (scope `PlatformInfo::EPlatformFlags`)
- L108 _prototype_ `const FTargetPlatformInfo* FindPlatformInfo(const FName& InPlatformName);` (scope `PlatformInfo`) — Try and find the information for the given platform @param InPlatformName - The name of the platform to find @return The platform info if the platform was found, null otherwise
- L115 _prototype_ `const FTargetPlatformInfo* FindVanillaPlatformInfo(const FName& InPlatformName);` (scope `PlatformInfo`) — Try and find the vanilla information for the given platform @param InPlatformName - The name of the platform to find (can be a flavor, but you'll still get back the vanilla platform) @return The platform info if the platform was found, null otherwise
- L121 _prototype_ `const TArray<FTargetPlatformInfo*>& GetPlatformInfoArray();` (scope `PlatformInfo`) — Get an array of all the platforms we know about @return The pointer to the start of the platform array
- L127 _prototype_ `const TArray<FTargetPlatformInfo*>& GetVanillaPlatformInfoArray();` (scope `PlatformInfo`) — Get an array of only the vanilla platforms @return The pointer to the start of the platform array
- L134 _prototype_ `void UpdatePlatformDisplayName(FString InPlatformName, FText InDisplayName);` (scope `PlatformInfo`) — Update the display name for a platform @param InPlatformName - The platform to update @param InDisplayName - The new display name
- L141 _prototype_ `const TArray<FName>& GetAllPlatformGroupNames();` (scope `PlatformInfo`) — Returns a list of all defined Platform Groups, excluding None. Used to to present a list in the Per-Platform Properties UI. @return An array of FNames.
- L148 _prototype_ `const TArray<FName>& GetAllVanillaPlatformNames();` (scope `PlatformInfo`) — Returns a list of all defined Platform, in vanilla form. Used to to present a list in the Per-Platform Properties UI. @return An array of FNames.

### `Source/Developer/DesktopPlatform/Public/SteamDeck/SteamDeckDevice.h` (Public)


#### class `TSteamDeckDevice`  
`template<class ParentDeviceClass> class TSteamDeckDevice : public ParentDeviceClass`  
_L15-107_
- inherits: `ParentDeviceClass`
- desc: Extend from either WIndows or Linux device, since there will be a lot of shared functionality
- L18 _public function_ `TSteamDeckDevice(FString InIpAddr, FString InDeviceName, FString InUserName, FString InPassword, const ITargetPlatformControls& InTargetPlatformControls, const TCHAR* InRuntimeOSName) : ParentDeviceClass(InTargetPlatformControls) , IpAddr(InIpAddr) , UserName(InUserName) , Password(InPassword) , RuntimeOSName(InRuntimeOSName)`
- L28 _public function_ `virtual FString GetName() const override`
- L33 _public function_ `virtual FTargetDeviceId GetId() const override`
- L38 _public function_ `virtual FString GetOperatingSystemName() override`
- L43 _public function_ `virtual bool GetUserCredentials(FString& OutUserName, FString& OutUserPassword) override`
- L51 _public function_ `static TArray<ITargetDevicePtr> DiscoverDevices(const ITargetPlatformControls& TargetPlatformControls, const TCHAR* RuntimeOSName)`
- L102 _private member_ `FString IpAddr;`
- L103 _private member_ `FString DeviceName;`
- L104 _private member_ `FString UserName;`
- L105 _private member_ `FString Password;`
- L106 _private member_ `FString RuntimeOSName;`

### `Source/Developer/DesktopPlatform/Public/TargetReceipt.h` (Public)


#### struct `FBuildProduct`  
`struct FBuildProduct`  
_L19-26_
- desc: Record of a file that was created as part of the build process
- L22 _public member_ `FString Path;` — Path to the file.
- L25 _public member_ `FString Type;` — Type of the build product.

#### struct `FRuntimeDependency`  
`struct FRuntimeDependency`  
_L31-38_
- desc: Information about a file which is required by the target at runtime, and must be moved around with it.
- L34 _public member_ `FString Path;` — The file that should be staged. Should use $(EngineDir) and $(ProjectDir) variables as a root, so that the target can be relocated to different machines.
- L37 _public member_ `FString Type;` — How to stage this file.

#### struct `FReceiptProperty`  
`struct FReceiptProperty`  
_L43-50_
- desc: Arbitrary property name/value which metadata from the build scripts can be passed on to downstream tasks
- L46 _public member_ `FString Name;` — Property name
- L49 _public member_ `FString Value;` — Value of the property

#### struct `FTargetReceipt`  
`struct FTargetReceipt`  
_L55-148_
- desc: Stores information about a compiled target. Mirror of the TargetReceipt class generated by UBT.
- L58 _public member_ `FString ProjectFile;` — Path to the project file for this target
- L61 _public member_ `FString ProjectDir;` — The project directory
- L64 _public member_ `FString TargetName;` — The name of this target
- L67 _public member_ `FString Platform;` — Which platform the target is compiled for
- L70 _public member_ `FString Architecture;` — Which platform the target is compiled for
- L73 _public member_ `FString BuildSettingsVersion;` — What build settings version the target is using
- L76 _public member_ `FString TargetBuildEnvironment;` — What build environment the target is using
- L79 _public member_ `EBuildConfiguration Configuration;` — Which configuration this target is compiled in
- L82 _public member_ `EBuildTargetType TargetType;` — The type of the target
- L85 _public member_ `FBuildVersion Version;` — The version information for this target
- L91 _public member_ `FString Launch;` — The executable to launch for this target. (NOTE: If the LaunchCmd field exists, but Launch does not, this will actually reflect LaunchCmd!)
- L94 _public member_ `TOptional<FString> LaunchCmd;` — The console subsystem executable for this target
- L97 _public member_ `TArray<FBuildProduct> BuildProducts;` — The build products which are part of this target
- L100 _public member_ `TArray<FRuntimeDependency> RuntimeDependencies;` — All the runtime dependencies that this target relies on
- L103 _public member_ `TMap<FString, bool> PluginNameToEnabledState;` — All plugins that were either enabled or disabled via the target rules.
- L106 _public member_ `TArray<FString> BuildPlugins;` — All plugins which are part of this target.
- L109 _public member_ `TArray<FReceiptProperty> AdditionalProperties;` — Additional build properties passed through from the module rules
- L118 _public prototype_ `bool Read(const FString& FileName, bool bExpandVariables = true);` — Read a target receipt from disk @param FileName The file to read from @param bExpandVariables Whether variables should be expanded in paths or not @return True if the file was read successfully
- L127 _public prototype_ `bool LaunchesCurrentExecutable(bool bCheckLaunchField = true, bool bCheckLaunchCmdField = true) const;` — Compares the running executable's path to the `Launch` and/or `LaunchCmd` paths. @param bCheckLaunchField Return true if the current executable is the one referred to by the `Launch` field. @param bCheckLaunchCmdField Return true if the current executable is the one referred to by the `LaunchCmd` field. @return True if either specified check matches; otherwise, false.
- L139 _public prototype_ `static FString GetDefaultPath(const TCHAR* BaseDir, const TCHAR* TargetName, const TCHAR* Platform, EBuildConfiguration Configuration, const TCHAR* BuildArchitecture);` — Gets the default path for a target receipt @param BaseDir Base directory for the target being built; either the project directory or engine directory. @param TargetName The target being built @param Platform The target platform @param Configuration The target configuration @param BuildArchitecture The architecture being built @return Path to the receipt for this target
- L147 _private prototype_ `void ExpandVariables(FString& Path);` — Expands the $(EngineDir) and $(ProjectDir) variables within a string @param Path Path to expand variables within

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DESKTOPPLATFORM_API`

### `Source/Developer/DesktopPlatform/Public/TargetReceiptBuildWorker.h` (Public)


#### struct `FTargetReceiptBuildWorkerParams`  
`struct FTargetReceiptBuildWorkerParams`  
_L18-30_
- L21 _public member_ `FStringView WorkerPackagePath;` — When provided, override the default saved builder worker package path with this path.
- L23 _public member_ `UE::TFunctionWithContext<bool ()> ShouldAbort = nullptr;` — When provided, called periodically to check if build worker creation should abort early.
- L25 _public member_ `bool bAlwaysBuild = false;` — When true, skip timestamp checks and unconditionally create the build worker package.
- L27 _public member_ `bool bIncludeSymbols = false;` — When true, include symbol files in the build worker package.
- L29 _public member_ `bool bSkipCompression = false;` — When true, skips compression of the build worker package attachments.

#### class `FTargetReceiptBuildWorker`  
`class FTargetReceiptBuildWorker final`  
_L49-60_
- desc: Globally registers a UE::DerivedData::IBuildWorkerFactory instance that runs an executable built by UnrealBuildTool. UnrealBuildTool provides the executable information through a TargetReceipt file.
- L52 _public prototype_ `FTargetReceiptBuildWorker(FStringView TargetReceiptFilePath);`
- L53 _public prototype_ `~FTargetReceiptBuildWorker();`
- L55 _public prototype_ `FTargetReceiptBuildWorker(const FTargetReceiptBuildWorker&) = delete;`
- L56 _public prototype_ `FTargetReceiptBuildWorker& operator=(const FTargetReceiptBuildWorker&) = delete;`
- L59 _private member_ `TPimplPtr<FTargetReceiptBuildWorkerFactory> Factory;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DESKTOPPLATFORM_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L40 _prototype_ `[[nodiscard]] TOptional<UE::DerivedData::FBuildWorker> CreateBuildWorkerFromTargetReceipt( FStringView TargetReceiptPath, UE::DerivedData::IBuildWorkerRegistry& Registry, const FTargetReceiptBuildWorkerParams& Params = {});` — Creates a build worker package from the target receipt. @param TargetReceiptPath   Path to load the target receipt from. @param Registry   Registry provided to avoid DesktopPlatform requiring a link dependency on DerivedDataCache. @param Params   Optional parameters to configure build worker package creation. @return A build worker for a package saved to the path, or unset on error.
