# Plugins / NamingTokensUI

- module root: `Plugins/Developer/NamingTokens/Source/NamingTokensUI`
- headers: 5; symbols: 227
- symbol kinds: class=7, delegate=3, function=19, member=87, prototype=106, struct=3, typedef=2
- PrivateDependencyModuleNames: Engine, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, NamingTokens, UMG, UnrealEd

### `Plugins/Developer/NamingTokens/Source/NamingTokensUI/Private/NamingTokensStringSyntaxHighlighterMarshaller.h` (Private)


#### class `FNamingTokensStringSyntaxHighlighterMarshaller`  
`class FNamingTokensStringSyntaxHighlighterMarshaller : public FSyntaxHighlighterTextLayoutMarshaller`  
_L18-71_
- inherits: `FSyntaxHighlighterTextLayoutMarshaller`
- desc: Get/set the raw text to/from a text layout, and also inject syntax highlighting for our rich-text markup
- L39 _public prototype_ `static TSharedRef<FNamingTokensStringSyntaxHighlighterMarshaller> Create(const FSyntaxTextStyle& InSyntaxTextStyle);`
- L41 _public prototype_ `virtual ~FNamingTokensStringSyntaxHighlighterMarshaller() override = default;`
- L44 _public function_ `void SetNormalStyle(const FTextBlockStyle& InStyle)` — Set the normal style of our syntax.
- L50 _public function_ `void SetArgumentStyle(const FTextBlockStyle& InStyle)` — Set the argument style for our syntax.
- L56 _public prototype_ `static const FTextBlockStyle& GetDefaultNormalStyle();` — Retrieve the default normal style used.
- L59 _public prototype_ `static const FTextBlockStyle& GetDefaultArgumentStyle();` — Retrieve the default argument style used.
- L65 _protected prototype_ `virtual void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<ISyntaxTokenizer::FTokenizedLine> TokenizedLines) override;`
- L67 _protected prototype_ `FNamingTokensStringSyntaxHighlighterMarshaller(TSharedPtr<ISyntaxTokenizer> InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);`
- L70 _protected member_ `FSyntaxTextStyle SyntaxTextStyle;` — Styles used to display the text

#### struct `FNamingTokensStringSyntaxHighlighterMarshaller::FSyntaxTextStyle`  
`struct FSyntaxTextStyle`  
_L21-37_
- L23 _public function_ `FSyntaxTextStyle() : NormalTextStyle(GetDefaultNormalStyle()) , ArgumentTextStyle(GetDefaultArgumentStyle())`
- L29 _public function_ `FSyntaxTextStyle(const FTextBlockStyle& InNormalTextStyle, const FTextBlockStyle& InArgumentTextStyle) : NormalTextStyle(InNormalTextStyle) , ArgumentTextStyle(InArgumentTextStyle)`
- L35 _public member_ `FTextBlockStyle NormalTextStyle;`
- L36 _public member_ `FTextBlockStyle ArgumentTextStyle;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensUI/Private/NamingTokensUIModule.h` (Private)


#### class `FNamingTokensUIModule`  
`class FNamingTokensUIModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensUI/Private/SNamingTokensDataTreeView.h` (Private)


#### struct `FNamingTokenDataTreeItem`  
`struct FNamingTokenDataTreeItem : TSharedFromThis<FNamingTokenDataTreeItem>`  
_L14-105_
- inherits: `TSharedFromThis<FNamingTokenDataTreeItem>`
- desc: Represents naming token items in our tree view.
- L17 _public member_ `TSharedPtr<FNamingTokenData> NamingTokenData;` — The token data, null on namespace entries.
- L20 _public member_ `FString Namespace;` — The namespace for this token. May be set regardless of entry type.
- L22 _public member_ `FText NamespaceDisplayName;` — The friendly display name for the namespace.
- L25 _public member_ `TArray<TSharedPtr<FNamingTokenDataTreeItem>> ChildItems;` — Children of a namespace.
- L27 _public member_ `TWeakPtr<FNamingTokenDataTreeItem> Parent;` — The parent owning this entry.
- L30 _public member_ `int32 ItemIndex = INDEX_NONE;` — The flattened item index in the tree.
- L33 _public member_ `bool bIsGlobal = false;` — If this entry is globally registered in the naming tokens subsystem.
- L35 _public function_ `bool ShouldItemBeExpanded() const`
- L38 _public function_ `float MatchesFilter(const FString& FilterText, bool bIsExactNamespaceMatch = false) const` — Checks if this item matches a filter returning a simple percentage score on the match.
- L84 _public function_ `bool IsNamespace() const` — True iff this is considered a namespace entry.
- L90 _public function_ `FString ToString(bool bFullyQualified) const` — Convert the item to the best text representation.
- L101 _public function_ `bool operator==(const FNamingTokenDataTreeItem& Other) const`

#### class `SNamingTokenDataTreeView`  
`class SNamingTokenDataTreeView : public STreeView<FNamingTokenDataTreeItemPtr>`  
_L112-130_
- inherits: `STreeView<FNamingTokenDataTreeItemPtr>`
- desc: A tree view for naming token filtering.
- L115 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<class SNamingTokenDataTreeViewWidget>& InTreeViewWidget);`
- L118 _public prototype_ `void SetExpansionStateFromItems(const TArray<FNamingTokenDataTreeItemPtr>& InTreeItems);` — Recursively set expansion state of tree view to match items.
- L121 _public function_ `const TWeakPtr<SNamingTokenDataTreeViewWidget>& GetOwningTreeViewWidget() const` — Pointer to our owning widget.
- L124 _public function_ `virtual bool HasKeyboardFocus() const override`
- L125 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L129 _private member_ `TWeakPtr<SNamingTokenDataTreeViewWidget> OwningTreeViewWidget;` — The owning tree view widget.

#### class `SNamingTokenDataTreeViewRow`  
`class SNamingTokenDataTreeViewRow final : public SMultiColumnTableRow<FNamingTokenDataTreeItemPtr>`  
_L135-156_
- inherits: `SMultiColumnTableRow<FNamingTokenDataTreeItemPtr>`
- desc: Each row of the tree view.
- L138 _public function_ `SLATE_BEGIN_ARGS(SNamingTokenDataTreeViewRow)`
- L141 _public prototype_ `SLATE_ARGUMENT(FNamingTokenDataTreeItemPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);` — The list item for this row.
- L147 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L151 _private prototype_ `static const FEditableTextBoxStyle& GetCustomEditableTextBoxStyle();`
- L155 _private member_ `TWeakPtr<FNamingTokenDataTreeItem> Item;` — The item associated with this row of data.

#### class `SNamingTokenDataTreeViewWidget`  
`class SNamingTokenDataTreeViewWidget final : public SCompoundWidget`  
_L161-281_
- inherits: `SCompoundWidget`
- desc: Widget for displaying namespaces and tokens to choose from.
- L163 _private typedef_ `using FOnSelectionChanged = STreeView<FNamingTokenDataTreeItemPtr>::FOnSelectionChanged;`
- L165 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, FNamingTokenDataTreeItemPtr);`
- L168 _public function_ `SLATE_BEGIN_ARGS(SNamingTokenDataTreeViewWidget)`
- L170 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FSimpleDelegate, OnFocused) SLATE_ARGUMENT(FNamingTokenFilterArgs, FilterArgs) SLATE_ARGUMENT(TArray<FString>, NamespacePriority) SLATE_END_ARGS() virtual ~SNamingTokenDataTreeViewWidget() override;` — If a selection is changed, such as arrow keys or a single click.
- L183 _public prototype_ `void Construct(const FArguments& InArgs);`
- L186 _public prototype_ `void PopulateTreeItems(const FNamingTokenFilterArgs& InFilterArgs);` — Populate all possible tree items
- L189 _public prototype_ `void FilterTreeItems(const FString& InFilterText);` — Filter down to specific tokens and namespaces.
- L195 _public prototype_ `bool ForwardKeyEventForNavigation(const FKeyEvent& InKeyEvent);` — Provide a key event from the user to determine a navigation path, highlighting an item. @return True if the key event contained a recognized navigation key.
- L198 _public prototype_ `FNamingTokenDataTreeItemPtr GetSelectedItem() const;` — Retrieve the currently selected item.
- L201 _public prototype_ `FNamingTokenDataTreeItemPtr GetItemFromIndex(int32 InIndex) const;` — Retrieve an item given its absolute index.
- L204 _public function_ `const FString& GetTokenFilterText() const` — Get the token filter text applied.
- L207 _public function_ `const FString& GetNamespaceFilterText() const` — Get the namespace filter text applied.
- L210 _public prototype_ `void NotifyFocusReceived();` — Informs us we're receiving focus, such as from a child of the treeview.
- L213 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L218 _private prototype_ `FNamingTokenDataTreeItemPtr GetItemFromIndex(int32 InIndex, const TArray<FNamingTokenDataTreeItemPtr>& InItems) const;` — Find an item given its index.
- L221 _private prototype_ `void SetItemFromIndex(int32 InIndex);` — Set the currently selected item given an absolute index.
- L224 _private prototype_ `void ClearCurrentSelection();` — Clears the currently selected item.
- L227 _private prototype_ `void FinalizeSelection(FNamingTokenDataTreeItemPtr SelectedItem);` — Officially complete and report the selection. Called from tab or double-click.
- L230 _public function_ `static FName PrimaryColumnName()`
- L234 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForTree(FNamingTokenDataTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called by STreeView for each row being generated.
- L237 _private prototype_ `void OnGetChildrenForTree(FNamingTokenDataTreeItemPtr InParent, TArray<FNamingTokenDataTreeItemPtr>& OutChildren);` — Called by STreeView to get child items for the specified parent item.
- L240 _private prototype_ `void OnItemExpansionChanged(FNamingTokenDataTreeItemPtr TreeItem, bool bIsExpanded) const;` — Called when an item in the tree has been collapsed or expanded.
- L243 _private prototype_ `void OnTreeViewItemSelectionChanged(FNamingTokenDataTreeItemPtr SelectedItem, ESelectInfo::Type SelectInfo);` — Called when the tree view changes selection.
- L246 _private prototype_ `void OnTreeViewItemDoubleClicked(FNamingTokenDataTreeItemPtr SelectedItem);` — Called when an item in the tree view is double-clicked.
- L250 _private member_ `TSharedPtr<SNamingTokenDataTreeView> TreeView;` — Our tree view widget.
- L253 _private member_ `TArray<FNamingTokenDataTreeItemPtr> RootTreeItems;` — The top most items on the tree view without a filter.
- L256 _private member_ `TArray<FNamingTokenDataTreeItemPtr> FilteredRootTreeItems;` — Items filtered in a search.
- L259 _private member_ `TArray<FString> NamespacePriority;` — Order to display namespaces.
- L262 _private member_ `FString LastFilterText;` — The last filter applied.
- L265 _private member_ `FString TokenFilterText;` — Last token filter text applied.
- L268 _private member_ `FString NamespaceFilterText;` — Last namespace filter text applied.
- L271 _private member_ `int32 CurrentSelectionIndex = 0;` — Index of tree item currently selected.
- L274 _private member_ `FOnSelectionChanged ItemSelectionChangedDelegate;` — Delegate for when selection changes.
- L277 _private member_ `FOnItemSelected ItemSelectedDelegate;` — Delegate for when an item is fully selected.
- L280 _private member_ `FSimpleDelegate OnFocusedDelegate;` — Delegate if we have received focus.

#### Free symbols / members of external scopes

- L107 _typedef_ `typedef TSharedPtr<FNamingTokenDataTreeItem> FNamingTokenDataTreeItemPtr;`
- L165 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, FNamingTokenDataTreeItemPtr);`

### `Plugins/Developer/NamingTokens/Source/NamingTokensUI/Public/NamingTokensEditableText.h` (Public)


#### class `UNamingTokensEditableText`  
`class UNamingTokensEditableText : public UMultiLineEditableText`  
_L17-189_
- reflection: `UCLASS(MinimalAPI, Config = NamingTokens, DefaultConfig, ClassGroup = UI, PrioritizeCategories = ("NamingTokens", "Content", "Appearance", "Behavior"), meta = (Category = "NamingTokens UI", DisplayName = "Naming Tokens Editable Text Box"))`
- inherits: `UMultiLineEditableText`
- desc: Editable text for displaying tokenized strings in either their unevaluated or resolved form.
- L22 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreEvaluateNamingTokens);`
- L24 _public prototype_ `UNamingTokensEditableText();`
- L28 _public prototype_ `const FText& GetResolvedText() const;` — `UFUNCTION(BlueprintCallable, Category=NamingTokens)` — Retrieve the evaluated text.
- L32 _public prototype_ `const FText& GetTokenizedText() const;` — `UFUNCTION(BlueprintCallable, Category=NamingTokens)` — Retrieve the raw token text.
- L36 _public prototype_ `void SetWidgetArgumentStyle(const FTextBlockStyle& InWidgetStyle);` — `UFUNCTION(BlueprintSetter)` — Sets the argument style to use for the widget.
- L40 _public prototype_ `void SetBackgroundColor(const FSlateColor& InColor);` — `UFUNCTION(BlueprintSetter)` — Set the background color.
- L44 _public prototype_ `void SetContexts(const TArray<UObject*>& InContexts);` — `UFUNCTION(BlueprintSetter)` — Set the contexts to use during evaluation.
- L48 _public prototype_ `void SetDisplayTokenIcon(bool bValue);` — `UFUNCTION(BlueprintSetter)` — Set whether the token icon is displayed.
- L52 _public prototype_ `void SetDisplayErrorMessage(bool bValue);` — `UFUNCTION(BlueprintSetter)` — Set whether error messages are displayed for token formatting.
- L56 _public prototype_ `void SetDisplayBorderImage(bool bValue);` — `UFUNCTION(BlueprintSetter)` — Set the background color of the border image.
- L60 _public prototype_ `bool GetDisplayTokenIcon() const;` — `UFUNCTION(BlueprintGetter)` — If the token icon should be displayed.
- L64 _public prototype_ `bool GetDisplayErrorMessage() const;` — `UFUNCTION(BlueprintGetter)` — If the error icon should be displayed.
- L68 _public prototype_ `bool GetDisplayBorderImage() const;` — `UFUNCTION(BlueprintGetter)` — If the border image should be displayed.
- L72 _public prototype_ `void SetCanDisplayResolvedText(bool bValue);` — `UFUNCTION(BlueprintSetter)` — Set whether we can display resolved text or not.
- L76 _public prototype_ `bool GetCanDisplayResolvedText() const;` — `UFUNCTION(BlueprintGetter)` — Get if we can display resolved text.
- L80 _public prototype_ `void SetShowUnknownTokenWarning(bool bValue);` — `UFUNCTION(BlueprintSetter)` — Set whether the widget should warn when token(s) in the tokenized text are not recognized.
- L84 _public prototype_ `bool GetShowUnknownTokenWarning() const;` — `UFUNCTION(BlueprintGetter)` — Get whether the widget warns when token(s) in the tokenized text are not recognized.
- L88 _public prototype_ `void SetShowUnsetTokenWarning(bool bValue);` — `UFUNCTION(BlueprintSetter)` — Set whether the widget should warn when token(s) in the tokenized text evaluate to an empty value.
- L92 _public prototype_ `bool GetShowUnsetTokenWarning() const;` — `UFUNCTION(BlueprintGetter)` — Get whether the widget warns when token(s) in the tokenized text evaluate to an empty value.
- L95 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L100 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L101 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L105 _protected prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L110 _private prototype_ `bool CanDisplayResolvedTextAttribute() const;` — Calculate if we're allowed to display the resolved text.
- L113 _private prototype_ `void OnPreEvaluateNamingTokensCallback();` — Callback when we are evaluating tokens.
- L118 _protected member_ `FNamingTokenFilterArgs FilterArgs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NamingTokens)` — Set naming token filter args to use during token evaluation.
- L122 _protected member_ `TArray<FString> NamespaceSuggestionPriority;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Behavior, meta = (EditCondition="bEnableSuggestionDropdown", EditConditionHides, DisplayAfter=bFullyQualifyFilteredNamespaces))` — A list prioritizing namespaces to show first in the dropdown.
- L126 _protected member_ `bool bEnableSuggestionDropdown = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Behavior)` — If the dropdown suggestion box should be enabled.
- L130 _protected member_ `bool bFullyQualifyFilteredNamespaces = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Behavior, meta = (EditCondition="bEnableSuggestionDropdown", EditConditionHides))` — If namespaces included in the FilterArgs.AdditionalNamespacesToInclude should autocomplete. If false, only the token is inserted.
- L134 _protected member_ `bool bIsMultiline = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — If this text box is configured for multiline.
- L138 _protected member_ `bool bDisplayTokenIcon = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetDisplayTokenIcon, BlueprintGetter=GetDisplayTokenIcon, Category=Appearance)` — Display the token icon in the text box.
- L142 _protected member_ `bool bDisplayErrorMessage = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetDisplayErrorMessage, BlueprintGetter=GetDisplayErrorMessage, Category=Appearance)` — Display an error message when tokens aren't properly formatted.
- L146 _protected member_ `bool bDisplayBorderImage = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetDisplayBorderImage, BlueprintGetter=GetDisplayBorderImage, Category=Appearance)` — Display the border image.
- L150 _protected member_ `FTextBlockStyle ArgumentStyle;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetWidgetArgumentStyle, Category=Appearance)` — The font to apply to the non-resolved tokens.
- L154 _protected member_ `FSlateColor BackgroundColor;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetBackgroundColor, Category=Appearance)` — Set the background color of the border image.
- L158 _protected member_ `bool bCanDisplayResolvedText = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetCanDisplayResolvedText, BlueprintGetter=GetCanDisplayResolvedText, Category=Appearance)` — If the resolved text can be displayed.
- L162 _protected member_ `bool bShowUnknownTokenWarning = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetShowUnknownTokenWarning, BlueprintGetter=GetShowUnknownTokenWarning, Category=Appearance)` — Display a warning when token(s) in the tokenized text are not recognized (unknown tokens).
- L166 _protected member_ `bool bShowUnsetTokenWarning = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, BlueprintSetter=SetShowUnsetTokenWarning, BlueprintGetter=GetShowUnsetTokenWarning, Category=Appearance)` — Display a warning when token(s) in the tokenized text evaluate to an empty value (unset tokens).
- L171 _protected member_ `bool bDisplayResolvedTextInDesigner = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Appearance, meta = (EditCondition="bCanDisplayResolvedText", EditConditionHides))` — If the resolved text should display while designing in the UMG window. If false, only the tokenized text will be displayed in the UMG designer.
- L177 _public member_ `FOnPreEvaluateNamingTokens OnPreEvaluateNamingTokens;` — `UPROPERTY(BlueprintAssignable, Category="NamingTokens|Event")` — Called before naming token evaluation.
- L181 _private member_ `TSharedPtr<SNamingTokensEditableTextBox> MyNamingTokensEditableText;` — The editable text slate widget.
- L184 _private member_ `TSharedPtr<FEditableTextBoxStyle> EditableTextBoxStyle;` — The editable text box style we use.
- L188 _private member_ `TArray<TObjectPtr<UObject>> Contexts;` — `UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetContexts, Category=NamingTokens, meta=(AllowPrivateAccess))` — Contexts to include during our evaluation.

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreEvaluateNamingTokens);`

### `Plugins/Developer/NamingTokens/Source/NamingTokensUI/Public/SNamingTokensEditableTextBox.h` (Public)


#### class `SNamingTokensEditableTextBox`  
`class SNamingTokensEditableTextBox : public SCompoundWidget`  
_L27-391_
- inherits: `SCompoundWidget`
- desc: An editable text box for displaying tokenized strings in either their unevaluated or resolved form.
- L30 _public function_ `SLATE_BEGIN_ARGS(SNamingTokensEditableTextBox) : _Style(nullptr) , _ArgumentStyle(nullptr) , _ShouldEvaluateTokens(true) , _EvaluationFrequency(0.0f) , _AllowMultiLine(false) , _IsReadOnly(false) , _CanDisplayResolvedText(true) , _DisplayTokenIcon(true) , _DisplayErrorMessage(true) , _DisplayBorderImage(true) , _TextBoxPadding() , _SupportInlineEdit(false) , _EnableSuggestionDropdown(true) , _FullyQualifyGlobalTokenSuggestions(false) , _FullyQualifyFilteredNamespaces(false) , _ShowUnknownTokenWarning(true) , _ShowUnsetTokenWarning(false)`
- L50 _public prototype_ `SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, Style) SLATE_STYLE_ARGUMENT(FTextBlockStyle, ArgumentStyle) SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, ResolvedText) SLATE_ATTRIBUTE(TConstArrayView<FString>, ValidArguments) SLATE_ARGUMENT(TSharedPtr<ITextLayoutMarshaller>, Marshaller) SLATE_ATTRIBUTE(bool, ShouldEvaluateTokens) SLATE_ATTRIBUTE(float, EvaluationFrequency) SLATE_ATTRIBUTE(bool, AllowMultiLine) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_ATTRIBUTE(bool, CanDisplayResolvedText) SLATE_ATTRIBUTE(bool, DisplayTokenIcon) SLATE_ATTRIBUTE(bool, DisplayErrorMessage) SLATE_ATTRIBUTE(bool, DisplayBorderImage)` — The styling of the textbox.
- L148 _public function_ `TSharedPtr<SMultiLineEditableText> GetEditableText() const` — Retrieve the editable text widget.
- L151 _public prototype_ `void SetTokenizedText(const FText& InText);` — Set the current tokenized text.
- L154 _public function_ `const TAttribute<FText>& GetBoundText() const` — Return the bound text attribute.
- L157 _public prototype_ `const FText& GetResolvedText() const;` — Retrieve the resolved text.
- L160 _public prototype_ `const FText& GetTokenizedText() const;` — Retrieve the raw tokenized text.
- L163 _public prototype_ `void SetNormalStyle(const FEditableTextBoxStyle* InNormalStyle);` — Sets the style to use.
- L166 _public prototype_ `void SetArgumentStyle(const FTextBlockStyle* InArgumentStyle);` — Sets the argument style to use.
- L169 _public prototype_ `void SetSupportInlineEdit(bool bInSupportInlineEdit);` — If the textbox should look and behave like an inline editable textbox
- L172 _public prototype_ `void SetEnableSuggestionDropdown(bool bInEnableSuggestionDropdown);` — If the suggestion box should be enabled.
- L175 _public prototype_ `void SetFilterArgs(const FNamingTokenFilterArgs& InFilterArgs);` — Provide filter args to use during evaluation.
- L178 _public prototype_ `void SetFullyQualifyFilteredNamespaces(bool bNewValue);` — Set whether namespaces under FilterArgs.AdditionalNamespacesToInclude should autocomplete.
- L181 _public prototype_ `void SetNamespaceSuggestionPriority(const TArray<FString>& InNamespaces);` — Set the namespace priority to use when sorting dropdown suggestions.
- L184 _public prototype_ `void SetContexts(const TArray<UObject*>& InContexts);` — Provide contexts to naming token evaluation.
- L187 _public prototype_ `void SetShowUnknownTokenWarning(bool bNewValue);` — Set whether the widget should warn when token(s) in the tokenized text are not recognized.
- L190 _public prototype_ `void SetShowUnsetTokenWarning(bool bNewValue);` — Set whether the widget should warn when token(s) in the tokenized text evaluate to an empty value.
- L193 _public prototype_ `void EvaluateNamingTokens();` — Evaluate the token text and update the resolved text.
- L196 _public prototype_ `void EnterEditingMode();` — If inline editing is supported, gives focus to the editable text, and sets the visibility and display options to resemble an editable textbox
- L199 _public prototype_ `void ExitEditingMode();` — If inline editing is supported, sets the visibility and display options to resemble a read-only textblock
- L203 _private prototype_ `FText GetText() const;` — @return Text contents based on current state
- L205 _private prototype_ `const FSlateBrush* GetBorderImage() const;`
- L207 _private prototype_ `virtual FSlateColor GetBorderBackgroundColor() const;` — The background color for the border.
- L208 _private prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L210 _private prototype_ `void SetError(const FText& InError) const;`
- L212 _private prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L213 _private prototype_ `virtual bool HasKeyboardFocus() const override;`
- L214 _private prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L215 _private prototype_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;`
- L216 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L218 _private prototype_ `bool ValidateTokenizedText(const FText& InTokenizedText);`
- L219 _private prototype_ `bool ValidateTokenBraces(const FText& InTokenizedText, FText& OutError);`
- L220 _private prototype_ `bool ValidateTokenArgs(const FText& InTokenizedText, FText& OutError);`
- L222 _private prototype_ `bool ParseArgs(const FString& InTokenizedTextString, TArray<FString>& OutArgs);`
- L224 _private prototype_ `void OnEditableTextChanged(const FText& InTokenizedText);`
- L225 _private prototype_ `void OnEditableTextCommitted(const FText& InTokenizedText, ETextCommit::Type InCommitType);`
- L228 _private prototype_ `void UpdateFilters() const;` — Check for type text and update filters if needed.
- L243 _private prototype_ `void OpenOrCloseSuggestionDropdown() const;` — Opens or closes the dropdown based on cursor status.
- L245 _private prototype_ `void OpenOrCloseSuggestionDropdownNextTick() const;` — Opens or closes the suggestion drop down on the next tick, providing a request hasn't already been made.
- L248 _private prototype_ `void OpenSuggestionDropdown() const;` — Trigger the suggestion process.
- L250 _private prototype_ `void CloseSuggestionDropdown() const;` — Close the suggestion window.
- L253 _private prototype_ `TSharedPtr<FCursorTokenData> GetCurrentCursorTokenData() const;` — Retrieve information about the current token where the cursor is.
- L256 _private prototype_ `TSharedRef<SWidget> OnGetDropdownContent();` — Create the dropdown content for filtering naming tokens.
- L259 _private prototype_ `FReply OnEditableTextKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) const;` — When our editable text has a character typed.
- L262 _private prototype_ `FReply OnEditableTextKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) const;` — When editable text has a key pressed.
- L265 _private prototype_ `void OnEditableTextCursorMoved(const FTextLocation& NewCursorPosition);` — User has moved the text cursor.
- L268 _private prototype_ `void OnSuggestionSelected(TSharedPtr<FNamingTokenDataTreeItem> SelectedItem) const;` — When a dropdown suggestion has been selected.
- L271 _private prototype_ `void OnSuggestionCommitted(TSharedPtr<FNamingTokenDataTreeItem> SelectedItem);` — Called when the user commits a suggestion (single click, double click, Enter, or Tab).
- L274 _private prototype_ `void OnSuggestionDropdownReceivedFocus() const;` — Called if the suggestion box has received focus.
- L277 _private prototype_ `FText GetUnresolvedTokenWarningTooltip() const;` — Builds the tooltip shown on the unresolved token warning icon
- L281 _private member_ `FNamingTokenFilterArgs NamingTokenFilterArgs;` — Filter args to use during evaluation.
- L284 _private member_ `TArray<TObjectPtr<UObject>> NamingTokenContexts;` — Contexts to provide to evaluation.
- L287 _private member_ `TArray<FString> NamespaceSuggestionPriority;` — A list prioritizing namespaces to show first in the dropdown.
- L290 _private member_ `TSharedPtr<SMultiLineEditableText> EditableText;` — Editable text widget.
- L293 _private member_ `TSharedPtr<SMenuAnchor> DropdownAnchor;` — The dropdown filter UI anchor.
- L296 _private member_ `TSharedPtr<class SNamingTokenDataTreeViewWidget> FilterWidget;` — The Dropdown widget.
- L299 _private member_ `mutable TSharedPtr<FCursorTokenData> LastCursorTokenData;` — Cursor token data of the last token data.
- L302 _private member_ `const FEditableTextBoxStyle* TextBoxStyle = nullptr;` — Style shared between Editable and NonEditable text widgets.
- L304 _private member_ `const FTextBlockStyle* ArgumentStyle = nullptr;` — The style to use for our argument formatting.
- L306 _private member_ `TSharedPtr<SHorizontalBox> Box;`
- L308 _private member_ `TSharedPtr<SBox> HScrollBarBox;`
- L309 _private member_ `TSharedPtr<SScrollBar> HScrollBar;`
- L311 _private member_ `TSharedPtr<SBox> VScrollBarBox;`
- L312 _private member_ `TSharedPtr<SScrollBar> VScrollBar;`
- L315 _private member_ `TSharedPtr<FNamingTokensStringSyntaxHighlighterMarshaller> Marshaller;` — The marshaller we use.
- L317 _private member_ `TSharedPtr<class IErrorReportingWidget> ErrorReporting;`
- L320 _private member_ `TAttribute<FText> BoundText;` — The bound text which could return either tokenized or resolved text.
- L322 _private member_ `TAttribute<FText> TokenizedText;`
- L323 _private member_ `TAttribute<FText> ResolvedText;`
- L326 _private member_ `TAttribute<bool> ShouldEvaluateTokens;` — If true, this widget will evaluate the tokenized text to produce the resolved text
- L329 _private member_ `TAttribute<float> EvaluationFrequency;` — If set, specifies how frequently the tokenized text should be re-evaluated
- L332 _private member_ `TAttribute<bool> DisplayTokenIcon;` — If we are displaying the token icon.
- L335 _private member_ `TAttribute<bool> DisplayErrorMessage;` — If error messages are displayed.
- L338 _private member_ `TAttribute<bool> DisplayBorderImage;` — If the border image is used.
- L341 _private member_ `TAttribute<FMargin> TextBoxPaddingOverride;` — Textbox padding (overrides style)
- L344 _private member_ `TAttribute<bool> CanDisplayResolvedText;` — Attribute checking if we can display the resolved text.
- L345 _private member_ `TAttribute<TConstArrayView<FString>> ValidArguments;`
- L348 _private member_ `FOnVerifyTextChanged OnValidateTokenizedText;` — Callback to verify tokenized text when changed. Will return an error message to denote problems.
- L351 _private member_ `FOnVerifyTextChanged OnValidateResolvedText;` — Callback to verify resolved text when changed. Will return an error message to denote problems.
- L354 _private member_ `FOnTextChanged OnTokenizedTextChanged;` — Callback when tokenized text is changed.
- L357 _private member_ `FOnTextCommitted OnTokenizedTextCommitted;` — Callback when tokenized text is committed.
- L360 _private member_ `FSimpleDelegate OnPreEvaluateTokens;` — Callback before we evaluate tokens.
- L363 _private member_ `FOnTokenizedTextEvaluated OnTokenizedTextEvaluated;` — Callback after the tokenized text has been evaluated
- L366 _private member_ `bool bFullyQualifyGlobalTokenSuggestions = false;` — If global tokens should have their namespace inserted too from suggestions.
- L369 _private member_ `bool bFullyQualifyFilteredNamespaces = false;` — If namespaces under FilterArgs.AdditionalNamespacesToInclude should autocomplete.
- L372 _private member_ `bool bSupportInlineEdit = false;` — If the widget supports inline editing
- L375 _private member_ `bool bEnableSuggestionDropdown = true;` — If suggestions are enabled by default.
- L378 _private member_ `mutable bool bModifyingSuggestionDropdown = false;` — Suggesting box in the process of opening or closing.
- L381 _private member_ `bool bShowUnknownTokenWarning = true;` — If the widget should warn when token(s) in the tokenized text are not recognized (unknown tokens).
- L384 _private member_ `bool bShowUnsetTokenWarning = false;` — If the widget should warn when token(s) in the tokenized text evaluate to an empty value (unset tokens).
- L387 _private member_ `TArray<FString> UnknownTokenKeys;` — Token keys that were unknown during the last evaluation. Drives the warning icon visibility and tooltip.
- L390 _private member_ `TArray<FString> UnsetTokenKeys;` — Token keys that evaluated to empty values during the last evaluation. Drives the warning icon visibility and tooltip.

#### struct `SNamingTokensEditableTextBox::FCursorTokenData`  
`struct FCursorTokenData`  
_L230-240_
- L233 _public member_ `FTextLocation StartLocation;` — Start '{' location of token.
- L235 _public member_ `FTextLocation EndLocation;` — End '}' location of token.
- L237 _public member_ `int32 Length;` — Length of EndLocation-StartLocation offset.
- L239 _public member_ `FString EnteredWord;` — Word entered between brackets.

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTokenizedTextEvaluated, const FText&);`
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTokenizedTextEvaluated, const FText&);`
