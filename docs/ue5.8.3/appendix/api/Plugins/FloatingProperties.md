# Plugins / FloatingProperties

- module root: `Plugins/Experimental/FloatingProperties/Source/FloatingProperties`
- headers: 21; symbols: 304
- symbol kinds: class=20, delegate=4, enum=2, enumerator=5, function=23, member=73, namespace=2, prototype=168, struct=7
- PrivateDependencyModuleNames: AppFramework, CoreUObject, EditorFramework, Engine, InputCore, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, DeveloperSettings

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Data/FloatingPropertiesPropertyNode.h` (Private)


#### enum `EFloatingPropertiesUpdateResult`  
`enum class EFloatingPropertiesUpdateResult : uint8`  
_L12-17_
- L14 _public enumerator_ `Failed = 0`
- L15 _public enumerator_ `AlreadyUpToDate`
- L16 _public enumerator_ `Updated`

#### class `FFloatingPropertiesPropertyNode`  
`class FFloatingPropertiesPropertyNode : public TSharedFromThis<FFloatingPropertiesPropertyNode>`  
_L24-119_
- inherits: `TSharedFromThis<FFloatingPropertiesPropertyNode>`
- L27 _public prototype_ `FFloatingPropertiesPropertyNode(FloatingPropertiesPropertyNodeContainer* InLinkedList, TSharedRef<SFloatingPropertiesPropertyWidget> InPropertyWidget, int32 InIndex);`
- L30 _public function_ `bool operator==(const FFloatingPropertiesPropertyNode& InOther) const`
- L35 _public prototype_ `bool HasParent() const;`
- L37 _public prototype_ `bool HasParent(TSharedRef<FFloatingPropertiesPropertyNode> InParent) const;`
- L39 _public prototype_ `TSharedPtr<FFloatingPropertiesPropertyNode> GetParent() const;`
- L41 _public prototype_ `bool HasChild() const;`
- L43 _public prototype_ `bool HasChild(TSharedRef<FFloatingPropertiesPropertyNode> InChild) const;`
- L45 _public prototype_ `TSharedPtr<FFloatingPropertiesPropertyNode> GetChild() const;`
- L47 _public prototype_ `bool HasSibling(TSharedRef<FFloatingPropertiesPropertyNode> InSibling) const;`
- L50 _public prototype_ `void SetParent(TSharedPtr<FFloatingPropertiesPropertyNode> InParent);` — Add a parent relationship.
- L53 _public prototype_ `void SetChild(TSharedRef<FFloatingPropertiesPropertyNode> InChild);` — Add child  relationship.
- L56 _public prototype_ `void InsertAfter(TSharedRef<FFloatingPropertiesPropertyNode> InMiddle);` — Insert between this parent and its child.
- L59 _public prototype_ `TSharedPtr<FFloatingPropertiesPropertyNode> RemoveParent();` — Remove parent and return it.
- L62 _public prototype_ `TSharedPtr<FFloatingPropertiesPropertyNode> RemoveChild();` — Remove child and return it.
- L64 _public prototype_ `void RemoveFromStack();`
- L66 _public prototype_ `TSharedRef<FFloatingPropertiesPropertyNode> GetStackRootNode() const;`
- L68 _public prototype_ `TSharedRef<FFloatingPropertiesPropertyNode> GetStackLeafMostNode() const;`
- L70 _public prototype_ `const FFloatingPropertiesClassPropertyAnchor& GetPropertyAnchor() const;`
- L72 _public prototype_ `const FFloatingPropertiesClassPropertyPosition& GetPropertyPosition() const;`
- L74 _public prototype_ `TSharedRef<SFloatingPropertiesPropertyWidget> GetPropertyWidget() const;`
- L77 _public prototype_ `EFloatingPropertiesUpdateResult UpdatePropertyNodePosition();` — Returns true if the node was able to update its position or if it already had a valid one.
- L80 _public prototype_ `EFloatingPropertiesUpdateResult UpdateStackPositions(bool bInInvalidate);` — Returns true if all nodes in the stack were able to update their positions.
- L82 _public prototype_ `void InvalidateCachedPosition();`
- L84 _public prototype_ `const FVector2f& GetCachedPosition() const;`
- L86 _public prototype_ `void SetPropertyPositionDirect(const FFloatingPropertiesClassPropertyPosition& InPropertyPosition);`
- L88 _public prototype_ `void SetPropertyPosition(const FVector2f& InDraggableArea, const FVector2f& InPosition);`
- L90 _public prototype_ `TArray<TSharedRef<FFloatingPropertiesPropertyNode>> GetNodeStack() const;`
- L92 _public prototype_ `FVector2f GetStackSize() const;`
- L95 _protected prototype_ `static FVector2f CalculateAnchorMultiplier(const FFloatingPropertiesClassPropertyPosition& InPropertyPosition);`
- L97 _protected prototype_ `static FFloatingPropertiesClassPropertyPosition CalculatePropertyPosition(const FVector2f& InDraggableArea, const FVector2f& InStackSize, const FVector2f& InPosition);`
- L100 _protected member_ `FloatingPropertiesPropertyNodeContainer* LinkedList;`
- L102 _protected member_ `int32 MyIndex;`
- L104 _protected member_ `int32 ParentNodeIndex;`
- L106 _protected member_ `int32 ChildNodeIndex;`
- L108 _protected member_ `TSharedRef<SFloatingPropertiesPropertyWidget> PropertyWidget;`
- L110 _protected member_ `FFloatingPropertiesClassPropertyAnchor PropertyAnchor;`
- L112 _protected member_ `FFloatingPropertiesClassPropertyPosition PropertyPosition;`
- L114 _protected member_ `mutable FVector2f CachedPosition;`
- L116 _protected member_ `mutable bool bValidPosition;`
- L118 _protected prototype_ `void SetCachedPosition(const FVector2f& InPosition);`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace FloatingProperties` (scope `UE`)
- L21 _prototype_ `EFloatingPropertiesUpdateResult CombineUpdateResult(EFloatingPropertiesUpdateResult InCurrentResult, EFloatingPropertiesUpdateResult InNewResult);` (scope `UE::FloatingProperties`)

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Data/FloatingPropertiesPropertyNodeContainer.h` (Private)


#### class `FloatingPropertiesPropertyNodeContainer`  
`class FloatingPropertiesPropertyNodeContainer`  
_L17-44_
- L20 _public prototype_ `FloatingPropertiesPropertyNodeContainer(TSharedRef<SFloatingPropertiesViewportWidget> InViewportWidget);`
- L22 _public function_ `TConstArrayView<TSharedRef<FFloatingPropertiesPropertyNode>> GetNodes() const`
- L24 _public prototype_ `void Reserve(int32 InAmount);`
- L26 _public prototype_ `TSharedRef<FFloatingPropertiesPropertyNode> AddWidget(TSharedRef<SFloatingPropertiesPropertyWidget> InWidget);`
- L28 _public prototype_ `TSharedPtr<FFloatingPropertiesPropertyNode> FindNodeForWidget(TSharedRef<SFloatingPropertiesPropertyWidget> InWidget) const;`
- L30 _public prototype_ `void Empty();`
- L32 _public prototype_ `void InvalidateAllPositions() const;`
- L34 _public prototype_ `EFloatingPropertiesUpdateResult EnsureCachedPositions() const;`
- L36 _public prototype_ `FVector2f GetDraggableArea() const;`
- L39 _protected member_ `TWeakPtr<SFloatingPropertiesViewportWidget> ContainerWeak;`
- L41 _protected member_ `TArray<TSharedRef<FFloatingPropertiesPropertyNode>> PropertyNodes;`
- L43 _protected member_ `TMap<TWeakPtr<SFloatingPropertiesPropertyWidget>, int32> WidgetToNode;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Data/FloatingPropertiesSnapMetrics.h` (Private)


#### enum `EFloatingPropertiesSnapType`  
`enum class EFloatingPropertiesSnapType`  
_L10-14_
- L12 _public enumerator_ `AttachAsParent`
- L13 _public enumerator_ `AttachAsChild`

#### struct `FFloatingPropertiesSnapMetrics`  
`struct FFloatingPropertiesSnapMetrics`  
_L16-35_
- L18 _public member_ `static constexpr int32 TopLeft = 0;`
- L19 _public member_ `static constexpr int32 BottomLeft = 1;`
- L20 _public member_ `static constexpr float SnapDistance = 10.f;`
- L21 _public member_ `static constexpr float SnapDistanceSq = SnapDistance * SnapDistance;`
- L22 _public member_ `static constexpr float SnapBreakDistanceSq = SnapDistanceSq * 2.f;`
- L24 _public prototype_ `static FFloatingPropertiesSnapMetrics Make(TSharedRef<FFloatingPropertiesPropertyNode> InNode, const FVector2f& InSnapPosition, EFloatingPropertiesSnapType InAttachType);`
- L27 _public prototype_ `static FVector2f GetSnapPosition(TSharedRef<FFloatingPropertiesPropertyNode> InNode, EFloatingPropertiesSnapType InAttachType);`
- L29 _public prototype_ `static void SnapToDraggableArea(const FVector2f& InDraggableArea, FVector2f& InOutPosition);`
- L31 _public member_ `TSharedRef<FFloatingPropertiesPropertyNode> Node;`
- L32 _public member_ `FVector2f Position;`
- L33 _public member_ `float DistanceSq;`
- L34 _public member_ `EFloatingPropertiesSnapType AttachType;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/FloatingPropertiesCommands.h` (Private)


#### class `FFloatingPropertiesCommands`  
`class FFloatingPropertiesCommands : public TCommands<FFloatingPropertiesCommands>`  
_L7-17_
- inherits: `TCommands<FFloatingPropertiesCommands>`
- L10 _public prototype_ `FFloatingPropertiesCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> ToggleEnabled;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/LevelEditor/FloatingPropertiesLevelEditorDataProvider.h` (Private)


#### class `FFloatingPropertiesLevelEditorDataProvider`  
`class FFloatingPropertiesLevelEditorDataProvider : public FFloatingPropertiesToolkitHostDataProvider`  
_L14-29_
- inherits: `FFloatingPropertiesToolkitHostDataProvider`
- L17 _public prototype_ `FFloatingPropertiesLevelEditorDataProvider(TSharedRef<ILevelEditor> InLevelEditor);`
- L18 _public prototype_ `virtual ~FFloatingPropertiesLevelEditorDataProvider() = default;`
- L21 _public prototype_ `virtual TArray<TSharedRef<IFloatingPropertiesWidgetContainer>> GetWidgetContainers() override;`
- L22 _public prototype_ `virtual bool IsWidgetVisibleInContainer(TSharedRef<IFloatingPropertiesWidgetContainer> InContainer) const override;`
- L26 _protected member_ `TMap<TWeakPtr<SLevelViewport>, TSharedRef<FFloatingPropertiesLevelEditorWidgetContainer>> CachedContainers;`
- L28 _protected prototype_ `void ClearExpiredViewports();`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/LevelEditor/FloatingPropertiesLevelEditorWidgetContainer.h` (Private)


#### class `FFloatingPropertiesLevelEditorWidgetContainer`  
`class FFloatingPropertiesLevelEditorWidgetContainer : public IFloatingPropertiesWidgetContainer`  
_L10-28_
- inherits: `IFloatingPropertiesWidgetContainer`
- L13 _public prototype_ `FFloatingPropertiesLevelEditorWidgetContainer(TSharedRef<SLevelViewport> InLevelViewport);`
- L14 _public prototype_ `virtual ~FFloatingPropertiesLevelEditorWidgetContainer();`
- L17 _public prototype_ `virtual TSharedPtr<SFloatingPropertiesViewportWidget> GetWidget() const override;`
- L18 _public prototype_ `virtual bool SetWidget(TSharedRef<SFloatingPropertiesViewportWidget> InWidget) override;`
- L19 _public prototype_ `virtual bool RemoveWidget() override;`
- L20 _public prototype_ `virtual bool IsValid() const override;`
- L23 _public prototype_ `TSharedPtr<SLevelViewport> GetLevelViewport() const;`
- L26 _protected member_ `TWeakPtr<SLevelViewport> LevelViewportWeak;`
- L27 _protected member_ `TSharedPtr<SFloatingPropertiesViewportWidget> Widget;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/LevelEditor/FloatingPropertiesLevelEditorWidgetController.h` (Private)


#### class `FFloatingPropertiesLevelEditorWidgetController`  
`class FFloatingPropertiesLevelEditorWidgetController : public FFloatingPropertiesWidgetController`  
_L10-34_
- inherits: `FFloatingPropertiesWidgetController`
- L13 _public prototype_ `static void StaticInit();`
- L15 _public prototype_ `FFloatingPropertiesLevelEditorWidgetController(TSharedRef<ILevelEditor> InLevelEditor);`
- L16 _public prototype_ `virtual ~FFloatingPropertiesLevelEditorWidgetController();`
- L19 _public prototype_ `virtual void Init() override;`
- L23 _protected prototype_ `static void RegisterLevelViewportMenuExtensions();`
- L25 _protected prototype_ `static void RegisterLevelEditorCommands();`
- L27 _protected member_ `FTSTicker::FDelegateHandle NextTickTimer;`
- L29 _protected prototype_ `void RegisterLevelViewportClientsChanged();`
- L31 _protected prototype_ `void UnregisterLevelViewportClientsChanged();`
- L33 _protected prototype_ `void OnLevelViewportClientsChanged();`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/ToolkitHost/FloatingPropertiesToolkitHostDataProvider.h` (Private)


#### class `FFloatingPropertiesToolkitHostDataProvider`  
`class FFloatingPropertiesToolkitHostDataProvider : public IFloatingPropertiesDataProvider`  
_L10-24_
- inherits: `IFloatingPropertiesDataProvider`
- L13 _public prototype_ `FFloatingPropertiesToolkitHostDataProvider(TSharedRef<IToolkitHost> InToolkitHost);`
- L14 _public prototype_ `virtual ~FFloatingPropertiesToolkitHostDataProvider() = default;`
- L17 _public prototype_ `virtual USelection* GetActorSelection() const override;`
- L18 _public prototype_ `virtual USelection* GetComponentSelection() const override;`
- L19 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L23 _protected member_ `TWeakPtr<IToolkitHost> ToolkitHostWeak;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/CustomPropertyWidgets/SFloatingPropertiesColorPropertyEditor.h` (Private)


#### class `SFloatingPropertiesColorPropertyEditor`  
`class SFloatingPropertiesColorPropertyEditor : public SFloatingPropertiesColorPropertyEditorBase`  
_L7-24_
- inherits: `SFloatingPropertiesColorPropertyEditorBase`
- L10 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesColorPropertyEditor, SFloatingPropertiesColorPropertyEditorBase) SLATE_BEGIN_ARGS(SFloatingPropertiesColorPropertyEditor)`
- L13 _public prototype_ `SLATE_END_ARGS() static TSharedPtr<SWidget> CreateWidget(TSharedRef<IPropertyHandle> InPropertyHandle);`
- L17 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L21 _protected prototype_ `virtual FLinearColor GetColorValue(FProperty* InProperty, UObject* InObject) const override;`
- L22 _protected prototype_ `virtual void SetColorValue(FProperty* InProperty, UObject* InObject, const FLinearColor& InNewValue) override;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/CustomPropertyWidgets/SFloatingPropertiesColorPropertyEditorBase.h` (Private)


#### class `SFloatingPropertiesColorPropertyEditorBase`  
`class SFloatingPropertiesColorPropertyEditorBase : public SCompoundWidget`  
_L15-50_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesColorPropertyEditorBase, SCompoundWidget) SLATE_BEGIN_ARGS(SFloatingPropertiesColorPropertyEditorBase)`
- L23 _public prototype_ `virtual ~SFloatingPropertiesColorPropertyEditorBase() override = default;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L28 _protected member_ `TWeakPtr<IPropertyHandle> PropertyHandleWeak;`
- L29 _protected member_ `TSharedPtr<FScopedTransaction> Transaction;`
- L30 _protected member_ `TMap<TWeakObjectPtr<UObject>, FLinearColor> OriginalValues;`
- L31 _protected member_ `bool bColorPickerOpen;`
- L33 _protected prototype_ `virtual FLinearColor GetColorValue(FProperty* InProperty, UObject* InObject) const = 0;`
- L35 _protected prototype_ `virtual void SetColorValue(FProperty* InProperty, UObject* InObject, const FLinearColor& InNewValue) = 0;`
- L37 _protected prototype_ `virtual FLinearColor GetColorValue() const;`
- L39 _protected prototype_ `void SetColorValue(const FLinearColor& InNewValue);`
- L41 _protected prototype_ `void RestoreOriginalColors();`
- L43 _protected prototype_ `FReply OnClickColorBlock(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L45 _protected prototype_ `void OnColorPickedCommitted(FLinearColor InNewColor);`
- L47 _protected prototype_ `void OnColorPickerCancelled(FLinearColor InOldColor);`
- L49 _protected prototype_ `void OnColorPickerClosed(const TSharedRef<SWindow>& InClosedWindow);`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/CustomPropertyWidgets/SFloatingPropertiesLinearColorPropertyEditor.h` (Private)


#### class `SFloatingPropertiesLinearColorPropertyEditor`  
`class SFloatingPropertiesLinearColorPropertyEditor : public SFloatingPropertiesColorPropertyEditorBase`  
_L7-24_
- inherits: `SFloatingPropertiesColorPropertyEditorBase`
- L10 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesLinearColorPropertyEditor, SFloatingPropertiesColorPropertyEditorBase) SLATE_BEGIN_ARGS(SFloatingPropertiesLinearColorPropertyEditor)`
- L13 _public prototype_ `SLATE_END_ARGS() static TSharedPtr<SWidget> CreateWidget(TSharedRef<IPropertyHandle> InPropertyHandle);`
- L17 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L21 _protected prototype_ `virtual FLinearColor GetColorValue(FProperty* InProperty, UObject* InObject) const override;`
- L22 _protected prototype_ `virtual void SetColorValue(FProperty* InProperty, UObject* InObject, const FLinearColor& InNewValue) override;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/FloatingPropertiesDragOperation.h` (Private)


#### class `FFloatingPropertiesDragOperation`  
`class FFloatingPropertiesDragOperation : public FDragDropOperation`  
_L11-25_
- inherits: `FDragDropOperation`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FFloatingPropertiesDragOperation, FDragDropOperation) FFloatingPropertiesDragOperation(TSharedPtr<SFloatingPropertiesPropertyWidget> InPropertyWidget);`
- L19 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;`
- L22 _protected member_ `TWeakPtr<SFloatingPropertiesPropertyWidget> PropertyWidgetWeak;`
- L23 _protected member_ `FVector2f MouseStartPosition;`
- L24 _protected member_ `FVector2f MouseToWidgetDelta;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/SFloatingPropertiesDragButton.h` (Private)


#### class `SFloatingPropertiesDragButton`  
`class SFloatingPropertiesDragButton : public SButton`  
_L9-31_
- inherits: `SButton`
- L12 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesDragButton, SButton) SLATE_BEGIN_ARGS(SFloatingPropertiesDragButton)`
- L16 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() virtual ~SFloatingPropertiesDragButton() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SFloatingPropertiesPropertyWidget> InPropertyWidget);`
- L25 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _protected member_ `TWeakPtr<SFloatingPropertiesPropertyWidget> PropertyWidgetWeak;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/SFloatingPropertiesDragContainer.h` (Private)


#### class `SFloatingPropertiesDragContainer`  
`class SFloatingPropertiesDragContainer : public SCompoundWidget`  
_L9-30_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesDragContainer, SCompoundWidget) SLATE_BEGIN_ARGS(SFloatingPropertiesDragContainer)`
- L16 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() virtual ~SFloatingPropertiesDragContainer() override = default;`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SFloatingPropertiesPropertyWidget> InPropertyWidget);`
- L24 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _protected member_ `TWeakPtr<SFloatingPropertiesPropertyWidget> PropertyWidgetWeak;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/SFloatingPropertiesPropertyWidget.h` (Private)


#### class `SFloatingPropertiesPropertyWidget`  
`class SFloatingPropertiesPropertyWidget : public SCompoundWidget`  
_L17-86_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesPropertyWidget, SCompoundWidget) SLATE_BEGIN_ARGS(SFloatingPropertiesPropertyWidget)`
- L25 _public prototype_ `virtual ~SFloatingPropertiesPropertyWidget() override = default;`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SFloatingPropertiesViewportWidget> InViewportWidget, const FFloatingPropertiesPropertyTypes& InPropertyTypes);`
- L30 _public function_ `TSharedPtr<SFloatingPropertiesViewportWidget> GetViewportWidget() const`
- L32 _public function_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const`
- L34 _public function_ `const FFloatingPropertiesClassProperty& GetClassProperty() const`
- L36 _public prototype_ `float GetPropertyNameWidgetWidth() const;`
- L38 _public prototype_ `float GetPropertyValueWidgetWidth() const;`
- L40 _public function_ `void SetPropertyNameOverrideSize(FOptionalSize InSize)`
- L42 _public function_ `void SetPropertyValueOverrideSize(FOptionalSize InSize)`
- L44 _public prototype_ `FVector2f GetAbsolutePropertySize() const;`
- L46 _public prototype_ `void SaveConfig();`
- L49 _protected member_ `TWeakPtr<SFloatingPropertiesViewportWidget> ViewportWidgetWeak;`
- L51 _protected member_ `TWeakPtr<IPropertyHandle> PropertyHandleWeak;`
- L53 _protected member_ `TSharedPtr<SMenuAnchor> PropertyAnchor;`
- L55 _protected member_ `TSharedPtr<SWidget> PropertyNameWidget;`
- L57 _protected member_ `TSharedPtr<SWidget> PropertyValueWidget;`
- L59 _protected member_ `FFloatingPropertiesClassProperty ClassProperty;`
- L61 _protected member_ `FOptionalSize PropertyNameOverrideSize;`
- L63 _protected member_ `FOptionalSize PropertyValueOverrideSize;`
- L65 _protected prototype_ `FFloatingPropertiesClassProperties* GetSavedValues(bool bInEnsure) const;`
- L67 _protected function_ `FOptionalSize GetPropertyNameOverrideSize() const`
- L69 _protected function_ `FOptionalSize GetPropertyValueOverrideSize() const`
- L71 _protected prototype_ `void AddSavedValue();`
- L73 _protected prototype_ `void AddSavedValue(const FString& InValueName);`
- L75 _protected prototype_ `void ApplySavedValue(FString InValueName);`
- L77 _protected prototype_ `bool IsValueActive(FString InValueName) const;`
- L79 _protected prototype_ `bool CanSaveValue(FString InValue) const;`
- L81 _protected prototype_ `void RemoveAllValues();`
- L83 _protected prototype_ `FReply OnPropertyButtonClicked();`
- L85 _protected prototype_ `TSharedRef<SWidget> MakePropertyMenu();`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Private/Widgets/SFloatingPropertiesViewportWidget.h` (Private)


#### class `SFloatingPropertiesViewportWidget`  
`class SFloatingPropertiesViewportWidget : public SCompoundWidget`  
_L19-76_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_DECLARE_WIDGET(SFloatingPropertiesViewportWidget, SCompoundWidget) SLATE_BEGIN_ARGS(SFloatingPropertiesViewportWidget)`
- L26 _public prototype_ `SLATE_EVENT(FIsVisibleDelegate, IsVisible) SLATE_END_ARGS() virtual ~SFloatingPropertiesViewportWidget() override = default;`
- L31 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L37 _public prototype_ `void BuildWidget(AActor* InSelectedActor, const FFloatingPropertiesPropertyList& InActorProperties, UActorComponent* InSelectedComponent, const FFloatingPropertiesPropertyList& InComponentProperties);`
- L40 _public prototype_ `TSharedRef<SWidget> AsWidget();`
- L42 _public prototype_ `FVector2f GetDraggableArea() const;`
- L53 _public prototype_ `void OnPropertyDragUpdate(TSharedRef<SFloatingPropertiesPropertyWidget> InPropertyWidget, const FVector2f& InMouseToWidgetDelta, const FVector2f& InMouseStartPosition, const FVector2f& InMouseCurrentPosition);` — The bottom of the stack attaches to the top of the closest snap node if it's above the node. The top of the stack attaches to the bottom of the closest snap node if it's below the node. Attaching to the bottom of another stack is temporary. If the node continues to be dragged, after SnapBreakDistanceSq from the snapped-to node, it will break off the stack it attached to and continue to be dragged.
- L56 _public prototype_ `void OnPropertyDragComplete(TSharedRef<SFloatingPropertiesPropertyWidget> InPropertyWidget);`
- L59 _protected member_ `TSharedPtr<SCanvas> FieldContainer;`
- L61 _protected member_ `TSharedPtr<FloatingPropertiesPropertyNodeContainer> Properties;`
- L63 _protected member_ `mutable FIntPoint LastRenderSize;`
- L65 _protected member_ `mutable bool bInitialPositionsSet;`
- L67 _protected prototype_ `void Reset();`
- L69 _protected prototype_ `void CheckForViewportSizeChange(const FVector2f& InViewportSize) const;`
- L71 _protected prototype_ `bool EnsurePositions(bool bInInvalidate) const;`
- L73 _protected prototype_ `FVector2D GetNodeSize(TWeakPtr<SFloatingPropertiesPropertyWidget> InNodeWidgetWeak) const;`
- L75 _protected prototype_ `FVector2D GetNodePosition(TWeakPtr<FFloatingPropertiesPropertyNode> InNodeWeak) const;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Public/Data/FloatingPropertiesWidgetController.h` (Public)


#### struct `FFloatingPropertiesPropertyTypes`  
`struct FFloatingPropertiesPropertyTypes`  
_L22-33_
- L24 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L25 _public member_ `FProperty* Property;`
- L26 _public member_ `TSharedPtr<IDetailTreeNode> TreeNode;`
- L28 _public function_ `~FFloatingPropertiesPropertyTypes()`

#### struct `FFloatingPropertiesPropertyList`  
`struct FFloatingPropertiesPropertyList`  
_L35-45_
- L37 _public member_ `TSharedPtr<IPropertyRowGenerator> Generator;`
- L38 _public member_ `TArray<FFloatingPropertiesPropertyTypes> Properties;`
- L40 _public function_ `~FFloatingPropertiesPropertyList()`

#### class `FFloatingPropertiesWidgetController`  
`class FFloatingPropertiesWidgetController : public TSharedFromThis<FFloatingPropertiesWidgetController>`  
_L49-88_
- inherits: `TSharedFromThis<FFloatingPropertiesWidgetController>`
- L52 _public prototype_ `FFloatingPropertiesWidgetController(TSharedRef<IFloatingPropertiesDataProvider> InDataProvider);`
- L54 _public prototype_ `virtual ~FFloatingPropertiesWidgetController();`
- L56 _public prototype_ `virtual void Init();`
- L59 _protected member_ `TSharedPtr<IFloatingPropertiesDataProvider> DataProvider;`
- L61 _protected member_ `TWeakObjectPtr<AActor> SelectedActorWeak;`
- L63 _protected member_ `TWeakObjectPtr<UActorComponent> SelectedComponentWeak;`
- L65 _protected member_ `FFloatingPropertiesPropertyList ActorProperties;`
- L67 _protected member_ `FFloatingPropertiesPropertyList ComponentProperties;`
- L69 _protected prototype_ `TSharedRef<SFloatingPropertiesViewportWidget> CreateWidget(FIsVisibleDelegate InVisibilityCallback);`
- L71 _protected prototype_ `void UpdatePropertiesForObject(UObject* InObject, FFloatingPropertiesPropertyList& OutPropertyList);`
- L73 _protected prototype_ `void RebuildWidgets(const FFloatingPropertiesPropertyList& InActorProperties, const FFloatingPropertiesPropertyList& InComponentProperties);`
- L75 _protected prototype_ `void RemoveWidgets();`
- L77 _protected prototype_ `void OnViewportChange();`
- L79 _protected prototype_ `void RegisterSelectionChanged();`
- L81 _protected prototype_ `void UnregisterSelectionChanged();`
- L83 _protected prototype_ `void OnSelectionChange(const UTypedElementSelectionSet* InSelectionSet);`
- L85 _protected prototype_ `void OnSelectionChange();`
- L87 _protected prototype_ `void OnSelectionChange(UWorld* InWorld, USelection* InActorSelection, USelection* InComponentSelection);`

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsVisibleDelegate);`
- L47 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsVisibleDelegate);`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Public/Data/IFloatingPropertiesDataProvider.h` (Public)


#### class `IFloatingPropertiesDataProvider`  
`class IFloatingPropertiesDataProvider`  
_L13-26_
- L17 _public prototype_ `virtual TArray<TSharedRef<IFloatingPropertiesWidgetContainer>> GetWidgetContainers() = 0;` — Must provide consistent shared refs. Same container, same ref.
- L19 _public prototype_ `virtual USelection* GetActorSelection() const = 0;`
- L21 _public prototype_ `virtual USelection* GetComponentSelection() const = 0;`
- L23 _public prototype_ `virtual UWorld* GetWorld() const = 0;`
- L25 _public prototype_ `virtual bool IsWidgetVisibleInContainer(TSharedRef<IFloatingPropertiesWidgetContainer> InContainer) const = 0;`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Public/Data/IFloatingPropertiesWidgetContainer.h` (Public)


#### class `IFloatingPropertiesWidgetContainer`  
`class IFloatingPropertiesWidgetContainer`  
_L9-23_
- L13 _public function_ `virtual TSharedPtr<SFloatingPropertiesViewportWidget> GetWidget() const` — Returns the added widget.
- L16 _public prototype_ `virtual bool SetWidget(TSharedRef<SFloatingPropertiesViewportWidget> InWidget) = 0;` — Adds the widget to teh container, which should store it for later.
- L19 _public prototype_ `virtual bool RemoveWidget() = 0;` — Removes the added widget.
- L22 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the widget's container is still valid.

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Public/FloatingPropertiesModule.h` (Public)


#### class `FFloatingPropertiesModule`  
`class FFloatingPropertiesModule : public IModuleInterface`  
_L24-57_
- inherits: `IModuleInterface`
- desc: Floating Properties - Adds floating details panel properties on to the viewport.
- L27 _public prototype_ `static FFloatingPropertiesModule& Get();`
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FCreateStructPropertyValueWidgetDelegate, TSharedRef<IPropertyHandle>);`
- L36 _public prototype_ `void RegiserStructPropertyValueWidgetDelegate(UScriptStruct* InStruct, FCreateStructPropertyValueWidgetDelegate InDelegate);`
- L38 _public prototype_ `const FCreateStructPropertyValueWidgetDelegate* GetStructPropertyValueWidgetDelegate(UScriptStruct* InStruct) const;`
- L40 _public prototype_ `void UnregiserStructPropertyValueWidgetDelegate(UScriptStruct* InStruct);`
- L43 _protected member_ `TSharedPtr<FFloatingPropertiesLevelEditorWidgetController> LevelEditorWidgetController;`
- L44 _protected member_ `TMap<FName, FCreateStructPropertyValueWidgetDelegate> PropertyValueWidgetDelegates;`
- L46 _protected prototype_ `void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);`
- L48 _protected prototype_ `void CreateLevelEditorWidgetController(TSharedPtr<ILevelEditor> InLevelEditor);`
- L50 _protected prototype_ `void DestroyLevelEditorWidgetController();`
- L52 _protected prototype_ `void OnSettingsChanged(const UFloatingPropertiesSettings* InSettings, FName InSetting);`
- L54 _protected prototype_ `void AddDefaultStructPropertyValueWidgetDelegates();`
- L56 _protected prototype_ `void OnEnginePreExit();`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFloatingProperties, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFloatingProperties, Log, All);`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FCreateStructPropertyValueWidgetDelegate, TSharedRef<IPropertyHandle>);`

### `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Public/FloatingPropertiesSettings.h` (Public)


#### struct `FFloatingPropertiesClassProperty`  
`struct FFloatingPropertiesClassProperty`  
_L18-48_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `TSoftClassPtr<UObject> Class;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`
- L26 _public member_ `FString PropertyPath;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`
- L28 _public function_ `bool operator==(const FFloatingPropertiesClassProperty& InOther) const`
- L33 _public function_ `bool IsValid() const`
- L38 _public function_ `void Reset()`

#### struct `FFloatingPropertiesClassProperties`  
`struct FFloatingPropertiesClassProperties`  
_L51-57_
- reflection: `USTRUCT(BlueprintType)`
- L56 _public member_ `TMap<FString, FString> Properties;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`

#### struct `FFloatingPropertiesClassPropertyPosition`  
`struct FFloatingPropertiesClassPropertyPosition`  
_L61-77_
- reflection: `USTRUCT(BlueprintType)`
- desc: The Fill alignments are used as a "not set" value.
- L65 _public member_ `static const FFloatingPropertiesClassPropertyPosition DefaultStackPosition;`
- L68 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAnchor = EHorizontalAlignment::HAlign_Fill;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`
- L71 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAnchor = EVerticalAlignment::VAlign_Fill;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`
- L74 _public member_ `FIntPoint Offset = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`
- L76 _public prototype_ `bool OnDefaultStack() const;`

#### struct `FFloatingPropertiesClassPropertyAnchor`  
`struct FFloatingPropertiesClassPropertyAnchor`  
_L80-89_
- reflection: `USTRUCT(BlueprintType)`
- L85 _public member_ `FFloatingPropertiesClassProperty ParentProperty;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`
- L88 _public member_ `FFloatingPropertiesClassProperty ChildProperty;` — `UPROPERTY(EditAnywhere, Category = "Floating Properties")`

#### class `UFloatingPropertiesSettings`  
`class UFloatingPropertiesSettings : public UDeveloperSettings`  
_L92-119_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "Floating Properties"))`
- inherits: `UDeveloperSettings`
- L97 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFloatingPropertiesSettingsChanged, const UFloatingPropertiesSettings* , FName ) static FOnFloatingPropertiesSettingsChanged OnChange;`
- L100 _public prototype_ `static FString FindUniqueName(const FFloatingPropertiesClassProperties& InPropertyList, const FString& InDefault);`
- L102 _public prototype_ `UFloatingPropertiesSettings();`
- L105 _public member_ `bool bEnabled;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Floating Properties")`
- L108 _public member_ `TMap<FFloatingPropertiesClassProperty, FFloatingPropertiesClassProperties> SavedValues;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Floating Properties")`
- L111 _public member_ `TMap<FFloatingPropertiesClassProperty, FFloatingPropertiesClassPropertyPosition> PropertyPositions;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Floating Properties")`
- L114 _public member_ `TMap<FFloatingPropertiesClassProperty, FFloatingPropertiesClassPropertyAnchor> PropertyAnchors;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Floating Properties")`
- L117 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L44 _function_ `friend uint32 GetTypeHash(const FFloatingPropertiesClassProperty& InClassProperty)`
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFloatingPropertiesSettingsChanged, const UFloatingPropertiesSettings* , FName ) static FOnFloatingPropertiesSettingsChanged OnChange;`
