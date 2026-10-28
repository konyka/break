# Plugins / VCamCoreEditor

- module root: `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor`
- headers: 42; symbols: 358
- symbol kinds: class=39, delegate=6, enum=1, enumerator=3, function=20, member=54, namespace=60, prototype=166, struct=8, typedef=1
- PrivateDependencyModuleNames: AssetDefinition, CinematicCamera, ConcertSyncClient, ConcertSyncCore, CoreUObject, EditorFramework, Engine, EngineAssetDefinitions, EnhancedInput, InputBlueprintNodes, InputCore, KismetCompiler, LiveLinkInterface, PropertyEditor, Slate, SlateCore, ToolWidgets, UMG, UMGEditor, UnrealEd, VCamCore, VPUtilities
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/AssetDefinition/AssetDefinition_EditorOnlyModifier.h` (Private)


#### class `UAssetDefinition_EditorOnlyModifier`  
`class UAssetDefinition_EditorOnlyModifier : public UAssetDefinition_Blueprint`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/AssetDefinition/AssetDefinition_VCamModifier.h` (Private)


#### class `UAssetDefinition_VCamModifier`  
`class UAssetDefinition_VCamModifier : public UAssetDefinition_Blueprint`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/AssetDefinition/AssetDefinition_VCamStateSwitcherWidget.h` (Private)


#### class `UAssetDefinition_VCamStateSwitcherWidget`  
`class UAssetDefinition_VCamStateSwitcherWidget : public UAssetDefinition_Blueprint`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/AssetDefinition/AssetDefinition_VCamWidget.h` (Private)


#### class `UAssetDefinition_VCamWidget`  
`class UAssetDefinition_VCamWidget : public UAssetDefinition_Blueprint`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Compilation/CompilationExtensionManager.h` (Private)


#### class `UE::VCamCoreEditor::FCompilationExtensionManager`  
`class FCompilationExtensionManager : public TSharedFromThis<FCompilationExtensionManager>`  
_L12-23_
- inherits: `TSharedFromThis<FCompilationExtensionManager>`
- desc: Manages all of the plugin's UBlueprintExtensions making sure they are added when a Blueprint asset is loaded.
- L16 _public prototype_ `~FCompilationExtensionManager();`
- L18 _public prototype_ `void Init();`
- L22 _private prototype_ `void OnAssetLoaded(UObject* Object) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Compilation/ModifierCompilationBlueprintExtension.h` (Private)


#### class `UModifierCompilationBlueprintExtension`  
`class UModifierCompilationBlueprintExtension : public UBlueprintExtension`  
_L22-37_
- reflection: `UCLASS()`
- inherits: `UBlueprintExtension`
- desc: Validates modifier Blueprint when compiled. Actions: - Add a warning to every input action node that is not found in the MappingContext in the class defaults.
- L28 _public prototype_ `virtual void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext) override;`
- L31 _public prototype_ `static bool RequiresRecompileToDetectIssues(UBlueprint& Blueprint);`
- L35 _private prototype_ `static void ValidateEnhancedInputAction(FKismetCompilerContext& CompilerContext, UVCamModifier& OldModifierCDO, UK2Node_EnhancedInputAction& EnhancedInputActionNode);`
- L36 _private prototype_ `static bool DoesInputMappingContainReferencedAction(UVCamModifier& OldModifierCDO, UK2Node_EnhancedInputAction& EnhancedInputActionNode);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/DeviceID/InputDeviceDetectionProcessor.h` (Private)


#### struct `UE::VCamCoreEditor::FInputDeviceSelectionSettings`  
`struct FInputDeviceSelectionSettings`  
_L13-17_
- L16 _public member_ `bool bAllowAnalog = false;` — Whether analog input can cause detection of an input device. Some input devices trigger an analog input every tick.

#### class `UE::VCamCoreEditor::FInputDeviceDetectionProcessor`  
`class FInputDeviceDetectionProcessor : public IInputProcessor, public TSharedFromThis<FInputDeviceDetectionProcessor>`  
_L20-60_
- inherits: `IInputProcessor,TSharedFromThis<FInputDeviceDetectionProcessor>`
- desc: Puts itself at top of input stack and blocks any input. Used to easily determine input devices (except for mice).
- L27 _public prototype_ `static TSharedPtr<FInputDeviceDetectionProcessor> MakeAndRegister(FOnInputDeviceDetected OnInputDeviceDetectedDelegate, FInputDeviceSelectionSettings Settings);` — Registers a new input processor which will fire OnInputDeviceDetectedDelegate until Unregister is called.
- L29 _public prototype_ `void Unregister();` — Unregisters this input processor so it will no longer call OnInputDeviceDetectedDelegate nor intercept input.
- L32 _public prototype_ `void UpdateInputSettings(FInputDeviceSelectionSettings Settings);` — Called when the user changes the settings
- L35 _public function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override`
- L37 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L38 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L39 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L42 _public function_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override` — Detection for mice is undesirable
- L43 _public function_ `virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override`
- L44 _public function_ `virtual bool HandleMouseButtonUpEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override`
- L45 _public function_ `virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override`
- L46 _public function_ `virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override`
- L48 _public function_ `virtual const TCHAR* GetDebugName() const`
- L53 _private prototype_ `FInputDeviceDetectionProcessor(FOnInputDeviceDetected OnInputDeviceDetectedDelegate, FInputDeviceSelectionSettings Settings);`
- L56 _private member_ `FOnInputDeviceDetected OnInputDeviceDetectedDelegate;` — Called when any input other than mouse input is received
- L59 _private member_ `FInputDeviceSelectionSettings Settings;` — Usability settings exposed by input capturing button

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInputDeviceDetected, int32) struct FInputDeviceSelectionSettings { bool bAllowAnalog = false; };`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/DeviceID/SInputDeviceSelector.h` (Private)


#### class `UE::VCamCoreEditor::SInputDeviceSelector`  
`class SInputDeviceSelector : public SCompoundWidget`  
_L16-54_
- inherits: `SCompoundWidget`
- desc: Widgets for specifying device ID: has a button for listening for input from any device and numeric box for manual entry.
- L20 _public function_ `SLATE_BEGIN_ARGS(SInputDeviceSelector)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(TOptional<int32>, CurrentInputDeviceID) SLATE_EVENT(FOnInputDeviceIDChanged, OnInputDeviceIDChanged) SLATE_END_ARGS() virtual ~SInputDeviceSelector() override;` — That current input device value which is shown in the manual text edit box
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L35 _private member_ `FOnInputDeviceIDChanged OnInputDeviceIDChangedDelegate;` — Called by ListenForInput when any input other than mouse input is received
- L37 _private member_ `TSharedPtr<FInputDeviceDetectionProcessor> InputDeviceDetector;` — Used by button to detect pressed input.
- L40 _private member_ `TSharedPtr<SNumericEntryBox<int32>> ManualEnterBox;` — Text edit for manual user input
- L43 _private prototype_ `FReply ListenForInput();` — Starts listening for input from any device other than mouse - blocks the input.
- L45 _private prototype_ `void StopListeningForInput();` — Util for destroying InputDeviceDetector
- L47 _private prototype_ `void OnAllowAnalogInputSettingToggled();`
- L50 _private prototype_ `FSlateColor GetKeyIconColor() const;` — Tints button orange while listening
- L53 _private prototype_ `void OnDeviceIDManuallyCommited(int32 Value, ETextCommit::Type CommitType);` — Called when user commits value to ManualEnterBox.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInputDeviceIDChanged, int32) class SInputDeviceSelector : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SInputDeviceSelector) {} SLATE_ATTRIBUTE(TOptional<int32>, CurrentInputDeviceID) SLATE_EVENT(FOnInputDeviceIDChanged, OnInputDeviceIDChanged) SLATE_END_ARGS() virtual ~SInputDeviceSelector() override; void Construct(const FArguments& InArgs); private: FOnInputDeviceIDChanged OnInputDeviceIDChangedDelegate; TSharedPtr<FInputDeviceDetectionProcessor> InputDeviceDetector; TSharedPtr<SNumericEntryBox<int32>> ManualEnterBox; FReply ListenForInput(); void StopListeningForInput(); void OnAllowAnalogInputSettingToggled(); FSlateColor GetKeyIconColor() const;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/DeviceID/VCamInputDeviceIDTypeCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FVCamInputDeviceIDTypeCustomization`  
`class FVCamInputDeviceIDTypeCustomization : public IPropertyTypeCustomization`  
_L15-38_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes FVCamInputDeviceID to display a button the user can use to listen for input from any device and numeric box for manual entry
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Util that just creates an instance
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L30 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Holds a handle to the property being edited.
- L32 _private member_ `TSharedPtr<IPropertyUtilities> Utils;` — Needed to force refresh
- L35 _private prototype_ `TOptional<int32> GetCurrentInputDeviceID() const;` — Reads the current input device ID from PropertyHandle
- L37 _private prototype_ `void OnInputDeviceIDChanged(int32 InputDeviceID);` — Called when SInputDeviceSelector has determined a new input device ID.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/OutputProvider/ConnectionContainerDummy.h` (Private)


#### struct `FConnectionContainerDummy`  
`struct FConnectionContainerDummy`  
_L16-22_
- reflection: `USTRUCT()`
- desc: This dummy is needed so that the FConnectionTargetSettingsTypeCustomization can access FVCamConnection and use RequiredInterfaces, etc. for filtering suggestions. The detail customization systems implementation requires a valid parent handle to whatever contains the FVCamConnection, which is FConnectionContainerDummy's task.
- L21 _public member_ `FVCamConnection Connection;` — `UPROPERTY(EditAnywhere, Category = "Dummy")`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/OutputProvider/ConnectionRemapCustomization_StateSwitcher.h` (Private)


#### class `UE::VCamCoreEditor::FConnectionRemapCustomization_StateSwitcher`  
`class FConnectionRemapCustomization_StateSwitcher : public FConnectionRemapCustomization_VCamWidget`  
_L9-24_
- inherits: `FConnectionRemapCustomization_VCamWidget`
- L11 _private typedef_ `using Super = FConnectionRemapCustomization_VCamWidget;`
- L14 _public prototype_ `static TSharedRef<IConnectionRemapCustomization> Make();`
- L17 _public prototype_ `virtual bool CanGenerateGroup(const FShouldGenerateArgs& Args) const override;`
- L18 _public prototype_ `virtual void Customize(const FConnectionRemapCustomizationArgs& Args) override;`
- L23 _private prototype_ `void AddCurrentStateProperty(const FConnectionRemapCustomizationArgs& Args);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/OutputProvider/ConnectionRemapCustomization_VCamWidget.h` (Private)


#### class `UE::VCamCoreEditor::FConnectionRemapCustomization_VCamWidget`  
`class FConnectionRemapCustomization_VCamWidget : public IConnectionRemapCustomization`  
_L10-26_
- inherits: `IConnectionRemapCustomization`
- L14 _public prototype_ `static TSharedRef<IConnectionRemapCustomization> Make();`
- L17 _public prototype_ `virtual bool CanGenerateGroup(const FShouldGenerateArgs& Args) const override;`
- L18 _public prototype_ `virtual void Customize(const FConnectionRemapCustomizationArgs& Args) override;`
- L23 _private member_ `TWeakObjectPtr<UVCamWidget> Widget;`
- L25 _private prototype_ `void OnTargetSettingsChanged(const FVCamConnectionTargetSettings& NewConnectionTargetSettings, FName ConnectionName) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/OutputProvider/ConnectionRemapUtilsImpl.h` (Private)


#### class `UE::VCamCoreEditor::FConnectionRemapUtilsImpl`  
`class FConnectionRemapUtilsImpl : public IConnectionRemapUtils`  
_L11-27_
- inherits: `IConnectionRemapUtils`
- L15 _public prototype_ `FConnectionRemapUtilsImpl(TSharedRef<IDetailLayoutBuilder> Builder);`
- L18 _public prototype_ `virtual void AddConnection(FAddConnectionArgs Args) override;`
- L19 _public prototype_ `virtual FSlateFontInfo GetRegularFont() const override;`
- L20 _public prototype_ `virtual void ForceRefreshProperties() const override;`
- L25 _private member_ `TWeakPtr<IDetailLayoutBuilder> Builder;`
- L26 _private member_ `TMap<FName, TSharedPtr<TStructOnScope<FConnectionContainerDummy>>> AddedConnections;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/OutputProvider/OutputProviderLayoutCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FOutputProviderLayoutCustomization`  
`class FOutputProviderLayoutCustomization : public IDetailCustomization`  
_L19-66_
- inherits: `IDetailCustomization`
- desc: Exposes all VCam widgets' connection settings for as long as the output provider has a valid widget.
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L34 _private member_ `TWeakObjectPtr<UVCamOutputProviderBase> CustomizedOutputProvider;` — Exactly 1 object can be customized at a time.
- L36 _private member_ `TWeakPtr<IDetailLayoutBuilder> WeakDetailBuilder;`
- L39 _private member_ `FDelegateHandle OnActivatedDelegateHandle;` — Handle to UVCamOutputProviderBase::OnActivatedDelegate
- L49 _private member_ `TMap<TWeakObjectPtr<UVCamWidget>, FWidgetData> EditableWidgets;` — The widgets added to the details panel
- L56 _private member_ `bool bRequestedRefresh = false;` — Whether a rebuild was already requested this tick. The output provider may activate & deactivate multiple times in a single tick so we combine them all. By deferring the update not only do we save useless updates, we can also detect whether the owning object was destroyed as part of an undo.
- L58 _private prototype_ `FDetailWidgetRow ExtendWidgetsRow(IDetailLayoutBuilder& DetailBuilder, IDetailGroup& WidgetGroup);`
- L59 _private prototype_ `void RebuildWidgetData();`
- L60 _private prototype_ `void GenerateWidgetRows(IDetailGroup& RootWidgetGroup, IDetailLayoutBuilder& DetailBuilder);`
- L62 _private prototype_ `void OnActivationChanged(bool bNewIsActivated);`
- L63 _private prototype_ `void ForceRefreshDetailsIfSafe() const;`
- L65 _private prototype_ `static void ClearWidgetData(TMap<TWeakObjectPtr<UVCamWidget>, FWidgetData>& InEditableWidgets);`

#### struct `UE::VCamCoreEditor::FOutputProviderLayoutCustomization::FWidgetData`  
`struct FWidgetData`  
_L41-47_
- L43 _public member_ `TSharedPtr<IConnectionRemapCustomization> Customization;`
- L46 _public member_ `TSharedPtr<FConnectionRemapUtilsImpl> RemapUtils;` — Utils for IConnectionRemapCustomizations

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/StateSwitcher/ConnectionTargetNodeBuilder.h` (Private)


#### class `UE::VCamCoreEditor::FConnectionTargetNodeBuilder`  
`class FConnectionTargetNodeBuilder : public IDetailCustomNodeBuilder , public TSharedFromThis<FConnectionTargetNodeBuilder>`  
_L18-52_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FConnectionTargetNodeBuilder>`
- desc: Customizes the FWidgetConnectionConfig::ConnectionTargets property. Makes every key widget be a drop-down to the connection exposed its corresponding VCamWidget.
- L24 _public prototype_ `FConnectionTargetNodeBuilder(TSharedRef<IPropertyHandle> ConnectionTargets, TAttribute<TArray<FName>> ChooseableConnections, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L26 _public prototype_ `void InitDelegates();`
- L29 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;`
- L30 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L31 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L32 _public function_ `virtual FName GetName() const override`
- L38 _private member_ `const TSharedRef<IPropertyHandle> ConnectionTargets;` — Handle to FWidgetConnectionConfig::ConnectionTargets
- L41 _private member_ `const TAttribute<TArray<FName>> ChooseableConnections;` — Gets the list of connections on the VCamWidget
- L43 _private member_ `const FSlateFontInfo RegularFont;`
- L44 _private member_ `const TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L46 _private member_ `FSimpleDelegate OnRegenerateChildren;`
- L48 _private prototype_ `TArray<FString> GetChooseableConnectionsAsStringArray() const;`
- L50 _private prototype_ `void ScheduleChildRebuild();`
- L51 _private prototype_ `void RebuilChildren();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/StateSwitcher/SStringSelectionComboBox.h` (Private)


#### class `UE::VCamCoreEditor::SStringSelectionComboBox`  
`class SStringSelectionComboBox : public SSearchableComboBox`  
_L9-39_
- inherits: `SSearchableComboBox`
- L13 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, const FString& );`
- L15 _public function_ `SLATE_BEGIN_ARGS(SStringSelectionComboBox)`
- L17 _public prototype_ `SLATE_ATTRIBUTE(FString, SelectedItem) SLATE_ATTRIBUTE(TArray<FString>, ItemList) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private member_ `TAttribute<TArray<FString>> ItemListAttribute;`
- L29 _private member_ `TArray<TSharedPtr<FString>> ItemList;` — Wraps ItemListAttribute and is fed into SSearchableComboBox API.
- L31 _private member_ `FOnItemSelected OnItemSelected;`
- L32 _private member_ `FSlateFontInfo Font;`
- L34 _private prototype_ `void RefreshItemList();`
- L36 _private prototype_ `void OnSelectionChangedInternal(TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo);`
- L37 _private prototype_ `TSharedRef<SWidget> OnGenerateComboWidget( TSharedPtr<FString> InComboString );`
- L38 _private prototype_ `EVisibility GetSearchVisibility() const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, const FString& );`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/StateSwitcher/VCamStateSwitcherWidgetCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FVCamStateSwitcherWidgetCustomization`  
`class FVCamStateSwitcherWidgetCustomization : public IDetailCustomization`  
_L10-20_
- inherits: `IDetailCustomization`
- desc: Makes CurrentState a drop-down based on the available states.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `void CustomizeCurrentState(IDetailLayoutBuilder& DetailBuilder);`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/StateSwitcher/WidgetConnectionConfigTypeCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FWidgetConnectionConfigTypeCustomization`  
`class FWidgetConnectionConfigTypeCustomization : public IPropertyTypeCustomization`  
_L14-29_
- inherits: `IPropertyTypeCustomization`
- desc: Makes the "Virtual Camera" category appear first on the actor properties.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _private prototype_ `void CustomizeConnectionTargetsReferenceProperty(TSharedRef<IPropertyHandle> StructPropertyHandle, TSharedRef<IPropertyHandle> ConnectionTargetsPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) const;`
- L28 _private prototype_ `TAttribute<TArray<FName>> CreateGetConnectionsFromChildWidgetAttribute(TSharedRef<IPropertyHandle> StructPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/TargetSettings/ConnectionTargetSettingsTypeCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FConnectionTargetSettingsTypeCustomization`  
`class FConnectionTargetSettingsTypeCustomization : public IPropertyTypeCustomization`  
_L21-76_
- inherits: `IPropertyTypeCustomization`
- desc: If the user as selected an actor with a VCamComponent or a Blueprint with a VCamComponent in the content browser, this will create drop-downs for the modifier and connection point properties instead of just text boxes.
- L27 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedRef<ConnectionTargetContextFinding::IContextFinderForConnectionTargetSettings> ContextFinder);`
- L30 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L36 _private member_ `TSharedRef<ConnectionTargetContextFinding::IContextFinderForConnectionTargetSettings> ContextFinder;`
- L38 _private prototype_ `FConnectionTargetSettingsTypeCustomization(TSharedRef<ConnectionTargetContextFinding::IContextFinderForConnectionTargetSettings> ContextFinder);`
- L40 _private prototype_ `void AddScopeRow(IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L42 _private prototype_ `void CustomizeModifier( TSharedRef<IPropertyHandle> ModifierHandle, IDetailPropertyRow& Row, TSharedRef<IPropertyHandle> ConnectionTargetSettingsStructHandle, TSharedRef<IPropertyUtilities> PropertyUtils ) const;`
- L48 _private prototype_ `void CustomizeConnectionPoint( TSharedRef<IPropertyHandle> ModifierHandle, TSharedRef<IPropertyHandle> ConnectionPointHandle, IDetailPropertyRow& Row, TSharedRef<IPropertyHandle> ConnectionTargetSettingsStructHandle, TSharedRef<IPropertyUtilities> PropertyUtils ) const;`
- L68 _private prototype_ `static FSelectedComponentInfo GetUserFocusedConnectionPointSource();` — Gets component from 1. Blueprint class selected in content browser or 2. selected actor in world.
- L70 _private prototype_ `void CustomizeNameProperty( TSharedRef<IPropertyHandle> PropertyHandle, IDetailPropertyRow& Row, TAttribute<TArray<FName>> GetOptionsAttr, TAttribute<bool> HasDataSourceAttr ) const;`

#### enum `UE::VCamCoreEditor::FConnectionTargetSettingsTypeCustomization::EComponentSource`  
`enum class EComponentSource`  
_L56-61_
- L58 _public enumerator_ `None`
- L59 _public enumerator_ `ContentBrowser`
- L60 _public enumerator_ `LevelSelection`

#### struct `UE::VCamCoreEditor::FConnectionTargetSettingsTypeCustomization::FSelectedComponentInfo`  
`struct FSelectedComponentInfo`  
_L62-66_
- L64 _public member_ `EComponentSource ComponentSource = EComponentSource::None;`
- L65 _public member_ `TWeakObjectPtr<UVCamComponent> Component;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L12 _namespace_ `namespace ConnectionTargetContextFinding` (scope `UE::VCamCoreEditor`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/TargetSettings/IContextFinderForConnectionTargetSettings.h` (Private)


#### class `UE::VCamCoreEditor::ConnectionTargetContextFinding::IContextFinderForConnectionTargetSettings`  
`class IContextFinderForConnectionTargetSettings : public TSharedFromThis<IContextFinderForConnectionTargetSettings>`  
_L18-31_
- inherits: `TSharedFromThis<IContextFinderForConnectionTargetSettings>`
- desc: Used by FConnectionTargetSettingsTypeCustomization to find a FVCamConnection to limit the options of selectable targets according to the connection's constraints.
- L23 _public prototype_ `virtual void FindAndProcessContext( const TSharedRef<IPropertyHandle>& ConnectionTargetSettingsStructHandle, IPropertyUtilities& PropertyUtils, TFunctionRef<void(const FVCamConnection& Connection)> ProcessWithContext, TFunctionRef<void()> ProcessWithoutContext ) = 0;` — Tries to find a context FVCamConnection if possible calls either ProcessWithContext or ProcessWithoutContext (but not both).
- L30 _public prototype_ `virtual ~IContextFinderForConnectionTargetSettings() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L12 _namespace_ `namespace ConnectionTargetContextFinding` (scope `UE::VCamCoreEditor`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/TargetSettings/InsideVCamConnectionContextFinder.h` (Private)


#### class `UE::VCamCoreEditor::ConnectionTargetContextFinding::FInsideVCamConnectionContextFinder`  
`class FInsideVCamConnectionContextFinder : public IContextFinderForConnectionTargetSettings`  
_L10-22_
- inherits: `IContextFinderForConnectionTargetSettings`
- desc: Figures out whether the FConnectionTargetSettings are contained in a FVCamConnection
- L15 _public prototype_ `virtual void FindAndProcessContext( const TSharedRef<IPropertyHandle>& ConnectionTargetSettingsStructHandle, IPropertyUtilities& PropertyUtils, TFunctionRef<void(const FVCamConnection& Connection)> ProcessWithContext, TFunctionRef<void()> ProcessWithoutContext ) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L7 _namespace_ `namespace ConnectionTargetContextFinding` (scope `UE::VCamCoreEditor`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/TargetSettings/ListOfContextFinders.h` (Private)


#### class `UE::VCamCoreEditor::ConnectionTargetContextFinding::FListOfContextFinders`  
`class FListOfContextFinders : public IContextFinderForConnectionTargetSettings`  
_L13-33_
- inherits: `IContextFinderForConnectionTargetSettings`
- desc: Goes through array of implementations and calls ProcessWithContext on the first one which finds a FVCamConnection (it is expected that only one will find a struct).
- L17 _public function_ `FListOfContextFinders(TArray<TSharedRef<IContextFinderForConnectionTargetSettings>> Implementations) : Implementations(MoveTemp(Implementations))`
- L22 _public prototype_ `virtual void FindAndProcessContext( const TSharedRef<IPropertyHandle>& ConnectionTargetSettingsStructHandle, IPropertyUtilities& PropertyUtils, TFunctionRef<void(const FVCamConnection& Connection)> ProcessWithContext, TFunctionRef<void()> ProcessWithoutContext ) override;`
- L32 _private member_ `TArray<TSharedRef<IContextFinderForConnectionTargetSettings>> Implementations;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L10 _namespace_ `namespace ConnectionTargetContextFinding` (scope `UE::VCamCoreEditor`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/TargetSettings/StateSwitcherContextFinder.h` (Private)


#### class `UE::VCamCoreEditor::ConnectionTargetContextFinding::FStateSwitcherContextFinder`  
`class FStateSwitcherContextFinder : public IContextFinderForConnectionTargetSettings`  
_L10-22_
- inherits: `IContextFinderForConnectionTargetSettings`
- desc: Figures out whether the FConnectionTargetSettings are contained in a FWidgetConnectionConfig
- L15 _public prototype_ `virtual void FindAndProcessContext( const TSharedRef<IPropertyHandle>& ConnectionTargetSettingsStructHandle, IPropertyUtilities& PropertyUtils, TFunctionRef<void(const FVCamConnection& Connection)> ProcessWithContext, TFunctionRef<void()> ProcessWithoutContext ) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L7 _namespace_ `namespace ConnectionTargetContextFinding` (scope `UE::VCamCoreEditor`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/VCamBaseActorCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FVCamBaseActorCustomization`  
`class FVCamBaseActorCustomization : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- desc: Makes the "Virtual Camera" category appear first on the actor properties.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/VCamInputProfileCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FVCamInputProfileCustomization`  
`class FVCamInputProfileCustomization : public IPropertyTypeCustomization`  
_L19-45_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `FVCamInputProfileCustomization();`
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L28 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L31 _protected member_ `TSharedPtr<IPropertyHandle> CachedStructPropertyHandle;`
- L32 _protected member_ `TSharedPtr<IPropertyHandle> MappableKeyOverridesHandle;`
- L34 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ProfileComboBox;`
- L35 _protected member_ `TArray<TSharedPtr<FString>> ProfileComboList;`
- L37 _protected prototype_ `void BuildProfileComboList();`
- L39 _protected prototype_ `bool IsProfileEnabled() const;`
- L40 _protected prototype_ `void OnProfileChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L41 _protected prototype_ `TSharedRef<SWidget> MakeProfileComboWidget(TSharedPtr<FString> InItem);`
- L43 _protected prototype_ `FText GetProfileComboBoxContent() const;`
- L44 _protected prototype_ `TSharedPtr<FString> GetProfileString(void* StructValueData) const;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/VCamViewportLockerTypeCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FVCamViewportLockerTypeCustomization`  
`class FVCamViewportLockerTypeCustomization : public IPropertyTypeCustomization`  
_L14-24_
- inherits: `IPropertyTypeCustomization`
- desc: Just inlines the TMap (since the keys cannot be changed).
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/WidgetReference/ChildWidgetReferenceCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FChildWidgetReferenceCustomization`  
`class FChildWidgetReferenceCustomization : public IPropertyTypeCustomization`  
_L12-30_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L20 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L25 _protected prototype_ `virtual TArray<UWidget*> GetSelectableChildWidgets(TWeakObjectPtr<UUserWidget> Widget) const;`
- L29 _private prototype_ `TArray<FString> GetPropertyItemList(TWeakObjectPtr<UUserWidget> Widget) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Customizations/WidgetReference/VCamChildWidgetReferenceCustomization.h` (Private)


#### class `UE::VCamCoreEditor::FVCamChildWidgetReferenceCustomization`  
`class FVCamChildWidgetReferenceCustomization : public FChildWidgetReferenceCustomization`  
_L11-22_
- inherits: `FChildWidgetReferenceCustomization`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _protected prototype_ `virtual TArray<UWidget*> GetSelectableChildWidgets(TWeakObjectPtr<UUserWidget> Widget) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/EditorOnlyVCamModifierBlueprint.h` (Private)


#### class `UEditorOnlyVCamModifierBlueprint`  
`class UEditorOnlyVCamModifierBlueprint : public UBlueprint`  
_L10-27_
- reflection: `UCLASS()`
- inherits: `UBlueprint`
- desc: This Blueprint class allows UEditorOnlyVCamModifier Blueprints to use editor-only functions.
- L16 _public function_ `virtual bool IsEditorOnly() const override`
- L24 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override` — UBlueprint interface
- L25 _public function_ `virtual bool AlwaysCompileOnLoad() const override`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Factories/EditorOnlyModifierFactory.h` (Private)


#### class `UEditorOnlyModifierFactory`  
`class UEditorOnlyModifierFactory : public UVCamObjectWithInputFactory`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `UVCamObjectWithInputFactory`
- L17 _public prototype_ `UEditorOnlyModifierFactory();`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetToolTip() const override;`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Factories/VCamModifierFactory.h` (Private)


#### class `UVCamModifierFactory`  
`class UVCamModifierFactory : public UVCamObjectWithInputFactory`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UVCamObjectWithInputFactory`
- L14 _public prototype_ `UVCamModifierFactory();`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetToolTip() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Factories/VCamObjectWithInputFactory.h` (Private)


#### class `UVCamObjectWithInputFactory`  
`class UVCamObjectWithInputFactory : public UFactory`  
_L10-28_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L16 _public member_ `TSubclassOf<UObject> ParentClass;` — `UPROPERTY(EditAnywhere, Category="BlueprintVirtualSubjectFactory", meta=(AllowAbstract = "", BlueprintBaseOnly = ""))` — The parent class of the created blueprint
- L19 _public member_ `TObjectPtr<UInputMappingContext> InputMappingContext;` — `UPROPERTY(BlueprintReadWrite, Category = "VCam Modifier Factory")`
- L22 _public member_ `int32 MappingPriority;` — `UPROPERTY(BlueprintReadWrite, Category = "VCam Modifier Factory")`
- L25 _public prototype_ `virtual bool ConfigureProperties() override;`
- L26 _public prototype_ `virtual TArray<FAssetCategoryPath> GetAssetMenuPathsForCategory(FName InCategory) const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Factories/VCamStateSwitcherWidgetFactory.h` (Private)


#### class `UVCamStateSwitcherWidgetFactory`  
`class UVCamStateSwitcherWidgetFactory : public UVCamWidgetFactory`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UVCamWidgetFactory`
- L14 _public prototype_ `UVCamStateSwitcherWidgetFactory();`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Factories/VCamWidgetFactory.h` (Private)


#### class `UVCamWidgetFactory`  
`class UVCamWidgetFactory : public UVCamObjectWithInputFactory`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UVCamObjectWithInputFactory`
- L14 _public prototype_ `UVCamWidgetFactory();`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetToolTip() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/LogVCamEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamEditor, Log, All);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/Util/SharedPropertyCustomizationUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L12 _namespace_ `namespace StateSwitcher` (scope `UE::VCamCoreEditor`)
- L15 _prototype_ `void CustomizeCurrentState(UVCamStateSwitcherWidget& StateSwitcher, IDetailPropertyRow& DetailPropertyRow, TSharedRef<IPropertyHandle> CurrentStatePropertyHandle, const FSlateFontInfo& RegularFont);` (scope `UE::VCamCoreEditor::StateSwitcher`) — Shared logic for customizing UVCamStateSwitcherWidget::CurrentState to display a drop-down widget.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Private/VCamCoreEditorModule.h` (Private)


#### class `UE::VCamCoreEditor::FVCamCoreEditorModule`  
`class FVCamCoreEditorModule : public IVCamCoreEditorModule`  
_L19-56_
- inherits: `IVCamCoreEditorModule`
- L23 _public function_ `static FVCamCoreEditorModule& Get()`
- L28 _public prototype_ `TSharedPtr<IConnectionRemapCustomization> CreateConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class) const;`
- L31 _public prototype_ `virtual void StartupModule() override;`
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _public prototype_ `virtual void RegisterConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class, FGetConnectionRemappingCustomization GetterDelegate) override;`
- L37 _public prototype_ `virtual void UnregisterConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class) override;`
- L38 _public prototype_ `virtual uint32 GetAdvancedAssetCategoryForVCam() const override;`
- L44 _private member_ `TMap<TWeakObjectPtr<UClass>, FGetConnectionRemappingCustomization> ConnectionRemappingCustomizationFactories;` — Maps pointer to UVCamWidget classes
- L46 _private member_ `TSharedPtr<FCompilationExtensionManager> CompilationExtensionManager;`
- L48 _private prototype_ `void RegisterAutoGeneratedDefaultEvents();`
- L49 _private prototype_ `void RegisterCustomizations();`
- L50 _private prototype_ `void RegisterDefaultConnectionRemappingCustomizations();`
- L52 _private prototype_ `void UnregisterCustomizations();`
- L54 _private prototype_ `void RegisterMultiUserFilters();`
- L55 _private prototype_ `ETransactionFilterResult ShouldObjectBeTransacted(const FConcertTransactionFilterArgs& FilterArgs) const;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Public/Customization/IConnectionRemapCustomization.h` (Public)


#### struct `UE::VCamCoreEditor::FTargetConnectionDisplaySettings`  
`struct FTargetConnectionDisplaySettings`  
_L16-19_
- L18 _public member_ `bool bOnlyShowManuallyConfiguredConnections = true;`

#### struct `UE::VCamCoreEditor::FShouldGenerateArgs`  
`struct FShouldGenerateArgs`  
_L21-25_
- L23 _public member_ `TWeakObjectPtr<UVCamWidget> CustomizedWidget;`
- L24 _public member_ `FTargetConnectionDisplaySettings DisplaySettings;`

#### struct `UE::VCamCoreEditor::FConnectionRemapCustomizationArgs`  
`struct FConnectionRemapCustomizationArgs`  
_L27-38_
- L30 _public member_ `IDetailLayoutBuilder& Builder;` — Use to register custom layouts or add external object / struct data.
- L32 _public member_ `IDetailGroup& WidgetGroup;` — Builder for the group under which to add the widget's data.
- L34 _public member_ `TSharedRef<IConnectionRemapUtils> Utils;`
- L35 _public member_ `TWeakObjectPtr<UVCamWidget> CustomizedWidget;`
- L37 _public member_ `FTargetConnectionDisplaySettings DisplaySettings;`

#### class `UE::VCamCoreEditor::IConnectionRemapCustomization`  
`class IConnectionRemapCustomization : public TSharedFromThis<IConnectionRemapCustomization>`  
_L46-57_
- inherits: `TSharedFromThis<IConnectionRemapCustomization>`
- desc: Implements support for customizing the connection target points of specific widget types. Instances are created when a widget needs customization and kept alive until 1. the widget becomes invalid or 2. the details panel displays a new object; stays alive across calls to IDetailBuilder::ForceRefreshDetails.
- L51 _public prototype_ `virtual bool CanGenerateGroup(const FShouldGenerateArgs& Args) const = 0;` — Whether a group should be generated for this widget
- L54 _public prototype_ `virtual void Customize(const FConnectionRemapCustomizationArgs& Args) = 0;` — Adds rows for CustomizedWidget
- L56 _public prototype_ `virtual ~IConnectionRemapCustomization() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCoreEditor` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Public/Customization/IConnectionRemapUtils.h` (Public)


#### struct `UE::VCamCoreEditor::FAddConnectionArgs`  
`struct FAddConnectionArgs`  
_L16-38_
- desc: Data for requesting to add connection target settings to details panel
- L18 _public member_ `IDetailGroup& DetailGroup;`
- L21 _public member_ `FName ConnectionName;` — Unique ID used for mapping data
- L23 _public member_ `const FVCamConnection& ConnectionData;` — Contains the data to display
- L26 _public member_ `FOnTargetSettingsChanged OnTargetSettingsChangedDelegate;` — `UPROPERTY()`
- L29 _public member_ `FSlateFontInfo Font;` — The font to use for displaying property texts.
- L31 _public function_ `FAddConnectionArgs(IDetailGroup& DetailGroup, FName ConnectionName, const FVCamConnection& ConnectionData, FOnTargetSettingsChanged OnTargetSettingsChangedDelegate, FSlateFontInfo Font) : DetailGroup(DetailGroup) , ConnectionName(ConnectionName) , ConnectionData(ConnectionData) , OnTargetSettingsChangedDelegate(MoveTemp(OnTargetSettingsChangedDelegate)) , Font(MoveTemp(Font))`

#### class `UE::VCamCoreEditor::IConnectionRemapUtils`  
`class IConnectionRemapUtils : public TSharedFromThis<IConnectionRemapUtils>`  
_L41-58_
- inherits: `TSharedFromThis<IConnectionRemapUtils>`
- desc: Passed to IConnectionTargetRemappingCustomizers to re-use functionality.
- L46 _public prototype_ `virtual void AddConnection(FAddConnectionArgs Params) = 0;` — Adds a property row representing FVCamConnection::TargetSettings to DetailGroup.
- L49 _public prototype_ `virtual FSlateFontInfo GetRegularFont() const = 0;` — @return the font used for properties and details
- L55 _public prototype_ `virtual void ForceRefreshProperties() const = 0;` — Refreshes the details view and regenerates all the customized layouts Use only when you need to remove or add complicated dynamic items
- L57 _public prototype_ `virtual ~IConnectionRemapUtils() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTargetSettingsChanged, const FVCamConnectionTargetSettings& NewSettings);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTargetSettingsChanged, const FVCamConnectionTargetSettings& NewSettings);` (scope `UE::VCamCoreEditor`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Public/EditorOnlyVCamModifier.h` (Public)


#### class `UEditorOnlyVCamModifier`  
`class UEditorOnlyVCamModifier : public UVCamBlueprintModifier`  
_L12-20_
- reflection: `UCLASS(Abstract)`
- inherits: `UVCamBlueprintModifier`
- desc: A modifier that only exists in uncooked builds.
- L18 _public function_ `virtual bool IsEditorOnly() const override`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Public/IVCamCoreEditorModule.h` (Public)


#### class `UE::VCamCoreEditor::IVCamCoreEditorModule`  
`class IVCamCoreEditorModule : public IModuleInterface`  
_L18-42_
- inherits: `IModuleInterface`
- desc: Passed to IConnectionTargetRemappingCustomizers to re-use functionality.
- L22 _public function_ `static IVCamCoreEditorModule& Get()`
- L35 _public prototype_ `virtual void RegisterConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class, FGetConnectionRemappingCustomization GetterDelegate) = 0;` — Registers a specific remapping customization for a class. At most one customization is used per VCamWidget class. To determine a widget's customization, the class's hierarchy is navigated recursively until a customization is found that is registered with a parent class. Cannot override already registered customizations. You'd have to call UnregisterConnectionTargetRemappingCustomizer first. @param Class The subclass to register for - cannot be UVCamWidget and @param GetterDelegate The factory to invoke whenever a widget is customized.
- L36 _public prototype_ `virtual void UnregisterConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class) = 0;`
- L39 _public prototype_ `virtual uint32 GetAdvancedAssetCategoryForVCam() const = 0;` — Gets the asset category that assets are grouped under.
- L41 _public prototype_ `virtual ~IVCamCoreEditorModule() override = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace VCamCoreEditor` (scope `UE`)
- L15 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IConnectionRemapCustomization>, FGetConnectionRemappingCustomization) class IVCamCoreEditorModule : public IModuleInterface { public: static IVCamCoreEditorModule& Get() { return FModuleManager::Get().GetModuleChecked<IVCamCoreEditorModule>("VCamCoreEditor"); } virtual void RegisterConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class, FGetConnectionRemappingCustomization GetterDelegate) = 0; virtual void UnregisterConnectionRemapCustomization(TSubclassOf<UVCamWidget> Class) = 0; virtual uint32 GetAdvancedAssetCategoryForVCam() const = 0; virtual ~IVCamCoreEditorModule() override = default; };`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCoreEditor/Public/VCamEditorLibrary.h` (Public)


#### class `UVCamEditorLibrary`  
`class UVCamEditorLibrary : public UBlueprintFunctionLibrary`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L22 _public prototype_ `static void GetAllVCamComponentsInLevel(TArray<UVCamComponent*>& VCamComponents);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Find all loaded VCam Components own by an actor in the world editor. Exclude actor that are pending kill, in PIE, PreviewEditor, ... @param VCamComponents Output List of found VCamComponents
