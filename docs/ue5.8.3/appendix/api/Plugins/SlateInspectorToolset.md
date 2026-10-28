# Plugins / SlateInspectorToolset

- module root: `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset`
- headers: 6; symbols: 87
- symbol kinds: class=6, function=1, member=31, prototype=46, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, ImageWrapper, InputCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: ToolsetRegistry

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset/Public/SlateInspectorToolset.h` (Public)


#### struct `FSlateInspectorToolsetModifierKeys`  
`struct FSlateInspectorToolsetModifierKeys`  
_L14-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: Modifier keys held during an input simulation (click, drag, etc.).
- L19 _public member_ `bool bShift = false;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")`
- L22 _public member_ `bool bCtrl = false;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")`
- L25 _public member_ `bool bAlt = false;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")`
- L28 _public member_ `bool bCmd = false;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")`
- L31 _public function_ `FModifierKeysState ToModifierKeysState() const` — Convert to Slate's FModifierKeysState.

#### struct `FSlateInspectorToolsetFormField`  
`struct FSlateInspectorToolsetFormField`  
_L39-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a single form field for the FillForm tool.
- L45 _public member_ `FString Ref;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")` — The ref identifier of the form field widget.
- L49 _public member_ `FString Value;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")` — The value to set.
- L53 _public member_ `FString FieldType;` — `UPROPERTY(BlueprintReadWrite, Category = "SlateInspectorToolset")` — The type of field: "textbox", "checkbox", or "combobox".

#### class `USlateInspectorToolset`  
`class USlateInspectorToolset : public UToolsetDefinition`  
_L75-196_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Playwright-style Slate UI automation toolset. Exposes snapshot, screenshot, and interaction tools for driving the Unreal Editor UI programmatically.  Registered via UToolsetRegistry so the ModelContextProtocol plugin picks them up automatically. A shallow root observer (depth 0) continuously tracks top-level windows.  Before working with a specific window or panel, call Observe() on it to get deep widget coverage, then Unobserve() when done.  Observers walk their subtree every ~100ms, assigning refs to newly appeared widgets and keeping the ref cache current. Input simulation uses direct Slate event APIs (ProcessKeyCharEvent, ProcessMouseButtonDownEvent, etc.) rather than the AutomationDriver, because AutomationDriver's synchronous API deadlocks when called from the game thread (which is where MCP tool calls execute).
- L92 _public prototype_ `static FString Snapshot(const FString& Ref, int32 MaxDepth = 30, bool bIncludeSourceLocations = false);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Capture a Slate UI accessibility snapshot.  Use this to read the current widget tree and discover refs for action tools (Click, Type, Hover, etc.). A shallow root observer (depth 0) covers top-level windows automatically. Before interacting with a specific window or panel, call Observe() on it to get deep coverage, then Snapshot that subtree to see its contents. Refs discovered by a previous Snapshot remain usable. You do NOT need to call Snapshot again before every action. @param Ref                      Subtree root ref. Empty = all windows. @param MaxDepth                 Maximum depth (default 30). @param bIncludeSourceLocations  Include [src=File:Line] tags showing where each widget was created in C++.
- L102 _public prototype_ `static FString Observe(const FString& Ref, int32 MaxDepth = 30);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Register an observer on a widget subtree so its refs are continuously kept up to date (~100ms tick).  Call this on the window or panel you are about to work with. It ensures new widgets appearing in that subtree are assigned refs automatically.  Unobserve when you are done. A shallow root observer (depth 0) already covers top-level windows. @param Ref       Root widget ref to observe. Empty = all visible windows. @param MaxDepth  Maximum depth to walk from the root.
- L107 _public prototype_ `static bool Unobserve(const FString& Identifier);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Remove an observer by its identifier. @param Identifier  The identifier returned by Observe().
- L113 _public prototype_ `static FString ListObservers();` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — List all active observers as a JSON array for debugging. Each entry includes the observer identifier, whether it is the root observer, the root widget ref (if any), max depth, and cached snapshot size.
- L119 _public prototype_ `static FToolsetImage Screenshot(const FString& Ref);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Screenshot a Slate widget or the active editor window. Prefer this over SceneTools.take_screenshot for Editor UI; use SceneTools only for 3D viewport. @param Ref  Slate widget ref. Empty = active window.
- L129 _public prototype_ `static bool Click(const FString& Ref, const FString& Button = TEXT("left"), bool DoubleClick = false, const FSlateInspectorToolsetModifierKeys& Modifiers = FSlateInspectorToolsetModifierKeys` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Click a Slate widget identified by its ref. @param Ref         Slate widget ref. @param Button      "left", "right", or "middle". @param DoubleClick True for double-click. @param Modifiers   Modifier keys held during the click.
- L134 _public prototype_ `static bool Hover(const FString& Ref);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Hover over a Slate widget, triggering any hover state or tooltip. @param Ref  Slate widget ref.
- L142 _public prototype_ `static bool Type(const FString& Ref, const FString& Text, bool Submit = false);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Type text into a Slate text input widget. Focuses the widget first, then sends one key event per character. @param Ref    Slate textbox ref. @param Text   Text to type. @param Submit Press Enter after typing.
- L148 _public prototype_ `static bool PressKey(const FString& Key);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Press and release a keyboard key on the currently focused Slate widget. Supports modifier prefixes: "Ctrl+C", "Shift+1". @param Key  Key name with optional modifiers, e.g. "Enter", "Ctrl+A", "Shift+Tab".
- L155 _public prototype_ `static bool SelectOption(const FString& Ref, const FString& Value);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Select an option in a Slate combobox by its text label. Opens the dropdown, finds the matching text, and clicks it. @param Ref    Slate combobox ref. @param Value  Exact option text to select.
- L162 _public prototype_ `static bool Drag(const FString& StartRef, const FString& EndRef, const FSlateInspectorToolsetModifierKeys& Modifiers = FSlateInspectorToolsetModifierKeys());` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Drag from one Slate widget to another (mouse down, move, release). @param StartRef   Slate widget ref for the drag source. @param EndRef     Slate widget ref for the drop target. @param Modifiers  Modifier keys held during the drag.
- L168 _public prototype_ `static FString Windows(const FString& Action = TEXT("list"), int32 Index =` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — List, select, or close top-level Slate editor windows. @param Action  "list" returns JSON array, "select" brings to front, "close" destroys. @param Index   Window index for select/close.
- L175 _public prototype_ `static bool WaitFor(const FString& Text = TEXT(""), const FString& TextGone = TEXT(""));` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Check if text is present or absent in the Slate widget tree. Non-blocking: checks once and returns immediately. Poll to wait. @param Text       Text that must be present (empty = skip). @param TextGone   Text that must be absent (empty = skip).
- L181 _public prototype_ `static bool FillForm(const TArray<FSlateInspectorToolsetFormField>& Fields);` — `UFUNCTION(meta = (AICallable), Category = "SlateInspectorToolset")` — Fill multiple Slate form fields at once. @param Fields  Array of {Ref, Value, FieldType} where FieldType is "textbox", "checkbox", or "combobox".
- L186 _private prototype_ `static TSharedPtr<SWidget> ResolveRefOrWarn(const FString& Ref);` — Resolve a ref to a widget, logging a warning if it fails.
- L189 _private prototype_ `static FVector2D GetWidgetScreenCenter(TSharedRef<SWidget> Widget);` — Get the absolute screen-space center of a widget.
- L192 _private prototype_ `static FKey ParseMouseButtonKey(const FString& Button);` — Map a button name ("left", "right", "middle") to an FKey.
- L195 _private prototype_ `static bool SimulateClick(TSharedRef<SWidget> Widget, FKey MouseButton, bool bDoubleClick, const FModifierKeysState& ModifierKeys = FModifierKeysState());` — Simulate a mouse click at a widget's screen-space center.

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset/Public/SlateInspectorToolsetModule.h` (Public)


#### class `FSlateInspectorToolsetModule`  
`class FSlateInspectorToolsetModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset/Public/SlateInspectorToolsetObserverManager.h` (Public)


#### struct `FSlateInspectorToolsetObserver`  
`struct FSlateInspectorToolsetObserver`  
_L9-25_
- desc: A single observer watching a Slate widget subtree.
- L12 _public member_ `FString Identifier;` — Unique identifier returned by AddObserver().
- L15 _public member_ `TWeakPtr<SWidget> RootWidget;` — Root widget to observe. Invalid (null) when bRoot is true.
- L18 _public member_ `bool bRoot = false;` — When true, this is the root observer covering all visible windows (RootWidget is ignored).
- L21 _public member_ `int32 MaxDepth = 30;` — Maximum depth to walk from the root.
- L24 _public member_ `FString CachedSnapshotText;` — Cached snapshot text from the most recent observer tick.

#### class `FSlateInspectorToolsetObserverManager`  
`class FSlateInspectorToolsetObserverManager`  
_L33-96_
- desc: Manages a set of observers that continuously walk Slate widget subtrees on a throttled tick, keeping the ref cache up to date as the UI changes. A default root observer (all visible windows) is always present.
- L37 _public prototype_ `static FSlateInspectorToolsetObserverManager& Get();`
- L46 _public prototype_ `FString AddObserver(TSharedPtr<SWidget> RootWidget, int32 MaxDepth = 30);` — Register an observer on a widget subtree. @param RootWidget  The root of the subtree to observe.  Null = all visible windows. @param MaxDepth    Maximum depth to walk. @return The observer identifier (used with RemoveObserver and GetCachedSnapshot).
- L53 _public prototype_ `bool RemoveObserver(const FString& Identifier);` — Remove an observer by identifier. @return True if the observer was found and removed.
- L56 _public prototype_ `TArray<FSlateInspectorToolsetObserver> GetObservers() const;` — Returns a copy of all active observers.
- L63 _public prototype_ `FString GetCachedSnapshot(const FString& Identifier) const;` — Returns the cached snapshot text for an observer. @return The most recently rendered snapshot text, or empty if not found.
- L75 _public prototype_ `FString FindMatchingObserverSnapshot(TSharedPtr<SWidget> RootWidget, int32 MaxDepth) const;` — Find the best matching observer for the given root and return its cached snapshot. A null RootWidget matches the root observer.  Otherwise, matches an observer whose root is the given widget (preferring deeper MaxDepth). @param RootWidget  The root to match. Null = root observer. @param MaxDepth    Only match observers with at least this depth. @return The cached snapshot text, or empty if no matching observer found.
- L80 _public prototype_ `void Tick(float DeltaTime);` — Called each Slate post-tick.  Throttled internally to ~100ms intervals.
- L84 _private member_ `TArray<FSlateInspectorToolsetObserver> Observers;`
- L86 _private member_ `int32 NextIdentifier = 1;`
- L89 _private member_ `float AccumulatedTime = 0.0f;` — Accumulated time since last observer pass.
- L92 _private member_ `int32 TickCounter = 0;` — Tick counter for periodic purge scheduling.
- L94 _private member_ `static constexpr float TickIntervalSeconds = 0.1f;`
- L95 _private member_ `static constexpr int32 PurgeEveryNTicks = 10;`

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset/Public/SlateInspectorToolsetRefCache.h` (Public)


#### class `FSlateInspectorToolsetRefCache`  
`class FSlateInspectorToolsetRefCache`  
_L27-86_
- desc: Manages bidirectional mapping between SWidget instances and short reference strings used by the SlateInspectorToolset snapshot and action tools. # Observer model (append-only) When observers are active, refs are never reset.  New widgets encountered during observer ticks receive the next available counter value for their role prefix.  Existing widgets keep their refs indefinitely (the same SWidget pointer always maps to the same ref string).  Destroyed widgets are cleaned up periodically via PurgeExpired(). Refs are no longer dense after widgets are destroyed (you may see b1, b3, b7 instead of b1, b2, b3), but keeping refs alive for existing widgets matters more than compactness. Reset() is available for callers that need to clear the cache entirely and start fresh (e.g. testing).
- L31 _public prototype_ `static FSlateInspectorToolsetRefCache& Get();`
- L44 _public prototype_ `FString GetOrAssignRef(TSharedRef<SWidget> Widget, const FString& RolePrefix);` — Returns existing ref or assigns a new one using the role prefix. The role prefix determines the ref format: "b" for buttons produces b1, b2, b3, etc.  Within a single snapshot pass, the same widget always gets the same ref (deduplication via WidgetToRef lookup). @param Widget      The widget to assign a ref to. @param RolePrefix  Short prefix derived from the widget's role (e.g., "b", "tb", "cb"). @return The assigned ref string (e.g., "b3").
- L52 _public prototype_ `TSharedPtr<SWidget> ResolveRef(const FString& Ref) const;` — Resolves a ref string back to a live widget. Returns nullptr if the ref is unknown or the widget has been destroyed since the last snapshot.
- L59 _public prototype_ `FString FindRef(TSharedRef<SWidget> Widget) const;` — Looks up the ref for a widget without assigning one. @return The ref string, or empty if the widget has no ref.
- L66 _public prototype_ `void Reset();` — Clears all mappings and resets counters to zero. Observer-driven passes should NOT call this because they rely on the append-only behavior to preserve existing refs.
- L74 _public prototype_ `void PurgeExpired();` — Removes entries whose widget has been destroyed (weak pointer expired). Called periodically by the observer manager to prevent unbounded map growth.  Safe to call at any time.
- L79 _private member_ `TMap<TWeakPtr<SWidget>, FString> WidgetToRef;` — Widget -> ref string (deduplication within a single snapshot pass).
- L82 _private member_ `TMap<FString, TWeakPtr<SWidget>> RefToWidget;` — Ref string -> widget (reverse lookup for action tools).
- L85 _private member_ `TMap<FString, int32> RolePrefixCounters;` — Per-role-prefix counters for generating sequential ref numbers.

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset/Public/SlateInspectorToolsetSnapshotRenderer.h` (Public)


#### class `FSlateInspectorToolsetSnapshotRenderer`  
`class FSlateInspectorToolsetSnapshotRenderer`  
_L16-83_
- desc: Renders a text-based accessibility snapshot of a Slate widget tree. Walks the tree depth-first, emitting one line per meaningful widget with role, label, state flags, and a compact ref identifier.  Structural containers (SBox, SBorder, SOverlay, etc.) are elided and their children are emitted at the parent's indent level.
- L30 _public prototype_ `static FString Render(TSharedPtr<SWidget> Root, int32 MaxDepth = 30, bool bIncludeSourceLocations = false, bool bResetCache = true);` — Render a snapshot starting from the given root widget. @param Root                     The widget subtree to snapshot.  If null, snapshots all top-level windows. @param MaxDepth                 Maximum recursion depth (default 30). @param bIncludeSourceLocations  Include [src=File:Line] tags showing where each widget was created in C++. @param bResetCache              When true (default), clears the ref cache before rendering. Pass false for observer-driven passes that preserve existing refs. @return Indented text representation of the widget tree.
- L33 _public prototype_ `static void RegisterWidgetRole(const FName& WidgetType, const FString& Role, const FString& RefPrefix);` — Register a custom widget type so it appears in snapshots.
- L36 _public prototype_ `static void RegisterLabelExtractor(const FName& WidgetType, TFunction<FString(TSharedRef<SWidget>)> Extractor);` — Register a custom label extractor for a widget type.
- L39 _public prototype_ `static void RegisterStateFlagsExtractor(const FName& WidgetType, TFunction<TArray<FString>(TSharedRef<SWidget>)> Extractor);` — Register a custom state flags extractor for a widget type.
- L44 _private prototype_ `static void EnsureMapsInitialized();` — Initializes the type-to-role and structural-skip maps on first use.
- L47 _private prototype_ `static void RenderWidget( FStringBuilderBase& Output, TSharedRef<SWidget> Widget, int32 IndentLevel, int32 CurrentDepth, int32 MaxDepth, bool bIncludeSourceLocations);` — Recursive depth-first walk.
- L56 _private prototype_ `static FString ExtractLabel(TSharedRef<SWidget> Widget, const FString& TypeString);` — Extract a human-readable label from a widget via type-specific methods.
- L59 _private prototype_ `static FString ExtractStateFlags(TSharedRef<SWidget> Widget, const FString& TypeString);` — Extract state flags (visibility, enabled, checked, focused).
- L62 _private prototype_ `static const FString* FindRoleForType(const FName& WidgetType, const FString& TypeString);` — Look up role for a widget type, handling template types via prefix matching.
- L65 _private member_ `static TMap<FName, FString> TypeToRole;` — Map from widget type name to role string (e.g., "SButton" -> "button").
- L68 _private member_ `static TArray<TPair<FString, FString>> TemplatePrefixToRole;` — Prefix-based role mapping for template types (e.g., "SComboBox" matches "SComboBox<...>").
- L71 _private member_ `static TMap<FString, FString> RoleToRefPrefix;` — Map from role string to ref prefix (e.g., "button" -> "b").
- L74 _private member_ `static TSet<FName> StructuralContainers;` — Set of structural container type names that should be skipped (children promoted).
- L77 _private member_ `static TMap<FName, TFunction<FString(TSharedRef<SWidget>)>> CustomLabelExtractors;` — Custom label extractors registered via RegisterLabelExtractor.
- L80 _private member_ `static TMap<FName, TFunction<TArray<FString>(TSharedRef<SWidget>)>> CustomStateFlagsExtractors;` — Custom state flags extractors registered via RegisterStateFlagsExtractor.
- L82 _private member_ `static bool bMapsInitialized;`

### `Plugins/Experimental/Toolsets/SlateInspectorToolset/Source/SlateInspectorToolset/Public/SlateInspectorToolsetSubsystem.h` (Public)


#### class `USlateInspectorToolsetSubsystem`  
`class USlateInspectorToolsetSubsystem : public UEditorSubsystem`  
_L12-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L18 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L20 _public prototype_ `virtual void Deinitialize() override;`
- L23 _public prototype_ `void SetToolsetEnabled(bool bEnabled);` — Register or unregister the toolset at runtime.
- L28 _private prototype_ `void OnSlatePostTick(float DeltaTime);` — Forwarded from FSlateApplication::OnPostTick to drive observer updates.
- L30 _private member_ `bool bToolsetRegistered = false;`
- L32 _private member_ `FDelegateHandle PostTickDelegateHandle;`
- L34 _private member_ `FString RootObserverIdentifier;`
