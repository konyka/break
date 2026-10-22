# Plugins / ClonerEffectorEditor

- module root: `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor`
- headers: 27; symbols: 245
- symbol kinds: class=19, delegate=2, enum=2, enumerator=7, function=34, member=36, namespace=6, prototype=132, struct=7
- PrivateDependencyModuleNames: ClonerEffector, InputCore, MovieScene, Niagara, NiagaraEditor, NiagaraSimCaching, Projects, Sequencer, Slate, SlateCore, ToolMenus
- PublicDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, PropertyEditor, UnrealEd

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/CEEditorInputPreprocessor.h` (Private)


#### class `FCEEditorInputPreprocessor`  
`class FCEEditorInputPreprocessor : public IInputProcessor, public TSharedFromThis<FCEEditorInputPreprocessor>`  
_L15-50_
- inherits: `IInputProcessor,TSharedFromThis<FCEEditorInputPreprocessor>`
- desc: This is a fix used to refocus last selected widget in the details panel Since a details refresh causes property value widget to lose focus This should be removed in the future once PropertyValueWidget can be refocused through the API or refresh does not cause a focus lost
- L19 _public function_ `virtual void Tick(const float InDeltaTime, FSlateApplication& InSlateApp, TSharedRef<ICursor> InCursor) override`
- L23 _public function_ `virtual bool HandleKeyDownEvent(FSlateApplication& InSlateApp, const FKeyEvent& InKeyEvent) override`
- L30 _public function_ `virtual bool HandleMouseButtonDownEvent(FSlateApplication& InSlateApp, const FPointerEvent& InMouseEvent) override`
- L37 _public function_ `virtual const TCHAR* GetDebugName() const override`
- L43 _public prototype_ `void RefocusLastWidget();`
- L44 _public prototype_ `void Register();`
- L45 _public prototype_ `void Unregister();`
- L48 _private member_ `bool bShouldRefocus = false;`
- L49 _private member_ `bool bRegistered = false;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/CEEditorModule.h` (Private)


#### class `FCEEditorModule`  
`class FCEEditorModule : public IModuleInterface`  
_L10-25_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `static TSharedPtr<FCEEditorInputPreprocessor> GetInputPreprocessor();`
- L21 _protected member_ `FDelegateHandle ClonerTrackCreateEditorHandle;`
- L22 _protected member_ `TSharedPtr<FCEEditorThrottleManager> ThrottleManager;`
- L23 _protected member_ `TSharedPtr<FCEEditorInputPreprocessor> InputPreprocessor;`
- L24 _protected member_ `TArray<FName> CustomizationNames;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/CEEditorThrottleManager.h` (Private)


#### struct `FCEEditorThrottleScope`  
`struct FCEEditorThrottleScope`  
_L12-26_
- L14 _public prototype_ `explicit FCEEditorThrottleScope(FName InPropertyName);`
- L16 _public prototype_ `virtual ~FCEEditorThrottleScope();`
- L18 _public function_ `FName GetPropertyName() const`
- L25 _private member_ `FName PropertyName;` — Property that is updating

#### class `FCEEditorThrottleManager`  
`class FCEEditorThrottleManager : public TSharedFromThis<FCEEditorThrottleManager>`  
_L32-46_
- inherits: `TSharedFromThis<FCEEditorThrottleManager>`
- desc: Used to allow preview when interactively changing a property within cloner/effector Disable slate throttling to allow viewport updates
- L35 _public prototype_ `FCEEditorThrottleManager() = default;`
- L36 _public prototype_ `virtual ~FCEEditorThrottleManager();`
- L38 _public prototype_ `void Init();`
- L40 _public prototype_ `void Stop();`
- L43 _private prototype_ `void OnPostPropertyChanged(UObject* InObject, FPropertyChangedEvent& InEvent);`
- L45 _private member_ `TOptional<FCEEditorThrottleScope> ThrottleScope;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Customizations/CEEditorClonerActorDetailCustomization.h` (Private)


#### class `FCEEditorClonerActorDetailCustomization`  
`class FCEEditorClonerActorDetailCustomization : public IDetailCustomization`  
_L9-28_
- inherits: `IDetailCustomization`
- desc: Used to customize cloner actor properties in details panel
- L12 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L17 _public function_ `explicit FCEEditorClonerActorDetailCustomization()`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L27 _protected prototype_ `static void RemoveEmptySections();`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Customizations/CEEditorClonerComponentDetailCustomization.h` (Private)


#### class `FCEEditorClonerComponentDetailCustomization`  
`class FCEEditorClonerComponentDetailCustomization : public IDetailCustomization`  
_L20-67_
- inherits: `IDetailCustomization`
- desc: Used to customize cloner component properties in details panel
- L23 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L30 _public function_ `explicit FCEEditorClonerComponentDetailCustomization()`
- L36 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L40 _protected member_ `static constexpr const TCHAR* TrackEditor = TEXT("Cre`
- L41 _protected prototype_ `static void RemoveEmptySections();`
- L42 _protected prototype_ `static void OnChildPropertyChanged(const FPropertyChangedEvent& InEvent, TWeakPtr<IPropertyHandle> InParentHandleWeak);`
- L43 _protected prototype_ `static void OnPropertyChanged(const FPropertyChangedEvent& InEvent, TWeakPtr<IPropertyUtilities> InUtilitiesWeak);`
- L45 _protected prototype_ `bool CanAddSequencerTracks() const;`
- L46 _protected prototype_ `FReply OnAddSequencerTracks();`
- L49 _protected prototype_ `void Init();` — Bind delegates needed
- L52 _protected prototype_ `void OnClonerLayoutLoaded(UCEClonerComponent* InCloner, UCEClonerLayoutBase* InLayout);` — Used to refresh details view when layout changes
- L54 _protected prototype_ `bool IsFunctionButtonEnabled(FName InFunctionName) const;`
- L57 _protected prototype_ `FReply OnFunctionButtonClicked(FName InFunctionName);` — Execute ufunction with that name on selected objects
- L60 _protected member_ `TMap<FName, TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UFunction>>> LayoutFunctionNames;` — Function name to object ufunction mapping
- L63 _protected member_ `TArray<TWeakObjectPtr<UCEClonerComponent>> ClonerComponentsWeak;` — Customized objects
- L66 _protected member_ `TWeakPtr<IPropertyUtilities> PropertyUtilitiesWeak;` — Property utilities for details view refresh

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Customizations/CEEditorClonerEffectorExtensionDetailCustomization.h` (Private)


#### class `FCEEditorClonerEffectorExtensionDetailCustomization`  
`class FCEEditorClonerEffectorExtensionDetailCustomization : public IDetailCustomization`  
_L13-28_
- inherits: `IDetailCustomization`
- desc: Used to customize cloner effector extension properties in details panel
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L26 _protected prototype_ `static void CustomizeEffectorsProperty(TSharedRef<IPropertyHandle> InProperty, IDetailCategoryBuilder& InCategoryBuilder);`
- L27 _protected prototype_ `static bool OnFilterEffectorActor(const AActor* InActor);`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Customizations/CEEditorClonerLifetimeExtensionDetailCustomization.h` (Private)


#### class `FCEEditorClonerLifetimeExtensionDetailCustomization`  
`class FCEEditorClonerLifetimeExtensionDetailCustomization : public IDetailCustomization`  
_L16-33_
- inherits: `IDetailCustomization`
- desc: Used to customize cloner lifetime extension properties in details panel
- L19 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L29 _protected prototype_ `EVisibility GetCurveVisibility(TWeakObjectPtr<UCEClonerLifetimeExtension> InExtensionWeak) const;`
- L31 _protected member_ `TSharedPtr<IPropertyHandle> LifetimeEnabledPropertyHandle;`
- L32 _protected member_ `TSharedPtr<IPropertyHandle> LifetimeScaleEnabledPropertyHandle;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Customizations/CEEditorClonerMeshLayoutDetailCustomization.h` (Private)


#### class `FCEEditorClonerMeshLayoutDetailCustomization`  
`class FCEEditorClonerMeshLayoutDetailCustomization : public IDetailCustomization`  
_L12-28_
- inherits: `IDetailCustomization`
- desc: Used to customize cloner mesh layout properties in details panel
- L15 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L25 _private prototype_ `bool OnFilterMeshActor(const AActor* InActor);`
- L27 _private member_ `TSharedPtr<IPropertyHandle> AssetPropertyHandle;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Customizations/CEEditorClonerSplineLayoutDetailCustomization.h` (Private)


#### class `FCEEditorClonerSplineLayoutDetailCustomization`  
`class FCEEditorClonerSplineLayoutDetailCustomization : public IDetailCustomization`  
_L11-25_
- inherits: `IDetailCustomization`
- desc: Used to customize cloner spline layout properties in details panel
- L14 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L24 _private prototype_ `static bool OnFilterSplineActor(const AActor* InActor);`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Menus/CEEditorClonerMenu.h` (Private)


#### struct `UE::ClonerEditor::Menu::FCEEditorClonerMenuData`  
`struct FCEEditorClonerMenuData`  
_L14-23_
- desc: Used internally to group menu data together
- L16 _public function_ `FCEEditorClonerMenuData(const FCEEditorClonerMenuContext& InContext, const FCEEditorClonerMenuOptions& InOptions) : Context(InContext) , Options(InOptions)`
- L21 _public member_ `const FCEEditorClonerMenuContext Context;`
- L22 _public member_ `const FCEEditorClonerMenuOptions Options;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ClonerEditor` (scope `UE`)
- L11 _namespace_ `namespace Menu` (scope `UE::ClonerEditor`)
- L27 _prototype_ `FToolMenuSection* FindOrAddClonerSection(UToolMenu* InMenu);` (scope `UE::ClonerEditor::Menu`)
- L29 _prototype_ `void FillEnableClonerSection(UToolMenu* InMenu, const FCEEditorClonerMenuData& InMenuData);` (scope `UE::ClonerEditor::Menu`)
- L31 _prototype_ `void FillDisableClonerSection(UToolMenu* InMenu, const FCEEditorClonerMenuData& InMenuData);` (scope `UE::ClonerEditor::Menu`)
- L33 _prototype_ `void FillCreateClonerEffectorSection(UToolMenu* InMenu, const FCEEditorClonerMenuData& InMenuData);` (scope `UE::ClonerEditor::Menu`)
- L35 _prototype_ `void FillConvertClonerSection(UToolMenu* InMenu, const FCEEditorClonerMenuData& InMenuData);` (scope `UE::ClonerEditor::Menu`)
- L37 _prototype_ `void FillCreateClonerSection(UToolMenu* InMenu, const FCEEditorClonerMenuData& InMenuData);` (scope `UE::ClonerEditor::Menu`)
- L41 _prototype_ `void ExecuteEnableClonerAction(const FCEEditorClonerMenuData& InMenuData, bool bInEnable);` (scope `UE::ClonerEditor::Menu`)
- L43 _prototype_ `void ExecuteEnableLevelClonerAction(const FCEEditorClonerMenuData& InMenuData, bool bInEnable);` (scope `UE::ClonerEditor::Menu`)
- L45 _prototype_ `void ExecuteCreateClonerEffectorAction(const FCEEditorClonerMenuData& InMenuData, FName InEffectorType);` (scope `UE::ClonerEditor::Menu`)
- L47 _prototype_ `void ExecuteConvertClonerAction(const FCEEditorClonerMenuData& InMenuData, ECEClonerMeshConversion InToMeshType);` (scope `UE::ClonerEditor::Menu`)
- L49 _prototype_ `void ExecuteCreateClonerAction(const FCEEditorClonerMenuData& InMenuData, FName InClonerLayout);` (scope `UE::ClonerEditor::Menu`)

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Cloner/Sequencer/MovieSceneClonerTrackEditor.h` (Private)


#### class `FMovieSceneClonerTrackEditor`  
`class FMovieSceneClonerTrackEditor : public FMovieSceneTrackEditor`  
_L11-43_
- inherits: `FMovieSceneTrackEditor`
- desc: Cloner track editor to add niagara track and section
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddClonerTrack, const TSet<UCEClonerComponent*>& ) static FOnAddClonerTrack OnAddClonerTrack;`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerTrackExists, UCEClonerComponent* , uint32& ) static FOnClonerTrackExists OnClonerTrackExists;`
- L20 _public function_ `FMovieSceneClonerTrackEditor(const TSharedRef<ISequencer>& InSequencer) : FMovieSceneTrackEditor(InSequencer)`
- L26 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer)`
- L35 _private prototype_ `virtual FText GetDisplayName() const override;`
- L36 _private prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> InTrackClass) const override;`
- L39 _private prototype_ `void BindDelegates();`
- L40 _private prototype_ `void ExecuteAddTrack(const TSet<UCEClonerComponent*>& InCloners);`
- L41 _private prototype_ `void ExecuteTrackExists(UCEClonerComponent* InCloner, uint32& OutCount) const;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddClonerTrack, const TSet<UCEClonerComponent*>& ) static FOnAddClonerTrack OnAddClonerTrack;`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerTrackExists, UCEClonerComponent* , uint32& ) static FOnClonerTrackExists OnClonerTrackExists;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Effector/Customizations/CEEditorEffectorActorDetailCustomization.h` (Private)


#### class `FCEEditorEffectorActorDetailCustomization`  
`class FCEEditorEffectorActorDetailCustomization : public IDetailCustomization`  
_L9-28_
- inherits: `IDetailCustomization`
- desc: Used to customize effector actor properties in details panel
- L12 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L17 _public function_ `explicit FCEEditorEffectorActorDetailCustomization()`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L27 _protected prototype_ `static void RemoveEmptySections();`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Effector/Customizations/CEEditorEffectorComponentDetailCustomization.h` (Private)


#### class `FCEEditorEffectorComponentDetailCustomization`  
`class FCEEditorEffectorComponentDetailCustomization : public IDetailCustomization`  
_L13-34_
- inherits: `IDetailCustomization`
- desc: Used to customize effector component properties in details panel
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L21 _public function_ `explicit FCEEditorEffectorComponentDetailCustomization()`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L31 _protected prototype_ `static void RemoveEmptySections();`
- L32 _protected prototype_ `static void OnChildPropertyChanged(const FPropertyChangedEvent& InEvent, TWeakPtr<IPropertyHandle> InParentHandleWeak);`
- L33 _protected prototype_ `static void OnPropertyChanged(const FPropertyChangedEvent& InEvent, TWeakPtr<IPropertyUtilities> InUtilitiesWeak);`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Effector/Customizations/CEEditorEffectorTypeDetailCustomization.h` (Private)


#### class `FCEEditorEffectorTypeDetailCustomization`  
`class FCEEditorEffectorTypeDetailCustomization : public IDetailCustomization`  
_L18-44_
- inherits: `IDetailCustomization`
- desc: Used to customize effector type properties in details panel
- L21 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L31 _protected prototype_ `static FSlateColor GetImageColorAndOpacity(const TSharedPtr<SWidget> InWidget);`
- L33 _protected prototype_ `void PopulateEasingInfos();`
- L34 _protected prototype_ `FName GetCurrentEasingName() const;`
- L35 _protected prototype_ `const FSlateBrush* GetEasingImage(FName InName) const;`
- L36 _protected prototype_ `FText GetEasingText(FName InName) const;`
- L38 _protected prototype_ `TSharedRef<SWidget> OnGenerateEasingEntry(FName InName) const;`
- L39 _protected prototype_ `void OnSelectionChanged(FName InSelection, ESelectInfo::Type InSelectInfo) const;`
- L41 _protected member_ `TArray<FName> EasingNames;`
- L42 _protected member_ `TWeakObjectPtr<UEnum> EasingEnumWeak;`
- L43 _protected member_ `TSharedPtr<IPropertyHandle> EasingPropertyHandle;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Effector/Menus/CEEditorEffectorMenu.h` (Private)


#### struct `UE::EffectorEditor::Menu::FCEEditorEffectorMenuData`  
`struct FCEEditorEffectorMenuData`  
_L13-22_
- desc: Used internally to group menu data together
- L15 _public function_ `FCEEditorEffectorMenuData(const FCEEditorEffectorMenuContext& InContext, const FCEEditorEffectorMenuOptions& InOptions) : Context(InContext) , Options(InOptions)`
- L20 _public member_ `const FCEEditorEffectorMenuContext Context;`
- L21 _public member_ `const FCEEditorEffectorMenuOptions Options;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EffectorEditor` (scope `UE`)
- L10 _namespace_ `namespace Menu` (scope `UE::EffectorEditor`)
- L26 _prototype_ `FToolMenuSection* FindOrAddEffectorSection(UToolMenu* InMenu);` (scope `UE::EffectorEditor::Menu`)
- L28 _prototype_ `void FillEnableEffectorSection(UToolMenu* InMenu, const FCEEditorEffectorMenuData& InMenuData);` (scope `UE::EffectorEditor::Menu`)
- L30 _prototype_ `void FillDisableEffectorSection(UToolMenu* InMenu, const FCEEditorEffectorMenuData& InMenuData);` (scope `UE::EffectorEditor::Menu`)
- L34 _prototype_ `void ExecuteEnableEffectorAction(const FCEEditorEffectorMenuData& InMenuData, bool bInEnable);` (scope `UE::EffectorEditor::Menu`)
- L36 _prototype_ `void ExecuteEnableLevelEffectorAction(const FCEEditorEffectorMenuData& InMenuData, bool bInEnable);` (scope `UE::EffectorEditor::Menu`)

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Private/Styles/CEEditorStyle.h` (Private)


#### class `FCEEditorStyle`  
`class FCEEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FCEEditorStyle();`
- L14 _public function_ `static FCEEditorStyle& Get()`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Cloner/CEClonerActorFactory.h` (Public)


#### class `UCEClonerActorFactory`  
`class UCEClonerActorFactory : public UActorFactory`  
_L9-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L14 _public prototype_ `UCEClonerActorFactory();`
- L16 _public prototype_ `void SetClonerLayout(FName InLayoutName);`
- L20 _protected prototype_ `virtual void PostSpawnActor(UObject* InAsset, AActor* InNewActor) override;`
- L21 _protected prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InHandle, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`
- L24 _protected member_ `FName ClonerLayoutName = NAME_None;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Cloner/Customizations/CEEditorClonerCustomActorPickerNodeBuilder.h` (Public)


#### class `FCEEditorClonerCustomActorPickerNodeBuilder`  
`class FCEEditorClonerCustomActorPickerNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FCEEditorClonerCustomActorPickerNodeBuilder>`  
_L15-48_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FCEEditorClonerCustomActorPickerNodeBuilder>`
- desc: Used to customize an actor picker to filter items based on a delegate
- L18 _public function_ `explicit FCEEditorClonerCustomActorPickerNodeBuilder(const TSharedRef<IPropertyHandle>& InPropertyHandle, FOnShouldFilterActor InActorFilterDelegate) : PropertyHandle(InPropertyHandle) , ActorFilterDelegate(InActorFilterDelegate)`
- L24 _public prototype_ `virtual FName GetName() const override;`
- L25 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override;`
- L26 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L27 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L31 _private prototype_ `static TSharedPtr<SWidget> FindWidgetType(TSharedPtr<SWidget> InSearchWidget, FName InTypeName, bool bInReverseSearch);`
- L33 _private prototype_ `FText GetPickerLabelText() const;`
- L34 _private prototype_ `FText GetSelectTooltipText() const;`
- L35 _private prototype_ `FText GetUseSelectTooltipText() const;`
- L36 _private prototype_ `TSharedRef<SWidget> GetActorPickerWidget() const;`
- L38 _private prototype_ `void OnActorSelected(AActor* InSelection) const;`
- L39 _private prototype_ `void OnSelectActor() const;`
- L40 _private prototype_ `void OnUseSelectedActor() const;`
- L42 _private prototype_ `AActor* GetPropertyActor() const;`
- L43 _private prototype_ `AActor* GetSelectedActor() const;`
- L45 _private member_ `TSharedRef<IPropertyHandle> PropertyHandle;`
- L46 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L47 _private member_ `FOnShouldFilterActor ActorFilterDelegate;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Cloner/Menus/CEEditorClonerMenuContext.h` (Public)


#### struct `FCEEditorClonerMenuContext`  
`struct FCEEditorClonerMenuContext`  
_L16-39_
- desc: Menu objects to apply actions on
- L18 _public function_ `FCEEditorClonerMenuContext()`
- L19 _public prototype_ `explicit FCEEditorClonerMenuContext(const TSet<UObject*>& InObjects);`
- L21 _public prototype_ `TSet<AActor*> GetActors() const;`
- L22 _public prototype_ `TSet<UCEClonerComponent*> GetCloners() const;`
- L23 _public prototype_ `TSet<UCEClonerComponent*> GetDisabledCloners() const;`
- L24 _public prototype_ `TSet<UCEClonerComponent*> GetEnabledCloners() const;`
- L25 _public prototype_ `UWorld* GetWorld() const;`
- L27 _public prototype_ `bool IsEmpty() const;`
- L28 _public prototype_ `bool ContainsAnyActor() const;`
- L29 _public prototype_ `bool ContainsAnyCloner() const;`
- L30 _public prototype_ `bool ContainsAnyDisabledCloner() const;`
- L31 _public prototype_ `bool ContainsAnyEnabledCloner() const;`
- L34 _protected prototype_ `bool ContainsClonerState(bool bInState) const;`
- L35 _protected prototype_ `TSet<UCEClonerComponent*> GetStateCloners(bool bInState) const;`
- L37 _protected member_ `TSet<TObjectKey<AActor>> ContextActorsKey;`
- L38 _protected member_ `TSet<TObjectKey<UCEClonerComponent>> ContextComponentsKey;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Cloner/Menus/CEEditorClonerMenuEnums.h` (Public)


#### enum `ECEEditorClonerMenuType`  
`enum class ECEEditorClonerMenuType : uint8`  
_L8-20_
- desc: Menu type available
- L11 _public enumerator_ `Enable = 1 << 0` — Enable the cloner
- L13 _public enumerator_ `Disable = 1 << 1` — Disable the cloner
- L15 _public enumerator_ `CreateEffector = 1 << 2` — Creates a cloner linked effector
- L17 _public enumerator_ `Convert = 1 << 3` — Converts cloner to specific mesh
- L19 _public enumerator_ `CreateCloner = 1 << 4` — Creates a cloner and attaches actors below it

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Cloner/Menus/CEEditorClonerMenuOptions.h` (Public)


#### struct `FCEEditorClonerMenuOptions`  
`struct FCEEditorClonerMenuOptions`  
_L9-41_
- desc: Menu options to customize
- L11 _public function_ `FCEEditorClonerMenuOptions()`
- L12 _public prototype_ `explicit FCEEditorClonerMenuOptions(const TSet<ECEEditorClonerMenuType>& InMenus);`
- L13 _public function_ `explicit FCEEditorClonerMenuOptions(const uint8 InMenus) : MenuTypes(InMenus)`
- L17 _public prototype_ `FCEEditorClonerMenuOptions& CreateSubMenu(bool bInCreateSubMenu);`
- L18 _public prototype_ `FCEEditorClonerMenuOptions& UseTransact(bool bInUseTransact);`
- L20 _public prototype_ `bool IsMenuType(ECEEditorClonerMenuType InMenuType) const;`
- L22 _public function_ `bool ShouldTransact() const`
- L27 _public function_ `bool ShouldCreateSubMenu() const`
- L34 _protected member_ `uint8 MenuTypes = 0;` — What type of menu should be generated
- L37 _protected member_ `bool bUseTransact = true;` — Create a transaction for actions performed using the menu
- L40 _protected member_ `bool bCreateSubMenu = false;` — Creates the section inside a submenu

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Effector/CEEffectorActorFactory.h` (Public)


#### class `UCEEffectorActorFactory`  
`class UCEEffectorActorFactory : public UActorFactory`  
_L9-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L14 _public prototype_ `UCEEffectorActorFactory();`
- L16 _public prototype_ `void SetEffectorTypeName(FName InEffectorTypeName);`
- L20 _protected prototype_ `virtual void PostSpawnActor(UObject* InAsset, AActor* InNewActor) override;`
- L21 _protected prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InHandle, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`
- L24 _protected member_ `FName EffectorTypeName;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Effector/Menus/CEEditorEffectorMenuContext.h` (Public)


#### struct `FCEEditorEffectorMenuContext`  
`struct FCEEditorEffectorMenuContext`  
_L15-35_
- desc: Menu objects to apply actions on
- L17 _public function_ `FCEEditorEffectorMenuContext()`
- L18 _public prototype_ `explicit FCEEditorEffectorMenuContext(const TSet<UObject*>& InObjects);`
- L20 _public prototype_ `TSet<UCEEffectorComponent*> GetComponents() const;`
- L21 _public prototype_ `TSet<UCEEffectorComponent*> GetDisabledEffectors() const;`
- L22 _public prototype_ `TSet<UCEEffectorComponent*> GetEnabledEffectors() const;`
- L23 _public prototype_ `UWorld* GetWorld() const;`
- L25 _public prototype_ `bool IsEmpty() const;`
- L26 _public prototype_ `bool ContainsAnyComponent() const;`
- L27 _public prototype_ `bool ContainsAnyDisabledEffectors() const;`
- L28 _public prototype_ `bool ContainsAnyEnabledEffectors() const;`
- L31 _protected prototype_ `bool ContainsEffectorState(bool bInState) const;`
- L32 _protected prototype_ `TSet<UCEEffectorComponent*> GetStateEffectors(bool bInState) const;`
- L34 _protected member_ `TSet<TObjectKey<UCEEffectorComponent>> ContextComponentsKey;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Effector/Menus/CEEditorEffectorMenuEnums.h` (Public)


#### enum `ECEEditorEffectorMenuType`  
`enum class ECEEditorEffectorMenuType : uint8`  
_L8-12_
- desc: Menu type available
- L10 _public enumerator_ `Enable = 1 << 0`
- L11 _public enumerator_ `Disable = 1 << 1`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Effector/Menus/CEEditorEffectorMenuOptions.h` (Public)


#### struct `FCEEditorEffectorMenuOptions`  
`struct FCEEditorEffectorMenuOptions`  
_L9-41_
- desc: Menu options to customize
- L11 _public function_ `FCEEditorEffectorMenuOptions()`
- L12 _public prototype_ `explicit FCEEditorEffectorMenuOptions(const TSet<ECEEditorEffectorMenuType>& InMenus);`
- L13 _public function_ `explicit FCEEditorEffectorMenuOptions(const uint8 InMenus) : MenuTypes(InMenus)`
- L17 _public prototype_ `FCEEditorEffectorMenuOptions& CreateSubMenu(bool bInCreateSubMenu);`
- L18 _public prototype_ `FCEEditorEffectorMenuOptions& UseTransact(bool bInUseTransact);`
- L20 _public prototype_ `bool IsMenuType(ECEEditorEffectorMenuType InMenuType) const;`
- L22 _public function_ `bool ShouldTransact() const`
- L27 _public function_ `bool ShouldCreateSubMenu() const`
- L34 _protected member_ `uint8 MenuTypes = 0;` — What type of menu should be generated
- L37 _protected member_ `bool bUseTransact = true;` — Create a transaction for actions performed using the menu
- L40 _protected member_ `bool bCreateSubMenu = false;` — Creates the section inside a submenu

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Subsystems/CEEditorClonerSubsystem.h` (Public)


#### class `UCEEditorClonerSubsystem`  
`class UCEEditorClonerSubsystem : public UEditorSubsystem`  
_L16-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Singleton class that handles editor operations for cloners
- L21 _public prototype_ `UCEEditorClonerSubsystem();`
- L24 _public prototype_ `static UCEEditorClonerSubsystem* Get();` — Get this subsystem instance
- L27 _public prototype_ `void FillClonerMenu(UToolMenu* InMenu, const FCEEditorClonerMenuContext& InContext, const FCEEditorClonerMenuOptions& InOptions);` — Fills a menu based on context objects and menu options

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorEditor/Public/Subsystems/CEEditorEffectorSubsystem.h` (Public)


#### class `UCEEditorEffectorSubsystem`  
`class UCEEditorEffectorSubsystem : public UEditorSubsystem`  
_L16-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Singleton class that handles editor operations for effectors
- L21 _public prototype_ `UCEEditorEffectorSubsystem();`
- L24 _public prototype_ `static UCEEditorEffectorSubsystem* Get();` — Get this subsystem instance
- L27 _public prototype_ `void FillEffectorMenu(UToolMenu* InMenu, const FCEEditorEffectorMenuContext& InContext, const FCEEditorEffectorMenuOptions& InOptions);` — Fills a menu based on context objects and menu options
