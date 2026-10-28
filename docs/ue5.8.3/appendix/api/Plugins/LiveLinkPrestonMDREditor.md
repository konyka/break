# Plugins / LiveLinkPrestonMDREditor

- module root: `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDREditor`
- headers: 2; symbols: 10
- symbol kinds: class=2, function=1, member=3, prototype=4
- PrivateDependencyModuleNames: Core, CoreUObject, LiveLinkPrestonMDR, PropertyEditor, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDREditor/Private/LiveLinkPrestonMDREditorModule.h` (Private)


#### class `FLiveLinkPrestonMDREditorModule`  
`class FLiveLinkPrestonMDREditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDREditor/Private/LiveLinkPrestonMDRSourcePanel.h` (Private)


#### class `SLiveLinkPrestonMDRSourcePanel`  
`class SLiveLinkPrestonMDRSourcePanel : public SCompoundWidget`  
_L12-28_
- inherits: `SCompoundWidget`
- L14 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkPrestonMDRSourcePanel)`
- L15 _private prototype_ `SLATE_ARGUMENT(const ULiveLinkPrestonMDRSourceFactory*, Factory) SLATE_EVENT(ULiveLinkSourceFactory::FOnLiveLinkSourceCreated, OnSourceCreated) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L22 _public prototype_ `FReply CreateNewSource(bool bShouldCreateSource);`
- L25 _private member_ `FLiveLinkPrestonMDRConnectionSettings ConnectionSettings;`
- L26 _private member_ `TWeakObjectPtr<const ULiveLinkPrestonMDRSourceFactory> SourceFactory;`
- L27 _private member_ `ULiveLinkSourceFactory::FOnLiveLinkSourceCreated OnSourceCreated;`
