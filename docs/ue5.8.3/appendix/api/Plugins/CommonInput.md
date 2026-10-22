# Plugins / CommonInput

- module root: `Plugins/Runtime/CommonUI/Source/CommonInput`
- headers: 9; symbols: 276
- symbol kinds: class=12, delegate=6, enum=3, enumerator=11, function=33, macro=5, member=95, namespace=1, prototype=104, struct=6
- PrivateDependencyModuleNames: ApplicationCore, EngineSettings, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, EnhancedInput, InputCore, UnrealEd

### `Plugins/Runtime/CommonUI/Source/CommonInput/Private/CommonInputPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommonInput, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommonInput, Log, All);`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputActionDomain.h` (Public)


#### enum `ECommonInputEventFlowBehavior`  
`enum class ECommonInputEventFlowBehavior`  
_L19-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `BlockIfActive`
- L21 _public enumerator_ `BlockIfHandled`
- L22 _public enumerator_ `NeverBlock`

#### class `ICommonInputActionDomainMetaData`  
`class ICommonInputActionDomainMetaData : public ISlateMetaData`  
_L26-36_
- inherits: `ISlateMetaData`
- desc: Slate meta data to store the owning Action Domain
- L29 _public prototype_ `SLATE_METADATA_TYPE(ICommonInputActionDomainMetaData, ISlateMetaData);`
- L31 _public function_ `explicit ICommonInputActionDomainMetaData(const TWeakObjectPtr<UCommonInputActionDomain> InActionDomain) : ActionDomain(InActionDomain)`
- L35 _public member_ `TWeakObjectPtr<UCommonInputActionDomain> ActionDomain;`

#### class `UCommonInputActionDomain`  
`class UCommonInputActionDomain : public UDataAsset`  
_L44-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Describes an input-event handling domain. It's InnerBehavior determines how events flow between widgets within the domain and Behavior determines how events will flow to other Domains in the DomainTable.
- L51 _public member_ `ECommonInputEventFlowBehavior Behavior = ECommonInputEventFlowBehavior::BlockIfActive;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — Behavior of an input event between Action Domains, i.e., how an event flows into the next Action Domain
- L56 _public member_ `ECommonInputEventFlowBehavior InnerBehavior = ECommonInputEventFlowBehavior::BlockIfHandled;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")` — Behavior of an input event within an Action Domain, i.e., how an event flows to a lower ZOrder active widget within the same Action Domain
- L59 _public member_ `bool bUseActionDomainDesiredInputConfig;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")`
- L62 _public member_ `ECommonInputMode InputMode = ECommonInputMode::Game;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", meta = (EditCondition = "bUseActionDomainDesiredInputConfig"))`
- L65 _public member_ `EMouseCaptureMode MouseCaptureMode = EMouseCaptureMode::CapturePermanently;` — `UPROPERTY(EditDefaultsOnly, Category = "Default", meta = (EditCondition = "bUseActionDomainDesiredInputConfig"))`
- L67 _public prototype_ `bool ShouldBreakInnerEventFlow(bool bInputEventHandled) const;`
- L69 _public prototype_ `bool ShouldBreakEventFlow(bool bDomainHadActiveRoots, bool bInputEventHandledAtLeastOnce) const;`

#### class `UCommonInputActionDomainTable`  
`class UCommonInputActionDomainTable : public UDataAsset`  
_L76-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: An ordered array of ActionDomains.
- L83 _public member_ `TArray<TObjectPtr<UCommonInputActionDomain>> ActionDomains;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")` — Domains will receive events in ascending index order
- L86 _public member_ `ECommonInputMode InputMode = ECommonInputMode::Game;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")`
- L89 _public member_ `EMouseCaptureMode MouseCaptureMode = EMouseCaptureMode::CapturePermanently;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")`
- L92 _public member_ `bool bHideCursorDuringViewportCapture = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONINPUT_API`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUIActionDomain, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUIActionDomain, Log, All);`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputBaseTypes.h` (Public)


#### struct `FCommonInputDefaults`  
`struct FCommonInputDefaults`  
_L29-33_
- L31 _public member_ `static const FName PlatformPC;`
- L32 _public member_ `static const FName GamepadGeneric;`

#### struct `FCommonInputKeyBrushConfiguration`  
`struct FCommonInputKeyBrushConfiguration`  
_L36-51_
- reflection: `USTRUCT(Blueprintable)`
- L41 _public prototype_ `FCommonInputKeyBrushConfiguration();`
- L43 _public function_ `const FSlateBrush& GetInputBrush() const`
- L47 _public member_ `FKey Key;` — `UPROPERTY(EditAnywhere, Category = "Key Brush Configuration")`
- L50 _public member_ `FSlateBrush KeyBrush;` — `UPROPERTY(EditAnywhere, Category = "Key Brush Configuration")`

#### struct `FCommonInputKeySetBrushConfiguration`  
`struct FCommonInputKeySetBrushConfiguration`  
_L54-69_
- reflection: `USTRUCT(Blueprintable)`
- L59 _public prototype_ `FCommonInputKeySetBrushConfiguration();`
- L61 _public function_ `const FSlateBrush& GetInputBrush() const`
- L65 _public member_ `TArray<FKey> Keys;` — `UPROPERTY(EditAnywhere, Category = "Key Brush Configuration", Meta = (TitleProperty = "KeyName"))`
- L68 _public member_ `FSlateBrush KeyBrush;` — `UPROPERTY(EditAnywhere, Category = "Key Brush Configuration")`

#### struct `FInputDeviceIdentifierPair`  
`struct FInputDeviceIdentifierPair`  
_L72-81_
- reflection: `USTRUCT()`
- L77 _public member_ `FName InputDeviceName;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad")`
- L80 _public member_ `FString HardwareDeviceIdentifier;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad")`

#### struct `FInputHoldData`  
`struct FInputHoldData`  
_L85-93_
- reflection: `USTRUCT()`
- desc: Data values needed for Hold interaction per input type.
- L89 _public member_ `float HoldTime = 0.0;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (ClampMin = "0.0", UIMin = "0.0"))`
- L92 _public member_ `float HoldRollbackTime = 0.0;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (ClampMin = "0.0", UIMin = "0.0"))`

#### class `UCommonUIInputData`  
`class UCommonUIInputData : public UObject`  
_L103-129_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = Input, meta = (Category = "Common Input"))`
- inherits: `UObject`
- desc: Derive from this class to store the Input data. It is referenced in the Common Input Settings, found in the project settings UI.
- L108 _public prototype_ `virtual bool NeedsLoadForServer() const override;`
- L112 _public member_ `FDataTableRowHandle DefaultClickAction;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))`
- L115 _public member_ `FDataTableRowHandle DefaultBackAction;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))`
- L122 _public member_ `TSoftClassPtr<UCommonUIHoldData> DefaultHoldData;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties")` — Newly created CommonButton widgets will use these hold values by default if bRequiresHold is true. Inherits from UCommonUIHoldData.
- L125 _public member_ `TObjectPtr<UInputAction> EnhancedInputClickAction;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))`
- L128 _public member_ `TObjectPtr<UInputAction> EnhancedInputBackAction;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))`

#### class `UCommonUIHoldData`  
`class UCommonUIHoldData : public UObject`  
_L133-153_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = Input, meta = (Category = "Common Input"))`
- inherits: `UObject`
- desc: Defines values for hold behavior per input type: for mouse Press and Hold, for gamepad focused Press and Hold, for touch Press and Hold.
- L137 _public function_ `UCommonUIHoldData()`
- L148 _public member_ `FInputHoldData KeyboardAndMouse;` — `UPROPERTY(EditDefaultsOnly, Category = "KeyboardAndMouse", meta = (ShowOnlyInnerProperties))`
- L150 _public member_ `FInputHoldData Gamepad;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", meta = (ShowOnlyInnerProperties))`
- L152 _public member_ `FInputHoldData Touch;` — `UPROPERTY(EditDefaultsOnly, Category = "Touch", meta = (ShowOnlyInnerProperties))`

#### class `UCommonInputBaseControllerData`  
`class UCommonInputBaseControllerData : public UObject`  
_L157-213_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = Input, meta = (Category = "Common Input"))`
- inherits: `UObject`
- desc: Derive from this class to store the Input data. It is referenced in the Common Input Settings, found in the project settings UI.
- L162 _public prototype_ `virtual bool NeedsLoadForServer() const override;`
- L163 _public prototype_ `virtual bool TryGetInputBrush(FSlateBrush& OutBrush, const FKey& Key) const;`
- L164 _public prototype_ `virtual bool TryGetInputBrush(FSlateBrush& OutBrush, const TArray<FKey>& Keys) const;`
- L166 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L167 _public prototype_ `virtual void PostLoad() override;`
- L172 _private member_ `int32 SetButtonImageHeightTo = 0;` — `UPROPERTY(Transient, EditAnywhere, Category = "Editor")`
- L177 _public member_ `ECommonInputType InputType;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")`
- L180 _public member_ `FName GamepadName;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", meta=(EditCondition="InputType == ECommonInputType::Gamepad", GetOptions = GetRegisteredGamepads))`
- L183 _public member_ `FText GamepadDisplayName;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", meta = (EditCondition = "InputType == ECommonInputType::Gamepad"))`
- L186 _public member_ `FText GamepadCategory;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", meta=(EditCondition="InputType == ECommonInputType::Gamepad"))`
- L189 _public member_ `FText GamepadPlatformName;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", meta = (EditCondition = "InputType == ECommonInputType::Gamepad"))`
- L192 _public member_ `TArray<FInputDeviceIdentifierPair> GamepadHardwareIdMapping;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", meta=(EditCondition="InputType == ECommonInputType::Gamepad"))`
- L195 _public member_ `TSoftObjectPtr<UTexture2D> ControllerTexture;` — `UPROPERTY(EditDefaultsOnly, Category = "Display")`
- L198 _public member_ `TSoftObjectPtr<UTexture2D> ControllerButtonMaskTexture;` — `UPROPERTY(EditDefaultsOnly, Category = "Display")`
- L201 _public member_ `TArray<FCommonInputKeyBrushConfiguration> InputBrushDataMap;` — `UPROPERTY(EditDefaultsOnly, Category = "Display", Meta = (TitleProperty = "Key"))`
- L204 _public member_ `TArray<FCommonInputKeySetBrushConfiguration> InputBrushKeySets;` — `UPROPERTY(EditDefaultsOnly, Category = "Display", Meta = (TitleProperty = "Keys"))`
- L207 _public prototype_ `static const TArray<FName>& GetRegisteredGamepads();` — `UFUNCTION()`
- L211 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UCommonInputPlatformSettings`  
`class UCommonInputPlatformSettings : public UPlatformSettings`  
_L216-294_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig)`
- inherits: `UPlatformSettings`
- L223 _public prototype_ `UCommonInputPlatformSettings();`
- L225 _public prototype_ `virtual void PostLoad() override;`
- L227 _public function_ `static UCommonInputPlatformSettings* Get()`
- L232 _public prototype_ `bool TryGetInputBrush(FSlateBrush& OutBrush, FKey Key, ECommonInputType InputType, const FName GamepadName) const;`
- L233 _public prototype_ `bool TryGetInputBrush(FSlateBrush& OutBrush, const TArray<FKey>& Keys, ECommonInputType InputType, const FName GamepadName) const;`
- L235 _public function_ `TArray<TSoftClassPtr<UCommonInputBaseControllerData>> GetControllerData() const`
- L239 _public prototype_ `TArray<const UCommonInputBaseControllerData*> GetControllerDataForInputType(ECommonInputType InputType, const FName GamepadName) const;`
- L240 _public prototype_ `void AddControllerDataEntry(TSoftClassPtr<UCommonInputBaseControllerData> Entry);`
- L241 _public prototype_ `void RemoveControllerDataEntry(TSoftClassPtr<UCommonInputBaseControllerData> Entry);`
- L243 _public prototype_ `FName GetBestGamepadNameForHardware(FName CurrentGamepadName, FName InputDeviceName, const FString& HardwareDeviceIdentifier);`
- L245 _public function_ `ECommonInputType GetDefaultInputType() const`
- L250 _public prototype_ `bool SupportsInputType(ECommonInputType InputType) const;`
- L252 _public function_ `const FName GetDefaultGamepadName() const`
- L257 _public function_ `bool CanChangeGamepadType() const`
- L263 _public prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L265 _public prototype_ `virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;`
- L268 _protected prototype_ `void InitializeControllerData() const;`
- L269 _protected prototype_ `virtual void InitializePlatformDefaults();`
- L272 _protected member_ `ECommonInputType DefaultInputType;` — `UPROPERTY(config, EditAnywhere, Category = "Default")`
- L275 _protected member_ `bool bSupportsMouseAndKeyboard;` — `UPROPERTY(config, EditAnywhere, Category = "Default")`
- L278 _protected member_ `bool bSupportsTouch;` — `UPROPERTY(config, EditAnywhere, Category = "Default")`
- L281 _protected member_ `bool bSupportsGamepad;` — `UPROPERTY(config, EditAnywhere, Category = "Default")`
- L284 _protected member_ `FName DefaultGamepadName;` — `UPROPERTY(config, EditAnywhere, Category = "Default", Meta = (EditCondition = "bSupportsGamepad"))`
- L287 _protected member_ `bool bCanChangeGamepadType;` — `UPROPERTY(config, EditAnywhere, Category = "Default", Meta = (EditCondition = "bSupportsGamepad"))`
- L290 _protected member_ `TArray<TSoftClassPtr<UCommonInputBaseControllerData>> ControllerData;` — `UPROPERTY(config, EditAnywhere, Category = "Default", Meta = (TitleProperty = "InputType"))`
- L293 _protected member_ `mutable TArray<TSubclassOf<UCommonInputBaseControllerData>> ControllerDataClasses;` — `UPROPERTY(Transient)`

#### struct `FCommonInputPlatformBaseData`  
`struct FCommonInputPlatformBaseData`  
_L298-389_
- reflection: `USTRUCT()`
- desc: DEPRECATED Legacy!
- L305 _public function_ `FCommonInputPlatformBaseData()`
- L314 _public prototype_ `virtual ~FCommonInputPlatformBaseData() = default;`
- L316 _public prototype_ `virtual bool TryGetInputBrush(FSlateBrush& OutBrush, FKey Key, ECommonInputType InputType, const FName& GamepadName) const;`
- L317 _public prototype_ `virtual bool TryGetInputBrush(FSlateBrush& OutBrush, const TArray<FKey>& Keys, ECommonInputType InputType, const FName& GamepadName) const;`
- L320 _public function_ `ECommonInputType GetDefaultInputType() const`
- L325 _public function_ `bool SupportsInputType(ECommonInputType InputType) const`
- L348 _public function_ `const FName GetDefaultGamepadName() const`
- L353 _public function_ `bool CanChangeGamepadType() const`
- L358 _public function_ `TArray<TSoftClassPtr<UCommonInputBaseControllerData>> GetControllerData()`
- L363 _public prototype_ `static const TArray<FName>& GetRegisteredPlatforms();`
- L367 _protected member_ `ECommonInputType DefaultInputType;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties")`
- L370 _protected member_ `bool bSupportsMouseAndKeyboard;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties")`
- L373 _protected member_ `bool bSupportsGamepad;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad")`
- L376 _protected member_ `FName DefaultGamepadName;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", Meta = (EditCondition = "bSupportsGamepad"))`
- L379 _protected member_ `bool bCanChangeGamepadType;` — `UPROPERTY(EditDefaultsOnly, Category = "Gamepad", Meta = (EditCondition = "bSupportsGamepad"))`
- L382 _protected member_ `bool bSupportsTouch;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties")`
- L385 _protected member_ `TArray<TSoftClassPtr<UCommonInputBaseControllerData>> ControllerData;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", Meta = (TitleProperty = "GamepadName"))`
- L388 _protected member_ `TArray<TSubclassOf<UCommonInputBaseControllerData>> ControllerDataClasses;` — `UPROPERTY(Transient)`

#### class `FCommonInputBase`  
`class FCommonInputBase`  
_L391-399_
- L394 _public prototype_ `static FName GetCurrentPlatformName();`
- L396 _public prototype_ `static UCommonInputSettings* GetInputSettings();`
- L398 _public prototype_ `static void GetCurrentPlatformDefaults(ECommonInputType& OutDefaultInputType, FName& OutDefaultGamepadName);`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API COMMONINPUT_API`
- L95 _namespace_ `namespace CommonUIUtils`
- L97 _prototype_ `bool TryGetInputBrushFromDataMap(FSlateBrush& OutBrush, const FKey& InKey, const TArray<FCommonInputKeyBrushConfiguration>& InInputBrushDataMap);` (scope `CommonUIUtils`)
- L98 _prototype_ `bool TryGetInputBrushFromKeySets(FSlateBrush& OutBrush, const TArray<FKey>& InKeys, const TArray<FCommonInputKeySetBrushConfiguration>& InInputBrushKeySets);` (scope `CommonUIUtils`)

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputModeTypes.h` (Public)


#### enum `ECommonInputMode`  
`enum class ECommonInputMode : uint8`  
_L11-18_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Menu UMETA(Tooltip = "Input is received by the UI only")`
- L14 _public enumerator_ `Game UMETA(Tooltip = "Input is received by the Game only")`
- L15 _public enumerator_ `All UMETA(Tooltip = "Input is received by UI and the Game")`
- L17 _public enumerator_ `MAX UMETA(Hidden)`

#### Free symbols / members of external scopes

- L20 _function_ `inline const TCHAR* LexToString(ECommonInputMode Value)`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputPreprocessor.h` (Public)


#### class `FCommonInputPreprocessor`  
`class FCommonInputPreprocessor : public IInputProcessor`  
_L18-62_
- inherits: `IInputProcessor`
- desc: Helper class that is designed to fire before any UI has a chance to process input so that we can properly set the current input type of the application.
- L21 _public prototype_ `FCommonInputPreprocessor(UCommonInputSubsystem& InCommonInputSubsystem);`
- L24 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;`
- L25 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L26 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L27 _public prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& InPointerEvent) override;`
- L28 _public prototype_ `virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& InPointerEvent) override;`
- L29 _public prototype_ `virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& InPointerEvent) override;`
- L30 _public prototype_ `virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;`
- L31 _public function_ `virtual const TCHAR* GetDebugName() const override`
- L34 _public prototype_ `void SetInputTypeFilter(ECommonInputType InputType, FName InReason, bool InFilter);`
- L36 _public prototype_ `bool IsInputMethodBlocked(ECommonInputType InputType) const;`
- L38 _public member_ `FGamepadChangeDetectedEvent OnGamepadChangeDetected;`
- L41 _protected prototype_ `bool IsRelevantInput(FSlateApplication& SlateApp, const FInputEvent& InputEvent, const ECommonInputType DesiredInputType);`
- L43 _protected prototype_ `void RefreshCurrentInputMethod(ECommonInputType InputMethod);`
- L45 _protected prototype_ `ECommonInputType GetInputType(const FKey& Key);`
- L47 _protected prototype_ `ECommonInputType GetInputType(const FPointerEvent& PointerEvent);`
- L50 _protected member_ `UCommonInputSubsystem& InputSubsystem;`
- L52 _protected member_ `bool bIgnoreNextMove = false;`
- L53 _protected member_ `bool InputMethodPermissions[(uint8)ECommonInputType::Count];`
- L56 _protected member_ `TMap<FName, bool> FilterInputTypeWithReasons[(uint8)ECommonInputType::Count];` — The reasons we might be filtering input right now.
- L58 _protected member_ `FName LastSeenGamepadInputDeviceName;`
- L59 _protected member_ `FString LastSeenGamepadHardwareDeviceIdentifier;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONINPUT_API`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputSettings.h` (Public)


#### class `UCommonInputSettings`  
`class UCommonInputSettings : public UDeveloperSettings`  
_L25-147_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig)`
- inherits: `UDeveloperSettings`
- L30 _public prototype_ `UCommonInputSettings(const FObjectInitializer& Initializer);`
- L33 _public prototype_ `void LoadData();` — Called to load CommonUISetting data, if bAutoLoadData if set to false then game code must call LoadData().
- L36 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `void ValidateData();` — Called to check that the data we have previously attempted to load is actually loaded and will attempt to load if it is not.
- L42 _public prototype_ `FDataTableRowHandle GetDefaultClickAction() const;`
- L43 _public prototype_ `FDataTableRowHandle GetDefaultBackAction() const;`
- L46 _public prototype_ `TSubclassOf<UCommonUIHoldData> GetDefaultHoldData() const;` — Default Hold Data
- L48 _public prototype_ `UInputAction* GetEnhancedInputClickAction() const;`
- L49 _public prototype_ `UInputAction* GetEnhancedInputBackAction() const;`
- L51 _public function_ `bool GetEnableInputMethodThrashingProtection() const`
- L53 _public function_ `int32 GetInputMethodThrashingLimit() const`
- L55 _public function_ `double GetInputMethodThrashingWindowInSeconds() const`
- L57 _public function_ `double GetInputMethodThrashingCooldownInSeconds() const`
- L59 _public function_ `bool GetAllowOutOfFocusDeviceInput() const`
- L61 _public function_ `bool GetEnableDefaultInputConfig() const`
- L63 _public function_ `bool GetEnableEnhancedInputSupport() const`
- L65 _public function_ `bool GetEnableAutomaticGamepadTypeDetection() const`
- L67 _public function_ `TObjectPtr<UCommonInputActionDomainTable> GetActionDomainTable() const`
- L69 _public function_ `const TMap<FName, FName>& GetPlatformNameUpgradeMap() const`
- L75 _public prototype_ `static bool IsEnhancedInputSupportEnabled();` — `UFUNCTION()` — Static version of enhanced input support check, exists to hide based on edit condition
- L78 _private prototype_ `virtual void PostInitProperties() override;`
- L82 _private member_ `TSoftClassPtr<UCommonUIInputData> InputData;` — `UPROPERTY(config, EditAnywhere, Category = "Input", Meta=(AllowAbstract=false))` — Create a derived asset from UCommonUIInputData to store Input data for your game.
- L85 _private member_ `FPerPlatformSettings PlatformInput;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L88 _private member_ `TMap<FName, FCommonInputPlatformBaseData> CommonInputPlatformData_DEPRECATED;` — `UPROPERTY(config)`
- L91 _private member_ `bool bEnableInputMethodThrashingProtection = true;` — `UPROPERTY(config, EditAnywhere, Category = "Thrashing Settings")`
- L94 _private member_ `int32 InputMethodThrashingLimit = 30;` — `UPROPERTY(config, EditAnywhere, Category = "Thrashing Settings")`
- L97 _private member_ `double InputMethodThrashingWindowInSeconds = 3.0;` — `UPROPERTY(config, EditAnywhere, Category = "Thrashing Settings")`
- L100 _private member_ `double InputMethodThrashingCooldownInSeconds = 1.0;` — `UPROPERTY(config, EditAnywhere, Category = "Thrashing Settings")`
- L103 _private member_ `bool bAllowOutOfFocusDeviceInput = false;` — `UPROPERTY(config, EditAnywhere, Category = "Input")`
- L110 _private member_ `bool bEnableDefaultInputConfig = true;` — `UPROPERTY(config, EditAnywhere, Category = "Input")` — Controls whether a default Input Config will be set when the active CommonActivatableWidgets do not specify a desired one. Disable this if you want to control the Input Mode via alternative means.
- L114 _private member_ `bool bEnableEnhancedInputSupport = false;` — `UPROPERTY(config, EditAnywhere, Category = "Input", meta = (ConfigRestartRequired = true))` — Controls if Enhanced Input Support plugin-wide. Requires restart due to caching.
- L121 _private member_ `bool bEnableAutomaticGamepadTypeDetection = true;` — `UPROPERTY(config, EditAnywhere, Category = "Input")` — Controls automatic detection of the gamepad type. Disable this if you want to manually control the gamepad type using the UCommonInputSubsystem::SetGamepadInputType() function.
- L125 _private member_ `TSoftObjectPtr<UCommonInputActionDomainTable> ActionDomainTable;` — `UPROPERTY(config, EditAnywhere, Category = "Action Domain")` — Create a derived asset from UCommonInputActionDomainTable to store ordered ActionDomain data for your game
- L133 _private member_ `TMap<FName, FName> PlatformNameUpgrades;` — `UPROPERTY(config, EditAnywhere, Category = "Input", meta = (ConfigRestartRequired = true))` — A map of Common Input platform names to a new one, which you can use to upgrade your Input Action data tables if you add a new platform to your project and wish to copy from some existing data
- L136 _private prototype_ `void LoadInputData();`
- L137 _private prototype_ `void LoadActionDomainTable();`
- L139 _private member_ `bool bInputDataLoaded;`
- L140 _private member_ `bool bActionDomainTableLoaded;`
- L143 _private member_ `TSubclassOf<UCommonUIInputData> InputDataClass;` — `UPROPERTY(Transient)`
- L146 _private member_ `TObjectPtr<UCommonInputActionDomainTable> ActionDomainTablePtr;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API COMMONINPUT_API`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputSubsystem.h` (Public)


#### class `UCommonInputSubsystem`  
`class UCommonInputSubsystem : public ULocalPlayerSubsystem`  
_L25-188_
- reflection: `UCLASS(MinimalAPI, DisplayName = "CommonInput")`
- inherits: `ULocalPlayerSubsystem`
- L30 _public prototype_ `static UCommonInputSubsystem* Get(const ULocalPlayer* LocalPlayer);`
- L32 _public prototype_ `UCommonInputSubsystem();`
- L34 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L35 _public prototype_ `virtual void Deinitialize() override;`
- L37 _public prototype_ `DECLARE_EVENT_OneParam(UCommonInputSubsystem, FInputMethodChangedEvent, ECommonInputType);`
- L38 _public member_ `FInputMethodChangedEvent OnInputMethodChangedNative;`
- L40 _public prototype_ `FGamepadChangeDetectedEvent& GetOnGamepadChangeDetected();`
- L42 _public prototype_ `void SetInputTypeFilter(ECommonInputType InputType, FName Reason, bool Filter);`
- L43 _public prototype_ `bool GetInputTypeFilter(ECommonInputType InputType) const;`
- L46 _public prototype_ `void AddOrRemoveInputTypeLock(FName InReason, ECommonInputType InInputType, bool bAddLock);`
- L49 _public prototype_ `bool IsInputMethodActive(ECommonInputType InputMethod) const;` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)`
- L53 _public prototype_ `ECommonInputType GetCurrentInputType() const;` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)` — The current input type based on the last input received on the device.
- L57 _public prototype_ `ECommonInputType GetDefaultInputType() const;` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)` — The default input type for the current platform.
- L60 _public prototype_ `void SetCurrentInputType(ECommonInputType NewInputType);` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)`
- L63 _public prototype_ `const FName GetCurrentGamepadName() const;` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)`
- L66 _public prototype_ `void SetGamepadInputType(const FName InGamepadInputType);` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)`
- L69 _public prototype_ `bool IsUsingPointerInput() const;` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)`
- L73 _public prototype_ `bool ShouldShowInputKeys() const;` — `UFUNCTION(BlueprintCallable, Category = CommonInputSubsystem)` — Should display indicators for the current input device on screen.  This is needed when capturing videos, but we don't want to reveal the capture source device.
- L75 _public function_ `void SetActionDomainTable(TObjectPtr<UCommonInputActionDomainTable> Table)`
- L77 _public function_ `TObjectPtr<UCommonInputActionDomainTable> GetActionDomainTable() const`
- L80 _public prototype_ `static bool IsMobileGamepadKey(const FKey& InKey);` — Returns true if the specified key can be present on both a mobile device and mobile gamepads
- L83 _public prototype_ `bool PlatformSupportsHardwareCursor() const;` — Returns true if the current platform supports a hardware cursor
- L85 _public prototype_ `void SetCursorPosition(FVector2D NewPosition, bool bForce);`
- L87 _public prototype_ `void UpdateCursorPosition(TSharedRef<FSlateUser> SlateUser, const FVector2D& NewPosition, bool bForce = false);`
- L90 _public prototype_ `bool GetIsGamepadSimulatedClick() const;` — Getter
- L93 _public prototype_ `void SetIsGamepadSimulatedClick(bool bNewIsGamepadSimulatedClick);` — Setter
- L103 _public function_ `static FPlatformInputSupportOverrideDelegate& GetOnPlatformInputSupportOverride()` — Gets the delegate that allows external systems to override which input methods are supported on this current platform. @param LocalPlayer								The Local Player. @param InputType									The current input type that is being tested. @param InOutCurrentPlatformInputSupportState		The state of if we support the input type as set by PlatformSupportsInputType() or the previous callee of this delegate. Note : Calling order is not guaranteed. Also, keep in mind that you might need to honor the previous callee's request to not support the input type being tested.
- L106 _public prototype_ `bool HadAnyChangeOfInputMethodInTheLastThrashingWindow() const;` — Returns true if the input method changed in the last thrashing window. See UCommonInputSettings::GetInputMethodThrashingWindowInSeconds
- L109 _protected prototype_ `virtual TSharedPtr<FCommonInputPreprocessor> MakeInputProcessor();`
- L111 _protected prototype_ `ECommonInputType LockInput(ECommonInputType InputToLock) const;`
- L114 _protected prototype_ `void BroadcastInputMethodChanged();` — `UFUNCTION()`
- L117 _protected member_ `TSharedPtr<FCommonInputPreprocessor> CommonInputPreprocessor;`
- L120 _private prototype_ `bool Tick(float DeltaTime);`
- L122 _private prototype_ `void ShouldShowInputKeysChanged(IConsoleVariable* Var);`
- L124 _private prototype_ `FVector2D ClampPositionToViewport(const FVector2D& InPosition) const;`
- L127 _private prototype_ `bool PlatformSupportsInputType(ECommonInputType InInputType) const;` — Returns true if the current platform supports the input type
- L129 _private prototype_ `bool CheckForInputMethodThrashing(ECommonInputType NewInputType);`
- L131 _private prototype_ `void RecalculateCurrentInputType();`
- L133 _private prototype_ `void HandleOnVirtualKeyboardShown(FPlatformRect VkRect);`
- L134 _private prototype_ `void HandleOnVirtualKeyboardHidden();`
- L136 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L139 _private member_ `FInputMethodChangedDelegate OnInputMethodChanged;` — `UPROPERTY(BlueprintAssignable, Category = CommonInputSubsystem, meta = (AllowPrivateAccess))`
- L142 _private member_ `int32 NumberOfInputMethodChangesRecently = 0;` — `UPROPERTY(Transient)`
- L145 _private member_ `double LastInputMethodChangeTime = 0;` — `UPROPERTY(Transient)`
- L148 _private member_ `double LastTimeInputMethodThrashingBegan = 0;` — `UPROPERTY(Transient)`
- L152 _private member_ `ECommonInputType RawInputType;` — `UPROPERTY(Transient)` — The most recent input type that the user used, before considering locks and thrashing, but does consider PlatformSupportsInputType()
- L156 _private member_ `ECommonInputType CurrentInputType;` — `UPROPERTY(Transient)` — The current effective input type after considering input locks and thrashing
- L160 _private member_ `FName GamepadInputType;` — `UPROPERTY(Transient)`
- L164 _private member_ `bool bInputMethodLockedByThrashing = false;` — `UPROPERTY(Transient)` — Whether the last input type recalculation was locked out by input thrashing
- L168 _private member_ `TMap<FName, ECommonInputType> CurrentInputLocks;` — `UPROPERTY(Transient)`
- L170 _private member_ `TOptional<ECommonInputType> CurrentInputLock;`
- L173 _private member_ `TObjectPtr<UCommonInputActionDomainTable> ActionDomainTable;` — `UPROPERTY(Transient)`
- L177 _private member_ `bool bIsGamepadSimulatedClick;` — `UPROPERTY(Transient)` — Is the current click simulated by the gamepad's face button down/right (platform dependent)
- L187 _private member_ `static FPlatformInputSupportOverrideDelegate OnPlatformInputSupportOverride;` — The delegate that allows external systems to override which input methods are supported on this current platform. @param LocalPlayer								The Local Player. @param InputType									The current input type that is being tested. @param InOutCurrentPlatformInputSupportState		The state of if we support the input type as set by PlatformSupportsInputType() or the previous callee of this delegate. Note : Calling order is not guaranteed. Also, keep in mind that you might need to honor the previous callee's request to not support the input type being tested.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONINPUT_API`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMethodChangedDelegate, ECommonInputType, bNewInputType);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMethodChangedDelegate, ECommonInputType, bNewInputType);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FPlatformInputSupportOverrideDelegate, ULocalPlayer*, ECommonInputType, bool&);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FPlatformInputSupportOverrideDelegate, ULocalPlayer*, ECommonInputType, bool&);`
- L22 _delegate_ `DECLARE_EVENT_OneParam(FCommonInputPreprocessor, FGamepadChangeDetectedEvent, FName);`
- L22 _prototype_ `DECLARE_EVENT_OneParam(FCommonInputPreprocessor, FGamepadChangeDetectedEvent, FName);`
- L37 _delegate_ `DECLARE_EVENT_OneParam(UCommonInputSubsystem, FInputMethodChangedEvent, ECommonInputType);`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputTypeEnum.h` (Public)


#### enum `ECommonInputType`  
`enum class ECommonInputType : uint8`  
_L9-15_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `MouseAndKeyboard`
- L12 _public enumerator_ `Gamepad`
- L13 _public enumerator_ `Touch`
- L14 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L17 _prototype_ `ENUM_RANGE_BY_COUNT(ECommonInputType, ECommonInputType::Count);`

### `Plugins/Runtime/CommonUI/Source/CommonInput/Public/ICommonInputModule.h` (Public)


#### class `ICommonInputModule`  
`class ICommonInputModule : public IModuleInterface`  
_L11-51_
- inherits: `IModuleInterface`
- desc: Interface for the input state system.
- L22 _public function_ `static inline ICommonInputModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L40 _public function_ `static inline UCommonInputSettings& GetSettings()` — @return reference to Common Input settings
- L50 _protected prototype_ `virtual UCommonInputSettings* GetSettingsInstance() const = 0;`
