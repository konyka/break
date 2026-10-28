# Plugins / AIAssistant

- module root: `Plugins/Experimental/AIAssistant/Source/AIAssistant`
- headers: 31; symbols: 647
- symbol kinds: class=24, delegate=4, enum=9, enumerator=28, externvar=1, function=35, macro=15, member=196, namespace=51, prototype=245, struct=30, typedef=9
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, BlueprintGraph, ContentBrowser, CoreUObject, DeveloperSettings, EditorFramework, EditorScriptingUtilities, EditorSubsystem, Engine, GraphEditor, HTTP, InputCore, Json, JsonUtilities, JsonUtilitiesEditor, Kismet, KismetCompiler, LevelEditor, Projects, PropertyEditor, PythonScriptPlugin, Slate, SlateCore, StatusBar, ToolMenus, UMG, UnrealEd, WebBrowser
- PublicDependencyModuleNames: Core, ToolsetRegistry

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistant.h` (Private)


#### class `FAIAssistantModule`  
`class FAIAssistantModule : public IModuleInterface`  
_L28-98_
- inherits: `IModuleInterface`
- L37 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L38 _public prototype_ `virtual void ShutdownModule() override;`
- L45 _public prototype_ `TSharedPtr<SAIAssistantWebBrowser> GetAIAssistantWebBrowserWidget();` — Get the AI Assistant's web browser widget. @return The AI Assistant's web browser widget.
- L54 _private prototype_ `void OnOpenPluginTab();` — This bring up the plugin tab.
- L59 _private prototype_ `void OnTogglePluginTabBasedOnCursorLocation();` — This bring up the plugin tab but select a drawer if needed based on the cursor location. Close the drawer if already open at the location.
- L64 _private prototype_ `void OnOpenPluginTab(const class FWidgetPath& InWidgetPath);` — This function will find the best tab manager to open the plugin tab into and open it in a panel drawer if available
- L69 _private prototype_ `void OnSlateQuery();` — This function will be bound to a Command. It will use AI Assistant to query the Slate UI at the current mouse position.
- L81 _private prototype_ `void ShowContextMenu(const FString& SelectedString, const FVector2f& ClientLocation) const;` — DEPRECATED? Everything left in this method can be done in JavaScript. Pops up a context menu related to the contents in the AI Assistant web browser. We usually get here via JavaScript, which provides these parameters. @param SelectedString String for that is selected in web browser. @param ClientLocation The location where the menu should appear.
- L83 _private prototype_ `void RegisterMenus();`
- L85 _private prototype_ `void RegisterStatusBarPanelDrawerSummon();`
- L86 _private prototype_ `void UnregisterStatusBarPanelDrawerSummon();`
- L87 _private prototype_ `void GenerateStatusBarPanelDrawerSummon(TArray<UStatusBarSubsystem::FTabIdAndButtonLabel>& OutTabIdsAndLabels, const TSharedRef<SDockTab>& InParentTab) const;`
- L89 _private prototype_ `TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);`
- L91 _private member_ `TSharedPtr<UE::AIAssistant::FCurrentConfig> CurrentConfig;`
- L92 _private member_ `TSharedPtr<FUICommandList> PluginCommands;`
- L93 _private member_ `TSharedPtr<FAIAssistantInputProcessor> InputProcessor;`
- L94 _private member_ `TSharedPtr<SAIAssistantWebBrowser> AIAssistantWebBrowserWidget;`
- L96 _private member_ `FDelegateHandle StatusBarPanelDrawerSummonHandle;`
- L97 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii OnPostEngineInitHandle;`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantCommands.h` (Private)


#### class `FAIAssistantCommands`  
`class FAIAssistantCommands : public TCommands<FAIAssistantCommands>`  
_L7-22_
- inherits: `TCommands<FAIAssistantCommands>`
- L10 _public prototype_ `FAIAssistantCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L19 _public member_ `TSharedPtr<FUICommandInfo> OpenAIAssistantTab;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> SummonAIAssistantTab;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AISlateQueryCommand;`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantConfig.h` (Private)


#### struct `UE::AIAssistant::FConfig`  
`struct FConfig : public FJsonSerializable`  
_L12-58_
- inherits: `FJsonSerializable`
- desc: Internal configuration for developers of the AI assistant.
- L16 _public member_ `FString MainUrl;` — Initial URL loaded when starting the assistant. If this isn't specified or is empty, FConfig::DefaultMainUrl is used.
- L18 _public member_ `FString DevOptionsRawJson;` — JSON dict of arbitrary string-any pairs for development options.
- L37 _public prototype_ `static TArray<FString> GetDefaultSearchDirectories();` — Get the default configuration search directories with the most specific overrides first. For example, when searching the engine configuration directory: * Engine/Restricted/NotForLicensees/Config/ * Engine/Restricted/NoRedist/Config/ * Engine/Restricted/LimitedAccess/Config/ * Engine/Config/ The base directories that are searched with overrides are: * Engine configuration directory: Engine/Config/ * Engine directory: Engine/ * Engine user directory (if installed): On Windows %LOCALAPPDATA%/UnrealEngine/Common/
- L40 _public prototype_ `static FString FindConfigFile(const TArray<FString>& SearchDirectories);` — Search for the assistant configuration file in the specified set of directories.
- L45 _public prototype_ `static FConfig Load(const FString& Filename);` — Attempt to the load the configuration from the specified filename. If the filename is empty return the default configuration. If configuration loading fails, an error is logged and the default configuration is returned.
- L48 _public function_ `static FConfig Load()` — Load the configuration from a file by searching default search directories.
- L54 _public member_ `static const FString DefaultMainUrl;` — Default initial URL when starting the assistant.
- L57 _public member_ `static const FString DefaultFilename;` — Configuration filename (basename, not the full path).

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantConsole.h` (Private)


#### class `UE::AIAssistant::FUefnModeSubscription`  
`class FUefnModeSubscription`  
_L15-43_
- desc: Receives notifications if the console variable that controls the assistant profile changes.
- L20 _public prototype_ `FUefnModeSubscription(TFunction<void(bool)>&& OnUefnModeFunction);` — The supplied function is called once on construction with the current mode and again if the mode changes.
- L23 _public prototype_ `FUefnModeSubscription(const FUefnModeSubscription&) = delete;` — Prevent copy.
- L24 _public prototype_ `FUefnModeSubscription& operator=(const FUefnModeSubscription&) = delete;`
- L26 _public prototype_ `~FUefnModeSubscription();`
- L30 _private prototype_ `static void InitializeUefnModeConsoleVariableSink();` — Initializes subscription to console variable changes.
- L33 _private prototype_ `static void NotifyUefnModeConsoleVariableUpdated();` — Called when the mode console variable is updated.
- L36 _private member_ `TFunction<void(bool)> OnUefnMode;`
- L40 _private member_ `static UE::FMutex SubscriptionsLock;`
- L41 _private member_ `static TDoubleLinkedList<FUefnModeSubscription*> Subscriptions;`
- L42 _private member_ `static bool bPreviousIsUefnModeConsoleVariableValue;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AIAssistant` (scope `UE`)
- L12 _externvar_ `extern const FString UefnModeConsoleVariableName;` (scope `UE::AIAssistant`) — UE vs. UEFN assistant mode.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantConversationReadyExecutor.h` (Private)


#### class `UE::AIAssistant::FConversationReadyExecutor`  
`class FConversationReadyExecutor : public FExecuteWhenReady`  
_L13-60_
- inherits: `FExecuteWhenReady`
- desc: Handles enqueuing of operations against a conversation until it's ready to accept messages.
- L16 _public typedef_ `using FGetExecuteWhenReadyStateFunc = TFunction<FExecuteWhenReady::EExecuteWhenReadyState()>;`
- L20 _public prototype_ `FConversationReadyExecutor( FGetExecuteWhenReadyStateFunc&& GetExecuteWhenReadyStateDelegate = FGetExecuteWhenReadyStateFunc());` — Construct with a delegate that retrieves additional execution when ready state.
- L24 _public prototype_ `virtual ~FConversationReadyExecutor() = default;`
- L27 _public prototype_ `void Reset();` — Reset to the initial state.
- L30 _public prototype_ `void NotifyAgentEnvironmentConfigured();` — Notify the executor that the agent environment has been configured.
- L33 _public prototype_ `void NotifyAgentEnvironmentReconfiguring();` — Notify the executor that the agent environment is being reconfigured.
- L36 _public function_ `bool IsAgentEnvironmentConfigured() const` — Whether the agent environment has been configured.
- L39 _public prototype_ `bool SetCreatingConversation(bool bNewCreatingConversation);` — Set the creating conversation flag returning the previous value.
- L42 _public function_ `template<class CallableType> void ExecuteWhenReady(CallableType&& Callable)`
- L49 _protected prototype_ `FExecuteWhenReady::EExecuteWhenReadyState GetExecuteWhenReadyState() override;`
- L52 _private prototype_ `void ClearExecutionQueueIfCreatingConversation();`
- L55 _private member_ `mutable UE::FMutex StateMutex;`
- L56 _private member_ `bool bConfiguredAgentEnvironment;`
- L57 _private member_ `bool bCreatingConversation;`
- L58 _private member_ `FGetExecuteWhenReadyStateFunc GetExecuteWhenReadyStateDelegate;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantCurrentConfig.h` (Private)


#### class `UE::AIAssistant::FCurrentConfig`  
`class FCurrentConfig`  
_L22-67_
- desc: Central location for the plugin's static configuration. At the moment, FWebApplication currently independently manages subscriptions to FUefnModeSubscription and FInternationalization::Get().OnCultureChanged() to monitor for restricted / unrestricted and language changes but they should probably be moved into this class to make it easier to test that functionality without modifying the global state of the editor.
- L38 _public prototype_ `FCurrentConfig(const FConstructorArgs& Args = FConstructorArgs());`
- L39 _public prototype_ `~FCurrentConfig() = default;`
- L42 _public prototype_ `TSharedPtr<const FConfig> Load();` — Load or reload the static configuration.
- L45 _public prototype_ `TSharedPtr<const FConfig> GetOrLoad();` — Get the currently loaded configuration.
- L49 _public function_ `bool IsEnabled() const` — Whether the assistant plugin should be enabled. This is set on construction and never modified for the lifetime of this instance.
- L52 _public function_ `FSimpleMulticastDelegate& OnPreExit() const` — Multicast delegate that can be used to watch for application pre-exit events.
- L55 _public function_ `bool IsExiting() const` — Returns true if the application is exiting.
- L59 _private prototype_ `void OnPreExitHandler();` — Handles OnPreExit event.
- L62 _private member_ `TSharedPtr<const FConfig> Config;`
- L63 _private member_ `std::atomic<bool> bIsExiting;`
- L64 _private member_ `FSimpleMulticastDelegate& OnPreExitDelegate;`
- L65 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii OnPreExitDelegateHandle;`
- L66 _private member_ `bool bIsEnabled = true;`

#### struct `UE::AIAssistant::FCurrentConfig::FConstructorArgs`  
`struct FConstructorArgs`  
_L27-35_
- desc: Arguments for the constructor so that the caller can override arguments without repeating default values.
- L30 _public function_ `FConstructorArgs()` — Explicitly define a constructor to workaround Clang DR 1351/1397.
- L31 _public member_ `FString EditorIniFilename = GEditorIni;`
- L34 _public member_ `FSimpleMulticastDelegate* OnPreExit = &FCoreDelegates::OnPreExit;` — IMPORTANT: The provided delegate lifetime must be longer than this object and FCurrentConfig constructed with this object.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantEnum.h` (Private)


#### struct `UE::AIAssistant::EnumValueDescription`  
`template <typename T> struct EnumValueDescription`  
_L121-125_
- desc: Describes an enum value.
- L123 _public member_ `T Value;`
- L124 _public member_ `const FString Description;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace AIAssistant` (scope `UE`)
- L27 _macro_ `#define UE_ENUM_VALUE(Value, UnusedDescription) Value` — Used to build an array of enum values. Given a macro that defines enum values like this: #define MY_ENUM(X)      \ X(Hello, "Hiya"),    \ X(Goodbye, "See-ya") The following generates an enum with Hello and Goodbye members: enum class ESalutation { MY_ENUM(UE_ENUM_VALUE) };
- L38 _macro_ `#define UE_ENUM_VALUE_DESCRIPTION(Value, Description) \` — Used to build an array of EnumValueDescription. Given a macro that defines enum values like this: #define MY_ENUM(X)      \ X(Hello, "Hiya"),    \ X(Goodbye, "See-ya") The following generates an array with enums mapped to strings: EnumValueDescription Description[] = { MY_ENUM(UE_ENUM_VALUE_DESCRIPTION) };
- L53 _macro_ `#define UE_ENUM_COUNT(...) \` — Used to count the number of entries in an enum. Given a macro that defines enum values like this: #define MY_ENUM(X) \ X(Hello, "Hiya"), \ X(Goodbye, "See-ya") The following generates a count of enum values stored in MyEnumCount. constexpr uint32 MyEnumCount = UE_ENUM_COUNT(MY_ENUM(UE_ENUM_COUNTER)); The macro that defines an enum must *not* include a trailing comma.
- L57 _macro_ `#define UE_ENUM_COUNTER(UnusedValue, UnusedDescription) 1` — See UE_ENUM_COUNT().
- L68 _macro_ `#define UE_ENUM_VALUE_DESCRIPTION_TYPE(EnumType, EnumTypeMacro) \` — Expands to an array type for the specified enum. Given a macro that defines enum values like this for enum MyEnum: #define MY_ENUM(X) \ X(Hello, "Hiya"), \ X(Goodbye, "See-ya") The following declares an EnumValueDescription array. extern const UE_ENUM_VALUE_DESCRIPTION_TYPE(EMyEnum, MY_ENUM MyEnumDescription);
- L80 _macro_ `#define UE_ENUM_METADATA_DECLARE(EnumType, EnumDescriptionMacro) \` — Declares metadata for an enum in the current namespace. (use in a header) * EnumTypeCount constant containing the number of items in the enum. * EnumTypeDescriptions constant containing the map of enum values to strings. * LexFromString(EnumType& OutputValue, const TCHAR* String) to convert from a string to a value. * FString LexToString(EnumType Value) to convert from an enum value to string.
- L95 _macro_ `#define UE_ENUM_METADATA_DEFINE(EnumType, EnumDescriptionMacro) \` — Defines metadata for an enum in the current namespace. (use in a source file)
- L129 _function_ `template <typename T, auto Size> TOptional<const FString*> GetEnumValueDescription( const TStaticArray<EnumValueDescription<T>, Size>& EnumValueDescriptions, T EnumValue)` (scope `UE::AIAssistant`) — Get the description of an enum value.
- L146 _function_ `template <typename T, auto Size> TOptional<T> GetEnumValueFromDescription( const TStaticArray<EnumValueDescription<T>, Size>& EnumValueDescriptions, const FString& Description, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive)` (scope `UE::AIAssistant`) — Convert an enum description to an enum value returning no value if the description is not found.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantExecuteWhenReady.h` (Private)


#### class `UE::AIAssistant::FExecuteWhenReady`  
`class FExecuteWhenReady`  
_L33-121_
- L38 _public prototype_ `FExecuteWhenReady() = default;`
- L39 _public prototype_ `virtual ~FExecuteWhenReady() = default;`
- L42 _public prototype_ `FExecuteWhenReady(const FExecuteWhenReady&) = delete;` — Disallow copies. (Unique functions in here are move-only.)
- L43 _public prototype_ `FExecuteWhenReady& operator=(const FExecuteWhenReady&) = delete;`
- L46 _public prototype_ `FExecuteWhenReady(FExecuteWhenReady&&) noexcept;` — Allow moves.
- L47 _public prototype_ `FExecuteWhenReady& operator=(FExecuteWhenReady&&) noexcept;`
- L53 _public typedef_ `using FDeferredExecutionFunction = TUniqueFunction<void()>;` — Internal type of deferred execution function.
- L61 _public function_ `template<class CallableType> void ExecuteWhenReady(CallableType&& Callable)` — To provide any callable that should be executed if/when this class is ready to do so. @param Callable Any callable, i.e. a lambda: []()->void{..do something..}
- L78 _public prototype_ `virtual EExecuteWhenReadyState GetExecuteWhenReadyState() = 0;` — Determine ready state. Overridden by derived class. @return Ready state.
- L86 _public prototype_ `void UpdateExecuteWhenReady();` — Calls and clears deferred execution functions if ready state is set to execute. Clears deferred execution functions if ready state is set to reject. Otherwise ignores deferred execution functions for now.
- L91 _public prototype_ `void ResetExecuteWhenReady();` — Clear deferred execution functions.
- L98 _public prototype_ `int32 GetNumDeferredExecutionFunctions() const;` — How many deferred execution functions are stored? Will be 0 after execution or rejection. @return Current number of deferred execution functions stored.
- L104 _public prototype_ `bool IsExecuteWhenReadyPending() const;` — Tells us if there are any deferred execution functions waiting to execute. @return If there are any deferred execution functions waiting to execute.
- L111 _private member_ `mutable FRWLock DeferredExecutionFunctionRWLock;` — Used during access/modification of deferred execution functions.
- L114 _private prototype_ `void Enqueue(FDeferredExecutionFunction&& DeferredExecutionFunction);` — Either executes incoming deferred execution function if ready now, or saves it to execute when ready later.
- L117 _private member_ `TArray<FDeferredExecutionFunction> DeferredExecutionFunctions;` — Deferred functions to execute in order, when we become ready to execute them.
- L120 _private prototype_ `void MoveFrom(FExecuteWhenReady& Other) noexcept;` — Used for custom moves.

#### enum `UE::AIAssistant::FExecuteWhenReady::EExecuteWhenReadyState`  
`enum class EExecuteWhenReadyState : uint8`  
_L67-72_
- L69 _public enumerator_ `Wait = 0`
- L70 _public enumerator_ `Execute`
- L71 _public enumerator_ `Reject`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantFileLockManager.h` (Private)


#### class `UE::AIAssistant::FFileLockManager`  
`class FFileLockManager`  
_L12-35_
- desc: Manages a list of files that should be locked from editing in the Unreal Editor. Files in this list will be opened in read-only mode.
- L16 _public prototype_ `static bool AddLockedFile(const FString& PackagePath);` — Add a file to the locked files list. Returns true if added, false if already present.
- L19 _public prototype_ `static bool RemoveLockedFile(const FString& PackagePath);` — Remove a file from the locked files list. Returns true if removed, false if not found.
- L22 _public prototype_ `static bool IsFileLocked(const FString& PackagePath);` — Check if a file is locked by package path (e.g., "/Game/MyAsset").
- L25 _public prototype_ `static TSet<FString> GetLockedFiles();` — Get all locked files.
- L28 _public prototype_ `static void ClearLockedFiles();` — Clear all locked files.
- L31 _public prototype_ `static void RegisterWithEditor();` — Register file locking hooks with the editor (asset open callback and read-only filter).
- L34 _public prototype_ `static void UnregisterFromEditor();` — Unregister file locking hooks from the editor.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantInputProcessor.h` (Private)


#### class `FAIAssistantInputProcessor`  
`class FAIAssistantInputProcessor : public IInputProcessor`  
_L26-41_
- inherits: `IInputProcessor`
- L31 _public prototype_ `explicit FAIAssistantInputProcessor(const TSharedPtr<FUICommandList>& InCommands);`
- L33 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;` — ..required
- L34 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& KeyEvent) override;`
- L40 _private member_ `TWeakPtr<FUICommandList> Commands;`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantJsonVariantSerializer.h` (Private)


#### class `UE::AIAssistant::TJsonVariantSerializer`  
`template<typename VariantTypeEnumT, typename VariantT> class TJsonVariantSerializer`  
_L44-114_
- desc: Handles serializing a variant where the variant object's type is described by an enum field. The enum, enum field name, variant type and variant field name can all be customized. See AIAssistantJsonVariantSerializerTest.cpp for an example.
- L47 _public function_ `TJsonVariantSerializer( const TCHAR* VariantTypeFieldNameToSerialize, VariantTypeEnumT& VariantTypeFieldToSerialize, const TCHAR* VariantFieldNameToSerialize, VariantT& VariantToSerialize, FJsonSerializerBase& CurrentSerializer) : VariantTypeFieldName(VariantTypeFieldNameToSerialize), VariantTypeField(VariantTypeFieldToSerialize), VariantFieldName(VariantFieldNameToSerialize), VariantField(VariantToSerialize), Serializer(CurrentSerializer)`
- L69 _public prototype_ `TJsonVariantSerializer(const TJsonVariantSerializer&) = delete;`
- L70 _public prototype_ `TJsonVariantSerializer& operator=(const TJsonVariantSerializer&) = delete;`
- L75 _public function_ `template<typename T> void Serialize(VariantTypeEnumT VariantTypeEnumValueToMatch)` — Call this once for each supported variant type and the associated enum value that instances the type.
- L109 _private member_ `const TCHAR* VariantTypeFieldName;`
- L110 _private member_ `VariantTypeEnumT& VariantTypeField;`
- L111 _private member_ `const TCHAR* VariantFieldName;`
- L112 _private member_ `VariantT& VariantField;`
- L113 _private member_ `FJsonSerializerBase& Serializer;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_JSON_SERIALIZE_ENUM_VARIANT_BEGIN( \` — Macro for TJsonVariantSerializer that provide a similar interface to JSON_SERIALIZE_VARIANT_*() This must be used within a BEGIN_JSON_SERIALIZER() block and must end with UE_JSON_SERIALIZE_ENUM_VARIANT_END(). EnumTypeFieldName is the name of the JSON field that will contain the type string, EnumTypeField is the corresponding C++ field in the FJsonSerializable. VariantFieldName is the name of the JSON field that will be parsed into / instantiate a variant in the field VariantField. After this macro, UE_JSON_SERIALIZE_ENUM_VARIANT() is used to instantiate or parse variant types.
- L28 _macro_ `#define UE_JSON_SERIALIZE_ENUM_VARIANT_END() \` — Ends a block started with UE_JSON_SERIALIZE_ENUM_VARIANT_BEGIN().
- L33 _macro_ `#define UE_JSON_SERIALIZE_ENUM_VARIANT(EnumTypeValue, VariantType) \` — Parse or instantiate the variant type VariantType when EnumTypeFieldName (see UE_JSON_SERIALIZE_ENUM_VARIANT_BEGIN) matches EnumTypeValue.
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAIAssistant, Log, Verbose);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAIAssistant, Log, Verbose);`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantRunSequential.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AIAssistant` (scope `UE`)
- L19 _function_ `template <typename FArgument, typename FPredicate> TFuture<void> RunSequential( TArray<FArgument> Arguments, FPredicate Predicate, int32 Index = 0, TSharedPtr<TPromise<void>> InPromise = nullptr)` (scope `UE::AIAssistant`) — Runs a series of asynchronous operations sequentially. Given a list of arguments and a predicate that returns TFuture<void>, this function executes the predicate for each argument in order and signals completion when all have finished. Index and InPromise are internal parameters used for recursive chaining.
- L36 _function_ `` (scope `UE::AIAssistant::RunSequential`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantSlateQuerier.h` (Private)


#### struct `UE::AIAssistant::SlateQuerier::FSlateQueryStructuredContext`  
`struct FSlateQueryStructuredContext : public FJsonSerializable`  
_L31-70_
- inherits: `FJsonSerializable`
- desc: Store structured context for query to pass along to AI Assistant as JSON.
- L33 _public member_ `FString TopWindowName;`
- L34 _public member_ `FString UnrealEditorVersion;`
- L35 _public member_ `FString UnrealEditorLanguage;`
- L36 _public member_ `FString UnrealEditorLocale;`
- L37 _public member_ `TOptional<FString> WindowName;`
- L38 _public member_ `TOptional<FString> EditorName;`
- L39 _public member_ `TOptional<FString> EditorMode;`
- L40 _public member_ `TOptional<FString> ActiveToolName;`
- L41 _public member_ `TOptional<FString> TabName;`
- L42 _public member_ `TOptional<FString> ToolTipText;`
- L43 _public member_ `TOptional<FString> TextUnderCursor;`
- L44 _public member_ `TOptional<FString> WidgetType;`
- L45 _public member_ `TOptional<FString> ActorClass;`
- L46 _public member_ `TOptional<FString> ItemName;`
- L47 _public member_ `TOptional<FString> ItemDescriptor;`
- L48 _public member_ `TOptional<FString> CategoryName;`
- L49 _public member_ `TOptional<TArray<FString>> WidgetPath;`

#### class `UE::AIAssistant::SlateQuerier::FSlateQuerier`  
`class FSlateQuerier`  
_L75-235_
- desc: Implements Slate widget querying functionality.
- L78 _public prototype_ `FSlateQuerier(const FWidgetPath& InWidgetPath);`
- L83 _public prototype_ `bool GenerateAndSendQuery();` — Inspects widget path, determines query parameters, and sends query to Assistant backend.
- L88 _public function_ `bool IsValid()` — True if a query has been successfully constructed.
- L94 _protected prototype_ `void IdentifyObjectOfQuery();` — Inspect widget path to determine query parameters.
- L99 _protected prototype_ `void GenerateQuery();` — Generate query and hidden instructions to Assistant.
- L104 _protected prototype_ `void GenerateStructuredContext();` — Generate context packet JSON to send to Assistant for additonal context clues.
- L109 _protected prototype_ `void SendQuery();` — Send query off to Assistant backend API.
- L115 _protected prototype_ `bool FindEditorName();` — Determine editor or window info from the widget path for purposes of querying the Assistant. Return true if successful.
- L121 _protected prototype_ `bool FindTabName();` — Determine tab or panel info from the widget path for purposes of querying the Assistant. Return true if successful.
- L126 _protected prototype_ `bool IsInEditor();` — Return true and store information if widget path is in a level or asset editor.
- L131 _protected prototype_ `bool IsInDrawer();` — Return true and store information if widget path is in a drawer overlay.
- L137 _protected prototype_ `bool FindItemName();` — Determine what type of widget the widget path is on for purposes of querying the Assistant. Return true if successful.
- L142 _protected prototype_ `bool ItemIsInViewport();` — Return true and store information if widget path is in a viewport.
- L147 _protected prototype_ `bool ItemIsGraphNode();` — Return true and store information if widget path is in a graph node.
- L152 _protected prototype_ `bool ItemIsSearchBox();` — Return true and store information if widget path is in a search box.
- L157 _protected prototype_ `bool ItemIsConsoleInputBox();` — Return true and store information if widget path is in a console input box.
- L162 _protected prototype_ `bool ItemIsDetailsProperty();` — Return true and store information if widget path is in a Details panel property.
- L167 _protected prototype_ `bool ItemIsPlugin();` — Return true and store information if widget path is in a plugin in Plugins browser.
- L172 _protected prototype_ `bool ItemIsBreadcrumbTrailButton();` — Return true and store information if widget path is on a navigation breadcrumb trail button.
- L177 _protected prototype_ `bool ItemIsAsset();` — Return true and store information if widget path is on an asset in Content Browser.
- L183 _protected prototype_ `bool ItemIsOutlinerActorOrSubobject();` — Return true and store information if widget path is on an Actor in the Outliner panel, or on an instance or component in the SubobjectInstanceEditor.
- L188 _protected prototype_ `bool ItemIsDetailPanelFilterCheckbox();` — Return true and store information if widget path is on a Details panel filter checkbox.
- L193 _protected prototype_ `bool ItemIsMenuItem();` — Return true and store information if widget path is on a menu item.
- L198 _protected prototype_ `bool ItemIsButton();` — Return true and store information if widget path is on a button.
- L204 _protected prototype_ `bool ItemIsButtonType(const TSet<FName> InButtonWidgetTypes, FText InItemDescriptor);` — Helper method for ItemIsButton Return true and store information if widget path is on a button.
- L210 _protected prototype_ `bool SetItemAsButton(const TSharedPtr<SWidget> Button, FText InItemDescriptor);` — Helper method for buttons.  Returns true if method was able to successfully infer a name for the button.
- L214 _private member_ `FWidgetPath OriginalWidgetPath;`
- L215 _private member_ `FWidgetPath WidgetPath;`
- L216 _private member_ `FText CurrentToolTipText;`
- L217 _private member_ `FText FormattedWindowName;`
- L218 _private member_ `FText FormattedTabName;`
- L219 _private member_ `FText TextUnderCursor;`
- L220 _private member_ `FText ItemName;`
- L221 _private member_ `FText ItemDescriptor;`
- L222 _private member_ `FString SelectedActorName;`
- L223 _private member_ `FString SelectedActorClass;`
- L224 _private member_ `TSharedPtr<SWidget> LastPickedWidget;`
- L226 _private member_ `bool bIsUIWidget = false;`
- L227 _private member_ `bool bIsObject = false;`
- L228 _private member_ `bool bIsInAssistantPanel = false;`
- L230 _private member_ `FText GeneratedQuery;`
- L231 _private member_ `FText GeneratedQueryInstructions;`
- L232 _private member_ `FText LanguageInstructions;`
- L234 _private member_ `FSlateQueryStructuredContext StructuredContext;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AIAssistant` (scope `UE`)
- L16 _namespace_ `namespace SlateQuerier` (scope `UE::AIAssistant`)
- L21 _prototype_ `FWidgetPath GetWidgetPathUnderCursor();` (scope `UE::AIAssistant::SlateQuerier`) — Get the widget path under the cursor
- L26 _prototype_ `void QueryAIAssistantAboutSlateWidget(const FWidgetPath& InWidgetPath);` (scope `UE::AIAssistant::SlateQuerier`) — Initiates an AI Assistant query to describe a Slate widget.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantSlateQuerierUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AIAssistant` (scope `UE`)
- L10 _namespace_ `namespace SlateQuerier` (scope `UE::AIAssistant`)
- L10 _namespace_ `namespace Utility` (scope `UE::AIAssistant::SlateQuerier`)
- L15 _prototype_ `FString CleanExtraWhiteSpaceFromString(const FString& InString);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Return copy of InString cleaned of redundant whitespace.
- L20 _prototype_ `FText FindTextUnderCursor(const FWidgetPath& InWidgetPath);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Look for text in widget under cursor and return it.  Return empty FText if not found.
- L25 _prototype_ `FText GetWidgetText(const TSharedRef<SWidget> InWidget);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Return text from InWidget if it is a text item.  Return empty FText if not found.
- L31 _prototype_ `FText FindChildWidgetWithText(const TSharedPtr<SWidget> InWidget);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search children of InWidget and return text from first one found with alphabetic text. Return empty FText if not found.
- L36 _prototype_ `FText FindCurrentToolTipText();` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Return first active tooltip text found.  Return empty FText if not found.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantSlateQuerierUtilsTypeSearch.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AIAssistant` (scope `UE`)
- L8 _namespace_ `namespace SlateQuerier` (scope `UE::AIAssistant`)
- L8 _namespace_ `namespace Utility` (scope `UE::AIAssistant::SlateQuerier`)
- L14 _prototype_ `TSharedPtr<SWidget> FindClosestWidgetPtrOfTypes(const FWidgetPath& InWidgetPath, const TSet<FName> InWidgetTypes);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search backwards from end of InWidgetPath and return first widget that matches any type in WidgetTypes. Return null ptr if not found.
- L20 _prototype_ `TSharedPtr<SWidget> FindClosestWidgetPtrOfType(const FWidgetPath& InWidgetPath, const FName& InWidgetType);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search backwards from end of InWidgetPath and return first widget that matches WidgetType. Return null ptr if not found.
- L27 _prototype_ `TSharedPtr<SWidget> FindClosestWidgetPtrOfSortedTypes( const FWidgetPath& InWidgetPath, const TConstArrayView<FName>& InWidgetTypes);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search backwards from end of InWidgetPath and return first widget that matches a type in WidgetTypes, testing each type in order. Return null ptr if not found.
- L34 _prototype_ `TSharedPtr<SWidget> FindFirstWidgetPtrOfType(const FWidgetPath& InWidgetPath, const FName& InWidgetType);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search forward from start of InWidgetPath and return first widget that matches WidgetType. Return null ptr if not found.
- L39 _prototype_ `void FindChildWidgetsOfType(TArray<TSharedRef<SWidget>>& OutWidgets, TSharedPtr<SWidget> InWidget, const FName& InWidgetType);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search children of InWidget for any widgets that match InWidgetType; return all found widgets in OutWidgets.
- L45 _prototype_ `TSharedPtr<SWidget> FindChildWidgetOfType(const TSharedPtr<SWidget> InWidget, const FName& InWidgetType);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search children of InWidget and return first widget that matches InWidgetType. Return null ptr if not found.
- L51 _prototype_ `TSharedPtr<SWidget> FindClosestMenuItem(const FWidgetPath& InWidgetPath);` (scope `UE::AIAssistant::SlateQuerier::Utility`) — Search backwards from end of InWidgetPath and return first menu item type widget found. Return null ptr if not found.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantStyle.h` (Private)


#### class `FAIAssistantStyle`  
`class FAIAssistantStyle`  
_L15-36_
- L20 _public prototype_ `static void Initialize();`
- L21 _public prototype_ `static void Shutdown();`
- L23 _public prototype_ `static void ReloadTextures();`
- L25 _public prototype_ `static const ISlateStyle& Get();`
- L27 _public prototype_ `static FName GetStyleSetName();`
- L33 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L35 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantSubsystem.h` (Private)


#### class `UAIAssistantSubsystem`  
`class UAIAssistantSubsystem : public UEditorSubsystem`  
_L23-49_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UEditorSubsystem`
- L29 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UEditorSubsystem interface
- L30 _public prototype_ `virtual void Deinitialize() override;`
- L38 _public prototype_ `void ShowContextMenuViaJavaScript(const FString& SelectedString, const int32 ClientX, const int32 ClientY) const;` — `UFUNCTION(BlueprintCallable, Category="JavaScript")` — See NOTE_JAVASCRIPT_CPP_FUNCTIONS in C++ code for how to call this from JavaScript.
- L43 _public prototype_ `static TValueOrError<TObjectPtr<UAIAssistantSubsystem>, FString> Get(const FString& WarningMessage=FString());` — Get the assistant subsystem.  Optionally log a warning if passed a non-empty string (the warning message will start with the passed-in string).
- L46 _public prototype_ `static FAIAssistantModule& GetAIAssistantModule();` — Get the assistant module.
- L48 _public prototype_ `static TSharedPtr<SAIAssistantWebBrowser> GetAIAssistantWebBrowserWidget();` — Get the assistant web browser.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantTextMessage.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AIAssistant` (scope `UE`)
- L12 _prototype_ `FAddMessageToConversationOptions CreateUserMessage( const FString& VisiblePrompt, const FString& HiddenContext);` (scope `UE::AIAssistant`) — Create a user message from visible and hidden prompt.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantToolResponse.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AIAssistant` (scope `UE`)
- L13 _prototype_ `FAddMessageToConversationOptions CreateToolResponseMessage( const FString& ToolName, const FString& ToolCallId, const TValueOrError<FString, FString>& ToolResult);` (scope `UE::AIAssistant`) — Create a tool response message content.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantToolset.h` (Private)


#### class `UAIAssistantContextUser`  
`class UAIAssistantContextUser : public UDeveloperSettings`  
_L15-24_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Epic Developer Assistant"))`
- inherits: `UDeveloperSettings`
- L23 _public member_ `FString Prompt;` — `UPROPERTY(Config, EditAnywhere, Category="Epic Developer Assistant", Meta=(Multiline=true))` — This field is used to help the Epic Developer Assistant understand important info about you, and can include things like your role, preferences, current goals, etc. The EDA will automatically consider this information whenever you ask it to do anything.

#### class `UAIAssistantContextProject`  
`class UAIAssistantContextProject : public UDeveloperSettings`  
_L27-36_
- reflection: `UCLASS(config=Editor, defaultconfig, meta=(DisplayName="Epic Developer Assistant"))`
- inherits: `UDeveloperSettings`
- L35 _public member_ `FString Prompt;` — `UPROPERTY(Config, EditAnywhere, Category = "Epic Developer Assistant", Meta=(Multiline=true))` — This field is used to help the Epic Developer Assistant understand important info about your project, and can include things like game genre, naming conventions, art style, etc. The EDA will automatically consider this information whenever you ask it to do anything.

#### struct `FAIAssistantContext`  
`struct FAIAssistantContext`  
_L40-55_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains information about the current Unreal project and user.
- L46 _public member_ `FString UnrealContext;` — `UPROPERTY(BlueprintReadOnly, Category = "AIAssistant")` — Describes important context about how to work with the Unreal engine.
- L50 _public member_ `FString ProjectContext;` — `UPROPERTY(BlueprintReadOnly, Category = "AIAssistant")` — Describes important context about the currently active Unreal project.
- L54 _public member_ `FString UserContext;` — `UPROPERTY(BlueprintReadOnly, Category = "AIAssistant")` — Describes important context about the currently active UnrealEd user.

#### struct `FAIAssistantDockContext`  
`struct FAIAssistantDockContext`  
_L59-74_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains information about the state of the editor that the assistant is currently docked with.
- L65 _public member_ `TObjectPtr<UObject> Asset;` — `UPROPERTY(BlueprintReadOnly, Category = "AIAssistant")` — The asset instance that is currently being edited (if any).
- L69 _public member_ `TObjectPtr<UEdGraph> Graph;` — `UPROPERTY(BlueprintReadOnly, Category = "AIAssistant")` — The graph instance that is currently being edited (if any).
- L73 _public member_ `TArray<TObjectPtr<UEdGraphNode>> SelectedNodes;` — `UPROPERTY(BlueprintReadOnly, Category = "AIAssistant")` — The list of selected graph nodes edited (if any).

#### class `UAIAssistantToolset`  
`class UAIAssistantToolset : public UToolsetDefinition`  
_L78-93_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: These functions help the AI assistant inspect its state as it relates to the larger Unreal Editor.
- L85 _public prototype_ `static FAIAssistantContext GetProjectContext();` — `UFUNCTION(meta = (AICallable), Category = "AI Assistant")` — Returns important information about the current project and/or current user.
- L92 _public prototype_ `static FAIAssistantDockContext GetDockedContext();` — `UFUNCTION(meta = (AICallable), Category = "AI Assistant")` — Returns information about the part of the unreal UI that the assistant is docked into. For example, if the assistant is docked with a Blueprint asset editor, this returns the Blueprint asset that is being edited, which graph is in focus, etc.  If the assistant is closed or not docked to an asset editor, this information will be empty.

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantTransactionBufferManager.h` (Private)


#### class `UE::AIAssistant::FTransactionBufferManager`  
`class FTransactionBufferManager`  
_L13-65_
- desc: Manager for creating and managing multiple independent transaction buffers. Allows for the creation of separate undo buffers that temporarily override the global buffer.
- L20 _public prototype_ `static TObjectPtr<UTransBuffer> GetTransactionBuffer(const FString& BufferName);` — Get an existing transaction buffer by name. @param BufferName Name of the transaction buffer to retrieve @return The transaction buffer if found, nullptr otherwise
- L27 _public prototype_ `static TObjectPtr<UTransBuffer> GetOrCreateTransactionBuffer(const FString& BufferName);` — Create a new transaction buffer with the given name. If a buffer with this name already exists, returns the existing buffer. @param BufferName Unique name for the transaction buffer @return The created or existing transaction buffer
- L35 _public prototype_ `static bool DestroyTransactionBuffer(const FString& BufferName);` — Destroy a transaction buffer by name. Removes it from the registry and releases the root reference. Cannot destroy a buffer that is currently active as an override. @param BufferName Name of the transaction buffer to destroy @return True if the buffer was destroyed, false if not found or currently active
- L40 _public prototype_ `static void Shutdown();` — Shutdown and cleanup all transaction buffers. Should be called during module shutdown. Restores any active overrides and clears all registered buffers.
- L47 _public prototype_ `static bool SetOverrideBuffer(UTransactor* OverrideBuffer);` — Override the global undo buffer with the provided buffer. The original global undo buffer is saved on first call and can be restored at any time. @param OverrideBuffer The transaction buffer to use as override. @return True if the override was set successfully, false otherwise.
- L51 _public prototype_ `static void RestoreGlobalBuffer();` — Clears the current override and restores the global undo buffer that was saved when SetOverrideBuffer was first called.
- L56 _public prototype_ `static bool IsOverrideActive();` — Check if there is currently an override buffer active. @return True if an override buffer is active, false otherwise
- L64 _public prototype_ `static TSet<FString> GetFilenamesFromUndoStack(const UTransBuffer* UndoStack);` — Extract all package path names from an undo stack. Iterates through active transactions (those that haven't been undone) and collects the package paths of all objects that were modified. @param UndoStack The transaction buffer to extract filenames from @return Set of package path names for all modified objects

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantTypes.h` (Private)


#### enum `UE::AIAssistant::EMessageRole`  
`enum class EMessageRole`  
_L19-24_
- desc: Role of the message author / source.
- L21 _public enumerator_ `Unknown` — Default; used for roles not recognized by this build.
- L22 _public enumerator_ `Agent`
- L23 _public enumerator_ `User`

#### enum `UE::AIAssistant::EMessageContentType`  
`enum class EMessageContentType`  
_L34-40_
- desc: Type of content added to a message (text and tool calls now, images etc. in future)
- L36 _public enumerator_ `Unknown` — Default; used for content types not recognized by this build.
- L37 _public enumerator_ `Text`
- L38 _public enumerator_ `ToolCall`
- L39 _public enumerator_ `ToolResponse`

#### enum `UE::AIAssistant::EConversationUpdateType`  
`enum class EConversationUpdateType`  
_L51-57_
- desc: Type of update delivered by OnConversationUpdate callbacks.
- L53 _public enumerator_ `Unknown` — Default; used for update types not recognized by this build.
- L54 _public enumerator_ `MessagesUpdated` — New messages are available for the conversation.
- L55 _public enumerator_ `Stopped` — The user requested that generation be stopped.
- L56 _public enumerator_ `Complete` — Generation has finished on the frontend.

#### struct `UE::AIAssistant::FTextMessageContent`  
`struct FTextMessageContent : public FJsonSerializable`  
_L68-79_
- inherits: `FJsonSerializable`
- desc: Text message content.
- L71 _public member_ `FString Text;` — Text message in a conversation.
- L73 _public member_ `TOptional<FString> Format;` — (Optional) Text format, default is set as markdown.

#### struct `UE::AIAssistant::FToolCallContent`  
`struct FToolCallContent : public FJsonSerializable`  
_L82-99_
- inherits: `FJsonSerializable`
- desc: Tool call message content.
- L85 _public member_ `FString Name;` — Tool name (e.g., 'agent_status', 'reference').
- L87 _public member_ `FString ArgumentsRawJson;` — Tool-specific arguments.
- L89 _public member_ `TOptional<FString> ToolCallId;` — UUID for tool calls that expect response.
- L91 _public member_ `TOptional<bool> ResponseRequired;` — Whether agent expects response, default is set to false.

#### struct `UE::AIAssistant::FToolResponseContent`  
`struct FToolResponseContent : public FJsonSerializable`  
_L102-122_
- inherits: `FJsonSerializable`
- desc: Tool response content.
- L105 _public member_ `FString ToolCallId;` — ID of the tool call this responds to.
- L107 _public member_ `FString Name;` — Name of the tool that was called.
- L109 _public member_ `FString ResponseRawJson;` — Response data from client execution.
- L111 _public member_ `TOptional<bool> Success;` — Whether execution succeeded. An empty value represents true.
- L113 _public member_ `TOptional<FString> ErrorMessage;` — Error details if success=false.

#### struct `UE::AIAssistant::FUnknownMessageContent`  
`struct FUnknownMessageContent : public FJsonSerializable`  
_L125-129_
- inherits: `FJsonSerializable`
- desc: Placeholder for message content whose type is not recognized by this build.

#### struct `UE::AIAssistant::FMessageContent`  
`struct FMessageContent : public FJsonSerializable`  
_L139-158_
- inherits: `FJsonSerializable`
- desc: Content of a message.
- L142 _public member_ `EMessageContentType ContentType = EMessageContentType::Unknown;` — Type of the messageContent field.
- L144 _public member_ `FMessageContentVariant Content;` — Content of the message, this can be extended in future to support additional types of content.
- L146 _public member_ `bool bVisibleToUser = true;` — Whether the message is visible to the user.
- L150 _public prototype_ `UE_JSON_SERIALIZE_ENUM_VARIANT(EMessageContentType::Unknown, FUnknownMessageContent);`
- L151 _public prototype_ `UE_JSON_SERIALIZE_ENUM_VARIANT(EMessageContentType::Text, FTextMessageContent);`
- L152 _public prototype_ `UE_JSON_SERIALIZE_ENUM_VARIANT(EMessageContentType::ToolCall, FToolCallContent);`
- L153 _public prototype_ `UE_JSON_SERIALIZE_ENUM_VARIANT(EMessageContentType::ToolResponse, FToolResponseContent);`
- L154 _public prototype_ `UE_JSON_SERIALIZE_ENUM_VARIANT_END();`

#### struct `UE::AIAssistant::FMessageId`  
`struct FMessageId : public FJsonSerializable`  
_L161-177_
- inherits: `FJsonSerializable`
- desc: ID of a message, generated by the assistant backend.
- L164 _public member_ `FString Id;` — Unique ID of an object.
- L166 _public member_ `FString Type;` — Discriminator of the type.
- L168 _public function_ `bool operator==(const FMessageId& Other) const`

#### struct `UE::AIAssistant::FMessage`  
`struct FMessage : public FJsonSerializable`  
_L180-198_
- inherits: `FJsonSerializable`
- desc: Message within a conversation.
- L183 _public member_ `TOptional<FMessageId> MessageId;` — Populated on the server side and ignore when specified on the client.
- L186 _public member_ `TOptional<FDateTime> Date;` — When the message was created (UTC). This is populated on the server side and ignored when specified on the client side.
- L188 _public member_ `EMessageRole MessageRole = EMessageRole::Unknown;` — Role or source of the message.
- L190 _public member_ `TArray<FMessageContent> MessageContent;` — Content of the message.

#### struct `UE::AIAssistant::FConversationDescriptor`  
`struct FConversationDescriptor : public FJsonSerializable`  
_L201-231_
- inherits: `FJsonSerializable`
- desc: Metadata used to index and display a conversation.
- L205 _public member_ `TOptional<FConversationId> ConversationId;` — ID of the conversation, this is generated on the server side and ignored if set by the client.
- L209 _public member_ `FString DisplayName;` — Display name / one-line description of the conversation that is simply used to help a user find it within a flat list of all conversations.
- L214 _public member_ `TArray<FString> Labels;` — Labels applied to the conversation to make it possible for a user to organize and search for conversations. For example: "epic.favorite" could be reserved for favorites (starred) conversations.
- L218 _public member_ `FDateTime CreatedAt;` — When the conversation was created (UTC milliseconds since the epoch). This is derived from the first message in the conversation.
- L222 _public member_ `FDateTime UpdatedAt;` — When the conversation was last updated (UTC milliseconds since the epoch). This is derived  from the most recent message in the conversation.

#### struct `UE::AIAssistant::FConversation`  
`struct FConversation : public FJsonSerializable`  
_L234-245_
- inherits: `FJsonSerializable`
- desc: Conversation.
- L237 _public member_ `FConversationDescriptor Descriptor;` — Metadata used to index and display a conversation.
- L239 _public member_ `TArray<FMessage> Messages;` — Messages in the conversation, ordered chronologically.

#### struct `UE::AIAssistant::FAddMessageToConversationOptions`  
`struct FAddMessageToConversationOptions : public FJsonSerializable`  
_L248-260_
- inherits: `FJsonSerializable`
- desc: Argument for AddMessageToConversation.
- L252 _public member_ `TOptional<FConversationId> ConversationId;` — ID of the conversation to add the message to. If this is not specified, the message is added to the current conversation.
- L254 _public member_ `FMessage Message;` — Message to add to the conversation.

#### enum `UE::AIAssistant::EPendingFileStatus`  
`enum class EPendingFileStatus`  
_L263-269_
- desc: Status indicating how a file was changed.
- L265 _public enumerator_ `Added`
- L266 _public enumerator_ `Removed`
- L267 _public enumerator_ `Modified`
- L268 _public enumerator_ `Moved`

#### struct `UE::AIAssistant::FPendingFileMetadata`  
`struct FPendingFileMetadata : public FJsonSerializable`  
_L280-297_
- inherits: `FJsonSerializable`
- desc: Metadata describing a file that has been modified by tool calls.
- L283 _public member_ `FString DisplayName;` — Display name shown to the user (e.g., filename without path).
- L285 _public member_ `FString FullPath;` — Full path to the source file.
- L287 _public member_ `EPendingFileStatus Status = EPendingFileStatus::Modified;` — Status indicating how the file was changed.
- L289 _public member_ `TOptional<FString> OriginalPath;` — For moved files, the original path before the move.

#### struct `UE::AIAssistant::FUpdatePendingFileListOptions`  
`struct FUpdatePendingFileListOptions : public FJsonSerializable`  
_L300-312_
- inherits: `FJsonSerializable`
- desc: Argument for UpdatePendingFileList.
- L304 _public member_ `TOptional<FConversationId> ConversationId;` — ID of the conversation this file list belongs to. If unspecified, the currently active conversation is used.
- L306 _public member_ `TArray<FPendingFileMetadata> Files;` — List of file metadata describing the pending file changes.

#### struct `UE::AIAssistant::FOnPendingFileDecisionOptions`  
`struct FOnPendingFileDecisionOptions : public FJsonSerializable`  
_L315-325_
- inherits: `FJsonSerializable`
- desc: Argument for OnPendingFileDecision callback.
- L318 _public member_ `FConversationId ConversationId;` — Unique ID of the conversation.
- L319 _public member_ `bool bAccepted = false;`

#### struct `UE::AIAssistant::FConversationUpdateEvent`  
`struct FConversationUpdateEvent : public FJsonSerializable`  
_L328-339_
- inherits: `FJsonSerializable`
- desc: Event delivered to OnConversationUpdate callbacks describing what changed.
- L331 _public member_ `FConversationId ConversationId;` — Unique ID of the conversation that was updated.
- L333 _public member_ `EConversationUpdateType UpdateType = EConversationUpdateType::Unknown;` — Type of update. Unknown is used for types not recognized by this build.

#### struct `UE::AIAssistant::FAgentEnvironmentDescriptor`  
`struct FAgentEnvironmentDescriptor : public FJsonSerializable`  
_L342-362_
- inherits: `FJsonSerializable`
- desc: High level descriptor of the environment is interacting with.
- L348 _public member_ `FString EnvironmentName;` — Name of the current environment. NOTE: This is a string so that this can be extended without modifying anything in the data path from the assistant client to the backend. Valid values are initially "Web", "UE", "UEFN".
- L353 _public member_ `FString EnvironmentVersion;` — If applicable, the version of the environment. For example, given a particular release version of the Unreal Engine this may allow the assistant backend to reference a particular set of documentation.
- L355 _public member_ `FString DevOptionsRawJson;` — JSON dict of arbitrary key-value pairs for development options.

#### struct `UE::AIAssistant::FAgentEnvironmentSchema`  
`struct FAgentEnvironmentSchema : public FJsonSerializable`  
_L364-389_
- inherits: `FJsonSerializable`
- L375 _public member_ `FString FrontendJsonSchemaRawJson;` — List of JSON schema objects that describe the interfaces available to the web frontend in the current environment. These are interactive modal tools we would expect the agent to not make use of when responding. For example, create a Verse file from a prior Verse code block response, add to the current UEFN project and open it in VS code. Note: In JSON this is represented as an array of JSON schema objects, but here we just store the raw JSON string.
- L383 _public member_ `FString ToolsetsRawJson;` — List of JSON schema objects that describe the JSON schema of tools available to the assistant in the current environment. This is described by EDA Tool Calling Architecture Note: In JSON this is represented as an array of JSON schema objects, but here we just store the raw JSON string.

#### struct `UE::AIAssistant::FAgentEnvironment`  
`struct FAgentEnvironment : public FJsonSerializable`  
_L392-403_
- inherits: `FJsonSerializable`
- desc: Description of the agent's environment.
- L395 _public member_ `FAgentEnvironmentDescriptor Descriptor;` — Very high level description of the environment.
- L397 _public member_ `TOptional<FAgentEnvironmentSchema> Schema;` — Schema of the environment's API.

#### struct `UE::AIAssistant::FAgentEnvironmentId`  
`struct FAgentEnvironmentId : public FJsonSerializable`  
_L407-414_
- inherits: `FJsonSerializable`
- desc: Permanent storage ID of an agent environment (e.g database generated ID)
- L409 _public member_ `FString Id;`

#### struct `UE::AIAssistant::FAgentEnvironmentHash`  
`struct FAgentEnvironmentHash : public FJsonSerializable`  
_L417-428_
- inherits: `FJsonSerializable`
- desc: Hash of an agent environment.
- L420 _public member_ `FString Algorithm;` — Name of the hash algorithm. If this is not specified, use SHA256.
- L422 _public member_ `FString Hash;` — Hash of the AgentEnvironment.

#### struct `UE::AIAssistant::FAgentEnvironmentHandle`  
`struct FAgentEnvironmentHandle : public FJsonSerializable`  
_L431-442_
- inherits: `FJsonSerializable`
- desc: Handle to an agent environment.
- L434 _public member_ `FAgentEnvironmentId Id;` — ID of the agent environment.
- L436 _public member_ `FAgentEnvironmentHash Hash;` — Hash of the environment.

#### struct `UE::AIAssistant::FWebApiBoolResult`  
`struct FWebApiBoolResult : public FJsonSerializable`  
_L445-454_
- inherits: `FJsonSerializable`
- desc: Boolean result.
- L447 _public member_ `bool bValue = false;`
- L449 _public function_ `operator bool() const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AIAssistant` (scope `UE`)
- L26 _macro_ `#define UE_AI_ASSISTANT_MESSAGE_ROLE_ENUM(X) \`
- L31 _prototype_ `UE_ENUM_METADATA_DECLARE(EMessageRole, UE_AI_ASSISTANT_MESSAGE_ROLE_ENUM);` (scope `UE::AIAssistant`)
- L42 _macro_ `#define UE_AI_ASSISTANT_MESSAGE_CONTENT_TYPE_ENUM(X) \`
- L48 _prototype_ `UE_ENUM_METADATA_DECLARE(EMessageContentType, UE_AI_ASSISTANT_MESSAGE_CONTENT_TYPE_ENUM);` (scope `UE::AIAssistant`)
- L59 _macro_ `#define UE_AI_ASSISTANT_CONVERSATION_UPDATE_TYPE_ENUM(X) \`
- L65 _prototype_ `UE_ENUM_METADATA_DECLARE(EConversationUpdateType, UE_AI_ASSISTANT_CONVERSATION_UPDATE_TYPE_ENUM);` (scope `UE::AIAssistant`)
- L131 _typedef_ `using FMessageContentVariant = TVariant< FUnknownMessageContent, FTextMessageContent, FToolCallContent, FToolResponseContent >;` (scope `UE::AIAssistant`)
- L271 _macro_ `#define UE_AI_ASSISTANT_PENDING_FILE_STATUS_ENUM(X) \`
- L277 _prototype_ `UE_ENUM_METADATA_DECLARE(EPendingFileStatus, UE_AI_ASSISTANT_PENDING_FILE_STATUS_ENUM);` (scope `UE::AIAssistant`)
- L457 _function_ `FORCEINLINE uint32 GetTypeHash(const UE::AIAssistant::FMessageId& Id)`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebApi.h` (Private)


#### class `UE::AIAssistant::FWebApi`  
`class FWebApi : private IWebJavaScriptDelegateBinder`  
_L24-309_
- inherits: `IWebJavaScriptDelegateBinder`
- desc: API to communicate with the web assistant.
- L29 _public prototype_ `FWebApi( IWebJavaScriptExecutor& JavaScriptExecutor, IWebJavaScriptDelegateBinder& JavaScriptDelegateBinder, FSimpleMulticastDelegate& UnbindDelegate);`
- L35 _public prototype_ `FWebApi(const FWebApi&) = delete;` — Prevent copy.
- L36 _public prototype_ `FWebApi& operator=(const FWebApi&) = delete;`
- L38 _public prototype_ `virtual ~FWebApi();`
- L41 _public prototype_ `TFuture<TValueOrError<FWebApiBoolResult, FString>> IsAvailable();` — Whether the web API is available in the current execution environment.
- L44 _public prototype_ `void AddMessageToConversation(const FAddMessageToConversationOptions& Options);` — Add a message to a conversation.
- L47 _public prototype_ `TFuture<TValueOrError<void, FString>> CreateConversation();` — Create a new conversation.
- L51 _public prototype_ `virtual TFuture<TValueOrError<FConversation, FString>> GetConversation( const TOptional<FConversationId>& ConversationId);` — Get a conversation by ID. If no ID is specified, the current conversation should be returned.
- L57 _public prototype_ `TFuture<TValueOrError<FAgentEnvironmentHandle, FString>> AddAgentEnvironment( const FAgentEnvironment& AgentEnvironment);` — Add an agent environment for the currently logged in user returning the ID. If a matching environment already exists for the user, this should return the existing environment (i.e upsert).
- L61 _public prototype_ `void SetAgentEnvironment(const FAgentEnvironmentId& AgentEnvironmentId);` — Set agent environment for the conversational UI.
- L64 _public prototype_ `void UpdateGlobalLocale(const FString& LocaleString);` — Update the global locale state.
- L67 _public typedef_ `using FEventCallbackHandle = TTuple<FString, FString>;` — Opaque handle to data needed to unregister an event callback.
- L69 _public typedef_ `using FOnConversationUpdateCallback = TFunction<UAIAssistantWebJavaScriptResultDelegate::EHandlerStatus(FConversationUpdateEvent)>;`
- L74 _public prototype_ `TFuture<TValueOrError<FEventCallbackHandle, FString>> RegisterOnConversationUpdate( FOnConversationUpdateCallback OnConversationUpdate);` — Register for conversation updates. To unregister the callback return EHandlerStatus::Unregister or explicitly call UnregisterOnConversationUpdate.
- L79 _public prototype_ `void UnregisterOnConversationUpdate(const FEventCallbackHandle& Registration);` — Unregister conversation update callback using the CallbackRegistration returned from RegisterOnConversationUpdate.
- L83 _public prototype_ `void UpdatePendingFileList(const FUpdatePendingFileListOptions& Options);` — Update the list of pending files modified by tool calls for a conversation. Called by the C++ backend after each tool call to report which files were modified.
- L85 _public typedef_ `using FOnPendingFileDecisionCallback = TFunction<void(FOnPendingFileDecisionOptions)>;`
- L88 _public prototype_ `TFuture<TValueOrError<FEventCallbackHandle, FString>> RegisterOnPendingFileDecision( FOnPendingFileDecisionCallback OnPendingFileDecision);` — Register a callback for when the user approves or rejects pending file changes.
- L93 _public prototype_ `void UnregisterOnPendingFileDecision(const FEventCallbackHandle& Registration);` — Unregister pending file decision callback using the handle returned from RegisterOnPendingFileDecision.
- L97 _protected prototype_ `FString FormatFunctionCall( const TCHAR* InstanceName, const TCHAR* FunctionName, const TCHAR* Arguments = TEXT(""), const FString& HandlerId = FString()) const;` — Format a function call of a member with result handling.
- L102 _protected prototype_ `FString FormatFunctionCallback(const FString& HandlerId) const;` — Format a function callback which calls a given handler ID with a result.
- L105 _protected prototype_ `TPair<FString, FString> FormatResultAndErrorHandlers(const FString& HandlerId) const;` — Format JavaScript for result and error handler function calls.
- L108 _protected prototype_ `TFuture<UAIAssistantWebJavaScriptResultDelegate::FResult> ExecuteFunction( const TCHAR* InstanceName, const TCHAR* FunctionName, const TCHAR* Arguments = TEXT(""));` — Execute a javascript function getting the result as a JSON encoded string.
- L115 _protected prototype_ `virtual FString RegisterCallback( TFunction<UAIAssistantWebJavaScriptResultDelegate::EHandlerStatus( UAIAssistantWebJavaScriptResultDelegate::FResult)> Callback);` — Register a callback with Javascript, allowing the given TFunction to be called multiple times from Javascript. This is virtual so that the returned handler ID can be captured in tests.
- L122 _protected prototype_ `virtual void ExecuteAsyncFunction( const TCHAR* InstanceName, const TCHAR* FunctionName, const TCHAR* Arguments, const TCHAR* HandlerId);` — Execute a javascript function handling the result with the specified handler. NOTE: This is virtual so tests can capture the function, arguments and handler ID before they're inserted into a script.
- L128 _protected function_ `template<typename JsonSerializableArgType> TFuture<UAIAssistantWebJavaScriptResultDelegate::FResult> ExecuteFunctionWithJsonArgument( const TCHAR* InstanceName, const TCHAR* FunctionName, const JsonSerializableArgType& Argument)` — Execute a javascript function converting an argument to JSON.
- L136 _protected function_ `TFuture<UAIAssistantWebJavaScriptResultDelegate::FResult> ExecuteFunctionWithJsonArgument( const TCHAR* InstanceName, const TCHAR* FunctionName, std::nullptr_t NullPtr)` — Execute a javascript function converting an empty argument to JSON null.
- L149 _protected function_ `CreatePromiseAndHandlerForFunction()`
- L176 _protected function_ `ExecutionFunctionParseJson(const TCHAR* InstanceName, const TCHAR* FunctionName)`
- L187 _protected function_ `ExecutionFunctionParseJson( const TCHAR* InstanceName, const TCHAR* FunctionName, const JsonSerializableArgType& Argument)`
- L200 _protected function_ `template<typename JsonSerializableReturnType> static TValueOrError<JsonSerializableReturnType, FString> ParseJsonIfNotVoid(const FString& Json)` — Parse a JSON string if JsonSerializableReturnType is not void otherwise return an empty value.
- L212 _protected function_ `template<> inline TValueOrError<void, FString> ParseJsonIfNotVoid(const FString& UnusedJson)` — Overload that ignores the supplied JSON string and returns an empty value.
- L221 _protected function_ `template<typename OptionsType> TFuture<TValueOrError<FEventCallbackHandle, FString>> RegisterEventCallback( const TCHAR* JsFunctionName, TFunction<UAIAssistantWebJavaScriptResultDelegate::EHandlerStatus( const OptionsType&)> InternalCallback)` — Register a callback for a JavaScript event, parsing the result JSON into OptionsType. InternalCallback returns EHandlerStatus to control whether the callback remains registered.
- L272 _protected prototype_ `void UnregisterEventCallback( const TCHAR* JsFunctionName, const FEventCallbackHandle& Handle);` — Unregister a previously registered event callback.
- L277 _private prototype_ `void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;` — Call the underlying binder.
- L281 _private prototype_ `void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;` — Unbind from the underlying binder and remove the reference to WebJavaScriptResultDelegate as it is likely being destroyed.
- L284 _protected member_ `IWebJavaScriptExecutor& WebJavaScriptExecutor;`
- L285 _protected member_ `IWebJavaScriptDelegateBinder& WebJavaScriptDelegateBinder;`
- L286 _protected member_ `TStrongObjectPtr<UAIAssistantWebJavaScriptResultDelegate> WebJavaScriptResultDelegate;`
- L290 _protected member_ `static const FString WebApiObjectName;` — Fully qualified name of the global object that implements the web API.
- L293 _protected member_ `static const FString WebApiAvailableFunction;` — JavaScript function that determines whether the web API is available.
- L303 _private member_ `static const FString FunctionCallFormatTemplate;` — FString::Format() template that requires: * Function: Fully qualified name of the function to call. * Arguments: String that contains the arguments to pass to the function. * NotifyHandlerOfResult: JavaScript snippet that is called with "result" to handle the result of the function. * NotifyHandlerOfError: JavaScript snippet that is called with "error" to handle a function error.
- L304 _private member_ `static const FString FunctionCallbackFormatTemplate;`
- L308 _private member_ `static const FString ConvertErrorToString;` — JavaScript that converts a variable called "error" into a string or returns the original object.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace AIAssistant` (scope `UE`)
- L157 _function_ `` (scope `UE::AIAssistant::FWebApi::CreatePromiseAndHandlerForFunction`)
- L226 _typedef_ `using FResult = UAIAssistantWebJavaScriptResultDelegate::FResult;` (scope `UE::AIAssistant::FWebApi::RegisterEventCallback`)
- L228 _function_ `[InternalCallback = MoveTemp(InternalCallback)](FResult Result)` (scope `UE::AIAssistant::FWebApi::RegisterEventCallback`)
- L252 _function_ `` (scope `UE::AIAssistant::FWebApi::RegisterEventCallback`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebApplication.h` (Private)


#### class `UE::AIAssistant::FWebApplication`  
`class FWebApplication : public TSharedFromThis<FWebApplication, ESPMode::ThreadSafe>`  
_L32-243_
- inherits: `TSharedFromThis<FWebApplication,ESPMode::ThreadSafe>`
- desc: Assistant web application.
- L45 _public prototype_ `explicit FWebApplication( TFunction<TSharedPtr<FWebApi>()>&& WebApiFactory, const FString& DevOptionsRawJson = FString());` — This *must* be constructed using MakeShared.
- L49 _public prototype_ `virtual ~FWebApplication() = default;`
- L52 _public prototype_ `FWebApplication(const FWebApplication&) = delete;` — Disable move and delete.
- L53 _public prototype_ `FWebApplication& operator=(const FWebApplication&) = delete;`
- L54 _public prototype_ `FWebApplication(FWebApplication&&) = delete;`
- L55 _public prototype_ `FWebApplication& operator=(FWebApplication&&) = delete;`
- L58 _public prototype_ `void CreateConversation();` — Create a new conversation.
- L61 _public prototype_ `virtual void AddUserMessageToConversation( FAddMessageToConversationOptions&& Options);` — Add a user message to the existing conversation.
- L65 _public prototype_ `void UpdatePendingFileList(FUpdatePendingFileListOptions&& Options);` — Add pending files modified by tool calls to the conversation.
- L68 _public prototype_ `void OnBeforeNavigation(const FString& Url, const FWebNavigationRequest& Request);` — Should be called before navigation to a new webpage occurs.
- L71 _public prototype_ `void OnPageLoadComplete();` — Should be called to notify that a page load is complete.
- L74 _public prototype_ `void OnPageLoadError();` — Notify the application that a page load error occurred.
- L79 _public prototype_ `ELoadState GetLoadState() const;` — Get the load state of the application. If the application enters ELoadState::Error a new instance of this object must be created to use the application.
- L82 _public prototype_ `TUniquePtr<FAgentEnvironment> GetAgentEnvironment(bool bUseUefnMode);` — Get the current agent environment.
- L88 _private prototype_ `void OnCultureChanged();` — Handle language / culture changed notification.
- L91 _private prototype_ `void TryUpdateAgentEnvironment(bool bUseUefnMode, bool bForce = false);` — Update the agent environment exposed to the assistant.
- L96 _private function_ `template<typename ValueType> bool HandleErrorResult( const FString& HandlerContext, const TValueOrError<ValueType, FString>& Result)` — Check a result for an error, logging the error if one is present, setting the load state to error and returning true. Returns false if the result does not have an error.
- L113 _private prototype_ `void EnsureInitialized();` — Ensure state that needs to lazily initialized is initialized.
- L116 _private prototype_ `void RegisterForConversationUpdates();` — Register for conversation updates. Called when IsLoaded() becomes true.
- L119 _private prototype_ `TSharedPtr<FWebApi> EnsureWebApi();` — Get / create the web API.
- L127 _private prototype_ `bool WithWebApi(TFunction<void(FWebApi&)>&& UsingWebApi);` — Ensure the web API is initialized and get a reference to it if possible. Returns true if the function was executed, false if the web API was not available. NOTE: The provided reference to the web API is only valid within the current stack frame. If the web API needs to be accessed later (e.g in a future continuation) it should be requested again using this method.
- L133 _private prototype_ `void WithWebApiWhenConversationReady( TFunction<void(FWebApi&)>&& UsingWebApi);` — Use the web API when the conversation is ready. IMPORTANT: See caveats in WithWebApi() documentation. NOTE: It's possible that UsingWebApi is never called if ConversationReadyExecutor's queue is flushed.
- L137 _private prototype_ `void ResetConversationState();` — Reset the conversation state.
- L140 _private prototype_ `void ResetPageState();` — Resets load/conversation state without tearing down the WebApi.
- L143 _private prototype_ `bool IsLoaded() const;` — Whether the assistant application has been loaded.
- L147 _protected prototype_ `void ResetState(const TOptional<ELoadState>&& NewLoadState = TOptional<ELoadState>());` — Reset the application state.
- L150 _protected prototype_ `virtual UE::ToolsetRegistry::FToolsetRegistry& GetToolsetRegistry();` — Get the toolset registry. This is virtual to allow overriding in tests.
- L153 _protected prototype_ `TFuture<TValueOrError<void, FString>> OnConversationUpdate(const FConversationId& ConversationId);` — Handle updates to the conversation.
- L156 _protected prototype_ `void OnPendingFileDecision(const FOnPendingFileDecisionOptions& Options);` — Handle pending file decision (accept/reject) from the user.
- L159 _protected prototype_ `void OnStopGenerating(const FConversationId& ConversationId);` — Handle stop generating notification from the frontend.
- L162 _protected prototype_ `bool IsConversationCancelled(const FString& ConversationId) const;` — Check whether a conversation has been cancelled by the user.
- L165 _protected prototype_ `virtual bool ProcessMessage(const FMessage& Message, const FString& ConversationId);` — Process a message from the conversation.
- L169 _protected prototype_ `void TrackToolResponses(const TArray<FMessage>& Messages);` — Extract all tool call IDs from their responses in a set of messages and store them in ProcessedToolCallIds.
- L172 _protected prototype_ `virtual TFuture<TValueOrError<void, FString>> ProcessToolCallContent( const FToolCallContent& ToolCall, const FString& ConversationId);` — Process a tool call message.
- L176 _protected prototype_ `FUpdatePendingFileListOptions BuildPendingFileListOptions( const FString& ConversationId, const UTransBuffer* TransactionBuffer);` — Build pending file list options from a set of filenames.
- L181 _private member_ `FConversationReadyExecutor ConversationReadyExecutor;` — Handles deferring adding messages until a conversation is ready.
- L183 _private member_ `const TFunction<TSharedPtr<FWebApi>()> CreateWebApi;` — Used to construct the web API.
- L185 _private member_ `FString DevOptionsRawJson;` — Raw JSON string for dev options passed to the agent environment.
- L187 _private member_ `bool bEnableUndoBuffer = false;` — Whether tool calls should be wrapped in undo transactions (from dev_options).
- L188 _private member_ `UE::FMutex InitializationMutex;`
- L190 _private member_ `TOptional<FUefnModeSubscription> UefnModeSubscription;` — Subscription to a cvar that controls the mode of the assistant.
- L192 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii CultureChangeDelegateHandle;` — Reference to a culture change notification delegate.
- L195 _private member_ `TOptional<FWebApi::FEventCallbackHandle> OnConversationUpdateHandle;` — Handle for conversation update registration.
- L197 _private member_ `TOptional<FWebApi::FEventCallbackHandle> OnPendingFileDecisionHandle;` — Handle for pending file decision registration.
- L199 _private member_ `TSet<FMessageId> ProcessedMessageIds;` — The set of message IDs that have been processed previously.
- L201 _private member_ `TSet<FString> ProcessedToolCallIds;` — Set of tool call IDs that have been processed.
- L204 _private member_ `TSet<FString> CancelledConversationIds;` — Set of conversation IDs that the user has cancelled via "Stop Generating". Guarded by StateMutex.
- L214 _private member_ `mutable UE::FRecursiveMutex StateMutex;` — Guards: * MaybeWebApi * bAgentEnvironmentIsUefn * bRequestedAgentEnvironmentIsUefn * bPageLoaded * bApplicationAvailable * LoadState * CancelledConversationIds
- L217 _private member_ `TSharedPtr<FWebApi> MaybeWebApi;` — Interface for the assistant web application.
- L220 _private member_ `TOptional<bool> bAgentEnvironmentIsUefn;` — Current agent environment mode if set.
- L222 _private member_ `bool bRequestedAgentEnvironmentIsUefn = false;` — Requested agent environment mode.
- L225 _private member_ `bool bPageLoaded = false;` — Whether a page load is complete.
- L227 _private member_ `bool bApplicationAvailable = false;` — Whether the application is available on the loaded page.
- L229 _private member_ `ELoadState LoadState = ELoadState::NotLoaded;` — State of the application.
- L231 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii OnToolsetRegisteredCallbackHandle;`
- L235 _private member_ `std::atomic<uint32> AgentEnvironmentUpdateGeneration = 0;` — Generation counter for environment updates. Incremented each time an update starts; only the latest generation's completion unblocks EDA responses.
- L239 _public prototype_ `static TFunction<TSharedPtr<FWebApi>()> CreateWebApiFactory( IWebJavaScriptExecutor& JavaScriptExecutor, IWebJavaScriptDelegateBinder& JavaScriptDelegateBinder, FSimpleMulticastDelegate& UnbindDelegate);` — Create a factory for web API instances.

#### enum `UE::AIAssistant::FWebApplication::ELoadState`  
`enum class ELoadState`  
_L36-41_
- desc: Load state of the AI Assistant URL.
- L38 _public enumerator_ `NotLoaded`
- L39 _public enumerator_ `Error`
- L40 _public enumerator_ `Complete`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebBrowser.h` (Private)


#### enum `UE::AIAssistant::EOpenBrowserMode`  
`enum class EOpenBrowserMode`  
_L35-39_
- desc: Where to load a URL.
- L37 _public enumerator_ `Embedded` — Open in the Unreal embedded browser.
- L38 _public enumerator_ `System` — Open in the system web browser.

#### class `SAIAssistantWebBrowser`  
`class SAIAssistantWebBrowser : public SCompoundWidget, public UE::AIAssistant::IWebJavaScriptDelegateBinder, public UE::AIAssistant::IWebJavaScriptExecutor`  
_L43-130_
- inherits: `SCompoundWidget,UE::AIAssistant::IWebJavaScriptDelegateBinder,UE::AIAssistant::IWebJavaScriptExecutor`
- L49 _public function_ `SLATE_BEGIN_ARGS(SAIAssistantWebBrowser)`
- L51 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<UE::AIAssistant::FCurrentConfig>, CurrentConfig);` — This *must* be set to construct this widget.
- L52 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<class SDockTab>& InParentTab);`
- L56 _public prototype_ `virtual ~SAIAssistantWebBrowser();`
- L62 _public prototype_ `void LoadUrl(const FString& Url, UE::AIAssistant::EOpenBrowserMode Mode) const;` — Loads a URL. @param Url Url to load. @param Mode Where to open the URL.
- L68 _public prototype_ `virtual void ExecuteJavaScript(const FString& JavaScript) override;` — JavaScript string to immediately execute in the web browser. @param JavaScript
- L71 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;` — See IWebBrowserWindow::BindUObject() / IWebBrowserWindow::UnbindUObject().
- L72 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) override;`
- L75 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Treat all keys as handled by this widget when it has focus. This prevents hotkeys from firing when users chat with the assistant.
- L76 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L82 _public prototype_ `void CreateConversation();` — Asynchronously create a new conversation.
- L87 _public prototype_ `void AddUserMessageToConversation( const FString& VisiblePrompt, const FString& HiddenContext = FString());` — Add a message to the existing conversation. If a new conversation is being currently being created, clear enqueued messages and enqueue the specified message.
- L93 _protected prototype_ `virtual TSharedPtr<UE::AIAssistant::FWebApplication> CreateWebApplication( UE::AIAssistant::IWebJavaScriptExecutor& Executor, UE::AIAssistant::IWebJavaScriptDelegateBinder& Binder, FSimpleMulticastDelegate& OnPreExit);` — Create the WebApplication for this browser. Override to provide a custom WebApplication subclass (e.g. for testing).
- L101 _private prototype_ `void InitializeWebApplication();` — Initialize this object to its initial state. This is used on construction and when reloading the page after the system has gone offline.
- L104 _private prototype_ `void EnsureWebApplication();` — Initialize the web application if it's not already initialized.
- L110 _private prototype_ `void WithWebApplication( TFunction<void(TSharedRef<UE::AIAssistant::FWebApplication>)>&& UsingWebApplication, bool bCheckUsingWebApplicationIsCalled = true) const;` — Get a reference to the current web application, if it's valid. If the reference is not valid and the editor is not shutting down, assert / check on if bCheckUsingWebApplicationIsCalled is true. When the editor is shutting down UsingWebApplication will not be called.
- L115 _private prototype_ `SAIAssistantWebConnectionWidget::EConnectionState GetConnectionState() const;` — Get the current connection state.
- L118 _private member_ `TSharedPtr<SWebBrowser> WebBrowserWidget;` — Widgets.
- L119 _private member_ `TSharedPtr<SAIAssistantWebConnectionWidget> WebConnectionWidget;`
- L121 _private member_ `TSharedPtr<SWidgetSwitcher> WebBrowserOrWebConnectionSwitcherWidget;` — Switches between web browser and connection widgets.
- L124 _private member_ `TSharedPtr<UE::AIAssistant::FCurrentConfig> CurrentConfig;` — Configuration.
- L127 _private member_ `mutable UE::FRecursiveMutex WebApplicationMutex;` — Guards MaybeWebApplication.
- L129 _private member_ `TSharedPtr<UE::AIAssistant::FWebApplication> MaybeWebApplication;` — Web application used by the widget.

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebConnectionWidget.h` (Private)


#### class `SAIAssistantWebConnectionWidget`  
`class SAIAssistantWebConnectionWidget : public SCompoundWidget`  
_L18-97_
- inherits: `SCompoundWidget`
- L24 _public prototype_ `DECLARE_DELEGATE(FOnConnected);`
- L25 _public prototype_ `DECLARE_DELEGATE(FOnDisconnected);`
- L26 _public prototype_ `DECLARE_DELEGATE(FOnReconnect);`
- L37 _public typedef_ `using FOnRequestConnectionState = TFunction<EConnectionState()>;`
- L40 _public function_ `SLATE_BEGIN_ARGS(SAIAssistantWebConnectionWidget) : _WhenDisconnectedMessage(LOCTEXT("AIAssistantWebConnection_NoInternetConnection", "No Internet Connection")), _bUseReconnectingTicker(true)`
- L45 _public prototype_ `SLATE_ARGUMENT(FText, WhenDisconnectedMessage) SLATE_ARGUMENT(bool, bUseReconnectingTicker) SLATE_ARGUMENT(FOnRequestConnectionState, OnRequestConnectionState) SLATE_EVENT(FOnConnected, OnConnected) SLATE_EVENT(FOnDisconnected, OnDisconnected) SLATE_EVENT(FOnReconnect, OnReconnect) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `EConnectionState GetConnectionState() const;` — @return The current connection state.
- L65 _public prototype_ `void Disconnect();` — Force disconnected state.
- L70 _public prototype_ `void StartReconnecting();` — Start attempt to acquire connected state.
- L75 _public prototype_ `void StopReconnecting();` — Stop attempting to acquire connected state.
- L80 _public prototype_ `void UpdateReconnecting();` — Update to check reconnection. Should probably only call this if not using the reconnecting ticker, which calls this automatically.
- L86 _private prototype_ `bool ReceiveReconnectingTickerUpdate(float DeltaTime);`
- L89 _private member_ `EConnectionState ConnectionState = EConnectionState::Connected;`
- L90 _private member_ `FOnConnected OnConnectedDelegate;`
- L91 _private member_ `FOnDisconnected OnDisconnectedDelegate;`
- L92 _private member_ `FOnReconnect OnReconnectDelegate;`
- L93 _private member_ `bool bUseReconnectingTicker = true;`
- L94 _private member_ `FTSTicker::FDelegateHandle ReconnectingTicker;`
- L95 _private member_ `FOnRequestConnectionState OnRequestConnectionStateFunction;`
- L96 _private member_ `double LastReconnectAttemptSeconds = 0.0;`

#### enum `SAIAssistantWebConnectionWidget::EConnectionState`  
`enum class EConnectionState : uint8`  
_L29-34_
- L31 _public enumerator_ `Connected`
- L32 _public enumerator_ `Disconnected`
- L33 _public enumerator_ `Reconnecting`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "SAIAssistantWebConnectionWidget"`
- L24 _delegate_ `DECLARE_DELEGATE(FOnConnected);`
- L25 _delegate_ `DECLARE_DELEGATE(FOnDisconnected);`
- L26 _delegate_ `DECLARE_DELEGATE(FOnReconnect);`

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebJavaScriptDelegateBinder.h` (Private)


#### class `UE::AIAssistant::IWebJavaScriptDelegateBinder`  
`class IWebJavaScriptDelegateBinder`  
_L11-26_
- desc: Provides a way to expose a UObject (i.e UFUNCTION) to a JavaScript execution environment (e.g a browser).
- L14 _public prototype_ `virtual ~IWebJavaScriptDelegateBinder() = default;`
- L20 _public prototype_ `virtual void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) = 0;` — Make Object with its properties (UPROPERTY) and functions (UFUNCTION) accessible from JavaScript as the name "window.ue.{Name}". For more information, see IWebBrowserWindow::BindUObject().
- L25 _public prototype_ `virtual void UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) = 0;` — Unbind an object from JavaScript. See IWebBrowserWindow::UnbindUObject().

#### class `UE::AIAssistant::FScopedWebJavaScriptDelegateBinder`  
`class FScopedWebJavaScriptDelegateBinder`  
_L30-49_
- desc: RAII container for a IWebJavaScriptDelegateBinder that binds a UObject on construction and unbinds on destruction.
- L33 _public prototype_ `FScopedWebJavaScriptDelegateBinder( IWebJavaScriptDelegateBinder& Binder, const FString& Name, UObject* Object, bool bIsPermanent = true);`
- L38 _public prototype_ `FScopedWebJavaScriptDelegateBinder(const FScopedWebJavaScriptDelegateBinder&) = delete;` — Prevent copy.
- L39 _public prototype_ `FScopedWebJavaScriptDelegateBinder& operator=( const FScopedWebJavaScriptDelegateBinder&) = delete;`
- L42 _public prototype_ `~FScopedWebJavaScriptDelegateBinder();`
- L45 _private member_ `IWebJavaScriptDelegateBinder& WebJavaScriptDelegateBinder;`
- L46 _private member_ `FString BoundObjectName;`
- L47 _private member_ `UObject* BoundObject;`
- L48 _private member_ `bool bIsPermanentBinding;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebJavaScriptExecutor.h` (Private)


#### class `UE::AIAssistant::IWebJavaScriptExecutor`  
`class IWebJavaScriptExecutor`  
_L9-18_
- desc: Executes JavaScript in a web browser.
- L12 _public prototype_ `virtual ~IWebJavaScriptExecutor() = default;`
- L17 _public prototype_ `virtual void ExecuteJavaScript(const FString& JavaScriptText) = 0;` — Execute JavaScript in a web browser without getting the result. Use UAIAssistantWebJavaScriptResultDelegate to get the result of a JavaScript execution in C++.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantWebJavaScriptResultDelegate.h` (Private)


#### class `UAIAssistantWebJavaScriptResultDelegate`  
`class UAIAssistantWebJavaScriptResultDelegate : public UObject`  
_L31-152_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Routes a JavaScript function call to a C++ handler (ResultHandler). This is registered with a JavaScript execution environment (e.g a web browser) using Bind(). After binding, C++ result handlers can be registered to handle callbacks using RegisterResultHandler().
- L66 _public typedef_ `using FResultHandler = TFunction<EHandlerStatus(FResultHandlerContext&&)>;` — Handles a JavaScript execution result. This functor should return EHandlerStatus::Unregister to unregister the handler or EHandlerStatus::Continue to leave the handler registered for future callbacks.
- L70 _public prototype_ `void Bind( UE::AIAssistant::IWebJavaScriptDelegateBinder& WebJavaScriptDelegateBinder, FSimpleMulticastDelegate& UnbindDelegate = FCoreDelegates::OnPreExit);` — Bind this object to a JavaScript execution environment as Name ("aiassistantresultdelegate").
- L78 _public prototype_ `void Unbind();` — Unregister this object from the previous JavaScript delegate binder. NOTE: This must be called before the bound IWebJavaScriptDelegateBinder is destroyed. It's not possible to rely upon automatic object lifetimes as this is a UObject and therefore can be garbage collected way far later than all references to it are dropped.
- L82 _public prototype_ `FString RegisterResultHandler(FResultHandler&& Handler);` — Register a handler for a JavaScript execution returning the ID that should be passed to this delegate.
- L86 _public prototype_ `TPair<FString, TFuture<FResult>> RegisterResultHandlerForFuture();` — Register a handler that completes a future when it's executed. This handler will always only be executed once.
- L90 _public prototype_ `FString RegisterResultHandlerForCallback(TFunction<EHandlerStatus(FResult)> Callback);` — Register a callback that may be called multiple times. Return EHandlerStatus::Unregister from the callback to unregister the handler, or explicitly call UnregisterResultHandler.
- L93 _public prototype_ `void UnregisterResultHandler(const FString& HandlerId);` — Unregister a previously registered handler with the specified ID.
- L99 _public prototype_ `FString FormatJavaScriptHandler(const FString& HandlerId) const;` — Generate a FString::Format() format string to call the JavaScript function associated with the handler using the specified ID. The returned format string has two arguments "{0}" that expects to accept an object that can be serialized as JSON to pass to the ResultHandler and "{1}" which should be truthy if the result is an error, falsey otherwise.
- L102 _public prototype_ `const FString& GetName() const;` — Get the name of the delegate.
- L109 _protected prototype_ `void HandleResult( const FString& HandlerId, const FString& ResultJson, bool bResultJsonIsError);` — `UFUNCTION(BlueprintCallable, Category = "JavaScript", meta = (BlueprintInternalUseOnly))` — Handle the result of an execution. HandlerId is the unique ID of the execution, ResultJson is the result of the execution or an error as JSON and bResultJsonIsError is true if ResultJson is an error.
- L114 _protected prototype_ `void BeginDestroy() override;` — Called when the object starts being destroyed, this unbinds and cancels all pending promises.
- L118 _private prototype_ `void RegisterResultHandlerWithId(FResultHandler&& Handler, const FString& HandlerId);` — Register a handler for a JavaScript execution with the specified ID.
- L121 _private prototype_ `void CompleteAllPendingPromises();` — Complete all pending promises.
- L124 _private prototype_ `TFuture<FResult> CreatePromiseAndGetFuture(const FString& HandlerId);` — Create a promise for a handler and get a future from the promise.
- L127 _private prototype_ `void TryCompletePendingPromise(FResultHandlerContext&& ResultContext);` — Complete a pending promise if the handler associated with the result is still available.
- L130 _private member_ `mutable UE::FMutex NameLock;` — Guards Name
- L133 _private member_ `mutable FString Name;` — Name of the delegate that is lazily initialized to avoid exposing this as a UObject property.
- L134 _private member_ `UE::FMutex ResultHandlersByIdLock;` — Guards ResultHandlersById
- L135 _private member_ `TMap<FString, TSharedPtr<FResultHandler>> ResultHandlersById;`
- L137 _private member_ `ScopedWebJavaScriptDelegateBinder;`
- L138 _private member_ `UE::FMutex PendingPromisesByIdLock;` — Guards PendingPromisesById
- L139 _private member_ `TMap<FString, TPromise<FResult>> PendingPromisesById;`
- L141 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii OnPreExitDelegateHandle;`
- L145 _private prototype_ `static FString CreateHandlerId();` — Create a handler ID.
- L149 _public member_ `static const FString BaseName;` — Base name of this object when registered with the JavaScript binder.
- L151 _public member_ `static const FString CanceledError;` — JSON result when a promise / future is canceled.

#### struct `UAIAssistantWebJavaScriptResultDelegate::FResult`  
`struct FResult`  
_L40-46_
- desc: Result of a JavaScript execution.
- L43 _public member_ `FString Json;` — JSON representation of a JavaScript function's result or error object.
- L45 _public member_ `bool bJsonIsError;` — Whether an error occurred, i.e ResultJson is represents an error object.

#### struct `UAIAssistantWebJavaScriptResultDelegate::FResultHandlerContext`  
`struct FResultHandlerContext : public FResult`  
_L49-54_
- inherits: `FResult`
- desc: Context passed to a result handler.
- L53 _public member_ `FString HandlerId;` — ID of the handler, this is used internally by UAIAssistantWebJavaScriptResultDelegate.

#### enum `UAIAssistantWebJavaScriptResultDelegate::EHandlerStatus`  
`enum class EHandlerStatus`  
_L57-61_
- desc: Whether or not the handler should remain registered or be unregistered after running.
- L59 _public enumerator_ `Continue`
- L60 _public enumerator_ `Unregister`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace AIAssistant` (scope `UE`)

### `Plugins/Experimental/AIAssistant/Source/AIAssistant/Public/AIAssistantConversationId.h` (Public)


#### struct `UE::AIAssistant::FConversationId`  
`struct FConversationId : public FJsonSerializable`  
_L13-29_
- inherits: `FJsonSerializable`
- desc: Identifies a conversation on the EDA backend.
- L16 _public member_ `FString Id;` — Unique ID string, generated by the backend.
- L18 _public member_ `FString Type;` — Type discriminator. Always "ConversationId" for values produced by MakeConversationId().
- L20 _public function_ `bool operator==(const FConversationId& Other) const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AIAssistant` (scope `UE`)
- L36 _function_ `inline FConversationId MakeConversationId(FString Id)` (scope `UE::AIAssistant`) — Creates a FConversationId from a string ID. @param Id  The conversation ID string produced by the backend. @return    A FConversationId with Type set to "ConversationId".
- L45 _function_ `FORCEINLINE uint32 GetTypeHash(const UE::AIAssistant::FConversationId& Id)`
