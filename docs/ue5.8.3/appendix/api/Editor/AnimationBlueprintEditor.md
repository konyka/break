# Editor / AnimationBlueprintEditor

- module root: `Source/Editor/AnimationBlueprintEditor`
- headers: 31; symbols: 466
- symbol kinds: class=29, delegate=4, externvar=11, function=44, macro=2, member=76, namespace=1, prototype=291, struct=7, typedef=1
- DynamicallyLoadedModuleNames: AnimationEditor, AssetTools, ContentBrowser, DesktopPlatform, Documentation, MainFrame, SkeletonEditor
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AppFramework, BlueprintGraph, Core, CoreUObject, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, KismetCompiler, KismetWidgets, PropertyEditor, RHI, Slate, SlateCore, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: MessageLog, SkeletonEditor
- PublicDependencyModuleNames: EditorFramework, Kismet, Persona

### `Source/Editor/AnimationBlueprintEditor/Private/AnimGraphConnectionDrawingPolicy.h` (Private)


#### class `FAnimGraphConnectionDrawingPolicy`  
`class FAnimGraphConnectionDrawingPolicy : public FKismetConnectionDrawingPolicy`  
_L27-51_
- inherits: `FKismetConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph with an animation schema
- L31 _public prototype_ `FAnimGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);` — Constructor
- L34 _public prototype_ `virtual bool TreatWireAsExecutionPin(UEdGraphPin* InputPin, UEdGraphPin* OutputPin) const override;` — FKismetConnectionDrawingPolicy interface
- L35 _public prototype_ `virtual void BuildExecutionRoadmap() override;`
- L36 _public prototype_ `virtual void DetermineStyleOfExecWire(float& Thickness, FLinearColor& WireColor, bool& bDrawBubbles, const FTimePair& Times) override;`
- L37 _public prototype_ `virtual void DrawConnection(int32 LayerId, const FVector2f& Start, const FVector2f& End, const FConnectionParams& Params) override;`
- L38 _public prototype_ `virtual void BuildPinToPinWidgetMap(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries) override;`
- L39 _public prototype_ `virtual void ApplyHoverDeemphasis(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, float& Thickness, FLinearColor& WireColor) override;`
- L44 _private member_ `TMap<UEdGraphPin*, TArrayView<const SGraphPinPose::FAttributeInfo>> PinAttributes;` — Map to cached attribute array on the node
- L47 _private member_ `FDelegateHandle OnBlueprintCompiledHandle;` — Handle to compilation delegate
- L50 _private member_ `float PanelZoom;` — Zoom level of the current panel

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationBlueprintEditor.h` (Private)


#### struct `FAnimationBlueprintEditorModes`  
`struct FAnimationBlueprintEditorModes`  
_L50-75_
- L53 _public member_ `static const FName AnimationBlueprintEditorMode;` — Mode constants
- L54 _public member_ `static const FName AnimationBlueprintInterfaceEditorMode;`
- L55 _public member_ `static const FName AnimationBlueprintTemplateEditorMode;`
- L57 _public function_ `static FText GetLocalizedMode(const FName InMode)`
- L74 _private function_ `FAnimationBlueprintEditorModes()`

#### class `FAnimationBlueprintEditor`  
`class FAnimationBlueprintEditor : public IAnimationBlueprintEditor`  
_L95-435_
- inherits: `IAnimationBlueprintEditor`
- desc: Animation Blueprint asset editor (extends Blueprint editor)
- L111 _public prototype_ `void InitAnimationBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UAnimBlueprint* InAnimBlueprint);` — Edits the specified character asset(s) @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InitSkeleton			The skeleton to edit.  If specified, Blueprint must be NULL. @param	InitAnimBlueprint		The blueprint object to start editing.  If specified, Skeleton and AnimationAsset must be NULL. @param	InitAnimationAsset		The animation asset to edit.  If specified, Blueprint must be NULL. @param	InitMesh				The mesh asset to edit.  If specified, Blueprint must be NULL.
- L114 _public prototype_ `FAnimationBlueprintEditor();`
- L116 _public prototype_ `virtual ~FAnimationBlueprintEditor();`
- L119 _public prototype_ `void SetDetailObjects(const TArray<UObject*>& InObjects);` — Update the inspector that displays information about the current selection
- L120 _public prototype_ `void SetDetailObject(UObject* Obj);`
- L123 _public function_ `virtual const FEdGraphPinType& GetLastGraphPinTypeUsed() const override` — IAnimationBlueprintEditor interface
- L124 _public function_ `virtual void SetLastGraphPinTypeUsed(const FEdGraphPinType& InType) override`
- L125 _public prototype_ `virtual IAnimationSequenceBrowser* GetAssetBrowser() const override;`
- L126 _public prototype_ `virtual UAnimInstance* GetPreviewInstance() const override;`
- L129 _public function_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const` — IHasPersonaToolkit interface
- L132 _public prototype_ `virtual void OnActiveTabChanged(TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated) override;` — FBlueprintEditor interface
- L133 _public prototype_ `virtual void OnSelectedNodesChangedImpl(const TSet<class UObject*>& NewSelection) override;`
- L134 _public prototype_ `virtual void HandleSetObjectBeingDebugged(UObject* InObject) override;`
- L137 _public prototype_ `UAnimBlueprint* GetAnimBlueprint() const;` — Gets the Anim Blueprint being edited/viewed by this Persona instance
- L140 _public prototype_ `void SetPreviewMesh(USkeletalMesh* NewPreviewMesh);` — Sets the current preview mesh
- L143 _public prototype_ `void ClearSelectedActor();` — Clears the selected actor
- L146 _public prototype_ `void ClearSelectedAnimGraphNodes();` — Clears the selected anim graph nodes
- L149 _public prototype_ `void DeselectAll();` — Clears the selection (both sockets and bones). Also broadcasts this
- L152 _public prototype_ `TSharedRef<class IPersonaPreviewScene> GetPreviewScene() const;` — Returns the editors preview scene
- L155 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);` — Handle general object selection
- L156 _public prototype_ `void HandleObjectSelected(UObject* InObject);`
- L157 _public prototype_ `void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);`
- L160 _public prototype_ `UObject* HandleGetObject();` — Get the object to be displayed in the asset properties
- L163 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L167 _public prototype_ `void HandleOpenNewAsset(UObject* InNewAsset);` — Handle opening a new asset from the asset browser
- L171 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L172 _public prototype_ `virtual FName GetToolkitContextFName() const override;`
- L173 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L174 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L175 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L176 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L177 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L181 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L187 _public prototype_ `virtual UBlueprint* GetBlueprintObj() const override;` — Returns a pointer to the Blueprint object we are currently editing, as long as we are editing exactly one
- L190 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L191 _public prototype_ `virtual TStatId GetStatId() const override;`
- L195 _public prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename) override;`
- L198 _public function_ `TSharedRef<SWidget> GetPreviewEditor()`
- L200 _public prototype_ `void RefreshPreviewInstanceTrackCurves();` — Refresh Preview Instance Track Curves
- L202 _public prototype_ `void RecompileAnimBlueprintIfDirty();`
- L205 _public function_ `TSharedPtr<class ISkeletonTree> GetSkeletonTree() const` — Get the skeleton tree this Persona editor is hosting
- L213 _protected prototype_ `virtual void CreateDefaultCommands() override;` — virtual void CreateDefaultToolbar() override;
- L214 _protected prototype_ `virtual void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList);`
- L215 _protected prototype_ `virtual void OnGraphEditorFocused(const TSharedRef<class SGraphEditor>& InGraphEditor) override;`
- L216 _protected prototype_ `virtual void OnGraphEditorBackgrounded(const TSharedRef<SGraphEditor>& InGraphEditor) override;`
- L217 _protected function_ `virtual bool IsInAScriptingMode() const override`
- L218 _protected prototype_ `virtual void GetCustomDebugObjects(TArray<FCustomDebugObject>& DebugList) const override;`
- L219 _protected prototype_ `virtual FString GetCustomDebugObjectLabel(UObject* ObjectBeingDebugged) const override;`
- L220 _protected prototype_ `virtual void CreateDefaultTabContents(const TArray<UBlueprint*>& InBlueprints) override;`
- L221 _protected prototype_ `virtual FGraphAppearanceInfo GetGraphAppearance(class UEdGraph* InGraph) const override;`
- L222 _protected prototype_ `virtual bool IsEditable(UEdGraph* InGraph) const override;`
- L223 _protected prototype_ `virtual FText GetGraphDecorationString(UEdGraph* InGraph) const override;`
- L224 _protected prototype_ `virtual void OnBlueprintChangedImpl(UBlueprint* InBlueprint, bool bIsJustBeingCompiled = false) override;`
- L225 _protected prototype_ `virtual void CreateEditorModeManager() override;`
- L226 _protected prototype_ `virtual bool IsSectionVisible(NodeSectionID::Type InSectionID) const override;`
- L227 _protected prototype_ `virtual bool AreEventGraphsAllowed() const override;`
- L228 _protected prototype_ `virtual bool AreMacrosAllowed() const override;`
- L229 _protected prototype_ `virtual bool AreDelegatesAllowed() const override;`
- L230 _protected prototype_ `virtual void OnCreateComment() override;`
- L234 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L235 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L239 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L243 _protected prototype_ `bool CanTogglePoseWatch();` — Toggle pose watch on selected nodes
- L244 _protected prototype_ `void OnTogglePoseWatch();`
- L247 _protected prototype_ `bool CanHideUnboundPropertyPins();` — Hide unbound pins on selected nodes
- L248 _protected prototype_ `void OnHideUnboundPropertyPins();`
- L250 _protected prototype_ `void BindCommands();`
- L255 _protected prototype_ `void ClearupPreviewMeshAnimNotifyStates();` — Clear up Preview Mesh's AnimNotifyStates. Called when undo or redo
- L259 _public member_ `TWeakPtr<class IPersonaViewport> Viewport;` — Viewport widget
- L262 _public member_ `class IDetailLayoutBuilder* PersonaMeshDetailLayout;` — holding this pointer to refresh persona mesh detials tab when LOD is changed
- L267 _public typedef_ `typedef FSimpleMulticastDelegate::FDelegate FOnPostUndo;` — Called after an undo is performed to give child widgets a chance to refresh
- L270 _public function_ `void RegisterOnPostUndo(const FOnPostUndo& Delegate)` — Registers a delegate to be called after an Undo operation
- L276 _public function_ `void UnregisterOnPostUndo(SWidget* Widget)` — Unregisters a delegate to be called after an Undo operation
- L282 _public member_ `FSimpleMulticastDelegate OnPostUndo;` — Delegate called after an undo operation for child widgets to refresh
- L286 _protected prototype_ `void UndoAction();` — Undo Action
- L288 _protected prototype_ `void RedoAction();` — Redo Action
- L293 _private prototype_ `void ExtendMenu();` — Extend menu
- L296 _private prototype_ `void RegisterMenus();` — Register menus
- L299 _private prototype_ `void ExtendToolbar();` — Extend toolbar
- L302 _private prototype_ `static TSharedPtr<FAnimationBlueprintEditor> GetAnimationBlueprintEditor(const FToolMenuContext& InMenuContext);` — Get the anim BP editor referenced by the supplied tool menu context
- L305 _private prototype_ `void OnBlueprintPreCompile(UBlueprint* BlueprintToCompile);` — Called immediately prior to a blueprint compilation
- L308 _private prototype_ `void OnBlueprintPostCompile(UBlueprint* InBlueprint);` — Called immediately after to a blueprint compilation
- L311 _private prototype_ `void OnPostCompile();` — Called post compile to copy node data
- L314 _private prototype_ `void NotifyAllNodesOnSelection(const bool bInIsSelected);` — Call OnNodeSelected for each selected node
- L317 _private prototype_ `void NotifyAllNodesOnPoseWatchChanged(const bool IsPoseWatchActive);` — Call OnPoseWatchChanged for each pose watched node
- L320 _private prototype_ `void ReleaseAllManagedNodes();` — Called to notify all Nodes before any change to node selection or pose watch status
- L323 _private prototype_ `void AcquireAllManagedNodes();` — Called to notify all Nodes after any change to node selection or pose watch status
- L326 _private prototype_ `struct FAnimNode_Base* FindAnimNode(class UAnimGraphNode_Base* AnimGraphNode) const;` — Helper function used to keep skeletal controls in preview & instance in sync
- L329 _private prototype_ `void HandlePinDefaultValueChanged(UEdGraphPin* InPinThatChanged);` — Handle a pin's default value changing be propagating it to the preview
- L332 _private prototype_ `void HandlePreviewMeshChanged(USkeletalMesh* OldPreviewMesh, USkeletalMesh* NewPreviewMesh);` — Handle the preview mesh changing (so we can re-hook debug anim links etc.)
- L335 _private prototype_ `void HandleViewportCreated(const TSharedRef<IPersonaViewport>& InPersonaViewport);` — Handle the viewport being created
- L338 _private prototype_ `void HandlePreviewAnimBlueprintCompiled(UBlueprint* InBlueprint);` — Handle the preview anim blueprint being compiled
- L341 _private prototype_ `void HandlePoseWatchSelectedNodes();` — Enable/disable pose watch on selected nodes
- L344 _private prototype_ `void RemoveAllSelectionPoseWatches();` — Removes all pose watches created by selection from the current view
- L349 _private prototype_ `virtual void LoadEditorSettings();` — Load editor settings from disk (docking state, window pos/size, option state, etc).
- L354 _private prototype_ `virtual void SaveEditorSettings();` — Saves editor settings to disk (docking state, window pos/size, option state, etc).
- L356 _private prototype_ `void HandleAnimationSequenceBrowserCreated(const TSharedRef<IAnimationSequenceBrowser>& InSequenceBrowser);`
- L359 _private prototype_ `void HandleScriptException(const UObject* InObject, const FFrame& InFrame, const FBlueprintExceptionInfo& InInfo);` — Hook the BP exception handler to deal with infinite loops (more) gracefully
- L361 _private prototype_ `void HandleUpdateSettings(const UAnimationBlueprintEditorSettings* AnimationBlueprintEditorSettings, EPropertyChangeType::Type ChangeType);`
- L364 _private prototype_ `FColor ChoosePoseWatchColor() const;` — Chooses a suitable pose watch color automatically - i.e. one that isn't already in use (if possible)
- L367 _private prototype_ `void OnAddPosePin();` — Pose pin UI handlers
- L368 _private prototype_ `bool CanAddPosePin() const;`
- L369 _private prototype_ `void OnRemovePosePin();`
- L370 _private prototype_ `bool CanRemovePosePin() const;`
- L373 _private prototype_ `void OnConvertToSequenceEvaluator();` — Node conversion functions
- L374 _private prototype_ `void OnConvertToSequencePlayer();`
- L375 _private prototype_ `void OnConvertToBlendSpaceEvaluator();`
- L376 _private prototype_ `void OnConvertToBlendSpacePlayer();`
- L377 _private prototype_ `void OnConvertToBlendSpaceGraph();`
- L378 _private prototype_ `void OnConvertToPoseBlender();`
- L379 _private prototype_ `void OnConvertToPoseByName();`
- L380 _private prototype_ `void OnConvertToAimOffsetLookAt();`
- L381 _private prototype_ `void OnConvertToAimOffsetSimple();`
- L382 _private prototype_ `void OnConvertToAimOffsetGraph();`
- L385 _private prototype_ `void OnOpenRelatedAsset();` — Opens the associated asset of the selected nodes
- L388 _private prototype_ `void OnCreateSelfTransition();` — State machine functions
- L389 _private prototype_ `FAnimNode_StateMachine* GetSelectedStateInstance(int32& OutSelectedState) const;`
- L390 _private prototype_ `bool CanSetActiveState() const;`
- L391 _private prototype_ `void OnSetActiveState();`
- L392 _private prototype_ `void OnReverseTransition();`
- L395 _private member_ `TSharedPtr<FExtender> MenuExtender;` — The extender to pass to the level editor to extend it's window menu
- L398 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender
- L401 _private member_ `TSharedPtr<class SWidget> PreviewEditor;` — Preview instance inspector widget
- L404 _private member_ `TSharedPtr<class IPersonaToolkit> PersonaToolkit;` — Persona toolkit
- L407 _private member_ `TSharedPtr<class ISkeletonTree> SkeletonTree;` — Skeleton tree
- L410 _private member_ `TArray< TWeakObjectPtr< class UAnimGraphNode_Base > > SelectedAnimGraphNodes;` — selected anim graph node
- L413 _private member_ `TWeakPtr<class IAnimationSequenceBrowser> SequenceBrowser;` — Sequence Browser
- L416 _private member_ `FDelegateHandle OnPinDefaultValueChangedHandle;` — Delegate handle registered for when pin default values change
- L419 _private member_ `FEdGraphPinType LastGraphPinType;` — The last pin type we added to a graph's inputs
- L422 _private member_ `TObjectPtr<UAnimationBlueprintEditorOptions> EditorOptions;` — Configuration class used to store editor settings across sessions.
- L425 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> DebuggedMeshComponent;` — Cached mesh component held during compilation, used to reconnect debugger
- L428 _private member_ `bool bPreviousPoseWatchSelectedNodes = false;` — Used to track wither the editor option has changed
- L431 _private member_ `FDelegateHandle AnimationBlueprintEditorSettingsChangedHandle;` — Delegate handle registered for when settings change
- L434 _private member_ `FDelegateHandle ScriptExceptionHandle;` — Delegate handle registered to handle infinite loop exceptions

#### Free symbols / members of external scopes

- L77 _namespace_ `namespace AnimationBlueprintEditorTabs`
- L79 _externvar_ `extern const FName DetailsTab;` (scope `AnimationBlueprintEditorTabs`)
- L80 _externvar_ `extern const FName SkeletonTreeTab;` (scope `AnimationBlueprintEditorTabs`)
- L81 _externvar_ `extern const FName ViewportTab;` (scope `AnimationBlueprintEditorTabs`)
- L82 _externvar_ `extern const FName AdvancedPreviewTab;` (scope `AnimationBlueprintEditorTabs`)
- L83 _externvar_ `extern const FName AssetBrowserTab;` (scope `AnimationBlueprintEditorTabs`)
- L84 _externvar_ `extern const FName AnimBlueprintPreviewEditorTab;` (scope `AnimationBlueprintEditorTabs`)
- L85 _externvar_ `extern const FName AssetOverridesTab;` (scope `AnimationBlueprintEditorTabs`)
- L86 _externvar_ `extern const FName SlotNamesTab;` (scope `AnimationBlueprintEditorTabs`)
- L87 _externvar_ `extern const FName CurveNamesTab;` (scope `AnimationBlueprintEditorTabs`)
- L88 _externvar_ `extern const FName PoseWatchTab;` (scope `AnimationBlueprintEditorTabs`)
- L89 _externvar_ `extern const FName FindReplaceTab;` (scope `AnimationBlueprintEditorTabs`)

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationBlueprintEditorMode.h` (Private)


#### class `FAnimationBlueprintEditorMode`  
`class FAnimationBlueprintEditorMode : public FBlueprintEditorApplicationMode`  
_L16-35_
- inherits: `FBlueprintEditorApplicationMode`
- L20 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in persona mode (@TODO: Multiple lists!)
- L23 _public prototype_ `FAnimationBlueprintEditorMode(const TSharedRef<FAnimationBlueprintEditor>& InAnimationBlueprintEditor);`
- L26 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L27 _public prototype_ `virtual void PreDeactivateMode() override;`
- L28 _public prototype_ `virtual void PostActivateMode() override;`
- L32 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;`
- L34 _private member_ `TWeakObjectPtr<class UAnimBlueprint> AnimBlueprintPtr;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationBlueprintEditorModule.h` (Private)


#### class `FAnimationBlueprintEditorModule`  
`class FAnimationBlueprintEditorModule : public IAnimationBlueprintEditorModule`  
_L18-59_
- inherits: `IAnimationBlueprintEditorModule`
- desc: Animation Blueprint Editor module allows editing of Animation Blueprints
- L24 _public prototype_ `virtual void StartupModule();` — Called right after the module's DLL has been loaded and the module object has been created
- L29 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L32 _public prototype_ `virtual TSharedRef<class IAnimationBlueprintEditor> CreateAnimationBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UAnimBlueprint* Blueprint) override;` — IAnimationBlueprintEditorModule interface
- L33 _public function_ `virtual TArray<FAnimationBlueprintEditorToolbarExtender>& GetAllAnimationBlueprintEditorToolbarExtenders()`
- L34 _public prototype_ `virtual void GetTypeActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L35 _public prototype_ `virtual void GetInstanceActions(const UAnimBlueprint* InAnimBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L38 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend this editor's menus and toolbars
- L39 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L41 _public function_ `virtual FOnGetCustomDebugObjects& OnGetCustomDebugObjects() override`
- L45 _private prototype_ `void OnNewBlueprintCreated(class UBlueprint* InBlueprint);` — When a new AnimBlueprint is created, this will handle post creation work such as adding non-event default nodes
- L46 _private prototype_ `void HandleMessageTokenClicked(const TSharedRef<IMessageToken>& InMessageToken);`
- L49 _private member_ `TSharedPtr<class FExtensibilityManager> MenuExtensibilityManager;`
- L50 _private member_ `TSharedPtr<class FExtensibilityManager> ToolBarExtensibilityManager;`
- L52 _private member_ `TArray<FAnimationBlueprintEditorToolbarExtender> AnimationBlueprintEditorToolbarExtenders;`
- L54 _private member_ `TSharedPtr<FAnimationGraphNodeFactory> AnimGraphNodeFactory;`
- L55 _private member_ `TSharedPtr<FAnimationGraphPinFactory> AnimGraphPinFactory;`
- L56 _private member_ `TSharedPtr<FAnimationGraphPinConnectionFactory> AnimGraphPinConnectionFactory;`
- L58 _private member_ `FOnGetCustomDebugObjects OnGetCustomDebugObjectsDelegate;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationBlueprintInterfaceEditorMode.h` (Private)


#### class `FAnimationBlueprintInterfaceEditorMode`  
`class FAnimationBlueprintInterfaceEditorMode : public FBlueprintInterfaceApplicationMode`  
_L13-28_
- inherits: `FBlueprintInterfaceApplicationMode`
- L17 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in persona mode (@TODO: Multiple lists!)
- L20 _public prototype_ `FAnimationBlueprintInterfaceEditorMode(const TSharedRef<FAnimationBlueprintEditor>& InAnimationBlueprintEditor);`
- L23 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L27 _private member_ `TWeakObjectPtr<class UAnimBlueprint> AnimBlueprintPtr;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationBlueprintToolMenuContext.h` (Private)


#### class `UAnimationBlueprintToolMenuContext`  
`class UAnimationBlueprintToolMenuContext : public UObject`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<FAnimationBlueprintEditor> AnimationBlueprintEditor;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationGraphFactory.h` (Private)


#### struct `FAnimationGraphNodeFactory`  
`struct FAnimationGraphNodeFactory : public FGraphPanelNodeFactory`  
_L11-14_
- inherits: `FGraphPanelNodeFactory`
- L13 _public prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override;`

#### struct `FAnimationGraphPinFactory`  
`struct FAnimationGraphPinFactory : public FGraphPanelPinFactory`  
_L16-20_
- inherits: `FGraphPanelPinFactory`
- L19 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;`

#### struct `FAnimationGraphPinConnectionFactory`  
`struct FAnimationGraphPinConnectionFactory : public FGraphPanelPinConnectionFactory`  
_L22-26_
- inherits: `FGraphPanelPinConnectionFactory`
- L25 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionPolicy(const class UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const class FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONBLUEPRINTEDITOR_API`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SAnimNodeReference.h` (Private)


#### class `SAnimNodeReference`  
`class SAnimNodeReference : public SGraphNodeK2Var`  
_L17-31_
- inherits: `SGraphNodeK2Var`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAnimNodeReference)`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, UK2Node_AnimNodeReference* InNode);`
- L27 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface
- L30 _public prototype_ `virtual TSharedRef<SWidget> UpdateTitleWidget(FText InTitleText, TSharedPtr<SWidget> InTitleWidget, EHorizontalAlignment& InOutTitleHAlign, FMargin& InOutTitleMargin) const override;` — SGraphNodeK2Var interface

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeAnimationResult.h` (Private)


#### class `SGraphNodeAnimationResult`  
`class SGraphNodeAnimationResult : public SAnimationGraphNode`  
_L11-23_
- inherits: `SAnimationGraphNode`
- L14 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAnimationResult)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UAnimGraphNode_Base* InNode);`
- L21 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;` — SGraphNode interface

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeBlendSpaceGraph.h` (Private)


#### class `SGraphNodeBlendSpaceGraph`  
`class SGraphNodeBlendSpaceGraph : public SGraphNodeK2Composite`  
_L17-38_
- inherits: `SGraphNodeK2Composite`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeBlendSpaceGraph)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UAnimGraphNode_BlendSpaceGraphBase* InNode);`
- L27 _protected prototype_ `virtual UEdGraph* GetInnerGraph() const override;` — SGraphNodeK2Composite interface
- L28 _protected prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L29 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeBody() override;`
- L32 _protected prototype_ `TSharedPtr<SToolTip> GetComplexTooltip() override;` — SGraphNode interface
- L35 _private member_ `TSharedPtr<SWidget> FastPathWidget;`
- L37 _private member_ `TSharedPtr<SPoseWatchOverlay> PoseWatchWidget;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeBlendSpacePlayer.h` (Private)


#### class `SGraphNodeBlendSpacePlayer`  
`class SGraphNodeBlendSpacePlayer : public SAnimationGraphNode`  
_L14-35_
- inherits: `SAnimationGraphNode`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeBlendSpacePlayer)`
- L18 _public prototype_ `SLATE_END_ARGS()`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);`
- L26 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;` — SGraphNode interface
- L31 _protected prototype_ `void UpdateGraphSyncLabel();` — Invalidates the node's label if we are syncing based on graph context
- L34 _protected member_ `FName CachedSyncGroupName;` — Cached name to display when sync groups are dynamic

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeLayeredBoneBlend.h` (Private)


#### class `SGraphNodeLayeredBoneBlend`  
`class SGraphNodeLayeredBoneBlend : public SAnimationGraphNode`  
_L13-32_
- inherits: `SAnimationGraphNode`
- L16 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeLayeredBoneBlend)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimGraphNode_LayeredBoneBlend* InNode);`
- L23 _protected prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;` — SGraphNode interface
- L24 _protected prototype_ `virtual FReply OnAddPin() override;`
- L30 _private member_ `UAnimGraphNode_LayeredBoneBlend* Node;` — The node that we represent

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeLinkedLayer.h` (Private)


#### class `SGraphNodeLinkedLayer`  
`class SGraphNodeLinkedLayer : public SAnimationGraphNode`  
_L11-23_
- inherits: `SAnimationGraphNode`
- L14 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeLinkedLayer)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);`
- L20 _protected prototype_ `void UpdateNodeLabel();`
- L22 _protected member_ `FName CachedTargetName;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeSequencePlayer.h` (Private)


#### class `SGraphNodeSequencePlayer`  
`class SGraphNodeSequencePlayer : public SAnimationGraphNode`  
_L19-55_
- inherits: `SAnimationGraphNode`
- L22 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeSequencePlayer)`
- L23 _public prototype_ `SLATE_END_ARGS()`
- L28 _public prototype_ `void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);`
- L31 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface
- L35 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L36 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L41 _protected prototype_ `struct FAnimNode_SequencePlayer* GetSequencePlayer() const;` — Get the sequence player associated with this graph node
- L42 _protected prototype_ `EVisibility GetSliderVisibility() const;`
- L43 _protected prototype_ `float GetSequencePositionRatio() const;`
- L44 _protected prototype_ `void SetSequencePositionRatio(float NewRatio);`
- L46 _protected prototype_ `FText GetPositionTooltip() const;`
- L48 _protected prototype_ `bool GetSequencePositionInfo(float& Out_Position, float& Out_Length, int32& FrameCount) const;`
- L51 _protected prototype_ `void UpdateGraphSyncLabel();` — Invalidates the node's label if we are syncing based on graph context
- L54 _protected member_ `FName CachedSyncGroupName;` — Cached name to display when sync groups are dynamic

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SGraphNodeStateMachineInstance.h` (Private)


#### class `SGraphNodeStateMachineInstance`  
`class SGraphNodeStateMachineInstance : public SGraphNodeK2Composite`  
_L15-32_
- inherits: `SGraphNodeK2Composite`
- L18 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeStateMachineInstance)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UAnimGraphNode_StateMachineBase* InNode);`
- L25 _protected prototype_ `virtual UEdGraph* GetInnerGraph() const override;` — SGraphNodeK2Composite interface
- L26 _protected prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L27 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeBody() override;`
- L31 _private member_ `TSharedPtr<SPoseWatchOverlay> PoseWatchWidget;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationNodes/SPoseWatchOverlay.h` (Private)


#### class `SPoseWatchOverlay`  
`class SPoseWatchOverlay : public SCompoundWidget`  
_L17-39_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SPoseWatchOverlay)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode* InNode);`
- L24 _public prototype_ `FVector2D GetOverlayOffset() const;`
- L25 _public prototype_ `bool IsPoseWatchValid() const;`
- L28 _private prototype_ `void HandlePoseWatchesChanged(UAnimBlueprint* InAnimBlueprint, UEdGraphNode* InNode);`
- L30 _private prototype_ `FSlateColor GetPoseViewColor() const;`
- L31 _private prototype_ `const FSlateBrush* GetPoseViewIcon() const;`
- L32 _private prototype_ `FReply TogglePoseWatchVisibility();`
- L34 _private member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;`
- L35 _private member_ `TWeakObjectPtr<class UPoseWatch> PoseWatch;`
- L37 _private member_ `static const FSlateBrush* IconVisible;`
- L38 _private member_ `static const FSlateBrush* IconNotVisible;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationPins/SGraphPinPose.h` (Private)


#### class `SGraphPinPose`  
`class SGraphPinPose : public SGraphPin`  
_L19-64_
- inherits: `SGraphPin`
- L22 _public function_ `SLATE_BEGIN_ARGS(SGraphPinPose)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L44 _public prototype_ `TArrayView<const FAttributeInfo> GetAttributeInfo() const;` — Get the attribute info used to draw connections. This varies based on LOD level.
- L47 _public prototype_ `float GetZoomAmount() const;` — Exposes the parent panel's zoom scalar for use when drawing links
- L50 _private prototype_ `void ReconfigureWidgetForAttributes();`
- L53 _private prototype_ `FText GetAttributeTooltipText() const;` — Get tooltip text with attributes included
- L57 _protected prototype_ `virtual const FSlateBrush* GetPinIcon() const override;`
- L60 _protected member_ `mutable const FSlateBrush* CachedImg_Pin_ConnectedHovered;`
- L61 _protected member_ `mutable const FSlateBrush* CachedImg_Pin_DisconnectedHovered;`
- L63 _protected member_ `TArray<FAttributeInfo> AttributeInfos;`

#### struct `SGraphPinPose::FAttributeInfo`  
`struct FAttributeInfo`  
_L28-41_
- desc: Struct used by connection drawing to draw attributes
- L30 _public function_ `FAttributeInfo(FName InAttribute, const FLinearColor& InColor, EAnimGraphAttributeBlend InBlend, int32 InSortOrder) : Attribute(InAttribute) , Color(InColor) , Blend(InBlend) , SortOrder(InSortOrder)`
- L37 _public member_ `FName Attribute;`
- L38 _public member_ `FLinearColor Color;`
- L39 _public member_ `EAnimGraphAttributeBlend Blend;`
- L40 _public member_ `int32 SortOrder;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationStateNodes/SGraphNodeAnimState.h` (Private)


#### class `SGraphNodeAnimState`  
`class SGraphNodeAnimState : public SGraphNode`  
_L24-58_
- inherits: `SGraphNode`
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAnimState)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimStateNodeBase* InNode);`
- L33 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface
- L37 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L38 _public prototype_ `virtual void CreatePinWidgets() override;`
- L39 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L40 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L41 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L45 _public prototype_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L46 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L49 _public prototype_ `void GetStateInfoPopup(TArray<FGraphInformationPopupInfo>& Popups) const;`
- L51 _protected prototype_ `FSlateColor GetBorderBackgroundColor() const;`
- L52 _protected prototype_ `virtual FSlateColor GetBorderBackgroundColor_Internal(FLinearColor InactiveStateColor, FLinearColor ActiveStateColorDim, FLinearColor ActiveStateColorBright) const;`
- L53 _protected prototype_ `virtual FText GetPreviewCornerText() const;`
- L54 _protected prototype_ `virtual const FSlateBrush* GetNameIcon() const;`
- L55 _protected prototype_ `virtual FSlateColor GetIconColor() const;`
- L57 _protected member_ `TSharedPtr<SOverlay> PinOverlay;`

#### class `SGraphNodeAnimConduit`  
`class SGraphNodeAnimConduit : public SGraphNodeAnimState`  
_L61-77_
- inherits: `SGraphNodeAnimState`
- L64 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAnimConduit)`
- L65 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimStateConduitNode* InNode);`
- L70 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface
- L73 _protected prototype_ `virtual FSlateColor GetBorderBackgroundColor_Internal(FLinearColor InactiveStateColor, FLinearColor ActiveStateColorDim, FLinearColor ActiveStateColorBright) const override;`
- L74 _protected prototype_ `virtual FText GetPreviewCornerText() const override;`
- L75 _protected prototype_ `virtual const FSlateBrush* GetNameIcon() const override;`
- L76 _protected prototype_ `virtual FSlateColor GetIconColor() const override;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationStateNodes/SGraphNodeAnimStateAlias.h` (Private)


#### class `SGraphNodeAnimStateAlias`  
`class SGraphNodeAnimStateAlias : public SGraphNodeAnimState`  
_L20-40_
- inherits: `SGraphNodeAnimState`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAnimStateAlias)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimStateAliasNode* InNode);`
- L29 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface
- L30 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L33 _public prototype_ `static void GetStateInfoPopup(UEdGraphNode* GraphNode, TArray<FGraphInformationPopupInfo>& Popups);`
- L36 _protected prototype_ `virtual FSlateColor GetBorderBackgroundColor_Internal(FLinearColor InactiveStateColor, FLinearColor ActiveStateColorDim, FLinearColor ActiveStateColorBright) const;`
- L37 _protected prototype_ `virtual FText GetPreviewCornerText() const override;`
- L38 _protected prototype_ `virtual const FSlateBrush* GetNameIcon() const override;`
- L39 _protected prototype_ `virtual FSlateColor GetIconColor() const override;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationStateNodes/SGraphNodeAnimStateEntry.h` (Private)


#### class `SGraphNodeAnimStateEntry`  
`class SGraphNodeAnimStateEntry : public SGraphNode`  
_L17-41_
- inherits: `SGraphNode`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAnimStateEntry)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimStateEntryNode* InNode);`
- L26 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface
- L30 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L31 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L32 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L33 _public prototype_ `virtual void CreatePinWidgets() override;`
- L38 _protected prototype_ `FSlateColor GetBorderBackgroundColor() const;`
- L40 _protected prototype_ `FText GetPreviewCornerText() const;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationStateNodes/SGraphNodeAnimTransition.h` (Private)


#### class `SGraphNodeAnimTransition`  
`class SGraphNodeAnimTransition : public SGraphNode`  
_L27-75_
- inherits: `SGraphNode`
- L30 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAnimTransition)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimStateTransitionNode* InNode);`
- L36 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface
- L37 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L38 _public prototype_ `virtual bool RequiresSecondPassLayout() const override;`
- L39 _public prototype_ `virtual void PerformSecondPassLayout(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup) const override;`
- L43 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L44 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L45 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L49 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L50 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L55 _public prototype_ `void PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const;` — Calculate position for multiple nodes to be placed between a start and end point, by providing this nodes index and max expected nodes
- L57 _public prototype_ `static FSlateColor StaticGetTransitionColor(UAnimStateTransitionNode* TransNode, bool bIsHovered);`
- L59 _public prototype_ `static bool IsTransitionActive(int32 TransitionIndex, class UAnimBlueprintGeneratedClass& AnimClass, class UAnimationStateMachineGraph& StateMachineGraph, class UAnimInstance& AnimInstance);`
- L61 _private member_ `TSharedPtr<STextEntryPopup> TextEntryWidget;`
- L64 _private member_ `mutable TWeakPtr<SNode> PrevStateNodeWidgetPtr;` — Cache of the widget representing the previous state node
- L67 _private prototype_ `FText GetPreviewCornerText(bool reverse) const;`
- L68 _private prototype_ `FSlateColor GetTransitionColor() const;`
- L69 _private prototype_ `const FSlateBrush* GetTransitionIconImage() const;`
- L71 _private prototype_ `TSharedRef<SWidget> GenerateInlineDisplayOrEditingWidget(bool bShowGraphPreview);`
- L72 _private prototype_ `TSharedRef<SWidget> GenerateRichTooltip();`
- L74 _private prototype_ `FString GetCurrentDuration() const;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationStateNodes/SStateMachineInputPin.h` (Private)


#### class `SStateMachineInputPin`  
`class SStateMachineInputPin : public SGraphPin`  
_L7-18_
- inherits: `SGraphPin`
- L10 _public function_ `SLATE_BEGIN_ARGS(SStateMachineInputPin)`
- L11 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L16 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

### `Source/Editor/AnimationBlueprintEditor/Private/AnimationStateNodes/SStateMachineOutputPin.h` (Private)


#### class `SStateMachineOutputPin`  
`class SStateMachineOutputPin : public SGraphPin`  
_L7-20_
- inherits: `SGraphPin`
- L10 _public function_ `SLATE_BEGIN_ARGS(SStateMachineOutputPin)`
- L11 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L16 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L19 _protected prototype_ `const FSlateBrush* GetPinBorder() const;`

### `Source/Editor/AnimationBlueprintEditor/Private/BlendSpaceDocumentTabFactory.h` (Private)


#### struct `FBlendSpaceDocumentTabFactory`  
`struct FBlendSpaceDocumentTabFactory : public FDocumentTabFactory`  
_L15-32_
- inherits: `FDocumentTabFactory`
- L18 _public prototype_ `FBlendSpaceDocumentTabFactory(TSharedPtr<FAnimationBlueprintEditor> InBlueprintEditorPtr);`
- L22 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L23 _protected prototype_ `virtual const FSlateBrush* GetTabIcon(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected prototype_ `virtual bool IsPayloadSupported(TSharedRef<FTabPayload> Payload) const override;`
- L25 _protected prototype_ `virtual bool IsPayloadValid(TSharedRef<FTabPayload> Payload) const override;`
- L26 _protected prototype_ `virtual TAttribute<FText> ConstructTabName(const FWorkflowTabSpawnInfo& Info) const override;`
- L27 _protected prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L28 _protected prototype_ `virtual void OnTabForegrounded(TSharedPtr<SDockTab> Tab) const override;`
- L31 _protected member_ `TWeakPtr<FAnimationBlueprintEditor> BlueprintEditorPtr;`

### `Source/Editor/AnimationBlueprintEditor/Private/StateMachineConnectionDrawingPolicy.h` (Private)


#### class `FStateMachineConnectionDrawingPolicy`  
`class FStateMachineConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L25-62_
- inherits: `FConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph with a state machine schema
- L28 _protected member_ `UEdGraph* GraphObj;`
- L30 _protected member_ `TMap<UEdGraphNode*, int32> NodeWidgetMap;`
- L35 _public prototype_ `FStateMachineConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L38 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface
- L39 _public prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& PinGeometries, FArrangedChildren& ArrangedNodes) override;`
- L40 _public prototype_ `virtual void DetermineLinkGeometry( FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget, UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry ) override;`
- L48 _public prototype_ `virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;`
- L49 _public prototype_ `virtual void DrawSplineWithArrow(const FVector2f& StartPoint, const FVector2f& EndPoint, const FConnectionParams& Params) override;`
- L50 _public prototype_ `virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2f& StartPoint, const FVector2f& EndPoint, UEdGraphPin* Pin) override;`
- L51 _public prototype_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const override;`
- L55 _protected prototype_ `void Internal_DrawLineWithArrow(const FVector2f& StartAnchorPoint, const FVector2f& EndAnchorPoint, const FConnectionParams& Params);`
- L58 _protected prototype_ `void DrawCircle(const FVector2f& Center, float Radius, const FLinearColor& Color, const int NumLineSegments);` — Draw line-based circle (no solid filling)
- L59 _protected member_ `TArray<FVector2f> TempPoints;`
- L61 _protected member_ `static constexpr float RelinkHandleHoverRadius = 10.0f;`

### `Source/Editor/AnimationBlueprintEditor/Private/TabPayload_BlendSpaceGraph.h` (Private)


#### struct `FTabPayload_BlendSpaceGraph`  
`struct FTabPayload_BlendSpaceGraph : public FTabPayload`  
_L10-61_
- inherits: `FTabPayload`
- desc: Tab payload used to generate blendspace documents
- L14 _public function_ `static TSharedRef<FTabPayload_BlendSpaceGraph> Make(const UBlendSpaceGraph* DocumentID)` — Create a new payload wrapper for a UObject
- L20 _public function_ `virtual bool IsEqual(const TSharedRef<FTabPayload>& OtherPayload) const override` — Determine if another payload is the same as this one
- L35 _public function_ `virtual bool IsValid() const override`
- L40 _public prototype_ `virtual ~FTabPayload_BlendSpaceGraph() = default;`
- L43 _public function_ `static UBlendSpaceGraph* GetBlendSpaceGraph(TSharedPtr<FTabPayload> Payload)` — Access the internal graph payload
- L52 _private function_ `FTabPayload_BlendSpaceGraph(UBlendSpaceGraph* InDocumentID) : FTabPayload(UBlendSpaceGraph::StaticClass()->GetFName()) , DocumentID(InDocumentID)` — Buried constructor. Use Make instead!
- L60 _private member_ `TWeakObjectPtr<UBlendSpaceGraph> DocumentID;` — The object that is the real payload

### `Source/Editor/AnimationBlueprintEditor/Public/AnimationBlueprintEditorSettings.h` (Public)


#### class `UAnimationBlueprintEditorSettings`  
`class UAnimationBlueprintEditorSettings : public UObject`  
_L19-50_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the Animation Blueprint Editor
- L26 _public member_ `bool bPoseWatchSelectedNodes = false;` — `UPROPERTY(EditAnywhere, config, Category = "Debugging")` — If true, automatically pose watch selected nodes.
- L30 _public member_ `bool bShowGraphCornerText = true;` — `UPROPERTY(EditAnywhere, config, Category = "Graphs")` — Whether to display the corner text in an animation graph. Changing this only affects newly opened graphs.
- L33 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSettingsMulticaster, const UAnimationBlueprintEditorSettings*, EPropertyChangeType::Type);`
- L34 _public member_ `FOnUpdateSettingsMulticaster OnSettingsChange;`
- L36 _public function_ `FDelegateHandle RegisterOnUpdateSettings(const FOnUpdateSettingsMulticaster::FDelegate& Delegate)`
- L41 _public function_ `void UnregisterOnUpdateSettings(FDelegateHandle Object)`
- L48 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSettingsMulticaster, const UAnimationBlueprintEditorSettings*, EPropertyChangeType::Type);`

### `Source/Editor/AnimationBlueprintEditor/Public/AnimationNodes/SAnimationGraphNode.h` (Public)


#### class `SAnimationGraphNode`  
`class SAnimationGraphNode : public SGraphNodeK2Base`  
_L38-100_
- inherits: `SGraphNodeK2Base`
- L41 _public function_ `SLATE_BEGIN_ARGS(SAnimationGraphNode)`
- L42 _public prototype_ `SLATE_END_ARGS()`
- L48 _public member_ `static const int32 TagAndFunctionsSlotReverseIndex = 1;` — Reverse index of the tag/functions slot
- L50 _public prototype_ `void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);`
- L53 _public prototype_ `static void ReconfigurePinWidgetsForPropertyBindings(UAnimGraphNode_Base* InAnimGraphNode, TSharedRef<SGraphNode> InGraphNodeWidget, TFunctionRef<TSharedPtr<SGraphPin>(UEdGraphPin*)> InFindWidgetForPin);` — Tweak any created pin widgets so they respond to bindings
- L56 _public prototype_ `static TSharedRef<SWidget> CreateNodeFunctionsWidget(UAnimGraphNode_Base* InAnimNode, TAttribute<bool> InUseLowDetail);` — Create below-widget controls for editing anim node functions
- L59 _public prototype_ `static TSharedRef<SWidget> CreateNodeTagWidget(UAnimGraphNode_Base* InAnimNode, TAttribute<bool> InUseLowDetail);` — Create below-widget controls for editing anim node tags
- L63 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L67 _protected prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;` — SGraphNode interface
- L68 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> InNodeTitle) override;`
- L69 _protected prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;`
- L70 _protected prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L71 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L72 _protected function_ `virtual bool IsHidingPinWidgets() const override`
- L77 _private prototype_ `void HandleNodeTitleChanged();` — Handle the node informing us that the title has changed
- L80 _private prototype_ `bool UseLowDetailNodeContent() const;` — LOD related functions for content area
- L81 _private prototype_ `FVector2D GetLowDetailDesiredSize() const;`
- L84 _private prototype_ `void HandlePoseWatchesChanged(UAnimBlueprint* InAnimBlueprint, UEdGraphNode* InNode);` — Handler for pose watches changing
- L87 _private member_ `TSharedPtr<SWidget> IndicatorWidget;` — Keep a reference to the indicator widget handing around
- L90 _private member_ `TSharedPtr<SPoseWatchOverlay> PoseViewWidget;` — Keep a reference to the pose view indicator widget handing around
- L93 _private member_ `TSharedPtr<SNodeTitle> NodeTitle;` — Cache the node title so we can invalidate it
- L96 _private member_ `FVector2D LastHighDetailSize;` — Cached size from when we last drew at high detail
- L99 _private member_ `TSharedPtr<SWidget> CachedContentArea;` — Cached content area widget (used to derive LastHighDetailSize)

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API ANIMATIONBLUEPRINTEDITOR_API`

### `Source/Editor/AnimationBlueprintEditor/Public/AnimationNodes/SBlendSpacePreview.h` (Public)


#### class `SBlendSpacePreview`  
`class SBlendSpacePreview : public SCompoundWidget`  
_L17-36_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SBlendSpacePreview)`
- L22 _public prototype_ `SLATE_ARGUMENT(FOnGetBlendSpaceSampleName, OnGetBlendSpaceSampleName) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);`
- L29 _protected prototype_ `EVisibility GetBlendSpaceVisibility() const;`
- L30 _protected prototype_ `bool GetBlendSpaceInfo(TWeakObjectPtr<const UBlendSpace>& OutBlendSpace, FVector& OutPosition, FVector& OutFilteredPosition) const;`
- L32 _protected member_ `TWeakObjectPtr<const UAnimGraphNode_Base> Node;`
- L33 _protected member_ `TWeakObjectPtr<const UBlendSpace> CachedBlendSpace;`
- L34 _protected member_ `FVector CachedPosition;`
- L35 _protected member_ `FVector CachedFilteredPosition;`

### `Source/Editor/AnimationBlueprintEditor/Public/IAnimationBlueprintEditor.h` (Public)


#### class `IAnimationBlueprintEditor`  
`class IAnimationBlueprintEditor : public FBlueprintEditor, public IHasPersonaToolkit`  
_L12-29_
- inherits: `FBlueprintEditor,IHasPersonaToolkit`
- L16 _public prototype_ `virtual const FEdGraphPinType& GetLastGraphPinTypeUsed() const = 0;` — Get the last pin type we used to create a graph pin
- L19 _public prototype_ `virtual void SetLastGraphPinTypeUsed(const FEdGraphPinType& InType) = 0;` — Set the last pin type we used to create a graph pin
- L22 _public prototype_ `virtual IAnimationSequenceBrowser* GetAssetBrowser() const = 0;` — Get the asset browser we host
- L25 _public prototype_ `virtual UAnimInstance* GetPreviewInstance() const = 0;` — Get the preview anim instance we are using, which can be a linked instance depending on preview settings
- L28 _public function_ `static FName GetAnimationBlueprintEditorToolkitName()` — Name of EditorToolkit, used for testing against FAssetEditorToolkit::GetToolkitFName

### `Source/Editor/AnimationBlueprintEditor/Public/IAnimationBlueprintEditorModule.h` (Public)


#### class `IAnimationBlueprintEditorModule`  
`class IAnimationBlueprintEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L17-48_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L33 _public prototype_ `virtual TSharedRef<IAnimationBlueprintEditor> CreateAnimationBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UAnimBlueprint* Blueprint) = 0;` — Creates an instance of an Animation Blueprint editor. Note: This function should not be called directly, use one of the following instead: - FKismetEditorUtilities::BringKismetToFocusAttentionOnObject - GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	AnimBlueprint			The blueprint object to start editing.  If specified, Skeleton and AnimationAsset must be NULL. @return	Interface to the new Animation Blueprint editor
- L37 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FAnimationBlueprintEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<IAnimationBlueprintEditor> );` — Get all toolbar extenders
- L38 _public prototype_ `virtual TArray<FAnimationBlueprintEditorToolbarExtender>& GetAllAnimationBlueprintEditorToolbarExtenders() = 0;`
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetCustomDebugObjects, const IAnimationBlueprintEditor& , TArray<FCustomDebugObject>& );`
- L41 _public prototype_ `virtual FOnGetCustomDebugObjects& OnGetCustomDebugObjects() = 0;`
- L44 _public prototype_ `virtual void GetTypeActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const = 0;` — Get anim blueprint type actions
- L47 _public prototype_ `virtual void GetInstanceActions(const UAnimBlueprint* InAnimBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar) const = 0;` — Get anim blueprint instance actions

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationBlueprintEditor, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationBlueprintEditor, Log, All);`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FAnimationBlueprintEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<IAnimationBlueprintEditor> );` — Get all toolbar extenders
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetCustomDebugObjects, const IAnimationBlueprintEditor& , TArray<FCustomDebugObject>& );`
