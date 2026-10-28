# Plugins / UIFramework

- module root: `Plugins/Experimental/UIFramework/Source`
- headers: 26; symbols: 650
- symbol kinds: class=25, delegate=9, enum=8, enumerator=10, function=84, macro=20, member=150, namespace=1, prototype=312, struct=31
- PrivateDependencyModuleNames: CommonInput, GameplayTags, NetCore
- PublicDependencyModuleNames: CommonUI, Core, CoreUObject, DeveloperSettings, Engine, EnhancedInput, FieldNotification, LocalizableMessage, ModelViewViewModel, Slate, SlateCore, UMG
- PublicIncludePathModuleNames: 

### `Plugins/Experimental/UIFramework/Source/Private/UIFLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUIFramework, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUIFramework, Log, All);`

### `Plugins/Experimental/UIFramework/Source/Private/Widgets/SUIFrameworkButtonWidget.h` (Private)


#### class `SUIFrameworkButtonWidget`  
`class SUIFrameworkButtonWidget : public SButton`  
_L20-93_
- inherits: `SButton`
- desc: Slate button for UUIFrameworkButtonWidget. It exposes touch events for start, end, and long press.
- L24 _public function_ `SLATE_BEGIN_ARGS(SUIFrameworkButtonWidget) : _OnTouchLongPressedDelegate() , _OnTouchStartedDelegate() , _OnTouchEndedDelegate() , _ButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("Button")) , _OnSlateButtonDragDetected() , _OnSlateButtonDragEnter() , _OnSlateButtonDragLeave() , _OnSlateButtonDragOver() , _OnSlateButtonDrop() , _ClickMethod(EButtonClickMethod::DownAndUp) , _TouchMethod(EButtonTouchMethod::DownAndUp) , _PressMethod(EButtonPressMethod::DownAndUp) , _IsFocusable(true) , _AllowDragDrop(false)`
- L42 _public prototype_ `SLATE_EVENT(FOnTouch, OnTouchLongPressedDelegate) SLATE_EVENT(FOnTouch, OnTouchStartedDelegate) SLATE_EVENT(FOnTouch, OnTouchEndedDelegate) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_EVENT(FOnClicked, OnClicked) SLATE_EVENT(FSimpleDelegate, OnPressed) SLATE_EVENT(FSimpleDelegate, OnReleased) SLATE_EVENT(FSimpleDelegate, OnHovered) SLATE_EVENT(FSimpleDelegate, OnUnhovered) SLATE_EVENT(FSimpleDelegate, OnReceivedFocus) SLATE_EVENT(FSimpleDelegate, OnLostFocus)`
- L84 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent) override;` — SWidget overrides
- L85 _public prototype_ `virtual FReply OnPreviewMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L86 _public prototype_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L90 _private member_ `FOnTouch OnTouchLongPressedDelegate;`
- L91 _private member_ `FOnTouch OnTouchStartedDelegate;`
- L92 _private member_ `FOnTouch OnTouchEndedDelegate;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( FReply, FOnTouch, const FPointerEvent&) class SUIFrameworkButtonWidget : public SButton { public: SLATE_BEGIN_ARGS(SUIFrameworkButtonWidget) : _OnTouchLongPressedDelegate() , _OnTouchStartedDelegate() , _OnTouchEndedDelegate() , _ButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("Button")) , _OnSlateButtonDragDetected() , _OnSlateButtonDragEnter() , _OnSlateButtonDragLeave() , _OnSlateButtonDragOver() , _OnSlateButtonDrop() , _ClickMethod(EButtonClickMethod::DownAndUp) , _TouchMethod(EButtonTouchMethod::DownAndUp) , _PressMethod(EButtonPressMethod::DownAndUp) , _IsFocusable(true) , _AllowDragDrop(false) { } SLATE_EVENT(FOnTouch, OnTouchLongPressedDelegate) SLATE_EVENT(FOnTouch, OnTouchStartedDelegate) SLATE_EVENT(FOnTouch, OnTouchEndedDelegate) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)`

### `Plugins/Experimental/UIFramework/Source/Private/Widgets/UIFrameworkButtonWidget.h` (Private)


#### class `UUIFrameworkButtonWidget`  
`class UUIFrameworkButtonWidget : public UButton`  
_L23-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UButton`
- L28 _public prototype_ `UUIFrameworkButtonWidget();`
- L31 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L32 _public prototype_ `virtual void OnWidgetRebuilt() override;`
- L33 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L34 _public prototype_ `virtual APlayerController* GetOwningPlayer() const override;`
- L37 _public prototype_ `void SetTriggeringEnhancedInputAction(UInputAction* InInputAction);`
- L39 _public member_ `FSimpleDelegate OnTouchLongPress;`
- L40 _public member_ `FSimpleDelegate OnTouchStarted;`
- L41 _public member_ `FSimpleDelegate OnTouchEnded;`
- L43 _public member_ `FOnButtonClickedEvent OnTriggered;`
- L46 _protected prototype_ `FReply SlateHandleTouchLongPress(const FPointerEvent& PointerEvent);`
- L47 _protected prototype_ `FReply SlateHandleTouchStarted(const FPointerEvent& PointerEvent);`
- L48 _protected prototype_ `FReply SlateHandleTouchEnded(const FPointerEvent& PointerEvent);`
- L53 _private prototype_ `void HandleButtonClicked();` — `UFUNCTION()`
- L54 _private prototype_ `void ExecuteTriggeredInput();`
- L56 _private prototype_ `void BindTriggeringInputActionToClick();`
- L57 _private prototype_ `void UnbindTriggeringInputActionToClick();`
- L59 _private prototype_ `void StartTrackingTouch(int32 PointerIndex);`
- L60 _private prototype_ `void StopTrackingTouch();`
- L62 _private prototype_ `bool HandleTouchEnded();`
- L66 _protected member_ `TObjectPtr<UInputAction> TriggeringInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)`
- L70 _private member_ `TSharedPtr<class SUIFrameworkButtonWidget> UIFButton;` — Cached pointer to the underlying slate button owned by this UWidget
- L72 _private member_ `FUIActionBindingHandle TriggeringBindingHandle;`
- L74 _private member_ `TSharedPtr<FUIFInputPreProcessor> InputPreProcessor;`
- L75 _private member_ `bool bTouchStarted = false;`
- L76 _private member_ `bool bLongPressActive = false;`

#### class `FUIFInputPreProcessor`  
`class FUIFInputPreProcessor : public IInputProcessor , public TSharedFromThis<FUIFInputPreProcessor>`  
_L79-97_
- inherits: `IInputProcessor,TSharedFromThis<FUIFInputPreProcessor>`
- L84 _public function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override`
- L85 _public prototype_ `virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L87 _public function_ `FTrackedTouchEnded& OnTrackedTouchEnded()`
- L89 _public prototype_ `void StartTrackingTouch(int32 Index);`
- L90 _public prototype_ `void StopTrackingTouch();`
- L92 _public function_ `int32 GetTrackedTouchIndex() const`
- L95 _private member_ `int32 TrackedTouchIndex = INDEX_NONE;`
- L96 _private member_ `FTrackedTouchEnded OnTrackedTouchEndedDelegate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UIFRAMEWORK_API`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal( bool, FTrackedTouchEnded) class UInputAction;`

### `Plugins/Experimental/UIFramework/Source/Private/Widgets/UIFrameworkCustomButtonWidget.h` (Private)


#### class `UUIFrameworkCustomButtonWidget`  
`class UUIFrameworkCustomButtonWidget : public UUIFrameworkButtonWidget`  
_L18-65_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Custom Button"))`
- inherits: `UUIFrameworkButtonWidget`
- L22 _public prototype_ `UUIFrameworkCustomButtonWidget();`
- L24 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L27 _private prototype_ `void LocalCreateDefaultUMGWidget();`
- L29 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L32 _private prototype_ `void HandleButtonClick();` — `UFUNCTION()`
- L35 _private prototype_ `void HandleButtonHighlight();` — `UFUNCTION()`
- L38 _private prototype_ `void HandleButtonUnhighlight();` — `UFUNCTION()`
- L41 _private prototype_ `void HandleButtonHover();` — `UFUNCTION()`
- L44 _private prototype_ `void HandleButtonUnhover();` — `UFUNCTION()`
- L47 _private member_ `TObjectPtr<UWidget> LocalDefaultUMGWidget;` — `UPROPERTY(Transient)`
- L50 _private member_ `TSoftClassPtr<UWidget> DefaultContentWidgetClass;` — `UPROPERTY(EditDefaultsOnly, Category = "UI Framework")`
- L52 _private member_ `TSharedPtr<FStreamableHandle> WidgetClassStreamableHandle;`
- L55 _protected prototype_ `TSharedPtr<FStreamableHandle> AsyncLoadDefaultWidgetClass();`
- L58 _protected member_ `FOnButtonClickedEvent OnButtonClicked;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Clicked"))`
- L61 _protected member_ `FOnButtonClickedEvent OnButtonHighlight;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Highlight"))`
- L64 _protected member_ `FOnButtonClickedEvent OnButtonUnhighlight;` — `UPROPERTY(BlueprintAssignable, Category = "Events", meta = (AllowPrivateAccess = true, DisplayName = "On Unhighlight"))`

### `Plugins/Experimental/UIFramework/Source/Private/Widgets/UIFrameworkTouchActionWrapperWidget.h` (Private)


#### class `UUIFrameworkTouchActionWrapperWidget`  
`class UUIFrameworkTouchActionWrapperWidget : public UUIFrameworkButtonWidget`  
_L17-31_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Touch Action Wrapper"))`
- inherits: `UUIFrameworkButtonWidget`
- L22 _public prototype_ `UUIFrameworkTouchActionWrapperWidget();`
- L24 _public prototype_ `bool HandleTouch() const;`
- L27 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L28 _private prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L30 _private member_ `TSharedPtr<FUIFTouchInputPreProcessor> TouchInputPreProcessor;`

#### class `FUIFTouchInputPreProcessor`  
`class FUIFTouchInputPreProcessor : public IInputProcessor , public TSharedFromThis<FUIFTouchInputPreProcessor>`  
_L33-59_
- inherits: `IInputProcessor,TSharedFromThis<FUIFTouchInputPreProcessor>`
- L38 _public prototype_ `FUIFTouchInputPreProcessor();`
- L39 _public function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override`
- L40 _public prototype_ `virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L42 _public function_ `FTrackedTouchEnded& OnTrackedTouchEnded()`
- L43 _public prototype_ `void SetTargetWidget(TWeakPtr<SWidget> InWidget);`
- L45 _public prototype_ `void StartTrackingTouch();`
- L46 _public prototype_ `void StopTrackingTouch();`
- L50 _private prototype_ `bool IsInputHittingWidget(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent);`
- L53 _private member_ `FTrackedTouchEnded OnTrackedTouchEndedDelegate;`
- L55 _private member_ `TWeakPtr<SWidget> TargetWidget;`
- L57 _private member_ `TArray<FSoftObjectPath> WidgetClassesToIgnore;`
- L58 _private member_ `TArray<TWeakPtr<SWidget>> CachedWidgetsToIgnore;`

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFEvents.h` (Public)


#### struct `FUIFrameworkSimpleEventArgument`  
`struct FUIFrameworkSimpleEventArgument`  
_L16-27_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FUIFrameworkSimpleEventArgument() = default;`
- L23 _public member_ `TObjectPtr<APlayerController> PlayerController;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<UUIFrameworkWidget> Sender;` — `UPROPERTY()`

#### struct `FUIFrameworkClickEventArgument`  
`struct FUIFrameworkClickEventArgument : public FUIFrameworkSimpleEventArgument`  
_L35-40_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSimpleEventArgument`
- L39 _public prototype_ `FUIFrameworkClickEventArgument() = default;`

#### struct `FUIFrameworkHighlightEventArgument`  
`struct FUIFrameworkHighlightEventArgument : public FUIFrameworkSimpleEventArgument`  
_L48-53_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSimpleEventArgument`
- L52 _public prototype_ `FUIFrameworkHighlightEventArgument() = default;`

#### struct `FUIFrameworkUnhighlightEventArgument`  
`struct FUIFrameworkUnhighlightEventArgument : public FUIFrameworkSimpleEventArgument`  
_L61-66_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSimpleEventArgument`
- L65 _public prototype_ `FUIFrameworkUnhighlightEventArgument() = default;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkSimpleEvent, FUIFrameworkSimpleEventArgument);`
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkSimpleEvent, FUIFrameworkSimpleEventArgument);`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkClickEvent, FUIFrameworkClickEventArgument);`
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkClickEvent, FUIFrameworkClickEventArgument);`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkHighlightEvent, FUIFrameworkHighlightEventArgument);`
- L55 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkHighlightEvent, FUIFrameworkHighlightEventArgument);`
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkUnhighlightEvent, FUIFrameworkUnhighlightEventArgument);`
- L68 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkUnhighlightEvent, FUIFrameworkUnhighlightEventArgument);`

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFParentWidget.h` (Public)


#### struct `FUIFrameworkParentWidget`  
`struct FUIFrameworkParentWidget`  
_L17-69_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public prototype_ `FUIFrameworkParentWidget() = default;`
- L23 _public prototype_ `FUIFrameworkParentWidget(UUIFrameworkWidget* InWidget);`
- L24 _public prototype_ `FUIFrameworkParentWidget(UUIFrameworkPlayerComponent* InPlayer);`
- L27 _public function_ `bool IsParentValid() const`
- L32 _public function_ `bool IsWidget() const`
- L38 _public function_ `bool IsPlayerComponent() const`
- L44 _public prototype_ `UUIFrameworkWidget* AsWidget() const;`
- L45 _public prototype_ `UUIFrameworkPlayerComponent* AsPlayerComponent() const;`
- L47 _public prototype_ `bool operator== (const UUIFrameworkWidget* Other) const;`
- L49 _public function_ `bool operator!= (const UUIFrameworkWidget* Other) const`
- L54 _public function_ `bool operator== (const FUIFrameworkParentWidget& Other) const`
- L59 _public function_ `bool operator!= (const FUIFrameworkParentWidget& Other) const`
- L66 _private member_ `TObjectPtr<UObject> Parent = nullptr;` — `UPROPERTY()`
- L68 _private member_ `bool bIsParentAWidget = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFSlotBase.h` (Public)


#### struct `FUIFrameworkSlotBase`  
`struct FUIFrameworkSlotBase : public FFastArraySerializerItem`  
_L23-64_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FFastArraySerializerItem`
- L27 _public prototype_ `FUIFrameworkSlotBase() = default;`
- L29 _public function_ `UUIFrameworkWidget* AuthorityGetWidget() const`
- L34 _public prototype_ `void AuthoritySetWidget(UUIFrameworkWidget* Widget);`
- L36 _public function_ `FUIFrameworkWidgetId GetWidgetId() const`
- L41 _public function_ `void LocalAquireWidget()`
- L46 _public function_ `bool LocalIsAquiredWidgetValid() const`
- L53 _private member_ `TObjectPtr<UUIFrameworkWidget> Widget = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework", NotReplicated, meta = (AllowPrivateAccess = "true"))`
- L56 _private member_ `FUIFrameworkWidgetId WidgetId;` — `UPROPERTY()`
- L63 _private member_ `FUIFrameworkWidgetId LocalPreviousWidgetId;` — `UPROPERTY(NotReplicated)` — The widget that was previously added on the local UMG Widget. The server may have changed it but the "application" of that modification may be applied on the next frame by the PlayerComponent.

#### struct `FUIFrameworkSimpleSlot`  
`struct FUIFrameworkSimpleSlot : public FUIFrameworkSlotBase`  
_L71-85_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSlotBase`
- L75 _public prototype_ `FUIFrameworkSimpleSlot() = default;`
- L78 _public member_ `FMargin Padding;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework")`
- L81 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework")`
- L84 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Fill;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFWidgetId.h` (Public)


#### struct `FUIFrameworkWidgetId`  
`struct FUIFrameworkWidgetId`  
_L15-66_
- reflection: `USTRUCT()`
- L19 _public prototype_ `FUIFrameworkWidgetId() = default;`
- L20 _public prototype_ `explicit FUIFrameworkWidgetId(UUIFrameworkWidget* InWidget);`
- L22 _public prototype_ `static FUIFrameworkWidgetId MakeNew();`
- L23 _public prototype_ `static FUIFrameworkWidgetId MakeRoot();`
- L26 _private function_ `FUIFrameworkWidgetId(int64 InKey) : Key(InKey)`
- L31 _public function_ `int64 GetKey() const`
- L36 _public function_ `bool IsRoot() const`
- L41 _public function_ `bool IsValid() const`
- L46 _public function_ `bool operator==(const FUIFrameworkWidgetId& Other) const`
- L51 _public function_ `bool operator!=(const FUIFrameworkWidgetId& Other) const`
- L63 _private member_ `int64 Key = INDEX_NONE;` — `UPROPERTY()`
- L65 _private member_ `static int64 KeyGenerator;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UIFRAMEWORK_API`
- L56 _function_ `inline friend uint32 GetTypeHash(const FUIFrameworkWidgetId& Value)`

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFWidgetOwner.h` (Public)


#### struct `FUIFrameworkWidgetOwner`  
`struct FUIFrameworkWidgetOwner`  
_L16-28_
- reflection: `USTRUCT()`
- L21 _public member_ `TObjectPtr<APlayerController> PlayerController = nullptr;` — `UPROPERTY()`
- L24 _public member_ `TObjectPtr<UGameInstance> GameInstance = nullptr;` — `UPROPERTY()`
- L27 _public member_ `TObjectPtr<UWorld> World = nullptr;` — `UPROPERTY()`

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFWidgetTree.h` (Public)


#### struct `FUIFrameworkWidgetTreeEntry`  
`struct FUIFrameworkWidgetTreeEntry : public FFastArraySerializerItem`  
_L35-58_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializerItem`
- L39 _public prototype_ `FUIFrameworkWidgetTreeEntry() = default;`
- L40 _public prototype_ `FUIFrameworkWidgetTreeEntry(UUIFrameworkWidget* Parent, UUIFrameworkWidget* Child);`
- L42 _public prototype_ `bool IsParentValid() const;`
- L43 _public prototype_ `bool IsChildValid() const;`
- L46 _public member_ `TObjectPtr<UUIFrameworkWidget> Parent = nullptr;` — `UPROPERTY()`
- L49 _public member_ `TObjectPtr<UUIFrameworkWidget> Child = nullptr;` — `UPROPERTY()`
- L52 _public member_ `FUIFrameworkWidgetId ParentId;` — `UPROPERTY()`
- L55 _public member_ `FUIFrameworkWidgetId ChildId;` — `UPROPERTY()`
- L57 _public prototype_ `FString GetDebugString();`

#### struct `FUIFrameworkWidgetTree`  
`struct FUIFrameworkWidgetTree : public FFastArraySerializer`  
_L67-162_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- desc: A valid snapshot of the widget tree that can be replicated to local instance. Authority widgets know their parent/children relation. That information is not replicated to the local widgets. When a widget is added to the tree, the tree is updated. The widget now has to inform the tree when that relationship changes until it's remove from the tree.
- L72 _public prototype_ `FUIFrameworkWidgetTree() = default;`
- L73 _public prototype_ `FUIFrameworkWidgetTree(AActor* InReplicatedOwner, IUIFrameworkWidgetTreeOwner* InOwner);`
- L74 _public prototype_ `~FUIFrameworkWidgetTree();`
- L78 _public prototype_ `void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);`
- L79 _public prototype_ `void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);`
- L80 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L83 _public function_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)`
- L88 _public function_ `AActor* GetReplicationOwner() const`
- L93 _public prototype_ `bool ReplicateSubWidgets(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);`
- L96 _public prototype_ `void AuthorityAddRoot(UUIFrameworkWidget* Widget);` — Add a new widget to the top hierarchy.
- L101 _public prototype_ `void AuthorityAddWidget(UUIFrameworkWidget* Parent, UUIFrameworkWidget* Child);` — Change the parent / child relationship of the child widget. If the child widget had a parent, that relationship entry will replaced it by a new one.
- L106 _public prototype_ `void AuthorityRemoveWidgetAndChildren(UUIFrameworkWidget* Widget);` — Remove the widget and all of its children and grand-children from the tree. It will clean all the parent relationship from the tree.
- L111 _public prototype_ `void LocalRemoveRoot(const UUIFrameworkWidget* Widget);` — The widget was removed from the client and the Authority is not aware of it.
- L114 _public prototype_ `FUIFrameworkWidgetTreeEntry* LocalGetEntryByReplicationId(int32 WidgetId);`
- L115 _public prototype_ `const FUIFrameworkWidgetTreeEntry* LocalGetEntryByReplicationId(int32 WidgetId) const;`
- L118 _public prototype_ `UUIFrameworkWidget* FindWidgetById(FUIFrameworkWidgetId WidgetId);` — Find the widget by its unique Id. The widget needs to be in the Tree.
- L119 _public prototype_ `const UUIFrameworkWidget* FindWidgetById(FUIFrameworkWidgetId WidgetId) const;`
- L122 _public prototype_ `void AuthorityAddAllWidgetsFromActorChannel();` — Add all widgets in the tree to the ActorChannel replicated list
- L125 _public prototype_ `void AuthorityRemoveAllWidgetsFromActorChannel();` — Removes all widgets added to the ActorChannel replicated list
- L128 _public prototype_ `const FUIFrameworkWidgetTreeEntry* FindRootEntryById(FUIFrameworkWidgetId WidgetId) const;` — Gets the root widget of the tree given the Id of a widget in the tree
- L131 _public prototype_ `void AuthorityTest() const;`
- L132 _public prototype_ `void LogTree() const;`
- L133 _public prototype_ `void LogWidgetsChildren() const;`
- L136 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkWidgetDelegate, UUIFrameworkWidget*);`
- L137 _public member_ `FUIFrameworkWidgetDelegate AuthorityOnWidgetAdded;`
- L138 _public member_ `FUIFrameworkWidgetDelegate AuthorityOnWidgetRemoved;`
- L139 _public member_ `FUIFrameworkWidgetDelegate LocalOnWidgetAdded;`
- L142 _private prototype_ `void AuthorityAddChildInternal(UUIFrameworkWidget* Parent, UUIFrameworkWidget* Child, bool bFirst);`
- L143 _private prototype_ `void AuthorityAddChildRecursiveInternal(UUIFrameworkWidget* Widget);`
- L144 _private prototype_ `bool AuthorityRemoveChildRecursiveInternal(UUIFrameworkWidget* Widget);`
- L147 _private prototype_ `void LogTreeInternal(const FUIFrameworkWidgetTreeEntry& Entry, FString Spaces) const;`
- L148 _private prototype_ `void AuthorityLogWidgetsChildrenInternal(UUIFrameworkWidget* Widget, FString Spaces) const;`
- L149 _private prototype_ `void LocalLogWidgetsChildrenInternal(const UWidget* Widget, FString Spaces) const;`
- L154 _private member_ `TArray<FUIFrameworkWidgetTreeEntry> Entries;` — `UPROPERTY()`
- L157 _private member_ `TObjectPtr<AActor> ReplicatedOwner;` — `UPROPERTY(NotReplicated, Transient)`
- L159 _private member_ `TMap<FObjectKey, int32> AuthorityIndexByWidgetMap;`
- L160 _private member_ `TMap<FUIFrameworkWidgetId, TWeakObjectPtr<UUIFrameworkWidget>> WidgetByIdMap;`
- L161 _private member_ `IUIFrameworkWidgetTreeOwner* Owner = nullptr;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUIFrameworkWidgetTree> : public TStructOpsTypeTraitsBase2<FUIFrameworkWidgetTree>`  
_L165-168_
- inherits: `TStructOpsTypeTraitsBase2<FUIFrameworkWidgetTree>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L167-167_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UIFRAMEWORK_API`
- L16 _macro_ `#define UE_UIFRAMEWORK_WITH_DEBUG !(UE_BUILD_SHIPPING)`
- L136 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUIFrameworkWidgetDelegate, UUIFrameworkWidget*);`
- L167 _enumerator_ `enum { WithNetDeltaSerializer = true };` (scope `TStructOpsTypeTraits::__anonb670cabf0103`)

### `Plugins/Experimental/UIFramework/Source/Public/Types/UIFWidgetTreeOwner.h` (Public)


#### class `IUIFrameworkWidgetTreeOwner`  
`class IUIFrameworkWidgetTreeOwner`  
_L14-37_
- L18 _public prototype_ `virtual FUIFrameworkWidgetTree& GetWidgetTree() = 0;` — The widget tree.
- L21 _public prototype_ `virtual FUIFrameworkWidgetOwner GetWidgetOwner() const = 0;` — The object that will be used to create the UserWidget.
- L24 _public function_ `virtual void LocalWidgetWasAddedToTree(const FUIFrameworkWidgetTreeEntry& Entry)` — A widget was added to the tree.
- L29 _public function_ `virtual void LocalWidgetRemovedFromTree(const FUIFrameworkWidgetTreeEntry& Entry)` — A widget was removed to the tree.
- L34 _public function_ `virtual void LocalRemoveWidgetRootFromTree(const UUIFrameworkWidget* Widget)` — Remove the widget (and the child) from the server.

### `Plugins/Experimental/UIFramework/Source/Public/UIFLocalSettings.h` (Public)


#### class `UUIFrameworkLocalSettings`  
`class UUIFrameworkLocalSettings : public UDeveloperSettings`  
_L16-65_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig, meta = (DisplayName = "UI Framework Local Settings"))`
- inherits: `UDeveloperSettings`
- L21 _public prototype_ `UUIFrameworkLocalSettings();`
- L23 _public function_ `UObject* GetErrorResource() const`
- L28 _public function_ `UObject* GetLoadingResource() const`
- L33 _public prototype_ `void LoadResources() const;`
- L35 _public prototype_ `virtual FName GetCategoryName() const override;`
- L37 _public function_ `virtual bool NeedsLoadForServer() const override`
- L43 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L52 _private member_ `TSoftObjectPtr<UObject> ErrorResource;` — `UPROPERTY(Config, EditAnywhere, Category = "UI Framework", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", AllowedClasses = "/Script/Engine.Texture,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))` — The image to render for when a requested resource is inaccessible. It can be a UTexture or UMaterialInterface or an object implementing the AtlasedTextureInterface.
- L59 _private member_ `TSoftObjectPtr<UObject> LoadingResource;` — `UPROPERTY(Config, EditAnywhere, Category = "UI Framework", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", AllowedClasses = "/Script/Engine.Texture,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))` — The image to render while a resource is loading. It can be a UTexture or UMaterialInterface or an object implementing the AtlasedTextureInterface.
- L62 _private member_ `TObjectPtr<UObject> ErrorResourcePtr;`
- L63 _private member_ `TObjectPtr<UObject> LoadingResourcePtr;`
- L64 _private member_ `mutable bool bResourceLoaded = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/UIFModule.h` (Public)


#### class `FUIFrameworkModule`  
`class FUIFrameworkModule : public IModuleInterface`  
_L19-43_
- inherits: `IModuleInterface`
- L28 _public prototype_ `static UUIFrameworkWidget* AuthorityAttachWidget(FUIFrameworkParentWidget Parent, UUIFrameworkWidget* Child);` — Set the new widget parent. It will attach the widget to the correct ReplicationOwner and add it to the WidgetTree. If the ReplicationOwner cannot be changed, a duplicate of the widget will be created and the AuthorityOnReattachWidgets will be broadcast. This function is recursive if the owner changed.
- L29 _public prototype_ `static bool AuthorityCanWidgetBeAttached(FUIFrameworkParentWidget Parent, UUIFrameworkWidget* Child);`
- L33 _public prototype_ `static void AuthorityDetachWidgetFromParent(UUIFrameworkWidget* Child);` — Will remove the widget from the tree and the replication owner.
- L36 _public prototype_ `static void SetPresenterClass(TSubclassOf<UUIFrameworkPresenter> Director);`
- L37 _public prototype_ `static TSubclassOf<UUIFrameworkPresenter> GetPresenterClass();`
- L40 _private prototype_ `static void AuthorityDetachWidgetFromParentInternal(UUIFrameworkWidget* Child, bool bTemporary);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/UIFPlayerComponent.h` (Public)


#### enum `EUIFrameworkGameLayerType`  
`enum class EUIFrameworkGameLayerType : uint8`  
_L27-31_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Viewport`
- L30 _public enumerator_ `PlayerScreen`

#### enum `EUIFrameworkInputMode`  
`enum class EUIFrameworkInputMode : uint8`  
_L37-43_
- reflection: `UENUM(BlueprintType)`
- L40 _public enumerator_ `UI` — Input is received by the UI.
- L42 _public enumerator_ `Game` — Input is received by the Game.

#### struct `FUIFrameworkGameLayerSlot`  
`struct FUIFrameworkGameLayerSlot : public FUIFrameworkSlotBase`  
_L50-64_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSlotBase`
- L54 _public prototype_ `FUIFrameworkGameLayerSlot() = default;`
- L57 _public member_ `int32 ZOrder = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework")`
- L60 _public member_ `EUIFrameworkInputMode InputMode = EUIFrameworkInputMode::Game;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework")`
- L63 _public member_ `EUIFrameworkGameLayerType Type = EUIFrameworkGameLayerType::Viewport;` — `UPROPERTY(BlueprintReadWrite, Category = "UI Framework")`

#### struct `FUIFrameworkWidgetToFocus`  
`struct FUIFrameworkWidgetToFocus`  
_L70-81_
- reflection: `USTRUCT()`
- L76 _public member_ `FUIFrameworkWidgetId Id;` — `UPROPERTY()`
- L80 _public member_ `int32 ReplicationCounter = 0;` — `UPROPERTY()`

#### struct `FUIFrameworkGameLayerSlotList`  
`struct FUIFrameworkGameLayerSlotList : public FFastArraySerializer`  
_L87-120_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L93 _public prototype_ `FUIFrameworkGameLayerSlotList() = default;`
- L94 _public function_ `FUIFrameworkGameLayerSlotList(UUIFrameworkPlayerComponent* InOwner) : Owner(InOwner)`
- L100 _public prototype_ `void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize);`
- L101 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L104 _public function_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)`
- L109 _public prototype_ `void AddEntry(FUIFrameworkGameLayerSlot Entry);`
- L110 _public prototype_ `bool RemoveEntry(UUIFrameworkWidget* Layer);`
- L111 _public prototype_ `FUIFrameworkGameLayerSlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L112 _public prototype_ `const FUIFrameworkGameLayerSlot* FindEntry(FUIFrameworkWidgetId WidgetId) const;`
- L116 _private member_ `TArray<FUIFrameworkGameLayerSlot> Entries;` — `UPROPERTY()`
- L119 _private member_ `TObjectPtr<UUIFrameworkPlayerComponent> Owner;` — `UPROPERTY(NotReplicated, Transient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUIFrameworkGameLayerSlotList> : public TStructOpsTypeTraitsBase2<FUIFrameworkGameLayerSlotList>`  
_L123-126_
- inherits: `TStructOpsTypeTraitsBase2<FUIFrameworkGameLayerSlotList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L125-125_

#### class `UUIFrameworkPlayerComponent`  
`class UUIFrameworkPlayerComponent : public UActorComponent, public IUIFrameworkWidgetTreeOwner`  
_L133-253_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IUIFrameworkWidgetTreeOwner`
- L140 _public prototype_ `UUIFrameworkPlayerComponent();`
- L143 _public prototype_ `void AddWidget(FUIFrameworkGameLayerSlot Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L146 _public prototype_ `void RemoveWidget(UUIFrameworkWidget* Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L148 _public function_ `const FUIFrameworkGameLayerSlotList& GetRootList() const`
- L155 _public function_ `template <class T = APlayerController> T* GetPlayerController() const` — Gets the controller that owns the component, this will always be valid during gameplay but can return null in the editor
- L172 _public function_ `template <class T = APlayerController> T* GetPlayerControllerChecked() const`
- L181 _public prototype_ `virtual void InitializeComponent() override;`
- L182 _public prototype_ `virtual void UninitializeComponent() override;`
- L183 _public prototype_ `virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;`
- L184 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L187 _public prototype_ `void AuthorityRemoveChild(UUIFrameworkWidget* Widget);`
- L188 _public prototype_ `FOnPendingReplicationProcessed& GetOnPendingReplicationProcessed();`
- L190 _public prototype_ `virtual FUIFrameworkWidgetTree& GetWidgetTree() override;`
- L191 _public prototype_ `virtual FUIFrameworkWidgetOwner GetWidgetOwner() const override;`
- L192 _public prototype_ `virtual void LocalWidgetWasAddedToTree(const FUIFrameworkWidgetTreeEntry& Entry) override;`
- L193 _public prototype_ `virtual void LocalWidgetRemovedFromTree(const FUIFrameworkWidgetTreeEntry& Entry) override;`
- L194 _public prototype_ `virtual void LocalRemoveWidgetRootFromTree(const UUIFrameworkWidget* Widget) override;`
- L196 _public prototype_ `void SetWidgetToFocus(FUIFrameworkWidgetId WidgetId);`
- L199 _protected prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId WidgetId);`
- L203 _private prototype_ `void ServerRemoveWidgetRootFromTree(FUIFrameworkWidgetId WidgetId);` — `UFUNCTION(Server, Reliable)`
- L205 _private prototype_ `void LocalOnClassLoaded(TSoftClassPtr<UWidget> WidgetClass);`
- L208 _private prototype_ `void OnRep_WidgetToFocus();` — `UFUNCTION()`
- L209 _private prototype_ `bool TrySetFocus(float DeltaTime, FUIFrameworkWidgetId CurrentWidgetToFocusId);`
- L211 _private prototype_ `void HandleAddPending();`
- L213 _private prototype_ `UUIFrameworkPresenter* GetOrCreatePresenter();`
- L217 _private member_ `FUIFrameworkGameLayerSlotList RootList;` — `UPROPERTY(Replicated)`
- L220 _private member_ `FUIFrameworkWidgetTree WidgetTree;` — `UPROPERTY(Replicated)`
- L223 _private member_ `TObjectPtr<UUIFrameworkPresenter> Presenter;` — `UPROPERTY(Transient)`
- L227 _private member_ `TSet<int32> NetReplicationPending;` — `UPROPERTY(Transient)`
- L231 _private member_ `TSet<int32> AddPending;` — `UPROPERTY(Transient)`
- L234 _private member_ `FOnPendingReplicationProcessed OnPendingReplicationProcessed;`
- L238 _private member_ `FUIFrameworkWidgetToFocus WidgetToFocus;` — `UPROPERTY(ReplicatedUsing=OnRep_WidgetToFocus, Transient)`
- L240 _private member_ `bool bIsPendingFocusCall = false;`
- L248 _private member_ `TMap<TSoftClassPtr<UWidget>, FWidgetClassToLoad> ClassesToLoad;`
- L250 _private member_ `bool bAddingWidget = false;`
- L252 _private member_ `FTSTicker::FDelegateHandle PendingWidgetConstructedTickerHandle;`

#### struct `UUIFrameworkPlayerComponent::FWidgetClassToLoad`  
`struct FWidgetClassToLoad`  
_L242-246_
- L244 _public member_ `TArray<int32, TInlineAllocator<4>> EntryReplicationIds;`
- L245 _public member_ `TSharedPtr<FStreamableHandle> StreamableHandle;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UIFRAMEWORK_API`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPendingReplicationProcessed);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPendingReplicationProcessed);`
- L125 _enumerator_ `enum { WithNetDeltaSerializer = true };` (scope `TStructOpsTypeTraits::__anon89e398870103`)

### `Plugins/Experimental/UIFramework/Source/Public/UIFPresenter.h` (Public)


#### class `UUIFrameworkPresenter`  
`class UUIFrameworkPresenter : public UObject`  
_L19-36_
- reflection: `UCLASS(MinimalAPI, Abstract, Within=UIFrameworkPlayerComponent)`
- inherits: `UObject`
- L24 _public function_ `virtual void AddToViewport(UWidget* UMGWidget, const FUIFrameworkGameLayerSlot& Slot)`
- L28 _public function_ `virtual void RemoveFromViewport(FUIFrameworkWidgetId WidgetId)`
- L32 _public function_ `virtual void FocusWidget(UWidget* UMGWidget)`

#### class `UUIFrameworkGameViewportPresenter`  
`class UUIFrameworkGameViewportPresenter : public UUIFrameworkPresenter`  
_L43-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUIFrameworkPresenter`
- L48 _public prototype_ `virtual void AddToViewport(UWidget* UMGWidget, const FUIFrameworkGameLayerSlot& Slot) override;`
- L49 _public prototype_ `virtual void RemoveFromViewport(FUIFrameworkWidgetId WidgetId) override;`
- L50 _public prototype_ `virtual void FocusWidget(UWidget* UMGWidget) override;`
- L51 _public prototype_ `virtual void BeginDestroy() override;`
- L61 _private member_ `TArray<FWidgetPair> Widgets;`

#### struct `UUIFrameworkGameViewportPresenter::FWidgetPair`  
`struct FWidgetPair`  
_L54-60_
- L56 _public prototype_ `FWidgetPair() = default;`
- L57 _public prototype_ `FWidgetPair(UWidget* Widget, FUIFrameworkWidgetId WidgetId);`
- L58 _public member_ `TWeakObjectPtr<UWidget> UMGWidget;`
- L59 _public member_ `FUIFrameworkWidgetId WidgetId;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/UIFWidget.h` (Public)


#### class `UUIFrameworkWidgetWrapperInterface`  
`class UUIFrameworkWidgetWrapperInterface : public UInterface`  
_L27-30_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IUIFrameworkWidgetWrapperInterface`  
`class IUIFrameworkWidgetWrapperInterface`  
_L32-35_

#### class `UUIFrameworkWidget`  
`class UUIFrameworkWidget : public UMVVMViewModelBase`  
_L41-226_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UMVVMViewModelBase`
- L49 _public prototype_ `UUIFrameworkWidget();`
- L50 _public prototype_ `UUIFrameworkWidget(const FObjectInitializer& ObjectInitializer);`
- L54 _private member_ `bool bIsEnabled = true;` — `UPROPERTY(BlueprintReadWrite, ReplicatedUsing = "OnRep_IsEnabled", Getter = "IsEnabled", Setter="SetEnabled", Category = "UI Framework", meta = (AllowPrivateAccess = "true"))`
- L57 _private member_ `ESlateVisibility Visibility = ESlateVisibility::Visible;` — `UPROPERTY(BlueprintReadWrite, ReplicatedUsing = "OnRep_Visibility", Getter, Setter = "SetVisibility", Category = "UI Framework", meta = (AllowPrivateAccess = "true"))`
- L60 _private member_ `bool bIsHitTestVisible = true;` — `UPROPERTY(BlueprintReadWrite, Getter = "IsHitTestVisible", Setter = "SetHitTestVisible", Category = "UI Framework", meta = (AllowPrivateAccess = "true"))`
- L63 _private member_ `double RenderOpacity = 1.0;` — `UPROPERTY(BlueprintReadWrite, ReplicatedUsing = "OnRep_RenderOpacity", Getter, Setter, Category = "UI Framework", meta = (AllowPrivateAccess = "true"))`
- L67 _public function_ `virtual bool IsSupportedForNetworking() const override`
- L71 _public prototype_ `virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;`
- L72 _public prototype_ `virtual bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;`
- L77 _public function_ `template <class T = APlayerController> T* GetPlayerController() const` — Gets the controller that owns the widget
- L101 _public function_ `TScriptInterface<IUIFrameworkWidgetWrapperInterface> AuthorityGetWrapper() const`
- L106 _public function_ `void AuthoritySetWrapper(TScriptInterface<IUIFrameworkWidgetWrapperInterface> InWrapper)`
- L111 _public function_ `FUIFrameworkWidgetId GetWidgetId() const`
- L116 _public function_ `IUIFrameworkWidgetTreeOwner* GetWidgetTreeOwner() const`
- L121 _public prototype_ `FUIFrameworkWidgetTree* GetWidgetTree() const;`
- L123 _public function_ `TSoftClassPtr<UWidget> GetUMGWidgetClass() const`
- L129 _public function_ `FUIFrameworkParentWidget AuthorityGetParent() const`
- L134 _public function_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func)`
- L139 _public function_ `virtual bool LocalIsReplicationReady() const`
- L144 _public function_ `UWidget* LocalGetUMGWidget() const`
- L150 _public prototype_ `UWidget* LocalGetOrCreateUMGWidgetIfReady();` — Can be used instead of manually calling LocalIsReplicationReady() and AsyncLoadWidgetClass()
- L152 _public prototype_ `TSharedPtr<FStreamableHandle> AsyncLoadWidgetClass();`
- L154 _public prototype_ `void LocalCreateUMGWidget(IUIFrameworkWidgetTreeOwner* Owner, bool* bDidCreateWidgetPtr = nullptr);`
- L155 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId);`
- L156 _public prototype_ `void LocalDestroyUMGWidget();`
- L159 _public prototype_ `ESlateVisibility GetVisibility() const;`
- L160 _public prototype_ `void SetVisibility(ESlateVisibility InVisibility);`
- L162 _public prototype_ `bool IsEnabled() const;`
- L163 _public prototype_ `void SetEnabled(bool bEnabled);`
- L165 _public prototype_ `bool IsHitTestVisible() const;`
- L166 _public prototype_ `void SetHitTestVisible(bool bInHitTestVisible);`
- L168 _public prototype_ `double GetRenderOpacity() const;`
- L169 _public prototype_ `void SetRenderOpacity(double InRenderOpacity);`
- L172 _protected function_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget)`
- L175 _protected function_ `virtual void AuthorityOnWidgetTreeOwnerChanged()`
- L178 _protected function_ `virtual void LocalOnUMGWidgetCreated()`
- L182 _protected prototype_ `void ForceNetUpdate();`
- L186 _private prototype_ `void OnRep_IsEnabled();` — `UFUNCTION()`
- L188 _private prototype_ `void OnRep_Visibility();` — `UFUNCTION()`
- L190 _private prototype_ `void OnRep_RenderOpacity();` — `UFUNCTION()`
- L192 _private function_ `void AuthoritySetWidgetTreeOwner(IUIFrameworkWidgetTreeOwner* InWidgetTreeOwner)`
- L203 _protected member_ `TSoftClassPtr<UWidget> WidgetClass;` — `UPROPERTY(BlueprintReadOnly, Replicated, EditDefaultsOnly, Category = "UI Framework")` — todo: make this private and use a constructor argument
- L208 _private member_ `FUIFrameworkWidgetId Id;` — `UPROPERTY(Replicated, Transient, DuplicateTransient)`
- L212 _private member_ `TScriptInterface<IUIFrameworkWidgetWrapperInterface> AuthorityWrapper;` — `UPROPERTY(Transient)`
- L215 _private member_ `IUIFrameworkWidgetTreeOwner* WidgetTreeOwner = nullptr;`
- L219 _private member_ `FUIFrameworkParentWidget AuthorityParent;` — `UPROPERTY(Transient)`
- L223 _private member_ `TObjectPtr<UWidget> LocalUMGWidget;` — `UPROPERTY(Transient)`
- L225 _private member_ `TSharedPtr<FStreamableHandle> WidgetClassStreamableHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFButton.h` (Public)


#### class `UUIFrameworkButton`  
`class UUIFrameworkButton : public UUIFrameworkWidget`  
_L21-97_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Button UIFramework")`
- inherits: `UUIFrameworkWidget`
- L26 _public prototype_ `UUIFrameworkButton();`
- L29 _public prototype_ `void SetContent(FUIFrameworkSimpleSlot Content);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L32 _public function_ `FUIFrameworkSimpleSlot GetContent() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L37 _public prototype_ `void SetTriggeringInputAction(TSoftObjectPtr<UInputAction> InputAction);`
- L39 _public prototype_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func) override;`
- L40 _public prototype_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget) override;`
- L41 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId) override;`
- L44 _protected prototype_ `virtual void LocalOnUMGWidgetCreated() override;`
- L48 _private prototype_ `void HandleClick();` — `UFUNCTION()`
- L51 _private prototype_ `void ServerClick(APlayerController* PlayerController);` — `UFUNCTION(Server, Reliable)`
- L54 _private prototype_ `void HandleHighlight();` — `UFUNCTION()`
- L57 _private prototype_ `void ServerHighlight(APlayerController* PlayerController);` — `UFUNCTION(Server, Reliable)`
- L60 _private prototype_ `void HandleUnhighlight();` — `UFUNCTION()`
- L63 _private prototype_ `void ServerUnhighlight(APlayerController* PlayerController);` — `UFUNCTION(Server, Reliable)`
- L66 _private prototype_ `void HandleHover();` — `UFUNCTION()`
- L69 _private prototype_ `void HandleUnhover();` — `UFUNCTION()`
- L72 _private prototype_ `void OnRep_Slot();` — `UFUNCTION()`
- L75 _private prototype_ `void OnRep_TriggeringInputAction();` — `UFUNCTION()`
- L77 _private prototype_ `void LoadInputAction();`
- L78 _private prototype_ `void HandleInputActionLoaded();`
- L81 _public member_ `FUIFrameworkClickEvent OnClick;`
- L83 _public member_ `FUIFrameworkHighlightEvent OnHighlight;`
- L85 _public member_ `FUIFrameworkUnhighlightEvent OnUnhighlight;`
- L89 _private member_ `FUIFrameworkSimpleSlot Slot;` — `UPROPERTY(/*ExposeOnSpawn, */ReplicatedUsing = OnRep_Slot)`
- L91 _private member_ `bool bIsHighlighted = false;`
- L93 _private member_ `TSharedPtr<FStreamableHandle> AsyncLoadInputActionHandle;`
- L96 _private member_ `TSoftObjectPtr<UInputAction> TriggeringInputAction;` — `UPROPERTY(ReplicatedUsing = OnRep_TriggeringInputAction)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFCanvasBox.h` (Public)


#### struct `FUIFrameworkCanvasBoxSlot`  
`struct FUIFrameworkCanvasBoxSlot : public FUIFrameworkSlotBase`  
_L21-48_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSlotBase`
- L27 _public member_ `FAnchors Anchors = FAnchors(0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)` — Anchors.
- L31 _public member_ `FMargin Offsets = FMargin(0.f, 0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)` — Offset.
- L39 _public member_ `FVector2D Alignment = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)` — Alignment is the pivot point of the widget.  Starting in the upper left at (0,0), ending in the lower right at (1,1).  Moving the alignment point allows you to move the origin of the widget.
- L43 _public member_ `int32 ZOrder = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)` — The order priority this widget is rendered inside the layer. Higher values are rendered last (and so they will appear to be on top).
- L47 _public member_ `bool bSizeToContent = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)` — When true we use the widget's desired size

#### struct `FUIFrameworkCanvasBoxSlotList`  
`struct FUIFrameworkCanvasBoxSlotList : public FFastArraySerializer`  
_L55-82_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L59 _public prototype_ `FUIFrameworkCanvasBoxSlotList() = default;`
- L60 _public function_ `FUIFrameworkCanvasBoxSlotList(UUIFrameworkCanvasBox* InOwner) : Owner(InOwner)`
- L66 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L69 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);`
- L71 _public prototype_ `void AddEntry(FUIFrameworkCanvasBoxSlot Entry);`
- L72 _public prototype_ `bool RemoveEntry(UUIFrameworkWidget* Widget);`
- L73 _public prototype_ `FUIFrameworkCanvasBoxSlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L74 _public prototype_ `void ForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func);`
- L78 _private member_ `TArray<FUIFrameworkCanvasBoxSlot> Slots;` — `UPROPERTY()`
- L81 _private member_ `TObjectPtr<UUIFrameworkCanvasBox> Owner;` — `UPROPERTY(NotReplicated, Transient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUIFrameworkCanvasBoxSlotList> : public TStructOpsTypeTraitsBase2<FUIFrameworkCanvasBoxSlotList>`  
_L86-89_
- inherits: `TStructOpsTypeTraitsBase2<FUIFrameworkCanvasBoxSlotList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L88-88_

#### class `UUIFrameworkCanvasBox`  
`class UUIFrameworkCanvasBox : public UUIFrameworkWidget`  
_L96-124_
- reflection: `UCLASS(MinimalAPI, DisplayName="Canvas UIFramework")`
- inherits: `UUIFrameworkWidget`
- L103 _public prototype_ `UUIFrameworkCanvasBox();`
- L107 _public prototype_ `void AddWidget(FUIFrameworkCanvasBoxSlot Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L110 _public prototype_ `void RemoveWidget(UUIFrameworkWidget* Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L112 _public prototype_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func) override;`
- L113 _public prototype_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget) override;`
- L114 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId) override;`
- L117 _private prototype_ `void AddEntry(FUIFrameworkCanvasBoxSlot Entry);`
- L118 _private prototype_ `bool RemoveEntry(UUIFrameworkWidget* Widget);`
- L119 _private prototype_ `FUIFrameworkCanvasBoxSlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L123 _private member_ `FUIFrameworkCanvasBoxSlotList ReplicatedSlotList;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UIFRAMEWORK_API`
- L88 _enumerator_ `enum { WithNetDeltaSerializer = true };` (scope `TStructOpsTypeTraits::__anon04aedbb20103`)

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFColorBlock.h` (Public)


#### class `UUIFrameworkColorBlock`  
`class UUIFrameworkColorBlock : public UUIFrameworkWidget`  
_L20-60_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Color Block UIFramework")`
- inherits: `UUIFrameworkWidget`
- L25 _public prototype_ `UUIFrameworkColorBlock();`
- L28 _public prototype_ `void SetColor(FLinearColor Tint);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L31 _public function_ `FLinearColor GetColor() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L37 _public prototype_ `void SetDesiredSize(FVector2f DesiredSize);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L40 _public function_ `FVector2f GetDesiredSize() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L45 _public prototype_ `virtual void LocalOnUMGWidgetCreated() override;`
- L49 _private prototype_ `void OnRep_Color();` — `UFUNCTION()`
- L52 _private prototype_ `void OnRep_DesiredSize();` — `UFUNCTION()`
- L56 _private member_ `FLinearColor Color;` — `UPROPERTY(ReplicatedUsing = OnRep_Color)`
- L59 _private member_ `FVector2f DesiredSize;` — `UPROPERTY(ReplicatedUsing = OnRep_DesiredSize)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFImageBlock.h` (Public)


#### struct `FUIFrameworkImageBlockData`  
`struct FUIFrameworkImageBlockData`  
_L20-45_
- reflection: `USTRUCT()`
- L26 _public member_ `FLinearColor Tint = FLinearColor::White;` — `UPROPERTY()` — Tinting applied to the image.
- L33 _public member_ `TSoftObjectPtr<UObject> ResourceObject;` — `UPROPERTY()` — The image to render for this brush, can be a UTexture2D or UMaterialInterface or an object implementing the AtlasedTextureInterface.
- L37 _public member_ `FVector2f DesiredSize = FVector2f::ZeroVector;` — `UPROPERTY()` — Size of the resource in Slate Units
- L41 _public member_ `TEnumAsByte<ESlateBrushTileType::Type> Tiling = ESlateBrushTileType::NoTile;` — `UPROPERTY()` — How to tile the image.
- L44 _public member_ `bool bUseTextureSize = false;` — `UPROPERTY()`

#### class `UUIFrameworkImageBlock`  
`class UUIFrameworkImageBlock : public UUIFrameworkWidget`  
_L51-117_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Image Block UIFramework")`
- inherits: `UUIFrameworkWidget`
- L56 _public prototype_ `UUIFrameworkImageBlock();`
- L59 _public prototype_ `virtual void SetMaterial(TSoftObjectPtr<UMaterialInterface> Material);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L62 _public function_ `TSoftObjectPtr<UObject> GeResourceObject() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L68 _public prototype_ `void SetTexture(TSoftObjectPtr<UTexture2D> Texture, bool bUseTextureSize);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L71 _public prototype_ `void SetTint(FLinearColor Tint);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L74 _public function_ `FLinearColor GetTint() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L80 _public prototype_ `void SetDesiredSize(FVector2f DesiredSize);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L83 _public function_ `FVector2f GetDesiredSize() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L89 _public prototype_ `void SetTiling(ESlateBrushTileType::Type OverflowPolicy);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L92 _public function_ `ESlateBrushTileType::Type GetTiling() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L97 _public prototype_ `virtual void LocalOnUMGWidgetCreated() override;`
- L98 _public prototype_ `virtual bool LocalIsReplicationReady() const override;`
- L101 _protected prototype_ `virtual UObject* ProcessResourceObject();`
- L105 _private prototype_ `void OnRep_Data();` — `UFUNCTION()`
- L110 _private member_ `FUIFrameworkImageBlockData Data;` — `UPROPERTY(ReplicatedUsing = OnRep_Data)` — Tinting applied to the image.
- L113 _private member_ `bool bWaitForResourceToBeLoaded = false;` — `UPROPERTY()`
- L115 _private member_ `TSharedPtr<FStreamableHandle> StreamingHandle;`
- L116 _private member_ `int32 StreamingCounter = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFOverlay.h` (Public)


#### struct `FUIFrameworkOverlaySlot`  
`struct FUIFrameworkOverlaySlot : public FUIFrameworkSlotBase`  
_L21-44_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSlotBase`
- L30 _public member_ `FMargin Padding = FMargin(0.f, 0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — Distance between that surrounds the widget inside the slot.
- L34 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — Horizontal alignment of the widget inside the slot.
- L38 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — Vertical alignment of the widget inside the slot.
- L43 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY()` — Index in the array the Slot is. The position in the array can change when replicated.

#### struct `FUIFrameworkOverlaySlotList`  
`struct FUIFrameworkOverlaySlotList : public FFastArraySerializer`  
_L51-78_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L55 _public prototype_ `FUIFrameworkOverlaySlotList() = default;`
- L56 _public function_ `FUIFrameworkOverlaySlotList(UUIFrameworkOverlay* InOwner) : Owner(InOwner)`
- L62 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L65 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);`
- L67 _public prototype_ `void AddEntry(FUIFrameworkOverlaySlot Entry);`
- L68 _public prototype_ `bool RemoveEntry(UUIFrameworkWidget* Widget);`
- L69 _public prototype_ `FUIFrameworkOverlaySlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L70 _public prototype_ `void ForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func);`
- L74 _private member_ `TArray<FUIFrameworkOverlaySlot> Slots;` — `UPROPERTY()`
- L77 _private member_ `TObjectPtr<UUIFrameworkOverlay> Owner;` — `UPROPERTY(NotReplicated, Transient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUIFrameworkOverlaySlotList> : public TStructOpsTypeTraitsBase2<FUIFrameworkOverlaySlotList>`  
_L82-85_
- inherits: `TStructOpsTypeTraitsBase2<FUIFrameworkOverlaySlotList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L84-84_

#### class `UUIFrameworkOverlay`  
`class UUIFrameworkOverlay : public UUIFrameworkWidget`  
_L92-118_
- reflection: `UCLASS(MinimalAPI, DisplayName="Overlay UIFramework")`
- inherits: `UUIFrameworkWidget`
- L99 _public prototype_ `UUIFrameworkOverlay();`
- L102 _public prototype_ `void AddWidget(FUIFrameworkOverlaySlot Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L105 _public prototype_ `void RemoveWidget(UUIFrameworkWidget* Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L107 _public prototype_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func) override;`
- L108 _public prototype_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget) override;`
- L109 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId) override;`
- L112 _private prototype_ `void AddEntry(FUIFrameworkOverlaySlot Entry);`
- L113 _private prototype_ `bool RemoveEntry(UUIFrameworkWidget* Widget);`
- L114 _private prototype_ `FUIFrameworkOverlaySlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L117 _private member_ `FUIFrameworkOverlaySlotList ReplicatedSlotList;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UIFRAMEWORK_API`
- L84 _enumerator_ `enum { WithNetDeltaSerializer = true };` (scope `TStructOpsTypeTraits::__anond6dadbcf0103`)

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFSafeZoneBox.h` (Public)


#### class `UUIFrameworkSafeZoneBox`  
`class UUIFrameworkSafeZoneBox : public UUIFrameworkWidget`  
_L18-41_
- reflection: `UCLASS(MinimalAPI, DisplayName = "SafeZone UIFramework")`
- inherits: `UUIFrameworkWidget`
- L23 _public prototype_ `UUIFrameworkSafeZoneBox();`
- L26 _public prototype_ `void SetContent(FUIFrameworkSlotBase Content);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L29 _public function_ `FUIFrameworkSlotBase GetContent() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L34 _public prototype_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func) override;`
- L35 _public prototype_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget) override;`
- L36 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId) override;`
- L40 _private member_ `FUIFrameworkSlotBase Slot;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UIFRAMEWORK_API`

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFStackBox.h` (Public)


#### struct `FUIFrameworkStackBoxSlot`  
`struct FUIFrameworkStackBoxSlot : public FUIFrameworkSlotBase`  
_L21-48_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUIFrameworkSlotBase`
- L30 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — Horizontal alignment of the widget inside the slot.
- L34 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Fill;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — Vertical alignment of the widget inside the slot.
- L38 _public member_ `FMargin Padding = FMargin(0.f, 0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — Distance between that surrounds the widget inside the slot.
- L42 _public member_ `FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Automatic);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — How much space this slot should occupy in the direction of the panel.
- L47 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY()` — Index in the array the Slot is. The position in the array can change when replicated.

#### struct `FUIFrameworkStackBoxSlotList`  
`struct FUIFrameworkStackBoxSlotList : public FFastArraySerializer`  
_L55-82_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L59 _public prototype_ `FUIFrameworkStackBoxSlotList() = default;`
- L60 _public function_ `FUIFrameworkStackBoxSlotList(UUIFrameworkStackBox* InOwner) : Owner(InOwner)`
- L66 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L69 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);`
- L71 _public prototype_ `void AddEntry(FUIFrameworkStackBoxSlot Entry);`
- L72 _public prototype_ `bool RemoveEntry(UUIFrameworkWidget* Widget);`
- L73 _public prototype_ `FUIFrameworkStackBoxSlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L74 _public prototype_ `void ForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func);`
- L78 _private member_ `TArray<FUIFrameworkStackBoxSlot> Slots;` — `UPROPERTY()`
- L81 _private member_ `TObjectPtr<UUIFrameworkStackBox> Owner;` — `UPROPERTY(NotReplicated, Transient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUIFrameworkStackBoxSlotList> : public TStructOpsTypeTraitsBase2<FUIFrameworkStackBoxSlotList>`  
_L86-89_
- inherits: `TStructOpsTypeTraitsBase2<FUIFrameworkStackBoxSlotList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L88-88_

#### class `UUIFrameworkStackBox`  
`class UUIFrameworkStackBox : public UUIFrameworkWidget`  
_L96-138_
- reflection: `UCLASS(MinimalAPI, DisplayName="StackBox UIFramework")`
- inherits: `UUIFrameworkWidget`
- L103 _public prototype_ `UUIFrameworkStackBox();`
- L108 _private member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Horizontal;` — `UPROPERTY(ReplicatedUsing="OnRep_Orientation", EditAnywhere, BlueprintReadWrite, Setter, Getter, Category = "UI Framework", meta = (AllowPrivateAccess = "true"))` — The orientation of the stack box.
- L112 _public prototype_ `void AddWidget(FUIFrameworkStackBoxSlot Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L115 _public prototype_ `void RemoveWidget(UUIFrameworkWidget* Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L118 _public prototype_ `EOrientation GetOrientation() const;` — Get the orientation of the stack box.
- L120 _public prototype_ `void SetOrientation(EOrientation Value);` — Set the orientation of the stack box. The existing elements will be rearranged.
- L122 _public prototype_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func) override;`
- L123 _public prototype_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget) override;`
- L124 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId) override;`
- L125 _public prototype_ `virtual void LocalOnUMGWidgetCreated() override;`
- L128 _private prototype_ `void AddEntry(FUIFrameworkStackBoxSlot Entry);`
- L129 _private prototype_ `bool RemoveEntry(UUIFrameworkWidget* Widget);`
- L130 _private prototype_ `FUIFrameworkStackBoxSlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L133 _private prototype_ `void OnRep_Orientation();` — `UFUNCTION()`
- L137 _private member_ `FUIFrameworkStackBoxSlotList ReplicatedSlotList;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UIFRAMEWORK_API`
- L88 _enumerator_ `enum { WithNetDeltaSerializer = true };` (scope `TStructOpsTypeTraits::__anona12c6d0c0103`)

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFTextBlock.h` (Public)


#### class `UUIFrameworkTextBase`  
`class UUIFrameworkTextBase : public UUIFrameworkWidget`  
_L22-182_
- reflection: `UCLASS(MinimalAPI, Abstract, HideDropDown)`
- inherits: `UUIFrameworkWidget`
- L27 _public prototype_ `UUIFrameworkTextBase();`
- L29 _public prototype_ `void SetMessage(FLocalizableMessage&& InMessage);`
- L32 _public function_ `FText GetText() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L38 _public prototype_ `void SetTextColor(FLinearColor TextColor);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L41 _public function_ `FLinearColor GetTextColor() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L47 _public prototype_ `void SetTextSize(float TextSize);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L50 _public function_ `float GetTextSize() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L56 _public prototype_ `void SetAutoWrap(bool InAutoWrap);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L59 _public function_ `bool GetAutoWrap() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L65 _public prototype_ `void SetWrapWidth(float InWrapWidth);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L68 _public function_ `float GetWrapWidth() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L74 _public prototype_ `void SetWrappingPolicy(ETextWrappingPolicy InWrappingPolicy);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L77 _public function_ `ETextWrappingPolicy GetWrappingPolicy() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L83 _public prototype_ `void SetJustification(ETextJustify::Type Justification);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L86 _public function_ `ETextJustify::Type GetJustification() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L92 _public prototype_ `void SetOverflowPolicy(ETextOverflowPolicy OverflowPolicy);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L95 _public function_ `ETextOverflowPolicy GetOverflowPolicy() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L100 _public prototype_ `virtual void LocalOnUMGWidgetCreated() override;`
- L104 _private prototype_ `void OnRep_Message();` — `UFUNCTION()`
- L107 _private prototype_ `void OnRep_TextColor();` — `UFUNCTION()`
- L110 _private prototype_ `void OnRep_TextSize();` — `UFUNCTION()`
- L113 _private prototype_ `void OnRep_AutoWrap();` — `UFUNCTION()`
- L116 _private prototype_ `void OnRep_WrapWidth();` — `UFUNCTION()`
- L119 _private prototype_ `void OnRep_WrappingPolicy();` — `UFUNCTION()`
- L122 _private prototype_ `void OnRep_Justification();` — `UFUNCTION()`
- L125 _private prototype_ `void OnRep_OverflowPolicy();` — `UFUNCTION()`
- L127 _private prototype_ `void SetText(const FLocalizableMessage& InMessage);`
- L130 _protected function_ `virtual void SetTextToWidget(const FText&)`
- L133 _protected function_ `virtual void SetTextColorToWidget(FLinearColor)`
- L136 _protected function_ `virtual void SetTextSizeToWidget(float)`
- L139 _protected function_ `virtual void SetAutoWrapToWidget(bool)`
- L142 _protected function_ `virtual void SetWrapWidthToWidget(float)`
- L145 _protected function_ `virtual void SetWrappingPolicyToWidget(ETextWrappingPolicy)`
- L148 _protected function_ `virtual void SetJustificationToWidget(ETextJustify::Type)`
- L151 _protected function_ `virtual void SetOverflowPolicyToWidget(ETextOverflowPolicy)`
- L157 _private member_ `FText Text;` — `UPROPERTY(Transient)`
- L160 _private member_ `FLocalizableMessage Message;` — `UPROPERTY(ReplicatedUsing = OnRep_Message)`
- L163 _private member_ `FLinearColor TextColor = FLinearColor::Black;` — `UPROPERTY(ReplicatedUsing = OnRep_TextColor)`
- L166 _private member_ `float TextSize = 24.0;` — `UPROPERTY(ReplicatedUsing = OnRep_TextSize)`
- L169 _private member_ `bool AutoWrap = false;` — `UPROPERTY(ReplicatedUsing = OnRep_AutoWrap)`
- L172 _private member_ `float WrapWidth = 0.0f;` — `UPROPERTY(ReplicatedUsing = OnRep_WrapWidth)`
- L175 _private member_ `ETextWrappingPolicy WrappingPolicy;` — `UPROPERTY(ReplicatedUsing = OnRep_WrappingPolicy)`
- L178 _private member_ `TEnumAsByte<ETextJustify::Type> Justification;` — `UPROPERTY(ReplicatedUsing = OnRep_Justification)`
- L181 _private member_ `ETextOverflowPolicy OverflowPolicy = ETextOverflowPolicy::Clip;` — `UPROPERTY(ReplicatedUsing = OnRep_OverflowPolicy)`

#### class `UUIFrameworkTextBlock`  
`class UUIFrameworkTextBlock : public UUIFrameworkTextBase`  
_L188-239_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Text Block UIFramework")`
- inherits: `UUIFrameworkTextBase`
- L193 _public prototype_ `UUIFrameworkTextBlock();`
- L196 _public prototype_ `void SetShadowOffset(FVector2f ShadowOffset);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L199 _public function_ `FVector2f GetShadowOffset() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L205 _public prototype_ `void SetShadowColor(FLinearColor ShadowColor);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L208 _public function_ `FLinearColor GetShadowColor() const` — `UFUNCTION(BlueprintCallable, Category = "UI Framework")`
- L213 _public prototype_ `virtual void LocalOnUMGWidgetCreated() override;`
- L217 _private prototype_ `void OnRep_ShadowOffset();` — `UFUNCTION()`
- L219 _private prototype_ `void OnRep_ShadowColor();` — `UFUNCTION()`
- L222 _protected prototype_ `virtual void SetTextToWidget(const FText&) override;`
- L223 _protected prototype_ `virtual void SetJustificationToWidget(ETextJustify::Type) override;`
- L224 _protected prototype_ `virtual void SetOverflowPolicyToWidget(ETextOverflowPolicy) override;`
- L225 _protected prototype_ `virtual void SetTextColorToWidget(FLinearColor) override;`
- L226 _protected prototype_ `virtual void SetTextSizeToWidget(float) override;`
- L227 _protected prototype_ `virtual void SetAutoWrapToWidget(bool) override;`
- L228 _protected prototype_ `virtual void SetWrapWidthToWidget(float) override;`
- L229 _protected prototype_ `virtual void SetWrappingPolicyToWidget(ETextWrappingPolicy) override;`
- L230 _protected prototype_ `virtual void SetShadowOffsetToWidget(FVector2f);`
- L231 _protected prototype_ `virtual void SetShadowColorToWidget(FLinearColor);`
- L235 _private member_ `FVector2f ShadowOffset = FVector2f::ZeroVector;` — `UPROPERTY(ReplicatedUsing = OnRep_ShadowOffset)`
- L238 _private member_ `FLinearColor ShadowColor = FLinearColor::Black;` — `UPROPERTY(ReplicatedUsing = OnRep_ShadowColor)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UIFRAMEWORK_API`
- L14 _namespace_ `namespace ETextJustify`

### `Plugins/Experimental/UIFramework/Source/Public/Widgets/UIFUserWidget.h` (Public)


#### struct `FUIFrameworkUserWidgetNamedSlot`  
`struct FUIFrameworkUserWidgetNamedSlot : public FUIFrameworkSlotBase`  
_L22-29_
- reflection: `USTRUCT()`
- inherits: `FUIFrameworkSlotBase`
- L28 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Framework")` — The name of the NamedSlot

#### struct `FUIFrameworkUserWidgetNamedSlotList`  
`struct FUIFrameworkUserWidgetNamedSlotList : public FFastArraySerializer`  
_L35-63_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L39 _public prototype_ `FUIFrameworkUserWidgetNamedSlotList() = default;`
- L40 _public function_ `FUIFrameworkUserWidgetNamedSlotList(UUIFrameworkUserWidget* InOwner) : Owner(InOwner)`
- L46 _public prototype_ `void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);`
- L49 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);`
- L51 _public prototype_ `void AuthorityAddEntry(FUIFrameworkUserWidgetNamedSlot Entry);`
- L52 _public prototype_ `bool AuthorityRemoveEntry(UUIFrameworkWidget* Widget);`
- L53 _public prototype_ `FUIFrameworkUserWidgetNamedSlot* FindEntry(FUIFrameworkWidgetId WidgetId);`
- L54 _public prototype_ `const FUIFrameworkUserWidgetNamedSlot* AuthorityFindEntry(FName SlotName) const;`
- L55 _public prototype_ `void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func);`
- L59 _private member_ `TArray<FUIFrameworkUserWidgetNamedSlot> Slots;` — `UPROPERTY()`
- L62 _private member_ `TObjectPtr<UUIFrameworkUserWidget> Owner;` — `UPROPERTY(NotReplicated, Transient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUIFrameworkUserWidgetNamedSlotList> : public TStructOpsTypeTraitsBase2<FUIFrameworkUserWidgetNamedSlotList>`  
_L67-70_
- inherits: `TStructOpsTypeTraitsBase2<FUIFrameworkUserWidgetNamedSlotList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L69-69_

#### class `UUIFrameworkUserWidget`  
`class UUIFrameworkUserWidget : public UUIFrameworkWidget`  
_L76-103_
- reflection: `UCLASS(MinimalAPI, DisplayName = "UserWidget UIFramework")`
- inherits: `UUIFrameworkWidget`
- L81 _public prototype_ `UUIFrameworkUserWidget();`
- L85 _public prototype_ `void SetWidgetClass(TSoftClassPtr<UWidget> Value);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L88 _public prototype_ `void SetNamedSlot(FName SlotName, UUIFrameworkWidget* Widget);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L91 _public prototype_ `UUIFrameworkWidget* GetNamedSlot(FName SlotName) const;` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "UI Framework")`
- L94 _public prototype_ `virtual bool LocalIsReplicationReady() const override;`
- L96 _public prototype_ `virtual void AuthorityForEachChildren(const TFunctionRef<void(UUIFrameworkWidget*)>& Func) override;`
- L97 _public prototype_ `virtual void AuthorityRemoveChild(UUIFrameworkWidget* Widget) override;`
- L98 _public prototype_ `virtual void LocalAddChild(FUIFrameworkWidgetId ChildId) override;`
- L102 _private member_ `FUIFrameworkUserWidgetNamedSlotList ReplicatedNamedSlotList;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UIFRAMEWORK_API`
- L69 _enumerator_ `enum { WithNetDeltaSerializer = true };` (scope `TStructOpsTypeTraits::__anon88376bb00103`)
