# Developer / SlateReflector

- module root: `Source/Developer/SlateReflector`
- headers: 24; symbols: 809
- symbol kinds: class=31, delegate=13, enum=5, enumerator=15, function=55, macro=2, member=239, namespace=7, prototype=420, struct=16, typedef=6
- DynamicallyLoadedModuleNames: Messaging, SessionServices
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, CoreUObject, DesktopPlatform, ImageCore, ImageWrapper, InputCore, Json, MessageLog, PropertyEditor, Slate, SlateCore, ToolWidgets, UMG, UnrealEd
- PrivateIncludePathModuleNames: Messaging, MessagingCommon, SessionServices
- PublicDependencyModuleNames: Core

### `Source/Developer/SlateReflector/Private/InputEventVisualizer.h` (Private)


#### class `FInputEventVisualizer`  
`class FInputEventVisualizer : public FSlateDebugging::IWidgetInputRoutingEvent`  
_L20-85_
- inherits: `FSlateDebugging::IWidgetInputRoutingEvent`
- L23 _public prototype_ `FInputEventVisualizer();`
- L24 _public prototype_ `virtual ~FInputEventVisualizer();`
- L26 _public prototype_ `void PopulateMenu(FMenuBuilder& MenuBuilder);`
- L29 _public prototype_ `virtual void OnProcessInput(ESlateDebuggingInputEvent InputEventType, const FInputEvent& Event) override;`
- L30 _public function_ `virtual void OnPreProcessInput(ESlateDebuggingInputEvent InputEventType, const TCHAR* InputPrecessorName, bool bHandled) override`
- L31 _public function_ `virtual void OnRouteInput(ESlateDebuggingInputEvent InputEventType, const FName& RoutedType) override`
- L32 _public function_ `virtual void OnInputEvent(ESlateDebuggingInputEvent InputEventType, const FReply& InReply, const TSharedPtr<SWidget>& HandlerWidget) override`
- L33 _public function_ `virtual void OnInputRouted(ESlateDebuggingInputEvent InputEventType) override`
- L34 _public function_ `virtual void OnInputProcessed(ESlateDebuggingInputEvent InputEventType) override`
- L38 _private prototype_ `void HandlePaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, FSlateWindowElementList& InOutDrawElements, int32& InOutLayerId);`
- L40 _private prototype_ `void HandleDemoModeEnabledChanged(IConsoleVariable* CVar);`
- L41 _private prototype_ `void HandleBeginFrameCallback();`
- L42 _private prototype_ `void HandleEndWindow(const FSlateWindowElementList& ElementList);`
- L44 _private prototype_ `void UpdateNotificationItem();`
- L45 _private prototype_ `void UpdateKeyText();`
- L47 _private prototype_ `void HandleToggleMouseEvent();`
- L48 _private prototype_ `ECheckBoxState HandleGetMouseEventCheckState() const;`
- L49 _private prototype_ `void HandleToggleKeyEvent();`
- L50 _private prototype_ `ECheckBoxState HandleGetKeyEventCheckState() const;`
- L71 _private member_ `bool bShowMouseEvent;`
- L72 _private member_ `float ClickFadeTime;`
- L73 _private member_ `TArray<FMouseEventInfo> MouseEvents;`
- L74 _private member_ `TMap<FKey, FLinearColor> MouseKeyColorsMap;`
- L76 _private member_ `bool bShowKeyEvent;`
- L77 _private member_ `float KeyFadeTime;`
- L78 _private member_ `double KeyEventTime;`
- L79 _private member_ `int32 MaxNumberOfKeys;`
- L80 _private member_ `TArray<FKeyEventInfo> KeyEvents;`
- L81 _private member_ `TWeakPtr<SNotificationItem> WeakOwningNotification;`
- L83 _private member_ `FAutoConsoleVariableRef DemoModeMouseConsoleVariable;`
- L84 _private member_ `FAutoConsoleVariableRef DemoModeKeyConsoleVariable;`

#### struct `FInputEventVisualizer::FMouseEventInfo`  
`struct FMouseEventInfo`  
_L53-59_
- L55 _public member_ `FKey Key;`
- L56 _public member_ `double EventTime;`
- L57 _public member_ `FVector2f CursorPingPosition;`
- L58 _public member_ `FLinearColor PingColor;`

#### struct `FInputEventVisualizer::FKeyEventInfo`  
`struct FKeyEventInfo`  
_L61-69_
- L63 _public member_ `FKey Key;`
- L64 _public member_ `FModifierKeysState KeysState;`
- L65 _public prototype_ `FKeyEventInfo() = default;`
- L66 _public function_ `FKeyEventInfo(const FKey& InKey, const FModifierKeysState& InKeysState) : Key(InKey), KeysState(InKeysState)`

#### class `FInputEventVisualizer`  
`class FInputEventVisualizer`  
_L91-93_
- L23 _public prototype_ `FInputEventVisualizer();`
- L24 _public prototype_ `virtual ~FInputEventVisualizer();`
- L26 _public prototype_ `void PopulateMenu(FMenuBuilder& MenuBuilder);`
- L29 _public prototype_ `virtual void OnProcessInput(ESlateDebuggingInputEvent InputEventType, const FInputEvent& Event) override;`
- L30 _public function_ `virtual void OnPreProcessInput(ESlateDebuggingInputEvent InputEventType, const TCHAR* InputPrecessorName, bool bHandled) override`
- L31 _public function_ `virtual void OnRouteInput(ESlateDebuggingInputEvent InputEventType, const FName& RoutedType) override`
- L32 _public function_ `virtual void OnInputEvent(ESlateDebuggingInputEvent InputEventType, const FReply& InReply, const TSharedPtr<SWidget>& HandlerWidget) override`
- L33 _public function_ `virtual void OnInputRouted(ESlateDebuggingInputEvent InputEventType) override`
- L34 _public function_ `virtual void OnInputProcessed(ESlateDebuggingInputEvent InputEventType) override`
- L38 _private prototype_ `void HandlePaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, FSlateWindowElementList& InOutDrawElements, int32& InOutLayerId);`
- L40 _private prototype_ `void HandleDemoModeEnabledChanged(IConsoleVariable* CVar);`
- L41 _private prototype_ `void HandleBeginFrameCallback();`
- L42 _private prototype_ `void HandleEndWindow(const FSlateWindowElementList& ElementList);`
- L44 _private prototype_ `void UpdateNotificationItem();`
- L45 _private prototype_ `void UpdateKeyText();`
- L47 _private prototype_ `void HandleToggleMouseEvent();`
- L48 _private prototype_ `ECheckBoxState HandleGetMouseEventCheckState() const;`
- L49 _private prototype_ `void HandleToggleKeyEvent();`
- L50 _private prototype_ `ECheckBoxState HandleGetKeyEventCheckState() const;`
- L71 _private member_ `bool bShowMouseEvent;`
- L72 _private member_ `float ClickFadeTime;`
- L73 _private member_ `TArray<FMouseEventInfo> MouseEvents;`
- L74 _private member_ `TMap<FKey, FLinearColor> MouseKeyColorsMap;`
- L76 _private member_ `bool bShowKeyEvent;`
- L77 _private member_ `float KeyFadeTime;`
- L78 _private member_ `double KeyEventTime;`
- L79 _private member_ `int32 MaxNumberOfKeys;`
- L80 _private member_ `TArray<FKeyEventInfo> KeyEvents;`
- L81 _private member_ `TWeakPtr<SNotificationItem> WeakOwningNotification;`
- L83 _private member_ `FAutoConsoleVariableRef DemoModeMouseConsoleVariable;`
- L84 _private member_ `FAutoConsoleVariableRef DemoModeKeyConsoleVariable;`

### `Source/Developer/SlateReflector/Private/Models/NavigationSimulationNode.h` (Private)


#### enum `ENavigationSimulationNodeType`  
`enum class ENavigationSimulationNodeType : uint8`  
_L19-23_
- L21 _public enumerator_ `Live`
- L22 _public enumerator_ `Snapshot`

#### struct `FNavigationSimulationWidgetInfo`  
`struct FNavigationSimulationWidgetInfo`  
_L25-43_
- L28 _public typedef_ `using TPointerAsInt = uint64;` — Should be PTRINT but if the platform that produce the file is 64bits and the reader is not then we could have a issue
- L30 _public prototype_ `FNavigationSimulationWidgetInfo() = default;`
- L31 _public prototype_ `explicit FNavigationSimulationWidgetInfo(const TSharedPtr<const SWidget>& Widget);`
- L32 _public prototype_ `explicit FNavigationSimulationWidgetInfo(const FWidgetPath& WidgetPath);`
- L35 _public function_ `bool IsWidgetExplicitlyNull() const` — Is the widget set to null.
- L37 _public member_ `TPointerAsInt WidgetPtr;`
- L38 _public member_ `TWeakPtr<const SWidget> WidgetLive;`
- L40 _public member_ `FText WidgetTypeAndShortName;`
- L41 _public member_ `FGeometry WidgetGeometry;`
- L42 _public member_ `bool bHasGeometry;`

#### struct `FNavigationSimulationWidgetNodeItem`  
`struct FNavigationSimulationWidgetNodeItem`  
_L45-65_
- L47 _public prototype_ `FNavigationSimulationWidgetNodeItem() = default;`
- L48 _public prototype_ `explicit FNavigationSimulationWidgetNodeItem(const FSlateNavigationEventSimulator::FSimulationResult& Result);`
- L50 _public member_ `EUINavigation NavigationType;`
- L51 _public member_ `FNavigationSimulationWidgetInfo Destination;`
- L52 _public member_ `FNavigationSimulationWidgetInfo ReplyEventHandler;`
- L53 _public member_ `FNavigationSimulationWidgetInfo ReplyFocusRecipient;`
- L54 _public member_ `EUINavigationRule ReplyBoundaryRule;`
- L55 _public member_ `FSlateNavigationEventSimulator::ERoutedReason RoutedReason;`
- L56 _public member_ `FNavigationSimulationWidgetInfo WidgetThatShouldReceivedFocus;`
- L57 _public member_ `FNavigationSimulationWidgetInfo FocusedWidget;`
- L58 _public member_ `uint8 bIsDynamic : 1;`
- L59 _public member_ `uint8 bAlwaysHandleNavigationAttempt : 1;`
- L60 _public member_ `uint8 bCanFindWidgetForSetFocus : 1;`
- L61 _public member_ `uint8 bRoutedHandlerHasNavigationMeta : 1;`
- L62 _public member_ `uint8 bHandledByViewport : 1;`
- L64 _public prototype_ `void ResetLiveWidget();`

#### struct `FNavigationSimulationWidgetNode`  
`struct FNavigationSimulationWidgetNode`  
_L67-81_
- L69 _public prototype_ `FNavigationSimulationWidgetNode() = default;`
- L70 _public prototype_ `explicit FNavigationSimulationWidgetNode(ENavigationSimulationNodeType NodeType, const FWidgetPath& InNavigationSource);`
- L72 _public member_ `FNavigationSimulationWidgetInfo NavigationSource;`
- L73 _public member_ `TArray<FNavigationSimulationWidgetNodeItem, TInlineAllocator<4>> Simulations;`
- L74 _public member_ `ENavigationSimulationNodeType NodeType;`
- L77 _public prototype_ `static TSharedRef<FJsonValue> ToJson(const FNavigationSimulationWidgetNode& Node);` — Save this node data as a JSON object
- L80 _public prototype_ `static FNavigationSimulationWidgetNodePtr FromJson(const TSharedRef<FJsonValue>& RootJsonValue);` — Populate this node data from a JSON object

#### struct `FNavigationSimulationNodeUtils`  
`struct FNavigationSimulationNodeUtils`  
_L84-93_
- L86 _public prototype_ `static TArray<FNavigationSimulationWidgetNodePtr> BuildNavigationSimulationNodeListForLive(const TArray<FSlateNavigationEventSimulator::FSimulationResult>& SimulationResult);`
- L87 _public prototype_ `static TArray<FNavigationSimulationWidgetNodePtr> BuildNavigationSimulationNodeListForSnapshot(const TArray<FSlateNavigationEventSimulator::FSimulationResult>& SimulationResult);`
- L89 _public prototype_ `static TArray<FNavigationSimulationWidgetNodePtr> FindReflectorNodes(const TArray<FNavigationSimulationWidgetNodePtr>& Nodes, const TArray<TSharedRef<FWidgetReflectorNodeBase>>& ToFind);`
- L91 _public prototype_ `static int32 IndexOfLiveWidget(const TArray<FNavigationSimulationWidgetNodePtr>& Nodes, const TSharedPtr<const SWidget>& WidgetToFind);`
- L92 _public prototype_ `static int32 IndexOfSnapshotWidget(const TArray<FNavigationSimulationWidgetNodePtr>& Nodes, FNavigationSimulationWidgetInfo::TPointerAsInt WidgetToFind);`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FNavigationSimulationWidgetNodePtr = TSharedPtr<FNavigationSimulationWidgetNode>;`

### `Source/Developer/SlateReflector/Private/Models/WidgetReflectorNode.h` (Private)


#### enum `EWidgetReflectorNodeType`  
`enum class EWidgetReflectorNodeType : uint8`  
_L21-25_
- desc: Enum used as crude RTTI for the widget reflector node types
- L23 _public enumerator_ `Live`
- L24 _public enumerator_ `Snapshot`

#### struct `FWidgetHitTestInfo`  
`struct FWidgetHitTestInfo`  
_L30-34_
- desc: Cached information about whether a widget can be hit-tested
- L32 _public member_ `bool IsHitTestVisible = false;`
- L33 _public member_ `bool AreChildrenHitTestVisible = false;`

#### class `FWidgetReflectorNodeBase`  
`class FWidgetReflectorNodeBase`  
_L39-279_
- desc: A widget reflector node that contains the interface and basic data required by both live and snapshot nodes
- L42 _public typedef_ `using TPointerAsInt = uint64;` — We can't use PTRINT since the target may be 32bits and the json could be saved in 64bits
- L47 _public prototype_ `virtual ~FWidgetReflectorNodeBase() = default;` — Destructor
- L52 _public prototype_ `virtual EWidgetReflectorNodeType GetNodeType() const = 0;` — @return Get the enum entry corresponding to this type of widget reflector node (used as crude RTTI)
- L58 _public prototype_ `virtual TSharedPtr<SWidget> GetLiveWidget() const = 0;` — @note This function only works for ULiveWidgetReflectorNode instances @return The live widget that this node is referencing
- L63 _public prototype_ `virtual FText GetWidgetType() const = 0;` — @return The type string for the widget we were initialized from
- L68 _public prototype_ `virtual FText GetWidgetTypeAndShortName() const = 0;` — @return The type string for the widget we were initialized from
- L73 _public prototype_ `virtual FText GetWidgetVisibilityText() const = 0;` — @return The visibility string for the widget we were initialized from
- L78 _public prototype_ `virtual FText GetWidgetClippingText() const = 0;` — @return The clipping string for the widget we were initialized from
- L83 _public prototype_ `virtual int32 GetWidgetLayerId() const = 0;` — @return The LayerId the widget were painted from
- L84 _public prototype_ `virtual int32 GetWidgetLayerIdOut() const = 0;`
- L89 _public prototype_ `virtual bool GetWidgetFocusable() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports as Focusable
- L94 _public prototype_ `virtual bool GetWidgetVisible() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports is visible
- L99 _public prototype_ `virtual bool GetWidgetVisibilityInherited() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports is visible
- L104 _public prototype_ `virtual bool GetWidgetSupportsInvalidation() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports as supporting invalidation
- L109 _public prototype_ `virtual bool GetSupportsInvalidationRecursive() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports as recursively supporting invalidation
- L114 _public prototype_ `virtual bool GetWidgetNeedsTick() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports needs tick
- L119 _public prototype_ `virtual bool GetWidgetIsVolatile() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports is volatile
- L124 _public prototype_ `virtual bool GetWidgetIsVolatileIndirectly() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports is volatile indirectly
- L129 _public prototype_ `virtual bool GetWidgetHasActiveTimers() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports has active timers
- L134 _public prototype_ `virtual bool GetWidgetIsInvalidationRoot() const = 0;` — @return The bool indicating whether or not the widget we were initialized from reports is an Invalidation Root
- L139 _public prototype_ `virtual int32 GetWidgetAttributeCount() const = 0;` — @return the numbers of registered slate attributes on the widget we were initialized from
- L144 _public prototype_ `virtual int32 GetWidgetCollapsedAttributeCount() const = 0;` — @return the numbers of registered slate attributes marked as "update when collapsed" on the widget we were initialized from
- L151 _public prototype_ `virtual FText GetWidgetReadableLocation() const = 0;` — The human readable location for widgets that are defined in C++ is the file and line number The human readable location for widgets that are defined in UMG is the asset name @return The fully human readable location for the widget we were initialized from
- L156 _public prototype_ `virtual FString GetWidgetFile() const = 0;` — @return The name of the file that the widget we were initialized from was created from (for C++ widgets)
- L161 _public prototype_ `virtual int32 GetWidgetLineNumber() const = 0;` — @return The line number of the file that the widget we were initialized from was created from (for C++ widgets)
- L166 _public prototype_ `virtual bool HasValidWidgetAssetData() const = 0;` — @return true if the data of the asset that the widget we were initialized from was created from (for UMG widgets) is valid
- L171 _public prototype_ `virtual FAssetData GetWidgetAssetData() const = 0;` — @return The data of the asset that the widget we were initialized from was created from (for UMG widgets)
- L176 _public prototype_ `virtual FVector2D GetWidgetDesiredSize() const = 0;` — @return The desired size of the widget we were initialized from
- L181 _public prototype_ `virtual FSlateColor GetWidgetForegroundColor() const = 0;` — @return The foreground color of the widget we were initialized from
- L186 _public prototype_ `virtual TPointerAsInt GetWidgetAddress() const = 0;` — @return The in-memory address of the widget we were initialized from
- L191 _public prototype_ `virtual bool GetWidgetEnabled() const = 0;` — @return True if the the widget we were initialized from is enabled, false otherwise
- L196 _public prototype_ `virtual bool IsWidgetLive() const = 0;` — @return True if the widget is live, and local and can potentially be manipulated in real-time.
- L201 _public prototype_ `virtual UObject* GetWidgetSourceObject() const = 0;` — @return The source object obtained from the widget's meta data.
- L206 _public prototype_ `const FGeometry& GetGeometry() const;` — @return The geometry of the widget.
- L211 _public prototype_ `FSlateLayoutTransform GetAccumulatedLayoutTransform() const;` — @return The accumulated layout transform of the widget we were initialized from
- L216 _public prototype_ `const FSlateRenderTransform& GetAccumulatedRenderTransform() const;` — @return The accumulated render transform of the widget we were initialized from
- L221 _public prototype_ `FVector2f GetLocalSize() const;` — @return The local size of the widget we were initialized from
- L226 _public prototype_ `const FWidgetHitTestInfo& GetHitTestInfo() const;` — @return The basic hit-test of the widget we were initialized from
- L231 _public prototype_ `const FLinearColor& GetTint() const;` — @return The tint that is applied to text in order to provide visual hints
- L236 _public prototype_ `void SetTint(const FLinearColor& InTint);` — Set the tint to the given value
- L241 _public prototype_ `static void AddChildNode(TSharedRef<FWidgetReflectorNodeBase> InParentNode, TSharedRef<FWidgetReflectorNodeBase> InChildNode);` — Add the given node to our list of children for this widget (this node will keep a strong reference to the instance)
- L246 _public prototype_ `const TArray<TSharedRef<FWidgetReflectorNodeBase>>& GetChildNodes() const;` — @return The node entries for the widget's children
- L251 _public prototype_ `const TSharedPtr<FWidgetReflectorNodeBase> GetParentNode() const;` — @returns The node entry for the widget's parent, if it exists,
- L257 _protected prototype_ `FWidgetReflectorNodeBase();` — Default constructor
- L262 _protected prototype_ `explicit FWidgetReflectorNodeBase(const FArrangedWidget& InWidgetGeometry);` — Construct this node from the given widget geometry, caching out any data that may be required for future visualization in the widget reflector
- L266 _protected member_ `FGeometry WidgetGeometry;` — The Geometry of the widget.
- L269 _protected member_ `FWidgetHitTestInfo HitTestInfo;` — The hit-test information for the widget
- L272 _protected member_ `TArray<TSharedRef<FWidgetReflectorNodeBase>> ChildNodes;` — Node entries for the widget's children
- L275 _protected member_ `TWeakPtr<FWidgetReflectorNodeBase> ParentNode;` — Node entry for the widget's parent
- L278 _protected member_ `FLinearColor Tint;` — A tint that is applied to text in order to provide visual hints (Transient)

#### class `FLiveWidgetReflectorNode`  
`class FLiveWidgetReflectorNode : public FWidgetReflectorNodeBase`  
_L284-339_
- inherits: `FWidgetReflectorNodeBase`
- desc: A widget reflector node that holds on to the widget it references so that certain properties can be updated live
- L290 _public prototype_ `virtual ~FLiveWidgetReflectorNode() = default;` — Destructor
- L295 _public prototype_ `static TSharedRef<FLiveWidgetReflectorNode> Create(const FArrangedWidget& InWidgetGeometry);` — Create a live node instance from the given widget geometry, caching out any data that may be required for future visualization in the widget reflector
- L298 _public prototype_ `virtual EWidgetReflectorNodeType GetNodeType() const override;` — FWidgetReflectorNodeBase interface
- L299 _public prototype_ `virtual TSharedPtr<SWidget> GetLiveWidget() const override;`
- L300 _public prototype_ `virtual FText GetWidgetType() const override;`
- L301 _public prototype_ `virtual FText GetWidgetTypeAndShortName() const override;`
- L302 _public prototype_ `virtual FText GetWidgetVisibilityText() const override;`
- L303 _public prototype_ `virtual bool GetWidgetVisible() const override;`
- L304 _public prototype_ `virtual bool GetWidgetVisibilityInherited() const override;`
- L305 _public prototype_ `virtual bool GetWidgetSupportsInvalidation() const override;`
- L306 _public prototype_ `virtual bool GetSupportsInvalidationRecursive() const override;`
- L307 _public prototype_ `virtual FText GetWidgetClippingText() const override;`
- L308 _public prototype_ `virtual int32 GetWidgetLayerId() const override;`
- L309 _public prototype_ `virtual int32 GetWidgetLayerIdOut() const override;`
- L310 _public prototype_ `virtual bool GetWidgetFocusable() const override;`
- L311 _public prototype_ `virtual bool GetWidgetNeedsTick() const override;`
- L312 _public prototype_ `virtual bool GetWidgetIsVolatile() const override;`
- L313 _public prototype_ `virtual bool GetWidgetIsVolatileIndirectly() const override;`
- L314 _public prototype_ `virtual bool GetWidgetHasActiveTimers() const override;`
- L315 _public prototype_ `virtual bool GetWidgetIsInvalidationRoot() const override;`
- L316 _public prototype_ `virtual FText GetWidgetReadableLocation() const override;`
- L317 _public prototype_ `virtual FString GetWidgetFile() const override;`
- L318 _public prototype_ `virtual int32 GetWidgetLineNumber() const override;`
- L319 _public prototype_ `virtual int32 GetWidgetAttributeCount() const override;`
- L320 _public prototype_ `virtual int32 GetWidgetCollapsedAttributeCount() const override;`
- L321 _public prototype_ `virtual bool HasValidWidgetAssetData() const override;`
- L322 _public prototype_ `virtual FAssetData GetWidgetAssetData() const override;`
- L323 _public prototype_ `virtual FVector2D GetWidgetDesiredSize() const override;`
- L324 _public prototype_ `virtual FSlateColor GetWidgetForegroundColor() const override;`
- L325 _public prototype_ `virtual TPointerAsInt GetWidgetAddress() const override;`
- L326 _public prototype_ `virtual bool GetWidgetEnabled() const override;`
- L327 _public function_ `virtual bool IsWidgetLive() const override`
- L328 _public prototype_ `virtual UObject* GetWidgetSourceObject() const override;`
- L334 _private prototype_ `explicit FLiveWidgetReflectorNode(const FArrangedWidget& InWidgetGeometry);` — Construct this node from the given widget geometry, caching out any data that may be required for future visualization in the widget reflector
- L338 _private member_ `TWeakPtr<SWidget> Widget;` — The widget this node is watching

#### class `FSnapshotWidgetReflectorNode`  
`class FSnapshotWidgetReflectorNode : public FWidgetReflectorNodeBase`  
_L344-488_
- inherits: `FWidgetReflectorNodeBase`
- desc: A widget reflector node that holds the widget information from a snapshot at a given point in time
- L350 _public prototype_ `virtual ~FSnapshotWidgetReflectorNode() = default;` — Destructor
- L355 _public prototype_ `static TSharedRef<FSnapshotWidgetReflectorNode> Create();` — Create a default snapshot node instance
- L360 _public prototype_ `static TSharedRef<FSnapshotWidgetReflectorNode> Create(const FArrangedWidget& InWidgetGeometry);` — Create a snapshot node instance node from the given widget geometry, caching out any data that may be required for future visualization in the widget reflector
- L363 _public prototype_ `virtual EWidgetReflectorNodeType GetNodeType() const override;` — FWidgetReflectorNodeBase interface
- L364 _public prototype_ `virtual TSharedPtr<SWidget> GetLiveWidget() const override;`
- L365 _public prototype_ `virtual FText GetWidgetType() const override;`
- L366 _public prototype_ `virtual FText GetWidgetTypeAndShortName() const override;`
- L367 _public prototype_ `virtual FText GetWidgetVisibilityText() const override;`
- L368 _public prototype_ `virtual FText GetWidgetClippingText() const override;`
- L369 _public prototype_ `virtual int32 GetWidgetLayerId() const override;`
- L370 _public prototype_ `virtual int32 GetWidgetLayerIdOut() const override;`
- L371 _public prototype_ `virtual bool GetWidgetVisible() const override;`
- L372 _public prototype_ `virtual bool GetWidgetVisibilityInherited() const override;`
- L373 _public prototype_ `virtual bool GetWidgetSupportsInvalidation() const override;`
- L374 _public prototype_ `virtual bool GetSupportsInvalidationRecursive() const override;`
- L375 _public prototype_ `virtual bool GetWidgetFocusable() const override;`
- L376 _public prototype_ `virtual bool GetWidgetNeedsTick() const override;`
- L377 _public prototype_ `virtual bool GetWidgetIsVolatile() const override;`
- L378 _public prototype_ `virtual bool GetWidgetIsVolatileIndirectly() const override;`
- L379 _public prototype_ `virtual bool GetWidgetHasActiveTimers() const override;`
- L380 _public prototype_ `virtual bool GetWidgetIsInvalidationRoot() const override;`
- L381 _public prototype_ `virtual FText GetWidgetReadableLocation() const override;`
- L382 _public prototype_ `virtual FString GetWidgetFile() const override;`
- L383 _public prototype_ `virtual int32 GetWidgetLineNumber() const override;`
- L384 _public prototype_ `virtual int32 GetWidgetAttributeCount() const override;`
- L385 _public prototype_ `virtual int32 GetWidgetCollapsedAttributeCount() const override;`
- L386 _public prototype_ `virtual bool HasValidWidgetAssetData() const override;`
- L387 _public prototype_ `virtual FAssetData GetWidgetAssetData() const override;`
- L388 _public prototype_ `virtual FVector2D GetWidgetDesiredSize() const override;`
- L389 _public prototype_ `virtual FSlateColor GetWidgetForegroundColor() const override;`
- L390 _public prototype_ `virtual TPointerAsInt GetWidgetAddress() const override;`
- L391 _public prototype_ `virtual bool GetWidgetEnabled() const override;`
- L392 _public function_ `virtual bool IsWidgetLive() const override`
- L393 _public prototype_ `virtual UObject* GetWidgetSourceObject() const override;`
- L396 _public prototype_ `static TSharedRef<FJsonValue> ToJson(const TSharedRef<FSnapshotWidgetReflectorNode>& RootSnapshotNode);` — Save this node data as a JSON object
- L399 _public prototype_ `static TSharedRef<FSnapshotWidgetReflectorNode> FromJson(const TSharedRef<FJsonValue>& RootJsonValue);` — Populate this node data from a JSON object
- L405 _private prototype_ `FSnapshotWidgetReflectorNode();` — Default constructor
- L410 _private prototype_ `explicit FSnapshotWidgetReflectorNode(const FArrangedWidget& InWidgetGeometry);` — Construct this node from the given widget geometry, caching out any data that may be required for future visualization in the widget reflector
- L414 _private member_ `FText CachedWidgetType;` — The type string of the widget at the point it was passed to Initialize
- L417 _private member_ `FText CachedWidgetTypeAndShortName;` — The type and short name string of the widget at the point it was passed to Initialize
- L420 _private member_ `FText CachedWidgetVisibilityText;` — The visibility string of the widget at the point it was passed to Initialize
- L423 _private member_ `bool bCachedWidgetVisible;` — The visible of the widget at the point it was passed to Initialize
- L426 _private member_ `bool bCachedWidgetVisibleInherited;` — The visible inherited of the widget at the point it was passed to Initialize
- L429 _private member_ `bool bCachedSupportsInvalidation;` — Did the widget support invalidation at the point it was passed to Initialize
- L432 _private member_ `bool bCachedSupportsInvalidationRecursive;` — Did the widget recursively support invalidation at the point it was passed to Initialize
- L435 _private member_ `bool bCachedWidgetFocusable;` — The focusability of the widget at the point it was passed to Initialize
- L438 _private member_ `bool bCachedWidgetNeedsTick;` — The ticking state of the widget at the point it was passed to Initialize
- L441 _private member_ `bool bCachedWidgetIsVolatile;` — The volatility state of the widget at the point it was passed to Initialize
- L444 _private member_ `bool bCachedWidgetIsVolatileIndirectly;` — The volatility indirectly state of the widget at the point it was passed to Initialize
- L447 _private member_ `bool bCachedWidgetHasActiveTimers;` — The active timer state of the widget at the point it was passed to Initialize
- L450 _private member_ `bool bCachedWidgetIsInvalidationRoot;` — If the widget was an invalidation root at the point it was passed to Initialize
- L453 _private member_ `bool bCachedWidgetEnabled;` — The enabled state of the widget at the point it was passed to Initialize
- L456 _private member_ `FText CachedWidgetClippingText;` — The clipping string of the widget at the point it was passed to Initialize
- L459 _private member_ `int32 CachedWidgetLayerId;` — The LayerId of the widget
- L460 _private member_ `int32 CachedWidgetLayerIdOut;`
- L463 _private member_ `FText CachedWidgetReadableLocation;` — The human readable location (source file for C++ widgets, asset name for UMG widgets) of the widget at the point it was passed to Initialize
- L466 _private member_ `FString CachedWidgetFile;` — The name of the file that the widget was created from at the point it was passed to Initialize (for C++ widgets)
- L469 _private member_ `int32 CachedWidgetLineNumber;` — The line number of the file that the widget was created from at the point it was passed to Initialize (for C++ widgets)
- L472 _private member_ `int32 CachedWidgetAttributeCount;` — The number of slate attributes registered on the SWidget.
- L475 _private member_ `int32 CachedWidgetCollapsedAttributeCount;` — The number of slate attributes registered on the SWidget marked as "update when collapsed".
- L478 _private member_ `FAssetData CachedWidgetAssetData;` — The name of the asset that the widget was created from at the point it was passed to Initialize (for UMG widgets)
- L481 _private member_ `FVector2D CachedWidgetDesiredSize;` — The desired size of the widget at the point it was passed to Initialize
- L484 _private member_ `FSlateColor CachedWidgetForegroundColor;` — The foreground color of the widget at the point it was passed to Initialize
- L487 _private member_ `TPointerAsInt CachedWidgetAddress;` — The in-memory address of the widget at the point it was passed to Initialize

#### class `FWidgetReflectorNodeUtils`  
`class FWidgetReflectorNodeUtils`  
_L491-685_
- L500 _public prototype_ `static TSharedRef<FLiveWidgetReflectorNode> NewLiveNode(const FArrangedWidget& InWidgetGeometry = FArrangedWidget(SNullWidget::NullWidget, FGeometry()));` — Create a single node referencing a live widget. @param InNodeClass The type of widget reflector node to create @param InWidgetGeometry Optional widget and associated geometry which this node should represent
- L509 _public prototype_ `static TSharedRef<FLiveWidgetReflectorNode> NewLiveNodeTreeFrom(const FArrangedWidget& InWidgetGeometry);` — Create nodes for the supplied widget and all their children such that they reference a live widget Note that we include both visible and invisible children! @param InNodeClass The type of widget reflector node to create @param InWidgetGeometry Widget and geometry whose children to capture in the snapshot.
- L517 _public prototype_ `static TSharedRef<FSnapshotWidgetReflectorNode> NewSnapshotNode(const FArrangedWidget& InWidgetGeometry = FArrangedWidget(SNullWidget::NullWidget, FGeometry()));` — Create a single node referencing a snapshot of its current state. @param InNodeClass The type of widget reflector node to create @param InWidgetGeometry Optional widget and associated geometry which this node should represent
- L526 _public prototype_ `static TSharedRef<FSnapshotWidgetReflectorNode> NewSnapshotNodeTreeFrom(const FArrangedWidget& InWidgetGeometry);` — Create nodes for the supplied widget and all their children such that they reference a snapshot of their current state Note that we include both visible and invisible children! @param InNodeClass The type of widget reflector node to create @param InWidgetGeometry Widget and geometry whose children to capture in the snapshot.
- L535 _private prototype_ `static TSharedRef<FWidgetReflectorNodeBase> NewNode(const EWidgetReflectorNodeType InNodeType, const FArrangedWidget& InWidgetGeometry = FArrangedWidget(SNullWidget::NullWidget, FGeometry()));` — Create a single node. @param InNodeClass The type of widget reflector node to create @param InWidgetGeometry Optional widget and associated geometry which this node should represent
- L544 _private prototype_ `static TSharedRef<FWidgetReflectorNodeBase> NewNodeTreeFrom(const EWidgetReflectorNodeType InNodeType, const FArrangedWidget& InWidgetGeometry);` — Create nodes for the supplied widget and all their children Note that we include both visible and invisible children! @param InNodeClass The type of widget reflector node to create @param InWidgetGeometry Widget and geometry whose children to capture in the snapshot.
- L555 _public prototype_ `static void FindLiveWidgetPath(const TArray<TSharedRef<FWidgetReflectorNodeBase>>& CandidateNodes, const FWidgetPath& WidgetPathToFind, TArray<TSharedRef<FWidgetReflectorNodeBase>>& SearchResult);` — Locate all the widgets from a widget path in a list of nodes and their children. @note This only really works for live nodes, as the snapshot nodes may no longer exist, or not even be local to this machine @param CandidateNodes A list of FReflectorNodes that represent widgets. @param WidgetPathToFind We want to find all reflector nodes corresponding to widgets in this path @param SearchResult An array that gets results put in it
- L565 _public prototype_ `static void FindLiveWidget(const TArray<TSharedRef<FWidgetReflectorNodeBase>>& CandidateNodes, const TSharedPtr<const SWidget>& WidgetToFind, TArray<TSharedRef<FWidgetReflectorNodeBase>>& SearchResult);` — Locate the widget in a list of nodes and their children. @note This only really works for live nodes, as the snapshot nodes may no longer exist, or not even be local to this machine @param CandidateNodes A list of FReflectorNodes that represent widgets. @param WidgetToFind We want to find the reflector nodes corresponding to this widget @param SearchResult An array that gets results put in it
- L575 _public prototype_ `static void FindSnaphotWidget(const TArray<TSharedRef<FWidgetReflectorNodeBase>>& CandidateNodes, FWidgetReflectorNodeBase::TPointerAsInt WidgetToFind, TArray<TSharedRef<FWidgetReflectorNodeBase>>& SearchResult);` — Locate the widget pointer in a list of nodes and their children. @note This only really works for snapshot nodes, as the live node may no longer have the same pointer @param CandidateNodes A list of FReflectorNodes that represent widgets. @param WidgetPointer We want to find all reflector nodes corresponding to widgets in this path @param SearchResult An array that gets results put in it
- L581 _public prototype_ `static FText GetWidgetType(const TSharedPtr<const SWidget>& InWidget);` — @return The type string for the given widget
- L586 _public prototype_ `static FText GetWidgetTypeAndShortName(const TSharedPtr<const SWidget>& InWidget);` — @return The type string combined with a short name (if any) for the given widget
- L591 _public prototype_ `static FText GetWidgetVisibilityText(const TSharedPtr<const SWidget>& InWidget);` — @return The current visibility string for the given widget
- L594 _public prototype_ `static bool GetWidgetVisibility(const TSharedPtr<const SWidget>& InWidget);` — Is the widget visible?
- L597 _public prototype_ `static bool GetWidgetVisibilityInherited(const TSharedPtr<const SWidget>& InWidget);` — Is the widget visible and its parents are also visible?
- L600 _public prototype_ `static bool GetWidgetSupportsInvalidation(const TSharedPtr<const SWidget>& InWidget);` — Does the widget supports invalidation?
- L603 _public prototype_ `static bool GetWidgetSupportsInvalidationRecursive(const TSharedPtr<const SWidget>& InWidget);` — Does this widget and all its children support invalidation?
- L608 _public prototype_ `static FText GetWidgetClippingText(const TSharedPtr<const SWidget>& InWidget);` — @return The current clipping string for the given widget
- L613 _public prototype_ `static int32 GetWidgetLayerId(const TSharedPtr<const SWidget>& InWidget);` — @return The current LayerId for the given widget
- L614 _public prototype_ `static int32 GetWidgetLayerIdOut(const TSharedPtr<const SWidget>& InWidget);`
- L619 _public prototype_ `static bool GetWidgetFocusable(const TSharedPtr<const SWidget>& InWidget);` — @return The current focusability for the given widget
- L621 _public prototype_ `static bool GetWidgetNeedsTick(const TSharedPtr<const SWidget>& InWidget);`
- L622 _public prototype_ `static bool GetWidgetIsVolatile(const TSharedPtr<const SWidget>& InWidget);`
- L623 _public prototype_ `static bool GetWidgetIsVolatileIndirectly(const TSharedPtr<const SWidget>& InWidget);`
- L624 _public prototype_ `static bool GetWidgetHasActiveTimers(const TSharedPtr<const SWidget>& InWidget);`
- L625 _public prototype_ `static bool GetWidgetIsInvalidationRoot(const TSharedPtr<const SWidget>& InWidget);`
- L626 _public prototype_ `static int32 GetWidgetAttributeCount(const TSharedPtr<const SWidget>& InWidget);`
- L627 _public prototype_ `static int32 GetWidgetCollapsedAttributeCount(const TSharedPtr<const SWidget>& InWidget);`
- L634 _public prototype_ `static FText GetWidgetReadableLocation(const TSharedPtr<const SWidget>& InWidget);` — The human readable location for widgets that are defined in C++ is the file and line number The human readable location for widgets that are defined in UMG is the asset name @return The fully human readable location for the given widget
- L639 _public prototype_ `static FString GetWidgetFile(const TSharedPtr<const SWidget>& InWidget);` — @return The name of the file that this widget was created from (for C++ widgets)
- L644 _public prototype_ `static int32 GetWidgetLineNumber(const TSharedPtr<const SWidget>& InWidget);` — @return The line number of the file that this widget was created from (for C++ widgets)
- L649 _public prototype_ `static bool HasValidWidgetAssetData(const TSharedPtr<const SWidget>& InWidget);` — @return true if the name of the asset that this widget was created from (for UMG widgets) is valid
- L654 _public prototype_ `static FAssetData GetWidgetAssetData(const TSharedPtr<const SWidget>& InWidget);` — @return The name of the asset that this widget was created from (for UMG widgets)
- L659 _public prototype_ `static FVector2D GetWidgetDesiredSize(const TSharedPtr<const SWidget>& InWidget);` — @return The current desired size of the given widget
- L664 _public prototype_ `static FString GetWidgetAddressAsString(const TSharedPtr<const SWidget>& InWidget);` — @return The in-memory address of the widget, converted to a string
- L669 _public prototype_ `static FWidgetReflectorNodeBase::TPointerAsInt GetWidgetAddress(const TSharedPtr<const SWidget>& InWidget);` — @return The in-memory address of the widget
- L674 _public prototype_ `static FString WidgetAddressToString(FWidgetReflectorNodeBase::TPointerAsInt InWidgetPtr);` — @return Convert a widget address into a string
- L679 _public prototype_ `static FSlateColor GetWidgetForegroundColor(const TSharedPtr<const SWidget>& InWidget);` — @return The current foreground color of the given widget
- L684 _public prototype_ `static bool GetWidgetEnabled(const TSharedPtr<const SWidget>& InWidget);` — @return True if the given widget is currently enabled, false otherwise

### `Source/Developer/SlateReflector/Private/SlateReflectorModule.h` (Private)


#### class `FSlateReflectorModule`  
`class FSlateReflectorModule : public ISlateReflectorModule`  
_L15-30_
- inherits: `ISlateReflectorModule`
- desc: Implements the SlateReflector module.
- L19 _public function_ `static FSlateReflectorModule* GetModulePtr()` — Get this module
- L26 _public prototype_ `virtual TSharedPtr<SWidgetReflector> GetWidgetReflectorInstance() = 0;` — Get the current instance of the WidgetReflector
- L29 _public prototype_ `virtual FInputEventVisualizer* GetInputEventVisualizer() = 0;` — Get the current instance of the Input Event Visualizer

### `Source/Developer/SlateReflector/Private/Styling/WidgetReflectorStyle.h` (Private)


#### class `FWidgetReflectorStyle`  
`class FWidgetReflectorStyle`  
_L10-26_
- desc: Implements the visual style of the widget reflector.
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L19 _public prototype_ `static FName GetStyleSetName();`
- L22 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L25 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

### `Source/Developer/SlateReflector/Private/VisualTreeCapture.h` (Private)


#### class `FVisualEntry`  
`class FVisualEntry`  
_L19-40_
- L22 _public member_ `FVector2f TopLeft;`
- L23 _public member_ `FVector2f TopRight;`
- L24 _public member_ `FVector2f BottomLeft;`
- L25 _public member_ `FVector2f BottomRight;`
- L27 _public member_ `int32 LayerId = INDEX_NONE;`
- L28 _public member_ `int32 ClippingIndex = INDEX_NONE;`
- L29 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L30 _public member_ `EElementType ElementType = EElementType::ET_Count;`
- L31 _public member_ `bool bFromCache = false;`
- L32 _public member_ `TWeakPtr<const SWidget> Widget;`
- L34 _public prototype_ `FVisualEntry(const TWeakPtr<const SWidget>& Widget, int32 InElementIndex, EElementType InElementType);`
- L35 _public prototype_ `FVisualEntry(const TSharedRef<const SWidget>& Widget, const FSlateDrawElement& InElement);`
- L37 _public prototype_ `void Resolve(const FSlateWindowElementList& ElementList);`
- L39 _public prototype_ `bool IsPointInside(const FVector2f& Point) const;`

#### class `FVisualTreeSnapshot`  
`class FVisualTreeSnapshot : public TSharedFromThis<FVisualTreeSnapshot>`  
_L42-54_
- inherits: `TSharedFromThis<FVisualTreeSnapshot>`
- L45 _public prototype_ `TSharedPtr<const SWidget> Pick(FVector2f Point) const;`
- L47 _public prototype_ `TArray<int32> PickAll(FVector2f Point) const;` — Returns all the the Entires at the location.
- L50 _public member_ `TArray<FVisualEntry> Entries;`
- L51 _public member_ `TArray<FSlateClippingState> ClippingStates;`
- L52 _public member_ `TArray<FSlateClippingState> CachedClippingStates;`
- L53 _public member_ `TArray<TWeakPtr<const SWidget>> WidgetStack;`

#### class `FVisualTreeCapture`  
`class FVisualTreeCapture`  
_L56-109_
- L59 _public prototype_ `FVisualTreeCapture();`
- L60 _public prototype_ `~FVisualTreeCapture();`
- L63 _public prototype_ `void Enable();` — Enables visual tree capture
- L66 _public prototype_ `void Disable();` — Disables visual tree capture
- L69 _public prototype_ `void Reset();` — Resets the visual tree capture to a pre-capture state and destroys the cached visual tree captured last.
- L72 _public function_ `bool IsEnabled() const` — The visual tree capture is enabled.
- L78 _public function_ `bool HasElements() const` — The visual tree capture contains elements.
- L83 _public prototype_ `TSharedPtr<const FVisualTreeSnapshot> GetVisualTreeForWindow(SWindow* InWindow) const;`
- L87 _private prototype_ `void AddInvalidationRootCachedEntries(TSharedRef<FVisualTreeSnapshot> Tree, const FSlateInvalidationRoot* Entries);`
- L90 _private prototype_ `void BeginWindow(const FSlateWindowElementList& ElementList);`
- L91 _private prototype_ `void EndWindow(const FSlateWindowElementList& ElementList);`
- L93 _private prototype_ `void BeginWidgetPaint(const SWidget* Widget, const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, const FSlateWindowElementList& ElementList, int32 LayerId);`
- L96 _private prototype_ `void EndWidgetPaint(const SWidget* Widget, const FSlateWindowElementList& ElementList, int32 LayerId);`
- L99 _private prototype_ `void ElementTypeAdded(const FSlateDebuggingElementTypeAddedEventArgs& ElementTypeAddedArgs);`
- L101 _private prototype_ `void OnWindowBeingDestroyed(const SWindow& WindowBeingDestoyed);`
- L104 _private member_ `TMap<const SWindow*, TSharedPtr<FVisualTreeSnapshot>> VisualTrees;`
- L105 _private member_ `bool bIsEnabled;`
- L106 _private member_ `int32 WindowIsInvalidationRootCounter;`
- L107 _private member_ `int32 WidgetIsInvalidationRootCounter;`
- L108 _private member_ `int32 WidgetIsInvisibleToWidgetReflectorCounter;`

### `Source/Developer/SlateReflector/Private/WidgetSnapshotMessages.h` (Private)


#### struct `FWidgetSnapshotRequest`  
`struct FWidgetSnapshotRequest`  
_L15-26_
- reflection: `USTRUCT()`
- desc: Implements a message that is used to request a widget snapshot from a remote target.
- L21 _public member_ `FGuid TargetInstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")` — The instance ID of the remote target we want to receive a snapshot from
- L25 _public member_ `FGuid SnapshotRequestId;` — `UPROPERTY(EditAnywhere, Category="Message")` — The request ID of this snapshot (used to identify the correct response from the target)

#### struct `FWidgetSnapshotResponse`  
`struct FWidgetSnapshotResponse`  
_L33-44_
- reflection: `USTRUCT()`
- desc: Implements a message that is used to receive a widget snapshot from a remote target.
- L39 _public member_ `FGuid SnapshotRequestId;` — `UPROPERTY(EditAnywhere, Category="Message")` — The request ID of this snapshot (used to identify the correct response from the target)
- L43 _public member_ `TArray<uint8> SnapshotData;` — `UPROPERTY(EditAnywhere, Category="Message")` — The snapshot data, to be used by FWidgetSnapshotData::LoadSnapshotFromBuffer

### `Source/Developer/SlateReflector/Private/WidgetSnapshotService.h` (Private)


#### class `FWidgetSnapshotService`  
`class FWidgetSnapshotService`  
_L15-40_
- desc: Implements the service for handling remote widget snapshots.
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetSnapshotResponse, const TArray<uint8>& );`
- L20 _public prototype_ `FWidgetSnapshotService();`
- L23 _public prototype_ `FGuid RequestSnapshot(const FGuid& InRemoteInstanceId, const FOnWidgetSnapshotResponse& OnResponse);` — Request a snapshot from the given instance. The given delegate will be called when the response comes in
- L26 _public prototype_ `void AbortSnapshotRequest(const FGuid& InSnapshotRequestId);` — Abort a request using the GUID previously obtained via a call to RequestSnapshot
- L30 _private prototype_ `void HandleWidgetSnapshotRequestMessage(const FWidgetSnapshotRequest& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FWidgetSnapshotRequest messages
- L33 _private prototype_ `void HandleWidgetSnapshotResponseMessage(const FWidgetSnapshotResponse& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FWidgetSnapshotResponse messages
- L36 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint
- L39 _private member_ `TMap<FGuid, FOnWidgetSnapshotResponse> PendingSnapshotResponseHandlers;` — Handlers awaiting their resultant snapshot data

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetSnapshotResponse, const TArray<uint8>& );`

### `Source/Developer/SlateReflector/Private/Widgets/NavigationSimulationOverlay.h` (Private)


#### class `FNavigationSimulationOverlay`  
`class FNavigationSimulationOverlay`  
_L12-19_
- desc: Helper class to paint the result of a navigation event simulation
- L15 _public prototype_ `FNavigationSimulationOverlay() = delete;`
- L17 _public prototype_ `static int32 PaintSnapshotNode(const TArray<FNavigationSimulationWidgetNodePtr>& NodeToPaint, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FVector2D& RootDrawOffset);`
- L18 _public prototype_ `static int32 PaintLiveNode(const TArray<FNavigationSimulationWidgetNodePtr>& NodeToPaint, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId);`

### `Source/Developer/SlateReflector/Private/Widgets/SAtlasVisualizer.h` (Private)


#### class `SAtlasVisualizer`  
`class SAtlasVisualizer : public ISlateViewport, public SCompoundWidget`  
_L18-68_
- inherits: `ISlateViewport,SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS( SAtlasVisualizer ) : _AtlasProvider()`
- L25 _public prototype_ `SLATE_ARGUMENT( ISlateAtlasProvider*, AtlasProvider ) SLATE_END_ARGS()`
- L31 _public prototype_ `virtual bool RequiresVsync() const override;`
- L32 _public prototype_ `virtual FSlateShaderResource* GetViewportRenderTargetTexture() const override;`
- L33 _public prototype_ `virtual bool IsViewportTextureAlphaOnly() const override;`
- L34 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L35 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent);`
- L36 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L37 _public prototype_ `virtual TUniquePtr<UE::Slate::FPaintScope> Paint(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, const int32 LayerId, const FWidgetStyle& InWidgetStyle, const bool bParentEnabled) override;`
- L38 _public prototype_ `virtual FText GetToolTipText() const;`
- L40 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _private prototype_ `void RebuildToolTip(const FAtlasSlotInfo& Info);`
- L43 _private prototype_ `FText GetViewportSizeText() const;`
- L44 _private prototype_ `FVector2D GetViewportWidgetSize() const;`
- L45 _private prototype_ `FText GetZoomLevelPercentText() const;`
- L46 _private prototype_ `void OnFitToWindowStateChanged( ECheckBoxState NewState );`
- L47 _private prototype_ `ECheckBoxState OnGetFitToWindowState() const;`
- L48 _private prototype_ `FReply OnActualSizeClicked();`
- L49 _private prototype_ `EVisibility OnGetDisplayCheckerboardVisibility() const;`
- L50 _private prototype_ `void OnDisplayCheckerboardStateChanged( ECheckBoxState NewState );`
- L51 _private prototype_ `ECheckBoxState OnGetCheckerboardState() const;`
- L52 _private prototype_ `EVisibility OnGetCheckerboardVisibility() const;`
- L53 _private prototype_ `void OnComboOpening();`
- L54 _private prototype_ `FText OnGetSelectedItemText() const;`
- L55 _private prototype_ `void OnAtlasPageChanged( TSharedPtr<int32> AtlasPage, ESelectInfo::Type SelectionType );`
- L56 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForCombo( TSharedPtr<int32> AtlasPage );`
- L58 _private member_ `FText HoveredAtlasSlotToolTip;`
- L59 _private member_ `ISlateAtlasProvider* AtlasProvider;`
- L60 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int32>>> AtlasPageCombo;`
- L61 _private member_ `TArray<TSharedPtr<int32>> AtlasPages;`
- L62 _private member_ `TSharedPtr<SAtlasVisualizerPanel> ScrollPanel;`
- L63 _private member_ `int32 SelectedAtlasPage;`
- L64 _private member_ `bool bDisplayCheckerboard;`
- L66 _private member_ `const FSlateBrush* HoveredSlotBorderBrush;`
- L67 _private member_ `FAtlasSlotInfo CurrentHoveredSlotInfo;`

### `Source/Developer/SlateReflector/Private/Widgets/SNavigationSimulationList.h` (Private)


#### class `SNavigationSimulationListBase`  
`class SNavigationSimulationListBase : public INavigationEventSimulationView`  
_L28-69_
- inherits: `INavigationEventSimulationView`
- L31 _public function_ `SLATE_BEGIN_ARGS(SNavigationSimulationListBase) : _ListItemsSource(nullptr)`
- L34 _public prototype_ `SLATE_ARGUMENT(const TArray<FNavigationSimulationWidgetNodePtr>*, ListItemsSource) SLATE_END_ARGS() void Construct(const FArguments& Args, ENavigationSimulationNodeType NodeType);`
- L40 _public prototype_ `virtual void SetSimulationResult(TArray<FSlateNavigationEventSimulator::FSimulationResult> SimulationResult) override;`
- L43 _public prototype_ `void SetListItemsSource(const TArray<FNavigationSimulationWidgetNodePtr>& ListItems);`
- L44 _public prototype_ `void SelectLiveWidget(const TSharedPtr<const SWidget>& Widget);`
- L45 _public prototype_ `void SelectSnapshotWidget(FNavigationSimulationWidgetInfo::TPointerAsInt SnapshotWidget);`
- L48 _protected prototype_ `virtual void HandleSourceListSelectionChangedImpl(const FNavigationSimulationWidgetNodePtr& Item) const = 0;`
- L49 _protected prototype_ `virtual void HandleNavigateToWidgetImpl(TWeakPtr<const SWidget> LiveWidget, FNavigationSimulationWidgetInfo::TPointerAsInt SnapshotWidget) const = 0;`
- L51 _protected prototype_ `TArray<FNavigationSimulationWidgetNodePtr> GetSelectedItems() const;`
- L52 _protected function_ `const TArray<FNavigationSimulationWidgetNodePtr>& GetItemsSource() const`
- L55 _private prototype_ `TSharedRef<ITableRow> MakeSourceListViewWidget(FNavigationSimulationWidgetNodePtr Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L56 _private prototype_ `void HandleSourceListSelectionChanged(FNavigationSimulationWidgetNodePtr Item, ESelectInfo::Type SelectionType);`
- L58 _private prototype_ `void HandleNavigateToLiveWidget(TWeakPtr<const SWidget> LiveWidget);`
- L59 _private prototype_ `void HandleNavigateToSnapshotWidget(FNavigationSimulationWidgetInfo::TPointerAsInt SnapshotWidget);`
- L62 _private member_ `ENavigationSimulationNodeType NodeType;`
- L63 _private member_ `TSharedPtr<SListView<FNavigationSimulationWidgetNodePtr>> ListView;`
- L64 _private member_ `TSharedPtr<SNavigationSimulationListInternal::SDetailView> ElementDetail;`
- L65 _private member_ `TArray<FNavigationSimulationWidgetNodePtr> ItemsSource;`
- L68 _protected member_ `bool bIsInSelectionGuard;`

#### class `SNavigationSimulationSnapshotList`  
`class SNavigationSimulationSnapshotList : public SNavigationSimulationListBase`  
_L71-92_
- inherits: `SNavigationSimulationListBase`
- L74 _public prototype_ `void Construct(const FArguments& Args, const FOnSnapshotWidgetAction& OnSnapshotWidgetSelected, const FOnSnapshotWidgetAction& OnNavigateToSnapshotWidget);`
- L77 _public function_ `virtual void SelectWidget(const TSharedPtr<SWidget>& Widget) override`
- L78 _public function_ `virtual int32 PaintSimuationResult(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) override`
- L81 _public prototype_ `int32 PaintNodesWithOffset(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FVector2D& RootDrawOffset);`
- L85 _protected prototype_ `virtual void HandleSourceListSelectionChangedImpl(const FNavigationSimulationWidgetNodePtr& Item) const override;`
- L86 _protected prototype_ `virtual void HandleNavigateToWidgetImpl(TWeakPtr<const SWidget> LiveWidget, FNavigationSimulationWidgetInfo::TPointerAsInt SnapshotWidget) const override;`
- L90 _private member_ `FOnSnapshotWidgetAction OnSnapshotWidgetSelected;`
- L91 _private member_ `FOnSnapshotWidgetAction OnNavigateToSnapshotWidget;`

#### class `SNavigationSimulationLiveList`  
`class SNavigationSimulationLiveList : public SNavigationSimulationListBase`  
_L94-113_
- inherits: `SNavigationSimulationListBase`
- L97 _public prototype_ `void Construct(const FArguments& Args, const FSimpleWidgetDelegate& OnLiveWidgetSelected, const FSimpleWidgetDelegate& OnNavigateToLiveWidget);`
- L100 _public prototype_ `virtual void SelectWidget(const TSharedPtr<SWidget>& Widget) override;`
- L101 _public prototype_ `virtual int32 PaintSimuationResult(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) override;`
- L106 _protected prototype_ `virtual void HandleSourceListSelectionChangedImpl(const FNavigationSimulationWidgetNodePtr& Item) const override;`
- L107 _protected prototype_ `virtual void HandleNavigateToWidgetImpl(TWeakPtr<const SWidget> LiveWidget, FNavigationSimulationWidgetInfo::TPointerAsInt SnapshotWidget) const override;`
- L111 _private member_ `FSimpleWidgetDelegate OnLiveWidgetSelected;`
- L112 _private member_ `FSimpleWidgetDelegate OnNavigateToLiveWidget;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace SNavigationSimulationListInternal`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSnapshotWidgetAction, FNavigationSimulationWidgetInfo::TPointerAsInt);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSnapshotWidgetAction, FNavigationSimulationWidgetInfo::TPointerAsInt);`

### `Source/Developer/SlateReflector/Private/Widgets/SSlateOptions.h` (Private)


#### class `SSlateOptions`  
`class SSlateOptions : public SCompoundWidget`  
_L14-25_
- inherits: `SCompoundWidget`
- desc: Widget that show debug options
- L17 _public function_ `SLATE_USER_ARGS(SSlateOptions)`
- L18 _public prototype_ `SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs);`
- L23 _private prototype_ `void HandleAppScaleSliderChanged(float NewValue);`
- L24 _private prototype_ `float HandleAppScaleSliderValue() const;`

### `Source/Developer/SlateReflector/Private/Widgets/SVisualElementsTab.h` (Private)


#### struct `UE::SlateReflector::Private::FVisualElementEntry`  
`struct FVisualElementEntry`  
_L22-29_
- desc: Lightweight display entry for the Elements tab: widget pointer, layer, and element type.
- L24 _public member_ `TWeakPtr<const SWidget> Widget;`
- L25 _public member_ `int32 LayerId = INDEX_NONE;`
- L26 _public member_ `EElementType ElementType = EElementType::ET_Count;`
- L28 _public prototype_ `explicit FVisualElementEntry(const FVisualEntry& InEntry);`

#### class `SVisualElementsTab`  
`class SVisualElementsTab : public SCompoundWidget`  
_L36-81_
- inherits: `SCompoundWidget`
- desc: Tab displaying all FVisualEntry items captured by FVisualTreeCapture.
- L39 _private typedef_ `using Super = SCompoundWidget;`
- L41 _private typedef_ `using FVisualElementEntry = UE::SlateReflector::Private::FVisualElementEntry;`
- L44 _public function_ `DECLARE_DELEGATE_OneParam(FOnWidgetSelected, TSharedPtr<const SWidget>) SLATE_BEGIN_ARGS(SVisualElementsTab)`
- L47 _public prototype_ `SLATE_EVENT(FOnWidgetSelected, OnWidgetSelected) SLATE_ATTRIBUTE(TArray<TSharedPtr<const SWidget>>, FilterWidgets) SLATE_ATTRIBUTE(bool, IsPickingActive) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TNotNull<const FVisualTreeCapture*> VisualCapture);`
- L54 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _private prototype_ `ECheckBoxState GetFilterByWidgetChecked() const;`
- L58 _private prototype_ `void HandleFilterByWidgetChanged(ECheckBoxState NewState);`
- L60 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FVisualElementEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L61 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRegionRow(TSharedPtr<FVisualElementEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L64 _private prototype_ `static bool IsEntryInsideRegion(const FVisualEntry& Entry, const FVisualEntry& Region);` — Returns true if all four corners of Entry are inside the Region's quad.
- L66 _private member_ `FOnWidgetSelected OnWidgetSelected;`
- L67 _private member_ `const FVisualTreeCapture* VisualCapture = nullptr;`
- L68 _private member_ `bool bFilterByWidget = false;`
- L69 _private member_ `bool bDrawablePickingActive = false;`
- L71 _private member_ `TAttribute<TArray<TSharedPtr<const SWidget>>> FilterWidgets;`
- L72 _private member_ `TAttribute<bool> IsPickingActive;`
- L75 _private member_ `TSharedPtr<SListView<TSharedPtr<FVisualElementEntry>>> ListView;` — Main list (filtered subset of snapshot entries).
- L76 _private member_ `TArray<TSharedPtr<FVisualElementEntry>> ListEntries;`
- L79 _private member_ `TSharedPtr<SListView<TSharedPtr<FVisualElementEntry>>> RegionListView;` — Region list (entries whose quads fit inside the entry under cursor).
- L80 _private member_ `TArray<TSharedPtr<FVisualElementEntry>> RegionEntries;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SlateReflector` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::SlateReflector`)
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetSelected, TSharedPtr<const SWidget>) SLATE_BEGIN_ARGS(SVisualElementsTab) {} SLATE_EVENT(FOnWidgetSelected, OnWidgetSelected) SLATE_ATTRIBUTE(TArray<TSharedPtr<const SWidget>>, FilterWidgets) SLATE_ATTRIBUTE(bool, IsPickingActive) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TNotNull<const FVisualTreeCapture*> VisualCapture);`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetEventLog.h` (Private)


#### class `SWidgetEventLog`  
`class SWidgetEventLog : public SCompoundWidget`  
_L24-100_
- inherits: `SCompoundWidget`
- L37 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetTokenActivated, TSharedPtr<const SWidget>);`
- L38 _public function_ `SLATE_BEGIN_ARGS(SWidgetEventLog)`
- L40 _public prototype_ `SLATE_EVENT(FOnWidgetTokenActivated, OnWidgetTokenActivated) SLATE_END_ARGS() virtual ~SWidgetEventLog();`
- L45 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<const SWidget> InReflectorWidget);`
- L48 _private prototype_ `void GenerateList();`
- L50 _private prototype_ `TSharedRef<SWidget> OnGenerateCategoriesMenu();`
- L51 _private prototype_ `void OnGenerateCategoriesSubMenu(FMenuBuilder& InSubMenuBuilder, EWidgetEventType EventType);`
- L52 _private prototype_ `void EnabledCategory(EWidgetEventType EventType);`
- L53 _private prototype_ `ECheckBoxState GetEnabledCheckState(EWidgetEventType EventType) const;`
- L54 _private prototype_ `void EnabledAllFromSubCategory(EWidgetEventType EventType);`
- L55 _private prototype_ `ECheckBoxState GetEnabledAllFromSubCategoryCheckState(EWidgetEventType EventType) const;`
- L56 _private prototype_ `void EnabledSubCategory(EWidgetEventType EventType, uint8 Index);`
- L57 _private prototype_ `ECheckBoxState GetEnabledSubCategoryCheckState(EWidgetEventType EventType, uint8 Index) const;`
- L58 _private prototype_ `void HandleFilterWidgetReflectorEventStateChanged(ECheckBoxState NewValue);`
- L59 _private prototype_ `ECheckBoxState HandleFilterWidgetReflectorEventIsChecked() const;`
- L61 _private prototype_ `void RemoveListeners();`
- L62 _private prototype_ `void UpdateListeners();`
- L64 _private prototype_ `void HandleWarning(const FSlateDebuggingWarningEventArgs& EventArgs) const;`
- L65 _private prototype_ `void HandleInputEvent(const FSlateDebuggingInputEventArgs& EventArgs) const;`
- L66 _private prototype_ `void HandleFocusEvent(const FSlateDebuggingFocusEventArgs& EventArgs) const;`
- L67 _private prototype_ `void HandleAttemptNavigationEvent(const FSlateDebuggingNavigationEventArgs& EventArgs) const;`
- L68 _private prototype_ `void HandleCaptureStateChangeEvent(const FSlateDebuggingMouseCaptureEventArgs& EventArgs) const;`
- L69 _private prototype_ `void HandleCursorChangedEvent(const FSlateDebuggingCursorQueryEventArgs& EventArgs) const;`
- L70 _private prototype_ `void SelectWidget(TWeakPtr<const SWidget> Widget) const;`
- L72 _private prototype_ `bool IsInsideWidgetReflector(const SWidget* Widget) const;`
- L73 _private prototype_ `bool IsInsideWidgetReflector(TSharedRef<const SWidget> Widget) const;`
- L74 _private prototype_ `bool IsInsideWidgetReflector(const TSharedPtr<const SWidget>& Widget) const;`
- L75 _private prototype_ `bool IsInsideWidgetReflector(const FWidgetPath& WidgetPath) const;`
- L76 _private prototype_ `bool IsInsideWidgetReflector(const FWeakWidgetPath& WidgetPath) const;`
- L78 _private prototype_ `const TBitArray<>& GetBitField(EWidgetEventType EventType) const;`
- L79 _private prototype_ `TBitArray<>& GetBitField(EWidgetEventType EventType);`
- L80 _private prototype_ `const bool& GetCategoryFlag(EWidgetEventType EventType) const;`
- L81 _private prototype_ `bool& GetCategoryFlag(EWidgetEventType EventType);`
- L82 _private prototype_ `const UEnum* GetEnum(EWidgetEventType EventType) const;`
- L84 _private member_ `TWeakPtr<const SWidget> ReflectorWidget;`
- L85 _private member_ `FOnWidgetTokenActivated OnWidgetTokenActivated;`
- L87 _private member_ `TBitArray<> FocusEnabled;`
- L88 _private member_ `TBitArray<> InputEnabled;`
- L89 _private member_ `TBitArray<> NavigationEnabled;`
- L90 _private member_ `TBitArray<> CursorEnabled;`
- L91 _private member_ `bool bIsAllFocusEnabled;`
- L92 _private member_ `bool bIsAllInputEnabled;`
- L93 _private member_ `bool bIsAllNavigationEnabled;`
- L94 _private member_ `bool bIsAllCursorEnabled;`
- L96 _private member_ `bool bIsWarningEnabled;`
- L97 _private member_ `bool bIsCaptureStateEnabled;`
- L99 _private member_ `bool bFilterWidgetReflectorEvent;`

#### enum `SWidgetEventLog::EWidgetEventType`  
`enum class EWidgetEventType`  
_L27-35_
- L29 _public enumerator_ `Warning`
- L30 _public enumerator_ `Focus`
- L31 _public enumerator_ `Input`
- L32 _public enumerator_ `Navigation`
- L33 _public enumerator_ `Capture`
- L34 _public enumerator_ `Cursor`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetTokenActivated, TSharedPtr<const SWidget>);`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetHittestGrid.h` (Private)


#### class `SWidgetHittestGrid`  
`class SWidgetHittestGrid : public SCompoundWidget`  
_L37-113_
- inherits: `SCompoundWidget`
- L40 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetSelected, TSharedPtr<const SWidget>);`
- L41 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnVisualizeWidget, const FWidgetPath&);`
- L42 _public function_ `SLATE_BEGIN_ARGS(SWidgetHittestGrid)`
- L44 _public prototype_ `SLATE_EVENT(FOnWidgetSelected, OnWidgetSelected) SLATE_EVENT(FOnVisualizeWidget, OnVisualizeWidget) SLATE_END_ARGS() virtual ~SWidgetHittestGrid();`
- L50 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<const SWidget> InReflectorWidget);`
- L53 _public prototype_ `void SetPause(bool bNewPaused);` — Stop listening to new events
- L56 _private prototype_ `void LoadSettings();`
- L57 _private prototype_ `void SaveSettings();`
- L58 _private prototype_ `TSharedRef<SWidget> ConstructNavigationDetail() const;`
- L60 _private prototype_ `void HandleDrawDebuggerVisual(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, FSlateWindowElementList& InOutDrawElements, int32& InOutLayerId);`
- L61 _private prototype_ `void HandleFindNextFocusableWidget(const FHittestGrid* HittestGrid, const FHittestGrid::FDebuggingFindNextFocusableWidgetArgs& Info);`
- L63 _private prototype_ `FText GetDisplayButtonText() const;`
- L64 _private prototype_ `TSharedRef<SWidget> GetDisplayMenuContent();`
- L65 _private prototype_ `void HandleDisplayButtonClicked(TWeakPtr<SWindow> Window);`
- L66 _private prototype_ `void HandleDisplayAllClicked();`
- L67 _private prototype_ `bool HandleIsDisplayButtonChecked(TWeakPtr<SWindow> Window) const;`
- L68 _private function_ `bool HandleIsDisplayAllChecked() const`
- L70 _private prototype_ `TSharedRef<SWidget> GetFlagsMenuContent();`
- L71 _private prototype_ `void HandleDisplayFlagsButtonClicked(FHittestGrid::EDisplayGridFlags Flag);`
- L72 _private prototype_ `bool HandleIsDisplayFlagsButtonChecked(FHittestGrid::EDisplayGridFlags Flag) const;`
- L74 _private prototype_ `void HandleVisualizeOnNavigationChanged(ECheckBoxState InCheck);`
- L75 _private function_ `ECheckBoxState HandleGetVisualizeOnNavigationChecked() const`
- L77 _private prototype_ `void HandleRejectWidgetReflectorChanged(ECheckBoxState InCheck);`
- L78 _private function_ `ECheckBoxState HandleGetRejectWidgetReflectorChecked() const`
- L80 _private function_ `FText GetNavigationFromText() const`
- L81 _private function_ `FText GetNavigationResultText() const`
- L82 _private function_ `FText GetNavigationDirectionText() const`
- L83 _private function_ `FText GetNavigationUserIndexText() const`
- L84 _private function_ `FText GetNavigationRuleWidgetText() const`
- L85 _private function_ `FText GetNavigationBoundaryRuleText() const`
- L86 _private prototype_ `void HandleNavigationNavigate(TWeakPtr<const SWidget> WidgetToNavigate) const;`
- L88 _private prototype_ `TSharedRef<ITableRow> HandleWidgetHittestGridGenerateRow(TSharedRef<WidgetHittestGridInternal::FIntermediateResultNode> InReflectorNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L89 _private prototype_ `void HandleWidgetHittestGridSelectionChanged(TSharedPtr<WidgetHittestGridInternal::FIntermediateResultNode>, ESelectInfo::Type );`
- L92 _private member_ `FOnWidgetSelected OnWidgetSelected;`
- L93 _private member_ `FOnVisualizeWidget OnVisualizeWidget;`
- L94 _private member_ `TWeakPtr<const SWidget> ReflectorWidget;`
- L96 _private member_ `FHittestGrid::EDisplayGridFlags DisplayGridFlags;`
- L97 _private member_ `TWeakPtr<SWindow> WindowToDisplay;`
- L98 _private member_ `bool bDisplayAllWindows;`
- L99 _private member_ `bool bVisualizeOnNavigation;`
- L100 _private member_ `bool bRejectWidgetReflectorEvent;`
- L102 _private member_ `TSharedPtr<SWidgetHittestGridTree> NavigationIntermediateResultTree;`
- L103 _private member_ `TArray<TSharedRef<WidgetHittestGridInternal::FIntermediateResultNode>> IntermediateResultNodesRoot;`
- L104 _private member_ `FText NavigationFrom;`
- L105 _private member_ `FText NavigationResult;`
- L106 _private member_ `FText NavigationDirection;`
- L107 _private member_ `FText NavigationUserIndex;`
- L108 _private member_ `FText NavigationRuleWidget;`
- L109 _private member_ `FText NavigationBoundaryRule;`
- L110 _private member_ `TWeakPtr<const SWidget> NavigationFromWidget;`
- L111 _private member_ `TWeakPtr<const SWidget> NavigationFromResult;`
- L112 _private member_ `TWeakPtr<const SWidget> NavigationRuleWidgetWidget;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace WidgetHittestGridInternal`
- L32 _typedef_ `typedef SListView<TSharedRef<WidgetHittestGridInternal::FIntermediateResultNode>> SWidgetHittestGridTree;`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetSelected, TSharedPtr<const SWidget>);`
- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVisualizeWidget, const FWidgetPath&);`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetList.h` (Private)


#### class `SWidgetList`  
`class SWidgetList : public SCompoundWidget`  
_L14-41_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SWidgetList)`
- L23 _public prototype_ `void Construct(const FArguments& Args);`
- L26 _private prototype_ `void Refresh();`
- L27 _private prototype_ `void Sort();`
- L28 _private prototype_ `void OnSort(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L29 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FWidgetListEntry> Entry, const TSharedRef<STableViewBase>& Table) const;`
- L30 _private prototype_ `FReply ExportToCSV() const;`
- L33 _private member_ `TSharedPtr<SListView<TSharedPtr<FWidgetListEntry>>> ListView;`
- L34 _private member_ `TArray<TSharedPtr<FWidgetListEntry>> Entries;`
- L35 _private member_ `FAccessAsset OnAccessAsset;`
- L36 _private member_ `FAccessSourceCode OnAccessSource;`
- L37 _private member_ `int32 CurrentCount = 0;`
- L38 _private member_ `int32 PreviousCount = 0;`
- L39 _private member_ `FName SortColumn;`
- L40 _private member_ `bool bSortAscending = false;`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetReflector.h` (Private)


#### class `SWidgetReflector`  
`class SWidgetReflector : public SUserWidget , public IWidgetReflector`  
_L18-36_
- inherits: `SUserWidget,IWidgetReflector`
- desc: Widget reflector implementation. User widget to enable iteration without recompilation.
- L24 _public function_ `SLATE_USER_ARGS(SWidgetReflector)`
- L27 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_ARGUMENT(TSharedPtr<FWidgetSnapshotService>, WidgetSnapshotService) SLATE_END_ARGS() virtual void Construct( const FArguments& InArgs ) = 0;`
- L33 _public prototype_ `virtual ~SWidgetReflector() = default;`
- L35 _public prototype_ `virtual void UpdateColumnWidth(TSharedRef<FWidgetReflectorNodeBase> InItem, FName InColumn) = 0;`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetReflectorToolTipWidget.h` (Private)


#### class `SReflectorToolTipWidget`  
`class SReflectorToolTipWidget : public SCompoundWidget`  
_L12-116_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SReflectorToolTipWidget) : _WidgetInfoToVisualize()`
- L28 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L32 _private prototype_ `FText GetWidgetsSourceName() const;`
- L34 _private function_ `FText GetWidgetsDesiredSize() const`
- L39 _private function_ `FText GetWidgetActualSize() const`
- L44 _private function_ `FText GetSizeInfo() const`
- L49 _private function_ `FText GetEnabled() const`
- L54 _private function_ `FText GetNeedsTick() const`
- L59 _private function_ `FText GetIsVolatile() const`
- L64 _private function_ `FText GetIsVolatileIndirectly() const`
- L69 _private function_ `FText GetHasActiveTimers() const`
- L74 _private prototype_ `FText GetLiveAttributeName() const;`
- L76 _private function_ `FText GetAttributeCount() const`
- L81 _private function_ `FText GetCollapsedAttributeCount() const`
- L86 _private function_ `FText GetIsVisible() const`
- L91 _private function_ `FText GetIsVisibleInherited() const`
- L96 _private function_ `FText GetSupportsInvalidation() const`
- L101 _private function_ `FText GetSupportsInvalidationRecursive() const`
- L108 _private member_ `static const FText TrueText;`
- L109 _private member_ `static const FText FalseText;`
- L112 _private member_ `TSharedPtr<FWidgetReflectorNodeBase> WidgetInfo;` — The info about the widget that we are visualizing.
- L115 _private member_ `FText SizeInfoText;` — The size info text

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "SReflectorToolTipWidget"`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetReflectorTreeWidgetItem.h` (Private)


#### class `SReflectorTreeWidgetItem`  
`class SReflectorTreeWidgetItem : public SMultiColumnTableRow<TSharedRef<FWidgetReflectorNodeBase>>`  
_L19-93_
- inherits: `SMultiColumnTableRow<TSharedRef<FWidgetReflectorNodeBase>>`
- desc: Widget that visualizes the contents of a FReflectorNode.
- L24 _public member_ `static FName NAME_WidgetName;`
- L25 _public member_ `static FName NAME_WidgetInfo;`
- L26 _public member_ `static FName NAME_Visibility;`
- L27 _public member_ `static FName NAME_Focusable;`
- L28 _public member_ `static FName NAME_Enabled;`
- L29 _public member_ `static FName NAME_Volatile;`
- L30 _public member_ `static FName NAME_HasActiveTimer;`
- L31 _public member_ `static FName NAME_Clipping;`
- L32 _public member_ `static FName NAME_LayerId;`
- L33 _public member_ `static FName NAME_ForegroundColor;`
- L34 _public member_ `static FName NAME_Address;`
- L35 _public member_ `static FName NAME_ActualSize;`
- L37 _public function_ `SLATE_BEGIN_ARGS(SReflectorTreeWidgetItem) : _WidgetReflector() , _WidgetInfoToVisualize() , _SourceCodeAccessor() , _AssetAccessor()`
- L58 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L63 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — SMultiColumnTableRow overrides
- L71 _protected function_ `FSlateColor GetTint() const` — @return The tint of the reflector node
- L76 _protected prototype_ `void HandleHyperlinkNavigate(bool bAttemptClassDebug);`
- L78 _protected prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn_Internal(const FName& ColumnName);`
- L80 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L83 _private member_ `TWeakPtr<SWidgetReflector> WidgetReflectorWeak;`
- L86 _private member_ `TSharedPtr<FWidgetReflectorNodeBase> WidgetInfo;` — The info about the widget that we are visualizing.
- L88 _private member_ `FAccessSourceCode OnAccessSourceCode;`
- L89 _private member_ `FAccessAsset OnAccessAsset;`
- L90 _private member_ `FAccessDebugObject OnAccessDebugObject;`
- L92 _private member_ `mutable TSet<FName> ColumnsToUpdate;`

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetSearchPanel.h` (Private)


#### class `UE::SlateReflector::SWidgetSearchPanel`  
`class SWidgetSearchPanel : public SCompoundWidget`  
_L28-96_
- inherits: `SCompoundWidget`
- desc: A panel that allows searching the widget hierarchy by type, description, tag, and address. Displays matching widgets in a list view; selecting an entry focuses it in the Widget Hierarchy. Two search scopes are available via a checkbox: - Current tree root  : searches the nodes currently shown in the Widget Hierarchy. - All live widgets   : builds a transient FWidgetReflectorNodeBase tree from every visible SWindow so that widgets outside the current pick scope can be found.
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectNode, TSharedRef<FWidgetReflectorNodeBase>);` — Called when the user selects a result that belongs to the current tree root.
- L36 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectLiveWidget, TSharedPtr<const SWidget>);` — Called when the user selects a result in "all live widgets" mode; passes the live SWidget so the hierarchy can locate it even if the tree root hasn't been set for that window yet.
- L39 _public prototype_ `DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FWidgetReflectorNodeBase>>, FGetRootNodes);` — Called to obtain the current root nodes (live or snapshot) at the time of search.
- L41 _public function_ `SLATE_BEGIN_ARGS(SWidgetSearchPanel)`
- L42 _public prototype_ `SLATE_EVENT(FOnSelectNode, OnSelectNode) SLATE_EVENT(FOnSelectLiveWidget, OnSelectLiveWidget) SLATE_EVENT(FGetRootNodes, OnGetRootNodes) SLATE_EVENT(FAccessSourceCode, OnAccessSourceCode) SLATE_EVENT(FAccessAsset, OnAccessAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L65 _private prototype_ `FReply HandleSearchClicked();`
- L68 _private prototype_ `TArray<TSharedRef<FWidgetReflectorNodeBase>> BuildSearchRoots() const;` — Build search roots: either the current tree root or a fresh live tree from all windows.
- L70 _private prototype_ `void SearchNodes(const TArray<TSharedRef<FWidgetReflectorNodeBase>>& InNodes, const FSearchFilters& Filters);`
- L71 _private prototype_ `bool NodeMatchesFilters(const TSharedRef<FWidgetReflectorNodeBase>& Node, const FSearchFilters& Filters) const;`
- L73 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FWidgetSearchResultEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L74 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FWidgetSearchResultEntry> Item, ESelectInfo::Type SelectType);`
- L77 _private prototype_ `bool IsAllLiveWidgetsMode() const;` — Returns true if the "Search all live widgets" checkbox is currently checked.
- L79 _private member_ `TSharedPtr<SEditableTextBox> TypeSearchBox;`
- L80 _private member_ `TSharedPtr<SEditableTextBox> DescSearchBox;`
- L81 _private member_ `TSharedPtr<SEditableTextBox> TagSearchBox;`
- L82 _private member_ `TSharedPtr<SEditableTextBox> AddressSearchBox;`
- L84 _private member_ `TSharedPtr<SCheckBox> AllLiveWidgetsCheckBox;`
- L86 _private member_ `TArray<TSharedRef<FWidgetReflectorNodeBase>> LastSearchRoots;`
- L88 _private member_ `TArray<TSharedPtr<FWidgetSearchResultEntry>> SearchResults;`
- L89 _private member_ `TSharedPtr<SListView<TSharedPtr<FWidgetSearchResultEntry>>> ResultListView;`
- L91 _private member_ `FOnSelectNode OnSelectNode;`
- L92 _private member_ `FOnSelectLiveWidget OnSelectLiveWidget;`
- L93 _private member_ `FGetRootNodes OnGetRootNodes;`
- L94 _private member_ `FAccessSourceCode OnAccessSourceCode;`
- L95 _private member_ `FAccessAsset OnAccessAsset;`

#### struct `UE::SlateReflector::SWidgetSearchPanel::FSearchFilters`  
`struct FSearchFilters`  
_L52-63_
- L54 _public member_ `FString DisplayName;`
- L55 _public member_ `FString Type;`
- L56 _public member_ `FString Tag;`
- L57 _public member_ `FString Address;`
- L59 _public function_ `bool IsEmpty() const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SlateReflector` (scope `UE`)
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectNode, TSharedRef<FWidgetReflectorNodeBase>);` — Called when the user selects a result that belongs to the current tree root.
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectLiveWidget, TSharedPtr<const SWidget>);` — Called when the user selects a result in "all live widgets" mode; passes the live SWidget so the hierarchy can locate it even if the tree root hasn't been set for that window yet.
- L39 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FWidgetReflectorNodeBase>>, FGetRootNodes);` — Called to obtain the current root nodes (live or snapshot) at the time of search.

### `Source/Developer/SlateReflector/Private/Widgets/SWidgetSnapshotVisualizer.h` (Private)


#### struct `FWidgetSnapshotTextureData`  
`struct FWidgetSnapshotTextureData`  
_L23-30_
- desc: The raw texture data from taking a screenshot of a Slate widget (typically the root window)
- L26 _public member_ `FIntVector Dimensions;` — The dimensions of the texture
- L29 _public member_ `TArray<FColor> ColorData;` — The raw color data for the texture (BGRA)

#### struct `FWidgetSnapshotNavigationSimulationData`  
`struct FWidgetSnapshotNavigationSimulationData`  
_L36-39_
- desc: The data of a Navigation Event Simulation
- L38 _public member_ `TArray<FNavigationSimulationWidgetNodePtr> SimulationData;`

#### class `FWidgetSnapshotData`  
`class FWidgetSnapshotData`  
_L44-125_
- desc: All of the data relating to a single widget hierarchy snapshot
- L48 _public prototype_ `~FWidgetSnapshotData();` — Destructor
- L51 _public prototype_ `void ClearSnapshot();` — Clear the current snapshot data so that we can reclaim the memory
- L54 _public prototype_ `void TakeSnapshot(bool bSimulateNavigation);` — Take a snapshot of all of the windows that are currently open
- L57 _public prototype_ `void CreateSnapshot(const TArray<TSharedRef<SWindow>>& VisibleWindows, bool bSimulateNavigation);` — Create a snapshot of the given windows
- L60 _public prototype_ `bool SaveSnapshotToFile(const FString& InFilename) const;` — Save this snapshot data to the given file. The data will be saved as uncompressed JSON data.
- L63 _public prototype_ `void SaveSnapshotToBuffer(TArray<uint8>& OutData) const;` — Save this snapshot data to the given buffer. The data will be saved as zlib compressed JSON data.
- L66 _public prototype_ `TSharedRef<FJsonObject> SaveSnapshotAsJson() const;` — Create a JSON object that represents the snapshot data.
- L69 _public prototype_ `bool LoadSnapshotFromFile(const FString& InFilename);` — Populate this snapshot data from the given file.
- L72 _public prototype_ `void LoadSnapshotFromBuffer(const TArray<uint8>& InData);` — Populate this snapshot data from the given buffer.
- L75 _public prototype_ `void LoadSnapshotFromJson(const TSharedRef<FJsonObject>& InRootJsonObject);` — Populate this snapshot data from the given JSON object
- L78 _public prototype_ `bool IsEmpty() const;` — Check to see whether this snapshot is empty (contains no windows)
- L81 _public prototype_ `int32 Num() const;` — Get the number of windows this snapshot contains
- L84 _public prototype_ `const TArray<TSharedPtr<FWidgetReflectorNodeBase>>& GetWindowsPtr() const;` — Get the internal windows array
- L87 _public prototype_ `TArray<TSharedRef<FWidgetReflectorNodeBase>> GetWindowsRef() const;` — Get the internal windows array, but with each window converted to a TSharedRef
- L90 _public prototype_ `TSharedPtr<FWidgetReflectorNodeBase> GetWindow(const int32 WindowIndex) const;` — Get the window for the given index, or null if the index is invalid
- L93 _public prototype_ `const FWidgetSnapshotNavigationSimulationData& GetNavigationSimulation(const int32 WindowIndex) const;` — Get the navigation simulation for the given index, or null if the index is invalid or not navigation data was created
- L96 _public prototype_ `const FSlateBrush* GetBrush(const int32 WindowIndex) const;` — Get the brush for the given index, or null if the index is invalid
- L100 _private prototype_ `void CreateBrushes();` — Create the dynamic Slate brushes from the texture data for each window
- L103 _private prototype_ `void DestroyBrushes();` — Destroy the dynamic Slate brushes for each window
- L106 _private prototype_ `void Reserve(const int32 NumWindows);` — Reserve space in all of our internal arrays for the given number of entries
- L109 _private prototype_ `void Reset();` — Reset our internal arrays
- L112 _private member_ `TArray<TSharedPtr<FWidgetReflectorNodeBase>> Windows;` — Array of root level windows, each containing a tree of widget nodes
- L115 _private member_ `TArray<FWidgetSnapshotNavigationSimulationData> NavigationSimulationData;` — Contains the simulation data entry for each entry  in Windows
- L118 _private member_ `TArray<FWidgetSnapshotTextureData> WindowTextureData;` — Contains a texture data entry for each entry in Windows
- L121 _private member_ `TArray<TSharedPtr<FSlateDynamicImageBrush>> WindowTextureBrushes;` — Contains a dynamic brush pointer for each entry in WindowTextureData
- L124 _private member_ `FWidgetSnapshotNavigationSimulationData EmptyNavigationSimulationData;` — For the list, there must always be a valid array of simulation data.

#### class `SWidgetSnapshotVisualizer`  
`class SWidgetSnapshotVisualizer : public SCompoundWidget`  
_L130-203_
- inherits: `SCompoundWidget`
- desc: Visualizer to handle viewing and picking from a widget hierarchy snapshot
- L133 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnWidgetPathPicked, const TArray<TSharedRef<FWidgetReflectorNodeBase>>& );`
- L134 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSnapshotWidgetAction, FWidgetReflectorNodeBase::TPointerAsInt);`
- L136 _public function_ `SLATE_BEGIN_ARGS(SWidgetSnapshotVisualizer) : _SnapshotData(nullptr)`
- L140 _public prototype_ `SLATE_ARGUMENT(const FWidgetSnapshotData*, SnapshotData) SLATE_EVENT(FOnWidgetPathPicked, OnWidgetPathPicked) SLATE_EVENT(FOnSnapshotWidgetAction, OnSnapshotWidgetSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L150 _public prototype_ `void SnapshotDataUpdated();` — Called when the snapshot data we're observing is changed. This allows us to update our view.
- L153 _public prototype_ `void SetSelectedWidgets(const TArray<TSharedRef<FWidgetReflectorNodeBase>>& InSelectedWidgets);` — Called to update the list of selected widgets
- L156 _public prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L160 _private prototype_ `void OnWindowSelectionChanged(TSharedPtr<FWidgetReflectorNodeBase> InWindow, ESelectInfo::Type InReason);` — Called when the selected window is changed in the combo box. Used to update our view.
- L163 _private prototype_ `static FText GetWindowPickerComboItemText(TSharedPtr<FWidgetReflectorNodeBase> InWindow);` — Get the combo item text to use for the given window
- L166 _private prototype_ `FText GetSelectedWindowComboItemText() const;` — Get the combo item text for the currently selected window
- L169 _private prototype_ `TSharedRef<SWidget> GenerateWindowPickerComboItem(TSharedPtr<FWidgetReflectorNodeBase> InWindow) const;` — Create a widget for the items in the window picker combo box
- L172 _private prototype_ `FText GetPickWidgetText() const;` — Get the current text to use for the "Pick Snapshot Widget" button
- L175 _private prototype_ `ECheckBoxState GetPickWidgetColor() const;` — Get the current check state to use for the "Pick Snapshot Widget" button
- L178 _private prototype_ `void OnPickWidgetClicked();` — Called when the "Pick Snapshot Widget" button is clicked
- L181 _private prototype_ `bool HasValidSnapshot() const;` — Is there any snapshot data to save, visualized...
- L184 _private prototype_ `EVisibility HandleGetNavigationSimulationListVisibility() const;` — Should we show the Navigation Event Simulation List.
- L188 _private prototype_ `void OnSaveSnapshotClicked();` — Called when the "Save Snapshot" button is clicked
- L193 _private member_ `const FWidgetSnapshotData* SnapshotDataPtr;` — Snapshot data we're visualizing
- L196 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FWidgetReflectorNodeBase>>> WindowPickerCombo;` — Window picker combo box
- L199 _private member_ `TSharedPtr<SScrollableSnapshotImage> SnapshotImage;` — Snapshot image
- L202 _private member_ `TSharedPtr<SNavigationSimulationSnapshotList> NavigationSimulationList;` — Navigation Simulation list

#### Free symbols / members of external scopes

- L133 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetPathPicked, const TArray<TSharedRef<FWidgetReflectorNodeBase>>& );`
- L134 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSnapshotWidgetAction, FWidgetReflectorNodeBase::TPointerAsInt);`

### `Source/Developer/SlateReflector/Public/INavigationEventSimulationView.h` (Public)


#### class `INavigationEventSimulationView`  
`class INavigationEventSimulationView : public SCompoundWidget`  
_L11-20_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(INavigationEventSimulationView)`
- L15 _public prototype_ `SLATE_END_ARGS() virtual void SetSimulationResult(TArray<FSlateNavigationEventSimulator::FSimulationResult> SimulationResult) = 0;`
- L18 _public prototype_ `virtual void SelectWidget(const TSharedPtr<SWidget>& Widget) = 0;`
- L19 _public prototype_ `virtual int32 PaintSimuationResult(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) = 0;`

### `Source/Developer/SlateReflector/Public/ISlateReflectorModule.h` (Public)


#### struct `FNavigationEventSimulationViewArgs`  
`struct FNavigationEventSimulationViewArgs`  
_L16-20_
- L18 _public member_ `FSimpleWidgetDelegate OnWidgetSelected;`
- L19 _public member_ `FSimpleWidgetDelegate OnNavigateToWidget;`

#### class `ISlateReflectorModule`  
`class ISlateReflectorModule : public IModuleInterface`  
_L25-65_
- inherits: `IModuleInterface`
- desc: Interface for messaging modules.
- L33 _public prototype_ `virtual void DisplayWidgetReflector() = 0;` — Display the widget reflector, either spawned from a tab manager, or in a new window if the tab manager can't be used
- L38 _public prototype_ `virtual void DisplayTextureAtlasVisualizer() = 0;` — Display the texture atlas visualizer, either spawned from a tab manager, or in a new window if the tab manager can't be used
- L43 _public prototype_ `virtual void DisplayFontAtlasVisualizer() = 0;` — Display the texture atlas visualizer, either spawned from a tab manager, or in a new window if the tab manager can't be used
- L50 _public prototype_ `virtual void RegisterTabSpawner( const TSharedPtr<FWorkspaceItem>& WorkspaceGroup ) = 0;` — Registers a tab spawner for the widget reflector. @param WorkspaceGroup The workspace group to insert the tab into.
- L53 _public prototype_ `virtual void UnregisterTabSpawner() = 0;` — Unregisters the tab spawner for the widget reflector.
- L56 _public prototype_ `virtual FSlateNavigationEventSimulator* GetNavigationEventSimulator() const = 0;` — Get the Navigation Event Simulator used by the widget reflector.
- L59 _public prototype_ `virtual TSharedRef<INavigationEventSimulationView> CreateNavigationEventSimulationView(const FNavigationEventSimulationViewArgs& DetailsViewArgs) = 0;` — Create a widget to visualize the result of a Navigation Event Simulation.
- L64 _public prototype_ `virtual ~ISlateReflectorModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FSimpleWidgetDelegate, TWeakPtr<const SWidget>);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FSimpleWidgetDelegate, TWeakPtr<const SWidget>);`

### `Source/Developer/SlateReflector/Public/SlateNavigationEventSimulator.h` (Public)


#### class `FSlateNavigationEventSimulator`  
`class FSlateNavigationEventSimulator`  
_L41-130_
- desc: Simulate navigation attempt and collect the result for later display. Some elements may steel the navigation attempt dynamically and can be evaluated until evaluated in game. A list of elements that can still the navigation attempt and modify the result. 1. The viewport may consume the Navigation. 2. A widget may override the OnNavigation function and return a different result dynamically. 3. A widget can change its "enabled" and "supports keyboard focus" flags dynamically during gameplay. 4. The GameViewportClient may consume the event via the CustomNavigationEvent. 5. The application or a widget can consume the "set focus" event. Resulting in different behavior.
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<FWidgetPath>, FHandleNavigation, uint32 , const TSharedPtr<SWidget>& );`
- L51 _public prototype_ `static FText ToText(ENavigationStyle NavigationStyle);`
- L59 _public prototype_ `static FText ToText(ERoutedReason RoutedReason);`
- L113 _public prototype_ `TArray<FSimulationResult> SimulateForEachWidgets(const FWidgetPath& WidgetPath, int32 UserIndex, ENavigationGenesis Genesis, ENavigationStyle Navigation);` — Simulate for each widgets that are enabled and support keyboard focus
- L114 _public prototype_ `TArray<FSimulationResult> SimulateForEachWidgets(const TSharedRef<SWindow>& Window, int32 UserIndex, ENavigationGenesis Genesis, ENavigationStyle Navigation);`
- L115 _public prototype_ `TArray<FSimulationResult> SimulateForEachWidgets(const FWidgetPath& WidgetPath, int32 UserIndex, ENavigationGenesis Genesis, EUINavigation Navigation);`
- L116 _public prototype_ `TArray<FSimulationResult> SimulateForEachWidgets(const TSharedRef<SWindow>& Window, int32 UserIndex, ENavigationGenesis Genesis, EUINavigation Navigation);`
- L121 _public prototype_ `TArray<FSimulationResult> Simulate(const FWidgetPath& WidgetPath, int32 UserIndex, ENavigationGenesis Genesis, ENavigationStyle Navigation);` — Simulate a navigation event for a widget
- L122 _public prototype_ `FSimulationResult Simulate(const FWidgetPath& WidgetPath, int32 UserIndex, ENavigationGenesis Genesis, EUINavigation Navigation);`
- L126 _public member_ `FHandleNavigation OnViewportHandleNavigation;` — Once the destination widget has been decided, the viewport may handled the event.
- L129 _private prototype_ `FSimulationResult InterpretResult(const FWidgetPath& WidgetPath, const FNavigationEvent& NavigationEvent, const FNavigationReply& Reply, const FArrangedWidget& BoundaryWidget);`

#### enum `FSlateNavigationEventSimulator::ENavigationStyle`  
`enum class ENavigationStyle`  
_L46-50_
- L48 _public enumerator_ `FourCardinalDirections`
- L49 _public enumerator_ `ConceptualNextAndPrevious`

#### enum `FSlateNavigationEventSimulator::ERoutedReason`  
`enum class ERoutedReason`  
_L53-58_
- L55 _public enumerator_ `BoundaryRule`
- L56 _public enumerator_ `Window`
- L57 _public enumerator_ `LastWidget`

#### struct `FSlateNavigationEventSimulator::FSimulatedReply`  
`struct FSimulatedReply`  
_L61-69_
- L63 _public prototype_ `FSimulatedReply() = default;`
- L64 _public prototype_ `FSimulatedReply(const FNavigationReply&);`
- L66 _public member_ `TSharedPtr<SWidget> EventHandler;`
- L67 _public member_ `TSharedPtr<SWidget> FocusRecipient;`
- L68 _public member_ `EUINavigationRule BoundaryRule;`

#### struct `FSlateNavigationEventSimulator::FSimulationResult`  
`struct FSimulationResult`  
_L71-107_
- L74 _public member_ `FWidgetPath NavigationSource;` — From where the navigation started.
- L77 _public member_ `FWidgetPath NavigationDestination;` — The result of the navigation simulation.
- L80 _public member_ `EUINavigation NavigationType = EUINavigation::Invalid;` — The navigation type
- L83 _public member_ `FSimulatedReply NavigationReply;` — The reply of received from the routed widget.
- L86 _public member_ `ERoutedReason RoutedReason = ERoutedReason::LastWidget;` — The reason we choose that boundary widget.
- L89 _public member_ `TSharedPtr<SWidget> WidgetThatShouldReceivedFocus;` — Base on the boundary rule, the widget that should receive the focus.
- L92 _public member_ `TSharedPtr<SWidget> FocusedWidgetPath;` — The widget that will received the focus.
- L95 _public member_ `bool bIsDynamic = false;` — Can not return a result since it would involve calling a dynamic callback.
- L97 _public member_ `bool bAlwaysHandleNavigationAttempt = false;` — The event is handle, even if the destination widget is nullptr or the Viewport->HandleNavigation return false.
- L99 _public member_ `bool bCanFindWidgetForSetFocus = false;` — Was able to find the widget to focus.
- L101 _public member_ `bool bRoutedHandlerHasNavigationMeta = false;` — Does the routed widget has navigation meta data.
- L103 _public member_ `bool bHandledByViewport = false;` — Handled by the viewport. See OnViewportHandleNavigation.
- L105 _public function_ `bool IsHandled() const`
- L106 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SLATEREFLECTOR_API`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<FWidgetPath>, FHandleNavigation, uint32 , const TSharedPtr<SWidget>& );`
