# Plugins / ModelViewViewModelPreview

- module root: `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview`
- headers: 7; symbols: 105
- symbol kinds: class=6, function=3, member=21, namespace=39, prototype=36
- PrivateDependencyModuleNames: AdvancedWidgets, ApplicationCore, Core, CoreUObject, DesktopPlatform, FieldNotification, InputCore, Json, MessageLog, ModelViewViewModel, ModelViewViewModelBlueprint, Projects, Slate, SlateCore, UMG, UMGWidgetPreview
- PrivateIncludePathModuleNames: UMGWidgetPreview

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/MVVMUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::MVVM`)
- L15 _namespace_ `namespace Utils` (scope `UE::MVVM::Private`)
- L19 _prototype_ `TOptional<FText> GetPropertyValue(UObject* SourceObject, FProperty* InProperty);` (scope `UE::MVVM::Private::Utils`) — Return a textual representation of the property's value Returns an unset optional on failure.
- L23 _prototype_ `TOptional<FText> GetFunctionValue(UObject* SourceObject, UFunction* InFunction);` (scope `UE::MVVM::Private::Utils`) — Call the function and return a text representation of its return value. Returns an unset optional on failure.
- L27 _prototype_ `TOptional<FText> GetFieldValue(TValueOrError<UE::MVVM::FFieldContext, void>& InFieldContext, bool bInAllowFunction);` (scope `UE::MVVM::Private::Utils`) — Return a textual representation of the field's value Returns an unset optional on failure.

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/MVVMWidgetPreviewExtension.h` (Private)


#### class `UE::MVVM::Private::FMVVMWidgetPreviewExtension`  
`class FMVVMWidgetPreviewExtension : public TSharedFromThis<FMVVMWidgetPreviewExtension>`  
_L16-31_
- inherits: `TSharedFromThis<FMVVMWidgetPreviewExtension>`
- L20 _public prototype_ `static FName GetPreviewSourceTabID();`
- L23 _public prototype_ `void Register(IUMGWidgetPreviewModule& InWidgetPreviewModule);` — Register various extensibility points with the WidgetPreviewModule.
- L25 _public prototype_ `void Unregister(IUMGWidgetPreviewModule* InWidgetPreviewModule);`
- L28 _private prototype_ `void HandleRegisterPreviewEditorTab(const TSharedPtr<UE::UMGWidgetPreview::IWidgetPreviewToolkit>& InPreviewEditor, const TSharedRef<FTabManager>& InTabManager);`
- L30 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSource(const FSpawnTabArgs& Args, TWeakPtr<UE::UMGWidgetPreview::IWidgetPreviewToolkit> InWeakPreviewEditor);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/ModelViewViewModelPreviewModule.h` (Private)


#### class `FMVVMPreviewModule`  
`class FMVVMPreviewModule : public IModuleInterface`  
_L16-28_
- inherits: `IModuleInterface`
- L19 _public member_ `static const FLazyName BindingMessageLogName;`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _private member_ `TSharedPtr<UE::MVVM::Private::FMVVMWidgetPreviewExtension> WidgetPreviewExtension;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/Styling/MVVMWidgetPreviewStyle.h` (Private)


#### class `UE::MVVM::Private::FMVVMWidgetPreviewStyle`  
`class FMVVMWidgetPreviewStyle : public FSlateStyleSet`  
_L9-20_
- inherits: `FSlateStyleSet`
- L13 _public member_ `static FName StyleName;`
- L15 _public prototype_ `static FMVVMWidgetPreviewStyle& Get();`
- L18 _private prototype_ `FMVVMWidgetPreviewStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MVVM` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/Widgets/SMVVMPreviewBindingLog.h` (Private)


#### class `UE::MVVM::Private::SMVVMPreviewBindingLog`  
`class SMVVMPreviewBindingLog : public SCompoundWidget`  
_L46-122_
- inherits: `SCompoundWidget`
- desc: Log to display the changes in the UMG Preview Widget MVVM Values/Bindings
- L49 _public function_ `SLATE_BEGIN_ARGS(SMVVMPreviewBindingLog)`
- L50 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<UMGWidgetPreview::IWidgetPreviewToolkit> InPreviewEditor);`
- L57 _private member_ `TWeakPtr<UMGWidgetPreview::IWidgetPreviewToolkit> WeakPreviewEditor;`
- L58 _private member_ `TWeakObjectPtr<UWidgetPreview> WeakWidgetPreview;`
- L59 _private member_ `TWeakObjectPtr<UMVVMView> WeakView;`
- L61 _private member_ `FDelegateHandle OnWidgetChangedHandle;`
- L64 _private member_ `FDelegateHandle OnOnLibraryBindingExecutedHandle;`
- L69 _private member_ `TArray<TWeakObjectPtr<UObject>> WeakSources;` — Must implement INotifyFieldValueChanged Stored here to remember whose events we subscribed to.
- L72 _private member_ `FDelegateHandle OnViewSourceChangedHandle;`
- L75 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`
- L76 _private member_ `TSharedPtr<SWidget> MessageLogWidget;`
- L79 _private prototype_ `void SetPreviewEditor(TSharedPtr<UMGWidgetPreview::IWidgetPreviewToolkit> InPreviewEditor);` — Sets and unsets the preview editor, adding and removing bindings.
- L82 _private prototype_ `void SetWidgetPreview(UWidgetPreview* InWidgetPreview);` — Sets and unsets the widget preview object, adding and removing bindings.
- L85 _private prototype_ `void SetPreviewWidget(UUserWidget* InWidget);` — Checks the current view to see if we need to update it with this widget's view.
- L88 _private prototype_ `void SetView(UMVVMView* InView);` — Sets and unsets the view.
- L91 _private prototype_ `void HandleOnWidgetChanged(const EWidgetPreviewWidgetChangeType InChangeType);` — When the widget in the preview is changed, update the view.
- L94 _private prototype_ `void HandleOnLibraryBindingExecuted(const FDebugging::FView& InView, const FDebugging::FLibraryBindingExecutedArgs& InArgs);`
- L98 _private prototype_ `void SetSources(const TArray<UObject*>& InSources);` — Removes previous binds to field notify sources and adds new binds to the provided sources.
- L102 _private prototype_ `void HandleOnViewSourceChanged(const FDebugging::FView& InView, const FDebugging::FViewSourceValueArgs& InArgs);` — When the sources change, update the source bindings.
- L106 _private prototype_ `void HandleOnFieldValueChanged(UObject* InSourceObject, UE::FieldNotification::FFieldId InFieldId);` — When a field notify value changes, produce a log entry.
- L109 _private prototype_ `TSharedRef<FTokenizedMessage> MakeLog(EMessageSeverity::Type InSeverity, const FText& InMessage);` — Creates a log message in the binding log message log and returns it.
- L112 _private prototype_ `void AddSourceToken(TSharedRef<FTokenizedMessage> InMessage, TNotNull<UObject*> InSource);` — Adds an action token that selects the given source object.
- L115 _private prototype_ `void HandleObjectTokenClicked(TWeakObjectPtr<UObject> InWeakObject);` — Callback to select an object.
- L118 _private prototype_ `void AddCopyToken(TSharedRef<FTokenizedMessage> InMessage, const FText& InText);` — Adds an action that copies the given text to the clipboard
- L121 _private prototype_ `void HandleCopyTokenClicked(FText InText);` — Handles the copy callback to copy text to the clipboard

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace EMessageSeverity`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace FieldNotification` (scope `UE`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace MVVM` (scope `UE`)
- L39 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/Widgets/SMVVMPreviewSourcePanel.h` (Private)


#### class `UE::MVVM::Private::SPreviewSourcePanel`  
`class SPreviewSourcePanel : public SCompoundWidget`  
_L29-58_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SPreviewSourcePanel)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<UMGWidgetPreview::IWidgetPreviewToolkit> PreviewEditor);`
- L40 _private prototype_ `void HandlePreviewWidgetChanged(const EWidgetPreviewWidgetChangeType InChangeType);`
- L41 _private prototype_ `void HandleSelectedObjectChanged(const TConstArrayView<TWeakObjectPtr<UObject>> InSelectedObjects);`
- L42 _private prototype_ `void HandleSourceSelectionChanged(TSharedPtr<Private::SPreviewSourceEntry> Entry, ESelectInfo::Type SelectionType) const;`
- L44 _private prototype_ `void HandleViewChanged(const FDebugging::FView&, const FDebugging::FViewSourceValueArgs&);`
- L46 _private prototype_ `TSharedRef<ITableRow> GenerateWidget(TSharedPtr<Private::SPreviewSourceEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L47 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpened();`
- L48 _private prototype_ `void ExecuteDumpData(TSharedPtr<Private::SPreviewSourceEntry> InEntry);`
- L50 _private member_ `TWeakObjectPtr<UMVVMView> WeakView;`
- L51 _private member_ `TWeakPtr<UMGWidgetPreview::IWidgetPreviewToolkit> WeakPreviewEditor;`
- L52 _private member_ `TSharedPtr<Private::SPreviewSourceView> SourceListView;`
- L53 _private member_ `TArray<TSharedPtr<Private::SPreviewSourceEntry>> SourceList;`
- L54 _private member_ `mutable bool bIsSelectingListItem = false;`
- L56 _private member_ `FDelegateHandle OnWidgetChangedHandle;`
- L57 _private member_ `FDelegateHandle OnSelectedObjectsChangedHandle;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MVVM` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::MVVM`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MVVM` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::MVVM`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace MVVM` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Editor/ModelViewViewModelPreview/Source/ModelViewViewModelPreview/Private/Widgets/SMVVMPreviewViewmodels.h` (Private)


#### class `UE::MVVM::Private::SMVVMPreviewViewmodels`  
`class SMVVMPreviewViewmodels : public SCompoundWidget`  
_L19-30_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SMVVMPreviewViewmodels)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<UMGWidgetPreview::IWidgetPreviewToolkit> InPreviewEditor);`
- L28 _private member_ `TSharedPtr<SWidget> SourcePanel;`
- L29 _private member_ `TSharedPtr<SWidget> BindingLog;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MVVM` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::MVVM`)
