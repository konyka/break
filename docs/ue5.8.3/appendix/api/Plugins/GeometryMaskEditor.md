# Plugins / GeometryMaskEditor

- module root: `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor`
- headers: 9; symbols: 136
- symbol kinds: class=10, delegate=1, function=9, member=40, prototype=70, struct=3, typedef=3
- PrivateDependencyModuleNames: Core, Engine, InputCore, Slate, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: CoreUObject, GeometryMask, SlateCore

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/GeometryMaskEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryMaskEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryMaskEditor, Log, All);`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/GeometryMaskEditorModule.h` (Private)


#### class `FGeometryMaskEditorModule`  
`class FGeometryMaskEditorModule : public IModuleInterface`  
_L14-43_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _private prototype_ `void RegisterConsoleCommands();` — Called from StartupModule and sets up console commands for the plugin via IConsoleManager
- L28 _private prototype_ `void UnregisterConsoleCommands();` — Called from ShutdownModule and clears out previously registered console commands
- L30 _private prototype_ `void ExecuteShowVisualizer(const TArray<FString>& InArgs);`
- L32 _private prototype_ `void ExecutePause(const TArray<FString>& InArgs);`
- L34 _private prototype_ `void ExecuteFlush(const TArray<FString>& InArgs);`
- L37 _private member_ `static const FName VisualizerTabId;`
- L40 _private member_ `TArray<IConsoleObject*> ConsoleCommands;` — References of registered console commands via IConsoleManager
- L42 _private member_ `TWeakPtr<SDockTab> VisualizerTabWeak;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/ViewModels/GMECanvasItemViewModel.h` (Private)


#### class `FGMECanvasItemViewModel`  
`class FGMECanvasItemViewModel : public FGMETickableViewModelBase , public FEditorUndoClient , public IGMETreeNodeViewModel`  
_L17-54_
- inherits: `FGMETickableViewModelBase,FEditorUndoClient,IGMETreeNodeViewModel`
- L27 _public prototype_ `static TSharedRef<FGMECanvasItemViewModel> Create(const TWeakObjectPtr<const UGeometryMaskCanvas>& InCanvas);`
- L29 _public prototype_ `FGMECanvasItemViewModel(FPrivateToken, const TWeakObjectPtr<const UGeometryMaskCanvas>& InCanvas);`
- L30 _public prototype_ `virtual ~FGMECanvasItemViewModel() override = default;`
- L32 _public prototype_ `virtual bool Tick(const float InDeltaSeconds) override;`
- L35 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IGMETreeNodeViewModel>>& OutChildren) override;`
- L38 _public prototype_ `const FGeometryMaskCanvasId& GetCanvasId() const;`
- L39 _public prototype_ `FName GetCanvasName() const;`
- L40 _public prototype_ `const FText& GetCanvasInfo() const;`
- L41 _public prototype_ `const UTexture* GetCanvasTexture() const;`
- L42 _public prototype_ `float GetMemoryUsage();`
- L45 _private prototype_ `void UpdateInfoText();`
- L48 _private member_ `FGeometryMaskCanvasId CanvasId;`
- L49 _private member_ `FText InfoText;`
- L50 _private member_ `TWeakObjectPtr<const UGeometryMaskCanvas> CanvasWeak;`
- L51 _private member_ `TWeakObjectPtr<UTexture> CanvasTextureWeak;`
- L52 _private member_ `int32 KnownReaderCount;`
- L53 _private member_ `int32 KnownWriterCount;`

#### struct `FGMECanvasItemViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L24-24_
- desc: Private token only allows members or friends to call MakeShared
- L24 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/ViewModels/GMECanvasListViewModel.h` (Private)


#### class `FGMECanvasListViewModel`  
`class FGMECanvasListViewModel : public FGMEListViewModelBase , public FEditorUndoClient , public IGMETreeNodeViewModel`  
_L12-52_
- inherits: `FGMEListViewModelBase,FEditorUndoClient,IGMETreeNodeViewModel`
- L17 _private typedef_ `using Super = FGMEListViewModelBase;`
- L24 _public prototype_ `static TSharedRef<FGMECanvasListViewModel> Create();`
- L26 _public function_ `explicit FGMECanvasListViewModel(FPrivateToken) : Super(Super::FPrivateToken{})`
- L31 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IGMETreeNodeViewModel>>& OutChildren) override;`
- L35 _private prototype_ `virtual bool RefreshItems() override;`
- L37 _private prototype_ `virtual void OnPostWorldInit(UWorld* InWorld, const UWorld::InitializationValues InWorldValues) override;`
- L38 _private prototype_ `virtual void OnPreWorldDestroyed(UWorld* InWorld) override;`
- L40 _private prototype_ `void OnCanvasCreated(const UGeometryMaskCanvas* InGeometryMaskCanvas);`
- L41 _private prototype_ `void OnCanvasDestroyed(const FGeometryMaskCanvasId& InGeometryMaskCanvasId);`
- L44 _private member_ `TMap<TObjectKey<ULevel>, FDelegateHandle> OnCanvasCreatedHandles;`
- L45 _private member_ `TMap<TObjectKey<ULevel>, FDelegateHandle> OnCanvasDestroyedHandles;`
- L48 _private member_ `TMap<TObjectKey<ULevel>, TArray<FName>> LastCanvasNames;` — Cached canvas names for comparison/refresh.
- L51 _private member_ `TArray<TSharedPtr<FGMECanvasItemViewModel>> CanvasItems;` — Canvas ViewModels

#### struct `FGMECanvasListViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L21-21_
- desc: Private token only allows members or friends to call MakeShared
- L21 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/ViewModels/GMEViewModelShared.h` (Private)


#### class `IGMETreeNodeViewModel`  
`class IGMETreeNodeViewModel`  
_L12-20_
- desc: Common interface for treeview nodes.
- L15 _protected prototype_ `~IGMETreeNodeViewModel() = default;`
- L19 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IGMETreeNodeViewModel>>& OutChildren) = 0;` — See STreeView::OnGetChildren, return false if no children.

#### class `FGMETickableViewModelBase`  
`class FGMETickableViewModelBase : public TSharedFromThis<FGMETickableViewModelBase>`  
_L22-36_
- inherits: `TSharedFromThis<FGMETickableViewModelBase>`
- L26 _public prototype_ `FGMETickableViewModelBase();`
- L27 _public prototype_ `virtual ~FGMETickableViewModelBase();`
- L30 _protected function_ `virtual bool Tick(const float InDeltaSeconds)`
- L34 _protected member_ `static constexpr float UpdateCheckInterval = 0.15f;` — In seconds.
- L35 _protected member_ `FTSTicker::FDelegateHandle UpdateCheckHandle;`

#### class `FGMEListViewModelBase`  
`class FGMEListViewModelBase : public FGMETickableViewModelBase`  
_L38-75_
- inherits: `FGMETickableViewModelBase`
- L46 _public prototype_ `explicit FGMEListViewModelBase(FPrivateToken);`
- L50 _public typedef_ `using FOnChanged = TMulticastDelegate<void()>;`
- L53 _public function_ `FOnChanged& OnChanged()` — Something has changed within the ViewModel
- L56 _protected prototype_ `virtual void Initialize();`
- L57 _protected prototype_ `virtual bool RefreshItems() = 0;`
- L59 _protected prototype_ `virtual bool Tick(const float InDeltaSeconds) override;`
- L61 _protected prototype_ `virtual void OnPostWorldInit(UWorld* InWorld, const UWorld::InitializationValues InWorldValues);`
- L62 _protected prototype_ `virtual void OnPreWorldDestroyed(UWorld* InWorld);`
- L66 _protected member_ `static constexpr float UpdateCheckInterval = 1.0f;` — In seconds.
- L67 _protected member_ `FTSTicker::FDelegateHandle UpdateCheckHandle;`
- L69 _protected member_ `TArray<TObjectKey<UWorld>> LoadedWorlds;`
- L71 _protected member_ `FDelegateHandle OnPostWorldInitDelegateHandle;`
- L72 _protected member_ `FDelegateHandle OnPreWorldDestroyedDelegateHandle;`
- L74 _protected member_ `FOnChanged OnChangedDelegate;`

#### struct `FGMEListViewModelBase::FPrivateToken`  
`struct FPrivateToken`  
_L43-43_
- desc: Private token only allows members or friends to call MakeShared
- L43 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/Widgets/SGMECanvasItem.h` (Private)


#### class `SGMECanvasItem`  
`class SGMECanvasItem : public SGMEImageItem<FGMECanvasItemViewModel>`  
_L13-29_
- inherits: `SGMEImageItem<FGMECanvasItemViewModel>`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGMECanvasItem)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FGMECanvasItemViewModel>& InViewModel);`
- L24 _protected prototype_ `FText GetLabel() const;`
- L25 _protected prototype_ `virtual FOptionalSize GetAspectRatio() override;`
- L28 _private member_ `TSharedPtr<FGMECanvasItemViewModel> ViewModel;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/Widgets/SGMECanvasList.h` (Private)


#### class `SGMECanvasList`  
`class SGMECanvasList : public SCompoundWidget`  
_L13-37_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGMECanvasList)`
- L21 _public prototype_ `virtual ~SGMECanvasList() override;`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FGMECanvasListViewModel> InViewModel);` — Constructs this widget with InArgs
- L27 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IGMETreeNodeViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L29 _private prototype_ `void Refresh();`
- L32 _private member_ `TSharedPtr<FGMECanvasListViewModel> ViewModel;`
- L34 _private member_ `TSharedPtr<SListView<TSharedPtr<IGMETreeNodeViewModel>>> CanvasListWidget;`
- L36 _private member_ `TArray<TSharedPtr<IGMETreeNodeViewModel>> CanvasItems;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Private/Widgets/SGMEImageItem.h` (Private)


#### class `SGMEImageItem`  
`template <typename InViewModelType> class SGMEImageItem : public STableRow<TSharedPtr<InViewModelType>>`  
_L21-97_
- inherits: `STableRow<TSharedPtr<InViewModelType>>`
- L23 _private typedef_ `using FTableRowArgs = typename STableRow<TSharedPtr<InViewModelType>>::FArguments;`
- L26 _public function_ `SLATE_BEGIN_ARGS(SGMEImageItem)`
- L28 _public function_ `SLATE_ATTRIBUTE(FText, Label) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L78 _protected prototype_ `virtual FOptionalSize GetAspectRatio() = 0;`
- L81 _protected function_ `FOptionalSize GetHeight()` — Get desired height based on the actual width.
- L95 _protected member_ `TSharedPtr<SPanel> ImageContainerWidget;`
- L96 _protected member_ `TSharedPtr<SWidget> ImageWidget;`

### `Plugins/VirtualProduction/GeometryMask/Source/GeometryMaskEditor/Public/Widgets/SGeometryMaskCanvasPreview.h` (Public)


#### class `SGeometryMaskCanvasPreview`  
`class SGeometryMaskCanvasPreview : public SCompoundWidget , public FGCObject`  
_L15-125_
- inherits: `SCompoundWidget,FGCObject`
- desc: Displays a named GeometryMaskCanvas.
- L20 _public function_ `SLATE_BEGIN_ARGS(SGeometryMaskCanvasPreview)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(FGeometryMaskCanvasId, CanvasId) SLATE_ATTRIBUTE_DEPRECATED(EGeometryMaskColorChannel, Channel, 5.8, "Color channel management has been deprecated as it's no longer needed") SLATE_ATTRIBUTE(bool, PaddingFrameVisibility) SLATE_ATTRIBUTE(bool, Invert) SLATE_ATTRIBUTE(bool, SolidBackground) SLATE_ATTRIBUTE(float, Opacity) SLATE_END_ARGS() SGeometryMaskCanvasPreview();`
- L33 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L35 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L38 _public prototype_ `const FGeometryMaskCanvasId& GetCanvasId() const;` — Get the id of the currently referenced canvas.
- L41 _public prototype_ `void SetCanvasId(const FGeometryMaskCanvasId& InCanvasId);` — Sets the id of the currently referenced canvas, and resolves the canvas itself.
- L44 _public prototype_ `const FName GetCanvasName() const;` — Get the name of the currently referenced canvas.
- L47 _public prototype_ `const EGeometryMaskColorChannel GetColorChannel(const bool bOnlyValid = true) const;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L50 _public prototype_ `void SetColorChannel(const EGeometryMaskColorChannel InColorChannel);` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")`
- L52 _public prototype_ `const bool IsPaddingFrameVisible() const;`
- L54 _public prototype_ `void SetPaddingFrameVisiblity(const bool bInIsVisible);`
- L57 _public prototype_ `const bool IsInverted() const;` — Get whether to invert the display of the canvas.
- L60 _public prototype_ `void SetInvert(const bool bInInverted);` — Set whether to invert the display of the canvas.
- L63 _public prototype_ `const bool GetSolidBackground() const;` — Get whether a solid background is used or not (vs. compositing with alpha on widgets below).
- L66 _public prototype_ `void SetSolidBackground(const bool bInHasSolidBackground);` — Set whether a solid background is used or not (vs. compositing with alpha on widgets below).
- L69 _public prototype_ `const float GetOpacity() const;` — Get the overall opacity multiplier value.
- L72 _public prototype_ `void SetOpacity(const float InValue);` — Set the overall opacity multiplier value.
- L75 _public prototype_ `UGeometryMaskCanvas* GetCanvas() const;` — Get the currently referenced canvas.
- L78 _public prototype_ `FOptionalSize GetAspectRatio();` — Get the aspect ratio of the referenced canvas.
- L81 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L82 _public prototype_ `virtual FString GetReferencerName() const override;`
- L86 _private prototype_ `bool TryResolveCanvas();`
- L88 _private prototype_ `void UpdateBrush(const UGeometryMaskCanvas* InCanvas);`
- L94 _private prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);` — Called when the world is being cleaned up Used to remove the mask texture reference from the preview MIDs if the textures belong to the world being cleaned up
- L97 _private member_ `TSharedPtr<FSlateBrush> PreviewBrush;`
- L98 _private member_ `FSoftObjectPath PreviewMaterialPath;`
- L99 _private member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMID;`
- L101 _private member_ `FSoftObjectPath DefaultTexturePath;`
- L102 _private member_ `TObjectPtr<UTextureRenderTarget2DArray> DefaultTexture;`
- L104 _private member_ `TWeakObjectPtr<UGeometryMaskCanvas> CanvasWeak;`
- L107 _private member_ `TAttribute<FGeometryMaskCanvasId> CanvasId;` — Id of the currently referenced canvas.
- L109 _private member_ `TAttribute<bool> bShowPaddingFrame;`
- L112 _private member_ `TAttribute<bool> Invert;` — Whether to invert the display of the canvas.
- L115 _private member_ `TAttribute<bool> HasSolidBackground;` — Whether a solid background is used or not (vs. compositing with alpha on widgets below).
- L118 _private member_ `TAttribute<float> OpacityMultiplier;` — Multiplies the overall opacity.
- L121 _private member_ `TAttribute<FOptionalSize> AspectRatio;` — Stores the aspect ratio of the referenced canvas.
- L124 _private member_ `FDelegateHandle OnWorldCleanupDelegateHandle;` — Handle to the delegate called when world gets cleaned up
