# Editor / RenderResourceViewer

- module root: `Source/Editor/RenderResourceViewer`
- headers: 3; symbols: 64
- symbol kinds: class=3, enum=1, enumerator=3, function=14, member=24, prototype=18, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, InputCore, RHI, Slate, SlateCore, TreeMap, UnrealEd
- PrivateIncludePathModuleNames: ContentBrowser, WorkspaceMenuStructure

### `Source/Editor/RenderResourceViewer/Private/SRenderResourceViewer.h` (Private)


#### class `SRenderResourceViewerWidget`  
`class SRenderResourceViewerWidget : public SCompoundWidget`  
_L17-87_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRenderResourceViewerWidget)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);`
- L25 _public prototype_ `SRenderResourceViewerWidget();`
- L26 _public prototype_ `~SRenderResourceViewerWidget() = default;`
- L28 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L31 _private prototype_ `void RefreshNodes(bool bUpdateRHIResources = false);`
- L32 _private prototype_ `void RefreshSizeMap();`
- L33 _private prototype_ `TSharedRef<ITableRow> HandleResourceGenerateRow(TSharedPtr<FRHIResourceStats> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L34 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L36 _private function_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const`
- L37 _private function_ `FText GetResourceCountText() const`
- L38 _private prototype_ `FText GetResourceSizeText() const;`
- L39 _private function_ `void FilterTextBox_OnTextChanged(const FText& InFilterText)`
- L40 _private function_ `void OnResidentComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L41 _private function_ `void OnTransientComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L42 _private function_ `void OnStreamingComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L43 _private function_ `void OnRTComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L44 _private function_ `void OnDSComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L45 _private function_ `void OnUAVComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L46 _private function_ `void OnRTASComboboxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)`
- L47 _private function_ `FReply OnRefreshButtonClicked()`
- L48 _private prototype_ `void InitCommandList();`
- L49 _private prototype_ `TSharedPtr<SWidget> OpenContextMenu();`
- L50 _private prototype_ `void ContextMenu_FindInContentBrowser();`
- L51 _private prototype_ `bool ContextMenu_FindInContentBrowser_CanExecute() const;`
- L59 _private prototype_ `EComboBoxType ComboBoxNameToType(TSharedPtr<FString> Value) const;`
- L60 _private function_ `TSharedPtr<FString> ComboBoxTypeToName(EComboBoxType Type) const`
- L61 _private prototype_ `bool ShouldShow(EComboBoxType FilterType, bool bValue) const;`
- L63 _private member_ `TArray<TSharedPtr<FRHIResourceStats>> RHIResources;`
- L64 _private member_ `TSharedPtr<SListView<TSharedPtr<FRHIResourceStats>>> ResourceListView;`
- L65 _private member_ `TArray<TSharedPtr<FRHIResourceStats>> ResourceInfos;`
- L66 _private member_ `FName SortByColumn;`
- L67 _private member_ `EColumnSortMode::Type SortMode;`
- L68 _private member_ `FText FilterText;`
- L69 _private member_ `TSharedPtr< class SEditableTextBox > FilterTextBox;`
- L70 _private member_ `uint64 TotalResourceCount = 0;`
- L71 _private member_ `uint64 TotalResourceSize = 0;`
- L72 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L73 _private member_ `TArray<TSharedPtr<FString>> ComboBoxNames;`
- L76 _private member_ `TSharedPtr<class STreeMap> TreeMapWidget;` — Our tree map widget
- L78 _private member_ `TSharedPtr<class FTreeMapNodeData> RootTreeMapNode;` — Our tree map source data
- L80 _private member_ `EComboBoxType ShowResident = EComboBoxType::Any;` — Show resource with Resident flag set
- L81 _private member_ `EComboBoxType ShowTransient = EComboBoxType::No;` — Show resource with Transient flag set
- L82 _private member_ `EComboBoxType ShowStreaming = EComboBoxType::Any;` — Show resource with Streaming flag set
- L83 _private member_ `EComboBoxType ShowRT = EComboBoxType::Any;` — Show resource with RenderTarget flag set
- L84 _private member_ `EComboBoxType ShowDS = EComboBoxType::Any;` — Show resource with DepthStencil flag set
- L85 _private member_ `EComboBoxType ShowUAV = EComboBoxType::Any;` — Show resource with UAV flag set
- L86 _private member_ `EComboBoxType ShowRTAS = EComboBoxType::Any;` — Show resource with RayTracingAccelationStructure flag set

#### enum `SRenderResourceViewerWidget::EComboBoxType`  
`enum class EComboBoxType : uint8`  
_L53-58_
- L55 _public enumerator_ `Any`
- L56 _public enumerator_ `Yes`
- L57 _public enumerator_ `No`

### `Source/Editor/RenderResourceViewer/Public/RenderResourceViewerModule.h` (Public)


#### class `FRenderResourceViewerModule`  
`class FRenderResourceViewerModule : public IModuleInterface`  
_L16-38_
- inherits: `IModuleInterface`
- desc: Struct Viewer module
- L22 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L27 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L30 _private prototype_ `TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& Args);`
- L32 _private function_ `void AssignWindow(const TSharedRef<SRenderResourceViewerWidget>& InWindow)`
- L37 _private member_ `TWeakPtr<class SRenderResourceViewerWidget> RenderResourceViewerWindow;`

### `Source/Editor/RenderResourceViewer/Public/RenderResourceViewerSettings.h` (Public)


#### struct `FRenderResourceViewerTreemapFilter`  
`struct FRenderResourceViewerTreemapFilter`  
_L10-19_
- reflection: `USTRUCT()`
- L15 _public member_ `FString FilterString;` — `UPROPERTY(config, EditAnywhere, Category = "Section")`
- L18 _public member_ `FString DisplayName;` — `UPROPERTY(config, EditAnywhere, Category = "Section")`

#### class `URenderResourceViewerSettings`  
`class URenderResourceViewerSettings : public UDeveloperSettings`  
_L22-28_
- reflection: `UCLASS(MinimalAPI, config = Editor, DefaultConfig, meta = (DisplayName = "Render Resource Viewer"))`
- inherits: `UDeveloperSettings`
- L27 _private member_ `TArray<FRenderResourceViewerTreemapFilter> Filters;` — `UPROPERTY(Config, EditAnywhere, Category = "Treemap")`
