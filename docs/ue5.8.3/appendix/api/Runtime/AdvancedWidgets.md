# Runtime / AdvancedWidgets

- module root: `Source/Runtime/AdvancedWidgets`
- headers: 30; symbols: 857
- symbol kinds: class=27, delegate=16, enum=8, enumerator=29, function=97, macro=1, member=256, namespace=53, prototype=353, struct=11, typedef=5, union=1
- PrivateDependencyModuleNames: Engine, InputCore, PropertyEditor, Slate, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, SlateCore, UMG

### `Source/Runtime/AdvancedWidgets/Private/Widgets/ColorGrading/SColorGradingComponentSpinBox.h` (Private)


#### class `UE::ColorGrading::SColorGradingComponentSpinBox`  
`class SColorGradingComponentSpinBox : public SCompoundWidget`  
_L26-357_
- inherits: `SCompoundWidget`
- desc: A modified SpinBox that shows a selector along a gradient to indicate a color component for color grading. Allows spinning via mouse drag if enabled, but does not allow text entry like a standard SpinBox.
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, float);` — Notification for numeric value change
- L35 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L37 _public function_ `SLATE_BEGIN_ARGS(SColorGradingComponentSpinBox) : _Style(&UE::AdvancedWidgets::FAdvancedWidgetsStyle::Get().GetWidgetStyle<FColorGradingSpinBoxStyle>("ColorGradingSpinBox")) , _Value(0) , _Component(EColorGradingComponent::Red) , _ColorGradingMode(EColorGradingModes::Invalid) , _MinValue(0) , _MaxValue(2) , _Delta(0) , _ShiftMultiplier(10.f) , _CtrlMultiplier(0.1f) , _Sensitivity(1.0f) , _SupportDynamicSliderMaxValue(false) , _SupportDynamicSliderMinValue(false) , _SliderExponent(1.f) , _OnValueChanged() , _OnQueryCurrentColor() , _AllowSpin(true)`
- L57 _public prototype_ `SLATE_STYLE_ARGUMENT(FColorGradingSpinBoxStyle, Style) SLATE_ATTRIBUTE(float, Value) SLATE_ATTRIBUTE(EColorGradingComponent, Component) SLATE_ATTRIBUTE(EColorGradingModes, ColorGradingMode) SLATE_ATTRIBUTE(TOptional<float>, MinValue) SLATE_ATTRIBUTE(TOptional<float>, MaxValue) SLATE_ATTRIBUTE(TOptional<float>, MinSliderValue) SLATE_ATTRIBUTE(TOptional<float>, MaxSliderValue) SLATE_ATTRIBUTE(bool, AlwaysUsesDeltaSnap) SLATE_ATTRIBUTE(float, Delta) SLATE_ATTRIBUTE(float, ShiftMultiplier) SLATE_ATTRIBUTE(float, CtrlMultiplier) SLATE_ATTRIBUTE(float, Sensitivity) SLATE_ATTRIBUTE(int32, LinearDeltaSensitivity) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMaxValue) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMinValue) SLATE_EVENT(FOnDynamicSliderMinMaxValueChanged, OnDynamicSliderMaxValueChanged) SLATE_EVENT(FOnDynamicSliderMinMaxValueChanged, OnDynamicSliderMinValueChanged) SLATE_ATTRIBUTE(float, SliderExponent) SLATE_ATTRIBUTE(float, SliderExponentNeutralValue)` — The style used to draw this spinbox
- L116 _public prototype_ `virtual ~SColorGradingComponentSpinBox();`
- L123 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L125 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L127 _public prototype_ `const bool CommitWithMultiplier(const FPointerEvent& MouseEvent);`
- L136 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — The system calls this method to notify the widget that a mouse button was pressed within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L145 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — The system calls this method to notify the widget that a mouse button was release within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L147 _public prototype_ `void ApplySliderMaxValueChanged(float SliderDeltaToAdd, bool UpdateOnlyIfHigher);`
- L149 _public prototype_ `void ApplySliderMinValueChanged(float SliderDeltaToAdd, bool UpdateOnlyIfLower);`
- L158 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — The system calls this method to notify the widget that a mouse moved within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L160 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L163 _public function_ `TAttribute<float> GetValueAttribute() const` — Return the Value attribute
- L166 _public function_ `float GetValue() const` — See the Value attribute
- L167 _public function_ `void SetValue(const TAttribute<float>& InValueAttribute)`
- L175 _public function_ `float GetMinValue() const` — See the MinValue attribute
- L176 _public function_ `void SetMinValue(const TAttribute<TOptional<float>>& InMinValue)`
- L183 _public function_ `float GetMaxValue() const` — See the MaxValue attribute
- L184 _public function_ `void SetMaxValue(const TAttribute<TOptional<float>>& InMaxValue)`
- L191 _public function_ `bool IsMinSliderValueBound() const` — See the MinSliderValue attribute
- L193 _public function_ `float GetMinSliderValue() const`
- L194 _public function_ `void SetMinSliderValue(const TAttribute<TOptional<float>>& InMinSliderValue)`
- L201 _public function_ `bool IsMaxSliderValueBound() const` — See the MaxSliderValue attribute
- L203 _public function_ `float GetMaxSliderValue() const`
- L204 _public function_ `void SetMaxSliderValue(const TAttribute<TOptional<float>>& InMaxSliderValue)`
- L211 _public function_ `bool GetAlwaysUsesDeltaSnap() const` — See the AlwaysUsesDeltaSnap attribute
- L212 _public function_ `void SetAlwaysUsesDeltaSnap(bool bNewValue)`
- L215 _public function_ `float GetDelta() const` — See the Delta attribute
- L216 _public function_ `void SetDelta(float InDelta)`
- L219 _public function_ `float GetSliderExponent() const` — See the SliderExponent attribute
- L220 _public function_ `void SetSliderExponent(const TAttribute<float>& InSliderExponent)`
- L222 _public function_ `const FColorGradingSpinBoxStyle* GetWidgetStyle() const`
- L223 _public function_ `void SetWidgetStyle(const FColorGradingSpinBoxStyle* InStyle)`
- L224 _public function_ `void InvalidateStyle()`
- L242 _protected prototype_ `void CommitValue(float NewValue, double NewSpinValue, ECommitMethod CommitMethod, ETextCommit::Type OriginalCommitInfo);` — Call this method when the user's interaction has changed the value @param NewValue               Value resulting from the user's interaction @param CommitMethod           Did the user type in the value or spin to it. @param OriginalCommitInfo	 If the user typed in the value, information about the source of the commit
- L244 _protected prototype_ `void NotifyValueCommitted(float CurrentValue) const;`
- L247 _protected prototype_ `static float Fraction(double InValue, double InMinValue, double InMaxValue);` — Calculates range fraction. Possible to use on full numeric range
- L252 _private prototype_ `static const TArray<FLinearColor>& GetHueGradientColors();` — Get the gradient stops for a hue slider. These are lazily generated and cached for future calls.
- L253 _private member_ `static TArray<FLinearColor> HueGradientColors;`
- L255 _private member_ `TAttribute<float> ValueAttribute;`
- L256 _private member_ `FOnValueChanged OnValueChanged;`
- L257 _private member_ `FSimpleDelegate OnBeginSliderMovement;`
- L258 _private member_ `FOnValueChanged OnEndSliderMovement;`
- L259 _private member_ `FOnGetCurrentVector4Value OnQueryCurrentColor;`
- L262 _private member_ `TSharedPtr<INumericTypeInterface<float>> Interface;` — Interface that defines conversion functionality for the templated type
- L265 _private member_ `bool bUnlimitedSpinRange;` — True when no range is specified, spinner can be spun indefinitely
- L266 _private function_ `void UpdateIsSpinRangeUnlimited()`
- L271 _private member_ `const FColorGradingSpinBoxStyle* Style;`
- L273 _private member_ `const FSlateBrush* BorderHoveredBrush;`
- L274 _private member_ `const FSlateBrush* BorderActiveBrush;`
- L275 _private member_ `const FSlateBrush* BorderBrush;`
- L276 _private member_ `const FSlateBrush* SelectorBrush;`
- L277 _private member_ `const float* SelectorWidth;`
- L279 _private member_ `bool bAllowSpin;`
- L280 _private member_ `float DistanceDragged;`
- L281 _private member_ `TAttribute<float> Delta;`
- L282 _private member_ `TAttribute<float> ShiftMultiplier;`
- L283 _private member_ `TAttribute<float> CtrlMultiplier;`
- L284 _private member_ `TAttribute<float> Sensitivity;`
- L285 _private member_ `TAttribute<int32> LinearDeltaSensitivity;`
- L286 _private member_ `TAttribute<float> SliderExponent;`
- L287 _private member_ `TAttribute<float> SliderExponentNeutralValue;`
- L288 _private member_ `TAttribute<TOptional<float>> MinValue;`
- L289 _private member_ `TAttribute<TOptional<float>> MaxValue;`
- L290 _private member_ `TAttribute<TOptional<float>> MinSliderValue;`
- L291 _private member_ `TAttribute<TOptional<float>> MaxSliderValue;`
- L292 _private member_ `TAttribute<bool> AlwaysUsesDeltaSnap;`
- L293 _private member_ `TAttribute<bool> SupportDynamicSliderMaxValue;`
- L294 _private member_ `TAttribute<bool> SupportDynamicSliderMinValue;`
- L295 _private member_ `FOnDynamicSliderMinMaxValueChanged OnDynamicSliderMaxValueChanged;`
- L296 _private member_ `FOnDynamicSliderMinMaxValueChanged OnDynamicSliderMinValueChanged;`
- L297 _private member_ `TAttribute<EColorGradingComponent> Component;`
- L298 _private member_ `TAttribute<EColorGradingModes> ColorGradingMode;`
- L305 _private prototype_ `float RoundIfIntegerValue(double ValueToRound) const;` — Rounds the submitted value to the correct value if it's an integer. For int64, not all values can be represented by a double. We can only round until we reach that limit. This function should only be used when we drag the value. We accept that we can't drag huge numbers.
- L307 _private prototype_ `void CancelMouseCapture();`
- L310 _private prototype_ `TArray<FLinearColor> GetGradientColors() const;` — Generate the gradient stops to display in the background based on the current color and viewed component.
- L313 _private prototype_ `FLinearColor GetCurrentRGBColor() const;` — Get the currently selected color in linear RGB space.
- L316 _private prototype_ `FLinearColor GetCurrentHSVColor() const;` — Get the currently selected color in HSV space.
- L319 _private member_ `int32 PointerDraggingSliderIndex;` — Tracks which cursor is currently dragging the slider (e.g., the mouse cursor or a specific finger)
- L322 _private member_ `FIntPoint CachedMousePosition;` — Cached mouse position to restore after scrolling.
- L329 _private member_ `double InternalValue;` — This value represents what the spinbox believes the value to be, regardless of delta and the user binding to an int. The spinbox will always count using floats between values, this is important to keep it flowing smoothly and feeling right, and most importantly not conflicting with the user truncating the value to an int.
- L332 _private member_ `float PreDragValue;` — The state of InternalValue before a drag operation was started
- L338 _private member_ `float CachedExternalValue;` — This is the cached value the user believes it to be (usually different due to truncation to an int). Used for identifying external forces on the spinbox and syncing the internal value to them. Synced when a value is committed to the spinbox.
- L341 _private member_ `bool bDragging;` — Whether the user is dragging the slider
- L344 _private member_ `bool bIsTextChanging;` — Re-entrant guard for the text changed handler
- L350 _private member_ `bool bPreventThrottling;` — Holds whether or not to prevent throttling during mouse capture When true, the viewport will be updated with every single change to the value during dragging
- L353 _private member_ `bool bEnableWheel = true;` — Does this spin box have the mouse wheel feature enabled?
- L356 _private member_ `bool bBroadcastValueChangesPerKey = false;` — True to broadcast every time we type.

#### enum `UE::ColorGrading::SColorGradingComponentSpinBox::ECommitMethod`  
`enum ECommitMethod`  
_L228-233_
- desc: How user changed the value in the spinbox
- L230 _public enumerator_ `CommittedViaSpin`
- L231 _public enumerator_ `CommittedViaCode`
- L232 _public enumerator_ `CommittedViaSpinMultiplier`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ColorGrading` (scope `UE`)
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, float);` — Notification for numeric value change
- L35 _delegate_ `DECLARE_DELEGATE_FourParams(FOnDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)

### `Source/Runtime/AdvancedWidgets/Private/Widgets/PropertyViewer/SPropertyViewerImpl.h` (Private)


#### struct `UE::PropertyViewer::Private::FContainer`  
`struct FContainer`  
_L36-103_
- desc: FContainer
- L38 _public prototype_ `FContainer(SPropertyViewer::FHandle InIdentifier, TOptional<FText> DisplayName, const UStruct* ClassToDisplay);`
- L39 _public prototype_ `FContainer(SPropertyViewer::FHandle InIdentifier, TOptional<FText> DisplayName, UObject* InstanceToDisplay);`
- L40 _public prototype_ `FContainer(SPropertyViewer::FHandle InIdentifier, TOptional<FText> DisplayName, const UScriptStruct* Struct, void* Data);`
- L43 _public function_ `SPropertyViewer::FHandle GetIdentifier() const`
- L48 _public function_ `void* GetBuffer() const`
- L54 _public function_ `const UStruct* GetStruct()`
- L59 _public function_ `bool CanEdit() const`
- L64 _public function_ `bool IsInstance() const`
- L69 _public function_ `bool IsObjectInstance() const`
- L74 _public function_ `UObject* GetObjectInstance() const`
- L79 _public function_ `bool IsScriptStructInstance() const`
- L84 _public function_ `void* GetScriptStructInstance() const`
- L89 _public function_ `TOptional<FText> GetDisplayName() const`
- L94 _public prototype_ `bool IsValid() const;`
- L97 _private member_ `SPropertyViewer::FHandle Identifier;`
- L98 _private member_ `TWeakObjectPtr<const UStruct> Container;`
- L99 _private member_ `TWeakObjectPtr<UObject> ObjectInstance;`
- L100 _private member_ `void* StructInstance = nullptr;`
- L101 _private member_ `TOptional<FText> DisplayName;`
- L102 _private member_ `bool bIsObject = false;`

#### struct `UE::PropertyViewer::Private::FTreeNode`  
`struct FTreeNode : public TSharedFromThis<FTreeNode>`  
_L109-192_
- inherits: `TSharedFromThis<FTreeNode>`
- desc: FTreeNode
- L112 _public prototype_ `static TSharedRef<FTreeNode> MakeContainer(const TSharedPtr<FContainer>& InContainer, TOptional<FText> InDisplayName);`
- L113 _public prototype_ `static TSharedRef<FTreeNode> MakeField(TSharedPtr<FTreeNode> InParent, const FProperty* Property, TOptional<FText> InDisplayName);`
- L114 _public prototype_ `static TSharedRef<FTreeNode> MakeField(TSharedPtr<FTreeNode> InParent, const UFunction* Function, TOptional<FText> InDisplayName);`
- L117 _private member_ `TWeakPtr<FTreeNode> ParentNode;`
- L120 _private member_ `TWeakPtr<FContainer> Container;` — Either a container, property or function
- L121 _private member_ `TWeakObjectPtr<const UStruct> FieldOwner;`
- L122 _private member_ `FName PropertyName;`
- L123 _private member_ `FName FunctionName;`
- L124 _private member_ `bool bIsStructProperty = false;`
- L125 _private member_ `bool bIsObjectProperty = false;`
- L127 _private member_ `TOptional<FText> OverrideDisplayName;`
- L130 _public member_ `TWeakPtr<SFieldName> PropertyWidget;`
- L131 _public member_ `TArray<TSharedPtr<FTreeNode>, TInlineAllocator<1>> ChildNodes;`
- L132 _public member_ `bool bChildGenerated = false;`
- L135 _public function_ `bool IsContainer() const`
- L140 _public function_ `TSharedPtr<FContainer> GetContainer() const`
- L145 _public function_ `bool IsField() const`
- L150 _public prototype_ `FFieldVariant GetField() const;`
- L152 _public function_ `TSharedPtr<FTreeNode> GetParentNode() const`
- L157 _public prototype_ `FPropertyPath GetPropertyPath() const;`
- L158 _public prototype_ `TArray<FFieldVariant> GetFieldPath() const;`
- L160 _public prototype_ `TSharedPtr<FContainer> GetOwnerContainer() const;`
- L162 _public function_ `TOptional<FText> GetOverrideDisplayName() const`
- L167 _public prototype_ `void GetFilterStrings(TArray<FString>& OutStrings) const;`
- L181 _public prototype_ `TArray<FNodeReference> BuildChildNodes(IFieldIterator& FieldIterator, IFieldExpander& FieldExpander, bool bSortChildNode);` — Returns the object node that was build
- L182 _public function_ `void RemoveChild()`
- L189 _private prototype_ `void BuildChildNodesRecursive(IFieldIterator& FieldIterator, IFieldExpander& FieldExpander, bool bSortChildNode, int32 RecursiveCount, TArray<FNodeReference>& OutTickReference);`
- L191 _private prototype_ `static bool Sort(const TSharedPtr<FTreeNode>& NodeA, const TSharedPtr<FTreeNode>& NodeB);`

#### struct `UE::PropertyViewer::Private::FTreeNode::FNodeReference`  
`struct FNodeReference`  
_L169-178_
- L171 _public member_ `TWeakObjectPtr<UObject> Previous;`
- L172 _public member_ `TWeakPtr<FTreeNode> Node;`
- L174 _public function_ `FNodeReference(UObject* InPrevious, const TWeakPtr<FTreeNode>& InNode) : Previous(InPrevious) , Node(InNode)`

#### class `UE::PropertyViewer::Private::FPropertyViewerImpl`  
`class FPropertyViewerImpl : public TSharedFromThis<FPropertyViewerImpl>`  
_L198-278_
- inherits: `TSharedFromThis<FPropertyViewerImpl>`
- desc: FPropertyViewerImpl
- L201 _public prototype_ `FPropertyViewerImpl(const SPropertyViewer::FArguments& InArgs);`
- L202 _public prototype_ `FPropertyViewerImpl(const FPropertyViewerImpl&) = delete;`
- L203 _public prototype_ `FPropertyViewerImpl& operator=(const FPropertyViewerImpl&) = delete;`
- L204 _public prototype_ `~FPropertyViewerImpl();`
- L207 _private member_ `TArray<TSharedPtr<FContainer>> Containers;`
- L208 _private member_ `TArray<FTreeNode::FNodeReference> NodeReferences;`
- L210 _private member_ `TSharedPtr<SSearchBox> SearchBoxWidget;`
- L211 _private member_ `TSharedPtr<STreeView<TSharedPtr<FTreeNode>>> TreeWidget;`
- L212 _private member_ `TArray<TSharedPtr<FTreeNode>> TreeSource;`
- L213 _private member_ `TArray<TSharedPtr<FTreeNode>> FilteredTreeSource;`
- L215 _private typedef_ `using FTextFilter = TTextFilter<TSharedPtr<FTreeNode>>;`
- L216 _private member_ `TSharedPtr<FTextFilter> SearchFilter;`
- L217 _private typedef_ `using FTreeFilter = TreeFilterHandler<TSharedPtr<FTreeNode>>;`
- L218 _private member_ `TSharedPtr<FTreeFilter> FilterHandler;`
- L220 _private member_ `SPropertyViewer::FGetFieldWidget OnGetPreSlot;`
- L221 _private member_ `SPropertyViewer::FGetFieldWidget OnGetPostSlot;`
- L222 _private member_ `SPropertyViewer::FOnContextMenuOpening OnContextMenuOpening;`
- L223 _private member_ `SPropertyViewer::FOnSelectionChanged OnSelectionChanged;`
- L224 _private member_ `SPropertyViewer::FOnDoubleClicked OnDoubleClicked;`
- L225 _private member_ `SPropertyViewer::FOnDragDetected OnDragDetected;`
- L226 _private member_ `SPropertyViewer::FOnGenerateContainer OnGenerateContainer;`
- L227 _private member_ `SPropertyViewer::EPropertyVisibility PropertyVisibility;`
- L228 _private member_ `TOptional<const FFieldColorSettings> OverrideIconColorSettings;`
- L229 _private member_ `bool bSanitizeName = false;`
- L230 _private member_ `bool bShowFieldIcon = false;`
- L231 _private member_ `bool bUseRows = false;`
- L232 _private member_ `bool bSortChildNode = false;`
- L234 _private member_ `IFieldIterator* FieldIterator = nullptr;`
- L235 _private member_ `IFieldExpander* FieldExpander = nullptr;`
- L236 _private member_ `INotifyHook* NotifyHook = nullptr;`
- L237 _private member_ `bool bOwnFieldIterator = false;`
- L238 _private member_ `bool bOwnFieldExpander = false;`
- L241 _public prototype_ `TSharedRef<SWidget> Construct(const SPropertyViewer::FArguments& InArgs);`
- L242 _public prototype_ `void Tick();`
- L244 _public prototype_ `void AddContainer(SPropertyViewer::FHandle Identifier, TOptional<FText> DisplayName, const UStruct* Struct);`
- L245 _public prototype_ `void AddContainerInstance(SPropertyViewer::FHandle Identifier, TOptional<FText> DisplayName, UObject* Object);`
- L246 _public prototype_ `void AddContainerInstance(SPropertyViewer::FHandle Identifier, TOptional<FText> DisplayName, const UScriptStruct* Struct, void* Data);`
- L247 _public prototype_ `void Remove(SPropertyViewer::FHandle Identifier);`
- L248 _public prototype_ `void RemoveAll();`
- L249 _public prototype_ `TArray<SPropertyViewer::FSelectedItem> GetSelectedItems() const;`
- L250 _public prototype_ `void SetRawFilterText(const FText& InFilterText);`
- L251 _public prototype_ `void SetSelection(SPropertyViewer::FHandle Identifier, TArrayView<const FFieldVariant> FieldPath);`
- L254 _private prototype_ `void AddContainerInternal(SPropertyViewer::FHandle Identifier, TSharedPtr<FContainer>& NewContainer);`
- L256 _private prototype_ `TSharedRef<SWidget> CreateSearch();`
- L257 _private prototype_ `TSharedRef<SWidget> CreateTree(bool bHasPreWidget, bool bShowPropertyValue, bool bHasPostWidget, ESelectionMode::Type SelectionMode);`
- L259 _private prototype_ `void HandleSearchChanged(const FText& InFilterText);`
- L260 _private prototype_ `FText SetRawFilterTextInternal(const FText& InFilterText);`
- L261 _private prototype_ `void SetHighlightTextRecursive(const TSharedPtr<FTreeNode>& OwnerNode, const FText& HighlightText);`
- L262 _private prototype_ `void HandleGetFilterStrings(TSharedPtr<FTreeNode> Item, TArray<FString>& OutStrings);`
- L264 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FTreeNode> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L265 _private prototype_ `void HandleGetChildren(TSharedPtr<FTreeNode> InParent, TArray<TSharedPtr<FTreeNode>>& OutChildren);`
- L267 _private prototype_ `TSharedPtr<SWidget> HandleContextMenuOpening();`
- L268 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FTreeNode> Item, ESelectInfo::Type SelectionType);`
- L269 _private prototype_ `void HandleDoubleClick(TSharedPtr<FTreeNode> Item);`
- L270 _private prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, const TSharedPtr<FTreeNode> Item);`
- L272 _private prototype_ `TSharedPtr<FTreeNode> FindExistingChild(const TSharedPtr<FTreeNode>& ContainerNode, TArrayView<const FFieldVariant> FieldPath) const;`
- L275 _private prototype_ `void HandleBlueprintCompiled();`
- L276 _private prototype_ `void HandleReplaceViewedObjects(const TMap<UObject*, UObject*>& OldToNewObjectMap);`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::PropertyViewer`)

### `Source/Runtime/AdvancedWidgets/Public/AdvancedWidgets.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AdvancedWidgets/Public/AdvancedWidgetsModule.h` (Public)


#### class `FAdvancedWidgetsModule`  
`class FAdvancedWidgetsModule : public IModuleInterface`  
_L18-39_
- inherits: `IModuleInterface`
- desc: Advanced Widgets module
- L21 _public prototype_ `static FAdvancedWidgetsModule& GetModule();`
- L22 _public prototype_ `static FAdvancedWidgetsModule* GetModulePtr();`
- L27 _public prototype_ `virtual void StartupModule();` — Called right after the plugin DLL has been loaded and the plugin object has been created
- L32 _public prototype_ `virtual void ShutdownModule();` — Called before the plugin is unloaded, right before the plugin object is destroyed.
- L35 _public prototype_ `UE::PropertyViewer::FPropertyValueFactory& GetPropertyValueFactory() const;`
- L38 _private member_ `TUniquePtr<UE::PropertyViewer::FPropertyValueFactory> PropertyValueFactory;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Components/RadialSlider.h` (Public)


#### class `URadialSlider`  
`class URadialSlider : public UWidget`  
_L27-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- L34 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance, BlueprintSetter = SetValue, meta = (UIMin="0", UIMax="1"))` — The slider value to display.
- L38 _public member_ `FGetFloat ValueDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L42 _public member_ `bool bUseCustomDefaultValue;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether the slider should draw it's progress bar from a custom value on the slider
- L46 _public member_ `float CustomDefaultValue;` — `UPROPERTY(EditAnywhere, Category = Appearance, meta = (EditCondition = "bUseCustomDefaultValue", UIMin = "0", UIMax = "1"))` — The value where the slider should draw it's progress bar from, independent of direction
- L50 _public member_ `FRuntimeFloatCurve SliderRange;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — A curve that defines how the slider should be sampled. Default is linear.
- L54 _public member_ `TArray<float> ValueTags;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — Adds text tags to the radial slider at the value's position.
- L58 _public member_ `float SliderHandleStartAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = "0", ClampMax = "360"), Category = Appearance)` — The angle at which the Slider Handle will start.
- L62 _public member_ `float SliderHandleEndAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = "0", ClampMax = "360"), Category = Appearance)` — The angle at which the Slider Handle will end.
- L66 _public member_ `float AngularOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = "0", ClampMax = "360"), Category = Appearance)` — Rotates radial slider by arbitrary offset to support full gamut of configurations.
- L70 _public member_ `FVector2D HandStartEndRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — Start and end of the hand as a ratio to the slider radius (so 0.0 to 1.0 is from the slider center to the handle).
- L74 _public member_ `FSliderStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=( DisplayName="Style" ))` — The progress bar style
- L78 _public member_ `FLinearColor SliderBarColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)` — The color to draw the slider bar in.
- L82 _public member_ `FLinearColor SliderProgressColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the completed progress of the slider bar in.
- L86 _public member_ `FLinearColor SliderHandleColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)` — The color to draw the slider handle in.
- L90 _public member_ `FLinearColor CenterBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)` — The color to draw the center background in.
- L94 _public member_ `bool Locked;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, AdvancedDisplay)` — Whether the handle is interactive or fixed.
- L98 _public member_ `bool MouseUsesStep;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)` — Sets new value if mouse position is greater/less than half the step size.
- L102 _public member_ `bool RequiresControllerLock;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)` — Sets whether we have to lock input to change the slider value.
- L106 _public member_ `float StepSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, meta=(UIMin="0", UIMax="1"))` — The amount to adjust the value by, when using a controller or keyboard
- L110 _public member_ `bool IsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")` — Should the slider be focusable?
- L114 _public member_ `bool UseVerticalDrag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — Whether the value is changed when dragging vertically as opposed to along the radial curve.
- L118 _public member_ `bool ShowSliderHandle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Whether to show the slider handle (thumb).
- L122 _public member_ `bool ShowSliderHand;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Whether to show the slider hand.
- L126 _public member_ `FOnMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is pressed and a capture begins.
- L130 _public member_ `FOnMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is released and a capture ends.
- L134 _public member_ `FOnControllerCaptureBeginEvent OnControllerCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture begins.
- L138 _public member_ `FOnControllerCaptureEndEvent OnControllerCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture ends.
- L142 _public member_ `FOnFloatValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Called when the value is changed by slider or typing.
- L146 _public prototype_ `float GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Gets the current value of the slider.
- L150 _public prototype_ `float GetCustomDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Gets the current custom default value of the slider.
- L154 _public prototype_ `float GetNormalizedSliderHandlePosition() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Get the current raw slider alpha from 0 to 1
- L158 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the current value of the slider.
- L162 _public prototype_ `void SetCustomDefaultValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the current custom default value of the slider.
- L166 _public prototype_ `void SetSliderRange(const FRuntimeFloatCurve& InSliderRange);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the curve for the slider range
- L170 _public prototype_ `void SetValueTags(const TArray<float>& InValueTags);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Adds value tags to the slider.
- L174 _public prototype_ `void SetSliderHandleStartAngle(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the minimum angle of the slider.
- L178 _public prototype_ `void SetSliderHandleEndAngle(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the maximum angle of the slider.
- L182 _public prototype_ `void SetAngularOffset(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the Angular Offset for the slider.
- L186 _public prototype_ `void SetHandStartEndRatio(FVector2D InValue);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the start and end of the hand as a ratio to the slider radius (so 0.0 to 1.0 is from the slider center to the handle).
- L190 _public prototype_ `void SetLocked(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the handle to be interactive or fixed
- L194 _public prototype_ `void SetStepSize(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the amount to adjust the value by, when using a controller or keyboard
- L198 _public prototype_ `void SetSliderBarColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color of the slider bar
- L202 _public prototype_ `void SetSliderProgressColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the progress color of the slider bar
- L206 _public prototype_ `void SetSliderHandleColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color of the handle bar
- L210 _public prototype_ `void SetCenterBackgroundColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color of the slider bar
- L214 _public prototype_ `void SetUseVerticalDrag(bool InUseVerticalDrag);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Set whether the value is changed when dragging vertically as opposed to along the radial curve.
- L218 _public prototype_ `void SetShowSliderHandle(bool InShowSliderHandle);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Whether to show the slider handle (thumb).
- L222 _public prototype_ `void SetShowSliderHand(bool InShowSliderHand);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Whether to show the slider hand.
- L225 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L229 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L233 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L238 _protected member_ `TSharedPtr<SRadialSlider> MyRadialSlider;` — Native Slate Widget
- L241 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L244 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L245 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L246 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L247 _protected prototype_ `void HandleOnControllerCaptureBegin();`
- L248 _protected prototype_ `void HandleOnControllerCaptureEnd();`
- L251 _protected prototype_ `virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;`
- L254 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, Value);`

### `Source/Runtime/AdvancedWidgets/Public/Framework/ColorGrading/ColorGradingCommon.h` (Public)


#### enum `UE::ColorGrading::EColorGradingComponent`  
`enum class EColorGradingComponent`  
_L15-24_
- desc: Color components that can be controlled by a color grading widget.
- L17 _public enumerator_ `Red`
- L18 _public enumerator_ `Green`
- L19 _public enumerator_ `Blue`
- L20 _public enumerator_ `Hue`
- L21 _public enumerator_ `Saturation`
- L22 _public enumerator_ `Value`
- L23 _public enumerator_ `Luminance`

#### enum `UE::ColorGrading::EColorGradingWheelType`  
`enum class EColorGradingWheelType`  
_L27-34_
- desc: Types of color grading modes
- L30 _public enumerator_ `Standard` — A wheel that controls a standard color value
- L33 _public enumerator_ `Offset` — A wheel that applies an offset to colors

#### enum `UE::ColorGrading::EColorGradingColorDisplayMode`  
`enum class EColorGradingColorDisplayMode`  
_L37-41_
- desc: Modes that colors can be displayed in for the color grading panel
- L39 _public enumerator_ `RGB`
- L40 _public enumerator_ `HSV`

#### enum `UE::ColorGrading::EColorGradingModes`  
`enum class EColorGradingModes`  
_L44-52_
- desc: Enumerates color picker modes
- L46 _public enumerator_ `Saturation`
- L47 _public enumerator_ `Contrast`
- L48 _public enumerator_ `Gamma`
- L49 _public enumerator_ `Gain`
- L50 _public enumerator_ `Offset`
- L51 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ColorGrading` (scope `UE`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetCurrentVector4Value, FVector4&);` — Callback to get the current FVector4 value
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetCurrentVector4Value, FVector4&);` (scope `UE::ColorGrading`) — Callback to get the current FVector4 value

### `Source/Runtime/AdvancedWidgets/Public/Framework/PropertyViewer/FieldIconFinder.h` (Public)


#### struct `UE::PropertyViewer::FFieldColorSettings`  
`struct FFieldColorSettings`  
_L18-61_
- L21 _public member_ `FLinearColor DefaultTypeColor = FLinearColor(0.750000f, 0.6f, 0.4f, 1.0f);` — The default color is used only for types not specifically defined below.
- L24 _public member_ `FLinearColor BooleanTypeColor = FColorList::Maroon;` — Boolean type color
- L27 _public member_ `FLinearColor ClassTypeColor = FLinearColor(0.1f, 0.0f, 0.5f, 1.0f);` — Class type color
- L30 _public member_ `FLinearColor EnumTypeColor = FLinearColor(0.0f, 0.160000f, 0.131270f, 1.0f);` — Enum pin type color
- L33 _public member_ `FLinearColor IntTypeColor = FLinearColor(0.013575f, 0.770000f, 0.429609f, 1.0f);` — Integer pin type color
- L36 _public member_ `FLinearColor FloatTypeColor = FLinearColor(0.357667f, 1.0f, 0.060000f, 1.0f);` — Floating-point type color
- L39 _public member_ `FLinearColor NameTypeColor = FLinearColor(0.607717f, 0.224984f, 1.0f, 1.0f);` — Name type color
- L42 _public member_ `FLinearColor DelegateTypeColor = FLinearColor(1.0f, 0.04f, 0.04f, 1.0f);` — Delegate type color
- L45 _public member_ `FLinearColor ObjectTypeColor = FLinearColor(0.0f, 0.4f, 0.910000f, 1.0f);` — Object type color
- L48 _public member_ `FLinearColor InterfaceTypeColor = FLinearColor(0.8784f, 1.0f, 0.4f, 1.0f);` — Interface type color
- L51 _public member_ `FLinearColor StringTypeColor = FLinearColor(1.0f, 0.0f, 0.660537f, 1.0f);` — String type color
- L54 _public member_ `FLinearColor TextTypeColor = FLinearColor(0.8f, 0.2f, 0.4f, 1.0f);` — Text type color
- L57 _public member_ `FLinearColor DefaultStructTypeColor = FColorList::DarkSlateBlue;` — Default Struct pin type color
- L60 _public member_ `TMap<FString, FLinearColor> StructColors;` — Struct pin type color

#### class `UE::PropertyViewer::FFieldIconFinder`  
`class FFieldIconFinder`  
_L65-87_
- L75 _public typedef_ `using FFieldIconArray = TArray<FFieldIcon, TInlineAllocator<2>>;`
- L78 _public prototype_ `static const FSlateBrush* GetIcon(const UObject* Object);`
- L81 _public prototype_ `static FFieldIconArray GetFunctionIcon(const UFunction* Function);`
- L82 _public prototype_ `static FFieldIconArray GetFunctionIcon(const UFunction* Function, const FFieldColorSettings& Settings);`
- L85 _public prototype_ `static FFieldIconArray GetPropertyIcon(const FProperty* Property);`
- L86 _public prototype_ `static FFieldIconArray GetPropertyIcon(const FProperty* Property, const FFieldColorSettings& Settings);`

#### struct `UE::PropertyViewer::FFieldIconFinder::FFieldIcon`  
`struct FFieldIcon`  
_L69-73_
- L71 _public member_ `const FSlateBrush* Icon = nullptr;`
- L72 _public member_ `FSlateColor Color;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Framework/PropertyViewer/IFieldExpander.h` (Public)


#### class `UE::PropertyViewer::IFieldExpander`  
`class IFieldExpander`  
_L20-36_
- L24 _public prototype_ `virtual TOptional<const UClass*> CanExpandObject(const FObjectPropertyBase* Property, const UObject* Instance) const = 0;` — @return the class that should be expended for this instance. The instance can be null.
- L26 _public prototype_ `virtual bool CanExpandScriptStruct(const FStructProperty* StructProperty) const = 0;` — @return true if the struct property can be expended.
- L28 _public prototype_ `virtual TOptional<const UStruct*> GetExpandedFunction(const UFunction* Function) const = 0;` — @return the struct that can be expanded from the function. ie. This can be the function itself (to see the arguments) or a return property.
- L29 _public prototype_ `virtual ~IFieldExpander() = default;`
- L32 _public function_ `virtual bool CanExpandFunction(const UFunction* Function) const` — `UE_DEPRECATED(5.2, "CanExpandFunction is deprecated and GetExpandedFunction should be used instead.")`

#### class `UE::PropertyViewer::FFieldExpander_Default`  
`class FFieldExpander_Default : public IFieldExpander`  
_L38-119_
- inherits: `IFieldExpander`
- L41 _public prototype_ `FFieldExpander_Default() = default;`
- L58 _public function_ `virtual TOptional<const UClass*> CanExpandObject(const FObjectPropertyBase* Property, const UObject* Instance) const override`
- L73 _public function_ `virtual bool CanExpandScriptStruct(const FStructProperty*) const override`
- L78 _public function_ `virtual TOptional<const UStruct*> GetExpandedFunction(const UFunction* Function) const override`
- L94 _public function_ `void SetExpandObject(EObjectExpandFlag InExpandObject)`
- L99 _public function_ `void SetExpandScriptStruct(bool bInExpandScriptStruct)`
- L105 _public function_ `void SetExpandFunction(bool bInExpandFunction)` — `UE_DEPRECATED(5.2, "Use the SetExpandFunction with the EExpandFunctionType")`
- L110 _public function_ `void SetExpandFunction(EFunctionExpand InExpandFunction)`
- L116 _private member_ `EObjectExpandFlag ExpandObject = EObjectExpandFlag::None;`
- L117 _private member_ `bool bExpandScriptStruct = false;`
- L118 _private member_ `EFunctionExpand ExpandFunction = EFunctionExpand::None;`

#### enum `UE::PropertyViewer::FFieldExpander_Default::EObjectExpandFlag`  
`enum class EObjectExpandFlag : uint8`  
_L43-48_
- L45 _public enumerator_ `None = 0`
- L46 _public enumerator_ `UseInstanceClass = 1 << 1`
- L47 _public enumerator_ `RequireValidInstance = 1 << 2`

#### enum `UE::PropertyViewer::FFieldExpander_Default::EFunctionExpand`  
`enum class EFunctionExpand : uint8`  
_L51-56_
- L53 _public enumerator_ `None = 0`
- L54 _public enumerator_ `FunctionProperties`
- L55 _public enumerator_ `FunctionReturnProperty`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L120 _prototype_ `ENUM_CLASS_FLAGS(FFieldExpander_Default::EObjectExpandFlag);` (scope `UE::PropertyViewer`)

### `Source/Runtime/AdvancedWidgets/Public/Framework/PropertyViewer/IFieldIterator.h` (Public)


#### class `UE::PropertyViewer::IFieldIterator`  
`class IFieldIterator`  
_L18-35_
- L22 _public function_ `virtual TArray<FFieldVariant> GetFields(const UStruct*) const` — `UE_DEPRECATED(5.6, "GetFields(const UStruct*) is deprecated. Please use the overload with three arguments: GetFields(const UStruct*, const FName, const UStruct*).")`
- L28 _public function_ `virtual TArray<FFieldVariant> GetFields(const UStruct* Struct, const FName FieldName, const UStruct* ContainerStruct) const`
- L34 _public prototype_ `virtual ~IFieldIterator() = default;`

#### class `UE::PropertyViewer::FFieldIterator_BlueprintVisible`  
`class FFieldIterator_BlueprintVisible : public IFieldIterator`  
_L37-40_
- inherits: `IFieldIterator`
- L39 _private prototype_ `virtual TArray<FFieldVariant> GetFields(const UStruct* Struct, const FName FieldName, const UStruct* ContainerStruct) const override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Framework/PropertyViewer/INotifyHook.h` (Public)


#### class `UE::PropertyViewer::INotifyHook`  
`class INotifyHook`  
_L12-17_
- L15 _public prototype_ `virtual void OnPreValueChange(const FPropertyPath& Path) = 0;`
- L16 _public prototype_ `virtual void OnPostValueChange(const FPropertyPath& Path) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Framework/PropertyViewer/PropertyPath.h` (Public)


#### struct `UE::PropertyViewer::FPropertyPath`  
`struct FPropertyPath`  
_L26-62_
- L29 _public typedef_ `using FPropertyArray = TArray<const FProperty*, TInlineAllocator<1>>;`
- L31 _public prototype_ `FPropertyPath() = default;`
- L32 _public prototype_ `FPropertyPath(UObject* Object, const FProperty* Property);`
- L33 _public prototype_ `FPropertyPath(UObject* Object, FPropertyArray Properties);`
- L34 _public prototype_ `FPropertyPath(const UScriptStruct* ScriptStruct, void* Data, const FProperty* Property);`
- L35 _public prototype_ `FPropertyPath(const UScriptStruct* ScriptStruct, void* Data, FPropertyArray Properties);`
- L38 _public function_ `bool HasProperty() const`
- L43 _public function_ `const FProperty* GetLastProperty() const`
- L48 _public function_ `TArrayView<const FProperty* const> GetProperties() const`
- L53 _public prototype_ `void* GetContainerPtr();`
- L54 _public prototype_ `const void* GetContainerPtr() const;`
- L57 _private member_ `TWeakObjectPtr<UObject> TopLevelContainer_Object = nullptr;`
- L58 _private member_ `TWeakObjectPtr<const UScriptStruct> TopLevelContainer_ScriptStruct = nullptr;`
- L59 _private member_ `void* TopLevelContainer_ScriptStructData = nullptr;`
- L61 _private member_ `FPropertyArray Properties;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Framework/PropertyViewer/PropertyValueFactory.h` (Public)


#### class `UE::PropertyViewer::FPropertyValueFactory`  
`class FPropertyValueFactory`  
_L27-79_
- L59 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGenerate, FGenerateArgs);`
- L62 _public prototype_ `FPropertyValueFactory();`
- L63 _public prototype_ `FPropertyValueFactory(const FPropertyValueFactory&) = delete;`
- L64 _public prototype_ `FPropertyValueFactory& operator=(const FPropertyValueFactory&) = delete;`
- L66 _public prototype_ `TSharedPtr<SWidget> Generate(FGenerateArgs Args) const;`
- L67 _public prototype_ `TSharedPtr<SWidget> GenerateDefault(FGenerateArgs Args) const;`
- L69 _public prototype_ `bool HasCustomPropertyValue(const FFieldClass* Property) const;`
- L70 _public prototype_ `bool HasCustomPropertyValue(const UStruct* Struct) const;`
- L72 _public prototype_ `FHandle Register(const FFieldClass* Field, FOnGenerate OnGenerate);`
- L73 _public prototype_ `FHandle Register(const UStruct* Struct, FOnGenerate OnGenerate);`
- L74 _public prototype_ `void Unregister(FHandle Handle);`
- L77 _private prototype_ `static FHandle MakeHandle();`
- L78 _private member_ `TPimplPtr<Private::FPropertyValueFactoryImpl> Impl;`

#### struct `UE::PropertyViewer::FPropertyValueFactory::FHandle`  
`struct FHandle`  
_L30-48_
- L34 _private member_ `int32 Id = 0;`
- L36 _public function_ `bool operator== (FHandle Other) const`
- L40 _public function_ `bool operator!= (FHandle Other) const`
- L44 _public function_ `bool IsValid() const`

#### struct `UE::PropertyViewer::FPropertyValueFactory::FGenerateArgs`  
`struct FGenerateArgs`  
_L50-56_
- L52 _public member_ `FPropertyPath Path;`
- L53 _public member_ `FFieldVariant* Field = nullptr;`
- L54 _public member_ `INotifyHook* NotifyHook = nullptr;`
- L55 _public member_ `bool bCanEditValue = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::PropertyViewer`)
- L59 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGenerate, FGenerateArgs);`

### `Source/Runtime/AdvancedWidgets/Public/Slate/SRadialSlider.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `inline void SRadialSliderHeaderDeprecatedWarning()` — `UE_DEPRECATED(5.1, "Including Slate/SRadialSlider.h is deprecated. The location of SRadialSlider has changed. Please include Widgets/SRadialSlider.h instead.")`
- L13 _function_ `inline void TriggerSRadialSliderHeaderDeprecatedWarning()`

### `Source/Runtime/AdvancedWidgets/Public/Styling/AdvancedWidgetsStyle.h` (Public)


#### class `UE::AdvancedWidgets::FAdvancedWidgetsStyle`  
`class FAdvancedWidgetsStyle`  
_L16-34_
- desc: Style for advanced widgets
- L19 _public prototype_ `static void Create();`
- L20 _public prototype_ `static void Destroy();`
- L21 _public prototype_ `static const ISlateStyle& Get();`
- L23 _public function_ `static const ::UE::PropertyViewer::FFieldColorSettings& GetColorSettings()`
- L30 _private member_ `static TUniquePtr<FSlateStyleSet> Instance;` — Singleton instances of this style.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AdvancedWidgets` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Styling/ColorGradingSpinBoxStyle.h` (Public)


#### struct `FColorGradingSpinBoxStyle`  
`struct FColorGradingSpinBoxStyle : public FSlateWidgetStyle`  
_L15-66_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a color grading spin box
- L19 _public prototype_ `FColorGradingSpinBoxStyle();`
- L21 _public prototype_ `virtual ~FColorGradingSpinBoxStyle() = default;`
- L23 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L25 _public member_ `static const FName TypeName;`
- L26 _public function_ `virtual const FName GetTypeName() const override`
- L28 _public prototype_ `static const FColorGradingSpinBoxStyle& GetDefault();`
- L32 _public member_ `FSlateBrush BorderBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Brush used to draw the border of the spinbox
- L33 _public function_ `FColorGradingSpinBoxStyle& SetBorderBrush(const FSlateBrush& InBorderBrush)`
- L37 _public member_ `FSlateBrush ActiveBorderBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Brush used to draw the border of the spinbox when it's in active use by the user
- L38 _public function_ `FColorGradingSpinBoxStyle& SetActiveBorderBrush(const FSlateBrush& InActiveBorderBrush)`
- L42 _public member_ `FSlateBrush HoveredBorderBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Brush used to draw the border of the spinbox when it's hovered over
- L43 _public function_ `FColorGradingSpinBoxStyle& SetHoveredBorderBrush(const FSlateBrush& InHoveredBorderBrush)`
- L47 _public member_ `FSlateBrush SelectorBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Brush used to draw the selector indicating the current value
- L48 _public function_ `FColorGradingSpinBoxStyle& SetSelectorBrush(const FSlateBrush& InSelectorBrush)`
- L52 _public member_ `float SelectorWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Width of the selector
- L53 _public function_ `FColorGradingSpinBoxStyle& SetSelectorWidth(float InSelectorWidth)`
- L59 _public function_ `void UnlinkColors()` — Unlinks all colors in this style. @see FSlateColor::Unlink

### `Source/Runtime/AdvancedWidgets/Public/Util/ColorGradingUtil.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ColorGrading` (scope `UE`)
- L11 _prototype_ `EColorGradingComponent GetColorGradingComponent(EColorGradingColorDisplayMode DisplayMode, int Index);` (scope `UE::ColorGrading`) — Get the color grading component typically associated with the given display mode and component index.

### `Source/Runtime/AdvancedWidgets/Public/Util/TrackedVector4PropertyHandle.h` (Public)


#### class `FTrackedVector4PropertyHandle`  
`class FTrackedVector4PropertyHandle`  
_L10-41_
- desc: Convenience wrapper for an IPropertyHandle that lets us track when we're using this handle to set the property's vector value.
- L13 _public prototype_ `FTrackedVector4PropertyHandle();`
- L14 _public prototype_ `FTrackedVector4PropertyHandle(TWeakPtr<IPropertyHandle> InHandle);`
- L17 _public prototype_ `TSharedPtr<IPropertyHandle> GetHandle() const;` — Get the underlying property handle.
- L20 _public prototype_ `FPropertyAccess::Result SetValue(const FVector4& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);` — Set the property's vector value
- L23 _public prototype_ `FPropertyAccess::Result GetValue(FVector4& OutValue) const;` — Get the property's vector value
- L28 _public prototype_ `bool IsSettingValue() const;` — @return Whether we're currently inside a call to SetValue
- L33 _public prototype_ `bool IsValidHandle() const;` — @return Whether or not the handle points to a valid property node. This can be true but GetProperty may still return null
- L37 _private member_ `TWeakPtr<IPropertyHandle> Handle;` — The underlying handle to the property
- L40 _private member_ `bool bIsSettingValue = false;` — Whether we're currently changing the property using SetValue

### `Source/Runtime/AdvancedWidgets/Public/Widgets/ColorGrading/SColorGradingComponentViewer.h` (Public)


#### class `UE::ColorGrading::SColorGradingComponentViewer`  
`class SColorGradingComponentViewer : public SCompoundWidget`  
_L24-152_
- inherits: `SCompoundWidget`
- desc: A slider displayed in tandem with a color grading wheel. Allows mouse-based control or direct input via a textbox. Shows a gradient representing the controlled color component.
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, float);` — Notification for numeric value change
- L33 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L35 _public function_ `SLATE_BEGIN_ARGS(SColorGradingComponentViewer) : _Value(0.f) , _MinValue(0.f) , _MaxValue(2.f) , _MinFractionalDigits(DefaultMinFractionalDigits) , _MaxFractionalDigits(DefaultMaxFractionalDigits) , _Delta(0.f) , _ShiftMultiplier(10.f) , _CtrlMultiplier(0.1f) , _SupportDynamicSliderMaxValue(false) , _SupportDynamicSliderMinValue(false) , _SliderExponent(1.f) , _OnValueChanged() , _OnQueryCurrentColor() , _UseCompactDisplay(false) , _AllowSpin(true)`
- L54 _public prototype_ `SLATE_ATTRIBUTE(TOptional<float>, Value) SLATE_ATTRIBUTE(EColorGradingComponent, Component) SLATE_ATTRIBUTE(EColorGradingModes, ColorGradingMode) SLATE_ATTRIBUTE(TOptional<float>, MinValue) SLATE_ATTRIBUTE(TOptional<float>, MaxValue) SLATE_ATTRIBUTE(TOptional<float>, MinSliderValue) SLATE_ATTRIBUTE(TOptional<float>, MaxSliderValue) SLATE_ATTRIBUTE(TOptional<int32>, MinFractionalDigits) SLATE_ATTRIBUTE(TOptional<int32>, MaxFractionalDigits) SLATE_ATTRIBUTE(float, Delta) SLATE_ATTRIBUTE(float, ShiftMultiplier) SLATE_ATTRIBUTE(float, CtrlMultiplier) SLATE_ATTRIBUTE(int32, LinearDeltaSensitivity) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMaxValue) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMinValue) SLATE_EVENT(FOnDynamicSliderMinMaxValueChanged, OnDynamicSliderMaxValueChanged) SLATE_EVENT(FOnDynamicSliderMinMaxValueChanged, OnDynamicSliderMinValueChanged) SLATE_ATTRIBUTE(float, SliderExponent) SLATE_ATTRIBUTE(float, SliderExponentNeutralValue) SLATE_ATTRIBUTE(TOptional<float>, WheelStep)` — The value to display
- L112 _public prototype_ `virtual ~SColorGradingComponentViewer();`
- L119 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L122 _public prototype_ `float GetMaxSliderValue() const;` — Get the maximum slider value
- L125 _public prototype_ `float GetMinSliderValue() const;` — Get the minimum slider value
- L130 _private prototype_ `float GetValue() const;` — Get the value as a non-optional float
- L133 _private prototype_ `FText GetComponentLabelText() const;` — Get the component's name as shown on a short label
- L136 _private prototype_ `FText GetComponentToolTipText() const;` — Get the component's name as shown in a tooltip
- L139 _private member_ `static constexpr int32 DefaultMinFractionalDigits = 1;` — The default minimum fractional digits
- L142 _private member_ `static constexpr int32 DefaultMaxFractionalDigits = 3;` — The default maximum fractional digits
- L144 _private member_ `TAttribute<TOptional<float>> MinValue;`
- L145 _private member_ `TAttribute<TOptional<float>> MaxValue;`
- L146 _private member_ `TAttribute<TOptional<float>> MinSliderValue;`
- L147 _private member_ `TAttribute<TOptional<float>> MaxSliderValue;`
- L148 _private member_ `TAttribute<TOptional<float>> OptionalValue;`
- L149 _private member_ `TSharedPtr<SNumericEntryBox<float>> NumericEntryBox;`
- L150 _private member_ `TSharedPtr<SColorGradingComponentSpinBox> GradientSpinBox;`
- L151 _private member_ `TAttribute<EColorGradingComponent> Component;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ADVANCEDWIDGETS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ColorGrading` (scope `UE`)
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, float);` — Notification for numeric value change
- L33 _delegate_ `DECLARE_DELEGATE_FourParams(FOnDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/ColorGrading/SColorGradingPicker.h` (Public)


#### class `UE::ColorGrading::SColorGradingPicker`  
`class SColorGradingPicker : public SCompoundWidget`  
_L23-157_
- inherits: `SCompoundWidget`
- desc: Class for placing a color picker. If all you need is a standalone color picker, use the functions OpenColorGradingWheel and DestroyColorGradingWheel, since they hold a static instance of the color picker.
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L31 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnColorGradingPickerValueChanged, FVector4&, bool);` — Delegate called when the widget Color Data changed
- L34 _public function_ `SLATE_BEGIN_ARGS(SColorGradingPicker) : _AllowSpin(true) , _SupportDynamicSliderMaxValue(false) , _SupportDynamicSliderMinValue(false) , _DesiredWheelSize() , _MainDelta(0.01f) , _MainShiftMultiplier(10.f) , _MainCtrlMultiplier(0.1f) , _ColorGradingModes(EColorGradingModes::Saturation) , _OnColorCommitted() , _OnQueryCurrentColor()`
- L47 _public prototype_ `SLATE_ARGUMENT(TOptional<float>, ValueMin) SLATE_ARGUMENT(TOptional<float>, ValueMax) SLATE_ARGUMENT(TOptional<float>, SliderValueMin) SLATE_ARGUMENT(TOptional<float>, SliderValueMax) SLATE_ATTRIBUTE(bool, AllowSpin) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMaxValue) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMinValue) SLATE_ATTRIBUTE(int32, DesiredWheelSize) SLATE_ARGUMENT(float, MainDelta) SLATE_ARGUMENT(float, MainShiftMultiplier) SLATE_ARGUMENT(float, MainCtrlMultiplier) SLATE_ARGUMENT_DEPRECATED(int32, MainShiftMouseMovePixelPerDelta, 5.4, "Shift Mouse Move Pixel Per Delta is deprecated and incrementing by a fixed delta per pixel is no longer supported. Please use ShiftMultiplier and CtrlMultiplier which will multiply the step per mouse move") SLATE_ARGUMENT(EColorGradingModes, ColorGradingModes) SLATE_EVENT(FOnColorGradingPickerValueChanged, OnColorCommitted) SLATE_EVENT(FOnGetCurrentVector4Value, OnQueryCurrentColor) SLATE_EVENT(FSimpleDelegate, OnBeginSliderMovement) SLATE_EVENT(FSimpleDelegate, OnEndSliderMovement) SLATE_EVENT(FSimpleDelegate, OnBeginMouseCapture)`
- L101 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget @param InArgs Declaration from which to construct the widget.
- L103 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMaxValueChangedDelegate()`
- L104 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMinValueChangedDelegate()`
- L107 _public prototype_ `void OnDynamicSliderMaxValueChanged(float NewMaxSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfHigher);` — Callback when the max/min spinner value are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L108 _public prototype_ `void OnDynamicSliderMinValueChanged(float NewMinSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfLower);`
- L112 _protected prototype_ `void TransformLinearColorRangeToColorGradingRange(FVector4& VectorValue) const;`
- L113 _protected prototype_ `void TransformColorGradingRangeToLinearColorRange(FVector4& VectorValue) const;`
- L114 _protected prototype_ `void TransformColorGradingRangeToLinearColorRange(float& FloatValue);`
- L116 _protected prototype_ `TOptional<float> OnGetMainValue() const;`
- L117 _protected prototype_ `void OnMainValueChanged(float InValue, bool ShouldCommitValueChanges);`
- L118 _protected prototype_ `void OnMainValueCommitted(float InValue, ETextCommit::Type CommitType);`
- L120 _protected prototype_ `FLinearColor GetCurrentLinearColor();`
- L122 _protected prototype_ `bool IsEntryBoxEnabled() const;`
- L125 _protected prototype_ `void HandleCurrentColorValueChanged(const FLinearColor& NewValue, bool ShouldCommitValueChanges);` — Callback for value changes in the color spectrum picker.
- L127 _protected prototype_ `void HandleColorWheelMouseCaptureBegin(const FLinearColor& InValue);`
- L128 _protected prototype_ `void HandleColorWheelMouseCaptureEnd(const FLinearColor& InValue);`
- L130 _protected prototype_ `void OnBeginSliderMovement();`
- L131 _protected prototype_ `void OnEndSliderMovement(float NewValue);`
- L132 _protected prototype_ `void AdjustRatioValue(FVector4& NewValue);`
- L134 _protected member_ `bool bIsMouseDragging;`
- L135 _protected member_ `FVector4 StartDragRatio;`
- L137 _protected member_ `float SliderValueMin;`
- L138 _protected member_ `float SliderValueMax;`
- L139 _protected member_ `float MainDelta;`
- L140 _protected member_ `float MainShiftMultiplier;`
- L141 _protected member_ `float MainCtrlMultiplier;`
- L142 _protected member_ `EColorGradingModes ColorGradingModes;`
- L144 _protected member_ `TSharedPtr<SNumericEntryBox<float>> NumericEntryBoxWidget;`
- L147 _protected member_ `FOnColorGradingPickerValueChanged OnColorCommitted;` — Invoked when a new value is selected on the color wheel
- L149 _protected member_ `FOnGetCurrentVector4Value OnQueryCurrentColor;`
- L150 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMaxValueChanged;`
- L151 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMinValueChanged;`
- L153 _protected member_ `FSimpleDelegate ExternalBeginSliderMovementDelegate;`
- L154 _protected member_ `FSimpleDelegate ExternalEndSliderMovementDelegate;`
- L155 _protected member_ `FSimpleDelegate ExternalBeginMouseCaptureDelegate;`
- L156 _protected member_ `FSimpleDelegate ExternalEndMouseCaptureDelegate;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ColorGrading` (scope `UE`)
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L31 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnColorGradingPickerValueChanged, FVector4&, bool);` — Delegate called when the widget Color Data changed

### `Source/Runtime/AdvancedWidgets/Public/Widgets/ColorGrading/SColorGradingWheel.h` (Public)


#### class `UE::ColorGrading::SColorGradingWheel`  
`class SColorGradingWheel : public SLeafWidget, public FGCObject`  
_L20-162_
- inherits: `SLeafWidget,FGCObject`
- desc: Implements the color wheel widget.
- L27 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnColorGradingWheelMouseCapture, const FLinearColor&);`
- L28 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnColorGradingWheelValueChanged, const FLinearColor&);`
- L30 _public function_ `SLATE_BEGIN_ARGS(SColorGradingWheel) : _SelectedColor() , _DesiredWheelSize() , _ExponentDisplacement() , _OnMouseCaptureBegin() , _OnMouseCaptureEnd() , _OnValueChanged()`
- L58 _public prototype_ `SColorGradingWheel();`
- L65 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget. @param InArgs The declaration data for this widget.
- L71 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L72 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L73 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L74 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L75 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L76 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L85 _protected prototype_ `UE::Slate::FDeprecateVector2DResult CalcRelativePositionFromCenter() const;` — Calculates the position of the color selection indicator. @return The position relative to the widget.
- L92 _protected prototype_ `bool ProcessMouseAction(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, bool bProcessWhenOutsideColorWheel);` — Performs actions according to mouse click / move @return	True if the mouse action occurred within the color wheel radius
- L95 _protected prototype_ `void SetSelectedColorAttribute(TAttribute<FLinearColor> InSelectedColor);`
- L98 _protected prototype_ `void SetDesiredWheelSizeAttribute(TAttribute<int32> InDesiredWheelSize);`
- L101 _protected prototype_ `void SetExponentDisplacementAttribute(TAttribute<float> InExponentDisplacement);`
- L104 _protected prototype_ `FVector2f GetActualSize(const FGeometry& MyGeometry) const;` — Get the actual size of the wheel, taking into account the available space
- L107 _protected function_ `TSlateAttributeRef<FLinearColor> GetSelectedColorAttribute() const` — @return an attribute reference of SelectedColor
- L110 _protected function_ `TSlateAttributeRef<int32> GetDesiredWheelSizeAttribute() const` — @return an attribute reference of DesiredWheelSize
- L113 _protected function_ `TSlateAttributeRef<float> GetExponentDisplacementAttribute() const` — @return an attribute reference of ExponentDisplacement
- L116 _protected member_ `TObjectPtr<UMaterial> BackgroundMaterial;` — The material to use for the wheel's background.
- L119 _protected member_ `TSharedPtr<FSlateBrush> BackgroundImage;` — The brush to use for the wheel's background.
- L122 _protected member_ `const FSlateBrush* CrossImage;` — The cross to show on top of the color wheel background.
- L125 _protected member_ `const FSlateBrush* SelectorImage;` — The color selector image to show.
- L128 _protected member_ `FOnColorGradingWheelMouseCapture OnMouseCaptureBegin;` — Invoked when the mouse is pressed and a capture begins.
- L131 _protected member_ `FOnColorGradingWheelMouseCapture OnMouseCaptureEnd;` — Invoked when the mouse is let up and a capture ends.
- L134 _protected member_ `FOnColorGradingWheelValueChanged OnValueChanged;` — Invoked when a new value is selected on the color wheel.
- L139 _private prototype_ `virtual FString GetReferencerName() const override;`
- L140 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L144 _private member_ `static constexpr float HueAngleOffset = -120.f / 180.f * PI;` — The angle in degrees (clockwise from due east) at which hue 0/red is represented on the wheel.
- L147 _private member_ `TSlateAttribute<FLinearColor> SelectedColorAttribute;` — The current color selected by the user.
- L149 _private member_ `TSlateAttribute<int32> DesiredWheelSizeAttribute;`
- L150 _private member_ `TSlateAttribute<float> ExponentDisplacementAttribute;`

#### union `UE::ColorGrading::SColorGradingWheel::(anonymous)`  
``  
_L154-161_

#### struct `UE::ColorGrading::SColorGradingWheel::__anonef30731c010a::(anonymous)`  
``  
_L156-159_

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ColorGrading` (scope `UE`)
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColorGradingWheelMouseCapture, const FLinearColor&);`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColorGradingWheelValueChanged, const FLinearColor&);`
- L157 _member_ `uint8 bIsAttributeDesiredWheelSizeSet : 1;` (scope `UE::ColorGrading::SColorGradingWheel::__anonef30731c010a::__anonef30731c0208`)
- L158 _member_ `uint8 bIsAttributeExponentDisplacementSet : 1;` (scope `UE::ColorGrading::SColorGradingWheel::__anonef30731c010a::__anonef30731c0208`)
- L160 _member_ `uint8 Union_IsAttributeSet;` (scope `UE::ColorGrading::SColorGradingWheel::__anonef30731c010a`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SBoolPropertyValue.h` (Public)


#### class `UE::PropertyViewer::SBoolPropertyValue`  
`class SBoolPropertyValue : public SCompoundWidget`  
_L17-36_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `static TSharedPtr<SWidget> CreateInstance(const FPropertyValueFactory::FGenerateArgs Args);`
- L23 _public function_ `SLATE_BEGIN_ARGS(SBoolPropertyValue)`
- L24 _public prototype_ `SLATE_ARGUMENT(FPropertyPath, Path);`
- L25 _public prototype_ `SLATE_ARGUMENT(INotifyHook*, NotifyHook);`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `ECheckBoxState HandleIsChecked() const;`
- L32 _private prototype_ `void HandleCheckStateChanged(ECheckBoxState NewState);`
- L34 _private member_ `FPropertyPath Path;`
- L35 _private member_ `INotifyHook* NotifyHook = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SDefaultPropertyValue.h` (Public)


#### class `UE::PropertyViewer::SDefaultPropertyValue`  
`class SDefaultPropertyValue : public SCompoundWidget`  
_L14-30_
- inherits: `SCompoundWidget`
- L17 _public prototype_ `static TSharedPtr<SWidget> CreateInstance(const FPropertyValueFactory::FGenerateArgs Args);`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDefaultPropertyValue)`
- L21 _public prototype_ `SLATE_ARGUMENT(FPropertyPath, Path);`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private prototype_ `FText GetText() const;`
- L29 _private member_ `FPropertyPath Path;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SEnumPropertyValue.h` (Public)


#### class `UE::PropertyViewer::SEnumPropertyValue`  
`class SEnumPropertyValue : public SCompoundWidget`  
_L16-39_
- inherits: `SCompoundWidget`
- L19 _public prototype_ `static TSharedPtr<SWidget> CreateInstance(const FPropertyValueFactory::FGenerateArgs Args);`
- L22 _public function_ `SLATE_BEGIN_ARGS(SEnumPropertyValue)`
- L23 _public prototype_ `SLATE_ARGUMENT(FPropertyPath, Path);`
- L24 _public prototype_ `SLATE_ARGUMENT(INotifyHook*, NotifyHook);`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `FText GetText() const;`
- L31 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L33 _private prototype_ `void SetEnumEntry(int32 Index);` — bool IsEnumEntryChecked(int32 Index) const;
- L34 _private prototype_ `int32 GetCurrentValue() const;`
- L36 _private member_ `TWeakObjectPtr<const UEnum> EnumType;`
- L37 _private member_ `FPropertyPath Path;`
- L38 _private member_ `INotifyHook* NotifyHook = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SFieldIcon.h` (Public)


#### class `UE::PropertyViewer::SFieldIcon`  
`class SFieldIcon : public SCompoundWidget`  
_L13-24_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SFieldIcon)`
- L17 _public prototype_ `SLATE_ARGUMENT(TOptional<const FFieldColorSettings>, OverrideColorSettings);`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UClass* Class);`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const UScriptStruct* Struct);`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const FProperty* Property);`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, const UFunction* FunctionToDisplay);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SFieldName.h` (Public)


#### class `UE::PropertyViewer::SFieldName`  
`class SFieldName : public SCompoundWidget`  
_L16-46_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SFieldName)`
- L22 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bShowIcon) = true;` — Show the class icon or the color that correspond to the property type.
- L24 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bSanitizeName) = false;` — Sanitize the property name.
- L26 _public prototype_ `SLATE_ARGUMENT(TOptional<FText>, OverrideDisplayName);` — Override the DisplayName of the container name.
- L28 _public prototype_ `SLATE_ARGUMENT(TOptional<const FFieldColorSettings>, OverrideIconColorSettings);` — Override the color settings of the icon.
- L30 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UClass* Class);` — The current highlighted text.
- L34 _public prototype_ `void Construct(const FArguments& InArgs, const UScriptStruct* Struct);`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, const FProperty* Property);`
- L36 _public prototype_ `void Construct(const FArguments& InArgs, const UFunction* FunctionToDisplay);`
- L38 _public prototype_ `void SetHighlightText(TAttribute<FText> InHighlightText);`
- L41 _private prototype_ `FText GetToolTipText() const;`
- L42 _private prototype_ `void Construct(const FArguments& InArgs, const FText& DisplayName, TSharedPtr<SWidget> Icon);`
- L44 _private member_ `TSharedPtr<STextBlock> NameBlock;`
- L45 _private member_ `FFieldVariant Field;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SNumericPropertyValue.h` (Public)


#### class `UE::PropertyViewer::SNumericPropertyValue`  
`class SNumericPropertyValue : public SCompoundWidget`  
_L16-46_
- inherits: `SCompoundWidget`
- L19 _public prototype_ `static TSharedPtr<SWidget> CreateInstance(const FPropertyValueFactory::FGenerateArgs Args);`
- L22 _public function_ `SLATE_BEGIN_ARGS(SNumericPropertyValue)`
- L23 _public prototype_ `SLATE_ARGUMENT(FPropertyPath, Path);`
- L24 _public prototype_ `SLATE_ARGUMENT(INotifyHook*, NotifyHook);`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `void OnEndSliderMovement_uint64(uint64 Value);`
- L31 _private prototype_ `void OnEndSliderMovement_int64(int64 Value);`
- L32 _private prototype_ `void OnEndSliderMovement_double(double Value);`
- L33 _private prototype_ `uint64 GetCurrentValue_uint64() const;`
- L34 _private prototype_ `int64 GetCurrentValue_int64() const;`
- L35 _private prototype_ `double GetCurrentValue_double() const;`
- L36 _private prototype_ `void OnValueChanged_uint64(uint64 Value);`
- L37 _private prototype_ `void OnValueChanged_int64(int64 Value);`
- L38 _private prototype_ `void OnValueChanged_double(double Value);`
- L39 _private prototype_ `void OnValueCommitted_uint64(uint64 Value, ETextCommit::Type CommitInfo);`
- L40 _private prototype_ `void OnValueCommitted_int64(int64 Value, ETextCommit::Type CommitInfo);`
- L41 _private prototype_ `void OnValueCommitted_double(double Value, ETextCommit::Type CommitInfo);`
- L44 _private member_ `FPropertyPath Path;`
- L45 _private member_ `INotifyHook* NotifyHook = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SObjectPropertyValue.h` (Public)


#### class `UE::PropertyViewer::SObjectPropertyValue`  
`class SObjectPropertyValue : public SCompoundWidget`  
_L15-37_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `static TSharedPtr<SWidget> CreateInstance(const FPropertyValueFactory::FGenerateArgs Args);`
- L21 _public function_ `SLATE_BEGIN_ARGS(SObjectPropertyValue)`
- L22 _public prototype_ `SLATE_ARGUMENT(FPropertyPath, Path);`
- L23 _public prototype_ `SLATE_ARGUMENT(INotifyHook*, NotifyHook);`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private member_ `FPropertyPath Path;`
- L30 _private member_ `INotifyHook* NotifyHook = nullptr;`
- L33 _private prototype_ `FString GetObjectPath() const;`
- L35 _private prototype_ `void OnObjectSelect(const FAssetData& InAsset);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SPropertyViewer.h` (Public)


#### class `UE::PropertyViewer::SPropertyViewer`  
`class SPropertyViewer : public SCompoundWidget`  
_L26-150_
- inherits: `SCompoundWidget`
- L29 _private typedef_ `using Super = SCompoundWidget;`
- L50 _public function_ `friend uint32 GetTypeHash(const FHandle& Other)`
- L71 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FGetFieldWidget, FHandle, TArrayView<const FFieldVariant>);`
- L72 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FOnContextMenuOpening, FHandle, TArrayView<const FFieldVariant>);`
- L73 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSelectionChanged, FHandle, TArrayView<const FFieldVariant>, ESelectInfo::Type);`
- L74 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnDoubleClicked, FHandle, TArrayView<const FFieldVariant>);`
- L75 _public prototype_ `DECLARE_DELEGATE_RetVal_FourParams(FReply, FOnDragDetected, const FGeometry&, const FPointerEvent&, FHandle, TArrayView<const FFieldVariant>);`
- L76 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateContainer, FHandle, TOptional<FText> DisplayName);`
- L78 _public function_ `SLATE_BEGIN_ARGS(SPropertyViewer)`
- L81 _public prototype_ `SLATE_ARGUMENT_DEFAULT(EPropertyVisibility, PropertyVisibility) = EPropertyVisibility::Hidden;` — Allow to edit the instance property.
- L83 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bSanitizeName) = false;` — Sanitize the field and container name.
- L85 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bShowFieldIcon) = true;` — Show the icon next to the field name.
- L87 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bSortChildNode) = false;` — Sort the field after building the list of fields.
- L89 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bShowSearchBox) = false;` — Show a search box.
- L91 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bFocusSearchBox) = false;` — Focus the search box when the widget is first displayed.
- L93 _public prototype_ `SLATE_ARGUMENT_DEFAULT(ESelectionMode::Type, SelectionMode) = ESelectionMode::Single;` — Is selection enabled.
- L95 _public prototype_ `SLATE_ARGUMENT_DEFAULT(IFieldIterator*, FieldIterator) = nullptr;` — Which properties/functions to show. FFieldIterator_BlueprintVisible is the default.
- L97 _public prototype_ `SLATE_ARGUMENT_DEFAULT(IFieldExpander*, FieldExpander) = nullptr;` — Which properties/functions that allow expansion. FFieldIterator_NoExpand is the default.
- L99 _public prototype_ `SLATE_ARGUMENT_DEFAULT(INotifyHook*, NotifyHook) = nullptr;` — Callback when a property is modified.
- L101 _public prototype_ `SLATE_ARGUMENT(TOptional<const FFieldColorSettings>, OverrideIconColorSettings);` — Override the color settings of the icons.
- L103 _public prototype_ `SLATE_NAMED_SLOT(FArguments, SearchBoxPreSlot) SLATE_NAMED_SLOT(FArguments, SearchBoxPostSlot) SLATE_EVENT(FGetFieldWidget, OnGetPreSlot) SLATE_EVENT(FGetFieldWidget, OnGetPostSlot) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnDoubleClicked, OnDoubleClicked);` — Slot for additional widget to go before the search box.
- L117 _public prototype_ `SLATE_EVENT(FOnGenerateContainer, OnGenerateContainer) SLATE_EVENT(FOnDragDetected, OnDragDetected);` — Delegate to invoke when we generate the entry for an added container.
- L120 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L123 _public prototype_ `void Construct(const FArguments& InArgs, const UScriptStruct* Struct);`
- L124 _public prototype_ `void Construct(const FArguments& InArgs, const UScriptStruct* Struct, void* Data);`
- L125 _public prototype_ `void Construct(const FArguments& InArgs, const UClass* Class);`
- L126 _public prototype_ `void Construct(const FArguments& InArgs, UObject* ObjectInstance);`
- L127 _public prototype_ `void Construct(const FArguments& InArgs, const UFunction* Function);`
- L129 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L132 _public prototype_ `FHandle AddContainer(const UScriptStruct* Struct, TOptional<FText> DisplayName = TOptional<FText>());`
- L133 _public prototype_ `FHandle AddContainer(const UClass* Class, TOptional<FText> DisplayName = TOptional<FText>());`
- L134 _public prototype_ `FHandle AddContainer(const UFunction* Function, TOptional<FText> DisplayName = TOptional<FText>());`
- L135 _public prototype_ `FHandle AddInstance(const UScriptStruct* Struct, void* Data, TOptional<FText> DisplayName = TOptional<FText>());`
- L136 _public prototype_ `FHandle AddInstance(UObject* ObjectInstance, TOptional<FText> DisplayName = TOptional<FText>());`
- L138 _public prototype_ `void Remove(FHandle Identifier);`
- L139 _public prototype_ `void RemoveAll();`
- L141 _public prototype_ `TArray<FSelectedItem> GetSelectedItems() const;`
- L143 _public prototype_ `void SetRawFilterText(const FText& InFilterText);`
- L144 _public prototype_ `void SetSelection(FHandle Container, TArrayView<const FFieldVariant> FieldPath);`
- L147 _private prototype_ `void ConstructInternal(const FArguments& InArgs);`
- L148 _private prototype_ `static FHandle MakeContainerIdentifier();`
- L149 _private member_ `TSharedPtr<Private::FPropertyViewerImpl> Implementation;`

#### class `UE::PropertyViewer::SPropertyViewer::FHandle`  
`class FHandle`  
_L32-54_
- L36 _private member_ `int32 Id = 0;`
- L38 _public function_ `bool operator==(FHandle Other) const`
- L42 _public function_ `bool operator!=(FHandle Other) const`
- L46 _public function_ `bool IsValid() const`

#### enum `UE::PropertyViewer::SPropertyViewer::EPropertyVisibility`  
`enum class EPropertyVisibility`  
_L56-61_
- L58 _public enumerator_ `Hidden`
- L59 _public enumerator_ `Visible`
- L60 _public enumerator_ `Editable`

#### struct `UE::PropertyViewer::SPropertyViewer::FSelectedItem`  
`struct FSelectedItem`  
_L63-68_
- L65 _public member_ `FHandle Handle;`
- L66 _public member_ `TArray<TArray<FFieldVariant>> Fields;`
- L67 _public member_ `bool bIsContainerSelected = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PropertyViewer` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::PropertyViewer`)
- L71 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FGetFieldWidget, FHandle, TArrayView<const FFieldVariant>);`
- L72 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FOnContextMenuOpening, FHandle, TArrayView<const FFieldVariant>);`
- L73 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSelectionChanged, FHandle, TArrayView<const FFieldVariant>, ESelectInfo::Type);`
- L74 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDoubleClicked, FHandle, TArrayView<const FFieldVariant>);`
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(FReply, FOnDragDetected, const FGeometry&, const FPointerEvent&, FHandle, TArrayView<const FFieldVariant>);`
- L76 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateContainer, FHandle, TOptional<FText> DisplayName);`

### `Source/Runtime/AdvancedWidgets/Public/Widgets/PropertyViewer/SStringPropertyValue.h` (Public)


#### class `UE::PropertyViewer::SStringPropertyValue`  
`class SStringPropertyValue : public SCompoundWidget`  
_L16-35_
- inherits: `SCompoundWidget`
- L19 _public prototype_ `static TSharedPtr<SWidget> CreateInstance(const FPropertyValueFactory::FGenerateArgs Args);`
- L22 _public function_ `SLATE_BEGIN_ARGS(SStringPropertyValue)`
- L23 _public prototype_ `SLATE_ARGUMENT(FPropertyPath, Path);`
- L24 _public prototype_ `SLATE_ARGUMENT(INotifyHook*, NotifyHook);`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `FText GetText() const;`
- L31 _private prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L33 _private member_ `FPropertyPath Path;`
- L34 _private member_ `INotifyHook* NotifyHook = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PropertyViewer` (scope `UE`)

### `Source/Runtime/AdvancedWidgets/Public/Widgets/SRadialSlider.h` (Public)


#### class `SRadialSlider`  
`class SRadialSlider : public SLeafWidget`  
_L25-432_
- inherits: `SLeafWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SRadialSlider) : _MouseUsesStep(false) , _RequiresControllerLock(true) , _Locked(false) , _SliderBarColor(FLinearColor::Gray) , _SliderProgressColor(FLinearColor::White) , _SliderHandleColor(FLinearColor::White) , _CenterBackgroundColor(FLinearColor::Transparent) , _CenterBackgroundBrush(FSlateRoundedBoxBrush(FStyleColors::Transparent, FVector2D(90.0f, 90.0f)))`
- L59 _public prototype_ `SLATE_ARGUMENT(bool, MouseUsesStep) SLATE_ARGUMENT(bool, RequiresControllerLock) SLATE_ATTRIBUTE(bool, Locked) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, SliderProgressColor) SLATE_ATTRIBUTE(FSlateColor, SliderHandleColor) SLATE_ATTRIBUTE(FSlateColor, CenterBackgroundColor) SLATE_ATTRIBUTE(float, Thickness) SLATE_ARGUMENT(FSlateBrush, CenterBackgroundBrush) SLATE_STYLE_ARGUMENT(FSliderStyle, Style ) SLATE_ATTRIBUTE(float, StepSize) SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE(bool, bUseCustomDefaultValue) SLATE_ATTRIBUTE(float, CustomDefaultValue)` — Sets new value if mouse position is greater/less than half the step size.
- L148 _public prototype_ `virtual ~SRadialSlider();`
- L155 _public prototype_ `void Construct( const SRadialSlider::FArguments& InDeclaration );` — Construct the widget. @param InDeclaration A declaration from which to construct the widget.
- L158 _public function_ `FRuntimeFloatCurve GetSliderRange() const` — Get the SliderRange attribute
- L161 _public prototype_ `float GetMinValue() const;` — Get the minumum value in Slider Range
- L164 _public prototype_ `float GetMaxValue() const;` — Get the maximum value in Slider Range
- L167 _public function_ `float GetSliderHandleStartAngle() const` — Get the MinSliderHandleAngle attribute
- L170 _public function_ `float GetSliderHandleEndAngle() const` — Get the MaxSliderHandleAngle attribute
- L173 _public function_ `float GetAngularOffset() const` — Get the AngularOffset attribute
- L176 _public function_ `TArray<float> GetValueTags() const` — Get the ValueTags attribute
- L179 _public prototype_ `float GetValue() const;` — Get the Value attribute
- L182 _public prototype_ `bool GetUseCustomDefaultValue() const;` — Get the bUseCustomDefaultValue attribute
- L185 _public prototype_ `float GetCustomDefaultValue() const;` — Get ths CustomDefaultValue attribute
- L188 _public prototype_ `float GetNormalizedValue(float RawValue) const;` — Get the Value attribute scaled from 0 to 1
- L191 _public prototype_ `float GetNormalizedSliderHandlePosition() const;` — Get the Slider's Handle position scaled from 0 to 1
- L194 _public prototype_ `void SetValue(const TAttribute<float>& InValueAttribute);` — Set the Value attribute
- L197 _public prototype_ `void SetUseCustomDefaultValue(const TAttribute<bool>& InValueAttribute);` — Set the bUseCustomDefaultValue attribute
- L200 _public prototype_ `void SetCustomDefaultValue(const TAttribute<float>& InValueAttribute);` — Set the CustomDefaultValue attribute
- L203 _public function_ `void SetSliderRange(const FRuntimeFloatCurve& InSliderRange)` — Set the SliderRange attribute
- L206 _public prototype_ `void SetSliderHandleStartAngleAndSliderHandleEndAngle(float InSliderHandleStartAngle, float InSliderHandleEndAngle);` — Set the SliderHandleStartAngle and SliderHandleEndAngle attributes. If the new SliderHandleStartAngle is more than the new SliderHandleEndAngle, SliderHandleEndAngle will be changed to equal SliderHandleStartAngle.
- L209 _public function_ `void SetAngularOffset(float InAngularOffset)` — Set the AngularOffset attribute
- L212 _public prototype_ `void SetHandStartEndRatio(FVector2D InHandStartEndRatio);` — Set the HandStartEndRatio. Clamped to 0.0 to 1.0, and if the start ratio is more than the end ratio, end ratio will be set to the start ratio.
- L215 _public function_ `void SetValueTags(const TArray<float>& InValueTags)` — Set the ValueTags attribute
- L218 _public prototype_ `void SetLocked(const TAttribute<bool>& InLocked);` — Set the Locked attribute
- L221 _public prototype_ `void SetSliderBarColor(FSlateColor InSliderBarColor);` — Set the SliderBarColor attribute
- L224 _public prototype_ `void SetSliderProgressColor(FSlateColor InSliderProgressColor);` — Set the SliderProgressColor attribute
- L227 _public prototype_ `void SetSliderHandleColor(FSlateColor InSliderHandleColor);` — Set the SliderHandleColor attribute
- L230 _public prototype_ `void SetCenterBackgroundColor(FSlateColor InCenterHandleColor);` — Set the SliderHandleColor attribute
- L233 _public prototype_ `void SetThickness(const float InThickness);` — Set the Thickness attribute. For backward compatibility, Thickness will be used for drawing instead of Style->BarThickness only if it has been set with this method,
- L236 _public prototype_ `float GetStepSize() const;` — Get the StepSize attribute
- L239 _public prototype_ `void SetStepSize(const TAttribute<float>& InStepSize);` — Set the StepSize attribute
- L242 _public prototype_ `void SetMouseUsesStep(bool MouseUsesStep);` — Set the MouseUsesStep attribute
- L245 _public prototype_ `void SetRequiresControllerLock(bool RequiresControllerLock);` — Set the RequiresControllerLock attribute
- L248 _public prototype_ `void SetUseVerticalDrag(bool UseVerticalDrag);` — Set the UseVerticalDrag attribute
- L251 _public prototype_ `void SetShowSliderHandle(bool ShowSliderHandle);` — Set the ShowSliderHandle attribute
- L254 _public prototype_ `void SetShowSliderHand(bool ShowSliderHand);` — Set the ShowSliderHand attribute
- L260 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L261 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L262 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L263 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L264 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L265 _public prototype_ `virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L266 _public prototype_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L267 _public prototype_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L268 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L269 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L270 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L271 _public prototype_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;`
- L273 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L274 _public prototype_ `virtual bool IsInteractable() const override;`
- L276 _public prototype_ `virtual TSharedRef<FSlateAccessibleWidget> CreateAccessibleWidget() override;`
- L280 _public prototype_ `bool IsLocked() const;` — @return Is the handle locked or not? Defaults to false
- L289 _protected prototype_ `virtual void CommitValue(float NewValue);` — Commits the specified slider value. @param NewValue The value to commit.
- L298 _protected prototype_ `float PositionToValue(const FGeometry& MyGeometry, const FVector2D& AbsolutePosition);` — Calculates the new value based on the given absolute coordinates. @param MyGeometry The slider's geometry. @param AbsolutePosition The absolute position of the slider. @return The new value.
- L300 _protected prototype_ `const FSlateBrush* GetBarImage() const;`
- L301 _protected prototype_ `const FSlateBrush* GetThumbImage() const;`
- L306 _protected member_ `const FSliderStyle* Style;` — Holds the style passed to the widget upon construction.
- L309 _protected member_ `TAttribute<bool> LockedAttribute;` — Holds a flag indicating whether the slider is locked.
- L312 _protected member_ `TAttribute<FSlateColor> SliderBarColor;` — Holds the color of the slider bar.
- L315 _protected member_ `TAttribute<FSlateColor> SliderProgressColor;` — Holds the color for the completed progress of the slider bar.
- L318 _protected member_ `TAttribute<FSlateColor> SliderHandleColor;` — Holds the color of the slider handle.
- L321 _protected member_ `TAttribute<FSlateColor> CenterBackgroundColor;` — Holds the color of the center background.
- L324 _protected member_ `FSlateBrush CenterBackgroundBrush;` — Center background image brush
- L327 _protected member_ `TAttribute<TOptional<float>> Thickness;` — Thickness used for slider bar instead of Style->BarThickness (see SetThickness)
- L330 _protected member_ `TAttribute<float> ValueAttribute;` — Holds the slider's current value.
- L333 _protected member_ `TAttribute<bool> bUseCustomDefaultValue;` — Whether the slider should draw it's progress bar from a custom value on the slider
- L336 _protected member_ `TAttribute<float> CustomDefaultValue;` — The value where the slider should draw it's progress bar from, independent of direction
- L339 _protected member_ `EMouseCursor::Type CachedCursor;` — Holds the initial cursor in case a custom cursor has been specified, so we can restore it after dragging the slider
- L342 _protected member_ `FVector2D PressedScreenSpaceTouchDownPosition = FVector2D(0, 0);` — The location in screenspace the slider was pressed by a touch
- L345 _protected member_ `TAttribute<float> StepSize;` — Holds the amount to adjust the value by when using a controller or keyboard
- L348 _protected member_ `float SliderHandleStartAngle;` — The angle at which the radial slider should begin
- L351 _protected member_ `float SliderHandleEndAngle;` — The angle at which the radial slider should end
- L354 _protected member_ `float AngularOffset;` — The angle at which the radial slider should be offset by
- L357 _protected member_ `FVector2D HandStartEndRatio;` — Start and end of the hand as a ratio to the slider radius (so 0.0 to 1.0 is from the slider center to the handle).
- L360 _protected member_ `TArray<float> ValueTags;` — The values that should be drawn around the radial slider
- L363 _protected member_ `FRuntimeFloatCurve SliderRange;` — A curve that defines how the slider should be sampled. Default is linear.
- L367 _protected member_ `bool bControllerInputCaptured;` — Holds a flag indicating whether a controller/keyboard is manipulating the slider's value. When true, navigation away from the widget is prevented until a new value has been accepted or canceled.
- L370 _protected member_ `bool bMouseUsesStep;` — Sets new value if mouse position is greater/less than half the step size.
- L373 _protected member_ `bool bRequiresControllerLock;` — Sets whether we have to lock input to change the slider value.
- L376 _protected member_ `bool bIsFocusable;` — When true, this slider will be keyboard focusable. Defaults to false.
- L379 _protected member_ `bool bUseVerticalDrag;` — When true, value is changed when dragging vertically as opposed to along the radial curve.
- L382 _protected member_ `bool bShowSliderHandle;` — Whether to show the slider handle (thumb).
- L385 _protected member_ `bool bShowSliderHand;` — Whether to show the slider hand.
- L390 _private prototype_ `void ResetControllerState();` — Resets controller input state. Fires delegates.
- L393 _private prototype_ `float GetAngleFromPosition(const FGeometry& MyGeometry, const FVector2D& AbsolutePosition);` — Helper function to convert Absolute Position to Angle
- L396 _private prototype_ `void OnInputStarted(const FGeometry& MyGeometry, const FVector2D& InputAbsolutePosition);` — Called on Mouse / Touch input to cache relevant properties
- L399 _private prototype_ `void AddSliderPointToArray(TArray<FVector2D>& SliderPoints, const bool bIsUnique, const FVector2D& SliderPoint) const;` — Helper function for adding slider points to a slider points array
- L402 _private member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L405 _private member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when the mouse is let up and a capture ends.
- L408 _private member_ `FSimpleDelegate OnControllerCaptureBegin;` — Holds a delegate that is executed when capture begins for controller or keyboard.
- L411 _private member_ `FSimpleDelegate OnControllerCaptureEnd;` — Holds a delegate that is executed when capture ends for controller or keyboard.
- L414 _private member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the slider's value changed.
- L417 _private member_ `float AbsoluteInputAngle;` — Holds the current interaction's unclamped input angle.
- L420 _private member_ `FVector2D PreviousAbsolutePosition;` — Stores the previous absolute position to support calculating rotational delta for relative input
- L424 _private member_ `bool bIsUsingFineTune;` — Settings for behavior when IsUsingVerticalDrag is true For when UseVerticalDrag is true, whether we're fine tuning the value
- L427 _private member_ `FKey FineTuneKey;` — The key to use when fine tuning vertical drag
- L429 _private member_ `float VerticalDragMouseSpeedNormal = 0.2f;`
- L430 _private member_ `float VerticalDragMouseSpeedFineTune = 0.05f;`
- L431 _private member_ `float VerticalDragPixelDelta = 50.0f;`
