# Editor / LocalizationCommandletExecution

- module root: `Source/Editor/LocalizationCommandletExecution`
- headers: 2; symbols: 44
- symbol kinds: class=1, function=6, macro=1, member=7, namespace=2, prototype=26, struct=1
- PrivateDependencyModuleNames: ApplicationCore, DesktopPlatform, EditorFramework, Engine, InputCore, Localization, Slate, SlateCore, SourceControl, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Editor/LocalizationCommandletExecution/Public/LocalizationCommandletExecution.h` (Public)


#### struct `LocalizationCommandletExecution::FTask`  
`struct FTask`  
_L13-26_
- L15 _public function_ `FTask()`
- L17 _public function_ `FTask(const FText& InName, const FString& InScriptPath, const bool InShouldUseProjectFile) : Name(InName) , ScriptPath(InScriptPath) , ShouldUseProjectFile(InShouldUseProjectFile)`
- L23 _public member_ `FText Name;`
- L24 _public member_ `FString ScriptPath;`
- L25 _public member_ `bool ShouldUseProjectFile;`

#### class `FLocalizationCommandletProcess`  
`class FLocalizationCommandletProcess : public TSharedFromThis<FLocalizationCommandletProcess>`  
_L31-68_
- inherits: `TSharedFromThis<FLocalizationCommandletProcess>`
- L34 _public prototype_ `static TSharedPtr<FLocalizationCommandletProcess> Execute(const FString& ConfigFilePath, const bool UseProjectFile = true);`
- L37 _private function_ `FLocalizationCommandletProcess(void* const InReadPipe, void* const InWritePipe, const FProcHandle InProcessHandle, const FString& InProcessArguments) : ReadPipe(InReadPipe) , WritePipe(InWritePipe) , ProcessHandle(InProcessHandle) , ProcessArguments(InProcessArguments)`
- L46 _public prototype_ `~FLocalizationCommandletProcess();`
- L48 _public function_ `void* GetReadPipe() const`
- L53 _public function_ `FProcHandle& GetHandle()`
- L58 _public function_ `const FString& GetProcessArguments() const`
- L64 _private member_ `void* const ReadPipe;`
- L65 _private member_ `void* const WritePipe;`
- L66 _private member_ `FProcHandle ProcessHandle;`
- L67 _private member_ `FString ProcessArguments;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LOCALIZATIONCOMMANDLETEXECUTION_API`
- L11 _namespace_ `namespace LocalizationCommandletExecution`
- L28 _prototype_ `bool Execute(const TSharedRef<SWindow>& ParentWindow, const FText& Title, const TArray<FTask>& Tasks);` (scope `LocalizationCommandletExecution`)

### `Source/Editor/LocalizationCommandletExecution/Public/LocalizationCommandletTasks.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace LocalizationCommandletTasks`
- L11 _prototype_ `bool GatherTextForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets);` (scope `LocalizationCommandletTasks`)
- L12 _prototype_ `bool GatherTextForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target);` (scope `LocalizationCommandletTasks`)
- L14 _prototype_ `bool ImportTextForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L15 _prototype_ `bool ImportTextForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L16 _prototype_ `bool ImportTextForCulture(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const FString& CultureName, const TOptional<FString> FilePath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L18 _prototype_ `bool ExportTextForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L19 _prototype_ `bool ExportTextForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L20 _prototype_ `bool ExportTextForCulture(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const FString& CultureName, const TOptional<FString> FilePath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L22 _prototype_ `bool ImportDialogueScriptForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L23 _prototype_ `bool ImportDialogueScriptForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L24 _prototype_ `bool ImportDialogueScriptForCulture(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const FString& CultureName, const TOptional<FString> FilePath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L26 _prototype_ `bool ExportDialogueScriptForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L27 _prototype_ `bool ExportDialogueScriptForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const TOptional<FString> DirectoryPath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L28 _prototype_ `bool ExportDialogueScriptForCulture(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const FString& CultureName, const TOptional<FString> FilePath = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
- L30 _prototype_ `bool ImportDialogueForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets);` (scope `LocalizationCommandletTasks`)
- L31 _prototype_ `bool ImportDialogueForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target);` (scope `LocalizationCommandletTasks`)
- L32 _prototype_ `bool ImportDialogueForCulture(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const FString& CultureName);` (scope `LocalizationCommandletTasks`)
- L34 _prototype_ `bool GenerateWordCountReportsForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets);` (scope `LocalizationCommandletTasks`)
- L35 _prototype_ `bool GenerateWordCountReportForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target);` (scope `LocalizationCommandletTasks`)
- L37 _prototype_ `bool CompileTextForTargets(const TSharedRef<SWindow>& ParentWindow, const TArray<ULocalizationTarget*>& Targets);` (scope `LocalizationCommandletTasks`)
- L38 _prototype_ `bool CompileTextForTarget(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target);` (scope `LocalizationCommandletTasks`)
- L39 _prototype_ `bool CompileTextForCulture(const TSharedRef<SWindow>& ParentWindow, ULocalizationTarget* const Target, const FString& CultureName);` (scope `LocalizationCommandletTasks`)
- L41 _prototype_ `bool ReportLoadedAudioAssets(const TArray<ULocalizationTarget*>& Targets, const TOptional<FString>& CultureName = TOptional<FString>());` (scope `LocalizationCommandletTasks`)
