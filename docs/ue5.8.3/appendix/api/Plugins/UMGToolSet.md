# Plugins / UMGToolSet

- module root: `Plugins/Experimental/Toolsets/UMGToolSet/Source/UMGToolSet`
- headers: 2; symbols: 73
- symbol kinds: class=2, member=35, prototype=27, struct=9
- PrivateDependencyModuleNames: AssetRegistry, BlueprintGraph, Kismet, MessageLog, MovieScene, MovieSceneTracks, Slate, SlateCore, UMGEditor, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, ToolsetRegistry, UMG

### `Plugins/Experimental/Toolsets/UMGToolSet/Source/UMGToolSet/Private/UMGToolSet.h` (Private)


#### struct `FUMGUIComponentInfo`  
`struct FUMGUIComponentInfo`  
_L22-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: Info for a single UI component attached to a widget instance.
- L33 _public member_ `TObjectPtr<UUIComponent> Component = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — The component archetype instance. Use ObjectTools to read/write its properties. 1. ObjectTools.list_properties(Component) -> get exact property names 2. ObjectTools.get_properties(Component, [names]) -> read current values 3. ObjectTools.set_properties(Component, {name: value}) -> write values
- L37 _public member_ `FSoftClassPath ComponentClassPath;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Class path for this component. Pass directly to AddUIComponent, RemoveUIComponent, or MoveUIComponent as ComponentClass.

#### struct `FUMGWidgetInfo`  
`struct FUMGWidgetInfo`  
_L58-97_
- reflection: `USTRUCT(BlueprintType)`
- desc: Widget info with hierarchy pointers. Returned by all widget query and creation functions. All TObjectPtr fields serialize as {"refPath": "..."} - pass them directly back to other functions. Reading properties: 1. ObjectTools.list_properties(Widget) -> get exact property names 2. ObjectTools.get_properties(Widget, [names]) -> read current values 3. ObjectTools.set_properties(Widget, {name: value}) -> write values Do the same for the Slot pointer to set padding, alignment, anchors, etc. Get property names via ObjectTools.list_properties - they vary per widget class. Hierarchy context: - Parent set        -> widget was added as a child of this panel - NamedSlotHost set -> widget is named slot content on this host - Both null         -> root widget - bInherited true   -> defined in the C++ parent class, not user-created
- L64 _public member_ `TObjectPtr<UWidget> Widget = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — The widget instance. Pass to AddWidget as parent, ObjectTools for properties.
- L68 _public member_ `TObjectPtr<UPanelWidget> Parent = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Parent panel widget. nullptr when this is the root widget or when this widget lives in a named slot (check NamedSlotHost instead).
- L72 _public member_ `TObjectPtr<UPanelSlot> Slot = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Panel slot for this widget. Pass to ObjectTools to read/write slot properties (padding, alignment, anchors, etc.). nullptr for root widget.
- L76 _public member_ `TObjectPtr<UWidget> NamedSlotHost = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Named slot host. If set, this widget is named slot content - use SetNamedSlotContent with this host instead of AddWidget. Call GetNamedSlots to find the slot name.
- L80 _public member_ `FSoftClassPath WidgetClassPath;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Class path for this widget. Pass directly to AddWidget or SetNamedSlotContent WidgetClass param.
- L84 _public member_ `FName WidgetName;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Widget instance name.
- L88 _public member_ `bool bIsVariable = false;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Whether this widget is exposed as a blueprint variable.
- L92 _public member_ `bool bInherited = false;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — True if this widget is inherited from the C++ parent class.
- L96 _public member_ `TArray<FUMGUIComponentInfo> UIComponents;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — UI components attached to this widget, in display order. Pass ComponentClass entries back to AddUIComponent / RemoveUIComponent / MoveUIComponent.

#### struct `FUMGNamedSlotEntry`  
`struct FUMGNamedSlotEntry`  
_L101-116_
- reflection: `USTRUCT(BlueprintType)`
- desc: Named slot binding entry. Returned by GetNamedSlots.
- L107 _public member_ `FName SlotName;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Slot name (e.g., "content", "header").
- L111 _public member_ `TObjectPtr<UWidget> HostWidget = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Host widget that owns the slot. nullptr = inherited from parent class.
- L115 _public member_ `TObjectPtr<UWidget> ContentWidget = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Root widget placed in the slot.

#### struct `FUMGWidgetBlueprintInfo`  
`struct FUMGWidgetBlueprintInfo`  
_L120-143_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint-level info. Part of FUMGWidgetTreeInfo returned by GetWidgets.
- L126 _public member_ `TSubclassOf<UUserWidget> ParentClass;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Parent class of this widget blueprint. Pass directly to CreateWidgetBlueprint's ParentClass param.
- L130 _public member_ `TSubclassOf<UWidget> RootWidgetClass;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Root widget class.
- L134 _public member_ `int32 WidgetCount = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Total widget count in the tree.
- L138 _public member_ `int32 InheritedWidgetCount = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Number of inherited widgets (from C++ parent class).
- L142 _public member_ `int32 NamedSlotCount = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Number of named slot bindings.

#### struct `FUMGWidgetTreeInfo`  
`struct FUMGWidgetTreeInfo`  
_L147-158_
- reflection: `USTRUCT(BlueprintType)`
- desc: Combined result from GetWidgets: blueprint info + full widget tree.
- L153 _public member_ `FUMGWidgetBlueprintInfo Info;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Blueprint-level info: parent class, root widget class, counts.
- L157 _public member_ `TArray<FUMGWidgetInfo> Widgets;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — All widgets in depth-first order. Parent pointer indicates hierarchy.

#### struct `FUMGWidgetDescriptionResult`  
`struct FUMGWidgetDescriptionResult`  
_L162-173_
- reflection: `USTRUCT(BlueprintType)`
- desc: Return value of GetWidgetDescription.
- L168 _public member_ `FString Description;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Human-readable tree. Each line is prefixed [N] where N is the 0-based index into Widgets.
- L172 _public member_ `TArray<FUMGWidgetInfo> Widgets;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Flat walk-order list. result.Widgets[N] corresponds to line [N] in Description. Same entries as GetWidgets.

#### struct `FUMGWidgetClassEntry`  
`struct FUMGWidgetClassEntry`  
_L177-196_
- reflection: `USTRUCT(BlueprintType)`
- desc: Widget class entry for ListWidgetClasses and GetWidgetClassInfo.
- L183 _public member_ `TSubclassOf<UWidget> WidgetClass;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — The widget class.
- L187 _public member_ `bool bIsPanel = false;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Whether this class is a panel (can have children).
- L191 _public member_ `FText Category;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Category for this widget class.
- L195 _public member_ `FText Description;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Description for this widget class that may contain more information on how the Widget is used and when to use it.

#### struct `FWidgetUnmatchedMember`  
`struct FWidgetUnmatchedMember`  
_L204-215_
- reflection: `USTRUCT(BlueprintType)`
- desc: One member (property or function) on the old widget class that has no compatible counterpart on the new class, paired with a human-readable explanation: "no member of that name on the new class" vs "name exists but the type/signature is incompatible".
- L210 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Name of the member on the old class.
- L214 _public member_ `FText Reason;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Reason this member couldn't be matched on the new class (missing name or type/signature mismatch).

#### struct `FWidgetReplacementReport`  
`struct FWidgetReplacementReport`  
_L226-253_
- reflection: `USTRUCT(BlueprintType)`
- desc: Result of ReplaceWidgetWithTemplate. Carries success/error state plus the lists of public members on the old widget that don't have a compatible counterpart on the new widget class. Each list is split into "still referenced in the outer blueprint" (BP graphs, bindings, animation property tracks, extension bindings) and the broader "all unmatched" set so callers can warn the user about references that will dangle. Every entry carries the per-member reason.
- L232 _public member_ `bool bSuccess = false;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — True if the replacement was performed.
- L236 _public member_ `FText MissingReferencesWarning;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — List of referenced properties/functions that are missing from the new class.
- L240 _public member_ `TArray<FWidgetUnmatchedMember> UnmatchedProperties;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Blueprint-visible properties on the old class that are missing or type-incompatible on the new class, with per-member reasons.
- L244 _public member_ `TArray<FWidgetUnmatchedMember> UnmatchedReferencedProperties;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Subset of UnmatchedProperties that the outer blueprint references through this widget (graphs, bindings, animation property tracks).
- L248 _public member_ `TArray<FWidgetUnmatchedMember> UnmatchedFunctions;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — BlueprintCallable / BlueprintEvent functions and multicast delegates on the old class that are missing or signature-incompatible on the new class, with per-member reasons.
- L252 _public member_ `TArray<FWidgetUnmatchedMember> UnmatchedReferencedFunctions;` — `UPROPERTY(BlueprintReadOnly, Category = "UMGToolSet")` — Subset of UnmatchedFunctions that the outer blueprint's graphs currently reference through this widget.

#### class `UUMGToolSet`  
`class UUMGToolSet : public UToolsetDefinition`  
_L273-542_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UToolsetDefinition`
- desc: UMG widget toolset for AI-driven widget creation and tree manipulation. IMPORTANT WORKFLOW - for every widget and slot returned by this toolset: 1. Call ObjectTools.list_properties(widget) to discover exact property names. 2. Call ObjectTools.get_properties(widget, [...]) with those exact names. 3. Call ObjectTools.set_properties(widget, {...}) with those exact names. Property names vary per widget class and CANNOT be guessed - list_properties is required. Skipping step 1 causes set_properties to silently fail or set wrong properties. Returns UObject pointers - ToolsetRegistry serializes them as {"refPath": "..."} automatically. Pass returned Widget, Slot, and Parent pointers directly to ObjectTools or back to this toolset.
- L287 _public prototype_ `static UWidgetBlueprint* CreateWidgetBlueprint(const FString& FolderPath, const FString& AssetName, TSubclassOf<UUserWidget> ParentClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Creation")` — Creates a new Widget Blueprint asset. Returns the blueprint or nullptr on failure. @param FolderPath Content folder path, e.g. "/Game/UI/Widgets". @param AssetName Name for the new blueprint asset. @param ParentClass The parent UUserWidget class. Get this from GetWidgets Info.ParentClass on the source blueprint.
- L300 _public prototype_ `static FUMGWidgetInfo AddWidget(UWidgetBlueprint* WidgetBlueprint, TSubclassOf<UWidget> WidgetClass, const FString& WidgetDisplayName, UWidget* ParentWidget = nullptr, int32 ChildIndex = -1);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Creation")` — Adds a widget to the tree at the specified position. Returns full widget info including Slot pointer. When ParentWidget is null and no root exists, the new widget becomes the root of the tree. Use ObjectTools.list_properties on the returned Widget and Slot to get property names before calling set_properties. @param WidgetBlueprint The widget blueprint to modify. @param WidgetClass The widget class to instantiate. @param WidgetDisplayName Display name for the new widget instance. @param ParentWidget The panel widget to add to. Pass null to add to root, or to make this widget the root if the tree is empty. @param ChildIndex Position in parent's child list (0 = first child). -1 (default) appends to end.
- L311 _public prototype_ `static FUMGWidgetInfo SetNamedSlotContent(UWidgetBlueprint* WidgetBlueprint, UWidget* HostWidget, FName SlotName, TSubclassOf<UWidget> WidgetClass, FName WidgetName);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Creation")` — Sets content for a named slot. Returns full widget info including Slot pointer. @param WidgetBlueprint The widget blueprint to modify. @param HostWidget The widget that owns the named slot, or null to target the root WidgetTree. @param SlotName Name of the slot to fill (e.g., "content", "header"). @param WidgetClass The widget class to place in the slot. @param WidgetName Name for the new widget instance.
- L323 _public prototype_ `static FUMGWidgetTreeInfo GetWidgets(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Query")` — Returns blueprint info and all widgets in depth-first order. Children within each parent are in their panel slot order - this is the hierarchy order shown in the designer. Info contains ParentClass (pass to CreateWidgetBlueprint) and RootWidgetClass. Use ObjectTools.list_properties on each returned Widget and Slot to get property names before calling set_properties. @param WidgetBlueprint The widget blueprint asset (e.g. "/Game/UI/WBP_MyWidget"), excluding the "_C" suffix.
- L330 _public prototype_ `static TArray<FUMGNamedSlotEntry> GetNamedSlots(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Query")` — Returns named slot bindings (separate from tree hierarchy). @param WidgetBlueprint The widget blueprint to query.
- L337 _public prototype_ `static TArray<FSoftObjectPath> ListWidgetBlueprints(const FString& FolderPath);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Query")` — Lists widget blueprints in a content folder. @param FolderPath Content folder to search, e.g. "/Game/UI". Searches recursively.
- L344 _public prototype_ `static TArray<FUMGWidgetClassEntry> ListWidgetClasses(const FString& Filter = TEXT(""));` — `UFUNCTION(meta = (AICallable), Category = "UMG|Query")` — Lists available widget classes, optionally filtered by name substring. @param Filter Substring to match against class names. Pass empty string to return all classes.
- L354 _public prototype_ `static FUMGWidgetClassEntry GetWidgetClassInfo(TSubclassOf<UWidget> WidgetClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Query")` — Returns the Category, Description and if it's a Panel for a single widget class. Same per-entry data as ListWidgetClasses, but lets callers query a class they already have without scanning every UClass. Returns an empty entry if WidgetClass is null. Can be used to get more information on the class from the Description and Category. @param WidgetClass The widget class to inspect.
- L366 _public prototype_ `static FUMGWidgetInfo MoveWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, UPanelWidget* NewParent, int32 ChildIndex = -1);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Moves a widget to a new parent panel at the specified position. Returns updated widget info with new Slot. @param WidgetBlueprint The widget blueprint to modify. @param Widget The widget to move. @param NewParent The destination panel widget. @param ChildIndex Position in new parent's child list (0 = first child). -1 (default) appends to end.
- L374 _public prototype_ `static bool RemoveWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Removes a widget and its children from the tree. @param WidgetBlueprint The widget blueprint to modify. @param Widget The widget to remove (along with its children).
- L383 _public prototype_ `static FUMGWidgetInfo RenameWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, const FString& NewDisplayName);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Renames a widget. Returns updated widget info or empty on failure. @param WidgetBlueprint The widget blueprint to modify. @param Widget The widget to rename. @param NewDisplayName The new display name.
- L392 _public prototype_ `static void ToggleWidgetAsVariable(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, bool bIsVariable);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Sets the bIsVariable flag. @param WidgetBlueprint The widget blueprint to modify. @param Widget The widget to update. @param bIsVariable True to expose as a blueprint variable, false to hide it.
- L411 _public prototype_ `static bool BindToEventProperty(UWidgetBlueprint* WidgetBlueprint, const FName EventName, FName PropertyName, UClass* PropertyClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Adds a Blueprint event handler graph node bound to a widget's multicast delegate event, Typical events: UButton::OnClicked / OnPressed / OnReleased / OnHovered / OnUnhovered, UCheckBox::OnCheckStateChanged, USlider::OnValueChanged. The matching delegate UPROPERTY must exist on PropertyClass (or a parent of it). Preconditions: - PropertyName must exist in the blueprint. - PropertyClass must be the widget's class (or a parent class) that declares the delegate. @param WidgetBlueprint The widget blueprint that will own the event handler. @param EventName       Name of the multicast delegate UPROPERTY on PropertyClass (e.g. "OnClicked"). @param PropertyName    Name of the blueprint variable owning the event. @param PropertyClass   Class declaring the delegate, typically the widget's class (e.g. UButton::StaticClass()).
- L426 _public prototype_ `static TArray<FUMGWidgetInfo> WrapWidgets(UWidgetBlueprint* WidgetBlueprint, TArray<UWidget*> Widgets, TSubclassOf<UPanelWidget> WrapperClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Wraps one or more widgets in a new panel widget of the specified class. Only the root-most widgets in the selection are wrapped — children of other selected widgets are skipped because their parent will be wrapped. Returns info for each newly created wrapper. Use ObjectTools.list_properties on each returned Widget and Slot to discover property names before calling set_properties (padding, alignment, anchors, etc. vary per panel class). @param WidgetBlueprint The widget blueprint to modify. @param Widgets         The widgets to wrap. Must all be in WidgetBlueprint's tree. @param WrapperClass    The panel widget class to wrap with (must be a UPanelWidget subclass).
- L442 _public prototype_ `static FUMGWidgetDescriptionResult GetWidgetDescription(const UWidgetBlueprint* WidgetBlueprint, const UWidget* StartWidget = nullptr, int32 MaxDepth = -1);` — `UFUNCTION(meta = (AICallable), Category = "UMGToolSet|WidgetDescription")` — Full property dump of every widget in the tree. Each line: [N] Type Name  Prop:Value ...  slot:(SlotProp:Value ...) N is the 0-based index into result.Widgets -- use result.Widgets[N] to get the widget ref without text parsing. Same indentation format as GetTaggedWidgetDescription; richer per-widget detail. @param WidgetBlueprint  The WBP asset. @param StartWidget      nullptr = full tree from root. @param MaxDepth         -1 = no limit; 0 = StartWidget only; N = N levels.
- L450 _public prototype_ `static int32 GetWidgetTreeDepth( const UWidgetBlueprint* WidgetBlueprint, const UWidget* StartWidget = nullptr);` — `UFUNCTION(meta = (AICallable), Category = "UMG|WidgetDescription")` — Returns the maximum depth of the widget tree. Depth: root with no children = 0; root + children = 1; etc. @return Depth as int32; -1 on error.
- L465 _public prototype_ `static FUMGWidgetInfo AddUIComponent(UWidgetBlueprint* WidgetBlueprint, FName WidgetName, TSubclassOf<UUIComponent> ComponentClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Components")` — Adds a UI component of the given class to the named widget. @param WidgetBlueprint The widget blueprint to modify. @param WidgetName Name of the widget instance to add the component to. @param ComponentClass The UIComponent subclass to add. @return Info for the widget the component was added to, including the populated UIComponents array. Returns an empty info on failure.
- L475 _public prototype_ `static bool RemoveUIComponent(UWidgetBlueprint* WidgetBlueprint, FName WidgetName, TSubclassOf<UUIComponent> ComponentClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Components")` — Removes a UI component of the given class from the named widget. @param WidgetBlueprint The widget blueprint to modify. @param WidgetName Name of the widget instance to remove the component from. @param ComponentClass The UIComponent subclass to remove. @return True if the component was removed, false if it was not found.
- L487 _public prototype_ `static bool MoveUIComponent(UWidgetBlueprint* WidgetBlueprint, FName WidgetName, TSubclassOf<UUIComponent> ComponentClassToMove, TSubclassOf<UUIComponent> RelativeToComponentClass, bool bMoveAfter);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Components")` — Moves a UI component before or after another component on the same widget. @param WidgetBlueprint The widget blueprint to modify. @param WidgetName Name of the widget instance whose component to move. @param ComponentClassToMove The UIComponent subclass to reorder. @param RelativeToComponentClass The UIComponent subclass to move relative to. @param bMoveAfter True to place after RelativeToComponentClass, false to place before. @return True if the component was moved, false if either component was not found.
- L506 _public prototype_ `static FWidgetReplacementReport ReplaceWidgetWithTemplate(UWidgetBlueprint* WidgetBlueprint, UWidget* WidgetToReplace, TSubclassOf<UWidget> TemplateClass);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Replaces a widget instance in the blueprint's widget tree with a new instance created from a different template widget class. Preserves references for members that exist on both classes with a compatible type/signature: bindings, BP graph variable references, animation bindings, and delegate bindings. Members without a compatible counterpart on the new class are listed in the returned report; references to those members in the outer blueprint will become orphaned graph nodes / dangling bindings. @param WidgetBlueprint    The widget blueprint containing the widget to replace. @param WidgetToReplace    The widget instance to replace (must be in WidgetBlueprint's tree). @param TemplateClass      The widget class to create the replacement from. @return Report whose bSuccess flag indicates whether the replacement happened, MissingReferencesWarning describes warnings that need action, and the Unmatched* arrays list members that have no compatible counterpart on the new class (with the *Referenced* subsets being the ones the blueprint actually uses today).
- L519 _public prototype_ `static bool ReplaceWidgetWithNamedSlot(UWidgetBlueprint* WidgetBlueprint, UWidget* WidgetToReplace, FName NamedSlot);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Replaces a host widget with the content of one of its named slots. The host must implement INamedSlotInterface (e.g., a UUserWidget exposing named slots). The slot's content widget is moved up to take the host's place in the tree. @param WidgetBlueprint    The widget blueprint containing the host widget. @param WidgetToReplace    The host widget to replace. @param NamedSlot          The slot whose content replaces WidgetToReplace. @return true on success, false if validation failed.
- L530 _public prototype_ `static bool ReplaceWidgetWithChild(UWidgetBlueprint* WidgetBlueprint, UWidget* WidgetToReplace);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Modification")` — Replaces a panel widget with its first child, removing the panel from the tree. The widget to replace must be a UPanelWidget with only one child. @param WidgetBlueprint    The widget blueprint containing the panel widget. @param WidgetToReplace    The panel widget to replace with its first child. @return true on success, false if validation failed.
- L541 _public prototype_ `static bool CompileWidgetBlueprint(UWidgetBlueprint* WidgetBlueprint);` — `UFUNCTION(meta = (AICallable), Category = "UMG|Lifecycle")` — Compiles a widget blueprint. Returns false with error details if compilation fails. Errors include missing BindWidget bindings, type mismatches, and graph errors. Call after all widgets and properties are set. Save separately via AssetTools.save_asset. @param WidgetBlueprint The widget blueprint to compile.

### `Plugins/Experimental/Toolsets/UMGToolSet/Source/UMGToolSet/Public/UMGToolSetModule.h` (Public)


#### class `FUMGToolSetModule`  
`class FUMGToolSetModule : public IModuleInterface`  
_L11-24_
- inherits: `IModuleInterface`
- desc: UMGToolSet module - provides AI assistant toolsets for UMG widget manipulation.
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `void OnAllModuleLoadingPhasesComplete();` — Called when all modules have finished loading
- L23 _private prototype_ `void OnPreExit();` — Called before application exit
