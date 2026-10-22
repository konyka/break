# Plugins / ControlRigPhysicsEditor

- module root: `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysicsEditor`
- headers: 3; symbols: 77
- symbol kinds: class=5, function=15, member=31, namespace=1, prototype=25
- PrivateDependencyModuleNames: ControlRig, ControlRigPhysics, CoreUObject, Engine, InputCore, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysicsEditor/Private/ControlRigPhysicsCVarBindings.h` (Private)


#### class `ControlRigPhysicsEditor::FCVarSimpleToggleBinding`  
`class FCVarSimpleToggleBinding : public TSharedFromThis<FCVarSimpleToggleBinding>`  
_L38-58_
- inherits: `TSharedFromThis<FCVarSimpleToggleBinding>`
- L41 _public prototype_ `FCVarSimpleToggleBinding(const FString& InCVarName, const FText& InTooltip);`
- L42 _public prototype_ `~FCVarSimpleToggleBinding();`
- L44 _public prototype_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget);`
- L46 _public prototype_ `TSharedRef<SWidget> BuildOverrideCell();`
- L47 _public prototype_ `TSharedRef<SWidget> BuildValueCell();`
- L50 _private prototype_ `void HandleCVarChanged(IConsoleVariable* InVariable);`
- L51 _private prototype_ `ECheckBoxState GetValueCheckState() const;`
- L52 _private prototype_ `void OnValueCheckStateChanged(ECheckBoxState NewState);`
- L54 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L55 _private member_ `FDelegateHandle OnChangedHandle;`
- L56 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L57 _private member_ `FText Tooltip;`

#### class `ControlRigPhysicsEditor::FCVarOverrideToggleBinding`  
`class FCVarOverrideToggleBinding : public TSharedFromThis<FCVarOverrideToggleBinding>`  
_L63-89_
- inherits: `TSharedFromThis<FCVarOverrideToggleBinding>`
- L66 _public prototype_ `FCVarOverrideToggleBinding(const FString& InCVarName, const FText& InTooltip);`
- L67 _public prototype_ `~FCVarOverrideToggleBinding();`
- L69 _public prototype_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget);`
- L71 _public prototype_ `TSharedRef<SWidget> BuildOverrideCell();`
- L72 _public prototype_ `TSharedRef<SWidget> BuildValueCell();`
- L75 _private prototype_ `void HandleCVarChanged(IConsoleVariable* InVariable);`
- L77 _private prototype_ `ECheckBoxState GetApplyCheckState() const;`
- L78 _private prototype_ `void OnApplyCheckStateChanged(ECheckBoxState NewState);`
- L80 _private prototype_ `ECheckBoxState GetValueCheckState() const;`
- L81 _private prototype_ `void OnValueCheckStateChanged(ECheckBoxState NewState);`
- L82 _private prototype_ `bool IsValueToggleEnabled() const;`
- L84 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L85 _private member_ `FDelegateHandle OnChangedHandle;`
- L86 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L87 _private member_ `FText Tooltip;`
- L88 _private member_ `int32 PendingValue = 1;`

#### class `ControlRigPhysicsEditor::FCVarOverrideNumericBinding`  
`template <typename NumericType> class FCVarOverrideNumericBinding : public TSharedFromThis<FCVarOverrideNumericBinding<NumericType>>`  
_L96-267_
- inherits: `TSharedFromThis<FCVarOverrideNumericBinding<NumericType>>`
- L100 _public function_ `FCVarOverrideNumericBinding( const FString& InCVarName, const FText& InTooltip, NumericType InDefaultValue, NumericType InMinAllowedValue) : Tooltip(InTooltip) , PendingValue(InDefaultValue) , MinAllowedValue(InMinAllowedValue)`
- L121 _public function_ `~FCVarOverrideNumericBinding()`
- L130 _public function_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget)`
- L141 _public function_ `TSharedRef<SWidget> BuildOverrideCell()`
- L151 _public function_ `TSharedRef<SWidget> BuildValueCell()`
- L166 _private function_ `NumericType ReadCVar() const`
- L179 _private function_ `void WriteCVar(NumericType Value)`
- L186 _private function_ `bool IsOverrideActive() const`
- L192 _private function_ `void HandleCVarChanged(IConsoleVariable* )`
- L209 _private function_ `ECheckBoxState GetApplyCheckState() const`
- L215 _private function_ `void OnApplyCheckStateChanged(ECheckBoxState NewState)`
- L232 _private function_ `TOptional<NumericType> GetDisplayValue() const`
- L242 _private function_ `void OnValueCommitted(NumericType NewValue, ETextCommit::Type )`
- L256 _private function_ `bool IsValueEntryEnabled() const`
- L261 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L262 _private member_ `FDelegateHandle OnChangedHandle;`
- L263 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L264 _private member_ `FText Tooltip;`
- L265 _private member_ `NumericType PendingValue;`
- L266 _private member_ `NumericType MinAllowedValue;`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace ControlRigPhysicsEditor`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysicsEditor/Private/ControlRigPhysicsEditorModule.h` (Private)


#### class `FControlRigPhysicsEditorModule`  
`class FControlRigPhysicsEditorModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `TSharedRef<SDockTab> OnSpawnDebugTab(const FSpawnTabArgs& SpawnTabArgs);`
- L20 _private prototype_ `void RegisterMenus();`

### `Plugins/Experimental/ControlRigPhysics/Source/ControlRigPhysicsEditor/Private/SControlRigPhysicsDebugWidget.h` (Private)


#### class `SControlRigPhysicsDebugWidget`  
`class SControlRigPhysicsDebugWidget : public SCompoundWidget`  
_L15-45_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SControlRigPhysicsDebugWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `FReply OnClearOverridesClicked();`
- L29 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarSimpleToggleBinding> EnableStepSolverBinding;` — Binding lifetime matches the widget. Kept as members so OnChangedDelegate bindings stay alive. The binding types are namespaced (ControlRigPhysicsEditor::) to avoid duplicate-symbol clashes with the parallel set declared in ControlRigDynamicsEditor.
- L30 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideNumericBinding<float>> FixedTimeStepBinding;`
- L31 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideNumericBinding<int32>> MaxTimeStepsBinding;`
- L32 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideNumericBinding<float>> MaxDeltaTimeBinding;`
- L33 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarSimpleToggleBinding> AllowVisualizationBinding;`
- L34 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowBodiesBinding;`
- L35 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowCentreOfMassBinding;`
- L36 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowJointsBinding;`
- L37 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowControlsBinding;`
- L38 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowActiveContactsBinding;`
- L39 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowInactiveContactsBinding;`
- L40 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowWorldObjectsBinding;`
- L41 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarOverrideToggleBinding> ShowWorldOverlapBoxBinding;`
- L42 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarSimpleToggleBinding> EnableDrawInterfaceInGameBinding;`
- L43 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarSimpleToggleBinding> AnimNodeControlRigDebugBinding;`
- L44 _private member_ `TSharedPtr<ControlRigPhysicsEditor::FCVarSimpleToggleBinding> ShowSimulationSpaceInfoBinding;`
