# Plugins / ControlRigDynamicsEditor

- module root: `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamicsEditor`
- headers: 3; symbols: 101
- symbol kinds: class=6, function=15, member=41, namespace=1, prototype=38
- PrivateDependencyModuleNames: ControlRig, ControlRigDynamics, CoreUObject, Engine, InputCore, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamicsEditor/Private/ControlRigDynamicsCVarBindings.h` (Private)


#### class `ControlRigDynamicsEditor::FCVarSimpleToggleBinding`  
`class FCVarSimpleToggleBinding : public TSharedFromThis<FCVarSimpleToggleBinding>`  
_L40-60_
- inherits: `TSharedFromThis<FCVarSimpleToggleBinding>`
- L43 _public prototype_ `FCVarSimpleToggleBinding(const FString& InCVarName, const FText& InTooltip);`
- L44 _public prototype_ `~FCVarSimpleToggleBinding();`
- L46 _public prototype_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget);`
- L48 _public prototype_ `TSharedRef<SWidget> BuildOverrideCell();`
- L49 _public prototype_ `TSharedRef<SWidget> BuildValueCell();`
- L52 _private prototype_ `void HandleCVarChanged(IConsoleVariable* InVariable);`
- L53 _private prototype_ `ECheckBoxState GetValueCheckState() const;`
- L54 _private prototype_ `void OnValueCheckStateChanged(ECheckBoxState NewState);`
- L56 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L57 _private member_ `FDelegateHandle OnChangedHandle;`
- L58 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L59 _private member_ `FText Tooltip;`

#### class `ControlRigDynamicsEditor::FCVarOverrideToggleBinding`  
`class FCVarOverrideToggleBinding : public TSharedFromThis<FCVarOverrideToggleBinding>`  
_L65-91_
- inherits: `TSharedFromThis<FCVarOverrideToggleBinding>`
- L68 _public prototype_ `FCVarOverrideToggleBinding(const FString& InCVarName, const FText& InTooltip);`
- L69 _public prototype_ `~FCVarOverrideToggleBinding();`
- L71 _public prototype_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget);`
- L73 _public prototype_ `TSharedRef<SWidget> BuildOverrideCell();`
- L74 _public prototype_ `TSharedRef<SWidget> BuildValueCell();`
- L77 _private prototype_ `void HandleCVarChanged(IConsoleVariable* InVariable);`
- L79 _private prototype_ `ECheckBoxState GetApplyCheckState() const;`
- L80 _private prototype_ `void OnApplyCheckStateChanged(ECheckBoxState NewState);`
- L82 _private prototype_ `ECheckBoxState GetValueCheckState() const;`
- L83 _private prototype_ `void OnValueCheckStateChanged(ECheckBoxState NewState);`
- L84 _private prototype_ `bool IsValueToggleEnabled() const;`
- L86 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L87 _private member_ `FDelegateHandle OnChangedHandle;`
- L88 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L89 _private member_ `FText Tooltip;`
- L90 _private member_ `int32 PendingValue = 1;`

#### class `ControlRigDynamicsEditor::FCVarEnumDropdownBinding`  
`class FCVarEnumDropdownBinding : public TSharedFromThis<FCVarEnumDropdownBinding>`  
_L98-134_
- inherits: `TSharedFromThis<FCVarEnumDropdownBinding>`
- L101 _public prototype_ `FCVarEnumDropdownBinding( const FString& InCVarName, const FText& InTooltip, UEnum* InEnum, const FString& InDefaultWhenApplied);`
- L106 _public prototype_ `~FCVarEnumDropdownBinding();`
- L108 _public prototype_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget);`
- L110 _public prototype_ `TSharedRef<SWidget> BuildOverrideCell();`
- L111 _public prototype_ `TSharedRef<SWidget> BuildValueCell();`
- L114 _private prototype_ `void HandleCVarChanged(IConsoleVariable* InVariable);`
- L116 _private prototype_ `ECheckBoxState GetApplyCheckState() const;`
- L117 _private prototype_ `void OnApplyCheckStateChanged(ECheckBoxState NewState);`
- L118 _private prototype_ `bool IsValueComboEnabled() const;`
- L120 _private prototype_ `TSharedRef<SWidget> OnGenerateComboItem(TSharedPtr<FString> InItem);`
- L121 _private prototype_ `void OnComboSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type SelectInfo);`
- L122 _private prototype_ `FText GetComboSelectedText() const;`
- L123 _private prototype_ `TSharedPtr<FString> FindOptionForString(const FString& InValue) const;`
- L125 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L126 _private member_ `FDelegateHandle OnChangedHandle;`
- L127 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L128 _private member_ `FText Tooltip;`
- L129 _private member_ `UEnum* Enum = nullptr;`
- L130 _private member_ `FString DefaultWhenApplied;`
- L131 _private member_ `FString PendingValue;`
- L132 _private member_ `TArray<TSharedPtr<FString>> Options;`
- L133 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboWidget;`

#### class `ControlRigDynamicsEditor::FCVarOverrideNumericBinding`  
`template <typename NumericType> class FCVarOverrideNumericBinding : public TSharedFromThis<FCVarOverrideNumericBinding<NumericType>>`  
_L141-312_
- inherits: `TSharedFromThis<FCVarOverrideNumericBinding<NumericType>>`
- L145 _public function_ `FCVarOverrideNumericBinding( const FString& InCVarName, const FText& InTooltip, NumericType InDefaultValue, NumericType InMinAllowedValue) : Tooltip(InTooltip) , PendingValue(InDefaultValue) , MinAllowedValue(InMinAllowedValue)`
- L166 _public function_ `~FCVarOverrideNumericBinding()`
- L175 _public function_ `void Initialize(TWeakPtr<SWidget> InOwnerWidget)`
- L186 _public function_ `TSharedRef<SWidget> BuildOverrideCell()`
- L196 _public function_ `TSharedRef<SWidget> BuildValueCell()`
- L211 _private function_ `NumericType ReadCVar() const`
- L224 _private function_ `void WriteCVar(NumericType Value)`
- L231 _private function_ `bool IsOverrideActive() const`
- L237 _private function_ `void HandleCVarChanged(IConsoleVariable* )`
- L254 _private function_ `ECheckBoxState GetApplyCheckState() const`
- L260 _private function_ `void OnApplyCheckStateChanged(ECheckBoxState NewState)`
- L277 _private function_ `TOptional<NumericType> GetDisplayValue() const`
- L287 _private function_ `void OnValueCommitted(NumericType NewValue, ETextCommit::Type )`
- L301 _private function_ `bool IsValueEntryEnabled() const`
- L306 _private member_ `IConsoleVariable* CachedCVar = nullptr;`
- L307 _private member_ `FDelegateHandle OnChangedHandle;`
- L308 _private member_ `TWeakPtr<SWidget> OwnerWidget;`
- L309 _private member_ `FText Tooltip;`
- L310 _private member_ `NumericType PendingValue;`
- L311 _private member_ `NumericType MinAllowedValue;`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace ControlRigDynamicsEditor`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamicsEditor/Private/ControlRigDynamicsEditorModule.h` (Private)


#### class `FControlRigDynamicsEditorModule`  
`class FControlRigDynamicsEditorModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `TSharedRef<SDockTab> OnSpawnDebugTab(const FSpawnTabArgs& SpawnTabArgs);`
- L20 _private prototype_ `void RegisterMenus();`

### `Plugins/Experimental/ControlRigDynamics/Source/ControlRigDynamicsEditor/Private/SControlRigDynamicsDebugWidget.h` (Private)


#### class `SControlRigDynamicsDebugWidget`  
`class SControlRigDynamicsDebugWidget : public SCompoundWidget`  
_L15-46_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SControlRigDynamicsDebugWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `FReply OnClearOverridesClicked();`
- L29 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarSimpleToggleBinding> EnableStepSolverBinding;` — Binding lifetime matches the widget. Kept as members so OnChangedDelegate bindings stay alive. The binding types are namespaced (ControlRigDynamicsEditor::) to avoid duplicate-symbol clashes with the parallel set declared in ControlRigPhysicsEditor.
- L30 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideNumericBinding<float>> MaxTimeStepBinding;`
- L31 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideNumericBinding<int32>> MaxNumStepsBinding;`
- L32 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarSimpleToggleBinding> AllowVisualizationBinding;`
- L33 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowParticlesBinding;`
- L34 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowCollidersBinding;`
- L35 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowConfinersBinding;`
- L36 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowSkeletalConstraintsBinding;`
- L37 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowHardConstraintsBinding;`
- L38 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowSoftConstraintsBinding;`
- L39 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowAngleLimitsBinding;`
- L40 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowConeLimitsBinding;`
- L41 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideToggleBinding> ShowForceFieldsBinding;`
- L42 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarOverrideNumericBinding<float>> ForceFieldDebugScaleBinding;`
- L43 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarEnumDropdownBinding> ParticleValueDisplayBinding;`
- L44 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarSimpleToggleBinding> EnableDrawInterfaceInGameBinding;`
- L45 _private member_ `TSharedPtr<ControlRigDynamicsEditor::FCVarSimpleToggleBinding> AnimNodeControlRigDebugBinding;`
