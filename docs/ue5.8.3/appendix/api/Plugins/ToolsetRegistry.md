# Plugins / ToolsetRegistry

- module root: `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry`
- headers: 37; symbols: 439
- symbol kinds: class=32, delegate=3, enum=1, enumerator=2, externvar=2, function=31, macro=16, member=71, namespace=56, prototype=207, struct=10, typedef=8
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, DeveloperSettings, EditorFramework, EditorScriptingUtilities, EditorSubsystem, Engine, FileSandboxCore, Json, JsonUtilities, JsonUtilitiesEditor, Kismet, PythonScriptPlugin, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ColorConverter.h` (Private)


#### class `UE::ToolsetRegistry::FToolsetColorConverter`  
`class FToolsetColorConverter : public FToolsetJsonConverter`  
_L10-29_
- inherits: `FToolsetJsonConverter`
- desc: Converts FColor and FLinearColor.
- L13 _public prototype_ `virtual FString GetName() const override;`
- L15 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L17 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema( TNotNull<const FProperty*> Property) override;`
- L20 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault( TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L23 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData( TNotNull<FProperty*> Property, const void* Value) override;`
- L26 _public prototype_ `virtual bool JsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/EngineDelegatesCompatibility.h` (Private)


#### struct `FOnPostEngineInit`  
`template<typename T> struct FOnPostEngineInit`  
_L10-23_
- desc: Temporarily used to determine whether FCoreDelegates::GetOnPostEngineInit() is available until it's present in all streams.
- L12 _public function_ `static FSimpleMulticastDelegate& Get()`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/FunctionLibraryToolset.h` (Private)


#### class `UE::ToolsetRegistry::FFunctionLibraryToolset`  
`class FFunctionLibraryToolset : public FToolset`  
_L22-86_
- inherits: `FToolset`
- desc: Wraps a UToolsetDefinition for use as a Toolset.
- L26 _public prototype_ `explicit FFunctionLibraryToolset(TSubclassOf<UToolsetDefinition> LibraryClass);`
- L30 _public function_ `virtual FString GetToolsetName() const override` — Returns the name of the toolset
- L36 _public prototype_ `virtual FString GetToolsetVersion() const override;` — Returns the version of the toolset
- L39 _public function_ `virtual UClass* GetToolsetClass() const override` — Returns the UClass that backs this toolset.
- L43 _public function_ `virtual FString GetToolsetDescription() const override` — Returns the description of the toolset from the class's metadata.
- L53 _public prototype_ `TArray<FString> GetToolNames() const;`
- L56 _public prototype_ `bool HasValidTools() const;` — Whether the toolset has a valid set of tools.
- L59 _public prototype_ `static FString GetToolsetClassName(const UClass* InClass);` — Get qualified name for toolset class.
- L64 _protected prototype_ `virtual TFuture<TValueOrError<FString, FString>> ExecuteToolInternal( const FString& ToolName, const FString& JsonInput) override;` — Executes a tool with the given name and JSON input, returning a future with the JSON output.
- L68 _protected prototype_ `virtual FString GetJsonSchemaInternal() const override;` — Returns the JSON schema for the toolset
- L72 _private member_ `TWeakObjectPtr<UClass> ToolsetClass;` — The wrapped toolset function library
- L76 _private member_ `FString ToolsetName;` — Cached toolset name to allow unregistering even when the wrapped toolset class is no longer available.
- L79 _private member_ `TMap<FString, TSharedPtr<FObjectFunctionToolCall>> Tools;` — Map of valid tool names to tool call objects.
- L82 _private prototype_ `TSharedPtr<FJsonObject> GenerateSchema() const;` — Generate schema from reflection data.
- L85 _private prototype_ `void GenerateToolCallObjects();` — Generate Tools list.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/GuidConverter.h` (Private)


#### class `UE::ToolsetRegistry::FToolsetGuidConverter`  
`class FToolsetGuidConverter : public FToolsetJsonConverter`  
_L18-37_
- inherits: `FToolsetJsonConverter`
- desc: Converts FGuid to/from a JSON string in FGuid::EGuidFormats::DigitsWithHyphens form. Quality-of-life converter for agents. Without it, the default FJsonObjectConverter exposes FGuid as an object {a, b, c, d} of four uint32s — agents have to manually plumb the four parts around and sometimes echo them back to the user, which is unreadable. With the converter the schema is a single hex string in standard 8-4-4-4-12 form, so the reflected GUID is human-recognizable in transcripts.
- L21 _public prototype_ `virtual FString GetName() const override;`
- L23 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L25 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema( TNotNull<const FProperty*> Property) override;`
- L28 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault( TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L31 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData( TNotNull<FProperty*> Property, const void* Value) override;`
- L34 _public prototype_ `virtual bool JsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/JsonConversion.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L13 _prototype_ `TSharedPtr<FJsonObject> JsonStringToJsonObject(const FString& JsonString);` (scope `UE::ToolsetRegistry::Internal`) — Convert a JSON string to a JSON object or return a null pointer if the string cannot be parsed or isn't an object.
- L16 _prototype_ `TSharedRef<FJsonObject> JsonObjectOrEmpty(TSharedPtr<FJsonObject> JsonObject);` (scope `UE::ToolsetRegistry::Internal`) — Return either the provided JSON object or return an empty object.
- L20 _prototype_ `TSharedPtr<FJsonValue> JsonStringToJsonValue(const FString& JsonString);` (scope `UE::ToolsetRegistry::Internal`) — Convert a JSON string to a JSON value or return a null pointer if the string cannot be parsed.
- L23 _prototype_ `FString JsonToString(const TSharedRef<FJsonObject> JsonObject);` (scope `UE::ToolsetRegistry::Internal`) — Convert a JSON object to a string.
- L26 _prototype_ `FString JsonToString(const TSharedRef<FJsonValue> JsonValue);` (scope `UE::ToolsetRegistry::Internal`) — Convert a JSON value to a string.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/JsonSchema.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L29 _prototype_ `TSharedRef<FJsonObject> CreateJsonSchema( const FString& Description, EJson Type, const TSharedPtr<FJsonObject> Properties = TSharedPtr<FJsonObject>());` (scope `UE::ToolsetRegistry::Internal`) — Create a minimal JSON schema. See https://json-schema.org/ This is intended to be used to create very simple schemas, if we need something that supports building arbitrary schemas we should probably turn this into a object that implements a builder pattern. Users still need to create constraints like: * Set the "items" or "prefixItems" field for arrays. * Manually create the properties object to define object fields. @param Description is the description of the schema. @param Type is the schema's type. @param Properties specifies the schemas for object fields when Type is EJson::Object. @returns JSON schema object.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/Module.h` (Private)


#### class `FToolsetRegistryModule`  
`class FToolsetRegistryModule : public IModuleInterface`  
_L14-22_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L20 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogToolsetRegistry, Log, Log);` — FToolsetRegistryModule
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogToolsetRegistry, Log, Log);` — FToolsetRegistryModule

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/NamePatternFilter.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L14 _prototype_ `FRegexPattern MakeNamePattern(const FString& Pattern);` (scope `UE::ToolsetRegistry::Internal`) — Compile a name-matching pattern. Patterns enclosed in forward slashes (e.g., /^Foo. ) are treated as regular expressions; all other patterns are matched as case-insensitive substrings.
- L17 _prototype_ `TArray<FRegexPattern> CompilePatterns(const TArray<FString>& PatternStrings);` (scope `UE::ToolsetRegistry::Internal`) — Compile a list of pattern strings into FRegexPattern objects.
- L22 _prototype_ `bool IsNameAllowed( const FString& Name, const TArray<FRegexPattern>& BlockPatterns, const TArray<FRegexPattern>& AllowPatterns);` (scope `UE::ToolsetRegistry::Internal`) — Returns true if Name passes the given block/allow filters. Block always wins. An empty allow-list permits any name that isn't blocked; a non-empty allow-list requires the name to match at least one allow pattern.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ObjectFunctionToolCall.h` (Private)


#### class `UE::ToolsetRegistry::FObjectFunctionToolCall`  
`class FObjectFunctionToolCall : public TSharedFromThis<FObjectFunctionToolCall, ESPMode::ThreadSafe>`  
_L22-92_
- inherits: `TSharedFromThis<FObjectFunctionToolCall,ESPMode::ThreadSafe>`
- L27 _public prototype_ `FObjectFunctionToolCall( TNotNull<UObject*> InInstanceObject, TNotNull<UFunction*> InFunction);` — Use Create() instead of constructing directly.
- L34 _public typedef_ `using FFunctionInputParamsJson = TVariant<TSharedPtr<FJsonObject>, FString>;` — Function input params. Holds either a JSON object or a JSON string.
- L41 _public prototype_ `static TSharedPtr<FObjectFunctionToolCall> Create( TNotNull<UObject*> InInstanceObject, TNotNull<UFunction*> InFunction);` — Create with a UFunction on a UObject instance. @param InInstanceObject UObject containing the function. @param InFunction UFunction contained in the UObject.
- L51 _public prototype_ `static TSharedPtr<FObjectFunctionToolCall> Create( TNotNull<UObject*> InInstanceObject, const FName& InFunctionName);` — Create with a UFunction on a UObject instance, but using the UObject's UClass where the function can be found by name. @param InInstanceObject UObject containing the function. @param InFunctionName UFunction name contained in the UObject. @return A function call object.
- L68 _public prototype_ `TFuture<FJsonValueOrError> Execute( const TOptional<FFunctionInputParamsJson>& FunctionInputParamsJson = TOptional<FFunctionInputParamsJson>(), TSharedPtr<FToolCallExceptionHandler> ExceptionHandler = nullptr) const;` — Given a JSON containing input parameters for a tool call, execute the function with those input parameters. @param FunctionInputParamsJson The optional JSON object or string containing the function parameters. If the function this class was initialized with has required params, then this must be supplied with JSON that provides those required params. Otherwise, an error will result. If the function this class was initialized with has no required params, then this does not need to be supplied. @return Tool call result future. (See above). When tool result does not have an error - Returned objects will either be (1) the object itself, or (2) a value named 'returnValue' inside an object. And this may be null JSON value if (1) function does not return a value, or (2) if function does return a value and that return value is null.
- L77 _public prototype_ `const UFunction* GetFunction() const;` — Returns the wrapped UFunction, or nullptr if it has been destroyed or superseded by a newer version (reinstanced class, reloaded package).
- L80 _private prototype_ `FJsonValueOrError BuildValidFunctionInputParamsJsonObject( const TOptional<FFunctionInputParamsJson>& FunctionInputParamsJson) const;`
- L83 _private prototype_ `FJsonValueOrError MakeResult(FJsonValueOrError&& ValueOrError) const;`
- L85 _private member_ `TWeakObjectPtr<UObject> InstanceObject;`
- L86 _private member_ `TWeakObjectPtr<UFunction> Function;`
- L89 _private member_ `FString FunctionName;` — Cached so error messages still work after the UFunction has been destroyed.
- L91 _private member_ `TSharedPtr<FJsonObject> FunctionSchemaJsonObject;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/PropertyAccessors.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L15 _prototype_ `TOptional<TObjectPtr<UObject>> PropertyValueAsObject( TNotNull<UClass*> Class, TNotNull<FProperty*> Property, TNotNull<const void*> ValueAddress);` (scope `UE::ToolsetRegistry::Internal`) — Get a property value as an object of a specific type. The returned optional is populated if the property matches the specified UClass.
- L22 _function_ `template<typename ObjectT> TOptional<TObjectPtr<ObjectT>> PropertyValueAsObject( TNotNull<FProperty*> Property, TNotNull<const void*> ValueAddress)` (scope `UE::ToolsetRegistry::Internal`) — Get a property value as an object of a specific type. The returned optional is populated if the property matches the UClass ObjectT.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/PythonTestRunner.h` (Private)


#### struct `FPythonTestRunnerSearchOptions`  
`struct FPythonTestRunnerSearchOptions`  
_L21-41_
- reflection: `USTRUCT(BlueprintType, Category="PythonTestRunner")`
- desc: Search parameters for Python tests.
- L28 _public member_ `FString RootModule;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PythonTestRunner")` — See toolset_registry.tests.unittest_runner.TestSearchOptions Python module / package to search under.
- L32 _public member_ `FString TestModuleGlob;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PythonTestRunner")` — Glob used to match test module names.
- L36 _public member_ `TArray<FString> TestNameGlobs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PythonTestRunner")` — Globs used to match individual test names.
- L40 _public prototype_ `TValueOrError<FString, FString> BuildPythonCode() const;` — Generate code to construct toolset_registry.tests.unittest_runner.TestSearchOptions assuming test_runner is imported in the current scope.

#### class `UE::ToolsetRegistry::FPythonAutomationTest`  
`class FPythonAutomationTest : public FAutomationTestBase, public TSharedFromThis<FPythonAutomationTest>`  
_L53-127_
- inherits: `FAutomationTestBase,TSharedFromThis<FPythonAutomationTest>`
- desc: At the moment this has the limitation that all Python tests with class or module level setup and teardown hooks (e.g setUpClass()) will be executed before and after every test case.
- L66 _public prototype_ `FPythonAutomationTest( const FString& Name, const FPythonTestRunnerSearchOptions& SearchOptions, float TimeoutInSeconds = 5.0f);` — @param Name Base name of the test case (e.g My.Tests) which will be prefixed to all Python test case names in test automation view. @param SearchOptions Options used to discover Python test cases. @param TimeoutInSeconds Time to wait for each test case to execute.
- L72 _public prototype_ `virtual EAutomationTestFlags GetTestFlags() const override;`
- L73 _public prototype_ `virtual FString GetBeautifiedTestName() const override;`
- L74 _public prototype_ `virtual uint32 GetRequiredDeviceNum() const override;`
- L81 _public prototype_ `virtual void GetTests( TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const override;` — @param OutBeautifiedNames Same as OutTestCommands. @param OutTestCommands Fully qualified names of Python tests discovered by this class.
- L90 _public prototype_ `virtual bool RunTest(const FString& Parameters) override;` — @returns true if the test started, false otherwise.
- L98 _public prototype_ `TValueOrError<TOptional<bool>, FString> GetLastTestResult(const FString& TestId) const;` — @returns If successful, returns an optional bool value that indicates whether the test is not started or running (not set), succeeded or failed.
- L103 _private prototype_ `TValueOrError<FString, FString> StartTestExecution(const FString& TestId);` — Run a test without waiting for it to complete returning the ID of the test being executed.
- L107 _private prototype_ `bool PollForTestCompletion(const FString& TestId);` — Poll to determine whether a test is complete returning false to continue polling, true to stop polling.
- L110 _private member_ `FPythonTestRunnerSearchOptions SearchOptions;`
- L111 _private member_ `float TimeoutInSeconds;`
- L115 _private prototype_ `static TValueOrError<TArray<FString>, FString> ParseJsonStringArray( const FString& StringArrayJson);` — Parse a JSON string list into a string array.
- L119 _private prototype_ `static TValueOrError<FString, FString> RunTestRunnerPythonCode( const FString& CodeToRun, const FString& ErrorContext);` — Run Python code in a context where json and unittest_runner modules are imported.
- L124 _private prototype_ `static TValueOrError<TArray<FString>, FString> RunAndParseTestCaseIds( const FString& FunctionThatReturnsTestCaseSequence, const FString& ErrorContext);` — Run a function that returns unittest.TestCases returning IDs of the test cases. In this context json and unittest_runner modules are imported.

#### struct `FPythonTestRunnerResult`  
`struct FPythonTestRunnerResult`  
_L132-143_
- reflection: `USTRUCT(BlueprintType, Category="PythonTestRunner")`
- desc: Result of a Python test.
- L138 _public member_ `bool bIsComplete = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PythonTestRunner")` — Whether a queried test has been executed and is complete.
- L142 _public member_ `bool bIsSuccessful = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PythonTestRunner")` — Whether a queried test completed successfully.

#### class `UPythonTestRunner`  
`class UPythonTestRunner : public UObject`  
_L147-232_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category="PythonTestRunner")`
- inherits: `UObject`
- desc: Python automation test runner.
- L161 _public prototype_ `TArray<FString> GetTests() const;` — `UFUNCTION(BlueprintCallable, Category="PythonTestRunner")` — @returns Test IDs discovered by this runner.
- L168 _public prototype_ `void RunTest(const FString& TestId);` — `UFUNCTION(BlueprintCallable, Category="PythonTestRunner")` — @param TestId Python test ID to run. This must be a test ID returned by GetTests().
- L176 _public prototype_ `FPythonTestRunnerResult GetLastTestResult(const FString& TestId) const;` — `UFUNCTION(BlueprintCallable, Category="PythonTestRunner")` — @return Last result of the test.
- L180 _private prototype_ `bool CheckInitialized() const;` — Ensure the instance is initialize otherwise log an error and return false.
- L183 _private prototype_ `void Initialize( const FString& BaseName, const FPythonTestRunnerSearchOptions& SearchOptions, float TimeoutInSeconds);` — Initialize the instance.
- L189 _private prototype_ `void Reset();` — Clear the instance.
- L192 _private member_ `TSharedPtr<UE::ToolsetRegistry::FPythonAutomationTest> Test;`
- L196 _private member_ `TFunction<void(const FString&)> RunTestDelegate;` — Delegate that runs a test by name, this is overridable by tests so that it's possible to test RunTests() since tests can't recursively call FAutomationTestFramework::StartTestByName().
- L198 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii OnExitDelegateHandle;`
- L228 _public prototype_ `static UPythonTestRunner* Create( const FString& BaseName, const FPythonTestRunnerSearchOptions& SearchOptions, float TimeoutInSeconds = 5.0f);` — `UFUNCTION(BlueprintCallable, Category="PythonTestRunner")`

#### Free symbols / members of external scopes

- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ReferenceConverter.h` (Private)


#### struct `FToolsetReference`  
`struct FToolsetReference`  
_L11-18_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a reference to a UObject or UClass.
- L17 _public member_ `FString RefPath;` — `UPROPERTY(BlueprintReadWrite, Category = "Toolset")` — The reference stored as a soft path string.

#### class `UE::ToolsetRegistry::FToolsetReferenceConverter`  
`class FToolsetReferenceConverter : public FToolsetJsonConverter`  
_L23-42_
- inherits: `FToolsetJsonConverter`
- desc: Converts UObject and UClass references.
- L26 _public prototype_ `virtual FString GetName() const override;`
- L28 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L30 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema( TNotNull<const FProperty*> Property) override;`
- L33 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault( TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L36 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData( TNotNull<FProperty*> Property, const void* Value) override;`
- L39 _public prototype_ `virtual bool JsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/RunOnMainThread.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L16 _function_ `template<typename CallableT> inline auto RunOnMainThread(CallableT&& Callable) -> TFuture<decltype(Forward<CallableT>(Callable)())>` (scope `UE::ToolsetRegistry::Internal`) — Run a function on the main thread as soon as possible.
- L21 _typedef_ `using ReturnT = decltype(Forward<CallableT>(Callable)());` (scope `UE::ToolsetRegistry::Internal::RunOnMainThread`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ToolCallExceptionHandlerInternal.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L16 _externvar_ `HandledBlueprintExceptionTypeToErrorStrings;` (scope `UE::ToolsetRegistry::Internal`)
- L18 _externvar_ `extern const TSet<EBlueprintExceptionType::Type> IgnoredBlueprintExceptionTypes;` (scope `UE::ToolsetRegistry::Internal`) — Set of FToolCallExceptionHandler ignored blueprint exception types to error strings.
- L21 _prototype_ `void CallWithinBlueprintScript(TFunction<void()>&& Func);` (scope `UE::ToolsetRegistry::Internal`) — Call a function within the scope of a blueprint script.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ToolCallExceptionHandlerTestScope.h` (Private)


#### class `UToolCallExceptionHandlerTestScope`  
`class UToolCallExceptionHandlerTestScope : public UObject`  
_L17-32_
- reflection: `UCLASS(BlueprintType, HideDropdown)`
- inherits: `UObject`
- desc: Simplifies testing Blueprint toolsets that raise errors caught by FToolCallExceptionHandler. NOTE: This is tested by ToolCallExceptionHandlerTest.cpp.
- L23 _public prototype_ `void CallFunction(TFunction<void()>&& Func);` — Call the specified function within a blueprint execution context.
- L28 _protected prototype_ `void CallFunctionInternal();` — `UFUNCTION()` — Calls FunctionToCall if set.
- L31 _private member_ `TFunction<void()> FunctionToCall;`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ToolsetJson.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L16 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L16 _namespace_ `namespace ToolsetJson` (scope `UE::ToolsetRegistry::Internal`)
- L23 _prototype_ `TSharedPtr<FJsonObject> PropertyToJsonSchema(TNotNull<const FProperty*> Property);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Converts an FProperty to JSON schema. @param Property The FProperty to convert. @return JSON schema that represents the FProperty.
- L30 _prototype_ `TSharedPtr<FJsonValue> PropertyToJsonData( TNotNull<FProperty*> Property, TNotNull<const void*> Value);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Gets an FProperty on an instance to JSON data. @param Property The FProperty to convert. @param Value The object or struct to get the value from. @return JSON data that represents the value of the FProperty.
- L39 _prototype_ `bool JsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, TNotNull<void*> OutValue, UObject* Outer = nullptr);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Set an FProperty on an instance from JSON data. @param JsonValue The JSON data to convert. @param Property The FProperty to apply the data to. @param OutValue The object or struct to modify. @return True if the data was converted successfully.
- L45 _prototype_ `bool HasCustomImporter(TNotNull<const FProperty*> Property);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Returns true if the ToolsetJson converter registry would handle this property, meaning callers must not bypass it by recursing field-by-field.
- L53 _prototype_ `TSharedPtr<FJsonObject> StructToJsonSchema( TNotNull<const UStruct*> StructDefinition, bool UserVisiblePropertiesOnly = false);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Converts a UStruct to JSON schema. @param StructDefinition The UStruct type to convert. @param UserVisiblePropertiesOnly Whether to export all properties or only the ones that appear in editor. @return JSON schema that represents the UStruct.
- L62 _prototype_ `TSharedPtr<FJsonObject> StructToJsonData( TNotNull<const UStruct*> StructDefinition, TNotNull<const void*> Struct, bool UserVisiblePropertiesOnly = false);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Converts a UStruct instance to JSON data. @param StructDefinition The UStruct type to convert. @param Struct The UStruct instance to convert. @param UserVisiblePropertiesOnly Whether to export all properties or only the ones that appear in editor. @return JSON data that represents the UStruct instance.
- L72 _prototype_ `bool JsonDataToStruct( const TSharedRef<FJsonObject>& JsonObject, TNotNull<const UStruct*> StructDefinition, TNotNull<void*> OutStruct);` (scope `UE::ToolsetRegistry::Internal::ToolsetJson`) — Updates a UStruct instance from JSON data. @param JsonObject The JSON data to convert. @param StructDefinition The UStruct type. @param OutStruct The UStruct instance to modify. @return True if the data was applied successfully.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ToolsetLibraryImpl.h` (Private)


#### struct `UE::ToolsetRegistry::Internal::FPropertyImportContext`  
`struct FPropertyImportContext`  
_L19-50_
- desc: Accumulated context passed down through recursive property import calls. Each recursive frame receives its own copy so inner frames can extend the chain and element-index map without affecting sibling calls.
- L22 _public member_ `TArray<FProperty*> Chain;` — Property chain, outermost-to-innermost. Chain[0] is always a direct UObject member.
- L31 _public member_ `TMap<FString, int32> ElementIndices;` — Element indices accumulated as we descend into containers. Keyed by container property name; used to populate FPropertyAccessChangeNotify::ElementIndicesMap for the change notification framework. NOTE: this is a name-keyed flat map, so if the same property name appears at two different chain depths the inner overwrites the outer. That is acceptable for notifications (consumers only care about the leaf element). Path construction for error reporting uses PropertyPath instead, which is collision-free.
- L39 _public member_ `FString PropertyPath;` — Pre-built dotted path of every Chain.Add() and container descent taken so far, e.g. "StructProp.Items[3].Tag" or "Mappings[KeyName]". Each push into Chain appends ".Name"; each descent into a container element appends "[Index]" (arrays/sets) or "[KeyString]" (maps). Read by the unmatched-key emission to produce paths that survive name collisions across chain depths and that distinguish map keys from iteration indices.
- L40 _public member_ `UObject* Object = nullptr;`
- L42 _public member_ `bool bBypassContainerChecking = false;` — When true, ImportPropertyWithNotify skips container-diff logic and always emits ValueSet.
- L49 _public member_ `TArray<FString>* OutUnmatchedKeys = nullptr;` — If non-null, ImportStructFieldsWithNotify appends dotted property paths here for any JSON key that didn't resolve to an FProperty on the nested struct. The top-level caller uses this to surface nested misspellings (e.g. "ShakeData.shake_class" instead of "ShakeClass") in the same error path as top-level unknown keys, rather than silently dropping them.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L63 _prototype_ `bool ImportPropertyWithNotify( const TSharedPtr<FJsonValue>& NewJson, FProperty* Property, void* PropertyMemory, FPropertyImportContext Ctx);` (scope `UE::ToolsetRegistry::Internal`) — Imports NewJson into the property at PropertyMemory, emitting the correct Pre/Post change notifications (ArrayAdd/ArrayRemove/ArrayClear/ValueSet) based on the detected change type. Recurses into structs and same-size containers to find nested container changes. FObjectProperty and special struct types (FInstancedStruct, IJsonObjectStructConverter implementors) fall through to ValueSet. TODO: Update JsonObjectConverter to track property and subobject chains and pass this information to its ImportCb. We can then move this logic to the JsonObjectConverter and our ImportCb overrides, making it more tractable to handle notifies within FObjectProperty, for example (UE-379502)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/TransformConverter.h` (Private)


#### struct `FToolsetTransform`  
`struct FToolsetTransform`  
_L13-28_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- desc: Represents a 3D transformation with optional location, rotation, and scale. Unset fields mean "identity" when creating objects and "don't change" when modifying existing ones.
- L19 _public member_ `TOptional<FVector> Location;` — `UPROPERTY(BlueprintReadWrite, Category = "Transform")` — The world-space location.
- L23 _public member_ `TOptional<FRotator> Rotation;` — `UPROPERTY(BlueprintReadWrite, Category = "Transform")` — The world-space rotation.
- L27 _public member_ `TOptional<FVector> Scale;` — `UPROPERTY(BlueprintReadWrite, Category = "Transform")` — The scale.

#### class `UE::ToolsetRegistry::FToolsetTransformConverter`  
`class FToolsetTransformConverter : public FToolsetJsonConverter`  
_L34-62_
- inherits: `FToolsetJsonConverter`
- desc: Converts FTransform properties to/from JSON using optional translation, rotation, and scale fields, matching the semantics of the Python Transform struct's to_ue / from_ue methods.
- L37 _public prototype_ `virtual FString GetName() const override;`
- L39 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L41 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema( TNotNull<const FProperty*> Property) override;`
- L44 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault( TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L47 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData( TNotNull<FProperty*> Property, const void* Value) override;`
- L50 _public prototype_ `virtual bool JsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`
- L57 _private prototype_ `static FTransform ToUE(const FToolsetTransform& Transform, const FTransform& Base = FTransform::Identity);` — Equivalent to Python's to_ue: applies set fields on top of Base, leaves unset fields at their Base values.
- L61 _private prototype_ `static FToolsetTransform FromUE(const FTransform& Transform);` — Equivalent to Python's from_ue: always populates all three fields from the transform.

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Private/ToolsetRegistry/ValueOrErrorFuture.h` (Private)


#### class `UE::ToolsetRegistry::Internal::TValueOrErrorFutureBase`  
`template<typename ValueT, typename ValueOrErrorT> class TValueOrErrorFutureBase`  
_L17-38_
- desc: Reduces the boilerplate required to construct a completed future with a value or error
- L20 _public typedef_ `using FValueOrError = ValueOrErrorT;`
- L21 _public typedef_ `using FFuture = TFuture<FValueOrError>;`
- L24 _public function_ `static FFuture Make(FValueOrError&& ValueOrError)`
- L29 _public function_ `static FFuture MakeValue(ValueT&& Value)`
- L34 _public function_ `static FFuture MakeError(FString&& Error)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::ToolsetRegistry`)
- L41 _typedef_ `template<typename ValueT> using TValueOrErrorFuture = TValueOrErrorFutureBase<ValueT, TValueOrError<ValueT, FString>>;` (scope `UE::ToolsetRegistry::Internal`)
- L43 _typedef_ `using FStringValueOrErrorFuture = TValueOrErrorFuture<FString>;` (scope `UE::ToolsetRegistry::Internal`)
- L45 _typedef_ `using FJsonValueOrErrorFuture = TValueOrErrorFutureBase<TSharedPtr<FJsonValue>, FJsonValueOrError>;` (scope `UE::ToolsetRegistry::Internal`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/AgentSkill.h` (Public)


#### struct `FAgentSkillDetails`  
`struct FAgentSkillDetails`  
_L18-26_
- reflection: `USTRUCT(BlueprintType)`
- desc: Detailed information about a specific AgentSkill.
- L25 _public member_ `FString Instructions;` — `UPROPERTY(BlueprintReadWrite, Category = "AgentSkill")` — Detailed information about how to use the skill.

#### class `UAgentSkill`  
`class UAgentSkill : public UObject`  
_L29-56_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L36 _public member_ `FString Description;` — `UPROPERTY(EditDefaultsOnly, Category="AgentSkill", meta=(MultiLine=true))` — A brief description of what the skill does or how it should be used.
- L39 _public prototype_ `FAgentSkillDetails GetDetails() const;` — Returns detailed information about how to use this skill.
- L44 _protected prototype_ `FString GeneratePrompt(const FString& InitialInstructions) const;` — `UFUNCTION(BlueprintNativeEvent, Category="AgentSkill")` — Generates the final prompt text for the Agent Skill.
- L45 _protected function_ `virtual FString GeneratePrompt_Implementation(const FString& InitialInstructions) const`
- L52 _protected member_ `FString Instructions;` — `UPROPERTY(EditDefaultsOnly, Category = "AgentSkill", meta = (MultiLine = true))` — Detailed instructions for how to use this skill and its associated tools.

#### class `UAgentSkillToolset`  
`class UAgentSkillToolset : public UToolsetDefinition`  
_L60-104_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for listing, reading, and creating/updating skills.
- L70 _public prototype_ `static TMap<FString, FString> ListSkills();` — `UFUNCTION(meta = (AICallable), Category="Agent Skill")` — Gets a summary of all AgentSkills in the project. @return A dictionary where the key is the Skill path and the value is a description.
- L78 _public prototype_ `static TMap<FString, FAgentSkillDetails> GetSkills(const TArray<FString>& SkillPaths);` — `UFUNCTION(meta = (AICallable), Category = "Agent Skill")` — Returns detailed information about a specific set of AgentSkills. @param SkillPaths A list of paths to the AgentSkills to retrieve. @return A dictionary where the key is the Skill path and the value is detailed info.
- L90 _public prototype_ `static FString CreateSkill( const FString& FolderPath, const FString& AssetName, const FString& Description, const FAgentSkillDetails& Details);` — `UFUNCTION(meta = (AICallable), Category = "Agent Skill")` — Creates a new AgentSkill. This should ONLY be called after getting explicit direction or permission from the user. @param FolderPath The folder in which to create the skill. i.e. /Game/Skills/. @param AssetName The name of the skill to create i.e. MySkill. @param Description The brief description of the skill. @param Details Detailed information about how to use the skill. @return The path for the created Skill class. Empty if unsuccessful.
- L102 _public prototype_ `static bool UpdateSkill( const FString& SkillPath, const FString& Description, const FAgentSkillDetails& Details);` — `UFUNCTION(meta = (AICallable), Category = "Agent Skill")` — Updates an existing AgentSkill. This should ONLY be called after getting explicit direction or permission from the user. @param SkillPath The full path to the skill to modify i.e. /Game/Skills/MySkill.MySkill_C. @param Description The brief description of the skill. @param Details Detailed information about how to use the skill. @return True if the skill was updated.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/DelegateHandle.h` (Public)


#### class `UE::ToolsetRegistry::FDelegateHandleRaiiBase`  
`class FDelegateHandleRaiiBase`  
_L11-30_
- desc: Delegate handle RAII container.
- L14 _public function_ `virtual ~FDelegateHandleRaiiBase()`
- L16 _public prototype_ `FDelegateHandleRaiiBase(const FDelegateHandleRaiiBase&) = delete;`
- L17 _public prototype_ `FDelegateHandleRaiiBase& operator=(const FDelegateHandleRaiiBase&) = delete;`
- L20 _public function_ `virtual void Reset()` — Reset the handle.
- L23 _public function_ `const FDelegateHandle& Get() const` — Get the underlying delegate handle.
- L26 _protected function_ `FDelegateHandleRaiiBase(FDelegateHandle&& Handle) : DelegateHandle(MoveTemp(Handle))`
- L29 _private member_ `FDelegateHandle DelegateHandle;`

#### class `UE::ToolsetRegistry::TDelegateHandleRaii`  
`template<typename DelegateRegistrationT> class TDelegateHandleRaii : public FDelegateHandleRaiiBase`  
_L34-60_
- inherits: `FDelegateHandleRaiiBase`
- desc: RAII container for a delegate handle.
- L38 _public function_ `TDelegateHandleRaii(DelegateRegistrationT& Registration, FDelegateHandle&& Handle) : FDelegateHandleRaiiBase(MoveTemp(Handle)), DelegateRegistration(Registration)` — Move the delegate handle for a registration into a container.
- L45 _public function_ `virtual ~TDelegateHandleRaii()` — On destruction, unregister the handle from the delegate registration.
- L48 _public function_ `virtual void Reset() override` — Unregister the handle from the delegate registration.
- L59 _private member_ `DelegateRegistrationT& DelegateRegistration;`

#### class `UE::ToolsetRegistry::FDelegateHandleRaii`  
`class FDelegateHandleRaii : public TUniquePtr<FDelegateHandleRaiiBase>`  
_L62-87_
- inherits: `TUniquePtr<FDelegateHandleRaiiBase>`
- L68 _public function_ `bool IsValid() const` — Whether this references a valid handle.
- L81 _public function_ `template<typename DelegateRegistrationT> static FDelegateHandleRaii Create( DelegateRegistrationT& Registration, FDelegateHandle&& Handle)` — Create an instance of a delegate handle RAII container. For example: auto HandleRaii = FDelegateHandleRaii::Create( OnSomeMulticastDelegate, OnSomeMulticastDelegate.AddLambda([]() -> void {   do something   }));

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/JsonValueOrError.h` (Public)


#### struct `UE::ToolsetRegistry::FJsonValueOrErrorSchemaDescriptor`  
`struct FJsonValueOrErrorSchemaDescriptor`  
_L19-31_
- desc: Schema descriptor for a JSON value or error.
- L22 _public member_ `const FString ObjectDescription;` — Top level description for a value or error object.
- L24 _public member_ `const FString ValueFieldName;` — Value field name in an object of this type.
- L26 _public member_ `const FString NullValueFieldDescription;` — Description of the value field if it can only be null.
- L28 _public member_ `const FString ErrorFieldName;` — Error field name in an object of this type.
- L30 _public member_ `const FString ErrorFieldDescription;` — Description of the error field.

#### class `UE::ToolsetRegistry::FJsonValueOrError`  
`class FJsonValueOrError : public FJsonValueOrErrorBase`  
_L39-84_
- inherits: `FJsonValueOrErrorBase`
- desc: ```typescript { "returnValue"?: unknown, "error"?: string } ```
- L49 _public prototype_ `TSharedRef<FJsonObject> ToJsonObject( const FJsonValueOrErrorSchemaDescriptor& Descriptor = DefaultDescriptor) const;` — @returns JSON object that contains the value or error.
- L57 _public prototype_ `FString ToJsonString( const FJsonValueOrErrorSchemaDescriptor& Descriptor = DefaultDescriptor) const;` — @returns JSON string that contains the value or error.
- L62 _public member_ `static const FJsonValueOrErrorSchemaDescriptor DefaultDescriptor;` — Default descriptor for a FJsonValueOrError.
- L71 _public prototype_ `static TSharedRef<FJsonObject> GetJsonSchema( TSharedPtr<FJsonObject> ValueSchema, const FJsonValueOrErrorSchemaDescriptor& Descriptor = DefaultDescriptor);` — @returns JSON schema for a FJsonValueOrError that has ValueSchema as the value type.
- L82 _public prototype_ `static FJsonValueOrError FromJsonStringOrError( const TValueOrError<FString, FString>& JsonStringOrError);` — @returns Instance of FJsonValueOrError that contains either the JSON value or error from JsonStringOrError.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L16 _typedef_ `using FJsonValueOrErrorBase = TValueOrError<TSharedPtr<FJsonValue>, FString>;` (scope `UE::ToolsetRegistry`) — Base class for FValueOrError.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/SandboxLibrary.h` (Public)


#### class `UE::ToolsetRegistry::FGlobalSandbox`  
`class FGlobalSandbox`  
_L13-74_
- desc: Provides static access to the globally active FileSandbox instance.
- L17 _public prototype_ `static bool IsActive();` — Returns whether a sandbox is currently active.
- L20 _public prototype_ `static FString GetActiveName();` — Returns the name of the active sandbox, or an empty string if none is active.
- L32 _public prototype_ `static bool Enter(const FString& Name, const FString& Description);` — Creates a new sandbox or resumes an existing one by name. If a different sandbox is already active, it is left before entering the new one. @param Name        The name of the sandbox to enter or create. @param Description Used only when creating a new sandbox; ignored if a sandbox with the given name already exists. @return True if the named sandbox is now active; false if leaving the current sandbox or entering the requested sandbox failed.
- L39 _public prototype_ `static bool Leave();` — Leaves the active sandbox without deleting it. The sandbox's files are preserved. @return True if no sandbox is active after the call.
- L45 _public prototype_ `static TArray<UE::FileSandboxCore::FSandboxedFileChangeInfo> GetChanges();` — Returns the list of files changed in the active sandbox. Returns an empty array if no sandbox is active.
- L53 _public prototype_ `static bool Persist(const TArray<FString>& Files);` — Persists sandbox changes to the real filesystem. @param Files Files to persist. If empty, all changes are persisted. @return True on success.
- L61 _public prototype_ `static bool Discard();` — Discards all changes in the active sandbox. The sandbox remains active after the call; call Leave() to exit it. @return True on success.
- L73 _public prototype_ `static bool DiscardFiles(const TArray<FString>& Files);` — Discards only the specified files in the active sandbox. To discard all changes, call Discard() instead. @param Files The files to discard. Must be non-empty; passing an empty list is treated as a caller error and returns false to avoid silently discarding all sandbox changes. @return True if the files were reverted; false if no sandbox is active or Files is empty.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolCallAsyncResult.h` (Public)


#### class `UToolCallAsyncResult`  
`class UToolCallAsyncResult : public UObject`  
_L42-156_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L53 _public member_ `bool bIsComplete = false;` — `UPROPERTY(BlueprintReadOnly, Category = "ToolsetRegistry")` — @warning Do *not* set this from C++ instead use SetError() or SetValue() if implemented by the subclass.
- L57 _public member_ `FToolCallAsyncResultCompleted OnCompleted;` — `UPROPERTY(BlueprintAssignable, Category = "ToolsetRegistry")` — Notified when the tool call is completes successfully or with an error.
- L66 _public member_ `FString Error;` — `UPROPERTY(BlueprintReadOnly, Category = "ToolsetRegistry")` — @warning Do *not* set this from C++ instead use SetError() or SetValue() if implemented by the subclass.
- L71 _public prototype_ `FString GetValueAsJsonString() const;` — `UFUNCTION(BlueprintCallable, Category = "ToolsetRegistry")` — Get the JSON representation of the Value. If the associated tool call is not complete or an error occurred, this returns an empty string.
- L75 _public prototype_ `virtual TSharedPtr<FJsonValue> GetValueAsJson() const;` — Get the JSON representation of the Value. If the associated tool call is not complete or an error occurred, this returns an empty (null) shared pointer.
- L84 _public prototype_ `bool SetError(const FString& InError);` — `UFUNCTION(BlueprintCallable, Category = "ToolsetRegistry")` — @note This is thread safe, the Error property will always be updated and OnCompleted will be signaled on the main thread.
- L98 _public prototype_ `bool BroadcastOnCompletedIfComplete();` — `UFUNCTION(BlueprintCallable, Category = "ToolsetRegistry")` — @remark Ideally we would override subscription methods for the OnCompleted delegate and notify subscribers there but unfortunately that isn't possible.
- L108 _protected prototype_ `bool MaybeBroadcastCompletion(TFunction<void()>&& SetFinalState);` — @note To make this thread safe, if this isn't called on the main thread, SetFinalState will not be called until the next main thread update so be careful that SetFinalState does not reference any data on the stack.
- L116 _protected function_ `template<typename ValueT> bool MaybeBroadcastSuccessfulCompletion(ValueT&& InValue, ValueT& ValueToSet)` — @note: InValue must be movable, as ValueToSet must be set on the main thread.
- L128 _protected function_ `bool MaybeBroadcastSuccessfulCompletion()` — @returns true if the broadcast was executed or scheduled, false otherwise.
- L135 _private prototype_ `void SetIsComplete();` — Thread safe access of bIsComplete.
- L136 _private prototype_ `bool GetIsComplete() const;`
- L139 _private prototype_ `void BroadcastOnCompleted();` — Broadcast OnCompleted and clear all listeners from the delegate.
- L143 _private member_ `mutable UE::FMutex CompletedLock;` — Guards: bIsComplete.
- L147 _public prototype_ `static TSharedRef<FJsonObject> GetValueJsonSchema(TSubclassOf<UToolCallAsyncResult> Class);` — Get the JSON schema for an async result class' value.
- L152 _public prototype_ `static UClass* MatchesProperty(TNotNull<const FProperty*> Property);` — Check whether a property references an async result class. Returns the async result UClass if the property is an FObjectProperty whose class derives from UToolCallAsyncResult, nullptr otherwise.
- L155 _private member_ `static FString ValuePropertyName;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToolCallAsyncResultCompleted, UToolCallAsyncResult*, Result);` — Notified when an async tool call completes successfully or with an error.
- L24 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToolCallAsyncResultCompleted, UToolCallAsyncResult*, Result);` — Notified when an async tool call completes successfully or with an error.
- L120 _function_ `` (scope `UToolCallAsyncResult::MaybeBroadcastSuccessfulCompletion`)
- L130 _function_ `return MaybeBroadcastCompletion([]() -> void {});` (scope `UToolCallAsyncResult::MaybeBroadcastSuccessfulCompletion`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolCallAsyncResultFutureHandler.h` (Public)


#### class `UToolCallAsyncResultFutureHandler`  
`class UToolCallAsyncResultFutureHandler : public UObject`  
_L24-63_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, HideDropdown)`
- inherits: `UObject`
- desc: Handles UToolCallAsyncResult::OnCompleted by completing the associated future. NOTE: This is tested by ToolCallAsyncResultTest.cpp.
- L33 _public prototype_ `TFuture<UE::ToolsetRegistry::FJsonValueOrError> GetValueAsJson();` — Resolves with the JSON result of UToolCallAsyncResult object passed to Create(). NOTE: The future can only be retrieved once.
- L36 _public prototype_ `void Unsubscribe();` — Unsubscribe from the result and cancel the pending future returned from GetValueAsJson().
- L41 _private prototype_ `void OnCompleted(UToolCallAsyncResult* Result);` — `UFUNCTION()` — Handles a result completion.
- L44 _private prototype_ `void Subscribe(UToolCallAsyncResult* Result);` — Subscribes to result completion.
- L47 _private prototype_ `void Unsubscribe(bool bIsDestructing);` — Unsubscribe, optionally without touching the Result as it may already be garbage collected.
- L50 _private member_ `TObjectPtr<UToolCallAsyncResult> Result;`
- L51 _private member_ `TPromise<UE::ToolsetRegistry::FJsonValueOrError> ResultPromise;`
- L52 _private member_ `bool bOnCompletedHandled = false;`
- L53 _private member_ `bool bRetrievedFuture = false;`
- L58 _public prototype_ `static TStrongObjectPtr<UToolCallAsyncResultFutureHandler> Create( TObjectPtr<UToolCallAsyncResult> Result);` — Create a handler and bind the OnCompleted method to the specified result instance's OnCompleted delegate.
- L62 _public member_ `static const FString CanceledError;` — Error that indicates the future was canceled.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolCallAsyncResultImage.h` (Public)


#### class `UToolCallAsyncResultImage`  
`class UToolCallAsyncResultImage : public UToolCallAsyncResult`  
_L12-27_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolCallAsyncResult`
- desc: Async tool call result that completes with a ToolsetImage.
- L19 _public function_ `bool SetValue(const FToolsetImage& InValue)` — `UFUNCTION(BlueprintCallable, Category = "ToolsetRegistry")` — Set the result.
- L26 _public member_ `FToolsetImage Value;` — `UPROPERTY(BlueprintReadOnly, Category = "ToolsetRegistry")` — Value of the result.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolCallAsyncResultString.h` (Public)


#### class `UToolCallAsyncResultString`  
`class UToolCallAsyncResultString : public UToolCallAsyncResult`  
_L13-28_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolCallAsyncResult`
- desc: Async tool call result that completes with a string.
- L20 _public function_ `bool SetValue(const FString& InValue)` — `UFUNCTION(BlueprintCallable, Category = "ToolsetRegistry")` — Set the result.
- L27 _public member_ `FString Value;` — `UPROPERTY(BlueprintReadOnly, Category = "ToolsetRegistry")` — Value of the result.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolCallAsyncResultVoid.h` (Public)


#### class `UToolCallAsyncResultVoid`  
`class UToolCallAsyncResultVoid : public UToolCallAsyncResult`  
_L18-35_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolCallAsyncResult`
- desc: Async tool call result that completes with no value.
- L25 _public function_ `bool SetCompleted()` — `UFUNCTION(BlueprintCallable, Category = "ToolsetRegistry")` — Complete this result with no value and notify listeners of OnCompleted.
- L30 _public prototype_ `virtual TSharedPtr<FJsonValue> GetValueAsJson() const override;`
- L34 _public prototype_ `static TSharedRef<FJsonObject> GetValueJsonSchema();` — Get the JSON schema for this class's value.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolCallExceptionHandler.h` (Public)


#### class `UE::ToolsetRegistry::FToolCallExceptionHandler`  
`class FToolCallExceptionHandler`  
_L18-80_
- desc: Register for tracking of tool call exceptions for the lifetime of this object.
- L21 _public prototype_ `FToolCallExceptionHandler();`
- L22 _public prototype_ `~FToolCallExceptionHandler() = default;`
- L25 _public prototype_ `FToolCallExceptionHandler(const FToolCallExceptionHandler&) = delete;` — Disallow copy and move.
- L26 _public prototype_ `FToolCallExceptionHandler& operator=(const FToolCallExceptionHandler&) = delete;`
- L27 _public prototype_ `FToolCallExceptionHandler(FToolCallExceptionHandler&&) = delete;`
- L28 _public prototype_ `FToolCallExceptionHandler& operator=(FToolCallExceptionHandler&&) = delete;`
- L33 _public function_ `FString GetException() const` — Description of script exceptions raised by UKismetSystemLibrary::RaiseScriptError or FBlueprintCoreDelegates::ThrowScriptException via FBlueprintCoreDelegates::OnScriptException during the lifetime of this object.
- L57 _public prototype_ `void CaptureErrorsIn(TFunction<void()>&& Func);`
- L63 _private prototype_ `void OnScriptException( const UObject* ActiveObject, const FFrame& StackFrame, const FBlueprintExceptionInfo& Info);` — Track script exceptions raised by UKismetSystemLibrary::RaiseScriptError or FBlueprintCoreDelegates::ThrowScriptException via FBlueprintCoreDelegates::OnScriptException and copy into local storage.
- L67 _private prototype_ `FString GetBackupExceptionMessage(const FString& ExceptionTypeName, const FFrame& StackFrame);` — Build an exception message for the stack frame with the specified ExceptionTypeName.
- L70 _private prototype_ `TOptional<FString> GetBlueprintExceptionMessage( const FBlueprintExceptionInfo& Info, const FFrame& StackFrame);` — Try to build an exception message from exception info and stack frame.
- L74 _private prototype_ `void AddToExceptionMessage(const FString& NewMessage);` — Append an message to the current exception message.
- L77 _private member_ `FDelegateHandleRaii ScriptExceptionHandle;` — Handler for FBlueprintCoreDelegates::OnScriptException
- L79 _private member_ `FString ScriptException;` — Raised script exception message.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/Toolset.h` (Public)


#### class `UE::ToolsetRegistry::FToolset`  
`class FToolset`  
_L16-85_
- desc: Base class for toolsets.
- L19 _public prototype_ `FToolset();`
- L20 _public prototype_ `virtual ~FToolset();`
- L28 _public prototype_ `TFuture<TValueOrError<FString, FString>> ExecuteTool( const FString& ToolName, const FString& JsonInput);` — @returns A future with the JSON output or an error string if it failed.
- L33 _public prototype_ `FString GetJsonSchema() const;` — Get the JSON schema the enabled tools in this toolset. Returns an empty string if the toolset is disabled or has no enabled tools.
- L36 _public prototype_ `virtual FString GetToolsetName() const = 0;` — Returns the name of the toolset
- L39 _public prototype_ `virtual FString GetToolsetVersion() const = 0;` — Returns the version of the toolset
- L42 _public prototype_ `virtual FString GetToolsetDescription() const = 0;` — Returns a description of what this toolset does and when it should be used.
- L45 _public function_ `virtual UClass* GetToolsetClass() const` — Returns the UClass that implements this toolset, if any.
- L48 _public prototype_ `bool IsEnabled() const;` — Returns true if the toolset is enabled.
- L51 _public prototype_ `void SetEnabled(bool bInEnabled);` — Enable or disable the toolset.
- L59 _public prototype_ `void SetNameFilters( const TArray<FString>& BlockPatterns, const TArray<FString>& AllowPatterns);` — Set the block and allow filter patterns. Patterns enclosed in forward slashes (e.g., /^Fake. ) are treated as regular expressions. All other patterns are matched as case-insensitive substrings. Block always takes precedence over the allow-list. Patterns that match the toolset name control whether the toolset itself is enabled. Patterns that don't match the toolset name are applied as per-tool filters. Passing empty arrays for both clears all filters.
- L64 _public prototype_ `bool IsToolEnabled(const FString& FullToolName) const;` — Returns true if the given tool passes the per-tool block/allow filters. Tool name should be the fully-qualified tool name (e.g., "ToolsetName.ToolName").
- L68 _public prototype_ `TArray<FString> ListToolNames() const;` — Returns the full names of all tools in this toolset, ignoring per-tool filters and the enabled state of the toolset.
- L72 _protected prototype_ `virtual TFuture<TValueOrError<FString, FString>> ExecuteToolInternal( const FString& ToolName, const FString& JsonInput) = 0;` — Executes a tool by name. Called by ExecuteTool() after enable checks pass.
- L76 _protected prototype_ `virtual FString GetJsonSchemaInternal() const = 0;` — Get the JSON schema for all tools in the toolset.
- L80 _private member_ `bool bEnabled = true;` — Whether this toolset has been explicitly enabled or disabled via SetEnabled().
- L84 _private member_ `TSet<FString> DisabledTools;` — Full names of disabled tools. Populated eagerly by SetNameFilters. An empty set means all tools are enabled (no filters active).

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetDefinition.h` (Public)


#### class `UToolsetDefinition`  
`class UToolsetDefinition : public UObject`  
_L18-33_
- reflection: `UCLASS(BlueprintType, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: This is the common base class for Toolsets defined as UObjects. UFunctions that define tools in this class should be static functions and be marked with meta = (AICallable). This is used both by UHT and the runtime UToolRegistry. UFunctions which should be ignored by tools should be marked with meta = (AIIgnore) in order to silence errors about invalid UFunctions
- L25 _public function_ `virtual FString GetToolsetVersion() const` — Note that this virtual method is currently called on the class default object.
- L32 _public prototype_ `static TValueOrError<bool, FString> IsFunctionAICallable(const TObjectPtr<const UFunction>& Function);` — Returns an Error if the function cannot be added to the tool and lacks the AIIgnore metadata. Otherwise, returns a Value of whether or not the function can be added to the tool.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetImage.h` (Public)


#### struct `FToolsetImage`  
`struct FToolsetImage`  
_L14-33_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- desc: The standard image format that toolsets should return.
- L20 _public member_ `FString MimeType;` — `UPROPERTY(BlueprintReadOnly, Category = "Image")` — The format the image is encoded in.
- L24 _public member_ `FString Data;` — `UPROPERTY(BlueprintReadOnly, Category = "Image")` — The image data encoded as a base64 string.
- L28 _public prototype_ `bool SetFromBitmap(const TArray<FColor>& Bitmap, FIntPoint Dimensions, ERGBFormat Format = ERGBFormat::BGRA);` — Populates the ToolsetImage based on a raw color image. Format controls the channel layout of Bitmap in memory (default BGRA matches FColor on LE).
- L32 _public prototype_ `bool SetFromFile(const FString& Path);` — Populates the ToolsetImage from a file saved on disk.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetJsonConverter.h` (Public)


#### class `UE::ToolsetRegistry::FToolsetJsonConverter`  
`class FToolsetJsonConverter`  
_L17-94_
- desc: Base class for custom conversion between FProperty and JSON.
- L20 _public prototype_ `FToolsetJsonConverter();`
- L21 _public prototype_ `virtual ~FToolsetJsonConverter();`
- L24 _public prototype_ `virtual FString GetName() const = 0;` — Returns the name of the converter
- L27 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) = 0;` — Determines whether a given property type can be handled by this converter.
- L34 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema( TNotNull<const FProperty*> Property) = 0;` — Converts an FProperty to JSON schema. @param Property The FProperty to convert. @return JSON schema that represents the FProperty.
- L43 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault( TNotNull<const FProperty*> Property, const FString& DefaultString) = 0;` — Generates a default object from the FProperty. @param Property The FProperty to convert. @param DefaultString The default value of the property as a string. @return JSON data that represents the FProperty.
- L52 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData( TNotNull<FProperty*> Property, const void* Value) = 0;` — Gets an FProperty on an instance to JSON data. @param Property The FProperty to convert. @param Value The object or struct to get the value from. @return JSON data that represents the value of the FProperty.
- L63 _public prototype_ `virtual bool JsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) = 0;` — Set an FProperty on an instance from JSON data. @param JsonValue The JSON data to convert. @param Property The FProperty to apply the data to. @param OutValue The object or struct to modify. @param Outer The UObject that owns the property being set. @return True if the data was converted successfully.
- L69 _protected prototype_ `static TSharedPtr<FJsonObject> ToolsetPropertyToJsonSchema( TNotNull<const FProperty*> Property);` — Converts a property to JSON schema via the full ToolsetJson pipeline.
- L73 _protected prototype_ `static TSharedPtr<FJsonValue> ToolsetPropertyToJsonData( TNotNull<FProperty*> Property, TNotNull<const void*> Value);` — Converts a property value to JSON data via the full ToolsetJson pipeline.
- L77 _protected prototype_ `static bool ToolsetJsonDataToProperty( const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, TNotNull<void*> OutValue);` — Sets a property on an instance from JSON data via the full ToolsetJson pipeline.
- L82 _protected prototype_ `static TSharedPtr<FJsonObject> ToolsetStructToJsonSchema( TNotNull<const UStruct*> StructDefinition, bool UserVisiblePropertiesOnly = false);` — Converts a UStruct to JSON schema via the full ToolsetJson pipeline.
- L86 _protected prototype_ `static TSharedPtr<FJsonObject> ToolsetStructToJsonData( TNotNull<const UStruct*> StructDefinition, TNotNull<const void*> Struct, bool UserVisiblePropertiesOnly = false);` — Converts a UStruct instance to JSON data via the full ToolsetJson pipeline.
- L91 _protected prototype_ `static bool ToolsetJsonDataToStruct( const TSharedRef<FJsonObject>& JsonObject, TNotNull<const UStruct*> StructDefinition, TNotNull<void*> OutStruct);` — Updates a UStruct instance from JSON data via the full ToolsetJson pipeline.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetLibrary.h` (Public)


#### enum `EBypassContainerCheck`  
`enum class EBypassContainerCheck : uint8`  
_L17-25_
- reflection: `UENUM(BlueprintType)`
- desc: Selects whether SetObjectProperties performs container diff-and-recurse logic or emits a single ValueSet for the whole property. Named (rather than bool) so call sites read clearly at the point of use.
- L21 _public enumerator_ `No` — Default. Compare incoming JSON against the live container and emit precise ArrayAdd / ArrayRemove / ArrayClear / ValueSet notifications with element indices.
- L24 _public enumerator_ `Yes` — Skip container diff logic and emit a single ValueSet for the property. Use when the receiving object handles a top-level ValueSet instead of per-element events.

#### class `UToolsetLibrary`  
`class UToolsetLibrary : public UBlueprintFunctionLibrary`  
_L30-145_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Provides functions that are critical to Python toolset operation but which are not available in and cannot be added to any other BFPL.
- L49 _public prototype_ `static FString ListStructProperties( const UStruct* Struct, bool bUserVisiblePropertiesOnly = true);` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Returns the properties of a struct as JSON Schema. By default only returns user-visible (Blueprint-accessible) properties. WARNING: bUserVisiblePropertiesOnly=false bypasses all visibility filtering and returns every non-deprecated property on the struct. Only use this when you know that all struct properties should be exposed. For example, DataTable row structs where every field is a data column regardless of its Blueprint visibility flags. @param Struct The struct to extract properties from. @param bUserVisiblePropertiesOnly When true (default), only Blueprint-accessible properties are included. When false, all non-deprecated properties are returned. @return A JSON Schema formatted string that describes the properties.
- L59 _public prototype_ `static FString GetObjectProperties(const UObject* Object, const TArray<FName>& PropertyNames);` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Returns the values of the requested properties. @param Object The object from which to extract properties. @param PropertyNames The names of the properties to extract. @return A JSON formatted string that contains the values of the requested properties.
- L84 _public prototype_ `static bool SetObjectProperties(UObject* Object, const FString& PropertiesJson, EBypassContainerCheck BypassContainerCheck = EBypassContainerCheck::No);` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Sets the values of specific properties in an Object. Partial-write semantics: writes are NOT transactional. Sibling properties whose JSON resolves cleanly are committed even when other properties (or other JSON keys within a nested struct) fail. A false return value means at least one property could not be set; it does not mean the object is unchanged. Callers that need all-or-nothing semantics should wrap the call in a transaction and roll back on failure. Example: passing {"name": "ok", "doesNotExist": 0} into a struct returns false, raises a script error naming "doesNotExist", AND leaves "name" set to "ok". Same applies to unknown keys inside nested structs, which surface via the same error path. @param Object The object to modify. @param PropertiesJson The property names and values in a JSON formatted string. @param BypassContainerCheck When Yes, container-size change detection is skipped and every property emits a plain ValueSet. Only use this when you know your object can handle top-level ValueSet changes instead of expecting individual ArrayAdd/ArrayRemove/ArrayClear change events when resizing containers. @return True if every property was set successfully. False indicates at least one failure; the object may already contain partial writes from sibling properties.
- L88 _public prototype_ `static bool SetObjectProperties(UObject* Object, const FString& PropertiesJson, TArray<FName>& OutSetPropertyNames, EBypassContainerCheck BypassContainerCheck = EBypassContainerCheck::No);` — C++-only overload that also reports which property names were successfully set.
- L99 _public prototype_ `static TArray<FSoftClassPath> GetDerivedClasses(UClass* BaseClass);` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Returns the list of subclasses that derive from a class. Uses the Asset Registry to find native and BP subclasses. @param BaseClass The class to get subclasses from. @return The list of native and BP classes that derive from the base class.
- L108 _public prototype_ `static TArray<UScriptStruct*> GetDerivedStructs(UScriptStruct* BaseStruct);` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Returns the list of substructs that derive from a struct. Iterates all loaded UScriptStruct objects to find matching substructs. @param BaseStruct The struct to get substructs from. @return The list of loaded structs that derive from the base struct.
- L129 _public prototype_ `static bool UndoTransaction(bool bCanRedo = false);` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Undo the most recent transaction on the global undo stack. Companion to UKismetSystemLibrary's BeginTransaction / EndTransaction / CancelTransaction, which cover starting and finalizing transactions but stop short of actually reverting them: CancelTransaction only discards the undo-stack entry without applying the inverse, so any modifications a partial transaction made to UObjects survive. Used by programmatic.execute_tool_script to roll back scripts that error out partway through. @param bCanRedo If true, the undone transaction stays on the redo stack. If false (default), it is removed entirely so a rolled-back script leaves no trace on the undo history. @return True if a transaction was undone; false if there was nothing to undo or the editor is in a state that prevents undo (e.g. saving a package, GC running, or no GEditor).
- L144 _public prototype_ `static int32 GetActiveUndoCount();` — `UFUNCTION(BlueprintCallable, Category = "Toolset Library")` — Returns the number of entries currently undoable on the global undo stack (queue length minus undo count, i.e. entries above the redo split). Snapshotting this around a BeginTransaction / EndTransaction pair lets a caller tell whether the pair actually committed a record: a transient transaction (no UObject changes) is silently dropped by UTransBuffer::End, leaving the count unchanged. @return The active undo count, or 0 when there is no editor transaction buffer available (e.g. no GEditor).

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetRegistry.h` (Public)


#### struct `UE::ToolsetRegistry::FToolDescriptor`  
`struct FToolDescriptor`  
_L21-28_
- desc: Descriptor for a tool within a toolset.
- L23 _public member_ `FString ToolsetName;`
- L24 _public member_ `FString ToolName;`
- L26 _public prototype_ `static TValueOrError<FToolDescriptor, FString> FromString( const FString& ToolsetAndToolName, bool LogErrors = false);`

#### class `UE::ToolsetRegistry::FToolsetRegistry`  
`class FToolsetRegistry`  
_L32-135_
- desc: Registry for AI toolsets. Allows registering, unregistering, finding, and executing tools from toolsets.
- L34 _public prototype_ `FToolsetRegistry( const TArray<FString>& InBlockedNames = {}, const TArray<FString>& InAllowedNames = {});`
- L37 _public prototype_ `~FToolsetRegistry();`
- L44 _public prototype_ `void AddBlockedName(const FString& Name);` — Add a pattern to the block-list. Any toolset or tool whose name matches the pattern will be treated as non-existent. Patterns enclosed in forward slashes (e.g., /^Fake. ) are treated as regular expressions. All other patterns are matched as case-insensitive substrings. Block always takes precedence over the allow-list.
- L47 _public prototype_ `void RemoveBlockedName(const FString& Name);` — Remove a pattern from the block-list. No-op if the pattern is not present.
- L50 _public prototype_ `const TArray<FString>& GetBlockedNames() const;` — Returns the current block-list patterns.
- L57 _public prototype_ `void AddAllowedName(const FString& Name);` — Add a pattern to the allow-list. Any toolset or tool whose name does not match these patterns will be treated as non-existent. Patterns enclosed in forward slashes (e.g., /^Fake. ) are treated as regular expressions. All other patterns are matched as case-insensitive substrings. Block always takes precedence over the allow-list.
- L60 _public prototype_ `void RemoveAllowedName(const FString& Name);` — Remove a pattern from the allow-list. No-op if the pattern is not present.
- L63 _public prototype_ `const TArray<FString>& GetAllowedNames() const;` — Returns the current allow-list patterns.
- L66 _public prototype_ `bool RegisterToolset(TSharedPtr<FToolset> ToolsetHandler);` — Register a toolset handler. Returns true if registration was successful.
- L69 _public prototype_ `bool UnregisterToolset(TSharedPtr<FToolset> ToolsetHandler);` — Unregister a toolset handler. Returns true if unregistration was successful.
- L72 _public prototype_ `TSharedPtr<FToolset> Find( const FString& ToolsetName, bool LogErrors = false, FString* ErrorMessage = nullptr);` — Find a registered toolset handler by name, and optionally log errors.
- L79 _public prototype_ `TFuture<TValueOrError<FString, FString>> ExecuteTool( const FString& ToolName, const FString& JsonInput);` — Execute a tool from a registered toolset handler. If there is an error in attempting to execute a tool, such as a tool not existing, the future will contain an error string.
- L86 _public prototype_ `TFuture<TValueOrError<FString, FString>> ExecuteTool( const FToolDescriptor& ToolDescriptor, const FString& JsonInput);` — Execute a tool from a registered toolset handler. If there is an error in attempting to execute a tool, such as a tool not existing, the future will contain an error string.
- L90 _public prototype_ `void ForEachToolset( TFunctionRef<void(const FString& Name, const FToolset& Toolset)> Callback) const;` — Iterate all registered toolsets.
- L95 _public prototype_ `FString GetToolsetJsonSchemas() const;` — Get the JSON schemas for all registered toolsets. Returns a JSON list concatenating all registered Toolset schemas.
- L98 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnToolsetRegistryChanged);` — Delegate to be called when the toolset registry changes.
- L101 _public function_ `FOnToolsetRegistryChanged& OnToolsetRegistered()` — Get the delegate for toolset registry changes.
- L107 _public prototype_ `bool RegisterConverter(TSharedPtr<FToolsetJsonConverter> JsonConverter);` — Register a custom JSON converter. Returns true if registration was successful.
- L110 _public prototype_ `bool UnregisterConverter(TSharedPtr<FToolsetJsonConverter> JsonConverter);` — Unregister a custom JSON converter. Returns true if unregistration was successful.
- L113 _public prototype_ `TSharedPtr<FToolsetJsonConverter> GetConverterForProperty( TNotNull<const FProperty*> Property);` — Returns the converter that can handle the specified property, if any.
- L119 _private prototype_ `void ApplyFiltersToAllToolsets();` — Calls SetNameFilters on every registered toolset, then broadcasts OnToolsetRegistryChanged. Called after any change to BlockedNames or AllowedNames.
- L122 _private member_ `TArray<FString> BlockedNames;` — Block-list pattern strings.
- L125 _private member_ `TArray<FString> AllowedNames;` — Allow-list pattern strings.
- L128 _private member_ `TMap<FString, TSharedPtr<FToolset>> ToolsetHandlers;` — The set of registered toolset handlers.
- L131 _private member_ `TMap<FString, TSharedPtr<FToolsetJsonConverter>> JsonConverters;` — The set of registered converters.
- L134 _private member_ `FOnToolsetRegistryChanged OnToolsetRegistryChanged;` — Callbacks to be called when the toolset registry changes.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TOOLSETREGISTRY_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L98 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnToolsetRegistryChanged);` — Delegate to be called when the toolset registry changes.

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetRegistrySubsystem.h` (Public)


#### class `UToolsetRegistrySettings`  
`class UToolsetRegistrySettings : public UDeveloperSettings`  
_L22-69_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, defaultconfig, MinimalAPI, meta=(DisplayName="Toolset Registry"))`
- inherits: `UDeveloperSettings`
- L27 _public function_ `virtual FName GetCategoryName() const override`
- L34 _public member_ `TArray<FString> BlockedNames;` — `UPROPERTY(config, EditAnywhere, Category="Toolsets", meta=(DisplayName="ToolsetBlockedNames"))` — Toolsets and tools whose names match any of these patterns are hidden. Patterns enclosed in forward slashes (e.g., /^Fake. ) are treated as regular expressions; all others are matched as case-insensitive substrings. Block takes precedence over ToolsetAllowedNames.
- L40 _public member_ `TArray<FString> AllowedNames;` — `UPROPERTY(config, EditAnywhere, Category="Toolsets", meta=(DisplayName="ToolsetAllowedNames"))` — When non-empty, only toolsets and tools whose names match one of these patterns are visible. Same pattern syntax as ToolsetBlockedNames. Block takes precedence over this list.
- L47 _public member_ `TArray<FString> AgentSkillBlockedNames;` — `UPROPERTY(config, EditAnywhere, Category="Agent Skills")` — AgentSkills whose paths match any of these patterns are hidden from ListSkills and GetSkills. Patterns enclosed in forward slashes (e.g., /^Foo. ) are treated as regular expressions; all others are matched as case-insensitive substrings against the skill's full path. Block takes precedence over AgentSkillAllowedNames.
- L53 _public member_ `TArray<FString> AgentSkillAllowedNames;` — `UPROPERTY(config, EditAnywhere, Category="Agent Skills")` — When non-empty, only AgentSkills whose paths match one of these patterns are visible. Same pattern syntax as AgentSkillBlockedNames. Block takes precedence over this list.
- L60 _public member_ `TArray<FString> SetObjectPropertiesBlockedClasses;` — `UPROPERTY(config, EditAnywhere, Category="SetObjectProperties Block List")` — Classes whose instances must be rejected by UToolsetLibrary::SetObjectProperties. Matched against the object's class and every parent class. Pattern syntax matches ToolsetBlockedNames (forward-slash-wrapped patterns are regex; others are case-insensitive substring).
- L68 _public member_ `TArray<FString> SetObjectPropertiesBlockedProperties;` — `UPROPERTY(config, EditAnywhere, Category="SetObjectProperties Block List")` — Class/property pairs that must be rejected by UToolsetLibrary::SetObjectProperties. Each pattern is matched against "ClassName.PropertyName" for every class in the target object's inheritance chain. Use a bare property name with a regex (e.g., /\.RootComponent$/) to match the property on every class. Same pattern syntax as SetObjectPropertiesBlockedClasses.

#### class `UToolsetRegistrySubsystem`  
`class UToolsetRegistrySubsystem : public UEditorSubsystem`  
_L72-87_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UEditorSubsystem`
- L79 _public prototype_ `static TValueOrError<TObjectPtr<UToolsetRegistrySubsystem>, FString> Get( const FString& WarningMessage = FString());` — Get the toolset registry subsystem.  Optionally log a warning if passed a non-empty string (the warning message will start with the passed-in string).
- L82 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L83 _public prototype_ `virtual void Deinitialize() override;`
- L86 _public member_ `UE::ToolsetRegistry::FToolsetRegistry ToolsetRegistry;` — The set of registered toolset handlers.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TOOLSETREGISTRY_API`

### `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/UToolsetRegistry.h` (Public)


#### class `UToolsetRegistry`  
`class UToolsetRegistry : public UBlueprintFunctionLibrary`  
_L16-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint-accessible wrapper to allow queries against the AI Toolset Registry.
- L24 _public prototype_ `static bool IsAvailable();` — `UFUNCTION(BlueprintCallable, Category="ToolsetRegistry")` — Whether the toolset registry is available. For example, this will return false if the editor is not available.
- L28 _public prototype_ `static void RegisterToolsetClass(TSubclassOf<UToolsetDefinition> InToolsetClass);` — `UFUNCTION(BlueprintCallable, Category="ToolsetRegistry")` — Register a Blueprint function library class as a toolset.
- L32 _public prototype_ `static void UnregisterToolsetClass(TSubclassOf<UToolsetDefinition> InToolsetClass);` — `UFUNCTION(BlueprintCallable, Category="ToolsetRegistry")` — Unregister a Blueprint function library class as a toolset.
- L36 _public prototype_ `static bool IsToolsetClassRegistered(TSubclassOf<UToolsetDefinition> InToolsetClass);` — `UFUNCTION(BlueprintPure, Category="ToolsetRegistry")` — Return whether a toolset class is already registered.
- L40 _public prototype_ `static bool IsToolsetRegistered(const FString& InToolsetName);` — `UFUNCTION(BlueprintPure, Category="ToolsetRegistry")` — Return whether a toolset is already registered by name.
- L46 _public prototype_ `static UToolCallAsyncResultString* ExecuteTool( const FString& ToolsetName, const FString& ToolName, const FString& JsonInput);` — `UFUNCTION(BlueprintCallable, Category="ToolsetRegistry")` — Execute a registered tool given a toolset and tool name as if it was being executed by an AI assistant. If successful, the result's value is a JSON string containing the tool's return value. If a failure occurs, the result will contain an error.
- L52 _public prototype_ `static FString GetToolsetJsonSchema(TSubclassOf<UToolsetDefinition> InToolsetClass);` — `UFUNCTION(BlueprintPure, Category="ToolsetRegistry")` — Get toolset JSON schema for a toolset class. Meant for use while testing.
- L56 _public prototype_ `static FString GetAllToolsetJsonSchemas();` — `UFUNCTION(BlueprintPure, Category="ToolsetRegistry")` — Get JSON schemas for all registered toolsets.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TOOLSETREGISTRY_API`
