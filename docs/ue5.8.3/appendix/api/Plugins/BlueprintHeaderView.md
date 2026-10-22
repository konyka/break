# Plugins / BlueprintHeaderView

- module root: `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView`
- headers: 7; symbols: 138
- symbol kinds: class=3, delegate=1, enum=1, enumerator=3, externvar=6, function=5, macro=1, member=29, namespace=5, prototype=77, struct=6, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetTools, BlueprintGraph, CoreUObject, DeveloperSettings, EditorStyle, Engine, InputCore, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Private/HeaderViewClassListItem.h` (Private)


#### struct `FHeaderViewClassListItem`  
`struct FHeaderViewClassListItem : public FHeaderViewListItem`  
_L12-35_
- inherits: `FHeaderViewListItem`
- desc: A header view list item that displays the class declaration
- L16 _public prototype_ `static FHeaderViewListItemPtr Create(TWeakObjectPtr<UBlueprint> InBlueprint);` — Creates a list item for the Header view representing a class declaration for the given blueprint
- L19 _public prototype_ `virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;`
- L22 _protected prototype_ `FString GetConditionalUClassSpecifiers(const UBlueprint* Blueprint) const;`
- L24 _protected prototype_ `FHeaderViewClassListItem(TWeakObjectPtr<UBlueprint> InBlueprint);`
- L26 _protected prototype_ `FString GetRenamedBlueprintPath(const UBlueprint* Blueprint, const FString& NewName) const;`
- L28 _protected prototype_ `bool OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UBlueprint> InBlueprint);`
- L30 _protected prototype_ `void OnRenameTextComitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UBlueprint> InBlueprint);`
- L34 _protected member_ `bool bIsValidName = true;` — Whether this class name is valid C++ (no spaces, special chars, etc)

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ETextCommit`

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Private/HeaderViewFunctionListItem.h` (Private)


#### struct `FHeaderViewFunctionListItem`  
`struct FHeaderViewFunctionListItem : public FHeaderViewListItem`  
_L12-46_
- inherits: `FHeaderViewListItem`
- desc: A header view list item that displays a function declaration
- L15 _public prototype_ `static FHeaderViewListItemPtr Create(const UK2Node_FunctionEntry* FunctionEntry);` — Creates a list item for the Header view representing a function declaration for the given blueprint function
- L18 _public prototype_ `virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;`
- L19 _public prototype_ `virtual void OnMouseButtonDoubleClick(TWeakObjectPtr<UObject> InAsset) override;`
- L23 _protected prototype_ `FHeaderViewFunctionListItem(const UK2Node_FunctionEntry* FunctionEntry);`
- L26 _protected prototype_ `FString GetConditionalUFunctionSpecifiers(const UFunction* SigFunction) const;` — Returns a string containing the specifiers for the UFUNCTION line
- L29 _protected prototype_ `void AppendFunctionParameters(const UFunction* SignatureFunction);` — Adds Function parameters to the RichText and PlainText strings
- L32 _protected prototype_ `bool OnVerifyRenameFunctionTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UBlueprint> WeakBlueprint);` — UI Callback Functions
- L33 _protected prototype_ `bool OnVerifyRenameParameterTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName);`
- L34 _protected prototype_ `void OnRenameFunctionTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName);`
- L35 _protected prototype_ `void OnRenameParameterTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName, FName OldParamName);`
- L36 _protected prototype_ `void JumpToDefinition(TWeakObjectPtr<UBlueprint> WeakBlueprint) const;`
- L39 _protected member_ `FName IllegalName = NAME_None;` — None if the function name is legal C++, else the name of the function
- L42 _protected member_ `FName GraphName = NAME_None;` — Name of the Function Graph this item represents
- L45 _protected member_ `TArray<FName> IllegalParameters;` — Names of any function parameters that are not legal C++

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ETextCommit`

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Private/HeaderViewStructListItem.h` (Private)


#### struct `FHeaderViewStructListItem`  
`struct FHeaderViewStructListItem : public FHeaderViewListItem`  
_L12-33_
- inherits: `FHeaderViewListItem`
- desc: A header view list item that displays the struct declaration
- L16 _public prototype_ `static FHeaderViewListItemPtr Create(TWeakObjectPtr<UUserDefinedStruct> InStruct);` — Creates a list item for the Header view representing a class declaration for the given blueprint
- L19 _public prototype_ `virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;`
- L22 _protected prototype_ `FHeaderViewStructListItem(TWeakObjectPtr<UUserDefinedStruct> InStruct);`
- L24 _protected prototype_ `FString GetRenamedStructPath(const UUserDefinedStruct* Struct, const FString& NewName) const;`
- L26 _protected prototype_ `bool OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UUserDefinedStruct> InStruct);`
- L28 _protected prototype_ `void OnRenameTextComitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UUserDefinedStruct> InStruct);`
- L32 _protected member_ `bool bIsValidName = true;` — Whether this class name is valid C++ (no spaces, special chars, etc)

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ETextCommit`

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Private/HeaderViewVariableListItem.h` (Private)


#### struct `FHeaderViewVariableListItem`  
`struct FHeaderViewVariableListItem : public FHeaderViewListItem`  
_L12-39_
- inherits: `FHeaderViewListItem`
- desc: A header view list item that displays a variable declaration
- L15 _public prototype_ `static FHeaderViewListItemPtr Create(const FBPVariableDescription* VariableDesc, const FProperty& VarProperty);` — Creates a list item for the Header view representing a variable declaration for the given blueprint variable
- L18 _public prototype_ `virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;`
- L22 _protected prototype_ `FHeaderViewVariableListItem(const FBPVariableDescription* VariableDesc, const FProperty& VarProperty);`
- L25 _protected prototype_ `void FormatDelegateDeclaration(const FMulticastDelegateProperty& DelegateProp);` — Formats a line declaring a delegate type and appends it to the item strings
- L28 _protected prototype_ `FString GetConditionalUPropertySpecifiers(const FProperty& VarProperty) const;` — Returns a string containing the specifiers for the UPROPERTY line
- L31 _protected prototype_ `FString GetOwningClassName(const FProperty& VarProperty) const;` — Returns the name of the owning class
- L33 _protected prototype_ `bool OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UObject> WeakAsset);`
- L34 _protected prototype_ `void OnRenameTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UObject> WeakAsset);`
- L38 _protected member_ `FName IllegalName = NAME_None;` — None if the name is legal, else holds the name of the variable

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ETextCommit`

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Private/SBlueprintHeaderView.h` (Private)


#### struct `FHeaderViewListItem`  
`struct FHeaderViewListItem : public TSharedFromThis<FHeaderViewListItem>`  
_L35-89_
- inherits: `TSharedFromThis<FHeaderViewListItem>`
- desc: A base class for List Items in the Header View
- L37 _public prototype_ `virtual ~FHeaderViewListItem() = default;`
- L40 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForItem();` — Creates the widget for this list item
- L43 _public prototype_ `static TSharedPtr<FHeaderViewListItem> Create(FString InRawString, FString InRichText);` — Creates a basic list item containing some text
- L46 _public function_ `const FString& GetRawItemString() const` — Returns the raw item text for copy actions
- L49 _public function_ `virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset)` — Allows the item to add items to the context menu if it is the only item selected
- L52 _public function_ `virtual void OnMouseButtonDoubleClick(TWeakObjectPtr<UObject> InAsset)` — Called when this List Item is double clicked
- L56 _protected function_ `FHeaderViewListItem()` — Empty base constructor hidden from public
- L58 _protected prototype_ `FHeaderViewListItem(FString&& InRawString, FString&& InRichText);`
- L66 _protected prototype_ `static void FormatCommentString(FString InComment, FString& OutRawString, FString& OutRichString);` — Formats a string into a C++ comment @param InComment The string to format as a C++ comment @param OutRawString The string formatted as a C++ comment @param OutRichString The string formatted as a C++ comment with rich text decorators for syntax highlighting
- L72 _protected prototype_ `static FString GetCPPTypenameForProperty(const FProperty* InProperty, bool bIsMemberProperty = false);` — returns a string representing the full C++ typename for the given property, including template params for container types
- L75 _protected prototype_ `static bool IsValidCPPIdentifier(const FString& InIdentifier);` — Checks whether a string is a valid C++ identifier
- L78 _protected prototype_ `static const FText& GetErrorTextFromValidatorResult(EValidatorResult Result);` — Returns the correct Error text for a Validator Result
- L82 _protected member_ `FString RichTextString;` — A rich text representation of the item, including syntax highlighting and errors
- L85 _protected member_ `FString RawItemString;` — A raw string representation of the item, used for copying the item
- L88 _protected member_ `static const FText InvalidCPPIdentifierErrorText;` — Validation Error text for when a new name is not a valid C++ Identifier

#### class `SBlueprintHeaderView`  
`class SBlueprintHeaderView : public SCompoundWidget, public FNotifyHook`  
_L93-178_
- inherits: `SCompoundWidget,FNotifyHook`
- L96 _public function_ `SLATE_BEGIN_ARGS(SBlueprintHeaderView)`
- L100 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L104 _public prototype_ `~SBlueprintHeaderView();`
- L107 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L112 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — Handles when the settings have changed, saves to config
- L116 _public prototype_ `void OnAssetSelected(const FAssetData& SelectedAsset);` — Callback for class picker menu selecting a blueprint asset
- L119 _private prototype_ `FText GetClassPickerText() const;` — Gets the text for the class picker combo button
- L122 _private prototype_ `TSharedRef<SWidget> GetClassPickerMenuContent();` — Constructs a Blueprint Class picker menu widget
- L125 _private prototype_ `TSharedRef<SWidget> GetSettingsMenuContent();` — Constructs a DetailsView widget for the settings menu
- L128 _private prototype_ `TSharedRef<ITableRow> GenerateRowForItem(FHeaderViewListItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generates a row for a given List Item
- L131 _private prototype_ `void RepopulateListView();` — Clears the list and repopulates it with info for the selected Blueprint
- L134 _private prototype_ `void PopulateFunctionItems(const UBlueprint* Blueprint);` — Adds items to the list view representing all functions present in the given blueprint
- L137 _private prototype_ `void GatherFunctionGraphs(const UBlueprint* Blueprint, TArray<const UEdGraph*>& OutFunctionGraphs);` — Gathers all function graphs from the blueprint and sorts them according to the selected method from config
- L140 _private prototype_ `void PopulateVariableItems(const UStruct* Struct);` — Adds items to the list view representing all variables present in the given asset
- L141 _private prototype_ `void AddVariableItems(TArray<const FProperty*> VarProperties);`
- L144 _private prototype_ `void SortPropertiesForPadding(TArray<const FProperty*>& InOutProperties);` — Sorts an array of properties to optimize for minimal C++ struct padding
- L147 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Creates a context menu for the list view
- L150 _private prototype_ `void OnItemDoubleClicked(FHeaderViewListItemPtr Item);` — Called when a List Item is double clicked
- L153 _private prototype_ `void OnBlueprintChanged(UBlueprint* InBlueprint);` — Callback for when the selected asset is modified
- L154 _private prototype_ `void OnStructChanged(UUserDefinedStruct* InStruct);`
- L157 _private prototype_ `void OnCopy() const;` — UI Command Functions
- L158 _private prototype_ `bool CanCopy() const;`
- L159 _private prototype_ `void OnSelectAll();`
- L160 _private prototype_ `FReply BrowseToAssetClicked() const;`
- L161 _private prototype_ `FReply OpenAssetEditorClicked() const;`
- L164 _private member_ `TSharedPtr<FUICommandList> CommandList;` — List of UI Commands for this scope
- L167 _private member_ `TWeakObjectPtr<UBlueprint> SelectedBlueprint;` — The asset currently being displayed by the header view
- L168 _private member_ `TWeakObjectPtr<UUserDefinedStruct> SelectedStruct;`
- L171 _private member_ `TSharedPtr<SComboButton> ClassPickerComboButton;` — Reference to the Class Picker combo button widget
- L174 _private member_ `TSharedPtr<SListView<FHeaderViewListItemPtr>> ListView;` — Reference to the ListView Widget
- L177 _private member_ `TArray<FHeaderViewListItemPtr> ListItems;` — List Items source

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintHeaderView, Log, All) namespace HeaderViewSyntaxDecorators { extern const FString CommentDecorator; extern const FString ErrorDecorator; extern const FString IdentifierDecorator; extern const FString KeywordDecorator; extern const FString MacroDecorator; extern const FString TypenameDecorator; } struct FHeaderViewListItem : public TSharedFromThis<FHeaderViewListItem> { virtual ~FHeaderViewListItem() = default; TSharedRef<SWidget> GenerateWidgetForItem(); static TSharedPtr<FHeaderViewListItem> Create(FString InRawString, FString InRichText); const FString& GetRawItemString() const { return RawItemString; } virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) {} virtual void OnMouseButtonDoubleClick(TWeakObjectPtr<UObject> InAsset) {}; protected: FHeaderViewListItem() {}; FHeaderViewListItem(FString&& InRawString, FString&& InRichText); /**`
- L24 _namespace_ `namespace HeaderViewSyntaxDecorators`
- L26 _externvar_ `extern const FString CommentDecorator;` (scope `HeaderViewSyntaxDecorators`)
- L27 _externvar_ `extern const FString ErrorDecorator;` (scope `HeaderViewSyntaxDecorators`)
- L28 _externvar_ `extern const FString IdentifierDecorator;` (scope `HeaderViewSyntaxDecorators`)
- L29 _externvar_ `extern const FString KeywordDecorator;` (scope `HeaderViewSyntaxDecorators`)
- L30 _externvar_ `extern const FString MacroDecorator;` (scope `HeaderViewSyntaxDecorators`)
- L31 _externvar_ `extern const FString TypenameDecorator;` (scope `HeaderViewSyntaxDecorators`)
- L91 _typedef_ `using FHeaderViewListItemPtr = TSharedPtr<FHeaderViewListItem>;`

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Public/BlueprintHeaderView.h` (Public)


#### class `FBlueprintHeaderViewModule`  
`class FBlueprintHeaderViewModule : public IModuleInterface`  
_L16-48_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `static bool IsClassHeaderViewSupported(const UClass* InClass);` — Returns whether the Header View supports the given class
- L27 _public prototype_ `static void OpenHeaderViewForAsset(FAssetData InAssetData);`
- L29 _private prototype_ `void SetupAssetEditorMenuExtender();`
- L31 _private prototype_ `void SetupContentBrowserContextMenuExtender();`
- L33 _private prototype_ `static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);`
- L37 _public member_ `static FTextBlockStyle HeaderViewTextStyle;` — Text style for the Header View Output
- L40 _public member_ `static FTableRowStyle HeaderViewTableRowStyle;` — TableRow style for the Header View Output
- L43 _public member_ `static TSharedPtr<FSlateStyleSet> HeaderViewStyleSet;` — Style set for the header view
- L47 _private member_ `FDelegateHandle ContentBrowserExtenderDelegateHandle;` — Handle to our delegate so we can remove it at module shutdown

### `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Public/BlueprintHeaderViewSettings.h` (Public)


#### enum `EHeaderViewSortMethod`  
`enum class EHeaderViewSortMethod : uint8`  
_L11-21_
- reflection: `UENUM()`
- L14 _public enumerator_ `None` — Properties will stay in the same order they were in the Blueprint class.
- L17 _public enumerator_ `SortByAccessSpecifier` — Properties will be grouped together by Access Specifiers, in order of visibility (public, protected, private).
- L20 _public enumerator_ `SortForOptimalPadding` — Properties will be sorted to minimize padding in compiled class layout.

#### struct `FHeaderViewSyntaxColors`  
`struct FHeaderViewSyntaxColors`  
_L24-49_
- reflection: `USTRUCT(NotBlueprintable)`
- L28 _public prototype_ `FHeaderViewSyntaxColors();`
- L32 _public member_ `FLinearColor Comment;` — `UPROPERTY(config, EditAnywhere, Category="Settings")`
- L35 _public member_ `FLinearColor Error;` — `UPROPERTY(config, EditAnywhere, Category="Settings")`
- L38 _public member_ `FLinearColor Macro;` — `UPROPERTY(config, EditAnywhere, Category="Settings")`
- L41 _public member_ `FLinearColor Typename;` — `UPROPERTY(config, EditAnywhere, Category="Settings")`
- L44 _public member_ `FLinearColor Identifier;` — `UPROPERTY(config, EditAnywhere, Category="Settings")`
- L47 _public member_ `FLinearColor Keyword;` — `UPROPERTY(config, EditAnywhere, Category="Settings")`

#### class `UBlueprintHeaderViewSettings`  
`class UBlueprintHeaderViewSettings : public UDeveloperSettings`  
_L53-88_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Settings for the Blueprint Header View Plugin
- L58 _public prototype_ `UBlueprintHeaderViewSettings();`
- L61 _public prototype_ `virtual FName GetCategoryName() const override;`
- L62 _public prototype_ `virtual FText GetSectionText() const override;`
- L63 _public prototype_ `virtual FName GetSectionName() const override;`
- L68 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L75 _public member_ `FHeaderViewSyntaxColors SyntaxColors;` — `UPROPERTY(config, EditAnywhere, Category="Settings|Style")` — Syntax Highlighting colors for Blueprint Header View output
- L79 _public member_ `FLinearColor SelectionColor = FLinearColor(0.3f, 0.3f, 1.0f, 1.0f);` — `UPROPERTY(config, EditAnywhere, Category="Settings|Style")` — Highlight color for selected items in the Blueprint Header View output
- L83 _public member_ `int32 FontSize = 9;` — `UPROPERTY(config, EditAnywhere, Category="Settings|Style", meta=(ClampMin=6, ClampMax=72))` — Font Size for the Blueprint Header View output
- L87 _public member_ `EHeaderViewSortMethod SortMethod = EHeaderViewSortMethod::None;` — `UPROPERTY(config, EditAnywhere, Category="Settings")` — Sorting Method for Header View Functions and Properties

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BLUEPRINTHEADERVIEW_API`
