# Plugins / UserToolBoxCore

- module root: `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore`
- headers: 22; symbols: 328
- symbol kinds: class=34, delegate=11, function=8, member=100, prototype=170, struct=5
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetTools, Blutility, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorSubsystem, EditorWidgets, Engine, InputCore, InteractiveToolsFramework, Kismet, LevelEditor, Projects, PropertyEditor, Slate, SlateCore, SlateScriptingCommands, StatusBar, ToolMenus, ToolWidgets, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Private/AssetTypeActions_UTBEditorUtilityBlueprint.h` (Private)


#### class `FAssetTypeActions_UTBEditorBlueprint`  
`class FAssetTypeActions_UTBEditorBlueprint : public FAssetTypeActions_Blueprint`  
_L9-20_
- inherits: `FAssetTypeActions_Blueprint`
- L13 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L14 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual bool HasActions(const TArray<UObject*>& InObjects) const override;`
- L17 _public prototype_ `virtual uint32 GetCategories() override;`
- L18 _public function_ `virtual bool CanLocalize() const override`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Private/Customization/BaseCommandCustomization.h` (Private)


#### class `FBaseCommandCustomization`  
`class FBaseCommandCustomization : public IDetailCustomization`  
_L15-26_
- inherits: `IDetailCustomization`
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L25 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Private/Editor/UTBEditorCommands.h` (Private)


#### class `FUTBEditorCommands`  
`class FUTBEditorCommands: public TCommands<FUTBEditorCommands>`  
_L10-25_
- inherits: `TCommands<FUTBEditorCommands>`
- L13 _public prototype_ `FUTBEditorCommands();`
- L14 _public prototype_ `~FUTBEditorCommands();`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L24 _public member_ `TSharedPtr< FUICommandInfo > RenameSection;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Private/UserToolBoxFunctionLibrary.h` (Private)


#### class `UUserToolBoxFunctionLibrary`  
`class UUserToolBoxFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public member_ `static const FSlateBrush DefaultBrush;`
- L20 _public prototype_ `static const FSlateBrush& GetBrushById(FString Name);` — `UFUNCTION(BlueprintCallable, Category=" User Toolbox Library")`
- L23 _public prototype_ `static TArray<FName> GetAllSlateStyle();` — `UFUNCTION(BlueprintCallable, Category=" User Toolbox Library")`
- L26 _public prototype_ `static const FSlateBrush& GetBrushByStyleAndId(FName StyleName, FName Id);` — `UFUNCTION(BlueprintCallable, Category=" User Toolbox Library")`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/Editor/IUTBTabEditor.h` (Public)


#### class `IUTBTabEditor`  
`class IUTBTabEditor : public FAssetEditorToolkit`  
_L10-14_
- inherits: `FAssetEditorToolkit`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/Editor/SCommandPickMenu.h` (Public)


#### class `SCommandPickMenuWidget`  
`class SCommandPickMenuWidget : public SCompoundWidget`  
_L12-60_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS( SCommandPickMenuWidget ) :_OnCommandSelectionChanged()`
- L31 _public prototype_ `SLATE_EVENT(FOnCommandSelectedChanged, OnCommandSelectionChanged) SLATE_END_ARGS() SCommandPickMenuWidget();`
- L39 _public prototype_ `~SCommandPickMenuWidget();`
- L41 _public prototype_ `void Construct( const FArguments& InArgs );`
- L45 _private prototype_ `void ReconstructCommandTree();`
- L47 _private prototype_ `void UpdateFilteredTreeNodes(FString Text);`
- L48 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FCommandTreeNode> InTreeNode, bool bInIsItemExpanded);`
- L51 _private member_ `FOnCommandSelectedChanged OnCommandSelectionChanged;`
- L52 _private member_ `TArray<TSharedPtr<FCommandTreeNode>> CommandTree;`
- L53 _private member_ `TArray<TSharedPtr<FCommandTreeNode>> CommandTreeAllNodes;`
- L55 _private member_ `TMap<TSharedPtr<FCommandTreeNode>,TArray<TSharedPtr<FCommandTreeNode>>> LeafsWithParentHierarchy;` — reverse tree for seaching
- L57 _private member_ `TSharedPtr<STreeView<TSharedPtr<FCommandTreeNode>>> TreeViewPtr;`
- L59 _private member_ `UClass* Selection;`

#### struct `SCommandPickMenuWidget::FCommandTreeNode`  
`struct FCommandTreeNode`  
_L14-21_
- L16 _public member_ `bool bIsCategory= false;`
- L17 _public member_ `UClass* Class;`
- L18 _public member_ `FString Name;`
- L19 _public member_ `TArray<TSharedPtr<FCommandTreeNode>> Children;`
- L20 _public member_ `TArray<TSharedPtr<FCommandTreeNode>> FilteredChildren;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCommandSelectedChanged, UClass*) class SCommandPickMenuWidget : public SCompoundWidget { struct FCommandTreeNode { bool bIsCategory= false; UClass* Class; FString Name; TArray<TSharedPtr<FCommandTreeNode>> Children; TArray<TSharedPtr<FCommandTreeNode>> FilteredChildren; }; public: SLATE_BEGIN_ARGS( SCommandPickMenuWidget ) :_OnCommandSelectionChanged() { } SLATE_EVENT(FOnCommandSelectedChanged, OnCommandSelectionChanged) SLATE_END_ARGS() SCommandPickMenuWidget(); ~SCommandPickMenuWidget(); void Construct( const FArguments& InArgs ); private: void ReconstructCommandTree(); void UpdateFilteredTreeNodes(FString Text); void OnSetExpansionRecursive(TSharedPtr<FCommandTreeNode> InTreeNode, bool bInIsItemExpanded);`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/Editor/SCommandWithOptionsDetailsView.h` (Public)


#### class `SCommandDetailsView`  
`class SCommandDetailsView : public SCompoundWidget`  
_L12-38_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS( SCommandDetailsView ) : _Command()`
- L22 _public prototype_ `SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_EVENT( FOnObjectPropertyModified, OnObjectPropertyModified ) SLATE_END_ARGS() SCommandDetailsView();` — Sets the text content for this editable text widget
- L29 _public prototype_ `~SCommandDetailsView();`
- L31 _public prototype_ `void Construct( const FArguments& InArgs );`
- L32 _public prototype_ `void SetObject(UUTBBaseCommand* Command);`
- L35 _private member_ `TWeakObjectPtr<UUTBBaseCommand> Command;`
- L36 _private member_ `TSharedPtr<IDetailsView> CommandDetailsView;`
- L37 _private member_ `FOnObjectPropertyModified OnObjectPropertyModified;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectPropertyModified,UUTBBaseCommand*);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectPropertyModified,UUTBBaseCommand*);`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/Editor/SCommandWithOptionsWidget.h` (Public)


#### class `SButtonCommandWidget`  
`class SButtonCommandWidget : public SButton`  
_L14-44_
- inherits: `SButton`
- L18 _public function_ `SLATE_BEGIN_ARGS( SButtonCommandWidget ) :_Content()`
- L25 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_EVENT( FOnClicked, OnClicked ) SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_END_ARGS() SButtonCommandWidget();` — Slot for this button's content (optional)
- L32 _public prototype_ `~SButtonCommandWidget();`
- L34 _public prototype_ `void Construct(const FArguments& InArgs );`
- L35 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _private member_ `TWeakObjectPtr<UUTBBaseCommand> Command;`
- L42 _private member_ `FOnContextMenuOpening OnContextMenuOpening;`

#### class `SCommandWidget`  
`class SCommandWidget : public SCompoundWidget`  
_L45-97_
- inherits: `SCompoundWidget`
- L48 _public function_ `DECLARE_DELEGATE_OneParam(FOnTabChangedNotify, UUserToolBoxBaseTab*) DECLARE_DELEGATE_ThreeParams(FOnCommandChanged, UUTBBaseCommand*, FString , int ) DECLARE_DELEGATE_OneParam(FOnCommandSelected, UUTBBaseCommand*) DECLARE_DELEGATE_OneParam(FOnCommandDeleted, UUTBBaseCommand* ) DECLARE_DELEGATE_ThreeParams(FOnDropCommand, UUTBBaseCommand*, FString , int ) SLATE_BEGIN_ARGS( SCommandWidget ) : _Command() , _IndexInSection(-1) , _SectionName("")`
- L63 _public prototype_ `SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_ATTRIBUTE( int, IndexInSection ) SLATE_ATTRIBUTE( FString, SectionName ) SLATE_ATTRIBUTE( TSharedPtr<FUTBTabEditor>, Editor ) SLATE_EVENT(FOnTabChangedNotify, OnTabChanged) SLATE_EVENT(FOnCommandChanged, OnCommandChanged) SLATE_EVENT(FOnCommandSelected, OnCommandSelected) SLATE_EVENT(FOnCommandDeleted, OnCommandDeleted) SLATE_EVENT(FOnDropCommand, OnDropCommand) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() SCommandWidget();` — Sets the text content for this editable text widget
- L76 _public prototype_ `~SCommandWidget();`
- L77 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L78 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L79 _public prototype_ `void Construct( const FArguments& InArgs );`
- L81 _public prototype_ `void OnObjectsReplacedCallback(const TMap<UObject*, UObject*>& ReplacementMap);`
- L82 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L83 _public prototype_ `TSharedPtr<SWidget> CreateContextMenu();`
- L85 _private prototype_ `void RegisterContextMenu();`
- L86 _private prototype_ `void RebuildWidget();`
- L87 _private member_ `TWeakPtr<FUTBTabEditor> Editor;`
- L88 _private member_ `FOnTabChangedNotify OnTabChanged;`
- L89 _private member_ `FOnCommandChanged OnCommandChanged;`
- L90 _private member_ `FOnCommandSelected OnCommandSelected;`
- L91 _private member_ `FOnCommandDeleted OnCommandDeleted;`
- L92 _private member_ `FOnDropCommand OnDropCommand;`
- L93 _private member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L94 _private member_ `TWeakObjectPtr<UUTBBaseCommand> Command;`
- L95 _private member_ `int IndexInSection;`
- L96 _private member_ `FString SectionName;`

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTabChangedNotify, UUserToolBoxBaseTab*) DECLARE_DELEGATE_ThreeParams(FOnCommandChanged, UUTBBaseCommand*, FString , int ) DECLARE_DELEGATE_OneParam(FOnCommandSelected, UUTBBaseCommand*) DECLARE_DELEGATE_OneParam(FOnCommandDeleted, UUTBBaseCommand* ) DECLARE_DELEGATE_ThreeParams(FOnDropCommand, UUTBBaseCommand*, FString , int ) SLATE_BEGIN_ARGS( SCommandWidget ) : _Command() , _IndexInSection(-1) , _SectionName("") { } SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_ATTRIBUTE( int, IndexInSection ) SLATE_ATTRIBUTE( FString, SectionName ) SLATE_ATTRIBUTE( TSharedPtr<FUTBTabEditor>, Editor ) SLATE_EVENT(FOnTabChangedNotify, OnTabChanged) SLATE_EVENT(FOnCommandChanged, OnCommandChanged) SLATE_EVENT(FOnCommandSelected, OnCommandSelected) SLATE_EVENT(FOnCommandDeleted, OnCommandDeleted) SLATE_EVENT(FOnDropCommand, OnDropCommand) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() SCommandWidget();`
- L49 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCommandChanged, UUTBBaseCommand*, FString , int ) DECLARE_DELEGATE_OneParam(FOnCommandSelected, UUTBBaseCommand*) DECLARE_DELEGATE_OneParam(FOnCommandDeleted, UUTBBaseCommand* ) DECLARE_DELEGATE_ThreeParams(FOnDropCommand, UUTBBaseCommand*, FString , int ) SLATE_BEGIN_ARGS( SCommandWidget ) : _Command() , _IndexInSection(-1) , _SectionName("") { } SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_ATTRIBUTE( int, IndexInSection ) SLATE_ATTRIBUTE( FString, SectionName ) SLATE_ATTRIBUTE( TSharedPtr<FUTBTabEditor>, Editor ) SLATE_EVENT(FOnTabChangedNotify, OnTabChanged) SLATE_EVENT(FOnCommandChanged, OnCommandChanged) SLATE_EVENT(FOnCommandSelected, OnCommandSelected) SLATE_EVENT(FOnCommandDeleted, OnCommandDeleted) SLATE_EVENT(FOnDropCommand, OnDropCommand) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() SCommandWidget();`
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCommandSelected, UUTBBaseCommand*) DECLARE_DELEGATE_OneParam(FOnCommandDeleted, UUTBBaseCommand* ) DECLARE_DELEGATE_ThreeParams(FOnDropCommand, UUTBBaseCommand*, FString , int ) SLATE_BEGIN_ARGS( SCommandWidget ) : _Command() , _IndexInSection(-1) , _SectionName("") { } SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_ATTRIBUTE( int, IndexInSection ) SLATE_ATTRIBUTE( FString, SectionName ) SLATE_ATTRIBUTE( TSharedPtr<FUTBTabEditor>, Editor ) SLATE_EVENT(FOnTabChangedNotify, OnTabChanged) SLATE_EVENT(FOnCommandChanged, OnCommandChanged) SLATE_EVENT(FOnCommandSelected, OnCommandSelected) SLATE_EVENT(FOnCommandDeleted, OnCommandDeleted) SLATE_EVENT(FOnDropCommand, OnDropCommand) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() SCommandWidget();`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCommandDeleted, UUTBBaseCommand* ) DECLARE_DELEGATE_ThreeParams(FOnDropCommand, UUTBBaseCommand*, FString , int ) SLATE_BEGIN_ARGS( SCommandWidget ) : _Command() , _IndexInSection(-1) , _SectionName("") { } SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_ATTRIBUTE( int, IndexInSection ) SLATE_ATTRIBUTE( FString, SectionName ) SLATE_ATTRIBUTE( TSharedPtr<FUTBTabEditor>, Editor ) SLATE_EVENT(FOnTabChangedNotify, OnTabChanged) SLATE_EVENT(FOnCommandChanged, OnCommandChanged) SLATE_EVENT(FOnCommandSelected, OnCommandSelected) SLATE_EVENT(FOnCommandDeleted, OnCommandDeleted) SLATE_EVENT(FOnDropCommand, OnDropCommand) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() SCommandWidget();`
- L52 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnDropCommand, UUTBBaseCommand*, FString , int ) SLATE_BEGIN_ARGS( SCommandWidget ) : _Command() , _IndexInSection(-1) , _SectionName("") { } SLATE_ATTRIBUTE( UUTBBaseCommand*, Command ) SLATE_ATTRIBUTE( int, IndexInSection ) SLATE_ATTRIBUTE( FString, SectionName ) SLATE_ATTRIBUTE( TSharedPtr<FUTBTabEditor>, Editor ) SLATE_EVENT(FOnTabChangedNotify, OnTabChanged) SLATE_EVENT(FOnCommandChanged, OnCommandChanged) SLATE_EVENT(FOnCommandSelected, OnCommandSelected) SLATE_EVENT(FOnCommandDeleted, OnCommandDeleted) SLATE_EVENT(FOnDropCommand, OnDropCommand) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() SCommandWidget();`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/Editor/UTBTabEditor.h` (Public)


#### struct `FCommandDragDropOperation`  
`struct FCommandDragDropOperation : public FDragDropOperation`  
_L15-28_
- inherits: `FDragDropOperation`
- L18 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FCommandDragDropOperation, FDragDropOperation);`
- L20 _public prototype_ `FCommandDragDropOperation();`
- L21 _public prototype_ `virtual ~FCommandDragDropOperation();`
- L23 _public prototype_ `static TSharedRef<FCommandDragDropOperation> New(UUTBBaseCommand* Command);`
- L26 _public member_ `TWeakObjectPtr<UUTBBaseCommand> Command;`

#### class `FUTBTabEditor`  
`class FUTBTabEditor : public IUTBTabEditor , public FEditorUndoClient`  
_L31-106_
- inherits: `IUTBTabEditor,FEditorUndoClient`
- L35 _public prototype_ `FUTBTabEditor();`
- L36 _public prototype_ `~FUTBTabEditor();`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentSectionChange, FString);`
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSectionListChange);`
- L41 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L42 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L43 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L44 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L45 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L46 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L47 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L48 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L50 _public prototype_ `virtual void InitUTBTabEditor(const EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost, UUserToolBoxBaseTab* Tab);`
- L51 _public prototype_ `FString GetCurrentSection();`
- L53 _public member_ `FOnCurrentSectionChange OnCurrentSectionChange;`
- L54 _public member_ `FOnSectionListChange OnSectionListChange;`
- L56 _public prototype_ `void AddCommandToCurrentSection(UUTBBaseCommand* InCommand);`
- L57 _public prototype_ `void RemoveCommandFromCurrentSection(UUTBBaseCommand* InCommand, bool ShouldRebuild=false);`
- L59 _public prototype_ `void AddCommandAt(UUTBBaseCommand* InCommand, FString Section,int Index);`
- L60 _public prototype_ `void SetCurrentCommandSelection(UUTBBaseCommand* Command);`
- L61 _public prototype_ `void NotifyTabHasChanged(UUserToolBoxBaseTab* Tab);`
- L62 _public prototype_ `void UpdateCommand(UUTBBaseCommand* Command);`
- L63 _public prototype_ `void UpdateCurrentSection();`
- L64 _public prototype_ `void CreateNewSection();`
- L65 _public prototype_ `void MoveSectionAfterExistingSection(FString SectionToMove,FString SectionToTarget);`
- L66 _public prototype_ `void RefreshSectionNames();`
- L67 _public prototype_ `void RemoveCurrentSection();`
- L68 _public prototype_ `void EditActiveSectionName();`
- L69 _public prototype_ `void RenameActiveSection(FString NewName);`
- L70 _public prototype_ `void BindCommands();`
- L73 _protected prototype_ `void CreateOrRebuildUTBTabTabWidget();`
- L74 _protected prototype_ `void CreateOrRebuildUTBTabSectionTabWidget();`
- L75 _protected prototype_ `TSharedPtr<SWidget> CreateUTBTabDetailsTabWidget();`
- L76 _protected prototype_ `TSharedPtr<SWidget> CreateUTBCommandTabWidget();`
- L77 _protected prototype_ `TSharedPtr<SWidget> CreateUTBCommandDetailsTabWidget();`
- L79 _protected prototype_ `void SetCurrentSection(FString SectionName);`
- L80 _protected member_ `TArray<TSharedPtr<FString>> SectionNames;`
- L90 _protected member_ `static const FName UTBTabTabId;`
- L91 _protected member_ `static const FName UTBTabSectionTabId;`
- L92 _protected member_ `static const FName UTBTabDetailsTabId;`
- L93 _protected member_ `static const FName UTBCommandTabId;`
- L94 _protected member_ `static const FName UTBCommandDetailsTabId;`
- L95 _protected member_ `FString CurrentSection;`
- L96 _protected member_ `FAssetData CurrentSelectedCommand;`
- L97 _protected member_ `TSharedPtr<SVerticalBox> UUTBTabTabWidget;`
- L98 _protected member_ `TSharedPtr<SVerticalBox> UUTBTabSectionTabWidget;`
- L99 _protected member_ `TSharedPtr<SWidget> UUTBTabDetailsTabWidget;`
- L100 _protected member_ `TSharedPtr<SWidget> UUTBCommandTabWidget;`
- L101 _protected member_ `TSharedPtr<SWidget> UUTBCommandDetailsTabWidget;`
- L103 _protected member_ `TSharedPtr<SCommandDetailsView> CommandDetailsView;`
- L104 _protected member_ `TSharedPtr<SVerticalBox> SectionVerticalBox;`
- L105 _protected member_ `TSharedPtr<SListView<TSharedPtr<FString>>> SectionListView;`

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentSectionChange, FString);`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSectionListChange);`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/IconsTracker.h` (Public)


#### struct `FIconInfo`  
`struct FIconInfo`  
_L11-22_
- reflection: `USTRUCT()`
- L15 _public member_ `FString Id;` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`
- L17 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`
- L19 _public member_ `FVector2D IconSize=FVector2D(30.0f);` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`

#### struct `FIconFolderInfo`  
`struct FIconFolderInfo : public FTableRowBase`  
_L24-33_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L28 _public member_ `FDirectoryPath FolderPath;` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`
- L30 _public member_ `FString PrefixId;` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`
- L32 _public member_ `FVector2D IconSize=FVector2D(30.0f);` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`

#### class `UIconsTracker`  
`class UIconsTracker : public UDataAsset`  
_L36-46_
- reflection: `UCLASS()`
- inherits: `UDataAsset`
- L42 _public member_ `TArray<FIconFolderInfo> IconFolderInfos;` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`
- L44 _public member_ `FString PrefixId;` — `UPROPERTY(EditAnywhere , Category="Icon Tracker")`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/SVerticalTextBlock.h` (Public)


#### class `SVerticalTextBlock`  
`class SVerticalTextBlock : public STextBlock`  
_L7-133_
- inherits: `STextBlock`
- L11 _public function_ `SLATE_BEGIN_ARGS( SVerticalTextBlock ) : _Text() , _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) ) , _Font() , _StrikeBrush() , _ColorAndOpacity() , _ShadowOffset() , _ShadowColorAndOpacity() , _HighlightColor() , _HighlightShape() , _HighlightText() , _WrapTextAt(0.0f) , _AutoWrapText(false) , _WrappingPolicy(ETextWrappingPolicy::DefaultWrapping) , _TransformPolicy() , _Margin() , _LineHeightPercentage(1.0f) , _Justification(ETextJustify::Left) , _MinDesiredWidth(0.0f) , _TextShapingMethod() , _TextFlowDirection() , _LineBreakPolicy() , _OverflowPolicy() , _SimpleTextMode(false)`
- L40 _public prototype_ `SLATE_ATTRIBUTE( FText, Text ) SLATE_STYLE_ARGUMENT( FTextBlockStyle, TextStyle ) SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_ATTRIBUTE( const FSlateBrush*, StrikeBrush ) SLATE_ATTRIBUTE( FSlateColor, ColorAndOpacity ) SLATE_ATTRIBUTE( FVector2D, ShadowOffset ) SLATE_ATTRIBUTE( FLinearColor, ShadowColorAndOpacity ) SLATE_ATTRIBUTE( FLinearColor, HighlightColor ) SLATE_ATTRIBUTE( const FSlateBrush*, HighlightShape ) SLATE_ATTRIBUTE( FText, HighlightText ) /** Whether text wraps onto a new line when it's length exceeds this width;` — The text displayed in this text block
- L123 _public prototype_ `~SVerticalTextBlock();` — Destructor
- L130 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param	InArgs	The declaration data for this widget
- L132 _public prototype_ `virtual FVector2D ComputeDesiredSize(const float) const override;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBBaseCommand.h` (Public)


#### class `UUTBBaseCommand`  
`class UUTBBaseCommand : public UObject`  
_L16-52_
- reflection: `UCLASS(Blueprintable, Abstract,EditInlineNew)`
- inherits: `UObject`
- desc: UUTBBaseCommand is the base class for any command of the usertoolbox framework. Inherit directly from this class if you want to create a new command implemented in c++
- L22 _public member_ `FString Name="De` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Command Description", AssetRegistrySearchable)` — The name of the command
- L25 _public member_ `FString IconPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Command Description")` — The icon path for the command
- L27 _public member_ `FString Tooltip;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Command Description")`
- L29 _public member_ `FString Category="De` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Command Description", AssetRegistrySearchable)`
- L31 _public member_ `bool bShowParameters=false;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Command Description")`
- L34 _public member_ `FInputChord KeyboardShortcut=FInputChord();` — `UPROPERTY(EditAnywhere, Category="Command Description")`
- L37 _public member_ `TObjectPtr<UClass> UIOverride=nullptr;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowAbstract = "false", MustImplement = "/Script/UserToolBoxCore.UTBUICommand" ), Category="Command Description")`
- L39 _public member_ `TObjectPtr<UObject> UI=nullptr;` — `UPROPERTY(Transient)`
- L41 _public member_ `bool bIsTransaction=false;` — `UPROPERTY()`
- L42 _public prototype_ `virtual void Execute();`
- L44 _public prototype_ `void ExecuteCommand();` — `UFUNCTION()`
- L45 _public prototype_ `virtual bool DisplayParameters();`
- L46 _public prototype_ `virtual UUTBBaseCommand* CopyCommand(UObject* Owner) const ;`
- L49 _public prototype_ `void AddObjectToTransaction(UObject* Object);` — `UFUNCTION(BlueprintCallable,Category="Transaction")`
- L51 _public prototype_ `void AddObjectsToTransaction(TArray<UObject*> Objects);` — `UFUNCTION(BlueprintCallable,Category="Transaction")`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBBaseTab.h` (Public)


#### struct `FUITemplateParameters`  
`struct FUITemplateParameters`  
_L22-27_
- desc: UTBTabSection is the class that represent a section in a UUserToolBoxBaseTab it contains the name of the section and the list of command attach to that section
- L24 _public member_ `bool bForceHideSettingsButton=false;`
- L25 _public member_ `bool bPrefixSectionWithTabName=false;`
- L26 _public member_ `bool bPostfixSectionWithTabName=false;`

#### class `UUTBTabSection`  
`class UUTBTabSection : public UObject`  
_L30-40_
- reflection: `UCLASS()`
- inherits: `UObject`
- L36 _public member_ `FString SectionName;` — `UPROPERTY(EditAnywhere, Category="Command Tab")` — The name of the section
- L39 _public member_ `TArray<TObjectPtr<UUTBBaseCommand>> Commands;` — `UPROPERTY()` — The list of command

#### class `UUserToolBoxBaseTab`  
`class UUserToolBoxBaseTab : public UDataAsset`  
_L49-158_
- reflection: `UCLASS()`
- inherits: `UDataAsset`
- desc: UUserToolBoxBaseTab is the class that represent a configurable tab This class contains the name of the tab and a section's list. In that class, you can also specified an UTBUICommand to override "by default" the UI of each command. Note: The override define in the command override the UI override define in the tab. This is the class serialized as an asset.
- L53 _public member_ `static const FName PlaceHolderSectionName;`
- L56 _public member_ `FString Name = "De` — `UPROPERTY(EditAnywhere, Category="Command Tab", AssetRegistrySearchable)` — The name of the toolbox
- L59 _public member_ `TSubclassOf<UUTBDefaultUITemplate> TabUI;` — `UPROPERTY(EditAnywhere, Category="Command Tab")` — The UI template to use to render this tab
- L62 _public member_ `TObjectPtr<UClass> DefaultCommandUIOverride;` — `UPROPERTY(EditAnywhere, meta=(MustImplement = "/Script/UserToolBoxCore.UTBUICommand", AllowAbstract="false"), Category="Command Tab")` — the default override for each command ( does not override ui command specified in the command)
- L67 _public member_ `bool IsSettingShouldBeVisible=true;` — `UPROPERTY(EditAnywhere, Category="Command Tab")` — Should the setting's icon be visible on the top right of the tab ( for easy access)
- L69 _public member_ `bool bIsVisibleInViewportOverlay=false;` — `UPROPERTY(EditAnywhere, Category="Command Tab",AssetRegistrySearchable)`
- L71 _public member_ `bool bIsVisibleInDrawer=true;` — `UPROPERTY(EditAnywhere, Category="Command Tab",AssetRegistrySearchable)`
- L73 _public member_ `bool bIsVisibleInWindowsMenu =true;` — `UPROPERTY(EditAnywhere, Category="Command Tab", AssetRegistrySearchable)`
- L75 _public prototype_ `TSharedPtr<SWidget> GenerateUI();` — Function to generate the raw widget of the tab. you may consider using the SUserToolBoxTabWidget instead if you want to register your different commands to the input manager etc..
- L76 _public prototype_ `TSharedPtr<SWidget> GenerateUI(const TSubclassOf<UUTBDefaultUITemplate> TabUiClass,const FUITemplateParameters& Params);`
- L77 _public prototype_ `virtual void PostLoad() override;`
- L78 _public prototype_ `virtual void BeginDestroy() override;`
- L84 _public prototype_ `void InsertCommandFromClass(const TSubclassOf<UUTBBaseCommand> InClass,const FString Section,const int Index=-1);` — Insert a default command from the class at a specific location in a specific section @param InClass the class we want to instanciate @param Section the section name @param Index  the position in the section of the new command
- L90 _public prototype_ `void InsertCommand(const UUTBBaseCommand* InCommand,const FString SectionName,const int Index=-1);` — Insert a command at a specific location in a specific section @param InCommand the command we want to add to the tab @param Section the section name @param Index the position in the section of the new command
- L95 _public prototype_ `void RemoveCommand(const FString SectionName,const int Index=0);` — remove a command at a specific location in a specific section @param Section the section name @param Index the position in the section of the command to remove
- L99 _public prototype_ `UUTBTabSection* GetSection(const FString SectionName);` — return the section with the specified name @param SectionName the section name
- L103 _public prototype_ `UUTBTabSection* GetOrCreateSection(const FString SectionName);` — return the section with the specified name or create it if it does not exist @param SectionName the section name
- L107 _public prototype_ `void RemoveSection( UUTBTabSection* Section);` — remove a section @param Section The section to remove
- L111 _public prototype_ `void RemoveSection(const FString SectionName);` — remove a section with a specific name @param SectionName The name of the section to remove
- L115 _public prototype_ `void RemoveCommand(UUTBBaseCommand* Command);` — remove a command @param Command The command to remove
- L120 _public prototype_ `void RemoveCommandFromSection(UUTBBaseCommand* Command,const FString SectionName);` — remove a command contained in a specific section @param Command The name of the section to remove @param SectionName The name of the section to remove
- L124 _public prototype_ `void ReplaceCommands(const TMap<UObject*,UObject*>& ReplacementMap);` — replace a batch of command @param ReplacementMap Map that contains the command to replace
- L128 _public prototype_ `TArray<UUTBTabSection*> GetSections();` — get all the section of that tab @return an array of section
- L130 _public prototype_ `void MoveSectionAfterExistingSection(const FString SectionToMoveName,const FString SectionToTargetName);`
- L134 _public prototype_ `UUTBTabSection* GetPlaceHolderSection();` — return the placeholder section @return the placeholder section
- L138 _public prototype_ `bool ContainsCommand(const UUTBBaseCommand* Command) const;` — return the presence of the command in the tab @return is the command inside that tab
- L142 _public prototype_ `void RegisterCommand();` — registering the command list
- L145 _public prototype_ `void UnregisterCommand();` — unregistering the command list
- L147 _public prototype_ `void RemoveInvalidCommand();`
- L151 _private member_ `TArray<TObjectPtr<UUTBTabSection>> Sections;` — `UPROPERTY()` — the array of sections
- L154 _private member_ `TObjectPtr<UUTBTabSection> PlaceholderSection;` — `UPROPERTY()` — the placeholder section
- L157 _private member_ `FDelegateHandle OnObjectReplacedHandle;`

#### class `SUserToolBoxTabWidget`  
`class SUserToolBoxTabWidget : public SCompoundWidget`  
_L164-198_
- inherits: `SCompoundWidget`
- desc: SUserToolBoxTabWidget is the UI widget generated by a UUserToolBoxBaseTab. It will generated the wanted UI based on the different UI override set in the UUserToolBoxBaseTab or in a specific command
- L166 _private function_ `SLATE_BEGIN_ARGS( SUserToolBoxTabWidget ) : _Tab(nullptr), _UIOverride(nullptr)`
- L174 _private prototype_ `SLATE_ATTRIBUTE( UUserToolBoxBaseTab*, Tab ) SLATE_ATTRIBUTE( TSubclassOf<UUTBDefaultUITemplate>, UIOverride ) SLATE_ATTRIBUTE( FUITemplateParameters, UIParameters ) SLATE_END_ARGS() ~SUserToolBoxTabWidget();` — Sets the text content for this editable text widget
- L181 _private prototype_ `void Construct( const FArguments& InArgs );`
- L186 _private prototype_ `void UpdateTab(UUserToolBoxBaseTab* InTab);` — Function to request a tab UI update @param Tab Tab to update
- L188 _private prototype_ `void OnObjectModified( UObject* Object, struct FPropertyChangedEvent&);`
- L191 _private member_ `TObjectPtr<UUserToolBoxBaseTab> Tab;`
- L192 _private member_ `TSubclassOf<UUTBDefaultUITemplate> UIOverride;`
- L193 _private member_ `FUITemplateParameters Parameters;`
- L195 _private member_ `FDelegateHandle OnTabChangedDelegate;` — Delegate handle
- L196 _private member_ `FDelegateHandle OnObjectPropertyChangedDelegate;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBBaseUICommand.h` (Public)


#### class `UBaseCommandNativeUI`  
`class UBaseCommandNativeUI : public UObject, public IUTBUICommand`  
_L15-32_
- reflection: `UCLASS()`
- inherits: `UObject,IUTBUICommand`
- desc: Native base class for Command UI Customization
- L19 _public prototype_ `virtual bool IsSupportingCommandClass(TSubclassOf<UUTBBaseCommand> CommandClass) override;`
- L20 _public prototype_ `virtual void SetCommand(UUTBBaseCommand* Command) override ;`
- L21 _public prototype_ `virtual void ExecuteCurrentCommand() override ;`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetUI() override ;`
- L27 _protected member_ `TObjectPtr<UUTBBaseCommand> MyCommand;` — `UPROPERTY()`
- L30 _public prototype_ `void ReplaceCommand(const TMap<UObject*,UObject*>& Map);`
- L31 _public prototype_ `virtual void BeginDestroy() override;`

#### class `UUTBCommandUMGUI`  
`class UUTBCommandUMGUI : public UUserWidget , public IUTBUICommand`  
_L35-58_
- reflection: `UCLASS()`
- inherits: `UUserWidget,IUTBUICommand`
- L41 _public prototype_ `bool DoesSupportClass(TSubclassOf<UUTBBaseCommand> ObjectClass);` — `UFUNCTION(BlueprintImplementableEvent, Category=" Command UI")`
- L44 _public prototype_ `void ExecuteCommand();` — `UFUNCTION(BlueprintCallable, Category=" Command UI")`
- L47 _public member_ `TObjectPtr<UUTBBaseCommand> Command;` — `UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=" Command UI")`
- L51 _public prototype_ `virtual bool IsSupportingCommandClass(TSubclassOf<UUTBBaseCommand> CommandClass) override;`
- L52 _public prototype_ `virtual void SetCommand(UUTBBaseCommand* Command) override;`
- L53 _public prototype_ `virtual void ExecuteCurrentCommand() override;`
- L54 _public prototype_ `virtual TSharedRef<SWidget> GetUI() override;`
- L56 _public prototype_ `void ReplaceCommand(const TMap<UObject*,UObject*>& Map);`
- L57 _public prototype_ `virtual void BeginDestroy() override;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBBaseUICommandInterface.h` (Public)


#### class `UUTBUICommand`  
`class UUTBUICommand : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface shared by the native UI and by the UMG one

#### class `IUTBUICommand`  
`class IUTBUICommand`  
_L20-29_
- L24 _public prototype_ `virtual bool IsSupportingCommandClass(TSubclassOf<UUTBBaseCommand> CommandClass)=0;`
- L25 _public prototype_ `virtual void SetCommand(UUTBBaseCommand* Command)=0;`
- L26 _public prototype_ `virtual void ExecuteCurrentCommand()=0;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GetUI()=0;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBBaseUITab.h` (Public)


#### class `UUTBDefaultUITemplate`  
`class UUTBDefaultUITemplate : public UObject`  
_L22-30_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> BuildTabUI(UUserToolBoxBaseTab* Tab, const FUITemplateParameters& Params);`

#### class `UUTBToolBarTabUI`  
`class UUTBToolBarTabUI : public UUTBDefaultUITemplate`  
_L32-41_
- reflection: `UCLASS()`
- inherits: `UUTBDefaultUITemplate`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> BuildTabUI(UUserToolBoxBaseTab* Tab, const FUITemplateParameters& Params) override;`
- L39 _protected prototype_ `virtual TSharedPtr<FToolBarBuilder> GetBuilder(TSharedPtr<const FUICommandList> InCommandList, FMultiBoxCustomization InCustomization, TSharedPtr<FExtender> InExtender = nullptr, const bool InForceSmallIcons = false);`

#### class `UUTBPaletteTabUI`  
`class UUTBPaletteTabUI : public UUTBToolBarTabUI`  
_L43-49_
- reflection: `UCLASS()`
- inherits: `UUTBToolBarTabUI`
- L47 _protected prototype_ `virtual TSharedPtr<FToolBarBuilder> GetBuilder(TSharedPtr<const FUICommandList> InCommandList, FMultiBoxCustomization InCustomization, TSharedPtr<FExtender> InExtender = nullptr, const bool InForceSmallIcons = false)override;`

#### class `UUTBVerticalToolBarTabUI`  
`class UUTBVerticalToolBarTabUI : public UUTBToolBarTabUI`  
_L51-57_
- reflection: `UCLASS()`
- inherits: `UUTBToolBarTabUI`
- L55 _protected prototype_ `virtual TSharedPtr<FToolBarBuilder> GetBuilder(TSharedPtr<const FUICommandList> InCommandList, FMultiBoxCustomization InCustomization, TSharedPtr<FExtender> InExtender = nullptr, const bool InForceSmallIcons = false)override;`

#### class `UUTBSlimHorizontalToolBarTabUI`  
`class UUTBSlimHorizontalToolBarTabUI : public UUTBToolBarTabUI`  
_L59-65_
- reflection: `UCLASS()`
- inherits: `UUTBToolBarTabUI`
- L63 _protected prototype_ `virtual TSharedPtr<FToolBarBuilder> GetBuilder(TSharedPtr<const FUICommandList> InCommandList, FMultiBoxCustomization InCustomization, TSharedPtr<FExtender> InExtender = nullptr, const bool InForceSmallIcons = false)override;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBEditorBlueprint.h` (Public)


#### class `UUTBEditorBlueprint`  
`class UUTBEditorBlueprint : public UEditorUtilityBlueprint`  
_L13-17_
- reflection: `UCLASS()`
- inherits: `UEditorUtilityBlueprint`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UTBFactory.h` (Public)


#### class `UUTBEditorUtilityBlueprintFactory`  
`class UUTBEditorUtilityBlueprintFactory : public UFactory`  
_L13-18_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L17 _private prototype_ `virtual bool CanCreateNew() const override;`

#### class `UUTBCommandFactory`  
`class UUTBCommandFactory : public UFactory`  
_L21-30_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L24 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _private prototype_ `virtual bool CanCreateNew() const override;`
- L26 _private prototype_ `virtual bool ConfigureProperties() override;`
- L29 _private member_ `UClass* ParentClass;`

#### class `UUTBCommandTabFactory`  
`class UUTBCommandTabFactory : public UFactory`  
_L32-38_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L35 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L36 _private prototype_ `virtual bool CanCreateNew() const override;`

#### class `UIconTrackerFactory`  
`class UIconTrackerFactory : public UFactory`  
_L40-46_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L43 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L44 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UserToolBoxBaseBlueprint.h` (Public)


#### class `UUserToolBoxBaseBlueprint`  
`class UUserToolBoxBaseBlueprint : public UUTBBaseCommand`  
_L16-26_
- reflection: `UCLASS(Abstract, hideCategories=(Object),Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `UUTBBaseCommand`
- L23 _public prototype_ `void Command() ;` — `UFUNCTION(BlueprintImplementableEvent)`
- L25 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UserToolBoxCore.h` (Public)


#### class `FUserToolBoxCoreModule`  
`class FUserToolBoxCoreModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUserToolBoxCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUserToolBoxCore, Log, All);`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UserToolBoxStyle.h` (Public)


#### class `FUserToolBoxStyle`  
`class FUserToolBoxStyle`  
_L13-39_
- L17 _public prototype_ `static void Initialize();`
- L19 _public prototype_ `static void Shutdown();`
- L22 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L25 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Shooter game
- L27 _public prototype_ `static FName GetStyleSetName();`
- L28 _public prototype_ `static void AddExternalImageBrushes(const TArray<FIconInfo>& IconInfos);`
- L29 _public prototype_ `static TArray<FString> GetAvailableExternalImageBrushes();`
- L32 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L36 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`
- L37 _private member_ `static TArray<FString> ExternalBrushIds;`
- L38 _private member_ `static TMap<FString, TUniquePtr<FSlateImageBrush>> ExternalBrushes;`

### `Plugins/Experimental/UserToolBoxCore/Source/UserToolBoxCore/Public/UserToolBoxSubsystem.h` (Public)


#### class `UUserToolboxSubsystem`  
`class UUserToolboxSubsystem : public UEditorSubsystem`  
_L21-78_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UEditorSubsystem`
- L25 _private prototype_ `void RegisterTabData();` — `UFUNCTION(BlueprintCallable, Category="User Toolbox Subsystem")`
- L30 _public prototype_ `TArray<FAssetData> GetAvailableTabList();`
- L31 _public member_ `FOnTabChanged OnTabChanged;`
- L34 _public prototype_ `bool PickAnIcon(FString& OutValue);` — `UFUNCTION(BlueprintCallable,Category="User Toolbox")`
- L38 _private member_ `TMap<FString,TObjectPtr<UUserToolBoxBaseTab>> RegisteredTabs;` — `UPROPERTY()`
- L43 _public prototype_ `void RefreshIcons();` — `UFUNCTION(BlueprintCallable,Category="User Toolbox")`
- L47 _public prototype_ `TSharedPtr<SWidget> GenerateTabUI(const FAssetData Data, TSubclassOf<UUTBDefaultUITemplate> Ui=nullptr,const FUITemplateParameters& Parameters=FUITemplateParameters());`
- L51 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Implement this for initialization of instances of the system
- L53 _public prototype_ `virtual void Deinitialize() override;` — Implement this for deinitialization of instances of the system
- L55 _public prototype_ `TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& SpawnTabArgs);`
- L56 _public prototype_ `void ReinitializeUIs();`
- L58 _public member_ `static EAssetTypeCategories::Type AssetCategory;`
- L61 _private member_ `TArray<TPair<FString,FString>> Icons;`
- L63 _private member_ `TArray<TSharedPtr<FString>> IconOptions;`
- L66 _public prototype_ `void RegisterDrawer();`
- L67 _public prototype_ `void UpdateLevelViewportWidget();`
- L70 _private prototype_ `void OnAssetChanged(const FAssetData& InAssetData);`
- L73 _private member_ `FDelegateHandle OnFileLoadHandle;` — Delegate handle
- L75 _private member_ `TSharedPtr<SWidget> LevelViewportOverlayWdget;`
- L76 _private member_ `TArray<FName> RegisteredDrawer;`
- L77 _private member_ `TArray<FAssetData> AvailableTabList;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTabChanged, UUserToolBoxBaseTab*) UCLASS(BlueprintType) class UUserToolboxSubsystem : public UEditorSubsystem { GENERATED_BODY() UFUNCTION(BlueprintCallable, Category="User Toolbox Subsystem") void RegisterTabData(); public: TArray<FAssetData> GetAvailableTabList(); FOnTabChanged OnTabChanged; UFUNCTION(BlueprintCallable,Category="User Toolbox") bool PickAnIcon(FString& OutValue); private: UPROPERTY() TMap<FString,TObjectPtr<UUserToolBoxBaseTab>> RegisteredTabs; public: UFUNCTION(BlueprintCallable,Category="User Toolbox") void RefreshIcons(); TSharedPtr<SWidget> GenerateTabUI(const FAssetData Data, TSubclassOf<UUTBDefaultUITemplate> Ui=nullptr,const FUITemplateParameters& Parameters=FUITemplateParameters()); virtual void Initialize(FSubsystemCollectionBase& Collection) override; virtual void Deinitialize() override; TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& SpawnTabArgs); void ReinitializeUIs(); static EAssetTypeCategories::Type AssetCategory;`
