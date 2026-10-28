# Plugins / InputEditor

- module root: `Plugins/EnhancedInput/Source/InputEditor`
- headers: 9; symbols: 180
- symbol kinds: class=15, delegate=2, enum=1, enumerator=2, function=24, macro=3, member=35, namespace=2, prototype=92, struct=1, variable=3
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, ContentBrowser, Core, CoreUObject, DetailCustomizations, DeveloperSettings, EditorSubsystem, Engine, GameplayTags, GraphEditor, InputCore, KismetCompiler, PropertyEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl, ToolMenus, UnrealEd
- PublicDependencyModuleNames: EnhancedInput

### `Plugins/EnhancedInput/Source/InputEditor/Private/ActionMappingDetails.h` (Private)


#### struct `ActionMappingDetails::FMappingSet`  
`struct FMappingSet`  
_L25-30_
- L27 _public member_ `const class UInputAction* SharedAction;`
- L28 _public member_ `IDetailGroup* DetailGroup;`
- L29 _public member_ `TArray<TSharedRef<IPropertyHandle>> Mappings;`

#### class `FActionMappingsNodeBuilderEx`  
`class FActionMappingsNodeBuilderEx : public IDetailCustomNodeBuilder, public TSharedFromThis<FActionMappingsNodeBuilderEx>`  
_L33-98_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FActionMappingsNodeBuilderEx>`
- L36 _public prototype_ `FActionMappingsNodeBuilderEx(const TSharedPtr<IPropertyHandle>& InPropertyHandle);`
- L40 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override` — IDetailCustomNodeBuilder interface
- L41 _public function_ `virtual bool RequiresTick() const override`
- L42 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L43 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L44 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L45 _public function_ `virtual bool InitiallyCollapsed() const override`
- L46 _public function_ `virtual FName GetName() const override`
- L48 _public prototype_ `int32 GetNumGroupedMappings() const;`
- L49 _public prototype_ `int32 GetNumMappings() const;`
- L56 _public prototype_ `void ReorderMappings(int32 OriginalIndex, int32 NewIndex, EReorderMode ReorderMode);`
- L58 _private prototype_ `void AddActionMappingButton_OnClick();`
- L59 _private prototype_ `void ClearActionMappingButton_OnClick();`
- L60 _private prototype_ `void OnActionMappingActionChanged(const FAssetData& AssetData, const ActionMappingDetails::FMappingSet MappingSet);`
- L61 _private prototype_ `void AddActionMappingToGroupButton_OnClick(const ActionMappingDetails::FMappingSet MappingSet);`
- L62 _private prototype_ `void RemoveActionMappingGroupButton_OnClick(const ActionMappingDetails::FMappingSet MappingSet);`
- L64 _private prototype_ `bool GroupsRequireRebuild() const;`
- L65 _private prototype_ `void RebuildGroupedMappings();`
- L66 _private function_ `void RebuildChildren()`
- L71 _private prototype_ `void HandleDelayedGroupExpansion();` — Makes sure that groups have their expansion set after any rebuilding
- L74 _private prototype_ `bool CanAddNewActionMapping() const;` — Returns true if the "Adds Action Mapping" button can be pressed
- L77 _private prototype_ `FText GetAddNewActionTooltip() const;` — The tooltip attribute for the "Adds Action Mapping" button
- L83 _private prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString& OldName);` — Called by the asset registry when an asset is renamed. Replaces any references to the old Input Action with the new one
- L87 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L90 _private member_ `TSharedPtr<IPropertyHandle> ActionMappingsPropertyHandle;` — Property handle to associated Action Mappings
- L92 _private member_ `TArray<ActionMappingDetails::FMappingSet> GroupedMappings;`
- L94 _private member_ `TArray<TPair<const UInputAction*, bool>> DelayedGroupExpansionStates;`
- L97 _private member_ `TMap<FName, FName> ActionsBeingRenamed;` — A map of Input Action's that have been renamed. This map is a map of the New Name to the Old Name.

#### enum `FActionMappingsNodeBuilderEx::EReorderMode`  
`enum class EReorderMode : uint8`  
_L51-55_
- L53 _public enumerator_ `Group`
- L54 _public enumerator_ `Single`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ActionMappingDetails`
- L18 _namespace_ `namespace InputConstants` (scope `ActionMappingDetails`)
- L20 _variable_ `const FMargin PropertyPadding(2.0f, 0.0f, 2.0f, 0.0f);` (scope `ActionMappingDetails::InputConstants`)
- L21 _variable_ `const float TextBoxWidth = 250.0f;` (scope `ActionMappingDetails::InputConstants`)
- L22 _variable_ `const float ScaleBoxWidth = 50.0f;` (scope `ActionMappingDetails::InputConstants`)

### `Plugins/EnhancedInput/Source/InputEditor/Private/AssetDefinition_InputAction.h` (Private)


#### class `UAssetDefinition_InputAction`  
`class UAssetDefinition_InputAction : public UAssetDefinitionDefault`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/EnhancedInput/Source/InputEditor/Private/AssetDefinition_InputMappingContext.h` (Private)


#### class `UAssetDefinition_InputMappingContext`  
`class UAssetDefinition_InputMappingContext : public UAssetDefinitionDefault`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/EnhancedInput/Source/InputEditor/Private/EnhancedInputCustomizations.h` (Private)


#### class `FEnhancedActionMappingCustomization`  
`class FEnhancedActionMappingCustomization : public IPropertyTypeCustomization`  
_L14-42_
- inherits: `IPropertyTypeCustomization`
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _public prototype_ `bool DoesTriggerArrayContainCombo() const;` — `UE_DEPRECATED(5.8, "The combo trigger is now deprecated")` — Searches the trigger array of an input action - returns true if any combo input triggers are present
- L31 _private prototype_ `void RemoveMappingButton_OnClick() const;`
- L32 _private prototype_ `void OnTriggersChanged() const;`
- L33 _private prototype_ `void AddInputActionProperties(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder);`
- L34 _private prototype_ `void OnInputActionTriggersChanged() const;`
- L35 _private prototype_ `void OnInputActionModifiersChanged() const;`
- L37 _private member_ `TSharedPtr<IPropertyTypeCustomization> KeyStructInstance;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> MappingPropertyHandle;`
- L39 _private member_ `TSharedPtr<FKeyStructCustomization> KeyStructCustomization;`
- L40 _private member_ `IDetailPropertyRow* InputActionTriggersPropertyRow = nullptr;`
- L41 _private member_ `IDetailPropertyRow* InputActionModifiersPropertyRow = nullptr;`

#### class `FEnhancedInputDeveloperSettingsCustomization`  
`class FEnhancedInputDeveloperSettingsCustomization : public IDetailCustomization`  
_L50-100_
- inherits: `IDetailCustomization`
- desc: Customization for UEnhancedInputDeveloperSettings. This will just make the normal details panel for UEnhancedInputDeveloperSettings, and then add all the default settings of Input Triggers and Input Modifiers by gather all the CDO's for them.
- L54 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L57 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L58 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L62 _public prototype_ `static bool DoesClassHaveSubtypes(UClass* Class);` — Returns true if something inherits from the UClass passed in. Checks BPs and Native
- L67 _private prototype_ `static void GatherNativeClassDetailsCDOs(UClass* Class, TArray<UObject*>& CDOs);` — Gather all of the native class CDOs for the given class.
- L75 _private prototype_ `void RebuildDetailsViewForAsset(const FAssetData& AssetData, const bool bIsAssetBeingRemoved);` — Called when any Asset is added, removed, or renamed. This will rebuild the Modifier and Trigger CDO views to make sure that any newly added Blueprint
- L78 _private function_ `void OnAssetAdded(const FAssetData& AssetData)` — Callbacks that are triggered from the Asset Registry.
- L79 _private function_ `void OnAssetRemoved(const FAssetData& AssetData)`
- L80 _private function_ `void OnAssetRenamed(const FAssetData& AssetData, const FString&)`
- L89 _private prototype_ `void CustomizeCDOValues(IDetailLayoutBuilder& DetailBuilder, const FName CategoryName, const TArray<UObject*>& ObjectsToCustomize);` — Create a new category on the DetailBuilder and add each object in the given array as an external reference. @param DetailBuilder			The details builder that can be used to add categories @param CategoryName			The name of the new category to add @param ObjectsToCustomize	Array of CDO objects to customize and add as external references
- L92 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;` — Cached details builder so that we can rebuild the details when a new BP asset is added
- L99 _private member_ `static TSet<FName> ExcludedAssetNames;` — Populated by RebuildDetailsViewForAsset so that we can exclude any blueprint classes that have been removed from the asset registry but are still loaded in memory. This is reset when CustomizeCDOValues is called

#### class `FPlayerMappableKeyChildSettingsCustomization`  
`class FPlayerMappableKeyChildSettingsCustomization : public IPropertyTypeCustomization`  
_L106-127_
- inherits: `IPropertyTypeCustomization`
- desc: Input customization for UPlayerMappableKeySettings to have some name validation on the custom saved FNames for mappings.
- L109 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L112 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L113 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L117 _private prototype_ `UPlayerMappableKeySettings* GetSettingsObject() const;`
- L118 _private prototype_ `FName GetCurrentName() const;`
- L120 _private prototype_ `FText OnGetMappingNameText() const;`
- L121 _private prototype_ `FText OnGetMappingNameToolTipText() const;`
- L122 _private prototype_ `void OnMappingNameTextCommited(const FText& NewText, ETextCommit::Type InTextCommit);`
- L123 _private prototype_ `bool OnVerifyMappingName(const FText& InNewText, FText& OutErrorMessage);`
- L125 _private member_ `TSharedPtr<IPropertyHandle> SettingsPropHandle;`
- L126 _private member_ `TSharedPtr<IPropertyHandle> MappingNamePropHandle;`

#### class `FMappingContextKeyContainerCustomization`  
`class FMappingContextKeyContainerCustomization : public IPropertyTypeCustomization`  
_L132-150_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for FInputMappingContextMappingData.
- L135 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L137 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L142 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L149 _private member_ `TSharedPtr<IPropertyHandle> MappingsArrayHandle;`

### `Plugins/EnhancedInput/Source/InputEditor/Public/EnhancedInputEditorProcessor.h` (Public)


#### class `FEnhancedInputEditorProcessor`  
`class FEnhancedInputEditorProcessor : public IInputProcessor`  
_L17-51_
- inherits: `IInputProcessor`
- desc: The Enhanced Input Editor Processor is used to pass InputKey events to the Enhanced Input Editor Subsystem. It will not steal input, and all the functions here will return "False" so that other Input Processors still run with all their normal considerations.
- L21 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;`
- L22 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L23 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L24 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L25 _public prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual bool HandleMouseButtonUpEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;`
- L30 _public function_ `virtual const TCHAR* GetDebugName() const`
- L35 _protected prototype_ `void UpdateCachedPointerPosition(const FPointerEvent& MouseEvent);`
- L38 _protected prototype_ `void ProcessAccumulatedPointerInput(float DeltaTime);` — Called on Tick to process any accumulated mouse input
- L41 _protected prototype_ `bool InputKeyToSubsystem(const struct FInputKeyEventArgs& Params);` — Tells the Enhanced Input Editor subsystem about the given key event
- L47 _protected member_ `FIntPoint NumCursorSamplesThisFrame = FIntPoint::ZeroValue;` — The number of cursor samples that happened this frame. The X and Y will be incremented when there is a mouse move event this frame and it will be reset on ProcessAccumulatedPointerInput.
- L50 _protected member_ `FVector2D CachedCursorDelta = FVector2D::ZeroVector;` — The value of the mouse cursor from the most recent mouse event

### `Plugins/EnhancedInput/Source/InputEditor/Public/EnhancedInputEditorSettings.h` (Public)


#### class `UEnhancedInputEditorProjectSettings`  
`class UEnhancedInputEditorProjectSettings : public UDeveloperSettings`  
_L19-33_
- reflection: `UCLASS(config = Input, defaultconfig, meta = (DisplayName = "Enhanced Input (Editor Only)"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the Enhanced Input Editor Subsystem that are persistent between a project's users
- L24 _public prototype_ `UEnhancedInputEditorProjectSettings(const FObjectInitializer& Initializer);`
- L28 _public member_ `TSoftClassPtr<UEnhancedPlayerInput> DefaultEditorInputClass;` — `UPROPERTY(config, EditAnywhere, NoClear, Category = Default)` — The default player input class that the Enhanced Input Editor subsystem will use.
- L32 _public member_ `TArray<FDefaultContextSetting> DefaultMappingContexts;` — `UPROPERTY(config, EditAnywhere, Category = Default)` — Array of any input mapping contexts that you want to always be applied to the Enhanced Input Editor Subsystem.

#### class `UEnhancedInputEditorSettings`  
`class UEnhancedInputEditorSettings : public UDeveloperSettingsBackedByCVars`  
_L39-60_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta=(DisplayName="Enhanced Input Editor Settings"))`
- inherits: `UDeveloperSettingsBackedByCVars`
- desc: A collection of useful individual user settings when using the EnhancedInputEditorSubsystem.
- L44 _public prototype_ `UEnhancedInputEditorSettings();`
- L51 _public member_ `uint8 bLogAllInput : 1;` — `UPROPERTY(config, EditAnywhere, Category = Logging)` — If true then the Enhanced Input Editor subsystem will log all input that is being processed by it (keypresses, analog values, etc) Note: This can produce A LOT of logs, so only use this if you are debugging something.
- L55 _public member_ `uint8 bAutomaticallyStartConsumingInput : 1;` — `UPROPERTY(config, EditAnywhere, Category = Editor)` — If true, then the UEnhancedInputEditorSubsystem will be started when it is initalized
- L59 _public member_ `uint8 VisibleEventPinsByDefault;` — `UPROPERTY(config, EditAnywhere, Category = Blueprints, meta = (Bitmask, BitmaskEnum = "/Script/EnhancedInput.ETriggerEvent"))` — A bitmask of what event pins are visible when you place an Input Action event node in blueprints.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INPUTEDITOR_API`

### `Plugins/EnhancedInput/Source/InputEditor/Public/EnhancedInputEditorSubsystem.h` (Public)


#### class `UEnhancedInputEditorSubsystem`  
`class UEnhancedInputEditorSubsystem : public UEditorSubsystem, public IEnhancedInputSubsystemInterface, public FTickableGameObject`  
_L29-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,IEnhancedInputSubsystemInterface,FTickableGameObject`
- desc: The Enhanced Input Editor Subsystem can be used to process input outside of PIE within the editor. Calling StartConsumingInput will allow the input preprocessor to drive Input Action delegates to be fired in the editor. This allows you to hook up Input Action delegates in Editor Utilities to make editor tools driven by input.
- L36 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L37 _public prototype_ `virtual void Deinitialize() override;`
- L38 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L42 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L43 _public function_ `virtual bool IsTickableInEditor() const`
- L44 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L45 _public prototype_ `virtual bool IsTickable() const override;`
- L46 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L47 _public function_ `TStatId GetStatId() const override`
- L51 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L55 _public prototype_ `virtual UEnhancedPlayerInput* GetPlayerInput() const override;`
- L57 _protected function_ `virtual TMap<TObjectPtr<const UInputAction>, FInjectedInput>& GetContinuouslyInjectedInputs() override`
- L63 _public prototype_ `void PushInputComponent(UInputComponent* InInputComponent);` — `UFUNCTION(BlueprintCallable, Category = "Input|Editor")` — Pushes this input component onto the stack to be processed by this subsystem's tick function
- L67 _public prototype_ `bool PopInputComponent(UInputComponent* InInputComponent);` — `UFUNCTION(BlueprintCallable, Category = "Input|Editor")` — Removes this input component onto the stack to be processed by this subsystem's tick function
- L71 _public prototype_ `void StartConsumingInput();` — `UFUNCTION(BlueprintCallable, Category = "Input|Editor")` — Start the consumption of input messages in this subsystem. This is required to have any Input Action delegates be fired.
- L75 _public prototype_ `void StopConsumingInput();` — `UFUNCTION(BlueprintCallable, Category = "Input|Editor")` — Tells this subsystem to stop ticking and consuming any input. This will stop any Input Action Delegates from being called.
- L79 _public function_ `bool IsConsumingInput() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input|Editor")` — Returns true if this subsystem is currently consuming input
- L82 _public prototype_ `bool InputKey(const FInputKeyEventArgs& Params);` — Inputs a key on this subsystem's player input which can then be processed as normal during Tick.
- L85 _public prototype_ `void AddDefaultMappingContexts();` — Adds all the default mapping contexts from the UEnhancedInputEditorSettings
- L88 _public prototype_ `void RemoveDefaultMappingContexts();` — Removes all the default mapping contexts from the UEnhancedInputEditorSettings
- L94 _private member_ `TObjectPtr<UEnhancedPlayerInput> PlayerInput = nullptr;` — `UPROPERTY()` — The player input that is processing the input within this subsystem
- L100 _private member_ `TSharedPtr<FEnhancedInputEditorProcessor> InputPreprocessor = nullptr;` — Input processor that is created on Initalize. This will take input from the editor and pass it through to this subsystem via InputKey.
- L103 _private member_ `bool bIsCurrentlyConsumingInput = false;` — If true, then this subsystem will Tick and process input delegates.
- L107 _private member_ `TArray<TWeakObjectPtr<UInputComponent>> CurrentInputStack;` — `UPROPERTY(Transient)` — Internal. This is the current stack of InputComponents that is being processed by the PlayerInput.
- L112 _protected member_ `TMap<TObjectPtr<const UInputAction>, FInjectedInput> ContinuouslyInjectedInputs;` — `UPROPERTY(Transient)` — Map of inputs that should be injected every frame. These inputs will be injected when ForcedInput is ticked.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INPUTEDITOR_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorInput, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorInput, Log, All);`

### `Plugins/EnhancedInput/Source/InputEditor/Public/EnhancedInputPlayerMappableNameValidator.h` (Public)


#### class `FEnhancedInputPlayerMappableNameValidator`  
`class FEnhancedInputPlayerMappableNameValidator : public FStringSetNameValidator`  
_L7-23_
- inherits: `FStringSetNameValidator`
- L10 _public prototype_ `FEnhancedInputPlayerMappableNameValidator(FName InExistingName);`
- L13 _public prototype_ `virtual EValidatorResult IsValid(const FString& Name, bool bOriginal) override;`
- L22 _public prototype_ `static FText GetErrorText(const FString& Name, EValidatorResult ErrorCode);` — If the error code is EValidatorResult::AlreadyInUse, this returns special error text that says what asset is using the name. Otherwise it will return INameValidatorInterface::GetErrorText.

### `Plugins/EnhancedInput/Source/InputEditor/Public/InputEditorModule.h` (Public)


#### class `FInputEditorModule`  
`class FInputEditorModule : public IModuleInterface`  
_L25-51_
- inherits: `IModuleInterface`
- L30 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public prototype_ `static EAssetTypeCategories::Type GetInputAssetsCategory();`
- L37 _public prototype_ `static const UPlayerMappableKeySettings* FindMappingByName(const FName InName);` — Returns a pointer to the player mappable settings object that has this mapping name
- L40 _public prototype_ `static bool IsMappingNameInUse(const FName InName);` — Returns true if the given name is in use by a player mappable key setting
- L43 _private prototype_ `void OnMainFrameCreationFinished(TSharedPtr<SWindow> InRootWindow, bool bIsRunningStartupDialog);`
- L46 _private prototype_ `void AutoUpgradeDefaultInputClasses();` — Automatically upgrade the current project to use Enhanced Input if it is currently set to the legacy input classes.
- L48 _private member_ `static EAssetTypeCategories::Type InputAssetsCategory;`
- L50 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;`

#### class `UInputMappingContext_Factory`  
`class UInputMappingContext_Factory : public UFactory`  
_L57-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L62 _public member_ `TSubclassOf<class UInputMappingContext> InputMappingContextClass;` — `UPROPERTY(EditAnywhere, Category=InputMappingContext)`
- L64 _public prototype_ `virtual bool ConfigureProperties() override;`
- L65 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L68 _public prototype_ `void SetInitialActions(TArray<TWeakObjectPtr<UInputAction>> InInitialActions);` — Set the array of initial actions that the resulting IMC should be populated with
- L73 _protected member_ `TArray<TWeakObjectPtr<UInputAction>> InitialActions;` — An array of Input Actions that the mapping context should be populated with upon creation

#### class `UInputAction_Factory`  
`class UInputAction_Factory : public UFactory`  
_L78-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L83 _public member_ `TSubclassOf<UInputAction> InputActionClass;` — `UPROPERTY(EditAnywhere, Category=InputAction)`
- L85 _public prototype_ `virtual bool ConfigureProperties() override;`
- L86 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INPUTEDITOR_API`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEnhancedInputEditor, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEnhancedInputEditor, Log, All);`
