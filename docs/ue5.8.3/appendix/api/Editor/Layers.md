# Editor / Layers

- module root: `Source/Editor/Layers`
- headers: 15; symbols: 322
- symbol kinds: class=15, delegate=8, enum=1, enumerator=3, function=82, macro=5, member=69, namespace=2, prototype=130, typedef=5, variable=2
- DynamicallyLoadedModuleNames: PropertyEditor
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, SceneOutliner, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: UnrealEd

### `Source/Editor/Layers/Private/ActorLayerCollectionViewModel.h` (Private)


#### class `FActorLayerCollectionViewModel`  
`class FActorLayerCollectionViewModel : public TSharedFromThis< FActorLayerCollectionViewModel >, public FEditorUndoClient`  
_L17-127_
- inherits: `TSharedFromThis<FActorLayerCollectionViewModel>,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a collection of layers that belong to a collection of actors
- L23 _public prototype_ `virtual ~FActorLayerCollectionViewModel();` — FLayerCloud destructor
- L30 _public function_ `static TSharedRef< FActorLayerCollectionViewModel > Create( const TWeakObjectPtr< UEditorEngine >& InEditor )` — Factory method which creates a new FActorLayerCollectionViewModel object @param	InEditor		The UEditorEngine to use
- L42 _public prototype_ `TArray< TSharedPtr< FActorLayerViewModel > >& GetLayers();` — @return	The list of FLayer objects to be displayed
- L45 _public prototype_ `const TArray< TWeakObjectPtr< AActor > >& GetActors() const;` — @return	The Actors whose layers should be displayed
- L52 _public prototype_ `void SetActors( const TArray< TWeakObjectPtr< AActor > >& InActors );` — Sets the specified array of Actors whose layers should be displayed @param	InActors	The Actors whose layers should be displayed
- L55 _public prototype_ `void RemoveActorsFromAllLayers();` — Removes the set list of Actors from all of their currently assigned Layers
- L62 _public prototype_ `void RemoveActorsFromLayer( const TSharedPtr< FActorLayerViewModel >& Layer );` — Removes the set list of Actors from the specified Layer @param	Layer	The Layer to remove from the actors
- L69 _public prototype_ `DECLARE_DERIVED_EVENT( FActorLayerCollectionViewModel, ULayersSubsystem::FOnLayersChanged, FOnLayersChanged );` — Broadcasts whenever the number of layers changes
- L70 _public function_ `FOnLayersChanged& OnLayersChanged()`
- L80 _private prototype_ `FActorLayerCollectionViewModel( const TWeakObjectPtr< UEditorEngine >& InEditor );` — in the LayerCloud Constructor @param	InEditor		The UEditorEngine to use
- L83 _private prototype_ `void Initialize();` — Initializes the FActorLayerCollectionViewModel for use
- L86 _private prototype_ `void Refresh();` — Refreshes any cached information
- L89 _private prototype_ `void OnLayersChanged( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty );` — Refreshes the Layers list
- L92 _private prototype_ `void RefreshLayers();` — Refreshes the Layers list
- L95 _private prototype_ `void SortLayers();` — Sorts the Layers list
- L98 _private prototype_ `void AppendLayerNames( TArray< FName >& OutLayerNames );` — Appends names of the currently exposed layers to the specified array
- L106 _private prototype_ `bool DoAllActorsBelongtoLayer( const TSharedRef< FActorLayerViewModel >& Layer );` — Returns whether the specified layer has all the specified Actors assigned to it @param	Layer		The layer to check actor assignment on @return				Whether the Layer includes all the specified Actors
- L111 _private member_ `bool bIsRefreshing;` — true if the in the middle of refreshing
- L114 _private member_ `TArray< TSharedPtr< FActorLayerViewModel > > Layers;` — All layers shown in the LayersView
- L117 _private member_ `TArray< TWeakObjectPtr< AActor > > Actors;` — All actors whose layers are being exposed
- L120 _private member_ `const TWeakObjectPtr< UEditorEngine > Editor;` — The UEditorEngine to use
- L123 _private member_ `ULayersSubsystem* WorldLayers;` — The layer management logic object
- L126 _private member_ `FOnLayersChanged LayersChanged;` — Broadcasts whenever one or more layers changes

#### Free symbols / members of external scopes

- L69 _delegate_ `DECLARE_DERIVED_EVENT( FActorLayerCollectionViewModel, ULayersSubsystem::FOnLayersChanged, FOnLayersChanged );` — Broadcasts whenever the number of layers changes

### `Source/Editor/Layers/Private/ActorLayerViewModel.h` (Private)


#### class `FActorLayerViewModel`  
`class FActorLayerViewModel : public TSharedFromThis< FActorLayerViewModel >, public FEditorUndoClient`  
_L16-88_
- inherits: `TSharedFromThis<FActorLayerViewModel>,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a single Layer
- L22 _public prototype_ `virtual ~FActorLayerViewModel();` — FActorLayerViewModel destructor
- L30 _public function_ `static TSharedRef< FActorLayerViewModel > Create( const TWeakObjectPtr< ULayer >& InLayer, const TArray< TWeakObjectPtr< AActor > >& InActors, const TWeakObjectPtr< UEditorEngine >& InEditor )` — Factory method which creates a new FActorLayerViewModel object @param	InLayer			The layer wrap @param	InEditor		The UEditorEngine to use
- L42 _public prototype_ `FName GetFName() const;` — @return	The Layer's display name as a FName
- L45 _public prototype_ `FText GetName() const;` — @return	The Layer's display name as a FString
- L48 _public prototype_ `bool IsVisible() const;` — @return Whether the Layer is visible
- L55 _public member_ `FSimpleMulticastDelegate Changed;` — Broadcasts whenever the layer changes
- L66 _private prototype_ `FActorLayerViewModel( const TWeakObjectPtr< ULayer >& InLayer, const TArray< TWeakObjectPtr< AActor > >& InActors, const TWeakObjectPtr< UEditorEngine >& InEditor );` — FActorLayerViewModel Constructor @param	InLayer			The Layer to represent @param	InEditor		The UEditorEngine to use
- L69 _private prototype_ `void Initialize();` — Initializes the FActorLayerViewModel for use
- L72 _private prototype_ `void OnLayersChanged( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty );` — Called when a change occurs regarding Layers
- L75 _private prototype_ `void Refresh();` — Refreshes any cached information in the FActorLayerViewModel
- L81 _private member_ `const TWeakObjectPtr< UEditorEngine > Editor;` — The UEditorEngine to use
- L84 _private member_ `const TWeakObjectPtr< ULayer > Layer;` — The Layer this object represents
- L87 _private member_ `TArray< TWeakObjectPtr< AActor > > Actors;` — The Actors this object represents

### `Source/Editor/Layers/Private/ActorsAssignedToSpecificLayersFilter.h` (Private)


#### class `FActorsAssignedToSpecificLayersFilter`  
`class FActorsAssignedToSpecificLayersFilter : public TSceneOutlinerFilter<FActorTreeItem>, public TSharedFromThis< FActorsAssignedToSpecificLayersFilter >`  
_L9-92_
- inherits: `TSceneOutlinerFilter<FActorTreeItem>,TSharedFromThis<FActorsAssignedToSpecificLayersFilter>`
- L14 _public function_ `FActorsAssignedToSpecificLayersFilter() : TSceneOutlinerFilter<FActorTreeItem>(FSceneOutlinerFilter::EDefaultBehaviour::Fail)` — By default, any types not handled by this filter will fail
- L24 _public function_ `virtual bool PassesFilterImpl(const FActorTreeItem& InItem) const` — Returns whether the specified Item passes the Filter's text restrictions @param	InItem	The Item to check @return			Whether the specified Item passed the filter
- L49 _public function_ `void SetLayers( const TArray< FName >& InLayerNames )`
- L64 _public function_ `void AddLayer( FName LayerName )`
- L73 _public function_ `bool RemoveLayer( FName LayerName )`
- L81 _public function_ `void ClearLayers()`
- L91 _private member_ `TArray< FName > LayerNames;` — The list of layer names which actors need to belong to

### `Source/Editor/Layers/Private/LayerCollectionViewCommands.h` (Private)


#### class `FLayersViewCommands`  
`class FLayersViewCommands : public TCommands<FLayersViewCommands>`  
_L16-83_
- inherits: `TCommands<FLayersViewCommands>`
- desc: The set of commands supported by the LayersView
- L22 _public function_ `FLayersViewCommands() : TCommands<FLayersViewCommands> ( "LayersView",` — FLayersViewCommands Constructor
- L35 _public function_ `virtual void RegisterCommands() override` — Initialize the commands
- L55 _public member_ `TSharedPtr< FUICommandInfo > CreateEmptyLayer;` — Creates a new empty Layer
- L58 _public member_ `TSharedPtr< FUICommandInfo > AddSelectedActorsToNewLayer;` — Adds the Selected Actors To a New Layer
- L61 _public member_ `TSharedPtr< FUICommandInfo > AddSelectedActorsToSelectedLayer;` — Adds the Selected Actors to the Selected Layers
- L64 _public member_ `TSharedPtr< FUICommandInfo > RemoveSelectedActorsFromSelectedLayer;` — Removes the Selected Actors from the Selected Layers
- L67 _public member_ `TSharedPtr< FUICommandInfo > SelectActors;` — Selects the actors in the Selected Layers
- L70 _public member_ `TSharedPtr< FUICommandInfo > AppendActorsToSelection;` — Adds the actors in the Selected Layers to the currently selected Actors
- L73 _public member_ `TSharedPtr< FUICommandInfo > DeselectActors;` — Deselects the actors in the Selected Layers
- L76 _public member_ `TSharedPtr< FUICommandInfo > ToggleSelectedLayersVisibility;` — Toggles the visibility of the currently selected layers
- L79 _public member_ `TSharedPtr< FUICommandInfo > MakeAllLayersVisible;` — Makes all layers visible
- L82 _public member_ `TSharedPtr< FUICommandInfo > RequestRenameLayer;` — Requests a rename on the layer

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "LayersViewCommands"`

### `Source/Editor/Layers/Private/LayerCollectionViewModel.h` (Private)


#### class `FLayerCollectionViewModel`  
`class FLayerCollectionViewModel : public TSharedFromThis< FLayerCollectionViewModel >, public FEditorUndoClient`  
_L22-270_
- inherits: `TSharedFromThis<FLayerCollectionViewModel>,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a LayersView
- L28 _public prototype_ `virtual ~FLayerCollectionViewModel();` — FLayerCollectionViewModel destructor
- L36 _public function_ `static TSharedRef< FLayerCollectionViewModel > Create( const TWeakObjectPtr< UEditorEngine >& InEditor )` — Factory method which creates a new FLayerCollectionViewModel object @param	InWorldLayers	The layer management logic object @param	InEditor		The UEditorEngine to use
- L52 _public prototype_ `void AddFilter( const TSharedRef< LayerFilter >& InFilter );` — Adds a filter which restricts the layers shown in the LayersView @param	InFilter	The Filter to add
- L59 _public prototype_ `void RemoveFilter( const TSharedRef< LayerFilter >& InFilter );` — Removes a filter which restricted the layers shown in the LayersView @param	InFilter	The Filter to remove
- L62 _public prototype_ `TArray< TSharedPtr< FLayerViewModel > >& GetLayers();` — @return	The list of ULayer objects to be displayed in the LayersView
- L65 _public prototype_ `const TArray< TSharedPtr< FLayerViewModel > >& GetSelectedLayers() const;` — @return	The selected ULayer objects in the LayersView
- L72 _public prototype_ `void GetSelectedLayerNames( OUT TArray< FName >& OutSelectedLayerNames ) const;` — Appends the names of the currently selected layers to the provided array @param	OutSelectedLayerNames	The array to append the layer names to
- L79 _public prototype_ `void SetSelectedLayers( const TArray< TSharedPtr< FLayerViewModel > >& InSelectedLayers );` — Sets the specified array of ULayer objects as the currently selected layers @param	InSelectedLayers	The layers to select
- L82 _public prototype_ `void SetSelectedLayers( const TArray< FName >& LayerNames );` — Set the current selection to the specified Layer names
- L85 _public prototype_ `void SetSelectedLayer( const FName& LayerName );` — Set the current selection to the specified Layer
- L88 _public prototype_ `const TSharedRef< FUICommandList > GetCommandList() const;` — @return	The UICommandList supported by the LayersView
- L95 _public prototype_ `void AddActorsToNewLayer( TArray< TWeakObjectPtr< AActor > > Actors );` — Adds the specified actors to a new layer @param	Actors	The actors to add to the new layer
- L98 _public prototype_ `void ToggleLayerVisibility( const TSharedPtr< FLayerViewModel >& InLayer );` — Toggles the visibility of the given layer and those of the other layers selected with it
- L105 _public prototype_ `DECLARE_DERIVED_EVENT( FLayerCollectionViewModel, ULayersSubsystem::FOnLayersChanged, FOnLayersChanged );` — Broadcasts whenever the number of layers changes
- L106 _public function_ `FOnLayersChanged& OnLayersChanged()`
- L109 _public prototype_ `DECLARE_EVENT( FLayerCollectionViewModel, FOnSelectionChanged );` — Broadcasts whenever the currently selected layers changes
- L110 _public function_ `FOnSelectionChanged& OnSelectionChanged()`
- L113 _public prototype_ `DECLARE_EVENT( FLayerCollectionViewModel, FOnRenameRequested );` — Broadcasts whenever a rename is requested on the selected layers
- L114 _public function_ `FOnRenameRequested& OnRenameRequested()`
- L123 _private prototype_ `FLayerCollectionViewModel( const TWeakObjectPtr< UEditorEngine >& InEditor );` — FLayerCollectionViewModel Constructor @param	InWorldLayers	The layer management logic object @param	InEditor		The UEditorEngine to use
- L126 _private prototype_ `void Initialize();` — Initializes the LayersView for use
- L129 _private prototype_ `void Refresh();` — Refreshes any cached information
- L132 _private prototype_ `void OnFilterChanged();` — Handles updating the viewmodel when one of its filters changes
- L135 _private prototype_ `void OnLayersChanged( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty );` — Refreshes the Layers list
- L138 _private prototype_ `void OnResetLayers();` — Refreshes the Layers list
- L141 _private prototype_ `void OnLayerAdded( const TWeakObjectPtr< ULayer >& AddedLayer );` — Handles updating the internal viewmodels when new layers are created
- L144 _private prototype_ `void OnLayerDelete();` — Handles updating the internal viewmodels when layers are deleted
- L147 _private prototype_ `void DestructivelyPurgeInvalidViewModels( TArray< TWeakObjectPtr< ULayer > > &ActualLayers );` — Discards any viewmodels which are invalid
- L150 _private prototype_ `void CreateViewModels( const TArray< TWeakObjectPtr< ULayer > > &ActualLayers );` — Creates ViewModels for all the layers in the specified list
- L153 _private prototype_ `void RefreshFilteredLayers();` — Rebuilds the list of filtered layers
- L156 _private prototype_ `void SortFilteredLayers();` — Sorts the filtered layers list
- L159 _private prototype_ `void BindCommands();` — Binds all layer browser commands to delegates
- L162 _private prototype_ `void AppendSelectLayerNames( TArray< FName >& OutLayerNames ) const;` — Appends the selected layer names to the specified array
- L165 _private prototype_ `FName GenerateUniqueLayerName() const;` — @return	A guaranteed unique name for a layer
- L171 _private prototype_ `void DeleteLayer_Executed();` — Deletes the currently selected layers
- L174 _private prototype_ `bool DeleteLayer_CanExecute() const;` — @return	whether the currently selected layers can be deleted
- L177 _private prototype_ `void CreateEmptyLayer_Executed();` — @return	creates a new empty layer
- L180 _private prototype_ `bool CreateEmptyLayer_CanExecute() const;` — @return	whether a new layer empty layer can be created
- L183 _private prototype_ `void AddSelectedActorsToNewLayer_Executed();` — Adds the currently selected actors to the a new layer
- L186 _private prototype_ `bool AddSelectedActorsToNewLayer_CanExecute() const;` — @return	whether the currently selected layers can be added to a new layer
- L189 _private prototype_ `void AddSelectedActorsToSelectedLayer_Executed();` — Adds the currently selected actors to the selected layers
- L192 _private prototype_ `bool AddSelectedActorsToSelectedLayer_CanExecute() const;` — @return	whether the currently selected actors can be added to the selected layers
- L195 _private prototype_ `void RemoveSelectedActorsFromSelectedLayer_Executed();` — Removes the selected actors from the selected layers
- L198 _private prototype_ `bool RemoveSelectedActorsFromSelectedLayer_CanExecute() const;` — @return	whether the selected actors can be remove from the selected layers
- L201 _private prototype_ `void SelectActors_Executed();` — Selects the actors in the selected layers
- L204 _private prototype_ `bool SelectActors_CanExecute() const;` — @return	whether the actors in the selected layers can be selected
- L207 _private prototype_ `void AppendActorsToSelection_Executed();` — Appends the actors of the selected layers to the editors current actor selection
- L210 _private prototype_ `bool AppendActorsToSelection_CanExecute() const;` — @return	whether the actors of the selected layers can be added to the editors current actor selection
- L213 _private prototype_ `void DeselectActors_Executed();` — Deselects the actors belonging to the selected layers
- L216 _private prototype_ `bool DeselectActors_CanExecute() const;` — @return	whether the actors belonging to the selected layers can be deselected
- L219 _private prototype_ `void ToggleSelectedLayersVisibility_Executed();` — Toggles the selected layers visibility
- L222 _private prototype_ `bool ToggleSelectedLayersVisibility_CanExecute() const;` — @return	whether the selected layers visibility can be toggled
- L225 _private prototype_ `void MakeAllLayersVisible_Executed();` — Makes all layers visible
- L228 _private prototype_ `bool MakeAllLayersVisible_CanExecute() const;` — @return	whether all layers can be made visible
- L231 _private prototype_ `void RequestRenameLayer_Executed();` — Requests renaming of selected layers
- L234 _private prototype_ `bool RequestRenameLayer_CanExecute() const;` — @return true if the layer can be renamed
- L239 _private member_ `bool bIsRefreshing;` — true if the LayersView is in the middle of refreshing
- L242 _private member_ `const TSharedRef< LayerFilterCollection > Filters;` — The collection of filters used to restrict the layers shown in the LayersView
- L245 _private member_ `TArray< TSharedPtr< FLayerViewModel > > FilteredLayerViewModels;` — All layers shown in the LayersView
- L248 _private member_ `TArray< TSharedPtr< FLayerViewModel > > AllLayerViewModels;` — All layers managed by the LayersView
- L251 _private member_ `TArray< TSharedPtr< FLayerViewModel > > SelectedLayers;` — Currently selected layers
- L254 _private member_ `const TSharedRef< FUICommandList > CommandList;` — The list of commands with bound delegates for the layer browser
- L257 _private member_ `const TWeakObjectPtr< UEditorEngine > Editor;` — The UEditorEngine to use
- L260 _private member_ `ULayersSubsystem* WorldLayers;` — The layer management logic object
- L263 _private member_ `FOnLayersChanged LayersChanged;` — Broadcasts whenever one or more layers changes
- L266 _private member_ `FOnSelectionChanged SelectionChanged;` — Broadcasts whenever the currently selected layers changes
- L269 _private member_ `FOnRenameRequested RenameRequested;` — Broadcasts whenever a rename is requested on the selected layers

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef TFilterCollection< const TSharedPtr< FLayerViewModel >& > LayerFilterCollection;`
- L17 _typedef_ `typedef IFilter< const TSharedPtr< FLayerViewModel >& > LayerFilter;`
- L105 _delegate_ `DECLARE_DERIVED_EVENT( FLayerCollectionViewModel, ULayersSubsystem::FOnLayersChanged, FOnLayersChanged );` — Broadcasts whenever the number of layers changes
- L109 _delegate_ `DECLARE_EVENT( FLayerCollectionViewModel, FOnSelectionChanged );` — Broadcasts whenever the currently selected layers changes
- L113 _delegate_ `DECLARE_EVENT( FLayerCollectionViewModel, FOnRenameRequested );` — Broadcasts whenever a rename is requested on the selected layers

### `Source/Editor/Layers/Private/LayerViewModel.h` (Private)


#### class `FLayerViewModel`  
`class FLayerViewModel : public TSharedFromThis< FLayerViewModel >, public FEditorUndoClient`  
_L16-237_
- inherits: `TSharedFromThis<FLayerViewModel>,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a single Layer
- L22 _public prototype_ `virtual ~FLayerViewModel();` — FLayerViewModel destructor
- L31 _public function_ `static TSharedRef< FLayerViewModel > Create( const TWeakObjectPtr< ULayer >& InLayer, const TWeakObjectPtr< UEditorEngine >& InEditor )` — Factory method which creates a new FLayerViewModel object @param	InLayer			The layer wrap @param	InWorldLayers	The layer management logic object @param	InEditor		The UEditorEngine to use
- L43 _public prototype_ `FName GetFName() const;` — @return	The Layer's display name as a FName
- L46 _public prototype_ `FString GetName() const;` — @return	The Layer's display name as a FString
- L49 _public prototype_ `FText GetNameAsText() const;` — @return	The Layer's display name as a FString
- L52 _public prototype_ `bool IsVisible() const;` — @return Whether the Layer is visible
- L57 _public prototype_ `void ToggleVisibility();` — Toggles the specified layer's visibility
- L66 _public prototype_ `bool CanRenameTo( const FName& NewLayerName, FString& OutMessage ) const;` — Returns whether the layer can be assigned the specified name @param	NewLayerName		The Layers new name @param	OutMessage [OUT]	A returned description explaining the boolean result @return						true then the name can be assigned
- L73 _public prototype_ `void RenameTo( const FName& NewLayerName );` — Renames the Layer to the specified name @param	NewLayerName	The Layers new name
- L83 _public prototype_ `bool CanAssignActors( const TArray< TWeakObjectPtr<AActor> > Actors, FText& OutMessage ) const;` — Returns whether the specified actors can be assigned to the Layer @param	Actors				The Actors to check if assignment is valid @param	OutMessage [OUT]	A returned description explaining the boolean result @return						if true then at least one actor can be assigned; If false, either Invalid actors were discovered or all actors are already assigned
- L93 _public prototype_ `bool CanAssignActor( const TWeakObjectPtr<AActor> Actor, FText& OutMessage ) const;` — Returns whether the specified actor can be assigned to the Layer @param	Actor				The Actor to check if assignment is valid @param	OutMessage [OUT]	A returned description explaining the boolean result @return						if true then at least one actor can be assigned; If false, either the Actor is Invalid or already assigned
- L100 _public prototype_ `void AppendActors( TArray< TWeakObjectPtr< AActor > >& InActors ) const;` — Appends all of the actors associated with this layer to the specified list @param	InActors	the list to append to
- L107 _public prototype_ `void AppendActorsOfSpecificType( TArray< TWeakObjectPtr< AActor > >& InActors, const TWeakObjectPtr< UClass >& Class );` — Appends all of the actors associated with this layer to the specified list @param	InActors	the list to append to
- L114 _public prototype_ `void AddActor( const TWeakObjectPtr<AActor>& Actor );` — Adds the specified actor to the layer @param	Actor	the actor to add
- L122 _public prototype_ `void AddActors( const TArray< TWeakObjectPtr<AActor> >& Actors );` — Adds the specified actors to the layer @param	Actors		The actors to add @param	LayerName	The layer to add the actors to
- L130 _public prototype_ `void RemoveActors( const TArray< TWeakObjectPtr<AActor> >& Actors );` — Removes the specified actors from the layer @param	Actors		The actors to add @param	LayerName	The layer to add the actors to
- L137 _public prototype_ `void RemoveActor( const TWeakObjectPtr<AActor>& Actor );` — Removes the specified actor from the layer @param	Actor	the actor to remove
- L147 _public prototype_ `void SelectActors( bool bSelect, bool bNotify, bool bSelectEvenIfHidden, const TSharedPtr< IFilter< const TWeakObjectPtr< AActor >& > >& Filter );` — Selects in the Editor all the Actors assigned to the Layer, based on the specified conditions. @param	bSelect					if true actors will be selected; If false, actors will be deselected @param	bNotify					if true the editor will be notified of the selection change; If false, the editor will not @param	bSelectEvenIfHidden		if true actors that are hidden will be selected; If false, they will be skipped @param	Filter					Only actors which pass the filters restrictions will be selected
- L155 _public prototype_ `FText GetActorStatTotal( int32 StatsIndex ) const;` — Retrieves the total number of actors of a specific type currently assigned to the Layer as a FString @param	StatsIndex		The array index of the FLayerActorStats @return					The total actors as a FString
- L160 _public prototype_ `void SelectActorsOfSpecificType( const TWeakObjectPtr< UClass >& Class );` — Selected the Actors assigned to the Layer that are of a certain type
- L163 _public prototype_ `const TArray< FLayerActorStats >& GetActorStats() const;` — @return	An array of Actor stats regarding the Layer
- L166 _public prototype_ `void SetDataSource( const TWeakObjectPtr< ULayer >& InLayer );` — Sets the ULayer this viewmodel should represent
- L169 _public prototype_ `const TWeakObjectPtr< ULayer > GetDataSource();` — @return The ULayer this viewmodel represents
- L176 _public function_ `DECLARE_EVENT( FLayerViewModel, FChangedEvent ) FChangedEvent& OnChanged()` — Broadcasts whenever the layer changes
- L180 _public function_ `DECLARE_EVENT( FLayerViewModel, FRenamedRequestEvent ) FRenamedRequestEvent& OnRenamedRequest()` — Broadcasts whenever renaming a layer is requested
- L182 _public function_ `void BroadcastRenameRequest()`
- L185 _public function_ `DECLARE_EVENT_OneParam( FLayerViewModel, FVisibilityToggledEvent, const TSharedPtr<FLayerViewModel>& ) FVisibilityToggledEvent& OnVisibilityToggled()` — Broadcasts whenever a layer visibility toggle is requested
- L196 _private prototype_ `FLayerViewModel( const TWeakObjectPtr< ULayer >& InLayer, const TWeakObjectPtr< UEditorEngine >& InEditor );` — FLayerViewModel Constructor @param	InLayer			The Layer to represent @param	InEditor		The UEditorEngine to use
- L199 _private prototype_ `void Initialize();` — Initializes the FLayerViewModel for use
- L202 _private prototype_ `void OnLayersChanged( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty );` — Called when a change occurs regarding Layers
- L205 _private prototype_ `void Refresh();` — Refreshes any cached information in the FLayerViewModel
- L208 _private prototype_ `void RefreshActorStats();` — Refreshes the cached ActorStats
- L211 _private function_ `virtual void PostUndo(bool bSuccess) override`
- L212 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L218 _private member_ `TArray< FLayerActorStats > ActorStats;` — The Actor stats of the Layer
- L221 _private member_ `const TWeakObjectPtr< UEditorEngine > Editor;` — The UEditorEngine to use
- L224 _private member_ `ULayersSubsystem* WorldLayers;` — The layer management logic object
- L227 _private member_ `TWeakObjectPtr< ULayer > Layer;` — The Layer this object represents
- L230 _private member_ `FChangedEvent ChangedEvent;` — Broadcasts whenever the layer changes
- L233 _private member_ `FRenamedRequestEvent RenamedRequestEvent;` — Broadcasts whenever a rename is requested
- L236 _private member_ `FVisibilityToggledEvent VisibilityToggledEvent;` — Broadcasts whenever a layer visibility toggle is requested

#### Free symbols / members of external scopes

- L176 _delegate_ `DECLARE_EVENT( FLayerViewModel, FChangedEvent ) FChangedEvent& OnChanged() { return ChangedEvent; } DECLARE_EVENT( FLayerViewModel, FRenamedRequestEvent ) FRenamedRequestEvent& OnRenamedRequest() { return RenamedRequestEvent; } void BroadcastRenameRequest() { RenamedRequestEvent.Broadcast(); } DECLARE_EVENT_OneParam( FLayerViewModel, FVisibilityToggledEvent, const TSharedPtr<FLayerViewModel>& ) FVisibilityToggledEvent& OnVisibilityToggled() { return VisibilityToggledEvent; } private: FLayerViewModel( const TWeakObjectPtr< ULayer >& InLayer, const TWeakObjectPtr< UEditorEngine >& InEditor );` — Broadcasts whenever the layer changes
- L180 _delegate_ `DECLARE_EVENT( FLayerViewModel, FRenamedRequestEvent ) FRenamedRequestEvent& OnRenamedRequest() { return RenamedRequestEvent; } void BroadcastRenameRequest() { RenamedRequestEvent.Broadcast(); } DECLARE_EVENT_OneParam( FLayerViewModel, FVisibilityToggledEvent, const TSharedPtr<FLayerViewModel>& ) FVisibilityToggledEvent& OnVisibilityToggled() { return VisibilityToggledEvent; } private: FLayerViewModel( const TWeakObjectPtr< ULayer >& InLayer, const TWeakObjectPtr< UEditorEngine >& InEditor );` — Broadcasts whenever renaming a layer is requested
- L185 _delegate_ `DECLARE_EVENT_OneParam( FLayerViewModel, FVisibilityToggledEvent, const TSharedPtr<FLayerViewModel>& ) FVisibilityToggledEvent& OnVisibilityToggled() { return VisibilityToggledEvent; } private: FLayerViewModel( const TWeakObjectPtr< ULayer >& InLayer, const TWeakObjectPtr< UEditorEngine >& InEditor );` — Broadcasts whenever a layer visibility toggle is requested

### `Source/Editor/Layers/Private/SActorLayerCloud.h` (Private)


#### class `SActorLayerCloud`  
`class SActorLayerCloud : public SCompoundWidget`  
_L29-184_
- inherits: `SCompoundWidget`
- desc: Displays a list of Layers in a "cloud" like format to the user
- L33 _public function_ `SLATE_BEGIN_ARGS( SActorLayerCloud )`
- L36 _public function_ `~SActorLayerCloud()`
- L48 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef< FActorLayerCollectionViewModel >& InViewModel )` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L80 _private function_ `void Reconstruct()` — Rebuilds the set of individual widgets representing each displayed Layer
- L136 _private function_ `void OnLayersChanged( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty )` — Called whenever a change is made to Layers @param	Action				The action taken on one or more layers @param	ChangedLayer		The layer that changed @param	ChangedProperty		The property that changed
- L149 _private function_ `EVisibility GetNoLayersMessageVisibility() const` — Returns the current visibility for the NoLayers message
- L159 _private function_ `FReply OnRemoveAllLayersClicked()` — Removes all the selected actors from the currently exposed Layers @return  Returns whether the event was handled, along with other possible actions
- L170 _private function_ `FReply OnRemoveLayerFromActorsClicked( const TSharedPtr< FActorLayerViewModel > Layer )` — Removes all the selected actors from the clicked Layer @return  Returns whether the event was handled, along with other possible actions
- L180 _private member_ `TSharedPtr< SWrapBox > TagArea;` — The widget box that holds the layer tags
- L183 _private member_ `TSharedPtr< FActorLayerCollectionViewModel > ViewModel;` — The ViewModel for the SWidget

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "LayerCloud"`

### `Source/Editor/Layers/Private/SLayerBrowser.h` (Private)


#### enum `ELayerBrowserMode::Type`  
`enum Type`  
_L32-38_
- L34 _public enumerator_ `Layers`
- L35 _public enumerator_ `LayerContents`
- L37 _public enumerator_ `Count`

#### class `SLayerBrowser`  
`class SLayerBrowser : public SCompoundWidget`  
_L45-460_
- inherits: `SCompoundWidget`
- L49 _public function_ `SLATE_BEGIN_ARGS( SLayerBrowser )`
- L52 _public function_ `~SLayerBrowser()`
- L66 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L72 _protected function_ `FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override` — Overridden from SWidget: Called when a key is pressed down
- L88 _protected function_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override` — Called during drag and drop when the drag leaves a widget. @param DragDropEvent   The drag and drop event.
- L105 _protected function_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override` — Called during drag and drop when the the mouse is being dragged over a widget. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L201 _protected function_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override` — Called when the user is dropping something onto a widget; terminates drag and drop. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L263 _private function_ `void RemoveActorsFromSelectedLayer( const TArray< TWeakObjectPtr< AActor > >& Actors )`
- L268 _private function_ `TSharedRef< ISceneOutlinerColumn > CreateCustomLayerColumn( ISceneOutliner& SceneOutliner ) const`
- L273 _private function_ `FSlateColor GetInvertedForegroundIfHovered() const`
- L279 _private function_ `const FSlateBrush* GetToggleModeButtonImageBrush() const`
- L286 _private prototype_ `FText GetLayerContentsHeaderText() const;`
- L289 _private function_ `EVisibility IsVisibleIfModeIs( ELayerBrowserMode::Type DesiredMode ) const` — Returns the visibility of the See Contents label
- L294 _private function_ `EVisibility GetLayerContentsHeaderVisibility() const`
- L299 _private function_ `FReply ToggleLayerContents()`
- L316 _private function_ `void SetupLayersMode()`
- L336 _private function_ `void SetupLayerContentsMode()`
- L357 _private function_ `void TransformLayerToString( const TSharedPtr< FLayerViewModel >& Layer, OUT TArray< FString >& OutSearchStrings ) const`
- L367 _private function_ `void UpdateLayerContentsFilter()`
- L374 _private function_ `void UpdateSelectedLayer()`
- L390 _private function_ `void OnLayersChanged( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty )`
- L411 _private function_ `void OnRenameRequested()` — Callback when layers want to be renamed
- L416 _private function_ `TSharedPtr< SWidget > ConstructLayerContextMenu()`
- L421 _private prototype_ `void OnFilterTextChanged( const FText& InNewText );`
- L426 _private member_ `TSharedPtr< SButton > ToggleModeButton;`
- L429 _private member_ `TSharedPtr< SVerticalBox > ContentAreaBox;`
- L432 _private member_ `TSharedPtr< SBorder > LayersSection;`
- L435 _private member_ `TSharedPtr< SBorder > LayerContentsSection;`
- L438 _private member_ `TSharedPtr< SBorder > LayerContentsHeader;`
- L441 _private member_ `TSharedPtr< class SSearchBox> SearchBoxPtr;`
- L444 _private member_ `TSharedPtr< LayerTextFilter > SearchBoxLayerFilter;`
- L447 _private member_ `TSharedPtr< FActorsAssignedToSpecificLayersFilter > SelectedLayersFilter;`
- L450 _private member_ `TSharedPtr< FLayerCollectionViewModel > LayerCollectionViewModel;`
- L453 _private member_ `ELayerBrowserMode::Type Mode;`
- L456 _private member_ `TSharedPtr< FLayerViewModel > SelectedLayerViewModel;`
- L459 _private member_ `TSharedPtr< SLayersView > LayersView;` — The layer view widget, displays all the layers in the level

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TTextFilter< const TSharedPtr< FLayerViewModel >& > LayerTextFilter;`
- L30 _namespace_ `namespace ELayerBrowserMode`

### `Source/Editor/Layers/Private/SLayerStats.h` (Private)


#### class `SLayerStats`  
`class SLayerStats : public SCompoundWidget`  
_L24-204_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS( SLayerStats )`
- L32 _public function_ `~SLayerStats()` — SLayerStats destructor
- L44 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef< FLayerViewModel >& InViewModel )` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The layer the row widget is supposed to represent
- L61 _public function_ `void Reconstruct()` — Rebuilds the children widgets of the StatsArea
- L117 _private function_ `EVisibility GetVisibility( int StatsIndex ) const` — Gets the appropriate EVisibility for the specified button depending on the button's current state @param	StatsIndex	The index into StatButtonWidgets to find the associated button @return				The EVisibility
- L135 _private function_ `FSlateColor GetForegroundColorForButton( int StatsIndex ) const` — Gets the appropriate SlateColor for the specified button depending on the button's current state @param	StatsIndex	The index into StatButtonWidgets to find the associated button @return				The ForegroundColor
- L154 _private function_ `FReply SelectLayerActorsOfSpecificType( const TWeakObjectPtr< UClass > Class )` — Selected the Actors assigned to the Layer of the specified type @param	Class	The Actor class to select by
- L165 _private function_ `FReply RemoveAllLayerActorsOfSpecificType( const TWeakObjectPtr< UClass > Class )` — Remove the Actors assigned to the Layer of the specified type @param	Class	The Actor class to select by
- L178 _private function_ `FText GetStatButtonToolTipText( const TWeakObjectPtr< UClass > Class ) const` — Retrieves the appropriate tooltip text for the stats button of the specified index @param Class	The Actor class which the stats are associated with
- L188 _private function_ `FText GetRemoveStatButtonToolTipText( const TWeakObjectPtr< UClass > Class ) const` — Retrieves the appropriate tooltip text for the remove stats button of the specified index @param Class	The Actor class which the stats are associated with
- L197 _private member_ `TSharedPtr< FLayerViewModel > ViewModel;` — The layer associated with this widget
- L200 _private member_ `TSharedPtr< SHorizontalBox > StatsArea;` — The Box widget holding the individual stats specific widgets
- L203 _private member_ `TArray< TSharedPtr< SButton> > StatButtonWidgets;` — The button widgets representing individual stats

#### Free symbols / members of external scopes

- L20 _macro_ `#define LOCTEXT_NAMESPACE "LayerStats"`

### `Source/Editor/Layers/Private/SLayersCommandsMenu.h` (Private)


#### class `SLayersCommandsMenu`  
`class SLayersCommandsMenu : public SCompoundWidget`  
_L13-35_
- inherits: `SCompoundWidget`
- desc: The widget that represents a row in the LayersView's list view control.  Generates widgets for each column on demand.
- L18 _public function_ `SLATE_BEGIN_ARGS( SLayersCommandsMenu ) :_CloseWindowAfterMenuSelection( true )`
- L21 _public prototype_ `SLATE_ARGUMENT( bool, CloseWindowAfterMenuSelection ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< FLayerCollectionViewModel > InViewModel );`
- L34 _private member_ `TSharedPtr< FLayerCollectionViewModel > ViewModel;` — The UI logic of the LayersView that is not Slate specific

### `Source/Editor/Layers/Private/SLayersView.h` (Private)


#### class `SLayersView`  
`class SLayersView : public SCompoundWidget`  
_L31-386_
- inherits: `SCompoundWidget`
- desc: A slate widget that can be used to display a list of Layers and perform various layers related actions
- L34 _public typedef_ `typedef SListView< TSharedPtr< FLayerViewModel > >::FOnGenerateRow FOnGenerateRow;`
- L38 _public function_ `SLATE_BEGIN_ARGS( SLayersView )`
- L39 _public function_ `SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_ARGUMENT( FOnContextMenuOpening, ConstructContextMenu ) SLATE_EVENT( FOnGenerateRow, OnGenerateRow ) SLATE_END_ARGS() SLayersView() : bUpdatingSelection( false )`
- L51 _public function_ `~SLayersView()` — SLayersView destructor
- L64 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef< FLayerCollectionViewModel >& InViewModel )` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L133 _public function_ `void RequestRenameOnSelectedLayer()` — Requests a rename on the selected layer, first forcing the item to scroll into view
- L149 _protected function_ `virtual bool SupportsKeyboardFocus() const override` — Checks to see if this widget supports keyboard focus.  Override this in derived classes. @return  True if this widget can take keyboard focus
- L162 _protected function_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override` — Called after a key is pressed when this widget has focus @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L172 _protected function_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override` — Called during drag and drop when the drag leaves a widget. @param DragDropEvent   The drag and drop event.
- L189 _protected function_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override` — Called during drag and drop when the the mouse is being dragged over a widget. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L210 _protected function_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override` — Called when the user is dropping something onto a widget; terminates drag and drop. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L253 _protected function_ `FReply OnDragRow(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L285 _private function_ `TSharedRef< ITableRow > OnGenerateRowDefault( const TSharedPtr< FLayerViewModel > Item, const TSharedRef< STableViewBase >& OwnerTable )` — Called by SListView to generate a table row for the specified item. @param	Item		The FLayerViewModel to generate a TableRow widget for @param	OwnerTable	The TableViewBase which will own the generated TableRow widget @return The generated TableRow widget
- L299 _private function_ `void RequestRefresh( const ELayersAction::Type Action, const TWeakObjectPtr< ULayer >& ChangedLayer, const FName& ChangedProperty )` — Kicks off a Refresh of the LayersView @param	Action				The action taken on one or more layers @param	ChangedLayer		The layer that changed @param	ChangedProperty		The property that changed
- L307 _private function_ `void UpdateSelection()` — Called whenever the viewmodels selection changes
- L335 _private function_ `void OnSelectionChanged( const TSharedPtr< FLayerViewModel > Item, ESelectInfo::Type SelectInfo )` — Called by SListView when the selection has changed @param	Item	The Layer affected by the selection change @param SelectInfo Provides context on how the selection changed
- L352 _private function_ `void OnListViewMouseButtonDoubleClick( const TSharedPtr< FLayerViewModel > Item )` — Called by SListView when the user double-clicks on an item @param	Item	The Layer that was double clicked
- L359 _private function_ `void OnItemScrolledIntoView(TSharedPtr<FLayerViewModel> LayerItem, const TSharedPtr<ITableRow>& Widget)` — Handler for when an item has scrolled into view after having been requested to do so
- L373 _private member_ `bool bUpdatingSelection;` — Whether the view is currently updating the viewmodel selection
- L376 _private member_ `TSharedPtr< FLayerCollectionViewModel > ViewModel;` — The UI logic of the LayersView that is not Slate specific
- L379 _private member_ `TSharedPtr< SLayersListView > ListView;` — Our list view used in the SLayersViews
- L382 _private member_ `TAttribute< FText > HighlightText;` — The string to highlight on any text contained in the view widget
- L385 _private member_ `TWeakPtr< FLayerViewModel > RequestedRenameLayer;` — Used to defer a rename on a layer until after it has been scrolled into view

#### Free symbols / members of external scopes

- L24 _macro_ `#define LOCTEXT_NAMESPACE "LayersView"`
- L26 _typedef_ `typedef SListView< TSharedPtr< FLayerViewModel > > SLayersListView;`

### `Source/Editor/Layers/Private/SLayersViewRow.h` (Private)


#### class `SLayersViewRow`  
`class SLayersViewRow : public SMultiColumnTableRow< TSharedPtr< FLayerViewModel > >`  
_L28-139_
- inherits: `SMultiColumnTableRow<TSharedPtr<FLayerViewModel>>`
- desc: The widget that represents a row in the LayersView's list view control.  Generates widgets for each column on demand.
- L33 _public function_ `SLATE_BEGIN_ARGS( SLayersViewRow )`
- L34 _public prototype_ `SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef< FLayerViewModel > InViewModel, TSharedRef< STableViewBase > InOwnerTableView );`
- L47 _public prototype_ `~SLayersViewRow();`
- L58 _protected prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForColumn( const FName& ColumnID ) override;` — Constructs the widget that represents the specified ColumnID for this Row @param ColumnName    A unique ID for a column in this TableView; see SHeaderRow::FColumn for more info. @return a widget to represent the contents of a cell in this row of a TableView.
- L61 _protected prototype_ `void OnRenameLayerTextCommitted(const FText& InText, ETextCommit::Type eInCommitType);` — Callback when the SInlineEditableTextBlock is committed, to update the name of the layer this row represents.
- L64 _protected prototype_ `bool OnRenameLayerTextChanged(const FText& NewText, FText& OutErrorMessage);` — Callback when the SInlineEditableTextBlock is changed, to check for error conditions.
- L71 _protected prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;` — Called during drag and drop when the drag leaves a widget. @param DragDropEvent   The drag and drop event.
- L81 _protected prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — Called during drag and drop when the the mouse is being dragged over a widget. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L91 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — Called when the user is dropping something onto a widget; terminates drag and drop. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L102 _private prototype_ `FSlateColor GetColorAndOpacity() const;` — Returns the Color and Opacity for displaying the bound Layer's Name. The Color and Opacity changes depending on whether a drag/drop operation is occurring @return	The SlateColor to render the Layer's name in
- L109 _private function_ `FReply OnToggleVisibility()` — Called when the user clicks on the visibility icon for a layer's row widget @return	A reply that indicated whether this event was handled.
- L121 _private prototype_ `const FSlateBrush* GetVisibilityBrushForLayer() const;` — Called to get the Slate Image Brush representing the visibility state of the layer this row widget represents @return	The SlateBrush representing the layer's visibility state
- L126 _private member_ `TSharedPtr< FLayerViewModel > ViewModel;` — The layer associated with this row of data
- L129 _private member_ `TSharedPtr< SButton > VisibilityButton;` — The visibility button for the layer
- L132 _private member_ `TAttribute< FText > HighlightText;` — The string to highlight on any text contained in the row widget
- L135 _private member_ `TSharedPtr< SInlineEditableTextBlock > InlineTextBlock;` — Widget for displaying and editing the Layer name
- L138 _private member_ `FDelegateHandle EnterEditingModeDelegateHandle;` — Handle to the registered EnterEditingMode delegate

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace LayersView`
- L21 _variable_ `static const FName ColumnID_LayerLabel( "Laye` (scope `LayersView`) — IDs for list columns
- L22 _variable_ `static const FName ColumnID_Visibility( "Visi` (scope `LayersView`)

### `Source/Editor/Layers/Private/SceneOutlinerLayerContentsColumn.h` (Private)


#### class `FSceneOutlinerLayerContentsColumn`  
`class FSceneOutlinerLayerContentsColumn : public ISceneOutlinerColumn`  
_L22-55_
- inherits: `ISceneOutlinerColumn`
- desc: A custom column for the SceneOutliner which allows the user to remove actors from the contents of a layer with a single click
- L30 _public prototype_ `FSceneOutlinerLayerContentsColumn( const TSharedRef< class FLayerViewModel >& InViewModel );` — Constructor
- L32 _public prototype_ `virtual ~FSceneOutlinerLayerContentsColumn() = default;`
- L34 _public prototype_ `static FName GetID();`
- L39 _public prototype_ `virtual FName GetColumnID() override;`
- L41 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L43 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L49 _private prototype_ `FReply OnRemoveFromLayerClicked( const TWeakObjectPtr< AActor > Actor );`
- L54 _private member_ `const TSharedRef< FLayerViewModel > ViewModel;`

### `Source/Editor/Layers/Public/LayersDragDropOp.h` (Public)


#### class `FLayersDragDropOp`  
`class FLayersDragDropOp : public FDecoratedDragDropOp`  
_L15-24_
- inherits: `FDecoratedDragDropOp`
- desc: Drag/drop operation for dragging layers in the editor
- L18 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FLayersDragDropOp, FDragDropOperation) TArray<FName> Layers;`
- L23 _public prototype_ `virtual void Construct() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LAYERS_API`

### `Source/Editor/Layers/Public/LayersModule.h` (Public)


#### class `FLayersModule`  
`class FLayersModule : public IModuleInterface`  
_L14-47_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related peices for Layers
- L22 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L27 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L32 _public prototype_ `virtual TSharedRef<class SWidget> CreateLayerBrowser();` — Creates a Layer Browser widget
- L37 _public prototype_ `virtual TSharedRef< class SWidget> CreateLayerCloud( const TArray< TWeakObjectPtr< AActor > >& Actors );` — Creates a widget that represents the layers the specified actors share in common as a cloud
- L40 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FLayersMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the layers menus
- L41 _public function_ `virtual TArray<FLayersMenuExtender>& GetAllLayersMenuExtenders()`
- L46 _private member_ `TArray<FLayersMenuExtender> LayersMenuExtenders;` — All extender delegates for the layers menus

#### Free symbols / members of external scopes

- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FLayersMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the layers menus
