# Plugins / AvalancheDataLinkEditor

- module root: `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLinkEditor`
- headers: 5; symbols: 34
- symbol kinds: class=5, function=3, member=7, namespace=2, prototype=17
- PrivateDependencyModuleNames: AvalancheDataLink, AvalancheInteractiveTools, Core, CoreUObject, Engine, InteractiveToolsFramework, PropertyEditor, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLinkEditor/Private/AvaDataLinkActorTool.h` (Private)


#### class `UAvaDataLinkActorTool`  
`class UAvaDataLinkActorTool : public UAvaInteractiveToolsActorToolBase`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorToolBase`
- L14 _public prototype_ `UAvaDataLinkActorTool();`
- L17 _public prototype_ `virtual bool ShouldForceDefaultAction() const override;`
- L18 _public prototype_ `virtual bool SupportsDefaultAction() const override;`
- L19 _public prototype_ `virtual bool OnBegin() override;`
- L20 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLinkEditor/Private/AvaDataLinkEditorCommands.h` (Private)


#### class `UE::AvaDataLink::FEditorCommands`  
`class FEditorCommands : public TCommands<FEditorCommands>`  
_L10-21_
- inherits: `TCommands<FEditorCommands>`
- L13 _public prototype_ `FEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> DataLinkActorTool;` — Command used to spawn the Motion Design Data Link Actor

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaDataLink` (scope `UE`)

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLinkEditor/Private/AvaDataLinkEditorModule.h` (Private)


#### class `FAvaDataLinkEditorModule`  
`class FAvaDataLinkEditorModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L12 _private prototype_ `virtual void StartupModule() override;`
- L13 _private prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `TArray<FName> CustomizedClasses;`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLinkEditor/Private/DetailsView/AvaDataLinkControllerMappingsBuilder.h` (Private)


#### class `FAvaDataLinkControllerMappingsBuilder`  
`class FAvaDataLinkControllerMappingsBuilder : public IDetailCustomNodeBuilder`  
_L10-36_
- inherits: `IDetailCustomNodeBuilder`
- L13 _public prototype_ `explicit FAvaDataLinkControllerMappingsBuilder(const TSharedRef<IPropertyHandle>& InControllerMappingsHandle, TWeakPtr<IDetailsView> InDetailsViewWeak);`
- L16 _public prototype_ `virtual FName GetName() const override;`
- L17 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;`
- L18 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override;`
- L19 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L20 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L21 _public function_ `virtual bool InitiallyCollapsed() const`
- L22 _public function_ `virtual bool RequiresTick() const override`
- L23 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L27 _private member_ `TSharedRef<IPropertyHandle> ControllerMappingsHandle;`
- L29 _private member_ `TSharedRef<IPropertyHandleArray> ArrayHandle;`
- L31 _private member_ `FSimpleDelegate OnRegenerateChildren;`
- L33 _private member_ `TWeakPtr<IDetailsView> DetailsViewWeak;`
- L35 _private member_ `uint32 CachedNumChildren = 0;`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLinkEditor/Private/DetailsView/AvaDataLinkInstanceCustomization.h` (Private)


#### class `FAvaDataLinkInstanceCustomization`  
`class FAvaDataLinkInstanceCustomization : public IDetailCustomization`  
_L7-19_
- inherits: `IDetailCustomization`
- L10 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L17 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
