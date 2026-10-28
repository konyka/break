# Plugins / RenderGridEditor

- module root: `Plugins/Experimental/RenderGrid/Source/RenderGridEditor`
- headers: 44; symbols: 743
- symbol kinds: class=41, delegate=10, enum=3, enumerator=12, function=80, member=144, namespace=178, prototype=259, struct=12, typedef=4
- PrivateDependencyModuleNames: AppFramework, AssetDefinition, DesktopPlatform, EditorStyle, GraphEditor, InputCore, Kismet, LevelSequence, MovieRenderPipelineCore, MovieScene, Projects, PropertyEditor, RenderGrid, RenderGridDeveloper, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RemoteControl

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/AssetDefinition/RenderGridBlueprintAssetDefinition.h` (Private)


#### class `URenderGridBlueprintAssetDefinition`  
`class URenderGridBlueprintAssetDefinition : public UAssetDefinitionDefault`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: This class adds support for the RenderGrid (RenderGridBlueprint) class to the AssetDefinition module.
- L19 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L20 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _public prototype_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override;`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/BlueprintModes/RenderGridApplicationModeBase.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridApplicationModeBase`  
`class FRenderGridApplicationModeBase : public FBlueprintEditorApplicationMode`  
_L25-43_
- inherits: `FBlueprintEditorApplicationMode`
- desc: This is the base class for the render grid editor application modes. It contains functionality that's shared between all the render grid editor application modes.
- L28 _public prototype_ `FRenderGridApplicationModeBase(TSharedPtr<IRenderGridEditor> InRenderGridEditor, FName InModeName);`
- L32 _protected prototype_ `URenderGridBlueprint* GetBlueprint() const;` — Returns the RenderGridBlueprint of the editor that was given to the constructor.
- L35 _protected prototype_ `TSharedPtr<IRenderGridEditor> GetBlueprintEditor() const;` — Returns the editor that was given to the constructor.
- L39 _protected member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — The editor that was given to the constructor.
- L42 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in the mode.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RenderGrid` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderGrid` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/BlueprintModes/RenderGridApplicationModeListing.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridApplicationModeListing`  
`class FRenderGridApplicationModeListing : public FRenderGridApplicationModeBase`  
_L14-24_
- inherits: `FRenderGridApplicationModeBase`
- desc: This is the application mode for the render grid editor listing functionality (the list of render grid jobs, with the render previews, the render grid job properties, etc).
- L17 _public prototype_ `FRenderGridApplicationModeListing(TSharedPtr<IRenderGridEditor> InRenderGridEditor);`
- L20 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L21 _public prototype_ `virtual void PreDeactivateMode() override;`
- L22 _public prototype_ `virtual void PostActivateMode() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/BlueprintModes/RenderGridApplicationModeLogic.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridApplicationModeLogic`  
`class FRenderGridApplicationModeLogic : public FRenderGridApplicationModeBase`  
_L15-25_
- inherits: `FRenderGridApplicationModeBase`
- desc: This is the application mode for the render grid editor 'logic' functionality (the blueprint graph).
- L18 _public prototype_ `FRenderGridApplicationModeLogic(TSharedPtr<IRenderGridEditor> InRenderGridEditor);`
- L21 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L22 _public prototype_ `virtual void PreDeactivateMode() override;`
- L23 _public prototype_ `virtual void PostActivateMode() override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGrid` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/BlueprintModes/RenderGridApplicationModes.h` (Private)


#### struct `UE::RenderGrid::Private::FRenderGridApplicationModes`  
`struct FRenderGridApplicationModes`  
_L13-28_
- desc: This struct contains the IDs as well as the localized text of each of the render grid editor application modes.
- L17 _public member_ `static const FName ListingMode;` — Constant for the listing mode.
- L20 _public member_ `static const FName LogicMode;` — Constant for the logic mode.
- L24 _public prototype_ `static FText GetLocalizedMode(const FName InMode);` — Returns the localized text for the given render grid editor application mode.
- L27 _private prototype_ `FRenderGridApplicationModes() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RenderGrid` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Commands/RenderGridEditorCommands.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridEditorCommands`  
`class FRenderGridEditorCommands : public TCommands<FRenderGridEditorCommands>`  
_L15-39_
- inherits: `TCommands<FRenderGridEditorCommands>`
- desc: Contains the commands for the render grid editor.
- L18 _public function_ `FRenderGridEditorCommands() : TCommands<FRenderGridEditorCommands>(TEXT("RenderGridEditor"), NSLOCTEXT("Contexts", "RenderGridEditor", "Render Grid Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L25 _public prototype_ `virtual void RegisterCommands() override;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> AddJob;` — Creates and adds a new job to the grid.
- L32 _public member_ `TSharedPtr<FUICommandInfo> DuplicateJob;` — Duplicates the selected job(s) and adds it to the grid.
- L35 _public member_ `TSharedPtr<FUICommandInfo> DeleteJob;` — Deletes the selected job(s) from the grid.
- L38 _public member_ `TSharedPtr<FUICommandInfo> BatchRenderList;` — Renders the enabled job(s) in batch.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGrid` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Factories/RenderGridBlueprintFactory.h` (Private)


#### class `URenderGridBlueprintFactory`  
`class URenderGridBlueprintFactory : public UFactory`  
_L19-34_
- reflection: `UCLASS(MinimalAPI, HideCategories=Object)`
- inherits: `UFactory`
- desc: The factory that creates URenderGridBlueprint (render grid) instances.
- L24 _public prototype_ `URenderGridBlueprintFactory();`
- L26 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L27 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L28 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L29 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L33 _public member_ `TSubclassOf<URenderGrid> ParentClass;` — `UPROPERTY(EditAnywhere, Category="Render Grid Factory", Meta = (AllowAbstract = ""))` — The parent class of the created blueprint.

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Factories/RenderGridPropsSourceWidgetFactoryLocal.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridPropsSourceWidgetFactoryLocal`  
`class FRenderGridPropsSourceWidgetFactoryLocal final : public IRenderGridPropsSourceWidgetFactory`  
_L14-18_
- inherits: `IRenderGridPropsSourceWidgetFactory`
- desc: The factory that creates props source instances for the props type "local".
- L17 _public prototype_ `virtual TSharedPtr<SRenderGridPropsBase> CreateInstance(URenderGridPropsSourceBase* PropsSource, TSharedPtr<IRenderGridEditor> BlueprintEditor) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Factories/RenderGridPropsSourceWidgetFactoryRemoteControl.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridPropsSourceWidgetFactoryRemoteControl`  
`class FRenderGridPropsSourceWidgetFactoryRemoteControl final : public IRenderGridPropsSourceWidgetFactory`  
_L14-18_
- inherits: `IRenderGridPropsSourceWidgetFactory`
- desc: The factory that creates props source instances for the props type "remote control".
- L17 _public prototype_ `virtual TSharedPtr<SRenderGridPropsBase> CreateInstance(URenderGridPropsSourceBase* PropsSource, TSharedPtr<IRenderGridEditor> BlueprintEditor) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/RenderGridEditorModule.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridEditorModule`  
`class FRenderGridEditorModule : public IRenderGridEditorModule`  
_L16-51_
- inherits: `IRenderGridEditorModule`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `virtual TSharedRef<IRenderGridEditor> CreateRenderGridEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, URenderGridBlueprint* InBlueprint) override;`
- L27 _public prototype_ `virtual TSharedPtr<SRenderGridPropsBase> CreatePropsSourceWidget(URenderGridPropsSourceBase* PropsSource, TSharedPtr<IRenderGridEditor> BlueprintEditor) override;`
- L28 _public function_ `virtual const TMap<ERenderGridPropsSourceType, TSharedPtr<IRenderGridPropsSourceWidgetFactory>>& GetPropsSourceWidgetFactories() const override`
- L32 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend GUI of the render grid editor menus.
- L35 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend GUI of the render grid editor toolbars.
- L39 _private prototype_ `void HandleNewBlueprintCreated(UBlueprint* InBlueprint);` — Handle a new render grid blueprint being created.
- L41 _private prototype_ `void RegisterPropsSourceWidgetFactories();`
- L42 _private prototype_ `void UnregisterPropsSourceWidgetFactories();`
- L43 _private prototype_ `void RegisterPropsSourceWidgetFactory(const ERenderGridPropsSourceType PropsSourceType, const TSharedPtr<IRenderGridPropsSourceWidgetFactory>& InFactory);`
- L44 _private prototype_ `void UnregisterPropsSourceWidgetFactory(const ERenderGridPropsSourceType PropsSourceType);`
- L47 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L48 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L50 _private member_ `TMap<ERenderGridPropsSourceType, TSharedPtr<IRenderGridPropsSourceWidgetFactory>> PropsSourceWidgetFactories;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderGrid` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Styles/RenderGridEditorStyle.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridEditorStyle`  
`class FRenderGridEditorStyle`  
_L14-36_
- desc: A static class containing the style setup of the render grid plugin.
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L19 _public prototype_ `static void Initialize();`
- L20 _public prototype_ `static void Shutdown();`
- L21 _public prototype_ `static void ReloadTextures();`
- L23 _public prototype_ `static FName GetStyleSetName();`
- L24 _public prototype_ `static const FLinearColor& GetColor(FName PropertyName, const ANSICHAR* Specifier = nullptr);`
- L25 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr);`
- L28 _public function_ `template<typename WidgetStyleType> static const WidgetStyleType& GetWidgetStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L34 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L35 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/TabFactory/RenderGridJobListTabSummoner.h` (Private)


#### struct `UE::RenderGrid::Private::FRenderGridJobListTabSummoner`  
`struct FRenderGridJobListTabSummoner : FWorkflowTabFactory`  
_L20-33_
- inherits: `FWorkflowTabFactory`
- desc: The render grid job list tab factory.
- L24 _public member_ `static const FName TabID;` — Unique ID representing this tab.
- L27 _public prototype_ `FRenderGridJobListTabSummoner(TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L32 _protected member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A weak reference to the blueprint editor.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/TabFactory/RenderGridJobPropertiesTabSummoner.h` (Private)


#### struct `UE::RenderGrid::Private::FRenderGridJobPropertiesTabSummoner`  
`struct FRenderGridJobPropertiesTabSummoner : FWorkflowTabFactory`  
_L20-33_
- inherits: `FWorkflowTabFactory`
- desc: The render grid job properties tab factory.
- L24 _public member_ `static const FName TabID;` — Unique ID representing this tab.
- L27 _public prototype_ `FRenderGridJobPropertiesTabSummoner(TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L32 _protected member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A weak reference to the blueprint editor.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/TabFactory/RenderGridPropertiesTabSummoner.h` (Private)


#### struct `UE::RenderGrid::Private::FRenderGridPropertiesTabSummoner`  
`struct FRenderGridPropertiesTabSummoner : FWorkflowTabFactory`  
_L20-33_
- inherits: `FWorkflowTabFactory`
- desc: The render grid properties tab factory.
- L24 _public member_ `static const FName TabID;` — Unique ID representing this tab.
- L27 _public prototype_ `FRenderGridPropertiesTabSummoner(TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L32 _protected member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A weak reference to the blueprint editor.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/TabFactory/RenderGridViewerTabSummoner.h` (Private)


#### struct `UE::RenderGrid::Private::FRenderGridViewerTabSummoner`  
`struct FRenderGridViewerTabSummoner : FWorkflowTabFactory`  
_L20-33_
- inherits: `FWorkflowTabFactory`
- desc: The render grid viewer tab factory.
- L24 _public member_ `static const FName TabID;` — Unique ID representing this tab.
- L27 _public prototype_ `FRenderGridViewerTabSummoner(TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L32 _protected member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A weak reference to the blueprint editor.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Toolkit/RenderGridEditor.h` (Private)


#### class `URenderGridJobSelection`  
`class URenderGridJobSelection : public UObject`  
_L29-43_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The selected render grid jobs. This is placed in a separate class, so it can be an UObject, so it can be placed in the undo/redo buffer.
- L34 _public prototype_ `URenderGridJobSelection();`
- L37 _public prototype_ `bool SetSelectedRenderGridJobs(const TArray<URenderGridJob*>& Jobs);` — Sets the new job selection. Returns true if it is different from the previous selection, returns false if it was exactly the same.
- L42 _public member_ `TSet<FGuid> SelectedRenderGridJobIds;` — `UPROPERTY()` — The GUIDs of the currently selected render grid jobs.

#### class `UE::RenderGrid::Private::FRenderGridEditor`  
`class FRenderGridEditor : public IRenderGridEditor`  
_L54-214_
- inherits: `IRenderGridEditor`
- desc: The render grid editor implementation.
- L58 _public member_ `static constexpr float TimeInSecondsToRemainDebugging = 4.0f;` — The time it should remain in debugging mode after it has been turned off.
- L62 _protected member_ `static TStrongObjectPtr<URenderGridJobSelection> RenderGridJobSelection;` — The currently selected render grid jobs. It's static so multiple open render grid editors won't cause bugs with each other.
- L66 _public prototype_ `void InitRenderGridEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, URenderGridBlueprint* InRenderGridBlueprint);`
- L69 _public prototype_ `FRenderGridEditor();`
- L73 _public prototype_ `virtual void CreateDefaultCommands() override;`
- L74 _public prototype_ `virtual UBlueprint* GetBlueprintObj() const override;`
- L75 _public prototype_ `virtual FGraphAppearanceInfo GetGraphAppearance(UEdGraph* InGraph) const override;`
- L76 _public function_ `virtual bool IsInAScriptingMode() const override`
- L77 _public prototype_ `virtual void OnActiveTabChanged(TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated) override;`
- L78 _public prototype_ `virtual void SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents) override;`
- L79 _public prototype_ `virtual void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;`
- L80 _public prototype_ `virtual void PostUndo(bool bSuccessful) override;`
- L81 _public prototype_ `virtual void PostRedo(bool bSuccessful) override;`
- L82 _public prototype_ `virtual void Compile() override;`
- L86 _public prototype_ `virtual URenderGridBlueprint* GetRenderGridBlueprint() const override;`
- L87 _public prototype_ `virtual URenderGrid* GetInstance() const override;`
- L88 _public prototype_ `virtual void SetIsDebugging(const bool bInIsDebugging) override;`
- L89 _public function_ `virtual TSharedPtr<FRenderGridBlueprintEditorToolbar> GetRenderGridToolbarBuilder() override`
- L90 _public prototype_ `virtual bool IsBatchRendering() const override;`
- L91 _public function_ `virtual URenderGridQueue* GetBatchRenderQueue() const override`
- L92 _public prototype_ `virtual bool IsPreviewRendering() const override;`
- L93 _public function_ `virtual URenderGridQueue* GetPreviewRenderQueue() const override`
- L94 _public prototype_ `virtual void SetPreviewRenderQueue(URenderGridQueue* Queue) override;`
- L95 _public prototype_ `virtual void MarkAsModified() override;`
- L96 _public prototype_ `virtual TArray<URenderGridJob*> GetSelectedRenderGridJobs() const override;`
- L97 _public prototype_ `virtual void SetSelectedRenderGridJobs(const TArray<URenderGridJob*>& Jobs) override;`
- L101 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L102 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L103 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L104 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L105 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L106 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L107 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L111 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L112 _public prototype_ `virtual TStatId GetStatId() const override;`
- L116 _public prototype_ `void RefreshInstance();` — Immediately rebuilds the render grid instance that is being shown in the editor.
- L120 _private prototype_ `virtual void OnBlueprintChangedImpl(UBlueprint* InBlueprint, bool bIsJustBeingCompiled = false) override;` — Called whenever the blueprint is structurally changed.
- L124 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L128 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L129 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L130 _protected prototype_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L135 _protected prototype_ `void BindCommands();` — Binds the FRenderGridEditorCommands commands to functions in this editor.
- L138 _protected prototype_ `void AddJobAction();` — Creates and adds a new render grid job.
- L141 _protected prototype_ `void DuplicateJobAction();` — Duplicates the selected render grid job(s).
- L144 _protected prototype_ `void DeleteJobAction();` — Removes the currently selected render grid job(s).
- L147 _protected prototype_ `void BatchRenderListAction();` — Renders all the currently enabled render grid jobs.
- L150 _protected prototype_ `void OnBatchRenderListActionFinished();` — The callback for when the batch render list action finishes.
- L153 _protected prototype_ `void UndoAction();` — Undo the last action.
- L156 _protected prototype_ `void RedoAction();` — Redo the last action that was undone.
- L160 _private prototype_ `void ExtendMenu();` — Extends the menu.
- L163 _private prototype_ `void ExtendToolbar();` — Extends the toolbar.
- L166 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);` — Fills the toolbar with content.
- L169 _private prototype_ `void DestroyInstance();` — Destroy the render grid instance that is currently visible in the editor.
- L172 _private prototype_ `void UpdateInstance(UBlueprint* InBlueprint, bool bInForceFullUpdate);` — Makes a newly compiled/opened render grid instance visible in the editor.
- L175 _private prototype_ `FActionMenuContent HandleCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Wraps the normal blueprint editor's action menu creation callback.
- L179 _private member_ `TSharedPtr<FRenderGridBlueprintEditorToolbar> RenderGridToolbar;` — The toolbar builder that is used to customize the toolbar of this editor.
- L183 _protected member_ `TSharedPtr<FExtender> MenuExtender;` — The extender to pass to the level editor to extend it's window menu.
- L186 _protected member_ `TSharedPtr<FExtender> ToolbarExtender;` — The toolbar extender of this editor.
- L189 _protected member_ `TWeakObjectPtr<URenderGridBlueprint> PreviewBlueprintWeakPtr;` — The blueprint instance that's currently visible in the editor.
- L192 _protected member_ `mutable TWeakObjectPtr<URenderGrid> RenderGridWeakPtr;` — The current render grid instance that's visible in the editor.
- L195 _protected member_ `bool bRunRenderNewBatch;` — True if it should call BatchRenderListAction() next frame.
- L198 _protected member_ `TStrongObjectPtr<URenderGridQueue> BatchRenderQueue;` — The current batch render queue, if any.
- L201 _protected member_ `TStrongObjectPtr<URenderGridQueue> PreviewRenderQueue;` — The current preview render queue, if any.
- L204 _protected member_ `float DebuggingTimeInSecondsRemaining;` — The time it should still remain in debugging mode (after it has been turned off).
- L207 _protected member_ `bool bIsDebugging;` — True if the graph editor is currently in debugging mode.
- L210 _protected member_ `bool bPreviousShouldHideUI;` — The value of ShouldHideUI() during the last tick.
- L213 _protected member_ `TSet<FGuid> PreviousSelectedRenderGridJobIds;` — The value of RenderGridJobSelection.Get()->SelectedRenderGridJobIds() during the last tick.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderGrid` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace RenderGrid` (scope `UE`)
- L46 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRenderGridEditorClosed, const UE::RenderGrid::IRenderGridEditor*, URenderGridBlueprint*);`
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRenderGridEditorClosed, const UE::RenderGrid::IRenderGridEditor*, URenderGridBlueprint*);` (scope `UE::RenderGrid::Private`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/Toolkit/RenderGridEditorToolbar.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridBlueprintEditorToolbar`  
`class FRenderGridBlueprintEditorToolbar : public TSharedFromThis<FRenderGridBlueprintEditorToolbar>`  
_L23-41_
- inherits: `TSharedFromThis<FRenderGridBlueprintEditorToolbar>`
- desc: Handles all of the toolbar related construction for the render grid blueprint editor.
- L26 _public prototype_ `FRenderGridBlueprintEditorToolbar(TSharedPtr<IRenderGridEditor>& InRenderGridEditor);`
- L29 _public prototype_ `void AddRenderGridBlueprintEditorModesToolbar(TSharedPtr<FExtender> Extender);` — Adds the mode-switch UI to the editor.
- L32 _public prototype_ `void AddListingModeToolbar(UToolMenu* InMenu);` — Adds the toolbar for the listing mode to the editor.
- L35 _public prototype_ `void AddLogicModeToolbar(UToolMenu* InMenu);` — Adds the toolbar for the logic mode to the editor.
- L39 _public prototype_ `void FillRenderGridBlueprintEditorModesToolbar(FToolBarBuilder& ToolbarBuilder);` — Creates the mode-switch UI.
- L40 _public member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RenderGrid` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderGrid` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridDragHandle.h` (Private)


#### class `SRenderGridDragHandle`  
`template<typename DragDropType> class SRenderGridDragHandle : public SCompoundWidget`  
_L17-82_
- inherits: `SCompoundWidget`
- desc: A reusable widget for drag and drop functionality.
- L20 _public typedef_ `using DragDropWidgetType = typename DragDropType::WidgetType;`
- L21 _public typedef_ `using HeldItemType = typename DragDropType::HeldItemType;`
- L23 _public function_ `SLATE_BEGIN_ARGS(SRenderGridDragHandle)`
- L24 _public function_ `SLATE_ARGUMENT(TSharedPtr<DragDropWidgetType>, Widget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, HeldItemType InItem)`
- L48 _public function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L53 _public function_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L65 _public function_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation()`
- L78 _private member_ `TWeakPtr<DragDropWidgetType> WidgetWeakPtr;` — Holds the widget to display when dragging.
- L81 _private member_ `HeldItemType Item;` — Holds the item being dragged.

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridEditableTextBlock.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridEditableTextBlock`  
`class SRenderGridEditableTextBlock : public SCompoundWidget`  
_L17-57_
- inherits: `SCompoundWidget`
- desc: A reusable text widget that can be modified by pressing a pencil button that's shown next to it.
- L20 _public function_ `SLATE_BEGIN_ARGS(SRenderGridEditableTextBlock)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(FText, Text)` — The text displayed in this text block
- L26 _public prototype_ `void Construct(const FArguments& InArgs);`
- L33 _public function_ `const FText& GetText() const` — Gets the text of this text block @return	This text block's text string
- L37 _public prototype_ `void SetText(TAttribute<FText> InText);` — Sets the text for this text block
- L40 _public prototype_ `void SetText(const FText& InText);` — Sets the text for this text block
- L43 _protected prototype_ `void OnTextBlockCommitted(const FText& InLabel, ETextCommit::Type InCommitInfo);`
- L47 _protected member_ `TSharedPtr<SInlineEditableTextBlock> TextBlock;` — A reference to the text block.
- L50 _protected member_ `FText Text;` — The current text in the text block (read-only).
- L53 _protected member_ `bool bNeedsRename;` — Whether the group needs to be renamed. (As requested by a click on the rename button)
- L56 _protected member_ `FOnRenderGridEditableTextBlockTextCommitted OnTextCommittedDelegate;` — Delegate to execute when editing mode text is committed.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGrid` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnRenderGridEditableTextBlockTextCommitted, const FText&, ETextCommit::Type);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnRenderGridEditableTextBlockTextCommitted, const FText&, ETextCommit::Type);` (scope `UE::RenderGrid::Private`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridFileSelectorTextBlock.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridFileSelectorTextBlock`  
`class SRenderGridFileSelectorTextBlock : public SCompoundWidget`  
_L17-57_
- inherits: `SCompoundWidget`
- desc: A reusable filepath text widget that can be modified by pressing a folder button that's shown next to it, which will open up a file selector popup.
- L20 _public function_ `SLATE_BEGIN_ARGS(SRenderGridFileSelectorTextBlock)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(FText, Text)` — The text displayed in this text block
- L33 _public function_ `const FText& GetText() const` — Gets the text of this text block @return	This text block's text string
- L37 _public prototype_ `void SetText(TAttribute<FText> InText);` — Sets the text for this text block
- L40 _public prototype_ `void SetText(const FText& InText);` — Sets the text for this text block
- L43 _protected prototype_ `FReply OnOpenDirectoryDialog();`
- L47 _protected member_ `TSharedPtr<SInlineEditableTextBlock> TextBlock;` — A reference to the text block.
- L50 _protected member_ `FText Text;` — The current text in the text block (read-only).
- L53 _protected member_ `TAttribute<FString> FolderPath;` — The default path of the open-directory dialog (read-only).
- L56 _protected member_ `FOnRenderGridFileSelectorTextBlockTextCommitted OnTextCommittedDelegate;` — Delegate to execute when editing mode text is committed.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGrid` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnRenderGridFileSelectorTextBlockTextCommitted, const FText&, ETextCommit::Type);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnRenderGridFileSelectorTextBlockTextCommitted, const FText&, ETextCommit::Type);` (scope `UE::RenderGrid::Private`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridRemoteControlEntity.h` (Private)


#### struct `UE::RenderGrid::Private::SRenderGridRemoteControlEntity`  
`struct SRenderGridRemoteControlEntity : SRenderGridRemoteControlTreeNode`  
_L20-42_
- inherits: `SRenderGridRemoteControlTreeNode`
- desc: The remote control entity widget, copied over from the remote control plugin, and slightly modified and cleaned up for usage in the render grid plugin. @Note if you inherit from this struct, you must call SRenderGridExposedEntity::Initialize.
- L23 _public prototype_ `TSharedPtr<FRemoteControlEntity> GetEntity() const;`
- L24 _public function_ `virtual FGuid GetRCId() const override final`
- L28 _protected prototype_ `void Initialize(const FGuid& InEntityId, URemoteControlPreset* InPreset);`
- L31 _protected prototype_ `TSharedRef<SWidget> CreateEntityWidget(const TSharedPtr<SWidget> ValueWidget);` — Create an exposed entity widget.
- L35 _protected member_ `FGuid EntityId;` — Id of the entity.
- L38 _protected member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeakPtr;` — The underlying preset.
- L41 _protected member_ `FName CachedLabel;` — Display name of the entity.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RenderGrid` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridRemoteControlField.h` (Private)


#### struct `UE::RenderGrid::Private::SRenderGridRemoteControlFieldChildNode`  
`struct SRenderGridRemoteControlFieldChildNode : SRenderGridRemoteControlTreeNode`  
_L28-39_
- inherits: `SRenderGridRemoteControlTreeNode`
- desc: The remote control field child node widget, copied over from the remote control plugin, and slightly modified and cleaned up for usage in the render grid plugin. Represents a child of an exposed field widget.
- L30 _public function_ `SLATE_BEGIN_ARGS(SRenderGridRemoteControlFieldChildNode)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IDetailTreeNode>& InNode, FRenderGridRemoteControlColumnSizeData InColumnSizeData);`
- L34 _public function_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRenderGridRemoteControlTreeNode>>& OutChildren) const override`
- L35 _public function_ `virtual FGuid GetRCId() const override`
- L36 _public function_ `virtual ENodeType GetRCType() const override`
- L38 _public member_ `TArray<TSharedPtr<SRenderGridRemoteControlFieldChildNode>> ChildrenNodes;`

#### struct `UE::RenderGrid::Private::SRenderGridRemoteControlField`  
`struct SRenderGridRemoteControlField : SRenderGridRemoteControlEntity`  
_L47-100_
- inherits: `SRenderGridRemoteControlEntity`
- desc: The remote control field widget, copied over from the remote control plugin, and slightly modified and cleaned up for usage in the render grid plugin. Widget that displays an exposed field.
- L49 _public function_ `SLATE_BEGIN_ARGS(SRenderGridRemoteControlField) : _Preset(nullptr)`
- L51 _public prototype_ `SLATE_ATTRIBUTE(URemoteControlPreset*, Preset) SLATE_END_ARGS() static TSharedPtr<SRenderGridRemoteControlTreeNode> MakeInstance(const FRenderGridRemoteControlGenerateWidgetArgs& Args);`
- L56 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FRemoteControlField> Field, FRenderGridRemoteControlColumnSizeData ColumnSizeData);`
- L60 _public prototype_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRenderGridRemoteControlTreeNode>>& OutChildren) const override;`
- L61 _public prototype_ `virtual ENodeType GetRCType() const override;`
- L62 _public prototype_ `virtual void Refresh() override;`
- L63 _public prototype_ `virtual void RefreshValue() override;`
- L67 _public function_ `TWeakPtr<FRemoteControlField> GetRemoteControlField() const` — Get a weak pointer to the underlying remote control field.
- L70 _public prototype_ `FName GetFieldLabel() const;` — Get this field's label.
- L73 _public prototype_ `EExposedFieldType GetFieldType() const;` — Get this field's type.
- L76 _public prototype_ `void GetBoundObjects(TSet<UObject*>& OutBoundObjects) const;` — Returns this widget's underlying objects.
- L80 _private prototype_ `TSharedRef<SWidget> ConstructWidget();` — Construct a property widget.
- L83 _private prototype_ `TSharedRef<SWidget> MakeFieldWidget(const TSharedRef<SWidget>& InWidget);` — Create the wrapper around the field value widget.
- L86 _private prototype_ `void ConstructPropertyWidget();` — Construct this field widget as a property widget.
- L90 _private member_ `TWeakPtr<FRemoteControlField> FieldWeakPtr;` — Weak pointer to the underlying RC Field.
- L93 _private member_ `TArray<TSharedPtr<SRenderGridRemoteControlFieldChildNode>> ChildWidgets;` — This exposed field's child widgets (ie. An array's rows)
- L96 _private member_ `TSharedPtr<IPropertyRowGenerator> Generator;` — The property row generator.
- L99 _private member_ `int32 FramesUntilRerender;` — Has a value of 1 if it should call Render() next frame, 2+ if it should subtract 1 from its value next frame, 0 and below and it won't do anything.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace RenderGrid` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridRemoteControlTreeNode.h` (Private)


#### struct `UE::RenderGrid::Private::FRenderGridRemoteControlColumnSizeData`  
`struct FRenderGridRemoteControlColumnSizeData`  
_L22-38_
- desc: The remote control column size data struct, copied over from the remote control plugin, and slightly modified and cleaned up for usage in the render grid plugin.
- L24 _public member_ `TAttribute<float> LeftColumnWidth = 0.0f;`
- L25 _public member_ `TAttribute<float> RightColumnWidth = 0.0f;`
- L26 _public member_ `SSplitter::FOnSlotResized OnWidthChanged;`
- L28 _public function_ `void SetColumnWidth(const float InWidth)`
- L33 _public function_ `bool operator!=(const FRenderGridRemoteControlColumnSizeData& RHS) const`
- L34 _public function_ `bool operator==(const FRenderGridRemoteControlColumnSizeData& RHS) const`

#### struct `UE::RenderGrid::Private::FRenderGridRemoteControlGenerateWidgetArgs`  
`struct FRenderGridRemoteControlGenerateWidgetArgs`  
_L43-55_
- desc: The remote control generate widget args struct, copied over from the remote control plugin, and slightly modified and cleaned up for usage in the render grid plugin.
- L45 _public member_ `TObjectPtr<URemoteControlPreset> Preset = nullptr;`
- L46 _public member_ `FRenderGridRemoteControlColumnSizeData ColumnSizeData;`
- L47 _public member_ `TSharedPtr<FRemoteControlEntity> Entity = nullptr;`
- L48 _public member_ `FName EntityFieldLabel;`
- L50 _public function_ `bool operator!=(const FRenderGridRemoteControlGenerateWidgetArgs& RHS) const`
- L51 _public function_ `bool operator==(const FRenderGridRemoteControlGenerateWidgetArgs& RHS) const`

#### struct `UE::RenderGrid::Private::SRenderGridRemoteControlTreeNode`  
`struct SRenderGridRemoteControlTreeNode : SCompoundWidget`  
_L63-122_
- inherits: `SCompoundWidget`
- desc: The remote control tree node widget, copied over from the remote control plugin, and slightly modified and cleaned up for usage in the render grid plugin. A node in the panel tree view.
- L76 _public function_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRenderGridRemoteControlTreeNode>>& OutChildren) const` — Get this tree node's children.
- L79 _public function_ `virtual FGuid GetRCId() const` — Get this node's ID if any.
- L82 _public function_ `virtual ENodeType GetRCType() const` — Get get this node's type.
- L85 _public function_ `virtual void Refresh()` — Refresh the node.
- L88 _public function_ `virtual void RefreshValue()` — Refreshes the value of the node, without replacing the node.
- L101 _protected prototype_ `TSharedRef<SWidget> MakeSplitRow(TSharedRef<SWidget> LeftColumn, TSharedRef<SWidget> RightColumn);` — Create a widget that represents a row with a splitter.
- L104 _protected prototype_ `TSharedRef<SWidget> MakeNodeWidget(const FRenderGridMakeNodeWidgetArgs& Args);` — Create a widget that represents a node in the panel tree hierarchy.
- L108 _private prototype_ `void OnLeftColumnResized(float) const;` — Stub handler for column resize callback to prevent the splitter from handling it internally.
- L111 _private prototype_ `float GetLeftColumnWidth() const;`
- L112 _private prototype_ `float GetRightColumnWidth() const;`
- L113 _private prototype_ `void SetColumnWidth(float InWidth);`
- L117 _protected member_ `FRenderGridRemoteControlColumnSizeData ColumnSizeData;` — Holds the row's columns' width.
- L121 _private member_ `static constexpr float SplitterOffset = 0.008f;` — The splitter offset to align the group splitter with the other row's splitters.

#### enum `UE::RenderGrid::Private::SRenderGridRemoteControlTreeNode::ENodeType`  
`enum class ENodeType : uint8`  
_L65-73_
- L67 _public enumerator_ `Invalid`
- L68 _public enumerator_ `Group`
- L69 _public enumerator_ `Field`
- L70 _public enumerator_ `FieldChild`
- L71 _public enumerator_ `Actor`
- L72 _public enumerator_ `Material`

#### struct `UE::RenderGrid::Private::SRenderGridRemoteControlTreeNode::FRenderGridMakeNodeWidgetArgs`  
`struct FRenderGridMakeNodeWidgetArgs`  
_L91-98_
- L93 _public member_ `TSharedPtr<SWidget> DragHandle;`
- L94 _public member_ `TSharedPtr<SWidget> NameWidget;`
- L95 _public member_ `TSharedPtr<SWidget> RenameButton;`
- L96 _public member_ `TSharedPtr<SWidget> ValueWidget;`
- L97 _public member_ `TSharedPtr<SWidget> UnexposeButton;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace RenderGrid` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Components/SRenderGridViewerFrameSlider.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridViewerFrameSlider`  
`class SRenderGridViewerFrameSlider : public SCompoundWidget`  
_L21-75_
- inherits: `SCompoundWidget`
- desc: The frame slider widget for the render grid viewer widgets.
- L24 _public function_ `SLATE_BEGIN_ARGS(SRenderGridViewerFrameSlider)`
- L25 _public prototype_ `SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)` — Called when the value is changed by the slider
- L32 _public function_ `float GetValue()` — Returns the current value of the frame slider (a value from 0.0 to 1.0, based on how far the slider is to the right, left=0.0, right=1.0).
- L35 _public prototype_ `void ClearFramesText();` — Clears the text of the start, current and end frame.
- L38 _public prototype_ `void SetFramesText(const int32 StartFrame, const int32 SelectedFrame, const int32 EndFrame);` — Sets the text of the start, current and end frame.
- L41 _public prototype_ `bool SetFramesText(URenderGridJob* Job);` — Sets the text of the start, current and end frame according to the start and end frame of the given render grid job, figures out the selected frame with the current value of the frame slider.
- L44 _public prototype_ `TOptional<int32> GetSelectedSequenceFrame(URenderGridJob* Job);` — Gets the selected sequence frame of the given render grid job, based on the current value of the frame slider.
- L47 _public prototype_ `TOptional<int32> GetSelectedFrame(URenderGridJob* Job);` — Gets the selected frame (that will be output) of the given render grid job, based on the current value of the frame slider.
- L50 _private prototype_ `void FrameSliderValueChanged(const float NewValue);`
- L51 _private prototype_ `void FrameSliderValueChangedEnd();`
- L55 _private member_ `TSharedPtr<SSlider> FrameSlider;` — The widget that allows the user to select what frame they'd like to see.
- L59 _private member_ `static float FrameSliderValue;` — The value of the frame slider.
- L62 _private member_ `TSharedPtr<STextBlock> FrameSliderStartFrameText;` — The text for the start frame under the slider.
- L65 _private member_ `TSharedPtr<STextBlock> FrameSliderSelectedFrameText;` — The text for the selected frame under the slider.
- L68 _private member_ `TSharedPtr<STextBlock> FrameSliderEndFrameText;` — The text for the end frame under the slider.
- L71 _private member_ `FOnFloatValueChanged OnValueChanged;` — Called when the value is changed by the slider.
- L74 _private member_ `FSimpleDelegate OnCaptureEnd;` — Called when the capture ends.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RenderGrid` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGrid.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGrid`  
`class SRenderGrid : public SCompoundWidget, public FNotifyHook`  
_L26-58_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: A widget with which the user can modify the render grid. Doesn't contain any UI elements to modify the jobs that the grid contains.
- L29 _public function_ `SLATE_BEGIN_ARGS(SRenderGrid)`
- L30 _public prototype_ `SLATE_END_ARGS() virtual void Tick(const FGeometry&, const double, const float) override;`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L36 _public prototype_ `virtual void NotifyPreChange(FEditPropertyChain* PropertyAboutToChange) override;`
- L37 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;`
- L41 _protected prototype_ `void SetRenderGrid(URenderGrid* RenderGrid);`
- L45 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L48 _private member_ `TWeakObjectPtr<URenderGrid> RenderGridWeakPtr;` — The render grid instance that's being edited in the details view.
- L51 _private member_ `TSharedPtr<IDetailsView> RenderGridDetailsView;` — A reference to the details view.
- L54 _private member_ `TSharedPtr<IDetailsView> RenderGridSettingsDetailsView;` — A reference to the details view.
- L57 _private member_ `TSharedPtr<IDetailsView> RenderGridDefaultsDetailsView;` — A reference to the details view.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridJob.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridJob`  
`class SRenderGridJob : public SCompoundWidget, public FNotifyHook`  
_L26-49_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: A widget with which the user can modify the selected render grid job. Can only modify 1 render grid job at a time, this widget will show nothing when 0 or 2+ render grid jobs are selected.
- L29 _public function_ `SLATE_BEGIN_ARGS(SRenderGridJob)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L35 _public prototype_ `virtual void NotifyPreChange(FEditPropertyChain* PropertyAboutToChange) override;` — FNotifyHook interface
- L36 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;`
- L41 _private prototype_ `void Refresh();` — Updates the details view.
- L45 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L48 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — A reference to the details view.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridJobList.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridJobList`  
`class SRenderGridJobList : public SCompoundWidget`  
_L40-100_
- inherits: `SCompoundWidget`
- desc: A widget with which the user can see and modify the list of render grid jobs that the render grid contains.
- L43 _public function_ `SLATE_BEGIN_ARGS(SRenderGridJobList)`
- L44 _public prototype_ `SLATE_END_ARGS() virtual void Tick(const FGeometry&, const double, const float) override;`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L50 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L54 _public prototype_ `void Refresh();` — Refreshes the content of this widget.
- L57 _public prototype_ `void RefreshHeaderEnabledCheckbox();` — Refreshes the state of the header is-job-enabled checkbox.
- L61 _private prototype_ `void OnRenderGridJobCreated(URenderGridJob* Job);` — Gets called when a render grid job is created.
- L64 _private prototype_ `void OnHeaderCheckboxToggled(ECheckBoxState State);` — Gets called when the header is-job-enabled checkbox is toggled.
- L67 _private prototype_ `ECheckBoxState GetDesiredHeaderEnabledCheckboxState();` — Gets the desired state of the header is-job-enabled checkbox.
- L70 _private prototype_ `void AddRenderStatusColumn();` — Adds the render status column to the job list.
- L73 _private prototype_ `void RemoveRenderStatusColumn();` — Removes the render status column from the job list.
- L76 _private prototype_ `void OnObjectModified(UObject* Object);`
- L77 _private function_ `void OnSearchBarTextChanged(const FText& Text)`
- L81 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L84 _private member_ `TWeakObjectPtr<URenderGrid> RenderGridWeakPtr;` — The render grid that is shown in the UI.
- L87 _private member_ `TArray<URenderGridJob*> RenderGridJobs;` — The render grid jobs that are shown in the UI.
- L90 _private member_ `TSharedPtr<SRenderGridJobListTable> RenderGridJobListWidget;` — The widget that lists the render grid jobs.
- L93 _private member_ `TSharedPtr<SSearchBox> RenderGridSearchBox;` — The search bar widget.
- L96 _private member_ `TSharedPtr<SCheckBox> RenderGridJobEnabledHeaderCheckbox;` — The header checkbox for the enable/disable column.
- L99 _private member_ `bool bPreviousIsBatchRendering;` — The value of BlueprintEditorWeakPtr.Get()->IsBatchRendering() during the last Refresh().

#### class `UE::RenderGrid::Private::SRenderGridJobListTable`  
`class SRenderGridJobListTable : public SListView<URenderGridJob*>`  
_L106-133_
- inherits: `SListView<URenderGridJob*>`
- desc: The widget that contains the rows of render grid jobs.
- L109 _public function_ `SLATE_BEGIN_ARGS(SRenderGridJobListTable)`
- L110 _public prototype_ `SLATE_ARGUMENT(const TArray<URenderGridJob*>*, ListItemsSource) SLATE_ARGUMENT(TSharedPtr<SHeaderRow>, HeaderRow) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<IRenderGridEditor> InBlueprintEditor, const TSharedPtr<SRenderGridJobList>& InJobListWidget);`
- L117 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L122 _private prototype_ `TSharedRef<ITableRow> HandleJobListGenerateRow(URenderGridJob* Item, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget in the session tree view.
- L125 _private prototype_ `void HandleJobListSelectionChanged(URenderGridJob* Item, ESelectInfo::Type SelectInfo);` — Callback for session tree view selection changes.
- L129 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L132 _private member_ `TSharedPtr<SRenderGridJobList> JobListWidget;` — A reference to the job list (the parent widget).

#### class `UE::RenderGrid::Private::SRenderGridJobListTableRow`  
`class SRenderGridJobListTableRow : public SMultiColumnTableRow<URenderGridJob*>`  
_L139-166_
- inherits: `SMultiColumnTableRow<URenderGridJob*>`
- desc: The widget that represents a single render grid job (a single row).
- L142 _public function_ `SLATE_BEGIN_ARGS(SRenderGridJobListTableRow)`
- L143 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TWeakPtr<IRenderGridEditor> InBlueprintEditor, URenderGridJob* InRenderGridJob, const TSharedPtr<SRenderGridJobList>& InJobListWidget);`
- L148 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L151 _public prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InEvent, EItemDropZone InItemDropZone, URenderGridJob* InJob);`
- L152 _public prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InEvent, EItemDropZone InItemDropZone, URenderGridJob* InJob);`
- L153 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L155 _public prototype_ `FText GetRenderStatusText() const;`
- L159 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L162 _private member_ `TWeakObjectPtr<URenderGridJob> RenderGridJobWeakPtr;` — A reference to the render grid job instance.
- L165 _private member_ `TSharedPtr<SRenderGridJobList> JobListWidget;` — A reference to the job list (the parent widget).

#### class `UE::RenderGrid::Private::FRenderGridJobListTableRowDragDropOp`  
`class FRenderGridJobListTableRowDragDropOp final : public FDecoratedDragDropOp`  
_L172-208_
- inherits: `FDecoratedDragDropOp`
- desc: The class that makes it possible to drag and drop render grid jobs (allowing the user to reorganize the render grid job list).
- L177 _public typedef_ `using WidgetType = SRenderGridJobListTableRow;`
- L178 _public typedef_ `using HeldItemType = TObjectPtr<URenderGridJob>;`
- L180 _public function_ `FRenderGridJobListTableRowDragDropOp(const TSharedPtr<WidgetType> InWidget, const HeldItemType InJob) : Job(InJob)`
- L192 _public function_ `HeldItemType GetJob() const`
- L197 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L204 _private member_ `HeldItemType Job;` — The held item.
- L207 _private member_ `TSharedPtr<SWidget> DecoratorWidget;` — Holds the displayed widget.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace RenderGrid` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace RenderGrid` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace RenderGrid` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnRenderGridJobListEditableTextBlockTextCommitted, const FText&, ETextCommit::Type);`
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnRenderGridJobListEditableTextBlockTextCommitted, const FText&, ETextCommit::Type);` (scope `UE::RenderGrid::Private`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridProps.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridProps`  
`class SRenderGridProps : public SCompoundWidget`  
_L26-47_
- inherits: `SCompoundWidget`
- desc: A widget with which the user can modify the props (like the remote control field values) of the selected render grid job. Can only modify the props of 1 render grid job at a time, this widget will show nothing when 0 or 2+ render grid jobs are selected.
- L29 _public function_ `SLATE_BEGIN_ARGS(SRenderGridProps)`
- L30 _public prototype_ `SLATE_END_ARGS() virtual void Tick(const FGeometry&, const double, const float) override;`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L36 _public prototype_ `void Refresh();` — Refreshes the content of this widget.
- L40 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L43 _private member_ `TSharedPtr<SBorder> WidgetContainer;` — The widget that lists the property rows.
- L46 _private member_ `TWeakObjectPtr<URenderGridPropsSourceBase> WidgetPropsSourceWeakPtr;` — The props source that's being shown in this widget.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridPropsBase.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridPropsBase`  
`class SRenderGridPropsBase : public SCompoundWidget`  
_L14-15_
- inherits: `SCompoundWidget`
- desc: The base class of the render grid props widget.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridPropsLocal.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridPropsLocal`  
`class SRenderGridPropsLocal : public SRenderGridPropsBase`  
_L21-35_
- inherits: `SRenderGridPropsBase`
- desc: The render grid props implementation for local properties.
- L24 _public function_ `SLATE_BEGIN_ARGS(SRenderGridPropsLocal)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor, URenderGridPropsSourceLocal* InPropsSource);`
- L31 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L34 _private member_ `TWeakObjectPtr<URenderGridPropsSourceLocal> PropsSourceWeakPtr;` — The props source control.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RenderGrid` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RenderGrid` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridPropsRemoteControl.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridPropsRemoteControl`  
`class SRenderGridPropsRemoteControl : public SRenderGridPropsBase`  
_L25-72_
- inherits: `SRenderGridPropsBase`
- desc: The render grid props implementation for remote control fields.
- L28 _public function_ `SLATE_BEGIN_ARGS(SRenderGridPropsRemoteControl)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor, URenderGridPropsSourceRemoteControl* InPropsSource);`
- L34 _public prototype_ `void UpdateStoredValuesAndRefresh(const bool bForce = false);` — Obtain the latest prop values and refreshes the content of this widget.
- L37 _public prototype_ `void Refresh(const bool bForce = false);` — Refreshes the content of this widget.
- L40 _private function_ `void OnRenderGridJobsSelectionChanged()`
- L41 _private function_ `void OnRemoteControlEntitiesExposed(URemoteControlPreset* Preset, const FGuid& EntityId)`
- L42 _private function_ `void OnRemoteControlEntitiesUnexposed(URemoteControlPreset* Preset, const FGuid& EntityId)`
- L43 _private function_ `void OnRemoteControlEntitiesUpdated(URemoteControlPreset* Preset, const TSet<FGuid>& ModifiedEntities)`
- L44 _private function_ `void OnRemoteControlPresetLayoutModified(URemoteControlPreset* Preset)`
- L45 _private prototype_ `void OnRemoteControlExposedPropertiesModified(URemoteControlPreset* Preset, const TSet<FGuid>& ModifiedProperties);`
- L49 _private prototype_ `URenderGridJob* GetSelectedJob();` — Returns the currently selected render grid job if 1 render grid job is currently selected, returns nullptr otherwise.
- L52 _private prototype_ `bool GetSelectedJobFieldValue(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, TArray<uint8>& OutBytes);` — Obtains the value (as bytes) of the given prop (the given remote control entity), returns true if it succeeded, returns false otherwise.
- L55 _private prototype_ `bool SetSelectedJobFieldValue(const TSharedPtr<FRemoteControlEntity>& RemoteControlEntity, const TArray<uint8>& Bytes);` — Sets the value of the given prop (the given remote control entity) with the given value (as bytes), returns true if it succeeded, returns false otherwise.
- L59 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L62 _private member_ `TWeakObjectPtr<URenderGridPropsSourceRemoteControl> PropsSourceWeakPtr;` — The props source control.
- L65 _private member_ `TSharedPtr<SVerticalBox> RowWidgetsContainer;` — The widget that lists the property rows.
- L68 _private member_ `TArray<TSharedPtr<SRenderGridRemoteControlTreeNode>> RowWidgets;` — The current property rows, needed to be able to refresh them, as well as to prevent garbage collection.
- L71 _private member_ `TArray<FRenderGridRemoteControlGenerateWidgetArgs> RowWidgetsArgs;` — The arguments that were used to create the current property rows, needed to not recreate the property rows unnecessarily.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridViewer.h` (Private)


#### enum `UE::RenderGrid::Private::ERenderGridViewerMode`  
`enum class ERenderGridViewerMode : uint8`  
_L24-30_
- desc: An enum containing the different render grid viewer modes that are currently available in the render grid plugin.
- L26 _public enumerator_ `Live`
- L27 _public enumerator_ `Preview`
- L28 _public enumerator_ `Rendered`
- L29 _public enumerator_ `None`

#### class `UE::RenderGrid::Private::SRenderGridViewer`  
`class SRenderGridViewer : public SCompoundWidget`  
_L35-63_
- inherits: `SCompoundWidget`
- desc: The render grid viewer, allows the user to see the expected render output, directly in the editor.
- L38 _public function_ `SLATE_BEGIN_ARGS(SRenderGridViewer)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L45 _private prototype_ `TSharedRef<SWidget> CreateViewerModeButton(const FText& ButtonText, const ERenderGridViewerMode ButtonViewerMode);` — Creates a tab button for a viewer mode.
- L49 _public prototype_ `void Refresh();` — Refreshes the content of this widget.
- L53 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L56 _private member_ `TSharedPtr<SBorder> WidgetContainer;` — The widget that lists the viewers.
- L59 _private member_ `ERenderGridViewerMode ViewerMode;` — The current viewer mode that should be shown in the UI.
- L62 _private member_ `ERenderGridViewerMode CachedViewerMode;` — The last viewer mode that was shown in the UI.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RenderGrid` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RenderGrid` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridViewerLive.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridEditorViewportClient`  
`class FRenderGridEditorViewportClient : public FEditorViewportClient`  
_L34-43_
- inherits: `FEditorViewportClient`
- desc: The viewport client for the live render grid viewer widget.
- L37 _public prototype_ `explicit FRenderGridEditorViewportClient(FPreviewScene* PreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);`
- L41 _public function_ `virtual EMouseCursor::Type GetCursor(FViewport* InViewport, int32 X, int32 Y) override`

#### class `UE::RenderGrid::Private::SRenderGridEditorViewport`  
`class SRenderGridEditorViewport : public SEditorViewport`  
_L49-109_
- inherits: `SEditorViewport`
- desc: The viewport for the live render grid viewer widget.
- L52 _public function_ `SLATE_BEGIN_ARGS(SRenderGridEditorViewport)`
- L53 _public prototype_ `SLATE_END_ARGS() virtual void Tick(const FGeometry&, const double, const float) override;`
- L56 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L59 _public prototype_ `void Render();`
- L60 _public prototype_ `void ClearSequenceFrame();`
- L61 _public prototype_ `bool ShowSequenceFrame(URenderGridJob* InJob, ULevelSequence* InSequence, const float InTime);`
- L62 _public function_ `bool HasRenderedLastAttempt() const`
- L63 _public function_ `UWorld* GetWorldPublic() const`
- L67 _protected function_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override`
- L68 _protected function_ `virtual void BindCommands() override`
- L69 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L72 _protected prototype_ `ULevelSequencePlayer* GetSequencePlayer();`
- L73 _protected prototype_ `void DestroySequencePlayer();`
- L77 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L80 _private member_ `TSharedPtr<FRenderGridEditorViewportClient> ViewportClient;` — The viewport client.
- L84 _private member_ `TWeakObjectPtr<UWorld> LevelSequencePlayerWorld;` — `UPROPERTY()` — The world that the level sequence actor was spawned in.
- L88 _private member_ `TObjectPtr<ALevelSequenceActor> LevelSequencePlayerActor;` — `UPROPERTY()` — The level sequence actor we spawned to play the sequence of any given render grid job.
- L92 _private member_ `TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer;` — `UPROPERTY()` — The level sequence player we created to play the sequence of any given render grid job.
- L96 _private member_ `TObjectPtr<ULevelSequence> LevelSequence;` — `UPROPERTY()` — The level sequence that we're currently playing.
- L100 _private member_ `TObjectPtr<URenderGridJob> RenderGridJob;` — `UPROPERTY()` — The render grid job that's currently being shown.
- L104 _private member_ `float LevelSequenceTime;` — `UPROPERTY()` — The time of the currently playing sequence.
- L108 _private member_ `bool bRenderedLastAttempt;` — `UPROPERTY()` — Whether it rendered or not during the last tick.

#### class `UE::RenderGrid::Private::SRenderGridViewerLive`  
`class SRenderGridViewerLive : public SCompoundWidget`  
_L115-150_
- inherits: `SCompoundWidget`
- desc: A render grid viewer widget, allows the user to see a live render using a viewport.
- L118 _public function_ `SLATE_BEGIN_ARGS(SRenderGridViewerLive)`
- L119 _public prototype_ `SLATE_END_ARGS() virtual void Tick(const FGeometry&, const double, const float) override;`
- L122 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L125 _private prototype_ `FReply OnClicked();`
- L126 _private prototype_ `void OnObjectModified(UObject* Object);`
- L127 _private prototype_ `void RenderGridJobDataChanged();`
- L128 _private prototype_ `void SelectedJobChanged();`
- L129 _private prototype_ `void FrameSliderValueChanged(const float NewValue);`
- L131 _private prototype_ `void UpdateViewport();`
- L132 _private prototype_ `void UpdateActionButton();`
- L133 _private prototype_ `void UpdateFrameSlider();`
- L137 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L140 _private member_ `TWeakObjectPtr<URenderGridJob> SelectedJobWeakPtr;` — A reference to the job that's currently rendering.
- L143 _private member_ `TSharedPtr<SRenderGridEditorViewport> ViewportWidget;` — The viewport widget.
- L146 _private member_ `TSharedPtr<SRenderGridViewerFrameSlider> FrameSlider;` — The widget that allows the user to select what frame they'd like to see.
- L149 _private member_ `TSharedPtr<SButton> ActionButton;` — The button which can be clicked, to to rerender the preview, or to open the map of the grid.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderGrid` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace RenderGrid` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace RenderGrid` (scope `UE`)
- L29 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridViewerPreview.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridViewerPreview`  
`class SRenderGridViewerPreview : public SCompoundWidget`  
_L36-116_
- inherits: `SCompoundWidget`
- desc: A render grid viewer widget, allows the user to render a single frame of a render grid job in low-resolution and afterwards see it in the editor.
- L39 _public function_ `SLATE_BEGIN_ARGS(SRenderGridViewerPreview)`
- L40 _public prototype_ `SLATE_END_ARGS() virtual void Tick(const FGeometry&, const double, const float) override;`
- L43 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`
- L46 _public prototype_ `void RenderNewPreview();` — Queues a new render action (if it isn't yet queued already). This is basically the Refresh() function of this widget.
- L49 _public prototype_ `void UpdateImageTexture(const bool bForce = true);` — Retrieves the rendered output from disk and shows it in the UI.
- L52 _public prototype_ `void SetImageTexture(UTexture2D* Texture);` — Shows the given texture, this is normally the output of a render.
- L56 _protected function_ `virtual bool IsPreviewWidget() const` — Returns true if this is the preview widget (1 frame), returns false if this is the rendered widgets (all frames). Override this function in order to change the value it returns.
- L59 _private prototype_ `FReply OnClicked();`
- L60 _private prototype_ `void OnObjectModified(UObject* Object);`
- L61 _private prototype_ `void GridDataChanged();`
- L62 _private prototype_ `void SelectedJobChanged();`
- L63 _private prototype_ `void FrameSliderValueChanged(const float NewValue);`
- L64 _private prototype_ `void FrameSliderValueChangedEnd();`
- L66 _private prototype_ `void InternalRenderNewPreview();`
- L67 _private prototype_ `void InternalRenderNewPreviewOfRenderGridJob(URenderGridJob* Job);`
- L68 _private prototype_ `void RenderNewPreviewCallback(const bool bSuccess);`
- L70 _private prototype_ `void UpdateActionButton();`
- L71 _private prototype_ `void UpdateFrameSlider();`
- L75 _private member_ `TWeakPtr<IRenderGridEditor> BlueprintEditorWeakPtr;` — A reference to the blueprint editor that owns the render grid instance.
- L78 _private member_ `TWeakObjectPtr<URenderGridQueue> CurrentRenderQueueWeakPtr;` — A reference to the queue that's currently rendering.
- L81 _private member_ `TWeakObjectPtr<URenderGridJob> SelectedJobWeakPtr;` — A reference to the job that's currently rendering.
- L84 _private member_ `int32 FramesUntilRenderNewPreview;` — Has a value of 1 if it should call RenderNewPreview() next frame, 2+ if it should subtract 1 from its value next frame, 0 and below and it won't do anything.
- L88 _private member_ `static bool bHasRenderedSinceAppStart;` — True if it has rendered before since the start of this application. Used for not hiding the rendering popup during the first render (since the first render can take a lot longer due to having to compile shaders etc).
- L91 _private member_ `TSharedPtr<SRenderGridViewerFrameSlider> FrameSlider;` — The widget that allows the user to select what frame they'd like to see.
- L94 _private member_ `TSharedPtr<SButton> ActionButton;` — The button which can be clicked, to to rerender the preview, or to open the map of the grid.
- L97 _private member_ `TSharedPtr<SImage> Image;` — The widget that contains the image.
- L100 _private member_ `TSharedPtr<SImage> ImageBackground;` — The widget that contains the background of the image.
- L103 _private member_ `FSlateBrush ImageBrushEmpty;` — The brush of the image, always empty.
- L106 _private member_ `FSlateBrush ImageBrush;` — The brush of the image.
- L109 _private member_ `TStrongObjectPtr<UTexture2D> ImageTexture;` — The texture of the image.
- L112 _private member_ `TWeakObjectPtr<URenderGridJob> LastUpdateImageTextureSelectedJobWeakPtr;` — The last render grid job used for the LastUpdateImageTexture function.
- L115 _private member_ `TOptional<int32> LastUpdateImageTextureFrame;` — The last frame used for the LastUpdateImageTexture function.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RenderGrid` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace RenderGrid` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace RenderGrid` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/SRenderGridViewerRendered.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridViewerRendered`  
`class SRenderGridViewerRendered : public SRenderGridViewerPreview`  
_L13-17_
- inherits: `SRenderGridViewerPreview`
- desc: A render grid viewer widget, allows the user to render a render grid job in low-resolution and afterwards scrub through the outputted frames of it in the editor.
- L16 _protected function_ `virtual bool IsPreviewWidget() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RenderGrid` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Tabs/SRenderGridJobListTab.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridJobListTab`  
`class SRenderGridJobListTab : public SCompoundWidget`  
_L20-27_
- inherits: `SCompoundWidget`
- desc: The render grid job list tab.
- L23 _public function_ `SLATE_BEGIN_ARGS(SRenderGridJobListTab)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Tabs/SRenderGridJobPropertiesTab.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridJobPropertiesTab`  
`class SRenderGridJobPropertiesTab : public SCompoundWidget`  
_L20-27_
- inherits: `SCompoundWidget`
- desc: The render grid job properties tab.
- L23 _public function_ `SLATE_BEGIN_ARGS(SRenderGridJobPropertiesTab)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Tabs/SRenderGridPropertiesTab.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridPropertiesTab`  
`class SRenderGridPropertiesTab : public SCompoundWidget`  
_L20-27_
- inherits: `SCompoundWidget`
- desc: The render grid properties tab.
- L23 _public function_ `SLATE_BEGIN_ARGS(SRenderGridPropertiesTab)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Tabs/SRenderGridViewerTab.h` (Private)


#### class `UE::RenderGrid::Private::SRenderGridViewerTab`  
`class SRenderGridViewerTab : public SCompoundWidget`  
_L20-27_
- inherits: `SCompoundWidget`
- desc: The render grid viewer tab.
- L23 _public function_ `SLATE_BEGIN_ARGS(SRenderGridViewerTab)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRenderGridEditor> InBlueprintEditor);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Private/UI/Utils/RenderGridWidgetUtils.h` (Private)


#### class `UE::RenderGrid::Private::RenderGridWidgetUtils`  
`class RenderGridWidgetUtils final`  
_L18-32_
- desc: A static class containing utility functions for widgets.
- L28 _public prototype_ `static TSharedRef<SWidget> CreateNodeValueWidget(const TSharedPtr<IDetailTreeNode>& Node);`
- L29 _public prototype_ `static bool FindPropertyHandleRecursive(const TSharedPtr<IPropertyHandle>& PropertyHandle, const FString& PropertyNameOrPath, ERenderGridFindNodeMethod FindMethod);`
- L30 _public prototype_ `static TSharedPtr<IDetailTreeNode> FindTreeNodeRecursive(const TSharedRef<IDetailTreeNode>& RootNode, const FString& PropertyNameOrPath, ERenderGridFindNodeMethod FindMethod);`
- L31 _public prototype_ `static TSharedPtr<IDetailTreeNode> FindNode(const TArray<TSharedRef<IDetailTreeNode>>& RootNodes, const FString& QualifiedPropertyName, ERenderGridFindNodeMethod FindMethod);`

#### enum `UE::RenderGrid::Private::RenderGridWidgetUtils::ERenderGridFindNodeMethod`  
`enum class ERenderGridFindNodeMethod : uint8`  
_L21-25_
- L23 _public enumerator_ `Name` — Find a node by providing its property name
- L24 _public enumerator_ `Path` — Find a node by providing a property path

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RenderGrid` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Public/Factories/IRenderGridPropsSourceWidgetFactory.h` (Public)


#### class `UE::RenderGrid::IRenderGridPropsSourceWidgetFactory`  
`class IRenderGridPropsSourceWidgetFactory`  
_L23-28_
- desc: The props source widget factory interface. Implementations should create a widget for the given props source.
- L26 _public prototype_ `virtual ~IRenderGridPropsSourceWidgetFactory() = default;`
- L27 _public function_ `virtual TSharedPtr<Private::SRenderGridPropsBase> CreateInstance(URenderGridPropsSourceBase* PropsSource, TSharedPtr<IRenderGridEditor> BlueprintEditor)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RenderGrid` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace RenderGrid` (scope `UE`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Public/IRenderGridEditor.h` (Public)


#### class `UE::RenderGrid::IRenderGridEditor`  
`class IRenderGridEditor : public FBlueprintEditor`  
_L26-104_
- inherits: `FBlueprintEditor`
- desc: The render grid editor interface.
- L30 _public prototype_ `virtual URenderGridBlueprint* GetRenderGridBlueprint() const = 0;` — @return The render grid blueprint currently being edited in this editor.
- L33 _public prototype_ `virtual URenderGrid* GetInstance() const = 0;` — @return The render grid instance.
- L36 _public prototype_ `virtual void SetIsDebugging(const bool bInIsDebugging) = 0;` — Sets whether the blueprint editor is in debugging mode or not.
- L39 _public prototype_ `virtual TSharedPtr<Private::FRenderGridBlueprintEditorToolbar> GetRenderGridToolbarBuilder() = 0;` — @return The render grid toolbar.
- L42 _public function_ `virtual bool IsCurrentlyRenderingOrPlaying() const` — Returns whether it is currently rendering or playing (so changes in the level and such should be ignored).
- L45 _public function_ `virtual bool CanCurrentlyRender() const` — Returns whether it can currently render (like a preview render or a batch render) or not.
- L48 _public function_ `virtual bool ShouldHideUI() const` — Returns whether it is should currently hide the UI for things to not cause any bugs (like during rendering etc).
- L51 _public prototype_ `virtual bool IsBatchRendering() const = 0;` — Returns whether it is currently batch rendering or not.
- L54 _public prototype_ `virtual URenderGridQueue* GetBatchRenderQueue() const = 0;` — Returns the current batch render queue, or null if it's not currently batch rendering.
- L57 _public prototype_ `virtual bool IsPreviewRendering() const = 0;` — Returns whether it is currently preview rendering or not.
- L60 _public prototype_ `virtual URenderGridQueue* GetPreviewRenderQueue() const = 0;` — Returns the current preview render queue, or null if it's not currently rendering a preview.
- L63 _public prototype_ `virtual void SetPreviewRenderQueue(URenderGridQueue* Queue) = 0;` — Sets the current preview render queue, set it to null if it's not currently rendering a preview.
- L66 _public prototype_ `virtual void MarkAsModified() = 0;` — Marks the editing asset as modified.
- L69 _public prototype_ `virtual TArray<URenderGridJob*> GetSelectedRenderGridJobs() const = 0;` — Get the currently selected render grid jobs.
- L72 _public prototype_ `virtual void SetSelectedRenderGridJobs(const TArray<URenderGridJob*>& Jobs) = 0;` — Set the selected render grid jobs.
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridChanged);`
- L75 _public function_ `virtual FOnRenderGridChanged& OnRenderGridChanged()`
- L77 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRenderGridJobCreated, URenderGridJob*);`
- L78 _public function_ `virtual FOnRenderGridJobCreated& OnRenderGridJobCreated()`
- L80 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridJobsSelectionChanged);`
- L81 _public function_ `virtual FOnRenderGridJobsSelectionChanged& OnRenderGridJobsSelectionChanged()`
- L83 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridShouldHideUIChanged);`
- L84 _public function_ `virtual FOnRenderGridShouldHideUIChanged& OnRenderGridShouldHideUIChanged()`
- L86 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridPreviewRenderedFirstTimeSinceAppStart) virtual FOnRenderGridPreviewRenderedFirstTimeSinceAppStart& OnRenderGridPreviewRenderedFirstTimeSinceAppStart()`
- L91 _private member_ `FOnRenderGridChanged OnRenderGridChangedDelegate;` — The delegate for when data in the render grid changed.
- L94 _private member_ `FOnRenderGridJobCreated OnRenderGridJobCreatedDelegate;` — The delegate for when a render grid job is created.
- L97 _private member_ `FOnRenderGridJobsSelectionChanged OnRenderGridJobsSelectionChangedDelegate;` — The delegate for when the selection of render grid jobs changed.
- L100 _private member_ `FOnRenderGridShouldHideUIChanged OnRenderGridShouldHideUIChangedDelegate;` — The delegate for when the the result of ShouldHideUI() has changed.
- L103 _private member_ `FOnRenderGridPreviewRenderedFirstTimeSinceAppStart OnRenderGridPreviewRenderedFirstTimeSinceAppStartDelegate;` — The delegate for the first time (since the start of this application) that the preview is rendered.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace RenderGrid` (scope `UE`)
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridChanged);`
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRenderGridJobCreated, URenderGridJob*);`
- L80 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridJobsSelectionChanged);`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridShouldHideUIChanged);`
- L86 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRenderGridPreviewRenderedFirstTimeSinceAppStart) virtual FOnRenderGridPreviewRenderedFirstTimeSinceAppStart& OnRenderGridPreviewRenderedFirstTimeSinceAppStart() { return OnRenderGridPreviewRenderedFirstTimeSinceAppStartDelegate; } private: FOnRenderGridChanged OnRenderGridChangedDelegate;`

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Public/IRenderGridEditorModule.h` (Public)


#### class `UE::RenderGrid::IRenderGridEditorModule`  
`class IRenderGridEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L31-52_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: RenderGridEditor module interface.
- L39 _public function_ `static inline IRenderGridEditorModule& Get()` — Singleton-like access to IRenderGridEditorModule. @return Returns RenderGridEditorModule singleton instance, loading the module on demand if needed.
- L45 _public prototype_ `virtual TSharedRef<IRenderGridEditor> CreateRenderGridEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, URenderGridBlueprint* InBlueprint) = 0;` — Creates an instance of the render grid editor.
- L48 _public prototype_ `virtual TSharedPtr<Private::SRenderGridPropsBase> CreatePropsSourceWidget(URenderGridPropsSourceBase* PropsSource, TSharedPtr<IRenderGridEditor> BlueprintEditor) = 0;` — Creates a props source widget for the given props source.
- L51 _public prototype_ `virtual const TMap<ERenderGridPropsSourceType, TSharedPtr<IRenderGridPropsSourceWidgetFactory>>& GetPropsSourceWidgetFactories() const = 0;` — Returns all the factories for creating widgets for props sources.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RenderGrid` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::RenderGrid`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace RenderGrid` (scope `UE`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridEditor/Public/RenderGridEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogRenderGridEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogRenderGridEditor, Log, All);`
