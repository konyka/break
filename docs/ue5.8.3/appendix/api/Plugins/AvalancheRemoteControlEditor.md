# Plugins / AvalancheRemoteControlEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor`
- headers: 6; symbols: 62
- symbol kinds: class=6, function=2, member=11, prototype=42, struct=1
- PrivateDependencyModuleNames: AvalancheEditorCore, AvalancheOutliner, AvalancheRemoteControl, Core, CoreUObject, Engine, InputCore, RemoteControl, RemoteControlComponents, RemoteControlComponentsEditor, RemoteControlUI, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor/Private/AvalancheRemoteControlEditorModule.h` (Private)


#### class `FAvalancheRemoteControlEditorModule`  
`class FAvalancheRemoteControlEditorModule : public IModuleInterface`  
_L7-20_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;`
- L11 _private prototype_ `virtual void ShutdownModule() override;`
- L14 _private prototype_ `void RegisterCustomizations();`
- L15 _private prototype_ `void UnregisterCustomizations();`
- L17 _private member_ `FDelegateHandle OutlinerProxiesExtensionDelegateHandle;`
- L19 _private member_ `TArray<FName> CustomPropertyTypeLayouts;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor/Private/Customizations/AvaRCControllerIdCustomization.h` (Private)


#### class `FAvaRCControllerIdCustomization`  
`class FAvaRCControllerIdCustomization : public IPropertyTypeCustomization`  
_L7-16_
- inherits: `IPropertyTypeCustomization`
- L10 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L13 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L14 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor/Private/Customizations/Widgets/SAvaRCControllerPicker.h` (Private)


#### struct `FAvaRCControllerPickerOption`  
`struct FAvaRCControllerPickerOption`  
_L12-15_
- L14 _public member_ `FName ControllerName;`

#### class `SAvaRCControllerPicker`  
`class SAvaRCControllerPicker : public SCompoundWidget`  
_L17-47_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAvaRCControllerPicker)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InControllerIdHandle);`
- L26 _private prototype_ `FText GetControllerName() const;`
- L28 _private prototype_ `void SetControllerName(FName InControllerName);`
- L30 _private prototype_ `void OnControllerNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L32 _private prototype_ `void RefreshOptions();`
- L34 _private prototype_ `void OnOptionSelectionChanged(TSharedPtr<FAvaRCControllerPickerOption> InSelectedOption, ESelectInfo::Type InSelectInfo);`
- L36 _private prototype_ `TSharedRef<SWidget> GenerateOptionWidget(TSharedPtr<FAvaRCControllerPickerOption> InOption);`
- L38 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FAvaRCControllerPickerOption>>> ComboBox;`
- L40 _private member_ `TWeakObjectPtr<ULevel> LevelWeak;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L44 _private member_ `TArray<TSharedPtr<FAvaRCControllerPickerOption>> Options;`
- L46 _private member_ `TSharedPtr<FAvaRCControllerPickerOption> SelectedOption;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor/Private/Outliner/AvaOutlinerRCComponentsContextMenu.h` (Private)


#### class `FAvaOutlinerRCComponentsContextMenu`  
`class FAvaOutlinerRCComponentsContextMenu`  
_L12-30_
- L16 _public prototype_ `static void OnExtendOutlinerContextMenu(UToolMenu* InToolMenu);` — Extend outliner context menu
- L19 _private prototype_ `static void GetActorItems(const UToolMenu* InToolMenu, TSet<TWeakObjectPtr<AActor>>& OutActors);`
- L20 _private prototype_ `static void AddRemoteControlComponentsMenuEntries(UToolMenu* InToolMenu, const TSet<TWeakObjectPtr<AActor>>& OutObjects);`
- L22 _private prototype_ `static void ExecuteUnexposeAllPropertiesAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L23 _private prototype_ `static bool CanExecuteUnexposeAllPropertiesAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L25 _private prototype_ `static void ExecuteAddTrackerAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L26 _private prototype_ `static bool CanExecuteAddTrackerAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L28 _private prototype_ `static void ExecuteRemoveTrackerAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L29 _private prototype_ `static bool DoesSelectionHaveTrackerComponent(TSet<TWeakObjectPtr<AActor>> InActors);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor/Private/Outliner/AvaOutlinerRCTrackerComponent.h` (Private)


#### class `FAvaOutlinerRCTrackerComponent`  
`class FAvaOutlinerRCTrackerComponent : public FAvaOutlinerObject`  
_L14-37_
- inherits: `FAvaOutlinerObject`
- desc: Inheriting from FAvaOutlinerObject and not from FAvaOutlinerComponent, which only takes into account Scene Components. This class needs instead to handle URemoteControlTrackerComponent, which is of type UActorComponent, and not Scene Component.
- L17 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerRCTrackerComponent, FAvaOutlinerObject);`
- L19 _public prototype_ `FAvaOutlinerRCTrackerComponent(IAvaOutliner& InOutliner, URemoteControlTrackerComponent* InComponent);`
- L22 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L23 _public prototype_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType InVisibilityType) const override;`
- L24 _public prototype_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType InVisibilityType) const override;`
- L25 _public prototype_ `virtual void OnVisibilityChanged(EAvaOutlinerVisibilityType InVisibilityType, bool bInNewVisibility) override;`
- L26 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L31 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L34 _protected member_ `TWeakObjectPtr<URemoteControlTrackerComponent> TrackerComponentWeak;`
- L36 _protected member_ `FSlateIcon TrackerIcon;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControlEditor/Private/Outliner/AvaOutlinerRCTrackerComponentProxy.h` (Private)


#### class `FAvaOutlinerRCTrackerComponentProxy`  
`class FAvaOutlinerRCTrackerComponentProxy : public FAvaOutlinerItemProxy`  
_L10-38_
- inherits: `FAvaOutlinerItemProxy`
- L13 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerRCTrackerComponentProxy, FAvaOutlinerItemProxy);`
- L15 _public prototype_ `FAvaOutlinerRCTrackerComponentProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L17 _public prototype_ `URemoteControlTrackerComponent* GetTrackerComponent() const;`
- L20 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L21 _public prototype_ `virtual FText GetDisplayName() const override;`
- L22 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L23 _public prototype_ `virtual void OnItemRegistered() override;`
- L24 _public prototype_ `virtual void OnItemUnregistered() override;`
- L28 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`
- L32 _protected prototype_ `void BindDelegates();`
- L33 _protected prototype_ `void UnbindDelegates();`
- L35 _protected prototype_ `void OnTrackedActorsChanged(AActor* InActor);`
- L37 _protected member_ `FSlateIcon TrackerIcon;`
