# Plugins / LiveLinkFaceSourceEditor

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSourceEditor`
- headers: 3; symbols: 31
- symbol kinds: class=3, delegate=1, function=1, member=13, namespace=1, prototype=12
- PrivateDependencyModuleNames: CaptureProtocolStack, CaptureUtils, Core, CoreUObject, Engine, InputCore, LiveLinkFaceDiscovery, LiveLinkFaceSource, LiveLinkInterface, Slate, SlateCore, Sockets
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSourceEditor/Private/LiveLinkFaceSourceCustomization.h` (Private)


#### class `FLiveLinkFaceSourceCustomization`  
`class FLiveLinkFaceSourceCustomization : public IDetailCustomization`  
_L14-44_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `FLiveLinkFaceSourceCustomization();`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;` — Start IDetailCustomization Interface
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L29 _private member_ `bool bIsConnectEnabled = false;`
- L31 _private member_ `FTextBlockStyle ButtonTextStyle;`
- L33 _private member_ `TSharedPtr<SLiveLinkFaceDiscoveryPanel> DiscoveryPanel;`
- L34 _private member_ `TSharedPtr<SEditableTextBox> AddressTextBox;`
- L35 _private member_ `TSharedPtr<SNumericEntryBox<uint16>> PortEntryBox;`
- L36 _private member_ `TSharedPtr<SEditableTextBox> SubjectNameTextBox;`
- L38 _private prototype_ `bool Validate(const ULiveLinkFaceSourceSettings* InSettings);`
- L40 _private member_ `TSharedRef<FLiveLinkFaceDiscovery> LiveLinkFaceDiscovery;`
- L42 _private member_ `TArray<TSharedPtr<FLiveLinkFaceDiscovery::FServer>> ListServers;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSourceEditor/Private/LiveLinkFaceSourceEditorModule.h` (Private)


#### class `FLiveLinkFaceSourceEditorModule`  
`class FLiveLinkFaceSourceEditorModule : public IModuleInterface`  
_L7-22_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L20 _private prototype_ `void PostEngineInit();`
- L21 _private prototype_ `void EnginePreExit();`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSourceEditor/Private/SLiveLinkFaceDiscoveryPanel.h` (Private)


#### class `SLiveLinkFaceDiscoveryPanel`  
`class SLiveLinkFaceDiscoveryPanel : public SCompoundWidget`  
_L20-47_
- inherits: `SCompoundWidget`
- L22 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkFaceDiscoveryPanel)`
- L23 _private prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<FLiveLinkFaceDiscovery::FServer>>*, Servers) SLATE_EVENT(FOnLiveLinkFaceServerSelected, OnServerSingleClicked) SLATE_EVENT(FOnLiveLinkFaceServerSelected, OnServerDoubleClicked) SLATE_END_ARGS() SLiveLinkFaceDiscoveryPanel();`
- L30 _private prototype_ `void Construct(const FArguments& Args);`
- L32 _private prototype_ `void Refresh() const;`
- L36 _private member_ `FSlateColorBrush DiscoveryListBorderBrush;`
- L39 _private member_ `TSharedPtr<SListView<TSharedPtr<FLiveLinkFaceDiscovery::FServer>>> ListView;` — The widgets displayed in the list.
- L42 _private member_ `FOnLiveLinkFaceServerSelected OnServerSingleClicked;` — A server in the list was single-clicked.
- L45 _private member_ `FOnLiveLinkFaceServerSelected OnServerDoubleClicked;` — A server in the list was double-clicked.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ESelectInfo`
- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLiveLinkFaceServerSelected, FString Address, uint16 Port);`
- L18 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnLiveLinkFaceServerSelected, FString Address, uint16 Port);`
