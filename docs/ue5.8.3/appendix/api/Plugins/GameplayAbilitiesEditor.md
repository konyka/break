# Plugins / GameplayAbilitiesEditor

- module root: `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor`
- headers: 25; symbols: 325
- symbol kinds: class=26, delegate=8, enum=2, enumerator=6, function=18, macro=4, member=75, namespace=1, prototype=182, struct=3
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, ClassViewer, ContentBrowser, Core, CoreUObject, DataRegistry, DataRegistryEditor, EditorFramework, EditorWidgets, Engine, EngineAssetDefinitions, GameplayAbilities, GameplayTags, GameplayTagsEditor, GameplayTasksEditor, GraphEditor, InputCore, Kismet, KismetCompiler, LevelSequence, MainFrame, MovieScene, MovieSceneTools, PropertyEditor, Sequencer, SequencerCore, Slate, SlateCore, SourceControl, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: GameplayTasks

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/AssetDefinition_GameplayAbilitiesBlueprint.h` (Private)


#### class `UAssetDefinition_GameplayAbilitiesBlueprint`  
`class UAssetDefinition_GameplayAbilitiesBlueprint : public UAssetDefinition_Blueprint`  
_L9-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L27 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`
- L32 _private prototype_ `bool ShouldUseDataOnlyEditor(const UBlueprint* Blueprint) const;` — Returns true if the blueprint is data only

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/AttributeBasedFloatDetails.h` (Private)


#### class `FAttributeBasedFloatDetails`  
`class FAttributeBasedFloatDetails : public IPropertyTypeCustomization`  
_L14-32_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FAttributeBasedFloat
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to provide the property name or hide, if necessary
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to allow for possibly being hidden
- L28 _private prototype_ `EVisibility GetFinalChannelVisibility() const;` — Called via delegate to determine visibility of the final channel property
- L31 _private member_ `TSharedPtr<IPropertyHandle> AttributeCalculationTypePropertyHandle;` — Property handle to the AttributeCalculationType property; Used to determine visibility of final channel property

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayAbilitiesGraphPanelPinFactory.h` (Private)


#### class `FGameplayAbilitiesGraphPanelPinFactory`  
`class FGameplayAbilitiesGraphPanelPinFactory: public FGraphPanelPinFactory`  
_L13-23_
- inherits: `FGraphPanelPinFactory`
- L15 _private function_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayCueTagDetails.h` (Private)


#### class `FGameplayCueTagDetails`  
`class FGameplayCueTagDetails : public IPropertyTypeCustomization`  
_L18-51_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L26 _private function_ `FGameplayCueTagDetails()`
- L30 _private prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L31 _private prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> GameplayTagProperty;`
- L35 _private prototype_ `TSharedRef<ITableRow> GenerateListRow(TSharedRef<FSoftObjectPath> NotifyName, const TSharedRef<STableViewBase>& OwnerTable);`
- L36 _private member_ `TArray<TSharedRef<FSoftObjectPath> > NotifyList;`
- L37 _private member_ `TSharedPtr< SListView < TSharedRef<FSoftObjectPath> > > ListView;`
- L39 _private prototype_ `void NavigateToHandler(TSharedRef<FSoftObjectPath> AssetRef);`
- L41 _private prototype_ `FReply OnAddNewNotifyClicked();`
- L44 _private prototype_ `void OnPropertyValueChanged();` — Updates the selected tag
- L45 _private prototype_ `bool UpdateNotifyList();`
- L46 _private prototype_ `FGameplayTag* GetTag() const;`
- L47 _private prototype_ `FText GetTagText() const;`
- L49 _private prototype_ `EVisibility GetListViewVisibility() const;`
- L50 _private prototype_ `EVisibility GetAddNewNotifyVisibliy() const;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayCueDetails, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayCueDetails, Log, All);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayEffectDetails.h` (Private)


#### class `FGameplayEffectDetails`  
`class FGameplayEffectDetails : public IDetailCustomization`  
_L13-26_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L23 _private member_ `IDetailLayoutBuilder* MyDetailLayout;`
- L25 _private prototype_ `void OnDurationPolicyChange();`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayEffectDetails, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayEffectDetails, Log, All);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayEffectExecutionDefinitionDetails.h` (Private)


#### class `FGameplayEffectExecutionDefinitionDetails`  
`class FGameplayEffectExecutionDefinitionDetails : public IPropertyTypeCustomization`  
_L14-50_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FGameplayEffectExecutionDefinition
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to provide the property name
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to allow for hiding/updating of the calculation modifiers array as the calculation class changes
- L28 _private prototype_ `void OnCalculationClassChanged();` — Called via delegate when the user changes the calculation class
- L31 _private prototype_ `void UpdateCalculationModifiers();` — Helper function to determine whether to hide/show the modifiers, as well as prune invalid options
- L34 _private prototype_ `EVisibility GetCalculationModifierVisibility() const;` — Visibility delegate for calculation modifiers
- L37 _private prototype_ `EVisibility GetPassedInTagsVisibility() const;` — Visibility delegate for Passed In Tags field
- L40 _private member_ `TSharedPtr<IPropertyHandle> CalculationClassPropHandle;` — Property handle for the calculation class
- L43 _private member_ `TSharedPtr<IPropertyHandleArray> CalculationModifiersArrayPropHandle;` — Property handle array for the calculation modifiers
- L46 _private member_ `bool bShowCalculationModifiers;` — If true, the calculation modifiers array should be shown
- L49 _private member_ `bool bShowPassedInTags;` — If true, the Passed In Tags field will be shown

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayEffectExecutionScopedModifierInfoDetails.h` (Private)


#### class `FGameplayEffectExecutionScopedModifierInfoDetails`  
`class FGameplayEffectExecutionScopedModifierInfoDetails : public IPropertyTypeCustomization`  
_L16-50_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FGameplayEffectExecutionScopedModifierInfo
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to provide the property name
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to allow for a custom selection widget for scoped modifiers inside a custom execution
- L31 _private prototype_ `void OnBackingDataComboBoxSelectionChanged(TSharedPtr<FAggregatorDetailsBackingData> InSelectedItem, ESelectInfo::Type InSelectInfo);` — Delegate called when combo box selection is changed
- L34 _private prototype_ `TSharedRef<SWidget> OnGenerateBackingDataComboWidget(TSharedPtr<FAggregatorDetailsBackingData> InItem);` — Called to generate the widgets for custom combo box entries
- L37 _private prototype_ `TSharedPtr<FAggregatorDetailsBackingData> GetCurrentBackingData() const;` — Get the current aggregator backing data, if possible; Otherwise falls back to first available definition from execution class
- L40 _private prototype_ `void SetCurrentBackingData(TSharedPtr<FAggregatorDetailsBackingData> InBackingData);` — Set the current capture definition
- L43 _private member_ `TSharedPtr<IPropertyHandle> ScopedModifierStructPropertyHandle;` — Cached property handle for the overall scoped modifier info struct
- L46 _private member_ `TSharedPtr<SScopedModBackingDataWidget> PrimaryBackingDataWidget;` — Primary backing data widget shown for the custom combo box
- L49 _private member_ `TArray< TSharedPtr<FAggregatorDetailsBackingData> > AvailableBackingData;` — Backing source for the custom combo box; Populated by all valid backing data from the execution class

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayEffectModifierMagnitudeDetails.h` (Private)


#### class `FGameplayEffectModifierMagnitudeDetails`  
`class FGameplayEffectModifierMagnitudeDetails : public IPropertyTypeCustomization`  
_L15-42_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FGameplayEffectModifierMagnitude
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to provide the property name
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to only show the magnitude that is currently being used based on calculation type
- L29 _private prototype_ `void OnCalculationTypeChanged();` — Called via delegate when the user changes the calculation type
- L32 _private prototype_ `EVisibility GetMagnitudeCalculationPropertyVisibility(FProperty* InProperty) const;` — Visibility delegate for the various methods of calculating magnitude
- L35 _private member_ `TSharedPtr<IPropertyHandle> MagnitudeCalculationTypePropertyHandle;` — Property handle of the enumeration of the magnitude calculation type
- L38 _private member_ `EGameplayEffectMagnitudeCalculation VisibleCalculationType;` — Currently visible magnitude calculation type
- L41 _private member_ `TMap<FProperty*, EGameplayEffectMagnitudeCalculation> PropertyToCalcEnumMap;` — Acceleration map for determining whether to show a magnitude property or not

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayModEvaluationChannelSettingsDetails.h` (Private)


#### class `FGameplayModEvaluationChannelSettingsDetails`  
`class FGameplayModEvaluationChannelSettingsDetails : public IPropertyTypeCustomization`  
_L13-28_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FGameplayEffectEvaluationChannelSettings
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to provide the property name or hide, if necessary
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to allow for possibly being hidden
- L27 _private member_ `bool bShouldBeVisible;` — Whether the evaluation channel settings should be visible or not

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/GameplayTagBlueprintPropertyMappingDetails.h` (Private)


#### class `FGameplayTagBlueprintPropertyMappingDetails`  
`class FGameplayTagBlueprintPropertyMappingDetails : public IPropertyTypeCustomization`  
_L15-43_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _protected prototype_ `void OnChangeProperty(TFieldPath<FProperty> ItemSelected, ESelectInfo::Type SelectInfo);`
- L28 _protected prototype_ `FGuid GetPropertyGuid(TFieldPath<FProperty> Property) const;`
- L29 _protected prototype_ `FString GetPropertyName(TFieldPath<FProperty> Property) const;`
- L31 _protected prototype_ `TSharedRef<SWidget> GeneratePropertyWidget(TFieldPath<FProperty> Property);`
- L33 _protected prototype_ `FText GetSelectedValueText() const;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> NamePropertyHandle;`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> GuidPropertyHandle;`
- L40 _protected member_ `TArray<TFieldPath<FProperty>> PropertyOptions;`
- L42 _protected member_ `TFieldPath<FProperty> SelectedProperty;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/SGameplayAttributeGraphPin.h` (Private)


#### class `SGameplayAttributeGraphPin`  
`class SGameplayAttributeGraphPin : public SGraphPin`  
_L10-31_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(SGameplayAttributeGraphPin)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L22 _public prototype_ `void OnAttributeChanged(FProperty* SelectedAttribute);`
- L24 _public member_ `FProperty* LastSelectedProperty;`
- L27 _private function_ `bool GetDefaultValueIsEnabled() const`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/SGameplayAttributeWidget.h` (Private)


#### class `SGameplayAttributeWidget`  
`class SGameplayAttributeWidget : public SCompoundWidget`  
_L11-56_
- inherits: `SCompoundWidget`
- L16 _public function_ `DECLARE_DELEGATE_OneParam(FOnAttributeChanged, FProperty*) SLATE_BEGIN_ARGS(SGameplayAttributeWidget) : _FilterMetaData() , _DefaultProperty(nullptr)` — Called when a tag status is changed
- L22 _public prototype_ `SLATE_ARGUMENT(FString, FilterMetaData) SLATE_ARGUMENT(FProperty*, DefaultProperty) SLATE_EVENT(FOnAttributeChanged, OnAttributeChanged)`
- L31 _private prototype_ `TSharedRef<SWidget> GenerateAttributePicker();`
- L33 _private prototype_ `FText GetSelectedValueAsString() const;`
- L36 _private prototype_ `void OnMenu(const FPointerEvent& MouseEvent);` — Called when the widget is clicked using RMB
- L38 _private prototype_ `void OnCopyAttribute(FProperty* AttributeProperty);`
- L39 _private prototype_ `bool CanPaste() const;`
- L40 _private prototype_ `void OnPasteAttribute();`
- L43 _private prototype_ `void OnAttributePicked(FProperty* InProperty);` — Handles updates when the selected attribute changes
- L46 _private member_ `FOnAttributeChanged OnAttributeChanged;` — Delegate to call when the selected attribute changes
- L49 _private member_ `FString FilterMetaData;` — The search string being used to filter the attributes
- L52 _private member_ `FProperty* SelectedProperty;` — The currently selected attribute
- L55 _private member_ `TSharedPtr<class SComboButton> ComboButton;` — Used to display an attribute picker.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAttributeChanged, FProperty*) SLATE_BEGIN_ARGS(SGameplayAttributeWidget) : _FilterMetaData() , _DefaultProperty(nullptr) {} SLATE_ARGUMENT(FString, FilterMetaData) SLATE_ARGUMENT(FProperty*, DefaultProperty) SLATE_EVENT(FOnAttributeChanged, OnAttributeChanged)` — Called when a tag status is changed

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/SGameplayCueEditor.h` (Private)


#### class `SGameplayCueEditor`  
`class SGameplayCueEditor : public SUserWidget`  
_L11-29_
- inherits: `SUserWidget`
- desc: Main Gameplay Cue Editor UI widget
- L15 _public function_ `SLATE_USER_ARGS(SGameplayCueEditor)`
- L16 _public prototype_ `SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs) = 0;`
- L19 _public prototype_ `virtual void OnNewGameplayCueTagCommited(const FString& TagName, const FString& TagComment, const FName& TagSource) = 0;`
- L21 _public prototype_ `virtual void OnSearchTagCommited(const FText& InText, ETextCommit::Type InCommitType) = 0;`
- L22 _public prototype_ `virtual void HandleNotify_OpenAssetInEditor(FString AssetName, int AssetType) = 0;`
- L23 _public prototype_ `virtual void HandleNotify_FindAssetInEditor(FString AssetName, int AssetType) = 0;`
- L25 _public prototype_ `static FString GetPathNameForGameplayCueTag(FString Tag);`
- L27 _public prototype_ `static void CreateNewGameplayCueNotifyDialogue(FString GameplayCue, UClass* ParentClass);`
- L28 _public prototype_ `static void OpenEditorForNotify(FString NotifyFullPath);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/SGameplayCueEditor_Picker.h` (Private)


#### class `SGameplayCuePickerDialog`  
`class SGameplayCuePickerDialog : public SCompoundWidget`  
_L32-84_
- inherits: `SCompoundWidget`
- desc: Widget for picking a new GameplayCue Notify class (similar to actor class picker)
- L35 _public function_ `SLATE_BEGIN_ARGS( SGameplayCuePickerDialog )`
- L38 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<SWindow>, ParentWindow ) SLATE_ARGUMENT( TArray<UClass*>, DefaultClasses ) SLATE_ARGUMENT( FString, GameplayCueTag ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _public prototype_ `static bool PickGameplayCue(const FText& TitleText, const TArray<UClass*>& DefaultClasses, UClass*& OutChosenClass, FString InGameplayCueTag);`
- L51 _private function_ `void OnClassPicked(UClass* InChosenClass)` — Handler for when a class is picked in the class picker
- L57 _private prototype_ `TSharedRef<ITableRow> GenerateListRow(UClass* InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Creates the default class widgets
- L60 _private prototype_ `FReply OnClassPickerConfirmed();` — Handler for when "Ok" we selected in the class viewer
- L62 _private prototype_ `FReply OnDefaultClassPicked(UClass* InChosenClass);`
- L65 _private prototype_ `void OnDefaultAreaExpansionChanged(bool bExpanded);` — Handler for the custom button to hide/unhide the default class viewer
- L68 _private prototype_ `void OnCustomAreaExpansionChanged(bool bExpanded);` — Handler for the custom button to hide/unhide the class viewer
- L72 _private member_ `TWeakPtr<SWindow> WeakParentWindow;` — A pointer to the window that is asking the user to select a parent class
- L75 _private member_ `UClass* ChosenClass;` — The class that was last clicked on
- L78 _private member_ `bool bPressedOk;` — A flag indicating that Ok was selected
- L81 _private member_ `TArray<UClass*> DefaultClasses;` — An array of default classes used in the dialog
- L83 _private member_ `FString GameplayCueTag;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Private/Sequencer/GameplayCueTrackEditor.h` (Private)


#### class `FGameplayCueTrackEditor`  
`class FGameplayCueTrackEditor : public FMovieSceneTrackEditor`  
_L17-53_
- inherits: `FMovieSceneTrackEditor`
- desc: A property track editor for named events.
- L28 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Factory function to create an instance of this class (called by a sequencer). @param InSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L32 _public prototype_ `FGameplayCueTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L38 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L39 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L40 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L41 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L42 _public prototype_ `virtual void BuildTrackContextMenu( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track ) override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L44 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L48 _private prototype_ `void BuildAddTrackMenuImpl(FMenuBuilder& MenuBuilder, TArrayView<const FGuid> InObjectBindingIDs);`
- L49 _private prototype_ `void HandleAddSectionToTrack(UMovieSceneTrack* Track, UClass* SectionClass, int32 RowIndex);`
- L51 _private prototype_ `void AddTracks(TRange<FFrameNumber> SectionTickRange, UClass* SectionClass, TArray<FGuid> InObjectBindingIDs);`
- L52 _private prototype_ `void AddSectionToTrack(UMovieSceneTrack* Track, const TRange<FFrameNumber>& SectionTickRange, UClass* SectionClass);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/AttributeDetails.h` (Public)


#### class `FAttributeDetails`  
`class FAttributeDetails : public IDetailCustomization`  
_L25-42_
- inherits: `IDetailCustomization`
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L33 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L35 _private prototype_ `TSharedPtr<FString> GetPropertyType() const;`
- L37 _private member_ `TArray<TSharedPtr<FString>> PropertyOptions;`
- L39 _private member_ `TSharedPtr<IPropertyHandle> MyProperty;`
- L41 _private prototype_ `void OnChangeProperty(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);`

#### class `FAttributePropertyDetails`  
`class FAttributePropertyDetails : public IPropertyTypeCustomization`  
_L45-69_
- inherits: `IPropertyTypeCustomization`
- L48 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L51 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L52 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L57 _private member_ `TSharedPtr<IPropertyHandle> MyProperty;` — the attribute property
- L59 _private member_ `TSharedPtr<IPropertyHandle> OwnerProperty;` — the owner property
- L61 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;` — the name property
- L63 _private member_ `TArray<TSharedPtr<FString>> PropertyOptions;`
- L65 _private prototype_ `TSharedPtr<FString> GetPropertyType() const;`
- L67 _private prototype_ `void OnChangeProperty(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);`
- L68 _private prototype_ `void OnAttributeChanged(FProperty* SelectedAttribute);`

#### class `FScalableFloatDetails`  
`class FScalableFloatDetails : public IPropertyTypeCustomization`  
_L71-151_
- inherits: `IPropertyTypeCustomization`
- L74 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L75 _public member_ `static constexpr float DefaultMinPreviewLevel = 0.f;`
- L76 _public member_ `static constexpr float DefaultMaxPreviewLevel = 30.f;`
- L78 _public function_ `FScalableFloatDetails() : PreviewLevel(0.f) , MinPreviewLevel(DefaultMinPreviewLevel) , MaxPreviewLevel(DefaultMaxPreviewLevel)`
- L87 _protected prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L88 _protected prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L90 _protected prototype_ `bool IsEditable() const;`
- L91 _protected prototype_ `void UpdatePreviewLevels();`
- L94 _protected prototype_ `TSharedRef<SWidget> CreateCurveTableWidget();` — Curve Table selector
- L95 _protected prototype_ `TSharedRef<SWidget> GetCurveTablePicker();`
- L96 _protected prototype_ `void OnSelectCurveTable(const FAssetData& AssetData);`
- L97 _protected prototype_ `void OnCloseMenu();`
- L98 _protected prototype_ `FText GetCurveTableText() const;`
- L99 _protected prototype_ `FText GetCurveTableTooltip() const;`
- L100 _protected prototype_ `EVisibility GetCurveTableVisiblity() const;`
- L101 _protected prototype_ `EVisibility GetAssetButtonVisiblity() const;`
- L102 _protected prototype_ `void OnBrowseTo();`
- L103 _protected prototype_ `void OnClear();`
- L104 _protected prototype_ `void OnUseSelected();`
- L107 _protected prototype_ `TSharedRef<SWidget> CreateRegistryTypeWidget();` — Registry Type selector
- L108 _protected prototype_ `FString GetRegistryTypeValueString() const;`
- L109 _protected prototype_ `FText GetRegistryTypeTooltip() const;`
- L110 _protected prototype_ `EVisibility GetRegistryTypeVisiblity() const;`
- L113 _protected prototype_ `void OnCurveSourceChanged();` — Curve source accessors
- L114 _protected prototype_ `void RefreshSourceData();`
- L115 _protected prototype_ `class UCurveTable* GetCurveTable(FPropertyAccess::Result* OutResult = nullptr) const;`
- L116 _protected prototype_ `FDataRegistryType GetRegistryType(FPropertyAccess::Result* OutResult = nullptr) const;`
- L119 _protected prototype_ `TSharedRef<SWidget> CreateRowNameWidget();` — Row/item name widget
- L120 _protected prototype_ `EVisibility GetRowNameVisibility() const;`
- L121 _protected prototype_ `FText GetRowNameComboBoxContentText() const;`
- L122 _protected prototype_ `FText GetRowNameComboBoxContentTooltip() const;`
- L123 _protected prototype_ `void OnRowNameChanged();`
- L126 _protected prototype_ `EVisibility GetPreviewVisibility() const;` — Preview widgets
- L127 _protected prototype_ `float GetPreviewLevel() const;`
- L128 _protected prototype_ `void SetPreviewLevel(float NewLevel);`
- L129 _protected prototype_ `FText GetRowValuePreviewLabel() const;`
- L130 _protected prototype_ `FText GetRowValuePreviewText() const;`
- L133 _protected prototype_ `FName GetRowName(FPropertyAccess::Result* OutResult = nullptr) const;` — Row accessors and callbacks
- L134 _protected prototype_ `const FRealCurve* GetRealCurve(FPropertyAccess::Result* OutResult = nullptr) const;`
- L135 _protected prototype_ `FDataRegistryId GetRegistryId(FPropertyAccess::Result* OutResult = nullptr) const;`
- L136 _protected prototype_ `void SetRegistryId(FDataRegistryId NewId);`
- L137 _protected prototype_ `void GetCustomRowNames(TArray<FName>& OutRows) const;`
- L139 _protected member_ `TSharedPtr<IPropertyHandle> ValueProperty;`
- L140 _protected member_ `TSharedPtr<IPropertyHandle> CurveTableHandleProperty;`
- L141 _protected member_ `TSharedPtr<IPropertyHandle> CurveTableProperty;`
- L142 _protected member_ `TSharedPtr<IPropertyHandle> RowNameProperty;`
- L143 _protected member_ `TSharedPtr<IPropertyHandle> RegistryTypeProperty;`
- L145 _protected member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;`
- L147 _protected member_ `float PreviewLevel;`
- L148 _protected member_ `float MinPreviewLevel;`
- L149 _protected member_ `float MaxPreviewLevel;`
- L150 _protected member_ `bool bSourceRefreshQueued;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GAMEPLAYABILITIESEDITOR_API`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAttributeDetails, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAttributeDetails, Log, All);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayAbilitiesBlueprintFactory.h` (Public)


#### class `UGameplayAbilitiesBlueprintFactory`  
`class UGameplayAbilitiesBlueprintFactory : public UFactory`  
_L13-30_
- reflection: `UCLASS(HideCategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L23 _private member_ `TSubclassOf<class UGameplayAbility> ParentClass;` — `UPROPERTY(EditAnywhere, Category=GameplayAbilitiesBlueprintFactory)` — The parent class of the created blueprint
- L26 _private prototype_ `virtual bool ConfigureProperties() override;`
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L28 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayAbilitiesEditor.h` (Public)


#### class `FGameplayAbilitiesEditor`  
`class FGameplayAbilitiesEditor : public FBlueprintEditor`  
_L14-58_
- inherits: `FBlueprintEditor`
- desc: Gameplay abilities asset editor (extends Blueprint editor)
- L26 _public prototype_ `void InitGameplayAbilitiesEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode);`
- L34 _private prototype_ `void EnsureGameplayAbilityBlueprintIsUpToDate(UBlueprint* Blueprint);` — Updates existing gameplay ability blueprints to make sure that they are up to date @param	Blueprint	The blueprint to be updated
- L37 _public prototype_ `FGameplayAbilitiesEditor();`
- L39 _public prototype_ `virtual ~FGameplayAbilitiesEditor();`
- L45 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface FRED_TODO: don't merge this back virtual FName GetToolkitContextFName() const override;
- L46 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L47 _public prototype_ `virtual FText GetToolkitName() const override;`
- L48 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L49 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L50 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L54 _public prototype_ `virtual FString GetDocumentationLink() const override;` — @return the documentation location for this editor
- L57 _public prototype_ `virtual UBlueprint* GetBlueprintObj() const override;` — Returns a pointer to the Blueprint object we are currently editing, as long as we are editing exactly one

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayAbilitiesEditorModule.h` (Public)


#### struct `FGameplayCueEditorStrings`  
`struct FGameplayCueEditorStrings`  
_L11-35_
- L13 _public member_ `FString GameplayCueNotifyDescription1;`
- L14 _public member_ `FString GameplayCueNotifyDescription2;`
- L16 _public member_ `FString GameplayCueEventDescription1;`
- L17 _public member_ `FString GameplayCueEventDescription2;`
- L19 _public function_ `FGameplayCueEditorStrings()`
- L28 _public function_ `FGameplayCueEditorStrings(FString Notify1, FString Notify2, FString Event1, FString Event2)`

#### class `IGameplayAbilitiesEditorModule`  
`class IGameplayAbilitiesEditorModule : public IModuleInterface`  
_L46-83_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L57 _public function_ `static inline IGameplayAbilitiesEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L67 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L73 _public prototype_ `virtual FGetGameplayCueNotifyClasses& GetGameplayCueNotifyClassesDelegate() = 0;` — Sets delegate that will be called to retrieve list of gameplay cue notify classes to be presented by GameplayCue Editor when creating a new notify
- L75 _public prototype_ `virtual FGetGameplayCueInterfaceClasses& GetGameplayCueInterfaceClassesDelegate() = 0;`
- L78 _public prototype_ `virtual FGetGameplayCuePath& GetGameplayCueNotifyPathDelegate() = 0;` — Sets delegate that will be called to get the save path for a gameplay cue notify that is created through the GameplayCue Editor
- L81 _public prototype_ `virtual FGetGameplayCueEditorStrings& GetGameplayCueEditorStringsDelegate() = 0;` — Returns strings used in the GameplayCue Editor widgets. Useful for games to override with game specific information for designers (real examples, etc).

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIESEDITOR_API`
- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FGetGameplayCueNotifyClasses, TArray<UClass*>&);`
- L37 _prototype_ `DECLARE_DELEGATE_OneParam(FGetGameplayCueNotifyClasses, TArray<UClass*>&);`
- L38 _delegate_ `DECLARE_DELEGATE_OneParam(FGetGameplayCueInterfaceClasses, TArray<UClass*>&);`
- L38 _prototype_ `DECLARE_DELEGATE_OneParam(FGetGameplayCueInterfaceClasses, TArray<UClass*>&);`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetGameplayCuePath, FString) DECLARE_DELEGATE_RetVal(FGameplayCueEditorStrings, FGetGameplayCueEditorStrings);`
- L39 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetGameplayCuePath, FString) DECLARE_DELEGATE_RetVal(FGameplayCueEditorStrings, FGetGameplayCueEditorStrings);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal(FGameplayCueEditorStrings, FGetGameplayCueEditorStrings);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayAbilityAudit.h` (Public)


#### enum `EGameplayAbilityActivationPath`  
`enum class EGameplayAbilityActivationPath : uint8`  
_L28-33_
- reflection: `UENUM()`
- desc: This enum indicates what flow the Blueprint takes once activated (or native if not Activate is not handled by Blueprints)
- L30 _public enumerator_ `Native`
- L31 _public enumerator_ `Blueprint` — Native,		  Ability has a Native Activate function (and therefore uninspectable by Blueprint analysis)
- L32 _public enumerator_ `FromEvent` — Blueprint,	  Ability has an Activate event implemented in Blueprints and is therefore likely not triggered by a GameplayEvent

#### enum `EGameplayAbilityEndInBlueprints`  
`enum class EGameplayAbilityEndInBlueprints : uint8`  
_L36-41_
- reflection: `UENUM()`
- L38 _public enumerator_ `Missing = 0`
- L39 _public enumerator_ `EndAbility = 1 << 0` — Missing				= 0,		  Ability does not have an EndAbility call in Blueprints and therefore must be ended by external Gameplay code
- L40 _public enumerator_ `EndAbilityLocally = 1 << 1` — EndAbility			= 1 << 0,	  EndAbility is called in Blueprints and is an indication the Server can control the flow of the Gameplay Ability

#### struct `FGameplayAbilityAuditRow`  
`struct FGameplayAbilityAuditRow : public FTableRowBase`  
_L46-125_
- reflection: `USTRUCT(BlueprintInternalUseOnlyHierarchical)`
- inherits: `FTableRowBase`
- desc: This contains all of the data we gather about a Blueprint during the Audit process
- L51 _public prototype_ `virtual void FillDataFromGameplayAbilityBlueprint(const UBlueprint& GameplayAbilityBlueprint);` — Fill this structure with data from a UBlueprint (GameplayAbility asset).  Return true if successful.
- L54 _public prototype_ `virtual void FillDataFromGameplayAbility(const UGameplayAbility& GameplayAbility);` — Fill this structure with data from a UGameplayAbility (likely compiled from a UBlueprint).  Return true if successful.
- L60 _protected member_ `EGameplayAbilityActivationPath ActivationPath = EGameplayAbilityActivationPath::Native;` — `UPROPERTY()` — Does the Blueprint override Activate, ActivateByEvent, or is it left up to Native code?
- L64 _protected member_ `TEnumAsByte<EGameplayAbilityInstancingPolicy::Type> InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::NonInstanced;` — `UPROPERTY()` — The InstancingPolicy of the GameplayAbility (Instancing Behavior can affect memory, which functions can be called, what data can be used, and replication)
- L68 _protected member_ `TEnumAsByte<EGameplayAbilityNetExecutionPolicy::Type> NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::LocalPredicted;` — `UPROPERTY()` — The NetExecutionPolicy of the GameplayAbility
- L72 _protected member_ `TEnumAsByte<EGameplayAbilityNetSecurityPolicy::Type> NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;` — `UPROPERTY()` — The NetSecurityPolicy of the GameplayAbility
- L76 _protected member_ `TEnumAsByte<EGameplayAbilityReplicationPolicy::Type> ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateNo;` — `UPROPERTY()` — The Replication Policy which controls if the instance itself is replicated (and therefore controls variable replication)
- L80 _protected member_ `TArray<FName> AssetTags;` — `UPROPERTY()` — Gameplay Tags that the Asset itself has (AbilityTags)
- L84 _protected member_ `FName CostGE = NAME_None;` — `UPROPERTY()` — If the GameplayAbility has a Cost GameplayEffect, this field will tell us which one it's using.
- L88 _protected member_ `FName CooldownGE = NAME_None;` — `UPROPERTY()` — If the GameplayAbility has a Cooldown GameplayEffect, this field will tell us which one it's using.
- L92 _protected member_ `bool bOverridesCanActivate = false;` — `UPROPERTY()` — Does the Blueprint implement CanActivate? It can be an indication that there are complex rules for triggering.
- L96 _protected member_ `bool bOverridesShouldAbilityRespondToEvent = false;` — `UPROPERTY()` — Does the Blueprint implement ShouldAbilityRespondToEvent? It can be an indication that there are complex rules for triggering.
- L100 _protected member_ `bool bChecksCostManually = false;` — `UPROPERTY()` — Does the Blueprint CheckCosts? If so it's an indication that this ability is a multi-step ability.
- L104 _protected member_ `bool bCommitAbility = false;` — `UPROPERTY()` — Does the Blueprint Commit?  If not (and we are a non-native BP), the costs will never apply and we are breaking our expected flow.
- L108 _protected member_ `EGameplayAbilityEndInBlueprints EndAbility = EGameplayAbilityEndInBlueprints::Missing;` — `UPROPERTY()` — How does the Blueprint call EndAbility?  If missing, this Ability can be assumed to be a persistent one and removed from Gameplay code (e.g. while tags are active)
- L112 _protected member_ `TArray<FName> ReferencedTags;` — `UPROPERTY()` — All of the known referenced tags (list may be incomplete -- does not take into account Blueprint Tags)
- L116 _protected member_ `TArray<FName> Functions;` — `UPROPERTY()` — List of functions the Blueprint calls
- L120 _protected member_ `TArray<FString> AsyncTasks;` — `UPROPERTY()` — List of AsyncTasks the Blueprint uses
- L124 _protected member_ `TArray<FName> MutatedVariables;` — `UPROPERTY()` — List of Variables the Blueprint mutates

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIESEDITOR_API`
- L128 _namespace_ `namespace GameplayAbilityAudit`
- L130 _prototype_ `TArray<UEdGraph*> GatherAllGraphsIncludingMacros(const UBlueprint& LoadedInstance);` (scope `GameplayAbilityAudit`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayAbilityGraph.h` (Public)


#### class `UGameplayAbilityGraph`  
`class UGameplayAbilityGraph : public UEdGraph`  
_L11-14_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayAbilityGraphSchema.h` (Public)


#### class `UGameplayAbilityGraphSchema`  
`class UGameplayAbilityGraphSchema : public UEdGraphSchema_K2`  
_L11-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- L24 _private prototype_ `virtual class UK2Node_VariableGet* SpawnVariableGetNode(const FVector2D GraphPosition, class UEdGraph* ParentGraph, FName VariableName, UStruct* Source) const override;` — Creates a new variable getter node and adds it to ParentGraph @param	GraphPosition		The location of the new node inside the graph @param	ParentGraph			The graph to spawn the new node in @param	VariableName		The name of the variable @param	Source				The source of the variable @return	A pointer to the newly spawned node
- L35 _private prototype_ `virtual class UK2Node_VariableSet* SpawnVariableSetNode(const FVector2D GraphPosition, class UEdGraph* ParentGraph, FName VariableName, UStruct* Source) const override;` — Creates a new variable setter node and adds it to ParentGraph @param	GraphPosition		The location of the new node inside the graph @param	ParentGraph			The graph to spawn the new node in @param	VariableName		The name of the variable @param	Source				The source of the variable @return	A pointer to the newly spawned node
- L37 _private function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayEffectCreationMenu.h` (Public)


#### struct `FGameplayEffectCreationData`  
`struct FGameplayEffectCreationData`  
_L13-27_
- reflection: `USTRUCT()`
- L19 _public member_ `FString MenuPath;` — `UPROPERTY(EditAnywhere, Category="Gameplay Effect")` — Where to show this in the menu. Use "|" for sub categories. E.g, "Status|Hard|Stun|Root".
- L23 _public member_ `FString BaseName;` — `UPROPERTY(EditAnywhere, Category="Gameplay Effect")` — The default BaseName of the new asset. E.g "Damage" -> GE_Damage or GE_HeroName_AbilityName_Damage
- L26 _public member_ `TSubclassOf<UGameplayEffect> ParentGameplayEffect;` — `UPROPERTY(EditAnywhere, Category="Gameplay Effect")`

#### class `UGameplayEffectCreationMenu`  
`class UGameplayEffectCreationMenu : public UObject`  
_L31-48_
- reflection: `UCLASS(config=Game,defaultconfig, MinimalAPI)`
- inherits: `UObject`
- desc: Container to hold EventKeywords for PIE testing
- L37 _public prototype_ `UGameplayEffectCreationMenu();`
- L40 _public member_ `static TFunction< FString(FString BaseName, FString Path) > GetDefaultAssetNameFunc;` — Set this in your project to programatically define default GE names
- L44 _public prototype_ `void AddMenuExtensions() const;`
- L47 _public member_ `TArray<FGameplayEffectCreationData> Definitions;` — `UPROPERTY(config, EditAnywhere, Category="Gameplay Effect")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIESEDITOR_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/K2Node_GameplayCueEvent.h` (Public)


#### class `UK2Node_GameplayCueEvent`  
`class UK2Node_GameplayCueEvent : public UK2Node_Event`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UK2Node_Event`
- L19 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L23 _private prototype_ `virtual FText GetTooltipText() const override;`
- L24 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _private prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L29 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/K2Node_LatentAbilityCall.h` (Public)


#### class `UK2Node_LatentAbilityCall`  
`class UK2Node_LatentAbilityCall : public UK2Node_LatentGameplayTaskCall`  
_L16-31_
- reflection: `UCLASS()`
- inherits: `UK2Node_LatentGameplayTaskCall`
- L21 _public prototype_ `UK2Node_LatentAbilityCall(const FObjectInitializer& ObjectInitializer);`
- L24 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UEdGraphNode interface
- L25 _public prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* TargetGraph) const override;`
- L26 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L30 _protected prototype_ `virtual bool IsHandling(TSubclassOf<UGameplayTask> TaskClass) const override;`
