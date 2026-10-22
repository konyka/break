# Plugins / ActorModifierCoreEditor

- module root: `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor`
- headers: 10; symbols: 161
- symbol kinds: class=8, enum=1, enumerator=7, function=15, member=28, namespace=2, prototype=94, struct=6
- PrivateDependencyModuleNames: ActorModifierCore, ActorModifierCoreBlueprint, ApplicationCore, AssetDefinition, CoreUObject, CustomDetailsView, EditorSubsystem, Engine, InputCore, Json, JsonUtilities, OperatorStackEditor, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: ActorModifierCore, Core

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/ActorModifierCoreEditorModule.h` (Private)


#### class `FActorModifierCoreEditorModule`  
`class FActorModifierCoreEditorModule : public IModuleInterface`  
_L9-24_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _protected prototype_ `void RegisterDetailCustomizations();`
- L19 _protected prototype_ `void UnregisterDetailCustomizations();`
- L21 _protected prototype_ `void RegisterBlueprintCustomizations();`
- L23 _protected member_ `TArray<FName> CustomizationNames;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/ActorModifierCoreEditorStyle.h` (Private)


#### class `FActorModifierCoreEditorStyle`  
`class FActorModifierCoreEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FActorModifierCoreEditorStyle();`
- L14 _public function_ `static FActorModifierCoreEditorStyle& Get()`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/Modifiers/ActorModifierCoreEditorMenu.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ActorModifierCoreEditor` (scope `UE`)
- L11 _prototype_ `void OnExtendAddModifierMenu(UToolMenu* InAddToolMenu, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — For add submenu
- L14 _prototype_ `void OnExtendInsertModifierMenu(UToolMenu* InInsertToolMenu, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — For insert submenu
- L17 _prototype_ `void OnExtendRemoveModifierMenu(UToolMenu* InRemoveToolMenu, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — For remove submenu
- L20 _prototype_ `void OnExtendMoveModifierMenu(UToolMenu* InMoveToolMenu, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — For move submenu
- L23 _prototype_ `void OnExtendEnableModifierMenu(UToolMenu* InToolMenu, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — For enable/disable submenu
- L26 _prototype_ `void OnAddModifierMenuAction(const FName& InModifier, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — Add a modifier action
- L29 _prototype_ `void OnInsertModifierMenuAction(UActorModifierCoreBase* InModifier, const FName& InModifierName, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — Insert a modifier action
- L32 _prototype_ `void OnRemoveActorModifierMenuAction(const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — Remove actor modifier action
- L35 _prototype_ `void OnRemoveModifierMenuAction(const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — Remove context modifier action
- L38 _prototype_ `void OnRemoveSingleModifierMenuAction(UActorModifierCoreBase* InModifier, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — Remove single modifier action
- L41 _prototype_ `void OnMoveModifierMenuAction(UActorModifierCoreBase* InMoveModifier, UActorModifierCoreBase* InPositionModifier, const FActorModifierCoreEditorMenuData& InData);` (scope `UE::ActorModifierCoreEditor`) — Move a modifier action
- L44 _prototype_ `void OnEnableModifierMenuAction(const FActorModifierCoreEditorMenuData& InData, bool bInEnable, bool bInStack);` (scope `UE::ActorModifierCoreEditor`) — Enable/disable modifier action

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/Modifiers/Blueprints/ActorModifierCoreBlueprintFactory.h` (Private)


#### class `UActorModifierCoreBlueprintFactory`  
`class UActorModifierCoreBlueprintFactory : public UFactory`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Factory responsible to create a UActorModifierCoreBlueprint object
- L18 _public prototype_ `UActorModifierCoreBlueprintFactory();`
- L21 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn, FName InCallingContext) override;`
- L25 _public member_ `TSubclassOf<UActorModifierCoreBlueprintBase> ParentClass;` — `UPROPERTY()`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/Modifiers/Blueprints/AssetDefinition_ActorModifierCoreBlueprint.h` (Private)


#### class `UAssetDefinition_ActorModifierCoreBlueprint`  
`class UAssetDefinition_ActorModifierCoreBlueprint : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Asset definition for UActorModifierCoreBlueprint objects available in editor
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/Modifiers/Customizations/ActorModifierCoreEditorDetailCustomization.h` (Private)


#### class `FActorModifierCoreEditorDetailCustomization`  
`class FActorModifierCoreEditorDetailCustomization : public IDetailCustomization`  
_L11-22_
- inherits: `IDetailCustomization`
- desc: Stack details customization in the details panel
- L14 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Private/Modifiers/Customizations/ActorModifierCoreEditorStackCustomization.h` (Private)


#### struct `FActorModifierCoreEditorPropertiesWrapper`  
`struct FActorModifierCoreEditorPropertiesWrapper`  
_L17-27_
- reflection: `USTRUCT()`
- desc: Struct used for copy pasting modifiers in clipboard
- L23 _public member_ `FName ModifierName;` — `UPROPERTY()`
- L26 _public member_ `TMap<FName, FString> PropertiesHandlesAsStringMap;` — `UPROPERTY()`

#### class `UActorModifierCoreEditorStackCustomization`  
`class UActorModifierCoreEditorStackCustomization : public UOperatorStackEditorStackCustomization`  
_L31-94_
- reflection: `UCLASS()`
- inherits: `UOperatorStackEditorStackCustomization`
- desc: Modifier customization for stack tab
- L36 _public member_ `static inline const FString PropertiesWrapperPrefix = TEXT("Act`
- L38 _public prototype_ `UActorModifierCoreEditorStackCustomization();`
- L42 _public prototype_ `virtual bool GetRootItem(const FOperatorStackEditorContext& InContext, FOperatorStackEditorItemPtr& OutRootItem) const override;`
- L43 _public prototype_ `virtual bool GetChildrenItem(const FOperatorStackEditorItemPtr& InItem, TArray<FOperatorStackEditorItemPtr>& OutChildrenItems) const override;`
- L44 _public prototype_ `virtual void CustomizeStackHeader(const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorHeaderBuilder& InHeaderBuilder) override;`
- L45 _public prototype_ `virtual void CustomizeItemHeader(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorHeaderBuilder& InHeaderBuilder) override;`
- L46 _public prototype_ `virtual void CustomizeItemBody(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorBodyBuilder& InBodyBuilder) override;`
- L47 _public prototype_ `virtual void CustomizeItemFooter(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorFooterBuilder& InFooterBuilder) override;`
- L48 _public prototype_ `virtual bool OnIsItemDraggable(const FOperatorStackEditorItemPtr& InDragItem) override;`
- L49 _public prototype_ `virtual TOptional<EItemDropZone> OnItemCanAcceptDrop(const TArray<FOperatorStackEditorItemPtr>& InDraggedItems, const FOperatorStackEditorItemPtr& InDropZoneItem, EItemDropZone InZone) override;`
- L50 _public prototype_ `virtual void OnDropItem(const TArray<FOperatorStackEditorItemPtr>& InDraggedItems, const FOperatorStackEditorItemPtr& InDropZoneItem, EItemDropZone InZone) override;`
- L51 _public prototype_ `virtual bool ShouldFocusCustomization(const FOperatorStackEditorContext& InContext) const override;`
- L56 _protected prototype_ `void FillStackHeaderMenu(UToolMenu* InToolMenu) const;` — Populates the header menu of the whole customization stack
- L59 _protected prototype_ `void FillItemHeaderActionMenu(UToolMenu* InToolMenu) const;` — Populates the header action menu for items
- L62 _protected prototype_ `void FillItemContextActionMenu(UToolMenu* InToolMenu) const;` — Populates the context action menu for item
- L65 _protected prototype_ `bool CanRemoveModifier(FOperatorStackEditorItemPtr InItem) const;` — Remove modifier action
- L66 _protected prototype_ `void RemoveModifierAction(FOperatorStackEditorItemPtr InItem) const;`
- L69 _protected prototype_ `bool CanCopyModifier(FOperatorStackEditorItemPtr InItem) const;` — Copy modifier action
- L70 _protected prototype_ `void CopyModifierAction(FOperatorStackEditorItemPtr InItem) const;`
- L73 _protected prototype_ `bool CanPasteModifier(FOperatorStackEditorItemPtr InItem) const;` — Paste modifier action
- L74 _protected prototype_ `void PasteModifierAction(FOperatorStackEditorItemPtr InItem) const;`
- L77 _protected prototype_ `bool IsModifierStackFrozen(FOperatorStackEditorItemPtr InItem) const;` — Toggle the frozen state for a whole stack
- L78 _protected prototype_ `void ToggleModifierStackFrozenAction(FOperatorStackEditorItemPtr InItem) const;`
- L81 _protected prototype_ `bool IsModifierProfiling(FOperatorStackEditorItemPtr InItem) const;` — Toggle the profiling for a whole stack
- L82 _protected prototype_ `void ToggleModifierProfilingAction(FOperatorStackEditorItemPtr InItem) const;`
- L84 _protected prototype_ `void OnModifierAdded(UActorModifierCoreBase* InModifier, EActorModifierCoreEnableReason InReason);`
- L85 _protected prototype_ `void OnModifierRemoved(UActorModifierCoreBase* InModifier, EActorModifierCoreDisableReason InReason);`
- L86 _protected prototype_ `void OnModifierUpdated(UActorModifierCoreBase* InModifier);`
- L88 _protected prototype_ `TSharedRef<FUICommandList> CreateModifierCommands(FOperatorStackEditorItemPtr InItem);`
- L90 _protected prototype_ `bool CreatePropertiesHandlesMapFromModifier(UActorModifierCoreBase* InModifier, TMap<FName, FString>& OutModifierPropertiesHandlesMap) const;`
- L91 _protected prototype_ `bool GetModifierPropertiesWrapperFromClipboard(TArray<FActorModifierCoreEditorPropertiesWrapper>& OutModifierProperties) const;`
- L92 _protected prototype_ `bool UpdateModifierFromPropertiesHandlesMap(UActorModifierCoreBase* InModifier, const TMap<FName, FString>& InModifierPropertiesHandlesMap) const;`
- L93 _protected prototype_ `bool AddModifierFromClipboard(const TSet<AActor*>& InActors, FName InModifierName, TArray<UActorModifierCoreBase*>& OutNewModifiers) const;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Public/Modifiers/ActorModifierCoreEditorMenuDefs.h` (Public)


#### enum `EActorModifierCoreEditorMenuType`  
`enum class EActorModifierCoreEditorMenuType : uint8`  
_L15-29_
- desc: Menu type available
- L18 _public enumerator_ `Add` — Menu to add a modifier at the end of the stack
- L20 _public enumerator_ `InsertBefore` — Menu to insert a modifier in the stack
- L21 _public enumerator_ `InsertAfter`
- L23 _public enumerator_ `Delete` — Menu to delete a modifier in the stack
- L25 _public enumerator_ `Move` — Menu to move a modifier in the stack
- L27 _public enumerator_ `Enable` — Menu to enable or disable modifiers or stack
- L28 _public enumerator_ `Disable`

#### struct `FActorModifierCoreEditorMenuOptions`  
`struct FActorModifierCoreEditorMenuOptions`  
_L32-61_
- desc: Menu customization options
- L34 _public function_ `explicit FActorModifierCoreEditorMenuOptions(EActorModifierCoreEditorMenuType InMenuType) : MenuType(InMenuType)`
- L38 _public prototype_ `FActorModifierCoreEditorMenuOptions& CreateSubMenu(bool bInCreateSubMenu);`
- L39 _public prototype_ `FActorModifierCoreEditorMenuOptions& UseTransact(bool bInUseTransact);`
- L40 _public prototype_ `FActorModifierCoreEditorMenuOptions& FireNotification(bool bInFireNotification);`
- L42 _public function_ `EActorModifierCoreEditorMenuType GetMenuType() const`
- L43 _public function_ `bool ShouldCreateSubMenu() const`
- L44 _public function_ `bool ShouldTransact() const`
- L45 _public function_ `bool ShouldFireNotification() const`
- L49 _private member_ `EActorModifierCoreEditorMenuType MenuType = EActorModifierCoreEditorMenuType::Add;` — What type of menu should be generated
- L54 _private member_ `bool bCreateSubMenu = true;` — Create a sub-menu to display actions instead of filling on the same level with submenu : Root/Action/Choices... without : Root/Choices...
- L57 _private member_ `bool bUseTransact = true;` — Create a transaction for actions performed using the menu
- L60 _private member_ `bool bFireNotification = true;` — Should we fire a notification when an action is triggered

#### struct `FActorModifierCoreEditorMenuContext`  
`struct FActorModifierCoreEditorMenuContext`  
_L64-98_
- desc: Used to cache context results in case you call menu function with different menu options
- L66 _public prototype_ `explicit FActorModifierCoreEditorMenuContext(const TSet<TWeakObjectPtr<UObject>>& InContextObjects);`
- L68 _public function_ `const TSet<AActor*>& GetContextActors() const`
- L73 _public function_ `const TSet<UActorModifierCoreBase*>& GetContextModifiers() const`
- L78 _public function_ `const TSet<UActorModifierCoreBase*>& GetContextStacks() const`
- L83 _public prototype_ `bool IsEmpty() const;`
- L84 _public prototype_ `bool ContainsAnyActor() const;`
- L85 _public prototype_ `bool ContainsAnyModifier() const;`
- L86 _public prototype_ `bool ContainsAnyStack() const;`
- L87 _public prototype_ `bool ContainsOnlyModifier() const;`
- L88 _public prototype_ `bool ContainsNonEmptyStack() const;`
- L89 _public prototype_ `bool ContainsDisabledModifier() const;`
- L90 _public prototype_ `bool ContainsDisabledStack() const;`
- L91 _public prototype_ `bool ContainsEnabledModifier() const;`
- L92 _public prototype_ `bool ContainsEnabledStack() const;`
- L95 _protected member_ `TSet<AActor*> ContextActors;`
- L96 _protected member_ `TSet<UActorModifierCoreBase*> ContextModifiers;`
- L97 _protected member_ `TSet<UActorModifierCoreBase*> ContextStacks;`

#### struct `FActorModifierCoreEditorMenuData`  
`struct FActorModifierCoreEditorMenuData`  
_L101-110_
- desc: Used internally to group menu data together
- L103 _public function_ `FActorModifierCoreEditorMenuData(const FActorModifierCoreEditorMenuContext& InContext, const FActorModifierCoreEditorMenuOptions& InOptions) : Context(InContext) , Options(InOptions)`
- L108 _public member_ `const FActorModifierCoreEditorMenuContext Context;`
- L109 _public member_ `const FActorModifierCoreEditorMenuOptions Options;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Public/Modifiers/Widgets/SActorModifierCoreEditorProfiler.h` (Public)


#### struct `FActorModifierCoreEditorProfilerStat`  
`struct FActorModifierCoreEditorProfilerStat`  
_L11-24_
- L14 _public member_ `FName Name;` — Name of this stat
- L17 _public member_ `TAttribute<FText> ValueText = FText::GetEmpty();` — Attribute value text for this stat
- L20 _public member_ `TAttribute<FSlateColor> ValueColor = FLinearColor::White;` — Attribute value color for this stat
- L23 _public member_ `FString Suffix;` — Suffix added after value, useful for units

#### class `SActorModifierCoreEditorProfiler`  
`class SActorModifierCoreEditorProfiler : public SCompoundWidget`  
_L27-62_
- inherits: `SCompoundWidget`
- desc: Represent a modifier profiler widget, inherit from this class to extend behaviour
- L31 _public member_ `static inline constexpr float Padding = 3.f;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SActorModifierCoreEditorProfiler)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FActorModifierCoreProfiler> InProfiler);`
- L39 _protected prototype_ `FActorModifierCoreEditorProfilerStat* AddProfilerStat(const FName& InName);`
- L40 _protected prototype_ `FActorModifierCoreEditorProfilerStat* GetProfilerStat(const FName& InName);`
- L41 _protected prototype_ `virtual void OnProfilerStatAdded(FActorModifierCoreEditorProfilerStat& InStat);`
- L43 _protected prototype_ `virtual void SetupProfilerStats(TSharedPtr<FActorModifierCoreProfiler> InProfiler);`
- L44 _protected prototype_ `virtual void ScanPropertiesStats();`
- L45 _protected prototype_ `virtual void HandlePropertyStat(FProperty* InProperty, uint8* InValuePtr);`
- L47 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L48 _protected prototype_ `void ShowContextMenu(const FVector2D& InPosition);`
- L49 _protected prototype_ `TSharedRef<SWidget> OnGetContextMenuWidget();`
- L51 _protected prototype_ `void TogglePinProfilerStat(FName InName);`
- L52 _protected prototype_ `void SetPinProfilerStat(const FName& InName, bool bInIsPinned);`
- L53 _protected prototype_ `bool IsProfilerStatPinned(FName InName) const;`
- L55 _protected prototype_ `EVisibility GetStatVisibility(FName InName) const;`
- L56 _protected prototype_ `EVisibility GetProfilerVisibility() const;`
- L59 _private member_ `TSharedPtr<IMenu> ContextMenu;`
- L60 _private member_ `TMap<FName, FActorModifierCoreEditorProfilerStat> ProfilerStats;`
- L61 _private member_ `TWeakPtr<FActorModifierCoreProfiler> ProfilerWeak;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreEditor/Public/Subsystems/ActorModifierCoreEditorSubsystem.h` (Public)


#### struct `FActorModifierCoreEditorCategoryMetadata`  
`struct FActorModifierCoreEditorCategoryMetadata`  
_L20-24_
- L22 _public member_ `FName Name;`
- L23 _public member_ `FText DisplayName;`

#### class `UActorModifierCoreEditorSubsystem`  
`class UActorModifierCoreEditorSubsystem : public UEditorSubsystem`  
_L28-87_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- desc: Singleton class that handles editor operations for modifiers
- L35 _public prototype_ `UActorModifierCoreEditorSubsystem();`
- L37 _public prototype_ `static UActorModifierCoreEditorSubsystem* Get();`
- L40 _public prototype_ `bool FillModifierMenu(UToolMenu* InMenu, const FActorModifierCoreEditorMenuContext& InContext, const FActorModifierCoreEditorMenuOptions& InMenuOptions) const;` — Fills a menu based on context objects and menu options, will perform menu action transaction if wanted, returns true if the menu has been modified
- L45 _public function_ `void RegisterProfilerWidget()`
- L56 _public function_ `template<typename InProfilerClass, typename = typename TEnableIf<TIsDerivedFrom<InProfilerClass, FActorModifierCoreProfiler>::Value>::Type> void UnregisterProfilerWidget()` — Unregister a modifier profiler widget
- L63 _public prototype_ `TSharedPtr<SActorModifierCoreEditorProfiler> CreateProfilerWidget(TSharedPtr<FActorModifierCoreProfiler> InProfiler);` — Creates a profiler widget for a modifier profiler, returns default widget if none was registered
- L66 _public prototype_ `bool RegisterModifierCategory(const FActorModifierCoreEditorCategoryMetadata& InCategoryMetadata);` — Register a category for modifier
- L69 _public prototype_ `TSharedPtr<const FActorModifierCoreEditorCategoryMetadata> FindModifierCategory(FName InCategoryIdentifier) const;` — Finds a category for modifier
- L73 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L77 _protected member_ `TMap<FName, TSet<FName>> ModifierProfilerStats;` — Modifier profiler pinned stats based on profiler type
- L80 _protected member_ `TMap<FName, TFunction<TSharedRef<SActorModifierCoreEditorProfiler>(TSharedPtr<FActorModifierCoreProfiler>)>> ModifierProfilerWidgets;` — Modifier profiler widgets
- L83 _protected member_ `TMap<FName, TSharedRef<const FActorModifierCoreEditorCategoryMetadata>> ModifierCategories;` — Registered modifier category for menus and widgets
- L86 _protected member_ `TWeakObjectPtr<UActorModifierCoreSubsystem> EngineSubsystem = nullptr;` — Runtime subsystem for modifier factories

#### Free symbols / members of external scopes

- L49 _function_ `` (scope `UActorModifierCoreEditorSubsystem::RegisterProfilerWidget`)
