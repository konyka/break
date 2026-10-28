# Plugins / LiveLinkMasterLockitEditor

- module root: `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockitEditor`
- headers: 2; symbols: 10
- symbol kinds: class=2, function=1, member=3, prototype=4
- PrivateDependencyModuleNames: Core, CoreUObject, LiveLinkMasterLockit, PropertyEditor, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockitEditor/Private/LiveLinkMasterLockitEditorModule.h` (Private)


#### class `FLiveLinkMasterLockitEditorModule`  
`class FLiveLinkMasterLockitEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockitEditor/Private/LiveLinkMasterLockitSourcePanel.h` (Private)


#### class `SLiveLinkMasterLockitSourcePanel`  
`class SLiveLinkMasterLockitSourcePanel : public SCompoundWidget`  
_L12-28_
- inherits: `SCompoundWidget`
- L14 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkMasterLockitSourcePanel)`
- L15 _private prototype_ `SLATE_ARGUMENT(const ULiveLinkMasterLockitSourceFactory*, Factory) SLATE_EVENT(ULiveLinkSourceFactory::FOnLiveLinkSourceCreated, OnSourceCreated) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L22 _public prototype_ `FReply CreateNewSource(bool bShouldCreateSource);`
- L25 _private member_ `FLiveLinkMasterLockitConnectionSettings ConnectionSettings;`
- L26 _private member_ `TWeakObjectPtr<const ULiveLinkMasterLockitSourceFactory> SourceFactory;`
- L27 _private member_ `ULiveLinkSourceFactory::FOnLiveLinkSourceCreated OnSourceCreated;`
