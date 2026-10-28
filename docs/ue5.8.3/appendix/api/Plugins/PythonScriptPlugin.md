# Plugins / PythonScriptPlugin

- module root: `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin`
- headers: 54; symbols: 2298
- symbol kinds: class=81, delegate=10, enum=22, enumerator=111, externvar=58, function=216, macro=9, member=413, namespace=13, prototype=1194, struct=104, typedef=65, variable=2
- PrivateDependencyModuleNames: Analytics, AssetRegistry, AssetTools, BlueprintGraph, ContentBrowserData, ContentBrowserFileDataSource, DesktopPlatform, DeveloperSettings, EditorFramework, EditorSubsystem, InputCore, Json, KismetCompiler, LevelEditor, Networking, Projects, Python3, Slate, SlateCore, Sockets, SourceControl, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, ToolMenus

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Internal/PyGenUtilAccessor.h` (Internal)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace PyGenUtilAccessor`
- L24 _prototype_ `void ExtractFunctionParamsAsProperties(const UFunction* InFunc, TArray<const FProperty*>& OutInputParams, TArray<const FProperty*>& OutOutputParams);` (scope `PyGenUtilAccessor`)
- L26 _prototype_ `FString GetClassPythonName(const UClass* InClass);` (scope `PyGenUtilAccessor`)
- L27 _prototype_ `FString GetFunctionPythonName(const UFunction* InFunc);` (scope `PyGenUtilAccessor`)
- L28 _prototype_ `FString GetPropertyPythonName(const FProperty* InProp);` (scope `PyGenUtilAccessor`)
- L29 _prototype_ `FString GetPropertyPythonType(const FProperty* InProp);` (scope `PyGenUtilAccessor`)
- L31 _prototype_ `bool ShouldExportClass(const UClass* InClass);` (scope `PyGenUtilAccessor`)
- L32 _prototype_ `bool ShouldExportFunction(const UFunction* InFunc);` (scope `PyGenUtilAccessor`)
- L33 _prototype_ `bool ShouldExportProperty(const FProperty* InProp);` (scope `PyGenUtilAccessor`)
- L34 _prototype_ `bool ShouldExportEditorOnlyProperty(const FProperty* InProp);` (scope `PyGenUtilAccessor`)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/EditorUtilities/EditorPythonExecuter.h` (Private)


#### class `FEditorPythonExecuter`  
`class FEditorPythonExecuter`  
_L13-18_
- desc: Class that will execute a Python script once the editor is ready. This is not a commandlet because the editor feature needs to be enabled and running. The script may use the editor functionalities. This could not be replaced with "ExecCmds=". Again need to wait for some editor functionalities to be completely loaded. ie. EnterpriseTest ExecutePythonScript="c:\my_script.py"
- L16 _public prototype_ `static void OnStartupModule();`
- L17 _public prototype_ `static void OnShutdownModule();`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/EditorUtilities/EditorPythonScriptingLibrary.h` (Private)


#### class `UEditorPythonScriptingLibrary`  
`class UEditorPythonScriptingLibrary : public UBlueprintFunctionLibrary`  
_L13-43_
- reflection: `UCLASS(meta=(ScriptName="EditorPythonScripting"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Utility class for Python scripting functionality.
- L18 _private member_ `static bool bKeepPythonScriptAlive;`
- L31 _public prototype_ `static void SetKeepPythonScriptAlive(const bool bNewKeepAlive);` — `UFUNCTION(BlueprintCallable, DisplayName = "Set Keep Python Script Alive", Category = "Editor Scripting | Python")` — Sets the bKeepPythonScriptAlive flag. If this is false (default), it will close the editor during the next tick (when executing a Python script in the editor-environment using the UnrealEditor-Cmd commandline tool). If this is true, it will not close the editor by itself, and you will have to close it manually, either by setting this value to false again, or by calling a function like unreal.SystemLibrary.quit_editor(). @param bNewKeepAlive The new value of the bKeepPythonScriptAlive flag. @return The result of the users decision, true=Ok, false=Cancel, or false if running in unattended mode.
- L42 _public prototype_ `static bool GetKeepPythonScriptAlive();` — `UFUNCTION(BlueprintPure, DisplayName = "Get Keep Python Script Alive", Category = "Editor Scripting | Python")` — Returns the value of the bKeepPythonScriptAlive flag. If this is false (default), it will close the editor during the next tick (when executing a Python script in the editor-environment using the UnrealEditor-Cmd commandline tool). If this is true, it will not close the editor by itself, and you will have to close it manually, either by setting this value to false again, or by calling a function like unreal.SystemLibrary.quit_editor(). @return The current value of the bKeepPythonScriptAlive flag.

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/IncludePython.h` (Private)


#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_STATS_GROUP(TEXT("Python"), STATGROUP_Python, STATCAT_Adva`
- L17 _variable_ `DECLARE_STATS_GROUP(TEXT("Python"), STATGROUP_Python, STATCAT_Adva`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/K2Node_ExecutePythonScript.h` (Private)


#### class `UK2Node_ExecutePythonScript`  
`class UK2Node_ExecutePythonScript : public UK2Node_CallFunction`  
_L14-63_
- reflection: `UCLASS()`
- inherits: `UK2Node_CallFunction`
- L18 _private prototype_ `UK2Node_ExecutePythonScript();`
- L21 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _private prototype_ `virtual void PostReconstructNode() override;`
- L27 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L28 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L29 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L30 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L34 _private prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L35 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L36 _private prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L37 _private prototype_ `virtual bool IsActionFilteredOut(const class FBlueprintActionFilter& Filter) override;`
- L38 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L39 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L44 _protected function_ `virtual bool CanToggleNodePurity() const override`
- L49 _private prototype_ `void SynchronizeArgumentPinType(UEdGraphPin* Pin);` — Synchronize the type of the given argument pin with the type its connected to, or reset it to a wildcard pin if there's no connection
- L50 _private prototype_ `void SynchronizeArgumentPinTypeImpl(UEdGraphPin* Pin);`
- L53 _private prototype_ `UEdGraphPin* FindArgumentPin(const FName PinName, EEdGraphPinDirection PinDirection = EGPD_MAX);` — Try and find a named argument pin - this is the same as FindPin except it searches the array from the end as that's where the argument pins will be
- L54 _private prototype_ `UEdGraphPin* FindArgumentPinChecked(const FName PinName, EEdGraphPinDirection PinDirection = EGPD_MAX);`
- L58 _private member_ `TArray<FName> Inputs;` — `UPROPERTY(EditAnywhere, Category="Arguments")` — User-defined input pins
- L62 _private member_ `TArray<FName> Outputs;` — `UPROPERTY(EditAnywhere, Category="Arguments")` — User-defined output pins

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PipInstall.h` (Private)


#### class `FPipInstall`  
`class FPipInstall : public IPipInstall`  
_L20-110_
- inherits: `IPipInstall`
- desc: Static singleton implementation of IPipInstall
- L23 _public prototype_ `static FPipInstall& Get();`
- L26 _public prototype_ `virtual bool InitPipInstall() override;` — IPipInstall Interface Implementation
- L28 _public prototype_ `virtual bool LaunchPipInstall(bool RunAsync, TSharedPtr<ICmdProgressNotifier> CmdProgressNotifier = nullptr, FSimpleDelegate OnCompleted = FSimpleDelegate()) override;` — Run pip to install all missing dependencies for enabled plugins
- L30 _public prototype_ `virtual bool IsInstalling() override;` — Check if a background install is still running
- L33 _public prototype_ `virtual int32 GetNumPackagesToInstall() override;` — Get number of missing python packages to install
- L35 _public prototype_ `virtual bool GetPackageInstallList(TArray<FString>& PyPackages) override;` — Get list of python packages to install
- L38 _public prototype_ `virtual bool RegisterPipSitePackagesPath() const override;` — Register the site-packages path with embedded python env
- L42 _private prototype_ `FPipInstall();`
- L47 _private prototype_ `bool IsInitialized() const;`
- L48 _private prototype_ `bool IsBackgroundInstalling() const;`
- L50 _private prototype_ `void CheckRemoveOrphanedPackages(const FString& SitePackagesPath);`
- L51 _private prototype_ `void CheckInvalidPipEnv() const;`
- L53 _private prototype_ `FString WritePluginsListing(TArray<TSharedRef<IPlugin>>& OutPythonPlugins) const;`
- L54 _private prototype_ `FString WritePluginDependencies(const TArray<TSharedRef<IPlugin>>& PythonPlugins, TArray<FString>& OutRequirements, TArray<FString>& OutExtraUrls) const;`
- L56 _private prototype_ `bool SetupPipEnv(FFeedbackContext* Context, bool bForceRebuild = false) const;`
- L57 _private prototype_ `void RemoveParsedDependencyFiles() const;`
- L58 _private prototype_ `bool ParsePluginDependencies(const FString& MergedInRequirementsFile, FFeedbackContext* Context) const;`
- L59 _private prototype_ `bool LaunchPipInstallImpl(bool RunAsync, TSharedPtr<ICmdProgressNotifier> CmdProgressNotifier, FFeedbackContext* Context, FSimpleDelegate OnCompleted);`
- L61 _private prototype_ `FString GetPipInstallPath() const;`
- L62 _private prototype_ `FString GetPipSitePackagesPath() const;`
- L64 _private prototype_ `bool CacheDetectInstallDeps(FFeedbackContext* Context = nullptr);`
- L66 _private prototype_ `int32 CountCachedInstallRequirements();`
- L67 _private prototype_ `void ClearCachedInstallRequirements();`
- L68 _private prototype_ `bool UpdateCachedInstallRequirements();`
- L72 _private prototype_ `FString GetInputRequirementsPath() const;`
- L73 _private prototype_ `FString GetParsedRequirementsPath() const;`
- L74 _private prototype_ `FString GetExtraUrlsPath() const;`
- L76 _private prototype_ `void WriteSitePackagePthFile() const;`
- L77 _private prototype_ `bool SetupPipInstallUtils(FFeedbackContext* Context) const;`
- L78 _private prototype_ `bool CheckPipInstallUtils(FFeedbackContext* Context) const;`
- L80 _private prototype_ `FString ParseVenvVersion() const;`
- L81 _private prototype_ `FString SetupPipInstallCmd(const FString& ParsedReqsFile, const TArray<FString>& ExtraUrls) const;`
- L82 _private prototype_ `bool RunPipCmdAsync(const FString& PythonInterp, const FString& Cmd, FFeedbackContext* Context, TSharedPtr<ICmdProgressParser> CmdParser, FSimpleDelegate OnCompleted = FSimpleDelegate());`
- L83 _private prototype_ `bool RunPipCmdSync(const FString& PythonInterp, const FString& Cmd, FFeedbackContext* Context, TSharedPtr<ICmdProgressParser> CmdParser, FSimpleDelegate OnCompleted = FSimpleDelegate());`
- L85 _private prototype_ `static int32 RunPythonCmd(const FString& PythonInterp, const FString& Cmd, FFeedbackContext* Context, TSharedPtr<ICmdProgressParser> CmdParser = nullptr);`
- L87 _private prototype_ `static FString GetPythonScriptPluginPath();`
- L88 _private prototype_ `static FString GetVenvInterpreter(const FString& InstallPath);`
- L90 _private prototype_ `static bool CheckCompatibleArch(const TSharedPtr<FJsonObject>& JsontObject, const FString& ArchName);`
- L91 _private prototype_ `static bool CheckCompatiblePlatform(const TSharedPtr<FJsonObject>& JsonObject, const FString& PlatformName);`
- L93 _private member_ `TAtomic<bool> bInitialized;`
- L94 _private member_ `FCriticalSection GuardCacheCS;`
- L95 _private member_ `TSharedPtr<FLoggedSubprocessThread> BackgroundInstallRunnable;`
- L97 _private member_ `TArray<FString> CachedInstallRequirements;`
- L99 _private member_ `FString PipInstallPath;`
- L100 _private member_ `FString VenvInterp;`
- L102 _private member_ `static const FString PipInstallUtilsVer;`
- L103 _private member_ `static const FString PluginsListingFilename;`
- L104 _private member_ `static const FString PluginsSitePackageFilename;`
- L105 _private member_ `static const FString RequirementsInputFilename;`
- L106 _private member_ `static const FString ExtraUrlsFilename;`
- L107 _private member_ `static const FString ParsedRequirementsFilename;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PipInstallCmdNotifiers.h` (Private)


#### class `FSlowTaskNotifier`  
`class FSlowTaskNotifier : public ICmdProgressNotifier`  
_L13-28_
- inherits: `ICmdProgressNotifier`
- desc: Slowtask-based notifier for updating command progress (ICmdProgressNotifier)
- L16 _public prototype_ `FSlowTaskNotifier(float GuessSteps, const FText& Description);`
- L20 _public prototype_ `virtual void UpdateProgress(float UpdateWorkDone, float UpdateTotalWork, const FText& Status) override;` — ICmdProgressNotifier methods
- L21 _public prototype_ `virtual void Completed(bool bSuccess) override;`
- L24 _private member_ `TPimplPtr<FSlowTask> SlowTask;`
- L26 _private member_ `float TotalWork;`
- L27 _private member_ `float WorkDone;`

#### class `FAsyncTaskCmdNotifier`  
`class FAsyncTaskCmdNotifier : public ICmdProgressNotifier`  
_L32-46_
- inherits: `ICmdProgressNotifier`
- desc: Asyntask notifier for updating background install commands
- L35 _public prototype_ `FAsyncTaskCmdNotifier(float GuessSteps, const FText& Description);`
- L38 _public prototype_ `virtual void UpdateProgress(float UpdateWorkDone, float UpdateTotalWork, const FText& Status) override;` — ICmdProgressNotifier methods
- L39 _public prototype_ `virtual void Completed(bool bSuccess) override;`
- L42 _private member_ `TPimplPtr<FAsyncTaskNotification> AsyncNotifier;`
- L44 _private member_ `float TotalWork;`
- L45 _private member_ `float WorkDone;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PipInstallLauncher.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PipInstallLauncher`
- L9 _prototype_ `bool StartSync(IPipInstall& PipInstall, FSimpleDelegate OnCompleted = FSimpleDelegate());` (scope `PipInstallLauncher`)
- L10 _prototype_ `bool StartAsync(IPipInstall& PipInstall, FSimpleDelegate OnCompleted = FSimpleDelegate());` (scope `PipInstallLauncher`)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PipRunnable.h` (Private)


#### struct `ICmdProgressParser`  
`struct ICmdProgressParser`  
_L16-25_
- desc: Simple interface for parsing cmd output to update slowtask progress Similar to FFeedbackContextMarkup, but supports arbitrary line parsing
- L18 _public prototype_ `virtual ~ICmdProgressParser()= default;`
- L20 _public prototype_ `virtual float GetTotalWork() = 0;` — Get a total work estimate
- L21 _public prototype_ `virtual float GetWorkDone() = 0;`
- L23 _public prototype_ `virtual bool UpdateStatus(const FString& ChkLine) = 0;` — Parse line and update status/progress (return true to eat the output and not log)
- L24 _public prototype_ `virtual void NotifyCompleted(bool bSuccess) = 0;`

#### class `FPipProgressParser`  
`class FPipProgressParser : public ICmdProgressParser`  
_L28-48_
- inherits: `ICmdProgressParser`
- desc: Pip progress parser implemenation of ICmdProgressParser
- L31 _public prototype_ `FPipProgressParser(int GuessRequirementsCount, TSharedRef<ICmdProgressNotifier> InCmdNotifier);`
- L33 _public prototype_ `virtual float GetTotalWork() override;` — ICmdProgressParser methods
- L34 _public prototype_ `virtual float GetWorkDone() override;`
- L35 _public prototype_ `virtual bool UpdateStatus(const FString& ChkLine) override;`
- L36 _public prototype_ `virtual void NotifyCompleted(bool bSuccess) override;`
- L39 _private prototype_ `static bool CheckUpdateMatch(const FString& Line);`
- L40 _private prototype_ `static FString ReplaceUpdateStrs(const FString& Line);`
- L42 _private member_ `float RequirementsDone;`
- L43 _private member_ `float RequirementsCount;`
- L44 _private member_ `TSharedRef<ICmdProgressNotifier> CmdNotifier;`
- L46 _private member_ `static const TArray<FString> MatchStatusStrs;`
- L47 _private member_ `static const TMap<FString,FString> LogReplaceStrs;`

#### class `FLoggedSubprocessSync`  
`class FLoggedSubprocessSync`  
_L50-54_
- L53 _public prototype_ `static bool Run(int32& OutExitCode, const FString& URI, const FString& Params, FFeedbackContext* Context, TSharedPtr<ICmdProgressParser> CmdParser);`

#### class `FLoggedSubprocessThread`  
`class FLoggedSubprocessThread`  
_L58-78_
- L61 _public prototype_ `FLoggedSubprocessThread(const FString& URI, const FString& Params, FFeedbackContext* Context, TSharedPtr<ICmdProgressParser> CmdParser);`
- L63 _public function_ `bool Launch()`
- L64 _public function_ `bool IsRunning()`
- L66 _public function_ `FOnSubprocessThreadCompleted& OnCompleted()`
- L69 _private prototype_ `void ParseOutput(FString StdoutLine) const;`
- L70 _private prototype_ `void HandleCompleted(int32 ReturnCode) const;`
- L72 _private member_ `FOnSubprocessThreadCompleted OnProcCompleted;`
- L74 _private member_ `FMonitoredProcess Process;`
- L75 _private member_ `FFeedbackContext* Context;`
- L76 _private member_ `TSharedPtr<ICmdProgressParser> CmdParser;`
- L77 _private member_ `const bool bLogOutput;`

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSubprocessThreadCompleted, int32) class FLoggedSubprocessThread { public: FLoggedSubprocessThread(const FString& URI, const FString& Params, FFeedbackContext* Context, TSharedPtr<ICmdProgressParser> CmdParser); bool Launch() {return Process.Launch();} bool IsRunning() {return Process.Update();} FOnSubprocessThreadCompleted& OnCompleted() {return OnProcCompleted;} private: void ParseOutput(FString StdoutLine) const; void HandleCompleted(int32 ReturnCode) const; FOnSubprocessThreadCompleted OnProcCompleted; FMonitoredProcess Process; FFeedbackContext* Context; TSharedPtr<ICmdProgressParser> CmdParser; const bool bLogOutput; };` — Threaded subprocess runner (converted to wrapped FMonitoredProcess)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyConstant.h` (Private)


#### struct `FPyConstantDef`  
`struct FPyConstantDef`  
_L25-56_
- desc: Definition for a constant value This takes a pointer to some static or otherwise persistent data, along with a function used to convert this data into a Python object when needed Compared to a template, this avoids variance in the Python-type which would require a new Python-type to be registered for each instantiation Compared to storing a PyObject*, this avoids returning an instance that could be mutated and affect the constant value
- L28 _public member_ `const void* ConstantContext;` — A pointer to the constant context
- L31 _public member_ `PyConstantGetter ConstantGetter;` — Function pointer used to convert a constant data into a Python object
- L34 _public member_ `const char* ConstantName;` — The name of the constant value
- L37 _public member_ `const char* ConstantDoc;` — The doc string of the constant value (may be null)
- L40 _public prototype_ `static bool AddConstantToType(FPyConstantDef* InConstant, PyTypeObject* InType);` — Add a singular constant to the given type
- L43 _public prototype_ `static bool AddConstantsToType(FPyConstantDef* InConstants, PyTypeObject* InType);` — Add the given null-terminated table of constants to the given type
- L46 _public prototype_ `static bool AddConstantToModule(FPyConstantDef* InConstant, PyObject* InModule);` — Add a singular constant to the given module
- L49 _public prototype_ `static bool AddConstantsToModule(FPyConstantDef* InConstants, PyObject* InModule);` — Add the given null-terminated table of constants to the given module
- L52 _public prototype_ `static bool AddConstantToDict(FPyConstantDef* InConstant, PyObject* InDict);` — Add a singular constant to the given dict
- L55 _public prototype_ `static bool AddConstantsToDict(FPyConstantDef* InConstants, PyObject* InDict);` — Add the given null-terminated table of constants to the given dict

#### struct `FPyConstantDescrObject`  
`struct FPyConstantDescrObject`  
_L61-77_
- desc: Python object for the descriptor of an constant value
- L67 _public member_ `PyObject* ConstantName;` — Name of the constant being described
- L70 _public member_ `const FPyConstantDef* ConstantDef;` — Pointer to the definition of this constant
- L73 _public prototype_ `static FPyConstantDescrObject* New(const FPyConstantDef* InConstantDef);` — New an instance
- L76 _public prototype_ `static void Free(FPyConstantDescrObject* InSelf);` — Free this instance

#### Free symbols / members of external scopes

- L11 _externvar_ `extern PyTypeObject PyConstantDescrType;` — Python type for FPyConstantDescrObject
- L14 _prototype_ `bool InitializePyConstant();` — Initialize the PyConstant types
- L17 _typedef_ `typedef PyObject*(*PyConstantGetter)(PyTypeObject*, const void*);` — Function pointer used to convert a constant value pointer into a Python object

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyConversion.h` (Private)


#### enum `PyConversion::ESetErrorState`  
`enum class ESetErrorState : uint8`  
_L22-22_
- L22 _public enumerator_ `enum class ESetErrorState : uint8 { No, Yes }; FPyConversionResult Nativize(PyObject* PyObj, bool& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes); FPyConversionResult Pythonize(const bool Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes); FPyConversionResult Nativize(PyObject* PyObj, int8& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);`
- L22 _public enumerator_ `enum class ESetErrorState : uint8 { No, Yes }; FPyConversionResult Nativize(PyObject* PyObj, bool& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes); FPyConversionResult Pythonize(const bool Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes); FPyConversionResult Nativize(PyObject* PyObj, int8& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);`

#### struct `PyConversion::Internal::FTypeConv`  
`template <typename T, typename Spec = void> struct FTypeConv`  
_L120-133_
- desc: Dummy catch-all for type conversions that aren't yet implemented
- L122 _public function_ `static FPyConversionResult Nativize(PyObject* PyObj, T& OutVal, const ESetErrorState SetErrorState)`
- L128 _public function_ `static FPyConversionResult Pythonize(const T& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState)`

#### struct `PyConversion::Internal::FTypeConv`  
`template <typename T> struct FTypeConv<T, typename TEnableIf<TPointerIsConvertibleFromTo<typename TRemovePointer<T>::Type, UObject>::Value>::Type>`  
_L137-148_
- desc: Override the catch-all for UObject types
- L122 _public function_ `static FPyConversionResult Nativize(PyObject* PyObj, T& OutVal, const ESetErrorState SetErrorState)`
- L128 _public function_ `static FPyConversionResult Pythonize(const T& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState)`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace PyConversion`
- L25 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, bool& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — bool overload
- L26 _prototype_ `FPyConversionResult Pythonize(const bool Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L29 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, int8& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — int8 overload
- L30 _prototype_ `FPyConversionResult Pythonize(const int8 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L33 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, uint8& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — uint8 overload
- L34 _prototype_ `FPyConversionResult Pythonize(const uint8 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L37 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, int16& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — int16 overload
- L38 _prototype_ `FPyConversionResult Pythonize(const int16 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L41 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, uint16& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — uint16 overload
- L42 _prototype_ `FPyConversionResult Pythonize(const uint16 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L45 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, int32& OutVal, const ESetErrorState ErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — int32 overload
- L46 _prototype_ `FPyConversionResult Pythonize(const int32 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L49 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, uint32& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — uint32 overload
- L50 _prototype_ `FPyConversionResult Pythonize(const uint32 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L53 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, int64& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — int64 overload
- L54 _prototype_ `FPyConversionResult Pythonize(const int64 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L57 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, uint64& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — uint64 overload
- L58 _prototype_ `FPyConversionResult Pythonize(const uint64 Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L61 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, float& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — float overload
- L62 _prototype_ `FPyConversionResult Pythonize(const float Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L65 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, double& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — double overload
- L66 _prototype_ `FPyConversionResult Pythonize(const double Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L69 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, FString& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — FString overload
- L70 _prototype_ `FPyConversionResult Pythonize(const FString& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L73 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, FName& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — FName overload
- L74 _prototype_ `FPyConversionResult Pythonize(const FName& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L77 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, FText& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — FText overload
- L78 _prototype_ `FPyConversionResult Pythonize(const FText& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L81 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, FFieldPath& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — FFieldPath overload
- L82 _prototype_ `FPyConversionResult Pythonize(const FFieldPath& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L85 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, void*& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — void* overload
- L86 _prototype_ `FPyConversionResult Pythonize(void* Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L89 _prototype_ `FPyConversionResult Nativize(PyObject* PyObj, UObject*& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — UObject overload
- L90 _prototype_ `FPyConversionResult Pythonize(UObject* Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L93 _prototype_ `FPyConversionResult NativizeObject(PyObject* PyObj, UObject*& OutVal, UClass* ExpectedType, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for object types, including optional type checking
- L94 _prototype_ `FPyConversionResult PythonizeObject(UObject* Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L95 _prototype_ `PyObject* PythonizeObject(UObject* Val, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L98 _prototype_ `FPyConversionResult NativizeClass(PyObject* PyObj, UClass*& OutVal, UClass* ExpectedType, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for class types, including optional type checking
- L99 _prototype_ `FPyConversionResult PythonizeClass(UClass* Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L100 _prototype_ `PyObject* PythonizeClass(UClass* Val, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L103 _prototype_ `FPyConversionResult NativizeStruct(PyObject* PyObj, UScriptStruct*& OutVal, UScriptStruct* ExpectedType, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for struct types, including optional type checking
- L104 _prototype_ `FPyConversionResult PythonizeStruct(UScriptStruct* Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L105 _prototype_ `PyObject* PythonizeStruct(UScriptStruct* Val, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L108 _prototype_ `FPyConversionResult NativizeEnumEntry(PyObject* PyObj, const UEnum* EnumType, int64& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for enum entries
- L109 _prototype_ `FPyConversionResult PythonizeEnumEntry(const int64 Val, const UEnum* EnumType, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L110 _prototype_ `PyObject* PythonizeEnumEntry(const int64 Val, const UEnum* EnumType, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L112 _namespace_ `namespace Internal` (scope `PyConversion`)
- L115 _prototype_ `FPyConversionResult NativizeStructInstance(PyObject* PyObj, UScriptStruct* StructType, void* StructInstance, const ESetErrorState SetErrorState);` (scope `PyConversion::Internal`) — Internal version of NativizeStructInstance/PythonizeStructInstance that work on the type-erased data
- L116 _prototype_ `FPyConversionResult PythonizeStructInstance(UScriptStruct* StructType, const void* StructInstance, PyObject*& OutPyObj, const ESetErrorState SetErrorState);` (scope `PyConversion::Internal`)
- L156 _function_ `template <typename T> FPyConversionResult Nativize(PyObject* PyObj, T& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Generic version of Nativize used if there is no matching overload. Used to allow conversion from object and struct types that don't match a specific override (see FTypeConv).
- L166 _function_ `template <typename T> FPyConversionResult Pythonize(const T& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Generic version of Pythonize used if there is no matching overload. Used to allow conversion from object and struct types that don't match a specific override (see FTypeConv).
- L173 _function_ `template <typename T> PyObject* Pythonize(const T& Val, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Generic version of Pythonize that returns a PyObject rather than a bool
- L182 _function_ `template <typename T> FPyConversionResult NativizeStructInstance(PyObject* PyObj, T& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Conversion for known struct types
- L189 _function_ `template <typename T> FPyConversionResult PythonizeStructInstance(const T& Val, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Conversion for known struct types
- L196 _function_ `template <typename T> PyObject* PythonizeStructInstance(const T& Val, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Conversion for known struct types that returns a PyObject rather than a bool
- L205 _function_ `template <typename T> FPyConversionResult NativizeEnumEntry(PyObject* PyObj, const UEnum* EnumType, T& OutVal, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Conversion for known enum types
- L218 _function_ `template <typename T> FPyConversionResult PythonizeEnumEntry(const T& Val, const UEnum* EnumType, PyObject*& OutPyObj, const ESetErrorState SetErrorState = ESetErrorState::Yes)` (scope `PyConversion`) — Conversion for known enum types
- L225 _prototype_ `FPyConversionResult NativizeProperty(PyObject* PyObj, const FProperty* Prop, void* ValueAddr, const TConstArrayView<void*>& ArchetypeInstValueAddrs = TArray<void*>(), const FPropertyAccessChangeNotify* InChangeNotify = nullptr, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for property instances (including fixed arrays) - ValueAddr should point to the property data
- L226 _prototype_ `FPyConversionResult PythonizeProperty(const FProperty* Prop, const void* ValueAddr, PyObject*& OutPyObj, const EPyConversionMethod ConversionMethod = EPyConversionMethod::Copy, PyObject* OwnerPyObj = nullptr, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L229 _prototype_ `FPyConversionResult NativizeProperty_Direct(PyObject* PyObj, const FProperty* Prop, void* ValueAddr, const TConstArrayView<void*>& ArchetypeInstValueAddrs = TArray<void*>(), const FPropertyAccessChangeNotify* InChangeNotify = nullptr, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for single property instances - ValueAddr should point to the property data
- L230 _prototype_ `FPyConversionResult PythonizeProperty_Direct(const FProperty* Prop, const void* ValueAddr, PyObject*& OutPyObj, const EPyConversionMethod ConversionMethod = EPyConversionMethod::Copy, PyObject* OwnerPyObj = nullptr, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L233 _prototype_ `FPyConversionResult NativizeProperty_InContainer(PyObject* PyObj, const FProperty* Prop, void* BaseAddr, const int32 ArrayIndex, const TConstArrayView<void*>& ArchetypeInstBaseAddrs = TArray<void*>(), const FPropertyAccessChangeNotify* InChangeNotify = nullptr, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`) — Conversion for property instances within a structure (including fixed arrays) - BaseAddr should point to the structure data
- L234 _prototype_ `FPyConversionResult PythonizeProperty_InContainer(const FProperty* Prop, const void* BaseAddr, const int32 ArrayIndex, PyObject*& OutPyObj, const EPyConversionMethod ConversionMethod = EPyConversionMethod::Copy, PyObject* OwnerPyObj = nullptr, const ESetErrorState SetErrorState = ESetErrorState::Yes);` (scope `PyConversion`)
- L241 _prototype_ `void EmitPropertyChangeNotifications(const FPropertyAccessChangeNotify* InChangeNotify, const bool bIdenticalValue, const TFunctionRef<void()>& InDoChangeFunc);` (scope `PyConversion`) — Helper function used to emit property change notifications as value changes are made This function should be called when you know the value will actually change (or know you want to emit the notifications for it changing) and will do the pre-change notify, invoke the passed delegate to perform the change, then do the post-change notify

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyConversionMethod.h` (Private)


#### enum `EPyConversionMethod`  
`enum class EPyConversionMethod : uint8`  
_L10-18_
- L13 _public enumerator_ `Copy` — Copy the value
- L15 _public enumerator_ `Steal` — Steal the value (or fallback to Copy)
- L17 _public enumerator_ `Reference` — Reference the value from the given owner (or fallback to Copy)

#### Free symbols / members of external scopes

- L20 _function_ `FORCEINLINE void AssertValidPyConversionOwner(PyObject* InPyOwner, const EPyConversionMethod InMethod)`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyConversionResult.h` (Private)


#### enum `EPyConversionResultState`  
`enum class EPyConversionResultState : uint8`  
_L10-18_
- desc: States that can be applied to a Python conversion result
- L13 _public enumerator_ `Failure` — Conversion failed
- L15 _public enumerator_ `Success` — Conversion succeeded
- L17 _public enumerator_ `SuccessWithCoercion` — Conversion succeeded, but type coercion occurred

#### class `FPyConversionResult`  
`class FPyConversionResult`  
_L21-87_
- desc: The result of attempting a Python conversion
- L25 _public function_ `FPyConversionResult() : State(EPyConversionResultState::Failure)` — Default constructor
- L31 _public function_ `explicit FPyConversionResult(const EPyConversionResultState InState) : State(InState)` — Construct from a specific state
- L37 _public function_ `FORCEINLINE static FPyConversionResult Failure()` — Factory for a result set to the Failure state
- L43 _public function_ `FORCEINLINE static FPyConversionResult Success()` — Factory for a result set to the Success state
- L49 _public function_ `FORCEINLINE static FPyConversionResult SuccessWithCoercion()` — Factory for a result set to the SuccessWithCoercion state
- L55 _public function_ `explicit operator bool() const` — Is this result in a successful state?
- L61 _public function_ `bool Succeeded() const` — Is this result in a successful state?
- L67 _public function_ `bool Failed() const` — Is this result in a failure state?
- L73 _public function_ `EPyConversionResultState GetState() const` — Get the current result state
- L79 _public function_ `void SetState(const EPyConversionResultState InState)` — Set the result state
- L86 _private member_ `EPyConversionResultState State;` — Current state of this result

#### Free symbols / members of external scopes

- L90 _function_ `FORCEINLINE void SetOptionalPyConversionResult(const FPyConversionResult& InResult, FPyConversionResult* OutResult)` — Helper function to set the value of an optional conversion result

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyCore.h` (Private)


#### struct `FPyDelegateHandle`  
`struct FPyDelegateHandle : public TPyWrapperBasic<FDelegateHandle, FPyDelegateHandle>`  
_L65-74_
- inherits: `TPyWrapperBasic<FDelegateHandle,FPyDelegateHandle>`
- desc: Type for all Unreal exposed FDelegateHandle instances
- L67 _public typedef_ `typedef TPyWrapperBasic<FDelegateHandle, FPyDelegateHandle> Super;`
- L70 _public prototype_ `static FPyDelegateHandle* CreateInstance(const FDelegateHandle& InValue);` — Create and initialize a new wrapper instance from the given native instance
- L73 _public prototype_ `static FPyDelegateHandle* CastPyObject(PyObject* InPyObject);` — Cast the given Python object to this wrapped type (returns a new reference)

#### struct `FPyTickerDelegateHandle`  
`struct FPyTickerDelegateHandle : public TPyWrapperBasic<FTSTicker::FDelegateHandle, FPyTickerDelegateHandle>`  
_L77-86_
- inherits: `TPyWrapperBasic<FTSTicker::FDelegateHandle,FPyTickerDelegateHandle>`
- desc: Type for all Unreal exposed FTSTicker::FDelegateHandle instances
- L79 _public typedef_ `typedef TPyWrapperBasic<FTSTicker::FDelegateHandle, FPyTickerDelegateHandle> Super;`
- L82 _public prototype_ `static FPyTickerDelegateHandle* CreateInstance(const FTSTicker::FDelegateHandle& InValue);` — Create and initialize a new wrapper instance from the given native instance
- L85 _public prototype_ `static FPyTickerDelegateHandle* CastPyObject(PyObject* InPyObject);` — Cast the given Python object to this wrapped type (returns a new reference)

#### struct `FPyScopedSlowTask`  
`struct FPyScopedSlowTask`  
_L89-111_
- desc: Type used to create and managed a scoped slow task in Python
- L95 _public member_ `FSlowTask* SlowTask;` — Internal slow task instance (created lazily due to having a custom constructor)
- L98 _public prototype_ `static FPyScopedSlowTask* New(PyTypeObject* InType);` — New this instance (called via tp_new for Python, or directly in C++)
- L101 _public prototype_ `static void Free(FPyScopedSlowTask* InSelf);` — Free this instance (called via tp_dealloc for Python)
- L104 _public prototype_ `static int Init(FPyScopedSlowTask* InSelf, const float InAmountOfWork, const FText& InDefaultMessage, const bool InEnabled);` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L107 _public prototype_ `static void Deinit(FPyScopedSlowTask* InSelf);` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)
- L110 _public prototype_ `static bool ValidateInternalState(FPyScopedSlowTask* InSelf);` — Called to validate the internal state of this instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)

#### struct `TPyObjectIterator`  
`template <typename ObjectType, typename SelfType> struct TPyObjectIterator`  
_L115-226_
- desc: Type for iterating Unreal Object instances
- L121 _public member_ `FPersistentThreadSafeObjectIterator* Iterator;` — Internal iterator instance (created lazily due to having a custom constructor)
- L124 _public member_ `ObjectType* IteratorFilter;` — Optional value used when filtering the iterator
- L127 _public function_ `static SelfType* New(PyTypeObject* InType)` — New this instance (called via tp_new for Python, or directly in C++)
- L139 _public function_ `static void Free(SelfType* InSelf)` — Free this instance (called via tp_dealloc for Python)
- L146 _public function_ `static int Init(SelfType* InSelf, UClass* InClass, ObjectType* InIteratorFilter)` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L163 _public function_ `static void Deinit(SelfType* InSelf)` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)
- L172 _public function_ `static bool ValidateInternalState(SelfType* InSelf)` — Called to validate the internal state of this instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L184 _public function_ `static SelfType* GetIter(SelfType* InSelf)` — Get the iterator
- L191 _public function_ `static PyObject* IterNext(SelfType* InSelf)` — Return the current value (if any) and advance the iterator
- L215 _public function_ `static PyObject* GetIterValue(SelfType* InSelf)` — Convert the current iterator value to a Python object (internal: define this in a derived type to "override" GetIterValue behavior)
- L222 _public function_ `static bool PassesFilter(SelfType* InSelf)` — True if the current iterator value passes the filter (internal: define this in a derived type to "override" PassesFilter behavior)

#### struct `FPyObjectIterator`  
`struct FPyObjectIterator : public TPyObjectIterator<UObject, FPyObjectIterator>`  
_L229-232_
- inherits: `TPyObjectIterator<UObject,FPyObjectIterator>`
- desc: Type for iterating Unreal Object instances
- L231 _public typedef_ `typedef TPyObjectIterator<UObject, FPyObjectIterator> Super;`

#### struct `FPyClassIterator`  
`struct FPyClassIterator : public TPyObjectIterator<UClass, FPyClassIterator>`  
_L235-244_
- inherits: `TPyObjectIterator<UClass,FPyClassIterator>`
- desc: Type for iterating Unreal class types
- L237 _public typedef_ `typedef TPyObjectIterator<UClass, FPyClassIterator> Super;`
- L240 _public prototype_ `static bool PassesFilter(FPyClassIterator* InSelf);` — True if the current iterator value passes the filter
- L243 _public prototype_ `static UClass* ExtractFilter(FPyClassIterator* InSelf, PyObject* InPyFilter);` — Extract the filter from the given Python object

#### struct `FPyStructIterator`  
`struct FPyStructIterator : public TPyObjectIterator<UScriptStruct, FPyStructIterator>`  
_L247-256_
- inherits: `TPyObjectIterator<UScriptStruct,FPyStructIterator>`
- desc: Type for iterating Unreal struct types
- L249 _public typedef_ `typedef TPyObjectIterator<UScriptStruct, FPyStructIterator> Super;`
- L252 _public prototype_ `static bool PassesFilter(FPyStructIterator* InSelf);` — True if the current iterator value passes the filter
- L255 _public prototype_ `static UScriptStruct* ExtractFilter(FPyStructIterator* InSelf, PyObject* InPyFilter);` — Extract the filter from the given Python object

#### struct `FPyTypeIterator`  
`struct FPyTypeIterator : public TPyObjectIterator<UStruct, FPyTypeIterator>`  
_L259-271_
- inherits: `TPyObjectIterator<UStruct,FPyTypeIterator>`
- desc: Type for iterating Python types
- L261 _public typedef_ `typedef TPyObjectIterator<UStruct, FPyTypeIterator> Super;`
- L264 _public prototype_ `static PyObject* GetIterValue(FPyTypeIterator* InSelf);` — Convert the current iterator value to a Python object
- L267 _public prototype_ `static bool PassesFilter(FPyTypeIterator* InSelf);` — True if the current iterator value passes the filter
- L270 _public prototype_ `static UStruct* ExtractFilter(FPyTypeIterator* InSelf, PyObject* InPyFilter);` — Extract the filter from the given Python object

#### struct `FPyUValueDef`  
`struct FPyUValueDef`  
_L274-299_
- desc: Type used to define constant values from Python
- L280 _public member_ `PyObject* Value;` — Value of this definition
- L283 _public member_ `PyObject* MetaData;` — Dictionary of meta-data associated with this value
- L286 _public prototype_ `static FPyUValueDef* New(PyTypeObject* InType);` — New this instance (called via tp_new for Python, or directly in C++)
- L289 _public prototype_ `static void Free(FPyUValueDef* InSelf);` — Free this instance (called via tp_dealloc for Python)
- L292 _public prototype_ `static int Init(FPyUValueDef* InSelf, PyObject* InValue, PyObject* InMetaData);` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L295 _public prototype_ `static void Deinit(FPyUValueDef* InSelf);` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)
- L298 _public prototype_ `static void ApplyMetaData(FPyUValueDef* InSelf, const TFunctionRef<void(const FString&, const FString&)>& InPredicate);` — Apply the meta-data on this instance via the given predicate

#### struct `FPyFPropertyDef`  
`struct FPyFPropertyDef`  
_L302-333_
- desc: Type used to define FProperty fields from Python
- L308 _public member_ `PyObject* PropType;` — Type of this property
- L311 _public member_ `PyObject* MetaData;` — Dictionary of meta-data associated with this property
- L314 _public member_ `FString GetterFuncName;` — Getter function to use with this property
- L317 _public member_ `FString SetterFuncName;` — Setter function to use with this property
- L320 _public prototype_ `static FPyFPropertyDef* New(PyTypeObject* InType);` — New this instance (called via tp_new for Python, or directly in C++)
- L323 _public prototype_ `static void Free(FPyFPropertyDef* InSelf);` — Free this instance (called via tp_dealloc for Python)
- L326 _public prototype_ `static int Init(FPyFPropertyDef* InSelf, PyObject* InPropType, PyObject* InMetaData, FString InGetterFuncName, FString InSetterFuncName);` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L329 _public prototype_ `static void Deinit(FPyFPropertyDef* InSelf);` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)
- L332 _public prototype_ `static void ApplyMetaData(FPyFPropertyDef* InSelf, FProperty* InProp);` — Apply the meta-data on this instance to the given property

#### enum `EPyUFunctionDefFlags`  
`enum class EPyUFunctionDefFlags : uint8`  
_L336-345_
- desc: Flags used to define the attributes of a UFunction field from Python
- L338 _public enumerator_ `None = 0`
- L339 _public enumerator_ `Override = 1<<0`
- L340 _public enumerator_ `Static = 1<<1`
- L341 _public enumerator_ `Pure = 1<<2`
- L342 _public enumerator_ `Impure = 1<<3`
- L343 _public enumerator_ `Getter = 1<<4`
- L344 _public enumerator_ `Setter = 1<<5`

#### struct `FPyUFunctionDef`  
`struct FPyUFunctionDef`  
_L349-383_
- desc: Type used to define UFunction fields from Python
- L355 _public member_ `PyObject* Func;` — Python function to call
- L358 _public member_ `PyObject* FuncRetType;` — Return type of this function
- L361 _public member_ `PyObject* FuncParamTypes;` — List of types for each parameter of this function
- L364 _public member_ `PyObject* MetaData;` — Dictionary of meta-data associated with this function
- L367 _public member_ `EPyUFunctionDefFlags FuncFlags;` — Flags used to define this function
- L370 _public prototype_ `static FPyUFunctionDef* New(PyTypeObject* InType);` — New this instance (called via tp_new for Python, or directly in C++)
- L373 _public prototype_ `static void Free(FPyUFunctionDef* InSelf);` — Free this instance (called via tp_dealloc for Python)
- L376 _public prototype_ `static int Init(FPyUFunctionDef* InSelf, PyObject* InFunc, PyObject* InFuncRetType, PyObject* InFuncParamTypes, PyObject* InMetaData, EPyUFunctionDefFlags InFuncFlags);` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L379 _public prototype_ `static void Deinit(FPyUFunctionDef* InSelf);` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)
- L382 _public prototype_ `static void ApplyMetaData(FPyUFunctionDef* InSelf, UFunction* InFunc);` — Apply the meta-data on this instance to the given function

#### Free symbols / members of external scopes

- L22 _prototype_ `UObject* GetPythonTypeContainer();` — Get the object that Python created types should be outered to
- L32 _prototype_ `UObjectRedirector* CreatePythonTypeLegacyRedirector(const FString& ShortName, const FTopLevelAssetPath& GeneratedPathName);` — Create a redirector for a Python type, if needed. This is for backwards compatability, as all types were historically generated under GetPythonTypeContainer() using their short name. @note The caller must set DestinationObject to point at the generated type. @param ShortName			The short name of the Python generated type. @param GeneratedPathName The path name that the Python generated type will actually use.
- L35 _externvar_ `extern PyTypeObject PyDelegateHandleType;` — Python type for FPyDelegateHandle
- L38 _externvar_ `extern PyTypeObject PyTickerDelegateHandleType;` — Python type for FPyTickerDelegateHandle
- L41 _externvar_ `extern PyTypeObject PyScopedSlowTaskType;` — Python type for FPyScopedSlowTask
- L44 _externvar_ `extern PyTypeObject PyObjectIteratorType;` — Python type for FPyObjectIterator
- L47 _externvar_ `extern PyTypeObject PyClassIteratorType;` — Python type for FPyClassIterator
- L50 _externvar_ `extern PyTypeObject PyStructIteratorType;` — Python type for FPyStructIterator
- L53 _externvar_ `extern PyTypeObject PyTypeIteratorType;` — Python type for FPyTypeIterator
- L56 _externvar_ `extern PyTypeObject PyUValueDefType;` — Python type for FPyUValueDef
- L59 _externvar_ `extern PyTypeObject PyFPropertyDefType;` — Python type for FPyFPropertyDef
- L62 _externvar_ `extern PyTypeObject PyUFunctionDefType;` — Python type for FPyUFunctionDef
- L346 _prototype_ `ENUM_CLASS_FLAGS(EPyUFunctionDefFlags);`
- L385 _typedef_ `typedef TPyPtr<FPyDelegateHandle> FPyDelegateHandlePtr;`
- L386 _typedef_ `typedef TPyPtr<FPyTickerDelegateHandle> FPyTickerDelegateHandlePtr;`
- L387 _typedef_ `typedef TPyPtr<FPyScopedSlowTask> FPyScopedSlowTaskPtr;`
- L388 _typedef_ `typedef TPyPtr<FPyObjectIterator> FPyObjectIteratorPtr;`
- L389 _typedef_ `typedef TPyPtr<FPyClassIterator> FPyClassIteratorPtr;`
- L390 _typedef_ `typedef TPyPtr<FPyStructIterator> FPyStructIteratorPtr;`
- L391 _typedef_ `typedef TPyPtr<FPyTypeIterator> FPyTypeIteratorPtr;`
- L392 _typedef_ `typedef TPyPtr<FPyUValueDef> FPyUValueDefPtr;`
- L393 _typedef_ `typedef TPyPtr<FPyFPropertyDef> FPyFPropertyDefPtr;`
- L394 _typedef_ `typedef TPyPtr<FPyUFunctionDef> FPyUFunctionDefPtr;`
- L396 _namespace_ `namespace PyCore`
- L398 _prototype_ `void InitializeModule();` (scope `PyCore`)
- L399 _prototype_ `void ShutdownModule();` (scope `PyCore`)
- L401 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPythonLogCapture, EPythonLogOutputType, const TCHAR*);`
- L401 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPythonLogCapture, EPythonLogOutputType, const TCHAR*);` (scope `PyCore`)
- L402 _prototype_ `FPythonLogCapture& GetPythonLogCapture();` (scope `PyCore`)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyEditor.h` (Private)


#### struct `FPyScopedEditorTransaction`  
`struct FPyScopedEditorTransaction`  
_L17-39_
- desc: Type used to create and managed a scoped editor transaction in Python
- L23 _public member_ `FText Description;` — Description of the transaction
- L26 _public member_ `int32 PendingTransactionId;` — Id of the pending transaction, or INDEX_NONE if there is no pending transaction
- L29 _public prototype_ `static FPyScopedEditorTransaction* New(PyTypeObject* InType);` — New this instance (called via tp_new for Python, or directly in C++)
- L32 _public prototype_ `static void Free(FPyScopedEditorTransaction* InSelf);` — Free this instance (called via tp_dealloc for Python)
- L35 _public prototype_ `static int Init(FPyScopedEditorTransaction* InSelf, const FText& InDescription);` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L38 _public prototype_ `static void Deinit(FPyScopedEditorTransaction* InSelf);` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)

#### Free symbols / members of external scopes

- L14 _externvar_ `extern PyTypeObject PyScopedEditorTransactionType;` — Python type for FPyScopedEditorTransaction
- L41 _typedef_ `typedef TPyPtr<FPyScopedEditorTransaction> FPyScopedEditorTransactionPtr;`
- L43 _namespace_ `namespace PyEditor`
- L45 _prototype_ `void InitializeModule();` (scope `PyEditor`)
- L46 _prototype_ `void ShutdownModule();` (scope `PyEditor`)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyEngine.h` (Private)


#### struct `TPyActorIterator`  
`template <typename IteratorType, typename SelfType> struct TPyActorIterator`  
_L24-105_
- desc: Type for iterating Unreal actor instances
- L30 _public member_ `IteratorType* Iterator;` — Internal iterator instance (created lazily due to having a custom constructor)
- L33 _public function_ `static SelfType* New(PyTypeObject* InType)` — New this instance (called via tp_new for Python, or directly in C++)
- L44 _public function_ `static void Free(SelfType* InSelf)` — Free this instance (called via tp_dealloc for Python)
- L51 _public function_ `static int Init(SelfType* InSelf, UWorld* InWorld, UClass* InClass)` — Initialize this instance (called via tp_init for Python, or directly in C++)
- L61 _public function_ `static void Deinit(SelfType* InSelf)` — Deinitialize this instance (called via Init and Free to restore the instance to its New state)
- L68 _public function_ `static bool ValidateInternalState(SelfType* InSelf)` — Called to validate the internal state of this instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L80 _public function_ `static SelfType* GetIter(SelfType* InSelf)` — Get the iterator
- L87 _public function_ `static PyObject* IterNext(SelfType* InSelf)` — Return the current value (if any) and advance the iterator

#### struct `FPyActorIterator`  
`struct FPyActorIterator : public TPyActorIterator<FActorIterator, FPyActorIterator>`  
_L108-111_
- inherits: `TPyActorIterator<FActorIterator,FPyActorIterator>`
- desc: Type for iterating Unreal actor instances
- L110 _public typedef_ `typedef TPyActorIterator<FActorIterator, FPyActorIterator> Super;`

#### struct `FPySelectedActorIterator`  
`struct FPySelectedActorIterator : public TPyActorIterator<FSelectedActorIterator, FPySelectedActorIterator>`  
_L114-117_
- inherits: `TPyActorIterator<FSelectedActorIterator,FPySelectedActorIterator>`
- desc: Type for iterating selected Unreal actor instances
- L116 _public typedef_ `typedef TPyActorIterator<FSelectedActorIterator, FPySelectedActorIterator> Super;`

#### Free symbols / members of external scopes

- L17 _externvar_ `extern PyTypeObject PyActorIteratorType;` — Python type for FPyActorIterator
- L20 _externvar_ `extern PyTypeObject PySelectedActorIteratorType;` — Python type for FPySelectedActorIterator
- L119 _typedef_ `typedef TPyPtr<FPyActorIterator> FPyActorIteratorPtr;`
- L120 _typedef_ `typedef TPyPtr<FPySelectedActorIterator> FPySelectedActorIteratorPtr;`
- L122 _namespace_ `namespace PyEngine`
- L124 _prototype_ `void InitializeModule();` (scope `PyEngine`)
- L125 _prototype_ `void ShutdownModule();` (scope `PyEngine`)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyFileWriter.h` (Private)


#### class `FPyFileWriter`  
`class FPyFileWriter`  
_L13-54_
- desc: Util class to help format and write a Python file to disk
- L16 _public prototype_ `FPyFileWriter();`
- L19 _public prototype_ `void WriteLine(const TCHAR* InStr);` — Write a single line to the file - this is equivalent to calling WriteIndentation, Write, then WriteNewLine
- L22 _public prototype_ `void WriteLine(const FString& InStr);` — Write a single line to the file - this is equivalent to calling WriteIndentation, Write, then WriteNewLine
- L25 _public prototype_ `void WriteIndentation();` — Write the current indentation level to the file
- L28 _public prototype_ `void WriteNewLine();` — Write a new-line to the file
- L31 _public prototype_ `void Write(const TCHAR* InStr);` — Write the given string to the file
- L34 _public prototype_ `void Write(const FString& InStr);` — Write the given string to the file
- L37 _public prototype_ `void WriteDocString(const TCHAR* InDocString);` — Write a doc string to the file
- L40 _public prototype_ `void WriteDocString(const FString& InDocString);` — Write a doc string to the file
- L43 _public prototype_ `void IncreaseIndent(const int32 InCount = 1);` — Increase the indentation level
- L46 _public prototype_ `void DecreaseIndent(const int32 InCount = 1);` — Decrease the indentation level
- L49 _public prototype_ `bool SaveFile(const TCHAR* InFilename);` — Save the file to disk
- L52 _private member_ `int32 Indentation;`
- L53 _private member_ `FString FileContents;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyGIL.h` (Private)


#### class `FPyScopedGIL`  
`class FPyScopedGIL`  
_L11-33_
- desc: Utility to handle taking a releasing the Python GIL within a scope
- L15 _public function_ `FPyScopedGIL() : GILState(PyGILState_Ensure())` — Constructor - take the GIL
- L21 _public function_ `~FPyScopedGIL()` — Destructor - release the GIL
- L27 _public prototype_ `FPyScopedGIL(const FPyScopedGIL&) = delete;` — Non-copyable
- L28 _public prototype_ `FPyScopedGIL& operator=(const FPyScopedGIL&) = delete;`
- L32 _private member_ `PyGILState_STATE GILState;` — Internal GIL state

#### class `TPyAutoGILPtr`  
`template <typename TPythonType> class TPyAutoGILPtr`  
_L37-132_
- desc: Wrapper of a TPyPtr that can be safely copied/moved/destroyed by code where the GIL might not currently be held (eg, a lambda bound to a delegate)
- L40 _public prototype_ `TPyAutoGILPtr() = default;`
- L42 _public function_ `explicit TPyAutoGILPtr(TPyPtr<TPythonType>&& InPtr) : Ptr(MoveTemp(InPtr))`
- L47 _public function_ `TPyAutoGILPtr(const TPyAutoGILPtr& InOther)`
- L57 _public function_ `TPyAutoGILPtr(TPyAutoGILPtr&& InOther)`
- L67 _public function_ `~TPyAutoGILPtr()`
- L82 _public function_ `TPyAutoGILPtr& operator=(const TPyAutoGILPtr& InOther)`
- L101 _public function_ `TPyAutoGILPtr& operator=(TPyAutoGILPtr&& InOther)`
- L120 _public function_ `TPyPtr<TPythonType>& Get()`
- L125 _public function_ `const TPyPtr<TPythonType>& Get() const`
- L131 _private member_ `TPyPtr<TPythonType> Ptr;`

#### Free symbols / members of external scopes

- L134 _typedef_ `typedef TPyAutoGILPtr<PyObject> FPyAutoGILPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyGenUtil.h` (Private)


#### struct `FReportPythonGenerationIssue_Private`  
`struct FReportPythonGenerationIssue_Private`  
_L23-32_
- L25 _public function_ `static FORCEINLINE void ConditionalBreak(const ELogVerbosity::Type InVerbosity)`

#### struct `PyGenUtil::FCaseSensitiveStringMapFuncs`  
`template <typename ValueType> struct FCaseSensitiveStringMapFuncs : BaseKeyFuncs<ValueType, FString, false>`  
_L74-88_
- inherits: `BaseKeyFuncs<ValueType,FString,false>`
- desc: Case sensitive hashing function for TMap
- L76 _public function_ `static FORCEINLINE const FString& GetSetKey(const TPair<FString, ValueType>& Element)`
- L80 _public function_ `static FORCEINLINE bool Matches(const FString& A, const FString& B)`
- L84 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& Key)`

#### struct `PyGenUtil::FMultithreadedGenerationContext`  
`struct FMultithreadedGenerationContext`  
_L91-105_
- desc: Context used during multithreaded wrapper generation.
- L93 _public prototype_ `FMultithreadedGenerationContext();`
- L94 _public prototype_ `~FMultithreadedGenerationContext();`
- L96 _public prototype_ `static bool IsMultithreadedGenerationActive();`
- L97 _public prototype_ `static void EnqueueGameThreadTask(TFunction<void()>&& Task);`
- L98 _public prototype_ `static void ExecuteGameThreadTask(TFunctionRef<void()> Task);`
- L100 _public prototype_ `bool ExecuteGameThreadTasks();`
- L101 _public prototype_ `void ExecuteGameThreadTasksAndWait();`
- L104 _private prototype_ `static bool& GetMultithreadedGenerationRef();`

#### struct `PyGenUtil::FNativePythonModule`  
`struct FNativePythonModule`  
_L108-133_
- desc: Stores the information about a native Python module
- L110 _public function_ `FNativePythonModule() : PyModule(nullptr) , PyModuleMethods(nullptr) , PyModuleTypes()`
- L117 _public prototype_ `FNativePythonModule(FNativePythonModule&&) = default;`
- L118 _public prototype_ `FNativePythonModule(const FNativePythonModule&) = default;`
- L119 _public prototype_ `FNativePythonModule& operator=(FNativePythonModule&&) = default;`
- L120 _public prototype_ `FNativePythonModule& operator=(const FNativePythonModule&) = default;`
- L123 _public prototype_ `void AddType(PyTypeObject* InType);` — Add the given type to this module (the type must have had PyType_Ready called on it)
- L126 _public member_ `PyObject* PyModule;` — Pointer to the native Python module
- L129 _public member_ `PyMethodDef* PyModuleMethods;` — Pointer to a null-terminated array of methods exposed in this module (if any)
- L132 _public member_ `TArray<PyTypeObject*> PyModuleTypes;` — Array of types exposed in this module (if any)

#### struct `PyGenUtil::FGeneratedWrappedMethodParameter`  
`struct FGeneratedWrappedMethodParameter`  
_L136-156_
- desc: Stores the data needed by a runtime generated Python parameter
- L138 _public function_ `FGeneratedWrappedMethodParameter() : ParamProp(nullptr)`
- L143 _public prototype_ `FGeneratedWrappedMethodParameter(FGeneratedWrappedMethodParameter&&) = default;`
- L144 _public prototype_ `FGeneratedWrappedMethodParameter(const FGeneratedWrappedMethodParameter&) = default;`
- L145 _public prototype_ `FGeneratedWrappedMethodParameter& operator=(FGeneratedWrappedMethodParameter&&) = default;`
- L146 _public prototype_ `FGeneratedWrappedMethodParameter& operator=(const FGeneratedWrappedMethodParameter&) = default;`
- L149 _public member_ `FUTF8Buffer ParamName;` — The name of the parameter
- L152 _public member_ `const FProperty* ParamProp;` — The Unreal property for this parameter
- L155 _public member_ `TOptional<FString> ParamDefaultValue;` — The default Unreal ExportText value of this parameter; parameters with this set are considered optional

#### struct `PyGenUtil::FGeneratedWrappedFunction`  
`struct FGeneratedWrappedFunction`  
_L159-193_
- desc: Stores the data needed to call an Unreal function via Python
- L169 _public function_ `FGeneratedWrappedFunction() : Func(nullptr)`
- L174 _public prototype_ `FGeneratedWrappedFunction(FGeneratedWrappedFunction&&) = default;`
- L175 _public prototype_ `FGeneratedWrappedFunction(const FGeneratedWrappedFunction&) = default;`
- L176 _public prototype_ `FGeneratedWrappedFunction& operator=(FGeneratedWrappedFunction&&) = default;`
- L177 _public prototype_ `FGeneratedWrappedFunction& operator=(const FGeneratedWrappedFunction&) = default;`
- L180 _public prototype_ `void SetFunction(const UFunction* InFunc, const uint32 InSetFuncFlags = SFF_All);` — Set the function, optionally also calculating some data about it
- L183 _public member_ `TObjectPtr<const UFunction> Func;` — The Unreal function to call (static dispatch)
- L186 _public member_ `TArray<FGeneratedWrappedMethodParameter> InputParams;` — Array of input parameters associated with the function
- L189 _public member_ `TArray<FGeneratedWrappedMethodParameter> OutputParams;` — Array of output (including return) parameters associated with the function
- L192 _public member_ `TOptional<FString> DeprecationMessage;` — Set if this function is deprecated and using it should emit a deprecation warning

#### enum `PyGenUtil::FGeneratedWrappedFunction::ESetFunctionFlags`  
`enum ESetFunctionFlags`  
_L161-167_
- L163 _public enumerator_ `SFF_None = 0`
- L164 _public enumerator_ `SFF_CalculateDeprecationState = 1<<0`
- L165 _public enumerator_ `SFF_ExtractParameters = 1<<1`
- L166 _public enumerator_ `SFF_All = SFF_CalculateDeprecationState | SFF_ExtractParameters`

#### struct `PyGenUtil::FGeneratedWrappedMethod`  
`struct FGeneratedWrappedMethod`  
_L196-226_
- desc: Stores the data needed by a runtime generated Python method
- L198 _public function_ `FGeneratedWrappedMethod() : MethodCallback(nullptr) , MethodFlags(0)`
- L204 _public prototype_ `FGeneratedWrappedMethod(FGeneratedWrappedMethod&&) = default;`
- L205 _public prototype_ `FGeneratedWrappedMethod(const FGeneratedWrappedMethod&) = default;`
- L206 _public prototype_ `FGeneratedWrappedMethod& operator=(FGeneratedWrappedMethod&&) = default;`
- L207 _public prototype_ `FGeneratedWrappedMethod& operator=(const FGeneratedWrappedMethod&) = default;`
- L210 _public prototype_ `void ToPython(FPyMethodWithClosureDef& OutPyMethod) const;` — Convert this wrapper type to its Python type
- L213 _public member_ `FUTF8Buffer MethodName;` — The name of the method
- L216 _public member_ `FUTF8Buffer MethodDoc;` — The doc string of the method
- L219 _public member_ `FGeneratedWrappedFunction MethodFunc;` — The Unreal function for this method
- L222 _public member_ `PyCFunctionWithClosure MethodCallback;` — The C function this method should call
- L225 _public member_ `int MethodFlags;` — The METH_ flags for this method

#### struct `PyGenUtil::FGeneratedWrappedMethods`  
`struct FGeneratedWrappedMethods`  
_L229-245_
- desc: Stores the data needed for a set of runtime generated Python methods
- L231 _public prototype_ `FGeneratedWrappedMethods() = default;`
- L232 _public prototype_ `FGeneratedWrappedMethods(FGeneratedWrappedMethods&&) = default;`
- L233 _public prototype_ `FGeneratedWrappedMethods(const FGeneratedWrappedMethods&) = delete;`
- L234 _public prototype_ `FGeneratedWrappedMethods& operator=(FGeneratedWrappedMethods&&) = default;`
- L235 _public prototype_ `FGeneratedWrappedMethods& operator=(const FGeneratedWrappedMethods&) = delete;`
- L238 _public prototype_ `void Finalize();` — Called to ready the generated methods with Python
- L241 _public member_ `TArray<FGeneratedWrappedMethod> TypeMethods;` — Array of methods associated from the wrapped type
- L244 _public member_ `TArray<FPyMethodWithClosureDef> PyMethods;` — The Python methods that were generated from TypeMethods (in Finalize)

#### struct `PyGenUtil::FGeneratedWrappedDynamicMethod`  
`struct FGeneratedWrappedDynamicMethod : public FGeneratedWrappedMethod`  
_L248-261_
- inherits: `FGeneratedWrappedMethod`
- desc: Stores the data needed by a runtime generated Python method that is dynamically created and registered post-finalize of its owner type (for hoisting util functions onto structs)
- L250 _public prototype_ `FGeneratedWrappedDynamicMethod() = default;`
- L251 _public prototype_ `FGeneratedWrappedDynamicMethod(FGeneratedWrappedDynamicMethod&&) = default;`
- L252 _public prototype_ `FGeneratedWrappedDynamicMethod(const FGeneratedWrappedDynamicMethod&) = default;`
- L253 _public prototype_ `FGeneratedWrappedDynamicMethod& operator=(FGeneratedWrappedDynamicMethod&&) = default;`
- L254 _public prototype_ `FGeneratedWrappedDynamicMethod& operator=(const FGeneratedWrappedDynamicMethod&) = default;`
- L257 _public member_ `FGeneratedWrappedMethodParameter SelfParam;` — The 'self' parameter information (this parameter is set to the instance that calls the method)
- L260 _public member_ `FGeneratedWrappedMethodParameter SelfReturn;` — The 'self' return information (this value overwrites the instance that calls the method)

#### struct `PyGenUtil::FGeneratedWrappedDynamicMethodWithClosure`  
`struct FGeneratedWrappedDynamicMethodWithClosure : public FGeneratedWrappedDynamicMethod`  
_L264-277_
- inherits: `FGeneratedWrappedDynamicMethod`
- desc: Stores the data needed by a runtime generated Python method that is dynamically created and registered post-finalize of its owner struct type (for hoisting util functions onto other types)
- L266 _public prototype_ `FGeneratedWrappedDynamicMethodWithClosure() = default;`
- L267 _public prototype_ `FGeneratedWrappedDynamicMethodWithClosure(FGeneratedWrappedDynamicMethodWithClosure&&) = default;`
- L268 _public prototype_ `FGeneratedWrappedDynamicMethodWithClosure(const FGeneratedWrappedDynamicMethodWithClosure&) = delete;`
- L269 _public prototype_ `FGeneratedWrappedDynamicMethodWithClosure& operator=(FGeneratedWrappedDynamicMethodWithClosure&&) = default;`
- L270 _public prototype_ `FGeneratedWrappedDynamicMethodWithClosure& operator=(const FGeneratedWrappedDynamicMethodWithClosure&) = delete;`
- L273 _public prototype_ `void Finalize();` — Called to ready the generated method for Python
- L276 _public member_ `FPyMethodWithClosureDef PyMethod;` — Python method that was generated from this method

#### struct `PyGenUtil::FGeneratedWrappedDynamicMethodsMixinBase`  
`struct FGeneratedWrappedDynamicMethodsMixinBase`  
_L280-293_
- desc: Mixin used to add dynamic method support to a type (base for common non-templated functionality)
- L282 _public prototype_ `FGeneratedWrappedDynamicMethodsMixinBase() = default;`
- L283 _public prototype_ `FGeneratedWrappedDynamicMethodsMixinBase(FGeneratedWrappedDynamicMethodsMixinBase&&) = default;`
- L284 _public prototype_ `FGeneratedWrappedDynamicMethodsMixinBase(const FGeneratedWrappedDynamicMethodsMixinBase&) = delete;`
- L285 _public prototype_ `FGeneratedWrappedDynamicMethodsMixinBase& operator=(FGeneratedWrappedDynamicMethodsMixinBase&&) = default;`
- L286 _public prototype_ `FGeneratedWrappedDynamicMethodsMixinBase& operator=(const FGeneratedWrappedDynamicMethodsMixinBase&) = delete;`
- L289 _public prototype_ `void AddDynamicMethodImpl(FGeneratedWrappedDynamicMethod&& InDynamicMethod, PyTypeObject* InPyType);` — Called to add a dynamic method to the Python type (this should only be called post-finalize)
- L292 _public member_ `TArray<TSharedRef<FGeneratedWrappedDynamicMethodWithClosure>> DynamicMethods;` — Array of dynamic methods associated with this type (call AddDynamicMethod to add methods)

#### struct `PyGenUtil::TGeneratedWrappedDynamicMethodsMixin`  
`template <typename MixedIntoType> struct TGeneratedWrappedDynamicMethodsMixin : public FGeneratedWrappedDynamicMethodsMixinBase`  
_L297-310_
- inherits: `FGeneratedWrappedDynamicMethodsMixinBase`
- desc: Mixin used to add dynamic method support to a type
- L299 _public prototype_ `TGeneratedWrappedDynamicMethodsMixin() = default;`
- L300 _public prototype_ `TGeneratedWrappedDynamicMethodsMixin(TGeneratedWrappedDynamicMethodsMixin&&) = default;`
- L301 _public prototype_ `TGeneratedWrappedDynamicMethodsMixin(const TGeneratedWrappedDynamicMethodsMixin&) = delete;`
- L302 _public prototype_ `TGeneratedWrappedDynamicMethodsMixin& operator=(TGeneratedWrappedDynamicMethodsMixin&&) = default;`
- L303 _public prototype_ `TGeneratedWrappedDynamicMethodsMixin& operator=(const TGeneratedWrappedDynamicMethodsMixin&) = delete;`
- L306 _public function_ `void AddDynamicMethod(FGeneratedWrappedDynamicMethod&& InDynamicMethod)` — Called to add a dynamic method to the Python type (this should only be called post-finalize)

#### enum `PyGenUtil::EGeneratedWrappedOperatorType`  
`enum class EGeneratedWrappedOperatorType : uint8`  
_L313-344_
- desc: Operator types supported by Python
- L315 _public enumerator_ `Bool = 0` — bool
- L316 _public enumerator_ `Equal` — ==
- L317 _public enumerator_ `NotEqual` — !=
- L318 _public enumerator_ `Less` — <
- L319 _public enumerator_ `LessEqual` — <=
- L320 _public enumerator_ `Greater` — >
- L321 _public enumerator_ `GreaterEqual` — >=
- L322 _public enumerator_ `Add` — +
- L323 _public enumerator_ `InlineAdd` — +=
- L324 _public enumerator_ `Subtract` — -
- L325 _public enumerator_ `InlineSubtract` — -=
- L326 _public enumerator_ `Multiply` — *
- L327 _public enumerator_ `InlineMultiply` — *=
- L328 _public enumerator_ `Divide` — /
- L329 _public enumerator_ `InlineDivide` — /=
- L330 _public enumerator_ `Modulus` — %
- L331 _public enumerator_ `InlineModulus` — %=
- L332 _public enumerator_ `And` — &
- L333 _public enumerator_ `InlineAnd` — &=
- L334 _public enumerator_ `Or` — |
- L335 _public enumerator_ `InlineOr` — |=
- L336 _public enumerator_ `Xor` — ^
- L337 _public enumerator_ `InlineXor` — ^=
- L338 _public enumerator_ `RightShift` — >>
- L339 _public enumerator_ `InlineRightShift` — >>=
- L340 _public enumerator_ `LeftShift` — <<
- L341 _public enumerator_ `InlineLeftShift` — <<=
- L342 _public enumerator_ `Negated` — -obj prefix operator
- L343 _public enumerator_ `Num`

#### struct `PyGenUtil::FGeneratedWrappedOperatorSignature`  
`struct FGeneratedWrappedOperatorSignature`  
_L347-419_
- desc: Stores the signature definition of a runtime generated Python operator stack function
- L361 _public function_ `FGeneratedWrappedOperatorSignature() : OpType(EGeneratedWrappedOperatorType::Num) , OpTypeStr(TEXT("")) , PyFuncName(TEXT("")) , ReturnType(EType::None) , OtherType(EType::None)`
- L370 _public function_ `FGeneratedWrappedOperatorSignature(const EGeneratedWrappedOperatorType InOpType, const TCHAR* InOpTypeStr, const TCHAR* InPyFuncName, const EType InReturnType, const EType InOtherType) : OpType(InOpType) , OpTypeStr(InOpTypeStr) , PyFuncName(InPyFuncName) , ReturnType(InReturnType) , OtherType(InOtherType)`
- L382 _public prototype_ `static const FGeneratedWrappedOperatorSignature& OpTypeToSignature(const EGeneratedWrappedOperatorType InOpType);` — Given an operator type, return its signature
- L388 _public prototype_ `static bool StringToSignature(const TCHAR* InStr, FGeneratedWrappedOperatorSignature& OutSignature);` — Given a potential operator string, try and convert it to a known operator signature @return true if the conversion was a success, false otherwise
- L393 _public prototype_ `static bool ValidateParam(const FGeneratedWrappedMethodParameter& InParam, const EType InType, const UScriptStruct* InStructType, FString* OutError = nullptr);` — Validate that the given parameter is compatible with the expected type.
- L398 _public prototype_ `int32 GetInputParamCount() const;` — Get the number of input parameter that are expected by this operator.
- L403 _public prototype_ `int32 GetOutputParamCount() const;` — Get the number of output parameter that are expected by this operator.
- L406 _public member_ `EGeneratedWrappedOperatorType OpType;` — The operator enum value
- L409 _public member_ `const TCHAR* OpTypeStr;` — The string representation of this operator (see the comments on EGeneratedWrappedOperatorType)
- L412 _public member_ `const TCHAR* PyFuncName;` — The name of the function used in Python for this operator)
- L415 _public member_ `EType ReturnType;` — The type that is required by the return value of this operator (a struct return implies a 'self' return)
- L418 _public member_ `EType OtherType;` — The type that is required by the other value of this operator (for binary operators)

#### enum `PyGenUtil::FGeneratedWrappedOperatorSignature::EType`  
`enum class EType`  
_L349-359_
- L352 _public enumerator_ `None` — This operator type should be void
- L354 _public enumerator_ `Any` — This operator type can be anything
- L356 _public enumerator_ `Struct` — This operator type should be a struct (of the same type as 'self')
- L358 _public enumerator_ `Bool` — This operator type should be a bool

#### struct `PyGenUtil::FGeneratedWrappedOperatorFunction`  
`struct FGeneratedWrappedOperatorFunction`  
_L422-451_
- desc: Stores the data needed by a runtime generated Python operator stack function
- L424 _public prototype_ `FGeneratedWrappedOperatorFunction() = default;`
- L425 _public prototype_ `FGeneratedWrappedOperatorFunction(FGeneratedWrappedOperatorFunction&&) = default;`
- L426 _public prototype_ `FGeneratedWrappedOperatorFunction(const FGeneratedWrappedOperatorFunction&) = default;`
- L427 _public prototype_ `FGeneratedWrappedOperatorFunction& operator=(FGeneratedWrappedOperatorFunction&&) = default;`
- L428 _public prototype_ `FGeneratedWrappedOperatorFunction& operator=(const FGeneratedWrappedOperatorFunction&) = default;`
- L431 _public prototype_ `bool SetFunction(const UFunction* InFunc, const FGeneratedWrappedOperatorSignature& InSignature, FString* OutError = nullptr);` — Set the function, validating that it's compatible with the given signature
- L432 _public prototype_ `bool SetFunction(const FGeneratedWrappedFunction& InFuncDef, const FGeneratedWrappedOperatorSignature& InSignature, FString* OutError = nullptr);`
- L435 _public member_ `const UFunction* Func;` — The Unreal function to call (static dispatch)
- L438 _public member_ `FGeneratedWrappedMethodParameter SelfParam;` — The 'self' parameter information (this parameter is set to the instance that calls the function)
- L441 _public member_ `FGeneratedWrappedMethodParameter SelfReturn;` — The 'self' return information (this value overwrites the instance that calls the function)
- L444 _public member_ `FGeneratedWrappedMethodParameter OtherParam;` — The 'other' parameter information (for binary operators)
- L447 _public member_ `FGeneratedWrappedMethodParameter ReturnParam;` — The return parameter information
- L450 _public member_ `TArray<FGeneratedWrappedMethodParameter> AdditionalParams;` — Array of additional defaulted input parameters

#### struct `PyGenUtil::FGeneratedWrappedOperatorStack`  
`struct FGeneratedWrappedOperatorStack`  
_L454-464_
- desc: Stores the data needed by a runtime generated Python operator stack that is dynamically created and registered post-finalize of its owner type (for hoisting operators onto other types)
- L456 _public prototype_ `FGeneratedWrappedOperatorStack() = default;`
- L457 _public prototype_ `FGeneratedWrappedOperatorStack(FGeneratedWrappedOperatorStack&&) = default;`
- L458 _public prototype_ `FGeneratedWrappedOperatorStack(const FGeneratedWrappedOperatorStack&) = default;`
- L459 _public prototype_ `FGeneratedWrappedOperatorStack& operator=(FGeneratedWrappedOperatorStack&&) = default;`
- L460 _public prototype_ `FGeneratedWrappedOperatorStack& operator=(const FGeneratedWrappedOperatorStack&) = default;`
- L463 _public member_ `TArray<FGeneratedWrappedOperatorFunction> Funcs;` — Array of operator functions associated with this operator stack

#### struct `PyGenUtil::FGeneratedWrappedProperty`  
`struct FGeneratedWrappedProperty`  
_L467-494_
- desc: Stores the data needed to access an Unreal property via Python
- L476 _public function_ `FGeneratedWrappedProperty() : Prop(nullptr)`
- L481 _public prototype_ `FGeneratedWrappedProperty(FGeneratedWrappedProperty&&) = default;`
- L482 _public prototype_ `FGeneratedWrappedProperty(const FGeneratedWrappedProperty&) = default;`
- L483 _public prototype_ `FGeneratedWrappedProperty& operator=(FGeneratedWrappedProperty&&) = default;`
- L484 _public prototype_ `FGeneratedWrappedProperty& operator=(const FGeneratedWrappedProperty&) = default;`
- L487 _public prototype_ `void SetProperty(const FProperty* InProp, const uint32 InSetPropFlags = SPF_All);` — Set the property, optionally also calculating some data about it
- L490 _public member_ `const FProperty* Prop;` — The Unreal property to access
- L493 _public member_ `TOptional<FString> DeprecationMessage;` — Set if this property is deprecated and using it should emit a deprecation warning

#### enum `PyGenUtil::FGeneratedWrappedProperty::ESetPropertyFlags`  
`enum ESetPropertyFlags`  
_L469-474_
- L471 _public enumerator_ `SPF_None = 0`
- L472 _public enumerator_ `SPF_CalculateDeprecationState = 1<<0`
- L473 _public enumerator_ `SPF_All = SPF_CalculateDeprecationState`

#### struct `PyGenUtil::FGeneratedWrappedGetSet`  
`struct FGeneratedWrappedGetSet`  
_L497-533_
- desc: Stores the data needed by a runtime generated Python get/set
- L499 _public function_ `FGeneratedWrappedGetSet() : GetCallback(nullptr) , SetCallback(nullptr)`
- L505 _public prototype_ `FGeneratedWrappedGetSet(FGeneratedWrappedGetSet&&) = default;`
- L506 _public prototype_ `FGeneratedWrappedGetSet(const FGeneratedWrappedGetSet&) = default;`
- L507 _public prototype_ `FGeneratedWrappedGetSet& operator=(FGeneratedWrappedGetSet&&) = default;`
- L508 _public prototype_ `FGeneratedWrappedGetSet& operator=(const FGeneratedWrappedGetSet&) = default;`
- L511 _public prototype_ `void ToPython(PyGetSetDef& OutPyGetSet) const;` — Convert this wrapper type to its Python type
- L514 _public member_ `FUTF8Buffer GetSetName;` — The name of the get/set
- L517 _public member_ `FUTF8Buffer GetSetDoc;` — The doc string of the get/set
- L520 _public member_ `FGeneratedWrappedProperty Prop;` — The Unreal property for this get/set
- L523 _public member_ `FGeneratedWrappedFunction GetFunc;` — The Unreal function for the get (if any)
- L526 _public member_ `FGeneratedWrappedFunction SetFunc;` — The Unreal function for the set (if any)
- L529 _public member_ `getter GetCallback;` — The C function that should be called for get
- L532 _public member_ `setter SetCallback;` — The C function that should be called for set

#### struct `PyGenUtil::FGeneratedWrappedGetSets`  
`struct FGeneratedWrappedGetSets`  
_L536-552_
- desc: Stores the data needed for a set of runtime generated Python get/sets
- L538 _public prototype_ `FGeneratedWrappedGetSets() = default;`
- L539 _public prototype_ `FGeneratedWrappedGetSets(FGeneratedWrappedGetSets&&) = default;`
- L540 _public prototype_ `FGeneratedWrappedGetSets(const FGeneratedWrappedGetSets&) = delete;`
- L541 _public prototype_ `FGeneratedWrappedGetSets& operator=(FGeneratedWrappedGetSets&&) = default;`
- L542 _public prototype_ `FGeneratedWrappedGetSets& operator=(const FGeneratedWrappedGetSets&) = delete;`
- L545 _public prototype_ `void Finalize();` — Called to ready the generated get/sets with Python
- L548 _public member_ `TArray<FGeneratedWrappedGetSet> TypeGetSets;` — Array of get/sets from the wrapped type
- L551 _public member_ `TArray<PyGetSetDef> PyGetSets;` — The Python get/sets that were generated from TypeGetSets (in Finalize)

#### struct `PyGenUtil::FGeneratedWrappedConstant`  
`struct FGeneratedWrappedConstant`  
_L555-574_
- desc: Stores the data needed by a runtime generated Python constant
- L557 _public prototype_ `FGeneratedWrappedConstant() = default;`
- L558 _public prototype_ `FGeneratedWrappedConstant(FGeneratedWrappedConstant&&) = default;`
- L559 _public prototype_ `FGeneratedWrappedConstant(const FGeneratedWrappedConstant&) = default;`
- L560 _public prototype_ `FGeneratedWrappedConstant& operator=(FGeneratedWrappedConstant&&) = default;`
- L561 _public prototype_ `FGeneratedWrappedConstant& operator=(const FGeneratedWrappedConstant&) = default;`
- L564 _public prototype_ `void ToPython(FPyConstantDef& OutPyConstant) const;` — Convert this wrapper type to its Python type
- L567 _public member_ `FUTF8Buffer ConstantName;` — The name of the constant
- L570 _public member_ `FUTF8Buffer ConstantDoc;` — The doc string of the constant
- L573 _public member_ `FGeneratedWrappedFunction ConstantFunc;` — The Unreal function for getting the constant data

#### struct `PyGenUtil::FGeneratedWrappedConstants`  
`struct FGeneratedWrappedConstants`  
_L577-593_
- desc: Stores the data needed for a set of runtime generated Python constants
- L579 _public prototype_ `FGeneratedWrappedConstants() = default;`
- L580 _public prototype_ `FGeneratedWrappedConstants(FGeneratedWrappedConstants&&) = default;`
- L581 _public prototype_ `FGeneratedWrappedConstants(const FGeneratedWrappedConstants&) = delete;`
- L582 _public prototype_ `FGeneratedWrappedConstants& operator=(FGeneratedWrappedConstants&&) = default;`
- L583 _public prototype_ `FGeneratedWrappedConstants& operator=(const FGeneratedWrappedConstants&) = delete;`
- L586 _public prototype_ `void Finalize();` — Called to ready the generated constants with Python
- L589 _public member_ `TArray<FGeneratedWrappedConstant> TypeConstants;` — Array of constants from the wrapped type
- L592 _public member_ `TArray<FPyConstantDef> PyConstants;` — The Python constants that were generated from TypeConstants (in Finalize)

#### struct `PyGenUtil::FGeneratedWrappedDynamicConstantWithClosure`  
`struct FGeneratedWrappedDynamicConstantWithClosure : public FGeneratedWrappedConstant`  
_L596-609_
- inherits: `FGeneratedWrappedConstant`
- desc: Stores the data needed by a runtime generated Python constant that is dynamically created and registered post-finalize of its owner type (for hoisting constant functions onto other types)
- L598 _public prototype_ `FGeneratedWrappedDynamicConstantWithClosure() = default;`
- L599 _public prototype_ `FGeneratedWrappedDynamicConstantWithClosure(FGeneratedWrappedDynamicConstantWithClosure&&) = default;`
- L600 _public prototype_ `FGeneratedWrappedDynamicConstantWithClosure(const FGeneratedWrappedDynamicConstantWithClosure&) = delete;`
- L601 _public prototype_ `FGeneratedWrappedDynamicConstantWithClosure& operator=(FGeneratedWrappedDynamicConstantWithClosure&&) = default;`
- L602 _public prototype_ `FGeneratedWrappedDynamicConstantWithClosure& operator=(const FGeneratedWrappedDynamicConstantWithClosure&) = delete;`
- L605 _public prototype_ `void Finalize();` — Called to ready the generated constant for Python
- L608 _public member_ `FPyConstantDef PyConstant;` — Python constant that was generated from this data

#### struct `PyGenUtil::FGeneratedWrappedDynamicConstantsMixinBase`  
`struct FGeneratedWrappedDynamicConstantsMixinBase`  
_L612-625_
- desc: Mixin used to add dynamic constant support to a type (base for common non-templated functionality)
- L614 _public prototype_ `FGeneratedWrappedDynamicConstantsMixinBase() = default;`
- L615 _public prototype_ `FGeneratedWrappedDynamicConstantsMixinBase(FGeneratedWrappedDynamicConstantsMixinBase&&) = default;`
- L616 _public prototype_ `FGeneratedWrappedDynamicConstantsMixinBase(const FGeneratedWrappedDynamicConstantsMixinBase&) = delete;`
- L617 _public prototype_ `FGeneratedWrappedDynamicConstantsMixinBase& operator=(FGeneratedWrappedDynamicConstantsMixinBase&&) = default;`
- L618 _public prototype_ `FGeneratedWrappedDynamicConstantsMixinBase& operator=(const FGeneratedWrappedDynamicConstantsMixinBase&) = delete;`
- L621 _public prototype_ `void AddDynamicConstantImpl(FGeneratedWrappedConstant&& InDynamicConstant, PyTypeObject* InPyType);` — Called to add a dynamic constant to the Python type (this should only be called post-finalize)
- L624 _public member_ `TArray<TSharedRef<FGeneratedWrappedDynamicConstantWithClosure>> DynamicConstants;` — Array of dynamic constants associated with this type (call AddDynamicConstant to add constants)

#### struct `PyGenUtil::TGeneratedWrappedDynamicConstantsMixin`  
`template <typename MixedIntoType> struct TGeneratedWrappedDynamicConstantsMixin : public FGeneratedWrappedDynamicConstantsMixinBase`  
_L629-642_
- inherits: `FGeneratedWrappedDynamicConstantsMixinBase`
- desc: Mixin used to add dynamic constant support to a type
- L631 _public prototype_ `TGeneratedWrappedDynamicConstantsMixin() = default;`
- L632 _public prototype_ `TGeneratedWrappedDynamicConstantsMixin(TGeneratedWrappedDynamicConstantsMixin&&) = default;`
- L633 _public prototype_ `TGeneratedWrappedDynamicConstantsMixin(const TGeneratedWrappedDynamicConstantsMixin&) = delete;`
- L634 _public prototype_ `TGeneratedWrappedDynamicConstantsMixin& operator=(TGeneratedWrappedDynamicConstantsMixin&&) = default;`
- L635 _public prototype_ `TGeneratedWrappedDynamicConstantsMixin& operator=(const TGeneratedWrappedDynamicConstantsMixin&) = delete;`
- L638 _public function_ `void AddDynamicConstant(FGeneratedWrappedConstant&& InDynamicConstant)` — Called to add a dynamic constant to the Python type (this should only be called post-finalize)

#### struct `PyGenUtil::FGeneratedWrappedPropertyDoc`  
`struct FGeneratedWrappedPropertyDoc`  
_L645-671_
- desc: Stores the data needed to generate a Python doc string for editor exposed properties
- L647 _public prototype_ `explicit FGeneratedWrappedPropertyDoc(const FProperty* InProp);`
- L649 _public prototype_ `FGeneratedWrappedPropertyDoc(FGeneratedWrappedPropertyDoc&&) = default;`
- L650 _public prototype_ `FGeneratedWrappedPropertyDoc(const FGeneratedWrappedPropertyDoc&) = default;`
- L651 _public prototype_ `FGeneratedWrappedPropertyDoc& operator=(FGeneratedWrappedPropertyDoc&&) = default;`
- L652 _public prototype_ `FGeneratedWrappedPropertyDoc& operator=(const FGeneratedWrappedPropertyDoc&) = default;`
- L655 _public prototype_ `static bool SortPredicate(const FGeneratedWrappedPropertyDoc& InOne, const FGeneratedWrappedPropertyDoc& InTwo);` — Util function to sort an array of doc structs based on the Pythonized property name
- L658 _public prototype_ `static FString BuildDocString(const TArray<FGeneratedWrappedPropertyDoc>& InDocs);` — Util function to convert an array of doc structs into a combined doc string (the array should have been sorted before calling this)
- L661 _public prototype_ `static void AppendDocString(const TArray<FGeneratedWrappedPropertyDoc>& InDocs, FString& OutStr);` — Util function to convert an array of doc structs into a combined doc string (the array should have been sorted before calling this)
- L664 _public member_ `FString PythonPropName;` — Pythonized name of the property
- L667 _public member_ `FString DocString;` — Pythonized doc string of the property
- L670 _public member_ `FString EditorDocString;` — Pythonized editor doc string of the property

#### struct `PyGenUtil::FGeneratedWrappedFieldTracker`  
`struct FGeneratedWrappedFieldTracker`  
_L674-690_
- desc: Utility for tracking and logging field conflicts when exported to Python
- L676 _public prototype_ `FGeneratedWrappedFieldTracker() = default;`
- L677 _public prototype_ `FGeneratedWrappedFieldTracker(FGeneratedWrappedFieldTracker&&) = default;`
- L678 _public prototype_ `FGeneratedWrappedFieldTracker(const FGeneratedWrappedFieldTracker&) = default;`
- L679 _public prototype_ `FGeneratedWrappedFieldTracker& operator=(FGeneratedWrappedFieldTracker&&) = default;`
- L680 _public prototype_ `FGeneratedWrappedFieldTracker& operator=(const FGeneratedWrappedFieldTracker&) = default;`
- L683 _public prototype_ `void RegisterPythonFieldName(const FString& InPythonFieldName, const FFieldVariant& InUnrealField);` — Register a Python field name, and detect if a name conflict has occurred
- L686 _public typedef_ `typedef TMap<FString, TWeakObjectPtr<const UField>, FDefaultSetAllocator, FCaseSensitiveStringMapFuncs<TWeakObjectPtr<const UField>>> FCaseSensitiveStringToFieldMap;` — Map from the Python wrapped field name to the Unreal field it was generated from (for conflict detection)
- L687 _public typedef_ `typedef TMap<FString, TWeakFieldPtr<const FField>, FDefaultSetAllocator, FCaseSensitiveStringMapFuncs<TWeakFieldPtr<const FField>>> FCaseSensitiveStringToFFieldMap;`
- L688 _public member_ `FCaseSensitiveStringToFieldMap PythonWrappedFieldNameToUnrealField;`
- L689 _public member_ `FCaseSensitiveStringToFFieldMap PythonWrappedFieldNameToFField;`

#### struct `PyGenUtil::FGeneratedWrappedType`  
`struct FGeneratedWrappedType`  
_L693-784_
- desc: Stores the minimal data needed by a runtime generated Python type
- L702 _public function_ `FGeneratedWrappedType()`
- L707 _public prototype_ `virtual ~FGeneratedWrappedType() = default;`
- L709 _public prototype_ `FGeneratedWrappedType(FGeneratedWrappedType&&) = delete;`
- L710 _public prototype_ `FGeneratedWrappedType(const FGeneratedWrappedType&) = delete;`
- L711 _public prototype_ `FGeneratedWrappedType& operator=(FGeneratedWrappedType&&) = delete;`
- L712 _public prototype_ `FGeneratedWrappedType& operator=(const FGeneratedWrappedType&) = delete;`
- L715 _public prototype_ `bool Finalize();` — Called to ready the generated type with Python
- L718 _public prototype_ `void Reset();` — Called to reset this type back to its clean state
- L721 _public prototype_ `virtual void Finalize_PreReady();` — Internal version of Finalize, called before readying the type with Python
- L724 _public prototype_ `virtual void Finalize_PostReady();` — Internal version of Finalize, called after readying the type with Python
- L727 _public prototype_ `virtual void Reset_CleansePyType();` — Internal version of Reset, called to remove data added to the Python type
- L730 _public prototype_ `virtual void Reset_CleanseSelf();` — Internal version of Reset, called to reset the data on this type
- L733 _public member_ `FUTF8Buffer TypeName;` — The name of the type
- L736 _public member_ `FUTF8Buffer TypeDoc;` — The doc string of the type
- L739 _public member_ `TSharedPtr<FPyWrapperBaseMetaData> MetaData;` — The meta-data associated with this type
- L742 _public member_ `PyTypeObject PyType;` — The Python type that was generated
- L745 _public member_ `EFinalizedState FinalizedState = EFinalizedState::Initial;` — What is the current finalization state of this generated type?
- L780 _public member_ `} Lock;`
- L783 _public member_ `std::atomic<bool> bIsReadyForUse;` — Used to atomically publish readyness of this object

#### enum `PyGenUtil::FGeneratedWrappedType::EFinalizedState`  
`enum class EFinalizedState : uint8`  
_L695-700_
- L697 _public enumerator_ `Initial`
- L698 _public enumerator_ `Reset`
- L699 _public enumerator_ `Finalized`

#### struct `PyGenUtil::FGeneratedWrappedType::FDebuggableMutex`  
`struct FDebuggableMutex`  
_L748-780_
- desc: Per-object lock used during the construction phase
- L755 _public function_ `static int32& GetThreadLocal()` — We should never go above 1 lock per stack because going recursive on those lock will create a very deadlock prone situation when run under multiple thread that will be hard to repro depending on the order in which things are recursed into.
- L761 _public member_ `UE::FMutex Mutex;`
- L762 _public member_ `uint32 OwnerThreadId = 0;`
- L764 _public function_ `void Lock()`
- L773 _public function_ `void Unlock()`

#### struct `PyGenUtil::FGeneratedWrappedStructType`  
`struct FGeneratedWrappedStructType : public FGeneratedWrappedType, public TGeneratedWrappedDynamicMethodsMixin<FGeneratedWrappedStructType>, public TGeneratedWrappedDynamicConstantsMixin<FGeneratedWrappedStructType>`  
_L787-806_
- inherits: `FGeneratedWrappedType,TGeneratedWrappedDynamicMethodsMixin<FGeneratedWrappedStructType>,TGeneratedWrappedDynamicConstantsMixin<FGeneratedWrappedStructType>`
- desc: Stores the data needed by a runtime generated Python struct type
- L789 _public prototype_ `FGeneratedWrappedStructType() = default;`
- L790 _public prototype_ `FGeneratedWrappedStructType(FGeneratedWrappedStructType&&) = delete;`
- L791 _public prototype_ `FGeneratedWrappedStructType(const FGeneratedWrappedStructType&) = delete;`
- L792 _public prototype_ `FGeneratedWrappedStructType& operator=(FGeneratedWrappedStructType&&) = delete;`
- L793 _public prototype_ `FGeneratedWrappedStructType& operator=(const FGeneratedWrappedStructType&) = delete;`
- L796 _public prototype_ `virtual void Finalize_PreReady() override;` — Internal version of Finalize, called before readying the type with Python
- L799 _public member_ `FGeneratedWrappedGetSets GetSets;` — Get/sets associated with this type
- L802 _public member_ `TArray<FGeneratedWrappedPropertyDoc> PropertyDocs;` — The doc string data for the properties associated with this type
- L805 _public member_ `FGeneratedWrappedFieldTracker FieldTracker;` — Tracks and logs field conflicts on this type

#### struct `PyGenUtil::FGeneratedWrappedClassType`  
`struct FGeneratedWrappedClassType : public FGeneratedWrappedType, public TGeneratedWrappedDynamicMethodsMixin<FGeneratedWrappedStructType>, public TGeneratedWrappedDynamicConstantsMixin<FGeneratedWrappedStructType>`  
_L809-837_
- inherits: `FGeneratedWrappedType,TGeneratedWrappedDynamicMethodsMixin<FGeneratedWrappedStructType>,TGeneratedWrappedDynamicConstantsMixin<FGeneratedWrappedStructType>`
- desc: Stores the data needed by a runtime generated Python class type
- L811 _public prototype_ `FGeneratedWrappedClassType() = default;`
- L812 _public prototype_ `FGeneratedWrappedClassType(FGeneratedWrappedClassType&&) = delete;`
- L813 _public prototype_ `FGeneratedWrappedClassType(const FGeneratedWrappedClassType&) = delete;`
- L814 _public prototype_ `FGeneratedWrappedClassType& operator=(FGeneratedWrappedClassType&&) = delete;`
- L815 _public prototype_ `FGeneratedWrappedClassType& operator=(const FGeneratedWrappedClassType&) = delete;`
- L818 _public prototype_ `virtual void Finalize_PreReady() override;` — Internal version of Finalize, called before readying the type with Python
- L821 _public prototype_ `virtual void Finalize_PostReady() override;` — Internal version of Finalize, called after readying the type with Python
- L824 _public member_ `FGeneratedWrappedMethods Methods;` — Methods associated with this type
- L827 _public member_ `FGeneratedWrappedGetSets GetSets;` — Get/sets associated with this type
- L830 _public member_ `FGeneratedWrappedConstants Constants;` — Constants associated with this type
- L833 _public member_ `TArray<FGeneratedWrappedPropertyDoc> PropertyDocs;` — The doc string data for the properties associated with this type
- L836 _public member_ `FGeneratedWrappedFieldTracker FieldTracker;` — Tracks and logs field conflicts on this type

#### struct `PyGenUtil::FGeneratedWrappedEnumEntry`  
`struct FGeneratedWrappedEnumEntry`  
_L840-859_
- desc: Stores the data needed by a runtime generated Python enum entry
- L842 _public prototype_ `FGeneratedWrappedEnumEntry() = default;`
- L843 _public prototype_ `FGeneratedWrappedEnumEntry(FGeneratedWrappedEnumEntry&&) = delete;`
- L844 _public prototype_ `FGeneratedWrappedEnumEntry(const FGeneratedWrappedEnumEntry&) = default;`
- L845 _public prototype_ `FGeneratedWrappedEnumEntry& operator=(FGeneratedWrappedEnumEntry&&) = delete;`
- L846 _public prototype_ `FGeneratedWrappedEnumEntry& operator=(const FGeneratedWrappedEnumEntry&) = default;`
- L849 _public member_ `TArray<FUTF8Buffer> EntryDeprecatedAliases;` — Array of deprecated aliases for this enum entry, if any
- L852 _public member_ `FUTF8Buffer EntryName;` — The name of the entry
- L855 _public member_ `FUTF8Buffer EntryDoc;` — The doc string of the entry
- L858 _public member_ `int64 EntryValue = 0;` — The value of the entry

#### struct `PyGenUtil::FGeneratedWrappedEnumType`  
`struct FGeneratedWrappedEnumType : public FGeneratedWrappedType`  
_L862-884_
- inherits: `FGeneratedWrappedType`
- desc: Stores the data needed by a runtime generated Python enum type
- L864 _public prototype_ `FGeneratedWrappedEnumType() = default;`
- L865 _public prototype_ `FGeneratedWrappedEnumType(FGeneratedWrappedEnumType&&) = delete;`
- L866 _public prototype_ `FGeneratedWrappedEnumType(const FGeneratedWrappedEnumType&) = delete;`
- L867 _public prototype_ `FGeneratedWrappedEnumType& operator=(FGeneratedWrappedEnumType&&) = delete;`
- L868 _public prototype_ `FGeneratedWrappedEnumType& operator=(const FGeneratedWrappedEnumType&) = delete;`
- L871 _public prototype_ `virtual void Finalize_PostReady() override;` — Internal version of Finalize, called after readying the type with Python
- L874 _public prototype_ `virtual void Reset_CleansePyType() override;` — Internal version of Reset, called to remove data added to the Python type
- L877 _public prototype_ `virtual void Reset_CleanseSelf() override;` — Internal version of Reset, called to reset the data on this type
- L880 _public prototype_ `void ExtractEnumEntries(const UEnum* InEnum);` — Called to extract the enum entries array from the given enum
- L883 _public member_ `TArray<FGeneratedWrappedEnumEntry> EnumEntries;` — Array of entries associated with this enum

#### struct `PyGenUtil::FPropertyDef`  
`struct FPropertyDef`  
_L887-900_
- desc: Definition data for an Unreal property generated from a Python type
- L889 _public prototype_ `FPropertyDef() = default;`
- L890 _public prototype_ `FPropertyDef(FPropertyDef&&) = default;`
- L891 _public prototype_ `FPropertyDef(const FPropertyDef&) = delete;`
- L892 _public prototype_ `FPropertyDef& operator=(FPropertyDef&&) = default;`
- L893 _public prototype_ `FPropertyDef& operator=(const FPropertyDef&) = delete;`
- L896 _public member_ `FGeneratedWrappedGetSet GeneratedWrappedGetSet;` — Data needed to re-wrap this property for Python
- L899 _public member_ `PyGetSetDef PyGetSet;` — Definition of the re-wrapped property for Python

#### struct `PyGenUtil::FFunctionDef`  
`struct FFunctionDef`  
_L903-922_
- desc: Definition data for an Unreal function generated from a Python type
- L905 _public prototype_ `FFunctionDef() = default;`
- L906 _public prototype_ `FFunctionDef(FFunctionDef&&) = default;`
- L907 _public prototype_ `FFunctionDef(const FFunctionDef&) = delete;`
- L908 _public prototype_ `FFunctionDef& operator=(FFunctionDef&&) = default;`
- L909 _public prototype_ `FFunctionDef& operator=(const FFunctionDef&) = delete;`
- L912 _public member_ `FGeneratedWrappedMethod GeneratedWrappedMethod;` — Data needed to re-wrap this function for Python
- L915 _public member_ `FPyMethodWithClosureDef PyMethod;` — Definition of the re-wrapped function for Python
- L918 _public member_ `FPyObjectPtr PyFunction;` — Python function to call when invoking this re-wrapped function
- L921 _public member_ `bool bIsHidden = false;` — Is this a function hidden from Python? (eg, internal getter/setter function)

#### enum `PyGenUtil::EPythonizeNameCase`  
`enum EPythonizeNameCase : uint8`  
_L925-931_
- desc: How should PythonizeName adjust the final name?
- L928 _public enumerator_ `Lower` — lower_snake_case
- L930 _public enumerator_ `Upper` — UPPER_SNAKE_CASE

#### enum `PyGenUtil::EPythonizeFlags`  
`enum class EPythonizeFlags`  
_L934-953_
- desc: Flags controlling the behavior of PythonizeValue/PythonizeMethodParam/PythonizeMethodReturnType.
- L936 _public enumerator_ `None = 0`
- L937 _public enumerator_ `IncludeUnrealNamespace = 1<<0`
- L938 _public enumerator_ `UseStrictTyping = 1<<1`
- L939 _public enumerator_ `DefaultConstructStructs = 1<<2`
- L940 _public enumerator_ `DefaultConstructDateTime = 1<<3`
- L943 _public enumerator_ `WithTypeHinting = 1<<4` — Type hinting is enabled.
- L946 _public enumerator_ `WithOptionalType = 1<<5` — If the type of a value being hinted can be None, wrap the type in Optional[T], which is an alias to Union[T, None].
- L949 _public enumerator_ `WithTypeCoercion = 1<<6` — Declare the type along with it known type coercion. For example [unreal.Name, str] because a string can be passed in place of a Name.
- L952 _public enumerator_ `AddMissingDefaultValueEllipseWorkaround = 1<<7` — In method declaration, add '...' as default value even if no default value was found. Used in stub generation to workaround 'non-defaulted param after defaulted param' coming from the 'malformed' UFUNCTION.

#### struct `PyGenUtil::FPythonizeTooltipContext`  
`struct FPythonizeTooltipContext`  
_L957-984_
- desc: Context information passed to PythonizeTooltip
- L959 _public function_ `FPythonizeTooltipContext() : Prop(nullptr) , Func(nullptr) , ReadOnlyFlags(PropertyAccessUtil::RuntimeReadOnlyFlags)`
- L966 _public prototype_ `explicit FPythonizeTooltipContext(const FProperty* InProp, const uint64 InReadOnlyFlags = PropertyAccessUtil::RuntimeReadOnlyFlags);`
- L968 _public prototype_ `explicit FPythonizeTooltipContext(const UFunction* InFunc, const TSet<FName>& InParamsToIgnore = TSet<FName>());`
- L971 _public member_ `const FProperty* Prop;` — Optional property that should be used when converting property tooltips
- L974 _public member_ `const UFunction* Func;` — Optional function that should be used when converting function tooltips
- L977 _public member_ `uint64 ReadOnlyFlags;` — Flags that dictate whether the property should be considered read-only
- L980 _public member_ `FString DeprecationMessage;` — Optional deprecation message for the property or function
- L983 _public member_ `TSet<FName> ParamsToIgnore;` — Optional set of parameters that we should ignore when generating function tooltips

#### struct `PyGenUtil::FParsedTooltip`  
`struct FParsedTooltip`  
_L987-1058_
- desc: Parsed tooltip data used by PythonizeTooltip
- L1049 _public typedef_ `typedef TArray<FMiscToken, TInlineAllocator<4>> FMiscTokensArray;`
- L1050 _public typedef_ `typedef TArray<FParamToken, TInlineAllocator<8>> FParamTokensArray;`
- L1052 _public member_ `int32 SourceTooltipLen = 0;`
- L1054 _public member_ `FString BasicTooltipText;`
- L1055 _public member_ `FMiscTokensArray MiscTokens;`
- L1056 _public member_ `FParamTokensArray ParamTokens;`
- L1057 _public member_ `FParamToken ReturnToken;`

#### struct `PyGenUtil::FParsedTooltip::FTokenString`  
`struct FTokenString`  
_L989-1026_
- L991 _public prototype_ `FTokenString() = default;`
- L992 _public prototype_ `FTokenString(FTokenString&&) = default;`
- L993 _public prototype_ `FTokenString& operator=(FTokenString&&) = default;`
- L995 _public function_ `bool operator==(const FTokenString& InOther) const`
- L1000 _public function_ `bool operator!=(const FTokenString& InOther) const`
- L1005 _public function_ `FStringView GetValue() const`
- L1012 _public function_ `void SetValue(FStringView InValue)`
- L1018 _public function_ `void SetValue(FString&& InValue)`
- L1024 _public member_ `FStringView SimpleValue;`
- L1025 _public member_ `FString ComplexValue;`

#### struct `PyGenUtil::FParsedTooltip::FMiscToken`  
`struct FMiscToken`  
_L1028-1036_
- L1030 _public prototype_ `FMiscToken() = default;`
- L1031 _public prototype_ `FMiscToken(FMiscToken&&) = default;`
- L1032 _public prototype_ `FMiscToken& operator=(FMiscToken&&) = default;`
- L1034 _public member_ `FTokenString TokenName;`
- L1035 _public member_ `FTokenString TokenValue;`

#### struct `PyGenUtil::FParsedTooltip::FParamToken`  
`struct FParamToken`  
_L1038-1047_
- L1040 _public prototype_ `FParamToken() = default;`
- L1041 _public prototype_ `FParamToken(FParamToken&&) = default;`
- L1042 _public prototype_ `FParamToken& operator=(FParamToken&&) = default;`
- L1044 _public member_ `FTokenString ParamName;`
- L1045 _public member_ `FTokenString ParamType;`
- L1046 _public member_ `FTokenString ParamComment;`

#### Free symbols / members of external scopes

- L34 _macro_ `#define REPORT_PYTHON_GENERATION_ISSUE(Verbosity, Format, ...) \`
- L38 _namespace_ `namespace PyGenUtil`
- L40 _externvar_ `extern const FName ScriptNameMetaDataKey;` (scope `PyGenUtil`)
- L41 _externvar_ `extern const FName ScriptNoExportMetaDataKey;` (scope `PyGenUtil`)
- L42 _externvar_ `extern const FName ScriptMethodMetaDataKey;` (scope `PyGenUtil`)
- L43 _externvar_ `extern const FName ScriptMethodSelfReturnMetaDataKey;` (scope `PyGenUtil`)
- L44 _externvar_ `extern const FName ScriptMethodMutableMetaDataKey;` (scope `PyGenUtil`)
- L45 _externvar_ `extern const FName ScriptOperatorMetaDataKey;` (scope `PyGenUtil`)
- L46 _externvar_ `extern const FName ScriptConstantMetaDataKey;` (scope `PyGenUtil`)
- L47 _externvar_ `extern const FName ScriptConstantHostMetaDataKey;` (scope `PyGenUtil`)
- L48 _externvar_ `extern const FName ScriptDefaultMakeMetaDataKey;` (scope `PyGenUtil`)
- L49 _externvar_ `extern const FName ScriptDefaultBreakMetaDataKey;` (scope `PyGenUtil`)
- L50 _externvar_ `extern const FName BlueprintTypeMetaDataKey;` (scope `PyGenUtil`)
- L51 _externvar_ `extern const FName NotBlueprintTypeMetaDataKey;` (scope `PyGenUtil`)
- L52 _externvar_ `extern const FName BlueprintSpawnableComponentMetaDataKey;` (scope `PyGenUtil`)
- L53 _externvar_ `extern const FName BlueprintGetterMetaDataKey;` (scope `PyGenUtil`)
- L54 _externvar_ `extern const FName BlueprintSetterMetaDataKey;` (scope `PyGenUtil`)
- L55 _externvar_ `extern const FName BlueprintInternalUseOnlyMetaDataKey;` (scope `PyGenUtil`)
- L56 _externvar_ `extern const FName BlueprintInternalUseOnlyHierarchicalMetaDataKey;` (scope `PyGenUtil`)
- L57 _externvar_ `extern const FName CustomThunkMetaDataKey;` (scope `PyGenUtil`)
- L58 _externvar_ `extern const FName HasNativeMakeMetaDataKey;` (scope `PyGenUtil`)
- L59 _externvar_ `extern const FName HasNativeBreakMetaDataKey;` (scope `PyGenUtil`)
- L60 _externvar_ `extern const FName NativeBreakFuncMetaDataKey;` (scope `PyGenUtil`)
- L61 _externvar_ `extern const FName NativeMakeFuncMetaDataKey;` (scope `PyGenUtil`)
- L62 _externvar_ `extern const FName DeprecatedPropertyMetaDataKey;` (scope `PyGenUtil`)
- L63 _externvar_ `extern const FName DeprecatedFunctionMetaDataKey;` (scope `PyGenUtil`)
- L64 _externvar_ `extern const FName DeprecationMessageMetaDataKey;` (scope `PyGenUtil`)
- L67 _variable_ `static const char* PostInitFuncName = "_p` (scope `PyGenUtil`) — Name used by the Python equivalent of PostInitProperties
- L70 _typedef_ `typedef TArray<char> FUTF8Buffer;` (scope `PyGenUtil`) — Buffer for storing the UTF-8 strings used by Python types
- L1061 _prototype_ `FUTF8Buffer TCHARToUTF8Buffer(const TCHAR* InStr);` (scope `PyGenUtil`) — Convert a TCHAR to a UTF-8 buffer
- L1064 _prototype_ `PyObject* GetPostInitFunc(PyTypeObject* InPyType);` (scope `PyGenUtil`) — Get the PostInit function from this Python type
- L1067 _prototype_ `void AddStructInitParam(const FProperty* InUnrealProp, const TCHAR* InPythonAttrName, TArray<FGeneratedWrappedMethodParameter>& OutInitParams);` (scope `PyGenUtil`) — Add a struct init parameter to the given array of method parameters
- L1070 _prototype_ `void ExtractFunctionParams(const UFunction* InFunc, TArray<FGeneratedWrappedMethodParameter>& OutInputParams, TArray<FGeneratedWrappedMethodParameter>& OutOutputParams);` (scope `PyGenUtil`) — Given a function, extract all of its parameter information (input and output)
- L1073 _prototype_ `void ApplyParamDefaults(void* InBaseParamsAddr, const TArray<FGeneratedWrappedMethodParameter>& InParamDef);` (scope `PyGenUtil`) — Apply default values to function arguments
- L1076 _prototype_ `bool ParseMethodParameters(PyObject* InArgs, PyObject* InKwds, const TArray<FGeneratedWrappedMethodParameter>& InParamDef, const char* InPyMethodName, TArray<PyObject*>& OutPyParams);` (scope `PyGenUtil`) — Parse an array Python objects from the args and keywords based on the generated method parameter data
- L1079 _prototype_ `PyObject* PackReturnValues(const void* InBaseParamsAddr, const TArray<FGeneratedWrappedMethodParameter>& InOutputParams, const TCHAR* InErrorCtxt, const TCHAR* InCallingCtxt);` (scope `PyGenUtil`) — Given a set of return values and the struct data associated with them, pack them appropriately for returning to Python
- L1082 _prototype_ `bool UnpackReturnValues(PyObject* InRetVals, const FOutParmRec* InOutputParms, const TCHAR* InErrorCtxt, const TCHAR* InCallingCtxt);` (scope `PyGenUtil`) — Given a Python return value, unpack the values into the struct data associated with them
- L1085 _prototype_ `bool InvokePythonCallableFromUnrealFunctionThunk(FPyObjectPtr InSelf, PyObject* InCallable, const UFunction* InFunc, UObject* Context, FFrame& Stack, RESULT_DECL);` (scope `PyGenUtil`) — Invoke a Python callable from an Unreal function thunk (ie, DEFINE_FUNCTION), ensuring that the calling convention is correct for both native and script function callers
- L1088 _prototype_ `PyObject* GetPropertyValue(const UStruct* InStruct, const void* InStructData, const FGeneratedWrappedProperty& InPropDef, const char *InAttributeName, PyObject* InOwnerPyObject, const TCHAR* InErrorCtxt);` (scope `PyGenUtil`) — Get the current value of the given property from the given struct
- L1091 _prototype_ `int SetPropertyValue(const UStruct* InStruct, void* InStructData, PyObject* InValue, const FGeneratedWrappedProperty& InPropDef, const char *InAttributeName, const FPropertyAccessChangeNotify* InChangeNotify, const uint64 InReadOnlyFlags, const bool InOwnerIsTemplate, const TCHAR* InErrorCtxt, const TConstArrayView<void*>& InArchetypeInstContainers);` (scope `PyGenUtil`) — Set the current value of the given property from the given struct
- L1094 _prototype_ `FString BuildFunctionDocString(const UFunction* InFunc, const FString& InFuncPythonName, const TArray<FGeneratedWrappedMethodParameter>& InInputParams, const TArray<FGeneratedWrappedMethodParameter>& InOutputParams, const bool* InStaticOverride = nullptr);` (scope `PyGenUtil`) — Build a Python doc string for the given function and arguments list
- L1097 _prototype_ `bool IsBlueprintGeneratedClass(const UClass* InClass);` (scope `PyGenUtil`) — Is the given class generated by Blueprints?
- L1100 _prototype_ `bool IsBlueprintGeneratedStruct(const UScriptStruct* InStruct);` (scope `PyGenUtil`) — Is the given struct generated by Blueprints?
- L1103 _prototype_ `bool IsBlueprintGeneratedEnum(const UEnum* InEnum);` (scope `PyGenUtil`) — Is the given enum generated by Blueprints?
- L1106 _prototype_ `bool IsDeprecatedClass(const UClass* InClass, FString* OutDeprecationMessage = nullptr);` (scope `PyGenUtil`) — Is the given class marked as deprecated?
- L1109 _prototype_ `bool IsDeprecatedProperty(const FProperty* InProp, FString* OutDeprecationMessage = nullptr);` (scope `PyGenUtil`) — Is the given property marked as deprecated?
- L1112 _prototype_ `bool IsDeprecatedFunction(const UFunction* InFunc, FString* OutDeprecationMessage = nullptr);` (scope `PyGenUtil`) — Is the given function marked as deprecated?
- L1115 _prototype_ `TArray<const UClass*> GetExportedInterfacesForClass(const UClass* InClass);` (scope `PyGenUtil`) — Given a class, get all the interface classes related to it that should be included when exporting it to Python
- L1118 _prototype_ `bool ShouldExportClass(const UClass* InClass);` (scope `PyGenUtil`) — Should the given class be exported to Python?
- L1121 _prototype_ `bool ShouldExportStruct(const UScriptStruct* InStruct);` (scope `PyGenUtil`) — Should the given struct be exported to Python?
- L1124 _prototype_ `bool ShouldExportEnum(const UEnum* InEnum);` (scope `PyGenUtil`) — Should the given enum be exported to Python?
- L1127 _prototype_ `bool ShouldExportEnumEntry(const UEnum* InEnum, int32 InEnumEntryIndex);` (scope `PyGenUtil`) — Should the given enum entry be exported to Python?
- L1130 _prototype_ `bool ShouldExportProperty(const FProperty* InProp);` (scope `PyGenUtil`) — Should the given property be exported to Python?
- L1133 _prototype_ `bool ShouldExportEditorOnlyProperty(const FProperty* InProp);` (scope `PyGenUtil`) — Should the given property be exported to Python as editor-only data?
- L1136 _prototype_ `bool ShouldExportFunction(const UFunction* InFunc);` (scope `PyGenUtil`) — Should the given function be exported to Python?
- L1139 _prototype_ `bool IsValidName(FStringView InName, FText* OutError = nullptr);` (scope `PyGenUtil`) — Check that the given name will be valid for Python
- L1142 _prototype_ `FString PythonizeName(FStringView InName, const EPythonizeNameCase InNameCase);` (scope `PyGenUtil`) — Given a CamelCase name, convert it to snake_case
- L1145 _prototype_ `FString PythonizePropertyName(FStringView InName, const EPythonizeNameCase InNameCase);` (scope `PyGenUtil`) — Given a CamelCase property name, convert it to snake_case (may remove some superfluous parts of the property name)
- L1148 _prototype_ `FString PythonizePropertyTooltip(const FParsedTooltip& InTooltip, const FProperty* InProp, const uint64 InReadOnlyFlags = PropertyAccessUtil::RuntimeReadOnlyFlags);` (scope `PyGenUtil`) — Given a property tooltip, convert it to a doc string
- L1151 _prototype_ `FString PythonizeFunctionTooltip(const FParsedTooltip& InTooltip, const UFunction* InFunc, const TSet<FName>& ParamsToIgnore = TSet<FName>());` (scope `PyGenUtil`) — Given a function tooltip, convert it to a doc string
- L1154 _prototype_ `FString PythonizeTooltip(const FParsedTooltip& InTooltip, const FPythonizeTooltipContext& InContext = FPythonizeTooltipContext());` (scope `PyGenUtil`) — Given a parsed tooltip, convert it to a doc string
- L1160 _prototype_ `FParsedTooltip ParseTooltip(FStringView InTooltip);` (scope `PyGenUtil`) — Given a tooltip, parse it into something that can be converted into a doc string @note The parsed result may referenced sub-strings of the given view, so InTooltip must exist as long as the result does.
- L1163 _prototype_ `FString PythonizeValue(const FProperty* InProp, const void* InPropValue, const EPythonizeFlags InPythonizeFlags = EPythonizeFlags::None);` (scope `PyGenUtil`) — Given a property and its value, convert it into something that could be used in a Python script
- L1166 _prototype_ `FString PythonizeDefaultValue(const FProperty* InProp, const FString& InDefaultValue, const EPythonizeFlags InPythonizeFlags = EPythonizeFlags::None);` (scope `PyGenUtil`) — Given a property and its default value, convert it into something that could be used in a Python script
- L1169 _prototype_ `FString PythonizeMethodParam(const FGeneratedWrappedMethodParameter& InMethodParam, EPythonizeFlags InPythonizeFlags = EPythonizeFlags::None, const TFunction<bool(const FString&)>& ShouldEllipseDefaultValue = TFunction<bool(const FString&)>());` (scope `PyGenUtil`) — Given a generated method parameter, extract the name, type and default value and format a parameter declaration usable in a Python method signature according to the specified flags.
- L1172 _prototype_ `FString PythonizeMethodParam(const FString& InParamName, const FProperty* ParamProp, EPythonizeFlags InPythonizeFlags = EPythonizeFlags::None);` (scope `PyGenUtil`) — Given a property and a name, format a parameter declaration usable in a Python method signature according to the specified flags.
- L1175 _prototype_ `FString PythonizeMethodParam(const FString& InParamName, const FString& InParamType = FString(), const FString& InDefaultValue = FString());` (scope `PyGenUtil`) — Given a param name and optional param type and default value, format a parameter declaration usable in a Python method signature.
- L1178 _prototype_ `FString PythonizeMethodReturnType(const TArray<PyGenUtil::FGeneratedWrappedMethodParameter>& InOutputParams, EPythonizeFlags InPythonizeFlags = EPythonizeFlags::None);` (scope `PyGenUtil`) — Given list of return parameter, format the return type declaration usable in the Python method signature according to the flags.
- L1181 _prototype_ `FString PythonizeMethodReturnType(const FProperty* InProp, EPythonizeFlags InPythonizeFlags = EPythonizeFlags::None);` (scope `PyGenUtil`) — Given a property, format a return type declaration usable in the Python method signature according to the flags.
- L1184 _prototype_ `const UObject* GetAssetTypeRegistryType(const UObject* InObj);` (scope `PyGenUtil`) — Get the type that should be used with the Python type registry for an asset (eg, a Blueprint asset should use its generated class)
- L1187 _prototype_ `FString GetFieldModule(const UField* InField);` (scope `PyGenUtil`) — Get the native module the given field belongs to
- L1190 _prototype_ `FString GetFieldPlugin(const UField* InField);` (scope `PyGenUtil`) — Get the plugin module the given field belongs to (if any)
- L1193 _prototype_ `FString GetModulePythonName(const FName InModuleName, const bool bIncludePrefix = true);` (scope `PyGenUtil`) — Given a native module name, get the Python module we should use
- L1196 _prototype_ `FString GetClassPythonName(const UClass* InClass);` (scope `PyGenUtil`) — Get the Python name of the given class
- L1199 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedClassPythonNames(const UClass* InClass);` (scope `PyGenUtil`) — Get the deprecated Python names of the given class
- L1202 _prototype_ `FString GetStructPythonName(const UScriptStruct* InStruct);` (scope `PyGenUtil`) — Get the Python name of the given struct
- L1205 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedStructPythonNames(const UScriptStruct* InStruct);` (scope `PyGenUtil`) — Get the deprecated Python names of the given struct
- L1208 _prototype_ `FString GetEnumPythonName(const UEnum* InEnum);` (scope `PyGenUtil`) — Get the Python name of the given enum
- L1211 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedEnumPythonNames(const UEnum* InEnum);` (scope `PyGenUtil`) — Get the deprecated Python names of the given enum
- L1214 _prototype_ `FString GetEnumEntryPythonName(const UEnum* InEnum, const int32 InEntryIndex);` (scope `PyGenUtil`) — Get the Python name of the given enum entry
- L1217 _prototype_ `TArray<FString> GetDeprecatedEnumEntryPythonNames(const UEnum* InEnum, const int32 InEntryIndex);` (scope `PyGenUtil`) — Get the deprecated Python names of the given enum entry
- L1220 _prototype_ `FString GetDelegatePythonName(const UFunction* InDelegateSignature);` (scope `PyGenUtil`) — Get the Python name of the given delegate signature
- L1223 _prototype_ `FString GetFunctionPythonName(const UFunction* InFunc);` (scope `PyGenUtil`) — Get the Python name of the given function
- L1226 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedFunctionPythonNames(const UFunction* InFunc);` (scope `PyGenUtil`) — Get the deprecated Python names of the given function
- L1229 _prototype_ `FString GetScriptMethodPythonName(const UFunction* InFunc);` (scope `PyGenUtil`) — Get the Python name of the given function when it's hoisted as a script method
- L1232 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedScriptMethodPythonNames(const UFunction* InFunc);` (scope `PyGenUtil`) — Get the deprecated Python names of the given function it's hoisted as a script method
- L1235 _prototype_ `FString GetScriptConstantPythonName(const UFunction* InFunc);` (scope `PyGenUtil`) — Get the Python name of the given function when it's hoisted as a script constant
- L1238 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedScriptConstantPythonNames(const UFunction* InFunc);` (scope `PyGenUtil`) — Get the deprecated Python names of the given function it's hoisted as a script constant
- L1241 _prototype_ `FString GetPropertyPythonName(const FProperty* InProp);` (scope `PyGenUtil`) — Get the Python name of the given property
- L1244 _prototype_ `TArray<TTuple<FSoftObjectPath, FString>> GetDeprecatedPropertyPythonNames(const FProperty* InProp);` (scope `PyGenUtil`) — Get the deprecated Python names of the given property
- L1247 _prototype_ `FString GetPropertyTypePythonName(const FProperty* InProp, const bool InIncludeUnrealNamespace = false, const bool InIsForDocString = true, const EPythonizeFlags PythonizeFlags = EPythonizeFlags::None);` (scope `PyGenUtil`) — Get the Python name of the given property
- L1250 _prototype_ `FString GetPropertyPythonType(const FProperty* InProp);` (scope `PyGenUtil`) — Get the Python type of the given property
- L1253 _prototype_ `void AppendPropertyPythonType(const FProperty* InProp, FString& OutStr);` (scope `PyGenUtil`) — Append the Python type of the given property to the given string
- L1256 _prototype_ `void AppendPropertyPythonReadWriteState(const FProperty* InProp, FString& OutStr, const uint64 InReadOnlyFlags = PropertyAccessUtil::RuntimeReadOnlyFlags);` (scope `PyGenUtil`) — Append the given Python property read /write state to the given string
- L1259 _prototype_ `FString GetFieldTooltip(const UField* InField);` (scope `PyGenUtil`) — Get the tooltip for the given field
- L1260 _prototype_ `FString GetFieldTooltip(const FField* InField);` (scope `PyGenUtil`)
- L1263 _prototype_ `FString GetEnumEntryTooltip(const UEnum* InEnum, const int64 InEntryIndex);` (scope `PyGenUtil`) — Get the tooltip for the given enum entry
- L1266 _prototype_ `FString BuildSourceInformationDocString(const UField* InOwnerType);` (scope `PyGenUtil`) — Get the doc string for the C++ or asset source information of the given type
- L1269 _prototype_ `void AppendSourceInformationDocString(const UField* InOwnerType, FString& OutStr);` (scope `PyGenUtil`) — Append the doc string for the C++ or asset source information of the given type to the given string
- L1272 _prototype_ `bool SaveGeneratedTextFile(const TCHAR* InFilename, FStringView InFileContents, const bool InForceWrite = false);` (scope `PyGenUtil`) — Save a generated text file to disk as UTF-8 (only writes the file if the contents differs, unless forced)
- L1279 _prototype_ `void SetTypeHintingMode(ETypeHintingMode InMode);` (scope `PyGenUtil`) — Whether Python type hints should be generated. This is only effective if Python interpreter version has the support. This affects the Python stub and docstrings. The function must be called before Python glue and the stub are generated. It can be set from the user settings or forced to a value for a specific purpose, like generating the online doc.
- L1285 _prototype_ `ETypeHintingMode GetTypeHintingMode();` (scope `PyGenUtil`) — Return the effecting type hinting mode. @see SetTypeHintingMode.
- L1292 _prototype_ `bool IsTypeHintingEnabled();` (scope `PyGenUtil`) — Whether the stub and docstrings are type hinted during glue/stub generation. Default to false. This doesn't read the user settings, but rather the value set with SetTypeHintingMode(). The function always returns false if the linked Python interpreter version is older than 3.7.

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyMethodWithClosure.h` (Private)


#### struct `FPyMethodWithClosureDef`  
`struct FPyMethodWithClosureDef`  
_L34-62_
- desc: Definition for a method with a closure (equivalent to PyMethodDef)
- L37 _public member_ `const char* MethodName;` — The name of the method
- L40 _public member_ `PyCFunctionWithClosure MethodCallback;` — The C function this method should call
- L43 _public member_ `int MethodFlags;` — Combination of METH_ flags describing how the C function should be called
- L46 _public member_ `const char* MethodDoc;` — The method documentation, or nullptr
- L49 _public member_ `void* MethodClosure;` — The closure passed to the C function, or nullptr
- L52 _public prototype_ `static bool AddMethod(FPyMethodWithClosureDef* InMethod, PyTypeObject* InType);` — Add a singular method to the given type
- L55 _public prototype_ `static bool AddMethods(FPyMethodWithClosureDef* InMethods, PyTypeObject* InType);` — Add the given null-terminated table of methods to the given type
- L58 _public prototype_ `static PyObject* NewMethodDescriptor(PyTypeObject* InType, FPyMethodWithClosureDef* InDef);` — Create a method descriptor for the given definition
- L61 _public prototype_ `static PyObject* Call(FPyMethodWithClosureDef* InDef, PyObject* InSelf, PyObject* InArgs, PyObject* InKwds);` — Call the method with the given self and arguments

#### struct `FPyCFunctionWithClosureObject`  
`struct FPyCFunctionWithClosureObject`  
_L65-93_
- desc: Python object for the bound callable form of method with a closure (equivalent to PyCFunctionObject)
- L71 _public member_ `FPyMethodWithClosureDef* MethodDef;` — Definition of the method to call
- L74 _public member_ `PyObject* SelfArg;` — The 'self' argument passed to the C function, or nullptr
- L77 _public member_ `PyObject* ModuleAttr;` — The __module__ attribute, can be anything
- L80 _public prototype_ `static FPyCFunctionWithClosureObject* New(FPyMethodWithClosureDef* InMethod, PyObject* InSelf, PyObject* InModule);` — New this instance
- L83 _public prototype_ `static void Free(FPyCFunctionWithClosureObject* InSelf);` — Free this instance
- L86 _public prototype_ `static int GCTraverse(FPyCFunctionWithClosureObject* InSelf, visitproc InVisit, void* InArg);` — Handle a Python GC traverse
- L89 _public prototype_ `static int GCClear(FPyCFunctionWithClosureObject* InSelf);` — Handle a Python GC clear
- L92 _public prototype_ `static PyObject* Str(FPyCFunctionWithClosureObject* InSelf);` — Get a string representing this instance

#### struct `FPyMethodWithClosureDescrObject`  
`struct FPyMethodWithClosureDescrObject`  
_L96-133_
- desc: Python object for the descriptor of a method with a closure (equivalent to PyMethodDescrObject)
- L102 _public member_ `PyTypeObject* OwnerType;` — Type of the owner object
- L105 _public member_ `PyObject* MethodName;` — Name of the method being described
- L108 _public member_ `FPyMethodWithClosureDef* MethodDef;` — Definition of the method to call
- L111 _public prototype_ `static FPyMethodWithClosureDescrObject* NewMethod(PyTypeObject* InType, FPyMethodWithClosureDef* InMethod);` — New a method
- L114 _public prototype_ `static FPyMethodWithClosureDescrObject* NewClassMethod(PyTypeObject* InType, FPyMethodWithClosureDef* InMethod);` — New a class method
- L117 _public prototype_ `static FPyMethodWithClosureDescrObject* NewImpl(PyTypeObject* InDescrType, PyTypeObject* InType, FPyMethodWithClosureDef* InMethod);` — New this instance
- L120 _public prototype_ `static void Free(FPyMethodWithClosureDescrObject* InSelf);` — Free this instance
- L123 _public prototype_ `static int GCTraverse(FPyMethodWithClosureDescrObject* InSelf, visitproc InVisit, void* InArg);` — Handle a Python GC traverse
- L126 _public prototype_ `static int GCClear(FPyMethodWithClosureDescrObject* InSelf);` — Handle a Python GC clear
- L129 _public prototype_ `static PyObject* Str(FPyMethodWithClosureDescrObject* InSelf);` — Get a string representing this instance
- L132 _public prototype_ `static FString GetMethodName(FPyMethodWithClosureDescrObject* InSelf);` — Safely get the name of the method (if known)

#### Free symbols / members of external scopes

- L11 _externvar_ `extern PyTypeObject PyCFunctionWithClosureType;` — Python type for FPyCFunctionWithClosureObject
- L14 _externvar_ `extern PyTypeObject PyMethodWithClosureDescrType;` — Python type for FPyMethodWithClosureDescrObject
- L17 _externvar_ `extern PyTypeObject PyClassMethodWithClosureDescrType;` — Python type for FPyMethodWithClosureDescrObject (for class methods)
- L20 _prototype_ `bool InitializePyMethodWithClosure();` — Initialize the PyMethodWithClosure types
- L23 _prototype_ `void ShutdownPyMethodWithClosure();` — Shutdown the PyMethodWithClosure types
- L26 _typedef_ `typedef PyObject*(*PyCFunctionWithClosure)(PyObject*, PyObject*, void*);` — C function pointers used by FPyMethodWithClosureDef
- L27 _typedef_ `typedef PyObject*(*PyCFunctionWithClosureAndKeywords)(PyObject*, PyObject*, PyObject*, void*);`
- L28 _typedef_ `typedef PyObject*(*PyCFunctionWithClosureAndNoArgs)(PyObject*, void*);`
- L31 _macro_ `#define PyCFunctionWithClosureCast(FUNCPTR) (PyCFunctionWithClosure)(void*)(FUNCPTR)` — Cast a function pointer to PyCFunctionWithClosure (via a void* to avoid a compiler warning)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyOnlineDocsWriter.h` (Private)


#### enum `EPyOnlineDocsFilterFlags`  
`enum class EPyOnlineDocsFilterFlags : uint8`  
_L13-21_
- desc: Flags controlling which data is included in the Python API online docs.
- L15 _public enumerator_ `IncludeNone = 0`
- L16 _public enumerator_ `IncludeEngine = 1<<0`
- L17 _public enumerator_ `IncludeEnterprise UE_DEPRECATED(5.6, "Enterprise is now considered a part of engine, please update usage to the engine enum flag.") = IncludeEngine`
- L18 _public enumerator_ `IncludeInternal = 1<<2`
- L19 _public enumerator_ `IncludeProject = 1<<3`
- L20 _public enumerator_ `IncludeAll = IncludeEngine | IncludeInternal | IncludeProject`

#### class `FPyOnlineDocsModule`  
`class FPyOnlineDocsModule`  
_L28-47_
- desc: A single module in the Python API online docs. Hosts a series of function names that belong to this module and will be used for indexing purposes later.
- L33 _public function_ `FPyOnlineDocsModule(const FString& InModuleName) : Name(InModuleName)`
- L39 _public prototype_ `void AccumulateFunction(const TCHAR* InFunctionName);` — Store function name in this module to generate files later.
- L43 _private member_ `FString Name;` — Module name.
- L46 _private member_ `TArray<FString> FunctionNames;` — Accumulated Python function names to write out to API docs.

#### class `FPyOnlineDocsSection`  
`class FPyOnlineDocsSection`  
_L53-75_
- desc: A single section in the Python API online docs. Hosts a series of type names that belong to this section and will be used for indexing purposes later.
- L58 _public function_ `FPyOnlineDocsSection(const FString& InSectionName) : Name(InSectionName)`
- L64 _public prototype_ `void AccumulateClass(const TCHAR* InTypeName);` — Store class name in this section to generate files later.
- L67 _public function_ `const FString& GetName() const` — /  Get name of section.
- L71 _private member_ `FString Name;` — Section name.
- L74 _private member_ `TArray<FString> TypeNames;` — Accumulated Python type names to write out to API docs.

#### class `FPyOnlineDocsWriter`  
`class FPyOnlineDocsWriter`  
_L82-124_
- desc: Utility class to help format and write Python API online docs in reStructuredText files used by Sphinx to generate static HTML. See PythonScriptPlugin\SphinxDocs\PythonAPI_docs_readme.txt for additional info.
- L86 _public prototype_ `TSharedRef<FPyOnlineDocsModule> CreateModule(const FString& InModuleName);` — Add a new module.
- L89 _public prototype_ `TSharedRef<FPyOnlineDocsSection> CreateSection(const FString& InSectionName);` — Add a new section.
- L92 _public prototype_ `FString GetSphinxDocsPath() const;` — Get the directory for the Sphinx files.
- L95 _public prototype_ `FString GetSourcePath() const;` — Get the directory for the Sphinx source files.
- L98 _public prototype_ `FString GetBuildPath() const;` — Get the directory for the Sphinx build files.
- L101 _public prototype_ `FString GetTemplatePath() const;` — Get the directory for the Sphinx template files.
- L104 _public prototype_ `void GenerateConfigFile();` — Create Python config for Sphinx based on template.
- L107 _public prototype_ `void GenerateIndexFile();` — Create index reStructuredText file for Sphinx based on template.
- L110 _public prototype_ `void GenerateModuleFiles();` — Create reStructuredText module files for Sphinx based on template.
- L113 _public prototype_ `void GenerateClassFiles();` — Create reStructuredText class files for Sphinx based on template.
- L116 _public prototype_ `void GenerateFiles(const FString& InPythonStubPath);` — Create reStructuredText files for Sphinx.
- L120 _private member_ `TArray<TSharedRef<FPyOnlineDocsModule>> Modules;` — API doc modules.
- L123 _private member_ `TArray<TSharedRef<FPyOnlineDocsSection>> Sections;` — API doc sections.

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_CLASS_FLAGS(EPyOnlineDocsFilterFlags);`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyPtr.h` (Private)


#### class `TPyPtr`  
`template <typename TPythonType> class TPyPtr`  
_L12-192_
- desc: Wrapper that handles the ref-counting of the contained Python object
- L16 _public function_ `TPyPtr() : Ptr(nullptr)` — Create a null pointer
- L22 _public function_ `TPyPtr(const TPyPtr& InOther) : Ptr(InOther.Ptr)` — Copy a pointer
- L30 _public function_ `template <typename TOtherPythonType> TPyPtr(const TPyPtr<TOtherPythonType>& InOther) : Ptr(InOther.Ptr)` — Copy a pointer
- L37 _public function_ `TPyPtr(TPyPtr&& InOther) : Ptr(InOther.Ptr)` — Move a pointer
- L45 _public function_ `template <typename TOtherPythonType> TPyPtr(TPyPtr<TOtherPythonType>&& InOther) : Ptr(InOther.Ptr)` — Move a pointer
- L52 _public function_ `~TPyPtr()` — Release our reference to this object
- L58 _public function_ `static TPyPtr NewReference(TPythonType* InPtr)` — Create a pointer from the given object, incrementing its reference count
- L64 _public function_ `static TPyPtr StealReference(TPythonType* InPtr)` — Create a pointer from the given object, leaving its reference count alone
- L70 _public function_ `TPyPtr& operator=(const TPyPtr& InOther)` — Copy a pointer
- L83 _public function_ `template <typename TOtherPythonType> TPyPtr& operator=(const TPyPtr<TOtherPythonType>& InOther)` — Copy a pointer
- L95 _public function_ `TPyPtr& operator=(TPyPtr&& InOther)` — Move a pointer
- L108 _public function_ `template <typename TOtherPythonType> TPyPtr& operator=(TPyPtr<TOtherPythonType>&& InOther)` — Move a pointer
- L119 _public function_ `explicit operator bool() const`
- L124 _public function_ `bool IsValid() const`
- L129 _public function_ `operator TPythonType*() const`
- L134 _public function_ `TPythonType& operator*()`
- L140 _public function_ `const TPythonType& operator*() const`
- L146 _public function_ `TPythonType* operator->()`
- L152 _public function_ `const TPythonType* operator->() const`
- L158 _public function_ `TPythonType*& Get()`
- L163 _public function_ `TPythonType* GetPtr() const`
- L168 _public function_ `TPythonType* Release()`
- L175 _public function_ `void Reset()`
- L182 _private function_ `TPyPtr(TPythonType* InPtr, const bool bIncRef) : Ptr(InPtr)`
- L191 _private member_ `TPythonType* Ptr;`

#### Free symbols / members of external scopes

- L194 _typedef_ `typedef TPyPtr<PyObject> FPyObjectPtr;`
- L195 _typedef_ `typedef TPyPtr<PyTypeObject> FPyTypeObjectPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyReferenceCollector.h` (Private)


#### enum `EPyReferenceCollectorFlags`  
`enum class EPyReferenceCollectorFlags : uint8`  
_L14-26_
- L16 _public enumerator_ `None = 0`
- L17 _public enumerator_ `IncludeObjects = 1<<0`
- L18 _public enumerator_ `IncludeInterfaces = 1<<1`
- L19 _public enumerator_ `IncludeStructs = 1<<2`
- L20 _public enumerator_ `IncludeDelegates = 1<<3`
- L21 _public enumerator_ `IncludeArrays = 1<<4`
- L22 _public enumerator_ `IncludeSets = 1<<5`
- L23 _public enumerator_ `IncludeMaps = 1<<6`
- L24 _public enumerator_ `IncludeContainers = IncludeArrays | IncludeSets | IncludeMaps`
- L25 _public enumerator_ `IncludeAll = IncludeObjects | IncludeInterfaces | IncludeStructs | IncludeDelegates | IncludeContainers`

#### class `FPyReferenceCollector`  
`class FPyReferenceCollector : public FGCObject`  
_L30-78_
- inherits: `FGCObject`
- desc: Singleton instance that keeps UObject instances alive while they're being referenced by Python
- L34 _public prototype_ `static FPyReferenceCollector& Get();` — Access the singleton instance
- L37 _public prototype_ `void AddWrappedInstance(FPyWrapperBase* InInstance);` — Add a wrapped instance so it can be reference collected
- L40 _public prototype_ `void RemoveWrappedInstance(FPyWrapperBase* InInstance);` — Remove a wrapped instance
- L43 _public prototype_ `void PurgeUnrealObjectReferences(const UObject* InObject, const bool bIncludeInnerObjects);` — Purge any Python references to the given UObject instance
- L46 _public prototype_ `void PurgeUnrealObjectReferences(const TArrayView<const UObject*>& InObjects, const bool bIncludeInnerObjects);` — Purge any Python references to the given UObject instances
- L49 _public prototype_ `void PurgeUnrealGeneratedTypes();` — Purge any Python references to any Unreal types generated from or for Python
- L51 _public prototype_ `void Shutdown();`
- L54 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L55 _public prototype_ `virtual FString GetReferencerName() const override;`
- L58 _public prototype_ `static void AddReferencedObjectsFromDelegate(FReferenceCollector& InCollector, FScriptDelegate& InDelegate);` — Utility function to ARO a delegate instance
- L61 _public prototype_ `static void AddReferencedObjectsFromMulticastDelegate(FReferenceCollector& InCollector, const FMulticastScriptDelegate& InDelegate);` — Utility function to ARO a multicast delegate instance
- L64 _public prototype_ `static void AddReferencedObjectsFromStruct(FReferenceCollector& InCollector, const UStruct* InStruct, void* InStructAddr, const EPyReferenceCollectorFlags InFlags = EPyReferenceCollectorFlags::IncludeAll);` — Utility function to ARO all properties on a struct instance
- L67 _public prototype_ `static void AddReferencedObjectsFromProperty(FReferenceCollector& InCollector, const FProperty* InProp, void* InBaseAddr, const EPyReferenceCollectorFlags InFlags = EPyReferenceCollectorFlags::IncludeAll);` — Utility function to ARO the given property instance
- L71 _private prototype_ `static void AddReferencedObjectsFromStructInternal(FReferenceCollector& InCollector, const UStruct* InStruct, void* InStructAddr, const EPyReferenceCollectorFlags InFlags, bool& OutValueChanged);` — Utility function to ARO all properties on a struct instance
- L74 _private prototype_ `static void AddReferencedObjectsFromPropertyInternal(FReferenceCollector& InCollector, const FProperty* InProp, void* InBaseAddr, const EPyReferenceCollectorFlags InFlags, bool& OutValueChanged);` — Utility function to ARO the given property instance
- L77 _private member_ `TSet<FPyWrapperBase*> PythonWrappedInstances;` — Set of Python wrapped instances to ARO

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PySlate.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PySlate`
- L13 _prototype_ `void InitializeModule();` (scope `PySlate`)
- L14 _prototype_ `void ShutdownModule();` (scope `PySlate`)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyTest.h` (Private)


#### enum `EPyTestEnum`  
`enum class EPyTestEnum : uint8`  
_L30-34_
- reflection: `UENUM(BlueprintType)`
- desc: Enum to allow testing of the various UEnum features that are exposed to Python wrapped types.
- L32 _public enumerator_ `One UMETA(DisplayName = "Says One but my value is Zero")`
- L33 _public enumerator_ `Two`

#### struct `FPyTestStruct`  
`struct FPyTestStruct`  
_L40-100_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct to allow testing of the various UStruct features that are exposed to Python wrapped types.
- L45 _public prototype_ `FPyTestStruct();`
- L48 _public member_ `bool Bool;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L51 _public member_ `int32 Int;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L54 _public member_ `float Float;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L57 _public member_ `EPyTestEnum Enum;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L60 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L63 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L66 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L69 _public member_ `TFieldPath<FProperty> FieldPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L72 _public member_ `TFieldPath<FStructProperty> StructFieldPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L75 _public member_ `TArray<FString> StringArray;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L78 _public member_ `TSet<FString> StringSet;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L81 _public member_ `TMap<FString, int32> StringIntMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L84 _public member_ `int32 LegacyInt_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="LegacyInt is deprecated. Please use Int instead."))`
- L87 _public member_ `bool BoolInstanceOnly;` — `UPROPERTY(EditInstanceOnly, Category = "Python|Internal")`
- L90 _public member_ `bool BoolDefaultsOnly;` — `UPROPERTY(EditDefaultsOnly, Category = "Python|Internal")`
- L93 _public member_ `mutable bool BoolMutable = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python|Internal")`
- L96 _public member_ `TOptional<int32> OptionalInt;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L99 _public member_ `TOptional<FString> OptionalString;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`

#### struct `FPyTestChildStruct`  
`struct FPyTestChildStruct : public FPyTestStruct`  
_L106-109_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPyTestStruct`
- desc: Struct to allow testing of inheritance on Python wrapped types.

#### class `UPyTestStructLibrary`  
`class UPyTestStructLibrary : public UBlueprintFunctionLibrary`  
_L115-148_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto the test struct in Python.
- L120 _private prototype_ `static bool IsBoolSet(const FPyTestStruct& InStruct);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptMethod="IsBoolSet;IsBoolSetOld"))`
- L123 _private prototype_ `static bool LegacyIsBoolSet(const FPyTestStruct& InStruct);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptMethod, DeprecatedFunction, DeprecationMessage="LegacyIsBoolSet is deprecated. Please use IsBoolSet instead."))`
- L126 _private prototype_ `static int32 GetConstantValue();` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptConstant="ConstantValue", ScriptConstantHost="/Script/PythonScriptPlugin.PyTestStruct"))`
- L129 _private prototype_ `static FPyTestStruct AddInt(const FPyTestStruct& InStruct, const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodSelfReturn, ScriptOperator="+;+="))`
- L132 _private prototype_ `static FPyTestStruct AddFloat(const FPyTestStruct& InStruct, const float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodSelfReturn, ScriptOperator="+;+="))`
- L135 _private prototype_ `static FPyTestStruct AddStr(const FPyTestStruct& InStruct, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodSelfReturn, ScriptOperator="+;+="))`
- L138 _private prototype_ `static void SetBoolMutable(const FPyTestStruct& InStruct);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodMutable))`
- L141 _private prototype_ `static void ClearBoolMutable(const FPyTestStruct& InStruct);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodMutable))`
- L144 _private prototype_ `static void SetBoolMutableViaRef(UPARAM(ref) FPyTestStruct& InStruct);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodMutable))`
- L147 _private prototype_ `static void ClearBoolMutableViaRef(UPARAM(ref) FPyTestStruct& InStruct);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(ScriptMethod, ScriptMethodMutable))`

#### struct `FPyTestClassSparseData`  
`struct FPyTestClassSparseData`  
_L154-161_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct to allow testing of class sparse data on a Python exposed type.
- L160 _public member_ `int32 IntFromSparseData = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Python|Internal")`

#### class `UPyTestObject`  
`class UPyTestObject : public UObject, public IPyTestChildInterface, public IPyTestOtherInterface`  
_L167-309_
- reflection: `UCLASS(Blueprintable, SparseClassDataTypes = PyTestClassSparseData)`
- inherits: `UObject,IPyTestChildInterface,IPyTestOtherInterface`
- desc: Object to allow testing of the various UObject features that are exposed to Python wrapped types.
- L172 _public prototype_ `UPyTestObject();`
- L175 _public member_ `bool Bool;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L178 _public member_ `int32 Int;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L181 _public member_ `float Float;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L184 _public member_ `EPyTestEnum Enum;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L187 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L190 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L193 _public member_ `FText Text;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L196 _public member_ `TFieldPath<FProperty> FieldPath = TFieldPath<FProperty>(FPyTestStruct::StaticStruct()->FindPropertyByName(TEXT("Strin` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L199 _public member_ `TFieldPath<FStructProperty> StructFieldPath = TFieldPath<FStructProperty>(CastField<FStructProperty>(UPyTestObject::GetClass()->FindPropertyByName(TEXT("Struct` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L202 _public member_ `TArray<FString> StringArray;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L205 _public member_ `TSet<FString> StringSet;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L208 _public member_ `TMap<FString, int32> StringIntMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L211 _public member_ `FPyTestDelegate Delegate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L214 _public member_ `FPyTestMulticastDelegate MulticastDelegate;` — `UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "Python|Internal")`
- L217 _public member_ `FPyTestStruct Struct;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L220 _public member_ `TArray<FPyTestStruct> StructArray;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L223 _public member_ `FPyTestChildStruct ChildStruct;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L226 _public member_ `bool BoolInstanceOnly;` — `UPROPERTY(EditInstanceOnly, Category = "Python|Internal")`
- L229 _public member_ `bool BoolDefaultsOnly;` — `UPROPERTY(EditDefaultsOnly, Category = "Python|Internal")`
- L232 _public member_ `TOptional<int32> OptionalInt;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L235 _public member_ `TOptional<FString> OptionalString;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L238 _public prototype_ `int32 FuncBlueprintImplementable(const int32 InValue) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python|Internal")`
- L241 _public prototype_ `bool FuncBlueprintImplementablePackedGetter(int32& OutValue) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python|Internal")`
- L244 _public prototype_ `int32 FuncBlueprintNative(const int32 InValue) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Python|Internal")`
- L247 _public prototype_ `void FuncBlueprintNativeRef(UPARAM(ref) FPyTestStruct& InOutStruct) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Python|Internal")`
- L250 _public prototype_ `int32 CallFuncBlueprintImplementable(const int32 InValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L253 _public prototype_ `bool CallFuncBlueprintImplementablePackedGetter(int32& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L256 _public prototype_ `int32 CallFuncBlueprintNative(const int32 InValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L259 _public prototype_ `void CallFuncBlueprintNativeRef(UPARAM(ref) FPyTestStruct& InOutStruct) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L262 _public prototype_ `void FuncTakingPyTestStruct(const FPyTestStruct& InStruct) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L265 _public prototype_ `void FuncTakingPyTestChildStruct(const FPyTestChildStruct& InStruct) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L268 _public prototype_ `void LegacyFuncTakingPyTestStruct(const FPyTestStruct& InStruct) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal", meta=(DeprecatedFunction, DeprecationMessage="LegacyFuncTakingPyTestStruct is deprecated. Please use FuncTakingPyTestStruct instead."))`
- L271 _public prototype_ `void FuncTakingPyTestStructDefault(const FPyTestStruct& InStruct = FPyTestStruct());` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L274 _public prototype_ `int32 FuncTakingPyTestDelegate(const FPyTestDelegate& InDelegate, const int32 InValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L277 _public prototype_ `void FuncTakingFieldPath(const TFieldPath<FProperty>& InFieldPath);` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")` — UHT couldn't parse any default value for the FieldPath.
- L280 _public prototype_ `int32 DelegatePropertyCallback(const int32 InValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L283 _public prototype_ `void MulticastDelegatePropertyCallback(FString InStr) const;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L286 _public prototype_ `static TArray<int32> ReturnArray();` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L289 _public prototype_ `static TSet<int32> ReturnSet();` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L292 _public prototype_ `static TMap<int32, bool> ReturnMap();` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L295 _public prototype_ `static TFieldPath<FProperty> ReturnFieldPath();` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L298 _public prototype_ `static void EmitScriptError();` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L301 _public prototype_ `static void EmitScriptWarning();` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`
- L304 _public prototype_ `static int32 GetConstantValue();` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptConstant="ConstantValue"))`
- L306 _public prototype_ `virtual int32 FuncInterface(const int32 InValue) const override;`
- L307 _public prototype_ `virtual int32 FuncInterfaceChild(const int32 InValue) const override;`
- L308 _public prototype_ `virtual int32 FuncInterfaceOther(const int32 InValue) const override;`

#### class `UPyTestChildObject`  
`class UPyTestChildObject : public UPyTestObject`  
_L315-318_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UPyTestObject`
- desc: Object to allow testing of inheritance on Python wrapped types.

#### class `UDEPRECATED_LegacyPyTestObject`  
`class UDEPRECATED_LegacyPyTestObject : public UPyTestObject`  
_L324-327_
- reflection: `UCLASS(Blueprintable, deprecated, meta=(DeprecationMessage="LegacyPyTestObject is deprecated. Please use PyTestObject instead."))`
- inherits: `UPyTestObject`
- desc: Object to test deprecation of Python wrapped types.

#### class `UPyTestObjectLibrary`  
`class UPyTestObjectLibrary : public UBlueprintFunctionLibrary`  
_L333-342_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that should be hoisted onto the test object in Python.
- L338 _private prototype_ `static bool IsBoolSet(const UPyTestObject* InObj);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptMethod="IsBoolSet"))`
- L341 _private prototype_ `static int32 GetOtherConstantValue();` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptConstant="OtherConstantValue", ScriptConstantHost="/Script/PythonScriptPlugin.PyTestObject"))`

#### class `UPyTestStructDelegate`  
`class UPyTestStructDelegate : public UObject`  
_L348-358_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: This class along with UPyTestVectorDelegate verify that 2 UObjects with the same delegate name/type, do not collide.
- L353 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameCollisionDelegate, const FPyTestStruct&, PyStruct);`
- L357 _public member_ `FOnNameCollisionDelegate OnNameCollisionTestDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Python|Internal")` — Called when a new item is selected in the combobox.

#### class `UPyTestVectorDelegate`  
`class UPyTestVectorDelegate : public UObject`  
_L364-374_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: This class along with UPyTestStructDelegate verify that 2 UObjects with the same delegate name/type, do not collide.
- L369 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameCollisionDelegate, const FVector2D&, Vec);`
- L373 _public member_ `FOnNameCollisionDelegate OnNameCollisionTestDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Python|Internal")` — Called when a new item is selected in the combobox.

#### class `UPyTestTypeHint`  
`class UPyTestTypeHint : public UObject`  
_L383-521_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: Used to verify if the generated Python stub is correctly type-hinted (if type hint is enabled). The stub is generated in the project intermediate folder when the Python developer mode is enabled (Editor preferences). The type hints can be checked in the stub itself or PythonScriptPlugin/Content/Python/test_type_hints.py can be loaded in a Python IDE that supports type checking and look at the code to verify that there is not problems with the types.
- L392 _public prototype_ `UPyTestTypeHint();`
- L393 _public prototype_ `UPyTestTypeHint(bool bParam1, int32 Param2, float Param3, const FString& Param4 = "Hi", const FText& Param5 = FText()`
- L400 _public prototype_ `static FString GetStringConst();` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptConstant="StrConst"))`
- L403 _public prototype_ `static int32 GetIntConst();` — `UFUNCTION(BlueprintPure, Category = "Python|Internal", meta=(ScriptConstant="IntConst"))`
- L410 _public member_ `bool BoolProp = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L413 _public member_ `int32 IntProp = 32;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L416 _public member_ `float FloatProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L419 _public member_ `EPyTestEnum EnumProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L422 _public member_ `FString StringProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L425 _public member_ `FName NameProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L428 _public member_ `FText TextProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L431 _public member_ `TFieldPath<FProperty> FieldPathProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L434 _public member_ `FPyTestStruct StructProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L437 _public member_ `TObjectPtr<UPyTestObject> ObjectProp = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L440 _public member_ `TArray<FString> StrArrayProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L443 _public member_ `TArray<FName> NameArrayProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L446 _public member_ `TArray<FText> TextArrayProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L449 _public member_ `TArray<TObjectPtr<UObject>> ObjectArrayProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L452 _public member_ `TSet<FString> SetProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L455 _public member_ `TMap<int32, FString> MapProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L458 _public member_ `FPyTestDelegate DelegateProp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`
- L461 _public member_ `FPyTestMulticastDelegate MulticastDelegateProp;` — `UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "Python|Internal")`
- L468 _public prototype_ `bool CheckBoolTypeHints(bool bParam1, bool bParam2 = true, bool bParam3 = false);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L471 _public prototype_ `int32 CheckIntegerTypeHints(uint8 Param1, int32 Param2 = 4, int64 Param3 = 5);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L474 _public prototype_ `double CheckFloatTypeHints(float Param1, double Param2, float Param3 = -3.3f, double Param4 = 4.4);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L477 _public prototype_ `EPyTestEnum CheckEnumTypeHints(EPyTestEnum Param1, EPyTestEnum Param2 = EPyTestEnum::One);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L480 _public prototype_ `FString CheckStringTypeHints(const FString& Param1, const FString& Param2 = TEXT("Hi")` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L483 _public prototype_ `FName CheckNameTypeHints(const FName& Param1, const FName& Param2 = FName(TEXT("Hi"))` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L486 _public prototype_ `FText CheckTextTypeHints(const FText& Param1, const FText& Param2 = INVTEXT("Hi")` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L489 _public prototype_ `TFieldPath<FProperty> CheckFieldPathTypeHints(const TFieldPath<FProperty> Param1);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L492 _public prototype_ `FPyTestStruct CheckStructTypeHints(const FPyTestStruct& Param1, const FPyTestStruct& Param2 = FPyTestStruct());` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L495 _public prototype_ `UPyTestObject* CheckObjectTypeHints(const UPyTestObject* Param1, const UPyTestObject* Param4 = nullptr);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L498 _public prototype_ `TArray<FText> CheckArrayTypeHints(const TArray<FString>& Param1, const TArray<FName>& Param2, const TArray<FText>& Param3, const TArray<UObject*>& Param4);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L501 _public prototype_ `TSet<FName> CheckSetTypeHints(const TSet<FString>& Param1, const TSet<FName>& Param2, const TSet<UObject*>& Param3);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L504 _public prototype_ `TMap<FString, UObject*> CheckMapTypeHints(const TMap<int, FString>& Param1, const TMap<int, FName>& Param2, const TMap<int, FText>& Param3, const TMap<int, UObject*>& Param4);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L507 _public prototype_ `FPyTestDelegate& CheckDelegateTypeHints(const FPyTestDelegate& Param1);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L510 _public prototype_ `static bool CheckStaticFunction(bool Param1, int32 Param2, double Param3, const FString& Param4);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L513 _public prototype_ `static int CheckTupleReturnType(UPARAM(ref) FString& InOutString);` — `UFUNCTION(BlueprintPure, Category = "Python|Internal")`
- L520 _public member_ `FPyTestSlateTickDelegate SlateTickDelegate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Python|Internal")`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(int32, FPyTestDelegate, int32, InValue);` — Delegate to allow testing of the various script delegate features that are exposed to Python wrapped types.
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(int32, FPyTestDelegate, int32, InValue);` — Delegate to allow testing of the various script delegate features that are exposed to Python wrapped types.
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPyTestMulticastDelegate, FString, InStr);` — Multicast delegate to allow testing of the various script delegate features that are exposed to Python wrapped types.
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPyTestMulticastDelegate, FString, InStr);` — Multicast delegate to allow testing of the various script delegate features that are exposed to Python wrapped types.
- L24 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FPyTestSlateTickDelegate, float, InDeltaTime);` — Delegate for slate pre/post tick event.
- L24 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FPyTestSlateTickDelegate, float, InDeltaTime);` — Delegate for slate pre/post tick event.
- L353 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameCollisionDelegate, const FPyTestStruct&, PyStruct);`
- L369 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameCollisionDelegate, const FVector2D&, Vec);`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyTestInterface.h` (Private)


#### class `UPyTestInterface`  
`class UPyTestInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface to allow testing of the various UInterface features that are exposed to Python wrapped types.

#### class `IPyTestInterface`  
`class IPyTestInterface`  
_L17-24_
- L23 _public prototype_ `virtual int32 FuncInterface(const int32 InValue) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`

#### class `UPyTestChildInterface`  
`class UPyTestChildInterface : public UPyTestInterface`  
_L30-33_
- reflection: `UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UPyTestInterface`
- desc: Interface to allow testing of inheritance on Python wrapped types.

#### class `IPyTestChildInterface`  
`class IPyTestChildInterface : public IPyTestInterface`  
_L34-41_
- inherits: `IPyTestInterface`
- L40 _public prototype_ `virtual int32 FuncInterfaceChild(const int32 InValue) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`

#### class `UPyTestOtherInterface`  
`class UPyTestOtherInterface : public UInterface`  
_L47-50_
- reflection: `UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface to allow testing of multiple-inheritance on Python wrapped types.

#### class `IPyTestOtherInterface`  
`class IPyTestOtherInterface`  
_L51-58_
- L57 _public prototype_ `virtual int32 FuncInterfaceOther(const int32 InValue) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Python|Internal")`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyUtil.h` (Private)


#### class `PyUtil::FEvalStack`  
`class FEvalStack`  
_L90-108_
- desc: Stack of context information given when calling PyEval_EvalCode
- L100 _public prototype_ `static FEvalStack& Get();`
- L102 _public prototype_ `void PushContext(FEvalContext&& Context);`
- L103 _public prototype_ `void PopContext();`
- L104 _public prototype_ `const FEvalContext* GetCurrentContext() const;`
- L107 _private member_ `TArray<FEvalContext> Stack;`

#### struct `PyUtil::FEvalStack::FEvalContext`  
`struct FEvalContext`  
_L93-98_
- L95 _public member_ `const TCHAR* Context = nullptr;`
- L96 _public member_ `PyObject* GlobalDict = nullptr;`
- L97 _public member_ `PyObject* LocalDict = nullptr;`

#### class `PyUtil::TPropOnScope`  
`template <typename TPropType> class TPropOnScope`  
_L112-239_
- desc: Helper to manage a property pointer that may be potentially owned by a wrapper or stack instance
- L117 _public function_ `static TPropOnScope OwnedReference(TPropType* InProp)`
- L122 _public function_ `static TPropOnScope ExternalReference(TPropType* InProp)`
- L127 _public prototype_ `TPropOnScope() = default;`
- L129 _public function_ `~TPropOnScope()`
- L134 _public prototype_ `TPropOnScope(const TPropOnScope&) = delete;`
- L135 _public prototype_ `TPropOnScope& operator=(const TPropOnScope&) = delete;`
- L141 _public function_ `TPropOnScope(TPropOnScope<TOtherPropType>&& Other)`
- L153 _public function_ `TPropOnScope& operator=(TPropOnScope<TOtherPropType>&& Other)`
- L167 _public function_ `explicit operator bool() const`
- L172 _public function_ `bool IsValid() const`
- L177 _public function_ `operator TPropType*() const`
- L182 _public function_ `TPropType& operator*() const`
- L188 _public function_ `TPropType* operator->() const`
- L194 _public function_ `TPropType* Get() const`
- L199 _public function_ `bool OwnsProp() const`
- L204 _public function_ `TPropType* Release()`
- L212 _public function_ `void Reset()`
- L222 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector)`
- L231 _private function_ `TPropOnScope(TPropType* InProp, const bool InOwnsProp) : Prop(InProp) , bOwnsProp(InOwnsProp)`
- L237 _private member_ `TPropType* Prop = nullptr;`
- L238 _private member_ `bool bOwnsProp = false;`

#### class `PyUtil::FPropValueOnScope`  
`class FPropValueOnScope`  
_L251-268_
- desc: Helper used to hold the value for a property value on the stack
- L254 _public prototype_ `explicit FPropValueOnScope(FConstPropOnScope&& InProp);`
- L255 _public prototype_ `~FPropValueOnScope();`
- L257 _public prototype_ `bool SetValue(PyObject* InPyObj, const TCHAR* InErrorCtxt);`
- L259 _public prototype_ `bool IsValid() const;`
- L261 _public prototype_ `const FProperty* GetProp() const;`
- L263 _public prototype_ `void* GetValue(const int32 InArrayIndex = 0) const;`
- L266 _private member_ `FConstPropOnScope Prop;`
- L267 _private member_ `void* Value = nullptr;`

#### class `PyUtil::FFixedArrayElementOnScope`  
`class FFixedArrayElementOnScope : public FPropValueOnScope`  
_L271-275_
- inherits: `FPropValueOnScope`
- desc: Helper used to hold the value for a single fixed array element on the stack
- L274 _public prototype_ `explicit FFixedArrayElementOnScope(const FProperty* InProp);`

#### class `PyUtil::FArrayElementOnScope`  
`class FArrayElementOnScope : public FPropValueOnScope`  
_L278-282_
- inherits: `FPropValueOnScope`
- desc: Helper used to hold the value for a single array element on the stack
- L281 _public prototype_ `explicit FArrayElementOnScope(const FArrayProperty* InProp);`

#### class `PyUtil::FSetElementOnScope`  
`class FSetElementOnScope : public FPropValueOnScope`  
_L285-289_
- inherits: `FPropValueOnScope`
- desc: Helper used to hold the value for a single set element on the stack
- L288 _public prototype_ `explicit FSetElementOnScope(const FSetProperty* InProp);`

#### class `PyUtil::FMapKeyOnScope`  
`class FMapKeyOnScope : public FPropValueOnScope`  
_L292-296_
- inherits: `FPropValueOnScope`
- desc: Helper used to hold the value for a single map key on the stack
- L295 _public prototype_ `explicit FMapKeyOnScope(const FMapProperty* InProp);`

#### class `PyUtil::FMapValueOnScope`  
`class FMapValueOnScope : public FPropValueOnScope`  
_L299-303_
- inherits: `FPropValueOnScope`
- desc: Helper used to hold the value for a single map value on the stack
- L302 _public prototype_ `explicit FMapValueOnScope(const FMapProperty* InProp);`

#### struct `PyUtil::FFunctionStackOnScope`  
`struct FFunctionStackOnScope`  
_L306-340_
- desc: Helper used to hold the stack data for a UFunction call
- L309 _public function_ `FFunctionStackOnScope(const UFunction* InFunc, void* InStackMemory) : Func(InFunc) , StackMemory(InStackMemory)`
- L319 _public function_ `~FFunctionStackOnScope()`
- L327 _public function_ `const UFunction* GetFunction() const`
- L332 _public function_ `void* GetMemory() const`
- L338 _private member_ `const UFunction* Func = nullptr;`
- L339 _private member_ `void* StackMemory = nullptr;`

#### struct `PyUtil::FPropertyDef`  
`struct FPropertyDef`  
_L345-389_
- desc: Struct containing information needed to construct a property instance
- L347 _public function_ `FPropertyDef() : PropertyClass(nullptr) , PropertySubType(nullptr) , KeyDef() , ValueDef()`
- L355 _public function_ `explicit FPropertyDef(FFieldClass* InPropertyClass, UObject* InPropertySubType = nullptr, TSharedPtr<FPropertyDef> InKeyDef = nullptr, TSharedPtr<FPropertyDef> InValueDef = nullptr) : PropertyClass(InPropertyClass) , PropertySubType(InPropertySubType) , KeyDef(InKeyDef) , ValueDef(InValueDef)`
- L363 _public prototype_ `FPropertyDef(const FProperty* InProperty);`
- L365 _public function_ `FORCEINLINE bool operator==(const FPropertyDef& Other) const`
- L373 _public function_ `FORCEINLINE bool operator!=(const FPropertyDef& Other) const`
- L379 _public member_ `FFieldClass* PropertyClass;` — Class of the property to create
- L382 _public member_ `UObject* PropertySubType;` — Sub-type of the property (the class for object properties, the struct for struct properties, the enum for enum properties, the function for delegate properties)
- L385 _public member_ `TSharedPtr<FPropertyDef> KeyDef;` — Key definition of this property (for map properties)
- L388 _public member_ `TSharedPtr<FPropertyDef> ValueDef;` — Value definition of this property (for array, set, map, and optional properties)

#### class `PyUtil::FOnDiskModules`  
`class FOnDiskModules`  
_L487-518_
- desc: Cache of on-disk Python modules to optimize repeated IsModuleAvailableForImport queries. @note This cache does not automatically watch or update itself from file-system changes after the initial scan!
- L490 _public prototype_ `FOnDiskModules() = default;`
- L492 _public function_ `explicit FOnDiskModules(FString InModuleNameWildcard) : ModuleNameWildcard(MoveTemp(InModuleNameWildcard))`
- L501 _public prototype_ `void AddModules(const TCHAR* InPath);` — Add any module files found under the given path. @note Function is non-recursive, and will find both "{Module}.py" and "{Module}/__init__.py" module layouts.
- L506 _public prototype_ `void RemoveModules(const TCHAR* InPath);` — Remove any module files found under the given path.
- L512 _public prototype_ `bool HasModule(const TCHAR* InModuleName, FString* OutResolvedFile = nullptr) const;` — Check to see whether the given module is known to the cache, optionally returning the actual module file location if it is. @note Will look for both "{Module}.py" and "{Module}/__init__.py" module layouts.
- L515 _private member_ `FString ModuleNameWildcard;`
- L517 _private member_ `TSet<FString> CachedModules;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPython, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPython, Log, All);`
- L23 _macro_ `#define PyCFunctionCast(FUNCPTR) (PyCFunction)(void*)(FUNCPTR)` — Cast a function pointer to PyCFunction (via a void* to avoid a compiler warning)
- L26 _macro_ `#define PyCStrCast(STR) (char*)(void*)(STR)` — Cast a string literal to a char* (via a void* to avoid a compiler warning)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Python` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::Python`)
- L37 _externvar_ `extern bool GIsRunningUserScript;` (scope `UE::Python::Private`) — Set to true whenever we're running user-defined Python script. This is primarily set for FPythonScriptPlugin::EvalString, but should also be set whenever calling back into user-defined Python from other places (eg, PythonGeneratedClass functions, delegates, etc).
- L41 _namespace_ `namespace PyUtil`
- L45 _typedef_ `typedef PyObject FPySliceType;` (scope `PyUtil`)
- L46 _typedef_ `typedef Py_hash_t FPyHashType;` (scope `PyUtil`)
- L47 _typedef_ `typedef PyObject FPyCodeObjectType;` (scope `PyUtil`)
- L55 _typedef_ `typedef wchar_t FPyApiChar;` (scope `PyUtil`) — Character type that this version of Python uses in its API
- L56 _typedef_ `typedef TArray<FPyApiChar> FPyApiBuffer;` (scope `PyUtil`)
- L59 _macro_ `#define TCHARToPyApiChar(InStr) TCHAR_TO_WCHAR(InStr)` — Convert a TCHAR to a transient buffer that can be passed to a Python API that doesn't hold the result
- L61 _externvar_ `extern const FName DefaultPythonPropertyName;` (scope `PyUtil`)
- L64 _prototype_ `FPyApiBuffer TCHARToPyApiBuffer(const TCHAR* InStr);` (scope `PyUtil`) — Convert a TCHAR to a persistent buffer that can be passed to a Python API that does hold the result (you have to keep the buffer around as long as Python needs it)
- L67 _prototype_ `FString PyObjectToUEString(PyObject* InPyObj);` (scope `PyUtil`) — Given a Python object, convert it to a string and extract the string value into an FString
- L70 _prototype_ `FString PyStringToUEString(PyObject* InPyStr);` (scope `PyUtil`) — Given a Python string/unicode object, extract the string value into an FString
- L73 _prototype_ `FString PyObjectToUEStringRepr(PyObject* InPyObj);` (scope `PyUtil`) — Given a Python object, convert it to its string representation (repr) and extract the string value into an FString
- L77 _function_ `template <typename T, typename U> PyObject* PyRichCmp(const T& InLHS, const U& InRHS, const int InOp)` (scope `PyUtil`) — Given two values, perform a rich-comparison and return the result
- L241 _typedef_ `typedef TPropOnScope<FProperty> FPropOnScope;` (scope `PyUtil`)
- L242 _typedef_ `typedef TPropOnScope<const FProperty> FConstPropOnScope;` (scope `PyUtil`)
- L243 _typedef_ `typedef TPropOnScope<FArrayProperty> FArrayPropOnScope;` (scope `PyUtil`)
- L244 _typedef_ `typedef TPropOnScope<const FArrayProperty> FConstArrayPropOnScope;` (scope `PyUtil`)
- L245 _typedef_ `typedef TPropOnScope<FSetProperty> FSetPropOnScope;` (scope `PyUtil`)
- L246 _typedef_ `typedef TPropOnScope<const FSetProperty> FConstSetPropOnScope;` (scope `PyUtil`)
- L247 _typedef_ `typedef TPropOnScope<FMapProperty> FMapPropOnScope;` (scope `PyUtil`)
- L248 _typedef_ `typedef TPropOnScope<const FMapProperty> FConstMapPropOnScope;` (scope `PyUtil`)
- L341 _macro_ `#define PY_UFUNCTION_STACK(NAME, FUNCTION) \`
- L392 _prototype_ `bool CalculatePropertyDef(PyTypeObject* InPyType, FPropertyDef& OutPropertyDef);` (scope `PyUtil`) — Given a Python type, work out what kind of property we would need to create to hold this data
- L395 _prototype_ `bool CalculatePropertyDef(PyObject* InPyObj, FPropertyDef& OutPropertyDef);` (scope `PyUtil`) — Given a Python instance, work out what kind of property we would need to create to hold this data
- L398 _prototype_ `bool IsOptionalPropertyDef(PyObject* InPyObj, PyObject** OutPyValueObj = nullptr);` (scope `PyUtil`) — Given a Python instance, work out whether this will produce an Optional property def, and if so (and requested), get the value that the Optional type will hold
- L401 _prototype_ `FProperty* CreateProperty(const FPropertyDef& InPropertyDef, const int32 InArrayDim = 1, FFieldVariant InOuter = nullptr, const FName InName = DefaultPythonPropertyName);` (scope `PyUtil`) — Given a property definition, create a property instance
- L404 _prototype_ `FProperty* CreateProperty(PyTypeObject* InPyType, const int32 InArrayDim = 1, FFieldVariant InOuter = nullptr, const FName InName = DefaultPythonPropertyName);` (scope `PyUtil`) — Given a Python type, create a compatible property instance
- L407 _prototype_ `FProperty* CreateProperty(PyObject* InPyObj, const int32 InArrayDim = 1, FFieldVariant InOuter = nullptr, const FName InName = DefaultPythonPropertyName);` (scope `PyUtil`) — Given a Python instance, create a compatible property instance
- L410 _prototype_ `bool IsInputParameter(const FProperty* InParam);` (scope `PyUtil`) — Check to see if the given property is an input parameter for a function
- L413 _prototype_ `bool IsOutputParameter(const FProperty* InParam);` (scope `PyUtil`) — Check to see if the given property is an output parameter for a function
- L416 _prototype_ `void ImportDefaultValue(const FProperty* InProp, void* InPropValue, const FString& InDefaultValue);` (scope `PyUtil`) — Import a UHT default value on the given property
- L419 _prototype_ `bool InvokeFunctionCall(UObject* InObj, const UFunction* InFunc, void* InBaseParamsAddr, const TCHAR* InErrorCtxt);` (scope `PyUtil`) — Invoke a function call. Returns false if a Python exception was raised
- L422 _prototype_ `bool InspectFunctionArgs(PyObject* InFunc, TArray<FString>& OutArgNames, TArray<FPyObjectPtr>* OutArgDefaults = nullptr);` (scope `PyUtil`) — Given a Python function, get the names of the arguments along with their default values
- L425 _prototype_ `int ValidateContainerTypeParam(PyObject* InPyObj, FPropertyDef& OutPropDef, const char* InPythonArgName, const TCHAR* InErrorCtxt);` (scope `PyUtil`) — Validate that the given Python object is valid for a 'type' parameter used by containers
- L428 _prototype_ `int ValidateContainerLenParam(PyObject* InPyObj, int32 &OutLen, const char* InPythonArgName, const TCHAR* InErrorCtxt);` (scope `PyUtil`) — Validate that the given Python object is valid for the 'len' parameter used by containers
- L431 _prototype_ `int ValidateContainerIndexParam(const Py_ssize_t InIndex, const Py_ssize_t InLen, const FProperty* InProp, const TCHAR* InErrorCtxt);` (scope `PyUtil`) — Validate that the given index is valid for the container length
- L434 _prototype_ `Py_ssize_t ResolveContainerIndexParam(const Py_ssize_t InIndex, const Py_ssize_t InLen);` (scope `PyUtil`) — Resolve a container index (taking into account negative indices)
- L444 _prototype_ `UObject* NewObject(UClass* InObjClass, UObject* InOuter, const FName InName, UClass* InBaseClass, const TCHAR* InErrorCtxt);` (scope `PyUtil`) — A NewObject wrapper for Python which catches some internal check conditions and raises them as Python exceptions instead. @param InObjClass The class type to create an instance of. @param InOuter The outer object that should host the new instance. @param InName The name that should be given to the new instance (will generate a unique name if None). @param InBaseClass The base class type required for InObjClass (ignored if null).
- L451 _prototype_ `UObject* GetOwnerObject(PyObject* InPyObj);` (scope `PyUtil`) — Given a Python object, try and get the owner Unreal object for the instance. For wrapped objects this is the wrapped instance, for wrapped structs it will attempt to walk through the owner chain to find a wrapped object. @return The owner Unreal object, or null.
- L454 _prototype_ `PyObject* GetPropertyValue(const UStruct* InStruct, const void* InStructData, const FProperty* InProp, const char *InAttributeName, PyObject* InOwnerPyObject, const TCHAR* InErrorCtxt);` (scope `PyUtil`) — Get the current value of the given property from the given struct
- L457 _prototype_ `int SetPropertyValue(const UStruct* InStruct, void* InStructData, PyObject* InValue, const FProperty* InProp, const char *InAttributeName, const FPropertyAccessChangeNotify* InChangeNotify, const uint64 InReadOnlyFlags, const bool InOwnerIsTemplate, const TCHAR* InErrorCtxt, const TConstArrayView<void*>& InArchetypeInstStructData);` (scope `PyUtil`) — Set the current value of the given property from the given struct
- L463 _prototype_ `bool HasLength(PyObject* InObj);` (scope `PyUtil`) — Check to see if the given object implements a length function. @return true if it does, false otherwise.
- L469 _prototype_ `bool HasLength(PyTypeObject* InType);` (scope `PyUtil`) — Check to see if the given type implements a length function. @return true if it does, false otherwise.
- L475 _prototype_ `bool IsMappingType(PyObject* InObj);` (scope `PyUtil`) — Check to see if the given object looks like a mapping type (implements a "keys" function). @return true if it does, false otherwise.
- L481 _prototype_ `bool IsMappingType(PyTypeObject* InType);` (scope `PyUtil`) — Check to see if the given type looks like a mapping type (implements a "keys" function). @return true if it does, false otherwise.
- L523 _prototype_ `FOnDiskModules& GetOnDiskUnrealModulesCache();` (scope `PyUtil`) — Get the cache of on-disk Unreal Python modules ("unreal_*" wildcard).
- L529 _prototype_ `bool IsModuleAvailableForImport(const TCHAR* InModuleName, const FOnDiskModules* InOnDiskModules = nullptr, FString* OutResolvedFile = nullptr);` (scope `PyUtil`) — Test to see whether the given module is available for import (is in the sys.modules table (which includes built-in modules), or is in any known sys.path path). @note This function can't handle dot separated names.
- L535 _prototype_ `bool IsModuleImported(const TCHAR* InModuleName, PyObject** OutPyModule = nullptr);` (scope `PyUtil`) — Test to see whether the given module is available for import (is in the sys.modules table). @note This function can't handle dot separated names.
- L540 _prototype_ `FString GetInterpreterExecutablePath(bool* OutIsEnginePython = nullptr);` (scope `PyUtil`) — Get the path to the Python interpreter executable of the Python SDK this plugin was compiled against.
- L545 _prototype_ `FString GetArchString();` (scope `PyUtil`) — Get the arch-specific path component for potential lib site-packages differences (currently X64/Arm)
- L550 _prototype_ `const TArray<FString>& GetSitePackageSubdirs();` (scope `PyUtil`) — Get static list of site-package subdirs to check
- L555 _prototype_ `void AddSitePackagesPath(const FString& InPath);` (scope `PyUtil`) — Register the given path as a known site-packages path (@see site.addsitedir in Python).
- L560 _prototype_ `void AddSystemPath(const FString& InPath);` (scope `PyUtil`) — Ensure that the given path is on the sys.path list.
- L565 _prototype_ `void RemoveSystemPath(const FString& InPath);` (scope `PyUtil`) — Remove the given path from the sys.path list.
- L570 _prototype_ `TArray<FString> GetSystemPaths();` (scope `PyUtil`) — Get the current sys.path list.
- L575 _prototype_ `FString GetDocString(PyObject* InPyObj);` (scope `PyUtil`) — Get the doc string of the given object (if any).
- L580 _prototype_ `FString GetFriendlyStructValue(const UScriptStruct* InStruct, const void* InStructValue, const uint32 InPortFlags);` (scope `PyUtil`) — Get the friendly value of the given struct that can be used when stringifying struct values for Python.
- L585 _prototype_ `FString GetFriendlyPropertyValue(const FProperty* InProp, const void* InPropValue, const uint32 InPropPortFlags);` (scope `PyUtil`) — Get the friendly value of the given property that can be used when stringifying property values for Python.
- L590 _prototype_ `FString GetFriendlyTypename(PyTypeObject* InPyType);` (scope `PyUtil`) — Get the friendly typename of the given object that can be used in error reporting.
- L596 _prototype_ `FString GetFriendlyTypename(PyObject* InPyObj);` (scope `PyUtil`) — Get the friendly typename of the given object that can be used in error reporting. @note Passing a PyTypeObject returns the name of that object, rather than 'type'.
- L599 _function_ `template <typename T> FString GetFriendlyTypename(T* InPyObj)` (scope `PyUtil`)
- L607 _prototype_ `FString GetCleanTypename(PyTypeObject* InPyType);` (scope `PyUtil`) — Get the clean type name for the given Python type (strip any module information).
- L613 _prototype_ `FString GetCleanTypename(PyObject* InPyObj);` (scope `PyUtil`) — Get the clean type name for the given Python object (strip any module information). @note Passing a PyTypeObject returns the name of that object, rather than 'type'.
- L616 _function_ `template <typename T> FString GetCleanTypename(T* InPyObj)` (scope `PyUtil`)
- L626 _prototype_ `void GetGeneratedTypeOuterAndName(PyTypeObject* InPyType, UObject*& OutOuter, FString& OutName);` (scope `PyUtil`) — Get the generated type outer and name to use for the given Python type. @note This should only be called when immediately processing the generation request from Python, as it relies on getting information from the Python exec stack.
- L631 _prototype_ `FString GetGeneratedTypeDisplayName(PyTypeObject* InPyType);` (scope `PyUtil`) — Get the generated display name to use for the given Python type.
- L636 _prototype_ `FString GetErrorContext(PyTypeObject* InPyType);` (scope `PyUtil`) — Get the error context string of the given object.
- L637 _prototype_ `FString GetErrorContext(PyObject* InPyObj);` (scope `PyUtil`)
- L640 _function_ `template <typename T> FString GetErrorContext(T* InPyObj)` (scope `PyUtil`)
- L646 _prototype_ `void SetPythonError(PyObject* InException, PyTypeObject* InErrorContext, const TCHAR* InErrorMsg);` (scope `PyUtil`) — Set the pending Python error, nesting any other pending error within this one
- L647 _prototype_ `void SetPythonError(PyObject* InException, PyObject* InErrorContext, const TCHAR* InErrorMsg);` (scope `PyUtil`)
- L648 _prototype_ `void SetPythonError(PyObject* InException, const TCHAR* InErrorContext, const TCHAR* InErrorMsg);` (scope `PyUtil`)
- L651 _function_ `template <typename T> void SetPythonError(PyObject* InException, T* InErrorContext, const TCHAR* InErrorMsg)` (scope `PyUtil`)
- L657 _prototype_ `int SetPythonWarning(PyObject* InException, PyTypeObject* InErrorContext, const TCHAR* InErrorMsg);` (scope `PyUtil`) — Set a Python warning (see PyErr_WarnEx for the return value meaning)
- L658 _prototype_ `int SetPythonWarning(PyObject* InException, PyObject* InErrorContext, const TCHAR* InErrorMsg);` (scope `PyUtil`)
- L659 _prototype_ `int SetPythonWarning(PyObject* InException, const TCHAR* InErrorContext, const TCHAR* InErrorMsg);` (scope `PyUtil`)
- L662 _function_ `template <typename T> int SetPythonWarning(PyObject* InException, T* InErrorContext, const TCHAR* InErrorMsg)` (scope `PyUtil`)
- L668 _prototype_ `bool EnableDeveloperWarnings();` (scope `PyUtil`) — Enable developer warnings (eg, deprecation warnings)
- L674 _prototype_ `bool LogPythonError(FString* OutError = nullptr, const bool bInteractive = false);` (scope `PyUtil`) — Log and clear any pending Python error, optionally retrieving the error text that was logged. @return True if Python was in an error state, false otherwise.
- L680 _prototype_ `bool ReThrowPythonError(FString* OutError = nullptr);` (scope `PyUtil`) — Re-throw and clear any pending Python error via FFrame::KismetExecutionMessage, optionally retrieving the error text that was thrown. @return True if Python was in an error state, false otherwise.
- L686 _prototype_ `void CollectGarbage(int32 Generations = 2);` (scope `PyUtil`) — Run the Python garbage collector to clean-up objects that have internal reference cycles that can be broken. @see https://github.com/python/cpython/blob/main/InternalDocs/garbage_collector.md#optimization-generations
- L689 _prototype_ `bool CanTickPython();` (scope `PyUtil`) — Return true if it's currently considered safe to invoke Python from tick handlers

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperArray.h` (Private)


#### struct `FPyWrapperArray`  
`struct FPyWrapperArray : public FPyWrapperBase`  
_L18-109_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed array instances
- L21 _public member_ `FPyWrapperOwnerContext OwnerContext;` — The owner of the wrapped array instance (if any)
- L24 _public member_ `PyUtil::FConstArrayPropOnScope ArrayProp;` — Property describing the array
- L27 _public member_ `void* ArrayInstance;` — Wrapped array instance
- L30 _public prototype_ `static FPyWrapperArray* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L33 _public prototype_ `static void Free(FPyWrapperArray* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L36 _public prototype_ `static int Init(FPyWrapperArray* InSelf, const PyUtil::FPropertyDef& InElementDef);` — Initialize this wrapper (called via tp_init for Python, or directly in C++)
- L39 _public prototype_ `static int Init(FPyWrapperArray* InSelf, const FPyWrapperOwnerContext& InOwnerContext, const FArrayProperty* InProp, void* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L42 _public prototype_ `static void Deinit(FPyWrapperArray* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L45 _public prototype_ `static bool ValidateInternalState(FPyWrapperArray* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L48 _public prototype_ `static FPyWrapperArray* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L51 _public prototype_ `static FPyWrapperArray* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, const PyUtil::FPropertyDef& InElementDef, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L54 _public prototype_ `static Py_ssize_t Len(FPyWrapperArray* InSelf);` — Get the length of this container (equivalent to 'len(x)' in Python)
- L57 _public prototype_ `static PyObject* GetItem(FPyWrapperArray* InSelf, Py_ssize_t InIndex);` — Get the item at index N (equivalent to 'x[N]' in Python, returns new reference)
- L60 _public prototype_ `static int SetItem(FPyWrapperArray* InSelf, Py_ssize_t InIndex, PyObject* InValue);` — Set the item at index N (equivalent to 'x[N] = v' in Python)
- L63 _public prototype_ `static int RemoveAt(FPyWrapperArray* InSelf, Py_ssize_t InIndex);` — Removes the item at index N
- L66 _public prototype_ `static int Contains(FPyWrapperArray* InSelf, PyObject* InValue);` — Does this container have an entry with the given value? (equivalent to 'v in x' in Python)
- L69 _public prototype_ `static FPyWrapperArray* Concat(FPyWrapperArray* InSelf, PyObject* InOther);` — Concatenate the other object to this one, returning a new container (equivalent to 'x + o' in Python, returns new reference)
- L72 _public prototype_ `static int ConcatInplace(FPyWrapperArray* InSelf, PyObject* InOther);` — Concatenate the other object to this one in-place (equivalent to 'x += o' in Python)
- L75 _public prototype_ `static FPyWrapperArray* Repeat(FPyWrapperArray* InSelf, Py_ssize_t InMultiplier);` — Repeat this container by N, returning a new container (equivalent to 'x * N' in Python, returns new reference)
- L78 _public prototype_ `static int RepeatInplace(FPyWrapperArray* InSelf, Py_ssize_t InMultiplier);` — Repeat this container by N in-place (equivalent to 'x *= N' in Python)
- L81 _public prototype_ `static int Append(FPyWrapperArray* InSelf, PyObject* InValue);` — Append the given value to the end this container (equivalent to 'x.append(v)' in Python)
- L84 _public prototype_ `static Py_ssize_t Count(FPyWrapperArray* InSelf, PyObject* InValue);` — Count the number of times that the given value appears in this container (equivalent to 'x.count(v)' in Python)
- L87 _public prototype_ `static Py_ssize_t Index(FPyWrapperArray* InSelf, PyObject* InValue, Py_ssize_t InStartIndex = 0, Py_ssize_t InStopIndex = INDEX_NONE);` — Get the index of the first the given value appears in this container (equivalent to 'x.index(v)' in Python)
- L90 _public prototype_ `static int Insert(FPyWrapperArray* InSelf, Py_ssize_t InIndex, PyObject* InValue);` — Insert the given value into this container at the given index (equivalent to 'x.insert(i, v)' in Python)
- L93 _public prototype_ `static PyObject* Pop(FPyWrapperArray* InSelf, Py_ssize_t InIndex = INDEX_NONE);` — Pop and return the value at the given index (or the end) of this container (equivalent to 'x.pop()' in Python)
- L96 _public prototype_ `static int Remove(FPyWrapperArray* InSelf, PyObject* InValue);` — Remove the given value from this container (equivalent to 'x.remove(v)' in Python)
- L99 _public prototype_ `static int Clear(FPyWrapperArray* InSelf);` — Remove all values from this container (equivalent to 'x.clear()' in Python)
- L102 _public prototype_ `static int Reverse(FPyWrapperArray* InSelf);` — Reverse this container (equivalent to 'x.reverse()' in Python)
- L105 _public prototype_ `static int Sort(FPyWrapperArray* InSelf, PyObject* InKey, bool InReverse);` — Sort this container (equivalent to 'x.sort()' in Python)
- L108 _public prototype_ `static int Resize(FPyWrapperArray* InSelf, Py_ssize_t InLen);` — Resize this container (equivalent to 'x.resize(l)' in Python)

#### struct `FPyWrapperArrayMetaData`  
`struct FPyWrapperArrayMetaData : public FPyWrapperBaseMetaData`  
_L112-122_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed array types
- L116 _public function_ `FPyWrapperArrayMetaData()`
- L121 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector

#### Free symbols / members of external scopes

- L12 _externvar_ `extern PyTypeObject PyWrapperArrayType;` — Python type for FPyWrapperArray
- L15 _prototype_ `void InitializePyWrapperArray(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperArray types and add them to the given Python module
- L124 _typedef_ `typedef TPyPtr<FPyWrapperArray> FPyWrapperArrayPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperBase.h` (Private)


#### struct `FPyWrapperBase`  
`struct FPyWrapperBase`  
_L24-40_
- desc: Base type for all Unreal exposed instances
- L30 _public prototype_ `static FPyWrapperBase* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L33 _public prototype_ `static void Free(FPyWrapperBase* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L36 _public prototype_ `static int Init(FPyWrapperBase* InSelf);` — Initialize this wrapper instance (called via tp_init for Python, or directly in C++)
- L39 _public prototype_ `static void Deinit(FPyWrapperBase* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)

#### struct `FPyWrapperBaseMetaData`  
`struct FPyWrapperBaseMetaData`  
_L53-88_
- desc: Base meta-data for all Unreal exposed types
- L56 _public prototype_ `static void SetMetaData(PyTypeObject* PyType, FPyWrapperBaseMetaData* MetaData);` — Set the meta-data object on the given type
- L59 _public prototype_ `static FPyWrapperBaseMetaData* GetMetaData(PyTypeObject* PyType);` — Get the meta-data object from the given type
- L62 _public prototype_ `static FPyWrapperBaseMetaData* GetMetaData(FPyWrapperBase* Instance);` — Get the meta-data object from the type of the given instance
- L64 _public function_ `FPyWrapperBaseMetaData()`
- L68 _public prototype_ `virtual ~FPyWrapperBaseMetaData() = default;`
- L71 _public prototype_ `virtual FGuid GetTypeId() const = 0;` — Get the ID associated with this meta-data type
- L74 _public function_ `virtual const UField* GetMetaType() const` — Get the reflection meta data type object associated with this wrapper type if there is one or nullptr if not.
- L80 _public function_ `virtual void AddTypeReferencedObjects(FReferenceCollector& Collector)` — Add object references from this type meta-data to the given collector
- L85 _public function_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector)` — Add object references from the given Python object to the given collector

#### class `UPythonResourceOwner`  
`class UPythonResourceOwner : public UInterface`  
_L95-98_
- reflection: `UINTERFACE(MinimalApi)`
- inherits: `UInterface`

#### class `IPythonResourceOwner`  
`class IPythonResourceOwner`  
_L100-110_
- L109 _public prototype_ `virtual void ReleasePythonResources() = 0;` — Release all Python resources owned by this object. Called during Python shutdown to free resources from lingering UObject-based instances.

#### class `UPythonObjectHandle`  
`class UPythonObjectHandle final : public UObject, public IPythonResourceOwner`  
_L129-166_
- reflection: `UCLASS(Transient, BlueprintType)`
- inherits: `UObject,IPythonResourceOwner`
- desc: Handle object to wrap a Python object for use as a UPROPERTY on a UCLASS or USTRUCT. This allows Python generated types to store arbitrary Python objects as native properties, rather than rely on the lifetime of the Python wrapper object to keep a non-property object reference alive. The following functions are available in Python script to interact with these handles: - unreal.create_python_object_handle(obj) -> handle  - Creates an unreal.PythonObjectHandle from a given PyObject. - unreal.resolve_python_object_handle(handle) -> obj - Resolves an unreal.PythonObjectHandle to its PyObject, or None. - unreal.destroy_python_object_handle(handle)        - Destroys an unreal.PythonObjectHandle (clearing its PyObject reference). Manually calling destroy is optional, but can be useful when you need to *immediately* clean-up a reference to the wrapped Python object, rather than wait for UE GC to clean it up at an arbitrary point in the future. This can be used to create a property on Python generated types via the standard unreal.uproperty syntax, eg): MyObjectHandleProperty = unreal.uproperty(unreal.PythonObjectHandle)
- L141 _public prototype_ `static UPythonObjectHandle* Create(PyObject* PyObjPtr);` — Create a handle that wraps the given Python object. @note Will return null if passed a null or None Python object. @param PyObjPtr Python object to wrap, may be null or None.
- L147 _public prototype_ `PyObject* Resolve() const;` — Resolve this handle to its underlying Python object, if any. @return The wrapped object, or None (but not null; borrowed reference).
- L150 _public prototype_ `virtual void BeginDestroy() override;`
- L153 _public prototype_ `virtual void ReleasePythonResources() override;`
- L157 _private member_ `FPyObjectPtr PyObj;` — Wrapped Python object, if any

#### Free symbols / members of external scopes

- L18 _externvar_ `extern PyTypeObject PyWrapperBaseType;` — Python type for FPyWrapperBase
- L21 _prototype_ `void InitializePyWrapperBase(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperBase types and add them to the given Python module
- L42 _macro_ `#define PY_OVERRIDE_GETSET_METADATA(TYPE) \`
- L47 _macro_ `#define PY_METADATA_METHODS(TYPE, GUID) \`
- L90 _typedef_ `typedef TPyPtr<FPyWrapperBase> FPyWrapperBasePtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperBasic.h` (Private)


#### struct `InitializePyWrapperBasicType::FFuncs`  
`struct FFuncs`  
_L12-28_
- L14 _public function_ `static PyObject* New(PyTypeObject* InType, PyObject* InArgs, PyObject* InKwds)`
- L19 _public function_ `static void Dealloc(SelfType* InSelf)`
- L24 _public function_ `static int Init(SelfType* InSelf, PyObject* InArgs, PyObject* InKwds)`

#### struct `TPyWrapperBasic`  
`template <typename ValueType, typename SelfType> struct TPyWrapperBasic : public FPyWrapperBase`  
_L49-121_
- inherits: `FPyWrapperBase`
- desc: Base type for any Unreal exposed simple value instances (that just copy data into Python)
- L52 _public member_ `ValueType Value;` — The wrapped instance
- L55 _public function_ `static SelfType* New(PyTypeObject* InType)` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L66 _public function_ `static void Free(SelfType* InSelf)` — Free this wrapper instance (called via tp_dealloc for Python)
- L75 _public function_ `static int Init(SelfType* InSelf)` — Initialize this wrapper instance (called via tp_init for Python, or directly in C++)
- L90 _public function_ `static int Init(SelfType* InSelf, const ValueType InValue)` — Initialize this wrapper instance to the given value (called directly in C++)
- L105 _public function_ `static void Deinit(SelfType* InSelf)` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L111 _public function_ `static void InitValue(SelfType* InSelf, const ValueType InValue)` — Initialize the value of this wrapper instance (internal: define this in a derived type to "override" InitValue behavior)
- L117 _public function_ `static void DeinitValue(SelfType* InSelf)` — Deinitialize the value of this wrapper instance (internal: define this in a derived type to "override" DeinitValue behavior)

#### Free symbols / members of external scopes

- L10 _function_ `template <typename SelfType> PyTypeObject InitializePyWrapperBasicType(const char* InTypeName, const char* InTypeDoc)`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperDelegate.h` (Private)


#### class `UPythonCallableForDelegate`  
`class UPythonCallableForDelegate : public UObject, public IPythonResourceOwner`  
_L16-53_
- reflection: `UCLASS(HideDropDown)`
- inherits: `UObject,IPythonResourceOwner`
- desc: UObject proxy base used to wrap a callable Python object so that it can be used with an Unreal delegate @note This can't go inside the WITH_PYTHON block due to UHT parsing limitations (it doesn't understand that macro)
- L22 _public member_ `static const FName GeneratedFuncName;` — Name given to the generated function that we should bind to the Unreal delegate
- L31 _public prototype_ `virtual void BeginDestroy() override;`
- L34 _public prototype_ `virtual void ReleasePythonResources() override;`
- L37 _public prototype_ `PyObject* GetCallable() const;` — Get the Python callable object on this instance (borrowed reference)
- L40 _public prototype_ `void SetCallable(PyObject* InCallable);` — Set the Python callable object on this instance
- L44 _private member_ `FPyObjectPtr PyCallable;` — The callable Python callable object this object wraps (if any)
- L50 _public function_ `virtual void ReleasePythonResources() override`

#### struct `TPyWrapperDelegate`  
`template <typename DelegateType> struct TPyWrapperDelegate : public FPyWrapperBase`  
_L68-78_
- inherits: `FPyWrapperBase`
- desc: Base type for all Unreal exposed delegate instances
- L71 _public member_ `FPyWrapperOwnerContext OwnerContext;` — The owner of the wrapped delegate instance (if any)
- L74 _public member_ `DelegateType* DelegateInstance;` — Wrapped delegate instance
- L77 _public member_ `DelegateType InternalDelegateInstance;` — Internal delegate instance (DelegateInstance is set to this when we own the instance)

#### struct `TPyWrapperDelegateMetaData`  
`template <typename WrapperType> struct TPyWrapperDelegateMetaData : public FPyWrapperBaseMetaData`  
_L82-136_
- inherits: `FPyWrapperBaseMetaData`
- desc: Base meta-data for all Unreal exposed delegate types
- L86 _public function_ `TPyWrapperDelegateMetaData() : PythonCallableForDelegateClass(nullptr)`
- L92 _public function_ `static PyGenUtil::FGeneratedWrappedFunction& GetDelegateSignature(PyTypeObject* PyType)` — Get the delegate signature from the given type
- L100 _public function_ `static PyGenUtil::FGeneratedWrappedFunction& GetDelegateSignature(WrapperType* Instance)` — Get the delegate signature from the type of the given instance
- L106 _public function_ `static const UClass* GetPythonCallableForDelegateClass(PyTypeObject* PyType)` — Get the generated class type used to wrap Python callables for this delegate type
- L113 _public function_ `static const UClass* GetPythonCallableForDelegateClass(WrapperType* Instance)` — Get the generated class type used to wrap Python callables for this delegate type
- L119 _public function_ `virtual void AddTypeReferencedObjects(FReferenceCollector& Collector) override` — Add object references from this type meta-data to the given collector
- L126 _public function_ `virtual const UField* GetMetaType() const override` — Get the reflection meta data type object associated with this wrapper type if there is one or nullptr if not.
- L132 _public member_ `PyGenUtil::FGeneratedWrappedFunction DelegateSignature;` — Unreal function representing the signature for the delegate
- L135 _public member_ `TObjectPtr<const UClass> PythonCallableForDelegateClass;` — Generated class type used to wrap Python callables for this delegate type

#### struct `FPyWrapperDelegate`  
`struct FPyWrapperDelegate : public TPyWrapperDelegate<FScriptDelegate>`  
_L139-167_
- inherits: `TPyWrapperDelegate<FScriptDelegate>`
- desc: Type for all Unreal exposed delegate instances
- L142 _public prototype_ `static FPyWrapperDelegate* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L145 _public prototype_ `static void Free(FPyWrapperDelegate* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L148 _public prototype_ `static int Init(FPyWrapperDelegate* InSelf);` — Initialize this wrapper instance (called via tp_init for Python, or directly in C++)
- L151 _public prototype_ `static int Init(FPyWrapperDelegate* InSelf, const FPyWrapperOwnerContext& InOwnerContext, FScriptDelegate* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L154 _public prototype_ `static void Deinit(FPyWrapperDelegate* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L157 _public prototype_ `static bool ValidateInternalState(FPyWrapperDelegate* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L160 _public prototype_ `static FPyWrapperDelegate* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L163 _public prototype_ `static FPyWrapperDelegate* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L166 _public prototype_ `static PyObject* CallDelegate(FPyWrapperDelegate* InSelf, PyObject* InArgs);` — Call the delegate

#### struct `FPyWrapperDelegateMetaData`  
`struct FPyWrapperDelegateMetaData : public TPyWrapperDelegateMetaData<FPyWrapperDelegate>`  
_L170-176_
- inherits: `TPyWrapperDelegateMetaData<FPyWrapperDelegate>`
- desc: Meta-data for all Unreal exposed delegate types
- L175 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector

#### struct `FPyWrapperMulticastDelegate`  
`struct FPyWrapperMulticastDelegate : public TPyWrapperDelegate<FMulticastScriptDelegate>`  
_L179-207_
- inherits: `TPyWrapperDelegate<FMulticastScriptDelegate>`
- desc: Type for all Unreal exposed multicast delegate instances
- L182 _public prototype_ `static FPyWrapperMulticastDelegate* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L185 _public prototype_ `static void Free(FPyWrapperMulticastDelegate* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L188 _public prototype_ `static int Init(FPyWrapperMulticastDelegate* InSelf);` — Initialize this wrapper instance (called via tp_init for Python, or directly in C++)
- L191 _public prototype_ `static int Init(FPyWrapperMulticastDelegate* InSelf, const FPyWrapperOwnerContext& InOwnerContext, FMulticastScriptDelegate* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L194 _public prototype_ `static void Deinit(FPyWrapperMulticastDelegate* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L197 _public prototype_ `static bool ValidateInternalState(FPyWrapperMulticastDelegate* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L200 _public prototype_ `static FPyWrapperMulticastDelegate* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L203 _public prototype_ `static FPyWrapperMulticastDelegate* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L206 _public prototype_ `static PyObject* CallDelegate(FPyWrapperMulticastDelegate* InSelf, PyObject* InArgs);` — Call the delegate

#### struct `FPyWrapperMulticastDelegateMetaData`  
`struct FPyWrapperMulticastDelegateMetaData : public TPyWrapperDelegateMetaData<FPyWrapperMulticastDelegate>`  
_L210-216_
- inherits: `TPyWrapperDelegateMetaData<FPyWrapperMulticastDelegate>`
- desc: Meta-data for all Unreal exposed multicast delegate types
- L215 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector

#### Free symbols / members of external scopes

- L58 _externvar_ `extern PyTypeObject PyWrapperDelegateType;` — Python type for FPyWrapperDelegate
- L61 _externvar_ `extern PyTypeObject PyWrapperMulticastDelegateType;` — Python type for FPyWrapperMulticastDelegate
- L64 _prototype_ `void InitializePyWrapperDelegate(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperDelegate types and add them to the given Python module
- L218 _typedef_ `typedef TPyPtr<FPyWrapperDelegate> FPyWrapperDelegatePtr;`
- L219 _typedef_ `typedef TPyPtr<FPyWrapperMulticastDelegate> FPyWrapperMulticastDelegatePtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperEnum.h` (Private)


#### struct `FPyWrapperEnum`  
`struct FPyWrapperEnum : public FPyWrapperBase`  
_L23-66_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed enum instances (an instance is created for each entry in the enum, before the enum type is locked for creating new instances)
- L26 _public member_ `PyObject* EntryName;` — Name of this enum entry
- L29 _public member_ `PyObject* EntryValue;` — Value of this enum entry
- L32 _public prototype_ `static FPyWrapperEnum* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L35 _public prototype_ `static void Free(FPyWrapperEnum* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L38 _public prototype_ `static int Init(FPyWrapperEnum* InSelf);` — Initialize this wrapper instance (called via tp_init for Python, or directly in C++)
- L41 _public prototype_ `static int Init(FPyWrapperEnum* InSelf, const int64 InEnumEntryValue, const char* InEnumEntryName);` — Initialize this wrapper instance (called directly in C++)
- L44 _public prototype_ `static void Deinit(FPyWrapperEnum* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L47 _public prototype_ `static bool ValidateInternalState(FPyWrapperEnum* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L50 _public prototype_ `static FPyWrapperEnum* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L53 _public prototype_ `static FPyWrapperEnum* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L56 _public prototype_ `static FString GetEnumEntryName(FPyWrapperEnum* InSelf);` — Get the name of the enum entry as a string
- L59 _public prototype_ `static int64 GetEnumEntryValue(FPyWrapperEnum* InSelf);` — Get the value of the enum entry as an int
- L62 _public prototype_ `static FPyWrapperEnum* AddEnumEntry(PyTypeObject* InType, const int64 InEnumEntryValue, const char* InEnumEntryName, const char* InEnumEntryDoc);` — Add the given enum entry on the given enum type (returns borrowed reference)
- L65 _public prototype_ `static FPyWrapperEnum* AddDeprecatedEnumEntry(PyTypeObject* InType, FPyWrapperEnum* InEnumEntry, const char* InEnumEntryName, const char* InEnumEntryDoc);` — Add the given deprecated enum entry on the given enum type (returns borrowed reference)

#### struct `FPyWrapperEnumMetaData`  
`struct FPyWrapperEnumMetaData : public FPyWrapperBaseMetaData`  
_L69-113_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed enum types
- L73 _public prototype_ `FPyWrapperEnumMetaData();`
- L76 _public prototype_ `static UEnum* GetEnum(PyTypeObject* PyType);` — Get the UEnum from the given type
- L79 _public prototype_ `static UEnum* GetEnum(FPyWrapperEnum* Instance);` — Get the UEnum from the type of the given instance
- L82 _public prototype_ `static bool IsEnumDeprecated(PyTypeObject* PyType, FString* OutDeprecationMessage = nullptr);` — Check to see if the enum is deprecated, and optionally return its deprecation message
- L85 _public prototype_ `static bool IsEnumDeprecated(FPyWrapperEnum* Instance, FString* OutDeprecationMessage = nullptr);` — Check to see if the enum is deprecated, and optionally return its deprecation message
- L88 _public prototype_ `static bool IsEnumFinalized(PyTypeObject* PyType);` — Check to see if the enum is finalized
- L91 _public prototype_ `static bool IsEnumFinalized(FPyWrapperEnum* Instance);` — Check to see if the enum is finalized
- L94 _public prototype_ `virtual void AddTypeReferencedObjects(FReferenceCollector& Collector) override;` — Add object references from this type meta-data to the given collector
- L97 _public function_ `virtual const UField* GetMetaType() const override` — Get the reflection meta data type object associated with this wrapper type if there is one or nullptr if not.
- L103 _public member_ `TObjectPtr<UEnum> Enum;` — Unreal enum
- L106 _public member_ `bool bFinalized;` — True if this enum type has been finalized after having all of its entries added to it
- L109 _public member_ `TOptional<FString> DeprecationMessage;` — Set if this enum is deprecated and using it should emit a deprecation warning
- L112 _public member_ `TArray<FPyWrapperEnum*> EnumEntries;` — Array of enum entries in the order they were added (enum entries are stored as borrowed references)

#### class `UPythonGeneratedEnum`  
`class UPythonGeneratedEnum final : public UEnum, public IPythonResourceOwner`  
_L121-182_
- reflection: `UCLASS()`
- inherits: `UEnum,IPythonResourceOwner`
- desc: An Unreal enum that was generated from a Python type
- L129 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L130 _public prototype_ `virtual void BeginDestroy() override;`
- L131 _public function_ `virtual bool IsAsset() const override`
- L137 _public prototype_ `virtual void ReleasePythonResources() override;`
- L140 _public prototype_ `void UnregisterGeneratedType();` — Unregister this type from FPyWrapperTypeRegistry
- L143 _public prototype_ `static UPythonGeneratedEnum* GenerateEnum(PyTypeObject* InPyType);` — Generate an Unreal enum from the given Python type
- L163 _private member_ `FPyTypeObjectPtr PyType;` — Python type this enum was generated from
- L166 _private member_ `TArray<TSharedPtr<FEnumValueDef>> EnumValueDefs;` — Array of values generated for this enum
- L169 _private member_ `FPyWrapperEnumMetaData PyMetaData;` — Meta-data for this generated enum that is applied to the Python type
- L171 _private member_ `TObjectPtr<UObjectRedirector> EnumRedirector;`

#### struct `UPythonGeneratedEnum::FEnumValueDef`  
`struct FEnumValueDef`  
_L147-160_
- desc: Definition data for an Unreal enum value generated from a Python type
- L150 _public member_ `int32 PyIndex = 0;` — Index of the enum value as it was registered with us from the Python
- L153 _public member_ `int64 Value = 0;` — Numeric value of the enum value
- L156 _public member_ `FString Name;` — Name of the enum value
- L159 _public member_ `FString DocString;` — Documentation string of the enum value

#### Free symbols / members of external scopes

- L14 _externvar_ `extern PyTypeObject PyWrapperEnumType;` — Python type for FPyWrapperEnum
- L17 _externvar_ `extern PyTypeObject PyWrapperEnumValueDescrType;` — Python type for FPyWrapperEnumValueDescrObject
- L20 _prototype_ `void InitializePyWrapperEnum(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperEnum types and add them to the given Python module
- L115 _typedef_ `typedef TPyPtr<FPyWrapperEnum> FPyWrapperEnumPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperFieldPath.h` (Private)


#### struct `FPyWrapperFieldPath`  
`struct FPyWrapperFieldPath : public TPyWrapperBasic<FFieldPath, FPyWrapperFieldPath>`  
_L16-31_
- inherits: `TPyWrapperBasic<FFieldPath,FPyWrapperFieldPath>`
- desc: Type for all Unreal exposed FPyWrapperFieldPath instances
- L18 _public typedef_ `typedef TPyWrapperBasic<FFieldPath, FPyWrapperFieldPath> Super;`
- L21 _public prototype_ `static FPyWrapperFieldPath* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L24 _public prototype_ `static FPyWrapperFieldPath* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L27 _public prototype_ `static void InitValue(FPyWrapperFieldPath* InSelf, const FFieldPath& InValue);` — Initialize the value of this wrapper instance (internal)
- L30 _public prototype_ `static void DeinitValue(FPyWrapperFieldPath* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)

#### Free symbols / members of external scopes

- L10 _externvar_ `extern PyTypeObject PyWrapperFieldPathType;` — Python type for FPyWrapperFieldPath
- L13 _prototype_ `void InitializePyWrapperFieldPath(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperFieldPath types and add them to the given Python module
- L33 _typedef_ `typedef TPyPtr<FPyWrapperFieldPath> FPyWrapperFieldPathPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperFixedArray.h` (Private)


#### struct `FPyWrapperFixedArray`  
`struct FPyWrapperFixedArray : public FPyWrapperBase`  
_L18-73_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed fixed-array instances
- L21 _public member_ `FPyWrapperOwnerContext OwnerContext;` — The owner of the wrapped fixed-array instance (if any)
- L24 _public member_ `PyUtil::FConstPropOnScope ArrayProp;` — Property describing the fixed-array
- L27 _public member_ `void* ArrayInstance;` — Wrapped fixed-array instance
- L30 _public prototype_ `static FPyWrapperFixedArray* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L33 _public prototype_ `static void Free(FPyWrapperFixedArray* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L36 _public prototype_ `static int Init(FPyWrapperFixedArray* InSelf, const PyUtil::FPropertyDef& InPropDef, const int32 InLen);` — Initialize this wrapper (called via tp_init for Python, or directly in C++)
- L39 _public prototype_ `static int Init(FPyWrapperFixedArray* InSelf, const FPyWrapperOwnerContext& InOwnerContext, const FProperty* InProp, void* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L42 _public prototype_ `static void Deinit(FPyWrapperFixedArray* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L45 _public prototype_ `static bool ValidateInternalState(FPyWrapperFixedArray* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L48 _public prototype_ `static FPyWrapperFixedArray* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L51 _public prototype_ `static FPyWrapperFixedArray* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, const PyUtil::FPropertyDef& InPropDef, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L54 _public prototype_ `static void* GetItemPtr(FPyWrapperFixedArray* InSelf, Py_ssize_t InIndex);` — Get the raw pointer to the element at index N (negative indexing not supported)
- L57 _public prototype_ `static Py_ssize_t Len(FPyWrapperFixedArray* InSelf);` — Get the length of this container (equivalent to 'len(x)' in Python)
- L60 _public prototype_ `static PyObject* GetItem(FPyWrapperFixedArray* InSelf, Py_ssize_t InIndex);` — Get the item at index N (equivalent to 'x[N]' in Python, returns new reference)
- L63 _public prototype_ `static int SetItem(FPyWrapperFixedArray* InSelf, Py_ssize_t InIndex, PyObject* InValue);` — Set the item at index N (equivalent to 'x[N] = v' in Python)
- L66 _public prototype_ `static int Contains(FPyWrapperFixedArray* InSelf, PyObject* InValue);` — Does this container have an entry with the given value? (equivalent to 'v in x' in Python)
- L69 _public prototype_ `static FPyWrapperFixedArray* Concat(FPyWrapperFixedArray* InSelf, PyObject* InOther);` — Concatenate the other object to this one, returning a new container (equivalent to 'x + o' in Python, returns new reference)
- L72 _public prototype_ `static FPyWrapperFixedArray* Repeat(FPyWrapperFixedArray* InSelf, Py_ssize_t InMultiplier);` — Repeat this container by N, returning a new container (equivalent to 'x * N' in Python, returns new reference)

#### struct `FPyWrapperFixedArrayMetaData`  
`struct FPyWrapperFixedArrayMetaData : public FPyWrapperBaseMetaData`  
_L76-86_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed fixed-array types
- L80 _public function_ `FPyWrapperFixedArrayMetaData()`
- L85 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector

#### Free symbols / members of external scopes

- L12 _externvar_ `extern PyTypeObject PyWrapperFixedArrayType;` — Python type for FPyWrapperFixedArray
- L15 _prototype_ `void InitializePyWrapperFixedArray(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperFixedArray types and add them to the given Python module
- L88 _typedef_ `typedef TPyPtr<FPyWrapperFixedArray> FPyWrapperFixedArrayPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperMap.h` (Private)


#### struct `FPyWrapperMap`  
`struct FPyWrapperMap : public FPyWrapperBase`  
_L18-94_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed map instances
- L21 _public member_ `FPyWrapperOwnerContext OwnerContext;` — The owner of the wrapped map instance (if any)
- L24 _public member_ `PyUtil::FConstMapPropOnScope MapProp;` — Property describing the map
- L27 _public member_ `void* MapInstance;` — Wrapped map instance
- L30 _public prototype_ `static FPyWrapperMap* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L33 _public prototype_ `static void Free(FPyWrapperMap* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L36 _public prototype_ `static int Init(FPyWrapperMap* InSelf, const PyUtil::FPropertyDef& InKeyDef, const PyUtil::FPropertyDef& InValueDef);` — Initialize this wrapper (called via tp_init for Python, or directly in C++)
- L39 _public prototype_ `static int Init(FPyWrapperMap* InSelf, const FPyWrapperOwnerContext& InOwnerContext, const FMapProperty* InProp, void* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L42 _public prototype_ `static void Deinit(FPyWrapperMap* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L45 _public prototype_ `static bool ValidateInternalState(FPyWrapperMap* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L48 _public prototype_ `static FPyWrapperMap* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L51 _public prototype_ `static FPyWrapperMap* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, const PyUtil::FPropertyDef& InKeyDef, const PyUtil::FPropertyDef& InValueDef, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L54 _public prototype_ `static Py_ssize_t Len(FPyWrapperMap* InSelf);` — Get the length of this container (equivalent to 'len(x)' in Python)
- L57 _public prototype_ `static PyObject* GetItem(FPyWrapperMap* InSelf, PyObject* InKey);` — Get the item with key K (equivalent to 'x[K]' in Python, returns new reference)
- L60 _public prototype_ `static PyObject* GetItem(FPyWrapperMap* InSelf, PyObject* InKey, PyObject* InDefault);` — Get the item with key K (equivalent to 'x.get(K, D)' in Python, returns new reference)
- L63 _public prototype_ `static int SetItem(FPyWrapperMap* InSelf, PyObject* InKey, PyObject* InValue);` — Set the item with key K (equivalent to 'x[K] = v' in Python)
- L66 _public prototype_ `static PyObject* SetDefault(FPyWrapperMap* InSelf, PyObject* InKey, PyObject* InValue);` — Set the item with key K if K isn't in the map and return the value of K (equivalent to 'x.setdefault(K, v)' in Python)
- L69 _public prototype_ `static int Contains(FPyWrapperMap* InSelf, PyObject* InKey);` — Does this container have an entry with the given value? (equivalent to 'v in x' in Python)
- L72 _public prototype_ `static int Clear(FPyWrapperMap* InSelf);` — Remove all values from this container (equivalent to 'x.clear()' in Python)
- L75 _public prototype_ `static PyObject* Pop(FPyWrapperMap* InSelf, PyObject* InKey, PyObject* InDefault);` — Remove and return the value for key K if present, otherwise return the default, or raise KeyError if no default is given (equivalent to 'x.popitem()' in Python, returns new reference)
- L78 _public prototype_ `static PyObject* PopItem(FPyWrapperMap* InSelf);` — Remove and return an arbitrary pair from this map (equivalent to 'x.popitem()' in Python, returns new reference)
- L81 _public prototype_ `static int Update(FPyWrapperMap* InSelf, PyObject* InOther);` — Update this map from another (equivalent to 'x.update(o)' in Python)
- L84 _public prototype_ `static PyObject* Items(FPyWrapperMap* InSelf);` — Get a Python list containing the items from this map as key->value pairs
- L87 _public prototype_ `static PyObject* Keys(FPyWrapperMap* InSelf);` — Get a Python list containing the keys from this map
- L90 _public prototype_ `static PyObject* Values(FPyWrapperMap* InSelf);` — Get a Python list containing the values from this map
- L93 _public prototype_ `static FPyWrapperMap* FromKeys(PyObject* InSequence, PyObject* InValue, PyTypeObject* InType);` — Create a new map of keys from the sequence using the given value (types are inferred)

#### struct `FPyWrapperMapMetaData`  
`struct FPyWrapperMapMetaData : public FPyWrapperBaseMetaData`  
_L97-107_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed map types
- L101 _public function_ `FPyWrapperMapMetaData()`
- L106 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector

#### Free symbols / members of external scopes

- L12 _externvar_ `extern PyTypeObject PyWrapperMapType;` — Python type for FPyWrapperMap
- L15 _prototype_ `void InitializePyWrapperMap(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperMap types and add them to the given Python module
- L109 _typedef_ `typedef TPyPtr<FPyWrapperMap> FPyWrapperMapPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperMath.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `void InitializePyWrapperMath(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperMath types and add them to the given Python module

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperName.h` (Private)


#### struct `FPyWrapperName`  
`struct FPyWrapperName : public TPyWrapperBasic<FName, FPyWrapperName>`  
_L16-31_
- inherits: `TPyWrapperBasic<FName,FPyWrapperName>`
- desc: Type for all Unreal exposed FName instances
- L18 _public typedef_ `typedef TPyWrapperBasic<FName, FPyWrapperName> Super;`
- L21 _public prototype_ `static FPyWrapperName* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L24 _public prototype_ `static FPyWrapperName* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L27 _public prototype_ `static void InitValue(FPyWrapperName* InSelf, const FName InValue);` — Initialize the value of this wrapper instance (internal)
- L30 _public prototype_ `static void DeinitValue(FPyWrapperName* InSelf);` — Deinitialize the value of this wrapper instance (internal)

#### Free symbols / members of external scopes

- L10 _externvar_ `extern PyTypeObject PyWrapperNameType;` — Python type for FPyWrapperName
- L13 _prototype_ `void InitializePyWrapperName(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the FPyWrapperName types and add them to the given Python module
- L33 _typedef_ `typedef TPyPtr<FPyWrapperName> FPyWrapperNamePtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperObject.h` (Private)


#### struct `FPyWrapperObject`  
`struct FPyWrapperObject : public FPyWrapperBase`  
_L22-104_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed object instances
- L25 _public member_ `TObjectPtr<UObject> ObjectInstance;` — Wrapped object instance
- L28 _public prototype_ `static FPyWrapperObject* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L31 _public prototype_ `static void Free(FPyWrapperObject* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L34 _public prototype_ `static int Init(FPyWrapperObject* InSelf, UObject* InValue);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L37 _public prototype_ `static void Deinit(FPyWrapperObject* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L40 _public prototype_ `static bool ValidateInternalState(FPyWrapperObject* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L43 _public prototype_ `static FPyWrapperObject* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L46 _public prototype_ `static FPyWrapperObject* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L49 _public prototype_ `static PyObject* GetPropertyValue(FPyWrapperObject* InSelf, const PyGenUtil::FGeneratedWrappedProperty& InPropDef, const char* InPythonAttrName);` — Get a property value from this instance (called via generated code)
- L52 _public prototype_ `static int SetPropertyValue(FPyWrapperObject* InSelf, PyObject* InValue, const PyGenUtil::FGeneratedWrappedProperty& InPropDef, const char* InPythonAttrName, const EPropertyAccessChangeNotifyMode InNotifyMode = EPropertyAccessChangeNotifyMode::Never, const uint64 InReadOnlyFlags = PropertyAccessUtil::RuntimeReadOnlyFlags);` — Set a property value on this instance (called via generated code)
- L55 _public prototype_ `static PyObject* CallGetterFunction(FPyWrapperObject* InSelf, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef);` — Call a named getter function on this class using the given instance (called via generated code)
- L58 _public prototype_ `static int CallSetterFunction(FPyWrapperObject* InSelf, PyObject* InValue, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef);` — Call a named setter function on this class using the given instance (called via generated code)
- L61 _public prototype_ `static PyObject* CallFunction(PyTypeObject* InType, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const char* InPythonFuncName);` — Call a function on this class (called via generated code)
- L64 _public prototype_ `static PyObject* CallFunction(PyTypeObject* InType, PyObject* InArgs, PyObject* InKwds, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const char* InPythonFuncName);` — Call a function on this class (called via generated code)
- L67 _public prototype_ `static PyObject* CallFunction(FPyWrapperObject* InSelf, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const char* InPythonFuncName);` — Call a function on this class using the given instance (called via generated code)
- L70 _public prototype_ `static PyObject* CallFunction(FPyWrapperObject* InSelf, PyObject* InArgs, PyObject* InKwds, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const char* InPythonFuncName);` — Call a function on this class using the given instance (called via generated code)
- L73 _public prototype_ `static PyObject* CallFunction_Impl(UObject* InObj, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const char* InPythonFuncName, const TCHAR* InErrorCtxt);` — Call a function on this instance (CallFunction internal use only)
- L76 _public prototype_ `static PyObject* CallFunction_Impl(UObject* InObj, PyObject* InArgs, PyObject* InKwds, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const char* InPythonFuncName, const TCHAR* InErrorCtxt);` — Call a function on this instance (CallFunction internal use only)
- L79 _public prototype_ `static PyObject* CallClassMethodNoArgs_Impl(PyTypeObject* InType, void* InClosure);` — Implementation of the "call" logic for a Python class method with no arguments (internal Python bindings use only)
- L82 _public prototype_ `static PyObject* CallClassMethodWithArgs_Impl(PyTypeObject* InType, PyObject* InArgs, PyObject* InKwds, void* InClosure);` — Implementation of the "call" logic for a Python class method with arguments (internal Python bindings use only)
- L85 _public prototype_ `static PyObject* CallMethodNoArgs_Impl(FPyWrapperObject* InSelf, void* InClosure);` — Implementation of the "call" logic for a Python method with no arguments (internal Python bindings use only)
- L88 _public prototype_ `static PyObject* CallMethodWithArgs_Impl(FPyWrapperObject* InSelf, PyObject* InArgs, PyObject* InKwds, void* InClosure);` — Implementation of the "call" logic for a Python method with arguments (internal Python bindings use only)
- L91 _public prototype_ `static PyObject* CallDynamicFunction_Impl(FPyWrapperObject* InSelf, PyObject* InArgs, PyObject* InKwds, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const PyGenUtil::FGeneratedWrappedMethodParameter& InSelfParam, const char* InPythonFuncName);` — Call a dynamic function on this instance (CallFunction internal use only)
- L94 _public prototype_ `static PyObject* CallDynamicMethodNoArgs_Impl(FPyWrapperObject* InSelf, void* InClosure);` — Implementation of the "call" logic for a dynamic Python method with no arguments (internal Python bindings use only)
- L97 _public prototype_ `static PyObject* CallDynamicMethodWithArgs_Impl(FPyWrapperObject* InSelf, PyObject* InArgs, PyObject* InKwds, void* InClosure);` — Implementation of the "call" logic for a dynamic Python method with arguments (internal Python bindings use only)
- L100 _public prototype_ `static PyObject* Getter_Impl(FPyWrapperObject* InSelf, void* InClosure);` — Implementation of the "getter" logic for a Python descriptor reading from an object property (internal Python bindings use only)
- L103 _public prototype_ `static int Setter_Impl(FPyWrapperObject* InSelf, PyObject* InValue, void* InClosure);` — Implementation of the "setter" logic for a Python descriptor writing to an object property (internal Python bindings use only)

#### struct `FPyWrapperObjectMetaData`  
`struct FPyWrapperObjectMetaData : public FPyWrapperBaseMetaData`  
_L107-181_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed object types
- L111 _public function_ `FPyWrapperObjectMetaData() : Class(nullptr)`
- L117 _public prototype_ `static UClass* GetClass(PyTypeObject* PyType);` — Get the UClass from the given type
- L120 _public prototype_ `static UClass* GetClass(FPyWrapperObject* Instance);` — Get the UClass from the type of the given instance
- L123 _public prototype_ `static FName ResolvePropertyName(PyTypeObject* PyType, const FName InPythonPropertyName);` — Resolve the original property name of a Python property from the given type
- L126 _public prototype_ `static FName ResolvePropertyName(FPyWrapperObject* Instance, const FName InPythonPropertyName);` — Resolve the original property name of a Python property of the given instance
- L129 _public prototype_ `static bool IsPropertyDeprecated(PyTypeObject* PyType, const FName InPythonPropertyName, FString* OutDeprecationMessage = nullptr);` — Check to see if the given Python property is deprecated, and optionally return its deprecation message
- L132 _public prototype_ `static bool IsPropertyDeprecated(FPyWrapperObject* Instance, const FName InPythonPropertyName, FString* OutDeprecationMessage = nullptr);` — Check to see if the given Python property is deprecated, and optionally return its deprecation message
- L135 _public prototype_ `static FName ResolveFunctionName(PyTypeObject* PyType, const FName InPythonMethodName);` — Resolve the original function name of a Python method from the given type
- L138 _public prototype_ `static FName ResolveFunctionName(FPyWrapperObject* Instance, const FName InPythonMethodName);` — Resolve the original function name of a Python method of the given instance
- L141 _public prototype_ `static bool IsFunctionDeprecated(PyTypeObject* PyType, const FName InPythonMethodName, FString* OutDeprecationMessage = nullptr);` — Check to see if the given Python method is deprecated, and optionally return its deprecation message
- L144 _public prototype_ `static bool IsFunctionDeprecated(FPyWrapperObject* Instance, const FName InPythonMethodName, FString* OutDeprecationMessage = nullptr);` — Check to see if the given Python method is deprecated, and optionally return its deprecation message
- L147 _public prototype_ `static bool IsClassDeprecated(PyTypeObject* PyType, FString* OutDeprecationMessage = nullptr);` — Check to see if the class is deprecated, and optionally return its deprecation message
- L150 _public prototype_ `static bool IsClassDeprecated(FPyWrapperObject* Instance, FString* OutDeprecationMessage = nullptr);` — Check to see if the class is deprecated, and optionally return its deprecation message
- L153 _public prototype_ `virtual void AddTypeReferencedObjects(FReferenceCollector& Collector) override;` — Add object references from this type meta-data to the given collector
- L156 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector
- L159 _public function_ `virtual const UField* GetMetaType() const override` — Get the reflection meta data type object associated with this wrapper type if there is one or nullptr if not.
- L165 _public member_ `TObjectPtr<UClass> Class;` — Unreal class
- L168 _public member_ `TMap<FName, FName> PythonProperties;` — Map of properties that were exposed to Python mapped to their original name
- L171 _public member_ `TMap<FName, FString> PythonDeprecatedProperties;` — Map of properties that were exposed to Python mapped to their deprecation message (if deprecated)
- L174 _public member_ `TMap<FName, FName> PythonMethods;` — Map of methods that were exposed to Python mapped to their original name
- L177 _public member_ `TMap<FName, FString> PythonDeprecatedMethods;` — Map of methods that were exposed to Python mapped to their deprecation message (if deprecated)
- L180 _public member_ `TOptional<FString> DeprecationMessage;` — Set if this class is deprecated and using it should emit a deprecation warning

#### class `UPythonGeneratedClass`  
`class UPythonGeneratedClass final : public UClass, public IPythonResourceOwner`  
_L189-256_
- reflection: `UCLASS(Transient)`
- inherits: `UClass,IPythonResourceOwner`
- desc: An Unreal class that was generated from a Python type
- L197 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L198 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L199 _public prototype_ `virtual void BeginDestroy() override;`
- L200 _public function_ `virtual bool IsAsset() const override`
- L206 _public prototype_ `virtual void PostInitInstance(UObject* InObj, FObjectInstancingGraph* InstanceGraph) override;`
- L209 _public prototype_ `virtual void ReleasePythonResources() override;`
- L212 _public prototype_ `void UnregisterGeneratedType();` — Unregister this type from FPyWrapperTypeRegistry
- L214 _public prototype_ `virtual bool IsFunctionImplementedInScript(FName InFunctionName) const override;`
- L217 _public prototype_ `static UPythonGeneratedClass* GenerateClass(PyTypeObject* InPyType);` — Generate an Unreal class from the given Python type
- L220 _public prototype_ `static bool ReparentDerivedClasses(UPythonGeneratedClass* InOldParent, UPythonGeneratedClass* InNewParent);` — Generate an Unreal class for all child classes of the old parent using the new parent class as their base (also update the Python types)
- L223 _public prototype_ `static UPythonGeneratedClass* ReparentClass(UPythonGeneratedClass* InOldClass, UPythonGeneratedClass* InNewParent);` — Generate an Unreal class based on the given class, but using the given parent class (also update the Python type)
- L230 _private member_ `FPyTypeObjectPtr PyType;` — Python type this class was generated from
- L233 _private member_ `FPyObjectPtr PyPostInitFunction;` — PostInit function for this class
- L236 _private member_ `TArray<TSharedPtr<PyGenUtil::FPropertyDef>> PropertyDefs;` — Array of properties generated for this class
- L239 _private member_ `TArray<TSharedPtr<PyGenUtil::FFunctionDef>> FunctionDefs;` — Array of functions generated for this class
- L242 _private member_ `FPyWrapperObjectMetaData PyMetaData;` — Meta-data for this generated class that is applied to the Python type
- L244 _private member_ `TObjectPtr<UObjectRedirector> ClassRedirector;`
- L245 _private member_ `TObjectPtr<UObjectRedirector> CDORedirector;`

#### Free symbols / members of external scopes

- L16 _externvar_ `extern PyTypeObject PyWrapperObjectType;` — Python type for FPyWrapperObject
- L19 _prototype_ `void InitializePyWrapperObject(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperObject types and add them to the given Python module
- L183 _typedef_ `typedef TPyPtr<FPyWrapperObject> FPyWrapperObjectPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperOwnerContext.h` (Private)


#### class `FPyWrapperOwnerContext`  
`class FPyWrapperOwnerContext`  
_L13-52_
- desc: Owner context information for wrapped types
- L17 _public prototype_ `FPyWrapperOwnerContext();` — Default constructor
- L20 _public prototype_ `explicit FPyWrapperOwnerContext(PyObject* InOwner, const FProperty* InProp = nullptr);` — Construct this context from the given Python object and optional property (will create a new reference to the given object)
- L23 _public prototype_ `explicit FPyWrapperOwnerContext(const FPyObjectPtr& InOwner, const FProperty* InProp = nullptr);` — Construct this context from the given Python object and optional property
- L26 _public prototype_ `void Reset();` — Reset this context back to its default state
- L29 _public prototype_ `bool HasOwner() const;` — Check to see if this context has an owner set
- L32 _public prototype_ `PyObject* GetOwnerObject() const;` — Get the Python object that owns the instance being wrapped (if any, borrowed reference)
- L35 _public prototype_ `const FProperty* GetOwnerProperty() const;` — Get the property on the owner object that owns the instance being wrapped (if known)
- L38 _public prototype_ `void AssertValidConversionMethod(const EPyConversionMethod InMethod) const;` — Assert that the given conversion method is valid for this owner context
- L41 _public prototype_ `TUniquePtr<FPropertyAccessChangeNotify> BuildChangeNotify(const EPropertyAccessChangeNotifyMode InNotifyMode) const;` — Build the property change notify that corresponds to this owner context, or null if this owner context shouldn't emit change notifications
- L44 _public prototype_ `UObject* FindChangeNotifyObject() const;` — Walk the owner context chain to find a UObject owner instance that should receive change notifications (if any)
- L48 _private member_ `FPyObjectPtr OwnerObject;` — The Python object that owns the instance being wrapped (if any)
- L51 _private member_ `const FProperty* OwnerProperty;` — The property on the owner object that owns the instance being wrapped (if known)

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperSet.h` (Private)


#### struct `FPyWrapperSet`  
`struct FPyWrapperSet : public FPyWrapperBase`  
_L18-106_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed set instances
- L21 _public member_ `FPyWrapperOwnerContext OwnerContext;` — The owner of the wrapped set instance (if any)
- L24 _public member_ `PyUtil::FConstSetPropOnScope SetProp;` — Property describing the set
- L27 _public member_ `void* SetInstance;` — Wrapped set instance
- L30 _public prototype_ `static FPyWrapperSet* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L33 _public prototype_ `static void Free(FPyWrapperSet* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L36 _public prototype_ `static int Init(FPyWrapperSet* InSelf, const PyUtil::FPropertyDef& InElementDef);` — Initialize this wrapper (called via tp_init for Python, or directly in C++)
- L39 _public prototype_ `static int Init(FPyWrapperSet* InSelf, const FPyWrapperOwnerContext& InOwnerContext, const FSetProperty* InProp, void* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L42 _public prototype_ `static void Deinit(FPyWrapperSet* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L45 _public prototype_ `static bool ValidateInternalState(FPyWrapperSet* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L48 _public prototype_ `static FPyWrapperSet* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L51 _public prototype_ `static FPyWrapperSet* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, const PyUtil::FPropertyDef& InElementDef, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L54 _public prototype_ `static Py_ssize_t Len(FPyWrapperSet* InSelf);` — Get the length of this container (equivalent to 'len(x)' in Python)
- L57 _public prototype_ `static int Contains(FPyWrapperSet* InSelf, PyObject* InValue);` — Does this container have an entry with the given value? (equivalent to 'v in x' in Python)
- L60 _public prototype_ `static int Add(FPyWrapperSet* InSelf, PyObject* InValue);` — Add the given value to this container (equivalent to 'x.add(v)' in Python)
- L63 _public prototype_ `static int Discard(FPyWrapperSet* InSelf, PyObject* InValue);` — Remove the given value from this container, doing nothing if it's not present (equivalent to 'x.discard(v)' in Python)
- L66 _public prototype_ `static int Remove(FPyWrapperSet* InSelf, PyObject* InValue);` — Remove the given value from this container (equivalent to 'x.remove(v)' in Python)
- L69 _public prototype_ `static PyObject* Pop(FPyWrapperSet* InSelf);` — Remove and return an arbitrary value from this container (equivalent to 'x.pop()' in Python, returns new reference)
- L72 _public prototype_ `static int Clear(FPyWrapperSet* InSelf);` — Remove all values from this container (equivalent to 'x.clear()' in Python)
- L75 _public prototype_ `static FPyWrapperSet* Difference(FPyWrapperSet* InSelf, PyObject* InOthers);` — Return the difference between this container and the other iterables passed for comparison (equivalent to 'x.difference(...)' in Python, returns new reference)
- L78 _public prototype_ `static int DifferenceUpdate(FPyWrapperSet* InSelf, PyObject* InOthers);` — Update this container to be the difference between itself and the other iterables passed for comparison (equivalent to 'x.difference_update(...)' in Python)
- L81 _public prototype_ `static FPyWrapperSet* Intersection(FPyWrapperSet* InSelf, PyObject* InOthers);` — Return the intersection between this container and the other iterables passed for comparison (equivalent to 'x.intersection(...)' in Python, returns new reference)
- L84 _public prototype_ `static int IntersectionUpdate(FPyWrapperSet* InSelf, PyObject* InOthers);` — Update this container to be the intersection between this container and the other iterables passed for comparison (equivalent to 'x.intersection_update(...)' in Python)
- L87 _public prototype_ `static FPyWrapperSet* SymmetricDifference(FPyWrapperSet* InSelf, PyObject* InOther);` — Return the symmetric difference between this container and another (equivalent to 'x.symmetric_difference(other)' in Python, returns new reference)
- L90 _public prototype_ `static int SymmetricDifferenceUpdate(FPyWrapperSet* InSelf, PyObject* InOther);` — Update this container to be the symmetric difference between this container and another (equivalent to 'x.symmetric_difference_update(other)' in Python)
- L93 _public prototype_ `static FPyWrapperSet* Union(FPyWrapperSet* InSelf, PyObject* InOthers);` — Return the union between this container and the other iterables passed for comparison (equivalent to 'x.union(...)' in Python, returns new reference)
- L96 _public prototype_ `static int Update(FPyWrapperSet* InSelf, PyObject* InOthers);` — Update this container to be the union between this container and the other iterables passed for comparison (equivalent to 'x.update(...)' in Python)
- L99 _public prototype_ `static int IsDisjoint(FPyWrapperSet* InSelf, PyObject* InOther);` — Return true if there is a null intersection between this container and another (equivalent to 'x.isdisjoint(other)' in Python)
- L102 _public prototype_ `static int IsSubset(FPyWrapperSet* InSelf, PyObject* InOther);` — Return true if there is another container contains this (equivalent to 'x.issubset(other)' in Python)
- L105 _public prototype_ `static int IsSuperset(FPyWrapperSet* InSelf, PyObject* InOther);` — Return true if there this container contains another (equivalent to 'x.issuperset(other)' in Python)

#### struct `FPyWrapperSetMetaData`  
`struct FPyWrapperSetMetaData : public FPyWrapperBaseMetaData`  
_L109-119_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed set types
- L113 _public function_ `FPyWrapperSetMetaData()`
- L118 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector

#### Free symbols / members of external scopes

- L12 _externvar_ `extern PyTypeObject PyWrapperSetType;` — Python type for FPyWrapperSet
- L15 _prototype_ `void InitializePyWrapperSet(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperSet types and add them to the given Python module
- L121 _typedef_ `typedef TPyPtr<FPyWrapperSet> FPyWrapperSetPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperStruct.h` (Private)


#### struct `FPyWrapperStruct`  
`struct FPyWrapperStruct : public FPyWrapperBase`  
_L25-112_
- inherits: `FPyWrapperBase`
- desc: Type for all Unreal exposed struct instances
- L28 _public member_ `FPyWrapperOwnerContext OwnerContext;` — The owner of the wrapped struct instance (if any)
- L31 _public member_ `TObjectPtr<UScriptStruct> ScriptStruct;` — Struct type of this instance
- L34 _public member_ `void* StructInstance;` — Wrapped struct instance
- L37 _public prototype_ `static FPyWrapperStruct* New(PyTypeObject* InType);` — New this wrapper instance (called via tp_new for Python, or directly in C++)
- L40 _public prototype_ `static void Free(FPyWrapperStruct* InSelf);` — Free this wrapper instance (called via tp_dealloc for Python)
- L43 _public prototype_ `static int Init(FPyWrapperStruct* InSelf);` — Initialize this wrapper instance (called via tp_init for Python, or directly in C++)
- L46 _public prototype_ `static int Init(FPyWrapperStruct* InSelf, const FPyWrapperOwnerContext& InOwnerContext, UScriptStruct* InStruct, void* InValue, const EPyConversionMethod InConversionMethod);` — Initialize this wrapper instance to the given value (called via tp_init for Python, or directly in C++)
- L49 _public prototype_ `static void Deinit(FPyWrapperStruct* InSelf);` — Deinitialize this wrapper instance (called via Init and Free to restore the instance to its New state)
- L52 _public prototype_ `static bool ValidateInternalState(FPyWrapperStruct* InSelf);` — Called to validate the internal state of this wrapper instance prior to operating on it (should be called by all functions that expect to operate on an initialized type; will set an error state on failure)
- L55 _public prototype_ `static FPyWrapperStruct* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L58 _public prototype_ `static FPyWrapperStruct* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L61 _public prototype_ `static int MakeStruct(FPyWrapperStruct* InSelf, PyObject* InArgs, PyObject* InKwds);` — "Make" this struct from the given arguments, either using a custom make function or by setting the named property values on this instance (called via generated code)
- L64 _public prototype_ `static PyObject* BreakStruct(FPyWrapperStruct* InSelf);` — "Break" this struct into a tuple, either using a custom break function or by getting each property value on this instance (called via generated code)
- L67 _public prototype_ `static PyObject* GetPropertyValue(FPyWrapperStruct* InSelf, const PyGenUtil::FGeneratedWrappedProperty& InPropDef, const char* InPythonAttrName);` — Get a property value from this instance (called via generated code)
- L70 _public prototype_ `static int SetPropertyValue(FPyWrapperStruct* InSelf, PyObject* InValue, const PyGenUtil::FGeneratedWrappedProperty& InPropDef, const char* InPythonAttrName, const EPropertyAccessChangeNotifyMode InNotifyMode = EPropertyAccessChangeNotifyMode::Never, const uint64 InReadOnlyFlags = PropertyAccessUtil::RuntimeReadOnlyFlags);` — Set a property value on this instance (called via generated code)
- L73 _public prototype_ `static int CallMakeFunction_Impl(FPyWrapperStruct* InSelf, PyObject* InArgs, PyObject* InKwds, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef);` — Call a make function on this instance (MakeStruct internal use only)
- L76 _public prototype_ `static PyObject* CallBreakFunction_Impl(FPyWrapperStruct* InSelf, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef);` — Call a break function on this instance (BreakStruct internal use only)
- L79 _public prototype_ `static PyObject* CallDynamicFunction_Impl(FPyWrapperStruct* InSelf, PyObject* InArgs, PyObject* InKwds, const PyGenUtil::FGeneratedWrappedFunction& InFuncDef, const PyGenUtil::FGeneratedWrappedMethodParameter& InSelfParam, const PyGenUtil::FGeneratedWrappedMethodParameter& InSelfReturn, const char* InPythonFuncName);` — Call a dynamic function on this instance (CallFunction internal use only)
- L82 _public prototype_ `static PyObject* CallDynamicMethodNoArgs_Impl(FPyWrapperStruct* InSelf, void* InClosure);` — Implementation of the "call" logic for a dynamic Python method with no arguments (internal Python bindings use only)
- L85 _public prototype_ `static PyObject* CallDynamicMethodWithArgs_Impl(FPyWrapperStruct* InSelf, PyObject* InArgs, PyObject* InKwds, void* InClosure);` — Implementation of the "call" logic for a dynamic Python method with arguments (internal Python bindings use only)
- L88 _public prototype_ `static PyObject* CallOperatorFunction_Impl(FPyWrapperStruct* InSelf, PyObject* InRHS, const PyGenUtil::FGeneratedWrappedOperatorFunction& InOpFunc, const TOptional<EPyConversionResultState> InRequiredConversionResult = TOptional<EPyConversionResultState>(), FPyConversionResult* OutRHSConversionResult = nullptr);` — Implementation of the "call" logic for a Python operator function (internal CallOperator use only)
- L91 _public prototype_ `static PyObject* CallOperator_Impl(FPyWrapperStruct* InSelf, PyObject* InRHS, const PyGenUtil::EGeneratedWrappedOperatorType InOpType);` — Implementation of the "call" logic for a Python operator function (internal Python bindings use only)
- L94 _public prototype_ `static PyObject* Getter_Impl(FPyWrapperStruct* InSelf, void* InClosure);` — Implementation of the "getter" logic for a Python descriptor reading from an struct property (internal Python bindings use only)
- L97 _public prototype_ `static int Setter_Impl(FPyWrapperStruct* InSelf, PyObject* InValue, void* InClosure);` — Implementation of the "setter" logic for a Python descriptor writing to an struct property (internal Python bindings use only)
- L101 _public function_ `template <typename StructType> static StructType* GetTypedStructPtr(FPyWrapperStruct* InSelf)` — Get a pointer to the typed struct instance this wrapper represents
- L108 _public function_ `template <typename StructType> static StructType& GetTypedStruct(FPyWrapperStruct* InSelf)` — Get a reference to the typed struct instance this wrapper represents

#### struct `TPyWrapperInlineStruct`  
`template <typename InlineType> struct TPyWrapperInlineStruct : public FPyWrapperStruct`  
_L116-240_
- inherits: `FPyWrapperStruct`
- desc: Specialized version of FPyWrapperStruct that can store its struct payload inline (requires a known type)
- L118 _public typedef_ `typedef InlineType WrappedType;`
- L121 _public member_ `TTypeCompatibleBytes<WrappedType> InlineStructInstance;` — Inline struct instance (do not use directly, StructInstance will be set to point to this when appropriate via FPyWrapperStructAllocationPolicy_Inline)
- L124 _public function_ `static TPyWrapperInlineStruct* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr)` — Cast the given Python object to this wrapped type (returns a new reference)
- L130 _public function_ `static TPyWrapperInlineStruct* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr)` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L136 _public function_ `static WrappedType* GetTypedStructPtr(TPyWrapperInlineStruct* InSelf)` — Get a pointer to the typed struct instance this wrapper represents
- L142 _public function_ `static WrappedType& GetTypedStruct(TPyWrapperInlineStruct* InSelf)` — Get a reference to the typed struct instance this wrapper represents
- L149 _public function_ `template <typename FieldType, FieldType WrappedType::*FieldPtr> static PyObject* IntrinsicFieldGetter(TPyWrapperInlineStruct* InSelf, void* InClosure)` — Getter function for intrinsic field access (for use with PyGetSetDef)
- L156 _public function_ `template <typename FieldType, FieldType WrappedType::*FieldPtr> static int IntrinsicFieldSetter(TPyWrapperInlineStruct* InSelf, PyObject* InValue, void* InClosure)` — Setter function for intrinsic field access (for use with PyGetSetDef)
- L174 _public function_ `template <typename FieldType, FieldType WrappedType::*FieldPtr> static PyObject* StructFieldGetter(TPyWrapperInlineStruct* InSelf, void* InClosure)` — Getter function for struct field access (for use with PyGetSetDef)
- L181 _public function_ `template <typename FieldType, FieldType WrappedType::*FieldPtr> static int StructFieldSetter(TPyWrapperInlineStruct* InSelf, PyObject* InValue, void* InClosure)` — Setter function for struct field access (for use with PyGetSetDef)
- L199 _public function_ `template <void(WrappedType::*FuncPtr)()> static PyObject* CallFunc_NoParams_NoReturn(TPyWrapperInlineStruct* InSelf)` — Call a function with no parameters and no return value (for use with PyMethodDef)
- L207 _public function_ `template <void(WrappedType::*FuncPtr)() const> static PyObject* CallConstFunc_NoParams_NoReturn(TPyWrapperInlineStruct* InSelf)` — Call a const function with no parameters and no return value (for use with PyMethodDef)
- L215 _public function_ `template <typename ReturnType, ReturnType(WrappedType::*FuncPtr)()> static PyObject* CallFunc_NoParams_IntrinsicReturn(TPyWrapperInlineStruct* InSelf)` — Call a function with no parameters and an intrinsic return value (for use with PyMethodDef)
- L222 _public function_ `template <typename ReturnType, ReturnType(WrappedType::*FuncPtr)() const> static PyObject* CallConstFunc_NoParams_IntrinsicReturn(TPyWrapperInlineStruct* InSelf)` — Call a const function with no parameters and an intrinsic return value (for use with PyMethodDef)
- L229 _public function_ `template <typename ReturnType, ReturnType(WrappedType::*FuncPtr)()> static PyObject* CallFunc_NoParams_StructReturn(TPyWrapperInlineStruct* InSelf)` — Call a function with no parameters and a struct return value (for use with PyMethodDef)
- L236 _public function_ `template <typename ReturnType, ReturnType(WrappedType::*FuncPtr)() const> static PyObject* CallConstFunc_NoParams_StructReturn(TPyWrapperInlineStruct* InSelf)` — Call a const function with no parameters and a struct return value (for use with PyMethodDef)

#### class `IPyWrapperStructAllocationPolicy`  
`class IPyWrapperStructAllocationPolicy`  
_L243-251_
- desc: Struct allocation policy interface
- L247 _public prototype_ `virtual void* AllocateStruct(const FPyWrapperStruct* InSelf, UScriptStruct* InStruct) const = 0;` — Allocate memory to hold an instance of the given struct and return the result
- L250 _public prototype_ `virtual void FreeStruct(const FPyWrapperStruct* InSelf, void* InAlloc) const = 0;` — Free memory previously allocated with AllocateStruct

#### class `IPyWrapperInlineStructFactory`  
`class IPyWrapperInlineStructFactory`  
_L254-265_
- desc: Inline struct factory interface
- L258 _public prototype_ `virtual FTopLevelAssetPath GetStructName() const = 0;` — Get the name of the Unreal struct this factory is for
- L261 _public prototype_ `virtual int32 GetPythonObjectSizeBytes() const = 0;` — Get the size of the Python object that should be constructed (in bytes)
- L264 _public prototype_ `virtual const IPyWrapperStructAllocationPolicy* GetPythonObjectAllocationPolicy() const = 0;` — Get the allocation policy of the Python object

#### class `TPyWrapperInlineStructFactory`  
`template <typename InlineType> class TPyWrapperInlineStructFactory : public IPyWrapperInlineStructFactory`  
_L269-301_
- inherits: `IPyWrapperInlineStructFactory`
- desc: Concrete implementation of an inline struct factory for the given type
- L286 _public function_ `virtual FTopLevelAssetPath GetStructName() const override`
- L291 _public function_ `virtual int32 GetPythonObjectSizeBytes() const override`
- L296 _public function_ `virtual const IPyWrapperStructAllocationPolicy* GetPythonObjectAllocationPolicy() const override`

#### class `TPyWrapperInlineStructFactory::FPyWrapperStructAllocationPolicy_Inline`  
`class FPyWrapperStructAllocationPolicy_Inline : public IPyWrapperStructAllocationPolicy`  
_L272-283_
- inherits: `IPyWrapperStructAllocationPolicy`
- L275 _public function_ `virtual void* AllocateStruct(const FPyWrapperStruct* InSelf, UScriptStruct* InStruct) const override`
- L280 _public function_ `virtual void FreeStruct(const FPyWrapperStruct* InSelf, void* InAlloc) const override`

#### struct `FPyWrapperStructMetaData`  
`struct FPyWrapperStructMetaData : public FPyWrapperBaseMetaData`  
_L304-369_
- inherits: `FPyWrapperBaseMetaData`
- desc: Meta-data for all Unreal exposed struct types
- L308 _public prototype_ `FPyWrapperStructMetaData();`
- L311 _public prototype_ `static UScriptStruct* GetStruct(PyTypeObject* PyType);` — Get the UScriptStruct from the given type
- L314 _public prototype_ `static UScriptStruct* GetStruct(FPyWrapperStruct* Instance);` — Get the UScriptStruct from the type of the given instance
- L317 _public prototype_ `static FName ResolvePropertyName(PyTypeObject* PyType, const FName InPythonPropertyName);` — Resolve the original property name of a Python property from the given type
- L320 _public prototype_ `static FName ResolvePropertyName(FPyWrapperStruct* Instance, const FName InPythonPropertyName);` — Resolve the original property name of a Python property of the given instance
- L323 _public prototype_ `static bool IsPropertyDeprecated(PyTypeObject* PyType, const FName InPythonPropertyName, FString* OutDeprecationMessage = nullptr);` — Check to see if the given Python property is deprecated, and optionally return its deprecation message
- L326 _public prototype_ `static bool IsPropertyDeprecated(FPyWrapperStruct* Instance, const FName InPythonPropertyName, FString* OutDeprecationMessage = nullptr);` — Check to see if the given Python property is deprecated, and optionally return its deprecation message
- L329 _public prototype_ `static bool IsStructDeprecated(PyTypeObject* PyType, FString* OutDeprecationMessage = nullptr);` — Check to see if the struct is deprecated, and optionally return its deprecation message
- L332 _public prototype_ `static bool IsStructDeprecated(FPyWrapperStruct* Instance, FString* OutDeprecationMessage = nullptr);` — Check to see if the struct is deprecated, and optionally return its deprecation message
- L335 _public prototype_ `virtual void AddTypeReferencedObjects(FReferenceCollector& Collector) override;` — Add object references from this type meta-data to the given collector
- L338 _public prototype_ `virtual void AddInstanceReferencedObjects(FPyWrapperBase* Instance, FReferenceCollector& Collector) override;` — Add object references from the given Python object to the given collector
- L341 _public function_ `virtual const UField* GetMetaType() const override` — Get the reflection meta data type object associated with this wrapper type if there is one or nullptr if not.
- L347 _public member_ `TObjectPtr<UScriptStruct> Struct;` — Unreal struct
- L350 _public member_ `TMap<FName, FName> PythonProperties;` — Map of properties that were exposed to Python mapped to their original name
- L353 _public member_ `TMap<FName, FString> PythonDeprecatedProperties;` — Map of properties that were exposed to Python mapped to their deprecation message (if deprecated)
- L356 _public member_ `PyGenUtil::FGeneratedWrappedFunction MakeFunc;` — Make function associated with this struct
- L359 _public member_ `PyGenUtil::FGeneratedWrappedFunction BreakFunc;` — Break function associated with this struct
- L362 _public member_ `TArray<PyGenUtil::FGeneratedWrappedMethodParameter> InitParams;` — Array of properties that were exposed to Python and can be used during init
- L365 _public member_ `PyGenUtil::FGeneratedWrappedOperatorStack OpStacks[(int32)PyGenUtil::EGeneratedWrappedOperatorType::Num];` — The operator stacks for this struct type
- L368 _public member_ `TOptional<FString> DeprecationMessage;` — Set if this struct is deprecated and using it should emit a deprecation warning

#### class `UPythonGeneratedStruct`  
`class UPythonGeneratedStruct final : public UScriptStruct, public IPythonResourceOwner`  
_L377-429_
- reflection: `UCLASS()`
- inherits: `UScriptStruct,IPythonResourceOwner`
- desc: An Unreal struct that was generated from a Python type
- L385 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L386 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L387 _public prototype_ `virtual void BeginDestroy() override;`
- L388 _public function_ `virtual bool IsAsset() const override`
- L394 _public prototype_ `virtual void InitializeStruct(void* Dest, int32 ArrayDim = 1) const override;`
- L397 _public prototype_ `virtual void ReleasePythonResources() override;`
- L400 _public prototype_ `void UnregisterGeneratedType();` — Unregister this type from FPyWrapperTypeRegistry
- L403 _public prototype_ `static UPythonGeneratedStruct* GenerateStruct(PyTypeObject* InPyType);` — Generate an Unreal struct from the given Python type
- L407 _private member_ `FPyTypeObjectPtr PyType;` — Python type this struct was generated from
- L410 _private member_ `FPyObjectPtr PyPostInitFunction;` — PostInit function for this struct
- L413 _private member_ `TArray<TSharedPtr<PyGenUtil::FPropertyDef>> PropertyDefs;` — Array of properties generated for this struct
- L416 _private member_ `FPyWrapperStructMetaData PyMetaData;` — Meta-data for this generated struct that is applied to the Python type
- L418 _private member_ `TObjectPtr<UObjectRedirector> StructRedirector;`

#### Free symbols / members of external scopes

- L19 _externvar_ `extern PyTypeObject PyWrapperStructType;` — Python type for FPyWrapperStruct
- L22 _prototype_ `void InitializePyWrapperStruct(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the PyWrapperStruct types and add them to the given Python module
- L371 _typedef_ `typedef TPyPtr<FPyWrapperStruct> FPyWrapperStructPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperText.h` (Private)


#### struct `FPyWrapperText`  
`struct FPyWrapperText : public TPyWrapperBasic<FText, FPyWrapperText>`  
_L16-31_
- inherits: `TPyWrapperBasic<FText,FPyWrapperText>`
- desc: Type for all Unreal exposed FText instances
- L18 _public typedef_ `typedef TPyWrapperBasic<FText, FPyWrapperText> Super;`
- L21 _public prototype_ `static FPyWrapperText* CastPyObject(PyObject* InPyObject, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type (returns a new reference)
- L24 _public prototype_ `static FPyWrapperText* CastPyObject(PyObject* InPyObject, PyTypeObject* InType, FPyConversionResult* OutCastResult = nullptr);` — Cast the given Python object to this wrapped type, or attempt to convert the type into a new wrapped instance (returns a new reference)
- L27 _public prototype_ `static void InitValue(FPyWrapperText* InSelf, const FText InValue);` — Initialize the value of this wrapper instance (internal)
- L30 _public prototype_ `static void DeinitValue(FPyWrapperText* InSelf);` — Deinitialize the value of this wrapper instance (internal)

#### Free symbols / members of external scopes

- L10 _externvar_ `extern PyTypeObject PyWrapperTextType;` — Python type for FPyWrapperText
- L13 _prototype_ `void InitializePyWrapperText(PyGenUtil::FNativePythonModule& ModuleInfo);` — Initialize the FPyWrapperText types and add them to the given Python module
- L33 _typedef_ `typedef TPyPtr<FPyWrapperText> FPyWrapperTextPtr;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PyWrapperTypeRegistry.h` (Private)


#### enum `EPyTypeGenerationFlags`  
`enum class EPyTypeGenerationFlags : uint8`  
_L43-53_
- L46 _public enumerator_ `None = 0` — No behavior
- L48 _public enumerator_ `ForceShouldExport = 1<<0` — Generate the Python wrapper for this type, even if it fails the PyGenUtil::ShouldExportX check
- L50 _public enumerator_ `IncludeBlueprintGeneratedTypes = 1<<1` — Generate the Python wrapper for this type, even if it passes the PyGenUtil::IsBlueprintGeneratedX check
- L52 _public enumerator_ `OverwriteExisting = 1<<2` — Generate the Python wrapper for this type, re-using the existing type if it already exists

#### struct `TPyWrapperTypeFactoryConversion`  
`template <typename UnrealType, typename KeyType> struct TPyWrapperTypeFactoryConversion`  
_L58-64_
- desc: Type conversion for TPyWrapperTypeFactory
- L60 _public function_ `static KeyType UnrealTypeToKeyType(UnrealType InUnrealInstance)`
- L70 _public function_ `static const void* UnrealTypeToKeyType(FText InUnrealInstance)`

#### struct `TPyWrapperTypeFactoryConversion`  
`template <> struct TPyWrapperTypeFactoryConversion<FText, const void*>`  
_L68-74_
- desc: Type conversion specialization for FPyWrapperTextFactory
- L60 _public function_ `static KeyType UnrealTypeToKeyType(UnrealType InUnrealInstance)`
- L70 _public function_ `static const void* UnrealTypeToKeyType(FText InUnrealInstance)`

#### class `TPyWrapperTypeFactory`  
`template <typename UnrealType, typename PythonType, typename KeyType = UnrealType> class TPyWrapperTypeFactory`  
_L78-167_
- desc: Generic factory implementation for Python wrapped types. Types should derive from this and implement a CreateInstance and FindInstance function
- L102 _protected function_ `friend inline uint32 GetTypeHash(const FInternalKey& Key)`
- L115 _public function_ `void MapInstance(UnrealType InUnrealInstance, PythonType* InPythonInstance)` — Map a wrapped Python instance associated with the given Unreal instance (called internally by the Python type)
- L121 _public function_ `void UnmapInstance(UnrealType InUnrealInstance, PyTypeObject* InWrappedPyType)` — Unmap the wrapped instance associated with the given UObject instance (called internally by the Python type)
- L126 _public function_ `void Shutdown()`
- L133 _protected typedef_ `typedef TFunctionRef<int(PythonType*)> FCreateInstanceInitializerFunc;` — Callback used to initialize this type
- L136 _protected function_ `PythonType* FindInstanceInternal(UnrealType InUnrealInstance, PyTypeObject* InWrappedPyType) const` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L142 _protected function_ `PythonType* CreateInstanceInternal(UnrealType InUnrealInstance, PyTypeObject* InWrappedPyType, FCreateInstanceInitializerFunc CreateInstanceInitializerFunc, const bool bForceCreate = false)` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)
- L166 _protected member_ `TMap<FInternalKey, PythonType*> MappedInstances;` — Map from the internal key to wrapped Python instance

#### struct `TPyWrapperTypeFactory::FInternalKey`  
`struct FInternalKey`  
_L81-111_
- L84 _public function_ `FInternalKey(KeyType InWrapperKey, PyTypeObject* InPyType) : WrapperKey(InWrapperKey) , PyType(InPyType) , Hash(HashCombine(GetTypeHash(WrapperKey), GetTypeHash(InPyType)))`
- L91 _public function_ `FORCEINLINE bool operator==(const FInternalKey& Other) const`
- L97 _public function_ `FORCEINLINE bool operator!=(const FInternalKey& Other) const`
- L108 _private member_ `KeyType WrapperKey;`
- L109 _private member_ `PyTypeObject* PyType;`
- L110 _private member_ `uint32 Hash;`

#### class `FPyWrapperObjectFactory`  
`class FPyWrapperObjectFactory : public TPyWrapperTypeFactory<UObject*, FPyWrapperObject>`  
_L170-184_
- inherits: `TPyWrapperTypeFactory<UObject*,FPyWrapperObject>`
- desc: Factory for wrapped UObject instances
- L174 _public prototype_ `static FPyWrapperObjectFactory& Get();` — Access the singleton instance
- L177 _public prototype_ `FPyWrapperObject* FindInstance(UObject* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L180 _public prototype_ `FPyWrapperObject* CreateInstance(UObject* InUnrealInstance);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)
- L183 _public prototype_ `FPyWrapperObject* CreateInstance(UClass* InInterfaceClass, UObject* InUnrealInstance);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperStructFactory`  
`class FPyWrapperStructFactory : public TPyWrapperTypeFactory<void*, FPyWrapperStruct>`  
_L187-198_
- inherits: `TPyWrapperTypeFactory<void*,FPyWrapperStruct>`
- desc: Factory for wrapped UScriptStruct instances
- L191 _public prototype_ `static FPyWrapperStructFactory& Get();` — Access the singleton instance
- L194 _public prototype_ `FPyWrapperStruct* FindInstance(UScriptStruct* InStruct, void* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L197 _public prototype_ `FPyWrapperStruct* CreateInstance(UScriptStruct* InStruct, void* InUnrealInstance, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperDelegateFactory`  
`class FPyWrapperDelegateFactory : public TPyWrapperTypeFactory<FScriptDelegate*, FPyWrapperDelegate>`  
_L201-212_
- inherits: `TPyWrapperTypeFactory<FScriptDelegate*,FPyWrapperDelegate>`
- desc: Factory for wrapped delegate instances
- L205 _public prototype_ `static FPyWrapperDelegateFactory& Get();` — Access the singleton instance
- L208 _public prototype_ `FPyWrapperDelegate* FindInstance(const UFunction* InDelegateSignature, FScriptDelegate* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L211 _public prototype_ `FPyWrapperDelegate* CreateInstance(const UFunction* InDelegateSignature, FScriptDelegate* InUnrealInstance, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperMulticastDelegateFactory`  
`class FPyWrapperMulticastDelegateFactory : public TPyWrapperTypeFactory<FMulticastScriptDelegate*, FPyWrapperMulticastDelegate>`  
_L215-226_
- inherits: `TPyWrapperTypeFactory<FMulticastScriptDelegate*,FPyWrapperMulticastDelegate>`
- desc: Factory for wrapped multicast delegate instances
- L219 _public prototype_ `static FPyWrapperMulticastDelegateFactory& Get();` — Access the singleton instance
- L222 _public prototype_ `FPyWrapperMulticastDelegate* FindInstance(const UFunction* InDelegateSignature, FMulticastScriptDelegate* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L225 _public prototype_ `FPyWrapperMulticastDelegate* CreateInstance(const UFunction* InDelegateSignature, FMulticastScriptDelegate* InUnrealInstance, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperNameFactory`  
`class FPyWrapperNameFactory : public TPyWrapperTypeFactory<FName, FPyWrapperName>`  
_L229-240_
- inherits: `TPyWrapperTypeFactory<FName,FPyWrapperName>`
- desc: Factory for wrapped FName instances
- L233 _public prototype_ `static FPyWrapperNameFactory& Get();` — Access the singleton instance
- L236 _public prototype_ `FPyWrapperName* FindInstance(const FName InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L239 _public prototype_ `FPyWrapperName* CreateInstance(const FName InUnrealInstance);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperTextFactory`  
`class FPyWrapperTextFactory : public TPyWrapperTypeFactory<FText, FPyWrapperText, const void*>`  
_L243-254_
- inherits: `TPyWrapperTypeFactory<FText,FPyWrapperText,constvoid*>`
- desc: Factory for wrapped FText instances
- L247 _public prototype_ `static FPyWrapperTextFactory& Get();` — Access the singleton instance
- L250 _public prototype_ `FPyWrapperText* FindInstance(const FText InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L253 _public prototype_ `FPyWrapperText* CreateInstance(const FText InUnrealInstance);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperArrayFactory`  
`class FPyWrapperArrayFactory : public TPyWrapperTypeFactory<void*, FPyWrapperArray>`  
_L257-268_
- inherits: `TPyWrapperTypeFactory<void*,FPyWrapperArray>`
- desc: Factory for wrapped array instances
- L261 _public prototype_ `static FPyWrapperArrayFactory& Get();` — Access the singleton instance
- L264 _public prototype_ `FPyWrapperArray* FindInstance(void* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L267 _public prototype_ `FPyWrapperArray* CreateInstance(void* InUnrealInstance, const FArrayProperty* InProp, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperFixedArrayFactory`  
`class FPyWrapperFixedArrayFactory : public TPyWrapperTypeFactory<void*, FPyWrapperFixedArray>`  
_L271-282_
- inherits: `TPyWrapperTypeFactory<void*,FPyWrapperFixedArray>`
- desc: Factory for wrapped fixed-array instances
- L275 _public prototype_ `static FPyWrapperFixedArrayFactory& Get();` — Access the singleton instance
- L278 _public prototype_ `FPyWrapperFixedArray* FindInstance(void* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L281 _public prototype_ `FPyWrapperFixedArray* CreateInstance(void* InUnrealInstance, const FProperty* InProp, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperSetFactory`  
`class FPyWrapperSetFactory : public TPyWrapperTypeFactory<void*, FPyWrapperSet>`  
_L285-296_
- inherits: `TPyWrapperTypeFactory<void*,FPyWrapperSet>`
- desc: Factory for wrapped set instances
- L289 _public prototype_ `static FPyWrapperSetFactory& Get();` — Access the singleton instance
- L292 _public prototype_ `FPyWrapperSet* FindInstance(void* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L295 _public prototype_ `FPyWrapperSet* CreateInstance(void* InUnrealInstance, const FSetProperty* InProp, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperMapFactory`  
`class FPyWrapperMapFactory : public TPyWrapperTypeFactory<void*, FPyWrapperMap>`  
_L299-310_
- inherits: `TPyWrapperTypeFactory<void*,FPyWrapperMap>`
- desc: Factory for wrapped map instances
- L303 _public prototype_ `static FPyWrapperMapFactory& Get();` — Access the singleton instance
- L306 _public prototype_ `FPyWrapperMap* FindInstance(void* InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L309 _public prototype_ `FPyWrapperMap* CreateInstance(void* InUnrealInstance, const FMapProperty* InProp, const FPyWrapperOwnerContext& InOwnerContext, const EPyConversionMethod InConversionMethod);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperFieldPathFactory`  
`class FPyWrapperFieldPathFactory : public TPyWrapperTypeFactory<FFieldPath, FPyWrapperFieldPath>`  
_L313-324_
- inherits: `TPyWrapperTypeFactory<FFieldPath,FPyWrapperFieldPath>`
- desc: Factory for wrapped field type instances
- L317 _public prototype_ `static FPyWrapperFieldPathFactory& Get();` — Access the singleton instance
- L320 _public prototype_ `FPyWrapperFieldPath* FindInstance(FFieldPath InUnrealInstance) const;` — Find the wrapped Python instance associated with the given Unreal instance (if any, returns borrowed reference)
- L323 _public prototype_ `FPyWrapperFieldPath* CreateInstance(FFieldPath InUnrealInstance);` — Find the wrapped Python instance associated with the given Unreal instance, or create one if needed (returns new reference)

#### class `FPyWrapperTypeReinstancer`  
`class FPyWrapperTypeReinstancer : public FGCObject`  
_L328-355_
- inherits: `FGCObject`
- desc: Singleton instance that handles re-instancing Python types
- L332 _public prototype_ `static FPyWrapperTypeReinstancer& Get();` — Access the singleton instance
- L335 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L336 _public prototype_ `virtual FString GetReferencerName() const override;`
- L339 _public prototype_ `void AddPendingClass(UPythonGeneratedClass* OldClass, UPythonGeneratedClass* NewClass);` — Add a pending pair of classes to be re-instanced
- L342 _public prototype_ `void AddPendingStruct(UPythonGeneratedStruct* OldStruct, UPythonGeneratedStruct* NewStruct);` — Add a pending pair of structs to be re-instanced
- L345 _public prototype_ `void ProcessPending();` — Process any pending re-instance requests
- L347 _public prototype_ `void Shutdown();`
- L351 _private member_ `TMap<TObjectPtr<UPythonGeneratedClass>, TObjectPtr<UPythonGeneratedClass>> ClassesToReinstance;` — Pending pairs of classes that to be re-instanced
- L354 _private member_ `TMap<TObjectPtr<UPythonGeneratedStruct>, TObjectPtr<UPythonGeneratedStruct>> StructsToReinstance;` — Pending pairs of structs that to be re-instanced

#### class `FPyWrapperTypeRegistry`  
`class FPyWrapperTypeRegistry : public FGCObject`  
_L358-563_
- inherits: `FGCObject`
- desc: Singleton instance that maps Unreal types to Python types
- L375 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModuleDirtied, FName);`
- L378 _public prototype_ `static FPyWrapperTypeRegistry& Get();` — Access the singleton instance
- L381 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L382 _public prototype_ `virtual FString GetReferencerName() const override;`
- L385 _public function_ `FOnModuleDirtied& OnModuleDirtied()` — Callback for when a Python module is dirtied
- L391 _public prototype_ `void RegisterNativePythonModule(PyGenUtil::FNativePythonModule&& NativePythonModule);` — Register the information about a native Python module
- L397 _public prototype_ `void RegisterInlineStructFactory(const TSharedRef<const IPyWrapperInlineStructFactory>& InFactory);` — Register the factory for an inline struct (ie, a struct known at compile time that will allocate its instance data inlined within the Python object). @note Inline struct registration must happen before the first call to GenerateWrappedStructType, and this function will assert if that is not the case!
- L400 _public prototype_ `const IPyWrapperInlineStructFactory* GetInlineStructFactory(const FTopLevelAssetPath& StructName) const;` — Get the factory for an inline struct (if known) from its Unreal struct name
- L403 _public prototype_ `void GenerateWrappedTypes(bool bAllowMultithreadedGeneration = false);` — Generate a wrapped type for all currently available Unreal types
- L406 _public prototype_ `void GenerateWrappedTypesForModule(const FName ModuleName);` — Generate a wrapped type for all available Unreal types in the given Unreal module
- L409 _public prototype_ `void OrphanWrappedTypesForModule(const FName ModuleName);` — Orphan the wrapped types associated with the given Unreal module (when the module is unloaded/reloaded)
- L412 _public prototype_ `void GenerateWrappedTypesForReferences(const FGeneratedWrappedTypeReferences& InGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules);` — Generate a wrapped type for all referenced types
- L415 _public prototype_ `void NotifyModulesDirtied(const TSet<FName>& InDirtyModules) const;` — Generate notifications to (re)load the dirtied modules in Python
- L418 _public prototype_ `void UpdateGenerateWrappedTypeForRename(const FSoftObjectPath& InOldTypeRegistryName, const UObject* InObj);` — Called when an asset that is registered with the type registry has been renamed
- L421 _public prototype_ `void RemoveGenerateWrappedTypeForDelete(const FSoftObjectPath& InTypeRegistryName);` — Called when an asset that is registered with the type registry is deleted
- L424 _public prototype_ `PyTypeObject* GenerateWrappedTypeForObject(const UObject* InObj, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules, const EPyTypeGenerationFlags InGenerationFlags = EPyTypeGenerationFlags::None);` — Generate a wrapped type for the given object (if it's a valid type to be wrapped)
- L427 _public prototype_ `bool HasWrappedTypeForObject(const UObject* InObj) const;` — True if we have wrapped type for the given object
- L430 _public prototype_ `bool HasWrappedTypeForObjectName(const FSoftObjectPath& InName) const;` — True if we have wrapped type for the given object name
- L433 _public prototype_ `PyTypeObject* GetWrappedTypeForObject(const UObject* InObj) const;` — Get the best wrapped type for the given object
- L436 _public prototype_ `PyTypeObject* GenerateWrappedClassType(const UClass* InClass, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules, const EPyTypeGenerationFlags InGenerationFlags = EPyTypeGenerationFlags::None);` — Generate a wrapped type for the given class (only if this class has not yet been registered; will also register the type)
- L439 _public prototype_ `void RegisterWrappedClassType(const FSoftObjectPath& ClassName, PyTypeObject* PyType, const bool InDetectNameConflicts = true);` — Register the wrapped type associated with the given class name
- L442 _public prototype_ `void UnregisterWrappedClassType(const FSoftObjectPath& ClassName, PyTypeObject* PyType, const bool InUnregisterName = true);` — Unregister the wrapped type associated with the given class name
- L445 _public prototype_ `bool HasWrappedClassType(const UClass* InClass) const;` — True if we have wrapped type for the exact given class
- L448 _public prototype_ `PyTypeObject* GetWrappedClassType(const UClass* InClass) const;` — Get the best wrapped type for the given class
- L451 _public prototype_ `PyTypeObject* GenerateWrappedStructType(const UScriptStruct* InStruct, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules, const EPyTypeGenerationFlags InGenerationFlags = EPyTypeGenerationFlags::None);` — Generate a wrapped type for the given struct (only if this struct has not yet been registered; will also register the type)
- L454 _public prototype_ `void RegisterWrappedStructType(const FSoftObjectPath& StructName, PyTypeObject* PyType, const bool InDetectNameConflicts = true);` — Register the wrapped type associated with the given struct name
- L457 _public prototype_ `void UnregisterWrappedStructType(const FSoftObjectPath& StructName, PyTypeObject* PyType, const bool InUnregisterName = true);` — Unregister the wrapped type associated with the given struct name
- L460 _public prototype_ `bool HasWrappedStructType(const UScriptStruct* InStruct) const;` — True if we have wrapped type for the exact given struct
- L463 _public prototype_ `PyTypeObject* GetWrappedStructType(const UScriptStruct* InStruct) const;` — Get the best wrapped type for the given struct
- L466 _public prototype_ `PyTypeObject* GenerateWrappedEnumType(const UEnum* InEnum, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules, const EPyTypeGenerationFlags InGenerationFlags = EPyTypeGenerationFlags::None);` — Generate a wrapped type for the given enum (only if this enum has not yet been registered; will also register the type)
- L469 _public prototype_ `void RegisterWrappedEnumType(const FSoftObjectPath& EnumName, PyTypeObject* PyType, const bool InDetectNameConflicts = true);` — Register the wrapped type associated with the given enum name
- L472 _public prototype_ `void UnregisterWrappedEnumType(const FSoftObjectPath& EnumName, PyTypeObject* PyType, const bool InUnregisterName = true);` — Unregister the wrapped type associated with the given enum name
- L475 _public prototype_ `bool HasWrappedEnumType(const UEnum* InEnum) const;` — True if we have wrapped type for the exact given enum
- L478 _public prototype_ `PyTypeObject* GetWrappedEnumType(const UEnum* InEnum) const;` — Get the best wrapped type for the given enum
- L481 _public prototype_ `PyTypeObject* GenerateWrappedDelegateType(const UFunction* InDelegateSignature, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules, const EPyTypeGenerationFlags InGenerationFlags = EPyTypeGenerationFlags::None);` — Generate a wrapped type for the given delegate signature (only if this delegate has not yet been registered; will also register the type)
- L484 _public prototype_ `void RegisterWrappedDelegateType(const FSoftObjectPath& DelegateName, PyTypeObject* PyType, const bool InDetectNameConflicts = true);` — Register the wrapped type associated with the given delegate name
- L487 _public prototype_ `void UnregisterWrappedDelegateType(const FSoftObjectPath& DelegateName, PyTypeObject* PyType, const bool InUnregisterName = true);` — Unregister the wrapped type associated with the given delegate name
- L490 _public prototype_ `bool HasWrappedDelegateType(const UFunction* InDelegateSignature) const;` — True if we have wrapped type for the exact given delegate signature
- L493 _public prototype_ `PyTypeObject* GetWrappedDelegateType(const UFunction* InDelegateSignature) const;` — Get the best wrapped type for the given delegate signature
- L496 _public prototype_ `void GenerateStubCodeForWrappedTypes(const EPyOnlineDocsFilterFlags InDocGenFlags = EPyOnlineDocsFilterFlags::IncludeNone) const;` — Generate stub Python code for our wrapped types
- L498 _public prototype_ `void Shutdown();`
- L502 _private prototype_ `void ExecutePostInitOnGameThread();` — Call the game-thread only logic
- L505 _private prototype_ `void GatherWrappedTypesForPropertyReferences(const FProperty* InProp, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences) const;` — Gather any types referenced by the given property are still need to be wrapped for use in Python
- L508 _private prototype_ `static void GenerateStubCodeForWrappedType(PyTypeObject* PyType, const PyGenUtil::FGeneratedWrappedType* GeneratedTypeData, FPyFileWriter& OutPythonScript, FPyOnlineDocsSection* OutOnlineDocsSection = nullptr);` — Generate stub Python code for the given type
- L511 _private prototype_ `void RegisterPythonTypeName(const FString& InPythonTypeName, const FSoftObjectPath& InUnrealTypeName);` — Register a Python type name, and detect if a name conflict has occurred
- L514 _private prototype_ `void UnregisterPythonTypeName(const FString& InPythonTypeName, const FSoftObjectPath& InUnrealTypeName);` — Unregister a Python type name if it corresponds to the given Unreal type name
- L516 _private prototype_ `FPyWrapperTypeRegistry();`
- L519 _private member_ `std::atomic<bool> bCanRegisterInlineStructFactories;` — True if we can register inline struct factories, False if we've already started generating types
- L522 _private member_ `TMap<FTopLevelAssetPath, TSharedPtr<const IPyWrapperInlineStructFactory>> InlineStructFactories;` — Map from the Unreal struct name to the factory data for an inline struct (ie, a struct known at compile time that will allocate its instance data inlined within the Python object)
- L525 _private member_ `static constexpr int32 StripeCount = 32;` — Good balance for high core count CPUs.
- L528 _private typedef_ `typedef TStripedMap<StripeCount, FString, FSoftObjectPath, FDefaultSetAllocator, PyGenUtil::FCaseSensitiveStringMapFuncs<FSoftObjectPath>> FCaseSensitiveStringToNameMap;` — Map from the Python wrapped type name to the Unreal type name it was generated from (for conflict detection)
- L529 _private member_ `FCaseSensitiveStringToNameMap PythonWrappedTypeNameToUnrealTypeName;`
- L532 _private member_ `TStripedMap<StripeCount, FSoftObjectPath, PyTypeObject*> PythonWrappedClasses;` — Map from the Unreal class name to the Python type
- L535 _private member_ `TStripedMap<StripeCount, FSoftObjectPath, PyTypeObject*> PythonWrappedStructs;` — Map from the Unreal struct name to the Python type
- L538 _private member_ `TStripedMap<StripeCount, FSoftObjectPath, PyTypeObject*> PythonWrappedEnums;` — Map from the Unreal enum name to the Python type
- L541 _private member_ `TStripedMap<StripeCount, FSoftObjectPath, PyTypeObject*> PythonWrappedDelegates;` — Map from the Unreal delegate signature name to the Python type
- L544 _private member_ `TStripedMap<StripeCount, FSoftObjectPath, TSharedPtr<PyGenUtil::FGeneratedWrappedType>> GeneratedWrappedTypes;` — Map from the Unreal type name to the generated Python type data
- L547 _private member_ `TStripedMultiMap<StripeCount, FName, FSoftObjectPath> GeneratedWrappedTypesForModule;` — Map from the Unreal module name to its generated type names (names are the Unreal names)
- L550 _private member_ `TStripedMap<StripeCount, FString, TSharedPtr<FPyWrapperStructMetaData>> UnresolvedMakeFuncs;` — Map make func name to the meta data of the struct to make. Used when meta 'HasNativeMake' references a function not loaded yet.
- L553 _private member_ `TStripedMap<StripeCount, FString, TSharedPtr<FPyWrapperStructMetaData>> UnresolvedBreakFuncs;` — Map break func name to the meta data of the struct to break. Used when meta 'HasNativeBreak' references a function not loaded yet.
- L556 _private member_ `TArray<TSharedPtr<PyGenUtil::FGeneratedWrappedType>> OrphanedWrappedTypes;` — Array of generated Python type data that has been orphaned (due to its owner module being unloaded/reloaded)
- L559 _private member_ `TArray<PyGenUtil::FNativePythonModule> NativePythonModules;` — Array of information about native Python modules
- L562 _private member_ `FOnModuleDirtied OnModuleDirtiedDelegate;` — Callback for when a Python module is dirtied

#### struct `FPyWrapperTypeRegistry::FGeneratedWrappedTypeReferences`  
`struct FGeneratedWrappedTypeReferences`  
_L362-373_
- desc: Struct used to build up a list of wrapped type references that still need to be generated
- L364 _public function_ `bool HasReferences() const`
- L369 _public member_ `TSet<const UClass*> ClassReferences;`
- L370 _public member_ `TSet<const UScriptStruct*> StructReferences;`
- L371 _public member_ `TSet<const UEnum*> EnumReferences;`
- L372 _public member_ `TSet<const UFunction*> DelegateReferences;`

#### Free symbols / members of external scopes

- L54 _prototype_ `ENUM_CLASS_FLAGS(EPyTypeGenerationFlags);`
- L375 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModuleDirtied, FName);`
- L565 _prototype_ `void ShutdownPyWrappers();`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonOnlineDocsCommandlet.h` (Private)


#### class `UPythonOnlineDocsCommandlet`  
`class UPythonOnlineDocsCommandlet : public UCommandlet`  
_L17-28_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Minimal commandlet to format and write Python API online docs. Can be passed the following flags to filter which types are included in the docs: -IncludeEngine -IncludeEnterprise -IncludeInternal -IncludeProject
- L23 _public prototype_ `UPythonOnlineDocsCommandlet();` — Default constructor.
- L26 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptCommandlet.h` (Private)


#### class `UPythonScriptCommandlet`  
`class UPythonScriptCommandlet : public UCommandlet`  
_L10-18_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Minimal commandlet to invoke a Python script and exit
- L16 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptLibrary.h` (Private)


#### class `UPythonScriptLibrary`  
`class UPythonScriptLibrary : public UBlueprintFunctionLibrary`  
_L11-73_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L21 _public prototype_ `static bool IsPythonAvailable();` — `UFUNCTION(BlueprintCallable, Category = "Python|Execution")` — Check to see whether Python support is available in the current environment. @note This may return false until IsPythonConfigured is true.
- L28 _public prototype_ `static bool IsPythonConfigured();` — `UFUNCTION(BlueprintCallable, Category = "Python|Execution")` — Check to see whether Python has been configured. @note Python may be configured but not yet be initialized (@see IsPythonInitialized).
- L34 _public prototype_ `static bool IsPythonInitialized();` — `UFUNCTION(BlueprintCallable, Category = "Python|Execution")` — Check to see whether Python has been initialized and is ready to use.
- L41 _public prototype_ `static bool ForceEnablePythonAtRuntime();` — `UFUNCTION(BlueprintCallable, Category = "Python|Execution")` — Force Python to be enabled and initialized, regardless of the settings that control its default enabled state. @return True if Python was requested to be enabled. Use IsPythonInitialized to verify that it actually initialized.
- L49 _public prototype_ `static bool ExecutePythonCommand(UPARAM(meta=(MultiLine=True)) const FString& PythonCommand);` — `UFUNCTION(BlueprintCallable, Category = "Python|Execution")` — Execute the given Python command. @param PythonCommand The command to run. This may be literal Python code, or a file (with optional arguments) that you want to run. @return true if the command ran successfully, false if there were errors (the output log will show the errors).
- L61 _public prototype_ `static bool ExecutePythonCommandEx(UPARAM(meta=(MultiLine=True)) const FString& PythonCommand, FString& CommandResult, TArray<FPythonLogOutputEntry>& LogOutput, const EPythonCommandExecutionMode ExecutionMode = EPythonCommandExecutionMode::ExecuteFile, const EPythonFileExecutionScope FileExecutionScope = EPythonFileExecutionScope::Private);` — `UFUNCTION(BlueprintCallable, Category = "Python|Execution", meta=(DisplayName="Execute Python Command (Advanced)", AdvancedDisplay="ExecutionMode,FileExecutionScope"))` — Execute the given Python command. @param PythonCommand The command to run. This may be literal Python code, or a file (with optional arguments) that you want to run. @param ExecutionMode Controls the mode used to execute the command. @param FileExecutionScope Controls the scope used when executing Python files. @param CommandResult The result of running the command. On success, for EvaluateStatement mode this will be the actual result of running the command, and will be None in all other cases. On failure, this will be the error information (typically a Python exception trace). @param LogOutput The log output captured while running the command. @return true if the command ran successfully, false if there were errors (the output log will show the errors).
- L71 _public prototype_ `static bool ExecutePythonScript(UPARAM(meta=(MultiLine=True)) const FString& PythonScript, const TArray<FString>& PythonInputs, const TArray<FString>& PythonOutputs);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "Python|Execution", meta=(Variadic, BlueprintInternalUseOnly="true"), DisplayName = "Execute Python Script")` — Execute a Python script with argument marshaling. @param PythonScript This literal Python code to run. @param PythonInputs The variadic input argument names (internal; set by UK2Node_ExecutePythonScript). @param PythonInputs The variadic output argument names (internal; set by UK2Node_ExecutePythonScript). @return true if the command ran successfully, false if there were errors (the output log will show the errors).

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptPlugin.h` (Private)


#### class `FPythonCommandExecutor`  
`class FPythonCommandExecutor : public IConsoleCommandExecutor`  
_L33-53_
- inherits: `IConsoleCommandExecutor`
- desc: Executor for "Python" commands
- L36 _public prototype_ `FPythonCommandExecutor(IPythonScriptPlugin* InPythonScriptPlugin);`
- L38 _public prototype_ `static FName StaticName();`
- L39 _public prototype_ `virtual FName GetName() const override;`
- L40 _public prototype_ `virtual FText GetDisplayName() const override;`
- L41 _public prototype_ `virtual FText GetDescription() const override;`
- L42 _public prototype_ `virtual FText GetHintText() const override;`
- L43 _public prototype_ `virtual void GetSuggestedCompletions(const TCHAR* Input, TArray<FConsoleSuggestion>& Out) override;`
- L44 _public prototype_ `virtual void GetExecHistory(TArray<FString>& Out) override;`
- L45 _public prototype_ `virtual bool Exec(const TCHAR* Input) override;`
- L46 _public prototype_ `virtual bool AllowHotKeyClose() const override;`
- L47 _public prototype_ `virtual bool AllowMultiLine() const override;`
- L48 _public prototype_ `virtual FInputChord GetHotKey() const override;`
- L49 _public prototype_ `virtual FInputChord GetIterateExecutorHotKey() const override;`
- L52 _private member_ `IPythonScriptPlugin* PythonScriptPlugin;`

#### class `FPythonREPLCommandExecutor`  
`class FPythonREPLCommandExecutor : public IConsoleCommandExecutor`  
_L58-78_
- inherits: `IConsoleCommandExecutor`
- desc: Executor for "Python (REPL)" commands
- L61 _public prototype_ `FPythonREPLCommandExecutor(IPythonScriptPlugin* InPythonScriptPlugin);`
- L63 _public prototype_ `static FName StaticName();`
- L64 _public prototype_ `virtual FName GetName() const override;`
- L65 _public prototype_ `virtual FText GetDisplayName() const override;`
- L66 _public prototype_ `virtual FText GetDescription() const override;`
- L67 _public prototype_ `virtual FText GetHintText() const override;`
- L68 _public prototype_ `virtual void GetSuggestedCompletions(const TCHAR* Input, TArray<FConsoleSuggestion>& Out) override;`
- L69 _public prototype_ `virtual void GetExecHistory(TArray<FString>& Out) override;`
- L70 _public prototype_ `virtual bool Exec(const TCHAR* Input) override;`
- L71 _public prototype_ `virtual bool AllowHotKeyClose() const override;`
- L72 _public prototype_ `virtual bool AllowMultiLine() const override;`
- L73 _public prototype_ `virtual FInputChord GetHotKey() const override;`
- L74 _public prototype_ `virtual FInputChord GetIterateExecutorHotKey() const override;`
- L77 _private member_ `IPythonScriptPlugin* PythonScriptPlugin;`

#### struct `IPythonCommandMenu`  
`struct IPythonCommandMenu`  
_L83-91_
- L85 _public prototype_ `virtual ~IPythonCommandMenu() = default;`
- L87 _public prototype_ `virtual void OnStartupMenu() = 0;`
- L88 _public prototype_ `virtual void OnShutdownMenu() = 0;`
- L90 _public prototype_ `virtual void OnRunFile(const FString& InFile, bool bAdd) = 0;`

#### class `FPythonScriptPlugin`  
`class FPythonScriptPlugin final : public IPythonScriptPlugin , public FSelfRegisteringExec , public FEnumEditorUtils::INotifyOnEnumChanged`  
_L94-253_
- inherits: `IPythonScriptPlugin,FSelfRegisteringExec,FEnumEditorUtils::INotifyOnEnumChanged`
- L100 _public prototype_ `FPythonScriptPlugin();`
- L103 _public function_ `static FPythonScriptPlugin* Get()` — Get this module
- L109 _public prototype_ `virtual bool IsPythonAvailable() const override;`
- L110 _public prototype_ `virtual bool IsPythonConfigured() const override;`
- L111 _public prototype_ `virtual bool IsPythonInitialized() const override;`
- L112 _public prototype_ `virtual bool ForceEnablePythonAtRuntime(UE::FSourceLocation Location = UE::FSourceLocation::Current()) override;`
- L113 _public prototype_ `virtual void ForceDisablePythonAtRuntime(UE::FSourceLocation Location = UE::FSourceLocation::Current()) override;`
- L114 _public prototype_ `virtual bool ExecPythonCommand(const TCHAR* InPythonCommand) override;`
- L115 _public prototype_ `virtual bool ExecPythonCommandEx(FPythonCommandEx& InOutPythonCommand) override;`
- L116 _public prototype_ `virtual FString GetInterpreterExecutablePath() const override;`
- L117 _public prototype_ `virtual FSimpleMulticastDelegate& OnPythonConfigured() override;`
- L118 _public prototype_ `virtual FSimpleMulticastDelegate& OnPythonInitialized() override;`
- L119 _public prototype_ `virtual FSimpleMulticastDelegate& OnPythonShutdown() override;`
- L121 _public prototype_ `bool ForceEnablePythonAtRuntime(const FString& Location);`
- L124 _public prototype_ `virtual void StartupModule() override;`
- L125 _public prototype_ `virtual void ShutdownModule() override;`
- L128 _public prototype_ `virtual void PreChange(const UUserDefinedEnum* Enum, FEnumEditorUtils::EEnumEditorChangeInfo Info) override;`
- L129 _public prototype_ `virtual void PostChange(const UUserDefinedEnum* Enum, FEnumEditorUtils::EEnumEditorChangeInfo Info) override;`
- L131 _public prototype_ `virtual void AddStartupScriptAllowPath(FName Owner, const FString& Path) override;`
- L132 _public prototype_ `virtual void RemoveStartupScriptAllowPath(FName Owner) override;`
- L135 _public prototype_ `void RunStartupScripts();`
- L138 _public prototype_ `void SyncRemoteExecutionToSettings();` — Sync the remote execution environment to the current settings, starting or stopping it as required
- L144 _public prototype_ `void ImportUnrealModule(const TCHAR* InModuleName);` — Import the given module into the "unreal" package. This function will take the given name and attempt to import either "unreal_{name}" or "_unreal_{name}" into the "unreal" package as "unreal.{name}".
- L147 _public prototype_ `PyObject* EvalString(const TCHAR* InStr, const TCHAR* InContext, const int InMode);` — Evaluate/Execute a Python string, and return the result
- L148 _public prototype_ `PyObject* EvalString(const TCHAR* InStr, const TCHAR* InContext, const int InMode, PyObject* InGlobalDict, PyObject* InLocalDict);`
- L151 _public prototype_ `bool RunString(FPythonCommandEx& InOutPythonCommand);` — Run literal Python script
- L154 _public prototype_ `bool RunFile(const TCHAR* InFile, const TCHAR* InArgs, FPythonCommandEx& InOutPythonCommand);` — Run a Python file
- L156 _public function_ `PyObject* GetDefaultGlobalDict()`
- L157 _public function_ `PyObject* GetDefaultLocalDict()`
- L158 _public function_ `PyObject* GetConsoleGlobalDict()`
- L159 _public function_ `PyObject* GetConsoleLocalDict()`
- L164 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L168 _private prototype_ `void OnPostEngineInit();`
- L170 _private prototype_ `void ConfigureAndInitializePython();`
- L172 _private prototype_ `bool InitializePython();`
- L174 _private prototype_ `void ShutdownPython();`
- L176 _private prototype_ `void RequestStubCodeGeneration();`
- L178 _private prototype_ `void GenerateStubCode();`
- L180 _private prototype_ `void Tick(const float InDeltaTime);`
- L182 _private prototype_ `void OnModuleDirtied(FName InModuleName);`
- L184 _private prototype_ `void OnModulesChanged(FName InModuleName, EModuleChangeReason InModuleChangeReason);`
- L186 _private prototype_ `void OnContentPathMounted(const FString& InAssetPath, const FString& InFilesystemPath);`
- L188 _private prototype_ `void OnContentPathDismounted(const FString& InAssetPath, const FString& InFilesystemPath);`
- L190 _private prototype_ `static void RegisterModulePaths(const FString& InFilesystemPath);`
- L192 _private prototype_ `static void UnregisterModulePaths(const FString& InFilesystemPath);`
- L194 _private prototype_ `static bool IsDeveloperModeEnabled();`
- L196 _private prototype_ `static ETypeHintingMode GetTypeHintingMode();`
- L198 _private prototype_ `void OnAssetRenamed(const FAssetData& Data, const FString& OldName);`
- L200 _private prototype_ `void OnAssetRemoved(const FAssetData& Data);`
- L202 _private prototype_ `void OnAssetReload(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);`
- L204 _private prototype_ `void OnAssetUpdated(const UObject* InObj);`
- L206 _private prototype_ `void OnPreGarbageCollect();`
- L209 _private prototype_ `void OnPrepareToCleanseEditorObject(UObject* InObject);`
- L211 _private prototype_ `void OnPIEEnd(const bool bIsSimulating);`
- L213 _private prototype_ `void PopulatePythonFileContextMenu(UToolMenu* InMenu);`
- L215 _private member_ `TStrongObjectPtr<UContentBrowserFileDataSource> PythonFileDataSource;`
- L218 _private member_ `TUniquePtr<FPythonScriptRemoteExecution> RemoteExecution;`
- L219 _private member_ `FPythonCommandExecutor CmdExec;`
- L220 _private member_ `FPythonREPLCommandExecutor CmdREPLExec;`
- L221 _private member_ `TUniquePtr<IPythonCommandMenu> CmdMenu = nullptr;`
- L222 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L223 _private member_ `FTSTicker::FDelegateHandle TickOnceHandle;`
- L224 _private member_ `FTSTicker::FDelegateHandle ModuleDelayedHandle;`
- L225 _private member_ `TArray<FString> DeferredCommands;`
- L227 _private member_ `PyUtil::FPyApiBuffer PyProgramName;`
- L228 _private member_ `PyUtil::FPyApiBuffer PyHomePath;`
- L229 _private member_ `FPyObjectPtr PyDefaultGlobalDict;`
- L230 _private member_ `FPyObjectPtr PyDefaultLocalDict;`
- L231 _private member_ `FPyObjectPtr PyConsoleGlobalDict;`
- L232 _private member_ `FPyObjectPtr PyConsoleLocalDict;`
- L233 _private member_ `FPyObjectPtr PyUnrealModule;`
- L234 _private member_ `PyThreadState* PyMainThreadState = nullptr;`
- L235 _private member_ `bool bIsConfigured = false;`
- L236 _private member_ `bool bIsInterpreterInitialized = false;` — Python interpreter is available; may not yet have run startup scripts
- L237 _private member_ `bool bIsFullyInitialized = false;` — Python interpreter is available, and start-up scripts have run
- L238 _private member_ `bool bIsEnabled = false;`
- L239 _private member_ `bool bIsForceEnabledAtRuntime = false;`
- L240 _private member_ `bool bHasTicked = false;`
- L243 _private member_ `PyConfig ModulePyConfig;`
- L244 _private member_ `static PyUtil::FPyApiBuffer Utf8String;`
- L248 _private member_ `FSimpleMulticastDelegate OnPythonConfiguredDelegate;`
- L249 _private member_ `FSimpleMulticastDelegate OnPythonInitializedDelegate;`
- L250 _private member_ `FSimpleMulticastDelegate OnPythonShutdownDelegate;`
- L252 _private member_ `FPathPermissionList StartupScriptAllowedPaths;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptPluginSettings.h` (Private)


#### enum `ETypeHintingMode`  
`enum class ETypeHintingMode : uint8`  
_L11-30_
- reflection: `UENUM()`
- L14 _public enumerator_ `Off` — Turn off type hinting.
- L21 _public enumerator_ `AutoCompletion` — When generating the Python stub and to some extend the Docstrings, enables type hinting (PEP 484) to get the best experience with a Python IDE auto-completion. The hinting will list the exact input types, omit type coercions and will assume all reflected unreal.Object cannot be None which is not true, but will let the function signature easy to read.
- L29 _public enumerator_ `TypeChecker` — Enables type hinting for static type checking. Hint as close as possible the real supported types including possible type coercions. Because the UE reflection API doesn't provide all the required information, some tradeoffs are required that do not always reflect the reality. For example, reflected UObject will always be marked as 'possibly None'. While this is true in some contexts, it is not true all the time.

#### enum `EPythonEnabledOverrideState`  
`enum class EPythonEnabledOverrideState : uint8`  
_L33-43_
- reflection: `UENUM()`
- L36 _public enumerator_ `None` — Python will be enabled based on the current project settings and any command line overrides.
- L39 _public enumerator_ `Enable` — Enable Python, even if the project has it disabled by default (behaves like '-EnablePython' on the command line). Note: Does not take precedence over '-DisablePython' on the command line.
- L42 _public enumerator_ `Disable` — Disable Python, even if the project has it enabled by default (behaves like '-DisablePython' on the command line). Note: Does not take precedence over '-EnablePython' on the command line.

#### class `UPythonScriptPluginSettings`  
`class UPythonScriptPluginSettings : public UDeveloperSettings`  
_L49-149_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Configure the Python plug-in.
- L54 _public prototype_ `UPythonScriptPluginSettings();`
- L58 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L59 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L62 _public prototype_ `virtual FText GetSectionText() const override;`
- L67 _public member_ `TArray<FString> StartupScripts;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true, MultiLine=true))` — Array of Python scripts to run at start-up (run before the first Tick after the Engine has initialized).
- L71 _public member_ `TArray<FDirectoryPath> AdditionalPaths;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true, RelativePath))` — Array of additional paths to add to the Python system paths.
- L81 _public member_ `bool bIsolateInterpreterEnvironment = true;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))` — Should the embedded interpreter be run in isolation mode. In isolation, the standard PYTHON* environment variables (PYTHONPATH, PYTHONHOME, etc), the script's directory and the user's site-packages directory are ignored by the interpreter. This prevents incompabible software to crash the engine. Consider turning this option off if you tightly control your Python environment and you are sure everything is compatible. Note that the UE_PYTHONPATH environment variable is added to 'sys.path' whether the interpreter runs in insolation mode or not.
- L91 _public member_ `bool bDeveloperMode;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true, DisplayName="Developer Mode (all users)"), AdvancedDisplay)` — Should Developer Mode be enabled on the Python interpreter *for all users of the project* Note: Most of the time you want to enable bDeveloperMode in the Editor Preferences instead! (will also enable extra warnings (e.g., for deprecated code), and enable stub code generation for use with external IDEs).
- L102 _public member_ `bool bRunPipInstallOnStartup = true;` — `UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, meta=(ConfigRestartRequired=true))` — Should the pip install task be run on python engine initialization. NOTE: The project pip install directory: <ProjectDir>/Intermediate/PipInstall/Lib/site-packages will still be added to site package path, to allow for pre-populated or deferred installs. See <ProjectDir>/Intermediate/PipInstall/merged_requirements.in for listing of required packages.
- L108 _public member_ `bool bPipStrictHashCheck = true;` — `UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))` — Require pip to use strict hash checking for all packages WARNING: Disabling this setting is a security risk, particularly when combined with IndexUrl override
- L112 _public member_ `bool bOfflineOnly = false;` — `UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))` — Only run pip to generate merged requirements and/or validate requested packages are installed
- L118 _public member_ `FString OverrideIndexURL;` — `UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))` — Override all index/extra-index URLs, this is useful for internal NAT installs (using e.g. devpi or similar index cache) WARNING: Strict hash checks should be enabled if an override index url is used
- L124 _public member_ `FString ExtraInstallArgs;` — `UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))` — Additional arguments passed to main pip install call, useful to add e.g. --cert or other proxy options for restrictive firewalls NOTE: Do not use this to add --index-url or --extra-index-url, instead use OverrideIndexURL setting or ExtraIndexUrls uplugin property, respectively
- L128 _public member_ `bool bRemoteExecution;` — `UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, meta=(DisplayName="Enable Remote Execution?"))` — Should remote Python execution be enabled?
- L132 _public member_ `FString RemoteExecutionMulticastGroupEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Multicast Group Endpoint"))` — The multicast group endpoint (in the form of IP_ADDRESS:PORT_NUMBER) that the UDP multicast socket should join
- L136 _public member_ `FString RemoteExecutionMulticastBindAddress;` — `UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Multicast Bind Address"))` — The adapter address that the UDP multicast socket should bind to, or 0.0.0.0 to bind to all adapters
- L140 _public member_ `int32 RemoteExecutionSendBufferSizeBytes;` — `UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Send Buffer Size", Units="Bytes"))` — Size of the send buffer for the remote endpoint connection
- L144 _public member_ `int32 RemoteExecutionReceiveBufferSizeBytes;` — `UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Receive Buffer Size", Units="Bytes"))` — Size of the receive buffer for the remote endpoint connection
- L148 _public member_ `uint8 RemoteExecutionMulticastTtl;` — `UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Multicast Time-To-Live"))` — The TTL that the UDP multicast socket should use (0 is limited to the local host, 1 is limited to the local subnet)

#### class `UPythonScriptPluginUserSettings`  
`class UPythonScriptPluginUserSettings : public UDeveloperSettings`  
_L153-192_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L158 _public prototype_ `UPythonScriptPluginUserSettings();`
- L162 _public prototype_ `virtual FText GetSectionText() const override;`
- L169 _public member_ `EPythonEnabledOverrideState EnablePythonOverride = EPythonEnabledOverrideState::None;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))` — Should we override the default enabled state for Python for this project?
- L178 _public member_ `bool bDeveloperMode;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))` — Should Developer Mode be enabled on the Python interpreter? (will also enable extra warnings (e.g., for deprecated code), and enable stub code generation for use with external IDEs).
- L187 _public member_ `ETypeHintingMode TypeHintingMode = ETypeHintingMode::AutoCompletion;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))` — Should the generated Python stub and API documentation have type hints. This enables standard Python type hinting (PEP 484) for the classes, structs, methods, properties, constants, etc. exposed by the engine. If the developer mode is enabled and the Python IDE configured to use the generated Python stub, types will be displayed in auto-completion popup and used by the IDE static type checkers. This has no effects on the execution of the code. (Requires Python >= 3.7)
- L191 _public member_ `bool bEnableContentBrowserIntegration;` — `UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))` — Should Python scripts be available in the Content Browser?

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptPluginStyle.h` (Private)


#### class `FPythonScriptPluginEditorStyle`  
`class FPythonScriptPluginEditorStyle : public FSlateStyleSet`  
_L11-24_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines the styles for Python UI in the Editor
- L15 _public member_ `static FName StyleName;`
- L18 _public prototype_ `static FPythonScriptPluginEditorStyle& Get();` — Access the singleton instance for this style set
- L22 _private prototype_ `FPythonScriptPluginEditorStyle();`
- L23 _private prototype_ `~FPythonScriptPluginEditorStyle();`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptRemoteExecution.h` (Private)


#### class `FPythonScriptRemoteExecution`  
`class FPythonScriptRemoteExecution`  
_L17-59_
- L23 _public prototype_ `explicit FPythonScriptRemoteExecution(IPythonScriptPlugin* InPythonScriptPlugin);`
- L24 _public prototype_ `~FPythonScriptRemoteExecution();`
- L27 _public prototype_ `bool Start();` — Start remote execution based on the current settings (also called during construction if remote execution should be active)
- L30 _public prototype_ `void Stop();` — Stop remote execution (also called during destruction if remote execution is active)
- L33 _public prototype_ `void SyncToSettings();` — Sync the remote execution environment to the current settings, starting or stopping it as required
- L36 _public prototype_ `void Tick(const float InDeltaTime);` — Tick, processing and sending messages as required
- L40 _private prototype_ `void OpenCommandConnection(const FString& InRemoteNodeId, const FIPv4Endpoint& InCommandEndpoint);` — Open a command connection to the given remote node, at the given endpoint
- L43 _private prototype_ `void CloseCommandConnection(const FString& InRemoteNodeId);` — Close any existing command connection to the given remote node
- L46 _private member_ `IPythonScriptPlugin* PythonScriptPlugin;` — The Python plugin that owns this instance
- L49 _private member_ `ISocketSubsystem* SocketSubsystem;` — Cached socket subsystem pointer
- L52 _private member_ `FString NodeId;` — The ID of this remote execution node
- L55 _private member_ `TUniquePtr<FPythonScriptRemoteExecutionCommandConnection> CommandConnection;` — Connection handling TCP commands
- L58 _private member_ `TUniquePtr<FPythonScriptRemoteExecutionBroadcastConnection> BroadcastConnection;` — Connection handling UDP broadcast

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Public/IPipInstall.h` (Public)


#### struct `ICmdProgressNotifier`  
`struct ICmdProgressNotifier`  
_L12-18_
- desc: Interface for wrapping a notifier that can return info from pip install
- L14 _public prototype_ `virtual void UpdateProgress(float UpdateWorkDone, float UpdateTotalWork, const FText& Status) = 0;`
- L15 _public prototype_ `virtual void Completed(bool bSuccess) = 0;`
- L17 _public prototype_ `virtual ~ICmdProgressNotifier()= default;`

#### class `IPipInstall`  
`class IPipInstall`  
_L23-44_
- desc: Interface to pip installer used by python script plugin for installing plugin python dependencies
- L26 _public prototype_ `static IPipInstall& Get();`
- L29 _public prototype_ `virtual bool InitPipInstall() = 0;` — Initialize the internal pip virtual env and check enabled plugins for python dependencies
- L31 _public prototype_ `virtual bool LaunchPipInstall(bool RunAsync, TSharedPtr<ICmdProgressNotifier> CmdProgressNotifier = nullptr, FSimpleDelegate OnCompleted = FSimpleDelegate()) = 0;` — Run pip to install all missing python dependencies for enabled plugins
- L33 _public prototype_ `virtual bool IsInstalling() = 0;` — Check if a background install is running
- L36 _public prototype_ `virtual int32 GetNumPackagesToInstall() = 0;` — Get number of missing python packages to install
- L38 _public prototype_ `virtual bool GetPackageInstallList(TArray<FString>& PyPackages) = 0;` — Get list of python packages to install
- L41 _public prototype_ `virtual bool RegisterPipSitePackagesPath() const = 0;` — Register the site-packages path with embedded python env
- L43 _public prototype_ `virtual ~IPipInstall()= default;`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Public/IPythonScriptPlugin.h` (Public)


#### class `IPythonScriptPlugin`  
`class IPythonScriptPlugin : public IModuleInterface`  
_L11-124_
- inherits: `IModuleInterface`
- L15 _public function_ `static IPythonScriptPlugin* Get()` — Get this module
- L25 _public prototype_ `virtual bool IsPythonAvailable() const = 0;` — Check to see whether the plugin has Python support enabled. @note This may return false until IsPythonConfigured is true.
- L31 _public prototype_ `virtual bool IsPythonConfigured() const = 0;` — Check to see whether Python has been configured. @note Python may be configured but not yet be initialized (@see IsPythonInitialized).
- L36 _public prototype_ `virtual bool IsPythonInitialized() const = 0;` — Check to see whether Python has been initialized and is ready to use.
- L42 _public prototype_ `virtual bool ForceEnablePythonAtRuntime(UE::FSourceLocation Location = UE::FSourceLocation::Current()) = 0;` — Force Python to be enabled and initialized, regardless of the settings that control its default enabled state. @return False if Python can't be enabled ever. Use IsPythonInitialized to verify that it actually initialized.
- L47 _public prototype_ `virtual void ForceDisablePythonAtRuntime(UE::FSourceLocation Location = UE::FSourceLocation::Current()) = 0;` — Force Python to shutdown.
- L54 _public prototype_ `virtual bool ExecPythonCommand(const TCHAR* InPythonCommand) = 0;` — Execute the given Python command. This may be literal Python code, or a file (with optional arguments) that you want to run. @return true if the command ran successfully, false if there were errors (the output log will show the errors).
- L60 _public prototype_ `virtual bool ExecPythonCommandEx(FPythonCommandEx& InOutPythonCommand) = 0;` — Execute the given Python command. @return true if the command ran successfully, false if there were errors.
- L65 _public prototype_ `virtual FString GetInterpreterExecutablePath() const = 0;` — Get the path to the Python interpreter executable of the Python SDK this plugin was compiled against.
- L70 _public prototype_ `virtual FSimpleMulticastDelegate& OnPythonConfigured() = 0;` — Delegate called after Python has been configured.
- L75 _public prototype_ `virtual FSimpleMulticastDelegate& OnPythonInitialized() = 0;` — Delegate called after Python has been initialized.
- L80 _public prototype_ `virtual FSimpleMulticastDelegate& OnPythonShutdown() = 0;` — Delegate called before Python is shutdown.
- L85 _public function_ `void RegisterOnPythonConfigured(FSimpleDelegate&& Callback)` — Wrapper around OnPythonConfigured that will either register the callback, or call it immediately if IsPythonConfigured is already true.
- L100 _public function_ `void RegisterOnPythonInitialized(FSimpleDelegate&& Callback)` — Wrapper around OnPythonInitialized that will either register the callback, or call it immediately if IsPythonInitialized is already true.
- L117 _public prototype_ `virtual void AddStartupScriptAllowPath(FName Owner, const FString& Path) = 0;` — Add allowed paths for startup script filtering in restrictive mode. @param Owner Owner name for cleanup @param Path The path prefix to allow
- L123 _public prototype_ `virtual void RemoveStartupScriptAllowPath(FName Owner) = 0;` — Remove all startup script allow paths registered by the given owner. @param Owner - Owner name whose entries should be removed

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Public/PipInstallHelpers.h` (Public)


#### enum `EPipInstallDialogResult`  
`enum EPipInstallDialogResult`  
_L10-16_
- desc: PipInstall dialog responses
- L12 _public enumerator_ `BackgroundInstall`
- L13 _public enumerator_ `Finished`
- L14 _public enumerator_ `Canceled`
- L15 _public enumerator_ `Error`

#### class `FPipInstallHelper`  
`class FPipInstallHelper`  
_L21-32_
- desc: Simplified UI helper for creating a modal dialog and running (background) installs
- L25 _public prototype_ `static int32 GetNumPackagesToInstall();` — Check if pip install is required
- L28 _public prototype_ `static EPipInstallDialogResult ShowPipInstallDialog(bool bAllowBackgroundInstall = true, FSimpleDelegate OnCompleted = FSimpleDelegate());` — Show notification that pip install is required
- L31 _public prototype_ `static bool LaunchHeadlessPipInstall();` — Run a headless pip install (for commandlets/build machines)

#### class `FPythonScriptInitHelper`  
`class FPythonScriptInitHelper`  
_L37-42_
- desc: Helpers for handling standard delegate pipeline pattern for python/pip install
- L40 _public prototype_ `static void InitPython(FSimpleDelegate OnInitialized, FSimpleDelegate OnPythonUnavailable = FSimpleDelegate());`
- L41 _public prototype_ `static void InitPythonAndPipInstall(FSimpleDelegate OnPipInstalled, FSimpleDelegate OnPythonUnavailable = FSimpleDelegate());`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PYTHONSCRIPTPLUGIN_API`

### `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Public/PythonScriptTypes.h` (Public)


#### enum `EPythonLogOutputType`  
`enum class EPythonLogOutputType : uint8`  
_L13-21_
- reflection: `UENUM()`
- desc: Types of log output that Python can give.
- L16 _public enumerator_ `Info` — This log was informative.
- L18 _public enumerator_ `Warning` — This log was a warning.
- L20 _public enumerator_ `Error` — This log was an error.

#### enum `EPythonCommandFlags`  
`enum class EPythonCommandFlags : uint8`  
_L25-31_
- reflection: `UENUM()`
- desc: Flags that can be specified when running Python commands.
- L28 _public enumerator_ `None = 0` — No special behavior.
- L30 _public enumerator_ `Unattended = 1<<0` — Run the Python command in "unattended" mode (GIsRunningUnattendedScript set to true), which will suppress certain pieces of UI.

#### enum `EPythonCommandExecutionMode`  
`enum class EPythonCommandExecutionMode : uint8`  
_L36-44_
- reflection: `UENUM()`
- desc: Controls the execution mode used for the Python command.
- L39 _public enumerator_ `ExecuteFile` — Execute the Python command as a file. This allows you to execute either a literal Python script containing multiple statements, or a file with optional arguments.
- L41 _public enumerator_ `ExecuteStatement` — Execute the Python command as a single statement. This will execute a single statement and print the result. This mode cannot run files.
- L43 _public enumerator_ `EvaluateStatement` — Evaluate the Python command as a single statement. This will evaluate a single statement and return the result. This mode cannot run files.

#### enum `EPythonFileExecutionScope`  
`enum class EPythonFileExecutionScope : uint8`  
_L48-54_
- reflection: `UENUM()`
- desc: Controls the scope used when executing Python files.
- L51 _public enumerator_ `Private` — Execute the Python file with its own unique locals and globals dict to isolate any changes it makes to the environment (like imports).
- L53 _public enumerator_ `Public` — Execute the Python file with the shared locals and globals dict as used by the console, so that executing it behaves as if you'd ran the file contents directly in the console.

#### struct `FPythonLogOutputEntry`  
`struct FPythonLogOutputEntry`  
_L58-69_
- reflection: `USTRUCT(BlueprintType)`
- desc: Log output entry captured from Python.
- L64 _public member_ `EPythonLogOutputType Type = EPythonLogOutputType::Info;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python|Output")` — The type of the log output.
- L68 _public member_ `FString Output;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python|Output")` — The log output string.

#### struct `FPythonCommandEx`  
`struct FPythonCommandEx`  
_L72-91_
- desc: Extended information when executing Python commands.
- L75 _public member_ `EPythonCommandFlags Flags = EPythonCommandFlags::None;` — Flags controlling how the command should be run.
- L78 _public member_ `EPythonCommandExecutionMode ExecutionMode = EPythonCommandExecutionMode::ExecuteFile;` — Controls the mode used to execute the command.
- L81 _public member_ `EPythonFileExecutionScope FileExecutionScope = EPythonFileExecutionScope::Private;` — Controls the scope used when executing Python files.
- L84 _public member_ `FString Command;` — The command to run. This may be literal Python code, or a file (with optional arguments) to run.
- L87 _public member_ `FString CommandResult;` — The result of running the command. On success, for EvaluateStatement mode this will be the actual result of running the command, and will be None in all other cases. On failure, this will be the error information (typically a Python exception trace).
- L90 _public member_ `TArray<FPythonLogOutputEntry> LogOutput;` — The log output captured while running the command.

#### Free symbols / members of external scopes

- L32 _prototype_ `ENUM_CLASS_FLAGS(EPythonCommandFlags);`
- L93 _function_ `inline const TCHAR* LexToString(EPythonLogOutputType InType)`
- L109 _function_ `inline const TCHAR* LexToString(EPythonCommandExecutionMode InMode)`
- L125 _function_ `inline bool LexTryParseString(EPythonCommandExecutionMode& OutMode, const TCHAR* InBuffer)`
- L145 _function_ `inline void LexFromString(EPythonCommandExecutionMode& OutMode, const TCHAR* InBuffer)`
