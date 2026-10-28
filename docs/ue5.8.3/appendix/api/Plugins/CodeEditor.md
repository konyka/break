# Plugins / CodeEditor

- module root: `Plugins/Experimental/CodeEditor/Source/CodeEditor`
- headers: 16; symbols: 143
- symbol kinds: class=16, delegate=1, enum=1, enumerator=3, function=13, member=40, namespace=1, prototype=65, struct=3
- PrivateDependencyModuleNames: AssetTools, Core, CoreUObject, DirectoryWatcher, EditorFramework, Engine, InputCore, Kismet, LevelEditor, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CPPRichTextSyntaxHighlighterTextLayoutMarshaller.h` (Private)


#### class `FCPPRichTextSyntaxHighlighterTextLayoutMarshaller`  
`class FCPPRichTextSyntaxHighlighterTextLayoutMarshaller : public FSyntaxHighlighterTextLayoutMarshaller`  
_L12-64_
- inherits: `FSyntaxHighlighterTextLayoutMarshaller`
- desc: Get/set the raw text to/from a text layout, and also inject syntax highlighting for our rich-text markup
- L49 _public prototype_ `static TSharedRef< FCPPRichTextSyntaxHighlighterTextLayoutMarshaller > Create(const FSyntaxTextStyle& InSyntaxTextStyle);`
- L51 _public prototype_ `virtual ~FCPPRichTextSyntaxHighlighterTextLayoutMarshaller();`
- L55 _protected prototype_ `virtual void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<ISyntaxTokenizer::FTokenizedLine> TokenizedLines) override;`
- L57 _protected prototype_ `FCPPRichTextSyntaxHighlighterTextLayoutMarshaller(TSharedPtr< ISyntaxTokenizer > InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);`
- L60 _protected member_ `FSyntaxTextStyle SyntaxTextStyle;` — Styles used to display the text
- L63 _protected member_ `FString TabString;` — String representing tabs

#### struct `FCPPRichTextSyntaxHighlighterTextLayoutMarshaller::FSyntaxTextStyle`  
`struct FSyntaxTextStyle`  
_L16-47_
- L18 _public function_ `FSyntaxTextStyle() : NormalTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.Normal")) , OperatorTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.Operator")) , KeywordTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.Keyword")) , StringTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.String")) , NumberTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.Number")) , CommentTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.Comment")) , PreProcessorKeywordTextStyle(FCodeEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.CPP.PreProcessorKeyword"))`
- L29 _public function_ `FSyntaxTextStyle(const FTextBlockStyle& InNormalTextStyle, const FTextBlockStyle& InOperatorTextStyle, const FTextBlockStyle& InKeywordTextStyle, const FTextBlockStyle& InStringTextStyle, const FTextBlockStyle& InNumberTextStyle, const FTextBlockStyle& InCommentTextStyle, const FTextBlockStyle& InPreProcessorKeywordTextStyle) : NormalTextStyle(InNormalTextStyle) , OperatorTextStyle(InOperatorTextStyle) , KeywordTextStyle(InKeywordTextStyle) , StringTextStyle(InStringTextStyle) , NumberTextStyle(InNumberTextStyle) , CommentTextStyle(InCommentTextStyle) , PreProcessorKeywordTextStyle(InPreProcessorKeywordTextStyle)`
- L40 _public member_ `FTextBlockStyle NormalTextStyle;`
- L41 _public member_ `FTextBlockStyle OperatorTextStyle;`
- L42 _public member_ `FTextBlockStyle KeywordTextStyle;`
- L43 _public member_ `FTextBlockStyle StringTextStyle;`
- L44 _public member_ `FTextBlockStyle NumberTextStyle;`
- L45 _public member_ `FTextBlockStyle CommentTextStyle;`
- L46 _public member_ `FTextBlockStyle PreProcessorKeywordTextStyle;`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeAssetTypeActions.h` (Private)


#### class `FCodeAssetTypeActions`  
`class FCodeAssetTypeActions : public FAssetTypeActions_Base`  
_L7-17_
- inherits: `FAssetTypeActions_Base`
- L11 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L12 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L13 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L14 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L15 _public prototype_ `virtual uint32 GetCategories() override;`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeEditorCustomization.h` (Private)


#### struct `FCodeEditorTextCustomization`  
`struct FCodeEditorTextCustomization`  
_L8-23_
- reflection: `USTRUCT()`
- L12 _public function_ `FCodeEditorTextCustomization() : Font("") , Color(0.0f, 0.0f, 0.0f, 1.0f)`
- L19 _public member_ `FString Font;` — `UPROPERTY(EditAnywhere, Category=Text)`
- L22 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category=Text)`

#### struct `FCodeEditorControlCustomization`  
`struct FCodeEditorControlCustomization`  
_L26-37_
- reflection: `USTRUCT()`
- L30 _public function_ `FCodeEditorControlCustomization() : Color(0.0f, 0.0f, 0.0f, 1.0f)`
- L36 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category=Controls)`

#### class `UCodeEditorCustomization`  
`class UCodeEditorCustomization : public UObject`  
_L40-54_
- reflection: `UCLASS(Config=Editor)`
- inherits: `UObject`
- L44 _private prototype_ `static const FCodeEditorControlCustomization& GetControl(const FName& ControlCustomizationName);`
- L46 _private prototype_ `static const FCodeEditorTextCustomization& GetText(const FName& TextCustomizationName);`
- L50 _private member_ `TArray<FCodeEditorControlCustomization> Controls;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category=Controls)`
- L53 _private member_ `TArray<FCodeEditorTextCustomization> Text;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category=Text)`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeEditorStyle.h` (Private)


#### class `FCodeEditorStyle`  
`class FCodeEditorStyle`  
_L9-24_
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static const ISlateStyle& Get();`
- L18 _public prototype_ `static const FName& GetStyleSetName();`
- L23 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;` — Singleton instances of this style.

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeProject.h` (Private)


#### class `UCodeProject`  
`class UCodeProject : public UCodeProjectItem`  
_L9-14_
- reflection: `UCLASS()`
- inherits: `UCodeProjectItem`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeProjectEditor.h` (Private)


#### class `FCodeProjectEditor`  
`class FCodeProjectEditor : public FWorkflowCentricApplication, public FGCObject`  
_L13-85_
- inherits: `FWorkflowCentricApplication,FGCObject`
- L16 _public prototype_ `FCodeProjectEditor();`
- L19 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L23 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L24 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L25 _public prototype_ `virtual FText GetToolkitName() const override;`
- L26 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L27 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L28 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L32 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L33 _public function_ `virtual FString GetReferencerName() const override`
- L39 _public function_ `static TSharedPtr<FCodeProjectEditor> Get()`
- L46 _public prototype_ `void InitCodeEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UCodeProject* CodeProject);` — Initialize the code editor
- L49 _public prototype_ `void OpenFileForEditing(class UCodeProjectItem* Item);` — Try to open a new file for editing
- L52 _public function_ `UCodeProject* GetCodeProjectBeingEdited() const` — Get the current project being edited by this code editor
- L54 _public prototype_ `TSharedRef<SWidget> CreateCodeEditorWidget(TSharedRef<FTabInfo> TabInfo, UCodeProjectItem* Item);`
- L56 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);`
- L59 _public function_ `TSharedPtr<class FCodeProjectEditorToolbar> GetToolbarBuilder()` — Access the toolbar builder for this editor
- L61 _public prototype_ `bool Save();`
- L63 _public prototype_ `bool SaveAll();`
- L66 _private prototype_ `void BindCommands();`
- L68 _private prototype_ `void Save_Internal();`
- L70 _private prototype_ `void SaveAll_Internal();`
- L72 _private prototype_ `bool CanSave() const;`
- L74 _private prototype_ `bool CanSaveAll() const;`
- L77 _protected member_ `TSharedPtr<FDocumentTracker> DocumentManager;`
- L80 _protected member_ `TWeakObjectPtr<UCodeProject> CodeProjectBeingEdited;` — The code project we are currently editing
- L82 _protected member_ `TSharedPtr<class FCodeProjectEditorToolbar> ToolbarBuilder;`
- L84 _protected member_ `static TWeakPtr<FCodeProjectEditor> CodeEditor;`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeProjectEditorCommands.h` (Private)


#### class `FCodeProjectEditorCommands`  
`class FCodeProjectEditorCommands : public TCommands<FCodeProjectEditorCommands>`  
_L7-17_
- inherits: `TCommands<FCodeProjectEditorCommands>`
- L10 _public prototype_ `FCodeProjectEditorCommands();`
- L12 _public member_ `TSharedPtr<FUICommandInfo> Save;`
- L13 _public member_ `TSharedPtr<FUICommandInfo> SaveAll;`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeProjectEditorToolbar.h` (Private)


#### class `FCodeProjectEditorToolbar`  
`class FCodeProjectEditorToolbar : public TSharedFromThis<FCodeProjectEditorToolbar>`  
_L9-23_
- inherits: `TSharedFromThis<FCodeProjectEditorToolbar>`
- L12 _public function_ `FCodeProjectEditorToolbar(TSharedPtr<class FCodeProjectEditor> InCodeProjectEditor) : CodeProjectEditor(InCodeProjectEditor)`
- L15 _public prototype_ `void AddEditorToolbar(TSharedPtr<FExtender> Extender);`
- L18 _private prototype_ `void FillEditorToolbar(FToolBarBuilder& ToolbarBuilder);`
- L22 _protected member_ `TWeakPtr<class FCodeProjectEditor> CodeProjectEditor;` — Pointer back to the code editor tool that owns us

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeProjectFactory.h` (Private)


#### class `UCodeProjectFactory`  
`class UCodeProjectFactory : public UFactory`  
_L9-16_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeProjectItem.h` (Private)


#### enum `ECodeProjectItemType::Type`  
`enum Type : int`  
_L11-16_
- L13 _public enumerator_ `Project`
- L14 _public enumerator_ `Folder`
- L15 _public enumerator_ `File`

#### class `UCodeProjectItem`  
`class UCodeProjectItem : public UObject`  
_L20-51_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public prototype_ `void RescanChildren();`
- L28 _public prototype_ `void HandleDirectoryScanned(const FString& InPathName, ECodeProjectItemType::Type InType);`
- L31 _public prototype_ `void HandleDirectoryChanged(const TArray<struct FFileChangeData>& FileChanges);` — Handle directory changing
- L35 _public member_ `TEnumAsByte<ECodeProjectItemType::Type> Type;` — `UPROPERTY(Transient)`
- L38 _public member_ `FString Name;` — `UPROPERTY(Transient)`
- L41 _public member_ `FString Extension;` — `UPROPERTY(Transient)`
- L44 _public member_ `FString Path;` — `UPROPERTY(Transient)`
- L47 _public member_ `TArray<TObjectPtr<UCodeProjectItem>> Children;` — `UPROPERTY(Transient)`
- L50 _public member_ `FDelegateHandle OnDirectoryChangedHandle;` — Delegate handle for directory watcher

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ECodeProjectItemType`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/DirectoryScanner.h` (Private)


#### class `FDirectoryScanner`  
`class FDirectoryScanner`  
_L9-22_
- L12 _public prototype_ `static bool Tick();`
- L14 _public prototype_ `static void AddDirectory(const FString& PathName, const FOnDirectoryScanned& OnDirectoryScanned);`
- L16 _public prototype_ `static bool IsScanning() ;`
- L19 _public member_ `static TArray<struct FDirectoryScannerCommand*> CommandQueue;`
- L21 _public member_ `static bool bDataDirty;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDirectoryScanned, const FString& , ECodeProjectItemType::Type );`
- L7 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnDirectoryScanned, const FString& , ECodeProjectItemType::Type );`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/SCodeEditableText.h` (Private)


#### class `SCodeEditableText`  
`class SCodeEditableText : public SMultiLineEditableText`  
_L11-36_
- inherits: `SMultiLineEditableText`
- L13 _private function_ `SLATE_BEGIN_ARGS( SCodeEditableText )`
- L16 _private prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ARGUMENT(TSharedPtr< ITextLayoutMarshaller >, Marshaller) SLATE_ARGUMENT(TSharedPtr< SScrollBar >, HScrollBar) SLATE_ARGUMENT(TSharedPtr< SScrollBar >, VScrollBar) SLATE_EVENT(FOnTextChanged, OnTextChanged) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The initial text that will appear in the widget.
- L35 _private prototype_ `virtual FReply OnKeyChar(const FGeometry& MyGeometry,const FCharacterEvent& InCharacterEvent) override;`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/SCodeEditor.h` (Private)


#### class `SCodeEditor`  
`class SCodeEditor : public SCompoundWidget`  
_L10-36_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SCodeEditor)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UCodeProjectItem* InCodeProjectItem);`
- L18 _public prototype_ `bool Save() const;`
- L20 _public prototype_ `bool CanSave() const;`
- L22 _public prototype_ `void GotoLineAndColumn(int32 LineNumber, int32 ColumnNumber);`
- L25 _private prototype_ `void OnTextChanged(const FText& NewText);`
- L28 _protected member_ `class UCodeProjectItem* CodeProjectItem;`
- L30 _protected member_ `TSharedPtr<SScrollBar> HorizontalScrollbar;`
- L31 _protected member_ `TSharedPtr<SScrollBar> VerticalScrollbar;`
- L33 _protected member_ `TSharedPtr<class SCodeEditableText> CodeEditableText;`
- L35 _protected member_ `mutable bool bDirty;`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/SCodeProjectEditor.h` (Private)


#### class `SCodeProjectEditor`  
`class SCodeProjectEditor : public SCompoundWidget`  
_L9-36_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SCodeProjectEditor)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UCodeProject* InCodeProject);`
- L19 _private prototype_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — Begin SWidget interface
- L22 _private prototype_ `TSharedRef<class ITableRow> OnGenerateRow(class UCodeProjectItem* Item, const TSharedRef<class STableViewBase>& TableView);`
- L24 _private prototype_ `void OnGetChildren(class UCodeProjectItem* Item, TArray<class UCodeProjectItem*>& OutChildItems);`
- L26 _private prototype_ `EVisibility GetThrobberVisibility() const;`
- L28 _private prototype_ `FName GetIconForItem(class UCodeProjectItem* Item) const;`
- L30 _private prototype_ `void HandleMouseButtonDoubleClick(class UCodeProjectItem* Item) const;`
- L33 _private member_ `class UCodeProject* CodeProject;`
- L35 _private member_ `TSharedPtr<STreeView<class UCodeProjectItem*>> ProjectTree;`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/SProjectViewItem.h` (Private)


#### class `SProjectViewItem`  
`class SProjectViewItem : public SCompoundWidget`  
_L7-19_
- inherits: `SCompoundWidget`
- L10 _public function_ `SLATE_BEGIN_ARGS(SProjectViewItem)`
- L12 _public prototype_ `SLATE_ARGUMENT(FName, IconName) SLATE_ARGUMENT(FText, Text) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/WhiteSpaceTextRun.h` (Private)


#### class `FWhiteSpaceTextRun`  
`class FWhiteSpaceTextRun : public FSlateTextRun`  
_L9-26_
- inherits: `FSlateTextRun`
- L12 _public prototype_ `static TSharedRef< FWhiteSpaceTextRun > Create( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FTextBlockStyle& Style, const FTextRange& InRange, int32 NumSpacesPerTab );`
- L15 _public prototype_ `virtual FVector2D Measure( int32 StartIndex, int32 EndIndex, float Scale, const FRunTextContext& TextContext) const override;`
- L18 _protected prototype_ `FWhiteSpaceTextRun( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FTextBlockStyle& InStyle, const FTextRange& InRange, int32 InNumSpacesPerTab );`
- L21 _private member_ `int32 NumSpacesPerTab;`
- L23 _private member_ `float TabWidth;`
- L25 _private member_ `float SpaceWidth;`
