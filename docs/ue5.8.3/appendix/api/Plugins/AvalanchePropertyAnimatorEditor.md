# Plugins / AvalanchePropertyAnimatorEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalanchePropertyAnimatorEditor`
- headers: 5; symbols: 56
- symbol kinds: class=5, function=1, member=8, prototype=42
- PrivateDependencyModuleNames: AvalancheOutliner, Core, CoreUObject, Engine, PropertyAnimator, PropertyAnimatorCore, PropertyAnimatorCoreEditor, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/Avalanche/Source/AvalanchePropertyAnimatorEditor/Private/AvaPropertyAnimatorEditorModule.h` (Private)


#### class `FAvaPropertyAnimatorEditorModule`  
`class FAvaPropertyAnimatorEditorModule : public IModuleInterface`  
_L7-22_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _protected prototype_ `void RegisterOutlinerItems();`
- L17 _protected prototype_ `void UnregisterOutlinerItems();`
- L19 _protected member_ `FDelegateHandle OutlinerProxiesExtensionDelegateHandle;`
- L20 _protected member_ `FDelegateHandle OutlinerContextDelegateHandle;`
- L21 _protected member_ `FDelegateHandle OutlinerDropHandlerDelegateHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalanchePropertyAnimatorEditor/Private/Outliner/AvaPropertyAnimatorEditorOutliner.h` (Private)


#### class `FAvaPropertyAnimatorEditorOutliner`  
`class FAvaPropertyAnimatorEditorOutliner : public FAvaOutlinerObject`  
_L14-51_
- inherits: `FAvaOutlinerObject`
- desc: Item representing a property animator item
- L17 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaPropertyAnimatorEditorOutliner, FAvaOutlinerObject);`
- L19 _public prototype_ `FAvaPropertyAnimatorEditorOutliner(IAvaOutliner& InOutliner, UPropertyAnimatorCoreBase* InObject);`
- L22 _public function_ `UPropertyAnimatorCoreBase* GetPropertyAnimator() const`
- L28 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L29 _public prototype_ `virtual FText GetDisplayName() const override;`
- L30 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L31 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L32 _public prototype_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType InVisibilityType) const override;`
- L33 _public prototype_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType InVisibilityType) const override;`
- L34 _public prototype_ `virtual void OnVisibilityChanged(EAvaOutlinerVisibilityType InVisibilityType, bool bInNewVisibility) override;`
- L35 _public prototype_ `virtual bool CanDelete() const override;`
- L36 _public prototype_ `virtual bool Delete() override;`
- L41 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L44 _protected prototype_ `void OnAnimatorRemoved(UPropertyAnimatorCoreComponent* InComponent, UPropertyAnimatorCoreBase* InAnimator, EPropertyAnimatorCoreUpdateEvent InReason) const;`
- L46 _protected member_ `TWeakObjectPtr<UPropertyAnimatorCoreBase> PropertyAnimator;`
- L48 _protected member_ `FText ItemName;`
- L49 _protected member_ `FSlateIcon ItemIcon;`
- L50 _protected member_ `FText ItemTooltip;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalanchePropertyAnimatorEditor/Private/Outliner/AvaPropertyAnimatorEditorOutlinerContextMenu.h` (Private)


#### class `FAvaPropertyAnimatorEditorOutlinerContextMenu`  
`class FAvaPropertyAnimatorEditorOutlinerContextMenu`  
_L13-21_
- desc: Context menu actions in outliner related to property animator
- L17 _public prototype_ `static void OnExtendOutlinerContextMenu(UToolMenu* InToolMenu);` — Extend outliner context menu
- L20 _public prototype_ `static void GetContextObjects(const UAvaOutlinerItemsContext* InContext, TSet<UObject*>& OutObjects);` — Gets all pertinent context object in this context

### `Plugins/VirtualProduction/Avalanche/Source/AvalanchePropertyAnimatorEditor/Private/Outliner/AvaPropertyAnimatorEditorOutlinerDropHandler.h` (Private)


#### class `FAvaPropertyAnimatorEditorOutlinerDropHandler`  
`class FAvaPropertyAnimatorEditorOutlinerDropHandler : public FAvaOutlinerItemDropHandler`  
_L10-26_
- inherits: `FAvaOutlinerItemDropHandler`
- desc: Class that handles dropping animator item into a target item
- L13 _public prototype_ `UE_AVA_INHERITS(FAvaPropertyAnimatorEditorOutlinerDropHandler, FAvaOutlinerItemDropHandler);`
- L17 _protected prototype_ `virtual bool IsDraggedItemSupported(const FAvaOutlinerItemPtr& InDraggedItem) const override;`
- L18 _protected prototype_ `virtual TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) const override;`
- L19 _protected prototype_ `virtual bool Drop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) override;`
- L22 _protected prototype_ `TSet<UPropertyAnimatorCoreBase*> GetDraggedAnimators() const;`
- L23 _protected prototype_ `TOptional<EItemDropZone> CanDropOnActor(AActor* InActor, EItemDropZone InDropZone) const;`
- L24 _protected prototype_ `bool DropAnimatorsOnActor(AActor* InActor, EItemDropZone InDropZone) const;`
- L25 _protected prototype_ `bool DropAnimatorsOnAnimator(UPropertyAnimatorCoreBase* InTargetAnimator, EItemDropZone InDropZone) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalanchePropertyAnimatorEditor/Private/Outliner/AvaPropertyAnimatorEditorOutlinerProxy.h` (Private)


#### class `FAvaPropertyAnimatorEditorOutlinerProxy`  
`class FAvaPropertyAnimatorEditorOutlinerProxy : public FAvaOutlinerItemProxy`  
_L13-44_
- inherits: `FAvaOutlinerItemProxy`
- desc: Creates property animator based on all the item found in the component of an Actor
- L16 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaPropertyAnimatorEditorOutlinerProxy, FAvaOutlinerItemProxy);`
- L18 _public prototype_ `FAvaPropertyAnimatorEditorOutlinerProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L20 _public prototype_ `UPropertyAnimatorCoreComponent* GetPropertyAnimatorComponent() const;`
- L23 _public prototype_ `virtual void OnItemRegistered() override;`
- L24 _public prototype_ `virtual void OnItemUnregistered() override;`
- L25 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L28 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L29 _public prototype_ `virtual bool CanDelete() const override;`
- L30 _public prototype_ `virtual bool Delete() override;`
- L34 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`
- L38 _protected prototype_ `void BindDelegates();`
- L39 _protected prototype_ `void UnbindDelegates();`
- L41 _protected prototype_ `void OnPropertyAnimatorUpdated(UPropertyAnimatorCoreComponent* InComponent, UPropertyAnimatorCoreBase* InAnimator, EPropertyAnimatorCoreUpdateEvent InReason);`
- L43 _protected member_ `FSlateIcon ItemIcon;`
