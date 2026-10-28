# Plugins / ComposureLayersEditor

- module root: `Plugins/Compositing/Composure/Source/ComposureLayersEditor`
- headers: 21; symbols: 547
- symbol kinds: class=24, delegate=12, enum=1, enumerator=5, function=66, macro=7, member=114, namespace=3, prototype=298, struct=3, typedef=9, variable=5
- PrivateDependencyModuleNames: AppFramework, BlueprintMaterialTextureNodes, ClassViewer, Composure, ContentBrowser, Core, CoreUObject, DetailCustomizations, Engine, InputCore, LevelEditor, MediaIOCore, PropertyEditor, RHI, RenderCore, SceneOutliner, Slate, SlateCore, UnrealEd, WorkspaceMenuStructure
- PublicIncludePathModuleNames: EditorFramework, UnrealEd

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/CompElementCollectionViewModel.h` (Private)


#### class `FCompElementCollectionViewModel`  
`class FCompElementCollectionViewModel : public TSharedFromThis<FCompElementCollectionViewModel>, public FEditorUndoClient`  
_L22-230_
- inherits: `TSharedFromThis<FCompElementCollectionViewModel>,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a comp elements' view.
- L31 _public function_ `static TSharedRef<FCompElementCollectionViewModel> Create(const TSharedRef<ICompElementManager>& InElementsManager, const TWeakObjectPtr<UEditorEngine>& InEditor)` — Factory method which creates a new FCompElementCollectionViewModel object. @param	InElementsManager	The element management logic object @param	InEditor			The UEditorEngine to register with (for undo/redo, etc.)
- L39 _public prototype_ `virtual ~FCompElementCollectionViewModel();`
- L43 _public function_ `virtual void PostUndo(bool bSuccess) override`
- L44 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L50 _public prototype_ `void AddFilter(const TSharedRef<FCompElementFilter>& InFilter);` — Hook for the UI search box (and others) to filter the model's element list.
- L55 _public prototype_ `void RemoveFilter(const TSharedRef<FCompElementFilter>& InFilter);` — Clears an existing filter from the elements list (refreshes the lists returned by GetCompShots() and GetElementsForComp()
- L60 _public prototype_ `TArray< TSharedPtr<FCompElementViewModel> >& GetRootCompElements();` — Returns the (filtered) list of top-level compositing elements (for the UI to display).
- L65 _public prototype_ `void GetChildElements(TSharedPtr<FCompElementViewModel> ParentPtr, TArray< TSharedPtr<FCompElementViewModel> >& OutChildElements);` — Returns a (filtered) list of child elements, nested directly under the specified CompItem.
- L72 _public prototype_ `TSharedPtr<FCompElementViewModel> GetSelectionProxy(const TSharedPtr<FCompElementViewModel>& SelectedItem) const;` — Some elements are not selectable (like child actors). This determines that and returns the (parent) element that should be selected instead. If the specified element is selectable, then this just returns that element.
- L75 _public prototype_ `const TArray< TSharedPtr<FCompElementViewModel> >& GetSelectedElements() const;` — Returns the a list of element model that are currently tracked as selected (should be reflected in the UI).
- L78 _public prototype_ `void GetSelectedElementNames(OUT TArray<FName>& OutSelectedElementNames) const;` — Appends the names of the currently selected elements to the provided array.
- L81 _public prototype_ `void SetSelectedElements(const TArray< TSharedPtr<FCompElementViewModel> >& InSelectedElements);` — Sets the specified array of element objects as the currently selected elements (provides a way to sync with the UI).
- L84 _public prototype_ `void SetSelectedElement(const FName& ElementName);` — Sets the current selection to the specified element.
- L87 _public prototype_ `const TSharedRef<FUICommandList> GetCommandList() const;` — Returns the bound UICommandList for the comp element view.
- L94 _public prototype_ `DECLARE_DERIVED_EVENT(FCompElementCollectionViewModel, ICompElementManager::FOnElementsChanged, FOnElementsChanged);` — Broadcasts whenever one or more elements change.
- L95 _public function_ `FOnElementsChanged& OnElementsChanged()`
- L98 _public prototype_ `DECLARE_EVENT(FCompElementCollectionViewModel, FOnSelectionChanged);` — Broadcasts whenever the currently selected elements change.
- L99 _public function_ `FOnSelectionChanged& OnSelectionChanged()`
- L102 _public prototype_ `DECLARE_EVENT(FCompElementCollectionViewModel, FOnRenameRequested);` — Broadcasts whenever a rename is requested on the selected elements.
- L103 _public function_ `FOnRenameRequested& OnRenameRequested()`
- L112 _private prototype_ `FCompElementCollectionViewModel(const TSharedRef<ICompElementManager>& InElementsManager, const TWeakObjectPtr<UEditorEngine>& InEditor);` — Private constructor to force users to go through Create(), which properly initializes the model. @param	InElementsManager	The element management logic object @param	InEditor			The UEditorEngine to register with (for undo/redo, etc.)
- L115 _private prototype_ `void Initialize();` — Initializes the elements view for use.
- L117 _private prototype_ `void BindCommands();` — Binds all element browser commands to delegates.
- L120 _private prototype_ `void Refresh();` — Refreshes any cached information.
- L123 _private prototype_ `void OnFilterChanged();` — Handles updating the view-model when one of its filters changes.
- L125 _private prototype_ `void OnElementsChanged(const ECompElementEdActions Action, const TWeakObjectPtr<ACompositingElement>& ChangedComp, const FName& ChangedProperty);`
- L127 _private prototype_ `void OnElementAdded(const TWeakObjectPtr<ACompositingElement>& AddedElement);`
- L129 _private prototype_ `void OnElementDelete();` — Handles updating the internal view-models when elements are deleted
- L131 _private prototype_ `void OnElementAttached(const TWeakObjectPtr<ACompositingElement>& AttachedElement);`
- L133 _private prototype_ `void OnResetElements();` — Refreshes the elements list
- L136 _private prototype_ `void DestructivelyPurgeInvalidViewModels(TArray< TWeakObjectPtr<ACompositingElement> >& InElements);` — Discards any element view-models which are invalid
- L138 _private prototype_ `void CreateViewModels(TArray< TWeakObjectPtr<ACompositingElement> >& ActualElements);` — Creates view-models for all elements in the specified list
- L140 _private prototype_ `void RebuildViewModelHierarchy();` — Updates the view-model hierarchy of known elements.
- L142 _private prototype_ `void RefreshFilteredElements();` — Rebuilds the list of filtered elements.
- L144 _private prototype_ `void SortFilteredElements();` — Sorts the filtered elements list
- L147 _private prototype_ `TSharedPtr<FCompElementViewModel> GetViewModel(TWeakObjectPtr<ACompositingElement> ElementObj);` — Looks up the view-model associated with the specified element object.
- L149 _private prototype_ `bool TryGetViewModel(TWeakObjectPtr<ACompositingElement> CompObjPtr, TSharedPtr<FCompElementViewModel>& OutViewModel);` — Looks up the view-model associated with the specified element object. Returns false if it couldn't find one.
- L151 _private prototype_ `void GetAllViewModels(TArray< TSharedPtr<FCompElementViewModel> >& OutAllViewModels);` — Returns a flat list of all element view-models (parents and children).
- L154 _private prototype_ `void AppendSelectedElementNames(TArray<FName>& OutElementNames) const;` — Appends the selected element names to the specified array
- L156 _private prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Updates the element selection from a selection made in the level editor.
- L158 _private prototype_ `void RefreshActorSelections() const;` — Updates actor selections from the internal selection state.
- L162 _private prototype_ `void CreateTopLevelElement_Executed();` — Creates a new top-level element, prompting the user to pick the class type first.
- L163 _private prototype_ `FName GenerateUniqueCompName() const;`
- L164 _private prototype_ `bool CreateTopLevelElement_CanExecute() const;`
- L167 _private prototype_ `void CreateChildElement_Executed();` — Creates a new child element, nesting it under the currently selected element.
- L168 _private prototype_ `FName GenerateUniqueElementName(TSubclassOf<ACompositingElement> ElementClass) const;`
- L169 _private prototype_ `bool CreateChildElement_CanExecute() const;`
- L172 _private prototype_ `void CutElements_Executed();` — Cuts the currently selected element
- L173 _private prototype_ `bool CutElements_CanExecute() const;`
- L176 _private prototype_ `void CopyElements_Executed();` — Copies the currently selected elements
- L177 _private prototype_ `bool CopyElements_CanExecute() const;`
- L180 _private prototype_ `void PasteElements_Executed();` — Pastes the currently selected elements
- L181 _private prototype_ `bool PasteElements_CanExecute() const;`
- L184 _private prototype_ `void DuplicateElements_Executed();` — Duplicates the currently selected elements
- L185 _private prototype_ `bool DuplicateElements_CanExecute() const;`
- L188 _private prototype_ `void DeleteElements_Executed();` — Deletes the currently selected elements
- L189 _private prototype_ `bool DeleteElements_CanExecute() const;`
- L192 _private prototype_ `void RequestRenameElement_Executed();` — Requests renaming of the selected element
- L193 _private prototype_ `bool RequestRenameElement_CanExecute() const;`
- L196 _private prototype_ `void OpenPreview_Executed();` — Opens a modeless dialog window, displaying the element's render result live.
- L197 _private prototype_ `bool OpenPreview_CanExecute() const;`
- L199 _private prototype_ `void RefreshList_Executed();` — Resets/Rebuilds the element list (useful in case the list gets stale by an unaccounted problem).
- L200 _private prototype_ `bool RefreshList_CanExecute() const;`
- L204 _private member_ `const TSharedRef<ICompElementManager> CompElementManager;` — The element management logic object.
- L206 _private member_ `const TWeakObjectPtr<UEditorEngine> Editor;` — The UEditorEngine to use.
- L208 _private member_ `const TSharedRef<FUICommandList> CommandList;` — The list of commands with bound delegates for the element browser.
- L211 _private member_ `TArray< TSharedPtr<FCompElementViewModel> > RootViewModels;` — All top-level elements managed by the view.
- L214 _private member_ `const TSharedRef<FCompElementFilterCollection> Filters;` — The collection of filters used to restrict the elements shown in the view.
- L217 _private member_ `TArray< TSharedPtr<FCompElementViewModel> > FilteredRootItems;` — All elements shown in the view.
- L218 _private typedef_ `typedef TMultiMap< TSharedPtr<FCompElementViewModel>, TSharedPtr<FCompElementViewModel> > FFilteredChildList;`
- L219 _private member_ `FFilteredChildList FilteredChildren;`
- L222 _private member_ `TArray< TSharedPtr<FCompElementViewModel> > SelectedElements;` — Currently selected elements.
- L225 _private member_ `FOnElementsChanged ElementsChanged;` — Broadcasts whenever one or more elements change.
- L227 _private member_ `FOnSelectionChanged SelectionChanged;` — Broadcasts whenever the currently selected elements change.
- L229 _private member_ `FOnRenameRequested RenameRequested;` — Broadcasts whenever a rename is requested on the selected elements.

#### Free symbols / members of external scopes

- L14 _typedef_ `template<typename TItemType> class IFilter;`
- L17 _typedef_ `template<typename ItemType> class TFilterCollection;`
- L94 _delegate_ `DECLARE_DERIVED_EVENT(FCompElementCollectionViewModel, ICompElementManager::FOnElementsChanged, FOnElementsChanged);` — Broadcasts whenever one or more elements change.
- L98 _delegate_ `DECLARE_EVENT(FCompElementCollectionViewModel, FOnSelectionChanged);` — Broadcasts whenever the currently selected elements change.
- L102 _delegate_ `DECLARE_EVENT(FCompElementCollectionViewModel, FOnRenameRequested);` — Broadcasts whenever a rename is requested on the selected elements.

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/CompElementDragDropOp.h` (Private)


#### class `FCompElementDragDropOp`  
`class FCompElementDragDropOp : public FActorDragDropGraphEdOp`  
_L9-18_
- inherits: `FActorDragDropGraphEdOp`
- desc: Drag/drop operation for dragging layers in the editor
- L12 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FCompElementDragDropOp, FActorDragDropGraphEdOp) virtual void Construct() override;`
- L17 _public member_ `TArray<FName> Elements;` — The names of the layers being dragged

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/CompElementEditorCommands.h` (Private)


#### class `FCompElementEditorCommands`  
`class FCompElementEditorCommands : public TCommands<FCompElementEditorCommands>`  
_L13-75_
- inherits: `TCommands<FCompElementEditorCommands>`
- desc: The set of commands supported by the compositing panel and associated windows.
- L17 _public function_ `FCompElementEditorCommands() : TCommands<FCompElementEditorCommands>("CompElementEditor", LOCTEXT("CompositingCmdsDesc", "Composure Compositing"), "GenericCommands", FAppStyle::GetAppStyleSetName())`
- L23 _public function_ `virtual void RegisterCommands() override`
- L55 _public member_ `TSharedPtr<FUICommandInfo> CreateEmptyComp;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> CreateNewElement;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> RefreshCompList;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> OpenElementPreview;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> RemoveMediaOutput;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> ResetMediaOutput;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> ResetColorPicker;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> FreezeFrame;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> ToggleRedChannel;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> ToggleGreenChannel;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> ToggleBlueChannel;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> ToggleAlphaChannel;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> CycleChannelPresets;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> SetChannelRed;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> SetChannelGreen;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> SetChannelBlue;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> SetChannelAlpha;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "CompElementEditorCommands"`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/CompElementManager.h` (Private)


#### class `FCompElementManager`  
`class FCompElementManager : public ICompElementManager, public FGCObject`  
_L17-115_
- inherits: `ICompElementManager,FGCObject`
- desc: Management class for interfacing with editor compositing element objects.
- L25 _public function_ `static TSharedRef<FCompElementManager> Create(const TWeakObjectPtr<UEditorEngine>& InEditor)` — Factory method which creates a new FCompElementManager object. @param  InEditor	The UEditorEngine to register delegates with, etc.
- L32 _public prototype_ `virtual ~FCompElementManager();`
- L36 _public prototype_ `virtual TWeakObjectPtr<ACompositingElement> CreateElement(const FName& ElementName, TSubclassOf<ACompositingElement> ClassType, AActor* LevelContext = nullptr, EObjectFlags ObjectFlags = EObjectFlags::RF_NoFlags) override;`
- L37 _public prototype_ `virtual TWeakObjectPtr<ACompositingElement> GetElement(const FName& ElementName) const override;`
- L38 _public prototype_ `virtual bool TryGetElement(const FName& ElementName, TWeakObjectPtr<ACompositingElement>& OutElement) override;`
- L39 _public prototype_ `virtual void AddAllCompElementsTo(TArray< TWeakObjectPtr<ACompositingElement> >& OutElements) const override;`
- L40 _public prototype_ `virtual void DeleteElementAndChildren(const FName& ElementToDelete, bool isCalledFromEditor = true) override;`
- L41 _public prototype_ `virtual void DeleteElements(const TArray<FName>& ElementsToDelete, bool isCalledFromEditor = true) override;`
- L42 _public prototype_ `virtual bool RenameElement(const FName OriginalElementName, const FName& NewElementName) override;`
- L43 _public prototype_ `virtual bool AttachCompElement(const FName ParentName, const FName ElementName) override;`
- L44 _public prototype_ `virtual bool SelectElementActors(const TArray<FName>& ElementNames, bool bSelect, bool bNotify, bool bSelectEvenIfHidden = false, const TSharedPtr<FActorFilter>& Filter = TSharedPtr<FActorFilter>(nullptr)) override;`
- L45 _public prototype_ `virtual void ToggleElementRendering(const FName& ElementName) override;`
- L46 _public prototype_ `virtual void ToggleElementFreezeFrame(const FName& ElementName) override;`
- L47 _public prototype_ `virtual void ToggleMediaCapture(const FName& ElementName) override;`
- L48 _public prototype_ `virtual UCompositingMediaCaptureOutput* ResetMediaCapture(const FName& ElementName) override;`
- L49 _public prototype_ `virtual void RemoveMediaCapture(const FName& ElementName) override;`
- L50 _public prototype_ `virtual void RefreshElementsList() override;`
- L51 _public prototype_ `void RequestRedraw() override;`
- L52 _public prototype_ `virtual bool IsDrawing(ACompositingElement* CompElement) const override;`
- L53 _public prototype_ `virtual void OnCreateNewElement(AActor* NewElement) override;`
- L54 _public prototype_ `virtual void OnDeleteElement(AActor* ElementToDelete) override;`
- L56 _public prototype_ `DECLARE_DERIVED_EVENT(FCompElementManager, ICompElementManager::FOnElementsChanged, FOnElementsChanged);`
- L57 _public function_ `virtual FOnElementsChanged& OnElementsChanged() override`
- L61 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L62 _public function_ `virtual FString GetReferencerName() const override`
- L70 _private prototype_ `FCompElementManager(const TWeakObjectPtr<UEditorEngine>& InEditor);` — Private constructor to force users to go through Create(), which properly initializes the manager.
- L73 _private prototype_ `void Initialize();` — Prepares for use.
- L75 _private prototype_ `UWorld* GetWorld() const;`
- L78 _private prototype_ `TWeakObjectPtr<ACompositingElement> EnsureElementExists(const FName& ElementName);` — Utility function for looking up and creating a element if it doesn't already exist.
- L86 _private prototype_ `TArray<FName> FindNamesOfAllChildElements(FName ElementName) const;` — Find all the child elements' FName given a parent element. @param  ElementName	        The name of the parent element. @return TArray<FName>        Array containing all the child elements' FName.
- L88 _private prototype_ `void OnLevelActorAdded(AActor* InActor);`
- L89 _private prototype_ `void OnLevelActorRemoved(AActor* InActor);`
- L90 _private prototype_ `void OnBlueprintCompiled();`
- L91 _private prototype_ `void OnCompElementConstructed(ACompositingElement* ConstructedElement);`
- L92 _private prototype_ `void OnEditorMapChange(uint32 MapChangeFlags);`
- L93 _private prototype_ `void OnWorldAdded(UWorld* NewWorld);`
- L94 _private prototype_ `void OnWorldRemoved(UWorld* NewWorld);`
- L95 _private prototype_ `void OnWorldLevelsChange(ULevel* InLevel, UWorld* InWorld);`
- L96 _private prototype_ `void OnLevelActorsListChange();`
- L100 _private member_ `TWeakObjectPtr<UEditorEngine> Editor;` — The associated UEditorEngine to bind/un-bind with.
- L103 _private member_ `TObjectPtr<UEditorCompElementContainer> ElementsContainer;` — UObject in charge of tracking all editor element actors. Separated as a UObject to more easily facilitate undo/redo actions.
- L105 _private member_ `TSharedPtr<FCompositingViewport> EditorCompositingViewport;` — Hidden editor viewport, in charge on enqueuing compositing render commands.
- L111 _private member_ `TArray< TWeakObjectPtr<ACompositingElement> > PendingDeletion;` — List which tracks elements queued for delete - used to circumvent broken child/parent link warnings. Tracked in case the user cancels the delete op and we need to restore the links.
- L114 _private member_ `FOnElementsChanged CompsChanged;` — Event broadcasted whenever one or more elements are modified.

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_DERIVED_EVENT(FCompElementManager, ICompElementManager::FOnElementsChanged, FOnElementsChanged);`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/CompElementViewModel.h` (Private)


#### class `FCompElementViewModel`  
`class FCompElementViewModel : public TSharedFromThis<FCompElementViewModel>`  
_L14-129_
- inherits: `TSharedFromThis<FCompElementViewModel>`
- desc: The non-UI solution specific presentation logic for a single comp element.
- L23 _public function_ `static TSharedRef<FCompElementViewModel> Create(const TWeakObjectPtr<ACompositingElement>& InElement, const TSharedRef<ICompElementManager>& InElementsManager)` — Factory method which creates a new FCompElementViewModel object. @param	InElement			The element to wrap @param	InElementsManager	The element management logic object
- L33 _public prototype_ `FName GetFName() const;` — Retrieve the element's display name as a FName.
- L35 _public prototype_ `FString GetName() const;` — Retrieve the element's display name as a FString.
- L37 _public prototype_ `FText GetNameAsText() const;` — Retrieve the element's display name as a FText.
- L40 _public prototype_ `const TSharedRef<FUICommandList> GetCommandList() const;` — Returns the bound UICommandList for this element row.
- L43 _public prototype_ `bool IsSetToRender() const;` — Determines if the element is enabled and rendering.
- L44 _public prototype_ `void ToggleRendering();`
- L45 _public prototype_ `bool IsRenderingExternallyDisabled() const;`
- L47 _public prototype_ `bool IsEditable() const;` — Returns whether this element is editable (certain elements, like child actors, are not editable).
- L50 _public prototype_ `bool IsFrameFrozen() const;` — Determines if the element's rendering is paused.
- L51 _public prototype_ `void ToggleFreezeFrame();`
- L52 _public prototype_ `bool IsFreezeFramingPermitted() const;`
- L55 _public prototype_ `bool HasMediaCaptureSetup(bool& bIsActive) const;` — Determines if the element has a media-capture output pass (and if it's enabled/active).
- L56 _public prototype_ `void ToggleMediaCapture();`
- L57 _public prototype_ `void RemoveMediaCapture();`
- L58 _public prototype_ `void ResetMediaCapture();`
- L61 _public prototype_ `float GetElementOpacity() const;` — Provides a way for users to easily adjust a element's final opacity.
- L62 _public prototype_ `void SetElementOpacity(const float NewOpacity, const bool bInteractive = false);`
- L63 _public prototype_ `bool IsOpacitySettingEnabled() const;`
- L72 _public prototype_ `bool CanRenameTo(const FName& NewElementName, FString& OutMessage) const;` — Returns whether the element can be assigned the specified name. @param	NewElementName		The desired new name @param	OutMessage [OUT]	A returned description explaining the boolean result @return						True when the name can be assigned.
- L74 _public prototype_ `void RenameTo(const FName& NewElementName);` — Renames the element to the specified name.
- L77 _public member_ `TArray< TSharedPtr<FCompElementViewModel> > Children;` — Child elements, parented to this one.
- L79 _public prototype_ `void AttachCompElements(const TArray<FName> ElementNames);` — Reparents the specified elements to be children nested under this element.
- L82 _public prototype_ `const TWeakObjectPtr<ACompositingElement> GetDataSource();` — Returns The actor this view-model represents.
- L89 _public function_ `DECLARE_EVENT( FCompElementViewModel, FRenamedRequestEvent ) FRenamedRequestEvent& OnRenamedRequest()` — Broadcasts whenever renaming a element is requested.
- L91 _public function_ `void BroadcastRenameRequest()`
- L94 _public function_ `DECLARE_EVENT(FCompElementViewModel, FPreviewRequestEvent) FPreviewRequestEvent& OnPreviewRequest()` — Broadcasts whenever a element preview is requested.
- L96 _public function_ `void BroadcastPreviewRequest()`
- L105 _private prototype_ `FCompElementViewModel(const TWeakObjectPtr<ACompositingElement>& InElement, const TSharedRef<ICompElementManager>& InElementsManager);` — Private constructor to force users to go through Create(), which properly initializes the model. @param	InElement			The element to wrap @param	InElementsManager	The element management logic object
- L108 _private prototype_ `void Initialize();` — Initializes the FCompElementViewModel for use
- L110 _private prototype_ `void BindCommands();` — Binds individual element row commands to delegates.
- L113 _private prototype_ `bool RemoveMediaCapture_CanExecute() const;` — Removes any media-capture output pass currently applied to this element.
- L114 _private prototype_ `bool ResetMediaCapture_CanExecute() const;`
- L118 _private member_ `const TSharedRef<ICompElementManager> CompElementManager;` — The element management logic object.
- L120 _private member_ `const TSharedRef<FUICommandList> CommandList;` — The list of commands with bound delegates for this specific element.
- L123 _private member_ `TWeakObjectPtr<ACompositingElement> ElementObj;` — The element actor this object represents.
- L126 _private member_ `FRenamedRequestEvent RenamedRequestEvent;` — Broadcasts whenever a rename is requested.
- L128 _private member_ `FPreviewRequestEvent PreviewRequestEvent;` — Broadcasts whenever a element preview is requested.

#### Free symbols / members of external scopes

- L89 _delegate_ `DECLARE_EVENT( FCompElementViewModel, FRenamedRequestEvent ) FRenamedRequestEvent& OnRenamedRequest() { return RenamedRequestEvent; } void BroadcastRenameRequest() { RenamedRequestEvent.Broadcast(); } DECLARE_EVENT(FCompElementViewModel, FPreviewRequestEvent) FPreviewRequestEvent& OnPreviewRequest() { return PreviewRequestEvent; } void BroadcastPreviewRequest() { PreviewRequestEvent.Broadcast(); } private: FCompElementViewModel(const TWeakObjectPtr<ACompositingElement>& InElement, const TSharedRef<ICompElementManager>& InElementsManager);` — Broadcasts whenever renaming a element is requested.
- L94 _delegate_ `DECLARE_EVENT(FCompElementViewModel, FPreviewRequestEvent) FPreviewRequestEvent& OnPreviewRequest() { return PreviewRequestEvent; } void BroadcastPreviewRequest() { PreviewRequestEvent.Broadcast(); } private: FCompElementViewModel(const TWeakObjectPtr<ACompositingElement>& InElement, const TSharedRef<ICompElementManager>& InElementsManager);` — Broadcasts whenever a element preview is requested.

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/CompositingViewportClient.h` (Private)


#### class `FCompositingViewportClient`  
`class FCompositingViewportClient final : public FEditorViewportClient, public FTickableEditorObject`  
_L12-42_
- inherits: `FEditorViewportClient,FTickableEditorObject`
- L15 _public prototype_ `FCompositingViewportClient(TWeakObjectPtr<UEditorCompElementContainer>&& CompElements);`
- L16 _public prototype_ `virtual ~FCompositingViewportClient();`
- L18 _public prototype_ `bool IsDrawing() const;`
- L21 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L22 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;`
- L23 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L24 _public prototype_ `virtual bool ProcessScreenShots(FViewport* Viewport) override;`
- L28 _public prototype_ `virtual bool WantsDrawWhenAppIsHidden() const override;`
- L32 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L33 _public prototype_ `virtual bool IsTickable() const override;`
- L34 _public prototype_ `virtual TStatId GetStatId() const override;`
- L38 _private prototype_ `bool InternalIsVisible() const;`
- L40 _private member_ `TWeakObjectPtr<UEditorCompElementContainer> ElementsContainerPtr;`
- L41 _private member_ `bool bIsDrawing = false;`

#### class `FCompositingViewport`  
`class FCompositingViewport final : public FDummyViewport`  
_L44-53_
- inherits: `FDummyViewport`
- L46 _private prototype_ `FCompositingViewport();`
- L48 _public prototype_ `static TSharedRef<FCompositingViewport> Create(TWeakObjectPtr<UEditorCompElementContainer>&& CompElements);`
- L50 _public prototype_ `FCompositingViewportClient& GetCompositingClient() const;`
- L51 _public prototype_ `bool IsDrawing() const;`
- L52 _public prototype_ `void RequestRedraw();`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/ComposureDetailCustomizations.h` (Private)


#### class `FCompElementDetailsCustomization`  
`class FCompElementDetailsCustomization : public IDetailCustomization`  
_L28-44_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L35 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L38 _private prototype_ `void ForceRefreshLayout();`
- L39 _private prototype_ `void GetInstanceCameraSourceComboStrings(TArray<TSharedPtr<FString>>& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems);`
- L40 _private prototype_ `FString GetInstanceCameraSourceValueStr(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L41 _private prototype_ `void OnCameraSourceSelected(const FString& Selection, TSharedPtr<IPropertyHandle> PropertyHandle);`
- L43 _private member_ `IDetailLayoutBuilder* MyLayout = nullptr;`

#### class `FCompositingMaterialPassCustomization`  
`class FCompositingMaterialPassCustomization : public IPropertyTypeCustomization, public FEditorUndoClient`  
_L53-124_
- inherits: `IPropertyTypeCustomization,FEditorUndoClient`
- L56 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L58 _public prototype_ `FCompositingMaterialPassCustomization();`
- L59 _public prototype_ `~FCompositingMaterialPassCustomization();`
- L62 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Begin IPropertyTypeCustomization interface
- L63 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L67 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L68 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L72 _protected member_ `TSharedPtr<ICompElementManager> CompElementManager;`
- L73 _protected member_ `TWeakPtr<IPropertyHandle> CachedPropertyHandle;`
- L74 _protected member_ `TSharedPtr<IPropertyHandle> CachedVectorProxies;`
- L75 _protected member_ `TSharedPtr<IPropertyHandle> CachedMaterialParamMappings;`
- L76 _protected member_ `TSharedPtr<IPropertyUtilities> CachedUtils;`
- L77 _protected member_ `TSharedPtr<IPropertyHandle> MaterialHandle;`
- L78 _protected member_ `TWeakObjectPtr<UMaterialInterface> MaterialReference;`
- L79 _protected member_ `FName* MaterialPassName;`
- L83 _private prototype_ `void VectorResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);` — Overrides for vector param reset to default
- L84 _private prototype_ `bool VectorShouldShowResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L85 _private prototype_ `void OnVectorOverrideChanged(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L86 _private prototype_ `void TextureResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle, TSharedPtr<SComboButton> ComboBoxHandle);`
- L87 _private prototype_ `bool TextureShouldShowResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L89 _private prototype_ `TOptional<float> GetScalarParameterSliderMin(FMaterialParameterInfo ScalarParam) const;`
- L90 _private prototype_ `TOptional<float> GetScalarParameterSliderMax(FMaterialParameterInfo ScalarParam) const;`
- L91 _private prototype_ `void OnScalarParameterSlideBegin(FMaterialParameterInfo ScalarParam);`
- L92 _private prototype_ `void OnScalarParameterSlideEnd(const float NewValue, FMaterialParameterInfo ScalarParam);`
- L93 _private prototype_ `void OnScalarParameterCommitted(const float NewValue, ETextCommit::Type CommitType, FMaterialParameterInfo ScalarParam);`
- L94 _private prototype_ `TOptional<float> GetScalarParameterValue(FMaterialParameterInfo ScalarParam) const;`
- L95 _private prototype_ `void SetScalarParameterValue(const float NewValue, FMaterialParameterInfo ScalarParam);`
- L96 _private prototype_ `EVisibility IsResetScalarParameterVisible(FMaterialParameterInfo ScalarParam) const;`
- L97 _private prototype_ `FReply OnResetScalarParameterClicked(FMaterialParameterInfo ScalarParam);`
- L99 _private prototype_ `void HandleRequiredParamComboChanged(TSharedPtr<FName> Item, ESelectInfo::Type SelectInfo, TWeakPtr<SComboButton> ComboButtonHandle, FName ParamName);`
- L100 _private prototype_ `FText GetRequiredParamComboText(FName TexName) const;`
- L101 _private prototype_ `void OnRequiredParamComboTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName ParamName);`
- L102 _private prototype_ `TSharedRef<SWidget> GetRequiredParamComboMenu(TWeakPtr<SComboButton> ComboButtonHandle, FName ParamName, EParamType ParamType);`
- L103 _private prototype_ `void RebuildRequiredParamSources();`
- L105 _private prototype_ `TSharedRef<ITableRow> GenerateComboItem(TSharedPtr<FName> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L106 _private prototype_ `void HandleComboChanged(TSharedPtr<FName> Item, ESelectInfo::Type SelectInfo, TWeakPtr<SComboButton> ComboButtonHandle, FName TexName);`
- L107 _private prototype_ `FText GetComboText(FName TexName) const;`
- L108 _private prototype_ `void OnComboTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName TexName);`
- L109 _private prototype_ `TSharedRef<SWidget> GetPassComboMenu(TWeakPtr<SComboButton> ComboButtonHandle, FName TexName);`
- L110 _private prototype_ `void RebuildTextureSourceList();`
- L112 _private prototype_ `static TArray<TSharedPtr<FName>> GetPassNamesRecursive(ACompositingElement* Element, const FString& Prefix = FString());`
- L113 _private prototype_ `void ResetParameterOverrides();`
- L114 _private prototype_ `void OnRedrawViewports();`
- L115 _private prototype_ `FCompositingMaterialType* GetMaterialPass() const;`
- L117 _private member_ `TArray<TSharedPtr<FName>> TextureComboSource;`
- L119 _private member_ `TArray<TSharedPtr<FName>> RequiredParamComboSourceScalar;`
- L120 _private member_ `TArray<TSharedPtr<FName>> RequiredParamComboSourceVector;`
- L121 _private member_ `TArray<TSharedPtr<FName>> RequiredParamComboSourceTexture;`
- L122 _private member_ `TArray<TSharedPtr<FName>> RequiredParamComboSourceMedia;`
- L123 _private member_ `TArray<TSharedPtr<FName>> RequiredParamComboSourceUnknown;`

#### class `FCompositingPassCustomization`  
`class FCompositingPassCustomization : public IPropertyTypeCustomization`  
_L130-146_
- inherits: `IPropertyTypeCustomization`
- L133 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L137 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L138 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L142 _private prototype_ `TSharedPtr<IPropertyHandle> GetInstancedObjectHandle(TSharedRef<IPropertyHandle> PropertyHandle);`
- L143 _private prototype_ `TSharedPtr<SWidget> ConditionallyCreatePreviewButton(TSharedRef<IPropertyHandle> PropertyHandle, TSharedPtr<SWidget> ParentWidget);`
- L145 _private member_ `TWeakPtr<SWidget> HeaderValueWidget;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ESelectInfo`
- L17 _namespace_ `namespace ETextCommit`
- L51 _typedef_ `typedef FCompositingMaterial FCompositingMaterialType;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/ComposureEditorSettings.h` (Private)


#### class `UDefaultComposureEditorSettings`  
`class UDefaultComposureEditorSettings : public UObject`  
_L8-21_
- reflection: `UCLASS(config=Composure)`
- inherits: `UObject`
- L14 _public member_ `TArray<FSoftObjectPath> FeaturedCompShotClasses;` — `UPROPERTY(Config)`
- L17 _public member_ `TArray<FSoftObjectPath> FeaturedElementClasses;` — `UPROPERTY(Config)`
- L20 _public member_ `TMap<FName, FString> DefaultElementNames;` — `UPROPERTY(Config)`

#### class `UComposureEditorSettings`  
`class UComposureEditorSettings : public UObject`  
_L24-38_
- reflection: `UCLASS(config=Editor)`
- inherits: `UObject`
- L30 _public member_ `TArray<FSoftObjectPath> FeaturedCompShotClassOverrides;` — `UPROPERTY(Config)`
- L33 _public member_ `TArray<FSoftObjectPath> FeaturedElementClassOverrides;` — `UPROPERTY(Config)`
- L36 _public prototype_ `const TArray<FSoftObjectPath>& GetFeaturedCompShotClasses() const;` — falls back to the defaults, if the project didn't specify any
- L37 _public prototype_ `const TArray<FSoftObjectPath>& GetFeaturedElementClasses() const;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/ComposureEditorStyle.h` (Private)


#### class `FComposureEditorStyle`  
`class FComposureEditorStyle final : public FSlateStyleSet`  
_L19-102_
- inherits: `FSlateStyleSet`
- L23 _public function_ `FComposureEditorStyle() : FSlateStyleSet("ComposureEditorStyle")`
- L92 _public function_ `static FComposureEditorStyle& Get()`
- L98 _public function_ `~FComposureEditorStyle()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`
- L14 _macro_ `#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`
- L15 _macro_ `#define BORDER_BRUSH(RelativePath, ...) FSlateBorderBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`
- L16 _macro_ `#define TTF_FONT(RelativePath, ...) FSlateFontInfo(RootToContentDir(RelativePath, TEXT(".ttf")), __VA_ARGS__)`
- L17 _macro_ `#define OTF_FONT(RelativePath, ...) FSlateFontInfo(RootToContentDir(RelativePath, TEXT(".otf")), __VA_ARGS__)`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/EditorCompElementContainer.h` (Private)


#### class `UEditorCompElementContainer`  
`class UEditorCompElementContainer : public UObject`  
_L14-57_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: UObject for tracking our list of in-level composure actors - wrapped by a UObject to mimic the UWorld::Layers property (hooks into undo/redo easily, etc.)
- L20 _public prototype_ `UEditorCompElementContainer();`
- L22 _public prototype_ `bool Add(ACompositingElement* NewElement, bool bTransactional = true);`
- L23 _public prototype_ `bool Remove(ACompositingElement* Element, bool bTransactional = true);`
- L24 _public prototype_ `bool Contains(ACompositingElement* Element) const;`
- L26 _public function_ `FORCEINLINE int32 Num()`
- L29 _public function_ `template <class PREDICATE_CLASS> void Sort(const PREDICATE_CLASS& Predicate)`
- L34 _public typedef_ `typedef TArray< TWeakObjectPtr<ACompositingElement> > FCompElementList;`
- L35 _public function_ `operator const FCompElementList&()`
- L37 _public prototype_ `void RebuildEditorElementsList();`
- L41 _public prototype_ `UWorld* GetWorld() const override;`
- L46 _private member_ `TArray< TWeakObjectPtr<ACompositingElement> > CompElements;` — `UPROPERTY()`
- L53 _public function_ `FORCEINLINE FCompElementList::RangedForIteratorType begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L54 _public function_ `FORCEINLINE FCompElementList::RangedForConstIteratorType begin() const`
- L55 _public function_ `FORCEINLINE FCompElementList::RangedForIteratorType end ()`
- L56 _public function_ `FORCEINLINE FCompElementList::RangedForConstIteratorType end () const`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/ScopedWorldLevelContext.h` (Private)


#### struct `FScopedWorldLevelContext`  
`struct FScopedWorldLevelContext`  
_L8-45_
- L10 _public function_ `FScopedWorldLevelContext(UWorld* InWorld, AActor* LevelContext) : World(InWorld)`
- L24 _public function_ `FScopedWorldLevelContext(UWorld* InWorld, ULevel* Level) : World(InWorld)`
- L34 _public function_ `~FScopedWorldLevelContext()`
- L43 _private member_ `UWorld* World = nullptr;`
- L44 _private member_ `ULevel* LevelToRestore = nullptr;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementBrowser.h` (Private)


#### class `SCompElementBrowser`  
`class SCompElementBrowser : public SCompoundWidget`  
_L15-82_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SCompElementBrowser)`
- L21 _public function_ `~SCompElementBrowser()`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget. Called by the SNew() Slate macro. @param  InArgs	Declaration used by the SNew() macro to construct this widget
- L36 _protected function_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override`
- L47 _private function_ `void TransformElementToString(const TSharedPtr<FCompElementViewModel>& Element, OUT TArray<FString>& OutSearchStrings) const`
- L58 _private function_ `void OnRenameRequested()` — Callback when elements want to be renamed
- L63 _private function_ `TSharedPtr<SWidget> ConstructElementContextMenu()`
- L68 _private prototype_ `void OnFilterTextChanged(const FText& InNewText);`
- L72 _private member_ `TSharedPtr<SSearchBox> SearchBoxPtr;`
- L75 _private member_ `TSharedPtr<FCompElementTextFilter> SearchBoxCompElementFilter;`
- L78 _private member_ `TSharedPtr<FCompElementCollectionViewModel> ElementCollectionViewModel;`
- L81 _private member_ `TSharedPtr<SCompElementsView> ElementsView;` — The element view widget, displays all the compositing elements in the level

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef TTextFilter<const TSharedPtr<FCompElementViewModel>&> FCompElementTextFilter;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementEdCommandsMenu.h` (Private)


#### class `SCompElementEdCommandsMenu`  
`class SCompElementEdCommandsMenu : public SCompoundWidget`  
_L8-23_
- inherits: `SCompoundWidget`
- L11 _public function_ `SLATE_BEGIN_ARGS(SCompElementEdCommandsMenu) : _CloseWindowAfterMenuSelection(true)`
- L14 _public prototype_ `SLATE_ARGUMENT(bool, CloseWindowAfterMenuSelection) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FCompElementCollectionViewModel> InViewModel);`
- L22 _private member_ `TSharedPtr<FCompElementCollectionViewModel> ViewModel;` — The UI logic of the panel that is not Slate specific

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementPickerWindow.h` (Private)


#### struct `FCompElementColorPickerArgs`  
`struct FCompElementColorPickerArgs`  
_L18-29_
- L20 _public member_ `TWeakUIntrfacePtr<ICompImageColorPickerInterface> PickerTarget;`
- L21 _public member_ `FText WindowTitle;`
- L23 _public member_ `FColorPickedEventHandler OnColorPicked;`
- L24 _public member_ `FSimpleDelegate OnColorPickerCanceled;`
- L26 _public member_ `TSharedPtr<SWidget> ParentWidget;`
- L28 _public member_ `bool bAverageColorOnDrag = true;`

#### class `SCompElementPickerWindow`  
`class SCompElementPickerWindow : public SWindow`  
_L36-78_
- inherits: `SWindow`
- L39 _public prototype_ `static TSharedPtr<SWindow> Open(const FCompElementColorPickerArgs& PickerArgs);`
- L42 _public prototype_ `SCompElementPickerWindow();`
- L44 _public function_ `SLATE_BEGIN_ARGS(SCompElementPickerWindow)`
- L45 _public prototype_ `SLATE_ARGUMENT(TWeakUIntrfacePtr<ICompImageColorPickerInterface>, PickerTarget) SLATE_ARGUMENT(FFreezeFrameControlHandle, FreezeFrameControlHandle) SLATE_ARGUMENT(bool, AverageColorOnDrag) SLATE_EVENT(FColorPickedEventHandler, OnColorPicked) SLATE_EVENT(FSimpleDelegate, OnPickerCanceled) SLATE_ARGUMENT(FText, WindowTitle) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L57 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L58 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L59 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L63 _private prototype_ `void BindCommands();`
- L65 _private prototype_ `void OnPreviewPressed();`
- L66 _private prototype_ `void OnPreviewReleased();`
- L68 _private prototype_ `void OnResetPicking();`
- L69 _private prototype_ `void OnToggleFreezeFrame();`
- L72 _private member_ `TSharedRef<FUICommandList> CommandList;`
- L73 _private member_ `bool bProcessingKeyDown = false;`
- L74 _private member_ `TSet< TSharedPtr<const FUICommandInfo> > PressedCmds;`
- L76 _private member_ `TSharedPtr<SCompElementColorPickerDialog> PickerContents;`
- L77 _private member_ `FSimpleDelegate OnPickerCanceled;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_ThreeParams(FColorPickedEventHandler, const FVector2D& , const FLinearColor& , bool );`
- L16 _prototype_ `DECLARE_DELEGATE_ThreeParams(FColorPickedEventHandler, const FVector2D& , const FLinearColor& , bool );`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementPreviewDialog.h` (Private)


#### class `SCompElementPreviewDialog`  
`class SCompElementPreviewDialog : public SCompoundWidget`  
_L23-75_
- inherits: `SCompoundWidget`
- L26 _public prototype_ `static TSharedRef<SWindow> OpenPreviewWindow(TWeakUIntrfacePtr<ICompEditorImagePreviewInterface> PreviewTarget, TSharedPtr<SWidget> ParentWidget = nullptr, const FText& WindowTitle = FText());`
- L29 _public prototype_ `SCompElementPreviewDialog();`
- L30 _public prototype_ `~SCompElementPreviewDialog();`
- L32 _public function_ `SLATE_BEGIN_ARGS(SCompElementPreviewDialog)`
- L33 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TWeakUIntrfacePtr<ICompEditorImagePreviewInterface>, PreviewTarget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L42 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L47 _protected prototype_ `virtual TSharedRef<SWidget> GeneratePreviewContent();`
- L48 _protected function_ `virtual void ExtendMenuOverlay(TSharedRef<SHorizontalBox> MenuBar)`
- L49 _protected prototype_ `virtual TSharedRef<SHorizontalBox> GenerateHoveredColorOverlay();`
- L50 _protected prototype_ `void BindCommands();`
- L53 _protected member_ `TWeakUIntrfacePtr<ICompEditorImagePreviewInterface> PreviewTarget;`
- L55 _protected member_ `TWeakPtr<SWindow> WeakParentWindow;` — A pointer to the window that is asking the user to select a parent class
- L57 _protected function_ `static bool CanAlwaysExecute()`
- L62 _protected member_ `TSharedPtr<SCompElementPreviewPane> ImagePane;`
- L65 _private prototype_ `void OnCycleChannelPresets();`
- L66 _private prototype_ `void SetChannelRed();`
- L67 _private prototype_ `void SetChannelGreen();`
- L68 _private prototype_ `void SetChannelBlue();`
- L69 _private prototype_ `void SetChannelAlpha();`
- L70 _private prototype_ `void SyncColorMaskPreset(const FLinearColor& ColorMask);`
- L72 _private member_ `FLinearColor ColorUnderMouse;`
- L73 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L74 _private member_ `EChannelPresets ChannelPreset;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementPreviewPane.h` (Private)


#### class `SCompElementPreviewPane`  
`class SCompElementPreviewPane : public SCompoundWidget, public FGCObject`  
_L23-92_
- inherits: `SCompoundWidget,FGCObject`
- L26 _public prototype_ `SCompElementPreviewPane();`
- L27 _public prototype_ `~SCompElementPreviewPane();`
- L29 _public prototype_ `DECLARE_DELEGATE_OneParam(FOverlayExtender, TSharedRef<SOverlay> );`
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam(FMenuBarOverlayExtender, TSharedRef<SHorizontalBox> );`
- L31 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnColorMaskChange, const FLinearColor& );`
- L33 _public function_ `SLATE_BEGIN_ARGS(SCompElementPreviewPane)`
- L34 _public prototype_ `SLATE_ARGUMENT(TWeakUIntrfacePtr<ICompEditorImagePreviewInterface>, PreviewTarget) SLATE_EVENT(FOverlayExtender, OverlayExtender) SLATE_EVENT(FMenuBarOverlayExtender, MenuOverlayExtender) SLATE_EVENT(FOnColorMaskChange, OnColorMaskChanged) SLATE_EVENT(FSimpleDelegate, OnRedraw) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `void SetDisplayImage(UTexture* NewDisplayImage);`
- L44 _public prototype_ `void SetPreviewColorMask(const FLinearColor& NewColorMask);`
- L45 _public function_ `const FLinearColor& GetPreviewColorMask() const`
- L47 _public prototype_ `void SetOnRedraw(FSimpleDelegate OnRedraw);`
- L51 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L52 _public function_ `virtual FString GetReferencerName() const override`
- L58 _private prototype_ `virtual const FSlateBrush* GetDisplayImage() const;`
- L59 _private prototype_ `ESlateDrawEffect GetDrawEffects() const;`
- L61 _private prototype_ `FReply OnMenuClicked();`
- L62 _private prototype_ `TSharedRef<SWidget> GenerateMenu() const;`
- L64 _private prototype_ `void RedChannelToggled();`
- L65 _private prototype_ `ECheckBoxState GetRedChannel();`
- L66 _private prototype_ `void GreenChannelToggled();`
- L67 _private prototype_ `ECheckBoxState GetGreenChannel();`
- L68 _private prototype_ `void BlueChannelToggled();`
- L69 _private prototype_ `ECheckBoxState GetBlueChannel();`
- L70 _private prototype_ `void AlphaChannelToggled();`
- L71 _private prototype_ `ECheckBoxState GetAlphaChannel();`
- L73 _private prototype_ `void ApplyColorMaskChange();`
- L75 _private prototype_ `EActiveTimerReturnType RefreshRenderWindow(double InCurrentTime, float InDeltaTime);`
- L78 _private member_ `TSharedPtr<FSlateBrush> PreviewBrush;`
- L79 _private member_ `FSoftObjectPath PreviewMaterialPath;`
- L80 _private member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMID;`
- L81 _private member_ `TSharedPtr<SImage> ImageWidget;`
- L83 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L84 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L85 _private member_ `FLinearColor ColorMask;`
- L87 _private member_ `TSharedPtr<ICompElementManager> CompElementManager;`
- L89 _private member_ `TWeakUIntrfacePtr<ICompEditorImagePreviewInterface> PreviewTarget;`
- L90 _private member_ `FOnColorMaskChange OnColorMaskChanged;`
- L91 _private member_ `FSimpleDelegate OnRedraw;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOverlayExtender, TSharedRef<SOverlay> );`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FMenuBarOverlayExtender, TSharedRef<SHorizontalBox> );`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColorMaskChange, const FLinearColor& );`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementViewRow.h` (Private)


#### class `SCompElementViewRow`  
`class SCompElementViewRow : public SMultiColumnTableRow< TSharedPtr<FCompElementViewModel> >`  
_L27-150_
- inherits: `SMultiColumnTableRow<TSharedPtr<FCompElementViewModel>>`
- desc: The widget that represents a row in the element view's list-view control. Generates widgets for each column on demand.
- L30 _public function_ `SLATE_BEGIN_ARGS(SCompElementViewRow)`
- L31 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCompElementViewModel> InViewModel, TSharedRef<STableViewBase> InOwnerTableView);`
- L44 _public prototype_ `~SCompElementViewRow();`
- L48 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnID) override;`
- L52 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L53 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L54 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L58 _protected prototype_ `void OnRenameElementTextCommitted(const FText& InText, ETextCommit::Type eInCommitType);` — Callback when the SInlineEditableTextBlock is committed, to update the name of the element this row represents.
- L60 _protected prototype_ `bool OnRenameElementTextChanged(const FText& NewText, FText& OutErrorMessage);` — Callback when the SInlineEditableTextBlock is changed, to check for error conditions.
- L69 _private prototype_ `FSlateColor GetColorAndOpacity() const;` — Returns the color and opacity for displaying the bound element's name. The color and opacity changes depending on whether a drag/drop operation is occurring. @return	The SlateColor to render the element's name in
- L74 _private prototype_ `TSharedRef<SWidget> GetIcon();` — Returns the row's leading icon (associated with the wrapped element type).
- L79 _private prototype_ `void OnPreviewRequested();` — Opens a standalone preview window displaying the associated element.
- L86 _private prototype_ `FReply OnToggleVisibility();` — Called when the user clicks on the visibility icon for a element's row widget. @return	A reply that indicated whether this event was handled
- L94 _private prototype_ `const FSlateBrush* GetVisibilityBrushForElement() const;` — Called to get the SlateImageBrush representing the visibility state of the element this row widget represents @return	The SlateBrush representing the element's visibility state
- L99 _private prototype_ `bool VisibilityToggleEnabled() const;` — Reports if the visibility button should be enabled or not (i.e. if toggling it would have an effect).
- L101 _private prototype_ `const FSlateBrush* GetFreezeFrameBrushForElement() const;`
- L102 _private prototype_ `FReply OnToggleFreezeFrame();`
- L103 _private prototype_ `bool IsFreezeFrameToggleEnabled() const;`
- L105 _private prototype_ `const FSlateBrush* GetMediaCaptureStatusBrush() const;`
- L106 _private prototype_ `FReply OnToggleMediaCapture();`
- L107 _private prototype_ `bool IsMediaCaptureToggleEnabled() const;`
- L108 _private prototype_ `TSharedPtr<SWidget> CreateMediaCaptureToggleContextMenu();`
- L110 _private prototype_ `TOptional<float> GetAlphaValueOptional() const;`
- L111 _private prototype_ `float GetAlphaValue() const;`
- L112 _private prototype_ `void OnSetAlphaValue(float NewValue, bool bFromSlider);`
- L113 _private prototype_ `void OnCommitAlphaValue(float NewValue, ETextCommit::Type CommitType);`
- L114 _private prototype_ `void OnAlphaSliderMouseEnd();`
- L115 _private prototype_ `bool IsAlphaWidgetEnabled() const;`
- L126 _private member_ `TSharedPtr<FCompElementViewModel> ViewModel;` — The element associated with this row of data
- L129 _private member_ `TSharedPtr<SButton> VisibilityButton;` — The visibility button for the element
- L132 _private member_ `TSharedPtr<SButton> FreezeFrameButton;` — The button widget for toggling the element's paused state
- L135 _private member_ `TAttribute<FText> HighlightText;` — The string to highlight on any text contained in the row widget
- L138 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;` — Widget for displaying and editing the element name
- L141 _private member_ `bool bSettingAlphaInteractively = false;` — Tracks whether the alpha slider is currently being dragged or not.
- L144 _private member_ `FDelegateHandle EnterEditingModeDelegateHandle;` — Handle to the registered EnterEditingMode delegate
- L146 _private member_ `FDelegateHandle PreviewRequestDelegateHandle;` — Handle ti the registered OnPreviewRequest delegate
- L149 _private member_ `TWeakPtr<SWindow> PreviewWindow;` — Weak pointer to the active preview window - spawned from OnPreviewRequested()

#### struct `SCompElementViewRow::FDefaultTreeItemMetrics`  
`struct FDefaultTreeItemMetrics`  
_L119-123_
- desc: Default metrics for outliner tree items
- L121 _public function_ `static int32 IconSize()`
- L122 _public function_ `static FMargin IconPadding()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace CompElementsView`
- L17 _variable_ `static const FName ColumnID_ElementLabel("Ele` (scope `CompElementsView`) — IDs for list columns
- L18 _variable_ `static const FName ColumnID_Visibility("Vis` (scope `CompElementsView`)
- L19 _variable_ `static const FName ColumnID_Alpha("Alp` (scope `CompElementsView`)
- L20 _variable_ `static const FName ColumnID_FreezeFrame("Fre` (scope `CompElementsView`)
- L21 _variable_ `static const FName ColumnID_MediaCapture("Med` (scope `CompElementsView`)

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompElementsView.h` (Private)


#### class `SCompElementsView`  
`class SCompElementsView : public SCompoundWidget`  
_L22-292_
- inherits: `SCompoundWidget`
- desc: A slate widget that can be used to display a list of compositing elements and perform various element related actions.
- L25 _public typedef_ `typedef SListView< TSharedPtr<FCompElementViewModel> >::FOnGenerateRow FOnGenerateRow;`
- L27 _public function_ `SLATE_BEGIN_ARGS(SCompElementsView)`
- L28 _public function_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FOnContextMenuOpening, ConstructContextMenu) SLATE_EVENT(FOnGenerateRow, OnGenerateRow) SLATE_END_ARGS() SCompElementsView() : bUpdatingSelection(false)`
- L37 _public function_ `~SCompElementsView()`
- L49 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<FCompElementCollectionViewModel>& InViewModel)` — Construct this widget. Called by the SNew() Slate macro. @param	InArgs		Declaration used by the SNew() macro to construct this widget @param	InViewModel The UI logic not specific to slate
- L119 _public function_ `void RequestRenameOnSelectedElement()` — Requests a rename on the selected element, first forcing the item to scroll into view
- L130 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L135 _protected function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L150 _private function_ `TSharedRef<ITableRow> OnGenerateRowDefault(const TSharedPtr<FCompElementViewModel> Item, const TSharedRef<STableViewBase>& OwnerTable)` — Called by the STreeView to generate a table row for the specified item. @param  Item			The FCompElementViewModel to generate a TableRow widget for @param  OwnerTable	The TableViewBase which will own the generated TableRow widget @return The generated TableRow widget
- L164 _private function_ `void RequestRefresh(const ECompElementEdActions , const TWeakObjectPtr<ACompositingElement>& , const FName& )` — Kicks off a Refresh of the elements view. @param  Action				The action taken on one or more elements @param  ChangedElement		The element that changed @param  ChangedProperty		The property that changed
- L172 _private function_ `void UpdateSelection()` — Called whenever the view model's selection changes.
- L201 _private function_ `void OnSelectionChanged(const TSharedPtr< FCompElementViewModel > Item, ESelectInfo::Type SelectInfo)` — Called by the STreeView when the selection has changed. @param  Item			The element affected by the selection change @param  SelectInfo	Provides context on how the selection changed
- L237 _private function_ `void OnListViewMouseButtonDoubleClick(const TSharedPtr<FCompElementViewModel> Item)` — Called by the STreeView when the user double-clicks on an item. @param Item	The element that was double clicked
- L242 _private function_ `void OnItemScrolledIntoView(TSharedPtr<FCompElementViewModel> ElementItem, const TSharedPtr<ITableRow>& Widget)` — Handler for when an item has scrolled into view after having been requested to do so.
- L253 _private function_ `FReply OnDragRow(const FGeometry& , const FPointerEvent& MouseEvent)` — Called when a specific row is dragged - creates a special drag/drop op.
- L279 _private member_ `bool bUpdatingSelection;` — Whether the view is currently updating the view model's selection
- L282 _private member_ `TSharedPtr<FCompElementCollectionViewModel> ViewModel;` — The UI logic of the elements view that is not slate specific
- L285 _private member_ `TSharedPtr<SCompElementTreeView> TreeView;` — Our tree view widget, used to list the comp elements
- L288 _private member_ `TAttribute<FText> HighlightText;` — The string to highlight on any text contained in the view widget
- L291 _private member_ `TWeakPtr<FCompElementViewModel> RequestedRenameElement;` — Used to defer a rename on a element until after it has been scrolled into view

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "CompElementsView"`
- L17 _typedef_ `typedef STreeView< TSharedPtr<FCompElementViewModel> > SCompElementTreeView;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/Widgets/SCompPreviewImage.h` (Private)


#### class `SCompPreviewImage`  
`class SCompPreviewImage : public SImage`  
_L7-59_
- inherits: `SImage`
- L10 _public function_ `SLATE_BEGIN_ARGS(SCompPreviewImage) : _Image(FCoreStyle::Get().GetDefaultBrush()) , _ColorAndOpacity(FLinearColor::White) , _DrawEffects(ESlateDrawEffect::None)`
- L16 _public function_ `SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity) SLATE_ATTRIBUTE(ESlateDrawEffect, DrawEffects) SLATE_END_ARGS() SCompPreviewImage() : DrawEffects(ESlateDrawEffect::None)`
- L25 _public function_ `void Construct(const FArguments& InArgs)`
- L37 _public function_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override`
- L58 _private member_ `TAttribute<ESlateDrawEffect> DrawEffects;`

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Public/CompElementEditorModule.h` (Public)


#### class `ICompElementEditorModule`  
`class ICompElementEditorModule : public IModuleInterface`  
_L13-27_
- inherits: `IModuleInterface`
- L16 _public prototype_ `static ICompElementEditorModule& Get();`
- L22 _public prototype_ `virtual TSharedPtr<ICompElementManager> GetCompElementManager() = 0;` — Returns a manager object for compositing elements, which can be used to perform various operations on the element objects in the editor.
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FCompEditorMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the comp-element editor menus
- L26 _public prototype_ `virtual TArray<FCompEditorMenuExtender>& GetEditorMenuExtendersList() = 0;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FCompEditorMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the comp-element editor menus

### `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Public/ICompElementManager.h` (Public)


#### enum `ECompElementEdActions`  
`enum class ECompElementEdActions`  
_L15-22_
- L17 _public enumerator_ `Add`
- L18 _public enumerator_ `Modify`
- L19 _public enumerator_ `Delete`
- L20 _public enumerator_ `Rename`
- L21 _public enumerator_ `Reset`

#### class `ICompElementManager`  
`class ICompElementManager`  
_L27-186_
- desc: Interface for running editor operations/logic on compositing element actors.
- L30 _public typedef_ `typedef IFilter<const TWeakObjectPtr<AActor>&> FActorFilter;`
- L40 _public prototype_ `virtual TWeakObjectPtr<ACompositingElement> CreateElement(const FName& ElementName, TSubclassOf<ACompositingElement> ClassType, AActor* LevelContext = nullptr, EObjectFlags ObjectFlags = EObjectFlags::RF_NoFlags) = 0;` — Creates a actor object for the named element. @param  ElementName	The name of the element to create. @param  ClassType	The element type to spawn. @param  LevelContext Optional actor whose world level you want to spawn into. @return The newly created actor object for the named element.
- L48 _public prototype_ `virtual TWeakObjectPtr<ACompositingElement> GetElement(const FName& ElementName) const = 0;` — Gets the actor object of the named element. @param  ElementName	The name of the element you want to lookup @return The object Object of the provided element name
- L57 _public prototype_ `virtual bool TryGetElement(const FName& ElementName, TWeakObjectPtr<ACompositingElement>& OutElement) = 0;` — Attempts to get the actor object of the provided element name. @param  ElementName		The name of the element you want to lookup @param  OutElement[OUT]	Set to the actor object of the named element. Set to Invalid if no actor object exists. @return True if a valid actor object was found and set to OutElement; otherwise false, a valid actor object was not found.
- L64 _public prototype_ `virtual void AddAllCompElementsTo(TArray< TWeakObjectPtr<ACompositingElement> >& OutElements) const = 0;` — Gets all known elements and appends them to the provided array. @param OutElements[OUT] Output array to store all known elements in
- L72 _public prototype_ `virtual void DeleteElementAndChildren(const FName& ElementToDelete, bool bIsCalledFromEditor = true) = 0;` — Deletes the specified element and all of its children. @param ElementToDelete	    A valid element name @param bIsCalledFromEditor   True if this function is called from editor. False if it is called from BP/C++. Its default value is true.
- L80 _public prototype_ `virtual void DeleteElements(const TArray<FName>& ElementsToDelete, bool bIsCalledFromEditor = true) = 0;` — Deletes all of the provided elements and all of their children if the function is called from editor. Use DeleteElementAndChildren instead. @param ElementsToDelete	   A list of valid element names @param bIsCalledFromEditor  True if this function is called from editor. False if it is called from BP/C++. Its default value is true.
- L88 _public prototype_ `virtual bool RenameElement(const FName OriginalElementName, const FName& NewElementName) = 0;` — Renames the element with the specified original named to the provided new name. @param	OriginalElementName The name of the element to be renamed @param	NewElementName		The new name for the element to be renamed
- L97 _public prototype_ `virtual bool AttachCompElement(const FName ParentName, const FName ElementName) = 0;` — Attaches the specified element as a child to the named parent. @param  ParentName	The element you want to nest the child under. @param  ElementName	A valid element name for the child you want to add. @return True if the element was successfully added as a child to the specified parent.
- L109 _public prototype_ `virtual bool SelectElementActors(const TArray<FName>& ElementNames, bool bSelect, bool bNotify, bool bSelectEvenIfHidden = false, const TSharedPtr<FActorFilter>& Filter = TSharedPtr<FActorFilter>(nullptr)) = 0;` — Selects/de-selects specified element actors. @param  ElementNames						A valid list of element names. @param  bSelect							If true, actors are selected; if false, actors are deselected @param  bNotify							If true, the Editor is notified of the selection change; if false, the Editor will not be notified @param  bSelectEvenIfHidden [optional]	If true, even hidden actors will be selected; if false, hidden actors won't be selected @param  Filter [optional]				Elements that don't pass the specified filter restrictions won't be selected @return 									true if at least one actor was selected/deselected.
- L116 _public prototype_ `virtual void ToggleElementRendering(const FName& ElementName) = 0;` — Toggles the named element's enabled state. @param ElementName	The name of the element to affect
- L123 _public prototype_ `virtual void ToggleElementFreezeFrame(const FName& ElementName) = 0;` — Toggles the named element's pause state. @param ElementName	The name of the element to affect
- L132 _public prototype_ `virtual void ToggleMediaCapture(const FName& ElementName) = 0;` — Adds/Enables/Disables a media-capture output pass for the specified element. Adds & enables a media-capture pass if one doesn't already exist. Just enables/disables if one already exits. @param ElementName	The name of the element to affect
- L140 _public prototype_ `virtual UCompositingMediaCaptureOutput* ResetMediaCapture(const FName& ElementName) = 0;` — Re-Prompts the user to select a UMediaOutput asset to associate the name element's media-capture pass with. @param ElementName	The name of the element to affect
- L147 _public prototype_ `virtual void RemoveMediaCapture(const FName& ElementName) = 0;` — Deletes any media-capture passes from the specified element. @param ElementName	The name of the element to affect
- L152 _public prototype_ `virtual void RefreshElementsList() = 0;` — Re-queries the scene for element actors and rebuilds the authoritative list used by the editor.
- L158 _public prototype_ `virtual void RequestRedraw() = 0;` — Dirties the draw state so editor element instance get ran/rendered this frame (utilized when rendering on demand, instead of intrinsically each frame).
- L166 _public prototype_ `virtual bool IsDrawing(ACompositingElement* CompElement) const = 0;` — Determines if the specified element is being rendered by the hidden compositing viewport. @param  CompElement	The element actor you're querying for @return True if the game-thread is in the middle of queuing the specified element.
- L173 _public prototype_ `virtual void OnCreateNewElement(AActor* NewElement) = 0;` — Function used to expose the editor call back function after a new composure element is created via Blueprint and C++. @param  NewElement	                             The new element that got created via Blueprint/C++
- L180 _public prototype_ `virtual void OnDeleteElement(AActor* ElementToDelete) = 0;` — Function used to expose the editor call back function after an existing composure element @param  ElementToDelete	                         The composure element that is going to be deleted.
- L184 _public prototype_ `DECLARE_EVENT_ThreeParams(ICompElementManager, FOnElementsChanged, const ECompElementEdActions , const TWeakObjectPtr<ACompositingElement>& , const FName& );` — Broadcasts whenever one or more elements are modified
- L185 _public prototype_ `virtual FOnElementsChanged& OnElementsChanged() = 0;`

#### Free symbols / members of external scopes

- L184 _delegate_ `DECLARE_EVENT_ThreeParams(ICompElementManager, FOnElementsChanged, const ECompElementEdActions , const TWeakObjectPtr<ACompositingElement>& , const FName& );` — Broadcasts whenever one or more elements are modified
