# Plugins / WebAPIEditor

- module root: `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor`
- headers: 70; symbols: 1325
- symbol kinds: class=84, delegate=10, enum=9, enumerator=30, function=200, member=366, namespace=27, prototype=543, struct=28, typedef=25, variable=3
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetRegistry, AssetTools, Core, CoreUObject, CurveEditor, DesktopPlatform, DeveloperSettings, EditorFramework, EditorStyle, EditorSubsystem, EditorWidgets, Engine, EngineSettings, GameProjectGeneration, GraphEditor, InputCore, Json, JsonUtilities, MessageLog, PluginBrowser, Projects, PropertyEditor, Sequencer, Slate, SlateCore, ToolMenus, UnrealEd, WebAPI
- PublicDependencyModuleNames: AssetTools, Core, CoreUObject, Engine, GraphEditor

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Assets/WebAPIDefinitionAssetEditorToolkit.h` (Private)


#### class `FWebAPIDefinitionAssetEditorToolkit`  
`class FWebAPIDefinitionAssetEditorToolkit : public FAssetEditorToolkit , public FEditorUndoClient`  
_L12-99_
- inherits: `FAssetEditorToolkit,FEditorUndoClient`
- L17 _public prototype_ `FWebAPIDefinitionAssetEditorToolkit();`
- L21 _public prototype_ `void Initialize(const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost, UWebAPIDefinition* InDefinition);` — Initializes the toolkit for the given WebAPI Definition.
- L24 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L25 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L26 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L27 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L31 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L32 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L36 _protected prototype_ `virtual void SetEditingObject(class UObject* InObject);`
- L37 _protected prototype_ `virtual void RegisterToolbar();`
- L40 _protected prototype_ `virtual void CreateEditorModeManager() override;`
- L46 _public prototype_ `void SetupCommands();` — Builds the toolbar widget.
- L47 _public prototype_ `void ExtendToolbar(const TSharedPtr<FExtender> InExtender);`
- L50 _public prototype_ `void Generate() const;` — Execute the Generate command.
- L53 _public prototype_ `FSlateIcon GetGenerateStatusImage() const;` — The icon representing the current status of the Generate command.
- L56 _public prototype_ `FText GetGenerateStatusTooltip() const;` — The tooltip for the current status of the Generate command.
- L61 _public member_ `static const FName DetailsTabID;` — Main details tab.
- L64 _public member_ `static const FName LogTabID;` — MessageLog tab.
- L67 _public member_ `static const FName CodeTabID;` — Code view tab.
- L71 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) const;` — Main details tab.
- L74 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Log(const FSpawnTabArgs& Args) const;` — MessageLog tab.
- L77 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Code(const FSpawnTabArgs& Args) const;` — Code view tab.
- L80 _protected member_ `static constexpr const TCHAR* LogName = TEXT("Ass`
- L83 _protected member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View.
- L86 _protected member_ `TSharedPtr<class SWebAPIMessageLog> LogView;` — Log View.
- L89 _protected member_ `TSharedPtr<class FWebAPICodeViewModel> CodeViewModel;` — Code ViewModel.
- L92 _protected member_ `TSharedPtr<class SWebAPICodeView> CodeView;` — Code View.
- L95 _protected member_ `TSharedPtr<FLayoutExtender> LayoutExtender;` — Extender for adding to the default layout for this asset editor
- L98 _protected member_ `TStrongObjectPtr<UWebAPIDefinition> Definition;` — The WebAPI Definition being edited.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Assets/WebAPIDefinitionAssetTypeActions.h` (Private)


#### class `FWebAPIDefinitionAssetTypeActions`  
`class FWebAPIDefinitionAssetTypeActions : public FAssetTypeActions_Base`  
_L7-18_
- inherits: `FAssetTypeActions_Base`
- L12 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L13 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L14 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L15 _public prototype_ `virtual uint32 GetCategories() override;`
- L16 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> InEditWithinLevelEditor) override;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPICodeViewModel.h` (Private)


#### class `FWebAPICodeViewModel`  
`class FWebAPICodeViewModel : public TSharedFromThis<FWebAPICodeViewModel> , public IWebAPIViewModel`  
_L7-42_
- inherits: `TSharedFromThis<FWebAPICodeViewModel>,IWebAPIViewModel`
- L12 _public prototype_ `static TSharedRef<FWebAPICodeViewModel> Create(UWebAPIDefinition* InDefinition);`
- L13 _public prototype_ `virtual ~FWebAPICodeViewModel() = default;`
- L15 _public function_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override`
- L16 _public function_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override`
- L17 _public function_ `virtual int32 GetIndex() const override`
- L18 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L20 _public function_ `const TWeakObjectPtr<UWebAPIDefinition>& GetDefinition() const`
- L22 _public prototype_ `FText GetCodeText() const;`
- L23 _public prototype_ `void SetCodeText(const FText& InCodeText) const;`
- L26 _public prototype_ `virtual bool IsValid() const override;` — Checks validity of this ViewModel
- L33 _public prototype_ `FWebAPICodeViewModel(FPrivateToken);`
- L34 _public prototype_ `FWebAPICodeViewModel(FPrivateToken, UWebAPIDefinition* InDefinition);`
- L37 _private prototype_ `void Initialize();`
- L40 _private member_ `TWeakObjectPtr<UWebAPIDefinition> Definition;`
- L41 _private member_ `TSharedPtr<FText> CodeContents;`

#### struct `FWebAPICodeViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L30-30_
- desc: Private token only allows members or friends to call MakeShared
- L30 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIEnumViewModel.h` (Private)


#### class `FWebAPIEnumValueViewModel`  
`class FWebAPIEnumValueViewModel : public TSharedFromThis<FWebAPIEnumValueViewModel> , public IWebAPIViewModel`  
_L10-44_
- inherits: `TSharedFromThis<FWebAPIEnumValueViewModel>,IWebAPIViewModel`
- L15 _public prototype_ `static TSharedRef<FWebAPIEnumValueViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIEnumValue* InValue, int32 InIndex = -1);`
- L17 _public prototype_ `virtual ~FWebAPIEnumValueViewModel() = default;`
- L19 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L20 _public function_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override`
- L21 _public function_ `virtual int32 GetIndex() const override`
- L22 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L24 _public function_ `FString GetValue() const`
- L27 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L34 _public function_ `FWebAPIEnumValueViewModel(FPrivateToken)`
- L35 _public prototype_ `FWebAPIEnumValueViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIEnumValue* InValue, int32 InIndex = -1);`
- L38 _private prototype_ `void Initialize();`
- L41 _private member_ `TSharedPtr<IWebAPIViewModel> Enum;`
- L42 _private member_ `TWeakObjectPtr<UWebAPIEnumValue> Value;`
- L43 _private member_ `int32 Index = 0;`

#### struct `FWebAPIEnumValueViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L31-31_
- desc: Private token only allows members or friends to call MakeShared
- L31 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### class `FWebAPIEnumViewModel`  
`class FWebAPIEnumViewModel : public TSharedFromThis<FWebAPIEnumViewModel> , public IWebAPIViewModel`  
_L46-83_
- inherits: `TSharedFromThis<FWebAPIEnumViewModel>,IWebAPIViewModel`
- L51 _public prototype_ `static TSharedRef<FWebAPIEnumViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIEnum* InEnum, int32 InIndex = -1);`
- L52 _public prototype_ `virtual ~FWebAPIEnumViewModel() = default;`
- L54 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L55 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L56 _public function_ `virtual int32 GetIndex() const override`
- L57 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L59 _public prototype_ `bool GetShouldGenerate() const;`
- L60 _public function_ `const TArray<TSharedPtr<FWebAPIEnumValueViewModel>>& GetValues() const`
- L63 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L70 _public function_ `FWebAPIEnumViewModel(FPrivateToken)`
- L71 _public prototype_ `FWebAPIEnumViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIEnum* InEnum, int32 InIndex = -1);`
- L74 _private prototype_ `void Initialize();`
- L79 _private member_ `TSharedPtr<IWebAPIViewModel> Schema;`
- L80 _private member_ `TWeakObjectPtr<UWebAPIEnum> Enum;`
- L81 _private member_ `TArray<TSharedPtr<FWebAPIEnumValueViewModel>> Values;`
- L82 _private member_ `int32 Index = 0;`

#### struct `FWebAPIEnumViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L67-67_
- desc: Private token only allows members or friends to call MakeShared
- L67 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIModelViewModel.h` (Private)


#### class `FWebAPIPropertyViewModel`  
`class FWebAPIPropertyViewModel : public TSharedFromThis<FWebAPIPropertyViewModel> , public IWebAPIViewModel`  
_L11-53_
- inherits: `TSharedFromThis<FWebAPIPropertyViewModel>,IWebAPIViewModel`
- L16 _public prototype_ `static TSharedRef<FWebAPIPropertyViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIProperty* InProperty, int32 InIndex = -1);`
- L17 _public prototype_ `virtual ~FWebAPIPropertyViewModel() = default;`
- L19 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L20 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L21 _public function_ `virtual int32 GetIndex() const override`
- L22 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L23 _public prototype_ `virtual bool HasCodeText() const override;`
- L24 _public prototype_ `virtual FText GetCodeText() const override;`
- L26 _public function_ `const TSharedPtr<IWebAPIViewModel>& GetModel() const`
- L27 _public prototype_ `FSlateColor GetPinColor() const;`
- L29 _public prototype_ `bool IsArray() const;`
- L32 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L39 _public function_ `FWebAPIPropertyViewModel(FPrivateToken)`
- L40 _public prototype_ `FWebAPIPropertyViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIProperty* InProperty, int32 InIndex = -1);`
- L43 _private prototype_ `void Initialize();`
- L46 _private member_ `TSharedPtr<IWebAPIViewModel> Model;`
- L47 _private member_ `TWeakObjectPtr<UWebAPIProperty> Property;`
- L50 _private member_ `TSharedPtr<IWebAPIViewModel> NestedModel;` — Optional nested model to display, if this properties type had to be uniquely generated and has two or more members.
- L52 _private member_ `int32 Index = 0;`

#### struct `FWebAPIPropertyViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L36-36_
- desc: Private token only allows members or friends to call MakeShared
- L36 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### class `FWebAPIModelViewModel`  
`class FWebAPIModelViewModel : public TSharedFromThis<FWebAPIModelViewModel> , public IWebAPIViewModel`  
_L55-92_
- inherits: `TSharedFromThis<FWebAPIModelViewModel>,IWebAPIViewModel`
- L60 _public prototype_ `static TSharedRef<FWebAPIModelViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIModel* InModel, int32 InIndex = -1);`
- L61 _public prototype_ `virtual ~FWebAPIModelViewModel() = default;`
- L63 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L64 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L65 _public function_ `virtual int32 GetIndex() const override`
- L66 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L67 _public prototype_ `virtual bool HasCodeText() const override;`
- L68 _public prototype_ `virtual FText GetCodeText() const override;`
- L70 _public prototype_ `bool GetShouldGenerate() const;`
- L71 _public function_ `const TArray<TSharedPtr<FWebAPIPropertyViewModel>>& GetProperties() const`
- L74 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L81 _public function_ `FWebAPIModelViewModel(FPrivateToken)`
- L82 _public prototype_ `FWebAPIModelViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIModel* InModel, int32 InIndex = -1);`
- L85 _private prototype_ `void Initialize();`
- L88 _private member_ `TSharedPtr<IWebAPIViewModel> Schema;`
- L89 _private member_ `TWeakObjectPtr<UWebAPIModel> Model;`
- L90 _private member_ `TArray<TSharedPtr<FWebAPIPropertyViewModel>> Properties;`
- L91 _private member_ `int32 Index = 0;`

#### struct `FWebAPIModelViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L78-78_
- desc: Private token only allows members or friends to call MakeShared
- L78 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIOperationParameterViewModel.h` (Private)


#### class `FWebAPIOperationParameterViewModel`  
`class FWebAPIOperationParameterViewModel : public TSharedFromThis<FWebAPIOperationParameterViewModel> , public IWebAPIViewModel`  
_L16-52_
- inherits: `TSharedFromThis<FWebAPIOperationParameterViewModel>,IWebAPIViewModel`
- L21 _public prototype_ `static TSharedRef<FWebAPIOperationParameterViewModel> Create(const TSharedRef<FWebAPIOperationRequestViewModel>& InParentViewModel, UWebAPIOperationParameter* InParameter, int32 InIndex = -1);`
- L22 _public prototype_ `virtual ~FWebAPIOperationParameterViewModel() = default;`
- L24 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L25 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L26 _public function_ `virtual int32 GetIndex() const override`
- L27 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L29 _public function_ `const TSharedPtr<FWebAPIOperationRequestViewModel>& GetRequest() const`
- L30 _public prototype_ `FSlateColor GetPinColor() const;`
- L32 _public prototype_ `bool IsArray() const;`
- L35 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L42 _public function_ `FWebAPIOperationParameterViewModel(FPrivateToken)`
- L43 _public prototype_ `FWebAPIOperationParameterViewModel(FPrivateToken, const TSharedRef<FWebAPIOperationRequestViewModel>& InParentViewModel, UWebAPIOperationParameter* InParameter, int32 InIndex = -1);`
- L46 _private prototype_ `void Initialize();`
- L49 _private member_ `TSharedPtr<FWebAPIOperationRequestViewModel> Request;`
- L50 _private member_ `TWeakObjectPtr<UWebAPIOperationParameter> Parameter;`
- L51 _private member_ `int32 Index;`

#### struct `FWebAPIOperationParameterViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L39-39_
- desc: Private token only allows members or friends to call MakeShared
- L39 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIOperationRequestViewModel.h` (Private)


#### class `FWebAPIOperationRequestViewModel`  
`class FWebAPIOperationRequestViewModel : public TSharedFromThis<FWebAPIOperationRequestViewModel> , public IWebAPIViewModel`  
_L16-52_
- inherits: `TSharedFromThis<FWebAPIOperationRequestViewModel>,IWebAPIViewModel`
- desc: Encapsulates a single Operation Request, containing one or more parameters.
- L21 _public prototype_ `static TSharedRef<FWebAPIOperationRequestViewModel> Create(const TSharedRef<FWebAPIOperationViewModel>& InParentViewModel, UWebAPIOperation* InOperation, int32 InIndex = -1);`
- L22 _public prototype_ `virtual ~FWebAPIOperationRequestViewModel() = default;`
- L24 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L25 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L26 _public function_ `virtual int32 GetIndex() const override`
- L27 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L28 _public function_ `const TArray<TSharedPtr<FWebAPIOperationParameterViewModel>>& GetParameters() const`
- L29 _public function_ `bool HasBody() const`
- L30 _public function_ `const TSharedPtr<FWebAPIModelViewModel>& GetBody() const`
- L33 _public prototype_ `virtual bool IsValid() const override;` — Checks validity of this ViewModel
- L40 _public function_ `FWebAPIOperationRequestViewModel(FPrivateToken)`
- L41 _public prototype_ `FWebAPIOperationRequestViewModel(FPrivateToken, const TSharedRef<FWebAPIOperationViewModel>& InParentViewModel, UWebAPIOperation* InOperation, int32 InIndex = -1);`
- L44 _private prototype_ `void Initialize();`
- L47 _private member_ `TSharedPtr<FWebAPIOperationViewModel> Operation;`
- L48 _private member_ `TWeakObjectPtr<UWebAPIOperation> OperationObject;`
- L49 _private member_ `TArray<TSharedPtr<FWebAPIOperationParameterViewModel>> Parameters;`
- L50 _private member_ `TSharedPtr<FWebAPIModelViewModel> Body;` — Re-use Model VM
- L51 _private member_ `int32 Index;`

#### struct `FWebAPIOperationRequestViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L37-37_
- desc: Private token only allows members or friends to call MakeShared
- L37 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIOperationResponseViewModel.h` (Private)


#### class `FWebAPIOperationResponseViewModel`  
`class FWebAPIOperationResponseViewModel : public TSharedFromThis<FWebAPIOperationResponseViewModel> , public IWebAPIViewModel`  
_L12-46_
- inherits: `TSharedFromThis<FWebAPIOperationResponseViewModel>,IWebAPIViewModel`
- L17 _public prototype_ `static TSharedRef<FWebAPIOperationResponseViewModel> Create(const TSharedRef<FWebAPIOperationViewModel>& InParentViewModel, UWebAPIOperationResponse* InResponse, int32 InIndex = -1);`
- L18 _public prototype_ `virtual ~FWebAPIOperationResponseViewModel() = default;`
- L20 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L21 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L22 _public function_ `virtual int32 GetIndex() const override`
- L23 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L25 _public prototype_ `const FText& GetDescription() const;`
- L28 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L35 _public function_ `FWebAPIOperationResponseViewModel(FPrivateToken)`
- L36 _public prototype_ `FWebAPIOperationResponseViewModel(FPrivateToken, const TSharedRef<FWebAPIOperationViewModel>& InParentViewModel, UWebAPIOperationResponse* InResponse, int32 InIndex = -1);`
- L39 _private prototype_ `void Initialize();`
- L42 _private member_ `TSharedPtr<FWebAPIOperationViewModel> Operation;`
- L43 _private member_ `TWeakObjectPtr<UWebAPIOperationResponse> Response;`
- L44 _private member_ `int32 Index;`
- L45 _private member_ `FText CachedDescription;`

#### struct `FWebAPIOperationResponseViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L32-32_
- desc: Private token only allows members or friends to call MakeShared
- L32 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIOperationViewModel.h` (Private)


#### class `FWebAPIOperationViewModel`  
`class FWebAPIOperationViewModel : public TSharedFromThis<FWebAPIOperationViewModel> , public IWebAPIViewModel`  
_L12-59_
- inherits: `TSharedFromThis<FWebAPIOperationViewModel>,IWebAPIViewModel`
- L17 _public prototype_ `static TSharedRef<FWebAPIOperationViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIOperation* InOperation, int32 InIndex = -1);`
- L18 _public prototype_ `virtual ~FWebAPIOperationViewModel() = default;`
- L20 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L21 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L22 _public function_ `virtual int32 GetIndex() const override`
- L23 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L24 _public prototype_ `virtual bool HasCodeText() const override;`
- L25 _public prototype_ `virtual FText GetCodeText() const override;`
- L27 _public prototype_ `bool GetShouldGenerate(bool bInherit = true) const;`
- L28 _public prototype_ `void SetShouldGenerate(bool bInShouldGenerate) const;`
- L29 _public prototype_ `TSharedPtr<FWebAPIServiceViewModel> GetService() const;`
- L30 _public function_ `const FText& GetVerb() const`
- L31 _public function_ `const FText& GetPath() const`
- L32 _public function_ `const FText& GetRichPath() const`
- L33 _public function_ `const TArray<TSharedPtr<FWebAPIOperationRequestViewModel>>& GetRequests() const`
- L34 _public function_ `const TArray<TSharedPtr<FWebAPIOperationResponseViewModel>>& GetResponses() const`
- L37 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L44 _public function_ `FWebAPIOperationViewModel(FPrivateToken)`
- L45 _public prototype_ `FWebAPIOperationViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIOperation* InOperation, int32 InIndex = -1);`
- L48 _private prototype_ `void Initialize();`
- L51 _private member_ `TSharedPtr<IWebAPIViewModel> Service;`
- L52 _private member_ `TWeakObjectPtr<UWebAPIOperation> Operation;`
- L53 _private member_ `TArray<TSharedPtr<FWebAPIOperationRequestViewModel>> Requests;`
- L54 _private member_ `TArray<TSharedPtr<FWebAPIOperationResponseViewModel>> Responses;`
- L55 _private member_ `int32 Index;`
- L56 _private member_ `FText VerbLabel;`
- L57 _private member_ `FText PathLabel;`
- L58 _private member_ `FText RichPathLabel;`

#### struct `FWebAPIOperationViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L41-41_
- desc: Private token only allows members or friends to call MakeShared
- L41 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIParameterViewModel.h` (Private)


#### class `FWebAPIParameterViewModel`  
`class FWebAPIParameterViewModel : public TSharedFromThis<FWebAPIParameterViewModel> , public IWebAPIViewModel`  
_L15-58_
- inherits: `TSharedFromThis<FWebAPIParameterViewModel>,IWebAPIViewModel`
- L20 _public prototype_ `static TSharedRef<FWebAPIParameterViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIParameter* InParameter, int32 InIndex = -1);`
- L21 _public prototype_ `virtual ~FWebAPIParameterViewModel() = default;`
- L23 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L24 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L25 _public function_ `virtual int32 GetIndex() const override`
- L26 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L27 _public prototype_ `virtual bool HasCodeText() const override;`
- L28 _public prototype_ `virtual FText GetCodeText() const override;`
- L30 _public prototype_ `bool GetShouldGenerate() const;`
- L31 _public function_ `const TSharedPtr<FWebAPIPropertyViewModel>& GetProperty() const`
- L33 _public prototype_ `bool IsArray() const;`
- L36 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L43 _public function_ `FWebAPIParameterViewModel(FPrivateToken)`
- L44 _public prototype_ `FWebAPIParameterViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIParameter* InParameter, int32 InIndex = -1);`
- L47 _private prototype_ `void Initialize();`
- L50 _private member_ `TSharedPtr<IWebAPIViewModel> Schema;`
- L51 _private member_ `TWeakObjectPtr<UWebAPIParameter> Parameter;`
- L52 _private member_ `TSharedPtr<FWebAPIPropertyViewModel> Property;`
- L55 _private member_ `TSharedPtr<IWebAPIViewModel> NestedModel;` — Optional nested model to display, if this properties type had to be uniquely generated and has two or more members.
- L57 _private member_ `int32 Index;`

#### struct `FWebAPIParameterViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L40-40_
- desc: Private token only allows members or friends to call MakeShared
- L40 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIServiceViewModel.h` (Private)


#### class `FWebAPIServiceViewModel`  
`class FWebAPIServiceViewModel : public TSharedFromThis<FWebAPIServiceViewModel> , public IWebAPIViewModel`  
_L10-45_
- inherits: `TSharedFromThis<FWebAPIServiceViewModel>,IWebAPIViewModel`
- L15 _public prototype_ `static TSharedRef<FWebAPIServiceViewModel> Create(const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIService* InService, int32 InIndex = -1);`
- L16 _public prototype_ `virtual ~FWebAPIServiceViewModel() = default;`
- L18 _public function_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override`
- L19 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L20 _public function_ `virtual int32 GetIndex() const override`
- L21 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L23 _public prototype_ `bool GetShouldGenerate() const;`
- L24 _public prototype_ `void SetShouldGenerate(bool bInShouldGenerate) const;`
- L25 _public function_ `const TArray<TSharedPtr<FWebAPIOperationViewModel>>& GetOperations() const`
- L28 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L35 _public function_ `FWebAPIServiceViewModel(FPrivateToken)`
- L36 _public prototype_ `FWebAPIServiceViewModel(FPrivateToken, const TSharedRef<IWebAPIViewModel>& InParentViewModel, UWebAPIService* InService, int32 InIndex = -1);`
- L39 _private prototype_ `void Initialize();`
- L42 _private member_ `TWeakObjectPtr<UWebAPIService> Service;`
- L43 _private member_ `TArray<TSharedPtr<FWebAPIOperationViewModel>> Operations;`
- L44 _private member_ `int32 Index;`

#### struct `FWebAPIServiceViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L32-32_
- desc: Private token only allows members or friends to call MakeShared
- L32 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIViewModel.h` (Private)


#### class `IWebAPIViewModel`  
`class IWebAPIViewModel`  
_L30-92_
- desc: Common interface for View Models.
- L33 _protected prototype_ `~IWebAPIViewModel() = default;`
- L37 _public prototype_ `virtual TSharedPtr<class IWebAPIViewModel> GetParent() = 0;` — Get Parent ViewModel, if any.
- L41 _public prototype_ `template <typename ModelType> TSharedPtr<ModelType> GetParent();` — Get Parent ViewModel of ModelType, if any.
- L44 _public function_ `virtual FText GetLabel()` — Get Label Text.
- L47 _public function_ `virtual FText GetTooltip()` — Get Tooltip Text.
- L50 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) = 0;` — See STreeView::OnGetChildren, return false if no children.
- L53 _public prototype_ `virtual int32 GetIndex() const = 0;` — Get the index of this element, if applicable.
- L56 _public prototype_ `virtual const FName& GetViewModelTypeName() = 0;` — Get the ViewModel type name.
- L59 _public function_ `virtual bool ShouldExpandByDefault()` — Whether this ViewModel should be initially expanded in a treeview.
- L62 _public function_ `virtual void Refresh()` — Rebuild the ViewModel.
- L65 _public prototype_ `virtual bool IsValid() const = 0;` — Checks validity of this ViewModel
- L68 _public function_ `virtual bool HasCodeText() const` — Check if this viewmodel context contains any code to display.
- L71 _public prototype_ `virtual FText GetCodeText() const;` — Get code text, if present.
- L74 _public member_ `static FName NAME_Definition;`
- L75 _public member_ `static FName NAME_Schema;`
- L76 _public member_ `static FName NAME_Model;`
- L77 _public member_ `static FName NAME_Property;`
- L78 _public member_ `static FName NAME_Enum;`
- L79 _public member_ `static FName NAME_EnumValue;`
- L80 _public member_ `static FName NAME_Parameter;`
- L81 _public member_ `static FName NAME_Service;`
- L82 _public member_ `static FName NAME_Operation;`
- L83 _public member_ `static FName NAME_OperationRequest;`
- L84 _public member_ `static FName NAME_OperationParameter;`
- L85 _public member_ `static FName NAME_OperationResponse;`
- L86 _public member_ `static FName NAME_Code;`
- L87 _public member_ `static FName NAME_MessageLog;`
- L90 _protected member_ `FText CachedLabel;`
- L91 _protected member_ `FText CachedTooltip;`
- L95 _function_ `template <class ModelType> TSharedPtr<ModelType> IWebAPIViewModel::GetParent()`

#### class `FWebAPIDefinitionViewModel`  
`class FWebAPIDefinitionViewModel : public TSharedFromThis<FWebAPIDefinitionViewModel> , public IWebAPIViewModel`  
_L112-150_
- inherits: `TSharedFromThis<FWebAPIDefinitionViewModel>,IWebAPIViewModel`
- L117 _public prototype_ `static TSharedRef<FWebAPIDefinitionViewModel> Create(UWebAPIDefinition* InDefinition);`
- L118 _public prototype_ `virtual ~FWebAPIDefinitionViewModel() = default;`
- L120 _public function_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override`
- L121 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L122 _public function_ `virtual int32 GetIndex() const override`
- L123 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L125 _public function_ `const TWeakObjectPtr<UWebAPIDefinition>& GetDefinition() const`
- L126 _public function_ `TSharedPtr<FWebAPISchemaViewModel> GetSchema() const`
- L129 _public prototype_ `virtual void Refresh() override;` — Rebuild the ViewModel.
- L131 _public prototype_ `bool IsSameDefinition(UObject* InObject) const;`
- L134 _public prototype_ `virtual bool IsValid() const override;` — Checks validity of this ViewModel
- L141 _public function_ `FWebAPIDefinitionViewModel(FPrivateToken)`
- L142 _public prototype_ `FWebAPIDefinitionViewModel(FPrivateToken, UWebAPIDefinition* InDefinition);`
- L145 _private prototype_ `void Initialize();`
- L148 _private member_ `TWeakObjectPtr<UWebAPIDefinition> Definition;`
- L149 _private member_ `TSharedPtr<FWebAPISchemaViewModel> Schema;`

#### struct `FWebAPIDefinitionViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L138-138_
- desc: Private token only allows members or friends to call MakeShared
- L138 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### class `FWebAPISchemaViewModel`  
`class FWebAPISchemaViewModel : public TSharedFromThis<FWebAPISchemaViewModel> , public IWebAPIViewModel`  
_L152-193_
- inherits: `TSharedFromThis<FWebAPISchemaViewModel>,IWebAPIViewModel`
- L157 _public prototype_ `static TSharedRef<FWebAPISchemaViewModel> Create(const TSharedRef<FWebAPIDefinitionViewModel>& InParentViewModel, UWebAPISchema* InSchema);`
- L158 _public prototype_ `virtual ~FWebAPISchemaViewModel() = default;`
- L160 _public prototype_ `virtual TSharedPtr<IWebAPIViewModel> GetParent() override;`
- L161 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IWebAPIViewModel>>& OutChildren) override;`
- L162 _public function_ `virtual int32 GetIndex() const override`
- L163 _public function_ `virtual const FName& GetViewModelTypeName() override`
- L165 _public function_ `const TArray<TSharedPtr<FWebAPIServiceViewModel>>& GetServices() const`
- L166 _public function_ `const TArray<TSharedPtr<IWebAPIViewModel>>& GetModels() const`
- L169 _public prototype_ `virtual void Refresh() override;` — Rebuild the ViewModel.
- L172 _public function_ `virtual bool ShouldExpandByDefault() override` — Whether this ViewModel should be initially expanded.
- L175 _public function_ `virtual bool IsValid() const override` — Checks validity of this ViewModel
- L182 _public function_ `FWebAPISchemaViewModel(FPrivateToken)`
- L183 _public prototype_ `FWebAPISchemaViewModel(FPrivateToken, const TSharedRef<FWebAPIDefinitionViewModel>& InParentViewModel, UWebAPISchema* InSchema);`
- L186 _private prototype_ `void Initialize();`
- L189 _private member_ `TSharedPtr<FWebAPIDefinitionViewModel> Definition;`
- L190 _private member_ `TWeakObjectPtr<UWebAPISchema> Schema;`
- L191 _private member_ `TArray<TSharedPtr<FWebAPIServiceViewModel>> Services;`
- L192 _private member_ `TArray<TSharedPtr<IWebAPIViewModel>> Models;`

#### struct `FWebAPISchemaViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L179-179_
- desc: Private token only allows members or friends to call MakeShared
- L179 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace WebAPI` (scope `UE`)
- L21 _namespace_ `namespace Details` (scope `UE::WebAPI`)
- L24 _prototype_ `template <class ParentViewModelType = IWebAPIViewModel, class ViewModelType = IWebAPIViewModel> TSharedPtr<ViewModelType> CreateViewModel(const TSharedRef<ParentViewModelType>& InParentViewModel, UObject* InModel);` (scope `UE::WebAPI::Details`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/ViewModels/WebAPIViewModel.inl` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace WebAPI` (scope `UE`)
- L14 _namespace_ `namespace Details` (scope `UE::WebAPI`)
- L17 _function_ `template <class ParentViewModelType, class ViewModelType> TSharedPtr<ViewModelType> CreateViewModel(const TSharedRef<ParentViewModelType>& InParentViewModel, UObject* InModel)` (scope `UE::WebAPI::Details`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/WebAPIDefinitionDetailsCustomization.h` (Private)


#### class `FWebAPIDefinitionDetailsCustomization`  
`class FWebAPIDefinitionDetailsCustomization : public IDetailCustomization`  
_L20-69_
- inherits: `IDetailCustomization`
- L24 _public typedef_ `using FTreeItemType = TSharedPtr<IWebAPIViewModel>;`
- L26 _public prototype_ `FWebAPIDefinitionDetailsCustomization();`
- L30 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailsCustomization interface
- L36 _public prototype_ `static FOnWebAPISchemaObjectSelected& OnSchemaObjectSelected();` — Global delegate for WebAPI schema object selection in the UI.
- L39 _protected prototype_ `void OnAssetImported(UObject* InObject) const;`
- L40 _protected prototype_ `void GetChildren(FTreeItemType InObject, TArray<FTreeItemType>& OutChildren);`
- L43 _protected prototype_ `void Refresh() const;` — Call when ViewModel has regenerated
- L44 _protected prototype_ `void RefreshTreeView() const;`
- L47 _protected prototype_ `void OnServiceSelectionChanged(FTreeItemType InObject, ESelectInfo::Type InSelectInfo) const;` — Called when the item selection changes in the services tree view.
- L50 _protected prototype_ `void OnModelSelectionChanged(FTreeItemType InObject, ESelectInfo::Type InSelectInfo) const;` — Called when the item selection changes in the models tree view.
- L52 _protected prototype_ `void OnDefinitionReimported(UObject* InObject) const;`
- L56 _private member_ `TSharedPtr<FWebAPIDefinitionViewModel> RootViewModel;` — View Model for the current Definition, contains reference to WebAPIDefinition.
- L59 _private member_ `TArray<FTreeItemType> ServicesTreeViewContext;` — WebAPISchema services for use by TreeView.
- L62 _private member_ `TSharedPtr<SWebAPITreeView> ServicesTreeView;` — WebAPISchema services TreeView Widget.
- L65 _private member_ `TArray<FTreeItemType> ModelsTreeViewContext;` — WebAPISchema models for use by TreeView.
- L68 _private member_ `TSharedPtr<SWebAPITreeView> ModelsTreeView;` — WebAPISchema models TreeView Widget.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWebAPISchemaObjectSelected, const TWeakObjectPtr<UWebAPIDefinition>&, const TSharedPtr<IWebAPIViewModel>&);` — Invoked when an object is selected in a tree view (service, model, etc.).
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWebAPISchemaObjectSelected, const TWeakObjectPtr<UWebAPIDefinition>&, const TSharedPtr<IWebAPIViewModel>&);` — Invoked when an object is selected in a tree view (service, model, etc.).

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/WebAPIDefinitionTargetModuleCustomization.h` (Private)


#### class `FWebAPIDefinitionTargetModuleCustomization`  
`class FWebAPIDefinitionTargetModuleCustomization : public IPropertyTypeCustomization`  
_L8-40_
- inherits: `IPropertyTypeCustomization`
- desc: Property customization for FWebAPIDefinitionTargetModule
- L12 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Root property handle.
- L27 _private member_ `TSharedPtr<IPropertyHandle> NamePropertyHandle;` — Property handle for Name.
- L30 _private member_ `TSharedPtr<IPropertyHandle> PathPropertyHandle;` — Property handle for AbsolutePath.
- L33 _private prototype_ `void OnAddModule();` — Called when the "Add Module" button is pressed.
- L36 _private prototype_ `bool CanAddModule() const;` — Returns true if the "Add Module" button can be pressed.
- L39 _private prototype_ `FText GetAddModuleTooltip() const;` — The tooltip attribute for the "Add Module" button.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPICodeView.h` (Private)


#### class `SWebAPICodeView`  
`class SWebAPICodeView : public SCompoundWidget`  
_L10-28_
- inherits: `SCompoundWidget`
- desc: Shows the generated code for the selected object.
- L13 _public function_ `SLATE_BEGIN_ARGS(SWebAPICodeView)`
- L17 _public prototype_ `SWebAPICodeView();`
- L18 _public prototype_ `virtual ~SWebAPICodeView();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPICodeViewModel>& InViewModel);` — Constructs this widget with InArgs
- L24 _protected prototype_ `void OnSchemaObjectSelected(const TWeakObjectPtr<class UWebAPIDefinition>& InDefinition, const TSharedPtr<class IWebAPIViewModel>& InSchemaObjectViewModel) const;`
- L27 _private member_ `TSharedPtr<FWebAPICodeViewModel> CodeView;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPIMessageLog.h` (Private)


#### class `SWebAPIMessageLog`  
`class SWebAPIMessageLog : public SCompoundWidget`  
_L12-27_
- inherits: `SCompoundWidget`
- desc: Lists WebAPI log entries.
- L15 _public function_ `SLATE_BEGIN_ARGS(SWebAPIMessageLog)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIMessageLog>& InMessageLog);`
- L24 _private member_ `TSharedPtr<SWidget> LogListingWidget;` — Pointer to log widget
- L26 _private member_ `TSharedPtr<FWebAPIMessageLog> MessageLog;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPIModulePicker.h` (Private)


#### class `SWebAPIModulePicker`  
`class SWebAPIModulePicker : public SCompoundWidget`  
_L20-68_
- inherits: `SCompoundWidget`
- desc: A widget to select a target module or plugin for generated files.
- L23 _public function_ `SLATE_BEGIN_ARGS(SWebAPIModulePicker)`
- L26 _public prototype_ `SLATE_ARGUMENT(FString, ModuleName) SLATE_EVENT(FOnModuleChanged, OnModuleChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The module initially provided.
- L36 _public prototype_ `void Refresh();` — Refreshes the list of available modules, accounting for any added or removed.
- L40 _private prototype_ `FText GetSelectedModuleComboText() const;` — Get the combo box text for the currently selected module
- L43 _private prototype_ `void SelectedModuleComboBoxSelectionChanged(TSharedPtr<FModuleContextInfo> InValue, ESelectInfo::Type InSelectInfo);` — Called when the currently selected module is changed
- L46 _private prototype_ `TSharedRef<SWidget> MakeWidgetForSelectedModuleCombo(TSharedPtr<FModuleContextInfo> InValue) const;` — Create the widget to use as the combo box entry for the given module info
- L49 _private prototype_ `void OnModuleCreated(FString InModuleName);` — When a module/plugin is newly created.
- L53 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FModuleContextInfo>>> AvailableModulesCombo;` — The available modules combo box
- L56 _private member_ `static FString LastSelectedModuleName;` — The last selected module name. Meant to keep the same module selected after first selection
- L59 _private member_ `FString ModuleName;` — The ModuleName chosen.
- L62 _private member_ `TArray<TSharedPtr<FModuleContextInfo>> AvailableModules;` — Information about the currently available modules for this project
- L65 _private member_ `TSharedPtr<FModuleContextInfo> SelectedModuleInfo;` — Information about the currently selected module; used for class validation
- L67 _private member_ `FOnModuleChanged OnModuleChanged;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ESelectInfo`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnModuleChanged, const FString& , const FString& );`
- L17 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnModuleChanged, const FString& , const FString& );`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaEnumRow.h` (Private)


#### class `SWebAPISchemaEnumRow`  
`class SWebAPISchemaEnumRow : public SWebAPISchemaTreeTableRow<FWebAPIEnumViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIEnumViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaEnumRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIEnumViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaEnumValueRow.h` (Private)


#### class `SWebAPISchemaEnumValueRow`  
`class SWebAPISchemaEnumValueRow : public SWebAPISchemaTreeTableRow<FWebAPIEnumValueViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIEnumValueViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaEnumValueRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIEnumValueViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaModelRow.h` (Private)


#### class `SWebAPISchemaModelRow`  
`class SWebAPISchemaModelRow : public SWebAPISchemaTreeTableRow<FWebAPIModelViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIModelViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaModelRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIModelViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaOperationParameterRow.h` (Private)


#### class `SWebAPISchemaOperationParameterRow`  
`class SWebAPISchemaOperationParameterRow : public SWebAPISchemaTreeTableRow<FWebAPIOperationParameterViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIOperationParameterViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaOperationParameterRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIOperationParameterViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaOperationRequestRow.h` (Private)


#### class `SWebAPISchemaOperationRequestRow`  
`class SWebAPISchemaOperationRequestRow : public SWebAPISchemaTreeTableRow<FWebAPIOperationRequestViewModel>`  
_L14-24_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIOperationRequestViewModel>`
- L18 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaOperationRequestRow)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIOperationRequestViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaOperationResponseRow.h` (Private)


#### class `SWebAPISchemaOperationResponseRow`  
`class SWebAPISchemaOperationResponseRow : public SWebAPISchemaTreeTableRow<FWebAPIOperationResponseViewModel>`  
_L14-24_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIOperationResponseViewModel>`
- L18 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaOperationResponseRow)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIOperationResponseViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaOperationRow.h` (Private)


#### class `SWebAPISchemaOperationRow`  
`class SWebAPISchemaOperationRow : public SWebAPISchemaTreeTableRow<FWebAPIOperationViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIOperationViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaOperationRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIOperationViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaParameterRow.h` (Private)


#### class `SWebAPISchemaParameterRow`  
`class SWebAPISchemaParameterRow : public SWebAPISchemaTreeTableRow<FWebAPIParameterViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIParameterViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaParameterRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIParameterViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaPropertyRow.h` (Private)


#### class `SWebAPISchemaPropertyRow`  
`class SWebAPISchemaPropertyRow : public SWebAPISchemaTreeTableRow<FWebAPIPropertyViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIPropertyViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaPropertyRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIPropertyViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaServiceRow.h` (Private)


#### class `SWebAPISchemaServiceRow`  
`class SWebAPISchemaServiceRow : public SWebAPISchemaTreeTableRow<FWebAPIServiceViewModel>`  
_L12-22_
- inherits: `SWebAPISchemaTreeTableRow<FWebAPIServiceViewModel>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaServiceRow)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FWebAPIServiceViewModel>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaTreeTableRow.h` (Private)


#### class `IWebAPISchemaTreeTableRow`  
`class IWebAPISchemaTreeTableRow`  
_L9-11_

#### class `SWebAPISchemaTreeTableRow`  
`template <typename ItemType> class SWebAPISchemaTreeTableRow : public STableRow<TSharedRef<ItemType>> , public IWebAPISchemaTreeTableRow`  
_L14-37_
- inherits: `STableRow<TSharedRef<ItemType>>,IWebAPISchemaTreeTableRow`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnColumnWidthChanged, float);`
- L24 _public function_ `SLATE_BEGIN_ARGS(SWebAPISchemaTreeTableRow)`
- L31 _public typedef_ `typedef STableRow<TSharedRef<ItemType>> FSuperRowType;` — Use this to construct the superclass; e.g. FSuperRowType::Construct( FTableRowArgs(), OwnerTableView )
- L33 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ItemType>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L36 _protected member_ `TSharedPtr<ItemType> ViewModel;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColumnWidthChanged, float);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPISchemaTreeTableRow.inl` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `template <typename ItemType> void SWebAPISchemaTreeTableRow<ItemType>::Construct(const FArguments& InArgs, const TSharedRef<ItemType>& InViewModel, const TSharedRef<STableViewBase>& InOwnerTableView)` (scope `SWebAPISchemaTreeTableRow`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/Details/Widgets/SWebAPITreeView.h` (Private)


#### class `SWebAPITreeView`  
`class SWebAPITreeView : public SCompoundWidget`  
_L26-108_
- inherits: `SCompoundWidget`
- desc: A widget containing either a tree of services or models.
- L29 _public typedef_ `using FTreeItemType = TSharedPtr<IWebAPIViewModel>;`
- L31 _public typedef_ `using FOnSelectionChanged = typename TSlateDelegates<FTreeItemType>::FOnSelectionChanged;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SWebAPITreeView) : _OnSelectionChanged()`
- L36 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FText& InLabel, const TArray<FTreeItemType>& InTreeViewItems = {});`
- L43 _public prototype_ `void Refresh(const TArray<TSharedPtr<IWebAPIViewModel>>& InTreeViewModels = {});` — Refresh the tree view. If new items are provided, they'll be replaced for this widget.
- L47 _public prototype_ `template <typename ViewModelType> void Refresh(const TArray<TSharedPtr<ViewModelType>>& InTreeViewModels = {});` — Refresh the tree view. If new items are provided, they'll be replaced for this widget.
- L51 _private prototype_ `void GetTreeItemChildren(FTreeItemType InObject, TArray<FTreeItemType>& OutChildren);` — Appends children of the provided Object to OutChildren.
- L54 _private prototype_ `void OnFilterTextChanged(const FText& InSearchText);` — Called when the associated search input changes.
- L58 _private prototype_ `template <typename ViewModelType> TSharedRef<ITableRow> GenerateRow(TSharedPtr<ViewModelType> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);` — Makes the row widget for the provided ViewModel.
- L61 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<IWebAPIViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L64 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIServiceViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L67 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIOperationViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L70 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIOperationRequestViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L73 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIOperationParameterViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L76 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIOperationResponseViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L79 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIModelViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L82 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIPropertyViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L85 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIEnumViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L88 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIEnumValueViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L91 _private prototype_ `template <> TSharedRef<ITableRow> GenerateRow(TSharedPtr<FWebAPIParameterViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L95 _private member_ `TSharedPtr<STreeView<FTreeItemType>> TreeViewWidget;` — TreeView Widget.
- L98 _private member_ `TArray<FTreeItemType> TreeViewItems;` — TreeView model context.
- L101 _private member_ `TArray<FTreeItemType> FilteredTreeViewItems;` — TreeView model context, filtered according to FilterText.
- L104 _private member_ `FText FilterText;` — Current filter text, if any.
- L107 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;` — The filter itself, if any.
- L111 _function_ `template <typename ViewModelType> void SWebAPITreeView::Refresh(const TArray<TSharedPtr<ViewModelType>>& InTreeViewModels)`

#### Free symbols / members of external scopes

- L115 _function_ `` (scope `SWebAPITreeView::Refresh`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/WebAPIEditorCommands.h` (Private)


#### class `FWebAPIEditorCommands`  
`class FWebAPIEditorCommands : public TCommands<FWebAPIEditorCommands>`  
_L8-24_
- inherits: `TCommands<FWebAPIEditorCommands>`
- L12 _public function_ `FWebAPIEditorCommands() : TCommands<FWebAPIEditorCommands>(TEXT("WebAPIEditor"), NSLOCTEXT("Contexts", "WebAPIEditor", "WebAPI Definition Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L20 _public member_ `TSharedPtr<FUICommandInfo> Generate;` — Generate command to execute code generation.
- L23 _public prototype_ `virtual void RegisterCommands() override;` — Registers all associated commands.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/WebAPIEditorModule.h` (Private)


#### class `FWebAPIEditorModule`  
`class FWebAPIEditorModule final : public IWebAPIEditorModuleInterface`  
_L13-83_
- inherits: `IWebAPIEditorModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual EAssetTypeCategories::Type GetAssetCategory() const override;`
- L23 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override`
- L27 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L31 _public prototype_ `virtual bool AddProvider(FName InProviderName, TSharedRef<IWebAPIProviderInterface> InProvider) override;` — Adds and registers a WebAPI provider.
- L34 _public prototype_ `virtual void RemoveProvider(FName InProviderName) override;` — Removes a WebAPI provider.
- L37 _public prototype_ `virtual TSharedPtr<IWebAPIProviderInterface> GetProvider(FName InProviderName) override;` — Retrieve a registered provider by its name.
- L40 _public prototype_ `virtual bool GetProviders(TArray<TSharedRef<IWebAPIProviderInterface>>& OutProviders) override;` — Retrieve all registered providers.
- L43 _public function_ `virtual FOnWebAPIProvidersChanged& OnProvidersChanged() override` — Whenever a Provider is added or removed.
- L46 _public prototype_ `virtual bool AddCodeGenerator(FName InCodeGeneratorName, const TSubclassOf<UObject>& InCodeGenerator) override;` — Adds and registers a WebAPI code generator.
- L49 _public prototype_ `virtual void RemoveCodeGenerator(FName InCodeGeneratorName) override;` — Removes a WebAPI code generator.
- L52 _public prototype_ `virtual TScriptInterface<IWebAPICodeGeneratorInterface> GetCodeGenerator(FName InCodeGeneratorName) override;` — Retrieve a registered code generator by its name.
- L55 _public prototype_ `virtual bool GetCodeGenerators(TArray<TScriptInterface<IWebAPICodeGeneratorInterface>>& OutCodeGenerators) override;` — Retrieve all registered code generators.
- L58 _public prototype_ `virtual UWebAPIStaticTypeRegistry* GetStaticTypeRegistry() const override;` — Returns the static type registry to retrieve metadata for built-in types.
- L60 _public function_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() override`
- L64 _public member_ `static const FName AppIdentifier;` — App identifier string
- L67 _public member_ `static const FName PluginCreatorTabName;` — ID name for the plugin creator tab
- L70 _private member_ `EAssetTypeCategories::Type AssetCategory = EAssetTypeCategories::Misc;`
- L71 _private member_ `TWeakPtr<FWebAPIDefinitionAssetEditorToolkit> AssetEditorToolkit;`
- L72 _private member_ `TArray<TSharedPtr<class IAssetTypeActions>> Actions;`
- L74 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L75 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L77 _private member_ `TMap<FName, TSharedRef<IWebAPIProviderInterface>> Providers;`
- L78 _private member_ `FOnWebAPIProvidersChanged ProvidersChangedDelegate;`
- L80 _private member_ `TMap<FName, TScriptInterface<IWebAPICodeGeneratorInterface>> CodeGenerators;`
- L82 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/WebAPIEditorStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("WebAPIEditor"), STATGROUP_WebAPIEditor, STATCA`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/WebAPIEditorStyle.h` (Private)


#### class `FWebAPIEditorStyle`  
`class FWebAPIEditorStyle`  
_L10-23_
- desc: Manages the style which provides resources for WebAPI Editor widgets.
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L18 _public prototype_ `static const ISlateStyle& Get();`
- L21 _private prototype_ `static TUniquePtr<class FSlateStyleSet> Create();`
- L22 _private member_ `static TUniquePtr<class FSlateStyleSet> StyleInstance;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/WebAPIEditorWidgetUtilities.h` (Private)


#### class `FWebAPIEditorWidgetsUtilities`  
`class FWebAPIEditorWidgetsUtilities`  
_L7-12_
- L10 _public function_ `static FSlateColor GetColorForVerb(uint8 InVerb)`
- L11 _public function_ `static FName GetIconNameForVerb(uint8 InVerb)`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Private/WebAPIPluginWizardDefinition.h` (Private)


#### class `FWebAPIPluginWizardDefinition`  
`class FWebAPIPluginWizardDefinition : public IPluginWizardDefinition`  
_L11-59_
- inherits: `IPluginWizardDefinition`
- desc: New plugin wizard definition used by PluginBrowser
- L14 _public prototype_ `FWebAPIPluginWizardDefinition(bool bIsContentOnlyProject = false);`
- L17 _public prototype_ `virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetTemplatesSource() const override;`
- L18 _public prototype_ `virtual void OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo) override;`
- L19 _public prototype_ `virtual TSharedPtr<FPluginTemplateDescription> GetSelectedTemplate() const override;`
- L20 _public prototype_ `virtual void ClearTemplateSelection() override;`
- L21 _public prototype_ `virtual bool HasValidTemplateSelection() const override;`
- L23 _public function_ `virtual bool CanShowOnStartup() const override`
- L24 _public prototype_ `virtual bool HasModules() const override;`
- L25 _public prototype_ `virtual bool IsMod() const override;`
- L26 _public function_ `virtual void OnShowOnStartupCheckboxChanged(ECheckBoxState CheckBoxState) override`
- L27 _public function_ `virtual ECheckBoxState GetShowOnStartupCheckBoxState() const override`
- L28 _public function_ `virtual TSharedPtr<class SWidget> GetCustomHeaderWidget() override`
- L29 _public prototype_ `virtual FText GetInstructions() const override;`
- L31 _public prototype_ `virtual bool GetPluginIconPath(FString& OutIconPath) const override;`
- L32 _public prototype_ `virtual EHostType::Type GetPluginModuleDescriptor() const override;`
- L33 _public prototype_ `virtual ELoadingPhase::Type GetPluginLoadingPhase() const override;`
- L34 _public prototype_ `virtual bool GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> InTemplate, FString& OutIconPath) const override;`
- L35 _public prototype_ `virtual FString GetPluginFolderPath() const override;`
- L36 _public prototype_ `virtual TArray<FString> GetFoldersForSelection() const override;`
- L37 _public prototype_ `virtual void PluginCreated(const FString& PluginName, bool bWasSuccessful) const override;`
- L42 _private prototype_ `void PopulateTemplatesSource();` — Creates the templates that can be used by the plugin manager to generate the plugin
- L45 _private prototype_ `FString GetFolderForTemplate(TSharedRef<FPluginTemplateDescription> InTemplate) const;` — Gets the folder for the specified template.
- L49 _private member_ `TArray<TSharedRef<FPluginTemplateDescription>> TemplateDefinitions;` — The templates available to this definition
- L52 _private member_ `TSharedPtr<FPluginTemplateDescription> CurrentTemplateDefinition;` — The currently selected template definition
- L55 _private member_ `FString PluginBaseDir;` — Base directory of the plugin templates
- L58 _private member_ `bool bIsContentOnlyProject;` — If true, this definition is for a project that can only contain content

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenBase.h` (Public)


#### class `FWebAPICodeGenBase`  
`class FWebAPICodeGenBase`  
_L7-48_
- L10 _public prototype_ `FWebAPICodeGenBase();`
- L11 _public prototype_ `virtual ~FWebAPICodeGenBase() = default;`
- L14 _public member_ `FString ServiceName;` — For Operations and Operation Parameters.
- L17 _public member_ `FString Description;` — Description for this object.
- L20 _public member_ `FString Module;` — Containing module name.
- L23 _public member_ `FString Namespace;` — Type Namespace, can be empty for built-in types.
- L26 _public member_ `TMap<FString, FString> Specifiers;` — U* specifiers, with or without a value.
- L29 _public member_ `TMap<FString, FString> Metadata;` — U* metadata, with or without a value.
- L32 _public prototype_ `virtual void SetModule(const FString& InModule);` — Sets the containing module name.
- L35 _public function_ `virtual FString GetName(bool bJustName = false)` — Retrieve the name. The source depends on the CodeGen object type.
- L38 _public function_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const` — Append any dependent modules for this file to the given Set.
- L41 _public function_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const` — Append any include paths for this file to the given Array (not Set, to allow custom order).
- L44 _public prototype_ `virtual void GetIncludePaths(TSet<FString>& OutIncludePaths) const;` — Append any include paths for this file to the given Set.
- L47 _public prototype_ `virtual const FName& GetTypeName();` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenClass.h` (Public)


#### class `FWebAPICodeGenClass`  
`class FWebAPICodeGenClass : public FWebAPICodeGenStruct`  
_L12-33_
- inherits: `FWebAPICodeGenStruct`
- L16 _private typedef_ `using Super = FWebAPICodeGenStruct;` — Inherited baseclass.
- L19 _public prototype_ `FWebAPICodeGenClass(const FWebAPICodeGenStruct& InStruct);`
- L22 _public member_ `TArray<TSharedPtr<FWebAPICodeGenFunction>> Functions;` — Functions within this class.
- L25 _public prototype_ `const TSharedPtr<FWebAPICodeGenFunction>& FindOrAddFunction(const FWebAPINameVariant& InName);` — Finds or creates a function with the given name.
- L29 _public member_ `inline static const FName TypeName = TEXT("Cla` — CodeGen Type.
- L32 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenEnum.h` (Public)


#### struct `FWebAPICodeGenEnumValue`  
`struct FWebAPICodeGenEnumValue`  
_L12-39_
- L16 _public member_ `FString Name;` — Name of the Enum Value.
- L19 _public member_ `FString DisplayName;` — Display Name of the Enum Value.
- L22 _public member_ `FString JsonName;` — Json Name of the Enum Value.
- L25 _public member_ `FString Description;` — Description of the Enum Value.
- L28 _public member_ `int32 IntegralValue = -1;` — Explicit integral value for an enum (0-255).
- L31 _public prototype_ `void FromWebAPI(const UWebAPIEnumValue* InSrcEnumValue);` — Populates this object from the given WebAPI object.
- L35 _public member_ `inline static const FName TypeName = TEXT("Enu` — CodeGen Type.
- L38 _public function_ `const FName& GetTypeName()` — CodeGen Type.

#### class `FWebAPICodeGenEnum`  
`class FWebAPICodeGenEnum : public FWebAPICodeGenBase`  
_L41-72_
- inherits: `FWebAPICodeGenBase`
- L45 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L49 _public member_ `FWebAPITypeNameVariant Name;` — Name of the Enum.
- L52 _public member_ `TArray<FWebAPICodeGenEnumValue> Values;` — Values within the Enum.
- L55 _public member_ `FString DefaultValue;` — Default value as a string, if applicable.
- L58 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L59 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L60 _public prototype_ `virtual FString GetName(bool bJustName = false) override;`
- L64 _public prototype_ `void FromWebAPI(const UWebAPIEnum* InSrcEnum);` — Populates this object from the given WebAPI object.
- L68 _public member_ `inline static const FName TypeName = TEXT("Enu` — CodeGen Type.
- L71 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenFile.h` (Public)


#### class `FWebAPICodeGenFile`  
`class FWebAPICodeGenFile : public FWebAPICodeGenBase`  
_L14-70_
- inherits: `FWebAPICodeGenBase`
- desc: Contains a list of declarations/definitions to generate for a single file.
- L18 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L22 _public member_ `FString BaseFilePath;` — Absolute Base Path to output to, usually a Module/Source/x/(Public or Private).
- L25 _public member_ `FString RelativeFilePath;` — Relative Path of the file, excluding the filename itself.
- L28 _public member_ `FString FileName;` — Name of the file, excluding extension.
- L31 _public member_ `FString FileType;` — File extension.
- L34 _public member_ `FString CopyrightNotice;` — Copyright notice to apply to the top of the file. Uses the Project setting unless specified.
- L37 _public member_ `TSet<FString> Modules;` — Module dependencies for this file.
- L40 _public member_ `TSet<FString> IncludePaths;` — Set of (unique) include paths.
- L43 _public member_ `TArray<TSharedPtr<FWebAPICodeGenBase>> SubItems;` — The inner codegen items to create within the file.
- L46 _public member_ `TArray<TWeakObjectPtr<UObject>> SchemaObjects;` — Schema objects represented by this file.
- L49 _public prototype_ `void AddItem(const TSharedPtr<FWebAPICodeGenBase>& InItem);` — Adds the given item as a SubItem and appends include paths.
- L53 _public prototype_ `template <typename CodeGenType> void AddItems(const TArray<TSharedPtr<CodeGenType>>& InItems);` — Adds the given item as a SubItem and appends include paths.
- L56 _public prototype_ `FString GetFullPath();` — Returns the full, absolute path to the file.
- L59 _public prototype_ `virtual void SetModule(const FString& InModule) override;`
- L60 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L61 _public prototype_ `virtual void GetIncludePaths(TSet<FString>& OutIncludePaths) const override;`
- L66 _public member_ `inline static const FName TypeName = TEXT("Fil` — CodeGen Type.
- L69 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.
- L73 _function_ `template <typename CodeGenType> void FWebAPICodeGenFile::AddItems(const TArray<TSharedPtr<CodeGenType>>& InItems)`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenFunction.h` (Public)


#### class `FWebAPICodeGenFunctionParameter`  
`class FWebAPICodeGenFunctionParameter : public FWebAPICodeGenProperty`  
_L9-17_
- inherits: `FWebAPICodeGenProperty`
- L13 _private typedef_ `using Super = FWebAPICodeGenProperty;` — Inherited baseclass.
- L17 _public member_ `inline static const FName TypeName = TEXT("Fun` — CodeGen Type.

#### class `FWebAPICodeGenFunction`  
`class FWebAPICodeGenFunction : public FWebAPICodeGenBase`  
_L20-50_
- inherits: `FWebAPICodeGenBase`
- L24 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L28 _public member_ `inline static const FName TypeName = TEXT("Fun` — CodeGen Type.
- L31 _public member_ `FWebAPINameVariant Name;` — Name with optional prefix, namespace, etc.
- L34 _public member_ `bool bIsConst = false;` — Flag for a constant function.
- L37 _public member_ `bool bIsOverride = false;` — Flag if the function is a virtual override.
- L40 _public member_ `FWebAPITypeNameVariant ReturnType;` — The type to return. If unspecified it will be void.
- L43 _public member_ `bool bIsConstReturnType = false;` — Flag if the returned value is constant.
- L46 _public member_ `TArray<TSharedPtr<FWebAPICodeGenFunctionParameter>> Parameters;` — Parameters for this function.
- L49 _public member_ `FString Body;` — Raw string to insert as the Function implementation.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenOperation.h` (Public)


#### class `FWebAPICodeGenOperationParameter`  
`class FWebAPICodeGenOperationParameter : public FWebAPICodeGenProperty`  
_L13-37_
- inherits: `FWebAPICodeGenProperty`
- L17 _private typedef_ `using Super = FWebAPICodeGenProperty;` — Inherited baseclass.
- L21 _public member_ `EWebAPIParameterStorage Storage;` — Where this parameter is stored/encoded in the request.
- L24 _public member_ `FString MediaType;` — The optional media-type, ie. "application/json".
- L27 _public member_ `bool bIsRequired;` — Mark as required (not-optional).
- L30 _public prototype_ `void FromWebAPI(const class UWebAPIOperationParameter* InSrcOperationParameter);` — Populates this object from the given WebAPI object.
- L34 _public member_ `inline static const FName TypeName = TEXT("Ope` — CodeGen Type.
- L36 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

#### class `FWebAPICodeGenOperationRequest`  
`class FWebAPICodeGenOperationRequest : public FWebAPICodeGenStruct`  
_L40-68_
- inherits: `FWebAPICodeGenStruct`
- desc: Encapsulates the request parameters for an operation.
- L44 _private typedef_ `using Super = FWebAPICodeGenStruct;` — Inherited baseclass.
- L48 _public member_ `TArray<TSharedPtr<FWebAPICodeGenOperationParameter>> Parameters;` — Array of parameters contained in this request.
- L51 _public prototype_ `const TSharedPtr<FWebAPICodeGenOperationParameter>& FindOrAddParameter(const FString& InName);` — Finds or creates a parameter with the given name.
- L54 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L55 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L56 _public prototype_ `virtual void SetModule(const FString& InModule) override;`
- L60 _public prototype_ `void FromWebAPI(const class UWebAPIOperationRequest* InSrcOperationRequest);` — Populates this object from the given WebAPI object.
- L64 _public member_ `inline static const FName TypeName = TEXT("Ope` — CodeGen Type.
- L67 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

#### class `FWebAPICodeGenOperationResponse`  
`class FWebAPICodeGenOperationResponse : public FWebAPICodeGenStruct`  
_L70-101_
- inherits: `FWebAPICodeGenStruct`
- L74 _private typedef_ `using Super = FWebAPICodeGenStruct;` — Inherited baseclass.
- L78 _public member_ `EWebAPIResponseStorage Storage;` — Where this parameter is stored/encoded in the response.
- L81 _public member_ `uint32 ResponseCode;` — Http response code.
- L84 _public member_ `FString Message;` — Optional message based on the response status or result.
- L87 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L88 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L89 _public prototype_ `virtual void SetModule(const FString& InModule) override;`
- L93 _public prototype_ `void FromWebAPI(const class UWebAPIOperationResponse* InSrcOperationResponse);` — Populates this object from the given WebAPI object.
- L97 _public member_ `inline static const FName TypeName = TEXT("Ope` — CodeGen Type.
- L100 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

#### class `FWebAPICodeGenOperation`  
`class FWebAPICodeGenOperation : public FWebAPICodeGenBase`  
_L103-153_
- inherits: `FWebAPICodeGenBase`
- L107 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L111 _public member_ `FWebAPITypeNameVariant Name;` — Name with optional prefix, namespace, etc.
- L114 _public member_ `FString Verb;` — Http Verb.
- L117 _public member_ `FString Path;` — Templated/tokenized Url path relative to the Base Url.
- L120 _public member_ `FString RequestMediaType;` — Usually application/json.
- L123 _public member_ `bool bIsDeprecated = false;` — Flags an operation previously available as deprecated.
- L126 _public member_ `TArray<TSharedPtr<FWebAPICodeGenOperationRequest>> Requests;` — Requests for this Operation.
- L129 _public member_ `TArray<TSharedPtr<FWebAPICodeGenOperationResponse>> Responses;` — Responses for this Operation.
- L132 _public member_ `FString SettingsTypeName;` — The name of the generated Settings class.
- L135 _public prototype_ `const TSharedPtr<FWebAPICodeGenOperationResponse>& FindOrAddResponse(const uint32& InResponseCode);` — Finds or creates a response with the given name.
- L138 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L139 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L140 _public prototype_ `virtual void SetModule(const FString& InModule) override;`
- L141 _public prototype_ `virtual FString GetName(bool bJustName = false) override;`
- L145 _public prototype_ `void FromWebAPI(const class UWebAPIOperation* InSrcOperation);` — Populates this object from the given WebAPI object.
- L149 _public member_ `inline static const FName TypeName = TEXT("Ope` — CodeGen Type.
- L152 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenProperty.h` (Public)


#### class `FWebAPICodeGenProperty`  
`class FWebAPICodeGenProperty : public FWebAPICodeGenBase`  
_L9-56_
- inherits: `FWebAPICodeGenBase`
- L13 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L16 _public prototype_ `FWebAPICodeGenProperty();`
- L19 _public member_ `FWebAPINameVariant Name;` — Name with optional prefix, namespace, etc.
- L22 _public member_ `FWebAPITypeNameVariant Type;` — Property Type.
- L25 _public member_ `bool bIsConst = false;` — Constant declaration.
- L28 _public member_ `FString DefaultValue;` — Default value as a string, if applicable.
- L31 _public member_ `bool bIsArray = false;` — If the property is an array of Type.
- L34 _public member_ `bool bIsRecursiveType = false;` — If the property type is the same as it's container.
- L37 _public member_ `bool bIsRequired = false;` — By default all properties are optional.
- L40 _public member_ `bool bIsMixin = false;` — When the properties inside of this should be treated as though they're directly in the parent.
- L43 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L44 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L48 _public prototype_ `void FromWebAPI(const class UWebAPIProperty* InSrcProperty);` — Populates this object from the given WebAPI object.
- L52 _public member_ `inline static const FName TypeName = TEXT("Pro` — CodeGen Type.
- L55 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenSettings.h` (Public)


#### class `FWebAPICodeGenSettings`  
`class FWebAPICodeGenSettings : public FWebAPICodeGenBase`  
_L11-53_
- inherits: `FWebAPICodeGenBase`
- desc: A settings class is generated from this, it's not in itself a Settings object.
- L15 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L19 _public member_ `FWebAPITypeNameVariant Name;` — Name with optional prefix, namespace, etc.
- L22 _public member_ `TSoftClassPtr<UDeveloperSettings> ParentType = UDeveloperSettings::StaticClass();` — Optional parent type. Useful if you have your own settings for this API that you want to extend.
- L25 _public member_ `FString Host;` — The default host address to access this API.
- L28 _public member_ `FString BaseUrl;` — The Url path relative to the host address, ie. "/V1".
- L31 _public member_ `FString UserAgent = TEXT("X-U` — The UserAgent to encode in Http request headers.
- L34 _public member_ `FString DateTimeFormat = TEXT("");` — The date-time format this API uses to encode/decode from string.
- L37 _public member_ `TArray<FString> Schemes;` — Uniform Resource Identifier schemes (ie. https, http).
- L40 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L41 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L45 _public prototype_ `void FromWebAPI(const UWebAPIDefinition* InSrcModel);` — Populates this object from the given WebAPI object.
- L49 _public member_ `inline static const FName TypeName = TEXT("Set` — CodeGen Type.
- L52 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/Dom/WebAPICodeGenStruct.h` (Public)


#### class `FWebAPICodeGenStruct`  
`class FWebAPICodeGenStruct : public FWebAPICodeGenBase`  
_L13-50_
- inherits: `FWebAPICodeGenBase`
- L17 _private typedef_ `using Super = FWebAPICodeGenBase;` — Inherited baseclass.
- L21 _public member_ `FWebAPITypeNameVariant Name;` — Name with optional prefix, namespace, etc.
- L24 _public member_ `FWebAPITypeNameVariant Base;` — Base class. Should be empty if none.
- L27 _public member_ `TArray<TSharedPtr<FWebAPICodeGenProperty>> Properties;` — Properties within this struct.
- L30 _public prototype_ `const TSharedPtr<FWebAPICodeGenProperty>& FindOrAddProperty(const FWebAPINameVariant& InName);` — Finds or creates a property with the given name.
- L33 _public prototype_ `virtual void GetModuleDependencies(TSet<FString>& OutModules) const override;`
- L34 _public prototype_ `virtual void GetIncludePaths(TArray<FString>& OutIncludePaths) const override;`
- L35 _public prototype_ `virtual FString GetName(bool bJustName = false) override;`
- L39 _public prototype_ `bool FindRecursiveProperties(TArray<TSharedPtr<FWebAPICodeGenProperty>>& OutProperties);` — Find and return properties that are of the same type as the containing class.
- L42 _public prototype_ `void FromWebAPI(const UWebAPIModel* InSrcModel);` — Populates this object from the given WebAPI object.
- L46 _public member_ `inline static const FName TypeName = TEXT("Str` — CodeGen Type.
- L49 _public function_ `virtual const FName& GetTypeName() override` — CodeGen Type.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/WebAPICodeGenerator.h` (Public)


#### enum `EWebAPIGenerationResult`  
`enum class EWebAPIGenerationResult : uint8`  
_L18-25_
- L20 _public enumerator_ `Failed = 0`
- L21 _public enumerator_ `Succeeded = 1`
- L22 _public enumerator_ `FailedWithErrors = 2`
- L23 _public enumerator_ `FailedWithWarnings = 3`
- L24 _public enumerator_ `SucceededWithWarnings = 4`

#### class `UWebAPICodeGeneratorInterface`  
`class UWebAPICodeGeneratorInterface : public UInterface`  
_L28-31_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IWebAPICodeGeneratorInterface`  
`class IWebAPICodeGeneratorInterface`  
_L34-44_
- desc: Interface for code generation for a given WebAPI Definition/Schema.
- L40 _public prototype_ `virtual TFuture<bool> IsAvailable() = 0;` — Check to see if this generator is available for use.
- L43 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> Generate(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition) = 0;` — Generate code for the given WebAPI Definition.

#### class `UWebAPICodeGeneratorBase`  
`class UWebAPICodeGeneratorBase : public UObject , public IWebAPICodeGeneratorInterface`  
_L48-85_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject,IWebAPICodeGeneratorInterface`
- desc: WebAPICodeGenerator base implementation. Converts WebAPI schema to code gen primitives. Use of this baseclass is optional.
- L56 _public prototype_ `virtual TFuture<bool> IsAvailable() override;` — Check to see if this generator is available for use.
- L59 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> Generate(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition) override;` — Generate code for the given WebAPI Definition.
- L62 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> GenerateServiceOperations(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const FString& InServiceName, const TArray<TSharedPtr<FWebAPICodeGenOperation>>& InOperations);` — Converts the given Service to a CodeGen Operation array.
- L65 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> GenerateEnum(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TSharedPtr<FWebAPICodeGenEnum>& InEnum);` — Converts the given Enum to a CodeGen Enum object.
- L68 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> GenerateModel(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TSharedPtr<FWebAPICodeGenStruct>& InStruct);` — Converts the given Model to a CodeGen Struct object.
- L71 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> GenerateFile(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TSharedPtr<FWebAPICodeGenFile>& InFile);` — Converts the given Definition to a CodeGen File object.
- L74 _public prototype_ `virtual TFuture<EWebAPIGenerationResult> GenerateSettings(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TSharedPtr<FWebAPICodeGenClass>& InSettingsClass);` — Converts the given Definition to a CodeGen Settings object.
- L77 _public member_ `static constexpr const TCHAR* LogName = TEXT("Cod`
- L81 _protected prototype_ `template <typename CodeGenType> bool CheckNameConflicts(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TArray<TSharedPtr<CodeGenType>>& InItems) const;`
- L84 _protected prototype_ `template <> bool CheckNameConflicts(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition, const TArray<TSharedPtr<FWebAPICodeGenFile>>& InItems) const;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/CodeGen/WebAPICodeGeneratorSettings.h` (Public)


#### struct `FWebAPIDefinitionTargetModule`  
`struct FWebAPIDefinitionTargetModule`  
_L13-32_
- reflection: `USTRUCT()`
- desc: Contains information about the target module for code generation files.
- L19 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Module")` — The name of the module.
- L23 _public member_ `FString AbsolutePath;` — `UPROPERTY(EditAnywhere, Category = "Module")` — The absolute location of the directory for this module. Only use to set, otherwise use GetPath().
- L26 _public prototype_ `FString GetPath();` — Resolves and returns the path, use instead of AbsolutePath.
- L31 _private member_ `FString ResolvedPath;` — `UPROPERTY(Transient)` — Caches the full path to the module.

#### struct `FWebAPICodeGeneratorSettings`  
`struct FWebAPICodeGeneratorSettings`  
_L39-98_
- reflection: `USTRUCT()`
- desc: Encapsulates settings for WebAPI code generation.
- L43 _public prototype_ `FWebAPICodeGeneratorSettings();`
- L47 _public member_ `bool bOverrideGeneratorClass = false;` — `UPROPERTY(EditAnywhere, Category = "Generator", meta = (InlineEditConditionToggle))` — Whether to override the Code Generator class specified in project settings.
- L51 _public member_ `TSoftClassPtr<UObject> CodeGeneratorClass;` — `UPROPERTY(EditAnywhere, NoClear, Category = "Generator", meta = (MustImplement = "/Script/WebAPIEditor.WebAPICodeGeneratorInterface", EditCondition="bOverrideGeneratorClass"))` — The Code Generator to use.
- L55 _public member_ `FString CopyrightNotice;` — `UPROPERTY(EditAnywhere, Category = "Generator")` — The copyright notice to apply to generated files.
- L59 _public member_ `FWebAPIDefinitionTargetModule TargetModule;` — `UPROPERTY(EditAnywhere, Category = "Generator")` — The C++ Unreal module determines the location of the generated files.
- L63 _public member_ `FString ModelOutputPath = TEXT("Mod` — `UPROPERTY(EditAnywhere, Category = "Generator")` — The relative output path for generated models. This accepts the token "{Model}", where Model is the name of the generated object.
- L67 _public member_ `FString OperationOutputPath = TEXT("Ser` — `UPROPERTY(EditAnywhere, Category = "Generator")` — The relative output path for generated operations. This accepts the token "{Service}" and "{Operation}".
- L71 _public member_ `TSoftClassPtr<UWebAPIDeveloperSettings> GeneratedSettingsBaseClass = UWebAPIDeveloperSettings::StaticClass();` — `UPROPERTY(EditAnywhere, NoClear, AdvancedDisplay, Category = "Generator", meta = (AllowAbstract))` — The generated settings baseclass (optional).
- L76 _public member_ `bool bWriteResult = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Generator")` — Disable to prevent the generator writing files/assets. The generation process itself will still occur.
- L80 _public prototype_ `TScriptInterface<class IWebAPICodeGeneratorInterface> GetGeneratorClass() const;` — Resolves and returns an instance of the CodeGeneratorClass.
- L83 _public prototype_ `const FString& GetNamespace() const;` — Returns the specified pseudo-namespace.
- L86 _public prototype_ `void SetNamespace(const FString& InNamespace);` — Sets the specified pseudo-namespace.
- L89 _public prototype_ `FOnNamespaceChangedDelegate& OnNamespaceChanged();` — When the pseudo-namespace changes.
- L94 _private member_ `FString Namespace;` — `UPROPERTY(EditAnywhere, Category = "Generator", meta = (AllowPrivateAccess))` — A pseudo-namespace to prefix generated types with to avoid naming conflicts. Usually the API name.
- L97 _private member_ `FOnNamespaceChangedDelegate OnNamespaceChangedDelegate;` — When the pseudo-namespace changes.

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNamespaceChangedDelegate, const FString& );` — Encapsulates a new pseudo-namespace.
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNamespaceChangedDelegate, const FString& );` — Encapsulates a new pseudo-namespace.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPICompositeModel.h` (Public)


#### enum `EWebAPIModelCompositionType`  
`enum class EWebAPIModelCompositionType`  
_L11-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `Single UMETA(DisplayName = "Single")` — Should contain *one* of the valid types. Maps to a Variant.
- L16 _public enumerator_ `Multiple UMETA(DisplayName = "Multiple")` — Should contain *one or more* of the valid types.
- L18 _public enumerator_ `All UMETA(DisplayName = "All")` — Should contain *all* of the valid types.

#### class `UWebAPICompositeModel`  
`class UWebAPICompositeModel : public UWebAPIModelBase`  
_L34-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWebAPIModelBase`
- L42 _public member_ `FWebAPITypeNameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the composition.
- L46 _public member_ `EWebAPIModelCompositionType CompositionType;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Type of composition.
- L50 _public member_ `TArray<FWebAPITypeNameVariant> Types;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Array of one or more types contained in the composition.
- L55 _public member_ `FString GeneratedCodeText;` — `UPROPERTY(Transient)` — The last generated code as text for debugging.
- L59 _public prototype_ `virtual FString GetSortKey() const override;` — Used for sorting in the UI.
- L62 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;` — Recursively sets the namespace of this and all child objects.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace WebAPI` (scope `UE`)
- L25 _namespace_ `namespace WebAPIModelCompositionType` (scope `UE::WebAPI`)
- L27 _prototype_ `const FString& ToString(const EWebAPIModelCompositionType& InEnumValue);` (scope `UE::WebAPI::WebAPIModelCompositionType`)
- L28 _prototype_ `const EWebAPIModelCompositionType& FromString(const FString& InStringValue);` (scope `UE::WebAPI::WebAPIModelCompositionType`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPIEnum.h` (Public)


#### class `UWebAPIEnumValue`  
`class UWebAPIEnumValue : public UWebAPIModelBase`  
_L14-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWebAPIModelBase`
- desc: Describes a single value within a enum.
- L22 _public member_ `FWebAPINameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the EnumValue.

#### class `UWebAPIEnum`  
`class UWebAPIEnum : public UWebAPIModelBase`  
_L27-76_
- reflection: `UCLASS()`
- inherits: `UWebAPIModelBase`
- desc: Describes a (usually) API-specific class representing an enum.
- L35 _public member_ `FWebAPITypeNameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the Enum.
- L39 _public member_ `bool bGenerate;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Will be set based on dependent operations.
- L43 _public member_ `FString Type = TEXT("uin` — `UPROPERTY(EditAnywhere, Category = "Type")` — The enum base type, always uint8.
- L47 _public member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Current or Default Value of the Enum.
- L51 _public member_ `TArray<TObjectPtr<UWebAPIEnumValue>> Values;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Values within the Enum.
- L56 _public member_ `FString GeneratedCodeText;` — `UPROPERTY(Transient)` — The last generated code as text for debugging.
- L60 _public prototype_ `TObjectPtr<UWebAPIEnumValue> AddValue();` — Add and return a reference to a new Enum Value.
- L63 _public prototype_ `virtual FString GetSortKey() const override;`
- L64 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L65 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor) override;`
- L66 _public prototype_ `virtual bool ToJson(TSharedPtr<FJsonObject>& OutJson) override;`
- L67 _public prototype_ `virtual void BindToTypeInfo() override;`
- L69 _public prototype_ `virtual void SetCodeText(const FString& InCodeText) override;`
- L70 _public prototype_ `virtual void AppendCodeText(const FString& InCodeText) override;`
- L75 _public prototype_ `FString GetDefaultValue(bool bQualified = false) const;` — Default value as a string, usually the first enum value.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPIModel.h` (Public)


#### class `UWebAPIProperty`  
`class UWebAPIProperty : public UWebAPIModelBase`  
_L14-60_
- reflection: `UCLASS()`
- inherits: `UWebAPIModelBase`
- desc: Describes a single property within a model.
- L22 _public member_ `FWebAPINameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the Property.
- L26 _public member_ `FWebAPITypeNameVariant Type;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Type of the Property.
- L30 _public member_ `bool bIsArray = false;` — `UPROPERTY(EditAnywhere, Category = "Type")` — If the property is an array of Type.
- L34 _public member_ `bool bIsMixin = false;` — `UPROPERTY(EditAnywhere, Category = "Type")` — When the properties inside of this should be treated as though they're directly in the parent.
- L38 _public member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Default value (optional) as a string.
- L42 _public member_ `TArray<FString> DefaultValues;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Array of values if needed, ie. enum
- L45 _public prototype_ `virtual bool IsRequired() const;` — Returns if this property is required to have it's value set by the user.
- L48 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L52 _public prototype_ `FString GetDefaultValue(bool bQualified = false) const;` — Default value as a string, if applicable.
- L58 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.

#### class `UWebAPIModel`  
`class UWebAPIModel : public UWebAPIModelBase`  
_L64-113_
- reflection: `UCLASS()`
- inherits: `UWebAPIModelBase`
- desc: Describes a (usually) API-specific struct or class representing a model.
- L72 _public member_ `FWebAPITypeNameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the Model.
- L76 _public member_ `bool bGenerate = true;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Will be set based on dependent operations.
- L80 _public member_ `FWebAPITypeNameVariant Type;` — `UPROPERTY(EditAnywhere, Category = "Type")` — The corresponding TypeInfo for this Model.
- L84 _public member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Default value (optional) as a string.
- L88 _public member_ `TArray<TObjectPtr<UWebAPIProperty>> Properties;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Array of properties contained in this model.
- L93 _public member_ `FString GeneratedCodeText;` — `UPROPERTY(Transient)` — The last generated code as text for debugging.
- L97 _public prototype_ `virtual FString GetSortKey() const override;`
- L98 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L99 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor) override;`
- L100 _public prototype_ `virtual void BindToTypeInfo() override;`
- L102 _public prototype_ `virtual void SetCodeText(const FString& InCodeText) override;`
- L103 _public prototype_ `virtual void AppendCodeText(const FString& InCodeText) override;`
- L111 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPIOperation.h` (Public)


#### enum `EWebAPIParameterStorage`  
`enum class EWebAPIParameterStorage`  
_L13-25_
- reflection: `UENUM()`
- L16 _public enumerator_ `Path UMETA(DisplayName = "Path")` — /users/{value}
- L18 _public enumerator_ `Query UMETA(DisplayName = "Query")` — /users?{key}={value}}
- L20 _public enumerator_ `Header UMETA(DisplayName = "Header")` — {key}: {value}
- L22 _public enumerator_ `Cookie UMETA(DisplayName = "Cookie")` — {key}={value}
- L24 _public enumerator_ `Body UMETA(DisplayName = "Body")` — ie. json string

#### enum `EWebAPIResponseStorage`  
`enum class EWebAPIResponseStorage`  
_L28-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `Body UMETA(DisplayName = "Body")` — ie. json string
- L33 _public enumerator_ `Header UMETA(DisplayName = "Header")` — {key}: {value}

#### class `UWebAPIOperationParameter`  
`class UWebAPIOperationParameter : public UWebAPIProperty`  
_L43-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWebAPIProperty`
- L51 _public member_ `EWebAPIParameterStorage Storage;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Where this parameter is stored/encoded in the request.
- L55 _public member_ `FString MediaType;` — `UPROPERTY(EditAnywhere, Category = "Type")` — The optional media-type, ie. "application/json".
- L59 _public member_ `TObjectPtr<UWebAPIModel> Model;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Optional model definition.
- L62 _public prototype_ `virtual bool IsRequired() const override;`
- L63 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`

#### class `UWebAPIOperationRequest`  
`class UWebAPIOperationRequest : public UWebAPIModel`  
_L68-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWebAPIModel`
- L76 _public member_ `TArray<TObjectPtr<UWebAPIOperationParameter>> Parameters;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Array of parameters contained in this request.
- L79 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L80 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor) override;`

#### class `UWebAPIOperationResponse`  
`class UWebAPIOperationResponse : public UWebAPIModel`  
_L85-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWebAPIModel`
- L93 _public member_ `EWebAPIResponseStorage Storage;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Where this parameter is stored/encoded in the response.
- L97 _public member_ `uint32 Code = 200;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Http response code.
- L101 _public member_ `FString Message;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Optional message based on the response status or result.

#### class `UWebAPIOperationError`  
`class UWebAPIOperationError : public UObject , public IWebAPISchemaObjectInterface`  
_L105-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IWebAPISchemaObjectInterface`
- L114 _public member_ `uint32 Code = 404;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Http response code.
- L118 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Describes this error, usually the error message.

#### class `UWebAPIOperation`  
`class UWebAPIOperation : public UObject , public IWebAPISchemaObjectInterface`  
_L122-203_
- reflection: `UCLASS()`
- inherits: `UObject,IWebAPISchemaObjectInterface`
- L129 _public prototype_ `UWebAPIOperation();`
- L133 _public member_ `FWebAPITypeNameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the Operation.
- L137 _public member_ `bool bGenerate = true;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Can be disabled to skip generation of this Operation.
- L141 _public member_ `TObjectPtr<class UWebAPIService> Service;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Parent service for this operation.
- L145 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Describes this operation.
- L149 _public member_ `bool bIsDeprecated = false;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Flags an operation previously available as deprecated.
- L153 _public member_ `FString Verb;` — `UPROPERTY(EditAnywhere, Category = "Type")` — The Http verb, ie. Get, Post, etc.
- L157 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, Category = "Type")` — The operation path, relative to the base url. This can contain named template args.
- L161 _public member_ `TArray<FString> RequestContentTypes;` — `UPROPERTY(EditAnywhere, Category = "Type")` — List of possible content types for requests, ie. application/json
- L165 _public member_ `TArray<FString> ResponseContentTypes;` — `UPROPERTY(EditAnywhere, Category = "Type")` — List of possible content types for responses, ie. application/json
- L169 _public member_ `TObjectPtr<UWebAPIOperationRequest> Request;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Request model.
- L173 _public member_ `TArray<TObjectPtr<UWebAPIOperationResponse>> Responses;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Array of responses.
- L177 _public member_ `TArray<TObjectPtr<UWebAPIOperationError>> Errors;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Array of errors that can be returned.
- L182 _public member_ `FString GeneratedCodeText;` — `UPROPERTY(Transient)` — The last generated code as text for debugging.
- L186 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L187 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor) override;`
- L189 _public prototype_ `virtual void SetCodeText(const FString& InCodeText) override;`
- L190 _public prototype_ `virtual void AppendCodeText(const FString& InCodeText) override;`
- L195 _public prototype_ `virtual void BindToTypeInfo();` — Associates this model with it's own TypeInfo.
- L201 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace WebAPI` (scope `UE`)
- L36 _namespace_ `namespace WebAPIParameterStorage` (scope `UE::WebAPI`)
- L38 _prototype_ `const FString& ToString(const EWebAPIParameterStorage& InEnumValue);` (scope `UE::WebAPI::WebAPIParameterStorage`)
- L39 _prototype_ `const EWebAPIParameterStorage& FromString(const FString& InStringValue);` (scope `UE::WebAPI::WebAPIParameterStorage`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPIParameter.h` (Public)


#### class `UWebAPIParameter`  
`class UWebAPIParameter : public UWebAPIModel`  
_L12-44_
- reflection: `UCLASS()`
- inherits: `UWebAPIModel`
- desc: A re-usable Parameter.
- L20 _public member_ `EWebAPIParameterStorage Storage;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Where this parameter is stored/encoded in the request.
- L24 _public member_ `FString MediaType;` — `UPROPERTY(EditAnywhere, Category = "Type")` — The optional media-type, ie. "application/json".
- L28 _public member_ `TObjectPtr<UWebAPIModel> Model;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Optional model definition.
- L32 _public member_ `bool bIsArray = false;` — `UPROPERTY(EditAnywhere, Category = "Type")` — If the property is an array of Type.
- L36 _public member_ `TObjectPtr<UWebAPIProperty> Property;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Single value property that this Parameter wraps.
- L40 _public prototype_ `virtual void SetCodeText(const FString& InCodeText) override;`
- L41 _public prototype_ `virtual void AppendCodeText(const FString& InCodeText) override;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPISchema.h` (Public)


#### class `UWebAPISchemaObjectInterface`  
`class UWebAPISchemaObjectInterface : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IWebAPISchemaObjectInterface`  
`class IWebAPISchemaObjectInterface`  
_L24-47_
- L30 _public prototype_ `virtual FString GetSortKey() const;` — Used for sorting in the UI.
- L33 _public prototype_ `virtual void SetNamespace(const FString& InNamespace);` — Recursively sets the namespace of this and all child objects.
- L36 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor);` — Recursively visit each element in the schema.
- L38 _public prototype_ `virtual bool ToJson(TSharedPtr<FJsonObject>& OutJson);`
- L42 _public prototype_ `virtual void SetCodeText(const FString& InCodeText);` — Sets the last generated code as text for debugging.
- L45 _public prototype_ `virtual void AppendCodeText(const FString& InCodeText);` — Appends the last generated code as text for debugging.

#### struct `FWebAPITypeNameVariant`  
`struct FWebAPITypeNameVariant`  
_L51-110_
- reflection: `USTRUCT(BlueprintType)`
- desc: Holds either UWebAPITypeInfo or FString.
- L57 _public member_ `TSoftObjectPtr<UWebAPITypeInfo> TypeInfo = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — TypeInfo.
- L61 _public member_ `FString TypeString;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — String.
- L65 _public member_ `FString JsonName;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Field name as sent to and received from the external API.
- L67 _public prototype_ `FWebAPITypeNameVariant() = default;`
- L69 _public prototype_ `FWebAPITypeNameVariant(const TObjectPtr<UWebAPITypeInfo>& InTypeName);`
- L71 _public prototype_ `FWebAPITypeNameVariant(const FString& InStringName);`
- L73 _public prototype_ `FWebAPITypeNameVariant(const TCHAR* InStringName);`
- L76 _public prototype_ `bool HasTypeInfo() const;` — Check if this has valid TypeInfo.
- L79 _public prototype_ `bool IsValid() const;` — Check that either TypeInfo is set and valid, or a TypeString is non-empty.
- L82 _public prototype_ `FString ToMemberName(const FString& InPrefix = {}) const;` — Get the fully formatted name as a valid member name. Optionally provide a prefix for invalid member names (ie. that start with a number).
- L85 _public prototype_ `FString ToString(bool bInJustName = false) const;` — Retrieve the String of whichever property is valid.
- L87 _public prototype_ `FString GetDisplayName() const;`
- L89 _public prototype_ `FString GetJsonName() const;`
- L92 _public function_ `FWebAPITypeNameVariant& operator=(const FString& InStringName)` — Copy-assignment.

#### struct `FWebAPINameInfo`  
`struct FWebAPINameInfo`  
_L114-157_
- reflection: `USTRUCT(BlueprintType)`
- desc: Holds information for a name and it's alternatives.
- L120 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Name")` — Name without prefix or namespace, ie. "SomeParameter", not "InSomeParameter".
- L124 _public member_ `FString JsonName;` — `UPROPERTY(VisibleAnywhere, Category = "Name")` — Field name as sent to and received from the external API.
- L128 _public member_ `FString Prefix;` — `UPROPERTY(VisibleAnywhere, Category = "Name")` — Type Prefix, usually for parameters ("In"/"Out") or booleans "b".
- L130 _public prototype_ `FWebAPINameInfo() = default;`
- L133 _public prototype_ `explicit FWebAPINameInfo(const FString& InName, const FString& InJsonName, const FWebAPITypeNameVariant& InTypeInfo = {});` — Optionally provide TypeInfo to infer a prefix, for example "b" for booleans.
- L136 _public prototype_ `FString ToString(bool bInJustName = false) const;` — Get the fully formatted name, with prefix.
- L139 _public prototype_ `FString ToMemberName(const FString& InPrefix = {}) const;` — Get the fully formatted name as a valid member name.
- L142 _public prototype_ `FString GetDisplayName() const;` — The name for UI display.
- L145 _public prototype_ `FString GetJsonName() const;` — The json field name that the target API expects, rather than the UE friendly one.

#### struct `FWebAPINameVariant`  
`struct FWebAPINameVariant`  
_L161-214_
- reflection: `USTRUCT(BlueprintType)`
- desc: Holds either FWebAPINameInfo or FString.
- L167 _public member_ `FWebAPINameInfo NameInfo;` — `UPROPERTY(VisibleAnywhere, Category = "Name")` — NameInfo.
- L171 _public member_ `FString NameString;` — `UPROPERTY(VisibleAnywhere, Category = "Name")` — String.
- L173 _public prototype_ `FWebAPINameVariant() = default;`
- L175 _public prototype_ `FWebAPINameVariant(const FWebAPINameInfo& InNameInfo);`
- L177 _public prototype_ `FWebAPINameVariant(const FString& InStringName);`
- L179 _public prototype_ `FWebAPINameVariant(const TCHAR* InStringName);`
- L182 _public prototype_ `bool HasNameInfo() const;` — Check if this has a valid NameInfo.
- L185 _public prototype_ `bool IsValid() const;` — Check that either NameInfo is set and valid, or a NameString is non-empty.
- L188 _public prototype_ `FString ToString(bool bInJustName = false) const;` — Retrieve the String of whichever property is valid.
- L191 _public prototype_ `FString ToMemberName(const FString& InPrefix = {}) const;` — Get the fully formatted name as a valid member name. Optionally provide a prefix for invalid member names (ie. that start with a number).
- L194 _public prototype_ `FString GetDisplayName() const;` — The name for UI display.
- L197 _public prototype_ `FString GetJsonName() const;` — The json field name that the target API expects, rather than the UE friendly one.
- L200 _public prototype_ `FWebAPINameVariant& operator=(const FString& InStringName);` — Copy-assignment.

#### class `UWebAPIModelBase`  
`class UWebAPIModelBase : public UObject , public IWebAPISchemaObjectInterface`  
_L218-274_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject,IWebAPISchemaObjectInterface`
- desc: Baseclass with common properties for various Schema classes.
- L227 _public member_ `FString Description;` — `UPROPERTY(VisibleAnywhere, Category = "Model")` — Describes this model.
- L231 _public member_ `bool bIsRequired = false;` — `UPROPERTY(VisibleAnywhere, Category = "Model")` — By default all properties are optional.
- L235 _public member_ `bool bIsReadOnly = false;` — `UPROPERTY(VisibleAnywhere, Category = "Model")` — By default all properties are read & write.
- L239 _public member_ `bool bUseMinimumValue;` — `UPROPERTY(VisibleAnywhere, Category = "Model", meta = (InlineEditConditionToggle))` — Whether to use Minimum value.
- L243 _public member_ `double MinimumValue;` — `UPROPERTY(VisibleAnywhere, Category = "Model", meta = (EditCondition="bUseMinimumValue"))` — Minimum value. Can also indicate minimum string length.
- L247 _public member_ `bool bUseMaximumValue;` — `UPROPERTY(VisibleAnywhere, Category = "Model", meta = (InlineEditConditionToggle))` — Whether to use Maximum value.
- L251 _public member_ `double MaximumValue;` — `UPROPERTY(VisibleAnywhere, Category = "Model", meta = (EditCondition="bUseMaximumValue"))` — Maximum value. Can also indicate maximum string length.
- L255 _public member_ `bool bUsePattern;` — `UPROPERTY(VisibleAnywhere, Category = "Model", meta = (InlineEditConditionToggle))` — Whether to use a Regex Pattern for validation.
- L259 _public member_ `FString Pattern;` — `UPROPERTY(VisibleAnywhere, Category = "Model", meta = (EditCondition="bUsePattern"))` — Regex Pattern to validate against.
- L262 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L266 _public prototype_ `virtual void BindToTypeInfo();` — Associates this model with it's own TypeInfo.
- L272 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.

#### class `UWebAPISchema`  
`class UWebAPISchema : public UObject , public IWebAPISchemaObjectInterface`  
_L278-359_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject,IWebAPISchemaObjectInterface`
- desc: Describes the intermediate structure from which to generate code.
- L285 _public prototype_ `UWebAPISchema();`
- L289 _public member_ `FString APIName;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — Name of the API.
- L293 _public member_ `FString Version;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — The API version can be any arbitrary string that is useful if there are several versions.
- L297 _public member_ `FString Host;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — The default host address to access this API.
- L301 _public member_ `FString BaseUrl;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — The Url path relative to the host address, ie. "/V1".
- L305 _public member_ `FString UserAgent = TEXT("X-U` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Schema")` — The UserAgent to encode in Http request headers.
- L309 _public member_ `FString DateTimeFormat;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — The date-time format this API uses to encode/decode from string.
- L313 _public member_ `TArray<FString> URISchemes;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — Uniform Resource Identifier schemes (ie. https, http).
- L317 _public member_ `TObjectPtr<UWebAPITypeRegistry> TypeRegistry;` — `UPROPERTY()` — Contains all referenced types for this API.
- L321 _public member_ `TArray<TObjectPtr<UWebAPIModelBase>> Models;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — Models can be a combination of classes, structs and enums used by this API.
- L325 _public member_ `TMap<FString, TObjectPtr<class UWebAPIService>> Services;` — `UPROPERTY(VisibleAnywhere, Category = "Schema")` — Each service contains one or more operations.
- L329 _public prototype_ `template <typename ModelType> ModelType* AddModel(const TObjectPtr<UWebAPITypeInfo>& InTypeInfo = {});` — Add and return a reference to a new Model
- L332 _public prototype_ `class UWebAPIEnum* AddEnum(const TObjectPtr<UWebAPITypeInfo>& InTypeInfo = {});` — Add and return a reference to a new Enum.
- L335 _public prototype_ `class UWebAPIParameter* AddParameter(const TObjectPtr<UWebAPITypeInfo>& InTypeInfo);` — Add and return a reference to a new Parameter. These can be referenced by operations rather than defining them inline.
- L338 _public prototype_ `TObjectPtr<class UWebAPIService> GetOrMakeService(const FString& InName);` — Find/Add and return a reference to an existing/new Service.
- L341 _public prototype_ `void Clear();` — Resets the Schema to defaults.
- L344 _public prototype_ `const TSharedPtr<FWebAPIMessageLog>& GetMessageLog() const;`
- L348 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor) override;` — Recursively visit each element in the schema.
- L354 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.
- L358 _public member_ `static constexpr const TCHAR* LogName = TEXT("Web`
- L362 _function_ `template <typename ModelType> ModelType* UWebAPISchema::AddModel(const TObjectPtr<UWebAPITypeInfo>& InTypeInfo)`

#### Free symbols / members of external scopes

- L99 _function_ `friend bool operator==(const FWebAPITypeNameVariant& A, const FWebAPITypeNameVariant& B)` — Comparisons.
- L106 _function_ `friend bool operator!=(const FWebAPITypeNameVariant& A, const FWebAPITypeNameVariant& B)`
- L148 _function_ `friend bool operator==(const FWebAPINameInfo& A, const FWebAPINameInfo& B)` — Comparisons.
- L153 _function_ `friend bool operator!=(const FWebAPINameInfo& A, const FWebAPINameInfo& B)`
- L203 _function_ `friend bool operator==(const FWebAPINameVariant& A, const FWebAPINameVariant& B)` — Comparisons.
- L210 _function_ `friend bool operator!=(const FWebAPINameVariant& A, const FWebAPINameVariant& B)`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPIService.h` (Public)


#### class `UWebAPIService`  
`class UWebAPIService : public UWebAPIModelBase`  
_L14-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWebAPIModelBase`
- desc: A service generally contains a sub-section of the API containing operations related to a particular subject.
- L22 _public member_ `FWebAPITypeNameVariant Name;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Name of the Service.
- L26 _public member_ `bool bGenerate = true;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Can be disabled to skip generation of this Service and it's operations.
- L30 _public member_ `TArray<TObjectPtr<UWebAPIOperation>> Operations;` — `UPROPERTY(EditAnywhere, Category = "Type")` — Operations contained within the service.
- L33 _public prototype_ `virtual void SetNamespace(const FString& InNamespace) override;`
- L34 _public prototype_ `virtual void Visit(TFunctionRef<void(IWebAPISchemaObjectInterface*&)> InVisitor) override;`
- L41 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPIType.h` (Public)


#### enum `EWebAPISchemaType`  
`enum class EWebAPISchemaType : uint8`  
_L17-28_
- reflection: `UENUM()`
- desc: Schema type allows same name but different Schema types, ie. both a service and model with the name "Pet".
- L19 _public enumerator_ `Model`
- L20 _public enumerator_ `Service`
- L21 _public enumerator_ `Operation`
- L24 _public enumerator_ `Property` — All items before this are considered top-level, all below are sub-items
- L25 _public enumerator_ `Parameter`
- L27 _public enumerator_ `Unspecified = 128`

#### class `UWebAPITypeInfo`  
`class UWebAPITypeInfo : public UObject`  
_L43-189_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Holds information for an existing or pending type.
- L50 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Type Name without prefix or namespace, ie. "Vector", not "FVector".
- L54 _public member_ `FString DisplayName;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Optional display name, different to the actual name, ie. "JsonObject" vs. "JsonObjectWrapper".
- L58 _public member_ `EWebAPISchemaType SchemaType = EWebAPISchemaType::Model;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — SchemaType to discern between ie. a Service and a Model with the same name.
- L62 _public member_ `bool bIsNested = false;` — `UPROPERTY(VisibleAnywhere, Category = "Type", meta = (InlineEditConditionToggle))` — Flag specifying whether this type is used exclusively by a parent type (isn't shared).
- L66 _public member_ `FWebAPITypeNameVariant ContainingType;` — `UPROPERTY(VisibleAnywhere, Category = "Type", meta = (EditCondition = "bIsNested"))` — When the type is nested, this specifies who "owns" it.
- L70 _public member_ `FString JsonName;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Field name as sent to and received from the external API.
- L74 _public member_ `FName JsonType = TEXT("Obj` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Json type. Should correspond with values in EJson.
- L78 _public member_ `FString JsonPropertyToSerialize;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Optional sub-property to serialize, instead of the object itself.
- L82 _public member_ `FString PrintFormatSpecifier = TEXT("");` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Optional specifier for printf, ie. "s", "d".
- L86 _public member_ `FString PrintFormatExpression = TEXT("{Pr` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Optional tokenized string expression to get the value for printf, ie. ToString({Property})
- L90 _public member_ `FString Namespace;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Type Namespace, can be empty for built-in types.
- L94 _public member_ `FString Prefix;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Type Prefix, usually "F", "U", "A", or "E".
- L98 _public member_ `FString Suffix;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Optional suffix, ie. "Parameter", "Item", etc.
- L102 _public member_ `FName DeclarationType = NAME_StructProperty;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Declaration type, ie. struct, enum.
- L106 _public member_ `bool bIsBuiltinType = true;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — If this is false, the type is to be generated and should have a namespace.
- L110 _public member_ `FString DefaultValue;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Default value as a string, if applicable.
- L114 _public member_ `TSet<FString> Modules = { TEXT("Core"` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Module dependencies for this type.
- L118 _public member_ `TSet<FString> IncludePaths = { TEXT("CoreM` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Relative include paths required when referencing this type.
- L122 _public member_ `FSlateColor PinColor;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Color for UI.
- L126 _public member_ `FString DebugString;` — `UPROPERTY(VisibleAnywhere, Category = "Type")` — Misc info for debug.
- L128 _public prototype_ `UWebAPITypeInfo() = default;`
- L130 _public prototype_ `bool IsEnum() const;`
- L133 _public prototype_ `TObjectPtr<UWebAPITypeInfo> Duplicate(const TObjectPtr<class UWebAPITypeRegistry>& InTypeRegistry) const;` — Duplicate this TypeInfo to the provided TypeRegistry.
- L136 _public prototype_ `FString ToString(bool bInJustName = false) const;` — Get the fully formatted name, with prefix and namespace.
- L139 _public prototype_ `FString ToMemberName(const FString& InPrefix = {}) const;` — Get the fully formatted name as a valid member name. Optionally provide a prefix for invalid member names (ie. that start with a number).
- L142 _public prototype_ `FString GetDisplayName() const;` — The name for UI display.
- L145 _public prototype_ `FString GetJsonName() const;` — The json field name that the target API expects, rather than the UE friendly one.
- L148 _public prototype_ `FString GetDefaultValue(bool bQualified = false) const;` — Default value as a string.
- L151 _public prototype_ `void SetName(const FString& InName);` — Set's the name and updates the underlying object id.
- L154 _public prototype_ `void SetNested(const FWebAPITypeNameVariant& InNester);` — Set's this type as nested, using the provided Type as ContainingType.
- L157 _public prototype_ `UObject* GetModel() const;` — Get the (mutable) Model. Will return nullptr if not set.
- L165 _public function_ `void SetModel(const ModelType* InModel)`
- L174 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.
- L188 _private member_ `TSoftObjectPtr<UObject> Model;` — `UPROPERTY(VisibleAnywhere, Category = "Type", meta = (ObjectMustImplement = "/Script/WebAPIEditor.WebAPISchemaObjectInterface"))` — Associated model, if any.

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L32 _namespace_ `namespace WebAPI` (scope `UE`)
- L34 _namespace_ `namespace WebAPISchemaType` (scope `UE::WebAPI`)
- L36 _prototype_ `const FString& ToString(EWebAPISchemaType SchemaType);` (scope `UE::WebAPI::WebAPISchemaType`)
- L180 _function_ `friend bool operator!=(const UWebAPITypeInfo& A, const UWebAPITypeInfo& B)`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Dom/WebAPITypeRegistry.h` (Public)


#### class `UWebAPIStaticTypeRegistry`  
`class UWebAPIStaticTypeRegistry final : public UEngineSubsystem`  
_L14-81_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Holds Type information for built-in types.
- L21 _public prototype_ `const TObjectPtr<UWebAPITypeInfo>& GetOrMakeBuiltinType(const FString& InName, const FString& InJsonName, const FSlateColor& InPinColor, const FString& InPrefix = TEXT(""), FName InDeclarationType = NAME_None);` — Find or create the TypeInfo for the given built-in type.
- L24 _public prototype_ `const TObjectPtr<UWebAPITypeInfo>* FindBuiltinType(const FString& InName);` — Finds the TypeInfo with the give name.
- L27 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Initializes and registers the built-in types.
- L30 _public prototype_ `static const UGraphEditorSettings* GetGraphEditorSettings();` — Used to retrieve PinColor.
- L33 _public member_ `inline static const FName ToFromJsonType = TEXT("ToF` — For JsonType, when there is a ToJson/FromJson overload for the given value.
- L36 _public member_ `inline static const FName ToFromJsonObject = TEXT("ToF` — For JsonObjectWrapper, manipulate the JsonObject directly (also JsonObjectToString, JsonObjectFromString).
- L40 _public member_ `TObjectPtr<UWebAPITypeInfo> Nullptr;` — List of common built-in types, static for easy comparisons, etc.
- L41 _public member_ `TObjectPtr<UWebAPITypeInfo> Auto;`
- L42 _public member_ `TObjectPtr<UWebAPITypeInfo> Void;`
- L44 _public member_ `TObjectPtr<UWebAPITypeInfo> String;`
- L45 _public member_ `TObjectPtr<UWebAPITypeInfo> Name;`
- L46 _public member_ `TObjectPtr<UWebAPITypeInfo> Text;`
- L47 _public member_ `TObjectPtr<UWebAPITypeInfo> Char;`
- L48 _public member_ `TObjectPtr<UWebAPITypeInfo> Boolean;`
- L49 _public member_ `TObjectPtr<UWebAPITypeInfo> Float;`
- L50 _public member_ `TObjectPtr<UWebAPITypeInfo> Double;`
- L51 _public member_ `TObjectPtr<UWebAPITypeInfo> Byte;`
- L52 _public member_ `TObjectPtr<UWebAPITypeInfo> Int16;`
- L53 _public member_ `TObjectPtr<UWebAPITypeInfo> Int32;`
- L54 _public member_ `TObjectPtr<UWebAPITypeInfo> Int64;`
- L56 _public member_ `TObjectPtr<UWebAPITypeInfo> FilePath;`
- L57 _public member_ `TObjectPtr<UWebAPITypeInfo> DateTime;`
- L60 _public member_ `TObjectPtr<UWebAPITypeInfo> Enum;` — Unnamed enum.
- L63 _public member_ `TObjectPtr<UWebAPITypeInfo> Object;` — Unnamed object.
- L66 _public member_ `TObjectPtr<UWebAPITypeInfo> JsonObject;` — Json object.
- L69 _public member_ `TObjectPtr<UWebAPITypeInfo> WebAPIMessageResponse;` — WebAPI Message Response object.
- L72 _public member_ `static constexpr const TCHAR* UnnamedTypeName = TEXT("Unn` — The name of a TypeInfo when it's unnamed/unknown.
- L76 _private prototype_ `void InitializeTypes();` — Initializes common built-in types.
- L80 _private member_ `TArray<TObjectPtr<UWebAPITypeInfo>> BuiltinTypes;` — `UPROPERTY()` — Array of common built-in types.

#### class `UWebAPITypeRegistry`  
`class UWebAPITypeRegistry : public UObject`  
_L85-130_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Holds Type information for a given Schema.
- L94 _public prototype_ `TObjectPtr<UWebAPITypeInfo> GetOrMakeGeneratedType(const EWebAPISchemaType& InSchemaType, const FString& InName, const FString& InJsonName, const FString& InPrefix = TEXT(""), FName InDeclarationType = NAME_None);` — Find or create the TypeInfo for the given SchemaType and Name. @note Providing the schema type allows for a Model and Service (for example) to have the same name but not be considered the same type.
- L95 _public prototype_ `TObjectPtr<UWebAPITypeInfo> GetOrMakeGeneratedType(const EWebAPISchemaType& InSchemaType, const FString& InName, const FString& InJsonName, const TObjectPtr<const UWebAPITypeInfo>& InTemplateTypeInfo);`
- L98 _public prototype_ `const TObjectPtr<UWebAPITypeInfo>* FindGeneratedType(const EWebAPISchemaType& InSchemaType, const FString& InName);` — Find and return the TypeInfo for the given SchemaType and Name. Returns nullptr if not found.
- L101 _public prototype_ `const TArray<TObjectPtr<UWebAPITypeInfo>>& GetGeneratedTypes() const;` — Returns the array containing all registered TypeInfo's for generation.
- L104 _public prototype_ `TArray<TObjectPtr<UWebAPITypeInfo>>& GetMutableGeneratedTypes();` — Returns the mutable array containing all registered TypeInfo's for generation.
- L107 _public prototype_ `void Clear();` — Clears all stored type information.
- L110 _public prototype_ `bool CheckAllNamed() const;` — Checks for any unnamed types, logs a message and returns false if one or more unnamed still exist.
- L113 _public prototype_ `bool CheckAllNamed(TArray<TObjectPtr<UWebAPITypeInfo>>& OutUnnamedTypes) const;` — Checks for and outputs any unnamed types, logs a message and returns false if one or more unnamed still exist.
- L119 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.
- L124 _public member_ `static constexpr const TCHAR* LogName = TEXT("Web` — For use by the WebAPI Message Log.
- L129 _private member_ `TArray<TObjectPtr<UWebAPITypeInfo>> GeneratedTypes;` — `UPROPERTY()` — Array of TypeInfo objects to generate (no built-in types).

#### Free symbols / members of external scopes

- L132 _namespace_ `namespace UE`
- L134 _namespace_ `namespace WebAPI` (scope `UE`)
- L137 _prototype_ `FName MakeTypeInfoName(UObject* InOuter, const EWebAPISchemaType& InSchemaType, const FString& InName);` (scope `UE::WebAPI`) — Creates a unique FName for TypeInfo's based on the given parameters.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/Factories/WebAPIDefinitionFactory.h` (Public)


#### class `UWebAPIDefinitionFactory`  
`class UWebAPIDefinitionFactory : public UFactory , public FReimportHandler`  
_L17-58_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UFactory,FReimportHandler`
- desc: Base Factory for WebAPIDefinition.
- L24 _public prototype_ `UWebAPIDefinitionFactory();`
- L27 _public prototype_ `virtual bool CanImportWebAPI(const FString& InFileName, const FString& InFileContents);` — Check if the factory can import the given file (and it's contents).
- L30 _public prototype_ `virtual TFuture<bool> ImportWebAPI(UWebAPIDefinition* InDefinition, const FString& InFileName, const FString& InFileContents);` — Perform the import or re-import.
- L33 _public prototype_ `virtual TFuture<void> PostImportWebAPI(UWebAPIDefinition* InDefinition);` — Called after a successful import.
- L36 _public prototype_ `virtual bool IsValidFileExtension(const FString& InFileExtension) const;` — Checks that the provided file extension (not the whole file name or path!) is valid for this factory.
- L39 _public prototype_ `virtual bool FactoryCanImport(const FString& InFileName) override;`
- L40 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& InFilename, const TCHAR* InParms, FFeedbackContext* InWarn, bool& bOutOperationCanceled) override;`
- L44 _public prototype_ `virtual bool CanReimport(UObject* InObj, TArray<FString>& OutFilenames) override;`
- L45 _public prototype_ `virtual void SetReimportPaths(UObject* InObj, const TArray<FString>& NewReimportPaths) override;`
- L46 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* InObj) override;`
- L51 _protected prototype_ `FString ReadFileContents(const FString& InFileName) const;` — Could be on-disk or URL.
- L54 _protected prototype_ `virtual bool IsValidFile(const FString& InFilename) const;` — Checks that the provided file contains a valid file extension.
- L57 _private member_ `static constexpr const TCHAR* LogName = TEXT("Web`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/IWebAPIEditorModule.h` (Public)


#### class `IWebAPIEditorModuleInterface`  
`class IWebAPIEditorModuleInterface : public IModuleInterface , public IHasMenuExtensibility , public IHasToolBarExtensibility`  
_L16-68_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L28 _public function_ `static IWebAPIEditorModuleInterface& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public prototype_ `virtual EAssetTypeCategories::Type GetAssetCategory() const = 0;`
- L37 _public prototype_ `virtual bool AddProvider(FName InProviderName, TSharedRef<IWebAPIProviderInterface> InProvider) = 0;` — Adds and registers a WebAPI provider.
- L40 _public prototype_ `virtual void RemoveProvider(FName InProviderName) = 0;` — Removes a WebAPI provider.
- L43 _public prototype_ `virtual TSharedPtr<IWebAPIProviderInterface> GetProvider(FName InProviderName) = 0;` — Retrieve a registered provider by its name.
- L46 _public prototype_ `virtual bool GetProviders(TArray<TSharedRef<IWebAPIProviderInterface>>& OutProviders) = 0;` — Retrieve all registered providers.
- L49 _public prototype_ `virtual FOnWebAPIProvidersChanged& OnProvidersChanged() = 0;` — Whenever a Provider is added or removed.
- L52 _public prototype_ `virtual bool AddCodeGenerator(FName InCodeGeneratorName, const TSubclassOf<UObject>& InCodeGenerator) = 0;` — Adds and registers a WebAPI code generator.
- L55 _public prototype_ `virtual void RemoveCodeGenerator(FName InCodeGeneratorName) = 0;` — Removes a WebAPI code generator.
- L58 _public prototype_ `virtual TScriptInterface<IWebAPICodeGeneratorInterface> GetCodeGenerator(FName InCodeGeneratorName) = 0;` — Retrieve a registered code generator by its name.
- L61 _public prototype_ `virtual bool GetCodeGenerators(TArray<TScriptInterface<IWebAPICodeGeneratorInterface>>& OutCodeGenerators) = 0;` — Retrieve all registered code generators.
- L64 _public prototype_ `virtual UWebAPIStaticTypeRegistry* GetStaticTypeRegistry() const = 0;` — Returns the static type registry to retrieve metadata for built-in types.
- L66 _public prototype_ `DECLARE_EVENT_OneParam(FUVEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L67 _public prototype_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() = 0;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWebAPIProvidersChanged);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWebAPIProvidersChanged);`
- L66 _delegate_ `DECLARE_EVENT_OneParam(FUVEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPICommon.h` (Public)


#### struct `FWebAPITemplateString`  
`struct FWebAPITemplateString`  
_L10-31_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `FString String;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="String")`
- L17 _public prototype_ `FWebAPITemplateString() = default;`
- L19 _public function_ `explicit FWebAPITemplateString(FString&& InString) : String(MoveTemp(InString))`
- L24 _public prototype_ `FString PopulateTemplate(const FStringFormatNamedArguments& InArgs);`
- L27 _public prototype_ `bool IsValid();` — Gets the validity of the template string.
- L30 _public prototype_ `bool IsValid(const FStringFormatNamedArguments& InArgs);` — Gets the validity of the template string for the given named arguments.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIDefinition.h` (Public)


#### class `UWebAPIDefinition`  
`class UWebAPIDefinition : public UObject`  
_L19-94_
- reflection: `UCLASS(AutoCollapseCategories = "ImportSettings")`
- inherits: `UObject`
- desc: The asset containing various options and the schema itself.
- L24 _public prototype_ `UWebAPIDefinition();`
- L30 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, AdvancedDisplay, Category = "ImportSettings")` — Importing data and options used for this definition.
- L34 _public prototype_ `UObject* AddOrGetImportedDataCache(FName InKey, const TSubclassOf<UObject>& InDataCacheClass);` — Retrieves the custom data for the given key, or creates it if it doesn't exist.
- L37 _public function_ `template <typename DataCacheType> DataCacheType* AddOrGetImportedDataCache(FName InKey)`
- L44 _public prototype_ `FString GetCopyrightNotice() const;` — Get the user-specified Copyright Notice, or from the Project Settings if unspecified.
- L47 _public prototype_ `const FWebAPIProviderSettings& GetProviderSettings() const;` — Settings for the WebAPI provider.
- L50 _public prototype_ `FWebAPIProviderSettings& GetProviderSettings();` — Settings for the WebAPI provider.
- L53 _public prototype_ `const FWebAPICodeGeneratorSettings& GetGeneratorSettings() const;` — Settings for the code generation.
- L56 _public prototype_ `FWebAPICodeGeneratorSettings& GetGeneratorSettings();` — Settings for the code generation.
- L58 _public prototype_ `UWebAPISchema* GetWebAPISchema();`
- L59 _public prototype_ `const UWebAPISchema* GetWebAPISchema() const;`
- L60 _public prototype_ `const TSharedPtr<FWebAPIMessageLog>& GetMessageLog() const;`
- L66 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — @return		Returns Valid if this object has data validation rules set up for it and the data for this object is valid. Returns Invalid if it does not pass the rules. Returns NotValidated if no rules are set for this object.
- L74 _private member_ `FWebAPIProviderSettings ProviderSettings;` — `UPROPERTY(EditAnywhere, Category = "Provider", meta = (ShowOnlyInnerProperties, AllowPrivateAccess))` — Settings for the WebAPI provider.
- L78 _private member_ `FWebAPICodeGeneratorSettings GeneratorSettings;` — `UPROPERTY(EditAnywhere, Category = "Generator", meta = (ShowOnlyInnerProperties, AllowPrivateAccess))` — Settings for code generation.
- L83 _private member_ `TMap<FName, TObjectPtr<UObject>> ImportedDataCache;` — `UPROPERTY()` — Optional data store, ie. schema file contents.
- L88 _private member_ `TObjectPtr<UWebAPISchema> WebAPISchema;` — `UPROPERTY(Instanced)` — The schema written by the provider.
- L91 _private member_ `TSharedPtr<FWebAPIMessageLog> MessageLog;` — MessageLog for this Definition.
- L93 _private prototype_ `void OnNamespaceChanged(const FString& InNewNamespace);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPIEditor, Log, All);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIEditorSettings.h` (Public)


#### class `UWebAPIEditorSettings`  
`class UWebAPIEditorSettings : public UDeveloperSettings`  
_L13-25_
- reflection: `UCLASS(BlueprintType, Config = Engine, DefaultConfig, meta = (DisplayName = "WebAPI"))`
- inherits: `UDeveloperSettings`
- L19 _public member_ `TSoftClassPtr<UObject> CodeGeneratorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "Generator", meta = (MustImplement = "/Script/WebAPIEditor.WebAPICodeGeneratorInterface"))`
- L21 _public function_ `virtual FName GetContainerName() const override`
- L22 _public function_ `virtual FName GetCategoryName() const override`
- L24 _public prototype_ `TScriptInterface<class IWebAPICodeGeneratorInterface> GetGeneratorClass() const;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIEditorSubsystem.h` (Public)


#### class `UWebAPIEditorSubsystem`  
`class UWebAPIEditorSubsystem : public UEditorSubsystem`  
_L17-59_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- desc: Common functionality and registry for WebAPI Editor.
- L22 _public prototype_ `UWebAPIEditorSubsystem();`
- L24 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L25 _public prototype_ `virtual void Deinitialize() override;`
- L32 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebAPIDefinitionPreImport, UWebAPIDefinition* );` — Before a WebAPI Definition is being (re)imported. @param Definition - The Definition being re-imported. Will be nullptr if it's a new import.
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWebAPIDefinitionPostImport, bool , FName , UWebAPIDefinition* );` — After a WebAPI Definition is being (re)imported. @param bSuccessful - Indicates if the import was successful. @param FactoryName - The (unique) name of the Factory that imported the Definition. @param Definition - The Definition being imported.
- L46 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModuleCreated, FString );` — After a new module or plugin is created.
- L48 _public prototype_ `FOnWebAPIDefinitionPreImport& OnDefinitionPreImport();`
- L49 _public prototype_ `FOnWebAPIDefinitionPostImport& OnDefinitionPostImport();`
- L50 _public prototype_ `FOnModuleCreated& OnModuleCreated();`
- L53 _private member_ `FOnWebAPIDefinitionPreImport OnDefinitionPreImportDelegate;`
- L54 _private member_ `FOnWebAPIDefinitionPostImport OnDefinitionPostImportDelegate;`
- L55 _private member_ `FOnModuleCreated OnModuleCreatedDelegate;`
- L57 _private prototype_ `void HandleDefinitionPreImport(UWebAPIDefinition* InDefinition);`
- L58 _private prototype_ `void HandleDefinitionPostImport(bool bInImportSuccessful, FName InFactoryName, UWebAPIDefinition* InDefinition);`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebAPIDefinitionPreImport, UWebAPIDefinition* );` — Before a WebAPI Definition is being (re)imported. @param Definition - The Definition being re-imported. Will be nullptr if it's a new import.
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWebAPIDefinitionPostImport, bool , FName , UWebAPIDefinition* );` — After a WebAPI Definition is being (re)imported. @param bSuccessful - Indicates if the import was successful. @param FactoryName - The (unique) name of the Factory that imported the Definition. @param Definition - The Definition being imported.
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModuleCreated, FString );` — After a new module or plugin is created.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIEditorUtilities.h` (Public)


#### class `UE::WebAPI::FWebAPIStringUtilities`  
`class FWebAPIStringUtilities`  
_L11-33_
- L15 _public prototype_ `static TSharedRef<FWebAPIStringUtilities> Get();` — Get the singleton instance.
- L18 _public prototype_ `FString ToPascalCase(FStringView InString);` — Converts the input string to PascalCase. The result may still contain characters illegal for a member name.
- L21 _public prototype_ `FString ToInitials(FStringView InString);` — Converts the input string to its initials.
- L24 _public prototype_ `FString MakeValidMemberName(FStringView InString, const FString& InPrefix = {}) const;` — Makes the input string valid for use as a member name, ie. no reserved characters. Provide an optional prefix to apply to invalid names (ie. start with a number).
- L30 _protected member_ `TSharedPtr<IBreakIterator> BreakIterator;`
- L32 _protected prototype_ `FWebAPIStringUtilities() = default;`

#### class `UE::WebAPI::FWebAPIEditorUtilities`  
`class FWebAPIEditorUtilities`  
_L35-52_
- L39 _public prototype_ `static TSharedRef<FWebAPIEditorUtilities> Get();` — Get the singleton instance.
- L42 _public prototype_ `bool GetHeadersForClass(const TSubclassOf<UObject>& InClass, TArray<FString>& OutHeaders);` — Get all required headers to reference the provided class.
- L45 _public prototype_ `bool GetModulesForClass(const TSubclassOf<UObject>& InClass, TArray<FString>& OutModules);` — Get all required modules to reference the provided class.
- L51 _protected prototype_ `FWebAPIEditorUtilities() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace WebAPI` (scope `UE`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIJsonUtilities.h` (Public)


#### struct `UE::Json::Concepts::CNumerical`  
`struct CNumerical`  
_L17-23_
- desc: Concept to check if T has NumericLimits, and isn't a bool.
- L20 _public prototype_ `template <typename T> auto Requires() -> decltype( std::is_same_v<typename TNumericLimits<T>::NumericType, T> && !std::is_same_v<T, bool>);`

#### struct `UE::Json::Concepts::CFromJsonable`  
`struct CFromJsonable`  
_L26-32_
- desc: Describes a type that provides a FromJson function.
- L29 _public prototype_ `template <typename T> auto Requires(T& Val, const TSharedRef<FJsonObject>& Arg) -> decltype( Val.FromJson(Arg) );`

#### struct `UE::Json::Concepts::CMap`  
`struct CMap`  
_L35-41_
- desc: Describes a type the is derived from TMap.
- L38 _public prototype_ `template <typename T> auto Requires(const TMap<typename T::KeyType, typename T::ValueType>* MapPtr, T* Ptr) -> decltype( MapPtr = Ptr );`

#### struct `UE::Json::TypeTraits::TIsStringLike`  
`template <typename ValueType, typename Enable = void> struct TIsStringLike`  
_L48-51_
- desc: String-like value types.

#### enum `UE::Json::TypeTraits::TIsStringLike::(anonymous)`  
`enum`  
_L50-50_

#### struct `UE::Json::TypeTraits::TIsStringLike`  
`template <typename ValueType> struct TIsStringLike< ValueType, typename TEnableIf< std::is_same_v<ValueType, FString> || std::is_same_v<ValueType, FName> || std::is_same_v<ValueType, FText>>::Type>`  
_L54-65_

#### enum `UE::Json::TypeTraits::TIsStringLike::(anonymous)`  
``  
_L62-64_

#### class `UE::Json::TJsonReference`  
`template<class ObjectType> class TJsonReference`  
_L82-260_
- desc: Contains either an object constructed in place, or a reference to an object declared elsewhere.
- L85 _public typedef_ `using ElementType = ObjectType;`
- L86 _public member_ `static constexpr ESPMode Mode = ESPMode::ThreadSafe;`
- L89 _public function_ `TJsonReference() : Object(nullptr)` — Constructs an empty Json Reference.
- L95 _public function_ `void ResolveDeferred(const FString& InJsonPath)` — Sets the object path and flags it as a pending reference (to be resolved later).
- L102 _public function_ `bool TryResolve(const TSharedRef<FJsonObject>& InRootObject, const TFunctionRef<ObjectType(TSharedRef<FJsonObject>&)>& InSetter)` — Attempts to resolve the reference, returns true if successful or already set.
- L129 _public function_ `ObjectType* Get()` — Returns the object referenced by this Json Reference, creating it if it doesn't exist.
- L140 _public function_ `TSharedPtr<ObjectType> GetShared()` — Returns the object referenced by this Json Reference, creating it if it doesn't exist.
- L151 _public function_ `ObjectType* Get() const` — Returns the object referenced by this Json Reference, or nullptr if it doesn't exist.
- L157 _public function_ `TSharedPtr<ObjectType> GetShared() const` — Returns the object referenced by this Json Reference, or nullptr if it doesn't exist.
- L163 _public function_ `bool Set(ObjectType&& InObject)` — Set's the object if it's not already set.
- L176 _public function_ `bool Set(TSharedPtr<ObjectType>&& InObject)` — Set's the object if it's not already set.
- L189 _public function_ `bool Set(const TSharedPtr<ObjectType>& InObject)` — Set's the object if it's not already set.
- L202 _public function_ `bool IsSet() const` — Checks if the underlying object has been set.
- L208 _public function_ `explicit operator bool() const` — Checks to see if this is actually pointing to an object.
- L214 _public function_ `bool IsValid() const` — Checks if the object is valid, or it's pending reference resolution.
- L217 _public function_ `ObjectType& operator*() const` — Dereferences the object
- L224 _public function_ `ObjectType* operator->() const` — Pointer to the underlying object.
- L230 _public function_ `const FString& GetPath() const`
- L236 _public function_ `bool GetPathSegments(TArray<FString>& OutSegments) const` — Returns true if there were one or more segments.
- L241 _public function_ `FString GetLastPathSegment() const`
- L253 _protected member_ `FString Path;` — The specified path to the actual object definition.
- L256 _protected member_ `bool bHasPendingResolve = false;` — Flag indicating this is a reference but not yet resolved.
- L259 _protected member_ `TSharedPtr<ObjectType> Object;` — Underling object pointer.

#### struct `UE::Json::FVariantValueVisitor`  
`struct FVariantValueVisitor`  
_L496-517_
- desc: Variant
- L498 _public function_ `explicit FVariantValueVisitor(const TSharedPtr<FJsonValue>& InJsonValue) : JsonValue(InJsonValue)`
- L504 _public function_ `template <typename ValueType> bool operator()(ValueType& OutValue)`
- L516 _public member_ `const TSharedPtr<FJsonValue> JsonValue;`

#### struct `UE::Json::FVariantObjectVisitor`  
`struct FVariantObjectVisitor`  
_L519-540_
- L521 _public function_ `explicit FVariantObjectVisitor(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName) : JsonObject(InJsonObject) , FieldName(InFieldName)`
- L528 _public function_ `template <typename ValueType> bool operator()(ValueType& OutValue)`
- L538 _public member_ `const TSharedPtr<FJsonObject> JsonObject;`
- L539 _public member_ `const FString FieldName;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Json` (scope `UE`)
- L14 _namespace_ `namespace Concepts` (scope `UE::Json`)
- L44 _namespace_ `namespace TypeTraits` (scope `UE::Json`)
- L50 _enumerator_ `enum { Value = false };` (scope `UE::Json::TypeTraits::TIsStringLike::__anond5f433f80103`)
- L63 _enumerator_ `Value = true` (scope `UE::Json::TypeTraits::TIsStringLike::__anond5f433f80203`)
- L69 _variable_ `template <typename ValueType> constexpr bool TIsNumeric_V = TModels_V<Concepts::CNumerical, std::decay_t<ValueType>>;` (scope `UE::Json::TypeTraits`) — Numeric value types.
- L73 _variable_ `template <typename ValueType> constexpr bool THasFromJson_V = TModels_V<Concepts::CFromJsonable, std::decay_t<ValueType>>;` (scope `UE::Json::TypeTraits`) — ValueType has FromJson.
- L77 _variable_ `template <typename ValueType> constexpr bool TIsDerivedFromMap_V = TModels_V<Concepts::CMap, std::decay_t<ValueType>>;` (scope `UE::Json::TypeTraits`) — ValueType is derived from TMap.
- L265 _function_ `As(const TSharedPtr<FJsonValue>& InJsonValue, ValueType& OutValue)` (scope `UE::Json`)
- L289 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, ValueType& OutValue);` (scope `UE::Json`)
- L293 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, ValueType& OutValue);` (scope `UE::Json`)
- L298 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, EnumType& OutValue, const TMap<FString, EnumType>& InNameToValue = {});` (scope `UE::Json`)
- L302 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, EnumType& OutValue, const TMap<FString, EnumType>& InNameToValue = {});` (scope `UE::Json`)
- L325 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, ContainerType& OutValues);` (scope `UE::Json`)
- L329 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, ContainerType& OutValues);` (scope `UE::Json`)
- L334 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TMap<KeyType, ValueType>& OutValues);` (scope `UE::Json`)
- L338 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TMap<KeyType, ValueType>& OutValues);` (scope `UE::Json`) — Key must be string
- L342 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, MapType& OutValues);` (scope `UE::Json`)
- L346 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, MapType& OutValues);` (scope `UE::Json`) — Key must be string
- L363 _prototype_ `template <typename... ValueTypes> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TVariant<ValueTypes...>& OutValue);` (scope `UE::Json`) — Variant
- L366 _prototype_ `template <typename... ValueTypes> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TVariant<ValueTypes...>& OutValue);` (scope `UE::Json`)
- L370 _prototype_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TUniqueObj<ValueType>& OutValue);` (scope `UE::Json`) — UniqueObj
- L373 _prototype_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TUniqueObj<ValueType>& OutValue);` (scope `UE::Json`)
- L377 _prototype_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TJsonReference<ValueType>& OutValue);` (scope `UE::Json`) — TJsonReference
- L380 _prototype_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TJsonReference<ValueType>& OutValue);` (scope `UE::Json`)
- L436 _prototype_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TSharedPtr<ValueType>& OutValue);` (scope `UE::Json`) — SharedPtr
- L439 _prototype_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TSharedPtr<ValueType>& OutValue);` (scope `UE::Json`)
- L451 _prototype_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TSharedRef<ValueType>& OutValue);` (scope `UE::Json`) — SharedRef
- L454 _prototype_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TSharedRef<ValueType>& OutValue);` (scope `UE::Json`)
- L459 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<ValueType>& OutValue);` (scope `UE::Json`)
- L463 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<ValueType>& OutValue);` (scope `UE::Json`)
- L468 _prototype_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<EnumType>& OutValue, const TMap<FString, EnumType>& InNameToValue = {});` (scope `UE::Json`)
- L472 _prototype_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<EnumType>& OutValue, const TMap<FString, EnumType>& InNameToValue = {});` (scope `UE::Json`)
- L476 _prototype_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<TUniqueObj<ValueType>>& OutValue);` (scope `UE::Json`) — Optional UniqueObj
- L479 _prototype_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<TUniqueObj<ValueType>>& OutValue);` (scope `UE::Json`)
- L483 _prototype_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<TSharedRef<ValueType>>& OutValue);` (scope `UE::Json`) — Optional SharedRef
- L486 _prototype_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<TSharedRef<ValueType>>& OutValue);` (scope `UE::Json`)
- L490 _prototype_ `template <typename ValueType, typename = typename TEnableIf<std::is_same_v<ValueType, TSharedPtr<FJsonObject>>>::Type> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, ValueType& OutValue);` (scope `UE::Json`) — JsonObject
- L493 _prototype_ `template <typename ValueType, typename = typename TEnableIf<std::is_same_v<ValueType, TSharedPtr<FJsonObject>>>::Type> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TSharedPtr<FJsonObject>& OutValue);` (scope `UE::Json`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIJsonUtilities.inl` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Json` (scope `UE`)
- L15 _function_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, ValueType& OutValue)` (scope `UE::Json`)
- L22 _function_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, ValueType& OutValue)` (scope `UE::Json`)
- L30 _function_ `TryGet( const TSharedPtr<FJsonValue>& InJsonValue, EnumType& OutValue, const TMap<FString, EnumType>& InNameToValue)` (scope `UE::Json`)
- L91 _function_ `TryGetField( const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, EnumType& OutValue, const TMap<FString, EnumType>& InNameToValue)` (scope `UE::Json`)
- L106 _function_ `template <> inline bool TryGet<FString>(const TSharedPtr<FJsonValue>& InJsonValue, FString& OutValue)` (scope `UE::Json`) — String
- L112 _function_ `template <> inline bool TryGetField<FString>(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, FString& OutValue)` (scope `UE::Json`)
- L119 _function_ `template <> inline bool TryGet<FText>(const TSharedPtr<FJsonValue>& InJsonValue, FText& OutValue)` (scope `UE::Json`) — Text
- L131 _function_ `template <> inline bool TryGetField<FText>(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, FText& OutValue)` (scope `UE::Json`)
- L160 _function_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, ContainerType& OutValues)` (scope `UE::Json`)
- L162 _typedef_ `using ValueType = typename ContainerType::ElementType;` (scope `UE::Json::TryGet`)
- L183 _function_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, ContainerType& OutValues)` (scope `UE::Json`)
- L187 _typedef_ `using ValueType = typename ContainerType::ElementType;` (scope `UE::Json::TryGetField`)
- L196 _function_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TMap<KeyType, ValueType>& OutValues)` (scope `UE::Json`)
- L214 _function_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TMap<KeyType, ValueType>& OutValues)` (scope `UE::Json`)
- L225 _function_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, MapType& OutValues)` (scope `UE::Json`)
- L227 _typedef_ `using KeyType = typename MapType::KeyType;` (scope `UE::Json::TryGet`)
- L228 _typedef_ `using ValueType = typename MapType::ValueType;` (scope `UE::Json::TryGet`)
- L235 _function_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, MapType& OutValues)` (scope `UE::Json`)
- L237 _typedef_ `using KeyType = typename MapType::KeyType;` (scope `UE::Json::TryGetField`)
- L238 _typedef_ `using ValueType = typename MapType::ValueType;` (scope `UE::Json::TryGetField`)
- L246 _function_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<ValueType>& OutValue)` (scope `UE::Json`)
- L259 _function_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<ValueType>& OutValue)` (scope `UE::Json`)
- L276 _function_ `TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<EnumType>& OutValue, const TMap<FString, EnumType>& InNameToValue)` (scope `UE::Json`)
- L289 _function_ `TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<EnumType>& OutValue, const TMap<FString, EnumType>& InNameToValue)` (scope `UE::Json`)
- L364 _function_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TUniqueObj<ValueType>& OutValue)` (scope `UE::Json`) — UniqueObj
- L370 _function_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TUniqueObj<ValueType>& OutValue)` (scope `UE::Json`)
- L381 _function_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TJsonReference<ValueType>& OutValue)` (scope `UE::Json`) — TJsonReference
- L397 _function_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TJsonReference<ValueType>& OutValue)` (scope `UE::Json`)
- L422 _function_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TSharedPtr<ValueType>& OutValue)` (scope `UE::Json`) — SharedPtr
- L439 _function_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TSharedPtr<ValueType>& OutValue)` (scope `UE::Json`)
- L464 _function_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TSharedRef<ValueType>& OutValue)` (scope `UE::Json`) — SharedRef
- L470 _function_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TSharedRef<ValueType>& OutValue)` (scope `UE::Json`)
- L481 _function_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<TUniqueObj<ValueType>>& OutValue)` (scope `UE::Json`) — Optional UniqueObj
- L506 _function_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<TUniqueObj<ValueType>>& OutValue)` (scope `UE::Json`)
- L517 _function_ `template <typename ValueType> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TOptional<TSharedRef<ValueType>>& OutValue)` (scope `UE::Json`) — Optional SharedRef
- L529 _function_ `template <typename ValueType> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TOptional<TSharedRef<ValueType>>& OutValue)` (scope `UE::Json`)
- L540 _function_ `template <typename ValueType, typename> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, ValueType& OutValue)` (scope `UE::Json`) — JsonObject
- L552 _function_ `template <typename ValueType, typename> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TSharedPtr<FJsonObject>& OutValue)` (scope `UE::Json`)
- L562 _function_ `template <size_t TypeIndex = 0, typename ...ValueTypes> bool TryParse(const TSharedPtr<FJsonValue>& InJsonValue, TVariant<ValueTypes...>& OutValue)` (scope `UE::Json`)
- L564 _typedef_ `using VariantType = TVariant<ValueTypes...>;` (scope `UE::Json::TryParse`)
- L567 _typedef_ `using ValueType = typename TNthTypeFromParameterPack<TypeIndex, ValueTypes...>::Type;` (scope `UE::Json::TryParse`)
- L585 _function_ `template <typename... ValueTypes> bool TryGet(const TSharedPtr<FJsonValue>& InJsonValue, TVariant<ValueTypes...>& OutValue)` (scope `UE::Json`) — Variant
- L595 _function_ `template <typename... ValueTypes> bool TryGetField(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InFieldName, TVariant<ValueTypes...>& OutValue)` (scope `UE::Json`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIMessageLog.h` (Public)


#### enum `EVerbosityLevel`  
`enum class EVerbosityLevel : uint8`  
_L13-18_
- desc: Log verbosity level
- L15 _public enumerator_ `Log`
- L16 _public enumerator_ `Warning`
- L17 _public enumerator_ `Error`

#### class `FWebAPIMessageLog`  
`class FWebAPIMessageLog final : public TSharedFromThis<FWebAPIMessageLog>`  
_L21-64_
- inherits: `TSharedFromThis<FWebAPIMessageLog>`
- desc: WebAPI Message Log, unique to each definition (when editing).
- L24 _public prototype_ `FWebAPIMessageLog();`
- L31 _public prototype_ `void LogInfo(const FText& InMessage, const FString& InCallerName = TEXT(""));` — Log an information message @param InMessage			The text message to log @param InCallerName		Message type: provider or generator name
- L38 _public prototype_ `void LogWarning(const FText& InMessage, const FString& InCallerName = TEXT(""));` — Logs a warning message @param InMessage			The text message to log @param InCallerName		Message type: provider or generator name
- L45 _public prototype_ `void LogError(const FText& InMessage, const FString& InCallerName = TEXT(""));` — Logs an error message @param InMessage			The text message to log @param InCallerName		Message type: provider or generator name
- L48 _public prototype_ `void ClearLog() const;` — Removes all messages from log.
- L51 _public function_ `TSharedPtr<IMessageLogListing> GetMessageLogListing() const` — Log listing interface.
- L60 _private prototype_ `template <EVerbosityLevel VerbosityLevel> void Log(const FText& InMessage, const FString& InCallerName = TEXT(""));` — Log a message @param InMessage			The text message to log @param InCallerName		Message type: provider or generator name
- L63 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;` — Log listing interface.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIProvider.h` (Public)


#### enum `EWebAPIConversionResult`  
`enum class EWebAPIConversionResult : uint8`  
_L10-16_
- L12 _public enumerator_ `Failed = 0`
- L13 _public enumerator_ `Succeeded = 1`
- L14 _public enumerator_ `FailedWithErrors = 2`
- L15 _public enumerator_ `FailedWithWarnings = 3`

#### class `IWebAPIProviderInterface`  
`class IWebAPIProviderInterface : public TSharedFromThis<IWebAPIProviderInterface>`  
_L19-27_
- inherits: `TSharedFromThis<IWebAPIProviderInterface>`
- desc: Interface for a provider of a WebAPI Schema
- L23 _public prototype_ `virtual ~IWebAPIProviderInterface() = default;`
- L26 _public prototype_ `virtual TFuture<EWebAPIConversionResult> ConvertToWebAPISchema(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition) = 0;` — Convert and modify the WebAPISchema for the given Definition. Returns true if successful.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIProviderSettings.h` (Public)


#### struct `FWebAPIProviderSettings`  
`struct FWebAPIProviderSettings`  
_L12-89_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates settings for WebAPI providers.
- L17 _public prototype_ `FString MakeRequestTypeName(const FWebAPITypeNameVariant& InOperationName) const;` — Makes a unique TypeName based on the provided Operation name.
- L20 _public prototype_ `FString MakeResponseTypeName(const FWebAPITypeNameVariant& InOperationName, const uint32& InResponseCode) const;` — Makes a unique TypeName based on the provided Operation name and response code.
- L23 _public prototype_ `FString MakeNestedPropertyTypeName(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName) const;` — Makes a unique TypeName based on the provided Model and Property names.
- L26 _public prototype_ `FString MakeParameterTypeName(const FWebAPINameVariant& InParameterName) const;` — Makes a unique TypeName based on the provided Parameter name.
- L29 _public prototype_ `FName MakeOperationObjectName(const TObjectPtr<UWebAPIService>& InService, const FWebAPITypeNameVariant& InOperationName) const;` — Makes a unique TypeName based on the provided Service and Operations names.
- L32 _public prototype_ `const FString& GetUnsetEnumValueName();` — Return the name of an "unset" value for a generated enum. This allows optional enums that aren't otherwise supported as FProperties.
- L35 _public prototype_ `const FString& GetDefaultPropertyName();` — Return the default name given to (single item) properties.
- L38 _public prototype_ `const FString& GetDefaultArrayPropertyName();` — Return the default name given to array properties.
- L41 _public prototype_ `FString ToPascalCase(const FWebAPINameVariant& InString) const;` — Converts the given string to Pascal Case (aka. Upper Camel Case).
- L44 _public prototype_ `FString ToInitials(const FWebAPINameVariant& InString) const;` — Converts the given string to it's initials.
- L47 _public prototype_ `FString MakeValidMemberName(const FWebAPINameVariant& InString, const FString& InPrefix = {}) const;` — Strips the provided string of invalid characters for a member name. Optionally provide a prefix for invalid member names (ie. that start with a number).
- L50 _public prototype_ `FString Singularize(const FString& InString) const;` — Returns a singularized version of the provided plural string. Currently only works for english words.
- L53 _public prototype_ `FString Pluralize(const FString& InString) const;` — Returns a pluralized version of the provided string. Currently only works for english words.
- L58 _public member_ `bool bEnableArbitraryJsonPayloads = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Provider")` — Enable this option to allow the user to supply arbitrary json data to any request without parameters.
- L64 _private member_ `FString RequestTypeNameTemplate = TEXT("{Op` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L67 _private member_ `FString ResponseTypeNameTemplate = TEXT("{Op` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L70 _private member_ `FString NestedPropertyTypeNameTemplate = TEXT("{Mo` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L73 _private member_ `FString ParameterTypeNameTemplate = TEXT("{Pa` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L76 _private member_ `FString OperationObjectNameTemplate = TEXT("{Cl` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L79 _private member_ `FString UnsetEnumValueName = TEXT("Uns` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L82 _private member_ `FString DefaultPropertyName = TEXT("Val` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L85 _private member_ `FString DefaultArrayPropertyName = TEXT("Val` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Provider")`
- L88 _private prototype_ `FString PopulateTemplate(const FString& InTemplateString, const FStringFormatNamedArguments& InArgs) const;` — Makes a unique TypeName based on the provided Operation Name.
