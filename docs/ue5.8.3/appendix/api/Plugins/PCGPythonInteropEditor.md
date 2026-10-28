# Plugins / PCGPythonInteropEditor

- module root: `Plugins/PCGInterops/PCGPythonInterop/Source/PCGPythonInteropEditor`
- headers: 5; symbols: 104
- symbol kinds: class=5, enum=1, enumerator=2, function=13, member=19, namespace=3, prototype=61
- PrivateDependencyModuleNames: AssetDefinition, PCGEditor, PythonScriptPlugin, Slate, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, PCG, Projects

### `Plugins/PCGInterops/PCGPythonInterop/Source/PCGPythonInteropEditor/Public/Elements/PCGExecutePythonScript.h` (Public)


#### enum `EPCGPythonScriptInputMethod`  
`enum class EPCGPythonScriptInputMethod`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `Input UMETA(Tooltip = "Execute the Python script from an input data or inline.")`
- L20 _public enumerator_ `File UMETA(Tooltip = "Execute the Python script from a selected file.")`

#### class `UPCGExecutePythonScriptSettings`  
`class UPCGExecutePythonScriptSettings : public UPCGSettings, public IPCGSettingsDefaultValueProvider`  
_L27-104_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings,IPCGSettingsDefaultValueProvider`
- desc: Execute a Python script, either inline, as input, or from a file.
- L32 _private member_ `static const FString DefaultInlineScript;` — The default script to employ until replaced by the user's script.
- L37 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L38 _public prototype_ `virtual EPCGChangeType GetChangeTypeForProperty(const FName& InPropertyName) const override;`
- L42 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L43 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L44 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L45 _public prototype_ `virtual EPCGSettingsType GetType() const override;`
- L46 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L47 _public function_ `virtual bool CanCullTaskIfUnwired() const override`
- L51 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L52 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L53 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L58 _public prototype_ `virtual bool DefaultValuesAreEnabled() const override;`
- L59 _public prototype_ `virtual bool IsPinDefaultValueEnabled(FName PinLabel) const override;`
- L60 _public prototype_ `virtual bool IsPinDefaultValueActivated(FName PinLabel) const override;`
- L61 _public prototype_ `virtual EPCGMetadataTypes GetPinDefaultValueType(FName PinLabel) const override;`
- L62 _public prototype_ `virtual bool IsPinDefaultValueMetadataTypeValid(FName PinLabel, EPCGMetadataTypes DataType) const override;`
- L63 _public prototype_ `virtual bool CreateInitialDefaultValueAttribute(FName PinLabel, UPCGMetadata* OutMetadata) const override;`
- L64 _public prototype_ `virtual bool IsInputPinRequiredByExecution(const UPCGPin* InPin) const override;`
- L67 _public prototype_ `virtual void ResetDefaultValues() override;`
- L68 _public prototype_ `virtual void ResetDefaultValue(FName PinLabel) override;`
- L69 _public prototype_ `virtual void SetPinDefaultValue(FName PinLabel, const FString& DefaultValue, bool bCreateIfNeeded = false) override;`
- L70 _public prototype_ `virtual void SetPinDefaultValueIsActivated(FName PinLabel, bool bIsActivated, bool bDirtySettings = true) override;`
- L71 _public prototype_ `virtual FString GetPinDefaultValueAsString(FName PinLabel) const override;`
- L72 _public prototype_ `virtual FString GetPinInitialDefaultValueString(FName PinLabel) const override;`
- L73 _public prototype_ `virtual EPCGSettingDefaultValueExtraFlags GetDefaultValueExtraFlags(FName PinLabel) const override;`
- L77 _protected prototype_ `virtual EPCGMetadataTypes GetPinInitialDefaultValueType(FName PinLabel) const override;`
- L83 _public member_ `EPCGPythonScriptInputMethod ScriptInputMethod = EPCGPythonScriptInputMethod::Input;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — The method for receiving the intended Python source.
- L87 _public member_ `FPCGAttributePropertyInputSelector ScriptSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PCG_Overridable, EditCondition = "ScriptInputMethod == EPCGPythonScriptInputMethod::Input", EditConditionHides))` — Which attribute to use as a script source.
- L91 _public member_ `FFilePath ScriptPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PCG_Overridable, EditCondition = "ScriptInputMethod == EPCGPythonScriptInputMethod::File", EditConditionHides, FilePathFilter = "Python files (*.py)|*.py"))` — The path to the .py file that will be executed.
- L94 _public member_ `bool bMuteEditorToast = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, AdvancedDisplay, meta = (PCG_Overridable))`
- L99 _private member_ `FString InlineScript = DefaultInlineScript;` — `UPROPERTY()` — Inline constant script on the input pin to run.
- L103 _private member_ `bool bIsDefaultValueActivated = true;` — `UPROPERTY()` — Inline constant is enabled for the input pin.

#### class `FPCGExecutePythonScriptElement`  
`class FPCGExecutePythonScriptElement : public IPCGElement`  
_L106-114_
- inherits: `IPCGElement`
- L109 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L111 _protected function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override` — @todo_pcg: To be confirmed that python should be executed on main thread only.
- L113 _protected function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override` — @todo_pcg: Could be a user option to run once only, etc

### `Plugins/PCGInterops/PCGPythonInterop/Source/PCGPythonInteropEditor/Public/Elements/PCGPythonDataProcessor.h` (Public)


#### class `UPCGPythonDataProcessorSettings`  
`class UPCGPythonDataProcessorSettings : public UPCGSettings, public IPCGDynamicPinsProvider, public IPCGSettingsDefaultValueProvider`  
_L18-118_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings,IPCGDynamicPinsProvider,IPCGSettingsDefaultValueProvider`
- desc: Execute a Python script with direct access to PCG data collections. Dynamic pins accept any PCG data type with multi-connection and multi-data. The user receives an FPCGDataCollection for input and builds one for output.
- L22 _private prototype_ `UPCGPythonDataProcessorSettings();`
- L24 _private member_ `static const FString DefaultInlineScript;`
- L29 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L30 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L31 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L32 _public prototype_ `virtual EPCGSettingsType GetType() const override;`
- L33 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L34 _public function_ `virtual bool CanCullTaskIfUnwired() const override`
- L36 _public function_ `virtual bool HasDynamicPins() const override`
- L37 _public prototype_ `virtual bool IsInputPinRequiredByExecution(const UPCGPin* InPin) const override;`
- L41 _public prototype_ `virtual const FPCGDynamicPinContainer* GetDynamicPinContainer(EPCGPinDirection Direction) const override;`
- L42 _public prototype_ `virtual FPCGDynamicPinContainer* GetMutableDynamicPinContainer(EPCGPinDirection Direction) override;`
- L43 _public prototype_ `virtual TArray<FPCGPinProperties> GetStaticPinProperties(EPCGPinDirection Direction) const override;`
- L45 _public prototype_ `virtual FPCGPinProperties CreateDefaultDynamicPin(EPCGPinDirection Direction) const override;`
- L46 _public function_ `virtual bool CanUserRenameDynamicPin(EPCGPinDirection Direction) const override`
- L51 _public prototype_ `virtual bool DefaultValuesAreEnabled() const override;`
- L52 _public prototype_ `virtual bool IsPinDefaultValueEnabled(FName PinLabel) const override;`
- L53 _public prototype_ `virtual bool IsPinDefaultValueActivated(FName PinLabel) const override;`
- L54 _public prototype_ `virtual EPCGMetadataTypes GetPinDefaultValueType(FName PinLabel) const override;`
- L55 _public prototype_ `virtual bool CreateInitialDefaultValueAttribute(FName PinLabel, UPCGMetadata* OutMetadata) const override;`
- L57 _public prototype_ `virtual bool IsPinDefaultValueMetadataTypeValid(FName PinLabel, EPCGMetadataTypes DataType) const override;`
- L58 _public prototype_ `virtual void ResetDefaultValues() override;`
- L59 _public prototype_ `virtual void ResetDefaultValue(FName PinLabel) override;`
- L60 _public prototype_ `virtual void SetPinDefaultValue(FName PinLabel, const FString& DefaultValue, bool bCreateIfNeeded = false) override;`
- L61 _public prototype_ `virtual void SetPinDefaultValueIsActivated(FName PinLabel, bool bIsActivated, bool bDirtySettings = true) override;`
- L62 _public prototype_ `virtual FString GetPinDefaultValueAsString(FName PinLabel) const override;`
- L63 _public prototype_ `virtual FString GetPinInitialDefaultValueString(FName PinLabel) const override;`
- L64 _public prototype_ `virtual EPCGSettingDefaultValueExtraFlags GetDefaultValueExtraFlags(FName PinLabel) const override;`
- L70 _public member_ `EPCGPythonScriptInputMethod ScriptInputMethod = EPCGPythonScriptInputMethod::Input;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — The method for receiving the intended Python source.
- L74 _public member_ `FPCGAttributePropertyInputSelector ScriptSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PCG_Overridable, EditCondition = "ScriptInputMethod == EPCGPythonScriptInputMethod::Input", EditConditionHides))` — Which attribute to use as a script source.
- L78 _public member_ `FFilePath ScriptPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PCG_Overridable, EditCondition = "ScriptInputMethod == EPCGPythonScriptInputMethod::File", EditConditionHides, FilePathFilter = "Python files (*.py)|*.py"))` — The path to the .py file that will be executed.
- L81 _public member_ `bool bMuteEditorToast = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, AdvancedDisplay, meta = (PCG_Overridable))`
- L85 _public function_ `static bool SupportsComposition()` — `UFUNCTION()`
- L89 _public member_ `FPCGDynamicPinContainer InputDynamicPins;` — `UPROPERTY()`
- L92 _public member_ `FPCGDynamicPinContainer OutputDynamicPins;` — `UPROPERTY()`
- L97 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L98 _protected prototype_ `virtual EPCGChangeType GetChangeTypeForProperty(const FName& InPropertyName) const override;`
- L103 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L104 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L105 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L109 _protected prototype_ `virtual EPCGMetadataTypes GetPinInitialDefaultValueType(FName PinLabel) const override;`
- L114 _private member_ `FString InlineScript = DefaultInlineScript;` — `UPROPERTY()`
- L117 _private member_ `bool bIsDefaultValueActivated = true;` — `UPROPERTY()`

#### class `FPCGPythonDataProcessorElement`  
`class FPCGPythonDataProcessorElement : public IPCGElement`  
_L120-126_
- inherits: `IPCGElement`
- L123 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L124 _protected function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L125 _protected function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`

### `Plugins/PCGInterops/PCGPythonInterop/Source/PCGPythonInteropEditor/Public/Helpers/PCGPythonDataBridge.h` (Public)


#### class `UPCGPythonDataBridge`  
`class UPCGPythonDataBridge : public UObject`  
_L21-55_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Lightweight UObject bridge for passing FPCGDataCollection (a USTRUCT) into Python scope. Created per-execution with a unique name so Python can locate it via unreal.find_object(). Used by the Python Data Processor node to give users direct access to input/output collections. @todo_pcg: This bridge exists because PythonScriptPlugin's PyConversion headers are Private, so we can't use PyConversion::NativizeProperty to transfer USTRUCTs directly between Python and C++. If those headers become public, this class can be removed in favor of direct struct marshalling.
- L28 _public function_ `FPCGDataCollection GetInputCollection() const` — `UFUNCTION(BlueprintCallable, Category = "PCG|Python")` — Returns the input data collection for the current execution.
- L32 _public prototype_ `void SetOutputCollection(const FPCGDataCollection& Collection);` — `UFUNCTION(BlueprintCallable, Category = "PCG|Python")` — Stores the output data collection built by the user's Python script.
- L36 _public prototype_ `void AddToCollection(const UPCGData* InData, FName InPinLabel, TArray<FString> InTags);` — `UFUNCTION(BlueprintCallable, Category = "PCG|Python")` — Adds data to the output collection, tagged to the given pin label. Mirrors UPCGDataFunctionLibrary::AddToCollection.
- L39 _public function_ `bool HasOutputCollection() const` — Returns true if SetOutputCollection was called during this execution.
- L42 _public function_ `const FPCGDataCollection& GetOutputCollection() const` — Returns the output collection set by the user's script. Only valid if HasOutputCollection() is true.
- L45 _public prototype_ `void Initialize(const FPCGDataCollection& InInputCollection);` — Populates the bridge with input data before script execution.
- L49 _private member_ `FPCGDataCollection InputCollection;` — `UPROPERTY()`
- L52 _private member_ `FPCGDataCollection OutputCollection;` — `UPROPERTY()`
- L54 _private member_ `bool bOutputCollectionSet = false;`

### `Plugins/PCGInterops/PCGPythonInterop/Source/PCGPythonInteropEditor/Public/Helpers/PCGPythonHelpers.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PCG`
- L9 _namespace_ `namespace Python` (scope `PCG`)
- L9 _namespace_ `namespace Helpers` (scope `PCG::Python`)
- L12 _function_ `inline FString ExtractErrorSummary(const FString& Traceback)` (scope `PCG::Python::Helpers`) — Extracts the concise error line from a full Python traceback.

### `Plugins/PCGInterops/PCGPythonInterop/Source/PCGPythonInteropEditor/Public/PCGPythonInteropEditorModule.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGPython, Log, All);`
