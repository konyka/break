# Plugins / PropertyAnimatorCoreEditor

- module root: `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor`
- headers: 15; symbols: 226
- symbol kinds: class=14, delegate=2, enum=1, enumerator=7, function=21, member=26, namespace=3, prototype=148, struct=4
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, CoreUObject, EditorSubsystem, EditorWidgets, Engine, InputCore, LevelSequence, MovieScene, MovieSceneTools, OperatorStackEditor, Projects, PropertyAnimatorCore, PropertyEditor, Sequencer, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Customizations/PropertyAnimatorCoreEditorContextTypeCustomization.h` (Private)


#### class `FPropertyAnimatorCoreEditorContextTypeCustomization`  
`class FPropertyAnimatorCoreEditorContextTypeCustomization : public IPropertyTypeCustomization`  
_L15-34_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for UPropertyAnimatorCoreContext
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L29 _protected prototype_ `ECheckBoxState IsPropertyEnabled() const;`
- L30 _protected prototype_ `void OnPropertyEnabled(ECheckBoxState InNewState) const;`
- L31 _protected prototype_ `FReply UnlinkProperty() const;`
- L33 _protected member_ `TSharedPtr<IPropertyHandle> PropertyContextHandle;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Customizations/PropertyAnimatorCoreEditorDetailCustomization.h` (Private)


#### class `FPropertyAnimatorCoreEditorDetailCustomization`  
`class FPropertyAnimatorCoreEditorDetailCustomization : public IDetailCustomization`  
_L16-45_
- inherits: `IDetailCustomization`
- desc: Details customization for UPropertyAnimatorCoreBase
- L19 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L29 _protected prototype_ `static void FillLinkMenu(UToolMenu* InToolMenu);`
- L31 _protected prototype_ `TSharedRef<SWidget> GenerateLinkMenu();`
- L33 _protected prototype_ `bool IsAnyPropertyLinked() const;`
- L34 _protected prototype_ `ECheckBoxState IsPropertiesEnabled() const;`
- L35 _protected prototype_ `void OnPropertiesEnabled(ECheckBoxState InNewState) const;`
- L37 _protected prototype_ `int32 GetPropertiesCount() const;`
- L38 _protected prototype_ `FText GetPropertiesCountText() const;`
- L40 _protected prototype_ `FReply UnlinkProperties() const;`
- L42 _protected prototype_ `FReply OnCreatePropertyPresetClicked() const;`
- L44 _protected member_ `TArray<TWeakObjectPtr<UPropertyAnimatorCoreBase>> AnimatorsWeak;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Customizations/PropertyAnimatorCoreEditorManualStateTypeCustomization.h` (Private)


#### class `FPropertyAnimatorCoreEditorManualStateTypeCustomization`  
`class FPropertyAnimatorCoreEditorManualStateTypeCustomization : public IPropertyTypeCustomization`  
_L14-35_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for EPropertyAnimatorCoreManualStatus to show a player
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L28 _protected prototype_ `FReply SetPlaybackStatus(EPropertyAnimatorCoreManualStatus InStatus);`
- L29 _protected prototype_ `FReply ResetPlaybackStatus();`
- L30 _protected prototype_ `bool IsPlaybackStatusAllowed(EPropertyAnimatorCoreManualStatus InStatus) const;`
- L31 _protected prototype_ `FSlateColor IsPlaybackStatusActive(EPropertyAnimatorCoreManualStatus InStatus) const;`
- L33 _protected member_ `TSharedPtr<IPropertyHandle> StatusPropertyHandle;`
- L34 _protected member_ `TSharedPtr<IPropertyHandle> CustomTimePropertyHandle;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Customizations/PropertyAnimatorCoreEditorSeedTypeCustomization.h` (Private)


#### class `FPropertyAnimatorCoreEditorSeedTypeIdentifier`  
`class FPropertyAnimatorCoreEditorSeedTypeIdentifier : public IPropertyTypeIdentifier`  
_L16-25_
- inherits: `IPropertyTypeIdentifier`
- desc: Only allow property customization with "Seed" metadata
- L20 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `FPropertyAnimatorCoreEditorSeedTypeCustomization`  
`class FPropertyAnimatorCoreEditorSeedTypeCustomization : public IPropertyTypeCustomization`  
_L28-43_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for seed properties
- L31 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L37 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L38 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L42 _private prototype_ `static FReply OnGenerateSeedClicked(TWeakPtr<IPropertyHandle> InPropertyHandleWeak);`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Customizations/PropertyAnimatorCoreEditorSequencerTimeSourceEvalResultTypeCustomization.h` (Private)


#### class `FPropertyAnimatorCoreEditorSequencerTimeSourceChannelTypeCustomization`  
`class FPropertyAnimatorCoreEditorSequencerTimeSourceChannelTypeCustomization : public IPropertyTypeCustomization`  
_L16-37_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FPropertyAnimatorCoreSequencerTimeSourceEvalResult
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L30 _protected prototype_ `FReply OnCreateTrackButtonClicked();`
- L31 _protected prototype_ `EVisibility GetCreateTrackButtonVisibility() const;`
- L32 _protected prototype_ `bool IsCreateTrackButtonEnabled() const;`
- L33 _protected prototype_ `TArray<AActor*> GetSelectedActors() const;`
- L34 _protected prototype_ `TArray<UObject*> GetBindingObjects() const;`
- L36 _protected member_ `TSharedPtr<IPropertyHandle> EvalTimePropertyHandle;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Customizations/PropertyAnimatorCoreEditorStackCustomization.h` (Private)


#### class `UPropertyAnimatorCoreEditorStackCustomization`  
`class UPropertyAnimatorCoreEditorStackCustomization : public UOperatorStackEditorStackCustomization`  
_L15-51_
- reflection: `UCLASS()`
- inherits: `UOperatorStackEditorStackCustomization`
- desc: Property Controller customization for operator stack tab
- L20 _public prototype_ `UPropertyAnimatorCoreEditorStackCustomization();`
- L24 _public prototype_ `virtual bool GetRootItem(const FOperatorStackEditorContext& InContext, FOperatorStackEditorItemPtr& OutRootItem) const override;`
- L25 _public prototype_ `virtual bool GetChildrenItem(const FOperatorStackEditorItemPtr& InItem, TArray<FOperatorStackEditorItemPtr>& OutChildrenItems) const override;`
- L26 _public prototype_ `virtual void CustomizeStackHeader(const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorHeaderBuilder& InHeaderBuilder) override;`
- L27 _public prototype_ `virtual void CustomizeItemHeader(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorHeaderBuilder& InHeaderBuilder) override;`
- L28 _public prototype_ `virtual void CustomizeItemBody(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorBodyBuilder& InBodyBuilder) override;`
- L29 _public prototype_ `virtual bool OnIsItemSelectable(const FOperatorStackEditorItemPtr& InItem) override;`
- L30 _public prototype_ `virtual const FSlateBrush* GetIcon() const override;`
- L31 _public prototype_ `virtual bool ShouldFocusCustomization(const FOperatorStackEditorContext& InContext) const override;`
- L36 _protected prototype_ `void RemoveAnimatorAction(FOperatorStackEditorItemPtr InItem) const;` — Remove animator menu action
- L38 _protected prototype_ `bool CanExportAnimator(FOperatorStackEditorItemPtr InItem) const;`
- L39 _protected prototype_ `void ExportAnimatorAction(FOperatorStackEditorItemPtr InItem);`
- L42 _protected prototype_ `void FillAddAnimatorMenuSection(UToolMenu* InToolMenu) const;` — Fill item action menus
- L43 _protected prototype_ `void FillAnimatorHeaderActionMenu(UToolMenu* InToolMenu);`
- L44 _protected prototype_ `void FillAnimatorContextActionMenu(UToolMenu* InToolMenu) const;`
- L46 _protected prototype_ `void OnAnimatorUpdated(UPropertyAnimatorCoreComponent* InComponent, UPropertyAnimatorCoreBase* InAnimator, EPropertyAnimatorCoreUpdateEvent InType);`
- L47 _protected prototype_ `void OnAnimatorRemoved(UPropertyAnimatorCoreComponent* InComponent, UPropertyAnimatorCoreBase* InAnimator, EPropertyAnimatorCoreUpdateEvent InType);`
- L50 _protected prototype_ `TSharedRef<FUICommandList> CreateAnimatorCommands(FOperatorStackEditorItemPtr InItem);` — Create commands for animator

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Menus/PropertyAnimatorCoreEditorMenu.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PropertyAnimatorCoreEditor` (scope `UE`)
- L19 _namespace_ `namespace Menu` (scope `UE::PropertyAnimatorCoreEditor`)
- L23 _prototype_ `void FillNewAnimatorSection(UToolMenu* InMenu, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L25 _prototype_ `void FillExistingAnimatorSection(UToolMenu* InMenu, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L27 _prototype_ `void FillLinkAnimatorSection(UToolMenu* InMenu, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L29 _prototype_ `void FillEnableAnimatorSection(UToolMenu* InMenu, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L31 _prototype_ `void FillDisableAnimatorSection(UToolMenu* InMenu, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L33 _prototype_ `void FillDeleteAnimatorSection(UToolMenu* InMenu, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L37 _prototype_ `void FillNewAnimatorSubmenu(UToolMenu* InMenu, UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCoreAnimatorPreset* InAnimatorPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L39 _prototype_ `void FillLinkAnimatorSubmenu(UToolMenu* InMenu, const TSet<UPropertyAnimatorCoreBase*>& InAnimators, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L41 _prototype_ `void FillPresetAnimatorSubmenu(UToolMenu* InMenu, const TSet<UPropertyAnimatorCoreBase*>& InAnimators, UPropertyAnimatorCorePropertyPreset* InPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L43 _prototype_ `void FillNewPresetAnimatorSubmenu(UToolMenu* InMenu, UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCoreAnimatorPreset* InAnimatorPreset, UPropertyAnimatorCorePropertyPreset* InPropertyPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L47 _prototype_ `void ExecuteNewAnimatorPresetAction(const UPropertyAnimatorCoreBase* InAnimator, const TSet<AActor*>& InActors, UPropertyAnimatorCoreAnimatorPreset* InAnimatorPreset, UPropertyAnimatorCorePropertyPreset* InPropertyPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L49 _prototype_ `void ExecuteNewAnimatorPropertyAction(const UPropertyAnimatorCoreBase* InAnimator, const FString& InPropertyLocatorPath, UPropertyAnimatorCoreAnimatorPreset* InAnimatorPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L51 _prototype_ `void ExecuteLinkLastCreatedAnimatorPropertyAction(const UPropertyAnimatorCoreBase* InAnimator, const FString& InPropertyLocatorPath, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L53 _prototype_ `void ExecuteApplyLastCreatedAnimatorPresetAction(const UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCorePropertyPreset* InPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L55 _prototype_ `void ExecuteLinkAnimatorPresetAction(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, UPropertyAnimatorCorePropertyPreset* InPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L57 _prototype_ `void ExecuteLinkAnimatorPropertyAction(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, const FString& InPropertyLocatorPath, UPropertyAnimatorCorePropertyPreset* InPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L59 _prototype_ `void ExecuteEnableActorAnimatorAction(TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData, bool bInEnable);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L61 _prototype_ `void ExecuteEnableLevelAnimatorAction(TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData, bool bInEnable);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L63 _prototype_ `void ExecuteEnableAnimatorAction(UPropertyAnimatorCoreBase* InAnimator, bool bInEnable, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L65 _prototype_ `void ExecuteDeleteActorAnimatorAction(TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L67 _prototype_ `void ExecuteDeleteAnimatorAction(UPropertyAnimatorCoreBase* InAnimator, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L71 _prototype_ `ECheckBoxState GetAnimatorPresetState(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, UPropertyAnimatorCorePropertyPreset* InPreset);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L73 _prototype_ `ECheckBoxState GetLastAnimatorCreatedPresetState(const UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCorePropertyPreset* InPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L75 _prototype_ `ECheckBoxState GetAnimatorPropertyLinkState(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, const FString& InPropertyLocatorPath);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L77 _prototype_ `bool IsAnimatorPresetLinked(UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCorePropertyPreset* InPreset);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L79 _prototype_ `bool IsAnimatorPropertyLinked(const UPropertyAnimatorCoreBase* InAnimator, const FPropertyAnimatorCoreData& InProperty);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L81 _prototype_ `bool IsAnimatorLinkPropertyAllowed(const TSet<UPropertyAnimatorCoreBase*>& InAnimators, const FString& InPropertyLocatorPath);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L83 _prototype_ `bool IsLastAnimatorCreatedPropertyLinked(const UPropertyAnimatorCoreBase* InAnimator, const FString& InPropertyLocatorPath, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L85 _prototype_ `bool IsLastAnimatorCreatedPresetLinked(const UPropertyAnimatorCoreBase* InAnimator, UPropertyAnimatorCorePropertyPreset* InPreset, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L87 _prototype_ `bool IsLastAnimatorCreatedActionVisible(const UPropertyAnimatorCoreBase* InAnimator, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)
- L89 _prototype_ `bool IsLastAnimatorCreatedActionHidden(const UPropertyAnimatorCoreBase* InAnimator, TSharedRef<FPropertyAnimatorCoreEditorMenuData> InMenuData);` (scope `UE::PropertyAnimatorCoreEditor::Menu`)

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Menus/PropertyAnimatorCoreEditorMenuContext.h` (Private)


#### class `UPropertyAnimatorCoreEditorMenuContext`  
`class UPropertyAnimatorCoreEditorMenuContext : public UObject`  
_L15-44_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Context passed in UToolMenu when generating entries with selected items
- L20 _public function_ `const TArray<FPropertyAnimatorCoreData>& GetProperties() const`
- L25 _public function_ `void SetProperties(const TArray<FPropertyAnimatorCoreData>& InProperties)`
- L30 _public function_ `const TSet<UPropertyAnimatorCoreBase*>& GetAnimators() const`
- L35 _public function_ `void SetAnimators(const TSet<UPropertyAnimatorCoreBase*>& InAnimators)`
- L42 _protected member_ `TArray<FPropertyAnimatorCoreData> Properties;` — The items this menu should apply to
- L43 _protected member_ `TSet<UPropertyAnimatorCoreBase*> Animators;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Presets/AssetDefinition_PropertyAnimatorCorePreset.h` (Private)


#### class `UAssetDefinition_PropertyAnimatorCorePreset`  
`class UAssetDefinition_PropertyAnimatorCorePreset : public UAssetDefinitionDefault`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Presets/PropertyAnimatorCorePresetFactory.h` (Private)


#### class `UPropertyAnimatorCorePresetFactory`  
`class UPropertyAnimatorCorePresetFactory : public UFactory`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UPropertyAnimatorCorePresetFactory();`
- L19 _public prototype_ `virtual bool ConfigureProperties() override;`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L21 _public prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, const TCHAR* InType, const TCHAR*& InBuffer, const TCHAR* InBufferEnd, FFeedbackContext* InWarn) override;`
- L22 _public prototype_ `virtual bool FactoryCanImport(const FString& InFilename) override;`
- L25 _public member_ `TSubclassOf<UPropertyAnimatorCorePresetBase> NewPresetClass;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/PropertyAnimatorCoreEditorModule.h` (Private)


#### class `FPropertyAnimatorCoreEditorModule`  
`class FPropertyAnimatorCoreEditorModule : public IModuleInterface`  
_L9-20_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `TArray<FName> RegisteredCustomizations;`
- L19 _private member_ `FDelegateHandle AnimatorTrackCreateEditorHandle;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Sequencer/MovieSceneAnimatorTrackEditor.h` (Private)


#### class `FMovieSceneAnimatorTrackEditor`  
`class FMovieSceneAnimatorTrackEditor : public FKeyframeTrackEditor<UMovieSceneAnimatorTrack>`  
_L11-47_
- inherits: `FKeyframeTrackEditor<UMovieSceneAnimatorTrack>`
- desc: Animator track editor to add animator track and section
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddAnimatorTrack, const TArray<UObject*>& ) static FOnAddAnimatorTrack OnAddAnimatorTrack;`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetAnimatorTrackCount, const TArray<UObject*>& , int32& ) static FOnGetAnimatorTrackCount OnGetAnimatorTrackCount;`
- L20 _public function_ `FMovieSceneAnimatorTrackEditor(const TSharedRef<ISequencer>& InSequencer) : FKeyframeTrackEditor<UMovieSceneAnimatorTrack>(InSequencer)`
- L26 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer)`
- L35 _private prototype_ `virtual FText GetDisplayName() const override;`
- L36 _private prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& InMenuBuilder) override;`
- L37 _private prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& InObjectBinding, UMovieSceneTrack* InTrack, const FBuildEditWidgetParams& InParams) override;`
- L38 _private prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L41 _private prototype_ `void BindDelegates();`
- L43 _private prototype_ `void GetTrackCount(const TArray<UObject*>& InOwners, int32& OutCount) const;`
- L45 _private prototype_ `bool CanExecuteAddTrack() const;`
- L46 _private prototype_ `void ExecuteAddTrack(const TArray<UObject*>& InOwners);`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddAnimatorTrack, const TArray<UObject*>& ) static FOnAddAnimatorTrack OnAddAnimatorTrack;`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetAnimatorTrackCount, const TArray<UObject*>& , int32& ) static FOnGetAnimatorTrackCount OnGetAnimatorTrackCount;`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Private/Styles/PropertyAnimatorCoreEditorStyle.h` (Private)


#### class `FPropertyAnimatorCoreEditorStyle`  
`class FPropertyAnimatorCoreEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FPropertyAnimatorCoreEditorStyle();`
- L14 _public function_ `static FPropertyAnimatorCoreEditorStyle& Get()`

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Public/Menus/PropertyAnimatorCoreEditorMenuDefs.h` (Public)


#### enum `EPropertyAnimatorCoreEditorMenuType`  
`enum class EPropertyAnimatorCoreEditorMenuType : uint8`  
_L16-32_
- desc: Menu type available
- L19 _public enumerator_ `NewSimple = 1 << 0` — Menu to add new animator on selected actors
- L21 _public enumerator_ `NewAdvanced = 1 << 1` — Menu to add new animator on selected actors, with submenus for presets and properties
- L23 _public enumerator_ `Existing = 1 << 2` — Menu to link or unlink properties/preset to/from existing animators
- L25 _public enumerator_ `Link = 1 << 3` — Menu to link properties/preset to existing animator
- L27 _public enumerator_ `Delete = 1 << 4` — Menu to delete animators
- L29 _public enumerator_ `Enable = 1 << 5` — Menu to enable animators
- L31 _public enumerator_ `Disable = 1 << 6` — Menu to disable animators

#### struct `FPropertyAnimatorCoreEditorMenuContext`  
`struct FPropertyAnimatorCoreEditorMenuContext`  
_L35-65_
- desc: Context for the menu builder, you can reuse it for multiple menus types
- L37 _public function_ `FPropertyAnimatorCoreEditorMenuContext()`
- L38 _public prototype_ `explicit FPropertyAnimatorCoreEditorMenuContext(const TSet<UObject*>& InObjects, const TArray<FPropertyAnimatorCoreData>& InProperties);`
- L40 _public prototype_ `const TSet<AActor*>& GetActors() const;`
- L41 _public prototype_ `const TSet<FPropertyAnimatorCoreData>& GetProperties() const;`
- L42 _public prototype_ `const TSet<UPropertyAnimatorCoreComponent*>& GetComponents() const;`
- L43 _public prototype_ `const TSet<UPropertyAnimatorCoreBase*>& GetAnimators() const;`
- L44 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetDisabledAnimators() const;`
- L45 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetEnabledAnimators() const;`
- L46 _public prototype_ `UWorld* GetWorld() const;`
- L48 _public prototype_ `bool IsEmpty() const;`
- L49 _public prototype_ `bool ContainsAnyProperty() const;`
- L50 _public prototype_ `bool ContainsAnyActor() const;`
- L51 _public prototype_ `bool ContainsAnyAnimator() const;`
- L52 _public prototype_ `bool ContainsAnyComponent() const;`
- L53 _public prototype_ `bool ContainsAnyDisabledAnimator() const;`
- L54 _public prototype_ `bool ContainsAnyEnabledAnimator() const;`
- L55 _public prototype_ `bool ContainsAnyComponentAnimator() const;`
- L58 _protected prototype_ `bool ContainsAnimatorState(bool bInState) const;`
- L59 _protected prototype_ `TSet<UPropertyAnimatorCoreBase*> GetStateAnimators(bool bInState) const;`
- L61 _protected member_ `TSet<FPropertyAnimatorCoreData> ContextProperties;`
- L62 _protected member_ `TSet<AActor*> ContextActors;`
- L63 _protected member_ `TSet<UPropertyAnimatorCoreComponent*> ContextComponents;`
- L64 _protected member_ `TSet<UPropertyAnimatorCoreBase*> ContextAnimators;`

#### struct `FPropertyAnimatorCoreEditorMenuOptions`  
`struct FPropertyAnimatorCoreEditorMenuOptions`  
_L68-92_
- desc: Menu builder options
- L70 _public function_ `FPropertyAnimatorCoreEditorMenuOptions()`
- L71 _public prototype_ `explicit FPropertyAnimatorCoreEditorMenuOptions(const TSet<EPropertyAnimatorCoreEditorMenuType>& InMenus);`
- L72 _public function_ `explicit FPropertyAnimatorCoreEditorMenuOptions(uint8 InMenus) : MenuTypes(InMenus)`
- L76 _public prototype_ `FPropertyAnimatorCoreEditorMenuOptions& CreateSubMenu(bool bInCreateSubMenu);`
- L77 _public prototype_ `FPropertyAnimatorCoreEditorMenuOptions& UseTransact(bool bInUseTransact);`
- L79 _public prototype_ `bool IsMenuType(EPropertyAnimatorCoreEditorMenuType InMenuType) const;`
- L80 _public function_ `bool ShouldTransact() const`
- L81 _public function_ `bool ShouldCreateSubMenu() const`
- L85 _protected member_ `uint8 MenuTypes = 0;` — What type of menu should be generated
- L88 _protected member_ `bool bUseTransact = true;` — Create a transaction for actions performed using the menu
- L91 _protected member_ `bool bCreateSubMenu = false;` — Creates the section inside a submenu

#### struct `FPropertyAnimatorCoreEditorMenuData`  
`struct FPropertyAnimatorCoreEditorMenuData`  
_L95-126_
- desc: Used internally to group menu data together
- L97 _public function_ `FPropertyAnimatorCoreEditorMenuData(const FPropertyAnimatorCoreEditorMenuContext& InContext, const FPropertyAnimatorCoreEditorMenuOptions& InOptions) : Context(InContext) , Options(InOptions)`
- L102 _public function_ `const FPropertyAnimatorCoreEditorMenuContext& GetContext() const`
- L107 _public function_ `const FPropertyAnimatorCoreEditorMenuOptions& GetOptions() const`
- L112 _public prototype_ `void SetLastCreatedAnimator(UPropertyAnimatorCoreBase* InAnimator);`
- L113 _public prototype_ `UPropertyAnimatorCoreBase* GetLastCreatedAnimator() const;`
- L115 _public prototype_ `void SetLastCreatedAnimators(const TSet<UPropertyAnimatorCoreBase*>& InAnimators);`
- L116 _public prototype_ `TSet<UPropertyAnimatorCoreBase*> GetLastCreatedAnimators() const;`
- L118 _public prototype_ `bool ContainsAnyLastCreatedAnimator() const;`
- L121 _protected member_ `const FPropertyAnimatorCoreEditorMenuContext Context;`
- L122 _protected member_ `const FPropertyAnimatorCoreEditorMenuOptions Options;`
- L125 _protected member_ `TSet<TWeakObjectPtr<UPropertyAnimatorCoreBase>> LastCreatedAnimators;` — Store last animators created to quickly link properties after creating it

### `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCoreEditor/Public/Subsystems/PropertyAnimatorCoreEditorSubsystem.h` (Public)


#### struct `FPropertyAnimatorCoreEditorCategoryMetadata`  
`struct FPropertyAnimatorCoreEditorCategoryMetadata`  
_L25-29_
- L27 _public member_ `FName Name;`
- L28 _public member_ `FText DisplayName;`

#### class `UPropertyAnimatorCoreEditorSubsystem`  
`class UPropertyAnimatorCoreEditorSubsystem : public UEditorSubsystem`  
_L33-102_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- desc: Singleton class that handles editor operations for property animators
- L39 _public prototype_ `static UPropertyAnimatorCoreEditorSubsystem* Get();` — Get this subsystem instance
- L42 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L43 _public prototype_ `virtual void Deinitialize() override;`
- L47 _public prototype_ `bool FillAnimatorMenu(UToolMenu* InMenu, const FPropertyAnimatorCoreEditorMenuContext& InContext, const FPropertyAnimatorCoreEditorMenuOptions& InOptions);` — Fills a menu based on context objects and menu options
- L50 _public prototype_ `UPropertyAnimatorCorePresetBase* CreatePresetAsset(TSubclassOf<UPropertyAnimatorCorePresetBase> InPresetClass, const TArray<IPropertyAnimatorCorePresetable*>& InPresetables);` — Creates a preset asset for an item
- L53 _public prototype_ `bool RegisterAnimatorCategory(const FPropertyAnimatorCoreEditorCategoryMetadata& InCategoryMetadata);` — Register a category for animator
- L56 _public prototype_ `TSharedPtr<const FPropertyAnimatorCoreEditorCategoryMetadata> FindAnimatorCategory(FName InCategoryIdentifier) const;` — Finds a registered category for animator
- L60 _protected prototype_ `void RegisterDetailPanelCustomization();` — Setup details panel button customization
- L63 _protected prototype_ `void UnregisterDetailPanelCustomization();` — Removes details panel button customization
- L66 _protected prototype_ `void OnGetGlobalRowExtension(const FOnGenerateGlobalRowExtensionArgs& InArgs, TArray<FPropertyRowExtensionButton>& OutExtensions);` — Extends the row extension from the details panel to display a button for each property row
- L69 _protected prototype_ `void OnControlPropertyClicked(TWeakPtr<IDetailTreeNode> InOwnerTreeNode, TSharedPtr<IPropertyHandle> InPropertyHandle);` — Called when user press the control property button in details panel
- L72 _protected prototype_ `bool IsControlPropertySupported(TWeakPtr<IDetailTreeNode> InOwnerTreeNode, TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Checks whether any controller supports that property
- L75 _protected prototype_ `bool IsControlPropertyVisible(TWeakPtr<IDetailTreeNode> InOwnerTreeNode, TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Checks whether the property control window is opened to display the icon
- L78 _protected prototype_ `bool IsControlPropertyLinked(TWeakPtr<IDetailTreeNode> InOwnerTreeNode, TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Checks whether any controller is linked to that property
- L81 _protected prototype_ `TSharedRef<SWidget> GenerateContextMenuWidget(const TArray<FPropertyAnimatorCoreData>& InProperties);` — Creates the context menu to display when selecting the animator icon
- L84 _protected prototype_ `void ExtendPropertyRowContextMenu();` — Extend the context menu on each property row in details panel with additional entries
- L87 _protected prototype_ `void FillAnimatorExtensionSection(UToolMenu* InToolMenu);` — Fills the animator details view extension menu
- L90 _protected prototype_ `void FillAnimatorRowContextSection(UToolMenu* InToolMenu);` — Fills the animator details view row context menu
- L93 _protected prototype_ `bool GetPropertiesFromHandle(const TSharedPtr<IPropertyHandle>& InPropertyHandle, TArray<FPropertyAnimatorCoreData>& OutProperties, bool bInFindMemberProperty = false) const;` — Extracts property data along with owners from a property handle
- L95 _protected member_ `FDelegateHandle OnGetGlobalRowExtensionHandle;`
- L97 _protected member_ `TWeakPtr<SPropertyAnimatorCoreEditorEditPanel> PropertyControllerPanelWeak;`
- L99 _protected member_ `TSharedPtr<FPropertyAnimatorCoreEditorMenuData> LastMenuData;`
- L101 _protected member_ `TMap<FName, TSharedRef<const FPropertyAnimatorCoreEditorCategoryMetadata>> AnimatorCategories;`
