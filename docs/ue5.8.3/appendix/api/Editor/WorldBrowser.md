# Editor / WorldBrowser

- module root: `Source/Editor/WorldBrowser`
- headers: 32; symbols: 1604
- symbol kinds: class=33, delegate=15, enum=7, enumerator=23, externvar=9, function=155, macro=5, member=347, namespace=14, prototype=955, struct=24, typedef=12, variable=5
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools, ContentBrowser, MeshMergeUtilities, MeshUtilities, SceneOutliner
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, Core, CoreUObject, DesktopPlatform, EditorConfig, EditorFramework, EditorWidgets, Engine, Foliage, FoliageEdit, GraphEditor, ImageCore, ImageWrapper, InputCore, Json, Landscape, LandscapeEditor, LevelEditor, MainFrame, MaterialUtilities, MeshDescription, NewLevelDialog, PropertyEditor, RHI, RenderCore, Slate, SlateCore, SourceControl, SourceControlWindows, StaticMeshDescription, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools, MeshMergeUtilities, MeshUtilities

### `Source/Editor/WorldBrowser/Private/LevelCollectionCommands.h` (Private)


#### class `FLevelCollectionCommands`  
`class FLevelCollectionCommands : public TCommands<FLevelCollectionCommands>`  
_L13-365_
- inherits: `TCommands<FLevelCollectionCommands>`
- desc: The set of commands supported by the WorldView
- L20 _public function_ `FLevelCollectionCommands() : TCommands<FLevelCollectionCommands> ( "WorldBrowser",` — FLevelCollectionCommands Constructor
- L32 _public function_ `virtual void RegisterCommands() override` — Initialize the commands
- L146 _public member_ `TSharedPtr< FUICommandInfo > RefreshBrowser;` — refreshes all world cached data
- L150 _public member_ `TSharedPtr< FUICommandInfo > FixUpInvalidReference;` — Replaces selected invalid level with an already existing one, prompts for path
- L153 _public member_ `TSharedPtr< FUICommandInfo > RemoveInvalidReference;` — Removes the ULevelStreaming reference to the selected invalid levels
- L157 _public member_ `TSharedPtr< FUICommandInfo > World_MakeLevelCurrent;` — makes the selected level the current level
- L160 _public member_ `TSharedPtr< FUICommandInfo> World_FindInContentBrowser;` — finds the selected levels in the content browser
- L163 _public member_ `TSharedPtr< FUICommandInfo > World_LoadLevel;` — Load level to the world
- L166 _public member_ `TSharedPtr< FUICommandInfo > World_UnloadLevel;` — Unload level from the world
- L169 _public member_ `TSharedPtr< FUICommandInfo > World_SaveSelectedLevels;` — Save selected levels; prompts for checkout if necessary
- L172 _public member_ `TSharedPtr< FUICommandInfo > World_SaveSelectedLevelAs;` — Save selected level under new name; prompts for checkout if necessary
- L175 _public member_ `TSharedPtr< FUICommandInfo > World_MigrateSelectedLevels;` — Migrate selected levels; copies levels and all their dependencies to another game
- L178 _public member_ `TSharedPtr< FUICommandInfo > World_MergeSelectedLevels;` — Merges the selected levels into a new level; prompts for save path; removes the levels that were merged
- L181 _public member_ `TSharedPtr< FUICommandInfo > World_CreateNewLevel;` — Creates a new level; prompts for save path
- L184 _public member_ `TSharedPtr< FUICommandInfo > World_AddExistingLevel;` — Adds an existing streaming level to the persistent; prompts for path
- L187 _public member_ `TSharedPtr< FUICommandInfo > World_AddSelectedActorsToNewLevel;` — Creates a new empty level and moves the selected actors to it; prompts for save path
- L190 _public member_ `TSharedPtr< FUICommandInfo > World_RemoveSelectedLevels;` — Removes the selected levels from the disk
- L194 _public member_ `TSharedPtr< FUICommandInfo > MoveWorldOrigin;` — Move world origin to selected level
- L197 _public member_ `TSharedPtr< FUICommandInfo > ResetWorldOrigin;` — Move world origin to zero (reset)
- L200 _public member_ `TSharedPtr< FUICommandInfo > ResetLevelOrigin;` — Move level origin to zero (reset)
- L204 _public member_ `TSharedPtr< FUICommandInfo > SelectAllLevels;` — Selects all levels within the level browser
- L207 _public member_ `TSharedPtr< FUICommandInfo > DeselectAllLevels;` — Deselects all levels within the level browser
- L210 _public member_ `TSharedPtr< FUICommandInfo > InvertLevelSelection;` — Inverts the level selection within the level browser
- L214 _public member_ `TSharedPtr< FUICommandInfo > SCCCheckOut;` — Check-Out selected levels from the SCC
- L217 _public member_ `TSharedPtr< FUICommandInfo > SCCCheckIn;` — Check-In selected levels from the SCC
- L220 _public member_ `TSharedPtr< FUICommandInfo > SCCOpenForAdd;` — Add selected levels to the SCC
- L223 _public member_ `TSharedPtr< FUICommandInfo > SCCHistory;` — Open a window to display the SCC history of the selected levels
- L226 _public member_ `TSharedPtr< FUICommandInfo > SCCRefresh;` — Refresh the status of selected levels in SCC
- L229 _public member_ `TSharedPtr< FUICommandInfo > SCCDiffAgainstDepot;` — Diff selected levels against the version in the SCC depot
- L232 _public member_ `TSharedPtr< FUICommandInfo > SCCConnect;` — Enable source control features
- L236 _public member_ `TSharedPtr< FUICommandInfo > SetAddStreamingMethod_Blueprint;` — Sets the streaming method for new or added levels to Blueprint streaming
- L239 _public member_ `TSharedPtr< FUICommandInfo > SetAddStreamingMethod_AlwaysLoaded;` — Sets the streaming method for new or added levels to be always loaded
- L243 _public member_ `TSharedPtr< FUICommandInfo > SetStreamingMethod_Blueprint;` — Changes the streaming method for the selected levels to Blueprint streaming
- L246 _public member_ `TSharedPtr< FUICommandInfo > SetStreamingMethod_AlwaysLoaded;` — Changes the streaming method for the selected levels to be always loaded
- L248 _public member_ `TSharedPtr< FUICommandInfo > SetLightingScenario_Enabled;`
- L249 _public member_ `TSharedPtr< FUICommandInfo > SetLightingScenario_Disabled;`
- L252 _public member_ `TSharedPtr< FUICommandInfo > AssignLevelToLayer;` — Assign selected levels to current layer
- L256 _public member_ `TSharedPtr< FUICommandInfo > AddsActors;` — Selects the actors in the selected Levels
- L259 _public member_ `TSharedPtr< FUICommandInfo > RemovesActors;` — Deselects the actors in the selected Levels
- L262 _public member_ `TSharedPtr< FUICommandInfo > ConvertLevelToExternalActors;` — Activate `Use External Actors` on the level and convert actors to external packaging.
- L265 _public member_ `TSharedPtr< FUICommandInfo > ConvertLevelToInternalActors;` — Disable `Use External Actors` on the level and convert actors to internal packaging.
- L268 _public member_ `TSharedPtr< FUICommandInfo > MoveActorsToSelected;` — Moves the selected actors to the selected level
- L271 _public member_ `TSharedPtr< FUICommandInfo > MoveFoliageToSelected;` — Moves the selected foliage instances to the selected level
- L274 _public member_ `TSharedPtr< FUICommandInfo > SelectStreamingVolumes;` — Selects the streaming volumes associated with the selected levels
- L277 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInEditorSelectedLevels;` — Makes selected Levels visible
- L280 _public member_ `TSharedPtr< FUICommandInfo > World_HideInEditorSelectedLevels;` — Makes selected Levels invisible
- L283 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInEditorOnlySelectedLevels;` — Makes selected Levels visible; makes all others invisible
- L286 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInEditorAllButSelectedLevels;` — Makes selected Levels invisible; makes all others visible
- L289 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInEditorAllLevels;` — Makes all Levels visible
- L292 _public member_ `TSharedPtr< FUICommandInfo > World_HideInEditorAllLevels;` — Makes all Levels invisible
- L296 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInGameSelectedLevels;` — Makes selected Levels visible in the editor
- L299 _public member_ `TSharedPtr< FUICommandInfo > World_HideInGameSelectedLevels;` — Makes selected Levels invisible in the editor
- L302 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInGameOnlySelectedLevels;` — Makes selected Levels visible; makes all others invisible in the editor
- L305 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInGameAllButSelectedLevels;` — Makes selected Levels invisible; makes all others visible in the editor
- L308 _public member_ `TSharedPtr< FUICommandInfo > World_ShowInGameAllLevels;` — Makes all Levels visible in the editor
- L311 _public member_ `TSharedPtr< FUICommandInfo > World_HideInGameAllLevels;` — Makes all Levels invisible in the editor
- L315 _public member_ `TSharedPtr< FUICommandInfo > World_LockSelectedLevels;` — Locks selected levels
- L318 _public member_ `TSharedPtr< FUICommandInfo > World_UnlockSelectedLevels;` — Unlocks selected levels
- L321 _public member_ `TSharedPtr< FUICommandInfo > World_LockAllLevels;` — Locks all levels
- L324 _public member_ `TSharedPtr< FUICommandInfo > World_UnlockAllLevels;` — Unlocks selected levels
- L327 _public member_ `TSharedPtr< FUICommandInfo > World_LockOnlySelectedLevels;` — Makes selected Levels locked; makes all others unlocked
- L330 _public member_ `TSharedPtr< FUICommandInfo > World_LockAllButSelectedLevels;` — Makes selected Levels unlocked; makes all others locked
- L333 _public member_ `TSharedPtr< FUICommandInfo > World_LockReadOnlyLevels;` — Locks all read-only levels
- L336 _public member_ `TSharedPtr< FUICommandInfo > World_UnlockReadOnlyLevels;` — Unlocks all read-only levels
- L340 _public member_ `TSharedPtr< FUICommandInfo > FitToSelection;` — Fits view to selected levels
- L343 _public member_ `TSharedPtr< FUICommandInfo > ExpandSelectedItems;` — Expand all descendants in selected tree items
- L347 _public member_ `TSharedPtr< FUICommandInfo > ClearParentLink;` — Clear link to parents for selected levels
- L351 _public member_ `TSharedPtr< FUICommandInfo > MoveLevelLeft;` — Move levels
- L352 _public member_ `TSharedPtr< FUICommandInfo > MoveLevelRight;`
- L353 _public member_ `TSharedPtr< FUICommandInfo > MoveLevelUp;`
- L354 _public member_ `TSharedPtr< FUICommandInfo > MoveLevelDown;`
- L356 _public member_ `TSharedPtr< FUICommandInfo > LockTilesLocation;`
- L359 _public member_ `TSharedPtr< FUICommandInfo > ImportTiledLandscape;` — Landscape operations
- L361 _public member_ `TSharedPtr< FUICommandInfo > AddLandscapeLevelXNegative;`
- L362 _public member_ `TSharedPtr< FUICommandInfo > AddLandscapeLevelXPositive;`
- L363 _public member_ `TSharedPtr< FUICommandInfo > AddLandscapeLevelYNegative;`
- L364 _public member_ `TSharedPtr< FUICommandInfo > AddLandscapeLevelYPositive;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "LevelCollectionCommands"`

### `Source/Editor/WorldBrowser/Private/LevelCollectionModel.h` (Private)


#### enum `EBuildHierarchyMenuFlags`  
`enum class EBuildHierarchyMenuFlags`  
_L26-30_
- L28 _public enumerator_ `None`
- L29 _public enumerator_ `ShowGameVisibility = 1 << 0`

#### class `FLevelCollectionModel`  
`class FLevelCollectionModel : public TSharedFromThis<FLevelCollectionModel> , public FTickableEditorObject`  
_L34-653_
- inherits: `TSharedFromThis<FLevelCollectionModel>,FTickableEditorObject`
- desc: Interface for non-UI presentation logic for a world.
- L40 _public prototype_ `DECLARE_EVENT_OneParam( FLevelCollectionModel, FOnNewItemAdded, TSharedPtr<FLevelModel>);`
- L41 _public prototype_ `DECLARE_EVENT( FLevelCollectionModel, FSimpleEvent );`
- L43 _public prototype_ `FLevelCollectionModel();`
- L47 _public prototype_ `virtual void Tick( float DeltaTime ) override;` — FTickableEditorObject interface
- L48 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L49 _public prototype_ `virtual TStatId GetStatId() const override;`
- L53 _public prototype_ `bool IsReadOnly() const;` — @return	Whether level collection is read only now
- L56 _public prototype_ `bool IsSimulating() const;` — @return	Whether level collection is in PIE/SIE mode
- L59 _public prototype_ `UWorld* GetSimulationWorld() const;` — @return	Current simulation world
- L62 _public function_ `UWorld* GetWorld(bool bEvenIfPendingKill = false) const` — @return	Current editor world
- L65 _public prototype_ `bool IsOriginRebasingEnabled() const;` — @return	Whether current world has world origin rebasing enabled
- L68 _public function_ `FIntPoint GetWorldSize() const` — Current world size
- L71 _public prototype_ `FLevelModelList& GetRootLevelList();` — @return	Root list of levels in hierarchy
- L74 _public prototype_ `const FLevelModelList& GetAllLevels() const;` — @return	All level list managed by this level collection
- L77 _public prototype_ `const FLevelModelList& GetFilteredLevels() const;` — @return	List of filtered levels
- L80 _public prototype_ `const FLevelModelList& GetSelectedLevels() const;` — @return	Currently selected level list
- L83 _public prototype_ `void AddFilter(const TSharedRef<LevelFilter>& InFilter);` — Adds a filter which restricts the Levels shown in UI
- L86 _public prototype_ `void RemoveFilter(const TSharedRef<LevelFilter>& InFilter);` — Removes a filter which restricted the Levels shown in UI
- L89 _public prototype_ `bool IsFilterActive() const;` — @return	Whether level filtering is active now
- L92 _public prototype_ `void IterateHierarchy(FLevelModelVisitor& Visitor);` — Iterates through level hierarchy with given Visitor
- L95 _public prototype_ `void SetSelectedLevels(const FLevelModelList& InList);` — Sets selected level list
- L98 _public prototype_ `void SetSelectedLevelsFromWorld();` — Sets selection to a levels that is currently marked as selected in UWorld
- L101 _public prototype_ `TSharedPtr<FLevelModel> FindLevelModel(ULevel* InLevel) const;` — @return	Found level model which represents specified level object
- L104 _public prototype_ `TSharedPtr<FLevelModel> FindLevelModel(const FName& PackageName) const;` — @return	Found level model with specified level package name
- L107 _public prototype_ `void HideLevelsInEditor(const FLevelModelList& InLevelList);` — Hides level in editor worlds
- L110 _public prototype_ `void ShowLevelsInEditor(const FLevelModelList& InLevelList);` — Shows level in editor worlds
- L113 _public prototype_ `void ShowInEditorOnlySelectedLevels();` — Toggles the selected levels to a visible state; toggles all other levels to an invisible state
- L116 _public prototype_ `void ShowInEditorAllButSelectedLevels();` — Toggles the selected levels to an invisible state; toggles all other levels to a visible state
- L119 _public prototype_ `void HideLevelsInGame(const FLevelModelList& InLevelList);` — Hides level in game worlds
- L122 _public prototype_ `void ShowLevelsInGame(const FLevelModelList& InLevelList);` — Shows level in game worlds
- L125 _public prototype_ `void ShowInGameOnlySelectedLevels();` — Toggles the selected levels to a visible state for game worlds; toggles all other levels to an invisible state
- L128 _public prototype_ `void ShowInGameAllButSelectedLevels();` — Toggles the selected levels to an invisible state for game worlds; toggles all other levels to a visible state
- L131 _public prototype_ `void UnlockLevels(const FLevelModelList& InLevelList);` — Unlocks level in the world
- L133 _public prototype_ `void LockLevels(const FLevelModelList& InLevelList);` — Locks level in the world
- L136 _public prototype_ `void LockOnlySelectedLevels();` — Toggles the selected levels to a locked state; toggles all other levels to an unlocked state
- L139 _public prototype_ `void LockAllButSelectedLevels();` — Toggles the selected levels to an unlocked state; toggles all other levels to a locked state
- L142 _public prototype_ `void SaveLevels(const FLevelModelList& InLevelList);` — Saves level to disk
- L145 _public prototype_ `void LoadLevels(const FLevelModelList& InLevelList);` — Loads level from disk
- L147 _public prototype_ `virtual void UnloadLevels(const FLevelModelList& InLevelList);` — Unloads levels from the editor
- L150 _public prototype_ `virtual void TranslateLevels(const FLevelModelList& InLevelList, FVector2D InAbsoluteDelta, bool bSnapDelta = true);` — Translate levels by specified delta
- L153 _public prototype_ `virtual FVector2D SnapTranslationDelta(const FLevelModelList& InLevelList, FVector2D InAbsoluteDelta, bool bBoundsSnapping, FVector2D::FReal SnappingValue);` — Snaps translation delta
- L156 _public prototype_ `virtual void UpdateTranslationDelta(const FLevelModelList& InLevelList, FVector2D InTranslationDelta, bool bBoundsSnapping, FVector2D::FReal SnappingValue);` — Updates current translation delta, when user drags levels on minimap
- L159 _public prototype_ `void AssignParent(const FLevelModelList& InLevels, TSharedPtr<FLevelModel> InParent);` — Attach levels as children to specified level
- L162 _public prototype_ `virtual void AddExistingLevelsFromAssetData(const TArray<struct FAssetData>& WorldList);` — Adds all levels in worlds represented by the supplied world list as sublevels
- L165 _public prototype_ `virtual TSharedPtr<WorldHierarchy::FWorldBrowserDragDropOp> CreateDragDropOp() const;` — Create drag drop operation for a selected level models
- L168 _public prototype_ `virtual TSharedPtr<WorldHierarchy::FWorldBrowserDragDropOp> CreateDragDropOp(const FLevelModelList& InLevels) const;` — Create a drag and drop operation for the specified level models
- L171 _public prototype_ `virtual bool PassesAllFilters(const FLevelModel& InLevelModel) const;` — @return	Whether specified level passes all filters
- L174 _public prototype_ `virtual void BuildHierarchyMenu(FMenuBuilder& InMenuBuilder, EBuildHierarchyMenuFlags Flags) const;` — Builds 'hierarchy' commands menu for a selected levels
- L177 _public prototype_ `virtual void CustomizeFileMainMenu(FMenuBuilder& InMenuBuilder) const;` — Customize 'File' section in main menu
- L180 _public prototype_ `virtual bool GetPlayerView(FVector& Location, FRotator& Rotation) const;` — @return	Player view in the PIE/Simulation world
- L183 _public prototype_ `virtual bool GetObserverView(FVector& Location, FRotator& Rotation) const;` — @return	Observer view in the Editor/Similuation world
- L186 _public prototype_ `virtual bool CompareLevelsZOrder(TSharedPtr<FLevelModel> InA, TSharedPtr<FLevelModel> InB) const;` — Compares 2 levels by Z order
- L189 _public prototype_ `virtual void RegisterDetailsCustomization(class FPropertyEditorModule& PropertyModule, TSharedPtr<class IDetailsView> InDetailsView);` — Registers level details customizations
- L192 _public prototype_ `virtual void UnregisterDetailsCustomization(class FPropertyEditorModule& PropertyModule, TSharedPtr<class IDetailsView> InDetailsView);` — Unregisters level details customizations
- L195 _public function_ `virtual bool IsTileWorld() const` — @return	Whether this level collection model is a tile world
- L198 _public function_ `virtual bool HasFolderSupport() const` — Returns true if this collection model will support folders
- L201 _public prototype_ `void PopulateLevelsList();` — Rebuilds levels collection
- L204 _public prototype_ `void PopulateFilteredLevelsList();` — Rebuilds the list of filtered Levels
- L207 _public prototype_ `void RequestUpdateAllLevels();` — Request to update levels cached information
- L210 _public prototype_ `void RequestRedrawAllLevels();` — Request to redraw all levels
- L213 _public prototype_ `void UpdateAllLevels();` — Updates all levels cached information
- L216 _public prototype_ `void RedrawAllLevels();` — Redraws all levels
- L219 _public prototype_ `void UpdateLevelActorsCount();` — Updates level actor count for all levels
- L222 _public prototype_ `bool IsOneLevelSelected() const;` — @return	whether exactly one level is selected
- L225 _public prototype_ `bool AreAnyLevelsSelected() const;` — @return	whether at least one level is selected
- L228 _public prototype_ `bool AreAllSelectedLevelsUserManaged() const;` — @return wether all selected levels are user managed
- L231 _public prototype_ `bool AreAllSelectedLevelsLoaded() const;` — @return whether all the currently selected levels are loaded
- L234 _public prototype_ `bool AreAnySelectedLevelsLoaded() const;` — @return whether any of the currently selected levels is loaded
- L237 _public prototype_ `bool AreAllSelectedLevelsUnloaded() const;` — @return whether all the currently selected levels are unloaded
- L240 _public prototype_ `bool AreAnySelectedLevelsUnloaded() const;` — @return whether any of the currently selected levels is unloaded
- L243 _public prototype_ `bool AreAllSelectedLevelsEditable() const;` — @return whether all the currently selected levels are editable
- L246 _public prototype_ `bool AreAllSelectedLevelsEditableAndNotPersistent() const;` — @return whether all the currently selected levels are editable and not persistent
- L249 _public prototype_ `bool AreAllSelectedLevelsEditableAndVisible() const;` — @return whether all the currently selected levels are editable and visible
- L252 _public prototype_ `bool AreAnySelectedLevelsEditable() const;` — @return whether any of the currently selected levels is editable
- L255 _public prototype_ `bool AreAnySelectedLevelsEditableAndVisible() const;` — @return whether any of the currently selected levels is editable and visible
- L258 _public prototype_ `bool CanExecuteGameVisibilityCommandsForSelectedLevels() const;` — @return Whether game visibility of the selected levels is allowed to be changed.
- L261 _public prototype_ `bool CanExecuteGameVisibilityCommands() const;` — @return Whether game visibility of levels is allowed to be changed.
- L264 _public prototype_ `bool IsSelectedLevelEditable() const;` — @return whether currently only one level selected and it is editable
- L267 _public prototype_ `bool IsNewLightingScenarioState(bool bExistingState) const;` — @return whether currently only one level selected and a lighting scenario
- L269 _public prototype_ `void SetIsLightingScenario(bool bNewLightingScenario);`
- L272 _public prototype_ `bool AreAnySelectedLevelsDirty() const;` — @return whether any of the currently selected levels is dirty
- L275 _public prototype_ `bool AreActorsSelected() const;` — @return	whether at least one actor is selected
- L278 _public prototype_ `bool CanConvertAnyLevelToExternalActors(bool bExternal) const;` — @return whether any of the currently selected levels can be converted to the specified actor bExternal packaging
- L281 _public prototype_ `bool IsValidMoveActorsToLevel() const;` — @return whether moving the selected actors to the selected level is a valid action
- L284 _public prototype_ `bool IsValidMoveFoliageToLevel() const;` — @return whether moving the selected foliage to the selected level is a valid action
- L287 _public prototype_ `void OnActorSelectionChanged(UObject* obj);` — delegate used to pickup when the selection has changed
- L290 _public prototype_ `void OnActorOrLevelSelectionChanged();` — Sets a flag to re-cache whether the selected actors move to the selected level is valid
- L293 _public prototype_ `bool GetDisplayPathsState() const;` — @return	whether 'display paths' is enabled
- L296 _public prototype_ `void SetDisplayPathsState(bool bDisplayPaths);` — Sets 'display paths', whether to show long package name in level display name
- L299 _public prototype_ `bool GetDisplayActorsCountState() const;` — @return	whether 'display actors count' is enabled
- L302 _public prototype_ `void SetDisplayActorsCountState(bool bDisplayActorsCount);` — Sets 'display actors count', whether to show actors count next to level name
- L305 _public member_ `FSimpleEvent SelectionChanged;` — Broadcasts whenever items selection has changed
- L306 _public prototype_ `void BroadcastSelectionChanged();`
- L309 _public member_ `FSimpleEvent CollectionChanged;` — Broadcasts whenever items collection has changed
- L310 _public prototype_ `void BroadcastCollectionChanged();`
- L313 _public member_ `FSimpleEvent HierarchyChanged;` — Broadcasts whenever items hierarchy has changed
- L314 _public prototype_ `void BroadcastHierarchyChanged();`
- L317 _public member_ `FSimpleEvent PreLevelsUnloaded;` — Broadcasts before levels are unloaded
- L318 _public prototype_ `void BroadcastPreLevelsUnloaded();`
- L321 _public member_ `FSimpleEvent PostLevelsUnloaded;` — Broadcasts after levels are unloaded
- L322 _public prototype_ `void BroadcastPostLevelsUnloaded();`
- L325 _public prototype_ `static double EditableAxisLength();` — Editable world axis length
- L328 _public prototype_ `static FBox EditableWorldArea();` — Editable world bounds
- L331 _public prototype_ `static void SCCCheckOut(const FLevelModelList& InList);`
- L332 _public prototype_ `static void SCCCheckIn(const FLevelModelList& InList);`
- L333 _public prototype_ `static void SCCOpenForAdd(const FLevelModelList& InList);`
- L334 _public prototype_ `static void SCCHistory(const FLevelModelList& InList);`
- L335 _public prototype_ `static void SCCRefresh(const FLevelModelList& InList);`
- L336 _public prototype_ `static void SCCDiffAgainstDepot(const FLevelModelList& InList, UEditorEngine* InEditor);`
- L339 _public prototype_ `static TArray<FName> GetPackageNamesList(const FLevelModelList& InList);` — @return	List of valid level package names from a specified level model list
- L342 _public prototype_ `static TArray<FString> GetFilenamesList(const FLevelModelList& InList);` — @return	List of valid level package filenames from a specified level model list
- L345 _public prototype_ `static TArray<UPackage*> GetPackagesList(const FLevelModelList& InList);` — @return	List of valid packages from a specified level model list
- L348 _public prototype_ `static TArray<ULevel*> GetLevelObjectList(const FLevelModelList& InList);` — @return	List of valid level objects from a specified level model list
- L351 _public prototype_ `static FLevelModelList GetLoadedLevels(const FLevelModelList& InList);` — @return	List of loaded level models from a specified level model list
- L354 _public prototype_ `static FLevelModelList GetLevelsHierarchy(const FLevelModelList& InList);` — @return	List of all level models found while traversing hierarchy of specified level models
- L357 _public prototype_ `static FBox GetLevelsBoundingBox(const FLevelModelList& InList, bool bIncludeChildren);` — @return	Total bounding box of specified level models
- L360 _public prototype_ `static FBox GetVisibleLevelsBoundingBox(const FLevelModelList& InList, bool bIncludeChildren);` — @return	Total bounding box of specified visible level models
- L363 _public prototype_ `const TSharedRef<FUICommandList> GetCommandList() const;` — @return	The UICommandList supported by this collection
- L366 _public prototype_ `void LoadSettings();`
- L369 _public prototype_ `void SaveSettings();`
- L373 _protected prototype_ `void RefreshBrowser_Executed();` — Refreshes current cached data
- L376 _protected prototype_ `void LoadSelectedLevels_Executed();` — Load selected levels to the world
- L379 _protected prototype_ `void UnloadSelectedLevels_Executed();` — Unload selected level from the world
- L382 _protected prototype_ `void MakeLevelCurrent_Executed();` — Make this Level the Current Level
- L385 _protected prototype_ `void FindInContentBrowser_Executed();` — Find selected levels in Content Browser
- L388 _protected prototype_ `bool IsValidFindInContentBrowser();` — Is FindInContentBrowser a valid action
- L391 _protected prototype_ `void MoveActorsToSelected_Executed();` — Moves the selected actors to this level
- L394 _protected prototype_ `void MoveFoliageToSelected_Executed();` — Moves the selected foliage to this level
- L397 _protected prototype_ `void SaveSelectedLevels_Executed();` — Saves selected levels
- L400 _protected prototype_ `void SaveSelectedLevelAs_Executed();` — Saves selected level under new name
- L403 _protected prototype_ `void MigrateSelectedLevels_Executed();` — Migrate selected levels
- L406 _protected prototype_ `void ExpandSelectedItems_Executed();` — Expand selected items hierarchy
- L409 _protected prototype_ `void OnSCCCheckOut();` — Check-Out selected levels from SCC
- L412 _protected prototype_ `void OnSCCOpenForAdd();` — Mark for Add selected levels from SCC
- L415 _protected prototype_ `void OnSCCCheckIn();` — Check-In selected levels from SCC
- L418 _protected prototype_ `void OnSCCHistory();` — Shows the SCC History of selected levels
- L421 _protected prototype_ `void OnSCCRefresh();` — Refreshes the states selected levels from SCC
- L424 _protected prototype_ `void OnSCCDiffAgainstDepot();` — Diffs selected levels from with those in the SCC depot
- L427 _protected prototype_ `void OnSCCConnect() const;` — Enable source control features
- L430 _protected prototype_ `void SelectAllLevels_Executed();` — Selects all levels in the collection view model
- L433 _protected prototype_ `void DeselectAllLevels_Executed();` — De-selects all levels in the collection view model
- L436 _protected prototype_ `void InvertSelection_Executed();` — Inverts level selection in the collection view model
- L439 _protected prototype_ `void SelectActors_Executed();` — Adds the Actors in the selected Levels from the viewport's existing selection
- L442 _protected prototype_ `void DeselectActors_Executed();` — Removes the Actors in the selected Levels from the viewport's existing selection
- L445 _protected prototype_ `void ConvertLevelToExternalActors_Executed(bool bExternal);` — Set level `Use External Actors` to bExternal
- L448 _protected prototype_ `void ShowInEditorSelectedLevels_Executed();` — Toggles selected levels to a visible state in the viewports for editor worlds
- L451 _protected prototype_ `void HideInEditorSelectedLevels_Executed();` — Toggles selected levels to an invisible state in the viewports for editor worlds
- L454 _protected prototype_ `void ShowInEditorOnlySelectedLevels_Executed();` — Toggles the selected levels to a visible state for editor worlds; toggles all other levels to an invisible state.
- L457 _protected prototype_ `void ShowInEditorAllButSelectedLevels_Executed();` — Toggles the selected levels to an invisible state for editor worlds; toggles all other levels to a visible state.
- L460 _protected prototype_ `void ShowInEditorAllLevels_Executed();` — Toggles all levels to a visible state in the viewports for editor worlds
- L463 _protected prototype_ `void HideInEditorAllLevels_Executed();` — Hides all levels to an invisible state in the viewports for editor worlds
- L466 _protected prototype_ `void ShowInGameSelectedLevels_Executed();` — Toggles selected levels to a visible state in the viewports for game worlds
- L469 _protected prototype_ `void HideInGameSelectedLevels_Executed();` — Toggles selected levels to an invisible state in the viewports
- L472 _protected prototype_ `void ShowInGameOnlySelectedLevels_Executed();` — Toggles the selected levels to a visible state for game worlds; toggles all other levels to an invisible state.
- L475 _protected prototype_ `void ShowInGameAllButSelectedLevels_Executed();` — Toggles the selected levels to an invisible state for game worlds; toggles all other levels to a visible state.
- L478 _protected prototype_ `void ShowInGameAllLevels_Executed();` — Toggles all levels to a visible state in the viewports for game worlds
- L481 _protected prototype_ `void HideInGameAllLevels_Executed();` — Hides all levels to an invisible state in the viewports for game worlds
- L484 _protected prototype_ `void LockSelectedLevels_Executed();` — Locks selected levels
- L487 _protected prototype_ `void UnlockSelectedLevels_Executed();` — Unlocks selected levels
- L490 _protected prototype_ `void LockOnlySelectedLevels_Executed();` — Toggles the selected levels to a locked state; toggles all other levels to an unlocked state
- L493 _protected prototype_ `void LockAllButSelectedLevels_Executed();` — Toggles the selected levels to an unlocked state; toggles all other levels to a locked state
- L496 _protected prototype_ `void LockAllLevels_Executed();` — Locks all levels
- L499 _protected prototype_ `void UnlockAllLevels_Executed();` — Unlocks all levels
- L502 _protected prototype_ `void ToggleReadOnlyLevels_Executed();` — Toggle all read-only levels
- L505 _protected function_ `bool CanExecuteSCCCheckOut() const` — true if the SCC Check-Out option is available
- L511 _protected function_ `bool CanExecuteSCCCheckIn() const` — true if the SCC Check-In option is available
- L517 _protected function_ `bool CanExecuteSCCOpenForAdd() const` — true if the SCC Mark for Add option is available
- L523 _protected function_ `bool CanExecuteSCC() const` — true if Source Control options are generally available.
- L529 _protected prototype_ `void FillLockSubMenu(FMenuBuilder& MenuBuilder);` — Fills MenuBulder with Lock level related commands
- L532 _protected prototype_ `void FillEditorVisibilitySubMenu(FMenuBuilder& MenuBuilder);` — Fills MenuBulder with level visisbility related commands
- L535 _protected prototype_ `void FillGameVisibilitySubMenu(FMenuBuilder& MenuBuilder);` — Fills MenuBulder with level visisbility related commands
- L538 _protected prototype_ `void FillSourceControlSubMenu(FMenuBuilder& MenuBuilder);` — Fills MenuBulder with SCC related commands
- L542 _protected prototype_ `virtual void Initialize(UWorld* InWorld);`
- L545 _protected prototype_ `virtual void BindCommands();`
- L548 _protected prototype_ `void DeselectActorsInAllReadOnlyLevel(const FLevelModelList& InLevelList);` — Removes the Actors in all read-only Levels from the viewport's existing selection
- L551 _protected prototype_ `void DeselectSurfaceInAllReadOnlyLevel(const FLevelModelList& InLevelList);` — Removes the Actors in all read-only Levels from the viewport's existing selection
- L554 _protected prototype_ `virtual void OnLevelsCollectionChanged();` — Called whenever level collection has been changed
- L557 _protected prototype_ `virtual void OnLevelsSelectionChanged();` — Called whenever level selection has been changed
- L560 _protected prototype_ `void OnLevelsSelectionChangedOutside();` — Called whenever level selection has been changed outside of this module, usually via World->SetSelectedLevels
- L563 _protected prototype_ `virtual void OnLevelsHierarchyChanged();` — Called whenever level collection hierarchy has been changed
- L566 _protected function_ `virtual void OnPreLoadLevels(const FLevelModelList& InList)` — Called before loading specified level models into editor
- L569 _protected function_ `virtual void OnPreShowLevels(const FLevelModelList& InList)` — Called before making visible specified level models
- L572 _protected prototype_ `void OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld);` — Called when level was added to the world
- L575 _protected prototype_ `void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);` — Called when level was removed from the world
- L578 _protected prototype_ `void OnRedrawAllViewports();` — Handler for FEditorSupportDelegates::RedrawAllViewports event
- L581 _protected prototype_ `void OnLevelActorAdded(AActor* InActor);` — Handler for when an actor was added to a level
- L584 _protected prototype_ `void OnLevelActorDeleted(AActor* InActor);` — Handler for when an actor was removed from a level
- L587 _protected prototype_ `void OnFilterChanged();` — Handler for level filter collection changes
- L590 _protected prototype_ `void CacheCanExecuteSourceControlVars() const;` — Caches the variables for which SCC menu options are available
- L595 _protected member_ `TWeakObjectPtr<UWorld> CurrentWorld;` — The editor world from where we pull our data
- L598 _protected member_ `bool bRequestedUpdateAllLevels;` — Has request to update all levels cached
- L601 _protected member_ `bool bRequestedRedrawAllLevels;` — Has request to redraw all levels
- L604 _protected member_ `bool bRequestedUpdateActorsCount;` — Has request to update actors count for all levels
- L607 _protected member_ `const TSharedRef<FUICommandList> CommandList;` — The list of commands with bound delegates for the Level collection
- L610 _protected member_ `const TSharedRef<LevelFilterCollection> Filters;` — The collection of filters used to restrict the Levels shown in UI
- L613 _protected member_ `FLevelModelList RootLevelsList;` — Levels in the root of hierarchy, persistent levels
- L616 _protected member_ `FLevelModelList AllLevelsList;` — All levels found in the world
- L619 _protected member_ `TMap<FName, TSharedPtr<FLevelModel>> AllLevelsMap;` — All levels in a map<PackageName, LevelModel>
- L622 _protected member_ `FLevelModelList FilteredLevelsList;` — Filtered levels from AllLevels list
- L625 _protected member_ `FLevelModelList SelectedLevelsList;` — Currently selected levels
- L628 _protected member_ `FIntPoint WorldSize;` — Cached value of world size (sum of levels size)
- L631 _protected member_ `bool bDisplayPaths;` — Whether we should show long package names in level display names
- L634 _protected member_ `bool bDisplayActorsCount;` — Whether we should show actors count next to level name
- L637 _protected member_ `mutable bool bCanExecuteSCCCheckOut;` — true if the SCC Check-Out option is available
- L640 _protected member_ `mutable bool bCanExecuteSCCOpenForAdd;` — true if the SCC Check-In option is available
- L643 _protected member_ `mutable bool bCanExecuteSCCCheckIn;` — true if the SCC Mark for Add option is available
- L646 _protected member_ `mutable bool bCanExecuteSCC;` — true if Source Control options are generally available.
- L649 _protected member_ `mutable bool bSelectionHasChanged;` — Flag for whether the selection of levels or actors has changed
- L652 _protected member_ `bool bUpdatingLevelsSelection;` — Guard to avoid recursive level selection updates

#### struct `FUnmodifiableObject`  
`struct FUnmodifiableObject`  
_L658-681_
- desc: Helper struct to temporally make specified UObject immune to dirtying
- L660 _public function_ `FUnmodifiableObject(UObject* InObject) : ImmuneObject(InObject) , bTransient(InObject->HasAnyFlags(RF_Transient))`
- L670 _public function_ `~FUnmodifiableObject()`
- L679 _private member_ `UObject* ImmuneObject;`
- L680 _private member_ `bool bTransient;`

#### struct `FTiledLandscapeImportSettings`  
`struct FTiledLandscapeImportSettings`  
_L684-723_
- L686 _public function_ `FTiledLandscapeImportSettings() : Scale3D(100.f,100.f,100.f) , ComponentsNum(8) , QuadsPerSection(63) , SectionsPerComponent(1) , TilesCoordinatesOffset(0,0) , SizeX(1009) , bFlipYAxis(true)`
- L696 _public member_ `FVector Scale3D;`
- L697 _public member_ `int32 ComponentsNum;`
- L698 _public member_ `int32 QuadsPerSection;`
- L699 _public member_ `int32 SectionsPerComponent;`
- L701 _public member_ `TArray<FString> HeightmapFileList;`
- L702 _public member_ `TArray<FIntPoint> TileCoordinates;`
- L703 _public member_ `FIntPoint TilesCoordinatesOffset;`
- L704 _public member_ `int32 SizeX;`
- L705 _public member_ `bool bFlipYAxis;`
- L708 _public member_ `TWeakObjectPtr<UMaterialInterface> LandscapeMaterial;`
- L722 _public member_ `TArray<LandscapeLayerSettings> LandscapeLayerSettingsList;`

#### struct `FTiledLandscapeImportSettings::LandscapeLayerSettings`  
`struct LandscapeLayerSettings`  
_L711-720_
- desc: Landscape layers
- L713 _public function_ `LandscapeLayerSettings() : bNoBlendWeight(false)`
- L717 _public member_ `FName Name;`
- L718 _public member_ `bool bNoBlendWeight;`
- L719 _public member_ `TMap<FIntPoint, FString> WeightmapFiles;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API WORLDBROWSER_API`
- L23 _typedef_ `typedef IFilter< const FLevelModel* > LevelFilter;`
- L24 _typedef_ `typedef TFilterCollection< const FLevelModel* > LevelFilterCollection;`
- L31 _prototype_ `ENUM_CLASS_FLAGS(EBuildHierarchyMenuFlags);`
- L40 _delegate_ `DECLARE_EVENT_OneParam( FLevelCollectionModel, FOnNewItemAdded, TSharedPtr<FLevelModel>);`
- L41 _delegate_ `DECLARE_EVENT( FLevelCollectionModel, FSimpleEvent );`

### `Source/Editor/WorldBrowser/Private/LevelFolders.h` (Private)


#### struct `FLevelFolderProps`  
`struct FLevelFolderProps`  
_L31-44_
- reflection: `USTRUCT()`
- desc: Properties for level folders
- L35 _public function_ `FLevelFolderProps() : bExpanded(true)`
- L43 _public member_ `bool bExpanded;`

#### class `UEditorLevelFolders`  
`class UEditorLevelFolders : public UObject`  
_L49-57_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Level folder UObject, for supporting undo/redo functionality
- L54 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L56 _public member_ `TMap<FName, FLevelFolderProps> Folders;`

#### struct `FLevelFolders`  
`struct FLevelFolders : public FGCObject`  
_L61-158_
- inherits: `FGCObject`
- desc: The class for managing in-memory representations of level folders in the editor
- L63 _public prototype_ `FLevelFolders();`
- L64 _public prototype_ `~FLevelFolders();`
- L69 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L70 _public function_ `virtual FString GetReferencerName() const`
- L78 _public function_ `static bool IsAvailable()` — Checks if the singleton is valid
- L81 _public prototype_ `static FLevelFolders& Get();` — Grants access to the singleton object if it's available
- L84 _public prototype_ `static void Init();` — Initialize the singleton
- L87 _public prototype_ `static void Cleanup();` — Clean up the singleton
- L91 _public member_ `static FOnLevelFolderCreate OnFolderCreate;` — Folder events
- L92 _public member_ `static FOnLevelFolderDelete OnFolderDelete;`
- L93 _public member_ `static FOnLevelFolderMove OnFolderMove;`
- L96 _public prototype_ `TMap<FName, FLevelFolderProps>& GetFolderProperties(TSharedRef<FLevelModel> LevelModel);` — Gets all folder properties for a specified level
- L99 _public prototype_ `FLevelFolderProps* GetFolderProperties(TSharedRef<FLevelModel> LevelModel, FName InPath);` — Gets the folder properties for a specified path within the level
- L102 _public prototype_ `FName GetDefaultFolderName(TSharedRef<FLevelModel> LevelModel, FName ParentPath);` — Gets the default folder name for the given path.
- L105 _public prototype_ `void CreateFolderContainingSelectedLevels(TSharedRef<FLevelCollectionModel> WorldModel, TSharedRef<FLevelModel> LevelModel, FName InPath);` — Creates a new folder with the given name for the current level selection
- L108 _public prototype_ `void CreateFolder(TSharedRef<FLevelModel> LevelModel, FName InPath);` — Creates a folder for the level model with the given path name
- L111 _public prototype_ `bool RenameFolder(TSharedRef<FLevelModel> LevelModel, FName OldPath, FName NewPath);` — Renames a folder. The folder with the old name is removed from the folder props
- L114 _public prototype_ `void DeleteFolder(TSharedRef<FLevelModel> LevelModel, FName FolderToDelete);` — Deletes a folder and all saved properties
- L117 _public prototype_ `void RebuildFolderList(TSharedRef<FLevelModel> LevelModel);` — Rebuilds the folder list for the level
- L120 _public prototype_ `void SaveLevel(TSharedRef<FLevelModel> LevelModel);` — Saves the level model when the world is saved
- L125 _private prototype_ `void SetSelectedLevelFolderPath(TSharedRef<FLevelCollectionModel> WorldModel, TSharedRef<FLevelModel> LevelModel, FName InPath) const;` — Sets the folder path for the current level selection
- L128 _private prototype_ `void Housekeeping();` — Remove references to folder arrays for unloaded levels
- L131 _private prototype_ `UEditorLevelFolders& InitializeForLevel(TSharedRef<FLevelModel> LevelModel);` — Create a folder container for the specified level model
- L134 _private prototype_ `bool PathIsChildOf(const FString& InPotentialChild, const FString& InParent);` — Checks if the supplied path is a descendant of the parent path
- L137 _private prototype_ `UEditorLevelFolders& GetOrCreateFoldersForLevel(TSharedRef<FLevelModel> LevelModel);` — Gets the folder information for the given level, or creates it if it's not in memory
- L140 _private prototype_ `UEditorLevelFolders& Initialize(TSharedRef<FLevelModel> LevelModel);` — Creates new folder information for the level
- L143 _private prototype_ `bool AddFolder(TSharedRef<FLevelModel> LevelModel, FName InPath);` — Adds a folder for the level without triggering any events
- L146 _private prototype_ `FLevelModelList GetSelectedLevels(TSharedRef<FLevelCollectionModel> WorldModel, TSharedRef<FLevelModel> LevelModel) const;` — Gets the selected levels in the world model
- L151 _private member_ `TMap<FLevelModelKey , TObjectPtr<UEditorLevelFolders>> TemporaryLevelFolders;` — Transient map of folders, keyed off level path name
- L154 _private member_ `TMap<FLevelModelKey, TWeakPtr<FLevelModel>> TemporaryModelObjects;` — Maps level paths to level model objects, to clear out unloaded level model information when necessary
- L157 _private member_ `static FLevelFolders* Singleton;` — Singleton object to be maintained by the world browser module

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API WORLDBROWSER_API`
- L17 _typedef_ `typedef FName FLevelModelKey;`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelFolderCreate, TSharedPtr<FLevelModel>, FName);` — Broadcasted when an editor-only folder has been created for a level
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelFolderCreate, TSharedPtr<FLevelModel>, FName);` — Broadcasted when an editor-only folder has been created for a level
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelFolderDelete, TSharedPtr<FLevelModel>, FName);` — Broadcasted when an editor-only folder for a level has been deleted
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelFolderDelete, TSharedPtr<FLevelModel>, FName);` — Broadcasted when an editor-only folder for a level has been deleted
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLevelFolderMove, TSharedPtr<FLevelModel>, FName , FName );` — Broadcasted when an editor-only folder for a level has moved
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLevelFolderMove, TSharedPtr<FLevelModel>, FName , FName );` — Broadcasted when an editor-only folder for a level has moved
- L38 _function_ `FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FLevelFolderProps& Folder)` — Serializer

### `Source/Editor/WorldBrowser/Private/LevelModel.h` (Private)


#### struct `FLevelModelVisitor`  
`struct FLevelModelVisitor`  
_L23-27_
- desc: Interface for level collection hierarchy traversal
- L25 _public prototype_ `virtual ~FLevelModelVisitor() = default;`
- L26 _public prototype_ `virtual void Visit(FLevelModel& Item) = 0;`

#### class `FLevelModel`  
`class FLevelModel : public TSharedFromThis<FLevelModel>`  
_L32-352_
- inherits: `TSharedFromThis<FLevelModel>`
- desc: Interface for non-UI presentation logic for a level in a world
- L36 _public typedef_ `typedef IFilter<const TWeakObjectPtr<AActor>&> ActorFilter;`
- L38 _public prototype_ `DECLARE_EVENT( FLevelModel, FSimpleEvent );`
- L41 _public prototype_ `FLevelModel(FLevelCollectionModel& InLevelCollectionModel);`
- L43 _public prototype_ `virtual ~FLevelModel();`
- L46 _public prototype_ `void Accept(FLevelModelVisitor& Vistor);` — Traverses level model hierarchy
- L49 _public prototype_ `void SetLevelSelectionFlag(bool bExpanded);` — Sets level selection flag
- L52 _public prototype_ `bool GetLevelSelectionFlag() const;` — @return Level selection flag
- L55 _public prototype_ `void SetLevelExpansionFlag(bool bExpanded);` — Sets level child hierarchy expansion flag
- L58 _public prototype_ `bool GetLevelExpansionFlag() const;` — @return Level child hierarchy expansion flag
- L61 _public prototype_ `void SetLevelFilteredOutFlag(bool bFiltredOut);` — Sets level filtered out flag
- L64 _public prototype_ `bool GetLevelFilteredOutFlag() const;` — @return Whether this level model was filtered out
- L67 _public prototype_ `FString GetDisplayName() const;` — @return	Level display name
- L70 _public prototype_ `FString GetPackageFileName() const;` — @return	Level package file name
- L73 _public function_ `virtual bool HasValidPackage() const` — @return	Whether level model has valid package file
- L76 _public prototype_ `virtual UObject* GetNodeObject() = 0;` — @return Pointer to UObject to be used as key in SNodePanel
- L79 _public prototype_ `virtual ULevel* GetLevelObject() const = 0;` — @return ULevel object if any
- L82 _public prototype_ `virtual FName GetAssetName() const = 0;` — @return	Level asset name
- L85 _public prototype_ `virtual FName GetLongPackageName() const = 0;` — @return	Level package file name
- L88 _public prototype_ `virtual void UpdateAsset(const FAssetData& AssetData) = 0;` — Update asset associated with level model
- L91 _public prototype_ `virtual void Update();` — Refreshes cached data
- L94 _public prototype_ `virtual void UpdateVisuals();` — Refreshes visual information
- L97 _public prototype_ `bool IsSimulating() const;` — @return	Whether level is in PIE/SIE mode
- L100 _public prototype_ `bool IsCurrent() const;` — @return Whether level is CurrentLevel
- L103 _public prototype_ `bool IsPersistent() const;` — @return Whether level is PersistentLevel
- L106 _public prototype_ `bool IsEditable() const;` — @return Whether level is editable
- L109 _public prototype_ `bool IsDirty() const;` — @return Whether level is dirty
- L112 _public prototype_ `bool IsLightingScenario() const;` — @return Whether level is a lighting scenario
- L114 _public prototype_ `void SetIsLightingScenario(bool bNew);`
- L117 _public prototype_ `bool IsLoaded() const;` — @return Whether level has loaded content
- L120 _public prototype_ `bool IsLoading() const;` — @return Whether level is in process of loading content
- L123 _public prototype_ `bool IsVisibleInEditor() const;` — @return Whether level is visible in editor worlds
- L126 _public prototype_ `bool IsVisibleInGame() const;` — @return Whether level is visible in game worlds
- L129 _public prototype_ `bool IsLocked() const;` — @return Whether level is locked
- L132 _public prototype_ `bool IsFileReadOnly() const;` — @return Whether level package file is read only
- L135 _public prototype_ `bool IsUserManaged() const;` — @return Whether this level can be add/removed/unloaded by user
- L138 _public function_ `virtual bool IsTransient() const` — @return Whether the streaming level object is transient
- L141 _public prototype_ `virtual void LoadLevel();` — Loads level into editor
- L144 _public prototype_ `virtual void SetVisibleInEditor(bool bVisible);` — Sets the Level's visibility
- L147 _public prototype_ `static void SetVisibleInEditor(TArray<FLevelModel*>& LevelModels, const TArray<bool>& bAreVisible);` — Static function analog to the non-static SetVisible but applied to an TArray of FLevelModel elements
- L149 _public prototype_ `static void SetVisibleInGame(TArray<FLevelModel*>& LevelModels, const TArray<bool>& bAreVisible);`
- L152 _public prototype_ `void SetLocked(bool bLocked);` — Sets the Level's locked/unlocked state
- L155 _public prototype_ `void MakeLevelCurrent();` — Sets Level as current in the world
- L158 _public prototype_ `virtual bool HitTest2D(const FVector2D& Point) const;` — @return Whether specified point is hovering level
- L161 _public prototype_ `virtual FVector2D GetLevelPosition2D() const;` — @return Level top left corner position
- L164 _public prototype_ `virtual FVector2D GetLevelSize2D() const;` — @return XY size of level
- L167 _public prototype_ `virtual FBox GetLevelBounds() const;` — @return Level bounding box
- L170 _public prototype_ `FVector2D GetLevelTranslationDelta() const;` — @return level translation delta, when user moving level item
- L173 _public prototype_ `void SetLevelTranslationDelta(FVector2D InAbsoluteDelta);` — Sets new translation delta to this model and all descendants
- L176 _public prototype_ `virtual FLinearColor GetLevelColor() const;` — @return level color, used for visualization. (Show -> Advanced -> Level Coloration)
- L179 _public prototype_ `virtual void SetLevelColor(FLinearColor InColor);` — Sets level color, used for visualization. (Show -> Advanced -> Level Coloration)
- L182 _public prototype_ `virtual bool IsVisibleInCompositionView() const;` — Whether level should be drawn in world composition view
- L185 _public prototype_ `bool HasKismet() const;` — @return Whether level has associated blueprint script
- L188 _public prototype_ `void OpenKismet();` — Opens level associated blueprint script
- L194 _public prototype_ `bool AttachTo(TSharedPtr<FLevelModel> InParent);` — Sets parent for this item @return false in case attaching has failed
- L197 _public prototype_ `void OnFilterChanged();` — Notifies level model that filters has been changed
- L200 _public prototype_ `const FLevelModelList& GetChildren() const;` — @return Level child hierarchy
- L203 _public prototype_ `TSharedPtr<FLevelModel> GetParent() const;` — @return Parent level model
- L206 _public prototype_ `void SetParent(TSharedPtr<FLevelModel>);` — Sets link to a parent model
- L209 _public prototype_ `void RemoveAllChildren();` — Removes all entries from children list
- L212 _public prototype_ `void RemoveChild(TSharedPtr<FLevelModel> InChild);` — Removes specific child
- L215 _public prototype_ `void AddChild(TSharedPtr<FLevelModel> InChild);` — Adds new entry to a children list
- L218 _public prototype_ `bool HasAncestor(const TSharedPtr<FLevelModel>& InLevel) const;` — @return Whether this model has in ancestors specified level model
- L221 _public prototype_ `bool HasDescendant(const TSharedPtr<FLevelModel>& InLevel) const;` — @return Whether this model has in descendants specified level model
- L224 _public function_ `virtual FName GetFolderPath() const` — Returns the folder path that the level should use when displayed in the world hierarchy
- L227 _public function_ `virtual void SetFolderPath(const FName& InFolderPath)` — Sets the folder path that the level should use when displayed in the world hierarchy
- L230 _public function_ `virtual bool HasFolderSupport() const` — Returns true if the level model can be added to hierarchy folders
- L233 _public prototype_ `virtual void OnDrop(const TSharedPtr<FLevelDragDropOp>& Op);` — @return Handles drop operation
- L236 _public prototype_ `virtual bool IsGoodToDrop(const TSharedPtr<FLevelDragDropOp>& Op) const;` — @return Whether it's possible to drop onto this level
- L239 _public prototype_ `virtual void OnLevelAddedToWorld(ULevel* InLevel);` — Notification when level was added(shown) to world
- L242 _public prototype_ `virtual void OnLevelRemovedFromWorld();` — Notification when level was removed(hidden) from world
- L245 _public function_ `virtual void OnParentChanged()` — Notification on level reparenting
- L248 _public prototype_ `void BroadcastLevelChanged();` — Event when level model has been changed
- L261 _public prototype_ `void UpdateSimulationStatus(ULevelStreaming* StreamingLevel);` — Updates this level simulation status
- L264 _public member_ `FSimpleEvent ChangedEvent;` — Broadcasts whenever level has changed
- L265 _public prototype_ `void BroadcastChangedEvent();`
- L268 _public prototype_ `void DeselectAllActors();` — Deselects all Actors in this level
- L271 _public prototype_ `void DeselectAllSurfaces();` — Deselects all BSP surfaces in this level
- L281 _public prototype_ `void SelectActors(bool bSelect, bool bNotify, bool bSelectEvenIfHidden, const TSharedPtr<ActorFilter>& Filter = TSharedPtr<ActorFilter>(NULL));` — Selects in the Editor all the Actors assigned to the Level, based on the specified conditions. @param	bSelect					if true actors will be selected; If false, actors will be deselected @param	bNotify					if true the editor will be notified of the selection change; If false, the editor will not @param	bSelectEvenIfHidden		if true actors that are hidden will be selected; If false, they will be skipped @param	Filter					Only actors which pass the filters restrictions will be selected
- L288 _public prototype_ `void ConvertLevelToExternalActors(bool bUseExternal);` — Set the level to use external actors and convert its actors to external packaging or vice versa @param bUseExternal Convert to external if `bUseExternal` is true, convert to internal otherwise
- L295 _public prototype_ `bool CanConvertLevelToExternalActors(bool bToExternal);` — Return if the level can be converted to the specified external packaging mode. @param bToExternal The packaging mode we want to convert to. (i.e true: external, false: internal) @return true if we can convert the level to the `bToExternal` packaging mode.
- L298 _public prototype_ `void UpdateLevelActorsCount();` — Updates cached value of level actors count
- L301 _public prototype_ `void UpdateDisplayName();` — Updates cached value of level display name
- L304 _public prototype_ `FString GetLightmassSizeString() const;` — @return the Level's Lightmass Size as a FString
- L307 _public prototype_ `FString GetFileSizeString() const;` — @return the Level's File Size as a FString
- L310 _public prototype_ `virtual UClass* GetStreamingClass() const;` — @return Class used for streaming this level
- L314 _protected prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString& OldObjectPath);` — Called when the map asset is renamed
- L318 _protected member_ `FString DisplayName;` — Level model display name
- L321 _protected member_ `FLevelCollectionModel& LevelCollectionModel;` — Reference to owning collection model
- L324 _protected member_ `TWeakPtr<FLevelModel> Parent;` — The parent level
- L327 _protected member_ `FLevelModelList FilteredChildren;` — Filtered children of this level
- L330 _protected member_ `FLevelModelList AllChildren;` — All children of this level
- L333 _protected member_ `FSimulationLevelStatus SimulationStatus;` — Level simulation status
- L336 _protected member_ `bool bSelected;` — Whether this level model is selected
- L339 _protected member_ `bool bExpanded;` — Whether this level model is expended in hierarchy view
- L342 _protected member_ `bool bLoadingLevel;` — Whether this level model is in a process of loading content
- L345 _protected member_ `bool bFilteredOut;` — Whether this level model does not pass filters
- L348 _protected member_ `FVector2D LevelTranslationDelta;` — Current translation delta
- L351 _protected member_ `int32 LevelActorsCount;` — Cached level actors count

#### struct `FLevelModel::FSimulationLevelStatus`  
`struct FSimulationLevelStatus`  
_L253-258_
- L255 _public member_ `bool bLoaded;`
- L256 _public member_ `bool bLoading;`
- L257 _public member_ `bool bVisible;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API WORLDBROWSER_API`
- L17 _typedef_ `typedef TArray<TSharedPtr<class FLevelModel>> FLevelModelList;`
- L38 _delegate_ `DECLARE_EVENT( FLevelModel, FSimpleEvent );`

### `Source/Editor/WorldBrowser/Private/SLevelsTreeWidget.h` (Private)


#### class `SLevelsTreeWidget`  
`class SLevelsTreeWidget : public STreeView<WorldHierarchy::FWorldTreeItemPtr>`  
_L21-43_
- inherits: `STreeView<WorldHierarchy::FWorldTreeItemPtr>`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FLevelCollectionModel>& InWorldModel, const TSharedPtr<SWorldHierarchyImpl>& InHierachy);`
- L26 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L28 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L30 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L34 _private prototype_ `bool GetWorldAssetsFromDrag(const FDragDropEvent& DragDropEvent, TArray<FAssetData>& OutWorldAssetList);` — Finds any world assets that are contained in the drag drop event and returns them in the supplied array. Returns true if a world asset was found
- L37 _private prototype_ `bool CanAttachAllItemsToRoot(const TArray<WorldHierarchy::FWorldTreeItemPtr>& Items) const;` — Checks to see if all selected items can be moved.
- L40 _private member_ `TSharedPtr<FLevelCollectionModel> WorldModel;`
- L42 _private member_ `TWeakPtr<SWorldHierarchyImpl> Hierarchy;`

### `Source/Editor/WorldBrowser/Private/SPropertyEditorLevelPackage.h` (Private)


#### struct `FLevelPackageItem`  
`struct FLevelPackageItem`  
_L24-28_
- desc: FLevelPackageItem
- L26 _public member_ `FString DisplayName;`
- L27 _public member_ `FString LongPackageName;`

#### class `SPropertyEditorLevelPackage`  
`class SPropertyEditorLevelPackage : public SCompoundWidget`  
_L39-118_
- inherits: `SCompoundWidget`
- desc: SPropertyEditorLevelPackage Widget which plugs in to a details panel to edit FNames properties which represent a level package name Looks kinda similar to a SPropertyEditorAsset, should be replaced with it when ContentBrowser will treat ULevel as an asset
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterPackage, const FString&);`
- L44 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPackagePicked, const FString&);`
- L47 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorLevelPackage ) : _RootPath(FPackageName::FilenameToLongPackageName(FPaths::ProjectContentDir())) , _SortAlphabetically(false)`
- L52 _public prototype_ `SLATE_ARGUMENT( FString, RootPath ) SLATE_ARGUMENT( bool, SortAlphabetically ) SLATE_EVENT(FOnShouldFilterPackage, OnShouldFilterPackage) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<class IPropertyHandle>& InPropertyHandle);` — Root folder path for gathering level packages
- L62 _public prototype_ `FLevelPackageItem PackageNameToItem(const FString& PackageName) const;` — @return FLevelPackageItem initialized from a given PackageName
- L66 _private prototype_ `FText GetDisplayPackageName() const;` — @return Display text for a property value
- L69 _private prototype_ `TSharedRef<SWidget> GetMenuContent();` — @return Picker widget with content to display combo box drop menu
- L72 _private prototype_ `TSharedRef<SWidget> MakePickerWidget();` — Creates picker widget
- L75 _private prototype_ `TSharedRef<ITableRow> MakeListRowWidget(TSharedPtr<FLevelPackageItem> InPackageName, const TSharedRef<STableViewBase>& OwnerTable) const;` — Creates a row for a piker widget
- L78 _private prototype_ `void OnSelectionChanged(const TSharedPtr<FLevelPackageItem> Item, ESelectInfo::Type SelectInfo);` — Handles on OnSelectionChanged event from a picker widget
- L81 _private prototype_ `void PopulatePackages();` — Populates internal array with levels packages found on disk under RootPath
- L84 _private prototype_ `void PopulateFilteredPackages();` — Populates internal array with packages previously found on disk according to current filter settings
- L87 _private prototype_ `void TransformPackageItemToString(const TSharedPtr<FLevelPackageItem>& Item, TArray<FString>& OutSearchStrings) const;` — Transforms FLevelPackageItem to a search terms for a text filter
- L90 _private prototype_ `void OnTextFilterChanged();` — Handles text filter changes
- L93 _private prototype_ `TSharedPtr<FLevelPackageItem> FindPackageItem(const FString& PackageName);` — Handles text filter changes
- L96 _private prototype_ `FString GetPropertyValue() const;` — @return Current property value as a string
- L100 _private member_ `FString RootPath;`
- L102 _private member_ `bool bSortAlphabetically;`
- L104 _private member_ `FOnShouldFilterPackage OnShouldFilterPackage;`
- L106 _private member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;`
- L108 _private member_ `TSharedPtr<class SComboButton> PropertyMainWidget;`
- L110 _private member_ `TWeakPtr<SLevelPackageListView> PickerListWidget;`
- L112 _private member_ `TArray<TSharedPtr<FLevelPackageItem>> LevelPackages;`
- L114 _private member_ `TArray<TSharedPtr<FLevelPackageItem>> FilteredLevelPackages;`
- L116 _private member_ `TSharedPtr<LevelPackageTextFilter> SearchBoxLevelPackageFilter;`

#### Free symbols / members of external scopes

- L30 _typedef_ `typedef TTextFilter<const TSharedPtr<FLevelPackageItem>&> LevelPackageTextFilter;`
- L31 _typedef_ `typedef SListView<TSharedPtr<FLevelPackageItem>> SLevelPackageListView;`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterPackage, const FString&);`
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPackagePicked, const FString&);`

### `Source/Editor/WorldBrowser/Private/SWorldDetails.h` (Private)


#### class `SWorldDetails`  
`class SWorldDetails : public SCompoundWidget`  
_L20-63_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SWorldDetails) :_InWorld(nullptr)`
- L27 _public prototype_ `SLATE_ARGUMENT(UWorld*, InWorld) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `SWorldDetails();`
- L32 _public prototype_ `~SWorldDetails();`
- L36 _private prototype_ `void OnBrowseWorld(UWorld* InWorld);`
- L39 _private prototype_ `void OnSelectionChanged();` — Handles selection changes in data source
- L42 _private prototype_ `void OnCollectionChanged();` — Handles levels collection changes in data source
- L45 _private prototype_ `void OnSetInspectedLevel(TSharedPtr<FLevelModel> InLevelModel, ESelectInfo::Type SelectInfo);`
- L46 _private prototype_ `TSharedRef<SWidget> HandleInspectedLevelComboBoxGenerateWidget(TSharedPtr<FLevelModel> InLevelModel) const;`
- L47 _private prototype_ `FText GetInspectedLevelText() const;`
- L50 _private prototype_ `FReply OnSummonHierarchy();`
- L53 _private prototype_ `EVisibility GetCompositionButtonVisibility() const;`
- L54 _private prototype_ `FReply OnSummonComposition();`
- L57 _private member_ `TSharedPtr<FLevelCollectionModel> WorldModel;`
- L58 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L59 _private member_ `TSharedPtr<SVerticalBox> VerticalBox;`
- L60 _private member_ `TSharedPtr<SBorder> VerticalBoxBorder;`
- L61 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FLevelModel>>> SubLevelsComboBox;`
- L62 _private member_ `bool bUpdatingSelection;`

### `Source/Editor/WorldBrowser/Private/SWorldHierarchy.h` (Private)


#### class `SWorldHierarchy`  
`class SWorldHierarchy : public SCompoundWidget , public UE::WorldHierarchy::IWorldHierarchy`  
_L17-65_
- inherits: `SCompoundWidget,UE::WorldHierarchy::IWorldHierarchy`
- desc: Listens for world changes and updates SWorldHierarchyImpl, which displays the level hierarchy for the passed in world.
- L21 _private function_ `SLATE_BEGIN_ARGS(SWorldHierarchy) :_InWorld(nullptr)`
- L24 _private prototype_ `SLATE_ARGUMENT(UWorld*, InWorld) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _private prototype_ `SWorldHierarchy();`
- L29 _private prototype_ `~SWorldHierarchy();`
- L32 _private function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L33 _private prototype_ `virtual bool IsColumnVisible(FName Column) const override;`
- L34 _private prototype_ `virtual void SetColumnVisible(FName Column, bool bVisible) override;`
- L38 _private prototype_ `void OnBrowseWorld(UWorld* InWorld);`
- L41 _private prototype_ `FReply OnSummonDetails();`
- L43 _private prototype_ `EVisibility GetCompositionButtonVisibility() const;`
- L44 _private prototype_ `FReply OnSummonComposition();`
- L45 _private prototype_ `const FSlateBrush* GetSummonCompositionBrush() const;`
- L48 _private prototype_ `TSharedRef<SWidget> GetFileButtonContent();`
- L56 _private member_ `TSharedPtr<FLevelCollectionModel> WorldModel;` — Model for the UI managing the world logic. FWorldBrowserModule expects to be the only referencer of this model when switching worlds.
- L64 _private member_ `TWeakPtr<SWorldHierarchyImpl> WeakWorldHierarchyImpl;` — Actually displays the hierarchy. WorldModel, which is managed by FWorldBrowserModule, expects the reference count to be 1 when switching worlds. OnBrowseWorld kills this widget when switching worlds. That is why this must be a weak pointer instead of a strong pointer.

### `Source/Editor/WorldBrowser/Private/SWorldHierarchyImpl.h` (Private)


#### struct `WorldHierarchy::FPendingWorldTreeOperation`  
`struct FPendingWorldTreeOperation`  
_L27-37_
- desc: Structure that defines an operation that should be applied to the world hierarchy
- L30 _public function_ `FPendingWorldTreeOperation(EType InOp, FWorldTreeItemRef InItem) : Operation(InOp), Item(InItem)`
- L33 _public member_ `EType Operation;` — The type of operation to perform
- L36 _public member_ `FWorldTreeItemRef Item;` — The item affected by this operation

#### enum `WorldHierarchy::FPendingWorldTreeOperation::EType`  
`enum EType`  
_L29-29_
- L29 _public enumerator_ `enum EType { Added, Removed, Moved, }; FPendingWorldTreeOperation(EType InOp, FWorldTreeItemRef InItem) : Operation(InOp)`
- L29 _public enumerator_ `enum EType { Added, Removed, Moved, }; FPendingWorldTreeOperation(EType InOp, FWorldTreeItemRef InItem) : Operation(InOp)`
- L29 _public enumerator_ `enum EType { Added, Removed, Moved, }; FPendingWorldTreeOperation(EType InOp, FWorldTreeItemRef InItem) : Operation(InOp)`

#### enum `WorldHierarchy::ENewItemAction`  
`enum class ENewItemAction : uint8`  
_L40-46_
- desc: Defines operations for items to perform when they are added to the tree
- L42 _public enumerator_ `None = 0`
- L43 _public enumerator_ `Select = 1 << 0` — None			= 0,		  No Actions for the item
- L44 _public enumerator_ `ScrollIntoView = 1 << 1` — Select			= 1 << 0,	  Item should be selected
- L45 _public enumerator_ `Rename = 1 << 2` — ScrollIntoView	= 1 << 1,	  Item should be selected

#### class `SWorldHierarchyImpl`  
`class SWorldHierarchyImpl : public SCompoundWidget , public FEditorUndoClient`  
_L53-400_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L58 _public function_ `SLATE_BEGIN_ARGS(SWorldHierarchyImpl) : _ShowFoldersOnly(false)`
- L62 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FLevelCollectionModel>, InWorldModel) SLATE_ARGUMENT(bool, ShowFoldersOnly) SLATE_ARGUMENT(TSet<FName>, InExcludedFolders) SLATE_ARGUMENT(FOnWorldHierarchyItemPicked, OnItemPickedDelegate) SLATE_END_ARGS() SWorldHierarchyImpl();` — The world represented by this hierarchy
- L72 _public prototype_ `~SWorldHierarchyImpl();`
- L74 _public prototype_ `void Construct(const FArguments& InArgs);`
- L77 _public prototype_ `void RefreshView();` — Regenerates current items
- L79 _public prototype_ `virtual void Tick( const FGeometry& AllotedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L82 _public prototype_ `void CreateFolder(TSharedPtr<FLevelModel> InModel, FName ParentPath = NAME_None, const bool bMoveSelected = true);` — Creates a new folder for the hierarchy. If ParentPath is defined, the folder will be created relative to that path.
- L85 _public prototype_ `void MoveItemsTo(TSharedPtr<FLevelModel> InModel, FName Path);` — Moves the current selection to the specified path
- L88 _public prototype_ `void InitiateRename(WorldHierarchy::FWorldTreeItemRef InItem);` — Initiates a rename of the selected item
- L91 _public prototype_ `void DeleteFolders(TArray<WorldHierarchy::FWorldTreeItemPtr> SelectedItems, bool bTransactional = true);` — Deletes the folders contained in the selection from the hierarchy tree.
- L94 _public prototype_ `void MoveDroppedItems(const TArray<WorldHierarchy::FWorldTreeItemPtr>& DraggedItems, FName FolderPath);` — Moves selected items from a drag and drop operation
- L97 _public prototype_ `void AddDroppedLevelsToFolder(const TArray<FAssetData>& WorldAssetList, FName FolderPath);` — Adds the specified levels to the hierarchy under the specified folder path
- L100 _public function_ `TArray<WorldHierarchy::FWorldTreeItemPtr> GetSelectedTreeItems() const` — Helper funciton to get the selected items from the tree widget
- L106 _public prototype_ `bool IsColumnVisible(FName ColumnId) const;` — @see WorldHierarchyColumns.h for named columns. @return Whether Column is visible in the UI.
- L111 _public prototype_ `void SetColumnVisible(FName ColumnId, bool bVisible);` — Sets whether Column is visible in the UI. @see WorldHierarchyColumns.h for named columns.
- L114 _public prototype_ `static bool IsVisibleInConfig(FName ColumnId);` — @return Whether the column will be visible according to the config.
- L116 _public prototype_ `static void SetWillBeVisibleInConfigTransient(FName ColumnId, bool bIsVisible);` — Sets whether the next widget created from now will have ColumnId visible but does not save it into the config.
- L120 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L121 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L125 _private member_ `static const int32 MaxPendingOperations = 500;` — The maximum number of pending operations to process at one time
- L128 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRow();` — Creates the header row for the level hierarchy.
- L131 _private prototype_ `void SaveColumnVisibilitiesIntoConfig();` — Invokes when the column visibility changes.
- L134 _private prototype_ `static bool IsRequiredColumn(FName ColumnId);` — @return Whether the given column is always shown.
- L137 _private prototype_ `static bool IsKnownColumn(FName ColumnId);` — @return Whether the column is used by this UI
- L140 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow(WorldHierarchy::FWorldTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Creates an item for the tree view
- L143 _private prototype_ `void GetChildrenForTree(WorldHierarchy::FWorldTreeItemPtr Item, TArray<WorldHierarchy::FWorldTreeItemPtr>& OutChildren);` — Handler for returning a list of children associated with a particular tree node
- L146 _private prototype_ `TSharedPtr<SWidget> ConstructLevelContextMenu() const;` — @return the SWidget containing the context menu
- L149 _private prototype_ `void FillFoldersSubmenu(FMenuBuilder& MenuBuilder);` — Builds the submenu for moving items to other folders in the hierarchy
- L152 _private prototype_ `void AddMoveToFolderOutliner(FMenuBuilder& MenuBuilder, const TArray<WorldHierarchy::FWorldTreeItemPtr>& CachedSelectedItems, TSharedRef<FLevelModel> RootLevel);` — Builds the list of valid folders that an item can be moved to
- L155 _private prototype_ `void FillSelectionSubmenu(FMenuBuilder& MenuBuilder);` — Builds the menu that allows for children of a folder to be selected from the context menu
- L158 _private prototype_ `void SelectFolderDescendants(bool bSelectAllDescendants);` — Selects the level descendants of the currently selected folders. If bSelectAllDescendants is true, all descendants will be selected instead of immediate children
- L161 _private prototype_ `void OnTreeItemScrolledIntoView( WorldHierarchy::FWorldTreeItemPtr Item, const TSharedPtr<ITableRow>& Widget );` — Called after a tree item has been scrolled into view. This initiates a pending rename.
- L164 _private prototype_ `void OnExpansionChanged(WorldHierarchy::FWorldTreeItemPtr Item, bool bIsItemExpanded);` — Called by TreeView widget whenever tree item expanded or collapsed
- L167 _private prototype_ `void OnSelectionChanged(const WorldHierarchy::FWorldTreeItemPtr Item, ESelectInfo::Type SelectInfo);` — Called by TreeView widget whenever selection is changed
- L170 _private prototype_ `void OnUpdateSelection();` — Handles selection changes in data source
- L177 _private prototype_ `void OnTreeViewMouseButtonDoubleClick(WorldHierarchy::FWorldTreeItemPtr Item);` — Called by STreeView when the user double-clicks on an item @param	Item	The item that was double clicked
- L184 _private function_ `virtual bool SupportsKeyboardFocus() const override` — Checks to see if this widget supports keyboard focus.  Override this in derived classes. @return  True if this widget can take keyboard focus
- L197 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Called after a key is pressed when this widget has focus @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L201 _private function_ `template <typename TreeItemType, typename DataType> void ConstructItemFor(const DataType& Data)` — Adds a new item for the specified type and refreshes the tree, provided it matches the filter terms
- L218 _private prototype_ `void Populate();` — Applies incremental changes to the tree, or completely repopulates it
- L221 _private prototype_ `void EmptyTreeItems();` — Empties all items within the tree
- L224 _private prototype_ `void RepopulateEntireTree();` — Fully rebuilds the tree, including folders
- L227 _private prototype_ `bool AddItemToTree(WorldHierarchy::FWorldTreeItemRef InItem);` — Adds a new item to the tree if it passes the current filter
- L230 _private prototype_ `void RemoveItemFromTree(WorldHierarchy::FWorldTreeItemRef InItem);` — Removes a single item from the tree. This does not delete it
- L233 _private prototype_ `void OnItemMoved(WorldHierarchy::FWorldTreeItemRef InItem);` — Handles moving an item to ensure that its parent now exists in the hierarchy regardless of filter, or potentially hides the previous parent
- L236 _private prototype_ `void AddUnfilteredItemToTree(WorldHierarchy::FWorldTreeItemRef InItem);` — Adds a new item to the tree, ignoring the current filter
- L239 _private prototype_ `void OnChildRemovedFromParent(WorldHierarchy::FWorldTreeItemRef InParent);` — Called when a child is removed from the parent. This can potentially filter the parent out of the current view
- L242 _private prototype_ `WorldHierarchy::FWorldTreeItemPtr EnsureParentForItem(WorldHierarchy::FWorldTreeItemRef Item);` — Ensures that the item's parent exists and is placed in the hierarchy tree
- L245 _private prototype_ `TMap<WorldHierarchy::FWorldTreeItemID, bool> GetParentsExpansionState() const;` — Gets the expansion state of all parent items. Call this before repopulating the tree
- L248 _private prototype_ `void SetParentsExpansionState(const TMap<WorldHierarchy::FWorldTreeItemID, bool>& ExpansionInfo);` — Sets the expansion state of all parent items based on the cached expansion info
- L251 _private prototype_ `void FullRefresh();` — Causes the tree to be fully rebuilt
- L254 _private prototype_ `void RebuildFoldersAndFullRefresh();` — Rebuilds the folder list for the hierarchy, and forces a full refresh
- L257 _private prototype_ `void ScrollItemIntoView(WorldHierarchy::FWorldTreeItemPtr Item);` — Scrolls the specified item into view
- L260 _private prototype_ `void OnBroadcastFolderCreate(TSharedPtr<FLevelModel> LevelModel, FName NewPath);` — Called when a folder is created
- L263 _private prototype_ `void OnBroadcastFolderMove(TSharedPtr<FLevelModel> LevelModel, FName OldPath, FName NewPath);` — Called when a folder is moved
- L266 _private prototype_ `void OnBroadcastFolderDelete(TSharedPtr<FLevelModel> LevelModel, FName Path);` — Called when a folder is deleted
- L269 _private prototype_ `void OnBroadcastLevelsUnloaded();` — Called when levels have been unloaded
- L272 _private prototype_ `FReply OnCreateFolderClicked();` — Called when the Create Folder button has been clicked
- L275 _private prototype_ `void RequestSort();` — Requests that items are sorted in the hierarchy view
- L278 _private prototype_ `void SortItems(TArray<WorldHierarchy::FWorldTreeItemPtr>& Items);` — Sorts the selected items
- L281 _private prototype_ `void MoveSelectionTo(WorldHierarchy::FWorldTreeItemRef Item);` — Moves the selected items to the given item
- L284 _private prototype_ `bool PassesFilter(const WorldHierarchy::IWorldTreeItem& Item);` — Returns true if the item would pass the current filter
- L287 _private prototype_ `EVisibility GetEmptyLabelVisibility() const;` — Gets the visibility of the empty label
- L291 _private prototype_ `bool IsTreeItemExpanded(WorldHierarchy::FWorldTreeItemPtr Item) const;` — @returns Whether specified item should be expanded
- L294 _private prototype_ `void TransformLevelToString(const FLevelModel* Level, TArray<FString>& OutSearchStrings) const;` — Appends the Level's name to the OutSearchStrings array if the Level is valid
- L297 _private prototype_ `void TransformItemToString(const WorldHierarchy::IWorldTreeItem& Item, TArray<FString>& OutSearchStrings) const;` — Appends the levels contained in Item to the OutSearchStrings array
- L300 _private prototype_ `FText GetSearchBoxText() const;` — @return Text entered in search box
- L303 _private prototype_ `FText GetFilterStatusText() const;` — @return	Returns the filter status text
- L305 _private prototype_ `void SetFilterText(const FText& InFilterText);`
- L308 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;` — @return Returns color for the filter status text message, based on success of search filter
- L311 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent();` — @return the content for the view button
- L314 _private function_ `void ToggleDisplayPaths_Executed()` — Toggles state of 'display path'
- L320 _private prototype_ `bool GetDisplayPathsState() const;` — Gets the state of the 'display paths' enabled/disabled
- L323 _private prototype_ `void ToggleDisplayActorsCount_Executed();` — Toggles state of 'display actors count'
- L326 _private prototype_ `bool GetDisplayActorsCountState() const;` — Gets the state of the 'display actors count' enabled/disabled
- L329 _private prototype_ `void OnWorldSaved(UWorld* World, FObjectPostSaveContext ObjectSaveContext);` — Callback for when the world is saved
- L333 _private member_ `bool bUpdatingSelection;` — Whether the view is currently updating the viewmodel selection
- L336 _private member_ `TSharedPtr<SLevelsTreeWidget> TreeWidget;` — Our list view widget
- L339 _private member_ `TSharedPtr<FLevelCollectionModel> WorldModel;` — Items collection to display
- L342 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;` — The Header Row for the hierarchy
- L345 _private member_ `TSharedPtr<LevelTextFilter> SearchBoxLevelFilter;` — The LevelTextFilter that constrains which items appear in the world model list
- L348 _private member_ `TSharedPtr<HierarchyFilter> SearchBoxHierarchyFilter;` — The filter that constrains which items appear in the hierarchy
- L351 _private member_ `TSharedPtr<SComboButton> ViewOptionsComboButton;` — Button representing view options on bottom
- L354 _private member_ `TArray<WorldHierarchy::FWorldTreeItemPtr> RootTreeItems;` — Root items for the tree widget
- L357 _private member_ `bool bIsReentrant;` — Reentracy guard
- L360 _private member_ `bool bFullRefresh;` — True if the tree should perform a full refresh
- L363 _private member_ `bool bNeedsRefresh;` — True if the tree needs to be refreshed
- L366 _private member_ `bool bRebuildFolders;` — True if the folder list needs to be rebuilt
- L369 _private member_ `bool bSortDirty;` — True if the items require sort
- L372 _private member_ `bool bIsProgrammaticallyChangingColumnVisibility = false;` — Whether the column visibility is currently being changed via code (as opposed to via user selection in the UI).
- L375 _private member_ `TArray<WorldHierarchy::FPendingWorldTreeOperation> PendingOperations;` — Operations that are waiting to be resolved for items in the tree
- L378 _private member_ `TMap<WorldHierarchy::FWorldTreeItemID, WorldHierarchy::FWorldTreeItemPtr> PendingTreeItemMap;` — Items that are waiting to be committed to the tree view
- L381 _private member_ `TMap<WorldHierarchy::FWorldTreeItemID, WorldHierarchy::FWorldTreeItemPtr> TreeItemMap;` — All items that are currently displayed in the tree widget
- L384 _private member_ `TMap<WorldHierarchy::FWorldTreeItemID, WorldHierarchy::ENewItemAction> NewItemActions;` — Map of actions to apply to new tree items
- L387 _private member_ `TWeakPtr<WorldHierarchy::IWorldTreeItem> ItemPendingRename;` — The item that is currently pending a rename
- L390 _private member_ `TArray<WorldHierarchy::FWorldTreeItemID> ItemsSelectedAfterRefresh;` — Keeps track of which items should be selected after a refresh occurs
- L393 _private member_ `bool bFoldersOnlyMode;` — If true, only show root items and the folders for each item
- L396 _private member_ `TSet<FName> ExcludedFolders;` — If folders-only mode is specified, prevents folders with the following names from being shown in the hierarchy
- L399 _private member_ `FOnWorldHierarchyItemPicked OnItemPicked;` — Delegate that fires when the selection changes

#### Free symbols / members of external scopes

- L21 _typedef_ `typedef TTextFilter<const WorldHierarchy::IWorldTreeItem& > HierarchyFilter;`
- L22 _typedef_ `typedef TTextFilter<const FLevelModel* > LevelTextFilter;`
- L24 _namespace_ `namespace WorldHierarchy`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWorldHierarchyItemPicked, WorldHierarchy::FWorldTreeItemRef);`
- L51 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWorldHierarchyItemPicked, WorldHierarchy::FWorldTreeItemRef);`

### `Source/Editor/WorldBrowser/Private/SWorldHierarchyItem.h` (Private)


#### class `SWorldHierarchyItem`  
`class SWorldHierarchyItem : public SMultiColumnTableRow<WorldHierarchy::FWorldTreeItemPtr>`  
_L24-261_
- inherits: `SMultiColumnTableRow<WorldHierarchy::FWorldTreeItemPtr>`
- desc: A single item in the levels hierarchy tree. Represents a level model
- L28 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnNameChanged, const WorldHierarchy::FWorldTreeItemPtr& , const FVector2D& );`
- L30 _public function_ `SLATE_BEGIN_ARGS( SWorldHierarchyItem ) : _IsItemExpanded( false ) , _FoldersOnlyMode( false )`
- L35 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FLevelCollectionModel>, InWorldModel) SLATE_ARGUMENT(WorldHierarchy::FWorldTreeItemPtr, InItemModel) SLATE_ARGUMENT(TSharedPtr<SWorldHierarchyImpl>, InHierarchy) SLATE_ATTRIBUTE(bool, IsItemExpanded) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(bool, FoldersOnlyMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView);` — Data for the world
- L57 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;`
- L59 _public prototype_ `FReply OnItemDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L60 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L61 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L62 _public function_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override`
- L63 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L66 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& Event) override;`
- L70 _private prototype_ `bool IsSaveEnabled() const;` — Operations buttons enabled/disabled state
- L71 _private prototype_ `bool IsLightingScenarioEnabled() const;`
- L72 _private prototype_ `bool IsLockEnabled() const;`
- L73 _private prototype_ `bool IsEditorVisibilityEnabled() const;`
- L74 _private prototype_ `bool IsGameVisibilityEnabled() const;`
- L75 _private prototype_ `bool IsKismetEnabled() const;`
- L78 _private prototype_ `FSlateColor GetDrawColor() const;` — Get DrawColor for the level
- L85 _private prototype_ `FReply OnToggleEditorVisibility();` — Called when the user clicks on the visibility icon for a Level's item widget @return	A reply that indicated whether this event was handled.
- L86 _private prototype_ `FReply OnToggleGameVisibility();`
- L88 _private prototype_ `FReply OnToggleLightingScenario();`
- L95 _private prototype_ `FReply OnToggleLock();` — Called when the user clicks on the lock icon for a Level's item widget @return	A reply that indicated whether this event was handled.
- L102 _private prototype_ `FReply OnSave();` — Called when the user clicks on the save icon for a Level's item widget @return	A reply that indicated whether this event was handled.
- L109 _private prototype_ `FReply OnOpenKismet();` — Called when the user clicks on the kismet icon for a Level's item widget @return	A reply that indicated whether this event was handled.
- L116 _private prototype_ `FReply OnChangeColor();` — Called when the user clicks on the color icon for a Level's item widget @return	A reply that indicated whether this event was handled.
- L119 _private prototype_ `void OnSetColorFromColorPicker(FLinearColor NewColor);` — Callback invoked from the color picker
- L120 _private prototype_ `void OnColorPickerCancelled(FLinearColor OriginalColor);`
- L121 _private prototype_ `void OnColorPickerInteractiveBegin();`
- L122 _private prototype_ `void OnColorPickerInteractiveEnd();`
- L125 _private prototype_ `EVisibility GetLightingScenarioVisibility() const;` — Whether the lighting scenario button should be visible
- L128 _private prototype_ `EVisibility GetColorButtonVisibility() const;` — Whether color button should be visible, depends on whether sub-level is loaded
- L131 _private prototype_ `FText GetEditorVisibilityToolTip() const;` — Gets the tooltip for the editor visibility toggle
- L134 _private prototype_ `FText GetGameVisibilityToolTip() const;` — Gets the tooltip for the game visibility toggle
- L137 _private prototype_ `FText GetSaveToolTip() const;` — Gets the tooltip for the save button
- L140 _private prototype_ `FText GetKismetToolTip() const;` — Gets the tooltip text for the Kismet button
- L145 _private prototype_ `FText GetDisplayNameText() const;` — @return The text of level name while it is not being edited
- L150 _private prototype_ `FText GetDisplayNameTooltip() const;` — @return The tooltip of level name (shows the full path of the asset package)
- L153 _private prototype_ `FSlateFontInfo GetDisplayNameFont() const;`
- L156 _private prototype_ `FSlateColor GetDisplayNameColorAndOpacity() const;`
- L161 _private prototype_ `const FSlateBrush* GetLevelIconBrush() const;` — @return	The SlateBrush representing level icon
- L169 _private prototype_ `const FSlateBrush* GetLevelVisibilityBrush() const;` — Called to get the Slate Image Brush representing the visibility state of the Level this item widget represents @return	The SlateBrush representing the Level's visibility state
- L170 _private prototype_ `const FSlateBrush* GetGameVisibilityBrush() const;`
- L172 _private prototype_ `const FSlateBrush* GetLightingScenarioBrush() const;`
- L180 _private prototype_ `const FSlateBrush* GetLevelLockBrush() const;` — Called to get the Slate Image Brush representing the lock state of the Level this item widget represents @return	The SlateBrush representing the Level's lock state
- L188 _private prototype_ `const FSlateBrush* GetLevelSaveBrush() const;` — Called to get the Slate Image Brush representing the save state of the Level this row widget represents @return	The SlateBrush representing the Level's save state
- L196 _private prototype_ `const FSlateBrush* GetLevelKismetBrush() const;` — Called to get the Slate Image Brush representing the kismet state of the Level this row widget represents @return	The SlateBrush representing the Level's kismet state
- L204 _private prototype_ `const FSlateBrush* GetLevelColorBrush() const;` — Called to get the Slate Image Brush representing the color of the Level this row widget represents @return	The SlateBrush representing the Level's color
- L207 _private prototype_ `FText GetLightingScenarioToolTip() const;`
- L210 _private prototype_ `FText GetLevelLockToolTip() const;`
- L213 _private prototype_ `FText GetSCCStateTooltip() const;`
- L216 _private prototype_ `const FSlateBrush* GetSCCStateImage() const;`
- L218 _private prototype_ `bool OnVerifyItemLabelChanged(const FText& InLabel, FText& OutErrorMessage);`
- L220 _private prototype_ `void OnLabelCommitted(const FText& InLabel, ETextCommit::Type InCommitInfo);`
- L224 _private member_ `TSharedPtr<FLevelCollectionModel> WorldModel;` — The world data
- L227 _private member_ `WorldHierarchy::FWorldTreeItemPtr WorldTreeItem;` — The data for this item
- L230 _private member_ `TWeakPtr<SWorldHierarchyImpl> Hierarchy;` — The hierarchy for this item
- L233 _private member_ `TAttribute<FText> HighlightText;` — The string to highlight in level display name
- L236 _private member_ `TAttribute<bool> IsItemExpanded;` — True when this item has children and is expanded
- L239 _private member_ `TSharedPtr<SButton> EditorVisibilityButton;` — The editor visibility button for the Level
- L242 _private member_ `TSharedPtr<SButton> GameVisibilityButton;` — The game visibility button for the Level
- L245 _private member_ `TSharedPtr<SButton> LightingScenarioButton;` — The lighting scenario button for the Level
- L248 _private member_ `TSharedPtr<SButton> LockButton;` — The lock button for the Level
- L251 _private member_ `TSharedPtr<SButton> SaveButton;` — The save button for the Level
- L254 _private member_ `TSharedPtr<SButton> KismetButton;` — The kismet button for the Level
- L257 _private member_ `TSharedPtr<SButton> ColorButton;` — The color button for the Level
- L260 _private member_ `bool bFoldersOnlyMode;` — If true, folders cannot be renamed and only folder names are ever shown

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnNameChanged, const WorldHierarchy::FWorldTreeItemPtr& , const FVector2D& );`

### `Source/Editor/WorldBrowser/Private/StreamingLevels/StreamingLevelCollectionModel.h` (Private)


#### class `FStreamingLevelCollectionModel`  
`class FStreamingLevelCollectionModel : public FLevelCollectionModel , public FEditorUndoClient`  
_L13-136_
- inherits: `FLevelCollectionModel,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a LevelsView
- L21 _public prototype_ `virtual ~FStreamingLevelCollectionModel();` — FStreamingLevelCollectionModel destructor
- L28 _public function_ `static TSharedRef<FStreamingLevelCollectionModel> Create(UWorld* InWorld)` — Factory method which creates a new FStreamingLevelCollectionModel object @param	InEditor		The UEditorEngine to use
- L37 _public prototype_ `virtual void UnloadLevels(const FLevelModelList& InLevelList) override;` — FLevelCollection interface
- L38 _public prototype_ `virtual void AddExistingLevelsFromAssetData(const TArray<FAssetData>& WorldList) override;`
- L39 _public prototype_ `virtual TSharedPtr<WorldHierarchy::FWorldBrowserDragDropOp> CreateDragDropOp() const override;`
- L40 _public prototype_ `virtual TSharedPtr<WorldHierarchy::FWorldBrowserDragDropOp> CreateDragDropOp(const FLevelModelList& InLevels) const override;`
- L41 _public prototype_ `virtual void BuildHierarchyMenu(FMenuBuilder& InMenuBuilder, EBuildHierarchyMenuFlags Flags) const override;`
- L42 _public prototype_ `virtual void CustomizeFileMainMenu(FMenuBuilder& InMenuBuilder) const override;`
- L43 _public prototype_ `virtual void RegisterDetailsCustomization(class FPropertyEditorModule& PropertyModule, TSharedPtr<class IDetailsView> InDetailsView) override;`
- L44 _public prototype_ `virtual void UnregisterDetailsCustomization(class FPropertyEditorModule& PropertyModule, TSharedPtr<class IDetailsView> InDetailsView) override;`
- L45 _public function_ `virtual bool HasFolderSupport() const override`
- L48 _private prototype_ `virtual void Initialize(UWorld* InWorld) override;`
- L49 _private prototype_ `virtual void BindCommands() override;`
- L50 _private prototype_ `virtual void OnLevelsCollectionChanged() override;`
- L51 _private prototype_ `virtual void OnLevelsSelectionChanged() override;`
- L56 _public prototype_ `const FLevelModelList& GetInvalidSelectedLevels() const;` — @return Any selected ULevel objects in the LevelsView that are NULL
- L65 _private prototype_ `FStreamingLevelCollectionModel();` — FStreamingLevelCollectionModel Constructor @param	InWorldLevels	The Level management logic object @param	InEditor		The UEditorEngine to use
- L68 _private function_ `virtual void PostUndo(bool bSuccess) override`
- L69 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L74 _private prototype_ `void FixupInvalidReference_Executed();` — Adds an existing level; prompts for path
- L77 _private prototype_ `void RemoveInvalidSelectedLevels_Executed();` — Removes selected levels from world
- L80 _private prototype_ `void CreateNewLevel_Executed();` — Creates a new level; prompts for level save location
- L83 _private prototype_ `void AddExistingLevel_Executed();` — Calls AddExistingLevel which adds an existing level; prompts for path
- L86 _private prototype_ `void AddExistingLevel(bool bRemoveInvalidSelectedLevelsAfter = false);` — Adds an existing level; prompts for path, Returns true if a level is selected
- L89 _private prototype_ `void HandleAddExistingLevelSelected(const TArray<FAssetData>& SelectedAssets, bool bRemoveInvalidSelectedLevelsAfter);` — Handler for when a level is selected after invoking AddExistingLevel
- L92 _private prototype_ `void HandleAddExistingLevelCancelled();` — Handler for when the level picker dialog is cancelled
- L95 _private prototype_ `void AddSelectedActorsToNewLevel_Executed();` — Add Selected Actors to New Level; prompts for level save location
- L98 _private prototype_ `void MergeSelectedLevels_Executed();` — Merges selected levels into a new level; prompts for level save location
- L101 _private prototype_ `void SetAddedLevelStreamingClass_Executed(UClass* InClass);` — Changes the streaming method for new or added levels.
- L104 _private prototype_ `bool IsNewStreamingMethodChecked(UClass* InClass) const;` — Checks if the passed in streaming method is checked
- L107 _private prototype_ `bool IsStreamingMethodChecked(UClass* InClass) const;` — Checks if the passed in streaming method is the current streaming method
- L110 _private prototype_ `bool AreAllSelectedLevelsRemovable() const;` — @return	whether the selected levels are allowed to be removed from the world
- L113 _private prototype_ `void SetStreamingLevelsClass_Executed(UClass* InClass);` — Changes the streaming method for the selected levels.
- L116 _private prototype_ `void SelectStreamingVolumes_Executed();` — Selects the streaming volumes associated with the selected levels
- L119 _private prototype_ `void FillSetStreamingMethodSubMenu(class FMenuBuilder& MenuBuilder);`
- L122 _private prototype_ `void FillChangeLightingScenarioSubMenu(class FMenuBuilder& MenuBuilder);`
- L125 _private prototype_ `void FillDefaultStreamingMethodSubMenu(class FMenuBuilder& MenuBuilder);`
- L129 _private member_ `FLevelModelList InvalidSelectedLevels;` — Currently selected NULL Levels
- L132 _private member_ `UClass* AddedLevelStreamingClass;` — The current class to set new or added levels streaming method to.
- L135 _private member_ `bool bAssetDialogOpen;` — Boolean indicating whether the asset dialog is currently open

### `Source/Editor/WorldBrowser/Private/StreamingLevels/StreamingLevelCustomization.h` (Private)


#### enum `ELevelTransformField::Type`  
`enum Type`  
_L15-19_
- L17 _public enumerator_ `Location`
- L18 _public enumerator_ `Rotation`

#### class `FStreamingLevelCustomization`  
`class FStreamingLevelCustomization : public IDetailCustomization`  
_L24-137_
- inherits: `IDetailCustomization`
- desc: FStreamingLevelCustomization
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedRef<FStreamingLevelCollectionModel> InWorldData);` — Makes a new instance of this detail layout class
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L35 _private prototype_ `FStreamingLevelCustomization();`
- L44 _private prototype_ `void OnSetLevelPosition( FVector::FReal NewValue, ETextCommit::Type CommitInfo, int32 Axis );` — Called by the Editor Level Transform column, to set the new values. @param NewValue		The new value entered. @param CommitInfo	The way in which the value was committed, currently ignored, we always use the new value. @param Axis			The axis being edited.
- L51 _private prototype_ `void OnSetLevelPosition(FVector NewValue);` — Called by the Editor Level Transform column, to set the new values. @param NewValue		The new value entered.
- L60 _private prototype_ `TOptional<FVector::FReal> OnGetLevelPosition( int32 Axis ) const;` — Called by the Editor Level Transform column, to get the current values. @param Axis		The axis to return the value for. @return			The current value of the translation for given axis.
- L67 _private prototype_ `void OnChangedLevelRotation(int32 NewValue);` — Called by the Editor Level Rotation column, to update the displayed value as we spin @param NewValue		The new value entered.
- L75 _private prototype_ `void OnSetLevelRotation( int32 NewValue, ETextCommit::Type CommitInfo);` — Called by the Editor Level Rotation column, to set the new values. @param NewValue		The new value entered. @param CommitInfo	How the value was set.
- L80 _private prototype_ `void OnBeginLevelRotationSlider();` — Called by the Editor Level Rotation column, to set weve started spinning the value.
- L87 _private prototype_ `void OnEndLevelRotationSlider( int32 NewValue );` — Called by the Editor Level Rotation column, to set weve stopped spinning the value. @param NewValue		The new value entered.
- L94 _private prototype_ `TOptional<int32> GetLevelRotation() const;` — Called by the Editor Level Transform column, to get the current values. @return			The current value of the Level Yaw.
- L97 _private prototype_ `bool LevelViewportTransformAllowed() const;` — @return Whether we can edit level transform in a viewport
- L100 _private prototype_ `bool LevelEditTextTransformAllowed() const;` — @return Whether we can edit level transform through property editor text fields
- L103 _private prototype_ `FReply OnEditLevelClicked();` — Handle for edit level transform button
- L106 _private prototype_ `void OnGenerateElementForEditorStreamingVolume(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder);` — Generate custom widget for the EditorStreamingVolumes array customization
- L109 _private prototype_ `bool OnShouldSetEditorStreamingVolume(const FAssetData& AssetData, TSharedRef<IPropertyHandle> ElementProperty) const;` — Called to determine whether the selected streaming volume can be set or not
- L114 _private prototype_ `void OnCopy(ELevelTransformField::Type TransformField);` — Copies the specified transform field to the clipboard
- L119 _private prototype_ `void OnPaste(ELevelTransformField::Type TransformField);` — Pastes the specified transform field from the clipboard
- L124 _private prototype_ `FUIAction CreateCopyAction(ELevelTransformField::Type TransformField) const;` — Creates a UI action for copying a specified transform field
- L129 _private prototype_ `FUIAction CreatePasteAction(ELevelTransformField::Type TransformField) const;` — Creates a UI action for pasting a specified transform field
- L132 _private member_ `TWeakPtr<FStreamingLevelCollectionModel> WorldModel;`
- L133 _private member_ `TSharedPtr<class IPropertyHandle> LevelPositionProperty;`
- L134 _private member_ `TSharedPtr<class IPropertyHandle> LevelRotationProperty;`
- L135 _private member_ `bool bSliderMovement;`
- L136 _private member_ `TOptional<int32> CachedYawValue;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ELevelTransformField`

### `Source/Editor/WorldBrowser/Private/StreamingLevels/StreamingLevelEdMode.h` (Private)


#### class `FStreamingLevelEdMode`  
`class FStreamingLevelEdMode : public FEdMode`  
_L15-75_
- inherits: `FEdMode`
- L20 _public prototype_ `FStreamingLevelEdMode();` — Constructor
- L23 _public prototype_ `virtual ~FStreamingLevelEdMode();` — Destructor
- L26 _public prototype_ `virtual void Enter() override;`
- L27 _public prototype_ `virtual void Exit() override;`
- L29 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L31 _public prototype_ `virtual EAxisList::Type GetWidgetAxisToDraw( UE::Widget::EWidgetMode InWidgetMode ) const override;`
- L33 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L35 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L37 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L39 _public function_ `virtual bool AllowWidgetMove() override`
- L41 _public prototype_ `virtual bool InputDelta( FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale ) override;`
- L43 _public prototype_ `virtual void Render( const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI ) override;`
- L45 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L47 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L49 _public prototype_ `virtual bool IsSnapRotationEnabled() override;`
- L51 _public prototype_ `virtual bool SnapRotatorToGridOverride(FRotator& Rotation) override;`
- L56 _public prototype_ `void SetLevel( ULevelStreaming* Level );` — Sets the level we will be transforming
- L59 _public prototype_ `virtual bool IsEditing( ULevelStreaming* Level );` — Returns true if this is the current level were editing
- L62 _public prototype_ `void ApplyPostEditMove();` — Calls Apply Post Edit Move on all Actors in the level
- L66 _private prototype_ `void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);` — Called when level was removed from the world
- L69 _private member_ `TWeakObjectPtr<ULevelStreaming> SelectedLevel;`
- L70 _private member_ `FTransform LevelTransform;`
- L71 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BoxMaterial;`
- L72 _private member_ `FBox LevelBounds;`
- L73 _private member_ `bool bIsTracking;`
- L74 _private member_ `bool bIsDirty;`

### `Source/Editor/WorldBrowser/Private/StreamingLevels/StreamingLevelModel.h` (Private)


#### class `FStreamingLevelModel`  
`class FStreamingLevelModel : public FLevelModel , public FEditorUndoClient`  
_L19-80_
- inherits: `FLevelModel,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a single streaming level
- L32 _public prototype_ `FStreamingLevelModel(FStreamingLevelCollectionModel& InWorldData, class ULevelStreaming* InLevelStreaming);` — FStreamingLevelModel Constructor @param	InEditor			The UEditorEngine to use @param	InWorldData			Level collection owning this model @param	InLevelStreaming	Streaming object this model should represent
- L33 _public prototype_ `~FStreamingLevelModel();`
- L38 _public prototype_ `virtual bool HasValidPackage() const override;` — FLevelModel interface
- L39 _public prototype_ `virtual UObject* GetNodeObject() override;`
- L40 _public prototype_ `virtual ULevel* GetLevelObject() const override;`
- L41 _public prototype_ `virtual FName GetAssetName() const override;`
- L42 _public prototype_ `virtual FName GetLongPackageName() const override;`
- L43 _public prototype_ `virtual void UpdateAsset(const FAssetData& AssetData) override;`
- L44 _public prototype_ `virtual FLinearColor GetLevelColor() const override;`
- L45 _public prototype_ `virtual void SetLevelColor(FLinearColor InColor) override;`
- L46 _public prototype_ `virtual void Update() override;`
- L47 _public prototype_ `virtual void OnDrop(const TSharedPtr<FLevelDragDropOp>& Op) override;`
- L48 _public prototype_ `virtual bool IsGoodToDrop(const TSharedPtr<FLevelDragDropOp>& Op) const override;`
- L49 _public prototype_ `virtual bool IsTransient() const override;`
- L50 _public prototype_ `virtual UClass* GetStreamingClass() const override;`
- L51 _public prototype_ `FName GetFolderPath() const override;`
- L52 _public prototype_ `virtual void SetFolderPath(const FName& InFolderPath) override;`
- L53 _public function_ `virtual bool HasFolderSupport() const override`
- L57 _public prototype_ `const TWeakObjectPtr< ULevelStreaming > GetLevelStreaming();` — @return The ULevelStreaming this viewmodel contains
- L60 _public prototype_ `void SetStreamingClass( UClass *LevelStreamingClass );` — Sets the Level's streaming class
- L64 _private prototype_ `void UpdatePackageFileAvailability();` — Updates cached value of package file availability
- L67 _private function_ `virtual void PostUndo(bool bSuccess) override`
- L68 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L73 _private member_ `TArray< FLayerActorStats > ActorStats;` — The Actor stats of the Level
- L76 _private member_ `TWeakObjectPtr< ULevelStreaming > LevelStreaming;` — The LevelStreaming this object represents
- L79 _private member_ `bool bHasValidPackageName;` — Whether underlying streaming level object has a valid package name

### `Source/Editor/WorldBrowser/Private/Tiles/STiledLandscapeImportDlg.h` (Private)


#### class `STiledLandscapeImportDlg`  
`class STiledLandscapeImportDlg : public SCompoundWidget`  
_L19-126_
- inherits: `SCompoundWidget`
- desc: STiledLandscapeImportDlg
- L32 _public function_ `SLATE_BEGIN_ARGS( STiledLandscapeImportDlg )`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SWindow> InParentWindow);`
- L39 _public prototype_ `bool ShouldImport() const;`
- L40 _public prototype_ `const FTiledLandscapeImportSettings& GetImportSettings() const;`
- L44 _private prototype_ `TSharedRef<SWidget> HandleTileConfigurationComboBoxGenarateWidget(TSharedPtr<FTileImportConfiguration> InItem) const;`
- L45 _private prototype_ `FText GetTileConfigurationText() const;`
- L48 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForLayerDataListView(TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings> InLayerData, const TSharedRef<STableViewBase>& OwnerTable);`
- L51 _private prototype_ `TOptional<float> GetScaleX() const;`
- L52 _private prototype_ `TOptional<float> GetScaleY() const;`
- L53 _private prototype_ `TOptional<float> GetScaleZ() const;`
- L54 _private prototype_ `void OnSetScale(float InValue, ETextCommit::Type CommitType, int32 InAxis);`
- L57 _private prototype_ `TOptional<int32> GetTileOffsetX() const;`
- L58 _private prototype_ `TOptional<int32> GetTileOffsetY() const;`
- L59 _private prototype_ `void SetTileOffsetX(int32 InValue);`
- L60 _private prototype_ `void SetTileOffsetY(int32 InValue);`
- L63 _private prototype_ `ECheckBoxState GetFlipYAxisState() const;`
- L64 _private prototype_ `void OnFlipYAxisStateChanged(ECheckBoxState NewState);`
- L67 _private prototype_ `void OnSetImportConfiguration(TSharedPtr<FTileImportConfiguration> InTileConfig, ESelectInfo::Type SelectInfo);`
- L70 _private prototype_ `bool IsImportEnabled() const;`
- L73 _private prototype_ `FReply OnClickedSelectHeightmapTiles();`
- L74 _private prototype_ `FReply OnClickedSelectWeightmapTiles(TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings> InLayerData);`
- L75 _private prototype_ `FReply OnClickedImport();`
- L76 _private prototype_ `FReply OnClickedCancel();`
- L79 _private prototype_ `FString GetLandscapeMaterialPath() const;`
- L80 _private prototype_ `void OnLandscapeMaterialChanged(const FAssetData& AssetData);`
- L83 _private prototype_ `FText GetImportSummaryText() const;`
- L84 _private prototype_ `FText GetWeightmapCountText(TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings> InLayerData) const;`
- L87 _private prototype_ `ECheckBoxState GetLayerBlendState(TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings> InLayerData) const;`
- L88 _private prototype_ `void OnLayerBlendStateChanged(ECheckBoxState NewState, TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings> InLayerData);`
- L91 _private prototype_ `int32 SetPossibleConfigurationsForFileWidth(int64 TargetFileWidth);`
- L94 _private prototype_ `void GenerateAllPossibleTileConfigurations();`
- L97 _private prototype_ `FText GenerateConfigurationText(int32 NumComponents, int32 NumSectionsPerComponent, int32 NumQuadsPerSection) const;`
- L100 _private prototype_ `void UpdateLandscapeLayerList();`
- L104 _private member_ `bool bShouldImport;`
- L107 _private member_ `mutable FText StatusMessage;`
- L110 _private member_ `TSharedPtr<SWindow> ParentWindow;`
- L113 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FTileImportConfiguration>>> TileConfigurationComboBox;`
- L115 _private member_ `TSharedPtr<SListView<TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings>>> LayerDataListView;`
- L116 _private member_ `TArray<TSharedPtr<FTiledLandscapeImportSettings::LandscapeLayerSettings>> LayerDataList;`
- L119 _private member_ `FTiledLandscapeImportSettings ImportSettings;`
- L122 _private member_ `FIntRect TotalLandscapeRect;`
- L124 _private member_ `TArray<FTileImportConfiguration> AllConfigurations;`
- L125 _private member_ `TArray<TSharedPtr<FTileImportConfiguration>> ActiveConfigurations;`

#### struct `STiledLandscapeImportDlg::FTileImportConfiguration`  
`struct FTileImportConfiguration`  
_L24-30_
- L26 _public member_ `int32 SizeX;`
- L27 _public member_ `int32 NumComponents;`
- L28 _public member_ `int32 NumSectionsPerComponent;`
- L29 _public member_ `int32 NumQuadsPerSection;`

### `Source/Editor/WorldBrowser/Private/Tiles/SWorldComposition.h` (Private)


#### class `SWorldComposition`  
`class SWorldComposition : public SCompoundWidget`  
_L17-69_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SWorldComposition) :_InWorld(nullptr)`
- L24 _public prototype_ `SLATE_ARGUMENT(UWorld*, InWorld) SLATE_END_ARGS() SWorldComposition();`
- L28 _public prototype_ `~SWorldComposition();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void OnBrowseWorld(UWorld* InWorld);`
- L37 _private prototype_ `TSharedRef<SWidget> ConstructContentWidget();`
- L40 _private prototype_ `void PopulateLayersList();` — Populate current FWorldTileLayer list to UI
- L43 _private prototype_ `FReply NewLayer_Clicked();` — Creates a popup window with New layer parameters
- L46 _private prototype_ `FReply CreateNewLayer(const FWorldTileLayer& NewLayer);` — Creates a new managed layer
- L49 _private prototype_ `FText GetZoomText() const;` — Top status bar details
- L50 _private prototype_ `FText GetCurrentOriginText() const;`
- L51 _private prototype_ `FText GetCurrentLevelText() const;`
- L54 _private prototype_ `FText GetMouseLocationText() const;` — Bottom status bar details
- L55 _private prototype_ `FText GetMarqueeSelectionSizeText() const;`
- L56 _private prototype_ `FText GetWorldSizeText() const;`
- L59 _private prototype_ `EVisibility IsSimulationVisible() const;` — @return whether SIMULATION sign should be visible
- L62 _private member_ `TSharedPtr<class FWorldTileCollectionModel> TileWorldModel;`
- L64 _private member_ `TSharedPtr<SBorder> ContentParent;`
- L65 _private member_ `TSharedPtr<SWrapBox> LayersListWrapBox;`
- L66 _private member_ `TSharedPtr<SButton> NewLayerButton;`
- L67 _private member_ `TWeakPtr<class IMenu> NewLayerMenu;`
- L68 _private member_ `TSharedPtr<class SWorldCompositionGrid> GridView;`

### `Source/Editor/WorldBrowser/Private/Tiles/SWorldLayers.h` (Private)


#### class `SWorldLayerButton`  
`class SWorldLayerButton : public SCompoundWidget`  
_L19-43_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SWorldLayerButton)`
- L26 _public prototype_ `SLATE_ARGUMENT(FWorldTileLayer, WorldLayer) SLATE_ARGUMENT(TSharedPtr<FWorldTileCollectionModel>, InWorldModel) SLATE_END_ARGS() ~SWorldLayerButton();` — Data for the asset this item represents
- L31 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `void OnCheckStateChanged(ECheckBoxState NewState);`
- L33 _public prototype_ `ECheckBoxState IsChecked() const;`
- L34 _public prototype_ `FReply OnDoubleClicked();`
- L35 _public prototype_ `FReply OnCtrlClicked();`
- L36 _public prototype_ `TSharedRef<SWidget> GetRightClickMenu();`
- L37 _public prototype_ `FText GetToolTipText() const;`
- L41 _private member_ `TSharedPtr<FWorldTileCollectionModel> WorldModel;` — The data for this item
- L42 _private member_ `FWorldTileLayer WorldLayer;`

#### class `SNewWorldLayerPopup`  
`class SNewWorldLayerPopup : public SBorder`  
_L46-117_
- inherits: `SBorder`
- L50 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnCreateLayer, const FWorldTileLayer&) SLATE_BEGIN_ARGS(SNewWorldLayerPopup)`
- L54 _public prototype_ `SLATE_EVENT(FOnCreateLayer, OnCreateLayer) SLATE_ARGUMENT(FString, DefaultName) SLATE_ARGUMENT(TSharedPtr<FWorldTileCollectionModel>, InWorldModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L61 _public function_ `TOptional<int32> GetStreamingDistance() const`
- L66 _public function_ `ECheckBoxState GetDistanceStreamingState() const`
- L71 _public function_ `bool IsDistanceStreamingEnabled() const`
- L76 _public function_ `void OnDistanceStreamingStateChanged(ECheckBoxState NewState)`
- L81 _public function_ `FText GetLayerName() const`
- L87 _private prototype_ `FReply OnClickedCreate();`
- L89 _private prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type CommitType);`
- L90 _private prototype_ `void OnDistanceCommitted(int32 InValue, ETextCommit::Type CommitType);`
- L93 _private prototype_ `FReply TryCreateLayer();` — Try to create a new streaming layer
- L95 _private prototype_ `bool CanCreateLayer() const;`
- L97 _private function_ `void SetLayerName(const FText& InText)`
- L102 _private function_ `void SetStreamingDistance(int32 InValue)`
- L107 _private function_ `void SetDistanceStreamingState(bool bIsEnabled)`
- L114 _private member_ `FOnCreateLayer OnCreateLayer;` — The delegate to execute when the create button is clicked
- L115 _private member_ `FWorldTileLayer LayerData;`
- L116 _private member_ `TSet<FString> ExistingLayerNames;`

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnCreateLayer, const FWorldTileLayer&) SLATE_BEGIN_ARGS(SNewWorldLayerPopup) {} SLATE_EVENT(FOnCreateLayer, OnCreateLayer) SLATE_ARGUMENT(FString, DefaultName) SLATE_ARGUMENT(TSharedPtr<FWorldTileCollectionModel>, InWorldModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Source/Editor/WorldBrowser/Private/Tiles/SWorldTileItem.h` (Private)


#### class `SWorldTileImage`  
`class SWorldTileImage : public SImage`  
_L25-43_
- inherits: `SImage`
- L27 _private function_ `SLATE_BEGIN_ARGS(SWorldTileImage) : _EditableTile(false)`
- L34 _public function_ `void Construct(const FArguments& InArgs)`
- L39 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L42 _private member_ `TAttribute<bool> EditableTile;`

#### class `SWorldTileItem`  
`class SWorldTileItem : public SNodePanel::SNode`  
_L49-131_
- inherits: `SNodePanel::SNode`
- L53 _public function_ `SLATE_BEGIN_ARGS(SWorldTileItem)`
- L56 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FWorldTileCollectionModel>, InWorldModel) SLATE_ARGUMENT(TSharedPtr<FWorldTileModel>, InItemModel) SLATE_ARGUMENT(TSharedPtr<FTileThumbnailCollection>, InThumbnailCollection) SLATE_END_ARGS() SWorldTileItem();` — The world data
- L64 _public prototype_ `~SWorldTileItem();`
- L66 _public prototype_ `void Construct(const FArguments& InArgs);`
- L69 _public prototype_ `virtual FVector2f GetDesiredSizeForMarquee2f() const override;` — SNodePanel::SNode interface start
- L70 _public prototype_ `virtual UObject* GetObjectBeingDisplayed() const override;`
- L71 _public prototype_ `virtual FVector2f GetPosition2f() const override;`
- L72 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L73 _public prototype_ `virtual void GetDiffHighlightBrushes(const FSlateBrush*& BackgroundOut, const FSlateBrush*& ForegroundOut) const override;`
- L77 _public prototype_ `void RequestRefresh();` — @return Deferred item refresh
- L80 _public prototype_ `TSharedPtr<FLevelModel> GetLevelModel() const;` — @return LevelModel associated with this item
- L83 _public prototype_ `FOptionalSize GetItemWidth() const;` — @return Item width in world units
- L86 _public prototype_ `FOptionalSize GetItemHeight() const;` — @return Item height in world units
- L89 _public prototype_ `FSlateRect GetItemRect() const;` — @return Rectangle in world units for this item as FSlateRect
- L92 _public prototype_ `bool IsItemEditable() const;` — @return Whether this item can be edited (loaded and not locked)
- L95 _public prototype_ `bool IsItemSelected() const;` — @return Whether this item is selected
- L98 _public prototype_ `bool IsItemEnabled() const;` — @return Whether this item is enabled
- L102 _private prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() override;` — SWidget interface start
- L103 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L104 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L105 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L108 _private prototype_ `TSharedRef<SToolTip> CreateToolTipWidget();`
- L111 _private prototype_ `FText GetLevelNameText() const;` — Tile tooltips fields
- L112 _private prototype_ `FText GetPositionText() const;`
- L113 _private prototype_ `FText GetBoundsExtentText() const;`
- L114 _private prototype_ `FText GetLevelLayerNameText() const;`
- L115 _private prototype_ `FText GetLevelLayerDistanceText() const;`
- L118 _public member_ `bool bAffectedByMarquee;`
- L122 _private member_ `TSharedPtr<FWorldTileCollectionModel> WorldModel;` — The world data
- L124 _private member_ `TSharedPtr<FWorldTileModel> TileModel;` — The data for this item
- L126 _private member_ `TSharedPtr<SWorldTileImage> ThumbnailImageWidget;`
- L127 _private member_ `TSharedPtr<FTileThumbnailCollection> ThumbnailCollection;`
- L129 _private member_ `mutable bool bNeedRefresh;`
- L130 _private member_ `bool bIsDragging;`

### `Source/Editor/WorldBrowser/Private/Tiles/WorldTileCollectionModel.h` (Private)


#### class `FWorldTileCollectionModel`  
`class FWorldTileCollectionModel : public FLevelCollectionModel , public FEditorUndoClient`  
_L14-283_
- inherits: `FLevelCollectionModel,FEditorUndoClient`
- desc: The non-UI solution specific presentation logic for a world composition
- L21 _public prototype_ `virtual ~FWorldTileCollectionModel();` — FWorldTileCollectionModel destructor
- L28 _public function_ `static TSharedRef<FWorldTileCollectionModel> Create(UWorld* InWorld)` — Factory method which creates a new FWorldTileCollectionModel object @param	InEditor		The UEditorEngine to use
- L36 _public prototype_ `virtual void UnloadLevels(const FLevelModelList& InLevelList) override;` — FLevelCollection interface
- L37 _public prototype_ `virtual void TranslateLevels(const FLevelModelList& InList, FVector2D InAbsoluteDelta, bool bSnapDelta = true) override;`
- L38 _public prototype_ `virtual FVector2D SnapTranslationDelta(const FLevelModelList& InList, FVector2D InTranslationDelta, bool bBoundsSnapping, FVector2D::FReal InSnappingValue) override;`
- L39 _public prototype_ `virtual TSharedPtr<WorldHierarchy::FWorldBrowserDragDropOp> CreateDragDropOp() const override;`
- L40 _public prototype_ `virtual TSharedPtr<WorldHierarchy::FWorldBrowserDragDropOp> CreateDragDropOp(const FLevelModelList& InLevels) const override;`
- L41 _public prototype_ `virtual bool PassesAllFilters(const FLevelModel& InLevelModel) const override;`
- L42 _public prototype_ `virtual void BuildHierarchyMenu(FMenuBuilder& InMenuBuilder, EBuildHierarchyMenuFlags Flags) const override;`
- L43 _public prototype_ `virtual void CustomizeFileMainMenu(FMenuBuilder& InMenuBuilder) const override;`
- L44 _public prototype_ `virtual bool GetPlayerView(FVector& Location, FRotator& Rotation) const override;`
- L45 _public prototype_ `virtual bool GetObserverView(FVector& Location, FRotator& Rotation) const override;`
- L46 _public prototype_ `virtual bool CompareLevelsZOrder(TSharedPtr<FLevelModel> InA, TSharedPtr<FLevelModel> InB) const override;`
- L47 _public prototype_ `virtual void RegisterDetailsCustomization(class FPropertyEditorModule& PropertyModule, TSharedPtr<class IDetailsView> InDetailsView) override;`
- L48 _public prototype_ `virtual void UnregisterDetailsCustomization(class FPropertyEditorModule& PropertyModule, TSharedPtr<class IDetailsView> InDetailsView) override;`
- L49 _public function_ `virtual bool IsTileWorld() const override`
- L54 _private prototype_ `void Tick( float DeltaTime ) override;` — FTickableEditorObject interface
- L58 _private prototype_ `virtual void Initialize(UWorld* InWorld) override;` — FLevelCollection interface
- L59 _private prototype_ `virtual void BindCommands() override;`
- L60 _private prototype_ `virtual void OnLevelsCollectionChanged() override;`
- L61 _private prototype_ `virtual void OnLevelsSelectionChanged() override;`
- L62 _private prototype_ `virtual void OnLevelsHierarchyChanged() override;`
- L63 _private prototype_ `virtual void OnPreLoadLevels(const FLevelModelList& InList) override;`
- L64 _private prototype_ `virtual void OnPreShowLevels(const FLevelModelList& InList) override;`
- L69 _public prototype_ `bool HasWorldRoot() const;` — @return	Whether world browser has world root opened
- L72 _public prototype_ `TSharedPtr<FWorldTileModel> GetWorldRootModel();` — Returns TileModel which is used as root for all tiles
- L75 _public prototype_ `void DeselectLevels(const FWorldTileLayer& InLayer);` — Removes selection from levels which belongs to provided Layer
- L78 _public prototype_ `bool AreAnyLayersSelected() const;` — @return	whether at least one layer is selected
- L83 _public prototype_ `void ShelveLevels(const FWorldTileModelList& InLevels);` — Hide a levels from the editor and move them to original position Similar to unloading level, but does not removes it from the memory
- L86 _public prototype_ `void UnshelveLevels(const FWorldTileModelList& InLevels);` — Show a levels in the editor and place them to actual world position
- L89 _public prototype_ `bool AreAnySelectedLevelsHaveLandscape() const;` — Whether any of the currently selected levels have landscape actor
- L94 _public prototype_ `TSharedPtr<FLevelModel> CreateNewEmptyLevel();` — Creates a new empty level @return LevelModel of a new empty level
- L97 _public prototype_ `TArray<FWorldTileLayer>& GetLayers();` — Returns all layers found in the world
- L100 _public prototype_ `void AddLayer(const FWorldTileLayer& InLayer);` — Adds unique runtime layer to the world
- L103 _public prototype_ `void AddManagedLayer(const FWorldTileLayer& InLayer);` — Adds unique managed layer to the world
- L106 _public prototype_ `void SetSelectedLayer(const FWorldTileLayer& InLayer);` — Sets provided layer as selected
- L109 _public prototype_ `void SetSelectedLayers(const TArray<FWorldTileLayer>& InLayers);` — Sets provided layers list as selected
- L112 _public prototype_ `void ToggleLayerSelection(const FWorldTileLayer& InLayer);` — Toggles provided layer selection
- L115 _public prototype_ `bool IsLayerSelected(const FWorldTileLayer& InLayer);` — Return whether provides layer is selected or not
- L118 _public prototype_ `void OnLevelLoadedFromDisk(TSharedPtr<FWorldTileModel> InLevel);` — Notification that level object was loaded from disk
- L121 _public prototype_ `void UpdateStreamingPreview(FVector2D InPreviewLocation, bool bEnabled);` — Notification that "view point" for streaming levels visibility preview was changed
- L124 _public prototype_ `const TMap<FName, int32>& GetPreviewStreamingLevels() const;` — Returns list of visible streaming levels for current preview location
- L127 _public prototype_ `FVector2D SnapTranslationDeltaLandscape(const TSharedPtr<FWorldTileModel>& LandscapeTile, FVector2D InAbsoluteDelta, float SnappingDistance);` — Calculates snapped moving delta based on specified landscape tile
- L132 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L133 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L147 _public prototype_ `void Focus(FBox InArea, FocusStrategy InStaragegy);` — Tell the browser that user is focusing on this area in world This may cause world origin shifting and subsequent shelving/unshelving operations
- L152 _public prototype_ `void BuildWorldCompositionMenu(FMenuBuilder& InMenuBuilder) const;` — Builds context menu for a world composition
- L155 _private prototype_ `FWorldTileCollectionModel();`
- L158 _private prototype_ `void SetupParentChildLinks();` — Setups parent->child links between tiles
- L161 _private prototype_ `void OnPreSaveWorld(class UWorld* World, FObjectPreSaveContext ObjectSaveContext);` — Called before saving world into package file
- L164 _private prototype_ `void OnPostSaveWorld(class UWorld* World, FObjectPostSaveContext ObjectSaveContext);` — Called right after world was saved into package file
- L167 _private prototype_ `void OnNewCurrentLevel();` — Called when world has new current level
- L170 _private prototype_ `TSharedPtr<FWorldTileModel> GetCorrespondingModel(ULevel* InLevel);` — @return shared pointer to FStreamingLevelModel associated with provided ULevel object
- L175 _private prototype_ `void PrepareToLoadLevels(FWorldTileModelList& InLevels);` — Moves world origin closer to levels which are going to be loaded and unloads levels which are far enough from new world origin
- L178 _private prototype_ `void PreWorldOriginOffset(UWorld* InWorld, FIntVector InSrcOrigin, FIntVector InDstOrigin);` — Delegate callback: the world origin is going to be moved.
- L181 _private prototype_ `void PostWorldOriginOffset(UWorld* InWorld, FIntVector InSrcOrigin, FIntVector InDstOrigin);` — Delegate callback: the world origin has been moved.
- L184 _private prototype_ `void PopulateLayersList();` — Update list layers
- L187 _private prototype_ `void MoveWorldOrigin(const FIntPoint& InOrigin2D);` — Scrolls world origin to specified position
- L192 _private prototype_ `bool AddLevelToTheWorld(const TSharedPtr<FWorldTileModel>& InLevel);` — Adds a loaded level to the world and makes it visible if possible @return Whether level was added to the world
- L195 _private prototype_ `void FillLayersSubMenu(FMenuBuilder& InMenuBuilder) const;` — Fills Layers sub-menu
- L198 _private prototype_ `void FillAdjacentLandscapeSubMenu(FMenuBuilder& InMenuBuilder) const;` — Fills adjacent landscape sub-menu
- L201 _private prototype_ `void FillReimportTiledLandscapeSubMenu(FMenuBuilder& InMenuBuilder) const;` — Fills reimport tiled landscape sub-menu
- L204 _private prototype_ `void FillWeightmapsSubMenu(FMenuBuilder& InMenuBuilder) const;` — Fills reimport weightmaps sub_menu
- L208 _private prototype_ `void CreateNewLevel_Executed();` — Creates a new level; prompts for level save location
- L211 _private prototype_ `void MoveWorldOrigin_Executed();` — Moves world origin to selected level position
- L214 _private prototype_ `void ResetWorldOrigin_Executed();` — Reset world origin offset
- L217 _private prototype_ `void ResetLevelOrigin_Executed();` — Reset world origin offset
- L220 _private prototype_ `void ClearParentLink_Executed();` — Clear parent links fro selected levels
- L226 _private prototype_ `void AddLandscapeProxy_Executed(FWorldTileModel::EWorldDirections InWhere);` — Creates a new Level with landscape proxy in it @param InWhere  Defines on which side of currently selected landscape level
- L229 _private prototype_ `bool CanAddLandscapeProxy(FWorldTileModel::EWorldDirections InWhere) const;` — @return whether it is possible to add a level with landscape proxy at specified location
- L232 _private prototype_ `bool CanReimportTiledlandscape() const;` — @return Whether selection contains tiles with tiled landscape
- L235 _private prototype_ `void ImportTiledLandscape_Executed();`
- L238 _private prototype_ `void ReimportTiledLandscape_Executed(FName TargetLayer);`
- L241 _private prototype_ `void OnToggleLockTilesLocation();` — Tiles location locking
- L243 _public prototype_ `bool IsLockTilesLocationEnabled();`
- L247 _public prototype_ `bool HasMeshProxySupport() const;` — Whether Editor has support for generating static mesh proxies
- L254 _public prototype_ `bool GenerateLODLevels(FLevelModelList InLevelList, int32 TargetLODIndex);` — Generates simplified versions of a specified levels. Levels has to be loaded. Currently all static meshes found inside one level will be merged into one proxy mesh using Simplygon ProxyLOD Landscape actors will be converted into static meshes using highest landscape LOD entry
- L257 _public prototype_ `void AssignSelectedLevelsToLayer_Executed(FWorldTileLayer InLayer);` — Assign selected levels to current layer
- L261 _private member_ `FLevelModelList StaticTileList;` — List of tiles currently not affected by user selection set
- L264 _private member_ `TMap<FName, int32> PreviewVisibleTiles;` — Cached streaming tiles which are potentially visible from specified view point
- L267 _private member_ `FVector PreviewLocation;` — View point location for calculating potentially visible streaming tiles
- L270 _private member_ `TArray<FWorldTileLayer> AllLayers;` — All layers
- L273 _private member_ `TArray<FWorldTileLayer> ManagedLayers;` — All layers currently created by the user
- L276 _private member_ `TArray<FWorldTileLayer> SelectedLayers;` — All selected layers
- L279 _private member_ `bool bIsSavingLevel;` — Is in process of saving a level
- L282 _private member_ `bool bMeshProxyAvailable;` — Whether Editor has support for mesh proxy

#### enum `FWorldTileCollectionModel::FocusStrategy`  
`enum FocusStrategy`  
_L136-141_
- L138 _public enumerator_ `OriginAtCenter` — Unconditionally move current world origin to specified area center
- L139 _public enumerator_ `EnsureEditable` — May move world origin such that specified area become editable
- L140 _public enumerator_ `EnsureEditableCentered` — May move world origin such that specified area become editable and centered in world

### `Source/Editor/WorldBrowser/Private/Tiles/WorldTileDetails.h` (Private)


#### struct `FTileLODEntryDetails`  
`struct FTileLODEntryDetails`  
_L22-38_
- reflection: `USTRUCT()`
- desc: FTileLODEntryDetails Helper class to hold tile LOD level description
- L28 _public member_ `int32 LODIndex;` — `UPROPERTY(Category=LODDetails, VisibleAnywhere)` — Maximum deviation of details percentage
- L32 _public member_ `int32 RelativeDistance;` — `UPROPERTY(Category=LODDetails, EditAnywhere, meta=(ClampMin = "10", ClampMax = "10000000", UIMin = "10", UIMax = "500000"))` — Relative to original tile streaming distance (Absolute Distance = Layer Streaming Distance + Relative Distance)
- L35 _public member_ `FLevelSimplificationDetails SimplificationDetails;` — `UPROPERTY(Category=ReductionSettings, EditAnywhere)`
- L37 _public prototype_ `FTileLODEntryDetails();`

#### class `UWorldTileDetails`  
`class UWorldTileDetails : public UObject`  
_L47-125_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: UWorldTileDetails Helper class to hold world tile information Holding this information in UObject gives us ability to use property editors and support undo operations
- L53 _private member_ `bool bTileEditable;` — `UPROPERTY(Category=Tile, VisibleAnywhere)` — Whether this tile properties can be edited via details panel
- L57 _private member_ `FName PackageName;` — `UPROPERTY(Category=Tile, VisibleAnywhere)` — Tile long package name (readonly)
- L61 _private member_ `FName ParentPackageName;` — `UPROPERTY(Category=Tile, EditAnywhere)` — Parent tile long package name
- L65 _private member_ `FIntVector Position;` — `UPROPERTY(Category=Tile, EditAnywhere)` — Tile position in the world, relative to parent
- L69 _private member_ `FIntVector AbsolutePosition;` — `UPROPERTY(Category=Tile, VisibleAnywhere)` — Tile absolute position in the world (readonly)
- L73 _private member_ `int32 ZOrder;` — `UPROPERTY(Category=Tile, EditAnywhere, meta=(ClampMin = "-1000", ClampMax = "1000", UIMin = "-1000", UIMax = "1000"))` — Tile sorting order
- L77 _private member_ `bool bHideInTileView;` — `UPROPERTY(Category=Tile, EditAnywhere)` — Whether to hide tile in the world composition tile view
- L81 _private member_ `int32 NumLOD;` — `UPROPERTY(Category=LODSettings, EditAnywhere, meta=(ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))` — LOD entries number
- L84 _private member_ `FTileLODEntryDetails LOD1;` — `UPROPERTY(Category=LODSettings, EditAnywhere)`
- L87 _private member_ `FTileLODEntryDetails LOD2;` — `UPROPERTY(Category=LODSettings, EditAnywhere)`
- L90 _private member_ `FTileLODEntryDetails LOD3;` — `UPROPERTY(Category=LODSettings, EditAnywhere)`
- L93 _private member_ `FTileLODEntryDetails LOD4;` — `UPROPERTY(Category=LODSettings, EditAnywhere)`
- L96 _private member_ `FWorldTileLayer Layer;` — Tile layer information
- L99 _private member_ `FBox Bounds;` — Tile bounds
- L102 _private member_ `bool bPersistentLevel;` — Whether this tile is a persistent level
- L105 _private prototype_ `DECLARE_EVENT( UWorldTileDetails, FTilePropertyChanged ) FTilePropertyChanged PostUndoEvent;` — Events when user edits tile properties
- L108 _private member_ `FTilePropertyChanged PositionChangedEvent;`
- L109 _private member_ `FTilePropertyChanged ParentPackageNameChangedEvent;`
- L110 _private member_ `FTilePropertyChanged LODSettingsChangedEvent;`
- L111 _private member_ `FTilePropertyChanged ZOrderChangedEvent;`
- L112 _private member_ `FTilePropertyChanged HideInTileViewChangedEvent;`
- L115 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L116 _private prototype_ `virtual void PostEditUndo() override;`
- L120 _public prototype_ `void SetInfo(const FWorldTileInfo& Info, ULevel* Level);` — Initialize tile details with values stored in FWorldTileInfo object
- L123 _public prototype_ `FWorldTileInfo GetInfo() const;` — Gets the initialized FWorldTileInfo from this details values

#### Free symbols / members of external scopes

- L105 _delegate_ `DECLARE_EVENT( UWorldTileDetails, FTilePropertyChanged ) FTilePropertyChanged PostUndoEvent;` — Events when user edits tile properties

### `Source/Editor/WorldBrowser/Private/Tiles/WorldTileDetailsCustomization.h` (Private)


#### class `FWorldTileDetailsCustomization`  
`class FWorldTileDetailsCustomization : public IDetailCustomization`  
_L16-39_
- inherits: `IDetailCustomization`
- desc: FWorldTileDetailsCustomization
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedRef<FWorldTileCollectionModel> InWorldData);` — Makes a new instance of this detail layout class
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L27 _private prototype_ `bool IsPropertyEditable() const;` — Whether property should be editable (depends on level load status and level lock status)
- L30 _private prototype_ `EVisibility GetLODPropertyVisibility(int LODIndex) const;` — Whether LOD entry property should be visible (depends on LOD entries num)
- L33 _private prototype_ `bool OnShouldFilterParentPackage(const FString& PackageName);` — Whether a particular package should be filtered out from a parent level package property editor
- L36 _private member_ `TSharedPtr<IPropertyHandle> NumLODHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> TileEditableHandle;`
- L38 _private member_ `TWeakPtr<FWorldTileCollectionModel> WorldModel;`

#### class `FStreamingLevelDetailsCustomization`  
`class FStreamingLevelDetailsCustomization : public IPropertyTypeCustomization`  
_L43-57_
- inherits: `IPropertyTypeCustomization`
- desc: FStreamingLevelDetailsCustomization
- L46 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedRef<FWorldTileCollectionModel> InWorldData);`
- L49 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L50 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L53 _private prototype_ `bool OnShouldFilterStreamingPackage(const FString& InPackageName) const;`
- L56 _private member_ `TWeakPtr<FWorldTileCollectionModel> WorldModel;`

#### class `FTileLODEntryDetailsCustomization`  
`class FTileLODEntryDetailsCustomization : public IPropertyTypeCustomization`  
_L61-78_
- inherits: `IPropertyTypeCustomization`
- desc: FTileLODEntryDetailsCustomization
- L64 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedRef<FWorldTileCollectionModel> InWorldData);`
- L67 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L68 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L71 _private prototype_ `FReply OnGenerateTile();`
- L72 _private prototype_ `bool IsGenerateTileEnabled() const;`
- L73 _private prototype_ `bool IsLODDistanceEnabled() const;`
- L76 _private member_ `TWeakPtr<FWorldTileCollectionModel> WorldModel;`
- L77 _private member_ `TSharedPtr<IPropertyHandle> LODIndexHandle;`

### `Source/Editor/WorldBrowser/Private/Tiles/WorldTileModel.h` (Private)


#### class `FWorldTileModel`  
`class FWorldTileModel : public FLevelModel`  
_L28-235_
- inherits: `FLevelModel`
- desc: The non-UI presentation logic for a single Level (Tile) in world composition
- L76 _public prototype_ `FWorldTileModel(FWorldTileCollectionModel& InWorldData, int32 TileIdx);` — FWorldTileModel Constructor @param	InWorldData		WorldBrowser world data @param	TileIdx			Tile index in world composition tiles list
- L77 _public prototype_ `~FWorldTileModel();`
- L81 _public prototype_ `virtual UObject* GetNodeObject() override;` — FLevelModel interface
- L82 _public prototype_ `virtual ULevel* GetLevelObject() const override;`
- L83 _public prototype_ `virtual FName GetAssetName() const override;`
- L84 _public prototype_ `virtual FName GetLongPackageName() const override;`
- L85 _public prototype_ `virtual void Update() override;`
- L86 _public prototype_ `virtual void UpdateAsset(const FAssetData& AssetData) override;`
- L87 _public prototype_ `virtual void LoadLevel() override;`
- L88 _public prototype_ `virtual void SetVisibleInEditor(bool bVisible) override;`
- L89 _public prototype_ `virtual FVector2D GetLevelPosition2D() const override;`
- L90 _public prototype_ `virtual FVector2D GetLevelSize2D() const override;`
- L91 _public prototype_ `virtual void OnDrop(const TSharedPtr<FLevelDragDropOp>& Op) override;`
- L92 _public prototype_ `virtual bool IsGoodToDrop(const TSharedPtr<FLevelDragDropOp>& Op) const override;`
- L93 _public prototype_ `virtual void OnLevelAddedToWorld(ULevel* InLevel) override;`
- L94 _public prototype_ `virtual void OnLevelRemovedFromWorld() override;`
- L95 _public prototype_ `virtual void OnParentChanged() override;`
- L96 _public prototype_ `virtual bool IsVisibleInCompositionView() const override;`
- L97 _public prototype_ `virtual FLinearColor GetLevelColor() const override;`
- L98 _public prototype_ `virtual void SetLevelColor(FLinearColor InColor) override;`
- L102 _public prototype_ `void AddStreamingLevel(UClass* InStreamingClass, const FName& InPackageName);` — Adds new streaming level
- L105 _public prototype_ `void AssignToLayer(const FWorldTileLayer& InLayer);` — Assigns level to provided layer
- L108 _public prototype_ `bool IsRootTile() const;` — @return Whether tile is root of hierarchy
- L111 _public prototype_ `bool ShouldBeVisible(FBox EditableArea) const;` — Whether level should be visible in given area
- L114 _public prototype_ `bool IsShelved() const;` — @return Whether level is shelved
- L117 _public prototype_ `void Shelve();` — Hide a level from the editor
- L120 _public prototype_ `void Unshelve();` — Show a level in the editor
- L123 _public prototype_ `bool IsLandscapeBased() const;` — Whether this level landscape based or not
- L126 _public prototype_ `bool IsTiledLandscapeBased() const;` — `UE_DEPRECATED(4.26, "No longer used; use CanReimportHeightmap instead.")`
- L129 _public prototype_ `bool CanReimportHeightmap() const;` — Whether this level has a heightmap that can be reimported or not
- L132 _public prototype_ `bool IsLandscapeProxy() const;` — `UE_DEPRECATED(4.26, "No longer used; use IsLandscapeStreamingProxy instead.")`
- L135 _public prototype_ `bool IsLandscapeStreamingProxy() const;` — Whether this level has ALandscapeStreamingProxy or not
- L138 _public prototype_ `ALandscapeProxy* GetLandscape() const;` — @return The landscape actor in case this level is landscape based
- L141 _public prototype_ `bool IsInLayersList(const TArray<FWorldTileLayer>& InLayerList) const;` — Whether this level in provided layers list
- L144 _public prototype_ `FVector GetLevelCurrentPosition() const;` — @return Level position in shifted space
- L147 _public prototype_ `FIntVector GetRelativeLevelPosition() const;` — @return Level relative position
- L150 _public prototype_ `FIntVector GetAbsoluteLevelPosition() const;` — @return Level absolute position in non shifted space
- L153 _public prototype_ `FIntVector CalcAbsoluteLevelPosition() const;` — @return Calculates Level absolute position in non shifted space based on relative position
- L156 _public prototype_ `FBox GetLevelBounds() const override;` — @return ULevel bounding box in shifted space
- L159 _public prototype_ `void SetLevelPosition(const FIntVector& InPosition, const FIntPoint* InLandscapeSectionOffset = nullptr);` — Translate level center to new position
- L162 _public prototype_ `void SortRecursive();` — Recursively sort all children by name
- L168 _public prototype_ `ULevelStreaming* GetAssociatedStreamingLevel();` — @return associated streaming level object for this tile Creates a new object in case it does not exists in a persistent world
- L171 _public function_ `ULevelStreaming* GetAssosiatedStreamingLevel()` — `UE_DEPRECATED(4.20, "Call GetAssociatedStreamingLevel instead")`
- L174 _public prototype_ `bool CreateAdjacentLandscapeProxy(ALandscapeProxy* SourceLandscape, FWorldTileModel::EWorldDirections InWhere);`
- L177 _public prototype_ `ALandscapeProxy* ImportLandscapeTile(const FLandscapeImportSettings& Settings);`
- L181 _private prototype_ `void OnLevelInfoUpdated();` — Flush world info to package and level objects
- L184 _private prototype_ `void FixupStreamingObjects();` — Fixup invalid streaming objects inside level
- L187 _private prototype_ `void UpdateLandscapeSectionsOffset(FIntPoint LevelOffset);` — When level with landscape is moved we need to update internal landscape coordinates to match landscape component grid
- L190 _private prototype_ `void OnLevelBoundsActorUpdated();` — Handler for LevelBoundsActorUpdated event
- L193 _private prototype_ `void EnsureLevelHasBoundsActor();` — Spawns AlevelBounds actor in the level in case it doesn't has one
- L196 _private prototype_ `void OnPostUndoEvent();` — Handler for PostEditUndo
- L199 _private prototype_ `void OnPositionPropertyChanged();` — Handler for PositionChanged event from Tile details object
- L202 _private prototype_ `void OnParentPackageNamePropertyChanged();` — Handler for ParentPackageName event from Tile details object
- L205 _private prototype_ `void OnLODSettingsPropertyChanged();` — Handler for LOD settings changes event from Tile details object
- L208 _private prototype_ `void OnZOrderPropertyChanged();` — Handler for ZOrder changes event from Tile details object
- L211 _private prototype_ `void OnHideInTileViewChanged();` — Handler for bHideInTileView changes event from Tile details object
- L214 _private prototype_ `void SetAssetName(const FName& PackageName);` — Set the asset name based on the passed in package name
- L218 _public member_ `int32 TileIdx;` — This tile index in world composition tile list
- L221 _public member_ `FName AssetName;` — Package name this item represents
- L224 _public member_ `UWorldTileDetails* TileDetails;` — UObject which holds tile properties to be able to edit them via details panel
- L227 _public member_ `TWeakObjectPtr<ULevel> LoadedLevel;` — The Level this object represents
- L230 _public member_ `bool bWasShelved;` — Whether this level was shelved: hidden by World Browser decision
- L234 _private member_ `TWeakObjectPtr<ALandscapeProxy> Landscape;` — Whether level has landscape components in it

#### struct `FWorldTileModel::FCompareByLongPackageName`  
`struct FCompareByLongPackageName`  
_L32-39_
- L34 _public function_ `FORCEINLINE bool operator()(const TSharedPtr<FLevelModel>& A, const TSharedPtr<FLevelModel>& B) const`

#### enum `FWorldTileModel::EWorldDirections`  
`enum EWorldDirections`  
_L41-48_
- L43 _public enumerator_ `XNegative`
- L44 _public enumerator_ `YNegative`
- L45 _public enumerator_ `XPositive`
- L46 _public enumerator_ `YPositive`
- L47 _public enumerator_ `Any`

#### struct `FWorldTileModel::FLandscapeImportSettings`  
`struct FLandscapeImportSettings`  
_L53-68_
- L56 _public member_ `FGuid LandscapeGuid;` — Depending on landscape guid import code will spawn Landscape actor or LandscapeProxy actor
- L57 _public member_ `FTransform LandscapeTransform;`
- L58 _public member_ `UMaterialInterface* LandscapeMaterial;`
- L59 _public member_ `int32 ComponentSizeQuads;`
- L60 _public member_ `int32 SectionsPerComponent;`
- L61 _public member_ `int32 QuadsPerSection;`
- L62 _public member_ `int32 SizeX;`
- L63 _public member_ `int32 SizeY;`
- L64 _public member_ `TArray<uint16> HeightData;`
- L65 _public member_ `TArray<FLandscapeImportLayerInfo> ImportLayers;`
- L66 _public member_ `FString HeightmapFilename;`
- L67 _public member_ `ELandscapeImportAlphamapType ImportLayerType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WORLDBROWSER_API`
- L22 _typedef_ `typedef TArray<TSharedPtr<class FWorldTileModel>> FWorldTileModelList;`

### `Source/Editor/WorldBrowser/Private/Tiles/WorldTileThumbnails.h` (Private)


#### class `FTileThumbnail`  
`class FTileThumbnail`  
_L27-44_
- L30 _public prototype_ `FTileThumbnail(FSlateTextureRenderTarget2DResource* InThumbnailRenderTarget, const FWorldTileModel& InTileModel, const FIntPoint& InSlotAllocation);`
- L33 _public prototype_ `FSlateTextureDataPtr UpdateThumbnail();` — Redraw thumbnail
- L34 _public prototype_ `FIntPoint GetThumbnailSlotAllocation() const;`
- L37 _private prototype_ `FSlateTextureDataPtr ToSlateTextureData(const FObjectThumbnail* ObjectThumbnail) const;`
- L40 _private member_ `const FWorldTileModel& TileModel;`
- L42 _private member_ `FSlateTextureRenderTarget2DResource* ThumbnailRenderTarget;` — Shared render target for slate
- L43 _private member_ `FIntPoint SlotAllocation;`

#### class `FTileAtlasPage`  
`class FTileAtlasPage`  
_L50-71_
- L53 _public prototype_ `FTileAtlasPage();`
- L54 _public prototype_ `~FTileAtlasPage();`
- L56 _public prototype_ `void SetOccupied(int32 SlotIdx, bool bOccupied);`
- L57 _public prototype_ `bool HasOccupiedSlots() const;`
- L58 _public prototype_ `int32 GetFreeSlotIndex() const;`
- L59 _public prototype_ `const FSlateBrush* GetSlotBrush(int32 SlotIdx) const;`
- L60 _public prototype_ `void UpdateSlotImageData(int32 SlotIdx, FSlateTextureDataPtr ImageData);`
- L69 _private member_ `FTileAtlasSlot AtlasSlots[TileThumbnailAtlasDim*TileThumbnailAtlasDim];`
- L70 _private member_ `UTexture2DDynamic* AtlasTexture;`

#### struct `FTileAtlasPage::FTileAtlasSlot`  
`struct FTileAtlasSlot`  
_L63-67_
- L65 _public member_ `FSlateDynamicImageBrush* SlotBrush;`
- L66 _public member_ `bool bOccupied;`

#### class `FTileThumbnailCollection`  
`class FTileThumbnailCollection`  
_L77-100_
- L80 _public prototype_ `FTileThumbnailCollection();`
- L81 _public prototype_ `~FTileThumbnailCollection();`
- L83 _public prototype_ `void RegisterTile(const FWorldTileModel& InTileModel);`
- L84 _public prototype_ `void UnregisterTile(const FWorldTileModel& InTileModel);`
- L85 _public prototype_ `const FSlateBrush* UpdateTileThumbnail(const FWorldTileModel& InTileModel);`
- L86 _public prototype_ `const FSlateBrush* GetTileBrush(const FWorldTileModel& InTileModel) const;`
- L88 _public prototype_ `bool IsOnCooldown() const;`
- L91 _private prototype_ `FIntPoint AllocateSlot();`
- L92 _private prototype_ `void ReleaseSlot(const FIntPoint& InSlotAllocation);`
- L95 _private member_ `FSlateTextureRenderTarget2DResource* SharedThumbnailRT;`
- L96 _private member_ `TMap<FName, FTileThumbnail> TileThumbnailsMap;`
- L97 _private member_ `double LastThumbnailUpdateTime;`
- L99 _private member_ `TArray<FTileAtlasPage*> AtlasPages;`

#### Free symbols / members of external scopes

- L19 _variable_ `const int32 TileThumbnailSize = 256;`
- L20 _variable_ `const int32 TileThumbnailAtlasSize = 1024;`
- L21 _variable_ `const int32 TileThumbnailAtlasDim = TileThumbnailAtlasSize/TileThumbnailSize;`

### `Source/Editor/WorldBrowser/Private/WorldBrowserConfig.h` (Private)


#### struct `FWorldBrowserColumnConfig`  
`struct FWorldBrowserColumnConfig`  
_L14-24_
- reflection: `USTRUCT()`
- L19 _public member_ `TMap<FName, bool> ColumnVisibilities {` — `UPROPERTY()`

#### class `UWorldBrowserConfig`  
`class UWorldBrowserConfig : public UEditorConfigBase`  
_L27-41_
- reflection: `UCLASS(EditorConfig="WorldBrowser")`
- inherits: `UEditorConfigBase`
- L33 _public member_ `FWorldBrowserColumnConfig ColumnConfig;` — `UPROPERTY(meta=(EditorConfig))`
- L35 _public prototype_ `static void Initialize();`
- L36 _public function_ `static UWorldBrowserConfig* Get()`
- L40 _private member_ `static TObjectPtr<UWorldBrowserConfig> Instance;`

### `Source/Editor/WorldBrowser/Private/WorldBrowserDragDrop.h` (Private)


#### struct `WorldHierarchy::FValidationInfo`  
`struct FValidationInfo`  
_L16-25_
- L18 _public function_ `FValidationInfo() : bValid(true)`
- L23 _public member_ `FText ValidationText;`
- L24 _public member_ `bool bValid;`

#### struct `WorldHierarchy::FDragDropPayload`  
`struct FDragDropPayload`  
_L28-32_
- L31 _public member_ `TArray<WorldHierarchy::FWorldTreeItemPtr> DraggedTreeItems;` — World tree items

#### struct `WorldHierarchy::FWorldBrowserDragDropOp`  
`struct FWorldBrowserDragDropOp : public FLevelDragDropOp`  
_L41-79_
- inherits: `FLevelDragDropOp`
- desc: Used to drag folders and level items within the world hierarchy widget
- L43 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FWorldBrowserDragDropOp, FLevelDragDropOp);`
- L45 _public prototype_ `FWorldBrowserDragDropOp();`
- L49 _public function_ `TArray<FWorldTreeItemPtr> GetDraggedItems() const`
- L52 _public prototype_ `void Init(const FDragDropPayload* Payload);` — Initializes the operation with the specified payload
- L54 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L57 _public function_ `static TSharedRef<FWorldBrowserDragDropOp> New(const TArray<TWeakObjectPtr<ULevel>>& Levels)` — Creates a drag and drop operation for the specified levels
- L67 _public function_ `static TSharedRef<FWorldBrowserDragDropOp> New(const TArray<TWeakObjectPtr<ULevelStreaming>>& StreamingLevels)` — Creates a drag and drop operation for the specified streaming levels
- L78 _private member_ `TArray<FWorldTreeItemPtr> DraggedItems;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace WorldHierarchy`
- L13 _typedef_ `typedef TSharedPtr<IWorldTreeItem> FWorldTreeItemPtr;` (scope `WorldHierarchy`)
- L14 _typedef_ `typedef TSharedRef<IWorldTreeItem> FWorldTreeItemRef;` (scope `WorldHierarchy`)
- L36 _prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation(const TArray<WorldHierarchy::FWorldTreeItemPtr>& InTreeItems);` (scope `WorldHierarchy`) — Construct a new drag and drop operation for the world hierarchy

### `Source/Editor/WorldBrowser/Private/WorldBrowserPrivateTypes.h` (Private)


#### struct `WorldHierarchy::FWorldTreeItemID`  
`struct FWorldTreeItemID`  
_L12-185_
- desc: Variable type for defining identifies for world tree items
- L24 _public function_ `FWorldTreeItemID() : Type(EType::Null), CachedHash(0)`
- L27 _public function_ `FWorldTreeItemID(const UObject* InObject, FName ItemName) : Type(EType::Object)` — IDs for UObjects
- L39 _public function_ `FWorldTreeItemID(const FObjectKey& InKey) : Type(EType::Object)`
- L46 _public function_ `FWorldTreeItemID(const FName& InFolder) : Type(EType::Folder)` — IDs for folders
- L53 _public function_ `FWorldTreeItemID(const FWorldTreeItemID& Other)` — Copy construction/assignment
- L57 _public function_ `FWorldTreeItemID& operator=(const FWorldTreeItemID& Other)`
- L78 _public function_ `FWorldTreeItemID(FWorldTreeItemID&& Other)` — Move construction/assignment
- L82 _public function_ `FWorldTreeItemID& operator=(FWorldTreeItemID&& Other)`
- L88 _public function_ `~FWorldTreeItemID()`
- L114 _public function_ `uint32 CalculateTypeHash() const`
- L140 _private function_ `void CreateAsMissing(FName ObjectName)`
- L147 _private function_ `FObjectKey& GetAsObjectKey() const`
- L148 _private function_ `FName& GetAsNameRef() const`
- L151 _private function_ `bool Compare(const FWorldTreeItemID& Other) const` — Compares the specified ID with this one, and returns true if they match.
- L180 _private member_ `static const uint32 MaxDataSize = TMaxSizeof<FObjectKey, FName>::Value;`
- L182 _private member_ `EType Type;`
- L183 _private member_ `uint32 CachedHash;`
- L184 _private member_ `mutable uint8 Data[MaxDataSize];`

#### enum `WorldHierarchy::FWorldTreeItemID::EType`  
`enum class EType : uint8`  
_L16-22_
- L18 _public enumerator_ `Object`
- L19 _public enumerator_ `Folder`
- L20 _public enumerator_ `MissingObject`
- L21 _public enumerator_ `Null`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace WorldHierarchy`
- L104 _function_ `friend bool operator==(const FWorldTreeItemID& One, const FWorldTreeItemID& Other)` (scope `WorldHierarchy`)
- L109 _function_ `friend bool operator!=(const FWorldTreeItemID& One, const FWorldTreeItemID& Other)` (scope `WorldHierarchy`)
- L133 _function_ `friend uint32 GetTypeHash(const FWorldTreeItemID& ItemID)` (scope `WorldHierarchy`)

### `Source/Editor/WorldBrowser/Private/WorldBrowserStyle.h` (Private)


#### class `WorldBrowser::FWorldBrowserStyle`  
`class FWorldBrowserStyle final : public FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- L14 _public prototype_ `FWorldBrowserStyle();`
- L15 _public function_ `virtual ~FWorldBrowserStyle()`
- L17 _public function_ `static FWorldBrowserStyle& Get()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace WorldBrowser`

### `Source/Editor/WorldBrowser/Private/WorldTreeItemTypes.h` (Private)


#### struct `WorldHierarchy::FLevelModelTreeItem`  
`struct FLevelModelTreeItem : IWorldTreeItem`  
_L16-121_
- inherits: `IWorldTreeItem`
- desc: The tree item for the level models
- L20 _public prototype_ `FLevelModelTreeItem(TSharedRef<FLevelModel> InLevelModel);`
- L22 _public prototype_ `virtual FWorldTreeItemID GetID() const override;`
- L24 _public prototype_ `virtual FWorldTreeItemPtr CreateParent() const override;`
- L26 _public prototype_ `virtual FLevelModelList GetModel() const override;`
- L28 _public prototype_ `virtual FString GetDisplayString() const override;`
- L30 _public prototype_ `virtual FText GetToolTipText() const override;`
- L31 _public prototype_ `virtual FText GetLockToolTipText() const override;`
- L32 _public prototype_ `virtual FText GetEditorVisibilityToolTipText() const override;`
- L33 _public prototype_ `virtual FText GetGameVisibilityToolTipText() const override;`
- L34 _public prototype_ `virtual FText GetSaveToolTipText() const override;`
- L35 _public prototype_ `virtual FString GetPackageFileName() const override;`
- L37 _public prototype_ `virtual FWorldTreeItemID GetParentID() const override;`
- L39 _public prototype_ `virtual bool CanHaveChildren() const override;`
- L41 _public prototype_ `virtual void SetExpansion(bool bExpanded) override;`
- L43 _public prototype_ `virtual bool HasModel(TSharedPtr<FLevelModel> InLevelModel) const override;`
- L45 _public prototype_ `virtual TSet<FName> GetAncestorPaths() const override;`
- L47 _public prototype_ `virtual void SetParentPath(const FName& InParentPath) override;`
- L49 _public function_ `virtual int32 GetSortPriority() const override`
- L51 _public prototype_ `virtual bool IsVisibleInEditor() const override;`
- L52 _public prototype_ `virtual bool IsVisibleInGame() const override;`
- L53 _public prototype_ `virtual bool IsLocked() const override;`
- L54 _public prototype_ `virtual bool IsTransient() const override;`
- L55 _public prototype_ `virtual bool IsReadOnly() const override;`
- L58 _public prototype_ `virtual bool CanSave() const override;`
- L59 _public prototype_ `virtual bool HasLightingControls() const override;`
- L60 _public prototype_ `virtual bool HasLockControls() const override;`
- L61 _public prototype_ `virtual bool HasEditorVisibilityControls() const override;`
- L62 _public prototype_ `virtual bool HasGameVisibilityControls() const override;`
- L63 _public prototype_ `virtual bool HasColorButtonControls() const override;`
- L64 _public prototype_ `virtual bool HasKismet() const override;`
- L66 _public prototype_ `virtual bool IsCurrent() const override;`
- L67 _public function_ `virtual bool CanBeCurrent() const override`
- L68 _public prototype_ `virtual void MakeCurrent() override;`
- L69 _public prototype_ `virtual bool HasValidPackage() const override;`
- L70 _public prototype_ `virtual bool IsDirty() const override;`
- L71 _public prototype_ `virtual bool IsLoaded() const override;`
- L73 _public prototype_ `virtual FLinearColor GetDrawColor() const override;`
- L74 _public prototype_ `virtual void SetDrawColor(const FLinearColor& Color) override;`
- L76 _public prototype_ `virtual void OnToggleEditorVisibility() override;`
- L77 _public prototype_ `virtual void OnShowInEditorOnlySelected() override;`
- L78 _public prototype_ `virtual void OnShowInEditorAllButSelected() override;`
- L79 _public prototype_ `virtual void OnToggleGameVisibility() override;`
- L80 _public prototype_ `virtual void OnShowInGameOnlySelected() override;`
- L81 _public prototype_ `virtual void OnShowInGameAllButSelected() override;`
- L82 _public prototype_ `virtual void PopulateLevelModelList(FLevelModelList& InModelList) override;`
- L83 _public prototype_ `virtual void OnToggleLightingScenario() override;`
- L84 _public prototype_ `virtual void OnToggleLock() override;`
- L85 _public prototype_ `virtual void OnLockOnlySelected() override;`
- L86 _public prototype_ `virtual void OnLockAllButSelected() override;`
- L87 _public prototype_ `virtual void OnSave() override;`
- L88 _public prototype_ `virtual void OnOpenKismet() override;`
- L90 _public prototype_ `virtual bool GetLevelSelectionFlag() const override;`
- L91 _public prototype_ `virtual bool IsLightingScenario() const override;`
- L92 _public prototype_ `virtual const FSlateBrush* GetHierarchyItemBrush() const override;`
- L94 _public prototype_ `virtual bool CanChangeParents() const override;`
- L95 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, const SWorldHierarchyImpl& Hierarchy) override;`
- L98 _public function_ `virtual FLevelModelTreeItem* GetAsLevelModelTreeItem() const override`
- L99 _public function_ `virtual FFolderTreeItem* GetAsFolderTreeItem() const override`
- L101 _public prototype_ `virtual void SetVisibleInEditor(bool bVisible) override;`
- L102 _public prototype_ `virtual void SetVisibleInGame(bool bVisible) override;`
- L103 _public prototype_ `virtual void SetLocked(bool bLocked) override;`
- L107 _public prototype_ `virtual FValidationInfo ValidateDrop(const FDragDropEvent& DragEvent) const override;`
- L108 _public prototype_ `virtual void OnDrop(const FDragDropEvent& DragEvent, TSharedRef<SWorldHierarchyImpl> Hierarchy) override;`
- L111 _protected member_ `TWeakPtr<FLevelModel> LevelModel;`
- L112 _protected member_ `bool bPersistentLevel : 1;`
- L116 _private member_ `FWorldTreeItemID ID;`
- L118 _private prototype_ `void SetSelectedLevelsToPopulatedList();`
- L120 _private prototype_ `bool IsPersistentLevel() const;`

#### struct `WorldHierarchy::FFolderTreeItem`  
`struct FFolderTreeItem : IWorldTreeItem`  
_L125-211_
- inherits: `IWorldTreeItem`
- desc: The tree item for the folders
- L129 _public prototype_ `FFolderTreeItem(FName InPath);`
- L133 _public prototype_ `virtual FWorldTreeItemID GetID() const override;`
- L135 _public prototype_ `virtual FWorldTreeItemPtr CreateParent() const override;`
- L137 _public prototype_ `virtual FString GetDisplayString() const override;`
- L139 _public prototype_ `virtual FText GetToolTipText() const override;`
- L140 _public prototype_ `virtual FText GetLockToolTipText() const override;`
- L141 _public prototype_ `virtual FText GetEditorVisibilityToolTipText() const override;`
- L142 _public prototype_ `virtual FText GetGameVisibilityToolTipText() const override;`
- L143 _public prototype_ `virtual FText GetSaveToolTipText() const override;`
- L145 _public prototype_ `virtual FWorldTreeItemID GetParentID() const override;`
- L147 _public prototype_ `virtual void SetParentPath(const FName& InParentPath) override;`
- L149 _public prototype_ `virtual TSet<FName> GetAncestorPaths() const override;`
- L151 _public function_ `virtual bool CanHaveChildren() const override`
- L153 _public function_ `virtual int32 GetSortPriority() const override`
- L155 _public prototype_ `virtual bool IsVisibleInEditor() const override;`
- L156 _public prototype_ `virtual bool IsVisibleInGame() const override;`
- L157 _public prototype_ `virtual bool IsLocked() const override;`
- L159 _public prototype_ `virtual bool CanSave() const override;`
- L160 _public prototype_ `virtual bool HasLockControls() const override;`
- L161 _public prototype_ `virtual bool HasEditorVisibilityControls() const override;`
- L162 _public prototype_ `virtual bool HasGameVisibilityControls() const override;`
- L163 _public prototype_ `virtual bool HasValidPackage() const override;`
- L164 _public prototype_ `virtual bool IsDirty() const override;`
- L166 _public prototype_ `virtual void OnToggleEditorVisibility() override;`
- L167 _public prototype_ `virtual void OnShowInEditorOnlySelected() override;`
- L168 _public prototype_ `virtual void OnShowInEditorAllButSelected() override;`
- L169 _public prototype_ `virtual void OnToggleGameVisibility() override;`
- L170 _public prototype_ `virtual void OnShowInGameOnlySelected() override;`
- L171 _public prototype_ `virtual void OnShowInGameAllButSelected() override;`
- L172 _public prototype_ `virtual void PopulateLevelModelList(FLevelModelList& InModelList) override;`
- L173 _public prototype_ `virtual void OnToggleLock() override;`
- L174 _public prototype_ `virtual void OnLockOnlySelected() override;`
- L175 _public prototype_ `virtual void OnLockAllButSelected() override;`
- L176 _public prototype_ `virtual void OnSave() override;`
- L177 _public prototype_ `virtual const FSlateBrush* GetHierarchyItemBrush() const override;`
- L178 _public function_ `virtual float GetHierarchyItemBrushWidth() const`
- L180 _public function_ `virtual bool CanChangeParents() const`
- L181 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, const SWorldHierarchyImpl& Hierarchy) override;`
- L184 _public prototype_ `void SetNewPath(FName NewPath);` — Sets the new path of the folder. This includes the leaf name. This will not rename any children in this folder
- L187 _public function_ `virtual FLevelModelTreeItem* GetAsLevelModelTreeItem() const override`
- L188 _public function_ `virtual FFolderTreeItem* GetAsFolderTreeItem() const override`
- L190 _public function_ `FName GetFullPath() const`
- L191 _public function_ `FName GetLeafName() const`
- L193 _public prototype_ `virtual void SetVisibleInEditor(bool bVisible) override;`
- L194 _public prototype_ `virtual void SetVisibleInGame(bool bVisible) override;`
- L195 _public prototype_ `virtual void SetLocked(bool bLocked) override;`
- L199 _public prototype_ `virtual FValidationInfo ValidateDrop(const FDragDropEvent& DragEvent) const override;`
- L200 _public prototype_ `virtual void OnDrop(const FDragDropEvent& DragEvent, TSharedRef<SWorldHierarchyImpl> Hierarchy) override;`
- L204 _private prototype_ `bool IsAnyChildLoaded() const;`
- L206 _private prototype_ `FLevelModelList SetSelectionToFolderChildren();`
- L209 _private member_ `FName Path;`
- L210 _private member_ `FName LeafName;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace WorldHierarchy`
- L9 _variable_ `static const int32 FolderSortPriority = 10;` (scope `WorldHierarchy`)
- L10 _variable_ `static const int32 LevelModelSortPriority = 0;` (scope `WorldHierarchy`)
- L13 _prototype_ `bool IsInPie();` (scope `WorldHierarchy`) — @return Whether currently playing in editor.

### `Source/Editor/WorldBrowser/Public/IWorldHierarchy.h` (Public)


#### class `UE::WorldHierarchy::IWorldHierarchy`  
`class IWorldHierarchy`  
_L13-32_
- desc: Displays levels for the world.
- L18 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;` — @return Gets the widget that displays the levels
- L24 _public prototype_ `virtual bool IsColumnVisible(FName Column) const = 0;` — @see WorldHierarchyColumns.h for named columns. @return Whether Column is visible in the UI.
- L29 _public prototype_ `virtual void SetColumnVisible(FName Column, bool bVisible) = 0;` — Sets whether Column is visible in the UI. Does not save this into the config though. @see WorldHierarchyColumns.h for named columns.
- L31 _public prototype_ `virtual ~IWorldHierarchy() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace WorldHierarchy` (scope `UE`)

### `Source/Editor/WorldBrowser/Public/IWorldTreeItem.h` (Public)


#### struct `WorldHierarchy::IDropTarget`  
`struct IDropTarget`  
_L22-29_
- desc: Interface for validating drag/drop movement
- L25 _public prototype_ `virtual FValidationInfo ValidateDrop(const FDragDropEvent& DragEvent) const = 0;` — Called to test whether the specified payload can be dropped onto this tree item
- L28 _public prototype_ `virtual void OnDrop(const FDragDropEvent& DragEvent, TSharedRef<SWorldHierarchyImpl> Hierarchy) = 0;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.

#### struct `WorldHierarchy::IWorldTreeItem`  
`struct IWorldTreeItem : IDropTarget, TSharedFromThis<IWorldTreeItem>`  
_L35-292_
- inherits: `IDropTarget,TSharedFromThis<IWorldTreeItem>`
- desc: Base tree item interface for the World Browser
- L62 _public member_ `FlagsType Flags;`
- L64 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequest);`
- L66 _public member_ `FOnRenameRequest RenameRequestEvent;`
- L68 _public member_ `TWeakPtr<FLevelCollectionModel> WorldModel;`
- L72 _protected function_ `IWorldTreeItem()`
- L73 _protected prototype_ `virtual ~IWorldTreeItem() = default;`
- L76 _protected member_ `mutable FWorldTreeItemPtr Parent;` — The parent of this tree item. Can be null.
- L79 _protected member_ `mutable TArray<FWorldTreeItemPtr> Children;` — The children of this tree item, if any
- L82 _public function_ `FWorldTreeItemPtr GetParent() const`
- L87 _public function_ `TSharedPtr<FLevelModel> GetRootItem() const`
- L100 _public function_ `void AddChild(FWorldTreeItemRef Child)`
- L106 _public function_ `void RemoveChild(const FWorldTreeItemRef& Child)`
- L114 _public function_ `FORCEINLINE const TArray<FWorldTreeItemPtr>& GetChildren() const`
- L119 _public function_ `FORCEINLINE void RemoveAllChildren()`
- L125 _public function_ `FLevelModelList GetLevelModels() const` — Gets all level models for this tree item and its children
- L134 _public function_ `void AppendLevelModels(FLevelModelList& OutLevelModels) const` — Appends all level models for this tree item to the supplied array
- L145 _public function_ `virtual FLevelModelList GetModel() const` — Gets the level model for this item, excluding its children
- L148 _public prototype_ `virtual TSet<FName> GetAncestorPaths() const = 0;` — Gets the set of all ancestor paths for this item
- L153 _public prototype_ `virtual FWorldTreeItemID GetID() const = 0;` — Gets the ID for this tree item
- L156 _public prototype_ `virtual FWorldTreeItemPtr CreateParent() const = 0;` — Create the parent item for this item, if it should have one
- L159 _public prototype_ `virtual FString GetDisplayString() const = 0;` — Gets the display string for this item
- L162 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Gets the tooltip for this item
- L165 _public prototype_ `virtual FText GetLockToolTipText() const = 0;` — Gets the tooltip for this item's lock icon
- L168 _public prototype_ `virtual FText GetEditorVisibilityToolTipText() const = 0;` — Gets the tooltip for this item's visibility icon
- L171 _public prototype_ `virtual FText GetGameVisibilityToolTipText() const = 0;` — Gets the tooltip for this item's visibility icon
- L174 _public prototype_ `virtual FText GetSaveToolTipText() const = 0;` — Gets the tooltip text for this item's save icon
- L177 _public function_ `virtual FString GetPackageFileName() const` — Gets the filename of the package for this item, if one exists
- L180 _public prototype_ `virtual FWorldTreeItemID GetParentID() const = 0;` — Gets the ID of the parent item, even if it is not yet constructed
- L183 _public prototype_ `virtual bool CanHaveChildren() const = 0;` — Returns true if the item can have children
- L186 _public function_ `virtual void SetExpansion(bool bExpanded)` — Sets the item's expansion state
- L192 _public function_ `virtual bool HasModel(TSharedPtr<FLevelModel> InLevelModel) const` — Returns true if this item has an associated level model with it
- L195 _public prototype_ `virtual void SetParentPath(const FName& InParentPath) = 0;` — Changes the parent path of this item, without changing the name of this item
- L198 _public prototype_ `virtual int32 GetSortPriority() const = 0;` — Gets the sort priority of the item. A higher value means it will appear first in the list
- L202 _public prototype_ `virtual FLevelModelTreeItem* GetAsLevelModelTreeItem() const = 0;`
- L203 _public prototype_ `virtual FFolderTreeItem* GetAsFolderTreeItem() const = 0;`
- L207 _public prototype_ `virtual bool IsVisibleInEditor() const = 0;`
- L208 _public prototype_ `virtual bool IsVisibleInGame() const = 0;`
- L209 _public prototype_ `virtual bool IsLocked() const = 0;`
- L212 _public function_ `virtual bool CanSave() const` — Can this item be saved?
- L215 _public function_ `virtual bool HasLightingControls() const` — Does this item have lighting controls?
- L218 _public function_ `virtual bool HasLockControls() const` — Can the lock state on this item be toggled?
- L221 _public function_ `virtual bool HasEditorVisibilityControls() const` — Can visibility on this item be toggled?
- L224 _public function_ `virtual bool HasGameVisibilityControls() const` — Can visibility on this item be toggled?
- L227 _public function_ `virtual bool HasColorButtonControls() const` — Does this item have color button controls?
- L230 _public function_ `virtual bool HasKismet() const` — Does this item have Kismet controls?
- L233 _public function_ `virtual bool IsCurrent() const` — Is this the current item?
- L236 _public function_ `virtual bool CanBeCurrent() const` — Can this ever become the current item?
- L239 _public function_ `virtual void MakeCurrent()` — Make this item the current item
- L242 _public function_ `virtual bool HasValidPackage() const` — Does the item have a valid package?
- L245 _public function_ `virtual bool IsDirty() const` — Is the item dirty?
- L248 _public function_ `virtual bool IsLoaded() const` — Is the item loaded?
- L251 _public function_ `virtual bool IsReadOnly() const` — Is the item read-only?
- L254 _public function_ `virtual bool IsTransient() const` — Is the item transient?
- L257 _public function_ `virtual FLinearColor GetDrawColor() const` — Gets the draw color for the item
- L258 _public function_ `virtual void SetDrawColor(const FLinearColor& Color)`
- L260 _public function_ `virtual bool GetLevelSelectionFlag() const`
- L261 _public function_ `virtual bool IsLightingScenario() const`
- L262 _public function_ `virtual const FSlateBrush* GetHierarchyItemBrush() const`
- L263 _public function_ `virtual float GetHierarchyItemBrushWidth() const`
- L265 _public function_ `virtual void OnToggleEditorVisibility()`
- L266 _public function_ `virtual void OnShowInEditorOnlySelected()`
- L267 _public function_ `virtual void OnShowInEditorAllButSelected()`
- L268 _public function_ `virtual void OnToggleGameVisibility()`
- L269 _public function_ `virtual void OnShowInGameOnlySelected()`
- L270 _public function_ `virtual void OnShowInGameAllButSelected()`
- L271 _public function_ `virtual void PopulateLevelModelList(FLevelModelList& InModelList)`
- L272 _public function_ `virtual void OnToggleLightingScenario()`
- L273 _public function_ `virtual void OnLockOnlySelected()`
- L274 _public function_ `virtual void OnLockAllButSelected()`
- L275 _public function_ `virtual void OnToggleLock()`
- L276 _public function_ `virtual void OnSave()`
- L277 _public function_ `virtual void OnOpenKismet()`
- L280 _public prototype_ `virtual bool CanChangeParents() const = 0;` — Returns true if this item can have its parent changed
- L283 _public function_ `virtual void GenerateContextMenu(UToolMenu* Menu, const SWorldHierarchyImpl& Hierarchy)` — Generates a context menu option for this item if and only if it's the only item selected in the hierarchy
- L286 _public prototype_ `virtual void SetVisibleInEditor(bool bVisible) = 0;` — Sets the item's editor visible status
- L288 _public prototype_ `virtual void SetVisibleInGame(bool bVisible) = 0;` — Sets the item's game visible status
- L291 _public prototype_ `virtual void SetLocked(bool bLocked) = 0;` — Sets the item's locked status

#### struct `WorldHierarchy::IWorldTreeItem::FlagsType`  
`struct FlagsType`  
_L39-58_
- L41 _public member_ `bool bExpanded : 1;`
- L43 _public member_ `bool bFilteredOut : 1;`
- L45 _public member_ `bool bChildrenRequiresSort : 1;`
- L47 _public member_ `bool bVisible : 1;`
- L49 _public member_ `bool bLocked : 1;`
- L51 _public function_ `FlagsType() : bExpanded(1) , bFilteredOut(0) , bChildrenRequiresSort(1) , bVisible(1) , bLocked(0)`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace WorldHierarchy`
- L64 _delegate_ `DECLARE_DELEGATE(FOnRenameRequest);`
- L295 _function_ `FORCEINLINE FName GetParentPath(const FName& InPath)` (scope `WorldHierarchy`) — Utility function to get the parent path for a specific path

### `Source/Editor/WorldBrowser/Public/WorldBrowserModule.h` (Public)


#### class `FWorldBrowserModule`  
`class FWorldBrowserModule : public IModuleInterface`  
_L15-88_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for SubLevels management
- L23 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L28 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L34 _public prototype_ `virtual TSharedRef<SWidget> CreateWorldBrowserHierarchy();` — `UE_DEPRECATED(5.5, "Use CreateWorldBrowserHierarchyWidget instead.")` — Creates a levels hierarchy widget
- L36 _public prototype_ `virtual TSharedRef<UE::WorldHierarchy::IWorldHierarchy> CreateWorldBrowserHierarchyWidget();` — Creates a levels hierarchy widget
- L41 _public prototype_ `virtual TSharedRef<class SWidget> CreateWorldBrowserDetails();` — Creates a levels details widget
- L46 _public prototype_ `virtual TSharedRef<class SWidget> CreateWorldBrowserComposition();` — Creates a levels composition widget
- L51 _public prototype_ `virtual TSharedPtr<class FLevelCollectionModel> SharedWorldModel(UWorld* InWorld);` — @return world model shared between all World Browser editors
- L56 _public prototype_ `DECLARE_EVENT_OneParam(FWorldBrowserModule, FOnBrowseWorld, UWorld*);`
- L57 _public member_ `FOnBrowseWorld OnBrowseWorld;`
- L60 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWorldBrowserModuleShutdown);` — Delegate called when WorldBrowserModule is shutdown.
- L61 _public function_ `FOnWorldBrowserModuleShutdown& OnShutdown()`
- L64 _private prototype_ `void OnWorldCreated(UWorld* InWorld);`
- L65 _private prototype_ `void OnWorldDestroyed(UWorld* InWorld);`
- L66 _private prototype_ `void OnWorldCompositionChanged(UWorld* InWorld);`
- L69 _private prototype_ `TSharedRef<FExtender> BindLevelMenu(const TSharedRef<FUICommandList> CommandList);` — Bind world browser command delegate to the level viewport
- L72 _private prototype_ `void BuildLevelMenu(FMenuBuilder& MenuBuilder);` — Fill out the level menu with entries for level operations
- L74 _private prototype_ `bool IsCurrentSublevel(TSharedPtr<class FLevelModel> InLevelModel);`
- L75 _private prototype_ `void SetCurrentSublevel(TSharedPtr<class FLevelModel> InLevelModel);`
- L77 _private prototype_ `void ReleaseWorldModel();`
- L80 _private member_ `TSharedPtr<class FLevelCollectionModel> WorldModel;`
- L83 _private member_ `FLevelEditorModule::FLevelEditorMenuExtender LevelMenuExtender;` — Extender for the level menu
- L85 _private member_ `FDelegateHandle LevelMenuExtenderHandle;` — Delegate called when the menu is created
- L87 _private member_ `FOnWorldBrowserModuleShutdown ShutdownDelegate;` — Holds FOnWorldBrowserModuleShutdown

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace WorldHierarchy` (scope `UE`)
- L56 _delegate_ `DECLARE_EVENT_OneParam(FWorldBrowserModule, FOnBrowseWorld, UWorld*);`
- L60 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWorldBrowserModuleShutdown);` — Delegate called when WorldBrowserModule is shutdown.

### `Source/Editor/WorldBrowser/Public/WorldHierarchyColumns.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace WorldHierarchy` (scope `UE`)
- L7 _namespace_ `namespace HierarchyColumns` (scope `UE::WorldHierarchy`)
- L10 _externvar_ `extern const FName ColumnID_LevelLabel;` (scope `UE::WorldHierarchy::HierarchyColumns`) — IDs for list columns
- L11 _externvar_ `extern const FName ColumnID_EditorVisibility;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L12 _externvar_ `extern const FName ColumnID_GameVisibility;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L13 _externvar_ `extern const FName ColumnID_LightingScenario;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L14 _externvar_ `extern const FName ColumnID_Lock;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L15 _externvar_ `extern const FName ColumnID_SCCStatus;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L16 _externvar_ `extern const FName ColumnID_Save;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L17 _externvar_ `extern const FName ColumnID_Color;` (scope `UE::WorldHierarchy::HierarchyColumns`)
- L18 _externvar_ `extern const FName ColumnID_Kismet;` (scope `UE::WorldHierarchy::HierarchyColumns`)
