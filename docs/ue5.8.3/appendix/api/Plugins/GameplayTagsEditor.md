# Plugins / GameplayTagsEditor

- module root: `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor`
- headers: 34; symbols: 731
- symbol kinds: class=34, delegate=22, enum=6, enumerator=15, function=51, macro=4, member=175, namespace=18, prototype=399, struct=7
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ContentBrowser, ContentBrowserData, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, GameplayTags, GraphEditor, InputCore, KismetCompiler, MainFrame, SettingsEditor, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: PropertyEditor, Settings, WorkspaceMenuStructure
- PublicIncludePathModuleNames: AssetRegistry, AssetTools

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_LiteralGameplayTag.h` (Public)


#### class `UGameplayTagsK2Node_LiteralGameplayTag`  
`class UGameplayTagsK2Node_LiteralGameplayTag : public UK2Node`  
_L17-44_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L23 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L24 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private function_ `virtual bool CanDuplicateNode() const override`
- L27 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L28 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L32 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L33 _private function_ `virtual bool IsNodeSafeToIgnore() const override`
- L34 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L35 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L36 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L37 _private function_ `virtual bool IsNodePure() const override`
- L38 _private function_ `virtual bool IsDeprecated() const override`
- L39 _private prototype_ `virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override;`
- L40 _private prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_MultiCompareBase.h` (Public)


#### class `UGameplayTagsK2Node_MultiCompareBase`  
`class UGameplayTagsK2Node_MultiCompareBase : public UK2Node`  
_L10-43_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L15 _private member_ `int32 NumberOfPins;` — `UPROPERTY(EditAnywhere, Category = PinOptions)`
- L18 _private member_ `TArray<FName> PinNames;` — `UPROPERTY()`
- L21 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L25 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L26 _private function_ `virtual bool CanDuplicateNode() const override`
- L30 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override` — UK2Node interface
- L31 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L32 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L33 _private function_ `virtual bool IsNodePure() const override`
- L36 _private prototype_ `void AddPin();`
- L37 _private prototype_ `void RemovePin();`
- L41 _protected function_ `virtual void AddPinToSwitchNode()`
- L42 _protected prototype_ `FString GetUniquePinName();`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_MultiCompareGameplayTagAssetInterface.h` (Public)


#### class `UGameplayTagsK2Node_MultiCompareGameplayTagAssetInterface`  
`class UGameplayTagsK2Node_MultiCompareGameplayTagAssetInterface : public UGameplayTagsK2Node_MultiCompareBase`  
_L15-32_
- reflection: `UCLASS()`
- inherits: `UGameplayTagsK2Node_MultiCompareBase`
- L20 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L21 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L26 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L31 _private prototype_ `virtual void AddPinToSwitchNode() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_MultiCompareGameplayTagAssetInterfaceSingleTags.h` (Public)


#### class `UGameplayTagsK2Node_MultiCompareGameplayTagAssetInterfaceSingleTags`  
`class UGameplayTagsK2Node_MultiCompareGameplayTagAssetInterfaceSingleTags : public UGameplayTagsK2Node_MultiCompareBase`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UGameplayTagsK2Node_MultiCompareBase`
- L19 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L20 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L25 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L30 _private prototype_ `virtual void AddPinToSwitchNode() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_MultiCompareGameplayTagContainer.h` (Public)


#### class `UGameplayTagsK2Node_MultiCompareGameplayTagContainer`  
`class UGameplayTagsK2Node_MultiCompareGameplayTagContainer : public UGameplayTagsK2Node_MultiCompareBase`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UGameplayTagsK2Node_MultiCompareBase`
- L19 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L20 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L25 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L30 _private prototype_ `virtual void AddPinToSwitchNode() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_MultiCompareGameplayTagContainerSingleTags.h` (Public)


#### class `UGameplayTagsK2Node_MultiCompareGameplayTagContainerSingleTags`  
`class UGameplayTagsK2Node_MultiCompareGameplayTagContainerSingleTags : public UGameplayTagsK2Node_MultiCompareBase`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UGameplayTagsK2Node_MultiCompareBase`
- L19 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L20 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L25 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L30 _private prototype_ `virtual void AddPinToSwitchNode() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_SwitchGameplayTag.h` (Public)


#### class `UGameplayTagsK2Node_SwitchGameplayTag`  
`class UGameplayTagsK2Node_SwitchGameplayTag : public UK2Node_Switch`  
_L15-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Switch`
- L20 _private member_ `TArray<FGameplayTag> PinTags;` — `UPROPERTY(EditAnywhere, Category = PinOptions)`
- L26 _private member_ `TArray<FName> PinNames;` — `UPROPERTY()`
- L29 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L30 _private prototype_ `virtual void PostLoad() override;`
- L34 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L40 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L44 _private prototype_ `virtual void AddPinToSwitchNode() override;` — UK2Node_Switch Interface
- L45 _private prototype_ `virtual FName GetUniquePinName() override;`
- L46 _private prototype_ `virtual FEdGraphPinType GetPinType() const override;`
- L47 _private prototype_ `virtual FEdGraphPinType GetInnerCaseType() const override;`
- L50 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const override;`
- L53 _protected prototype_ `virtual void CreateFunctionPin() override;`
- L54 _protected prototype_ `virtual void CreateSelectionPin() override;`
- L55 _protected prototype_ `virtual void CreateCasePins() override;`
- L56 _protected prototype_ `virtual void RemovePin(UEdGraphPin* TargetPin) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Classes/GameplayTagsK2Node_SwitchGameplayTagContainer.h` (Public)


#### class `UGameplayTagsK2Node_SwitchGameplayTagContainer`  
`class UGameplayTagsK2Node_SwitchGameplayTagContainer : public UK2Node_Switch`  
_L15-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Switch`
- L20 _private member_ `TArray<FGameplayTagContainer> PinContainers;` — `UPROPERTY(EditAnywhere, Category = PinOptions)`
- L26 _private member_ `TArray<FName> PinNames;` — `UPROPERTY()`
- L29 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L30 _private prototype_ `virtual void PostLoad() override;`
- L34 _private prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L40 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;` — UK2Node interface
- L44 _private prototype_ `virtual void AddPinToSwitchNode() override;` — UK2Node_Switch Interface
- L45 _private prototype_ `virtual FEdGraphPinType GetInnerCaseType() const override;`
- L46 _private prototype_ `virtual FName GetUniquePinName() override;`
- L47 _private prototype_ `virtual FEdGraphPinType GetPinType() const override;`
- L50 _private prototype_ `virtual FName GetPinNameGivenIndex(int32 Index) const override;`
- L53 _protected prototype_ `virtual void CreateFunctionPin() override;`
- L54 _protected prototype_ `virtual void CreateSelectionPin() override;`
- L55 _protected prototype_ `virtual void CreateCasePins() override;`
- L56 _protected prototype_ `virtual void RemovePin(UEdGraphPin* TargetPin) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Internal/SAddNewGameplayTagWidget.h` (Internal)


#### class `SAddNewGameplayTagWidget`  
`class SAddNewGameplayTagWidget : public SCompoundWidget`  
_L14-139_
- inherits: `SCompoundWidget`
- desc: Widget allowing the user to create new gameplay tags
- L24 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGameplayTagAdded, const FString& , const FString& , const FName& );`
- L26 _public function_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsValidTag, const FString& , FText* ) SLATE_BEGIN_ARGS(SAddNewGameplayTagWidget) : _NewTagName(TEXT("")) , _Padding(FMargin(15)) , _AddButtonPadding(FMargin(0, 16, 0, 0)) , _RestrictedTags(false)`
- L34 _public prototype_ `SLATE_EVENT(FOnGameplayTagAdded, OnGameplayTagAdded)` — Callback for when a new tag is added
- L44 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L46 _public prototype_ `void Construct(const FArguments& InArgs);`
- L49 _public function_ `bool IsAddingNewTag() const` — Returns true if we're currently attempting to add a new gameplay tag to an INI file
- L55 _public prototype_ `void AddSubtagFromParent(const FString& ParentTagName, const FName& ParentTagSource);` — Begins the process of adding a subtag to a parent tag
- L58 _public prototype_ `void AddDuplicate(const FString& ParentTagName, const FName& ParentTagSource);` — Begins the process of adding a duplicate of existing tag
- L61 _public prototype_ `void Reset(EResetType ResetType);` — Resets all input fields
- L66 _private prototype_ `void SetTagName(const FText& InName = FText());` — Sets the name of the tag. Uses the default if the name is not specified
- L69 _private prototype_ `void SelectTagSource(const FName& InSource = FName());` — Selects tag file location. Uses the default if the location is not specified
- L72 _private prototype_ `FName GetSelectedTagSource() const;` — Gets selected tag source as name
- L75 _private prototype_ `void PopulateTagSources();` — Creates a list of all INIs that gameplay tags can be added to
- L78 _private prototype_ `void OnCommitNewTagName(const FText& InText, ETextCommit::Type InCommitType);` — Callback for when Enter is pressed when modifying a tag's name or comment
- L81 _private prototype_ `FReply OnAddNewTagButtonPressed();` — Callback for when the Add New Tag button is pressed
- L84 _private prototype_ `void CreateNewGameplayTag();` — Creates a new gameplay tag and adds it to the INI files based on the widget's stored parameters
- L87 _private prototype_ `void ValidateNewRestrictedTag();` — Handle validation and creation of restricted tags
- L88 _private prototype_ `void CreateNewRestrictedGameplayTag();`
- L89 _private prototype_ `void CancelNewTag();`
- L92 _private prototype_ `TSharedRef<SWidget> OnGenerateTagSourcesComboBox(TSharedPtr<FString> InItem);` — Populates the widget's combo box with all potential places where a gameplay tag can be stored
- L95 _private prototype_ `FText CreateTagSourcesComboBoxContent() const;` — Creates the text displayed by the combo box when an option is selected
- L98 _private prototype_ `FText CreateTagSourcesComboBoxToolTip() const;` — Creates the text displayed by the combo box tooltip when an option is selected
- L100 _private prototype_ `EVisibility OnGetTagSourceFavoritesVisibility() const;`
- L101 _private prototype_ `FReply OnToggleTagSourceFavoriteClicked();`
- L102 _private prototype_ `const FSlateBrush* OnGetTagSourceFavoriteImage() const;`
- L107 _private member_ `TArray<TSharedPtr<FString> > TagSources;` — All potential INI files where a gameplay tag can be stored
- L110 _private member_ `TSharedPtr<SEditableTextBox> TagNameTextBox;` — The name of the next gameplay tag to create
- L113 _private member_ `TSharedPtr<SEditableTextBox> TagCommentTextBox;` — The comment to asign to the next gameplay tag to create
- L116 _private member_ `TSharedPtr<SSearchableComboBox> TagSourcesComboBox;` — The INI file where the next gameplay tag will be created
- L120 _private member_ `FOnGameplayTagAdded OnGameplayTagAdded;` — Callback for when a new gameplay tag has been added to the INI files
- L123 _private member_ `FIsValidTag IsValidTag;` — Callback to see if the gameplay tag is valid. This should be used for any specialized rules that are not covered by IsValidGameplayTagString
- L126 _private member_ `bool bAddingNewTag = false;` — Guards against the window closing when it loses focus due to source control checking out a file
- L129 _private member_ `bool bShouldGetKeyboardFocus = false;` — Tracks if this widget should get keyboard focus
- L132 _private member_ `bool bRestrictedTags = false;` — If true, this widget is displaying restricted tags; if false this widget displays regular gameplay tags.
- L135 _private member_ `FString DefaultNewName;` — Cached from NewTagName argument.
- L138 _private member_ `TSharedPtr<SNotificationItem> NotificationItem;` — Last error notification trying to create a new tag.

#### enum `SAddNewGameplayTagWidget::EResetType`  
`enum class EResetType : uint8`  
_L18-22_
- L20 _public enumerator_ `ResetAll`
- L21 _public enumerator_ `DoNotResetSource`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ETextCommit`
- L24 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGameplayTagAdded, const FString& , const FString& , const FName& );`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsValidTag, const FString& , FText* ) SLATE_BEGIN_ARGS(SAddNewGameplayTagWidget) : _NewTagName(TEXT("")) , _Padding(FMargin(15)) , _AddButtonPadding(FMargin(0, 16, 0, 0)) , _RestrictedTags(false) {} SLATE_EVENT(FOnGameplayTagAdded, OnGameplayTagAdded)`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagContainerCustomization.h` (Private)


#### class `FGameplayTagContainerCustomization`  
`class FGameplayTagContainerCustomization : public IPropertyTypeCustomization`  
_L15-43_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the gameplay tag container struct
- L18 _public prototype_ `FGameplayTagContainerCustomization();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to show an edit button to launch the gameplay tag editor
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to do nothing
- L28 _private function_ `FGameplayTagContainer GetMetaDataCategories() const`
- L33 _private prototype_ `void OnGameplayTagContainerComboClosed(const FGameplayTagContainer& NewTagContainer);`
- L34 _private prototype_ `void OnTagCleared();`
- L37 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Cached property handle
- L38 _private member_ `FGameplayTagContainer MetaDataCategories;`
- L39 _private member_ `TWeakObjectPtr<UBlueprint> CreatorBP;`
- L41 _private prototype_ `void OnPasteTag() const;`
- L42 _private prototype_ `bool CanPasteTag() const;`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagCustomization.h` (Private)


#### class `FGameplayTagCustomization`  
`class FGameplayTagCustomization : public IPropertyTypeCustomization`  
_L16-48_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the gameplay tag struct
- L20 _public prototype_ `FGameplayTagCustomization();`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to show an edit button to launch the gameplay tag editor
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to display "Categories" metadata if created from BP
- L29 _public function_ `virtual bool ShouldInlineKey() const override` — Overridden to show tags and value inline
- L34 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Cached property handle
- L36 _private function_ `FGameplayTagContainer GetMetaDataCategories() const`
- L41 _private prototype_ `void OnGameplayTagContainerComboClosed(const FGameplayTagContainer& NewTagContainer);`
- L42 _private prototype_ `void OnTagCleared();`
- L45 _private member_ `FGameplayTag Tag;` — Edited Tag
- L46 _private member_ `FGameplayTagContainer MetaDataCategories;`
- L47 _private member_ `TWeakObjectPtr<UBlueprint> CreatorBP;`

#### class `FGameplayTagCreationWidgetHelperDetails`  
`class FGameplayTagCreationWidgetHelperDetails : public IPropertyTypeCustomization`  
_L51-61_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for FGameplayTagCreationWidgetHelper showing an add tag button
- L54 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L57 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L58 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L60 _public member_ `TSharedPtr<SGameplayTagPicker> TagWidget;`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagEditorUtilities.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GameplayTags` (scope `UE`)
- L13 _namespace_ `namespace EditorUtilities` (scope `UE::GameplayTags`)
- L23 _prototype_ `FString ExtractTagFilterStringFromGraphPin(UEdGraphPin* InTagPin);` (scope `UE::GameplayTags::EditorUtilities`) — Given a editor graph pin representing a tag or container, extract the appropriate filter string from any associated metadata @param InTagPin	Pin to extract from @return Filter string, if any, to apply from the tag pin based on metadata
- L30 _prototype_ `FString GameplayTagExportText(const FGameplayTag Tag);` (scope `UE::GameplayTags::EditorUtilities`) — Exports a gameplay tag to text compatible with Import/Export text. @param Tag tag to export @return tag as text.
- L38 _prototype_ `FGameplayTag GameplayTagTryImportText(const FString& Text, const int32 PortFlags = 0);` (scope `UE::GameplayTags::EditorUtilities`) — Tries to import gameplay tag from text. @param Text string to import from @param PortFlags EPropertyPortFlags controlling import behavior. @return parsed gameplay tag, or None if import failed.
- L45 _prototype_ `FString GameplayTagContainerExportText(const FGameplayTagContainer& TagContainer);` (scope `UE::GameplayTags::EditorUtilities`) — Exports a gameplay tag container to text compatible with Import/Export text. @param TagContainer tag container to export @return tag container as text.
- L53 _prototype_ `FGameplayTagContainer GameplayTagContainerTryImportText(const FString& Text, int32 PortFlags = 0);` (scope `UE::GameplayTags::EditorUtilities`) — Tries to import gameplay tag container from text. @param Text string to import from @param PortFlags EPropertyPortFlags controlling import behavior. @return parsed gameplay tag container, or empty if import failed.
- L60 _prototype_ `FString GameplayTagQueryExportText(const FGameplayTagQuery& TagQuery);` (scope `UE::GameplayTags::EditorUtilities`) — Exports a gameplay tag query to text compatible with Import/Export text. @param TagQuery tag query to export @return tag query as text.
- L68 _prototype_ `FGameplayTagQuery GameplayTagQueryTryImportText(const FString Text, int32 PortFlags = 0);` (scope `UE::GameplayTags::EditorUtilities`) — Tries to import gameplay tag query from text. @param Text string to import from @param PortFlags EPropertyPortFlags controlling import behavior. @return parsed gameplay tag query, or empty if import failed.
- L75 _prototype_ `FString FormatGameplayTagQueryDescriptionToLines(const FString& Desc);` (scope `UE::GameplayTags::EditorUtilities`) — Formats Gameplay Tag Query description to multiple lines. @param Desc Description to format @return Description in multiline format.

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagQueryCustomization.h` (Private)


#### class `FGameplayTagQueryCustomization`  
`class FGameplayTagQueryCustomization : public IPropertyTypeCustomization`  
_L14-28_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the gameplay tag query struct
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to show an edit button to launch the gameplay tag editor
- L25 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagSearchFilter.h` (Private)


#### class `UGameplayTagSearchFilter`  
`class UGameplayTagSearchFilter : public UContentBrowserFrontEndFilterExtension`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UContentBrowserFrontEndFilterExtension`
- L15 _public prototype_ `virtual void AddFrontEndFilterExtensions(TSharedPtr<class FFrontendFilterCategory> DefaultCategory, TArray< TSharedRef<class FFrontendFilter> >& InOutFilterList) const override;` — UContentBrowserFrontEndFilterExtension interface

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagStyle.h` (Private)


#### class `FGameplayTagStyle`  
`class FGameplayTagStyle`  
_L7-27_
- L10 _public prototype_ `static void Initialize();`
- L11 _public prototype_ `static void Shutdown();`
- L12 _public function_ `static ISlateStyle& Get()`
- L13 _public prototype_ `static FName GetStyleSetName();`
- L15 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L20 _public function_ `static const FLinearColor& GetColor(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L26 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagsGraphPanelNodeFactory.h` (Private)


#### class `FGameplayTagsGraphPanelNodeFactory`  
`class FGameplayTagsGraphPanelNodeFactory : public FGraphPanelNodeFactory`  
_L9-20_
- inherits: `FGraphPanelNodeFactory`
- L11 _private function_ `virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagsGraphPanelPinFactory.h` (Private)


#### class `FGameplayTagsGraphPanelPinFactory`  
`class FGameplayTagsGraphPanelPinFactory: public FGraphPanelPinFactory`  
_L12-41_
- inherits: `FGraphPanelPinFactory`
- L14 _private function_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagsSettingsCustomization.h` (Private)


#### class `FGameplayTagsSettingsCustomization`  
`class FGameplayTagsSettingsCustomization : public IDetailCustomization`  
_L13-25_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `FGameplayTagsSettingsCustomization();`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SAddNewGameplayTagSourceWidget.h` (Private)


#### class `SAddNewGameplayTagSourceWidget`  
`class SAddNewGameplayTagSourceWidget : public SCompoundWidget`  
_L11-69_
- inherits: `SCompoundWidget`
- desc: Widget allowing the user to create new gameplay tags
- L15 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnGameplayTagSourceAdded, const FString& );`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAddNewGameplayTagSourceWidget) : _NewSourceName(TEXT("")) , _Padding(FMargin(15))`
- L21 _public prototype_ `SLATE_EVENT(FOnGameplayTagSourceAdded, OnGameplayTagSourceAdded )` — Callback for when a new source is added
- L26 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L28 _public prototype_ `void Construct( const FArguments& InArgs);`
- L31 _public prototype_ `void Reset();` — Resets all input fields
- L36 _private prototype_ `void SetSourceName(const FText& InName = FText());` — Sets the name of the source. Uses the default if the name is not specified
- L39 _private prototype_ `void PopulateTagRoots();` — Creates a list of all root directories for tag sources
- L42 _private prototype_ `TSharedRef<SWidget> OnGenerateTagRootsComboBox(TSharedPtr<FString> InItem);` — Populates the widget's combo box with all potential places where a tag source can be stored
- L45 _private prototype_ `FText GetFriendlyPath(TSharedPtr<FString> InItem) const;` — Gets friendly version of a root path
- L48 _private prototype_ `FText CreateTagRootsComboBoxContent() const;` — Creates the text displayed by the combo box when an option is selected
- L51 _private prototype_ `FReply OnAddNewSourceButtonPressed();` — Callback for when the Add New Tag button is pressed
- L54 _private member_ `TSharedPtr<SEditableTextBox> SourceNameTextBox;` — The name of the next gameplay tag source to create
- L57 _private member_ `FOnGameplayTagSourceAdded OnGameplayTagSourceAdded;` — Callback for when a new gameplay tag has been added to the INI files
- L60 _private member_ `TArray<TSharedPtr<FString> > TagRoots;` — All potential INI files where a tag source can be stored
- L63 _private member_ `TSharedPtr<SSearchableComboBox> TagRootsComboBox;` — The directory where the next tag source will be created
- L66 _private member_ `bool bShouldGetKeyboardFocus;` — Tracks if this widget should get keyboard focus
- L68 _private member_ `FString DefaultNewName;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam( FOnGameplayTagSourceAdded, const FString& );`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SCleanupUnusedGameplayTagsWidget.h` (Private)


#### class `SCleanupUnusedGameplayTagsWidget`  
`class SCleanupUnusedGameplayTagsWidget : public SCompoundWidget`  
_L15-74_
- inherits: `SCompoundWidget`
- desc: Widget for removing unused gameplay tags
- L18 _public function_ `SLATE_BEGIN_ARGS(SCleanupUnusedGameplayTagsWidget)`
- L19 _public prototype_ `SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct( const FArguments& InArgs);`
- L25 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L28 _private prototype_ `void CopySelection();` — Copies the selected tags to the clipboard
- L31 _private prototype_ `ECheckBoxState GetToggleSelectedState() const;` — The state of the column header checkbox that toggles the check state of all items
- L34 _private prototype_ `void OnToggleSelectedCheckBox(ECheckBoxState InNewState);` — Handler for when column header checkbox that toggles the check state of all items is clicked
- L37 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — The sort mode for the given column
- L40 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Handler for when when a column is clicked to change the sort mode
- L43 _private prototype_ `void SortTags();` — Sorts the tags in the list given the current sorting mode and column
- L46 _private prototype_ `FText GetDescriptionText() const;` — Returns the text at the stop of the dialog
- L49 _private prototype_ `TSharedRef<ITableRow> MakeUnusedTagListItemWidget(TSharedPtr<FUnusedTagItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Creates the widget for a list item
- L52 _private prototype_ `void PopulateUnusedTags();` — Updates the list
- L55 _private prototype_ `bool IsRemoveEnabled() const;` — Returns true if the user can click the remove button
- L58 _private prototype_ `FReply OnRemovePressed();` — Handler for when the user clicks the button to remove the selected tags
- L61 _private member_ `TArray<TSharedPtr<FUnusedTagItem>> UnusedTags;` — The unused tag items
- L64 _private member_ `TSharedPtr<SListView<TSharedPtr<FUnusedTagItem>>> UnusedTagsListView;` — The list widget for the unused tag items
- L67 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list to handle generic commands like 'Copy'
- L70 _private member_ `FName SortByColumn;` — The current sort column
- L73 _private member_ `EColumnSortMode::Type SortMode;` — The current sort mode

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SGameplayTagContainerGraphPin.h` (Private)


#### class `SGameplayTagContainerGraphPin`  
`class SGameplayTagContainerGraphPin : public SGraphPinStructInstance`  
_L9-27_
- inherits: `SGraphPinStructInstance`
- desc: Almost the same as a tag pin, but supports multiple tags
- L12 _public function_ `SLATE_BEGIN_ARGS(SGameplayTagContainerGraphPin)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L19 _protected prototype_ `virtual void ParseDefaultValueData() override;`
- L20 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L23 _protected prototype_ `FGameplayTagContainer GetTagContainer() const;`
- L24 _protected prototype_ `void OnTagContainerChanged(const FGameplayTagContainer& NewTagContainer);`
- L26 _protected member_ `FGameplayTagContainer GameplayTagContainer;`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SGameplayTagGraphPin.h` (Private)


#### class `SGameplayTagGraphPin`  
`class SGameplayTagGraphPin : public SGraphPinStructInstance`  
_L11-29_
- inherits: `SGraphPinStructInstance`
- desc: Pin that represents a single gameplay tag, overrides the generic struct widget because tags have their own system for saving changes
- L14 _public function_ `SLATE_BEGIN_ARGS(SGameplayTagGraphPin)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L21 _protected prototype_ `virtual void ParseDefaultValueData() override;`
- L22 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L25 _protected prototype_ `FGameplayTag GetGameplayTag() const;`
- L26 _protected prototype_ `void OnTagChanged(const FGameplayTag NewTag);`
- L28 _protected member_ `FGameplayTag GameplayTag;`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SGameplayTagQueryGraphPin.h` (Private)


#### class `SGameplayTagQueryGraphPin`  
`class SGameplayTagQueryGraphPin : public SGraphPin`  
_L10-31_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(SGameplayTagQueryGraphPin)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L24 _private prototype_ `void ParseDefaultValueData();` — Parses the Data from the pin to fill in the names of the array.
- L26 _private prototype_ `FGameplayTagQuery GetTagQuery() const;`
- L27 _private prototype_ `void OnTagQueryChanged(const FGameplayTagQuery& NewTagQuery);`
- L30 _private member_ `FGameplayTagQuery TagQuery;` — Parse tag query used for editing.

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SGameplayTagQueryWidget.h` (Private)


#### class `SGameplayTagQueryWidget`  
`class SGameplayTagQueryWidget : public SCompoundWidget, public FNotifyHook`  
_L16-99_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Widget allowing user to tag assets with gameplay tags
- L20 _public function_ `DECLARE_DELEGATE_OneParam( FOnQueriesCommitted, const TArray<FGameplayTagQuery>& ) SLATE_BEGIN_ARGS( SGameplayTagQueryWidget ) : _ReadOnly(false)`
- L26 _public prototype_ `SLATE_ARGUMENT(bool, ReadOnly) SLATE_ARGUMENT(FString, Filter) SLATE_EVENT(FSimpleDelegate, OnOk) SLATE_EVENT(FSimpleDelegate, OnCancel) SLATE_EVENT(FOnQueriesCommitted, OnQueriesCommitted) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<FGameplayTagQuery>& InTagQueries);` — Flag to set if the list is read only
- L40 _public function_ `void SetOnOk(FSimpleDelegate InOnOk)`
- L41 _public function_ `void SetOnCancel(FSimpleDelegate InOnCancel)`
- L42 _public function_ `void SetOnQueriesCommitted(FOnQueriesCommitted InOnQueriesCommitted)`
- L44 _public function_ `bool IsReadOnly() const`
- L45 _public function_ `const TArray<FGameplayTagQuery>& GetTagQueries()`
- L46 _public function_ `const FString& GetFilter()`
- L49 _public prototype_ `bool IsBoundToWindow() const;` — Returns true if this widget is currently bound to an SWindow (i.e. it's possible to commit the changes)
- L53 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;`
- L57 _private prototype_ `void OnGetCategoriesMetaFromPropertyHandle(TSharedPtr<IPropertyHandle> PropertyHandle, FString& MetaString) const;`
- L60 _private prototype_ `FReply OnOkClicked();` — Called when the user clicks the "Save and Close" button
- L63 _private prototype_ `FReply OnCancelClicked();` — Called when the user clicks the "Close Without Saving" button
- L66 _private prototype_ `EVisibility GetSaveAndCloseButtonVisibility() const;` — Controls visibility of the "Save and Close" button
- L68 _private prototype_ `EVisibility GetCancelButtonVisibility() const;` — Controls visibility of the "Close Without Saving" button
- L71 _private prototype_ `void SaveToTagQuery();` — Converts editable representation to FGameplayTagQuery and calls OnQueriesCommitted.
- L74 _private member_ `uint32 bReadOnly : 1;` — Flag to set if the list is read only
- L77 _private member_ `TArray<FGameplayTagQuery> TagQueries;` — Containers to modify
- L80 _private member_ `FOnQueriesCommitted OnQueriesCommitted;` — Called when values are committed.
- L83 _private member_ `FSimpleDelegate OnOk;` — Called when "OK" is clicked.
- L86 _private member_ `FSimpleDelegate OnCancel;` — Called when "Cancel" is clicked.
- L89 _private member_ `FString Filter;` — Comma delimited string of tag root names to filter by
- L92 _private member_ `TSharedPtr<IDetailsView> Details;` — Properties Tab
- L94 _private prototype_ `static UEditableGameplayTagQuery* CreateEditableQuery(FGameplayTagQuery& Q);`
- L96 _private member_ `TWeakObjectPtr<UEditableGameplayTagQuery> EditableQuery;`
- L98 _private member_ `TArray<FGameplayTagQuery> OriginalTagQueries;`

#### struct `FGameplayTagQueryWindowArgs`  
`struct FGameplayTagQueryWindowArgs`  
_L101-123_
- L104 _public member_ `FText Title;` — Title of the query editor window.
- L107 _public member_ `bool bReadOnly = false;` — Flag to set if the list is read only
- L110 _public member_ `SGameplayTagQueryWidget::FOnQueriesCommitted OnQueriesCommitted;` — Delegate to call when the query is changed.
- L113 _public member_ `FString Filter;` — Comma delimited string of tag root names to filter by
- L116 _public member_ `TArray<FGameplayTagQuery> EditableQueries;` — The array of queries to edit.
- L119 _public member_ `TSharedPtr<SWidget> AnchorWidget;` — (Optional) Widget to use to position the query window.
- L122 _public member_ `TWeakFieldPtr<FProperty> Property;` — (Optional) The underlying edited property. Used for re-assigning the window upon a detail panel refresh.

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam( FOnQueriesCommitted, const TArray<FGameplayTagQuery>& ) SLATE_BEGIN_ARGS( SGameplayTagQueryWidget ) : _ReadOnly(false) {} SLATE_ARGUMENT(bool, ReadOnly) SLATE_ARGUMENT(FString, Filter) SLATE_EVENT(FSimpleDelegate, OnOk) SLATE_EVENT(FSimpleDelegate, OnCancel) SLATE_EVENT(FOnQueriesCommitted, OnQueriesCommitted) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<FGameplayTagQuery>& InTagQueries);`
- L125 _namespace_ `namespace UE`
- L125 _namespace_ `namespace GameplayTags` (scope `UE`)
- L125 _namespace_ `namespace Editor` (scope `UE::GameplayTags`)
- L127 _prototype_ `TWeakPtr<SGameplayTagQueryWidget> OpenGameplayTagQueryWindow(const FGameplayTagQueryWindowArgs& Args);` (scope `UE::GameplayTags::Editor`)
- L128 _prototype_ `void CloseGameplayTagQueryWindow(TWeakPtr<SGameplayTagQueryWidget> QueryWidget);` (scope `UE::GameplayTags::Editor`)
- L129 _prototype_ `TWeakPtr<SGameplayTagQueryWidget> TrySyncGameplayTagQueryWidget(const FGameplayTagQueryWindowArgs& Args);` (scope `UE::GameplayTags::Editor`)

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SGraphNode_MultiCompareGameplayTag.h` (Private)


#### class `SGraphNode_MultiCompareGameplayTag`  
`class SGraphNode_MultiCompareGameplayTag : public SGraphNode`  
_L9-28_
- inherits: `SGraphNode`
- L12 _public function_ `SLATE_BEGIN_ARGS(SGraphNode_MultiCompareGameplayTag)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UGameplayTagsK2Node_MultiCompareBase* InNode);`
- L20 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;` — SGraphNode interface
- L21 _protected prototype_ `virtual void CreateOutputSideRemoveButton(TSharedPtr<SVerticalBox> OutputBox);`
- L22 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L23 _protected prototype_ `virtual FReply OnAddPin() override;`
- L26 _protected prototype_ `EVisibility IsRemovePinButtonVisible() const;`
- L27 _protected prototype_ `FReply OnRemovePin();`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/SRenameGameplayTagDialog.h` (Private)


#### class `SRenameGameplayTagDialog`  
`class SRenameGameplayTagDialog : public SCompoundWidget`  
_L11-55_
- inherits: `SCompoundWidget`
- L15 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnGameplayTagRenamed, FString , FString );`
- L17 _public function_ `SLATE_BEGIN_ARGS( SRenameGameplayTagDialog ) : _GameplayTagNode() , _Padding(FMargin(15))`
- L21 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FGameplayTagNode>, GameplayTagNode )` — The gameplay tag we want to rename
- L31 _private prototype_ `bool IsRenameEnabled() const;` — Checks if we're in a valid state to rename the tag
- L34 _private prototype_ `FReply OnRenameClicked();` — Renames the tag based on dialog parameters
- L37 _private prototype_ `FReply OnCancelClicked();` — Callback for when Cancel is clicked
- L40 _private prototype_ `void RenameAndClose();` — Renames the tag and attempts to close the active window
- L43 _private prototype_ `void OnRenameTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Attempts to rename the tag if enter is pressed while editing the tag name
- L46 _private prototype_ `void CloseContainingWindow();` — Closes the window that contains this widget
- L50 _private member_ `TSharedPtr<FGameplayTagNode> GameplayTagNode;`
- L52 _private member_ `TSharedPtr<SEditableTextBox> NewTagNameTextBox;`
- L54 _private member_ `FOnGameplayTagRenamed OnGameplayTagRenamed;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ETextCommit`
- L15 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnGameplayTagRenamed, FString , FString );`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/AssetDefinition_GameplayTagAssetBase.h` (Public)


#### class `UAssetDefinition_GameplayTagAssetBase`  
`class UAssetDefinition_GameplayTagAssetBase : public UAssetDefinitionDefault`  
_L16-43_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAssetDefinitionDefault`
- desc: Base asset type actions for any classes with gameplay tagging
- L21 _public function_ `UAssetDefinition_GameplayTagAssetBase()`
- L25 _public prototype_ `static void AddGameplayTagsEditMenuExtension(FToolMenuSection& InSection, TArray<UObject*> InObjects, const FName& OwnedGameplayTagPropertyName);` — Traditionally these are implemented in a MenuExtension namespace. However, UAssetDefinition_GameplayTagAssetBase is an abstract class, and the derived classes need to invoke this in their static MenuExtension functions
- L29 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override` — Overridden to specify misc category
- L42 _private prototype_ `static void OpenGameplayTagEditor(TArray<UObject*> Objects, TArray<FGameplayTagContainer> Containers, const FName& OwnedGameplayTagPropertyName);` — Open the gameplay tag editor @param TagAssets	Assets to open the editor with

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYTAGSEDITOR_API`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/GameplayTagsEditorModule.h` (Public)


#### class `IGameplayTagsEditorModule`  
`class IGameplayTagsEditorModule : public IModuleInterface`  
_L21-87_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L32 _public function_ `static inline IGameplayTagsEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L48 _public prototype_ `virtual bool AddNewGameplayTagToINI(const FString& NewTag, const FString& Comment = TEXT(""), FName TagSourceName = NAME_None, bool bIsRestrictedTag = false, bool bAllowNonRestrictedChildren = true) = 0;` — Tries to add a new gameplay tag to the ini lists
- L51 _public prototype_ `virtual bool DeleteTagFromINI(TSharedPtr<struct FGameplayTagNode> TagNodeToDelete) = 0;` — Tries to delete a tag from the library. This will pop up special UI or error messages as needed. It will also delete redirectors if that is specified.
- L52 _public prototype_ `virtual void DeleteTagsFromINI(const TArray<TSharedPtr<struct FGameplayTagNode>>& TagNodesToDelete) = 0;`
- L55 _public prototype_ `virtual bool RenameTagInINI(const FString& TagToRename, const FString& TagToRenameTo, bool bRenameChildren = true) = 0;` — Tries to rename a tag, leaving a rediretor in the ini, and adding the new tag if it does not exist yet
- L58 _public prototype_ `virtual bool UpdateTagInINI(const FString& TagToUpdate, const FString& Comment, bool bIsRestrictedTag, bool bAllowNonRestrictedChildren) = 0;` — Updates info about a tag
- L61 _public prototype_ `virtual bool MoveTagsBetweenINI(const TArray<FString>& TagsToMove, const FName& TargetTagSource, TArray<FString>& OutTagsMoved, TArray<FString>& OutFailedToMoveTags) = 0;` — Tries to move existing tags from each source ini lists to the target source ini list.
- L64 _public prototype_ `virtual bool AddTransientEditorGameplayTag(const FString& NewTransientTag) = 0;` — Adds a transient gameplay tag (only valid for the current editor session)
- L67 _public prototype_ `virtual bool AddNewGameplayTagSource(const FString& NewTagSource, const FString& RootDirToUse = FString()) = 0;` — Adds a new tag source, well use project config directory if not specified. This will not save anything until a tag is added
- L75 _public prototype_ `virtual TSharedRef<SWidget> MakeGameplayTagContainerWidget(FOnSetGameplayTagContainer OnSetTag, TSharedPtr<FGameplayTagContainer> GameplayTagContainer, const FString& FilterString = FString()) = 0;` — Creates a simple version of a tag container widget that has a default value and will call a custom callback @param OnSetTag			Delegate called when container is changed @param GameplayTagValue	Shared ptr to tag container value that will be used as default and modified @param FilterString		Optional filter string, same format as Categories metadata on tag properties
- L83 _public prototype_ `virtual TSharedRef<SWidget> MakeGameplayTagWidget(FOnSetGameplayTag OnSetTag, TSharedPtr<FGameplayTag> GameplayTag, const FString& FilterString = FString()) = 0;` — Creates a simple version of a gameplay tag widget that has a default value and will call a custom callback @param OnSetTag			Delegate called when tag is changed @param GameplayTagValue	Shared ptr to tag value that will be used as default and modified @param FilterString		Optional filter string, same format as Categories metadata on tag properties
- L86 _public prototype_ `virtual void GetUnusedGameplayTags(TArray<TSharedPtr<struct FGameplayTagNode>>& OutUnusedTags) = 0;` — Returns the list of gameplay tags that are not used by content

#### struct `FGameplayTagCustomizationPublic`  
`struct FGameplayTagCustomizationPublic`  
_L90-93_
- desc: This is public so that child structs of FGameplayTag can use the details customization
- L92 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`

#### struct `FGameplayTagContainerCustomizationPublic`  
`struct FGameplayTagContainerCustomizationPublic`  
_L96-99_
- desc: This is public so that child structs of FGameplayTagContainer can use the details customization
- L98 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`

#### struct `FRestrictedGameplayTagCustomizationPublic`  
`struct FRestrictedGameplayTagCustomizationPublic`  
_L101-104_
- L103 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEPLAYTAGSEDITOR_API`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetGameplayTag, const FGameplayTag&);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetGameplayTag, const FGameplayTag&);`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetGameplayTagContainer, const FGameplayTagContainer&);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetGameplayTagContainer, const FGameplayTagContainer&);`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/SGameplayTagChip.h` (Public)


#### class `SGameplayTagChip`  
`class SGameplayTagChip : public SCompoundWidget`  
_L17-91_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a single gameplay tag with optional clear button.
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal(FReply, FOnClearPressed);`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal(FReply, FOnEditPressed);`
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal(FReply, FOnNavigate);`
- L26 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnMenu, const FPointerEvent& );`
- L28 _public function_ `SLATE_BEGIN_ARGS(SGameplayTagChip) : _EnableNavigation(false) , _ReadOnly(false) , _IsSelected(true) , _ShowClearButton(true)`
- L35 _public prototype_ `SLATE_EVENT(FOnEditPressed, OnEditPressed)` — Callback for when button body is pressed
- L68 _public prototype_ `SGameplayTagChip();`
- L70 _public prototype_ `void Construct(const FArguments& InArgs);`
- L74 _private prototype_ `void UpdatePillStyle();`
- L76 _private member_ `TSlateAttribute<bool> IsSelectedAttribute;`
- L77 _private member_ `TSlateAttribute<bool> ShowClearButtonAttribute;`
- L78 _private member_ `TSlateAttribute<FText> ToolTipTextAttribute;`
- L79 _private member_ `TSlateAttribute<FText> TextAttribute;`
- L80 _private member_ `TOptional<FSlateColor> TextColor;`
- L81 _private member_ `TSharedPtr<SButton> ChipButton;`
- L82 _private member_ `TSharedPtr<SButton> ClearButton;`
- L83 _private member_ `TSharedPtr<STextBlock> TagText;`
- L84 _private member_ `FOnClearPressed OnClearPressed;`
- L85 _private member_ `FOnEditPressed OnEditPressed;`
- L86 _private member_ `FOnNavigate OnNavigate;`
- L87 _private member_ `FOnMenu OnMenu;`
- L88 _private member_ `bool bEnableNavigation = false;`
- L89 _private member_ `bool bReadOnly = false;`
- L90 _private member_ `bool bLastHasIsSelected = false;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FOnClearPressed);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FOnEditPressed);`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FOnNavigate);`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnMenu, const FPointerEvent& );`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/SGameplayTagCombo.h` (Public)


#### class `SGameplayTagCombo`  
`class SGameplayTagCombo : public SCompoundWidget`  
_L21-105_
- inherits: `SCompoundWidget`
- desc: Widget for editing a Gameplay Tag.
- L27 _public function_ `DECLARE_DELEGATE_OneParam(FOnTagChanged, const FGameplayTag ) SLATE_BEGIN_ARGS(SGameplayTagCombo) : _Filter() , _ReadOnly(false) , _DisplayShortTagNames(false) , _EnableNavigation(false) , _PropertyHandle(nullptr)`
- L37 _public prototype_ `SLATE_ARGUMENT(FString, Filter)` — Comma delimited string of tag root names to filter by
- L67 _public prototype_ `SGameplayTagCombo();`
- L69 _public prototype_ `void Construct(const FArguments& InArgs);`
- L71 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L75 _private prototype_ `bool ShowClearButton() const;`
- L76 _private prototype_ `FText GetText() const;`
- L77 _private prototype_ `bool IsValueEnabled() const;`
- L78 _private prototype_ `FText GetToolTipText() const;`
- L79 _private prototype_ `bool IsSelected() const;`
- L80 _private prototype_ `FReply OnClearPressed();`
- L81 _private prototype_ `void OnMenuOpenChanged(const bool bOpen) const;`
- L82 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L83 _private prototype_ `FGameplayTag GetCommonTag() const;`
- L84 _private prototype_ `FReply OnTagMenu(const FPointerEvent& MouseEvent);`
- L85 _private prototype_ `FReply OnEditTag() const;`
- L86 _private prototype_ `void RefreshTagsFromProperty();`
- L87 _private prototype_ `void OnTagSelected(const TArray<FGameplayTagContainer>& TagContainers);`
- L88 _private prototype_ `void OnClearTag();`
- L89 _private prototype_ `void OnCopyTag(const FGameplayTag TagToCopy) const;`
- L90 _private prototype_ `void OnPasteTag();`
- L91 _private prototype_ `bool CanPaste() const;`
- L93 _private member_ `TSlateAttribute<FGameplayTag> TagAttribute;`
- L94 _private member_ `TArray<FGameplayTag> TagsFromProperty;`
- L95 _private member_ `bool bHasMultipleValues = false;`
- L96 _private member_ `bool bIsReadOnly = false;`
- L97 _private member_ `bool bDisplayShortTagNames = false;`
- L98 _private member_ `FString Filter;`
- L99 _private member_ `FString SettingsName;`
- L100 _private member_ `FOnTagChanged OnTagChanged;`
- L101 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L102 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L103 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L104 _private member_ `TSharedPtr<SGameplayTagPicker> TagPicker;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTagChanged, const FGameplayTag ) SLATE_BEGIN_ARGS(SGameplayTagCombo) : _Filter() , _ReadOnly(false) , _DisplayShortTagNames(false) , _EnableNavigation(false) , _PropertyHandle(nullptr) {}`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/SGameplayTagContainerCombo.h` (Public)


#### class `SGameplayTagContainerCombo`  
`class SGameplayTagContainerCombo : public SCompoundWidget`  
_L23-148_
- inherits: `SCompoundWidget`
- desc: Widget for editing a Gameplay Tag Container.
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTagContainerComboClosed, const FGameplayTagContainer& ) DECLARE_DELEGATE_OneParam(FOnTagContainerChanged, const FGameplayTagContainer& )`
- L35 _public function_ `SLATE_BEGIN_ARGS(SGameplayTagContainerCombo) : _Filter() , _ReadOnly(false) , _DisplayShortTagNames(false) , _EnableNavigation(false) , _PropertyHandle(nullptr)`
- L43 _public prototype_ `SLATE_ARGUMENT(FString, Filter)` — Comma delimited string of tag root names to filter by
- L82 _public prototype_ `SGameplayTagContainerCombo();`
- L84 _public prototype_ `void Construct(const FArguments& InArgs);`
- L86 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L89 _public prototype_ `bool IsOpen() const;` — Returns true if the expanded edit UI is open
- L92 _public prototype_ `void Open(FGameplayTag TagToFocus = { });` — Opens the expanded edit UI, optionally focusing on a specific tag
- L94 _public prototype_ `void RefreshTagContainers();`
- L112 _private prototype_ `bool IsValueEnabled() const;`
- L113 _private prototype_ `TSharedRef<ITableRow> MakeTagListViewRow(TSharedPtr<FEditableItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L114 _private prototype_ `void OnMenuOpenChanged(const bool bOpen);`
- L115 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L116 _private prototype_ `FText GetTagToolTipText(const FGameplayTag TagToDisplay) const;`
- L118 _private prototype_ `FReply OnTagMenu(const FPointerEvent& MouseEvent, const FGameplayTag GameplayTag);`
- L119 _private prototype_ `FReply OnEmptyMenu(const FPointerEvent& MouseEvent);`
- L120 _private prototype_ `FReply OnEditClicked(const FGameplayTag TagToHilight);`
- L121 _private prototype_ `FReply OnClearAllClicked();`
- L122 _private prototype_ `FReply OnClearTagClicked(const FGameplayTag TagToClear);`
- L123 _private prototype_ `void OnTagChanged(const TArray<FGameplayTagContainer>& TagContainers);`
- L124 _private prototype_ `void OnClearAll();`
- L125 _private prototype_ `void OnCopyTag(const FGameplayTag TagToCopy) const;`
- L126 _private prototype_ `void OnPasteTag();`
- L127 _private prototype_ `bool CanPaste() const;`
- L128 _private prototype_ `void OnSearchForAnyReferences() const;`
- L130 _private member_ `TSlateAttribute<FGameplayTagContainer> TagContainerAttribute;`
- L131 _private member_ `TArray<FGameplayTagContainer> CachedTagContainers;`
- L132 _private member_ `TArray<TSharedPtr<FEditableItem>> TagsToEdit;`
- L133 _private member_ `TSharedPtr<SListView<TSharedPtr<FEditableItem>>> TagListView;`
- L135 _private member_ `FString Filter;`
- L136 _private member_ `FString SettingsName;`
- L137 _private member_ `bool bIsReadOnly = false;`
- L138 _private member_ `bool bDisplayShortTagNames = false;`
- L139 _private member_ `FOnTagCleared OnTagCleared;`
- L140 _private member_ `FOnTagContainerComboClosed OnTagContainerComboClosed;`
- L141 _private member_ `FOnTagContainerChanged OnTagContainerChanged;`
- L142 _private member_ `FOnGetTagTextColor OnGetTagTextColor;`
- L143 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L144 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L145 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L146 _private member_ `TSharedPtr<SGameplayTagPicker> TagPicker;`
- L147 _private member_ `FGameplayTag TagToHilight;`

#### struct `SGameplayTagContainerCombo::FEditableItem`  
`struct FEditableItem`  
_L98-110_
- L100 _public prototype_ `FEditableItem() = default;`
- L101 _public function_ `FEditableItem(const FGameplayTag InTag, const int InCount = 1) : Tag(InTag) , Count(InCount)`
- L107 _public member_ `FGameplayTag Tag;`
- L108 _public member_ `int32 Count = 0;`
- L109 _public member_ `bool bMultipleValues = false;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE(FOnTagCleared) DECLARE_DELEGATE_OneParam(FOnTagContainerComboClosed, const FGameplayTagContainer& ) DECLARE_DELEGATE_OneParam(FOnTagContainerChanged, const FGameplayTagContainer& )`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTagContainerComboClosed, const FGameplayTagContainer& ) DECLARE_DELEGATE_OneParam(FOnTagContainerChanged, const FGameplayTagContainer& )`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTagContainerChanged, const FGameplayTagContainer& )`
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FSlateColor>, FOnGetTagTextColor, const FGameplayTag& );` — If bound returns optional color to use for this tag text.

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/SGameplayTagPicker.h` (Public)


#### enum `EGameplayTagPickerMode`  
`enum class EGameplayTagPickerMode : uint8`  
_L24-29_
- desc: Determines the behavior of the gameplay tag UI depending on where it's used
- L26 _public enumerator_ `SelectionMode` — Allows selecting tags for gameplay tag containers.
- L27 _public enumerator_ `ManagementMode` — Allows renaming/deleting tags, does not require gameplay tag containers.
- L28 _public enumerator_ `HybridMode` — Allows doing operations from both Selection and Management mode.

#### class `SGameplayTagPicker`  
`class SGameplayTagPicker : public SCompoundWidget`  
_L32-458_
- inherits: `SCompoundWidget`
- desc: Widget allowing user to tag assets with gameplay tags
- L48 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(ETagFilterResult, FOnFilterTag, const TSharedPtr<FGameplayTagNode>&) SLATE_BEGIN_ARGS(SGameplayTagPicker) : _Filter() , _SettingsName(TEXT("")) , _ReadOnly(false) , _MultiSelect(true) , _RestrictedTags(false) , _ShowMenuItems(false) , _PropertyHandle(nullptr) , _GameplayTagPickerMode(EGameplayTagPickerMode::SelectionMode) , _MaxHeight(260.0f) , _Padding(FMargin(2.0f))`
- L63 _public prototype_ `SLATE_ARGUMENT(FString, Filter)` — Comma delimited string of tag root names to filter by
- L116 _public prototype_ `static bool GetEditableTagContainersFromPropertyHandle(const TSharedRef<IPropertyHandle>& PropHandle, TArray<FGameplayTagContainer>& OutEditableContainers);` — Given a property handle, try and extract the editable tag containers from within it (when dealing with a struct property of type FGameplayTagContainer). @return True if it was possible to extract containers (even if no containers were extracted), or false otherwise.
- L121 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the actual widget
- L123 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L126 _public prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Updates the tag list when the filter text changes
- L129 _public prototype_ `bool FilterChildrenCheck(TSharedPtr<FGameplayTagNode>& InItem) const;` — Returns true if this TagNode has any children that match the current filter
- L132 _public prototype_ `bool FilterChildrenCheckRecursive(TSharedPtr<FGameplayTagNode>& InItem) const;` — Child recursion helper for FilterChildrenCheck()
- L135 _public prototype_ `void RefreshTags();` — Refreshes the tags that should be displayed by the widget
- L138 _public prototype_ `void RefreshOnNextTick();` — Forces the widget to refresh its tags on the next tick
- L141 _public prototype_ `void RequestScrollToView(const FGameplayTag Tag);` — Scrolls the view to specified tag.
- L144 _public prototype_ `TSharedPtr<SWidget> GetWidgetToFocusOnOpen();` — Gets the widget to focus once the menu opens.
- L147 _public prototype_ `void SetTagContainers(TConstArrayView<FGameplayTagContainer> TagContainers);` — Sets tag containers to edit.
- L158 _private prototype_ `void OnPostUndoRedo();`
- L161 _private prototype_ `void VerifyAssetTagValidity();` — Verify the tags are all valid and if not prompt the user.
- L164 _private prototype_ `void FilterTagTree();` — Filters the tree view based on the current filter text.
- L167 _private member_ `static const FString SettingsIniSection;` — string that sets the section of the ini file to use for this class
- L170 _private prototype_ `static const FString& GetGameplayTagsEditorStateIni();` — Filename of ini file to store state of the UI
- L180 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FGameplayTagNode> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row widget for the specified item node and table @param InItem		Tag node to generate a row widget for @param OwnerTable	Table that owns the row @return Generated row widget for the item node
- L188 _private prototype_ `void OnGetChildren(TSharedPtr<FGameplayTagNode> InItem, TArray< TSharedPtr<FGameplayTagNode> >& OutChildren);` — Get children nodes of the specified node @param InItem		Node to get children of @param OutChildren	[OUT] Array of children nodes, if any
- L196 _private prototype_ `void OnTagCheckStatusChanged(ECheckBoxState NewCheckState, TSharedPtr<FGameplayTagNode> NodeChanged);` — Called via delegate when the status of a check box in a row changes @param NewCheckState	New check box state @param NodeChanged	Node that was checked/unchecked
- L205 _private prototype_ `ECheckBoxState IsTagChecked(TSharedPtr<FGameplayTagNode> Node) const;` — Called via delegate to determine the checkbox state of the specified node @param Node	Node to find the checkbox state of @return Checkbox state of the specified node
- L210 _private prototype_ `bool IsExactTagInCollection(TSharedPtr<FGameplayTagNode> Node) const;` — @return true if the exact Tag provided is included in any of the tag containers the widget is editing.
- L218 _private prototype_ `void OnAllowChildrenTagCheckStatusChanged(ECheckBoxState NewCheckState, TSharedPtr<FGameplayTagNode> NodeChanged);` — Called via delegate when the status of the allow non-restricted children check box in a row changes @param NewCheckState	New check box state @param NodeChanged	Node that was checked/unchecked
- L227 _private prototype_ `ECheckBoxState IsAllowChildrenTagChecked(TSharedPtr<FGameplayTagNode> Node) const;` — Called via delegate to determine the non-restricted children checkbox state of the specified node @param Node	Node to find the non-restricted children checkbox state of @return Non-restricted children heckbox state of the specified node
- L230 _private prototype_ `EVisibility DetermineAllowChildrenVisible(TSharedPtr<FGameplayTagNode> Node) const;` — Helper function to determine the visibility of the checkbox for allowing non-restricted children of restricted gameplay tags
- L237 _private prototype_ `void OnTagChecked(TSharedPtr<FGameplayTagNode> NodeChecked);` — Helper function called when the specified node is checked @param NodeChecked	Node that was checked by the user
- L244 _private prototype_ `void OnTagUnchecked(TSharedPtr<FGameplayTagNode> NodeUnchecked);` — Helper function called when the specified node is unchecked @param NodeUnchecked	Node that was unchecked by the user
- L252 _private prototype_ `void UncheckChildren(TSharedPtr<FGameplayTagNode> NodeUnchecked, FGameplayTagContainer& EditableContainer);` — Recursive function to uncheck all child tags @param NodeUnchecked	Node that was unchecked by the user @param EditableContainer The container we are removing the tags from
- L261 _private prototype_ `FSlateColor GetTagTextColour(TSharedPtr<FGameplayTagNode> Node) const;` — Called via delegate to determine the text colour of the specified node @param Node	Node to find the colour of @return Text colour of the specified node
- L264 _private prototype_ `void OnManageTagsClicked(TSharedPtr<FGameplayTagNode> Node, TSharedPtr<SComboButton> OwnerCombo);` — Called when the user clicks the "Create and Manage Gameplay Tags" button; Opens Gameplay Tag manager window.
- L267 _private prototype_ `void OnClearAllClicked(TSharedPtr<SComboButton> OwnerCombo);` — Called when the user clicks the "Clear All" button; Clears all tags
- L270 _private prototype_ `void OnExpandAllClicked(TSharedPtr<SComboButton> OwnerCombo);` — Called when the user clicks the "Expand All" button; Expands the entire tag tree
- L273 _private prototype_ `void OnCollapseAllClicked(TSharedPtr<SComboButton> OwnerCombo);` — Called when the user clicks the "Collapse All" button; Collapses the entire tag tree
- L281 _private prototype_ `void SetTagTreeItemExpansion(bool bExpand, bool bPersistExpansion = false);` — Helper function to set the expansion state of the tree widget @param bExpand If true, expand the entire tree; Otherwise, collapse the entire tree @param bPersistExpansion If true, persist the expansion state.
- L290 _private prototype_ `void SetTagNodeItemExpansion(TSharedPtr<FGameplayTagNode> Node, bool bExpand, bool bPersistExpansion = false);` — Helper function to set the expansion state of a specific node @param Node		Node to set the expansion state of @param bExpand	If true, expand the node; Otherwise, collapse the node @param bPersistExpansion If true, persist the expansion state.
- L293 _private prototype_ `void LoadSettings();` — Load settings for the tags
- L296 _private prototype_ `void MigrateSettings();` — Migrate settings
- L299 _private prototype_ `EVisibility DetermineExpandableUIVisibility() const;` — Helper function to determine the visibility of the expandable UI controls
- L302 _private prototype_ `bool CanAddNewTag() const;` — Helper function to determine the visibility of the Add New Tag widget
- L305 _private prototype_ `bool CanAddNewSubTag(TSharedPtr<FGameplayTagNode> Node) const;` — Helper function to determine the visibility of the Add New Subtag widget
- L308 _private prototype_ `bool CanModifyTag(TSharedPtr<FGameplayTagNode> Node) const;` — Helper function to determine if tag can be modified
- L311 _private prototype_ `void LoadTagNodeItemExpansion(TSharedPtr<FGameplayTagNode> Node );` — Recursive load function to go through all tags in the tree and set the expansion
- L314 _private prototype_ `void SetDefaultTagNodeItemExpansion(TSharedPtr<FGameplayTagNode> Node);` — Recursive function to go through all tags in the tree and set the expansion to default
- L317 _private prototype_ `void OnExpansionChanged(TSharedPtr<FGameplayTagNode> InItem, bool bIsExpanded);` — Expansion changed callback
- L320 _private prototype_ `void OnGameplayTagAdded(const FString& TagName, const FString& TagComment, const FName& TagSource);` — Callback for when a new tag is added
- L323 _private prototype_ `void ShowInlineAddTagWidget(const EGameplayTagAdd Mode, TSharedPtr<FGameplayTagNode> InTagNode = TSharedPtr<FGameplayTagNode>());` — Initializes the inline add tag widget and makes in visible.
- L326 _private prototype_ `bool IsNodeSingleRoot(const TSharedPtr<FGameplayTagNode>& InNode) const;` — Returns true if the passed in node is the root node, and there is only one node on the root level
- L328 _private prototype_ `FText GetHighlightText() const;`
- L331 _private prototype_ `TSharedRef<SWidget> MakeTagActionsMenu(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo, const bool bInShouldCloseWindowAfterMenuSelection);` — Creates a dropdown menu to provide additional functionality for tags (renaming, deletion, search for references, etc.)
- L334 _private prototype_ `TSharedRef<SWidget> MakeSettingsMenu(TSharedPtr<SComboButton> OwnerCombo);` — Creates settings menu content.
- L336 _private prototype_ `void OnAddSubTag(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);`
- L338 _private prototype_ `void OnDuplicateTag(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);`
- L341 _private prototype_ `void OnRenameTag(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Attempts to rename the tag through a dialog box
- L344 _private prototype_ `void OnDeleteTag(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Attempts to delete the specified tag
- L347 _private prototype_ `void OnSelectExactTag(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Attempts to select the exact specified tag
- L350 _private prototype_ `void OnUnselectExactTag(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Attempts to unselect the specified tag, but not the children
- L353 _private prototype_ `void OnSearchForReferences(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Searches for all references for the selected tag
- L356 _private prototype_ `void OnSearchForReferencesAsChildren(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Searches for all references for the selected tag and its children
- L359 _private prototype_ `void OnCopyTagNameToClipboard(TSharedPtr<FGameplayTagNode> InTagNode, TSharedPtr<SComboButton> OwnerCombo);` — Copies individual tag's name to clipboard.
- L362 _private prototype_ `bool CanSelectTags() const;` — Returns true if the user can select tags from the widget
- L365 _private prototype_ `void OnContainersChanged();` — Called when tags are selected.
- L368 _private prototype_ `void OpenRenameGameplayTagDialog(TSharedPtr<FGameplayTagNode> GameplayTagNode) const;` — Opens a dialog window to rename the selected tag
- L371 _private prototype_ `void OnGameplayTagRenamed(FString OldTagName, FString NewTagName);` — Delegate that is fired when a tag is successfully renamed
- L374 _private prototype_ `void GetFilteredGameplayRootTags(const FString& InFilterString, TArray<TSharedPtr<FGameplayTagNode>>& OutNodes) const;` — Populate tag items from the gameplay tags manager.
- L377 _private prototype_ `TSharedPtr<SWidget> OnTreeContextMenuOpening();` — Called to create context menu for the tag tree items.
- L380 _private prototype_ `void OnTreeSelectionChanged(TSharedPtr<FGameplayTagNode> SelectedItem, ESelectInfo::Type SelectInfo);` — Called when the tag tree selection changes.
- L383 _private prototype_ `FReply OnTreeKeyDown(const FGeometry& Geometry, const FKeyEvent& Key);` — Called to handle key presses in the tag tree.
- L386 _private member_ `FString SettingsName;` — Holds the Name of this TagContainer used for saving out expansion settings
- L389 _private member_ `TArray<FString> FilterStringTokens;` — Filter string tokens used during search box
- L392 _private member_ `FString RootFilterString;` — root filter (passed in on creation)
- L395 _private member_ `FOnFilterTag TagFilter;` — User specified filter function.
- L398 _private member_ `bool bReadOnly = false;` — Flag to set if the list is read only
- L401 _private member_ `bool bMultiSelect = true;` — Flag to set if we can select multiple items form the list
- L404 _private member_ `bool bDelayRefresh = false;` — If true, refreshes tags on the next frame
- L407 _private member_ `bool bRestrictedTags = false;` — If true, this widget is displaying restricted tags; if false this widget displays regular gameplay tags.
- L410 _private member_ `float MaxHeight = 260.0f;` — The maximum height of the gameplay tag tree. If 0, the height is unbound.
- L413 _private member_ `TArray<TSharedPtr<FGameplayTagNode>> TagItems;` — Array of all tags
- L416 _private member_ `TArray<TSharedPtr<FGameplayTagNode>> FilteredTagItems;` — Array of tags filtered to be displayed in the TreeView
- L419 _private member_ `TSharedPtr<SBorder> TagTreeContainerWidget;` — Container widget holding the tag tree
- L422 _private member_ `TSharedPtr<STreeView<TSharedPtr<FGameplayTagNode>>> TagTreeWidget;` — Tree widget showing the gameplay tag library
- L425 _private member_ `TSharedPtr<SSearchBox> SearchTagBox;` — Allows for the user to find a specific gameplay tag in the tree
- L428 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Property to edit
- L431 _private member_ `TArray<FGameplayTagContainer> TagContainers;` — Containers to modify, ignored if PropertyHandle is set.
- L434 _private member_ `FOnTagChanged OnTagChanged;` — Called when the Tag list changes
- L437 _private member_ `FOnRefreshTagContainers OnRefreshTagContainers;` — Called on when tags might need refreshing (e.g. after undo/redo or when tags change).
- L440 _private member_ `FGameplayTag RequestedScrollToTag;` — Tag to scroll to, cleared after scroll is requested.
- L443 _private member_ `EGameplayTagPickerMode GameplayTagPickerMode = EGameplayTagPickerMode::SelectionMode;` — Determines behavior of the widget
- L446 _private member_ `bool bInSelectionChanged = false;` — Guard value used to prevent feedback loops in selection handling.
- L449 _private member_ `bool bPersistExpansionChange = true;` — Guard value used define if expansion code should persist the expansion operations.
- L452 _private member_ `TSet<TSharedPtr<FGameplayTagNode>> CachedExpandedItems;` — Expanded items cached from settings
- L454 _private member_ `TSharedPtr<SAddNewGameplayTagWidget> AddNewTagWidget;`
- L455 _private member_ `bool bNewTagWidgetVisible = false;`
- L457 _private member_ `FDelegateHandle PostUndoRedoDelegateHandle;`

#### enum `SGameplayTagPicker::ETagFilterResult`  
`enum class ETagFilterResult`  
_L42-46_
- L44 _public enumerator_ `IncludeTag`
- L45 _public enumerator_ `ExcludeTag`

#### enum `SGameplayTagPicker::EGameplayTagAdd`  
`enum class EGameplayTagAdd : uint8`  
_L151-156_
- L153 _public enumerator_ `Root`
- L154 _public enumerator_ `Child`
- L155 _public enumerator_ `Duplicate`

#### struct `FGameplayTagManagerWindowArgs`  
`struct FGameplayTagManagerWindowArgs`  
_L461-467_
- L463 _public member_ `FText Title;`
- L464 _public member_ `FString Filter;` — Comma delimited string of tag root names to filter by
- L465 _public member_ `FGameplayTag HighlightedTag;` — Tag to highlight when window is opened.
- L466 _public member_ `bool bRestrictedTags;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GAMEPLAYTAGSEDITOR_API`
- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTagChanged, const TArray<FGameplayTagContainer>& ) DECLARE_DELEGATE_OneParam(FOnRefreshTagContainers, SGameplayTagPicker& ) enum class ETagFilterResult { IncludeTag, ExcludeTag };` — Called when a tag status is changed
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRefreshTagContainers, SGameplayTagPicker& ) enum class ETagFilterResult { IncludeTag, ExcludeTag };` — Called on when tags might need refreshing (e.g. after undo/redo or when tags change). Use SetTagContainers() to set the new tags.
- L48 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ETagFilterResult, FOnFilterTag, const TSharedPtr<FGameplayTagNode>&) SLATE_BEGIN_ARGS(SGameplayTagPicker) : _Filter() , _SettingsName(TEXT("")) , _ReadOnly(false) , _MultiSelect(true) , _RestrictedTags(false) , _ShowMenuItems(false) , _PropertyHandle(nullptr) , _GameplayTagPickerMode(EGameplayTagPickerMode::SelectionMode) , _MaxHeight(260.0f) , _Padding(FMargin(2.0f)) {}`
- L469 _namespace_ `namespace UE`
- L469 _namespace_ `namespace GameplayTags` (scope `UE`)
- L469 _namespace_ `namespace Editor` (scope `UE::GameplayTags`)
- L471 _prototype_ `TWeakPtr<SGameplayTagPicker> OpenGameplayTagManager(const FGameplayTagManagerWindowArgs& Args);` (scope `UE::GameplayTags::Editor`)
- L472 _prototype_ `TSharedRef<SGameplayTagPicker> Create(const FGameplayTagManagerWindowArgs& Args);` (scope `UE::GameplayTags::Editor`)

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/SGameplayTagQueryEntryBox.h` (Public)


#### class `SGameplayTagQueryEntryBox`  
`class SGameplayTagQueryEntryBox : public SCompoundWidget`  
_L17-82_
- inherits: `SCompoundWidget`
- desc: Widget for editing a Gameplay Tag Query.
- L23 _public function_ `DECLARE_DELEGATE_OneParam(FOnTagQueryChanged, const FGameplayTagQuery& ) SLATE_BEGIN_ARGS(SGameplayTagQueryEntryBox) : _Filter() , _ReadOnly(false) , _DescriptionMaxWidth(250.0f) , _PropertyHandle(nullptr)`
- L32 _public prototype_ `SLATE_ARGUMENT(FString, Filter) SLATE_ARGUMENT(bool, ReadOnly) SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ATTRIBUTE(FGameplayTagQuery, TagQuery) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnTagQueryChanged, OnTagQueryChanged) SLATE_END_ARGS();` — Comma delimited string of tag root names to filter by
- L49 _public prototype_ `SGameplayTagQueryEntryBox();`
- L51 _public prototype_ `void Construct(const FArguments& InArgs);`
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _private prototype_ `void CacheQueryList();`
- L58 _private prototype_ `struct FGameplayTagQueryWindowArgs BuildWindowArgs();`
- L59 _private prototype_ `FReply OnEditButtonClicked();`
- L60 _private prototype_ `FReply OnClearAllButtonClicked();`
- L61 _private prototype_ `EVisibility GetQueryDescVisibility() const;`
- L62 _private prototype_ `bool HasAnyValidQueries() const;`
- L63 _private prototype_ `bool IsValueEnabled() const;`
- L64 _private prototype_ `FText GetQueryDescText() const;`
- L65 _private prototype_ `FText GetQueryDescTooltip() const;`
- L66 _private prototype_ `void OnQueriesCommitted(const TArray<FGameplayTagQuery>& TagQueries);`
- L68 _private member_ `TSlateAttribute<FGameplayTagQuery> TagQueryAttribute;`
- L70 _private member_ `bool bIsReadOnly = false;`
- L71 _private member_ `FString Filter;`
- L72 _private member_ `FOnTagQueryChanged OnTagQueryChanged;`
- L73 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L74 _private member_ `TArray<FGameplayTagQuery> CachedQueries;`
- L76 _private member_ `TSharedPtr<SHorizontalBox> WidgetContainer;`
- L78 _private member_ `TWeakPtr<SGameplayTagQueryWidget> QueryWidget;`
- L80 _private member_ `FText QueryDescription;`
- L81 _private member_ `FText QueryDescriptionTooltip;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTagQueryChanged, const FGameplayTagQuery& ) SLATE_BEGIN_ARGS(SGameplayTagQueryEntryBox) : _Filter() , _ReadOnly(false) , _DescriptionMaxWidth(250.0f) , _PropertyHandle(nullptr) {} SLATE_ARGUMENT(FString, Filter) SLATE_ARGUMENT(bool, ReadOnly) SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ATTRIBUTE(FGameplayTagQuery, TagQuery) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnTagQueryChanged, OnTagQueryChanged) SLATE_END_ARGS();`

### `Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Public/SGameplayTagWidget.h` (Public)


#### enum `EGameplayTagUIMode`  
`enum class EGameplayTagUIMode : uint8`  
_L23-28_
- desc: Determines the behavior of the gameplay tag UI depending on where it's used
- L25 _public enumerator_ `SelectionMode` — Allows selecting tags for gameplay tag containers.
- L26 _public enumerator_ `ManagementMode` — Allows renaming/deleting tags, does not require gameplay tag containers.
- L27 _public enumerator_ `HybridMode` — Allows doing operations from both Selection and Management mode.

#### class `SGameplayTagWidget`  
`class SGameplayTagWidget : public SCompoundWidget`  
_L31-426_
- inherits: `SCompoundWidget`
- desc: Widget allowing user to tag assets with gameplay tags
- L43 _public function_ `DECLARE_DELEGATE_RetVal_OneParam( ETagFilterResult, FOnFilterTag, const TSharedPtr<FGameplayTagNode>&) SLATE_BEGIN_ARGS( SGameplayTagWidget ) : _Padding(2.f) , _Filter() , _NewTagName(TEXT("")) , _ReadOnly( false ) , _TagContainerName( TEXT("") ) , _MultiSelect( true ) , _NewTagControlsInitiallyExpanded( false ) , _PropertyHandle( NULL ) , _GameplayTagUIMode( EGameplayTagUIMode::SelectionMode ) , _MaxHeight(260.0f) , _RestrictedTags( false ) , _ForceHideAddNewTag(false) , _ForceHideAddNewTagSource(false) , _ForceHideTagTreeControls(false) , _BackgroundBrush(FAppStyle::GetBrush("ToolPanel.GroupBorder")) , _TagTreeViewBackgroundBrush(nullptr)`
- L104 _public prototype_ `static bool EnumerateEditableTagContainersFromPropertyHandle(const TSharedRef<IPropertyHandle>& PropHandle, TFunctionRef<bool(const FEditableGameplayTagContainerDatum&)> Callback);` — Given a property handle, try and enumerate the editable tag containers from within it (when dealing with a struct property of type FGameplayTagContainer). @return True if it was possible to enumerate containers (even if no containers were enumerated), or false otherwise.
- L110 _public prototype_ `static bool GetEditableTagContainersFromPropertyHandle(const TSharedRef<IPropertyHandle>& PropHandle, TArray<FEditableGameplayTagContainerDatum>& OutEditableContainers);` — Given a property handle, try and extract the editable tag containers from within it (when dealing with a struct property of type FGameplayTagContainer). @return True if it was possible to extract containers (even if no containers were extracted), or false otherwise.
- L113 _public prototype_ `void Construct(const FArguments& InArgs, const TArray<FEditableGameplayTagContainerDatum>& EditableTagContainers);` — Construct the actual widget
- L115 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L118 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;` — Ensures that this widget will always account for the MaxHeight if it's specified
- L121 _public prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Updates the tag list when the filter text changes
- L124 _public prototype_ `bool FilterChildrenCheck( TSharedPtr<FGameplayTagNode> );` — Returns true if this TagNode has any children that match the current filter
- L127 _public prototype_ `bool IsAddingNewTag() const;` — Returns true if we're currently adding a new tag to an INI file
- L130 _public prototype_ `void RefreshTags();` — Refreshes the tags that should be displayed by the widget
- L133 _public prototype_ `void RefreshOnNextTick();` — Forces the widget to refresh its tags on the next tick
- L136 _public prototype_ `TSharedPtr<SWidget> GetWidgetToFocusOnOpen();` — Gets the widget to focus once the menu opens.
- L141 _private prototype_ `void VerifyAssetTagValidity();` — Verify the tags are all valid and if not prompt the user.
- L144 _private prototype_ `void FilterTagTree();` — Filters the tree view based on the current filter text.
- L147 _private member_ `static const FString SettingsIniSection;` — string that sets the section of the ini file to use for this class
- L150 _private prototype_ `static const FString& GetGameplayTagsEditorStateIni();` — Filename of ini file to store state of the UI
- L153 _private member_ `FString TagContainerName;` — Holds the Name of this TagContainer used for saving out expansion settings
- L156 _private member_ `FString FilterString;` — Filter string used during search box
- L159 _private member_ `FString RootFilterString;` — root filter (passed in on creation)
- L162 _private member_ `FOnFilterTag TagFilter;` — User specified filter function.
- L165 _private member_ `bool bReadOnly;` — Flag to set if the list is read only
- L168 _private member_ `bool bMultiSelect;` — Flag to set if we can select multiple items form the list
- L171 _private member_ `bool bAddTagSectionExpanded;` — Tracks if the Add Tag UI is expanded
- L174 _private member_ `bool bAddSourceSectionExpanded;` — Tracks if the Add Source UI is expanded
- L177 _private member_ `bool bDelayRefresh;` — If true, refreshes tags on the next frame
- L180 _private member_ `bool bRestrictedTags;` — If true, this widget is displaying restricted tags; if false this widget displays regular gameplay tags.
- L183 _private member_ `bool bForceHideAddNewTag;` — If true, this widget is unable to display the 'Add new tag' widget
- L186 _private member_ `bool bForceHideAddNewTagSource;` — If true, this widget is unable to display the 'Add new tag source' widget
- L189 _private member_ `bool bForceHideTagTreeControls;` — If true, this widget is unable to display the tag tree controls.
- L192 _private member_ `float MaxHeight;` — The maximum height of the gameplay tag tree. If 0, the height is unbound.
- L195 _private member_ `TArray< TSharedPtr<FGameplayTagNode> > TagItems;` — Array of tags to be displayed in the TreeView
- L198 _private member_ `TArray< TSharedPtr<FGameplayTagNode> > FilteredTagItems;` — Array of tags to be displayed in the TreeView
- L201 _private member_ `TSharedPtr<SWidget> TagTreeContainerWidget;` — Container widget holding the tag tree
- L204 _private member_ `TSharedPtr< STreeView< TSharedPtr<FGameplayTagNode> > > TagTreeWidget;` — Tree widget showing the gameplay tag library
- L207 _private member_ `TSharedPtr<class SAddNewGameplayTagWidget> AddNewTagWidget;` — The widget that controls how new gameplay tags are added to the config files
- L210 _private member_ `TSharedPtr<class SAddNewGameplayTagSourceWidget> AddNewTagSourceWidget;` — The widget that controls how new gameplay tag source files are added
- L213 _private member_ `TSharedPtr<SSearchBox> SearchTagBox;` — Allows for the user to find a specific gameplay tag in the tree
- L216 _private member_ `TArray<FEditableGameplayTagContainerDatum> TagContainers;` — Containers to modify
- L219 _private member_ `FOnTagChanged OnTagChanged;` — Called when the Tag list changes
- L222 _private member_ `EGameplayTagUIMode GameplayTagUIMode;` — Determines behavior of the widget
- L224 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L234 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FGameplayTagNode> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row widget for the specified item node and table @param InItem		Tag node to generate a row widget for @param OwnerTable	Table that owns the row @return Generated row widget for the item node
- L242 _private prototype_ `void OnGetChildren(TSharedPtr<FGameplayTagNode> InItem, TArray< TSharedPtr<FGameplayTagNode> >& OutChildren);` — Get children nodes of the specified node @param InItem		Node to get children of @param OutChildren	[OUT] Array of children nodes, if any
- L250 _private prototype_ `void OnTagCheckStatusChanged(ECheckBoxState NewCheckState, TSharedPtr<FGameplayTagNode> NodeChanged);` — Called via delegate when the status of a check box in a row changes @param NewCheckState	New check box state @param NodeChanged	Node that was checked/unchecked
- L259 _private prototype_ `ECheckBoxState IsTagChecked(TSharedPtr<FGameplayTagNode> Node) const;` — Called via delegate to determine the checkbox state of the specified node @param Node	Node to find the checkbox state of @return Checkbox state of the specified node
- L264 _private prototype_ `bool IsExactTagInCollection(TSharedPtr<FGameplayTagNode> Node) const;` — @return true if the exact Tag provided is included in any of the tag containers the widget is editing.
- L272 _private prototype_ `void OnAllowChildrenTagCheckStatusChanged(ECheckBoxState NewCheckState, TSharedPtr<FGameplayTagNode> NodeChanged);` — Called via delegate when the status of the allow non-restricted children check box in a row changes @param NewCheckState	New check box state @param NodeChanged	Node that was checked/unchecked
- L281 _private prototype_ `ECheckBoxState IsAllowChildrenTagChecked(TSharedPtr<FGameplayTagNode> Node) const;` — Called via delegate to determine the non-restricted children checkbox state of the specified node @param Node	Node to find the non-restricted children checkbox state of @return Non-restricted children heckbox state of the specified node
- L284 _private prototype_ `EVisibility DetermineAllowChildrenVisible(TSharedPtr<FGameplayTagNode> Node) const;` — Helper function to determine the visibility of the checkbox for allowing non-restricted children of restricted gameplay tags
- L291 _private prototype_ `void OnTagChecked(TSharedPtr<FGameplayTagNode> NodeChecked);` — Helper function called when the specified node is checked @param NodeChecked	Node that was checked by the user
- L298 _private prototype_ `void OnTagUnchecked(TSharedPtr<FGameplayTagNode> NodeUnchecked);` — Helper function called when the specified node is unchecked @param NodeUnchecked	Node that was unchecked by the user
- L306 _private prototype_ `void UncheckChildren(TSharedPtr<FGameplayTagNode> NodeUnchecked, FGameplayTagContainer& EditableContainer);` — Recursive function to uncheck all child tags @param NodeUnchecked	Node that was unchecked by the user @param EditableContainer The container we are removing the tags from
- L315 _private prototype_ `FSlateColor GetTagTextColour(TSharedPtr<FGameplayTagNode> Node) const;` — Called via delegate to determine the text colour of the specified node @param Node	Node to find the colour of @return Text colour of the specified node
- L318 _private prototype_ `FReply OnClearAllClicked();` — Called when the user clicks the "Clear All" button; Clears all tags
- L321 _private prototype_ `FReply OnExpandAllClicked();` — Called when the user clicks the "Expand All" button; Expands the entire tag tree
- L324 _private prototype_ `FReply OnCollapseAllClicked();` — Called when the user clicks the "Collapse All" button; Collapses the entire tag tree
- L331 _private prototype_ `void SetTagTreeItemExpansion(bool bExpand);` — Helper function to set the expansion state of the tree widget @param bExpand If true, expand the entire tree; Otherwise, collapse the entire tree
- L339 _private prototype_ `void SetTagNodeItemExpansion(TSharedPtr<FGameplayTagNode> Node, bool bExpand);` — Helper function to set the expansion state of a specific node @param Node		Node to set the expansion state of @param bExapnd	If true, expand the node; Otherwise, collapse the node
- L342 _private prototype_ `void LoadSettings();` — Load settings for the tags
- L345 _private prototype_ `void MigrateSettings();` — Migrate settings
- L348 _private prototype_ `EVisibility DetermineExpandableUIVisibility() const;` — Helper function to determine the visibility of the expandable UI controls
- L351 _private prototype_ `EVisibility DetermineAddNewSourceExpandableUIVisibility() const;` — Helper function to determine the visibility of the add new source expandable UI controls
- L354 _private prototype_ `EVisibility DetermineAddNewTagWidgetVisibility() const;` — Helper function to determine the visibility of the Add New Tag widget
- L357 _private prototype_ `EVisibility DetermineAddNewSourceWidgetVisibility() const;` — Helper function to determine the visibility of the Add New Tag Source widget
- L360 _private prototype_ `EVisibility DetermineTagTreeControlsVisibility() const;` — Helper function to determine the visibility of the tag tree controls.
- L363 _private prototype_ `EVisibility DetermineAddNewSubTagWidgetVisibility(TSharedPtr<FGameplayTagNode> Node) const;` — Helper function to determine the visibility of the Add New Subtag widget
- L366 _private prototype_ `EVisibility DetermineClearSelectionVisibility() const;` — Helper function to determine the visibility of the Clear Selection button
- L369 _private prototype_ `void LoadTagNodeItemExpansion( TSharedPtr<FGameplayTagNode> Node );` — Recursive load function to go through all tags in the tree and set the expansion
- L372 _private prototype_ `void SetDefaultTagNodeItemExpansion( TSharedPtr<FGameplayTagNode> Node );` — Recursive function to go through all tags in the tree and set the expansion to default
- L375 _private prototype_ `void OnExpansionChanged( TSharedPtr<FGameplayTagNode> InItem, bool bIsExpanded );` — Expansion changed callback
- L378 _private prototype_ `void OnGameplayTagAdded(const FString& TagName, const FString& TagComment, const FName& TagSource);` — Callback for when a new tag is added
- L381 _private prototype_ `FReply OnAddSubtagClicked(TSharedPtr<FGameplayTagNode> InTagNode);` — Callback when the user wants to add a subtag to an existing tag
- L384 _private prototype_ `TSharedRef<SWidget> MakeTagActionsMenu(TSharedPtr<FGameplayTagNode> InTagNode);` — Creates a dropdown menu to provide additional functionality for tags (renaming, deletion, search for references, etc.)
- L387 _private prototype_ `void OnRenameTag(TSharedPtr<FGameplayTagNode> InTagNode);` — Attempts to rename the tag through a dialog box
- L390 _private prototype_ `void OnDeleteTag(TSharedPtr<FGameplayTagNode> InTagNode);` — Attempts to delete the specified tag
- L393 _private prototype_ `void OnAddTag(TSharedPtr<FGameplayTagNode> InTagNode);` — Attempts to add the exact specified tag
- L396 _private prototype_ `void OnRemoveTag(TSharedPtr<FGameplayTagNode> InTagNode);` — Attempts to remove the specified tag, but not the children
- L399 _private prototype_ `void OnSearchForReferences(TSharedPtr<FGameplayTagNode> InTagNode);` — Searches for all references for the selected tag
- L402 _private prototype_ `bool CanSelectTags() const;` — Returns true if the user can select tags from the widget
- L405 _private prototype_ `ECheckBoxState GetAddTagSectionExpansionState() const;` — Determines if the expandable UI that contains the Add New Tag widget should be expanded or collapsed
- L408 _private prototype_ `void OnAddTagSectionExpansionStateChanged(ECheckBoxState NewState);` — Callback for when the state of the expandable UI section changes
- L411 _private prototype_ `ECheckBoxState GetAddSourceSectionExpansionState() const;` — Determines if the expandable UI that contains the Add New Tag Source widget should be expanded or collapsed
- L414 _private prototype_ `void OnAddSourceSectionExpansionStateChanged(ECheckBoxState NewState);` — Callback for when the state of the expandable tag source UI section changes
- L416 _private prototype_ `void SetContainer(FGameplayTagContainer* OriginalContainer, FGameplayTagContainer* EditedContainer, UObject* OwnerObj);`
- L419 _private prototype_ `void OpenRenameGameplayTagDialog(TSharedPtr<FGameplayTagNode> GameplayTagNode) const;` — Opens a dialog window to rename the selected tag
- L422 _private prototype_ `void OnGameplayTagRenamed(FString OldTagName, FString NewTagName);` — Delegate that is fired when a tag is successfully renamed
- L425 _private prototype_ `void GetFilteredGameplayRootTags(const FString& InFilterString, TArray<TSharedPtr<FGameplayTagNode>>& OutNodes) const;` — Populate tag items from the gameplay tags manager.

#### enum `SGameplayTagWidget::ETagFilterResult`  
`enum class ETagFilterResult`  
_L37-41_
- L39 _public enumerator_ `IncludeTag`
- L40 _public enumerator_ `ExcludeTag`

#### struct `SGameplayTagWidget::FEditableGameplayTagContainerDatum`  
`struct FEditableGameplayTagContainerDatum`  
_L85-98_
- desc: Simple struct holding a tag container and its owner for generic re-use of the widget
- L88 _public function_ `FEditableGameplayTagContainerDatum(class UObject* InOwnerObj, struct FGameplayTagContainer* InTagContainer) : TagContainerOwner(InOwnerObj) , TagContainer(InTagContainer)` — Constructor
- L94 _public member_ `TWeakObjectPtr<class UObject> TagContainerOwner;` — Owning UObject of the container being edited
- L97 _public member_ `struct FGameplayTagContainer* TagContainer;` — Tag container to edit

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYTAGSEDITOR_API`
- L36 _delegate_ `DECLARE_DELEGATE( FOnTagChanged ) enum class ETagFilterResult { IncludeTag, ExcludeTag };` — Called when a tag status is changed
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( ETagFilterResult, FOnFilterTag, const TSharedPtr<FGameplayTagNode>&) SLATE_BEGIN_ARGS( SGameplayTagWidget ) : _Padding(2.f) , _Filter() , _NewTagName(TEXT("")) , _ReadOnly( false ) , _TagContainerName( TEXT("") ) , _MultiSelect( true ) , _NewTagControlsInitiallyExpanded( false ) , _PropertyHandle( NULL ) , _GameplayTagUIMode( EGameplayTagUIMode::SelectionMode ) , _MaxHeight(260.0f) , _RestrictedTags( false ) , _ForceHideAddNewTag(false) , _ForceHideAddNewTagSource(false) , _ForceHideTagTreeControls(false) , _BackgroundBrush(FAppStyle::GetBrush("ToolPanel.GroupBorder")) , _TagTreeViewBackgroundBrush(nullptr) {} SLATE_ATTRIBUTE( FMargin, Padding )`
