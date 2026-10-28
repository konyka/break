# Plugins / SubmitToolEditor

- module root: `Plugins/Experimental/SubmitToolEditor/Source/SubmitToolEditor`
- headers: 2; symbols: 41
- symbol kinds: class=2, delegate=1, function=1, member=12, prototype=23, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, DataValidation, DeveloperSettings, Engine, SourceControl, SourceControlWindows

### `Plugins/Experimental/SubmitToolEditor/Source/SubmitToolEditor/Private/SubmitToolEditor.h` (Private)


#### class `FSubmitToolEditorModule`  
`class FSubmitToolEditorModule : public IModuleInterface`  
_L17-56_
- inherits: `IModuleInterface`
- L23 _public function_ `static inline FSubmitToolEditorModule& Get()` — Get reference to the SubmitToolEditor module instance
- L29 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `void RegisterSubmitOverrideDelegate(const USubmitToolEditorSettings* InSettings);`
- L33 _public prototype_ `void UnregisterSubmitOverrideDelegate();`
- L37 _private prototype_ `FSubmitOverrideReply OnCanSubmitToolOverrideCallback(const SSubmitOverrideParameters& InParameters, FText* ErrorMessageOut);`
- L38 _private prototype_ `FSubmitOverrideReply OnSubmitToolOverrideCallback(const SSubmitOverrideParameters& InParameters);`
- L39 _private prototype_ `FSubmitOverrideReply InvokeSubmitTool(ISourceControlProvider& InProvider, const FString& InPath, const FString& InArgs, const FString& InDescription, const FString& InIdentifier);`
- L40 _private prototype_ `FSubmitOverrideReply InvokeSubmitTool(ISourceControlProvider& InProvider, const FString& InPath, const FString& InArgs, const FString& InDescription, const TArray<FString>& InFiles);`
- L41 _private prototype_ `FSubmitOverrideReply InvokeSubmitTool(ISourceControlProvider& InProvider, const FString& InPath, const FString& InArgs, const FString& InIdentifier);`
- L43 _private prototype_ `bool IsPerforceProvider() const;`
- L44 _private prototype_ `bool GetPerforceParameter(ISourceControlProvider& InProvider, FString& OutPort, FString& OutUser, FString& OutClient, FString& OutWorkspacePath);`
- L45 _private prototype_ `bool EditChangelistDescription(ISourceControlProvider& InProvider, const FString& InNewChangelistDescription, const FString& InIdentifier, FString& OutIdentifier);`
- L46 _private prototype_ `void SaveChangelistDescription(ISourceControlProvider& InProvider, const FString& InNewChangelistDescription, const FString& InIdentifier);`
- L47 _private prototype_ `bool CreateChangelist(ISourceControlProvider& InProvider, const FString& InNewChangelistDescription, const TArray<FString>& InFiles, FString& OutIdentifier);`
- L48 _private prototype_ `bool GetChangelistValidationResult(ISourceControlProvider& InProvider, const FString& InIdentifier, TArray<FText>& OutValidationMessages);`
- L49 _private prototype_ `FString UpdateValidationTag(const FString& InDescription, bool bIsvalid);`
- L50 _private prototype_ `void UpdateOptionalValidationArgs(USubmitToolEditorSettings const* InSettings, TArrayView<FText> InValidationMessages, FString& InOutArgs);`
- L51 _private prototype_ `void UpdateOptionalValidationTags(USubmitToolEditorSettings const* InSettings, TArrayView<FText> InValidationMessages, FString& InOutDescription);`
- L53 _private prototype_ `bool Tick(float InDeltaTime);`
- L55 _private member_ `FProcHandle SubmitToolProcHandle;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolEditor, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubmitToolEditor, Log, All);`

### `Plugins/Experimental/SubmitToolEditor/Source/SubmitToolEditor/Private/SubmitToolEditorSettings.h` (Private)


#### struct `FSubmitToolChangelistTagTrigger`  
`struct FSubmitToolChangelistTagTrigger`  
_L13-22_
- reflection: `USTRUCT()`
- desc: Settings for adding SubmitTool changelist tags based on validation messages
- L18 _public member_ `FString RegExMessage;` — `UPROPERTY(EditAnywhere, Category = "Submit Tool")`
- L21 _public member_ `FString SubmitToolTag;` — `UPROPERTY(EditAnywhere, Category = "Submit Tool")`

#### struct `FSubmitToolArgumentTrigger`  
`struct FSubmitToolArgumentTrigger`  
_L26-35_
- reflection: `USTRUCT()`
- desc: Settings for adding SubmitTool arguments based on validation messages
- L31 _public member_ `FString RegExMessage;` — `UPROPERTY(EditAnywhere, Category = "Submit Tool")`
- L34 _public member_ `FString SubmitToolArgument;` — `UPROPERTY(EditAnywhere, Category = "Submit Tool")`

#### class `USubmitToolEditorSettings`  
`class USubmitToolEditorSettings : public UDeveloperSettings`  
_L39-68_
- reflection: `UCLASS(config=Editor, meta = (DisplayName = "Submit Tool Settings"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the submit tool in the editor
- L44 _public prototype_ `USubmitToolEditorSettings();`
- L45 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L46 _public prototype_ `virtual FName GetCategoryName() const override;`
- L49 _public member_ `FString SubmitToolPath;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
- L52 _public member_ `FString SubmitToolArguments;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
- L55 _public member_ `bool bSubmitToolEnabled;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
- L58 _public member_ `bool bForceSubmitTool = true;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
- L61 _public member_ `bool bEnforceDataValidation;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
- L64 _public member_ `TArray<FSubmitToolChangelistTagTrigger> ChangelistTagTriggers;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
- L67 _public member_ `TArray<FSubmitToolArgumentTrigger> OptionalArgumentTriggers;` — `UPROPERTY(config, Category = "Submit Tool", EditDefaultsOnly)`
