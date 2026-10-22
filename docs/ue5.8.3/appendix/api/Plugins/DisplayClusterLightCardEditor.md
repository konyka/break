# Plugins / DisplayClusterLightCardEditor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor`
- headers: 20; symbols: 586
- symbol kinds: class=17, delegate=3, enum=3, enumerator=10, function=58, member=174, namespace=4, prototype=309, struct=7, typedef=1
- PrivateDependencyModuleNames: AdvancedPreviewScene, AppFramework, ApplicationCore, Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, DisplayClusterOperator, DisplayClusterScenePreview, EditorStyle, Engine, InputCore, OpenCV, OpenCVHelper, ProceduralMeshComponent, PropertyEditor, RHI, RenderCore, Renderer, SceneOutliner, Slate, SlateCore, ToolMenus, ToolWidgets, UMG, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DetailCustomizations/DisplayClusterLightCardActorDetails.h` (Private)


#### class `FDisplayClusterLightCardActorDetails`  
`class FDisplayClusterLightCardActorDetails final : public IDetailCustomization`  
_L8-16_
- inherits: `IDetailCustomization`
- L11 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InLayoutBuilder) override;` — IDetailCustomization interface

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditor.h` (Private)


#### class `FDisplayClusterLightCardEditor`  
`class FDisplayClusterLightCardEditor : public IDisplayClusterOperatorApp, public FEditorUndoClient`  
_L34-373_
- inherits: `IDisplayClusterOperatorApp,FEditorUndoClient`
- desc: A panel that can be spawned in a tab that contains all the UI elements that make up the 2D light cards editor
- L38 _public member_ `static const FName ViewportTabName;` — The name of the tab that the viewport lives in
- L41 _public member_ `static const FName OutlinerTabName;` — The name of the tab that the outliner lives in
- L44 _public prototype_ `static TSharedRef<IDisplayClusterOperatorApp> MakeInstance(TSharedRef<IDisplayClusterOperatorViewModel> InViewModel);` — Construct an instance of the light card editor
- L46 _public prototype_ `~FDisplayClusterLightCardEditor();`
- L49 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L50 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L54 _public prototype_ `void Initialize(TSharedRef<IDisplayClusterOperatorViewModel> InViewModel);` — Initialize the light card editor instance
- L57 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const` — Return the command list for the light card editor
- L60 _public function_ `TWeakObjectPtr<ADisplayClusterRootActor> GetActiveRootActor() const` — The current active root actor for this light card editor
- L63 _public prototype_ `TArray<AActor*> FindAllManagedActors() const;` — Iterate the world actors looking for all actors this editor is managing
- L66 _public prototype_ `void SelectActors(const TArray<AActor*>& ActorsToSelect);` — Selects the specified actors in the outliner and details panel
- L69 _public function_ `template<typename T> TArray<T*> GetSelectedActorsAs() const`
- L84 _public prototype_ `void GetSelectedActors(TArray<AActor*>& OutSelectedActors);` — Gets the actors that are selected in the outliner
- L87 _public prototype_ `void SelectActorProxies(const TArray<AActor*>& ActorsToSelect);` — Selects the actor proxies that correspond to the specified actors
- L90 _public prototype_ `void CenterActorInView(AActor* Actor);` — Places the given light card in the middle of the viewport
- L93 _public prototype_ `AActor* SpawnActor(TSubclassOf<AActor> InActorClass, const FName& InActorName = NAME_None, const UDisplayClusterLightCardTemplate* InTemplate = nullptr, ULevel* InLevel = nullptr, bool bIsPreview = false);` — Spawns a new actor and adds it to the root actor if it is a light card
- L97 _public prototype_ `AActor* SpawnActor(const UDisplayClusterLightCardTemplate* InTemplate, ULevel* InLevel = nullptr, bool bIsPreview = false);` — Spawn an actor from a template
- L100 _public function_ `template<typename T> T* SpawnActorAs(const FName& InActorName = NAME_None, const UDisplayClusterLightCardTemplate* InTemplate = nullptr)`
- L106 _public prototype_ `ADisplayClusterLightCardActor* AddNewLightCard();` — Adds a new light card to the root actor and centers it in the viewport
- L109 _public prototype_ `void AddExistingLightCard();` — Select an existing Light Card from a menu
- L112 _public prototype_ `ADisplayClusterLightCardActor* AddNewFlag();` — Adds a new light card configured as a flag
- L115 _public prototype_ `AActor* AddNewDynamic(UClass* InClass);` — Add a new actor dynamically based on a class
- L118 _public prototype_ `void AddLightCardsToActor(const TArray<ADisplayClusterLightCardActor*>& LightCards);` — Adds the given Light Card to the root actor
- L121 _public prototype_ `bool CanAddNewActor() const;` — If a Light Card can currently be added
- L122 _public prototype_ `bool CanAddNewActor(UClass* InClass) const;`
- L125 _public prototype_ `void CutSelectedActors();` — Copies any selected actors to the clipboard, and then deletes them
- L128 _public prototype_ `bool CanCutSelectedActors();` — Determines if there are selected actors that can be cut
- L131 _public prototype_ `void CopySelectedActors(bool bShouldCut = false);` — Copies any selected actors to the clipboard
- L134 _public prototype_ `bool CanCopySelectedActors() const;` — Determines if there are selected actors that can be copied
- L137 _public prototype_ `TArray<AActor*> PasteActors();` — Pastes any actors in the clipboard to the current root actor
- L140 _public prototype_ `bool CanPasteActors() const;` — Determines if there are any actors that can be pasted from the clipboard
- L143 _public prototype_ `void DuplicateSelectedActors();` — Copies any selected actors to the clipboard and then pastes them
- L146 _public prototype_ `bool CanDuplicateSelectedActors() const;` — Determines if there are selected actors that can be duplicated
- L149 _public prototype_ `void RenameSelectedItem();` — Rename the selected item. Requires the outliner
- L152 _public prototype_ `bool CanRenameSelectedItem() const;` — If the selected item can be renamed
- L158 _public prototype_ `void RemoveSelectedActors(bool bDeleteLightCardActor);` — Remove the light card from the actor @param bDeleteLightCardActor Delete the actor from the level
- L165 _public prototype_ `void RemoveActors(const TArray<TWeakObjectPtr<AActor>>& InActorsToRemove, bool bDeleteActors);` — Remove the given light cards from the actor @param InActorsToRemove Actors which should be removed @param bDeleteActors If the light cards should be deleted from the level
- L168 _public prototype_ `bool CanRemoveSelectedActors() const;` — If the selected actors can be removed
- L171 _public prototype_ `bool CanRemoveSelectedLightCardFromActor() const;` — If the selected light card can be removed from the actor
- L174 _public prototype_ `void CreateLightCardTemplate();` — Creates a template of the selected light card
- L177 _public prototype_ `bool CanCreateLightCardTemplate() const;` — Determines if there are selected light cards that can have templates created
- L180 _public prototype_ `void ToggleLightCardLabels();` — Toggles the visible status of labels
- L183 _public prototype_ `void ShowLightCardLabels(bool bVisible);` — Display or hide labels for all included light cards
- L186 _public prototype_ `bool ShouldShowLightCardLabels() const;` — If light card labels are currently toggled
- L189 _public prototype_ `void ToggleLightCardLabelFlag(EDisplayClusterLabelFlags InFlag);` — Toggles light cards label flag
- L192 _public prototype_ `void SaveLightCardLabelFlags(EDisplayClusterLabelFlags InFlags);` — Save the light card label flags to settings
- L195 _public prototype_ `bool LightCardLabelHasFlag(EDisplayClusterLabelFlags FlagToCheck) const;` — If the light card label has a specific flag
- L198 _public prototype_ `bool LightCardLabelDoesNotHaveFlag(EDisplayClusterLabelFlags FlagToCheck) const;` — If the light card label is missing a specific flag
- L201 _public prototype_ `EDisplayClusterLabelFlags GetLightCardLabelFlags() const;` — The current light card label flags
- L204 _public prototype_ `TOptional<float> GetLightCardLabelScale() const;` — Return the current light card label scale
- L207 _public prototype_ `void SetLightCardLabelScale(float NewValue);` — Update light card label scale
- L210 _public prototype_ `void ShowIcons(bool bVisible);` — Set all icon visibility
- L213 _public prototype_ `bool ShouldShowIcons() const;` — If all icons should be visible
- L216 _public prototype_ `TOptional<float> GetIconScale() const;` — Return the current icon scale
- L219 _public prototype_ `void SetIconScale(float NewValue);` — Update all icons scale
- L223 _private prototype_ `void OnActiveRootActorChanged(ADisplayClusterRootActor* NewRootActor);` — Raised when the active Display cluster root actor has been changed in the operator panel
- L226 _private prototype_ `void OnActorsSelectedExternally(const TArray<AActor*>& Actors, bool bShouldSelect);` — Raised when a request to select or deselect actors in the operator panel is raised from outside the panel
- L229 _private prototype_ `void RegisterTabSpawners();` — Registers the light card editor with the global tab manager and adds it to the operator panel's extension tab stack
- L232 _private prototype_ `void UnregisterTabSpawners();` — Unregisters the light card editor from the global tab manager
- L235 _private prototype_ `static void RegisterLayoutExtension(FLayoutExtender& InExtender);` — Registers the light card editor tab with the operator panel using a layout extension
- L238 _private prototype_ `TSharedRef<SDockTab> SpawnViewportTab(const FSpawnTabArgs& SpawnTabArgs);` — Spawns in the viewport tab
- L241 _private prototype_ `TSharedRef<SDockTab> SpawnOutlinerTab(const FSpawnTabArgs& SpawnTabArgs);` — Spawns in the outliner tab
- L244 _private prototype_ `TSharedRef<SWidget> CreateLightCardOutlinerWidget();` — Creates the widget used to show the list of light cards associated with the active root actor
- L247 _private prototype_ `TSharedRef<SWidget> CreateLightCardTemplateWidget();` — Create the widget for selecting light card templates
- L250 _private prototype_ `TSharedRef<SWidget> CreateViewportWidget();` — Create the 3d viewport widget
- L253 _private prototype_ `TSharedRef<SWidget> GeneratePlaceActorsMenu();` — Generate the place actors drop down menu
- L256 _private prototype_ `const FSlateBrush* GetLightCardTemplateIcon(const TWeakObjectPtr<UDisplayClusterLightCardTemplate> InTemplate) const;` — Return the correct template icon to use
- L259 _private prototype_ `void GenerateTemplateSubMenu(FMenuBuilder& InMenuBuilder);` — Generate the All Templates sub menu
- L262 _private prototype_ `TSharedRef<SWidget> GenerateLabelsMenu();` — Generate the labels dropdown menu
- L265 _private prototype_ `TSharedRef<SWidget> CreateFrustumWidget();` — Creates the frustum combo box
- L268 _private prototype_ `void BindCommands();` — Creates the editor's command list and binds commands to it
- L271 _private prototype_ `void RegisterToolbarExtensions();` — Register any extensions for the toolbar
- L274 _private prototype_ `void RegisterMenuExtensions();` — Register any extensions for the menu bar
- L277 _private prototype_ `void ExtendToolbar(FToolBarBuilder& ToolbarBuilder);` — Extend the toolbar for this local instance
- L280 _private prototype_ `void ExtendFileMenu(FMenuBuilder& MenuBuilder);` — Extend the main file menu
- L283 _private prototype_ `void ExtendEditMenu(FMenuBuilder& MenuBuilder);` — Extend the main edit menu
- L286 _private prototype_ `void RefreshPreviewActors(EDisplayClusterLightCardEditorProxyType ProxyType = EDisplayClusterLightCardEditorProxyType::All);` — Refresh all preview actors
- L289 _private prototype_ `void RefreshPreviewStageActor(AActor* Actor);` — Refresh a specific preview stage actor
- L292 _private prototype_ `void RefreshLabels();` — Reapply the current label settings
- L300 _private prototype_ `bool IsOurObject(UObject* InObject, EDisplayClusterLightCardEditorProxyType& OutProxyType) const;` — Check if an object is managed by us @param InObject The object to compare @param OutProxyType The type of the object @return True if our object, false if not
- L303 _private prototype_ `void BindCompileDelegates();` — Bind delegates to when a BP compiles
- L306 _private prototype_ `void RemoveCompileDelegates();` — Remove compile delegates from a BP
- L309 _private prototype_ `void OnActorPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);` — When a property on the actor has changed
- L312 _private prototype_ `void OnLevelActorAdded(AActor* Actor);` — Raised when the user adds an actor to the level
- L315 _private prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Raised when the user deletes an actor from the level
- L318 _private prototype_ `void OnBlueprintCompiled(UBlueprint* Blueprint);` — Raised when a supported blueprint is compiled
- L321 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);` — Raised when any object is transacted
- L324 _private prototype_ `void AddRecentlyPlacedItem(const FDisplayClusterLightCardEditorRecentItem& InItem);` — Add an item to recently placed list. Reorders matching items to the top of the list and trims the list
- L327 _private prototype_ `void CleanupRecentlyPlacedItems();` — Make sure no invalid entries are present
- L335 _private prototype_ `bool DoOutlinerFoldersNeedEditorDelegates() const;` — Checks if it is possible only one or more folders - and no actors - are selected in the outliner They require editor delegates fired when executing some generic commands @return true if the outliner is valid and no actor is selected
- L339 _private member_ `TSharedPtr<SDisplayClusterLightCardOutliner> LightCardOutliner;` — The light card outliner widget
- L342 _private member_ `TMap<TWeakObjectPtr<UDisplayClusterLightCardTemplate>, TSharedPtr<FSlateBrush>> TemplateBrushes;` — Templates to their icon brushes
- L345 _private member_ `TSharedPtr<SDisplayClusterLightCardEditorViewport> ViewportView;` — The 3d viewport
- L348 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for editor commands
- L351 _private member_ `TOptional<FIntPoint> CachedContextMenuMousePos;` — Stores the mouse position when the context menu was opened
- L354 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> ActiveRootActor;` — A reference to the root actor that is currently being operated on
- L357 _private member_ `TWeakPtr<IDisplayClusterOperatorViewModel> OperatorViewModel;` — The view model for the operator panel
- L360 _private member_ `TArray<TWeakObjectPtr<AActor>> SelectedActors;` — Selected actors
- L363 _private member_ `TArray<TSharedPtr<FString>> FrustumSelections;` — Available frustums to choose
- L366 _private member_ `FDelegateHandle ActiveRootActorChangedHandle;` — Delegate handle for the OnActiveRootActorChanged delegate
- L369 _private member_ `FDelegateHandle ActorsSelectedExternallyHandle;` — Delegate handle for the OnActorsSelectedExternally delegate
- L372 _private member_ `FDelegateHandle OnObjectTransactedHandle;` — Delegate handle for when an object is transacted

#### Free symbols / members of external scopes

- L73 _function_ `` (scope `FDisplayClusterLightCardEditor::GetSelectedActorsAs`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditorCommands.h` (Private)


#### class `FDisplayClusterLightCardEditorCommands`  
`class FDisplayClusterLightCardEditorCommands : public TCommands<FDisplayClusterLightCardEditorCommands>`  
_L11-61_
- inherits: `TCommands<FDisplayClusterLightCardEditorCommands>`
- L15 _public function_ `FDisplayClusterLightCardEditorCommands() : TCommands<FDisplayClusterLightCardEditorCommands>(TEXT("DisplayClusterLightCardEditor"), NSLOCTEXT("Contexts", "DisplayClusterLightCardEditor", "Display Cluster LightCard Editor"), NAME_None, FDisplayClusterLightCardEditorStyle::Get().GetStyleSetName())`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ResetCamera;` — Viewport commands
- L27 _public member_ `TSharedPtr<FUICommandInfo> FrameSelection;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> PerspectiveProjection;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> OrthographicProjection;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> AzimuthalProjection;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> UVProjection;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ViewOrientationTop;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ViewOrientationBottom;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ViewOrientationLeft;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ViewOrientationRight;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ViewOrientationFront;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ViewOrientationBack;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> CycleEditorWidgetCoordinateSystem;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> CartesianCoordinateSystem;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> SphericalCoordinateSystem;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> AddNewLightCard;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> AddNewFlag;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> AddExistingLightCard;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> RemoveLightCard;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> PasteHere;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> SaveLightCardTemplate;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> DrawLightCard;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> ToggleAllLabels;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> ToggleLightCardLabels;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> ToggleLabelsVisibleInEditor;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> ToggleLabelsHiddenInGame;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> ToggleIconVisibility;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(DisplayClusterLightCardEditorLog, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(DisplayClusterLightCardEditorLog, Log, All);` — Module-wide log categories
- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("nDisplay Light Card Editor"), STATGROUP_NDisplayLightCardEditor, STATCAT_Advanced)`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditorModule.h` (Private)


#### class `FDisplayClusterLightCardEditorModule`  
`class FDisplayClusterLightCardEditorModule : public IDisplayClusterLightCardEditor`  
_L10-39_
- inherits: `IDisplayClusterLightCardEditor`
- desc: Display Cluster editor module
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual void ShowLabels(const FLabelArgs& InArgs) override;`
- L19 _public prototype_ `virtual UDisplayClusterStageActorTemplate* GetDefaultLightCardTemplate() const override;`
- L22 _private prototype_ `void RegisterSettings();`
- L23 _private prototype_ `void UnregisterSettings();`
- L25 _private prototype_ `void RegisterDetailCustomizations();`
- L26 _private prototype_ `void UnregisterDetailCustomizations();`
- L28 _private prototype_ `void RegisterOperatorApp();`
- L29 _private prototype_ `void UnregisterOperatorApp();`
- L31 _private prototype_ `void HandleModuleChanged(FName InModuleName, EModuleChangeReason InChangeReason);`
- L35 _private member_ `TArray<FName> RegisteredClassLayoutNames;` — Stores a list of class names that custom layouts have been registered for
- L37 _private member_ `FDelegateHandle ModuleChangedHandle;`
- L38 _private member_ `FDelegateHandle OperatorAppHandle;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditorProxyType.h` (Private)


#### enum `EDisplayClusterLightCardEditorProxyType`  
`enum class EDisplayClusterLightCardEditorProxyType : uint8`  
_L7-12_
- L9 _public enumerator_ `All`
- L10 _public enumerator_ `RootActor`
- L11 _public enumerator_ `StageActor`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditorStyle.h` (Private)


#### class `FDisplayClusterLightCardEditorStyle`  
`class FDisplayClusterLightCardEditorStyle final : public FSlateStyleSet`  
_L14-30_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the operator panel
- L18 _public prototype_ `FDisplayClusterLightCardEditorStyle();`
- L20 _public function_ `virtual ~FDisplayClusterLightCardEditorStyle()`
- L25 _public function_ `static FDisplayClusterLightCardEditorStyle& Get()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/DisplayClusterLightCardEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DisplayClusterLightCardEditorUtils` (scope `UE`)
- L12 _prototype_ `bool IsManagedActor(const AActor* InActor);` (scope `UE::DisplayClusterLightCardEditorUtils`) — Check if the given actor is of a type that should be managed by the light card editor
- L15 _prototype_ `bool IsProxySelectable(const AActor* InActor);` (scope `UE::DisplayClusterLightCardEditorUtils`) — Check if the given actor is of a type that is selectable in the light card editor
- L18 _prototype_ `TSet<UClass*> GetAllStageActorClasses();` (scope `UE::DisplayClusterLightCardEditorUtils`) — Discover all classes implementing or inheriting the stage actor interface

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/LightCardTemplates/DisplayClusterLightCardTemplate.h` (Private)


#### class `UDisplayClusterLightCardTemplate`  
`class UDisplayClusterLightCardTemplate : public UDisplayClusterStageActorTemplate`  
_L14-27_
- reflection: `UCLASS(NotBlueprintType, NotBlueprintable, NotPlaceable)`
- inherits: `UDisplayClusterStageActorTemplate`
- desc: A template asset to store appearance settings from Light Card actors.
- L20 _public function_ `virtual AActor* GetTemplateActor() const override` — UDisplayClusterStageActorTemplate
- L26 _public member_ `TObjectPtr<ADisplayClusterLightCardActor> LightCardActor;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = Template, NoClear, meta = (ShowOnlyInnerProperties))` — The instanced template object containing user settings for the light card.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/LightCardTemplates/DisplayClusterLightCardTemplateDragDropOp.h` (Private)


#### class `FDisplayClusterLightCardTemplateDragDropOp`  
`class FDisplayClusterLightCardTemplateDragDropOp : public FDecoratedDragDropOp`  
_L10-41_
- inherits: `FDecoratedDragDropOp`
- L13 _public function_ `DRAG_DROP_OPERATOR_TYPE(FDisplayClusterLightCardTemplateDragDropOp, FDecoratedDragDropOp) FDisplayClusterLightCardTemplateDragDropOp() : bCanBeDropped(true)`
- L19 _public prototype_ `static TSharedRef<FDisplayClusterLightCardTemplateDragDropOp> New(TWeakObjectPtr<UDisplayClusterLightCardTemplate> InTemplate);`
- L21 _public function_ `TWeakObjectPtr<UDisplayClusterLightCardTemplate> GetTemplate() const`
- L25 _protected prototype_ `virtual void Construct() override;`
- L29 _public prototype_ `void SetDropAsInvalid(FText Message = FText::GetEmpty());`
- L30 _public prototype_ `void SetDropAsValid(FText Message = FText::GetEmpty());`
- L31 _public function_ `bool CanBeDropped() const`
- L34 _protected function_ `virtual FText GetHoverText() const`
- L37 _protected member_ `bool bCanBeDropped;`
- L40 _private member_ `TWeakObjectPtr<UDisplayClusterLightCardTemplate> LightCardTemplate;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/LightCardTemplates/DisplayClusterLightCardTemplateHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DisplayClusterLightCardTemplateHelpers` (scope `UE`)
- L17 _prototype_ `TArray<UDisplayClusterLightCardTemplate*> GetLightCardTemplates(bool bFavoritesOnly = false);` (scope `UE::DisplayClusterLightCardTemplateHelpers`) — Load and return all light card templates @param bFavoritesOnly only return light card templates that are marked as a user favorite @return the light card template objects, loaded from their asset

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/LightCardTemplates/SDisplayClusterLightCardTemplateList.h` (Private)


#### class `SDisplayClusterLightCardTemplateList`  
`class SDisplayClusterLightCardTemplateList : public SCompoundWidget`  
_L17-87_
- inherits: `SCompoundWidget`
- desc: Displays available light card templates for users to drop into the light card editor scene
- L33 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterLightCardTemplateList)`
- L35 _public prototype_ `SLATE_ARGUMENT(bool, HideHeader) SLATE_ARGUMENT(bool, SpawnOnSelection) SLATE_END_ARGS() virtual ~SDisplayClusterLightCardTemplateList() override;`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FDisplayClusterLightCardEditor> InLightCardEditor);`
- L44 _public prototype_ `void RefreshTemplateList();` — Find available templates and refresh the list
- L47 _public prototype_ `void ApplyFilter(const FString& InFilterText, bool bFavorite);` — Apply a filter to the template list
- L50 _public prototype_ `void ApplyFilter();` — Reapply the current filter
- L53 _public prototype_ `bool IsDragDropEnabled() const;` — If drag & drop should be used
- L56 _private prototype_ `TSharedRef<ITableRow> GenerateTreeItemRow(TSharedPtr<FLightCardTemplateTreeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L57 _private prototype_ `void GetChildrenForTreeItem(TSharedPtr<FLightCardTemplateTreeItem> InItem, TArray<TSharedPtr<FLightCardTemplateTreeItem>>& OutChildren);`
- L58 _private prototype_ `const FSlateBrush* GetFavoriteFilterIcon() const;`
- L59 _private prototype_ `void OnSelectionChanged(TSharedPtr<FLightCardTemplateTreeItem> InItem, ESelectInfo::Type SelectInfo);`
- L61 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L63 _private prototype_ `void OnAssetAddedOrRemoved(const FAssetData& InAssetData);`
- L64 _private prototype_ `void OnAssetsLoaded();`
- L68 _private member_ `TWeakPtr<FDisplayClusterLightCardEditor> LightCardEditorPtr;` — Pointer to the light card editor that owns this widget
- L71 _private member_ `TArray<TSharedPtr<FLightCardTemplateTreeItem>> LightCardTemplateTree;` — A list of all light card tree items to be displayed in the tree view
- L74 _private member_ `TArray<TSharedPtr<FLightCardTemplateTreeItem>> FilteredLightCardTemplateTree;` — The visible list of light card tree items filtered by the user
- L77 _private member_ `TSharedPtr<STreeView<TSharedPtr<FLightCardTemplateTreeItem>>> LightCardTemplateTreeView;` — The tree view widget displaying the light card templates
- L80 _private member_ `FString FilterText;` — The search string text
- L83 _private member_ `bool bFilterFavorites = false;` — If the favorite filter should be applied
- L86 _private member_ `bool bSpawnOnSelection = false;` — If selecting a template should spawn it

#### struct `SDisplayClusterLightCardTemplateList::FLightCardTemplateTreeItem`  
`struct FLightCardTemplateTreeItem`  
_L20-31_
- L22 _public member_ `TWeakObjectPtr<UDisplayClusterLightCardTemplate> LightCardTemplate;`
- L23 _public member_ `FName TemplateName;`
- L24 _public member_ `TSharedPtr<FSlateBrush> SlateBrush;`
- L26 _public function_ `FLightCardTemplateTreeItem()`
- L30 _public prototype_ `bool IsFavorite() const;` — If the template is a user favorite

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Outliner/DisplayClusterLightCardOutlinerColumns.h` (Private)


#### class `FDisplayClusterLightCardOutlinerHiddenInGameColumn`  
`class FDisplayClusterLightCardOutlinerHiddenInGameColumn : public FSceneOutlinerGutter`  
_L14-29_
- inherits: `FSceneOutlinerGutter`
- L17 _public function_ `FDisplayClusterLightCardOutlinerHiddenInGameColumn(ISceneOutliner& SceneOutliner) : FSceneOutlinerGutter(SceneOutliner)`
- L18 _public function_ `virtual ~FDisplayClusterLightCardOutlinerHiddenInGameColumn()`
- L19 _public prototype_ `static FName GetID();`
- L20 _public prototype_ `static FText GetDisplayText();`
- L23 _public function_ `virtual FName GetColumnID() override`
- L24 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L25 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L26 _public function_ `virtual bool SupportsSorting() const override`
- L27 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Outliner/DisplayClusterLightCardOutlinerMode.h` (Private)


#### class `FDisplayClusterLightCardOutlinerMode`  
`class FDisplayClusterLightCardOutlinerMode final : public FActorMode`  
_L14-93_
- inherits: `FActorMode`
- desc: Custom outliner mode for the light card editor based on FActorBrowsingMode. The primary goal is to allow basic actor functionality such as selecting actors locally, creating folders, and drag & drop. Selection should occur locally when possible and not update the GEditor selection. Additionally the context menu is cleaned up.
- L18 _public prototype_ `FDisplayClusterLightCardOutlinerMode(SSceneOutliner* InSceneOutliner, TWeakPtr<SDisplayClusterLightCardOutliner> InLightCardOutliner, TWeakObjectPtr<UWorld> InSpecifiedWorldToDisplay = nullptr);`
- L23 _public prototype_ `virtual void SynchronizeSelection() override;`
- L24 _public function_ `virtual bool IsInteractive() const override`
- L25 _public prototype_ `virtual FCreateSceneOutlinerMode CreateFolderPickerMode(const FFolder::FRootObject& InRootObject = FFolder::GetInvalidRootObject()) const override;`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L27 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L28 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L29 _public function_ `virtual bool ShouldShowFolders() const override`
- L30 _public function_ `virtual bool SupportsCreateNewFolder() const override`
- L31 _public function_ `virtual bool ShowStatusBar() const override`
- L32 _public function_ `virtual bool ShowViewButton() const override`
- L33 _public function_ `virtual bool ShowFilterOptions() const override`
- L34 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L35 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L36 _public prototype_ `virtual bool CanDelete() const override;`
- L37 _public prototype_ `virtual bool CanRename() const override;`
- L38 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L39 _public prototype_ `virtual bool CanCut() const override;`
- L40 _public prototype_ `virtual bool CanCopy() const override;`
- L41 _public prototype_ `virtual bool CanPaste() const override;`
- L42 _public prototype_ `virtual FFolder CreateNewFolder() override;`
- L43 _public prototype_ `virtual FFolder GetFolder(const FFolder& ParentPath, const FName& LeafName) override;`
- L44 _public prototype_ `virtual bool CreateFolder(const FFolder& NewFolder) override;`
- L45 _public prototype_ `virtual bool ReparentItemToFolder(const FFolder& FolderPath, const FSceneOutlinerTreeItemPtr& Item) override;`
- L46 _public function_ `virtual bool CanSupportDragAndDrop() const override`
- L47 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L48 _public prototype_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const override;`
- L49 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L50 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L53 _public prototype_ `void OnEditCutActorsBegin();` — Called by engine when edit cut actors begins
- L56 _public prototype_ `void OnEditCutActorsEnd();` — Called by engine when edit cut actors ends
- L59 _public prototype_ `void OnEditCopyActorsBegin();` — Called by engine when edit copy actors begins
- L62 _public prototype_ `void OnEditCopyActorsEnd();` — Called by engine when edit copy actors ends
- L65 _public prototype_ `void OnEditPasteActorsBegin();` — Called by engine when edit paste actors begins
- L68 _public prototype_ `void OnEditPasteActorsEnd();` — Called by engine when edit paste actors ends
- L71 _public prototype_ `void OnDuplicateActorsBegin();` — Called by engine when edit duplicate actors begins
- L74 _public prototype_ `void OnDuplicateActorsEnd();` — Called by engine when edit duplicate actors ends
- L77 _public prototype_ `void OnDeleteActorsBegin();` — Called by engine when edit delete actors begins
- L80 _public prototype_ `void OnDeleteActorsEnd();` — Called by engine when edit delete actors ends
- L83 _private prototype_ `static void RegisterContextMenu();`
- L84 _private prototype_ `bool CanPasteFoldersOnlyFromClipboard() const;`
- L85 _private prototype_ `bool GetFolderNamesFromPayload(const FSceneOutlinerDragDropPayload& InPayload, TArray<FName>& OutFolders, FFolder::FRootObject& OutCommonRootObject) const;`
- L86 _private prototype_ `FFolder GetWorldDefaultRootFolder() const;`
- L89 _private prototype_ `void UpdateGlobalActorSelection();` — Updates GEditor selection
- L92 _private member_ `TWeakPtr<SDisplayClusterLightCardOutliner> LightCardOutliner;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Outliner/SDisplayClusterLightCardOutliner.h` (Private)


#### class `SDisplayClusterLightCardOutliner`  
`class SDisplayClusterLightCardOutliner : public SCompoundWidget`  
_L22-135_
- inherits: `SCompoundWidget`
- desc: Displays all of the light cards associated with a particular display cluster root actor in a list view
- L35 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterLightCardOutliner)`
- L39 _public prototype_ `virtual ~SDisplayClusterLightCardOutliner() override;`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FDisplayClusterLightCardEditor> InLightCardEditor, TSharedPtr<FUICommandList> InCommandList);`
- L43 _public prototype_ `void SetRootActor(ADisplayClusterRootActor* NewRootActor);`
- L45 _public function_ `const TArray<TSharedPtr<FStageActorTreeItem>>& GetStageActorTreeItems() const`
- L48 _public prototype_ `void GetSelectedActors(TArray<AActor*>& OutSelectedActors) const;` — Gets a list of light card actors that are currently selected in the list
- L51 _public prototype_ `void SelectActors(const TArray<AActor*>& ActorsToSelect);` — Select light cards in the outliner
- L54 _public prototype_ `void RestoreCachedSelection();` — Restores the last valid cached selection to the outliner
- L59 _public prototype_ `bool CanDeleteSelectedFolder() const;`
- L60 _public prototype_ `bool CanCutSelectedFolder() const;`
- L61 _public prototype_ `bool CanCopySelectedFolder() const;`
- L62 _public prototype_ `bool CanPasteSelectedFolder() const;`
- L65 _public prototype_ `bool CanRenameSelectedItem() const;` — If either a folder or actor should be renamed
- L67 _public prototype_ `void RenameSelectedItem();` — Rename the selected folder or actor
- L71 _private prototype_ `void CreateWorldOutliner();` — Creates a world outliner based on the root actor world
- L77 _private prototype_ `bool FillActorList();` — Fill the outliner with available actors @return True if the list has been modified
- L80 _private prototype_ `void OnOutlinerSelectionChanged(FSceneOutlinerTreeItemPtr TreeItem, ESelectInfo::Type Type);` — Called when the user clicks on a selection in the outliner
- L83 _private prototype_ `TSharedPtr<FStageActorTreeItem> GetStageActorTreeItemFromOutliner(FSceneOutlinerTreeItemPtr InOutlinerTreeItem) const;` — Return our stage actor tree item from the outliner tree item
- L86 _private prototype_ `AActor* GetActorFromTreeItem(FSceneOutlinerTreeItemPtr InOutlinerTreeItem) const;` — Return an actor if the tree item is an actor tree item
- L88 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L91 _private prototype_ `void RegisterContextMenu(FName& InName, struct FToolMenuContext& InContext);` — Registers a context menu for use with tool menus
- L95 _private member_ `TWeakPtr<FDisplayClusterLightCardEditor> LightCardEditorPtr;` — Pointer to the light card editor that owns this widget
- L98 _private member_ `TArray<TSharedPtr<FStageActorTreeItem>> StageActorTree;` — A hierarchical list of stage actor tree items to be displayed in the tree view
- L101 _private member_ `TMap<TObjectPtr<AActor>, TSharedPtr<FStageActorTreeItem>> TrackedActors;` — All actors currently tracked by the scene outliner
- L104 _private member_ `TArray<FSceneOutlinerTreeItemPtr> CachedOutlinerItems;` — Cached items currently selected. Used for synchronizing with the outliner mode
- L107 _private member_ `TArray<TSharedPtr<FStageActorTreeItem>> StageActorTreeItems;` — A flattened list of all the light card actors being displayed in the tree view
- L113 _private member_ `TArray<TWeakObjectPtr<AActor>> NonOutlinerSelectedActors;` — Additional selected actors that aren't visible in the outliner hierarchy. We store these to avoid trampling the light card editor's selection, which may include actors that aren't displayed in the outliner.
- L116 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActor;` — The active root actor whose light cards are being displayed
- L119 _private member_ `TSharedPtr<SSceneOutliner> SceneOutliner;` — The scene outliner managed by this widget
- L122 _private member_ `TWeakPtr<ISceneOutlinerTreeItem> MostRecentSelectedItem;` — The most recently selected item from the outliner
- L125 _private member_ `FDelegateHandle SceneOutlinerSelectionChanged;` — Called when the outliner makes a selection change
- L128 _private member_ `TSharedPtr<FExtender> Extenders;` — Extenders for menus
- L131 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Mapped commands for this list
- L134 _private member_ `bool bIsOutlinerChangingSelection = false;` — If the outliner is responsible for changing the actor selection

#### struct `SDisplayClusterLightCardOutliner::FStageActorTreeItem`  
`struct FStageActorTreeItem`  
_L25-32_
- L27 _public member_ `TWeakObjectPtr<AActor> Actor;`
- L29 _public function_ `FStageActorTreeItem() : Actor(nullptr)`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Settings/DisplayClusterLightCardEditorSettings.h` (Private)


#### class `UDisplayClusterLightCardEditorProjectSettings`  
`class UDisplayClusterLightCardEditorProjectSettings : public UObject`  
_L17-47_
- reflection: `UCLASS(config = Editor, defaultconfig, meta = (DisplayClusterMultiUserInclude))`
- inherits: `UObject`
- desc: Default settings shared across users of the project
- L22 _public prototype_ `UDisplayClusterLightCardEditorProjectSettings();`
- L26 _public member_ `FDirectoryPath LightCardTemplateDefaultPath;` — `UPROPERTY(config, EditAnywhere, Category = Templates)` — The default path to save new light card templates
- L30 _public member_ `TSoftObjectPtr<UDisplayClusterLightCardTemplate> DefaultLightCardTemplate;` — `UPROPERTY(config, EditAnywhere, Category = Templates)` — The default template to use when creating a new light card
- L34 _public member_ `TSoftObjectPtr<UDisplayClusterLightCardTemplate> DefaultFlagTemplate;` — `UPROPERTY(config, EditAnywhere, Category = Templates)` — The default template to use when creating a new flag
- L38 _public member_ `bool bDisplayLightCardLabels;` — `UPROPERTY()` — Whether light card labels should be displayed. Handled through the light card editor
- L42 _public member_ `EDisplayClusterLabelFlags LightCardLabelFlags;` — `UPROPERTY()` — Flags for the label
- L46 _public member_ `float LightCardLabelScale;` — `UPROPERTY(config, EditAnywhere, Category = Labels)` — The scale to use for light card labels

#### struct `FDisplayClusterLightCardEditorRecentItem`  
`struct FDisplayClusterLightCardEditorRecentItem`  
_L50-77_
- reflection: `USTRUCT()`
- L54 _public member_ `static const FName Type_LightCard;`
- L55 _public member_ `static const FName Type_Flag;`
- L56 _public member_ `static const FName Type_LightCardTemplate;`
- L57 _public member_ `static const FName Type_Dynamic;`
- L61 _public member_ `TSoftObjectPtr<UObject> ObjectPath;` — `UPROPERTY()` — Path of object to instantiate
- L65 _public member_ `FName ItemType;` — `UPROPERTY()` — Type of item placed
- L67 _public prototype_ `FText GetItemDisplayName() const;`
- L68 _public prototype_ `const FSlateBrush* GetSlateBrush() const;`
- L70 _public function_ `bool operator==(const FDisplayClusterLightCardEditorRecentItem& Rhs) const`
- L76 _private member_ `mutable TSharedPtr<FSlateBrush> SlateBrush;`

#### class `UDisplayClusterLightCardEditorSettings`  
`class UDisplayClusterLightCardEditorSettings : public UObject`  
_L83-109_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Editor preferences unique to this user
- L88 _public prototype_ `UDisplayClusterLightCardEditorSettings();`
- L92 _public member_ `TArray<FDisplayClusterLightCardEditorRecentItem> RecentlyPlacedItems;` — `UPROPERTY(config)` — Items recently placed by the user
- L96 _public member_ `uint8 ProjectionMode;` — `UPROPERTY(config)` — Last used projection mode user has set
- L100 _public member_ `uint8 RenderViewportType;` — `UPROPERTY(config)` — Last used viewport type user has set
- L104 _public member_ `bool bDisplayIcons;` — `UPROPERTY(config, EditAnywhere, Category = Icons)` — Display icons in the light card editor where applicable
- L108 _public member_ `float IconScale;` — `UPROPERTY(config, EditAnywhere, Category = Icons)` — Scale icon size where applicable

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Viewport/DisplayClusterLightCardEditorViewportClient.h` (Private)


#### class `FDisplayClusterLightCardEditorViewportClient`  
`class FDisplayClusterLightCardEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FDisplayClusterLightCardEditorViewportClient>`  
_L26-409_
- inherits: `FEditorViewportClient,TSharedFromThis<FDisplayClusterLightCardEditorViewportClient>`
- desc: Viewport Client for the preview viewport
- L28 _private typedef_ `using Super = FEditorViewportClient;`
- L45 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNextSceneRefresh);`
- L48 _public prototype_ `FDisplayClusterLightCardEditorViewportClient(FPreviewScene& InPreviewScene, const TWeakPtr<SDisplayClusterLightCardEditorViewport>& InEditorViewportWidget);`
- L53 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — FEditorViewportClient
- L54 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L55 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L56 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L57 _public function_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override`
- L58 _public function_ `virtual bool CanCycleWidgetMode() const override`
- L59 _public function_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override`
- L60 _public prototype_ `virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily, const int32 StereoViewIndex = INDEX_NONE) override;`
- L61 _public function_ `virtual bool IsLevelEditorClient() const override`
- L62 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L63 _public prototype_ `virtual bool InputWidgetDelta(FViewport* InViewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override;`
- L64 _public prototype_ `virtual void TrackingStarted(const FInputEventState& InInputState, bool bIsDraggingWidget, bool bNudge) override;`
- L65 _public prototype_ `virtual void TrackingStopped() override;`
- L66 _public prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L67 _public prototype_ `virtual void BeginCameraMovement(bool bHasMovement) override;`
- L68 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* Viewport,int32 X,int32 Y) override;`
- L69 _public function_ `virtual ELevelViewportType GetViewportType() const override`
- L70 _public function_ `virtual bool HasDropPreviewActors() const override`
- L71 _public prototype_ `virtual void DestroyDropPreviewActors() override;`
- L72 _public prototype_ `virtual bool UpdateDropPreviewActors(int32 MouseX, int32 MouseY, const TArray<UObject*>& DroppedObjects, bool& bOutDroppedObjectsVisible, UActorFactory* FactoryToUse) override;`
- L73 _public prototype_ `virtual bool DropObjectsAtCoordinates(int32 MouseX, int32 MouseY, const TArray<UObject*>& DroppedObjects, TArray<AActor*>& OutNewActors, bool bOnlyDropOnTarget, bool bCreateDropPreview, bool bSelectActors, UActorFactory* FactoryToUse) override;`
- L77 _public function_ `FOnNextSceneRefresh& GetOnNextSceneRefresh()` — Returns a delegate that is invoked on the next scene refresh. The delegate is cleared afterwards
- L87 _public prototype_ `void UpdatePreviewActor(ADisplayClusterRootActor* RootActor, bool bForce = false, EDisplayClusterLightCardEditorProxyType ProxyType = EDisplayClusterLightCardEditorProxyType::All, AActor* StageActor = nullptr);` — Update the spawned preview actor from a root actor in the level @param RootActor The new root actor to use. Accepts nullptr @param bForce Force the update even if the RootActor hasn't changed @param ProxyType The proxy type to destroy and update @param StageActor Limit the update to a single stage actor
- L92 _public prototype_ `void UpdateProxyTransforms();` — Only update required transform values of proxies
- L95 _public prototype_ `void UpdateProxyTransformFromLevelInstance(AActor* InLevelInstance);` — Update transforms value for a proxy from a level instance
- L98 _public prototype_ `void DestroyProxies(EDisplayClusterLightCardEditorProxyType ProxyType);` — Remove proxies of the specified type
- L101 _public prototype_ `void DestroyProxy(AActor* Actor);` — Remove a proxy that is or belongs to the given actor
- L104 _public prototype_ `void SelectActors(const TArray<AActor*>& ActorsToSelect);` — Selects the actor proxies that correspond to the specified actors
- L107 _public prototype_ `bool HasSelection() const;` — Gets whether any items are selected in the viewport
- L109 _public function_ `FDisplayClusterLightCardEditorWidget::EWidgetMode GetEditorWidgetMode() const`
- L110 _public prototype_ `void SetEditorWidgetMode(FDisplayClusterLightCardEditorWidget::EWidgetMode InWidgetMode);`
- L113 _public function_ `EDisplayClusterMeshProjectionType GetProjectionMode() const` — Gets the current projection mode of the editor viewport
- L116 _public function_ `ELevelViewportType GetRenderViewportType() const` — Gets the current viewport type the viewport is being rendered with
- L119 _public prototype_ `void SetProjectionMode(EDisplayClusterMeshProjectionType InProjectionMode, ELevelViewportType InViewportType);` — Sets the projection mode and the render viewport type of the viewport
- L122 _public prototype_ `float GetProjectionModeFOV(EDisplayClusterMeshProjectionType InProjectionMode) const;` — Gets the field of view of the specified projection mode
- L125 _public prototype_ `void SetProjectionModeFOV(EDisplayClusterMeshProjectionType InProjectionMode, float NewFOV);` — Sets the field of view of the specified projection mode
- L128 _public prototype_ `void ResetCamera(bool bLocationOnly = false);` — Resets the camera to the initial rotation / position
- L131 _public prototype_ `void FrameSelection();` — Frames the currently selected items in the viewport
- L134 _public prototype_ `void CycleCoordinateSystem();` — Cycles the editor widget's coordinate system between cartesian and spherical
- L137 _public function_ `FDisplayClusterLightCardEditorHelper::ECoordinateSystem GetCoordinateSystem() const` — Gets the editor widget's current coordinate system
- L140 _public prototype_ `void SetCoordinateSystem(FDisplayClusterLightCardEditorHelper::ECoordinateSystem NewCoordinateSystem);` — Sets the editor widget's coordinate system to the specified coordinate system
- L148 _public prototype_ `void MoveActorTo(const FDisplayClusterWeakStageActorPtr& Actor, const FDisplayClusterLightCardEditorHelper::FSphericalCoordinates& SphericalCoords) const;` — Moves specified card to desired coordinates. Actual radius will be based on flush constraint and Actor's RadialOffset. @param Actor The actor that we are moving @param SphericalCoords specifies desired location of actor in spherical coordinates with respect to view point.
- L151 _public prototype_ `void CenterActorInView(const FDisplayClusterWeakStageActorPtr& Actor);` — Places the given light card in the middle of the current viewport
- L154 _public prototype_ `void MoveSelectedActorsToPixel(const FIntPoint& PixelPos);` — Moves all selected light cards to the specified pixel position
- L157 _public prototype_ `void MoveActorsToPixel(const FIntPoint& PixelPos, const TArray<FDisplayClusterWeakStageActorPtr>& InActors);` — Moves all given actors to the specified pixel position
- L160 _public function_ `EInputMode GetInputMode()` — Returns the current input mode
- L163 _public prototype_ `void EnterDrawingLightCardMode();` — Requests that we enter light card drawing input mode
- L166 _public prototype_ `void ExitDrawingLightCardMode();` — Requests that we exit light card drawing input mode (and go back to idle/normal)
- L169 _public function_ `bool HasCalledPostEditChangeProperty() const` — If the viewport client is responsible for the post edit change property call
- L173 _private prototype_ `void BeginTransaction(const FText& Description);` — Initiates a transaction.
- L176 _private prototype_ `void EndTransaction();` — Ends the current transaction, if one exists.
- L179 _private prototype_ `void GetScenePrimitiveComponents(TArray<UPrimitiveComponent*>& OutPrimitiveComponents);` — Gets a list of all primitive components to be rendered in the scene
- L182 _private prototype_ `void GetSceneViewInitOptions(FSceneViewInitOptions& OutViewInitOptions);` — Gets the scene view init options to use to create scene views for the preview scene
- L185 _private prototype_ `void GetNormalMapSceneViewInitOptions(FIntPoint NormalMapSize, float NormalMapFOV, const FVector& ViewDirection, FSceneViewInitOptions& OutViewInitOptions);` — Gets the scene view init options to use when rendering the normal map cache
- L188 _private prototype_ `UDisplayClusterConfigurationViewport* FindViewportForPrimitiveComponent(UPrimitiveComponent* PrimitiveComponent);` — Gets the viewport that is attached to the specified primitive component
- L191 _private prototype_ `USceneComponent* FindProjectionOriginComponent(const ADisplayClusterRootActor* InRootActor) const;` — Finds a suitable primitive component on the stage actor to use as a projection origin
- L194 _private prototype_ `bool IsActorSelected(const AActor* Actor);` — Callback to check if an actor is among the list of selected actors
- L197 _private prototype_ `void SelectActor(AActor* Actor, bool bAddToSelection = false);` — Adds the specified actor the the list of selected actors
- L200 _private prototype_ `void PropagateActorSelection();` — Notifies the light card editor of the currently selected actors so that it may update other UI components to match
- L203 _private prototype_ `void PropagateActorTransform(const FDisplayClusterWeakStageActorPtr& ActorProxy);` — Propagates the specified actor proxy's transform back to its level instance version
- L206 _private prototype_ `void MoveSelectedActors(FViewport* InViewport, EAxisList::Type CurrentAxis);` — Moves the currently selected actors
- L209 _private prototype_ `void MoveSelectedUVActors(FViewport* InViewport, EAxisList::Type CurrentAxis);` — Moves the currently selected UV actors
- L212 _private prototype_ `void ScaleSelectedActors(FViewport* InViewport, EAxisList::Type CurrentAxis);` — Scales the currently selected actors
- L215 _private prototype_ `FVector2D GetActorScaleDelta(FViewport* InViewport, const FDisplayClusterWeakStageActorPtr& InActor, EAxisList::Type CurrentAxis);` — Determines the appropriate scale delta needed to scale the actor
- L218 _private prototype_ `void SpinSelectedActors(FViewport* InViewport);` — Rotates the currently selected actors around the actor's normal axis
- L221 _private prototype_ `double GetActorSpinDelta(FViewport* InViewport);` — Determines the appropriate spin delta needed to rotate the light card
- L224 _private prototype_ `AActor* TraceScreenForActor(const FSceneView& View, int32 HitX, int32 HitY);` — Traces to find the actor corresponding to a click on a stage screen
- L227 _private prototype_ `FVector ProjectWorldPosition(const FVector& UnprojectedWorldPosition, const FViewMatrices& ViewMatrices) const;` — Projects the specified world position to the viewport's current projection space
- L230 _private prototype_ `bool WorldToScreenDirection(const FSceneView& View, const FVector& WorldPos, const FVector& WorldDirection, FVector2D& OutScreenDir);` — Converts a direction vector from world space to screen screen space, and returns true of the direction vector is on the screen
- L233 _private prototype_ `bool CalcEditorWidgetTransform(FTransform& WidgetTransform);` — Calculates the world transform to render the editor widget with to align it with the selected actor
- L236 _private prototype_ `bool IsLocationCloseToEdge(const FVector& InPosition, const FViewport* InViewport = nullptr, const FSceneView* InView = nullptr, FVector2D* OutPercentageToEdge = nullptr);` — Checks if the location is approaching the edge of the view space
- L239 _private prototype_ `void FixCameraTransform();` — Called each tick to ensure the viewport camera is in the appropriate place based on the projection mode
- L242 _private prototype_ `void SaveProjectionCameraTransform();` — Saves the current camera transform for the current projection mode
- L245 _private prototype_ `void RestoreProjectionCameraTransform();` — Restores the saved camera transform for the current projection mode
- L248 _private prototype_ `void ResetProjectionViewConfigurations();` — Resets the stored view configurations to default values for each projection mode
- L251 _private prototype_ `void TrySetShouldCheckHitProxy();` — Attempt to set bShouldCheckHitProxy
- L254 _private prototype_ `void CreateDrawnLightCard(const TArray<FIntPoint>& MousePositions);` — Creates a new light card using a polygon alpha mask as defined by the given mouse positions on the viewport
- L257 _private prototype_ `double CalculateFinalActorDistance(double FlushDistance, double DesiredOffsetFromFlush = 0.) const;` — Calculates the final distance from the origin of an actor, given its flush distance and a desired offset
- L292 _private prototype_ `const FActorProxy* FindActorProxyFromLevelInstance(AActor* InLevelInstance) const;` — Find the actor proxy if it exists from a level instance
- L295 _private prototype_ `const FActorProxy* FindActorProxyFromActor(AActor* InActor) const;` — Find the actor proxy from either the proxy itself or the actor the proxy belongs to
- L298 _private prototype_ `AActor* CreateStageActorProxy(AActor* InLevelInstance);` — Create a stage actor proxy
- L301 _private prototype_ `void UpdateProxyTransforms(const FActorProxy& InActorProxy);` — Update the transforms for the specific proxy
- L304 _private prototype_ `void OnSequencerTimeChanged(TWeakPtr<class ISequencer> InSequencer);` — When the time in a sequencer has changed
- L307 _private member_ `TWeakPtr<FSceneViewport> SceneViewportPtr;`
- L308 _private member_ `TWeakPtr<SDisplayClusterLightCardEditorViewport> LightCardEditorViewportPtr;`
- L309 _private member_ `TWeakPtr<FDisplayClusterLightCardEditor> LightCardEditorPtr;`
- L310 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActorProxy;`
- L311 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActorLevelInstance;`
- L312 _private member_ `TSet<AActor*> ActorsRefreshing;`
- L315 _private member_ `TSet<EDisplayClusterLightCardEditorProxyType> ProxyTypesRefreshing;` — Proxy types that are currently refreshing over 1-2 frames
- L318 _private member_ `float RootActorBoundingRadius = 0.0f;` — The radius of the bounding sphere that entirely encapsulates the root actor
- L330 _private member_ `TArray<FActorProxy> ActorProxies;`
- L331 _private member_ `TArray<TWeakObjectPtr<UBillboardComponent>> BillboardComponentProxies;`
- L332 _private member_ `TArray<TWeakObjectPtr<UWidgetComponent>> WidgetComponentProxies;`
- L333 _private member_ `TArray<FDisplayClusterWeakStageActorPtr> SelectedActors;`
- L336 _private member_ `FCriticalSection SpriteComponentCS;` — Billboards and widgets are accessed from the render thread and game thread for sprite rendering
- L339 _private member_ `FViewMatrices SpriteViewMatrices;` — View matrices set per tick if there are any sprites being rendered
- L342 _private member_ `FDisplayClusterWeakStageActorPtr LastSelectedActor;` — The actor in the selected actor list that was selected last
- L345 _private member_ `TArray<FDisplayClusterWeakStageActorPtr> DropPreviewLightCards;` — Light card preview actors being dropped on the scene
- L348 _private member_ `int32 PreviewRendererId = -1;` — The index of the scene preview renderer returned from IDisplayClusterScenePreview
- L351 _private member_ `TSharedPtr<FDisplayClusterLightCardEditorHelper> ProjectionHelper;` — Helper used to convert between screen and world coordinates for actor positions.
- L354 _private member_ `TSharedPtr<FDisplayClusterLightCardEditorWidget> EditorWidget;` — The LC editor widget used to manipulate actors
- L357 _private member_ `FTransform CachedEditorWidgetWorldTransform;` — The cached editor widget transform in unprojected world space
- L360 _private member_ `FDisplayClusterLightCardEditorHelper::ECoordinateSystem EditorWidgetCoordinateSystem = FDisplayClusterLightCardEditorHelper::ECoordinateSystem::Spherical;` — The current coordinate system of the editor widget
- L363 _private member_ `FVector DragWidgetOffset;` — The offset between the widget's origin and the place it was clicked when a drag action was started
- L366 _private member_ `FIntPoint LastWidgetMousePos;` — The mouse position registered on the previous widget input pass
- L369 _private member_ `TOptional<FVector> DesiredLookAtLocation;` — The location the camera should be looking at
- L372 _private member_ `float DesiredLookAtSpeed = 1.f;` — The current speed to use when looking at a location
- L375 _private member_ `float MaxDesiredLookAtSpeed = 5.f;` — The maximum speed to use when looking at a location
- L378 _private member_ `float EdgePercentageLookAtThreshold = 0.1f;` — The percentage to the edge of the view which should trigger auto tilt and auto pan
- L381 _private member_ `EDisplayClusterMeshProjectionType ProjectionMode = EDisplayClusterMeshProjectionType::Azimuthal;` — The current projection mode the 3D viewport is being displayed with
- L384 _private member_ `ELevelViewportType RenderViewportType = LVT_Perspective;` — The viewport type (perspective or orthogonal) to use when rendering the viewport. Separate from ViewportType since ViewportType also determines input functionality
- L387 _private member_ `TWeakObjectPtr<USceneComponent> ProjectionOriginComponent;` — The component of the root actor that is acting as the projection origin. Can be either the root component (stage origin) or a view point component
- L390 _private member_ `TArray<FProjectionViewConfiguration> ProjectionViewConfigurations;` — Stores each projecion mode's view configuration separately so they can be restored when the projection mode is selected
- L393 _private member_ `float FOVScrollIncrement = 5.0f;` — The increment to change the FOV by when using the scroll wheel
- L396 _private member_ `EInputMode InputMode = EInputMode::Idle;` — Current input mode
- L399 _private member_ `TArray<FIntPoint> DrawnMousePositions;` — Array of mouse positions that will be used to spawn a new light card with the shape of the drawn polygon
- L402 _private member_ `FOnNextSceneRefresh OnNextSceneRefreshDelegate;` — Multicast delegate that stores callbacks to be invoked the next time the scene is refreshed
- L405 _private member_ `bool bDisableCustomRenderer = false;` — A flag that disables drawing with the custom projection renderer and instead renders the viewport client with the editor's default renderer
- L408 _private member_ `bool bHasCalledPostEditChangeProperty = false;` — True if the viewport client has triggered the post edit change property call

#### enum `FDisplayClusterLightCardEditorViewportClient::EInputMode`  
`enum class EInputMode`  
_L33-42_
- desc: State machine that helps keep track of the context to which user inputs apply (e.g. mouse buttons, key presses)
- L35 _public enumerator_ `Idle`
- L38 _public enumerator_ `DraggingActor` — Indicates that the user is dragging an actor in the viewport
- L41 _public enumerator_ `DrawingLightCard` — Indicates that the user is drawing a light card in the viewport

#### struct `FDisplayClusterLightCardEditorViewportClient::FActorProxy`  
`struct FActorProxy`  
_L259-271_
- L261 _public member_ `FDisplayClusterWeakStageActorPtr LevelInstance;`
- L262 _public member_ `FDisplayClusterWeakStageActorPtr Proxy;`
- L264 _public function_ `FActorProxy(const AActor* InLevelInstance, const AActor* InProxy) : LevelInstance(InLevelInstance) , Proxy(InProxy)`
- L270 _public function_ `bool operator==(const AActor* Actor) const`

#### struct `FDisplayClusterLightCardEditorViewportClient::FSpriteProxy`  
`struct FSpriteProxy`  
_L273-289_
- L275 _public member_ `TObjectPtr<UTexture2D> Sprite;`
- L276 _public member_ `FVector WorldPosition;`
- L277 _public member_ `float U;`
- L278 _public member_ `float UL;`
- L279 _public member_ `float V;`
- L280 _public member_ `float VL;`
- L281 _public member_ `float ScreenSize;`
- L282 _public member_ `float SpriteScale;`
- L283 _public member_ `float OpacityMaskRefVal;`
- L285 _public member_ `bool bIsScreenSizeScaled = false;`
- L288 _public prototype_ `static FSpriteProxy FromBillboard(const UBillboardComponent* InBillboardComponent);` — Construct a sprite proxy from a billboard component

#### struct `FDisplayClusterLightCardEditorViewportClient::FProjectionViewConfiguration`  
`struct FProjectionViewConfiguration`  
_L321-328_
- desc: Stores view configuration values (view transform and field of view) for the supported projection modes
- L324 _public member_ `FViewportCameraTransform PerspectiveTransform = FViewportCameraTransform();`
- L325 _public member_ `FViewportCameraTransform OrthographicTransform = FViewportCameraTransform();`
- L326 _public member_ `float PerspectiveFOV = 0.0f;`
- L327 _public member_ `float OrthographicFOV = 0.0f;`

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNextSceneRefresh);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Viewport/DisplayClusterLightCardEditorWidget.h` (Private)


#### class `FDisplayClusterLightCardEditorWidget`  
`class FDisplayClusterLightCardEditorWidget`  
_L15-113_
- desc: Widget used to manipulate entities in the light card editor's viewport
- L19 _public member_ `constexpr static float ReferenceResolution = 1920.0f;` — The default reference resolution that the size and length constants are defined relative to
- L22 _public member_ `constexpr static float AxisLength = 100.f;` — The length of the widget's axes, in pixels
- L25 _public member_ `constexpr static float AxisThickness = 5.f;` — The thickness of the widget's axes, in pixels
- L28 _public member_ `constexpr static float AxisCapSize = 15.f;` — The size of the axes caps
- L31 _public member_ `constexpr static float OriginSize = 10.0f;` — The size of the axes origin
- L34 _public member_ `constexpr static float CirlceRadius = 100.0f;` — The size of the rotation circle, in pixels
- L37 _public member_ `constexpr static float CircleThickness = 5.f;` — The thickness of the rotation circle, in pixels
- L39 _public member_ `constexpr static FLinearColor AxisColorX = FLinearColor(0.594f, 0.0197f, 0.0f);`
- L40 _public member_ `constexpr static FLinearColor AxisColorY = FLinearColor(0.1349f, 0.3959f, 0.0f);`
- L41 _public member_ `constexpr static FLinearColor AxisColorZ = FLinearColor(0.0251f, 0.207f, 0.85f);`
- L42 _public member_ `constexpr static FLinearColor HighlightColor = FLinearColor(1.0f, 1.0f, 0.0f);`
- L53 _public prototype_ `FDisplayClusterLightCardEditorWidget();`
- L56 _public prototype_ `void Tick(const FDisplayClusterLightCardEditorViewportClient* ViewportClient, float InDeltaSeconds);` — Called from the game thread, allows the widget to perform any game thread specific actions
- L58 _public prototype_ `void Draw(const FSceneView* View, const FDisplayClusterLightCardEditorViewportClient* ViewportClient, FPrimitiveDrawInterface* PDI, bool bDrawZAxis);`
- L60 _public function_ `EWidgetMode GetWidgetMode() const`
- L61 _public function_ `void SetWidgetMode(EWidgetMode NewWidgetMode)`
- L63 _public function_ `void SetTransform(const FTransform& NewTransform)`
- L64 _public function_ `void SetProjectionTransform(const FDisplayClusterMeshProjectionTransform& NewProjectionTransform)`
- L65 _public function_ `void SetHighlightedAxis(EAxisList::Type InAxis)`
- L66 _public function_ `void SetWidgetScale(float InWidgetScale)`
- L70 _private prototype_ `void DrawAxis(FPrimitiveDrawInterface* PDI, EAxisList::Type Axis, float SizeScalar, float LengthScalar, float OrthoScalar);` — Draws the specified axis to the PDI, sizing and coloring it appropriately
- L73 _private prototype_ `void DrawOrigin(FPrimitiveDrawInterface* PDI, float SizeScalar, float OrthoScalar);` — Draws the widget origin to the PDI, sizing and coloring it appropriately
- L75 _private prototype_ `void DrawCircle(FPrimitiveDrawInterface* PDI, EAxisList::Type Axis, float SizeScalar, float LengthScalar);`
- L78 _private prototype_ `FVector GetGlobalAxis(EAxisList::Type Axis) const;` — Gets the axis vector in global coordinates for the specified axis
- L81 _private prototype_ `FLinearColor GetAxisColor(EAxisList::Type Axis) const;` — Gets the color for the specified axis
- L84 _private prototype_ `float GetLengthScreenScalar(const FSceneView* View, const FDisplayClusterLightCardEditorViewportClient* ViewportClient, const FVector& Origin) const;` — Calculates a scalar to use to keep lengths and lines a fixed size on the screen regardless of DPI, viewport size, FOV, or distance from the view point.
- L87 _private prototype_ `float GetSizeScreenScalar(const FSceneView* View, const FDisplayClusterLightCardEditorViewportClient* ViewportClient) const;` — Calculates a scalar to use to keep sizes a fixed size on the screen regardless of DPI, viewport size, FOV, or distance from the view point.
- L91 _private member_ `UTexture2D* TranslateOriginTexture;` — Texture to use to render the translation widget origin
- L94 _private member_ `UTexture2D* ScaleOriginTexture;` — Texture to use to render the scale widget origin
- L97 _private member_ `EWidgetMode WidgetMode = WM_Translate;` — The current mode the widget is in
- L100 _private member_ `FTransform Transform;` — The world transform to apply to the widget when rendering
- L103 _private member_ `FDisplayClusterMeshProjectionTransform ProjectionTransform;` — The projection transfrom to apply to the widget when rendering
- L106 _private member_ `EAxisList::Type HighlightedAxis = EAxisList::Type::None;` — The axis on the widget which should be highlighted
- L109 _private member_ `float WidgetScale = 1.f;` — A scale factor to scale the widget's rendered size
- L112 _private member_ `float DPIScale = 1.f;` — Cached DPI scale used to scale the widget's rendered size

#### enum `FDisplayClusterLightCardEditorWidget::EWidgetMode`  
`enum EWidgetMode`  
_L44-51_
- L46 _public enumerator_ `WM_Translate`
- L47 _public enumerator_ `WM_RotateZ`
- L48 _public enumerator_ `WM_Scale`
- L50 _public enumerator_ `WM_Max`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Viewport/DisplayClusterLightcardEditorViewport.h` (Private)


#### class `SDisplayClusterLightCardEditorViewport`  
`class SDisplayClusterLightCardEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L21-146_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- desc: Slate widget which renders our view client.
- L24 _public member_ `static const FVector ViewDirectionTop;`
- L25 _public member_ `static const FVector ViewDirectionBottom;`
- L26 _public member_ `static const FVector ViewDirectionLeft;`
- L27 _public member_ `static const FVector ViewDirectionRight;`
- L28 _public member_ `static const FVector ViewDirectionFront;`
- L29 _public member_ `static const FVector ViewDirectionBack;`
- L32 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterLightCardEditorViewport)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDisplayClusterLightCardEditor> InLightCardEditor, TSharedPtr<class FUICommandList> InCommandList);`
- L36 _public prototype_ `~SDisplayClusterLightCardEditorViewport();`
- L39 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider
- L40 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L41 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L45 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L48 _public function_ `TWeakPtr<FDisplayClusterLightCardEditor> GetLightCardEditor()`
- L50 _public prototype_ `void SetRootActor(ADisplayClusterRootActor* NewRootActor);`
- L53 _public prototype_ `TWeakObjectPtr<ADisplayClusterRootActor> GetRootActor() const;` — Return the active root actor for this viewport.
- L55 _public function_ `TSharedRef<FDisplayClusterLightCardEditorViewportClient> GetLightCardEditorViewportClient() const`
- L58 _public prototype_ `void SummonContextMenu();` — Summons the context menu within this viewport at the mouse's current position
- L62 _private prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport
- L63 _private prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L64 _private prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L65 _private prototype_ `virtual void BindCommands() override;`
- L66 _private prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L67 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L68 _private prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L69 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L73 _private prototype_ `TSharedRef<SWidget> MakeContextMenu();` — Create the popup context menu
- L76 _private prototype_ `void MakePlaceActorsSubMenu(FMenuBuilder& MenuBuilder);` — Create the submenu for placing actors
- L79 _private prototype_ `void SetEditorWidgetMode(FDisplayClusterLightCardEditorWidget::EWidgetMode InWidgetMode);` — Sets the widget mode for the editor viewport to the specified mode
- L82 _private prototype_ `bool IsEditorWidgetModeSelected(FDisplayClusterLightCardEditorWidget::EWidgetMode InWidgetMode) const;` — Returns true if the widget mode of the editor viewport matches the specified mode
- L85 _private prototype_ `void CycleEditorWidgetMode();` — Cycles the widget mode of the editor viewport
- L88 _private prototype_ `void SetProjectionMode(EDisplayClusterMeshProjectionType InProjectionMode, ELevelViewportType InViewportType);` — Sets the projection mode and viewport type of the editor viewport
- L91 _private prototype_ `bool IsProjectionModeSelected(EDisplayClusterMeshProjectionType InProjectionMode, ELevelViewportType InViewportType) const;` — Returns true if the editor viewport's projection mode and viewport type match the specified parameters
- L94 _private prototype_ `void SetViewDirection(FVector InViewDirection);` — Sets the direction of the editor viewport
- L97 _private prototype_ `void DrawLightCard();` — Handles the Draw LC button being pressed.
- L100 _private prototype_ `bool IsDrawingLightCard() const;` — Returns true if we are in light card drawing mode
- L103 _private prototype_ `void PasteLightCardsHere();` — Pastes any light cards in the clipboard and moves them to the cached mouse position
- L106 _private prototype_ `bool CanPasteLightCardsHere() const;` — Determines if there are any light cards in the clipboard that can be pasted
- L109 _private prototype_ `void AddLightCardHere();` — Adds a new light card and moves it to the cached mouse position
- L112 _private prototype_ `void AddFlagHere();` — Adds a new flag and moves it to the cached mouse position
- L115 _private prototype_ `void AddStageActorHere(UClass* InClass);` — Adds a new stage actor of the specified class and moves it to the cached mouse position
- L118 _private prototype_ `bool CanPlaceActorHere() const;` — If placing actors is allowed
- L119 _private prototype_ `bool CanPlaceActorHere(UClass* Class) const;`
- L122 _private prototype_ `void ToggleLabels();` — Toggles light card labels on or off
- L125 _private prototype_ `bool AreLabelsToggled() const;` — If light card labels are currently toggled
- L128 _private prototype_ `void ToggleIcons();` — Toggles all icons on or off
- L131 _private prototype_ `bool AreIconsToggled() const;` — If icons are currently toggled
- L135 _private member_ `TSharedPtr<FPreviewScene> PreviewScene;` — The preview scene to use by the viewport client to manage the preview 3D world
- L138 _private member_ `TSet<TSharedPtr<FScopedTransaction>> AddActorHereTransactions;` — Open transactions when using an 'Add Actor Here' method since they occur over multiple frames
- L141 _private member_ `TSharedPtr<FDisplayClusterLightCardEditorViewportClient> ViewportClient;` — Level viewport client
- L142 _private member_ `TWeakPtr<FDisplayClusterLightCardEditor> LightCardEditorPtr;`
- L145 _private member_ `FVector2D PasteHerePos;` — The cached mouse position used for the Paste Here command

### `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Public/IDisplayClusterLightCardEditor.h` (Public)


#### class `IDisplayClusterLightCardEditor`  
`class IDisplayClusterLightCardEditor : public IModuleInterface`  
_L15-60_
- inherits: `IModuleInterface`
- desc: Display Cluster Light Card Editor module interface
- L18 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L21 _public prototype_ `virtual ~IDisplayClusterLightCardEditor() = default;`
- L29 _public function_ `static inline IDisplayClusterLightCardEditor& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L54 _public prototype_ `virtual void ShowLabels(const FLabelArgs& InArgs) = 0;` — Show the light card labels for the given root actor and save current settings. @param InArgs The arguments for displaying labels.
- L59 _public prototype_ `virtual UDisplayClusterStageActorTemplate* GetDefaultLightCardTemplate() const = 0;` — Get the default template to use when creating a new light card

#### struct `IDisplayClusterLightCardEditor::FLabelArgs`  
`struct FLabelArgs : FDisplayClusterLabelConfiguration`  
_L44-47_
- inherits: `FDisplayClusterLabelConfiguration`
