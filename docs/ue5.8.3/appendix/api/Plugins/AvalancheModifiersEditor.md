# Plugins / AvalancheModifiersEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor`
- headers: 6; symbols: 62
- symbol kinds: class=6, function=2, member=8, prototype=46
- PrivateDependencyModuleNames: ActorModifier, ActorModifierCore, ActorModifierCoreEditor, ActorModifierEditor, CoreUObject, Engine, Projects, Slate, ToolMenus, UnrealEd
- PublicDependencyModuleNames: AvalancheModifiers, AvalancheOutliner, Core, SlateCore

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor/Private/AvaModifiersEditorModule.h` (Private)


#### class `FAvaModifiersEditorModule`  
`class FAvaModifiersEditorModule : public IModuleInterface`  
_L8-23_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void RegisterOutlinerItems();`
- L18 _private prototype_ `void UnregisterOutlinerItems();`
- L20 _private member_ `FDelegateHandle OutlinerProxiesExtensionDelegateHandle;`
- L21 _private member_ `FDelegateHandle OutlinerContextDelegateHandle;`
- L22 _private member_ `FDelegateHandle OutlinerDropHandlerDelegateHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor/Private/AvaModifiersEditorStyle.h` (Private)


#### class `FAvaModifiersEditorStyle`  
`class FAvaModifiersEditorStyle final : public FSlateStyleSet`  
_L10-24_
- inherits: `FSlateStyleSet`
- L13 _public function_ `static FAvaModifiersEditorStyle& Get()`
- L19 _public prototype_ `FAvaModifiersEditorStyle();`
- L23 _private prototype_ `void OnModifierClassRegistered(const FActorModifierCoreMetadata& InMetadata);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor/Private/Outliner/AvaOutlinerModifier.h` (Private)


#### class `FAvaOutlinerModifier`  
`class FAvaOutlinerModifier : public FAvaOutlinerObject`  
_L12-43_
- inherits: `FAvaOutlinerObject`
- desc: Item representing a Modifier Item
- L15 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerModifier, FAvaOutlinerObject);`
- L17 _public prototype_ `FAvaOutlinerModifier(IAvaOutliner& InOutliner, UActorModifierCoreBase* InObject);`
- L19 _public function_ `UActorModifierCoreBase* GetModifier() const`
- L22 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L23 _public prototype_ `virtual FText GetDisplayName() const override;`
- L24 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L26 _public prototype_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType InVisibilityType) const override;`
- L27 _public prototype_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType InVisibilityType) const override;`
- L28 _public prototype_ `virtual void OnVisibilityChanged(EAvaOutlinerVisibilityType InVisibilityType, bool bInNewVisibility) override;`
- L29 _public prototype_ `virtual bool CanDelete() const override;`
- L30 _public prototype_ `virtual bool Delete() override;`
- L35 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L38 _protected member_ `TWeakObjectPtr<UActorModifierCoreBase> Modifier;`
- L40 _protected member_ `FText ModifierName;`
- L41 _protected member_ `FSlateIcon ModifierIcon;`
- L42 _protected member_ `FText ModifierTooltip;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor/Private/Outliner/AvaOutlinerModifierContextMenu.h` (Private)


#### class `FAvaOutlinerModifierContextMenu`  
`class FAvaOutlinerModifierContextMenu`  
_L13-22_
- desc: Context menu actions in outliner related to modifiers
- L18 _public prototype_ `static void OnExtendOutlinerContextMenu(UToolMenu* InToolMenu);` — Extend outliner context menu
- L21 _public prototype_ `static void GetContextObjects(const UAvaOutlinerItemsContext* ItemsContext, TSet<TWeakObjectPtr<UObject>>& OutObjects);` — Gets all pertinent context object in this context

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor/Private/Outliner/AvaOutlinerModifierDropHandler.h` (Private)


#### class `FAvaOutlinerModifierDropHandler`  
`class FAvaOutlinerModifierDropHandler : public FAvaOutlinerItemDropHandler`  
_L12-30_
- inherits: `FAvaOutlinerItemDropHandler`
- desc: Class that handles dropping modifiers item into a target item
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerModifierDropHandler, FAvaOutlinerItemDropHandler);`
- L19 _protected prototype_ `virtual bool IsDraggedItemSupported(const FAvaOutlinerItemPtr& InDraggedItem) const override;`
- L20 _protected prototype_ `virtual TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) const override;`
- L21 _protected prototype_ `virtual bool Drop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) override;`
- L25 _protected prototype_ `TSet<UActorModifierCoreBase*> GetDraggedModifiers() const;` — Get raw dragged modifiers set
- L27 _protected prototype_ `TOptional<EItemDropZone> CanDropOnActor(AActor* InActor, EItemDropZone InDropZone) const;`
- L28 _protected prototype_ `bool DropModifiersInActor(AActor* InActor, EItemDropZone InDropZone) const;`
- L29 _protected prototype_ `bool DropModifiersInModifier(UActorModifierCoreBase* InTargetModifier, EItemDropZone InDropZone) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiersEditor/Private/Outliner/AvaOutlinerModifierProxy.h` (Private)


#### class `FAvaOutlinerModifierProxy`  
`class FAvaOutlinerModifierProxy : public FAvaOutlinerItemProxy`  
_L15-50_
- inherits: `FAvaOutlinerItemProxy`
- desc: Creates Modifier Items based on all the Modifiers found in the Root Stack of an Actor
- L18 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerModifierProxy, FAvaOutlinerItemProxy);`
- L20 _public prototype_ `FAvaOutlinerModifierProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L23 _public prototype_ `UActorModifierCoreStack* GetModifierStack() const;` — Gets the Modifier Stack to use (e.g. for an Actor it would be the Root Modifier Stack)
- L24 _public prototype_ `AActor* GetActor() const;`
- L27 _public prototype_ `virtual void OnItemRegistered() override;`
- L28 _public prototype_ `virtual void OnItemUnregistered() override;`
- L29 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L30 _public prototype_ `virtual FText GetDisplayName() const override;`
- L31 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L32 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L33 _public prototype_ `virtual bool CanDelete() const override;`
- L34 _public prototype_ `virtual bool Delete() override;`
- L38 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`
- L42 _protected prototype_ `void BindDelegates();`
- L43 _protected prototype_ `void UnbindDelegates();`
- L45 _protected prototype_ `void OnModifierAdded(UActorModifierCoreBase* InItemChanged, EActorModifierCoreEnableReason InReason);`
- L46 _protected prototype_ `void OnModifierRemoved(UActorModifierCoreBase* InItemChanged, EActorModifierCoreDisableReason InReason);`
- L47 _protected prototype_ `void OnModifierUpdated(UActorModifierCoreBase* ItemChanged);`
- L49 _protected member_ `FSlateIcon ModifierIcon;`
