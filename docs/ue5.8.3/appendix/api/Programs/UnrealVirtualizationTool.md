# Programs / UnrealVirtualizationTool

- module root: `Source/Programs/UnrealVirtualizationTool`
- headers: 8; symbols: 189
- symbol kinds: class=8, delegate=1, enum=5, enumerator=17, function=13, macro=1, member=33, namespace=14, prototype=92, struct=4, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DesktopPlatform, Json, PerforceSourceControl, Projects, SourceControl, Virtualization
- PublicIncludePathModuleNames: Launch

### `Source/Programs/UnrealVirtualizationTool/Private/Commands/CommandBase.h` (Private)


#### struct `UE::Virtualization::FCommandOutput`  
`struct FCommandOutput : public FJsonSerializable`  
_L33-46_
- inherits: `FJsonSerializable`
- L35 _public prototype_ `FCommandOutput() = default;`
- L36 _public function_ `FCommandOutput(FStringView InProjectName) : ProjectName(InProjectName)`
- L45 _public member_ `FString ProjectName;`

#### class `UE::Virtualization::FCommand`  
`class FCommand`  
_L49-168_
- desc: The base class to derive new commands from
- L52 _public prototype_ `FCommand(FStringView InCommandName);`
- L53 _public prototype_ `virtual ~FCommand();`
- L55 _public prototype_ `virtual bool Initialize(const TCHAR* CmdLine) = 0;`
- L57 _public function_ `void ToJson(TSharedRef<TJsonWriter<> >& JsonWriter) const`
- L63 _public function_ `bool FromJson(TSharedPtr<FJsonObject> JsonObject)`
- L74 _public prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer) = 0;`
- L82 _public prototype_ `virtual bool IsProjectValidForCommand(const FProject& Project) const = 0;` — Check to see if the provided project can be run with the current command. @Project	The project to be validated @return	True if the project is allowed to be processed by the command and false if it is not.
- L89 _public prototype_ `virtual bool ProcessProject(const FProject& Project, TUniquePtr<FCommandOutput>& Output) = 0;` — Called when a project needs to be processed by the command. The output parameter is used to return output that will eventually be passed to ::ProcessOutput. If the command does not produce any output needed by ::ProcessOutput then the parameter may be ignored.
- L97 _public prototype_ `virtual bool ProcessOutput(const TArray<TUniquePtr<FCommandOutput>>& CmdOutputArray) = 0;` — Called after all projects have been processed. This will always be called by the original processes and never called by a spawned child process. If the command produces output when processing a project then the CmdOutputArray will be populated, otherwise it will be empty. It is assumed that each command knows how to cast the FCommandOutput to the correct type.
- L105 _public prototype_ `virtual TUniquePtr<FCommandOutput> CreateOutputObject() const = 0;` — Derived command classes should return a new instance of the command output that it can produce. This will be called when we are parsing child process output files while attempting to reconstruct the output of a child process. Commands that do not return any output can return nullptr.
- L107 _public prototype_ `virtual const TArray<FString>& GetPackages() const = 0;`
- L109 _public function_ `const FString& GetName() const`
- L116 _protected prototype_ `static void ParseCommandLine(const TCHAR* CmdLine, TArray<FString>& Tokens, TArray<FString>& Switches);`
- L128 _protected prototype_ `static EPathResult ParseSwitchForPaths(const FString& Switch, TArray<FString>& OutPackages);`
- L139 _protected prototype_ `bool TryConnectToSourceControl(FStringView ClientSpecName);` — Creates a new ISourceControlProvider that can be used to perforce source control operations. This provider will remain valid until reset or the command is completed. @param ClientSpecName	The client spec to use when connecting. If left blank we will use a default spec, which will likely be auto determined by the system. @return True if the provider was created, otherwise false.
- L140 _protected function_ `bool TryConnectToSourceControl()`
- L145 _protected prototype_ `bool TryParseChangelist(FStringView ClientSpecName, FStringView ChangelistNumber, TArray<FString>& OutPackages, FSourceControlChangelistPtr* OutChangelist);`
- L147 _protected prototype_ `FString FindClientSpecForChangelist(FStringView ChangelistNumber);`
- L150 _private member_ `FString CommandName;`
- L157 _private member_ `TUniquePtr<ISourceControlProvider> OwnedSCCProvider;` — Sometimes the command will have to create and own the source control provider and be responsible for cleaning it up once the command has finished. In these cases we store the pointer to the provider that we own, here.
- L165 _protected member_ `ISourceControlProvider* SCCProvider = nullptr;` — Pointer to the source control provider that the command should use.This can either be to a provider that the command owns in 'OwnedSCCProvider' or one provided for us by the source control api.

#### enum `UE::Virtualization::FCommand::EPathResult`  
`enum EPathResult : int8`  
_L118-126_
- L121 _public enumerator_ `Error = -1` — The switch was a valid package/path but parsing it resulted in an error
- L123 _public enumerator_ `NotFound = 0` — The switch was not a valid package/path
- L125 _public enumerator_ `Success = 1` — The switch was a valid package/path and was successfully parsed

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TSharedPtr<ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistPtr;`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Virtualization` (scope `UE`)
- L30 _macro_ `#define JSON_SERIALIZE_PARENT(ParentType) \` — The JSON serialization macros do not support inheritance properly as far as I can tell, this helps work around that. Currently it stores all levels of the inheritance chain in the same json object, I'd want to change this to have an object per level before considering moving this to JsonSerializerMacros.h

### `Source/Programs/UnrealVirtualizationTool/Private/Commands/RehydrateCommand.h` (Private)


#### class `UE::Virtualization::FRehydrateCommand`  
`class FRehydrateCommand final : public FCommand`  
_L10-38_
- inherits: `FCommand`
- L13 _public prototype_ `FRehydrateCommand(FStringView CommandName);`
- L14 _public prototype_ `virtual ~FRehydrateCommand() = default;`
- L16 _public prototype_ `static void PrintCmdLineHelp();`
- L18 _private prototype_ `virtual bool Initialize(const TCHAR* CmdLine) override;`
- L20 _private prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer) override;`
- L22 _private prototype_ `virtual bool IsProjectValidForCommand(const FProject& Project) const final;`
- L24 _private prototype_ `virtual bool ProcessProject(const FProject& Project, TUniquePtr<FCommandOutput>& Output) override;`
- L25 _private prototype_ `virtual bool ProcessOutput(const TArray<TUniquePtr<FCommandOutput>>& OutputArray) override;`
- L27 _private prototype_ `virtual TUniquePtr<FCommandOutput> CreateOutputObject() const override;`
- L29 _private prototype_ `virtual const TArray<FString>& GetPackages() const override;`
- L33 _private member_ `FString ClientSpecName;`
- L35 _private member_ `TArray<FString> Packages;`
- L37 _private member_ `bool bShouldCheckout = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Programs/UnrealVirtualizationTool/Private/Commands/VirtualizeCommand.h` (Private)


#### struct `UE::Virtualization::FVirtualizeCommandOutput`  
`struct FVirtualizeCommandOutput final : public FCommandOutput`  
_L10-21_
- inherits: `FCommandOutput`
- L12 _public prototype_ `FVirtualizeCommandOutput() = default;`
- L13 _public prototype_ `FVirtualizeCommandOutput(FStringView InProjectName, const TArray<FText>& InDescriptionTags);`
- L16 _public prototype_ `JSON_SERIALIZE_PARENT(FCommandOutput);`
- L20 _public member_ `TArray<FString> DescriptionTags;`

#### class `UE::Virtualization::FVirtualizeCommand`  
`class FVirtualizeCommand : public FCommand`  
_L23-61_
- inherits: `FCommand`
- L26 _public prototype_ `FVirtualizeCommand(FStringView CommandName);`
- L27 _public prototype_ `virtual ~FVirtualizeCommand() = default;`
- L29 _public prototype_ `static void PrintCmdLineHelp();`
- L32 _private prototype_ `virtual bool Initialize(const TCHAR* CmdLine) override;`
- L34 _private prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer) override;`
- L36 _private prototype_ `virtual bool IsProjectValidForCommand(const FProject& Project) const final;`
- L38 _private prototype_ `virtual bool ProcessProject(const FProject& Project, TUniquePtr<FCommandOutput>& Output) override;`
- L39 _private prototype_ `virtual bool ProcessOutput(const TArray<TUniquePtr<FCommandOutput>>& CmdOutputArray) override;`
- L41 _private prototype_ `virtual TUniquePtr<FCommandOutput> CreateOutputObject() const override;`
- L43 _private prototype_ `virtual const TArray<FString>& GetPackages() const override;`
- L45 _private prototype_ `bool TrySubmitChangelist(const FSourceControlChangelistPtr& ChangelistToSubmit, const TArray<FString>& DescriptionTags);`
- L49 _protected prototype_ `bool TryParsePackageList(const FString& PackageListPath, TArray<FString>& OutPackages);`
- L52 _protected member_ `FString ClientSpecName;`
- L54 _protected member_ `TArray<FString> AllPackages;`
- L56 _protected member_ `FSourceControlChangelistPtr SourceChangelist;`
- L57 _protected member_ `FString SourceChangelistNumber;`
- L59 _protected member_ `bool bShouldSubmitChangelist = false;`
- L60 _protected member_ `bool bShouldCheckout = false;`

#### class `UE::Virtualization::FVirtualizeLegacyChangeListCommand`  
`class FVirtualizeLegacyChangeListCommand final : public FVirtualizeCommand`  
_L64-72_
- inherits: `FVirtualizeCommand`
- desc: Used to convert the legacy command line -Mode=Changelist to the new style of command
- L67 _public prototype_ `FVirtualizeLegacyChangeListCommand(FStringView CommandName);`
- L68 _public prototype_ `virtual ~FVirtualizeLegacyChangeListCommand() = default;`
- L71 _private prototype_ `virtual bool Initialize(const TCHAR* CmdLine) override;`

#### class `UE::Virtualization::FVirtualizeLegacyPackageListCommand`  
`class FVirtualizeLegacyPackageListCommand final : public FVirtualizeCommand`  
_L75-83_
- inherits: `FVirtualizeCommand`
- desc: Used to convert the legacy command line -Mode=Packagelist to the new style of command
- L78 _public prototype_ `FVirtualizeLegacyPackageListCommand(FStringView CommandName);`
- L79 _public prototype_ `virtual ~FVirtualizeLegacyPackageListCommand() = default;`
- L82 _private prototype_ `virtual bool Initialize(const TCHAR* CmdLine) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Programs/UnrealVirtualizationTool/Private/OverrideOutputDevice.h` (Private)


#### class `UE::FOverrideOutputDevice`  
`class FOverrideOutputDevice final : public FFeedbackContextAnsi`  
_L17-39_
- inherits: `FFeedbackContextAnsi`
- desc: This class can be used to prevent log messages from other systems being logged with the Display verbosity. In practical terms this means as long as the class is alive, only LogVirtualizationTool messages will be logged to the display meaning the user will have less information to deal with.
- L20 _public prototype_ `FOverrideOutputDevice();`
- L22 _public prototype_ `virtual ~FOverrideOutputDevice();`
- L24 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override`
- L29 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time) override;`
- L31 _public prototype_ `virtual void SerializeRecord(const UE::FLogRecord& Record) override;`
- L35 _private prototype_ `bool ShouldFilterMessage(ELogVerbosity::Type Verbosity, const FName& Category);`
- L37 _private member_ `FFeedbackContext* OriginalLog;`
- L38 _private member_ `FDelegateHandle OnInitHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UE`

### `Source/Programs/UnrealVirtualizationTool/Private/ProcessUtilities.h` (Private)


#### struct `UE::Virtualization::FProcessPipes`  
`struct FProcessPipes`  
_L15-76_
- desc: Wrapper around stdin and stdout pipes created by a call to FPlatformProcess::CreatePipe
- L17 _public function_ `FProcessPipes()`
- L23 _public function_ `~FProcessPipes()`
- L29 _public function_ `void ProcessStdOut()`
- L49 _public function_ `void* GetStdInForProcess() const`
- L54 _public function_ `void* GetStdInForWriting() const`
- L59 _public function_ `void* GetStdOutForProcess() const`
- L64 _public function_ `void* GetStdOutForReading() const`
- L71 _private member_ `void* StdOutReadPipe = nullptr;`
- L72 _private member_ `void* StdOutWritePipe = nullptr;`
- L74 _private member_ `void* StdInReadPipe = nullptr;`
- L75 _private member_ `void* StdInWritePipe = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Programs/UnrealVirtualizationTool/Private/ProjectFiles.h` (Private)


#### enum `UE::Virtualization::EProjectType`  
`enum EProjectType : int32`  
_L13-19_
- L15 _public enumerator_ `Unknown = -1` — Error condition
- L17 _public enumerator_ `GameProject` — .uproject
- L18 _public enumerator_ `UEFNProject` — .uefnproject

#### struct `UE::Virtualization::FPlugin`  
`struct FPlugin : public FJsonSerializable`  
_L24-36_
- inherits: `FJsonSerializable`
- L27 _public member_ `FString PluginFilePath;`
- L29 _public member_ `TArray<FString> PackagePaths;`

#### class `UE::Virtualization::FProject`  
`class FProject : public FJsonSerializable`  
_L38-101_
- inherits: `FJsonSerializable`
- L43 _public prototype_ `FProject() = default;`
- L44 _public prototype_ `FProject(FString&& ProjectFilePath);`
- L45 _public prototype_ `~FProject() = default;`
- L47 _public prototype_ `void AddFile(const FString& FilePath);`
- L48 _public prototype_ `void AddPluginFile(const FString& FilePath, FString&& PluginFilePath);`
- L54 _public prototype_ `const FString& GetProjectFilePath() const;` — Returns the path of the project file that we should use for the content within this project. This can be different from the project path that was used to create the FProject.
- L56 _public prototype_ `FStringView GetProjectName() const;`
- L57 _public prototype_ `EProjectType GetProjectType() const;`
- L59 _public prototype_ `bool DoesMatchProjectPath(FStringView Path) const;`
- L61 _public prototype_ `TArray<FString> GetAllPackages() const;`
- L62 _public prototype_ `int32 GetNumPackages() const;`
- L64 _public prototype_ `void RegisterMountPoints() const;`
- L65 _public prototype_ `void UnRegisterMountPoints() const;`
- L67 _public prototype_ `bool TryLoadConfig(FConfigFile& OutConfig) const;`
- L71 _private member_ `FString ProjectFilePath;` — The original path for the project (can be any type supported by EProjectType)
- L73 _private member_ `FString OverridenProjectFilePath;` — The path of the project to use for sourcing virtualization settings. This
- L86 _private member_ `TArray<FPlugin> Plugins;`
- L87 _private member_ `TArray<FString> PackagePaths;`
- L89 _private member_ `EProjectType ProjectType = EProjectType::Unknown;`
- L91 _private prototype_ `void ProcessProjectPath();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Virtualization` (scope `UE`)
- L21 _prototype_ `const TCHAR* LexToString(UE::Virtualization::EProjectType Type);` (scope `UE::Virtualization`)
- L22 _prototype_ `void LexFromString(UE::Virtualization::EProjectType& OutType, const TCHAR* InString);` (scope `UE::Virtualization`)

### `Source/Programs/UnrealVirtualizationTool/Private/UnrealVirtualizationTool.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVirtualizationTool, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVirtualizationTool, Log, All);`

### `Source/Programs/UnrealVirtualizationTool/Private/UnrealVirtualizationToolApp.h` (Private)


#### enum `UE::Virtualization::EMode`  
`enum class EMode :uint32`  
_L17-36_
- desc: The mode of the application to run
- L20 _public enumerator_ `Unknown = 0` — Error condition
- L25 _public enumerator_ `Changelist` — Virtualize and submit a given changelist
- L27 _public enumerator_ `PackageList` — Virtualize a list of packages provided by text file
- L32 _public enumerator_ `Virtualize` — Virtualize one or more packages
- L35 _public enumerator_ `Rehydrate` — Rehydrate one or more packages

#### enum `UE::Virtualization::EInitResult`  
`enum class EInitResult`  
_L39-47_
- desc: The result of FUnrealVirtualizationToolApp initialization
- L42 _public enumerator_ `Success = 0` — Initialization succeeded and the application should run.
- L44 _public enumerator_ `EarlyOut` — No error was encountered but the application should early out and not run.
- L46 _public enumerator_ `Error` — Initialization failed with an error, we should not run and should display an error to the user

#### enum `UE::Virtualization::EProcessResult`  
`enum class EProcessResult`  
_L49-54_
- L51 _public enumerator_ `Success = 0`
- L52 _public enumerator_ `Error`
- L53 _public enumerator_ `ChildProcessError`

#### class `UE::Virtualization::FUnrealVirtualizationToolApp`  
`class FUnrealVirtualizationToolApp`  
_L56-118_
- L59 _public prototype_ `FUnrealVirtualizationToolApp();`
- L60 _public prototype_ `~FUnrealVirtualizationToolApp();`
- L62 _public prototype_ `EInitResult Initialize();`
- L63 _public prototype_ `EProcessResult Run();`
- L67 _private prototype_ `void PrintCmdLineHelp() const;`
- L69 _private prototype_ `EProcessResult ProcessProjects(TArray<TUniquePtr<FCommandOutput>>& OutputArray);`
- L71 _private prototype_ `bool TryLoadModules();`
- L72 _private prototype_ `bool TryInitEnginePlugins();`
- L74 _private prototype_ `EInitResult TryParseCmdLine();`
- L75 _private prototype_ `EInitResult TryParseGlobalOptions(const TCHAR* CmdLine);`
- L77 _private prototype_ `EInitResult CreateCommandFromString(const FString& CommandName, const TCHAR* Cmdline);`
- L79 _private prototype_ `bool TrySortFilesByProject(const TArray<FString>& Packages);`
- L80 _private prototype_ `void FilterProjectsForCommand();`
- L82 _private prototype_ `bool TryFindProject(const FString& PackagePath, FString& ProjectFilePath, FString& PluginFilePath) const;`
- L83 _private prototype_ `FProject& FindOrAddProject(FString&& ProjectFilePath);`
- L85 _private prototype_ `bool IsChildProcess() const;`
- L87 _private prototype_ `void AddGlobalOption(FStringView Options);`
- L89 _private prototype_ `static bool TryReadChildProcessOutputFile(const FGuid& ChildProcessId, const FCommand& Command, TArray<TUniquePtr<FCommandOutput>>& OutputArray);`
- L90 _private prototype_ `static bool TryWriteChildProcessOutputFile(const FString& ChildProcessId, const TArray<TUniquePtr<FCommandOutput>>& OutputArray);`
- L93 _private prototype_ `bool TryReadChildProcessInputFile(const FString& InputPath);` — Note not currently static due to dependencies
- L94 _private prototype_ `static bool TryWriteChildProcessInputFile(const FGuid& ChildProcessId, const FCommand& Command, const FProject& Project, FStringBuilderBase& OutPath);`
- L95 _private prototype_ `static void CleanUpChildProcessFiles(const FGuid& ChildProcessId);`
- L97 _private prototype_ `static EProcessResult LaunchChildProcess(const FCommand& Command, const FProject& Project, FStringView GlobalOptions, TArray<TUniquePtr<FCommandOutput>>& OutputArray);`
- L102 _private member_ `TUniquePtr<FFeedbackContext> OutputDeviceOverride;` — Override used to suppress log messages
- L105 _private member_ `FString ChildProcessId;` — Stored the id of the child process. This is the base file name of the input file used to launch it
- L108 _private member_ `FString GlobalCmdlineOptions;` — A string containing all global options that were found in the cmdline
- L111 _private member_ `TArray<FProject> Projects;` — Data structure holding the files in the changelist sorted by project and then by plugin
- L114 _private member_ `EMode Mode = EMode::Unknown;` — The mode for the application to run
- L117 _private member_ `TUniquePtr<FCommand> CurrentCommand;` — The command being processed

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Virtualization` (scope `UE`)
