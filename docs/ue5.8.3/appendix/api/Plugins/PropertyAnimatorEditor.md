# Plugins / PropertyAnimatorEditor

- module root: `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimatorEditor`
- headers: 5; symbols: 64
- symbol kinds: class=5, function=25, member=7, prototype=18, struct=2, typedef=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MovieScene, MovieSceneTools, Projects, PropertyAnimator, PropertyAnimatorCore, PropertyAnimatorCoreEditor, Sequencer, SequencerCore, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimatorEditor/Private/Customizations/PropertyAnimatorEditorCounterDetailCustomization.h` (Private)


#### class `FPropertyAnimatorEditorCounterDetailCustomization`  
`class FPropertyAnimatorEditorCounterDetailCustomization : public IDetailCustomization`  
_L11-27_
- inherits: `IDetailCustomization`
- desc: Details customization for UPropertyAnimatorCounter
- L14 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L24 _protected prototype_ `void OnConditionPropertyChanged() const;`
- L26 _protected member_ `TSharedPtr<IPropertyHandle> UseCustomFormatHandle;`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimatorEditor/Private/PropertyAnimatorEditorModule.h` (Private)


#### class `FPropertyAnimatorEditorModule`  
`class FPropertyAnimatorEditorModule : public IModuleInterface`  
_L12-27_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public function_ `template<typename InCurveChannelType> void RegisterCurveChannelInterface(ISequencerModule& InSequencerModule)`

#### Free symbols / members of external scopes

- L23 _typedef_ `using FMenuExtensionType = TPropertyAnimatorEditorCurveSectionMenuExtension<InCurveChannelType>;` (scope `FPropertyAnimatorEditorModule::RegisterCurveChannelInterface`)
- L24 _typedef_ `using FChannelInterfaceType = TPropertyAnimatorEditorCurveChannelInterface<InCurveChannelType, FMenuExtensionType>;` (scope `FPropertyAnimatorEditorModule::RegisterCurveChannelInterface`)

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimatorEditor/Private/Sequencer/PropertyAnimatorEditorCurveChannelInterface.h` (Private)


#### struct `TPropertyAnimatorEditorCurveChannelInterface`  
`template<typename InChannelType, typename InMenuExtensionType> struct TPropertyAnimatorEditorCurveChannelInterface : ISequencerChannelInterface`  
_L16-43_
- inherits: `ISequencerChannelInterface`
- L18 _public typedef_ `using FChannelType = InChannelType;`
- L19 _public typedef_ `using FMenuExtensionType = InMenuExtensionType;`
- L20 _public typedef_ `using FCurveValueType = typename InChannelType::CurveValueType;`
- L21 _public typedef_ `using FKeyEditor = TSequencerKeyEditor<FChannelType, FCurveValueType>;`
- L22 _public typedef_ `using SKeyEditorWidget = SNumericTextBlockKeyEditor<FChannelType, FCurveValueType>;`
- L25 _public function_ `virtual FKeyHandle AddOrUpdateKey_Raw(FMovieSceneChannel*, UMovieSceneSection*, const void*, FFrameNumber, ISequencer&, const FGuid&, FTrackInstancePropertyBindings*) const override`
- L26 _public function_ `virtual void DeleteKeys_Raw(FMovieSceneChannel*, TConstArrayView<FKeyHandle>, FFrameNumber) const override`
- L27 _public function_ `virtual void CopyKeys_Raw(FMovieSceneChannel*, const UMovieSceneSection*, FName, FMovieSceneClipboardBuilder&, TConstArrayView<FKeyHandle>) const override`
- L28 _public function_ `virtual void PasteKeys_Raw(FMovieSceneChannel*, UMovieSceneSection*, const FMovieSceneClipboardKeyTrack&, const FMovieSceneClipboardEnvironment&, const FSequencerPasteEnvironment&, TArray<FKeyHandle>&) const override`
- L29 _public function_ `virtual TSharedPtr<FStructOnScope> GetKeyStruct_Raw(FMovieSceneChannelHandle, FKeyHandle) const override`
- L30 _public function_ `virtual bool CanCreateKeyEditor_Raw(const FMovieSceneChannel*) const override`
- L31 _public function_ `virtual void ExtendKeyMenu_Raw(FMenuBuilder&, TSharedPtr<FExtender>, TConstArrayView<FExtendKeyMenuParams>, TWeakPtr<ISequencer>) const override`
- L32 _public function_ `virtual void DrawKeys_Raw(FMovieSceneChannel*, TConstArrayView<FKeyHandle>, const UMovieSceneSection*, TArrayView<FKeyDrawParams>) const override`
- L33 _public function_ `virtual bool ShouldShowCurve_Raw(const FMovieSceneChannel*, UMovieSceneSection*) const override`
- L34 _public function_ `virtual bool SupportsCurveEditorModels_Raw(const FMovieSceneChannelHandle&) const override`
- L35 _public function_ `virtual TUniquePtr<FCurveModel> CreateCurveEditorModel_Raw(const FMovieSceneChannelHandle&, const UE::Sequencer::FCreateCurveEditorModelParams& Params) const override`
- L36 _public function_ `virtual TSharedPtr<UE::Sequencer::FChannelModel> CreateChannelModel_Raw(const FMovieSceneChannelHandle&, const UE::Sequencer::FSectionModel& InSection, FName) const override`
- L37 _public function_ `virtual TSharedPtr<UE::Sequencer::STrackAreaLaneView> CreateChannelView_Raw(const FMovieSceneChannelHandle&, TWeakPtr<UE::Sequencer::FChannelModel>, const UE::Sequencer::FCreateTrackLaneViewParams&) const override`
- L38 _public prototype_ `virtual void ExtendSectionMenu_Raw(FMenuBuilder& MenuBuilder, TSharedPtr<FExtender> InMenuExtender, TConstArrayView<FMovieSceneChannelHandle> InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer) const override;`
- L39 _public prototype_ `virtual TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu_Raw(FMenuBuilder& MenuBuilder, TSharedPtr<FExtender> InMenuExtender, TConstArrayView<FMovieSceneChannelHandle> InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer) const override;`
- L40 _public prototype_ `virtual int32 DrawExtra_Raw(FMovieSceneChannel* InChannel, const UMovieSceneSection* InOwner, const FSequencerChannelPaintArgs& InPaintArgs, int32 InLayerId) const override;`
- L41 _public prototype_ `virtual TSharedRef<SWidget> CreateKeyEditor_Raw(const FMovieSceneChannelHandle& InChannel, const UE::Sequencer::FCreateKeyEditorParams& Params) const override;`
- L46 _function_ `template<typename InChannelType, typename InMenuExtensionType> void TPropertyAnimatorEditorCurveChannelInterface<InChannelType, InMenuExtensionType>::ExtendSectionMenu_Raw(FMenuBuilder& MenuBuilder , TSharedPtr<FExtender> InMenuExtender , TConstArrayView<FMovieSceneChannelHandle> InChannels , const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections , TWeakPtr<ISequencer> InWeakSequencer) const`
- L62 _function_ `template<typename InChannelType, typename InMenuExtensionType> TSharedPtr<ISidebarChannelExtension> TPropertyAnimatorEditorCurveChannelInterface<InChannelType, InMenuExtensionType>::ExtendSidebarMenu_Raw(FMenuBuilder& MenuBuilder , TSharedPtr<FExtender> InMenuExtender , TConstArrayView<FMovieSceneChannelHandle> InChannels , const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections , TWeakPtr<ISequencer> InWeakSequencer) const`
- L74 _function_ `template<typename InChannelType, typename InMenuExtensionType> int32 TPropertyAnimatorEditorCurveChannelInterface<InChannelType, InMenuExtensionType>::DrawExtra_Raw(FMovieSceneChannel* InChannel , const UMovieSceneSection* InOwner , const FSequencerChannelPaintArgs& InPaintArgs , int32 InLayerId) const`
- L117 _function_ `template<typename InChannelType, typename InMenuExtensionType> TSharedRef<SWidget> TPropertyAnimatorEditorCurveChannelInterface<InChannelType, InMenuExtensionType>::CreateKeyEditor_Raw(const FMovieSceneChannelHandle& InChannel , const UE::Sequencer::FCreateKeyEditorParams& Params) const`

#### Free symbols / members of external scopes

- L56 _function_ `` (scope `TPropertyAnimatorEditorCurveChannelInterface::ExtendSectionMenu_Raw`)

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimatorEditor/Private/Sequencer/PropertyAnimatorEditorCurveSectionMenuExtension.h` (Private)


#### class `FPropertyAnimatorEditorCurveSectionMenuExtension`  
`class FPropertyAnimatorEditorCurveSectionMenuExtension : public TSharedFromThis<FPropertyAnimatorEditorCurveSectionMenuExtension>, public ISidebarChannelExtension`  
_L15-55_
- inherits: `TSharedFromThis<FPropertyAnimatorEditorCurveSectionMenuExtension>,ISidebarChannelExtension`
- L34 _public prototype_ `FPropertyAnimatorEditorCurveSectionMenuExtension(TConstArrayView<FMovieSceneChannelHandle> InChannelHandles, const TConstArrayView<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections);`
- L35 _public prototype_ `virtual ~FPropertyAnimatorEditorCurveSectionMenuExtension() = default;`
- L37 _public prototype_ `virtual bool GetParameterStructData(FMovieSceneChannelHandle InChannelHandle, UStruct*& OutStruct, uint8*& OutData) const = 0;`
- L39 _public prototype_ `virtual TSharedPtr<ISidebarChannelExtension> ExtendMenu(FMenuBuilder& InMenuBuilder, const bool bInSubMenu) override;`
- L42 _private prototype_ `void Initialize();`
- L44 _private prototype_ `void BuildChannelsMenu(FMenuBuilder& InMenuBuilder);`
- L46 _private prototype_ `void BuildParametersMenu(FMenuBuilder& InMenuBuilder, int32 InChannelHandleIndex);`
- L48 _private member_ `TArray<FMovieSceneChannelHandle> ChannelHandles;`
- L50 _private member_ `TArray<int32> ChannelHandleSectionIndexes;`
- L52 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSection>> WeakSections;`
- L54 _private member_ `TArray<FChannelNotifyHook> NotifyHooks;`

#### struct `FPropertyAnimatorEditorCurveSectionMenuExtension::FChannelNotifyHook`  
`struct FChannelNotifyHook : FNotifyHook`  
_L17-31_
- inherits: `FNotifyHook`
- L19 _public function_ `explicit FChannelNotifyHook(UObject* InObjectToModify) : ObjectToModifyWeak(InObjectToModify)`
- L25 _public prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L26 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L29 _public member_ `TWeakObjectPtr<UObject> ObjectToModifyWeak;`
- L30 _public member_ `int32 TransactionIndex = INDEX_NONE;`

#### class `TPropertyAnimatorEditorCurveSectionMenuExtension`  
`template<typename InChannelType> class TPropertyAnimatorEditorCurveSectionMenuExtension : public FPropertyAnimatorEditorCurveSectionMenuExtension`  
_L58-82_
- inherits: `FPropertyAnimatorEditorCurveSectionMenuExtension`
- L61 _public function_ `TPropertyAnimatorEditorCurveSectionMenuExtension(const TConstArrayView<FMovieSceneChannelHandle>& InChannelHandles, const TConstArrayView<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections) : FPropertyAnimatorEditorCurveSectionMenuExtension(InChannelHandles, InWeakSections)`
- L67 _public function_ `template<typename InParameterType> UStruct* GetParameterStruct(const InParameterType& InParameters) const`
- L72 _public function_ `virtual bool GetParameterStructData(FMovieSceneChannelHandle InChannelHandle, UStruct*& OutStruct, uint8*& OutData) const override`

### `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimatorEditor/Private/Styles/PropertyAnimatorEditorStyle.h` (Private)


#### class `FPropertyAnimatorEditorStyle`  
`class FPropertyAnimatorEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FPropertyAnimatorEditorStyle();`
- L14 _public function_ `static FPropertyAnimatorEditorStyle& Get()`
