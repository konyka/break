# Plugins / MetaHumanLocalLiveLinkSourceEditor

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor`
- headers: 6; symbols: 23
- symbol kinds: class=6, member=4, prototype=13
- PrivateDependencyModuleNames: Core, CoreUObject, EditorStyle, Engine, LiveLinkInterface, MetaHumanCoreTech, MetaHumanImageViewer, MetaHumanLiveLinkSource, MetaHumanLocalLiveLinkSource, MetaHumanPipelineCore, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor/Private/MetaHumanAudioBaseLiveLinkSubjectCustomization.h` (Private)


#### class `FMetaHumanAudioBaseLiveLinkSubjectCustomization`  
`class FMetaHumanAudioBaseLiveLinkSubjectCustomization : public FMetaHumanLocalLiveLinkSubjectCustomization`  
_L9-16_
- inherits: `FMetaHumanLocalLiveLinkSubjectCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor/Private/MetaHumanAudioLiveLinkSourceCustomization.h` (Private)


#### class `FMetaHumanAudioLiveLinkSourceCustomization`  
`class FMetaHumanAudioLiveLinkSourceCustomization : public IDetailCustomization, public FMetaHumanMediaSourceCustomization`  
_L11-18_
- inherits: `IDetailCustomization,FMetaHumanMediaSourceCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor/Private/MetaHumanLocalLiveLinkSubjectCustomization.h` (Private)


#### class `FMetaHumanLocalLiveLinkSubjectCustomization`  
`class FMetaHumanLocalLiveLinkSubjectCustomization : public IDetailCustomization`  
_L11-22_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L21 _private member_ `FTextBlockStyle ButtonTextStyle;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor/Private/MetaHumanMediaSourceCustomization.h` (Private)


#### class `FMetaHumanMediaSourceCustomization`  
`class FMetaHumanMediaSourceCustomization`  
_L9-23_
- L14 _protected prototype_ `void Setup(IDetailLayoutBuilder& InDetailBuilder, bool bInIsVideo);`
- L16 _protected member_ `TSharedPtr<class SMetaHumanMediaSourceWidget> MediaSource;`
- L17 _protected member_ `TSharedPtr<class SEditableTextBox> SubjectName;`
- L19 _protected member_ `FTextBlockStyle ButtonTextStyle;`
- L21 _protected prototype_ `void AddRow(IDetailCategoryBuilder& InCategoryBuilder, FText InText, TSharedPtr<SWidget> InWidget, bool bInIsAdvanced = false, FText InToolTip = FText());`
- L22 _protected prototype_ `FText ValidateSubjectName() const;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor/Private/MetaHumanVideoBaseLiveLinkSubjectCustomization.h` (Private)


#### class `FMetaHumanVideoBaseLiveLinkSubjectCustomization`  
`class FMetaHumanVideoBaseLiveLinkSubjectCustomization : public FMetaHumanLocalLiveLinkSubjectCustomization`  
_L9-16_
- inherits: `FMetaHumanLocalLiveLinkSubjectCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSourceEditor/Private/MetaHumanVideoLiveLinkSourceCustomization.h` (Private)


#### class `FMetaHumanVideoLiveLinkSourceCustomization`  
`class FMetaHumanVideoLiveLinkSourceCustomization : public IDetailCustomization, public FMetaHumanMediaSourceCustomization`  
_L11-18_
- inherits: `IDetailCustomization,FMetaHumanMediaSourceCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
