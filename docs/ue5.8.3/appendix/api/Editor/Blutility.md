# Editor / Blutility

- module root: `Source/Editor/Blutility`
- headers: 37; symbols: 525
- symbol kinds: class=59, delegate=13, enum=1, enumerator=2, externvar=10, function=38, macro=19, member=114, namespace=2, prototype=261, struct=6
- PrivateDependencyModuleNames: AssetDefinition, AssetRegistry, AssetTools, AutomationController, BlueprintGraph, ClassViewer, CollectionManager, ContentBrowser, ContentBrowserData, Core, CoreUObject, DeveloperSettings, EditorFramework, EditorToolEvents, Engine, ImageWrapper, ImageWriteQueue, InputCore, Json, JsonUtilities, Kismet, KismetCompiler, PropertyEditor, RHI, RenderCore, Slate, SlateCore, ToolMenus, ToolWidgets, UMG, UMGEditor, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: AssetTools
- PublicDependencyModuleNames: EditorSubsystem, MainFrame

### `Source/Editor/Blutility/Classes/ActorActionUtility.h` (Public)


#### class `UActorActionUtility`  
`class UActorActionUtility : public UEditorUtilityObject, public IEditorUtilityExtension`  
_L18-46_
- reflection: `UCLASS(MinimalAPI, Abstract, hideCategories=(Object), Blueprintable)`
- inherits: `UEditorUtilityObject,IEditorUtilityExtension`
- desc: Base class for all actor action-related utilities Any functions/events that are exposed on derived classes that have the correct signature will be included as menu options when right-clicking on a group of actors in the level editor.
- L26 _public prototype_ `UClass* GetSupportedClass() const;` — `UE_DEPRECATED(5.2, "GetSupportedClasses() instead, but ideally you're not requesting this directly and are instead using the FAssetActionUtilityPrototype to wrap access to an unload utility asset.")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, Category="Assets", meta=(DeprecatedFunction, DeprecationMessage="If you were just returning a single class add it to the SupportedClasses array (you can find it listed in the Class Defaults). If you were doing complex logic to simulate having multiple classes act as filters, add them to the SupportedClasses array. If you were doing 'other' logic, you'll need to do that upon action execution."))` — Return the class that this actor action supports. Leave this blank to support all actor classes.
- L33 _public function_ `const TArray<TSoftClassPtr<UObject>>& GetSupportedClasses() const` — `UFUNCTION(BlueprintPure, Category = "Assets")` — Gets the statically determined supported classes, these classes are used as a first pass filter when determining if we can utilize this asset utility action on the asset.
- L37 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L45 _private member_ `TArray<TSoftClassPtr<UObject>> SupportedClasses;` — `UPROPERTY(EditDefaultsOnly, Category="Assets", meta=(AllowAbstract))` — For simple Asset Action's you should fill out the supported class here.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/AssetActionUtility.h` (Public)


#### struct `FAssetActionSupportCondition`  
`struct FAssetActionSupportCondition`  
_L25-52_
- reflection: `USTRUCT()`
- L36 _public member_ `FString Filter;` — `UPROPERTY(EditAnywhere, Category=Condition)` — This is a content browser styled filter.  For example, ..._N AND VirtualTextureStreaming=FALSE, would require that asset tag VirtualTextureStreaming be false, and the asset name end in _N. You can learn more about the content browser search syntax in the "Advanced Search Syntax" documentation.
- L43 _public member_ `FString FailureReason;` — `UPROPERTY(EditAnywhere, Category=Condition, meta=(MultiLine=true))` — This is the failure reason to reply to the user with if the condition above fails. If you fill in the reason, it will override the default failure text in the tooltip for the function menu option.
- L51 _public member_ `bool bShowInMenuIfFilterFails = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Asset Support")` — If this filter does not pass, show the corresponding functions from the menu anyways. If true, the menu option will display with the error tooltip, but be disabled. If false, the menu options will be removed entirely.

#### class `UAssetActionUtility`  
`class UAssetActionUtility : public UEditorUtilityObject, public IEditorUtilityExtension`  
_L60-116_
- reflection: `UCLASS(MinimalAPI, Abstract, hideCategories=(Object), Blueprintable)`
- inherits: `UEditorUtilityObject,IEditorUtilityExtension`
- desc: Base class for all asset action-related utilities Any functions/events that are exposed on derived classes that have the correct signature will be included as menu options when right-clicking on a group of assets in the content browser.
- L71 _public prototype_ `UClass* GetSupportedClass() const;` — `UE_DEPRECATED(5.2, "GetSupportedClasses() instead, but ideally you're not requesting this directly and are instead using the FAssetActionUtilityPrototype to wrap access to an unload utility asset.")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, Category="Assets", meta=(DeprecatedFunction, DeprecationMessage="If you were just returning a single class add it to the SupportedClasses array (you can find it listed in the Class Defaults). If you were doing complex logic to simulate having multiple classes act as filters, add them to the SupportedClasses array. If you were doing 'other' logic, you'll need to do that upon action execution."))` — Return the class that this asset action supports (if not implemented, it will show up for all asset types) Do not do custom logic here based on the currently selected assets.
- L79 _public prototype_ `bool IsActionForBlueprints() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Assets")` — Returns whether or not this action is designed to work specifically on Blueprints (true) or on all assets (false). If true, GetSupportedClass() is treated as a filter against the Parent Class of selected Blueprint assets. @note Returns the value of bIsActionForBlueprints by default.
- L86 _public function_ `const TArray<TSoftClassPtr<UObject>>& GetSupportedClasses() const` — `UFUNCTION(BlueprintPure, Category = "Assets")` — Gets the statically determined supported classes, these classes are used as a first pass filter when determining if we can utilize this asset utility action on the asset.
- L90 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L99 _protected member_ `bool bIsActionForBlueprints = false;` — `UPROPERTY(EditDefaultsOnly, Category="Asset Support")` — Is this action designed to work specifically on Blueprints (true) or on all assets (false). If true, SupportedClasses is treated as a filter against the Parent Class of selected Blueprint assets.
- L107 _protected member_ `TArray<TSoftClassPtr<UObject>> SupportedClasses;` — `UPROPERTY(EditDefaultsOnly, Category="Asset Support", meta=(AllowAbstract, ShowObjectRootClass))` — The supported classes controls the list of classes that may be operated on by all of the asset functions in this utility class. @note When bIsActionForBlueprints is true, this will compare against the generated class of any Blueprint assets.
- L115 _protected member_ `TArray<FAssetActionSupportCondition> SupportedConditions;` — `UPROPERTY(EditDefaultsOnly, Category="Asset Support")` — The supported conditions for any asset to use these utility functions.  Note: all of these conditions must pass in sequence.  So if you have earlier failure conditions you want to be run first, put them first in the list, if those fail, their failure reason will be handled first.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API BLUTILITY_API`
- L13 _namespace_ `namespace AssetActionUtilityTags`
- L15 _externvar_ `extern const FName BlutilityTagVersion;` (scope `AssetActionUtilityTags`)
- L16 _externvar_ `extern const FName SupportedClasses;` (scope `AssetActionUtilityTags`)
- L17 _externvar_ `extern const FName IsActionForBlueprint;` (scope `AssetActionUtilityTags`)
- L18 _externvar_ `extern const FName CallableFunctions;` (scope `AssetActionUtilityTags`)
- L19 _externvar_ `extern const FName SupportedConditions;` (scope `AssetActionUtilityTags`)

### `Source/Editor/Blutility/Classes/EditorUtilityActor.h` (Public)


#### class `AEditorUtilityActor`  
`class AEditorUtilityActor : public AActor`  
_L28-71_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `AActor`
- L34 _private prototype_ `void Run();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Editor")` — Standard function to execute
- L36 _private prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L38 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _private function_ `UInputComponent* GetInputComponent() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input|Editor")` — Returns the current InputComponent on this utility actor. This will be NULL unless bReceivesEditorInput is set to true.
- L49 _private prototype_ `void SetReceivesEditorInput(bool bInValue);` — `UFUNCTION(BlueprintSetter, Category = "Input|Editor")`
- L52 _private function_ `bool GetReceivesEditorInput() const` — `UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Input|Editor")`
- L60 _private prototype_ `void CreateEditorInput();` — Creates the EditorOnlyInputComponent if it does not already exist and registers all subobject callbacks to it
- L63 _private prototype_ `void RemoveEditorInput();` — Removes the EditorOnlyInputComponent from this utility actor
- L66 _private member_ `TObjectPtr<UInputComponent> EditorOnlyInputComponent;` — `UPROPERTY(Transient, DuplicateTransient)`
- L70 _private member_ `bool bReceivesEditorInput = false;` — `UPROPERTY(EditAnywhere, Category = "Input|Editor", BlueprintSetter = SetReceivesEditorInput, BlueprintGetter = GetReceivesEditorInput)` — If set to true, then this actor will be able to recieve input delegate callbacks when in the editor.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/EditorUtilityActorComponent.h` (Public)


#### class `UEditorUtilityActorComponent`  
`class UEditorUtilityActorComponent : public UActorComponent`  
_L19-24_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `UActorComponent`

### `Source/Editor/Blutility/Classes/EditorUtilityBlueprint.h` (Public)


#### class `UEditorUtilityBlueprint`  
`class UEditorUtilityBlueprint : public UBlueprint`  
_L20-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprint`
- L25 _private prototype_ `virtual bool SupportedByDefaultBlueprintFactory() const override;` — UBlueprint interface
- L26 _private prototype_ `virtual bool AlwaysCompileOnLoad() const override;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/EditorUtilityBlueprintFactory.h` (Public)


#### class `UEditorUtilityBlueprintFactory`  
`class UEditorUtilityBlueprintFactory : public UFactory`  
_L27-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L33 _private member_ `TSubclassOf<class UObject> ParentClass;` — `UPROPERTY(EditAnywhere, Category=BlueprintFactory, meta=(AllowAbstract = "", BlueprintBaseOnly = ""))` — The parent class of the created blueprint
- L36 _private prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L37 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L38 _private prototype_ `virtual bool CanCreateNew() const override;`
- L42 _private prototype_ `void OnClassPicked(UClass* InChosenClass);` — Handler for when a class is picked in the class picker
- L46 _protected member_ `TWeakPtr<SWindow> PickerWindow;` — A pointer to the window that is asking the user to select a parent class

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/EditorUtilityCamera.h` (Public)


#### class `AEditorUtilityCamera`  
`class AEditorUtilityCamera : public ACameraActor`  
_L19-24_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `ACameraActor`

### `Source/Editor/Blutility/Classes/EditorUtilityObject.h` (Public)


#### class `UEditorUtilityObject`  
`class UEditorUtilityObject : public UObject, public IAssetRegistryTagProviderInterface`  
_L20-42_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `UObject,IAssetRegistryTagProviderInterface`
- L26 _private prototype_ `void Run();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Editor")` — Standard function to execute
- L29 _private prototype_ `virtual void PostLoad() override;` — we use this to call tool started delegate
- L32 _private function_ `virtual bool ShouldAddCDOTagsToBlueprintClass() const override`
- L41 _protected member_ `bool bRunEditorUtilityOnStartup = false;` — `UPROPERTY(Category=Settings, EditDefaultsOnly, AssetRegistrySearchable, DisplayName="Run on Start-up")` — Run this editor utility on start-up (after asset discovery)?

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/EditorUtilityTask.h` (Public)


#### class `UEditorUtilityTask`  
`class UEditorUtilityTask : public UObject, public IAssetRegistryTagProviderInterface`  
_L32-108_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `UObject,IAssetRegistryTagProviderInterface`
- L37 _public member_ `FOnEditorUtilityTaskDelegate OnFinished;`
- L40 _public prototype_ `UEditorUtilityTask();`
- L43 _public prototype_ `void Run();` — `UFUNCTION()`
- L46 _public function_ `virtual bool ShouldAddCDOTagsToBlueprintClass() const override`
- L52 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L56 _public prototype_ `void FinishExecutingTask(const bool bSuccess = true);` — `UFUNCTION(BlueprintCallable, Category=Task)`
- L59 _public prototype_ `void SetTaskNotificationText(const FText& Text);` — `UFUNCTION(BlueprintCallable, Category = Task)`
- L62 _public prototype_ `void RequestCancel();` — Calls CancelRequested() and ReceiveCancelRequested()
- L65 _public prototype_ `bool WasCancelRequested() const;` — `UFUNCTION(BlueprintCallable, Category = Task)`
- L68 _protected function_ `virtual void BeginExecution()`
- L69 _protected function_ `virtual void CancelRequested()`
- L70 _protected prototype_ `virtual FText GetTaskTitle() const;`
- L73 _protected prototype_ `void ReceiveBeginExecution();` — `UFUNCTION(BlueprintImplementableEvent, Category=Task, meta=(DisplayName="BeginExecution"))`
- L76 _protected prototype_ `void ReceiveCancelRequested();` — `UFUNCTION(BlueprintImplementableEvent, Category=Task, meta=(DisplayName="CancelRequested"))`
- L79 _protected prototype_ `FText GetTaskTitleOverride() const;` — `UFUNCTION(BlueprintImplementableEvent, Category=Task)`
- L83 _private prototype_ `void CreateNotification();` — Calls GetTaskTitle() and GetTaskTitleOverride()
- L86 _private prototype_ `void StartExecutingTask();` — Calls BeginExecution() and ReceiveBeginExecution()
- L91 _protected member_ `bool bRunEditorUtilityOnStartup = false;` — `UPROPERTY(Category=Settings, EditDefaultsOnly, AssetRegistrySearchable, DisplayName="Run on Start-up")` — Run this editor utility on start-up (after asset discovery)?
- L95 _private member_ `TObjectPtr<UEditorUtilitySubsystem> MyTaskManager;` — `UPROPERTY(Transient)`
- L98 _private member_ `TObjectPtr<UEditorUtilityTask> MyParentTask;` — `UPROPERTY(Transient)`
- L101 _private member_ `bool bCancelRequested = false;` — `UPROPERTY(Transient)`
- L103 _private member_ `bool Cached_GIsRunningUnattendedScript = false;`
- L105 _private member_ `TUniquePtr<FAsyncTaskNotification> TaskNotification;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API BLUTILITY_API`
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityTaskDynamicDelegate, UEditorUtilityTask*, Task);`
- L25 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityTaskDynamicDelegate, UEditorUtilityTask*, Task);`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityTaskDelegate, UEditorUtilityTask* );`
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityTaskDelegate, UEditorUtilityTask* );`

### `Source/Editor/Blutility/Classes/EditorUtilityToolMenu.h` (Public)


#### class `UEditorUtilityToolMenuEntry`  
`class UEditorUtilityToolMenuEntry : public UToolMenuEntryScript, public IAssetRegistryTagProviderInterface`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, Blueprintable, abstract)`
- inherits: `UToolMenuEntryScript,IAssetRegistryTagProviderInterface`
- L19 _private function_ `virtual bool ShouldAddCDOTagsToBlueprintClass() const override`
- L28 _protected member_ `bool bRunEditorUtilityOnStartup = false;` — `UPROPERTY(Category=Settings, EditDefaultsOnly, AssetRegistrySearchable, DisplayName="Run on Start-up")` — Run this editor utility on start-up (after asset discovery)?

#### class `UEditorUtilityToolMenuSection`  
`class UEditorUtilityToolMenuSection : public UToolMenuSectionDynamic, public IAssetRegistryTagProviderInterface`  
_L32-47_
- reflection: `UCLASS(MinimalAPI, Blueprintable, abstract)`
- inherits: `UToolMenuSectionDynamic,IAssetRegistryTagProviderInterface`
- L37 _private function_ `virtual bool ShouldAddCDOTagsToBlueprintClass() const override`
- L46 _protected member_ `bool bRunEditorUtilityOnStartup = false;` — `UPROPERTY(Category=Settings, EditDefaultsOnly, AssetRegistrySearchable, DisplayName="Run on Start-up")` — Run this editor utility on start-up (after asset discovery)?

### `Source/Editor/Blutility/Classes/EditorUtilityWidget.h` (Public)


#### class `UEditorUtilityWidget`  
`class UEditorUtilityWidget : public UUserWidget, public IAssetRegistryTagProviderInterface`  
_L27-90_
- reflection: `UCLASS(MinimalAPI, Abstract, meta = (ShowWorldContextPin), config = Editor)`
- inherits: `UUserWidget,IAssetRegistryTagProviderInterface`
- L34 _public prototype_ `void Run();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Editor")` — The default action called when the widget is invoked if bAutoRunDefaultAction=true (it is never called otherwise)
- L37 _public function_ `virtual bool ShouldAddCDOTagsToBlueprintClass() const override`
- L44 _public prototype_ `UWidget* FindChildWidgetByName(FName WidgetName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Editor Utility Widget")`
- L47 _public prototype_ `void ExecuteDefaultAction();` — Run the default action
- L49 _public function_ `bool ShouldAlwaysReregisterWithWindowsMenu() const`
- L54 _public function_ `bool ShouldAutoRunDefaultAction() const`
- L60 _public function_ `FText GetTabDisplayName() const` — Returns the default desired tab display name that was specified for this widget
- L65 _public function_ `virtual bool IsEditorUtility() const override`
- L70 _protected prototype_ `virtual void NativeOnInitialized() override;` — Used to send event OnEditorToolStarted event on initialize
- L74 _protected member_ `FText TabDisplayName;` — `UPROPERTY(Category = Config, EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable)` — The display name for tabs spawned with this widget
- L77 _protected member_ `FString HelpText;` — `UPROPERTY(Category = Config, EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable)`
- L81 _protected member_ `bool bAlwaysReregisterWithWindowsMenu;` — `UPROPERTY(Config, Category = Settings, EditDefaultsOnly)` — Should this widget always be re-added to the windows menu once it's opened
- L85 _protected member_ `bool bAutoRunDefaultAction;` — `UPROPERTY(Category = Settings, EditDefaultsOnly, BlueprintReadOnly)` — Should this blueprint automatically run OnDefaultActionClicked, or should it open up a details panel to edit properties and/or offer multiple buttons
- L89 _protected member_ `bool bRunEditorUtilityOnStartup = false;` — `UPROPERTY(Category=Settings, EditDefaultsOnly, AssetRegistrySearchable, DisplayName="Run on Start-up")` — Run this editor utility on start-up (after asset discovery)?

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h` (Public)


#### class `UEditorUtilityWidgetBlueprint`  
`class UEditorUtilityWidgetBlueprint : public UWidgetBlueprint`  
_L39-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidgetBlueprint`
- L44 _public prototype_ `virtual void BeginDestroy() override;`
- L46 _public prototype_ `TSharedRef<SDockTab> SpawnEditorUITab(const FSpawnTabArgs& SpawnTabArgs);`
- L49 _public prototype_ `TSharedRef<SWidget> CreateUtilityWidget();` — Creates the slate widget from the UMG widget
- L52 _public prototype_ `void RegenerateCreatedTab(UBlueprint* RecompiledBlueprint);` — Recreate the tab's content on recompile
- L54 _public prototype_ `void UpdateRespawnListIfNeeded(TSharedRef<SDockTab> TabBeingClosed);`
- L57 _public prototype_ `virtual void GetReparentingRules(TSet< const UClass* >& AllowedChildrenOfClasses, TSet< const UClass* >& DisallowedChildrenOfClasses) const override;` — UBlueprint interface
- L59 _public function_ `virtual bool AllowEditorWidget() const override`
- L61 _public function_ `UEditorUtilityWidget* GetCreatedWidget() const`
- L66 _public function_ `void SetRegistrationName(FName InRegistrationName)`
- L71 _public function_ `FName GetRegistrationName() const`
- L77 _public prototype_ `FText GetTabDisplayName() const;` — Returns the default desired tab display name that was specified for this widget
- L79 _public function_ `bool ShouldSpawnAsNomadTab() const`
- L84 _public prototype_ `virtual UWidgetEditingProjectSettings* GetRelevantSettings() override;`
- L85 _public prototype_ `virtual const UWidgetEditingProjectSettings* GetRelevantSettings() const override;`
- L88 _public prototype_ `static void MarkTransientRecursive(UEditorUtilityWidget* UtilityWidget);`
- L91 _private prototype_ `bool IsWidgetEnabled() const;`
- L93 _private prototype_ `void ChangeTabWorld(UWorld* World, EMapChangeType MapChangeType);`
- L98 _private member_ `bool bIsEnabledInPIE = false;` — `UPROPERTY(Category = Settings, EditDefaultsOnly)` — Should the widget be enabled when running PIE
- L102 _private member_ `bool bIsEnabledInDebugging = false;` — `UPROPERTY(Category = Settings, EditDefaultsOnly)` — Should the widget be enabled when debugging BP
- L106 _private member_ `bool bSpawnAsNomadTab = false;` — `UPROPERTY(Category = Settings, EditDefaultsOnly)` — Should the widget be spawned on a Nomad tab to be docked anywhere
- L108 _private member_ `FName RegistrationName;`
- L110 _private member_ `TWeakPtr<SDockTab> CreatedTab;`
- L113 _private member_ `TObjectPtr<UEditorUtilityWidget> CreatedUMGWidget;` — `UPROPERTY(Transient)`
- L115 _private member_ `FDelegateHandle OnBlueprintCompileHandle;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/EditorUtilityWidgetBlueprintFactory.h` (Public)


#### class `UEditorUtilityWidgetBlueprintFactory`  
`class UEditorUtilityWidgetBlueprintFactory : public UFactory`  
_L26-47_
- reflection: `UCLASS(HideCategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L32 _private member_ `TEnumAsByte<EBlueprintType> BlueprintType;` — `UPROPERTY(EditAnywhere, Category = WidgetBlueprintFactory)` — The type of blueprint that will be created
- L36 _private member_ `TSubclassOf<class UUserWidget> ParentClass;` — `UPROPERTY(EditAnywhere, Category = WidgetBlueprintFactory, meta = (AllowAbstract = ""))` — The parent class of the created blueprint
- L39 _private prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L40 _private function_ `virtual bool ShouldShowInNewMenu() const override`
- L41 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L42 _private prototype_ `virtual bool CanCreateNew() const override;`
- L46 _private member_ `UClass* RootWidgetClass;`

### `Source/Editor/Blutility/Classes/EditorUtilityWidgetComponents.h` (Public)


#### class `UEditorUtilityButton`  
`class UEditorUtilityButton : public UButton`  
_L38-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UButton`

#### class `UEditorUtilityCheckBox`  
`class UEditorUtilityCheckBox : public UCheckBox`  
_L44-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCheckBox`

#### class `UEditorUtilityCircularThrobber`  
`class UEditorUtilityCircularThrobber : public UCircularThrobber`  
_L50-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCircularThrobber`

#### class `UEditorUtilityComboBoxKey`  
`class UEditorUtilityComboBoxKey : public UComboBoxKey`  
_L56-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UComboBoxKey`
- L61 _public prototype_ `UEditorUtilityComboBoxKey();`

#### class `UEditorUtilityComboBoxString`  
`class UEditorUtilityComboBoxString : public UComboBoxString`  
_L65-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UComboBoxString`

#### class `UEditorUtilityEditableText`  
`class UEditorUtilityEditableText : public UEditableText`  
_L71-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditableText`

#### class `UEditorUtilityEditableTextBox`  
`class UEditorUtilityEditableTextBox : public UEditableTextBox`  
_L77-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditableTextBox`

#### class `UEditorUtilityExpandableArea`  
`class UEditorUtilityExpandableArea : public UExpandableArea`  
_L83-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UExpandableArea`

#### class `UEditorUtilityInputKeySelector`  
`class UEditorUtilityInputKeySelector : public UInputKeySelector`  
_L89-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputKeySelector`

#### class `UEditorUtilityListView`  
`class UEditorUtilityListView : public UListView`  
_L95-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UListView`

#### class `UEditorUtilityMultiLineEditableText`  
`class UEditorUtilityMultiLineEditableText : public UMultiLineEditableText`  
_L101-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiLineEditableText`

#### class `UEditorUtilityMultiLineEditableTextBox`  
`class UEditorUtilityMultiLineEditableTextBox : public UMultiLineEditableTextBox`  
_L107-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiLineEditableTextBox`

#### class `UEditorUtilityProgressBar`  
`class UEditorUtilityProgressBar : public UProgressBar`  
_L113-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProgressBar`

#### class `UEditorUtilityScrollBar`  
`class UEditorUtilityScrollBar : public UScrollBar`  
_L119-122_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScrollBar`

#### class `UEditorUtilityScrollBox`  
`class UEditorUtilityScrollBox : public UScrollBox`  
_L125-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScrollBox`

#### class `UEditorUtilitySlider`  
`class UEditorUtilitySlider : public USlider`  
_L131-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USlider`

#### class `UEditorUtilitySpinBox`  
`class UEditorUtilitySpinBox : public USpinBox`  
_L137-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USpinBox`

#### class `UEditorUtilityThrobber`  
`class UEditorUtilityThrobber : public UThrobber`  
_L143-146_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UThrobber`

#### class `UEditorUtilityTreeView`  
`class UEditorUtilityTreeView : public UTreeView`  
_L149-152_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTreeView`

#### Free symbols / members of external scopes

- L35 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Classes/GlobalEditorUtilityBase.h` (Public)


#### class `UDEPRECATED_GlobalEditorUtilityBase`  
`class UDEPRECATED_GlobalEditorUtilityBase : public UObject`  
_L33-122_
- reflection: `UCLASS(MinimalAPI, Abstract, hideCategories=(Object), Blueprintable, Deprecated)`
- inherits: `UObject`
- L38 _private member_ `FString HelpText;` — `UPROPERTY(Category=Config, EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable)`
- L41 _private member_ `bool bDirtiedSelectionSet;` — `UPROPERTY(Transient)`
- L44 _private prototype_ `virtual UWorld* GetWorld() const override;` — UObject interface
- L47 _private prototype_ `TArray<AActor*> GetSelectionSet();` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")`
- L55 _private prototype_ `AActor* GetActorReference(FString PathToActor);` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Attempts to find the actor specified by PathToActor in the current editor world @param	PathToActor	The path to the actor (e.g. PersistentLevel.PlayerStart) @return	A reference to the actor, or none if it wasn't found
- L61 _private member_ `bool bAutoRunDefaultAction;` — `UPROPERTY(Category=Settings, EditDefaultsOnly, BlueprintReadOnly)` — Should this blueprint automatically run OnDefaultActionClicked, or should it open up a details panel to edit properties and/or offer multiple buttons
- L65 _private prototype_ `void OnDefaultActionClicked();` — `UFUNCTION(BlueprintImplementableEvent)` — The default action called when the blutility is invoked if bAutoRunDefaultAction=true (it is never called otherwise)
- L71 _private prototype_ `void ForEachSelectedActor();` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")` — Calls OnEachSelectedActor for each selected actor
- L75 _private member_ `FForEachActorIteratorSignature OnEachSelectedActor;` — `UPROPERTY(BlueprintAssignable)` — The method called for each selected actor when ForEachSelectedActor is called
- L81 _private prototype_ `void ForEachSelectedAsset();` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")` — Calls OnEachSelectedAsset for each selected asset
- L85 _private member_ `FForEachAssetIteratorSignature OnEachSelectedAsset;` — `UPROPERTY(BlueprintAssignable)` — The method called for each selected asset when ForEachSelectedAsset is called
- L89 _private prototype_ `TArray<UObject*> GetSelectedAssets();` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")` — Gets the set of currently selected assets
- L94 _private prototype_ `UEditorPerProjectUserSettings* GetEditorUserSettings();` — `UFUNCTION(BlueprintPure, Category="Development|Editor")`
- L98 _private prototype_ `void ClearActorSelectionSet();` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")` — Remove all actors from the selection set
- L102 _private prototype_ `void SelectNothing();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Selects nothing in the editor (another way to clear the selection)
- L106 _private prototype_ `void SetActorSelectionState(AActor* Actor, bool bShouldBeSelected);` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")` — Set the selection state for the selected actor
- L109 _private prototype_ `void GetSelectionBounds(FVector& Origin, FVector& BoxExtent, float& SphereRadius);` — `UFUNCTION(BlueprintCallable, Category="Development|Editor")`
- L113 _private prototype_ `void RenameAsset(UObject* Asset, const FString& NewName);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Renames an asset (cannot move folders)
- L118 _private prototype_ `void ExecuteDefaultAction();` — Run the default action
- L121 _private prototype_ `void PostExecutionCleanup();` — Handles notifying the editor if the recent command mucked with the selection set

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API BLUTILITY_API`
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FForEachActorIteratorSignature, class AActor*, Actor, int32, Index );`
- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FForEachActorIteratorSignature, class AActor*, Actor, int32, Index );`
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FForEachAssetIteratorSignature, class UObject*, Asset, int32, Index );`
- L29 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FForEachAssetIteratorSignature, class UObject*, Asset, int32, Index );`

### `Source/Editor/Blutility/Classes/PlacedEditorUtilityBase.h` (Public)


#### class `ADEPRECATED_PlacedEditorUtilityBase`  
`class ADEPRECATED_PlacedEditorUtilityBase : public AActor`  
_L27-83_
- reflection: `UCLASS(MinimalAPI, Abstract, hideCategories=(Object, Actor), Deprecated)`
- inherits: `AActor`
- L32 _private member_ `FString HelpText;` — `UPROPERTY(Category=Config, EditDefaultsOnly, BlueprintReadWrite)`
- L35 _private prototype_ `virtual void TickActor(float DeltaSeconds, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;` — AActor interface
- L36 _private function_ `virtual bool ShouldTickIfViewportsOnly() const override`
- L43 _private prototype_ `TArray<AActor*> GetSelectionSet();` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Returns the current selection set in the editor.  Note that for non-editor builds, this will return an empty array
- L53 _private prototype_ `bool GetLevelViewportCameraInfo(FVector& CameraLocation, FRotator& CameraRotation);` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Gets information about the camera position for the primary level editor viewport.  In non-editor builds, these will be zeroed @param	CameraLocation	(out) Current location of the level editing viewport camera, or zero if none found @param	CameraRotation	(out) Current rotation of the level editing viewport camera, or zero if none found @return	Whether or not we were able to get a camera for a level editing viewport
- L62 _private prototype_ `void SetLevelViewportCameraInfo(FVector CameraLocation, FRotator CameraRotation);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Sets information about the camera position for the primary level editor viewport. @param	CameraLocation	Location the camera will be moved to. @param	CameraRotation	Rotation the camera will be set to.
- L66 _private prototype_ `void ClearActorSelectionSet();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Remove all actors from the selection set
- L70 _private prototype_ `void SelectNothing();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Selects nothing in the editor (another way to clear the selection)
- L74 _private prototype_ `void SetActorSelectionState(AActor* Actor, bool bShouldBeSelected);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Set the selection state for the selected actor
- L82 _private prototype_ `AActor* GetActorReference(FString PathToActor);` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Attempts to find the actor specified by PathToActor in the current editor world @param	PathToActor	The path to the actor (e.g. PersistentLevel.PlayerStart) @return	A reference to the actor, or none if it wasn't found

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Private/BlutilityContentBrowserExtensions.h` (Private)


#### class `FBlutilityContentBrowserExtensions`  
`class FBlutilityContentBrowserExtensions`  
_L6-12_
- desc: Integrate Blutility actions associated with existing engine types (e.g., Texture2D) into the content browser
- L9 _public prototype_ `static void InstallHooks();`
- L10 _public prototype_ `static void RegisterMenus();`
- L11 _public prototype_ `static void RemoveHooks();`

### `Source/Editor/Blutility/Private/BlutilityLevelEditorExtensions.h` (Private)


#### class `FBlutilityLevelEditorExtensions`  
`class FBlutilityLevelEditorExtensions`  
_L6-12_
- desc: Integrate Blutility actions associated with level editor functionality (e.g. Actor editing)
- L9 _public prototype_ `static void InstallHooks();`
- L10 _public prototype_ `static void RegisterMenus();`
- L11 _public prototype_ `static void RemoveHooks();`

### `Source/Editor/Blutility/Private/BlutilityUMGEditorExtensions.h` (Private)


#### class `FBlutilityUMGEditorExtensions`  
`class FBlutilityUMGEditorExtensions`  
_L6-11_
- desc: Integrate Blutility actions associated with UMG editor functionality (e.g. Run / Stop Utility Widget)
- L9 _public prototype_ `static void InstallHooks();`
- L10 _public prototype_ `static void RemoveHooks();`

### `Source/Editor/Blutility/Private/EditorFunctionLibrary.h` (Private)


#### class `UEditorFunctionLibrary`  
`class UEditorFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-16_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of static functions that can use the editor APIs

### `Source/Editor/Blutility/Private/EditorUtilityCommon.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorUtilityBlueprint, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorUtilityBlueprint, Log, All);`

### `Source/Editor/Blutility/Private/EditorUtilityWidgetSettingsCustomization.h` (Private)


#### class `FEditorUtilityWidgetSettingsCustomization`  
`class FEditorUtilityWidgetSettingsCustomization : public IDetailCustomization`  
_L13-29_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `FEditorUtilityWidgetSettingsCustomization() = default;`
- L17 _public prototype_ `virtual ~FEditorUtilityWidgetSettingsCustomization() = default;`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Source/Editor/Blutility/Private/SEditorUtilityDialog.h` (Private)


#### class `SEditorUtilityDialog`  
`class SEditorUtilityDialog : public SWindow`  
_L33-105_
- inherits: `SWindow`
- desc: A modal (or non-modal) dialog window that hosts an Editor Utility Widget. Modeled after SCustomDialog but specialized for EUW content. Auto-generates a standard button bar from EAppMsgType and returns EAppReturnType results.
- L36 _public function_ `SLATE_BEGIN_ARGS(SEditorUtilityDialog) : _ButtonLayout(EAppMsgType::OkCancel) , _ClientSize(FVector2D::ZeroVector)`
- L40 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(EAppMsgType::Type, ButtonLayout) SLATE_ARGUMENT(FVector2D, ClientSize) SLATE_END_ARGS() virtual ~SEditorUtilityDialog() override;`
- L47 _public prototype_ `void Construct(const FArguments& InArgs);`
- L55 _public prototype_ `void SetContent(UEditorUtilityDialogWidget* InWidget);` — Host the given widget in this dialog. Safe to call multiple times: tears down any prior hosted widget, installs the new one, wires ownership, and (re)subscribes to the widget's Blueprint compile delegate so the dialog rebuilds its content when the user recompiles the widget Blueprint.
- L57 _public prototype_ `EAppReturnType::Type ShowModal();`
- L58 _public prototype_ `void Show(FOnEditorUtilityDialogSlateClosedNative OnClosed);`
- L59 _public prototype_ `void CloseWithResult(EAppReturnType::Type Result);`
- L60 _public function_ `EAppReturnType::Type GetResult() const`
- L63 _public function_ `UEditorUtilityDialogWidget* GetHostedWidget() const` — Current hosted widget, or nullptr. After a Blueprint recompile this returns the rebuilt instance.
- L66 _public function_ `FOnEditorUtilityDialogWidgetRebuilt& GetOnWidgetRebuilt()` — Fires after the hosted widget has been rebuilt due to a Blueprint recompile.
- L73 _public prototype_ `static UEditorUtilityDialogWidget* CreateHostedWidget(TSubclassOf<UEditorUtilityDialogWidget> WidgetClass);` — Create a dialog widget instance suitable for hosting in an SEditorUtilityDialog. Single source of truth for world resolution, CreateWidget, RF_Transient flagging, and error logging. Returns nullptr and logs on failure.
- L75 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L78 _private prototype_ `TSharedRef<SWidget> CreateButtonBar(EAppMsgType::Type MsgType);`
- L79 _private prototype_ `FReply OnButtonClicked(EAppReturnType::Type Result);`
- L80 _private prototype_ `void HandleButtonResult(EAppReturnType::Type Result);`
- L81 _private prototype_ `void HandleWindowClosed(const TSharedRef<SWindow>& ClosedWindow);`
- L82 _private prototype_ `bool CanExecuteHotkey() const;`
- L83 _private prototype_ `static bool IsPositiveResult(EAppReturnType::Type Result);`
- L86 _private prototype_ `void SubscribeToBlueprintCompile(UEditorUtilityDialogWidget* ForWidget);` — Subscribe to the hosted widget's UBlueprint::OnCompiled so we can rebuild on recompile. Idempotent.
- L89 _private prototype_ `void UnsubscribeFromBlueprintCompile();` — Unsubscribe from the currently-watched UBlueprint's OnCompiled delegate, if any.
- L92 _private prototype_ `void HandleHostedBlueprintCompiled(UBlueprint* RecompiledBlueprint);` — Rebuild-on-compile handler. Replaces the hosted widget with a fresh instance of the recompiled class.
- L94 _private member_ `EAppReturnType::Type LastPressedButton = EAppReturnType::Cancel;`
- L95 _private member_ `EAppReturnType::Type CancelResult = EAppReturnType::Cancel;`
- L96 _private member_ `bool bIsClosing = false;`
- L97 _private member_ `TStrongObjectPtr<UEditorUtilityDialogWidget> HostedWidget;`
- L98 _private member_ `TSharedPtr<SVerticalBox> ContentBox;`
- L99 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L100 _private member_ `FOnEditorUtilityDialogSlateClosedNative OnClosedDelegate;`
- L102 _private member_ `TWeakObjectPtr<UBlueprint> WatchedBlueprint;`
- L103 _private member_ `FDelegateHandle OnBlueprintCompiledHandle;`
- L104 _private member_ `FOnEditorUtilityDialogWidgetRebuilt OnWidgetRebuiltDelegate;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEditorUtilityDialogSlateClosedNative, EAppReturnType::Type );` — Delegate fired when an SEditorUtilityDialog is closed (used by the non-modal Show path).
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnEditorUtilityDialogSlateClosedNative, EAppReturnType::Type );` — Delegate fired when an SEditorUtilityDialog is closed (used by the non-modal Show path).
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityDialogWidgetRebuilt, UEditorUtilityDialogWidget* );` — Multicast delegate fired when the hosted widget is rebuilt after a Blueprint recompile. Callers that cached the widget pointer should refresh it. Also fired with nullptr when the dialog cancels because the recompile produced no usable class, so listeners can drop their stale reference rather than report it back to consumers.
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityDialogWidgetRebuilt, UEditorUtilityDialogWidget* );` — Multicast delegate fired when the hosted widget is rebuilt after a Blueprint recompile. Callers that cached the widget pointer should refresh it. Also fired with nullptr when the dialog cancels because the recompile produced no usable class, so listeners can drop their stale reference rather than report it back to consumers.

### `Source/Editor/Blutility/Public/AsyncCaptureScene.h` (Public)


#### class `UAsyncCaptureScene`  
`class UAsyncCaptureScene : public UBlueprintAsyncActionBase`  
_L29-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L34 _public prototype_ `UAsyncCaptureScene();`
- L37 _public prototype_ `static UAsyncCaptureScene* CaptureSceneAsync(UCameraComponent* ViewCamera, TSubclassOf<ASceneCapture2D> SceneCaptureClass, int ResX, int ResY);` — `UFUNCTION(BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ))`
- L40 _public prototype_ `static UAsyncCaptureScene* CaptureSceneWithWarmupAsync(UCameraComponent* ViewCamera, TSubclassOf<ASceneCapture2D> SceneCaptureClass, int ResX, int ResY, int WarmUpFrames);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))`
- L42 _public prototype_ `virtual void Activate() override;`
- L46 _public member_ `FOnAsyncCaptureSceneComplete Complete;` — `UPROPERTY(BlueprintAssignable)`
- L50 _private prototype_ `void NotifyComplete(UTextureRenderTarget2D* InTexture);`
- L51 _private prototype_ `void Start(UCameraComponent* ViewCamera, TSubclassOf<ASceneCapture2D> SceneCaptureClass, int ResX, int ResY, int InWarmUpFrames);`
- L52 _private prototype_ `void FinishLoadingBeforeScreenshot();`
- L56 _private member_ `TObjectPtr<ASceneCapture2D> SceneCapture;` — `UPROPERTY()`
- L59 _private member_ `TObjectPtr<UTextureRenderTarget2D> SceneCaptureRT;` — `UPROPERTY()`
- L61 _private member_ `int32 WarmUpFrames;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAsyncCaptureSceneComplete, UTextureRenderTarget2D*, Texture);`
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAsyncCaptureSceneComplete, UTextureRenderTarget2D*, Texture);`

### `Source/Editor/Blutility/Public/AsyncImageExport.h` (Public)


#### class `UAsyncImageExport`  
`class UAsyncImageExport : public UBlueprintAsyncActionBase`  
_L29-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L34 _public prototype_ `UAsyncImageExport();`
- L37 _public prototype_ `static UAsyncImageExport* ExportImageAsync(UTexture* Texture, const FString& OutputFile, int Quality = 100);` — `UFUNCTION(BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ))`
- L39 _public prototype_ `virtual void Activate() override;`
- L43 _public member_ `FOnExportImageAsyncComplete Complete;` — `UPROPERTY(BlueprintAssignable)`
- L47 _private prototype_ `void NotifyComplete(bool bSuccess);`
- L48 _private prototype_ `void Start(UTexture* Texture, const FString& OutputFile);`
- L49 _private prototype_ `void ReadPixelsFromRT(UTextureRenderTarget2D* InRT, TArray<FColor>* OutPixels);`
- L50 _private prototype_ `void ExportImage(TArray<FColor>&& RawPixels, FIntPoint ImageSize);`
- L54 _private member_ `TObjectPtr<UTexture> TextureToExport;` — `UPROPERTY()`
- L57 _private member_ `int32 Quality;` — `UPROPERTY()`
- L60 _private member_ `FString TargetFile;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExportImageAsyncComplete, bool, bSuccess);`
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExportImageAsyncComplete, bool, bSuccess);`

### `Source/Editor/Blutility/Public/AsyncRegisterAndExecuteTask.h` (Public)


#### class `UAsyncRegisterAndExecuteTask`  
`class UAsyncRegisterAndExecuteTask : public UBlueprintAsyncActionBase`  
_L17-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L22 _public prototype_ `UAsyncRegisterAndExecuteTask();`
- L25 _public prototype_ `static UAsyncRegisterAndExecuteTask* RegisterAndExecuteTask(UEditorUtilityTask* Task, UEditorUtilityTask* OptionalParentTask = nullptr);` — `UFUNCTION(BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ))`
- L30 _public member_ `FOnEditorUtilityTaskDynamicDelegate OnFinished;` — `UPROPERTY(BlueprintAssignable)`
- L34 _public prototype_ `void Start(UEditorUtilityTask* Task, UEditorUtilityTask* OptionalParentTask);`
- L38 _private prototype_ `void HandleFinished(UEditorUtilityTask* Task);`

### `Source/Editor/Blutility/Public/BlutilityMenuExtensions.h` (Public)


#### class `FBlutilityMenuExtensions`  
`class FBlutilityMenuExtensions`  
_L32-109_
- desc: Blutility Menu extension helpers
- L36 _public prototype_ `static void GetBlutilityClasses(TArray<FAssetData>& OutAssets, FTopLevelAssetPath InClassName);` — Helper function to get all Blutility classes derived from the specified class name
- L39 _public prototype_ `static void CreateActorBlutilityActionsMenu(FToolMenuSection& InSection, TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>> Utils, const TArray<AActor*> SelectedSupportedActors);` — Helper function that populates a menu based on the exposed functions in a set of Blutility objects
- L40 _public prototype_ `static void CreateAssetBlutilityActionsMenu(FToolMenuSection& InSection, TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>> Utils, const TArray<FAssetData> SelectedSupportedAssets);`
- L60 _public prototype_ `static void CreateObjectBlutilityActionsMenu( FMenuBuilder& MenuBuilder, const FMenuParams& MenuParams, const FObjectActionParams& ObjectActionParams );` — Helper function that populates a menu based on the exposed functions in a set of Blutility objects
- L102 _protected prototype_ `template<typename SelectionType> static void CreateBlutilityActionsMenu(FMenuBuilder& MenuBuilder, TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>> Utils, const FText& MenuLabel, const FText& MenuToolTip, TFunction<bool(const FProperty* Property)> IsValidPropertyType, const TArray<SelectionType> Selection, const FName& IconName = "Gra`
- L104 _protected prototype_ `template<typename SelectionType> static void CreateBlutilityActionsMenu(FToolMenuSection& InSection, TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>> Utils, const FName& MenuName, const FText& MenuLabel, const FText& MenuToolTip, TFunction<bool(const FProperty* Property)> IsValidPropertyType, const TArray<SelectionType> Selection, const FName& IconName = "Gra`
- L106 _protected prototype_ `template<typename SelectionType> static void CreateBlulityActionsSection(FMenuBuilder& InMenuBuilder, const FObjectActionParams& InObjectActionParams);`
- L107 _protected prototype_ `static void OpenEditorForUtility(const FFunctionAndUtil& FunctionAndUtil);`
- L108 _protected prototype_ `static void ExtractFunctions(const TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>>& Utils, TMap<FString, TArray<FFunctionAndUtil>>& OutCategoryFunctions);`

#### struct `FBlutilityMenuExtensions::FMenuParams`  
`struct FMenuParams`  
_L43-49_
- desc: Structure that defines parameters related to the menu passed into the CreateObjectBlutilityActionsMenu function.
- L45 _public member_ `FText Label;`
- L46 _public member_ `FText ToolTip;`
- L47 _public member_ `FName IconName = "Gr`
- L48 _public member_ `bool bAsSubMenu = true;`

#### struct `FBlutilityMenuExtensions::FObjectActionParams`  
`struct FObjectActionParams`  
_L52-57_
- desc: Structure that defines the parameters related to actions and the objects to act on passed into the CreateObjectBlutilityActionsMenu function.
- L54 _public member_ `TArray<UObject*> Objects;`
- L55 _public member_ `TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>> Utils;`
- L56 _public function_ `TFunction<bool(const FProperty* Property)> IsValidPropertyFunc = [](const FProperty*)`
- L56 _public member_ `TFunction<bool(const FProperty* Property)> IsValidPropertyFunc = [](const FProperty*){ return true; };`

#### struct `FBlutilityMenuExtensions::FFunctionAndUtil`  
`struct FFunctionAndUtil`  
_L68-98_
- desc: Helper struct to track the util to call a function on
- L70 _public function_ `FFunctionAndUtil(const FBlutilityFunctionData& InFunctionData, const TSharedRef<FAssetActionUtilityPrototype>& InUtil, TSet<int32>& InSelection) : FunctionData(InFunctionData) , Util(InUtil) , SelectionIndices(InSelection)`
- L76 _public function_ `bool operator==(const FFunctionAndUtil& InFunction) const`
- L81 _public function_ `UFunction* GetFunction() const`
- L94 _public member_ `FBlutilityFunctionData FunctionData;`
- L95 _public member_ `TSharedRef<FAssetActionUtilityPrototype> Util;`
- L97 _public member_ `TSet<int32> SelectionIndices;` — Indices to original object selection array which are supported by this utility

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Public/EditorUtilityAssetPrototype.h` (Public)


#### struct `FBlutilityFunctionData`  
`struct FBlutilityFunctionData`  
_L13-42_
- reflection: `USTRUCT()`
- L19 _public member_ `TSoftClassPtr<UClass> Class;` — `UPROPERTY()`
- L22 _public member_ `FName Name;` — `UPROPERTY()`
- L25 _public member_ `FText NameText;` — `UPROPERTY()`
- L28 _public member_ `FString Category;` — `UPROPERTY()`
- L31 _public member_ `FText TooltipText;` — `UPROPERTY()`
- L33 _public function_ `bool operator !=(const FBlutilityFunctionData& Other) const`
- L38 _public function_ `bool operator == (const FBlutilityFunctionData& Other) const`

#### class `FAssetActionUtilityPrototype`  
`class FAssetActionUtilityPrototype`  
_L56-93_
- L59 _public function_ `FAssetActionUtilityPrototype(const FAssetData& SourceAsset) : UtilityBlueprintAsset(SourceAsset)`
- L64 _public prototype_ `UObject* LoadUtilityAsset() const;`
- L66 _public prototype_ `bool IsLatestVersion() const;`
- L67 _public prototype_ `bool AreSupportedClassesForBlueprints() const;`
- L68 _public prototype_ `TArray<TSoftClassPtr<UObject>> GetSupportedClasses() const;`
- L69 _public prototype_ `TArray<FAssetActionSupportCondition> GetAssetActionSupportConditions() const;`
- L70 _public prototype_ `TArray<FBlutilityFunctionData> GetCallableFunctions() const;`
- L72 _public function_ `const FAssetData& GetUtilityBlueprintAsset() const`
- L74 _public function_ `bool operator !=(const FAssetActionUtilityPrototype& Other) const`
- L79 _public function_ `bool operator == (const FAssetActionUtilityPrototype& Other) const`
- L85 _public prototype_ `static void AddTagsFor_Version(FAssetRegistryTagsContext Context);`
- L86 _public prototype_ `static void AddTagsFor_SupportedClasses(const TArray<TSoftClassPtr<UObject>>& SupportedClasses, FAssetRegistryTagsContext Context);`
- L87 _public prototype_ `static void AddTagsFor_SupportedConditions(const TArray<FAssetActionSupportCondition>& SupportedConditions, FAssetRegistryTagsContext Context);`
- L88 _public prototype_ `static void AddTagsFor_IsActionForBlueprints(bool IsActionForBlueprints, FAssetRegistryTagsContext Context);`
- L89 _public prototype_ `static void AddTagsFor_CallableFunctions(const UObject* FunctionsSource, FAssetRegistryTagsContext Context);`
- L92 _private member_ `FAssetData UtilityBlueprintAsset;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace AssetActionUtilityTags`
- L46 _externvar_ `extern const FName BlutilityTagVersion;` (scope `AssetActionUtilityTags`)
- L47 _externvar_ `extern const FName SupportedClasses;` (scope `AssetActionUtilityTags`)
- L48 _externvar_ `extern const FName IsActionForBlueprint;` (scope `AssetActionUtilityTags`)
- L49 _externvar_ `extern const FName CallableFunctions;` (scope `AssetActionUtilityTags`)
- L51 _externvar_ `extern const int32 TagVersion;` (scope `AssetActionUtilityTags`)
- L54 _macro_ `#define UE_API BLUTILITY_API`
- L95 _function_ `FORCEINLINE uint32 GetTypeHash(const FAssetActionUtilityPrototype& ExtensionAsset)`

### `Source/Editor/Blutility/Public/EditorUtilityDialogLibrary.h` (Public)


#### class `UEditorUtilityDialogLibrary`  
`class UEditorUtilityDialogLibrary : public UBlueprintFunctionLibrary`  
_L22-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint Function Library for creating modal and non-modal dialogs that contain Editor Utility Widgets.
- L29 _public prototype_ `static FEditorUtilityDialogResult ShowModalEditorUtilityDialog(TSubclassOf<UEditorUtilityDialogWidget> WidgetClass, FText Title, EAppMsgType::Type ButtonLayout = EAppMsgType::OkCancel, FVector2D Size = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Editor Utility|Dialog")` — Creates an Editor Utility Dialog Widget and shows it as a modal window. Blocks until dismissed.
- L33 _public prototype_ `static UEditorUtilityDialogWidget* ShowEditorUtilityDialog(TSubclassOf<UEditorUtilityDialogWidget> WidgetClass, const FOnEditorUtilityDialogClosed& OnClosed, FText Title = FText::GetEmpty(), EAppMsgType::Type ButtonLayout = EAppMsgType::OkCancel, FVector2D Size = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Editor Utility|Dialog", meta = (AutoCreateRefTerm = "OnClosed", DeterminesOutputType = "WidgetClass"))` — Creates an Editor Utility Dialog Widget as a non-modal window. Returns immediately. OnClosed fires when dismissed.
- L37 _public prototype_ `static UEditorUtilityDialogWidget* CreateEditorUtilityDialogWidget(TSubclassOf<UEditorUtilityDialogWidget> WidgetClass);` — `UFUNCTION(BlueprintCallable, Category = "Editor Utility|Dialog", meta = (DeterminesOutputType = "WidgetClass"))` — Creates and initializes a dialog widget without showing it. Set data on it, then pass to Show Modal/Non-Modal (Instance).
- L41 _public prototype_ `static FEditorUtilityDialogResult ShowModalEditorUtilityDialogInstance(UEditorUtilityDialogWidget* WidgetInstance, FText Title, EAppMsgType::Type ButtonLayout = EAppMsgType::OkCancel, FVector2D Size = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Editor Utility|Dialog")` — Shows a pre-constructed Editor Utility Dialog Widget as a modal window.
- L45 _public prototype_ `static void ShowEditorUtilityDialogInstance(UEditorUtilityDialogWidget* WidgetInstance, const FOnEditorUtilityDialogClosed& OnClosed, FText Title = FText::GetEmpty(), EAppMsgType::Type ButtonLayout = EAppMsgType::OkCancel, FVector2D Size = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Editor Utility|Dialog", meta = (AutoCreateRefTerm = "OnClosed"))` — Shows a pre-constructed Editor Utility Dialog Widget as a non-modal window.
- L48 _private prototype_ `static TPair<UEditorUtilityDialogWidget*, TSharedPtr<SEditorUtilityDialog>> CreateDialogInternal(TSubclassOf<UEditorUtilityDialogWidget> WidgetClass, const FText& Title, EAppMsgType::Type ButtonLayout, const FVector2D& Size);`
- L50 _private prototype_ `static TSharedPtr<SEditorUtilityDialog> WrapWidgetInDialog(UEditorUtilityDialogWidget* Widget, const FText& Title, EAppMsgType::Type ButtonLayout, const FVector2D& Size);`
- L53 _private prototype_ `static void BindNonModalCloseCallback(SEditorUtilityDialog& Dialog, UEditorUtilityDialogWidget* InitialWidget, const FOnEditorUtilityDialogClosed& OnClosed);` — Show the dialog non-modally and route the close callback through a holder that tracks rebuilds.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Public/EditorUtilityDialogResult.h` (Public)


#### struct `FEditorUtilityDialogResult`  
`struct FEditorUtilityDialogResult`  
_L25-36_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- desc: Result returned by ShowModalEditorUtilityDialog. Contains the button the user pressed and a reference to the widget instance so the caller can read back any data the user entered.
- L31 _public member_ `TEnumAsByte<EAppReturnType::Type> ReturnType = EAppReturnType::Cancel;` — `UPROPERTY(BlueprintReadOnly, Category = "Dialog Result")` — Which button the user pressed to close the dialog (Ok, Cancel, Yes, No, etc.).
- L35 _public member_ `TObjectPtr<UEditorUtilityDialogWidget> WidgetInstance = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Dialog Result")` — The widget instance shown in the dialog. Cast to your subclass to read back user-entered data.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnEditorUtilityDialogClosed, EAppReturnType::Type, Result, UEditorUtilityDialogWidget*, WidgetInstance);` — Delegate fired when an async (non-modal) Editor Utility Dialog is closed.
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnEditorUtilityDialogClosed, EAppReturnType::Type, Result, UEditorUtilityDialogWidget*, WidgetInstance);` — Delegate fired when an async (non-modal) Editor Utility Dialog is closed.

### `Source/Editor/Blutility/Public/EditorUtilityDialogWidget.h` (Public)


#### class `UEditorUtilityDialogWidget`  
`class UEditorUtilityDialogWidget : public UEditorUtilityWidget`  
_L26-69_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `UEditorUtilityWidget`
- desc: Base class for Editor Utility Widgets that are designed to be shown in modal or non-modal dialog windows. Subclass this in Blueprint to create custom dialog content. Unlike regular Editor Utility Widgets (which live in dockable tabs), dialog widgets are shown in standalone windows with a standard button bar (OK, Cancel, Yes/No, etc.). The caller receives this widget instance after the dialog closes, so you can expose UPROPERTY fields that the caller reads back to get user-entered data.
- L33 _public member_ `FText DialogTitle;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog Settings")` — The title shown in the modal window's title bar. Can be overridden by the caller when showing the dialog.
- L37 _public member_ `FVector2D DesiredDialogSize = FVector2D::ZeroVector;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog Settings")` — Default window size in pixels (Width, Height). Set to (0, 0) to auto-size to content.
- L41 _public member_ `TEnumAsByte<EAppMsgType::Type> ButtonLayout = EAppMsgType::OkCancel;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog Settings")` — Which standard buttons appear at the bottom of the dialog (Ok, OkCancel, YesNo, etc.).
- L45 _public prototype_ `void OnDialogOpened();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Dialog|Events")` — Called after the widget is created, before the dialog becomes visible. Initialize state here.
- L49 _public prototype_ `void OnDialogConfirmed();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Dialog|Events")` — Called when the user presses a positive button (OK, Yes, etc.). Fires before close.
- L53 _public prototype_ `void OnDialogCancelled();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Dialog|Events")` — Called when the user presses Cancel, No, or closes via the X button. Fires before close.
- L57 _public prototype_ `void OnDialogButtonPressed(EAppReturnType::Type Result);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Dialog|Events")` — Called for ANY button press. Catch-all alternative to OnDialogConfirmed/OnDialogCancelled.
- L61 _public prototype_ `void CloseDialog(EAppReturnType::Type Result);` — `UFUNCTION(BlueprintCallable, Category = "Dialog")` — Programmatically close this dialog with a specific result.
- L64 _public prototype_ `void SetOwningDialog(TSharedPtr<SEditorUtilityDialog> InDialog);` — Set by the dialog system when the widget is hosted in an SEditorUtilityDialog.
- L68 _private member_ `TWeakPtr<SEditorUtilityDialog> OwningDialog;` — Weak reference to the Slate dialog window hosting this widget. Used by CloseDialog().

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Public/EditorUtilityLibrary.h` (Public)


#### enum `ECastToWidgetBlueprintCases`  
`enum class ECastToWidgetBlueprintCases : uint8`  
_L34-38_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `CastSucceeded`
- L37 _public enumerator_ `CastFailed`

#### class `UEditorUtilityBlueprintAsyncActionBase`  
`class UEditorUtilityBlueprintAsyncActionBase : public UBlueprintAsyncActionBase`  
_L41-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintAsyncActionBase`
- L46 _public prototype_ `virtual void RegisterWithGameInstance(const UObject* WorldContextObject) override;`
- L47 _public prototype_ `virtual void SetReadyToDestroy() override;`

#### class `UAsyncEditorDelay`  
`class UAsyncEditorDelay : public UEditorUtilityBlueprintAsyncActionBase`  
_L53-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorUtilityBlueprintAsyncActionBase`
- L61 _public prototype_ `static UAsyncEditorDelay* AsyncEditorDelay(float Seconds, int32 MinimumFrames = 30);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))`
- L68 _public member_ `FAsyncDelayComplete Complete;` — `UPROPERTY(BlueprintAssignable)`
- L72 _public prototype_ `void Start(float InMinimumSeconds, int32 InMinimumFrames);`
- L76 _private prototype_ `bool HandleComplete(float DeltaTime);`
- L78 _private member_ `uint64 EndFrame = 0;`
- L79 _private member_ `double EndTime = 0;`

#### class `UAsyncEditorWaitForGameWorld`  
`class UAsyncEditorWaitForGameWorld : public UEditorUtilityBlueprintAsyncActionBase`  
_L85-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorUtilityBlueprintAsyncActionBase`
- L93 _public prototype_ `static UAsyncEditorWaitForGameWorld* AsyncWaitForGameWorld(int32 Index = 0, bool Server = false);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))`
- L100 _public member_ `FAsyncEditorWaitForGameWorldEvent Complete;` — `UPROPERTY(BlueprintAssignable)`
- L104 _public prototype_ `void Start(int32 Index, bool Server);`
- L108 _private prototype_ `bool OnTick(float DeltaTime);`
- L110 _private member_ `int32 Index;`
- L111 _private member_ `bool Server;`

#### class `UAsyncEditorOpenMapAndFocusActor`  
`class UAsyncEditorOpenMapAndFocusActor : public UEditorUtilityBlueprintAsyncActionBase`  
_L115-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorUtilityBlueprintAsyncActionBase`
- L123 _public prototype_ `static UAsyncEditorOpenMapAndFocusActor* AsyncEditorOpenMapAndFocusActor(FSoftObjectPath Map, FString FocusActorName);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))`
- L130 _public member_ `FAsyncDelayComplete Complete;` — `UPROPERTY(BlueprintAssignable)`
- L134 _public prototype_ `void Start(FSoftObjectPath InMap, FString InFocusActorName);`
- L138 _private prototype_ `bool OnTick(float DeltaTime);`
- L140 _private member_ `FSoftObjectPath Map;`
- L141 _private member_ `FString FocusActorName;`

#### class `UEditorUtilityLibrary`  
`class UEditorUtilityLibrary : public UBlueprintFunctionLibrary`  
_L147-238_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Expose editor utility functions to Blutilities
- L155 _public prototype_ `static TArray<AActor*> GetSelectionSet();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L158 _public prototype_ `static void GetSelectionBounds(FVector& Origin, FVector& BoxExtent, float& SphereRadius);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L162 _public prototype_ `static TArray<UObject*> GetSelectedAssets();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Gets the set of currently selected assets
- L165 _public prototype_ `static TArray<UObject*> GetSelectedAssetsOfClass(UClass* AssetClass);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L169 _public prototype_ `static TArray<UClass*> GetSelectedBlueprintClasses();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Gets the set of currently selected classes
- L173 _public prototype_ `static TArray<FAssetData> GetSelectedAssetData();` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Gets the set of currently selected asset data
- L177 _public prototype_ `static void RenameAsset(UObject* Asset, const FString& NewName);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Renames an asset (cannot move folders)
- L185 _public prototype_ `AActor* GetActorReference(FString PathToActor);` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Attempts to find the actor specified by PathToActor in the current editor world @param	PathToActor	The path to the actor (e.g. PersistentLevel.PlayerStart) @return	A reference to the actor, or none if it wasn't found
- L194 _public prototype_ `static bool GetCurrentContentBrowserPath(FString& OutPath);` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Attempts to get the path for the active content browser, returns false if there is no active content browser or if it was a virtual path @param	OutPath	The returned path if successfully found @return	Whether a path was successfully returned
- L198 _public prototype_ `static FContentBrowserItemPath GetCurrentContentBrowserItemPath();` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Gets the current content browser path if one is open, whether it is internal or virtual.
- L202 _public prototype_ `static TArray<FString> GetSelectedFolderPaths();` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Gets the path to the currently selected folder in the content browser
- L206 _public prototype_ `static TArray<FString> GetSelectedPathViewFolderPaths();` — `UFUNCTION(BlueprintPure, Category = "Development|Editor")` — Returns the folders that are selected in the path view for the content browser
- L213 _public prototype_ `static void SyncBrowserToFolders(const TArray<FString>& FolderList);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Content Browser")` — Sync the Content Browser to the given folder(s) @param	FolderList	The list of folders to sync to in the Content Browser
- L216 _public prototype_ `static void ConvertToEditorUtilityWidget(class UWidgetBlueprint* WidgetBP);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Content Browser")`
- L219 _public prototype_ `static void CastToWidgetBlueprint(UObject* Object, ECastToWidgetBlueprintCases& Branches, UWidgetBlueprint*& AsWidgetBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Widget Blueprint", Meta = (ExpandEnumAsExecs = "Branches"))`
- L223 _public prototype_ `static UWidget* FindSourceWidgetByName(UWidgetBlueprint* WidgetBlueprint, FName WidgetName);` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Editor Scripting | Widget Blueprint")` — Searches the blueprint's widget hierarchy for a widget with the specified name
- L236 _public prototype_ `static UWidget* AddSourceWidget(UWidgetBlueprint* WidgetBlueprint, TSubclassOf<UWidget> WidgetClass, FName WidgetName, FName WidgetParentName);` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Editor Scripting | Widget Blueprint")` — Create a new widget and add to the specific widget blueprint's widget tree @param WidgetBlueprint The widget blueprint to add a widget to @param WidgetClass The widget class to add to the widget blueprint @param WidgetName The name to give the new widget @param WidgetParentName The name of the existing widget that will hold the new widget. Must be an existing Panel Widget or none of if the widget tree is empty and the new widget will become the RootWidget. @return The widget that was created and added to the widget blueprint

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API BLUTILITY_API`
- L50 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncDelayComplete);`
- L50 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncDelayComplete);`
- L82 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncEditorWaitForGameWorldEvent, UWorld*, World);`
- L82 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncEditorWaitForGameWorldEvent, UWorld*, World);`

### `Source/Editor/Blutility/Public/EditorUtilitySubsystem.h` (Public)


#### class `UEditorUtilitySubsystem`  
`class UEditorUtilitySubsystem : public UEditorSubsystem`  
_L47-215_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UEditorSubsystem`
- L52 _public prototype_ `UEditorUtilitySubsystem();`
- L54 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection);`
- L55 _public prototype_ `virtual void Deinitialize();`
- L57 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L59 _public prototype_ `void MainFrameCreationFinished(TSharedPtr<SWindow> InRootWindow, bool bIsRunningStartupDialog);`
- L60 _public prototype_ `void HandleStartup();`
- L63 _public member_ `TArray<FSoftObjectPath> LoadedUIs;` — `UPROPERTY(config)`
- L66 _public member_ `TArray<FSoftObjectPath> StartupObjects;` — `UPROPERTY(config)`
- L68 _public member_ `TMap<FName, UEditorUtilityWidgetBlueprint*> RegisteredTabs;`
- L69 _public member_ `TMap<FName, UWidgetBlueprintGeneratedClass*> RegisteredTabsByGeneratedClass;`
- L73 _public prototype_ `void ReleaseInstanceOfAsset(UObject* Asset);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Allow startup object to be garbage collected
- L76 _public prototype_ `bool TryRun(UObject* Asset);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L79 _public prototype_ `bool TryRunClass(UClass* ObjectClass);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L82 _public prototype_ `bool CanRun(UObject* Asset) const;` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L85 _public prototype_ `UEditorUtilityWidget* SpawnAndRegisterTabAndGetID(class UEditorUtilityWidgetBlueprint* InBlueprint, FName& NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L88 _public prototype_ `UEditorUtilityWidget* SpawnAndRegisterTab(class UEditorUtilityWidgetBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L91 _public prototype_ `void RegisterTabAndGetID(class UEditorUtilityWidgetBlueprint* InBlueprint, FName& NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L97 _public prototype_ `UEditorUtilityWidget* SpawnAndRegisterTabWithId(class UEditorUtilityWidgetBlueprint* InBlueprint, FName InTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Unlike SpawnAndRegisterTabAndGetID allows spawn tab while providing TabID from Python scripts or BP
- L100 _public prototype_ `UEditorUtilityWidget* SpawnAndRegisterTabAndGetIDGeneratedClass(UWidgetBlueprintGeneratedClass* InGeneratedWidgetBlueprint, FName& NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L103 _public prototype_ `UEditorUtilityWidget* SpawnAndRegisterTabGeneratedClass(UWidgetBlueprintGeneratedClass* InGeneratedWidgetBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L106 _public prototype_ `void RegisterTabAndGetIDGeneratedClass(UWidgetBlueprintGeneratedClass* InGeneratedWidgetBlueprint, FName& NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L112 _public prototype_ `UEditorUtilityWidget* SpawnAndRegisterTabWithIdGeneratedClass(UWidgetBlueprintGeneratedClass* InGeneratedWidgetBlueprint, FName InTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Unlike SpawnAndRegisterTabAndGetID allows spawn tab while providing TabID from Python scripts or BP
- L116 _public prototype_ `bool SpawnRegisteredTabByID(FName NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Given an ID for a tab, try to find a tab spawner that matches, and then spawn a tab. Returns true if it was able to find a matching tab spawner
- L120 _public prototype_ `bool DoesTabExist(FName NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Given an ID for a tab, try to find an existing tab. Returns true if it found a tab.
- L124 _public prototype_ `bool CloseTabByID(FName NewTabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Given an ID for a tab, try to find and close an existing tab. Returns true if it found a tab to close.
- L128 _public prototype_ `bool UnregisterTabByID(FName TabID);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Given an ID for a tab, try to close and unregister a tab that was registered through this subsystem
- L132 _public prototype_ `UEditorUtilityWidget* FindUtilityWidgetFromBlueprint(class UEditorUtilityWidgetBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Given an editor utility widget blueprint, get the widget it creates. This will return a null pointer if the widget is not currently in a tab.
- L136 _public prototype_ `FName GetTabIDFromBlueprint(class UEditorUtilityWidgetBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")` — Given an editor utility widget blueprint, get the TabID for it. This will return None if the widget is not currently in a tab.
- L140 _public prototype_ `void RegisterAndExecuteTask(UEditorUtilityTask* NewTask, UEditorUtilityTask* OptionalParentTask = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Development|Editor")`
- L142 _public prototype_ `void RemoveTaskFromActiveList(UEditorUtilityTask* Task);`
- L144 _public prototype_ `void RegisterReferencedObject(UObject* ObjectToReference);`
- L145 _public prototype_ `void UnregisterReferencedObject(UObject* ObjectToReference);`
- L149 _public member_ `FOnEditorUtilityPIEEvent OnBeginPIE;` — `UPROPERTY(BlueprintAssignable)` — Expose Begin PIE to blueprints.
- L153 _public member_ `FOnEditorUtilityPIEEvent OnEndPIE;` — `UPROPERTY(BlueprintAssignable)` — Expose End PIE to blueprints.
- L156 _protected prototype_ `void HandleStartupAssets();`
- L157 _protected prototype_ `void HandleDynamicStartupAssets(TConstArrayView<FAssetData> InAssets);`
- L159 _protected prototype_ `void OnBlueprintGeneratedClassUnloaded(UBlueprintGeneratedClass* BPGC);`
- L161 _protected function_ `UEditorUtilityTask* GetActiveTask()`
- L163 _protected prototype_ `void StartTask(UEditorUtilityTask* Task);`
- L165 _protected prototype_ `bool Tick(float DeltaTime);`
- L167 _protected prototype_ `void ProcessRunTaskCommands();`
- L169 _protected prototype_ `void RunTaskCommand(const TArray<FString>& Params, UWorld* InWorld, FOutputDevice& Ar);`
- L170 _protected prototype_ `void CancelAllTasksCommand(const TArray<FString>& Params, UWorld* InWorld, FOutputDevice& Ar);`
- L172 _protected prototype_ `UClass* FindClassByName(const FString& RawTargetName);`
- L173 _protected prototype_ `UClass* FindBlueprintClass(const FString& TargetNameRaw);`
- L176 _protected prototype_ `void HandleOnBeginPIE(const bool bIsSimulating);` — Called when Play in Editor begins.
- L179 _protected prototype_ `void HandleOnEndPIE(const bool bIsSimulating);` — Called when Play in Editor stops.
- L181 _protected prototype_ `TSharedRef<SDockTab> SpawnEditorUITabFromGeneratedClass(const FSpawnTabArgs& SpawnTabArgs, UWidgetBlueprintGeneratedClass* InGeneratedWidgetBlueprint);`
- L183 _protected prototype_ `void OnSpawnedFromGeneratedClassTabClosed(TSharedRef<SDockTab> TabBeingClosed);`
- L185 _protected prototype_ `void OnMapChanged(UWorld* World, EMapChangeType MapChangeType);`
- L187 _protected member_ `TMap<TSharedRef<SDockTab>, UEditorUtilityWidget*> SpawnedFromGeneratedClassTabs;`
- L190 _private prototype_ `FName GenerateNewTabID(const UObject* WidgetObject, const FName& OptionalPostfix);`
- L192 _private prototype_ `void ExtendTabContextMenu(FMenuBuilder& InMenuBuilder, FName InTabId);`
- L193 _private prototype_ `void OnBrowseAssetInContentBrowser(FName InTabId);`
- L194 _private prototype_ `bool OnCanBrowseAssetInContentBrowser(FName InTabId);`
- L196 _private member_ `IConsoleObject* RunTaskCommandObject = nullptr;`
- L197 _private member_ `IConsoleObject* CancelAllTasksCommandObject = nullptr;`
- L200 _private member_ `TMap<TObjectPtr<UObject> , TObjectPtr<UObject> > ObjectInstances;` — `UPROPERTY()`
- L202 _private member_ `TQueue< TArray<FString> > RunTaskCommandBuffer;`
- L205 _private member_ `TMap<TObjectPtr<UEditorUtilityTask>, TArray<TObjectPtr<UEditorUtilityTask>>> PendingTasks;` — AddReferencedObjects is used to report these references to GC.
- L208 _private member_ `TArray<TObjectPtr<UEditorUtilityTask>> ActiveTaskStack;` — `UPROPERTY(Transient)`
- L210 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L214 _private member_ `TSet<TObjectPtr<UObject>> ReferencedObjects;` — `UPROPERTY()` — List of objects that are being kept alive by this subsystem.

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API BLUTILITY_API`
- L44 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityPIEEvent, const bool, bIsSimulating);` — Delegate for a PIE event exposed via Editor Utility (begin, end, pause/resume, etc)
- L44 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditorUtilityPIEEvent, const bool, bIsSimulating);` — Delegate for a PIE event exposed via Editor Utility (begin, end, pause/resume, etc)

### `Source/Editor/Blutility/Public/EditorUtilityWidgetProjectSettings.h` (Public)


#### class `UEditorUtilityWidgetProjectSettings`  
`class UEditorUtilityWidgetProjectSettings : public UWidgetEditingProjectSettings`  
_L26-58_
- reflection: `UCLASS(MinimalAPI, config=Editor, defaultconfig)`
- inherits: `UWidgetEditingProjectSettings`
- desc: Implements the settings for Editor Utility Widget Editing Project Settings
- L32 _public prototype_ `virtual FText GetSectionText() const override;`
- L33 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L36 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `FNamePermissionList& GetAllowedEditorUtilityActorActions();` — Get the permission list that controls actor actions
- L41 _public prototype_ `const FNamePermissionList& GetAllowedEditorUtilityActorActions() const;`
- L44 _public prototype_ `FNamePermissionList& GetAllowedEditorUtilityAssetActions();` — Get the permission list that controls asset actions
- L45 _public prototype_ `const FNamePermissionList& GetAllowedEditorUtilityAssetActions() const;`
- L49 _public member_ `bool bSearchGeneratedClassesForScriptedActions = false;` — `UPROPERTY(EditAnywhere, config, Category = Designer)` — Set true to search generated classes for scripted actions.
- L54 _protected member_ `FNamePermissionList AllowedEditorUtilityActorActions;` — EditorUtility actor actions to always consider during context menu creation
- L57 _protected member_ `FNamePermissionList AllowedEditorUtilityAssetActions;` — EditorUtility asset actions to always consider during context menu creation

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BLUTILITY_API`

### `Source/Editor/Blutility/Public/IBlutilityModule.h` (Public)


#### class `IBlutilityModule`  
`class IBlutilityModule : public IModuleInterface`  
_L15-30_
- inherits: `IModuleInterface`
- desc: The public interface of BlutilityModule
- L20 _public prototype_ `virtual bool IsEditorUtilityBlueprint( const UBlueprint* Blueprint ) const = 0;` — Returns if the blueprint is an editor utility blueprint or widget
- L23 _public prototype_ `virtual TSharedPtr<class FWorkspaceItem> GetMenuGroup() const = 0;` — Global Find Results workspace menu item
- L25 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const = 0;`
- L27 _public prototype_ `virtual void AddLoadedScriptUI(class UEditorUtilityWidgetBlueprint* InBlueprint) = 0;`
- L29 _public prototype_ `virtual void RemoveLoadedScriptUI(class UEditorUtilityWidgetBlueprint* InBlueprint) = 0;`

### `Source/Editor/Blutility/Public/IEditorUtilityExtension.h` (Public)


#### class `UEditorUtilityExtension`  
`class UEditorUtilityExtension : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IEditorUtilityExtension`  
`class IEditorUtilityExtension`  
_L17-20_

### `Source/Editor/Blutility/Public/ToolMenuWidget.h` (Public)


#### class `UToolMenuWidget`  
`class UToolMenuWidget : public UWidget`  
_L20-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A base ToolMenu widget that can support Menus and Toolbars. Menus can be modified and added to with Blueprint or Python commands using the ToolMenus system.
- L24 _private prototype_ `UToolMenuWidget(const FObjectInitializer& ObjectInitializer);`
- L31 _public member_ `FString MenuName;` — `UPROPERTY(Category = Config, EditAnywhere, BlueprintReadOnly)` — Name of toolbar for registering with ToolMenus. This has the editor utility widget pre-pended to it to make the FullMenuName.
- L34 _public member_ `EMultiBoxType MenuType;` — `UPROPERTY(Category = Config, EditAnywhere, BlueprintReadOnly)`
- L40 _public prototype_ `virtual void PostInitProperties();`
- L44 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L49 _protected member_ `TSharedRef<SWidget> MyToolMenu = SNullWidget::NullWidget;`
- L55 _protected member_ `FName FullMenuName;` — `UPROPERTY(Category = Config, BlueprintReadOnly, VisibleAnywhere)` — The final usable name that can be retrieved by Python/Blueprint. Use this value when trying to Extend menus.
- L59 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L63 _private prototype_ `void UpdateFullMenuName();`
