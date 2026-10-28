# Plugins / CommonUI

- module root: `Plugins/Runtime/CommonUI/Source/CommonUI`
- headers: 73; symbols: 2521
- symbol kinds: class=88, delegate=76, enum=20, enumerator=74, externvar=3, function=256, macro=61, member=695, namespace=4, prototype=1205, struct=27, typedef=11, variable=1
- PrivateDependencyModuleNames: Analytics, AnalyticsET, AudioMixer, DeveloperSettings, EngineSettings, SlateCore
- PublicDependencyModuleNames: ApplicationCore, CommonInput, Core, CoreUObject, EditorFramework, Engine, EnhancedInput, GameplayTags, InputCore, MediaAssets, Slate, UMG, UnrealEd, WidgetCarousel

### `Plugins/Runtime/CommonUI/Source/CommonUI/Private/CommonButtonTypes.h` (Private)


#### class `SCommonButton`  
`class SCommonButton : public SButton`  
_L17-137_
- inherits: `SButton`
- desc: Lets us disable clicking on a button without disabling hit-testing Needed because NativeOnMouseEnter is not received by disabled widgets, but that also disables our anchored tooltips.
- L20 _public function_ `SLATE_BEGIN_ARGS(SCommonButton) : _Content() , _HAlign(HAlign_Fill) , _VAlign(VAlign_Fill) , _OnSlateButtonDragDetected() , _OnSlateButtonDragEnter() , _OnSlateButtonDragLeave() , _OnSlateButtonDragOver() , _OnSlateButtonDrop() , _ClickMethod(EButtonClickMethod::DownAndUp) , _TouchMethod(EButtonTouchMethod::DownAndUp) , _PressMethod(EButtonPressMethod::DownAndUp) , _IsFocusable(true) , _IsInteractionEnabled(true)`
- L35 _public function_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_ARGUMENT(EHorizontalAlignment, HAlign) SLATE_ARGUMENT(EVerticalAlignment, VAlign) SLATE_EVENT(FOnDragDetected, OnSlateButtonDragDetected) SLATE_EVENT(FOnDragEnter, OnSlateButtonDragEnter) SLATE_EVENT(FOnDragLeave, OnSlateButtonDragLeave) SLATE_EVENT(FOnDragOver, OnSlateButtonDragOver) SLATE_EVENT(FOnDrop, OnSlateButtonDrop) SLATE_EVENT(FOnClicked, OnClicked) SLATE_EVENT(FOnClicked, OnDoubleClicked) SLATE_EVENT(FSimpleDelegate, OnPressed) SLATE_EVENT(FSimpleDelegate, OnReleased) SLATE_ARGUMENT(EButtonClickMethod::Type, ClickMethod) SLATE_ARGUMENT(EButtonTouchMethod::Type, TouchMethod) SLATE_ARGUMENT(EButtonPressMethod::Type, PressMethod) SLATE_ARGUMENT(bool, IsFocusable) SLATE_EVENT(FSimpleDelegate, OnReceivedFocus) SLATE_EVENT(FSimpleDelegate, OnLostFocus) SLATE_ARGUMENT(bool, IsButtonEnabled) SLATE_ARGUMENT(bool, IsInteractionEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L96 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L98 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L100 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L102 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L104 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L106 _public prototype_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L108 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L110 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L112 _public prototype_ `void SetIsButtonEnabled(bool bInIsButtonEnabled);`
- L114 _public prototype_ `void SetIsButtonFocusable(bool bInIsButtonFocusable);`
- L116 _public prototype_ `void SetIsInteractionEnabled(bool bInIsInteractionEnabled);`
- L118 _public prototype_ `bool IsInteractable() const;`
- L120 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L124 _protected prototype_ `virtual void Press() override;` — Press the button
- L127 _private member_ `FOnClicked OnDoubleClicked;`
- L130 _private member_ `bool bIsButtonEnabled;` — True if the button is enabled
- L133 _private member_ `bool bIsInteractionEnabled;` — True if clicking is enabled, to allow for things like double click
- L136 _private member_ `bool bHovered;` — True if mouse over the widget

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Private/CommonCustomVersion.h` (Private)


#### struct `FCommonCustomVersion`  
`struct FCommonCustomVersion`  
_L9-29_
- desc: Custom serialization version for all packages containing CommonUI asset types
- L25 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L28 _private function_ `FCommonCustomVersion()`

#### enum `FCommonCustomVersion::Type`  
`enum Type`  
_L11-22_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `RemovingIsPercentage = 1` — Removing IsPercentage from the Common Numeric Text block in favor of an enum we can further extend.
- L20 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L21 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Private/CommonUIObjectVersion.h` (Private)


#### enum `ECommonUIObjectVersion::Type`  
`enum Type`  
_L9-19_
- L11 _public enumerator_ `Initial = 0`
- L14 _public enumerator_ `CreatedLoadGuardSlot` — Updated the UCommonUILoadGuard to expose its content in a ULoadGuardSlot
- L17 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ECommonUIObjectVersion`
- L22 _externvar_ `const extern FGuid Guid;` (scope `ECommonUIObjectVersion`) — The GUID for this custom version number

### `Plugins/Runtime/CommonUI/Source/CommonUI/Private/CommonUIPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommonUI, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommonUI, Log, All);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Private/CommonWidgetPaletteCategories.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace CommonWidgetPaletteCategories`
- L10 _variable_ `const FText Default = NSLOCTEXT("CommonUI",` (scope `CommonWidgetPaletteCategories`)

### `Plugins/Runtime/CommonUI/Source/CommonUI/Private/Input/UIActionRouterTypes.h` (Private)


#### class `FActionRouterBindingCollection`  
`class FActionRouterBindingCollection : public TSharedFromThis<FActionRouterBindingCollection>`  
_L48-90_
- inherits: `TSharedFromThis<FActionRouterBindingCollection>`
- L51 _public prototype_ `virtual ~FActionRouterBindingCollection() = default;`
- L53 _public prototype_ `virtual EProcessHoldActionResult ProcessHoldInput(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent, int32 UserIndex) const;`
- L54 _public prototype_ `virtual bool ProcessNormalInput(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent, int32 UserIndex) const;`
- L55 _public function_ `virtual bool IsReceivingInput() const`
- L57 _public prototype_ `void AddBinding(FUIActionBinding& Binding);`
- L59 _public prototype_ `void RemoveBindings(const TArray<FUIActionBindingHandle>& WidgetBindings);`
- L60 _public prototype_ `void RemoveBinding(FUIActionBindingHandle ActionHandle);`
- L62 _public function_ `bool HasHoldBindings() const`
- L64 _public function_ `const TArray<FUIActionBindingHandle>& GetActionBindings() const`
- L67 _protected prototype_ `FActionRouterBindingCollection(UCommonUIActionRouterBase& OwningRouter);`
- L68 _protected prototype_ `virtual bool IsWidgetReachableForInput(const UWidget* Widget) const;`
- L70 _protected prototype_ `int32 GetOwnerUserIndex() const;`
- L71 _protected prototype_ `int32 GetOwnerControllerId() const;`
- L72 _protected function_ `UCommonUIActionRouterBase& GetActionRouter() const`
- L74 _protected prototype_ `void DebugDumpActionBindings(FString& OutputStr, int32 IndentSpaces) const;`
- L77 _protected member_ `TArray<FUIActionBindingHandle> ActionBindings;` — The set of action bindings contained within this collection
- L83 _protected member_ `TWeakObjectPtr<UCommonUIActionRouterBase> ActionRouterPtr;` — Treat this as guaranteed to be valid and access via GetActionRouter() Only kept as a WeakObjectPtr so we can reliably assert in the case it somehow becomes invalid.
- L87 _private member_ `mutable FUIActionBindingHandle CurrentlyHeldBinding;` — Slate application sends repeat actions only for the last pressed key, so we have to keep track of this last held binding and clear it when we get a new key to hold
- L89 _private member_ `int32 HoldBindingsCount = 0;`

#### class `FActivatableTreeNode`  
`class FActivatableTreeNode : public FActionRouterBindingCollection`  
_L96-183_
- inherits: `FActionRouterBindingCollection`
- L99 _public prototype_ `virtual ~FActivatableTreeNode();`
- L101 _public prototype_ `virtual EProcessHoldActionResult ProcessHoldInput(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent, int32 UserIndex) const override;`
- L102 _public prototype_ `virtual bool ProcessNormalInput(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent, int32 UserIndex) const override;`
- L103 _public function_ `virtual bool IsReceivingInput() const override`
- L105 _public prototype_ `bool IsWidgetValid() const;`
- L106 _public prototype_ `bool IsWidgetActivated() const;`
- L107 _public prototype_ `bool DoesWidgetSupportActivationFocus() const;`
- L108 _public prototype_ `void AppendAllActiveActions(TArray<FUIActionBindingHandle>& BoundActions) const;`
- L110 _public function_ `UCommonActivatableWidget* GetWidget()`
- L111 _public function_ `const UCommonActivatableWidget* GetWidget() const`
- L113 _public function_ `TArray<FActivatableTreeNodeRef>& GetChildren()`
- L114 _public function_ `const TArray<FActivatableTreeNodeRef>& GetChildren() const`
- L116 _public function_ `FActivatableTreeNodePtr GetParentNode() const`
- L118 _public prototype_ `FActivatableTreeNodeRef AddChildNode(UCommonActivatableWidget& InActivatableWidget);`
- L119 _public prototype_ `void CacheFocusRestorationTarget();`
- L120 _public function_ `void ClearFocusRestorationTarget()`
- L121 _public prototype_ `TSharedPtr<SWidget> GetFocusFallbackTarget() const;`
- L123 _public prototype_ `bool IsExclusiveParentOfWidget(const TSharedPtr<SWidget>& SlateWidget) const;`
- L129 _public prototype_ `bool IsParentOfWidget(const TSharedPtr<SWidget>& SlateWidget, EIsParentSearchType ParentSearchType) const;`
- L131 _public prototype_ `int32 GetLastPaintLayer() const;`
- L132 _public prototype_ `TOptional<FUIInputConfig> FindDesiredInputConfig() const;`
- L133 _public prototype_ `TOptional<FUIInputConfig> FindDesiredActionDomainInputConfig() const;`
- L134 _public prototype_ `FActivationMetadata FindActivationMetadata() const;`
- L136 _public prototype_ `void SetCanReceiveInput(bool bInCanReceiveInput);`
- L138 _public prototype_ `void AddScrollRecipient(const UWidget& ScrollRecipient);`
- L139 _public prototype_ `void RemoveScrollRecipient(const UWidget& ScrollRecipient);`
- L140 _public prototype_ `void AddInputPreprocessor(const TSharedRef<IInputProcessor>& InputPreprocessor, const FInputPreprocessorRegistrationKey& RegistrationInfo);`
- L142 _public member_ `FSimpleDelegate OnActivated;`
- L143 _public member_ `FSimpleDelegate OnDeactivated;`
- L146 _protected prototype_ `FActivatableTreeNode(UCommonUIActionRouterBase& OwningRouter, UCommonActivatableWidget& ActivatableWidget);`
- L147 _protected prototype_ `FActivatableTreeNode(UCommonUIActionRouterBase& OwningRouter, UCommonActivatableWidget& ActivatableWidget, const FActivatableTreeNodeRef& InParent);`
- L149 _protected prototype_ `virtual bool IsWidgetReachableForInput(const UWidget* Widget) const override;`
- L151 _protected function_ `bool CanReceiveInput() const`
- L152 _protected prototype_ `virtual void Init();`
- L153 _protected prototype_ `FActivatableTreeRootRef GetRoot() const;`
- L155 _protected prototype_ `void AppendValidScrollRecipients(TArray<const UWidget*>& AllScrollRecipients) const;`
- L156 _protected prototype_ `void DebugDumpRecursive(FString& OutputStr, int32 Depth, bool bIncludeActions, bool bIncludeChildren, bool bIncludeInactive) const;`
- L159 _private prototype_ `void HandleWidgetActivated();`
- L160 _private prototype_ `void HandleWidgetDeactivated();`
- L161 _private prototype_ `void HandleChildSlateReleased(UCommonActivatableWidget* ChildWidget);`
- L163 _private prototype_ `void RegisterPreprocessors();`
- L164 _private prototype_ `void UnregisterPreprocessors();`
- L166 _private prototype_ `bool DoesPathSupportActivationFocus() const;`
- L169 _private member_ `FString DebugWidgetName;`
- L172 _private member_ `TWeakObjectPtr<UCommonActivatableWidget> RepresentedWidget;`
- L173 _private member_ `TWeakPtr<FActivatableTreeNode> Parent;`
- L174 _private member_ `TArray<FActivatableTreeNodeRef> Children;`
- L175 _private member_ `TWeakPtr<SWidget> FocusRestorationTarget;`
- L177 _private member_ `bool bCanReceiveInput = false;`
- L179 _private member_ `TArray<FInputPreprocessorRegistration> RegisteredPreprocessors;`
- L182 _private member_ `mutable TArray<TWeakObjectPtr<const UWidget>> ScrollRecipients;` — Mutable so we can keep it clean during normal use

#### enum `FActivatableTreeNode::EIsParentSearchType`  
`enum EIsParentSearchType`  
_L124-128_
- L126 _public enumerator_ `ExcludeSelf`
- L127 _public enumerator_ `IncludeSelf`

#### class `FActivatableTreeRoot`  
`class FActivatableTreeRoot : public FActivatableTreeNode`  
_L189-233_
- inherits: `FActivatableTreeNode`
- L192 _public prototype_ `static FActivatableTreeRootRef Create(UCommonUIActionRouterBase& OwningRouter, UCommonActivatableWidget& ActivatableWidget);`
- L194 _public prototype_ `void UpdateLeafNode();`
- L196 _public prototype_ `TArray<const UWidget*> GatherScrollRecipients() const;`
- L198 _public prototype_ `bool UpdateLeafmostActiveNode(FActivatableTreeNodePtr BaseCandidateNode, bool bInApplyConfig = true);`
- L200 _public prototype_ `void DebugDump(FString& OutputStr, bool bIncludeActions, bool bIncludeChildren, bool bIncludeInactive) const;`
- L202 _public member_ `FSimpleDelegate OnLeafmostActiveNodeChanged;`
- L204 _public prototype_ `void FocusLeafmostNode();`
- L206 _public prototype_ `void RefreshCachedRestorationTarget();`
- L208 _public prototype_ `void ApplyLeafmostNodeConfig(bool bAttemptRetainFocus = false);`
- L210 _public prototype_ `bool IsAnActionDomainRoot() const;`
- L211 _public prototype_ `bool IsActiveActionDomainRoot() const;`
- L212 _public prototype_ `bool CanSetInputConfigAndFocus() const;`
- L213 _public prototype_ `bool IsWidgetInLeafmostNodeHierarchy(const UWidget& Widget) const;`
- L215 _public prototype_ `UCommonActivatableWidget* GetLeafmostActivatableWidget() const;`
- L218 _protected prototype_ `virtual void Init() override;`
- L221 _private function_ `FActivatableTreeRoot(UCommonUIActionRouterBase& OwningRouter, UCommonActivatableWidget& ActivatableWidget) : FActivatableTreeNode(OwningRouter, ActivatableWidget)`
- L225 _private prototype_ `void HandleInputMethodChanged(ECommonInputType InputMethod);`
- L227 _private prototype_ `void HandleRequestRefreshLeafmostFocus();`
- L229 _private prototype_ `bool GamepadFocusHoveredWidget();`
- L232 _private member_ `TWeakPtr<FActivatableTreeNode> LeafmostActiveNode;` — WeakPtr because the root itself can be the primary active node - results in a circular ref leak using a full SharedPtr here

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L33 _typedef_ `using FActivatableTreeNodePtr = TSharedPtr<FActivatableTreeNode>;`
- L34 _typedef_ `using FActivatableTreeNodeRef = TSharedRef<FActivatableTreeNode>;`
- L37 _typedef_ `using FActivatableTreeRootPtr = TSharedPtr<FActivatableTreeRoot>;`
- L38 _typedef_ `using FActivatableTreeRootRef = TSharedRef<FActivatableTreeRoot>;`
- L42 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUIActionRouter, Log, All);`
- L42 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUIActionRouter, Log, All);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/AnalogSlider.h` (Public)


#### class `UAnalogSlider`  
`class UAnalogSlider : public USlider`  
_L22-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USlider`
- desc: A simple widget that shows a sliding bar with a handle that allows you to control the value in a user define range (between 0..1 by default). * No Children
- L29 _public member_ `FOnFloatValueChangedEvent OnAnalogCapture;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when the value is changed by slider or typing.
- L32 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L35 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L36 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L38 _public prototype_ `void HandleOnAnalogCapture(float InValue);`
- L40 _public prototype_ `void HandleInputMethodChanged(ECommonInputType CurrentInputType);`
- L43 _protected member_ `TSharedPtr<SAnalogSlider> MyAnalogSlider;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonActionHandlerInterface.h` (Public)


#### struct `FCommonInputActionHandlerData`  
`struct FCommonInputActionHandlerData`  
_L48-86_
- reflection: `USTRUCT(BlueprintType)`
- desc: @FIXME: This struct is related to legacy CommonUI and should be removed in 5.3 - UE-164871
- L52 _public function_ `FCommonInputActionHandlerData() : State(EInputActionState::Enabled)`
- L57 _public function_ `FCommonInputActionHandlerData(const FDataTableRowHandle& InInputActionRow) : InputActionRow(InInputActionRow) , State(EInputActionState::Enabled)`
- L63 _public function_ `FCommonInputActionHandlerData(const FDataTableRowHandle& InInputActionRow, UWidget* InPopupMenu) : InputActionRow(InInputActionRow) , State(EInputActionState::Enabled) , PopupMenu(InPopupMenu)`
- L71 _public member_ `FDataTableRowHandle InputActionRow;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)`
- L73 _public prototype_ `EInputActionState GetState(ECommonInputType InputType, const FName& GamepadName) const;`
- L74 _public function_ `void SetState(EInputActionState InState)`
- L79 _public function_ `TWeakObjectPtr<UWidget> GetPopupMenu() const`
- L83 _private member_ `EInputActionState State;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L85 _private member_ `TWeakObjectPtr<UWidget> PopupMenu;`

#### struct `FCommonInputActionHandlerDelegateData`  
`struct FCommonInputActionHandlerDelegateData`  
_L92-113_
- desc: Action Handle Data used to trigger any callbacks by an object implementing the ICommonActionHandlerInterface. For use with native delegates
- L94 _public member_ `FCommonActionProgressNative OnActionProgress;`
- L95 _public member_ `FCommonActionCommittedNative OnActionCommitted;`
- L96 _public member_ `FCommonActionCompleteNative OnActionComplete;`
- L98 _public member_ `FCommonActionCommittedNative OnDisabledActionCommited;`
- L100 _public member_ `FCommonInputActionHandlerData Data;`
- L102 _public function_ `FCommonInputActionHandlerDelegateData()`
- L106 _public function_ `FCommonInputActionHandlerDelegateData(const FDataTableRowHandle& InInputActionRow, const FCommonActionProgressSingleNative& ActivationProgressDelegate, const FCommonActionCommittedNative& ActivationCommittedDelegate, UWidget* PopupMenu) : OnActionCommitted(ActivationCommittedDelegate) , Data(InInputActionRow, PopupMenu)`

#### class `UCommonActionHandlerInterface`  
`class UCommonActionHandlerInterface : public UInterface`  
_L123-126_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICommonActionHandlerInterface`  
`class ICommonActionHandlerInterface`  
_L129-148_
- L135 _public prototype_ `virtual bool HandleHoldInput(int32 ControllerId, FKey KeyPressed, EInputEvent EventType, bool& bPassThrough) = 0;` — The common input manager calls this for any object implementing this interface
- L136 _public prototype_ `virtual bool HandlePressInput(FKey KeyPressed, EInputEvent EventType, bool& bPassThrough) = 0;`
- L137 _public prototype_ `virtual bool HandleTouchInput(uint32 TouchId, ETouchType::Type TouchType, const FVector2D& TouchLocation, bool& bPassThrough) = 0;`
- L140 _public prototype_ `virtual void UpdateCurrentlyHeldAction(float InDeltaTime) = 0;` — When an action progress happens for a held key, this will be called
- L147 _public prototype_ `virtual void TriggerFirstMatchingInputAction(int32 ControllerId, const FCommonInputActionDataBase& InInputActionData, bool bHoldAction) = 0;` — This will trigger the first input action based on input action data and the hold action flag @param Key the key to use for triggering the first matching input action @param bHoldAction if true, we're looking for a hold action specifically.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`
- L16 _namespace_ `namespace ETouchType`
- L25 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCommonActionCommited, bool&, bPassThrough);` — Action committed delegate tells the handler that an action is ready to handle. Return value is used to determine if the action was handled or ignored.
- L25 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCommonActionCommited, bool&, bPassThrough);` — Action committed delegate tells the handler that an action is ready to handle. Return value is used to determine if the action was handled or ignored.
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FCommonActionCommittedNative, bool&);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FCommonActionCommittedNative, bool&);`
- L32 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FCommonActionCompleteSingle);` — Action complete delegate will tell a listener if a held action completed. The single delegate will be used for binding with a listener that the multicast delegate calls.
- L32 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FCommonActionCompleteSingle);` — Action complete delegate will tell a listener if a held action completed. The single delegate will be used for binding with a listener that the multicast delegate calls.
- L33 _delegate_ `DECLARE_DELEGATE(FCommonActionCompleteSingleNative);`
- L33 _prototype_ `DECLARE_DELEGATE(FCommonActionCompleteSingleNative);`
- L34 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCommonActionComplete);`
- L34 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCommonActionComplete);`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE(FCommonActionCompleteNative);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE(FCommonActionCompleteNative);`
- L41 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCommonActionProgressSingle, float, HeldPercent);` — Action progress delegate will tell a listener about the progress of an action being held. The single delegate will be used for binding with a listener that the multicast delegate calls.
- L41 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCommonActionProgressSingle, float, HeldPercent);` — Action progress delegate will tell a listener about the progress of an action being held. The single delegate will be used for binding with a listener that the multicast delegate calls.
- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FCommonActionProgressSingleNative, float);`
- L42 _prototype_ `DECLARE_DELEGATE_OneParam(FCommonActionProgressSingleNative, float);`
- L43 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonActionProgress, float, HeldPercent);`
- L43 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonActionProgress, float, HeldPercent);`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FCommonActionProgressNative, float);`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FCommonActionProgressNative, float);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonActionWidget.h` (Public)


#### class `UCommonActionWidget`  
`class UCommonActionWidget: public UWidget`  
_L25-160_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UWidget`
- desc: A widget that shows a platform-specific icon for the given input action.
- L32 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L36 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — Begin UWidget
- L37 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L38 _public prototype_ `virtual void SynchronizeProperties() override;`
- L42 _public prototype_ `virtual FSlateBrush GetIcon() const;` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L45 _public prototype_ `FText GetDisplayText() const;` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L48 _public prototype_ `UMaterialInstanceDynamic* GetIconDynamicMaterial();` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L51 _public prototype_ `virtual void SetEnhancedInputAction(UInputAction* InInputAction);` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L54 _public prototype_ `const UInputAction* GetEnhancedInputAction() const;` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L57 _public prototype_ `virtual void SetInputAction(FDataTableRowHandle InputActionRow);` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L60 _public prototype_ `virtual void SetInputActionBinding(FUIActionBindingHandle BindingHandle);` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L63 _public prototype_ `virtual void SetInputActions(TArray<FDataTableRowHandle> NewInputActions);` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L66 _public prototype_ `void SetIconRimBrush(FSlateBrush InIconRimBrush);` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L69 _public prototype_ `virtual bool IsHeldAction() const;` — `UFUNCTION(BlueprintCallable, Category = CommonActionWidget)`
- L71 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMethodChanged, bool, bUsingGamepad);`
- L73 _public member_ `FOnInputMethodChanged OnInputMethodChanged;` — `UPROPERTY(BlueprintAssignable, Category = CommonActionWidget)`
- L75 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputIconUpdated);`
- L77 _public member_ `FOnInputIconUpdated OnInputIconUpdated;` — `UPROPERTY(BlueprintAssignable, Category = CommonActionWidget)`
- L84 _public member_ `FSlateBrush ProgressMaterialBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CommonActionWidget)` — The material to use when showing held progress, the progress will be sent using the material parameter defined by ProgressMaterialParam and the value will range from 0..1.
- L88 _public member_ `FName ProgressMaterialParam;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonActionWidget)` — The material parameter on ProgressMaterialBrush to update the held percentage.  This value will be 0..1.
- L91 _public member_ `FSlateBrush IconRimBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonActionWidget)`
- L94 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L97 _public prototype_ `virtual void OnActionProgress(float HeldPercent);`
- L98 _public prototype_ `virtual void OnActionComplete();`
- L99 _public prototype_ `void SetProgressMaterial(const FSlateBrush& InProgressMaterialBrush, const FName& InProgressMaterialParam);`
- L100 _public prototype_ `void SetHidden(bool bAlwaysHidden);`
- L109 _protected member_ `TArray<FDataTableRowHandle> InputActions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonActionWidget, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase", TitleProperty = "RowName"))` — List all the input actions that this common action widget is intended to represent.  In some cases you might have multiple actions that you need to represent as a single entry in the UI.  For example - zoom, might be mouse wheel up or down, but you just need to show a single icon for Up & Down on the mouse, this solves that problem.
- L115 _protected member_ `TObjectPtr<class UInputAction> EnhancedInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = CommonActionWidget, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))` — Input Action this common action widget is intended to represent. Optional if using EnhancedInputs
- L117 _protected member_ `FUIActionBindingHandle DisplayedBindingHandle;`
- L121 _protected member_ `FDataTableRowHandle InputActionDataRow_DEPRECATED;` — `UPROPERTY()`
- L124 _protected member_ `FKey DesignTimeKey;` — `UPROPERTY(EditAnywhere, Category = "CommonActionWidget")`
- L128 _protected prototype_ `UCommonInputSubsystem* GetInputSubsystem() const;`
- L129 _protected prototype_ `const FCommonInputActionDataBase* GetInputActionData() const;`
- L131 _protected prototype_ `virtual void UpdateActionWidget();`
- L133 _protected prototype_ `virtual bool ShouldUpdateActionWidgetIcon() const;`
- L135 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L137 _protected prototype_ `void UpdateBindingHandleInternal(FUIActionBindingHandle BindingHandle);`
- L139 _protected prototype_ `void ListenToInputMethodChanged(bool bListen = true);`
- L140 _protected prototype_ `void HandleInputMethodChanged(ECommonInputType InInputType);`
- L143 _protected prototype_ `void OnEnhancedInputMappingsRebuilt();` — `UFUNCTION()`
- L146 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> ProgressDynamicMaterial;` — `UPROPERTY(Transient)`
- L148 _protected member_ `TSharedPtr<SBox> MyKeyBox;`
- L150 _protected member_ `TSharedPtr<SImage> MyIcon;`
- L152 _protected member_ `TSharedPtr<SImage> MyProgressImage;`
- L154 _protected member_ `TSharedPtr<SImage> MyIconRim;`
- L157 _protected member_ `FSlateBrush Icon;` — `UPROPERTY()`
- L159 _protected member_ `bool bAlwaysHideOverride = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`
- L71 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMethodChanged, bool, bUsingGamepad);`
- L75 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputIconUpdated);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonActivatableWidget.h` (Public)


#### class `FCommonActivatableSlateMetaData`  
`class FCommonActivatableSlateMetaData : public ISlateMetaData`  
_L20-24_
- inherits: `ISlateMetaData`
- desc: Metadata set on UCommonActivatableWidget's underlying slate widget to allow Slate -> UMG lookup
- L23 _public prototype_ `SLATE_METADATA_TYPE(FCommonActivatableSlateMetaData, ISlateMetaData);`

#### class `UCommonActivatableWidget`  
`class UCommonActivatableWidget : public UCommonUserWidget`  
_L43-301_
- reflection: `UCLASS(MinimalAPI, meta = (DisableNativeTick))`
- inherits: `UCommonUserWidget`
- desc: The base for widgets that are capable of being "activated" and "deactivated" during their lifetime without being otherwise modified or destroyed. This is generally desired for one or more of the following purposes: - This widget can turn on/off without being removed from the hierarchy (or otherwise reconstructing the underlying SWidgets), so Construct/Destruct are insufficient - You'd like to be able to "go back" from this widget, whether that means back a breadcrumb, closing a modal, or something else. This is built-in here. - This widget's place in the hierarchy is such that it defines a meaningful node-point in the tree of activatable widgets through which input is routed to all widgets. By default, an activatable widget: - Is not automatically activated upon construction - Does not register to receive back actions (or any other actions, for that matter) - If classified as a back handler, is automatically deactivated (but not destroyed) when it receives a back action Note that removing an activatable widget from the UI (i.e. triggering Destruct()) will always deactivate it, even if the UWidget is not destroyed. Re-constructing the underlying SWidget will only result in re-activation if auto-activate is enabled.
- L49 _public function_ `bool IsActivated() const` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)`
- L52 _public prototype_ `void ActivateWidget();` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)`
- L55 _public prototype_ `void DeactivateWidget();` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)`
- L74 _public prototype_ `void BindVisibilityToActivation(UCommonActivatableWidget* ActivatableWidget);` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)` — Bind our visibility to the activation of another widget, useful for making mouse collisions behave similiar to console navigation w.r.t activation Will immediately update visibility based on the bound widget activation & visibilites set by SetBindVisibilities. @param	ActivatableWidget		- The widget whose activation / deactivation will modify our visibility
- L78 _public prototype_ `UWidget* GetDesiredFocusTarget() const;` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)` — Returns the desired widget to focus when this Widget Activates.
- L82 _public prototype_ `void ClearFocusRestorationTarget();` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)` — Clears the cached focus target that's set when bAutoRestoreFocus is true
- L92 _public prototype_ `void RequestRefreshFocus();` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidget)` — Ask for focus to be re-set to our current DesiredFocusTarget, but only if our node is currently the leaf-most active node (no stealing!). This is useful for complex cases like: the buttons animate in from off-screen, or the buttons are deeply nested in a multi-switcher hierarchy and it would be burdensome to wrap each element in a CommonActivatableWidget.
- L94 _public function_ `FSimpleMulticastDelegate& OnActivated() const`
- L95 _public function_ `FSimpleMulticastDelegate& OnDeactivated() const`
- L102 _public prototype_ `virtual TOptional<FActivationMetadata> GetActivationMetadata() const;` — Gets custom game-specific activation metadata for this widget. By default does nothing & used for nothing.
- L108 _public prototype_ `virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const;` — Gets the desired input configuration to establish when this widget activates and can receive input (i.e. all parents are also active). This configuration will override the existing one established by any previous activatable widget and restore it (if valid) upon deactivation.
- L110 _public function_ `bool IsModal() const`
- L111 _public function_ `bool SupportsActivationFocus() const`
- L112 _public function_ `bool AutoRestoresFocus() const`
- L114 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActivatableWidgetRebuildEvent, UCommonActivatableWidget&);`
- L115 _public member_ `static FActivatableWidgetRebuildEvent OnRebuilding;`
- L117 _public function_ `FSimpleMulticastDelegate& OnSlateReleased() const`
- L119 _public function_ `FSimpleMulticastDelegate& OnRequestRefreshFocus() const`
- L121 _public function_ `bool SetsVisibilityOnActivated() const`
- L122 _public function_ `bool SetsVisibilityOnDeactivated() const`
- L124 _public prototype_ `TWeakPtr<FActivatableTreeNode> GetInputTreeNode() const;`
- L125 _public prototype_ `void RegisterInputTreeNode(const TSharedPtr<FActivatableTreeNode>& OwnerNode);`
- L126 _public prototype_ `void ClearActiveHoldInputs();`
- L131 _public prototype_ `TObjectPtr<UCommonInputActionDomain> GetCalculatedActionDomain();` — Returns the widget's ActionDomain, respecting any inheritance requirements.
- L137 _public prototype_ `void ResetCalculatedActionDomainCache();` — Reset the Action Domain cached by GetCalculatedActionDomain() Call this when updating this widget or a parent widget's action domain
- L140 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L141 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L142 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L143 _protected prototype_ `virtual void NativeConstruct() override;`
- L144 _protected prototype_ `virtual void NativeDestruct() override;`
- L150 _protected prototype_ `virtual UWidget* NativeGetDesiredFocusTarget() const;` — Override to provide the desired widget that should receive focus when this becomes the primary active widget. If bAutoRestoreFocus is true, is only called when there is no valid cached restoration target (to provide the default/fallback)
- L157 _protected prototype_ `UWidget* BP_GetDesiredFocusTarget() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "Get Desired Focus Target"))` — Implement to provide the desired widget to focus if/when this activatable becomes the primary active widget. Note: This is a fallback used only if the native class parentage does not provide a target.
- L165 _protected prototype_ `FUIInputConfig BP_GetDesiredInputConfig() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "Get Desired Input Config"))` — Implement to provide the input config to use when this widget is activated. Keep in mind when all widgets are deactivated, CommonUI will not attempt to automatically restore the input config to before any widget was active. Note: This is a fallback used only if the native class parentage does not provide an input config.
- L168 _protected prototype_ `void BP_OnActivated();` — `UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "On Activated"))`
- L169 _protected prototype_ `virtual void NativeOnActivated();`
- L170 _protected prototype_ `virtual void ActivateMappingContext();`
- L173 _protected prototype_ `void BP_OnDeactivated();` — `UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "On Deactivated"))`
- L174 _protected prototype_ `virtual void NativeOnDeactivated();`
- L175 _protected prototype_ `virtual void DeactivateMappingContext();`
- L182 _protected prototype_ `bool BP_OnHandleBackAction();` — `UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "On Handle Back Action"))` — Override in BP implementations to provide custom behavior when receiving a back action Note: Only called if native code in the base class hasn't handled it in NativeOnHandleBackAction
- L183 _protected prototype_ `virtual bool NativeOnHandleBackAction();`
- L185 _protected prototype_ `void HandleBackAction();`
- L189 _protected member_ `bool bIsBackHandler = false;` — `UPROPERTY(EditAnywhere, Category = Back)` — True to receive "Back" actions automatically. Custom back handler behavior can be provided, default is to deactivate.
- L193 _protected member_ `bool bIsBackActionDisplayedInActionBar = false;` — `UPROPERTY(EditAnywhere, Category = Back)` — True to receive "Back" actions automatically. Custom back handler behavior can be provided, default is to deactivate.
- L197 _protected member_ `FText OverrideBackActionDisplayName;` — `UPROPERTY(EditAnywhere, Category = Back)` — You can specify an override for display name for the back action. If left empty, the default will be used.
- L201 _protected member_ `bool bAutoActivate = false;` — `UPROPERTY(EditAnywhere, Category = Activation)` — True to automatically activate upon construction
- L209 _protected member_ `bool bSupportsActivationFocus = true;` — `UPROPERTY(EditAnywhere, Category = Activation)` — True if this widget is a candidate to receive/route focus or specify a desired UIInputConfig when active. Primary reason for disabling is for utility sub-widgets within a larger screen that possess actions, but are never intended to be involved in navigation or dictate changes to the active UI input config.
- L216 _protected member_ `bool bIsModal = false;` — `UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = bSupportsActivationFocus))` — True to have this widget be treated as a root node for input routing, regardless of its actual parentage. Should seldom be needed, but useful in cases where a child widget should prevent all action processing by parents, even though they remain active (ex: modal popup menu).
- L224 _protected member_ `bool bAutoRestoreFocus = false;` — `UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = bSupportsActivationFocus))` — True to prefer automatically restoring focus to the widget that was focused when this widget last became the non-leafmost-active-widget. If true and a valid restoration candidate exists, we'll use that. If it doesn't, we rely on GetDesiredFocusTarget() If false, we simply always rely on GetDesiredFocusTarget()
- L227 _protected member_ `bool bOverrideActionDomain = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (InlineEditConditionToggle))`
- L231 _protected member_ `TObjectPtr<UInputMappingContext> InputMapping;` — `UPROPERTY(EditAnywhere, Category="Input", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))` — Optional mapping context to be applied & removed on activation & deactivation, respectively.
- L235 _protected member_ `int32 InputMappingPriority = 0;` — `UPROPERTY(EditAnywhere, Category="Input", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))` — Enhanced Input priority. Higher priority input mappings will be prioritized over mappings with a lower priority.
- L241 _protected member_ `TSoftObjectPtr<UCommonInputActionDomain> ActionDomainOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (EditCondition = "bOverrideActionDomain"))` — Enable to override the inherited ActionDomain from owning CommonActivatableWidget.
- L245 _private prototype_ `void HandleVisibilityBoundWidgetActivations();` — See BindVisibilityToMultipleActivations
- L249 _private member_ `FOnWidgetActivationChanged BP_OnWidgetActivated;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (AllowPrivateAccess = true, DisplayName = "On Widget Activated"))` — Fires when the widget is activated.
- L253 _private member_ `FOnWidgetActivationChanged BP_OnWidgetDeactivated;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (AllowPrivateAccess = true, DisplayName = "On Widget Deactivated"))` — Fires when the widget is deactivated.
- L256 _private member_ `bool bIsActive = false;` — `UPROPERTY(BlueprintReadOnly, Category = ActivatableWidget, meta = (AllowPrivateAccess = true))`
- L260 _private member_ `TArray<TWeakObjectPtr<UCommonActivatableWidget>> VisibilityBoundWidgets;` — `UPROPERTY(Transient)` — List of widgets whose collective activation controls our visibility.
- L263 _private member_ `ESlateVisibility ActivatedBindVisibility = ESlateVisibility::SelfHitTestInvisible;` — Visibility to use when widgets we are bound to are activated
- L266 _private member_ `ESlateVisibility DeactivatedBindVisibility = ESlateVisibility::SelfHitTestInvisible;` — Visibility to use when widgets we are bound to are deactivated, not used if widget has activation / deactivation visibilities
- L269 _private member_ `bool bAllActive = true;` — True if we should switch to activated visibility only when all bound widgets are active
- L272 _private member_ `FUIActionBindingHandle DefaultBackActionHandle;` — Handle to default back action, if bound
- L275 _private member_ `TWeakPtr<FActivatableTreeNode> InputTreeNode;` — Input tree node referencing this widget
- L277 _private member_ `mutable FSimpleMulticastDelegate OnActivatedEvent;`
- L278 _private member_ `mutable FSimpleMulticastDelegate OnDeactivatedEvent;`
- L279 _private member_ `mutable FSimpleMulticastDelegate OnSlateReleasedEvent;`
- L280 _private member_ `mutable FSimpleMulticastDelegate OnRequestRefreshFocusEvent;`
- L282 _private member_ `TOptional<TSoftObjectPtr<UCommonInputActionDomain>> CalculatedActionDomainCache;`
- L287 _protected member_ `bool bSetVisibilityOnActivated = false;` — `UPROPERTY(EditAnywhere, Category = Activation, meta = (InlineEditConditionToggle = "ActivatedVisibility"))`
- L290 _protected member_ `ESlateVisibility ActivatedVisibility = ESlateVisibility::SelfHitTestInvisible;` — `UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = "bSetVisibilityOnActivated"))`
- L293 _protected member_ `bool bSetVisibilityOnDeactivated = false;` — `UPROPERTY(EditAnywhere, Category = Activation, meta = (InlineEditConditionToggle = "DeactivatedVisibility"))`
- L296 _protected member_ `ESlateVisibility DeactivatedVisibility = ESlateVisibility::Collapsed;` — `UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = "bSetVisibilityOnDeactivated"))`
- L298 _protected prototype_ `virtual void InternalProcessActivation();`
- L299 _protected prototype_ `virtual void InternalProcessDeactivation();`
- L300 _protected prototype_ `void Reset();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetActivationChanged);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetActivationChanged);`
- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActivatableWidgetRebuildEvent, UCommonActivatableWidget&);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonActivatableWidgetSwitcher.h` (Public)


#### class `UCommonActivatableWidgetSwitcher`  
`class UCommonActivatableWidgetSwitcher : public UCommonAnimatedSwitcher`  
_L18-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommonAnimatedSwitcher`
- desc: An animated switcher that knows about CommonActivatableWidgets. It can also hold other Widgets.
- L23 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L26 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L28 _protected prototype_ `virtual void HandleOutgoingWidget() override;`
- L29 _protected prototype_ `virtual void HandleSlateActiveIndexChanged(int32 ActiveIndex) override;`
- L33 _protected member_ `bool bClearFocusRestorationTargetOfDeactivatedWidgets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Switcher")`
- L36 _private prototype_ `void HandleOwningWidgetActivationChanged(const bool bIsActivated);`
- L38 _private prototype_ `void AttemptToActivateActiveWidget();`
- L39 _private prototype_ `void DeactivateActiveWidget();`
- L41 _private prototype_ `void BindOwningActivatableWidget();`
- L42 _private prototype_ `void UnbindOwningActivatableWidget();`
- L44 _private prototype_ `UCommonActivatableWidget* GetOwningActivatableWidget() const;`
- L46 _private member_ `TOptional<TWeakObjectPtr<UCommonActivatableWidget>> WeakOwningActivatableWidget;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonAnimatedSwitcher.h` (Public)


#### class `UCommonAnimatedSwitcher`  
`class UCommonAnimatedSwitcher : public UWidgetSwitcher`  
_L22-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidgetSwitcher`
- desc: A widget switcher that activates / deactivates CommonActivatableWidgets, allowing for associated animations to trigger.
- L27 _public prototype_ `UCommonAnimatedSwitcher(const FObjectInitializer& ObjectInitializer);`
- L29 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L32 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L35 _public prototype_ `virtual void SetActiveWidgetIndex(int32 Index) override;`
- L36 _public prototype_ `virtual void SetActiveWidget(UWidget* Widget) override;`
- L39 _public prototype_ `void ActivateNextWidget(bool bCanWrap);` — `UFUNCTION(BlueprintCallable, Category = "Common Widget Switcher")`
- L42 _public prototype_ `void ActivatePreviousWidget(bool bCanWrap);` — `UFUNCTION(BlueprintCallable, Category = "Common Widget Switcher")`
- L45 _public prototype_ `bool HasWidgets() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Widget Switcher")`
- L48 _public prototype_ `void SetDisableTransitionAnimation(bool bDisableAnimation);` — `UFUNCTION(BlueprintCallable, Category = "Common Widget Switcher")`
- L51 _public prototype_ `bool IsCurrentlySwitching() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Widget Switcher")`
- L55 _public prototype_ `bool IsTransitionPlaying() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Widget Switcher")` — Is the switcher playing a transition animation?
- L57 _public prototype_ `UWidget* GetPendingActiveWidget() const;`
- L58 _public prototype_ `int32 GetPendingActiveWidgetIndex() const;`
- L61 _protected prototype_ `virtual void HandleSlateActiveIndexChanged(int32 ActiveIndex);`
- L63 _protected prototype_ `virtual void HandleSlateIsTransitioningChanged(bool bIsTransitioning);`
- L65 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L67 _protected function_ `virtual void HandleOutgoingWidget()`
- L71 _public prototype_ `DECLARE_EVENT_TwoParams(UCommonAnimatedSwitcher, FOnActiveIndexChanged, UWidget*, int32) FOnActiveIndexChanged OnActiveWidgetIndexChanged;` — Fires when the active widget displayed by the switcher changes
- L75 _public prototype_ `DECLARE_EVENT_OneParam(UCommonAnimatedSwitcher, FOnTransitioningChanged, bool) FOnTransitioningChanged OnTransitioningChanged;` — Fires when the switcher changes its transition animation state
- L80 _public member_ `FOnActiveIndexChangedDelegate OnActiveWidgetIndexChangedBP;` — `UPROPERTY(BlueprintAssignable, Category = "Common Widget Switcher")` — Fires when the active widget displayed by the switcher changes
- L85 _protected member_ `ECommonSwitcherTransition TransitionType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")` — The type of transition to play between widgets
- L89 _protected member_ `ETransitionCurve TransitionCurveType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")` — The curve function type to apply to the transition animation
- L93 _protected member_ `float TransitionDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")` — The total duration of a single transition between widgets
- L97 _protected member_ `ECommonSwitcherTransitionFallbackStrategy TransitionFallbackStrategy = ECommonSwitcherTransitionFallbackStrategy::None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")` — Controls how we will choose another widget if a transitioning widget is removed during the transition.
- L99 _protected member_ `TSharedPtr<SOverlay> MyOverlay;`
- L100 _protected member_ `TSharedPtr<SSpacer> MyInputGuard;`
- L101 _protected member_ `TSharedPtr<SCommonAnimatedSwitcher> MyAnimatedSwitcher;`
- L104 _protected member_ `bool bInstantTransition = false;` — If set, transition animations will not play
- L106 _protected member_ `bool bSetOnce = false;`
- L107 _protected member_ `bool bCurrentlySwitching = false;`
- L110 _private prototype_ `void SetActiveWidgetIndex_Internal(int32 Index);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveIndexChangedDelegate, UWidget*, ActiveWidget, int32, ActiveIndex);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveIndexChangedDelegate, UWidget*, ActiveWidget, int32, ActiveIndex);`
- L71 _delegate_ `DECLARE_EVENT_TwoParams(UCommonAnimatedSwitcher, FOnActiveIndexChanged, UWidget*, int32) FOnActiveIndexChanged OnActiveWidgetIndexChanged;` — Fires when the active widget displayed by the switcher changes
- L75 _delegate_ `DECLARE_EVENT_OneParam(UCommonAnimatedSwitcher, FOnTransitioningChanged, bool) FOnTransitioningChanged OnTransitioningChanged;` — Fires when the switcher changes its transition animation state

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonBorder.h` (Public)


#### class `UCommonBorderStyle`  
`class UCommonBorderStyle : public UObject`  
_L17-30_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `UObject`
- desc: ---- All properties must be EditDefaultsOnly, BlueprintReadOnly !!! ----- We return the CDO to blueprints, so we cannot allow any changes (blueprint doesn't support const variables)
- L22 _public prototype_ `UCommonBorderStyle();`
- L26 _public member_ `FSlateBrush Background;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The brush for the background of the border
- L29 _public prototype_ `void GetBackgroundBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Border Style|Getters")`

#### class `UCommonBorder`  
`class UCommonBorder : public UBorder`  
_L36-88_
- reflection: `UCLASS(MinimalAPI, Config = CommonUI, DefaultConfig, ClassGroup = UI, meta = (Category = "Common UI", DisplayName = "Common Border"))`
- inherits: `UBorder`
- desc: Uses the border style template defined in CommonUI project settings by default
- L42 _public prototype_ `void SetStyle(TSubclassOf<UCommonBorderStyle> InStyle);` — `UFUNCTION(BlueprintCallable, Category = "Common Border")`
- L46 _public member_ `TSubclassOf<UCommonBorderStyle> Style;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Common Border", meta = (ExposeOnSpawn = true))` — References the border style to use
- L50 _public member_ `bool bReducePaddingBySafezone;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Common Border")` — Turning this on will cause the safe zone size to be removed from this borders content padding down to the minimum specified
- L54 _public member_ `FMargin MinimumPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Common Border", meta = (EditCondition = "bReducePaddingBySafezone"))` — The minimum padding we will reduce to when the safezone grows
- L59 _public member_ `bool bStyleNoLongerNeedsConversion;` — `UPROPERTY()` — Used to track widgets that were created before changing the default style pointer to null
- L63 _protected prototype_ `virtual void PostLoad() override;`
- L66 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L67 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L68 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L71 _protected prototype_ `void SafeAreaUpdated();`
- L72 _protected function_ `void DebugSafeAreaUpdated(const FMargin& NewSafeZone, bool bShouldRecacheMetrics)`
- L74 _protected prototype_ `virtual void OnCreationFromPalette() override;`
- L75 _protected prototype_ `const FText GetPaletteCategory() override;`
- L76 _protected prototype_ `virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;`
- L82 _protected member_ `TOptional<FVector2D> DesignerSize;` — The editor-only size constraint passed in by UMG Designer
- L86 _private prototype_ `const UCommonBorderStyle* GetStyleCDO() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonButtonBase.h` (Public)


#### enum `EHoverEventSource`  
`enum class EHoverEventSource : uint8`  
_L26-33_
- L28 _public enumerator_ `Unknown`
- L29 _public enumerator_ `MouseEvent`
- L30 _public enumerator_ `InteractabilityChanged`
- L31 _public enumerator_ `SelectionChanged`
- L32 _public enumerator_ `SimulationForTouch`

#### class `FCommonButtonMetaData`  
`class FCommonButtonMetaData : public ISlateMetaData`  
_L35-44_
- inherits: `ISlateMetaData`
- L38 _public function_ `SLATE_METADATA_TYPE(FCommonButtonMetaData, ISlateMetaData) FCommonButtonMetaData(const UCommonButtonBase& InOwningCommonButtonInternal):OwningCommonButton(&InOwningCommonButtonInternal)`
- L43 _public member_ `const TWeakObjectPtr<const UCommonButtonBase> OwningCommonButton;`

#### struct `FCommonButtonStyleOptionalSlateSound`  
`struct FCommonButtonStyleOptionalSlateSound`  
_L47-62_
- reflection: `USTRUCT(BlueprintType)`
- L53 _public member_ `bool bHasSound = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")`
- L56 _public member_ `FSlateSound Sound;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (EditCondition = "bHasSound"))`
- L58 _public function_ `explicit operator bool() const`

#### class `UCommonButtonStyle`  
`class UCommonButtonStyle : public UObject`  
_L69-237_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `UObject`
- desc: ---- All properties must be EditDefaultsOnly, BlueprintReadOnly !!! ----- we return the CDO to blueprints, so we cannot allow any changes (blueprint doesn't support const variables)
- L73 _private prototype_ `virtual bool NeedsLoadForServer() const override;`
- L79 _public member_ `bool bSingleMaterial;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — Whether or not the style uses a drop shadow
- L83 _public member_ `FSlateBrush SingleMaterialBrush;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (EditCondition = "bSingleMaterial"))` — The normal (un-selected) brush to apply to each size of this button
- L87 _public member_ `FSlateBrush NormalBase;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Normal", meta = (EditCondition = "!bSingleMaterial"))` — The normal (un-selected) brush to apply to each size of this button
- L91 _public member_ `FSlateBrush NormalHovered;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Normal", meta = (EditCondition = "!bSingleMaterial"))` — The normal (un-selected) brush to apply to each size of this button when hovered
- L95 _public member_ `FSlateBrush NormalPressed;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Normal", meta = (EditCondition = "!bSingleMaterial"))` — The normal (un-selected) brush to apply to each size of this button when pressed
- L99 _public member_ `FSlateBrush SelectedBase;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selected", meta = (EditCondition = "!bSingleMaterial"))` — The selected brush to apply to each size of this button
- L103 _public member_ `FSlateBrush SelectedHovered;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selected", meta = (EditCondition = "!bSingleMaterial"))` — The selected brush to apply to each size of this button when hovered
- L107 _public member_ `FSlateBrush SelectedPressed;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selected", meta = (EditCondition = "!bSingleMaterial"))` — The selected brush to apply to each size of this button when pressed
- L111 _public member_ `FSlateBrush Disabled;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Disabled", meta = (EditCondition = "!bSingleMaterial"))` — The disabled brush to apply to each size of this button
- L115 _public member_ `FMargin ButtonPadding;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The button content padding to apply for each size
- L119 _public member_ `FMargin CustomPadding;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The custom padding of the button to use for each size
- L123 _public member_ `int32 MinWidth;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The minimum width of buttons using this style
- L127 _public member_ `int32 MinHeight;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The minimum height of buttons using this style
- L131 _public member_ `int32 MaxWidth;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The maximum width of buttons using this style
- L135 _public member_ `int32 MaxHeight;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The maximum height of buttons using this style
- L139 _public member_ `TSubclassOf<UCommonTextStyle> NormalTextStyle;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The text style to use when un-selected
- L143 _public member_ `TSubclassOf<UCommonTextStyle> NormalHoveredTextStyle;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The text style to use when un-selected
- L147 _public member_ `TSubclassOf<UCommonTextStyle> SelectedTextStyle;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The text style to use when selected
- L151 _public member_ `TSubclassOf<UCommonTextStyle> SelectedHoveredTextStyle;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The text style to use when un-selected
- L155 _public member_ `TSubclassOf<UCommonTextStyle> DisabledTextStyle;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The text style to use when disabled
- L159 _public member_ `FSlateSound PressedSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Pressed Sound"))` — The sound to play when the button is pressed
- L163 _public member_ `FSlateSound ClickedSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Clicked Sound"))` — The sound to play when the button is clicked
- L167 _public member_ `FCommonButtonStyleOptionalSlateSound SelectedPressedSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Selected Pressed Sound"))` — The sound to play when the button is pressed while selected
- L171 _public member_ `FCommonButtonStyleOptionalSlateSound SelectedClickedSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Selected Clicked Sound"))` — The sound to play when the button is clicked while selected
- L175 _public member_ `FCommonButtonStyleOptionalSlateSound LockedPressedSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Locked Pressed Sound"))` — The sound to play when the button is pressed while locked
- L179 _public member_ `FCommonButtonStyleOptionalSlateSound LockedClickedSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Locked Clicked Sound"))` — The sound to play when the button is clicked while locked
- L183 _public member_ `FSlateSound HoveredSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Hovered Sound"))` — The sound to play when the button is hovered
- L187 _public member_ `FCommonButtonStyleOptionalSlateSound SelectedHoveredSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Selected Hovered Sound"))` — The sound to play when the button is hovered while selected
- L191 _public member_ `FCommonButtonStyleOptionalSlateSound LockedHoveredSlateSound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (DisplayName = "Locked Hovered Sound"))` — The sound to play when the button is hovered while locked
- L194 _public prototype_ `void GetMaterialBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L197 _public prototype_ `void GetNormalBaseBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L200 _public prototype_ `void GetNormalHoveredBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L203 _public prototype_ `void GetNormalPressedBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L206 _public prototype_ `void GetSelectedBaseBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L209 _public prototype_ `void GetSelectedHoveredBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L212 _public prototype_ `void GetSelectedPressedBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L215 _public prototype_ `void GetDisabledBrush(FSlateBrush& Brush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L218 _public prototype_ `void GetButtonPadding(FMargin& OutButtonPadding) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L221 _public prototype_ `void GetCustomPadding(FMargin& OutCustomPadding) const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L224 _public prototype_ `UCommonTextStyle* GetNormalTextStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L227 _public prototype_ `UCommonTextStyle* GetNormalHoveredTextStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L230 _public prototype_ `UCommonTextStyle* GetSelectedTextStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L233 _public prototype_ `UCommonTextStyle* GetSelectedHoveredTextStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`
- L236 _public prototype_ `UCommonTextStyle* GetDisabledTextStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common ButtonStyle|Getters")`

#### class `UCommonButtonInternalBase`  
`class UCommonButtonInternalBase : public UButton`  
_L243-319_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UButton`
- desc: Custom UButton override that allows us to disable clicking without disabling the widget entirely
- L248 _public prototype_ `void SetButtonEnabled(bool bInIsButtonEnabled);`
- L249 _public prototype_ `void SetInteractionEnabled(bool bInIsInteractionEnabled);`
- L252 _public prototype_ `void SetButtonFocusable(bool bInIsButtonFocusable);` — Updates the IsFocusable flag and updates the bIsFocusable flag of the underlying slate button widget
- L253 _public prototype_ `bool IsHovered() const;`
- L254 _public prototype_ `bool IsPressed() const;`
- L256 _public prototype_ `void SetMinDesiredHeight(int32 InMinHeight);`
- L257 _public function_ `int32 GetMinHeight() const`
- L258 _public prototype_ `void SetMinDesiredWidth(int32 InMinWidth);`
- L259 _public function_ `int32 GetMinWidth() const`
- L260 _public prototype_ `void SetMaxDesiredHeight(int32 InMaxHeight);`
- L261 _public function_ `int32 GetMaxHeight() const`
- L262 _public prototype_ `void SetMaxDesiredWidth(int32 InMaxWidth);`
- L263 _public function_ `int32 GetMaxWidth() const`
- L265 _public function_ `inline TSharedPtr<class SCommonButton> GetCommonButton() const`
- L268 _public member_ `FOnButtonDoubleClickedEvent HandleDoubleClicked;` — Called when the button is clicked
- L272 _public member_ `FOnButtonClickedEvent OnDoubleClicked;` — `UPROPERTY(BlueprintAssignable, Category = "Common Button Internal|Event")` — Called when the button is clicked
- L276 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L277 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L280 _protected prototype_ `virtual FReply SlateHandleClickedOverride();`
- L281 _protected prototype_ `virtual void SlateHandlePressedOverride();`
- L282 _protected prototype_ `virtual void SlateHandleReleasedOverride();`
- L283 _protected prototype_ `virtual FReply SlateHandleDoubleClicked();`
- L284 _protected prototype_ `virtual FReply SlateHandleDragDetectedOverride(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);`
- L285 _protected prototype_ `virtual void SlateHandleDragEnterOverride(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L286 _protected prototype_ `virtual void SlateHandleDragLeaveOverride(const FDragDropEvent& DragDropEvent);`
- L287 _protected prototype_ `virtual FReply SlateHandleDragOverOverride(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L288 _protected prototype_ `virtual FReply SlateHandleDropOverride(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L292 _protected member_ `int32 MinWidth;` — `UPROPERTY()` — The minimum width of the button
- L296 _protected member_ `int32 MinHeight;` — `UPROPERTY()` — The minimum height of the button
- L300 _protected member_ `int32 MaxWidth;` — `UPROPERTY()` — The maximum width of the button
- L304 _protected member_ `int32 MaxHeight;` — `UPROPERTY()` — The maximum height of the button
- L308 _protected member_ `bool bButtonEnabled;` — `UPROPERTY()` — If true, this button is enabled.
- L312 _protected member_ `bool bInteractionEnabled;` — `UPROPERTY()` — If true, this button can be interacted with it normally. Otherwise, it will not react to being hovered or clicked.
- L315 _protected member_ `TSharedPtr<SBox> MyBox;` — Cached pointer to the underlying slate button owned by this UWidget
- L318 _protected member_ `TSharedPtr<class SCommonButton> MyCommonButton;` — Cached pointer to the underlying slate button owned by this UWidget

#### class `UCommonButtonBase`  
`class UCommonButtonBase : public UCommonUserWidget`  
_L330-1159_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI, ClassGroup = UI, meta = (Category = "Common UI", DisableNativeTick))`
- inherits: `UCommonUserWidget`
- desc: Button that disables itself when not active. Also updates actions for CommonActionWidget if bound to display platform-specific icons.
- L336 _public prototype_ `virtual bool IsHovered() const override;` — UWidget interface
- L340 _public prototype_ `virtual void NativeConstruct() override;` — UUserWidget interface
- L341 _public prototype_ `virtual void NativeDestruct() override;`
- L342 _public prototype_ `virtual bool Initialize() override;`
- L343 _public prototype_ `virtual void SetIsEnabled(bool bInIsEnabled) override;`
- L344 _public prototype_ `virtual void SetVisibility(ESlateVisibility InVisibility) override;`
- L345 _public prototype_ `virtual bool NativeIsInteractable() const override;`
- L350 _public prototype_ `void DisableButtonWithReason(const FText& DisabledReason);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Disables this button with a reason (use instead of SetIsEnabled)
- L354 _public prototype_ `void SetIsInteractionEnabled(bool bInIsInteractionEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this widget is selectable at all. If false and currently selected, will deselect.
- L357 _public prototype_ `void SetHideInputAction(bool bInHideInputAction);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")`
- L360 _public prototype_ `void SetHideInputActionWithKeyboard(bool bInHideInputActionWithKeyboard);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")`
- L364 _public prototype_ `bool IsInteractionEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — Is this button currently interactable? (use instead of GetIsEnabled)
- L368 _public prototype_ `bool IsPressed() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — Is this button currently pressed?
- L372 _public prototype_ `void SetClickMethod(EButtonClickMethod::Type InClickMethod);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Set the click method for mouse interaction
- L376 _public prototype_ `void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Set the click method for touch interaction
- L380 _public prototype_ `void SetPressMethod(EButtonPressMethod::Type InPressMethod);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Set the click method for keyboard/gamepad button press interaction
- L384 _public prototype_ `void SetIsSelectable(bool bInIsSelectable);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this widget is selectable at all. If false and currently selected, will deselect.
- L388 _public prototype_ `void SetIsInteractableWhenSelected(bool bInInteractableWhenSelected);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this widget is selectable at all. If false and currently selected, will deselect.
- L392 _public prototype_ `void SetIsToggleable(bool bInIsToggleable);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this widget is toggleable. If toggleable, clicking when selected will deselect.
- L396 _public prototype_ `void SetShouldUseFallbackDefaultInputAction(bool bInShouldUseFallbackDefaultInputAction);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this widget should use the fallback default input action.
- L403 _public prototype_ `void SetIsSelected(bool InSelected, bool bGiveClickFeedback = true);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change the selected state manually. @param bGiveClickFeedback	If true, the button may give user feedback as if it were clicked. IE: Play a click sound, trigger animations as if it were clicked.
- L407 _public prototype_ `void SetIsLocked(bool bInIsLocked);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this widget is locked. If locked, the button can be focusable and responsive to mouse input but will not broadcast OnClicked events.
- L411 _public prototype_ `bool GetSelected() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @returns True if the button is currently in a selected state, False otherwise
- L415 _public prototype_ `bool GetLocked() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @returns True if the button is currently locked, False otherwise
- L418 _public prototype_ `void ClearSelection();` — `UFUNCTION(BlueprintCallable, Category = "Common Button")`
- L422 _public prototype_ `void SetShouldSelectUponReceivingFocus(bool bInShouldSelectUponReceivingFocus);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Set whether the button should become selected upon receiving focus or not; Only settable for buttons that are selectable
- L426 _public prototype_ `bool GetShouldSelectUponReceivingFocus() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — Get whether the button should become selected upon receiving focus or not
- L430 _public prototype_ `void SetStyle(TSubclassOf<UCommonButtonStyle> InStyle = {});` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Sets the style of this button, rebuilds the internal styling
- L434 _public prototype_ `UCommonButtonStyle* GetStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @Returns Current button style
- L436 _public prototype_ `const UCommonButtonStyle* GetStyleCDO() const;`
- L440 _public prototype_ `void GetCurrentButtonPadding(FMargin& OutButtonPadding) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @return The current button padding that corresponds to the current size and selection state
- L444 _public prototype_ `void GetCurrentCustomPadding(FMargin& OutCustomPadding) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @return The custom padding that corresponds to the current size and selection state
- L448 _public prototype_ `UCommonTextStyle* GetCurrentTextStyle() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @return The text style that corresponds to the current size and selection state
- L452 _public prototype_ `TSubclassOf<UCommonTextStyle> GetCurrentTextStyleClass() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — @return The class of the text style that corresponds to the current size and selection state
- L456 _public prototype_ `void SetMinDimensions(int32 InMinWidth, int32 InMinHeight);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Sets the minimum dimensions of this button
- L460 _public prototype_ `void SetMaxDimensions(int32 InMaxWidth, int32 InMaxHeight);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Sets the maximum dimensions of this button
- L464 _public prototype_ `void SetActionDisplayName(const FText& InDisplayName);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Updates the display name via its bound UIAction
- L468 _public prototype_ `void SetTriggeredInputAction(const FDataTableRowHandle &InputActionRow);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Updates the current triggered action
- L472 _public prototype_ `void SetTriggeringInputAction(const FDataTableRowHandle & InputActionRow);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Updates the current triggering action
- L476 _public prototype_ `void SetTriggeringEnhancedInputAction(UInputAction* InInputAction);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Updates the current triggering enhanced input action, requires enhanced input enabled in CommonUI settings
- L480 _public prototype_ `bool GetInputAction(FDataTableRowHandle &InputActionRow) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — Gets the appropriate input action that is set
- L484 _public prototype_ `UInputAction* GetEnhancedInputAction() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — Gets the appropriate enhanced input action that is set
- L488 _public function_ `bool GetRequiresHold() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Common Button|Getters")` — Returns true if this button has a hold behavior, even if the triggering action is not holdable.
- L492 _public prototype_ `void SetRequiresHold(bool bInRequiresHold);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Change whether this button should have a hold behavior even if the triggering action is not holdable.
- L496 _public function_ `float GetRequiredHoldTime() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Common Button|Getters")` — Returns required hold time for performing a triggering action.
- L500 _public prototype_ `void SetAllowDragDrop(bool bInAllowDragDrop);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Updates the bAllowDragDrop flag  on the RootButton
- L504 _public prototype_ `void SetIsFocusable(bool bInIsFocusable);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Setters")` — Updates the bIsFocusable flag
- L508 _public prototype_ `bool GetIsFocusable() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Getters")` — Gets the bIsFocusable flag
- L512 _public prototype_ `UMaterialInstanceDynamic* GetSingleMaterialStyleMID() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Common Button|Getters")` — Returns the dynamic instance of the material being used for this button, if it is using a single material style.
- L515 _public prototype_ `void SetInputActionProgressMaterial(const FSlateBrush& InProgressMaterialBrush, const FName& InProgressMaterialParam);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Input")`
- L518 _public prototype_ `void SetPressedSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L521 _public prototype_ `void SetClickedSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L524 _public prototype_ `void SetHoveredSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L527 _public prototype_ `void SetSelectedPressedSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L530 _public prototype_ `void SetSelectedClickedSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L533 _public prototype_ `void SetSelectedHoveredSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L536 _public prototype_ `void SetLockedPressedSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L539 _public prototype_ `void SetLockedClickedSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L542 _public prototype_ `void SetLockedHoveredSoundOverride(USoundBase* Sound);` — `UFUNCTION(BlueprintCallable, Category = "Common Button|Sound")`
- L544 _public prototype_ `DECLARE_EVENT(UCommonButtonBase, FCommonButtonEvent);`
- L545 _public function_ `FCommonButtonEvent& OnClicked() const`
- L546 _public function_ `FCommonButtonEvent& OnDoubleClicked() const`
- L547 _public function_ `FCommonButtonEvent& OnPressed() const`
- L548 _public function_ `FCommonButtonEvent& OnReleased() const`
- L549 _public function_ `FCommonButtonEvent& OnHovered() const`
- L550 _public function_ `FCommonButtonEvent& OnUnhovered() const`
- L551 _public function_ `FCommonButtonEvent& OnFocusReceived() const`
- L552 _public function_ `FCommonButtonEvent& OnFocusLost() const`
- L553 _public function_ `FCommonButtonEvent& OnLockClicked() const`
- L554 _public function_ `FCommonButtonEvent& OnLockDoubleClicked() const`
- L556 _public function_ `FOnDragDetected& OnCommonButtonDragDetected() const`
- L557 _public function_ `FOnDragEnter& OnCommonButtonDragEnter() const`
- L558 _public function_ `FOnDragLeave& OnCommonButtonDragLeave() const`
- L559 _public function_ `FOnDragOver& OnCommonButtonDragOver() const`
- L560 _public function_ `FOnDrop& OnCommonButtonDrop() const`
- L563 _public member_ `FWidgetEventField ClickEvent;` — `UPROPERTY(BlueprintReadOnly, FieldNotify, Category= "Common Button")`
- L565 _public prototype_ `DECLARE_EVENT_OneParam(UCommonButtonBase, FOnIsSelectedChanged, bool);`
- L566 _public function_ `FOnIsSelectedChanged& OnIsSelectedChanged() const`
- L569 _protected function_ `bool IsPersistentBinding() const`
- L570 _protected function_ `ECommonInputMode GetInputModeOverride() const`
- L572 _protected prototype_ `virtual UCommonButtonInternalBase* ConstructInternalButton();`
- L574 _protected prototype_ `virtual void OnWidgetRebuilt();`
- L575 _protected prototype_ `virtual void PostLoad() override;`
- L576 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L577 _protected prototype_ `virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;`
- L580 _protected prototype_ `virtual void OnCreationFromPalette() override;`
- L581 _protected prototype_ `const FText GetPaletteCategory() override;`
- L585 _protected prototype_ `void SetPressedSlateSoundOverride(const FSlateSound& InPressedSlateSoundOverride);` — In some scenarios, USoundBase* setters are bypassed, so standard setters must also be provided for sound override properties
- L586 _protected prototype_ `void SetClickedSlateSoundOverride(const FSlateSound& InClickedSlateSoundOverride);`
- L587 _protected prototype_ `void SetHoveredSlateSoundOverride(const FSlateSound& InHoveredSlateSoundOverride);`
- L588 _protected prototype_ `void SetSelectedPressedSlateSoundOverride(const FSlateSound& InSelectedPressedSlateSoundOverride);`
- L589 _protected prototype_ `void SetSelectedClickedSlateSoundOverride(const FSlateSound& InSelectedClickedSlateSoundOverride);`
- L590 _protected prototype_ `void SetSelectedHoveredSlateSoundOverride(const FSlateSound& InSelectedHoveredSlateSoundOverride);`
- L591 _protected prototype_ `void SetLockedPressedSlateSoundOverride(const FSlateSound& InLockedPressedSlateSoundOverride);`
- L592 _protected prototype_ `void SetLockedClickedSlateSoundOverride(const FSlateSound& InLockedClickedSlateSoundOverride);`
- L593 _protected prototype_ `void SetLockedHoveredSlateSoundOverride(const FSlateSound& InLockedHoveredSlateSoundOverride);`
- L596 _protected prototype_ `virtual void BindInputMethodChangedDelegate();` — Helper function to bind to input method change events
- L599 _protected prototype_ `virtual void UnbindInputMethodChangedDelegate();` — Helper function to unbind from input method change events
- L603 _protected prototype_ `virtual void OnInputMethodChanged(ECommonInputType CurrentInputType);` — `UFUNCTION()` — Called via delegate when the input method changes
- L607 _protected prototype_ `bool ShouldProcessHoverEvent(EHoverEventSource HoverReason);` — This should be used as a check before calling NativeOnHovered and NativeOnUnhovered. returns false if this button is set to explicitly block hover events on touch.
- L611 _protected prototype_ `virtual void UpdateHoldData(ECommonInputType CurrentInputType);` — `UFUNCTION()` — If HoldData is valid, assigns its values to Keyboard and Mouse, Gamepad and Touch, based off the Current Input Type.
- L614 _protected prototype_ `virtual void BindTriggeringInputActionToClick();` — Associates this button at its priority with the given key
- L617 _protected prototype_ `virtual void UnbindTriggeringInputActionToClick();` — Associates this button at its priority with the given key
- L620 _protected prototype_ `virtual void HandleTriggeringActionCommited(bool& bPassthrough);` — `UFUNCTION()`
- L621 _protected prototype_ `virtual void HandleTriggeringActionCommited();`
- L624 _protected prototype_ `virtual void ExecuteTriggeredInput();` — @TODO: DarenC - API decision, consider removing
- L627 _protected prototype_ `virtual void UpdateInputActionWidget();` — Helper function to update the associated input action widget, if any, based upon the state of the button
- L631 _protected prototype_ `virtual void HandleButtonClicked();` — `UFUNCTION()` — Handler function registered to the underlying button's click.
- L634 _protected prototype_ `virtual FReply HandleButtonDoubleClicked();` — Handler function registered to the underlying button's double click.
- L638 _protected prototype_ `virtual void HandleFocusReceived();` — `UFUNCTION()` — Helper function registered to the underlying button receiving focus
- L642 _protected prototype_ `virtual void HandleFocusLost();` — `UFUNCTION()` — Helper function registered to the underlying button losing focus
- L646 _protected prototype_ `virtual void HandleButtonPressed();` — `UFUNCTION()` — Helper function registered to the underlying button when pressed
- L650 _protected prototype_ `virtual void HandleButtonReleased();` — `UFUNCTION()` — Helper function registered to the underlying button when released
- L653 _protected prototype_ `virtual FReply HandleButtonDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);` — Helper function registered to the underlying button when drag is detected
- L656 _protected prototype_ `virtual void HandleButtonDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);` — Helper function registered to the underlying button when dragged widget enters
- L659 _protected prototype_ `virtual void HandleButtonDragLeave(const FDragDropEvent& DragDropEvent);` — Helper function registered to the underlying button when dragged widget leaves
- L662 _protected prototype_ `virtual FReply HandleButtonDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);` — Helper function registered to the underlying button when dragged over
- L665 _protected prototype_ `virtual FReply HandleButtonDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);` — Helper function registered to the underlying button when dropped during a drag drop operation
- L668 _protected prototype_ `void BP_OnSelected();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Selected"))`
- L669 _protected prototype_ `virtual void NativeOnSelected(bool bBroadcast);`
- L672 _protected prototype_ `void BP_OnDeselected();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Deselected"))`
- L673 _protected prototype_ `virtual void NativeOnDeselected(bool bBroadcast);`
- L676 _protected prototype_ `void BP_OnHovered();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Hovered"))`
- L677 _protected prototype_ `virtual void NativeOnHovered();`
- L680 _protected prototype_ `void BP_OnUnhovered();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Unhovered"))`
- L681 _protected prototype_ `virtual void NativeOnUnhovered();`
- L684 _protected prototype_ `void BP_OnFocusReceived();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Focused"))`
- L687 _protected prototype_ `void BP_OnFocusLost();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Unfocused"))`
- L690 _protected prototype_ `void BP_OnLockedChanged(bool bIsLocked);` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Locked Changed"))`
- L693 _protected prototype_ `void BP_OnLockClicked();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Lock Clicked"))`
- L696 _protected prototype_ `void BP_OnLockDoubleClicked();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Lock Double Clicked"))`
- L699 _protected prototype_ `void BP_OnClicked();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Clicked"))`
- L700 _protected prototype_ `virtual void NativeOnClicked();`
- L703 _protected prototype_ `void BP_OnDoubleClicked();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Double Clicked"))`
- L704 _protected prototype_ `virtual void NativeOnDoubleClicked();`
- L707 _protected prototype_ `void BP_OnInputActionTriggered();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Input Action Triggered"))`
- L711 _protected prototype_ `void StopDoubleClickPropagation();` — `UFUNCTION(BlueprintCallable, Category = CommonButton)` — Unless this is called, we will assume the double click should be converted into a normal click.
- L714 _protected prototype_ `void BP_OnPressed();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Pressed"))`
- L715 _protected prototype_ `virtual void NativeOnPressed();`
- L718 _protected prototype_ `void BP_OnReleased();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Released"))`
- L719 _protected prototype_ `virtual void NativeOnReleased();`
- L721 _protected prototype_ `virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;`
- L723 _protected prototype_ `virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;`
- L725 _protected prototype_ `virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;`
- L727 _protected prototype_ `virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;`
- L729 _protected prototype_ `virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;`
- L732 _protected prototype_ `void BP_OnEnabled();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Enabled"))`
- L733 _protected prototype_ `virtual void NativeOnEnabled();`
- L736 _protected prototype_ `void BP_OnDisabled();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Disabled"))`
- L737 _protected prototype_ `virtual void NativeOnDisabled();`
- L740 _protected prototype_ `void BP_OnInputMethodChanged(ECommonInputType CurrentInputType);` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Input Method Changed"))`
- L744 _protected prototype_ `void OnCurrentTextStyleChanged();` — `UFUNCTION(BlueprintImplementableEvent, meta=(BlueprintProtected="true"), Category = "Common Button")` — Allows derived classes to take action when the current text style has changed
- L745 _protected prototype_ `virtual void NativeOnCurrentTextStyleChanged();`
- L748 _protected prototype_ `void BP_OnRequiresHoldChanged();` — `UFUNCTION(BlueprintImplementableEvent, Category = CommonButton, meta = (DisplayName = "On Requires Hold Changed"))`
- L752 _protected prototype_ `void SetSelectedInternal(bool bInSelected, bool bAllowSound = true, bool bBroadcast = true);` — `UFUNCTION(BlueprintCallable, meta=(BlueprintProtected="true"), Category = "Common Button")` — Internal method to allow the selected state to be set regardless of selectability or toggleability
- L756 _protected prototype_ `void OnTriggeredInputActionChanged(const FDataTableRowHandle& NewTriggeredAction);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Common Button")` — Callback fired when input action datatable row changes
- L760 _protected prototype_ `void OnTriggeringInputActionChanged(const FDataTableRowHandle& NewTriggeredAction);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Common Button")` — Callback fired when triggered input action datatable row changes
- L764 _protected prototype_ `void OnTriggeringEnhancedInputActionChanged(const UInputAction* InInputAction);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Common Button")` — Callback fired when enhanced input action changes
- L768 _protected prototype_ `void OnActionProgress(float HeldPercent);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Common Button")` — Callback fired continously during hold interactions
- L775 _protected prototype_ `virtual bool GetConvertInputActionToHold();` — `UFUNCTION()` — By default, if bRequiresHold is true, the bound Input Action will be forced to require hold as well. The Bound Input action will use the row's hold values regardless of the row's bRequiresHold state.
- L779 _protected prototype_ `virtual void NativeOnActionProgress(float HeldPercent);` — `UFUNCTION()` — Bound to the hold progress of the bound key from the input action
- L783 _protected prototype_ `virtual bool NativeOnHoldProgress(float DeltaTime);` — `UFUNCTION()` — Bound to the hold progress not related to the bound key
- L787 _protected prototype_ `virtual bool NativeOnHoldProgressRollback(float DeltaTime);` — `UFUNCTION()` — Bound to the hold progress rollback not related to the bound key
- L791 _protected prototype_ `void OnActionComplete();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Common Button")` — Callback fired when hold events complete
- L794 _protected prototype_ `virtual void NativeOnActionComplete();` — `UFUNCTION()`
- L797 _protected prototype_ `virtual void HoldReset();` — `UFUNCTION()`
- L799 _protected prototype_ `virtual bool GetButtonAnalyticInfo(FString& ButtonName, FString& ABTestName, FString& ExtraData) const;`
- L801 _protected prototype_ `void RefreshDimensions();`
- L802 _protected prototype_ `void RefreshDimensions(const int32 InMinWidth,const int32 InMinHeight,const int32 InMaxWidth,const int32 InMaxHeight);`
- L803 _protected prototype_ `virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;`
- L804 _protected prototype_ `virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;`
- L806 _protected prototype_ `virtual void UpdateInputActionWidgetVisibility();`
- L810 _protected member_ `int32 MinWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Layout, meta = (ClampMin = "0"))` — The minimum width of the button (only used if greater than the style's minimum)
- L814 _protected member_ `int32 MinHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Layout, meta = (ClampMin = "0"))` — The minimum height of the button (only used if greater than the style's minimum)
- L818 _protected member_ `int32 MaxWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Layout, meta = (ClampMin = "0"))` — The maximum width of the button (only used if greater than the style's maximum)
- L822 _protected member_ `int32 MaxHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Layout, meta = (ClampMin = "0"))` — The maximum height of the button (only used if greater than the style's maximum)
- L826 _protected member_ `TSubclassOf<UCommonButtonStyle> Style;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Style, meta = (ExposeOnSpawn = true))` — References the button style asset that defines a style in multiple sizes
- L830 _protected member_ `bool bHideInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Style)` — Whether to hide the input action widget at all times (useful for textless small buttons)
- L837 _protected member_ `FSlateSound PressedSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Pressed Sound Override"))` — Optional override for the sound to play when this button is pressed. Also used for the Selected and Locked Pressed state if their respective overrides are empty.
- L843 _protected member_ `FSlateSound ClickedSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Clicked Sound Override"))` — Optional override for the sound to play when this button is clicked (based on Click/Touch/Press methods).
- L850 _protected member_ `FSlateSound HoveredSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Hovered Sound Override"))` — Optional override for the sound to play when this button is hovered. Also used for the Selected and Locked Hovered state if their respective overrides are empty.
- L854 _protected member_ `FSlateSound SelectedPressedSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Selected Pressed Sound Override"))` — Optional override for the sound to play when this button is pressed while Selected
- L858 _protected member_ `FSlateSound SelectedClickedSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Selected Clicked Sound Override"))` — Optional override for the sound to play when this button is clicked while Selected
- L862 _protected member_ `FSlateSound SelectedHoveredSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Selected Hovered Sound Override"))` — Optional override for the sound to play when this button is hovered while Selected
- L866 _protected member_ `FSlateSound LockedPressedSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Locked Pressed Sound Override"))` — Optional override for the sound to play when this button is pressed while Locked
- L870 _protected member_ `FSlateSound LockedClickedSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Locked Clicked Sound Override"))` — Optional override for the sound to play when this button is clicked while Locked
- L874 _protected member_ `FSlateSound LockedHoveredSlateSoundOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = Sound, meta = (DisplayName = "Locked Hovered Sound Override"))` — Optional override for the sound to play when this button is hovered while Locked
- L878 _protected member_ `uint8 bApplyAlphaOnDisable:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Style, meta = (ExposeOnSpawn = true))` — The type of mouse action required by the user to trigger the button's 'Click'
- L886 _protected member_ `uint8 bLocked:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Locked, meta = (ExposeOnSpawn = true))` — True if this button is currently locked. Locked button can be hovered, focused, and pressed, but the Click event will not go through. Business logic behind it will not be executed. Designed for progressive disclosure
- L890 _protected member_ `uint8 bSelectable:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Selection, meta = (ExposeOnSpawn = true))` — True if the button supports being in a "selected" state, which will update the style accordingly
- L894 _protected member_ `uint8 bShouldSelectUponReceivingFocus:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Selection, meta = (ExposeOnSpawn = true, EditCondition = "bSelectable"))` — If true, the button will be selected when it receives focus.
- L898 _protected member_ `uint8 bInteractableWhenSelected:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Selection, meta = (ExposeOnSpawn = true, EditCondition = "bSelectable"))` — If true, the button may be clicked while selected. Otherwise, interaction is disabled in the selected state.
- L902 _protected member_ `uint8 bToggleable:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Selection, meta = (ExposeOnSpawn = true, EditCondition = "bSelectable"))` — True if the button can be deselected by clicking it when selected
- L905 _protected member_ `uint8 bTriggerClickedAfterSelection:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Selection, meta = (ExposeOnSpawn = true, EditCondition = "bSelectable"))`
- L909 _protected member_ `uint8 bDisplayInputActionWhenNotInteractable:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true))` — True if the input action should be displayed when the button is not interactable
- L913 _protected member_ `uint8 bHideInputActionWithKeyboard:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true))` — True if the input action should be hidden while the user is using a keyboard
- L917 _protected member_ `uint8 bShouldUseFallbackDefaultInputAction:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true))` — True if this button should use the default fallback input action (bool is useful for buttons that shouldn't because they are never directly hit via controller)
- L921 _protected member_ `uint8 bRequiresHold:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hold", meta = (ExposeOnSpawn = true))` — True if this button should have a press and hold behavior, triggering the click when the specified hold time is met
- L925 _protected member_ `TSubclassOf<UCommonUIHoldData> HoldData;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hold", meta = (EditCondition="bRequiresHold", ExposeOnSpawn = true))` — Press and Hold values used for Keyboard and Mouse, Gamepad and Touch, depending on the current input type
- L929 _protected member_ `bool bSimulateHoverOnTouchInput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, AdvancedDisplay, meta = (EditCondition="IsHoverSimulationOnTouchAvailable()", EditConditionHides))` — True if this button should play the hover effect when pressed by a touch input
- L934 _private member_ `uint8 bSelected:1;` — True if this button is currently selected
- L937 _private member_ `uint8 bButtonEnabled:1;` — True if this button is currently enabled
- L940 _private member_ `uint8 bInteractionEnabled:1;` — True if interaction with this button is currently enabled
- L945 _public member_ `TEnumAsByte<EButtonClickMethod::Type> ClickMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true))` — The type of mouse action required by the user to trigger the button's 'Click'
- L948 _public member_ `TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)`
- L951 _public member_ `TEnumAsByte<EButtonPressMethod::Type> PressMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)`
- L960 _public member_ `int32 InputPriority;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true))` — This is the priority for the TriggeringInputAction.  The first, HIGHEST PRIORITY widget will handle the input action, and no other widgets will be considered. Additionally, no inputs with a priority below the current ActivatablePanel's Input Priority value will even be considered! @TODO: This is part of legacy CommonUI and should be removed
- L967 _public member_ `FDataTableRowHandle TriggeringInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true, RowType = "/Script/CommonUI.CommonInputActionDataBase"))` — The input action that is bound to this button. The common input manager will trigger this button to click if the action was pressed
- L974 _public member_ `TObjectPtr<UInputAction> TriggeringEnhancedInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))` — The enhanced input action that is bound to this button. The common input manager will trigger this button to click if the action was pressed
- L982 _public member_ `FDataTableRowHandle TriggeredInputAction;` — The input action that can be visualized as well as triggered when the user clicks the button. @TODO: This is part of legacy CommonUI and should be removed
- L987 _public member_ `bool bStyleNoLongerNeedsConversion;` — `UPROPERTY()` — Used to track widgets that were created before changing the default style pointer to null
- L992 _public member_ `uint8 bNavigateToNextWidgetOnDisable : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)` — If this button is currently in focus, and is disabled, hidden, or collapsed then focus will be routed to the next available widget
- L996 _protected member_ `FCommonSelectedStateChangedBase OnSelectedChangedBase;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Selected Changed"))`
- L999 _protected member_ `FCommonButtonBaseClicked OnButtonBaseClicked;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Clicked"))`
- L1002 _protected member_ `FCommonButtonBaseClicked OnButtonBaseDoubleClicked;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Double Clicked"))`
- L1005 _protected member_ `FCommonButtonBaseClicked OnButtonBaseHovered;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Hovered"))`
- L1008 _protected member_ `FCommonButtonBaseClicked OnButtonBaseUnhovered;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Unhovered"))`
- L1011 _protected member_ `FCommonButtonBaseClicked OnButtonBaseFocused;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Focused"))`
- L1014 _protected member_ `FCommonButtonBaseClicked OnButtonBaseUnfocused;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Unfocused"))`
- L1017 _protected member_ `FCommonButtonBaseClicked OnButtonBaseLockClicked;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Lock Clicked"))`
- L1020 _protected member_ `FCommonButtonBaseClicked OnButtonBaseLockDoubleClicked;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Lock Double Clicked"))`
- L1023 _protected member_ `FCommonButtonBaseClicked OnButtonBaseSelected;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Selected"))`
- L1026 _protected member_ `FCommonButtonBaseClicked OnButtonBaseUnselected;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Unselected"))`
- L1029 _protected member_ `FOnButtonBaseGeoOperationDynamic OnButtonBaseDragDetected;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Drag Detected"))`
- L1032 _protected member_ `FOnButtonBaseGeoOperationDynamic OnButtonBaseDragEnter;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Drag Enter"))`
- L1035 _protected member_ `FOnButtonBaseOperationDynamic OnButtonBaseDragLeave;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Drag Leave"))`
- L1038 _protected member_ `FOnButtonBaseGeoOperationDynamic OnButtonBaseDragOver;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Drag Over"))`
- L1041 _protected member_ `FOnButtonBaseGeoOperationDynamic OnButtonBaseDrop;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Drag Drop"))`
- L1043 _protected member_ `FUIActionBindingHandle TriggeringBindingHandle;`
- L1046 _protected member_ `float HoldTime;` — Press and hold time in seconds
- L1053 _protected member_ `float HoldRollbackTime;` — Time (in seconds) for hold progress to go from 1.0 (completed) to 0.0. Used when the press and hold is interrupted. If set to 0, there will be no rollback and the hold progress will reset immediately.
- L1056 _protected member_ `float CurrentHoldTime;` — Current hold time for this button
- L1059 _protected member_ `float CurrentHoldProgress;` — Current hold progress % for this button
- L1062 _protected member_ `FTSTicker::FDelegateHandle HoldTickerHandle;` — Handle for ticker spawned for press and hold
- L1065 _protected member_ `FTSTicker::FDelegateHandle HoldProgressRollbackTickerHandle;` — Handle for ticker spawned for button hold rollback
- L1078 _private member_ `bool bIsPersistentBinding = false;` — `UPROPERTY(EditAnywhere, Category = Input, AdvancedDisplay)` — DANGER! Be very, very careful with this. Unless you absolutely know what you're doing, this is not the property you're looking for. True to register the action bound to this button as a "persistent" binding. False (default) will register a standard activation-based binding. A persistent binding ignores the standard ruleset for UI input routing - the binding will be live immediately upon construction of the button.
- L1082 _private member_ `ECommonInputMode InputModeOverride = ECommonInputMode::Menu;` — `UPROPERTY(EditAnywhere, Category = Input, AdvancedDisplay)` — Set this to Game for special cases where an input action needs to be set for an in-game button.
- L1085 _private prototype_ `bool IsHoverSimulationOnTouchAvailable() const;` — `UFUNCTION()`
- L1087 _private prototype_ `void BuildStyles();`
- L1088 _private prototype_ `void SetButtonStyle();`
- L1091 _private prototype_ `void EnableButton();` — Enables this button (called in SetIsEnabled override)
- L1094 _private prototype_ `void DisableButton();` — Disables this button (called in SetIsEnabled override)
- L1096 _private prototype_ `void HandleImplicitFocusLost();`
- L1098 _private member_ `FText EnabledTooltipText;`
- L1099 _private member_ `FText DisabledTooltipText;`
- L1103 _private member_ `TObjectPtr<UMaterialInstanceDynamic> SingleMaterialStyleMID;` — `UPROPERTY(Transient)` — The dynamic material instance of the material set by the single material style, if specified.
- L1107 _private member_ `FButtonStyle NormalStyle;` — `UPROPERTY()` — Internally managed and applied style to use when not selected
- L1111 _private member_ `FButtonStyle SelectedStyle;` — `UPROPERTY()` — Internally managed and applied style to use when selected
- L1115 _private member_ `FButtonStyle DisabledStyle;` — `UPROPERTY()` — Internally managed and applied style to use when disabled
- L1119 _private member_ `FButtonStyle LockedStyle;` — `UPROPERTY()` — Internally managed and applied style to use when locked
- L1122 _private member_ `uint32 bStopDoubleClickPropagation : 1;` — `UPROPERTY(Transient)`
- L1128 _private member_ `TWeakObjectPtr<class UCommonButtonInternalBase> RootButton;` — The actual UButton that we wrap this user widget into. Allows us to get user widget customization and built-in button functionality.
- L1130 _private member_ `mutable FCommonButtonEvent OnClickedEvent;`
- L1131 _private member_ `mutable FCommonButtonEvent OnDoubleClickedEvent;`
- L1132 _private member_ `mutable FCommonButtonEvent OnPressedEvent;`
- L1133 _private member_ `mutable FCommonButtonEvent OnReleasedEvent;`
- L1134 _private member_ `mutable FCommonButtonEvent OnHoveredEvent;`
- L1135 _private member_ `mutable FCommonButtonEvent OnUnhoveredEvent;`
- L1136 _private member_ `mutable FCommonButtonEvent OnFocusReceivedEvent;`
- L1137 _private member_ `mutable FCommonButtonEvent OnFocusLostEvent;`
- L1138 _private member_ `mutable FCommonButtonEvent OnLockClickedEvent;`
- L1139 _private member_ `mutable FCommonButtonEvent OnLockDoubleClickedEvent;`
- L1140 _private member_ `mutable FOnDragDetected OnDragDetectedEvent;`
- L1141 _private member_ `mutable FOnDragEnter OnDragEnterEvent;`
- L1142 _private member_ `mutable FOnDragLeave OnDragLeaveEvent;`
- L1143 _private member_ `mutable FOnDragOver OnDragOverEvent;`
- L1144 _private member_ `mutable FOnDrop OnDropEvent;`
- L1146 _private member_ `mutable FOnIsSelectedChanged OnIsSelectedChangedEvent;`
- L1158 _protected member_ `TObjectPtr<UCommonActionWidget> InputActionWidget;` — `UPROPERTY(BlueprintReadOnly, Category = Input, meta = (BindWidget, OptionalWidget = true, AllowPrivateAccess = true))` — Optionally bound widget for visualization behavior of an input action; NOTE: If specified, will visualize according to the following algorithm: If TriggeringEnhancedInputAction is specified, visualize it else: If TriggeringInputAction is specified, visualize it else: If TriggeredInputAction is specified, visualize it else: Visualize the default click action while hovered

#### class `UWidgetLockedStateRegistration`  
`class UWidgetLockedStateRegistration : public UWidgetBinaryStateRegistration`  
_L1162-1184_
- reflection: `UCLASS(Transient)`
- inherits: `UWidgetBinaryStateRegistration`
- L1169 _public member_ `static inline FWidgetStateBitfield Bit;` — Post-load initialized bit corresponding to this binary state
- L1171 _public member_ `static const inline FName StateName = FName("Loc`
- L1174 _public prototype_ `virtual FName GetStateName() const override;`
- L1175 _public prototype_ `virtual bool GetRegisteredWidgetState(const UWidget* InWidget) const override;`
- L1182 _protected prototype_ `virtual void InitializeStaticBitfields() const override;`

#### Free symbols / members of external scopes

- L239 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FOnButtonDoubleClickedEvent);`
- L239 _prototype_ `DECLARE_DELEGATE_RetVal(FReply, FOnButtonDoubleClickedEvent);`
- L321 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCommonSelectedStateChangedBase, class UCommonButtonBase*, Button, bool, Selected);`
- L321 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCommonSelectedStateChangedBase, class UCommonButtonBase*, Button, bool, Selected);`
- L322 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonButtonBaseClicked, class UCommonButtonBase*, Button);`
- L322 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonButtonBaseClicked, class UCommonButtonBase*, Button);`
- L323 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonBaseOperationDynamic, class UCommonButtonBase*, Button, UDragDropOperation*, Operation);`
- L323 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonBaseOperationDynamic, class UCommonButtonBase*, Button, UDragDropOperation*, Operation);`
- L324 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnButtonBaseGeoOperationDynamic, class UCommonButtonBase*, Button, const FGeometry&, MyGeometry, UDragDropOperation*, Operation);`
- L324 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnButtonBaseGeoOperationDynamic, class UCommonButtonBase*, Button, const FGeometry&, MyGeometry, UDragDropOperation*, Operation);`
- L544 _delegate_ `DECLARE_EVENT(UCommonButtonBase, FCommonButtonEvent);`
- L565 _delegate_ `DECLARE_EVENT_OneParam(UCommonButtonBase, FOnIsSelectedChanged, bool);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonCustomNavigation.h` (Public)


#### class `UCommonCustomNavigation`  
`class UCommonCustomNavigation : public UBorder`  
_L14-41_
- reflection: `UCLASS(MinimalAPI, Config = CommonUI, DefaultConfig, ClassGroup = UI, meta = (Category = "Common UI", DisplayName = "Common Custom Navigation"))`
- inherits: `UBorder`
- desc: Exposes a bindable event that can be used to stomp default border navigation with custom behaviors.
- L19 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FOnCustomNavigationEvent, EUINavigation, NavigationType);`
- L23 _public member_ `FOnCustomNavigationEvent OnNavigationEvent;` — `UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))` — Return true if the Navigation has been handled
- L28 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L39 _protected prototype_ `bool OnNavigation(EUINavigation NavigationType);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`
- L19 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FOnCustomNavigationEvent, EUINavigation, NavigationType);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonDateTimeTextBlock.h` (Public)


#### class `UCommonDateTimeTextBlock`  
`class UCommonDateTimeTextBlock : public UCommonTextBlock`  
_L11-82_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCommonTextBlock`
- L16 _public prototype_ `UCommonDateTimeTextBlock(const FObjectInitializer& ObjectInitializer);`
- L18 _public prototype_ `DECLARE_EVENT(UCommonDateTimeTextBlock, FOnTimeCountDownCompletion);`
- L19 _public function_ `FOnTimeCountDownCompletion& OnTimeCountDownCompletion() const`
- L22 _public prototype_ `const FText GetPaletteCategory() override;`
- L25 _public prototype_ `virtual void SynchronizeProperties() override;`
- L28 _public prototype_ `void SetDateTimeValue(const FDateTime InDateTime, bool bShowAsCountdown, float InRefreshDelay = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "DateTime Text Block")`
- L31 _public prototype_ `void SetTimespanValue(const FTimespan InTimespan);` — `UFUNCTION(BlueprintCallable, Category = "DateTime Text Block")`
- L34 _public prototype_ `void SetCountDownCompletionText(const FText InCompletionText);` — `UFUNCTION(BlueprintCallable, Category = "DateTime Text Block")`
- L37 _public prototype_ `FDateTime GetDateTime() const;` — `UFUNCTION(BlueprintCallable, Category = "DateTime Text Block")`
- L41 _protected prototype_ `void UpdateUnderlyingText();`
- L43 _protected prototype_ `virtual FDateTime GetTimespanStartingTime() const;`
- L44 _protected prototype_ `virtual bool ShouldClearTimer(const FTimespan& TimeRemaining) const;`
- L46 _protected prototype_ `virtual TOptional<FText> FormatTimespan(const FTimespan& InTimespan) const;`
- L47 _protected prototype_ `virtual TOptional<FText> FormatDateTime(const FDateTime& InDateTime) const;`
- L49 _protected function_ `int32 GetLastDaysCount() const`
- L50 _protected function_ `int32 GetLastHoursCount() const`
- L57 _protected member_ `FText CustomTimespanFormat;` — `UPROPERTY(EditAnywhere, Category = "Custom Timespan")` — Supplies a custom timespan format to use if desired Supported arguments include {Days}, {Hours}, {Minutes}, and {Seconds}
- L63 _protected member_ `bool bCustomTimespanLeadingZeros = false;` — `UPROPERTY(EditAnywhere, Category = "Custom Timespan")` — If the custom timespan should use a leading zero for values, ie "02"
- L68 _private member_ `FTimerHandle TimerTickHandle;` — Timer handle for timer-based ticking based on InterpolationUpdateInterval.
- L69 _private member_ `float LastTimerTickTime;`
- L71 _private member_ `FDateTime DateTime;`
- L72 _private member_ `bool bShowAsCountdown;`
- L73 _private member_ `int32 LastDaysCount;`
- L74 _private member_ `int32 LastHoursCount;`
- L76 _private member_ `bool bUseCountdownCompletionText;`
- L77 _private member_ `FText CountdownCompletionText;`
- L79 _private member_ `mutable FOnTimeCountDownCompletion OnTimeCountDownCompletionEvent;`
- L81 _private prototype_ `void TimerTick();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`
- L18 _delegate_ `DECLARE_EVENT(UCommonDateTimeTextBlock, FOnTimeCountDownCompletion);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonGameViewportClient.h` (Public)


#### class `UCommonGameViewportClient`  
`class UCommonGameViewportClient : public UGameViewportClient`  
_L24-99_
- reflection: `UCLASS(MinimalAPI, Within = Engine, transient, config = Engine)`
- inherits: `UGameViewportClient`
- desc: CommonUI Viewport to reroute input to UI first. Needed to allow CommonUI to route / handle inputs.
- L30 _public prototype_ `UCommonGameViewportClient(FVTableHelper& Helper);`
- L33 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;` — UGameViewportClient interface begin
- L34 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& Args) override;`
- L35 _public prototype_ `virtual bool InputTouch(FViewport* const InViewport, const FTouchId TouchId, const ETouchType::Type Type, const FVector2D& TouchLocation, const float Force, const uint64 Timestamp) override;`
- L36 _public prototype_ `virtual void MouseMove(FViewport* InViewport, int32 X, int32 Y) override;`
- L37 _public prototype_ `virtual void CapturedMouseMove(FViewport* InViewport, int32 X, int32 Y) override;`
- L38 _public prototype_ `virtual TOptional<TSharedRef<SWidget>> MapCursor(FViewport* Viewport, const FCursorReply& CursorReply) override;`
- L42 _public function_ `void SetUseVirtualPointerCursor(bool bEnabled)` — When true, MapCursor redirects any non-None cursor type to Custom so the virtual pointer widget is always displayed.
- L44 _public function_ `FOnRerouteInputDelegate& OnRerouteInput()`
- L45 _public function_ `FOnRerouteAxisDelegate& OnRerouteAxis()`
- L49 _public function_ `FOnRerouteTouchInputDelegate& OnRerouteTouchInput()` — `UE_DEPRECATED(5.8, "Use GetRerouteTouchRegistration() instead.")`
- L55 _public function_ `FTouchRerouteDelegate::RegistrationType& GetRerouteTouchRegistration()`
- L60 _public function_ `FOnRerouteInputDelegate& OnRerouteBlockedInput()`
- L63 _public prototype_ `virtual void HandleRerouteInput(FInputDeviceId DeviceId, FKey Key, EInputEvent EventType, FReply& Reply);` — Default Handler for Key input.
- L66 _public prototype_ `virtual void HandleRerouteAxis(FInputDeviceId DeviceId, FKey Key, float Delta, FReply& Reply);` — Default Handler for Axis input.
- L69 _public prototype_ `virtual void HandleRerouteTouch(FInputDeviceId DeviceId, uint32 TouchId, ETouchType::Type TouchType, const FVector2D& TouchLocation, FReply& Reply) final;` — `UE_DEPRECATED(5.8, "Use the version which takes a FTouchId instead.")`
- L72 _public prototype_ `virtual void HandleRerouteTouch(FTouchId TouchId, ETouchType::Type TouchType, const FVector2D& TouchLocation, FReply& Reply);` — Default Handler for Touch input.
- L76 _protected function_ `FTouchRerouteDelegate& GetRerouteTouchDelegate()`
- L82 _protected prototype_ `virtual bool IsKeyPriorityAboveUI(const FInputKeyEventArgs& EventArgs);` — Console window & fullscreen shortcut have higher priority than UI
- L84 _protected member_ `FOnRerouteInputDelegate RerouteInput;`
- L85 _protected member_ `FOnRerouteAxisDelegate RerouteAxis;`
- L89 _protected member_ `FOnRerouteTouchInputDelegate RerouteTouchInput;` — `UE_DEPRECATED(5.8, "Use GetRerouteTouchDelegate() instead.")`
- L92 _protected member_ `FOnRerouteInputDelegate RerouteBlockedInput;`
- L96 _private member_ `bool bUseVirtualPointerCursor = false;`
- L98 _private member_ `FTouchRerouteDelegate RerouteTouchDelegate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`
- L12 _delegate_ `DECLARE_DELEGATE_FourParams(FOnRerouteInputDelegate, FInputDeviceId , FKey , EInputEvent , FReply& );`
- L12 _prototype_ `DECLARE_DELEGATE_FourParams(FOnRerouteInputDelegate, FInputDeviceId , FKey , EInputEvent , FReply& );`
- L13 _delegate_ `DECLARE_DELEGATE_FourParams(FOnRerouteAxisDelegate, FInputDeviceId , FKey , float , FReply& );`
- L13 _prototype_ `DECLARE_DELEGATE_FourParams(FOnRerouteAxisDelegate, FInputDeviceId , FKey , float , FReply& );`
- L16 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnRerouteTouchInputDelegate, FInputDeviceId , uint32 , ETouchType::Type , const FVector2D& , FReply& );`
- L16 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnRerouteTouchInputDelegate, FInputDeviceId , uint32 , ETouchType::Type , const FVector2D& , FReply& );` — `UE_DEPRECATED(5.8, "Use the version which takes an FTouchId instead (FTouchRerouteDelegate).")`
- L18 _delegate_ `DECLARE_DELEGATE_FourParams(FTouchRerouteDelegate, FTouchId , ETouchType::Type , const FVector2D& , FReply& );`
- L18 _prototype_ `DECLARE_DELEGATE_FourParams(FTouchRerouteDelegate, FTouchId , ETouchType::Type , const FVector2D& , FReply& );`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonHardwareVisibilityBorder.h` (Public)


#### class `UCommonHardwareVisibilityBorder`  
`class UCommonHardwareVisibilityBorder : public UCommonBorder`  
_L19-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommonBorder`
- desc: A container that controls visibility based on Platform, Input
- L29 _protected member_ `FGameplayTagQuery VisibilityQuery;` — `UPROPERTY(EditAnywhere, Category = "Visibility", meta=(Categories="Input,Platform.Trait"))`
- L32 _protected member_ `ESlateVisibility VisibleType;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L35 _protected member_ `ESlateVisibility HiddenType;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L39 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L42 _protected prototype_ `void UpdateVisibility(UCommonUIVisibilitySubsystem* VisSystem = nullptr);`
- L44 _protected prototype_ `void ListenToInputMethodChanged();`
- L46 _protected prototype_ `void HandleInputMethodChanged(UCommonUIVisibilitySubsystem*);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonHierarchicalScrollBox.h` (Public)


#### class `UCommonHierarchicalScrollBox`  
`class UCommonHierarchicalScrollBox : public UScrollBox`  
_L14-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScrollBox`
- desc: An arbitrary scrollable collection of widgets.  Great for presenting 10-100 widgets in a list.  Doesn't support virtualization.
- L20 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonLazyImage.h` (Public)


#### class `UCommonLazyImage`  
`class UCommonLazyImage : public UImage`  
_L25-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UImage`
- desc: A special Image widget that can show unloaded images and takes care of the loading for you! UCommonLazyImage is another wrapper for SLoadGuard, but it only handles image loading and a throbber during loading. If this class changes to show any text, by default it will have CoreStyle styling
- L30 _public prototype_ `virtual void SetBrush(const FSlateBrush& InBrush) override;`
- L31 _public prototype_ `virtual void SetBrushFromAsset(USlateBrushAsset* Asset) override;`
- L32 _public prototype_ `virtual void SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize = false) override;`
- L33 _public prototype_ `virtual void SetBrushFromTextureDynamic(UTexture2DDynamic* Texture, bool bMatchSize = false) override;`
- L34 _public prototype_ `virtual void SetBrushFromMaterial(UMaterialInterface* Material) override;`
- L38 _public prototype_ `void SetBrushFromLazyTexture(const TSoftObjectPtr<UTexture2D>& LazyTexture, bool bMatchSize = false);` — `UFUNCTION(BlueprintCallable, Category = LazyImage)` — Set the brush from a lazy texture asset pointer - will load the texture as needed.
- L42 _public prototype_ `void SetBrushFromLazyMaterial(const TSoftObjectPtr<UMaterialInterface>& LazyMaterial);` — `UFUNCTION(BlueprintCallable, Category = LazyImage)` — Set the brush from a lazy material asset pointer - will load the material as needed.
- L46 _public prototype_ `void SetBrushFromLazyDisplayAsset(const TSoftObjectPtr<UObject>& LazyObject, bool bMatchTextureSize = false);` — `UFUNCTION(BlueprintCallable, Category = LazyImage)` — Set the brush from a string asset ref only - expects the referenced asset to be a texture or material.
- L49 _public prototype_ `bool IsLoading() const;` — `UFUNCTION(BlueprintCallable, Category = LazyImage)`
- L59 _public prototype_ `void SetMaterialTextureParamName(FName TextureParamName);` — `UFUNCTION(BlueprintCallable, Category = LazyImage)` — Establishes the name of the texture parameter on the currently applied brush material to which textures should be applied. Does nothing if the current brush resource object is not a material. Note: that this is cleared out automatically if/when a new material is established on the brush. You must call this function again after doing so if the new material has a texture param.
- L61 _public function_ `FOnLoadGuardStateChangedEvent& OnLoadingStateChanged()`
- L64 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override final;`
- L65 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L66 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L67 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L69 _protected prototype_ `virtual void CancelImageStreaming() override;`
- L70 _protected prototype_ `virtual void OnImageStreamingStarted(TSoftObjectPtr<UObject> SoftObject) override;`
- L71 _protected prototype_ `virtual void OnImageStreamingComplete(TSoftObjectPtr<UObject> LoadedSoftObject) override;`
- L73 _protected prototype_ `virtual TSharedRef<SWidget> RebuildImageWidget();`
- L76 _protected prototype_ `virtual const FText GetPaletteCategory() override;`
- L77 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L80 _protected prototype_ `void SetIsLoading(bool bIsLoading);`
- L81 _protected prototype_ `void ShowDefaultImage();`
- L84 _private prototype_ `void HandleLoadGuardStateChanged(bool bIsLoading);`
- L86 _private prototype_ `void SetBrushObjectInternal(UMaterialInterface* Material);`
- L87 _private prototype_ `void SetBrushObjectInternal(UTexture* Texture, bool bMatchSize = false);`
- L91 _private member_ `bool bShowLoading = false;` — `UPROPERTY(EditAnywhere, Category = LoadPreview)`
- L95 _private member_ `FSlateBrush LoadingBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L98 _private member_ `FSlateBrush LoadingThrobberBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L106 _private member_ `FName MaterialTextureParamName;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Appearance)` — If this image uses a material that a texture should be applied to, this is the name of the material param to use. I.e. if this property is not blank, the resource object of our brush is a material, and we are given a lazy texture, that texture will be assigned to the texture param on the material instead of replacing the material outright on the brush.
- L109 _private member_ `FOnLoadGuardStateChangedDynamic BP_OnLoadingStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = LazyImage, meta = (DisplayName = "On Loading State Changed", ScriptName = "OnLoadingStateChanged"))`
- L111 _private member_ `TSharedPtr<SLoadGuard> MyLoadGuard;`
- L112 _private member_ `FOnLoadGuardStateChangedEvent OnLoadingStateChangedEvent;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonLazyWidget.h` (Public)


#### class `UCommonLazyWidget`  
`class UCommonLazyWidget : public UWidget`  
_L21-147_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A widget that can async load and create an instance of a UserWidget.
- L26 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWidgetCreated, UUserWidget*, Widget);`
- L30 _public prototype_ `void SetLazyContent(const TSoftClassPtr<UUserWidget> SoftWidget);` — `UFUNCTION(BlueprintCallable, Category = LazyContent)` — Loads and creates an instance of SoftWidget.
- L34 _public prototype_ `void SetLazyContentWithCallback(const TSoftClassPtr<UUserWidget> SoftWidget, const FOnWidgetCreated& OnCreatedCallback);` — `UFUNCTION(BlueprintCallable, Category = LazyContent)` — Loads and creates an instance of SoftWidget.
- L38 _public prototype_ `void LoadLazyContent();` — `UFUNCTION(BlueprintCallable, Category = LazyContent)` — Loads and creates an instance of the WidgetClass property.
- L41 _public function_ `template<typename TWidget = UUserWidget> void LoadLazyContent(TFunction<void(TWidget&)>&& InitInstanceFunc)`
- L51 _public function_ `UUserWidget* GetContent() const` — `UFUNCTION(BlueprintCallable, Category = LazyContent)` — Gets the attached Content which was instanced from an async loaded TSoftClassPtr.
- L54 _public function_ `template <class TContent = UUserWidget> TContent* GetContent() const`
- L60 _public prototype_ `bool IsLoading() const;` — `UFUNCTION(BlueprintCallable, Category = LazyContent)`
- L62 _public function_ `FOnLazyContentChangedEvent& OnContentChanged()`
- L63 _public function_ `FOnLoadGuardStateChangedEvent& OnLoadingStateChanged()`
- L67 _protected function_ `template <typename TWidget = UUserWidget> void SetLazyContentInternal(const TSoftClassPtr<UUserWidget> SoftWidget, TFunction<void(TWidget&)>&& InitInstanceFunc)`
- L103 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L104 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L105 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L106 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L108 _protected prototype_ `void SetForceShowSpinner(bool bShowLoading);`
- L110 _protected prototype_ `void CancelStreaming();`
- L111 _protected prototype_ `void OnStreamingStarted(TSoftClassPtr<UObject> SoftObject);`
- L112 _protected prototype_ `void OnStreamingComplete(TSoftClassPtr<UObject> LoadedSoftObject);`
- L115 _protected prototype_ `virtual const FText GetPaletteCategory() override;`
- L119 _private prototype_ `void SetLoadedContent(UUserWidget* InContent);`
- L120 _private prototype_ `void RequestAsyncLoad(TSoftClassPtr<UObject> SoftObject, TFunction<void()>&& Callback);`
- L121 _private prototype_ `void RequestAsyncLoad(TSoftClassPtr<UObject> SoftObject, FStreamableDelegate DelegateToCall);`
- L122 _private prototype_ `void HandleLoadGuardStateChanged(bool bIsLoading);`
- L125 _private member_ `TSoftClassPtr<UUserWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, Category = LazyWidget)`
- L129 _private member_ `FSlateBrush LoadingThrobberBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The loading throbber brush
- L132 _private member_ `FSlateBrush LoadingBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L135 _private member_ `TObjectPtr<UUserWidget> Content;` — `UPROPERTY(Transient)`
- L137 _private member_ `TSharedPtr<FStreamableHandle> StreamingHandle;`
- L138 _private member_ `FSoftObjectPath StreamingObjectPath;`
- L141 _private member_ `FOnLoadGuardStateChangedDynamic BP_OnLoadingStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = LazyWidget, meta = (DisplayName = "On Loading State Changed", ScriptName = "OnLoadingStateChanged"))`
- L143 _private member_ `TSharedPtr<SLoadGuard> MyLoadGuard;`
- L144 _private member_ `FOnLoadGuardStateChangedEvent OnLoadingStateChangedEvent;`
- L146 _private member_ `FOnLazyContentChangedEvent OnContentChangedEvent;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLazyContentChangedEvent, UUserWidget*);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLazyContentChangedEvent, UUserWidget*);`
- L26 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWidgetCreated, UUserWidget*, Widget);`
- L79 _function_ `RequestAsyncLoad(SoftWidget, [WeakThis, SoftWidget, InitInstanceFunc = MoveTemp(InitInstanceFunc)]() { if (ThisClass* StrongThis = WeakThis.Get()) { if (ensureMsgf(SoftWidget.Get(), TEXT("Failed to load %s"), *SoftWidget.ToSoftObjectPath().ToString())) {` (scope `UCommonLazyWidget::SetLazyContentInternal`)

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonListView.h` (Public)


#### class `SCommonListView`  
`template <typename ItemType> class SCommonListView : public SListView<ItemType>`  
_L22-428_
- inherits: `SListView<ItemType>`
- L25 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L99 _public function_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override`
- L195 _public function_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override`
- L356 _public function_ `virtual void NotifyItemScrolledIntoView() override`
- L382 _public function_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override`
- L388 _public function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override`
- L400 _public function_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L413 _public function_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L423 _protected member_ `TWeakPtr<SWidget> IntraEntrySourceWidget;` — Last sub-widget that held focus within an entry. Written by OnFocusChanging; consumed by OnNavigation intra-entry navigation and the cross-list source precision correction.
- L425 _protected member_ `bool bScrollToSelectedOnFocus = true;`

#### class `UCommonListView`  
`class UCommonListView : public UListView`  
_L435-452_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UListView`
- L440 _public prototype_ `UCommonListView(const FObjectInitializer& ObjectInitializer);`
- L443 _public prototype_ `void SetEntrySpacing(float InEntrySpacing);` — `UFUNCTION(BlueprintCallable, Category = ListView)`
- L446 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L450 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget() override;`
- L451 _protected prototype_ `virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonLoadGuard.h` (Public)


#### class `SLoadGuard`  
`class SLoadGuard : public SCompoundWidget`  
_L28-93_
- inherits: `SCompoundWidget`
- L30 _private function_ `SLATE_BEGIN_ARGS(SLoadGuard) : _ThrobberHAlign(HAlign_Center) , _Throbber(nullptr) , _GuardTextStyle(nullptr) , _GuardBackgroundBrush(nullptr)`
- L48 _public prototype_ `SLoadGuard();`
- L49 _public prototype_ `void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L52 _public prototype_ `void SetForceShowSpinner(bool bInForceShowSpinner);`
- L53 _public function_ `bool IsLoading() const`
- L55 _public prototype_ `void SetContent(const TSharedRef<SWidget>& InContent);`
- L56 _public prototype_ `void SetThrobberHAlign(EHorizontalAlignment InHAlign);`
- L57 _public prototype_ `void SetThrobber(const TSharedPtr<SWidget>& InThrobber);`
- L58 _public prototype_ `void SetGuardText(const FText& InText);`
- L59 _public prototype_ `void SetGuardTextStyle(const FTextBlockStyle& InGuardTextStyle);`
- L60 _public prototype_ `void SetGuardBackgroundBrush(const FSlateBrush* InGuardBackground);`
- L66 _public prototype_ `void GuardAndLoadAsset(const TSoftObjectPtr<UObject>& InLazyAsset, FOnLoadGuardAssetLoaded OnAssetLoaded);` — Displays the loading spinner until the asset is loaded Will pass a casted pointer to the given asset in the lambda callback - could be nullptr if you provide an incompatible type or invalid asset.
- L69 _public function_ `template <typename ObjectType> void GuardAndLoadAsset(const TSoftObjectPtr<UObject>& InLazyAsset, TFunction<void(ObjectType*)> OnAssetLoaded)`
- L76 _public function_ `TSharedRef<SBorder> GetContentBorder() const`
- L79 _private prototype_ `void UpdateLoadingAppearance();`
- L81 _private member_ `TSoftObjectPtr<UObject> LazyAsset;`
- L83 _private member_ `TSharedPtr<SBorder> ContentBorder;`
- L84 _private member_ `TSharedPtr<SBorder> GuardBorder;`
- L85 _private member_ `TSharedPtr<STextBlock> GuardTextBlock;`
- L86 _private member_ `SHorizontalBox::FSlot* ThrobberSlot = nullptr;`
- L88 _private member_ `FOnLoadGuardStateChanged OnLoadingStateChanged;`
- L90 _private member_ `TSharedPtr<FStreamableHandle> StreamingHandle;`
- L91 _private member_ `bool bForceShowSpinner = false;`
- L92 _private member_ `bool bIsShowingSpinner = false;`

#### class `ULoadGuardSlot`  
`class ULoadGuardSlot : public UPanelSlot`  
_L101-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPanelSlot`
- desc: Virtually identical to a UBorderSlot, but unfortunately that assumes (fairly) that its parent widget is a UBorder.
- L106 _public prototype_ `virtual void SynchronizeProperties() override;`
- L107 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L109 _public prototype_ `void BuildSlot(TSharedRef<SLoadGuard> InLoadGuard);`
- L112 _public prototype_ `void SetPadding(FMargin InPadding);` — `UFUNCTION(BlueprintCallable, Category = "Layout|LoadGuard Slot")`
- L115 _public prototype_ `void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category = "Layout|LoadGuard Slot")`
- L118 _public prototype_ `void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category = "Layout|LoadGuard Slot")`
- L122 _private member_ `FMargin Padding;` — `UPROPERTY(EditAnywhere, Category = "Layout|LoadGuard Slot")`
- L125 _private member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Fill;` — `UPROPERTY(EditAnywhere, Category = "Layout|LoadGuard Slot")`
- L128 _private member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Fill;` — `UPROPERTY(EditAnywhere, Category = "Layout|LoadGuard Slot")`
- L130 _private member_ `TWeakPtr<SLoadGuard> LoadGuard;`

#### class `UCommonLoadGuard`  
`class UCommonLoadGuard : public UContentWidget`  
_L151-260_
- reflection: `UCLASS(MinimalAPI, Config = Game, DefaultConfig)`
- inherits: `UContentWidget`
- desc: The Load Guard behaves similarly to a Border, but with the ability to hide its primary content and display a loading spinner and optional message while needed content is loaded or otherwise prepared. Use GuardAndLoadAsset to automatically display the loading state until the asset is loaded (then the content widget will be displayed). For other applications (ex: waiting for an async backend call to complete), you can manually set the loading state of the guard.
- L156 _public prototype_ `UCommonLoadGuard(const FObjectInitializer& Initializer);`
- L158 _public prototype_ `virtual void PostLoad() override;`
- L159 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L161 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L162 _public prototype_ `virtual void SynchronizeProperties() override;`
- L164 _public function_ `virtual UClass* GetSlotClass() const override`
- L165 _public prototype_ `virtual void OnSlotAdded(UPanelSlot* NewSlot) override;`
- L166 _public prototype_ `virtual void OnSlotRemoved(UPanelSlot* OldSlot) override;`
- L169 _public prototype_ `void SetLoadingText(const FText& InLoadingText);` — `UFUNCTION(BlueprintCallable, Category = LoadGuard)`
- L172 _public prototype_ `void SetIsLoading(bool bInIsLoading);` — `UFUNCTION(BlueprintCallable, Category = LoadGuard)`
- L175 _public prototype_ `bool IsLoading() const;` — `UFUNCTION(BlueprintCallable, Category = LoadGuard)`
- L182 _public function_ `template <typename ObjectType = UObject> void GuardAndLoadAsset(const TSoftObjectPtr<ObjectType>& InLazyAsset, TFunction<void(ObjectType*)> OnAssetLoaded)` — Displays the loading spinner until the asset is loaded Will pass a casted pointer to the given asset in the lambda callback - could be nullptr if you provide an incompatible type or invalid asset.
- L190 _public function_ `void GuardAndLoadAsset(const TSoftObjectPtr<UObject>& InLazyAsset, FOnLoadGuardAssetLoaded OnAssetLoaded)`
- L198 _public function_ `FOnLoadGuardStateChangedEvent& OnLoadingStateChanged()`
- L201 _public prototype_ `virtual void OnCreationFromPalette() override;`
- L202 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L205 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAssetLoaded, UObject*, Object);`
- L208 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L212 _protected member_ `bool bShowLoading = false;` — `UPROPERTY(EditAnywhere, Category = LoadGuard)`
- L217 _private prototype_ `void BP_GuardAndLoadAsset(const TSoftObjectPtr<UObject>& InLazyAsset, const FOnAssetLoaded& OnAssetLoaded);` — `UFUNCTION(BlueprintCallable, Category = LoadGuard, meta = (DisplayName = "Guard and Load Asset", ScriptName="GuardAndLoadAsset", AllowPrivateAccess = true))`
- L219 _private prototype_ `void HandleLoadingStateChanged(bool bIsLoading);`
- L223 _private member_ `FSlateBrush LoadingBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = LoadGuardThrobber)` — The background brush to display while loading the content
- L227 _private member_ `FSlateBrush LoadingThrobberBrush;` — `UPROPERTY(EditAnywhere, Category = LoadGuardThrobber)` — The loading throbber brush
- L231 _private member_ `TEnumAsByte<EHorizontalAlignment> ThrobberAlignment;` — `UPROPERTY(EditAnywhere, Category = LoadGuardThrobber)` — The horizontal alignment of the loading throbber & message
- L235 _private member_ `FMargin ThrobberPadding;` — `UPROPERTY(EditAnywhere, Category = LoadGuardThrobber)` — The padding of the loading throbber & message
- L239 _private member_ `FText LoadingText;` — `UPROPERTY(EditAnywhere, Category = LoadGuardText)` — Loading message to display alongside the throbber
- L243 _private member_ `TSubclassOf<UCommonTextStyle> TextStyle;` — `UPROPERTY(EditAnywhere, Category = LoadGuardText)` — Style to apply to the loading message
- L246 _private member_ `FOnLoadGuardStateChangedDynamic BP_OnLoadingStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = LoadGuard, meta = (DisplayName = "On Loading State Changed"))`
- L249 _private member_ `FSoftObjectPath SpinnerMaterialPath;` — `UPROPERTY(Config)`
- L254 _private member_ `bool bStyleNoLongerNeedsConversion;` — `UPROPERTY()` — Used to track widgets that were created before changing the default style pointer to null
- L257 _private member_ `TSharedPtr<SLoadGuard> MyLoadGuard;`
- L259 _private member_ `FOnLoadGuardStateChangedEvent OnLoadingStateChangedEvent;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONUI_API`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLoadGuardStateChanged, bool);`
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLoadGuardStateChanged, bool);`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLoadGuardAssetLoaded, UObject*);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLoadGuardAssetLoaded, UObject*);`
- L71 _function_ `GuardAndLoadAsset(InLazyAsset, FOnLoadGuardAssetLoaded::CreateLambda([OnAssetLoaded](UObject* LoadedObject) { OnAssetLoaded(Cast<ObjectType>(LoadedObject)); }));` (scope `SLoadGuard::GuardAndLoadAsset`)
- L139 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadGuardStateChangedEvent, bool);`
- L139 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadGuardStateChangedEvent, bool);`
- L140 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadGuardStateChangedDynamic, bool, bIsLoading);`
- L140 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadGuardStateChangedDynamic, bool, bIsLoading);`
- L205 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAssetLoaded, UObject*, Object);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonNativeListItem.h` (Public)


#### class `FCommonNativeListItem`  
`class FCommonNativeListItem : public TSharedFromThis<FCommonNativeListItem>`  
_L13-41_
- inherits: `TSharedFromThis<FCommonNativeListItem>`
- desc: Base item class for any UMG ListViews based on native, non-UObject items. Exclusively intended to provide bare-bones RTTI to the items to allow one array of list items to be multiple classes without needing a different, more awkward identification mechanism or an abstract virtual of every conceivable method in the base list item class
- L16 _public prototype_ `virtual ~FCommonNativeListItem() = default;`
- L19 _public function_ `template <typename ListItemT> bool IsDerivedFrom() const`
- L26 _public function_ `template <typename ListItemT> TSharedPtr<ListItemT> AsTypedItem()`
- L37 _public function_ `virtual FString GetStaticItemTypeName() const`
- L39 _protected function_ `static FName StaticItemType()`
- L40 _protected function_ `virtual bool IsDerivedInternal(FName ItemTypeName) const`

#### Free symbols / members of external scopes

- L46 _macro_ `#define DERIVED_LIST_ITEM(ItemType, ParentItemType) \` — Put this at the top of any list item classes that ultimately derive from FCommonNativeListItem.

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonNumericTextBlock.h` (Public)


#### struct `FCommonNumberFormattingOptions`  
`struct FCommonNumberFormattingOptions`  
_L11-52_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public function_ `FCommonNumberFormattingOptions() : RoundingMode(ERoundingMode::HalfFromZero) , AlwaysSign(false) , UseGrouping(true) , MinimumIntegralDigits(FNumberFormattingOptions::DefaultNoGrouping().MinimumIntegralDigits) , MaximumIntegralDigits(FNumberFormattingOptions::DefaultNoGrouping().MaximumIntegralDigits) , MinimumFractionalDigits(0) , MaximumFractionalDigits(0)`
- L27 _public member_ `TEnumAsByte<ERoundingMode> RoundingMode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating")` — The rounding mode to be used when the actual value can not be precisely represented due to restrictions on the number of integral or fractional digits. See values for details.
- L31 _public member_ `bool AlwaysSign;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating")` — Should the numerals always display the sign. IE: "+1"
- L35 _public member_ `bool UseGrouping;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating")` — Should the numerals use group separators. IE: "1,000,000"
- L39 _public member_ `int32 MinimumIntegralDigits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating", meta = (ClampMin = "0"))` — How many integral digits should be shown at minimum? May cause digit "padding". IE: A minimum of 3 integral digits means 1.0 -> "001".
- L43 _public member_ `int32 MaximumIntegralDigits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating", meta = (ClampMin = "0"))` — How many integral digits should be shown at maximum? May cause rounding. IE: A maximum of 2 integral digits means 100.0 -> "99".
- L47 _public member_ `int32 MinimumFractionalDigits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating", meta = (ClampMin = "0"))` — How many fractional digits should be shown at minimum? May cause digit "padding". IE: A minimum of 2 fractional digits means 1.0 -> "1.00".
- L51 _public member_ `int32 MaximumFractionalDigits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating", meta = (ClampMin = "0"))` — How many fractional digits should be shown at maximum? May cause rounding. IE: HalfFromZero rounding and a maximum of 2 fractional digits means 0.009 -> "0.01".

#### enum `ECommonNumericType`  
`enum class ECommonNumericType : uint8`  
_L55-61_
- reflection: `UENUM(BlueprintType)`
- L57 _public enumerator_ `Number`
- L58 _public enumerator_ `Percentage`
- L59 _public enumerator_ `Seconds`
- L60 _public enumerator_ `Distance`

#### class `UCommonNumericTextBlock`  
`class UCommonNumericTextBlock : public UCommonTextBlock`  
_L67-226_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCommonTextBlock`
- desc: Numeric text block that provides interpolation, and some type support (numbers, percents, seconds, distance).
- L72 _public prototype_ `UCommonNumericTextBlock(const FObjectInitializer& ObjectInitializer);`
- L74 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L75 _public prototype_ `virtual void PostLoad() override;`
- L79 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const;`
- L81 _public prototype_ `const FText GetPaletteCategory() override;`
- L84 _public prototype_ `virtual void SynchronizeProperties() override;`
- L88 _public prototype_ `float GetTargetValue() const;` — `UFUNCTION(BlueprintCallable, Category = "Numeric Text Block")` — Returns the value this widget will ultimately show if it is interpolating, or the current value if it is not.
- L92 _public prototype_ `void SetCurrentValue(const float NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Numeric Text Block")` — Sets the current numeric value. NOTE: Cancels any ongoing interpolation!
- L105 _public prototype_ `void InterpolateToValue(const float TargetValue, float MaximumInterpolationDuration = 3.0f, float MinimumChangeRate = 1.0f, float OutroOffset = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Numeric Interpolation")` — Starts an ongoing process of interpolating the current numeric value to the specified target value. The interpolation process may take the specified maximum duration or complete sooner if the minimum change rate causes the target to be reached prematurely. Optionally, an outro duration can be specified in order to trigger an outro event before interpolation completes. TargetValue					The value to be interpolated to. MaximumInterpolationDuration	The duration, in seconds, for the interpolation to take, at most. Must be greater than 0. MinimumChangeRate			The minimum change in numeric value per second. Must be greater than or equal to 0. OutroDuration				The time offset, in seconds, *before* the end of the InterpolationDuration elapses, at which to trigger an outro event. Must be less than or equal to MaximumInterpolationDuration
- L108 _public prototype_ `bool IsInterpolatingNumericValue() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Numeric Interpolation")`
- L110 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInterpolationStarted, UCommonNumericTextBlock*, NumericTextBlock);`
- L113 _public member_ `FOnInterpolationStarted OnInterpolationStartedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Numeric Interpolation")` — Event triggered when interpolation has started.
- L115 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInterpolationUpdated, UCommonNumericTextBlock*, NumericTextBlock, float, LastValue, float, NewValue);`
- L118 _public member_ `FOnInterpolationUpdated OnInterpolationUpdatedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Numeric Interpolation")` — Event triggered when interpolation has updated.
- L120 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOutro, UCommonNumericTextBlock*, NumericTextBlock);`
- L123 _public member_ `FOnOutro OnOutroEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Numeric Interpolation")` — Event triggered at a specified time before the interpolation completes, for "outro" purposes.
- L125 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInterpolationEnded, UCommonNumericTextBlock*, NumericTextBlock, const bool, HadCompleted);`
- L128 _public member_ `FOnInterpolationEnded OnInterpolationEndedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Numeric Interpolation")` — Event triggered when interpolation has ended.
- L132 _public member_ `float CurrentNumericValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeric Text Block")` — The current numeric value being formatted for display, potentially being interpolated from. NOTE: The displayed text is very likely not identical to this value, due to formatting.
- L135 _public prototype_ `void SetNumericType(ECommonNumericType InNumericType);` — `UFUNCTION(BlueprintCallable, Category = "Numeral Formating")`
- L138 _public member_ `ECommonNumericType NumericType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formating")`
- L142 _public member_ `FCommonNumberFormattingOptions FormattingSpecification;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeral Formatting")` — The specifications for how the current numeric value should be formatted in to numeral text.
- L146 _public member_ `float EaseOutInterpolationExponent;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeric Interpolation", meta = (ClampMin = "1.0"))` — Exponent parameter for the "ease out" interpolation curve. Must be > 0, but should be > 1 in order to "ease out".
- L150 _public member_ `float InterpolationUpdateInterval;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Numeric Interpolation", meta = (ClampMin = "0.0"))` — The desired interval, in seconds, between interpolation updates. 0.0 implies per-frame updates. NOTE: Interpolation updates may occur further apart due to tick rates.
- L158 _public member_ `float PostInterpolationShrinkDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Size Interpolation", meta = (ClampMin = "0.0"))` — The desired width of the formatted text may change rapidly and erratically during interpolation due to font glyph dimensions. To combat this, the desired width of the text will never shrink during interpolation. Once interpolation completes, the desired width will shrink over the duration specified.
- L161 _public member_ `bool PerformSizeInterpolation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Size Interpolation")`
- L165 _protected prototype_ `void UpdateUnderlyingText();`
- L166 _protected prototype_ `virtual FText FormatText(float InCurrentNumericValue, const FNumberFormattingOptions& InNumberFormattingOptions) const;`
- L169 _private prototype_ `FNumberFormattingOptions MakeNumberFormattingOptions() const;`
- L171 _private prototype_ `float CalculateInterpolationDuration(const float InTargetValue, const float InMinimumChangeRate, const float InMaximumInterpolationDuration) const;`
- L173 _private prototype_ `void OnTimerTick();`
- L174 _private prototype_ `void Tick(float DeltaTime);`
- L176 _private prototype_ `void EnterNumericInterpolation(const float InitialValue, const float FinalValue, const float Duration, const float OutroOffset);`
- L177 _private prototype_ `void UpdateNumericInterpolation();`
- L178 _private prototype_ `void ExitNumericInterpolation(const bool HasCompleted = false);`
- L180 _private prototype_ `void EnterSizeInterpolation(const float Duration);`
- L181 _private prototype_ `void UpdateSizeInterpolation();`
- L182 _private prototype_ `void ExitSizeInterpolation();`
- L184 _private prototype_ `void CancelInterpolation();`
- L189 _private member_ `bool IsPercentage_DEPRECATED;` — `UPROPERTY()` — Should the current numeric value be presented as a percentage? IE: 1.0 -> "100%"
- L197 _private member_ `} CurrentInterpolationState;`
- L200 _private member_ `FTimerHandle TimerTickHandle;` — Timer handle for timer-based ticking based on InterpolationUpdateInterval.
- L201 _private member_ `float LastTimerTickTime;`
- L207 _private member_ `} InterpolationState;`
- L218 _private member_ `} NumericInterpolationState;`
- L225 _private member_ `} SizeInterpolationState;`

#### enum `UCommonNumericTextBlock::EInterpolationState`  
`enum class EInterpolationState`  
_L192-197_
- desc: Enum for interpolation state machine.
- L194 _public enumerator_ `None`
- L195 _public enumerator_ `NumericInterpolation`
- L196 _public enumerator_ `SizeInterpolation`

#### struct `UCommonNumericTextBlock::(anonymous)`  
``  
_L205-207_

#### struct `UCommonNumericTextBlock::(anonymous)`  
``  
_L212-218_

#### struct `UCommonNumericTextBlock::(anonymous)`  
``  
_L222-225_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`
- L110 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInterpolationStarted, UCommonNumericTextBlock*, NumericTextBlock);`
- L115 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInterpolationUpdated, UCommonNumericTextBlock*, NumericTextBlock, float, LastValue, float, NewValue);`
- L120 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOutro, UCommonNumericTextBlock*, NumericTextBlock);`
- L125 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInterpolationEnded, UCommonNumericTextBlock*, NumericTextBlock, const bool, HadCompleted);`
- L206 _member_ `float ElapsedStateDuration;` (scope `UCommonNumericTextBlock::__anon77bb1c160108`)
- L213 _member_ `float SourceValue;` (scope `UCommonNumericTextBlock::__anon77bb1c160208`)
- L214 _member_ `float DestinationValue;` (scope `UCommonNumericTextBlock::__anon77bb1c160208`)
- L215 _member_ `float OutroOffset;` (scope `UCommonNumericTextBlock::__anon77bb1c160208`)
- L216 _member_ `bool HasTriggeredOutro;` (scope `UCommonNumericTextBlock::__anon77bb1c160208`)
- L217 _member_ `float Duration;` (scope `UCommonNumericTextBlock::__anon77bb1c160208`)
- L223 _member_ `int32 InitialWidth;` (scope `UCommonNumericTextBlock::__anon77bb1c160308`)
- L224 _member_ `float Duration;` (scope `UCommonNumericTextBlock::__anon77bb1c160308`)

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonPoolableWidgetInterface.h` (Public)


#### class `UCommonPoolableWidgetInterface`  
`class UCommonPoolableWidgetInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICommonPoolableWidgetInterface`  
`class ICommonPoolableWidgetInterface`  
_L19-29_
- desc: Widget pool, if implemented WidgetFactory will attempt to reuse implementing widget objects.
- L25 _protected prototype_ `void OnAcquireFromPool();` — `UFUNCTION(BlueprintNativeEvent, Category = "Common Poolable Widget")`
- L28 _protected prototype_ `void OnReleaseToPool();` — `UFUNCTION(BlueprintNativeEvent, Category = "Common Poolable Widget")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonRichTextBlock.h` (Public)


#### enum `ERichTextInlineIconDisplayMode`  
`enum class ERichTextInlineIconDisplayMode : uint8`  
_L20-29_
- reflection: `UENUM(BlueprintType)`
- desc: Various ways that we display inline icon that have an icon-name association
- L23 _public enumerator_ `IconOnly` — Only show the icon - use when space is limited
- L25 _public enumerator_ `TextOnly` — Only show the text - use seldom if ever
- L27 _public enumerator_ `IconAndText` — Show both the icon and the text - use whenever there is space
- L28 _public enumerator_ `MAX`

#### class `UCommonRichTextBlock`  
`class UCommonRichTextBlock : public URichTextBlock`  
_L35-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URichTextBlock`
- desc: Text block that supports custom scaling for mobile platforms, with option to only show icons if space is sparse.
- L40 _public function_ `ETextTransformPolicy GetTextTransformPolicy() const`
- L41 _public function_ `TSubclassOf<UCommonTextStyle> GetDefaultTextStyleClass() const`
- L42 _public function_ `float GetMobileTextBlockScale() const`
- L44 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L45 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L46 _public prototype_ `virtual void SetText(const FText& InText) override;`
- L49 _public prototype_ `void SetStyle(const TSubclassOf<UCommonTextStyle>& InStyle);` — `UFUNCTION(BlueprintCallable, Category = "Common Rich Text")`
- L52 _public prototype_ `void SetScrollingEnabled(bool bInIsScrollingEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Common Rich Text|Scroll Style")`
- L55 _public prototype_ `virtual void OnCreationFromPalette() override;`
- L56 _public prototype_ `const FText GetPaletteCategory() override;`
- L57 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const;`
- L61 _public member_ `ERichTextInlineIconDisplayMode InlineIconDisplayMode;` — `UPROPERTY(EditAnywhere, Category = InlineIcon)`
- L65 _public member_ `bool bTintInlineIcon = false;` — `UPROPERTY(EditAnywhere, Category = InlineIcon)` — Toggle it on if the text color should also tint the inline icons.
- L66 _public prototype_ `static FString EscapeStringForRichText(FString InString);`
- L69 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L70 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L71 _protected prototype_ `virtual void CreateDecorators(TArray<TSharedRef<ITextDecorator>>& OutDecorators) override;`
- L73 _protected prototype_ `virtual void ApplyUpdatedDefaultTextStyle() override;`
- L76 _private prototype_ `void RefreshOverrideStyle();`
- L77 _private prototype_ `void ApplyTextBlockScale() const;`
- L82 _private member_ `float MobileTextBlockScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Mobile", meta = (ClampMin = "0.01", ClampMax = "5"))` — Mobile font size multiplier. Activated by default on mobile. See CVar Mobile_PreviewFontSize
- L85 _private member_ `TSubclassOf<UCommonTextStyle> DefaultTextStyleOverrideClass;` — `UPROPERTY(EditAnywhere, Category = Appearance, meta = (EditCondition = bOverrideDefaultStyle))`
- L89 _private member_ `TSubclassOf<UCommonTextScrollStyle> ScrollStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — References the scroll style asset to use, no reference disables scrolling
- L93 _private member_ `TEnumAsByte<EOrientation> ScrollOrientation = Orient_Horizontal;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — The orientation the text will scroll if out of bounds.
- L97 _private member_ `bool bIsScrollingEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — If scrolling is enabled/disabled initially, this can be updated in blueprint
- L101 _private member_ `bool bDisplayAllCaps_DEPRECATED = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bDisplayAllCaps is deprecated. Please use TextTransformPolicy instead."))` — True to always display text in ALL CAPS
- L105 _private member_ `bool bAutoCollapseWithEmptyText = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = true))` — True to automatically collapse this rich text block when set to display an empty string. Conversely, will be SelfHitTestInvisible when showing a non-empty string.
- L107 _private member_ `TSharedPtr<STextScroller> MyTextScroller;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonRotator.h` (Public)


#### enum `ERotatorDirection`  
`enum class ERotatorDirection : uint8`  
_L16-20_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Right`
- L19 _public enumerator_ `Left`

#### class `UCommonRotator`  
`class UCommonRotator : public UCommonButtonBase`  
_L29-102_
- reflection: `UCLASS(MinimalAPI, meta = (DisableNativeTick))`
- inherits: `UCommonButtonBase`
- desc: A button that can rotate between given text labels.
- L35 _public prototype_ `virtual bool Initialize() override;`
- L36 _public prototype_ `virtual FNavigationReply NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply);`
- L39 _public member_ `FNavigationDelegate OnNavigation;` — Handle and use controller navigation to rotate text
- L40 _public prototype_ `TSharedPtr<SWidget> HandleNavigation(EUINavigation UINavigation);`
- L44 _public prototype_ `void PopulateTextLabels(TArray<FText> Labels);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Set the array of texts available
- L48 _public prototype_ `FText GetSelectedText() const;` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Gets the current text value of the slider.
- L52 _public prototype_ `virtual void SetSelectedItem(int32 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Sets the current value of the slider.
- L56 _public function_ `int32 GetSelectedIndex() const` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Gets the current selected index
- L60 _public prototype_ `void ShiftTextLeft();` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Shift the current text left.
- L64 _public prototype_ `void ShiftTextRight();` — `UFUNCTION(BlueprintCallable, Category = "Behavior")` — Shift the current text right.
- L70 _public member_ `FOnRotatedWithDirection OnRotatedWithDirection;` — `UPROPERTY(BlueprintAssignable, Category = "Events")` — Called when the Selected state of this button changes. Provides the direction of rotation.
- L75 _public member_ `FOnRotated OnRotated;` — `UE_DEPRECATED(5.4, "OnRotated is deprecated, please use OnRotatedWithDirection instead.")` — `UPROPERTY(BlueprintAssignable, Category = "Events")` — Called when the Selected state of this button changes
- L77 _public prototype_ `DECLARE_EVENT_TwoParams(UCommonRotator, FRotationEvent, int32 , bool );`
- L78 _public member_ `FRotationEvent OnRotatedEvent;`
- L81 _protected prototype_ `void ShiftTextLeftInternal(bool bFromNavigation);`
- L82 _protected prototype_ `void ShiftTextRightInternal(bool bFromNavigation);`
- L86 _protected prototype_ `void BP_OnOptionsPopulated(int32 Count);` — `UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Options Populated"))`
- L89 _protected prototype_ `void BP_OnOptionSelected(int32 Index);` — `UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Options Selected"))`
- L95 _protected member_ `TObjectPtr<UCommonTextBlock> MyText;` — `UPROPERTY(BlueprintReadOnly, Category = CommonRotator, Meta = (BindWidget))` — The displayed text
- L98 _protected member_ `TArray<FText> TextLabels;` — Holds the array of display texts
- L101 _protected member_ `int32 SelectedIndex;` — The index of the current text item

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`
- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotated, int32, Value);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotated, int32, Value);`
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRotatedWithDirection, int32, Value, ERotatorDirection, RotatorDir);`
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRotatedWithDirection, int32, Value, ERotatorDirection, RotatorDir);`
- L77 _delegate_ `DECLARE_EVENT_TwoParams(UCommonRotator, FRotationEvent, int32 , bool );`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonTabListWidgetBase.h` (Public)


#### struct `FCommonRegisteredTabInfo`  
`struct FCommonRegisteredTabInfo`  
_L21-47_
- reflection: `USTRUCT()`
- desc: Information about a registered tab in the tab list
- L28 _public member_ `int32 TabIndex;` — `UPROPERTY()` — The index of the tab in the list
- L32 _public member_ `TSubclassOf<UCommonButtonBase> TabButtonClass;` — `UPROPERTY()` — The class of our TabButton widget
- L36 _public member_ `TObjectPtr<UCommonButtonBase> TabButton;` — `UPROPERTY()` — The actual button widget that represents this tab on-screen
- L40 _public member_ `TObjectPtr<UWidget> ContentInstance;` — `UPROPERTY()` — The actual instance of the content widget to display when this tab is selected. Can be null if a load is required.
- L42 _public function_ `FCommonRegisteredTabInfo() : TabIndex(INDEX_NONE) , TabButton(nullptr) , ContentInstance(nullptr)`

#### class `UCommonTabListWidgetBase`  
`class UCommonTabListWidgetBase : public UCommonUserWidget`  
_L51-272_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "Common UI", DisableNativeTick))`
- inherits: `UCommonUserWidget`
- desc: Base class for a list of selectable tabs that correspondingly activate and display an arbitrary widget in a linked switcher
- L57 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabSelected, FName, TabId);` — Delegate broadcast when a new tab is selected.
- L61 _public member_ `FOnTabSelected OnTabSelected;` — `UPROPERTY(BlueprintAssignable, Category = TabList)` — Broadcasts when a new tab is selected.
- L64 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabButtonCreation, FName, TabId, UCommonButtonBase*, TabButton);` — Delegate broadcast when a new tab is created. Allows hook ups after creation.
- L68 _public member_ `FOnTabButtonCreation OnTabButtonCreation;` — `UPROPERTY(BlueprintAssignable, Category = TabList)` — Broadcasts when a new tab is created.
- L71 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabButtonRemoval, FName, TabId, UCommonButtonBase*, TabButton);` — Delegate broadcast when a tab is being removed. Allows clean ups after destruction.
- L75 _public member_ `FOnTabButtonRemoval OnTabButtonRemoval;` — `UPROPERTY(BlueprintAssignable, Category = TabList)` — Broadcasts when a new tab is created.
- L78 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTabListRebuilt);` — Delegate broadcast when the tab list has been rebuilt (after a new tab has been inserted rather than added to the end).
- L82 _public member_ `FOnTabListRebuilt OnTabListRebuilt;` — `UPROPERTY(BlueprintAssignable, Category = TabList)` — Broadcasts when the tab list has been rebuilt (after a new tab has been inserted rather than added to the end).
- L86 _public function_ `FName GetActiveTab() const` — `UFUNCTION(BlueprintCallable, Category = TabList)` — @return The currently active (selected) tab
- L93 _public prototype_ `virtual void SetLinkedSwitcher(UCommonAnimatedSwitcher* CommonSwitcher);` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Establishes the activatable widget switcher instance that this tab list should interact with @param CommonSwitcher The switcher that this tab list should be associated with and manipulate
- L97 _public prototype_ `UCommonAnimatedSwitcher* GetLinkedSwitcher() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = TabList)` — @return The switcher that this tab list is associated with and manipulates
- L108 _public prototype_ `bool RegisterTab(FName TabNameID, TSubclassOf<UCommonButtonBase> ButtonWidgetType, UWidget* ContentWidget, const int32 TabIndex = -1 );` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Registers and adds a new tab to the list that corresponds to a given widget instance. If not present in the linked switcher, it will be added. @param TabID The name ID used to keep track of this tab. Attempts to register a tab under a duplicate ID will fail. @param ButtonWidgetType The widget type to create for this tab @param ContentWidget The widget to associate with the registered tab @param TabIndex Determines where in the tab list to insert the new tab (-1 means tab will be added to end of the list) @return True if the new tab registered successfully and there were no name ID conflicts
- L111 _public prototype_ `bool RemoveTab(FName TabNameID);` — `UFUNCTION(BlueprintCallable, Category = TabList)`
- L114 _public prototype_ `void RemoveAllTabs();` — `UFUNCTION(BlueprintCallable, Category = TabList)`
- L117 _public prototype_ `int32 GetTabCount() const;` — `UFUNCTION(BlueprintCallable, Category = TabList)`
- L124 _public prototype_ `bool SelectTabByID(FName TabNameID, bool bSuppressClickFeedback = false );` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Selects the tab registered under the provided name ID @param TabNameID The name ID for the tab given when registered
- L127 _public prototype_ `FName GetSelectedTabId() const;` — `UFUNCTION(BlueprintCallable, Category = TabList)`
- L130 _public prototype_ `FName GetTabIdAtIndex(int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category = TabList)`
- L134 _public prototype_ `void SetTabVisibility(FName TabNameID, ESlateVisibility NewVisibility);` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Sets the visibility of the tab associated with the given ID
- L138 _public prototype_ `void SetTabEnabled(FName TabNameID, bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Sets whether the tab associated with the given ID is enabled/disabled
- L142 _public prototype_ `void SetTabInteractionEnabled(FName TabNameID, bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Sets whether the tab associated with the given ID is interactable
- L146 _public prototype_ `void DisableTabWithReason(FName TabNameID, const FText& Reason);` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Disables the tab associated with the given ID with a reason
- L149 _public prototype_ `virtual void SetListeningForInput(bool bShouldListen);` — `UFUNCTION(BlueprintCallable, Category = TabList)`
- L153 _public prototype_ `UCommonButtonBase* GetTabButtonBaseByID(FName TabNameID) const;` — `UFUNCTION(BlueprintCallable, Category = TabList)` — Returns the tab button matching the ID, if found
- L157 _public prototype_ `bool HasTabContentWidget(const FName TabNameId) const;` — `UFUNCTION(BlueprintCallable, Category = "Tab List")` — Checks if a tab has an associated content widget
- L161 _public prototype_ `bool RegisterTabContentWidget(const FName TabNameId, UWidget* ContentWidget);` — `UFUNCTION(BlueprintCallable, Category = "Tab List")` — Registers a content widget with a previously created tab with ID TabNameId. If a linked switcher has been setup, it will also be added to it
- L164 _public prototype_ `void SetSelectionRequired(bool bSelectionRequired);` — Allows one to temporarily disable the selection-required behavior TabButtonGroup, useful during initialization and destruction of a UCommonTabListWidgetBase
- L168 _protected prototype_ `virtual void NativeOnInitialized() override;` — UUserWidget interface
- L169 _protected prototype_ `virtual void NativeConstruct() override;`
- L170 _protected prototype_ `virtual void NativeDestruct() override;`
- L171 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L174 _protected prototype_ `virtual void UpdateBindings();`
- L176 _protected prototype_ `bool IsRebuildingList() const;`
- L179 _protected prototype_ `void HandlePreLinkedSwitcherChanged_BP();` — `UFUNCTION(BlueprintImplementableEvent, Category = TabList, meta = (BlueprintProtected = "true"))`
- L181 _protected prototype_ `virtual void HandlePreLinkedSwitcherChanged();`
- L184 _protected prototype_ `void HandlePostLinkedSwitcherChanged_BP();` — `UFUNCTION(BlueprintImplementableEvent, Category = TabList, meta = (BlueprintProtected = "true"))`
- L186 _protected prototype_ `virtual void HandlePostLinkedSwitcherChanged();`
- L189 _protected prototype_ `void HandleTabCreation(FName TabNameID, UCommonButtonBase* TabButton);` — `UFUNCTION(BlueprintNativeEvent, Category = TabList, meta = (BlueprintProtected = "true"))`
- L192 _protected prototype_ `void HandleTabRemoval(FName TabNameID, UCommonButtonBase* TabButton);` — `UFUNCTION(BlueprintNativeEvent, Category = TabList, meta = (BlueprintProtected = "true"))`
- L196 _protected member_ `FDataTableRowHandle NextTabInputActionData;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TabList, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))` — The input action to listen for causing the next tab to be selected
- L200 _protected member_ `FDataTableRowHandle PreviousTabInputActionData;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TabList, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))` — The input action to listen for causing the previous tab to be selected
- L204 _protected member_ `TObjectPtr<UInputAction> NextTabEnhancedInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TabList, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))` — The input action to listen for causing the next tab to be selected
- L208 _protected member_ `TObjectPtr<UInputAction> PreviousTabEnhancedInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TabList, meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))` — The input action to listen for causing the previous tab to be selected
- L212 _protected member_ `bool bAutoListenForInput;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TabList, meta = (ExposeOnSpawn = "true"))` — Whether to register to handle tab list input immediately upon construction
- L216 _protected member_ `bool bShouldWrapNavigation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TabList, meta = (ExposeOnSpawn = "true"))` — Whether pressing next/prev tab on the last/first tab should wrap selection to the beginning/end or stay at the end/beginning.
- L223 _protected member_ `bool bDeferRebuildingTabList;` — `UPROPERTY(EditAnywhere, Category = TabList)` — Whether to defer until next tick rebuilding tab list when inserting new tab (rather than adding to the end). Useful if inserting multiple tabs in the same tick as the tab list will only be rebuilt once.
- L226 _protected prototype_ `const TMap<FName, FCommonRegisteredTabInfo>& GetRegisteredTabsByID() const;`
- L229 _protected prototype_ `void HandleTabButtonSelected(UCommonButtonBase* SelectedTabButton, int32 ButtonIndex);` — `UFUNCTION()`
- L232 _protected prototype_ `void HandlePreviousTabInputAction(bool& bPassthrough);` — `UFUNCTION()`
- L235 _protected prototype_ `void HandleNextTabInputAction(bool& bPassthrough);` — `UFUNCTION()`
- L239 _protected member_ `TWeakObjectPtr<UCommonAnimatedSwitcher> LinkedSwitcher;` — `UPROPERTY(Transient)` — The activatable widget switcher that this tab list is associated with and manipulates
- L243 _protected member_ `TObjectPtr<UCommonButtonGroupBase> TabButtonGroup;` — `UPROPERTY(Transient)` — The button group that manages all the created tab buttons
- L246 _protected member_ `bool bIsListeningForInput = false;` — Is the tab list currently listening for tab input actions?
- L249 _private prototype_ `void HandleNextTabAction();`
- L250 _private prototype_ `void HandlePreviousTabAction();`
- L252 _private prototype_ `bool DeferredRebuildTabList(float DeltaTime);`
- L253 _private prototype_ `void RebuildTabList();`
- L255 _private prototype_ `void RemoveTab_Internal(const FName TabNameID, const FCommonRegisteredTabInfo& TabInfo);`
- L259 _private member_ `TMap<FName, FCommonRegisteredTabInfo> RegisteredTabsByID;` — `UPROPERTY(Transient)` — Info about each of the currently registered tabs organized by a given registration name ID
- L262 _private member_ `FUserWidgetPool TabButtonWidgetPool;` — `UPROPERTY(Transient)`
- L265 _private member_ `FName ActiveTabID;` — The registration ID of the currently active tab
- L267 _private member_ `bool bIsRebuildingList = false;`
- L268 _private member_ `bool bPendingRebuild = false;`
- L270 _private member_ `FUIActionBindingHandle NextTabActionHandle;`
- L271 _private member_ `FUIActionBindingHandle PrevTabActionHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`
- L57 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabSelected, FName, TabId);` — Delegate broadcast when a new tab is selected.
- L64 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabButtonCreation, FName, TabId, UCommonButtonBase*, TabButton);` — Delegate broadcast when a new tab is created. Allows hook ups after creation.
- L71 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabButtonRemoval, FName, TabId, UCommonButtonBase*, TabButton);` — Delegate broadcast when a tab is being removed. Allows clean ups after destruction.
- L78 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTabListRebuilt);` — Delegate broadcast when the tab list has been rebuilt (after a new tab has been inserted rather than added to the end).

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonTextBlock.h` (Public)


#### class `UCommonTextStyle`  
`class UCommonTextStyle : public UObject`  
_L22-92_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `UObject`
- desc: ---- All properties must be EditDefaultsOnly, BlueprintReadOnly !!! ----- We return the CDO to blueprints, so we cannot allow any changes (blueprint doesn't support const variables)
- L27 _public prototype_ `UCommonTextStyle();`
- L31 _public member_ `FSlateFontInfo Font;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Font")` — The font to apply at each size
- L35 _public member_ `FLinearColor Color;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Color")` — The color of the text
- L39 _public member_ `bool bUsesDropShadow;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shadow")` — Whether or not the style uses a drop shadow
- L43 _public member_ `FVector2D ShadowOffset;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shadow", meta = (EditCondition = "bUsesDropShadow"))` — The offset of the drop shadow at each size
- L47 _public member_ `FLinearColor ShadowColor;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shadow", meta = (EditCondition = "bUsesDropShadow"))` — The drop shadow color
- L51 _public member_ `FMargin Margin;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The amount of blank space left around the edges of text area at each size
- L55 _public member_ `FSlateBrush StrikeBrush;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The brush used to draw an strike through the text (if any)
- L59 _public member_ `float LineHeightPercentage;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — The amount to scale each lines height by at each size
- L63 _public member_ `bool ApplyLineHeightToBottomLine;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")` — Whether to leave extra space below the last line due to line height
- L66 _public prototype_ `void GetFont(FSlateFontInfo& OutFont) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L69 _public prototype_ `void GetColor(FLinearColor& OutColor) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L72 _public prototype_ `void GetMargin(FMargin& OutMargin) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L75 _public prototype_ `float GetLineHeightPercentage() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L78 _public prototype_ `bool GetApplyLineHeightToBottomLine() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L81 _public prototype_ `void GetShadowOffset(FVector2D& OutShadowOffset) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L84 _public prototype_ `void GetShadowColor(FLinearColor& OutColor) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L87 _public prototype_ `void GetStrikeBrush(FSlateBrush& OutStrikeBrush) const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text Style|Getters")`
- L89 _public prototype_ `virtual void ToTextBlockStyle(FTextBlockStyle& OutTextBlockStyle) const;`
- L91 _public prototype_ `virtual void ApplyToTextBlock(const TSharedRef<STextBlock>& TextBlock) const;`

#### class `UCommonTextScrollStyle`  
`class UCommonTextScrollStyle : public UObject`  
_L99-123_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `UObject`
- desc: ---- All properties must be EditDefaultsOnly, BlueprintReadOnly !!! ----- We return the CDO to blueprints, so we cannot allow any changes (blueprint doesn't support const variables)
- L104 _public prototype_ `FTextScrollerOptions ToScrollOptions() const;`
- L107 _public member_ `float Speed;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")`
- L110 _public member_ `float StartDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")`
- L113 _public member_ `float EndDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")`
- L116 _public member_ `float FadeInDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")`
- L119 _public member_ `float FadeOutDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")`
- L122 _public member_ `EWidgetClipping Clipping = EWidgetClipping::OnDemand;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")`

#### class `UCommonTextBlock`  
`class UCommonTextBlock : public UTextBlock`  
_L129-230_
- reflection: `UCLASS(MinimalAPI, Config = CommonUI, DefaultConfig, ClassGroup = UI, meta = (Category = "Common UI", DisplayName = "Common Text", PrioritizeCategories = "Content"))`
- inherits: `UTextBlock`
- desc: Text block with automatic scrolling for FX / large texts, also supports a larger set of default styling, & custom mobile scaling.
- L133 _public prototype_ `virtual void PostInitProperties() override;`
- L134 _public prototype_ `virtual void PostLoad() override;`
- L135 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L136 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L139 _public prototype_ `void SetWrapTextWidth(int32 InWrapTextAt);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L142 _public prototype_ `void SetTextCase(bool bUseAllCaps);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L145 _public prototype_ `void SetLineHeightPercentage(float InLineHeightPercentage);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L148 _public prototype_ `void SetApplyLineHeightToBottomLine(bool InApplyLineHeightToBottomLine);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L151 _public prototype_ `void SetStyle(TSubclassOf<UCommonTextStyle> InStyle);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L154 _public prototype_ `void SetScrollOrientation(TEnumAsByte<EOrientation> InScrollOrientation);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L157 _public prototype_ `const FMargin& GetMargin();` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L160 _public prototype_ `void SetMargin(const FMargin& InMargin);` — `UFUNCTION(BlueprintCallable, Category = "Common Text")`
- L163 _public prototype_ `float GetMobileFontSizeMultiplier() const;` — `UFUNCTION(BlueprintCallable, Category = "Common Text|Mobile")`
- L167 _public prototype_ `void SetMobileFontSizeMultiplier(float InMobileFontSizeMultiplier);` — `UFUNCTION(BlueprintCallable, Category = "Common Text|Mobile")` — Sets the new value and then applies the FontSizeMultiplier
- L170 _public prototype_ `void ResetScrollState();` — `UFUNCTION(BlueprintCallable, Category = "Common Text|Scroll Style")`
- L173 _public prototype_ `void SetScrollingEnabled(bool bInIsScrollingEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Common Text|Scroll Style")`
- L176 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L177 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L179 _protected prototype_ `virtual void OnTextChanged() override;`
- L180 _protected prototype_ `virtual void OnFontChanged() override;`
- L184 _protected member_ `float MobileFontSizeMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Mobile", meta = (ClampMin = "0.01", ClampMax = "5.0"))` — Mobile font size multiplier. Activated by default on mobile. See CVar Mobile_PreviewFontSize
- L187 _protected prototype_ `virtual void OnCreationFromPalette() override;`
- L188 _protected prototype_ `const FText GetPaletteCategory() override;`
- L189 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const;`
- L195 _private member_ `bool bIsScrollingEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonText, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — If scrolling is enabled/disabled initially, this can be updated in blueprint
- L199 _private member_ `bool bDisplayAllCaps_DEPRECATED = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bDisplayAllCaps is deprecated. Please use TextTransformPolicy instead."))` — True to always display text in ALL CAPS
- L203 _private member_ `bool bAutoCollapseWithEmptyText = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonText, meta = (AllowPrivateAccess = true))` — True to automatically collapse this text block when set to display an empty string. Conversely, will be SelfHitTestInvisible when showing a non-empty string.
- L207 _private member_ `TSubclassOf<UCommonTextStyle> Style;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonText, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — References the text style to use
- L211 _private member_ `TSubclassOf<UCommonTextScrollStyle> ScrollStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonText, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — References the scroll style asset to use, no reference disables scrolling
- L215 _private member_ `TEnumAsByte<EOrientation> ScrollOrientation = Orient_Horizontal;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CommonText, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))` — The orientation the text will scroll if out of bounds.
- L220 _private member_ `bool bStyleNoLongerNeedsConversion;` — `UPROPERTY()` — Used to track widgets that were created before changing the default style pointer to null
- L223 _private prototype_ `void UpdateFromStyle();`
- L224 _private prototype_ `const UCommonTextStyle* GetStyleCDO() const;`
- L225 _private prototype_ `const UCommonTextScrollStyle* GetScrollStyleCDO() const;`
- L227 _private member_ `TSharedPtr<class STextScroller> TextScroller;`
- L229 _private prototype_ `void ApplyFontSizeMultiplier() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonTileView.h` (Public)


#### class `UCommonTileView`  
`class UCommonTileView : public UTileView`  
_L16-26_
- reflection: `UCLASS(MinimalAPI, meta = (DisableNativeTick))`
- inherits: `UTileView`
- desc: TileView specialized to navigate on focus for consoles & enable scrolling when not focused for touch
- L21 _public prototype_ `UCommonTileView(const FObjectInitializer& ObjectInitializer);`
- L24 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget() override;`
- L25 _protected prototype_ `virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonTreeView.h` (Public)


#### class `SCommonTreeView`  
`template <typename ItemType> class SCommonTreeView : public STreeView<ItemType>`  
_L17-82_
- inherits: `STreeView<ItemType>`
- L20 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L51 _public function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override`
- L63 _public function_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L75 _public function_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L81 _protected member_ `bool bScrollToSelectedOnFocus = true;`

#### class `UCommonTreeView`  
`class UCommonTreeView : public UTreeView`  
_L92-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTreeView`
- desc: TreeView specialized to navigate on focus for consoles & enable scrolling when not focused for touch
- L97 _public prototype_ `UCommonTreeView(const FObjectInitializer& ObjectInitializer);`
- L100 _protected prototype_ `virtual TSharedRef<STableViewBase> RebuildListWidget() override;`
- L101 _protected prototype_ `virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUIEditorSettings.h` (Public)


#### class `UCommonUIEditorSettings`  
`class UCommonUIEditorSettings : public UObject`  
_L14-62_
- reflection: `UCLASS(MinimalAPI, config = Editor, defaultconfig)`
- inherits: `UObject`
- L19 _public prototype_ `UCommonUIEditorSettings(const FObjectInitializer& Initializer);`
- L22 _public prototype_ `void LoadData();` — Called to load CommonUIEditorSettings data
- L24 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _public prototype_ `const TSubclassOf<UCommonTextStyle>& GetTemplateTextStyle() const;` — Template Styles - Only accessible in editor builds should be transfered to new widgets in OnCreationFromPalette() overrides
- L29 _public prototype_ `const TSubclassOf<UCommonButtonStyle>& GetTemplateButtonStyle() const;`
- L31 _public prototype_ `const TSubclassOf<UCommonBorderStyle>& GetTemplateBorderStyle() const;`
- L34 _private prototype_ `void LoadEditorData();`
- L40 _private member_ `TSoftClassPtr<UCommonTextStyle> TemplateTextStyle;` — `UPROPERTY(config, EditAnywhere, Category = "Text")` — Newly created CommonText Widgets will use this style.
- L44 _private member_ `TSoftClassPtr<UCommonButtonStyle> TemplateButtonStyle;` — `UPROPERTY(config, EditAnywhere, Category = "Buttons")` — Newly created CommonButton Widgets will use this style.
- L48 _private member_ `TSoftClassPtr<UCommonBorderStyle> TemplateBorderStyle;` — `UPROPERTY(config, EditAnywhere, Category = "Border")` — Newly created CommonBorder Widgets will use this style.
- L52 _private member_ `TSubclassOf<UCommonTextStyle> TemplateTextStyleClass;` — `UPROPERTY(Transient)`
- L55 _private member_ `TSubclassOf<UCommonButtonStyle> TemplateButtonStyleClass;` — `UPROPERTY(Transient)`
- L58 _private member_ `TSubclassOf<UCommonBorderStyle> TemplateBorderStyleClass;` — `UPROPERTY(Transient)`
- L61 _private member_ `bool bDefaultDataLoaded;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUILibrary.h` (Public)


#### class `UCommonUILibrary`  
`class UCommonUILibrary : public UBlueprintFunctionLibrary`  
_L15-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L30 _public prototype_ `static bool RefreshFocusIfLeafmostDescendant(UWidget* ContextWidget);` — `UFUNCTION(BlueprintCallable, Category = "CommonUI|Focus", meta=(DefaultToSelf="ContextWidget", WorldContext="ContextWidget"))` — Request a focus refresh from any widget that is a descendant of the leaf-most activated widget. This should be used to handle asynchronous requests to route focus from outside the leaf-most activatable widget. A very common use case is a visualization or asynchronous widget creation from a plugin-injected widget or a widget otherwise unavailable or cumbersome to access from the leaf-most activatable widget. @return Whether or not the request for focus was made
- L36 _public prototype_ `static UWidget* FindParentWidgetOfType(UWidget* StartingWidget, TSubclassOf<UWidget> Type);` — `UFUNCTION(BlueprintCallable, Category="Common UI", meta=(DeterminesOutputType=Type))` — Finds the first parent widget of the given type and returns it, or null if no parent could be found.
- L42 _public prototype_ `static UWidget* FindParentWidgetImplementingInterface(UWidget* StartingWidget, TSubclassOf<UInterface> Interface);` — `UFUNCTION(BlueprintCallable, Category="Common UI")` — Finds the first parent widget implementing the given interface and returns it, or null if no parent could be found.
- L48 _public prototype_ `static FGameplayTag Conv_UITagToGameplayTag(FUITag InValue);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (BlueprintAutocast))` — Interpret a UITag as GameplayTag. Enables connecting UITags to wildcard comparison nodes that map to explicit GameplayTag functions.
- L54 _public prototype_ `static FGameplayTag Conv_UIActionTagToGameplayTag(FUIActionTag InValue);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (BlueprintAutocast))` — Interpret a UIActionTag as GameplayTag. Enables connecting FUIActionTags to wildcard comparison nodes that map to explicit GameplayTag functions.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUIRichTextData.h` (Public)


#### struct `FRichTextIconData`  
`struct FRichTextIconData : public FTableRowBase`  
_L12-24_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- L17 _public member_ `FText DisplayName;` — `UPROPERTY(EditDefaultsOnly, Category = "RichText Icon")`
- L20 _public member_ `TSoftObjectPtr<UObject> ResourceObject;` — `UPROPERTY(EditDefaultsOnly, Category = "RichText Icon", meta = (DisplayThumbnail = "true", DisplayName = "Image", AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))`
- L23 _public member_ `FVector2D ImageSize = FVector2D(64.f, 64.f);` — `UPROPERTY(EditDefaultsOnly, Category = "RichText Icon")`

#### class `UCommonUIRichTextData`  
`class UCommonUIRichTextData : public UObject`  
_L31-44_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (Category = "Common UI"))`
- inherits: `UObject`
- desc: Derive from this class for rich text data per game it is referenced in Common UI Settings, found in project settings UI
- L36 _public prototype_ `static UCommonUIRichTextData* Get();`
- L38 _public prototype_ `const FRichTextIconData* FindIcon(const FName& InKey);`
- L39 _public function_ `const TMap<FName, uint8*>& GetIconMap() const`
- L43 _private member_ `TObjectPtr<UDataTable> InlineIconSet;` — `UPROPERTY(EditDefaultsOnly, Category = "Inline Icons", meta = (RowType = "/Script/CommonUI.RichTextIconData"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUISettings.h` (Public)


#### enum `ECommonButtonAcceptKeyHandling`  
`enum class ECommonButtonAcceptKeyHandling`  
_L19-30_
- reflection: `UENUM()`
- L24 _public enumerator_ `Ignore` — (Default for projects created prior to 5.6) When a CommonButton is focused, it will ignore the configured keys for slate navigation's Accept action (see FNavigationConfig::KeyActionRules), leaving it up to the button's Triggering Input Action to trigger the button's click event. This allows other objects to bind input actions to the accept action keys while focusing a common button.
- L29 _public enumerator_ `TriggerClick` — (Default for new projects as of 5.6) When a CommonButton is focused, it will let all inputs events flow through to the underlying SButton, therefore triggering the button's click event when pressing the configured keys for slate navigation's Accept action (see FNavigationConfig::KeyActionRules) This will prevent input actions that are bound to those keys from triggering while a CommonButton is focused.

#### class `UCommonUISettings`  
`class UCommonUISettings : public UObject`  
_L33-114_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig)`
- inherits: `UObject`
- L38 _public prototype_ `UCommonUISettings(const FObjectInitializer& Initializer = FObjectInitializer::Get());`
- L39 _public prototype_ `UCommonUISettings(FVTableHelper& Helper);`
- L40 _public prototype_ `~UCommonUISettings();`
- L43 _public prototype_ `void LoadData();` — Called to load CommonUISetting data, if bAutoLoadData if set to false then game code must call LoadData().
- L47 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L49 _public prototype_ `virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;`
- L50 _public prototype_ `virtual void PostInitProperties() override;`
- L54 _public prototype_ `void AutoLoadData();` — Called by the module startup to auto load CommonUISetting data if bAutoLoadData is true.
- L56 _public prototype_ `UCommonUIRichTextData* GetRichTextData() const;`
- L57 _public prototype_ `const FSlateBrush& GetDefaultThrobberBrush() const;`
- L58 _public prototype_ `UObject* GetDefaultImageResourceObject() const;`
- L59 _public prototype_ `const FGameplayTagContainer& GetPlatformTraits() const;`
- L60 _public prototype_ `ECommonButtonAcceptKeyHandling GetCommonButtonAcceptKeyHandling() const;`
- L68 _private member_ `bool bAutoLoadData;` — `UPROPERTY(config, EditAnywhere, Category = "Default")` — Controls if the data referenced is automatically loaded. If False then game code must call LoadData() on it's own.
- L72 _private member_ `TSoftObjectPtr<UObject> DefaultImageResourceObject;` — `UPROPERTY(config, EditAnywhere, Category = "Image", meta = (AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.MaterialInterface"))` — The Default Image Resource, newly created CommonImage Widgets will use this style.
- L76 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultThrobberMaterial;` — `UPROPERTY(config, EditAnywhere, Category = "Throbber")` — The Default Throbber Material, newly created CommonLoadGuard Widget will use this style.
- L80 _private member_ `TSoftClassPtr<UCommonUIRichTextData> DefaultRichTextDataClass;` — `UPROPERTY(config, EditAnywhere, Category = "RichText", meta=(AllowAbstract=false))` — The Default Data for rich text to show inline icon and others.
- L84 _private member_ `TArray<FGameplayTag> PlatformTraits;` — `UPROPERTY(config, EditAnywhere, Category = "Visibility", meta=(Categories="Platform.Trait", ConfigHierarchyEditable))` — The set of traits defined per-platform (e.g., the default input mode, whether or not you can exit the application, etc...)
- L90 _private member_ `ECommonButtonAcceptKeyHandling CommonButtonAcceptKeyHandling;` — `UPROPERTY(config, EditAnywhere, Category = "Button")` — How should CommonButton widgets handle SlateNavigation Accept actions?
- L93 _private prototype_ `void LoadEditorData();`
- L94 _private prototype_ `void RebuildTraitContainer();`
- L96 _private member_ `bool bDefaultDataLoaded;`
- L101 _private member_ `FGameplayTagContainer PlatformTraitContainer;` — Merged version of PlatformTraits This is not the config property because there is no direct ini inheritance for structs (even ones like tag containers that represent a set), unlike arrays
- L104 _private member_ `TObjectPtr<UObject> DefaultImageResourceObjectInstance;` — `UPROPERTY(Transient)`
- L107 _private member_ `TObjectPtr<UMaterialInterface> DefaultThrobberMaterialInstance;` — `UPROPERTY(Transient)`
- L110 _private member_ `FSlateBrush DefaultThrobberBrush;` — `UPROPERTY(Transient)`
- L113 _private member_ `TObjectPtr<UCommonUIRichTextData> RichTextDataInstance;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONUI_API`
- L16 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PlatformTrait_PlayInEditor);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUISubsystemBase.h` (Public)


#### class `UCommonUISubsystemBase`  
`class UCommonUISubsystemBase : public UGameInstanceSubsystem`  
_L21-58_
- reflection: `UCLASS(MinimalAPI, DisplayName = "CommonUI")`
- inherits: `UGameInstanceSubsystem`
- L26 _public prototype_ `static UCommonUISubsystemBase* Get(const UWidget& Widget);`
- L28 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L29 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L32 _public prototype_ `void SetAnalyticProvider(const TSharedPtr<IAnalyticsProviderET>& AnalyticProvider);` — set the analytic provider for the CommonUI Widgets to use
- L36 _public prototype_ `FSlateBrush GetInputActionButtonIcon(const FDataTableRowHandle& InputActionRowHandle, ECommonInputType InputType, const FName& GamepadName) const;` — `UFUNCTION(BlueprintCallable, Category = CommonUISubsystem)` — Gets Action Button Icon for current gamepad
- L40 _public prototype_ `FSlateBrush GetEnhancedInputActionButtonIcon(const UInputAction* InputAction, const ULocalPlayer* LocalPlayer) const;` — `UFUNCTION(BlueprintCallable, Category = CommonUISubsystem)` — Gets Action Button Icon for given action and player, enhanced input API currently does not allow input type specification
- L45 _public prototype_ `void FireEvent_ButtonClicked(const FString& InstanceName, const FString& ABTestName, const FString& ExtraData) const;` — CommonUI.ButtonClicked
- L48 _public prototype_ `void FireEvent_PanelPushed(const FString& PanelName) const;` — CommonUI.PanelPushed
- L50 _public prototype_ `virtual void SetInputAllowed(bool bEnabled, const FName& Reason, const ULocalPlayer& LocalPlayer);`
- L51 _public prototype_ `virtual bool IsInputAllowed(const ULocalPlayer* LocalPlayer) const;`
- L55 _private prototype_ `void HandleInputMethodChanged(ECommonInputType bNewInputType);`
- L57 _private member_ `TWeakPtr<class IAnalyticsProviderET> AnalyticProviderWeakPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUITypes.h` (Public)


#### enum `EInputActionState`  
`enum class EInputActionState : uint8`  
_L25-37_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Enabled` — Enabled, will call all callbacks
- L30 _public enumerator_ `Disabled` — Disabled, will call all the disabled callback if specified otherwise do nothing
- L33 _public enumerator_ `Hidden` — The common input reflector will not visualize this but still calls all callbacks. NOTE: Use this sparingly
- L36 _public enumerator_ `HiddenAndDisabled` — Hidden and disabled behaves as if it were never added with no callbacks being called

#### struct `FCommonInputTypeInfo`  
`struct FCommonInputTypeInfo`  
_L40-109_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public prototype_ `FCommonInputTypeInfo();`
- L48 _private member_ `FKey Key;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Key this action is bound to
- L52 _private member_ `TArray<FKey> AdditionalKeys;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Additional keys that also trigger this action (the primary Key is still used for display)
- L57 _public prototype_ `FKey GetKey() const;` — Get the input type key bound to this input type, with a potential override
- L60 _public prototype_ `TArray<FKey> GetAllKeys() const;` — Get all keys (primary + additional) that trigger this action
- L63 _public prototype_ `bool IsKeyBound(const FKey& InKey) const;` — Returns true if the given key matches the primary key or any additional key
- L66 _public function_ `void SetKey(FKey InKey)` — Get the input type key bound to this input type, with a potential override
- L73 _public member_ `EInputActionState OverrrideState;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — EInputActionState::Enabled means that the state isn't overriden and the games dynamic control will work
- L77 _public member_ `bool bActionRequiresHold;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Enables hold time if true
- L81 _public member_ `float HoldTime;` — `UPROPERTY(EditAnywhere, Category = "CommonInput", meta = (EditCondition = "bActionRequiresHold", ClampMin = "0.0", UIMin = "0.0"))` — The hold time in seconds
- L89 _public member_ `float HoldRollbackTime;` — `UPROPERTY(EditAnywhere, Category = "CommonInput", meta = (EditCondition = "bActionRequiresHold", ClampMin = "0", UIMin = "0", ClampMax = "10.0", UIMax = "10"))` — Time (in seconds) for hold progress to go from 1.0 (completed) to 0.0. If the hold interaction was interrupted, then hold progress starts to roll back decreasing its value. Set to 0.0 to disable the rollback functionality.
- L93 _public member_ `FSlateBrush OverrideBrush;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Override the brush specified by the Key Display Data
- L95 _public function_ `bool operator==(const FCommonInputTypeInfo& Other) const`
- L105 _public function_ `bool operator!=(const FCommonInputTypeInfo& Other) const`

#### struct `FCommonInputActionDataBase`  
`struct FCommonInputActionDataBase : public FTableRowBase`  
_L112-198_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- L116 _public prototype_ `FCommonInputActionDataBase();`
- L120 _public member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonInput")` — User facing name (used when NOT a hold action)
- L124 _public member_ `FText HoldDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonInput")` — User facing name used when it IS a hold action
- L128 _public member_ `int32 NavBarPriority = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonInput")` — Priority in nav-bar
- L135 _protected member_ `FCommonInputTypeInfo KeyboardInputTypeInfo;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Key to bind to for each input method
- L141 _protected member_ `FCommonInputTypeInfo DefaultGamepadInputTypeInfo;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Default input state for gamepads
- L147 _protected member_ `TMap<FName, FCommonInputTypeInfo> GamepadInputOverrides;` — `UPROPERTY(EditAnywhere, Category = "CommonInput", Meta = (GetOptions = "CommonInput.CommonInputBaseControllerData.GetRegisteredGamepads"))` — Override the input state for each input method
- L153 _protected member_ `FCommonInputTypeInfo TouchInputTypeInfo;` — `UPROPERTY(EditAnywhere, Category = "CommonInput")` — Override the displayed brush for each input method
- L158 _public prototype_ `bool CanDisplayInReflector(ECommonInputType InputType, const FName& GamepadName) const;`
- L160 _public prototype_ `virtual const FCommonInputTypeInfo& GetCurrentInputTypeInfo(const UCommonInputSubsystem* CommonInputSubsystem) const;`
- L162 _public prototype_ `virtual const FCommonInputTypeInfo& GetInputTypeInfo(ECommonInputType InputType, const FName& GamepadName) const;`
- L164 _public prototype_ `virtual bool IsKeyBoundToInputActionData(const FKey& Key) const;`
- L166 _public prototype_ `bool IsKeyBoundToInputActionData(const FKey& Key, const UCommonInputSubsystem* CommonInputSubsystem) const;`
- L168 _public prototype_ `FSlateBrush GetCurrentInputActionIcon(const UCommonInputSubsystem* CommonInputSubsystem) const;`
- L170 _public prototype_ `virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override;`
- L172 _public prototype_ `virtual bool HasHoldBindings() const;`
- L174 _public prototype_ `const FCommonInputTypeInfo& GetDefaultGamepadInputTypeInfo() const;`
- L176 _public prototype_ `bool HasGamepadInputOverride(const FName& GamepadName) const;`
- L178 _public prototype_ `void AddGamepadInputOverride(const FName& GamepadName, const FCommonInputTypeInfo& InputInfo);`
- L180 _public function_ `bool operator==(const FCommonInputActionDataBase& Other) const`
- L190 _public function_ `bool operator!=(const FCommonInputActionDataBase& Other) const`
- L196 _public prototype_ `bool Serialize(FArchive& Ar);`
- L197 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCommonInputActionDataBase> : public TStructOpsTypeTraitsBase2<FCommonInputActionDataBase>`  
_L201-208_
- inherits: `TStructOpsTypeTraitsBase2<FCommonInputActionDataBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L204-207_

#### class `UCommonInputMetadata`  
`class UCommonInputMetadata : public UObject`  
_L223-244_
- reflection: `UCLASS(MinimalAPI, Blueprintable, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- desc: Metadata CommonUI will try to acquire from Enhanced Input Mapping Contexts (IMC) You can Inherit from this class if you have any info that may need to be parsed per platform by CommonUI. IMC's can be specified per platform, so each platform may have different Common Input Metadata Note: We intentionally do not define any context-independant metadata. Even though some metadata should be context-independant (Like NavBarPriority below). Locking it that info to a seperate metadata type prevents any chance of future overriding. Instead, we prefer info for all metadata to be set across all instances.
- L231 _public member_ `int32 NavBarPriority = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonInput")` — Priority in nav-bar
- L243 _public member_ `bool bIsGenericInputAction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonInput")` — Generic actions like accept or face button top will be subscribed to by multiple UI elements. These actions will not broadcast enhanced input action delegates such as "Triggered, Ongoing, Canceled, or Completed." Since those delegates would be fired by multiple UI elements. Non-generic input actions will fire Enhanced Input events. However they will not fire CommonUI action bindings (Since those can be manually fired in BP).

#### class `UCommonMappingContextMetadataInterface`  
`class UCommonMappingContextMetadataInterface : public UInterface`  
_L258-261_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for metadata objects specified in Enhanced Input Mapping Contexts (IMC). We provide an interface since it's possible you may need the IMC metadata for non-CommonUI info. In this scenario you can implement this interface and CommonUI will still be able to gather info it needs to function correctly with your Enhanced Input Actions / IMC's. If you don't have any metadata needs or your UI IMC's are for CommonUI only, then you should use the provided 'UCommonMappingContextMetadata' below.

#### class `ICommonMappingContextMetadataInterface`  
`class ICommonMappingContextMetadataInterface`  
_L263-276_
- L275 _public prototype_ `virtual const UCommonInputMetadata* GetCommonInputMetadata(const UInputAction* InInputAction) const = 0;` — Gets base info needed from CommonUI from this IMC metadata Accepts InputAction as an arg to allow for user to create one metadata with multiple values per action, rather than having to create one metadata asset per unique value @param InputAction the input action that may or may not be used to help determine correct metadata

#### class `UCommonMappingContextMetadata`  
`class UCommonMappingContextMetadata : public UDataAsset, public ICommonMappingContextMetadataInterface`  
_L285-300_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset,ICommonMappingContextMetadataInterface`
- desc: Base CommonUI metadata implementation for specification in IMC's. Utilizes a map of input actions to metadata to prevent users from having to create multiple metadata assets / instances. Using this map is not mandatory.
- L292 _public member_ `TObjectPtr<UCommonInputMetadata> EnhancedInputMetadata;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "CommonInput")` — Fallback or default metadata CommonUI relies on if no per-action meta is found below
- L296 _public member_ `TMap<TObjectPtr<UInputAction>, TObjectPtr<const UCommonInputMetadata>> PerActionEnhancedInputMetadata;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "CommonInput")` — Map of action to metadata, allows creation of single metadata asset rather than one per input action type
- L299 _public prototype_ `virtual const UCommonInputMetadata* GetCommonInputMetadata(const UInputAction* InInputAction) const override;`

#### class `CommonUI`  
`class CommonUI`  
_L302-321_
- L305 _public prototype_ `static void SetupStyles();`
- L306 _public member_ `static FScrollBoxStyle EmptyScrollBoxStyle;`
- L308 _public prototype_ `static const FCommonInputActionDataBase* GetInputActionData(const FDataTableRowHandle& InputActionRowHandle);`
- L309 _public prototype_ `static FSlateBrush GetIconForInputActions(const UCommonInputSubsystem* CommonInputSubsystem, const TArray<FDataTableRowHandle>& InputActions);`
- L311 _public prototype_ `static bool IsEnhancedInputSupportEnabled();`
- L313 _public prototype_ `static TObjectPtr<const UCommonInputMetadata> GetEnhancedInputActionMetadata(const UInputAction* InputAction);`
- L314 _public prototype_ `static void GetEnhancedInputActionKeys(const ULocalPlayer* LocalPlayer, const UInputAction* InputAction, TArray<FKey>& OutKeys);`
- L315 _public prototype_ `static void InjectEnhancedInputForAction(const ULocalPlayer* LocalPlayer, const UInputAction* InputAction, FInputActionValue RawValue);`
- L316 _public prototype_ `static FSlateBrush GetIconForEnhancedInputAction(const UCommonInputSubsystem* CommonInputSubsystem, const UInputAction* InputAction);`
- L317 _public prototype_ `static bool ActionValidForInputType(const ULocalPlayer* LocalPlayer, ECommonInputType InputType, const UInputAction* InputAction);`
- L318 _public prototype_ `static bool ActionValidForInputType(const ULocalPlayer* LocalPlayer, ECommonInputType InputType, const FCommonInputActionDataBase* InputAction);`
- L319 _public prototype_ `static bool IsKeyValidForInputType(const FKey& Key, ECommonInputType InputType);`
- L320 _public prototype_ `static FKey GetFirstKeyForInputType(const ULocalPlayer* LocalPlayer, ECommonInputType InputType, const UInputAction* InputAction);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONUI_API`
- L205 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonaaed6da60103`)
- L206 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonaaed6da60103`)
- L323 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnItemClicked, UUserWidget*, Widget);`
- L323 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnItemClicked, UUserWidget*, Widget);`
- L324 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnItemSelected, UUserWidget*, Widget, bool, Selected);`
- L324 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnItemSelected, UUserWidget*, Widget, bool, Selected);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUIUtils.h` (Public)


#### enum `CommonUIUtils::ECollisionPolicy`  
`enum class ECollisionPolicy`  
_L17-25_
- L20 _public enumerator_ `Allow` — Widgets in a switcher may occupy different slots of the switcher
- L22 _public enumerator_ `Require` — Widgets in a switcher must occupy the same slot of the switcher
- L24 _public enumerator_ `Forbid` — Widgets in a switcher must occupy different slots of the switcher

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace CommonUIUtils`
- L14 _externvar_ `extern float UISmallTextScaling;` (scope `CommonUIUtils`)
- L15 _externvar_ `extern float UISmallTextScalingThresholdMax;` (scope `CommonUIUtils`)
- L27 _prototype_ `bool ShouldDisplayMobileUISizes();` (scope `CommonUIUtils`)
- L29 _prototype_ `bool ShouldScaleText();` (scope `CommonUIUtils`)
- L37 _function_ `template <typename UserWidgetT = UUserWidget> UserWidgetT* GetOwningUserWidget(const UWidget* Widget)` (scope `CommonUIUtils`) — Traverses the UserWidgets that the given widget resides in until we find one matching the given type (or we run out of parents) @param Widget The widget whose parent we're seeking @return The first parent of the given type, or nullptr if there is none
- L70 _prototype_ `FString PrintAllOwningUserWidgets(const UWidget* Widget);` (scope `CommonUIUtils`) — Traverses the UserWidgets the given widget resides in and prints their names. Useful for debug logging. @param Widget The widget whose parents we'll print @return An FString containing the names of the parents
- L89 _prototype_ `void ValidateBoundWidgetHierarchy(const UWidgetTree& WidgetTree, IWidgetCompilerLog& CompileLog, ECollisionPolicy CollisionPolicy, FName ParentWidgetName, TArray<FName>&& ChildNames);` (scope `CommonUIUtils`) — Validates that a given widget tree hierarchy satisfies the condition that a given widget contains N other widgets (optionally requiring individual slots for each) Intended to be called from within a widget subclass's ValidateCompiledWidgetTree override If the given hierarchy does not satisfy the requirements, we'll log an error in the compiler log void MyWidget::ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, IWidgetCompilerLog& CompileLog) const { Super::ValidateCompiledWidgetTree(BlueprintWidgetTree, CompileLog); const CommonUIUtils::ECollisionPolicy CollisionPolicy = CommonUIUtils::ECollisionPolicy::Forbid; CommonUIUtils::ValidateBoundWidgetHierarchy(BlueprintWidgetTree, CompileLog, CollisionPolicy, GET_MEMBER_NAME_CHECKED(MyWidget, MySubWidget1Name), GET_MEMBER_NAME_CHECKED(MyWidget, MySubWidget2Name)); }
- L92 _function_ `template <typename... ChildNameArgs> void ValidateBoundWidgetHierarchy(const UWidgetTree& WidgetTree, IWidgetCompilerLog& CompileLog, ECollisionPolicy CollisionPolicy, FName ParentWidgetName, ChildNameArgs&&... ChildNames)` (scope `CommonUIUtils`)

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUIVisibilitySubsystem.h` (Public)


#### class `UCommonUIVisibilitySubsystem`  
`class UCommonUIVisibilitySubsystem : public ULocalPlayerSubsystem`  
_L22-70_
- reflection: `UCLASS(MinimalAPI, DisplayName = "UI Visibility Subsystem")`
- inherits: `ULocalPlayerSubsystem`
- L27 _public prototype_ `static UCommonUIVisibilitySubsystem* Get(const ULocalPlayer* LocalPlayer);`
- L28 _public prototype_ `static UCommonUIVisibilitySubsystem* GetChecked(const ULocalPlayer* LocalPlayer);`
- L30 _public prototype_ `UCommonUIVisibilitySubsystem();`
- L32 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L34 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L35 _public prototype_ `virtual void Deinitialize() override;`
- L37 _public prototype_ `DECLARE_EVENT_OneParam(UCommonUIVisibilitySubsystem, FHardwareVisibilityTagsChangedEvent, UCommonUIVisibilitySubsystem*);`
- L38 _public member_ `FHardwareVisibilityTagsChangedEvent OnVisibilityTagsChanged;`
- L44 _public function_ `const FGameplayTagContainer& GetVisibilityTags() const` — Get the visibility tags currently in play (the combination of platform traits and current input tags). These can change over time, if input mode changes, or other groups are removed/added.
- L49 _public function_ `bool HasVisibilityTag(const FGameplayTag VisibilityTag) const` — Returns true if the player currently has the specified visibility tag (note: this value should not be cached without listening for OnVisibilityTagsChanged as it can change at runtime)
- L51 _public prototype_ `void AddUserVisibilityCondition(const FGameplayTag UserTag);`
- L52 _public prototype_ `void RemoveUserVisibilityCondition(const FGameplayTag UserTag);`
- L55 _public prototype_ `static void SetDebugVisibilityConditions(const FGameplayTagContainer& TagsToEnable, const FGameplayTagContainer& TagsToSuppress);`
- L59 _protected prototype_ `void RefreshVisibilityTags();`
- L60 _protected prototype_ `void OnInputMethodChanged(ECommonInputType CurrentInputType);`
- L61 _protected prototype_ `virtual FGameplayTagContainer ComputeVisibilityTags() const;`
- L64 _private member_ `FGameplayTagContainer ComputedVisibilityTags;`
- L65 _private member_ `FGameplayTagContainer UserVisibilityTags;`
- L67 _private member_ `static FGameplayTagContainer DebugTagsToEnable;`
- L68 _private member_ `static FGameplayTagContainer DebugTagsToSuppress;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHardwareVisibilityTagsChangedDynamicEvent, UCommonUIVisibilitySubsystem*, TagSubsystem);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHardwareVisibilityTagsChangedDynamicEvent, UCommonUIVisibilitySubsystem*, TagSubsystem);`
- L37 _delegate_ `DECLARE_EVENT_OneParam(UCommonUIVisibilitySubsystem, FHardwareVisibilityTagsChangedEvent, UCommonUIVisibilitySubsystem*);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUserWidget.h` (Public)


#### enum `ECommonUIScrollRecipientOwningNodeSource`  
`enum ECommonUIScrollRecipientOwningNodeSource : uint8`  
_L23-30_
- desc: Enum to represent which common UI tree node takes scroll input
- L26 _public enumerator_ `ScrollRecipient` — The scroll recipient owner takes scroll input
- L29 _public enumerator_ `RegisteringUserWidget` — The userwidget that is registering the scroll recipient takes scroll input. It may or may not be the same as scroll recipient owner.

#### class `UCommonUserWidget`  
`class UCommonUserWidget : public UUserWidget`  
_L33-141_
- reflection: `UCLASS(MinimalAPI, ClassGroup = UI, meta = (Category = "Common UI", DisableNativeTick))`
- inherits: `UUserWidget`
- L40 _public prototype_ `void SetConsumePointerInput(bool bInConsumePointerInput);` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Sets whether or not this widget will consume ALL pointer input that reaches it
- L44 _public prototype_ `void RegisterScrollRecipientExternal(const UWidget* AnalogScrollRecipient);` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Add a widget to the list of widgets to get scroll events for this input root node
- L48 _public prototype_ `void UnregisterScrollRecipientExternal(const UWidget* AnalogScrollRecipient);` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Remove a widget from the list of widgets to get scroll events for this input root node
- L51 _public prototype_ `virtual class UWorld* GetWorld() const override;`
- L56 _public function_ `const TArray<FUIActionBindingHandle>& GetActionBindings() const`
- L57 _public function_ `const TArray<TWeakObjectPtr<const UWidget>> GetScrollRecipients() const`
- L63 _public prototype_ `FUIActionBindingHandle RegisterUIActionBinding(const FBindUIActionArgs& BindActionArgs);` — Convenience methods for menu action registrations (any UWidget can register via FCommonUIActionRouter directly, though generally that shouldn't be needed). Persistent bindings are *always* listening for input while registered, while normal bindings are only listening when all of this widget's activatable parents are activated.
- L68 _public prototype_ `FUIActionBindingHandle RegisterUIAction(const UInputAction* EnhancedInputAction, bool ShouldDisplayInActionBar = true);` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Helper to register a UI Enhanced Input Action from BP, they are meant to be global UI action to work with Enhanced Input See the UCommonMappingContextMetadata set in the Input Action User Settings Section
- L72 _public prototype_ `TArray<FUIActionBindingHandle> RegisterUIActionsFromMappingContext(const UInputMappingContext* MappingContext, bool ShouldDisplayInActionBar = true);` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Similar to RegisterUIAction but uses a Mapping Context
- L76 _public prototype_ `void RemoveUIAction(FUIActionBindingHandle ActionBinding);` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Remove a register UI Action. Will silently fail as CommonActionRouter doesn't give Feedback
- L80 _public prototype_ `void RemoveAllUIActionBinding();` — `UFUNCTION(BlueprintCallable, Category = CommonUserWidget)` — Remove All the UI Action that were registered on this widget
- L82 _public prototype_ `void RemoveActionBinding(FUIActionBindingHandle ActionBinding);`
- L83 _public prototype_ `void AddActionBinding(FUIActionBindingHandle ActionBinding);`
- L86 _protected function_ `virtual ERequiresLegacyPlayer GetLegacyPlayerRequirement() const override`
- L88 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L89 _protected prototype_ `virtual void NativeDestruct() override;`
- L91 _protected prototype_ `virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L92 _protected prototype_ `virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L93 _protected prototype_ `virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L94 _protected prototype_ `virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L95 _protected prototype_ `virtual FReply NativeOnTouchGesture(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;`
- L96 _protected prototype_ `virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;`
- L97 _protected prototype_ `virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;`
- L98 _protected prototype_ `virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;`
- L100 _protected prototype_ `UCommonInputSubsystem* GetInputSubsystem() const;`
- L101 _protected prototype_ `UCommonUISubsystemBase* GetUISubsystem() const;`
- L102 _protected prototype_ `TSharedPtr<FSlateUser> GetOwnerSlateUser() const;`
- L105 _protected function_ `template <typename GameInstanceT = UGameInstance> GameInstanceT& GetGameInstanceChecked() const`
- L113 _protected function_ `template <typename PlayerControllerT = APlayerController> PlayerControllerT& GetOwningPlayerChecked() const`
- L120 _protected prototype_ `void RegisterScrollRecipient(const UWidget& AnalogScrollRecipient, ECommonUIScrollRecipientOwningNodeSource OwningNodeSource = ECommonUIScrollRecipientOwningNodeSource::ScrollRecipient);`
- L121 _protected prototype_ `void UnregisterScrollRecipient(const UWidget& AnalogScrollRecipient, ECommonUIScrollRecipientOwningNodeSource OwningNodeSource = ECommonUIScrollRecipientOwningNodeSource::ScrollRecipient);`
- L124 _protected prototype_ `virtual const FText GetPaletteCategory() override;`
- L129 _protected member_ `bool bDisplayInActionBar = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))` — True to generally display this widget's actions in the action bar, assuming it has actions.
- L135 _private member_ `bool bConsumePointerInput = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))` — Set this to true if you don't want any pointer (mouse and touch) input to bubble past this widget
- L139 _private member_ `TArray<FUIActionBindingHandle> ActionBindings;`
- L140 _private member_ `TArray<TWeakObjectPtr<const UWidget>> ScrollRecipients;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonVideoPlayer.h` (Public)


#### class `UCommonVideoPlayer`  
`class UCommonVideoPlayer : public UWidget`  
_L22-122_
- reflection: `UCLASS(MinimalAPI, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `UWidget`
- L27 _public prototype_ `UCommonVideoPlayer(const FObjectInitializer& Initializer);`
- L28 _public prototype_ `virtual void PostInitProperties() override;`
- L31 _public prototype_ `void SetVideo(UMediaSource* NewVideo);` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L33 _public prototype_ `void Seek(float PlaybackTime);` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L35 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L38 _public prototype_ `void SetPlaybackRate(float PlaybackRate);` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L40 _public prototype_ `void SetLooping(bool bShouldLoopPlayback);` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L42 _public prototype_ `void SetIsMuted(bool bInIsMuted);` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L44 _public prototype_ `void SetShouldMatchSize(bool bInMatchSize);` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L47 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L49 _public prototype_ `void Reverse();` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L51 _public prototype_ `void Pause();` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L53 _public prototype_ `void PlayFromStart();` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L56 _public prototype_ `float GetVideoDuration() const;` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L58 _public prototype_ `float GetPlaybackTime() const;` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L60 _public prototype_ `float GetPlaybackRate() const;` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L63 _public prototype_ `bool IsLooping() const;` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L65 _public prototype_ `bool IsPaused() const;` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L67 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L69 _public function_ `bool IsMuted() const` — `UFUNCTION(BlueprintCallable, Category="Video Player")`
- L71 _public function_ `FSimpleMulticastDelegate& OnPlaybackResumed()`
- L72 _public function_ `FSimpleMulticastDelegate& OnPlaybackPaused()`
- L73 _public function_ `FSimpleMulticastDelegate& OnPlaybackComplete()`
- L76 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L77 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L78 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L80 _protected prototype_ `void PlayInternal() const;`
- L81 _protected function_ `const UMediaPlayer& GetMediaPlayer() const`
- L82 _protected prototype_ `virtual void HandleMediaPlayerEvent(EMediaEvent EventType);`
- L83 _protected prototype_ `virtual void PlaybackTick(double InCurrentTime, float InDeltaTime);`
- L86 _protected prototype_ `virtual const FText GetPaletteCategory() override;`
- L90 _private prototype_ `EActiveTimerReturnType HandlePlaybackTick(double InCurrentTime, float InDeltaTime);`
- L94 _private member_ `TObjectPtr<UMediaSource> Video;` — `UPROPERTY(EditAnywhere, Category = VideoPlayer)`
- L98 _private member_ `bool bMatchSize = false;` — `UPROPERTY(EditAnywhere, Category = VideoPlayer)` — Should we match the size of the media source when it opens?
- L101 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(Transient)`
- L104 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(Transient)`
- L107 _private member_ `TObjectPtr<UMaterial> VideoMaterial;` — `UPROPERTY(Transient)`
- L110 _private member_ `TObjectPtr<UMediaSoundComponent> SoundComponent;` — `UPROPERTY(Transient)`
- L113 _private member_ `FSlateBrush VideoBrush;` — `UPROPERTY(Transient)`
- L115 _private member_ `mutable FSimpleMulticastDelegate OnPlaybackResumedEvent;`
- L116 _private member_ `mutable FSimpleMulticastDelegate OnPlaybackPausedEvent;`
- L117 _private member_ `mutable FSimpleMulticastDelegate OnPlaybackCompleteEvent;`
- L120 _private member_ `bool bIsMuted = false;`
- L121 _private member_ `TSharedPtr<SImage> MyImage;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonVisibilitySwitcher.h` (Public)


#### class `UCommonVisibilitySwitcher`  
`class UCommonVisibilitySwitcher : public UOverlay`  
_L15-104_
- reflection: `UCLASS(MinimalAPI, meta = (DisableNativeTick))`
- inherits: `UOverlay`
- desc: Basic switcher that toggles visibility on its children to only show one widget at a time. Activates visible widget if possible.
- L22 _public prototype_ `void SetActiveWidgetIndex(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L25 _public function_ `int32 GetActiveWidgetIndex() const` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L28 _public prototype_ `UWidget* GetActiveWidget() const;` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L31 _public prototype_ `void SetActiveWidget(const UWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L34 _public prototype_ `void IncrementActiveWidgetIndex(bool bAllowWrapping = true);` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L37 _public prototype_ `void DecrementActiveWidgetIndex(bool bAllowWrapping = true);` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L40 _public prototype_ `void ActivateVisibleSlot();` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L43 _public prototype_ `void DeactivateVisibleSlot();` — `UFUNCTION(BlueprintCallable, Category = CommonVisibilitySwitcher)`
- L46 _public function_ `bool IsCurrentlySwitching() const` — `UFUNCTION(BlueprintPure, Category = CommonVisibilitySwitcher)`
- L48 _public prototype_ `UWidget* GetWidgetAtIndex(int32 Index) const;`
- L50 _public prototype_ `virtual void SynchronizeProperties() override;`
- L52 _public prototype_ `void MoveChild(int32 CurrentIdx, int32 NewIdx);`
- L54 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveWidgetIndexChanged, int32) FOnActiveWidgetIndexChanged& OnActiveWidgetIndexChanged() const`
- L60 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L61 _public prototype_ `virtual void OnDescendantSelectedByDesigner(UWidget* DescendantWidget) override;`
- L62 _public prototype_ `virtual void OnDescendantDeselectedByDesigner(UWidget* DescendantWidget) override;`
- L64 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L68 _protected prototype_ `virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;`
- L72 _private member_ `int32 DesignTime_ActiveIndex = INDEX_NONE;`
- L77 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L78 _protected prototype_ `virtual UClass* GetSlotClass() const override;`
- L79 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* InSlot) override;`
- L80 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* InSlot) override;`
- L84 _protected prototype_ `virtual void SetActiveWidgetIndex_Internal(int32 Index, bool bBroadcastChange = true);`
- L85 _protected prototype_ `void ResetSlotVisibilities();`
- L88 _protected member_ `ESlateVisibility ShownVisibility = ESlateVisibility::SelfHitTestInvisible;` — `UPROPERTY(EditAnywhere, Category = CommonVisibilitySwitcher)`
- L91 _protected member_ `int32 ActiveWidgetIndex = 0;` — `UPROPERTY(EditAnywhere, Category = CommonVisibilitySwitcher, meta = (ClampMin = -1))`
- L95 _protected member_ `bool bAutoActivateSlot = true;` — `UPROPERTY(EditAnywhere, Category = CommonVisibilitySwitcher)` — Whether or not to automatically activate a slot when it becomes visible
- L99 _protected member_ `bool bActivateFirstSlotOnAdding = false;` — `UPROPERTY(EditAnywhere, Category = CommonVisibilitySwitcher)` — Whether or not to activate the first slot if one is added dynamically
- L101 _protected member_ `bool bCurrentlySwitching = false;`
- L103 _protected member_ `mutable FOnActiveWidgetIndexChanged OnActiveWidgetIndexChangedEvent;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveWidgetIndexChanged, int32) FOnActiveWidgetIndexChanged& OnActiveWidgetIndexChanged() const { return OnActiveWidgetIndexChangedEvent; } #if WITH_EDITOR public: virtual const FText GetPaletteCategory() override;`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonVisibilitySwitcherSlot.h` (Public)


#### class `UCommonVisibilitySwitcherSlot`  
`class UCommonVisibilitySwitcherSlot : public UOverlaySlot`  
_L17-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UOverlaySlot`
- L23 _public prototype_ `UCommonVisibilitySwitcherSlot(const FObjectInitializer& Initializer);`
- L25 _public prototype_ `virtual void BuildSlot(TSharedRef<SOverlay> InOverlay) override;`
- L27 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L29 _public prototype_ `void SetSlotVisibility(ESlateVisibility Visibility);`
- L31 _public function_ `const TSharedPtr<SBox>& GetVisibilityBox() const`
- L35 _private member_ `TSharedPtr<SBox> VisibilityBox;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonVisibilityWidgetBase.h` (Public)


#### class `UDEPRECATED_UCommonVisibilityWidgetBase`  
`class UDEPRECATED_UCommonVisibilityWidgetBase : public UCommonBorder`  
_L18-54_
- reflection: `UCLASS(MinimalAPI, Deprecated)`
- inherits: `UCommonBorder`
- desc: A container that controls visibility based on Input type and Platform
- L24 _public member_ `TMap<FName, bool> VisibilityControls;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Visibility", meta = (GetOptions = GetRegisteredPlatforms))`
- L27 _public member_ `bool bShowForGamepad;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L30 _public member_ `bool bShowForMouseAndKeyboard;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L33 _public member_ `bool bShowForTouch;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L36 _public member_ `ESlateVisibility VisibleType;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L39 _public member_ `ESlateVisibility HiddenType;` — `UPROPERTY(EditAnywhere, Category = "Visibility")`
- L43 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L46 _protected prototype_ `void UpdateVisibility();`
- L48 _protected prototype_ `void ListenToInputMethodChanged(bool bListen = true);`
- L50 _protected prototype_ `void HandleInputMethodChanged(ECommonInputType input);`
- L53 _protected prototype_ `static const TArray<FName>& GetRegisteredPlatforms();` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonVisualAttachment.h` (Public)


#### class `UCommonVisualAttachment`  
`class UCommonVisualAttachment : public USizeBox`  
_L15-42_
- reflection: `UCLASS(MinimalAPI, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `USizeBox`
- desc: Adds a widget as a zero-size attachment to another. Think icons to the left of labels, without changing the computed size of the label.
- L20 _public prototype_ `UCommonVisualAttachment(const FObjectInitializer& ObjectInitializer);`
- L25 _public member_ `FVector2D ContentAnchor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category="Child Layout")` — Content Anchor Point as a ratio of the content size. Use (1.0, 1.0) to anchor the content on the bottom right, (0.0) to anchor top left, (0.5, 0.5) to anchor centered.
- L28 _public prototype_ `FVector2D GetContentAnchor() const;` — Get Content Anchor Point
- L31 _public prototype_ `void SetContentAnchor(FVector2D InContentAnchor);` — Set Content Anchor Point
- L35 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L36 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L37 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L41 _private member_ `TSharedPtr<class SVisualAttachmentBox> MyAttachmentBox;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonWidgetCarousel.h` (Public)


#### class `UCommonWidgetCarousel`  
`class UCommonWidgetCarousel : public UPanelWidget`  
_L23-128_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UPanelWidget`
- desc: A widget switcher is like a tab control, but without tabs. At most one widget is visible at time.
- L30 _public member_ `int32 ActiveWidgetIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Carousel", meta=( UIMin=0, ClampMin=0 ))` — The slot index to display
- L36 _protected member_ `float MoveSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter="GetMoveSpeed", BlueprintSetter="SetMoveSpeed", Category="Carousel", meta=( UIMin=0, ClampMin=0 ))` — How quickly the carousel transitions when changing active widget
- L40 _protected member_ `bool bCacheChildren;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "GetCacheChildren", Setter = "SetCacheChildren", BlueprintGetter = "GetCacheChildren", BlueprintSetter = "SetCacheChildren", Category = "Carousel")` — Whether we should cache children to prevent them from being destroyed when not visible. Enable this to avoid ConstructWidget costs when changing index, disable to save memory
- L46 _public prototype_ `int32 GetActiveWidgetIndex() const;` — `UFUNCTION(BlueprintCallable, Category="Carousel")` — Gets the slot index of the currently active widget
- L50 _public prototype_ `virtual void SetActiveWidgetIndex( int32 Index );` — `UFUNCTION(BlueprintCallable, Category="Carousel")` — Activates the widget at the specified index.
- L54 _public prototype_ `virtual void SetActiveWidget(UWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category="Carousel")` — Activates the widget and makes it the active index.
- L58 _public prototype_ `UWidget* GetWidgetAtIndex( int32 Index ) const;` — `UFUNCTION(BlueprintCallable, Category = "Carousel")` — Get a widget at the provided index
- L61 _public prototype_ `void BeginAutoScrolling(float ScrollInterval = 10);` — `UFUNCTION(BlueprintCallable, Category="Carousel")`
- L64 _public prototype_ `void EndAutoScrolling();` — `UFUNCTION(BlueprintCallable, Category="Carousel")`
- L67 _public prototype_ `void NextPage();` — `UFUNCTION(BlueprintCallable, Category="Carousel")`
- L70 _public prototype_ `void PreviousPage();` — `UFUNCTION(BlueprintCallable, Category="Carousel")`
- L74 _public prototype_ `void SetMoveSpeed(float InMoveSpeed);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the Move Speed.
- L78 _public prototype_ `float GetMoveSpeed() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Gets the Move Speed.
- L82 _public prototype_ `void SetCacheChildren(bool InCacheChildren);` — `UFUNCTION(BlueprintCallable, Category="Widget")` — Sets the current caching behavior.
- L86 _public prototype_ `bool GetCacheChildren() const;` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Gets the current caching behavior.
- L89 _public member_ `FOnCurrentPageIndexChanged OnCurrentPageIndexChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Carousel")`
- L92 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L93 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L97 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L98 _public prototype_ `virtual void OnDescendantSelectedByDesigner(UWidget* DescendantWidget) override;`
- L99 _public prototype_ `virtual void OnDescendantDeselectedByDesigner(UWidget* DescendantWidget) override;`
- L102 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L107 _protected prototype_ `bool AutoScrollCallback(float DeltaTime);`
- L109 _protected prototype_ `TSharedRef<SWidget> OnGenerateWidgetForCarousel(UPanelSlot* PanelSlot);`
- L110 _protected prototype_ `void HandlePageChanged(int32 PageIndex);`
- L113 _protected prototype_ `virtual UClass* GetSlotClass() const override;` — UPanelWidget
- L114 _protected prototype_ `virtual void OnSlotAdded(UPanelSlot* InSlot) override;`
- L115 _protected prototype_ `virtual void OnSlotRemoved(UPanelSlot* InSlot) override;`
- L119 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L123 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L125 _protected member_ `TSharedPtr< SWidgetCarousel<UPanelSlot*> > MyCommonWidgetCarousel;`
- L127 _protected member_ `TArray< TSharedRef<SWidget> > CachedSlotWidgets;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONUI_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentPageIndexChanged, UCommonWidgetCarousel*, CarouselWidget, int32, CurrentPageIndex);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentPageIndexChanged, UCommonWidgetCarousel*, CarouselWidget, int32, CurrentPageIndex);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonWidgetCarouselNavBar.h` (Public)


#### class `UCommonWidgetCarouselNavBar`  
`class UCommonWidgetCarouselNavBar : public UWidget`  
_L19-71_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UWidget`
- desc: A Navigation control for a Carousel
- L26 _public member_ `TSubclassOf<UCommonButtonBase> ButtonWidgetType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CarouselNavBar")`
- L29 _public member_ `FMargin ButtonPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CarouselNavBar")`
- L36 _public prototype_ `void SetLinkedCarousel(UCommonWidgetCarousel* CommonCarousel);` — `UFUNCTION(BlueprintCallable, Category = "CarouselNavBar")` — Establishes the Widget Carousel instance that this Nav Bar should interact with @param CommonCarousel The carousel that this nav bar should be associated with and manipulate
- L40 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UWidget interface
- L44 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L49 _protected prototype_ `void HandlePageChanged(UCommonWidgetCarousel* CommonCarousel, int32 PageIndex);` — `UFUNCTION()`
- L52 _protected prototype_ `void HandleButtonClicked(UCommonButtonBase* AssociatedButton, int32 ButtonIndex);` — `UFUNCTION()`
- L55 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L58 _protected prototype_ `void RebuildButtons();`
- L61 _protected member_ `TSharedPtr<SHorizontalBox> MyContainer;`
- L64 _protected member_ `TObjectPtr<UCommonWidgetCarousel> LinkedCarousel;` — `UPROPERTY()`
- L67 _protected member_ `TObjectPtr<UCommonButtonGroupBase> ButtonGroup;` — `UPROPERTY()`
- L70 _protected member_ `TArray<TObjectPtr<UCommonButtonBase>> Buttons;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Groups/CommonButtonGroupBase.h` (Public)


#### class `UCommonButtonGroupBase`  
`class UCommonButtonGroupBase : public UCommonWidgetGroupBase`  
_L21-173_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCommonWidgetGroupBase`
- desc: Manages an arbitrary collection of CommonButton widgets. Ensures that no more (and optionally, no less) than one button in the group is selected at a time
- L25 _public prototype_ `UCommonButtonGroupBase();`
- L27 _public function_ `virtual TSubclassOf<UWidget> GetWidgetType() const override`
- L35 _public prototype_ `void SetSelectionRequired(bool bRequireSelection);` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)` — Sets whether the group should always have a button selected. @param bRequireSelection True to force the group to always have a button selected. If true and nothing is selected, will select the first entry. If empty, will select the first button added.
- L37 _public prototype_ `bool GetSelectionRequired() const;`
- L41 _public prototype_ `void DeselectAll();` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)` — Deselects all buttons in the group.
- L49 _public prototype_ `void SelectNextButton(bool bAllowWrap = true, const bool bAllowSound = true);` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)` — Selects the next button in the group @param bAllowWrap Whether to wrap to the first button if the last one is currently selected @param bAllowSound Whether the selected button should play its click sound
- L57 _public prototype_ `void SelectPreviousButton(bool bAllowWrap = true, const bool bAllowSound = true);` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)` — Selects the previous button in the group @param bAllowWrap Whether to wrap to the first button if the last one is currently selected @param bAllowSound Whether the selected button should play its click sound
- L65 _public prototype_ `void SelectButtonAtIndex(int32 ButtonIndex, const bool bAllowSound = true);` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)` — Selects a button at a specific index in the group. Clears all selection if given an invalid index. @param ButtonIndex The index of the button in the group to select @param bAllowSound Whether the selected button should play its click sound
- L72 _public prototype_ `int32 GetSelectedButtonIndex() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = BaseButtonGroup)` — Get the index of the currently selected button, if any. @param The index of the currently selected button in the group, or -1 if there is no selected button.
- L79 _public prototype_ `int32 GetHoveredButtonIndex() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = BaseButtonGroup)` — Get the index of the currently hovered button, if any. @param The index of the currently hovered button in the group, or -1 if there is no hovered button.
- L87 _public prototype_ `int32 FindButtonIndex(const UCommonButtonBase* ButtonToFind) const;` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)` — Find the button index of the specified button, if possible @param ButtonToFind	Button to find the index of @return Index of the button in the group. INDEX_NONE if not found
- L89 _public prototype_ `void ForEach(TFunctionRef<void(UCommonButtonBase&, int32)> Functor);`
- L91 _public prototype_ `DECLARE_EVENT_TwoParams(UCommonButtonGroupBase, FNativeSimpleButtonBaseGroupDelegate, UCommonButtonBase*, int32);`
- L94 _public member_ `FButtonLostSelectionDelegate OnSelectedButtonLostSelection;` — `UPROPERTY(BlueprintAssignable)`
- L97 _public member_ `FSimpleButtonBaseGroupDelegate OnSelectedButtonBaseChanged;` — `UPROPERTY(BlueprintAssignable)`
- L98 _public member_ `FNativeSimpleButtonBaseGroupDelegate NativeOnSelectedButtonBaseChanged;`
- L101 _public member_ `FSimpleButtonBaseGroupDelegate OnHoveredButtonBaseChanged;` — `UPROPERTY(BlueprintAssignable)`
- L102 _public member_ `FNativeSimpleButtonBaseGroupDelegate NativeOnHoveredButtonBaseChanged;`
- L105 _public member_ `FSimpleButtonBaseGroupDelegate OnButtonBaseClicked;` — `UPROPERTY(BlueprintAssignable)`
- L106 _public member_ `FNativeSimpleButtonBaseGroupDelegate NativeOnButtonBaseClicked;`
- L109 _public member_ `FSimpleButtonBaseGroupDelegate OnButtonBaseDoubleClicked;` — `UPROPERTY(BlueprintAssignable)`
- L110 _public member_ `FNativeSimpleButtonBaseGroupDelegate NativeOnButtonBaseDoubleClicked;`
- L112 _public prototype_ `DECLARE_EVENT(UCommonButtonGroupBase, FNativeOnSelectionCleared);`
- L115 _public member_ `FOnSelectionCleared OnSelectionCleared;` — `UPROPERTY(BlueprintAssignable)`
- L116 _public member_ `FNativeOnSelectionCleared NativeOnSelectionCleared;`
- L119 _public member_ `FSimpleButtonBaseGroupDelegate OnButtonBaseLockClicked;` — `UPROPERTY(BlueprintAssignable)`
- L120 _public member_ `FNativeSimpleButtonBaseGroupDelegate NativeOnButtonBaseLockClicked;`
- L123 _public member_ `FSimpleButtonBaseGroupDelegate OnButtonBaseLockDoubleClicked;` — `UPROPERTY(BlueprintAssignable)`
- L124 _public member_ `FNativeSimpleButtonBaseGroupDelegate NativeOnButtonBaseLockDoubleClicked;`
- L127 _public prototype_ `UCommonButtonBase* GetButtonBaseAtIndex(int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)`
- L130 _public prototype_ `UCommonButtonBase* GetSelectedButtonBase() const;` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)`
- L133 _public prototype_ `bool HasAnyButtons() const;` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)`
- L136 _public prototype_ `int32 GetButtonCount() const;` — `UFUNCTION(BlueprintCallable, Category = BaseButtonGroup)`
- L141 _protected member_ `bool bSelectionRequired;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BaseButtonGroup, meta = (ExposeOnSpawn="true"))` — If true, the group will force that a button be selected at all times
- L143 _protected prototype_ `virtual void OnWidgetAdded( UWidget* NewWidget ) override;`
- L144 _protected prototype_ `virtual void OnWidgetRemoved( UWidget* OldWidget ) override;`
- L145 _protected prototype_ `virtual void OnRemoveAll() override;`
- L148 _protected prototype_ `virtual void OnSelectionStateChangedBase( UCommonButtonBase* BaseButton, bool bIsSelected );` — `UFUNCTION()`
- L151 _protected prototype_ `virtual void OnHandleButtonBaseClicked(UCommonButtonBase* BaseButton);` — `UFUNCTION()`
- L154 _protected prototype_ `virtual void OnHandleButtonBaseDoubleClicked(UCommonButtonBase* BaseButton);` — `UFUNCTION()`
- L157 _protected prototype_ `virtual void OnButtonBaseHovered(UCommonButtonBase* BaseButton);` — `UFUNCTION()`
- L160 _protected prototype_ `virtual void OnButtonBaseUnhovered(UCommonButtonBase* BaseButton);` — `UFUNCTION()`
- L163 _protected prototype_ `virtual void OnHandleButtonBaseLockClicked(UCommonButtonBase* BaseButton);` — `UFUNCTION()`
- L166 _protected prototype_ `virtual void OnHandleButtonBaseLockDoubleClicked(UCommonButtonBase* BaseButton);` — `UFUNCTION()`
- L170 _protected member_ `TArray<TWeakObjectPtr<UCommonButtonBase>> Buttons;`
- L171 _protected member_ `int32 SelectedButtonIndex = INDEX_NONE;`
- L172 _protected member_ `int32 HoveredButtonIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSimpleButtonBaseGroupDelegate, UCommonButtonBase*, AssociatedButton, int32, ButtonIndex );`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSimpleButtonBaseGroupDelegate, UCommonButtonBase*, AssociatedButton, int32, ButtonIndex );`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonLostSelectionDelegate, UCommonButtonBase*, PreviouslySelectedButton);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonLostSelectionDelegate, UCommonButtonBase*, PreviouslySelectedButton);`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSelectionCleared );`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSelectionCleared );`
- L91 _delegate_ `DECLARE_EVENT_TwoParams(UCommonButtonGroupBase, FNativeSimpleButtonBaseGroupDelegate, UCommonButtonBase*, int32);`
- L112 _delegate_ `DECLARE_EVENT(UCommonButtonGroupBase, FNativeOnSelectionCleared);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Groups/CommonWidgetGroupBase.h` (Public)


#### class `UCommonWidgetGroupBase`  
`class UCommonWidgetGroupBase : public UObject`  
_L14-48_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject`
- desc: Base class for CommonUI widget groups, currently only used for button groups
- L19 _public prototype_ `UCommonWidgetGroupBase();`
- L21 _public function_ `virtual TSubclassOf<UWidget> GetWidgetType() const`
- L24 _public prototype_ `void AddWidget(UWidget* InWidget);` — `UFUNCTION(BlueprintCallable, Category = Group)`
- L27 _public prototype_ `void AddWidgets(const TArray<UWidget*>& Widgets);` — `UFUNCTION(BlueprintCallable, Category = Group)`
- L30 _public prototype_ `void RemoveWidget(UWidget* InWidget);` — `UFUNCTION(BlueprintCallable, Category = Group)`
- L33 _public prototype_ `void RemoveAll();` — `UFUNCTION(BlueprintCallable, Category = Group)`
- L36 _public function_ `template <typename WidgetT> void AddWidgets(const TArray<WidgetT>& Widgets)`
- L45 _protected prototype_ `virtual void OnWidgetAdded(UWidget* NewWidget) PURE_VIRTUAL(UCommonWidgetGroupBase::OnWidgetAdded, );`
- L46 _protected prototype_ `virtual void OnWidgetRemoved(UWidget* OldWidget) PURE_VIRTUAL(UCommonWidgetGroupBase::OnWidgetRemoved, );`
- L47 _protected prototype_ `virtual void OnRemoveAll() PURE_VIRTUAL(UCommonWidgetGroupBase::OnRemoveAll, );`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/ICommonUIModule.h` (Public)


#### class `ICommonUIModule`  
`class ICommonUIModule : public IModuleInterface`  
_L16-79_
- inherits: `IModuleInterface`
- desc: Interface for the purchase flow module.
- L27 _public function_ `static inline ICommonUIModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L45 _public function_ `static inline UCommonUISettings& GetSettings()` — @return reference to Common UI settings
- L57 _public function_ `static inline UCommonUIEditorSettings& GetEditorSettings()` — @return reference to Common UI Editor settings
- L67 _public prototype_ `virtual FStreamableManager& GetStreamableManager() const = 0;` — Streamable Management
- L70 _public prototype_ `virtual TAsyncLoadPriority GetLazyLoadPriority() const = 0;` — Lazy Load Priority
- L74 _protected prototype_ `virtual UCommonUISettings* GetSettingsInstance() const = 0;`
- L77 _protected prototype_ `virtual UCommonUIEditorSettings* GetEditorSettingsInstance() const = 0;`

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef int32 TAsyncLoadPriority;`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonAnalogCursor.h` (Public)


#### class `FCommonAnalogCursor`  
`class FCommonAnalogCursor : public FAnalogCursor, public FGCObject`  
_L35-183_
- inherits: `FAnalogCursor,FGCObject`
- desc: Analog cursor preprocessor that tastefully hijacks things a bit to support controller navigation by moving a hidden cursor around based on focus. Introduces a separate focus-driven mode of operation, wherein the cursor is made invisible and automatically updated to be centered over whatever widget is currently focused (except the game viewport - we completely hide it then)
- L39 _public function_ `template <typename AnalogCursorT = FCommonAnalogCursor> static TSharedRef<AnalogCursorT> CreateAnalogCursor(const UCommonUIActionRouterBase& InActionRouter)`
- L46 _public prototype_ `virtual void Deinitialize();`
- L48 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;`
- L49 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L50 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L52 _public prototype_ `virtual bool CanReleaseMouseCapture() const;`
- L54 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L55 _public prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L56 _public prototype_ `virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& InPointerEvent) override;`
- L57 _public prototype_ `virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& InPointerEvent) override;`
- L59 _public prototype_ `void SetCursorMovementStick(EAnalogStick InCursorMovementStick);`
- L61 _public prototype_ `virtual int32 GetOwnerUserIndex() const override;`
- L63 _public prototype_ `virtual void ShouldHandleRightAnalog(bool bInShouldHandleRightAnalog);`
- L65 _public function_ `virtual bool IsAnalogMovementEnabled() const`
- L67 _public prototype_ `virtual bool ShouldVirtualAcceptSimulateMouseButton(const FKeyEvent& InKeyEvent, EInputEvent InputEvent) const;`
- L69 _public prototype_ `void OnVirtualAcceptHoldCanceled();`
- L71 _public prototype_ `TWeakPtr<SWidget> GetLastCursorTarget() const;`
- L73 _public prototype_ `bool IsUsingFakeTouch() const;`
- L74 _public prototype_ `bool IsVirtualPointerEnabled() const;`
- L75 _public prototype_ `bool IsUsingVirtualPointer() const;`
- L76 _public prototype_ `void SetVirtualPointerVisibility(bool bVisible);`
- L78 _public prototype_ `FVirtualPointerEnabledChanged& GetOnVirtualPointerEnabledChanged();`
- L80 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L85 _public function_ `virtual FString GetReferencerName() const override`
- L88 _protected prototype_ `FCommonAnalogCursor(const UCommonUIActionRouterBase& InActionRouter);`
- L89 _protected prototype_ `virtual void Initialize();`
- L91 _protected prototype_ `virtual EOrientation DetermineScrollOrientation(const UWidget& Widget) const;`
- L93 _protected prototype_ `virtual bool IsRelevantInput(const FKeyEvent& KeyEvent) const override;`
- L94 _protected prototype_ `virtual bool IsRelevantInput(const FAnalogInputEvent& AnalogInputEvent) const override;`
- L96 _protected prototype_ `void SetNormalizedCursorPosition(const FVector2D& RelativeNewPosition);`
- L97 _protected prototype_ `bool IsInViewport(const FVector2D& Position) const;`
- L98 _protected prototype_ `FVector2D ClampPositionToViewport(const FVector2D& InPosition) const;`
- L99 _protected prototype_ `void HideCursor();`
- L101 _protected prototype_ `UGameViewportClient* GetViewportClient() const;`
- L109 _protected prototype_ `bool IsGameViewportInFocusPathWithoutCapture() const;` — A ridiculous function name, but we have this exact question in a few places. We don't care about input while our owning player's game viewport isn't involved in the focus path, but we also want to hold off doing anything while that game viewport has full capture. So we need that "relevant, but not exclusive" sweet spot.
- L111 _protected prototype_ `virtual void RefreshCursorSettings();`
- L112 _protected prototype_ `virtual void RefreshCursorVisibility();`
- L114 _protected prototype_ `virtual void HandleInputMethodChanged(ECommonInputType NewInputMethod);`
- L116 _protected prototype_ `bool IsUsingGamepad() const;`
- L118 _protected prototype_ `bool ShouldHideCursor() const;`
- L121 _protected member_ `const UCommonUIActionRouterBase& ActionRouter;` — Knowingly unorthodox member reference to a UObject - ok because we are a subobject of the owning router and will never outlive it
- L122 _protected member_ `ECommonInputType ActiveInputMethod;`
- L124 _protected member_ `bool bEnableCommonUIVirtualPointer = false;`
- L125 _protected member_ `bool bIsAnalogMovementEnabled = false;`
- L127 _protected member_ `bool bShouldHandleRightAnalog = true;`
- L129 _protected member_ `FVirtualPointerEnabledChanged OnVirtualPointerEnabledChanged;`
- L133 _private prototype_ `void HandleOnEnableVirtualPointerChanged(IConsoleVariable* ConsoleVariable);`
- L134 _private prototype_ `void UpdateInputPreProcessor();`
- L135 _private prototype_ `TObjectPtr<UUserWidget> GetOrLoadDefaultVirtualPointer();`
- L136 _private prototype_ `void OnDefaultVirtualPointerClassLoaded();`
- L137 _private prototype_ `void UpdateVirtualPointerVisualState();`
- L140 _private member_ `TSet<FKey> PointerButtonDownKeys;` — The current set of pointer buttons being used as keys.
- L142 _private member_ `TWeakPtr<SWidget> LastCursorTarget;`
- L143 _private member_ `FSlateRenderTransform LastCursorTargetTransform;`
- L145 _private member_ `TOptional<FKeyEvent> ActiveKeyUpEvent;`
- L147 _private member_ `TObjectPtr<UUserWidget> DefaultVirtualPointerWidget = nullptr;`
- L148 _private member_ `TObjectPtr<UUserWidget> VirtualPointerWidget = nullptr;`
- L151 _private member_ `TSharedPtr<FStreamableHandle> DefaultVirtualPointerLoadHandle;` — In-flight async load handle for the default virtual pointer class. Reset once load completes or is cancelled.
- L153 _private member_ `bool bDefaultVirtualPointerLoadFailed = false;` — Set when the configured class fails to resolve so we don't keep firing async loads every frame.
- L155 _private member_ `float TimeUntilScrollUpdate = 0.f;`
- L158 _private member_ `bool bLastCursorInputWasGamepad = false;` — UE-380247: was the last cursor input a gamepad stick?
- L160 _private member_ `bool bIgnoreNextMouseMove = false;` — Swallow the synthetic mouse-move that follows our SetCursorPosition.
- L162 _private member_ `bool bShowVirtualPointer = false;`
- L163 _private member_ `bool bLastBroadcastVirtualPointerEnabled = false;`
- L166 _private member_ `TWeakObjectPtr<UUserWidget> LastAppliedSoftwareCursorWidget;` — Skips per-tick UUserWidget::TakeWidget() rebuilds in RefreshCursorVisibility when unchanged.
- L167 _private member_ `ECursorVisualState CurrentVirtualPointerVisualState = ECursorVisualState::Default;`
- L168 _private member_ `bool bVirtualAcceptDown = false;`
- L169 _private member_ `float HoldElapsedTime = 0.f;`
- L181 _private member_ `int32 ShoulderButtonStatus = EShoulderButtonFlags::None;`

#### enum `FCommonAnalogCursor::EShoulderButtonFlags`  
`enum EShoulderButtonFlags`  
_L172-180_
- L174 _public enumerator_ `None = 0`
- L175 _public enumerator_ `LeftShoulder = 1 << 0`
- L176 _public enumerator_ `RightShoulder = 1 << 1`
- L177 _public enumerator_ `LeftTrigger = 1 << 2`
- L178 _public enumerator_ `RightTrigger = 1 << 3`
- L179 _public enumerator_ `All = LeftShoulder | RightShoulder | LeftTrigger | RightTrigger`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COMMONUI_API`
- L27 _delegate_ `DECLARE_EVENT_OneParam(FCommonAnalogCursor, FVirtualPointerEnabledChanged, bool);`
- L27 _prototype_ `DECLARE_EVENT_OneParam(FCommonAnalogCursor, FVirtualPointerEnabledChanged, bool);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonAnalogCursorTypes.h` (Public)


#### enum `ECursorVisualState`  
`enum class ECursorVisualState : uint8`  
_L14-21_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Cumulative cursor visual states - flags can combine (e.g. Hover + Pressed + Drag). Default (no flags) represents the idle state.
- L16 _public enumerator_ `Default = 0 UMETA(Hidden)`
- L17 _public enumerator_ `Hover = 1 << 0`
- L18 _public enumerator_ `Pressed = 1 << 1`
- L19 _public enumerator_ `Drag = 1 << 2`
- L20 _public enumerator_ `Hold = 1 << 3`

#### class `UVirtualPointerVisualStateInterface`  
`class UVirtualPointerVisualStateInterface : public UInterface`  
_L26-29_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI)`
- inherits: `UInterface`
- desc: Implement this interface on a widget to receive cursor visual state changes from FCommonAnalogCursor.

#### class `IVirtualPointerVisualStateInterface`  
`class IVirtualPointerVisualStateInterface`  
_L31-42_
- L37 _public prototype_ `void OnVirtualPointerVisualStateChanged(ECursorVisualState PreviousStates, ECursorVisualState ActiveStates);` — `UFUNCTION(BlueprintImplementableEvent, Category = "CommonUI|VirtualPointer")` — Fired when the cumulative state flags change. PreviousStates and ActiveStates carry combined flags.
- L41 _public prototype_ `void OnVirtualPointerHoldProgress(float Progress);` — `UFUNCTION(BlueprintImplementableEvent, Category = "CommonUI|VirtualPointer")` — Fired each tick while the accept button is held. Progress goes from 0.0 to 1.0 over MaxHoldDuration.

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonBoundActionBar.h` (Public)


#### class `UCommonBoundActionBar`  
`class UCommonBoundActionBar : public UDynamicEntryBoxBase`  
_L24-80_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = UI, meta = (Category = "Common UI"))`
- inherits: `UDynamicEntryBoxBase`
- desc: A box populated with current actions available per CommonUI's Input Handler.
- L30 _public prototype_ `void SetDisplayOwningPlayerActionsOnly(bool bShouldOnlyDisplayOwningPlayerActions);` — `UFUNCTION(BlueprintCallable, Category = CommonBoundActionBar)`
- L33 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L34 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L35 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L37 _protected function_ `virtual void NativeOnActionButtonCreated(ICommonBoundActionButtonInterface* ActionButton, const FUIActionBindingHandle& RepresentedAction)`
- L39 _protected function_ `virtual void ActionBarUpdateBeginImpl()`
- L40 _protected function_ `virtual void ActionBarUpdateEndImpl()`
- L42 _protected prototype_ `virtual UUserWidget* CreateActionButton(const FUIActionBindingHandle& BindingHandle);`
- L44 _protected function_ `TSubclassOf<UCommonButtonBase> GetActionButtonClass()`
- L47 _protected prototype_ `void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;`
- L51 _private prototype_ `void HandledInputTypeUpdated(ECommonInputType InputType);`
- L52 _private prototype_ `void HandleBoundActionsUpdated(bool bFromOwningPlayer);`
- L54 _private prototype_ `void HandleInputMappingsRebuiltUpdated();` — `UFUNCTION()`
- L55 _private prototype_ `void UpdateDisplay();`
- L56 _private prototype_ `bool IsSafeToUpdateDisplay() const;`
- L57 _private prototype_ `void HandleDeferredDisplayUpdate();`
- L58 _private prototype_ `void HandlePlayerAdded(int32 PlayerIdx);`
- L59 _private prototype_ `void HandlePlayerRemoved(int32 PlayerIdx);`
- L61 _private prototype_ `void MonitorPlayerActions(const ULocalPlayer* NewPlayer);`
- L63 _private prototype_ `void ActionBarUpdateBegin();`
- L64 _private prototype_ `void ActionBarUpdateEnd();`
- L65 _private prototype_ `bool DoAnyActionButtonsHaveMouseCapture() const;`
- L68 _private member_ `TSubclassOf<UCommonButtonBase> ActionButtonClass;` — `UPROPERTY(EditAnywhere, Category = EntryLayout, meta=(MustImplement = "/Script/CommonUI.CommonBoundActionButtonInterface"))`
- L71 _private member_ `bool bDisplayOwningPlayerActionsOnly = true;` — `UPROPERTY(EditAnywhere, Category = Display)`
- L74 _private member_ `bool bIgnoreDuplicateActions = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Display)`
- L77 _private member_ `FActionBarUpdated OnActionBarUpdated;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true))`
- L79 _private member_ `bool bIsRefreshQueued = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionBarUpdated);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionBarUpdated);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonBoundActionButton.h` (Public)


#### class `UCommonBoundActionButton`  
`class UCommonBoundActionButton : public UCommonButtonBase, public ICommonBoundActionButtonInterface`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, Abstract, meta = (DisableNativeTick))`
- inherits: `UCommonButtonBase,ICommonBoundActionButtonInterface`
- L21 _public prototype_ `virtual void SetRepresentedAction(FUIActionBindingHandle InBindingHandle) override;`
- L25 _protected prototype_ `virtual void NativeOnClicked() override;`
- L26 _protected prototype_ `virtual void NativeOnCurrentTextStyleChanged() override;`
- L28 _protected prototype_ `virtual void UpdateInputActionWidget() override;`
- L29 _protected prototype_ `virtual void UpdateHoldData(ECommonInputType CurrentInputType) override;`
- L32 _protected prototype_ `void OnUpdateInputAction();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Common Bound Action")`
- L36 _protected member_ `TObjectPtr<UCommonTextBlock> Text_ActionName;` — `UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Text Block")`
- L40 _protected member_ `bool bLinkRequiresHoldToBindingHold = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Hold")` — Set to true if clicking this button should require holding it when the bound action is a hold action
- L43 _private member_ `FUIActionBindingHandle BindingHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonBoundActionButtonInterface.h` (Public)


#### class `UCommonBoundActionButtonInterface`  
`class UCommonBoundActionButtonInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICommonBoundActionButtonInterface`  
`class ICommonBoundActionButtonInterface`  
_L20-26_
- desc: Interface for runtime bindable action buttons. Allows button widget to be used by CommonBoundActionBar.
- L25 _public prototype_ `virtual void SetRepresentedAction(FUIActionBindingHandle InBindingHandle) = 0;`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonGenericInputActionDataTable.h` (Public)


#### class `UCommonGenericInputActionDataTable`  
`class UCommonGenericInputActionDataTable : public UDataTable`  
_L18-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataTable`
- desc: Overrides postload to allow for derived classes to perform code-level changes to the datatable. Ex: Per-platform edits. Allows modification of datatable data without checking out the data table asset.
- L23 _public prototype_ `UCommonGenericInputActionDataTable();`
- L24 _public prototype_ `virtual ~UCommonGenericInputActionDataTable() = default;`
- L27 _public prototype_ `virtual void PostLoad() override;`

#### class `UCommonInputActionDataProcessor`  
`class UCommonInputActionDataProcessor : public UObject`  
_L35-44_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: Derive from to process common input action datatable
- L40 _public prototype_ `UCommonInputActionDataProcessor() = default;`
- L41 _public prototype_ `virtual ~UCommonInputActionDataProcessor() = default;`
- L43 _public prototype_ `virtual void ProcessInputActions(UCommonGenericInputActionDataTable* InputActionDataTable);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonInputMode.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonUIActionRouterBase.h` (Public)


#### enum `ERouteUIInputResult`  
`enum class ERouteUIInputResult : uint8`  
_L52-57_
- L54 _public enumerator_ `Handled`
- L55 _public enumerator_ `BlockGameInput`
- L56 _public enumerator_ `Unhandled`

#### class `UCommonUIActionRouterBase`  
`class UCommonUIActionRouterBase : public ULocalPlayerSubsystem`  
_L66-300_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULocalPlayerSubsystem`
- desc: The nucleus of the CommonUI input routing system. Gathers input from external sources such as game viewport client and forwards them to widgets via activatable tree node representation.
- L71 _public prototype_ `static UCommonUIActionRouterBase* Get(const UWidget& ContextWidget);`
- L74 _public prototype_ `static UCommonActivatableWidget* FindOwningActivatable(TSharedPtr<SWidget> Widget, ULocalPlayer* OwningLocalPlayer);` — searches up the SWidget tree until it finds the nearest UCommonActivatableWidget (excluding checking Widget itself)
- L76 _public prototype_ `static UCommonActivatableWidget* FindActivatable(TSharedPtr<SWidget> Widget, ULocalPlayer* OwningLocalPlayer);` — searches up the SWidget tree until it finds the nearest UCommonActivatableWidget (including checking Widget itself)
- L78 _public prototype_ `UCommonUIActionRouterBase();`
- L79 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L80 _public prototype_ `virtual void Deinitialize() override;`
- L81 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L84 _public prototype_ `virtual void SetIsActivatableTreeEnabled(bool bInIsTreeEnabled);` — Sets whether the underlying activatable tree system is enabled - when disabled, all we really do is process Persistent input actions
- L86 _public prototype_ `virtual FUIActionBindingHandle RegisterUIActionBinding(const UWidget& Widget, const FBindUIActionArgs& BindActionArgs);`
- L88 _public prototype_ `bool RegisterLinkedPreprocessor(const UWidget& Widget, const TSharedRef<IInputProcessor>& InputPreprocessor, int32 DesiredIndex);` — `UE_DEPRECATED(5.5, "The version of RegisterLinkedPreprocessor taking an int32 DesiredIndex parameter is deprecated and uses EInputPreProcessorType::Game as a default. For greater control in pre-processor priority, please use the new version with a FInputPreprocessorRegistrationInfo parameter")`
- L89 _public prototype_ `bool RegisterLinkedPreprocessor(const UWidget& Widget, const TSharedRef<IInputProcessor>& InputPreprocessor);`
- L90 _public prototype_ `bool RegisterLinkedPreprocessor(const UWidget& Widget, const TSharedRef<IInputProcessor>& InputPreprocessor, const FInputPreprocessorRegistrationKey& RegistrationInfo);`
- L92 _public prototype_ `DECLARE_EVENT_OneParam(UCommonUIActionRouterBase, FOnActiveInputModeChanged, ECommonInputMode);`
- L93 _public function_ `FOnActiveInputModeChanged& OnActiveInputModeChanged() const`
- L94 _public prototype_ `ECommonInputMode GetActiveInputMode(ECommonInputMode DefaultInputMode = ECommonInputMode::All) const;`
- L95 _public prototype_ `EMouseCaptureMode GetActiveMouseCaptureMode(EMouseCaptureMode DefaultMouseCapture = EMouseCaptureMode::NoCapture) const;`
- L97 _public prototype_ `DECLARE_EVENT_OneParam(UCommonUIActionRouterBase, FOnActiveInputConfigChanged, const FUIInputConfig);`
- L98 _public function_ `FOnActiveInputConfigChanged& OnActiveInputConfigChanged() const`
- L100 _public prototype_ `DECLARE_EVENT_OneParam(UCommonUIActionRouterBase, FOnActivationMetadataChanged, FActivationMetadata);`
- L101 _public function_ `FOnActivationMetadataChanged& OnActivationMetadataChanged() const`
- L103 _public prototype_ `void RegisterScrollRecipient(const UWidget& ScrollableWidget, UWidget* OwningNodeWidget = nullptr);`
- L104 _public prototype_ `void UnregisterScrollRecipient(const UWidget& ScrollableWidget, UWidget* OwningNodeWidget = nullptr);`
- L105 _public prototype_ `TArray<const UWidget*> GatherActiveAnalogScrollRecipients() const;`
- L107 _public prototype_ `TArray<FUIActionBindingHandle> GatherActiveBindings() const;`
- L108 _public function_ `FSimpleMulticastDelegate& OnBoundActionsUpdated() const`
- L110 _public prototype_ `UCommonInputSubsystem& GetInputSubsystem() const;`
- L112 _public prototype_ `virtual ERouteUIInputResult ProcessInput(FKey Key, EInputEvent InputEvent) const;`
- L113 _public prototype_ `virtual bool CanProcessNormalGameInput() const;`
- L115 _public prototype_ `bool IsPendingTreeChange() const;`
- L117 _public function_ `TSharedPtr<FCommonAnalogCursor> GetCommonAnalogCursor() const`
- L119 _public prototype_ `void FlushInput();`
- L121 _public prototype_ `bool IsWidgetInActiveRoot(const UCommonActivatableWidget* Widget) const;`
- L122 _public prototype_ `bool IsWidgetInLeafmostNodeHierarchy(const UWidget& Widget) const;`
- L124 _public prototype_ `UCommonActivatableWidget* GetLeafmostActivatableWidget() const;`
- L132 _public prototype_ `void SetActiveUIInputConfig(const FUIInputConfig& NewConfig, const UObject* InConfigSource = nullptr);` — Sets Input Config @param NewConfig config to set @param InConfigSource optional source of config. If exists, will be used to log input config source
- L135 _public prototype_ `void NotifyUserWidgetConstructed(const UCommonUserWidget& Widget);`
- L136 _public prototype_ `void NotifyUserWidgetDestructed(const UCommonUserWidget& Widget);`
- L138 _public prototype_ `virtual void AddBinding(FUIActionBindingHandle Binding);`
- L139 _public prototype_ `virtual void RemoveBinding(FUIActionBindingHandle Binding);`
- L141 _public prototype_ `int32 GetLocalPlayerIndex() const;`
- L143 _public prototype_ `void RefreshActiveRootFocusRestorationTarget() const;`
- L144 _public prototype_ `void RefreshActiveRootFocus();`
- L145 _public prototype_ `void RefreshUIInputConfig();`
- L147 _public prototype_ `bool ShouldAlwaysShowCursor() const;`
- L150 _protected prototype_ `virtual TSharedRef<FCommonAnalogCursor> MakeAnalogCursor() const;`
- L151 _protected prototype_ `virtual void PostAnalogCursorCreate();`
- L152 _protected prototype_ `void RegisterAnalogCursorTick();`
- L154 _protected prototype_ `TWeakPtr<FActivatableTreeRoot> GetActiveRoot() const;`
- L155 _protected prototype_ `virtual void SetActiveRoot(FActivatableTreeRootPtr NewActiveRoot);`
- L156 _protected prototype_ `void SetForceResetActiveRoot(bool bInForceResetActiveRoot);`
- L158 _protected prototype_ `virtual void ApplyUIInputConfig(const FUIInputConfig& NewConfig, bool bForceRefresh);`
- L159 _protected prototype_ `void UpdateLeafNodeAndConfig(FActivatableTreeRootPtr DesiredRoot, FActivatableTreeNodePtr DesiredLeafNode);`
- L160 _protected prototype_ `void FlushPressedKeys() const;`
- L162 _protected prototype_ `void RefreshActionDomainLeafNodeConfig();`
- L164 _protected member_ `bool bIsActivatableTreeEnabled = true;`
- L167 _protected member_ `TOptional<FUIInputConfig> ActiveInputConfig;` — The currently applied UI input configuration
- L169 _protected member_ `TSharedPtr<FCommonAnalogCursor> AnalogCursor;`
- L170 _protected member_ `FTSTicker::FDelegateHandle TickHandle;`
- L173 _private prototype_ `bool Tick(float DeltaTime);`
- L175 _private prototype_ `void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L176 _private prototype_ `void PopulateAutoCompleteEntries(TArray<FAutoCompleteCommand>& AutoCompleteList);`
- L178 _private prototype_ `void RegisterWidgetBindings(const FActivatableTreeNodePtr& TreeNode, const TArray<FUIActionBindingHandle>& BindingHandles);`
- L180 _private prototype_ `FActivatableTreeNodePtr FindNode(const UCommonActivatableWidget* Widget) const;`
- L181 _private prototype_ `FActivatableTreeNodePtr FindOwningNode(const UWidget& Widget) const;`
- L182 _private prototype_ `FActivatableTreeNodePtr FindNodeRecursive(const FActivatableTreeNodePtr& CurrentNode, const UCommonActivatableWidget& Widget) const;`
- L183 _private prototype_ `FActivatableTreeNodePtr FindNodeRecursive(const FActivatableTreeNodePtr& CurrentNode, const TSharedPtr<SWidget>& Widget) const;`
- L184 _private prototype_ `void SetActiveActivationMetadata(const FActivationMetadata& NewConfig);`
- L188 _private prototype_ `FActivatableTreeRootPtr FindActiveActionDomainRootNode() const;` — Returns the top-most active root that is receiving input Action Domain's analogue to ActiveRootNode
- L190 _private prototype_ `void HandleActivatableWidgetRebuilding(UCommonActivatableWidget& RebuildingWidget);`
- L191 _private prototype_ `void ProcessRebuiltWidgets();`
- L192 _private prototype_ `void RefreshRootNodes();`
- L193 _private prototype_ `void RefreshBoundActions();`
- L194 _private prototype_ `void AssembleTreeRecursive(const FActivatableTreeNodeRef& CurNode, TMap<UCommonActivatableWidget*, TArray<UCommonActivatableWidget*>>& WidgetsByDirectParent);`
- L196 _private prototype_ `void HandleRootWidgetSlateReleased(TWeakPtr<FActivatableTreeRoot> WeakRoot);`
- L197 _private prototype_ `void HandleRootNodeActivated(TWeakPtr<FActivatableTreeRoot> WeakActivatedRoot);`
- L198 _private prototype_ `void HandleRootNodeDeactivated(TWeakPtr<FActivatableTreeRoot> WeakDeactivatedRoot);`
- L199 _private prototype_ `void HandleLeafmostActiveNodeChanged();`
- L201 _private prototype_ `void HandleSlateFocusChanging(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);`
- L203 _private prototype_ `void HandlePostGarbageCollect();`
- L204 _private prototype_ `void HandleVirtualPointerEnabled(bool bEnabled);`
- L206 _private prototype_ `const UCommonInputActionDomainTable* GetActionDomainTable() const;`
- L207 _private prototype_ `bool ProcessInputOnActionDomains(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent, int32 UserIndex) const;`
- L208 _private prototype_ `EProcessHoldActionResult ProcessHoldInputOnActionDomains(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent, int32 UserIndex) const;`
- L209 _private prototype_ `FGameplayTagContainer GetGameplayTagsForInputMode(const ECommonInputMode Mode) const;`
- L211 _private prototype_ `void DebugDumpActionDomainRootNodes(int32 UserIndex, int32 ControllerId, bool bIncludeActions, bool bIncludeChildren, bool bIncludeInactive) const;`
- L240 _private prototype_ `FPendingWidgetRegistration& GetOrCreatePendingRegistration(const UWidget& Widget);`
- L241 _private member_ `TArray<FPendingWidgetRegistration> PendingWidgetRegistrations;`
- L243 _private member_ `TArray<TWeakObjectPtr<UCommonActivatableWidget>> RebuiltWidgetsPendingNodeAssignment;`
- L244 _private member_ `TSet<TWeakPtr<FActivatableTreeRoot>> ActiveActionDomainRootsPendingPaint;`
- L246 _private member_ `TArray<FActivatableTreeRootRef> RootNodes;`
- L247 _private member_ `FActivatableTreeRootPtr ActiveRootNode;`
- L250 _private member_ `TSharedPtr<class FPersistentActionCollection> PersistentActions;` — Note: Treat this as a TSharedRef - only reason it isn't is because TSharedRef doesn't play nice with forward declarations :(
- L252 _private member_ `TCircularBuffer<FString> InputConfigSources = TCircularBuffer<FString>(5, "Non`
- L253 _private member_ `int32 InputConfigSourceIndex = 0;`
- L255 _private member_ `bool bForceResetActiveRoot = false;`
- L257 _private member_ `mutable FSimpleMulticastDelegate OnBoundActionsUpdatedEvent;`
- L258 _private member_ `mutable FOnActiveInputModeChanged OnActiveInputModeChangedEvent;`
- L259 _private member_ `mutable FOnActivationMetadataChanged OnActivationMetadataChangedEvent;`
- L260 _private member_ `mutable FOnActiveInputConfigChanged OnActiveInputConfigChangedEvent;`
- L267 _private member_ `mutable TArray<FKey> HeldKeys;`
- L299 _private member_ `TMap<TObjectPtr<UCommonInputActionDomain>, FActionDomainSortedRootList> ActionDomainRootNodes;`

#### struct `UCommonUIActionRouterBase::FPendingWidgetRegistration`  
`struct FPendingWidgetRegistration`  
_L213-239_
- L215 _public member_ `TWeakObjectPtr<const UWidget> Widget;`
- L216 _public member_ `TArray<FUIActionBindingHandle> ActionBindings;`
- L217 _public member_ `bool bIsScrollRecipient = false;`
- L227 _public member_ `TArray<FPreprocessorRegistration> Preprocessors;` — `UE_DEPRECATED(5.5, "This variable is using a deprecated type, please use InputPreProcessors instead.")`
- L230 _public member_ `TArray<FInputPreprocessorRegistration> InputPreProcessors;`
- L232 _public function_ `bool operator==(const UWidget* OtherWidget) const`
- L233 _public function_ `bool operator==(const UWidget& OtherWidget) const`
- L236 _public prototype_ `FPendingWidgetRegistration() = default;`
- L237 _public prototype_ `FPendingWidgetRegistration(const FPendingWidgetRegistration&) = default;`

#### struct `UCommonUIActionRouterBase::FPendingWidgetRegistration::FPreprocessorRegistration`  
`struct UE_DEPRECATED(5.5, "This struct is deprecated, please use FInputPreprocessorRegistration instead.") FPreprocessorRegistration`  
_L219-224_
- L221 _public member_ `TSharedPtr<IInputProcessor> Preprocessor;`
- L222 _public member_ `int32 DesiredIdx = 0;`
- L223 _public function_ `bool operator==(const TSharedRef<IInputProcessor>& OtherPreprocessor) const`

#### struct `UCommonUIActionRouterBase::FActionDomainSortedRootList`  
`struct FActionDomainSortedRootList`  
_L270-297_
- desc: A wrapper around TArray that keeps RootList sorted by PaintLayer
- L272 _public function_ `TArray<FActivatableTreeRootRef>& GetRootList()`
- L276 _public function_ `const TArray<FActivatableTreeRootRef>& GetRootList() const`
- L282 _public prototype_ `void Add(FActivatableTreeRootRef RootNode);` — Inserts RootNode into RootList based on its paint layer
- L285 _public prototype_ `int32 Remove(FActivatableTreeRootRef RootNode);` — Trivial removal
- L288 _public prototype_ `bool Contains(FActivatableTreeRootRef RootNode) const;` — Trivial Contains check
- L290 _public prototype_ `void Sort();`
- L293 _public prototype_ `void DebugDumpRootList(FString& OutputStr, bool bIncludeActions, bool bIncludeChildren, bool bIncludeInactive) const;` — Needed for debug purposes
- L296 _private member_ `TArray<FActivatableTreeRootRef> RootList;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API COMMONUI_API`
- L44 _typedef_ `using FActivatableTreeNodePtr = TSharedPtr<FActivatableTreeNode>;`
- L45 _typedef_ `using FActivatableTreeNodeRef = TSharedRef<FActivatableTreeNode>;`
- L48 _typedef_ `using FActivatableTreeRootPtr = TSharedPtr<FActivatableTreeRoot>;`
- L49 _typedef_ `using FActivatableTreeRootRef = TSharedRef<FActivatableTreeRoot>;`
- L92 _delegate_ `DECLARE_EVENT_OneParam(UCommonUIActionRouterBase, FOnActiveInputModeChanged, ECommonInputMode);`
- L97 _delegate_ `DECLARE_EVENT_OneParam(UCommonUIActionRouterBase, FOnActiveInputConfigChanged, const FUIInputConfig);`
- L100 _delegate_ `DECLARE_EVENT_OneParam(UCommonUIActionRouterBase, FOnActivationMetadataChanged, FActivationMetadata);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonUIInputSettings.h` (Public)


#### struct `FUIActionKeyMapping`  
`struct FUIActionKeyMapping`  
_L16-39_
- reflection: `USTRUCT()`
- L21 _public function_ `FUIActionKeyMapping()`
- L22 _public function_ `FUIActionKeyMapping(FKey InKey, float InHoldTime, float InHoldRollbackTime) : Key(InKey) , HoldTime(InHoldTime) , HoldRollbackTime(InHoldRollbackTime)`
- L30 _public member_ `FKey Key;` — `UPROPERTY(EditAnywhere, Config, Category = "UI Action Key Mapping")` — A key that triggers this action
- L34 _public member_ `float HoldTime = 0.f;` — `UPROPERTY(EditAnywhere, Config, Category = "UI Action Key Mapping")` — How long must the key be held down for the action to be executed?
- L38 _public member_ `float HoldRollbackTime = 0.f;` — `UPROPERTY(EditAnywhere, Config, Category = "UI Action Key Mapping")` — Time (in seconds) for hold progress to go from 1.0 (completed) to 0.0.

#### struct `FUIInputAction`  
`struct FUIInputAction`  
_L42-63_
- reflection: `USTRUCT()`
- L49 _public member_ `FUIActionTag ActionTag;` — `UPROPERTY(EditAnywhere, Config, Category = "UI Input Action")` — The UI.Action tag that acts as the universal identifier of this action.
- L56 _public member_ `FText DefaultDisplayName;` — `UPROPERTY(EditAnywhere, Config, Category = "UI Input Action")` — Whenever a UI input action is bound, an override display name can optionally be provided. This is the default generic display name of this action for use in the absence of such an override.
- L60 _public member_ `TArray<FUIActionKeyMapping> KeyMappings;` — `UPROPERTY(EditAnywhere, Config, Category = "UI Input Action", meta = (TitleProperty = "Key"))` — All key mappings that will trigger this action
- L62 _public prototype_ `bool HasAnyHoldMappings() const;`

#### struct `FCommonAnalogCursorSettings`  
`struct FCommonAnalogCursorSettings`  
_L66-111_
- reflection: `USTRUCT()`
- L74 _public member_ `int32 PreprocessorPriority = 2;` — `UE_DEPRECATED(5.5, "PreprocessorPriority is deprecated, please use PreprocessorRegistrationInfo from now on.")` — `UPROPERTY(EditAnywhere, Config, Category = General)` — The registration priority of the analog cursor preprocessor.
- L80 _public member_ `bool bEnableCursorAcceleration = true;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor)`
- L83 _public member_ `float CursorAcceleration = 1500.f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor, meta = (EditCondition = bEnableCursorAcceleration))`
- L86 _public member_ `float CursorMaxSpeed = 2200.f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor)`
- L89 _public member_ `float CursorDeadZone = 0.25f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor, meta = (ClampMin = "0.0", ClampMax = "0.9"))`
- L92 _public member_ `float HoverSlowdownFactor = 0.4f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor, meta = (ClampMin = "0.0", ClampMax = "1.0"))`
- L95 _public member_ `float ScrollDeadZone = 0.2f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor, meta = (ClampMin = "0.0", ClampMax = "0.9"))`
- L98 _public member_ `float ScrollUpdatePeriod = 0.1f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor)`
- L101 _public member_ `float ScrollMultiplier = 2.5f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor)`
- L105 _public member_ `float MaxHoldDuration = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = AnalogCursor)` — Duration in seconds for hold progress to go from 0.0 to 1.0 while the accept button is held.
- L107 _public function_ `FCommonAnalogCursorSettings()`
- L109 _public prototype_ `FCommonAnalogCursorSettings& operator=(const FCommonAnalogCursorSettings&) = default;`

#### class `UCommonUIInputSettings`  
`class UCommonUIInputSettings : public UObject`  
_L115-163_
- reflection: `UCLASS(config=Input, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- desc: Project-wide input settings for UI input actions
- L120 _public prototype_ `static const UCommonUIInputSettings& Get();`
- L122 _public prototype_ `virtual void PostInitProperties() override;`
- L124 _public function_ `int32 GetUIActionProcessingPriority() const`
- L125 _public prototype_ `const FUIInputAction* FindAction(FUIActionTag ActionTag) const;`
- L126 _public function_ `const TArray<FUIInputAction>& GetUIInputActions() const`
- L127 _public function_ `const FCommonAnalogCursorSettings& GetAnalogCursorSettings() const`
- L128 _public function_ `const TSoftClassPtr<UUserWidget>& GetDefaultVirtualPointerClass() const`
- L129 _public function_ `bool ShouldLinkCursorToGamepadFocus() const`
- L134 _private member_ `bool bLinkCursorToGamepadFocus = true;` — `UPROPERTY(EditAnywhere, Config, Category = General)` — True to have the mouse pointer automatically moved to the center of whatever widget is currently focused while using a gamepad.
- L147 _private member_ `int32 UIActionProcessingPriority = 10000;` — `UPROPERTY(EditAnywhere, Config, Category = General)` — The input priority of the input components that process UI input actions. The lower the value, the higher the priority of the component. By default, this value is incredibly high to ensure UI action processing priority over game elements. Adjust as needed for the UI input components to be processed at the appropriate point in the input stack in your project. NOTE: When the active input mode is ECommonInputMode::Menu, ALL input components with lower priority than this will be fully blocked. Thus, if any game agent input components are registered with higher priority than this, behavior will not match expectation.
- L151 _private member_ `TArray<FUIInputAction> InputActions;` — `UPROPERTY(EditAnywhere, Config, Category = Actions, meta = (TitleProperty = "ActionTag"))` — All UI input action mappings for the project
- L155 _private member_ `TArray<FUIInputAction> ActionOverrides;` — `UPROPERTY(Config)` — Config-only set of input action overrides - if an entry for a given action is both here and in the InputActions array, this entry wins completely.
- L158 _private member_ `FCommonAnalogCursorSettings AnalogCursorSettings;` — `UPROPERTY(EditAnywhere, Config, Category = AnalogCursor)`
- L162 _private member_ `TSoftClassPtr<UUserWidget> DefaultVirtualPointerClass;` — `UPROPERTY(EditAnywhere, Config, Category = AnalogCursor)` — Widget class used as the software cursor when the virtual pointer is active. Stored here so the cooker tracks it as a dependency. Default is set in the plugin's Config/Input.ini.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonUIInputTypes.h` (Public)


#### struct `FBindUIActionArgs`  
`struct FBindUIActionArgs`  
_L14-112_
- L16 _public function_ `FBindUIActionArgs(FUIActionTag InActionTag, const FSimpleDelegate& InOnExecuteAction) : ActionTag(InActionTag) , OnExecuteAction(InOnExecuteAction)`
- L21 _public function_ `FBindUIActionArgs(FUIActionTag InActionTag, bool bShouldDisplayInActionBar, const FSimpleDelegate& InOnExecuteAction) : ActionTag(InActionTag) , bDisplayInActionBar(bShouldDisplayInActionBar) , OnExecuteAction(InOnExecuteAction)`
- L28 _public function_ `FBindUIActionArgs(const FDataTableRowHandle& InLegacyActionTableRow, const FSimpleDelegate& InOnExecuteAction) : LegacyActionTableRow(InLegacyActionTableRow) , OnExecuteAction(InOnExecuteAction)` — @TODO: Rename non-legacy in 5.3. We no longer have any active plans to remove data tables in CommonUI.
- L34 _public function_ `FBindUIActionArgs(const FDataTableRowHandle& InLegacyActionTableRow, bool bShouldDisplayInActionBar, const FSimpleDelegate& InOnExecuteAction) : LegacyActionTableRow(InLegacyActionTableRow) , bDisplayInActionBar(bShouldDisplayInActionBar) , OnExecuteAction(InOnExecuteAction)` — @TODO: Rename non-legacy in 5.3. We no longer have any active plans to remove data tables in CommonUI.
- L40 _public function_ `FBindUIActionArgs(const UInputAction* InInputAction, const FSimpleDelegate & InOnExecuteAction) : InputAction(InInputAction) , OnExecuteAction(InOnExecuteAction)`
- L45 _public function_ `FBindUIActionArgs(const UInputAction* InInputAction, bool bShouldDisplayInActionBar, const FSimpleDelegate & InOnExecuteAction) : InputAction(InInputAction) , bDisplayInActionBar(bShouldDisplayInActionBar) , OnExecuteAction(InOnExecuteAction)`
- L51 _public prototype_ `FName GetActionName() const;`
- L53 _public prototype_ `bool ActionHasHoldMappings() const;`
- L55 _public member_ `FUIActionTag ActionTag;`
- L58 _public member_ `FDataTableRowHandle LegacyActionTableRow;` — @TODO: Rename non-legacy in 5.3. We no longer have any active plans to remove data tables in CommonUI.
- L60 _public member_ `TWeakObjectPtr<const UInputAction> InputAction;`
- L62 _public member_ `ECommonInputMode InputMode = ECommonInputMode::Menu;`
- L63 _public member_ `EInputEvent KeyEvent = IE_Pressed;`
- L69 _public member_ `TSet<ECommonInputType> InputTypesExemptFromValidKeyCheck = { ECommonInputType::MouseAndKeyboard, ECommonInputType::Touch };` — By default, the action bar only displays prompts for actions with keys valid for the current input type, any input types added here will skip that check and display this action regardless of the bound keys
- L75 _public member_ `bool bIsPersistent = false;` — A persistent binding is always registered and will be executed regardless of the activation status of the binding widget's parentage. Persistent bindings also never stomp one another - if two are bound to the same action, both will execute. Use should be kept to a minimum.
- L82 _public member_ `bool bConsumeInput = true;` — True to have this binding consume the triggering key input. Persistent bindings that consume will prevent the key reaching non-persistent bindings and game agents. Non-persistent bindings that consume will prevent the key reaching game agents.
- L85 _public member_ `bool bDisplayInActionBar = true;` — Whether this binding can/should be displayed in a CommonActionBar (if one exists)
- L88 _public member_ `bool bForceHold = false;` — True implies we will add default hold times if the current action is not a hold action
- L91 _public member_ `FText OverrideDisplayName;` — Optional display name to associate with this binding instead of the default
- L97 _public member_ `int32 PriorityWithinCollection = 0;` — Normally, actions on a widget are triggered in the order they're registered. We can assign a priority to ensure a certain order of execution. 0 is the order of registration.
- L99 _public member_ `FSimpleDelegate OnExecuteAction;`
- L102 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnHoldActionProgressed, float);` — If the bound action has any hold mappings, this will fire each frame while held. Has no bearing on actual execution and wholly irrelevant for non-hold actions
- L103 _public member_ `FOnHoldActionProgressed OnHoldActionProgressed;`
- L106 _public prototype_ `DECLARE_DELEGATE(FOnHoldActionPressed);` — If the bound action has any hold mappings, this will fire when the hold begins. Has no bearing on actual execution and wholly irrelevant for non-hold actions
- L107 _public member_ `FOnHoldActionPressed OnHoldActionPressed;`
- L110 _public prototype_ `DECLARE_DELEGATE(FOnHoldActionReleased);` — If the bound action has any hold mappings, this will fire when the hold is interrupted. Has no bearing on actual execution and wholly irrelevant for non-hold actions
- L111 _public member_ `FOnHoldActionReleased OnHoldActionReleased;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONUI_API`
- L102 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHoldActionProgressed, float);` — If the bound action has any hold mappings, this will fire each frame while held. Has no bearing on actual execution and wholly irrelevant for non-hold actions
- L106 _delegate_ `DECLARE_DELEGATE(FOnHoldActionPressed);` — If the bound action has any hold mappings, this will fire when the hold begins. Has no bearing on actual execution and wholly irrelevant for non-hold actions
- L110 _delegate_ `DECLARE_DELEGATE(FOnHoldActionReleased);` — If the bound action has any hold mappings, this will fire when the hold is interrupted. Has no bearing on actual execution and wholly irrelevant for non-hold actions

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/UIActionBinding.h` (Public)


#### enum `EProcessHoldActionResult`  
`enum class EProcessHoldActionResult`  
_L22-27_
- L24 _public enumerator_ `Handled`
- L25 _public enumerator_ `GeneratePress`
- L26 _public enumerator_ `Unhandled`

#### struct `FUIActionBinding`  
`struct FUIActionBinding`  
_L29-124_
- L31 _public prototype_ `FUIActionBinding() = delete;`
- L32 _public prototype_ `FUIActionBinding(const FUIActionBinding&) = delete;`
- L33 _public prototype_ `FUIActionBinding(FUIActionBinding&&) = delete;`
- L36 _public prototype_ `static FUIActionBindingHandle TryCreate(const UWidget& InBoundWidget, const FBindUIActionArgs& BindArgs);` — `UE_DEPRECATED(5.6, "Calling FUIActionBinding::TryCreate without a user index is deprecated. Call the version with the UserIndex param.")`
- L37 _public prototype_ `static FUIActionBindingHandle TryCreate(const UWidget& InBoundWidget, const FBindUIActionArgs& BindArgs, int32 UserIndex);`
- L39 _public prototype_ `static TSharedPtr<FUIActionBinding> FindBinding(FUIActionBindingHandle Handle);`
- L40 _public prototype_ `static void CleanRegistrations();`
- L42 _public function_ `bool operator==(const FUIActionBindingHandle& OtherHandle) const`
- L45 _public prototype_ `FCommonInputActionDataBase* GetLegacyInputActionData() const;` — @TODO: Rename non-legacy in 5.3. We no longer have any active plans to remove data tables in CommonUI.
- L47 _public prototype_ `EProcessHoldActionResult ProcessHoldInput(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent);`
- L48 _public prototype_ `bool ProcessNormalInput(ECommonInputMode ActiveInputMode, FKey Key, EInputEvent InputEvent);`
- L49 _public prototype_ `FString ToDebugString() const;`
- L51 _public prototype_ `void BeginHold();`
- L52 _public prototype_ `bool UpdateHold(float TargetHoldTime);`
- L53 _public prototype_ `void CancelHold();`
- L54 _public prototype_ `void BeginRollback(float TargetHoldRollbackTime, float HoldTime, FUIActionBindingHandle BindingHandle);`
- L55 _public prototype_ `double GetSecondsHeld() const;`
- L56 _public prototype_ `bool IsHoldActive() const;`
- L57 _public prototype_ `void ResetHold();`
- L59 _public member_ `FName ActionName;`
- L60 _public member_ `EInputEvent InputEvent;`
- L61 _public member_ `bool bConsumesInput = true;`
- L62 _public member_ `bool bIsPersistent = false;`
- L64 _public member_ `int32 PriorityWithinCollection = 0;`
- L66 _public member_ `TWeakObjectPtr<const UWidget> BoundWidget;`
- L67 _public member_ `ECommonInputMode InputMode;`
- L69 _public member_ `int32 UserIndex = INDEX_NONE;`
- L71 _public member_ `bool bDisplayInActionBar = false;`
- L72 _public member_ `TSet<ECommonInputType> InputTypesExemptFromValidKeyCheck;`
- L73 _public member_ `FText ActionDisplayName;`
- L75 _public member_ `TWeakPtr<FActionRouterBindingCollection> OwningCollection;`
- L76 _public member_ `FSimpleDelegate OnExecuteAction;`
- L77 _public member_ `FUIActionBindingHandle Handle;`
- L79 _public member_ `TArray<FUIActionKeyMapping> NormalMappings;`
- L80 _public member_ `TArray<FUIActionKeyMapping> HoldMappings;`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHoldActionProgressedMulticast, float);`
- L83 _public member_ `FOnHoldActionProgressedMulticast OnHoldActionProgressed;`
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnHoldActionPressed);`
- L86 _public member_ `FOnHoldActionPressed OnHoldActionPressed;`
- L88 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnHoldActionReleased);`
- L89 _public member_ `FOnHoldActionPressed OnHoldActionReleased;`
- L92 _public member_ `FDataTableRowHandle LegacyActionTableRow;` — @TODO: Rename non-legacy in 5.3. We no longer have any active plans to remove data tables in CommonUI.
- L94 _public member_ `TWeakObjectPtr<const UInputAction> InputAction;`
- L97 _private prototype_ `FUIActionBinding(const UWidget& InBoundWidget, const FBindUIActionArgs& BindArgs);`
- L100 _private member_ `double HoldStartTime = -1.0;` — At what time in seconds did the hold start?
- L103 _private member_ `double HoldStartSecond = 0.0;` — At what second will the hold start?
- L106 _private member_ `double CurrentHoldSecond = 0.0;` — At what second is the hold progress at?
- L109 _private member_ `double HoldRollbackMultiplier = 1.0;` — Multiplier for the time (in seconds) for hold progress to go from 1.0 (completed) to 0.0.
- L112 _private member_ `double HoldTime = 0.0;` — Target time (in seconds) for the hold progress to go from 0.0 to 1.0 (completed).
- L115 _private member_ `FTSTicker::FDelegateHandle HoldProgressRollbackTickerHandle;` — Handle for ticker spawned for button hold rollback
- L117 _private member_ `static int32 IdCounter;`
- L118 _private member_ `static TMap<FUIActionBindingHandle, TSharedPtr<FUIActionBinding>> AllRegistrationsByHandle;`
- L121 _private member_ `static TMap<FKey, FUIActionBindingHandle> CurrentHoldActionKeys;` — All keys currently being tracked for a hold action

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHoldActionProgressedMulticast, float);`
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnHoldActionPressed);`
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnHoldActionReleased);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/UIActionBindingHandle.h` (Public)


#### struct `FUIActionBindingHandle`  
`struct FUIActionBindingHandle`  
_L19-68_
- reflection: `USTRUCT(BlueprintType, DisplayName = "UI Action Binding Handle")`
- L24 _public prototype_ `bool IsValid() const;`
- L25 _public prototype_ `void Unregister();`
- L28 _public prototype_ `void ResetHold();` — Calls ResetHold() on the Action Binding, which in turn resets the hold progress to 0.0
- L30 _public prototype_ `FName GetActionName() const;`
- L32 _public prototype_ `FText GetDisplayName() const;`
- L35 _public prototype_ `void SetDisplayName(const FText& DisplayName);` — Should not be called often as broadcasts UCommonUIActionRouterBase::OnBoundActionsUpdated event
- L37 _public prototype_ `bool GetDisplayInActionBar() const;`
- L40 _public prototype_ `void SetDisplayInActionBar(const bool bDisplayInActionBar);` — Should not be called often as broadcasts UCommonUIActionRouterBase::OnBoundActionsUpdated event
- L42 _public prototype_ `const UWidget* GetBoundWidget() const;`
- L44 _public prototype_ `ULocalPlayer* GetBoundLocalPlayer() const;`
- L46 _public function_ `FUIActionBindingHandle()`
- L47 _public function_ `bool operator==(const FUIActionBindingHandle& Other) const`
- L48 _public function_ `bool operator!=(const FUIActionBindingHandle& Other) const`
- L60 _private member_ `FString CachedDebugActionName;` — Using FString since the FName visualizer gets confused after live coding atm
- L63 _private function_ `FUIActionBindingHandle(int32 InRegistrationId) : RegistrationId(InRegistrationId)`
- L67 _private member_ `int32 RegistrationId = INDEX_NONE;`

#### struct `FActivationMetadata`  
`struct FActivationMetadata`  
_L78-87_
- desc: Metadata that can be set on activatable widgets via GetActivationMetadata & listened to via OnActivationMetadataChanged. Useful for game-specific behaviors to be triggered by activation of certain widgets generically. For example changing camera config of your game when certain widgets activate. By default only has an enum for this metadata.
- L80 _public function_ `FActivationMetadata()`
- L81 _public function_ `FActivationMetadata(uint8 InMetadataEnum) : MetadataEnum(InMetadataEnum)`
- L83 _public function_ `TOptional<uint8> GetMetadataEnum() const`
- L86 _private member_ `TOptional<uint8> MetadataEnum;`

#### struct `FUIInputConfig`  
`struct FUIInputConfig`  
_L94-146_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input Config that can be applied on widget activation. Allows for input setup  (Mouse capture, UI-only input, move / look ignore, etc), to be controlled by widget activation.
- L98 _public function_ `ECommonInputMode GetInputMode() const`
- L99 _public function_ `EMouseCaptureMode GetMouseCaptureMode() const`
- L100 _public function_ `EMouseLockMode GetMouseLockMode() const`
- L101 _public function_ `bool HideCursorDuringViewportCapture() const`
- L103 _public prototype_ `FUIInputConfig();`
- L104 _public prototype_ `FUIInputConfig(ECommonInputMode InInputMode, EMouseCaptureMode InMouseCaptureMode, bool bInHideCursorDuringViewportCapture = true);`
- L105 _public prototype_ `FUIInputConfig(ECommonInputMode InInputMode, EMouseCaptureMode InMouseCaptureMode, EMouseLockMode InMouseLockMode, bool bInHideCursorDuringViewportCapture = true);`
- L107 _public function_ `bool operator==(const FUIInputConfig& Other) const`
- L117 _public function_ `bool operator!=(const FUIInputConfig& Other) const`
- L123 _public member_ `bool bIgnoreMoveInput = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)`
- L126 _public member_ `bool bIgnoreLookInput = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)`
- L129 _public prototype_ `FString ToString() const;` — Simplification of config as string
- L135 _protected member_ `ECommonInputMode InputMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)`
- L138 _protected member_ `EMouseCaptureMode MouseCaptureMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)`
- L142 _protected member_ `EMouseLockMode MouseLockMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)`
- L145 _protected member_ `bool bHideCursorDuringViewportCapture = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`
- L50 _function_ `friend uint32 GetTypeHash(const FUIActionBindingHandle& Handle)`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Misc/Passkey.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define DEFINE_PASSKEY(FriendClass, PropertyType, PropertyName) \` — A Passkey is an object that allows friend-esque access to a single function by allowing only the pseudo-friend to construct the passkey. In practice, the caller doesn't have to care, as passkey will be created implicitly from the property you're actually interested in. Not intended to be used widely or with great regularity. Prefer proper encapsulation methods, and only use this as a last resort, as using it does undeniably make the code more cryptic to others.

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/SAnalogSlider.h` (Public)


#### class `SAnalogSlider`  
`class SAnalogSlider : public SSlider`  
_L14-104_
- inherits: `SSlider`
- desc: A Slate slider control is a linear scale and draggable handle.
- L18 _public function_ `SLATE_BEGIN_ARGS(SAnalogSlider) : _IndentHandle(true) , _Locked(false) , _Orientation(EOrientation::Orient_Horizontal) , _SliderBarColor(FLinearColor::White) , _SliderHandleColor(FLinearColor::White) , _Style(&FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider")) , _StepSize(0.01f) , _Value(1.f) , _IsFocusable(true) , _OnMouseCaptureBegin() , _OnMouseCaptureEnd() , _OnValueChanged() , _OnAnalogCapture()`
- L35 _public prototype_ `SLATE_ATTRIBUTE(bool, IndentHandle) SLATE_ATTRIBUTE(bool, Locked) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, SliderHandleColor) SLATE_STYLE_ARGUMENT(FSliderStyle, Style) SLATE_ATTRIBUTE(float, StepSize) SLATE_ATTRIBUTE(float, Value) SLATE_ARGUMENT(bool, IsFocusable) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_EVENT(FSimpleDelegate, OnControllerCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnControllerCaptureEnd) SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)` — Whether the slidable area should be indented to fit the handle.
- L89 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Input overrides, for adding controller input to the slider
- L90 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L91 _public prototype_ `virtual FReply OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L92 _public prototype_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;`
- L94 _public prototype_ `void SetUsingGamepad(bool InUsingGamepad);`
- L98 _private member_ `FOnFloatValueChanged OnAnalogCapture;` — Holds a delegate that is executed when the mouse is let up and a capture ends.
- L100 _private member_ `bool bIsUsingGamepad = false;`
- L103 _private member_ `double LastAnalogStepTime = 0;` — The last app time we stepped with analog input

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/SCommonButtonTableRow.h` (Public)


#### class `SCommonButtonTableRow`  
`template <typename ItemType> class SCommonButtonTableRow : public SObjectTableRow<ItemType>`  
_L15-234_
- inherits: `SObjectTableRow<ItemType>`
- desc: A CommonUI version of the object table row that is aware of UCommonButtonBase. Instead of bothering with handling mouse events directly, we rely on the entry being a button itself and respond to events from it.
- L18 _public function_ `SLATE_BEGIN_ARGS(SCommonButtonTableRow<ItemType>) :_bAllowDragging(true), _bAllowKeepPreselectedItems(true)`
- L39 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, UUserWidget& InChildWidget, UListViewBase* InOwnerListView)`
- L73 _public function_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override` — We rely on the button to handle all of these things for us
- L74 _public function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override`
- L75 _public function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L76 _public function_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L77 _public function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L80 _protected function_ `virtual void InitializeObjectRow() override`
- L117 _protected function_ `virtual void ResetObjectRow() override`
- L143 _protected function_ `virtual void DetectItemSelectionChanged() override`
- L161 _protected function_ `virtual void OnItemSelectionChanged(bool bIsItemSelected) override`
- L175 _private function_ `void HandleButtonClicked()`
- L185 _private function_ `void HandleButtonDoubleClicked()`
- L198 _private function_ `void HandleButtonHovered()`
- L203 _private function_ `void HandleButtonUnhovered()`
- L208 _private function_ `void HandleButtonSelectionChanged(bool bIsButtonSelected)`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/SCommonHierarchicalScrollBox.h` (Public)


#### class `SCommonHierarchicalScrollBox`  
`class SCommonHierarchicalScrollBox : public SScrollBox`  
_L8-21_
- inherits: `SScrollBox`
- desc: SScrollBox can scroll through an arbitrary number of widgets.
- L16 _public prototype_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;` — SWidget interface This is a near copy of SScrollBox::OnNavigation. Ideally AppendFocusableChildren would be a virtual function in SScrollbox, but I don't have enough time to test functional changes to a core slate widget at the time of this writing. It was safer to isolate it. to this widget where I can test every case where it is used.
- L20 _private prototype_ `void AppendFocusableChildren(TArray<TSharedRef<SWidget>>& OutChildren, TSharedRef<SWidget> Owner);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/SCommonTileView.h` (Public)


#### class `SCommonTileView`  
`template <typename ItemType> class SCommonTileView : public STileView<ItemType>`  
_L12-466_
- inherits: `STileView<ItemType>`
- L15 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L96 _public function_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override`
- L191 _public function_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override`
- L397 _public function_ `virtual void NotifyItemScrolledIntoView() override`
- L423 _public function_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override`
- L432 _public function_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override`
- L444 _public function_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L461 _protected member_ `TWeakPtr<SWidget> IntraEntrySourceWidget;` — Last sub-widget that held focus within an entry. Written by OnFocusChanging; consumed by OnNavigation intra-entry navigation and the cross-list source precision correction.
- L464 _private member_ `bool bScrollToSelectedOnFocus = true;`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/SVisualAttachmentBox.h` (Public)


#### class `SVisualAttachmentBox`  
`class SVisualAttachmentBox : public SBox`  
_L12-27_
- inherits: `SBox`
- desc: Wrapper widget meant to handle native-side painting for UCommonVisualAttachment.
- L15 _public prototype_ `void Construct(const FArguments& InArgs);`
- L17 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L18 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L19 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L21 _public prototype_ `void SetContentAnchor(FVector2D InContentAnchor);`
- L24 _private member_ `mutable FVector2D InnerDesiredSize;`
- L26 _private member_ `FVector2D ContentAnchor = FVector2D::ZeroVector;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMMONUI_API`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Slate/SCommonAnimatedSwitcher.h` (Public)


#### enum `ECommonSwitcherTransition`  
`enum class ECommonSwitcherTransition : uint8`  
_L13-23_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `FadeOnly` — Fade transition only with no movement
- L18 _public enumerator_ `Horizontal` — Increasing the active index goes right, decreasing goes left
- L20 _public enumerator_ `Vertical` — Increasing the active index goes up, decreasing goes down
- L22 _public enumerator_ `Zoom` — Increasing the active index zooms in, decreasing zooms out

#### enum `ETransitionCurve`  
`enum class ETransitionCurve : uint8`  
_L26-42_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Linear` — Linear interpolation, with no easing
- L31 _public enumerator_ `QuadIn` — Quadratic ease in
- L33 _public enumerator_ `QuadOut` — Quadratic ease out
- L35 _public enumerator_ `QuadInOut` — Quadratic ease in, quadratic ease out
- L37 _public enumerator_ `CubicIn` — Cubic ease in
- L39 _public enumerator_ `CubicOut` — Cubic ease out
- L41 _public enumerator_ `CubicInOut` — Cubic ease in, cubic ease out

#### enum `ECommonSwitcherTransitionFallbackStrategy`  
`enum class ECommonSwitcherTransitionFallbackStrategy : uint8`  
_L46-58_
- reflection: `UENUM(BlueprintType)`
- desc: Determines the switcher's behavior if the target of a transition is removed before it becomes the active widget.
- L49 _public enumerator_ `None` — Transition fallbacks are disabled and no special handling will occur if a transitioning widget is removed.
- L51 _public enumerator_ `Previous` — Fall back to the nearest valid slot at a lower index than the original target, or the first slot if there are none lower
- L53 _public enumerator_ `Next` — Fall back to the nearest valid slot at a higher index than the original target, or the last slot if there are none higher
- L55 _public enumerator_ `First` — Fall back to the first item in the switcher
- L57 _public enumerator_ `Last` — Fall back to the last item in the switcher

#### class `SCommonAnimatedSwitcher`  
`class SCommonAnimatedSwitcher : public SWidgetSwitcher`  
_L75-155_
- inherits: `SWidgetSwitcher`
- L78 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnActiveIndexChanged, int32);`
- L79 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnIsTransitioningChanged, bool);`
- L81 _public function_ `SLATE_BEGIN_ARGS(SCommonAnimatedSwitcher) : _InitialIndex(0) , _TransitionType(ECommonSwitcherTransition::FadeOnly) , _TransitionCurveType(ETransitionCurve::CubicInOut) , _TransitionDuration(0.4f) , _TransitionFallbackStrategy(ECommonSwitcherTransitionFallbackStrategy::Previous)`
- L103 _public prototype_ `void Construct(const FArguments& InArgs);`
- L105 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L106 _public prototype_ `void TransitionToIndex(int32 NewWidgetIndex, bool bInstantTransition = false);`
- L108 _public prototype_ `FSlot* GetChildSlot(int32 SlotIndex);`
- L110 _public prototype_ `void SetTransition(float Duration, ETransitionCurve Curve);`
- L111 _public prototype_ `void SetTransition(float Duration, ETransitionCurve Curve, ECommonSwitcherTransition NewTransitionType);`
- L112 _public prototype_ `void SetTransitionType(ECommonSwitcherTransition NewTransitionType);`
- L114 _public prototype_ `bool IsTransitionPlaying() const;`
- L116 _public function_ `TWeakPtr<SWidget> GetPendingActiveWidget() const`
- L117 _public function_ `int32 GetPendingActiveWidgetIndex() const`
- L119 _public function_ `void SetTransitionFallbackStrategy(const ECommonSwitcherTransitionFallbackStrategy InStrategy)`
- L120 _public function_ `ECommonSwitcherTransitionFallbackStrategy GetTransitionFallbackStrategy() const`
- L121 _public function_ `bool IsTransitionFallbackEnabled() const`
- L124 _protected prototype_ `virtual void OnSlotAdded(int32 AddedIndex) override;`
- L125 _protected prototype_ `virtual void OnSlotRemoved(int32 RemovedIndex, TSharedRef<SWidget> RemovedWidget, bool bWasActiveSlot) override;`
- L128 _private prototype_ `EActiveTimerReturnType UpdateTransition(double InCurrentTime, float InDeltaTime);`
- L129 _private prototype_ `float GetTransitionProgress() const;`
- L130 _private prototype_ `int32 GetTransitionFallbackForIndex(int32 RemovedWidgetIndex) const;`
- L131 _private prototype_ `bool TryTransitionFallbackOfPendingWidget();`
- L132 _private prototype_ `bool TryTransitionFallbackOfActiveWidget(int32 RemovedWidgetIndex);`
- L136 _private member_ `FCurveSequence TransitionSequence;` — Anim sequence for the transition; plays twice per transition
- L139 _private member_ `TWeakPtr<SWidget> PendingActiveWidget;` — The pending active widget, set when the initial transition out completes. If set to a null value then we don't have any pending widget
- L142 _private member_ `int32 PendingActiveWidgetIndex = INDEX_NONE;` — Tracks the index of PendingActiveWidget, if there is one.
- L145 _private member_ `ECommonSwitcherTransitionFallbackStrategy TransitionFallbackStrategy = ECommonSwitcherTransitionFallbackStrategy::None;` — Controls how we will choose another widget if a transitioning widget is removed during the transition.
- L148 _private member_ `bool bTransitioningOut = false;` — If true, we are transitioning content out and need to play the sequence again to transition it in
- L150 _private member_ `bool bIsTransitionTimerRegistered = false;`
- L151 _private member_ `ECommonSwitcherTransition TransitionType;`
- L153 _private member_ `FOnActiveIndexChanged OnActiveIndexChanged;`
- L154 _private member_ `FOnIsTransitioningChanged OnIsTransitioningChanged;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L60 _function_ `static inline ECurveEaseFunction TransitionCurveToCurveEaseFunction(ETransitionCurve CurveType)`
- L78 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActiveIndexChanged, int32);`
- L79 _delegate_ `DECLARE_DELEGATE_OneParam(FOnIsTransitioningChanged, bool);`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/UITag.h` (Public)


#### class `TTypedTagStaticImpl`  
`template <typename TagT> class TTypedTagStaticImpl`  
_L17-91_
- desc: Implementation utility for typed subclasses of FGameplayTag. Implemented here instead of directly within the macro to make debugging possible.
- L21 _private function_ `static TagT AddNativeTag(const FString& TagBody)`
- L48 _private function_ `static inline TagT FindFromString_DebugOnly(const FString& PartialTagName)` — Intended for console commands/cheats: not for shipping code!
- L54 _private function_ `static bool ExportTextItem(const TagT& Tag, FString& ValueStr, int32 PortFlags)`
- L60 _private function_ `static TagT TryConvert(FGameplayTag VanillaTag, bool bChecked)`
- L73 _private function_ `TTypedTagStaticImpl()`
- L83 _private function_ `~TTypedTagStaticImpl()`
- L88 _private member_ `TagT RootTag;`
- L89 _private member_ `static TTypedTagStaticImpl StaticImpl;`
- L90 _private member_ `FDelegateHandle OnLastChanceToAddNativeTagsHandle;`

#### struct `FUITag`  
`struct FUITag : public FGameplayTag`  
_L128-132_
- reflection: `USTRUCT(meta = (Categories = "UI"))`
- inherits: `FGameplayTag`

#### struct `FUIActionTag`  
`struct FUIActionTag : public FUITag`  
_L135-139_
- reflection: `USTRUCT(meta = (Categories = "UI.Action"))`
- inherits: `FUITag`

#### struct `FGlobalUITags`  
`struct FGlobalUITags : public FGameplayTagNativeAdder`  
_L156-177_
- inherits: `FGameplayTagNativeAdder`
- L158 _public member_ `FUIActionTag UIAction_Cancel;`
- L159 _public member_ `FUIActionTag UIAction_PreviousTab;`
- L160 _public member_ `FUIActionTag UIAction_NextTab;`
- L161 _public member_ `FUIActionTag UIAction_Confirm;`
- L163 _public function_ `void AddTags()`
- L173 _public function_ `inline static const FGlobalUITags& Get()`
- L176 _private member_ `static FGlobalUITags GUITags;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONUI_API`
- L78 _function_ `` (scope `TTypedTagStaticImpl::TTypedTagStaticImpl`)
- L94 _member_ `template <typename TagT> TTypedTagStaticImpl<TagT> TTypedTagStaticImpl<TagT>::StaticImpl;` (scope `TTypedTagStaticImpl<TagT>`)
- L97 _macro_ `#define END_UI_TAG_DECL(TagType, TagRoot) \` — Intended to be the absolute last thing in the definition of a UI tag

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/WidgetFactory.h` (Public)


#### class `TWidgetFactory`  
`template <class WidgetType> class TWidgetFactory : public FGCObject`  
_L14-282_
- inherits: `FGCObject`
- L18 _private function_ `inline UGameInstance* OwningObjectAsGameInstance() const`
- L19 _private function_ `inline UWorld* OwningObjectAsWorld() const`
- L20 _private function_ `inline APlayerController* OwningObjectAsPlayerController() const`
- L23 _public typedef_ `typedef TFunctionRef<TSharedPtr<SObjectWidget>(UUserWidget*, TSharedRef<SWidget>)> ConstructMethodType;`
- L25 _public prototype_ `TWidgetFactory() = default;`
- L26 _public function_ `TWidgetFactory(UWidget& InOwningWidget, TSubclassOf<WidgetType> InWidgetClass, TFunction<UObject*(void)>&& InOuterGetter, bool InTrackActiveWidgets = false) : OwningWidget(&InOwningWidget) , WidgetClass(InWidgetClass) , OuterGetter(MoveTemp(InOuterGetter)) , bTrackActiveWidgets(InTrackActiveWidgets)`
- L35 _public function_ `TWidgetFactory(TWidgetFactory&& Other) : ActiveWidgets(MoveTemp(Other.ActiveWidgets)) , InactiveWidgets(MoveTemp(Other.InactiveWidgets)) , CachedSlateWidgets(MoveTemp(Other.CachedSlateWidgets)) , OwningWidget(Other.OwningWidget) , WidgetClass(Other.WidgetClass) , OuterGetter(MoveTemp(Other.OuterGetter))`
- L51 _public function_ `virtual ~TWidgetFactory()`
- L58 _public function_ `TWidgetFactory& operator=(TWidgetFactory&& Other)`
- L79 _public function_ `bool IsInitialized() const`
- L84 _public function_ `const TArray<WidgetType*>& GetActiveWidgets() const`
- L86 _public function_ `void PreConstruct(int32 Num)`
- L122 _public function_ `WidgetType* Acquire()` — Method to get a widget from this factory, can sometimes call CreateWidget
- L172 _public function_ `void Release(WidgetType* Widget)` — Return a widget to the pool, allowing it to be reused in the future
- L194 _public function_ `void Reset(const bool bReleaseSlate = false, const bool bMoveToInactive = false)`
- L227 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector) override`
- L235 _public function_ `virtual FString GetReferencerName() const override`
- L242 _public function_ `TSharedRef<DerivedWidgetType> TakeAndCacheWidget(WidgetType* Key, ConstructMethodType ConstructMethod)`
- L256 _public function_ `TSharedRef<DerivedWidgetType> TakeAndCacheRow(WidgetType* Key, const TSharedRef<STableViewBase>& DestinationTable)`
- L275 _private member_ `TArray<TObjectPtr<WidgetType>> ActiveWidgets;`
- L276 _private member_ `TArray<TObjectPtr<WidgetType>> InactiveWidgets;`
- L277 _private member_ `TMap<WidgetType*, TSharedPtr<SWidget>> CachedSlateWidgets;`
- L278 _private member_ `TWeakObjectPtr<UWidget> OwningWidget;`
- L279 _private member_ `TSubclassOf<WidgetType> WidgetClass;`
- L280 _private member_ `TFunction<UObject*(void)> OuterGetter;`
- L281 _private member_ `bool bTrackActiveWidgets;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define ENABLE_WIDGET_FACTORY_POOLING 1`
- L263 _function_ `` (scope `TWidgetFactory::TakeAndCacheRow`)
- L284 _typedef_ `using FUserWidgetFactory = TWidgetFactory<UUserWidget>;`

### `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h` (Public)


#### class `UCommonActivatableWidgetContainerBase`  
`class UCommonActivatableWidgetContainerBase : public UWidget`  
_L24-188_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UWidget`
- desc: Base of widgets built to manage N activatable widgets, displaying one at a time. Intentionally meant to be black boxes that do not expose child/slot modification like a normal panel widget.
- L29 _public prototype_ `UCommonActivatableWidgetContainerBase(const FObjectInitializer& Initializer);`
- L33 _public function_ `template <typename ActivatableWidgetT = UCommonActivatableWidget> ActivatableWidgetT* AddWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)` — Adds an activatable widget to the container. See BP_AddWidget for more info.
- L49 _public function_ `template <typename ActivatableWidgetT = UCommonActivatableWidget> ActivatableWidgetT* AddWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InstanceInitFunc)` — Generates (either creates or pulls from the inactive pool) instance of the given widget class and adds it to the container. The provided lambda is called after the instance has been generated and before it is actually added to the container. So if you've got setup to do on the instance before it potentially activates, the lambda is the place to do it.
- L68 _public prototype_ `void AddWidgetInstance(UCommonActivatableWidget& ActivatableWidget);` — Adds an activatable widget instance to the container. This instance is not pooled in any way by the stack and responsibility for ownership lies with the original creator of the widget. NOTE: In general, it is *strongly* recommended that you opt for the class-based AddWidget above. This one is mostly just here for legacy support.
- L70 _public prototype_ `void RemoveWidget(UCommonActivatableWidget& WidgetToRemove);`
- L73 _public prototype_ `UCommonActivatableWidget* GetActiveWidget() const;` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidgetStack)`
- L75 _public function_ `const TArray<UCommonActivatableWidget*>& GetWidgetList() const`
- L77 _public prototype_ `int32 GetNumWidgets() const;`
- L80 _public prototype_ `void ClearWidgets();` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidgetContainer)`
- L83 _public prototype_ `void SetTransitionDuration(float Duration);` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidgetContainer)`
- L85 _public prototype_ `float GetTransitionDuration() const;` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidgetContainer)`
- L87 _public prototype_ `DECLARE_EVENT_OneParam(UCommonActivatableWidgetContainerBase, FOnDisplayedWidgetChanged, UCommonActivatableWidget*);`
- L88 _public function_ `FOnDisplayedWidgetChanged& OnDisplayedWidgetChanged() const`
- L90 _public prototype_ `DECLARE_EVENT_TwoParams(UCommonActivatableWidgetContainerBase, FTransitioningChanged, UCommonActivatableWidgetContainerBase* , bool );`
- L91 _public member_ `FTransitioningChanged OnTransitioningChanged;`
- L94 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L95 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L96 _protected prototype_ `virtual void OnWidgetRebuilt() override;`
- L98 _protected function_ `virtual void OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget)`
- L100 _protected prototype_ `void SetSwitcherIndex(int32 TargetIndex, bool bInstantTransition = false);`
- L103 _protected prototype_ `virtual const FText GetPaletteCategory() override;`
- L108 _protected member_ `ECommonSwitcherTransition TransitionType;` — `UPROPERTY(EditAnywhere, Category = Transition)` — The type of transition to play between widgets
- L112 _protected member_ `ETransitionCurve TransitionCurveType;` — `UPROPERTY(EditAnywhere, Category = Transition)` — The curve function type to apply to the transition animation
- L116 _protected member_ `float TransitionDuration = 0.4f;` — `UPROPERTY(EditAnywhere, Category = Transition)` — The total duration of a single transition between widgets
- L124 _protected member_ `bool bResetPoolWhenReleasingSlateResources = false;` — `UPROPERTY(EditAnywhere, Category = Performance)` — Whether to completely reset the pool of widgets when slate resources are released. This usually happens when changing maps. You may not want to have all frontend screens loaded taking up memory while in game and vice versa. Enabling this means widgets will have to be loaded again when re-entering the map next time.
- L131 _protected member_ `ECommonSwitcherTransitionFallbackStrategy TransitionFallbackStrategy = ECommonSwitcherTransitionFallbackStrategy::None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Transition)` — Controls how we will choose another widget if a transitioning widget is removed during the transition. Note for Queues and Stacks, ECommonSwitcherTransitionFallbackStrategy::Previous is a good option.
- L134 _protected member_ `TArray<TObjectPtr<UCommonActivatableWidget>> WidgetList;` — `UPROPERTY(Transient)`
- L137 _protected member_ `TObjectPtr<UCommonActivatableWidget> DisplayedWidget;` — `UPROPERTY(Transient)`
- L140 _protected member_ `FUserWidgetPool GeneratedWidgetsPool;` — `UPROPERTY(Transient)`
- L142 _protected member_ `TSharedPtr<SOverlay> MyOverlay;`
- L143 _protected member_ `TSharedPtr<SSpacer> MyInputGuard;`
- L144 _protected member_ `TSharedPtr<SCommonAnimatedSwitcher> MySwitcher;`
- L157 _private prototype_ `UCommonActivatableWidget* BP_AddWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidgetStack, meta = (DeterminesOutputType = ActivatableWidgetClass, DisplayName = "Push Widget"))` — Adds a widget of the given class to the container. Note that all widgets added to the container are pooled, so the caller should not try to cache and re-use the created widget. It is possible for multiple instances of the same class to be added to the container at once, so any instance created in the past is not guaranteed to be the one returned this time. So in practice, you should not trust that any prior state has been retained on the returned widget, and establish all appropriate properties every time.
- L160 _private prototype_ `void RemoveWidget(UCommonActivatableWidget* WidgetToRemove);` — `UFUNCTION(BlueprintCallable, Category = ActivatableWidgetContainer)`
- L162 _private prototype_ `UCommonActivatableWidget* AddWidgetInternal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, TFunctionRef<void(UCommonActivatableWidget&)> InitFunc);`
- L163 _private prototype_ `void RegisterInstanceInternal(UCommonActivatableWidget& NewWidget);`
- L165 _private prototype_ `void HandleSwitcherIsTransitioningChanged(bool bIsTransitioning);`
- L166 _private prototype_ `void HandleActiveIndexChanged(int32 ActiveWidgetIndex);`
- L167 _private prototype_ `void HandleActiveWidgetDeactivated(UCommonActivatableWidget* DeactivatedWidget);`
- L182 _private prototype_ `void ReleaseWidget(const TSharedRef<SWidget>& WidgetToRelease);` — This is a bit hairy and very edge-casey, but a necessary measure to ensure expected Slate interaction behavior. Since we immediately remove slots from our switcher in response to changes to the active index of the switcher, we can wind up confusing the HittestGrid for that frame. The grid (correctly) thinks the widget at the previously displayed index is what it should interact with, but it skips it because we've already released all references and destroyed it. This causes pointer input (most importantly the synthetic mouse move) to fall through our container for that frame, potentially triggering interactions with elements that, as far as any user can tell, were never actually visible! So, when we remove a slot, we hold a reference to the SWidget in that slot for a single frame, to ensure hittest grid integrity. This does delay destruction of the removed SObjectWidget by one frame, but that does not present any discernable issue, as it's no different from any other inactive widget within a switcher.
- L183 _private member_ `TArray<TSharedPtr<SWidget>> ReleasedWidgets;`
- L185 _private member_ `bool bRemoveDisplayedWidgetPostTransition = false;`
- L187 _private member_ `mutable FOnDisplayedWidgetChanged OnDisplayedWidgetChangedEvent;`

#### class `UCommonActivatableWidgetStack`  
`class UCommonActivatableWidgetStack : public UCommonActivatableWidgetContainerBase`  
_L202-221_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommonActivatableWidgetContainerBase`
- desc: A display stack of ActivatableWidget elements. - Only the widget at the top of the stack is displayed and activated. All others are deactivated. - When that top-most displayed widget deactivates, it's automatically removed and the preceding entry is displayed/activated. - If RootContent is provided, it can never be removed regardless of activation state
- L208 _public prototype_ `UCommonActivatableWidget* GetRootContent() const;`
- L211 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L212 _protected prototype_ `virtual void OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget) override;`
- L217 _private member_ `TSubclassOf<UCommonActivatableWidget> RootContentWidgetClass;` — `UPROPERTY(EditAnywhere, Category = Content)` — Optional widget to auto-generate as the permanent root element of the stack
- L220 _private member_ `TObjectPtr<UCommonActivatableWidget> RootContentWidget;` — `UPROPERTY(Transient)`

#### class `UCommonActivatableWidgetQueue`  
`class UCommonActivatableWidgetQueue : public UCommonActivatableWidgetContainerBase`  
_L235-241_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommonActivatableWidgetContainerBase`
- desc: A display queue of ActivatableWidget elements. - Only one widget is active/displayed at a time, all others in the queue are deactivated. - When the active widget deactivates, it is automatically removed from the widget, released back to the pool, and the next widget in the queue (if any) is displayed
- L240 _protected prototype_ `virtual void OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONUI_API`
- L38 _function_ `return Cast<ActivatableWidgetT>(AddWidgetInternal(ActivatableWidgetClass, [](UCommonActivatableWidget&) {}));` (scope `UCommonActivatableWidgetContainerBase::AddWidget`)
- L55 _function_ `` (scope `UCommonActivatableWidgetContainerBase::AddWidget`)
- L87 _delegate_ `DECLARE_EVENT_OneParam(UCommonActivatableWidgetContainerBase, FOnDisplayedWidgetChanged, UCommonActivatableWidget*);`
- L90 _delegate_ `DECLARE_EVENT_TwoParams(UCommonActivatableWidgetContainerBase, FTransitioningChanged, UCommonActivatableWidgetContainerBase* , bool );`
