# Plugins / ModelViewViewModelEditor

- module root: `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor`
- headers: 54; symbols: 1400
- symbol kinds: class=61, delegate=13, enum=10, enumerator=26, function=135, macro=3, member=291, namespace=134, prototype=674, struct=26, typedef=27
- PrivateDependencyModuleNames: AdvancedWidgets, ApplicationCore, AssetTools, EditorWidgets, GraphEditor, InputCore, Kismet, MessageLog, Projects, PropertyEditor, Slate, SlateCore, StatusBar, ToolMenus, ToolWidgets, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, EditorSubsystem, Engine, EnhancedInput, FieldNotification, KismetCompiler, ModelViewViewModel, ModelViewViewModelBlueprint, PropertyPath

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMBlueprintViewModelContextCustomization.h` (Private)


#### class `UE::MVVM::FViewModelPropertyAccessEditor`  
`class FViewModelPropertyAccessEditor`  
_L17-34_
- L20 _public member_ `TWeakObjectPtr<UClass> ClassToLookFor;`
- L22 _public prototype_ `TSharedRef<SWidget> MakePropertyBindingWidget(TSharedRef<FWidgetBlueprintEditor> WidgetBlueprintEditor, FProperty* PropertyToMatch, TSharedRef<IPropertyHandle> AssignToProperty, FName ViewModelPropertyName);`
- L25 _private prototype_ `bool CanBindProperty(FProperty* Property) const;`
- L26 _private prototype_ `bool CanBindFunction(UFunction* Function) const;`
- L27 _private prototype_ `bool CanBindToClass(UClass* Class) const;`
- L28 _private prototype_ `bool HasValidClassToLookFor() const;`
- L29 _private prototype_ `void AddBinding(FName, const TArray<FBindingChainElement>& BindingChain);`
- L31 _private member_ `FProperty* GeneratePureBindingsProperty = nullptr;`
- L32 _private member_ `FProperty* ViewModelProperty = nullptr;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> AssignToProperty = nullptr;`

#### class `UE::MVVM::FBlueprintViewModelContextDetailCustomization`  
`class FBlueprintViewModelContextDetailCustomization : public IPropertyTypeCustomization`  
_L36-82_
- inherits: `IPropertyTypeCustomization`
- L39 _public prototype_ `FBlueprintViewModelContextDetailCustomization(TWeakPtr<FWidgetBlueprintEditor> InEditor);`
- L42 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L43 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L45 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<FWidgetBlueprintEditor> InEditor)`
- L51 _private prototype_ `TSharedRef<SWidget> CreateExecutionTypeMenuContent();`
- L52 _private prototype_ `FText GetCreationTypeValue() const;`
- L53 _private prototype_ `FText GetExecutionTypeValueToolTip() const;`
- L54 _private prototype_ `FText GetClassName() const;`
- L55 _private prototype_ `void HandleClassChanged();`
- L56 _private prototype_ `void HandleCreationTypeChanged();`
- L57 _private prototype_ `void HandleCreateSetterFunctionChanged();`
- L58 _private prototype_ `void HandleUseAsInterfaceChanged();`
- L59 _private prototype_ `TSharedRef<SWidget> HandleClassGetMenuContent();`
- L60 _private prototype_ `void HandleClassCancelMenu();`
- L61 _private prototype_ `void HandleClassCommitted(const UClass* SelectedClass);`
- L62 _private prototype_ `FText GetViewModelNameValueAsText() const;`
- L63 _private prototype_ `bool CanRenameViewModel() const;`
- L64 _private prototype_ `void HandleNameTextCommitted(const FText& NewText, ETextCommit::Type );`
- L65 _private prototype_ `bool HandleNameVerifyTextChanged(const FText& Text, FText& OutError) const;`
- L66 _private prototype_ `bool IsUseAsInterfaceAvailable() const;`
- L68 _private member_ `FViewModelPropertyAccessEditor PropertyAccessEditor;`
- L69 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor;`
- L70 _private member_ `TSharedPtr<SComboButton> NotifyFieldValueClassComboButton;`
- L71 _private member_ `TSharedPtr<IPropertyHandle> ContextHandle;`
- L72 _private member_ `TSharedPtr<IPropertyHandle> NotifyFieldValueClassHandle;`
- L73 _private member_ `TSharedPtr<IPropertyHandle> PropertyPathHandle;`
- L74 _private member_ `TSharedPtr<IPropertyHandle> CreationTypeHandle;`
- L75 _private member_ `TSharedPtr<IPropertyHandle> ViewModelNameHandle;`
- L76 _private member_ `TSharedPtr<IPropertyHandle> OptionalHandle;`
- L77 _private member_ `TSharedPtr<IPropertyHandle> UseAsInterfaceHandle;`
- L78 _private member_ `TSharedPtr<IPropertyHandle> CreateSetterFunctionHandle;`
- L79 _private member_ `TSharedPtr<IPropertyHandle> ForceExecuteBindingsOnSetSourceHandle;`
- L80 _private member_ `TSharedPtr<IPropertyHandle> ResolverHandle;`
- L81 _private member_ `TArray<EMVVMBlueprintViewModelContextCreationType> AllowedCreationTypes;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMClipboardExtension.h` (Private)


#### class `UE::MVVM::FClipboardExtension`  
`class FClipboardExtension : public IClipboardExtension`  
_L15-44_
- inherits: `IClipboardExtension`
- L19 _private prototype_ `virtual void AppendToClipboard(const UWidget* Widget, const FExportArgs& ExportArgs) override;`
- L20 _private prototype_ `virtual bool CanAppendToClipboard(const UWidget* Widget) const override;`
- L21 _private prototype_ `virtual void ProcessImportedText(const UWidgetBlueprint* WidgetBlueprint, const FString& TextToImport, UPackage*& TempPackage) override;`
- L22 _private prototype_ `virtual bool CanImportFromClipboard(const UWidget* Widget) const override;`
- L23 _private prototype_ `virtual void ImportDataToWidget(const UWidget* Widget, FName OldWidgetName) override;`
- L24 _private prototype_ `virtual bool CanWidgetAcceptPaste(const UWidget* Widget) const override;`
- L43 _private member_ `FExtensionTextFactory Factory;`

#### class `UE::MVVM::FClipboardExtension::FExtensionTextFactory`  
`class FExtensionTextFactory : public FCustomizableTextObjectFactory`  
_L29-41_
- inherits: `FCustomizableTextObjectFactory`
- L32 _public prototype_ `FExtensionTextFactory();`
- L35 _public prototype_ `virtual bool CanCreateClass(UClass* ObjectClass, bool& bOmitSubObjs) const override;`
- L36 _public prototype_ `virtual void ProcessConstructedObject(UObject* NewObject) override;`
- L40 _public member_ `TArray<TWeakObjectPtr<UMVVMBlueprintViewExtension>> NewExtensions;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMConversionPathCustomization.h` (Private)


#### class `UE::MVVM::FConversionPathCustomization`  
`class FConversionPathCustomization : public IPropertyTypeCustomization`  
_L13-33_
- inherits: `IPropertyTypeCustomization`
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(UWidgetBlueprint* InWidgetBlueprint)`
- L20 _public prototype_ `FConversionPathCustomization(UWidgetBlueprint* InWidgetBlueprint);`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L25 _private prototype_ `FText GetFunctionPathText(UMVVMBlueprintViewConversionFunction* BlueprintViewConversionFunction) const;`
- L26 _private prototype_ `void AddRowForProperty(IDetailChildrenBuilder& ChildBuilder, const TSharedPtr<IPropertyHandle>& Property, bool bSourceToDestination);`
- L27 _private prototype_ `EMVVMBindingMode GetBindingMode() const;`
- L30 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBlueprint;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> ParentHandle;`
- L32 _private member_ `TSharedPtr<IPropertyHandle> BindingModeHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMDragDropExtension.h` (Private)


#### class `UE::MVVM::FWidgetDragDropExtension`  
`class FWidgetDragDropExtension : public IWidgetDragDropExtension`  
_L9-15_
- inherits: `IWidgetDragDropExtension`
- L12 _private prototype_ `virtual bool ShouldPreventDropOnTarget(const UWidget* Target, const TSharedPtr<FDragDropOperation>& DragDropOp) const override;`
- L13 _private prototype_ `virtual FText GetDropFailureText(const UWidget* Target, const TSharedPtr<FDragDropOperation>& DragDropOp) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMListViewBaseExtensionCustomizationExtender.h` (Private)


#### class `UE::MVVM::FMVVMListViewBaseExtensionCustomizationExtender`  
`class FMVVMListViewBaseExtensionCustomizationExtender : public IBlueprintWidgetCustomizationExtender`  
_L21-78_
- inherits: `IBlueprintWidgetCustomizationExtender`
- L24 _public prototype_ `static TSharedPtr<FMVVMListViewBaseExtensionCustomizationExtender> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout, const TArrayView<UWidget*> InWidgets, const TSharedRef<FWidgetBlueprintEditor>& InWidgetBlueprintEditor);`
- L29 _private prototype_ `void SetEntryViewModel(FGuid InEntryViewModelId, bool bMarkModified = true);` — Set the entry viewmodel on the MVVMViewBlueprintListViewBaseExtension for this widget.
- L32 _private prototype_ `TSharedRef<SWidget> OnGetViewModelsMenuContent();` — Get a list of all viewmodels in the entry class.
- L35 _private prototype_ `FText OnGetSelectedViewModel() const;` — Get the name of the currently-selected entry viewmodel from the extension.
- L38 _private prototype_ `void ClearEntryViewModel();` — Clear the entry viewmodel on the MVVMViewBlueprintListViewBaseExtension for this widget.
- L41 _private prototype_ `void HandleEntryClassChanged(bool bIsInit);` — Update the cached variables when the entry class property changes.
- L44 _private function_ `EVisibility GetEntryViewModelVisibility() const` — Get the visibility of entry viewmodel row in the details panel.
- L50 _private prototype_ `void CreateListBaseViewExtensionIfNotExisting();` — Create a new MVVMViewBlueprintListViewBaseExtension for this widget in the blueprint view class.
- L53 _private prototype_ `UMVVMBlueprintViewExtension_ListViewBase* GetListBaseViewExtension() const;` — Get the MVVMViewBlueprintListViewBaseExtension for this widget in the blueprint view class.
- L56 _private prototype_ `UMVVMWidgetBlueprintExtension_View* GetExtensionViewForSelectedWidgetBlueprint() const;` — Get the MVVM blueprint view class of this widget blueprint.
- L59 _private prototype_ `FReply ModifyExtension();` — Add/Remove the MVVMViewBlueprintListViewBaseExtension for this widget on button click.
- L62 _private prototype_ `const FSlateBrush* GetExtensionButtonIcon() const;` — Get + or X icon for the MVVM extension button.
- L65 _private prototype_ `FText GetExtensionButtonText() const;` — Get display text for the MVVM extension button.
- L69 _private member_ `TWeakObjectPtr<UListViewBase> Widget;` — The selected ListViewBase widget in the details panel.
- L70 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor;`
- L72 _private member_ `TSubclassOf<UUserWidget> EntryClass;`
- L73 _private member_ `TSharedPtr<IPropertyHandle> EntryClassHandle;`
- L74 _private member_ `TWeakObjectPtr<UWidgetBlueprint> EntryWidgetBlueprint;`
- L77 _private member_ `bool bIsExtensionAdded = false;` — Keep track of whether we have a MVVMViewBlueprintListViewBaseExtension for this widget.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMPanelWidgetExtensionCustomizationExtender.h` (Private)


#### class `UE::MVVM::FMVVMPanelWidgetExtensionCustomizationExtender`  
`class FMVVMPanelWidgetExtensionCustomizationExtender : public IBlueprintWidgetCustomizationExtender`  
_L21-84_
- inherits: `IBlueprintWidgetCustomizationExtender`
- L24 _public prototype_ `static TSharedPtr<FMVVMPanelWidgetExtensionCustomizationExtender> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout, const TArrayView<UWidget*> InWidgets, const TSharedRef<FWidgetBlueprintEditor>& InWidgetBlueprintEditor);`
- L29 _private prototype_ `void SetEntryViewModel(FGuid InEntryViewModelId, bool bMarkModified = true);` — Set the entry viewmodel on the MVVMViewBlueprintPanelWidgetExtension for this widget.
- L32 _private prototype_ `TSharedRef<SWidget> OnGetViewModelsMenuContent();` — Get a list of all viewmodels in the entry class.
- L35 _private prototype_ `FText OnGetSelectedViewModel() const;` — Get the name of the currently-selected entry viewmodel from the extension.
- L38 _private prototype_ `void ClearEntryViewModel();` — Clear the entry viewmodel on the MVVMViewBlueprintPanelWidgetExtension for this widget.
- L41 _private prototype_ `void HandleEntryClassChanged(bool bIsInit);` — Update the cached variables when the entry class property changes.
- L44 _private prototype_ `void HandleSlotChildPropertyChanged();` — Called when a child property on the slot property changes.
- L47 _private prototype_ `void HandleNumDesignerPreviewEntriesChanged();` — Called when the "Num Designer Preview Entries" property changes.
- L50 _private prototype_ `void HandleNumGridColumns();` — Update the cached variables when the number of grid columns changes.
- L53 _private prototype_ `void CreatePanelWidgetViewExtensionIfNotExisting();` — Create a new MVVMViewBlueprintPanelWidgetExtension for this widget in the blueprint view class.
- L56 _private prototype_ `void RefreshDesignerPreviewEntries(bool bFullRebuild);` — Create preview entries for the selected panel widget.
- L59 _private prototype_ `UMVVMBlueprintViewExtension_PanelWidget* GetPanelWidgetExtension() const;` — Get the MVVMViewBlueprintPanelWidgetExtension for this widget in the blueprint view class.
- L62 _private prototype_ `UMVVMWidgetBlueprintExtension_View* GetExtensionViewForSelectedWidgetBlueprint() const;` — Get the MVVM blueprint view class of this widget blueprint.
- L65 _private prototype_ `FReply ModifyExtension();` — Add/Remove the MVVMViewBlueprintPanelWidgetExtension for this widget on button click.
- L68 _private prototype_ `const FSlateBrush* GetExtensionButtonIcon() const;` — Get + or X icon for the MVVM extension button.
- L71 _private prototype_ `FText GetExtensionButtonText() const;` — Get display text for the MVVM extension button.
- L75 _private member_ `TWeakObjectPtr<UPanelWidget> Widget;` — The selected panel widget in the details panel.
- L76 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor;`
- L78 _private member_ `TSubclassOf<UUserWidget> EntryClass;`
- L79 _private member_ `TSharedPtr<IPropertyHandle> EntryClassHandle;`
- L80 _private member_ `TWeakObjectPtr<UWidgetBlueprint> EntryWidgetBlueprint;`
- L83 _private member_ `bool bIsExtensionAdded = false;` — Keep track of whether we have a MVVMViewBlueprintPanelWidgetExtension for this widget.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMPropertyBindingExtension.h` (Private)


#### class `UE::MVVM::FMVVMPropertyBindingExtension`  
`class FMVVMPropertyBindingExtension : public IPropertyBindingExtension`  
_L14-31_
- inherits: `IPropertyBindingExtension`
- L17 _private prototype_ `static void ExtendBindingsMenu(FMenuBuilder& MenuBuilder, TSharedRef<FMVVMPropertyBindingExtension> MVVMPropertyBindingExtension, const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> WidgetPropertyHandle);`
- L19 _private prototype_ `virtual TOptional<FName> GetCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const override;`
- L20 _private prototype_ `virtual const FSlateBrush* GetCurrentIcon(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const override;`
- L21 _private prototype_ `virtual TOptional<FLinearColor> GetCurrentIconColor(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const override;`
- L23 _private prototype_ `virtual void ClearCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L24 _private prototype_ `virtual TSharedPtr<FExtender> CreateMenuExtender(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L25 _private prototype_ `virtual bool CanExtend(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<const IPropertyHandle> PropertyHandle) const override;`
- L26 _private prototype_ `virtual EDropResult OnDrop(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent, UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L27 _private prototype_ `virtual TSharedRef<SWidget> OnGenerateMenu(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle, TWeakPtr<IDetailsView> DetailsView) override;`
- L28 _private prototype_ `virtual bool ShouldAllowEditingValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const override;`
- L30 _private prototype_ `EVisibility GetCheckmarkVisibility(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, const FProperty* Property, FGuid OwningViewModelId, TSharedPtr<IPropertyHandle> PropertyHandle) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMPropertyPathCustomization.h` (Private)


#### class `UE::MVVM::FPropertyPathCustomization`  
`class FPropertyPathCustomization : public IPropertyTypeCustomization`  
_L11-35_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `FPropertyPathCustomization(UWidgetBlueprint* WidgetBlueprint);`
- L15 _public prototype_ `~FPropertyPathCustomization();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(UWidgetBlueprint* InWidgetBlueprint)`
- L24 _public prototype_ `FMVVMLinkedPinValue GetFieldValue() const;`
- L25 _public prototype_ `FMVVMBlueprintViewBinding* GetOwningBinding() const;`
- L28 _private prototype_ `FMVVMBlueprintPropertyPath GetPropertyPathValue() const;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L32 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBlueprint;`
- L33 _private member_ `bool bIsSource = false;`
- L34 _private member_ `FGuid OwningBindingId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMWidgetBlueprintDiffProvider.h` (Private)


#### class `FMVVMDiffCustomObject_View`  
`class FMVVMDiffCustomObject_View : public IDiffCustomObject`  
_L13-40_
- inherits: `IDiffCustomObject`
- L16 _public member_ `TSharedPtr<UE::MVVM::SBindingsList> OldList;`
- L17 _public member_ `TSharedPtr<UE::MVVM::SBindingsList> NewList;`
- L19 _public function_ `FMVVMDiffCustomObject_View(const UWidgetBlueprint* NewBlueprint, const UWidgetBlueprint* OldBlueprint)`
- L38 _public function_ `TSharedPtr<SWidget> GetOldWidget() override`
- L39 _public function_ `TSharedPtr<SWidget> GetNewWidget() override`

#### class `FMVVMDiffCustomProperty_Binding`  
`class FMVVMDiffCustomProperty_Binding : public IDiffCustomProperty`  
_L42-68_
- inherits: `IDiffCustomProperty`
- L45 _public member_ `FGuid NewBinding;`
- L46 _public member_ `FGuid OldBinding;`
- L48 _public function_ `FMVVMDiffCustomProperty_Binding(const FGuid NewBinding, const FGuid OldBinding) : NewBinding(NewBinding) , OldBinding(OldBinding)`
- L54 _public function_ `void HighlightProperty(const TSharedPtr<IDiffCustomObject> Widget) override`

#### class `FMVVMDiffCustomProperty_Event`  
`class FMVVMDiffCustomProperty_Event : public IDiffCustomProperty`  
_L70-96_
- inherits: `IDiffCustomProperty`
- L73 _public member_ `const UMVVMBlueprintViewEvent* NewEvent;`
- L74 _public member_ `const UMVVMBlueprintViewEvent* OldEvent;`
- L76 _public function_ `FMVVMDiffCustomProperty_Event(const UMVVMBlueprintViewEvent* NewEvent, const UMVVMBlueprintViewEvent* OldEvent) : NewEvent(NewEvent) , OldEvent(OldEvent)`
- L82 _public function_ `void HighlightProperty(const TSharedPtr<IDiffCustomObject> Widget) override`

#### class `FMVVMDiffCustomProperty_Condition`  
`class FMVVMDiffCustomProperty_Condition : public IDiffCustomProperty`  
_L98-124_
- inherits: `IDiffCustomProperty`
- L101 _public member_ `const UMVVMBlueprintViewCondition* NewCondition;`
- L102 _public member_ `const UMVVMBlueprintViewCondition* OldCondition;`
- L104 _public function_ `FMVVMDiffCustomProperty_Condition(const UMVVMBlueprintViewCondition* NewCondition, const UMVVMBlueprintViewCondition* OldCondition) : NewCondition(NewCondition) , OldCondition(OldCondition)`
- L110 _public function_ `void HighlightProperty(const TSharedPtr<IDiffCustomObject> Widget) override`

#### class `FMVVMDiffCustomProperty_Parameter`  
`class FMVVMDiffCustomProperty_Parameter : public IDiffCustomProperty`  
_L126-146_
- inherits: `IDiffCustomProperty`
- L129 _public member_ `FMVVMBlueprintPinId NewParameter;`
- L130 _public member_ `FMVVMBlueprintPinId OldParameter;`
- L132 _public function_ `FMVVMDiffCustomProperty_Parameter(FMVVMBlueprintPinId NewParameter, FMVVMBlueprintPinId OldParameter) : NewParameter(NewParameter) , OldParameter(OldParameter)`
- L138 _public function_ `void HighlightProperty(const TSharedPtr<IDiffCustomObject> Widget) override`

#### struct `FMVVMWidgetBlueprintDiffProvider`  
`struct FMVVMWidgetBlueprintDiffProvider : public UE::MVVM::FMVVMDiffCustomObjectProvider`  
_L148-174_
- inherits: `UE::MVVM::FMVVMDiffCustomObjectProvider`
- L150 _public function_ `TSharedPtr<IDiffCustomObject> CreateObjectDiff(const UWidgetBlueprint* NewBlueprint, const UWidgetBlueprint* OldBlueprint)`
- L155 _public function_ `TSharedPtr<IDiffCustomProperty> CreatePropertyBindingDiff(FGuid NewBinding, FGuid OldBinding)`
- L160 _public function_ `TSharedPtr<IDiffCustomProperty> CreatePropertyConditionDiff(const UMVVMBlueprintViewCondition* NewCondition, const UMVVMBlueprintViewCondition* OldCondition)`
- L165 _public function_ `TSharedPtr<IDiffCustomProperty> CreatePropertyConditionDiff(const UMVVMBlueprintViewEvent* NewEvent, const UMVVMBlueprintViewEvent* OldEvent)`
- L170 _public function_ `TSharedPtr<IDiffCustomProperty> CreatePropertyParameterDiff(const FMVVMBlueprintPinId& NewParameter, const FMVVMBlueprintPinId& OldParameter)`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Customizations/MVVMWidgetContextMenuExtension.h` (Private)


#### class `UE::MVVM::FWidgetContextMenuExtension`  
`class FWidgetContextMenuExtension : public IWidgetContextMenuExtension`  
_L12-17_
- inherits: `IWidgetContextMenuExtension`
- L15 _private prototype_ `virtual void ExtendContextMenu(FMenuBuilder& MenuBuilder, TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, FVector2D TargetLocation) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Framework/MVVMBindingEditorHelper.h` (Private)


#### struct `UE::MVVM::FMVVMBindingEditorHelper`  
`struct FMVVMBindingEditorHelper`  
_L14-19_
- L17 _public prototype_ `static bool CreateWidgetBindings(UWidgetBlueprint* Blueprint, TSet<FWidgetReference> Widgets, TArray<FGuid>& OutBindingIds);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Framework/MVVMConversionFunctionLibrary.h` (Private)


#### struct `UE::MVVM::ConversionFunctionLibrary::FFunctionEntry`  
`struct FFunctionEntry`  
_L25-41_
- L31 _public prototype_ `FFunctionEntry() = default;`
- L32 _public prototype_ `FFunctionEntry(FConversionFunctionValue Function);`
- L34 _public function_ `const ::UE::MVVM::FConversionFunctionValue& GetFunction() const`

#### class `UE::MVVM::ConversionFunctionLibrary::FCollection`  
`class FCollection : public FGCObject`  
_L48-105_
- inherits: `FGCObject`
- desc: Collection of all available conversion functions. The collection rebuild when a new object is loaded and when the WidgetBlueprint is compiled.
- L51 _public prototype_ `FCollection();`
- L52 _public prototype_ `~FCollection();`
- L55 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L56 _public prototype_ `virtual FString GetReferencerName() const override;`
- L60 _public prototype_ `[[nodiscard]] TArray<::UE::MVVM::FConversionFunctionValue> GetFunctions(const UWidgetBlueprint* Blueprint) const;`
- L61 _public prototype_ `[[nodiscard]] TArray<::UE::MVVM::FConversionFunctionValue> GetFunctions(const UWidgetBlueprint* Blueprint, const FProperty* ArgumentType, const FProperty* ReturnType) const;`
- L63 _public prototype_ `[[nodiscard]] const TSharedPtr<FFunctionEntry> FindFunction(::UE::MVVM::FConversionFunctionValue) const;`
- L66 _public prototype_ `void Rebuild();` — Rebuild the library when a setting outside of MVVM changed.
- L69 _private prototype_ `void RefreshIfNeeded();`
- L70 _private prototype_ `void Build();`
- L71 _private prototype_ `void Build_Class(const TArray<const UClass*>& AllowClasses, const TArray<const UClass*>& DenyClasses, const UObject* Class);`
- L72 _private prototype_ `bool IsClassSupported(const TArray<const UClass*>& AllowClasses, const TArray<const UClass*>& DenyClasses, const UClass* Class) const;`
- L73 _private prototype_ `void AddClassFunctions(const UClass* Class);`
- L74 _private prototype_ `void AddNode(TSubclassOf<UK2Node> Function);`
- L75 _private prototype_ `void RegisterBlueprintCallback(const UClass* Class);`
- L76 _private prototype_ `void UnegisterBlueprintCallback(UObject* Class);`
- L79 _private prototype_ `void AddObjectToRefresh(UObject* Object);`
- L81 _private prototype_ `void HandleBlueprintChanged(UBlueprint* Blueprint);`
- L82 _private prototype_ `void HandleBlueprintUnloaded(UBlueprint* Blueprint);`
- L83 _private prototype_ `void HandleObjectLoaded(UObject* NewObject);`
- L84 _private prototype_ `void HandleObjectPendingDelete(TArray<UObject*> const& ObjectsForDelete);`
- L85 _private prototype_ `void HandleAssetAdded(FAssetData const& AssetInfo);`
- L86 _private prototype_ `void HandleAssetRemoved(FAssetData const& AssetInfo);`
- L87 _private prototype_ `void HandleAssetRenamed(FAssetData const& AssetInfo, const FString& InOldName);`
- L88 _private prototype_ `void HandleModulesChanged(FName InModuleName, EModuleChangeReason InModuleChangeReason);`
- L89 _private prototype_ `void HandleReloadComplete(EReloadCompleteReason Reason);`
- L98 _private member_ `TMap<FObjectKey, FFunctionContainer> ClassOrBlueprintToFunctions;`
- L99 _private member_ `TArray<TObjectPtr<UK2Node>> ConversionFunctionNodes;`
- L101 _private member_ `TSet<FObjectKey> ObjectToRefresh;` — can only be GeneratedClass or Blueprint
- L102 _private member_ `TSet<FName> ModuleToRefresh;`
- L103 _private member_ `int32 NumberOfFunctions = 0;`
- L104 _private member_ `bool bRefreshAll = true;`

#### struct `UE::MVVM::ConversionFunctionLibrary::FCollection::FFunctionContainer`  
`struct FFunctionContainer`  
_L92-97_
- L94 _public member_ `TArray<TSharedRef<FFunctionEntry>> Functions;`
- L95 _public member_ `bool bIsUserWidget = false;`
- L96 _public member_ `bool bIsNode = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L16 _namespace_ `namespace ConversionFunctionLibrary` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Framework/MVVMConversionHelper.h` (Private)


#### struct `UE::MVVM::FConversionHelper`  
`struct FConversionHelper`  
_L14-17_
- L16 _public prototype_ `static FString GetBindToDestinationStringFromConversionFunction(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewConversionFunction* ConversionFunction);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Framework/MVVMRowHelper.h` (Private)


#### struct `UE::MVVM::BindingEntry::FRowHelper`  
`struct FRowHelper`  
_L26-43_
- L28 _public prototype_ `static void GatherAllChildBindings(UMVVMBlueprintView* BlueprintView, const TConstArrayView<TSharedPtr<FBindingEntry>> Entries, TArray<FGuid>& OutBindingIds, TArray<UMVVMBlueprintViewEvent*>& OutEvents, TArray<UMVVMBlueprintViewCondition*>& OutConditions, bool bRecurse = true);`
- L30 _public prototype_ `static void DeleteEntries(const UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintView* BlueprintView, TArrayView<const TSharedPtr<FBindingEntry>> Selection);`
- L31 _public prototype_ `static void DuplicateEntries(const UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintView* BlueprintView, TArrayView<const TSharedPtr<FBindingEntry>> Selection, TArray<const TSharedPtr<FBindingEntry>>& OutSelection);`
- L33 _public prototype_ `static void CopyEntries(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintView* BlueprintView, const TArray<TSharedPtr<FBindingEntry>>& Entries);`
- L34 _public prototype_ `static void PasteEntries(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintView* BlueprintView, const TArray<TSharedPtr<FBindingEntry>>& Entries);`
- L36 _public prototype_ `static bool HasBlueprintGraph(UMVVMBlueprintView* BlueprintView, const TSharedPtr<FBindingEntry> Entry);`
- L37 _public prototype_ `static void ShowBlueprintGraph(FBlueprintEditor* Editor, UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintView* BlueprintView, TArrayView<const TSharedPtr<FBindingEntry>> Selection);`
- L39 _public prototype_ `static TOptional<FMVVMBlueprintPropertyPath> DropFieldSelector(const UWidgetBlueprint* WidgetBlueprint, const FDragDropEvent& DragDropEvent, bool bIsSource);`
- L40 _public prototype_ `static FReply DragOverFieldSelector(const UWidgetBlueprint* WidgetBlueprint, const FDragDropEvent& DragDropEvent, bool bIsSource);`
- L42 _public prototype_ `static FMenuBuilder CreateContextMenu(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintView* View, TConstArrayView<TSharedPtr<FBindingEntry>> Entries, FOnContextMenuEntryCallback OnSelectionChanged = FOnContextMenuEntryCallback());`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MVVM` (scope `UE`)
- L21 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnContextMenuEntryCallback, TConstArrayView<const TSharedPtr<FBindingEntry>> );`
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnContextMenuEntryCallback, TConstArrayView<const TSharedPtr<FBindingEntry>> );` (scope `UE::MVVM::BindingEntry`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/MVVMFieldVariantListTraits.h` (Private)


#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<UE::MVVM::FMVVMFieldVariant>`  
_L9-15_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L12-14_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<UE::MVVM::FMVVMFieldVariant>`  
_L18-60_
- L20 _public typedef_ `typedef UE::MVVM::FMVVMFieldVariant NullableType;`
- L22 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMFieldVariant, TSharedRef<ITableRow>, false>;`
- L23 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMFieldVariant, FSparseItemInfo, false>;`
- L24 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FMVVMFieldVariant>;`
- L27 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FMVVMFieldVariant>&, TSet<UE::MVVM::FMVVMFieldVariant>&, TMap<const U*, UE::MVVM::FMVVMFieldVariant>&)`
- L34 _public function_ `static bool IsPtrValid(const UE::MVVM::FMVVMFieldVariant& InPtr)`
- L39 _public function_ `static void ResetPtr(UE::MVVM::FMVVMFieldVariant& InPtr)`
- L44 _public function_ `static UE::MVVM::FMVVMFieldVariant MakeNullPtr()`
- L49 _public function_ `static UE::MVVM::FMVVMFieldVariant NullableItemTypeConvertToItemType(const UE::MVVM::FMVVMFieldVariant& InPtr)`
- L54 _public function_ `static FString DebugDump(UE::MVVM::FMVVMFieldVariant InPtr)`
- L74 _public typedef_ `typedef UE::MVVM::FMVVMConstFieldVariant NullableType;`
- L76 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMConstFieldVariant, TSharedRef<ITableRow>, false>;`
- L77 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMConstFieldVariant, FSparseItemInfo, false>;`
- L78 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FMVVMConstFieldVariant>;`
- L81 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FMVVMConstFieldVariant>&, TSet<UE::MVVM::FMVVMConstFieldVariant>&, TMap<const U*, UE::MVVM::FMVVMConstFieldVariant>&)`
- L88 _public function_ `static bool IsPtrValid(const UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L93 _public function_ `static void ResetPtr(UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L98 _public function_ `static UE::MVVM::FMVVMConstFieldVariant MakeNullPtr()`
- L103 _public function_ `static UE::MVVM::FMVVMConstFieldVariant NullableItemTypeConvertToItemType(const UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L108 _public function_ `static FString DebugDump(UE::MVVM::FMVVMConstFieldVariant InPtr)`
- L128 _public typedef_ `typedef FMVVMBlueprintPropertyPath NullableType;`
- L130 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FMVVMBlueprintPropertyPath, TSharedRef<ITableRow>, false>;`
- L131 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FMVVMBlueprintPropertyPath, FSparseItemInfo, false>;`
- L132 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FMVVMBlueprintPropertyPath>;`
- L135 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FMVVMBlueprintPropertyPath>&, TSet<FMVVMBlueprintPropertyPath>&, TMap<const U*, FMVVMBlueprintPropertyPath>&)`
- L142 _public function_ `static bool IsPtrValid(const FMVVMBlueprintPropertyPath& InPtr)`
- L147 _public function_ `static void ResetPtr(FMVVMBlueprintPropertyPath& InPtr)`
- L152 _public function_ `static FMVVMBlueprintPropertyPath MakeNullPtr()`
- L157 _public function_ `static FMVVMBlueprintPropertyPath NullableItemTypeConvertToItemType(const FMVVMBlueprintPropertyPath& InPtr)`
- L162 _public function_ `static FString DebugDump(FMVVMBlueprintPropertyPath InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L59-59_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<UE::MVVM::FMVVMConstFieldVariant>`  
_L63-69_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L66-68_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<UE::MVVM::FMVVMConstFieldVariant>`  
_L72-114_
- L20 _public typedef_ `typedef UE::MVVM::FMVVMFieldVariant NullableType;`
- L22 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMFieldVariant, TSharedRef<ITableRow>, false>;`
- L23 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMFieldVariant, FSparseItemInfo, false>;`
- L24 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FMVVMFieldVariant>;`
- L27 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FMVVMFieldVariant>&, TSet<UE::MVVM::FMVVMFieldVariant>&, TMap<const U*, UE::MVVM::FMVVMFieldVariant>&)`
- L34 _public function_ `static bool IsPtrValid(const UE::MVVM::FMVVMFieldVariant& InPtr)`
- L39 _public function_ `static void ResetPtr(UE::MVVM::FMVVMFieldVariant& InPtr)`
- L44 _public function_ `static UE::MVVM::FMVVMFieldVariant MakeNullPtr()`
- L49 _public function_ `static UE::MVVM::FMVVMFieldVariant NullableItemTypeConvertToItemType(const UE::MVVM::FMVVMFieldVariant& InPtr)`
- L54 _public function_ `static FString DebugDump(UE::MVVM::FMVVMFieldVariant InPtr)`
- L74 _public typedef_ `typedef UE::MVVM::FMVVMConstFieldVariant NullableType;`
- L76 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMConstFieldVariant, TSharedRef<ITableRow>, false>;`
- L77 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMConstFieldVariant, FSparseItemInfo, false>;`
- L78 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FMVVMConstFieldVariant>;`
- L81 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FMVVMConstFieldVariant>&, TSet<UE::MVVM::FMVVMConstFieldVariant>&, TMap<const U*, UE::MVVM::FMVVMConstFieldVariant>&)`
- L88 _public function_ `static bool IsPtrValid(const UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L93 _public function_ `static void ResetPtr(UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L98 _public function_ `static UE::MVVM::FMVVMConstFieldVariant MakeNullPtr()`
- L103 _public function_ `static UE::MVVM::FMVVMConstFieldVariant NullableItemTypeConvertToItemType(const UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L108 _public function_ `static FString DebugDump(UE::MVVM::FMVVMConstFieldVariant InPtr)`
- L128 _public typedef_ `typedef FMVVMBlueprintPropertyPath NullableType;`
- L130 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FMVVMBlueprintPropertyPath, TSharedRef<ITableRow>, false>;`
- L131 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FMVVMBlueprintPropertyPath, FSparseItemInfo, false>;`
- L132 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FMVVMBlueprintPropertyPath>;`
- L135 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FMVVMBlueprintPropertyPath>&, TSet<FMVVMBlueprintPropertyPath>&, TMap<const U*, FMVVMBlueprintPropertyPath>&)`
- L142 _public function_ `static bool IsPtrValid(const FMVVMBlueprintPropertyPath& InPtr)`
- L147 _public function_ `static void ResetPtr(FMVVMBlueprintPropertyPath& InPtr)`
- L152 _public function_ `static FMVVMBlueprintPropertyPath MakeNullPtr()`
- L157 _public function_ `static FMVVMBlueprintPropertyPath NullableItemTypeConvertToItemType(const FMVVMBlueprintPropertyPath& InPtr)`
- L162 _public function_ `static FString DebugDump(FMVVMBlueprintPropertyPath InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L113-113_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<FMVVMBlueprintPropertyPath>`  
_L117-123_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L120-122_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<FMVVMBlueprintPropertyPath>`  
_L126-168_
- L20 _public typedef_ `typedef UE::MVVM::FMVVMFieldVariant NullableType;`
- L22 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMFieldVariant, TSharedRef<ITableRow>, false>;`
- L23 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMFieldVariant, FSparseItemInfo, false>;`
- L24 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FMVVMFieldVariant>;`
- L27 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FMVVMFieldVariant>&, TSet<UE::MVVM::FMVVMFieldVariant>&, TMap<const U*, UE::MVVM::FMVVMFieldVariant>&)`
- L34 _public function_ `static bool IsPtrValid(const UE::MVVM::FMVVMFieldVariant& InPtr)`
- L39 _public function_ `static void ResetPtr(UE::MVVM::FMVVMFieldVariant& InPtr)`
- L44 _public function_ `static UE::MVVM::FMVVMFieldVariant MakeNullPtr()`
- L49 _public function_ `static UE::MVVM::FMVVMFieldVariant NullableItemTypeConvertToItemType(const UE::MVVM::FMVVMFieldVariant& InPtr)`
- L54 _public function_ `static FString DebugDump(UE::MVVM::FMVVMFieldVariant InPtr)`
- L74 _public typedef_ `typedef UE::MVVM::FMVVMConstFieldVariant NullableType;`
- L76 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMConstFieldVariant, TSharedRef<ITableRow>, false>;`
- L77 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FMVVMConstFieldVariant, FSparseItemInfo, false>;`
- L78 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FMVVMConstFieldVariant>;`
- L81 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FMVVMConstFieldVariant>&, TSet<UE::MVVM::FMVVMConstFieldVariant>&, TMap<const U*, UE::MVVM::FMVVMConstFieldVariant>&)`
- L88 _public function_ `static bool IsPtrValid(const UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L93 _public function_ `static void ResetPtr(UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L98 _public function_ `static UE::MVVM::FMVVMConstFieldVariant MakeNullPtr()`
- L103 _public function_ `static UE::MVVM::FMVVMConstFieldVariant NullableItemTypeConvertToItemType(const UE::MVVM::FMVVMConstFieldVariant& InPtr)`
- L108 _public function_ `static FString DebugDump(UE::MVVM::FMVVMConstFieldVariant InPtr)`
- L128 _public typedef_ `typedef FMVVMBlueprintPropertyPath NullableType;`
- L130 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FMVVMBlueprintPropertyPath, TSharedRef<ITableRow>, false>;`
- L131 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FMVVMBlueprintPropertyPath, FSparseItemInfo, false>;`
- L132 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FMVVMBlueprintPropertyPath>;`
- L135 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FMVVMBlueprintPropertyPath>&, TSet<FMVVMBlueprintPropertyPath>&, TMap<const U*, FMVVMBlueprintPropertyPath>&)`
- L142 _public function_ `static bool IsPtrValid(const FMVVMBlueprintPropertyPath& InPtr)`
- L147 _public function_ `static void ResetPtr(FMVVMBlueprintPropertyPath& InPtr)`
- L152 _public function_ `static FMVVMBlueprintPropertyPath MakeNullPtr()`
- L157 _public function_ `static FMVVMBlueprintPropertyPath NullableItemTypeConvertToItemType(const FMVVMBlueprintPropertyPath& InPtr)`
- L162 _public function_ `static FString DebugDump(FMVVMBlueprintPropertyPath InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L167-167_

#### Free symbols / members of external scopes

- L13 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon543380a10103`)
- L67 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon543380a10203`)
- L121 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon543380a10303`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/MVVMViewBindingMenuContext.h` (Private)


#### class `UMVVMViewBindingMenuContext`  
`class UMVVMViewBindingMenuContext : public UObject`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor;`
- L19 _public member_ `TWeakPtr<UE::MVVM::SBindingsPanel> BindingsPanel;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/ModelViewViewModelEditorModule.h` (Private)


#### class `FModelViewViewModelEditorModule`  
`class FModelViewViewModelEditorModule : public IModelViewViewModelEditorModule`  
_L30-64_
- inherits: `IModelViewViewModelEditorModule`
- L33 _public prototype_ `FModelViewViewModelEditorModule() = default;`
- L36 _public prototype_ `virtual void StartupModule() override;`
- L37 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public prototype_ `virtual void OpenPopoutEditor(TNotNull<UObject*> InObject, bool bInReadyOnly) override;`
- L45 _private prototype_ `void HandleRegisterBlueprintEditorTab(const FWidgetBlueprintApplicationMode& ApplicationMode, FWorkflowAllowedTabSet& TabFactories);`
- L46 _private prototype_ `void HandleRenameFieldReferences(UBlueprint* Blueprint, UClass* FieldOwnerClass, const FName& OldVarName, const FName& NewVarName);`
- L47 _private prototype_ `void HandleDeactiveMode(FWidgetBlueprintApplicationMode& InDesignerMode);`
- L48 _private prototype_ `void HandleActivateMode(FWidgetBlueprintApplicationMode& InDesignerMode);`
- L49 _private prototype_ `void HandleWidgetBlueprintAssetTags(const UWidgetBlueprint* Widget, FAssetRegistryTagsContext Context);`
- L50 _private prototype_ `void HandleClassBlueprintAssetTags(const UWidgetBlueprintGeneratedClass* GeneratedClass, FAssetRegistryTagsContext Context);`
- L51 _private prototype_ `void HandleCollectSaveOverrides(const UWidgetBlueprintGeneratedClass* GeneratedClass, FObjectCollectSaveOverridesContext SaveContext);`
- L52 _private prototype_ `void HandleRegisterMenus();`
- L53 _private prototype_ `void UnregisterMenus();`
- L56 _private member_ `TSharedPtr<UE::MVVM::FMVVMPropertyBindingExtension> PropertyBindingExtension;`
- L57 _private member_ `TSharedPtr<UE::MVVM::FClipboardExtension> ClipboardExtension;`
- L58 _private member_ `TSharedPtr<UE::MVVM::FWidgetDragDropExtension> DragDropExtension;`
- L59 _private member_ `TSharedPtr<UE::MVVM::FWidgetContextMenuExtension> WidgetContextMenuCustomization;`
- L60 _private member_ `TSharedPtr<UE::MVVM::FAssetTypeActions_ViewModelBlueprint> ViewModelBlueprintActions;`
- L61 _private member_ `TSharedPtr<UE::MVVM::FMVVMListViewBaseExtensionCustomizationExtender> ListViewBaseCustomizationExtender;`
- L62 _private member_ `TSharedPtr<UE::MVVM::FMVVMPanelWidgetExtensionCustomizationExtender> PanelWidgetCustomizationExtender;`
- L63 _private member_ `TSharedPtr<UE::MVVM::FBlueprintViewDesignerExtensionFactory> BlueprintViewDesignerExtensionFactory;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Styling/MVVMEditorStyle.h` (Private)


#### class `FMVVMEditorStyle`  
`class FMVVMEditorStyle : public FSlateStyleSet`  
_L10-36_
- inherits: `FSlateStyleSet`
- L14 _public prototype_ `static void CreateInstance();`
- L15 _public prototype_ `static void DestroyInstance();`
- L17 _public function_ `static FMVVMEditorStyle& Get()`
- L24 _private prototype_ `FMVVMEditorStyle();`
- L25 _private prototype_ `FMVVMEditorStyle(const FMVVMEditorStyle&) = delete;`
- L26 _private prototype_ `FMVVMEditorStyle& operator=(const FMVVMEditorStyle&) = delete;`
- L27 _private prototype_ `~FMVVMEditorStyle();`
- L35 _private member_ `static TUniquePtr<FMVVMEditorStyle, FCustomDeleter> Instance;`

#### struct `FMVVMEditorStyle::FCustomDeleter`  
`struct FCustomDeleter`  
_L28-34_
- L30 _public function_ `void operator()(FMVVMEditorStyle* Ptr) const`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Tabs/MVVMBindingSummoner.h` (Private)


#### struct `FMVVMBindingSummoner`  
`struct FMVVMBindingSummoner : public FWorkflowTabFactory`  
_L10-24_
- inherits: `FWorkflowTabFactory`
- L12 _public member_ `static const FName TabID;`
- L13 _public member_ `static const FName DrawerID;`
- L15 _public prototype_ `FMVVMBindingSummoner(TSharedPtr<FWidgetBlueprintEditor> BlueprintEditor, bool bInIsDrawerTab = false);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L19 _public prototype_ `static void ToggleMVVMDrawer();`
- L22 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakWidgetBlueprintEditor;`
- L23 _private member_ `bool bIsDrawerTab;`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Tabs/MVVMViewModelSummoner.h` (Private)


#### struct `UE::MVVM::FViewModelSummoner`  
`struct FViewModelSummoner : public FWorkflowTabFactory`  
_L12-24_
- inherits: `FWorkflowTabFactory`
- L15 _public member_ `static const FName TabID;`
- L18 _public prototype_ `FViewModelSummoner(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _protected member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Types/MVVMBindingEntry.h` (Private)


#### struct `UE::MVVM::FBindingEntry`  
`struct FBindingEntry`  
_L23-166_
- desc: A structure for the different entries in the BindingList
- L37 _public prototype_ `FMVVMBlueprintViewBinding* GetBinding(UMVVMBlueprintView* View) const;`
- L39 _public prototype_ `const FMVVMBlueprintViewBinding* GetBinding(const UMVVMBlueprintView* View) const;`
- L41 _public function_ `ERowType GetRowType() const`
- L47 _public function_ `FName GetGroupName() const`
- L52 _public function_ `FGuid GetGroupAsViewModel() const`
- L57 _public function_ `bool IsGroupWidget() const`
- L62 _public prototype_ `void SetGroup(FName WidgetName);`
- L63 _public prototype_ `void SetGroup(FName ViewModelName, FGuid ViewModelId);`
- L66 _public function_ `FGuid GetBindingId() const`
- L71 _public prototype_ `void SetBindingId(FGuid Id);`
- L73 _public function_ `void SetHasPathToVerseVariable(bool bInHasPathToVerseVariable)`
- L74 _public function_ `void SetHasPathToViewModel(bool bInHasPathToViewModel)`
- L75 _public function_ `bool GetHasPathToVerseVariable() const`
- L76 _public function_ `bool GetHasPathToViewModel() const`
- L79 _public function_ `const FMVVMBlueprintPinId& GetBindingParameterId() const`
- L84 _public function_ `const FEdGraphPinType& GetBindingParameterType() const`
- L89 _public prototype_ `void SetBindingParameter(FGuid Id, FMVVMBlueprintPinId Parameter, FEdGraphPinType ParameterType);`
- L92 _public prototype_ `UMVVMBlueprintViewEvent* GetEvent() const;`
- L94 _public prototype_ `void SetEvent(UMVVMBlueprintViewEvent* InEvent);`
- L97 _public function_ `const FMVVMBlueprintPinId& GetEventParameterId() const`
- L102 _public function_ `const FEdGraphPinType& GetEventParameterType() const`
- L107 _public prototype_ `void SetEventParameter(UMVVMBlueprintViewEvent* Event, FMVVMBlueprintPinId Parameter, FEdGraphPinType ParameterType);`
- L110 _public prototype_ `UMVVMBlueprintViewCondition* GetCondition() const;`
- L112 _public prototype_ `void SetCondition(UMVVMBlueprintViewCondition* InCondition);`
- L115 _public function_ `const FMVVMBlueprintPinId& GetConditionParameterId() const`
- L120 _public function_ `const FEdGraphPinType& GetConditionParameterType() const`
- L125 _public prototype_ `void SetConditionParameter(UMVVMBlueprintViewCondition* Condition, FMVVMBlueprintPinId Parameter, FEdGraphPinType ParameterType);`
- L129 _public function_ `TConstArrayView<TSharedPtr<FBindingEntry>> GetAllChildren() const`
- L134 _public function_ `TConstArrayView<TSharedPtr<FBindingEntry>> GetFilteredChildren() const`
- L139 _public prototype_ `void AddChild(TSharedPtr<FBindingEntry> Child);`
- L141 _public prototype_ `void AddFilteredChild(TSharedPtr<FBindingEntry> Child);`
- L143 _public prototype_ `void ResetChildren();`
- L144 _public prototype_ `void ResetFilteredChildren();`
- L146 _public prototype_ `void SetUseFilteredChildList();`
- L148 _public prototype_ `bool operator==(const FBindingEntry& Other) const;`
- L150 _public prototype_ `FString GetSearchNameString(UMVVMBlueprintView* View, UWidgetBlueprint* WidgetBP);`
- L153 _private member_ `ERowType RowType = ERowType::None;`
- L154 _private member_ `FName Name;`
- L155 _private member_ `FGuid BindingId;`
- L156 _private member_ `FMVVMBlueprintPinId PinId;`
- L157 _private member_ `FEdGraphPinType PinType;`
- L158 _private member_ `TWeakObjectPtr<UMVVMBlueprintViewEvent> Event;`
- L159 _private member_ `TWeakObjectPtr<UMVVMBlueprintViewCondition> Condition;`
- L160 _private member_ `TArray<TSharedPtr<FBindingEntry>> AllChildren;`
- L161 _private member_ `TArray<TSharedPtr<FBindingEntry>> FilteredChildren;`
- L162 _private member_ `bool bGroupIsWidget = false;`
- L163 _private member_ `bool bUseFilteredChildren = false;`
- L164 _private member_ `bool bHasPathToVerseVariable = false;`
- L165 _private member_ `bool bHasPathToViewModel = false;`

#### enum `UE::MVVM::FBindingEntry::ERowType`  
`enum class ERowType`  
_L25-35_
- L27 _public enumerator_ `None`
- L28 _public enumerator_ `Group`
- L29 _public enumerator_ `Binding`
- L30 _public enumerator_ `BindingParameter`
- L31 _public enumerator_ `Event`
- L32 _public enumerator_ `EventParameter`
- L33 _public enumerator_ `Condition`
- L34 _public enumerator_ `ConditionParameter`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Types/MVVMBindingSource.h` (Private)


#### struct `UE::MVVM::FBindingSource`  
`struct FBindingSource`  
_L19-93_
- L22 _private member_ `FGuid ViewModelId;`
- L23 _private member_ `FName WidgetName;`
- L24 _private member_ `TWeakObjectPtr<UClass> Class;`
- L25 _private member_ `FText DisplayName;`
- L26 _private member_ `EMVVMBlueprintFieldPathSource Source = EMVVMBlueprintFieldPathSource::None;`
- L29 _public function_ `bool operator==(const FBindingSource& Other) const`
- L34 _public function_ `bool operator!=(const FBindingSource& Other) const`
- L47 _public function_ `bool IsValid() const`
- L52 _public function_ `EMVVMBlueprintFieldPathSource GetSource() const`
- L57 _public prototype_ `const UClass* GetClass() const;`
- L58 _public prototype_ `FText GetDisplayName() const;`
- L60 _public function_ `FName GetWidgetName() const`
- L65 _public function_ `FGuid GetViewModelId() const`
- L70 _public function_ `void Reset()`
- L79 _public prototype_ `FMVVMBindingName ToBindingName(const UWidgetBlueprint* WidgetBlueprint) const;`
- L80 _public prototype_ `void SetSourceTo(FMVVMBlueprintPropertyPath& PropertyPath) const;`
- L82 _public prototype_ `bool Matches(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintPropertyPath& PropertyPath) const;`
- L84 _public prototype_ `static FBindingSource CreateForBlueprint(const UWidgetBlueprint* WidgetBlueprint);`
- L85 _public prototype_ `static FBindingSource CreateForWidget(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget);`
- L86 _public prototype_ `static FBindingSource CreateForWidget(const UWidgetBlueprint* WidgetBlueprint, FName WidgetName);`
- L87 _public prototype_ `static FBindingSource CreateForWidgetComponent(const UWidgetBlueprint* WidgetBlueprint, FName WidgetName, UUIComponent* Component);`
- L88 _public prototype_ `static FBindingSource CreateForViewModel(const UWidgetBlueprint* WidgetBlueprint, FGuid ViewModelId);`
- L89 _public prototype_ `static FBindingSource CreateForViewModel(const UWidgetBlueprint* WidgetBlueprint, FName ViewModelName);`
- L90 _public prototype_ `static FBindingSource CreateForViewModel(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewModelContext& ViewModelContext);`
- L91 _public prototype_ `static FBindingSource CreateEmptySource(UClass* ViewModel);`
- L92 _public prototype_ `static FBindingSource CreateFromPropertyPath(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintPropertyPath& Path);`

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<UE::MVVM::FBindingSource>`  
_L98-104_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L101-103_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<UE::MVVM::FBindingSource>`  
_L107-149_
- L109 _public typedef_ `typedef UE::MVVM::FBindingSource NullableType;`
- L111 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FBindingSource, TSharedRef<ITableRow>, false>;`
- L112 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FBindingSource, FSparseItemInfo, false>;`
- L113 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FBindingSource>;`
- L116 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FBindingSource>&, TSet<UE::MVVM::FBindingSource>&, TMap<const U*, UE::MVVM::FBindingSource>&)`
- L123 _public function_ `static bool IsPtrValid(const UE::MVVM::FBindingSource& InPtr)`
- L128 _public function_ `static void ResetPtr(UE::MVVM::FBindingSource& InPtr)`
- L133 _public function_ `static UE::MVVM::FBindingSource MakeNullPtr()`
- L138 _public function_ `static UE::MVVM::FBindingSource NullableItemTypeConvertToItemType(const UE::MVVM::FBindingSource& InPtr)`
- L143 _public function_ `static FString DebugDump(UE::MVVM::FBindingSource InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L148-148_

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L39 _function_ `friend int32 GetTypeHash(const FBindingSource& InSource)` (scope `UE::MVVM`)
- L102 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon9862e7250103`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/BindingEntry/SMVVMBaseRow.h` (Private)


#### class `UE::MVVM::BindingEntry::SBaseRow`  
`class SBaseRow : public STableRow<TSharedPtr<FBindingEntry>>`  
_L25-60_
- inherits: `STableRow<TSharedPtr<FBindingEntry>>`
- L28 _public function_ `SLATE_BEGIN_ARGS(SBaseRow)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, SBindingsList* BindingsList, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FWidgetBlueprintEditor>& InBlueprintEditor, UWidgetBlueprint* InBlueprint, const TSharedPtr<FBindingEntry>& InEntry);`
- L33 _public function_ `TSharedPtr<FBindingEntry> GetEntry() const`
- L38 _public function_ `TSharedPtr<FWidgetBlueprintEditor> GetBlueprintEditor() const`
- L43 _public prototype_ `UWidgetBlueprint* GetBlueprint() const;`
- L44 _public prototype_ `UMVVMBlueprintView* GetBlueprintView() const;`
- L45 _public prototype_ `UMVVMEditorSubsystem* GetEditorSubsystem() const;`
- L48 _protected prototype_ `virtual TSharedRef<SWidget> BuildRowWidget() = 0;`
- L49 _protected prototype_ `virtual const ANSICHAR* GetTableRowStyle() const = 0;`
- L50 _protected prototype_ `virtual TSharedRef<SWidget> BuildContextMenuButton();`
- L53 _private prototype_ `TSharedRef<SWidget> HandleContextMenu() const;`
- L54 _private prototype_ `void HandleShowBlueprintGraph() const;`
- L56 _private member_ `TSharedPtr<FBindingEntry> BindingEntry;`
- L57 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WeakBlueprint;`
- L58 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakBlueprintEditor;`
- L59 _private member_ `SBindingsList* BindingsList;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)
- L19 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/BindingEntry/SMVVMBindingRow.h` (Private)


#### class `UE::MVVM::BindingEntry::SBindingRow`  
`class SBindingRow : public SBaseRow`  
_L24-101_
- inherits: `SBaseRow`
- L27 _public function_ `SLATE_BEGIN_ARGS(SBindingRow)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, SBindingsList* BindingsList, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FWidgetBlueprintEditor>& InBlueprintEditor, UWidgetBlueprint* InBlueprint, const TSharedPtr<FBindingEntry>& InEntry);`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> BuildRowWidget() override;`
- L34 _protected function_ `virtual const ANSICHAR* GetTableRowStyle() const override`
- L40 _private prototype_ `FMVVMBlueprintViewBinding* GetThisViewBinding() const;`
- L42 _private prototype_ `FSlateColor GetErrorBorderColor() const;`
- L44 _private prototype_ `ECheckBoxState IsBindingEnabled() const;`
- L46 _private prototype_ `ECheckBoxState IsBindingCompiled() const;`
- L48 _private prototype_ `EVisibility GetErrorButtonVisibility() const;`
- L50 _private prototype_ `FText GetErrorButtonToolTip() const;`
- L52 _private prototype_ `FReply OnErrorButtonClicked();`
- L54 _private prototype_ `TSharedRef<ITableRow> OnGenerateErrorRow(TSharedPtr<FText> Text, const TSharedRef<STableViewBase>& TableView) const;`
- L56 _private prototype_ `TArray<FBindingSource> GetAvailableViewModels() const;`
- L58 _private prototype_ `FMVVMLinkedPinValue GetFieldSelectedValue(bool bSource) const;`
- L60 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue Value, SFieldSelectorMenu::ESelectionType SelectionType, bool bSource);`
- L62 _private prototype_ `FFieldSelectionContext GetSelectedSelectionContext(bool bSource) const;`
- L64 _private prototype_ `FReply HandleFieldSelectorDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bSource);`
- L66 _private prototype_ `FReply HandleFieldSelectorDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bSource);`
- L68 _private prototype_ `ECheckBoxState IsExecutionModeOverrideChecked() const;`
- L70 _private prototype_ `void OnExecutionModeOverrideChanged(ECheckBoxState NewState);`
- L72 _private prototype_ `void OnExecutionModeSelectionChanged(EMVVMExecutionMode Value);`
- L74 _private prototype_ `TSharedRef<SWidget> OnGetExecutionModeMenuContent();`
- L76 _private prototype_ `FText GetExecutioModeValue() const;`
- L78 _private prototype_ `FText GetExecutioModeValueToolTip() const;`
- L80 _private prototype_ `bool IsExecutionModeOverridden() const;`
- L82 _private prototype_ `void OnIsBindingEnableChanged(ECheckBoxState NewState);`
- L84 _private prototype_ `void OnIsBindingCompileChanged(ECheckBoxState NewState);`
- L86 _private prototype_ `const FSlateBrush* GetBindingModeBrush(EMVVMBindingMode BindingMode) const;`
- L88 _private prototype_ `const FSlateBrush* GetCurrentBindingModeBrush() const;`
- L90 _private prototype_ `FText GetCurrentBindingModeLabel() const;`
- L92 _private prototype_ `FText GetBindingModeLabel(EMVVMBindingMode BindingMode) const;`
- L94 _private prototype_ `TSharedRef<SWidget> GenerateBindingModeWidget(FName ValueName) const;`
- L96 _private prototype_ `void OnBindingModeSelectionChanged(FName ValueName, ESelectInfo::Type);`
- L99 _private member_ `TArray<TSharedPtr<FText>> ErrorItems;`
- L100 _private member_ `EMVVMExecutionMode DefaultExecutionMode = EMVVMExecutionMode::DelayedWhenSharedElseImmediate;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MVVM` (scope `UE`)
- L18 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/BindingEntry/SMVVMConditionRow.h` (Private)


#### class `UE::MVVM::BindingEntry::SConditionRow`  
`class SConditionRow : public SBaseRow`  
_L22-83_
- inherits: `SBaseRow`
- L25 _public function_ `SLATE_BEGIN_ARGS(SConditionRow)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, SBindingsList* BindingsList, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FWidgetBlueprintEditor>& InBlueprintEditor, UWidgetBlueprint* InBlueprint, const TSharedPtr<FBindingEntry>& InEntry);`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> BuildRowWidget() override;`
- L32 _protected function_ `virtual const ANSICHAR* GetTableRowStyle() const override`
- L38 _private prototype_ `UMVVMBlueprintViewCondition* GetCondition() const;`
- L40 _private prototype_ `FSlateColor GetErrorBorderColor() const;`
- L42 _private prototype_ `EVisibility GetErrorButtonVisibility() const;`
- L44 _private prototype_ `FText GetErrorButtonToolTip() const;`
- L46 _private prototype_ `FReply OnErrorButtonClicked();`
- L48 _private prototype_ `TSharedRef<ITableRow> OnGenerateErrorRow(TSharedPtr<FText> Text, const TSharedRef<STableViewBase>& TableView) const;`
- L50 _private prototype_ `ECheckBoxState IsConditionEnabled() const;`
- L52 _private prototype_ `void OnIsConditionEnableChanged(ECheckBoxState NewState);`
- L54 _private prototype_ `ECheckBoxState IsConditionCompiled() const;`
- L56 _private prototype_ `void OnIsConditionCompileChanged(ECheckBoxState NewState);`
- L58 _private prototype_ `FMVVMLinkedPinValue GetFieldSelectedValue(bool bCondition) const;`
- L60 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue Value, SFieldSelectorMenu::ESelectionType SelectionType, bool bCondition);`
- L62 _private prototype_ `FFieldSelectionContext GetSelectedSelectionContext(bool bCondition) const;`
- L64 _private prototype_ `FReply HandleFieldSelectorDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bCondition);`
- L66 _private prototype_ `FReply HandleFieldSelectorOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bCondition);`
- L68 _private prototype_ `void OnConditionOperationSelectionChanged(FName ValueName, ESelectInfo::Type);`
- L69 _private prototype_ `FText GetCurrentConditionOperationLabel() const;`
- L70 _private prototype_ `TSharedRef<SWidget> GenerateConditionOperationWidget(FName ValueName) const;`
- L71 _private prototype_ `FText GetConditionOperationLabel(EMVVMConditionOperation Operation) const;`
- L72 _private prototype_ `EMVVMConditionOperation GetConditionOperationFromValueName(FName ValueName);`
- L74 _private prototype_ `TOptional<float> GetValue() const;`
- L75 _private prototype_ `TOptional<float> GetMaxValue() const;`
- L76 _private prototype_ `void OnValueChanged(float InValue);`
- L77 _private prototype_ `void OnMaxValueChanged(float InValue);`
- L78 _private prototype_ `EVisibility GetMaxValueVisibilityFromOperation() const;`
- L79 _private prototype_ `FText GetValueTooltipFromOperation() const;`
- L82 _private member_ `TArray<TSharedPtr<FText>> ErrorItems;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L16 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/BindingEntry/SMVVMEventRow.h` (Private)


#### class `UE::MVVM::BindingEntry::SEventRow`  
`class SEventRow : public SBaseRow`  
_L22-70_
- inherits: `SBaseRow`
- L25 _public function_ `SLATE_BEGIN_ARGS(SEventRow)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, SBindingsList* BindingsList, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FWidgetBlueprintEditor>& InBlueprintEditor, UWidgetBlueprint* InBlueprint, const TSharedPtr<FBindingEntry>& InEntry);`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> BuildRowWidget() override;`
- L32 _protected function_ `virtual const ANSICHAR* GetTableRowStyle() const override`
- L38 _private prototype_ `UMVVMBlueprintViewEvent* GetEvent() const;`
- L40 _private prototype_ `FSlateColor GetErrorBorderColor() const;`
- L42 _private prototype_ `EVisibility GetErrorButtonVisibility() const;`
- L44 _private prototype_ `FText GetErrorButtonToolTip() const;`
- L46 _private prototype_ `FReply OnErrorButtonClicked();`
- L48 _private prototype_ `TSharedRef<ITableRow> OnGenerateErrorRow(TSharedPtr<FText> Text, const TSharedRef<STableViewBase>& TableView) const;`
- L50 _private prototype_ `ECheckBoxState IsEventEnabled() const;`
- L52 _private prototype_ `void OnIsEventEnableChanged(ECheckBoxState NewState);`
- L54 _private prototype_ `ECheckBoxState IsEventCompiled() const;`
- L56 _private prototype_ `void OnIsEventCompileChanged(ECheckBoxState NewState);`
- L58 _private prototype_ `FMVVMLinkedPinValue GetFieldSelectedValue(bool bEvent) const;`
- L60 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue Value, SFieldSelectorMenu::ESelectionType SelectionType, bool bEvent);`
- L62 _private prototype_ `FFieldSelectionContext GetSelectedSelectionContext(bool bEvent) const;`
- L64 _private prototype_ `FReply HandleFieldSelectorDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bEvent);`
- L66 _private prototype_ `FReply HandleFieldSelectorDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bEvent);`
- L69 _private member_ `TArray<TSharedPtr<FText>> ErrorItems;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L16 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/BindingEntry/SMVVMFunctionParameterRow.h` (Private)


#### class `UE::MVVM::BindingEntry::SFunctionParameterRow`  
`class SFunctionParameterRow : public SBaseRow`  
_L16-24_
- inherits: `SBaseRow`
- L19 _protected prototype_ `virtual TSharedRef<SWidget> BuildRowWidget() override;`
- L20 _protected function_ `virtual const ANSICHAR* GetTableRowStyle() const override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L10 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/BindingEntry/SMVVMGroupRow.h` (Private)


#### class `UE::MVVM::BindingEntry::SGroupRow`  
`class SGroupRow : public SBaseRow`  
_L21-43_
- inherits: `SBaseRow`
- L24 _public function_ `SLATE_BEGIN_ARGS(SGroupRow)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, SBindingsList* BindingsList, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FWidgetBlueprintEditor>& InBlueprintEditor, UWidgetBlueprint* InBlueprint, const TSharedPtr<FBindingEntry>& InEntry);`
- L30 _protected prototype_ `virtual TSharedRef<SWidget> BuildRowWidget() override;`
- L31 _protected function_ `virtual const ANSICHAR* GetTableRowStyle() const override`
- L38 _private prototype_ `FBindingSource GetSelectedWidget() const;`
- L40 _private prototype_ `void SetSelectedWidget(FBindingSource Source);`
- L42 _private prototype_ `FReply AddBinding() const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MVVM` (scope `UE`)
- L15 _namespace_ `namespace BindingEntry` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMCachedViewBindingConversionFunction.h` (Private)


#### class `UE::MVVM::SCachedViewBindingConversionFunction`  
`class SCachedViewBindingConversionFunction : public SCompoundWidget`  
_L20-41_
- inherits: `SCompoundWidget`
- L23 _private typedef_ `using Super = SCompoundWidget;`
- L26 _public typedef_ `using FConversionFunctionVariant = TVariant<const UFunction*, TSubclassOf<UK2Node>, FEmptyVariantState>;`
- L27 _public prototype_ `DECLARE_DELEGATE_RetVal(FConversionFunctionVariant, FOnGetConversionFunction);`
- L29 _public function_ `SLATE_BEGIN_ARGS(SCachedViewBindingConversionFunction) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L32 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_EVENT(FOnGetConversionFunction, OnGetConversionFunction) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* WidgetBlueprint);`
- L39 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L40 _private member_ `FOnGetConversionFunction OnGetConversionFunction;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)
- L27 _delegate_ `DECLARE_DELEGATE_RetVal(FConversionFunctionVariant, FOnGetConversionFunction);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMCachedViewBindingPropertyPath.h` (Private)


#### class `UE::MVVM::SCachedViewBindingPropertyPath`  
`class SCachedViewBindingPropertyPath : public SCompoundWidget`  
_L20-46_
- inherits: `SCompoundWidget`
- L23 _private typedef_ `using Super = SCompoundWidget;`
- L26 _public prototype_ `DECLARE_DELEGATE_RetVal(FMVVMBlueprintPropertyPath, FOnGetPropertyPath);`
- L28 _public function_ `SLATE_BEGIN_ARGS(SCachedViewBindingPropertyPath) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L31 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_EVENT(FOnGetPropertyPath, OnGetPropertyPath) SLATE_ARGUMENT_DEFAULT(bool, ShowContext) = true;`
- L34 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowOnlyLastPath) = false;`
- L35 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowFieldNotify) = true;`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* WidgetBlueprint);`
- L39 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L43 _private member_ `TSharedPtr<SPropertyPath> PropertyPathWidget;`
- L44 _private member_ `FOnGetPropertyPath OnGetPropertyPath;`
- L45 _private member_ `FMVVMBlueprintPropertyPath CachedPropertyPath;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(FMVVMBlueprintPropertyPath, FOnGetPropertyPath);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMConditionParameter.h` (Private)


#### class `UE::MVVM::SConditionParameter`  
`class SConditionParameter : public SCompoundWidget`  
_L24-58_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SConditionParameter)`
- L28 _public prototype_ `SLATE_ARGUMENT_DEFAULT(UMVVMBlueprintViewCondition*, Condition) = nullptr;`
- L29 _public prototype_ `SLATE_ARGUMENT(FMVVMBlueprintPinId, ParameterId) SLATE_ARGUMENT_DEFAULT(bool, AllowDefault) = true;`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UWidgetBlueprint* WidgetBlueprint);`
- L36 _private prototype_ `ECheckBoxState OnGetIsBindArgumentChecked() const;`
- L37 _private prototype_ `void OnBindArgumentChecked(ECheckBoxState Checked);`
- L39 _private prototype_ `FMVVMLinkedPinValue OnGetSelectedField() const;`
- L40 _private prototype_ `void SetSelectedField(const FMVVMLinkedPinValue& Path);`
- L42 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue Value, SFieldSelectorMenu::ESelectionType SelectionType);`
- L43 _private prototype_ `FFieldSelectionContext GetSelectedSelectionContext() const;`
- L45 _private prototype_ `int32 GetCurrentWidgetIndex() const;`
- L48 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBlueprint;`
- L49 _private member_ `TWeakObjectPtr<UMVVMBlueprintViewCondition> ViewCondition;`
- L50 _private member_ `FMVVMBlueprintPinId ParameterId;`
- L52 _private member_ `TSharedPtr<SGraphPin> GraphPin;` — This reference is just to keep the default value widget alive.
- L54 _private member_ `FMVVMLinkedPinValue PreviousSelectedField;`
- L56 _private member_ `bool bAllowDefault = true;`
- L57 _private member_ `bool bDefaultValueVisible = true;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMEventParameter.h` (Private)


#### class `UE::MVVM::SEventParameter`  
`class SEventParameter : public SCompoundWidget`  
_L24-58_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SEventParameter)`
- L28 _public prototype_ `SLATE_ARGUMENT_DEFAULT(UMVVMBlueprintViewEvent*, Event) = nullptr;`
- L29 _public prototype_ `SLATE_ARGUMENT(FMVVMBlueprintPinId, ParameterId) SLATE_ARGUMENT_DEFAULT(bool, AllowDefault) = true;`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UWidgetBlueprint* WidgetBlueprint);`
- L36 _private prototype_ `ECheckBoxState OnGetIsBindArgumentChecked() const;`
- L37 _private prototype_ `void OnBindArgumentChecked(ECheckBoxState Checked);`
- L39 _private prototype_ `FMVVMLinkedPinValue OnGetSelectedField() const;`
- L40 _private prototype_ `void SetSelectedField(const FMVVMLinkedPinValue& Path);`
- L42 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue Value, SFieldSelectorMenu::ESelectionType SelectionType);`
- L43 _private prototype_ `FFieldSelectionContext GetSelectedSelectionContext() const;`
- L45 _private prototype_ `int32 GetCurrentWidgetIndex() const;`
- L48 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBlueprint;`
- L49 _private member_ `TWeakObjectPtr<UMVVMBlueprintViewEvent> ViewEvent;`
- L50 _private member_ `FMVVMBlueprintPinId ParameterId;`
- L52 _private member_ `TSharedPtr<SGraphPin> GraphPin;` — This reference is just to keep the default value widget alive.
- L54 _private member_ `FMVVMLinkedPinValue PreviousSelectedField;`
- L56 _private member_ `bool bAllowDefault = true;`
- L57 _private member_ `bool bDefaultValueVisible = true;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMFieldDisplay.h` (Private)


#### class `UE::MVVM::SFieldDisplay`  
`class SFieldDisplay : public SCompoundWidget`  
_L16-43_
- inherits: `SCompoundWidget`
- L19 _public prototype_ `DECLARE_DELEGATE_RetVal(FMVVMLinkedPinValue, FOnGetLinkedPinValue);`
- L21 _public function_ `SLATE_BEGIN_ARGS(SFieldDisplay) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L25 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT_DEFAULT(bool, ShowContext) = true;`
- L27 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowFieldNotify) = true;`
- L28 _public prototype_ `SLATE_EVENT(FOnGetLinkedPinValue, OnGetLinkedValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* InWidgetBlueprint);`
- L34 _private prototype_ `int32 GetCurrentDisplayIndex() const;`
- L35 _private prototype_ `FMVVMBlueprintPropertyPath HandleGetPropertyPath() const;`
- L36 _private prototype_ `TVariant<const UFunction*, TSubclassOf<UK2Node>, FEmptyVariantState> HandleGetConversionFunction() const;`
- L39 _public member_ `FOnGetLinkedPinValue OnGetLinkedValue;`
- L42 _private member_ `const FTextBlockStyle* TextStyle = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_RetVal(FMVVMLinkedPinValue, FOnGetLinkedPinValue);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMFieldEntry.h` (Private)


#### class `UE::MVVM::SFieldPaths`  
`class SFieldPaths : public SCompoundWidget`  
_L21-41_
- inherits: `SCompoundWidget`
- desc: Show the TArray<FMVVMBlueprintFieldPath>.
- L24 _public function_ `SLATE_BEGIN_ARGS(SFieldPaths) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L27 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT(TArrayView<UE::MVVM::FMVVMConstFieldVariant>, FieldPaths) SLATE_ARGUMENT(bool, ShowOnlyLast) SLATE_ARGUMENT(TOptional<FInt32Range>, HighlightField) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `void SetFieldPaths(TArrayView<UE::MVVM::FMVVMConstFieldVariant> InField);`
- L37 _private member_ `const FTextBlockStyle* TextStyle = nullptr;`
- L38 _private member_ `TSharedPtr<SHorizontalBox> FieldBox;`
- L39 _private member_ `TOptional<FInt32Range> HighlightField;`
- L40 _private member_ `bool bShowOnlyLast = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMFieldIcon.h` (Private)


#### class `UE::MVVM::SFieldIcon`  
`class SFieldIcon : public SCompoundWidget`  
_L13-25_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SFieldIcon)`
- L17 _public prototype_ `SLATE_ARGUMENT(FMVVMConstFieldVariant, Field) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L21 _public prototype_ `void RefreshBinding(const FMVVMConstFieldVariant& Field);`
- L24 _private member_ `TSharedPtr<SLayeredImage> LayeredImage;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMFieldSelector.h` (Private)


#### class `UE::MVVM::SFieldSelector`  
`class SFieldSelector : public SCompoundWidget`  
_L19-65_
- inherits: `SCompoundWidget`
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal(FFieldSelectionContext, FOnGetSelectionContext);`
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDrop, const FGeometry&, const FDragDropEvent&);`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDragOver, const FGeometry&, const FDragDropEvent&);`
- L26 _public function_ `SLATE_BEGIN_ARGS(SFieldSelector) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L30 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT_DEFAULT(bool, ShowContext) = true;`
- L32 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, IsBindingToEvent) = false;`
- L33 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowFieldNotify) = true;`
- L34 _public prototype_ `SLATE_EVENT(SFieldDisplay::FOnGetLinkedPinValue, OnGetLinkedValue) SLATE_EVENT(SFieldSelectorMenu::FOnLinkedValueSelected, OnSelectionChanged) SLATE_EVENT(FOnGetSelectionContext, OnGetSelectionContext) SLATE_EVENT(FOnDrop, OnDrop) SLATE_EVENT(FOnDragOver, OnDragOver) SLATE_ARGUMENT_DEFAULT(bool, CanCreateEvent) = false;`
- L40 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* InWidgetBlueprint);`
- L43 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L44 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L45 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L48 _private prototype_ `TSharedRef<SWidget> CreateSourcePanel();`
- L49 _private prototype_ `TSharedRef<SWidget> HandleGetMenuContent();`
- L51 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue NewValue, SFieldSelectorMenu::ESelectionType SelectionType);`
- L52 _private prototype_ `void HandleMenuClosed();`
- L55 _private member_ `TSharedPtr<SCachedViewBindingPropertyPath> PropertyPathWidget;`
- L56 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L57 _private member_ `TSharedPtr<SFieldDisplay> FieldDisplay;`
- L58 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L59 _private member_ `SFieldSelectorMenu::FOnLinkedValueSelected OnSelectionChanged;`
- L60 _private member_ `FOnGetSelectionContext OnGetSelectionContext;`
- L61 _private member_ `FOnDrop OnDropEvent;`
- L62 _private member_ `FOnDragOver OnDragOverEvent;`
- L63 _private member_ `bool bIsBindingToEvent = false;`
- L64 _private member_ `bool bCanCreateEvent = false;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(FFieldSelectionContext, FOnGetSelectionContext);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDrop, const FGeometry&, const FDragDropEvent&);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDragOver, const FGeometry&, const FDragDropEvent&);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMFieldSelectorMenu.h` (Private)


#### struct `TListTypeTraits`  
`template<> struct TListTypeTraits<UE::MVVM::FConversionFunctionValue>`  
_L29-68_
- L32 _public typedef_ `using NullableType = UE::MVVM::FConversionFunctionValue;`
- L33 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::FConversionFunctionValue, TSharedRef<ITableRow>, false>;`
- L34 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::FConversionFunctionValue, FSparseItemInfo, false>;`
- L35 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::FConversionFunctionValue>;`
- L38 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<UE::MVVM::FConversionFunctionValue>&, TSet<UE::MVVM::FConversionFunctionValue>&, TMap< const U*, UE::MVVM::FConversionFunctionValue>&)`
- L42 _public function_ `static bool IsPtrValid(UE::MVVM::FConversionFunctionValue InPtr)`
- L47 _public function_ `static void ResetPtr(UE::MVVM::FConversionFunctionValue& InPtr)`
- L52 _public function_ `static UE::MVVM::FConversionFunctionValue MakeNullPtr()`
- L57 _public function_ `static UE::MVVM::FConversionFunctionValue NullableItemTypeConvertToItemType(UE::MVVM::FConversionFunctionValue InPtr)`
- L62 _public function_ `static FString DebugDump( UE::MVVM::FConversionFunctionValue InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L67-67_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<UE::MVVM::FConversionFunctionValue>`  
_L71-77_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L74-76_

#### struct `UE::MVVM::FFieldSelectionContext`  
`struct FFieldSelectionContext`  
_L82-92_
- L84 _public member_ `EMVVMBindingMode BindingMode = EMVVMBindingMode::OneWayToDestination;`
- L85 _public member_ `const FProperty* AssignableTo = nullptr;`
- L86 _public member_ `TOptional<FBindingSource> FixedBindingSource;`
- L87 _public member_ `bool bAllowWidgets = true;`
- L88 _public member_ `bool bAllowViewModels = true;`
- L89 _public member_ `bool bAllowConversionFunctions = true;`
- L90 _public member_ `bool bReadable = true;`
- L91 _public member_ `bool bWritable = true;`

#### class `UE::MVVM::SFieldSelectorMenu`  
`class SFieldSelectorMenu : public SCompoundWidget`  
_L94-237_
- inherits: `SCompoundWidget`
- L104 _public prototype_ `DECLARE_DELEGATE_RetVal(FFieldSelectionContext, FOnGetFieldSelectionContext);`
- L105 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnLinkedValueSelected, FMVVMLinkedPinValue, ESelectionType);`
- L106 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnLinkedValueConversionSelected, FMVVMLinkedPinValue, const FMVVMFieldConversion&, ESelectionType);`
- L108 _public function_ `SLATE_BEGIN_ARGS(SFieldSelectorMenu)`
- L109 _public function_ `SLATE_ARGUMENT(TOptional<FMVVMLinkedPinValue>, CurrentSelected) SLATE_EVENT(FOnLinkedValueSelected, OnSelected) SLATE_EVENT(FOnLinkedValueConversionSelected, OnSelectedConversion) SLATE_EVENT(FSimpleDelegate, OnMenuCloseRequested) SLATE_ARGUMENT(FFieldSelectionContext, SelectionContext) SLATE_ARGUMENT_DEFAULT(bool, IsBindingToEvent)`
- L115 _public function_ `SLATE_ARGUMENT_DEFAULT(bool, CanCreateEvent)`
- L116 _public function_ `SLATE_ARGUMENT_DEFAULT(bool, IsEnableContextToggleAvailable)`
- L117 _public function_ `SLATE_ARGUMENT_DEFAULT(bool, IsClearEnableable)`
- L118 _public function_ `SLATE_ARGUMENT_DEFAULT(bool, ShowTooltipText)`
- L125 _public function_ `SLATE_ARGUMENT_DEFAULT(bool, CanConvertField)` — If CanConvertField is set to true - Menu will display Fields that can be converted to the Selected Property. - Selections will be return via OnSelectedConversion
- L126 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* InWidgetBlueprint);`
- L129 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L131 _public prototype_ `TSharedRef<SWidget> GetWidgetToFocus() const;`
- L146 _private prototype_ `void SetPropertyPathSelection(const FMVVMBlueprintPropertyPath& SelectedPath);`
- L147 _private prototype_ `void SetConversionFunctionSelection(const UE::MVVM::FConversionFunctionValue SelectedFunction);`
- L149 _private prototype_ `TSharedRef<SWidget> CreateBindingContextPanel(const FArguments& InArgs);`
- L150 _private prototype_ `TSharedRef<SWidget> CreateBindingListPanel(const FArguments& InArgs, const FProperty* AssignableToProperty);`
- L152 _private prototype_ `void HandleWidgetSelected(FName WidgetName, ESelectInfo::Type);`
- L154 _private prototype_ `void HandleViewModelSelected(FBindingSource ViewModel, ESelectInfo::Type);`
- L155 _private prototype_ `TSharedRef<ITableRow> HandleGenerateViewModelRow(MVVM::FBindingSource ViewModel, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L157 _private prototype_ `int32 SortConversionFunctionItemsRecursive(TArray<TSharedPtr<FConversionFunctionItem>>& Items);`
- L158 _private prototype_ `void GenerateConversionFunctionItems();`
- L159 _private prototype_ `void FilterConversionFunctionCategories();`
- L160 _private prototype_ `void FilterConversionFunctions();`
- L162 _private prototype_ `int32 FilterConversionFunctionCategoryChildren(const TArray<FString>& FilterStrings, const TArray<TSharedPtr<FConversionFunctionItem>>& SourceArray, TArray<TSharedPtr<FConversionFunctionItem>>& OutDestArray);` — Recursively filter the items in SourceArray and place them into DestArray. Returns true if any items were added.
- L163 _private prototype_ `void AddConversionFunctionChildrenRecursive(const TSharedPtr<FConversionFunctionItem>& Parent, TArray<UE::MVVM::FConversionFunctionValue>& OutFunctions);`
- L164 _private prototype_ `TSharedPtr<FConversionFunctionItem> FindOrCreateItemForCategory(TArray<TSharedPtr<FConversionFunctionItem>>& Items, TArrayView<FString> CategoryPath);`
- L165 _private prototype_ `TSharedPtr<FConversionFunctionItem> FindConversionFunctionCategory(const TArray<TSharedPtr<FConversionFunctionItem>>& Items, TArrayView<FString> CategoryNameParts) const;`
- L166 _private prototype_ `void HandleGetConversionFunctionCategoryChildren(TSharedPtr<FConversionFunctionItem> Item, TArray<TSharedPtr<FConversionFunctionItem>>& OutItems) const;`
- L167 _private prototype_ `void HandleConversionFunctionCategorySelected(TSharedPtr<FConversionFunctionItem> Item, ESelectInfo::Type);`
- L168 _private prototype_ `TSharedRef<ITableRow> HandleGenerateConversionFunctionCategoryRow(TSharedPtr<FConversionFunctionItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L169 _private prototype_ `TSharedRef<ITableRow> HandleGenerateConversionFunctionRow(const UE::MVVM::FConversionFunctionValue Function, const TSharedRef<STableViewBase>& OwnerTable);`
- L171 _private prototype_ `TSharedPtr<FConversionFunctionItem> ExpandFunctionCategoryTreeToItem(const UE::MVVM::FConversionFunctionValue Function);`
- L172 _private prototype_ `void ExpandFunctionCategoryTree(const TArray<TSharedPtr<FConversionFunctionItem>>& Items, bool bRecursive);`
- L174 _private prototype_ `void FilterViewModels(const FText& NewText);`
- L175 _private prototype_ `void HandleSearchBoxTextChanged(const FText& NewText);`
- L176 _private prototype_ `void HandleEnabledContextToggleChanged(ECheckBoxState CheckState);`
- L177 _private prototype_ `ECheckBoxState ToggleEnabledContext() const;`
- L179 _private prototype_ `TOptional<FMVVMLinkedPinValue> GetCurrentSelection() const;`
- L180 _private prototype_ `void UpdateSelection();`
- L181 _private prototype_ `void SetSelectedValue(const TOptional<FMVVMLinkedPinValue>& NewSelection);`
- L183 _private prototype_ `FText GetTooltipText() const;`
- L184 _private prototype_ `FText GetAdditionalTooltipText() const;`
- L185 _private prototype_ `FMVVMBlueprintPropertyPath GetTooltipPropertyPath() const;`
- L187 _private prototype_ `bool IsSelectEnabled() const;`
- L188 _private prototype_ `bool IsEventSelectEnabled() const;`
- L190 _private prototype_ `FReply HandleSelectClicked();`
- L191 _private prototype_ `FReply HandleEventSelectClicked();`
- L192 _private prototype_ `FReply HandleClearClicked();`
- L193 _private prototype_ `FReply HandleCancelClicked();`
- L195 _private prototype_ `FReply PromptConversionSelection();`
- L198 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L199 _private member_ `FOnLinkedValueSelected OnSelected;`
- L200 _private member_ `FOnLinkedValueConversionSelected OnSelectedConversion;`
- L202 _private member_ `FSimpleDelegate OnMenuCloseRequested;`
- L203 _private member_ `FFieldSelectionContext SelectionContext;`
- L205 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L206 _private member_ `TSharedPtr<SPrimaryButton> EventSelectButton;`
- L209 _private member_ `TSharedPtr<SListView<FBindingSource>> ViewModelList;`
- L210 _private member_ `TArray<FBindingSource> ViewModelSources;`
- L211 _private member_ `TArray<FBindingSource> FilteredViewModelSources;`
- L214 _private member_ `TSharedPtr<SReadOnlyHierarchyView> WidgetList;`
- L217 _private member_ `TSharedPtr<SSourceBindingList> BindingList;`
- L220 _private member_ `TSharedPtr<STreeView<TSharedPtr<FConversionFunctionItem>>> ConversionFunctionCategoryTree;`
- L221 _private member_ `TArray<TSharedPtr<FConversionFunctionItem>> FilteredConversionFunctionRoot;`
- L222 _private member_ `TArray<TSharedPtr<FConversionFunctionItem>> ConversionFunctionRoot;`
- L225 _private member_ `TSharedPtr<SListView<UE::MVVM::FConversionFunctionValue>> ConversionFunctionList;`
- L226 _private member_ `TArray<UE::MVVM::FConversionFunctionValue> ConversionFunctions;`
- L227 _private member_ `TArray<UE::MVVM::FConversionFunctionValue> FilteredConversionFunctions;`
- L228 _private member_ `TArray<FMVVMFieldConversion> AvailableFieldConversions;`
- L230 _private member_ `TOptional<FMVVMLinkedPinValue> CurrentSelectedValue;`
- L231 _private member_ `TOptional<FMVVMFieldConversion> CurrentSelectedConversionValue;`
- L233 _private member_ `bool bIsMenuInitialized = false;`
- L234 _private member_ `bool bCanCreateEvent = false;`
- L235 _private member_ `bool bCanConvertField = false;`
- L236 _private member_ `bool bIsSelectingConversion = false;`

#### enum `UE::MVVM::SFieldSelectorMenu::ESelectionType`  
`enum class ESelectionType`  
_L97-102_
- L99 _public enumerator_ `None`
- L100 _public enumerator_ `Binding`
- L101 _public enumerator_ `Event`

#### struct `UE::MVVM::SFieldSelectorMenu::FConversionFunctionItem`  
`struct FConversionFunctionItem`  
_L134-143_
- L136 _public function_ `FString GetCategoryName()`
- L138 _public member_ `TArray<FString> CategoryPath;`
- L139 _public member_ `TArray<FString> SearchKeywords;`
- L140 _public member_ `UE::MVVM::FConversionFunctionValue Function;`
- L141 _public member_ `TArray<TSharedPtr<FConversionFunctionItem>> Children;`
- L142 _public member_ `int32 NumFunctions = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ESelectInfo`
- L75 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon85990ea80103`)
- L79 _namespace_ `namespace UE`
- L79 _namespace_ `namespace MVVM` (scope `UE`)
- L104 _delegate_ `DECLARE_DELEGATE_RetVal(FFieldSelectionContext, FOnGetFieldSelectionContext);`
- L105 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLinkedValueSelected, FMVVMLinkedPinValue, ESelectionType);`
- L106 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnLinkedValueConversionSelected, FMVVMLinkedPinValue, const FMVVMFieldConversion&, ESelectionType);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMFunctionParameter.h` (Private)


#### class `UE::MVVM::SFunctionParameter`  
`class SFunctionParameter : public SCompoundWidget`  
_L25-64_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SFunctionParameter)`
- L29 _public prototype_ `SLATE_ARGUMENT(FGuid, BindingId) SLATE_ARGUMENT(FMVVMBlueprintPinId, ParameterId) SLATE_ARGUMENT_DEFAULT(bool, SourceToDestination) = true;`
- L32 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, AllowDefault) = true;`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UWidgetBlueprint* WidgetBlueprint);`
- L38 _private prototype_ `ECheckBoxState OnGetIsBindArgumentChecked() const;`
- L39 _private prototype_ `void OnBindArgumentChecked(ECheckBoxState Checked);`
- L41 _private prototype_ `FMVVMLinkedPinValue OnGetSelectedField() const;`
- L42 _private prototype_ `void SetSelectedField(const FMVVMLinkedPinValue& Path);`
- L44 _private prototype_ `void HandleFieldSelectionChanged(FMVVMLinkedPinValue Value, SFieldSelectorMenu::ESelectionType SelectionType);`
- L45 _private prototype_ `FFieldSelectionContext GetSelectedSelectionContext() const;`
- L47 _private prototype_ `FReply HandleFieldSelectorDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L48 _private prototype_ `FReply HandleFieldSelectorDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L50 _private prototype_ `int32 GetCurrentWidgetIndex() const;`
- L53 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBlueprint;`
- L54 _private member_ `FGuid BindingId;`
- L55 _private member_ `FMVVMBlueprintPinId ParameterId;`
- L57 _private member_ `TSharedPtr<SGraphPin> GraphPin;` — This reference is just to keep the default value widget alive.
- L59 _private member_ `FMVVMLinkedPinValue PreviousSelectedField;`
- L61 _private member_ `bool bSourceToDestination = true;`
- L62 _private member_ `bool bAllowDefault = true;`
- L63 _private member_ `bool bDefaultValueVisible = true;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMPopoutEditor.h` (Private)


#### class `UE::MVVM::SMVVMPopoutEditor`  
`class SMVVMPopoutEditor : public SCompoundWidget`  
_L24-47_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SMVVMPopoutEditor) : _bReadOnly(true)`
- L30 _public prototype_ `SLATE_ARGUMENT(bool, bReadOnly) SLATE_END_ARGS() static void OpenPopoutEditor(TNotNull<UObject*> InObjectToInspect, bool bInReadOnly = true);`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, UObject* InObjectToInspect);`
- L38 _private member_ `TWeakObjectPtr<UObject> ObjectWeak;`
- L39 _private member_ `TUniquePtr<UE::PropertyViewer::FFieldIterator_BlueprintVisible> FieldIterator;`
- L40 _private member_ `TUniquePtr<UE::PropertyViewer::FFieldExpander_Default> FieldExpander;`
- L41 _private member_ `TSharedPtr<UE::PropertyViewer::SPropertyViewer> PropertyViewer;`
- L43 _private prototype_ `TSharedPtr<SWidget> HandleGetPreSlot(UE::PropertyViewer::SPropertyViewer::FHandle Handle, TArrayView<const FFieldVariant> FieldPath);`
- L44 _private prototype_ `TSharedRef<SWidget> HandleGenerateContainer(UE::PropertyViewer::SPropertyViewer::FHandle ContainerHandle, TOptional<FText> DisplayName);`
- L46 _private prototype_ `TSharedRef<SWidget> ConstructFieldPreSlot(const UObject* InObject, UE::PropertyViewer::SPropertyViewer::FHandle Handle, const FFieldVariant FieldPath, const bool bIsForEvent = false);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMPropertyPath.h` (Private)


#### class `UE::MVVM::SPropertyPath`  
`class SPropertyPath : public SCompoundWidget`  
_L17-40_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SPropertyPath) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L23 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT(FMVVMBlueprintPropertyPath, PropertyPath) SLATE_ARGUMENT_DEFAULT(bool, ShowContext) = true;`
- L26 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowOnlyLastPath) = false;`
- L27 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowFieldNotify) = true;`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* WidgetBlueprint);`
- L31 _public prototype_ `void SetPropertyPath(const FMVVMBlueprintPropertyPath& InPropertyPath);`
- L34 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L35 _private member_ `const FTextBlockStyle* TextStyle = nullptr;`
- L36 _private member_ `TSharedPtr<SHorizontalBox> FieldBox;`
- L37 _private member_ `bool bShowContext = false;`
- L38 _private member_ `bool bShowOnlyLastPath = false;`
- L39 _private member_ `bool bShowFieldNotify = true;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMSelectViewModel.h` (Private)


#### class `UE::MVVM::FViewModelClassFilter`  
`class FViewModelClassFilter : public IClassViewerFilter`  
_L16-25_
- inherits: `IClassViewerFilter`
- L19 _public prototype_ `FViewModelClassFilter() = default;`
- L21 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override;`
- L22 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override;`
- L24 _public member_ `EClassFlags DisallowedClassFlags = CLASS_HideDropDown | CLASS_Hidden | CLASS_Deprecated | CLASS_Abstract;`

#### class `UE::MVVM::SMVVMSelectViewModel`  
`class SMVVMSelectViewModel : public SCompoundWidget`  
_L27-55_
- inherits: `SCompoundWidget`
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, const UClass*);`
- L32 _public function_ `SLATE_BEGIN_ARGS(SMVVMSelectViewModel)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, const UWidgetBlueprint* WidgetBlueprint);`
- L42 _private prototype_ `void HandleClassPicked(UClass* ClassPicked);`
- L43 _private prototype_ `FReply HandleSelected();`
- L44 _private prototype_ `FReply HandleCancel();`
- L45 _private prototype_ `bool HandleIsSelectionEnabled() const;`
- L48 _private member_ `TSharedPtr<SWidget> ClassViewer;`
- L49 _private member_ `TSharedPtr<SSourceBindingList> BindingListWidget;`
- L50 _private member_ `TWeakObjectPtr<const UClass> SelectedClass;`
- L52 _private member_ `FSimpleDelegate OnCancel;`
- L53 _private member_ `FOnValueChanged OnViewModelCommitted;`
- L54 _private member_ `EClassFlags DisallowedClassFlags;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, const UClass*);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMSourceEntry.h` (Private)


#### class `UE::MVVM::SBindingContextEntry`  
`class SBindingContextEntry : public SCompoundWidget`  
_L17-36_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SBindingContextEntry) : _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L24 _public function_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT(UE::MVVM::FBindingSource, BindingContext) SLATE_ARGUMENT_DEFAULT(FText, ToolTipDescription)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _public prototype_ `void RefreshSource(const UE::MVVM::FBindingSource& Source);`
- L33 _private member_ `TSharedPtr<STextBlock> Label;`
- L34 _private member_ `TSharedPtr<SImage> Image;`
- L35 _private member_ `FText ToolTipDescription;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMSourceSelector.h` (Private)


#### class `UE::MVVM::SBindingContextSelector`  
`class SBindingContextSelector : public SCompoundWidget`  
_L22-76_
- inherits: `SCompoundWidget`
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FSelectionChanged, FBindingSource);`
- L27 _public function_ `SLATE_BEGIN_ARGS(SBindingContextSelector) : _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) )`
- L31 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT_DEFAULT(bool, ShowClear) = true;`
- L33 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, AutoRefresh) = false;`
- L34 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ViewModels) = false;`
- L35 _public prototype_ `SLATE_ATTRIBUTE(FBindingSource, SelectedBindingSource) SLATE_EVENT(FSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* InWidgetBlueprint);`
- L40 _public prototype_ `void Refresh();`
- L43 _private prototype_ `void OnViewModelSelectionChanged(FBindingSource Selected, ESelectInfo::Type SelectionType);`
- L44 _private prototype_ `void OnWidgetSelectionChanged(FName SelectedName, ESelectInfo::Type SelectionType);`
- L45 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L47 _private prototype_ `FReply HandleSelect();`
- L48 _private prototype_ `FReply HandleCancel();`
- L49 _private prototype_ `bool IsSelectEnabled() const;`
- L51 _private prototype_ `EVisibility GetClearVisibility() const;`
- L52 _private prototype_ `FReply OnClearSource();`
- L54 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FBindingSource Source, const TSharedRef<STableViewBase>& OwnerTable);`
- L57 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L58 _private member_ `FSelectionChanged OnSelectionChangedDelegate;`
- L59 _private member_ `const FTextBlockStyle* TextStyle = nullptr;`
- L61 _private member_ `TAttribute<TArray<FBindingSource>> AvailableSourcesAttribute;`
- L62 _private member_ `TAttribute<FBindingSource> SelectedSourceAttribute;`
- L64 _private member_ `TArray<FBindingSource> ViewModelSources;`
- L65 _private member_ `FBindingSource InitialSource;`
- L66 _private member_ `FBindingSource SelectedSource;`
- L68 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L69 _private member_ `TSharedPtr<SListView<FBindingSource>> ViewModelList;`
- L70 _private member_ `TSharedPtr<SReadOnlyHierarchyView> WidgetHierarchy;`
- L71 _private member_ `TSharedPtr<SBindingContextEntry> SelectedSourceWidget;`
- L73 _private member_ `bool bAutoRefresh = false;`
- L74 _private member_ `bool bViewModels = false;`
- L75 _private member_ `bool bShowClear = true;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ESelectInfo`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FSelectionChanged, FBindingSource);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMViewBindingListView.h` (Private)


#### class `UE::MVVM::SBindingsList`  
`class SBindingsList : public SCompoundWidget`  
_L26-93_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SBindingsList)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SBindingsPanel> Owner, TSharedPtr<FWidgetBlueprintEditor> BlueprintEditor, UMVVMWidgetBlueprintExtension_View* MVVMExtension);`
- L33 _public prototype_ `~SBindingsList();`
- L35 _public prototype_ `void Refresh();`
- L37 _public prototype_ `void EventParametersRegenerate(UMVVMBlueprintViewEvent* Event);`
- L38 _public prototype_ `void ConditionParametersRegenerate(UMVVMBlueprintViewCondition* Condition);`
- L40 _public prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L41 _public prototype_ `void ClearFilterText();`
- L44 _public prototype_ `TSharedPtr<SWidget> OnSourceConstructContextMenu();` — Constructs context menu used for right click and dropdown button
- L46 _public prototype_ `void RequestNavigateToBinding(FGuid BindingId);`
- L47 _public prototype_ `void RequestNavigateToEvent(UMVVMBlueprintViewEvent* Event);`
- L48 _public prototype_ `void RequestNavigateToCondition(UMVVMBlueprintViewCondition* Condition);`
- L50 _public prototype_ `void SetRootGroupsExpansion(bool InIsExpanded);`
- L51 _public prototype_ `void SetBindingsExpansion(bool InIsExpanded);`
- L53 _public prototype_ `void SetSelection(TConstArrayView<const TSharedPtr<FBindingEntry>> InEntries);`
- L55 _public prototype_ `void SelectBinding(FGuid BindingId, bool bShouldScrollIntoView);`
- L56 _public prototype_ `void SelectEvent(const UMVVMBlueprintViewEvent* Event, bool bShouldScrollIntoView);`
- L57 _public prototype_ `void SelectCondition(const UMVVMBlueprintViewCondition* Condition, bool bShouldScrollIntoView);`
- L58 _public prototype_ `void SelectParameter(const FMVVMBlueprintPinId& PinId, bool bShouldScrollIntoView);`
- L67 _public prototype_ `EFilterMode GetActiveFilterMode() const;`
- L68 _public prototype_ `void OnActiveFilterModeChanged(EFilterMode InFilterMode);`
- L71 _private prototype_ `TSharedRef<ITableRow> GenerateEntryRow(TSharedPtr<FBindingEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L72 _private prototype_ `void OnSourceListSelectionChanged(TSharedPtr<FBindingEntry> Entry, ESelectInfo::Type SelectionType) const;`
- L73 _private prototype_ `void GetChildrenOfEntry(TSharedPtr<FBindingEntry> Entry, TArray<TSharedPtr<FBindingEntry>>& OutChildren) const;`
- L75 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L77 _private prototype_ `void ForceRefresh();`
- L79 _private prototype_ `template<typename TEntryValueType> void RegisterWrapperGraphModified(TEntryValueType* EntryValue, TSharedPtr<FBindingEntry> GroupEntry);`
- L80 _private prototype_ `void HandleRefreshChildren(FObjectKey EntryKey);`
- L83 _private member_ `TWeakPtr<SBindingsPanel> BindingPanel;`
- L84 _private member_ `TSharedPtr<STreeView<TSharedPtr<FBindingEntry>>> TreeView;`
- L85 _private member_ `TMap<FObjectKey, TPair<TWeakPtr<FBindingEntry>, FDelegateHandle>> WrapperGraphModifiedDelegates;`
- L86 _private member_ `TArray<TSharedPtr<FBindingEntry>> AllRootGroups;`
- L87 _private member_ `TArray<TSharedPtr<FBindingEntry>> FilteredRootGroups;`
- L88 _private member_ `TWeakObjectPtr<UMVVMWidgetBlueprintExtension_View> MVVMExtension;`
- L89 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakBlueprintEditor;`
- L90 _private member_ `mutable bool bSelectionChangedGuard = false;`
- L91 _private member_ `FText FilterText;`
- L92 _private member_ `EFilterMode FilterMode = EFilterMode::All;`

#### enum `UE::MVVM::SBindingsList::EFilterMode`  
`enum class EFilterMode : uint8`  
_L60-65_
- L62 _public enumerator_ `All = 0` — Display all bindings, no filtering
- L63 _public enumerator_ `Viewmodel = 1` — Display only bindings associated to a viewmodel
- L64 _public enumerator_ `Verse = 2` — Display only bindings associated to a verse field

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMViewBindingPanel.h` (Private)


#### class `UE::MVVM::SBindingsPanel`  
`class SBindingsPanel : public SCompoundWidget`  
_L28-113_
- inherits: `SCompoundWidget`
- L31 _private typedef_ `using Super = SCompoundWidget;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SBindingsPanel)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor>, bool bInIsDrawerTab);`
- L38 _public prototype_ `virtual ~SBindingsPanel();`
- L41 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L42 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L44 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L45 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L46 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L49 _public prototype_ `void OnBindingListSelectionChanged(TConstArrayView<FBindingsSelectionVariantType> Selection);`
- L50 _public prototype_ `bool IsFilterModeEnabled() const;`
- L52 _public prototype_ `static void RegisterSettingsMenu();`
- L61 _private prototype_ `void LoadSettings();`
- L62 _private prototype_ `void SaveSettings();`
- L64 _private prototype_ `void HandleBlueprintViewChangedDelegate();`
- L66 _private prototype_ `TSharedRef<SWidget> GenerateEditViewWidget();`
- L68 _private prototype_ `void AddBindingToWidgetList(const TSet<FWidgetReference>& WidgetsToAddBinding);`
- L69 _private prototype_ `void AddDefaultBinding();`
- L70 _private prototype_ `bool CanAddBinding() const;`
- L71 _private prototype_ `FText GetAddBindingText() const;`
- L72 _private prototype_ `FText GetAddBindingToolTip() const;`
- L73 _private prototype_ `TSharedRef<SWidget> HandleAddDefaultBindingContextMenu();`
- L74 _private prototype_ `void HandleAddDefaultBindingButtonClick(EAddBindingMode NewMode);`
- L76 _private prototype_ `void AddEmptyCondition();`
- L77 _private prototype_ `bool CanAddEmptyCondition() const;`
- L78 _private prototype_ `FText GetAddEmptyConditionToolTip() const;`
- L80 _private prototype_ `TSharedRef<SWidget> GenerateSettingsMenu();`
- L82 _private prototype_ `TSharedRef<SWidget> CreateDrawerDockButton();`
- L83 _private prototype_ `FReply CreateDrawerDockButtonClicked();`
- L85 _private prototype_ `void HandleExtensionAdded(UBlueprintExtension* NewExtension);`
- L87 _private prototype_ `FReply HandleCreateViewModelClicked();`
- L89 _private prototype_ `bool IsDetailsViewEditingEnabled() const;`
- L90 _private prototype_ `void RefreshDetailsView();`
- L91 _private prototype_ `void RefreshNotifyHookBinding();`
- L92 _private prototype_ `void SetDetailsView(TUnion<UObject*, TSharedPtr<FStructOnScope>> ObjectOrStruct, const FText& ErrorMessage = FText::GetEmpty());`
- L94 _private prototype_ `EVisibility GetViewModelMessageVisibility() const;`
- L95 _private prototype_ `EVisibility GetBindingMessageVisibility() const;`
- L97 _private prototype_ `EVisibility GetVisibility(bool bVisibleWithBindings) const;`
- L99 _private prototype_ `ECheckBoxState GetDetailsVisibleCheckState() const;`
- L100 _private prototype_ `void ToggleDetailsVisibility();`
- L103 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakBlueprintEditor;`
- L104 _private member_ `TSharedPtr<SBindingsList> BindingsList;`
- L105 _private member_ `TSharedPtr<SBorder> DetailContainer;`
- L106 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L107 _private member_ `TSharedPtr<IStructureDetailsView> StructDetailsView;`
- L108 _private member_ `TWeakObjectPtr<UMVVMWidgetBlueprintExtension_View> MVVMExtension;`
- L109 _private member_ `TPimplPtr<Private::FStructDetailNotifyHook> NotifyHook;`
- L110 _private member_ `FDelegateHandle BlueprintViewChangedDelegateHandle;`
- L111 _private member_ `EAddBindingMode AddBindingMode = EAddBindingMode::Selected;`
- L112 _private member_ `bool bIsDrawerTab;`

#### enum `UE::MVVM::SBindingsPanel::EAddBindingMode`  
`enum class EAddBindingMode`  
_L55-59_
- L57 _public enumerator_ `Selected = 0`
- L58 _public enumerator_ `Empty = 1`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MVVM` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::MVVM`)
- L26 _typedef_ `using FBindingsSelectionVariantType = TVariant<FMVVMBlueprintViewBinding*, UMVVMBlueprintViewCondition*, UMVVMBlueprintViewEvent*>;` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMViewModelBindingListWidget.h` (Private)


#### enum `UE::MVVM::EFieldVisibility`  
`enum class EFieldVisibility : uint8`  
_L22-29_
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `Readable = 1 << 1`
- L26 _public enumerator_ `Writable = 1 << 2`
- L27 _public enumerator_ `Notify = 1 << 3`
- L28 _public enumerator_ `All = 0xff`

#### class `UE::MVVM::FFieldIterator_Bindable`  
`class FFieldIterator_Bindable : public UE::PropertyViewer::FFieldIterator_BlueprintVisible`  
_L36-63_
- inherits: `UE::PropertyViewer::FFieldIterator_BlueprintVisible`
- L39 _public prototype_ `FFieldIterator_Bindable(const UWidgetBlueprint* WidgetBlueprint, EFieldVisibility InVisibilityFlags, const FProperty* InAssignableTo = nullptr, const bool InIsBindingToEvent = false, const bool bEnableConversion = false);`
- L40 _public prototype_ `virtual TArray<FFieldVariant> GetFields(const UStruct* Struct, const FName FieldName, const UStruct* Container) const override;`
- L41 _public function_ `EFieldVisibility GetFieldVisibilityFlags() const`
- L45 _public function_ `const FProperty* GetAssignableTo() const`
- L49 _public function_ `bool IsConversionEnabled() const`
- L53 _public function_ `void EnableConversion(bool InEnabled)`
- L58 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L59 _private member_ `EFieldVisibility FieldVisibilityFlags = EFieldVisibility::All;`
- L60 _private member_ `const FProperty* AssignableTo = nullptr;`
- L61 _private member_ `bool bIsBindingToEvent = false;`
- L62 _private member_ `bool bEnableConversion = false;`

#### class `UE::MVVM::FFieldExpander_Bindable`  
`class FFieldExpander_Bindable : public UE::PropertyViewer::FFieldExpander_Default`  
_L68-75_
- inherits: `UE::PropertyViewer::FFieldExpander_Default`
- L71 _public prototype_ `FFieldExpander_Bindable();`
- L72 _public prototype_ `virtual TOptional<const UClass*> CanExpandObject(const FObjectPropertyBase* Property, const UObject* Instance) const override;`
- L73 _public prototype_ `virtual bool CanExpandScriptStruct(const FStructProperty*) const override;`
- L74 _public prototype_ `virtual TOptional<const UStruct*> GetExpandedFunction(const UFunction* Function) const override;`

#### struct `UE::MVVM::FMVVMFieldConversion`  
`struct FMVVMFieldConversion : TSharedFromThis<FMVVMFieldConversion>`  
_L80-91_
- inherits: `TSharedFromThis<FMVVMFieldConversion>`
- L82 _public prototype_ `FMVVMFieldConversion() = default;`
- L83 _public prototype_ `FMVVMFieldConversion(FConversionFunctionValue Function, FMVVMBlueprintPinId ParameterId);`
- L85 _public member_ `FConversionFunctionValue Function;`
- L86 _public member_ `FMVVMBlueprintPinId ParameterId;`
- L88 _public prototype_ `bool IsValid() const;`
- L89 _public prototype_ `FName GetFName() const;`
- L90 _public prototype_ `FMVVMBlueprintFunctionReference ToBlueprintFunctionReference(UBlueprint* Blueprint) const;`

#### class `UE::MVVM::SSourceBindingList`  
`class SSourceBindingList : public SCompoundWidget`  
_L96-163_
- inherits: `SCompoundWidget`
- L99 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDoubleClicked, const FMVVMBlueprintPropertyPath&);`
- L101 _public function_ `SLATE_BEGIN_ARGS(SSourceBindingList)`
- L102 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowSearchBox) = false;`
- L103 _public prototype_ `SLATE_ARGUMENT_DEFAULT(EFieldVisibility, FieldVisibilityFlags) = EFieldVisibility::All;`
- L104 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, EnableSelection) = true;`
- L105 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, IsBindingToEvent) = false;`
- L112 _public prototype_ `SLATE_ARGUMENT_DEFAULT(const FProperty*, AssignableTo) = nullptr;` — Show only properties that are assignable to the given property. This means that they are either the exact same type, or that they are trivially convertible to the target type. Eg. bool -> bool, int32 -> int64, float -> double
- L118 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bEnableConversion) = false;` — If enabled, will show properties that can be converted to AssignableTo. The compatible conversion functions will be accessible via GetSelectedConversions
- L120 _public prototype_ `SLATE_EVENT(FOnDoubleClicked, OnDoubleClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UWidgetBlueprint* WidgetBlueprint);`
- L125 _public prototype_ `void ClearSources();`
- L127 _public prototype_ `void AddSource(const FBindingSource& InSource);`
- L128 _public prototype_ `void AddSources(TArrayView<const FBindingSource> InSources);`
- L130 _public prototype_ `void AddWidgetBlueprint();`
- L131 _public prototype_ `void AddWidgets(TArrayView<const UWidget*> Widgets);`
- L132 _public prototype_ `void AddViewModels(TArrayView<const FMVVMBlueprintViewModelContext> ViewModels);`
- L134 _public prototype_ `FMVVMBlueprintPropertyPath GetSelectedProperty() const;`
- L135 _public prototype_ `void SetSelectedProperty(const FMVVMBlueprintPropertyPath& Property);`
- L137 _public prototype_ `TArray<FMVVMFieldConversion> GetSelectedConversions() const;`
- L139 _public prototype_ `void SetRawFilterText(const FText& InFilterText);`
- L141 _public prototype_ `void EnableConversion(bool InEnabled);`
- L142 _public prototype_ `bool IsConversionEnabled() const;`
- L145 _private typedef_ `using SPropertyViewer = UE::PropertyViewer::SPropertyViewer;`
- L147 _private prototype_ `TSharedPtr<SWidget> HandleGetPreSlot(SPropertyViewer::FHandle Handle, TArrayView<const FFieldVariant> Path);`
- L148 _private prototype_ `void HandleSelectionChanged(SPropertyViewer::FHandle Handle, TArrayView<const FFieldVariant> Path, ESelectInfo::Type SelectionType);`
- L149 _private prototype_ `void HandleDoubleClicked(SPropertyViewer::FHandle Handle, TArrayView<const FFieldVariant> Path);`
- L151 _private prototype_ `FMVVMBlueprintPropertyPath CreateBlueprintPropertyPath(SPropertyViewer::FHandle Handle, TArrayView<const FFieldVariant> Path) const;`
- L154 _private member_ `FOnDoubleClicked OnDoubleClicked;`
- L155 _private member_ `TUniquePtr<FFieldIterator_Bindable> FieldIterator;`
- L156 _private member_ `TUniquePtr<UE::PropertyViewer::FFieldExpander_Default> FieldExpander;`
- L157 _private typedef_ `using FSourceType = TTuple<FBindingSource, SPropertyViewer::FHandle>;`
- L158 _private member_ `TArray<TPair<FBindingSource, SPropertyViewer::FHandle>> Sources;`
- L159 _private member_ `FMVVMBlueprintPropertyPath SelectedPath;`
- L160 _private member_ `TSharedPtr<SPropertyViewer> PropertyViewer;`
- L161 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L162 _private member_ `bool bIsBindingToEvent = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MVVM` (scope `UE`)
- L78 _prototype_ `TSharedRef<SWidget> ConstructFieldPreSlot(const UWidgetBlueprint* WidgetBlueprint, UE::PropertyViewer::SPropertyViewer::FHandle Handle, const FFieldVariant FieldPath, const bool bIsForEvent = false);` (scope `UE::MVVM`) — Genereate the icon for the binding type.
- L99 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDoubleClicked, const FMVVMBlueprintPropertyPath&);`

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/SMVVMViewModelPanel.h` (Private)


#### class `UMVVMBlueprintViewModelContextWrapper`  
`class UMVVMBlueprintViewModelContextWrapper : public UObject`  
_L32-44_
- reflection: `UCLASS()`
- inherits: `UObject`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public member_ `FMVVMBlueprintViewModelContext Wrapper;` — `UPROPERTY(EditAnywhere, Category="Viewmodel", meta = (ShowOnlyInnerProperties))`
- L42 _public member_ `TWeakObjectPtr<UMVVMBlueprintView> BlueprintView;`
- L43 _public member_ `FGuid ViewModelId;`

#### class `UMVVMViewModelPanelToolMenuContext`  
`class UMVVMViewModelPanelToolMenuContext : public UObject`  
_L47-53_
- reflection: `UCLASS()`
- inherits: `UObject`
- L52 _public member_ `TWeakPtr<UE::MVVM::SMVVMViewModelPanel> ViewModelPanel;`

#### class `UE::MVVM::SMVVMViewModelPanel`  
`class SMVVMViewModelPanel : public SCompoundWidget, public FNotifyHook`  
_L62-149_
- inherits: `SCompoundWidget,FNotifyHook`
- L65 _public function_ `SLATE_BEGIN_ARGS(SMVVMViewModelPanel)`
- L66 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> Editor);`
- L69 _public prototype_ `SMVVMViewModelPanel();`
- L70 _public prototype_ `virtual ~SMVVMViewModelPanel();`
- L72 _public prototype_ `void OpenAddViewModelMenu();`
- L74 _public prototype_ `static void RegisterMenu();`
- L77 _private prototype_ `void BuildContextMenu(FToolMenuSection& InSection);`
- L79 _private prototype_ `void HandleViewUpdated(UBlueprintExtension* Extension);`
- L80 _private prototype_ `void HandleViewModelsUpdated();`
- L81 _private prototype_ `TSet<UObject*> GetSelectedEditableObjects() const;`
- L82 _private prototype_ `bool HandleCanPopoutEditor() const;`
- L83 _private prototype_ `void HandlePopoutEditor();`
- L85 _private prototype_ `TSharedRef<SWidget> MakeAddMenu();`
- L86 _private prototype_ `void HandleCancelAddMenu();`
- L87 _private prototype_ `void HandleAddMenuViewModel(const UClass* SelectedClass);`
- L88 _private prototype_ `TSharedPtr<SWidget> HandleGetPreSlot(UE::PropertyViewer::SPropertyViewer::FHandle Handle, TArrayView<const FFieldVariant> FieldPath);`
- L89 _private prototype_ `bool HandleCanEditViewmodelList() const;`
- L90 _private prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L91 _private prototype_ `TSharedRef<SWidget> HandleGenerateContainer(UE::PropertyViewer::SPropertyViewer::FHandle ContainerHandle, TOptional<FText> DisplayName);`
- L92 _private prototype_ `TSharedPtr<SWidget> HandleContextMenuOpening(UE::PropertyViewer::SPropertyViewer::FHandle ContainerHandle, TArrayView<const FFieldVariant> Field) const;`
- L93 _private prototype_ `void HandleSelectionChanged(UE::PropertyViewer::SPropertyViewer::FHandle, TArrayView<const FFieldVariant>, ESelectInfo::Type);`
- L94 _private prototype_ `void HandleEditorSelectionChanged();`
- L95 _private prototype_ `void HandleSetObjectBeingDebugged(UObject* DebugObject);`
- L96 _private prototype_ `bool HandleCanRename(FGuid ViewModelGuid) const;`
- L97 _private prototype_ `bool HandleVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage, FGuid ViewModelGuid);`
- L98 _private prototype_ `void HandleNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo, FGuid ViewModelGuid);`
- L99 _private prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, UE::PropertyViewer::SPropertyViewer::FHandle ContainerHandle, TArrayView<const FFieldVariant> Fields) const;`
- L101 _private prototype_ `void HandleDeleteViewModel();`
- L102 _private prototype_ `bool HandleCanDeleteViewModel() const;`
- L103 _private prototype_ `void HandleRenameViewModel();`
- L104 _private prototype_ `bool HandleCanRenameViewModel() const;`
- L105 _private prototype_ `TSharedRef<SWidget> HandleAddViewModelContextMenu();`
- L107 _private prototype_ `EVisibility GetWarningPanelVisibility() const;`
- L108 _private prototype_ `FText GetWarningMessage() const;`
- L109 _private prototype_ `FReply HandleDisableWarningPanel();`
- L111 _private prototype_ `void CreateCommandList();`
- L112 _private prototype_ `void FillViewModel();`
- L113 _private prototype_ `bool RenameViewModelProperty(FGuid ViewModelGuid, const FText& RenameTo, bool bCommit, FText& OutErrorMessage) const;`
- L115 _private prototype_ `void CreateViewModelTreeView(UE::PropertyViewer::SPropertyViewer::EPropertyVisibility InPropertyVisibility);`
- L118 _private prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L119 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L123 _private member_ `TSharedPtr<SPositiveActionButton> AddMenuButton;`
- L124 _private member_ `TSharedPtr<SBox> ViewModelTreeViewContainer;`
- L125 _private member_ `TSharedPtr<UE::PropertyViewer::SPropertyViewer> ViewModelTreeView;`
- L126 _private member_ `TUniquePtr<FFieldIterator_Bindable> FieldIterator;`
- L127 _private member_ `TUniquePtr<UE::PropertyViewer::FFieldExpander_Default> FieldExpander;`
- L128 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L130 _private member_ `TMap<UE::PropertyViewer::SPropertyViewer::FHandle, FGuid> PropertyViewerHandles;`
- L131 _private member_ `TMap<FGuid, TSharedPtr<SInlineEditableTextBlock>> EditableTextBlocks;`
- L133 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakBlueprintEditor;`
- L134 _private member_ `TWeakObjectPtr<UMVVMBlueprintView> WeakBlueprintView;`
- L135 _private member_ `FDelegateHandle ViewModelsUpdatedHandle;`
- L136 _private member_ `FDelegateHandle ExtensionAddeddHandle;`
- L137 _private member_ `FDelegateHandle WidgetBlueprintTransactionHandle;`
- L139 _private member_ `TStrongObjectPtr<UMVVMBlueprintViewModelContextWrapper> ModelContextWrapper;`
- L141 _private member_ `FGuid SelectedViewModelGuid;`
- L142 _private member_ `FName PreviousViewModelPropertyName;`
- L143 _private member_ `bool bIsViewModelSelecting = false;`
- L144 _private member_ `bool bDisableWarningPanel = false;`
- L146 _private member_ `UE::PropertyViewer::SPropertyViewer::EPropertyVisibility PropertyVisibility;`
- L147 _private member_ `TSharedPtr<SWidget> ToolbarWidget;`
- L148 _private member_ `TSharedPtr<SWidget> SettingsWidget;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ETextCommit`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Private/Widgets/ViewModelFieldDragDropOp.h` (Private)


#### class `UE::MVVM::FViewModelFieldDragDropOp`  
`class FViewModelFieldDragDropOp : public FDecoratedDragDropOp`  
_L16-29_
- inherits: `FDecoratedDragDropOp`
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FViewModelFieldDragDropOp, FDecoratedDragDropOp) FViewModelFieldDragDropOp();`
- L22 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L23 _public prototype_ `static TSharedRef<FViewModelFieldDragDropOp> New(TArray<FFieldVariant> InField, const FGuid& ViewModelId, UWidgetBlueprint* InWidgetBP);`
- L25 _public member_ `TArray<FFieldVariant> DraggedField;`
- L26 _public member_ `FGuid ViewModelId;`
- L27 _public member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBP;`
- L28 _public member_ `TUniquePtr<FScopedTransaction> Transaction;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Public/Customizations/MVVMBlueprintViewDesignerExtension.h` (Public)


#### class `UE::MVVM::FBlueprintViewDesignerExtensionFactory`  
`class FBlueprintViewDesignerExtensionFactory : public IDesignerExtensionFactory, public TSharedFromThis<FBlueprintViewDesignerExtensionFactory>`  
_L10-17_
- inherits: `IDesignerExtensionFactory,TSharedFromThis<FBlueprintViewDesignerExtensionFactory>`
- L13 _public prototype_ `FBlueprintViewDesignerExtensionFactory() = default;`
- L14 _public prototype_ `virtual ~FBlueprintViewDesignerExtensionFactory() = default;`
- L16 _public prototype_ `virtual TSharedRef<FDesignerExtension> CreateDesignerExtension() const override;`

#### class `UE::MVVM::FBlueprintViewDesignerExtension`  
`class FBlueprintViewDesignerExtension : public FDesignerExtension`  
_L19-23_
- inherits: `FDesignerExtension`
- L22 _public prototype_ `virtual void PreviewContentChanged(TSharedRef<SWidget> NewContent) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Public/IModelViewViewModelEditorModule.h` (Public)


#### class `IModelViewViewModelEditorModule`  
`class IModelViewViewModelEditorModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void OpenPopoutEditor(TNotNull<UObject*> InObject, bool bInReadyOnly = true) = 0;` — Pops open a new window with a standalone object editor in either read only or edit mode.

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Public/MVVMEditorCommands.h` (Public)


#### class `FMVVMEditorCommands`  
`class FMVVMEditorCommands : public TCommands<FMVVMEditorCommands>`  
_L7-19_
- inherits: `TCommands<FMVVMEditorCommands>`
- L10 _public prototype_ `FMVVMEditorCommands();`
- L11 _public prototype_ `void RegisterCommands() override;`
- L12 _public prototype_ `static const FMVVMEditorCommands& Get();`
- L15 _public member_ `TSharedPtr<FUICommandInfo> ToggleMVVMDrawer;` — Command to toggle MVVM drawer in widget editor
- L18 _public member_ `TSharedPtr<FUICommandInfo> PopoutEditor;` — Pops out a standalone property editor window.

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Public/MVVMEditorSubsystem.h` (Public)


#### class `UMVVMEditorSubsystem`  
`class UMVVMEditorSubsystem : public UEditorSubsystem`  
_L35-173_
- reflection: `UCLASS(MinimalAPI, DisplayName="Viewmodel Editor Subsystem")`
- inherits: `UEditorSubsystem`
- L41 _public prototype_ `UMVVMBlueprintView* RequestView(UWidgetBlueprint* WidgetBlueprint) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L44 _public prototype_ `UMVVMBlueprintView* GetView(const UWidgetBlueprint* WidgetBlueprint) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L47 _public prototype_ `FGuid AddViewModel(UWidgetBlueprint* WidgetBlueprint, const UClass* ViewModel);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L50 _public prototype_ `FGuid AddInstancedViewModel(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L53 _public prototype_ `void RemoveViewModel(UWidgetBlueprint* WidgetBlueprint, FName ViewModel);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L56 _public prototype_ `bool VerifyViewModelRename(UWidgetBlueprint* WidgetBlueprint, FName ViewModel, FName NewViewModel, FText& OutError);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L59 _public prototype_ `bool RenameViewModel(UWidgetBlueprint* WidgetBlueprint, FName ViewModel, FName NewViewModel, FText& OutError);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L62 _public prototype_ `bool ReparentViewModel(UWidgetBlueprint* WidgetBlueprint, FName ViewModel, const UClass* NewViewModel, FText& OutError);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L65 _public prototype_ `FMVVMBlueprintViewBinding& AddBinding(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L68 _public prototype_ `void RemoveBinding(UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L71 _public prototype_ `UMVVMBlueprintViewEvent* AddEvent(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L74 _public prototype_ `void RemoveEvent(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L77 _public prototype_ `UMVVMBlueprintViewCondition* AddCondition(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L80 _public prototype_ `void RemoveCondition(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewCondition* Condition);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L83 _public prototype_ `TArray<FMVVMAvailableBinding> GetChildViewModels(TSubclassOf<UObject> Class, TSubclassOf<UObject> Accessor);` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L86 _public prototype_ `void SetSourceToDestinationConversionFunction(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, const UFunction* ConversionFunction);` — `UE_DEPRECATED(5.4, "SetSourceToDestinationConversionFunction with a UFunction is deprecated.")`
- L87 _public prototype_ `void SetSourceToDestinationConversionFunction(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, FMVVMBlueprintFunctionReference ConversionFunction);`
- L89 _public prototype_ `void SetDestinationToSourceConversionFunction(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, const UFunction* ConversionFunction);` — `UE_DEPRECATED(5.4, "SetDestinationToSourceConversionFunction with a UFunction is deprecated.")`
- L90 _public prototype_ `void SetDestinationToSourceConversionFunction(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, FMVVMBlueprintFunctionReference ConversionFunction);`
- L91 _public prototype_ `void SetDestinationPathForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, FMVVMBlueprintPropertyPath Field, bool bAllowEventConversion);`
- L92 _public prototype_ `void SetSourcePathForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, FMVVMBlueprintPropertyPath Field);`
- L93 _public prototype_ `void OverrideExecutionModeForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, EMVVMExecutionMode Mode);`
- L94 _public prototype_ `void ResetExecutionModeForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding);`
- L95 _public prototype_ `void SetBindingTypeForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, EMVVMBindingMode Type);`
- L96 _public prototype_ `void SetEnabledForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, bool bEnabled);`
- L97 _public prototype_ `void SetCompileForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, bool bCompile);`
- L98 _public prototype_ `void GenerateBindToDestinationPathsForBinding(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding);`
- L100 _public prototype_ `void SetEventPath(UMVVMBlueprintViewEvent* Event, FMVVMBlueprintPropertyPath PropertyPath, bool bRequestBindingConversion);`
- L101 _public prototype_ `void SetEventDestinationPath(UMVVMBlueprintViewEvent* Event, FMVVMBlueprintPropertyPath PropertyPath);`
- L102 _public prototype_ `void SetEventArgumentPath(UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId, const FMVVMBlueprintPropertyPath& PropertyPath) const;`
- L103 _public prototype_ `void SetEnabledForEvent(UMVVMBlueprintViewEvent* Event, bool bEnabled);`
- L104 _public prototype_ `void SetCompileForEvent(UMVVMBlueprintViewEvent* Event, bool bCompile);`
- L106 _public prototype_ `void SetConditionPath(UMVVMBlueprintViewCondition* Condition, FMVVMBlueprintPropertyPath PropertyPath, bool bRequestBindingConversion);`
- L107 _public prototype_ `void SetConditionDestinationPath(UMVVMBlueprintViewCondition* Condition, FMVVMBlueprintPropertyPath PropertyPath);`
- L108 _public prototype_ `void SetConditionArgumentPath(UMVVMBlueprintViewCondition* Condition, const FMVVMBlueprintPinId& PinId, const FMVVMBlueprintPropertyPath& PropertyPath) const;`
- L109 _public prototype_ `void SetEnabledForCondition(UMVVMBlueprintViewCondition* Condition, bool bEnabled);`
- L110 _public prototype_ `void SetCompileForCondition(UMVVMBlueprintViewCondition* Condition, bool bCompile);`
- L111 _public prototype_ `void SetConditionOperation(UMVVMBlueprintViewCondition* Condition, EMVVMConditionOperation Operation);`
- L112 _public prototype_ `void SetConditionOperationValue(UMVVMBlueprintViewCondition* Condition, float Value);`
- L113 _public prototype_ `void SetConditionOperationMaxValue(UMVVMBlueprintViewCondition* Condition, float MaxValue);`
- L116 _public prototype_ `bool IsValidConversionFunction(const UWidgetBlueprint* WidgetBlueprint, const UFunction* Function, const FMVVMBlueprintPropertyPath& Source, const FMVVMBlueprintPropertyPath& Destination) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L117 _public prototype_ `bool IsValidConversionFunction(const UWidgetBlueprint* WidgetBlueprint, const UFunction* Function, const FProperty* ExpectedArgumentType, const FProperty* ExptectedReturnType) const;`
- L118 _public prototype_ `bool IsValidConversionFunction(const UWidgetBlueprint* WidgetBlueprint, UE::MVVM::FConversionFunctionValue Function, const FProperty* ExpectedArgumentType, const FProperty* ExptectedReturnType) const;`
- L120 _public prototype_ `bool IsValidConversionNode(const UWidgetBlueprint* WidgetBlueprint, const TSubclassOf<UK2Node> Function, const FMVVMBlueprintPropertyPath& Source, const FMVVMBlueprintPropertyPath& Destination) const;`
- L121 _public prototype_ `bool IsValidConversionNode(const UWidgetBlueprint* WidgetBlueprint, const TSubclassOf<UK2Node> Function, const FProperty* ExpectedArgumentType, const FProperty* ExptectedReturnType) const;`
- L124 _public prototype_ `bool IsSimpleConversionFunction(const UFunction* Function) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L127 _public prototype_ `UEdGraph* GetConversionFunctionGraph(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, bool bSourceToDestination) const;` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L131 _public prototype_ `UFunction* GetConversionFunction(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, bool bSourceToDestination) const;` — `UE_DEPRECATED(5.4, "GetConversionFunction was moved to MVVMBlueprintViewConversionFunction.")` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L135 _public prototype_ `UK2Node_CallFunction* GetConversionFunctionNode(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, bool bSourceToDestination) const;` — `UE_DEPRECATED(5.3, "GetConversionFunctionNode was moved to MVVMBlueprintViewConversionFunction.")` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L139 _public prototype_ `TArray<UFunction*> GetAvailableConversionFunctions(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintPropertyPath& Source, const FMVVMBlueprintPropertyPath& Destination) const;` — `UE_DEPRECATED(5.5, "GetAvailableConversionFunctions return value changes.")` — `UFUNCTION(BlueprintCallable, Category = "Viewmodel")`
- L141 _public prototype_ `TArray<UE::MVVM::FConversionFunctionValue> GetConversionFunctions(const UWidgetBlueprint* WidgetBlueprint, const FProperty* ExpectedArgumentType, const FProperty* ExptectedReturnType) const;`
- L142 _public prototype_ `TArray<FMVVMBlueprintPinId> GetConversionFunctionPins(const UWidgetBlueprint* WidgetBlueprint, const UE::MVVM::FConversionFunctionValue& Function, const FProperty* ExpectedArgumentType) const;`
- L144 _public prototype_ `FMVVMBlueprintPropertyPath GetPathForConversionFunctionArgument(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L145 _public prototype_ `void SetPathForConversionFunctionArgument(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, const FMVVMBlueprintPropertyPath& Path, bool bSourceToDestination) const;`
- L146 _public prototype_ `UEdGraphPin* GetConversionFunctionArgumentPin(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L148 _public prototype_ `void SplitPin(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L149 _public prototype_ `bool CanSplitPin(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L150 _public prototype_ `void SplitPin(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L151 _public prototype_ `bool CanSplitPin(const UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L152 _public prototype_ `void RecombinePin(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L153 _public prototype_ `bool CanRecombinePin(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L154 _public prototype_ `void RecombinePin(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L155 _public prototype_ `bool CanRecombinePin(const UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L156 _public prototype_ `void ResetPinToDefaultValue(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding,const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L157 _public prototype_ `bool CanResetPinToDefaultValue(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L158 _public prototype_ `void ResetPinToDefaultValue(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L159 _public prototype_ `bool CanResetPinToDefaultValue(const UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L160 _public prototype_ `void ResetOrphanedPin(UWidgetBlueprint* WidgetBlueprint, FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L161 _public prototype_ `bool CanResetOrphanedPin(const UWidgetBlueprint* WidgetBlueprint, const FMVVMBlueprintViewBinding& Binding, const FMVVMBlueprintPinId& PinId, bool bSourceToDestination) const;`
- L162 _public prototype_ `void ResetOrphanedPin(UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event,const FMVVMBlueprintPinId& PinId) const;`
- L163 _public prototype_ `bool CanResetOrphanedPin(const UWidgetBlueprint* WidgetBlueprint, UMVVMBlueprintViewEvent* Event, const FMVVMBlueprintPinId& PinId) const;`
- L165 _public prototype_ `TArray<UE::MVVM::FBindingSource> GetBindableWidgets(const UWidgetBlueprint* WidgetBlueprint) const;`
- L166 _public prototype_ `TArray<UE::MVVM::FBindingSource> GetAllViewModels(const UWidgetBlueprint* WidgetBlueprint) const;`
- L168 _public prototype_ `FGuid GetFirstBindingThatUsesViewModel(const UWidgetBlueprint* WidgetBlueprint, FGuid ViewModelId) const;`
- L169 _public prototype_ `static FString GetDefaultViewModelName(const UClass* ViewModelClass);`
- L172 _private member_ `mutable TUniquePtr<UE::MVVM::ConversionFunctionLibrary::FCollection> ConversionFunctionCollection;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELVIEWVIEWMODELEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MVVM` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MVVM` (scope `UE`)
- L20 _namespace_ `namespace ConversionFunctionLibrary` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Public/Types/MVVMConversionFunctionValue.h` (Public)


#### struct `UE::MVVM::FConversionFunctionValue`  
`struct FConversionFunctionValue`  
_L16-87_
- L20 _public prototype_ `FConversionFunctionValue() = default;`
- L21 _public function_ `explicit FConversionFunctionValue(const UFunction* Function) : ConversionFunction(Function)`
- L24 _public function_ `explicit FConversionFunctionValue(TSubclassOf<UK2Node> Node) : ConversionNode(Node)`
- L29 _public function_ `bool IsFunction() const`
- L34 _public function_ `const UFunction* GetFunction() const`
- L39 _public function_ `bool IsNode() const`
- L44 _public function_ `TSubclassOf<UK2Node> GetNode() const`
- L49 _public prototype_ `FString GetName() const;`
- L50 _public prototype_ `FName GetFName() const;`
- L51 _public prototype_ `FString GetFullGroupName(bool bStartWithOuter) const;`
- L52 _public prototype_ `FText GetDisplayName() const;`
- L53 _public prototype_ `FText GetTooltip() const;`
- L54 _public prototype_ `FText GetCategory() const;`
- L55 _public prototype_ `TArray<FString> GetSearchKeywords() const;`
- L58 _public function_ `bool IsValid() const`
- L63 _public function_ `bool operator== (const FConversionFunctionValue& Other) const`
- L68 _public function_ `bool operator== (const UFunction* Other) const`
- L73 _public function_ `bool operator== (const TSubclassOf<UK2Node> Other) const`
- L85 _private member_ `const UFunction* ConversionFunction = nullptr;`
- L86 _private member_ `TSubclassOf<UK2Node> ConversionNode;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELVIEWVIEWMODELEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MVVM` (scope `UE`)
- L79 _function_ `friend int32 GetTypeHash(const FConversionFunctionValue& Value)` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelEditor/Public/Types/MVVMLinkedPinValue.h` (Public)


#### struct `FMVVMLinkedPinValue`  
`struct FMVVMLinkedPinValue`  
_L19-57_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public prototype_ `FMVVMLinkedPinValue() = default;`
- L25 _public prototype_ `explicit FMVVMLinkedPinValue(FMVVMBlueprintPropertyPath InPath);`
- L26 _public prototype_ `explicit FMVVMLinkedPinValue(const UBlueprint* InBlueprint, FMVVMBlueprintFunctionReference InConversion);`
- L27 _public prototype_ `explicit FMVVMLinkedPinValue(UE::MVVM::FConversionFunctionValue Function);`
- L28 _public prototype_ `explicit FMVVMLinkedPinValue(const UFunction* Function);`
- L29 _public prototype_ `explicit FMVVMLinkedPinValue(TSubclassOf<UK2Node> Node);`
- L32 _public prototype_ `bool IsPropertyPath() const;`
- L33 _public prototype_ `const FMVVMBlueprintPropertyPath& GetPropertyPath() const;`
- L35 _public prototype_ `bool IsConversionFunction() const;`
- L36 _public prototype_ `const UFunction* GetConversionFunction() const;`
- L38 _public prototype_ `bool IsConversionNode() const;`
- L39 _public prototype_ `TSubclassOf<UK2Node> GetConversionNode() const;`
- L42 _public prototype_ `bool IsValid() const;`
- L43 _public function_ `bool operator== (const FMVVMLinkedPinValue& Other) const`
- L50 _protected member_ `FMVVMBlueprintPropertyPath PropertyPath;` — `UPROPERTY(BlueprintReadWrite, Category = "MVVM")`
- L53 _protected member_ `TObjectPtr<const UFunction> ConversionFunction = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "MVVM")`
- L56 _protected member_ `TSubclassOf<UK2Node> ConversionNode;` — `UPROPERTY(BlueprintReadWrite, Category = "MVVM")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELVIEWVIEWMODELEDITOR_API`
