# Plugins / MetaHumanLiveLinkSourceEditor

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSourceEditor`
- headers: 3; symbols: 13
- symbol kinds: class=3, member=3, prototype=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MetaHumanCoreTech, MetaHumanLiveLinkSource, Slate, SlateCore
- PublicDependencyModuleNames: LiveLinkInterface, UnrealEd

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSourceEditor/Private/MetaHumanLiveLinkSourceEditorModule.h` (Private)


#### class `FMetaHumanLiveLinkSourceEditorModule`  
`class FMetaHumanLiveLinkSourceEditorModule : public IModuleInterface`  
_L7-19_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`
- L18 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSourceEditor/Private/MetaHumanSmoothingPreProcessorCustomization.h` (Private)


#### class `FMetaHumanSmoothingPreProcessorCustomization`  
`class FMetaHumanSmoothingPreProcessorCustomization: public IPropertyTypeCustomization`  
_L7-14_
- inherits: `IPropertyTypeCustomization`
- L10 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L11 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLiveLinkSourceEditor/Public/MetaHumanLiveLinkSubjectSettingsCustomization.h` (Public)


#### class `FMetaHumanLiveLinkSubjectSettingsCustomization`  
`class FMetaHumanLiveLinkSubjectSettingsCustomization : public IDetailCustomization`  
_L11-22_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L21 _private member_ `FTextBlockStyle ButtonTextStyle;`
